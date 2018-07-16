//------------------------------------------------------------------------------
/// \file
/// \brief
/// \copyright (C) Copyright Aquaveo 2018. Distributed under the xmsng
///  Software License, Version 1.0. (See accompanying file
///  LICENSE_1_0.txt or copy at http://www.aquaveo.com/xmsng/LICENSE_1_0.txt)
//------------------------------------------------------------------------------

//----- Included files ---------------------------------------------------------
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <boost/shared_ptr.hpp>
#include <xmsgrid/ugrid/XmUGrid.h>

//----- Namespace declaration --------------------------------------------------
namespace py = pybind11;

//----- Python Interface -------------------------------------------------------
PYBIND11_DECLARE_HOLDER_TYPE(T, boost::shared_ptr<T>);

void initXmUGrid(py::module &m) {
    py::class_<xms::XmUGrid, boost::shared_ptr<xms::XmUGrid>> xmUgrid(m, "XmUGrid");
    //     .def(py::init(&xms::XmUGrid::New))

    // UGrid CellType
    py::enum_<xms::XmUGridCellType>(xmUgrid, "xmugrid_celltype_enum",
                                    "ugrid_celltype_enum for XmUGrid class")
        .value("XMU_INVALID_CELL_TYPE", xms::XmUGridCellType::XMU_INVALID_CELL_TYPE)
        .value("XMU_EMPTY_CELL", xms::XmUGridCellType::XMU_EMPTY_CELL)
        .value("XMU_VERTEX", xms::XmUGridCellType::XMU_VERTEX)
        .value("XMU_POLY_VERTEX", xms::XmUGridCellType::XMU_POLY_VERTEX)
        .value("XMU_LINE", xms::XmUGridCellType::XMU_LINE)
        .value("XMU_POLY_LINE", xms::XmUGridCellType::XMU_POLY_LINE)
        .value("XMU_TRIANGLE", xms::XmUGridCellType::XMU_TRIANGLE)
        .value("XMU_TRIANGLE_STRIP", xms::XmUGridCellType::XMU_TRIANGLE_STRIP)
        .value("XMU_POLYGON", xms::XmUGridCellType::XMU_POLYGON)
        .value("XMU_PIXEL", xms::XmUGridCellType::XMU_PIXEL)
        .value("XMU_QUAD", xms::XmUGridCellType::XMU_QUAD)
        .value("XMU_TETRA", xms::XmUGridCellType::XMU_TETRA)
        .value("XMU_VOXEL", xms::XmUGridCellType::XMU_VOXEL)
        .value("XMU_HEXAHEDRON", xms::XmUGridCellType::XMU_HEXAHEDRON)
        .value("XMU_WEDGE", xms::XmUGridCellType::XMU_WEDGE)
        .value("XMU_PYRAMID", xms::XmUGridCellType::XMU_PYRAMID)
        .value("XMU_PENTAGONAL_PRISM", xms::XmUGridCellType::XMU_PENTAGONAL_PRISM)
        .value("XMU_HEXAGONAL_PRISM", xms::XmUGridCellType::XMU_HEXAGONAL_PRISM)
        .value("XMU_QUADRATIC_EDGE", xms::XmUGridCellType::XMU_QUADRATIC_EDGE)
        .value("XMU_QUADRATIC_TRIANGLE", xms::XmUGridCellType::XMU_QUADRATIC_TRIANGLE)
        .value("XMU_QUADRATIC_QUAD", xms::XmUGridCellType::XMU_QUADRATIC_QUAD)
        .value("XMU_QUADRATIC_POLYGON", xms::XmUGridCellType::XMU_QUADRATIC_POLYGON)
        .value("XMU_QUADRATIC_TETRA", xms::XmUGridCellType::XMU_QUADRATIC_TETRA)
        .value("XMU_QUADRATIC_HEXAHEDRON", xms::XmUGridCellType::XMU_QUADRATIC_HEXAHEDRON)
        .value("XMU_QUADRATIC_WEDGE", xms::XmUGridCellType::XMU_QUADRATIC_WEDGE)
        .value("XMU_QUADRATIC_PYRAMID", xms::XmUGridCellType::XMU_QUADRATIC_PYRAMID)
        .value("XMU_BIQUADRATIC_QUAD", xms::XmUGridCellType::XMU_BIQUADRATIC_QUAD)
        .value("XMU_TRIQUADRATIC_HEXAHEDRON", xms::XmUGridCellType::XMU_TRIQUADRATIC_HEXAHEDRON)
        .value("XMU_QUADRATIC_LINEAR_QUAD", xms::XmUGridCellType::XMU_QUADRATIC_LINEAR_QUAD)
        .value("XMU_QUADRATIC_LINEAR_WEDGE", xms::XmUGridCellType::XMU_QUADRATIC_LINEAR_WEDGE)
        .value("XMU_BIQUADRATIC_QUADRATIC_WEDGE", xms::XmUGridCellType::XMU_BIQUADRATIC_QUADRATIC_WEDGE)
        .value("XMU_BIQUADRATIC_QUADRATIC_HEXAHEDRON", xms::XmUGridCellType::XMU_BIQUADRATIC_QUADRATIC_HEXAHEDRON)
        .value("XMU_BIQUADRATIC_TRIANGLE", xms::XmUGridCellType::XMU_BIQUADRATIC_TRIANGLE)
        .value("XMU_CUBIC_LINE", xms::XmUGridCellType::XMU_CUBIC_LINE)
        .value("XMU_CONVEX_POINT_SET", xms::XmUGridCellType::XMU_CONVEX_POINT_SET)
        .value("XMU_POLYHEDRON", xms::XmUGridCellType::XMU_POLYHEDRON)
        .value("XMU_PARAMETRIC_CURVE", xms::XmUGridCellType::XMU_PARAMETRIC_CURVE)
        .value("XMU_PARAMETRIC_SURFACE", xms::XmUGridCellType::XMU_PARAMETRIC_SURFACE)
        .value("XMU_PARAMETRIC_TRI_SURFACE", xms::XmUGridCellType::XMU_PARAMETRIC_TRI_SURFACE)
        .value("XMU_PARAMETRIC_QUAD_SURFACE", xms::XmUGridCellType::XMU_PARAMETRIC_QUAD_SURFACE)
        .value("XMU_PARAMETRIC_TETRA_REGION", xms::XmUGridCellType::XMU_PARAMETRIC_TETRA_REGION)
        .value("XMU_PARAMETRIC_HEX_REGION", xms::XmUGridCellType::XMU_PARAMETRIC_HEX_REGION)
        .value("XMU_HIGHER_ORDER_EDGE", xms::XmUGridCellType::XMU_HIGHER_ORDER_EDGE)
        .value("XMU_HIGHER_ORDER_TRIANGLE", xms::XmUGridCellType::XMU_HIGHER_ORDER_TRIANGLE)
        .value("XMU_HIGHER_ORDER_QUAD", xms::XmUGridCellType::XMU_HIGHER_ORDER_QUAD)
        .value("XMU_HIGHER_ORDER_POLYGON", xms::XmUGridCellType::XMU_HIGHER_ORDER_POLYGON)
        .value("XMU_HIGHER_ORDER_TETRAHEDRON", xms::XmUGridCellType::XMU_HIGHER_ORDER_TETRAHEDRON)
        .value("XMU_HIGHER_ORDER_WEDGE", xms::XmUGridCellType::XMU_HIGHER_ORDER_WEDGE)
        .value("XMU_HIGHER_ORDER_PYRAMID", xms::XmUGridCellType::XMU_HIGHER_ORDER_PYRAMID)
        .value("XMU_HIGHER_ORDER_HEXAHEDRON", xms::XmUGridCellType::XMU_HIGHER_ORDER_HEXAHEDRON)
        .value("XMU_NUMBER_OF_CELL_TYPES", xms::XmUGridCellType::XMU_NUMBER_OF_CELL_TYPES)
        .export_values();

    // UGrid FaceOrientation
    py::enum_<xms::XmUGridFaceOrientation>(xmUgrid, "xmugrid_faceorientation_enum",
                                    "xmugrid_faceorientation_enum for XmUGrid class")
        .value("XMU_ORIENTATION_UNKNOWN", xms::XmUGridFaceOrientation::XMU_ORIENTATION_UNKNOWN)
        .value("XMU_ORIENTATION_SIDE", xms::XmUGridFaceOrientation::XMU_ORIENTATION_SIDE)
        .value("XMU_ORIENTATION_TOP", xms::XmUGridFaceOrientation::XMU_ORIENTATION_TOP)
        .value("XMU_ORIENTATION_BOTTOM", xms::XmUGridFaceOrientation::XMU_ORIENTATION_BOTTOM)
        .export_values();
}