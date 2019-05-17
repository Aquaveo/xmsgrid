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
#include <xmsgrid/ugrid/XmEdge.h>

//----- Namespace declaration --------------------------------------------------
namespace py = pybind11;

//----- Python Interface -------------------------------------------------------
PYBIND11_DECLARE_HOLDER_TYPE(T, boost::shared_ptr<T>);

namespace {

//------------------------------------------------------------------------------
/// \brief Create XmEdge from py::iterable
/// \param[in] a_intpair py::iterable object that represents an XmEdge
/// \return The edge.
//------------------------------------------------------------------------------
xms::XmEdge XmEdgeFromPyIter(const py::iterable& a_intpair)
{
  py::tuple pr = a_intpair.cast<py::tuple>();
  if (py::len(pr) != 2) {
    throw py::type_error("arg must be an 2-tuple");
  }
  else {
    xms::XmEdge edge(pr[0].cast<int>(), pr[1].cast<int>());
    return edge;
  }
} // XmEdgeFromPyIter

}

void initXmUGridUtils(py::module &m) {
  py::module modXmUGridUtils = m.def_submodule("ugrid_utils");
  // ---------------------------------------------------------------------------
  // function: read_ugrid_from_ascii_file
  // ---------------------------------------------------------------------------
  modXmUGridUtils.def("read_ugrid_from_ascii_file", 
    &xms::XmReadUGridFromAsciiFile, py::arg("file_path"));
  // ---------------------------------------------------------------------------
  // function: write_ugrid_to_ascii_file
  // ---------------------------------------------------------------------------
  modXmUGridUtils.def("write_ugrid_to_ascii_file", 
    &xms::XmWriteUGridToAsciiFile, py::arg("ugrid"),py::arg("file_path"));

  // ---------------------------------------------------------------------------
  // function: edges_equivalent
  // ---------------------------------------------------------------------------
  modXmUGridUtils.def("edges_equivalent", [](py::iterable a_edge1, py::iterable a_edge2) -> bool {
    xms::XmEdge edge1 = XmEdgeFromPyIter(a_edge1);
    xms::XmEdge edge2 = XmEdgeFromPyIter(a_edge2);
    return XmEdgesEquivalent(edge1, edge2);
  }, py::arg("edge1"), py::arg("edge2"));
}
