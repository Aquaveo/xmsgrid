#pragma once
#ifdef CXX_TEST
//------------------------------------------------------------------------------
/// \file
/// \ingroup geometry
/// \copyright (C) Copyright Aquaveo 2018. Distributed under FreeBSD License
/// (See accompanying file LICENSE or https://aquaveo.com/bsd/license.txt)
//------------------------------------------------------------------------------

//----- Included files ---------------------------------------------------------
// 3. Standard Library Headers

// 4. External Library Headers
#include <cxxtest/TestSuite.h>

// 5. Shared Headers

// 6. Non-shared Headers

//----- Namespace declaration --------------------------------------------------

// namespace xms {

//----- Forward declarations ---------------------------------------------------

//----- Structs / Classes ------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
class GmMultiPolyIntersectorUnitTests : public CxxTest::TestSuite
{
public:
  // 1 poly
  void test1OutOut();
  void test1OutIn();
  void test1InOut();
  void test1InIn();
  void test1OnOn();
  void test1OnIn();
  void test1InOn();
  void test1OutOn();
  void test1OnOut();
  void test1EdgeInIn();
  void test1EdgePtPt();
  void test1EdgeOutOut();
  void test1EdgeOutIn();
  void test1EdgeInOut();
  void test1OutPt();
  void test1OutPtOut();
  void test1AllOut();
  void test1PtIn();
  void test1InPt();

  // 2 polys
  void test2OnOn();
  void test2InOn();
  void test2OnIn();
  void test2OutOut();
  void test2OutIn();
  void test2InOut();
  void test2InIn();
  void test2InPt();
  void test2PtIn();
  void test2InEdgePt();
  void testCorners();
  void testQuadCorners();
  void testQuadCornersBug12396();
  void test2InOutIn();

  // Multiple polys
  void testInsideToInside();
  void testOutsideToOutside();
  void testTouchesVertex();
  void testTouchesEdge();
  void testAlongEdgesInsideToInside();
  void testAlongEdgesOutsideToOutside();
  void testEdgeThroughOppositeVertexAtAngle();
  void testStartAtEdgeThroughAdjacent();
  void testInsideToEdgeThenThroughAdjacent();
  void testEndAtEdgeFromAdjacent();
  void testSmsCase1();
  void testMap2MfBug();
}; // GmMultiPolyIntersectorUnitTests

////////////////////////////////////////////////////////////////////////////////
class GmMultiPolyIntersector2IntermediateTests : public CxxTest::TestSuite
{
public:
  void testLargeNumPolys();
  void testLargeNumPolysAndSegments();
  void testBug12586();
  void testBug12728();
  void testBug13273();
  void testPointOnPolygonVertex();
  void testPointsNearEdgePoints();
};

//} // namespace xms
#endif
