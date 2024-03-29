#pragma once
//------------------------------------------------------------------------------
/// \file XmUGridUtils.t.h
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

////////////////////////////////////////////////////////////////////////////////
/// Tests for XmUGrid utility functions.
class XmUGridUtilsTests : public CxxTest::TestSuite
{
public:
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
  void testCellOrderWriteThenRead();
  void testWriteThenReadUGridFile();
  void testWriteThenReadUGridFileToAscii();
  void testReadVersion1Dot0File();
  void testWriteThenReadUGridBinary();
  void testCellStringToEnum();
  void testLargeUGridBinarySpeed();
  void testReadReadyAtNextLine();
  void testReadTrailingEmptyCellNoNumber();
  void testReadTrailingEmptyCell();

  void testRemovePoint();
  void testRemovePoints();
  void testRemoveCell();
  void testRemoveCells();
  void testRemovePointsAndCells();
}; // XmUGridReaderTests

#endif
