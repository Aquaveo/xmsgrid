from .._xmsgrid.ugrid import XmUGrid


class UGrid(object):
    """Class for representing unstructured grid geometries

    """

    cell_type_enum = XmUGrid.ugrid_celltype_enum
    face_orientation_enum = XmUGrid.ugrid_faceorientation_enum

    def __init__(self, points=None, cellstream=None, **kwargs):
        if 'instance' not in kwargs:
            if points is None and cellstream is None:
                self._instance = XmUGrid()
            elif points is None:
                raise ValueError("Cannot create ugrid with cellstream and no points")
            elif cellstream is None:
                self._instance = XmUGrid(points, [])
            else:
                self._instance = XmUGrid(points, cellstream)
        else:
            self._instance = kwargs['instance']

    def __repr__(self):
        return "<UGrid - Number of Locations: {}, Number of Cells: {}, Extents: {}, Modified: {}>".format(
            self.point_count, self.cell_count, str(self.extents), str(self.modified)
        )

    def __str__(self):
        return "<UGrid - Number of Locations: {}, Number of Cells: {}, Extents: {}, Modified: {}>".format(
            self.point_count, self.cell_count, str(self.extents), str(self.modified)
        )

    @property
    def modified(self):
        """Flag if grid is modified"""
        return self._instance.GetModified()

    @property
    def point_count(self):
        """Point count for ugrid"""
        return self._instance.GetPointCount()

    @property
    def locations(self):
        """Point locations for ugrid"""
        return self._instance.GetLocations()

    @locations.setter
    def locations(self, _locations):
        self._instance.SetLocations(_locations)

    @property
    def cellstream(self):
        """Get cell stream vector for the entire UGrid"""
        return self._instance.GetCellstream()

    @cellstream.setter
    def cellstream(self, _cellstream):
        self._instance.SetCellstream(_cellstream)

    @property
    def extents(self):
        """Get extents of the entire UGrid"""
        return self._instance.GetExtents()

    @property
    def cell_count(self):
        """Get the number of cells in the UGrid"""
        return self._instance.GetCellCount()

    @property
    def dimension_counts(self):
        """Count all number of the cells with each dimension (0, 1, 2, 3)"""
        return self._instance.GetDimensionCounts()

    def set_unmodified(self):
        """
        Set grid as unmodified
        """
        self._instance.SetUnmodified()

    def use_cache(self, use_cache):
        """
        Flag if cache is being used

        Args:
            use_cache (bool): flag if cache is being used
        """
        self._instance.SetUseCache(use_cache)

    def get_point_location(self, point_idx):
        """
        Get location of a single point

        Args:
            point_idx (int): The index of the point

        Returns:
            A tuple point location of the point at point_idx
        """
        return self._instance.GetPointLocation(point_idx)

    def set_point_location(self, point_idx, location):
        """
        Set location of a single point

        Args:
            point_idx (int): The index of the point
            location:

        Returns:
            bool: True if successful
        """
        return self._instance.SetPointLocation(point_idx, location)

    def get_point_xy0(self, point_idx):
        """
        Get x, y location of a single point with z set to 0.0

        Args:
            point_idx (int): The index of the point

        Returns:
            A tuple point location of point_idx
        """
        return self._instance.GetPointXy0(point_idx)

    def get_points_locations(self, point_indices):
        """
        Get locations of multiple points

        Args:
            point_indices: The indices of the points

        Returns:
            List of tuple point locations of the point_indices
        """
        return self._instance.GetPointsLocations(point_indices)

    def get_point_adjacent_cells(self, point_idx):
        """
        Get cells adjacent to a point

        Args:
            point_idx (int): The index of the point to find adjacent cells of

        Returns:
            List of cell indices of cells adjacent to point_idx
        """
        return self._instance.GetPointAdjacentCells(point_idx)

    def get_points_adjacent_cells(self, point_indices):
        """
        Get adjacent cells common to a set of points

        Args:
            point_indices: The indices of the points to find adjacent cells of

        Returns:
            List of cell indices of cells adjacent to point_indices
        """
        return self._instance.GetPointsAdjacentCells(point_indices)

    def get_cells_adjacent_to_edge(self, point1, point2):
        """
        Get cells adjacent to both points

        Args:
            point1 (int): The index of the edge's first point
            point2 (int): The index of the edge's second point

        Returns:
            List of cell indices of cells adjacent to the edge defined by point1 and point2
        """
        return self._instance.GetPointsAdjacentCells(point1, point2)

    def is_valid_point_change(self, point_idx, new_position):
        """
        Determine whether adjacent cells are valid after a point is moved.

        Args:
            point_idx (int): The index of the point to check change
            new_position: Tuple location of the point's new location

        Returns:
            True if the point change is valid, False otherwise
        """
        return self._instance.IsValidPointChange(point_idx, new_position)

    def get_cell_point_count(self, cell_idx):
        """
        Get the number of cell points (including polyhedron)

        Args:
            cell_idx (int): The index of the cell

        Returns:
            Number of points in the cell
        """
        return self._instance.GetCellPointCount(cell_idx)

    def get_cell_points(self, cell_idx):
        """
        Get the points of a cell (including polyhedron)

        Args:
            cell_idx (int): The index of the cell

        Returns:
            List of point indices of the points that define the cell
        """
        return self._instance.GetCellPoints(cell_idx)

    def get_cell_locations(self, cell_idx):
        """
        Get locations of cell points

        Args:
            cell_idx (int): The index of the cell

        Returns:
            List of tuple point locations of the points that define the cell
        """
        return self._instance.GetCellLocations(cell_idx)

    def get_cell_type(self, cell_idx):
        """
        Get a cell's type

        Args:
            cell_idx (int): The index of the cell

        Returns:
            The cell's type enum
        """
        return self._instance.GetCellType(cell_idx)

    def get_cell_dimension(self, cell_idx):
        """
        Get the dimension of the specified cell

        Args:
            cell_idx (int): The index of the cell

        Returns:
            int: The number of dimensions of the cell
        """
        return self._instance.GetCellDimension(cell_idx)

    def get_cell_extents(self, cell_idx):
        """
        Get the extents of the given cell

        Args:
            cell_idx (int): The index of the cell

        Returns:
            Tuple of point locations of the minimum and maximum extents of the UGrid
        """
        return self._instance.GetCellExtents(cell_idx)

    def get_cell_cellstream(self, cell_idx):
        """
        Get cell stream list for a single cell

        Args:
            cell_idx (int): The index of the cell

        Returns:
            List of integers representing the cell - [cell type, number of points, pt_index_1, ..., pt_index_n]
        """
        return self._instance.GetCellCellstream(cell_idx)

    def get_cell_adjacent_cells(self, cell_idx):
        """
        Get the cells neighboring a cell (cells associated with any of it's points)

        Args:
            cell_idx (int): The index of the cell to find neighboring cells of

        Returns:
            List of integer cell indices of the cells adjacent to cell_idx
        """
        return self._instance.GetCellAdjacentCells(cell_idx)

    def get_cell_plan_view_polygon(self, cell_idx):
        """
        Get the plan view polygon of a specified cell

        Args:
            cell_idx (int): The index of the cell to get plan view polygon for

        Returns:
            Tuple of bool (False if plan view polygon could not be created) and a list of tuple point locations
                defining the plan view polygon.
        """
        return self._instance.GetCellPlanViewPolygon(cell_idx)

    def get_cell_centroid(self, cell_idx):
        """
        Get the centroid location of a cell

        Args:
            cell_idx (int): The index of the cell

        Returns:
            Tuple point location of the cell's center
        """
        return self._instance.GetCellCentroid(cell_idx)

    def get_cell_edge_count(self, cell_idx):
        """
        Get the number of edges for a cell

        Args:
            cell_idx (int): The index of the cell

        Returns:
            int: The number of edges in the cell
        """
        return self._instance.GetCellEdgeCount(cell_idx)

    def get_cell_edge(self, cell_idx, edge_idx):
        """
        Get a specified edge of a cell

        Args:
            cell_idx (int): The index of the cell containing the edge
            edge_idx (int): The edge index in the cell

        Returns:
            Tuple of point indices of the points that define the edge
        """
        return self._instance.GetCellEdge(cell_idx, edge_idx)

    def get_cell_edge_adjacent_cells(self, cell_idx, edge_idx):
        """
        Get the indices of the adjacent cells (that shares the same cell edge)

        Args:
            cell_idx (int): The index of the cell containing the edge
            edge_idx (int): The edge index in the cell

        Returns:
            List of cell indices of the cells adjacent to the edge
        """
        return self._instance.GetCellEdgeAdjacentCells(cell_idx, edge_idx)

    def get_cell_2d_edge_adjacent_cell(self, cell_idx, edge_idx):
        """
        Get the index of the adjacent cells (that shares the same cell edge)

        Args:
            cell_idx (int): The index of the cell containing the edge
            edge_idx (int): The edge index in the cell

        Returns:
            List of cell indices of the cells adjacent to the edge
        """
        return self._instance.GetCell2dEdgeAdjacentCell(cell_idx, edge_idx)

    def get_edge_adjacent_cells(self, edge):
        """
        Get the indices of the adjacent cells (that shares the same cell edge)

        Args:
            edge: Tuple of two point locations that define an edge

        Returns:
            List of cell indices that are adjacent to the edge
        """
        return self._instance.GetEdgeAdjacentCells(edge)

    def get_cell_edges(self, cell_idx):
        """
        Get the edges of a cell

        Args:
            cell_idx (int): The index of the cell

        Returns:
            List of 2-tuple of point indices that define the cell's edges
        """
        return self._instance.GetCellEdges(cell_idx)

    def get_point_adjacent_points(self, point_idx):
        """
        Given a point gets point indices attached to the point by an edge

        Args:
            point_idx (int): The index of the point to find adjacent point indices for

        Returns:
            List of point indices that are attached to point_idx by an edge
        """
        return self._instance.GetPointAdjacentPoints(point_idx)

    def get_point_adjacent_locations(self, point_idx):
        """
        Given a point gets point locations attached to the point by an edges

        Args:
            point_idx (int): The index of the point to find adjacent point locations for

        Returns:
            List of tuple point locations of points that are attached to point_idx by an edge
        """
        return self._instance.GetPointAdjacentLocations(point_idx)

    def get_cell_3d_face_count(self, cell_idx):
        """
        Get the number of cell faces for given cell

        Args:
            cell_idx (int): The index of the cell

        Returns:
            int: The number of cell faces in the cell
        """
        return self._instance.GetCell3dFaceCount(cell_idx)

    def get_cell_3d_face_point_count(self, cell_idx, face_idx):
        """
        Get the number of face points for a given cell and face

        Args:
            cell_idx (int): The index of the cell containing the face
            face_idx (int): The index of the face in the cell

        Returns:
            int: The number of points in the cell face
        """
        return self._instance.GetCell3dFacePointCount(cell_idx, face_idx)

    def get_cell_3d_face_points(self, cell_idx, face_idx):
        """
        Get the cell face for given cell and face index

        Args:
            cell_idx (int): The index of the cell containing the face
            face_idx (int): The index of the face in the cell

        Returns:
            List of point indices of the points that define the cell face
        """
        return self._instance.GetCell3dFacePoints(cell_idx, face_idx)

    def get_cell_3d_faces_points(self, cell_idx):
        """
        Get the faces of a cell

        Args:
            cell_idx (int): The index of the cell

        Returns:
            List of lists of point indices of the points that define the cell's faces
        """
        return self._instance.GetCell3dFacesPoints(cell_idx)

    def get_cell_3d_face_adjacent_cell(self, cell_idx, face_idx):
        """
        Get the cell face neighbors for given cell and face index

        Args:
            cell_idx (int): The index of the cell containing the face
            face_idx (int): The index of the face in the cell

        Returns:
            int: The cell index of the cell adjacent to the face_idx face of cell_idx
        """
        return self._instance.GetCell3dFaceAdjacentCell(cell_idx, face_idx)

    def get_cell_3d_face_orientation(self, cell_idx, face_idx):
        """
        Get the orientation of the face of a vertically prismatic cell

        Args:
            cell_idx (int): The index of the cell containing the face
            face_idx (int): The index of the face in the cell

        Returns:
            The face orientation enum of the face
        """
        return self._instance.GetCell3dFaceOrientation(cell_idx, face_idx)
