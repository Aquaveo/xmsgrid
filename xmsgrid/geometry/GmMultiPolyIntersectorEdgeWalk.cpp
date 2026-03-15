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

//----- Classes / Structs ------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
/// \brief Private implementation for GmMultiPolyIntersectorEdgeWalk.
////////////////////////////////////////////////////////////////////////////////
class GmMultiPolyIntersectorEdgeWalk::Impl
{
public:
  Impl(std::shared_ptr<XmUGrid> a_ugrid, int a_startingId);
  ~Impl();

  void SetQuery(GmMultiPolyIntersectorQueryEnum a_query);
  void TraverseLineSegment(double a_x1,
                           double a_y1,
                           double a_x2,
                           double a_y2,
                           VecInt& a_polyIds,
                           VecDbl& a_tValues,
                           VecPt3d& a_pts);
  int PolygonFromPoint(const Pt3d& a_pt);

private:
  int FindCellContainingPoint(const Pt3d& a_pt);
  bool FindExitEdge(int a_cellIdx,
                    const Pt3d& a_pt1,
                    const Pt3d& a_pt2,
                    double a_currentT,
                    int& a_exitEdgeIdx,
                    Pt3d& a_exitPt,
                    double& a_exitT,
                    int& a_hitVertexIdx);
  int ResolveVertexCrossing(int a_vertexIdx,
                            const Pt3d& a_pt1,
                            const Pt3d& a_pt2,
                            int a_currentCell);
  bool FindFirstMeshEntry(const Pt3d& a_pt1,
                          const Pt3d& a_pt2,
                          int& a_cellIdx,
                          Pt3d& a_entryPt,
                          double& a_entryT);
  void BuildRTree();
  void CalculateBuffer();
  void BufferTheBox(GmBstBox3d& a_box) const;
  void OffsetPolyIds(VecInt& a_polyIds) const;
  void RemoveDuplicateTValues(VecInt& a_polyIds, VecDbl& a_tValues, VecPt3d& a_pts);
  int PickCellOnRight(int a_vertexIdx1, int a_vertexIdx2, const Pt3d& a_pt1, const Pt3d& a_pt2);

  std::shared_ptr<XmUGrid> m_ugrid;
  RtreeBox* m_rtree;
  int m_startingId;
  double m_buffer;
  double m_xyTol;
  GmMultiPolyIntersectorQueryEnum m_query;
};

//----- Class / Function definitions -------------------------------------------

////////////////////////////////////////////////////////////////////////////////
/// \class GmMultiPolyIntersectorEdgeWalk
/// \brief Edge-walk based multi-polygon intersector using XmUGrid adjacency.
////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
/// \brief Constructor.
/// \param a_ugrid: The unstructured grid.
/// \param a_startingId: Starting ID for polygon numbering (default 1).
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
/// \return 1-based polygon ID, or XM_NONE.
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
//------------------------------------------------------------------------------
GmMultiPolyIntersectorEdgeWalk::Impl::Impl(std::shared_ptr<XmUGrid> a_ugrid, int a_startingId)
: m_ugrid(a_ugrid)
, m_rtree(nullptr)
, m_startingId(a_startingId)
, m_buffer(0.0)
, m_xyTol(1e-9)
, m_query(GMMPIQ_COVEREDBY)
{
  CalculateBuffer();
  BuildRTree();
}
//------------------------------------------------------------------------------
/// \brief Destructor for Impl.
//------------------------------------------------------------------------------
GmMultiPolyIntersectorEdgeWalk::Impl::~Impl()
{
  delete m_rtree;
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
  m_rtree = new RtreeBox(boxen.begin(), boxen.end());
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
/// \brief Remove duplicate t-values near 1.0 (matching existing behavior).
//------------------------------------------------------------------------------
void GmMultiPolyIntersectorEdgeWalk::Impl::RemoveDuplicateTValues(VecInt& a_polyIds,
                                                                  VecDbl& a_tValues,
                                                                  VecPt3d& a_pts)
{
  VecInt indexesToRemove;
  int size = (int)a_tValues.size();
  for (int i = size - 1; i > 0; --i)
  {
    if (GTEQ_TOL(a_tValues[i], 1.0, XM_ZERO_TOL) && GTEQ_TOL(a_tValues[i - 1], 1.0, XM_ZERO_TOL))
    {
      for (int j = i - 1; j > 0; --j)
      {
        if (GTEQ_TOL(a_tValues[i], 1.0, XM_ZERO_TOL) && GTEQ_TOL(a_tValues[j], 1.0, XM_ZERO_TOL) &&
            a_polyIds[i] == a_polyIds[j])
          indexesToRemove.push_back(j);
      }
    }
    else if (a_polyIds[i] == -1 && a_polyIds[i - 1] == -1)
    {
      for (int j = i - 1; j > 0; --j)
      {
        if (GTEQ_TOL(a_tValues[i], 1.0, 0.1) && GTEQ_TOL(a_tValues[j], 1.0, 0.1) &&
            a_polyIds[j] == -1)
          indexesToRemove.push_back(j);
      }
    }
    else
      break;
  }
  if (!indexesToRemove.empty())
  {
    auto it = std::unique(indexesToRemove.begin(), indexesToRemove.end());
    indexesToRemove.resize(std::distance(indexesToRemove.begin(), it));
    for (auto&& i : indexesToRemove)
    {
      a_polyIds.erase(a_polyIds.begin() + i);
      a_tValues.erase(a_tValues.begin() + i);
      a_pts.erase(a_pts.begin() + i);
    }
  }
}
//------------------------------------------------------------------------------
/// \brief Find the cell containing a point using R-tree + point-in-polygon.
/// \param a_pt: The point to locate.
/// \return 0-based cell index, or -1 if not found.
//------------------------------------------------------------------------------
int GmMultiPolyIntersectorEdgeWalk::Impl::FindCellContainingPoint(const Pt3d& a_pt)
{
  std::vector<ValueBox> result;
  m_rtree->query(bgi::intersects(a_pt), std::back_inserter(result));

  for (size_t i = 0; i < result.size(); ++i)
  {
    int cellIdx = result[i].second;
    VecPt3d cellLocs;
    m_ugrid->GetCellLocations(cellIdx, cellLocs);
    if (cellLocs.empty())
      continue;

    bool inside = false;
    switch (m_query)
    {
    case GMMPIQ_COVEREDBY: {
      GmBstPoly3d poly;
      for (auto& pt : cellLocs)
        bg::exterior_ring(poly).push_back(pt);
      bg::exterior_ring(poly).push_back(cellLocs[0]);
      inside = bg::covered_by(a_pt, poly);
      break;
    }
    case GMMPIQ_INTERSECTS: {
      GmBstPoly3d poly;
      for (auto& pt : cellLocs)
        bg::exterior_ring(poly).push_back(pt);
      bg::exterior_ring(poly).push_back(cellLocs[0]);
      inside = bg::intersects(a_pt, poly);
      break;
    }
    default:
      XM_ASSERT(false);
      break;
    }
    if (inside)
      return cellIdx;
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
                                                        int& a_hitVertexIdx)
{
  a_exitEdgeIdx = -1;
  a_hitVertexIdx = -1;
  a_exitT = std::numeric_limits<double>::max();

  int edgeCount = m_ugrid->GetCellEdgeCount(a_cellIdx);
  double xyTol = m_xyTol;

  // Compute a t-value epsilon from the XY tolerance and segment length.
  // t-values are parametric (0-1), so we need to convert spatial tolerance
  // into parametric tolerance.
  double segLen = gmXyDistance(a_pt1, a_pt2);
  double tEps = (segLen > 1e-30) ? (xyTol / segLen) : 1e-10;
  tEps = std::max(tEps, 1e-12);

  for (int e = 0; e < edgeCount; ++e)
  {
    XmEdge edge = m_ugrid->GetCellEdge(a_cellIdx, e);
    Pt3d edgePt1 = m_ugrid->GetPointLocation(edge.GetFirst());
    Pt3d edgePt2 = m_ugrid->GetPointLocation(edge.GetSecond());

    VecPt3d intersections;
    gmLineSegmentIntersections(a_pt1, a_pt2, edgePt1, edgePt2, intersections, xyTol);

    for (auto& ixPt : intersections)
    {
      double t = gmPtDistanceAlongSegment(a_pt1, a_pt2, ixPt, xyTol);
      if (t < -tEps || t > 1.0 + tEps)
        continue;
      if (t < 0.0)
        t = 0.0;
      if (t > 1.0)
        t = 1.0;

      // Must be strictly beyond current position (forward progress)
      if (t <= a_currentT + tEps)
        continue;

      if (t < a_exitT)
      {
        a_exitT = t;
        a_exitPt = ixPt;
        a_exitEdgeIdx = e;

        // Check if intersection is at a vertex
        a_hitVertexIdx = -1;
        if (gmEqualPointsXY(ixPt, edgePt1, xyTol))
          a_hitVertexIdx = edge.GetFirst();
        else if (gmEqualPointsXY(ixPt, edgePt2, xyTol))
          a_hitVertexIdx = edge.GetSecond();
      }
    }
  }
  return a_exitEdgeIdx != -1;
}
//------------------------------------------------------------------------------
/// \brief Resolve which cell the line enters when crossing through a vertex.
/// \param a_vertexIdx: The shared vertex index.
/// \param a_pt1: Line segment start.
/// \param a_pt2: Line segment end.
/// \param a_currentCell: The cell we're leaving.
/// \return 0-based cell index of the next cell, or -1 if exiting the mesh.
//------------------------------------------------------------------------------
int GmMultiPolyIntersectorEdgeWalk::Impl::ResolveVertexCrossing(int a_vertexIdx,
                                                                const Pt3d& a_pt1,
                                                                const Pt3d& a_pt2,
                                                                int a_currentCell)
{
  Pt3d V = m_ugrid->GetPointLocation(a_vertexIdx);
  double dx = a_pt2.x - a_pt1.x;
  double dy = a_pt2.y - a_pt1.y;
  double mag = std::sqrt(dx * dx + dy * dy);
  if (mag < 1e-30)
    return -1;

  VecInt adjCells = m_ugrid->GetPointAdjacentCells(a_vertexIdx);

  // Probe a point slightly past V along the line direction and check which
  // adjacent cell contains it. This handles convex and non-convex cells.
  for (double probeDist : {m_xyTol * 100, m_xyTol * 1000, m_xyTol * 10000})
  {
    double frac = probeDist / mag;
    Pt3d probe;
    probe.x = V.x + frac * dx;
    probe.y = V.y + frac * dy;

    for (int candidateCell : adjCells)
    {
      if (candidateCell == a_currentCell)
        continue;
      VecPt3d cellLocs;
      m_ugrid->GetCellLocations(candidateCell, cellLocs);
      if (cellLocs.empty())
        continue;
      int pip = gmPointInPolygon2D(&cellLocs[0], cellLocs.size(), probe.x, probe.y, m_xyTol);
      if (pip >= 0)
        return candidateCell;
    }
  }

  // If probing didn't work, try the edge-along case: line runs along an edge.
  // Check if the line direction is collinear with any edge from V and pick
  // the cell on the right side.
  for (int candidateCell : adjCells)
  {
    if (candidateCell == a_currentCell)
      continue;
    int cellEdgeCount = m_ugrid->GetCellEdgeCount(candidateCell);
    for (int e = 0; e < cellEdgeCount; ++e)
    {
      XmEdge edge = m_ugrid->GetCellEdge(candidateCell, e);
      int otherVtx = -1;
      if (edge.GetFirst() == a_vertexIdx)
        otherVtx = edge.GetSecond();
      else if (edge.GetSecond() == a_vertexIdx)
        otherVtx = edge.GetFirst();
      if (otherVtx < 0)
        continue;

      Pt3d other = m_ugrid->GetPointLocation(otherVtx);
      double edx = other.x - V.x;
      double edy = other.y - V.y;
      double cross = dx * edy - dy * edx;
      if (std::fabs(cross) <= m_xyTol * mag)
      {
        // Line is collinear with this edge. Pick the cell on the right side.
        int result = PickCellOnRight(a_vertexIdx, otherVtx, a_pt1, a_pt2);
        if (result != -1 && result != a_currentCell)
          return result;
      }
    }
  }

  return -1;
}
//------------------------------------------------------------------------------
/// \brief Pick the cell on the right side of a directed edge (matching
///        existing behavior for line-along-edge cases).
/// \param a_vertexIdx1: First vertex of the edge.
/// \param a_vertexIdx2: Second vertex of the edge.
/// \param a_pt1: Line direction start.
/// \param a_pt2: Line direction end.
/// \return 0-based cell index on the right side, or -1.
//------------------------------------------------------------------------------
int GmMultiPolyIntersectorEdgeWalk::Impl::PickCellOnRight(int a_vertexIdx1,
                                                          int a_vertexIdx2,
                                                          const Pt3d& a_pt1,
                                                          const Pt3d& a_pt2)
{
  VecInt adjCells;
  m_ugrid->GetPointsAdjacentCells(a_vertexIdx1, a_vertexIdx2, adjCells);

  if (adjCells.size() == 1)
    return adjCells[0];
  if (adjCells.empty())
    return -1;

  // Find the cell whose centroid is on the right side of the line direction
  Pt3d edgePt1 = m_ugrid->GetPointLocation(a_vertexIdx1);
  double dx = a_pt2.x - a_pt1.x;
  double dy = a_pt2.y - a_pt1.y;

  for (int cellIdx : adjCells)
  {
    Pt3d centroid;
    m_ugrid->GetCellCentroid(cellIdx, centroid);
    double cross = dx * (centroid.y - edgePt1.y) - dy * (centroid.x - edgePt1.x);
    if (cross < -m_xyTol)
      return cellIdx; // Right side
  }
  // Fallback: return first cell
  return adjCells[0];
}
//------------------------------------------------------------------------------
/// \brief Find where a line first enters the mesh from outside.
/// \param a_pt1: Line segment start (outside mesh).
/// \param a_pt2: Line segment end.
/// \param a_cellIdx: [out] Cell the line enters.
/// \param a_entryPt: [out] Entry point on the mesh boundary.
/// \param a_entryT: [out] t-value of entry point.
/// \return true if an entry was found.
//------------------------------------------------------------------------------
bool GmMultiPolyIntersectorEdgeWalk::Impl::FindFirstMeshEntry(const Pt3d& a_pt1,
                                                              const Pt3d& a_pt2,
                                                              int& a_cellIdx,
                                                              Pt3d& a_entryPt,
                                                              double& a_entryT)
{
  // Query R-tree for cells whose bounding box intersects the line
  GmBstLine3d line;
  line.push_back(a_pt1);
  line.push_back(a_pt2);

  std::vector<ValueBox> result;
  m_rtree->query(bgi::intersects(line), std::back_inserter(result));

  double bestT = std::numeric_limits<double>::max();
  int bestCell = -1;
  Pt3d bestPt;
  double tol = m_xyTol;

  for (size_t i = 0; i < result.size(); ++i)
  {
    int cellIdx = result[i].second;
    int edgeCount = m_ugrid->GetCellEdgeCount(cellIdx);

    for (int e = 0; e < edgeCount; ++e)
    {
      XmEdge edge = m_ugrid->GetCellEdge(cellIdx, e);
      Pt3d edgePt1 = m_ugrid->GetPointLocation(edge.GetFirst());
      Pt3d edgePt2 = m_ugrid->GetPointLocation(edge.GetSecond());

      VecPt3d intersections;
      gmLineSegmentIntersections(a_pt1, a_pt2, edgePt1, edgePt2, intersections, tol);

      for (auto& ixPt : intersections)
      {
        double t = gmPtDistanceAlongSegment(a_pt1, a_pt2, ixPt, tol);
        if (t < -tol || t > 1.0 + tol)
          continue;
        if (t < 0.0)
          t = 0.0;
        if (t > 1.0)
          t = 1.0;
        if (t < bestT - tol)
        {
          bestT = t;
          bestPt = ixPt;
          bestCell = cellIdx;
        }
        else if (t < bestT + tol)
        {
          // Same t: this intersection might be at a vertex shared by multiple cells.
          // Prefer a cell that the line actually enters (not just touches).
          // Check if the midpoint slightly beyond entry is inside this cell.
          double probeT = t + 1e-6;
          if (probeT <= 1.0)
          {
            Pt3d probe;
            probe.x = a_pt1.x + probeT * (a_pt2.x - a_pt1.x);
            probe.y = a_pt1.y + probeT * (a_pt2.y - a_pt1.y);
            VecPt3d cellLocs;
            m_ugrid->GetCellLocations(cellIdx, cellLocs);
            int pip = gmPointInPolygon2D(&cellLocs[0], cellLocs.size(), probe.x, probe.y, tol);
            if (pip >= 0)
            {
              bestT = t;
              bestPt = ixPt;
              bestCell = cellIdx;
            }
          }
        }
      }
    }
  }

  if (bestCell != -1)
  {
    a_cellIdx = bestCell;
    a_entryPt = bestPt;
    a_entryT = bestT;
    return true;
  }
  return false;
}
//------------------------------------------------------------------------------
/// \brief Find the polygon containing a point.
/// \param a_pt: Point location.
/// \return 1-based polygon ID (offset by m_startingId), or XM_NONE.
//------------------------------------------------------------------------------
int GmMultiPolyIntersectorEdgeWalk::Impl::PolygonFromPoint(const Pt3d& a_pt)
{
  int cellIdx = FindCellContainingPoint(a_pt);
  if (cellIdx < 0)
    return XM_NONE;
  // Return 1-based ID, then offset
  int id = cellIdx + 1;
  if (m_startingId != 1)
    id += (m_startingId - 1);
  return id;
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

  double oldTolerance = gmXyTol();
  gmXyTol(true, m_xyTol);

  Pt3d pt1(a_x1, a_y1, 0.0);
  Pt3d pt2(a_x2, a_y2, 0.0);
  double tol = m_xyTol;

  double segLen = gmXyDistance(pt1, pt2);

  // Degenerate segment check
  if (gmEqualPointsXY(pt1, pt2, tol) || segLen < 1e-30)
  {
    gmXyTol(true, oldTolerance);
    return;
  }

  // Step 1: Find starting cell.
  // If pt1 is on a boundary between cells, we need to pick the cell the
  // line actually enters. Find all candidate cells and probe slightly ahead.
  int currentCell = -1;
  {
    // Collect all cells whose R-tree bounding box contains pt1
    std::vector<ValueBox> rtreeResult;
    m_rtree->query(bgi::intersects(pt1), std::back_inserter(rtreeResult));

    VecInt candidates;
    for (auto& vb : rtreeResult)
    {
      int cellIdx = vb.second;
      VecPt3d cellLocs;
      m_ugrid->GetCellLocations(cellIdx, cellLocs);
      if (cellLocs.empty())
        continue;
      GmBstPoly3d poly;
      for (auto& p : cellLocs)
        bg::exterior_ring(poly).push_back(p);
      bg::exterior_ring(poly).push_back(cellLocs[0]);
      if (bg::covered_by(pt1, poly))
        candidates.push_back(cellIdx);
    }

    if (candidates.size() == 1)
    {
      currentCell = candidates[0];
    }
    else if (candidates.size() > 1)
    {
      // pt1 is on a boundary shared by multiple cells. Probe along the
      // line direction to pick the cell the line enters.
      for (double frac : {1e-4, 1e-3, 1e-2})
      {
        Pt3d probe;
        probe.x = pt1.x + frac * (pt2.x - pt1.x);
        probe.y = pt1.y + frac * (pt2.y - pt1.y);
        for (int c : candidates)
        {
          VecPt3d cellLocs;
          m_ugrid->GetCellLocations(c, cellLocs);
          int pip = gmPointInPolygon2D(&cellLocs[0], cellLocs.size(), probe.x, probe.y, tol);
          if (pip >= 0)
          {
            currentCell = c;
            break;
          }
        }
        if (currentCell >= 0)
          break;
      }
      if (currentCell < 0)
        currentCell = candidates[0]; // Fallback
    }
  }
  double currentT = 0.0;
  Pt3d currentPt = pt1;

  if (currentCell == -1)
  {
    // pt1 is outside the mesh — find where the line first enters
    Pt3d entryPt;
    double entryT;
    if (!FindFirstMeshEntry(pt1, pt2, currentCell, entryPt, entryT))
    {
      // Line doesn't cross the mesh at all
      gmXyTol(true, oldTolerance);
      return;
    }
    currentT = entryT;
    currentPt = entryPt;

    // If entry t >= 1.0, the line only touches the mesh boundary at the end
    if (currentT >= 1.0 - tol)
    {
      // Special case: line touches mesh at a single point (like OutPt test)
      // Record: [cellId, -1] at [t, t]
      a_polyIds.push_back(currentCell + 1);
      a_tValues.push_back(currentT);
      a_pts.push_back(Pt3d(currentPt.x, currentPt.y, 0.0));
      a_polyIds.push_back(-1);
      a_tValues.push_back(currentT);
      a_pts.push_back(Pt3d(currentPt.x, currentPt.y, 0.0));
      OffsetPolyIds(a_polyIds);
      gmXyTol(true, oldTolerance);
      return;
    }
  }

  // Record the entry into the first cell
  a_polyIds.push_back(currentCell + 1); // 1-based
  a_tValues.push_back(currentT);
  a_pts.push_back(Pt3d(currentPt.x, currentPt.y, 0.0));

  // Compute a t-epsilon for end-of-segment detection
  double tEps = (segLen > 1e-30) ? (tol / segLen) : 1e-10;
  tEps = std::max(tEps, 1e-12);

  // Step 2: Walk through cells
  int prevCell = -1;
  const int maxIterations = m_ugrid->GetCellCount() + 100;
  for (int iter = 0; iter < maxIterations; ++iter)
  {
    int exitEdgeIdx;
    Pt3d exitPt;
    double exitT;
    int hitVertexIdx;

    bool found =
      FindExitEdge(currentCell, pt1, pt2, currentT, exitEdgeIdx, exitPt, exitT, hitVertexIdx);

    if (!found)
    {
      // No exit edge found. Either pt2 is inside this cell, or the line
      // entered at a boundary point and immediately exited.
      int pt2Cell = FindCellContainingPoint(pt2);
      if (pt2Cell == currentCell)
      {
        // pt2 is genuinely inside this cell
        a_polyIds.push_back(-1);
        a_tValues.push_back(1.0);
        a_pts.push_back(Pt3d(pt2.x, pt2.y, 0.0));
      }
      else
      {
        // pt2 is NOT inside this cell. The line touched the boundary at the
        // entry point and immediately left.
        // Only discard vertex-only touches when this is the FIRST entry from
        // outside (prevCell == -1). During mid-walk, always record the exit.
        bool discard = false;
        if (prevCell == -1)
        {
          // Check if this is a vertex-only touch at a shared vertex
          VecInt cellPts = m_ugrid->GetCellPoints(currentCell);
          for (int ptIdx : cellPts)
          {
            Pt3d vtx = m_ugrid->GetPointLocation(ptIdx);
            if (gmEqualPointsXY(currentPt, vtx, tol))
            {
              int adjCount = m_ugrid->GetPointAdjacentCellCount(ptIdx);
              if (adjCount > 1)
                discard = true;
              break;
            }
          }
        }
        if (discard)
        {
          // Vertex-only touch from outside — discard the entry
          a_polyIds.pop_back();
          a_tValues.pop_back();
          a_pts.pop_back();
        }
        else
        {
          // Boundary touch — record exit at the entry point
          a_polyIds.push_back(-1);
          a_tValues.push_back(currentT);
          a_pts.push_back(Pt3d(currentPt.x, currentPt.y, 0.0));
        }
      }
      break;
    }

    // Clamp exit t
    if (exitT > 1.0)
      exitT = 1.0;

    // Determine next cell
    int nextCell = -1;
    if (hitVertexIdx >= 0)
    {
      nextCell = ResolveVertexCrossing(hitVertexIdx, pt1, pt2, currentCell);
    }
    else
    {
      nextCell = m_ugrid->GetCell2dEdgeAdjacentCell(currentCell, exitEdgeIdx);
    }

    // Prevent bouncing back to the cell we just came from
    if (nextCell == prevCell && nextCell >= 0)
    {
      // Try to find an alternative next cell
      if (hitVertexIdx >= 0)
      {
        // At a vertex, try other adjacent cells
        VecInt adjCells = m_ugrid->GetPointAdjacentCells(hitVertexIdx);
        int altCell = -1;
        for (int c : adjCells)
        {
          if (c != currentCell && c != prevCell)
          {
            altCell = c;
            break;
          }
        }
        if (altCell >= 0)
          nextCell = altCell;
      }
    }

    if (exitT >= 1.0 - tEps)
    {
      // We've reached pt2
      int pt2Cell = FindCellContainingPoint(pt2);

      if (pt2Cell == currentCell)
      {
        a_polyIds.push_back(-1);
        a_tValues.push_back(1.0);
        a_pts.push_back(Pt3d(pt2.x, pt2.y, 0.0));
      }
      else if (nextCell >= 0 && pt2Cell == nextCell)
      {
        a_polyIds.push_back(nextCell + 1);
        a_tValues.push_back(exitT);
        a_pts.push_back(Pt3d(exitPt.x, exitPt.y, 0.0));
        a_polyIds.push_back(-1);
        a_tValues.push_back(1.0);
        a_pts.push_back(Pt3d(pt2.x, pt2.y, 0.0));
      }
      else
      {
        a_polyIds.push_back(-1);
        a_tValues.push_back(exitT);
        a_pts.push_back(Pt3d(exitPt.x, exitPt.y, 0.0));
      }
      break;
    }

    if (nextCell == -1)
    {
      // Exiting the mesh through a boundary
      a_polyIds.push_back(-1);
      a_tValues.push_back(exitT);
      a_pts.push_back(Pt3d(exitPt.x, exitPt.y, 0.0));

      // Try to find re-entry into the mesh.
      // Use a search start that's at least m_buffer past the exit to avoid
      // false re-entry at the same boundary due to R-tree buffer tolerance.
      double bufferT = (segLen > 1e-30) ? (m_buffer * 2.0 / segLen) : 0.01;
      double searchStartT = exitT + std::max(bufferT, tEps * 100);
      if (searchStartT < 1.0)
      {
        Pt3d searchStart;
        searchStart.x = pt1.x + searchStartT * (pt2.x - pt1.x);
        searchStart.y = pt1.y + searchStartT * (pt2.y - pt1.y);

        int reentryCell = -1;
        Pt3d reentryPt;
        double reentryT;
        if (FindFirstMeshEntry(searchStart, pt2, reentryCell, reentryPt, reentryT))
        {
          // Convert reentryT from searchStart-pt2 space to pt1-pt2 space
          reentryT = searchStartT + reentryT * (1.0 - searchStartT);
          // Only accept re-entry if it's at a genuinely different location
          if (reentryT < 1.0 + tEps && reentryCell != currentCell)
          {
            prevCell = -1;
            currentCell = reentryCell;
            currentT = reentryT;
            currentPt = reentryPt;
            a_polyIds.push_back(currentCell + 1);
            a_tValues.push_back(currentT);
            a_pts.push_back(Pt3d(currentPt.x, currentPt.y, 0.0));
            continue;
          }
        }
      }
      break; // No re-entry
    }

    // Move to next cell
    a_polyIds.push_back(nextCell + 1);
    a_tValues.push_back(exitT);
    a_pts.push_back(Pt3d(exitPt.x, exitPt.y, 0.0));

    prevCell = currentCell;
    currentCell = nextCell;
    currentT = exitT;
    currentPt = exitPt;
  }

  OffsetPolyIds(a_polyIds);
  RemoveDuplicateTValues(a_polyIds, a_tValues, a_pts);

  gmXyTol(true, oldTolerance);
}

} // namespace xms
