//------------------------------------------------------------------------------
/// \file
/// \brief Python bindings for XmUGridUtils.h.
/// \copyright (C) Copyright Aquaveo 2018. Distributed under FreeBSD License
/// (See accompanying file LICENSE or https://aquaveo.com/bsd/license.txt)
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

//------------------------------------------------------------------------------
/// \brief Create a set of ints from a Python iterable.
/// \param[in] a_iter py::iterable object that represents a set of ints.
/// \return The set of ints.
//------------------------------------------------------------------------------
xms::SetInt XmSetIntFromPyIter(const py::iterable& a_iter)
{
  xms::SetInt result;
  for (const auto& item : a_iter)
  {
    result.insert(py::cast<int>(item));
  }
  return result;
} // XmSetIntFromPyIter

} // namespace

void initXmUGridUtils(py::module& m)
{
  py::module modXmUGridUtils = m.def_submodule("ugrid_utils");
  // ---------------------------------------------------------------------------
  // function: read_ugrid_from_ascii_file
  // ---------------------------------------------------------------------------
  modXmUGridUtils.def("read_ugrid_from_ascii_file", &xms::XmReadUGridFromAsciiFile,
                      py::arg("file_path"));
  // ---------------------------------------------------------------------------
  // function: write_ugrid_to_ascii_file
  // ---------------------------------------------------------------------------
  modXmUGridUtils.def("write_ugrid_to_ascii_file", &xms::XmWriteUGridToAsciiFile, py::arg("ugrid"),
                      py::arg("file_path"));

  // ---------------------------------------------------------------------------
  // function: edges_equivalent
  // ---------------------------------------------------------------------------
  modXmUGridUtils.def(
    "edges_equivalent",
    [](py::iterable a_edge1, py::iterable a_edge2) -> bool {
      xms::XmEdge edge1 = XmEdgeFromPyIter(a_edge1);
      xms::XmEdge edge2 = XmEdgeFromPyIter(a_edge2);
      return XmEdgesEquivalent(edge1, edge2);
    },
    py::arg("edge1"), py::arg("edge2"));

  // ---------------------------------------------------------------------------
  // function: remove_points
  // ---------------------------------------------------------------------------
  modXmUGridUtils.def(
    "remove_points",
    [](std::shared_ptr<xms::XmUGrid> a_ugrid, py::iterable a_pointIds) -> std::shared_ptr<xms::XmUGrid> {
      xms::SetInt pointIds = XmSetIntFromPyIter(a_pointIds);
      return XmRemovePoints(*a_ugrid, pointIds);
    },
    py::arg("ugrid"), py::arg("ids"));

  // ---------------------------------------------------------------------------
  // function: remove_cells
  // ---------------------------------------------------------------------------
  modXmUGridUtils.def(
    "remove_cells",
    [](std::shared_ptr<xms::XmUGrid> a_ugrid, py::iterable a_cellIds,
       bool a_deleteOrphanedPoints) -> std::shared_ptr<xms::XmUGrid> {
      xms::SetInt cellIds = XmSetIntFromPyIter(a_cellIds);
      return XmRemoveCells(*a_ugrid, cellIds, a_deleteOrphanedPoints);
    },
    py::arg("ugrid"), py::arg("ids"), py::arg("remove_orphaned_points") = false);

  // ---------------------------------------------------------------------------
  // function: remove_points_and_cells
  // ---------------------------------------------------------------------------
  modXmUGridUtils.def(
    "remove_points_and_cells",
    [](std::shared_ptr<xms::XmUGrid> a_ugrid, py::iterable a_pointIds,
        py::iterable a_cellIds) -> std::shared_ptr<xms::XmUGrid> {
      xms::SetInt pointIds = XmSetIntFromPyIter(a_pointIds);
      xms::SetInt cellIds = XmSetIntFromPyIter(a_cellIds);
      xms::VecPt3d newPoints;
      xms::VecInt newCells;

      XmRemovePointsAndCells(*a_ugrid, pointIds, cellIds, newPoints, newCells);
      return xms::XmUGrid::New(newPoints, newCells);
    },
    py::arg("ugrid"), py::arg("point_ids"), py::arg("cell_ids"));

  // ---------------------------------------------------------------------------
  // function: clip_ugrid
  // ---------------------------------------------------------------------------
  modXmUGridUtils.def(
      "clip_ugrid",
      [](std::shared_ptr<xms::XmUGrid> a_ugrid, py::iterable a_loops)
      -> std::shared_ptr<xms::XmUGrid> {
        auto loops = xms::VecInt2dFromPyIter(a_loops);
        return xms::XmClipUGrid(a_ugrid, *loops);
      }, py::arg("ugrid"), py::arg("loops"));
}
