//------------------------------------------------------------------------------
/// \file
/// \ingroup triangulate
/// \copyright (C) Copyright Aquaveo 2018. Distributed under FreeBSD License
/// (See accompanying file LICENSE or https://aquaveo.com/bsd/license.txt)
//------------------------------------------------------------------------------

//----- Included files ---------------------------------------------------------

// 1. Precompiled header

// 2. My own header
#include <xmsgrid/triangulate/TrBreaklineAdder.h>

// 3. Standard library headers
#include <functional>

// 4. External library headers

// 5. Shared code headers
#include <xmscore/misc/Progress.h>
#include <xmscore/stl/set.h>
#include <xmscore/stl/vector.h>
#include <xmsgrid/geometry/geoms.h>
#include <xmsgrid/geometry/GmBoostTypes.h>
#include <xmsgrid/geometry/GmPtSearch.h>
#include <xmsgrid/geometry/GmMultiPolyIntersector.h>
#include <xmsgrid/geometry/GmMultiPolyIntersectionSorterTerse.h>
#include <xmscore/misc/Observer.h>
#include <xmsgrid/triangulate/triangles.h>
#include <xmsgrid/triangulate/TrTin.h>
#include <xmscore/misc/XmError.h>

// 6. Non-shared code headers

//----- Namespace declaration --------------------------------------------------

namespace xms
{
//----- Forward declarations ---------------------------------------------------

//----- External globals -------------------------------------------------------

//----- Constants / Enumerations -----------------------------------------------

//----- Classes / Structs ------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
/// \brief Defines an edge that intersects a breakline
struct edgerecord
{
  int pt1;           ///< Index of point defining the edge
  int pt2;           ///< Index of point defining the edge
  Pt3d intersection; ///< Point of intersection
};

typedef std::vector<edgerecord> VecEdge; ///< Vector of edgerecord

////////////////////////////////////////////////////////////////////////////////
class TrBreaklineAdderImpl : public TrBreaklineAdder
{
public:
  TrBreaklineAdderImpl();
  virtual ~TrBreaklineAdderImpl();

  /// \brief Set the observer to use for feedback while processing.
  /// \param a_: The observer.
  virtual void SetObserver(BSHP<Observer> a_) override { m_observer = a_; }
  virtual void SetTin(BSHP<TrTin> a_tin, double a_tol = -1) override;
  virtual void AddBreakline(const VecInt& a_breakline) override;
  virtual void AddBreaklines(const VecInt2d& a_breakline) override;
  virtual std::string ErrorMessage(int) const override;

private:
  bool GetExtents();
  void ComputeTolerance();
  bool CrossesBoundary(int a_blpt1, int a_blpt2);
  void ProcessSegmentBySwapping(int a_vtx1, int a_vtx2);
  void GetIntersectingEdges(int a_blpt1, int a_blpt2, VecEdge& a_edges);
  void FindIntersectingEdgeFromPoint(int a_blpt1,
                                     int a_blpt2,
                                     int* a_intpt1,
                                     int* a_intpt2,
                                     double* a_x,
                                     double* a_y,
                                     double* a_z1,
                                     double* a_z2);
  void FindIntersectingEdgeFromEdge(int a_ept1,
                                    int a_ept2,
                                    int a_blpt1,
                                    int a_blpt2,
                                    int* a_intpt1,
                                    int* a_intpt2,
                                    double* a_x,
                                    double* a_y,
                                    double* a_z1,
                                    double* a_z2);

  BSHP<TrTin> m_tin;         ///< The tin
  BSHP<Observer> m_observer; ///< The observer
  double m_xyTol;            ///< Xy tolerance used with geom functions
  VecInt* m_tris;            ///< Pointer to m_tin triangles for convenience
  VecPt3d* m_pts;            ///< Pointer to m_tin points for convenience
  VecInt2d* m_trisAdjToPts;  ///< Pointer to m_tin trisAdjToPts for convenience
  Pt3d m_mn;                 ///< Minimum extent of all points
  Pt3d m_mx;                 ///< Maximum extent of all points
  BSHP<GmMultiPolyIntersector>
    m_multiPolyIntersector;    ///< Used to check if breakline crosses boundary
  BSHP<GmPtSearch> m_searcher; ///< Used to check if breakline crosses boundary
};                             // class TrBreaklineAdderImpl

//----- Internal functions -----------------------------------------------------

//----- Class / Function definitions -------------------------------------------

////////////////////////////////////////////////////////////////////////////////
/// \class TrBreaklineAdderImpl
/// \brief Adds breaklines to a triangulation.
////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
/// \brief
//------------------------------------------------------------------------------
TrBreaklineAdderImpl::TrBreaklineAdderImpl()
: m_tin()
, m_observer()
, m_xyTol(1e-9)
, m_tris(nullptr)
, m_pts(nullptr)
, m_trisAdjToPts(nullptr)
, m_mn()
, m_mx()
, m_multiPolyIntersector()
, m_searcher()
{
}
//------------------------------------------------------------------------------
/// \brief
//------------------------------------------------------------------------------
TrBreaklineAdderImpl::~TrBreaklineAdderImpl()
{
}
//------------------------------------------------------------------------------
/// \brief Sets the tin that will have breaklines added to it.
/// \param a_tin: The tin to be modified.
/// \param a_tol: Tolerance used when intersecting line segments. Optional. If
///               not specified, one is computed from the tin extents.
//------------------------------------------------------------------------------
void TrBreaklineAdderImpl::SetTin(BSHP<TrTin> a_tin, double a_tol /*-1*/)
{
  m_tin = a_tin;

  // Check for an invalid tin
  XM_ENSURE_TRUE_T_NO_ASSERT(m_tin, std::runtime_error("Tin is null."));
  // XM_ENSURE_TRUE_T_NO_ASSERT(!m_tin->Triangles().empty(), std::runtime_error("Tin has no
  // triangles."));  XM_ENSURE_TRUE_T_NO_ASSERT(!m_tin->Points().empty(), std::runtime_error("Tin
  // has no points."));  XM_ENSURE_TRUE_T_NO_ASSERT(!m_tin->TrisAdjToPts().empty(),
  //                 std::runtime_error("Tin has no adjacency info."));

  m_tris = &m_tin->Triangles();
  m_pts = &m_tin->Points();
  m_trisAdjToPts = &m_tin->TrisAdjToPts();
  if (a_tol < 0)
  {
    ComputeTolerance();
  }
  else
  {
    m_xyTol = a_tol;
  }
} // TrBreaklineAdderImpl::SetTin
//------------------------------------------------------------------------------
/// \brief Add a breakline by swapping. Compare to bkProcessScatBySwapping.
///
/// Currently does not consider points that are coincident with the breakline.
/// \param a_breakline: The breakline to add as indices of m_tin->Points().
//------------------------------------------------------------------------------
void TrBreaklineAdderImpl::AddBreakline(const VecInt& a_breakline)
{
  XM_ENSURE_TRUE_T_NO_ASSERT(m_tin, std::runtime_error("No tin set in TrBreaklineAdder."));
  Progress prog("Adding Breaklines");
  double totNumSegs = static_cast<double>(a_breakline.size() - 1);
  double segCount(0.0);

  for (size_t pt = 1; pt < a_breakline.size(); ++pt)
  {
    int pt1 = a_breakline[pt - 1];
    int pt2 = a_breakline[pt];
    if (!m_tin->VerticesAreAdjacent(pt1, pt2))
    {
      ProcessSegmentBySwapping(pt1, pt2);
    }
    segCount += 1.0;
    prog.ProgressStatus(std::min(1.0, segCount / totNumSegs));
  }
} // TrBreaklineAdderImpl::AddBreakline
//------------------------------------------------------------------------------
/// \brief Add breaklines by swapping. Compare to bkProcessScatBySwapping.
///
/// Currently does not consider points that are coincident with the breakline.
/// \param a_breaklines: The breaklines to add as indices of m_tin->Points().
//------------------------------------------------------------------------------
void TrBreaklineAdderImpl::AddBreaklines(const VecInt2d& a_breaklines)
{
  XM_ENSURE_TRUE_T_NO_ASSERT(m_tin, std::runtime_error("No tin set in TrBreaklineAdder."));
  Progress prog("Adding Breaklines");
  size_t segCount(0);
  size_t totNumSegs(0);
  for (size_t i = 0; i < a_breaklines.size(); ++i)
  {
    totNumSegs += a_breaklines[i].size() - 1;
  }
  double total = static_cast<double>(totNumSegs);
  for (size_t i = 0; i < a_breaklines.size(); ++i)
  {
    segCount += a_breaklines[i].size() - 1;
    AddBreakline(a_breaklines[i]);
    prog.ProgressStatus(static_cast<double>(segCount) / total);
  }
} // TrBreaklineAdderImpl::AddBreaklines
//------------------------------------------------------------------------------
/// \brief Returns the error message associated with the given number.
/// \param[in] a_messageNumber: Number associated with an error message.
/// \return The error message.
//------------------------------------------------------------------------------
std::string TrBreaklineAdderImpl::ErrorMessage(int a_messageNumber) const
{
  std::string message;
  switch (a_messageNumber)
  {
  case 0:
    message = "One or more breakline segments intersected a boundary and was ignored.";
    break;
  default:
    XM_ASSERT(false);
    break;
  }
  return message;
} // TrBreaklineAdderImpl::ErrorMessage
//------------------------------------------------------------------------------
/// \brief Returns true if the line connecting the two points crosses the tin
///        boundary.
/// \param a_blpt1: First point of breakline segment.
/// \param a_blpt2: Second point of breakline segment.
/// \return true if the line connecting the two points crosses a boundary.
//------------------------------------------------------------------------------
bool TrBreaklineAdderImpl::CrossesBoundary(int a_blpt1, int a_blpt2)
{
  //#if 0
  if (!m_multiPolyIntersector)
  {
    VecInt2d boundaryPolys;
    m_tin->GetBoundaryPolys(boundaryPolys);

    BSHP<GmMultiPolyIntersectionSorter> sorter =
      BSHP<GmMultiPolyIntersectionSorter>(new GmMultiPolyIntersectionSorterTerse());
    m_multiPolyIntersector = GmMultiPolyIntersector::New(m_tin->Points(), boundaryPolys, sorter);
    m_multiPolyIntersector->SetQuery(GMMPIQ_INTERSECTS);

    m_searcher = GmPtSearch::New(true);
    m_searcher->PtsToSearch(m_tin->PointsPtr());
  }

  VecInt intersectedPolys;
  VecPt3d intersectionPts;
  m_multiPolyIntersector->TraverseLineSegment(
    m_tin->Points()[a_blpt1].x, m_tin->Points()[a_blpt1].y, m_tin->Points()[a_blpt2].x,
    m_tin->Points()[a_blpt2].y, intersectedPolys, intersectionPts);
  if (intersectedPolys.empty())
  {
    return false;
  }
  else
  {
    // See if the intersectionPts are at the boundary points. If so, we aren't
    // crossing an edge.
    for (size_t i = 0; i < intersectionPts.size(); ++i)
    {
      if (!m_searcher->PtInRTree(intersectionPts[i], m_xyTol))
      {
        return true;
      }
    }
  }
  //#endif
  return false;
} // TrBreaklineAdderImpl::CrossesBoundary
//------------------------------------------------------------------------------
/// \brief Insert breakline segment into triangulation by swapping triangle
///        edges. Compare to bkiProcessScatSegmentBySwapping
/// \param a_blpt1: First point of breakline segment.
/// \param a_blpt2: Second point of breakline segment.
//------------------------------------------------------------------------------
void TrBreaklineAdderImpl::ProcessSegmentBySwapping(int a_blpt1, int a_blpt2)
{
  if (CrossesBoundary(a_blpt1, a_blpt2))
  {
    XM_LOG(xmlog::warning,
           "One or more breakline segments intersected a boundary and was ignored.");
    return;
  }

  VecEdge edges;
  GetIntersectingEdges(a_blpt1, a_blpt2, edges);
  
  Pt3d blvtx1 = m_tin->Points()[a_blpt1];
  Pt3d blvtx2 = m_tin->Points()[a_blpt2];
  double bk_seg_dx = blvtx2.x - blvtx1.x;
  double bk_seg_dy = blvtx2.y - blvtx1.y;
  double mag = sqrt(bk_seg_dx*bk_seg_dx + bk_seg_dy*bk_seg_dy);
  if (mag < XM_ZERO_TOL)
  {
    // error - degenerate break line segment - we won't force this segment
    return;
  }
  bk_seg_dx /= mag;
  bk_seg_dy /= mag;

  VecEdge::iterator edge = edges.begin();

  // the goal is to avoid very skinny angles.  Start by limiting to > 15.0 degrees.
  double minAngle = 15.0;
  bool trisSwappedThisPass = false;
  double x, y, z1, z2;

  while (!edges.empty() && edge != edges.end())
  {
    int tri1 = m_tin->TriangleAdjacentToEdge(edge->pt1, edge->pt2);
    int tri2 = m_tin->TriangleAdjacentToEdge(edge->pt2, edge->pt1);

        // make sure the swapped edge is better than the current edge
    int a1, a2, a3, b1, b2, b3;
    int top, btm, lft, rgt;
    Pt3d toppt, btmpt, lftpt, rgtpt;
    /*****************************************
    *                b2 * top               *
    *                  / \                  *
    *                 /   \   tri2          *
    *             b3 / --> \ b1             *
    *           lft *-------* rgt           *
    *                \ <-- / a3             *
    *                 \   /   tri1          *
    *                  \ /                  *
    *               btm * a2                *
    *****************************************/
    if (tri2 == -1 || tri1 == -1)
    {
      // error - invalid triangle in surface (hole?) - we won't force this segment
      return;
    }
    b3 = m_tin->CommonEdgeIndex(tri2, tri1);
    b2 = trDecrementIndex(b3);
    b1 = trIncrementIndex(b3);
    a3 = m_tin->CommonEdgeIndex(tri1, tri2);
    a1 = trIncrementIndex(a3);
    a2 = trIncrementIndex(a1);
    top = m_tin->GlobalIndex(tri2, b2);
    lft = m_tin->GlobalIndex(tri2, b3);
    rgt = m_tin->GlobalIndex(tri2, b1);
    btm = m_tin->GlobalIndex(tri1, a2);
    toppt = m_tin->Points()[top];
    lftpt = m_tin->Points()[lft];
    rgtpt = m_tin->Points()[rgt];
    btmpt = m_tin->Points()[btm];

    // this code tries to prevent bad triangles but we can't do that if 
    // we are FORCING a breakline

    //// dot product of the original edge with the bkline seg
    //double edge_dx = rgtpt.x - lftpt.x;
    //double edge_dy = rgtpt.y - lftpt.y;
    //double mag = sqrt(edge_dx*edge_dx + edge_dy*edge_dy);
    //if (mag < XM_ZERO_TOL)
    //{
    //  // error - duplicate vertices - we won't force this segment
    //  return;
    //}
    //edge_dx /= mag;
    //edge_dy /= mag;
    //double dot_edge = fabs(edge_dx*bk_seg_dx + edge_dy*bk_seg_dy);

    //// dot product of the swapped edge with the bkline seg
    //edge_dx = toppt.x - btmpt.x;
    //edge_dy = toppt.y - btmpt.y;
    //mag = sqrt(edge_dx*edge_dx + edge_dy*edge_dy);
    //if (mag < XM_ZERO_TOL)
    //{
    //  // error - duplicate vertices - we won't force this segment
    //  return;
    //}
    //edge_dx /= mag;
    //edge_dy /= mag;
    //double dot_swap = fabs(edge_dx*bk_seg_dx + edge_dy*bk_seg_dy);

    // if the swap is a bad idea or the edge won't swap, go on to the next edge
    //if (dot_swap < dot_edge || !trSwapEdgeWithMinAngle(*m_tin, tri1, tri2, minAngle))
    if (!trSwapEdgeWithMinAngle(*m_tin, tri1, tri2, minAngle))
    {
      ++edge;
    }
    else
    {
      trisSwappedThisPass = true;
      // See if new edge needs to be put on the list
      int index = m_tin->CommonEdgeIndex(tri1, tri2);
      // 'unsigned int', possible loss of data
      int newpt1 = (*m_tris)[(tri1 * 3) + index];
      index = trIncrementIndex(index);
      int newpt2 = (*m_tris)[(tri1 * 3) + index];
      if ((newpt1 != a_blpt1) && (newpt1 != a_blpt2) && (newpt2 != a_blpt1) &&
          (newpt2 != a_blpt2) &&
          gmIntersectLineSegmentsWithTol((*m_pts)[a_blpt1], (*m_pts)[a_blpt2], (*m_pts)[newpt1],
                                         (*m_pts)[newpt2], &x, &y, &z1, &z2, m_xyTol))
      {
        // put edge on the list in place of swapped one
        edge->pt1 = newpt1;
        edge->pt2 = newpt2;
        ++edge;
      }
      else
      {
        // Remove this edge from the list
        edge = edges.erase(edge);
      }
    }
    // if we are still not adjacent
    if (edge == edges.end() && (tri1 != -1 && tri2 != -1))
    {
      // if we didn't do any swaps reduce the minimum angle
      if (!trisSwappedThisPass)
      {
        minAngle /= 2.0;
      }
      // start over with the edge list
      edge = edges.begin();
      trisSwappedThisPass = false;
    }
    else if (m_tin->VerticesAreAdjacent(a_blpt1, a_blpt2))
      break;
    // if (xgCheckEscape()) {
    //  throw exceptions::Exception("User Escape");
    //}
  }
} // TrBreaklineAdderImpl::ProcessSegmentBySwapping
//------------------------------------------------------------------------------
/// \brief Find triangle edges which intersect the breakline. Compare to
///        bkiGetListOfIntersectingScatEdges.
/// \param a_blpt1: First point of breakline segment.
/// \param a_blpt2: Second point of breakline segment.
/// \param a_edges: Edges which intersect the breakline.
//------------------------------------------------------------------------------
void TrBreaklineAdderImpl::GetIntersectingEdges(int a_blpt1, int a_blpt2, VecEdge& a_edges)
{
  bool first = true;
  bool done = false;
  int intpt1, intpt2;
  double x, y, z1, z2;
  do
  {
    if (first)
    {
      FindIntersectingEdgeFromPoint(a_blpt1, a_blpt2, &intpt1, &intpt2, &x, &y, &z1, &z2);
      first = false;
    }
    else
    {
      FindIntersectingEdgeFromEdge(intpt2, intpt1, a_blpt1, a_blpt2, &intpt1, &intpt2, &x, &y, &z1,
                                   &z2);
    }
    if (intpt1 == -1 || intpt2 == -1)
      done = true;
    else if (intpt1 == a_blpt2 || intpt2 == a_blpt2)
      done = true;
    else
    {
      edgerecord edge;
      edge.pt1 = intpt1;
      edge.pt2 = intpt2;
      edge.intersection.x = x;
      edge.intersection.y = y;
      edge.intersection.z = z2;
      a_edges.push_back(edge);
    }
  } while (!done);

} // TrBreaklineAdderImpl::GetIntersectingEdges
//------------------------------------------------------------------------------
/// \brief Finds edge opposite of a_blpt1 intersected by breakline segment
///        a_blpt1, a_blpt2. Compare to bkiFindIntersectingEdgeFromVertex.
/// \param a_blpt1: First breakline segment point.
/// \param a_blpt2: Second breakline segment point.
/// \param a_intpt1: First point on intersecting edge, or -1 if not found.
/// \param a_intpt2: Second point on intersecting edge, or -1 if not found.
/// \param a_x: x value of intersection.
/// \param a_y: y value of intersection.
/// \param a_z1: z value of intersection.
/// \param a_z2: z value of intersection.
//------------------------------------------------------------------------------
void TrBreaklineAdderImpl::FindIntersectingEdgeFromPoint(int a_blpt1,
                                                         int a_blpt2,
                                                         int* a_intpt1,
                                                         int* a_intpt2,
                                                         double* a_x,
                                                         double* a_y,
                                                         double* a_z1,
                                                         double* a_z2)
{
  // loop thru adjacent tris until found
  bool found = false;
  // 'unsigned int', possible loss of data
  for (size_t adjTri = 0; adjTri < (*m_trisAdjToPts)[a_blpt1].size() && !found; ++adjTri)
  {
    int tri = (*m_trisAdjToPts)[a_blpt1][adjTri];
    // Check opposite edge(s) for intersections
    int localIdx1 = m_tin->LocalIndex(tri, a_blpt1);
    localIdx1 = trIncrementIndex(localIdx1);
    int localIdx2 = trIncrementIndex(localIdx1);
    *a_intpt1 = m_tin->Triangles()[(tri * 3) + localIdx1];
    *a_intpt2 = m_tin->Triangles()[(tri * 3) + localIdx2];
    found =
      gmIntersectLineSegmentsWithTol((*m_pts)[a_blpt1], (*m_pts)[a_blpt2], (*m_pts)[*a_intpt1],
                                     (*m_pts)[*a_intpt2], a_x, a_y, a_z1, a_z2, m_xyTol);
  }
  if (!found)
  {
    *a_intpt1 = *a_intpt2 = -1;
  }

} // TrBreaklineAdderImpl::FindIntersectingEdgeFromPoint
//------------------------------------------------------------------------------
/// \brief Finds edge of triangle intersected by breakline and returns next
///        edge in a_intpt1 and a_intpt2. Compare to
///        bkiFindIntersectingScatEdgeFromEdge.
/// \param a_ept1: First point of starting edge.
/// \param a_ept2: Second point of starting edge.
/// \param a_blpt1: First point of breakline segment.
/// \param a_blpt2: Second point of breakline segment.
/// \param a_intpt1: First point of intersecting edge, or -1 if not found.
/// \param a_intpt2: Second point of intersecting edge, or -1 if not found.
/// \param a_x: x value of intersection.
/// \param a_y: y value of intersection.
/// \param a_z1: z value of intersection.
/// \param a_z2: z value of intersection.
//------------------------------------------------------------------------------
void TrBreaklineAdderImpl::FindIntersectingEdgeFromEdge(int a_ept1,
                                                        int a_ept2,
                                                        int a_blpt1,
                                                        int a_blpt2,
                                                        int* a_intpt1,
                                                        int* a_intpt2,
                                                        double* a_x,
                                                        double* a_y,
                                                        double* a_z1,
                                                        double* a_z2)
{
  bool found = false;
  int tri = m_tin->TriangleAdjacentToEdge(a_ept2, a_ept1);
  XM_ENSURE_TRUE_T_NO_ASSERT(tri != -1, std::runtime_error("Void in breakline"));

  int localIdx1 = m_tin->LocalIndex(tri, a_ept2);
  const int kNumcorners = 3;
  int crnrid;
  int count;
  for (crnrid = localIdx1, count = 1; !found && count <= kNumcorners - 1; count++)
  {
    int nextid = trIncrementIndex(crnrid);
    int trisIdx = tri * 3;
    *a_intpt1 = (*m_tris)[trisIdx + crnrid];
    *a_intpt2 = (*m_tris)[trisIdx + nextid];
    found =
      gmIntersectLineSegmentsWithTol((*m_pts)[a_blpt1], (*m_pts)[a_blpt2], (*m_pts)[*a_intpt1],
                                     (*m_pts)[*a_intpt2], a_x, a_y, a_z1, a_z2, m_xyTol);
    if (found)
    {
      int adjTri = -1;
      int id1, id2;
      m_tin->TriangleFromEdge(*a_intpt1, *a_intpt2, adjTri, id1, id2);
      if (adjTri == -1)
      {
        throw std::runtime_error("Void in breakline");
      }
    }
    crnrid = nextid;
  }

  if (!found)
  {
    *a_intpt1 = *a_intpt2 = -1;
  }

} // TrBreaklineAdderImpl::FindIntersectingEdgeFromEdge
//------------------------------------------------------------------------------
/// \brief Computes the extents (min, max) of the polygon.
/// \return true if there are any points and the extents were computed.
//------------------------------------------------------------------------------
bool TrBreaklineAdderImpl::GetExtents()
{
  if (m_tin)
  {
    return m_tin->GetExtents(m_mn, m_mx);
  }
  return false;
} // TrBreaklineAdderImpl::GetExtents
//------------------------------------------------------------------------------
/// \brief Computes a tolerance to use based on point extents.
//------------------------------------------------------------------------------
void TrBreaklineAdderImpl::ComputeTolerance()
{
  if (GetExtents())
  {
    m_xyTol = gmComputeXyTol(m_mn, m_mx);
  }
} // TrBreaklineAdderImpl::ComputeTolerance

////////////////////////////////////////////////////////////////////////////////
/// \class TrBreaklineAdder
/// \brief Adds breaklines to a tin.
///
/// Currently only swapping is implemented. Currently does not consider points
/// that are coincident with the breakline.
////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
/// \brief
//------------------------------------------------------------------------------
TrBreaklineAdder::TrBreaklineAdder()
{
}
//------------------------------------------------------------------------------
/// \brief
//------------------------------------------------------------------------------
TrBreaklineAdder::~TrBreaklineAdder()
{
}
//------------------------------------------------------------------------------
/// \brief Create a TrBreaklineAdderImpl object.
/// \return TrBreaklineAdder.
//------------------------------------------------------------------------------
BSHP<TrBreaklineAdder> TrBreaklineAdder::New()
{
  return BDPC<TrBreaklineAdder>(BSHP<TrBreaklineAdderImpl>(new TrBreaklineAdderImpl()));
} // TrBreaklineAdder::TrBreaklineAdder

} // namespace xms

///////////////////////////////////////////////////////////////////////////////
// TESTS
///////////////////////////////////////////////////////////////////////////////
#ifdef CXX_TEST

#include <xmsgrid/triangulate/TrBreaklineAdder.t.h>

#include <boost/assign.hpp>

#include <xmscore/testing/TestTools.h>
#include <xmscore/misc/carray.h>
#include <xmsgrid/triangulate/TrTriangulatorPoints.h>
#include <xmsgrid/triangulate/TrTin.t.h>

//----- Namespace declaration --------------------------------------------------

// namespace xms {
using namespace xms;

////////////////////////////////////////////////////////////////////////////////
/// \class TrBreaklineAdderUnitTests
/// \brief Tests for TrBreaklineAdder
////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
/// \brief Test a simple case involving a swap and removal of outer triangle.
/// \verbatim
//  Before
//
//  4-          3---------------4
//   |        / | \           / | \
//   |      /   |   \   5   /   |   \
//   |    /     |     \   /     |     \
//  0-  0    0  |  1    1    2  |  4    2
//   |    \     |     /   \     |     /
//   |      \   |   /   3   \   |   /
//   |        \ | /           \ | /
// -4-          5-------------- 6
//
//      |-------|-------|-------|-------|
//      0       5      10      15      20
//
//  After
//
//  4-          3---------------4
//   |        / | \           /   \
//   |      /   |   \   5   /   2   \
//   |    /     |     \   /           \
//  0-  0    0  |  1    1---------------2
//   |    \     |     /   \           /
//   |      \   |   /   3   \   4   /
//   |        \ | /           \   /
// -4-          5-------------- 6
//
//      |-------|-------|-------|-------|
//      0       5      10      15      20
/// \endverbatim
//------------------------------------------------------------------------------
void TrBreaklineAdderUnitTests::test1()
{
  // Set up the tin
  BSHP<TrTin> tin = TrTin::New();
  tin->Points() = {{0, 0, 0},  {10, 0, 0}, {20, 0, 0}, {5, 4, 0},
                   {15, 4, 0}, {5, -4, 0}, {15, -4, 0}};
  TrTriangulatorPoints triangulator(tin->Points(), tin->Triangles(), &tin->TrisAdjToPts());
  triangulator.Triangulate();

  // Verify triangles before
  int trisB[] = {0, 5, 3, 3, 5, 1, 1, 6, 4, 6, 1, 5, 2, 4, 6, 1, 4, 3};
  TS_ASSERT_EQUALS(VecInt(&trisB[0], &trisB[18]), tin->Triangles());

  // Add breakline
  BSHP<TrBreaklineAdder> adder = TrBreaklineAdder::New();
  adder->SetTin(tin);
  VecInt outPoly = {0, 5, 6, 1, 2, 4, 3};
  adder->AddBreakline(outPoly);

  // Verify triangles after
  int trisA[] = {0, 5, 3, 3, 5, 1, 1, 2, 4, 6, 1, 5, 2, 1, 6, 1, 4, 3};
  TS_ASSERT_EQUALS(VecInt(&trisA[0], &trisA[XM_COUNTOF(trisA)]), tin->Triangles());

} // TrBreaklineAdderUnitTests::test1
//------------------------------------------------------------------------------
/// \brief Test a more complex case involving two inner polygons and removal
///        of outer triangles. This doesn't remove the triangles - that would
///        be the next step.
/// \verbatim
//  Before
//
//  10-  17-----18------19------20------21
//    |  |\  8  /|\ 11  /|\ 22  / \ 26  /|
//    |  | \   / | \   / | \   /   \   //|
//    |  |  \ /  |  \ /30|23\ / 27  \ / /|
//   5-  |6 13 12|9 14   |  15------16  /|
//    |  |  / \  |  /|\  |  / \ 25  /|28/|
//    |  | /   \ | / | \ | /   \   / | / |
//    |  |/  7  \|/  |  \|/ 24  \ /29| / |
//   0-  9------10 10|3 11------12   | / |
//    |  |\ 13  / \  |  / \ 15  / \  |/  |
//    |  | \   /   \ | /   \   /   \ |/  |
//    |  |  \ /  5  \|/ 16  \ / 21  \|/  |
//  -5-  | 0 5-------6-------7-------8 18|
//    |  |  / \  4  / \ 14  / \ 19  / \  |
//    |  | /   \   /   \   /   \   /   \ |
//    |  |/  1  \ /  2  \ / 20  \ / 17  \|
// -10-  0-------1-------2-------3-------4
//
//       |-------|-------|-------|-------|
//       0      10      20      30      40
//
//  After swapping
//
//  10-  17-----18------19------20------21
//    |  |\  8  / \ 11  /|\ 22  / \ 26  /|
//    |  | \   /   \   / | \   /   \   //|
//    |  |  \ / 12  \ /30|23\ / 27  \ / /|
//   5-  |6 13------14   |  15------16  /|
//    |  |  /|\  9  /|\  |  /|\ 25  /|28/|
//    |  | / | \   / | \ | / | \   / | / |
//    |  |/  |  \ /  |  \|/  |24\ /29| / |
//   0-  9 13|7 10 10|3 11 15|  12   | / |
//    |  |\  |  / \  |  / \  |  / \  |/  |
//    |  | \ | /   \ | /   \ | /   \ |/  |
//    |  |  \|/  5  \|/ 16  \|/ 21  \|/  |
//  -5-  | 0 5-------6-------7-------8 18|
//    |  |  / \  4  / \ 14  / \ 19  / \  |
//    |  | /   \   /   \   /   \   /   \ |
//    |  |/  1  \ /  2  \ / 20  \ / 17  \|
// -10-  0-------1-------2-------3-------4
//
//       |-------|-------|-------|-------|
//       0      10      20      30      40
//
//  After removing triangles (*** means a hole)
//
//  10-  17-----18------19------20------21
//    |  |\  7  / \  9  /|\ 17  / \ 21  /
//    |  | \   /   \   / | \   /   \   /
//    |  |  \ / 10  \ /24|18\ / 22  \ /
//   5-  |6 13------14   |  15------16
//    |  |  /|******/|\  |  /|\ 20  /|
//    |  | / |*****/ | \ | /*| \   / |
//    |  |/  |****/  |  \|/**|19\ /23|
//   0-  9 11|**10  8|3 11***|  12   |
//    |  |\  |**/ \  |  /****|  / \  |
//    |  | \ |*/   \ | /*****| /   \ |
//    |  |  \|/  5  \|/******|/ 16  \|
//  -5-  | 0 5-------6-------7-------8
//    |  |  / \  4  / \ 12  / \ 14  / \
//    |  | /   \   /   \   /   \   /   \
//    |  |/  1  \ /  2  \ / 15  \ / 13  \
// -10-  0-------1-------2-------3-------4
//
//       |-------|-------|-------|-------|
//       0      10      20      30      40
/// \endverbatim
//------------------------------------------------------------------------------
void TrBreaklineAdderUnitTests::test2()
{
  // Set up tin
  BSHP<TrTin> tin = trBuildTestTin7();

  // Verify triangles before
  int trisB[] = {0,  5,  9,  5,  0,  1,  1,  2,  6,  14, 6,  11, 1,  6,  5,  5,  6,  10, 9,
                 13, 17, 13, 9,  10, 17, 13, 18, 10, 14, 18, 14, 10, 6,  18, 14, 19, 10, 18,
                 13, 9,  5,  10, 6,  2,  7,  12, 11, 7,  7,  11, 6,  3,  4,  8,  8,  4,  21,
                 3,  8,  7,  7,  2,  3,  12, 7,  8,  19, 15, 20, 15, 19, 11, 12, 15, 11, 15,
                 12, 16, 20, 16, 21, 16, 20, 15, 21, 16, 8,  12, 8,  16, 11, 19, 14};
  TS_ASSERT_EQUALS(VecInt(&trisB[0], &trisB[93]), tin->Triangles());

  // Set up polygons
  int outPolyA[] = {0, 1, 2, 3, 4, 8, 16, 21, 20, 19, 18, 17, 9};
  VecInt outPoly(&outPolyA[0], &outPolyA[13]);
  int inPoly1[] = {10, 5, 13, 14};
  int inPoly2[] = {6, 11, 15, 7};
  VecInt2d inPolys;
  inPolys.push_back(VecInt(&inPoly1[0], &inPoly1[4]));
  inPolys.push_back(VecInt(&inPoly2[0], &inPoly2[4]));

  // Add breaklines
  BSHP<TrBreaklineAdder> adder = TrBreaklineAdder::New();
  adder->SetTin(tin);
  adder->AddBreakline(outPoly);
  adder->AddBreaklines(inPolys);

  // Verify triangles after
  int trisA[] = {0,  5,  9,  5,  0,  1,  1,  2,  6,  14, 6,  11, 1,  6,  5,  5,  6,  10, 9,
                 13, 17, 13, 5,  10, 17, 13, 18, 10, 14, 13, 14, 10, 6,  18, 14, 19, 14, 18,
                 13, 9,  5,  13, 6,  2,  7,  15, 11, 7,  7,  11, 6,  3,  4,  8,  8,  4,  21,
                 3,  8,  7,  7,  2,  3,  12, 7,  8,  19, 15, 20, 15, 19, 11, 12, 15, 7,  15,
                 12, 16, 20, 16, 21, 16, 20, 15, 21, 16, 8,  12, 8,  16, 11, 19, 14};
  VecInt trisAfter(&trisA[0], &trisA[XM_COUNTOF(trisA)]);
  TS_ASSERT_EQUALS(trisAfter, tin->Triangles());

} // TrBreaklineAdderUnitTests::test2
//------------------------------------------------------------------------------
/// \brief Test a case involving crossing a hole and the outer boundary.
/// \verbatim
//
///  15.0        9----10----11
///             /|\ 10 | 11 /
///           /  |  \  |  /
///         /  8 | 9  \|/
///  10.0  6-----7-----8
///        |\  5 |\  6 |\
///        |  \  |  \  |  \
///        | 4  \|    \| 7  \
///   5.0  2-----3-----4-----5
///         \  0 |\  2 | 3  /
///           \  |  \  |  /
///             \| 1  \|/
///   0.0        0-----1
///
///      0.0   5.0   10.0  15.0
/// \endverbatim
//------------------------------------------------------------------------------
void TrBreaklineAdderUnitTests::testCrossingBoundary()
{
  try
  {
    BSHP<TrTin> tin = trBuildTestTin8();

    // Add breakline
    BSHP<TrBreaklineAdder> adder = TrBreaklineAdder::New();
    adder->SetTin(tin);

    // Copy triangles before
    VecInt tris = tin->Triangles();

    std::string errorMessage = adder->ErrorMessage(0);

    // Try to add a breakline that crosses the hole
    VecInt breakline = {3, 8};
    XmLog::Instance().GetAndClearStackStr();
    adder->AddBreakline(breakline);
    TS_ASSERT(XmLog::Instance().ErrCount() == 1);
    if (XmLog::Instance().ErrCount() > 0)
    {
      MessageStack messages = XmLog::Instance().GetAndClearStack();
      TS_ASSERT_EQUALS(messages[0].second, errorMessage);
    }
    TS_ASSERT_EQUALS(tris, tin->Triangles());

    // Try to add a breakline that crosses the concavity
    breakline = {4, 11};
    XmLog::Instance().GetAndClearStackStr();
    adder->AddBreakline(breakline);
    TS_ASSERT(XmLog::Instance().ErrCount() == 1);
    if (XmLog::Instance().ErrCount() > 0)
    {
      MessageStack messages = XmLog::Instance().GetAndClearStack();
      TS_ASSERT_EQUALS(messages[0].second, errorMessage);
    }
    TS_ASSERT_EQUALS(tris, tin->Triangles());

    // Try to add a breakline that crosses both inside and inner boundary
    breakline = {10, 7, 2, 8};
    XmLog::Instance().GetAndClearStackStr();
    adder->AddBreakline(breakline);
    TS_ASSERT(XmLog::Instance().ErrCount() == 1);
    if (XmLog::Instance().ErrCount() > 0)
    {
      MessageStack messages = XmLog::Instance().GetAndClearStack();
      TS_ASSERT_EQUALS(messages[0].second, errorMessage);
    }
    {
      int trisA[] = {0, 3, 2, 0, 1, 3, 1, 4, 3, 1, 5,  4, 2, 7,  6, 3, 7,  2,
                     4, 8, 7, 4, 5, 8, 6, 7, 9, 7, 10, 9, 8, 10, 7, 8, 11, 10};
      TS_ASSERT_EQUALS(VecInt(&trisA[0], &trisA[XM_COUNTOF(trisA)]), tin->Triangles());
    }

    // Try to add a breakline that crosses both inside and outer boundary
    breakline = {0, 4, 11};
    XmLog::Instance().GetAndClearStackStr();
    adder->AddBreakline(breakline);
    TS_ASSERT(XmLog::Instance().ErrCount() == 1);
    if (XmLog::Instance().ErrCount() > 0)
    {
      MessageStack messages = XmLog::Instance().GetAndClearStack();
      TS_ASSERT_EQUALS(messages[0].second, errorMessage);
    }
    {
      int trisA[] = {0, 3, 2, 0, 4, 3, 1, 4, 0, 1, 5,  4, 2, 7,  6, 3, 7,  2,
                     4, 8, 7, 4, 5, 8, 6, 7, 9, 7, 10, 9, 8, 10, 7, 8, 11, 10};
      TS_ASSERT_EQUALS(VecInt(&trisA[0], &trisA[XM_COUNTOF(trisA)]), tin->Triangles());
    }

    // Go around inner border
    breakline = {3, 4, 7, 8, 4, 3, 7};
    XmLog::Instance().GetAndClearStackStr();
    adder->AddBreakline(breakline);
    TS_ASSERT(XmLog::Instance().ErrCount() == 0);
    {
      int trisA[] = {0, 3, 2, 0, 4, 3, 1, 4, 0, 1, 5,  4, 2, 7,  6, 3, 7,  2,
                     4, 8, 7, 4, 5, 8, 6, 7, 9, 7, 10, 9, 8, 10, 7, 8, 11, 10};
      TS_ASSERT_EQUALS(VecInt(&trisA[0], &trisA[XM_COUNTOF(trisA)]), tin->Triangles());
    }

    XmLog::Instance().GetAndClearStackStr();
  }
  catch (std::exception&)
  {
    TS_FAIL("exception");
  }

} // TrBreaklineAdderUnitTests::testCrossingBoundary
//------------------------------------------------------------------------------
/// \brief Test forcing a breakline with two very skinny triangles.
//------------------------------------------------------------------------------
void TrBreaklineAdderUnitTests::testVerySkinnyTris()
{
  // Set up the tin
  BSHP<TrTin> tin = TrTin::New();
  BSHP<VecPt3d> points(new VecPt3d);
  *points = {{2260112.1313182, 1425642.6953098, 502.61074829102},
    {2260112.1083855, 1425642.6889503, 502.6106262207},
    {2260066.0105718, 1425772.98009, 494.3948059082},
    {2260063.7238376, 1425771.8543445, 493.07467651367}};
  tin->SetPoints(points);

  BSHP<VecInt> tris(new VecInt);
  *tris = {3, 0, 2, 3, 1, 0};
  tin->SetTriangles(tris);

  tin->BuildTrisAdjToPts();

  // Add breakline
  BSHP<TrBreaklineAdder> adder = TrBreaklineAdder::New();
  adder->SetTin(tin);
  // from top right to lower left.
  adder->AddBreakline({2, 1});

  // Verify triangles after
  VecInt newTris = tin->Triangles();
  VecInt expectedTris = {1, 0, 2, 3, 1, 2};
  TS_ASSERT_EQUALS(expectedTris, newTris);

} // TrBreaklineAdderUnitTests::testVerySkinnyTris
//------------------------------------------------------------------------------
/// \brief Test forcing a breakline with two very skinny triangles.
//------------------------------------------------------------------------------
void TrBreaklineAdderUnitTests::testForceBreaklineBug13951()
{
  BSHP<TrTin> tin = TrTin::New();
  tin->Points() = {
    {240.66, 1510.06, 0.0}, {329.41, 1509.95, 0.0}, {330.75, 1511.59, 0.0}, {332.43, 1510.88, 0.0},
    {333.08, 1510.67, 0.0}, {336.35, 1509.93, 0.0}, {347.06, 1510.59, 0.0}, {395.04, 1513.55, 0.0},
    {330.90, 1509.41, 0.0}, {369.92, 1451.04, 0.0}, {423.10, 1458.44, 0.0}, {399.21, 1455.09, 0.0},
    {369.47, 1450.71, 0.0}, {283.29, 1457.97, 0.0}, {346.22, 1474.37, 0.0}, {336.10, 1498.59, 0.0},
    {336.88, 1498.90, 0.0}
  };
  TrTriangulatorPoints client(tin->Points(), tin->Triangles(), &tin->TrisAdjToPts());
  bool rv = client.Triangulate();

  // Add breakline
  BSHP<TrBreaklineAdder> adder = TrBreaklineAdder::New();
  adder->SetTin(tin);
  VecInt breakLine = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 0};
  adder->AddBreakline(breakLine);
  VecInt baseTris = {13, 1,  0,  1,  13, 15, 4,  8,  5, 15, 8,  1,  13, 14, 15, 1,  8,
                     2,  0,  2,  7,  0,  1,  2,  3,  4, 2,  2,  8,  3,  8,  4,  3,  2,
                     4,  5,  8,  6,  5,  12, 9,  14, 9, 12, 11, 9,  10, 7,  10, 11, 12,
                     9,  11, 10, 15, 16, 8,  6,  8,  7, 9,  8,  16, 16, 14, 9,  7,  2,
                     6,  7,  8,  9,  16, 15, 14, 6,  2, 5,  12, 14, 13};
  TS_ASSERT_EQUALS(baseTris, tin->Triangles());
} // TrBreaklineAdderUnitTests::testForceBreaklineBug13951
//------------------------------------------------------------------------------
/// \brief Test forcing a breakline with two very skinny triangles.
//------------------------------------------------------------------------------
void TrBreaklineAdderUnitTests::testForceBreaklineBug14095()
{
  BSHP<TrTin> tin = TrTin::New();
  tin->Points() = {
    {368631.60307407, 4054926.1087416, 0.0}, {368641.14, 4055088.48, 0.0},
    {368788.05741829, 4055093.8780732, 0.0}, {368801.93750472, 4055031.4021071, 0.0},
    {368700.9467262, 4055005.8666216, 0.0},  {368722.26076012, 4054908.6649129, 0.0},
    {368677.64946168, 4054917.2487615, 0.0}, {368654.48, 4054950.97, 0.0},
    {368672.77161426, 4054918.1873287, 0.0}, {368659.25312515, 4055005.1071713, 0.0},
    {368689.76987238, 4054961.9504233, 0.0}, {368664.47053169, 4054981.7580834, 0.0}
  };
  TrTriangulatorPoints client(tin->Points(), tin->Triangles(), &tin->TrisAdjToPts());
  bool rv = client.Triangulate();

  // Add breakline
  BSHP<TrBreaklineAdder> adder = TrBreaklineAdder::New();
  adder->SetTin(tin);
  VecInt breakLine = {0, 1, 2, 3, 4, 5, 6, 7, 8, 0};
  adder->AddBreakline(breakLine);
  VecInt baseTris = {0,  8, 7, 11, 7,  10, 0, 7,  9, 4,  1, 9, 9, 1, 0, 11, 9, 7, 4, 9, 11, 7, 6,
                     10, 6, 5, 10, 10, 5,  4, 10, 4, 11, 4, 3, 2, 3, 4, 5,  4, 2, 1, 7, 8,  6};
  TS_ASSERT_EQUALS(baseTris, tin->Triangles());
} // TrBreaklineAdderUnitTests::testForceBreaklineBug13951

  //} // namespace xms

#endif
