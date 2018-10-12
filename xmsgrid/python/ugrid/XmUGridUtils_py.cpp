//------------------------------------------------------------------------------
/// \file
/// \brief
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
  py::module modXmUGridUtils = m.def_submodule("XmUGridUtils");
  // ---------------------------------------------------------------------------
  // function: read_ugrid_from_ascii_file
  // --------------------------------------------------------------------------- 
  const char* read_ugrid_from_ascii_file_doc = R"pydoc(
    Read XmUGrid from an ASCII file.

    Args: 
        file_path (str): Path of the ascii file

    Returns:
        XmUGrid: The generated XmUGrid
  )pydoc";
  modXmUGridUtils.def("read_ugrid_from_ascii_file", &xms::XmReadUGridFromAsciiFile,
        read_ugrid_from_ascii_file_doc,py::arg("file_path"));
  // ---------------------------------------------------------------------------
  // function: write_ugrid_to_ascii_file
  // --------------------------------------------------------------------------- 
  const char* write_ugrid_to_ascii_file_doc = R"pydoc(
    Write XmUGrid to an ASCII file.

    Args: 
        ugrid (XmUGrid): XmUGrid to write to file
        file_path (str): Path of the ascii file to be created
  )pydoc";
  modXmUGridUtils.def("write_ugrid_to_ascii_file", &xms::XmWriteUGridToAsciiFile,
        write_ugrid_to_ascii_file_doc,py::arg("ugrid"),py::arg("file_path"));
  // ---------------------------------------------------------------------------
  // function: cross
  // --------------------------------------------------------------------------- 
  const char* cross_doc = R"pydoc(
    2D cross product of two points

    Args: 
        Origin (iterable): The point of origin
        A (iterable): The first vector
        B (iterable): The second vector

    Returns:
        float: The cross product of two points
  )pydoc";
  modXmUGridUtils.def("cross", [](py::iterable Origin, py::iterable A, py::iterable B) -> double {
          xms::Pt3d origin = xms::Pt3dFromPyIter(Origin);
          xms::Pt3d a = xms::Pt3dFromPyIter(A);
          xms::Pt3d b = xms::Pt3dFromPyIter(B);
          return xms::cross(origin, a, b);
      },cross_doc,py::arg("Origin"),py::arg("A"),py::arg("B"));
  // ---------------------------------------------------------------------------
  // function: do_line_segments_cross
  // --------------------------------------------------------------------------- 
  const char* do_line_segments_cross_doc = R"pydoc(
    Determine whether 2 line segments intersect

    Args: 
        seg1_pt1 (iterable): First point of the first line segment
        set1_pt2 (iterable): Second point of the first line segment
        seg2_pt1 (iterable): First point of the second line segment
        seg2_pt2 (iterable): Second point of the second line segment

    Returns:
        bool: Whether the line segments cross
  )pydoc";
  modXmUGridUtils.def("do_line_segments_cross", [](py::iterable seg1_pt1, py::iterable seg1_pt2,
                                        py::iterable seg2_pt1, py::iterable seg2_pt2) -> bool {
          xms::Pt3d s1p1 = xms::Pt3dFromPyIter(seg1_pt1);
          xms::Pt3d s1p2 = xms::Pt3dFromPyIter(seg1_pt2);
          xms::Pt3d s2p1 = xms::Pt3dFromPyIter(seg2_pt1);
          xms::Pt3d s2p2 = xms::Pt3dFromPyIter(seg2_pt2);
          return DoLineSegmentsCross(s1p1, s1p2, s2p1, s2p2);
      },do_line_segments_cross_doc, py::arg("seg1_pt1"),py::arg("set1_pt2"),
      py::arg("seg2_pt1"),py::arg("seg2_pt2")
     );
}
