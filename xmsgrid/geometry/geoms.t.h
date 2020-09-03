#pragma once
#ifdef CXX_TEST
//------------------------------------------------------------------------------
/// \file
/// \ingroup geometry
/// \copyright (C) Copyright Aquaveo 2018. Distributed under FreeBSD License
/// (See accompanying file LICENSE or https://aqaveo.com/bsd/license.txt)
//------------------------------------------------------------------------------

// 3. Standard Library Headers

// 4. External Library Headers
#include <cxxtest/TestSuite.h>
#pragma warning(push)
#pragma warning(disable : 4103)  // boost code: alignment change
#include <boost/timer/timer.hpp> // boost::timer::cpu_timer
#pragma warning(pop)

// 5. Shared Headers
#include <xmscore/points/ptsfwd.h>
#include <xmscore/misc/base_macros.h>

// 6. Non-shared Headers

//----- Namespace declaration --------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
class GeomsXmsngUnitTests : public CxxTest::TestSuite
{
public:
  void test_gmComputePolygonCentroid();
  void test_gmComputeCentroid();

  void test_gmPointInPolygon2D_Speed();
  void testConvexHull();
  void testDoLineSegmentsCross();
}; // class GeomsXmsngUnitTests

////////////////////////////////////////////////////////////////////////////////
class GmPointInPolyUnitTests
{
public:
  GmPointInPolyUnitTests();
  void DoTest();

protected:
  // You must override these
  /// Determine if a point is in or out.
  /// \param a_pt: The point to check.
  virtual void CheckPoint(const xms::Pt3d& a_pt) = 0;
  /// Maximum time for test to take.
  /// \return The max time
  virtual double MaxTime() = 0;

  // You don't have to override these
  virtual void Setup();
  virtual void CheckPoints();
  virtual void GetResults();

protected:
  std::vector<xms::Pt3d> m_outPoly; ///< Output polygon
  std::vector<xms::Pt3d> m_inPoly;  ///< Input polygon
  boost::timer::cpu_timer m_timer;  ///< Timer
  int m_count;                      ///< Number of points checked
  int m_status;                     ///< Status (in, out, on) of at least one pt

private:
  XM_DISALLOW_COPY_AND_ASSIGN(GmPointInPolyUnitTests); ///< Hide compiler generated copy and assign
};                                                     // GmPointInPolyUnitTests

////////////////////////////////////////////////////////////////////////////////
class GeomsXmsngIntermediateTests : public CxxTest::TestSuite
{
public:
  void test_gmPointInPolygon2D();
};

////////////////////////////////////////////////////////////////////////////////
class GeomsUnitTest : public CxxTest::TestSuite
{
public:
  void test_gmCounterClockwise();
  void test_gmQuadToTriAreaCheck();
  void test_gmConvertAngleBetweenXAndNorth();
  void test_gmAddToExtents();
  void test_gmExtents2D();
  void test_gmExtents3D();
  void test_gmEqualPoints();
  void test_gmPolygonArea();
  void test_gmPointInPolygon3DWithTol();
  void test_gmIntersectLineSegmentsWithTol();
  void test_gmIntersectLineSegmentsWithTol2();
  void test_gmMakePolygonClockwise();
  void test_gmCounterClockwiseQuad();
  void test_gmAngleBetween2DVectors();
  void test_gmAngleBetweenEdges();
  void test_gmBaryPrepare();
  void test_gmIntersectLines();
  void test_gmMiddleThirdWithTol();
  void testGreatCircleDistanceMeters();
}; // class GeomsUnitTest

#endif
