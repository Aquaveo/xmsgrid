#pragma once
#ifdef CXX_TEST
//------------------------------------------------------------------------------
/// \file
/// \ingroup triangulate_detail
/// \copyright (C) Copyright Aquaveo 2018. Distributed under FreeBSD License
/// (See accompanying file LICENSE or https://aquaveo.com/bsd/license.txt)
//------------------------------------------------------------------------------

// 3. Standard Library Headers

// 4. External Library Headers
#include <cxxtest/TestSuite.h>

// 5. Shared Headers

// 6. Non-shared Headers

//----- Namespace declaration --------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
class TrAutoFixFourTrianglePtsUnitTests : public CxxTest::TestSuite
{
public:
  void test1();
  void test_bug15186();
  void test_bug15186a();
  void test_bug15178();
}; // class TrAutoFixFourTrianglePtsUnitTests

#endif
