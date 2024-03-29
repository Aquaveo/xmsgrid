#pragma once
#ifdef CXX_TEST
//------------------------------------------------------------------------------
/// \file
/// \ingroup triangulate
/// \copyright (C) Copyright Aquaveo 2018. Distributed under FreeBSD License
/// (See accompanying file LICENSE or https://aquaveo.com/bsd/license.txt)
//------------------------------------------------------------------------------

//----- Included files ---------------------------------------------------------
// 3. Standard Library Headers

// 4. External Library Headers
#include <cxxtest/TestSuite.h>

// 5. Shared Headers

// 6. Non-shared Headers

//----- Forward declarations ---------------------------------------------------

//----- Namespace declaration --------------------------------------------------
// namespace xms {

//----- Constants / Enumerations -----------------------------------------------

//----- Structs / Classes ------------------------------------------------------
class TrBreaklineAdderUnitTests : public CxxTest::TestSuite
{
public:
  void test1();
  void test2();
  void testCrossingBoundary();
  void testVerySkinnyTris();
  void testForceBreaklineBug13951();
  void testForceBreaklineBug14095();
};
//----- Function prototypes ----------------------------------------------------

//} // namespace xms
#endif
