#pragma once
#ifdef CXX_TEST
//------------------------------------------------------------------------------
/// \file
/// \ingroup geometry
/// \copyright (C) Copyright Aquaveo 2026. Distributed under FreeBSD License
/// (See accompanying file LICENSE or https://aquaveo.com/bsd/license.txt)
//------------------------------------------------------------------------------

// 3. Standard Library Headers

// 4. External Library Headers
#include <cxxtest/TestSuite.h>

// 5. Shared Headers

// 6. Non-shared Headers

//----- Namespace declaration --------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
class GmMultiPolyIntersectorCommonUnitTests : public CxxTest::TestSuite
{
public:
  void testRemoveDuplicateTValuesManyAtOne();
  void testRemoveDuplicateTValuesManyEndIds();
  void testXyTolGuardRestoresOnThrow();
}; // class GmMultiPolyIntersectorCommonUnitTests

#endif
