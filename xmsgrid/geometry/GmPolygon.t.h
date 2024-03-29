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
#include <xmscore/stl/vector.h>
#include <cxxtest/TestSuite.h>

// 5. Shared Headers

// 6. Non-shared Headers

//----- Namespace declaration --------------------------------------------------

//----- Forward declarations ---------------------------------------------------

//----- Structs / Classes ------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
/// \brief Tests GmPolygon
class GmPolygonUnitTests : public CxxTest::TestSuite
{
public:
  void testNoHoles();
  void testWithHoles();
  void testMinDistanceToBoundary();
  void testIntersection();
  void testUnion();

  static void SetUpPolyWithHoles1(xms::VecPt3d& a_outPoly,
                                  xms::VecPt3d2d& a_inPolys,
                                  xms::VecPt3d& a_ptsToTest);
  static void SetUpPolyWithHole(xms::VecPt3d& a_outPoly, xms::VecPt3d& a_inPolys);
}; // GmPolygonUnitTests

////////////////////////////////////////////////////////////////////////////////
/// \brief Tests GmPolygonIntermediateTests
class GmPolygonIntermediateTests : public CxxTest::TestSuite
{
public:
  void testSpeed();
}; // GmPolygonIntermediateTests
#endif
