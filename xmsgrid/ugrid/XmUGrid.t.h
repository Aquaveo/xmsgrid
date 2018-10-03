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
class XmUGridUnitTests : public CxxTest::TestSuite
{
public:
  void testUGridStreams();
  void testGetSetPoint();
  void testCellCellstream();
  void testCellType();
  void testCellDimension();
  void testExtents();
  void testCellEdgeCount();
  void testCell3dFaceCount();
  void testCell3dFacePointCount();
  void testPointAdjacentCellsSimple();
  void testPointAdjacentCells();
  void testCellPoints();
  void testCellEdge();
  void testPointsAdjacentCells();
  void testCellAdjacentCells();
  void testCellEdgeAdjacentCells();
  void testEdgeAdjacentCells();
  void testCell3dFacePoints();
  void testCell3dFaceAdjacentCell();
  void testPointAdjacentPoints();
  void testCellPlanViewPolygon();
  void testCellPlanViewPolygonMultiSideFace();
  void testIsCellValidWithPointChange();
  void testPointFunctions();
  void testCellFunctions();
  void testCellstreamFunctions();
  void testCellEdgeAdjacentCellFunctions();
  void testCellEdges();
  void testCell3dFaceFunctions();
  void testLargeUGridLinkSpeed();
}; // XmUGridUnitTests

std::string TestFilesPath();

#endif
