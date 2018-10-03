# 3D UGrid Tutorial

\tableofcontents
# 3D UGrid Tutorial {#ThreeD_Tutorial}

## Introduction {#Intro_3Ugrid}
The purpose of this tutorial is to provide explanation on how to use xmsgrid to create three dimensional unstructured grids, or UGrids. A UGrid has points and cells defined using those points. There are many different kinds of cells available, but this tutorial will focus on the 3-dimensional cells, namely: tetrahedron, voxel, hexahedron, wedge, pyramid, and polyhedron.

## Example - Defining Ugrid Cells {#Example_DefiningA3dUGridCell}
Supported 3D grid cells include: tetrahedron (10), voxel (11), hexahedron (12), wedge (13), pyramid (14), and polyhedron (42). A cell is defined with the number declaration of the shape (10, 11, 12, 13, 14, and 42, respectively, as defined by the enumeration xms::XmUGridCellType), then the number of points, followed by the point indices.  The cell definitions mirror VTK cell definitions which are available on page 9 of VTK File Formats for VTK version 4.2 at https://www.vtk.org/wp-content/uploads/2015/04/file-formats.pdf. 

A tetrahedron (10) has 4 points. See the illustration in the VTK file Format pdf referenced above on page 9 for a VTK_TETRA for point order. A cellstream example for a tetrahedron is: 10, 4, 0, 1, 2, 3.

A voxel (11) has 8 orthogonially defined points. See the illustration in the VTK file Format pdf referenced above on page 9 for a VTK_VOXEL for point order. A cellstream example for a voxel is: 11, 8, 0, 1, 2, 3, 4, 5, 6, 7.

A hexahedron (12) has 8 points. See the illustration in the VTK file Format pdf referenced above on page 9 for a VTK_HEXAHEDRON for point order. A cellstream example for a hexahedron is: 12, 8, 0, 1, 2, 3, 4, 5, 6, 7.

A wedge (13) has 6 points. See the illustration in the VTK file Format pdf referenced above on page 9 for a VTK_WEDGE for point order. A cellstream example for a wedge is: 13, 6, 0, 1, 2, 3, 4, 5.

A pyramid (14) has 5 points. See the illustration in the VTK file Format pdf referenced above on page 9 for a VTK_PYRAMID for point order. A cellstream example for a pyramid is: 14, 5, 0, 1, 2, 3, 4.

A polyhedron (42) does not a have a defined number of points. A polyhedron cellstream has the following format: The cell type, number of faces, and then repeated for each face: the number of points in the face, followed by the points in the face declared in a counter-clockwise (ccw) direction (as viewed from outside the solid). A cellstream example for a polyhedron representation of a cube defined with points (10, 11, 12, 13) on the top face and points (14, 15, 16, 17) on the bottom face as viewed from above with points ordered clockwise from the lower left as viewed from above) is: 42, 6, 4, 10, 13, 12, 11, 4, 10, 11, 15, 14, 4, 11, 12, 16, 15, 4, 12, 13, 17, 16, 4, 13, 10, 14, 17, 4, 14, 15, 16, 17.  (42 is the type number, 6 is the number of faces, 4 is the number of points in the first face, those points are: 10, 13, 12, 11 in ccw order from the outside, 4 is the number of points on the next face, 10, 11, 15, 14 are the point indices of that face in ccw order, and so on.)

The testing code for this example is in TEST_XmUGrid3DLinear.
\snippet xmsgrid/ugrid/XmUGrid.cpp snip_test_3DShapes

## Example - Creating a New 3D UGrid With Data {#Example_New_With_Data_3d}
This example shows how to create a new 3D UGrid with the overloaded New function which directly sets the data as it constructs the grid, using the static function xms::XmUGrid::New(const VecPt3d& a_points, const VecInt& a_cellStream). Functionality is shared between 2d and 3d UGrids. The testing code for this example is XmUGridUnitTests::testGetSetPoint.

\snippet xmsgrid/ugrid/XmUGrid.cpp snip_test_NewOperator

## Example - Creating a New 3D UGrid {#Example_New3d}
This example shows how to create a new 3D UGrid. XmUGrid is an abstract class that cannot be instantiated. The static function xms::XmUGrid::New is the only method to obtain a Boost Shared Pointer to an instance of XmUGrid. Points and Cellstream may be passed to New to initialize the UGrid with data but this is not required. Functionality is shared between 2d and 3d UGrids. The testing code for this example is XmUGridUnitTests::testUGridStreams.

## Example - Setting the UGrid Points {#Example_SetPoints3d}
This example shows how to set all of the UGrid points using xms::XmUGrid::SetLocations. The Ugrid points cannot be added or removed individually, though they can be edited individually. The SetPoints function takes one argument, a vector of 3D points. It is reccomended that each point is unique to avoid unexpected behavior. Functionality is shared between 2d and 3d UGrids. The testing code for this example is the same as used for creating a new UGrid, XmUGridUnitTests::testUGridStreams.

## Example - Setting the UGrid Cell Stream {#Example_SetCellstream3d}
This example shows how to set the entire UGrid Cellstream using xms::XmUGrid::SetCellstream. Cellstreams are formatted as a stream of integers starting with the cell type as described by the enumeration XmUGridCellType, then the number of points in the cell, followed by a series of indices to points. The SetCellstream function takes one argument, a vector of integers formatted as previously described. Functionality is shared between 2d and 3d UGrids. The testing code for this example is the same as used for creating a new UGrid, XmUGridUnitTests::testUGridStreams.

\snippet xmsgrid/ugrid/XmUGrid.cpp snip_test_UGrid_Streams

## Example - Validating the Cellstream {#Example_ValidatingCellstream3d}
This example shows how to validate whether a given Cellstream is valid as previously defined. The xms::XmUGrid::IsValidCellstream checks whether all cell types and point counts within the cellstream match up, but does not check for orientation or valid point positions. This function should not be relied on to catch all errors, but can be a basic check before setting the cellstream. The function takes one arguement, a cellstream containing one or more cells. Functionality is shared between 2d and 3d UGrids. The testing code for this example is XmUGridUnitTests::SetCellstream.

\snippet xmsgrid/ugrid/XmUGrid.cpp snip_test_SetCellstream

## Example - Get Number Of Points {#Example_PointCount3d}
This example shows how to return the number of points contained in a UGrid. The xms::XmUGrid::PointCount function returns the number of points in the UGrid. Functionality is shared between 2d and 3d UGrids. The testing code for this example is shared with other examples, XmUGridUnitTests::testPointFunctions.

## Example - Get Point Locations {#Example_Locations3d}
This example shows how to get all points contained within the XmUGrid. The xms::XmUGrid::Locations function returns a vector of Pt3d's. Functionality is shared between 2d and 3d UGrids. The testing code for this example is shared with other examples, XmUGridUnitTests::testPointFunctions.

## Example - Get Location of a Point {#Example_PointLocation3d}
This example shows how to get a specific point given a point index. The xms::XmUGrid::PointLocation function returns the Pt3d of the point at the specified index. Functionality is shared between 2d and 3d UGrids. The testing code for this example is shared with other examples, XmUGridUnitTests::testPointFunctions.

## Example - Set Point Location {#Example_SetLocation3d}
This example shows how to set a specific point given a point index. The xms::XmUGrid::SetLocation function takes a point index and a Pt3d as arguements and returns whether the operation was succesful. The function may fail and return false if the change would cause any edges to cross. Functionality is shared between 2d and 3d UGrids. The testing code for this example is shared with other examples, XmUGridUnitTests::testPointFunctions.

## Example - Get Locations of an Array of Points {#Example_PointsLocations3d}
This example shows how to convert a vector of point indices into a vector of Pt3d's. The xms::XmUGrid::PointsLocations function takes a vector of Point Indices as an arguement and returns a vector of corresponding Pt3d's as a result. Functionality is shared between 2d and 3d UGrids. The testing code for this example is shared with other examples, XmUGridUnitTests::testPointFunctions.

## Example - Get Extents of UGrid {#Example_Extents3d}
This example shows how to get the extents of a UGrid. The xms::XmUGrid::Extents function takes two 3D points as arguements describing the minimum and maximum extent that the points of the UGrid cover. These arguments will be set by the funtion. Functionality is shared between 2d and 3d UGrids. The testing code for this example is shared with other examples, XmUGridUnitTests::testPointFunctions.

## Example - Get Cells Associated with a Point {#Example_PointCells3d}
This example shows how to the cells associated with a single point. The xms::XmUGrid::PointCells function takes one point index as an arguement and returns a vector of point indices. Functionality is shared between 2d and 3d UGrids. The testing code for this example is shared with other examples, XmUGridUnitTests::testPointFunctions.

## Example - Get the Cells that Share the Same Point or Points {#Example_PointsAdjacentCells3d}
This example shows how to the cells that share the same point or points. The xms::XmUGrid::PointsAdjacentCells function takes a vector of point indices as an arguement and returns a vector of cell indices. Functionality is shared between 2d and 3d UGrids. The testing code for this example is shared with other examples, XmUGridUnitTests::testPointFunctions.

\snippet xmsgrid/ugrid/XmUGrid.cpp snip_test_PointFunctions

## Example - Get the Points of a Cell {#Example_CellPointsLocations3d}
This example shows how to get the points of a cell. The xms::XmUGrid::CellPoints function takes one cell index and returns a vector of point indices. There is also a The xms::XmUGrid::CellLocations function that returns the locations (Pt3d) of those points.  Functionality is shared between 2d and 3d UGrids. The testing code for this example is shared with other examples, XmUGridUnitTests::testCellFunctions.

## Example - Get the Type of a Cell {#Example_CellType3d}
This example shows how to get the type of a cell. The xms::XmUGrid::CellType function takes one cell index and returns the cell type. Functionality is shared between 2d and 3d UGrids. The testing code for this example is shared with other examples, XmUGridUnitTests::testCellFunctions.

## Example - Get the Number of the Cells of each Dimension in a UGrid {#Example_DimensionCounts3d}
This example shows how to get the count of the dimensions of cells used in a UGrid. The xms::XmUGrid::DimensionCounts function returns a vector with the number of cells with zero dimensions in the zero index, number of cells with one dimension in the first index, number of cells with two dimensions in the second index, and the number of cells with three dimensions in the third index. Functionality is shared between 2d and 3d UGrids. The testing code for this example is shared with other examples, XmUGridUnitTests::testCellFunctions.

## Example - Get the Dimension of a Cell {#Example_CellDimension3d}
This example shows how to get the dimension of a cell. The xms::XmUGrid::CellDimension function takes one cell index and returns the cell dimension as an integer value. Functionality is shared between 2d and 3d UGrids. The testing code for this example is shared with other examples, XmUGridUnitTests::testCellFunctions.

\snippet xmsgrid/ugrid/XmUGrid.cpp snip_test_CellFunctions

## Example - Get the Cellstream of the UGrid {#Example_Cellstream3d}
This example shows how to get the entire cellstream of the UGrid. The xms::XmUGrid::Cellstream function returns a vector of integers that is the cellstream. Functionality is shared between 2d and 3d UGrids. The testing code for this example is shared with other examples, XmUGridUnitTests::testCellstreamFunctions.

## Example - Get a Single Cellstream for One Cell {#Example_CellCellstream3d}
This example shows how to get the cellstream for just one cell. The xms::XmUGrid::CellCellstream function takes a cell index and a vector of integers that is the cellstream for the specified cell passed in by reference. Functionality is shared between 2d and 3d UGrids. The testing code for this example is shared with other examples, XmUGridUnitTests::testCellstreamFunctions.

\snippet xmsgrid/ugrid/XmUGrid.cpp snip_test_CellstreamFunctions

## Example - Get the Cells Adjacent to a Given Cell {#Example_CellAdjacentCells3d}
This example shows how to get the cells that also use any of the points of a given cell. Cells are adjacent if they share at least one point. The xms::XmUGrid::CellAdjacentCells function takes a cell index and returns a vector of cell indices. Functionality is shared between 2d and 3d UGrids. The testing code for this example is XmUGridUnitTests::testCellAdjacentCells.

\snippet xmsgrid/ugrid/XmUGrid.cpp snip_test_CellAdjacentCells

## Example - Get a Plan View Polygon {#Example_CellPlanViewPolygon3d}
This example shows how to get a plan view polygon. This function first assumes that the shape is prismatic (or that the sides of the shape are vertical) and it gathers the points of the vertical sides. If this method fails, it builds a convex hull of the unique points of the shape. If the second method is employed, concave shapes will result in a convex polygon. The xms::XmUGrid::CellPlanViewPolygon function takes a cell index and a vector of Pt3d to contain on return the locations of the points of the plan view polygon and returns whether the operation was succesful. The testing code for this example is XmUGridUnitTests::testCellPlanViewPolygon.

\snippet xmsgrid/ugrid/XmUGrid.cpp snip_test_CellPlanViewPolygon

## Example - Get Number of Cell Edges {#Example_CellEdgeCount3d}
This example shows how to get the number of cell edges in a cell. The xms::XmUGrid::CellEdgeCount function takes a cell index and returns the number of edges as an int. Functionality is shared between 2d and 3d UGrids. The testing code for this example is XmUGridUnitTests::testCellEdgeCount

## Example Get Cell Edge Adjacent Cells {#Example_CellEdgeAdjacentCells3d}
This example shows how to get all cells which share the specified edge with a cell. The xms::XmUGrid::CellEdgeAdjacentCells function takes a cell index and an edge index and returns a vector of cell indices. Functionality is shared between 2d and 3d UGrids. The testing code for this example is shared with other examples, XmUGridUnitTests::testCellEdgeAdjacentCellFunctions

\snippet xmsgrid/ugrid/XmUGrid.cpp snip_test_CellEdgeAdjacentCellFunctions

## Example Get Edges Associated with a Cell {#Example_CellEdges3d}
This example shows how to get edges associated with a cell. The xms::XmUGrid::CellEdges function takes a cell index and returns a vector of XmEdge (each of with contains a pairs of integers which are point indices). Functionality is shared between 2d and 3d UGrids. The testing code for this example is XmUGridUnitTests::testCellEdges

\snippet xmsgrid/ugrid/XmUGrid.cpp snip_test_CellEdges

## Example Get Number of Faces for a Cell {#Example_Cell3dFaceCount3d}
This example shows how to get the number of faces that a cell has. The xms::XmUGrid::Cell3dFaceCount function takes a cell index and returns the number of cell faces associated with it as an integer. The testing code for this example is XmUGridUnitTests::testCell3dFaceFunctions

\snippet xmsgrid/ugrid/XmUGrid.cpp snip_test_GetNumberOfCellFaces

## Example Get Cell Face {#Example_Cell3dFacePoints3d}
This example shows how to get a cell face. The xms::XmUGrid::Cell3dFacePoints function takes a cell index and a face index and returns a vector of point indices which define the face in counter-clockwise direction. The testing code for this example is shared with another example, XmUGridUnitTests::testCell3dFaceFunctions.

## Example Get Faces of Cell {#Example_Cell3dFacesPoints3d}
This example shows how to get all the faces of a cell. The xms::XmUGrid::Cell3dFacesPoints function takes a cell index and returns a vector of vectors (one for each face, of point indices which define that face, in counter-clockwise direction as viewed from outside). The testing code for this example is shared with another example, XmUGridUnitTests::testCell3dFaceFunctions.

\snippet xmsgrid/ugrid/XmUGrid.cpp snip_test_Cell3dFaceFunctions

## Example Get Cell Face Ajacent Cell {#Example_Cell3dFaceAdjacentCell3d}
This example shows how to get the cell, if any, which shares a face with a specified cell and face. The xms::XmUGrid::Cell3dFaceAdjacentCell function takes a cell index and a face index and return the cell index of the cell which shares the face, or -1 if there are none. There is an overload which takes a cell index, a face index, an integer which it will set to be the cell index if any of the adjacent cell, and an integer which it will set to be the index of the face of the adjacent cell which it shares with the specified cell if any, and returns true if there is a cell with a shared face. The testing code for this example is XmUGridUnitTests::testGetCellFaceNeighbor.

\snippet xmsgrid/ugrid/XmUGrid.cpp snip_test_Cell3dFaceAdjacentCell

