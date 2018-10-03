# 2D UGrid Tutorial

\tableofcontents
# 2D UGrid Tutorial {#TwoD_Tutorial}

## Introduction {#Intro_2Ugrid}
The purpose of this tutorial is to provide explanation on how to use xmsgrid to create two dimensional unstructured grids, or UGrids. A UGrid has points and cells defined using those points. There are many different kinds of cells available, but this tutorial will focus on the 2-dimensional cells, namely: triangle, polygon, pixel, quadrilateral.

## Example - Defining Ugrid Cells {#Example_DefiningA2dUGridCell}
Supported 2D grid cells include: triangle (5), polygon (7), pixel (8), quad (9). A cell is defined with the number declaration of the shape (5, 7, 8, and 9 respectively as defined by the enumeration xms::XmUGridCellType), then the number of points, followed by the point indices. The cell definitions mirror VTK cell definitions which are available on page 9 of VTK File Formats for VTK version 4.2 at https://www.vtk.org/wp-content/uploads/2015/04/file-formats.pdf.

A triangle (5) has 3 points and the points are declared in a counter-clockwise direction. A cellstream example for a triangle is: 5, 3, 0, 1, 2.

A polygon (7) does not a have a defined number of points, but the points are still declared in a counter-clockwise direction. A cellstream example for a polygon is: 7, 5, 0, 1, 2, 3, 4.

A pixel (8) has 4 orthogonially defined points. For the direction and order of points, see the illustration in the VTK file Format pdf referenced above on page 9 for a VTK_PIXEL. A cellstream example for a pixel is: 8, 4, 0, 1, 2, 3.

A quad (9) has 4 points declared in a counter-clockwise direction. A cellstream example for a quad is: 9, 4, 0, 1, 2, 3.

The testing code for this example is xms::TEST_XmUGrid2dLinear.
\snippet xmsgrid/ugrid/XmUGrid.cpp snip_test_2DShapes

## Example - Creating a New 2D UGrid With Data {#Example_New_With_Data_2d}
This example shows how to create a new 2D UGrid with the overloaded New function which directly sets the data as it constructs the grid, using the static function xms::XmUGrid::New(const VecPt3d& a_points, const VecInt& a_cellStream). Functionality is shared between 2d and 3d UGrids. The testing code for this example is XmUGridUnitTests::testGetSetPoint.

\snippet xmsgrid/ugrid/XmUGrid.cpp snip_test_NewOperator

## Example - Creating a New 2D UGrid {#Example_New2d}
This example shows how to create a new 2D UGrid. XmUGrid is an abstract class that cannot be instantiated. The static function xms::XmUGrid::New() is the only method to obtain a Boost Shared Pointer to an instance of XmUGrid. Points and Cellstream may be passed to New to initialize the UGrid with data but this is not required. Functionality is shared between 2d and 3d UGrids. The testing code for this example is XmUGridUnitTests::testUGridStreams.

## Example - Setting the UGrid Points {#Example_SetPoints2d}
This example shows how to set all of the UGrid points using xms::XmUGrid::SetLocations. The Ugrid points cannot be added or removed individually, though they can be edited individually. The SetPoints function takes one argument, a vector of 3D points. It is recomended that each point is unique to avoid unexpected behavior. Functionality is shared between 2d and 3d UGrids. The testing code for this example is the same as used for creating a new UGrid, XmUGridUnitTests::testUGridStreams.

## Example - Setting the UGrid Cell Stream {#Example_SetCellstream2d}
This example shows how to set the entire UGrid Cellstream using xms::XmUGrid::SetCellstream. Cellstreams are formatted as a stream of integers starting with the cell type as described by the enumeration XmUGridCellType, then the number of points in the cell, followed by a series of indices to points. The SetCellstream function takes one argument, a vector of integers formatted as previously described. Functionality is shared between 2d and 3d UGrids. The testing code for this example is the same as used for creating a new UGrid, XmUGridUnitTests::testUGridStreams.

\snippet xmsgrid/ugrid/XmUGrid.cpp snip_test_UGrid_Streams

## Example - Validating the Cellstream {#Example_IsValidCellstream}
This example shows how to determine whether a given Cellstream is valid as previously defined. The xms::XmUGrid::IsValidCellstream checks whether all cell types and point counts within the cellstream match up, but does not check for orientation or valid point positions. This function should not be relied on to catch all errors, but can be a basic check before setting the cellstream. The function takes one argument, a cellstream containing one or more cells. Functionality is shared between 2d and 3d UGrids. The testing code for this example is XmUGridUnitTests::SetCellstream.

\snippet xmsgrid/ugrid/XmUGrid.cpp snip_test_SetCellstream

## Example - Get Number Of Points {#Example_PointCount}
This example shows how to return the number of points contained in a UGrid. The xms::XmUGrid::PointCount function returns the number of points in the UGrid. Functionality is shared between 2d and 3d UGrids. The testing code for this example is shared with other examples, XmUGridUnitTests::testPointFunctions.

## Example - Get Points (Locations) {#Example_Locations}
This example shows how to get all points contained within the XmUGrid. The xms::XmUGrid::Locations function returns a vector of Pt3d's. Functionality is shared between 2d and 3d UGrids. The testing code for this example is shared with other examples, XmUGridUnitTests::testPointFunctions.

## Example - Get Point Location {#Example_PointLocation}
This example shows how to get a specific point given a point index. The xms::XmUGrid::PointLocation function returns the Pt3d of the point at the specified index. Functionality is shared between 2d and 3d UGrids. The testing code for this example is shared with other examples, XmUGridUnitTests::testPointFunctions.

## Example - Set Point Location {#Example_SetLocation}
This example shows how to set a specific point location given a point index. The xms::XmUGrid::SetLocation function takes a point index and a Pt3d as arguments and returns whether the operation was succesful. The function will fail and return false if the change would cause any edges to cross. Functionality is shared between 2d and 3d UGrids. The testing code for this example is shared with other examples, XmUGridUnitTests::testPointFunctions.

## Example - Get Locations of Many Points {#Example_PointsLocations}
This example shows how to convert a vector of point indices into a vector of Pt3d's. The xms::XmUGrid::PointsLocations function takes a vector of Point Indices as an argument and returns a vector of corresponding Pt3d's as a result. Functionality is shared between 2d and 3d UGrids. The testing code for this example is shared with other examples, XmUGridUnitTests::testPointFunctions.

## Example - Get Extents of UGrid {#Example_Extents}
This example shows how to get the extents of a UGrid. The xms::XmUGrid::Extents function takes two 3D points as arguments describing the minimum and maximum extent that the points of the UGrid cover. These arguments will be set by the funtion. Functionality is shared between 2d and 3d UGrids. The testing code for this example is shared with other examples, XmUGridUnitTests::testPointFunctions.

## Example - Get Cells Adjacent to a Point {#Example_PointAdjacentCells}
This example shows how to the cells associated with a single point. The xms::XmUGrid::PointAdjacentCells function takes one point index as an argument and returns a vector of cell indices. Functionality is shared between 2d and 3d UGrids. The testing code for this example is shared with other examples, XmUGridUnitTests::testPointFunctions.

## Example - Get the Cells that Share All of Group of Points {#Example_PointsAdjacentCells}
This example shows how to get the cells that share all of the same points or points. The xms::XmUGrid::PointsAdjacentCells function takes a vector of point indices as an argument and returns a vector of cell indices. Functionality is shared between 2d and 3d UGrids. The testing code for this example is shared with other examples, XmUGridUnitTests::testPointFunctions.

\snippet xmsgrid/ugrid/XmUGrid.cpp snip_test_PointFunctions

## Example - Get the Points (or their Locations) Adjacent to Point {#Example_PointAdjacentPoints}
This example shows how to get the Points that are adjacent to a given point. The xms::XmUGrid::PointAdjacentPoints functions takes a point index as an argument and returns the indices of the adjacent Points.  The function xms::XmUGrid::PointAdjacentLocations returns instead the locations of the adjacent points.  The testing code for this example is in XmUGridUnitTests::testPointAdjacentPoints.

\snippet xmsgrid/ugrid/XmUGrid.cpp snip_test_PointAdjacentPoints

## Example - Get the Points or Locations of a Cell {#Example_CellPointsLocations}
This example shows how to get the points of a cell. The xms::XmUGrid::CellPoints function takes one cell index and returns a vector of point indices. The xms::XmUGrid::CellLocations functions takes a cell index and returns a VecPt3d of the locations of those points.  Functionality is shared between 2d and 3d UGrids. The testing code for this example is shared with other examples, XmUGridUnitTests::testCellFunctions.

## Example - Get the Type of a Cell {#Example_CellType}
This example shows how to get the type of a cell. The xms::XmUGrid::CellType function takes one cell index and returns the cell type. Functionality is shared between 2d and 3d UGrids. The testing code for this example is shared with other examples, XmUGridUnitTests::testCellFunctions.

## Example - Get the Count of Cells in a UGrid of each of the possible Dimensions {#Example_DimensionCounts}
This example shows how to get the count of the dimensions of cells used in a UGrid. The xms::XmUGrid::DimensionCounts function returns a vector with the number of cells with zero dimensions in the zero index, number of cells with one dimension in the first index, number of cells with two dimensions in the second index, and the number of cells with three dimensions in the third index. Functionality is shared between 2d and 3d UGrids. The testing code for this example is shared with other examples, XmUGridUnitTests::testCellFunctions.

## Example - Get the Dimension of a Cell {#Example_CellDimension}
This example shows how to get the dimension of a cell. The xms::XmUGrid::CellDimension function takes one cell index and returns the cell dimension as an integer value. Functionality is shared between 2d and 3d UGrids. The testing code for this example is shared with other examples, XmUGridUnitTests::testCellFunctions.

\snippet xmsgrid/ugrid/XmUGrid.cpp snip_test_CellFunctions

## Example - Get the Cellstream of the UGrid {#Example_Cellstream}
This example shows how to get the entire cellstream of the UGrid. The xms::XmUGrid::Cellstream function returns a vector of integers that is the cellstream. Functionality is shared between 2d and 3d UGrids. The testing code for this example is shared with other examples, XmUGridUnitTests::testCellstreamFunctions.

## Example - Get a the Cellstream for Single Cell {#Example_CellCellstream}
This example shows how to get the cellstream for one cell. The xms::XmUGrid::CellCellstream function takes a cell index and a vector of integers that is the cellstream for the specified cell passed in by reference. Functionality is shared between 2d and 3d UGrids. The testing code for this example is shared with other examples, XmUGridUnitTests::testCellstreamFunctions.

\snippet xmsgrid/ugrid/XmUGrid.cpp snip_test_CellstreamFunctions

## Example - Get the Cells Adjacent to a Given Cell {#Example_CellAdjacentCells}
This example shows how to get the cells adjacent to a given cell. Cells are adjacent if they share at least one point. The xms::XmUGrid::CellAdjacentCells function takes a cell index and returns a vector of cell indices. Functionality is shared between 2d and 3d UGrids. The testing code for this example is XmUGridUnitTests::testCellAdjacentCells.

\snippet xmsgrid/ugrid/XmUGrid.cpp snip_test_CellAdjacentCells

## Example - Get a Plan View Polygon {#Example_CellPlanViewPolygon}
This example shows how to get a plan view polygon. The xms::XmUGrid::CellPlanViewPolygon function takes a cell index and a vector of Pt3d which is the points of the 2D cell and returns whether the operation was succesful. The testing code for this example is XmUGridUnitTests::testCellPlanViewPolygon.

\snippet xmsgrid/ugrid/XmUGrid.cpp snip_test_CellPlanViewPolygon

## Example - Get Number of Cell Edges {#Example_CellEdgeCount}
This example shows how to get the number of cell edges in a cell. The xms::XmUGrid::CellEdgeCount function takes a cell index and returns the number of edges as an int. Functionality is shared between 2d and 3d UGrids. The testing code for this example is XmUGridUnitTests::testCellEdgeAdjacentCellFunctions

## Example - Get Cell Edge from Edge Index {#Example_CellEdge}
This example shows how to get the cell edge from a given cell and edge index. The xms::XmUGrid::CellEdge function takes a cell index and an edge index and returns a XmEdge containing the point indices of the edge. Functionality is shared between 2d and 3d UGrids. The testing code for this example is shared with other examples, XmUGridUnitTests::testCellEdgeAdjacentCellFunctions

\snippet xmsgrid/ugrid/XmUGrid.cpp snip_test_CellEdgeAdjacentCellFunctions

## Example Get Cells Adjacent to an Edge of a Cell {#Example_CellEdgeAdjacentCells}
This example shows how to get all cells which share the specified edge with a cell. The xms::XmUGrid::CellEdgeAdjacentCells function takes a cell index and an edge index and returns a vector of cell indices. Functionality is shared between 2d and 3d UGrids. The testing code for this example is shared with other examples, XmUGridUnitTests::testCellEdgeAdjacentCellFunctions

## Example 2D Get the Other Cell Adjacent to a particular Cell Edge{#Example_Cell2dEdgeAdjacentCell}
This example shows how to get a 2D cell which is adjacent to another given 2D cell with a given edge index. The xms::XmUGrid::Cell2dEdgeAdjacentCell function takes a cell index and an edge index and returns a cell index, since no more than one cell may legally share an edge in this manner. The testing code for this example is shared with other examples, XmUGridUnitTests::testCellEdgeAdjacentCellFunctions

## Example Get Cells Adjacent to a Given Edge {#Example_EdgeAdjacentCells}
This example shows how to get all cells which contain a given edge. The xms::XmUGrid::EdgeAdjacentCells function takes two point indices describing an edge and returns a vector of cell indices. There is also an overload which takes a pair of point indices describing an edge. Functionality is shared between 2d and 3d UGrids. The testing code for this example is shared with other examples, XmUGridUnitTests::testCellEdgeAdjacentCellFunctions

\snippet xmsgrid/ugrid/XmUGrid.cpp snip_test_CellEdgeAdjacentCellFunctions

## Example Get Edges of a Cell {#Example_CellEdges}
This example shows how to get edges associated with a cell. The xms::XmUGrid::CellEdges function takes a cell index and returns a vector of XmEdge (each of which has a pair of integers which are point indices of the Edge). Functionality is shared between 2d and 3d UGrids. The testing code for this example is XmUGridUnitTests::testCellEdges

\snippet xmsgrid/ugrid/XmUGrid.cpp snip_test_CellEdges
