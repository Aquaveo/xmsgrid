#pragma once
//------------------------------------------------------------------------------
/// \file
/// \ingroup ugrid
/// \copyright (C) Copyright Aquaveo 2018.
//------------------------------------------------------------------------------

#ifdef CXX_TEST

// 3. Standard Library Headers

// 4. External Library Headers
#include <cxxtest/TestSuite.h>

// 5. Shared Headers

// 6. Non-shared Headers

////////////////////////////////////////////////////////////////////////////////
/// Tests for XmUGrid utility functions.
class XmUGridUtilsTests : public CxxTest::TestSuite
{
public:
  void testDoLineSegmentsCross();

  void testWriteEmptyUGrid();
  void testWriteBasicUGrid();
  void testWritePolyhedronUGrid();
  void testWriteLinear2dCells();
  void testWriteLinear3dCells();

  void testReadEmptyUGridAsciiFile();
  void testReadBasicUGrid();
  void testReadPolyhedronUGrid();

  void testLinear2dWriteThenRead();
  void testLinear3dWriteThenRead();

  void testWriteThenReadUGridFile();
}; // XmUGridReaderTests

#endif
