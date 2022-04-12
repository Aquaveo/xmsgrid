"""ugrid_util function tests."""
import unittest

import numpy as np

from xms.grid.ugrid import UGrid
from xms.grid.ugrid import ugrid_utils


def _get_test_ugrid():
    points = [
        (9.18, 59.48), (32.48, 46.66), (6.29, 27.33), (66.44, 15.05), (66.08, 39.79), (34.83, 53.34),
        (76.19, 62.19), (33.38, 73.03), (27.96, 52.98), (46.75, 27.15), (11.53, 34.74), (-4.91, 36.36),
        (-12.86, 27.87), (-20.26, 51.72), (-8.34, 59.3), (4.12, 73.57), (17.31, 67.25), (60.48, 56.41),
        (52.35, 43.41), (35.19, 32.75), (30.85, 20.11), (10.08, 46.48),
    ]
    cellstream = [
        UGrid.cell_type_enum.TRIANGLE, 3, 12, 11, 13,
        UGrid.cell_type_enum.TRIANGLE, 3, 11, 12, 2,
        UGrid.cell_type_enum.TRIANGLE, 3, 10, 21, 11,
        UGrid.cell_type_enum.TRIANGLE, 3, 1, 21, 10,
        UGrid.cell_type_enum.TRIANGLE, 3, 8, 21, 1,
        UGrid.cell_type_enum.TRIANGLE, 3, 10, 11, 2,
        UGrid.cell_type_enum.TRIANGLE, 3, 12, 20, 2,
        UGrid.cell_type_enum.TRIANGLE, 3, 11, 21, 14,
        UGrid.cell_type_enum.TRIANGLE, 3, 13, 14, 15,
        UGrid.cell_type_enum.TRIANGLE, 3, 13, 11, 14,
        UGrid.cell_type_enum.TRIANGLE, 3, 15, 14, 0,
        UGrid.cell_type_enum.TRIANGLE, 3, 0, 8, 16,
        UGrid.cell_type_enum.TRIANGLE, 3, 14, 21, 0,
        UGrid.cell_type_enum.TRIANGLE, 3, 16, 8, 7,
        UGrid.cell_type_enum.TRIANGLE, 3, 0, 16, 15,
        UGrid.cell_type_enum.TRIANGLE, 3, 21, 8, 0,
        UGrid.cell_type_enum.TRIANGLE, 3, 15, 16, 7,
        UGrid.cell_type_enum.TRIANGLE, 3, 10, 2, 20,
        UGrid.cell_type_enum.TRIANGLE, 3, 19, 1, 10,
        UGrid.cell_type_enum.TRIANGLE, 3, 19, 20, 9,
        UGrid.cell_type_enum.TRIANGLE, 3, 9, 3, 4,
        UGrid.cell_type_enum.TRIANGLE, 3, 3, 9, 20,
        UGrid.cell_type_enum.TRIANGLE, 3, 4, 3, 6,
        UGrid.cell_type_enum.TRIANGLE, 3, 19, 9, 18,
        UGrid.cell_type_enum.TRIANGLE, 3, 18, 9, 4,
        UGrid.cell_type_enum.TRIANGLE, 3, 5, 7, 8,
        UGrid.cell_type_enum.TRIANGLE, 3, 5, 1, 18,
        UGrid.cell_type_enum.TRIANGLE, 3, 7, 5, 17,
        UGrid.cell_type_enum.TRIANGLE, 3, 8, 1, 5,
        UGrid.cell_type_enum.TRIANGLE, 3, 4, 17, 18,
        UGrid.cell_type_enum.TRIANGLE, 3, 17, 4, 6,
        UGrid.cell_type_enum.TRIANGLE, 3, 17, 6, 7,
        UGrid.cell_type_enum.TRIANGLE, 3, 18, 17, 5,
        UGrid.cell_type_enum.TRIANGLE, 3, 1, 19, 18,
        UGrid.cell_type_enum.TRIANGLE, 3, 10, 20, 19
    ]

    return UGrid(points=points, cellstream=cellstream)


class TestUGridUtilFunctions(unittest.TestCase):
    """ugrid_util function tests."""

    @staticmethod
    def get_3d_linear_ugrid():
        """Returns a 3D linear UGrid."""
        points = ((0, 0, 0), (10, 0, 0), (20, 0, 0), (30, 0, 0), (40, 0, 0),
                  (0, 10, 0), (10, 10, 0), (20, 10, 0), (30, 10, 0), (40, 10, 0),
                  (0, 20, 0), (10, 20, 0), (20, 20, 0), (30, 20, 0), (40, 20, 0),
                  (0, 0, 10), (10, 0, 10), (20, 0, 10), (30, 0, 10), (40, 0, 10),
                  (0, 10, 10), (10, 10, 10), (20, 10, 10), (30, 10, 10),
                  (40, 10, 10), (0, 20, 10), (10, 20, 10), (20, 20, 10), (30, 20, 10),
                  (40, 20, 10))
        cells = (UGrid.cell_type_enum.TETRA, 4, 0, 1, 5, 15,
                 UGrid.cell_type_enum.VOXEL, 8, 1, 2, 6, 7, 16, 17, 21, 22,
                 UGrid.cell_type_enum.HEXAHEDRON, 8, 2, 3, 8, 7, 17, 18, 23, 22,
                 UGrid.cell_type_enum.POLYHEDRON, 6, 4, 8, 9, 14, 13, 4, 8, 9, 24, 23,
                               4, 9, 14, 29, 24, 4, 13, 14, 29, 28,  # NOQA E127
                               4, 8, 13, 28, 23, 4, 23, 24, 29, 28,  # NOQA E127
                 UGrid.cell_type_enum.WEDGE, 6, 3, 4, 18, 8, 9, 23,
                 UGrid.cell_type_enum.PYRAMID, 5, 5, 6, 11, 10, 20)
        xu = UGrid(points, cells)
        return xu

    def test_xm_write_and_read_ugrid_to_ascii_file(self):
        """Test reading and writing a UGrid to an ASCII file."""
        xu3d = self.get_3d_linear_ugrid()
        # write
        # TODO Get this path set correctly
        out_file_name = "PLACEHOLDER FOR TEST FILES PATH" + "3d_grid_linear.xmugrid"
        ugrid_utils.write_ugrid_to_ascii_file(xu3d, out_file_name)
        # read
        xu_read = ugrid_utils.read_ugrid_from_ascii_file(out_file_name)
        np.testing.assert_array_equal(xu3d.locations, xu_read.locations)
        np.testing.assert_array_equal(xu3d.cellstream, xu3d.cellstream)

    def test_remove_points(self):
        """Test removing points from a UGrid."""
        expected_points = [
            (9.18, 59.48, 0.0), (32.48, 46.66, 0.0), (6.29, 27.33, 0.0), (66.44, 15.05, 0.0), (66.08, 39.79, 0.0),
            (34.83, 53.34, 0.0), (76.19, 62.19, 0.0), (33.38, 73.03, 0.0), (27.96, 52.98, 0.0), (46.75, 27.15, 0.0),
            (11.53, 34.74, 0.0), (-4.91, 36.36, 0.0), (-12.86, 27.87, 0.0), (-20.26, 51.72, 0.0), (-8.34, 59.3, 0.0),
            (4.12, 73.57, 0.0), (17.31, 67.25, 0.0), (60.48, 56.41, 0.0), (35.19, 32.75, 0.0), (30.85, 20.11, 0.0),
        ]
        expected_cells = [
            UGrid.cell_type_enum.TRIANGLE, 3, 12, 11, 13,
            UGrid.cell_type_enum.TRIANGLE, 3, 11, 12, 2,
            UGrid.cell_type_enum.TRIANGLE, 3, 10, 11, 2,
            UGrid.cell_type_enum.TRIANGLE, 3, 12, 19, 2,
            UGrid.cell_type_enum.TRIANGLE, 3, 13, 14, 15,
            UGrid.cell_type_enum.TRIANGLE, 3, 13, 11, 14,
            UGrid.cell_type_enum.TRIANGLE, 3, 15, 14, 0,
            UGrid.cell_type_enum.TRIANGLE, 3, 0, 8, 16,
            UGrid.cell_type_enum.TRIANGLE, 3, 16, 8, 7,
            UGrid.cell_type_enum.TRIANGLE, 3, 0, 16, 15,
            UGrid.cell_type_enum.TRIANGLE, 3, 15, 16, 7,
            UGrid.cell_type_enum.TRIANGLE, 3, 10, 2, 19,
            UGrid.cell_type_enum.TRIANGLE, 3, 18, 1, 10,
            UGrid.cell_type_enum.TRIANGLE, 3, 18, 19, 9,
            UGrid.cell_type_enum.TRIANGLE, 3, 9, 3, 4,
            UGrid.cell_type_enum.TRIANGLE, 3, 3, 9, 19,
            UGrid.cell_type_enum.TRIANGLE, 3, 4, 3, 6,
            UGrid.cell_type_enum.TRIANGLE, 3, 5, 7, 8,
            UGrid.cell_type_enum.TRIANGLE, 3, 7, 5, 17,
            UGrid.cell_type_enum.TRIANGLE, 3, 8, 1, 5,
            UGrid.cell_type_enum.TRIANGLE, 3, 17, 4, 6,
            UGrid.cell_type_enum.TRIANGLE, 3, 17, 6, 7,
            UGrid.cell_type_enum.TRIANGLE, 3, 10, 19, 18,
        ]
        input_grid = _get_test_ugrid()
        output_grid = ugrid_utils.remove_points(input_grid, [18, 21])

        actual_points = output_grid.locations
        actual_cellstream = output_grid.cellstream

        self.assertTrue(np.array_equal(expected_points, actual_points))
        self.assertTrue(np.array_equal(expected_cells, actual_cellstream))

    def test_remove_cells(self):
        """Test removing cells from a UGrid."""
        expected_points = [
            (9.18, 59.48, 0.0), (32.48, 46.66, 0.0), (6.29, 27.33, 0.0), (66.44, 15.05, 0.0), (66.08, 39.79, 0.0),
            (34.83, 53.34, 0.0), (76.19, 62.19, 0.0), (33.38, 73.03, 0.0), (27.96, 52.98, 0.0), (46.75, 27.15, 0.0),
            (11.53, 34.74, 0.0), (-4.91, 36.36, 0.0), (-12.86, 27.87, 0.0), (-20.26, 51.72, 0.0), (-8.34, 59.3, 0.0),
            (4.12, 73.57, 0.0), (17.31, 67.25, 0.0), (60.48, 56.41, 0.0), (52.35, 43.41, 0.0), (35.19, 32.75, 0.0),
            (30.85, 20.11, 0.0), (10.08, 46.48, 0.0),
        ]
        expected_cells = [
            UGrid.cell_type_enum.TRIANGLE, 3, 12, 11, 13,
            UGrid.cell_type_enum.TRIANGLE, 3, 11, 12, 2,
            UGrid.cell_type_enum.TRIANGLE, 3, 1, 21, 10,
            UGrid.cell_type_enum.TRIANGLE, 3, 8, 21, 1,
            UGrid.cell_type_enum.TRIANGLE, 3, 10, 11, 2,
            UGrid.cell_type_enum.TRIANGLE, 3, 12, 20, 2,
            UGrid.cell_type_enum.TRIANGLE, 3, 11, 21, 14,
            UGrid.cell_type_enum.TRIANGLE, 3, 13, 14, 15,
            UGrid.cell_type_enum.TRIANGLE, 3, 13, 11, 14,
            UGrid.cell_type_enum.TRIANGLE, 3, 15, 14, 0,
            UGrid.cell_type_enum.TRIANGLE, 3, 0, 8, 16,
            UGrid.cell_type_enum.TRIANGLE, 3, 14, 21, 0,
            UGrid.cell_type_enum.TRIANGLE, 3, 16, 8, 7,
            UGrid.cell_type_enum.TRIANGLE, 3, 0, 16, 15,
            UGrid.cell_type_enum.TRIANGLE, 3, 21, 8, 0,
            UGrid.cell_type_enum.TRIANGLE, 3, 15, 16, 7,
            UGrid.cell_type_enum.TRIANGLE, 3, 10, 2, 20,
            UGrid.cell_type_enum.TRIANGLE, 3, 19, 1, 10,
            UGrid.cell_type_enum.TRIANGLE, 3, 19, 20, 9,
            UGrid.cell_type_enum.TRIANGLE, 3, 9, 3, 4,
            UGrid.cell_type_enum.TRIANGLE, 3, 3, 9, 20,
            UGrid.cell_type_enum.TRIANGLE, 3, 4, 3, 6,
            UGrid.cell_type_enum.TRIANGLE, 3, 19, 9, 18,
            UGrid.cell_type_enum.TRIANGLE, 3, 18, 9, 4,
            UGrid.cell_type_enum.TRIANGLE, 3, 5, 7, 8,
            UGrid.cell_type_enum.TRIANGLE, 3, 5, 1, 18,
            UGrid.cell_type_enum.TRIANGLE, 3, 7, 5, 17,
            UGrid.cell_type_enum.TRIANGLE, 3, 4, 17, 18,
            UGrid.cell_type_enum.TRIANGLE, 3, 17, 4, 6,
            UGrid.cell_type_enum.TRIANGLE, 3, 17, 6, 7,
            UGrid.cell_type_enum.TRIANGLE, 3, 18, 17, 5,
            UGrid.cell_type_enum.TRIANGLE, 3, 1, 19, 18,
            UGrid.cell_type_enum.TRIANGLE, 3, 10, 20, 19,
        ]
        input_grid = _get_test_ugrid()
        output_grid = ugrid_utils.remove_cells(input_grid, [2, 28])

        actual_points = output_grid.locations
        actual_cellstream = output_grid.cellstream

        self.assertTrue(np.array_equal(expected_points, actual_points))
        self.assertTrue(np.array_equal(expected_cells, actual_cellstream))

    def test_remove_points_and_cells(self):
        """Test removing points and cells from a UGrid."""
        expected_points = [
            (9.18, 59.48, 0.0), (32.48, 46.66, 0.0), (6.29, 27.33, 0.0), (66.44, 15.05, 0.0), (66.08, 39.79, 0.0),
            (34.83, 53.34, 0.0), (76.19, 62.19, 0.0), (33.38, 73.03, 0.0), (27.96, 52.98, 0.0), (46.75, 27.15, 0.0),
            (11.53, 34.74, 0.0), (-4.91, 36.36, 0.0), (-12.86, 27.87, 0.0), (-20.26, 51.72, 0.0), (-8.34, 59.3, 0.0),
            (4.12, 73.57, 0.0), (17.31, 67.25, 0.0), (60.48, 56.41, 0.0), (52.35, 43.41, 0.0), (35.19, 32.75, 0.0),
            (30.85, 20.11, 0.0),
        ]
        expected_cells = [
            UGrid.cell_type_enum.TRIANGLE, 3, 12, 11, 13,
            UGrid.cell_type_enum.TRIANGLE, 3, 11, 12, 2,
            UGrid.cell_type_enum.TRIANGLE, 3, 10, 11, 2,
            UGrid.cell_type_enum.TRIANGLE, 3, 12, 20, 2,
            UGrid.cell_type_enum.TRIANGLE, 3, 13, 14, 15,
            UGrid.cell_type_enum.TRIANGLE, 3, 13, 11, 14,
            UGrid.cell_type_enum.TRIANGLE, 3, 15, 14, 0,
            UGrid.cell_type_enum.TRIANGLE, 3, 0, 8, 16,
            UGrid.cell_type_enum.TRIANGLE, 3, 16, 8, 7,
            UGrid.cell_type_enum.TRIANGLE, 3, 0, 16, 15,
            UGrid.cell_type_enum.TRIANGLE, 3, 15, 16, 7,
            UGrid.cell_type_enum.TRIANGLE, 3, 10, 2, 20,
            UGrid.cell_type_enum.TRIANGLE, 3, 19, 1, 10,
            UGrid.cell_type_enum.TRIANGLE, 3, 19, 20, 9,
            UGrid.cell_type_enum.TRIANGLE, 3, 9, 3, 4,
            UGrid.cell_type_enum.TRIANGLE, 3, 3, 9, 20,
            UGrid.cell_type_enum.TRIANGLE, 3, 4, 3, 6,
            UGrid.cell_type_enum.TRIANGLE, 3, 19, 9, 18,
            UGrid.cell_type_enum.TRIANGLE, 3, 18, 9, 4,
            UGrid.cell_type_enum.TRIANGLE, 3, 5, 7, 8,
            UGrid.cell_type_enum.TRIANGLE, 3, 5, 1, 18,
            UGrid.cell_type_enum.TRIANGLE, 3, 7, 5, 17,
            UGrid.cell_type_enum.TRIANGLE, 3, 8, 1, 5,
            UGrid.cell_type_enum.TRIANGLE, 3, 4, 17, 18,
            UGrid.cell_type_enum.TRIANGLE, 3, 17, 4, 6,
            UGrid.cell_type_enum.TRIANGLE, 3, 17, 6, 7,
            UGrid.cell_type_enum.TRIANGLE, 3, 18, 17, 5,
            UGrid.cell_type_enum.TRIANGLE, 3, 1, 19, 18,
            UGrid.cell_type_enum.TRIANGLE, 3, 10, 20, 19
        ]
        input_grid = _get_test_ugrid()
        output_grid = ugrid_utils.remove_points_and_cells(input_grid, [21], [2, 3, 4, 7, 12, 15])

        actual_points = output_grid.locations
        actual_cellstream = output_grid.cellstream

        self.assertTrue(np.array_equal(expected_points, actual_points))
        self.assertTrue(np.array_equal(expected_cells, actual_cellstream))
