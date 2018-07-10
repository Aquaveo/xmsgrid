#pragma once
//------------------------------------------------------------------------------
/// \file XmConvexHull
/// \ingroup ugrid
/// \copyright (C) Copyright Aquaveo 2018.
//------------------------------------------------------------------------------

#ifdef CXX_TEST

// 3. Standard Library Headers

// 4. External Library Headers
#include <cxxtest/TestSuite.h>

// 5. Shared Headers
#include <xmscore/misc/base_macros.h>
#include <xmscore/misc/boost_defines.h>
#include <xmscore/points/pt.h>

// 6. Non-shared Headers

/// XMS Namespace
namespace xms
{
class XmUGrid;
}

////////////////////////////////////////////////////////////////////////////////
/// Tests for ConvexHull functions.
class XmUGridConvexHullTests : public CxxTest::TestSuite
{
public:
  void TestConvexHull();
}; // XmUGridConvexHullTests

#endif
