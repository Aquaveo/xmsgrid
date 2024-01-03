"""Tests for the MultiPolyIntersector class."""

__copyright__ = "(C) Copyright Aquaveo 2023"
__license__ = "See accompanying file LICENSE or https://aquaveo.com/bsd/license.txt"

# 1. Standard python modules
import math
import unittest

# 2. Third party modules

# 3. Aquaveo modules

# 4. Local modules
from xms import grid


def _zeroed_z(points) -> list[list[float]]:
    """Returns the points with 0.0 for z values."""
    return [[point[0], point[1], 0.0] for point in points]


class TestMultiPolyIntersector(unittest.TestCase):
    """Tests for the MultiPolyIntersector class."""

    def setUp(self):
        """Runs before each test case."""
        pass

    def _run_test(self, pt1, pt2, poly_points, polys, poly_ids, t_vals, pts, starting_id=1, query='covered_by'):
        """Runs the test."""
        mpi = grid.geometry.MultiPolyIntersector(poly_points, polys, starting_id, query)

        # Traverse the line segment
        out_poly_ids, out_t_vals, out_pts = mpi.traverse_line_segment(pt1, pt2)

        # Check poly ids
        assert len(out_poly_ids) == len(poly_ids)
        assert_str = f'Expected {poly_ids}. Got {out_poly_ids}'
        assert out_poly_ids == poly_ids, assert_str

        # Check t vals
        assert len(out_t_vals) == len(t_vals)
        for out_t_val, t_val in zip(out_t_vals, t_vals):
            assert_str = f'Expected {t_val}. Got {out_t_val}'
            assert math.isclose(out_t_val, t_val), assert_str

        # Check points
        assert len(out_pts) == len(pts)
        for idx, (out_point, point) in enumerate(zip(_zeroed_z(out_pts), _zeroed_z(pts))):
            for i in range(3):
                assert_str = f'Point {idx}[{i}], : Expected {point[i]}. Got {out_point[i]}'
                assert math.isclose(out_point[i], point[i]), assert_str

    def test_traverse_line_segment_1_out_out(self):
        r"""A test.

                      (10,10)
           3-------------2
           |             |
         0------------------1
           |             |
           |      1      |
           |             |
           0-------------1
        (0,0)
        """
        # Use lists to prove that we can
        pts = [[0, 0, 0], [10, 0, 0], [10, 10, 0], [0, 10, 0]]
        polys = [[0, 1, 2, 3]]
        expected_ids = (1, -1)
        expected_t_vals = (0.08333333333333333, 0.91666666666666667)
        expected_pts = ((0.0, 5.0, 0.0), (10.0, 5.0, 0.0))
        self._run_test([-1, 5], [11, 5], pts, polys, expected_ids, expected_t_vals, expected_pts)
        expected_ids = (0, -1)
        self._run_test([-1, 5], [11, 5], pts, polys, expected_ids, expected_t_vals, expected_pts, 0, 'intersects')

    def test_traverse_line_segment_1_out_in(self):
        """A test.

                      (10,10)
           3-------------2
           |             |
         0----------1    |
           |             |
           |      1      |
           |             |
           0-------------1
        (0,0)
        """
        # Use tuples to prove that we can
        pts = ((0, 0, 0), (10, 0, 0), (10, 10, 0), (0, 10, 0))
        polys = [(0, 1, 2, 3)]
        expected_ids = (1, -1)
        expected_t_vals = (0.11111111111111111, 1.0)
        expected_pts = ((0.0, 5.0, 0.0), (8.0, 5.0, 0.0))
        self._run_test((-1, 5), (8, 5), pts, polys, expected_ids, expected_t_vals, expected_pts)
        expected_ids = (2, -1)
        self._run_test((-1, 5), (8, 5), pts, polys, expected_ids, expected_t_vals, expected_pts, 2, 'intersects')

    def test_polygon_from_point(self):
        r"""A test.

         (0,20)
           3-------------2
           |             |
           |             |
           |      *1     |      *
           |             |
           |             |
           0------*-----*1------*------6
                         |             |
                         |             |
                         |      *2     |
                  *      |             |
                         |             |
                         4-------------5
        (0,0)                        (20,0)
        """
        pts = [(0, 10, 0), (10, 10, 0), (10, 20, 0), (0, 20, 0), (10, 0, 0), (20, 0, 0), (20, 10, 0)]
        polys = [(0, 1, 2, 3), (4, 5, 6, 1)]
        mpi = grid.geometry.MultiPolyIntersector(pts, polys)
        assert mpi.polygon_from_point((5, 5, 0)) == -1
        assert mpi.polygon_from_point((5, 10, 0)) == 1
        assert mpi.polygon_from_point((5, 15, 0)) == 1
        assert mpi.polygon_from_point((10, 10, 0)) == 1
        assert mpi.polygon_from_point((15, 15, 0)) == -1
        assert mpi.polygon_from_point((15, 10, 0)) == 2
        assert mpi.polygon_from_point((15, 5, 0)) == 2
        mpi = grid.geometry.MultiPolyIntersector(pts, polys, query='intersects')
        assert mpi.polygon_from_point((5, 5, 0)) == -1
        assert mpi.polygon_from_point((5, 10, 0)) == 1
        assert mpi.polygon_from_point((5, 15, 0)) == 1
        assert mpi.polygon_from_point((10, 10, 0)) == 1
        assert mpi.polygon_from_point((15, 15, 0)) == -1
        assert mpi.polygon_from_point((15, 10, 0)) == 2
        assert mpi.polygon_from_point((15, 5, 0)) == 2


if __name__ == '__main__':
    unittest.main()
