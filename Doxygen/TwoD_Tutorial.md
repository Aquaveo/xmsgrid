# 2D UGrid Tutorial

\tableofcontents
# 2D UGrid Tutorial {#TwoD_Tutorial}

## Introduction {#Intro_2Ugrid}
The purpose of this tutorial is to provide explanation on how to use xmsgrid to create two dimensional unstructured grids, or UGrids. A UGrid has points and cells defined using those points. There are many different kinds of cells available, but this tutorial will focus on the 2-dimensional cells, namely: triangle, polygon, pixel, quadrilateral.

Most UGrid functionality is shared between 2D and 3D grids. The examples in
this tutorial therefore reuse the same xms::XmUGrid API documented in the
[3D UGrid Tutorial](ThreeD_Tutorial.md). For IO and modification utilities
(read/write, clip, remove points/cells) see the
[UGrid File IO Tutorial](FileIO_Tutorial.md).

## Example - Defining Ugrid Cells {#Example_DefiningA2dUGridCell}
Supported 2D grid cells include: triangle (5), polygon (7), pixel (8), quad (9). A cell is defined with the number declaration of the shape (5, 7, 8, and 9 respectively as defined by the enumeration xms::XmUGridCellType), then the number of points, followed by the point indices. The cell definitions mirror VTK cell definitions which are available on page 9 of VTK File Formats for VTK version 4.2 at https://www.vtk.org/wp-content/uploads/2015/04/file-formats.pdf.

\note The integer cell-type values shown below are the on-the-wire cellstream format and are kept in sync with VTK and xms::XmUGridCellType. If that enum is ever renumbered or extended, update these examples to match.

A triangle (5) has 3 points and the points are declared in a counter-clockwise direction. A cellstream example for a triangle is: 5, 3, 0, 1, 2.

A polygon (7) does not a have a defined number of points, but the points are still declared in a counter-clockwise direction. A cellstream example for a polygon is: 7, 5, 0, 1, 2, 3, 4.

A pixel (8) has 4 orthogonally defined points. For the direction and order of points, see the illustration in the VTK file Format pdf referenced above on page 9 for a VTK_PIXEL. A cellstream example for a pixel is: 8, 4, 0, 1, 2, 3.

A quad (9) has 4 points declared in a counter-clockwise direction. A cellstream example for a quad is: 9, 4, 0, 1, 2, 3.

The testing code for this example is xms::TEST_XmUGrid2dLinear.
\snippet xmsgrid/ugrid/XmUGrid.cpp snip_test_2DShapes

## Example - Creating a New 2D UGrid With Data {#Example_New_With_Data_2d}
This example shows how to create a new 2D UGrid with the overloaded New function which directly sets the data as it constructs the grid, using the static function xms::XmUGrid::New(const VecPt3d& a_points, const VecInt& a_cellStream). Functionality is shared between 2d and 3d UGrids. The testing code for this example is XmUGridUnitTests::testGetSetPoint.

\snippet xmsgrid/ugrid/XmUGrid.cpp snip_test_NewOperator

## Example - Creating a New 2D UGrid {#Example_New2d}
This example shows how to create a new 2D UGrid. The static function xms::XmUGrid::New() returns a `std::shared_ptr<XmUGrid>`. Points and a cellstream may be passed to `New` to initialize the UGrid with data, but this is not required. Functionality is shared between 2d and 3d UGrids. The testing code for this example is XmUGridUnitTests::testUGridStreams.

## Example - Setting the UGrid Points {#Example_SetPoints2d}
This example shows how to set all of the UGrid points using xms::XmUGrid::SetLocations. The UGrid points cannot be added or removed individually, though they can be edited individually. The SetLocations function takes one argument, a vector of 3D points. It is recommended that each point is unique to avoid unexpected behavior. Functionality is shared between 2d and 3d UGrids. The testing code for this example is the same as used for creating a new UGrid, XmUGridUnitTests::testUGridStreams.

## Example - Setting the UGrid Cell Stream {#Example_SetCellstream2d}
This example shows how to set the entire UGrid Cellstream using xms::XmUGrid::SetCellstream. Cellstreams are formatted as a stream of integers starting with the cell type as described by the enumeration XmUGridCellType, then the number of points in the cell, followed by a series of indices to points. The SetCellstream function takes one argument, a vector of integers formatted as previously described. Functionality is shared between 2d and 3d UGrids. The testing code for this example is the same as used for creating a new UGrid, XmUGridUnitTests::testUGridStreams.

The xms::XmUGrid::IsValidCellstream function checks whether all cell types and point counts within the cellstream match up, but does not check for orientation or valid point positions. This function should not be relied on to catch all errors, but can be a basic check before setting the cellstream. Prefer the overload that accepts the number of points in the grid (`IsValidCellstream(cellstream, pointCount)`); the single-argument overload is deprecated because it cannot fully validate point indices. Functionality is shared between 2d and 3d UGrids. The testing code for this example is XmUGridUnitTests::SetCellstream.

\snippet xmsgrid/ugrid/XmUGrid.cpp snip_test_UGrid_Streams

## Example - Get Number Of Points {#Example_GetPointCount}
This example shows how to return the number of points contained in a UGrid. The xms::XmUGrid::GetPointCount function returns the number of points in the UGrid. Functionality is shared between 2d and 3d UGrids. The testing code for this example is shared with other examples, XmUGridUnitTests::testPointFunctions.

## Example - Get Points (Locations) {#Example_GetLocations}
This example shows how to get all points contained within the XmUGrid. The xms::XmUGrid::GetLocations function returns a vector of Pt3d's. Functionality is shared between 2d and 3d UGrids. The testing code for this example is shared with other examples, XmUGridUnitTests::testPointFunctions.

## Example - Get Point Location {#Example_GetPointLocation}
This example shows how to get a specific point given a point index. The xms::XmUGrid::GetPointLocation function returns the Pt3d of the point at the specified index. Functionality is shared between 2d and 3d UGrids. The testing code for this example is shared with other examples, XmUGridUnitTests::testPointFunctions.

## Example - Get Point Location With Z = 0 {#Example_GetPointXy0}
This example shows how to get a point's location with z forced to 0.0. The xms::XmUGrid::GetPointXy0 function takes a point index and returns the Pt3d of that point with z = 0.0. This is useful for 2D operations that should ignore the elevation of the points. Functionality is shared between 2d and 3d UGrids.

## Example - Set Point Location {#Example_SetLocation}
This example shows how to set a specific point location given a point index. The xms::XmUGrid::SetPointLocation function takes a point index and a Pt3d as arguments and returns whether the operation was successful. The function will fail and return false if the change would cause any edges to cross. Functionality is shared between 2d and 3d UGrids. The testing code for this example is shared with other examples, XmUGridUnitTests::testPointFunctions.

## Example - Check If a Point Change Is Valid {#Example_IsValidPointChange}
This example shows how to check whether moving a point would invalidate the grid without actually moving it. The xms::XmUGrid::IsValidPointChange function takes a point index and a candidate Pt3d location and returns true if no edge crossings would result. This is useful when interactively moving points to provide feedback before committing the change. Functionality is shared between 2d and 3d UGrids.

## Example - Get Locations of Many Points {#Example_GetPointsLocations}
This example shows how to convert a vector of point indices into a vector of Pt3d's. The xms::XmUGrid::GetPointsLocations function takes a vector of Point Indices as an argument and returns a vector of corresponding Pt3d's as a result. Functionality is shared between 2d and 3d UGrids. The testing code for this example is shared with other examples, XmUGridUnitTests::testPointFunctions.

## Example - Get Extents of UGrid {#Example_GetExtents}
This example shows how to get the extents of a UGrid. The xms::XmUGrid::GetExtents function takes two 3D points as arguments describing the minimum and maximum extent that the points of the UGrid cover. These arguments will be set by the function. Functionality is shared between 2d and 3d UGrids. The testing code for this example is shared with other examples, XmUGridUnitTests::testPointFunctions.

## Example - Get Cells Adjacent to a Point {#Example_GetPointAdjacentCells}
This example shows how to get the cells associated with a single point. The xms::XmUGrid::GetPointAdjacentCells function takes one point index as an argument and returns a vector of cell indices. Use xms::XmUGrid::GetPointAdjacentCellCount to query just the count without allocating a vector. Functionality is shared between 2d and 3d UGrids. The testing code for this example is shared with other examples, XmUGridUnitTests::testPointFunctions.

## Example - Get the Cells that Share All of Group of Points {#Example_GetPointsAdjacentCells}
This example shows how to get the cells that share all of the same points or points. The xms::XmUGrid::GetPointsAdjacentCells function takes a vector of point indices as an argument and returns a vector of cell indices. Functionality is shared between 2d and 3d UGrids. The testing code for this example is shared with other examples, XmUGridUnitTests::testPointFunctions.

\snippet xmsgrid/ugrid/XmUGrid.cpp snip_test_PointFunctions

## Example - Get the Points (or their Locations) Adjacent to Point {#Example_GetPointAdjacentPoints}
This example shows how to get the Points that are adjacent to a given point. The xms::XmUGrid::GetPointAdjacentPoints function takes a point index as an argument and returns the indices of the adjacent Points. The function xms::XmUGrid::GetPointAdjacentLocations returns instead the locations of the adjacent points. The testing code for this example is in XmUGridUnitTests::testGetPointAdjacentPoints.

\snippet xmsgrid/ugrid/XmUGrid.cpp snip_test_GetPointAdjacentPoints

## Example - Get the Points or Locations of a Cell {#Example_GetCellPointsLocations}
This example shows how to get the points of a cell. The xms::XmUGrid::GetCellPoints function takes one cell index and returns a vector of point indices. The xms::XmUGrid::GetCellLocations function takes a cell index and returns a VecPt3d of the locations of those points. Use xms::XmUGrid::GetCellPointCount to query just the number of points in a cell. Functionality is shared between 2d and 3d UGrids. The testing code for this example is shared with other examples, XmUGridUnitTests::testCellFunctions.

## Example - Get the Type of a Cell {#Example_GetCellType}
This example shows how to get the type of a cell. The xms::XmUGrid::GetCellType function takes one cell index and returns the cell type. Functionality is shared between 2d and 3d UGrids. The testing code for this example is shared with other examples, XmUGridUnitTests::testCellFunctions.

## Example - Get the Count of Cells in a UGrid of each of the possible Dimensions {#Example_GetDimensionCounts}
This example shows how to get the count of the dimensions of cells used in a UGrid. The xms::XmUGrid::GetDimensionCounts function returns a vector with the number of cells with zero dimensions in the zero index, number of cells with one dimension in the first index, number of cells with two dimensions in the second index, and the number of cells with three dimensions in the third index. Functionality is shared between 2d and 3d UGrids. The testing code for this example is shared with other examples, XmUGridUnitTests::testCellFunctions.

## Example - Get the Dimension of a Cell {#Example_GetCellDimension}
This example shows how to get the dimension of a cell. The xms::XmUGrid::GetCellDimension function takes one cell index and returns the cell dimension as an integer value. Functionality is shared between 2d and 3d UGrids. The testing code for this example is shared with other examples, XmUGridUnitTests::testCellFunctions.

## Example - Get the Extents of a Cell {#Example_GetCellExtents}
This example shows how to get the bounding extents of a single cell. The xms::XmUGrid::GetCellExtents function takes a cell index and two Pt3d output arguments which are set to the minimum and maximum extents of the cell. Functionality is shared between 2d and 3d UGrids.

## Example - Get the Centroid of a Cell {#Example_GetCellCentroid}
This example shows how to compute the centroid of a cell. The xms::XmUGrid::GetCellCentroid function takes a cell index and a Pt3d output argument which is set to the centroid location. The function returns true if the centroid could be computed. Functionality is shared between 2d and 3d UGrids.

\snippet xmsgrid/ugrid/XmUGrid.cpp snip_test_CellFunctions

## Example - Get the Cellstream of the UGrid {#Example_GetCellstream}
This example shows how to get the entire cellstream of the UGrid. The xms::XmUGrid::GetCellstream function returns a vector of integers that is the cellstream. Functionality is shared between 2d and 3d UGrids. The testing code for this example is shared with other examples, XmUGridUnitTests::testCellstreamFunctions.

## Example - Get a the Cellstream for Single Cell {#Example_GetCellCellstream}
This example shows how to get the cellstream for one cell. The xms::XmUGrid::GetCellCellstream function takes a cell index and a vector of integers that is the cellstream for the specified cell passed in by reference. Use xms::XmUGrid::GetCellCellstreamIndex to obtain the offset of a cell within the underlying cellstream. Functionality is shared between 2d and 3d UGrids. The testing code for this example is shared with other examples, XmUGridUnitTests::testCellstreamFunctions.

\snippet xmsgrid/ugrid/XmUGrid.cpp snip_test_CellstreamFunctions

## Example - Get the Cells Adjacent to a Given Cell {#Example_GetCellAdjacentCells}
This example shows how to get the cells adjacent to a given cell. Cells are adjacent if they share at least one point. The xms::XmUGrid::GetCellAdjacentCells function takes a cell index and returns a vector of cell indices. Functionality is shared between 2d and 3d UGrids. The testing code for this example is XmUGridUnitTests::testGetCellAdjacentCells.

\snippet xmsgrid/ugrid/XmUGrid.cpp snip_test_GetCellAdjacentCells

## Example - Get a Plan View Polygon {#Example_GetCellPlanViewPolygon}
This example shows how to get a plan view polygon. The xms::XmUGrid::GetCellPlanViewPolygon function takes a cell index and a vector of Pt3d which is the points of the 2D cell and returns whether the operation was successful. The testing code for this example is XmUGridUnitTests::testGetCellPlanViewPolygon.

\snippet xmsgrid/ugrid/XmUGrid.cpp snip_test_GetCellPlanViewPolygon

## Example - Get Number of Cell Edges {#Example_GetCellEdgeCount}
This example shows how to get the number of cell edges in a cell. The xms::XmUGrid::GetCellEdgeCount function takes a cell index and returns the number of edges as an int. Functionality is shared between 2d and 3d UGrids. The testing code for this example is XmUGridUnitTests::testCellEdgeAdjacentCellFunctions

## Example - Get Cell Edge from Edge Index {#Example_GetCellEdge}
This example shows how to get the cell edge from a given cell and edge index. The xms::XmUGrid::GetCellEdge function takes a cell index and an edge index and returns a XmEdge containing the point indices of the edge. Functionality is shared between 2d and 3d UGrids. The testing code for this example is shared with other examples, XmUGridUnitTests::testCellEdgeAdjacentCellFunctions

\snippet xmsgrid/ugrid/XmUGrid.cpp snip_test_CellEdgeAdjacentCellFunctions

## Example Get Cells Adjacent to an Edge of a Cell {#Example_GetCellEdgeAdjacentCells}
This example shows how to get all cells which share the specified edge with a cell. The xms::XmUGrid::GetCellEdgeAdjacentCells function takes a cell index and an edge index and returns a vector of cell indices. Functionality is shared between 2d and 3d UGrids. The testing code for this example is shared with other examples, XmUGridUnitTests::testCellEdgeAdjacentCellFunctions

## Example 2D Get the Other Cell Adjacent to a particular Cell Edge {#Example_GetCell2dEdgeAdjacentCell}
This example shows how to get a 2D cell which is adjacent to another given 2D cell with a given edge index. The xms::XmUGrid::GetCell2dEdgeAdjacentCell function takes a cell index and an edge index and returns a cell index, since no more than one cell may legally share an edge in this manner. The testing code for this example is shared with other examples, XmUGridUnitTests::testCellEdgeAdjacentCellFunctions

## Example Get Cells Adjacent to a Given Edge {#Example_GetEdgeAdjacentCells}
This example shows how to get all cells which contain a given edge. The xms::XmUGrid::GetEdgeAdjacentCells function takes two point indices describing an edge and returns a vector of cell indices. There is also an overload which takes a pair of point indices describing an edge. Functionality is shared between 2d and 3d UGrids. The testing code for this example is shared with other examples, XmUGridUnitTests::testCellEdgeAdjacentCellFunctions

## Example Get Edges of a Cell {#Example_GetCellEdges}
This example shows how to get edges associated with a cell. The xms::XmUGrid::GetCellEdges function takes a cell index and returns a vector of XmEdge (each of which has a pair of integers which are point indices of the Edge). Functionality is shared between 2d and 3d UGrids. The testing code for this example is XmUGridUnitTests::testCellEdges

\snippet xmsgrid/ugrid/XmUGrid.cpp snip_test_CellEdges

## Example - Caching and Modification State {#Example_CacheAndModified}
For grids that are queried often, the UGrid maintains internal caches that
accelerate adjacency lookups. Use xms::XmUGrid::SetUseCache to opt in or out of
caching. xms::XmUGrid::GetModified returns true when the grid has been mutated
since it was created or since the last call to xms::XmUGrid::SetUnmodified.
These flags are useful when synchronizing derived data structures with the
grid. Functionality is shared between 2d and 3d UGrids.
