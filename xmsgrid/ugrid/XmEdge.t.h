#pragma once
//------------------------------------------------------------------------------
/// \file
/// \ingroup ugrid
/// \copyright (C) Copyright Aquaveo 2018. Distributed under FreeBSD License
/// (See accompanying file LICENSE or https://aquaveo.com/bsd/license.txt)
//------------------------------------------------------------------------------

#ifdef CXX_TEST

// 3. Standard Library Headers

// 4. External Library Headers
#include <cxxtest/TestSuite.h>

// 5. Shared Headers

// 6. Non-shared Headers

/// XMS Namespace
namespace xms
{
class XmUGrid;
}

////////////////////////////////////////////////////////////////////////////////
class XmEdgeUnitTests : public CxxTest::TestSuite
{
public:
  void testLessThanOperator();
  void testEqualsOperator();
  void testIsEquivalent();
}; // XmEdgeUnitTests

#endif
