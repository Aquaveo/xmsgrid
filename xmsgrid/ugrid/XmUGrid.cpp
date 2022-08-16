//------------------------------------------------------------------------------
/// \file
/// \ingroup ugrid
/// \copyright (C) Copyright Aquaveo 2018. Distributed under FreeBSD License
/// (See accompanying file LICENSE or https://aqaveo.com/bsd/license.txt)
//------------------------------------------------------------------------------

//----- Included files ---------------------------------------------------------

// 1. Precompiled header

// 2. My own header
#include <xmsgrid/ugrid/XmUGrid.h>

// 3. Standard library headers
#include <cmath>

// 4. External library headers
#include <boost/container/flat_set.hpp>

// 5. Shared code headers
#include <xmscore/misc/XmConst.h>
#include <xmscore/misc/XmError.h>
#include <xmscore/misc/XmLog.h>
#include <xmscore/misc/xmstype.h>
#include <xmscore/stl/set.h>

// 6. Non-shared code headers
#include <xmsgrid/geometry/geoms.h>
#include <xmsgrid/ugrid/XmEdge.h>

//----- Forward declarations ---------------------------------------------------

//----- External globals -------------------------------------------------------

//----- Namespace declaration --------------------------------------------------

//----- Constants / Enumerations -----------------------------------------------

//----- Classes / Structs ------------------------------------------------------

//----- Class / Function definitions -------------------------------------------

/// XMS Namespace
namespace xms
{
////////////////////////////////////////////////////////////////////////////////
/// Implementation for XmUGrid
class XmUGrid::Impl
{
public:
  /// Default constructor.
  Impl() = default;
  /// Default copy constructor.
  Impl(const Impl&) = default;
  /// \brief Default ssignment operator.
  /// \param a_xmUGrid The XmUGrid to copy from.
  /// \return The reference to this.
  Impl& operator=(const Impl& a_xmUGrid) = default;

  // Misc
  bool GetModified() const;
  void SetUnmodified();
  void SetUseCache(bool a_useCache);

  // Points

  int GetPointCount() const;

  const VecPt3d& GetLocations() const;
  void SetLocations(const VecPt3d& a_locations);

  Pt3d GetPointLocation(int a_pointIdx) const;
  bool SetPointLocation(int a_pointIdx, const Pt3d& a_location);

  Pt3d GetPointXy0(int a_pointIdx) const;
  VecPt3d GetPointsLocations(const VecInt& a_points) const;

  void GetExtents(Pt3d& a_min, Pt3d& a_max) const;

  int GetPointAdjacentCellCount(int a_pointIdx) const;
  VecInt GetPointAdjacentCells(int a_pointIdx) const; // cells associated with point
  void GetPointAdjacentCells(int a_pointIdx, VecInt& a_adjacentCells) const;

  VecInt GetPointsAdjacentCells(const VecInt& a_points) const;
  void GetPointsAdjacentCells(const int* a_pointIdxs,
                              int a_numpointIdxs,
                              VecInt& a_commonCellIdxs) const;
  void GetPointsAdjacentCells(const VecInt& a_pointIdxs, VecInt& a_adjacentCellIdxs) const;
  void GetPointsAdjacentCells(int a_pointIdx1, int a_pointIdx2, VecInt& a_adjacentCellIdxs) const;
  bool IsValidPointChange(int a_changedPtIdx, const Pt3d& a_newPosition) const;
  void GetPointAdjacentPoints(int a_pointIdx, VecInt& a_edgePoints) const;
  void GetPointAdjacentLocations(int a_pointIdx, VecPt3d& a_edgePoints) const;

  // Cells
  int GetCellCount() const;

  int GetCellPointCount(int a_cellIdx) const;
  VecInt GetCellPoints(int a_cellIdx) const;
  bool GetCellPoints(int a_cellIdx, VecInt& a_cellPoints) const;
  void GetCellLocations(int a_cellIdx, VecPt3d& a_cellLocations) const;

  XmUGridCellType GetCellType(int a_cellIdx) const;
  std::vector<int> GetDimensionCounts() const;
  int GetCellDimension(int a_cellIdx) const;
  void GetCellExtents(int a_cellIdx, Pt3d& a_min, Pt3d& a_max) const;

  const VecInt& GetCellstream() const;
  bool SetCellstream(const VecInt& a_cellstream);
  bool GetCellCellstream(int a_cellIdx, VecInt& a_cellstream) const;
  int GetCellCellstreamIndex(int a_cellIdx) const;

  XmUGridCellOrder GetCellOrder() const;
  void SetCellOrder(XmUGridCellOrder a_cellOrder);
  XmUGridCellOrder CalculateCellOrder() const;

  VecInt GetCellAdjacentCells(int a_cellIdx) const;
  void GetCellAdjacentCells(int a_cellIdx, VecInt& a_cellNeighbors) const;
  bool GetCellPlanViewPolygon(int a_cellIdx, VecPt3d& a_polygon) const;
  bool GetCellCentroid(int a_cellIdx, Pt3d& a_centroid) const;

  // Edges
  int GetCellEdgeCount(int a_cellIdx) const;
  XmEdge GetCellEdge(int a_cellIdx, int a_edgeIdx) const;
  VecInt GetCellEdgeAdjacentCells(int a_cellIdx, int a_edgeIdx) const;
  void GetCellEdgeAdjacentCells(int a_cellIdx, int a_edgeIdx, VecInt& a_adjacentCellIdxs) const;
  int GetCell2dEdgeAdjacentCell(int a_cellIdx, int a_edgeIdx) const;
  void GetEdgeAdjacentCells(const XmEdge& a_edge, VecInt& a_adjacentCellIdxs) const;

  VecInt GetEdgeAdjacentCells(const XmEdge& a_edge) const;

  std::vector<XmEdge> GetCellEdges(int a_cellIdx) const;
  void GetCellEdges(int a_cellIdx, std::vector<XmEdge>& a_edges) const;

  // Faces
  int GetCell3dFaceCount(int a_cellIdx) const;
  int GetCell3dFacePointCount(int a_cellIdx, int a_faceIdx) const;

  VecInt GetCell3dFacePoints(int a_cellIdx, int a_faceIdx) const;
  void GetCell3dFacePoints(int a_cellIdx, int a_faceIdx, VecInt& a_facePtIdxs) const;
  VecInt2d GetCell3dFacesPoints(int a_cellIdx) const;

  int GetCell3dFaceAdjacentCell(int a_cellIdx, int a_faceIdx) const;
  bool GetCell3dFaceAdjacentCell(int a_cellIdx,
                                 int a_faceIdx,
                                 int& a_neighborCell,
                                 int& a_neighborFace) const;

  XmUGridFaceOrientation GetCell3dFaceOrientation(int a_cellIdx, int a_faceIdx) const;
  XmUGridFaceOrientation FaceOrientation(int a_cellIdx, int a_faceIdx) const;
  XmUGridFaceOrientation VerticalOrientationFromOpposing(int a_cellIdx, int a_faceIdx) const;
  bool IsSideFace(int a_cellIdx, int a_faceIdx) const;
  XmUGridFaceOrientation ConnectedTopOrBottom(int a_cellIdx, int a_faceIdx) const;
  XmUGridFaceOrientation GetOrientationFromArea(int a_cellIdx, int a_faceIdx) const;

private:
  void UpdateLinks(); // Calls UpdateCellLinks & UpdatePointLinks
  void UpdateCellLinks();
  void UpdatePointLinks();

  void SetModified();

  bool IsCellValidWithPointChange(int a_cellIdx,
                                  int a_changedPtIdx,
                                  const Pt3d& a_newPosition) const;
  bool IsValidCellIdx(int a_cellIdx) const;

  static int DimensionFromCellType(XmUGridCellType a_cellType);

  int GetNumberOfItemsForCell(int a_cellIdx) const;

  // Optimized for efficiency
  void GetCellCellstream(int a_cellIdx, const int** a_start, int& a_length) const;

  int GetNumberOfPolyhedronEdges(int a_cellIdx) const;
  static void GetUniquePointsFromPolyhedronCellstream(const VecInt& a_cellstream,
                                                      int a_numCellItems,
                                                      int& a_currIdx,
                                                      VecInt& a_uniqueGetCellPoints,
                                                      VecInt& a_pointLastUsedIdx);
  static bool GetUniquePointsFromPolyhedronSingleCellstream(const VecInt& a_cellstream,
                                                            VecInt& a_cellPoints);
  static void GetUniqueEdgesFromPolyhedronCellstream(
    const int* a_start,
    int& a_length,
    boost::container::flat_set<XmEdge>& a_cellEdges,
    int& a_currIdx);

  bool GetPlanViewPolygon2d(int a_cellIdx, VecPt3d& a_polygon) const;
  bool GetPlanViewPolygon3d(int a_cellIdx, VecPt3d& a_polygon) const;

  bool IsFaceSide(const VecInt& a_facePts) const;                 // plan view
  bool GetCellXySegments(int cellIdx, VecPt3d& a_segments) const; // plan view
  void GetEdgesOfFace(const VecInt& a_face, std::vector<XmEdge>& a_edges) const;
  bool DoEdgesCrossWithPointChange(int a_changedPtIdx,
                                   const Pt3d& a_newPosition,
                                   const std::vector<XmEdge>& a_edges) const;
  void GetExtentsFromPoints(const VecPt3d& a_locations, Pt3d& a_min, Pt3d& a_max) const;
  bool GetFaceXySegments(int a_cellIdx, int a_faceIdx, VecPt3d& a_segments) const; // plan view

  void CalculateCacheValues() const;
  void ClearCacheValues();
  int GetCell3dFaceCountNoCache(int a_cellIdx) const;
  int GetCell3dFaceAdjacentCellNoCache(int a_cellIdx, int a_faceIdx) const;
  XmUGridFaceOrientation GetCell3dFaceOrientationNoCache(int a_cellIdx, int a_faceIdx) const;
  bool GetNextFaceColumn(const VecInt& a_facePoints,
                         int a_starti,
                         int& a_columnBegin,
                         int& a_columnEnd) const;
  void GetFacePointSegments(const VecInt& a_facePts,
                            int a_columnBegin,
                            int a_columnEnd,
                            VecPt3d& a_segments) const;
  XmUGridFaceOrientation FaceOrientationWithFail(int a_cellIdx, int a_faceIdx) const;

  /// Constant for when a cached integer item needs to be calculated.
  enum XmUGridCacheHolder {
    NEEDS_CALCULATION = -2 ///< Cached value needs to be calculated
  };

  VecPt3d m_locations;              ///< UGrid point locations
  VecInt m_cellstream;              ///< UGrid cell stream. @see SetCellstream, GetCellstream
  VecInt m_cellIdxToStreamIdx;      ///< Indexes for each cell in the cell stream
  VecInt m_pointsToCells;           ///< Array of points cells (goes from pointIdx to list
                                    ///< of cells)
  VecInt m_pointIdxToPointsToCells; ///< Indexes for each point in array of
                                    ///< points cells
  bool m_modified = false;          ///< Has UGrid been modified since last SetUnmodified call?
  bool m_useCache = true;           ///< Are we using caching for some calls?
  mutable VecInt m_numberOfFaces;   ///< Cache for number of cell faces
  mutable VecInt m_cellFaceOffset;  ///< Cache for offset to m_faceOrientation and m_faceNeighbor
  mutable VecInt m_faceOrientation; ///< For vertically prismatic cell is face top, side, bottom
  mutable VecInt m_faceNeighbor;    ///< Cache for Face neighbor
  mutable VecInt m_cellDimensionCounts; ///< Cache for cell dimension counts
  XmUGridCellOrder m_cellOrder = XMU_CELL_ORDER_UNKNOWN; ///< Cell order. When known speeds
                                                         ///< up face orientation calculation.
};

//----- Internal functions -----------------------------------------------------
namespace
{
typedef std::vector<XmEdge> VecEdge; ///< A Vector of XmEdges.

constexpr int BAD_CELL_STREAM = -1;

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
  // 0D
  case XMU_EMPTY_CELL:
  case XMU_VERTEX:
  case XMU_POLY_VERTEX:
  case XMU_CONVEX_POINT_SET: // Special class of cells formed by convex group of
                             // points
    return fg_empty;

  // 1D
  case XMU_LINE:
    return fg_line;

  // 2D
  case XMU_TRIANGLE:
    return fg_triangle;
  case XMU_PIXEL:
    return fg_pixel;
  case XMU_QUAD:
    return fg_quad;

  // should be using cell stream
  case XMU_POLYGON:
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

  // 3D dimensions
  case XMU_TETRA:
    return fg_tetra;
  case XMU_WEDGE:
    return fg_wedge;
  case XMU_VOXEL:
    return fg_voxel;
  case XMU_HEXAHEDRON:
    return fg_hexahedron;
  case XMU_PYRAMID:
    return fg_pyramid;
  case XMU_PENTAGONAL_PRISM:
    return fg_pentagonalPrism;
  case XMU_HEXAGONAL_PRISM:
    return fg_hexagonalPrism;

  // should be using cell stream
  case XMU_POLYHEDRON:
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
  default:
    XM_ASSERT(0);
    return fg_empty;
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

  // 3D dimensions
  case XMU_TETRA:
    return fg_tetra;
  case XMU_WEDGE:
    return fg_wedge;
  case XMU_VOXEL:
    return fg_voxel;
  case XMU_HEXAHEDRON:
    return fg_hexahedron;
  case XMU_PYRAMID:
    return fg_pyramid;
  case XMU_PENTAGONAL_PRISM:
    return fg_pentagonalPrism;
  case XMU_HEXAGONAL_PRISM:
    return fg_hexagonalPrism;

  // should be using cell stream
  case XMU_POLYHEDRON:
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
  default:
    XM_ASSERT(0);
    return fg_empty;
  }

  XM_ASSERT(0);
  return fg_empty;
} // iGetFaceOffsetTable
//------------------------------------------------------------------------------
/// \brief Determine if a location is within the X/Y bounds of two other points.
/// \param[in] a_location The point location.
/// \param[in] a_first The first bounds location.
/// \param[in] a_second The second bounds location.
/// \return True if the point is within the bounds locations.
//------------------------------------------------------------------------------
bool iPointInSegmentBounds(const Pt3d& a_location, const Pt3d& a_first, const Pt3d& a_second)
{
  bool inBounds = a_location.x >= std::min(a_first.x, a_second.x) &&
                  a_location.y >= std::min(a_first.y, a_second.y) &&
                  a_location.x <= std::max(a_first.x, a_second.x) &&
                  a_location.y <= std::max(a_first.y, a_second.y);
  return inBounds;
} // iPointInSegmentBounds
//------------------------------------------------------------------------------
/// \brief Gets a vector of sorted unique values.
/// \param[in] a_segments The input vector.
/// \return A sorted vector of unique values.
//------------------------------------------------------------------------------
template <typename T>
std::vector<T> iGetUniquePoints(const std::vector<T>& a_segments)
{
  std::vector<T> points = a_segments;
  std::sort(points.begin(), points.end());
  auto pIt = std::unique(points.begin(), points.end());
  points.resize(pIt - points.begin());
  return points;
} // iGetUniquePoints
//------------------------------------------------------------------------------
/// \brief Build a polygon from vector of polygon segments.
/// \param[in] a_segs Vector of segments that would make a polygon.
/// \param[out] a_polygon Output polygon vector ordered either CW or CCW.
//------------------------------------------------------------------------------
template <typename T>
void iBuildPolygon(std::vector<std::pair<T, T>>& a_segs, std::vector<T>& a_polygon)
{
  xms::VecChar placed(a_segs.size(), false);
  a_polygon.push_back(a_segs[0].first);
  a_polygon.push_back(a_segs[0].second);
  placed[0] = true;
  for (size_t i = 1; i != a_segs.size(); ++i)
  {
    T& toMatch = a_polygon.back();
    for (size_t j = 1; j != a_segs.size(); ++j)
    {
      if (!placed[j])
      {
        if (a_segs[j].first == toMatch)
        {
          a_polygon.push_back(a_segs[j].second);
          placed[j] = true;
        }
        else if (a_segs[j].second == toMatch)
        {
          a_polygon.push_back(a_segs[j].first);
          placed[j] = true;
        }
      }
    }
  }
} // iBuildPolygon
//------------------------------------------------------------------------------
/// \brief Builds a vector of sorted unique segments as a std::pair from a vector
/// with segments ordered {firstIdx1, firstIdx2, secondIdx1, secondIdx2}, etc.
/// \param[in] a_segments A vector of segments in odd/even indices.
/// \return A sorted vector of segments as std::pairs.
//------------------------------------------------------------------------------
template <typename T>
std::vector<std::pair<T, T>> iGetUniqueSegments(const std::vector<T>& a_segments)
{
  std::vector<std::pair<T, T>> segs;
  for (size_t i = 0; i < a_segments.size(); i += 2)
  {
    T a = a_segments[i];
    T b = a_segments[i + 1];
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
/// \brief Merge possibly duplicate segments into a unique polygon.
/// \param[in] a_segments The segments ordered {firstIdx1, firstIdx2,
/// secondIdx1, secondIdx2}, etc.
/// \param[out] a_polygon Output polygon with points ordered CCW.
//------------------------------------------------------------------------------
void iMergeSegmentsToPoly(const VecPt3d& a_segments, VecPt3d& a_polygon)
{
  if (a_segments.empty())
    return;

  VecPt3d points = iGetUniquePoints(a_segments);
  std::vector<std::pair<Pt3d, Pt3d>> segs = iGetUniqueSegments(a_segments);

  // if any point is on any other segment split up the segment
  for (auto& point : points)
  {
    size_t segsSize = segs.size();
    for (size_t i = 0; i < segsSize; ++i)
    {
      Pt3d pt1 = segs[i].first;
      Pt3d pt2 = segs[i].second;
      if (point != pt1 && point != pt2 && iPointInSegmentBounds(point, pt1, pt2))
      {
        Pt3d diff = pt1 - pt2;
        double distance = std::max(fabs(diff.x), fabs(diff.y));
        double tolerance = distance / 1.0e6;
        if (gmOnLineWithTol(pt1, pt2, point.x, point.y, tolerance))
        {
          segs.emplace_back(point, pt2);
          segs[i].second = point;
        }
      }
    }
  }
  std::sort(segs.begin(), segs.end());
  auto segIt = std::unique(segs.begin(), segs.end());
  segs.resize(segIt - segs.begin());

  iBuildPolygon(segs, a_polygon);

  if (a_polygon.size() > 3 && a_polygon.front() == a_polygon.back())
  {
    a_polygon.pop_back();
    double area = gmPolygonArea(&a_polygon[0], (int)a_polygon.size());
    if (area < 0)
      std::reverse(a_polygon.begin(), a_polygon.end());
  }
  else
  {
    XM_ASSERT(0);
    a_polygon.clear();
  }
} // iMergeSegmentsToPoly

//------------------------------------------------------------------------------
/// \brief Check if a polygon cell in a stream is valid.
/// \param a_cellStream: The stream containing the cell.
/// \param a_points: The number of points in this grid. Used to ensure the cell
///                  only refers to valid points.
/// \param a_currIdx: The current index into the stream. Should point at the
///                   number of points in the polygon.
/// \param a_expectedPoints: The number of points the cell should have.
///        If a_isVariableLength is true, this is treated as the minimum number
///        of points. Otherwise, it is treated as the exact number of points.
/// \param a_isVariableLength: Whether the cell is variable length.
/// \returns: If the polygon was valid, the number of elements in the stream
///           that were part of it. If the polygon was invalid, 0.
//------------------------------------------------------------------------------
int iValidatePolygonCell(const VecInt& a_cellStream,
                         int a_points,
                         int a_currIdx,
                         int a_expectedPoints,
                         bool a_isVariableLength)
{
  int oldIdx = a_currIdx - 1; // Caller already took the polygon's type; add it back.

  int numPoints = a_cellStream[a_currIdx++];

  if (a_isVariableLength && numPoints < a_expectedPoints)
  {
    return BAD_CELL_STREAM;
  }
  if (!a_isVariableLength && numPoints != a_expectedPoints)
  {
    return BAD_CELL_STREAM;
  }

  if (a_currIdx + numPoints > a_cellStream.size())
  {
    return BAD_CELL_STREAM;
  }

  for (int i = 0; i < numPoints; i++)
  {
    int point = a_cellStream[a_currIdx++];
    if (point < 0 || point >= a_points)
    {
      return BAD_CELL_STREAM;
    }
  }

  return a_currIdx - oldIdx;
} // iValidatePolygonCell

//------------------------------------------------------------------------------
/// \brief Check if a polyhedron cell in a stream is valid.
/// \param a_cellStream: The stream containing the cell.
/// \param a_points: The number of points in this grid. Used to ensure the cell
///                  only refers to valid points.
/// \param a_currIdx: The current index into the stream. Should point at the
///                   number of faces in the polyhedron.
/// \returns: If the polyhedron was valid, the number of elements in the stream
///           that were part of it. If the polyhedron was invalid, BAD_CELL_STREAM.
//------------------------------------------------------------------------------
int iValidatePolyhedronCell(const VecInt& a_cellStream, int a_points, int a_currIdx)
{
  int oldIdx = a_currIdx - 1; // Caller already took the polyhedron's type; add it back.

  int numFaces = a_cellStream[a_currIdx++];

  if (numFaces < 3)
  {
    return BAD_CELL_STREAM;
  }

  for (int faceIdx = 0; faceIdx < numFaces; ++faceIdx)
  {
    if (a_currIdx >= a_cellStream.size())
    {
      return BAD_CELL_STREAM;
    }

    int numPoints = a_cellStream[a_currIdx++];
    if (numPoints < 3)
    {
      return BAD_CELL_STREAM;
    }

    if (a_currIdx + numPoints > a_cellStream.size())
    {
      return BAD_CELL_STREAM;
    }

    for (int i = 0; i < numPoints; i++)
    {
      int point = a_cellStream[a_currIdx++];
      if (point < 0 || point >= a_points)
      {
        return BAD_CELL_STREAM;
      }
    }
  }

  return a_currIdx - oldIdx;
} // iValidatePolyhedronCell

//------------------------------------------------------------------------------
/// \brief Check if a cell in a stream is valid.
/// \param a_cellStream: The stream containing the cell.
/// \param a_points: The number of points in this grid. Used to ensure the cell
///                  only refers to valid points.
/// \param a_currIdx: The current index into the stream. Should point at the
///                   polygon's type.
/// \returns: If the polygon was valid, the number of elements in the stream
///           that were part of it. If the polygon was invalid, BAD_CELL_STREAM.
//------------------------------------------------------------------------------
int iValidateCell(const VecInt& a_cellStream, int a_points, int a_currIdx)
{
  int oldIdx = a_currIdx;

  if (a_currIdx + 1 >= a_cellStream.size())
  {
    return BAD_CELL_STREAM; // Cell type is present, but number of points missing
  }

  int cellType = a_cellStream[a_currIdx++];

  switch (cellType)
  {
  case XMU_EMPTY_CELL:
    return iValidatePolygonCell(a_cellStream, a_points, a_currIdx, 0, false);
  case XMU_VERTEX:
    return iValidatePolygonCell(a_cellStream, a_points, a_currIdx, 1, false);
  case XMU_LINE:
    return iValidatePolygonCell(a_cellStream, a_points, a_currIdx, 2, false);
  case XMU_TRIANGLE:
    return iValidatePolygonCell(a_cellStream, a_points, a_currIdx, 3, false);
  case XMU_PIXEL:
  case XMU_QUAD:
  case XMU_TETRA:
    return iValidatePolygonCell(a_cellStream, a_points, a_currIdx, 4, false);
  case XMU_PYRAMID:
    return iValidatePolygonCell(a_cellStream, a_points, a_currIdx, 5, false);
  case XMU_WEDGE:
  case XMU_PENTAGONAL_PRISM:
    return iValidatePolygonCell(a_cellStream, a_points, a_currIdx, 6, false);
  case XMU_HEXAGONAL_PRISM:
    return iValidatePolygonCell(a_cellStream, a_points, a_currIdx, 7, false);
  case XMU_VOXEL:
  case XMU_HEXAHEDRON:
    return iValidatePolygonCell(a_cellStream, a_points, a_currIdx, 8, false);
  case XMU_POLY_VERTEX:
    return iValidatePolygonCell(a_cellStream, a_points, a_currIdx, 1, true);
  case XMU_POLY_LINE:
    return iValidatePolygonCell(a_cellStream, a_points, a_currIdx, 2, true);
  case XMU_TRIANGLE_STRIP:
  case XMU_POLYGON:
    return iValidatePolygonCell(a_cellStream, a_points, a_currIdx, 3, true);
  case XMU_POLYHEDRON:
    return iValidatePolyhedronCell(a_cellStream, a_points, a_currIdx);
  default:
    return iValidatePolygonCell(a_cellStream, a_points, a_currIdx, a_cellStream[a_currIdx], false);
  }

  XM_ASSERT(false); // This should be unreachable.
  return BAD_CELL_STREAM;
} // iValidateCell

} // namespace

////////////////////////////////////////////////////////////////////////////////
/// \class XmUGrid::Impl
/// \brief Implementation for XmUGrid which provides geometry for an
///        unstructured grid.
////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
/// \brief Returns the modified flag. Gets set when points or cells get changed.
/// \return the modified flag
//------------------------------------------------------------------------------
bool XmUGrid::Impl::GetModified() const
{
  return m_modified;
} // XmUGrid::Impl::GetModified
//------------------------------------------------------------------------------
/// \brief Resets the modified flag to false.
//------------------------------------------------------------------------------
void XmUGrid::Impl::SetUnmodified()
{
  m_modified = false;
} // XmUGrid::Impl::SetUnmodified
//------------------------------------------------------------------------------
/// \brief Sets the modified flag to true.
//------------------------------------------------------------------------------
void XmUGrid::Impl::SetModified()
{
  ClearCacheValues();
  m_modified = true;
} // XmUGrid::Impl::SetModified
//------------------------------------------------------------------------------
/// \brief Turn on or off use of caching.
/// \param a_useCache Flag to determine if caching will be used.
//------------------------------------------------------------------------------
void XmUGrid::Impl::SetUseCache(bool a_useCache)
{
  m_useCache = a_useCache;
} // XmUGrid::Impl::SetUseCache
// Points
//------------------------------------------------------------------------------
/// \brief Get the number of points.
/// \return the number of points
//------------------------------------------------------------------------------
int XmUGrid::Impl::GetPointCount() const
{
  return (int)m_locations.size();
} // XmUGrid::Impl::GetPointCount
//------------------------------------------------------------------------------
/// \brief Get vector of UGrid points.
/// \return constant reference to vector of points
//------------------------------------------------------------------------------
const VecPt3d& XmUGrid::Impl::GetLocations() const
{
  return m_locations;
} // XmUGrid::Impl::GetLocations
//------------------------------------------------------------------------------
/// \brief Set UGrid points.
/// \param[in] a_locations vector of point locations
//------------------------------------------------------------------------------
void XmUGrid::Impl::SetLocations(const VecPt3d& a_locations)
{
  m_locations = a_locations;
  SetModified();
} // XmUGrid::Impl::SetLocations
//------------------------------------------------------------------------------
/// \brief Get the point
/// \param[in] a_pointIdx the index of the point
/// \return the point or an initialize point if the index is invalid
//------------------------------------------------------------------------------
Pt3d XmUGrid::Impl::GetPointLocation(int a_pointIdx) const
{
  if (a_pointIdx >= 0 && a_pointIdx < m_locations.size())
    return m_locations[a_pointIdx];
  return {};
} // XmUGrid::Impl::GetPointLocation
//------------------------------------------------------------------------------
/// \brief Set the point
/// \param[in] a_pointIdx the index of the point
/// \param[in] a_location The new location of the specified point
/// \return whether the point was successfully set
//------------------------------------------------------------------------------
bool XmUGrid::Impl::SetPointLocation(int a_pointIdx, const Pt3d& a_location)
{
  if (a_pointIdx >= 0 && a_pointIdx < m_locations.size())
  {
    m_locations[a_pointIdx] = a_location;
    SetModified();
    return true;
  }
  return false;
} // XmUGrid::Impl::SetPointLocation

//------------------------------------------------------------------------------
/// \brief Get the X, Y location of a point.
/// \param[in] a_pointIdx The index of the point.
/// \return The location of the point with Z set to 0.0.
//------------------------------------------------------------------------------
Pt3d XmUGrid::Impl::GetPointXy0(int a_pointIdx) const
{
  Pt3d pt = GetPointLocation(a_pointIdx);
  pt.z = 0.0;
  return pt;
} // XmUGrid::Impl::GetPointXy0

//------------------------------------------------------------------------------
/// \brief Convert a vector of point indices into a vector of point 3d
/// \param[in] a_points a vector of point indices
/// \return vector of point 3d
//------------------------------------------------------------------------------
VecPt3d XmUGrid::Impl::GetPointsLocations(const VecInt& a_points) const
{
  VecPt3d point3d;
  for (auto point : a_points)
  {
    point3d.push_back(GetPointLocation(point));
  }
  return point3d;
} // XmUGrid::Impl::GetPointsLocations

//------------------------------------------------------------------------------
/// \brief Get extents of all points in UGrid
/// \param[out] a_min minimum extent of all points
/// \param[out] a_max maximum extent of all points
//------------------------------------------------------------------------------
void XmUGrid::Impl::GetExtents(Pt3d& a_min, Pt3d& a_max) const
{
  GetExtentsFromPoints(m_locations, a_min, a_max);
} // XmUGrid::Impl::GetExtents

//------------------------------------------------------------------------------
/// \brief Get the number of cells that use a point.
/// \param a_pointIdx The point to check.
/// \return The number of cells that use the point.
//------------------------------------------------------------------------------
int XmUGrid::Impl::GetPointAdjacentCellCount(int a_pointIdx) const
{
  if (a_pointIdx < 0 || a_pointIdx >= m_locations.size())
    return 0;
  int numCells = m_pointsToCells[m_pointIdxToPointsToCells[a_pointIdx]];
  return numCells;
} // XmUGrid::Impl::GetPointAdjacentCellCount

//------------------------------------------------------------------------------
/// \brief Get the cells that are associated with the specified point
/// \param[in] a_pointIdx the index of the point
/// \return a vector of the cell indices associated with this point
//------------------------------------------------------------------------------
VecInt XmUGrid::Impl::GetPointAdjacentCells(int a_pointIdx) const
{
  VecInt cellsOfPoint;
  GetPointAdjacentCells(a_pointIdx, cellsOfPoint);
  return cellsOfPoint;
} // XmUGrid::Impl::GetPointAdjacentCells
//------------------------------------------------------------------------------
/// \brief Get the cells that are associated with the specified point
/// \param[in] a_pointIdx the index of the point
/// \param[out] a_adjacentCells a vector of the adjacent cell indices
/// \return a vector of the cell indices associated with this point
//------------------------------------------------------------------------------
void XmUGrid::Impl::GetPointAdjacentCells(int a_pointIdx, VecInt& a_adjacentCells) const
{
  a_adjacentCells.clear();
  int numCells = GetPointAdjacentCellCount(a_pointIdx);
  for (int cellIdx = 0; cellIdx < numCells; cellIdx++)
  {
    a_adjacentCells.push_back(m_pointsToCells[m_pointIdxToPointsToCells[a_pointIdx] + cellIdx + 1]);
  }
} // XmUGrid::Impl::GetPointAdjacentCells
//------------------------------------------------------------------------------
/// \brief Gets the common cells from a vector of points
/// \param[in] a_points a vector of unique points
/// \return a vector of cell indices
//------------------------------------------------------------------------------
VecInt XmUGrid::Impl::GetPointsAdjacentCells(const VecInt& a_points) const
{
  VecInt commonCells;
  if (!a_points.empty())
    GetPointsAdjacentCells(&a_points[0], (int)a_points.size(), commonCells);
  return commonCells;
} // XmUGrid::Impl::GetPointsAdjacentCells
//------------------------------------------------------------------------------
/// \brief Gets the common cells from a vector of points
/// \param[in] a_pointIdxs an array of point indices
/// \param[in] a_numPointIdxs number of points in array
/// \param[out] a_commonCellIdxs a vector of cell indices
//------------------------------------------------------------------------------
void XmUGrid::Impl::GetPointsAdjacentCells(const int* a_pointIdxs,
                                           int a_numPointIdxs,
                                           VecInt& a_commonCellIdxs) const
{
  a_commonCellIdxs.clear();
  if (a_numPointIdxs == 0)
    return;
  a_commonCellIdxs = GetPointAdjacentCells(a_pointIdxs[0]);
  for (int i = 1; i < a_numPointIdxs; ++i)
  {
    VecInt tempAssociatedCells = GetPointAdjacentCells(a_pointIdxs[i]);
    VecInt remove;
    for (int j = 0; j < a_commonCellIdxs.size(); ++j)
    {
      bool found = false;
      for (int tempAssociatedCell : tempAssociatedCells)
      {
        if (a_commonCellIdxs[j] == tempAssociatedCell)
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
    if (a_commonCellIdxs.empty())
      break;
  }
} // XmUGrid::Impl::GetPointsAdjacentCells
//------------------------------------------------------------------------------
/// \brief Gets the cells adjacent to all of a vector of points.
/// \param[in] a_pointIdxs a vector of unique points
/// \param[out] a_adjacentCellIdxs a vector of cell indices
//------------------------------------------------------------------------------
void XmUGrid::Impl::GetPointsAdjacentCells(const VecInt& a_pointIdxs,
                                           VecInt& a_adjacentCellIdxs) const
{
  if (!a_pointIdxs.empty())
    GetPointsAdjacentCells(&a_pointIdxs[0], (int)a_pointIdxs.size(), a_adjacentCellIdxs);
} // XmUGrid::Impl::GetPointsAdjacentCells
//------------------------------------------------------------------------------
/// \brief Gets the cells adjacent to both of the two points.
/// \param[in] a_pointIdx1 first point index
/// \param[in] a_pointIdx2 second point index
/// \param[out] a_adjacentCellIdxs a vector of cell indices
//------------------------------------------------------------------------------
void XmUGrid::Impl::GetPointsAdjacentCells(int a_pointIdx1,
                                           int a_pointIdx2,
                                           VecInt& a_adjacentCellIdxs) const
{
  int points[] = {a_pointIdx1, a_pointIdx2};
  GetPointsAdjacentCells(points, 2, a_adjacentCellIdxs);
} // XmUGrid::Impl::GetPointsAdjacentCells

//------------------------------------------------------------------------------
/// \brief Given a point gets point indices attached to the point by an edge.
/// \param[in] a_pointIdx The point to get adjacent points from.
/// \param[out] a_edgePoints The indices of the adjacent points.
//------------------------------------------------------------------------------
void XmUGrid::GetPointAdjacentPoints(int a_pointIdx, VecInt& a_edgePoints) const
{
  m_impl->GetPointAdjacentPoints(a_pointIdx, a_edgePoints);
} // XmUGrid::GetPointAdjacentPoints

//------------------------------------------------------------------------------
/// \brief Given a point gets point locations attached to the point by an edge.
/// \param[in] a_pointIdx The point to get attached point from.
/// \param[out] a_edgePoints A vector of points attached across edges.
//------------------------------------------------------------------------------
void XmUGrid::GetPointAdjacentLocations(int a_pointIdx, VecPt3d& a_edgePoints) const
{
  m_impl->GetPointAdjacentLocations(a_pointIdx, a_edgePoints);
} // XmUGrid::GetPointAdjacentLocations
// Cells
//------------------------------------------------------------------------------
/// \brief Get the number of cells.
/// \return the number of cells
//------------------------------------------------------------------------------
int XmUGrid::Impl::GetCellCount() const
{
  if (m_cellIdxToStreamIdx.empty())
    return 0;
  else
    return (int)m_cellIdxToStreamIdx.size() - 1;
} // XmUGrid::Impl::GetCellCount
//------------------------------------------------------------------------------
/// \brief Get the number of cell points (including polyhedron).
/// \param[in] a_cellIdx the index of the cell
/// \return a vector of point indices
//------------------------------------------------------------------------------
int XmUGrid::Impl::GetCellPointCount(int a_cellIdx) const
{
  int pointCount = 0;
  if (GetCellType(a_cellIdx) == XMU_POLYHEDRON)
  {
    boost::container::flat_set<int> uniqueIdxs;
    const int* cellstream = nullptr;
    int streamLength;
    GetCellCellstream(a_cellIdx, &cellstream, streamLength);
    if (cellstream)
    {
      int currIdx = 1;
      int numFaces = cellstream[currIdx++];
      for (int faceIdx = 0; faceIdx < numFaces; faceIdx++)
      {
        int numPoints = cellstream[currIdx++];
        for (int pointIdx = 0; pointIdx < numPoints; ++pointIdx)
        {
          int point = cellstream[currIdx++];
          uniqueIdxs.insert(point);
        }
      }
    }
    pointCount = (int)uniqueIdxs.size();
  }
  else
  {
    pointCount = GetNumberOfItemsForCell(a_cellIdx);
  }

  return pointCount;
} // XmUGrid::Impl::GetCellPointCount
//------------------------------------------------------------------------------
/// \brief Get the points of a cell (including polyhedron)
/// \param[in] a_cellIdx the index of the cell
/// \return a vector of point indices
//------------------------------------------------------------------------------
VecInt XmUGrid::Impl::GetCellPoints(int a_cellIdx) const
{
  VecInt pointsOfCell;
  GetCellPoints(a_cellIdx, pointsOfCell);
  return pointsOfCell;
} // XmUGrid::Impl::GetCellPoints
//------------------------------------------------------------------------------
/// \brief Get the points of a cell.
/// \param[in] a_cellIdx the index of the cell
/// \param[out] a_cellPoints the points of the cell
/// \return if the cell index is valid
//------------------------------------------------------------------------------
bool XmUGrid::Impl::GetCellPoints(int a_cellIdx, VecInt& a_cellPoints) const
{
  a_cellPoints.clear();
  VecInt cellstream;
  if (GetCellCellstream(a_cellIdx, cellstream))
  {
    XM_ENSURE_TRUE_NO_ASSERT(!cellstream.empty(), false);
    int cellType = cellstream[0];
    if (cellType == XMU_POLYHEDRON)
    {
      GetUniquePointsFromPolyhedronSingleCellstream(cellstream, a_cellPoints);
      return true;
    }
    else if (cellType == XMU_PIXEL)
    {
      a_cellPoints.push_back(cellstream[2]);
      a_cellPoints.push_back(cellstream[3]);
      a_cellPoints.push_back(cellstream[5]);
      a_cellPoints.push_back(cellstream[4]);
      return true;
    }
    else
    {
      a_cellPoints.assign(cellstream.begin() + 2, cellstream.end());
      return true;
    }
  }
  return false;
} // XmUGrid::Impl::GetCellPoints

//------------------------------------------------------------------------------
/// \brief Get locations of cell points.
/// \param[in] a_cellIdx the index of the cell
/// \param[out] a_cellLocations The locations of the cell points
//------------------------------------------------------------------------------
void XmUGrid::Impl::GetCellLocations(int a_cellIdx, VecPt3d& a_cellLocations) const
{
  VecInt ptIdxs = GetCellPoints(a_cellIdx);
  a_cellLocations = GetPointsLocations(ptIdxs);
} // XmUGrid::Impl::GetCellPoints

//------------------------------------------------------------------------------
/// \brief Get the cell type of a specified cell.
/// \param[in] a_cellIdx the index of the cell
/// \return The type of the specified cell or -1 if invalid.
//------------------------------------------------------------------------------
XmUGridCellType XmUGrid::Impl::GetCellType(int a_cellIdx) const
{
  if (a_cellIdx < 0 || m_cellIdxToStreamIdx.size() < 2 ||
      a_cellIdx > m_cellIdxToStreamIdx.size() - 2)
  {
    return XMU_INVALID_CELL_TYPE;
  }
  else
  {
    int cellStart = m_cellIdxToStreamIdx[a_cellIdx];
#if _DEBUG
    if ((m_cellstream[cellStart] > XMU_PYRAMID) && (m_cellstream[cellStart] != XMU_POLYHEDRON) ||
        (m_cellstream[cellStart] == XMU_TRIANGLE_STRIP))
    {
      assert("UNSUPPORTED TYPE!");
    }
#endif
    return (XmUGridCellType)m_cellstream[cellStart];
  }
} // XmUGrid::Impl::GetCellType
//------------------------------------------------------------------------------
/// \brief Count all number of the cells with each dimension (0, 1, 2, 3)
/// \return the count of dimensions of all of the cells of the ugrid
//------------------------------------------------------------------------------
std::vector<int> XmUGrid::Impl::GetDimensionCounts() const
{
  if (!m_cellDimensionCounts.empty())
  {
    return m_cellDimensionCounts;
  }
  else
  {
    m_cellDimensionCounts.clear();
    m_cellDimensionCounts.resize(4, 0);
    int itemp = 0;
    int cellCount = GetCellCount();
    for (int i = 0; i < cellCount; i++)
    {
      itemp = GetCellDimension(i);
      if (itemp >= 0)
      {
        m_cellDimensionCounts[itemp]++;
      }
    }
    return m_cellDimensionCounts;
  }
} // XmUGrid::Impl::GetDimensionCounts
//------------------------------------------------------------------------------
/// \brief Get the dimension of the specified cell.
/// \param[in] a_cellIdx the index of the cell
/// \return the dimension of the cells or -1 if invalid index or invalid
/// dimension
//------------------------------------------------------------------------------
int XmUGrid::Impl::GetCellDimension(int a_cellIdx) const
{
  return DimensionFromCellType(GetCellType(a_cellIdx));
} // XmUGrid::Impl::GetCellDimension

//------------------------------------------------------------------------------
/// \brief Get the extents of the given cell.
/// \param[in] a_cellIdx The cell index to get the extents of.
/// \param[out] a_min The minimum location.
/// \param[out] a_max The maximum location.
//------------------------------------------------------------------------------
void XmUGrid::Impl::GetCellExtents(int a_cellIdx, Pt3d& a_min, Pt3d& a_max) const
{
  VecPt3d pts;
  GetCellLocations(a_cellIdx, pts);
  GetExtentsFromPoints(pts, a_min, a_max);
} // XmUGrid::Impl::GetCellExtents

//------------------------------------------------------------------------------
/// \brief Get cell stream vector for the entire UGrid.
/// \return constant reference to the cell stream vector
//------------------------------------------------------------------------------
const VecInt& XmUGrid::Impl::GetCellstream() const
{
  return m_cellstream;
} // XmUGrid::Impl::GetCellstream
//------------------------------------------------------------------------------
/// \brief Set the ugrid cells for the entire UGrid using a cell stream.
/// \param[in] a_cellstream cells defined as follows:
/// Hexahedrons, polygons, quads, triangles etc:
///   Cell type (ElemTypeEnum), number of points, point numbers.
///   Generally 0-based, CCW, bottom, then top. Not true
///   for pixel or voxel.
/// Polyhedrons:
///   Cell type, number of faces, [num points in face,
///   point numbers (0-based, CCW when looking in)] repeated
///   for each face.
/// \return if successfully set
//------------------------------------------------------------------------------
bool XmUGrid::Impl::SetCellstream(const VecInt& a_cellstream)
{
  if (IsValidCellstream(a_cellstream, (int)m_locations.size()))
  {
    m_cellstream = a_cellstream;
    UpdateLinks();
    SetModified();
    return true;
  }
  else
  {
    XM_LOG(xmlog::error, "Invalid cell stream data.");
    return false;
  }
} // XmUGrid::Impl::SetCellstream
//------------------------------------------------------------------------------
/// \brief Get cell stream vector for a single cell.
/// \param[in] a_cellIdx the index of the cell
/// \param[in] a_cellstream The cellstream of the cell
/// @see SetCellstream for more detail on cell stream definitions.
/// \return whether it was successfull or not
//------------------------------------------------------------------------------
bool XmUGrid::Impl::GetCellCellstream(int a_cellIdx, VecInt& a_cellstream) const
{
  a_cellstream.clear();
  if (a_cellIdx < 0 || m_cellIdxToStreamIdx.size() < 2 ||
      a_cellIdx > m_cellIdxToStreamIdx.size() - 2)
  {
    return false;
  }
  int startIndex(m_cellIdxToStreamIdx[a_cellIdx]), endIndex(m_cellIdxToStreamIdx[a_cellIdx + 1]);
  a_cellstream.assign(m_cellstream.begin() + startIndex, m_cellstream.begin() + endIndex);
  return true;
} // XmUGrid::Impl::GetCellCellstream
//------------------------------------------------------------------------------
/// \brief Get beginning index of cell in cell stream.
/// \param[in] a_cellIdx the index of the cell
/// \return The index of the cell in the cell stream.
//------------------------------------------------------------------------------
int XmUGrid::Impl::GetCellCellstreamIndex(int a_cellIdx) const
{
  if (a_cellIdx < 0 || a_cellIdx >= (int)m_cellIdxToStreamIdx.size())
  {
    return -1;
  }
  return m_cellIdxToStreamIdx[a_cellIdx];
} // XmUGrid::GetCellCellstreamIndex
//------------------------------------------------------------------------------
/// \brief Get the cells neighboring a cell (cells associated with any of it's points)
/// \param[in] a_cellIdx the index of the cell
/// \return vector of cell indices
//------------------------------------------------------------------------------
VecInt XmUGrid::Impl::GetCellAdjacentCells(int a_cellIdx) const
{
  VecInt neighbors;
  GetCellAdjacentCells(a_cellIdx, neighbors);
  return neighbors;
} // XmUGrid::Impl::GetCellAdjacentCells
//------------------------------------------------------------------------------
/// \brief Get the cells neighboring a cell (cells associated with any of it's points)
/// \param[in] a_cellIdx the index of the cell
/// \param[out] a_cellNeighbors vector of cell indices
//------------------------------------------------------------------------------
void XmUGrid::Impl::GetCellAdjacentCells(int a_cellIdx, VecInt& a_cellNeighbors) const
{
  a_cellNeighbors.clear();
  VecInt pointsOfCell;
  pointsOfCell = GetCellPoints(a_cellIdx);
  for (int pointIdx : pointsOfCell)
  {
    VecInt associatedCells = GetPointAdjacentCells(pointIdx);
    for (int associatedCell : associatedCells)
    {
      if (associatedCell != a_cellIdx)
      {
        bool found(false);
        for (int a_cellNeighbor : a_cellNeighbors)
        {
          if (a_cellNeighbor == associatedCell)
          {
            found = true;
          }
        }
        if (!found)
        {
          a_cellNeighbors.push_back(associatedCell);
        }
      }
    }
  }
} // XmUGrid::Impl::GetCellAdjacentCells
//------------------------------------------------------------------------------
/// \brief Get a plan view polygon of a specified cell
/// \param[in] a_cellIdx The index of the cell.
/// \param[out] a_polygon Vector of Pt3d that is the plan view polygon.
/// \return False if the cell index does not exist or if the cell is not 2 or 3
/// dimensional.
//------------------------------------------------------------------------------
bool XmUGrid::Impl::GetCellPlanViewPolygon(int a_cellIdx, VecPt3d& a_polygon) const
{
  a_polygon.clear();
  if (!IsValidCellIdx(a_cellIdx))
    return false;
  int dimension = GetCellDimension(a_cellIdx);
  if (dimension == 3)
    return GetPlanViewPolygon3d(a_cellIdx, a_polygon);
  else if (dimension == 2)
    return GetPlanViewPolygon2d(a_cellIdx, a_polygon);
  else
    return false;
} // XmUGrid::Impl::GetCellPlanViewPolygon

//------------------------------------------------------------------------------
/// \brief Get the centroid location of a cell.
/// \param[in] a_cellIdx The index of the cell.
/// \param[out] a_centroid The location of the cell centroid.
/// \return False if the cell index does not exist.
//------------------------------------------------------------------------------
bool XmUGrid::Impl::GetCellCentroid(int a_cellIdx, Pt3d& a_centroid) const
{
  VecPt3d polyPoints;
  bool retVal = true;
  Pt3d centroid = Pt3d(0.0, 0.0, 0.0);
  if (GetCellPlanViewPolygon(a_cellIdx, polyPoints))
  {
    centroid = gmComputePolygonCentroid(polyPoints);
  }
  else if (!IsValidCellIdx(a_cellIdx))
  {
    retVal = false;
  }
  else
  {
    VecPt3d cellPoints;
    GetCellLocations(a_cellIdx, cellPoints);
    for (Pt3d& pt : cellPoints)
    {
      centroid += pt;
    }
    centroid /= (double)cellPoints.size();
  }
  a_centroid = centroid;
  return retVal;
} // XmUGrid::Impl::GetCellCentroid
//------------------------------------------------------------------------------
/// \brief Determine whether a cell is valid after a point is moved.
/// \param[in] a_cellIdx the index of the cell
/// \param[in] a_changedPtIdx index of the point to be changed
/// \param[in] a_newPosition location the point is to be moved to
/// \return whether the cell is valid
//------------------------------------------------------------------------------
bool XmUGrid::Impl::IsCellValidWithPointChange(int a_cellIdx,
                                               int a_changedPtIdx,
                                               const Pt3d& a_newPosition) const
{
  if (GetCellDimension(a_cellIdx) == 2)
  {
    std::vector<XmEdge> edges = GetCellEdges(a_cellIdx);
    return !DoEdgesCrossWithPointChange(a_changedPtIdx, a_newPosition, edges);
  }
  else if (GetCellDimension(a_cellIdx) == 3)
  {
    //  Go through the affected faces and if they are not a side face
    // check if the edges cross each other
    VecInt2d faces = GetCell3dFacesPoints(a_cellIdx);
    for (auto& face : faces)
    {
      bool faceIsAffected = false;
      for (int ptIdx : face)
      {
        if (ptIdx == a_changedPtIdx)
        {
          faceIsAffected = true;
        }
      }
      if (faceIsAffected)
      {
        std::vector<XmEdge> edges;
        GetEdgesOfFace(face, edges);
        if (DoEdgesCrossWithPointChange(a_changedPtIdx, a_newPosition, edges))
          return false;
      }
    }
  }
  return true;
} // XmUGrid::Impl::IsCellValidWithPointChange
//------------------------------------------------------------------------------
/// \brief Determine if a cell index is valid.
/// \param[in] a_cellIdx the index of the cell
/// \return True if the cell index is valid.
//------------------------------------------------------------------------------
bool XmUGrid::Impl::IsValidCellIdx(int a_cellIdx) const
{
  return a_cellIdx >= 0 && a_cellIdx < GetCellCount();
} // XmUGrid::Impl::IsValidCellIdx
//------------------------------------------------------------------------------
/// \brief Determine whether adjacent cells are valid after a point is moved.
/// \param[in] a_changedPtIdx index of the point to be changed
/// \param[in] a_newPosition location the point is to be moved to
/// \return whether the change is valid
//------------------------------------------------------------------------------
bool XmUGrid::Impl::IsValidPointChange(int a_changedPtIdx, const Pt3d& a_newPosition) const
{
  bool validChange = false;
  if (a_changedPtIdx >= 0 && a_changedPtIdx < m_locations.size())
  {
    validChange = true;
    VecInt affectedCells = GetPointAdjacentCells(a_changedPtIdx);
    for (int affectedCell : affectedCells)
    {
      if (!IsCellValidWithPointChange(affectedCell, a_changedPtIdx, a_newPosition))
      {
        validChange = false;
        break;
      }
    }
  }
  return validChange;
} // XmUGrid::Impl::IsValidPointChange
//------------------------------------------------------------------------------
/// \brief Get the edges of a cell given a face
/// \param[in] a_face a vector of point indices of a face
/// \param[out] a_edges a vector of point indices of an edge
//------------------------------------------------------------------------------
void XmUGrid::Impl::GetEdgesOfFace(const VecInt& a_face, std::vector<XmEdge>& a_edges) const
{
  a_edges.reserve(a_face.size());
  for (int i = 1; i < a_face.size(); ++i)
  {
    a_edges.emplace_back(a_face[i - 1], a_face[i]);
  }
  if (a_edges.size() > 1)
    a_edges.emplace_back(a_face[a_face.size() - 1], a_face[0]);
} // XmUGrid::Impl::GetEdgesOfFace

//------------------------------------------------------------------------------
/// \brief Gets whether or not edges cross with a point change
/// \param[out] a_edges The edges to check
/// \param[in] a_changedPtIdx index of the point to be changed
/// \param[in] a_newPosition location the point is to be moved to
/// \return whether the edges cross
//------------------------------------------------------------------------------
bool XmUGrid::Impl::DoEdgesCrossWithPointChange(int a_changedPtIdx,
                                                const Pt3d& a_newPosition,
                                                const std::vector<XmEdge>& a_edges) const
{
  std::vector<std::pair<Pt3d, Pt3d>> changedEdges;
  std::vector<std::pair<Pt3d, Pt3d>> unChangedEdges;
  for (const auto& edge : a_edges)
  {
    if (edge.GetFirst() == a_changedPtIdx)
    {
      changedEdges.emplace_back(a_newPosition, GetPointLocation(edge.GetSecond()));
    }
    else if (edge.GetSecond() == a_changedPtIdx)
    {
      changedEdges.emplace_back(GetPointLocation(edge.GetFirst()), a_newPosition);
    }
    else
    {
      unChangedEdges.emplace_back(GetPointLocation(edge.GetFirst()),
                                  GetPointLocation(edge.GetSecond()));
    }
  }
  for (const auto& changedEdge : changedEdges)
  {
    for (const auto& unChangedEdge : unChangedEdges)
    {
      if (gmLinesCross(changedEdge.first, changedEdge.second, unChangedEdge.first,
                       unChangedEdge.second))
        return true;
    }
  }
  return false;
} // XmUGrid::Impl::DoEdgesCrossWithPointChange
// Edges
//------------------------------------------------------------------------------
/// \brief Get the number of edges for a cell.
/// \param[in] a_cellIdx the index of the cell
/// \return the count of cell edges
//------------------------------------------------------------------------------
int XmUGrid::Impl::GetCellEdgeCount(int a_cellIdx) const
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
} // XmUGrid::Impl::GetCellEdgeCount
//------------------------------------------------------------------------------
/// \brief Get the points of a cell.
/// \param[in] a_cellIdx the index of the cell
/// \param[in] a_edgeIdx the index of the edge
/// \return a standard pair of point indices (which is an edge)
//------------------------------------------------------------------------------
XmEdge XmUGrid::Impl::GetCellEdge(int a_cellIdx, int a_edgeIdx) const
{
  XmEdge edge;
  if (a_edgeIdx < 0)
    return edge;

  const int* cellstream = nullptr;
  int streamLength;
  GetCellCellstream(a_cellIdx, &cellstream, streamLength);
  if (cellstream)
  {
    if (streamLength < 4)
      return edge;

    int cellType = cellstream[0];
    switch (cellType)
    {
    case XMU_POLY_LINE:
    case XMU_POLYGON:
    {
      int numPoints = cellstream[1];
      const int* cellPoints = cellstream + 2;
      int idx1 = cellPoints[a_edgeIdx];
      int idx2 = cellPoints[(a_edgeIdx + 1) % numPoints];
      edge = XmEdge(idx1, idx2);
      break;
    }

    case XMU_POLYHEDRON:
    {
      boost::container::flat_set<XmEdge> cellEdges;
      int currIdx = 2;
      GetUniqueEdgesFromPolyhedronCellstream(cellstream, streamLength, cellEdges, currIdx);

      if (a_edgeIdx < (int)cellEdges.size())
        edge = *(cellEdges.begin() + a_edgeIdx);
      break;
    }

    default:
    {
      const VecEdge& edgeTable = iGetEdgeOffsetTable(cellType);
      if (a_edgeIdx < (int)edgeTable.size())
      {
        const XmEdge& edgeOffset = edgeTable[a_edgeIdx];
        const int* cellPoints = cellstream + 2;
        int idx1 = cellPoints[edgeOffset.GetFirst()];
        int idx2 = cellPoints[edgeOffset.GetSecond()];
        edge = XmEdge(idx1, idx2);
      }
      break;
    }
    }
  }

  return edge;
} // XmUGrid::Impl::GetCellEdge
//------------------------------------------------------------------------------
/// \brief Get the index of the adjacent cells (that shares the same cell edge)
/// \param[in] a_cellIdx the index of the cell
/// \param[in] a_edgeIdx the index of the edge
/// \return a vector of cell indices of the adjacent cells
//------------------------------------------------------------------------------
VecInt XmUGrid::Impl::GetCellEdgeAdjacentCells(int a_cellIdx, int a_edgeIdx) const
{
  VecInt adjacentCells;
  GetCellEdgeAdjacentCells(a_cellIdx, a_edgeIdx, adjacentCells);
  return adjacentCells;
} // XmUGrid::Impl::GetCellEdgeAdjacentCells
//------------------------------------------------------------------------------
/// \brief Get the index of the adjacent cells (that shares the same cell edge)
/// \param[in] a_cellIdx the index of the cell
/// \param[in] a_edgeIdx the index of the edge
/// \param[out] a_adjacentCellIdxs a vector of cell indices of the adjacent
///             cells
//------------------------------------------------------------------------------
void XmUGrid::Impl::GetCellEdgeAdjacentCells(int a_cellIdx,
                                             int a_edgeIdx,
                                             VecInt& a_adjacentCellIdxs) const
{
  a_adjacentCellIdxs.clear();
  VecInt adjacentCells;
  VecInt cellNeighbors = GetCellAdjacentCells(a_cellIdx);
  if (cellNeighbors.empty())
  {
    return;
  }
  if (a_edgeIdx < 0 || a_edgeIdx >= GetCellEdgeCount(a_cellIdx))
  {
    return;
  }

  XmEdge currEdge, neighborEdge;
  currEdge = GetCellEdge(a_cellIdx, a_edgeIdx);
  for (int cellNeighbor : cellNeighbors)
  {
    for (int k(0); k < GetCellEdgeCount(cellNeighbor); k++)
    {
      neighborEdge = GetCellEdge(cellNeighbor, k);
      if (currEdge.IsEquivalent(neighborEdge))
      {
        a_adjacentCellIdxs.push_back(cellNeighbor);
      }
    }
  }
} // XmUGrid::Impl::GetCellEdgeAdjacentCells
//------------------------------------------------------------------------------
/// \brief Get the index of the adjacent cells (that shares the same cell edge)
/// \param[in] a_cellIdx the index of the cell
/// \param[in] a_edgeIdx the index of the edge
/// \return index of the adjacent cell (or -1 if none).
//------------------------------------------------------------------------------
int XmUGrid::Impl::GetCell2dEdgeAdjacentCell(int a_cellIdx, int a_edgeIdx) const
{
  if (GetCellDimension(a_cellIdx) != 2)
    return -1;

  XmEdge edge = GetCellEdge(a_cellIdx, a_edgeIdx);
  int pointIdx = edge.GetFirst();

  int adjCellCount = GetPointAdjacentCellCount(pointIdx);
  for (int cellIdx = 0; cellIdx < adjCellCount; cellIdx++)
  {
    int adjacentCell = m_pointsToCells[m_pointIdxToPointsToCells[pointIdx] + cellIdx + 1];
    if (adjacentCell == a_cellIdx)
      continue;

    int edgeCount = GetCellEdgeCount(adjacentCell);
    for (int adjacentEdgeIdx = 0; adjacentEdgeIdx < edgeCount; ++adjacentEdgeIdx)
    {
      XmEdge adjacentEdge = GetCellEdge(adjacentCell, adjacentEdgeIdx);
      if (adjacentEdge.IsEquivalent(edge))
        return adjacentCell;
    }
  }

  return -1;
} // XmUGrid::Impl::GetCell2dEdgeAdjacentCell
//------------------------------------------------------------------------------
/// \brief Get the indices of the adjacent cells (that shares the same cell edge)
/// \param[in] a_edge the edge (a pair of point indices)
/// \param[out] a_adjacentCellIdxs a vector of cell indices of the adjacent cells
//------------------------------------------------------------------------------
void XmUGrid::Impl::GetEdgeAdjacentCells(const XmEdge& a_edge, VecInt& a_adjacentCellIdxs) const
{
  a_adjacentCellIdxs.clear();
  GetPointsAdjacentCells(a_edge.GetFirst(), a_edge.GetSecond(), a_adjacentCellIdxs);
} // XmUGrid::Impl::GetEdgeAdjacentCells
//------------------------------------------------------------------------------
/// \brief Get the index of the adjacent cells (that shares the same cell edge)
/// \param[in] a_edge the edge (a pair of point indices)
/// \return a vector of cell indices of the adjacent cells
//------------------------------------------------------------------------------
VecInt XmUGrid::Impl::GetEdgeAdjacentCells(const XmEdge& a_edge) const
{
  VecInt adjacentCellIdxs;
  GetEdgeAdjacentCells(a_edge, adjacentCellIdxs);
  return adjacentCellIdxs;
} // XmUGrid::Impl::GetEdgeAdjacentCells
//------------------------------------------------------------------------------
/// \brief Get the Edges of a cell.
/// \param[in] a_cellIdx the cells to whom the edges belong
/// \return a vector of edges
//------------------------------------------------------------------------------
std::vector<XmEdge> XmUGrid::Impl::GetCellEdges(int a_cellIdx) const
{
  std::vector<XmEdge> edges;
  GetCellEdges(a_cellIdx, edges);
  return edges;
} // XmUGrid::Impl::GetCellEdges
//------------------------------------------------------------------------------
/// \brief Get the Edges of a cell.
/// \param[in] a_cellIdx the cells to whom the edges belong
/// \param[out] a_edges a vector of edges (organized in std::pairs)
//------------------------------------------------------------------------------
void XmUGrid::Impl::GetCellEdges(int a_cellIdx, std::vector<XmEdge>& a_edges) const
{
  a_edges.clear();
  int numEdges = GetCellEdgeCount(a_cellIdx);
  for (int i = 0; i < numEdges; ++i)
  {
    a_edges.push_back(GetCellEdge(a_cellIdx, i));
  }
} // XmUGrid::Impl::GetCellEdges

//------------------------------------------------------------------------------
/// \brief Given a point gets point indices attached to the point by an edge.
/// \param[in] a_pointIdx The point to get adjacent points from.
/// \param[out] a_edgePoints The indices of the adjacent points.
//------------------------------------------------------------------------------
void XmUGrid::Impl::GetPointAdjacentPoints(int a_pointIdx, VecInt& a_edgePoints) const
{
  a_edgePoints.clear();
  VecInt associatedCells = GetPointAdjacentCells(a_pointIdx);
  if (associatedCells.empty())
  {
    return;
  }
  for (int associatedCell : associatedCells)
  {
    for (int j = 0; j < GetCellEdgeCount(associatedCell); ++j)
    {
      XmEdge temp = GetCellEdge(associatedCell, j);
      if (temp.GetFirst() == a_pointIdx)
      {
        a_edgePoints.push_back(temp.GetSecond());
      }
      else if (temp.GetSecond() == a_pointIdx)
      {
        a_edgePoints.push_back(temp.GetFirst());
      }
    }
  }
  std::sort(a_edgePoints.begin(), a_edgePoints.end());
  auto it = std::unique(a_edgePoints.begin(), a_edgePoints.end());
  a_edgePoints.erase(it, a_edgePoints.end());
} // XmUGrid::Impl::GetPointAdjacentPoints

//------------------------------------------------------------------------------
/// \brief Given a point gets point locations attached to the point by an edge.
/// \param[in] a_pointIdx The point to get attached point from.
/// \param[out] a_edgePoints A vector of points attached across edges.
//------------------------------------------------------------------------------
void XmUGrid::Impl::GetPointAdjacentLocations(int a_pointIdx, VecPt3d& a_edgePoints) const
{
  VecInt edgePtIdxs;
  GetPointAdjacentPoints(a_pointIdx, edgePtIdxs);
  a_edgePoints = GetPointsLocations(edgePtIdxs);
} // XmUGrid::Impl::GetPointAdjacentLocations

// Faces
//------------------------------------------------------------------------------
/// \brief Get the number of cell faces for given cell.
/// \param[in] a_cellIdx the index of the cell
/// \return the count of cell faces
//------------------------------------------------------------------------------
int XmUGrid::Impl::GetCell3dFaceCount(int a_cellIdx) const
{
  if (m_useCache)
  {
    CalculateCacheValues();
    int faceCount = IsValidCellIdx(a_cellIdx) ? m_numberOfFaces[a_cellIdx] : -1;
    return faceCount;
  }
  else
  {
    return GetCell3dFaceCountNoCache(a_cellIdx);
  }
} // XmUGrid::Impl::GetCell3dFaceCount

//------------------------------------------------------------------------------
/// \brief Get the number of face points for a given cell and face.
/// \param[in] a_cellIdx The cell
/// \param[in] a_faceIdx The face
/// \return The number of face points or -1 if invalid face or cell index.
//------------------------------------------------------------------------------
int XmUGrid::Impl::GetCell3dFacePointCount(int a_cellIdx, int a_faceIdx) const
{
  if (!IsValidCellIdx(a_cellIdx))
  {
    return -1;
  }

  int cellType = GetCellType(a_cellIdx);
  if (cellType == XMU_POLYHEDRON)
  {
    const int* cellstream;
    int length;
    GetCellCellstream(a_cellIdx, &cellstream, length);
    if (cellstream != nullptr)
    {
      auto currItem = cellstream;
      currItem++; // skip cell type
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
  }
  else
  {
    const VecInt2d& faceTable = iGetFaceOffsetTable(cellType);
    if (a_faceIdx >= 0 && a_faceIdx < (int)faceTable.size())
    {
      return (int)faceTable[a_faceIdx].size();
    }
  }

  return 0;
} // XmUGrid::Impl::GetCell3dFacePointCount

//------------------------------------------------------------------------------
/// \brief Get the cell face for given cell and face index.
/// \param[in] a_cellIdx the index of the cell
/// \param[in] a_faceIdx the face index of the cell
/// \return a vector of point indices for the face index of the cell
//------------------------------------------------------------------------------
VecInt XmUGrid::Impl::GetCell3dFacePoints(int a_cellIdx, int a_faceIdx) const
{
  VecInt facePoints;
  GetCell3dFacePoints(a_cellIdx, a_faceIdx, facePoints);
  return facePoints;
} // XmUGrid::Impl::GetCell3dFacePoints
//------------------------------------------------------------------------------
/// \brief Get the cell face for given cell and face index.
/// \param[in] a_cellIdx the index of the cell
/// \param[in] a_faceIdx the face index of the cell
/// \param[out] a_facePtIdxs a vector of point indices for the face
//------------------------------------------------------------------------------
void XmUGrid::Impl::GetCell3dFacePoints(int a_cellIdx, int a_faceIdx, VecInt& a_facePtIdxs) const
{
  a_facePtIdxs.clear();
  if (a_faceIdx < 0)
  {
    return;
  }

  const int* cellstream = nullptr;
  int streamLength;
  GetCellCellstream(a_cellIdx, &cellstream, streamLength);
  if (!cellstream)
    return;

  int cellType = *cellstream++;
  if (cellType == XMU_POLYHEDRON)
  {
    int numFaces = *cellstream++;
    for (int faceIdx = 0; faceIdx < numFaces; ++faceIdx)
    {
      int numFacePoints = *cellstream++;
      if (faceIdx == a_faceIdx)
      {
        a_facePtIdxs.assign(cellstream, cellstream + numFacePoints);
        break;
      }
      cellstream += numFacePoints;
    }
  }
  else
  {
    const VecInt2d& faceTable = iGetFaceOffsetTable(cellType);
    if (a_faceIdx < (int)faceTable.size())
    {
      if (cellstream)
      {
        const int* cellPoints = ++cellstream;
        const VecInt& faceOffsets = faceTable[a_faceIdx];
        for (auto offset : faceOffsets)
        {
          int idx = cellPoints[offset];
          a_facePtIdxs.push_back(idx);
        }
      }
    }
  }
} // XmUGrid::Impl::GetCell3dFacePoints
//------------------------------------------------------------------------------
/// \brief Get the faces of a cell.
/// \param[in] a_cellIdx the cells to whom the faces belong
/// \return a vector of faces, which is a vector of point indices
//------------------------------------------------------------------------------
VecInt2d XmUGrid::Impl::GetCell3dFacesPoints(int a_cellIdx) const
{
  int numFaces = GetCell3dFaceCount(a_cellIdx);

  VecInt2d faces(numFaces);
  for (int i(0); i < numFaces; i++)
  {
    faces[i] = GetCell3dFacePoints(a_cellIdx, i);
  }
  return faces;
} // XmUGrid::Impl::GetCell3dFacesPoints
//------------------------------------------------------------------------------
/// \brief Get the cell face neighbors for given cell and face index.
/// \param[in] a_cellIdx the index of the cell
/// \param[in] a_faceIdx the face index of the cell
/// \return a cell index of the neighbor
//------------------------------------------------------------------------------
int XmUGrid::Impl::GetCell3dFaceAdjacentCell(int a_cellIdx, int a_faceIdx) const
{
  if (m_useCache)
  {
    CalculateCacheValues();
    int faceNeighbor = -1;
    int numFaces = GetCell3dFaceCount(a_cellIdx);
    if (a_faceIdx >= 0 && a_faceIdx < numFaces)
    {
      int faceOffset = m_cellFaceOffset[a_cellIdx];
      if (faceOffset >= 0)
      {
        faceOffset += a_faceIdx;
        faceNeighbor = m_faceNeighbor[faceOffset];
        if (faceNeighbor == NEEDS_CALCULATION)
        {
          faceNeighbor = GetCell3dFaceAdjacentCellNoCache(a_cellIdx, a_faceIdx);
          m_faceNeighbor[faceOffset] = faceNeighbor;
        }
        else
        {
          faceNeighbor = m_faceNeighbor[faceOffset];
        }
      }
    }
    return faceNeighbor;
  }
  else
  {
    return GetCell3dFaceAdjacentCellNoCache(a_cellIdx, a_faceIdx);
  }
} // XmUGrid::Impl::GetCell3dFaceAdjacentCell
//------------------------------------------------------------------------------
/// \brief Get the cell face neighbors for given cell and face index.
/// \param[in] a_cellIdx the index of the cell
/// \param[in] a_faceIdx the face index of the cell
/// \param[in] a_neighborCell the index of the neighboring cell
/// \param[in] a_neighborFace the face index of the neighboring cell adjacent
///      to the given face
/// \return a cell index of the neighbor
//------------------------------------------------------------------------------
bool XmUGrid::Impl::GetCell3dFaceAdjacentCell(int a_cellIdx,
                                              int a_faceIdx,
                                              int& a_neighborCell,
                                              int& a_neighborFace) const
{
  a_neighborCell = GetCell3dFaceAdjacentCell(a_cellIdx, a_faceIdx);
  if (a_neighborCell < 0)
  {
    a_neighborCell = a_neighborFace = -1;
    return false;
  }
  VecInt cellFacePts = GetCell3dFacePoints(a_cellIdx, a_faceIdx);
  for (int faceIdx(0); faceIdx < GetCell3dFaceCount(a_neighborCell); faceIdx++)
  {
    VecInt curCellFacePts = GetCell3dFacePoints(a_neighborCell, faceIdx);
    if (cellFacePts.size() == curCellFacePts.size())
    {
      int cellFacePtsIdx(0);
      for (; cellFacePtsIdx < (int)cellFacePts.size(); ++cellFacePtsIdx)
      {
        bool found = false;
        for (int curCellFacePt : curCellFacePts)
        {
          if (cellFacePts[cellFacePtsIdx] == curCellFacePt)
          {
            found = true;
            break;
          }
        }
        if (!found)
          break; // This face is not the face we are l.
      }
      if (cellFacePtsIdx == (int)cellFacePts.size()) // Every point is found
      {
        a_neighborFace = faceIdx;
        a_neighborFace = faceIdx;
        return true;
      }
    }
  }
  a_neighborCell = a_neighborFace = -1;
  return false;
} // XmUGrid::Impl::GetCell3dFaceAdjacentCell
//------------------------------------------------------------------------------
/// \brief Get the orientation of the face of a vertically prismatic cell.
/// \param[in] a_cellIdx the index of the cell
/// \param[in] a_faceIdx the face index of the cell
/// \return The orientation of the face (TOP, BOTTOM, SIDE, UNKNOWN).
//------------------------------------------------------------------------------
XmUGridFaceOrientation XmUGrid::Impl::GetCell3dFaceOrientation(int a_cellIdx, int a_faceIdx) const
{
  if (m_useCache)
  {
    CalculateCacheValues();
    int faceOrientation = XMU_ORIENTATION_UNKNOWN;
    int numFaces = GetCell3dFaceCount(a_cellIdx);
    if (a_faceIdx >= 0 && a_faceIdx < numFaces)
    {
      int faceOffset = m_cellFaceOffset[a_cellIdx];
      if (faceOffset >= 0)
      {
        faceOffset += a_faceIdx;
        faceOrientation = m_faceOrientation[faceOffset];
        if (faceOrientation == NEEDS_CALCULATION)
        {
          faceOrientation = (int)GetCell3dFaceOrientationNoCache(a_cellIdx, a_faceIdx);
          m_faceOrientation[faceOffset] = faceOrientation;
        }
        else
        {
          faceOrientation = m_faceOrientation[faceOffset];
        }
      }
    }
    return (XmUGridFaceOrientation)faceOrientation;
  }
  else
  {
    return GetCell3dFaceOrientationNoCache(a_cellIdx, a_faceIdx);
  }
} // XmUGrid::Impl::GetCell3dFaceOrientation
//------------------------------------------------------------------------------
/// \brief Find the orientation of a given 3D cell face.
/// \param[in] a_cellIdx The cell index.
/// \param[in] a_faceIdx The face index.
/// \return The orientation of the face (TOP, BOTTOM, SIDE, UNKNOWN).
//------------------------------------------------------------------------------
XmUGridFaceOrientation XmUGrid::Impl::FaceOrientation(int a_cellIdx, int a_faceIdx) const
{
  XmUGridFaceOrientation orientation = FaceOrientationWithFail(a_cellIdx, a_faceIdx);
  if (orientation == XMU_ORIENTATION_UNKNOWN)
  {
    // Is there any way to know if we reach this point? First face top and next
    // bottom? What about multi-panel top with no cell above?
    // XM_ASSERT(0);
    orientation = VerticalOrientationFromOpposing(a_cellIdx, a_faceIdx);
  }

  XM_ASSERT(orientation != XMU_ORIENTATION_UNKNOWN);
  return orientation;
} // XmUGrid::Impl::FaceOrientation
//------------------------------------------------------------------------------
/// \brief Update internal links to navigate between associated points and
///        cells.
//------------------------------------------------------------------------------
void XmUGrid::Impl::UpdateLinks()
{
  UpdateCellLinks();
  UpdatePointLinks();
} // XmUGrid::Impl::UpdateLinks
//------------------------------------------------------------------------------
/// \brief Update internal link from cells to cell stream index.
//------------------------------------------------------------------------------
void XmUGrid::Impl::UpdateCellLinks()
{
  m_cellIdxToStreamIdx.clear();

  int currIdx = 0;
  if (m_cellstream.empty())
  {
    m_cellIdxToStreamIdx.push_back(currIdx);
    return;
  }

  int numItems = (int)m_cellstream.size();
  while (currIdx < numItems)
  {
    m_cellIdxToStreamIdx.push_back(currIdx);

    // get cell type
    int cellType = m_cellstream[currIdx++];
    if (currIdx >= numItems)
      return;

    // get the number of items
    int numPoints = m_cellstream[currIdx++];
    if (currIdx >= numItems)
      return;

    if (cellType == XMU_POLYHEDRON)
    {
      int numFaces = numPoints;
      for (int faceIdx = 0; faceIdx < numFaces; ++faceIdx)
      {
        int numFacePoints = m_cellstream[currIdx++];
        currIdx += numFacePoints;
      }
    }
    else
    {
      currIdx += numPoints;
    }
  }

  m_cellIdxToStreamIdx.push_back(currIdx);
} // XmUGrid::Impl::UpdateCellLinks
//------------------------------------------------------------------------------
/// \brief Update internal links from points to associated cells.
//------------------------------------------------------------------------------
void XmUGrid::Impl::UpdatePointLinks()
{
  m_pointIdxToPointsToCells.clear();
  m_pointIdxToPointsToCells.resize(m_locations.size(), 0);
  m_pointsToCells.clear();

  // get number of cells for each point
  int numStreamItems = (int)m_cellstream.size();
  int cellIdx = 0;
  int currIdx = 0;
  VecInt pointLastUsedIdx(m_locations.size(), -1);
  VecInt cellPoints;
  while (currIdx < numStreamItems)
  {
    // get cell type
    int cellType = m_cellstream[currIdx++];
    if (currIdx >= numStreamItems)
      return;

    // get the number of items (points or faces depending on cell type)
    int numCellItems = m_cellstream[currIdx++];
    if (currIdx >= numStreamItems)
      return;

    if (cellType == XMU_POLYHEDRON)
    {
      GetUniquePointsFromPolyhedronCellstream(m_cellstream, numCellItems, currIdx, cellPoints,
                                              pointLastUsedIdx);

      // Deemed to be slower than flat set-- Left only as a warning to others!
      // std::stable_sort(cellPoints.begin(), cellPoints.end());
      // auto uniqueEnd = std::unique(cellPoints.begin(), cellPoints.end());

      // flat set deemed to be slower than marking when a point was last used (pointLastUsedIdx)

      // for (auto pt = cellPoints.begin(); pt != uniqueEnd; ++pt)
      for (auto cellPoint : cellPoints)
      {
        m_pointIdxToPointsToCells[cellPoint] += 1;
      }
    }
    else
    {
      // iterate on points
      int numPoints = numCellItems;
      for (int ptIdx = 0; ptIdx < numPoints; ++ptIdx)
      {
        int pt = m_cellstream[currIdx++];
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
  std::fill(pointLastUsedIdx.begin(), pointLastUsedIdx.end(), -1);
  while (currIdx < numStreamItems)
  {
    // get cell type
    int cellType = m_cellstream[currIdx++];
    if (currIdx >= numStreamItems)
      return;

    // get the number of items (points or faces depending on cell type)
    int numCellItems = m_cellstream[currIdx++];
    if (currIdx >= numStreamItems)
      return;

    if (cellType == XMU_POLYHEDRON)
    {
      GetUniquePointsFromPolyhedronCellstream(m_cellstream, numCellItems, currIdx, cellPoints,
                                              pointLastUsedIdx);

      // Deemed to be slower than flat set-- Left only as a warning to others!
      // std::stable_sort(cellPoints.begin(), cellPoints.end());
      // auto uniqueEnd = std::unique(cellPoints.begin(), cellPoints.end());

      // for (auto pt = cellPoints.begin(); pt != uniqueEnd; ++pt)
      for (auto cellPoint : cellPoints)
      {
        int countIdx = m_pointIdxToPointsToCells[cellPoint];
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
        int pt = m_cellstream[currIdx++];
        int countIdx = m_pointIdxToPointsToCells[pt];
        int& count = m_pointsToCells[countIdx]; // point's cell count
        ++count;                                // incrementing point's cell count
        int updateIdx = countIdx + count;
        m_pointsToCells[updateIdx] = cellIdx;
      }
    }

    ++cellIdx;
  }
} // XmUGrid::Impl::UpdatePointLinks
//------------------------------------------------------------------------------
/// \brief Get the dimension given the cell type (0d, 1d, 2d, or 3d).
/// \param[in] a_cellType the cell type
/// \return the dimension of the cell type
//------------------------------------------------------------------------------
int XmUGrid::Impl::DimensionFromCellType(XmUGridCellType a_cellType)
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

} // XmUGrid::Impl::DimensionFromCellType

//------------------------------------------------------------------------------
/// \brief Get number of items given cell. For polyhedron number of items is
///        number of faces. For other cell types it is number of points.
/// \param[in] a_cellIdx the index of the cell
/// \return the number of faces for polyhedron or number of points.
//------------------------------------------------------------------------------
int XmUGrid::Impl::GetNumberOfItemsForCell(int a_cellIdx) const
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
    return m_cellstream[startIndex + 1];
  }
  else
  { // Polyhedron case, same value is number of faces
    int startIndex = m_cellIdxToStreamIdx[a_cellIdx];
    return m_cellstream[startIndex + 1];
  }
} // XmUGrid::Impl::GetNumberOfItemsForCell
//------------------------------------------------------------------------------
/// \brief Internal function to get start of cell stream for an individual cell.
///        Returns nullptr and zero length for invalid cell index.
/// \param[in] a_cellIdx the index of the cell
/// \param[out] a_start pointer to the start of the stream for the cell
/// \param[out] a_length the length of the stream for the cell
//------------------------------------------------------------------------------
void XmUGrid::Impl::GetCellCellstream(int a_cellIdx, const int** a_start, int& a_length) const
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
    *a_start = &m_cellstream[startIndex];
    a_length = nextCellIndex - startIndex;
  }
} // XmUGrid::Impl::GetCellCellstream
//------------------------------------------------------------------------------
/// \brief Get the number of edges for a polyhedron cell.
/// \param[in] a_cellIdx the index of the cell
/// \return the number of edges
//------------------------------------------------------------------------------
int XmUGrid::Impl::GetNumberOfPolyhedronEdges(int a_cellIdx) const
{
  const int* cellstream;
  int streamLength;
  GetCellCellstream(a_cellIdx, &cellstream, streamLength);
  if (cellstream && streamLength > 0 && cellstream[0] == XMU_POLYHEDRON)
  {
    boost::container::flat_set<XmEdge> edges;
    int currItem = 2;
    while (currItem < streamLength)
    {
      GetUniqueEdgesFromPolyhedronCellstream(cellstream, streamLength, edges, currItem);
    }
    return (int)edges.size();
  }
  return 0;
} // XmUGrid::Impl::GetNumberOfPolyhedronEdges
//------------------------------------------------------------------------------
/// \brief Get the unique points in a flat set
/// \param[in] a_cellstream the UGrid cell stream
/// \param[in] a_numCellItems the number of cell faces in the polyhedron
/// \param[in] a_currIdx the index of the cell stream; this should reference
///       the number of points in the first face. This variable will be updated
///       to the cell type of the next cell.
/// \param[out] a_uniqueGetCellPoints the unique points of the polyhedron
/// \param[out] a_pointLastUsedIdx a list of integers representing when a point
///  was last found while reading the stream.
/// \note: This function does NOT verify cellstream size!!  This function
///      needs to be efficient!
//------------------------------------------------------------------------------
void XmUGrid::Impl::GetUniquePointsFromPolyhedronCellstream(const VecInt& a_cellstream,
                                                            int a_numCellItems,
                                                            int& a_currIdx,
                                                            VecInt& a_uniqueGetCellPoints,
                                                            VecInt& a_pointLastUsedIdx)
{
  int stable = a_currIdx;
  a_uniqueGetCellPoints.clear();
  int numFaces = a_numCellItems;
  for (int faceIdx = 0; faceIdx < numFaces; ++faceIdx)
  {
    int numFacePoints = a_cellstream[a_currIdx++];
    for (int ptIdx = 0; ptIdx < numFacePoints; ++ptIdx)
    {
      int pt = a_cellstream[a_currIdx++];
      if (a_pointLastUsedIdx[pt] < stable)
      {
        a_pointLastUsedIdx[pt] = stable;
        a_uniqueGetCellPoints.push_back(pt);
      }
    }
  }
} // XmUGrid::Impl::GetUniquePointsFromPolyhedronCellstream
//------------------------------------------------------------------------------
/// \brief Get the unique points for cell stream of a single polyhedron cell.
/// \param[in] a_cellstream a single cell stream that is a polyhedron type
/// \param[out] a_cellPoints the points of the cell
/// \return false if invalid stream
//------------------------------------------------------------------------------
bool XmUGrid::Impl::GetUniquePointsFromPolyhedronSingleCellstream(const VecInt& a_cellstream,
                                                                  VecInt& a_cellPoints)
{
  a_cellPoints.clear();
  if (a_cellstream.size() < 2)
  {
    return false;
  }

  auto currItem = a_cellstream.begin();
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
} // XmUGrid::Impl::GetUniquePointsFromPolyhedronSingleCellstream
//------------------------------------------------------------------------------
/// \brief Get the unique edges in a flat set for a given polyhedron
/// \param[in] a_start the UGrid cell stream (integer pointer)
/// \param[in] a_length the length of the cell stream
/// \param[in] a_cellEdges Unique cell edges of the polyhedron
/// \param[in] a_currIdx the index of the cell stream; this should reference
///       the number of points in the first face. This variable will be updated
///       to the cell type of the next cell.
/// \note: This function does NOT verify cellstream size!!  This function
///      needs to be efficient!
//------------------------------------------------------------------------------
void XmUGrid::Impl::GetUniqueEdgesFromPolyhedronCellstream(
  const int* a_start,
  int& a_length,
  boost::container::flat_set<XmEdge>& a_cellEdges,
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
        a_cellEdges.insert(XmEdge(pt1, pt2));
      else
        a_cellEdges.insert(XmEdge(pt2, pt1));
    }
    a_currIdx += numPoints;
  }
} // XmUGrid::Impl::GetUniqueEdgesFromPolyhedronCellstream
//------------------------------------------------------------------------------
/// \brief Get a plan view polygon of a specified 2D cell
/// \param[in] a_cellIdx the index of the cell
/// \param[out] a_polygon vector of Pt3d that is the plan view polygon
/// \return whether the operation was successful
//------------------------------------------------------------------------------
bool XmUGrid::Impl::GetPlanViewPolygon2d(int a_cellIdx, VecPt3d& a_polygon) const
{
  GetCellLocations(a_cellIdx, a_polygon);
  if (!a_polygon.empty())
  {
    return true;
  }
  return false;
} // XmUGrid::Impl::GetPlanViewPolygon2d
//------------------------------------------------------------------------------
/// \brief Get a plan view polygon of a specified 3D cell
/// \param[in] a_cellIdx the index of the cell
/// \param[out] a_polygon vector of Pt3d that is the plan view polygon
/// \return whether the operation was successful
//------------------------------------------------------------------------------
bool XmUGrid::Impl::GetPlanViewPolygon3d(int a_cellIdx, VecPt3d& a_polygon) const
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
    VecInt uniquePoints = GetCellPoints(a_cellIdx);
    VecPt3d cellPoints(uniquePoints.size());
    for (int i(0); i < uniquePoints.size(); i++)
    {
      cellPoints[i] = GetPointLocation(uniquePoints[i]);
      cellPoints[i].z = 0.0; // Insist that our z values are 0.0 for plan view
    }
    gmGetConvexHull(cellPoints, a_polygon, false);
    return true;
  }
  return false;
} // XmUGrid::Impl::GetPlanViewPolygon3d
//------------------------------------------------------------------------------
/// \brief Get whether the cell face is of a side orientation. Only works for
///        plan view prismatic cells.
/// \param[in] a_facePts the points in the face
/// \return whether the face is a Side
//------------------------------------------------------------------------------
bool XmUGrid::Impl::IsFaceSide(const VecInt& a_facePts) const
{
  // if any face point has same x and y as any other face point then
  // the face is a side face
  if (a_facePts.size() > 2)
  {
    Pt3d ptLast = GetPointLocation(a_facePts[0]);
    for (size_t facePtIdx = 1; facePtIdx < a_facePts.size(); ++facePtIdx)
    {
      Pt3d ptCurr = GetPointLocation(a_facePts[facePtIdx]);
      if ((ptLast.x == ptCurr.x) && (ptLast.y == ptCurr.y))
        return true;

      ptLast = ptCurr;
    }
  }
  return false;
} // XmUGrid::Impl::IsFaceSide
//------------------------------------------------------------------------------
/// \brief Get the XY segments of a cell.
/// \param[in] a_cellIdx the index of the cell
/// \param[out] a_segments The XY segments of a cell
/// \return whether the collected segments form a valid polygon
//------------------------------------------------------------------------------
bool XmUGrid::Impl::GetCellXySegments(int a_cellIdx, VecPt3d& a_segments) const
{
  bool foundSideFace = false;
  for (int faceIdx = 0; faceIdx < GetCell3dFaceCount(a_cellIdx); ++faceIdx)
  {
    VecInt ptIdxs = GetCell3dFacePoints(a_cellIdx, faceIdx);
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
} // XmUGrid::Impl::GetCellXySegments

//------------------------------------------------------------------------------
/// \brief Function to get the extents from a list of points.
/// \param[in] a_locations The point locations to get the extents of.
/// \param[out] a_min Minimum point location.
/// \param[out] a_max Maximum point location.
//------------------------------------------------------------------------------
void XmUGrid::Impl::GetExtentsFromPoints(const VecPt3d& a_locations, Pt3d& a_min, Pt3d& a_max) const
{
  a_min.x = a_min.y = a_min.z = xms::XM_DBL_HIGHEST;
  a_max.x = a_max.y = a_max.z = xms::XM_DBL_LOWEST;
  for (const Pt3d& pt : a_locations)
  {
    gmAddToExtents(pt, a_min, a_max);
  }
} // XmUGrid::Impl::GetExtentsFromPoints

//------------------------------------------------------------------------------
/// \brief Get the Xy locations of Face Points
/// \param[in] a_cellIdx The index of the cells whose face points are wanted.
/// \param[in] a_faceIdx The index of the face whose points are wanted.
/// \param[out] a_segments The points of the face segments
/// \return true if successful.
//------------------------------------------------------------------------------
bool XmUGrid::Impl::GetFaceXySegments(int a_cellIdx, int a_faceIdx, VecPt3d& a_segments) const
{
  VecInt facePts;
  GetCell3dFacePoints(a_cellIdx, a_faceIdx, facePts);
  if (facePts.empty())
    return false;

  int column1Begin, column1End;
  if (!GetNextFaceColumn(facePts, 0, column1Begin, column1End))
    return false;

  int column2Begin, column2End;
  if (!GetNextFaceColumn(facePts, column1End, column2Begin, column2End))
    return false;

  GetFacePointSegments(facePts, column1End, column2Begin, a_segments);
  GetFacePointSegments(facePts, column2End, column1Begin, a_segments);
  return true;
} // XmUGrid::Impl::GetFaceXySegments
//------------------------------------------------------------------------------
/// \brief Calculate cached values for faster lookup.
//------------------------------------------------------------------------------
void XmUGrid::Impl::CalculateCacheValues() const
{
  if (m_numberOfFaces.empty() && GetCellCount() != 0)
  {
    int cellCount = GetCellCount();
    m_numberOfFaces.assign(cellCount, 0);
    m_cellFaceOffset.assign(cellCount + 1, 0);
    int faceCount = 0;
    for (int cellIdx = 0; cellIdx < cellCount; ++cellIdx)
    {
      int numberOfFaces = GetCell3dFaceCountNoCache(cellIdx);
      m_numberOfFaces[cellIdx] = numberOfFaces;
      faceCount += numberOfFaces;
      m_cellFaceOffset[cellIdx + 1] = faceCount;
    }

    m_faceOrientation.assign(faceCount, NEEDS_CALCULATION);
    m_faceNeighbor.assign(faceCount, NEEDS_CALCULATION);
  }
} // XmUGrid::Impl::CalculateCacheValues
//------------------------------------------------------------------------------
/// \brief Clear cached so they will be recalculated.
//------------------------------------------------------------------------------
void XmUGrid::Impl::ClearCacheValues()
{
  m_numberOfFaces.clear();
  m_cellFaceOffset.clear();
  m_faceOrientation.clear();
  m_faceNeighbor.clear();
  m_cellDimensionCounts.clear();
} // XmUGrid::Impl::ClearCacheValues
//------------------------------------------------------------------------------
/// \brief Get the number of cell faces for given cell.
/// \param[in] a_cellIdx the index of the cell
/// \return the count of cell faces
//------------------------------------------------------------------------------
int XmUGrid::Impl::GetCell3dFaceCountNoCache(int a_cellIdx) const
{
  if (!IsValidCellIdx(a_cellIdx))
    return -1;

  int cellType(GetCellType(a_cellIdx));
  if (cellType == XMU_POLYHEDRON)
  {
    return GetNumberOfItemsForCell(a_cellIdx);
  }

  const VecInt2d& faceTable = iGetFaceOffsetTable(cellType);
  return (int)faceTable.size();
} // XmUGrid::Impl::GetCell3dFaceCountNoCache
//------------------------------------------------------------------------------
/// \brief Get the cell face neighbors for given cell and face index.
/// \param[in] a_cellIdx the index of the cell
/// \param[in] a_faceIdx the face index of the cell
/// \return a cell index of the neighbor
//------------------------------------------------------------------------------
int XmUGrid::Impl::GetCell3dFaceAdjacentCellNoCache(int a_cellIdx, int a_faceIdx) const
{
  VecInt cellFace = GetCell3dFacePoints(a_cellIdx, a_faceIdx);
  if (cellFace.empty())
    return -1;
  VecInt neighborCellFace = GetPointsAdjacentCells(cellFace);
  if (neighborCellFace.size() <= 1)
    return -1;
  if (neighborCellFace.size() > 2)
  {
    assert("Cell definitions are invalid; more than 2 cells found sharing the same face.");
  }
  for (int i : neighborCellFace)
  {
    if (i != a_cellIdx)
    {
      return i;
    }
  }
  return -1;
} // XmUGrid::Impl::GetCell3dFaceAdjacentCellNoCache
//------------------------------------------------------------------------------
/// \brief Get the orientation of the face of a vertically prismatic cell.
/// \param[in] a_cellIdx the index of the cell
/// \param[in] a_faceIdx the face index of the cell
/// \return The orientation of the face (TOP, BOTTOM, SIDE, UNKNOWN).
//------------------------------------------------------------------------------
XmUGridFaceOrientation XmUGrid::Impl::GetCell3dFaceOrientationNoCache(int a_cellIdx,
                                                                      int a_faceIdx) const
{
  XmUGridFaceOrientation faceOrientation = FaceOrientation(a_cellIdx, a_faceIdx);
  return faceOrientation;
} // XmUGrid::Impl::GetCell3dFaceOrientationNoCache
//------------------------------------------------------------------------------
/// \brief Get next vertical column of points with equal x/y values for side
/// face.
/// \param[in] a_facePoints The face point indices.
/// \param[in] a_starti The starting index into a_facePoints.
/// \param[out] a_columnBegin The first index of the column of points.
/// \param[out] a_columnEnd The last index of the column of points.
/// \return True if succeeded in getting next face column.
//------------------------------------------------------------------------------
bool XmUGrid::Impl::GetNextFaceColumn(const VecInt& a_facePoints,
                                      int a_starti,
                                      int& a_columnBegin,
                                      int& a_columnEnd) const
{
  int facePointsSize = (int)a_facePoints.size();

  // find next start of column of points (matching x/y values)
  Pt3d lastPt = GetPointXy0(a_facePoints[a_starti]);
  int lasti = a_starti;
  int i = (a_starti + 1) % facePointsSize;
  Pt3d pt;
  bool found = false;
  while (!found && i != a_starti)
  {
    pt = GetPointXy0(a_facePoints[i]);
    if (pt == lastPt)
    {
      a_columnBegin = lasti;
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
  while (!found && i != a_columnBegin)
  {
    pt = GetPointXy0(a_facePoints[i]);
    if (pt != lastPt)
    {
      a_columnEnd = lasti;
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
} // XmUGrid::Impl::GetNextFaceColumn

//------------------------------------------------------------------------------
/// \brief Get plan view segments of face points.
/// \param[in] a_facePts The face point indices.
/// \param[in] a_columnBegin The the first point of a vertical column.
/// \param[in] a_columnEnd The last point of a vertical column.
/// \param[out] a_segments The face point segments.
//------------------------------------------------------------------------------
void XmUGrid::Impl::GetFacePointSegments(const VecInt& a_facePts,
                                         int a_columnBegin,
                                         int a_columnEnd,
                                         VecPt3d& a_segments) const
{
  int i = a_columnBegin;
  while (i != a_columnEnd)
  {
    Pt3d p = GetPointXy0(a_facePts[i]);
    a_segments.push_back(p);
    if (i != a_columnBegin)
      a_segments.push_back(p);
    i = (i + 1) % (int)a_facePts.size();
  }
  a_segments.push_back(GetPointXy0(a_facePts[i]));
} // XmUGrid::Impl::GetFacePointSegments
//------------------------------------------------------------------------------
/// \brief Find the orientation of a given 3D cell face. Check first for side
/// face, then top or bottom based on connected face, or top or bottom based on
/// area calculation.
/// \param[in] a_cellIdx The cell index.
/// \param[in] a_faceIdx The face index.
/// \return The orientation of the face (TOP, BOTTOM, SIDE, UNKNOWN).
//------------------------------------------------------------------------------
XmUGridFaceOrientation XmUGrid::Impl::FaceOrientationWithFail(int a_cellIdx, int a_faceIdx) const
{
  // if first face point has same x and y as any other face point then
  // the face is a side face
  if (IsSideFace(a_cellIdx, a_faceIdx))
    return XMU_ORIENTATION_SIDE;

  // else if face connected to cell lower idx cell then top face
  // else if face connected to cell higher idx cell then bottom face
  XmUGridFaceOrientation orientation = ConnectedTopOrBottom(a_cellIdx, a_faceIdx);
  if (orientation != XMU_ORIENTATION_UNKNOWN)
    return orientation;

  // else use sign of area to determine up or down
  orientation = GetOrientationFromArea(a_cellIdx, a_faceIdx);
  if (orientation != XMU_ORIENTATION_UNKNOWN)
    return orientation;

  return XMU_ORIENTATION_UNKNOWN;
} // XmUGrid::Impl::FaceOrientationWithFail
//------------------------------------------------------------------------------
/// \brief Find vertical orientation of a given 3D cell face from opposing face.
/// \param[in] a_cellIdx The cell index.
/// \param[in] a_faceIdx The face index.
/// \return The orientation of the face (TOP, BOTTOM, UNKNOWN).
//------------------------------------------------------------------------------
XmUGridFaceOrientation XmUGrid::Impl::VerticalOrientationFromOpposing(int a_cellIdx,
                                                                      int a_faceIdx) const
{
  XmUGridFaceOrientation orientation = XMU_ORIENTATION_UNKNOWN;

  // Assume only 1 top and bottom.  Find other face that's top or bottom and
  // give answer as opposite.  Otherwise first top other is bottom.
  bool firstUnknown = false;
  bool foundTop = false;
  bool foundBot = false;
  for (int face = 0; face < GetCell3dFaceCount(a_cellIdx); ++face)
  {
    int orientation = FaceOrientationWithFail(a_cellIdx, face);
    if (orientation == XMU_ORIENTATION_UNKNOWN)
    {
      if (a_faceIdx == face)
        firstUnknown = true;
    }
    else if (orientation == XMU_ORIENTATION_TOP)
      foundTop = true;
    else if (orientation == XMU_ORIENTATION_BOTTOM)
      foundBot = true;
  }

  if (foundTop)
    orientation = XMU_ORIENTATION_BOTTOM;
  else if (foundBot)
    orientation = XMU_ORIENTATION_TOP;
  else if (firstUnknown)
    orientation = XMU_ORIENTATION_TOP;
  else
    orientation = XMU_ORIENTATION_BOTTOM;
  return orientation;
} // XmUGrid::Impl::VerticalOrientationFromOpposing
//------------------------------------------------------------------------------
/// \brief Determines if a cell face is a vertical side face.
/// \param[in] a_cellIdx The cell index.
/// \param[in] a_faceIdx The face index.
/// \return True if the face is a vertical side face (points with same X and Y).
//------------------------------------------------------------------------------
bool XmUGrid::Impl::IsSideFace(int a_cellIdx, int a_faceIdx) const
{
  VecInt facePts;
  GetCell3dFacePoints(a_cellIdx, a_faceIdx, facePts);

  // if any two successive face points have same x and y then
  // the face is a side face
  if (!facePts.empty())
  {
    Pt3d ptLast = GetPointXy0(facePts.back());
    for (size_t facePtIdx = 0; facePtIdx < facePts.size(); ++facePtIdx)
    {
      Pt3d ptCurr = GetPointXy0(facePts[facePtIdx]);
      if (ptLast == ptCurr)
        return true;

      ptLast = ptCurr;
    }
  }

  return false;
} // XmUGrid::Impl::IsSideFace
//------------------------------------------------------------------------------
/// \brief Determine face orientation by using cell index of connected face.
/// Top face is connected to lower index, bottom face to higher index.
/// \param[in] a_cellIdx The cell index.
/// \param[in] a_faceIdx The face index.
/// \return The orientation of the face (TOP, BOTTOM, UNKNOWN).
//------------------------------------------------------------------------------
XmUGridFaceOrientation XmUGrid::Impl::ConnectedTopOrBottom(int a_cellIdx, int a_faceIdx) const
{
  if (m_cellOrder == XMU_CELL_ORDER_UNKNOWN)
    return XMU_ORIENTATION_UNKNOWN;

  int adjacentCellIdx = GetCell3dFaceAdjacentCell(a_cellIdx, a_faceIdx);
  if (adjacentCellIdx != XM_NONE && adjacentCellIdx < a_cellIdx)
  {
    if (m_cellOrder == XMU_CELL_ORDER_INCREASING_DOWN)
      return XMU_ORIENTATION_TOP;
    else if (m_cellOrder == XMU_CELL_ORDER_INCREASING_UP)
      return XMU_ORIENTATION_BOTTOM;
  }
  else if (adjacentCellIdx != XM_NONE && adjacentCellIdx > a_cellIdx)
  {
    if (m_cellOrder == XMU_CELL_ORDER_INCREASING_DOWN)
      return XMU_ORIENTATION_BOTTOM;
    else if (m_cellOrder == XMU_CELL_ORDER_INCREASING_UP)
      return XMU_ORIENTATION_TOP;
  }
  return XMU_ORIENTATION_UNKNOWN;
} // ConnectedTopOrBottom
//------------------------------------------------------------------------------
/// \brief Determine top or bottom face orientation using area. Since faces are
/// ordered CCW looking in, the top face area is positive and the bottom
/// negative.
/// \param[in] a_cellIdx The cell index.
/// \param[in] a_faceIdx The face index.
/// \return The orientation of the face (TOP, BOTTOM, UNKNOWN).
//------------------------------------------------------------------------------
XmUGridFaceOrientation XmUGrid::Impl::GetOrientationFromArea(int a_cellIdx, int a_faceIdx) const
{
  VecInt facePtIdxs;
  GetCell3dFacePoints(a_cellIdx, a_faceIdx, facePtIdxs);
  VecPt3d facePts;
  for (int facePtIdx : facePtIdxs)
    facePts.push_back(GetPointXy0(facePtIdx));
  double area = gmPolygonArea(&facePts[0], facePts.size());
  if (area > 0.0)
    return XMU_ORIENTATION_TOP;
  else if (area < 0.0)
    return XMU_ORIENTATION_BOTTOM;
  return XMU_ORIENTATION_UNKNOWN;
} // XmUGrid::Impl::GetOrientationFromArea
//------------------------------------------------------------------------------
/// \brief Returns the cell order of the UGrid.
/// \return The order of the UGrid.
//------------------------------------------------------------------------------
XmUGridCellOrder XmUGrid::Impl::GetCellOrder() const
{
  return m_cellOrder;
} // XmUGrid::Impl::GetCellOrder
//------------------------------------------------------------------------------
/// \brief Set the cell order for the grid.
/// \param a_cellOrder[in] The cell order.
//------------------------------------------------------------------------------
void XmUGrid::Impl::SetCellOrder(XmUGridCellOrder a_cellOrder)
{
  m_cellOrder = a_cellOrder;
  if (m_useCache)
  {
    m_faceOrientation.assign(m_faceNeighbor.size(), NEEDS_CALCULATION);
  }
} // XmUGrid::Impl::SetCellOrder
//------------------------------------------------------------------------------
/// \brief Calculate the cell order of the UGrid.
/// \return The cell order if able to find the order.
//------------------------------------------------------------------------------
XmUGridCellOrder XmUGrid::Impl::CalculateCellOrder() const
{
  int cellCount = GetCellCount();
  XmUGridCellOrder order = XMU_CELL_ORDER_UNKNOWN;
  struct CellOrderTable
  {
    XmUGridFaceOrientation orientation;
    int direction;
    XmUGridCellOrder goodOrder;
  };
  enum { LESS = -1, EQUAL = 0, GREATER = 1 };
  std::vector<CellOrderTable> orderTable = {
    {XMU_ORIENTATION_TOP, LESS, XMU_CELL_ORDER_INCREASING_DOWN},
    {XMU_ORIENTATION_TOP, GREATER, XMU_CELL_ORDER_INCREASING_UP},
    {XMU_ORIENTATION_BOTTOM, GREATER, XMU_CELL_ORDER_INCREASING_DOWN},
    {XMU_ORIENTATION_BOTTOM, LESS, XMU_CELL_ORDER_INCREASING_UP}};
  for (int cellIdx = 0; cellIdx < cellCount; ++cellIdx)
  {
    int faceCount = GetCell3dFaceCount(cellIdx);
    for (int faceIdx = 0; faceIdx < faceCount; ++faceIdx)
    {
      XmUGridFaceOrientation orientation = GetCell3dFaceOrientation(cellIdx, faceIdx);
      if (orientation == XMU_ORIENTATION_TOP || orientation == XMU_ORIENTATION_BOTTOM)
      {
        int adjacentCellIdx = GetCell3dFaceAdjacentCell(cellIdx, faceIdx);
        if (adjacentCellIdx >= 0)
        {
          int direction = adjacentCellIdx - cellIdx;
          if (direction < 0)
            direction = LESS;
          else if (direction > 0)
            direction = GREATER;

          for (const auto& orderItem : orderTable)
          {
            if (orientation == orderItem.orientation)
            {
              if (direction == orderItem.direction)
              {
                if (order == XMU_CELL_ORDER_UNKNOWN)
                {
                  // set order on first found top/bottom direction
                  order = orderItem.goodOrder;
                  break;
                }
                else if (order != orderItem.goodOrder)
                {
                  return XMU_CELL_ORDER_UNKNOWN;
                }
              }
            }
          }
        }
      }
    }
  }
  return order;
} // XmUGrid::Impl::CalculateCellOrder

////////////////////////////////////////////////////////////////////////////////
/// \class XmUGrid
/// \brief Geometry for an unstructured grid.
/// An XmUGrid is defined as a vector of 3d points and a stream of cells.
/// Throughout this interface, we use these terms:
///
/// Point or pointIdx refer to an index into the vector of points.
///
/// Location refers to the actual 3d coordinates of one or more of those points.
///
/// GetCellstream refers to a single flat vector of integers that defines the cells.
/// The cellstream for each cell begins with an integer that defines the cell
/// type.  For most cell types, the next integer specifies the number of points
/// in the cell (even though that number never varies for all cells of most
/// types). That is followed by the indices for that number of points.
/// One of the cell types is a polyhedron.  It follows the cell type with a
/// count of the faces in the polyhedron.  Then for that number of faces, each
/// face is defined by a number of points (ordered counter-clockwise from the
/// outside), followed by that many point indices.
///
/// Cell or CellIdx refers to the n-th cell defined in the cell stream.
/// Internally, such an value is used to index into a secondary vector that
/// defines the offsets into the cellstream where that cell begins and ends.
///
/// Edge refers to a simple structure that contains a pair of indices to points
/// that are connected by at least one cell's points.
///
/// EdgeIdx refers to a particular ordering of the edges of a cell.  For each
/// cell type, there is a predefined way of connecting the points of cells of
/// that type to form an Edge.  The EdgeIdx is a convenient way to loop through
/// that set of edges on a cell without actually collecting them into a vector.
///
/// Dimension refers to the kinds of connectivity a cell type will have. Cells
/// that represent a single point have dimension 0.  Those that connect into a
/// curve have dimension 1.  Those that connect to form a surface have
/// dimension 2.  Those that represent solids have dimension 3. (All of these
/// cell types can exist in 3 dimensional space.)
///
/// Functions that just have one word, like GetLocations(), GetCellstream(),
/// or GetExtents() return properties of the entire XmUGrid.
/// Those that return properties of a particular cell will begin with the word
/// "Cell" (and have a_cellIdx as their first argument) and end with type of
/// related objects.  For example: GetCellPoints(), GetCellLocations(), GetCellType(),
/// GetCellDimension(), GetCellAdjacentCells(), etc.
///
/// Functions that begin with "Point" have a_pointIdx as their first argument
/// return objects relative to that point, such GetPointLocation(), GetPointXy0(),
/// GetPointAdjacentCells(), etc.  (One could expect a function like PointEdges()
/// or GetPointAdjacentPoints() to take a_pointIdx as the first argument return
/// a vector of Edges or PointIdxs that connect to that point.)
///
/// Functions that return the number of objects in some scope end with the word
/// "Count" preceded by the type of things being counted and optionally a
/// scope. So GetPointCount() and GetCellCount() return the number of points and
/// cells respectively in the XmUGrid, while GetCellPointCount() and
/// GetCellEdgeCount() return the number of points or edges, respectively, in a
/// specified cell.
///
/// There is a predefined ordering of faces within the solid cell types, so
/// faceIdx refers to the face in that ordering. Methods containing the words
/// Cell3d or Face are specific to solids (dimension 3 cells).
///
/// Some functions begin with two scoping words and take two input index
/// arguments; for example: GetCellEdgeAdjacentCells() or GetCell3dFacePoints().
////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
/// \brief Create a new XmUGrid.
/// \return the new XmUGrid.
//------------------------------------------------------------------------------
std::shared_ptr<XmUGrid> XmUGrid::New()
{
  std::shared_ptr<XmUGrid> ugrid(new XmUGrid());
  return ugrid;
} // XmUGrid::New
//------------------------------------------------------------------------------
/// \brief Create a new XmUGrid.
/// \param[in] a_locations the UGrid points
/// \param[in] a_cellstream the UGrid cell stream
/// \return the new XmUGrid.
//------------------------------------------------------------------------------
std::shared_ptr<XmUGrid> XmUGrid::New(const VecPt3d& a_locations, const VecInt& a_cellstream)
{
  std::shared_ptr<XmUGrid> ugrid = XmUGrid::New();
  ugrid->SetLocations(a_locations);
  bool valid = ugrid->SetCellstream(a_cellstream);
  if (valid)
  {
    return ugrid;
  }
  else
  {
    return nullptr;
  }
} // XmUGrid::New
//------------------------------------------------------------------------------
/// \brief Constructor
//------------------------------------------------------------------------------
XmUGrid::XmUGrid()
: m_impl(new Impl)
{
} // XmUGrid::XmUGrid
//------------------------------------------------------------------------------
/// \brief Copy constructor.
/// \param a_xmUGrid The XmUGrid to copy.
//------------------------------------------------------------------------------
XmUGrid::XmUGrid(const XmUGrid& a_xmUGrid)
: m_impl(new Impl)
{
  *m_impl = *a_xmUGrid.m_impl;
} // XmUGrid::XmUGrid
//------------------------------------------------------------------------------
/// \brief Move constructor.
/// \param a_xmUGrid The XmUGrid to move.
//------------------------------------------------------------------------------
XmUGrid::XmUGrid(XmUGrid&& a_xmUGrid)
: XmUGrid()
{
  Swap(a_xmUGrid);
} // XmUGrid::XmUGrid
//------------------------------------------------------------------------------
/// \brief Destructor
//------------------------------------------------------------------------------
XmUGrid::~XmUGrid()
{
} // XmUGrid::~XmUGrid
//------------------------------------------------------------------------------
/// \brief Assignment operator.
/// \param a_xmUGrid The XmUGrid to copy from.
/// \return The reference to this.
//------------------------------------------------------------------------------
XmUGrid& XmUGrid::operator=(XmUGrid a_xmUGrid)
{
  Swap(a_xmUGrid);
  return *this;
} // XmUGrid::operator=
//------------------------------------------------------------------------------
/// \brief Swap data between two XmUGrids.
/// \param a_xmUGrid The other XmUGrid.
//------------------------------------------------------------------------------
void XmUGrid::Swap(XmUGrid& a_xmUGrid)
{
  std::swap(m_impl, a_xmUGrid.m_impl);
} // XmUGrid::Swap
//------------------------------------------------------------------------------
/// \brief Check a cell stream to make sure it's valid. Compares cell type
///        against expected number of points. Also ensures cells only refer to
///        valid points.
/// \param[in] a_cellstream the cell stream to check
/// \param a_points: The number of points in this grid. Used to ensure the cells
///                  only refer to valid points.
/// \return Whether the cell stream is valid.
//------------------------------------------------------------------------------
bool XmUGrid::IsValidCellstream(const VecInt& a_cellstream, int a_points)
{
  if (a_cellstream.empty())
  {
    return true;
  }

  int currIdx = 0;
  while (currIdx < a_cellstream.size())
  {
    int step = iValidateCell(a_cellstream, a_points, currIdx);
    if (step == BAD_CELL_STREAM)
    {
      return false;
    }
    else
    {
      currIdx += step;
    }
  }

  return true;
} // XmUGrid::IsValidCellstream

//------------------------------------------------------------------------------
/// \brief Check a cell stream to make sure it's valid. Compares cell type
///        against expected number of points.
///        ***Does not check if cells refer to valid points.***
/// \param[in] a_cellstream the cell stream to check
/// \return Whether the cell stream is valid.
//------------------------------------------------------------------------------
bool XmUGrid::IsValidCellstream(const VecInt& a_cellstream)
{
  return IsValidCellstream(a_cellstream, std::numeric_limits<int>::max());
} // XmUGrid::IsValidCellstream

//------------------------------------------------------------------------------
/// \brief Returns the modified flag. Gets set when points or cells get changed.
/// \return the modified flag
//------------------------------------------------------------------------------
bool XmUGrid::GetModified() const
{
  return m_impl->GetModified();
} // XmUGrid::GetModified

//------------------------------------------------------------------------------
/// \brief Resets the modified flag to false.
//------------------------------------------------------------------------------
void XmUGrid::SetUnmodified()
{
  m_impl->SetUnmodified();
} // XmUGrid::SetUnmodified

//------------------------------------------------------------------------------
/// \brief Turn on or off use of caching to speed up some operations.
/// \param a_useCache Flag to determine if caching will be used.
//------------------------------------------------------------------------------
void XmUGrid::SetUseCache(bool a_useCache)
{
  m_impl->SetUseCache(a_useCache);
} // XmUGrid::SetUseCache

// Points

//------------------------------------------------------------------------------
/// \brief Get the number of points.
/// \return the number of points
//------------------------------------------------------------------------------
int XmUGrid::GetPointCount() const
{
  return m_impl->GetPointCount();
} // XmUGrid::GetPointCount

//------------------------------------------------------------------------------
/// \brief Get vector of UGrid points.
/// \return a vector of point locations
//------------------------------------------------------------------------------
const VecPt3d& XmUGrid::GetLocations() const
{
  return m_impl->GetLocations();
} // XmUGrid::GetLocations

//------------------------------------------------------------------------------
/// \brief Set UGrid points.
/// \param[in] a_locations vector of point locations
//------------------------------------------------------------------------------
void XmUGrid::SetLocations(const VecPt3d& a_locations)
{
  m_impl->SetLocations(a_locations);
} // XmUGrid::SetLocations

//------------------------------------------------------------------------------
/// \brief Get the point
/// \param[in] a_pointIdx the index of the point
/// \return the point or an initialize point if the index is invalid
//------------------------------------------------------------------------------
Pt3d XmUGrid::GetPointLocation(int a_pointIdx) const
{
  return m_impl->GetPointLocation(a_pointIdx);
} // XmUGrid::GetPointLocation

//------------------------------------------------------------------------------
/// \brief Set the point
/// \param[in] a_pointIdx the index of the point
/// \param[in] a_location The new location of the specified point
/// \return whether the point was successfully set
//------------------------------------------------------------------------------
bool XmUGrid::SetPointLocation(int a_pointIdx, const Pt3d& a_location)
{
  return m_impl->SetPointLocation(a_pointIdx, a_location);
} // XmUGrid::SetPointLocation

//------------------------------------------------------------------------------
/// \brief Get the X, Y location of a point.
/// \param[in] a_pointIdx The index of the point.
/// \return The location of the point with Z set to 0.0.
//------------------------------------------------------------------------------
Pt3d XmUGrid::GetPointXy0(int a_pointIdx) const
{
  return m_impl->GetPointXy0(a_pointIdx);
} // XmUGrid::GetPointXy0

//------------------------------------------------------------------------------
/// \brief Convert a vector of point indices into a vector of point 3d
/// \param[in] a_points a vector of point indices
/// \return vector of point 3d
//------------------------------------------------------------------------------
VecPt3d XmUGrid::GetPointsLocations(const VecInt& a_points) const
{
  return m_impl->GetPointsLocations(a_points);
} // XmUGrid::GetPointsLocations

//------------------------------------------------------------------------------
/// \brief Get extents of all points in UGrid
/// \param[out] a_min minimum extent of all points
/// \param[out] a_max maximum extent of all points
//------------------------------------------------------------------------------
void XmUGrid::GetExtents(Pt3d& a_min, Pt3d& a_max) const
{
  m_impl->GetExtents(a_min, a_max);
} // XmUGrid::GetExtents

//------------------------------------------------------------------------------
/// \brief Get the number of cells that use a point.
/// \param a_pointIdx The point to check.
/// \return The number of cells that use the point.
//------------------------------------------------------------------------------
int XmUGrid::GetPointAdjacentCellCount(int a_pointIdx) const
{
  return m_impl->GetPointAdjacentCellCount(a_pointIdx);
} // XmUGrid::GetPointAdjacentCellCount

//------------------------------------------------------------------------------
/// \brief Get the cells that are associated with the specified point
/// \param[in] a_pointIdx the index of the point
/// \return a vector of the cell indices associated with this point
//------------------------------------------------------------------------------
VecInt XmUGrid::GetPointAdjacentCells(int a_pointIdx) const
{
  return m_impl->GetPointAdjacentCells(a_pointIdx);
} // XmUGrid::GetPointAdjacentCells

//------------------------------------------------------------------------------
/// \brief Get the cells that are associated with the specified point
/// \param[in] a_pointIdx the index of the point
/// \param[out] a_adjacentCells a vector of the adjacent cell indices
/// \return a vector of the cell indices associated with this point
//------------------------------------------------------------------------------
void XmUGrid::GetPointAdjacentCells(int a_pointIdx, VecInt& a_adjacentCells) const
{
  m_impl->GetPointAdjacentCells(a_pointIdx, a_adjacentCells);
} // XmUGrid::GetPointAdjacentCells

//------------------------------------------------------------------------------
/// \brief Gets the common cells from a vector of points
/// \param[in] a_points a vector of unique points
/// \return a vector of cell indices
//------------------------------------------------------------------------------
VecInt XmUGrid::GetPointsAdjacentCells(const VecInt& a_points) const
{
  return m_impl->GetPointsAdjacentCells(a_points);
} // XmUGrid::GetPointsAdjacentCells

//------------------------------------------------------------------------------
/// \brief Gets the cells adjacent to all of a vector of points.
/// \param[in] a_pointIdxs an array of point indices
/// \param[out] a_adjacentCellIdxs a vector of cell indices
void XmUGrid::GetPointsAdjacentCells(
  const VecInt& a_pointIdxs,
  //------------------------------------------------------------------------------
  VecInt& a_adjacentCellIdxs) const
{
  m_impl->GetPointsAdjacentCells(a_pointIdxs, a_adjacentCellIdxs);
} // XmUGrid::GetPointsAdjacentCells

//------------------------------------------------------------------------------
/// \brief Gets the cells adjacent to both of the two points.
/// \param[in] a_pointIdx1 first point index
/// \param[in] a_pointIdx2 second point index
/// \param[out] a_adjacentCellIdxs a vector of cell indices
void XmUGrid::GetPointsAdjacentCells(
  int a_pointIdx1,
  int a_pointIdx2,
  //------------------------------------------------------------------------------
  VecInt& a_adjacentCellIdxs) const
{
  m_impl->GetPointsAdjacentCells(a_pointIdx1, a_pointIdx2, a_adjacentCellIdxs);
} // XmUGrid::GetPointsAdjacentCells

//------------------------------------------------------------------------------
/// \brief Determine whether adjacent cells are valid after a point is moved.
/// \param[in] a_changedPtIdx index of the point to be changed
/// \param[in] a_newPosition location the point is to be moved to
/// \return whether the change is valid
//------------------------------------------------------------------------------
bool XmUGrid::IsValidPointChange(int a_changedPtIdx, const Pt3d& a_newPosition) const
{
  return m_impl->IsValidPointChange(a_changedPtIdx, a_newPosition);
} // XmUGrid::IsValidPointChange

//------------------------------------------------------------------------------
/// \brief Get the number of cells.
/// \return the number of cells
//------------------------------------------------------------------------------
int XmUGrid::GetCellCount() const
{
  return m_impl->GetCellCount();
} // XmUGrid::GetCellCount

//------------------------------------------------------------------------------
/// \brief Get the number of cell points (including polyhedron).
/// \param[in] a_cellIdx the index of the cell
/// \return a vector of point indices
//------------------------------------------------------------------------------
int XmUGrid::GetCellPointCount(int a_cellIdx) const
{
  return m_impl->GetCellPointCount(a_cellIdx);
} // XmUGrid::GetCellPointCount

//------------------------------------------------------------------------------
/// \brief Get the points of a cell (including polyhedron)
/// \param[in] a_cellIdx the index of the cell
/// \return a vector of point indices
//------------------------------------------------------------------------------
VecInt XmUGrid::GetCellPoints(int a_cellIdx) const
{
  return m_impl->GetCellPoints(a_cellIdx);
} // XmUGrid::GetCellPoints

//------------------------------------------------------------------------------
/// \brief Get the points of a cell.
/// \param[in] a_cellIdx the index of the cell
/// \param[out] a_cellPoints the points of the cell
/// \return if the cell index is valid
//------------------------------------------------------------------------------
bool XmUGrid::GetCellPoints(int a_cellIdx, VecInt& a_cellPoints) const
{
  return m_impl->GetCellPoints(a_cellIdx, a_cellPoints);
} // XmUGrid::GetCellPoints

//------------------------------------------------------------------------------
/// \brief Get locations of cell points.
/// \param[in] a_cellIdx the index of the cell
/// \param[out] a_cellLocations The locations of the cell points
//------------------------------------------------------------------------------
void XmUGrid::GetCellLocations(int a_cellIdx, VecPt3d& a_cellLocations) const
{
  m_impl->GetCellLocations(a_cellIdx, a_cellLocations);
} // XmUGrid::GetCellLocations

//------------------------------------------------------------------------------
/// \brief Get the number of cells.
/// \param[in] a_cellIdx the index of the cell
/// \return the number of cells or -1 if invalid index
//------------------------------------------------------------------------------
XmUGridCellType XmUGrid::GetCellType(int a_cellIdx) const
{
  return m_impl->GetCellType(a_cellIdx);
} // XmUGrid::GetCellType

//------------------------------------------------------------------------------
/// \brief Count all number of the cells with each dimenion (0, 1, 2, 3)
/// \return the count of dimensions of all of the cells of the ugrid
//------------------------------------------------------------------------------
std::vector<int> XmUGrid::GetDimensionCounts() const
{
  return m_impl->GetDimensionCounts();
} // XmUGrid::GetDimensionCounts

//------------------------------------------------------------------------------
/// \brief Get the dimension of the specified cell.
/// \param[in] a_cellIdx the index of the cell
/// \return the dimension of the cells or -1 if invalid index or invalid
/// dimension
//------------------------------------------------------------------------------
int XmUGrid::GetCellDimension(int a_cellIdx) const
{
  return m_impl->GetCellDimension(a_cellIdx);
} // XmUGrid::GetCellDimension

//------------------------------------------------------------------------------
/// \brief Get the extents of the given cell.
/// \param[in] a_cellIdx The cell index to get the extents of.
/// \param[out] a_min The minimum location.
/// \param[out] a_max The maximum location.
//------------------------------------------------------------------------------
void XmUGrid::GetCellExtents(int a_cellIdx, Pt3d& a_min, Pt3d& a_max) const
{
  m_impl->GetCellExtents(a_cellIdx, a_min, a_max);
} // XmUGrid::GetCellExtents

//------------------------------------------------------------------------------
/// \brief Get cell stream vector for the entire UGrid.
/// A cellstream is defined as follows:
///   Polyhedrons:
///     Cell type, number of faces, [num points in face, point numbers (0-based,
///     CCW when looking in)] repeated for each face.
///   Hexahedrons, polygons, quads, triangles etc:
///     Cell type (ElemTypeEnum), number of points, point numbers.  Zero-based, CCW,
///     bottom, then top. Not true for pixel or voxel.
/// \return constant reference to the cell stream vector
//------------------------------------------------------------------------------
const VecInt& XmUGrid::GetCellstream() const
{
  return m_impl->GetCellstream();
} // XmUGrid::GetCellstream

//------------------------------------------------------------------------------
/// \brief Set the ugrid cells for the entire UGrid using a cell stream.
/// \param[in] a_cellstream The cellstream for the UGrid.
/// @see CellStream
/// \return if successfully set
//------------------------------------------------------------------------------
bool XmUGrid::SetCellstream(const VecInt& a_cellstream)
{
  return m_impl->SetCellstream(a_cellstream);
} // XmUGrid::SetCellstream

//------------------------------------------------------------------------------
/// \brief Get cell stream vector for a single cell.
/// \param[in] a_cellIdx the index of the cell
/// \param[in] a_cellstream The cellstream of the cell
/// @see GetCellstream for more detail on cell stream definitions.
/// \return whether it was successfull or not
//------------------------------------------------------------------------------
bool XmUGrid::GetCellCellstream(int a_cellIdx, VecInt& a_cellstream) const
{
  return m_impl->GetCellCellstream(a_cellIdx, a_cellstream);
} // XmUGrid::GetCellCellstream
//------------------------------------------------------------------------------
/// \brief Get beginning index of cell in cell stream.
/// \param[in] a_cellIdx the index of the cell
/// \return The index of the cell in the cell stream.
//------------------------------------------------------------------------------
int XmUGrid::GetCellCellstreamIndex(int a_cellIdx) const
{
  return m_impl->GetCellCellstreamIndex(a_cellIdx);
} // XmUGrid::GetCellCellstreamIndex
//------------------------------------------------------------------------------
/// \brief Get the cells neighboring a cell (cells associated with any of it's points)
/// \param[in] a_cellIdx the index of the cell
/// \return vector of cell indices
//------------------------------------------------------------------------------
VecInt XmUGrid::GetCellAdjacentCells(int a_cellIdx) const
{
  return m_impl->GetCellAdjacentCells(a_cellIdx);
} // XmUGrid::GetCellAdjacentCells

//------------------------------------------------------------------------------
/// \brief Get the cells neighboring a cell (cells associated with any of it's points)
/// \param[in] a_cellIdx the index of the cell
/// \param[out] a_cellNeighbors vector of cell indices
//------------------------------------------------------------------------------
void XmUGrid::GetCellAdjacentCells(int a_cellIdx, VecInt& a_cellNeighbors) const
{
  m_impl->GetCellAdjacentCells(a_cellIdx, a_cellNeighbors);
} // XmUGrid::GetCellAdjacentCells

//------------------------------------------------------------------------------
/// \brief Get a plan view polygon of a specified cell
/// \param[in] a_cellIdx The index of the cell.
/// \param[out] a_polygon Vector of Pt3d that is the plan view polygon.
/// \return False if the cell index does not exist or if the cell is not 2 or 3
/// dimensional.
//------------------------------------------------------------------------------
bool XmUGrid::GetCellPlanViewPolygon(int a_cellIdx, VecPt3d& a_polygon) const
{
  return m_impl->GetCellPlanViewPolygon(a_cellIdx, a_polygon);
} // XmUGrid::GetCellPlanViewPolygon

//------------------------------------------------------------------------------
/// \brief Get the centroid location of a cell.
/// \param[in] a_cellIdx The index of the cell.
/// \param[out] a_centroid The location of the cell centroid.
/// \return False if the cell index does not exist.
//------------------------------------------------------------------------------
bool XmUGrid::GetCellCentroid(int a_cellIdx, Pt3d& a_centroid) const
{
  return m_impl->GetCellCentroid(a_cellIdx, a_centroid);
} // XmUGrid::GetCellCentroid

//------------------------------------------------------------------------------
/// \brief Get the number of edges for a cell.
/// \param[in] a_cellIdx the index of the cell
/// \return the count of cell edges
//------------------------------------------------------------------------------
int XmUGrid::GetCellEdgeCount(int a_cellIdx) const
{
  return m_impl->GetCellEdgeCount(a_cellIdx);
} // XmUGrid::GetCellEdgeCount

//------------------------------------------------------------------------------
/// \brief Get the points of a cell.
/// \param[in] a_cellIdx the index of the cell
/// \param[in] a_edgeIdx the index of the edge
/// \return a standard pair of point indices (which is an edge)
//------------------------------------------------------------------------------
XmEdge XmUGrid::GetCellEdge(int a_cellIdx, int a_edgeIdx) const
{
  return m_impl->GetCellEdge(a_cellIdx, a_edgeIdx);
} // XmUGrid::GetCellEdge

//------------------------------------------------------------------------------
/// \brief Get the index of the adjacent cells (that shares the same cell edge)
/// \param[in] a_cellIdx the index of the cell
/// \param[in] a_edgeIdx the index of the edge
/// \return a vector of cell indices of the adjacent cells
//------------------------------------------------------------------------------
VecInt XmUGrid::GetCellEdgeAdjacentCells(int a_cellIdx, int a_edgeIdx) const
{
  return m_impl->GetCellEdgeAdjacentCells(a_cellIdx, a_edgeIdx);
} // XmUGrid::GetCellEdgeAdjacentCells

//------------------------------------------------------------------------------
/// \brief Get the index of the adjacent cells (that shares the same cell edge)
/// \param[in] a_cellIdx the index of the cell
/// \param[in] a_edgeIdx the index of the edge
/// \param[out] a_adjacentCellIdxs a vector of cell indices of the adjacent
///             cells
//------------------------------------------------------------------------------
void XmUGrid::GetCellEdgeAdjacentCells(int a_cellIdx,
                                       int a_edgeIdx,
                                       VecInt& a_adjacentCellIdxs) const
{
  m_impl->GetCellEdgeAdjacentCells(a_cellIdx, a_edgeIdx, a_adjacentCellIdxs);
} // XmUGrid::GetCellEdgeAdjacentCells

//------------------------------------------------------------------------------
/// \brief Get the index of the adjacent cells (that shares the same cell edge)
/// \param[in] a_cellIdx the index of the cell
/// \param[in] a_edgeIdx the index of the edge
/// \return index of the adjacent cell (or -1 if none).
//------------------------------------------------------------------------------
int XmUGrid::GetCell2dEdgeAdjacentCell(int a_cellIdx, int a_edgeIdx) const
{
  return m_impl->GetCell2dEdgeAdjacentCell(a_cellIdx, a_edgeIdx);
} // XmUGrid::GetCell2dEdgeAdjacentCell

//------------------------------------------------------------------------------
/// \brief Get the indices of the adjacent cells (that shares the same cell edge)
/// \param[in] a_edge the edge (a pair of point indices)
/// \param[out] a_adjacentCellIdxs a vector of cell indices of the adjacent cells
//------------------------------------------------------------------------------
void XmUGrid::GetEdgeAdjacentCells(const XmEdge& a_edge, VecInt& a_adjacentCellIdxs) const
{
  m_impl->GetEdgeAdjacentCells(a_edge, a_adjacentCellIdxs);
} // XmUGrid::GetEdgeAdjacentCells

//------------------------------------------------------------------------------
/// \brief Get the index of the adjacent cells (that shares the same cell edge)
/// \param[in] a_edge the edge (a pair of point indices)
/// \return a vector of cell indices of the adjacent cells
//------------------------------------------------------------------------------
VecInt XmUGrid::GetEdgeAdjacentCells(const XmEdge& a_edge) const
{
  return m_impl->GetEdgeAdjacentCells(a_edge);
} // XmUGrid::GetEdgeAdjacentCells

//------------------------------------------------------------------------------
/// \brief Get the Edges of a cell.
/// \param[in] a_cellIdx the cells to whom the edges belong
/// \return a vector of edges
//------------------------------------------------------------------------------
std::vector<XmEdge> XmUGrid::GetCellEdges(int a_cellIdx) const
{
  return m_impl->GetCellEdges(a_cellIdx);
} // XmUGrid::GetCellEdges

//------------------------------------------------------------------------------
/// \brief Get the Edges of a cell.
/// \param[in] a_cellIdx the cells to whom the edges belong
/// \param[out] a_edges a vector of edges
//------------------------------------------------------------------------------
void XmUGrid::GetCellEdges(int a_cellIdx, std::vector<XmEdge>& a_edges) const
{
  m_impl->GetCellEdges(a_cellIdx, a_edges);
} // XmUGrid::GetCellEdges

// Faces

//------------------------------------------------------------------------------
/// \brief Get the number of cell faces for given cell.
/// \param[in] a_cellIdx the index of the cell
/// \return the count of cell faces
//------------------------------------------------------------------------------
int XmUGrid::GetCell3dFaceCount(int a_cellIdx) const
{
  return m_impl->GetCell3dFaceCount(a_cellIdx);
} // XmUGrid::GetCell3dFaceCount
//------------------------------------------------------------------------------
/// \brief Get the number of face points for a given cell and face.
/// \param[in] a_cellIdx The cell
/// \param[in] a_faceIdx The face
/// \return The number of face points or -1 if invalid face or cell index.
//------------------------------------------------------------------------------
int XmUGrid::GetCell3dFacePointCount(int a_cellIdx, int a_faceIdx) const
{
  return m_impl->GetCell3dFacePointCount(a_cellIdx, a_faceIdx);
} // XmUGrid::GetCell3dFacePointCount

//------------------------------------------------------------------------------
/// \brief Get the cell face for given cell and face index.
/// \param[in] a_cellIdx the index of the cell
/// \param[in] a_faceIdx the face index of the cell
/// \return a vector of point indices for the face index of the cell
//------------------------------------------------------------------------------
VecInt XmUGrid::GetCell3dFacePoints(int a_cellIdx, int a_faceIdx) const
{
  return m_impl->GetCell3dFacePoints(a_cellIdx, a_faceIdx);
} // XmUGrid::GetCell3dFacePoints

//------------------------------------------------------------------------------
/// \brief Get the cell face for given cell and face index.
/// \param[in] a_cellIdx the index of the cell
/// \param[in] a_faceIdx the face index of the cell
/// \param[out] a_facePtIdxs a vector of point indices for the face
/// \return a vector of point indices for the face index of the cell
//------------------------------------------------------------------------------
void XmUGrid::GetCell3dFacePoints(int a_cellIdx, int a_faceIdx, VecInt& a_facePtIdxs) const
{
  m_impl->GetCell3dFacePoints(a_cellIdx, a_faceIdx, a_facePtIdxs);
} // XmUGrid::GetCell3dFacePoints

//------------------------------------------------------------------------------
/// \brief Get the faces of a cell.
/// \param[in] a_cellIdx the cells to whom the faces belong
/// \return a vector of faces, which is a vector of point indices
//------------------------------------------------------------------------------
VecInt2d XmUGrid::GetCell3dFacesPoints(int a_cellIdx) const
{
  return m_impl->GetCell3dFacesPoints(a_cellIdx);
} // XmUGrid::GetCell3dFacesPoints

//------------------------------------------------------------------------------
/// \brief Get the cell face neighbors for given cell and face index.
/// \param[in] a_cellIdx the index of the cell
/// \param[in] a_faceIdx the face index of the cell
/// \return a cell index of the neighbor
//------------------------------------------------------------------------------
int XmUGrid::GetCell3dFaceAdjacentCell(int a_cellIdx, int a_faceIdx) const
{
  return m_impl->GetCell3dFaceAdjacentCell(a_cellIdx, a_faceIdx);
} // XmUGrid::GetCell3dFaceAdjacentCell

//------------------------------------------------------------------------------
/// \brief Get the cell face neighbors for given cell and face index.
/// \param[in] a_cellIdx the index of the cell
/// \param[in] a_faceIdx the face index of the cell
/// \param[in] a_neighborCell the index of the neighboring cell
/// \param[in] a_neighborFace the face index of the neighboring cell adjacent
///      to the given face
/// \return a cell index of the neighbor
//------------------------------------------------------------------------------
bool XmUGrid::GetCell3dFaceAdjacentCell(int a_cellIdx,
                                        int a_faceIdx,
                                        int& a_neighborCell,
                                        int& a_neighborFace) const
{
  return m_impl->GetCell3dFaceAdjacentCell(a_cellIdx, a_faceIdx, a_neighborCell, a_neighborFace);
} // XmUGrid::GetCell3dFaceAdjacentCell

//------------------------------------------------------------------------------
/// \brief Get the orientation of the face of a vertically prismatic cell.
/// \param[in] a_cellIdx the index of the cell
/// \param[in] a_faceIdx the face index of the cell
/// \return The orientation of the face (TOP, BOTTOM, SIDE, UNKNOWN).
//------------------------------------------------------------------------------
XmUGridFaceOrientation XmUGrid::GetCell3dFaceOrientation(int a_cellIdx, int a_faceIdx) const
{
  return m_impl->GetCell3dFaceOrientation(a_cellIdx, a_faceIdx);
} // XmUGrid::GetCell3dFaceOrientation
XmUGridCellOrder XmUGrid::GetCellOrder() const
{
  return m_impl->GetCellOrder();
} // XmUGrid::GetCellOrder
void XmUGrid::SetCellOrder(XmUGridCellOrder a_cellOrder)
{
  m_impl->SetCellOrder(a_cellOrder);
} // XmUGrid::SetCellOrder
XmUGridCellOrder XmUGrid::CalculateCellOrder() const
{
  return m_impl->CalculateCellOrder();
} // XmUGrid::CalculateCellOrder
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
std::shared_ptr<XmUGrid> TEST_XmUGrid1Left90Tri()
{
  VecPt3d points = {{0, 0, 0}, {20, 0, 0}, {0, 20, 0}};

  // Cell type (5), number of points (3), point numbers, counterclockwise
  std::vector<int> cells = {5, 3, 0, 1, 2};

  std::shared_ptr<XmUGrid> ugrid = XmUGrid::New(points, cells);

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
std::shared_ptr<XmUGrid> TEST_XmUGridSimpleQuad()
{
  VecPt3d points = {{0, 10, 0}, {10, 10, 0}, {20, 10, 0},  {0, 0, 0},   {10, 0, 0},
                    {20, 0, 0}, {0, -10, 0}, {10, -10, 0}, {20, -10, 0}};

  // Cell type (9), number of points (4), point numbers, counterclockwise
  VecInt cellstream = {XMU_QUAD, 4, 0, 3, 4, 1, XMU_QUAD, 4, 1, 4, 5, 2,
                       XMU_QUAD, 4, 3, 6, 7, 4, XMU_QUAD, 4, 4, 7, 8, 5};

  std::shared_ptr<XmUGrid> ugrid = XmUGrid::New(points, cellstream);
  return ugrid;
} // TEST_XmUGridSimpleQuad

//------------------------------------------------------------------------------
/// \brief Builds an XmUGrid with supported 1D and 2D linear cells for testing.
/// \return Returns the XmUGrid.
//------------------------------------------------------------------------------
std::shared_ptr<XmUGrid> TEST_XmUGrid2dLinear()
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

  std::shared_ptr<XmUGrid> ugrid = XmUGrid::New(points, cells);

  return ugrid;
} // TEST_XmUGrid2dLinear
//------------------------------------------------------------------------------
/// \brief Builds an XmUGrid with supported 3D linear cells for testing.
/// \return Returns the XmUGrid.
//------------------------------------------------------------------------------
std::shared_ptr<XmUGrid> TEST_XmUGrid3dLinear()
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
                            4, 9, 8, 13, 14, // Bottom face with 4 points : 9, 8, 13, 14
                            4, 8, 9, 24, 23, // Front face with 4 points : 8, 9, 24, 23
                            4, 9, 14, 29, 24, // Right face with 4 points : 9, 14, 29, 28
                            4, 14, 13, 28, 29, // Back face with 4 points : 14, 13, 28, 29
                            4, 8, 13, 28, 23, // Left face with 4 points : 13, 8, 23, 28
                            4, 23, 24, 29, 28, // Top face with 4 points : 23, 24, 29, 28
                            (int)XMU_WEDGE, 6, 3, 4, 18, 8, 9, 23,
                            (int)XMU_PYRAMID, 5, 5, 6, 11, 10, 20};
  //! [snip_test_3DShapes]
  // clang-format on

  std::shared_ptr<XmUGrid> ugrid = XmUGrid::New(points, cells);

  return ugrid;
} // TEST_XmUGrid3dLinear
//------------------------------------------------------------------------------
/// \brief Builds a 1 cell hexagon with cell type polyhedron.
/// \return Returns the UGrid.
//------------------------------------------------------------------------------
std::shared_ptr<XmUGrid> TEST_XmUGridHexagonalPolyhedron()
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

  std::shared_ptr<XmUGrid> ugrid = XmUGrid::New(points, cells);

  return ugrid;
} // TEST_XmUGridHexagonalPolyhedron
//------------------------------------------------------------------------------
/// \brief Builds a UGrid of Quads at 1 spacing for rows & cols specified
/// \param[in] a_rows number of rows in UGrid
/// \param[in] a_cols number of columns in UGrid
/// \return Returns the UGrid.
//------------------------------------------------------------------------------
std::shared_ptr<xms::XmUGrid> TEST_XmUBuildQuadUGrid(int a_rows, int a_cols)
{
  Pt3d origin(0.0, 0.0, 0.0);
  return TEST_XmUBuildQuadUGrid(a_rows, a_cols, origin);
} // TEST_XmUBuildQuadUGrid
//------------------------------------------------------------------------------
/// \brief Builds a UGrid of square quads with points at 1 spacing.
/// \param[in] a_rows number of rows in UGrid
/// \param[in] a_cols number of columns in UGrid
/// \param[in] a_origin location where the UGrid begins (min x, min y, min z)
/// \return Returns the UGrid.
//------------------------------------------------------------------------------
std::shared_ptr<xms::XmUGrid> TEST_XmUBuildQuadUGrid(int a_rows, int a_cols, const xms::Pt3d& a_origin)
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
/// \brief Builds a UGrid of square hexahedrons with points at 1 spacing.
/// \param[in] a_rows number of rows in UGrid
/// \param[in] a_cols number of columns in UGrid
/// \param[in] a_lays number of layers in UGrid
/// \return Returns the UGrid.
//------------------------------------------------------------------------------
std::shared_ptr<xms::XmUGrid> TEST_XmUBuildHexahedronUgrid(int a_rows, int a_cols, int a_lays)
{
  Pt3d origin(0.0, 0.0, 0.0);
  return TEST_XmUBuildHexahedronUgrid(a_rows, a_cols, a_lays, origin);
} // TEST_XmUBuildHexahedronUgrid
//------------------------------------------------------------------------------
/// \brief Builds a UGrid of square hexahedrons with points at 1 spacing.
/// \param[in] a_pointRows Number of point rows in UGrid.
/// \param[in] a_pointColumns Number of point columns in UGrid.
/// \param[in] a_pointLayers Number of point layers in UGrid
/// \param[in] a_origin Location of minimum point (min x, min y, min z).
/// \param[in] a_increasingDown Cells start at the top layer and go down.
/// \return Returns the UGrid.
//------------------------------------------------------------------------------
std::shared_ptr<xms::XmUGrid> TEST_XmUBuildDirectedHexahedronUgrid(int a_pointRows,
                                                                   int a_pointColumns,
                                                                   int a_pointLayers,
                                                                   const xms::Pt3d& a_origin,
                                                                   bool a_increasingDown)
{
  VecPt3d points;
  points.reserve(a_pointRows * a_pointColumns);
  for (int k = 0; k < a_pointLayers; ++k)
  {
    for (int i = 0; i < a_pointRows; ++i)
    {
      for (int j = 0; j < a_pointColumns; ++j)
      {
        double x = j + a_origin.x;
        double y = a_pointRows - i - 1 + a_origin.y;
        double z;
        if (a_increasingDown)
          z = a_pointLayers - k - 1 + a_origin.z;
        else
          z = k + a_origin.z;
        points.push_back(Pt3d(x, y, z));
      }
    }
  }

  VecInt cells;
  cells.reserve((a_pointRows - 1) * (a_pointColumns - 1) * (a_pointLayers - 1) * 10);
  int numInLayer = a_pointRows * a_pointColumns;
  for (int k = 0; k < a_pointLayers - 1; ++k)
  {
    int layOffset = numInLayer * k;
    for (int i = 0; i < a_pointRows - 1; ++i)
    {
      for (int j = 0; j < a_pointColumns - 1; ++j)
      {
        cells.push_back(XMU_HEXAHEDRON);
        cells.push_back(8);
        if (a_increasingDown)
        {
          // top face counterclockwise looking down
          cells.push_back(j + a_pointColumns * i + layOffset);
          cells.push_back(j + 1 + a_pointColumns * i + layOffset);
          cells.push_back(j + 1 + a_pointColumns * (i + 1) + layOffset);
          cells.push_back(j + a_pointColumns * (i + 1) + layOffset);
          // bottom face counterclockwise looking down
          cells.push_back(j + a_pointColumns * i + layOffset + numInLayer);
          cells.push_back(j + 1 + a_pointColumns * i + layOffset + numInLayer);
          cells.push_back(j + 1 + a_pointColumns * (i + 1) + layOffset + numInLayer);
          cells.push_back(j + a_pointColumns * (i + 1) + layOffset + numInLayer);
        }
        else
        {
          // top face counterclockwise looking down
          cells.push_back(j + a_pointColumns * i + layOffset + numInLayer);
          cells.push_back(j + 1 + a_pointColumns * i + layOffset + numInLayer);
          cells.push_back(j + 1 + a_pointColumns * (i + 1) + layOffset + numInLayer);
          cells.push_back(j + a_pointColumns * (i + 1) + layOffset + numInLayer);
          // bottom face counterclockwise looking down
          cells.push_back(j + a_pointColumns * i + layOffset);
          cells.push_back(j + 1 + a_pointColumns * i + layOffset);
          cells.push_back(j + 1 + a_pointColumns * (i + 1) + layOffset);
          cells.push_back(j + a_pointColumns * (i + 1) + layOffset);
        }
      }
    }
  }
  return XmUGrid::New(points, cells);
} // TEST_XmUBuildHexahedronUgrid
//------------------------------------------------------------------------------
/// \brief Builds a UGrid of Quads at 1 spacing for rows & cols specified
/// \param[in] a_rows number of rows in UGrid
/// \param[in] a_cols number of columns in UGrid
/// \param[in] a_lays number of layers in UGrid
/// \param[in] a_origin locatGetPointLocation UGrid begins (min x, min y, min z)
/// \return Returns the UGrid.
//------------------------------------------------------------------------------
std::shared_ptr<xms::XmUGrid> TEST_XmUBuildHexahedronUgrid(int a_rows,
                                                           int a_cols,
                                                           int a_lays,
                                                           const xms::Pt3d& a_origin)
{
  return TEST_XmUBuildDirectedHexahedronUgrid(a_rows, a_cols, a_lays, a_origin, true);
} // TEST_XmUBuildHexahedronUgrid
//------------------------------------------------------------------------------
/// \brief Builds a UGrid of Quads at 1 spacing for rows & cols specified
/// \param[in] a_rows number of rows in UGrid
/// \param[in] a_cols number of columns in UGrid
/// \param[in] a_lays number of layers in UGrid
/// \param[in] a_origin locatGetPointLocation UGrid begins (min x, min y, min z)
/// \return Returns the UGrid.
//------------------------------------------------------------------------------
std::shared_ptr<xms::XmUGrid> TEST_XmUBuildIncreasingUpHexahedronUgrid(int a_rows,
                                                                       int a_cols,
                                                                       int a_lays,
                                                                       const xms::Pt3d& a_origin)
{
  return TEST_XmUBuildDirectedHexahedronUgrid(a_rows, a_cols, a_lays, a_origin, false);
} // TEST_XmUBuildIncreasingUpHexahedronUgrid
//------------------------------------------------------------------------------
/// \brief Builds a UGrid of Quads at 1 spacing for rows & cols specified
/// \param[in] a_rows number of rows in UGrid
/// \param[in] a_cols number of columns in UGrid
/// \param[in] a_lays number of layers in UGrid
/// \return Returns the UGrid.
//------------------------------------------------------------------------------
std::shared_ptr<xms::XmUGrid> TEST_XmUBuildPolyhedronUgrid(int a_rows, int a_cols, int a_lays)
{
  Pt3d origin(0.0, 0.0, 0.0);
  return TEST_XmUBuildPolyhedronUgrid(a_rows, a_cols, a_lays, origin);
} // TEST_XmUBuildPolyhedronUgrid
//------------------------------------------------------------------------------
/// \brief Builds a UGrid of Quads at 1 spacing for rows & cols specified
/// \param[in] a_rows number of rows in UGrid
/// \param[in] a_cols number of columns in UGrid
/// \param[in] a_lays number of layers in UGrid
/// \param[in] a_origin location wGetPointLocationd begins (min x, min y, min z)
/// \return Returns the UGrid.
//------------------------------------------------------------------------------
std::shared_ptr<xms::XmUGrid> TEST_XmUBuildPolyhedronUgrid(int a_rows,
                                                           int a_cols,
                                                           int a_lays,
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
        int pt1 = j + 1 + a_cols * i + layOffset;
        int pt2 = j + a_cols * (i + 1) + layOffset;
        int pt3 = j + 1 + a_cols * (i + 1) + layOffset;
        int pt4 = pt0 + numInLayer;
        int pt5 = pt1 + numInLayer;
        int pt6 = pt2 + numInLayer;
        int pt7 = pt3 + numInLayer;

        cells.push_back(XMU_POLYHEDRON);
        cells.push_back(6);
        // front
        cells.push_back(4);
        cells.push_back(pt2);
        cells.push_back(pt6);
        cells.push_back(pt7);
        cells.push_back(pt3);
        // right
        cells.push_back(4);
        cells.push_back(pt1);
        cells.push_back(pt5);
        cells.push_back(pt7);
        cells.push_back(pt3);
        // back
        cells.push_back(4);
        cells.push_back(pt0);
        cells.push_back(pt1);
        cells.push_back(pt5);
        cells.push_back(pt4);
        // left
        cells.push_back(4);
        cells.push_back(pt0);
        cells.push_back(pt4);
        cells.push_back(pt6);
        cells.push_back(pt2);
        // top
        cells.push_back(4);
        cells.push_back(pt0);
        cells.push_back(pt2);
        cells.push_back(pt3);
        cells.push_back(pt1);
        // bottom
        cells.push_back(4);
        cells.push_back(pt4);
        cells.push_back(pt5);
        cells.push_back(pt7);
        cells.push_back(pt6);
      }
    }
  }
  return XmUGrid::New(points, cells);
} // TEST_XmUBuildPolyhedronUgrid
//------------------------------------------------------------------------------
/// \brief Builds a UGrid with one 3D Chevron polyhedron
/// \return Returns the UGrid.
//------------------------------------------------------------------------------
std::shared_ptr<xms::XmUGrid> TEST_XmUBuild3DChevronUgrid()
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
#include <xmsgrid/ugrid/XmUGrid.t.h>

#include <numeric>
#include <xmscore/testing/TestTools.h>

using namespace xms;

////////////////////////////////////////////////////////////////////////////////
/// \class XmUGridUnitTests
/// \brief Tests XmUGrids.
////////////////////////////////////////////////////////////////////////////////

//------------------------------------------------------------------------------
/// \brief Test constructors and assignment operator.
//------------------------------------------------------------------------------
void XmUGridUnitTests::testOperators()
{
  std::shared_ptr<XmUGrid> xmUGrid = TEST_XmUGrid1Left90Tri();

  // test copy constructor
  XmUGrid grid1(*xmUGrid);
  TS_ASSERT_EQUALS(xmUGrid->GetLocations(), grid1.GetLocations());

  // test move constructor
  XmUGrid grid2(std::move(grid1));
  TS_ASSERT(grid1.GetLocations().empty());
  TS_ASSERT_EQUALS(xmUGrid->GetLocations(), grid2.GetLocations());

  // test assignment operator
  grid1 = grid2;
  TS_ASSERT_EQUALS(xmUGrid->GetLocations(), grid1.GetLocations());
  TS_ASSERT_EQUALS(xmUGrid->GetLocations(), grid2.GetLocations());
} // XmUGridUnitTests::testOperators

//! [snip_test_UGrid_Streams]
//------------------------------------------------------------------------------
/// \brief Test XmUGrid point and cell streams.
//------------------------------------------------------------------------------
void XmUGridUnitTests::testUGridStreams()
{
  // test empty UGrid
  std::shared_ptr<XmUGrid> emptyUGrid = XmUGrid::New();
  VecPt3d points = emptyUGrid->GetLocations();
  TS_ASSERT_EQUALS(0, points.size());

  VecInt cellstream = emptyUGrid->GetCellstream();
  TS_ASSERT(XmUGrid::IsValidCellstream(cellstream, (int)points.size()));
  TS_ASSERT_EQUALS(0, cellstream.size());

  // test adding points and cell stream

  //     0----1----2
  //     |    |    |
  //     3----4----5
  //     |    |    |
  //     6----7----8

  std::shared_ptr<XmUGrid> ugrid = XmUGrid::New();

  points = {{0, 10, 0}, {10, 10, 0}, {20, 10, 0},  {0, 0, 0},   {10, 0, 0},
            {20, 0, 0}, {0, -10, 0}, {10, -10, 0}, {20, -10, 0}};

  // Cell type (9), number of points (4), point numbers, counterclockwise
  cellstream = {9, 4, 0, 3, 4, 1, 9, 4, 1, 4, 5, 2, 9, 4, 3, 6, 7, 4, 9, 4, 4, 7, 8, 5};

  TS_ASSERT(!ugrid->GetModified());
  ugrid->SetLocations(points);
  VecPt3d pointsOut = ugrid->GetLocations();
  TS_ASSERT_EQUALS(points, pointsOut);
  TS_ASSERT(ugrid->GetModified());

  ugrid->SetUnmodified();
  TS_ASSERT(!ugrid->GetModified());
  TS_ASSERT(ugrid->SetCellstream(cellstream));
  VecInt cellstreamOut = ugrid->GetCellstream();
  TS_ASSERT_EQUALS(cellstream, cellstreamOut);
  TS_ASSERT(ugrid->GetModified());

  // Test adding cellstream then points (should fail)
  std::shared_ptr<XmUGrid> ugridBadOrder = XmUGrid::New();
  TS_ASSERT(!ugridBadOrder->SetCellstream(cellstream));

} // XmUGridUnitTests::testUGridStreams
//! [snip_test_UGrid_Streams]

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
                    {20, 0, 0}, {0, -10, 0},  {10, -10, 0}, {20, -10, 0}};

  // Cell type (9), number of points (4), point numbers, counterclockwise
  VecInt cellstream = {9, 4, 0, 3, 4, 1, 9, 4, 1, 4, 5, 2, 9, 4, 3, 6, 7, 4, 9, 4, 4, 7, 8, 5};

  std::shared_ptr<XmUGrid> ugrid = XmUGrid::New(points, cellstream);
  //! [snip_test_NewOperator]

  TS_ASSERT_EQUALS(Pt3d(), ugrid->GetPointLocation(-1));
  for (int i = 0; i < (int)points.size(); i++)
  {
    TS_ASSERT_EQUALS(points[i], ugrid->GetPointLocation(i));
  }
  TS_ASSERT_EQUALS(Pt3d(10, 10, 0), ugrid->GetPointXy0(1));
  TS_ASSERT_EQUALS(Pt3d(), ugrid->GetPointLocation((int)points.size()));
  TS_ASSERT(ugrid->GetModified());

  ugrid->SetUnmodified();
  TS_ASSERT(!ugrid->GetModified());
  TS_ASSERT(!ugrid->SetPointLocation(-1, Pt3d()));
  TS_ASSERT(!ugrid->SetPointLocation((int)points.size(), Pt3d()));
  TS_ASSERT(!ugrid->GetModified());

  TS_ASSERT(ugrid->SetPointLocation(0, Pt3d(-10, 10, 0)));
  TS_ASSERT_EQUALS(Pt3d(-10, 10, 0), ugrid->GetPointLocation(0));
  TS_ASSERT(ugrid->GetModified());
} // XmUGridUnitTests::testGetSetPoint
//------------------------------------------------------------------------------
/// \brief Test Getting a cell stream.
//------------------------------------------------------------------------------
void XmUGridUnitTests::testGetCellCellstream()
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
  VecInt cellstream;
  cellstream.insert(cellstream.end(), cell0.begin(), cell0.end());
  cellstream.insert(cellstream.end(), cell1.begin(), cell1.end());
  cellstream.insert(cellstream.end(), cell2.begin(), cell2.end());
  cellstream.insert(cellstream.end(), cell3.begin(), cell3.end());

  std::shared_ptr<XmUGrid> ugrid = XmUGrid::New(points, cellstream);
  VecInt cellResult;

  TS_ASSERT_EQUALS(false, ugrid->GetCellCellstream(-1, cellResult));
  TS_ASSERT_EQUALS(-1, ugrid->GetCellCellstreamIndex(-1));

  TS_ASSERT_EQUALS(true, ugrid->GetCellCellstream(0, cellResult));
  TS_ASSERT_EQUALS(cell0, cellResult);
  TS_ASSERT_EQUALS(0, ugrid->GetCellCellstreamIndex(0));

  TS_ASSERT_EQUALS(true, ugrid->GetCellCellstream(1, cellResult));
  TS_ASSERT_EQUALS(cell1, cellResult);
  TS_ASSERT_EQUALS(6, ugrid->GetCellCellstreamIndex(1));

  TS_ASSERT_EQUALS(true, ugrid->GetCellCellstream(2, cellResult));
  TS_ASSERT_EQUALS(cell2, cellResult);
  TS_ASSERT_EQUALS(12, ugrid->GetCellCellstreamIndex(2));

  TS_ASSERT_EQUALS(true, ugrid->GetCellCellstream(3, cellResult));
  TS_ASSERT_EQUALS(cell3, cellResult);
  TS_ASSERT_EQUALS(18, ugrid->GetCellCellstreamIndex(3));

  TS_ASSERT_EQUALS(false, ugrid->GetCellCellstream(ugrid->GetCellCount(), cellResult));
  TS_ASSERT_EQUALS(24, ugrid->GetCellCellstreamIndex(ugrid->GetCellCount()));
  TS_ASSERT_EQUALS(-1, ugrid->GetCellCellstreamIndex(ugrid->GetCellCount() + 1));

} // XmUGridUnitTests::testGetCellCellstream
//------------------------------------------------------------------------------
/// \brief Test getting number of points, cells, and cell type.
//------------------------------------------------------------------------------
void XmUGridUnitTests::testGetCellType()
{
  std::shared_ptr<XmUGrid> ugrid2d = TEST_XmUGrid2dLinear();
  TS_REQUIRE_NOT_NULL(ugrid2d);
  TS_ASSERT_EQUALS(14, ugrid2d->GetPointCount());
  TS_ASSERT_EQUALS(6, ugrid2d->GetCellCount());
  TS_ASSERT_EQUALS(XMU_INVALID_CELL_TYPE, ugrid2d->GetCellType(-1));
  TS_ASSERT_EQUALS(XMU_INVALID_CELL_TYPE, ugrid2d->GetCellType(6));
  TS_ASSERT_EQUALS(XMU_QUAD, ugrid2d->GetCellType(0));
  TS_ASSERT_EQUALS(XMU_PIXEL, ugrid2d->GetCellType(1));
  TS_ASSERT_EQUALS(XMU_TRIANGLE, ugrid2d->GetCellType(2));
  TS_ASSERT_EQUALS(XMU_POLYGON, ugrid2d->GetCellType(3));
  TS_ASSERT_EQUALS(XMU_POLY_LINE, ugrid2d->GetCellType(4));
  TS_ASSERT_EQUALS(XMU_LINE, ugrid2d->GetCellType(5));

  std::shared_ptr<XmUGrid> ugrid3d = TEST_XmUGrid3dLinear();
  TS_REQUIRE_NOT_NULL(ugrid3d);

  TS_ASSERT_EQUALS(30, ugrid3d->GetPointCount());
  TS_ASSERT_EQUALS(6, ugrid3d->GetCellCount());
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
  std::shared_ptr<XmUGrid> ugrid2d = TEST_XmUGrid2dLinear();
  TS_REQUIRE_NOT_NULL(ugrid2d);

  TS_ASSERT_EQUALS(XMU_INVALID_CELL_TYPE, ugrid2d->GetCellDimension(-1));
  TS_ASSERT_EQUALS(XMU_INVALID_CELL_TYPE, ugrid2d->GetCellDimension(6));
  TS_ASSERT_EQUALS(2, ugrid2d->GetCellDimension(0));
  TS_ASSERT_EQUALS(2, ugrid2d->GetCellDimension(1));
  TS_ASSERT_EQUALS(2, ugrid2d->GetCellDimension(2));
  TS_ASSERT_EQUALS(2, ugrid2d->GetCellDimension(3));
  TS_ASSERT_EQUALS(1, ugrid2d->GetCellDimension(4));
  TS_ASSERT_EQUALS(1, ugrid2d->GetCellDimension(5));

  std::shared_ptr<XmUGrid> ugrid3d = TEST_XmUGrid3dLinear();
  TS_REQUIRE_NOT_NULL(ugrid3d);

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
  TS_ASSERT_EQUALS(twoDResults, ugrid2d->GetDimensionCounts());
  TS_ASSERT_EQUALS(threeDResults, ugrid3d->GetDimensionCounts());

  // Test GetDimensionCounts with an empty grid
  std::shared_ptr<XmUGrid> emptyUgrid = XmUGrid::New();
  std::vector<int> emptyResults = emptyUgrid->GetDimensionCounts();
  TS_ASSERT_EQUALS(VecInt(4, 0), emptyResults);
} // XmUGridUnitTests::testGetCellDimension
//------------------------------------------------------------------------------
/// \brief Test getting the extents of a UGrid
//------------------------------------------------------------------------------
void XmUGridUnitTests::testGetExtents()
{
  std::shared_ptr<XmUGrid> ugrid2d = TEST_XmUGrid2dLinear();
  TS_REQUIRE_NOT_NULL(ugrid2d);

  Pt3d min, max;
  Pt3d expectedMin = {0.0, 0.0, 0.0}, expectMax = {40.0, 20.0, 0.0};
  ugrid2d->GetExtents(min, max);
  TS_ASSERT_EQUALS(expectedMin, min);
  TS_ASSERT_EQUALS(expectMax, max);

  std::shared_ptr<XmUGrid> ugrid3d = TEST_XmUGrid3dLinear();
  TS_REQUIRE_NOT_NULL(ugrid3d);

  expectedMin = {0.0, 0.0, 0.0};
  expectMax = {40.0, 20.0, 10.0};
  ugrid3d->GetExtents(min, max);
  TS_ASSERT_EQUALS(expectedMin, min);
  TS_ASSERT_EQUALS(expectMax, max);

  Pt3d origin(-25.0, -25.0, -15.0);
  std::shared_ptr<XmUGrid> ugridBuild = TEST_XmUBuildHexahedronUgrid(51, 51, 31, origin);
  TS_REQUIRE_NOT_NULL(ugridBuild);

  expectedMin = {-25.0, -25.0, -15.0};
  expectMax = {25.0, 25.0, 15.0};
  ugridBuild->GetExtents(min, max);
  TS_ASSERT_EQUALS(expectedMin, min);
  TS_ASSERT_EQUALS(expectMax, max);
} // XmUGridUnitTests::testGetExtents
//------------------------------------------------------------------------------
/// \brief Test getting edges of single cells.
//------------------------------------------------------------------------------
void XmUGridUnitTests::testGetCellEdgeCount()
{
  std::shared_ptr<XmUGrid> ugrid2d = TEST_XmUGrid2dLinear();
  TS_REQUIRE_NOT_NULL(ugrid2d);

  TS_ASSERT_EQUALS(-1, ugrid2d->GetCellEdgeCount(-1));
  TS_ASSERT_EQUALS(-1, ugrid2d->GetCellEdgeCount(6));
  TS_ASSERT_EQUALS(4, ugrid2d->GetCellEdgeCount(0));
  TS_ASSERT_EQUALS(4, ugrid2d->GetCellEdgeCount(1));
  TS_ASSERT_EQUALS(3, ugrid2d->GetCellEdgeCount(2));
  TS_ASSERT_EQUALS(6, ugrid2d->GetCellEdgeCount(3));
  TS_ASSERT_EQUALS(2, ugrid2d->GetCellEdgeCount(4));
  TS_ASSERT_EQUALS(1, ugrid2d->GetCellEdgeCount(5));

  std::shared_ptr<XmUGrid> ugrid3d = TEST_XmUGrid3dLinear();
  TS_REQUIRE_NOT_NULL(ugrid3d);

  TS_ASSERT_EQUALS(-1, ugrid3d->GetCellEdgeCount(-1));
  TS_ASSERT_EQUALS(-1, ugrid3d->GetCellEdgeCount(6));
  TS_ASSERT_EQUALS(6, ugrid3d->GetCellEdgeCount(0));
  TS_ASSERT_EQUALS(12, ugrid3d->GetCellEdgeCount(1));
  TS_ASSERT_EQUALS(12, ugrid3d->GetCellEdgeCount(2));
  TS_ASSERT_EQUALS(12, ugrid3d->GetCellEdgeCount(3));
  TS_ASSERT_EQUALS(9, ugrid3d->GetCellEdgeCount(4));
  TS_ASSERT_EQUALS(8, ugrid3d->GetCellEdgeCount(5));

} // XmUGridUnitTests::testGetCellEdgeCount

//! [snip_test_GetNumberOfCellFaces]
//------------------------------------------------------------------------------
/// \brief Test getting edges of single cells.
//------------------------------------------------------------------------------
void XmUGridUnitTests::testGetCell3dFaceCount()
{
  std::shared_ptr<XmUGrid> ugrid2d = TEST_XmUGrid2dLinear();
  TS_REQUIRE_NOT_NULL(ugrid2d);

  // test 1D and 2D cells
  TS_ASSERT_EQUALS(-1, ugrid2d->GetCell3dFaceCount(-1));
  for (int cellIdx = 0; cellIdx < ugrid2d->GetCellCount(); ++cellIdx)
  {
    TS_ASSERT_EQUALS(0, ugrid2d->GetCell3dFaceCount(cellIdx));
  }
  TS_ASSERT_EQUALS(-1, ugrid2d->GetCell3dFaceCount(ugrid2d->GetCellCount()));

  std::shared_ptr<XmUGrid> ugrid3d = TEST_XmUGrid3dLinear();
  TS_REQUIRE_NOT_NULL(ugrid3d);

  // test 3D cells
  TS_ASSERT_EQUALS(-1, ugrid3d->GetCell3dFaceCount(-1));
  TS_ASSERT_EQUALS(-1, ugrid3d->GetCell3dFaceCount(6));
  TS_ASSERT_EQUALS(4, ugrid3d->GetCell3dFaceCount(0));
  TS_ASSERT_EQUALS(6, ugrid3d->GetCell3dFaceCount(1));
  TS_ASSERT_EQUALS(6, ugrid3d->GetCell3dFaceCount(2));
  TS_ASSERT_EQUALS(6, ugrid3d->GetCell3dFaceCount(3));
  TS_ASSERT_EQUALS(5, ugrid3d->GetCell3dFaceCount(4));
  TS_ASSERT_EQUALS(5, ugrid3d->GetCell3dFaceCount(5));
} // XmUGridUnitTests::testGetCell3dFaceCount
//! [snip_test_GetNumberOfCellFaces]

//------------------------------------------------------------------------------
/// \brief Test getting the number of face points for a cell face.
//------------------------------------------------------------------------------
void XmUGridUnitTests::testGetCell3dFacePointCount()
{
  std::shared_ptr<XmUGrid> ugrid2d = TEST_XmUGrid2dLinear();
  TS_REQUIRE_NOT_NULL(ugrid2d);

  // test 1D and 2D cells - should return 0 for valid cell index
  TS_ASSERT_EQUALS(-1, ugrid2d->GetCell3dFacePointCount(-1, 0));
  TS_ASSERT_EQUALS(0, ugrid2d->GetCell3dFacePointCount(1, 0));
  TS_ASSERT_EQUALS(-1, ugrid2d->GetCell3dFacePointCount(ugrid2d->GetCellCount(), 0));

  std::shared_ptr<XmUGrid> ugrid3d = TEST_XmUGrid3dLinear();
  TS_REQUIRE_NOT_NULL(ugrid3d);

  // test 3D cells
  TS_ASSERT_EQUALS(-1, ugrid3d->GetCell3dFacePointCount(-1, 0));
  TS_ASSERT_EQUALS(-1, ugrid3d->GetCell3dFacePointCount(6, 0));
  TS_ASSERT_EQUALS(4, ugrid3d->GetCell3dFacePointCount(1, 3));
  TS_ASSERT_EQUALS(4, ugrid3d->GetCell3dFacePointCount(3, 2));
} // XmUGridUnitTests::testGetCell3dFacePointCount
//------------------------------------------------------------------------------
/// \brief Test getting the cells attached to points.
//------------------------------------------------------------------------------
void XmUGridUnitTests::testGetPointAdjacentCellsSimple()
{
  //     0----1----2
  //     |    |    |
  //     3----4----5

  VecPt3d points = {{0, 10, 0}, {10, 10, 0}, {20, 10, 0}, {0, 0, 0}, {10, 0, 0}, {20, 0, 0}};

  VecInt cellstream = {XMU_QUAD, 4, 0, 3, 4, 1, XMU_QUAD, 4, 1, 4, 5, 2};

  std::shared_ptr<XmUGrid> ugrid = XmUGrid::New(points, cellstream);

  VecInt cellEmpty = {};
  VecInt cellZero = {0};
  VecInt cellZeroAndOne = {0, 1};
  VecInt cellOne = {1};

  TS_ASSERT_EQUALS(cellEmpty, ugrid->GetPointAdjacentCells(-1));
  TS_ASSERT_EQUALS(cellZero, ugrid->GetPointAdjacentCells(0));
  TS_ASSERT_EQUALS(cellZeroAndOne, ugrid->GetPointAdjacentCells(1));
  TS_ASSERT_EQUALS(cellOne, ugrid->GetPointAdjacentCells(2));
  TS_ASSERT_EQUALS(cellZero, ugrid->GetPointAdjacentCells(3));
  TS_ASSERT_EQUALS(cellZeroAndOne, ugrid->GetPointAdjacentCells(4));
  TS_ASSERT_EQUALS(cellOne, ugrid->GetPointAdjacentCells(5));
  TS_ASSERT_EQUALS(cellEmpty, ugrid->GetPointAdjacentCells(6));

  TS_ASSERT_EQUALS(0, ugrid->GetPointAdjacentCellCount(-1));
  TS_ASSERT_EQUALS(1, ugrid->GetPointAdjacentCellCount(0));
  TS_ASSERT_EQUALS(2, ugrid->GetPointAdjacentCellCount(1));
  TS_ASSERT_EQUALS(1, ugrid->GetPointAdjacentCellCount(2));
  TS_ASSERT_EQUALS(1, ugrid->GetPointAdjacentCellCount(3));
  TS_ASSERT_EQUALS(2, ugrid->GetPointAdjacentCellCount(4));
  TS_ASSERT_EQUALS(1, ugrid->GetPointAdjacentCellCount(5));
  TS_ASSERT_EQUALS(0, ugrid->GetPointAdjacentCellCount(6));

} // XmUGridUnitTests::testGetPointAdjacentCellsSimple

//------------------------------------------------------------------------------
/// \brief Test getting cells adjacent to a point.
//------------------------------------------------------------------------------
void XmUGridUnitTests::testGetPointAdjacentCells()
{
  std::shared_ptr<XmUGrid> ugrid2d = TEST_XmUGrid2dLinear();
  TS_REQUIRE_NOT_NULL(ugrid2d);

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
    TS_ASSERT_EQUALS(cellsFor2DPoints[i], ugrid2d->GetPointAdjacentCells(i));
  }

  std::shared_ptr<XmUGrid> ugrid3d = TEST_XmUGrid3dLinear();
  TS_REQUIRE_NOT_NULL(ugrid3d);

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
    if (cellsFor3DPoints[i] != ugrid3d->GetPointAdjacentCells(i))
    {
      TS_FAIL(i);
    }
    TS_ASSERT_EQUALS(cellsFor3DPoints[i], ugrid3d->GetPointAdjacentCells(i));
  }

} // XmUGridUnitTests::testGetPointAdjacentCells
//------------------------------------------------------------------------------
/// \brief Test getting a vector of point indices for a cell
//------------------------------------------------------------------------------
void XmUGridUnitTests::testGetCellPoints()
{
  std::shared_ptr<XmUGrid> ugrid = TEST_XmUGridSimpleQuad();
  TS_REQUIRE_NOT_NULL(ugrid);

  VecInt2d expectedGetCellPoints = {{0, 3, 4, 1}, {1, 4, 5, 2}, {3, 6, 7, 4}, {4, 7, 8, 5}};
  VecInt2d cellPoints;
  VecInt cellPoint1D;
  TS_ASSERT(!ugrid->GetCellPoints(-1, cellPoint1D));
  TS_ASSERT(!ugrid->GetCellPoints(5, cellPoint1D));

  for (int i(0); i < ugrid->GetCellCount(); i++)
  {
    TS_ASSERT(ugrid->GetCellPoints(i, cellPoint1D));
    cellPoints.push_back(cellPoint1D);
    TS_ASSERT_EQUALS(expectedGetCellPoints[i], cellPoints[i]);
  }

  expectedGetCellPoints = {{0, 1, 6, 5},         {1, 2, 7, 6}, {2, 3, 7},
                           {3, 4, 8, 13, 12, 7}, {7, 11, 10},  {5, 9}};
  cellPoints.clear();
  std::shared_ptr<XmUGrid> ugrid2d = TEST_XmUGrid2dLinear();
  TS_REQUIRE_NOT_NULL(ugrid2d);

  for (int i(0); i < ugrid2d->GetCellCount(); i++)
  {
    TS_ASSERT(ugrid2d->GetCellPoints(i, cellPoint1D));
    cellPoints.push_back(cellPoint1D);
    TS_ASSERT_EQUALS(expectedGetCellPoints[i], cellPoints[i]);
  }

  expectedGetCellPoints = {{0, 1, 5, 15},
                           {1, 2, 6, 7, 16, 17, 21, 22},
                           {2, 3, 8, 7, 17, 18, 23, 22},
                           {9, 8, 13, 14, 24, 23, 29, 28},
                           {3, 4, 18, 8, 9, 23},
                           {5, 6, 11, 10, 20}};
  VecInt expectedPointCounts = {4, 8, 8, 8, 6, 5};
  cellPoints.clear();
  std::shared_ptr<XmUGrid> ugrid3d = TEST_XmUGrid3dLinear();
  TS_REQUIRE_NOT_NULL(ugrid3d);

  for (int i(0); i < ugrid3d->GetCellCount(); i++)
  {
    TS_ASSERT(ugrid3d->GetCellPoints(i, cellPoint1D));
    cellPoints.push_back(cellPoint1D);
    TS_ASSERT_EQUALS(expectedGetCellPoints[i], cellPoints[i]);
    TS_ASSERT_EQUALS(expectedPointCounts[i], ugrid3d->GetCellPointCount(i));
  }

} // XmUGridUnitTests::testGetCellPoints

//------------------------------------------------------------------------------
/// \brief Test iterating through the edges of cells
//------------------------------------------------------------------------------
void XmUGridUnitTests::testGetCellEdge()
{
  //     0-----1-----2
  //     |  0  |  1  |
  //     3-----4-----5
  //     |  2  |  3  |
  //     6-----7-----8

  // 2D shape (simple)
  std::shared_ptr<XmUGrid> ugrid = TEST_XmUGridSimpleQuad();
  TS_REQUIRE_NOT_NULL(ugrid);

  {
    XmEdge edge0(0, 3), edge1(3, 4), edge2(4, 1), edge3(1, 0);     // cell 0
    XmEdge edge4(1, 4), edge5(4, 5), edge6(5, 2), edge7(2, 1);     // cell 1
    XmEdge edge8(3, 6), edge9(6, 7), edge10(7, 4), edge11(4, 3);   // cell 2
    XmEdge edge12(4, 7), edge13(7, 8), edge14(8, 5), edge15(5, 4); // cell 3
    XmEdge emptyEdge;
    std::vector<std::vector<XmEdge>> expectedCellsCellEdges;
    std::vector<XmEdge> emptyVec = {emptyEdge};
    std::vector<XmEdge> cellEdges;

    cellEdges.push_back(ugrid->GetCellEdge(0, -1));
    TS_ASSERT_EQUALS(emptyVec, cellEdges);

    cellEdges.clear();
    cellEdges.push_back(ugrid->GetCellEdge(0, ugrid->GetCellEdgeCount(0)));
    TS_ASSERT_EQUALS(emptyVec, cellEdges);

    cellEdges.clear();
    expectedCellsCellEdges = {{edge0, edge1, edge2, edge3},
                              {edge4, edge5, edge6, edge7},
                              {edge8, edge9, edge10, edge11},
                              {edge12, edge13, edge14, edge15}};
    for (int i(0); i < ugrid->GetCellCount(); i++)
    {
      for (int j(0); j < ugrid->GetCellEdgeCount(i); j++)
      {
        cellEdges.push_back(ugrid->GetCellEdge(i, j));
      }
      TS_ASSERT_EQUALS(expectedCellsCellEdges[i], cellEdges);
      cellEdges.clear();
    }
  }
  //! [snip_test_GetCellEdgeFromEdgeIndex2D]
  {
    XmEdge edge0(0, 1), edge1(1, 6), edge2(6, 5), edge3(5, 0); // Quad
    XmEdge edge4(1, 2), edge5(2, 7), edge6(7, 6), edge7(6, 1); // Pixel
    XmEdge edge8(2, 3), edge9(3, 7), edge10(7, 2);             // Triangle
    XmEdge edge11(3, 4), edge12(4, 8), edge13(8, 13), edge14(13, 12), edge15(12, 7),
      edge16(7, 3);                       // Polygon
    XmEdge edge17(7, 11), edge18(11, 10); // PolyLine
    XmEdge edge19(5, 9);                  // Line

    // 2D Shapes
    std::shared_ptr<XmUGrid> ugrid2d = TEST_XmUGrid2dLinear();
    TS_REQUIRE_NOT_NULL(ugrid2d);

    std::vector<std::vector<XmEdge>> expectedCellsCellEdges;
    expectedCellsCellEdges = {{edge0, edge1, edge2, edge3},
                              {edge4, edge5, edge6, edge7},
                              {edge8, edge9, edge10},
                              {edge11, edge12, edge13, edge14, edge15, edge16},
                              {edge17, edge18},
                              {edge19}};
    std::vector<XmEdge> cellEdges;
    for (int i(0); i < ugrid2d->GetCellCount(); i++)
    {
      for (int j(0); j < ugrid2d->GetCellEdgeCount(i); j++)
      {
        cellEdges.push_back(ugrid2d->GetCellEdge(i, j));
      }
      TS_ASSERT_EQUALS(expectedCellsCellEdges[i], cellEdges);
      cellEdges.clear();
    }
  }
  //! [snip_test_GetCellEdgeFromEdgeIndex2D]

  //! [snip_test_GetCellEdgeFromEdgeIndex3D]
  {
    // 3D Shapes
    std::shared_ptr<XmUGrid> ugrid3d = TEST_XmUGrid3dLinear();
    TS_REQUIRE_NOT_NULL(ugrid3d);

    // clang-format off
    std::vector<std::vector<XmEdge>> expectedCellsCellEdges =
    {
      {{0, 1}, {1, 5}, {5, 0}, {0, 15}, {1, 15}, {5, 15}}, // XMU_TETRA
      {{1, 2}, {2, 7}, {6, 7}, {1, 6}, {16, 17}, {17, 22}, {21, 22}, {16, 21}, {1, 16}, {2, 17}, {6, 21}, {7, 22}}, // XMU_VOXEL
      {{2, 3}, {3, 8}, {7, 8}, {2, 7}, {17, 18}, {18, 23}, {22, 23}, {17, 22}, {2, 17}, {3, 18}, {7, 22}, {8, 23}}, // XMU_HEXAHEDRON
      {{8, 9}, {8, 13}, {8, 23}, {9, 14}, {9, 24}, {13, 14}, {13, 28}, {14, 29}, {23, 24}, {23, 28}, {24, 29}, {28, 29}}, // XMU_POLYHEDRON
      {{3, 4}, {4, 18}, {18, 3}, {8, 9}, {9, 23}, {23, 8}, {3, 8}, {4, 9}, {18, 23}}, // XMU_WEDGE
      {{5, 6}, {6, 11}, {11, 10}, {10, 5}, {5, 20}, {6, 20}, {11, 20}, {10, 20}} // XMU_PYRAMID
    };
    // clang-format on
    std::vector<XmEdge> cellEdges;
    for (int i(0); i < ugrid3d->GetCellCount(); i++)
    {
      for (int j(0); j < ugrid3d->GetCellEdgeCount(i); j++)
      {
        cellEdges.push_back(ugrid3d->GetCellEdge(i, j));
      }
      TS_ASSERT_EQUALS(expectedCellsCellEdges[i], cellEdges);
      cellEdges.clear();
    }
  }
  //! [snip_test_GetCellEdgeFromEdgeIndex3D]
} // XmUGridUnitTests::testGetCellEdge

//------------------------------------------------------------------------------
/// \brief Test retrieving common cells from points
//------------------------------------------------------------------------------
void XmUGridUnitTests::testGetPointsAdjacentCells()
{
  //     0-----1-----2
  //     |  0  |  1  |
  //     3-----4-----5
  //     |  2  |  3  |
  //     6-----7-----8

  std::shared_ptr<XmUGrid> ugrid = TEST_XmUGridSimpleQuad();
  TS_REQUIRE_NOT_NULL(ugrid);

  VecInt expectedCells;
  VecInt points = {-1, 0};
  VecInt retrievedCells;
  retrievedCells = ugrid->GetPointsAdjacentCells(points);
  TS_ASSERT_EQUALS(expectedCells, retrievedCells);

  points = {0, -1};
  retrievedCells = ugrid->GetPointsAdjacentCells(points);
  TS_ASSERT_EQUALS(expectedCells, retrievedCells);

  points = {0, 8};
  retrievedCells = ugrid->GetPointsAdjacentCells(points);
  TS_ASSERT_EQUALS(expectedCells, retrievedCells);
  expectedCells.clear();
  points.clear();
  retrievedCells.clear();

  expectedCells = {0, 2};
  points = {3, 4};
  retrievedCells = ugrid->GetPointsAdjacentCells(points);
  TS_ASSERT_EQUALS(expectedCells, retrievedCells);
  expectedCells.clear();
  points.clear();
  retrievedCells.clear();

  expectedCells = {0};
  points = {0, 3};
  retrievedCells = ugrid->GetPointsAdjacentCells(points);
  TS_ASSERT_EQUALS(expectedCells, retrievedCells);
  expectedCells.clear();
  points.clear();
  retrievedCells.clear();

  points = {3, 4, 5};
  retrievedCells = ugrid->GetPointsAdjacentCells(points);
  TS_ASSERT_EQUALS(expectedCells, retrievedCells);
  expectedCells.clear();
  points.clear();
  retrievedCells.clear();

  points = {ugrid->GetPointCount(), 0};
  retrievedCells = ugrid->GetPointsAdjacentCells(points);
  TS_ASSERT_EQUALS(expectedCells, retrievedCells);

  points = {0, ugrid->GetPointCount()};
  retrievedCells = ugrid->GetPointsAdjacentCells(points);
  TS_ASSERT_EQUALS(expectedCells, retrievedCells);

} // XmUGridUnitTests::testGetPointsAdjacentCells

//! [snip_test_GetCellAdjacentCells]
//------------------------------------------------------------------------------
/// \brief Test retrieving Cell Neighbors
//------------------------------------------------------------------------------
void XmUGridUnitTests::testGetCellAdjacentCells()
{
  //     0-----1-----2
  //     |  0  |  1  |
  //     3-----4-----5
  //     |  2  |  3  |
  //     6-----7-----8

  std::shared_ptr<XmUGrid> ugrid = TEST_XmUGridSimpleQuad();
  TS_REQUIRE_NOT_NULL(ugrid);

  VecInt expectedCells;

  VecInt retrievedCells;
  retrievedCells = ugrid->GetCellAdjacentCells(-1);
  TS_ASSERT_EQUALS(expectedCells, retrievedCells);
  retrievedCells = ugrid->GetCellAdjacentCells(0);
  expectedCells = {2, 1, 3};
  TS_ASSERT_EQUALS(expectedCells, retrievedCells);
  expectedCells.clear();
  retrievedCells = ugrid->GetCellAdjacentCells(4);
  TS_ASSERT_EQUALS(expectedCells, retrievedCells);
  expectedCells.clear();
  retrievedCells = ugrid->GetCellAdjacentCells(5);
  TS_ASSERT_EQUALS(expectedCells, retrievedCells);
  expectedCells.clear();
  retrievedCells.clear();

  // 2D Shapes
  std::shared_ptr<XmUGrid> ugrid2d = TEST_XmUGrid2dLinear();
  TS_REQUIRE_NOT_NULL(ugrid2d);

  expectedCells = {1, 5};
  retrievedCells = ugrid2d->GetCellAdjacentCells(0);
  TS_ASSERT_EQUALS(expectedCells, retrievedCells);
  expectedCells = {0, 2, 3, 4};
  retrievedCells = ugrid2d->GetCellAdjacentCells(1);
  TS_ASSERT_EQUALS(expectedCells, retrievedCells);
  expectedCells = {1, 3, 4};
  retrievedCells = ugrid2d->GetCellAdjacentCells(2);
  TS_ASSERT_EQUALS(expectedCells, retrievedCells);
  expectedCells = {2, 1, 4};
  retrievedCells = ugrid2d->GetCellAdjacentCells(3);
  TS_ASSERT_EQUALS(expectedCells, retrievedCells);
  expectedCells = {1, 2, 3};
  retrievedCells = ugrid2d->GetCellAdjacentCells(4);
  TS_ASSERT_EQUALS(expectedCells, retrievedCells);
  expectedCells = {0};
  retrievedCells = ugrid2d->GetCellAdjacentCells(5);
  TS_ASSERT_EQUALS(expectedCells, retrievedCells);

  // 3D Shapes
  std::shared_ptr<XmUGrid> ugrid3d = TEST_XmUGrid3dLinear();
  TS_REQUIRE_NOT_NULL(ugrid3d);

  expectedCells = {1, 5};
  retrievedCells = ugrid3d->GetCellAdjacentCells(0);
  TS_ASSERT_EQUALS(expectedCells, retrievedCells);
  expectedCells = {0, 2, 5};
  retrievedCells = ugrid3d->GetCellAdjacentCells(1);
  TS_ASSERT_EQUALS(expectedCells, retrievedCells);
  expectedCells = {1, 4, 3};
  retrievedCells = ugrid3d->GetCellAdjacentCells(2);
  TS_ASSERT_EQUALS(expectedCells, retrievedCells);
  expectedCells = {4, 2};
  retrievedCells = ugrid3d->GetCellAdjacentCells(3);
  TS_ASSERT_EQUALS(expectedCells, retrievedCells);
  expectedCells = {2, 3};
  retrievedCells = ugrid3d->GetCellAdjacentCells(4);
  TS_ASSERT_EQUALS(expectedCells, retrievedCells);
  expectedCells = {0, 1};
  retrievedCells = ugrid3d->GetCellAdjacentCells(5);
  TS_ASSERT_EQUALS(expectedCells, retrievedCells);

} // XmUGridUnitTests::testGetCellAdjacentCells
//! [snip_test_GetCellAdjacentCells]

//------------------------------------------------------------------------------
/// \brief Test retrieving Adjacent Cell
//------------------------------------------------------------------------------
void XmUGridUnitTests::testGetCellEdgeAdjacentCells()
{
  //     0-----1-----2
  //     |  0  |  1  |
  //     3-----4-----5
  //     |  2  |  3  |
  //     6-----7-----8

  std::shared_ptr<XmUGrid> ugrid = TEST_XmUGridSimpleQuad();
  TS_REQUIRE_NOT_NULL(ugrid);

  VecInt expectedFail;
  VecInt2d expectedCells = {{}, {2}, {1}, {}};
  VecInt expected2dCells = {-1, 2, 1, -1};

  int adjacentCell;
  VecInt adjacentCells = ugrid->GetCellEdgeAdjacentCells(0, -1);
  TS_ASSERT_EQUALS(expectedFail, adjacentCells);
  adjacentCell = ugrid->GetCell2dEdgeAdjacentCell(0, -1);
  TS_ASSERT_EQUALS(-1, adjacentCell);

  for (int i(0); i < ugrid->GetCellEdgeCount(0); i++)
  {
    adjacentCells = ugrid->GetCellEdgeAdjacentCells(0, i);
    TS_ASSERT_EQUALS(expectedCells[i], adjacentCells);

    adjacentCell = ugrid->GetCell2dEdgeAdjacentCell(0, i);
    TS_ASSERT_EQUALS(expected2dCells[i], adjacentCell);
  }
  adjacentCells = ugrid->GetCellEdgeAdjacentCells(0, ugrid->GetCellEdgeCount(0));
  TS_ASSERT_EQUALS(expectedFail, adjacentCells);
  adjacentCell = ugrid->GetCell2dEdgeAdjacentCell(0, ugrid->GetCellEdgeCount(0));
  TS_ASSERT_EQUALS(-1, adjacentCell);

  // Test a cell in the middle of an hexahedron grid
  std::shared_ptr<XmUGrid> hexUgrid = TEST_XmUBuildHexahedronUgrid(5, 5, 5);
  TS_REQUIRE_NOT_NULL(hexUgrid);

  expectedCells = {{2, 6, 18},   {6, 7, 23},   {6, 10, 26},  {5, 6, 21},
                   {18, 34, 38}, {23, 38, 39}, {26, 38, 42}, {21, 37, 38},
                   {17, 18, 21}, {18, 19, 23}, {21, 26, 25}, {23, 26, 27}};

  for (int i(0); i < hexUgrid->GetCellEdgeCount(22); i++)
  {
    adjacentCells = hexUgrid->GetCellEdgeAdjacentCells(22, i);
    TS_ASSERT_EQUALS(expectedCells[i], adjacentCells);
  }
} // XmUGridUnitTests::testGetCellEdgeAdjacentCells
//------------------------------------------------------------------------------
/// \brief Test retrieving Adjacent Cell
//------------------------------------------------------------------------------
void XmUGridUnitTests::testEdgeAdjacentCells()
{
  //     0-----1-----2
  //     |  0  |  1  |
  //     3-----4-----5
  //     |  2  |  3  |
  //     6-----7-----8

  std::shared_ptr<XmUGrid> ugrid = TEST_XmUGridSimpleQuad();
  TS_REQUIRE_NOT_NULL(ugrid);

  VecInt expectedFail;
  VecInt2d expectedCells = {{0, 1}, {0, 2}, {0}};
  std::vector<XmEdge> edges = {{1, 4}, {3, 4}, {0, 3}};

  VecInt adjacentCells = ugrid->GetEdgeAdjacentCells(XmEdge(-1, -1));
  TS_ASSERT_EQUALS(expectedFail, adjacentCells);
  for (int i(0); i < edges.size(); i++)
  {
    adjacentCells = ugrid->GetEdgeAdjacentCells(edges[i]);
    TS_ASSERT_EQUALS(expectedCells[i], adjacentCells);
  }

  XmEdge badEdge(0, ugrid->GetPointCount());
  adjacentCells = ugrid->GetEdgeAdjacentCells(badEdge);
  TS_ASSERT_EQUALS(expectedFail, adjacentCells);

} // XmUGridUnitTests::testEdgeAdjacentCells

//------------------------------------------------------------------------------
/// \brief Test retrieving Cell Face
//------------------------------------------------------------------------------
void XmUGridUnitTests::testGetCell3dFacePoints()
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
  std::shared_ptr<XmUGrid> ugrid2d = TEST_XmUGrid2dLinear();
  TS_REQUIRE_NOT_NULL(ugrid2d);

  cellFaces = ugrid2d->GetCell3dFacePoints(-1, 0);
  TS_ASSERT_EQUALS(emptyCellFaces, cellFaces);
  cellFaces = ugrid2d->GetCell3dFacePoints(0, -1);
  TS_ASSERT_EQUALS(emptyCellFaces, cellFaces);

  for (int i(0); i < ugrid2d->GetCellCount(); i++)
  {
    cellFaces = ugrid2d->GetCell3dFacePoints(i, 0);
    TS_ASSERT_EQUALS(expectedCellFaces[i], cellFaces);
  }

  cellFaces = ugrid2d->GetCell3dFacePoints(ugrid2d->GetCellCount(), 0);
  TS_ASSERT_EQUALS(emptyCellFaces, cellFaces);
  cellFaces = ugrid2d->GetCell3dFacePoints(0, 1);
  TS_ASSERT_EQUALS(emptyCellFaces, cellFaces);

  // 3D Shapes
  std::shared_ptr<XmUGrid> ugrid3d = TEST_XmUGrid3dLinear();
  TS_REQUIRE_NOT_NULL(ugrid3d);

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
                       {9, 8, 13, 14},
                       {8, 9, 24, 23},
                       {9, 14, 29, 24},
                       {14, 13, 28, 29},
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
  for (int i(0); i < ugrid3d->GetCellCount(); i++)
  {
    for (int j(0); j < ugrid3d->GetCell3dFaceCount(i); j++, currId++)
    {
      cellFaces = ugrid3d->GetCell3dFacePoints(i, j);
      TS_ASSERT_EQUALS(expectedCellFaces[currId], cellFaces);
    }
  }
} // XmUGridUnitTests::testGetCell3dFacePoints

//! [snip_test_GetCell3dFaceAdjacentCell]
//------------------------------------------------------------------------------
/// \brief Test retrieving Cell Face Neighbor
//------------------------------------------------------------------------------
void XmUGridUnitTests::testGetCell3dFaceAdjacentCell()
{
  // 2 hexahedrons
  int rows = 3;
  int cols = 2;
  int lays = 2;

  std::shared_ptr<xms::XmUGrid> grid = TEST_XmUBuildHexahedronUgrid(rows, cols, lays);
  TS_REQUIRE_NOT_NULL(grid);

  // clang-format off
  VecInt expectedNeighbor = {-1, -1, -1, 1, -1, -1, -1, -1, 0, -1, -1, -1};
  VecInt expectedFace =     {-1, -1, -1, 2, -1, -1, -1, -1, 3, -1, -1, -1};
  // clang-format on

  int expectedIdx = 0;
  int neighborCellIdx;

  neighborCellIdx = grid->GetCell3dFaceAdjacentCell(-1, 0);
  TS_ASSERT_EQUALS(-1, neighborCellIdx);
  neighborCellIdx = grid->GetCell3dFaceAdjacentCell(0, -1);
  TS_ASSERT_EQUALS(-1, neighborCellIdx);

  for (int cellIdx = 0; cellIdx < grid->GetCellCount(); cellIdx++)
  {
    for (int faceIdx = 0; faceIdx < grid->GetCell3dFaceCount(cellIdx); faceIdx++, expectedIdx++)
    {
      // Check first function
      neighborCellIdx = grid->GetCell3dFaceAdjacentCell(cellIdx, faceIdx);
      TS_ASSERT_EQUALS(expectedNeighbor[expectedIdx], neighborCellIdx);

      // Check overload function
      int neighborFaceIdx = -1;
      grid->GetCell3dFaceAdjacentCell(cellIdx, faceIdx, neighborCellIdx, neighborFaceIdx);
      TS_ASSERT_EQUALS(expectedNeighbor[expectedIdx], neighborCellIdx);
      TS_ASSERT_EQUALS(expectedFace[expectedIdx], neighborFaceIdx);

      // Check that faces are the same
      VecInt expectedFacePt = grid->GetCell3dFacePoints(cellIdx, faceIdx);
      std::sort(expectedFacePt.begin(), expectedFacePt.end());
      VecInt neighborFacePt = grid->GetCell3dFacePoints(neighborCellIdx, neighborFaceIdx);
      std::sort(neighborFacePt.begin(), neighborFacePt.end());
      if (!expectedFacePt.empty() && !neighborFacePt.empty())
      {
        TS_ASSERT_EQUALS(expectedFacePt, neighborFacePt);
      }
    }
  }
  neighborCellIdx = grid->GetCell3dFaceAdjacentCell(grid->GetCellCount(), 0);
  TS_ASSERT_EQUALS(-1, neighborCellIdx);
  neighborCellIdx = grid->GetCell3dFaceAdjacentCell(0, grid->GetCellCount());
  TS_ASSERT_EQUALS(-1, neighborCellIdx);

  rows = 3;
  cols = 3;
  lays = 3;
  grid = TEST_XmUBuildHexahedronUgrid(rows, cols, lays);
  TS_REQUIRE_NOT_NULL(grid);

  expectedNeighbor.clear();
  // clang-format off
  expectedNeighbor = {-1, 1, -1, 2, -1, 4, 0, -1, -1, 3, -1, 5, -1, 3, 0, -1, -1, 6, 2, -1, 1, -1, -1, 7, -1, 5, -1, 6, 0, -1, 4, -1, -1, 7, 1, -1, -1, 7, 4, -1, 2, -1, 6, -1, 5, -1, 3, -1};
  expectedFace =     {-1, 0, -1, 2, -1, 4, 1, -1, -1, 2, -1, 4, -1, 0, 3, -1, -1, 4, 1, -1, 3, -1, -1, 4, -1, 0, -1, 2, 5, -1, 1, -1, -1, 2, 5, -1, -1, 0, 3, -1, 5, -1, 1, -1, 3, -1, 5, -1};
  // clang-format on

  expectedIdx = 0;
  for (int cellIdx = 0; cellIdx < grid->GetCellCount(); ++cellIdx)
  {
    for (int faceIdx = 0; faceIdx < grid->GetCell3dFaceCount(cellIdx); faceIdx++, expectedIdx++)
    {
      // Check first function
      neighborCellIdx = grid->GetCell3dFaceAdjacentCell(cellIdx, faceIdx);
      TS_ASSERT_EQUALS(expectedNeighbor[expectedIdx], neighborCellIdx);

      // Check overload function
      int neighborFaceIdx = -1;
      grid->GetCell3dFaceAdjacentCell(cellIdx, faceIdx, neighborCellIdx, neighborFaceIdx);
      TS_ASSERT_EQUALS(expectedNeighbor[expectedIdx], neighborCellIdx);
      TS_ASSERT_EQUALS(expectedFace[expectedIdx], neighborFaceIdx);

      // Check that faces are the same
      VecInt expectedFacePt = grid->GetCell3dFacePoints(cellIdx, faceIdx);
      std::sort(expectedFacePt.begin(), expectedFacePt.end());
      VecInt neighborFacePt = grid->GetCell3dFacePoints(neighborCellIdx, neighborFaceIdx);
      std::sort(neighborFacePt.begin(), neighborFacePt.end());
      if (!expectedFacePt.empty() && !neighborFacePt.empty())
      {
        TS_ASSERT_EQUALS(expectedFacePt, neighborFacePt);
      }
    }
  }
} // XmUGridUnitTests::testGetCell3dFaceAdjacentCell
//! [snip_test_GetCell3dFaceAdjacentCell]

//! [snip_test_GetPointAdjacentPoints]
//------------------------------------------------------------------------------
/// \brief Test GetPointAdjacentPoints and GetPointAdjacentLocations.
//------------------------------------------------------------------------------
void XmUGridUnitTests::testGetPointAdjacentPoints()
{
  //     0-----1-----2
  //     |  0  |  1  |
  //     3-----4-----5
  //     |  2  |  3  |
  //     6-----7-----8

  std::shared_ptr<xms::XmUGrid> grid = TEST_XmUGridSimpleQuad();
  TS_REQUIRE_NOT_NULL(grid);

  VecInt attachedIdxs;
  grid->GetPointAdjacentPoints(0, attachedIdxs);
  VecInt expectedIdxs = {1, 3};
  TS_ASSERT_EQUALS(expectedIdxs, attachedIdxs);
  grid->GetPointAdjacentPoints(3, attachedIdxs);
  expectedIdxs = {0, 4, 6};
  TS_ASSERT_EQUALS(expectedIdxs, attachedIdxs);
  grid->GetPointAdjacentPoints(4, attachedIdxs);
  expectedIdxs = {1, 3, 5, 7};
  TS_ASSERT_EQUALS(expectedIdxs, attachedIdxs);
  VecPt3d attachedPts;
  grid->GetPointAdjacentLocations(0, attachedPts);
  VecPt3d expectedPts = {{10, 10, 0}, {0, 0, 0}};
  TS_ASSERT_EQUALS(expectedPts, attachedPts);
  grid->GetPointAdjacentLocations(3, attachedPts);
  expectedPts = {{0, 10, 0}, {10, 0, 0}, {0, -10, 0}};
  TS_ASSERT_EQUALS(expectedPts, attachedPts);
  grid->GetPointAdjacentLocations(4, attachedPts);
  expectedPts = {{10, 10, 0}, {0, 0, 0}, {20, 0, 0}, {10, -10, 0}};
  TS_ASSERT_EQUALS(expectedPts, attachedPts);
} // XmUGridUnitTests::testGetPointAdjacentPoints
//! [snip_test_GetPointAdjacentPoints]

//! [snip_test_GetCellPlanViewPolygon]
//------------------------------------------------------------------------------
/// \brief Test getting the plan view polygon of a cell.
//------------------------------------------------------------------------------
void XmUGridUnitTests::testGetCellPlanViewPolygon()
{
  // 2d
  std::shared_ptr<xms::XmUGrid> grid2d = TEST_XmUGrid2dLinear();
  TS_REQUIRE_NOT_NULL(grid2d);

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
  TS_ASSERT(!grid2d->GetCellPlanViewPolygon(-1, viewPolygon));
  TS_ASSERT_EQUALS(empty, viewPolygon);
  TS_ASSERT(!grid2d->GetCellPlanViewPolygon(grid2d->GetCellCount(), viewPolygon));
  TS_ASSERT_EQUALS(empty, viewPolygon);
  // Regular testing
  for (int i = 0; i < grid2d->GetCellCount(); ++i)
  {
    // Should return true for the first 4 cells, and false for the last 2
    TS_ASSERT(grid2d->GetCellPlanViewPolygon(i, viewPolygon) != i >= 4);
    TS_ASSERT_EQUALS(expectedPolygons[i], viewPolygon);
  }

  // 3d
  std::shared_ptr<XmUGrid> ugrid3d = TEST_XmUGrid3dLinear();
  TS_REQUIRE_NOT_NULL(ugrid3d);

  expectedPolygons = {{{0, 0, 0}, {10, 0, 0}, {0, 10, 0}},
                      {{20, 0, 0}, {20, 10, 0}, {10, 10, 0}, {10, 0, 0}},
                      {{30, 0, 0}, {30, 10, 0}, {20, 10, 0}, {20, 0, 0}},
                      {{40, 10, 0}, {40, 20, 0}, {30, 20, 0}, {30, 10, 0}},
                      {{30, 0, 0}, {40, 0, 0}, {40, 10, 0}, {30, 10, 0}},
                      {{0, 10, 0}, {10, 10, 0}, {10, 20, 0}, {0, 20, 0}}};

  for (int i = 0; i < ugrid3d->GetCellCount(); ++i)
  {
    TS_ASSERT(ugrid3d->GetCellPlanViewPolygon(i, viewPolygon));
    TS_ASSERT_EQUALS(expectedPolygons[i], viewPolygon);
  }

  std::shared_ptr<xms::XmUGrid> chevronUgrid = TEST_XmUBuild3DChevronUgrid();
  TS_REQUIRE_NOT_NULL(chevronUgrid);

  expectedPolygons = {{{0.0, 0.0, 0.0}, {20.0, 10.0, 0.0}, {40.0, 0.0, 0.0}, {20.0, 50.0, 0.0}}};
  TS_ASSERT(chevronUgrid->GetCellPlanViewPolygon(0, viewPolygon));
  TS_ASSERT_EQUALS(expectedPolygons[0], viewPolygon);

} // XmUGridUnitTests::testGetCellPlanViewPolygon
//! [snip_test_GetCellPlanViewPolygon]

//------------------------------------------------------------------------------
/// \brief Test getting the plan view points of a cell.
//------------------------------------------------------------------------------
void XmUGridUnitTests::testGetCellPlanViewPolygonMultiSideFace()
{
  // 3d - For vertically prismatic cells returns the unique plan view points for side faces
  //      in sorted order. For cells that aren't vertically prismatic returns an empty vector.
  VecPt3d points = {
    {0, 0, 0}, {1, 0, 0}, {2, 0, 0}, {0, 0, 1}, {1, 0, 1},
    {2, 0, 1}, {0, 0, 2}, {2, 0, 2},                       // front face
    {0, 1, 2}, {1, 1, 2}, {2, 1, 2},                       // points midway back
    {0, 2, 0}, {2, 2, 0}, {0, 2, 2}, {1, 2, 2}, {2, 2, 2}, // back points
    {4, 2, 0}, {3, 1, 2}                                   // tetrahedron
  };
  // clang-format off
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
  // clang-format on
  std::shared_ptr<XmUGrid> ugrid3d = XmUGrid::New(points, cells);
  TS_REQUIRE_NOT_NULL(ugrid3d);

  // vertically prismatic
  VecPt3d cellPoints;
  ugrid3d->GetCellPlanViewPolygon(0, cellPoints);
  VecPt3d expectedGetCellPoints = {{1, 0, 0}, {2, 0, 0}, {2, 1, 0}, {2, 2, 0},
                                   {1, 2, 0}, {0, 2, 0}, {0, 1, 0}, {0, 0, 0}};
  TS_ASSERT_EQUALS(expectedGetCellPoints, cellPoints);

  // not vertically prismatic
  ugrid3d->GetCellPlanViewPolygon(1, cellPoints);
  expectedGetCellPoints = {{2, 0, 0}, {4, 2, 0}, {2, 2, 0}};
  TS_ASSERT_EQUALS(expectedGetCellPoints, cellPoints);
} // XmUGridUnitTests::testGetCellPlanViewPolygonMultiSideFace
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

  std::shared_ptr<XmUGrid> ugrid = TEST_XmUGridSimpleQuad();
  TS_REQUIRE_NOT_NULL(ugrid);

  Pt3d validPt = {5.0, 5.0, 0.0};
  Pt3d invalid = {500.0, 500.0, 0.0};

  TS_ASSERT(ugrid->IsValidPointChange(4, validPt));
  TS_ASSERT(!ugrid->IsValidPointChange(4, invalid));

  std::shared_ptr<XmUGrid> ugrid3d = TEST_XmUBuildHexahedronUgrid(4, 4, 4);

  validPt = ugrid3d->GetPointLocation(21);
  validPt.x += 0.5;
  validPt.y += 0.5;
  validPt.z += 0.5;
  TS_ASSERT(ugrid3d->IsValidPointChange(21, validPt));
  TS_ASSERT(!ugrid3d->IsValidPointChange(21, invalid));

  TS_ASSERT(ugrid->SetPointLocation(4, validPt));
  TS_ASSERT(ugrid->SetPointLocation(4, invalid));
  TS_ASSERT(ugrid3d->SetPointLocation(21, validPt));
  TS_ASSERT(ugrid3d->SetPointLocation(21, invalid));
} // XmUGridUnitTests::testIsCellValidWithPointChange

//! [snip_test_PointFunctions]
//------------------------------------------------------------------------------
/// \brief Test various point functions
//------------------------------------------------------------------------------
void XmUGridUnitTests::testPointFunctions()
{
  std::shared_ptr<XmUGrid> ugrid = TEST_XmUGridSimpleQuad();
  TS_REQUIRE_NOT_NULL(ugrid);

  // Test GetPointCount
  TS_ASSERT_EQUALS(ugrid->GetPointCount(), 9);
  VecPt3d points = {{0, 10, 0}, {10, 10, 0}, {20, 10, 0},  {0, 0, 0},   {10, 0, 0},
                    {20, 0, 0}, {0, -10, 0}, {10, -10, 0}, {20, -10, 0}};

  // Test Locations
  TS_ASSERT_EQUALS(ugrid->GetLocations(), points);
  for (int i = 0; i < points.size(); ++i)
  {
    TS_ASSERT_EQUALS(points[i], ugrid->GetPointLocation(i));
  }

  // Test SetPointLocation & GetPointLocation
  Pt3d invalid = {100, 100, 100};
  Pt3d valid = {5, 5, 5};
  TS_ASSERT(!ugrid->IsValidPointChange(4, invalid));
  TS_ASSERT(ugrid->SetPointLocation(4, valid));
  TS_ASSERT_EQUALS(valid, ugrid->GetPointLocation(4));

  VecInt pointIndices = {0, 3, 6};
  VecPt3d expectedPoints = {{0, 10, 0}, {0, 0, 0}, {0, -10, 0}};
  VecPt3d pointsPt3d;

  // Test GetPointsLocations
  pointsPt3d = ugrid->GetPointsLocations(pointIndices);
  TS_ASSERT_EQUALS(expectedPoints, pointsPt3d);

  // Test GetExtents
  Pt3d min, max, expectedMin = {0, -10, 0}, expectedMax = {20, 10, 5};
  ugrid->GetExtents(min, max);
  TS_ASSERT_EQUALS(expectedMin, min);
  TS_ASSERT_EQUALS(expectedMax, max);

  // Test GetPointAdjacentCells
  VecInt expectedCells = {0, 2};
  VecInt cellsAssociated = ugrid->GetPointAdjacentCells(3);
  TS_ASSERT_EQUALS(expectedCells, cellsAssociated);

  // Test GetPointsAdjacentCells
  VecInt expectedCommonCells = {0, 1};
  VecInt pointIndex = {1};
  VecInt commonCells = ugrid->GetPointsAdjacentCells(pointIndex);
  TS_ASSERT_EQUALS(expectedCells, cellsAssociated);

} // XmUGridUnitTests::testPointFunctions
//! [snip_test_PointFunctions]

//! [snip_test_CellFunctions]
//------------------------------------------------------------------------------
/// \brief Test various cell functions
//------------------------------------------------------------------------------
void XmUGridUnitTests::testCellFunctions()
{
  std::shared_ptr<XmUGrid> ugrid = TEST_XmUGridSimpleQuad();
  TS_REQUIRE_NOT_NULL(ugrid);

  // Test GetCellPoints
  VecInt pointsOfCell = ugrid->GetCellPoints(0);
  VecInt expectedPoints = {0, 3, 4, 1};
  TS_ASSERT_EQUALS(expectedPoints, pointsOfCell);
  // Test overload
  ugrid->GetCellPoints(0, pointsOfCell);
  TS_ASSERT_EQUALS(expectedPoints, pointsOfCell);
  VecPt3d locations;
  ugrid->GetCellLocations(0, locations);
  VecPt3d expectedLocations = {{0, 10, 0}, {0, 0, 0}, {10, 0, 0}, {10, 10, 0}};
  TS_ASSERT_EQUALS(expectedLocations, locations);

  // Test GetCellExtents
  Pt3d min, max;
  ugrid->GetCellExtents(0, min, max);
  TS_ASSERT_EQUALS(Pt3d(0, 0, 0), min);
  TS_ASSERT_EQUALS(Pt3d(10, 10, 0), max);

  // Test GetCellType
  TS_ASSERT_EQUALS(XMU_QUAD, ugrid->GetCellType(0));

  // Test GetDimensionCounts
  VecInt expectedDimensions = {0, 0, 4, 0};
  TS_ASSERT_EQUALS(expectedDimensions, ugrid->GetDimensionCounts());

  // Test GetCellDimension
  TS_ASSERT_EQUALS(2, ugrid->GetCellDimension(0));

  // Test GetCellCentroid
  Pt3d centroid;
  TS_ASSERT(ugrid->GetCellCentroid(0, centroid));
  TS_ASSERT_EQUALS(Pt3d(5, 5, 0), centroid);
} // XmUGridUnitTests::testCellFunctions
//! [snip_test_CellFunctions]
//! [snip_test_CellstreamFunctions]
//------------------------------------------------------------------------------
/// \brief Test various cell functions
//------------------------------------------------------------------------------
void XmUGridUnitTests::testCellstreamFunctions()
{
  std::shared_ptr<XmUGrid> ugrid = TEST_XmUGridSimpleQuad();
  TS_REQUIRE_NOT_NULL(ugrid);

  // Test GetCellstream
  VecInt cellstream = ugrid->GetCellstream();
  VecInt expectedCellstream = {XMU_QUAD, 4, 0, 3, 4, 1, XMU_QUAD, 4, 1, 4, 5, 2,
                               XMU_QUAD, 4, 3, 6, 7, 4, XMU_QUAD, 4, 4, 7, 8, 5};
  TS_ASSERT_EQUALS(expectedCellstream, cellstream);

  // Test GetCellCellstream
  ugrid->GetCellCellstream(0, cellstream);
  expectedCellstream = {XMU_QUAD, 4, 0, 3, 4, 1};
  TS_ASSERT_EQUALS(expectedCellstream, cellstream);

} // XmUGridUnitTests::testCellstreamFunctions
//! [snip_test_CellstreamFunctions]
//! [snip_test_CellEdgeAdjacentCellFunctions]
//------------------------------------------------------------------------------
/// \brief Test all get adjacent cell functions
//------------------------------------------------------------------------------
void XmUGridUnitTests::testCellEdgeAdjacentCellFunctions()
{
  //     0-----1-----2
  //     |  0  |  1  |
  //     3-----4-----5
  //     |  2  |  3  |
  //     6-----7-----8
  std::shared_ptr<XmUGrid> ugrid = TEST_XmUGridSimpleQuad();
  TS_REQUIRE_NOT_NULL(ugrid);

  // Get Adjacent Cells from cell and edge
  VecInt2d expectedCells = {{}, {2}, {1}, {}};
  VecInt expected2dCells = {-1, 2, 1, -1};
  int adjacentCell;
  VecInt adjacentCells;
  for (int i(0); i < ugrid->GetCellEdgeCount(0); i++)
  {
    adjacentCells = ugrid->GetCellEdgeAdjacentCells(0, i);
    TS_ASSERT_EQUALS(expectedCells[i], adjacentCells);
    // For 2D cells only
    adjacentCell = ugrid->GetCell2dEdgeAdjacentCell(0, i);
    TS_ASSERT_EQUALS(expected2dCells[i], adjacentCell);
  }

  // Get Adjacent cells from given Edge
  VecInt2d expectedCellsFromEdge = {{0, 1}, {0, 2}, {0}};
  std::vector<XmEdge> edges = {{1, 4}, {3, 4}, {0, 3}};
  adjacentCells = ugrid->GetEdgeAdjacentCells(XmEdge(-1, -1));
  for (int i(0); i < edges.size(); i++)
  {
    adjacentCells = ugrid->GetEdgeAdjacentCells(edges[i]);
    TS_ASSERT_EQUALS(expectedCellsFromEdge[i], adjacentCells);
  }
} // XmUGridUnitTests::testCellAdjacentCellFunctions
//! [snip_test_CellEdgeAdjacentCellFunctions]
//! [snip_test_CellEdges]
//------------------------------------------------------------------------------
/// \brief Test various cell functions
//------------------------------------------------------------------------------
void XmUGridUnitTests::testCellEdges()
{
  std::shared_ptr<XmUGrid> ugrid = TEST_XmUGridSimpleQuad();
  TS_REQUIRE_NOT_NULL(ugrid);

  // Test GetCellEdges
  std::vector<XmEdge> edges = ugrid->GetCellEdges(0);
  std::vector<XmEdge> expectededges = {{0, 3}, {3, 4}, {4, 1}, {1, 0}};
  TS_ASSERT_EQUALS(expectededges, edges);

} // XmUGridUnitTests::testCellEdges
//! [snip_test_CellEdges]
//! [snip_test_Cell3dFaceFunctions]
//------------------------------------------------------------------------------
/// \brief Test various get face functions
//------------------------------------------------------------------------------
void XmUGridUnitTests::testCell3dFaceFunctions()
{
  // 3D Shapes
  std::shared_ptr<XmUGrid> ugrid3d = TEST_XmUGrid3dLinear();
  TS_REQUIRE_NOT_NULL(ugrid3d);

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
                                {9, 8, 13, 14},
                                {8, 9, 24, 23},
                                {9, 14, 29, 24},
                                {14, 13, 28, 29},
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
  for (int i(0); i < ugrid3d->GetCellCount(); i++)
  {
    for (int j(0); j < ugrid3d->GetCell3dFaceCount(i); j++, expectedIdx++)
    {
      cellFace = ugrid3d->GetCell3dFacePoints(i, j);
      TS_ASSERT_EQUALS(expectedCellFaces[expectedIdx], cellFace);
    }
  }

  VecInt2d cellFaces;
  expectedIdx = 0;
  for (int i(0); i < ugrid3d->GetCellCount(); i++)
  {
    cellFaces = ugrid3d->GetCell3dFacesPoints(i);
    TS_ASSERT_EQUALS(cellFaces.size(), ugrid3d->GetCell3dFaceCount(i));
    for (int j(0); j < ugrid3d->GetCell3dFaceCount(i); j++, expectedIdx++)
    {
      TS_ASSERT_EQUALS(expectedCellFaces[expectedIdx], cellFaces[j]);
    }
  }

  VecInt faceOrientations;
  for (int cellIdx = 0; cellIdx < ugrid3d->GetCellCount(); ++cellIdx)
  {
    for (int faceIdx = 0; faceIdx < ugrid3d->GetCell3dFaceCount(cellIdx); ++faceIdx)
    {
      faceOrientations.push_back(ugrid3d->GetCell3dFaceOrientation(cellIdx, faceIdx));
    }
  }

  VecInt expectedFaceOrientations = {
    // Tetra
    XMU_ORIENTATION_SIDE, XMU_ORIENTATION_TOP, XMU_ORIENTATION_SIDE, XMU_ORIENTATION_BOTTOM,
    // Voxel
    XMU_ORIENTATION_SIDE, XMU_ORIENTATION_SIDE, XMU_ORIENTATION_SIDE, XMU_ORIENTATION_SIDE,
    XMU_ORIENTATION_BOTTOM, XMU_ORIENTATION_TOP,
    // Hexahedron
    XMU_ORIENTATION_SIDE, XMU_ORIENTATION_SIDE, XMU_ORIENTATION_SIDE, XMU_ORIENTATION_SIDE,
    XMU_ORIENTATION_BOTTOM, XMU_ORIENTATION_TOP,
    // Polyhedron
    XMU_ORIENTATION_BOTTOM, XMU_ORIENTATION_SIDE, XMU_ORIENTATION_SIDE, XMU_ORIENTATION_SIDE,
    XMU_ORIENTATION_SIDE, XMU_ORIENTATION_TOP,
    // Wedge
    XMU_ORIENTATION_SIDE, XMU_ORIENTATION_SIDE, XMU_ORIENTATION_BOTTOM, XMU_ORIENTATION_TOP,
    XMU_ORIENTATION_SIDE,
    // Pyramid
    XMU_ORIENTATION_BOTTOM, XMU_ORIENTATION_SIDE, XMU_ORIENTATION_TOP, XMU_ORIENTATION_TOP,
    XMU_ORIENTATION_SIDE};

  TS_ASSERT_EQUALS(expectedFaceOrientations, faceOrientations);
} // XmUGridUnitTests::testCell3dFaceFunctions
//! [snip_test_Cell3dFaceFunctions]
//------------------------------------------------------------------------------
/// \brief Test face orientation for 3D grid of hexahedrons.
//------------------------------------------------------------------------------
void XmUGridUnitTests::testGetCell3dFaceOrientationHexahedrons()
{
  std::vector<std::shared_ptr<XmUGrid>> grids;

  // hexahedron grid with unknown (actually down) cell order
  std::shared_ptr<XmUGrid> grid = TEST_XmUBuildHexahedronUgrid(4, 4, 4, Pt3d());
  grids.push_back(grid);

  // hexahedron grid with increasing down cell order
  grid = TEST_XmUBuildHexahedronUgrid(4, 4, 4, Pt3d());
  grid->SetCellOrder(xms::XMU_CELL_ORDER_INCREASING_DOWN);
  grids.push_back(grid);

  // hexahedron grid with increasing up cell order
  grid = TEST_XmUBuildIncreasingUpHexahedronUgrid(4, 4, 4, Pt3d());
  grid->SetCellOrder(xms::XMU_CELL_ORDER_INCREASING_UP);
  grids.push_back(grid);

  for (auto xmUGrid : grids)
  {
    for (int cellIdx = 0; cellIdx < xmUGrid->GetCellCount(); ++cellIdx)
    {
      TS_ASSERT_EQUALS(XMU_ORIENTATION_SIDE, xmUGrid->GetCell3dFaceOrientation(cellIdx, 0));
      TS_ASSERT_EQUALS(XMU_ORIENTATION_SIDE, xmUGrid->GetCell3dFaceOrientation(cellIdx, 1));
      TS_ASSERT_EQUALS(XMU_ORIENTATION_SIDE, xmUGrid->GetCell3dFaceOrientation(cellIdx, 2));
      TS_ASSERT_EQUALS(XMU_ORIENTATION_SIDE, xmUGrid->GetCell3dFaceOrientation(cellIdx, 3));
      TS_ASSERT_EQUALS(XMU_ORIENTATION_TOP, xmUGrid->GetCell3dFaceOrientation(cellIdx, 4));
      TS_ASSERT_EQUALS(XMU_ORIENTATION_BOTTOM, xmUGrid->GetCell3dFaceOrientation(cellIdx, 5));
    }
  }
} // XmUGridUnitTests::testGetCell3dFaceOrientationHexahedrons
//------------------------------------------------------------------------------
/// \brief Test face orientation for concave cell where a triangle from the
///        first two points in the top face to the centroid create a triangle
///        with a normal pointing down rather than up.
//------------------------------------------------------------------------------
void XmUGridUnitTests::testGetCell3dFaceOrientationConcaveCell()
{
  // clang-format off
  // vertically prismatic concave cell
  VecPt3d nodes = {
    Pt3d(1620022.8468, 6134363.759, 0),    Pt3d(1620009.9411, 6134414.9476, 0),
    Pt3d(1619994.9996, 6134289.4991, 0),   Pt3d(1619866.1047, 6134542.8755, 0),
    Pt3d(1619745.5374, 6134167.0467, 0),   Pt3d(1619829.9996, 6134192.9991, 0),
    Pt3d(1619773.3077, 6134545.2322, 0),   Pt3d(1619710.0815, 6134182.8542, 0),
    Pt3d(1619693.1618, 6134208.2547, 0),   Pt3d(1619645.5529, 6134438.0278, 0),
    Pt3d(1619774.9993, 6134371.9982, 0),   Pt3d(1620022.8468, 6134363.759, -10),
    Pt3d(1620009.9411, 6134414.9476, -10), Pt3d(1619994.9996, 6134289.4991, -10),
    Pt3d(1619866.1047, 6134542.8755, -10), Pt3d(1619745.5374, 6134167.0467, -10),
    Pt3d(1619829.9996, 6134192.9991, -10), Pt3d(1619773.3077, 6134545.2322, -10),
    Pt3d(1619710.0815, 6134182.8542, -10), Pt3d(1619693.1618, 6134208.2547, -10),
    Pt3d(1619645.5529, 6134438.0278, -10), Pt3d(1619774.9993, 6134371.9982, -10) };
  VecInt elements = {
    XMU_POLYHEDRON,
    13, // number of faces
    11, 5, 10, 2, 0, 1, 3, 6, 9, 8, 7, 4, // top
    11, 16, 15, 18, 19, 20, 17, 14, 12, 11, 13, 21, // bottom
    4, 5, 16, 21, 10, // sides
    4, 10, 21, 13, 2,
    4, 2, 13, 11, 0,
    4, 0, 11, 12, 1,
    4, 1, 12, 14, 3,
    4, 3, 14, 17, 6,
    4, 6, 17, 20, 9,
    4, 9, 20, 19, 8,
    4, 8, 19, 18, 7,
    4, 7, 18, 15, 4,
    4, 4, 1, 16, 5
  };
  // clang-format on

  std::shared_ptr<XmUGrid> xmUGrid = XmUGrid::New(nodes, elements);
  VecInt actual;
  for (int faceIdx = 0; faceIdx < xmUGrid->GetCell3dFaceCount(0); ++faceIdx)
  {
    actual.push_back(xmUGrid->GetCell3dFaceOrientation(0, faceIdx));
  }
  VecInt expected = {XMU_ORIENTATION_TOP,  XMU_ORIENTATION_BOTTOM, XMU_ORIENTATION_SIDE,
                     XMU_ORIENTATION_SIDE, XMU_ORIENTATION_SIDE,   XMU_ORIENTATION_SIDE,
                     XMU_ORIENTATION_SIDE, XMU_ORIENTATION_SIDE,   XMU_ORIENTATION_SIDE,
                     XMU_ORIENTATION_SIDE, XMU_ORIENTATION_SIDE,   XMU_ORIENTATION_SIDE,
                     XMU_ORIENTATION_SIDE};
  TS_ASSERT_EQUALS(expected, actual);
} // XmUGridUnitTests::testFaceOrientationConcaveCell
//------------------------------------------------------------------------------
/// \brief Test calculate cell numbering for an increasing up grid.
//------------------------------------------------------------------------------
void XmUGridUnitTests::testGetCellNumberingOneCell()
{
  std::shared_ptr<XmUGrid> xmUGrid = TEST_XmUBuildHexahedronUgrid(2, 2, 2, Pt3d());
  TS_ASSERT_EQUALS(XMU_CELL_ORDER_UNKNOWN, xmUGrid->GetCellOrder());
  TS_ASSERT_EQUALS(XMU_CELL_ORDER_UNKNOWN, xmUGrid->CalculateCellOrder())
} // XmUGridUnitTests::testGetCellNumberingOneCell
//------------------------------------------------------------------------------
/// \brief Test calculate cell numbering for an increasing down grid.
//------------------------------------------------------------------------------
void XmUGridUnitTests::testCalculateCellNumberingIncreasingDown()
{
  std::shared_ptr<XmUGrid> xmUGrid = TEST_XmUBuildHexahedronUgrid(3, 2, 3, Pt3d());
  TS_ASSERT_EQUALS(XMU_CELL_ORDER_UNKNOWN, xmUGrid->GetCellOrder());
  TS_ASSERT_EQUALS(XMU_CELL_ORDER_INCREASING_DOWN, xmUGrid->CalculateCellOrder())
} // XmUGridUnitTests::testCalculateCellNumberingIncreasingDown
//------------------------------------------------------------------------------
/// \brief Test calculate cell numbering for an increasing up grid.
//------------------------------------------------------------------------------
void XmUGridUnitTests::testCalculateCellNumberingIncreasingUp()
{
  std::shared_ptr<XmUGrid> xmUGrid = TEST_XmUBuildIncreasingUpHexahedronUgrid(3, 2, 3, Pt3d());
  TS_ASSERT_EQUALS(XMU_CELL_ORDER_UNKNOWN, xmUGrid->GetCellOrder());
  xmUGrid->SetCellOrder(xms::XMU_CELL_ORDER_UNKNOWN);
  TS_ASSERT_EQUALS(XMU_CELL_ORDER_INCREASING_UP, xmUGrid->CalculateCellOrder())
} // XmUGridUnitTests::testCalculateCellNumberingIncreasingUp
//------------------------------------------------------------------------------
/// \brief Test calculate cell numbering for an increasing up grid.
//------------------------------------------------------------------------------
void XmUGridUnitTests::testCalculateCellNumberingMixed()
{
  std::shared_ptr<XmUGrid> xmUGrid = TEST_XmUBuildIncreasingUpHexahedronUgrid(4, 2, 3, Pt3d());
  // make a UGrid with first and last cells exchanged
  VecInt cellOrder(xmUGrid->GetCellCount(), 0);
  std::iota(cellOrder.begin(), cellOrder.end(), 0);
  cellOrder.front() = cellOrder.back();
  cellOrder.back() = 0;
  VecPt3d locations = xmUGrid->GetLocations();
  VecInt cellstream;
  for (int cellIdx = 0; cellIdx < xmUGrid->GetCellCount(); ++cellIdx)
  {
    VecInt cellCellstream;
    xmUGrid->GetCellCellstream(cellOrder[cellIdx], cellCellstream);
    cellstream.insert(cellstream.begin(), cellCellstream.begin(), cellCellstream.end());
  }
  xmUGrid = XmUGrid::New(locations, cellstream);
  TS_ASSERT_EQUALS(XMU_CELL_ORDER_UNKNOWN, xmUGrid->GetCellOrder());
  xmUGrid->SetCellOrder(xms::XMU_CELL_ORDER_UNKNOWN);
  TS_ASSERT_EQUALS(XMU_CELL_ORDER_UNKNOWN, xmUGrid->CalculateCellOrder());
} // XmUGridUnitTests::testCalculateCellNumberingMixed
//------------------------------------------------------------------------------
/// \brief Test caching to speed up a few 3D cell getters.
//------------------------------------------------------------------------------
void XmUGridUnitTests::testCell3dFunctionCaching()
{
  std::shared_ptr<XmUGrid> xmUGrid = TEST_XmUBuildHexahedronUgrid(2, 3, 2);

  VecInt2d expectedNeighbors = {{-1, 1, -1, -1, -1, -1}, {0, -1, -1, -1, -1, -1}};
  VecInt2d expectedOrientations = {
    {XMU_ORIENTATION_SIDE, XMU_ORIENTATION_SIDE, XMU_ORIENTATION_SIDE, XMU_ORIENTATION_SIDE,
     XMU_ORIENTATION_TOP, XMU_ORIENTATION_BOTTOM},
    {XMU_ORIENTATION_SIDE, XMU_ORIENTATION_SIDE, XMU_ORIENTATION_SIDE, XMU_ORIENTATION_SIDE,
     XMU_ORIENTATION_TOP, XMU_ORIENTATION_BOTTOM}};

  // test four times, to fill the cache, read from the cache, turn off the cache,
  // and turn on the cache
  bool useCacheValues[] = {true, true, false, true};
  for (bool useCacheValue : useCacheValues)
  {
    xmUGrid->SetUseCache(useCacheValue);
    for (int cellIdx = 0; cellIdx < xmUGrid->GetCellCount(); ++cellIdx)
    {
      TS_ASSERT_EQUALS(6, xmUGrid->GetCell3dFaceCount(cellIdx));
      for (int faceIdx = 0; faceIdx < xmUGrid->GetCell3dFaceCount(cellIdx); ++faceIdx)
      {
        int neighbor = xmUGrid->GetCell3dFaceAdjacentCell(cellIdx, faceIdx);
        TS_ASSERT_EQUALS(expectedNeighbors[cellIdx][faceIdx], neighbor);
        int orientation = (int)xmUGrid->GetCell3dFaceOrientation(cellIdx, faceIdx);
        TS_ASSERT_EQUALS(expectedOrientations[cellIdx][faceIdx], orientation);
      }
    }
  }

  // change to different points and cells and test again
  expectedNeighbors = {{-1, 1, -1, -1, -1, -1}, {0, 2, -1, -1, -1, -1}, {1, -1, -1, -1, -1, -1}};
  expectedOrientations = {{XMU_ORIENTATION_SIDE, XMU_ORIENTATION_SIDE, XMU_ORIENTATION_SIDE,
                           XMU_ORIENTATION_SIDE, XMU_ORIENTATION_TOP, XMU_ORIENTATION_BOTTOM},
                          {XMU_ORIENTATION_SIDE, XMU_ORIENTATION_SIDE, XMU_ORIENTATION_SIDE,
                           XMU_ORIENTATION_SIDE, XMU_ORIENTATION_TOP, XMU_ORIENTATION_BOTTOM},
                          {XMU_ORIENTATION_SIDE, XMU_ORIENTATION_SIDE, XMU_ORIENTATION_SIDE,
                           XMU_ORIENTATION_SIDE, XMU_ORIENTATION_TOP, XMU_ORIENTATION_BOTTOM}};
  std::shared_ptr<XmUGrid> newXmUGrid = TEST_XmUBuildHexahedronUgrid(2, 4, 2);
  xmUGrid->SetLocations(newXmUGrid->GetLocations());
  xmUGrid->SetCellstream(newXmUGrid->GetCellstream());
  for (bool useCacheValue : useCacheValues)
  {
    xmUGrid->SetUseCache(useCacheValue);
    for (int cellIdx = 0; cellIdx < xmUGrid->GetCellCount(); ++cellIdx)
    {
      TS_ASSERT_EQUALS(6, xmUGrid->GetCell3dFaceCount(cellIdx));
      for (int faceIdx = 0; faceIdx < xmUGrid->GetCell3dFaceCount(cellIdx); ++faceIdx)
      {
        int neighbor = xmUGrid->GetCell3dFaceAdjacentCell(cellIdx, faceIdx);
        TS_ASSERT_EQUALS(expectedNeighbors[cellIdx][faceIdx], neighbor);
        int orientation = (int)xmUGrid->GetCell3dFaceOrientation(cellIdx, faceIdx);
        TS_ASSERT_EQUALS(expectedOrientations[cellIdx][faceIdx], orientation);
      }
    }
  }
} // XmUGridUnitTests::testCell3dFunctionCaching
//------------------------------------------------------------------------------
/// \brief Tests creating a large UGrid and checks the time spent.
//------------------------------------------------------------------------------
// #define SPEEDTEST
#ifdef SPEEDTEST
#include <boost/timer/timer.hpp>
#endif
void XmUGridUnitTests::testLargeUGridLinkSpeed()
{
#ifdef SPEEDTEST
  int rows = 1000;
  int cols = 500;
  int lays = 4;

  // std::shared_ptr<xms::XmUGrid> grid = TEST_XmUBuildQuadUGrid(rows, cols);
  // std::shared_ptr<xms::XmUGrid> grid = TEST_XmUBuildHexahedronUgrid(rows, cols, lays);
  std::shared_ptr<xms::XmUGrid> grid = TEST_XmUBuildPolyhedronUgrid(rows, cols, lays);

  {
    boost::timer::cpu_timer timer;
    std::shared_ptr<XmUGrid> ugrid = XmUGrid::New(grid->GetLocations(), grid->GetCellstream());
    std::cerr << timer.format() << '\n';
  }

#endif
} // XmUGridUnitTests::testLargeUGridLinkSpeed

//------------------------------------------------------------------------------
/// \brief Test building a UGrid with invalid cells and make sure the invalid
///        cells result in failure to build.
//------------------------------------------------------------------------------
void XmUGridUnitTests::testUgridWithInvalidCells()
{
  VecPt3d points = {{0, 10, 0}};

  // A quad that claims to have 3 points, but actually has 2
  VecInt cellstream = {XMU_QUAD, 3, 0, 3};

  std::shared_ptr<XmUGrid> ugrid = XmUGrid::New(points, cellstream);
  TS_ASSERT_EQUALS(nullptr, ugrid);
} // XmUGridUnitTests::testUgridWithInvalidCells

//------------------------------------------------------------------------------
/// \brief Test that a cell stream is invalid for a UGrid with 99 points.
//------------------------------------------------------------------------------
void iTestBadCellStream(const VecInt& a_cellStream)
{
  bool valid = XmUGrid::IsValidCellstream(a_cellStream, 99);
  TS_ASSERT(!valid);
} // iTestBadCellStream

//------------------------------------------------------------------------------
/// \brief Test that a cell stream is valid for a UGrid with 99 points.
//------------------------------------------------------------------------------
void iTestGoodCellStream(const VecInt& a_cellStream)
{
  bool valid = XmUGrid::IsValidCellstream(a_cellStream, 99);
  TS_ASSERT(valid);
} // iTestGoodCellStream

//------------------------------------------------------------------------------
/// \brief Test that trailing empty cells are valid.
//------------------------------------------------------------------------------
void CellStreamValidationUnitTests::testTrailingEmptyCell()
{
  iTestGoodCellStream({XMU_EMPTY_CELL, 0});
} // CellStreamValidationUnitTests::testTrailingEmptyCell

//------------------------------------------------------------------------------
/// \brief Test a good unknown cell.
//------------------------------------------------------------------------------
void CellStreamValidationUnitTests::testGoodUnknownCell()
{
  iTestGoodCellStream({-1, 2, 1, 2});
} // CellStreamValidationUnitTests::testGoodUnknownCell

//------------------------------------------------------------------------------
/// \brief Test a good empty cell.
//------------------------------------------------------------------------------
void CellStreamValidationUnitTests::testGoodEmptyCell()
{
  iTestGoodCellStream({XMU_EMPTY_CELL, 0});
} // CellStreamValidationUnitTests::testGoodEmptyCell

//------------------------------------------------------------------------------
/// \brief Test a good vertex.
//------------------------------------------------------------------------------
void CellStreamValidationUnitTests::testGoodVertex()
{
  iTestGoodCellStream({XMU_VERTEX, 1, 1});
} // CellStreamValidationUnitTests::testGoodVertex

//------------------------------------------------------------------------------
/// \brief Test a good line.
//------------------------------------------------------------------------------
void CellStreamValidationUnitTests::testGoodLine()
{
  iTestGoodCellStream({XMU_LINE, 2, 1, 2});
} // CellStreamValidationUnitTests::testGoodLine

//------------------------------------------------------------------------------
/// \brief Test a good triangle.
//------------------------------------------------------------------------------
void CellStreamValidationUnitTests::testGoodTriangle()
{
  iTestGoodCellStream({XMU_TRIANGLE, 3, 1, 2, 3});
} // CellStreamValidationUnitTests::testGoodTriangle

//------------------------------------------------------------------------------
/// \brief Test a good pixel.
//------------------------------------------------------------------------------
void CellStreamValidationUnitTests::testGoodPixel()
{
  iTestGoodCellStream({XMU_PIXEL, 4, 1, 2, 3, 4});
} // CellStreamValidationUnitTests::testGoodPixel

//------------------------------------------------------------------------------
/// \brief Test a good quad.
//------------------------------------------------------------------------------
void CellStreamValidationUnitTests::testGoodQuad()
{
  iTestGoodCellStream({XMU_PIXEL, 4, 1, 2, 3, 4});
} // CellStreamValidationUnitTests::testGoodQuad

//------------------------------------------------------------------------------
/// \brief Test a good tetrahedron.
//------------------------------------------------------------------------------
void CellStreamValidationUnitTests::testGoodTetra()
{
  iTestGoodCellStream({XMU_TETRA, 4, 1, 2, 3, 4});
} // CellStreamValidationUnitTests::testGoodTetra

//------------------------------------------------------------------------------
/// \brief Test a good pyramid.
//------------------------------------------------------------------------------
void CellStreamValidationUnitTests::testGoodPyramid()
{
  iTestGoodCellStream({XMU_PYRAMID, 5, 1, 2, 3, 4, 5});
} // CellStreamValidationUnitTests::testGoodPyramid

//------------------------------------------------------------------------------
/// \brief Test a good wedge.
//------------------------------------------------------------------------------
void CellStreamValidationUnitTests::testGoodWedge()
{
  iTestGoodCellStream({XMU_WEDGE, 6, 1, 2, 3, 4, 5, 6});
} // CellStreamValidationUnitTests::testGoodWedge

//------------------------------------------------------------------------------
/// \brief Test a good pentagonal prism.
//------------------------------------------------------------------------------
void CellStreamValidationUnitTests::testGoodPentagonalPrism()
{
  iTestGoodCellStream({XMU_PENTAGONAL_PRISM, 6, 1, 2, 3, 4, 5, 6});
} // CellStreamValidationUnitTests::testGoodPentagonalPrism

//------------------------------------------------------------------------------
/// \brief Test a good hexagonal prism.
//------------------------------------------------------------------------------
void CellStreamValidationUnitTests::testGoodHexagonalPrism()
{
  iTestGoodCellStream({XMU_HEXAGONAL_PRISM, 7, 1, 2, 3, 4, 5, 6, 7});
} // CellStreamValidationUnitTests::testGoodHexagonalPrism

//------------------------------------------------------------------------------
/// \brief Test a good voxel.
//------------------------------------------------------------------------------
void CellStreamValidationUnitTests::testGoodVoxel()
{
  iTestGoodCellStream({XMU_VOXEL, 8, 1, 2, 3, 4, 5, 6, 7, 8});
} // CellStreamValidationUnitTests::testGoodVoxel

//------------------------------------------------------------------------------
/// \brief Test a good hexahedron.
//------------------------------------------------------------------------------
void CellStreamValidationUnitTests::testGoodHexahedron()
{
  iTestGoodCellStream({XMU_HEXAHEDRON, 8, 1, 2, 3, 4, 5, 6, 7, 8});
} // CellStreamValidationUnitTests::testGoodHexahedron

//------------------------------------------------------------------------------
/// \brief Test a good polygon vertex.
//------------------------------------------------------------------------------
void CellStreamValidationUnitTests::testGoodPolyVertex()
{
  iTestGoodCellStream({XMU_POLY_VERTEX, 1, 1});
} // CellStreamValidationUnitTests::testGoodPolyVertex

//------------------------------------------------------------------------------
/// \brief Test a good polygon line.
//------------------------------------------------------------------------------
void CellStreamValidationUnitTests::testGoodPolyLine()
{
  iTestGoodCellStream({XMU_POLY_LINE, 2, 1, 2});
} // CellStreamValidationUnitTests::testGoodPolyLine

//------------------------------------------------------------------------------
/// \brief Test a good triangle strip.
//------------------------------------------------------------------------------
void CellStreamValidationUnitTests::testGoodTriangleStrip()
{
  iTestGoodCellStream({XMU_TRIANGLE_STRIP, 3, 1, 2, 3});
} // CellStreamValidationUnitTests::testGoodTriangleStrip

//------------------------------------------------------------------------------
/// \brief Test a good polygon.
//------------------------------------------------------------------------------
void CellStreamValidationUnitTests::testGoodPolygon()
{
  iTestGoodCellStream({XMU_POLYGON, 3, 1, 2, 3});
} // CellStreamValidationUnitTests::testGoodPolygon

//------------------------------------------------------------------------------
/// \brief Test a good grid, including multiple cells of different types.
//------------------------------------------------------------------------------
void CellStreamValidationUnitTests::testGoodGrid()
{
  iTestGoodCellStream({
      XMU_EMPTY_CELL, 0,
      XMU_VERTEX, 1, 98, // There are 99 points, so 98 should be okay
      XMU_LINE, 2, 1, 2,
      XMU_TRIANGLE, 3, 1, 2, 3,
      XMU_PIXEL, 4, 1, 2, 3, 4,
      XMU_QUAD, 4, 1, 2, 3, 4,
      XMU_TETRA, 4, 1, 2, 3, 4,
      XMU_PYRAMID, 5, 1, 2, 3, 4, 5,
      XMU_WEDGE, 6, 1, 2, 3, 4, 5, 6,
      XMU_PENTAGONAL_PRISM, 6, 1, 2, 3, 4, 5, 6,
      XMU_HEXAGONAL_PRISM, 7, 1, 2, 3, 4, 5, 6, 7,
      XMU_VOXEL, 8, 1, 2, 3, 4, 5, 6, 7, 8,
      XMU_HEXAHEDRON, 8, 1, 2, 3, 4, 5, 6, 7, 8,
      XMU_POLY_VERTEX, 3, 1, 2, 3,
      XMU_POLY_LINE, 5, 1, 2, 3, 4, 5,
      XMU_TRIANGLE_STRIP, 9, 1, 2, 3, 4, 5, 6, 7, 8, 9,
      XMU_POLYGON, 8, 1, 2, 3, 4, 5, 6, 7, 8,
      
      XMU_POLYHEDRON, 5,
      3, 1, 2, 3,
      4, 2, 3, 4, 5,
      5, 3, 4, 5, 6, 7,
      6, 4, 5, 6, 7, 8, 9,
      7, 5, 6, 7, 8, 9, 10, 11,

      -1, 4, 1, 2, 3, 4 // unrecognized cells are okay, the number of points is
                        // just assumed to be correct.
  });
} // CellStreamValidationUnitTests::testGoodGrid

//------------------------------------------------------------------------------
/// \brief Test that unknown cells must have a number of points.
//------------------------------------------------------------------------------
void CellStreamValidationUnitTests::testUnknownCellNoNumberOfPoints()
{
  iTestBadCellStream({-1});
} // CellStreamValidationUnitTests::testUnknownCellNoNumberOfPoints

//------------------------------------------------------------------------------
/// \brief Test that empty cells must have a number of points.
//------------------------------------------------------------------------------
void CellStreamValidationUnitTests::testEmptyCellNoNumberOfPoints()
{
  iTestBadCellStream({XMU_EMPTY_CELL});
} // CellStreamValidationUnitTests::testEmptyCellNoNumberOfPoints

//------------------------------------------------------------------------------
/// \brief Test that vertices must have a number of points.
//------------------------------------------------------------------------------
void CellStreamValidationUnitTests::testVertexNoNumberOfPoints()
{
  iTestBadCellStream({XMU_VERTEX});
} // CellStreamValidationUnitTests::testVertexNoNumberOfPoints

//------------------------------------------------------------------------------
/// \brief Test that lines must have a number of points.
//------------------------------------------------------------------------------
void CellStreamValidationUnitTests::testLineNoNumberOfPoints()
{
  iTestBadCellStream({XMU_LINE});
} // CellStreamValidationUnitTests::testLineNoNumberOfPoints

//------------------------------------------------------------------------------
/// \brief Test that triangles must have a number of points.
//------------------------------------------------------------------------------
void CellStreamValidationUnitTests::testTriangleNoNumberOfPoints()
{
  iTestBadCellStream({XMU_TRIANGLE});
} // CellStreamValidationUnitTests::testTriangleNoNumberOfPoints

//------------------------------------------------------------------------------
/// \brief Test that pixels must have a number of points.
//------------------------------------------------------------------------------
void CellStreamValidationUnitTests::testPixelNoNumberOfPoints()
{
  iTestBadCellStream({XMU_PIXEL});
} // CellStreamValidationUnitTests::testPixelNoNumberOfPoints

//------------------------------------------------------------------------------
/// \brief Test that quads must have a number of points.
//------------------------------------------------------------------------------
void CellStreamValidationUnitTests::testQuadNoNumberOfPoints()
{
  iTestBadCellStream({XMU_QUAD});
} // CellStreamValidationUnitTests::testQuadNoNumberOfPoints

//------------------------------------------------------------------------------
/// \brief Test that tetrahedrons must have a number of points.
//------------------------------------------------------------------------------
void CellStreamValidationUnitTests::testTetraNoNumberOfPoints()
{
  iTestBadCellStream({XMU_TETRA});
} // CellStreamValidationUnitTests::testTetraNoNumberOfPoints

//------------------------------------------------------------------------------
/// \brief Test that pyramids must have a number of points.
//------------------------------------------------------------------------------
void CellStreamValidationUnitTests::testPyramidNoNumberOfPoints()
{
  iTestBadCellStream({XMU_PYRAMID});
} // CellStreamValidationUnitTests::testPyramidNoNumberOfPoints

//------------------------------------------------------------------------------
/// \brief Test that wedges must have a number of points.
//------------------------------------------------------------------------------
void CellStreamValidationUnitTests::testWedgeNoNumberOfPoints()
{
  iTestBadCellStream({XMU_WEDGE});
} // CellStreamValidationUnitTests::testWedgeNoNumberOfPoints

//------------------------------------------------------------------------------
/// \brief Test that pentagonal prisms must have a number of points.
//------------------------------------------------------------------------------
void CellStreamValidationUnitTests::testPentagonalPrismNoNumberOfPoints()
{
  iTestBadCellStream({XMU_PENTAGONAL_PRISM});
} // CellStreamValidationUnitTests::testPentagonalPrismNoNumberOfPoints

//------------------------------------------------------------------------------
/// \brief Test that hexagonal prisms must have a number of points.
//------------------------------------------------------------------------------
void CellStreamValidationUnitTests::testHexagonalPrismNoNumberOfPoints()
{
  iTestBadCellStream({XMU_HEXAGONAL_PRISM});
} // CellStreamValidationUnitTests::testHexagonalPrismNoNumberOfPoints

//------------------------------------------------------------------------------
/// \brief Test that voxels must have a number of points.
//------------------------------------------------------------------------------
void CellStreamValidationUnitTests::testVoxelNoNumberOfPoints()
{
  iTestBadCellStream({XMU_VOXEL});
} // CellStreamValidationUnitTests::testVoxelNoNumberOfPoints

//------------------------------------------------------------------------------
/// \brief Test that hexahedrons must have a number of points.
//------------------------------------------------------------------------------
void CellStreamValidationUnitTests::testHexahedronNoNumberOfPoints()
{
  iTestBadCellStream({XMU_HEXAHEDRON});
} // CellStreamValidationUnitTests::testHexahedronNoNumberOfPoints

//------------------------------------------------------------------------------
/// \brief Test that polygon vertices must have a number of points.
//------------------------------------------------------------------------------
void CellStreamValidationUnitTests::testPolyVertexNoNumberOfPoints()
{
  iTestBadCellStream({XMU_POLY_VERTEX});
} // CellStreamValidationUnitTests::testPolyVertexNoNumberOfPoints

//------------------------------------------------------------------------------
/// \brief Test that polygon lines must have a number of points.
//------------------------------------------------------------------------------
void CellStreamValidationUnitTests::testPolyLineNoNumberOfPoints()
{
  iTestBadCellStream({XMU_POLY_LINE});
} // CellStreamValidationUnitTests::testPolyLineNoNumberOfPoints

//------------------------------------------------------------------------------
/// \brief Test that triangle strips must have a number of points.
//------------------------------------------------------------------------------
void CellStreamValidationUnitTests::testTriangleStripNoNumberOfPoints()
{
  iTestBadCellStream({XMU_TRIANGLE_STRIP});
} // CellStreamValidationUnitTests::testTriangleStripNoNumberOfPoints

//------------------------------------------------------------------------------
/// \brief Test that polygons must have a number of points.
//------------------------------------------------------------------------------
void CellStreamValidationUnitTests::testPolygonNoNumberOfPoints()
{
  iTestBadCellStream({XMU_POLYGON});
} // CellStreamValidationUnitTests::testPolygonNoNumberOfPoints

//------------------------------------------------------------------------------
/// \brief Test that entire grids must have a number of points.
//------------------------------------------------------------------------------
void CellStreamValidationUnitTests::testGridNoNumberOfPoints()
{
  iTestBadCellStream({
      XMU_EMPTY_CELL, 0,
      XMU_VERTEX, 1, 1,
      XMU_LINE, 2, 1, 2,
      XMU_TRIANGLE, 3, 1, 2, 3,
      XMU_PIXEL, 4, 1, 2, 3, 4,
      XMU_QUAD, 4, 1, 2, 3, 4,
      XMU_TETRA, 4, 1, 2, 3, 4,
      XMU_PYRAMID, 5, 1, 2, 3, 4, 5,
      XMU_WEDGE, 6, 1, 2, 3, 4, 5, 6,
      XMU_PENTAGONAL_PRISM, 6, 1, 2, 3, 4, 5, 6,
      XMU_HEXAGONAL_PRISM, 7, 1, 2, 3, 4, 5, 6, 7,
      XMU_VOXEL, 8, 1, 2, 3, 4, 5, 6, 7, 8,
      XMU_HEXAHEDRON, 8, 1, 2, 3, 4, 5, 6, 7, 8,
      XMU_POLY_VERTEX, 3, 1, 2, 3,
      XMU_POLY_LINE, 5, 1, 2, 3, 4, 5,
      XMU_TRIANGLE_STRIP, 9, 1, 2, 3, 4, 5, 6, 7, 8, 9,
      XMU_POLYGON, 8, 1, 2, 3, 4, 5, 6, 7, 8,
	  XMU_EMPTY_CELL,
  });
} // CellStreamValidationUnitTests::testGridNoNumberOfPoints

//------------------------------------------------------------------------------
/// \brief Test that empty cells must have the right number of points.
//------------------------------------------------------------------------------
void CellStreamValidationUnitTests::testEmptyCellWrongNumberOfPoints()
{
  iTestBadCellStream({XMU_EMPTY_CELL, 5});
} // CellStreamValidationUnitTests::testEmptyCellWrongNumberOfPoints

//------------------------------------------------------------------------------
/// \brief Test that vertices must have the right number of points.
//------------------------------------------------------------------------------
void CellStreamValidationUnitTests::testVertexWrongNumberOfPoints()
{
  iTestBadCellStream({XMU_VERTEX, 5});
} // CellStreamValidationUnitTests::testVertexWrongNumberOfPoints

//------------------------------------------------------------------------------
/// \brief Test that lines must have the right number of points.
//------------------------------------------------------------------------------
void CellStreamValidationUnitTests::testLineWrongNumberOfPoints()
{
  iTestBadCellStream({XMU_LINE, 5, 1, 2});
} // CellStreamValidationUnitTests::testLineWrongNumberOfPoints

//------------------------------------------------------------------------------
/// \brief Test that triangles must have the right number of points.
//------------------------------------------------------------------------------
void CellStreamValidationUnitTests::testTriangleWrongNumberOfPoints()
{
  iTestBadCellStream({XMU_TRIANGLE, 5, 1, 2, 3});
} // CellStreamValidationUnitTests::testTriangleWrongNumberOfPoints

//------------------------------------------------------------------------------
/// \brief Test that pixels must have the right number of points.
//------------------------------------------------------------------------------
void CellStreamValidationUnitTests::testPixelWrongNumberOfPoints()
{
  iTestBadCellStream({XMU_PIXEL, 5, 1, 2, 3, 4});
} // CellStreamValidationUnitTests::testPixelWrongNumberOfPoints

//------------------------------------------------------------------------------
/// \brief Test that quads must have the right number of points.
//------------------------------------------------------------------------------
void CellStreamValidationUnitTests::testQuadWrongNumberOfPoints()
{
  iTestBadCellStream({XMU_QUAD, 5, 1, 2, 3, 4});
} // CellStreamValidationUnitTests::testQuadWrongNumberOfPoints

//------------------------------------------------------------------------------
/// \brief Test that tetrahedrons must have the right number of points.
//------------------------------------------------------------------------------
void CellStreamValidationUnitTests::testTetraWrongNumberOfPoints()
{
  iTestBadCellStream({XMU_TETRA, 5, 1, 2, 3, 4});
} // CellStreamValidationUnitTests::testTetraWrongNumberOfPoints

//------------------------------------------------------------------------------
/// \brief Test that pyramids must have the right number of points.
//------------------------------------------------------------------------------
void CellStreamValidationUnitTests::testPyramidWrongNumberOfPoints()
{
  iTestBadCellStream({XMU_PYRAMID, 3, 1, 2, 3, 4, 5});
} // CellStreamValidationUnitTests::testPyramidWrongNumberOfPoints

//------------------------------------------------------------------------------
/// \brief Test that wedges must have the right number of points.
//------------------------------------------------------------------------------
void CellStreamValidationUnitTests::testWedgeWrongNumberOfPoints()
{
  iTestBadCellStream({XMU_WEDGE, 3, 1, 2, 3, 4, 5, 6});
} // CellStreamValidationUnitTests::testWedgeWrongNumberOfPoints

//------------------------------------------------------------------------------
/// \brief Test that pentagonal prisms must have the right number of points.
//------------------------------------------------------------------------------
void CellStreamValidationUnitTests::testPentagonalPrismWrongNumberOfPoints()
{
  iTestBadCellStream({XMU_PENTAGONAL_PRISM, 3, 1, 2, 3, 4, 5, 6});
} // CellStreamValidationUnitTests::testPentagonalPrismWrongNumberOfPoints

//------------------------------------------------------------------------------
/// \brief Test that hexagonal prisms must have the right number of points.
//------------------------------------------------------------------------------
void CellStreamValidationUnitTests::testHexagonalPrismWrongNumberOfPoints()
{
  iTestBadCellStream({XMU_HEXAGONAL_PRISM, 3, 1, 2, 3, 4, 5, 6, 7});
} // CellStreamValidationUnitTests::testHexagonalPrismWrongNumberOfPoints

//------------------------------------------------------------------------------
/// \brief Test that voxels must have the right number of points.
//------------------------------------------------------------------------------
void CellStreamValidationUnitTests::testVoxelWrongNumberOfPoints()
{
  iTestBadCellStream({XMU_VOXEL, 3, 1, 2, 3, 4, 5, 6, 7, 8});
} // CellStreamValidationUnitTests::testVoxelWrongNumberOfPoints

//------------------------------------------------------------------------------
/// \brief Test that hexahedrons must have the right number of points.
//------------------------------------------------------------------------------
void CellStreamValidationUnitTests::testHexahedronWrongNumberOfPoints()
{
  iTestBadCellStream({XMU_HEXAHEDRON, 3, 1, 2, 3, 4, 5, 6, 7, 8});
} // CellStreamValidationUnitTests::testHexahedronWrongNumberOfPoints

//------------------------------------------------------------------------------
/// \brief Test that polygon vertices must have the right number of points.
//------------------------------------------------------------------------------
void CellStreamValidationUnitTests::testPolyVertexWrongNumberOfPoints()
{
  iTestBadCellStream({XMU_POLY_VERTEX, 0, 1});
} // CellStreamValidationUnitTests::testPolyVertexWrongNumberOfPoints

//------------------------------------------------------------------------------
/// \brief Test that polygon lines must have the right number of points.
//------------------------------------------------------------------------------
void CellStreamValidationUnitTests::testPolyLineWrongNumberOfPoints()
{
  iTestBadCellStream({XMU_POLY_LINE, 1, 1, 2});
} // CellStreamValidationUnitTests::testPolyLineWrongNumberOfPoints

//------------------------------------------------------------------------------
/// \brief Test that triangle strips must have the right number of points.
//------------------------------------------------------------------------------
void CellStreamValidationUnitTests::testTriangleStripWrongNumberOfPoints()
{
  iTestBadCellStream({XMU_TRIANGLE_STRIP, 2, 1, 2, 3});
} // CellStreamValidationUnitTests::testTriangleStripWrongNumberOfPoints

//------------------------------------------------------------------------------
/// \brief Test that polygons must have the right number of points.
//------------------------------------------------------------------------------
void CellStreamValidationUnitTests::testPolygonWrongNumberOfPoints()
{
  iTestBadCellStream({XMU_POLYGON, 2, 1, 2, 3});
} // CellStreamValidationUnitTests::testPolygonWrongNumberOfPoints

//------------------------------------------------------------------------------
/// \brief Test that entire grids must have the right number of points.
//------------------------------------------------------------------------------
void CellStreamValidationUnitTests::testGridWrongNumberOfPoints()
{
  iTestBadCellStream({
      XMU_EMPTY_CELL, 0,
      XMU_VERTEX, 1, 1,
      XMU_LINE, 2, 1, 2,
      XMU_TRIANGLE, 3, 1, 2, 3,
      XMU_PIXEL, 4, 1, 2, 3, 4,
      XMU_QUAD, 4, 1, 2, 3, 4,
      XMU_TETRA, 4, 1, 2, 3, 4,
      XMU_PYRAMID, 5, 1, 2, 3, 4, 5,
      XMU_WEDGE, 6, 1, 2, 3, 4, 5, 6,
      XMU_PENTAGONAL_PRISM, 6, 1, 2, 3, 4, 5, 6,
      XMU_HEXAGONAL_PRISM, 6, 1, 2, 3, 4, 5, 6, 7, // Prism should have 7 points, has 6
      XMU_VOXEL, 8, 1, 2, 3, 4, 5, 6, 7, 8,
      XMU_HEXAHEDRON, 8, 1, 2, 3, 4, 5, 6, 7, 8,
      XMU_POLY_VERTEX, 3, 1, 2, 3,
      XMU_POLY_LINE, 5, 1, 2, 3, 4, 5,
      XMU_TRIANGLE_STRIP, 9, 1, 2, 3, 4, 5, 6, 7, 8, 9,
      XMU_POLYGON, 8, 1, 2, 3, 4, 5, 6, 7, 8
  });
} // CellStreamValidationUnitTests::testGridWrongNumberOfPoints

//------------------------------------------------------------------------------
/// \brief Test that unknown cells must have enough points.
//------------------------------------------------------------------------------
void CellStreamValidationUnitTests::testUnknownCellMissingPoints()
{
  iTestBadCellStream({-1, 3, 1, 2});
} // CellStreamValidationUnitTests::testUnknownCellMissingPoints

//------------------------------------------------------------------------------
/// \brief Test that vertices must have enough points.
//------------------------------------------------------------------------------
void CellStreamValidationUnitTests::testVertexMissingPoints()
{
  iTestBadCellStream({XMU_VERTEX, 1});
} // CellStreamValidationUnitTests::testVertexMissingPoints

//------------------------------------------------------------------------------
/// \brief Test that lines must have enough points.
//------------------------------------------------------------------------------
void CellStreamValidationUnitTests::testLineMissingPoints()
{
  iTestBadCellStream({XMU_LINE, 2, 1});
} // CellStreamValidationUnitTests::testLineMissingPoints

//------------------------------------------------------------------------------
/// \brief Test that triangles must have enough points.
//------------------------------------------------------------------------------
void CellStreamValidationUnitTests::testTriangleMissingPoints()
{
  iTestBadCellStream({XMU_TRIANGLE, 3, 1, 2});
} // CellStreamValidationUnitTests::testTriangleMissingPoints

//------------------------------------------------------------------------------
/// \brief Test that pixels must have enough points.
//------------------------------------------------------------------------------
void CellStreamValidationUnitTests::testPixelMissingPoints()
{
  iTestBadCellStream({XMU_PIXEL, 4, 1, 2, 3});
} // CellStreamValidationUnitTests::testPixelMissingPoints

//------------------------------------------------------------------------------
/// \brief Test that quads must have enough points.
//------------------------------------------------------------------------------
void CellStreamValidationUnitTests::testQuadMissingPoints()
{
  iTestBadCellStream({XMU_QUAD, 4, 1, 2, 3});
} // CellStreamValidationUnitTests::testQuadMissingPoints

//------------------------------------------------------------------------------
/// \brief Test that tetrahedrons must have enough points.
//------------------------------------------------------------------------------
void CellStreamValidationUnitTests::testTetraMissingPoints()
{
  iTestBadCellStream({XMU_TETRA, 4, 1, 2, 3});
} // CellStreamValidationUnitTests::testTetraMissingPoints

//------------------------------------------------------------------------------
/// \brief Test that pyramids must have enough points.
//------------------------------------------------------------------------------
void CellStreamValidationUnitTests::testPyramidMissingPoints()
{
  iTestBadCellStream({XMU_PYRAMID, 5, 1, 2, 3, 4});
} // CellStreamValidationUnitTests::testPyramidMissingPoints

//------------------------------------------------------------------------------
/// \brief Test that wedges must have enough points.
//------------------------------------------------------------------------------
void CellStreamValidationUnitTests::testWedgeMissingPoints()
{
  iTestBadCellStream({XMU_WEDGE, 6, 1, 2, 3, 4, 5});
} // CellStreamValidationUnitTests::testWedgeMissingPoints

//------------------------------------------------------------------------------
/// \brief Test that pentagonal prisms must have enough points.
//------------------------------------------------------------------------------
void CellStreamValidationUnitTests::testPentagonalPrismMissingPoints()
{
  iTestBadCellStream({XMU_PENTAGONAL_PRISM, 6, 1, 2, 3, 4, 5});
} // CellStreamValidationUnitTests::testPentagonalPrismMissingPoints

//------------------------------------------------------------------------------
/// \brief Test that hexagonal prisms must have enough points.
//------------------------------------------------------------------------------
void CellStreamValidationUnitTests::testHexagonalPrismMissingPoints()
{
  iTestBadCellStream({XMU_HEXAGONAL_PRISM, 7, 1, 2, 3, 4, 5, 6});
} // CellStreamValidationUnitTests::testHexagonalPrismMissingPoints

//------------------------------------------------------------------------------
/// \brief Test that voxels must have enough points.
//------------------------------------------------------------------------------
void CellStreamValidationUnitTests::testVoxelMissingPoints()
{
  iTestBadCellStream({XMU_VOXEL, 8, 1, 2, 3, 4, 5, 6, 7});
} // CellStreamValidationUnitTests::testVoxelMissingPoints

//------------------------------------------------------------------------------
/// \brief Test that hexahedrons must have enough points.
//------------------------------------------------------------------------------
void CellStreamValidationUnitTests::testHexahedronMissingPoints()
{
  iTestBadCellStream({XMU_HEXAHEDRON, 8, 1, 2, 3, 4, 5, 6, 7});
} // CellStreamValidationUnitTests::testHexahedronMissingPoints

//------------------------------------------------------------------------------
/// \brief Test that polygon vertices must have enough points.
//------------------------------------------------------------------------------
void CellStreamValidationUnitTests::testPolyVertexMissingPoints()
{
  iTestBadCellStream({XMU_POLY_VERTEX, 1});
} // CellStreamValidationUnitTests::testPolyVertexMissingPoints

//------------------------------------------------------------------------------
/// \brief Test that polygon lines must have enough points.
//------------------------------------------------------------------------------
void CellStreamValidationUnitTests::testPolyLineMissingPoints()
{
  iTestBadCellStream({XMU_POLY_LINE, 2, 1});
} // CellStreamValidationUnitTests::testPolyLineMissingPoints

//------------------------------------------------------------------------------
/// \brief Test that triangle strips must have enough points.
//------------------------------------------------------------------------------
void CellStreamValidationUnitTests::testTriangleStripMissingPoints()
{
  iTestBadCellStream({XMU_TRIANGLE_STRIP, 3, 1, 2});
} // CellStreamValidationUnitTests::testTriangleStripMissingPoints

//------------------------------------------------------------------------------
/// \brief Test that polygons must have enough points.
//------------------------------------------------------------------------------
void CellStreamValidationUnitTests::testPolygonMissingPoints()
{
  iTestBadCellStream({XMU_POLYGON, 3, 1, 2});
} // CellStreamValidationUnitTests::testPolygonMissingPoints

//------------------------------------------------------------------------------
/// \brief Test a grid that is missing a point at the end.
//------------------------------------------------------------------------------
void CellStreamValidationUnitTests::testGridMissingPoints()
{
  iTestBadCellStream({
      XMU_EMPTY_CELL, 0,
      XMU_VERTEX, 1, 1,
      XMU_LINE, 2, 1, 2,
      XMU_TRIANGLE, 3, 1, 2, 3,
      XMU_PIXEL, 4, 1, 2, 3, 4,
      XMU_QUAD, 4, 1, 2, 3, 4,
      XMU_TETRA, 4, 1, 2, 3, 4,
      XMU_PYRAMID, 5, 1, 2, 3, 4, 5,
      XMU_WEDGE, 6, 1, 2, 3, 4, 5, 6,
      XMU_PENTAGONAL_PRISM, 6, 1, 2, 3, 4, 5, 6,
      XMU_HEXAGONAL_PRISM, 7, 1, 2, 3, 4, 5, 6, 7,
      XMU_VOXEL, 8, 1, 2, 3, 4, 5, 6, 7, 8,
      XMU_HEXAHEDRON, 8, 1, 2, 3, 4, 5, 6, 7, 8,
      XMU_POLY_VERTEX, 3, 1, 2, 3,
      XMU_POLY_LINE, 5, 1, 2, 3, 4, 5,
      XMU_TRIANGLE_STRIP, 9, 1, 2, 3, 4, 5, 6, 7, 8, 9,
      XMU_POLYGON, 8, 1, 2, 3, 4, 5, 6, 7 // Said there were 8, actually 7
  });
} // CellStreamValidationUnitTests::testGridMissingPoints

//------------------------------------------------------------------------------
/// \brief Test that vertices must have valid points.
//------------------------------------------------------------------------------
void CellStreamValidationUnitTests::testUnknownCellBadPoints()
{
  iTestBadCellStream({-1, 3, 1, 2, 99});
  iTestBadCellStream({-1, 3, 1, 2, -1});
} // CellStreamValidationUnitTests::testUnknownCellBadPoints

//------------------------------------------------------------------------------
/// \brief Test that vertices must have valid points.
//------------------------------------------------------------------------------
void CellStreamValidationUnitTests::testVertexBadPoints()
{
  iTestBadCellStream({XMU_VERTEX, 1, 99});
  iTestBadCellStream({XMU_VERTEX, 1, -1});
} // CellStreamValidationUnitTests::testVertexBadPoints

//------------------------------------------------------------------------------
/// \brief Test that lines must have valid points.
//------------------------------------------------------------------------------
void CellStreamValidationUnitTests::testLineBadPoints()
{
  iTestBadCellStream({XMU_LINE, 2, 1, 99});
  iTestBadCellStream({XMU_LINE, 2, 1, -1});
} // CellStreamValidationUnitTests::testLineBadPoints

//------------------------------------------------------------------------------
/// \brief Test that triangles must have valid points.
//------------------------------------------------------------------------------
void CellStreamValidationUnitTests::testTriangleBadPoints()
{
  iTestBadCellStream({XMU_TRIANGLE, 3, 1, 2, 99});
  iTestBadCellStream({XMU_TRIANGLE, 3, 1, 2, -1});
} // CellStreamValidationUnitTests::testTriangleBadPoints

//------------------------------------------------------------------------------
/// \brief Test that pixels must have valid points.
//------------------------------------------------------------------------------
void CellStreamValidationUnitTests::testPixelBadPoints()
{
  iTestBadCellStream({XMU_PIXEL, 4, 1, 2, 3, 99});
  iTestBadCellStream({XMU_PIXEL, 4, 1, 2, 3, -1});
} // CellStreamValidationUnitTests::testPixelBadPoints

//------------------------------------------------------------------------------
/// \brief Test that quads must have valid points.
//------------------------------------------------------------------------------
void CellStreamValidationUnitTests::testQuadBadPoints()
{
  iTestBadCellStream({XMU_QUAD, 4, 1, 2, 3, 99});
  iTestBadCellStream({XMU_QUAD, 4, 1, 2, 3, -1});
} // CellStreamValidationUnitTests::testQuadBadPoints

//------------------------------------------------------------------------------
/// \brief Test that tetrahedrons must have valid points.
//------------------------------------------------------------------------------
void CellStreamValidationUnitTests::testTetraBadPoints()
{
  iTestBadCellStream({XMU_TETRA, 4, 1, 2, 3, 99});
  iTestBadCellStream({XMU_TETRA, 4, 1, 2, 3, -1});
} // CellStreamValidationUnitTests::testTetraBadPoints

//------------------------------------------------------------------------------
/// \brief Test that pyramids must have valid points.
//------------------------------------------------------------------------------
void CellStreamValidationUnitTests::testPyramidBadPoints()
{
  iTestBadCellStream({XMU_PYRAMID, 5, 1, 2, 3, 4, 99});
  iTestBadCellStream({XMU_PYRAMID, 5, 1, 2, 3, 4, -1});
} // CellStreamValidationUnitTests::testPyramidBadPoints

//------------------------------------------------------------------------------
/// \brief Test that wedges must have valid points.
//------------------------------------------------------------------------------
void CellStreamValidationUnitTests::testWedgeBadPoints()
{
  iTestBadCellStream({XMU_WEDGE, 6, 1, 2, 3, 4, 5, 99});
  iTestBadCellStream({XMU_WEDGE, 6, 1, 2, 3, 4, 5, -1});
} // CellStreamValidationUnitTests::testWedgeBadPoints

//------------------------------------------------------------------------------
/// \brief Test that pentagonal prisms must have valid points.
//------------------------------------------------------------------------------
void CellStreamValidationUnitTests::testPentagonalPrismBadPoints()
{
  iTestBadCellStream({XMU_PENTAGONAL_PRISM, 6, 1, 2, 3, 4, 5, 99});
  iTestBadCellStream({XMU_PENTAGONAL_PRISM, 6, 1, 2, 3, 4, 5, -1});
} // CellStreamValidationUnitTests::testPentagonalPrismBadPoints

//------------------------------------------------------------------------------
/// \brief Test that hexagonal prisms must have valid points.
//------------------------------------------------------------------------------
void CellStreamValidationUnitTests::testHexagonalPrismBadPoints()
{
  iTestBadCellStream({XMU_HEXAGONAL_PRISM, 7, 1, 2, 3, 4, 5, 6, 99});
  iTestBadCellStream({XMU_HEXAGONAL_PRISM, 7, 1, 2, 3, 4, 5, 6, -1});
} // CellStreamValidationUnitTests::testHexagonalPrismBadPoints

//------------------------------------------------------------------------------
/// \brief Test that voxels must have valid points.
//------------------------------------------------------------------------------
void CellStreamValidationUnitTests::testVoxelBadPoints()
{
  iTestBadCellStream({XMU_VOXEL, 8, 1, 2, 3, 4, 5, 6, 7, 99});
  iTestBadCellStream({XMU_VOXEL, 8, 1, 2, 3, 4, 5, 6, 7, -1});
} // CellStreamValidationUnitTests::testVoxelBadPoints

//------------------------------------------------------------------------------
/// \brief Test that hexahedrons must have valid points.
//------------------------------------------------------------------------------
void CellStreamValidationUnitTests::testHexahedronBadPoints()
{
  iTestBadCellStream({XMU_HEXAHEDRON, 8, 1, 2, 3, 4, 5, 6, 7, 99});
  iTestBadCellStream({XMU_HEXAHEDRON, 8, 1, 2, 3, 4, 5, 6, 7, -1});
} // CellStreamValidationUnitTests::testHexahedronBadPoints

//------------------------------------------------------------------------------
/// \brief Test that polygon vertices must have valid points.
//------------------------------------------------------------------------------
void CellStreamValidationUnitTests::testPolyVertexBadPoints()
{
  iTestBadCellStream({XMU_POLY_VERTEX, 1, 99});
  iTestBadCellStream({XMU_POLY_VERTEX, 1, -1});
} // CellStreamValidationUnitTests::testPolyVertexBadPoints

//------------------------------------------------------------------------------
/// \brief Test that polygon lines must have valid points.
//------------------------------------------------------------------------------
void CellStreamValidationUnitTests::testPolyLineBadPoints()
{
  iTestBadCellStream({XMU_POLY_LINE, 2, 1, 99});
  iTestBadCellStream({XMU_POLY_LINE, 2, 1, -1});
} // CellStreamValidationUnitTests::testPolyLineBadPoints

//------------------------------------------------------------------------------
/// \brief Test that triangle strips must have valid points.
//------------------------------------------------------------------------------
void CellStreamValidationUnitTests::testTriangleStripBadPoints()
{
  iTestBadCellStream({XMU_TRIANGLE_STRIP, 3, 1, 2, 99});
  iTestBadCellStream({XMU_TRIANGLE_STRIP, 3, 1, 2, -1});
} // CellStreamValidationUnitTests::testTriangleStripBadPoints

//------------------------------------------------------------------------------
/// \brief Test that polygons must have valid points.
//------------------------------------------------------------------------------
void CellStreamValidationUnitTests::testPolygonBadPoints()
{
  iTestBadCellStream({XMU_POLYGON, 3, 1, 2, 99});
  iTestBadCellStream({XMU_POLYGON, 3, 1, 2, -1});
} // CellStreamValidationUnitTests::testPolygonBadPoints

//------------------------------------------------------------------------------
/// \brief Test that entire grids must have valid points.
//------------------------------------------------------------------------------
void CellStreamValidationUnitTests::testGridBadPoints()
{
  iTestBadCellStream({
      XMU_EMPTY_CELL, 0,
      XMU_VERTEX, 1, 1,
      XMU_LINE, 2, 1, 2,
      XMU_TRIANGLE, 3, 1, 2, 3,
      XMU_PIXEL, 4, 1, 2, 3, 4,
      XMU_QUAD, 4, 1, 2, 3, 4,
      XMU_TETRA, 4, 1, 2, 3, 4,
      XMU_PYRAMID, 5, 1, 2, 3, 4, 5,
      XMU_WEDGE, 6, 1, 2, 3, 4, 5, 6,
      XMU_PENTAGONAL_PRISM, 6, 1, 2, 3, 4, 5, 6,
      XMU_HEXAGONAL_PRISM, 7, 1, 2, 3, 4, 5, 6, 7,
      XMU_VOXEL, 8, 1, 2, 3, 4, 5, 6, 7, 8,
      XMU_HEXAHEDRON, 8, 1, 2, 3, 4, 5, 6, 7, 8,
      XMU_POLY_VERTEX, 3, 1, 2, 99, // Point 99 doesn't exist
      XMU_POLY_LINE, 5, 1, 2, 3, 4, 5,
      XMU_TRIANGLE_STRIP, 9, 1, 2, 3, 4, 5, 6, 7, 8, 9,
      XMU_POLYGON, 8, 1, 2, 3, 4, 5, 6, 7, 8
  });
  iTestBadCellStream({
      XMU_EMPTY_CELL, 0,
      XMU_VERTEX, 1, 1,
      XMU_LINE, 2, 1, 2,
      XMU_TRIANGLE, 3, 1, 2, 3,
      XMU_PIXEL, 4, 1, 2, 3, 4,
      XMU_QUAD, 4, 1, 2, 3, 4,
      XMU_TETRA, 4, 1, 2, 3, 4,
      XMU_PYRAMID, 5, 1, 2, 3, 4, 5,
      XMU_WEDGE, 6, 1, 2, 3, 4, 5, 6,
      XMU_PENTAGONAL_PRISM, 6, 1, 2, 3, 4, 5, 6,
      XMU_HEXAGONAL_PRISM, 7, 1, 2, 3, 4, 5, 6, 7,
      XMU_VOXEL, 8, 1, 2, 3, 4, 5, 6, 7, 8,
      XMU_HEXAHEDRON, 8, 1, 2, 3, 4, 5, 6, 7, 8,
      XMU_POLY_VERTEX, 3, 1, 2, -1, // Point -1 can't exist
      XMU_POLY_LINE, 5, 1, 2, 3, 4, 5,
      XMU_TRIANGLE_STRIP, 9, 1, 2, 3, 4, 5, 6, 7, 8, 9,
      XMU_POLYGON, 8, 1, 2, 3, 4, 5, 6, 7, 8
  });
} // CellStreamValidationUnitTests::testGridBadPoints

//------------------------------------------------------------------------------
/// \brief Test a good polyhedron.
//------------------------------------------------------------------------------
void CellStreamValidationUnitTests::testGoodPolyhedron()
{
  iTestGoodCellStream({
      XMU_POLYHEDRON, 5,
      3, 1, 2, 3,
      4, 2, 3, 4, 5,
      5, 3, 4, 5, 6, 7,
      6, 4, 5, 6, 7, 8, 9,
      7, 5, 6, 7, 8, 9, 10, 11
  });
} // CellStreamValidationUnitTests::testGoodPolyhedron

//------------------------------------------------------------------------------
/// \brief Test that polyhedrons must have the right number of faces.
//------------------------------------------------------------------------------
void CellStreamValidationUnitTests::testPolyhedronWrongNumberOfFaces()
{
  iTestBadCellStream({
      XMU_POLYHEDRON, 2, // 2 faces in polyhedron not allowed
      3, 1, 2, 3,
      3, 4, 5, 6,
      3, 7, 8, 9,
  });
} // CellStreamValidationUnitTests::testPolyhedronMismatchedFaces

//------------------------------------------------------------------------------
/// \brief Test that polyhedrons must have the right face count.
//------------------------------------------------------------------------------
void CellStreamValidationUnitTests::testPolyhedronWrongNumberOfPoints()
{
  iTestBadCellStream({
      XMU_POLYHEDRON, 5,
      3, 1, 2, 3,
      4, 2, 3, 4, 5,
      5, 3, 4, 5, 6, 7,
      2, 4, 5, // 2 points in face not allowed
      7, 5, 6, 7, 8, 9, 10, 11
  });
} // CellStreamValidationUnitTests::testPolyhedronWrongNumberOfPoints

//------------------------------------------------------------------------------
/// \brief Test that polyhedrons must have enough faces.
//------------------------------------------------------------------------------
void CellStreamValidationUnitTests::testPolyhedronMissingFaces()
{
  iTestBadCellStream({
      XMU_POLYHEDRON, 6,
      3, 1, 2, 3,
      4, 2, 3, 4, 5,
      5, 3, 4, 5, 6, 7,
      6, 4, 5, 6, 7, 8, 9,
      7, 5, 6, 7, 8, 9, 10, 11
      // Sixth face is missing
  });
} // CellStreamValidationUnitTests::testPolyhedronMissingFaces

//------------------------------------------------------------------------------
/// \brief Test that polyhedrons must have enough points.
//------------------------------------------------------------------------------
void CellStreamValidationUnitTests::testPolyhedronMissingPoints()
{
  iTestBadCellStream({
      XMU_POLYHEDRON, 5,
      3, 1, 2, 3,
      4, 2, 3, 4, 5,
      5, 3, 4, 5, 6, 7,
      6, 4, 5, 6, 7, 8, 9,
      7, 5, 6, 7, 8, 9, 10 // Seventh point missing
  });
} // CellStreamValidationUnitTests::testPolyhedronMissingPoints

//------------------------------------------------------------------------------
/// \brief Test that polyhedrons must have valid points.
//------------------------------------------------------------------------------
void CellStreamValidationUnitTests::testPolyhedronBadPoints()
{
  iTestBadCellStream({
      XMU_POLYHEDRON, 5,
      3, 1, 2, 3,
      4, 2, 3, 4, 5,
      5, 3, 4, 99, 6, 7, // Point 99 doesn't exist
      6, 4, 5, 6, 7, 8, 9,
      7, 5, 6, 7, 8, 9, 10, 11
  });
  iTestBadCellStream({
      XMU_POLYHEDRON, 5,
      3, 1, 2, 3,
      4, 2, 3, 4, 5,
      5, 3, 4, -1, 6, 7, // Point -1 can't exist
      6, 4, 5, 6, 7, 8, 9,
      7, 5, 6, 7, 8, 9, 10, 11
  });
} // CellStreamValidationUnitTests::testPolyhedronBadPoints

#endif
