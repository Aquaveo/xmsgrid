//------------------------------------------------------------------------------
/// \file
/// \brief
/// \copyright (C) Copyright Aquaveo 2018. Distributed under FreeBSD License
/// (See accompanying file LICENSE or https://aqaveo.com/bsd/license.txt)
//------------------------------------------------------------------------------

//----- Included files ---------------------------------------------------------
#include <pybind11/pybind11.h>
#include <xmsgrid/python/geometry/geometry_py.h>

//----- Namespace declaration --------------------------------------------------
namespace py = pybind11;

//----- Python Interface -------------------------------------------------------

void initGeometry(py::module &geometry)
{
    // ---------------------------------------------------------------------------
	// function: gmPointInPolygon2D
	// ---------------------------------------------------------------------------
	geometry.def("gmPointInPolygon2D",
		[](py::iterable& a_polygon, py::iterable& a_point)-> int
	{
		BSHP<xms::VecPt3d> polygon = xms::VecPt3dFromPyIter(a_polygon);
		xms::Pt3d point = xms::Pt3dFromPyIter(a_point);
		return xms::gmPointInPolygon2D(*polygon, point);
	});
	// ---------------------------------------------------------------------------
	// function: gmPolygonArea
	// ---------------------------------------------------------------------------
	geometry.def("gmPolygonArea",
		[](py::iterable& a_polygon)-> double
	{
		BSHP<xms::VecPt3d> polygon = xms::VecPt3dFromPyIter(a_polygon);
		return xms::gmPolygonArea((*polygon).data(), (*polygon).size());
	});
	// ---------------------------------------------------------------------------
	// function: gmGetXyTol
	// ---------------------------------------------------------------------------
	geometry.def("gmGetXyTol",
		[]()-> double
	{
		return xms::gmXyTol();
	});
	// ---------------------------------------------------------------------------
	// function: gmSetXyTol
	// ---------------------------------------------------------------------------
	geometry.def("gmSetXyTol",
		[](double a_value)-> void
	{
		xms::gmXyTol(true, a_value);
	}, py::arg("a_value")=1e-9);
	// ---------------------------------------------------------------------------
	// function: gmOnLineWithTol
	// ---------------------------------------------------------------------------
	geometry.def("gmOnLineWithTol",
		[](const py::iterable& a_pt1, const py::iterable& a_pt2, const py::iterable& a_pt, const double a_tol)-> bool
	{
		xms::Pt3d pt1 = xms::Pt3dFromPyIter(a_pt1);
		xms::Pt3d pt2 = xms::Pt3dFromPyIter(a_pt2);
		xms::Pt3d pt = xms::Pt3dFromPyIter(a_pt);
		return xms::gmOnLineWithTol(pt1, pt2, pt.x, pt.y, a_tol);
	});
	// ---------------------------------------------------------------------------
	// function: gmInsideOrOnLineWithTol
	// ---------------------------------------------------------------------------
	geometry.def("gmInsideOrOnLineWithTol",
		[](const py::iterable& a_p1, const py::iterable& a_p2, const py::iterable& a_referencePoint,
		   const py::iterable& a_pt, double a_tol)-> py::tuple
	{
		xms::Pt3d p1 = xms::Pt3dFromPyIter(a_p1);
		xms::Pt3d p2 = xms::Pt3dFromPyIter(a_p2);
		xms::Pt3d referencePoint = xms::Pt3dFromPyIter(a_referencePoint);
		xms::Pt3d pt = xms::Pt3dFromPyIter(a_pt);
		double dist;
		bool result = xms::gmInsideOrOnLineWithTol(&p1, &p2, &referencePoint, pt.x, pt.y, a_tol, &dist);
		return py::make_tuple(result, dist);
	});
	// ---------------------------------------------------------------------------
	// function: gmFindClosestPtOnSegment
	// ---------------------------------------------------------------------------
	geometry.def("gmFindClosestPtOnSegment",
		[](const py::iterable& a_pt1, const py::iterable& a_pt2, const py::iterable& a_pt,
		   const double a_tol)-> py::tuple
	{
		xms::Pt3d p1 = xms::Pt3dFromPyIter(a_pt1);
		xms::Pt3d p2 = xms::Pt3dFromPyIter(a_pt2);
		xms::Pt3d pt = xms::Pt3dFromPyIter(a_pt);
		xms::Pt3d newPoint;
		double value = xms::gmFindClosestPtOnSegment(p1, p2, pt, newPoint, a_tol);
		return py::make_tuple(value, py::make_tuple(newPoint.x, newPoint.y, newPoint.z));
	});
	// ---------------------------------------------------------------------------
	// function: gmPtDistanceAlongSegment
	// ---------------------------------------------------------------------------
	geometry.def("gmPtDistanceAlongSegment",
		[](const py::iterable& a_pt1, const py::iterable& a_pt2, const py::iterable& a_pt, const double tol)-> double
	{
		xms::Pt3d p1 = xms::Pt3dFromPyIter(a_pt1);
		xms::Pt3d p2 = xms::Pt3dFromPyIter(a_pt2);
		xms::Pt3d pt = xms::Pt3dFromPyIter(a_pt);
		return xms::gmPtDistanceAlongSegment(p1, p2, pt, tol);
	});
	// ---------------------------------------------------------------------------
	// function: gmInsideOfLineWithTol
	// ---------------------------------------------------------------------------
	geometry.def("gmInsideOfLineWithTol",
		[](const py::iterable& a_pt1, const py::iterable& a_pt2, const py::iterable& a_referencePoint,
		   const py::iterable& a_pt, const double a_tol)-> bool
	{
		xms::Pt3d pt1 = xms::Pt3dFromPyIter(a_pt1);
		xms::Pt3d pt2 = xms::Pt3dFromPyIter(a_pt2);
		xms::Pt3d reference = xms::Pt3dFromPyIter(a_referencePoint);
		xms::Pt3d pt = xms::Pt3dFromPyIter(a_pt);
		return xms::gmInsideOfLineWithTol(pt1, pt2, reference, pt.x, pt.y, a_tol);
	});
	// ---------------------------------------------------------------------------
	// function: gmLinesIntersect
	// ---------------------------------------------------------------------------
	geometry.def("gmLinesIntersect",
		[](const py::iterable& a_line1pt1, const py::iterable& a_line1pt2, const py::iterable& a_line2pt1,
		   const py::iterable& a_line2pt2)-> bool
	{
		xms::Pt3d line1pt1 = xms::Pt3dFromPyIter(a_line1pt1);
		xms::Pt3d line1pt2 = xms::Pt3dFromPyIter(a_line1pt2);
		xms::Pt3d line2pt1 = xms::Pt3dFromPyIter(a_line2pt1);
		xms::Pt3d line2pt2 = xms::Pt3dFromPyIter(a_line2pt2);
		return xms::gmLinesIntersect(line1pt1, line1pt2, line2pt1, line2pt2);
	});
	// ---------------------------------------------------------------------------
	// function: gmEqualPointsXY
	// ---------------------------------------------------------------------------
	geometry.def("gmEqualPointsXY",
		[](const py::iterable& a_pt1, const py::iterable& a_pt2, double tol)-> bool
	{
		xms::Pt3d p1 = xms::Pt3dFromPyIter(a_pt1);
		xms::Pt3d p2 = xms::Pt3dFromPyIter(a_pt2);
		return xms::gmEqualPointsXY(p1.x, p1.y, p2.x, p2.y, tol);
	});
	// ---------------------------------------------------------------------------
	// function: gmOnLineAndBetweenEndpointsWithTol
	// ---------------------------------------------------------------------------
	geometry.def("gmOnLineAndBetweenEndpointsWithTol",
		[](const py::iterable& a_pt1, const py::iterable& a_pt2, const py::iterable& a_pt, double a_tol)-> bool
	{
		xms::Pt3d pt1 = xms::Pt3dFromPyIter(a_pt1);
		xms::Pt3d pt2 = xms::Pt3dFromPyIter(a_pt2);
		xms::Pt3d pt = xms::Pt3dFromPyIter(a_pt);
		return xms::gmOnLineAndBetweenEndpointsWithTol(pt1, pt2, pt.x, pt.y, a_tol);
	});
	// ---------------------------------------------------------------------------
	// function: gm2DDistanceToLineSegmentWithTol
	// ---------------------------------------------------------------------------
	geometry.def("gm2DDistanceToLineSegmentWithTol",
		[](const py::iterable& a_pt1, const py::iterable& a_pt2, const py::iterable& a_pt, double a_tol)-> double
	{
		xms::Pt3d pt1 = xms::Pt3dFromPyIter(a_pt1);
		xms::Pt3d pt2 = xms::Pt3dFromPyIter(a_pt2);
		xms::Pt3d pt = xms::Pt3dFromPyIter(a_pt);
		return xms::gm2DDistanceToLineSegmentWithTol(&pt1, &pt2, pt.x, pt.y, a_tol);
	});
	// ---------------------------------------------------------------------------
	// function: gmCross2D
	// ---------------------------------------------------------------------------
	geometry.def("gmCross2D",
		[](const py::iterable& a_origin, const py::iterable& a_a, const py::iterable& a_b)-> double
	{
		xms::Pt3d origin = xms::Pt3dFromPyIter(a_origin);
		xms::Pt3d a = xms::Pt3dFromPyIter(a_a);
		xms::Pt3d b = xms::Pt3dFromPyIter(a_b);
		return xms::gmCross2D(origin, a, b);
	});
	// ---------------------------------------------------------------------------
	// function: gmXyDistance
	// ---------------------------------------------------------------------------
	geometry.def("gmXyDistance",
		[](const py::iterable& a_pt1, const py::iterable& a_pt2)
	{
		xms::Pt3d pt1 = xms::Pt3dFromPyIter(a_pt1);
		xms::Pt3d pt2 = xms::Pt3dFromPyIter(a_pt2);
		return xms::gmXyDistance(pt1, pt2);
	});
	// ---------------------------------------------------------------------------
	// function: gmComputePolygonCentroid
	// ---------------------------------------------------------------------------
	geometry.def("gmComputePolygonCentroid",
		[](const py::iterable& a_polygon)-> py::tuple
	{
		BSHP<xms::VecPt3d> polygon = xms::VecPt3dFromPyIter(a_polygon);
		xms::Pt3d result = xms::gmComputePolygonCentroid(*polygon);
		return xms::PyIterFromPt3d(result);
	});
	// ---------------------------------------------------------------------------
	// function: gm2DDistanceToLineWithTol
	// ---------------------------------------------------------------------------
	geometry.def("gm2DDistanceToLineWithTol",
		[](const py::iterable& a_pt1, const py::iterable& a_pt2, const py::iterable& a_pt3, double a_tol)-> double
	{
		xms::Pt3d pt1 = xms::Pt3dFromPyIter(a_pt1);
		xms::Pt3d pt2 = xms::Pt3dFromPyIter(a_pt2);
		xms::Pt3d pt3 = xms::Pt3dFromPyIter(a_pt3);
		return xms::gm2DDistanceToLineWithTol(&pt1, &pt2, pt3.x, pt3.y, a_tol);
	});
	// ---------------------------------------------------------------------------
	// function: gmAngleBetweenEdges
	// ---------------------------------------------------------------------------
	geometry.def("gmAngleBetweenEdges",
		[](const py::iterable& a_endpoint1, const py::iterable& a_commonPoint, const py::iterable& a_endpoint2)-> double
	{
		xms::Pt3d endpoint1 = xms::Pt3dFromPyIter(a_endpoint1);
		xms::Pt3d commonPoint = xms::Pt3dFromPyIter(a_commonPoint);
		xms::Pt3d endpoint2 = xms::Pt3dFromPyIter(a_endpoint2);
		return xms::gmAngleBetweenEdges(endpoint1, commonPoint, endpoint2);
	});
    initGmTriSearch(geometry);
}