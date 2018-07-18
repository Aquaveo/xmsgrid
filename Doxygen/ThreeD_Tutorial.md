# 3D UGrid Tutorial

\tableofcontents
# 3D UGrid Tutorial {#ThreeD_Tutorial}

## Introduction {#Intro_3Ugrid}
The purpose of this tutorial is to provide explanation on how to use xmsgrid to create three dimensional unstructured grids, or UGrids. A UGrid has points and cells defined using those points. There are many different kinds of cells available, but this tutorial will focus on the 3-dimensional cells, namely: tetrahedron, voxel, hexahedron, wedge, pyramid, and polyhedron.

## Example - Defining Ugrid Cells {#Example_DefiningA3dUGridCell}
Supported 3D grid cells include: tetrahedron (10), voxel (11), hexahedron (12), wedge (13), pyramid (14), and polyhedron (42). A cell is defined with the number declaration of the shape (10, 11, 12, 13, 14, and 42 respectively as defined by the enumeration xms::XmUGridCellType), then the number of points, followed by the point indices.  The cell definitions mirror VTK cell definitions which are available on page 9 of VTK File Formats for VTK version 4.2 at https://www.vtk.org/wp-content/uploads/2015/04/file-formats.pdf. 

A tetrahedron (10) has 4 points. See the illustration in the VTK file Format pdf referenced above on page 9 for a VTK_TETRA for point order. A cell stream example for a tetrahedron is: 10, 4, 0, 1, 2, 3.

A voxel (11) has 8 orthogonially defined points. See the illustration in the VTK file Format pdf referenced above on page 9 for a VTK_VOXEL for point order. A cell stream example for a voxel is: 11, 8, 0, 1, 2, 3, 4, 5, 6, 7.

A hexahedron (12) has 8 points. See the illustration in the VTK file Format pdf referenced above on page 9 for a VTK_HEXAHEDRON for point order. A cell stream example for a hexahedron is: 12, 8, 0, 1, 2, 3, 4, 5, 6, 7.

A wedge (13) has 6 points. See the illustration in the VTK file Format pdf referenced above on page 9 for a VTK_WEDGE for point order. A cell stream example for a wedge is: 13, 6, 0, 1, 2, 3, 4, 5.

A pyramid (14) has 5 points. See the illustration in the VTK file Format pdf referenced above on page 9 for a VTK_PYRAMID for point order. A cell stream example for a pyramid is: 14, 5, 0, 1, 2, 3, 4.

A polyhedron (42) does not a have a defined number of points. A polyhedron cell stream has the following format: The cell type, number of faces, and then repeated for each face the number of points in the face followed by the points in the face declared in a counter-clockwise direction. A cell stream example for a polyhedron is: 42, 6, 4, 10, 13, 12, 11, 4, 10, 11, 15, 16, 4, 11, 12, 16, 15, 4, 12, 13, 17, 16, 4, 13, 10, 14, 17, 4, 14, 15, 16, 17.

The testing code for this example is XmUGridUnitTests::TEST_XmUGrid3DLinear.
\snippet xmsgrid/ugrid/XmUGrid.cpp snip_test_3DShapes

## Example - Creating a New 3D UGrid With Data {#Example_New_With_Data_3d}
This example shows how to create a new 3D UGrid with the overloaded New function which directly sets the data as it constructs the grid, using the static function xms::XmUGrid::New(const VecPt3d& a_points, const VecInt& a_cellStream). Functionality is shared between 2d and 3d UGrids. The testing code for this example is XmUGridUnitTests::testGetSetPoint.

\snippet xmsgrid/ugrid/XmUGrid.cpp snip_test_NewOperator

## Example - Creating a New 3D UGrid {#Example_New3d}
This example shows how to create a new 3D UGrid. XmUGrid is an abstract class that cannot be instantiated. The static function xms::XmUGrid::New() is the only method to obtain a Boost Shared Pointer to an instance of XmUGrid. Points and Cellstream may be passed to New to initialize the UGrid with data but this is not required. Functionality is shared between 2d and 3d UGrids. The testing code for this example is XmUGridUnitTests::testUGridStreams.

## Example - Setting the UGrid Points {#Example_SetPoints3d}
This example shows how to set all of the UGrid points using xms::XmUGridImpl::SetPoints. The Ugrid points cannot be added or removed individually, though they can be edited individually. The SetPoints function takes one argument, a vector of 3D points. It is reccomended that each point is unique to avoid unexpected behavior. Functionality is shared between 2d and 3d UGrids. The testing code for this example is the same as used for creating a new UGrid, XmUGridUnitTests::testUGridStreams.

## Example - Setting the UGrid Cell Stream {#Example_SetCellStream3d}
This example shows how to set the entire UGrid Cellstream using xms::XmUGridImpl::SetCellStream. Cellstreams are formatted as a stream of integers starting with the cell type as described by the enumeration XmUGridCellType, then the number of points in the cell, followed by a series of indices to points. The SetCellStream function takes one argument, a vector of integers formatted as previously described. Functionality is shared between 2d and 3d UGrids. The testing code for this example is the same as used for creating a new UGrid, XmUGridUnitTests::testUGridStreams.

\snippet xmsgrid/ugrid/XmUGrid.cpp snip_test_UGrid_Streams

## Example - Validating the Cellstream {#Example_ValidatingCellStream3d}
This example shows how to validate whether a given Cellstream is valid as previously defined. The xms::XmUGridImpl::ValidCellStream checks whether all cell types and point counts within the cellstream match up, but does not check for orientation or valid point positions. This function should not be relied on to catch all errors, but can be a basic check before setting the cellstream. The function takes one arguement, a cellstream containing one or more cells. Functionality is shared between 2d and 3d UGrids. The testing code for this example is XmUGridUnitTests::SetCellStream.

\snippet xmsgrid/ugrid/XmUGrid.cpp snip_test_SetCellStream

## Example - Get Number Of Points {#Example_GetNumberOfPoints3d}
This example shows how to return the number of points contained in a UGrid. The xms::XmUGridImpl::GetNumberOfPoints function returns the number of points in the UGrid. Functionality is shared between 2d and 3d UGrids. The testing code for this example is shared with other examples, XmUGridUnitTests::TestPointFunctions.

## Example - Get Points {#Example_GetPoints3d}
This example shows how to get all points contained within the XmUGrid. The xms::XmUGridImpl::GetPoints function returns a vector of Pt3d's. Functionality is shared between 2d and 3d UGrids. The testing code for this example is shared with other examples, XmUGridUnitTests::TestPointFunctions.

## Example - Get Point {#Example_GetPoint3d}
This example shows how to get a specific point given a point index. The xms::XmUGridImpl::GetPoint function returns the Pt3d of the point at the specified index. Functionality is shared between 2d and 3d UGrids. The testing code for this example is shared with other examples, XmUGridUnitTests::TestPointFunctions.

## Example - Set Point {#Example_SetPoint3d}
This example shows how to set a specific point given a point index. The xms::XmUGridImpl::SetPoint function takes a point index and a Pt3d as arguements and returns whether the operation was succesful. The function may fail and return false if the change would cause any edges to cross. Functionality is shared between 2d and 3d UGrids. The testing code for this example is shared with other examples, XmUGridUnitTests::TestPointFunctions.

## Example - Get Points from Point Indices {#Example_GetPointsFromPointIdxs3d}
This example shows how to convert a vector of point indices into a vector of Pt3d's. The xms::XmUGridImpl::GetPointsFromPointIdxs function takes a vector of Point Indices as an arguement and returns a vector of corresponding Pt3d's as a result. Functionality is shared between 2d and 3d UGrids. The testing code for this example is shared with other examples, XmUGridUnitTests::TestPointFunctions.

## Example - Get Extents of UGrid {#Example_GetExtents3d}
This example shows how to get the extents of a UGrid. The xms::XmUGridImpl::GetExtents function takes two 3D points as arguements describing the minimum and maximum extent that the points of the UGrid cover. These arguments will be set by the funtion. Functionality is shared between 2d and 3d UGrids. The testing code for this example is shared with other examples, XmUGridUnitTests::TestPointFunctions.

## Example - Get Cells Associated with a Point {#Example_GetPointCells3d}
This example shows how to the cells associated with a single point. The xms::XmUGridImpl::GetPointCells function takes one point index as an arguement and returns a vector of point indices. Functionality is shared between 2d and 3d UGrids. The testing code for this example is shared with other examples, XmUGridUnitTests::TestPointFunctions.

## Example - Get the Cells that Share the Same Point or Points {#Example_GetCommonCells3d}
This example shows how to the cells that share the same point or points. The xms::XmUGridImpl::GetCommonCells function takes a vector of point indices as an arguement and returns a vector of cell indices. Functionality is shared between 2d and 3d UGrids. The testing code for this example is shared with other examples, XmUGridUnitTests::TestPointFunctions.

\snippet xmsgrid/ugrid/XmUGrid.cpp snip_test_PointFunctions

## Example - Get the Points of a Cell {#Example_GetPointsOfCell3d}
This example shows how to get the points of a cell. The xms::XmUGridImpl::GetPointsOfCell function takes one cell index and returns a vector of point indices. There is also an overloaded function that will take the vector of point indices as an argument passed by reference which returns whether the operation was successful. Functionality is shared between 2d and 3d UGrids. The testing code for this example is shared with other examples, XmUGridUnitTests::TestCellFunctions.

## Example - Get the Type of a Cell {#Example_GetCellType3d}
This example shows how to get the type of a cell. The xms::XmUGridImpl::GetCellType function takes one cell index and returns the cell type. Functionality is shared between 2d and 3d UGrids. The testing code for this example is shared with other examples, XmUGridUnitTests::TestCellFunctions.

## Example - Get the Count of the Dimensions of Cells used in a UGrid {#Example_GetDimensionCount3d}
This example shows how to get the count of the dimensions of cells used in a UGrid. The xms::XmUGridImpl::GetDimensionCount function returns a vector with the number of cells with zero dimensions in the zero index, number of cells with one dimension in the first index, number of cells with two dimensions in the second index, and the number of cells with three dimensions in the third index. Functionality is shared between 2d and 3d UGrids. The testing code for this example is shared with other examples, XmUGridUnitTests::TestCellFunctions.

## Example - Get the Dimension of a Cell {#Example_GetCellDimension3d}
This example shows how to get the dimension of a cell. The xms::XmUGridImpl::GetCellDimension function takes one cell index and returns the cell dimension as an integer value. Functionality is shared between 2d and 3d UGrids. The testing code for this example is shared with other examples, XmUGridUnitTests::TestCellFunctions.

\snippet xmsgrid/ugrid/XmUGrid.cpp snip_test_CellFunctions

## Example - Get the Cellstream of the UGrid {#Example_GetCellStream3d}
This example shows how to get the entire cellstream of the UGrid. The xms::XmUGridImpl::GetCellStream function returns a vector of integers that is the cell stream. Functionality is shared between 2d and 3d UGrids. The testing code for this example is shared with other examples, XmUGridUnitTests::testGetCellStreamFunctions.

## Example - Get a Single Cellstream for One Cell {#Example_GetSingleCellStream3d}
This example shows how to get a single cellstream for one cell. The xms::XmUGridImpl::GetSingleCellStream function takes a cell index and a vector of integers that is the cell stream for the specified cell passed in by reference. Functionality is shared between 2d and 3d UGrids. The testing code for this example is shared with other examples, XmUGridUnitTests::testGetCellStreamFunctions.

\snippet xmsgrid/ugrid/XmUGrid.cpp snip_test_GetCellStreamFunctions

## Example - Get the Cells that Neighbor a Given Cell {#Example_GetCellNeighbors3d}
This example shows how to get the cells that neighbor a given cell. Cells are neighbors if they share at least one point. The xms::XmUGridImpl::GetCellNeighbors function takes a cell index and returns a vector of cell indices. Functionality is shared between 2d and 3d UGrids. The testing code for this example is XmUGridUnitTests::testGetCellNeighbors.

\snippet xmsgrid/ugrid/XmUGrid.cpp snip_test_GetCellNeighbors

## Example - Get a Plan View Polygon {#Example_GetPlanViewPolygon3d}
This example shows how to get a plan view polygon. This function first assumes that the shape is prismatic (or that the sides of the shape are vertical) and it gathers the points of the vertical sides. If this method fails, it builds a convex hull of the unique points of the shape. If the second method is employed, concave shapes will result in a convex polygon. The xms::XmUGridImpl::GetPlanViewPolygon function takes a cell index and a vector of Pt3d which is the points of the plan view polygon and returns whether the operation was succesful. The testing code for this example is XmUGridUnitTests::testGetPlanViewPolygon.

\snippet xmsgrid/ugrid/XmUGrid.cpp snip_test_GetPlanViewPolygon

## Example - Get Number of Cell Edges {#Example_GetNumberOfCellEdges3d}
This example shows how to get the number of cell edges in a cell. The xms::XmUGridImpl::GetNumberOfCellEdges function takes a cell index and returns the number of edges as an int. Functionality is shared between 2d and 3d UGrids. The testing code for this example is XmUGridUnitTests::testGetCellEdgeFromEdgeIndex

## Example - Get Cell Edge from Edge Index {#Example_GetCellEdgeFromEdgeIndex3d}
This example shows how to get the cell edge from a given cell and edge index. The xms::XmUGridImpl::GetCellEdgeFromEdgeIndex function takes a cell index and an edge index and returns a pair of ints containing the point indices of the edge. Functionality is shared between 2d and 3d UGrids. The testing code for this example is shared with other examples, XmUGridUnitTests::testGetCellEdgeFromEdgeIndex

\snippet xmsgrid/ugrid/XmUGrid.cpp snip_test_GetCellEdgeFromEdgeIndex3D

## Example Get Adjacent Cells {#Example_GetAdjacentCells3d}
This example shows how to get all cells which share the specified edge with a cell. The xms::XmUGridImpl::GetAdjacentCells function takes a cell index and an edge index and returns a vector of cell indices. Functionality is shared between 2d and 3d UGrids. The testing code for this example is shared with other examples, XmUGridUnitTests::testGetAdjacentCellFunctions

## Example Get Adjacent Cells from Given Edge {#Example_GetAdjacentCellsFromAGivenEdge3d}
This example shows how to get all cells which contain a given edge. The xms::XmUGridImpl::GetAdjacentCellsFromGivenEdge function takes two point indices describing an edge and returns a vector of cell indices. There is also an overload which takes a pair of point indices describing an edge. Functionality is shared between 2d and 3d UGrids. The testing code for this example is shared with other examples, XmUGridUnitTests::testGetAdjacentCellFunctions

\snippet xmsgrid/ugrid/XmUGrid.cpp snip_test_GetAdjacentCellFunctions

## Example Get Edges Associated with a Point {#Example_GetEdgesFromPoint3d}
This example shows how to get edges associated with a point. The xms::XmUGridImpl::GetEdgesFromPoint function takes a point index, a vector of cell indices, and a vector of edge indices. The cell and edge indices will be set by the function. It will return whether it was successful. There are two overloads, the first takes a point index, a vector of cell indices, and a vector of edges defined as a pair of integers which are point indices. The second overload takes a point index, a vector of cell indices, and two vectors of edge point indexes. Functionality is shared between 2d and 3d UGrids. The testing code for this example is XmUGridUnitTests::testGetEdgesFromPoint

\snippet xmsgrid/ugrid/XmUGrid.cpp snip_test_GetEdgesFromPoint

## Example Get Edges Associated with a Cell {#Example_GetEdgesOfCell3d}
This example shows how to get edges associated with a cell. The xms::XmUGridImpl::GetEdgesOfCell function takes a cell index and returns a vector of pairs of integers which are point indices. Functionality is shared between 2d and 3d UGrids. The testing code for this example is XmUGridUnitTests::testGetEdgesFromPoint

\snippet xmsgrid/ugrid/XmUGrid.cpp snip_test_GetEdgesOfCell

## Example Get Number of Faces for a Cell {#Example_GetNumberOfFacesForCell}
This example shows how to get the number of faces that a cell has. The xms::XmUGridImpl::GetNumberOfCellFaces function takes a cell index and returns the number of cell faces associated with it as an integer. The testing code for this example is XmUGridUnitTests::testGetNumberOfCellEdges

\snippet xmsgrid/ugrid/XmUGrid.cpp snip_test_GetNumberOfCellFaces

## Example Get Cell Face {#Example_GetCellFace}
This example shows how to get a cell face. The xms::XmUGridImpl::GetCellFace function takes a cell index and a face index and returns a vector of point indices which define the face in counter-clockwise direction. The testing code for this example is shared with another example, XmUGridUnitTests::testGetFaces.

## Example Get Faces of Cell {#Example_GetFacesOfCell}
This example shows how to get all the faces of a cell. The xms::XmUGridImpl::GetFacesOfCell function takes a cell index and returns a two dimensional vector of point indices which define the faces in counter-clockwise direction. The testing code for this example is shared with another example, XmUGridUnitTests::testGetFaces.

\snippet xmsgrid/ugrid/XmUGrid.cpp snip_test_GetFaces

## Example GetFacesFromPoint {#Example_GetFacesFromPoint}
This example shows how to get all the faces associated with a point. The xms::XmUGridImpl::GetFacesFromPoint function takes in a point index and a vector of integers which it will set with the cell indices and a vector of integers which it will set with the face indices. The testing code for this example is XmUGridUnitTests::testGetFacesFromPoint

\snippet xmsgrid/ugrid/XmUGrid.cpp snip_test_GetFacesFromPoint

## Example Get Cell Face Neighbor {#Example_GetCellFaceNeighbor}
This example shows how to get the cell, if any, which shares a face with a specified cell and face. The xms::XmUGridImpl::GetCellFaceNeighbor function takes a cell index and a face index and return the cell index of the cell which shares the face, or negative 1 if there are none. There is an overload which takes a cell index, a face index, an integer which it will set to be the cell index if any of the neighboring cell, and an integer which it will set to be the face of the neighboring cell which it shares with the specified cell if any, and returns true if there is a cell with a shared face. The testing code for this example is XmUGridUnitTests::testGetCellFaceNeighbor.

\snippet xmsgrid/ugrid/XmUGrid.cpp snip_test_GetCellFaceNeighbor

