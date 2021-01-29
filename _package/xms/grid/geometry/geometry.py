from .. import _xmsgrid

geometry = _xmsgrid.geometry


def point_in_polygon_2d(polygon, point):
    """Check whether a point is inside, outside, or on a polygon.

    *DON'T* repeat the first point at the end of the polygon list.
    Points are represented as (x, y, z) triples.

    Args:
        polygon: A list of points describing the polygon.
                 Can be in clockwise or counterclockwise order.
        point: The point to test.

    Returns:
         1 if the point is inside the polygon.
         0 if the point is on the polygon.
         -1 if the point is outside the polygon.
    """
    return geometry.gmPointInPolygon2D(polygon, point)


def polygon_area_2d(polygon):
    """Compute the 2d planview projection of area of polygon.

    The last point should not be repeated.
    Points are represented as (x, y, z) triples.

    Args:
        polygon: A list of points defining the polygon.
                 CCW order gives positive areas, CW gives negative.
                 The last point should not be repeated.

    Returns:
         The area of the polygon.
    """
    return geometry.gmPolygonArea(polygon)


def get_tol_2d():
    """Get the global tolerance for 2d float operations.

    Value may not be meaningful if it has not been set yet.
    """
    return geometry.gmGetXyTol()


def set_tol_2d(value=1e-9):
    """Set the global tolerance for 2d float operations.

    Args:
        value: The value to set the tolerance to.
    """
    geometry.gmSetXyTol(value)


def on_line_2d(p1, p2, pt, tol=None):
    """Determines whether a point pt is on the line defined by p1 and p2.

    If p1 and p2 are equal within tol, this function may fail.
    Points are represented as (x, y, z) triples.

    Args:
        p1: First point defining a line.
        p2: Second point defining a line.
        pt: The point to test.
        tol: Tolerance for geometric comparison. If omitted, uses global tolerance according to get_tol_2d().

    Returns:
        True if the point is on the line passing through p1 and p2 within tolerance.
    """
    if tol is None:
        tol = get_tol_2d()
    return geometry.gmOnLineWithTol(p1, p2, pt, tol)


def inside_or_on_line_2d(p1, p2, reference_point, pt, tol=None):
    """Tests whether a point is on the same side of a line as a reference point, or on the line itself.

    Assumes reference_point is not on the line (within tol).
    Points are represented as (x, y, z) triples.

    Args:
        p1: The first point defining the line.
        p2: The second point defining the line.
        reference_point: A point on one side of the line.
        pt: Point to test.
        tol: Tolerance. If omitted, uses global tolerance according to get_tol_2d().

    Returns:
        A tuple (result, distance).
        result is True if pt is either on the line or on the same side as reference_point, or False otherwise.
        distance is how far away from the line pt is. It will be negative if pt is on the same side of the line as
        reference_point, or positive if pt is on the opposite side of the line.
    """
    if tol is None:
        tol = get_tol_2d()
    return geometry.gmInsideOrOnLineWithTol(p1, p2, reference_point, pt, tol)


def find_closest_pt_on_segment_2d(pt1, pt2, pt, tol=None):
    """Finds the closest point to another point on a line segment.

    Points are represented as (x, y, z) triples.

    Args:
        pt1: First point defining the line segment.
        pt2: Second point defining the line segment.
        pt: Point used to find closest point on the segment.
        tol: Tolerance. If omitted, uses global tolerance according to get_tol_2d().

    Returns:
        A tuple of (value, point).
        value is the parametric value along the line segment that is the location of point.
        point is an (x, y, z) tuple describing the closest point on the line segment to the parameter pt.
    """
    if tol is None:
        tol = get_tol_2d()
    return geometry.gmFindClosestPtOnSegment(pt1, pt2, pt, tol)


def pt_distance_along_segment_2d(pt1, pt2, pt, tol=None):
    """Finds the distance along a segment for the location closest to pt.

    Points are represented as (x, y, z) triples.

    Args:
        pt1: First point defining the line segment.
        pt2: Second point defining the line segment.
        pt: Point used to find the closest point on the segment.
        tol: Tolerance. If omitted, uses global tolerance according to get_tol_2d().

    Returns:
        Parametric value along the line segment that is the closest to pt.
    """
    if tol is None:
        tol = get_tol_2d()
    return geometry.gmPtDistanceAlongSegment(pt1, pt2, pt, tol)


def inside_of_line_2d(pt1, pt2, reference_point, pt, tol=None):
    """Tests whether a point is on the same side of a line as another point.

    Assumes reference_point is not on the line (within tol).
    Points are represented as (x, y, z) triples.

    Args:
        pt1: The first point defining the line.
        pt2: The second point defining the line.
        reference_point: A point on one side of the line.
        pt: Point to test.
        tol: Tolerance. If omitted, uses global tolerance according to get_tol_2d().

    Returns:
        True if pt is on the same side of the line segment as the reference point, else False.
    """
    if tol is None:
        tol = get_tol_2d()
    return geometry.gmInsideOfLineWithTol(pt1, pt2, reference_point, pt, tol)


def lines_intersect_2d(line1_pt1, line1_pt2, line2_pt1, line2_pt2):
    """Tests whether two line segments intersect.

    Points are represented as (x, y, z) triples.

    Args:
        line1_pt1: First point defining the first line segment.
        line1_pt2: Second point defining the first line segment.
        line2_pt1: First point defining the second line segment.
        line2_pt2: Second point defining the second line segment.

    Returns:
        True if the segments intersect, else False.
    """
    return geometry.gmLinesIntersect(line1_pt1, line1_pt2, line2_pt1, line2_pt2)


def equal_points_2d(p1, p2, tol=None):
    """Tests whether two points are equal to within tolerance.

    Points are represented as (x, y, z) triples.

    Args:
        p1: The first point.
        p2: The second point.
        tol: Tolerance. If omitted, uses global tolerance according to get_tol_2d().

    Returns:
        True if the points are equal to within tolerance, else False.
    """
    if tol is None:
        tol = get_tol_2d()
    return geometry.gmEqualPointsXY(p1, p2, tol)


def on_line_and_between_endpoints_2d(pt1, pt2, pt, tol=None):
    """Tests whether pt is on the line segment defined by pt1 and pt2.

    Points are represented as (x, y, z) triples.

    Args:
        pt1: First point defining the line segment.
        pt2: Second point defining the line segment.
        pt: the point to test.
        tol: Tolerance. If omitted, uses global tolerance according to get_tol_2d().

    Returns:
        True if the point is on the line segment, else False.
    """
    if tol is None:
        tol = get_tol_2d()
    return geometry.gmOnLineAndBetweenEndpointsWithTol(pt1, pt2, pt, tol)


def distance_to_line_segment_2d(pt1, pt2, pt, tol=None):
    """Computes the minimum distance between a point and a line segment.

    The closest point may be an endpoint. Checks to the tolerance passed in.
    Points are represented as (x, y, z) triples.

    Args:
        pt1: First point defining the line segment.
        pt2: Second point defining the line segment.
        pt: The point to find the distance to.
        tol: Tolerance. If omitted, uses global tolerance according to get_tol_2d().

    Returns:
        The minimum distance between pt and the line.
    """
    if tol is None:
        tol = get_tol_2d()
    return geometry.gm2DDistanceToLineSegmentWithTol(pt1, pt2, pt, tol)


def cross_2d(origin, a, b):
    """Computes the cross product of two points.

    Points are represented as (x, y, z) triples.

    Args:
        origin: The origin that the points are relative to.
        a: The first point to compute the cross product of.
        b: The second point to compute the cross product of.

    Returns:
        The cross product of the two points.
    """
    return geometry.gmCross2D(origin, a, b)


def distance_2d(pt1, pt2):
    """Compute the 2D distance between two 3D points.

    Points are represented as (x, y, z) triples.

    Args:
        pt1: The first point.
        pt2: The second point.

    Returns:
        The distance between the two points.
    """
    return geometry.gmXyDistance(pt1, pt2)


def compute_polygon_centroid_2d(polygon):
    """Computes the plan view centroid of a non-self-intersecting polygon.

    Points are represented as (x, y, z) triples.

    Args:
        polygon: A list of points defining the polygon.

    Returns:
        The point at the polygon's centroid.
    """
    return geometry.gmComputePolygonCentroid(polygon)


def distance_to_line_2d(pt1, pt2, pt, tol=None):
    """Get the closest distance from pt to the line defined by pt1 and pt2.

    Unlike distance_to_line_segment_2d, points outside the line segment
    defined by pt1 and pt2 will be considered when finding the closest
    distance to pt.
    Points are represented as (x, y, z) triples.

    Args:
        pt1: First point defining the line.
        pt2: Second point defining the line.
        pt: Point to find the distance for.
        tol: Tolerance. If omitted, uses global tolerance according to get_tol_2d().

    Returns:
        The minimum distance between pt and the line.
    """
    if tol is None:
        tol = get_tol_2d()
    return geometry.gm2DDistanceToLineWithTol(pt1, pt2, pt, tol)


def angle_between_edges_2d(endpoint1, common_point, endpoint2):
    """Compute the CCW angle (0 to 2pi) between two edges which share a point.

    Points are represented as (x, y, z) triples.

    Args:
        endpoint1: The un-shared endpoint of the first edge.
        common_point: The shared endpoint of the two edges.
        endpoint2: The un-shared endpoint of the second edge.

    Returns:
        The angle between the two edges.
    """
    return geometry.gmAngleBetweenEdges(endpoint1, common_point, endpoint2)

def calculate_celerity(period, depth, gravity):
    """Calculate the celerity at a node.

    Args:
        period: Period.
        depth: Depth.
        gravity: Gravity.

    Returns:
        The celerity at a node.
    """
    return geometry.gmCalculateCelerity(period, depth, gravity)

def calculate_wavelength(period, depth, gravity):
    """Calculate the wavelength at a node.

    Args:
        period: Period.
        depth: Depth.
        gravity: Gravity.

    Returns:
        The wavelength at a node.
    """
    return geometry.gmCalculateWavelength(period, depth, gravity)