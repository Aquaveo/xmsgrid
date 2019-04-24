from .._xmsgrid.triangulate import TrTin

class Tin(object):
    """

    """

    def __init__(self, points=None, triangles=None, **kwargs):
        if 'instance' not in kwargs:
            if points is None:
                raise ValueError('points is a required arguments.')
            if triangles is None:
                self._instance = TrTin(points)
            else:
                self._instance = TrTin(points, triangles)
        else:
            self._instance = kwargs['instance']

    def __repr__(self):
        return "<Tin - Point Count: {}, Triangle Count: {}, Extents: {}>".format(
            self.number_of_points, self.number_of_triangles, self.extents
        )

    def __str__(self):
        return "<Tin - Point Count: {}, Triangle Count: {}, Extents: {}>".format(
            self.number_of_points, self.number_of_triangles, self.extents
        )

    @property
    def points(self):
        """Points in the tin"""
        return self._instance.Points

    @points.setter
    def points(self, _points):
        self._instance.SetPoints(_points)

    @property
    def triangles(self):
        """Triangles defining the tin"""
        return self._instance.Triangles

    @triangles.setter
    def triangles(self, _triangles):
        self._instance.SetTriangles(_triangles)

    @property
    def triangles_adjacent_to_points(self):
        """Triangles adjacent to points"""
        return self._instance.TrianglesAdjacentToPoints

    @triangles_adjacent_to_points.setter
    def triangles_adjacent_to_points(self, _triangles_adjacent_to_points):
        self._instance.SetTrianglesAdjacentToPoints(_triangles_adjacent_to_points)

    @property
    def number_of_points(self):
        """Number of points in the tin"""
        return self._instance.NumPoints

    @property
    def number_of_triangles(self):
        """Number of triangles in the tin"""
        return self._instance.NumTriangles

    @property
    def boundary_points(self):
        """Indices of all points on any boundary, in no particular order"""
        return self._instance.GetBoundaryPoints()

    @property
    def boundary_polys(self):
        """
        Exterior boundary and all interior voids as polygons of 0-based point indices. First point is not
        repeated as the last point.
        """
        return self._instance.GetBoundaryPolys()

    @property
    def extents(self):
        """
        The extents of the tin
        """
        return self._instance.GetExtents()

    def set_geometry(self, points, triangles, triangles_adjacent_to_points):
        """
        Set the geomoetry of the tin

        Args:
            points: Points in tin
            triangles: Triangles defining tin
            triangles_adjacent_to_points: Triangles adjacent to points
        """
        self._instance.SetGeometry(points, triangles, triangles_adjacent_to_points)

    def triangulate(self):
        """
        Triangulate the tin
        """
        self._instance.Triangulate()

    def triangle_from_edge(self, point1,  point2):
        """
        Finds the triangle with the edge defined by an edge

        Args:
            point1: first point of edge
            point2: second point of edge

        Returns:
            Triangle from an edge
        """
        return self._instance.TriangleFromEdge(point1,  point2)
    
    def triangle_adjacent_to_edge(self, point1,  point2):
        """
        Gives triangle on the right side of the edge.

        Args:
            point1: first point of the edge
            point2: second point of the edge

        Returns:
            The triangle adjacent to the edge.
        """
        return self._instance.TriangleAdjacentToEdge(point1,  point2)
    
    def local_index(self, triangle,  point):
        """
        Returns index (0-2) of point within triangle given global index.

        Args:
            triangle: triangle index
            point: global point index

        Returns:
            local index of the point in the triangle, or None if it is not part of the triangle
        """
        return self._instance.LocalIndex(triangle,  point)
    
    def global_index(self, triangle_idx,  local_point):
        """
        Returns the global index of a point given the local index and a triangle

        Args:
            triangle_idx: triangle to search
            local_point: local index

        Returns:
            global index of local_point in triangle_idx
        """
        return self._instance.GlobalIndex(triangle_idx,  local_point)
    
    def vertices_are_adjacent(self, point1,  point2):
        """
        Check if vertices form an edge of a triangle

        Args:
            point1: first point index
            point2: second point index

        Returns:
            True if points form a triangle edge, False otherwise.
        """
        return self._instance.VerticesAreAdjacent(point1,  point2)
    
    def common_edge_index(self, triangle,  adjacent_triangle):
        """
        Find common edge between triangle and neighbor

        Args:
            triangle: triangle index
            adjacent_triangle: adjacent triangle index

        Returns:
            local index of the edge between the triange and adjacent_triangle if it exists, None otherwise.
        """
        return self._instance.CommonEdgeIndex(triangle,  adjacent_triangle)
    
    def adjacent_triangle(self, triangle_index,  edge_idx):
        """
        Find the adjacent triangle from a triangle index and an edge

        Args:
            triangle_index: index of the triangle
            edge_idx: index of the edge

        Returns:
            The triangle adjance to the triangle at the index or None if there isn't one
        """
        return self._instance.AdjacentTriangle(triangle_index,  edge_idx)
    
    def triangle_centroid(self, triangle):
        """
        Calculate and return the centroid of a triangle.

        Args:
            triangle (int): Triangle index (0-based).

        Returns:
            The centroid
        """
        return self._instance.TriangleCentroid(triangle)
    
    def triangle_area(self, triangle):
        """
        Calculate and return the area of a triangle.

        Args:
            triangle (int): Triangle index (0-based).

        Returns:
            The area
        """
        return self._instance.TriangleArea(triangle)
    
    def next_boundary_point(self, point):
        """
        Get the next point CW from point on the boundary. CCW if in an inside hole.

        Args:
            point (int): The starting point

        Returns:
            The point index or None if not found
        """
        return self._instance.NextBoundaryPoint(point)
    
    def previous_boundary_point(self, point):
        """
        Get the previous point CCW from point on the boundary. CW if in an inside hole.

        Args:
            point (int): The starting point

        Returns:
            The point index or None if not found
        """
        return self._instance.PreviousBoundaryPoint(point)
    
    def export_tin_file(self, file_name):
        """
        Export in the .tin file format.

        Args:
            file_name (str): a file to write the tin to
        """
        self._instance.ExportTinFile(file_name)

    # Modifiers
    def swap_edge(self, triangle_a,  triangle_b,  check_angle=True):
        """
        Swap edges if triangles combine to form convex quad.

        Args:
            triangle_a: First triangle
            triangle_b: Second triangle
            check_angle: Dont swap very thin triangles

        Returns:
            True if successful False otherwise
        """
        return self._instance.SwapEdge(triangle_a,  triangle_b,  check_angle)
    
    def delete_triangles(self,  triangles):
        """
        Delete a list of triangles, update and renumber.

        Args:
            triangles: Triangle to be deleted
        """
        self._instance.DeleteTriangles(triangles)
    
    def delete_points(self,  points):
        """
        Delete a list of points, update and renumber.

        Args:
            points: Points to be deleted
        """
        self._instance.DeletePoints(points)
    
    def optimize_triangulation(self):
        """
        Swaps triangle edges until they are a Delauney triangulation.

        Returns:
            True if modified, False otherwise
        """
        return self._instance.OptimizeTriangulation()
    
    def remove_long_thin_triangles_on_perimeter(self,  ratio):
        """
        Removes long thin triangles on the boundary of the tin.

        Args:
            ratio: The ratio of one edge length compared to the sum of the other two edge lengths.  If the length ratio of a triangle is greater then or equal to this given ratio, the triangle is deleted.

        Returns:
            True if successful, False otherwise
        """
        return self._instance.RemoveLongThinTrianglesOnPerimeter(ratio)
    
    def build_triangles_adjacent_to_points(self):
        """
        Build array of triangles adjacent to points.
        """
        return self._instance.BuildTrisAdjToPts()  # Triangles adjacent to points
    
    def clear(self):
        """
        Clear the tin of all points, triangles, and triangles adjacent to points.
        """
        return self._instance.Clear()