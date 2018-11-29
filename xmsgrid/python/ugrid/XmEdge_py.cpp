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
#include <xmscore/python/misc/PyUtils.h>
#include <xmsgrid/ugrid/XmEdge.h>

//----- Namespace declaration --------------------------------------------------
namespace py = pybind11;

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

//----- Python Interface -------------------------------------------------------

void initXmEdge(py::module &m)
{
  py::module modXmEdge = m.def_submodule("edge");
  // ---------------------------------------------------------------------------
  // function: edges_equivalent
  // --------------------------------------------------------------------------- 
  const char* edges_equivalent_doc = R"pydoc(
    Test if two edges are the same ignoring direction

    Args: 
        a_edge1 (iterable): The first edge to compare against
        a_edge2 (iterable): The second edge to compare against

    Returns:
        bool: If two edges are same when indexes are in sorted order
  )pydoc";
  modXmEdge.def("edges_equivalent", [](py::iterable a_edge1, py::iterable a_edge2) -> bool {
    xms::XmEdge edge1 = XmEdgeFromPyIter(a_edge1);
    xms::XmEdge edge2 = XmEdgeFromPyIter(a_edge2);
    return XmEdgesEquivalent(edge1, edge2);
  }, edges_equivalent_doc, py::arg("a_edge1"), py::arg("a_edge2"));
}
