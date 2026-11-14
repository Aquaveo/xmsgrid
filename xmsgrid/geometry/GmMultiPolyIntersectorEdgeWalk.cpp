//------------------------------------------------------------------------------
/// \file
/// \ingroup geometry
/// \copyright (C) Copyright Aquaveo 2018. Distributed under FreeBSD License
/// (See accompanying file LICENSE or https://aqaveo.com/bsd/license.txt)
//------------------------------------------------------------------------------

//----- Included files ---------------------------------------------------------

// 1. Precompiled header

// 2. My own header
#include <xmsgrid/geometry/GmMultiPolyIntersectorEdgeWalk.h>

// 3. Standard library headers
#include <algorithm>
#include <cmath>
#include <limits>
#include <memory>
#include <stdexcept>

// 4. External library headers
#pragma warning(push)
#pragma warning(disable : 4512)
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/polygon.hpp>
#include <boost/geometry/index/rtree.hpp>
#pragma warning(pop)

// 5. Shared code headers
#include <xmscore/math/math.h>
#include <xmscore/misc/XmConst.h>
#include <xmscore/misc/XmError.h>
#include <xmscore/misc/xmstype.h>
#include <xmscore/points/pt.h>
#include <xmscore/stl/vector.h>
#include <xmsgrid/geometry/GmBoostTypes.h>
#include <xmsgrid/geometry/detail/GmMultiPolyIntersectorCommon.h>
#include <xmsgrid/geometry/geoms.h>
#include <xmsgrid/ugrid/XmEdge.h>
#include <xmsgrid/ugrid/XmUGrid.h>

//----- Forward declarations ---------------------------------------------------

namespace bg = boost::geometry;
namespace bgi = boost::geometry::index;

//----- Namespace declaration --------------------------------------------------

namespace xms
{
//----- Constants / Enumerations -----------------------------------------------

typedef std::pair<GmBstBox3d, int> ValueBox;
typedef bgi::rtree<ValueBox, bgi::quadratic<8>> RtreeBox;

namespace // unnamed namespace
{
//------------------------------------------------------------------------------
/// \brief Query an R-tree for the boxes that meet a geometry.
/// \param a_rtree: The R-tree.
/// \param a_geometry: What the boxes must meet.
/// \return The boxes, lowest cell index first, so that a choice between cells
///         does not depend on the R-tree's order.
//------------------------------------------------------------------------------
template <typename Geometry>
std::vector<ValueBox> iQueryInCellOrder(const RtreeBox& a_rtree, const Geometry& a_geometry)
{
  std::vector<ValueBox> result;
  a_rtree.query(bgi::intersects(a_geometry), std::back_inserter(result));
  std::sort(result.begin(), result.end(), [](const ValueBox& a_lhs, const ValueBox& a_rhs) {
    return a_lhs.second < a_rhs.second;
  });
  return result;
} // iQueryInCellOrder
} // unnamed namespace

//----- Classes / Structs ------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
/// \brief Private implementation for GmMultiPolyIntersectorEdgeWalk.
////////////////////////////////////////////////////////////////////////////////
class GmMultiPolyIntersectorEdgeWalk::Impl
{
public:
  Impl(std::shared_ptr<XmUGrid> a_ugrid, int a_startingId);

  void SetQuery(GmMultiPolyIntersectorQueryEnum a_query);
  void TraverseLineSegment(double a_x1,
                           double a_y1,
                           double a_x2,
                           double a_y2,
                           VecInt& a_polyIds,
                           VecDbl& a_tValues,
                           VecPt3d& a_pts);
  int PolygonFromPoint(const Pt3d& a_pt) const;

private:
  GmBstPoly3d CellPolygon(int a_cellIdx) const;
  int PointInCell(int a_cellIdx, const Pt3d& a_pt) const;
  bool CellHoldsPoint(int a_cellIdx, const Pt3d& a_pt) const;
  bool IsSharedPoint(int a_cellIdx, const Pt3d& a_pt) const;
  GmBstBox3d ToleranceBox(const Pt3d& a_pt) const;
  double TEps(double a_segLen) const;
  bool SegmentT(const Pt3d& a_pt1,
                const Pt3d& a_pt2,
                const Pt3d& a_pt,
                double a_tEps,
                double& a_t) const;
  bool CellOnRightOfLine(int a_cellIdx,
                         const Pt3d& a_pt1,
                         const Pt3d& a_pt2,
                         const Pt3d& a_pt) const;
  int CellEnteredAfter(const VecInt& a_cells,
                       const Pt3d& a_pt1,
                       const Pt3d& a_pt2,
                       double a_t) const;
  int FindStartCell(const Pt3d& a_pt1, const Pt3d& a_pt2) const;
  int FindCellContainingPoint(const Pt3d& a_pt) const;
  bool FindExitEdge(int a_cellIdx,
                    const Pt3d& a_pt1,
                    const Pt3d& a_pt2,
                    double a_currentT,
                    int& a_exitEdgeIdx,
                    Pt3d& a_exitPt,
                    double& a_exitT,
                    int& a_hitVertexIdx) const;
  int ResolveVertexCrossing(int a_vertexIdx,
                            const Pt3d& a_pt1,
                            const Pt3d& a_pt2,
                            double a_t,
                            int a_prevCell,
                            int a_currentCell) const;
  bool FindFirstMeshEntry(const Pt3d& a_pt1,
                          const Pt3d& a_pt2,
                          double a_afterT,
                          int a_leftCell,
                          int& a_cellIdx,
                          Pt3d& a_entryPt,
                          double& a_entryT) const;
  void RemoveZeroLengthStretches(double a_tEps,
                                 VecInt& a_polyIds,
                                 VecDbl& a_tValues,
                                 VecPt3d& a_pts) const;
  void BuildRTree();
  void CalculateBuffer();
  void BufferTheBox(GmBstBox3d& a_box) const;
  void OffsetPolyIds(VecInt& a_polyIds) const;

  std::shared_ptr<XmUGrid> m_ugrid;        ///< The grid whose cells are walked
  std::unique_ptr<RtreeBox> m_rtree;       ///< Buffered extents of the cells
  int m_startingId;                        ///< Id of the grid's first cell
  double m_buffer;                         ///< Distance the R-tree boxes are grown by
  double m_xyTol;                          ///< xy tolerance for this grid
  int m_maxIterations;                     ///< Most passes a traversal can need
  GmMultiPolyIntersectorQueryEnum m_query; ///< Point query: covered by or intersects
};

//----- Class / Function definitions -------------------------------------------

////////////////////////////////////////////////////////////////////////////////
/// \class GmMultiPolyIntersectorEdgeWalk
/// \brief Edge-walk based multi-polygon intersector using XmUGrid adjacency.
////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
/// \brief Constructor.
/// \param a_ugrid: The unstructured grid. Every cell must be 2D.
/// \param a_startingId: Id of the grid's first cell.
/// \throw std::invalid_argument if a_ugrid is null or has a cell that is not
///        2D.
//------------------------------------------------------------------------------
GmMultiPolyIntersectorEdgeWalk::GmMultiPolyIntersectorEdgeWalk(std::shared_ptr<XmUGrid> a_ugrid,
                                                               int a_startingId)
: m_impl(new Impl(a_ugrid, a_startingId))
{
}
//------------------------------------------------------------------------------
/// \brief Destructor.
//------------------------------------------------------------------------------
GmMultiPolyIntersectorEdgeWalk::~GmMultiPolyIntersectorEdgeWalk() = default;
//------------------------------------------------------------------------------
/// \brief Set the query type.
/// \param a_query: GmMultiPolyIntersectorQueryEnum
//------------------------------------------------------------------------------
void GmMultiPolyIntersectorEdgeWalk::SetQuery(GmMultiPolyIntersectorQueryEnum a_query)
{
  m_impl->SetQuery(a_query);
}
//------------------------------------------------------------------------------
/// \brief Traverse line segment — polyIds + tValues overload.
//------------------------------------------------------------------------------
void GmMultiPolyIntersectorEdgeWalk::TraverseLineSegment(double a_x1,
                                                         double a_y1,
                                                         double a_x2,
                                                         double a_y2,
                                                         VecInt& a_polyIds,
                                                         VecDbl& a_tValues)
{
  VecPt3d pts;
  m_impl->TraverseLineSegment(a_x1, a_y1, a_x2, a_y2, a_polyIds, a_tValues, pts);
}
//------------------------------------------------------------------------------
/// \brief Traverse line segment — polyIds only overload.
//------------------------------------------------------------------------------
void GmMultiPolyIntersectorEdgeWalk::TraverseLineSegment(double a_x1,
                                                         double a_y1,
                                                         double a_x2,
                                                         double a_y2,
                                                         VecInt& a_polyIds)
{
  VecDbl tValues;
  VecPt3d pts;
  m_impl->TraverseLineSegment(a_x1, a_y1, a_x2, a_y2, a_polyIds, tValues, pts);
}
//------------------------------------------------------------------------------
/// \brief Traverse line segment — polyIds + pts overload.
//------------------------------------------------------------------------------
void GmMultiPolyIntersectorEdgeWalk::TraverseLineSegment(double a_x1,
                                                         double a_y1,
                                                         double a_x2,
                                                         double a_y2,
                                                         VecInt& a_polyIds,
                                                         VecPt3d& a_pts)
{
  VecDbl tValues;
  m_impl->TraverseLineSegment(a_x1, a_y1, a_x2, a_y2, a_polyIds, tValues, a_pts);
}
//------------------------------------------------------------------------------
/// \brief Traverse line segment — full overload with polyIds, tValues, pts.
//------------------------------------------------------------------------------
void GmMultiPolyIntersectorEdgeWalk::TraverseLineSegment(double a_x1,
                                                         double a_y1,
                                                         double a_x2,
                                                         double a_y2,
                                                         VecInt& a_polyIds,
                                                         VecDbl& a_tValues,
                                                         VecPt3d& a_pts)
{
  m_impl->TraverseLineSegment(a_x1, a_y1, a_x2, a_y2, a_polyIds, a_tValues, a_pts);
}
//------------------------------------------------------------------------------
/// \brief Find polygon containing a point.
/// \param a_pt: Point location.
/// \return Id of the cell holding the point, counted from the starting id, or
///         XM_NONE.
//------------------------------------------------------------------------------
int GmMultiPolyIntersectorEdgeWalk::PolygonFromPoint(const Pt3d& a_pt)
{
  return m_impl->PolygonFromPoint(a_pt);
}

////////////////////////////////////////////////////////////////////////////////
// Impl
////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
/// \brief Constructor for Impl.
/// \param a_ugrid: The unstructured grid. Every cell must be 2D.
/// \param a_startingId: Id of the grid's first cell.
/// \throw std::invalid_argument if a_ugrid is null or has a cell that is not
///        2D.
//------------------------------------------------------------------------------
GmMultiPolyIntersectorEdgeWalk::Impl::Impl(std::shared_ptr<XmUGrid> a_ugrid, int a_startingId)
: m_ugrid(a_ugrid)
, m_startingId(a_startingId)
, m_buffer(0.0)
, m_xyTol(1e-9)
, m_maxIterations(0)
, m_query(GMMPIQ_COVEREDBY)
{
  if (!m_ugrid)
    throw std::invalid_argument("GmMultiPolyIntersector needs a grid");
  int edgeCount = 0;
  for (int cellIdx = 0; cellIdx < m_ugrid->GetCellCount(); ++cellIdx)
  {
    if (m_ugrid->GetCellDimension(cellIdx) != 2)
      throw std::invalid_argument("GmMultiPolyIntersector needs a grid of 2D cells");
    edgeCount += m_ugrid->GetCellEdgeCount(cellIdx);
  }
  // A segment meets an edge at no more than two points. Each pass of the walk
  // moves to a later one, or into another cell at the same point; the pass
  // after that moves on.
  m_maxIterations = 4 * edgeCount + 2;
  CalculateBuffer();
  BuildRTree();
}
//------------------------------------------------------------------------------
/// \brief Set the query type.
//------------------------------------------------------------------------------
void GmMultiPolyIntersectorEdgeWalk::Impl::SetQuery(GmMultiPolyIntersectorQueryEnum a_query)
{
  m_query = a_query;
}
//------------------------------------------------------------------------------
/// \brief Calculate buffer and tolerance from grid extents.
//------------------------------------------------------------------------------
void GmMultiPolyIntersectorEdgeWalk::Impl::CalculateBuffer()
{
  Pt3d mn, mx;
  m_ugrid->GetExtents(mn, mx);
  const double kFraction = 1e-5;
  m_buffer = gmXyDistance(mn, mx) * kFraction;
  m_xyTol = gmComputeXyTol(mn, mx);
}
//------------------------------------------------------------------------------
/// \brief Expand bounding box by buffer.
//------------------------------------------------------------------------------
void GmMultiPolyIntersectorEdgeWalk::Impl::BufferTheBox(GmBstBox3d& a_box) const
{
  a_box.min_corner().x -= m_buffer;
  a_box.min_corner().y -= m_buffer;
  a_box.max_corner().x += m_buffer;
  a_box.max_corner().y += m_buffer;
}
//------------------------------------------------------------------------------
/// \brief Build an R-tree from cell bounding boxes.
//------------------------------------------------------------------------------
void GmMultiPolyIntersectorEdgeWalk::Impl::BuildRTree()
{
  std::vector<ValueBox> boxen;
  int cellCount = m_ugrid->GetCellCount();
  boxen.reserve(cellCount);
  for (int i = 0; i < cellCount; ++i)
  {
    Pt3d mn, mx;
    m_ugrid->GetCellExtents(i, mn, mx);
    GmBstBox3d box(mn, mx);
    BufferTheBox(box);
    boxen.push_back(std::make_pair(box, i));
  }
  m_rtree = std::make_unique<RtreeBox>(boxen.begin(), boxen.end());
}
//------------------------------------------------------------------------------
/// \brief Offset polygon IDs if startingId != 1.
//------------------------------------------------------------------------------
void GmMultiPolyIntersectorEdgeWalk::Impl::OffsetPolyIds(VecInt& a_polyIds) const
{
  if (m_startingId != 1)
  {
    int offset = m_startingId - 1;
    for (int i = 0; i < (int)a_polyIds.size(); ++i)
    {
      if (a_polyIds[i] != -1 && a_polyIds[i] != XM_NONE)
      {
        a_polyIds[i] += offset;
      }
    }
  }
}
//------------------------------------------------------------------------------
/// \brief Build the boost polygon of a cell.
/// \param a_cellIdx: 0-based cell index.
/// \return The cell's outline, closed.
//------------------------------------------------------------------------------
GmBstPoly3d GmMultiPolyIntersectorEdgeWalk::Impl::CellPolygon(int a_cellIdx) const
{
  VecPt3d cellLocs;
  m_ugrid->GetCellLocations(a_cellIdx, cellLocs);
  GmBstPoly3d poly;
  for (const Pt3d& pt : cellLocs)
    bg::exterior_ring(poly).push_back(pt);
  if (!cellLocs.empty())
    bg::exterior_ring(poly).push_back(cellLocs[0]);
  return poly;
}
//------------------------------------------------------------------------------
/// \brief Locate a point relative to a cell, within m_xyTol.
/// \param a_cellIdx: 0-based cell index.
/// \param a_pt: The point.
/// \return 1 if the point is inside the cell, 0 if on its boundary, -1 if
///         outside.
//------------------------------------------------------------------------------
int GmMultiPolyIntersectorEdgeWalk::Impl::PointInCell(int a_cellIdx, const Pt3d& a_pt) const
{
  VecPt3d cellLocs;
  m_ugrid->GetCellLocations(a_cellIdx, cellLocs);
  if (cellLocs.empty())
    return -1;
  return gmPointInPolygon2D(&cellLocs[0], cellLocs.size(), a_pt.x, a_pt.y, m_xyTol);
}
//------------------------------------------------------------------------------
/// \brief Whether a point is inside a cell or on its boundary.
/// \param a_cellIdx: 0-based cell index.
/// \param a_pt: The point.
/// \return true if the cell holds the point.
//------------------------------------------------------------------------------
bool GmMultiPolyIntersectorEdgeWalk::Impl::CellHoldsPoint(int a_cellIdx, const Pt3d& a_pt) const
{ return PointInCell(a_cellIdx, a_pt) >= 0; }
//------------------------------------------------------------------------------
/// \brief Whether a cell other than a given one holds a point.
///
/// Decided by location, not by point index, so cells that meet at coincident
/// copies of a point share it as cells that use the same point do.
/// \param a_cellIdx: 0-based index of the cell to leave out.
/// \param a_pt: The point.
/// \return true if another cell holds a_pt, inside or on its boundary.
//------------------------------------------------------------------------------
bool GmMultiPolyIntersectorEdgeWalk::Impl::IsSharedPoint(int a_cellIdx, const Pt3d& a_pt) const
{
  for (const ValueBox& vb : iQueryInCellOrder(*m_rtree, ToleranceBox(a_pt)))
  {
    if (vb.second != a_cellIdx && CellHoldsPoint(vb.second, a_pt))
      return true;
  }
  return false;
}
//------------------------------------------------------------------------------
/// \brief The box within m_xyTol of a point.
/// \param a_pt: The point.
/// \return The box. Every cell whose boundary passes within m_xyTol of a_pt
///         has an R-tree box that meets it, even where m_xyTol is larger than
///         m_buffer.
//------------------------------------------------------------------------------
GmBstBox3d GmMultiPolyIntersectorEdgeWalk::Impl::ToleranceBox(const Pt3d& a_pt) const
{
  return GmBstBox3d(Pt3d(a_pt.x - m_xyTol, a_pt.y - m_xyTol, 0.0),
                    Pt3d(a_pt.x + m_xyTol, a_pt.y + m_xyTol, 0.0));
}
//------------------------------------------------------------------------------
/// \brief Convert m_xyTol to a tolerance on the t-values of a segment.
/// \param a_segLen: Length of the segment.
/// \return The t tolerance.
//------------------------------------------------------------------------------
double GmMultiPolyIntersectorEdgeWalk::Impl::TEps(double a_segLen) const
{
  double tEps = (a_segLen > 1e-30) ? (m_xyTol / a_segLen) : 1e-10;
  return std::max(tEps, 1e-12);
}
//------------------------------------------------------------------------------
/// \brief Find the t-value of a point on a segment, clamped to [0, 1].
/// \param a_pt1: Segment start.
/// \param a_pt2: Segment end.
/// \param a_pt: A point on the segment's line.
/// \param a_tEps: t tolerance for the segment.
/// \param a_t: [out] The t-value.
/// \return false if the point is past either end by more than a_tEps.
//------------------------------------------------------------------------------
bool GmMultiPolyIntersectorEdgeWalk::Impl::SegmentT(const Pt3d& a_pt1,
                                                    const Pt3d& a_pt2,
                                                    const Pt3d& a_pt,
                                                    double a_tEps,
                                                    double& a_t) const
{
  a_t = gmPtDistanceAlongSegment(a_pt1, a_pt2, a_pt, m_xyTol);
  if (a_t < -a_tEps || a_t > 1.0 + a_tEps)
    return false;
  a_t = std::min(std::max(a_t, 0.0), 1.0);
  return true;
}
//------------------------------------------------------------------------------
/// \brief Whether a cell lies on the right of a line that runs along one of
///        its edges.
/// \param a_cellIdx: 0-based cell index.
/// \param a_pt1: Line segment start.
/// \param a_pt2: Line segment end.
/// \param a_pt: A point where the line runs along the cell's boundary.
/// \return true if the cell's interior is on the line's right at a_pt.
//------------------------------------------------------------------------------
bool GmMultiPolyIntersectorEdgeWalk::Impl::CellOnRightOfLine(int a_cellIdx,
                                                             const Pt3d& a_pt1,
                                                             const Pt3d& a_pt2,
                                                             const Pt3d& a_pt) const
{
  VecPt3d cellLocs;
  m_ugrid->GetCellLocations(a_cellIdx, cellLocs);
  size_t pointCount = cellLocs.size();
  if (pointCount < 3)
    return false;
  // A cell's interior is on the left of its edges where they run
  // counterclockwise, and on their right where they run clockwise.
  bool counterclockwise = gmPolygonArea(&cellLocs[0], pointCount) > 0.0;
  double dx = a_pt2.x - a_pt1.x;
  double dy = a_pt2.y - a_pt1.y;
  for (size_t i = 0; i < pointCount; ++i)
  {
    const Pt3d& edgePt1 = cellLocs[i];
    const Pt3d& edgePt2 = cellLocs[(i + 1) % pointCount];
    if (!gmOnLineAndBetweenEndpointsWithTol(edgePt1, edgePt2, a_pt.x, a_pt.y, m_xyTol))
      continue;
    bool sameDirection = (edgePt2.x - edgePt1.x) * dx + (edgePt2.y - edgePt1.y) * dy > 0.0;
    return sameDirection != counterclockwise;
  }
  return false;
}
//------------------------------------------------------------------------------
/// \brief Pick the cell a segment goes into just past a point on it.
///
/// Up to the next point where the segment meets a cell's boundary, the segment
/// is inside the cell, outside it, or along its boundary all the way. The
/// middle of that stretch says which. A cell the segment goes into wins. Where
/// the segment runs along an edge, the cell on its right wins, as in the
/// sorter-based implementation. Failing both, the first cell the segment runs
/// along: the segment runs along the edge of the mesh with the mesh on its
/// left.
/// \param a_cells: Candidate cells, in order of preference.
/// \param a_pt1: Segment start.
/// \param a_pt2: Segment end.
/// \param a_t: t-value of the point.
/// \return The cell the segment goes into, or -1 if it goes into none of them
///         or ends at a_t.
//------------------------------------------------------------------------------
int GmMultiPolyIntersectorEdgeWalk::Impl::CellEnteredAfter(const VecInt& a_cells,
                                                           const Pt3d& a_pt1,
                                                           const Pt3d& a_pt2,
                                                           double a_t) const
{
  const double tEps = TEps(gmXyDistance(a_pt1, a_pt2));
  int along = -1;      // the first cell the segment runs along
  int alongRight = -1; // the first of those on the segment's right
  for (int cellIdx : a_cells)
  {
    int edgeIdx, vertexIdx;
    Pt3d nextPt;
    double nextT;
    if (!FindExitEdge(cellIdx, a_pt1, a_pt2, a_t, edgeIdx, nextPt, nextT, vertexIdx))
      nextT = 1.0;
    if (nextT <= a_t + tEps)
      continue; // the segment ends at a_t
    double midT = 0.5 * (a_t + nextT);
    Pt3d midPt(a_pt1.x + midT * (a_pt2.x - a_pt1.x), a_pt1.y + midT * (a_pt2.y - a_pt1.y), 0.0);
    int inCell = PointInCell(cellIdx, midPt);
    if (inCell > 0)
      return cellIdx;
    if (inCell < 0)
      continue;
    if (along == -1)
      along = cellIdx;
    if (alongRight == -1 && CellOnRightOfLine(cellIdx, a_pt1, a_pt2, midPt))
      alongRight = cellIdx;
  }
  return alongRight != -1 ? alongRight : along;
}
//------------------------------------------------------------------------------
/// \brief Find the cell a segment starts in.
/// \param a_pt1: Segment start.
/// \param a_pt2: Segment end.
/// \return 0-based index of the cell holding a_pt1 that the segment goes into.
///         If the segment goes into none of the cells holding a_pt1, the first
///         of them; -1 if no cell holds a_pt1.
//------------------------------------------------------------------------------
int GmMultiPolyIntersectorEdgeWalk::Impl::FindStartCell(const Pt3d& a_pt1, const Pt3d& a_pt2) const
{
  VecInt candidates; // cells holding a_pt1, within m_xyTol
  for (const ValueBox& vb : iQueryInCellOrder(*m_rtree, a_pt1))
  {
    if (CellHoldsPoint(vb.second, a_pt1))
      candidates.push_back(vb.second);
  }
  if (candidates.size() <= 1)
    return candidates.empty() ? -1 : candidates[0];

  // a_pt1 is on a boundary that several cells share.
  int cellIdx = CellEnteredAfter(candidates, a_pt1, a_pt2, 0.0);
  return cellIdx != -1 ? cellIdx : candidates[0];
}
//------------------------------------------------------------------------------
/// \brief Find the cell containing a point using R-tree + point-in-polygon.
/// \param a_pt: The point to locate.
/// \return 0-based index of the cell holding the point, or -1 if none does.
///         Where several cells do (the point is on an edge or vertex they
///         share), the lowest, as in the sorter-based implementation.
//------------------------------------------------------------------------------
int GmMultiPolyIntersectorEdgeWalk::Impl::FindCellContainingPoint(const Pt3d& a_pt) const
{
  for (const ValueBox& vb : iQueryInCellOrder(*m_rtree, a_pt))
  {
    GmBstPoly3d poly = CellPolygon(vb.second);
    bool inside = false;
    switch (m_query)
    {
    case GMMPIQ_COVEREDBY:
      inside = bg::covered_by(a_pt, poly);
      break;
    case GMMPIQ_INTERSECTS:
      inside = bg::intersects(a_pt, poly);
      break;
    default:
      XM_ASSERT(false);
      break;
    }
    if (inside)
      return vb.second;
  }
  return -1;
}
//------------------------------------------------------------------------------
/// \brief Find where the line exits the current cell.
/// \param a_cellIdx: Current cell index.
/// \param a_pt1: Line segment start.
/// \param a_pt2: Line segment end.
/// \param a_currentT: Current t-value position along the line (avoid going backward).
/// \param a_exitEdgeIdx: [out] Edge index within the cell that the line exits through.
/// \param a_exitPt: [out] The exit point.
/// \param a_exitT: [out] t-value of the exit point along the line.
/// \param a_hitVertexIdx: [out] Vertex index if exit is at a vertex, or -1.
/// \return true if an exit edge was found.
//------------------------------------------------------------------------------
bool GmMultiPolyIntersectorEdgeWalk::Impl::FindExitEdge(int a_cellIdx,
                                                        const Pt3d& a_pt1,
                                                        const Pt3d& a_pt2,
                                                        double a_currentT,
                                                        int& a_exitEdgeIdx,
                                                        Pt3d& a_exitPt,
                                                        double& a_exitT,
                                                        int& a_hitVertexIdx) const
{
  a_exitEdgeIdx = -1;
  a_hitVertexIdx = -1;
  a_exitT = std::numeric_limits<double>::max();

  const double tEps = TEps(gmXyDistance(a_pt1, a_pt2));
  int edgeCount = m_ugrid->GetCellEdgeCount(a_cellIdx);
  for (int e = 0; e < edgeCount; ++e)
  {
    XmEdge edge = m_ugrid->GetCellEdge(a_cellIdx, e);
    Pt3d edgePt1 = m_ugrid->GetPointLocation(edge.GetFirst());
    Pt3d edgePt2 = m_ugrid->GetPointLocation(edge.GetSecond());

    VecPt3d intersections;
    gmLineSegmentIntersections(a_pt1, a_pt2, edgePt1, edgePt2, intersections, m_xyTol);

    for (const Pt3d& ixPt : intersections)
    {
      // Only the nearest point strictly ahead of the current position counts.
      double t;
      if (!SegmentT(a_pt1, a_pt2, ixPt, tEps, t) || t <= a_currentT + tEps || t >= a_exitT)
        continue;

      a_exitT = t;
      a_exitPt = ixPt;
      a_exitEdgeIdx = e;
      a_hitVertexIdx = -1;
      if (gmEqualPointsXY(ixPt, edgePt1, m_xyTol))
        a_hitVertexIdx = edge.GetFirst();
      else if (gmEqualPointsXY(ixPt, edgePt2, m_xyTol))
        a_hitVertexIdx = edge.GetSecond();
    }
  }
  return a_exitEdgeIdx != -1;
}
//------------------------------------------------------------------------------
/// \brief Resolve which cell the line goes into when it crosses a vertex.
/// \param a_vertexIdx: The vertex.
/// \param a_pt1: Line segment start.
/// \param a_pt2: Line segment end.
/// \param a_t: t-value of the vertex on the line.
/// \param a_prevCell: The cell the walk was in before the current one, or -1.
/// \param a_currentCell: The cell the walk is in.
/// \return 0-based index of the cell the line goes into, or -1 if it leaves the
///         mesh or ends at the vertex. It is a_currentCell when the line only
///         touches the vertex and stays in the cell.
//------------------------------------------------------------------------------
int GmMultiPolyIntersectorEdgeWalk::Impl::ResolveVertexCrossing(int a_vertexIdx,
                                                                const Pt3d& a_pt1,
                                                                const Pt3d& a_pt2,
                                                                double a_t,
                                                                int a_prevCell,
                                                                int a_currentCell) const
{
  // The cells the walk has not been in come first, so that where
  // CellEnteredAfter has nothing else to go on, the walk moves on.
  VecInt adjCells = m_ugrid->GetPointAdjacentCells(a_vertexIdx);
  VecInt candidates;
  for (int cellIdx : adjCells)
  {
    if (cellIdx != a_prevCell && cellIdx != a_currentCell)
      candidates.push_back(cellIdx);
  }
  for (int cellIdx : {a_prevCell, a_currentCell})
  {
    if (std::find(adjCells.begin(), adjCells.end(), cellIdx) != adjCells.end())
      candidates.push_back(cellIdx);
  }
  return CellEnteredAfter(candidates, a_pt1, a_pt2, a_t);
}
//------------------------------------------------------------------------------
/// \brief Find where a line next meets the mesh from outside.
///
/// Where the line has just left a cell at a_afterT, another cell can meet the
/// line at that same point: a cell narrower than the tolerance, or a cell that
/// meets the one left only at coincident copies of its points. If the line
/// goes into such a cell, that is where it meets the mesh.
/// \param a_pt1: Line segment start.
/// \param a_pt2: Line segment end.
/// \param a_afterT: t-value where the line left the mesh; other than at that
///        point, only points past it count. Negative to count every point.
/// \param a_leftCell: The cell the line left at a_afterT, or -1.
/// \param a_cellIdx: [out] Cell the line meets.
/// \param a_entryPt: [out] Point where it meets the cell's boundary.
/// \param a_entryT: [out] t-value of that point.
/// \return true if the line meets the mesh again.
//------------------------------------------------------------------------------
bool GmMultiPolyIntersectorEdgeWalk::Impl::FindFirstMeshEntry(const Pt3d& a_pt1,
                                                              const Pt3d& a_pt2,
                                                              double a_afterT,
                                                              int a_leftCell,
                                                              int& a_cellIdx,
                                                              Pt3d& a_entryPt,
                                                              double& a_entryT) const
{
  // The points where the line meets the boundaries of the cells in a_boxes,
  // from a_afterT on, other than where the cell it left meets it at a_afterT.
  struct Hit
  {
    double t;
    int cellIdx;
    Pt3d pt;
  };
  const double tEps = TEps(gmXyDistance(a_pt1, a_pt2));
  std::vector<Hit> hits;
  auto addHits = [&](const std::vector<ValueBox>& a_boxes) {
    for (const ValueBox& vb : a_boxes)
    {
      int cellIdx = vb.second;
      int edgeCount = m_ugrid->GetCellEdgeCount(cellIdx);
      for (int e = 0; e < edgeCount; ++e)
      {
        XmEdge edge = m_ugrid->GetCellEdge(cellIdx, e);
        Pt3d edgePt1 = m_ugrid->GetPointLocation(edge.GetFirst());
        Pt3d edgePt2 = m_ugrid->GetPointLocation(edge.GetSecond());

        VecPt3d intersections;
        gmLineSegmentIntersections(a_pt1, a_pt2, edgePt1, edgePt2, intersections, m_xyTol);
        for (const Pt3d& ixPt : intersections)
        {
          double t;
          if (!SegmentT(a_pt1, a_pt2, ixPt, tEps, t))
            continue;
          bool ahead = t > a_afterT + tEps;
          bool atLeftPoint = !ahead && t >= a_afterT - tEps && cellIdx != a_leftCell;
          if (ahead || atLeftPoint)
            hits.push_back({t, cellIdx, ixPt});
        }
      }
    }
  };

  // The cells that meet the line within tEps of a_t, past a_minT, and the
  // point of the first hit among them.
  auto cellsAt = [&](double a_t, double a_minT, Pt3d& a_pt) {
    VecInt cells;
    for (const Hit& hit : hits)
    {
      if (std::fabs(hit.t - a_t) > tEps || hit.t <= a_minT)
        continue;
      if (cells.empty())
        a_pt = hit.pt;
      if (std::find(cells.begin(), cells.end(), hit.cellIdx) == cells.end())
        cells.push_back(hit.cellIdx);
    }
    return cells;
  };

  if (a_afterT >= 0.0)
  {
    // Only a cell within m_xyTol of the point where the line left can take
    // over there, so search around that point before the rest of the line.
    Pt3d leftPt(a_pt1.x + a_afterT * (a_pt2.x - a_pt1.x), a_pt1.y + a_afterT * (a_pt2.y - a_pt1.y),
                0.0);
    addHits(iQueryInCellOrder(*m_rtree, ToleranceBox(leftPt)));
    Pt3d pt;
    VecInt cells = cellsAt(a_afterT, -1.0, pt);
    int entered = cells.empty() ? -1 : CellEnteredAfter(cells, a_pt1, a_pt2, a_afterT);
    if (entered != -1)
    {
      a_cellIdx = entered;
      a_entryPt = pt;
      a_entryT = a_afterT;
      return true;
    }
    hits.clear();
  }

  // Search the cells whose boxes meet the rest of the line.
  double startT = std::max(a_afterT, 0.0);
  GmBstLine3d line;
  line.push_back(
    Pt3d(a_pt1.x + startT * (a_pt2.x - a_pt1.x), a_pt1.y + startT * (a_pt2.y - a_pt1.y), 0.0));
  line.push_back(a_pt2);
  addHits(iQueryInCellOrder(*m_rtree, line));

  double bestT = std::numeric_limits<double>::max();
  for (const Hit& hit : hits)
  {
    if (hit.t > a_afterT + tEps)
      bestT = std::min(bestT, hit.t);
  }
  if (bestT > 1.0)
    return false;

  // Several cells meet the line at the entry point when it is a vertex they
  // share. Take the one the line goes into.
  Pt3d bestPt;
  VecInt bestCells = cellsAt(bestT, a_afterT + tEps, bestPt);
  a_cellIdx = bestCells[0];
  if (bestCells.size() > 1)
  {
    int entered = CellEnteredAfter(bestCells, a_pt1, a_pt2, bestT);
    if (entered != -1)
      a_cellIdx = entered;
  }
  a_entryPt = bestPt;
  a_entryT = bestT;
  return true;
}
//------------------------------------------------------------------------------
/// \brief Drop the stretches of the line that have no length.
///
/// A record whose next record is within a_tEps of it covers no length of the
/// line. It is a cell the line only touches (a corner it grazes, or a boundary
/// it starts or ends on and heads away from), a cell narrower than the
/// tolerance, or a gap between cells that meet at coincident points.
///
/// The sorter-based implementation reports a touch only when it is all the
/// line meets, and never a touch at a point that several cells hold, such as
/// a vertex they share. So does the walk.
/// \param a_tEps: Tolerance for comparing t-values.
/// \param a_polyIds: [in,out] 1-based cell ids, -1 where the line leaves the
///        mesh.
/// \param a_tValues: [in,out] The t-value of each entry in a_polyIds.
/// \param a_pts: [in,out] The point of each entry in a_polyIds.
//------------------------------------------------------------------------------
void GmMultiPolyIntersectorEdgeWalk::Impl::RemoveZeroLengthStretches(double a_tEps,
                                                                     VecInt& a_polyIds,
                                                                     VecDbl& a_tValues,
                                                                     VecPt3d& a_pts) const
{
  size_t count = a_polyIds.size();
  VecBool keep(count, true);
  bool anyLength = false; // whether the line runs through any cell
  int touch = -1;         // a touch the line could report on its own
  int touchCount = 0;     // touches other than at shared vertices
  for (size_t i = 0; i + 1 < count; ++i)
  {
    if (a_tValues[i + 1] - a_tValues[i] > a_tEps)
    {
      anyLength = anyLength || a_polyIds[i] != -1;
      continue;
    }
    keep[i] = false;
    if (a_polyIds[i] != -1 && !IsSharedPoint(a_polyIds[i] - 1, a_pts[i]))
    {
      touch = (int)i;
      ++touchCount;
    }
  }

  size_t kept = 0;
  auto keepRecord = [&](size_t a_i, int a_polyId) {
    a_polyIds[kept] = a_polyId;
    a_tValues[kept] = a_tValues[a_i];
    a_pts[kept] = a_pts[a_i];
    ++kept;
  };
  if (!anyLength)
  {
    // The line only touches the mesh: report the touch if there is one.
    if (touchCount == 1)
    {
      size_t i = static_cast<size_t>(touch);
      keepRecord(i, a_polyIds[i]);
      keepRecord(i + 1, -1);
    }
  }
  else
  {
    for (size_t i = 0; i < count; ++i)
    {
      if (!keep[i])
        continue;
      if (kept == 0 ? a_polyIds[i] == -1 : a_polyIds[kept - 1] == a_polyIds[i])
        continue; // a gap before the first cell, or the same cell or gap as before
      keepRecord(i, a_polyIds[i]);
    }
  }
  a_polyIds.resize(kept);
  a_tValues.resize(kept);
  a_pts.resize(kept);
} // GmMultiPolyIntersectorEdgeWalk::Impl::RemoveZeroLengthStretches
//------------------------------------------------------------------------------
/// \brief Find the polygon containing a point.
/// \param a_pt: Point location.
/// \return Id of the cell holding the point (its 0-based index plus the
///         starting id), or XM_NONE.
//------------------------------------------------------------------------------
int GmMultiPolyIntersectorEdgeWalk::Impl::PolygonFromPoint(const Pt3d& a_pt) const
{
  int cellIdx = FindCellContainingPoint(a_pt);
  return cellIdx < 0 ? XM_NONE : cellIdx + m_startingId;
}
//------------------------------------------------------------------------------
/// \brief Main edge-walk traversal.
/// \param a_x1: x coordinate of 1st point.
/// \param a_y1: y coordinate of 1st point.
/// \param a_x2: x coordinate of 2nd point.
/// \param a_y2: y coordinate of 2nd point.
/// \param a_polyIds: [out] List of polygon IDs crossed.
/// \param a_tValues: [out] t-values where crossings occur.
/// \param a_pts: [out] Crossing points.
//------------------------------------------------------------------------------
void GmMultiPolyIntersectorEdgeWalk::Impl::TraverseLineSegment(double a_x1,
                                                               double a_y1,
                                                               double a_x2,
                                                               double a_y2,
                                                               VecInt& a_polyIds,
                                                               VecDbl& a_tValues,
                                                               VecPt3d& a_pts)
{
  a_polyIds.clear();
  a_tValues.clear();
  a_pts.clear();

  // Every geometry call below takes m_xyTol explicitly, but gmOnLineWithTol
  // falls back to gmXyTol() for a cell edge shorter than the tolerance.
  GmXyTolGuard xyTol(m_xyTol);

  Pt3d pt1(a_x1, a_y1, 0.0);
  Pt3d pt2(a_x2, a_y2, 0.0);
  double segLen = gmXyDistance(pt1, pt2);
  if (gmEqualPointsXY(pt1, pt2, m_xyTol) || segLen < 1e-30)
    return; // degenerate segment
  const double tEps = TEps(segLen);

  int prevCell = -1; // the cell the walk was in before currentCell, or -1
  int currentCell = -1;
  double currentT = 0.0;
  Pt3d currentPt = pt1;
  // Whether the walk came into currentCell at currentT from outside the mesh,
  // and has not yet confirmed that the line goes into the cell there.
  bool justEntered = false;

  // Record that the line goes into a cell (0-based), or leaves the mesh (-1),
  // at a_t.
  auto record = [&](int a_cellIdx, double a_t, const Pt3d& a_pt) {
    a_polyIds.push_back(a_cellIdx < 0 ? -1 : a_cellIdx + 1);
    a_tValues.push_back(a_t);
    a_pts.push_back(Pt3d(a_pt.x, a_pt.y, 0.0));
  };
  // Move the walk to where the line comes back into the mesh after leaving
  // currentCell at a_leftT. Returns false if it never does.
  auto reenter = [&](double a_leftT) {
    int cellIdx;
    Pt3d pt;
    double t;
    if (!FindFirstMeshEntry(pt1, pt2, a_leftT, currentCell, cellIdx, pt, t))
      return false;
    prevCell = -1;
    currentCell = cellIdx;
    currentT = t;
    currentPt = pt;
    justEntered = true;
    record(currentCell, currentT, currentPt);
    return true;
  };

  // Step 1: find the cell the line starts in, or where it first enters the
  // mesh.
  currentCell = FindStartCell(pt1, pt2);
  if (currentCell == -1)
  {
    if (!FindFirstMeshEntry(pt1, pt2, -1.0, -1, currentCell, currentPt, currentT))
      return; // the line misses the mesh
  }
  justEntered = true;
  record(currentCell, currentT, currentPt);

  // Step 2: walk from cell to cell. Every pass moves to a later point on the
  // line, or into another cell at the same point, so the walk ends well before
  // m_maxIterations.
  for (int iter = 0; iter < m_maxIterations; ++iter)
  {
    int exitEdgeIdx;
    int hitVertexIdx;
    Pt3d exitPt;
    double exitT;
    bool found =
      FindExitEdge(currentCell, pt1, pt2, currentT, exitEdgeIdx, exitPt, exitT, hitVertexIdx);
    if (!found && CellHoldsPoint(currentCell, pt2))
    {
      record(-1, 1.0, pt2); // the line ends in this cell
      break;
    }

    // With nothing ahead in this cell, the line leaves the mesh here. Where the
    // walk has just come in from outside, the line can also miss the cell up
    // to the next boundary point: it only touched the cell, or the cell is
    // not convex and the line crosses a notch in it.
    bool leaves = !found;
    if (found && justEntered)
    {
      double midT = 0.5 * (currentT + exitT);
      Pt3d midPt(pt1.x + midT * (pt2.x - pt1.x), pt1.y + midT * (pt2.y - pt1.y), 0.0);
      leaves = !CellHoldsPoint(currentCell, midPt);
    }
    if (leaves)
    {
      record(-1, currentT, currentPt);
      if (!reenter(currentT))
        break;
      continue;
    }

    int nextCell;
    if (hitVertexIdx >= 0)
      nextCell = ResolveVertexCrossing(hitVertexIdx, pt1, pt2, exitT, prevCell, currentCell);
    else
      nextCell = m_ugrid->GetCell2dEdgeAdjacentCell(currentCell, exitEdgeIdx);

    if (exitT >= 1.0 - tEps)
    {
      // The line ends on this cell's boundary.
      if (CellHoldsPoint(currentCell, pt2))
      {
        record(-1, 1.0, pt2);
      }
      else if (nextCell >= 0 && CellHoldsPoint(nextCell, pt2))
      {
        record(nextCell, exitT, exitPt);
        record(-1, 1.0, pt2);
      }
      else
      {
        record(-1, exitT, exitPt);
      }
      break;
    }

    if (nextCell == -1)
    {
      // The line leaves the mesh.
      record(-1, exitT, exitPt);
      if (!reenter(exitT))
        break;
      continue;
    }

    if (nextCell != currentCell)
    {
      record(nextCell, exitT, exitPt);
      prevCell = currentCell;
      currentCell = nextCell;
    }
    // Otherwise the line touched a vertex of the cell and stays inside it.
    currentT = exitT;
    currentPt = exitPt;
    justEntered = false;
  }

  if (!a_polyIds.empty() && a_polyIds.back() != -1)
  {
    XM_ASSERT(false); // the walk ran out of passes
    record(-1, currentT, currentPt);
  }
  RemoveZeroLengthStretches(tEps, a_polyIds, a_tValues, a_pts);
  OffsetPolyIds(a_polyIds);
  gmRemoveDuplicateTValues(a_polyIds, a_tValues, a_pts);
}

} // namespace xms
