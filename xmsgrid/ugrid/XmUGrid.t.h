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
  void testGetSingleCellStream();
  void testGetCellType();
  void testGetCellDimension();
  void testGetExtents();
  void testGetNumberOfCellEdges();
  void testGetNumberOfCellFaces();
  void testGetPointCellsSimple();
  void testGetPointCells();
  void testGetPointsOfCell();
  void testGetCellEdgeFromEdgeIndex();
  void testGetCommonCells();
  void testGetCellNeighbors();
  void testGetAdjacentCell();
  void testGetAdjacentCellsFromGivenEdge();
  void testGetCellFace();
  void testGetCellFaceNeighbor();
  void testGetEdgesFromPoint();
  void testGetFacesFromPoint();
  void testGetPlanViewPolygon();
  void testIsCellValidWithPointChange();
  void testPointFunctions();
  void testCellFunctions();
  void testGetCellStreamFunctions();
  void testGetAdjacentCellFunctions();
  void testGetEdgesOfCell();
  void testGetFaces();
  void testLargeUGridLinkSpeed();
}; // XmUGridUnitTests

std::string TestFilesPath();

#endif
