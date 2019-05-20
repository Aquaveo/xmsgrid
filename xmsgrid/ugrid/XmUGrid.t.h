#pragma once
//------------------------------------------------------------------------------
/// \file XmUGrid.t.h
/// \ingroup ugrid
/// \copyright (C) Copyright Aquaveo 2018. Distributed under FreeBSD License
/// (See accompanying file LICENSE or https://aqaveo.com/bsd/license.txt)
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
  void testOperators();
  void testUGridStreams();
  void testGetSetPoint();
  void testGetCellCellstream();
  void testGetCellType();
  void testGetCellDimension();
  void testGetExtents();
  void testGetCellEdgeCount();
  void testGetCell3dFaceCount();
  void testGetCell3dFacePointCount();
  void testGetPointAdjacentCellsSimple();
  void testGetPointAdjacentCells();
  void testGetCellPoints();
  void testGetCellEdge();
  void testGetPointsAdjacentCells();
  void testGetCellAdjacentCells();
  void testGetCellEdgeAdjacentCells();
  void testEdgeAdjacentCells();
  void testGetCell3dFacePoints();
  void testGetCell3dFaceAdjacentCell();
  void testGetPointAdjacentPoints();
  void testGetCellPlanViewPolygon();
  void testGetCellPlanViewPolygonMultiSideFace();
  void testIsCellValidWithPointChange();
  void testPointFunctions();
  void testCellFunctions();
  void testCellstreamFunctions();
  void testCellEdgeAdjacentCellFunctions();
  void testCellEdges();
  void testCell3dFaceFunctions();
  void testGetCell3dFaceOrientationHexahedrons();
  void testGetCell3dFaceOrientationConcaveCell();
  void testCell3dFunctionCaching();
  void testLargeUGridLinkSpeed();
}; // XmUGridUnitTests

#endif
