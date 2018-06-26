#pragma once
//------------------------------------------------------------------------------
/// \file
/// \brief
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
namespace xms
{
//----- Forward declarations ---------------------------------------------------

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

//----- Structs / Classes ------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
class XmUGrid
{
public:
  static BSHP<XmUGrid> New(const VecPt3d& a_points, const VecInt& a_cellStream);
  static BSHP<XmUGrid> New();
  virtual ~XmUGrid();

  static bool ValidCellStream(const VecInt& a_cellStream);

  /// \cond
  virtual int GetNumberOfPoints() const = 0;
  virtual int GetNumberOfCells() const = 0;

  virtual Pt3d GetPoint(const int a_pointIdx) const = 0;
  virtual bool SetPoint(const int a_pointIdx, const Pt3d& a_point) = 0;

  virtual XmUGridCellType GetCellType(const int a_cellIdx) const = 0;
  virtual int GetCellDimension(const int a_cellIdx) const = 0;
  virtual std::vector<int> GetDimensionCount() const = 0;
  virtual int GetNumberOfCellEdges(const int a_cellIdx) const = 0;
  virtual int GetNumberOfCellFaces(const int a_cellIdx) const = 0;


  virtual const VecPt3d& GetPoints() const = 0;
  virtual void SetPoints(const VecPt3d& a_points) = 0;

  virtual VecInt GetPointCells(const int a_pointIdx) const = 0;


  virtual bool GetSingleCellStream(const int a_cellIdx, VecInt& a_cellStream) const = 0;
  virtual const VecInt& GetCellStream() const = 0;
  virtual bool SetCellStream(const VecInt& a_cellStream) = 0;

private:
  XM_DISALLOW_COPY_AND_ASSIGN(XmUGrid)
  /// \endcond

protected:
  XmUGrid();
};

//----- Function prototypes ----------------------------------------------------

} // namespace xms
