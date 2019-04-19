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
#include <xmsgrid/triangulate/TrTin.h>
#include <xmsgrid/triangulate/TrTriangulatorPoints.h>
#include <iostream>
#include <fstream>


//----- Namespace declaration --------------------------------------------------
namespace py = pybind11;

//----- Python Interface -------------------------------------------------------
PYBIND11_DECLARE_HOLDER_TYPE(T, boost::shared_ptr<T>);

void initTrTin(py::module &m) {
  // Class
  py::class_<xms::TrTin, boost::shared_ptr<xms::TrTin>> iTrTin(m, "TrTin");

  // init
  iTrTin.def(py::init([](py::iterable pts, py::iterable tris) {
    boost::shared_ptr<xms::TrTin> rval(xms::TrTin::New());
    boost::shared_ptr<xms::VecPt3d> vec_pts = xms::VecPt3dFromPyIter(pts);
    boost::shared_ptr<xms::VecInt> vec_tris = xms::VecIntFromPyIter(tris);
    rval->SetPoints(vec_pts);
    rval->SetTriangles(vec_tris);
    return rval;
  }), py::arg("pts"), py::arg("tris") = py::make_tuple());

  // ---------------------------------------------------------------------------
  // function: Triangulate
  // ---------------------------------------------------------------------------
  iTrTin.def("Triangulate", [](xms::TrTin &self) {
      boost::shared_ptr<xms::VecPt3d> vec_pts = self.PointsPtr();
      if (!vec_pts || vec_pts->empty())
      {
        throw std::length_error("No points defined in TIN.");
      }
      boost::shared_ptr<xms::VecInt> vec_tris(new xms::VecInt());
      boost::shared_ptr<xms::VecInt2d> vec_adj_tris(new xms::VecInt2d());
      xms::TrTriangulatorPoints triangulator(*vec_pts, *vec_tris, &(*vec_adj_tris));
      triangulator.Triangulate();
      self.SetGeometry(vec_pts, vec_tris, vec_adj_tris);
  });
  // ---------------------------------------------------------------------------
  // function: SetPoints
  // ---------------------------------------------------------------------------
  iTrTin.def("SetPoints", [](xms::TrTin &self, py::iterable points) {
      BSHP<xms::VecPt3d> vec_pts = xms::VecPt3dFromPyIter(points);
      self.SetPoints(vec_pts);
  }, py::arg("points"));
  // ---------------------------------------------------------------------------
  // function: SetTriangles
  // ---------------------------------------------------------------------------
  iTrTin.def("SetTriangles", [](xms::TrTin &self, py::iterable triangles) {
      BSHP<xms::VecInt> vec_tris = xms::VecIntFromPyIter(triangles);
      self.SetTriangles(vec_tris);
  }, py::arg("triangles"));
  // ---------------------------------------------------------------------------
  // function: SetTrianglesAdjacentToPoints
  // ---------------------------------------------------------------------------
  iTrTin.def("SetTrianglesAdjacentToPoints", [](xms::TrTin &self, py::iterable triangles_adjacent) {
      BSHP<xms::VecInt2d> vec_tris_adj = xms::VecInt2dFromPyIter(triangles_adjacent);
      self.SetTrianglesAdjacentToPoints(vec_tris_adj);
  }, py::arg("triangles_adjacent"));
  // ---------------------------------------------------------------------------
  // function: SetGeometry
  // ---------------------------------------------------------------------------
  iTrTin.def("SetGeometry", [](xms::TrTin &self, py::iterable pts, py::iterable tris, py::iterable tris_adj) {
      boost::shared_ptr<xms::VecPt3d> vec_pts = xms::VecPt3dFromPyIter(pts);
      boost::shared_ptr<xms::VecInt> vec_tris = xms::VecIntFromPyIter(tris);
      boost::shared_ptr<xms::VecInt2d> vec_tris_adj = xms::VecInt2dFromPyIter(tris_adj);
      self.SetGeometry(vec_pts, vec_tris, vec_tris_adj);
  }, py::arg("pts"), py::arg("tris"), py::arg("tris_adj"));
  // ---------------------------------------------------------------------------
  // function: Points
  // ---------------------------------------------------------------------------
  iTrTin.def_property_readonly("Points", [](xms::TrTin &self) -> py::iterable {
      xms::VecPt3d pts = self.Points();
      return xms::PyIterFromVecPt3d(pts);
  });
  // ---------------------------------------------------------------------------
  // function: Triangles
  // ---------------------------------------------------------------------------
  iTrTin.def_property_readonly("Triangles", [](xms::TrTin &self) -> py::iterable {
      xms::VecInt tris = self.Triangles();
      return xms::PyIterFromVecInt(tris);
  });
  // ---------------------------------------------------------------------------
  // function: TrianglesAdjacentToPoints
  // ---------------------------------------------------------------------------
  iTrTin.def_property_readonly("TrianglesAdjacentToPoints", [](xms::TrTin &self) -> py::iterable {
      xms::VecInt2d tris_adj = self.TrisAdjToPts();
      return xms::PyIterFromVecInt2d(tris_adj);
  });
  // ---------------------------------------------------------------------------
  // function: NumPoints
  // ---------------------------------------------------------------------------
  iTrTin.def_property_readonly("NumPoints", &xms::TrTin::NumPoints);
  // ---------------------------------------------------------------------------
  // function: NumTriangles
  // ---------------------------------------------------------------------------
  iTrTin.def_property_readonly("NumTriangles", &xms::TrTin::NumTriangles);
  // ---------------------------------------------------------------------------
  // function: TriangleFromEdge
  // ---------------------------------------------------------------------------
  iTrTin.def("TriangleFromEdge", [](xms::TrTin &self, int pt1, int pt2) -> py::tuple {
      int tri, localPt1, localPt2;
      bool ret = self.TriangleFromEdge(pt1, pt2, tri, localPt1, localPt2);
      return py::make_tuple(ret, tri, localPt1, localPt2);
  }, py::arg("pt1"), py::arg("pt2"));
  // ---------------------------------------------------------------------------
  // function: TriangleAdjacentToEdge
  // ---------------------------------------------------------------------------
  iTrTin.def("TriangleAdjacentToEdge", [](xms::TrTin &self, int pt1, int pt2) -> int {
      return self.TriangleAdjacentToEdge(pt1, pt2);
  }, py::arg("pt1"), py::arg("pt2"));
  // ---------------------------------------------------------------------------
  // function: LocalIndex
  // ---------------------------------------------------------------------------
  iTrTin.def("LocalIndex", &xms::TrTin::LocalIndex, py::arg("tri"), py::arg("pt"));
  // ---------------------------------------------------------------------------
  // function: GlobalIndex
  // ---------------------------------------------------------------------------
  iTrTin.def("GlobalIndex", &xms::TrTin::GlobalIndex, py::arg("tri"), py::arg("pt"));
  // ---------------------------------------------------------------------------
  // function: VerticesAreAdjacent
  // ---------------------------------------------------------------------------
  iTrTin.def("VerticesAreAdjacent", &xms::TrTin::VerticesAreAdjacent, py::arg("pt1"),py::arg("pt2"));
  // ---------------------------------------------------------------------------
  // function: CommonEdgeIndex
  // ---------------------------------------------------------------------------
  iTrTin.def("CommonEdgeIndex", &xms::TrTin::CommonEdgeIndex, py::arg("tri"), py::arg("adj_tri"));
  // ---------------------------------------------------------------------------
  // function: AdjacentTriangle
  // ---------------------------------------------------------------------------
  iTrTin.def("AdjacentTriangle", &xms::TrTin::AdjacentTriangle, py::arg("tri"), py::arg("edge"));
  // ---------------------------------------------------------------------------
  // function: TriangleCentroid
  // ---------------------------------------------------------------------------
  iTrTin.def("TriangleCentroid", [](xms::TrTin &self, int tri) -> py::tuple {
      xms::Pt3d pt = self.TriangleCentroid(tri);
      return xms::PyIterFromPt3d(pt);
  }, py::arg("tri"));
  // ---------------------------------------------------------------------------
  // function: TriangleArea
  // ---------------------------------------------------------------------------
  iTrTin.def("TriangleArea", &xms::TrTin::TriangleArea, py::arg("tri"));
  // ---------------------------------------------------------------------------
  // function: NextBoundaryPoint
  // ---------------------------------------------------------------------------
  iTrTin.def("NextBoundaryPoint", &xms::TrTin::NextBoundaryPoint, py::arg("point"));
  // ---------------------------------------------------------------------------
  // function: PreviousBoundaryPoint
  // ---------------------------------------------------------------------------
  iTrTin.def("PreviousBoundaryPoint", &xms::TrTin::PreviousBoundaryPoint, py::arg("point"));
  // ---------------------------------------------------------------------------
  // function: GetBoundaryPoints
  // ---------------------------------------------------------------------------
  iTrTin.def("GetBoundaryPoints", [](xms::TrTin &self) -> py::iterable {
      xms::VecInt bp;
      self.GetBoundaryPoints(bp);
      return xms::PyIterFromVecInt(bp);
  });
  // ---------------------------------------------------------------------------
  // function: GetBoundaryPolys
  // ---------------------------------------------------------------------------
  iTrTin.def("GetBoundaryPolys", [](xms::TrTin &self) -> py::tuple {
      xms::VecInt2d bp;
      self.GetBoundaryPolys(bp);
      return xms::PyIterFromVecInt2d(bp);
  });
  // ---------------------------------------------------------------------------
  // function: GetExtents
  // ---------------------------------------------------------------------------
  iTrTin.def("GetExtents", [](xms::TrTin &self) -> py::tuple {
      xms::Pt3d pt_min, pt_max;
      self.GetExtents(pt_min, pt_max);
      auto min_pt = xms::PyIterFromPt3d(pt_min);
      auto max_pt = xms::PyIterFromPt3d(pt_max);
      return py::make_tuple(min_pt, max_pt);
  });
  // ---------------------------------------------------------------------------
  // function: ExportTinFile
  // ---------------------------------------------------------------------------
  iTrTin.def("ExportTinFile", [](xms::TrTin &self, std::string fname) {
      std::filebuf fb;
      fb.open(fname, std::ios::out);
      std::string msg = "Unable to open file " + fname + ".";
      if (!fb.is_open())
        throw std::runtime_error(msg.c_str());
      std::ostream os(&fb);
      if (os.bad())
        throw std::runtime_error(msg.c_str());
      self.ExportTinFile(os);
      fb.close();
  }, py::arg("fname"));
  // ---------------------------------------------------------------------------
  // function: SwapEdge
  // ---------------------------------------------------------------------------
  iTrTin.def("SwapEdge", &xms::TrTin::SwapEdge, py::arg("tri_A"), py::arg("tri_B"), py::arg("check_angle"));
  // ---------------------------------------------------------------------------
  // function: DeleteTriangles
  // ---------------------------------------------------------------------------
  iTrTin.def("DeleteTriangles", [](xms::TrTin &self, py::iterable tris) {
      xms::SetInt to_delete;
      for (auto item : tris) {
        to_delete.insert(item.cast<int>());
      }
      self.DeleteTriangles(to_delete);
  }, py::arg("tris"));
  // ---------------------------------------------------------------------------
  // function: DeletePoints
  // ---------------------------------------------------------------------------
  iTrTin.def("DeletePoints", [](xms::TrTin &self, py::iterable pts) {
      xms::SetInt to_delete;
      for (auto item : pts) {
        to_delete.insert(item.cast<int>());
      }
      self.DeletePoints(to_delete);
  },  py::arg("pts"));
  // ---------------------------------------------------------------------------
  // function: OptimizeTriangulation
  // ---------------------------------------------------------------------------
  iTrTin.def("OptimizeTriangulation", &xms::TrTin::OptimizeTriangulation);
  // ---------------------------------------------------------------------------
  // function: OptimizeTriangulation
  // ---------------------------------------------------------------------------
  iTrTin.def("RemoveLongThinTrianglesOnPerimeter", &xms::TrTin::RemoveLongThinTrianglesOnPerimeter);
  // ---------------------------------------------------------------------------
  // function: BuildTrisAdjToPts
  // ---------------------------------------------------------------------------
  iTrTin.def("BuildTrisAdjToPts", &xms::TrTin::BuildTrisAdjToPts);
  // ---------------------------------------------------------------------------
  // function: Clear
  // ---------------------------------------------------------------------------
  iTrTin.def("Clear", &xms::TrTin::Clear);
}