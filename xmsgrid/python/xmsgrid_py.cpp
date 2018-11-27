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
#ifndef XMS_VERSION
  #define XMS_VERSION "99.99.99";
#endif


//------ Primary Module --------------------------------------------------------
PYBIND11_MODULE(xmsgrid, m) {
    m.doc() = "Python bindings for xmsgrid"; // optional module docstring
    m.attr("__version__") = XMS_VERSION;

    const char* misc_doc = R"pydoc(
        Xmsgrid is a grid geometry library used in xms libraries and products. 
        The library supports unstructured grids with 0D, 1D, 2D and 3D elements. 
        Contains functions to read and write unstructered grids.
    )pydoc"; 
    // UGrid module
    py::module modUGrid = m.def_submodule("ugrid", misc_doc);
    initUGrid(modUGrid);
}

