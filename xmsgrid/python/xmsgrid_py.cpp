//------------------------------------------------------------------------------
/// \file
/// \brief root module for xmsgrid Python bindings.
/// \copyright (C) Copyright Aquaveo 2018. Distributed under the xmsng
///  Software License, Version 1.0. (See accompanying file
///  LICENSE_1_0.txt or copy at http://www.aquaveo.com/xmsng/LICENSE_1_0.txt)
//------------------------------------------------------------------------------

//----- Included files ---------------------------------------------------------
#include <pybind11/pybind11.h>
#include <xmsgrid/python/ugrid/ugrid_py.h>

//----- Namespace declaration --------------------------------------------------
namespace py = pybind11;

//----- Python Interface -------------------------------------------------------
std::string version() {
    return "1.0.0";
}


//------ Primary Module --------------------------------------------------------
PYBIND11_MODULE(xmsgrid_py, m) {
    m.doc() = "Python bindings for xmsgrid"; // optional module docstring
    m.def("version", &version,
          "Get current version of xmsgrid Python bindings.");

    // UGrid module
    py::module modUGrid = m.def_submodule("ugrid");
    initUGrid(modUGrid);
}

