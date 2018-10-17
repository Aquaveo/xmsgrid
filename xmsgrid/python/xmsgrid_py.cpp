//------------------------------------------------------------------------------
/// \file
/// \brief root module for xmsgrid Python bindings.
/// \copyright (C) Copyright Aquaveo 2018. Distributed under FreeBSD License
/// (See accompanying file LICENSE or https://aqaveo.com/bsd/license.txt)
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
    const char* misc_doc = R"pydoc(
        The misc module of the xmsgrid python library contains classes and
        functions that are shared between all of the xms family of libraries.
        These functions and classes can be used in any of the library to ensure
        that functionality is standardized. Xmsgrid is a grid geometry library 
        used in xms libraries and products.
    )pydoc"; 
    // UGrid module
    py::module modUGrid = m.def_submodule("ugrid", misc_doc);
    initUGrid(modUGrid);
}

