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
  void testGetCell3dFaceOrientationWedgeIncreasingUp();
  void testGetCellNumberingOneCell();
  void testCalculateCellNumberingIncreasingDown();
  void testCalculateCellNumberingIncreasingUp();
  void testCalculateCellNumberingMixed();
  void testCell3dFunctionCaching();
  void testLargeUGridLinkSpeed();
  void testUgridWithInvalidCells();
}; // XmUGridUnitTests

////////////////////////////////////////////////////////////////////////////////
class CellStreamValidationUnitTests : public CxxTest::TestSuite
{
public:
  void testTrailingEmptyCell();

  // Test that good cells are accepted
  void testGoodUnknownCell();
  void testGoodEmptyCell();
  void testGoodVertex();
  void testGoodLine();
  void testGoodTriangle();
  void testGoodPixel();
  void testGoodQuad();
  void testGoodTetra();
  void testGoodPyramid();
  void testGoodWedge();
  void testGoodPentagonalPrism();
  void testGoodHexagonalPrism();
  void testGoodVoxel();
  void testGoodHexahedron();
  void testGoodPolyVertex();
  void testGoodPolyLine();
  void testGoodTriangleStrip();
  void testGoodPolygon();
  void testGoodGrid();

  // Test cell types with no number of points after.
  void testUnknownCellNoNumberOfPoints();
  void testEmptyCellNoNumberOfPoints();
  void testVertexNoNumberOfPoints();
  void testLineNoNumberOfPoints();
  void testTriangleNoNumberOfPoints();
  void testPixelNoNumberOfPoints();
  void testQuadNoNumberOfPoints();
  void testTetraNoNumberOfPoints();
  void testPyramidNoNumberOfPoints();
  void testWedgeNoNumberOfPoints();
  void testPentagonalPrismNoNumberOfPoints();
  void testHexagonalPrismNoNumberOfPoints();
  void testVoxelNoNumberOfPoints();
  void testHexahedronNoNumberOfPoints();
  void testPolyVertexNoNumberOfPoints();
  void testPolyLineNoNumberOfPoints();
  void testTriangleStripNoNumberOfPoints();
  void testPolygonNoNumberOfPoints();
  void testGridNoNumberOfPoints();

  // Test cell types followed by wrong number of points.
  // These test for redundancy, which unknown cells lack, so no unknown cell test.
  void testEmptyCellWrongNumberOfPoints();
  void testVertexWrongNumberOfPoints();
  void testLineWrongNumberOfPoints();
  void testTriangleWrongNumberOfPoints();
  void testPixelWrongNumberOfPoints();
  void testQuadWrongNumberOfPoints();
  void testTetraWrongNumberOfPoints();
  void testPyramidWrongNumberOfPoints();
  void testWedgeWrongNumberOfPoints();
  void testPentagonalPrismWrongNumberOfPoints();
  void testHexagonalPrismWrongNumberOfPoints();
  void testVoxelWrongNumberOfPoints();
  void testHexahedronWrongNumberOfPoints();
  void testPolyVertexWrongNumberOfPoints();
  void testPolyLineWrongNumberOfPoints();
  void testTriangleStripWrongNumberOfPoints();
  void testPolygonWrongNumberOfPoints();
  void testGridWrongNumberOfPoints();

  // Test that there must be enough points
  void testUnknownCellMissingPoints();
  void testVertexMissingPoints();
  void testLineMissingPoints();
  void testTriangleMissingPoints();
  void testPixelMissingPoints();
  void testQuadMissingPoints();
  void testTetraMissingPoints();
  void testPyramidMissingPoints();
  void testWedgeMissingPoints();
  void testPentagonalPrismMissingPoints();
  void testHexagonalPrismMissingPoints();
  void testVoxelMissingPoints();
  void testHexahedronMissingPoints();
  void testPolyVertexMissingPoints();
  void testPolyLineMissingPoints();
  void testTriangleStripMissingPoints();
  void testPolygonMissingPoints();
  void testGridMissingPoints();

  // Test that points must be valid
  void testUnknownCellBadPoints();
  void testVertexBadPoints();
  void testLineBadPoints();
  void testTriangleBadPoints();
  void testPixelBadPoints();
  void testQuadBadPoints();
  void testTetraBadPoints();
  void testPyramidBadPoints();
  void testWedgeBadPoints();
  void testPentagonalPrismBadPoints();
  void testHexagonalPrismBadPoints();
  void testVoxelBadPoints();
  void testHexahedronBadPoints();
  void testPolyVertexBadPoints();
  void testPolyLineBadPoints();
  void testTriangleStripBadPoints();
  void testPolygonBadPoints();
  void testGridBadPoints();

  // Polyhedron tests
  void testGoodPolyhedron();
  void testPolyhedronWrongNumberOfFaces();
  void testPolyhedronWrongNumberOfPoints();
  void testPolyhedronMissingFaces();
  void testPolyhedronMissingPoints();
  void testPolyhedronBadPoints();
};

#endif
