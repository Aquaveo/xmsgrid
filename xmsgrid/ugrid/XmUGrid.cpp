//------------------------------------------------------------------------------
/// \file XmUGrid.cpp
/// \ingroup ugrid
/// \copyright (C) Copyright Aquaveo 2018.
//------------------------------------------------------------------------------

//----- Included files ---------------------------------------------------------

// 1. Precompiled header

// 2. My own header
#include <xmsgrid/ugrid/XmUGrid.h>

// 3. Standard library headers
#include <set>
#include <unordered_set>

// 4. External library headers
#include <boost/container/flat_set.hpp>

// 5. Shared code headers
#include <xmscore/misc/XmConst.h>
#include <xmscore/misc/XmError.h>
#include <xmscore/misc/XmLog.h>
#include <xmscore/stl/set.h>

// 6. Non-shared code headers
#include <xmsgrid/ugrid/XmConvexHull.h>
#include <xmsgrid/ugrid/XmUGridUtils.h>

//----- Forward declarations ---------------------------------------------------

//----- External globals -------------------------------------------------------

//----- Namespace declaration --------------------------------------------------

/// XMS Namespace
namespace xms
{
//----- Constants / Enumerations -----------------------------------------------

//----- Classes / Structs ------------------------------------------------------

//----- Internal functions -----------------------------------------------------

namespace
{
typedef std::pair<int, int> Edge;
typedef std::vector<Edge> VecEdge;

//----- Class / Function definitions -------------------------------------------
////////////////////////////////////////////////////////////////////////////////
/// Implementation for XmUGrid
class XmUGridImpl : public XmUGrid
{
public:
  XmUGridImpl();

  // Points

  virtual int GetNumberOfPoints() const override;

  virtual const VecPt3d& GetPoints() const override;
  virtual void SetPoints(const VecPt3d& a_points) override;

  virtual Pt3d GetPoint(const int a_pointIdx) const override;
  virtual bool SetPoint(const int a_pointIdx, const Pt3d& a_point) override;

  virtual Pt3d GetXYPoint(const int a_pointIdx) const override;
  virtual VecPt3d GetPointsFromPointIdxs(const VecInt& a_points) const override;

  virtual void GetExtents(Pt3d& a_min, Pt3d& a_max) const override;

  virtual VecInt GetPointCells(const int a_pointIdx) const override; // cells associated with point
  virtual void GetPointCells(const int a_pointIdx, VecInt& a_attachedCellIdxs) const override;

  virtual VecInt GetCommonCells(const VecInt& a_points) const override;
  virtual void GetCommonCells(const int* a_pointIdxs,
                              int a_numpointIdxs,
                              VecInt& a_commonCellIdxs) const;
  virtual void GetCommonCells(const VecInt& a_points, VecInt& a_commonCellIdxs) const override;
  virtual void GetCommonCells(const int a_ptIdx1,
                              const int a_ptIdx2,
                              VecInt& a_commonCellIdxs) const override;

  // Cells
  virtual int GetNumberOfCells() const override;

  virtual VecInt GetPointsOfCell(const int a_cellIdx) const override;
  virtual bool GetPointsOfCell(const int a_cellIdx, VecInt& a_cellPoints) const override;
  virtual void GetPointsOfCell(const int a_cellIdx, VecPt3d& a_cellPoints) const override;

  virtual XmUGridCellType GetCellType(const int a_cellIdx) const override;
  virtual std::vector<int> GetDimensionCount() const override;
  virtual int GetCellDimension(const int a_cellIdx) const override;
  virtual void GetCellExtents(const int a_cellIdx, Pt3d& a_min, Pt3d& a_max) const override;

  virtual const VecInt& GetCellStream() const override;
  virtual bool SetCellStream(const VecInt& a_cellStream) override;
  virtual bool GetSingleCellStream(const int a_cellIdx, VecInt& a_cellStream) const override;

  virtual VecInt GetCellNeighbors(const int a_cellIdx) const override;
  virtual void GetCellNeighbors(const int a_cellIdx, VecInt& a_cellNeighbors) const override;
  virtual bool GetPlanViewPolygon(int a_cellIdx, VecPt3d& a_polygon) const override;
  virtual bool GetCentroid(int a_cellIdx, Pt3d& a_centroid) const override;

  // Edges
  virtual int GetNumberOfCellEdges(const int a_cellIdx) const override;
  virtual std::pair<int, int> GetCellEdgeFromEdgeIndex(const int a_cellIdx,
                                                       const int a_edgeIdx) const override;
  virtual VecInt GetAdjacentCells(const int a_cellIdx, const int a_edgeIdx) const override;
  virtual void GetAdjacentCells(const int a_cellIdx,
                                const int a_edgeIdx,
                                VecInt& a_adjacentCellIdxs) const override;
  virtual int Get2dAdjacentCell(const int a_cellIdx, const int a_edgeIdx) const override;
  virtual VecInt GetAdjacentCellsFromGivenEdge(const int a_pointIdx1,
                                               const int a_pointIdx2) const override;
  virtual void GetAdjacentCellsFromGivenEdge(const int a_pointIdx1,
                                             const int a_pointIdx2,
                                             VecInt& a_adjacentCellIdxs) const override;

  virtual VecInt GetAdjacentCellsFromGivenEdge(const std::pair<int, int> a_edge) const override;

  virtual bool GetEdgesFromPoint(const int a_pointId,
                                 VecInt& a_cellIdxs,
                                 VecInt& a_edgeIdxs) const override;
  virtual bool GetEdgesFromPoint(const int a_pointId,
                                 VecInt& a_cellIdxs,
                                 std::vector<std::pair<int, int>>& a_edges) const override;
  virtual bool GetEdgesFromPoint(const int a_pointId,
                                 VecInt& a_cellIdxs,
                                 VecInt& a_edgePoints1,
                                 VecInt& a_edgePoints2) const override;

  virtual std::vector<std::pair<int, int>> GetEdgesOfCell(const int a_cellIdx) const override;
  virtual void GetEdgesOfCell(const int a_cellIdx,
                              std::vector<std::pair<int, int>>& a_edges) const override;
  virtual void GetPointIdxsAttachedByEdge(int a_pointIdx, VecInt& a_edgePoints) const override;
  virtual void GetPointsAttachedByEdge(int a_pointIdx, VecPt3d& a_edgePoints) const override;

  // Faces
  virtual int GetNumberOfCellFaces(const int a_cellIdx) const override;
  virtual int GetNumberOfFacePoints(const int a_cellIdx, const int a_faceIdx) const override;

  virtual VecInt GetCellFace(const int a_cellIdx, const int a_faceIdx) const override;
  virtual void GetCellFace(const int a_cellIdx,
                           const int a_faceIdx,
                           VecInt& a_facePtIdxs) const override;
  virtual VecInt2d GetFacesOfCell(const int a_cellIdx) const override;

  virtual int GetCellFaceNeighbor(const int a_cellIdx, const int a_faceIdx) const override;
  virtual bool GetCellFaceNeighbor(const int a_cellIdx,
                                   const int a_faceIdx,
                                   int& a_neighborCell,
                                   int& a_neighborFace) const override;

  virtual bool GetFacesFromPoint(const int a_pointId,
                                 VecInt& a_cellIdxs,
                                 VecInt& a_faceIdxs) const override;

  // virtual XmUGridFaceOrientation GetFaceOrientation(const int a_cellIdx, const int a_faceIdx)
  // const override;

  // Misc

private:
  void UpdateLinks(); // Calls UpdateCellLinks & UpdatePointLinks
  void UpdateCellLinks();
  void UpdatePointLinks();

  static int DimensionFromCellType(const XmUGridCellType a_cellType);

  int GetNumberOfItemsForCell(const int a_cellIdx) const;

  // Optimized for efficiency
  void GetSingleCellStream(const int a_cellIdx, const int** a_start, int& a_length) const;

  int GetNumberOfPolyhedronEdges(const int a_cellIdx) const;
  static void GetUniquePointsFromPolyhedronCellStream(const VecInt& a_cellStream,
                                                      const int a_numCellItems,
                                                      int& a_currIdx,
                                                      VecInt& a_uniquePoints,
                                                      VecInt& a_cellMask);
  static bool GetUniquePointsFromPolyhedronSingleCellStream(const VecInt& a_cellStream,
                                                            VecInt& a_cellPoints);
  static void GetUniqueEdgesFromPolyhedronCellStream(
    const int* a_start,
    int& a_length,
    boost::container::flat_set<std::pair<int, int>>& a_cellEdges,
    int& a_currIdx);

  bool GetPlanViewPolygon2d(int a_cellIdx, VecPt3d& a_polygon) const;
  bool GetPlanViewPolygon3d(int a_cellIdx, VecPt3d& a_polygon) const;

  bool IsFaceSide(const VecInt& a_facePts) const; // plan view
  bool GetCellXySegments(int cellIdx, VecPt3d& segments) const; // plan view
  bool IsCellValidWithPointChange(const int a_cellIdx,
                                  const int a_changedPtIdx,
                                  const Pt3d& a_newPosition) const;
  void GetEdgesOfFace(const VecInt& a_face, std::vector<std::pair<int, int>>& a_edges) const;
  bool DoEdgesCrossWithPointChange(const int a_changedPtIdx,
                                   const Pt3d& a_newPosition,
                                   const std::vector<std::pair<int, int>>& a_edges) const;
  void GetExtentsFromPoints(const VecPt3d& a_points, Pt3d &a_min, Pt3d &a_max) const;
  bool GetFaceXySegments(int a_cellIdx, int a_faceIdx, VecPt3d& a_segments) const; // plan view

  VecPt3d m_points;                 ///< UGrid points
  VecInt m_cellStream;              ///< UGrid cell stream. @see SetCellStream, GetCellStream
  VecInt m_cellIdxToStreamIdx;      ///< Indexes for each cell in the cell stream
  VecInt m_pointsToCells;           ///< Array of points cells (goes from pointIdx to list
                                    ///< of cells)
  VecInt m_pointIdxToPointsToCells; ///< Indexes for each point in array of
                                    ///< points cells
};

//------------------------------------------------------------------------------
/// \brief Return if two edges are the same edge even if not directed the same.
/// \param[in] a_edge1 The first edge to compare.
/// \param[in] a_edge2 The second edge to compare.
/// \return Whether the two edges are the same even if not directed the same.
//------------------------------------------------------------------------------
bool iEdgesEquivalent(const std::pair<int, int>& a_edge1, const std::pair<int, int>& a_edge2)
{
  bool equivalent = (a_edge1.first == a_edge2.first && a_edge1.second == a_edge2.second) ||
                    (a_edge1.first == a_edge2.second && a_edge1.second == a_edge2.first);
  return equivalent;
} // iEdgesEquivalent
//------------------------------------------------------------------------------
/// \brief Get the offset for each edge for a given cell type.
/// \param[in] a_cellType The cell type to get the table for.
/// \return A const reference to the cell type's table.
//------------------------------------------------------------------------------
const VecEdge& iGetEdgeOffsetTable(int a_cellType)
{
  static const VecEdge fg_empty;
  static const VecEdge fg_line = {{0, 1}};
  static const VecEdge fg_triangle = {{0, 1}, {1, 2}, {2, 0}};
  static const VecEdge fg_pixel = {{0, 1}, {1, 3}, {3, 2}, {2, 0}};
  static const VecEdge fg_quad = {{0, 1}, {1, 2}, {2, 3}, {3, 0}};
  static const VecEdge fg_tetra = {{0, 1}, {1, 2}, {2, 0}, {0, 3}, {1, 3}, {2, 3}};
  static const VecEdge fg_wedge = {{0, 1}, {1, 2}, {2, 0}, {3, 4}, {4, 5},
                                   {5, 3}, {0, 3}, {1, 4}, {2, 5}};
  static const VecEdge fg_voxel = {{0, 1}, {1, 3}, {2, 3}, {0, 2}, {4, 5}, {5, 7},
                                   {6, 7}, {4, 6}, {0, 4}, {1, 5}, {2, 6}, {3, 7}};
  static const VecEdge fg_hexahedron = {{0, 1}, {1, 2}, {3, 2}, {0, 3}, {4, 5}, {5, 6},
                                        {7, 6}, {4, 7}, {0, 4}, {1, 5}, {3, 7}, {2, 6}};
  static const VecEdge fg_pyramid = {{0, 1}, {1, 2}, {2, 3}, {3, 0},
                                     {0, 4}, {1, 4}, {2, 4}, {3, 4}};
  static const VecEdge fg_pentagonalPrism = {{0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 0},
                                             {5, 6}, {6, 7}, {7, 8}, {8, 9}, {9, 5},
                                             {0, 5}, {1, 6}, {2, 7}, {3, 8}, {4, 9}};
  static const VecEdge fg_hexagonalPrism = {{0, 1}, {1, 2}, {2, 3}, {3, 4},  {4, 5},   {5, 0},
                                            {6, 7}, {7, 8}, {8, 9}, {9, 10}, {10, 11}, {11, 6},
                                            {0, 6}, {1, 7}, {2, 8}, {3, 9},  {4, 10},  {5, 11}};

  switch (a_cellType)
  {
  // invalid
  case XMU_INVALID_CELL_TYPE:
    return fg_empty;
    break;

  // 0D
  case XMU_EMPTY_CELL:
  case XMU_VERTEX:
  case XMU_POLY_VERTEX:
  case XMU_CONVEX_POINT_SET: // Special class of cells formed by convex group of
                             // points
    return fg_empty;
    break;

  // 1D
  case XMU_LINE:
    return fg_line;
    break;

  // 2D
  case XMU_TRIANGLE:
    return fg_triangle;
    break;
  case XMU_PIXEL:
    return fg_pixel;
    break;
  case XMU_QUAD:
    return fg_quad;
    break;

  case XMU_POLYGON:
    // should be using cell stream
    XM_ASSERT(0);
    return fg_empty;
    break;

  // 2D Not yet supported
  case XMU_QUADRATIC_EDGE:
  case XMU_PARAMETRIC_CURVE:
  case XMU_HIGHER_ORDER_EDGE:
  case XMU_CUBIC_LINE: // Cubic, isoparametric cell
  case XMU_TRIANGLE_STRIP:
  case XMU_QUADRATIC_TRIANGLE:
  case XMU_BIQUADRATIC_TRIANGLE:
  case XMU_HIGHER_ORDER_TRIANGLE:
  case XMU_HIGHER_ORDER_POLYGON:
  case XMU_QUADRATIC_POLYGON:
  case XMU_PARAMETRIC_SURFACE:
  case XMU_PARAMETRIC_TRI_SURFACE:
  case XMU_PARAMETRIC_QUAD_SURFACE:
    XM_ASSERT(0);
    return fg_empty;
    break;

  // 3D dimensions
  case XMU_TETRA:
    return fg_tetra;
    break;
  case XMU_WEDGE:
    return fg_wedge;
    break;
  case XMU_VOXEL:
    return fg_voxel;
    break;
  case XMU_HEXAHEDRON:
    return fg_hexahedron;
    break;
  case XMU_PYRAMID:
    return fg_pyramid;
    break;
  case XMU_PENTAGONAL_PRISM:
    return fg_pentagonalPrism;
    break;
  case XMU_HEXAGONAL_PRISM:
    return fg_hexagonalPrism;
    break;
  case XMU_POLYHEDRON:
    // should be using cell stream
    XM_ASSERT(0);
    return fg_empty;
    break;

  // 3D Not yet supported
  case XMU_QUADRATIC_TETRA:
  case XMU_HIGHER_ORDER_TETRAHEDRON:
  case XMU_QUADRATIC_WEDGE:
  case XMU_QUADRATIC_LINEAR_WEDGE:
  case XMU_BIQUADRATIC_QUADRATIC_WEDGE:
  case XMU_HIGHER_ORDER_WEDGE:
  case XMU_QUADRATIC_HEXAHEDRON:
  case XMU_TRIQUADRATIC_HEXAHEDRON:
  case XMU_BIQUADRATIC_QUADRATIC_HEXAHEDRON:
  case XMU_HIGHER_ORDER_HEXAHEDRON:
  case XMU_QUADRATIC_PYRAMID:
  case XMU_HIGHER_ORDER_PYRAMID:
  case XMU_PARAMETRIC_TETRA_REGION:
  case XMU_PARAMETRIC_HEX_REGION:
    XM_ASSERT(0);
    return fg_empty;
    break;
  }

  XM_ASSERT(0);
  return fg_empty;
} // iGetEdgeOffsetTable
//------------------------------------------------------------------------------
/// \brief Get the offset for each face for a given cell type.
/// \param[in] a_cellType The cell type to get the table for.
/// \return A const reference to the cell type's table.
//------------------------------------------------------------------------------
const VecInt2d& iGetFaceOffsetTable(int a_cellType)
{
  static const VecInt2d fg_empty;
  static const VecInt2d fg_tetra = {{0, 1, 3}, {1, 2, 3}, {2, 0, 3}, {0, 2, 1}};
  static const VecInt2d fg_wedge = {{0, 1, 2}, {3, 5, 4}, {0, 3, 4, 1}, {1, 4, 5, 2}, {2, 5, 3, 0}};
  static const VecInt2d fg_voxel = {{0, 4, 6, 2}, {1, 3, 7, 5}, {0, 1, 5, 4},
                                    {2, 6, 7, 3}, {0, 2, 3, 1}, {4, 5, 7, 6}};
  static const VecInt2d fg_hexahedron = {{0, 4, 7, 3}, {1, 2, 6, 5}, {0, 1, 5, 4},
                                         {3, 7, 6, 2}, {0, 3, 2, 1}, {4, 5, 6, 7}};
  static const VecInt2d fg_pyramid = {{0, 3, 2, 1}, {0, 1, 4}, {1, 2, 4}, {2, 3, 4}, {3, 0, 4}};
  static const VecInt2d fg_pentagonalPrism = {{0, 4, 3, 2, 1}, {5, 6, 7, 8, 9}, {0, 1, 6, 5},
                                              {1, 2, 7, 6},    {2, 3, 8, 7},    {3, 4, 9, 8},
                                              {4, 0, 5, 9}};
  static const VecInt2d fg_hexagonalPrism = {
    {0, 5, 4, 3, 2, 1}, {6, 7, 8, 9, 10, 11}, {0, 1, 7, 6},   {1, 2, 8, 7},
    {2, 3, 9, 8},       {3, 4, 10, 9},        {4, 5, 11, 10}, {5, 0, 6, 11}};

  switch (a_cellType)
  {
  // invalid
  // 0D
  // 1D
  case XMU_INVALID_CELL_TYPE:
  case XMU_EMPTY_CELL:
  case XMU_VERTEX:
  case XMU_POLY_VERTEX:
  case XMU_CONVEX_POINT_SET: // Special class of cells formed by convex group of
                             // points
  case XMU_LINE:
  case XMU_TRIANGLE:
  case XMU_PIXEL:
  case XMU_QUAD:
  case XMU_POLYGON:
  case XMU_POLY_LINE:
  case XMU_QUADRATIC_EDGE:
  case XMU_PARAMETRIC_CURVE:
  case XMU_HIGHER_ORDER_EDGE:
  case XMU_CUBIC_LINE: // Cubic, isoparametric cell
  case XMU_TRIANGLE_STRIP:
  case XMU_QUADRATIC_TRIANGLE:
  case XMU_BIQUADRATIC_TRIANGLE:
  case XMU_HIGHER_ORDER_TRIANGLE:
  case XMU_HIGHER_ORDER_POLYGON:
  case XMU_QUADRATIC_POLYGON:
  case XMU_PARAMETRIC_SURFACE:
  case XMU_PARAMETRIC_TRI_SURFACE:
  case XMU_PARAMETRIC_QUAD_SURFACE:
    return fg_empty;
    break;

  // 3D dimensions
  case XMU_TETRA:
    return fg_tetra;
    break;
  case XMU_WEDGE:
    return fg_wedge;
    break;
  case XMU_VOXEL:
    return fg_voxel;
    break;
  case XMU_HEXAHEDRON:
    return fg_hexahedron;
    break;
  case XMU_PYRAMID:
    return fg_pyramid;
    break;
  case XMU_PENTAGONAL_PRISM:
    return fg_pentagonalPrism;
    break;
  case XMU_HEXAGONAL_PRISM:
    return fg_hexagonalPrism;
    break;
  case XMU_POLYHEDRON:
    // should be using cell stream
    XM_ASSERT(0);
    return fg_empty;
    break;

  // 3D Not yet supported
  case XMU_QUADRATIC_TETRA:
  case XMU_HIGHER_ORDER_TETRAHEDRON:
  case XMU_QUADRATIC_WEDGE:
  case XMU_QUADRATIC_LINEAR_WEDGE:
  case XMU_BIQUADRATIC_QUADRATIC_WEDGE:
  case XMU_HIGHER_ORDER_WEDGE:
  case XMU_QUADRATIC_HEXAHEDRON:
  case XMU_TRIQUADRATIC_HEXAHEDRON:
  case XMU_BIQUADRATIC_QUADRATIC_HEXAHEDRON:
  case XMU_HIGHER_ORDER_HEXAHEDRON:
  case XMU_QUADRATIC_PYRAMID:
  case XMU_HIGHER_ORDER_PYRAMID:
  case XMU_PARAMETRIC_TETRA_REGION:
  case XMU_PARAMETRIC_HEX_REGION:
    XM_ASSERT(0);
    return fg_empty;
    break;
  }

  XM_ASSERT(0);
  return fg_empty;
} // iGetFaceOffsetTable



//////////// plan view
//------------------------------------------------------------------------------
/// \brief Get next column of points with equal x/y values for side face.
//------------------------------------------------------------------------------
bool iGetNextFaceColumn(const XmUGridImpl& ugridGeom,
                        const VecInt& facePoints,
                        size_t starti,
                        size_t& columnBegin,
                        size_t& columnEnd)
{
  size_t facePointsSize = facePoints.size();

  // find next start of column of points (matching x/y values)
  Pt3d lastPt = ugridGeom.GetXYPoint(facePoints[starti]);
  size_t lasti = starti;
  size_t i = (starti + 1) % facePointsSize;
  Pt3d pt;
  bool found = false;
  while (!found && i != starti)
  {
    pt = ugridGeom.GetXYPoint(facePoints[i]);
    if (pt == lastPt)
    {
      columnBegin = lasti;
      found = true;
    }
    lastPt = pt;
    lasti = i;
    i = (i + 1) % facePointsSize;
  }

  if (!found)
  {
    // should have found first pair of points with matching x/y values
    return false;
  }

  // find end of column of points
  found = false;
  while (!found && i != columnBegin)
  {
    pt = ugridGeom.GetXYPoint(facePoints[i]);
    if (pt != lastPt)
    {
      columnEnd = lasti;
      found = true;
    }
    else
    {
      lastPt = pt;
      lasti = i;
      i = (i + 1) % facePointsSize;
    }
  }

  if (!found)
  {
    // should have found end of points with matching x/y values
    return false;
  }

  return true;
} // iGetNextFaceColumn

//------------------------------------------------------------------------------
/// \brief
//------------------------------------------------------------------------------
void iGetFacePointSegments(const XmUGridImpl& ugridGeom,
                           const VecInt& facePts,
                           size_t columnBegin,
                           size_t columnEnd,
                           VecPt3d& segments)
{
  size_t i = columnBegin;
  while (i != columnEnd)
  {
    Pt3d p = ugridGeom.GetXYPoint(facePts[i]);
    segments.push_back(p);
    if (i != columnBegin)
      segments.push_back(p);
    i = (i + 1) % facePts.size();
  }
  segments.push_back(ugridGeom.GetXYPoint(facePts[i]));
} // iGetFacePointSegments
//------------------------------------------------------------------------------
/// \brief
//------------------------------------------------------------------------------
bool iPointInSegmentBounds(const Pt3d& point, const Pt3d first, const Pt3d& second)
{
  bool inBounds = point.x >= std::min(first.x, second.x) &&
                  point.y >= std::min(first.y, second.y) &&
                  point.x <= std::max(first.x, second.x) && point.y <= std::max(first.y, second.y);
  return inBounds;
} // iPointInSegmentBounds
//------------------------------------------------------------------------------
/// \brief
//------------------------------------------------------------------------------
template <typename T>
std::vector<T> iGetUniquePoints(const std::vector<T>& segments)
{
  std::vector<T> points = segments;
  std::sort(points.begin(), points.end());
  auto pIt = std::unique(points.begin(), points.end());
  points.resize(pIt - points.begin());
  return points;
} // iGetUniquePoints
//------------------------------------------------------------------------------
/// \brief
//------------------------------------------------------------------------------
template <typename T>
void iBuildPolygon(std::vector<std::pair<T, T>>& segs, std::vector<T>& polygon)
{
  xms::VecChar placed(segs.size(), false);
  polygon.push_back(segs[0].first);
  polygon.push_back(segs[0].second);
  placed[0] = true;
  for (size_t i = 1; i != segs.size(); ++i)
  {
    T& toMatch = polygon.back();
    for (size_t j = 1; j != segs.size(); ++j)
    {
      if (!placed[j])
      {
        if (segs[j].first == toMatch)
        {
          polygon.push_back(segs[j].second);
          placed[j] = true;
        }
        else if (segs[j].second == toMatch)
        {
          polygon.push_back(segs[j].first);
          placed[j] = true;
        }
      }
    }
  }
} // iBuildPolygon
//------------------------------------------------------------------------------
/// \brief
//------------------------------------------------------------------------------
template <typename T>
std::vector<std::pair<T, T>> iGetUniqueSegments(const std::vector<T>& segments)
{
  std::vector<std::pair<T, T>> segs;
  for (size_t i = 0; i < segments.size(); i += 2)
  {
    T a = segments[i];
    T b = segments[i + 1];
    if (a < b)
      segs.push_back(std::pair<T, T>(a, b));
    else
      segs.push_back(std::pair<T, T>(b, a));
  }
  std::sort(segs.begin(), segs.end());
  auto segIt = std::unique(segs.begin(), segs.end());
  segs.resize(segIt - segs.begin());
  return segs;
} // iGetUniqueSegments
//------------------------------------------------------------------------------
/// \brief  Returns true if the points are equal to within gmXyTol().
/// \param x1: x of point 1.
/// \param y1: y of point 1.
/// \param x2: x of point 2.
/// \param y2: y of point 2.
/// \param tolerance: tolerance.
/// \return true if equal.
//------------------------------------------------------------------------------
bool gmEqualPointsXY(double x1, double y1, double x2, double y2, double tolerance)
{
  double dx = fabs(x1 - x2);
  double dy = fabs(y1 - y2);
  if (dx > tolerance || dy > tolerance)
    return false;
  else if (sqrt(dx * dx + dy * dy) <= tolerance)
    return true;
  else
    return false;
} // gmEqualPointsXY
//------------------------------------------------------------------------------
/// \brief   Determines if a point (x,y) is on the line defined by p1 and
///          p2. Assumes p1 and p2 aren't the same.
/// \param p1: first location defining a line
/// \param p2: second location defining a line
/// \param x: x coord of point to test
/// \param y: y coord of point to test
/// \param tol: tolerance for geometric comparison
/// \return  Returns true if the Point is on the line passing through p1 and p2
///          within the tolerance passed.
/// \note: you should always be careful to consider the case when p1 and
///          p2 are very close to each other but not to x,y.  in that case this
///          test will almost always fail because it will be more susceptible to
///          roundoff error.  if you need to know if three points are colinear
///          you should use the gmColinear function.
//------------------------------------------------------------------------------
bool gmOnLineWithTol(const Pt3d& p1,
                     const Pt3d& p2,
                     const double x,
                     const double y,
                     const double tol)
{
  // compute vector components
  double dx = p2.x - p1.x;
  double dy = p2.y - p1.y;
  double mag = sqrt((dx*dx) + (dy*dy));
  // check for extremely small segment
  if (mag <= tol)
    return gmEqualPointsXY(p1.x, p1.y, x, y, 1.0e-7);
  else
  {
    double a = -dy / mag;
    double b = dx / mag;
    double c = -a * p2.x - b * p2.y;
    // compute distance from line to (x,y)
    double d = a * x + b * y + c;
    return fabs(d) <= tol;
  }
} // gmOnLineWithTol
//------------------------------------------------------------------------------
/// \brief   Compute 2d planview projection of area of polygon.
/// \param pts: locations defining the polygon
/// \param npoints: number of pts
/// \return Area of the polygon.
///
/// CCW = positive area, CW = negative. Don't repeat the last point.
//------------------------------------------------------------------------------
double gmPolygonArea(const Pt3d* pts, size_t npoints)
{
  size_t id;
  double area = 0.0;

  if (npoints < 3)
    return area;

  /* original method with precision errors
  for (id = 0; id < npoints; id++)
  {
    if (id != (npoints - 1))
    {
      area += (pts[id].x * pts[id + 1].y);
      area -= (pts[id].y * pts[id + 1].x);
    }
    else
    {
      area += (pts[id].x * pts[0].y);
      area -= (pts[id].y * pts[0].x);
    }
  }
  area /= 2.0;
  */

  // AKZ 2/15/2018
  // I changed the implementation to translate the polygon
  //   so that the first point is at the origin
  // Reduces round off error due to large coordinates
  // Reduces the number of computations because the first and last
  //   computations in the loop would be 0.0
  VecDbl x, y;
  double x0 = pts[0].x;
  double y0 = pts[0].y;
  for (id = 1; id < npoints; id++)
  {
    x.push_back((pts[id].x - x0));
    y.push_back((pts[id].y - y0));
  }
  for (id = 0; id < npoints - 2; id++)
  {
    area += (x[id] * y[id + 1]);
    area -= (y[id] * x[id + 1]);
  }
  area /= 2.0;

  return (area);
} // gmPolygonArea
//------------------------------------------------------------------------------
/// \brief Computes the plan view centroid of a non-self-intersecting polygon.
/// \param[in] pts: Points.
/// \return Centroid.
//------------------------------------------------------------------------------
Pt3d gmComputePolygonCentroid(const VecPt3d& pts)
{
  Pt3d centroid;
  if (pts.empty())
    return centroid;
  // get offset to use in calculation below to fix precision issues
  double xMax = XM_DBL_LOWEST, yMax = XM_DBL_LOWEST, xMin = XM_DBL_HIGHEST, yMin = XM_DBL_HIGHEST;
  size_t i = 0;
  for (i = 0; i < pts.size(); ++i)
  {
    double x = pts[i].x;
    double y = pts[i].y;
    xMax = (x > xMax) ? x : xMax;
    yMax = (y > yMax) ? y : yMax;
    xMin = (x < xMin) ? x : xMin;
    yMin = (y < yMin) ? y : yMin;
  }
  double xOffset = (xMax + xMin) / 2.0;
  double yOffset = (yMax + yMin) / 2.0;
  // For all vertices except last
  double signedArea = 0.0;
  for (i = 0; i < pts.size() - 1; ++i)
  {
    double x0 = pts[i].x - xOffset;
    double y0 = pts[i].y - yOffset;
    double x1 = pts[i + 1].x - xOffset;
    double y1 = pts[i + 1].y - yOffset;
    double a = x0 * y1 - x1 * y0;
    signedArea += a;
    centroid.x += (x0 + x1) * a;
    centroid.y += (y0 + y1) * a;
  }
  // Do last vertex
  double x0 = pts[i].x - xOffset;
  double y0 = pts[i].y - yOffset;
  double x1 = pts[0].x - xOffset;
  double y1 = pts[0].y - yOffset;
  double a = x0 * y1 - x1 * y0;
  signedArea += a;
  centroid.x += (x0 + x1) * a;
  centroid.y += (y0 + y1) * a;
  signedArea *= 0.5;
  centroid.x /= (6.0 * signedArea);
  centroid.y /= (6.0 * signedArea);
  centroid.x += xOffset;
  centroid.y += yOffset;
  return centroid;
} // gmComputePolygonCentroid
//------------------------------------------------------------------------------
/// \brief
//------------------------------------------------------------------------------
void iMergeSegmentsToPoly(const VecPt3d& segments, VecPt3d& polygon)
{
  if (segments.empty())
    return;

  VecPt3d points = iGetUniquePoints(segments);
  std::vector<std::pair<Pt3d, Pt3d>> segs = iGetUniqueSegments(segments);

  // if any point is on any other segment split up the segment
  for (auto pIt = points.begin(); pIt != points.end(); ++pIt)
  {
    size_t segsSize = segs.size();
    for (size_t i = 0; i < segsSize; ++i)
    {
      Pt3d pt1 = segs[i].first;
      Pt3d pt2 = segs[i].second;
      if (*pIt != pt1 && *pIt != pt2 && iPointInSegmentBounds(*pIt, pt1, pt2))
      {
        Pt3d diff = pt1 - pt2;
        double distance = std::max(fabs(diff.x), fabs(diff.y));
        double tolerance = distance / 1.0e6;
        if (gmOnLineWithTol(pt1, pt2, pIt->x, pIt->y, tolerance))
        {
          segs.push_back(std::pair<Pt3d, Pt3d>(*pIt, pt2));
          segs[i].second = *pIt;
        }
      }
    }
  }
  std::sort(segs.begin(), segs.end());
  auto segIt = std::unique(segs.begin(), segs.end());
  segs.resize(segIt - segs.begin());

  iBuildPolygon(segs, polygon);

  if (polygon.size() > 3 && polygon.front() == polygon.back())
  {
    polygon.pop_back();
    double area = gmPolygonArea(&polygon[0], (int)polygon.size());
    if (area < 0)
      std::reverse(polygon.begin(), polygon.end());
  }
  else
  {
    XM_ASSERT(0);
    polygon.clear();
  }
} // iMergeSegmentsToPoly


////////////////////////////////////////////////////////////////////////////////
/// \class XmUGrid
/// \brief Implementation for XmUGrid which provides geometry for an
///        unstructured grid.
////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
/// \brief Default constructor.
//------------------------------------------------------------------------------
XmUGridImpl::XmUGridImpl()
{
} // XmUGridImpl::XmUGridImpl
// Points
//------------------------------------------------------------------------------
/// \brief Get the number of points.
/// \return the number of points
//------------------------------------------------------------------------------
int XmUGridImpl::GetNumberOfPoints() const
{
  return (int)m_points.size();
} // XmUGridImpl::GetNumberOfPoints
//------------------------------------------------------------------------------
/// \brief Get vector of UGrid points.
/// \return constant reference to vector of points
//------------------------------------------------------------------------------
const VecPt3d& XmUGridImpl::GetPoints() const
{
  return m_points;
} // XmUGridImpl::GetPoints
//------------------------------------------------------------------------------
/// \brief Set UGrid points.
/// \param[in] a_points: the points
//------------------------------------------------------------------------------
void XmUGridImpl::SetPoints(const VecPt3d& a_points)
{
  m_points = a_points;
} // XmUGridImpl::SetPoints
//------------------------------------------------------------------------------
/// \brief Get the point
/// \param[in] a_pointIdx: the index of the point
/// \return the point or an initialize point if the index is invalid
//------------------------------------------------------------------------------
Pt3d XmUGridImpl::GetPoint(const int a_pointIdx) const
{
  if (a_pointIdx >= 0 && a_pointIdx < m_points.size())
    return m_points[a_pointIdx];
  return Pt3d();
} // XmUGridImpl::GetPoint
//------------------------------------------------------------------------------
/// \brief Set the point
/// \param[in] a_pointIdx: the index of the point
/// \param[in] a_point: The point that will replace the data of the specified
///            point in the UGrid
/// \return whether the point was successfully set
//------------------------------------------------------------------------------
bool XmUGridImpl::SetPoint(const int a_pointIdx, const Pt3d& a_point)
{
  if (a_pointIdx >= 0 && a_pointIdx < m_points.size())
  {
    VecInt affectedCells = GetPointCells(a_pointIdx);
    bool badCell = false;
    for (int i(0); i < affectedCells.size(); i++)
    {
      if (!IsCellValidWithPointChange(affectedCells[i], a_pointIdx, a_point))
      {
        badCell = true;
        break;
      }
    }
    if (!badCell)
    {
      m_points[a_pointIdx] = a_point;
      return true;
    }
    return false;
  }
  return false;
} // XmUGridImpl::SetPoint

//------------------------------------------------------------------------------
/// \brief Get the X, Y location of a point.
/// \param[in] a_pointIdx The index of the point.
/// \return The location of the point with Z set to 0.0.
//------------------------------------------------------------------------------
Pt3d XmUGridImpl::GetXYPoint(const int a_pointIdx) const
{
  Pt3d pt = GetPoint(a_pointIdx);
  pt.z = 0.0;
  return pt;
} // XmUGridImpl::GetXYPoint

//------------------------------------------------------------------------------
/// \brief Convert a vector of point indices into a vector of point 3d
/// \param[in] a_points: a vector of point indices
/// \return vector of point 3d
//------------------------------------------------------------------------------
VecPt3d XmUGridImpl::GetPointsFromPointIdxs(const VecInt& a_points) const
{
  VecPt3d point3d;
  for (int i(0); i < a_points.size(); i++)
  {
    point3d.push_back(GetPoint(a_points[i]));
  }
  return point3d;
} // XmUGridImpl::GetPointsFromPointIdxs

//------------------------------------------------------------------------------
/// \brief Get extents of all points in UGrid
/// \param[out] a_min: minimum extent of all points
/// \param[out] a_max: maximum extent of all points
//------------------------------------------------------------------------------
void XmUGridImpl::GetExtents(Pt3d& a_min, Pt3d& a_max) const
{
  GetExtentsFromPoints(m_points,a_min,a_max);
} // XmUGridImpl::GetExtents

//------------------------------------------------------------------------------
/// \brief Get the cells that are associated with the specified point
/// \param[in] a_pointIdx: the index of the point
/// \return a vector of the cell indexes associated with this point
//------------------------------------------------------------------------------
VecInt XmUGridImpl::GetPointCells(const int a_pointIdx) const
{
  VecInt cellsOfPoint;
  GetPointCells(a_pointIdx, cellsOfPoint);
  return cellsOfPoint;
} // XmUGridImpl::GetPointCells
//------------------------------------------------------------------------------
/// \brief Get the cells that are associated with the specified point
/// \param[in] a_pointIdx: the index of the point
/// \param[out] a_attachedCellIdxs a vector of the cell indexes associated with
///             the point
/// \return a vector of the cell indexes associated with this point
//------------------------------------------------------------------------------
void XmUGridImpl::GetPointCells(const int a_pointIdx, VecInt& a_attachedCellIdxs) const
{
  a_attachedCellIdxs.clear();
  if (a_pointIdx < 0 || a_pointIdx >= m_points.size())
    return;
  int numCells = m_pointsToCells[m_pointIdxToPointsToCells[a_pointIdx]];
  for (int cellIdx = 0; cellIdx < numCells; cellIdx++)
  {
    a_attachedCellIdxs.push_back(
      m_pointsToCells[m_pointIdxToPointsToCells[a_pointIdx] + cellIdx + 1]);
  }
} // XmUGridImpl::GetPointCells
//------------------------------------------------------------------------------
/// \brief Gets the common cells from a vector of points
/// \param[in] a_points: a vector of unique points
/// \return a vector of cell indices
//------------------------------------------------------------------------------
VecInt XmUGridImpl::GetCommonCells(const VecInt& a_points) const
{
  VecInt commonCells;
  if (!a_points.empty())
    GetCommonCells(&a_points[0], (int)a_points.size(), commonCells);
  return commonCells;
} // XmUGridImpl::GetCommonCells
//------------------------------------------------------------------------------
/// \brief Gets the common cells from a vector of points
/// \param[in] a_pointIdxs: an array of point indexes
/// \param[in] a_numPointIdxs: number of points in array
/// \param[out] a_commonCellIdxs a vector of cell indices
//------------------------------------------------------------------------------
void XmUGridImpl::GetCommonCells(const int* a_pointIdxs,
                                 int a_numPointIdxs,
                                 VecInt& a_commonCellIdxs) const
{
  a_commonCellIdxs.clear();
  if (a_numPointIdxs == 0)
    return;
  a_commonCellIdxs = GetPointCells(a_pointIdxs[0]);
  for (int i = 1; i < a_numPointIdxs; ++i)
  {
    VecInt tempAssociatedCells = GetPointCells(a_pointIdxs[i]);
    VecInt remove;
    for (int j = 0; j < a_commonCellIdxs.size(); ++j)
    {
      bool found = false;
      for (int k = 0; k < tempAssociatedCells.size(); ++k)
      {
        if (a_commonCellIdxs[j] == tempAssociatedCells[k])
        {
          found = true;
          break;
        }
      }
      if (!found)
        remove.push_back(j);
    }
    for (int j = (int)remove.size() - 1; j >= 0; --j)
    {
      a_commonCellIdxs.erase(a_commonCellIdxs.begin() + remove[j]);
    }
    if (a_commonCellIdxs.size() == 0)
      break;
  }
} // XmUGridImpl::GetCommonCells
//------------------------------------------------------------------------------
/// \brief Gets the common cells from a vector of points
/// \param[in] a_points a vector of unique points
/// \param[out] a_commonCellIdxs a vector of cell indices
//------------------------------------------------------------------------------
void XmUGridImpl::GetCommonCells(const VecInt& a_points, VecInt& a_commonCellIdxs) const
{
  if (!a_points.empty())
    GetCommonCells(&a_points[0], (int)a_points.size(), a_commonCellIdxs);
} // XmUGridImpl::GetCommonCells
//------------------------------------------------------------------------------
/// \brief Gets the common cells for two points.
/// \param[in] a_idx1 first point index
/// \param[in] a_idx2 second point index
/// \param[out] a_commonCellIdxs a vector of cell indices
//------------------------------------------------------------------------------
void XmUGridImpl::GetCommonCells(const int a_idx1, const int a_idx2, VecInt& a_commonCellIdxs) const
{
  int points[] = {a_idx1, a_idx2};
  GetCommonCells(points, 2, a_commonCellIdxs);
} // XmUGridImpl::GetCommonCells
// Cells
//------------------------------------------------------------------------------
/// \brief Get the number of cells.
/// \return the number of cells
//------------------------------------------------------------------------------
int XmUGridImpl::GetNumberOfCells() const
{
  if (m_cellIdxToStreamIdx.empty())
    return 0;
  else
    return (int)m_cellIdxToStreamIdx.size() - 1;
} // XmUGridImpl::GetNumberOfCells
//------------------------------------------------------------------------------
/// \brief Get the points of a cell (including polyhedron)
/// \param[in] a_cellIdx: the index of the cell
/// \return a vector of point indices
//------------------------------------------------------------------------------
VecInt XmUGridImpl::GetPointsOfCell(const int a_cellIdx) const
{
  VecInt pointsOfCell;
  GetPointsOfCell(a_cellIdx, pointsOfCell);
  return pointsOfCell;
} // XmUGridImpl::GetPointsOfCell

//------------------------------------------------------------------------------
/// \brief Get the points of a cell.
/// \param[in] a_cellIdx: the index of the cell
/// \param[out] a_cellPoints: the points of the cell
/// \return if the cell index is valid
//------------------------------------------------------------------------------
bool XmUGridImpl::GetPointsOfCell(const int a_cellIdx, VecInt& a_cellPoints) const
{
  a_cellPoints.clear();
  VecInt cellStream;
  if (GetSingleCellStream(a_cellIdx, cellStream))
  {
    XM_ENSURE_TRUE_NO_ASSERT(!cellStream.empty(), false);
    int cellType = cellStream[0];
    if (cellType == XMU_POLYHEDRON)
    {
      GetUniquePointsFromPolyhedronSingleCellStream(cellStream, a_cellPoints);
      return true;
    }
    else if (cellType == XMU_PIXEL)
    {
      a_cellPoints.push_back(cellStream[2]);
      a_cellPoints.push_back(cellStream[3]);
      a_cellPoints.push_back(cellStream[5]);
      a_cellPoints.push_back(cellStream[4]);
      return true;
    }
    else
    {
      a_cellPoints.assign(cellStream.begin() + 2, cellStream.end());
      return true;
    }
  }
  return false;
} // XmUGridImpl::GetPointsOfCell

//------------------------------------------------------------------------------
/// \brief
//------------------------------------------------------------------------------
void XmUGridImpl::GetPointsOfCell(const int a_cellIdx,VecPt3d& a_cellPoints) const
{
  VecInt ptIdxs = GetPointsOfCell(a_cellIdx);
  a_cellPoints = GetPointsFromPointIdxs(ptIdxs);
} // XmUGridImpl::GetPointsOfCell

//------------------------------------------------------------------------------
/// \brief Get the number of cells.
/// \param[in] a_cellIdx: the index of the cell
/// \return the number of cells or -1 if invalid index
//------------------------------------------------------------------------------
XmUGridCellType XmUGridImpl::GetCellType(const int a_cellIdx) const
{
  if (m_cellIdxToStreamIdx.size() < 2 || a_cellIdx > m_cellIdxToStreamIdx.size() - 2)
  {
    return XMU_INVALID_CELL_TYPE;
  }
  else
  {
    int cellStart = m_cellIdxToStreamIdx[a_cellIdx];
#if _DEBUG
    if ((m_cellStream[cellStart] > XMU_PYRAMID) && (m_cellStream[cellStart] != XMU_POLYHEDRON) ||
        (m_cellStream[cellStart] == XMU_TRIANGLE_STRIP))
    {
      assert("UNSUPPORTED TYPE!");
    }
#endif
    return (XmUGridCellType)m_cellStream[cellStart];
  }
} // XmUGridImpl::GetCellType
//------------------------------------------------------------------------------
/// \brief Count all number of the cells with each dimenion (0, 1, 2, 3)
/// \return the count of dimensions of all of the cells of the ugrid
//------------------------------------------------------------------------------
std::vector<int> XmUGridImpl::GetDimensionCount() const
{
  std::vector<int> m_dimensionCounts(4, 0);
  int itemp(0);
  for (int i(0); i < m_cellIdxToStreamIdx.size() - 1; i++)
  {
    itemp = GetCellDimension(i);
    if (itemp >= 0)
    {
      m_dimensionCounts[itemp]++;
    }
  }
  return m_dimensionCounts;
} // XmUGridImpl::GetDimensionCount
//------------------------------------------------------------------------------
/// \brief Get the dimension of the specified cell.
/// \param[in] a_cellIdx: the index of the cell
/// \return the dimension of the cells or -1 if invalid index or invalid
/// dimension
//------------------------------------------------------------------------------
int XmUGridImpl::GetCellDimension(const int a_cellIdx) const
{
  return DimensionFromCellType(GetCellType(a_cellIdx));
} // XmUGridImpl::GetCellDimension

//------------------------------------------------------------------------------
/// \brief Get the extents of the given cell.
/// \param[in] a_cellIdx The cell index to get the extents of.
/// \param[out] a_min The minimum location.
/// \param[out] a_max The maximum location.
//------------------------------------------------------------------------------
void XmUGridImpl::GetCellExtents(const int a_cellIdx, Pt3d& a_min, Pt3d& a_max) const
{
  VecPt3d pts;
  GetPointsOfCell(a_cellIdx, pts);
  GetExtentsFromPoints(pts, a_min, a_max);
} // XmUGridImpl::GetCellExtents

//------------------------------------------------------------------------------
/// \brief Get cell stream vector for the entire UGrid.
/// \return constant reference to the cell stream vector
//------------------------------------------------------------------------------
const VecInt& XmUGridImpl::GetCellStream() const
{
  return m_cellStream;
} // XmUGridImpl::GetCellStream
//! [snip_test_SetCellStream]
//------------------------------------------------------------------------------
/// \brief Set the ugrid cells for the entire UGrid using a cell stream.
/// \param[in] a_cellStream: cells defined as follows:
///              Hexahedrons, polygons, quads, triangles etc:
///                Cell type (ElemTypeEnum), number of points, point numbers.
///                Generally 1-based, CCW, bottom, then top. Not true
///                for pixel or voxel.
///              Polyhedrons:
///                Cell type, number of faces, [num points in face,
///                point numbers (1-based, CCW when looking in)] repeated
///                for each face.
/// \return if successfully set
//------------------------------------------------------------------------------
bool XmUGridImpl::SetCellStream(const VecInt& a_cellStream)
{
  if (ValidCellStream(a_cellStream))
  {
    m_cellStream = a_cellStream;
    UpdateLinks();
    return true;
  }
  else
  {
    XM_LOG(xmlog::error, "Invalid cell stream data.");
    return false;
  }
} // XmUGridImpl::SetCellStream
//! [snip_test_SetCellStream]
//------------------------------------------------------------------------------
/// \brief Get cell stream vector for a single cell.
/// \param[in] a_cellIdx: the index of the cell
/// \param[in] a_cellStream: The cellstream of the cell
/// @see SetCellStream for more detail on cell stream definitions.
/// \return whether it was successfull or not
//------------------------------------------------------------------------------
bool XmUGridImpl::GetSingleCellStream(const int a_cellIdx, VecInt& a_cellStream) const
{
  a_cellStream.clear();
  if (m_cellIdxToStreamIdx.size() < 2 || a_cellIdx > m_cellIdxToStreamIdx.size() - 2)
  {
    return false;
  }
  int startIndex(m_cellIdxToStreamIdx[a_cellIdx]), endIndex(m_cellIdxToStreamIdx[a_cellIdx + 1]);
  a_cellStream.assign(m_cellStream.begin() + startIndex, m_cellStream.begin() + endIndex);
  return true;
} // XmUGridImpl::GetSingleCellStream

//------------------------------------------------------------------------------
/// \brief Get the cells neighboring a cell (cells associated with any of it's points)
/// \param[in] a_cellIdx: the index of the cell
/// \return vector of cell indices
//------------------------------------------------------------------------------
VecInt XmUGridImpl::GetCellNeighbors(const int a_cellIdx) const
{
  VecInt neighbors;
  GetCellNeighbors(a_cellIdx, neighbors);
  return neighbors;
} // XmUGridImpl::GetCellNeighbors
//------------------------------------------------------------------------------
/// \brief Get the cells neighboring a cell (cells associated with any of it's points)
/// \param[in] a_cellIdx: the index of the cell
/// \param[out] a_cellNeighbors vector of cell indices
//------------------------------------------------------------------------------
void XmUGridImpl::GetCellNeighbors(const int a_cellIdx, VecInt& a_cellNeighbors) const
{
  a_cellNeighbors.clear();
  VecInt pointsOfCell;
  pointsOfCell = GetPointsOfCell(a_cellIdx);
  for (int i = 0; i < pointsOfCell.size(); i++)
  {
    VecInt associatedCells = GetPointCells(pointsOfCell[i]);
    for (int j = 0; j < associatedCells.size(); j++)
    {
      if (associatedCells[j] != a_cellIdx)
      {
        bool found(false);
        for (int k = 0; k < a_cellNeighbors.size(); k++)
        {
          if (a_cellNeighbors[k] == associatedCells[j])
          {
            found = true;
          }
        }
        if (!found)
        {
          a_cellNeighbors.push_back(associatedCells[j]);
        }
      }
    }
  }
} // XmUGridImpl::GetCellNeighbors
//------------------------------------------------------------------------------
/// \brief Get a plan view polygon of a specified cell
/// \param[in] a_cellIdx The index of the cell.
/// \param[out] a_polygon Vector of Pt3d that is the plan view polygon.
/// \return False if the cell index does not exist or if the cell is not 2 or 3 dimensional.
//------------------------------------------------------------------------------
bool XmUGridImpl::GetPlanViewPolygon(int a_cellIdx, VecPt3d& a_polygon) const
{
  a_polygon.clear();
  if (a_cellIdx < 0 || a_cellIdx >= GetNumberOfCells())
    return false;
  int dimension = GetCellDimension(a_cellIdx);
  if (dimension == 3)
    return GetPlanViewPolygon3d(a_cellIdx, a_polygon);
  else if (dimension == 2)
    return GetPlanViewPolygon2d(a_cellIdx, a_polygon);
  else
    return false;
} // XmUGridImpl::GetPlanViewPolygon

//------------------------------------------------------------------------------
/// \brief Get the centroid location of a cell.
/// \param[in] a_cellIdx The index of the cell.
/// \param[out] a_centroid The location of the cell centroid.
/// \return False if the cell index does not exist.
//------------------------------------------------------------------------------
bool XmUGridImpl::GetCentroid(int a_cellIdx, Pt3d& a_centroid) const
{
  VecPt3d pts;
  bool retVal = true;
  Pt3d centroid= Pt3d(0.0, 0.0, 0.0);
  if (GetPlanViewPolygon(a_cellIdx, pts))
  {
    centroid = gmComputePolygonCentroid(pts);
  }
  else if (a_cellIdx < 0 || a_cellIdx >= GetNumberOfCells())
  {
    retVal = false;
  }
  else
  {
    VecPt3d pts;
    GetPointsOfCell(a_cellIdx, pts);
    for (Pt3d& pt : pts)
    {
      centroid += pt;
    }
    centroid /= (double)pts.size();
  }
  a_centroid = centroid;
  return retVal;
} // XmUGridImpl::GetCentroid

//------------------------------------------------------------------------------
/// \brief Determine whether a cell is valid after a point is moved.
/// \param[in] a_cellIdx: the index of the cell
/// \param[in] a_changedPtIdx: index of the point to be changed
/// \param[in] a_newPosition: location the point is to be moved to
/// \return whether the cell is valid
//------------------------------------------------------------------------------
bool XmUGridImpl::IsCellValidWithPointChange(const int a_cellIdx,
                                             const int a_changedPtIdx,
                                             const Pt3d& a_newPosition) const
{
  if (GetCellDimension(a_cellIdx) == 2)
  {
    std::vector<std::pair<int, int>> edges = GetEdgesOfCell(a_cellIdx);
    return !DoEdgesCrossWithPointChange(a_changedPtIdx, a_newPosition, edges);
  }
  else if (GetCellDimension(a_cellIdx) == 3)
  {
    //  Go through the affected faces and if they are not a side face
    // check if the edges cross each other
    VecInt2d faces = GetFacesOfCell(a_cellIdx);
    for (int faceIdx = 0; faceIdx < faces.size(); faceIdx++)
    {
      bool faceIsAffected = false;
      for (int ptIdx = 0; ptIdx < faces[faceIdx].size(); ptIdx++)
      {
        if (faces[faceIdx][ptIdx] == a_changedPtIdx)
        {
          faceIsAffected = true;
        }
      }
      if (faceIsAffected)
      {
        std::vector<std::pair<int, int>> edges;
        GetEdgesOfFace(faces[faceIdx], edges);
        if (DoEdgesCrossWithPointChange(a_changedPtIdx, a_newPosition, edges))
          return false;
      }
    }
  }
  return true;
} // XmUGridImpl::IsCellValidWithPointChange
//------------------------------------------------------------------------------
/// \brief Get the edges of a cell given a face
/// \param[in] a_face: a vector of point indices of a face
/// \param[out] a_edges: a vector of point indices of an edge
//------------------------------------------------------------------------------
void XmUGridImpl::GetEdgesOfFace(const VecInt& a_face,
                                 std::vector<std::pair<int, int>>& a_edges) const
{
  a_edges.reserve(a_face.size());
  for (int i = 1; i < a_face.size(); ++i)
  {
    a_edges.push_back(std::pair<int, int>(a_face[i - 1], a_face[i]));
  }
  if (a_edges.size() > 1)
    a_edges.push_back(std::pair<int, int>(a_face[a_face.size() - 1], a_face[0]));
} // XmUGridImpl::GetEdgesOfFace

//------------------------------------------------------------------------------
/// \brief Gets whether or not edges cross with a point change
/// \param[out] a_edges: The edges to check
/// \param[in] a_changedPtIdx: index of the point to be changed
/// \param[in] a_newPosition: location the point is to be moved to
/// \return whether the edges cross
//------------------------------------------------------------------------------
bool XmUGridImpl::DoEdgesCrossWithPointChange(const int a_changedPtIdx,
                                              const Pt3d& a_newPosition,
                                              const std::vector<std::pair<int, int>>& a_edges) const
{
  std::vector<std::pair<Pt3d, Pt3d>> changedEdges;
  std::vector<std::pair<Pt3d, Pt3d>> unChangedEdges;
  for (int i = 0; i < a_edges.size(); ++i)
  {
    if (a_edges[i].first == a_changedPtIdx)
    {
      changedEdges.push_back(std::pair<Pt3d, Pt3d>(a_newPosition, GetPoint(a_edges[i].second)));
    }
    else if (a_edges[i].second == a_changedPtIdx)
    {
      changedEdges.push_back(std::pair<Pt3d, Pt3d>(GetPoint(a_edges[i].first), a_newPosition));
    }
    else
    {
      unChangedEdges.push_back(
        std::pair<Pt3d, Pt3d>(GetPoint(a_edges[i].first), GetPoint(a_edges[i].second)));
    }
  }
  for (int i = 0; i < changedEdges.size(); ++i)
  {
    for (int j = 0; j < unChangedEdges.size(); ++j)
    {
      if (DoLineSegmentsCross(changedEdges[i], unChangedEdges[j]))
        return true;
    }
  }
  return false;
} // XmUGridImpl::DoEdgesCrossWithPointChange
// Edges
//------------------------------------------------------------------------------
/// \brief Get the number of edges for a cell.
/// \param[in] a_cellIdx: the index of the cell
/// \return the count of cell edges
//------------------------------------------------------------------------------
int XmUGridImpl::GetNumberOfCellEdges(const int a_cellIdx) const
{
  int cellType(GetCellType(a_cellIdx));
  switch (cellType)
  {
  // invalid
  case XMU_INVALID_CELL_TYPE:
    return -1;
    break;

  case XMU_POLY_LINE:
    return GetNumberOfItemsForCell(a_cellIdx) - 1;
    break;

  case XMU_POLYGON:
    return GetNumberOfItemsForCell(a_cellIdx);
    break;

  case XMU_POLYHEDRON:
    return GetNumberOfPolyhedronEdges(a_cellIdx);
    break;

  default:
  {
    const VecEdge& edgeTable = iGetEdgeOffsetTable(cellType);
    if (!edgeTable.empty())
      return (int)edgeTable.size();
    break;
  }
  }

  XM_ASSERT(0);
  return -1;
} // XmUGridImpl::GetNumberOfCellEdges
//------------------------------------------------------------------------------
/// \brief Get the points of a cell.
/// \param[in] a_cellIdx: the index of the cell
/// \param[in] a_edgeIdx: the index of the edge
/// \return a standard pair of point indexes (which is an edge)
//------------------------------------------------------------------------------
std::pair<int, int> XmUGridImpl::GetCellEdgeFromEdgeIndex(const int a_cellIdx,
                                                          const int a_edgeIdx) const
{
  std::pair<int, int> edge;
  if (a_edgeIdx < 0)
    return edge;

  const int* cellStream = nullptr;
  int streamLength;
  GetSingleCellStream(a_cellIdx, &cellStream, streamLength);
  if (cellStream)
  {
    if (streamLength < 4)
      return edge;

    int cellType = cellStream[0];
    switch (cellType)
    {
    case XMU_POLY_LINE:
    case XMU_POLYGON:
    {
      int numPoints = cellStream[1];
      const int* cellPoints = cellStream + 2;
      int idx1 = cellPoints[a_edgeIdx];
      int idx2 = cellPoints[(a_edgeIdx + 1) % numPoints];
      edge = std::pair<int, int>(idx1, idx2);
      break;
    }

    case XMU_POLYHEDRON:
    {
      boost::container::flat_set<std::pair<int, int>> cellEdges;
      int currIdx = 2;
      GetUniqueEdgesFromPolyhedronCellStream(cellStream, streamLength, cellEdges, currIdx);

      if (a_edgeIdx < (int)cellEdges.size())
        edge = *(cellEdges.begin() + a_edgeIdx);
      break;
    }

    default:
    {
      const VecEdge& edgeTable = iGetEdgeOffsetTable(cellType);
      if (a_edgeIdx < (int)edgeTable.size())
      {
        const std::pair<int, int>& edgeOffset = edgeTable[a_edgeIdx];
        const int* cellPoints = cellStream + 2;
        int idx1 = cellPoints[edgeOffset.first];
        int idx2 = cellPoints[edgeOffset.second];
        edge = std::pair<int, int>(idx1, idx2);
      }
      break;
    }
    }
  }

  return edge;
} // XmUGridImpl::GetCellEdgeFromEdgeIndex
//------------------------------------------------------------------------------
/// \brief Get the index of the adjacent cells (that shares the same cell edge)
/// \param[in] a_cellIdx: the index of the cell
/// \param[in] a_edgeIdx: the index of the edge
/// \return a vector of cell indices of the adjacent cells
//------------------------------------------------------------------------------
VecInt XmUGridImpl::GetAdjacentCells(const int a_cellIdx, const int a_edgeIdx) const
{
  VecInt adjacentCells;
  GetAdjacentCells(a_cellIdx, a_edgeIdx, adjacentCells);
  return adjacentCells;
} // XmUGridImpl::GetAdjacentCells
//------------------------------------------------------------------------------
/// \brief Get the index of the adjacent cells (that shares the same cell edge)
/// \param[in] a_cellIdx: the index of the cell
/// \param[in] a_edgeIdx: the index of the edge
/// \param[out] a_adjacentCellIdxs a vector of cell indices of the adjacent
///             cells
//------------------------------------------------------------------------------
void XmUGridImpl::GetAdjacentCells(const int a_cellIdx,
                                   const int a_edgeIdx,
                                   VecInt& a_adjacentCellIdxs) const
{
  a_adjacentCellIdxs.clear();
  VecInt adjacentCells;
  VecInt cellNeighbors = GetCellNeighbors(a_cellIdx);
  if (cellNeighbors.size() == 0)
  {
    return;
  }
  if (a_edgeIdx < 0 && a_edgeIdx >= GetNumberOfCellEdges(a_cellIdx))
  {
    return;
  }

  std::pair<int, int> currEdge, neighborEdge;
  currEdge = GetCellEdgeFromEdgeIndex(a_cellIdx, a_edgeIdx);
  for (int j(0); j < cellNeighbors.size(); j++)
  {
    for (int k(0); k < GetNumberOfCellEdges(cellNeighbors[j]); k++)
    {
      neighborEdge = GetCellEdgeFromEdgeIndex(cellNeighbors[j], k);
      if (iEdgesEquivalent(currEdge, neighborEdge))
      {
        a_adjacentCellIdxs.push_back(cellNeighbors[j]);
      }
    }
  }
} // XmUGridImpl::GetAdjacentCells
//------------------------------------------------------------------------------
/// \brief Get the index of the adjacent cells (that shares the same cell edge)
/// \param[in] a_cellIdx: the index of the cell
/// \param[in] a_edgeIdx: the index of the edge
/// \return a vector of cell indices of the adjacent cells
//------------------------------------------------------------------------------
int XmUGridImpl::Get2dAdjacentCell(const int a_cellIdx, const int a_edgeIdx) const
{
  VecInt adjacentCells = GetAdjacentCells(a_cellIdx, a_edgeIdx);
  if (adjacentCells.size() == 1)
  {
    return adjacentCells[0];
  }
  else if (adjacentCells.size() == 0)
  {
    return -1;
  }
  else
  {
    assert("This is a 2D Function!");
    return -1;
  }
} // XmUGridImpl::Get2dAdjacentCell

//------------------------------------------------------------------------------
/// \brief Get the indices of the adjacent cells (that shares the same cell edge)
/// \param[in] a_pointIdx1: the index of the first point
/// \param[in] a_pointIdx2: the index of the second point
/// \return a vector of cell indices of the adjacent cells
//------------------------------------------------------------------------------
VecInt XmUGridImpl::GetAdjacentCellsFromGivenEdge(const int a_pointIdx1,
                                                  const int a_pointIdx2) const
{
  VecInt adjacentCellIdxs;
  GetCommonCells(a_pointIdx1, a_pointIdx2, adjacentCellIdxs);
  return adjacentCellIdxs;
} // XmUGridImpl::GetAdjacentCellsFromGivenEdge
//------------------------------------------------------------------------------
/// \brief Get the indices of the adjacent cells (that shares the same cell edge)
/// \param[in] a_pointIdx1: the index of the first point
/// \param[in] a_pointIdx2: the index of the second point
/// \param[out] a_adjacentCellIdxs a vector of cell indices of the adjacent cells
//------------------------------------------------------------------------------
void XmUGridImpl::GetAdjacentCellsFromGivenEdge(const int a_pointIdx1,
                                                const int a_pointIdx2,
                                                VecInt& a_adjacentCellIdxs) const
{
  return GetCommonCells(a_pointIdx1, a_pointIdx2, a_adjacentCellIdxs);
} // XmUGridImpl::GetAdjacentCellsFromGivenEdge
//------------------------------------------------------------------------------
/// \brief Get the index of the adjacent cells (that shares the same cell edge)
/// \param[in] a_edge: the edge (a pair of point indexes)
/// \return a vector of cell indices of the adjacent cells
//------------------------------------------------------------------------------
VecInt XmUGridImpl::GetAdjacentCellsFromGivenEdge(const std::pair<int, int> a_edge) const
{
  return GetAdjacentCellsFromGivenEdge(a_edge.first, a_edge.second);
} // XmUGridImpl::GetAdjacentCellsFromGivenEdge

//------------------------------------------------------------------------------
/// \brief Get the Edges associated with a point.
/// \param[in] a_pointId: the point
/// \param[in] a_cellIdxs: the cells to whom the edges belong
/// \param[in] a_edgeIdxs: the index of the edge connected to the point
/// \return true if operation was successful
//------------------------------------------------------------------------------
bool XmUGridImpl::GetEdgesFromPoint(const int a_pointId,
                                    VecInt& a_cellIdxs,
                                    VecInt& a_edgeIdxs) const
{
  a_edgeIdxs.clear();
  a_cellIdxs.clear();
  VecInt associatedCells = GetPointCells(a_pointId);
  if (associatedCells.size() == 0)
    return false;
  for (int i = 0; i < associatedCells.size(); ++i)
  {
    for (int j = 0; j < GetNumberOfCellEdges(associatedCells[i]); ++j)
    {
      std::pair<int, int> temp = GetCellEdgeFromEdgeIndex(associatedCells[i], j);
      if (temp.first == a_pointId || temp.second == a_pointId)
      {
        a_edgeIdxs.push_back(j);
        a_cellIdxs.push_back(associatedCells[i]);
      }
    }
  }
  return true;
} // XmUGridImpl::GetEdgesFromPoint
//------------------------------------------------------------------------------
/// \brief Get the Edges of a cell.
/// \param[in] a_cellIdx: the cells to whom the edges belong
/// \return a vector of edges (organized in std::pairs)
//------------------------------------------------------------------------------
std::vector<std::pair<int, int>> XmUGridImpl::GetEdgesOfCell(const int a_cellIdx) const
{
  std::vector<std::pair<int, int>> edges;
  GetEdgesOfCell(a_cellIdx, edges);
  return edges;
} // XmUGridImpl::GetEdgesOfCell
//------------------------------------------------------------------------------
/// \brief Get the Edges of a cell.
/// \param[in] a_cellIdx: the cells to whom the edges belong
/// \param[out] a_edges a vector of edges (organized in std::pairs)
//------------------------------------------------------------------------------
void XmUGridImpl::GetEdgesOfCell(const int a_cellIdx,
                                 std::vector<std::pair<int, int>>& a_edges) const
{
  a_edges.clear();
  int numEdges = GetNumberOfCellEdges(a_cellIdx);
  for (int i = 0; i < numEdges; ++i)
  {
    a_edges.push_back(GetCellEdgeFromEdgeIndex(a_cellIdx, i));
  }
} // XmUGridImpl::GetEdgesOfCell

//------------------------------------------------------------------------------
/// \brief Given a point gets point indexes attached to the point by an edge.
//------------------------------------------------------------------------------
void XmUGridImpl::GetPointIdxsAttachedByEdge(int a_pointIdx,VecInt& a_edgePoints) const
{
  a_edgePoints.clear();
  VecInt associatedCells = GetPointCells(a_pointIdx);
  if (associatedCells.size() == 0)
  {
    return;
  }
  for (int i = 0; i < associatedCells.size(); ++i)
  {
    for (int j = 0; j < GetNumberOfCellEdges(associatedCells[i]); ++j)
    {
      std::pair<int, int> temp = GetCellEdgeFromEdgeIndex(associatedCells[i], j);
      if (temp.first == a_pointIdx)
      {
        a_edgePoints.push_back(temp.second);
      }
      else if (temp.second == a_pointIdx)
      {
        a_edgePoints.push_back(temp.first);
      }
    }
  }
  std::sort(a_edgePoints.begin(), a_edgePoints.end());
  auto it = std::unique(a_edgePoints.begin(), a_edgePoints.end());
  a_edgePoints.erase(it, a_edgePoints.end());
} // XmUGridImpl::GetPointIdxsAttachedByEdge

//------------------------------------------------------------------------------
/// \brief Given a point gets point locations attached to the point by an edge.
/// \param[in] a_pointIdx The point to get attached point from.
/// \param[out] a_edgePoints A vector of points attached across edges.
//------------------------------------------------------------------------------
void XmUGridImpl::GetPointsAttachedByEdge(int a_pointIdx,VecPt3d& a_edgePoints) const
{
  VecInt edgePtIdxs;
  GetPointIdxsAttachedByEdge(a_pointIdx, edgePtIdxs);
  a_edgePoints = GetPointsFromPointIdxs(edgePtIdxs);
} // XmUGridImpl::GetPointsAttachedByEdge

//------------------------------------------------------------------------------
/// \brief Get the Edges associated with a point
/// \param[in] a_pointId: the point
/// \param[in] a_cellIdxs: the cells to whom the edges belong
/// \param[in] a_edges: the edges connected to the point
/// \return true if operation was successful
//------------------------------------------------------------------------------
bool XmUGridImpl::GetEdgesFromPoint(const int a_pointId,
                                    VecInt& a_cellIdxs,
                                    std::vector<std::pair<int, int>>& a_edges) const
{
  a_cellIdxs.clear();
  a_edges.clear();
  VecInt edgeIdx;
  if (!GetEdgesFromPoint(a_pointId, a_cellIdxs, edgeIdx))
    return false;
  for (int i = 0; i < edgeIdx.size(); ++i)
  {
    a_edges.push_back(GetCellEdgeFromEdgeIndex(a_cellIdxs[i], edgeIdx[i]));
  }
  return true;
} // XmUGridImpl::GetEdgesFromPoint

//------------------------------------------------------------------------------
/// \brief Get the Edges associated with a point
/// \param[in] a_pointId: the point
/// \param[in] a_cellIdxs: the cells to whom the edges belong
/// \param[in] a_edgePoints1: the first points of the edges connected to the point
/// \param[in] a_edgePoints2: the second points of the edges connected to the point
/// \return true if operation was successful
//------------------------------------------------------------------------------
bool XmUGridImpl::GetEdgesFromPoint(const int a_pointId,
                                    VecInt& a_cellIdxs,
                                    VecInt& a_edgePoints1,
                                    VecInt& a_edgePoints2) const
{
  a_edgePoints1.clear();
  a_edgePoints2.clear();
  std::vector<std::pair<int, int>> edges;
  if (!GetEdgesFromPoint(a_pointId, a_cellIdxs, edges))
    return false;
  for (int i = 0; i < edges.size(); ++i)
  {
    a_edgePoints1.push_back(edges[i].first);
    a_edgePoints2.push_back(edges[i].second);
  }
  return true;
} // XmUGridImpl::GetEdgesFromPoint

// Faces
//------------------------------------------------------------------------------
/// \brief Get the number of cell faces for given cell.
/// \param[in] a_cellIdx: the index of the cell
/// \return the count of cell faces
//------------------------------------------------------------------------------
int XmUGridImpl::GetNumberOfCellFaces(const int a_cellIdx) const
{
  if (a_cellIdx < 0 || a_cellIdx >= GetNumberOfCells())
    return -1;

  int cellType(GetCellType(a_cellIdx));
  switch (cellType)
  {
  case XMU_POLYHEDRON:
    return GetNumberOfItemsForCell(a_cellIdx);
    break;

  default:
  {
    const VecInt2d& faceTable = iGetFaceOffsetTable(cellType);
    return (int)faceTable.size();
    break;
  }
  }

  return 0;
} // XmUGridImpl::GetNumberOfCellFaces

//------------------------------------------------------------------------------
/// \brief Get the number of face points for a given cell and face.
/// \param[in] a_cellIdx The cell
/// \param[in] a_faceIdx The face
/// \return The number of face points or -1 if invalid face or cell index.
//------------------------------------------------------------------------------
int XmUGridImpl::GetNumberOfFacePoints(const int a_cellIdx,const int a_faceIdx) const
{
  if (a_cellIdx < 0 || a_cellIdx >= GetNumberOfCells())
  {
    return -1;
  }

  int cellType(GetCellType(a_cellIdx));
  switch (cellType)
  {
  case XMU_POLYHEDRON:
  {
    const int* cellStream;
    int length;
    GetSingleCellStream(a_cellIdx, &cellStream, length);
    if (cellStream != nullptr)
    {
      auto currItem = cellStream;
      int cellType = *currItem++;
      int numFaces = *currItem++;
      for (int faceIdx = 0; faceIdx < numFaces; ++faceIdx)
      {
        int numFacePoints = *currItem++;
        if (a_faceIdx == faceIdx)
        {
          return numFacePoints;
        }
        currItem += numFacePoints;
      }
    }
    break;
  }

  default:
  {
    const VecInt2d& faceTable = iGetFaceOffsetTable(cellType);
    if (a_faceIdx >= 0 && a_faceIdx < faceTable.size())
    {
      return (int)faceTable[a_faceIdx].size();
    }
    break;
  }
  }

  return 0;
} // XmUGridImpl::GetNumberOfFacePoints

//------------------------------------------------------------------------------
/// \brief Get the cell face for given cell and face index.
/// \param[in] a_cellIdx: the index of the cell
/// \param[in] a_faceIdx: the face index of the cell
/// \return a vector of point indexes for the face index of the cell
//------------------------------------------------------------------------------
VecInt XmUGridImpl::GetCellFace(const int a_cellIdx, const int a_faceIdx) const
{
  VecInt facePoints;
  GetCellFace(a_cellIdx, a_faceIdx, facePoints);
  return facePoints;
} // XmUGridImpl::GetCellFace
//------------------------------------------------------------------------------
/// \brief Get the cell face for given cell and face index.
/// \param[in] a_cellIdx: the index of the cell
/// \param[in] a_faceIdx: the face index of the cell
/// \param[out] a_facePtIdxs a vector of point indexes for the face index of the
///             cell
//------------------------------------------------------------------------------
void XmUGridImpl::GetCellFace(const int a_cellIdx, const int a_faceIdx, VecInt& a_facePtIdxs) const
{
  a_facePtIdxs.clear();
  if (a_faceIdx < 0)
  {
    return;
  }

  const int* cellStream = nullptr;
  int streamLength;
  GetSingleCellStream(a_cellIdx, &cellStream, streamLength);
  if (!cellStream)
    return;

  int cellType = *cellStream++;
  switch (cellType)
  {
  case XMU_POLYHEDRON:
  {
    int numFaces = *cellStream++;
    for (int faceIdx = 0; faceIdx < numFaces; ++faceIdx)
    {
      int numFacePoints = *cellStream++;
      if (faceIdx == a_faceIdx)
      {
        a_facePtIdxs.assign(cellStream, cellStream + numFacePoints);
        break;
      }
      cellStream += numFacePoints;
    }
  }
  break;

  default:
  {
    const VecInt2d& faceTable = iGetFaceOffsetTable(cellType);
    if (a_faceIdx < (int)faceTable.size())
    {
      if (cellStream)
      {
        const int* cellPoints = ++cellStream;
        const VecInt& faceOffsets = faceTable[a_faceIdx];
        for (auto offset : faceOffsets)
        {
          int idx = cellPoints[offset];
          a_facePtIdxs.push_back(idx);
        }
      }
    }
  }
  break;
  }
} // XmUGridImpl::GetCellFace
//------------------------------------------------------------------------------
/// \brief Get the faces of a cell.
/// \param[in] a_cellIdx: the cells to whom the faces belong
/// \return a vector of faces, which is a vector of point indices
//------------------------------------------------------------------------------
VecInt2d XmUGridImpl::GetFacesOfCell(const int a_cellIdx) const
{
  int numFaces = GetNumberOfCellFaces(a_cellIdx);

  VecInt2d faces(numFaces);
  for (int i(0); i < numFaces; i++)
  {
    faces[i] = GetCellFace(a_cellIdx, i);
  }
  return faces;
} // XmUGridImpl::::GetFacesOfCell
//------------------------------------------------------------------------------
/// \brief Get the cell face neighbors for given cell and face index.
/// \param[in] a_cellIdx: the index of the cell
/// \param[in] a_faceIdx: the face index of the cell
/// \return a cell index of the neighbor
//------------------------------------------------------------------------------
int XmUGridImpl::GetCellFaceNeighbor(const int a_cellIdx, const int a_faceIdx) const
{
  VecInt cellFace = GetCellFace(a_cellIdx, a_faceIdx);
  if (cellFace.empty())
    return -1;
  VecInt neighborCellFace = GetCommonCells(cellFace);
  if (neighborCellFace.size() <= 1)
    return -1;
  if (neighborCellFace.size() > 2)
  {
    assert("Cell definitions are invalid; more than 2 cells found sharing the same face.");
  }
  for (int i(0); i < neighborCellFace.size(); i++)
  {
    if (neighborCellFace[i] != a_cellIdx)
    {
      return neighborCellFace[i];
    }
  }
  return -1;
} // XmUGridImpl::GetCellFaceNeighbor
//------------------------------------------------------------------------------
/// \brief Get the cell face neighbors for given cell and face index.
/// \param[in] a_cellIdx: the index of the cell
/// \param[in] a_faceIdx: the face index of the cell
/// \param[in] a_neighborCell: the index of the neighboring cell
/// \param[in] a_neighborFace: the face index of the neighboring cell adjacent
///      to the given face
/// \return a cell index of the neighbor
//------------------------------------------------------------------------------
bool XmUGridImpl::GetCellFaceNeighbor(const int a_cellIdx,
                                      const int a_faceIdx,
                                      int& a_neighborCell,
                                      int& a_neighborFace) const
{
  a_neighborCell = GetCellFaceNeighbor(a_cellIdx, a_faceIdx);
  if (a_neighborCell < 0)
  {
    a_neighborCell = a_neighborFace = -1;
    return false;
  }
  VecInt cellFace = GetCellFace(a_cellIdx, a_faceIdx);
  for (int i(0); i < GetNumberOfCellFaces(a_neighborCell); i++)
  {
    VecInt curCellFace = GetCellFace(a_neighborCell, i);
    if (cellFace.size() == curCellFace.size())
    {
      int j(0);
      for (; j < cellFace.size(); ++j)
      {
        bool found = false;
        for (int k(0); k < curCellFace.size(); ++k)
        {
          if (cellFace[j] == curCellFace[k])
          {
            found = true;
            break;
          }
        }
        if (!found)
          break; // This face is not the face we are l.
      }
      if (j == cellFace.size()) // Every point is found
      {
        a_neighborFace = i;
        a_neighborFace = i;
        return true;
      }
    }
  }
  a_neighborCell = a_neighborFace = -1;
  return false;
} // XmUGridImpl::GetCellFaceNeighbor

//------------------------------------------------------------------------------
/// \brief Get the cell face associated with a point.
/// \param[in] a_pointId: the point
/// \param[in] a_cellIdxs: the cells to whom the faces belong
/// \param[in] a_faceIdxs: the index of the face connected to the point
/// \return a cell index of the neighbor
//------------------------------------------------------------------------------
bool XmUGridImpl::GetFacesFromPoint(const int a_pointId,
                                    VecInt& a_cellIdxs,
                                    VecInt& a_faceIdxs) const
{
  a_faceIdxs.clear();
  a_cellIdxs.clear();
  VecInt associatedCells = GetPointCells(a_pointId);
  if (associatedCells.size() == 0)
    return false;
  for (int i = 0; i < associatedCells.size(); ++i)
  {
    for (int j = 0; j < GetNumberOfCellFaces(associatedCells[i]); ++j)
    {
      VecInt temp = GetCellFace(associatedCells[i], j);
      for (int k = 0; k < temp.size(); k++)
      {
        if (temp[k] == a_pointId)
        {
          a_faceIdxs.push_back(j);
          a_cellIdxs.push_back(associatedCells[i]);
          break;
        }
      }
    }
  }
  return true;
} // XmUGridImpl::GetFacesFromPoint

//------------------------------------------------------------------------------
/// \brief Update internal links to navigate between associated points and
///        cells.
//------------------------------------------------------------------------------
void XmUGridImpl::UpdateLinks()
{
  UpdateCellLinks();
  UpdatePointLinks();
} // XmUGridImpl::UpdateLinks
//------------------------------------------------------------------------------
/// \brief Update internal link from cells to cell stream index.
//------------------------------------------------------------------------------
void XmUGridImpl::UpdateCellLinks()
{
  m_cellIdxToStreamIdx.clear();

  int currIdx = 0;
  if (m_cellStream.empty())
  {
    m_cellIdxToStreamIdx.push_back(currIdx);
    return;
  }

  int numItems = (int)m_cellStream.size();
  while (currIdx < numItems)
  {
    m_cellIdxToStreamIdx.push_back(currIdx);

    // get cell type
    int cellType = m_cellStream[currIdx++];
    if (currIdx >= numItems)
      return;

    // get the number of items
    int numPoints = m_cellStream[currIdx++];
    if (currIdx >= numItems)
      return;

    if (cellType == XMU_POLYHEDRON)
    {
      int numFaces = numPoints;
      for (int faceIdx = 0; faceIdx < numFaces; ++faceIdx)
      {
        int numPoints = m_cellStream[currIdx++];
        currIdx += numPoints;
      }
    }
    else
    {
      currIdx += numPoints;
    }
  }

  m_cellIdxToStreamIdx.push_back(currIdx);
} // XmUGridImpl::UpdateCellLinks
//------------------------------------------------------------------------------
/// \brief Update internal links from points to associated cells.
//------------------------------------------------------------------------------
void XmUGridImpl::UpdatePointLinks()
{
  m_pointIdxToPointsToCells.clear();
  m_pointIdxToPointsToCells.resize(m_points.size(), 0);
  m_pointsToCells.clear();

  // get number of cells for each point
  int numStreamItems = (int)m_cellStream.size();
  int cellIdx = 0;
  int currIdx = 0;
  VecInt cellPointMask(m_points.size(), -1);
  VecInt cellPoints;
  while (currIdx < numStreamItems)
  {
    // get cell type
    int cellType = m_cellStream[currIdx++];
    if (currIdx >= numStreamItems)
      return;

    // get the number of items (points or faces depending on cell type)
    int numCellItems = m_cellStream[currIdx++];
    if (currIdx >= numStreamItems)
      return;

    if (cellType == XMU_POLYHEDRON)
    {
      GetUniquePointsFromPolyhedronCellStream(m_cellStream, numCellItems, currIdx, cellPoints,
                                              cellPointMask);

      // Deemed to be slower than flat set-- Left only as a warning to others!
      // std::stable_sort(cellPoints.begin(), cellPoints.end());
      // auto uniqueEnd = std::unique(cellPoints.begin(), cellPoints.end());

      // for (auto pt = cellPoints.begin(); pt != uniqueEnd; ++pt)
      for (auto pt = cellPoints.begin(); pt != cellPoints.end(); ++pt)
      {
        m_pointIdxToPointsToCells[*pt] += 1;
      }
    }
    else
    {
      // iterate on points
      int numPoints = numCellItems;
      for (int ptIdx = 0; ptIdx < numPoints; ++ptIdx)
      {
        int pt = m_cellStream[currIdx++];
        m_pointIdxToPointsToCells[pt] += 1;
      }
    }

    ++cellIdx;
  }
  m_pointIdxToPointsToCells.push_back(0);

  // change array of counts to array of offsets
  int currCount = 0;
  for (auto& item : m_pointIdxToPointsToCells)
  {
    int count = item + 1;
    item = currCount;
    currCount += count;
  }

  cellIdx = 0;
  currIdx = 0;
  m_pointsToCells.resize(currCount, 0);
  std::fill(cellPointMask.begin(), cellPointMask.end(), -1);
  while (currIdx < numStreamItems)
  {
    // get cell type
    int cellType = m_cellStream[currIdx++];
    if (currIdx >= numStreamItems)
      return;

    // get the number of items (points or faces depending on cell type)
    int numCellItems = m_cellStream[currIdx++];
    if (currIdx >= numStreamItems)
      return;

    if (cellType == XMU_POLYHEDRON)
    {
      GetUniquePointsFromPolyhedronCellStream(m_cellStream, numCellItems, currIdx, cellPoints,
                                              cellPointMask);

      // Deemed to be slower than flat set-- Left only as a warning to others!
      // std::stable_sort(cellPoints.begin(), cellPoints.end());
      // auto uniqueEnd = std::unique(cellPoints.begin(), cellPoints.end());

      // for (auto pt = cellPoints.begin(); pt != uniqueEnd; ++pt)
      for (auto pt = cellPoints.begin(); pt != cellPoints.end(); ++pt)
      {
        int countIdx = m_pointIdxToPointsToCells[*pt];
        int& count = m_pointsToCells[countIdx]; // point's cell count
        ++count;                                // incrementing point's cell count
        int updateIdx = countIdx + count;
        m_pointsToCells[updateIdx] = cellIdx;
      }
    }
    else
    {
      // iterate on points
      int numPoints = numCellItems;
      for (int ptIdx = 0; ptIdx < numPoints; ++ptIdx)
      {
        int pt = m_cellStream[currIdx++];
        int countIdx = m_pointIdxToPointsToCells[pt];
        int& count = m_pointsToCells[countIdx]; // point's cell count
        ++count;                                // incrementing point's cell count
        int updateIdx = countIdx + count;
        m_pointsToCells[updateIdx] = cellIdx;
      }
    }

    ++cellIdx;
  }
} // XmUGridImpl::UpdatePointLinks
//------------------------------------------------------------------------------
/// \brief Get the dimension given the cell type (0d, 1d, 2d, or 3d).
/// \param[in] a_cellType: the cell type
/// \return the dimension of the cell type
//------------------------------------------------------------------------------
int XmUGridImpl::DimensionFromCellType(const XmUGridCellType a_cellType)
{
  switch (a_cellType)
  {
  // invalid
  case XMU_INVALID_CELL_TYPE:
    return -1;
    break;

  // 0D
  case XMU_EMPTY_CELL:
  case XMU_VERTEX:
  case XMU_POLY_VERTEX:
  case XMU_CONVEX_POINT_SET: // Special class of cells formed by convex group of
                             // points
    return 0;
    break;

  // 1D
  case XMU_LINE:
  case XMU_POLY_LINE:

  case XMU_QUADRATIC_EDGE:
  case XMU_PARAMETRIC_CURVE:
  case XMU_HIGHER_ORDER_EDGE:
  case XMU_CUBIC_LINE: // Cubic, isoparametric cell
    return 1;
    break;
  // 2D
  case XMU_TRIANGLE:
  case XMU_TRIANGLE_STRIP:
  case XMU_POLYGON:
  case XMU_PIXEL:
  case XMU_QUAD:

  case XMU_QUADRATIC_TRIANGLE:
  case XMU_QUADRATIC_QUAD:
  case XMU_BIQUADRATIC_QUAD:
  case XMU_QUADRATIC_LINEAR_QUAD:
  case XMU_BIQUADRATIC_TRIANGLE:
  case XMU_QUADRATIC_POLYGON:

  case XMU_PARAMETRIC_SURFACE:
  case XMU_PARAMETRIC_TRI_SURFACE:
  case XMU_PARAMETRIC_QUAD_SURFACE:

  case XMU_HIGHER_ORDER_TRIANGLE:
  case XMU_HIGHER_ORDER_QUAD:
  case XMU_HIGHER_ORDER_POLYGON:

    return 2;
    break;

  // assuming the rest are 3D
  default:
    return 3;
    break;
#if 0 // Remaining definitions
    XMU_TETRA = 10,
    XMU_VOXEL = 11,
    XMU_HEXAHEDRON = 12,
    XMU_WEDGE = 13,
    XMU_PYRAMID = 14,
    XMU_PENTAGONAL_PRISM = 15,
    XMU_HEXAGONAL_PRISM = 16,

    // Quadratic, isoparametric cells
    XMU_QUADRATIC_TETRA = 24,
    XMU_QUADRATIC_HEXAHEDRON = 25,
    XMU_QUADRATIC_WEDGE = 26,
    XMU_QUADRATIC_PYRAMID = 27,
    XMU_TRIQUADRATIC_HEXAHEDRON = 29,
    XMU_QUADRATIC_LINEAR_WEDGE = 31,
    XMU_BIQUADRATIC_QUADRATIC_WEDGE = 32,
    XMU_BIQUADRATIC_QUADRATIC_HEXAHEDRON = 33,

    // Polyhedron cell (consisting of polygonal faces)
    XMU_POLYHEDRON = 42,

    // Higher order cells in parametric form
    XMU_PARAMETRIC_TETRA_REGION = 55,
    XMU_PARAMETRIC_HEX_REGION = 56,

    // Higher order cells
    XMU_HIGHER_ORDER_TETRAHEDRON = 64,
    XMU_HIGHER_ORDER_WEDGE = 65,
    XMU_HIGHER_ORDER_PYRAMID = 66,
    XMU_HIGHER_ORDER_HEXAHEDRON = 67,
#endif
  }
  return -1;

} // XmUGridImpl::DimensionFromCellType

//------------------------------------------------------------------------------
/// \brief Get number of items given cell. For polyhedron number of items is
///        number of faces. For other cell types it is number of points.
/// \param[in] a_cellIdx: the index of the cell
/// \return the number of faces for polyhedron or number of points.
//------------------------------------------------------------------------------
int XmUGridImpl::GetNumberOfItemsForCell(const int a_cellIdx) const
{
  int cellType = GetCellType(a_cellIdx);
  if (cellType == XMU_INVALID_CELL_TYPE)
  {
    return 0;
  }
  else if (cellType != XMU_POLYHEDRON)
  {
    // Number of points is right after cell type
    int startIndex = m_cellIdxToStreamIdx[a_cellIdx];
    return m_cellStream[startIndex + 1];
  }
  else
  { // Polyhedron case, same value is number of faces
    int startIndex = m_cellIdxToStreamIdx[a_cellIdx];
    return m_cellStream[startIndex + 1];
  }
} // XmUGridImpl::GetNumberOfItemsForCell
//------------------------------------------------------------------------------
/// \brief Internal function to get start of cell stream for an individual cell.
///        Returns nullptr and zero length for invalid cell index.
/// \param[in] a_cellIdx: the index of the cell
/// \param[out] a_start: pointer to the start of the stream for the cell
/// \param[out] a_length: the length of the stream for the cell
//------------------------------------------------------------------------------
void XmUGridImpl::GetSingleCellStream(const int a_cellIdx, const int** a_start, int& a_length) const
{
  int cellType = GetCellType(a_cellIdx);
  if (cellType == XMU_INVALID_CELL_TYPE)
  {
    *a_start = nullptr;
    a_length = 0;
  }
  else
  {
    int startIndex = m_cellIdxToStreamIdx[a_cellIdx];
    int nextCellIndex = m_cellIdxToStreamIdx[a_cellIdx + 1];
    *a_start = &m_cellStream[startIndex];
    a_length = nextCellIndex - startIndex;
  }
} // XmUGridImpl::GetSingleCellStream
//------------------------------------------------------------------------------
/// \brief Get the number of edges for a polyhedron cell.
/// \param[in] a_cellIdx: the index of the cell
/// \return the number of edges
//------------------------------------------------------------------------------
int XmUGridImpl::GetNumberOfPolyhedronEdges(const int a_cellIdx) const
{
  const int* cellStream;
  int streamLength;
  GetSingleCellStream(a_cellIdx, &cellStream, streamLength);
  if (cellStream && streamLength > 0 && cellStream[0] == XMU_POLYHEDRON)
  {
    boost::container::flat_set<std::pair<int, int>> edges;
    int currItem = 2;
    while (currItem < streamLength)
    {
      GetUniqueEdgesFromPolyhedronCellStream(cellStream, streamLength, edges, currItem);
    }
    return (int)edges.size();
  }
  return 0;
} // XmUGridImpl::GetNumberOfPolyhedronEdges
//------------------------------------------------------------------------------
/// \brief Get the unique points in a flat set
/// \param[in] a_cellStream: the UGrid cell stream
/// \param[in] a_numCellItems: the number of cell faces in the polyhedron
/// \param[in] a_currIdx: the index of the cell stream; this should reference
///       the number of points in the first face. This variable will be updated
///       to the cell type of the next cell.
/// \param[out] a_uniqueCellPoints: the unique points of the polyhedron
/// \param[out] a_cellMask: a list of integers representing the last time a point was found
/// \note: This function does NOT verify cellstream size!!  This function
///      needs to be efficient!
//------------------------------------------------------------------------------
void XmUGridImpl::GetUniquePointsFromPolyhedronCellStream(const VecInt& a_cellStream,
                                                          const int a_numCellItems,
                                                          int& a_currIdx,
                                                          VecInt& a_uniqueCellPoints,
                                                          VecInt& a_cellMask)
{
  int stable = a_currIdx;
  a_uniqueCellPoints.clear();
  int numFaces = a_numCellItems;
  for (int faceIdx = 0; faceIdx < numFaces; ++faceIdx)
  {
    int numFacePoints = a_cellStream[a_currIdx++];
    for (int ptIdx = 0; ptIdx < numFacePoints; ++ptIdx)
    {
      int pt = a_cellStream[a_currIdx++];
      if (a_cellMask[pt] < stable)
      {
        a_cellMask[pt] = stable;
        a_uniqueCellPoints.push_back(pt);
      }
    }
  }
} // XmUGridImpl::GetUniquePointsFromPolyhedronCellStream
//------------------------------------------------------------------------------
/// \brief Get the unique points for cell stream of a single polyhedron cell.
/// \param[in] a_cellStream: a single cell stream that is a polyhedron type
/// \param[out] a_cellPoints: the points of the cell
/// \return false if invalid stream
//------------------------------------------------------------------------------
bool XmUGridImpl::GetUniquePointsFromPolyhedronSingleCellStream(const VecInt& a_cellStream,
                                                                VecInt& a_cellPoints)
{
  a_cellPoints.clear();
  if (a_cellStream.size() < 2)
  {
    return false;
  }

  auto currItem = a_cellStream.begin();
  int cellType = *currItem++;
  if (cellType != XMU_POLYHEDRON)
  {
    return false;
  }

  int numFaces = *currItem++;
  for (int faceIdx = 0; faceIdx < numFaces; ++faceIdx)
  {
    int numFacePoints = *currItem++;
    for (int ptIdx = 0; ptIdx < numFacePoints; ++ptIdx)
    {
      int pt = *currItem++;
      if (std::find(a_cellPoints.begin(), a_cellPoints.end(), pt) == a_cellPoints.end())
      {
        a_cellPoints.push_back(pt);
      }
    }
  }

  return true;
} // XmUGridImpl::GetUniquePointsFromPolyhedronSingleCellStream
//------------------------------------------------------------------------------
/// \brief Get the unique edges in a flat set for a given polyhedron
/// \param[in] a_start: the UGrid cell stream (integer pointer)
/// \param[in] a_length: the length of the cell stream
/// \param[in] a_cellEdges: Unique cell edges of the polyhedron
/// \param[in] a_currIdx: the index of the cell stream; this should reference
///       the number of points in the first face. This variable will be updated
///       to the cell type of the next cell.
/// \note: This function does NOT verify cellstream size!!  This function
///      needs to be efficient!
//------------------------------------------------------------------------------
void XmUGridImpl::GetUniqueEdgesFromPolyhedronCellStream(
  const int* a_start,
  int& a_length,
  boost::container::flat_set<std::pair<int, int>>& a_cellEdges,
  int& a_currIdx)
{
  int numFaces = a_start[1];
  for (int i(0); i < numFaces; i++)
  {
    int numPoints = a_start[a_currIdx++];
    for (int pointIdx = 0; pointIdx < numPoints; ++pointIdx)
    {
      int pt1Idx = pointIdx;
      int pt2Idx = (pointIdx + 1) % numPoints;
      // The % operator will reset the index back 0 so the final loop will
      // provide the last and first point
      int pt1 = a_start[a_currIdx + pt1Idx];
      int pt2 = a_start[a_currIdx + pt2Idx];
      // We want unique edges, so we add the lower point index first
      if (pt1 < pt2)
        a_cellEdges.insert(std::pair<int, int>(pt1, pt2));
      else
        a_cellEdges.insert(std::pair<int, int>(pt2, pt1));
    }
    a_currIdx += numPoints;
  }
} // XmUGridImpl::GetUniqueEdgesFromPolyhedronCellStream
//------------------------------------------------------------------------------
/// \brief Get a plan view polygon of a specified 2D cell
/// \param[in] a_cellIdx: the index of the cell
/// \param[out] a_polygon: vector of Pt3d that is the plan view polygon
/// \return whether the operation was successful
//------------------------------------------------------------------------------
bool XmUGridImpl::GetPlanViewPolygon2d(int a_cellIdx, VecPt3d& a_polygon) const
{
  GetPointsOfCell(a_cellIdx, a_polygon);
  if (a_polygon.size() > 0)
  {
    return true;
  }
  return false;
} // XmUGridImpl::GetPlanViewPolygon2d
//------------------------------------------------------------------------------
/// \brief Get a plan view polygon of a specified 3D cell
/// \param[in] a_cellIdx: the index of the cell
/// \param[out] a_polygon: vector of Pt3d that is the plan view polygon
/// \return whether the operation was successful
//------------------------------------------------------------------------------
bool XmUGridImpl::GetPlanViewPolygon3d(int a_cellIdx, VecPt3d& a_polygon) const
{
  VecPt3d segments;
  if (GetCellXySegments(a_cellIdx, segments))
  {
    // Prismatic cell
    iMergeSegmentsToPoly(segments, a_polygon);
    return true;
  }
  else
  {
    // Non-prismatic cell
    VecInt uniquePoints = GetPointsOfCell(a_cellIdx);
    VecPt3d cellPoints(uniquePoints.size());
    for (int i(0); i < uniquePoints.size(); i++)
    {
      cellPoints[i] = GetPoint(uniquePoints[i]);
      cellPoints[i].z = 0.0; // Insist that our z values are 0.0 for plan view
    }
    a_polygon = ConvexHull(cellPoints);
    return true;
  }
  return false;
} // XmUGridImpl::GetPlanViewPolygon3d
//------------------------------------------------------------------------------
/// \brief Get whether the cell face is of a side orientation. Only works for
///        plan view prismatic cells.
/// \param[in] a_facePts: the points in the face
/// \return whether the face is a Side
//------------------------------------------------------------------------------
bool XmUGridImpl::IsFaceSide(const VecInt& a_facePts) const
{
  // if any face point has same x and y as any other face point then
  // the face is a side face
  if (a_facePts.size() > 2)
  {
    Pt3d ptLast = GetPoint(a_facePts[0]);
    for (size_t facePtIdx = 1; facePtIdx < a_facePts.size(); ++facePtIdx)
    {
      Pt3d ptCurr = GetPoint(a_facePts[facePtIdx]);
      if ((ptLast.x == ptCurr.x) && (ptLast.y == ptCurr.y))
        return true;

      ptLast = ptCurr;
    }
  }
  return false;
} // XmUGridImpl::IsFaceSide
//------------------------------------------------------------------------------
/// \brief Get the XY segments of a cell.
/// \param[in] a_cellIdx: the index of the cell
/// \param[out] a_segments: The XY segments of a cell
/// \return whether the collected segments form a valid polygon
//------------------------------------------------------------------------------
bool XmUGridImpl::GetCellXySegments(int a_cellIdx, VecPt3d& a_segments) const
{
  bool foundSideFace = false;
  for (int faceIdx = 0; faceIdx < GetNumberOfCellFaces(a_cellIdx); ++faceIdx)
  {
    VecInt ptIdxs = GetCellFace(a_cellIdx, faceIdx);
    if (IsFaceSide(ptIdxs))
    {
      foundSideFace = true;
      if (!GetFaceXySegments(a_cellIdx, faceIdx, a_segments))
      {
        return false;
      }
    }
  }
  return foundSideFace;
} // XmUGridImpl::GetCellXySegments

//------------------------------------------------------------------------------
/// \brief Function to get the extents from a list of points. Will be removed after geometry library is built.
/// \param[in] a_points The point locations to get the extents of.
/// \param[out] a_min Minimum point location.
/// \param[out] a_min Minimum point location.
//------------------------------------------------------------------------------
void XmUGridImpl::GetExtentsFromPoints(const VecPt3d& a_points, Pt3d &a_min,Pt3d &a_max) const
{
#pragma message("TODO: Remove this function after geometry library is built.")
  a_min.x = a_min.y = a_min.z = xms::XM_DBL_HIGHEST;
  a_max.x = a_max.y = a_max.z = xms::XM_DBL_LOWEST;
  for (const Pt3d& pt : a_points)
  {
    a_min.x = std::min(pt.x,a_min.x);
    a_min.y = std::min(pt.y,a_min.y);
    a_min.z = std::min(pt.z,a_min.z);
    a_max.x = std::max(pt.x,a_max.x);
    a_max.y = std::max(pt.y,a_max.y);
    a_max.z = std::max(pt.z,a_max.z);
  }
} // XmUGridImpl::GetExtentsFromPoints

//------------------------------------------------------------------------------
/// \brief
//------------------------------------------------------------------------------
bool XmUGridImpl::GetFaceXySegments(int a_cellIdx, int a_faceIdx, VecPt3d& a_segments) const
{
  VecInt facePts;
  GetCellFace(a_cellIdx, a_faceIdx, facePts);
  if (facePts.empty())
    return false;

  size_t column1Begin, column1End;
  if (!iGetNextFaceColumn(*this, facePts, 0, column1Begin, column1End))
    return false;

  size_t column2Begin, column2End;
  if (!iGetNextFaceColumn(*this, facePts, column1End, column2Begin, column2End))
    return false;

  iGetFacePointSegments(*this, facePts, column1End, column2Begin, a_segments);
  iGetFacePointSegments(*this, facePts, column2End, column1Begin, a_segments);
  return true;
} // XmUGridImpl::GetFaceXySegments

} // namespace
////////////////////////////////////////////////////////////////////////////////
/// \class XmUGrid
/// \brief Geometry for an unstructured grid.
////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
/// \brief Create a new XmUGrid.
/// \return the new XmUGrid.
//------------------------------------------------------------------------------
BSHP<XmUGrid> XmUGrid::New()
{
  BSHP<XmUGrid> ugrid(new XmUGridImpl());
  return ugrid;
} // XmUGrid::New
//------------------------------------------------------------------------------
/// \brief Create a new XmUGrid.
/// \param[in] a_points: the UGrid points
/// \param[in] a_cellStream: the UGrid cell stream
/// \return the new XmUGrid.
//------------------------------------------------------------------------------
BSHP<XmUGrid> XmUGrid::New(const VecPt3d& a_points, const VecInt& a_cellStream)
{
  BSHP<XmUGrid> ugrid = XmUGrid::New();
  ugrid->SetPoints(a_points);
  ugrid->SetCellStream(a_cellStream);
  return ugrid;
} // XmUGrid::New
//------------------------------------------------------------------------------
/// \brief Constructor
//------------------------------------------------------------------------------
XmUGrid::XmUGrid()
{
} // XmUGrid::XmUGrid
//------------------------------------------------------------------------------
/// \brief Destructor
//------------------------------------------------------------------------------
XmUGrid::~XmUGrid()
{
} // XmUGrid::~XmUGrid
//------------------------------------------------------------------------------
/// \brief Check a cell stream to make sure it's valid. Compares cell type
///        against expected number of points.
/// \param[in] a_cellStream: the cell stream to check
/// \return true if cell stream is valid
//------------------------------------------------------------------------------
bool XmUGrid::ValidCellStream(const VecInt& a_cellStream)
{
  if (a_cellStream.empty())
    return true;

  int numItems = (int)a_cellStream.size();
  int currIdx = 0;
  while (currIdx < numItems)
  {
    // get cell type
    int cellType = a_cellStream[currIdx++];
    if (currIdx >= numItems)
      return false;

    // get the number of points
    int numPoints = a_cellStream[currIdx++];
    if (currIdx >= numItems)
      return false;

    switch (cellType)
    {
    case XMU_EMPTY_CELL:
      if (numPoints != 0)
        return false;
      break;
    case XMU_VERTEX:
      if (numPoints != 1)
        return false;
      currIdx += numPoints;
      break;
    case XMU_LINE:
      if (numPoints != 2)
        return false;
      currIdx += numPoints;
      break;
    case XMU_TRIANGLE:
      if (numPoints != 3)
        return false;
      currIdx += numPoints;
      break;
    case XMU_PIXEL:
    case XMU_QUAD:
    case XMU_TETRA:
      if (numPoints != 4)
        return false;
      currIdx += numPoints;
      break;
    case XMU_PYRAMID:
      if (numPoints != 5)
        return false;
      currIdx += numPoints;
      break;
    case XMU_WEDGE:
    case XMU_PENTAGONAL_PRISM:
      if (numPoints != 6)
        return false;
      currIdx += numPoints;
      break;
    case XMU_HEXAGONAL_PRISM:
      if (numPoints != 7)
        return false;
      currIdx += numPoints;
      break;
    case XMU_VOXEL:
    case XMU_HEXAHEDRON:
      if (numPoints != 8)
        return false;
      currIdx += numPoints;
      break;
    case XMU_POLY_VERTEX:
      if (numPoints < 1)
        return false;
      currIdx += numPoints;
      break;
    case XMU_POLY_LINE:
      if (numPoints < 2)
        return false;
      currIdx += numPoints;
      break;
    case XMU_TRIANGLE_STRIP:
    case XMU_POLYGON:
      if (numPoints < 3)
        return false;
      currIdx += numPoints;
      break;
    case XMU_POLYHEDRON:
    {
      int numFaces = numPoints;
      if (numFaces < 3)
        return false;
      for (int faceIdx = 0; faceIdx < numFaces; ++faceIdx)
      {
        if (currIdx >= numItems)
          return false;
        int numPoints = a_cellStream[currIdx++];
        if (numPoints < 3)
          return false;
        currIdx += numPoints;
      }
    }
    break;
    default:
      currIdx += numPoints;
      break;
    }

    if (currIdx > numItems)
      return false;
  }

  return true;
} // XmUGrid::ValidCellStream
//------------------------------------------------------------------------------
/// \brief Builds a 1 cell (left 90 degree triangle) 2D XmUGrid for testing.
/// \code
///  2
///  | \
///  |  \
///  |   \
///  0----1
///
/// \endcode
/// \return Returns a builder for the UGrid.
BSHP<XmUGrid> TEST_XmUGrid1Left90Tri()
{
  VecPt3d points = {{0, 0, 0}, {20, 0, 0}, {0, 20, 0}};

  // Cell type (5), number of points (3), point numbers, counterclockwise
  std::vector<int> cells = {5, 3, 0, 1, 2};

  BSHP<XmUGrid> ugrid = XmUGrid::New(points, cells);

  return ugrid;
} // TEST_UGrid1Left90Tri
//------------------------------------------------------------------------------
/// \brief Builds a 2 cell (Quad) 2D XmUGrid for testing.
/// \code
///
///     0-----1-----2
///     |  0  |  1  |
///     3-----4-----5
///     |  2  |  3  |
///     6-----7-----8
///
/// \endcode
/// \return Returns a builder for the UGrid.
BSHP<XmUGrid> TEST_XmUGridSimpleQuad()
{
  VecPt3d points = {{0, 10, 0}, {10, 10, 0}, {20, 10, 0},  {0, 0, 0},   {10, 0, 0},
                    {20, 0, 0}, {0, -10, 0}, {10, -10, 0}, {20, -10, 0}};

  // Cell type (9), number of points (4), point numbers, counterclockwise
  VecInt cellStream = {XMU_QUAD, 4, 0, 3, 4, 1, XMU_QUAD, 4, 1, 4, 5, 2,
                       XMU_QUAD, 4, 3, 6, 7, 4, XMU_QUAD, 4, 4, 7, 8, 5};

  BSHP<XmUGrid> ugrid = XmUGrid::New(points, cellStream);
  return ugrid;
} // TEST_XmUGridSimpleQuad

//------------------------------------------------------------------------------
/// \brief Builds an XmUGrid with supported 1D and 2D linear cells for testing.
/// \return Returns the XmUGrid.
//------------------------------------------------------------------------------
BSHP<XmUGrid> TEST_XmUGrid2dLinear()
{
  // clang-format off
  //! [snip_test_2DShapes]
  VecPt3d points = { { 0, 0, 0 }, { 10, 0, 0 }, { 20, 0, 0 }, { 30, 0, 0 }, { 40, 0, 0 },
                    {0, 10, 0},  {10, 10, 0}, {20, 10, 0}, {40, 10, 0}, {0, 20, 0},
                    {10, 20, 0}, {20, 20, 0}, {30, 20, 0}, {40, 20, 0}};

  // Cell type (5), number of points (3), point numbers, counterclockwise
  std::vector<int> cells = {(int)XMU_QUAD, 4, 0, 1, 6, 5,            // 0
                            (int)XMU_PIXEL, 4, 1, 2, 6, 7,           // 1
                            (int)XMU_TRIANGLE, 3, 2, 3, 7,           // 2
                            (int)XMU_POLYGON, 6, 3, 4, 8, 13, 12, 7, // 3
                            (int)XMU_POLY_LINE, 3, 7, 11, 10,        // 4
                            (int)XMU_LINE, 2, 5, 9};                 // 5
  //! [snip_test_2DShapes]
  // clang-format on

  BSHP<XmUGrid> ugrid = XmUGrid::New(points, cells);

  return ugrid;
} // TEST_XmUGrid2dLinear
//------------------------------------------------------------------------------
/// \brief Builds an XmUGrid with supported 3D linear cells for testing.
/// \return Returns the XmUGrid.
//------------------------------------------------------------------------------
BSHP<XmUGrid> TEST_XmUGrid3dLinear()
{
  // clang-format off
  //! [snip_test_3DShapes]
  VecPt3d points = {{0, 0, 0},   {10, 0, 0},   {20, 0, 0},   {30, 0, 0},   {40, 0, 0},
                    {0, 10, 0},  {10, 10, 0},  {20, 10, 0},  {30, 10, 0},  {40, 10, 0},
                    {0, 20, 0},  {10, 20, 0},  {20, 20, 0},  {30, 20, 0},  {40, 20, 0},
                    {0, 0, 10},  {10, 0, 10},  {20, 0, 10},  {30, 0, 10},  {40, 0, 10},
                    {0, 10, 10}, {10, 10, 10}, {20, 10, 10}, {30, 10, 10}, {40, 10, 10},
                    {0, 20, 10}, {10, 20, 10}, {20, 20, 10}, {30, 20, 10}, {40, 20, 10}};

  // Cell type (5), number of points (3), point numbers, counterclockwise
  std::vector<int> cells = {(int)XMU_TETRA, 4, 0, 1, 5, 15,
                            (int)XMU_VOXEL, 8, 1, 2, 6, 7, 16, 17, 21, 22,
                            (int)XMU_HEXAHEDRON, 8, 2, 3, 8, 7, 17, 18, 23, 22,
                            (int)XMU_POLYHEDRON, 6, // A polyhedron with 6 faces
                            4, 8, 9, 14, 13, // First face with 4 points : 8, 9, 14, 13
                            4, 8, 9, 24, 23, // Second face with 4 points : 8, 9, 24, 23
                            4, 9, 14, 29, 24, // Third face with 4 points : 9, 14, 29, 28
                            4, 13, 14, 29, 28, // Fourth face with 4 points : 13, 14, 29, 28
                            4, 8, 13, 28, 23, // Fifth face with 4 points : 8, 13, 28, 23
                            4, 23, 24, 29, 28, // Sixth face with 4 points : 23, 24, 29, 28
                            (int)XMU_WEDGE, 6, 3, 4, 18, 8, 9, 23,
                            (int)XMU_PYRAMID, 5, 5, 6, 11, 10, 20};
  //! [snip_test_3DShapes]
  // clang-format on

  BSHP<XmUGrid> ugrid = XmUGrid::New(points, cells);

  return ugrid;
} // TEST_XmUGrid3dLinear
//------------------------------------------------------------------------------
/// \brief Builds a 1 cell hexagon with cell type polyhedron.
/// \return Returns the UGrid.
//------------------------------------------------------------------------------
BSHP<XmUGrid> TEST_XmUGridHexagonalPolyhedron()
{
  VecPt3d points = {
    {0, 0, 10}, {10, 0, 10}, {10, 10, 10}, {0, 10, 10},
    {0, 0, 0},  {10, 0, 0},  {10, 10, 0},  {0, 10, 0},
  };

  // clang-format off

  // Cell type (5), number of points (3), point numbers, counterclockwise
  std::vector<int> cells = {(int)XMU_POLYHEDRON, 6,
                            4, 0, 1, 2, 3,
                            4, 4, 5, 7, 2,
                            4, 5, 6, 2, 1,
                            4, 6, 7, 3, 2,
                            4, 7, 4, 0, 3,
                            4, 4, 7, 6, 5};
  // clang-format on

  BSHP<XmUGrid> ugrid = XmUGrid::New(points, cells);

  return ugrid;
} // TEST_XmUGridHexagonalPolyhedron
//------------------------------------------------------------------------------
/// \brief Builds a UGrid of Quads at 1 spacing for rows & cols specified
/// \param[in] a_rows: number of rows in UGrid
/// \param[in] a_cols: number of columns in UGrid
/// \return Returns the UGrid.
//------------------------------------------------------------------------------
BSHP<xms::XmUGrid> TEST_XmUBuildQuadUGrid(const int a_rows, const int a_cols)
{
  Pt3d origin(0.0, 0.0, 0.0);
  return TEST_XmUBuildQuadUGrid(a_rows, a_cols, origin);
} // TEST_XmUBuildQuadUGrid
//------------------------------------------------------------------------------
/// \brief Builds a UGrid of Quads at 1 spacing for rows & cols specified
/// \param[in] a_rows: number of rows in UGrid
/// \param[in] a_cols: number of columns in UGrid
/// \param[in] a_origin: Point where the UGrid begins (min x, min y, min z)
/// \return Returns the UGrid.
//------------------------------------------------------------------------------
BSHP<xms::XmUGrid> TEST_XmUBuildQuadUGrid(const int a_rows,
                                          const int a_cols,
                                          const xms::Pt3d& a_origin)
{
  VecPt3d points;
  points.reserve(a_rows * a_cols);
  for (int i = 0; i < a_rows; ++i)
  {
    for (int j = 0; j < a_cols; ++j)
    {
      points.push_back(Pt3d(j + a_origin.x, a_rows - i + a_origin.y));
    }
  }

  VecInt cells;
  cells.reserve((a_rows - 1) * (a_cols - 1) * 6);
  for (int i = 0; i < a_rows - 1; ++i)
  {
    for (int j = 0; j < a_cols - 1; ++j)
    {
      cells.push_back(XMU_QUAD);
      cells.push_back(4);
      cells.push_back(j + a_cols * i);
      cells.push_back(j + a_cols * (i + 1));
      cells.push_back(j + 1 + a_cols * (i + 1));
      cells.push_back(j + 1 + a_cols * i);
    }
  }

  return XmUGrid::New(points, cells);
} // TEST_XmUBuildQuadUGrid
//------------------------------------------------------------------------------
/// \brief Builds a UGrid of Quads at 1 spacing for rows & cols specified
/// \param[in] a_rows: number of rows in UGrid
/// \param[in] a_cols: number of columns in UGrid
/// \param[in] a_lays: number of layers in UGrid
/// \return Returns the UGrid.
//------------------------------------------------------------------------------
BSHP<xms::XmUGrid> TEST_XmUBuildHexahedronUgrid(const int a_rows,
                                                const int a_cols,
                                                const int a_lays)
{
  Pt3d origin(0.0, 0.0, 0.0);
  return TEST_XmUBuildHexahedronUgrid(a_rows, a_cols, a_lays, origin);
} // TEST_XmUBuildHexahedronUgrid
//------------------------------------------------------------------------------
/// \brief Builds a UGrid of Quads at 1 spacing for rows & cols specified
/// \param[in] a_rows: number of rows in UGrid
/// \param[in] a_cols: number of columns in UGrid
/// \param[in] a_lays: number of layers in UGrid
/// \param[in] a_origin: Point where the UGrid begins (min x, min y, min z)
/// \return Returns the UGrid.
//------------------------------------------------------------------------------
BSHP<xms::XmUGrid> TEST_XmUBuildHexahedronUgrid(const int a_rows,
                                                const int a_cols,
                                                const int a_lays,
                                                const xms::Pt3d& a_origin)
{
  VecPt3d points;
  points.reserve(a_rows * a_cols);
  for (int k = 0; k < a_lays; ++k)
  {
    for (int i = 0; i < a_rows; ++i)
    {
      for (int j = 0; j < a_cols; ++j)
      {
        points.push_back(
          Pt3d(j + a_origin.x, a_rows - i - 1 + a_origin.y, a_lays - k - 1 + a_origin.z));
      }
    }
  }

  VecInt cells;
  cells.reserve((a_rows - 1) * (a_cols - 1) * (a_lays - 1) * 10);
  int numInLayer = a_rows * a_cols;
  for (int k = 0; k < a_lays - 1; ++k)
  {
    int layOffset = numInLayer * k;
    for (int i = 0; i < a_rows - 1; ++i)
    {
      for (int j = 0; j < a_cols - 1; ++j)
      {
        cells.push_back(XMU_HEXAHEDRON);
        cells.push_back(8);
        cells.push_back(j + a_cols * i + layOffset);
        cells.push_back(j + a_cols * (i + 1) + layOffset);
        cells.push_back(j + 1 + a_cols * (i + 1) + layOffset);
        cells.push_back(j + 1 + a_cols * i + layOffset);
        cells.push_back(j + a_cols * i + layOffset + numInLayer);
        cells.push_back(j + a_cols * (i + 1) + layOffset + numInLayer);
        cells.push_back(j + 1 + a_cols * (i + 1) + layOffset + numInLayer);
        cells.push_back(j + 1 + a_cols * i + layOffset + numInLayer);
      }
    }
  }
  return XmUGrid::New(points, cells);
} // TEST_XmUBuildHexahedronUgrid
//------------------------------------------------------------------------------
/// \brief Builds a UGrid of Quads at 1 spacing for rows & cols specified
/// \param[in] a_rows: number of rows in UGrid
/// \param[in] a_cols: number of columns in UGrid
/// \param[in] a_lays: number of layers in UGrid
/// \return Returns the UGrid.
//------------------------------------------------------------------------------
BSHP<xms::XmUGrid> TEST_XmUBuildPolyhedronUgrid(const int a_rows,
                                                const int a_cols,
                                                const int a_lays)
{
  Pt3d origin(0.0, 0.0, 0.0);
  return TEST_XmUBuildPolyhedronUgrid(a_rows, a_cols, a_lays, origin);
} // TEST_XmUBuildPolyhedronUgrid
//------------------------------------------------------------------------------
/// \brief Builds a UGrid of Quads at 1 spacing for rows & cols specified
/// \param[in] a_rows: number of rows in UGrid
/// \param[in] a_cols: number of columns in UGrid
/// \param[in] a_lays: number of layers in UGrid
/// \param[in] a_origin: Point where the UGrid begins (min x, min y, min z)
/// \return Returns the UGrid.
//------------------------------------------------------------------------------
BSHP<xms::XmUGrid> TEST_XmUBuildPolyhedronUgrid(const int a_rows,
                                                const int a_cols,
                                                const int a_lays,
                                                const xms::Pt3d& a_origin)
{
  VecPt3d points;
  points.reserve(a_rows * a_cols);
  for (int k = 0; k < a_lays; ++k)
  {
    for (int i = 0; i < a_rows; ++i)
    {
      for (int j = 0; j < a_cols; ++j)
      {
        points.push_back(Pt3d(j + a_origin.x, a_rows - i + a_origin.y, a_lays - k + a_origin.z));
      }
    }
  }

  VecInt cells;
  cells.reserve((a_rows - 1) * (a_cols - 1) * (a_lays - 1) * 10);
  int numInLayer = a_rows * a_cols;
  for (int k = 0; k < a_lays - 1; ++k)
  {
    int layOffset = numInLayer * k;
    for (int i = 0; i < a_rows - 1; ++i)
    {
      for (int j = 0; j < a_cols - 1; ++j)
      {
        int pt0 = j + a_cols * i + layOffset;
        int pt1 = j + a_cols * (i + 1) + layOffset;
        int pt2 = j + 1 + a_cols * (i + 1) + layOffset;
        int pt3 = j + 1 + a_cols * i + layOffset;
        int pt4 = j + a_cols * i + layOffset + numInLayer;
        int pt5 = j + a_cols * (i + 1) + layOffset + numInLayer;
        int pt6 = j + 1 + a_cols * (i + 1) + layOffset + numInLayer;
        int pt7 = j + 1 + a_cols * i + layOffset + numInLayer;

        cells.push_back(XMU_POLYHEDRON);
        cells.push_back(6);
        // top
        cells.push_back(4);
        cells.push_back(pt0);
        cells.push_back(pt1);
        cells.push_back(pt2);
        cells.push_back(pt3);
        // front
        cells.push_back(4);
        cells.push_back(pt0);
        cells.push_back(pt1);
        cells.push_back(pt5);
        cells.push_back(pt7);
        // right
        cells.push_back(4);
        cells.push_back(pt1);
        cells.push_back(pt3);
        cells.push_back(pt7);
        cells.push_back(pt5);
        // back
        cells.push_back(4);
        cells.push_back(pt3);
        cells.push_back(pt2);
        cells.push_back(pt6);
        cells.push_back(pt7);
        // left
        cells.push_back(4);
        cells.push_back(pt2);
        cells.push_back(pt0);
        cells.push_back(pt4);
        cells.push_back(pt6);
        // bottom
        cells.push_back(4);
        cells.push_back(pt4);
        cells.push_back(pt5);
        cells.push_back(pt6);
        cells.push_back(pt7);
      }
    }
  }
  return XmUGrid::New(points, cells);
} // TEST_XmUBuildPolyhedronUgrid
//------------------------------------------------------------------------------
/// \brief Builds a UGrid with one 3D Chevron polyhedron
/// \return Returns the UGrid.
//------------------------------------------------------------------------------
BSHP<xms::XmUGrid> TEST_XmUBuild3DChevronUgrid()
{
  VecPt3d ugridPoints = {{0.0, 0.0, 0.0},   {20.0, 10.0, 0.0}, {40.0, 0.0, 0.0},
                         {20.0, 50.0, 0.0}, {0.0, 0.0, 10.0},  {20.0, 10.0, 10.0},
                         {40.0, 0.0, 10.0}, {20.0, 50.0, 10.0}};
  // clang-format off
  VecInt ugridCell = { (int)XMU_POLYHEDRON, 6, 
                      4, 0, 3, 2, 1,
                      4, 4, 5, 6, 7,
                      4, 0, 1, 5, 4,
                      4, 1, 2, 6, 5,
                      4, 2, 3, 7, 6,
                      4, 3, 0, 4, 7};
  // clang-format on

  return XmUGrid::New(ugridPoints, ugridCell);
} // TEST_XmUBuild3DChevronUgrid

} // namespace xms

#ifdef CXX_TEST
//------------------------------------------------------------------------------
// Unit Tests
//------------------------------------------------------------------------------
using namespace xms;
#include <xmsgrid/ugrid/XmUGrid.t.h>

//------------------------------------------------------------------------------
/// \brief Path to test files.
/// \return Returns path to test files.
//------------------------------------------------------------------------------
std::string TestFilesPath()
{
  return std::string(XMSGRID_TEST_PATH);
} // TestFilesPath

////////////////////////////////////////////////////////////////////////////////
/// \class XmUGridUnitTests
/// \brief Tests XmUGrids.
////////////////////////////////////////////////////////////////////////////////
//! [snip_test_UGrid_Streams]
//------------------------------------------------------------------------------
/// \brief Test XmUGrid point and cell streams.
//------------------------------------------------------------------------------
void XmUGridUnitTests::testUGridStreams()
{
  // test empty UGrid
  BSHP<XmUGrid> emptyUGrid = XmUGrid::New();
  VecPt3d points = emptyUGrid->GetPoints();
  TS_ASSERT_EQUALS(0, points.size());

  VecInt cellStream = emptyUGrid->GetCellStream();
  TS_ASSERT(XmUGrid::ValidCellStream(cellStream));
  TS_ASSERT_EQUALS(0, cellStream.size());

  // test adding points and cell stream

  //     0----1----2
  //     |    |    |
  //     3----4----5
  //     |    |    |
  //     6----7----8

  BSHP<XmUGrid> ugrid = XmUGrid::New();

  points = {{0, 10, 0}, {10, 10, 0}, {20, 10, 0},  {0, 0, 0},   {10, 0, 0},
            {20, 0, 0}, {0, -10, 0}, {10, -10, 0}, {20, -10, 0}};

  // Cell type (9), number of points (4), point numbers, counterclockwise
  cellStream = {9, 4, 0, 3, 4, 1, 9, 4, 1, 4, 5, 2, 9, 4, 3, 6, 7, 4, 9, 4, 4, 7, 8, 5};

  ugrid->SetPoints(points);
  VecPt3d pointsOut = ugrid->GetPoints();
  TS_ASSERT_EQUALS(points, pointsOut);

  TS_ASSERT(ugrid->SetCellStream(cellStream));
  VecInt cellStreamOut = ugrid->GetCellStream();
  TS_ASSERT_EQUALS(cellStream, cellStreamOut);

  // Test invalid cell streams
  cellStream = {-1};
  TS_ASSERT(!XmUGrid::ValidCellStream(cellStream));
  cellStream = {9, 4, 0, 3, 4};
  TS_ASSERT(!XmUGrid::ValidCellStream(cellStream));
  cellStream = {9, 3, 0, 3, 4, 1};
  TS_ASSERT(!XmUGrid::ValidCellStream(cellStream));

  // Test adding cellstream then points (should fail)
  BSHP<XmUGrid> ugridBadOrder = XmUGrid::New();
  TS_ASSERT(!ugridBadOrder->SetCellStream(cellStream));

} // XmUGridUnitTests::testUGridStreams
//! [snip_test_UGrid_Streams]
////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
/// \brief Test Getting a point

//------------------------------------------------------------------------------
void XmUGridUnitTests::testGetSetPoint()
{
  //     0----1----2
  //     |    |    |
  //     3----4----5
  //     |    |    |
  //     6----7----8

  //! [snip_test_NewOperator]
  VecPt3d points = {{0, 10, 0}, {10, 10, 10}, {20, 10, 0},  {0, 0, 0},   {10, 0, 0},
                    {20, 0, 0}, {0, -10, 0}, {10, -10, 0}, {20, -10, 0}};

  // Cell type (9), number of points (4), point numbers, counterclockwise
  VecInt cellStream = {9, 4, 0, 3, 4, 1, 9, 4, 1, 4, 5, 2, 9, 4, 3, 6, 7, 4, 9, 4, 4, 7, 8, 5};

  BSHP<XmUGrid> ugrid = XmUGrid::New(points, cellStream);
  //! [snip_test_NewOperator]

  TS_ASSERT_EQUALS(Pt3d(), ugrid->GetPoint(-1));
  for (int i = 0; i < (int)points.size(); i++)
  {
    TS_ASSERT_EQUALS(points[i], ugrid->GetPoint(i));
  }
  TS_ASSERT_EQUALS(Pt3d(10, 10, 0), ugrid->GetXYPoint(1));
  TS_ASSERT_EQUALS(Pt3d(), ugrid->GetPoint((int)points.size()));

  TS_ASSERT(!ugrid->SetPoint(-1, Pt3d()));
  TS_ASSERT(!ugrid->SetPoint((int)points.size(), Pt3d()));

  TS_ASSERT(ugrid->SetPoint(0, Pt3d(-10, 10, 0)));
  TS_ASSERT_EQUALS(Pt3d(-10, 10, 0), ugrid->GetPoint(0));

} // XmUGridUnitTests::testGetSetPoint
////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
/// \brief Test Getting a cell stream.
//------------------------------------------------------------------------------
void XmUGridUnitTests::testGetSingleCellStream()
{
  //     0-----1-----2
  //     |  0  |  1  |
  //     3-----4-----5
  //     |  2  |  3  |
  //     6-----7-----8

  VecPt3d points = {{0, 10, 0}, {10, 10, 0}, {20, 10, 0},  {0, 0, 0},   {10, 0, 0},
                    {20, 0, 0}, {0, -10, 0}, {10, -10, 0}, {20, -10, 0}};

  VecInt cell0 = {9, 4, 0, 3, 4, 1}, cell1 = {9, 4, 1, 4, 5, 2}, cell2 = {9, 4, 3, 6, 7, 4},
         cell3 = {9, 4, 4, 7, 8, 5};
  // Cell type (9), number of points (4), point numbers, counterclockwise
  VecInt cellStream;
  cellStream.insert(cellStream.end(), cell0.begin(), cell0.end());
  cellStream.insert(cellStream.end(), cell1.begin(), cell1.end());
  cellStream.insert(cellStream.end(), cell2.begin(), cell2.end());
  cellStream.insert(cellStream.end(), cell3.begin(), cell3.end());

  BSHP<XmUGrid> ugrid = XmUGrid::New(points, cellStream);
  VecInt cellResult;

  TS_ASSERT_EQUALS(false, ugrid->GetSingleCellStream(-1, cellResult));

  TS_ASSERT_EQUALS(true, ugrid->GetSingleCellStream(0, cellResult));
  TS_ASSERT_EQUALS(cell0, cellResult);
  TS_ASSERT_EQUALS(true, ugrid->GetSingleCellStream(1, cellResult));
  TS_ASSERT_EQUALS(cell1, cellResult);
  TS_ASSERT_EQUALS(true, ugrid->GetSingleCellStream(2, cellResult));
  TS_ASSERT_EQUALS(cell2, cellResult);
  TS_ASSERT_EQUALS(true, ugrid->GetSingleCellStream(3, cellResult));
  TS_ASSERT_EQUALS(cell3, cellResult);

  TS_ASSERT_EQUALS(false, ugrid->GetSingleCellStream((int)points.size(), cellResult));

} // XmUGridUnitTests::testGetSingleCellStream
//------------------------------------------------------------------------------
/// \brief Test getting number of points, cells, and cell type.
//------------------------------------------------------------------------------
void XmUGridUnitTests::testGetCellType()
{
  BSHP<XmUGrid> ugrid2d = TEST_XmUGrid2dLinear();
  if (!ugrid2d)
  {
    TS_FAIL("Unable to create UGrid.");
    return;
  }
  TS_ASSERT_EQUALS(14, ugrid2d->GetNumberOfPoints());
  TS_ASSERT_EQUALS(6, ugrid2d->GetNumberOfCells());
  TS_ASSERT_EQUALS(XMU_INVALID_CELL_TYPE, ugrid2d->GetCellType(-1));
  TS_ASSERT_EQUALS(XMU_INVALID_CELL_TYPE, ugrid2d->GetCellType(6));
  TS_ASSERT_EQUALS(XMU_QUAD, ugrid2d->GetCellType(0));
  TS_ASSERT_EQUALS(XMU_PIXEL, ugrid2d->GetCellType(1));
  TS_ASSERT_EQUALS(XMU_TRIANGLE, ugrid2d->GetCellType(2));
  TS_ASSERT_EQUALS(XMU_POLYGON, ugrid2d->GetCellType(3));
  TS_ASSERT_EQUALS(XMU_POLY_LINE, ugrid2d->GetCellType(4));
  TS_ASSERT_EQUALS(XMU_LINE, ugrid2d->GetCellType(5));

  BSHP<XmUGrid> ugrid3d = TEST_XmUGrid3dLinear();
  if (!ugrid3d)
  {
    TS_FAIL("Unable to create UGrid.");
    return;
  }
  TS_ASSERT_EQUALS(30, ugrid3d->GetNumberOfPoints());
  TS_ASSERT_EQUALS(6, ugrid3d->GetNumberOfCells());
  TS_ASSERT_EQUALS(XMU_INVALID_CELL_TYPE, ugrid3d->GetCellType(-1));
  TS_ASSERT_EQUALS(XMU_INVALID_CELL_TYPE, ugrid3d->GetCellType(6));
  TS_ASSERT_EQUALS(XMU_TETRA, ugrid3d->GetCellType(0));
  TS_ASSERT_EQUALS(XMU_VOXEL, ugrid3d->GetCellType(1));
  TS_ASSERT_EQUALS(XMU_HEXAHEDRON, ugrid3d->GetCellType(2));
  TS_ASSERT_EQUALS(XMU_POLYHEDRON, ugrid3d->GetCellType(3));
  TS_ASSERT_EQUALS(XMU_WEDGE, ugrid3d->GetCellType(4));
  TS_ASSERT_EQUALS(XMU_PYRAMID, ugrid3d->GetCellType(5));
} // XmUGridUnitTests::testGetCellType
//------------------------------------------------------------------------------
/// \brief Test getting dimension of single cells and all cells.
//------------------------------------------------------------------------------
void XmUGridUnitTests::testGetCellDimension()
{
  BSHP<XmUGrid> ugrid2d = TEST_XmUGrid2dLinear();
  if (!ugrid2d)
  {
    TS_FAIL("Unable to create UGrid.");
    return;
  }

  TS_ASSERT_EQUALS(XMU_INVALID_CELL_TYPE, ugrid2d->GetCellDimension(-1));
  TS_ASSERT_EQUALS(XMU_INVALID_CELL_TYPE, ugrid2d->GetCellDimension(6));
  TS_ASSERT_EQUALS(2, ugrid2d->GetCellDimension(0));
  TS_ASSERT_EQUALS(2, ugrid2d->GetCellDimension(1));
  TS_ASSERT_EQUALS(2, ugrid2d->GetCellDimension(2));
  TS_ASSERT_EQUALS(2, ugrid2d->GetCellDimension(3));
  TS_ASSERT_EQUALS(1, ugrid2d->GetCellDimension(4));
  TS_ASSERT_EQUALS(1, ugrid2d->GetCellDimension(5));

  BSHP<XmUGrid> ugrid3d = TEST_XmUGrid3dLinear();
  if (!ugrid3d)
  {
    TS_FAIL("Unable to create UGrid.");
    return;
  }
  TS_ASSERT_EQUALS(XMU_INVALID_CELL_TYPE, ugrid3d->GetCellDimension(-1));
  TS_ASSERT_EQUALS(XMU_INVALID_CELL_TYPE, ugrid3d->GetCellDimension(6));
  TS_ASSERT_EQUALS(3, ugrid3d->GetCellDimension(0));
  TS_ASSERT_EQUALS(3, ugrid3d->GetCellDimension(1));
  TS_ASSERT_EQUALS(3, ugrid3d->GetCellDimension(2));
  TS_ASSERT_EQUALS(3, ugrid3d->GetCellDimension(3));
  TS_ASSERT_EQUALS(3, ugrid3d->GetCellDimension(4));
  TS_ASSERT_EQUALS(3, ugrid3d->GetCellDimension(5));

  // Test Dimension Counts
  std::vector<int> twoDResults(4, 0), threeDResults(4, 0);
  twoDResults[1] = 2;
  twoDResults[2] = 4;
  threeDResults[3] = 6;
  TS_ASSERT_EQUALS(twoDResults, ugrid2d->GetDimensionCount());
  TS_ASSERT_EQUALS(threeDResults, ugrid3d->GetDimensionCount());
} // XmUGridUnitTests::testGetCellDimension
//------------------------------------------------------------------------------
/// \brief Test getting the extents of a UGrid
//------------------------------------------------------------------------------
void XmUGridUnitTests::testGetExtents()
{
  BSHP<XmUGrid> ugrid2d = TEST_XmUGrid2dLinear();
  if (!ugrid2d)
  {
    TS_FAIL("Unable to create UGrid.");
    return;
  }

  Pt3d min, max;
  Pt3d expectedMin = {0.0, 0.0, 0.0}, expectMax = {40.0, 20.0, 0.0};
  ugrid2d->GetExtents(min, max);
  TS_ASSERT_EQUALS(expectedMin, min);
  TS_ASSERT_EQUALS(expectMax, max);

  BSHP<XmUGrid> ugrid3d = TEST_XmUGrid3dLinear();
  if (!ugrid3d)
  {
    TS_FAIL("Unable to create UGrid.");
    return;
  }

  expectedMin = {0.0, 0.0, 0.0};
  expectMax = {40.0, 20.0, 10.0};
  ugrid3d->GetExtents(min, max);
  TS_ASSERT_EQUALS(expectedMin, min);
  TS_ASSERT_EQUALS(expectMax, max);

  Pt3d origin(-25.0, -25.0, -15.0);
  BSHP<XmUGrid> ugridBuild = TEST_XmUBuildHexahedronUgrid(51, 51, 31, origin);
  if (!ugridBuild)
  {
    TS_FAIL("Unable to create UGrid.");
    return;
  }
  expectedMin = {-25.0, -25.0, -15.0};
  expectMax = {25.0, 25.0, 15.0};
  ugridBuild->GetExtents(min, max);
  TS_ASSERT_EQUALS(expectedMin, min);
  TS_ASSERT_EQUALS(expectMax, max);
} // XmUGridUnitTests::testGetExtents
//------------------------------------------------------------------------------
/// \brief Test getting edges of single cells.
//------------------------------------------------------------------------------
void XmUGridUnitTests::testGetNumberOfCellEdges()
{
  BSHP<XmUGrid> ugrid2d = TEST_XmUGrid2dLinear();
  if (!ugrid2d)
  {
    TS_FAIL("Unable to create UGrid.");
    return;
  }

  TS_ASSERT_EQUALS(-1, ugrid2d->GetNumberOfCellEdges(-1));
  TS_ASSERT_EQUALS(-1, ugrid2d->GetNumberOfCellEdges(6));
  TS_ASSERT_EQUALS(4, ugrid2d->GetNumberOfCellEdges(0));
  TS_ASSERT_EQUALS(4, ugrid2d->GetNumberOfCellEdges(1));
  TS_ASSERT_EQUALS(3, ugrid2d->GetNumberOfCellEdges(2));
  TS_ASSERT_EQUALS(6, ugrid2d->GetNumberOfCellEdges(3));
  TS_ASSERT_EQUALS(2, ugrid2d->GetNumberOfCellEdges(4));
  TS_ASSERT_EQUALS(1, ugrid2d->GetNumberOfCellEdges(5));

  BSHP<XmUGrid> ugrid3d = TEST_XmUGrid3dLinear();
  if (!ugrid3d)
  {
    TS_FAIL("Unable to create UGrid.");
    return;
  }

  TS_ASSERT_EQUALS(-1, ugrid3d->GetNumberOfCellEdges(-1));
  TS_ASSERT_EQUALS(-1, ugrid3d->GetNumberOfCellEdges(6));
  TS_ASSERT_EQUALS(6, ugrid3d->GetNumberOfCellEdges(0));
  TS_ASSERT_EQUALS(12, ugrid3d->GetNumberOfCellEdges(1));
  TS_ASSERT_EQUALS(12, ugrid3d->GetNumberOfCellEdges(2));
  TS_ASSERT_EQUALS(12, ugrid3d->GetNumberOfCellEdges(3));
  TS_ASSERT_EQUALS(9, ugrid3d->GetNumberOfCellEdges(4));
  TS_ASSERT_EQUALS(8, ugrid3d->GetNumberOfCellEdges(5));

} // XmUGridUnitTests::testGetNumberOfCellEdges
//! [snip_test_GetNumberOfCellFaces]
//------------------------------------------------------------------------------
/// \brief Test getting edges of single cells.
//------------------------------------------------------------------------------
void XmUGridUnitTests::testGetNumberOfCellFaces()
{
  BSHP<XmUGrid> ugrid2d = TEST_XmUGrid2dLinear();
  if (!ugrid2d)
  {
    TS_FAIL("Unable to create UGrid.");
    return;
  }

  // test 1D and 2D cells
  TS_ASSERT_EQUALS(-1, ugrid2d->GetNumberOfCellFaces(-1));
  for (int cellIdx = 0; cellIdx < ugrid2d->GetNumberOfCells(); ++cellIdx)
  {
    TS_ASSERT_EQUALS(0, ugrid2d->GetNumberOfCellFaces(cellIdx));
  }
  TS_ASSERT_EQUALS(-1, ugrid2d->GetNumberOfCellFaces(ugrid2d->GetNumberOfCells()));

  BSHP<XmUGrid> ugrid3d = TEST_XmUGrid3dLinear();
  if (!ugrid3d)
  {
    TS_FAIL("Unable to create UGrid.");
    return;
  }

  // test 3D cells
  TS_ASSERT_EQUALS(-1, ugrid3d->GetNumberOfCellFaces(-1));
  TS_ASSERT_EQUALS(-1, ugrid3d->GetNumberOfCellFaces(6));
  TS_ASSERT_EQUALS(4, ugrid3d->GetNumberOfCellFaces(0));
  TS_ASSERT_EQUALS(6, ugrid3d->GetNumberOfCellFaces(1));
  TS_ASSERT_EQUALS(6, ugrid3d->GetNumberOfCellFaces(2));
  TS_ASSERT_EQUALS(6, ugrid3d->GetNumberOfCellFaces(3));
  TS_ASSERT_EQUALS(5, ugrid3d->GetNumberOfCellFaces(4));
  TS_ASSERT_EQUALS(5, ugrid3d->GetNumberOfCellFaces(5));
} // XmUGridUnitTests::testGetNumberOfCellFaces
//! [snip_test_GetNumberOfCellFaces]
//------------------------------------------------------------------------------
/// \brief Test getting the number of face points for a cell face.
//------------------------------------------------------------------------------
void XmUGridUnitTests::testGetNumberOfFacePoints()
{
  BSHP<XmUGrid> ugrid2d = TEST_XmUGrid2dLinear();
  if (!ugrid2d)
  {
    TS_FAIL("Unable to create UGrid.");
    return;
  }

  // test 1D and 2D cells - should return 0 for valid cell index
  TS_ASSERT_EQUALS(-1, ugrid2d->GetNumberOfFacePoints(-1, 0));
  TS_ASSERT_EQUALS(0, ugrid2d->GetNumberOfFacePoints(1, 0));
  TS_ASSERT_EQUALS(-1, ugrid2d->GetNumberOfFacePoints(ugrid2d->GetNumberOfCells(), 0));

  BSHP<XmUGrid> ugrid3d = TEST_XmUGrid3dLinear();
  if (!ugrid3d)
  {
    TS_FAIL("Unable to create UGrid.");
    return;
  }

  // test 3D cells
  TS_ASSERT_EQUALS(-1, ugrid3d->GetNumberOfFacePoints(-1, 0));
  TS_ASSERT_EQUALS(-1, ugrid3d->GetNumberOfFacePoints(6, 0));
  TS_ASSERT_EQUALS(4, ugrid3d->GetNumberOfFacePoints(1, 3));
  TS_ASSERT_EQUALS(4, ugrid3d->GetNumberOfFacePoints(3, 2));
} // XmUGridUnitTests::testGetNumberOfFacePoints
//------------------------------------------------------------------------------
/// \brief Test getting the cells attached to points.
//------------------------------------------------------------------------------
void XmUGridUnitTests::testGetPointCellsSimple()
{
  //     0----1----2
  //     |    |    |
  //     3----4----5

  VecPt3d points = {{0, 10, 0}, {10, 10, 0}, {20, 10, 0}, {0, 0, 0}, {10, 0, 0}, {20, 0, 0}};

  VecInt cellStream = {XMU_QUAD, 4, 0, 3, 4, 1, XMU_QUAD, 4, 1, 4, 5, 2};

  BSHP<XmUGrid> ugrid = XmUGrid::New(points, cellStream);

  VecInt cellEmpty = {};
  VecInt cellZero = {0};
  VecInt cellZeroAndOne = {0, 1};
  VecInt cellOne = {1};
  TS_ASSERT_EQUALS(cellEmpty, ugrid->GetPointCells(-1));
  TS_ASSERT_EQUALS(cellZero, ugrid->GetPointCells(0));
  TS_ASSERT_EQUALS(cellZeroAndOne, ugrid->GetPointCells(1));
  TS_ASSERT_EQUALS(cellOne, ugrid->GetPointCells(2));
  TS_ASSERT_EQUALS(cellZero, ugrid->GetPointCells(3));
  TS_ASSERT_EQUALS(cellZeroAndOne, ugrid->GetPointCells(4));
  TS_ASSERT_EQUALS(cellOne, ugrid->GetPointCells(5));
  TS_ASSERT_EQUALS(cellEmpty, ugrid->GetPointCells(6));

} // XmUGridUnitTests::testGetNumberOfCellFaces

//------------------------------------------------------------------------------
/// \brief Test getting edges of single cells.
//------------------------------------------------------------------------------
void XmUGridUnitTests::testGetPointCells()
{
  BSHP<XmUGrid> ugrid2d = TEST_XmUGrid2dLinear();
  if (!ugrid2d)
  {
    TS_FAIL("Unable to create UGrid.");
    return;
  }

  VecInt2d cellsFor2DPoints = {{0},          // point 0
                               {0, 1},       // point 1
                               {1, 2},       // point 2
                               {2, 3},       // point 3
                               {3},          // point 4
                               {0, 5},       // point 5
                               {0, 1},       // point 6
                               {1, 2, 3, 4}, // point 7
                               {3},          // point 8
                               {5},          // point 9
                               {4},          // point 10
                               {4},          // point 11
                               {3},          // point 12
                               {3}};         // point 13

  // test 1D and 2D cells
  for (int i(0); i < cellsFor2DPoints.size(); i++)
  {
    TS_ASSERT_EQUALS(cellsFor2DPoints[i], ugrid2d->GetPointCells(i));
  }

  BSHP<XmUGrid> ugrid3d = TEST_XmUGrid3dLinear();
  if (!ugrid3d)
  {
    TS_FAIL("Unable to create UGrid.");
    return;
  }
  VecInt2d cellsFor3DPoints = {{0},       // point 0
                               {0, 1},    // point 1
                               {1, 2},    // point 2
                               {2, 4},    // point 3
                               {4},       // point 4
                               {0, 5},    // point 5
                               {1, 5},    // point 6
                               {1, 2},    // point 7
                               {2, 3, 4}, // point 8
                               {3, 4},    // point 9
                               {5},       // point 10
                               {5},       // point 11
                               {},        // point 12
                               {3},       // point 13
                               {3},       // point 14
                               {0},       // point 15
                               {1},       // point 16
                               {1, 2},    // point 17
                               {2, 4},    // point 18
                               {},        // point 19
                               {5},       // point 20
                               {1},       // point 21
                               {1, 2},    // point 22
                               {2, 3, 4}, // point 23
                               {3},       // point 24
                               {},        // point 25
                               {},        // point 26
                               {},        // point 27
                               {3},       // point 28
                               {3},       // point 29
                               {}};       // point 30

  // test 3D cells
  for (int i(0); i < cellsFor3DPoints.size(); i++)
  {
    if (cellsFor3DPoints[i] != ugrid3d->GetPointCells(i))
    {
      TS_FAIL(i);
    }
    TS_ASSERT_EQUALS(cellsFor3DPoints[i], ugrid3d->GetPointCells(i));
  }

} // XmUGridUnitTests::testGetPointCells
//------------------------------------------------------------------------------
/// \brief Test getting a vector of point indexes for a cell
//------------------------------------------------------------------------------
void XmUGridUnitTests::testGetPointsOfCell()
{
  BSHP<XmUGrid> ugrid = TEST_XmUGridSimpleQuad();
  if (!ugrid)
  {
    TS_FAIL("Unable to create UGrid.");
    return;
  }

  VecInt2d expectedCellPoints = {{0, 3, 4, 1}, {1, 4, 5, 2}, {3, 6, 7, 4}, {4, 7, 8, 5}};
  VecInt2d cellPoints;
  VecInt cellPoint1D;
  TS_ASSERT(!ugrid->GetPointsOfCell(-1, cellPoint1D));
  TS_ASSERT(!ugrid->GetPointsOfCell(5, cellPoint1D));

  for (int i(0); i < ugrid->GetNumberOfCells(); i++)
  {
    TS_ASSERT(ugrid->GetPointsOfCell(i, cellPoint1D));
    cellPoints.push_back(cellPoint1D);
    TS_ASSERT_EQUALS(expectedCellPoints[i], cellPoints[i]);
  }

  expectedCellPoints = {{0, 1, 6, 5},         {1, 2, 7, 6}, {2, 3, 7},
                        {3, 4, 8, 13, 12, 7}, {7, 11, 10},  {5, 9}};
  cellPoints.clear();
  BSHP<XmUGrid> ugrid2d = TEST_XmUGrid2dLinear();
  if (!ugrid2d)
  {
    TS_FAIL("Unable to create UGrid.");
    return;
  }

  for (int i(0); i < ugrid2d->GetNumberOfCells(); i++)
  {
    TS_ASSERT(ugrid2d->GetPointsOfCell(i, cellPoint1D));
    cellPoints.push_back(cellPoint1D);
    TS_ASSERT_EQUALS(expectedCellPoints[i], cellPoints[i]);
  }

  expectedCellPoints = {{0, 1, 5, 15},
                        {1, 2, 6, 7, 16, 17, 21, 22},
                        {2, 3, 8, 7, 17, 18, 23, 22},
                        {8, 9, 14, 13, 24, 23, 29, 28},
                        {3, 4, 18, 8, 9, 23},
                        {5, 6, 11, 10, 20}};
  cellPoints.clear();
  BSHP<XmUGrid> ugrid3d = TEST_XmUGrid3dLinear();
  if (!ugrid3d)
  {
    TS_FAIL("Unable to create UGrid.");
    return;
  }

  for (int i(0); i < ugrid3d->GetNumberOfCells(); i++)
  {
    TS_ASSERT(ugrid3d->GetPointsOfCell(i, cellPoint1D));
    cellPoints.push_back(cellPoint1D);
    TS_ASSERT_EQUALS(expectedCellPoints[i], cellPoints[i]);
  }

} // XmUGridUnitTests::testGetPointsOfCell

//------------------------------------------------------------------------------
/// \brief Test iterating through the edges of cells
//------------------------------------------------------------------------------
void XmUGridUnitTests::testGetCellEdgeFromEdgeIndex()
{
  //     0-----1-----2
  //     |  0  |  1  |
  //     3-----4-----5
  //     |  2  |  3  |
  //     6-----7-----8

  // 2D shape (simple)
  BSHP<XmUGrid> ugrid = TEST_XmUGridSimpleQuad();
  if (!ugrid)
  {
    TS_FAIL("Unable to create UGrid.");
    return;
  }

  {
    std::pair<int, int> edge0(0, 3), edge1(3, 4), edge2(4, 1), edge3(1, 0);     // cell 0
    std::pair<int, int> edge4(1, 4), edge5(4, 5), edge6(5, 2), edge7(2, 1);     // cell 1
    std::pair<int, int> edge8(3, 6), edge9(6, 7), edge10(7, 4), edge11(4, 3);   // cell 2
    std::pair<int, int> edge12(4, 7), edge13(7, 8), edge14(8, 5), edge15(5, 4); // cell 3
    std::pair<int, int> emptyEdge;
    std::vector<std::vector<std::pair<int, int>>> expectedCellsCellEdges;
    std::vector<std::pair<int, int>> emptyVec = {emptyEdge};
    std::vector<std::pair<int, int>> cellEdges;

    cellEdges.push_back(ugrid->GetCellEdgeFromEdgeIndex(0, -1));
    TS_ASSERT_EQUALS(emptyVec, cellEdges);

    cellEdges.clear();
    cellEdges.push_back(ugrid->GetCellEdgeFromEdgeIndex(0, ugrid->GetNumberOfCellEdges(0)));
    TS_ASSERT_EQUALS(emptyVec, cellEdges);

    cellEdges.clear();
    expectedCellsCellEdges = {{edge0, edge1, edge2, edge3},
                              {edge4, edge5, edge6, edge7},
                              {edge8, edge9, edge10, edge11},
                              {edge12, edge13, edge14, edge15}};
    for (int i(0); i < ugrid->GetNumberOfCells(); i++)
    {
      for (int j(0); j < ugrid->GetNumberOfCellEdges(i); j++)
      {
        cellEdges.push_back(ugrid->GetCellEdgeFromEdgeIndex(i, j));
      }
      TS_ASSERT_EQUALS(expectedCellsCellEdges[i], cellEdges);
      cellEdges.clear();
    }
  }
  //! [snip_test_GetCellEdgeFromEdgeIndex2D]
  {
    std::pair<int, int> edge0(0, 1), edge1(1, 6), edge2(6, 5), edge3(5, 0); // Quad
    std::pair<int, int> edge4(1, 2), edge5(2, 7), edge6(7, 6), edge7(6, 1); // Pixel
    std::pair<int, int> edge8(2, 3), edge9(3, 7), edge10(7, 2);             // Triangle
    std::pair<int, int> edge11(3, 4), edge12(4, 8), edge13(8, 13), edge14(13, 12), edge15(12, 7),
      edge16(7, 3);                                    // Polygon
    std::pair<int, int> edge17(7, 11), edge18(11, 10); // PolyLine
    std::pair<int, int> edge19(5, 9);                  // Line

    // 2D Shapes
    BSHP<XmUGrid> ugrid2d = TEST_XmUGrid2dLinear();
    if (!ugrid2d)
    {
      TS_FAIL("Unable to create UGrid.");
      return;
    }

    std::vector<std::vector<std::pair<int, int>>> expectedCellsCellEdges;
    expectedCellsCellEdges = {{edge0, edge1, edge2, edge3},
                              {edge4, edge5, edge6, edge7},
                              {edge8, edge9, edge10},
                              {edge11, edge12, edge13, edge14, edge15, edge16},
                              {edge17, edge18},
                              {edge19}};
    std::vector<std::pair<int, int>> cellEdges;
    for (int i(0); i < ugrid2d->GetNumberOfCells(); i++)
    {
      for (int j(0); j < ugrid2d->GetNumberOfCellEdges(i); j++)
      {
        cellEdges.push_back(ugrid2d->GetCellEdgeFromEdgeIndex(i, j));
      }
      TS_ASSERT_EQUALS(expectedCellsCellEdges[i], cellEdges);
      cellEdges.clear();
    }
  }
  //! [snip_test_GetCellEdgeFromEdgeIndex2D]

  //! [snip_test_GetCellEdgeFromEdgeIndex3D]
  {
    // 3D Shapes
    BSHP<XmUGrid> ugrid3d = TEST_XmUGrid3dLinear();
    if (!ugrid3d)
    {
      TS_FAIL("Unable to create UGrid.");
      return;
    }

    // clang-format off
    std::vector<std::vector<std::pair<int, int>>> expectedCellsCellEdges =
    {
      {{0, 1}, {1, 5}, {5, 0}, {0, 15}, {1, 15}, {5, 15}}, // XMU_TETRA
      {{1, 2}, {2, 7}, {6, 7}, {1, 6}, {16, 17}, {17, 22}, {21, 22}, {16, 21}, {1, 16}, {2, 17}, {6, 21}, {7, 22}}, // XMU_VOXEL
      {{2, 3}, {3, 8}, {7, 8}, {2, 7}, {17, 18}, {18, 23}, {22, 23}, {17, 22}, {2, 17}, {3, 18}, {7, 22}, {8, 23}}, // XMU_HEXAHEDRON
      {{8, 9}, {8, 13}, {8, 23}, {9, 14}, {9, 24}, {13, 14}, {13, 28}, {14, 29}, {23, 24}, {23, 28}, {24, 29}, {28, 29}}, // XMU_POLYHEDRON
      {{3, 4}, {4, 18}, {18, 3}, {8, 9}, {9, 23}, {23, 8}, {3, 8}, {4, 9}, {18, 23}}, // XMU_WEDGE
      {{5, 6}, {6, 11}, {11, 10}, {10, 5}, {5, 20}, {6, 20}, {11, 20}, {10, 20}} // XMU_PYRAMID
    };
    // clang-format on
    std::vector<std::pair<int, int>> cellEdges;
    for (int i(0); i < ugrid3d->GetNumberOfCells(); i++)
    {
      for (int j(0); j < ugrid3d->GetNumberOfCellEdges(i); j++)
      {
        cellEdges.push_back(ugrid3d->GetCellEdgeFromEdgeIndex(i, j));
      }
      TS_ASSERT_EQUALS(expectedCellsCellEdges[i], cellEdges);
      cellEdges.clear();
    }
  }
  //! [snip_test_GetCellEdgeFromEdgeIndex3D]
} // XmUGridUnitTests::testGetCellEdgeFromEdgeIndex

//------------------------------------------------------------------------------
/// \brief Test retrieving common cells from points
//------------------------------------------------------------------------------
void XmUGridUnitTests::testGetCommonCells()
{
  //     0-----1-----2
  //     |  0  |  1  |
  //     3-----4-----5
  //     |  2  |  3  |
  //     6-----7-----8

  BSHP<XmUGrid> ugrid = TEST_XmUGridSimpleQuad();
  if (!ugrid)
  {
    TS_FAIL("Unable to create UGrid.");
    return;
  }

  VecInt expectedCells;
  VecInt points = {-1, 0};
  VecInt retrievedCells;
  retrievedCells = ugrid->GetCommonCells(points);
  TS_ASSERT_EQUALS(expectedCells, retrievedCells);

  points = {0, -1};
  retrievedCells = ugrid->GetCommonCells(points);
  TS_ASSERT_EQUALS(expectedCells, retrievedCells);

  points = {0, 8};
  retrievedCells = ugrid->GetCommonCells(points);
  TS_ASSERT_EQUALS(expectedCells, retrievedCells);
  expectedCells.clear();
  points.clear();
  retrievedCells.clear();

  expectedCells = {0, 2};
  points = {3, 4};
  retrievedCells = ugrid->GetCommonCells(points);
  TS_ASSERT_EQUALS(expectedCells, retrievedCells);
  expectedCells.clear();
  points.clear();
  retrievedCells.clear();

  expectedCells = {0};
  points = {0, 3};
  retrievedCells = ugrid->GetCommonCells(points);
  TS_ASSERT_EQUALS(expectedCells, retrievedCells);
  expectedCells.clear();
  points.clear();
  retrievedCells.clear();

  points = {3, 4, 5};
  retrievedCells = ugrid->GetCommonCells(points);
  TS_ASSERT_EQUALS(expectedCells, retrievedCells);
  expectedCells.clear();
  points.clear();
  retrievedCells.clear();

  points = {ugrid->GetNumberOfPoints(), 0};
  retrievedCells = ugrid->GetCommonCells(points);
  TS_ASSERT_EQUALS(expectedCells, retrievedCells);

  points = {0, ugrid->GetNumberOfPoints()};
  retrievedCells = ugrid->GetCommonCells(points);
  TS_ASSERT_EQUALS(expectedCells, retrievedCells);

} // XmUGridUnitTests::testGetCommonCells

//! [snip_test_GetCellNeighbors]
//------------------------------------------------------------------------------
/// \brief Test retrieving Cell Neighbors
//------------------------------------------------------------------------------
void XmUGridUnitTests::testGetCellNeighbors()
{
  //     0-----1-----2
  //     |  0  |  1  |
  //     3-----4-----5
  //     |  2  |  3  |
  //     6-----7-----8

  BSHP<XmUGrid> ugrid = TEST_XmUGridSimpleQuad();
  if (!ugrid)
  {
    TS_FAIL("Unable to create UGrid.");
    return;
  }

  VecInt expectedCells;

  VecInt retrievedCells;
  retrievedCells = ugrid->GetCellNeighbors(-1);
  TS_ASSERT_EQUALS(expectedCells, retrievedCells);
  retrievedCells = ugrid->GetCellNeighbors(0);
  expectedCells = {2, 1, 3};
  TS_ASSERT_EQUALS(expectedCells, retrievedCells);
  expectedCells.clear();
  retrievedCells = ugrid->GetCellNeighbors(4);
  TS_ASSERT_EQUALS(expectedCells, retrievedCells);
  expectedCells.clear();
  retrievedCells = ugrid->GetCellNeighbors(5);
  TS_ASSERT_EQUALS(expectedCells, retrievedCells);
  expectedCells.clear();
  retrievedCells.clear();

  // 2D Shapes
  BSHP<XmUGrid> ugrid2d = TEST_XmUGrid2dLinear();
  if (!ugrid2d)
  {
    TS_FAIL("Unable to create UGrid.");
    return;
  }

  expectedCells = {1, 5};
  retrievedCells = ugrid2d->GetCellNeighbors(0);
  TS_ASSERT_EQUALS(expectedCells, retrievedCells);
  expectedCells = {0, 2, 3, 4};
  retrievedCells = ugrid2d->GetCellNeighbors(1);
  TS_ASSERT_EQUALS(expectedCells, retrievedCells);
  expectedCells = {1, 3, 4};
  retrievedCells = ugrid2d->GetCellNeighbors(2);
  TS_ASSERT_EQUALS(expectedCells, retrievedCells);
  expectedCells = {2, 1, 4};
  retrievedCells = ugrid2d->GetCellNeighbors(3);
  TS_ASSERT_EQUALS(expectedCells, retrievedCells);
  expectedCells = {1, 2, 3};
  retrievedCells = ugrid2d->GetCellNeighbors(4);
  TS_ASSERT_EQUALS(expectedCells, retrievedCells);
  expectedCells = {0};
  retrievedCells = ugrid2d->GetCellNeighbors(5);
  TS_ASSERT_EQUALS(expectedCells, retrievedCells);

  // 3D Shapes
  BSHP<XmUGrid> ugrid3d = TEST_XmUGrid3dLinear();
  if (!ugrid3d)
  {
    TS_FAIL("Unable to create UGrid.");
    return;
  }

  expectedCells = {1, 5};
  retrievedCells = ugrid3d->GetCellNeighbors(0);
  TS_ASSERT_EQUALS(expectedCells, retrievedCells);
  expectedCells = {0, 2, 5};
  retrievedCells = ugrid3d->GetCellNeighbors(1);
  TS_ASSERT_EQUALS(expectedCells, retrievedCells);
  expectedCells = {1, 4, 3};
  retrievedCells = ugrid3d->GetCellNeighbors(2);
  TS_ASSERT_EQUALS(expectedCells, retrievedCells);
  expectedCells = {2, 4};
  retrievedCells = ugrid3d->GetCellNeighbors(3);
  TS_ASSERT_EQUALS(expectedCells, retrievedCells);
  expectedCells = {2, 3};
  retrievedCells = ugrid3d->GetCellNeighbors(4);
  TS_ASSERT_EQUALS(expectedCells, retrievedCells);
  expectedCells = {0, 1};
  retrievedCells = ugrid3d->GetCellNeighbors(5);
  TS_ASSERT_EQUALS(expectedCells, retrievedCells);

} // XmUGridUnitTests::testGetCellNeighbors
//! [snip_test_GetCellNeighbors]
//------------------------------------------------------------------------------
/// \brief Test retrieving Adjacent Cell
//------------------------------------------------------------------------------
void XmUGridUnitTests::testGetAdjacentCell()
{
  //     0-----1-----2
  //     |  0  |  1  |
  //     3-----4-----5
  //     |  2  |  3  |
  //     6-----7-----8

  BSHP<XmUGrid> ugrid = TEST_XmUGridSimpleQuad();
  if (!ugrid)
  {
    TS_FAIL("Unable to create UGrid.");
    return;
  }

  VecInt expectedFail;
  VecInt2d expectedCells = {{}, {2}, {1}, {}};
  VecInt expected2dCells = {-1, 2, 1, -1};

  int adjacentCell;
  VecInt adjacentCells = ugrid->GetAdjacentCells(0, -1);
  TS_ASSERT_EQUALS(expectedFail, adjacentCells);
  adjacentCell = ugrid->Get2dAdjacentCell(0, -1);
  TS_ASSERT_EQUALS(-1, adjacentCell);

  for (int i(0); i < ugrid->GetNumberOfCellEdges(0); i++)
  {
    adjacentCells = ugrid->GetAdjacentCells(0, i);
    TS_ASSERT_EQUALS(expectedCells[i], adjacentCells);

    adjacentCell = ugrid->Get2dAdjacentCell(0, i);
    TS_ASSERT_EQUALS(expected2dCells[i], adjacentCell);
  }
  adjacentCells = ugrid->GetAdjacentCells(0, ugrid->GetNumberOfCellEdges(0));
  TS_ASSERT_EQUALS(expectedFail, adjacentCells);
  adjacentCell = ugrid->Get2dAdjacentCell(0, ugrid->GetNumberOfCellEdges(0));
  TS_ASSERT_EQUALS(-1, adjacentCell);

  // Test a cell in the middle of an hexahedron grid
  BSHP<XmUGrid> hexUgrid = TEST_XmUBuildHexahedronUgrid(5, 5, 5);
  if (!hexUgrid)
  {
    TS_FAIL("Unable to create UGrid.");
    return;
  }
  expectedCells = {{5, 6, 21},   {6, 10, 26},  {6, 7, 23},   {2, 6, 18},
                   {21, 37, 38}, {26, 38, 42}, {23, 38, 39}, {18, 34, 38},
                   {17, 18, 21}, {21, 25, 26}, {18, 23, 19}, {26, 23, 27}};

  for (int i(0); i < hexUgrid->GetNumberOfCellEdges(22); i++)
  {
    adjacentCells = hexUgrid->GetAdjacentCells(22, i);
    TS_ASSERT_EQUALS(expectedCells[i], adjacentCells);
  }

} // XmUGridUnitTests::testGetAdjacentCell
//------------------------------------------------------------------------------
/// \brief Test retrieving Adjacent Cell
//------------------------------------------------------------------------------
void XmUGridUnitTests::testGetAdjacentCellsFromGivenEdge()
{
  //     0-----1-----2
  //     |  0  |  1  |
  //     3-----4-----5
  //     |  2  |  3  |
  //     6-----7-----8

  BSHP<XmUGrid> ugrid = TEST_XmUGridSimpleQuad();
  if (!ugrid)
  {
    TS_FAIL("Unable to create UGrid.");
    return;
  }

  VecInt expectedFail;
  VecInt2d expectedCells = {{0, 1}, {0, 2}, {0}};
  std::vector<std::pair<int, int>> edges = {{1, 4}, {3, 4}, {0, 3}};

  VecInt adjacentCells = ugrid->GetAdjacentCellsFromGivenEdge(-1, -1);
  TS_ASSERT_EQUALS(expectedFail, adjacentCells);
  for (int i(0); i < edges.size(); i++)
  {
    adjacentCells = ugrid->GetAdjacentCellsFromGivenEdge(edges[i]);
    TS_ASSERT_EQUALS(expectedCells[i], adjacentCells);
  }
  adjacentCells = ugrid->GetAdjacentCellsFromGivenEdge(edges[0].first, edges[1].second);
  TS_ASSERT_EQUALS(expectedCells[0], adjacentCells);

  adjacentCells = ugrid->GetAdjacentCellsFromGivenEdge(0, ugrid->GetNumberOfPoints());
  TS_ASSERT_EQUALS(expectedFail, adjacentCells);

} // XmUGridUnitTests::testGetAdjacentCellsFromGivenEdge

//------------------------------------------------------------------------------
/// \brief Test retrieving Cell Face
//------------------------------------------------------------------------------
void XmUGridUnitTests::testGetCellFace()
{
  // 2D Tests, include the bounds check
  VecInt emptyCellFaces = {};
  VecInt2d expectedCellFaces = {// XMU_QUAD
                                {},
                                // XMU_PIXEL
                                {},
                                // XMU_TRIANGLE
                                {},
                                // XMU_POLYGON
                                {},
                                // XMU_POLY_LINE
                                {},
                                // XMU_LINE
                                {}};
  VecInt cellFaces;

  // 2D Shapes
  BSHP<XmUGrid> ugrid2d = TEST_XmUGrid2dLinear();
  if (!ugrid2d)
  {
    TS_FAIL("Unable to create UGrid.");
    return;
  }

  cellFaces = ugrid2d->GetCellFace(-1, 0);
  TS_ASSERT_EQUALS(emptyCellFaces, cellFaces);
  cellFaces = ugrid2d->GetCellFace(0, -1);
  TS_ASSERT_EQUALS(emptyCellFaces, cellFaces);

  for (int i(0); i < ugrid2d->GetNumberOfCells(); i++)
  {
    cellFaces = ugrid2d->GetCellFace(i, 0);
    TS_ASSERT_EQUALS(expectedCellFaces[i], cellFaces);
  }

  cellFaces = ugrid2d->GetCellFace(ugrid2d->GetNumberOfCells(), 0);
  TS_ASSERT_EQUALS(emptyCellFaces, cellFaces);
  cellFaces = ugrid2d->GetCellFace(0, 1);
  TS_ASSERT_EQUALS(emptyCellFaces, cellFaces);

  // 3D Shapes
  BSHP<XmUGrid> ugrid3d = TEST_XmUGrid3dLinear();
  if (!ugrid3d)
  {
    TS_FAIL("Unable to create UGrid.");
    return;
  }

  expectedCellFaces = {// Tetra
                       {0, 1, 15},
                       {1, 5, 15},
                       {5, 0, 15},
                       {0, 5, 1},
                       // Voxel
                       {1, 16, 21, 6},
                       {2, 7, 22, 17},
                       {1, 2, 17, 16},
                       {6, 21, 22, 7},
                       {1, 6, 7, 2},
                       {16, 17, 22, 21},
                       // Hexahedron
                       {2, 17, 22, 7},
                       {3, 8, 23, 18},
                       {2, 3, 18, 17},
                       {7, 22, 23, 8},
                       {2, 7, 8, 3},
                       {17, 18, 23, 22},
                       // Polyhedron
                       {8, 9, 14, 13},
                       {8, 9, 24, 23},
                       {9, 14, 29, 24},
                       {13, 14, 29, 28},
                       {8, 13, 28, 23},
                       {23, 24, 29, 28},
                       // Wedge
                       {3, 4, 18},
                       {8, 23, 9},
                       {3, 8, 9, 4},
                       {4, 9, 23, 18},
                       {18, 23, 8, 3},
                       // Pyramid
                       {5, 10, 11, 6},
                       {5, 6, 20},
                       {6, 11, 20},
                       {11, 10, 20},
                       {10, 5, 20}};
  int currId(0);
  for (int i(0); i < ugrid3d->GetNumberOfCells(); i++)
  {
    for (int j(0); j < ugrid3d->GetNumberOfCellFaces(i); j++, currId++)
    {
      cellFaces = ugrid3d->GetCellFace(i, j);
      TS_ASSERT_EQUALS(expectedCellFaces[currId], cellFaces);
    }
  }
} // XmUGridUnitTests::testGetCellFace
//! [snip_test_GetCellFaceNeighbor]
//------------------------------------------------------------------------------
/// \brief Test retrieving Cell Face Neighbor
//------------------------------------------------------------------------------
void XmUGridUnitTests::testGetCellFaceNeighbor()
{
  // 2 hexahedrons
  int rows = 3;
  int cols = 2;
  int lays = 2;

  BSHP<xms::XmUGrid> grid = TEST_XmUBuildHexahedronUgrid(rows, cols, lays);
  if (!grid)
  {
    TS_FAIL("Unable to create UGrid.");
    return;
  }

  // clang-format off
  VecInt expectedNeighbor = {-1, 1, -1, -1, -1, -1, 0, -1, -1, -1, -1, -1};
  VecInt expectedFace =     {-1, 0, -1, -1, -1, -1, 1, -1, -1, -1, -1, -1};
  // clang-format on

  int expectedIdx = 0;
  int neighborCellIdx;

  neighborCellIdx = grid->GetCellFaceNeighbor(-1, 0);
  TS_ASSERT_EQUALS(-1, neighborCellIdx);
  neighborCellIdx = grid->GetCellFaceNeighbor(0, -1);
  TS_ASSERT_EQUALS(-1, neighborCellIdx);

  for (int cellIdx = 0; cellIdx < grid->GetNumberOfCells(); cellIdx++)
  {
    for (int faceIdx = 0; faceIdx < grid->GetNumberOfCellFaces(cellIdx); faceIdx++, expectedIdx++)
    {
      // Check first function
      neighborCellIdx = grid->GetCellFaceNeighbor(cellIdx, faceIdx);
      TS_ASSERT_EQUALS(expectedNeighbor[expectedIdx], neighborCellIdx);

      // Check overload function
      int neighborFaceIdx = -1;
      grid->GetCellFaceNeighbor(cellIdx, faceIdx, neighborCellIdx, neighborFaceIdx);
      TS_ASSERT_EQUALS(expectedNeighbor[expectedIdx], neighborCellIdx);
      TS_ASSERT_EQUALS(expectedFace[expectedIdx], neighborFaceIdx);

      // Check that faces are the same
      VecInt expectedFacePt = grid->GetCellFace(cellIdx, faceIdx);
      std::sort(expectedFacePt.begin(), expectedFacePt.end());
      VecInt neighborFacePt = grid->GetCellFace(neighborCellIdx, neighborFaceIdx);
      std::sort(neighborFacePt.begin(), neighborFacePt.end());
      if (!expectedFacePt.empty() && !neighborFacePt.empty())
      {
        TS_ASSERT_EQUALS(expectedFacePt, neighborFacePt);
      }
    }
  }
  neighborCellIdx = grid->GetCellFaceNeighbor(grid->GetNumberOfCells(), 0);
  TS_ASSERT_EQUALS(-1, neighborCellIdx);
  neighborCellIdx = grid->GetCellFaceNeighbor(0, grid->GetNumberOfCells());
  TS_ASSERT_EQUALS(-1, neighborCellIdx);

  rows = 3;
  cols = 3;
  lays = 3;
  grid = TEST_XmUBuildHexahedronUgrid(rows, cols, lays);
  if (!grid)
  {
    TS_FAIL("Unable to create UGrid.");
    return;
  }

  expectedNeighbor.clear();
  // clang-format off
  expectedNeighbor = {-1, 2, -1, 1, -1, 4, -1, 3, 0, -1, -1, 5, 0, -1, -1, 3, -1, 6, 1, -1, 2, -1,
                      -1, 7, -1, 6, -1, 5, 0, -1, -1, 7, 4, -1, 1, -1, 4, -1, -1, 7, 2, -1, 5, -1,
                      6, -1, 3, -1};
  expectedFace =     {-1, 0, -1, 2, -1, 4, -1, 0, 3, -1, -1, 4, 1, -1, -1, 2, -1, 4, 1, -1, 3, -1,
                      -1, 4, -1, 0, -1, 2, 5, -1, -1, 0, 3, -1, 5, -1, 1, -1, -1, 2, 5, -1, 1, -1,
                      3, -1, 5, -1};
  // clang-format on

  expectedIdx = 0;
  for (int cellIdx = 0; cellIdx < grid->GetNumberOfCells(); ++cellIdx)
  {
    for (int faceIdx = 0; faceIdx < grid->GetNumberOfCellFaces(cellIdx); faceIdx++, expectedIdx++)
    {
      // Check first function
      neighborCellIdx = grid->GetCellFaceNeighbor(cellIdx, faceIdx);
      TS_ASSERT_EQUALS(expectedNeighbor[expectedIdx], neighborCellIdx);

      // Check overload function
      int neighborFaceIdx = -1;
      grid->GetCellFaceNeighbor(cellIdx, faceIdx, neighborCellIdx, neighborFaceIdx);
      TS_ASSERT_EQUALS(expectedNeighbor[expectedIdx], neighborCellIdx);
      TS_ASSERT_EQUALS(expectedFace[expectedIdx], neighborFaceIdx);

      expectedNeighbor.push_back(neighborCellIdx);
      expectedFace.push_back(neighborFaceIdx);

      // Check that faces are the same
      VecInt expectedFacePt = grid->GetCellFace(cellIdx, faceIdx);
      std::sort(expectedFacePt.begin(), expectedFacePt.end());
      VecInt neighborFacePt = grid->GetCellFace(neighborCellIdx, neighborFaceIdx);
      std::sort(neighborFacePt.begin(), neighborFacePt.end());
      if (!expectedFacePt.empty() && !neighborFacePt.empty())
      {
        TS_ASSERT_EQUALS(expectedFacePt, neighborFacePt);
      }
    }
  }
} // XmUGridUnitTests::testGetCellFaceNeighbor
//! [snip_test_GetCellFaceNeighbor]
//! [snip_test_GetEdgesFromPoint]
//------------------------------------------------------------------------------
/// \brief Test retrieving Cell Face Neighbor
//------------------------------------------------------------------------------
void XmUGridUnitTests::testGetEdgesFromPoint()
{
  //     0-----1-----2
  //     |  0  |  1  |
  //     3-----4-----5
  //     |  2  |  3  |
  //     6-----7-----8

  BSHP<xms::XmUGrid> grid = TEST_XmUGridSimpleQuad();
  if (!grid)
  {
    TS_FAIL("Unable to create UGrid.");
    return;
  }
  VecInt2d expectedCells{
    {0, 0},       {0, 0, 1, 1}, {1, 1},       {0, 0, 2, 2}, {0, 0, 1, 1, 2, 2, 3, 3},
    {1, 1, 3, 3}, {2, 2},       {2, 2, 3, 3}, {3, 3}};
  VecInt2d expectedEdgeIdxs{
    {0, 3},       {2, 3, 0, 3}, {2, 3},       {0, 1, 0, 3}, {1, 2, 0, 1, 2, 3, 0, 3},
    {1, 2, 2, 3}, {0, 1},       {1, 2, 0, 1}, {1, 2}};
  std::vector<std::vector<std::pair<int, int>>> expectedEdges{
    {{0, 3}, {1, 0}},
    {{4, 1}, {1, 0}, {1, 4}, {2, 1}},
    {{5, 2}, {2, 1}},
    {{0, 3}, {3, 4}, {3, 6}, {4, 3}},
    {{3, 4}, {4, 1}, {1, 4}, {4, 5}, {7, 4}, {4, 3}, {4, 7}, {5, 4}},
    {{4, 5}, {5, 2}, {8, 5}, {5, 4}},
    {{3, 6}, {6, 7}},
    {{6, 7}, {7, 4}, {4, 7}, {7, 8}},
    {{7, 8}, {8, 5}}};
  VecInt2d expectedEdgePoints1{
    {0, 1},       {4, 1, 1, 2}, {5, 2},       {0, 3, 3, 4}, {3, 4, 1, 4, 7, 4, 4, 5},
    {4, 5, 8, 5}, {3, 6},       {6, 7, 4, 7}, {7, 8}};
  VecInt2d expectedEdgePoints2{
    {3, 0},       {1, 0, 4, 1}, {2, 1},       {3, 4, 6, 3}, {4, 1, 4, 5, 4, 3, 7, 4},
    {5, 2, 5, 4}, {6, 7},       {7, 4, 7, 8}, {8, 5}};

  std::vector<std::pair<int, int>> edges;
  VecInt cells;
  VecInt edgeIdx;
  VecInt edgePoints1;
  VecInt edgePoints2;
  VecInt empty;

  TS_ASSERT(!grid->GetEdgesFromPoint(-1, cells, edgeIdx));
  TS_ASSERT_EQUALS(empty, cells);
  TS_ASSERT_EQUALS(empty, edgeIdx);

  for (int i = 0; i < grid->GetNumberOfPoints(); ++i)
  {
    // Function 1
    grid->GetEdgesFromPoint(i, cells, edgeIdx);
    TS_ASSERT_EQUALS(expectedCells[i], cells);
    TS_ASSERT_EQUALS(expectedEdgeIdxs[i], edgeIdx);
    // Overload
    grid->GetEdgesFromPoint(i, cells, edges);
    TS_ASSERT_EQUALS(expectedCells[i], cells);
    TS_ASSERT_EQUALS(expectedEdges[i], edges);
    // 2nd Overload
    grid->GetEdgesFromPoint(i, cells, edgePoints1, edgePoints2);
    TS_ASSERT_EQUALS(expectedCells[i], cells);
    TS_ASSERT_EQUALS(expectedEdgePoints1[i], edgePoints1);
    TS_ASSERT_EQUALS(expectedEdgePoints2[i], edgePoints2);
  }

  TS_ASSERT(!grid->GetEdgesFromPoint(grid->GetNumberOfPoints(), cells, edgeIdx));
  TS_ASSERT_EQUALS(empty, cells);
  TS_ASSERT_EQUALS(empty, edgeIdx);
} // XmUGridUnitTests::testGetEdgesFromPoint
//! [snip_test_GetEdgesFromPoint]
//------------------------------------------------------------------------------
/// \brief Test GetPointIdxsAttachedByEdge and GetPointsAttachedByEdge.
//------------------------------------------------------------------------------
void XmUGridUnitTests::testGetPointsAttachedByEdge()
{
  //     0-----1-----2
  //     |  0  |  1  |
  //     3-----4-----5
  //     |  2  |  3  |
  //     6-----7-----8

  BSHP<xms::XmUGrid> grid = TEST_XmUGridSimpleQuad();
  if (!grid)
  {
    TS_FAIL("Unable to create UGrid.");
    return;
  }
  VecInt attachedIdxs;
  grid->GetPointIdxsAttachedByEdge(0, attachedIdxs);
  VecInt expectedIdxs = {1, 3};
  TS_ASSERT_EQUALS(expectedIdxs, attachedIdxs);
  grid->GetPointIdxsAttachedByEdge(3, attachedIdxs);
  expectedIdxs = {0, 4, 6};
  TS_ASSERT_EQUALS(expectedIdxs, attachedIdxs);
  grid->GetPointIdxsAttachedByEdge(4, attachedIdxs);
  expectedIdxs = {1, 3, 5, 7};
  TS_ASSERT_EQUALS(expectedIdxs, attachedIdxs);
  VecPt3d attachedPts;
  grid->GetPointsAttachedByEdge(0, attachedPts);
  VecPt3d expectedPts = {{10, 10, 0}, {0, 0, 0}};
  TS_ASSERT_EQUALS(expectedPts, attachedPts);
  grid->GetPointsAttachedByEdge(3, attachedPts);
  expectedPts = {{0, 10, 0}, {10, 0, 0}, {0, -10, 0}};
  TS_ASSERT_EQUALS(expectedPts, attachedPts);
  grid->GetPointsAttachedByEdge(4, attachedPts);
  expectedPts = {{10, 10, 0}, {0, 0, 0}, {20, 0, 0}, {10, -10, 0}};
  TS_ASSERT_EQUALS(expectedPts, attachedPts);
} // XmUGridUnitTests::testGetPointsAttachedByEdge
//! [snip_test_GetFacesFromPoint]
//------------------------------------------------------------------------------
/// \brief Test retrieving Cell Faces From Point
//------------------------------------------------------------------------------
void XmUGridUnitTests::testGetFacesFromPoint()
{
  // 2 hexahedrons
  int rows = 3;
  int cols = 2;
  int lays = 2;

  BSHP<xms::XmUGrid> grid = TEST_XmUBuildHexahedronUgrid(rows, cols, lays);
  if (!grid)
  {
    TS_FAIL("Unable to create UGrid.");
    return;
  }
  VecInt empty;
  VecInt2d expectedCell = {
    {0, 0, 0}, {0, 0, 0}, {0, 0, 0, 1, 1, 1}, {0, 0, 0, 1, 1, 1}, {1, 1, 1}, {1, 1, 1},
    {0, 0, 0}, {0, 0, 0}, {0, 0, 0, 1, 1, 1}, {0, 0, 0, 1, 1, 1}, {1, 1, 1}, {1, 1, 1}};
  VecInt2d expectedFaces = {
    {0, 2, 4}, {0, 3, 4}, {1, 2, 4, 0, 2, 4}, {1, 3, 4, 0, 3, 4}, {1, 2, 4}, {1, 3, 4},
    {0, 2, 5}, {0, 3, 5}, {1, 2, 5, 0, 2, 5}, {1, 3, 5, 0, 3, 5}, {1, 2, 5}, {1, 3, 5}};
  VecInt cells, faces;
  int expectedIdx = 0;
  TS_ASSERT(!grid->GetFacesFromPoint(-1, cells, faces));
  TS_ASSERT_EQUALS(empty, cells);
  TS_ASSERT_EQUALS(empty, faces);
  for (int pointIdx = 0; pointIdx < grid->GetNumberOfPoints(); pointIdx++, expectedIdx++)
  {
    // Check first function
    grid->GetFacesFromPoint(pointIdx, cells, faces);
    TS_ASSERT_EQUALS(expectedCell[expectedIdx], cells);
    TS_ASSERT_EQUALS(expectedFaces[expectedIdx], faces);
    expectedCell.push_back(cells);
    expectedFaces.push_back(faces);
  }
  TS_ASSERT(!grid->GetFacesFromPoint(grid->GetNumberOfPoints(), cells, faces));
  TS_ASSERT_EQUALS(empty, cells);
  TS_ASSERT_EQUALS(empty, faces);
} // XmUGridUnitTests::testGetFacesFromPoint
//! [snip_test_GetFacesFromPoint]
//! [snip_test_GetPlanViewPolygon]
//------------------------------------------------------------------------------
/// \brief Test getting the plan view polygon of a cell.
//------------------------------------------------------------------------------
void XmUGridUnitTests::testGetPlanViewPolygon()
{
  // 2d
  BSHP<xms::XmUGrid> grid2d = TEST_XmUGrid2dLinear();
  if (!grid2d)
  {
    TS_FAIL("Unable to create UGrid.");
    return;
  }
  VecPt3d2d expectedPolygons{
    {{0, 0, 0}, {10, 0, 0}, {10, 10, 0}, {0, 10, 0}},
    {{10, 0, 0}, {20, 0, 0}, {20, 10, 0}, {10, 10, 0}},
    {{20, 0, 0}, {30, 0, 0}, {20, 10, 0}},
    {{30, 0, 0}, {40, 0, 0}, {40, 10, 0}, {40, 20, 0}, {30, 20, 0}, {20, 10, 0}},
    {},
    {}};
  VecPt3d viewPolygon;
  VecPt3d empty;
  // Bounds testing
  TS_ASSERT(!grid2d->GetPlanViewPolygon(-1, viewPolygon));
  TS_ASSERT_EQUALS(empty, viewPolygon);
  TS_ASSERT(!grid2d->GetPlanViewPolygon(grid2d->GetNumberOfCells(), viewPolygon));
  TS_ASSERT_EQUALS(empty, viewPolygon);
  // Regular testing
  for (int i = 0; i < grid2d->GetNumberOfCells(); ++i)
  {
    // Should return true for the first 4 cells, and false for the last 2
    TS_ASSERT(grid2d->GetPlanViewPolygon(i, viewPolygon) != i >= 4);
    TS_ASSERT_EQUALS(expectedPolygons[i], viewPolygon);
  }

  // 3d
  BSHP<XmUGrid> ugrid3d = TEST_XmUGrid3dLinear();
  if (!ugrid3d)
  {
    TS_FAIL("Unable to create UGrid.");
    return;
  }
  expectedPolygons = {{{0, 0, 0}, {10, 0, 0}, {0, 10, 0}},
                      {{20, 0, 0}, {20, 10, 0}, {10, 10, 0}, {10, 0, 0}},
                      {{30, 0, 0}, {30, 10, 0}, {20, 10, 0}, {20, 0, 0}},
                      {{40, 10, 0}, {40, 20, 0}, {30, 20, 0}, {30, 10, 0}},
                      {{30, 0, 0}, {40, 0, 0}, {40, 10, 0}, {30, 10, 0}},
                      {{0, 10, 0}, {10, 10, 0}, {10, 20, 0}, {0, 20, 0}}};

  for (int i = 0; i < ugrid3d->GetNumberOfCells(); ++i)
  {
    TS_ASSERT(ugrid3d->GetPlanViewPolygon(i, viewPolygon));
    TS_ASSERT_EQUALS(expectedPolygons[i], viewPolygon);
  }

  BSHP<xms::XmUGrid> chevronUgrid = TEST_XmUBuild3DChevronUgrid();
  if (!chevronUgrid)
  {
    TS_FAIL("Unable to create UGrid.");
    return;
  }

  expectedPolygons = {{{0.0, 0.0, 0.0}, {20.0, 10.0, 0.0}, {40.0, 0.0, 0.0}, {20.0, 50.0, 0.0}}};
  TS_ASSERT(chevronUgrid->GetPlanViewPolygon(0, viewPolygon));
  TS_ASSERT_EQUALS(expectedPolygons[0], viewPolygon);

} // XmUGridUnitTests::testGetPlanViewPolygon
//! [snip_test_GetPlanViewPolygon]
//------------------------------------------------------------------------------
/// \brief Test getting the plan view points of a cell.
//------------------------------------------------------------------------------
void XmUGridUnitTests::testGetPlanViewPolygonMultiSideFace()
{
  // 3d - For vertically prismatic cells returns the unique plan view points for side faces
  //      in sorted order. For cells that aren't vertically prismatic returns an empty vector.
  VecPt3d points = {
    {0, 0, 0}, {1, 0, 0}, {2, 0, 0}, {0, 0, 1}, {1, 0, 1}, {2, 0, 1}, {0, 0, 2}, {2, 0, 2}, // front face
    {0, 1, 2}, {1, 1, 2}, {2, 1, 2}, // points midway back
    {0, 2, 0}, {2, 2, 0}, {0, 2, 2}, {1, 2, 2}, {2, 2, 2}, // back points
    {4, 2, 0}, {3, 1, 2} // tetrahedron
  };
  VecInt cells = {
    XMU_POLYHEDRON, 10,     // hexahedron split into smaller faces
    4, 0, 1, 4, 3,          // hex front - lower left face
    4, 1, 2, 5, 4,          // hex front - lower right face
    5, 3, 4, 5, 7, 6,       // hex front - top face
    5, 6, 7, 10, 9, 8,      // hex top - front face
    4, 8, 9, 14, 13,        // hex top - left back face
    4, 9, 10, 15, 14,       // hex top - right back face
    6, 0, 3, 6, 8, 13, 11,  // hex left
    6, 2, 12, 15, 10, 7, 5, // hex right
    5, 0, 11, 12, 2, 1,     // hex bottom
    5, 11, 13, 14, 15, 12,  // hex back
    XMU_TETRA, 4, 2, 16, 12, 17 // tetrahedron with 
  };
  BSHP<XmUGrid> ugrid3d = XmUGrid::New(points, cells);
  if (!ugrid3d)
  {
    TS_FAIL("Unable to create UGrid.");
    return;
  }

  // vertically prismatic
  VecPt3d cellPoints;
  ugrid3d->GetPlanViewPolygon(0, cellPoints);
  VecPt3d expectedCellPoints = {
    {1, 0, 0},
    {2, 0, 0},
    {2, 1, 0},
    {2, 2, 0},
    {1, 2, 0},
    {0, 2, 0},
    {0, 1, 0},
    {0, 0, 0}
  };
  TS_ASSERT_EQUALS(expectedCellPoints, cellPoints);

  // not vertically prismatic
  ugrid3d->GetPlanViewPolygon(1, cellPoints);
  expectedCellPoints = {{2, 0, 0}, {4, 2, 0}, {2, 2, 0}};
  TS_ASSERT_EQUALS(expectedCellPoints, cellPoints);
} // XmUGridUnitTests::testGetPlanViewPoints
//------------------------------------------------------------------------------
/// \brief Test validating a cell for a changed point
//------------------------------------------------------------------------------
void XmUGridUnitTests::testIsCellValidWithPointChange()
{
  //     0-----1-----2
  //     |  0  |  1  |
  //     3-----4-----5
  //     |  2  |  3  |
  //     6-----7-----8

  // VecPt3d points = { { 0, 10, 0 }, { 10, 10, 0 }, { 20, 10, 0 }, { 0, 0, 0 }, { 10, 0, 0 },
  //{ 20, 0, 0 }, { 0, -10, 0 }, { 10, -10, 0 }, { 20, -10, 0 } };

  BSHP<XmUGrid> ugrid = TEST_XmUGridSimpleQuad();
  if (!ugrid)
  {
    TS_FAIL("Unable to create UGrid.");
    return;
  }

  Pt3d valid = {5.0, 5.0, 0.0};
  Pt3d invalid = {500.0, 500.0, 0.0};

  TS_ASSERT(ugrid->SetPoint(4, valid));
  TS_ASSERT(!ugrid->SetPoint(4, invalid));

  BSHP<XmUGrid> ugrid3d = TEST_XmUBuildHexahedronUgrid(4, 4, 4);

  valid = ugrid3d->GetPoint(21);
  valid.x += 0.5;
  valid.y += 0.5;
  valid.z += 0.5;
  TS_ASSERT(ugrid3d->SetPoint(21, valid));
  TS_ASSERT(!ugrid3d->SetPoint(21, invalid));

} // XmUGridUnitTests::testIsCellValidWithPointChange
//! [snip_test_PointFunctions]
//------------------------------------------------------------------------------
/// \brief Test various point functions
//------------------------------------------------------------------------------
void XmUGridUnitTests::testPointFunctions()
{
  BSHP<XmUGrid> ugrid = TEST_XmUGridSimpleQuad();
  if (!ugrid)
  {
    TS_FAIL("Unable to create UGrid.");
    return;
  }

  // Test GetNumberOfPoints
  TS_ASSERT_EQUALS(ugrid->GetNumberOfPoints(), 9);
  VecPt3d points = {{0, 10, 0}, {10, 10, 0}, {20, 10, 0},  {0, 0, 0},   {10, 0, 0},
                    {20, 0, 0}, {0, -10, 0}, {10, -10, 0}, {20, -10, 0}};

  // Test GetPoints
  TS_ASSERT_EQUALS(ugrid->GetPoints(), points);
  for (int i = 0; i < points.size(); ++i)
  {
    TS_ASSERT_EQUALS(points[i], ugrid->GetPoint(i));
  }

  // Test SetPoint & GetPoint
  Pt3d invalid = {100, 100, 100};
  Pt3d valid = {5, 5, 5};
  TS_ASSERT(!ugrid->SetPoint(4, invalid));
  TS_ASSERT_EQUALS(points[4], ugrid->GetPoint(4));
  TS_ASSERT(ugrid->SetPoint(4, valid));
  TS_ASSERT_EQUALS(valid, ugrid->GetPoint(4));

  VecInt pointIndices = {0, 3, 6};
  VecPt3d expectedPoints = {{0, 10, 0}, {0, 0, 0}, {0, -10, 0}};
  VecPt3d pointsPt3d;

  // Test GetPointsFromPointIdxs
  pointsPt3d = ugrid->GetPointsFromPointIdxs(pointIndices);
  TS_ASSERT_EQUALS(expectedPoints, pointsPt3d);

  // Test GetExtents
  Pt3d min, max, expectedMin = {0, -10, 0}, expectedMax = {20, 10, 5};
  ugrid->GetExtents(min, max);
  TS_ASSERT_EQUALS(expectedMin, min);
  TS_ASSERT_EQUALS(expectedMax, max);

  // Test GetPointCells
  VecInt expectedCells = {0, 2};
  VecInt cellsAssociated = ugrid->GetPointCells(3);
  TS_ASSERT_EQUALS(expectedCells, cellsAssociated);

  // Test GetCommonCells
  VecInt expectedCommonCells = {0, 1};
  VecInt pointIndex = {1};
  VecInt commonCells = ugrid->GetCommonCells(pointIndex);
  TS_ASSERT_EQUALS(expectedCells, cellsAssociated);

} // XmUGridUnitTests::testPointFunctions
//! [snip_test_PointFunctions]
//! [snip_test_CellFunctions]
//------------------------------------------------------------------------------
/// \brief Test various cell functions
//------------------------------------------------------------------------------
void XmUGridUnitTests::testCellFunctions()
{
  BSHP<XmUGrid> ugrid = TEST_XmUGridSimpleQuad();
  if (!ugrid)
  {
    TS_FAIL("Unable to create UGrid.");
    return;
  }

  // Test GetPointsOfCell
  VecInt pointsOfCell = ugrid->GetPointsOfCell(0);
  VecInt expectedPoints = {0, 3, 4, 1};
  TS_ASSERT_EQUALS(expectedPoints, pointsOfCell);
  // Test overload
  ugrid->GetPointsOfCell(0, pointsOfCell);
  TS_ASSERT_EQUALS(expectedPoints, pointsOfCell);
  VecPt3d locations;
  ugrid->GetPointsOfCell(0, locations);
  VecPt3d expectedLocations = {{0, 10, 0}, {0, 0, 0}, {10, 0, 0}, {10, 10, 0}};
  TS_ASSERT_EQUALS(expectedLocations, locations);

  // Test GetCellExtents
  Pt3d min, max;
  ugrid->GetCellExtents(0, min, max);
  TS_ASSERT_EQUALS(Pt3d(0, 0, 0), min);
  TS_ASSERT_EQUALS(Pt3d(10, 10, 0), max);

  // Test GetCellType
  TS_ASSERT_EQUALS(XMU_QUAD, ugrid->GetCellType(0));

  // Test GetDimensionCount
  VecInt expectedDimensions = {0, 0, 4, 0};
  TS_ASSERT_EQUALS(expectedDimensions, ugrid->GetDimensionCount());

  // Test GetCellDimension
  TS_ASSERT_EQUALS(2, ugrid->GetCellDimension(0));
  
  // Test GetCentroid
  Pt3d centroid;
  TS_ASSERT(ugrid->GetCentroid(0, centroid));
  TS_ASSERT_EQUALS(Pt3d(5, 5, 0), centroid);

} // XmUGridUnitTests::testCellFunctions
//! [snip_test_CellFunctions]
//! [snip_test_GetCellStreamFunctions]
//------------------------------------------------------------------------------
/// \brief Test various cell functions
//------------------------------------------------------------------------------
void XmUGridUnitTests::testGetCellStreamFunctions()
{
  BSHP<XmUGrid> ugrid = TEST_XmUGridSimpleQuad();
  if (!ugrid)
  {
    TS_FAIL("Unable to create UGrid.");
    return;
  }

  // Test GetCellStream
  VecInt cellStream = ugrid->GetCellStream();
  VecInt expectedCellStream = {XMU_QUAD, 4, 0, 3, 4, 1, XMU_QUAD, 4, 1, 4, 5, 2,
                               XMU_QUAD, 4, 3, 6, 7, 4, XMU_QUAD, 4, 4, 7, 8, 5};
  TS_ASSERT_EQUALS(expectedCellStream, cellStream);

  // Test GetSingleCellStream
  ugrid->GetSingleCellStream(0, cellStream);
  expectedCellStream = {XMU_QUAD, 4, 0, 3, 4, 1};
  TS_ASSERT_EQUALS(expectedCellStream, cellStream);

} // XmUGridUnitTests::testGetCellStreamFunctions
//! [snip_test_GetCellStreamFunctions]
//! [snip_test_GetAdjacentCellFunctions]
//------------------------------------------------------------------------------
/// \brief Test all get adjacent cell functions
//------------------------------------------------------------------------------
void XmUGridUnitTests::testGetAdjacentCellFunctions()
{
  //     0-----1-----2
  //     |  0  |  1  |
  //     3-----4-----5
  //     |  2  |  3  |
  //     6-----7-----8
  BSHP<XmUGrid> ugrid = TEST_XmUGridSimpleQuad();
  if (!ugrid)
  {
    TS_FAIL("Unable to create UGrid.");
    return;
  }

  // Get Adjacent Cells from cell and edge
  VecInt2d expectedCells = {{}, {2}, {1}, {}};
  VecInt expected2dCells = {-1, 2, 1, -1};
  int adjacentCell;
  VecInt adjacentCells;
  for (int i(0); i < ugrid->GetNumberOfCellEdges(0); i++)
  {
    adjacentCells = ugrid->GetAdjacentCells(0, i);
    TS_ASSERT_EQUALS(expectedCells[i], adjacentCells);
    // For 2D cells only
    adjacentCell = ugrid->Get2dAdjacentCell(0, i);
    TS_ASSERT_EQUALS(expected2dCells[i], adjacentCell);
  }

  // Get Adjacent cells from given Edge
  VecInt2d expectedCellsFromEdge = {{0, 1}, {0, 2}, {0}};
  std::vector<std::pair<int, int>> edges = {{1, 4}, {3, 4}, {0, 3}};
  adjacentCells = ugrid->GetAdjacentCellsFromGivenEdge(-1, -1);
  for (int i(0); i < edges.size(); i++)
  {
    adjacentCells = ugrid->GetAdjacentCellsFromGivenEdge(edges[i]);
    TS_ASSERT_EQUALS(expectedCellsFromEdge[i], adjacentCells);
  }
  adjacentCells = ugrid->GetAdjacentCellsFromGivenEdge(edges[0].first, edges[1].second);
  TS_ASSERT_EQUALS(expectedCellsFromEdge[0], adjacentCells);
} // XmUGridUnitTests::testGetAdjacentCellFunctions
//! [snip_test_GetAdjacentCellFunctions]
//! [snip_test_GetEdgesOfCell]
//------------------------------------------------------------------------------
/// \brief Test various cell functions
//------------------------------------------------------------------------------
void XmUGridUnitTests::testGetEdgesOfCell()
{
  BSHP<XmUGrid> ugrid = TEST_XmUGridSimpleQuad();
  if (!ugrid)
  {
    TS_FAIL("Unable to create UGrid.");
    return;
  }

  // Test GetEdgesOfCell
  std::vector<std::pair<int, int>> edges = ugrid->GetEdgesOfCell(0);
  std::vector<std::pair<int, int>> expectededges = {{0, 3}, {3, 4}, {4, 1}, {1, 0}};
  TS_ASSERT_EQUALS(expectededges, edges);

} // XmUGridUnitTests::testGetEdgesOfCell
//! [snip_test_GetEdgesOfCell]
//! [snip_test_GetFaces]
//------------------------------------------------------------------------------
/// \brief Test various get face functions
//------------------------------------------------------------------------------
void XmUGridUnitTests::testGetFaces()
{
  // 3D Shapes
  BSHP<XmUGrid> ugrid3d = TEST_XmUGrid3dLinear();
  if (!ugrid3d)
  {
    TS_FAIL("Unable to create UGrid.");
    return;
  }

  VecInt cellFace;
  VecInt2d expectedCellFaces = {// Tetra
                                {0, 1, 15},
                                {1, 5, 15},
                                {5, 0, 15},
                                {0, 5, 1},
                                // Voxel
                                {1, 16, 21, 6},
                                {2, 7, 22, 17},
                                {1, 2, 17, 16},
                                {6, 21, 22, 7},
                                {1, 6, 7, 2},
                                {16, 17, 22, 21},
                                // Hexahedron
                                {2, 17, 22, 7},
                                {3, 8, 23, 18},
                                {2, 3, 18, 17},
                                {7, 22, 23, 8},
                                {2, 7, 8, 3},
                                {17, 18, 23, 22},
                                // Polyhedron
                                {8, 9, 14, 13},
                                {8, 9, 24, 23},
                                {9, 14, 29, 24},
                                {13, 14, 29, 28},
                                {8, 13, 28, 23},
                                {23, 24, 29, 28},
                                // Wedge
                                {3, 4, 18},
                                {8, 23, 9},
                                {3, 8, 9, 4},
                                {4, 9, 23, 18},
                                {18, 23, 8, 3},
                                // Pyramid
                                {5, 10, 11, 6},
                                {5, 6, 20},
                                {6, 11, 20},
                                {11, 10, 20},
                                {10, 5, 20}};
  int expectedIdx = 0;
  for (int i(0); i < ugrid3d->GetNumberOfCells(); i++)
  {
    for (int j(0); j < ugrid3d->GetNumberOfCellFaces(i); j++, expectedIdx++)
    {
      cellFace = ugrid3d->GetCellFace(i, j);
      TS_ASSERT_EQUALS(expectedCellFaces[expectedIdx], cellFace);
    }
  }
  // Tetra
  VecInt2d cellFaces;
  expectedIdx = 0;
  for (int i(0); i < ugrid3d->GetNumberOfCells(); i++)
  {
    cellFaces = ugrid3d->GetFacesOfCell(i);
    TS_ASSERT_EQUALS(cellFaces.size(), ugrid3d->GetNumberOfCellFaces(i));
    for (int j(0); j < ugrid3d->GetNumberOfCellFaces(i); j++, expectedIdx++)
    {
      TS_ASSERT_EQUALS(expectedCellFaces[expectedIdx], cellFaces[j]);
    }
  }
} // XmUGridUnitTests::testGetFaces
//! [snip_test_GetFaces]
//------------------------------------------------------------------------------
/// \brief Tests creating a large UGrid and checks the time spent.
//------------------------------------------------------------------------------
//#define SPEEDTEST
#ifdef SPEEDTEST
#include <boost/timer/timer.hpp>
#endif
void XmUGridUnitTests::testLargeUGridLinkSpeed()
{
#ifdef SPEEDTEST
  int rows = 1000;
  int cols = 500;
  int lays = 4;

  // BSHP<xms::XmUGrid> grid = TEST_XmUBuildQuadUGrid(rows, cols);
  // BSHP<xms::XmUGrid> grid = TEST_XmUBuildHexahedronUgrid(rows, cols, lays);
  BSHP<xms::XmUGrid> grid = TEST_XmUBuildPolyhedronUgrid(rows, cols, lays);

  {
    boost::timer::cpu_timer timer;
    BSHP<XmUGrid> ugrid = XmUGrid::New(grid->GetPoints(), grid->GetCellStream());
    TS_FAIL(timer.format());
  }

#endif
} // XmUGridUnitTests::testLargeUGridLinkSpeed

#endif
