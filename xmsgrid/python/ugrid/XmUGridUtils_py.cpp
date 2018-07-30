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
#include <xmsgrid/ugrid/XmUGridUtils.h>
#include <xmsgrid/ugrid/XmUGrid.h>

//----- Namespace declaration --------------------------------------------------
namespace py = pybind11;

//----- Python Interface -------------------------------------------------------
PYBIND11_DECLARE_HOLDER_TYPE(T, boost::shared_ptr<T>);

void initXmUGridUtils(py::module &m) {
    py::module modXmUGridUtils = m.def_submodule("XmUGridUtils")
      .def("xm_write_ugrid_to_ascii_file", &xms::XmWriteUGridToAsciiFile)
      .def("cross", [](py::iterable Origin, py::iterable A, py::iterable B) -> double {
          xms::Pt3d origin = xms::Pt3dFromPyIter(Origin);
          xms::Pt3d a = xms::Pt3dFromPyIter(A);
          xms::Pt3d b = xms::Pt3dFromPyIter(B);
          return xms::cross(origin, a, b);
      },"2D cross product of two points",py::arg("Origin"),py::arg("A"),py::arg("B"))
      .def("do_line_segments_cross", [](py::iterable seg1_pt1, py::iterable seg1_pt2,
                                        py::iterable seg2_pt1, py::iterable seg2_pt2) -> bool {
          xms::Pt3d s1p1 = xms::Pt3dFromPyIter(seg1_pt1);
          xms::Pt3d s1p2 = xms::Pt3dFromPyIter(seg1_pt2);
          xms::Pt3d s2p1 = xms::Pt3dFromPyIter(seg2_pt1);
          xms::Pt3d s2p2 = xms::Pt3dFromPyIter(seg2_pt2);
          return DoLineSegmentsCross(s1p1, s1p2, s2p1, s2p2);
      },"Determine whether 2 line segments intersect",
        py::arg("seg1_pt1"),py::arg("set1_pt2"),py::arg("seg2_pt1"),py::arg("seg2_pt2")
     )
    ;
}
