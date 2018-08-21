#pragma once
//------------------------------------------------------------------------------
/// \file XmUGrid.t.h
/// \ingroup ugrid
/// \copyright (C) Copyright Aquaveo 2018.
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
