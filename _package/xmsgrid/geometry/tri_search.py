from .._xmsgrid.geometry import GmTriSearch

class TriSearch(object):
    """

    """

    def __init__(self, points=None, triangles=None, **kwargs):
        if 'instance' not in kwargs:
            if not points:
                raise ValueError('points is a required arguments.')
            if not triangles:
                raise ValueError('triangles is a required argument.')
            self._instance = GmTriSearch(points, triangles)
        else:
            self._instance = kwargs['instance']

    def __repr__(self):
        return "<xmsgrid.geometry.TriSearch>"

    def __str__(self):
        return "<xmsgrid.geometry.TriSearch>"

    @property
    def point_activity(self):
        """Activity of the points"""
        return self._instance.GetPtActivity()

    @point_activity.setter
    def point_activity(self, activity):
        self._instance.SetPtActivity(activity)

    @property
    def triangle_activity(self):
        """Activity of the triangles"""
        return self._instance.GetTriActivity()

    @triangle_activity.setter
    def triangle_activity(self, activity):
        self._instance.SetTriActivity(activity)

    @property
    def points(self):
        """Points in the search"""
        return self._instance.GetPoints()

    @property
    def triangles(self):
        """Triangles in the search"""
        return self._instance.GetTriangles()

    def triangle_containing_point(self, point):
        """
        Find the triangle containing the point

        Args:
            point (iterable): The location used to find the triangle

        Returns:
            The index of the triangle containing point
        """
        return self._instance.TriContainingPt(point)

    def triangle_envelops_containing_point(self, point):
        """
        Find all triangles whose envelope contains the point.

        Args:
            point (iterable): The point to search for

        Returns:
            The indices to triangles whose envelope contains the point
        """
        return self._instance.TriEnvelopsContainingPt(point)

    def triangle_envelopes_overlap(self, min_point, max_point):
        """
        Find all triangles whose envelope overlaps the envelope defined by min and max.

        Args:
            min_point: min x,y location of the box
            max_point: max x,y location of the box

        Returns:
            The indices to triangles whose envelope intersects with the input envelope.
        """
        return self._instance.TriEnvelopesOverlap(min_point, max_point)

    def interp_weights(self, point):
        """
        Use the stored triangles to get interpolation weights for a point.

        Args:
            point (iterable): location that is interpolated to.

        Returns:
            A tuple of a flag if it was successful, triangle point indices and triangle point weights.
        """
        return self._instance.InterpWeights(point)

    def interp_weights_triangle_index(self, point):
        """

        Args:
            point (iterable): location that is interpolated to.

        Returns:
            A tuple of a flag if it was successful, triangle containing the point, triangle point indices and triangle point weights or None if the point is not any triangle
        """
        return self._instance.InterpWeightsTriangleIdx(point)
