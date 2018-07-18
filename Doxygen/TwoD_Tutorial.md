# 2D UGrid Tutorial

\tableofcontents
# 2D UGrid Tutorial {#TwoD_Tutorial}

## Introduction {#Intro_2Ugrid}
The purpose of this tutorial is to provide explanation on how to use xmsgrid to create two dimensional unstructured grids, or UGrids. A UGrid has points and cells defined using those points. There are many different kinds of cells available, but this tutorial will focus on the 2-dimensional cells, namely: triangle, polygon, pixel, quadrilateral.

## Example - Defining Ugrid Cells {#Example_DefiningA2dUGridCell}
Supported 2D grid cells include: triangle (5), polygon (7), pixel (8), quad (9). A cell is defined with the number declaration of the shape (5, 7, 8, and 9 respectively as defined by the enumeration xms::XmUGridCellType), then the number of points, followed by the point indices. The cell definitions mirror VTK cell definitions which are available on page 9 of VTK File Formats for VTK version 4.2 at https://www.vtk.org/wp-content/uploads/2015/04/file-formats.pdf.

A triangle (5) has 3 points and the points are declared in a counter-clockwise direction. A cell stream example for a triangle is: 5, 3, 0, 1, 2.

A polygon (7) does not a have a defined number of points, but the points are still declared in a counter-clockwise direction. A cell stream example for a polygon is: 7, 5, 0, 1, 2, 3, 4.

A pixel (8) has 4 orthogonially defined points. For the direction and order of points, see the illustration in the VTK file Format pdf referenced above on page 9 for a VTK_PIXEL. A cell stream example for a pixel is: 8, 4, 0, 1, 2, 3.

A quad (9) has 4 points declared in a counter-clockwise direction. A cell stream example for a quad is: 9, 4, 0, 1, 2, 3.

The testing code for this example is XmUGridUnitTests::TEST_XmUGrid2dLinear.
\snippet xmsgrid/ugrid/XmUGrid.cpp snip_test_2DShapes

## Example - Creating a New 2D UGrid With Data {#Example_New_With_Data_2d}
This example shows how to create a new 2D UGrid with the overloaded New function which directly sets the data as it constructs the grid, using the static function xms::XmUGrid::New(const VecPt3d& a_points, const VecInt& a_cellStream). Functionality is shared between 2d and 3d UGrids. The testing code for this example is XmUGridUnitTests::testGetSetPoint.

\snippet xmsgrid/ugrid/XmUGrid.cpp snip_test_NewOperator

## Example - Creating a New 2D UGrid {#Example_New2d}
This example shows how to create a new 2D UGrid. XmUGrid is an abstract class that cannot be instantiated. The static function xms::XmUGrid::New() is the only method to obtain a Boost Shared Pointer to an instance of XmUGrid. Points and Cellstream may be passed to New to initialize the UGrid with data but this is not required. Functionality is shared between 2d and 3d UGrids. The testing code for this example is XmUGridUnitTests::testUGridStreams.

## Example - Setting the UGrid Points {#Example_SetPoints2d}
This example shows how to set all of the UGrid points using xms::XmUGridImpl::SetPoints. The Ugrid points cannot be added or removed individually, though they can be edited individually. The SetPoints function takes one argument, a vector of 3D points. It is reccomended that each point is unique to avoid unexpected behavior. Functionality is shared between 2d and 3d UGrids. The testing code for this example is the same as used for creating a new UGrid, XmUGridUnitTests::testUGridStreams.

## Example - Setting the UGrid Cell Stream {#Example_SetCellStream2d}
This example shows how to set the entire UGrid Cellstream using xms::XmUGridImpl::SetCellStream. Cellstreams are formatted as a stream of integers starting with the cell type as described by the enumeration XmUGridCellType, then the number of points in the cell, followed by a series of indices to points. The SetCellStream function takes one argument, a vector of integers formatted as previously described. Functionality is shared between 2d and 3d UGrids. The testing code for this example is the same as used for creating a new UGrid, XmUGridUnitTests::testUGridStreams.

\snippet xmsgrid/ugrid/XmUGrid.cpp snip_test_UGrid_Streams

## Example - Validating the Cellstream {#Example_ValidatingCellStream2d}
This example shows how to validate whether a given Cellstream is valid as previously defined. The xms::XmUGridImpl::ValidCellStream checks whether all cell types and point counts within the cellstream match up, but does not check for orientation or valid point positions. This function should not be relied on to catch all errors, but can be a basic check before setting the cellstream. The function takes one arguement, a cellstream containing one or more cells. Functionality is shared between 2d and 3d UGrids. The testing code for this example is XmUGridUnitTests::SetCellStream.

\snippet xmsgrid/ugrid/XmUGrid.cpp snip_test_SetCellStream

## Example - Get Number Of Points {#Example_GetNumberOfPoints2d}
This example shows how to return the number of points contained in a UGrid. The xms::XmUGridImpl::GetNumberOfPoints function returns the number of points in the UGrid. Functionality is shared between 2d and 3d UGrids. The testing code for this example is shared with other examples, XmUGridUnitTests::testPointFunctions.

## Example - Get Points {#Example_GetPoints2d}
This example shows how to get all points contained within the XmUGrid. The xms::XmUGridImpl::GetPoints function returns a vector of Pt3d's. Functionality is shared between 2d and 3d UGrids. The testing code for this example is shared with other examples, XmUGridUnitTests::testPointFunctions.

## Example - Get Point {#Example_GetPoint2d}
This example shows how to get a specific point given a point index. The xms::XmUGridImpl::GetPoint function returns the Pt3d of the point at the specified index. Functionality is shared between 2d and 3d UGrids. The testing code for this example is shared with other examples, XmUGridUnitTests::testPointFunctions.

## Example - Set Point {#Example_SetPoint2d}
This example shows how to set a specific point given a point index. The xms::XmUGridImpl::SetPoint function takes a point index and a Pt3d as arguements and returns whether the operation was succesful. The function will fail and return false if the change would cause any edges to cross. Functionality is shared between 2d and 3d UGrids. The testing code for this example is shared with other examples, XmUGridUnitTests::testPointFunctions.

## Example - Get Points from Point Indices {#Example_GetPointsFromPointIdxs2d}
This example shows how to convert a vector of point indices into a vector of Pt3d's. The xms::XmUGridImpl::GetPointsFromPointIdxs function takes a vector of Point Indices as an arguement and returns a vector of corresponding Pt3d's as a result. Functionality is shared between 2d and 3d UGrids. The testing code for this example is shared with other examples, XmUGridUnitTests::testPointFunctions.

## Example - Get Extents of UGrid {#Example_GetExtents2d}
This example shows how to get the extents of a UGrid. The xms::XmUGridImpl::GetExtents function takes two 3D points as arguements describing the minimum and maximum extent that the points of the UGrid cover. These arguments will be set by the funtion. Functionality is shared between 2d and 3d UGrids. The testing code for this example is shared with other examples, XmUGridUnitTests::testPointFunctions.

## Example - Get Cells Associated with a Point {#Example_GetPointCells2d}
This example shows how to the cells associated with a single point. The xms::XmUGridImpl::GetPointCells function takes one point index as an arguement and returns a vector of point indices. Functionality is shared between 2d and 3d UGrids. The testing code for this example is shared with other examples, XmUGridUnitTests::testPointFunctions.

## Example - Get the Cells that Share the Same Point or Points {#Example_GetCommonCells2d}
This example shows how to the cells that share the same point or points. The xms::XmUGridImpl::GetCommonCells function takes a vector of point indices as an arguement and returns a vector of cell indices. Functionality is shared between 2d and 3d UGrids. The testing code for this example is shared with other examples, XmUGridUnitTests::testPointFunctions.

\snippet xmsgrid/ugrid/XmUGrid.cpp snip_test_PointFunctions

## Example - Get the Points of a Cell {#Example_GetPointsOfCell2d}
This example shows how to get the points of a cell. The xms::XmUGridImpl::GetPointsOfCell function takes one cell index and returns a vector of point indices. There is also an overloaded function that will take the vector of point indices as an argument passed by reference which returns whether the operation was successful. Functionality is shared between 2d and 3d UGrids. The testing code for this example is shared with other examples, XmUGridUnitTests::TestCellFunctions.

## Example - Get the Type of a Cell {#Example_GetCellType2d}
This example shows how to get the type of a cell. The xms::XmUGridImpl::GetCellType function takes one cell index and returns the cell type. Functionality is shared between 2d and 3d UGrids. The testing code for this example is shared with other examples, XmUGridUnitTests::TestCellFunctions.

## Example - Get the Count of the Dimensions of Cells used in a UGrid {#Example_GetDimensionCount2d}
This example shows how to get the count of the dimensions of cells used in a UGrid. The xms::XmUGridImpl::GetDimensionCount function returns a vector with the number of cells with zero dimensions in the zero index, number of cells with one dimension in the first index, number of cells with two dimensions in the second index, and the number of cells with three dimensions in the third index. Functionality is shared between 2d and 3d UGrids. The testing code for this example is shared with other examples, XmUGridUnitTests::TestCellFunctions.

## Example - Get the Dimension of a Cell {#Example_GetCellDimension2d}
This example shows how to get the dimension of a cell. The xms::XmUGridImpl::GetCellDimension function takes one cell index and returns the cell dimension as an integer value. Functionality is shared between 2d and 3d UGrids. The testing code for this example is shared with other examples, XmUGridUnitTests::TestCellFunctions.

\snippet xmsgrid/ugrid/XmUGrid.cpp snip_test_CellFunctions

## Example - Get the Cellstream of the UGrid {#Example_GetCellStream2d}
This example shows how to get the entire cellstream of the UGrid. The xms::XmUGridImpl::GetCellStream function returns a vector of integers that is the cell stream. Functionality is shared between 2d and 3d UGrids. The testing code for this example is shared with other examples, XmUGridUnitTests::testGetCellStreamFunctions.

## Example - Get a Single Cellstream for One Cell {#Example_GetSingleCellStream2d}
This example shows how to get a single cellstream for one cell. The xms::XmUGridImpl::GetSingleCellStream function takes a cell index and a vector of integers that is the cell stream for the specified cell passed in by reference. Functionality is shared between 2d and 3d UGrids. The testing code for this example is shared with other examples, XmUGridUnitTests::testGetCellStreamFunctions.

\snippet xmsgrid/ugrid/XmUGrid.cpp snip_test_GetCellStreamFunctions

## Example - Get the Cells that Neighbor a Given Cell {#Example_GetCellNeighbors2d}
This example shows how to get the cells that neighbor a given cell. Cells are neighbors if they share at least one point. The xms::XmUGridImpl::GetCellNeighbors function takes a cell index and returns a vector of cell indices. Functionality is shared between 2d and 3d UGrids. The testing code for this example is XmUGridUnitTests::testGetCellNeighbors.

\snippet xmsgrid/ugrid/XmUGrid.cpp snip_test_GetCellNeighbors

## Example - Get a Plan View Polygon {#Example_GetPlanViewPolygon2d}
This example shows how to get a plan view polygon. The xms::XmUGridImpl::GetPlanViewPolygon function takes a cell index and a vector of Pt3d which is the points of the 2D cell and returns whether the operation was succesful. The testing code for this example is XmUGridUnitTests::testGetPlanViewPolygon.

\snippet xmsgrid/ugrid/XmUGrid.cpp snip_test_GetPlanViewPolygon

## Example - Get Number of Cell Edges {#Example_GetNumberOfCellEdges2d}
This example shows how to get the number of cell edges in a cell. The xms::XmUGridImpl::GetNumberOfCellEdges function takes a cell index and returns the number of edges as an int. Functionality is shared between 2d and 3d UGrids. The testing code for this example is XmUGridUnitTests::testGetCellEdgeFromEdgeIndex

## Example - Get Cell Edge from Edge Index {#Example_GetCellEdgeFromEdgeIndex2d}
This example shows how to get the cell edge from a given cell and edge index. The xms::XmUGridImpl::GetCellEdgeFromEdgeIndex function takes a cell index and an edge index and returns a pair of ints containing the point indices of the edge. Functionality is shared between 2d and 3d UGrids. The testing code for this example is shared with other examples, XmUGridUnitTests::testGetCellEdgeFromEdgeIndex

\snippet xmsgrid/ugrid/XmUGrid.cpp snip_test_GetCellEdgeFromEdgeIndex2D

## Example Get Adjacent Cells {#Example_GetAdjacentCells2d}
This example shows how to get all cells which share the specified edge with a cell. The xms::XmUGridImpl::GetAdjacentCells function takes a cell index and an edge index and returns a vector of cell indices. Functionality is shared between 2d and 3d UGrids. The testing code for this example is shared with other examples, XmUGridUnitTests::testGetAdjacentCellFunctions

## Example 2D Get Adjacent Cell {#Example_GetAdjacent2DCell}
This example shows how to get a 2D cell which is adjacent to another given 2D cell with a given edge index. The xms::XmUGridImpl::Get2dAdjacentCell function takes a cell index and an edge index and returns a cell index, since no more than one cell may legally share an edge in this manner. The testing code for this example is shared with other examples, XmUGridUnitTests::testGetAdjacentCellFunctions

## Example Get Adjacent Cells from Given Edge {#Example_GetAdjacentCellsFromAGivenEdge2d}
This example shows how to get all cells which contain a given edge. The xms::XmUGridImpl::GetAdjacentCellsFromGivenEdge function takes two point indices describing an edge and returns a vector of cell indices. There is also an overload which takes a pair of point indices describing an edge. Functionality is shared between 2d and 3d UGrids. The testing code for this example is shared with other examples, XmUGridUnitTests::testGetAdjacentCellFunctions

\snippet xmsgrid/ugrid/XmUGrid.cpp snip_test_GetAdjacentCellFunctions

## Example Get Edges Associated with a Point {#Example_GetEdgesFromPoint2d}
This example shows how to get edges associated with a point. The xms::XmUGridImpl::GetEdgesFromPoint function takes a point index, a vector of cell indices, and a vector of edge indices. The cell and edge indices will be set by the function. It will return whether it was successful. There are two overloads, the first takes a point index, a vector of cell indices, and a vector of edges defined as a pair of integers which are point indices. The second overload takes a point index, a vector of cell indices, and two vectors of edge point indexes. Functionality is shared between 2d and 3d UGrids. The testing code for this example is XmUGridUnitTests::testGetEdgesFromPoint

\snippet xmsgrid/ugrid/XmUGrid.cpp snip_test_GetEdgesFromPoint

## Example Get Edges Associated with a Cell {#Example_GetEdgesOfCell2d}
This example shows how to get edges associated with a cell. The xms::XmUGridImpl::GetEdgesOfCell function takes a cell index and returns a vector of pairs of integers which are point indices. Functionality is shared between 2d and 3d UGrids. The testing code for this example is XmUGridUnitTests::testGetEdgesFromPoint

\snippet xmsgrid/ugrid/XmUGrid.cpp snip_test_GetEdgesOfCell

