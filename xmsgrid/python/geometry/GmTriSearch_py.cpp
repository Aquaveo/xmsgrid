//------------------------------------------------------------------------------
/// \file
/// \brief
/// \copyright (C) Copyright Aquaveo 2018. Distributed under FreeBSD License
/// (See accompanying file LICENSE or https://aquaveo.com/bsd/license.txt)
//------------------------------------------------------------------------------

//----- Included files ---------------------------------------------------------
#include <sstream>
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>  // Needed for PyUtils.h

#include <xmscore/misc/DynBitset.h>
#include <xmscore/python/misc/PyUtils.h>
#include <xmsgrid/geometry/GmTriSearch.h>
#include <xmsgrid/python/geometry/geometry_py.h>

//----- Namespace declaration --------------------------------------------------
namespace py = pybind11;

//----- Python Interface -------------------------------------------------------
PYBIND11_DECLARE_HOLDER_TYPE(T, boost::shared_ptr<T>);

void initGmTriSearch(py::module &m) {

  py::class_<xms::GmTriSearch, boost::shared_ptr<xms::GmTriSearch>> iGmTriSearch(m, "GmTriSearch");

  iGmTriSearch.def(py::init([](py::iterable pts, py::iterable tris) {
    boost::shared_ptr<xms::GmTriSearch> rval(xms::GmTriSearch::New());
    boost::shared_ptr<xms::VecPt3d> vec_pts = xms::VecPt3dFromPyIter(pts);
    boost::shared_ptr<xms::VecInt> vec_tris = xms::VecIntFromPyIter(tris);
    rval->TrisToSearch(vec_pts, vec_tris);
    return rval;
  }), py::arg("pts"), py::arg("tris"));
  // ---------------------------------------------------------------------------
  // property: GetPtActivity
  // ---------------------------------------------------------------------------
  iGmTriSearch.def("GetPtActivity", [](xms::GmTriSearch &self) -> py::iterable {
    return xms::PyIterFromDynamicBitset(self.GetPtActivity());
  });
  // ---------------------------------------------------------------------------
  // property: SetPtActivity
  // ---------------------------------------------------------------------------
  iGmTriSearch.def("SetPtActivity", [](xms::GmTriSearch &self, py::iterable activity) {
        xms::DynBitset bit_act = xms::DynamicBitsetFromPyIter(activity);
        self.SetPtActivity(bit_act);
  });
  // ---------------------------------------------------------------------------
  // property: GetTriActivity
  // ---------------------------------------------------------------------------
  iGmTriSearch.def("GetTriActivity", [](xms::GmTriSearch &self) -> py::iterable {
    return xms::PyIterFromDynamicBitset(self.GetTriActivity());
  });
  // ---------------------------------------------------------------------------
  // property: SetTriActivity
  // ---------------------------------------------------------------------------
  iGmTriSearch.def("SetTriActivity", [](xms::GmTriSearch &self, py::iterable activity) {
        xms::DynBitset bit_act = xms::DynamicBitsetFromPyIter(activity);
        self.SetTriActivity(bit_act);
  });
  // ---------------------------------------------------------------------------
  // property: GetPoints
  // ---------------------------------------------------------------------------
  iGmTriSearch.def("GetPoints", [](xms::GmTriSearch &self) {
        return xms::PyIterFromVecPt3d(*self.GetPoints());
  });
  // ---------------------------------------------------------------------------
  // property: GetPoints
  // ---------------------------------------------------------------------------
  iGmTriSearch.def("GetTriangles", [](xms::GmTriSearch &self) {
        return xms::PyIterFromVecInt(*self.GetTriangles());
  });
  // ---------------------------------------------------------------------------
  // function: TriContainingPt
  // ---------------------------------------------------------------------------
  iGmTriSearch.def("TriContainingPt", [](xms::GmTriSearch &self, py::iterable pt) -> int {
    xms::Pt3d p = xms::Pt3dFromPyIter(pt);
    return self.TriContainingPt(p);
  }, py::arg("pt"));
  // ---------------------------------------------------------------------------
  // function: TriEnvelopsContainingPt
  // ---------------------------------------------------------------------------
  iGmTriSearch.def("TriEnvelopsContainingPt",
    [](xms::GmTriSearch &self, py::iterable pt) -> py::iterable {
    xms::Pt3d p = xms::Pt3dFromPyIter(pt);
    xms::VecInt tris;
    self.TriEnvelopsContainingPt(p, tris);
    return xms::PyIterFromVecInt(tris);
  }, py::arg("pt"));
  // ---------------------------------------------------------------------------
  // function: TriEnvelopesOverlap
  // ---------------------------------------------------------------------------
  iGmTriSearch.def("TriEnvelopesOverlap", [](xms::GmTriSearch &self, py::iterable pt_min,
                          py::iterable pt_max) -> py::iterable {
    xms::Pt3d p_min = xms::Pt3dFromPyIter(pt_min);
    xms::Pt3d p_max = xms::Pt3dFromPyIter(pt_max);
    xms::VecInt tris;
    self.TriEnvelopesOverlap(p_min, p_max, tris);
    return xms::PyIterFromVecInt(tris);
  }, py::arg("pt_min"), py::arg("pt_max"));
  // ---------------------------------------------------------------------------
  // function: InterpWeights
  // ---------------------------------------------------------------------------
  iGmTriSearch.def("InterpWeights", [](xms::GmTriSearch &self, py::iterable pt) -> py::iterable {
    xms::Pt3d p = xms::Pt3dFromPyIter(pt);
    xms::VecInt idxs;
    xms::VecDbl wts;
    bool result = self.InterpWeights(p, idxs, wts);
    return py::make_tuple(
      result,
      xms::PyIterFromVecInt(idxs),
      xms::PyIterFromVecDbl(wts)
    );
  }, py::arg("pt"));
  // ---------------------------------------------------------------------------
  // function: InterpWeightsTriangleIdx
  // ---------------------------------------------------------------------------
  iGmTriSearch.def("InterpWeightsTriangleIdx", [](xms::GmTriSearch &self, py::iterable pt) -> py::iterable {
    xms::Pt3d p = xms::Pt3dFromPyIter(pt);
    int tri_idx;
    xms::VecInt idxs;
    xms::VecDbl wts;
    bool result = self.InterpWeightsTriangleIdx(p, tri_idx, idxs, wts);
    return py::make_tuple(
      result,
      tri_idx,
      xms::PyIterFromVecInt(idxs),
      xms::PyIterFromVecDbl(wts)
    );
  }, py::arg("pt"));
}