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
        file_path (str): Filename to read including path, file name, and
            extension.

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
        file_path (str): Filename to write including path, file name, and
            extension.
  )pydoc";
  modXmUGridUtils.def("write_ugrid_to_ascii_file", 
    &xms::XmWriteUGridToAsciiFile,
        write_ugrid_to_ascii_file_doc,py::arg("ugrid"),py::arg("file_path"));
  // ---------------------------------------------------------------------------
  // function: cross
  // --------------------------------------------------------------------------- 
  const char* cross_doc = R"pydoc(
    2D cross product of two points.

    Args: 
        Origin (iterable): Origin point for the "vectors".
        A (iterable): The first vector.
        B (iterable): The second vector.

    Returns:
        float: The cross product.
  )pydoc";
  modXmUGridUtils.def("cross", [](py::iterable Origin, py::iterable A, 
   py::iterable B) -> double {
          xms::Pt3d origin = xms::Pt3dFromPyIter(Origin);
          xms::Pt3d a = xms::Pt3dFromPyIter(A);
          xms::Pt3d b = xms::Pt3dFromPyIter(B);
          return xms::cross(origin, a, b);
      },cross_doc,py::arg("Origin"),py::arg("A"),py::arg("B"));
  // ---------------------------------------------------------------------------
  // function: do_line_segments_cross
  // --------------------------------------------------------------------------- 
  const char* do_line_segments_cross_doc = R"pydoc(
    Determine whether 2 line segments intersect.

    Args: 
        seg1_pt1 (iterable): First point 3d of line segment 1.
        set1_pt2 (iterable): Second point 3d of line segment 1.
        seg2_pt1 (iterable): First point 3d of line segment 2.
        seg2_pt2 (iterable): Second point 3d of line segment 2.

    Returns:
        bool: True if the line segments cross.
  )pydoc";
  modXmUGridUtils.def("do_line_segments_cross", [](py::iterable seg1_pt1, 
  py::iterable seg1_pt2, py::iterable seg2_pt1, py::iterable seg2_pt2) -> bool {
          xms::Pt3d s1p1 = xms::Pt3dFromPyIter(seg1_pt1);
          xms::Pt3d s1p2 = xms::Pt3dFromPyIter(seg1_pt2);
          xms::Pt3d s2p1 = xms::Pt3dFromPyIter(seg2_pt1);
          xms::Pt3d s2p2 = xms::Pt3dFromPyIter(seg2_pt2);
          return DoLineSegmentsCross(s1p1, s1p2, s2p1, s2p2);
      },do_line_segments_cross_doc, py::arg("seg1_pt1"),py::arg("set1_pt2"),
      py::arg("seg2_pt1"),py::arg("seg2_pt2")
     );
}
