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
#include <xmscore/misc/base_macros.h>
#include <xmscore/misc/boost_defines.h>
#include <xmscore/points/pt.h>

// 6. Non-shared Headers

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
  void testGetCellPointIndexes();
  void testGetCellEdgePointIndexes();
  void testGetCommonCells();
  void testGetCellNeighbors();
  void testGetAdjacentCell();
  void testGetAdjacentCellsFromGivenEdge();
  void testGetCellFace();
  void testGetCellFaceNeighbor();
  void testGetEdgesFromPoint();
  void testGetFacesFromPoint();
  void testLargeUGridLinkSpeed();
}; // XmUGridUnitTests

BSHP<xms::XmUGrid> TEST_XmUGrid1Left90Tri();
BSHP<xms::XmUGrid> TEST_XmUGridSimpleQuad();
BSHP<xms::XmUGrid> TEST_XmUGrid2dLinear();
BSHP<xms::XmUGrid> TEST_XmUGrid3dLinear();
BSHP<xms::XmUGrid> TEST_XmUGridHexagonalPolyhedron();
BSHP<xms::XmUGrid> TEST_XmUBuildQuadUGrid(const int a_rows, const int a_cols);
BSHP<xms::XmUGrid> TEST_XmUBuildQuadUGrid(const int a_rows,
                                          const int a_cols,
                                          const xms::Pt3d& a_origin);
BSHP<xms::XmUGrid> TEST_XmUBuildHexadronUgrid(const int a_rows, const int a_cols, const int a_lays);
BSHP<xms::XmUGrid> TEST_XmUBuildHexadronUgrid(const int a_rows,
                                              const int a_cols,
                                              const int a_lays,
                                              const xms::Pt3d& a_origin);
BSHP<xms::XmUGrid> TEST_XmUBuildPolyhedronUgrid(const int a_rows,
                                                const int a_cols,
                                                const int a_lays);
BSHP<xms::XmUGrid> TEST_XmUBuildPolyhedronUgrid(const int a_rows,
                                                const int a_cols,
                                                const int a_lays,
                                                const xms::Pt3d& a_origin);
std::string TestFilesPath();

#endif
