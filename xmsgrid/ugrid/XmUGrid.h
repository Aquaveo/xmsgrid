#pragma once
//------------------------------------------------------------------------------
/// \file XmUGrid.h
/// \brief Contains the XmUGrid Class and supporting data types.
/// \ingroup ugrid
/// \copyright (C) Copyright Aquaveo 2018. Distributed under FreeBSD License
/// (See accompanying file LICENSE or https://aquaveo.com/bsd/license.txt)
//------------------------------------------------------------------------------

//----- Included files ---------------------------------------------------------

// 3. Standard library headers
#include <memory>

// 4. External library headers

// 5. Shared code headers
#include <xmscore/stl/vector.h>

//----- Forward declarations ---------------------------------------------------

//----- Namespace declaration --------------------------------------------------

/// XMS Namespace
namespace xms
{
//----- Forward declarations ---------------------------------------------------
class XmEdge;

//----- Constants / Enumerations -----------------------------------------------

/// Matches cell types from VTK (see vtkCellType.h)
enum XmUGridCellType {
  XMU_INVALID_CELL_TYPE = -1,

  // Linear cells
  XMU_EMPTY_CELL = 0,
  XMU_VERTEX = 1,
  XMU_POLY_VERTEX = 2,
  XMU_LINE = 3,
  XMU_POLY_LINE = 4,
  XMU_TRIANGLE = 5,
  XMU_TRIANGLE_STRIP = 6,
  XMU_POLYGON = 7,
  XMU_PIXEL = 8,
  XMU_QUAD = 9,
  XMU_TETRA = 10,
  XMU_VOXEL = 11,
  XMU_HEXAHEDRON = 12,
  XMU_WEDGE = 13,
  XMU_PYRAMID = 14,
  XMU_PENTAGONAL_PRISM = 15,
  XMU_HEXAGONAL_PRISM = 16,

  // Quadratic, isoparametric cells
  XMU_QUADRATIC_EDGE = 21,
  XMU_QUADRATIC_TRIANGLE = 22,
  XMU_QUADRATIC_QUAD = 23,
  XMU_QUADRATIC_POLYGON = 36,
  XMU_QUADRATIC_TETRA = 24,
  XMU_QUADRATIC_HEXAHEDRON = 25,
  XMU_QUADRATIC_WEDGE = 26,
  XMU_QUADRATIC_PYRAMID = 27,
  XMU_BIQUADRATIC_QUAD = 28,
  XMU_TRIQUADRATIC_HEXAHEDRON = 29,
  XMU_QUADRATIC_LINEAR_QUAD = 30,
  XMU_QUADRATIC_LINEAR_WEDGE = 31,
  XMU_BIQUADRATIC_QUADRATIC_WEDGE = 32,
  XMU_BIQUADRATIC_QUADRATIC_HEXAHEDRON = 33,
  XMU_BIQUADRATIC_TRIANGLE = 34,

  // Cubic, isoparametric cell
  XMU_CUBIC_LINE = 35,

  // Special class of cells formed by convex group of points
  XMU_CONVEX_POINT_SET = 41,

  // Polyhedron cell (consisting of polygonal faces)
  XMU_POLYHEDRON = 42,

  // Higher order cells in parametric form
  XMU_PARAMETRIC_CURVE = 51,
  XMU_PARAMETRIC_SURFACE = 52,
  XMU_PARAMETRIC_TRI_SURFACE = 53,
  XMU_PARAMETRIC_QUAD_SURFACE = 54,
  XMU_PARAMETRIC_TETRA_REGION = 55,
  XMU_PARAMETRIC_HEX_REGION = 56,

  // Higher order cells
  XMU_HIGHER_ORDER_EDGE = 60,
  XMU_HIGHER_ORDER_TRIANGLE = 61,
  XMU_HIGHER_ORDER_QUAD = 62,
  XMU_HIGHER_ORDER_POLYGON = 63,
  XMU_HIGHER_ORDER_TETRAHEDRON = 64,
  XMU_HIGHER_ORDER_WEDGE = 65,
  XMU_HIGHER_ORDER_PYRAMID = 66,
  XMU_HIGHER_ORDER_HEXAHEDRON = 67,

  XMU_NUMBER_OF_CELL_TYPES

};

/// Order of cells in a layered 3D UGrid
enum XmUGridCellOrdering {
  XMU_CELL_ORDER_UNKNOWN = -1,
  XMU_CELL_ORDER_INCREASING_DOWN = 0,
  XMU_CELL_ORDER_INCREASING_UP = 1
};

/// The orientation of a 3D face must be one of these.
enum XmUGridFaceOrientation {
  XMU_ORIENTATION_UNKNOWN = -1,
  XMU_ORIENTATION_SIDE = 0,
  XMU_ORIENTATION_TOP = 1,
  XMU_ORIENTATION_BOTTOM = 2,
  XMU_ORIENTATION_NUMBER
};

//----- Structs / Classes ------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
class XmUGrid
{
public:
  static std::shared_ptr<XmUGrid> New(const VecPt3d& a_locations, const VecInt& a_cellstream);
  static std::shared_ptr<XmUGrid> New();
  XmUGrid();
  XmUGrid(const XmUGrid& a_xmUGrid);
  XmUGrid(XmUGrid&& a_xmUGrid);
  ~XmUGrid();

  XmUGrid& operator=(XmUGrid a_xmUGrid);
  void Swap(XmUGrid& a_xmUGrid);

  // Misc
  bool GetModified() const;
  void SetUnmodified();
  void SetUseCache(bool a_useCache);
  [[deprecated(
      "This overload is only retained for source compatibility with external "
      "code and may be removed in the next major version of xmsgrid. Its use "
      "is discouraged due to a harmful and unfixable bug. "
      "This overload validates the cell stream's structure, but CANNOT fully "
      "validate the point IDs. It can only ensure they are positive. "
      "Excessively large point IDs will be assumed valid, even though doing "
      "so may result in past-the-end access to the points list later. "
      "To prevent this issue, pass the number of points in the grid as the "
      "second parameter to use the safer overload that validates point IDs."
  )]]
  static bool IsValidCellstream(const VecInt& a_cellstream);
  static bool IsValidCellstream(const VecInt& a_cellstream, int a_points);

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
  VecInt GetPointAdjacentCells(int a_pointIdx) const;
  void GetPointAdjacentCells(int a_pointIdx, VecInt& a_adjacentCells) const;
  VecInt GetPointsAdjacentCells(const VecInt& a_points) const;
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
  XmUGridCellOrdering GetCellOrdering() const;
  void SetCellOrdering(XmUGridCellOrdering a_cellOrdering);
  XmUGridCellOrdering CalculateCellOrdering() const;
  VecInt GetCellAdjacentCells(int a_cellIdx) const;
  void GetCellAdjacentCells(int a_cellIdx, VecInt& a_cellNeighbors) const;
  bool GetCellPlanViewPolygon(int a_cellIdx, VecPt3d& a_polygon) const;
  bool GetCellCentroid(int a_cellIdx, Pt3d& a_centroid) const;
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

private:
  class Impl;
  std::unique_ptr<Impl> m_impl; ///< implementation
};

//----- Function prototypes ----------------------------------------------------
std::shared_ptr<XmUGrid> TEST_XmUGrid1Left90Tri();
std::shared_ptr<XmUGrid> TEST_XmUGridSimpleQuad();
std::shared_ptr<XmUGrid> TEST_XmUGrid2dLinear();
std::shared_ptr<XmUGrid> TEST_XmUGrid3dLinear();
std::shared_ptr<XmUGrid> TEST_XmUGridHexagonalPolyhedron();
std::shared_ptr<XmUGrid> TEST_XmUBuildQuadUGrid(int a_rows, int a_cols);
std::shared_ptr<XmUGrid> TEST_XmUBuildQuadUGrid(int a_rows, int a_cols, const xms::Pt3d& a_origin);
std::shared_ptr<XmUGrid> TEST_XmUBuildHexahedronUgrid(int a_rows, int a_cols, int a_lays);
std::shared_ptr<XmUGrid> TEST_XmUBuildHexahedronUgrid(int a_rows,
                                                      int a_cols,
                                                      int a_lays,
                                                      const xms::Pt3d& a_origin);
std::shared_ptr<xms::XmUGrid> TEST_XmUBuildIncreasingUpHexahedronUgrid(int a_rows,
                                                                       int a_cols,
                                                                       int a_lays,
                                                                       const xms::Pt3d& a_origin);
std::shared_ptr<XmUGrid> TEST_XmUBuildPolyhedronUgrid(int a_rows, int a_cols, int a_lays);
std::shared_ptr<XmUGrid> TEST_XmUBuildPolyhedronUgrid(int a_rows,
                                                      int a_cols,
                                                      int a_lays,
                                                      const xms::Pt3d& a_origin);
std::shared_ptr<XmUGrid> TEST_XmUBuild3DChevronUgrid();

} // namespace xms
