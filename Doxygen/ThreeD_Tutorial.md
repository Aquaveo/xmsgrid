# 3D UGrid Tutorial

\tableofcontents
# 3D UGrid Tutorial {#ThreeD_Tutorial}

## Introduction {#Intro_3Ugrid}
The purpose of this tutorial is to provide explanation on how to use xmsgrid to create three dimensional unstructured grids, or UGrids. A UGrid has points and cells defined using those points. There are many different kinds of cells available, but this tutorial will focus on the 3-dimensional cells, namely: tetrahedron, voxel, hexahedron, wedge, pyramid, and polyhedron.

For 2D-only concepts (plan-view polygons, edge adjacency for a single 2D cell)
see the [2D UGrid Tutorial](TwoD_Tutorial.md). For IO and modification
utilities see the [UGrid File IO Tutorial](FileIO_Tutorial.md).

## Example - Defining Ugrid Cells {#Example_DefiningA3dUGridCell}
Supported 3D grid cells include: tetrahedron (10), voxel (11), hexahedron (12), wedge (13), pyramid (14), and polyhedron (42). A cell is defined with the number declaration of the shape (10, 11, 12, 13, 14, and 42, respectively, as defined by the enumeration xms::XmUGridCellType), then the number of points, followed by the point indices. The cell definitions mirror VTK cell definitions which are available on page 9 of VTK File Formats for VTK version 4.2 at https://www.vtk.org/wp-content/uploads/2015/04/file-formats.pdf.

A tetrahedron (10) has 4 points. See the illustration in the VTK file Format pdf referenced above on page 9 for a VTK_TETRA for point order. A cellstream example for a tetrahedron is: 10, 4, 0, 1, 2, 3.

A voxel (11) has 8 orthogonally defined points. See the illustration in the VTK file Format pdf referenced above on page 9 for a VTK_VOXEL for point order. A cellstream example for a voxel is: 11, 8, 0, 1, 2, 3, 4, 5, 6, 7.

A hexahedron (12) has 8 points. See the illustration in the VTK file Format pdf referenced above on page 9 for a VTK_HEXAHEDRON for point order. A cellstream example for a hexahedron is: 12, 8, 0, 1, 2, 3, 4, 5, 6, 7.

A wedge (13) has 6 points. See the illustration in the VTK file Format pdf referenced above on page 9 for a VTK_WEDGE for point order. A cellstream example for a wedge is: 13, 6, 0, 1, 2, 3, 4, 5.

A pyramid (14) has 5 points. See the illustration in the VTK file Format pdf referenced above on page 9 for a VTK_PYRAMID for point order. A cellstream example for a pyramid is: 14, 5, 0, 1, 2, 3, 4.

A polyhedron (42) does not a have a defined number of points. A polyhedron cellstream has the following format: The cell type, number of faces, and then repeated for each face: the number of points in the face, followed by the points in the face declared in a counter-clockwise (ccw) direction (as viewed from outside the solid). A cellstream example for a polyhedron representation of a cube defined with points (10, 11, 12, 13) on the top face and points (14, 15, 16, 17) on the bottom face as viewed from above with points ordered clockwise from the lower left as viewed from above) is: 42, 6, 4, 10, 13, 12, 11, 4, 10, 11, 15, 14, 4, 11, 12, 16, 15, 4, 12, 13, 17, 16, 4, 13, 10, 14, 17, 4, 14, 15, 16, 17. (42 is the type number, 6 is the number of faces, 4 is the number of points in the first face, those points are: 10, 13, 12, 11 in ccw order from the outside, 4 is the number of points on the next face, 10, 11, 15, 14 are the point indices of that face in ccw order, and so on.)

The testing code for this example is in TEST_XmUGrid3DLinear.
\snippet xmsgrid/ugrid/XmUGrid.cpp snip_test_3DShapes

## Example - Creating a New 3D UGrid With Data {#Example_New_With_Data_3d}
This example shows how to create a new 3D UGrid with the overloaded New function which directly sets the data as it constructs the grid, using the static function xms::XmUGrid::New(const VecPt3d& a_points, const VecInt& a_cellStream). Functionality is shared between 2d and 3d UGrids. The testing code for this example is XmUGridUnitTests::testGetSetPoint.

\snippet xmsgrid/ugrid/XmUGrid.cpp snip_test_NewOperator

## Example - Creating a New 3D UGrid {#Example_New3d}
This example shows how to create a new 3D UGrid. The static function xms::XmUGrid::New returns a `std::shared_ptr<XmUGrid>`. Points and a cellstream may be passed to `New` to initialize the UGrid with data, but this is not required. Functionality is shared between 2d and 3d UGrids. The testing code for this example is XmUGridUnitTests::testUGridStreams.

## Example - Setting the UGrid Points {#Example_SetPoints3d}
This example shows how to set all of the UGrid points using xms::XmUGrid::SetLocations. The UGrid points cannot be added or removed individually, though they can be edited individually. The SetLocations function takes one argument, a vector of 3D points. It is recommended that each point is unique to avoid unexpected behavior. Functionality is shared between 2d and 3d UGrids. The testing code for this example is the same as used for creating a new UGrid, XmUGridUnitTests::testUGridStreams.

## Example - Setting the UGrid Cell Stream {#Example_SetCellstream3d}
This example shows how to set the entire UGrid Cellstream using xms::XmUGrid::SetCellstream. Cellstreams are formatted as a stream of integers starting with the cell type as described by the enumeration XmUGridCellType, then the number of points in the cell, followed by a series of indices to points. The SetCellstream function takes one argument, a vector of integers formatted as previously described. Functionality is shared between 2d and 3d UGrids. The testing code for this example is the same as used for creating a new UGrid, XmUGridUnitTests::testUGridStreams.

The xms::XmUGrid::IsValidCellstream function checks whether all cell types and point counts within the cellstream match up, but does not check for orientation or valid point positions. This function should not be relied on to catch all errors, but can be a basic check before setting the cellstream. Prefer the overload that accepts the number of points (`IsValidCellstream(cellstream, pointCount)`); the single-argument overload is deprecated because it cannot fully validate point indices. Functionality is shared between 2d and 3d UGrids. The testing code for this example is XmUGridUnitTests::SetCellstream.

\snippet xmsgrid/ugrid/XmUGrid.cpp snip_test_UGrid_Streams

## Example - Cell Ordering of a Layered 3D UGrid {#Example_CellOrdering3d}
For 3D UGrids built up from stacked layers, xmsgrid can record whether the
layer index increases as you move up or down through the grid. The enumeration
xms::XmUGridCellOrdering distinguishes XMU_CELL_ORDER_INCREASING_DOWN,
XMU_CELL_ORDER_INCREASING_UP, and XMU_CELL_ORDER_UNKNOWN. Use
xms::XmUGrid::GetCellOrdering to read the current setting,
xms::XmUGrid::SetCellOrdering to override it, and
xms::XmUGrid::CalculateCellOrdering to compute the ordering from cell
geometry. The cell ordering is required for face-orientation queries (top vs.
bottom) on prismatic cells.

## Example - Get Number Of Points {#Example_GetPointCount3d}
This example shows how to return the number of points contained in a UGrid. The xms::XmUGrid::GetPointCount function returns the number of points in the UGrid. Functionality is shared between 2d and 3d UGrids. The testing code for this example is shared with other examples, XmUGridUnitTests::testPointFunctions.

## Example - Get Point Locations {#Example_GetLocations3d}
This example shows how to get all points contained within the XmUGrid. The xms::XmUGrid::GetLocations function returns a vector of Pt3d's. Functionality is shared between 2d and 3d UGrids. The testing code for this example is shared with other examples, XmUGridUnitTests::testPointFunctions.

## Example - Get Location of a Point {#Example_PointLocation3d}
This example shows how to get a specific point given a point index. The xms::XmUGrid::GetPointLocation function returns the Pt3d of the point at the specified index. Functionality is shared between 2d and 3d UGrids. The testing code for this example is shared with other examples, XmUGridUnitTests::testPointFunctions.

## Example - Set Point Location {#Example_SetLocation3d}
This example shows how to set a specific point given a point index. The xms::XmUGrid::SetPointLocation function takes a point index and a Pt3d as arguments and returns whether the operation was successful. The function may fail and return false if the change would cause any edges to cross. Functionality is shared between 2d and 3d UGrids. The testing code for this example is shared with other examples, XmUGridUnitTests::testPointFunctions.

## Example - Get Locations of an Array of Points {#Example_GetPointsLocations3d}
This example shows how to convert a vector of point indices into a vector of Pt3d's. The xms::XmUGrid::GetPointsLocations function takes a vector of Point Indices as an argument and returns a vector of corresponding Pt3d's as a result. Functionality is shared between 2d and 3d UGrids. The testing code for this example is shared with other examples, XmUGridUnitTests::testPointFunctions.

## Example - Get GetExtents of UGrid {#Example_GetExtents3d}
This example shows how to get the extents of a UGrid. The xms::XmUGrid::GetExtents function takes two 3D points as arguments describing the minimum and maximum extent that the points of the UGrid cover. These arguments will be set by the function. Functionality is shared between 2d and 3d UGrids. The testing code for this example is shared with other examples, XmUGridUnitTests::testPointFunctions.

## Example - Get Cells Associated with a Point {#Example_PointCells3d}
This example shows how to get the cells associated with a single point. The xms::XmUGrid::GetPointAdjacentCells function takes one point index as an argument and returns a vector of cell indices. Use xms::XmUGrid::GetPointAdjacentCellCount to query just the count. Functionality is shared between 2d and 3d UGrids. The testing code for this example is shared with other examples, XmUGridUnitTests::testPointFunctions.

## Example - Get the Cells that Share the Same Point or Points {#Example_GetPointsAdjacentCells3d}
This example shows how to get the cells that share the same point or points. The xms::XmUGrid::GetPointsAdjacentCells function takes a vector of point indices as an argument and returns a vector of cell indices. Functionality is shared between 2d and 3d UGrids. The testing code for this example is shared with other examples, XmUGridUnitTests::testPointFunctions.

\snippet xmsgrid/ugrid/XmUGrid.cpp snip_test_PointFunctions

## Example - Get the Points Adjacent to a Point {#Example_GetPointAdjacentPoints3d}
This example shows how to get the points connected to a given point by an
edge. The xms::XmUGrid::GetPointAdjacentPoints function takes a point index
and returns a vector of point indices, while
xms::XmUGrid::GetPointAdjacentLocations returns the corresponding Pt3d
locations. Functionality is shared between 2d and 3d UGrids. The testing code
for this example is in XmUGridUnitTests::testGetPointAdjacentPoints.

\snippet xmsgrid/ugrid/XmUGrid.cpp snip_test_GetPointAdjacentPoints

## Example - Get the Points of a Cell {#Example_GetCellPointsLocations3d}
This example shows how to get the points of a cell. The xms::XmUGrid::GetCellPoints function takes one cell index and returns a vector of point indices. The xms::XmUGrid::GetCellLocations function returns the locations (Pt3d) of those points. Use xms::XmUGrid::GetCellPointCount to query just the number of points in a cell. Functionality is shared between 2d and 3d UGrids. The testing code for this example is shared with other examples, XmUGridUnitTests::testCellFunctions.

## Example - Get the Type of a Cell {#Example_GetCellType3d}
This example shows how to get the type of a cell. The xms::XmUGrid::GetCellType function takes one cell index and returns the cell type. Functionality is shared between 2d and 3d UGrids. The testing code for this example is shared with other examples, XmUGridUnitTests::testCellFunctions.

## Example - Get the Number of the Cells of each Dimension in a UGrid {#Example_GetDimensionCounts3d}
This example shows how to get the count of the dimensions of cells used in a UGrid. The xms::XmUGrid::GetDimensionCounts function returns a vector with the number of cells with zero dimensions in the zero index, number of cells with one dimension in the first index, number of cells with two dimensions in the second index, and the number of cells with three dimensions in the third index. Functionality is shared between 2d and 3d UGrids. The testing code for this example is shared with other examples, XmUGridUnitTests::testCellFunctions.

## Example - Get the Dimension of a Cell {#Example_GetCellDimension3d}
This example shows how to get the dimension of a cell. The xms::XmUGrid::GetCellDimension function takes one cell index and returns the cell dimension as an integer value. Functionality is shared between 2d and 3d UGrids. The testing code for this example is shared with other examples, XmUGridUnitTests::testCellFunctions.

## Example - Get the Extents of a Cell {#Example_GetCellExtents3d}
This example shows how to get the bounding extents of a single cell. The xms::XmUGrid::GetCellExtents function takes a cell index and two Pt3d output arguments which are set to the minimum and maximum extents of the cell. Functionality is shared between 2d and 3d UGrids.

## Example - Get the Centroid of a Cell {#Example_GetCellCentroid3d}
This example shows how to compute the centroid of a cell. The xms::XmUGrid::GetCellCentroid function takes a cell index and a Pt3d output argument which is set to the centroid location. The function returns true if the centroid could be computed. Functionality is shared between 2d and 3d UGrids.

\snippet xmsgrid/ugrid/XmUGrid.cpp snip_test_CellFunctions

## Example - Get the Cellstream of the UGrid {#Example_GetCellstream3d}
This example shows how to get the entire cellstream of the UGrid. The xms::XmUGrid::GetCellstream function returns a vector of integers that is the cellstream. Functionality is shared between 2d and 3d UGrids. The testing code for this example is shared with other examples, XmUGridUnitTests::testCellstreamFunctions.

## Example - Get a Single Cellstream for One Cell {#Example_GetCellCellstream3d}
This example shows how to get the cellstream for just one cell. The xms::XmUGrid::GetCellCellstream function takes a cell index and a vector of integers that is the cellstream for the specified cell passed in by reference. Use xms::XmUGrid::GetCellCellstreamIndex to find a cell's offset within the underlying cellstream. Functionality is shared between 2d and 3d UGrids. The testing code for this example is shared with other examples, XmUGridUnitTests::testCellstreamFunctions.

\snippet xmsgrid/ugrid/XmUGrid.cpp snip_test_CellstreamFunctions

## Example - Get the Cells Adjacent to a Given Cell {#Example_GetCellAdjacentCells3d}
This example shows how to get the cells that also use any of the points of a given cell. Cells are adjacent if they share at least one point. The xms::XmUGrid::GetCellAdjacentCells function takes a cell index and returns a vector of cell indices. Functionality is shared between 2d and 3d UGrids. The testing code for this example is XmUGridUnitTests::testGetCellAdjacentCells.

\snippet xmsgrid/ugrid/XmUGrid.cpp snip_test_GetCellAdjacentCells

## Example - Get a Plan View Polygon {#Example_GetCellPlanViewPolygon3d}
This example shows how to get a plan view polygon. This function first assumes that the shape is prismatic (or that the sides of the shape are vertical) and it gathers the points of the vertical sides. If this method fails, it builds a convex hull of the unique points of the shape. If the second method is employed, concave shapes will result in a convex polygon. The xms::XmUGrid::GetCellPlanViewPolygon function takes a cell index and a vector of Pt3d to contain on return the locations of the points of the plan view polygon and returns whether the operation was successful. The testing code for this example is XmUGridUnitTests::testGetCellPlanViewPolygon.

\snippet xmsgrid/ugrid/XmUGrid.cpp snip_test_GetCellPlanViewPolygon

## Example - Get Number of Cell Edges {#Example_GetCellEdgeCount3d}
This example shows how to get the number of cell edges in a cell. The xms::XmUGrid::GetCellEdgeCount function takes a cell index and returns the number of edges as an int. Functionality is shared between 2d and 3d UGrids. The testing code for this example is XmUGridUnitTests::testGetCellEdgeCount

## Example Get Cell Edge Adjacent Cells {#Example_GetCellEdgeAdjacentCells3d}
This example shows how to get all cells which share the specified edge with a cell. The xms::XmUGrid::GetCellEdgeAdjacentCells function takes a cell index and an edge index and returns a vector of cell indices. Functionality is shared between 2d and 3d UGrids. The testing code for this example is shared with other examples, XmUGridUnitTests::testCellEdgeAdjacentCellFunctions

\snippet xmsgrid/ugrid/XmUGrid.cpp snip_test_CellEdgeAdjacentCellFunctions

## Example Get Edges Associated with a Cell {#Example_GetCellEdges3d}
This example shows how to get edges associated with a cell. The xms::XmUGrid::GetCellEdges function takes a cell index and returns a vector of XmEdge (each of which contains a pair of integers which are point indices). Functionality is shared between 2d and 3d UGrids. The testing code for this example is XmUGridUnitTests::testCellEdges

\snippet xmsgrid/ugrid/XmUGrid.cpp snip_test_CellEdges

## Example Get Number of Faces for a Cell {#Example_GetCell3dFaceCount3d}
This example shows how to get the number of faces that a cell has. The xms::XmUGrid::GetCell3dFaceCount function takes a cell index and returns the number of cell faces associated with it as an integer. The testing code for this example is XmUGridUnitTests::testCell3dFaceFunctions

\snippet xmsgrid/ugrid/XmUGrid.cpp snip_test_GetNumberOfCellFaces

## Example Get Number of Points on a Cell Face {#Example_GetCell3dFacePointCount3d}
This example shows how to get the number of points that bound a particular face of a 3D cell. The xms::XmUGrid::GetCell3dFacePointCount function takes a cell index and a face index and returns the number of points in that face. The testing code for this example is shared with another example, XmUGridUnitTests::testCell3dFaceFunctions.

## Example Get Cell Face {#Example_GetCell3dFacePoints3d}
This example shows how to get a cell face. The xms::XmUGrid::GetCell3dFacePoints function takes a cell index and a face index and returns a vector of point indices which define the face in counter-clockwise direction. The testing code for this example is shared with another example, XmUGridUnitTests::testCell3dFaceFunctions.

## Example Get Faces of Cell {#Example_GetCell3dFacesPoints3d}
This example shows how to get all the faces of a cell. The xms::XmUGrid::GetCell3dFacesPoints function takes a cell index and returns a vector of vectors (one for each face, of point indices which define that face, in counter-clockwise direction as viewed from outside). The testing code for this example is shared with another example, XmUGridUnitTests::testCell3dFaceFunctions.

\snippet xmsgrid/ugrid/XmUGrid.cpp snip_test_Cell3dFaceFunctions

## Example Get Cell Face Adjacent Cell {#Example_GetCell3dFaceAdjacentCell3d}
This example shows how to get the cell, if any, which shares a face with a specified cell and face. The xms::XmUGrid::GetCell3dFaceAdjacentCell function takes a cell index and a face index and returns the cell index of the cell which shares the face, or -1 if there are none. There is an overload which takes a cell index, a face index, an integer which it will set to be the cell index of the adjacent cell if any, and an integer which it will set to be the index of the face of the adjacent cell which it shares with the specified cell if any, and returns true if there is a cell with a shared face. The testing code for this example is XmUGridUnitTests::testGetCell3dFaceAdjacentCell.

\snippet xmsgrid/ugrid/XmUGrid.cpp snip_test_GetCell3dFaceAdjacentCell

## Example Get Cell Face Orientation {#Example_GetCell3dFaceOrientation3d}
For prismatic cells in a layered 3D UGrid the orientation of each face is one
of side, top, or bottom. The xms::XmUGrid::GetCell3dFaceOrientation function
takes a cell index and a face index and returns a value of the
xms::XmUGridFaceOrientation enumeration. The result depends on the cell
ordering recorded on the grid (see [Cell Ordering of a Layered 3D
UGrid](#Example_CellOrdering3d)); if the cell ordering is unknown the
function returns XMU_ORIENTATION_UNKNOWN.
