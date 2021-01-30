import math
import unittest

from xms.grid.geometry import geometry


class TestGeometry(unittest.TestCase):
    """Tests for geometry module."""

    def test_point_in_polygon_2d(self):
        """Tests point_in_polygon_2d."""
        star = [(2, 6), (2.5, 4), (4, 4), (3, 3), (3.5, 1),
                (2, 2.5), (0.5, 1), (1, 3), (0, 4), (1.5, 4)]

        # Test a point near the center of the star
        central = (2, 3)
        self.assertEqual(1, geometry.point_in_polygon_2d(star, central))

        # Test a point near the point of the star
        point = (3.25, 1.75)
        self.assertEqual(1, geometry.point_in_polygon_2d(star, point))

        # Test a point that is a vertex of the polygon
        vertex = (0, 4)
        self.assertEqual(0, geometry.point_in_polygon_2d(star, vertex))

        # Test a point on the edge of the polygon
        edge = (1, 4)
        self.assertEqual(0, geometry.point_in_polygon_2d(star, edge))

        # Test a point between the star's points
        point_inverse = (2, 1.5)
        self.assertEqual(-1, geometry.point_in_polygon_2d(star, point_inverse))

        # Test a point that is well outside the star
        outside = (5, 5)
        self.assertEqual(-1, geometry.point_in_polygon_2d(star, outside))

    def test_polygon_area_2d(self):
        """Tests polygon_area_2d."""
        polygon = [(0, 0), (4, 0), (4, 4), (0, 4)]
        self.assertEqual(16, geometry.polygon_area_2d(polygon))

    def test_tol_2d(self):
        """Tests tol_2d."""
        geometry.set_tol_2d(77)
        self.assertEqual(77, geometry.get_tol_2d())

        geometry.set_tol_2d(1e-9)
        self.assertEqual(1e-9, geometry.get_tol_2d())

    def test_on_line_2d(self):
        """Tests on_line_2d."""
        p1 = (1, 1)
        p2 = (2, 2)

        self.assertTrue(geometry.on_line_2d(p1, p2, (3, 3), 0.001))
        self.assertFalse(geometry.on_line_2d(p1, p2, (3, 7), 0.001))

    def test_inside_or_on_line_2d(self):
        """Tests inside_or_on_line_2d."""
        p1 = (1, 1)
        p2 = (3, 3)
        in_point = (1, 2)
        tol = 0.1

        (inside, distance) = geometry.inside_or_on_line_2d(p1, p2, in_point, (2, 2), tol)
        self.assertTrue(inside)

        (inside, distance) = geometry.inside_or_on_line_2d(p1, p2, in_point, (1.5, 2), tol)
        self.assertTrue(inside)

        (inside, distance) = geometry.inside_or_on_line_2d(p1, p2, in_point, (0.5, -0.5), tol)
        self.assertFalse(inside)

    def test_find_closest_pt_on_segment_2d(self):
        """Tests find_closest_pt_on_segment_2d."""
        pt1 = (1, 1)
        pt2 = (3, 3)
        pt = (1, 2)

        (value, point) = geometry.find_closest_pt_on_segment_2d(pt1, pt2, pt, 0.01)
        self.assertEqual((1.5, 1.5, 0), point)

    def test_pt_distance_along_segment_2d(self):
        """Tests pt_distance_along_segment_2d."""
        pt1 = (1, 1)
        pt2 = (3, 3)
        pt = (1, 2)

        distance = geometry.pt_distance_along_segment_2d(pt1, pt2, pt, 0.01)
        self.assertEqual(0.25, distance)

    def test_inside_of_line_2d(self):
        """Tests inside_of_line_2d."""
        pt1 = (1, 1)
        pt2 = (3, 3)
        opposite = (1, -1)

        self.assertFalse(geometry.inside_of_line_2d(pt1, pt2, opposite, (1, 1.5), 0.01))
        self.assertTrue(geometry.inside_of_line_2d(pt1, pt2, opposite, (1.5, -1.5), 0.01))

    def test_lines_intersect_2d(self):
        """Tests lines_intersect_2d."""
        pt11 = (1, 1)
        pt12 = (2, 2)
        pt21 = (0, 2)
        pt22 = (2, 0)
        pt31 = (1, 2)
        pt32 = (2, 3)

        self.assertTrue(geometry.lines_intersect_2d(pt11, pt12, pt21, pt22))
        self.assertFalse(geometry.lines_intersect_2d(pt11, pt12, pt31, pt32))

    def test_equal_points_2d(self):
        """Tests equal_points_2d."""
        p1 = (0, 0)
        p2 = (0.25, 0.25)

        self.assertTrue(geometry.equal_points_2d(p1, p2, 1))
        self.assertFalse(geometry.equal_points_2d(p1, p2, 0.000005))

    def test_on_line_and_between_endpoints_2d(self):
        """Tests on_line_and_between_endpoints_2d."""
        pt1 = (0, 0)
        pt2 = (4, 4)
        tol = 0.01

        self.assertTrue(geometry.on_line_and_between_endpoints_2d(pt1, pt2, (2, 2), tol))
        self.assertFalse(geometry.on_line_and_between_endpoints_2d(pt1, pt2, (2, 2.5), tol))

    def test_distance_2d_to_line_segment_2d(self):
        """Tests distance_2d_to_line_segment_2d."""
        pt1 = (0, 0)
        pt2 = (4, 4)
        pt3 = (2, 3)

        geometry.set_tol_2d(0.01)
        self.assertEqual(0.7071067811865476, geometry.distance_to_line_segment_2d(pt1, pt2, pt3))

    def test_cross_2d(self):
        """Tests cross_2d."""
        origin = (1, 1)
        pt1 = (2, 4, 6)
        pt2 = (8, 10, 12)

        self.assertEqual(-12, geometry.cross_2d(origin, pt1, pt2))

    def test_distance_2d(self):
        """Test distance_2d."""
        pt1 = (2, 2, 2)
        pt2 = (4, 4, 4)

        self.assertEqual(2.8284271247461903, geometry.distance_2d(pt1, pt2))

    def test_compute_polygon_centroid_2d(self):
        """Test compute_polygon_centroid_2d."""
        triangle = [
            (0, 0),
            (2, 0),
            (1, 3)
        ]

        self.assertEqual((1, 1, 0), geometry.compute_polygon_centroid_2d(triangle))

    def test_distance_to_line_2d(self):
        """Test distance_to_line_2d."""
        pt1 = (0, 0)
        pt2 = (4, 4)
        pt3 = (2, 3)

        self.assertEqual(0.7071067811865475, geometry.distance_to_line_2d(pt1, pt2, pt3, 0.01))

    def test_angle_between_edges_2d(self):
        """Test angle_between_edges_2d."""
        pt1 = (1, 0)
        pt2 = (0, 0)
        pt3 = (0, 1)

        self.assertEqual(math.pi / 2, geometry.angle_between_edges_2d(pt1, pt2, pt3))

    def test_calculate_celerity(self):
        """Test celerity calculation."""
        self.assertAlmostEqual(3.998971888515353, geometry.calculate_celerity(20, -50, 32), places=6)

    def test_calculate_wavelength(self):
        """Test celerity calculation."""
        self.assertAlmostEqual(79.97938716775904, geometry.calculate_wavelength(20, -100, 32), places=6)


if __name__ == '__main__':
    unittest.main()
