//------------------------------------------------------------------------------
/// \file
/// \copyright (C) Copyright Aquaveo 2018. Distributed under FreeBSD License
/// (See accompanying file LICENSE or https://aquaveo.com/bsd/license.txt)
//------------------------------------------------------------------------------
#pragma once

#ifdef CXX_TEST

// 3. Standard Library Headers

// 4. External Library Headers
#include <cxxtest/TestSuite.h>

// 5. Shared Headers

// 6. Non-shared Headers

//----- Namespace declaration --------------------------------------------------

// namespace xms {

////////////////////////////////////////////////////////////////////////////////
class GmExtents3dUnitTests : public CxxTest::TestSuite
{
public:
  void testSinglePt();
  void testMultiplePts();
  void testNoPts();
  void testOverlapping();
}; // class GmExtents3dUnitTests

//} // namespace xms

#endif
