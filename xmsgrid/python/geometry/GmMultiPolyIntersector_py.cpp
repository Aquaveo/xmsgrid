//------------------------------------------------------------------------------
/// \file
/// \brief
/// \copyright (C) Copyright Aquaveo 2023. Distributed under FreeBSD License
/// (See accompanying file LICENSE or https://aquaveo.com/bsd/license.txt)
//------------------------------------------------------------------------------

//----- Included files ---------------------------------------------------------
#include <sstream>
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>  // Needed for PyUtils.h

#include <xmscore/misc/boost_defines.h>
#include <xmscore/python/misc/PyUtils.h>
#include <xmsgrid/geometry/GmMultiPolyIntersector.h>
#include <xmsgrid/geometry/GmMultiPolyIntersectionSorterTerse.h>
#include <xmsgrid/python/geometry/geometry_py.h>

//----- Namespace declaration --------------------------------------------------
namespace py = pybind11;

//----- Python Interface -------------------------------------------------------

// Use a wrapper struct to avoid compile errors due to virtual ~GmMultiPolyIntersector() being declared protected
struct Wrapper {
  BSHP<xms::GmMultiPolyIntersector> p = nullptr;
};

void initGmMultiPolyIntersector(py::module &m) {
  // GmMultiPolyIntersector class
  py::class_<Wrapper> gmMpi(m, "GmMultiPolyIntersector");

  // ---------------------------------------------------------------------------
  // function: init
  // ---------------------------------------------------------------------------
  gmMpi.def(py::init([](py::iterable poly_points, py::iterable polys, int starting_id,
   const std::string& query) {
    BSHP<xms::VecPt3d> vec_pts = xms::VecPt3dFromPyIter(poly_points);
    BSHP<xms::VecInt2d> vec_polys = xms::VecInt2dFromPyIter(polys);
    BSHP<xms::GmMultiPolyIntersectionSorterTerse> sorter(new xms::GmMultiPolyIntersectionSorterTerse);
    Wrapper wrapper;
    wrapper.p = xms::GmMultiPolyIntersector::New(*vec_pts, *vec_polys, sorter, starting_id);
    wrapper.p->SetQuery(query == "covered_by" ? xms::GMMPIQ_COVEREDBY : xms::GMMPIQ_INTERSECTS);
    return wrapper;
  }), py::arg("poly_points"), py::arg("polys"), py::arg("starting_id") = 1, py::arg("query") = "covered_by");
  // ---------------------------------------------------------------------------
  // function: TraverseLineSegment
  // ---------------------------------------------------------------------------
  gmMpi.def("TraverseLineSegment", [](Wrapper &self, py::iterable pt1, py::iterable pt2)
   -> py::tuple {
    xms::Pt3d p1 = xms::Pt3dFromPyIter(pt1);
    xms::Pt3d p2 = xms::Pt3dFromPyIter(pt2);
    xms::VecInt poly_ids;
    xms::VecDbl t_vals;
    xms::VecPt3d pts;
    self.p->TraverseLineSegment(p1.x, p1.y, p2.x, p2.y, poly_ids, t_vals, pts);
    return py::make_tuple(xms::PyIterFromVecInt(poly_ids), xms::PyIterFromVecDbl(t_vals), xms::PyIterFromVecPt3d(pts));
  }, py::arg("pt1"), py::arg("pt2"));
  // ---------------------------------------------------------------------------
  // function: PolygonFromPoint
  // ---------------------------------------------------------------------------
  gmMpi.def("PolygonFromPoint", [](Wrapper &self, py::iterable point) -> int {
    xms::Pt3d p = xms::Pt3dFromPyIter(point);
    return self.p->PolygonFromPoint(p);
  }, py::arg("point"));
}