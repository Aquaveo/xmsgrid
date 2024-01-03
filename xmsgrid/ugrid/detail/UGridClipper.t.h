#pragma once
//------------------------------------------------------------------------------
/// \file
/// \ingroup ugrid
/// \copyright (C) Copyright Aquaveo 2022. Distributed under FreeBSD License
/// (See accompanying file LICENSE or https://aquaveo.com/bsd/license.txt)
//------------------------------------------------------------------------------

#ifdef CXX_TEST

// 3. Standard Library Headers

// 4. External Library Headers
#include <cxxtest/TestSuite.h>

// 5. Shared Headers

// 6. Non-shared Headers

////////////////////////////////////////////////////////////////////////////////
/// Tests for UGridClipper functions.
class UGridClipperTests : public CxxTest::TestSuite
{
public:
  // iGetLeftRightCells
  void testGetLeftRightCells();
  void testGetLeftRightCellsReversed();
  void testGetLeftRightCellsNoLeft();
  void testGetLeftRightCellsNoRight();

  // iMarkCellsOnLoop
  void testMarkCellsOnLoopBoundary();
  void testMarkCellsOnLoopHole();
  void testMarkCellsOnLoopBoundaryAndHole();

  // iMarkCellsOnLoops
  void testMarkCellsOnLoops();

  // iMarkNeighborsOfCell
  void testMarkBoundaryCellNoVisitedNeighbors();
  void testMarkBoundaryCellOneVisitedNeighbor();
  void testMarkBoundaryCellAllVisitedNeighbors();
  void testMarkInteriorCellNoVisitedNeighbors();
  void testMarkInteriorCellOneVisitedNeighbor();
  void testMarkInteriorCellAllVisitedNeighbors();

  // iMarkNeighborsOfCells
  void testMarkOuterBoundaryAsOutside();
  void testMarkOuterBoundaryAsInside();
  void testMarkInnerBoundaryAsOutside();
  void testMarkInnerBoundaryAsInside();
  void testMarkMultipleBoundaries();

  // XmClipUGrid
  void testClipUgrid();
}; // UGridClipperTests

#endif
