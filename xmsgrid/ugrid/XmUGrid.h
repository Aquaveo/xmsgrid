#pragma once
//------------------------------------------------------------------------------
/// \file XmUGrid.h
/// \brief Contains the XmUGrid Class and supporting data types.
/// \ingroup ugrid
/// \copyright (C) Copyright Aquaveo 2018. Distributed under FreeBSD License
/// (See accompanying file LICENSE or https://aqaveo.com/bsd/license.txt)
//------------------------------------------------------------------------------

//----- Included files ---------------------------------------------------------

// 3. Standard library headers
#include <memory>

// 4. External library headers

// 5. Shared code headers
#include <xmscore/misc/base_macros.h>
#include <xmscore/misc/boost_defines.h>
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
  static BSHP<XmUGrid> New(const VecPt3d& a_points, const VecInt& a_cellstream);
  static BSHP<XmUGrid> New();
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

  static bool IsValidCellstream(const VecInt& a_cellstream);

  // Points

  int GetPointCount() const;

  const VecPt3d& GetLocations() const;

  void SetLocations(const VecPt3d& a_locations);

  Pt3d GetPointLocation(const int a_pointIdx) const;

  bool SetPointLocation(const int a_pointIdx, const Pt3d& a_location);

  Pt3d GetPointXy0(const int a_pointIdx) const;

  VecPt3d GetPointsLocations(const VecInt& a_points) const;

  void GetExtents(Pt3d& a_min, Pt3d& a_max) const;

  VecInt GetPointAdjacentCells(const int a_pointIdx) const;

  void GetPointAdjacentCells(const int a_pointIdx, VecInt& a_adjacentCells) const;

  VecInt GetPointsAdjacentCells(const VecInt& a_points) const;

  void GetPointsAdjacentCells(const VecInt& a_pointIdxs, VecInt& a_adjacentCellIdxs) const;

  void GetPointsAdjacentCells(const int a_pointIdx1,
                              const int a_pointIdx2,
                              VecInt& a_adjacentCellIdxs) const;

  bool IsValidPointChange(const int a_changedPtIdx, const Pt3d& a_newPosition) const;

  // Cells

  int GetCellCount() const;

  int GetCellPointCount(const int a_cellIdx) const;

  VecInt GetCellPoints(const int a_cellIdx) const;

  bool GetCellPoints(const int a_cellIdx, VecInt& a_cellPoints) const;

  void GetCellLocations(const int a_cellIdx, VecPt3d& a_cellLocations) const;

  XmUGridCellType GetCellType(const int a_cellIdx) const;

  std::vector<int> GetDimensionCounts() const;

  int GetCellDimension(const int a_cellIdx) const;

  void GetCellExtents(const int a_cellIdx, Pt3d& a_min, Pt3d& a_max) const;

  const VecInt& GetCellstream() const;

  bool SetCellstream(const VecInt& a_cellstream);

  bool GetCellCellstream(const int a_cellIdx, VecInt& a_cellstream) const;

  VecInt GetCellAdjacentCells(const int a_cellIdx) const;

  void GetCellAdjacentCells(const int a_cellIdx, VecInt& a_cellNeighbors) const;

  bool GetCellPlanViewPolygon(int a_cellIdx, VecPt3d& a_polygon) const;

  bool GetCellCentroid(int a_cellIdx, Pt3d& a_centroid) const;

  int GetCellEdgeCount(const int a_cellIdx) const;

  XmEdge GetCellEdge(const int a_cellIdx, const int a_edgeIdx) const;

  VecInt GetCellEdgeAdjacentCells(const int a_cellIdx, const int a_edgeIdx) const;

  void GetCellEdgeAdjacentCells(const int a_cellIdx,
                                const int a_edgeIdx,
                                VecInt& a_adjacentCellIdxs) const;

  int GetCell2dEdgeAdjacentCell(const int a_cellIdx, const int a_edgeIdx) const;

  void GetEdgeAdjacentCells(const XmEdge& a_edge, VecInt& a_adjacentCellIdxs) const;

  VecInt GetEdgeAdjacentCells(const XmEdge& a_edge) const;

  std::vector<XmEdge> GetCellEdges(const int a_cellIdx) const;

  void GetCellEdges(const int a_cellIdx, std::vector<XmEdge>& a_edges) const;

  void GetPointAdjacentPoints(int a_pointIdx, VecInt& a_edgePoints) const;

  void GetPointAdjacentLocations(int a_pointIdx, VecPt3d& a_edgePoints) const;

  // Faces

  int GetCell3dFaceCount(const int a_cellIdx) const;
  int GetCell3dFacePointCount(const int a_cellIdx, const int a_faceIdx) const;

  VecInt GetCell3dFacePoints(const int a_cellIdx, const int a_faceIdx) const;

  void GetCell3dFacePoints(const int a_cellIdx, const int a_faceIdx, VecInt& a_facePtIdxs) const;

  VecInt2d GetCell3dFacesPoints(const int a_cellIdx) const;

  int GetCell3dFaceAdjacentCell(const int a_cellIdx, const int a_faceIdx) const;

  bool GetCell3dFaceAdjacentCell(const int a_cellIdx,
                                 const int a_faceIdx,
                                 int& a_neighborCell,
                                 int& a_neighborFace) const;

  XmUGridFaceOrientation GetCell3dFaceOrientation(int a_cellIdx, int a_faceIdx) const;

private:
  class Impl;
  std::unique_ptr<Impl> m_impl; ///< imlementation
};

//----- Function prototypes ----------------------------------------------------
BSHP<xms::XmUGrid> TEST_XmUGrid1Left90Tri();
BSHP<xms::XmUGrid> TEST_XmUGridSimpleQuad();
BSHP<xms::XmUGrid> TEST_XmUGrid2dLinear();
BSHP<xms::XmUGrid> TEST_XmUGrid3dLinear();
BSHP<xms::XmUGrid> TEST_XmUGridHexagonalPolyhedron();
BSHP<xms::XmUGrid> TEST_XmUBuildQuadUGrid(const int a_rows, const int a_cols);
BSHP<xms::XmUGrid> TEST_XmUBuildQuadUGrid(const int a_rows,
                                          const int a_cols,
                                          const xms::Pt3d& a_origin);
BSHP<xms::XmUGrid> TEST_XmUBuildHexahedronUgrid(const int a_rows,
                                                const int a_cols,
                                                const int a_lays);
BSHP<xms::XmUGrid> TEST_XmUBuildHexahedronUgrid(const int a_rows,
                                                const int a_cols,
                                                const int a_lays,
                                                const xms::Pt3d& a_origin);
BSHP<xms::XmUGrid> TEST_XmUBuildPolyhedronUgrid(const int a_rows,
                                                const int a_cols,
                                                const int a_lays);
BSHP<xms::XmUGrid> TEST_XmUBuildPolyhedronUgrid(const int a_rows,
                                                const int a_cols,
                                                const int a_lays,
                                                const xms::Pt3d& a_origin);
BSHP<xms::XmUGrid> TEST_XmUBuild3DChevronUgrid();

} // namespace xms
