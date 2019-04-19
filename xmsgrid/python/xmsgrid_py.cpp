//------------------------------------------------------------------------------
/// \file
/// \brief root module for xmsgrid Python bindings.
/// \copyright (C) Copyright Aquaveo 2018. Distributed under FreeBSD License
/// (See accompanying file LICENSE or https://aqaveo.com/bsd/license.txt)
//------------------------------------------------------------------------------

//----- Included files ---------------------------------------------------------
#include <pybind11/pybind11.h>
#include <xmsgrid/python/geometry/geometry_py.h>
#include <xmsgrid/python/triangulate/triangulate_py.h>
#include <xmsgrid/python/ugrid/ugrid_py.h>

//----- Namespace declaration --------------------------------------------------
namespace py = pybind11;

//----- Python Interface -------------------------------------------------------
#ifndef XMS_VERSION
  #define XMS_VERSION "99.99.99";
#endif


//------ Primary Module --------------------------------------------------------
PYBIND11_MODULE(_xmsgrid, m) {
    m.doc() = "Python bindings for xmsgrid"; // optional module docstring
    m.attr("__version__") = XMS_VERSION;
    // Triangulate module
    py::module modTriangulate = m.def_submodule("triangulate");
    initTriangulate(modTriangulate);
    // Geometry module
    py::module modGeometry = m.def_submodule("geometry");
    initGeometry(modGeometry);
    // UGrid module
    py::module modUGrid = m.def_submodule("ugrid");
    initUGrid(modUGrid);
}

