//------------------------------------------------------------------------------
/// \file
/// \brief Python bindings for XmUGridUtils.h.
/// \copyright (C) Copyright Aquaveo 2018. Distributed under FreeBSD License
/// (See accompanying file LICENSE or https://aqaveo.com/bsd/license.txt)
//------------------------------------------------------------------------------

//----- Included files ---------------------------------------------------------
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <boost/shared_ptr.hpp>
#include <xmscore/python/misc/PyUtils.h>
#include <xmsgrid/ugrid/XmUGridUtils.h>
#include <xmsgrid/ugrid/XmUGrid.h>

//----- Namespace declaration --------------------------------------------------
namespace py = pybind11;

//----- Python Interface -------------------------------------------------------
PYBIND11_DECLARE_HOLDER_TYPE(T, boost::shared_ptr<T>);

void initXmUGridUtils(py::module &m) {
  py::module modXmUGridUtils = m.def_submodule("ugrid_utils");
  // ---------------------------------------------------------------------------
  // function: read_ugrid_from_ascii_file
  // --------------------------------------------------------------------------- 
  const char* read_ugrid_from_ascii_file_doc = R"pydoc(
    Read XmUGrid from an ASCII file.

    Args: 
        file_path (str): Filename to read including path, file name, and extension.

    Returns:
        XmUGrid: The UGrid that was read from the file.
  )pydoc";
  modXmUGridUtils.def("read_ugrid_from_ascii_file", 
    &xms::XmReadUGridFromAsciiFile,
        read_ugrid_from_ascii_file_doc,py::arg("file_path"));
  // ---------------------------------------------------------------------------
  // function: write_ugrid_to_ascii_file
  // --------------------------------------------------------------------------- 
  const char* write_ugrid_to_ascii_file_doc = R"pydoc(
    Write an XmUGrid to an ASCII file.

    Args: 
        ugrid (XmUGrid): The XmUGrid to write to file.

        file_path (str): Filename to write including path, file name, and extension.
  )pydoc";
  modXmUGridUtils.def("write_ugrid_to_ascii_file", 
    &xms::XmWriteUGridToAsciiFile,
        write_ugrid_to_ascii_file_doc,py::arg("ugrid"),py::arg("file_path"));
}
