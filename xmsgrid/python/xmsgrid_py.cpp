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
        Xmsgrid is a grid geometry library used in xms libraries and products. 
        The library supports unstructured grids with 0D, 1D, 2D and 3D elements. 
        Contains functions to read and write unstructered grids.
    )pydoc"; 
    // UGrid module
    py::module modUGrid = m.def_submodule("ugrid", misc_doc);
    initUGrid(modUGrid);
}

