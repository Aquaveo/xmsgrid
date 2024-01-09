"""Pure Python wrapper for GmMultiPolyIntersector class."""

__copyright__ = "(C) Copyright Aquaveo 2023"
__license__ = "See accompanying file LICENSE or https://aquaveo.com/bsd/license.txt"

# 1. Standard python modules

# 2. Third party modules

# 3. Aquaveo modules

# 4. Local modules
from .._xmsgrid.geometry import GmMultiPolyIntersector


class MultiPolyIntersector(object):
    """Intersects a line segment with any number of polygons in 2D and returns the polygons in order with t values."""

    def __init__(self, points, polys, starting_id=1, query='covered_by', **kwargs) -> None:
        """Constructor.

        Args:
            points (list): The points that make up the polygon.
            polys (list): 0-based indexes into a_points array to define polygons. The first point is NOT repeated as
             the last point.
            starting_id (int): If the polygon IDs should start at something other than 1, specify the starting value.
            query (str): The query to use ('covered_by', 'intersects')
            **kwargs (dict): Generic keyword arguments
        """
        if 'instance' not in kwargs:
            if points is None:
                raise ValueError('points is a required argument.')
            if polys is None:
                raise ValueError('polys is a required argument.')
            if query not in {'covered_by', 'intersects'}:
                raise ValueError('query must be either "covered_by" or "intersects".')
            self._instance = GmMultiPolyIntersector(points, polys, starting_id, query)
        else:
            if not isinstance(kwargs['instance'], GmMultiPolyIntersector):
                raise ValueError('"instance" must be of type _xmsgrid.geometry.GmMultiPolyIntersector')
            self._instance = kwargs['instance']

    def __eq__(self, other) -> bool:
        """Equality operator.

        Args:
            other (MultiPolyIntersector): MultiPolyIntersector to compare

        Returns:
            bool: True if MultiPolyIntersector are equal
        """
        other_instance = getattr(other, '_instance', None)
        if not other_instance or not isinstance(other_instance, GmMultiPolyIntersector):
            print("not instance or no value")
            return False
        return other_instance == self._instance

    def __ne__(self, other) -> bool:
        """Equality operator.

        Args:
            other (MultiPolyIntersector): MultiPolyIntersector to compare

        Returns:
            bool: True if MultiPolyIntersector are not equal
        """
        result = self.__eq__(other)
        return not result

    # Why define these?
    # def __repr__(self) -> str:
    #     """Returns a string representation of the MultiPolyIntersector."""
    #     return "<xms.grid.geometry.MultiPolyIntersector>"
    #
    # def __str__(self) -> str:
    #     """Returns a string representation of the MultiPolyIntersector."""
    #     return "<xms.grid.geometry.MultiPolyIntersector>"

    def traverse_line_segment(self, pt1, pt2) -> tuple[tuple[int], tuple[float], tuple[tuple[float, float, float]]]:
        """Intersect segment with polys and return intersected polys, t-values, and points.

        Args:
            pt1 (iterable): 1st point defining a line segment.
            pt2 (iterable): 2nd point defining a line segment.

        Returns:
            tuple containing:
            - Ids of polygons intersected by line segment. Can be zero or 1 based depending on starting_id.
            - Values from 0.0 to 1.0 representing where on the line segment the intersection with the polygon occurs.
            If there are any t values there are always at least 2 and all represent where the line enters the polygon,
            except the last which represents where it exited. There would therefore be one more t value than poly id
            but we make the sizes equal by always making the last poly id -1.
            - Intersection points.
        """
        return self._instance.TraverseLineSegment(pt1, pt2)

    def polygon_from_point(self, point) -> int:
        """Returns the ID of the polygon containing the point.

        Args:
            point (iterable): The point.

        Returns:
            The polygon id.
        """
        return self._instance.PolygonFromPoint(point)
