#pragma once
//------------------------------------------------------------------------------
/// \file XmUGrid.h
/// \brief Contains the XmUGrid Class and supporting data types.
/// \ingroup ugrid
/// \copyright (C) Copyright Aquaveo 2018. Distributed under the xmsng
///  Software License, Version 1.0. (See accompanying file
///  LICENSE_1_0.txt or copy at http://www.aquaveo.com/xmsng/LICENSE_1_0.txt)
//------------------------------------------------------------------------------

//----- Included files ---------------------------------------------------------

// 3. Standard library headers

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

/// The orientation of a face must be one of these.
enum XmUGridFaceOrientation {
  XMU_ORIENTATION_UNKNOWN = -1,

  // Linear cells
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
  virtual ~XmUGrid();

  // Misc
  static bool IsValidCellstream(const VecInt& a_cellstream);

  // Points

  /// \brief Get the number of points.
  /// \return the number of points
  virtual int PointCount() const = 0;

  /// \brief Get vector of UGrid points.
  /// \return a vector of point locations
  virtual const VecPt3d& Locations() const = 0;

  /// \brief Set UGrid points.
  /// \param[in] a_locations vector of point locations
  virtual void SetLocations(const VecPt3d& a_locations) = 0;

  /// \brief Get the point
  /// \param[in] a_pointIdx the index of the point
  /// \return the point or an initialize point if the index is invalid
  virtual Pt3d PointLocation(const int a_pointIdx) const = 0;

  /// \brief Set the point
  /// \param[in] a_pointIdx the index of the point
  /// \param[in] a_location The new location of the specified point
  /// \return whether the point was successfully set
  virtual bool SetLocation(const int a_pointIdx, const Pt3d& a_location) = 0;

  /// \brief Get the X, Y location of a point.
  /// \param[in] a_pointIdx The index of the point.
  /// \return The location of the point with Z set to 0.0.
  virtual Pt3d PointXy0(const int a_pointIdx) const = 0;

  /// \brief Convert a vector of point indices into a vector of point 3d
  /// \param[in] a_points a vector of point indices
  /// \return vector of point 3d
  virtual VecPt3d PointsLocations(const VecInt& a_points) const = 0;

  /// \brief Get extents of all points in UGrid
  /// \param[out] a_min minimum extent of all points
  /// \param[out] a_max maximum extent of all points
  virtual void Extents(Pt3d& a_min, Pt3d& a_max) const = 0;

  /// \brief Get the cells that are associated with the specified point
  /// \param[in] a_pointIdx the index of the point
  /// \return a vector of the cell indices associated with this point
  virtual VecInt PointAdjacentCells(const int a_pointIdx) const = 0;

  /// \brief Get the cells that are associated with the specified point
  /// \param[in] a_pointIdx the index of the point
  /// \param[out] a_adjacentCells a vector of the adjacent cell indices
  /// \return a vector of the cell indices associated with this point
  virtual void PointAdjacentCells(const int a_pointIdx, VecInt& a_adjacentCells) const = 0;

  /// \brief Gets the common cells from a vector of points
  /// \param[in] a_points a vector of unique points
  /// \return a vector of cell indices
  virtual VecInt PointsAdjacentCells(const VecInt& a_points) const = 0;

  /// \brief Gets the cells adjacent to all of a vector of points.
  /// \param[in] a_pointIdxs an array of point indices
  /// \param[out] a_adjacentCellIdxs a vector of cell indices
  virtual void PointsAdjacentCells(const VecInt& a_pointIdxs, VecInt& a_adjacentCellIdxs) const = 0;

  /// \brief Gets the cells adjacent to both of the two points.
  /// \param[in] a_pointIdx1 first point index
  /// \param[in] a_pointIdx2 second point index
  /// \param[out] a_adjacentCellIdxs a vector of cell indices
  virtual void PointsAdjacentCells(const int a_pointIdx1,
                                   const int a_pointIdx2,
                                   VecInt& a_adjacentCellIdxs) const = 0;

  // Cells

  /// \brief Get the number of cells.
  /// \return the number of cells
  virtual int CellCount() const = 0;

  /// \brief Get the number of cell points (including polyhedron).
  /// \param[in] a_cellIdx the index of the cell
  /// \return a vector of point indices
  virtual int CellPointCount(const int a_cellIdx) const = 0;

  /// \brief Get the points of a cell (including polyhedron)
  /// \param[in] a_cellIdx the index of the cell
  /// \return a vector of point indices
  virtual VecInt CellPoints(const int a_cellIdx) const = 0;

  /// \brief Get the points of a cell.
  /// \param[in] a_cellIdx the index of the cell
  /// \param[out] a_cellPoints the points of the cell
  /// \return if the cell index is valid
  virtual bool CellPoints(const int a_cellIdx, VecInt& a_cellPoints) const = 0;

  /// \brief Get locations of cell points.
  /// \param[in] a_cellIdx the index of the cell
  /// \param[out] a_cellLocations The locations of the cell points
  virtual void CellLocations(const int a_cellIdx, VecPt3d& a_cellLocations) const = 0;

  /// \brief Get the number of cells.
  /// \param[in] a_cellIdx the index of the cell
  /// \return the number of cells or -1 if invalid index
  virtual XmUGridCellType CellType(const int a_cellIdx) const = 0;

  /// \brief Count all number of the cells with each dimenion (0, 1, 2, 3)
  /// \return the count of dimensions of all of the cells of the ugrid
  virtual std::vector<int> DimensionCounts() const = 0;

  /// \brief Get the dimension of the specified cell.
  /// \param[in] a_cellIdx the index of the cell
  /// \return the dimension of the cells or -1 if invalid index or invalid
  /// dimension
  virtual int CellDimension(const int a_cellIdx) const = 0;

  /// \brief Get the extents of the given cell.
  /// \param[in] a_cellIdx The cell index to get the extents of.
  /// \param[out] a_min The minimum location.
  /// \param[out] a_max The maximum location.
  virtual void CellExtents(const int a_cellIdx, Pt3d& a_min, Pt3d& a_max) const = 0;

  /// \brief Get cell stream vector for the entire UGrid.
  /// A cellstream is defined as follows:
  ///   Polyhedrons:
  ///     Cell type, number of faces, [num points in face, point numbers (0-based,
  ///     CCW when looking in)] repeated for each face.
  ///   Hexahedrons, polygons, quads, triangles etc:
  ///     Cell type (ElemTypeEnum), number of points, point numbers.  Zero-based, CCW,
  ///     bottom, then top. Not true for pixel or voxel.
  /// \return constant reference to the cell stream vector
  virtual const VecInt& Cellstream() const = 0;

  /// \brief Set the ugrid cells for the entire UGrid using a cell stream.
  /// \param[in] a_cellstream The cellstream for the UGrid.
  /// @see CellStream
  /// \return if successfully set
  virtual bool SetCellstream(const VecInt& a_cellstream) = 0;

  /// \brief Get cell stream vector for a single cell.
  /// \param[in] a_cellIdx the index of the cell
  /// \param[in] a_cellstream The cellstream of the cell
  /// @see Cellstream for more detail on cell stream definitions.
  /// \return whether it was successfull or not
  virtual bool CellCellstream(const int a_cellIdx, VecInt& a_cellstream) const = 0;

  /// \brief Get the cells neighboring a cell (cells associated with any of it's points)
  /// \param[in] a_cellIdx the index of the cell
  /// \return vector of cell indices
  virtual VecInt CellAdjacentCells(const int a_cellIdx) const = 0;

  /// \brief Get the cells neighboring a cell (cells associated with any of it's points)
  /// \param[in] a_cellIdx the index of the cell
  /// \param[out] a_cellNeighbors vector of cell indices
  virtual void CellAdjacentCells(const int a_cellIdx, VecInt& a_cellNeighbors) const = 0;

  /// \brief Get a plan view polygon of a specified cell
  /// \param[in] a_cellIdx The index of the cell.
  /// \param[out] a_polygon Vector of Pt3d that is the plan view polygon.
  /// \return False if the cell index does not exist or if the cell is not 2 or 3
  /// dimensional.
  virtual bool CellPlanViewPolygon(int a_cellIdx, VecPt3d& a_polygon) const = 0;

  /// \brief Get the centroid location of a cell.
  /// \param[in] a_cellIdx The index of the cell.
  /// \param[out] a_centroid The location of the cell centroid.
  /// \return False if the cell index does not exist.
  virtual bool CellCentroid(int a_cellIdx, Pt3d& a_centroid) const = 0;

  /// \brief Get the number of edges for a cell.
  /// \param[in] a_cellIdx the index of the cell
  /// \return the count of cell edges
  virtual int CellEdgeCount(const int a_cellIdx) const = 0;

  /// \brief Get the points of a cell.
  /// \param[in] a_cellIdx the index of the cell
  /// \param[in] a_edgeIdx the index of the edge
  /// \return a standard pair of point indices (which is an edge)
  virtual XmEdge CellEdge(const int a_cellIdx, const int a_edgeIdx) const = 0;

  /// \brief Get the index of the adjacent cells (that shares the same cell edge)
  /// \param[in] a_cellIdx the index of the cell
  /// \param[in] a_edgeIdx the index of the edge
  /// \return a vector of cell indices of the adjacent cells
  virtual VecInt CellEdgeAdjacentCells(const int a_cellIdx, const int a_edgeIdx) const = 0;

  /// \brief Get the index of the adjacent cells (that shares the same cell edge)
  /// \param[in] a_cellIdx the index of the cell
  /// \param[in] a_edgeIdx the index of the edge
  /// \param[out] a_adjacentCellIdxs a vector of cell indices of the adjacent
  ///             cells
  virtual void CellEdgeAdjacentCells(const int a_cellIdx,
                                     const int a_edgeIdx,
                                     VecInt& a_adjacentCellIdxs) const = 0;

  /// \brief Get the index of the adjacent cells (that shares the same cell edge)
  /// \param[in] a_cellIdx the index of the cell
  /// \param[in] a_edgeIdx the index of the edge
  /// \return index of the adjacent cell (or -1 if none).
  virtual int Cell2dEdgeAdjacentCell(const int a_cellIdx, const int a_edgeIdx) const = 0;

  /// \brief Get the indices of the adjacent cells (that shares the same cell edge)
  /// \param[in] a_edge the edge (a pair of point indices)
  /// \param[out] a_adjacentCellIdxs a vector of cell indices of the adjacent cells
  virtual void EdgeAdjacentCells(const XmEdge& a_edge, VecInt& a_adjacentCellIdxs) const = 0;

  /// \brief Get the index of the adjacent cells (that shares the same cell edge)
  /// \param[in] a_edge the edge (a pair of point indices)
  /// \return a vector of cell indices of the adjacent cells
  virtual VecInt EdgeAdjacentCells(const XmEdge& a_edge) const = 0;

  /// \brief Get the Edges of a cell.
  /// \param[in] a_cellIdx the cells to whom the edges belong
  /// \return a vector of edges
  virtual std::vector<XmEdge> CellEdges(const int a_cellIdx) const = 0;

  /// \brief Get the Edges of a cell.
  /// \param[in] a_cellIdx the cells to whom the edges belong
  /// \param[out] a_edges a vector of edges
  virtual void CellEdges(const int a_cellIdx, std::vector<XmEdge>& a_edges) const = 0;

  /// \brief Given a point gets point indices attached to the point by an edge.
  /// \param[in] a_pointIdx The point to get adjacent points from.
  /// \param[out] a_edgePoints The indices of the adjacent points.
  virtual void PointAdjacentPoints(int a_pointIdx, VecInt& a_edgePoints) const = 0;

  /// \brief Given a point gets point locations attached to the point by an edge.
  /// \param[in] a_pointIdx The point to get attached point from.
  /// \param[out] a_edgePoints A vector of points attached across edges.
  virtual void PointAdjacentLocations(int a_pointIdx, VecPt3d& a_edgePoints) const = 0;

  // Faces

  /// \brief Get the number of cell faces for given cell.
  /// \param[in] a_cellIdx the index of the cell
  /// \return the count of cell faces
  virtual int Cell3dFaceCount(const int a_cellIdx) const = 0;
  /// \brief Get the number of face points for a given cell and face.
  /// \param[in] a_cellIdx The cell
  /// \param[in] a_faceIdx The face
  /// \return The number of face points or -1 if invalid face or cell index.
  virtual int Cell3dFacePointCount(const int a_cellIdx, const int a_faceIdx) const = 0;

  /// \brief Get the cell face for given cell and face index.
  /// \param[in] a_cellIdx the index of the cell
  /// \param[in] a_faceIdx the face index of the cell
  /// \return a vector of point indices for the face index of the cell
  virtual VecInt Cell3dFacePoints(const int a_cellIdx, const int a_faceIdx) const = 0;

  /// \brief Get the cell face for given cell and face index.
  /// \param[in] a_cellIdx the index of the cell
  /// \param[in] a_faceIdx the face index of the cell
  /// \param[out] a_facePtIdxs a vector of point indices for the face
  /// \return a vector of point indices for the face index of the cell
  virtual void Cell3dFacePoints(const int a_cellIdx,
                                const int a_faceIdx,
                                VecInt& a_facePtIdxs) const = 0;

  /// \brief Get the faces of a cell.
  /// \param[in] a_cellIdx the cells to whom the faces belong
  /// \return a vector of faces, which is a vector of point indices
  virtual VecInt2d Cell3dFacesPoints(const int a_cellIdx) const = 0;

  /// \brief Get the cell face neighbors for given cell and face index.
  /// \param[in] a_cellIdx the index of the cell
  /// \param[in] a_faceIdx the face index of the cell
  /// \return a cell index of the neighbor
  virtual int Cell3dFaceAdjacentCell(const int a_cellIdx, const int a_faceIdx) const = 0;

  /// \brief Get the cell face neighbors for given cell and face index.
  /// \param[in] a_cellIdx the index of the cell
  /// \param[in] a_faceIdx the face index of the cell
  /// \param[in] a_neighborCell the index of the neighboring cell
  /// \param[in] a_neighborFace the face index of the neighboring cell adjacent
  ///      to the given face
  /// \return a cell index of the neighbor
  virtual bool Cell3dFaceAdjacentCell(const int a_cellIdx,
                                      const int a_faceIdx,
                                      int& a_neighborCell,
                                      int& a_neighborFace) const = 0;

private:
  /// \cond
  XM_DISALLOW_COPY_AND_ASSIGN(XmUGrid)
  /// \endcond

protected:
  XmUGrid();
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
