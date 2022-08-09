"""Test UGrid_py.cpp."""
import unittest

from xms.grid.ugrid import UGrid


class TestUGrid(unittest.TestCase):
    """UGrid tests."""

    @staticmethod
    def get_simple_quad_ugrid():
        """Returns a simple quad UGrid."""
        import numpy as np
        points = np.array(((0, 10, 0), (10, 10, 0), (20, 10, 0), (0, 0, 0), (10, 0, 0),
                           (20, 0, 0), (0, -10, 0), (10, -10, 0), (20, -10, 0)))
        cells = np.array((9, 4, 0, 3, 4, 1, 9, 4, 1, 4, 5, 2, 9, 4, 3, 6, 7, 4, 9, 4, 4, 7, 8, 5))
        xu = UGrid(points, cells)
        return xu

    @staticmethod
    def get_2d_linear_ugrid():
        """Returns a linear 2D UGrid."""
        points = ((0, 0, 0), (10, 0, 0), (20, 0, 0), (30, 0, 0), (40, 0, 0),
                  (0, 10, 0), (10, 10, 0), (20, 10, 0), (40, 10, 0), (0, 20, 0),
                  (10, 20, 0), (20, 20, 0), (30, 20, 0), (40, 20, 0))
        cells = (UGrid.cell_type_enum.QUAD, 4, 0, 1, 6, 5,
                 UGrid.cell_type_enum.PIXEL, 4, 1, 2, 6, 7,
                 UGrid.cell_type_enum.TRIANGLE, 3, 2, 3, 7,
                 UGrid.cell_type_enum.POLYGON, 6, 3, 4, 8, 13, 12, 7,
                 UGrid.cell_type_enum.POLY_LINE, 3, 7, 11, 10,
                 UGrid.cell_type_enum.LINE, 2, 5, 9)
        xu = UGrid(points, cells)
        return xu

    @staticmethod
    def get_3d_linear_ugrid():
        """Returns a linear 3D UGrid."""
        points = ((0, 0, 0), (10, 0, 0), (20, 0, 0), (30, 0, 0), (40, 0, 0),
                  (0, 10, 0), (10, 10, 0), (20, 10, 0), (30, 10, 0), (40, 10, 0),
                  (0, 20, 0), (10, 20, 0), (20, 20, 0), (30, 20, 0), (40, 20, 0),
                  (0, 0, 10), (10, 0, 10), (20, 0, 10), (30, 0, 10), (40, 0, 10),
                  (0, 10, 10), (10, 10, 10), (20, 10, 10), (30, 10, 10), (40, 10, 10),
                  (0, 20, 10), (10, 20, 10), (20, 20, 10), (30, 20, 10), (40, 20, 10))
        cells = (UGrid.cell_type_enum.TETRA, 4, 0, 1, 5, 15,
                 UGrid.cell_type_enum.VOXEL, 8, 1, 2, 6, 7, 16, 17, 21, 22,
                 UGrid.cell_type_enum.HEXAHEDRON, 8, 2, 3, 8, 7, 17, 18, 23, 22,
                 UGrid.cell_type_enum.POLYHEDRON, 6,
                 4, 9, 8, 13, 14,  # Bottom face with 4 points : 9, 8, 13, 14
                 4, 8, 9, 24, 23,  # Front face with 4 points : 8, 9, 24, 23
                 4, 9, 14, 29, 24,  # Right face with 4 points : 9, 14, 29, 28
                 4, 14, 13, 28, 29,  # Back face with 4 points : 14, 13, 28, 29
                 4, 8, 13, 28, 23,  # Left face with 4 points : 13, 8, 23, 28
                 4, 23, 24, 29, 28,  # Top face with 4 points : 23, 24, 29, 28
                 UGrid.cell_type_enum.WEDGE, 6, 3, 4, 18, 8, 9, 23,
                 UGrid.cell_type_enum.PYRAMID, 5, 5, 6, 11, 10, 20)
        xu = UGrid(points, cells)
        return xu

    @staticmethod
    def get_hexahedron_ugrid(rows, cols, lays, origin):
        """Returns a hexahedron UGrid."""
        points = [None] * rows * cols * lays
        curr_id = 0
        for k in range(0, lays):
            for i in range(0, rows):
                for j in range(0, cols):
                    points[curr_id] = (j + origin[0], rows - i - 1 + origin[1], lays - k - 1 + origin[2])
                    curr_id += 1
        cells = [None] * (rows - 1) * (cols - 1) * (lays - 1) * 10
        num_in_layer = rows * cols
        curr_id = 0
        for k in range(0, lays - 1):
            lay_offset = num_in_layer * k
            for i in range(0, rows - 1):
                for j in range(0, cols - 1):
                    cells[curr_id] = UGrid.cell_type_enum.HEXAHEDRON
                    cells[curr_id + 1] = 8
                    cells[curr_id + 2] = j + cols * i + lay_offset
                    cells[curr_id + 3] = j + 1 + cols * i + lay_offset
                    cells[curr_id + 4] = j + 1 + cols * (i + 1) + lay_offset
                    cells[curr_id + 5] = j + cols * (i + 1) + lay_offset
                    cells[curr_id + 6] = j + cols * i + lay_offset + num_in_layer
                    cells[curr_id + 7] = j + 1 + cols * i + lay_offset + num_in_layer
                    cells[curr_id + 8] = j + 1 + cols * (i + 1) + lay_offset + num_in_layer
                    cells[curr_id + 9] = j + cols * (i + 1) + lay_offset + num_in_layer
                    curr_id += 10
        xu = UGrid(points, cells)
        return xu

    def test_ugrid_new_default(self):
        """Test constructing a UGrid with default arguments."""
        # TODO Check for default args
        xu = UGrid()
        self.assertIsInstance(xu, UGrid)

    def test_ugrid_new(self):
        """Test constructing a UGrid."""
        points = ((0, 0, 0), (20, 0, 0), (0, 20, 0))
        cells = (5, 3, 0, 1, 2)
        xu = UGrid(points, cells)
        self.assertIsInstance(xu, UGrid)

    def test_ugrid_new_numpy(self):
        """Test constructing a UGrid from numpy arrays."""
        import numpy as np
        points = np.array(((0, 0, 0), (20, 0, 0), (0, 20, 0)))
        cells = np.array((5, 3, 0, 1, 2))
        xu = UGrid(points, cells)
        self.assertIsInstance(xu, UGrid)

    def test_ugrid_point_count(self):
        """Test getting the number of points in a UGrid."""
        points = ((0, 0, 0), (20, 0, 0), (0, 20, 0))
        cells = (5, 3, 0, 1, 2)
        xu = UGrid(points, cells)
        num_points_base = len(points)
        self.assertEqual(num_points_base, xu.point_count)

    def test_ugrid_get_locations(self):
        """Test getting a point locations of a UGrid."""
        import numpy as np
        points = ((0, 0, 0), (20, 0, 0), (0, 20, 0))
        cells = (5, 3, 0, 1, 2)
        xu = UGrid(points, cells)
        points_out = xu.locations
        np.testing.assert_array_equal(np.array(points), points_out)

    def test_ugrid_set_locations(self):
        """Test setting a point locations of a UGrid."""
        import numpy as np
        points = ((0, 0, 0), (20, 0, 0), (0, 20, 0))
        xu = UGrid()
        self.assertEqual(0, xu.point_count)  # Should be empty
        self.assertFalse(xu.modified)
        xu.locations = points
        self.assertTrue(xu.modified)
        num_points_base = len(points)
        self.assertEqual(num_points_base, xu.point_count)
        points_out = xu.locations
        np.testing.assert_array_equal(np.array(points), points_out)

    def test_ugrid_get_locations_numpy(self):
        """Test getting a point locations of a UGrid."""
        import numpy as np
        points = np.array(((0, 0, 0), (20, 0, 0), (0, 20, 0)))
        xu = UGrid()
        self.assertEqual(0, xu.point_count)  # Should be empty
        xu.locations = points
        num_points_base = len(points)
        self.assertEqual(num_points_base, xu.point_count)
        points_out = xu.locations
        np.testing.assert_array_equal(np.array(points), points_out)

    def test_ugrid_get_locations2(self):
        """Test getting a point locations of a UGrid."""
        points = ((0, 0, 0), (20, 0, 0), (0, 20, 0))
        cells = (5, 3, 0, 1, 2)
        xu = UGrid(points, cells)
        p1 = xu.get_point_location(0)
        p2 = xu.get_point_location(1)
        p3 = xu.get_point_location(2)
        p4 = xu.get_point_location(3)
        self.assertEqual((0, 0, 0), p1)
        self.assertEqual((20, 0, 0), p2)
        self.assertEqual((0, 20, 0), p3)
        self.assertEqual((0, 0, 0), p4)

    def test_ugrid_get_point_xy0(self):
        """Test getting a point location by index."""
        points = ((0, 0, 2), (20, 0, 1), (0, 20, 0))
        cells = (5, 3, 0, 1, 2)
        xu = UGrid(points, cells)
        p1 = xu.get_point_xy0(0)
        p2 = xu.get_point_xy0(1)
        p3 = xu.get_point_xy0(2)
        p4 = xu.get_point_xy0(3)
        self.assertEqual((0, 0, 0), p1)
        self.assertEqual((20, 0, 0), p2)
        self.assertEqual((0, 20, 0), p3)
        self.assertEqual((0, 0, 0), p4)

    def test_ugrid_set_point_location(self):
        """Test setting the location of a point in a UGrid."""
        points = ((0, 10, 0), (10, 10, 0), (20, 10, 0), (0, 0, 0), (10, 0, 0),
                  (20, 0, 0), (0, -10, 0), (10, -10, 0), (20, -10, 0))
        cells = (9, 4, 0, 3, 4, 1, 9, 4, 1, 4, 5, 2, 9, 4, 3, 6, 7, 4, 9, 4, 4, 7, 8, 5)
        xu = UGrid(points, cells)
        self.assertTrue(xu.modified)
        xu.set_unmodified()
        self.assertFalse(xu.modified)
        self.assertFalse(xu.set_point_location(-1, (0, 0, 0)))
        self.assertFalse(xu.set_point_location(len(points), (0, 0, 0)))
        self.assertTrue(xu.set_point_location(0, (-10, -10, 0)))
        self.assertTrue(xu.modified)
        self.assertEqual((-10, -10, 0), xu.get_point_location(0))

    def test_ugrid_set_point_location_numpy(self):
        """Test setting the point locations of a UGrid with a numpy array."""
        import numpy as np
        points = np.array(((0, 10, 0), (10, 10, 0), (20, 10, 0), (0, 0, 0), (10, 0, 0),
                           (20, 0, 0), (0, -10, 0), (10, -10, 0), (20, -10, 0)))
        cells = np.array((9, 4, 0, 3, 4, 1, 9, 4, 1, 4, 5, 2, 9, 4, 3, 6, 7, 4, 9, 4, 4, 7, 8, 5))
        xu = UGrid(points, cells)
        self.assertFalse(xu.set_point_location(-1, (0, 0, 0)))
        self.assertFalse(xu.set_point_location(len(points), (0, 0, 0)))
        self.assertTrue(xu.set_point_location(0, (-10, -10, 0)))
        self.assertEqual((-10, -10, 0), xu.get_point_location(0))

    def test_ugrid_get_points_locations(self):
        """Test getting the point locations of a UGrid."""
        import numpy as np
        points = np.array(((0, 10, 0), (10, 10, 0), (20, 10, 0), (0, 0, 0), (10, 0, 0),
                           (20, 0, 0), (0, -10, 0), (10, -10, 0), (20, -10, 0)))
        cells = np.array((9, 4, 0, 3, 4, 1, 9, 4, 1, 4, 5, 2, 9, 4, 3, 6, 7, 4, 9, 4, 4, 7, 8, 5))
        xu = UGrid(points, cells)
        point_indices = np.array((0, 3, 6))
        expected_points = np.array(((0, 10, 0), (0, 0, 0), (0, -10, 0)))
        points_from_indxs = xu.get_points_locations(point_indices)
        np.testing.assert_array_equal(expected_points, points_from_indxs)

    def test_ugrid_get_extents(self):
        """Test getting the extents of a UGrid."""
        points = ((0, 0, 0), (10, 0, 0), (20, 0, 0), (30, 0, 0), (40, 0, 0),
                  (0, 10, 0), (10, 10, 0), (20, 10, 0), (40, 10, 0), (0, 20, 0),
                  (10, 20, 0), (20, 20, 0), (30, 20, 0), (40, 20, 0))
        cells = (UGrid.cell_type_enum.QUAD, 4, 0, 1, 6, 5,
                 UGrid.cell_type_enum.PIXEL, 4, 1, 2, 6, 7,
                 UGrid.cell_type_enum.TRIANGLE, 3, 2, 3, 7,
                 UGrid.cell_type_enum.POLYGON, 6, 3, 4, 8, 13, 12, 7,
                 UGrid.cell_type_enum.POLY_LINE, 3, 7, 11, 10,
                 UGrid.cell_type_enum.LINE, 2, 5, 9)
        xu = UGrid(points, cells)
        exp_min = (0, 0, 0)
        exp_max = (40, 20, 0)
        act_min, act_max = xu.extents
        self.assertEqual(exp_min, act_min)
        self.assertEqual(exp_max, act_max)

    def test_get_point_adjacent_cells(self):
        """Test getting the cells adjacent to a point."""
        points = ((0, 10, 0), (10, 10, 0), (20, 10, 0), (0, 0, 0), (10, 0, 0), (20, 0, 0))
        cellstream = (UGrid.cell_type_enum.QUAD, 4, 0, 3, 4, 1,
                      UGrid.cell_type_enum.QUAD, 4, 1, 4, 5, 2)
        xu = UGrid(points, cellstream)

        cell_empty = ()
        cell_zero = (0,)
        cell_zero_and_one = (0, 1)
        cell_one = (1,)

        self.assertEqual(cell_empty, xu.get_point_adjacent_cells(-1))
        self.assertEqual(cell_zero, xu.get_point_adjacent_cells(0))
        self.assertEqual(cell_zero_and_one, xu.get_point_adjacent_cells(1))
        self.assertEqual(cell_one, xu.get_point_adjacent_cells(2))
        self.assertEqual(cell_zero, xu.get_point_adjacent_cells(3))
        self.assertEqual(cell_zero_and_one, xu.get_point_adjacent_cells(4))
        self.assertEqual(cell_one, xu.get_point_adjacent_cells(5))
        self.assertEqual(cell_empty, xu.get_point_adjacent_cells(6))

    def test_get_points_adjacent_cells(self):
        """Test getting the cells adjacent to points."""
        points = ((0, 10, 0), (10, 10, 0), (20, 10, 0), (0, 0, 0), (10, 0, 0),
                  (20, 0, 0), (0, -10, 0), (10, -10, 0), (20, -10, 0))
        cellstream = (UGrid.cell_type_enum.QUAD, 4, 0, 3, 4, 1,
                      UGrid.cell_type_enum.QUAD, 4, 1, 4, 5, 2,
                      UGrid.cell_type_enum.QUAD, 4, 3, 6, 7, 4,
                      UGrid.cell_type_enum.QUAD, 4, 4, 7, 8, 5)
        xu = UGrid(points, cellstream)
        expected_cells = ()

        points = (-1, 0)
        retrieved_cells = xu.get_points_adjacent_cells(points)
        self.assertEqual(expected_cells, retrieved_cells)

        points = (0, -1)
        retrieved_cells = xu.get_points_adjacent_cells(points)
        self.assertEqual(expected_cells, retrieved_cells)

        points = (0, 8)
        retrieved_cells = xu.get_points_adjacent_cells(points)
        self.assertEqual(expected_cells, retrieved_cells)

        expected_cells = (0, 2)
        points = (3, 4)
        retrieved_cells = xu.get_points_adjacent_cells(points)
        self.assertEqual(expected_cells, retrieved_cells)

        expected_cells = (0,)
        points = (0, 3)
        retrieved_cells = xu.get_points_adjacent_cells(points)
        self.assertEqual(expected_cells, retrieved_cells)

        expected_cells = ()
        points = (3, 4, 5)
        retrieved_cells = xu.get_points_adjacent_cells(points)
        self.assertEqual(expected_cells, retrieved_cells)

        expected_cells = ()
        points = (xu.point_count, 0)
        retrieved_cells = xu.get_points_adjacent_cells(points)
        self.assertEqual(expected_cells, retrieved_cells)

        expected_cells = ()
        points = (0, xu.point_count)
        retrieved_cells = xu.get_points_adjacent_cells(points)
        self.assertEqual(expected_cells, retrieved_cells)

    def test_get_cell_count(self):
        """Test getting the cell count of a UGrid."""
        points = ((0, 0, 0), (20, 0, 0), (0, 20, 0))
        cells = (5, 3, 0, 1, 2)
        xu = UGrid(points, cells)
        num_cells_base = 1
        self.assertEqual(num_cells_base, xu.cell_count)

    def test_get_cell_points(self):
        """Test getting the points of a cell."""
        import numpy as np
        xu = self.get_simple_quad_ugrid()
        invalid1 = xu.get_cell_points(-1)
        invalid2 = xu.get_cell_points(5)
        self.assertEqual(0, len(invalid1))
        self.assertEqual(0, len(invalid2))

        expected_cell_points = [np.array((0, 3, 4, 1)),
                                np.array((1, 4, 5, 2)),
                                np.array((3, 6, 7, 4)),
                                np.array((4, 7, 8, 5))]
        for i in range(0, len(expected_cell_points)):
            cell_points = xu.get_cell_points(i)
            np.testing.assert_array_equal(expected_cell_points[i], cell_points)

        xu2d = self.get_2d_linear_ugrid()
        expected_cell_points_2d = [np.array((0, 1, 6, 5)),
                                   np.array((1, 2, 7, 6)),
                                   np.array((2, 3, 7)),
                                   np.array((3, 4, 8, 13, 12, 7)),
                                   np.array((7, 11, 10)),
                                   np.array((5, 9))]
        for i in range(0, len(expected_cell_points_2d)):
            cell_points = xu2d.get_cell_points(i)
            np.testing.assert_array_equal(expected_cell_points_2d[i], cell_points)

        xu3d = self.get_3d_linear_ugrid()
        expected_cell_points_3d = [np.array((0, 1, 5, 15)),
                                   np.array((1, 2, 6, 7, 16, 17, 21, 22)),
                                   np.array((2, 3, 8, 7, 17, 18, 23, 22)),
                                   np.array((9, 8, 13, 14, 24, 23, 29, 28)),
                                   np.array((3, 4, 18, 8, 9, 23)),
                                   np.array((5, 6, 11, 10, 20))]
        for i in range(0, len(expected_cell_points_3d)):
            cell_points = xu3d.get_cell_points(i)
            np.testing.assert_array_equal(expected_cell_points_3d[i], cell_points)

    def test_get_cell_type(self):
        """Test getting the type of a cell."""
        xu2d = self.get_2d_linear_ugrid()
        self.assertEqual(14, xu2d.point_count)
        self.assertEqual(6, xu2d.cell_count)
        self.assertEqual(UGrid.cell_type_enum.INVALID_CELL_TYPE, xu2d.get_cell_type(-1))
        self.assertEqual(UGrid.cell_type_enum.INVALID_CELL_TYPE, xu2d.get_cell_type(6))
        self.assertEqual(UGrid.cell_type_enum.QUAD, xu2d.get_cell_type(0))
        self.assertEqual(UGrid.cell_type_enum.PIXEL, xu2d.get_cell_type(1))
        self.assertEqual(UGrid.cell_type_enum.TRIANGLE, xu2d.get_cell_type(2))
        self.assertEqual(UGrid.cell_type_enum.POLYGON, xu2d.get_cell_type(3))
        self.assertEqual(UGrid.cell_type_enum.POLY_LINE, xu2d.get_cell_type(4))
        self.assertEqual(UGrid.cell_type_enum.LINE, xu2d.get_cell_type(5))

        xu3d = self.get_3d_linear_ugrid()
        self.assertEqual(30, xu3d.point_count)
        self.assertEqual(6, xu3d.cell_count)
        self.assertEqual(UGrid.cell_type_enum.INVALID_CELL_TYPE, xu3d.get_cell_type(-1))
        self.assertEqual(UGrid.cell_type_enum.INVALID_CELL_TYPE, xu3d.get_cell_type(6))
        self.assertEqual(UGrid.cell_type_enum.TETRA, xu3d.get_cell_type(0))
        self.assertEqual(UGrid.cell_type_enum.VOXEL, xu3d.get_cell_type(1))
        self.assertEqual(UGrid.cell_type_enum.HEXAHEDRON, xu3d.get_cell_type(2))
        self.assertEqual(UGrid.cell_type_enum.POLYHEDRON, xu3d.get_cell_type(3))
        self.assertEqual(UGrid.cell_type_enum.WEDGE, xu3d.get_cell_type(4))
        self.assertEqual(UGrid.cell_type_enum.PYRAMID, xu3d.get_cell_type(5))

    def test_get_dimension_counts(self):
        """Test getting the dimension counts of various geometries."""
        import numpy as np
        # test 2D UGrid
        xu2d = self.get_2d_linear_ugrid()
        results_2d = np.array((0, 2, 4, 0))
        np.testing.assert_array_equal(results_2d, xu2d.dimension_counts)
        # test 3D UGrid
        xu3d = self.get_3d_linear_ugrid()
        results_3d = np.array((0, 0, 0, 6))
        np.testing.assert_array_equal(results_3d, xu3d.dimension_counts)
        xuempty = UGrid()
        # test empty UGrid
        results_empty = np.array((0, 0, 0, 0))
        np.testing.assert_array_equal(results_empty, xuempty.dimension_counts)

    def test_get_cell_dimension(self):
        """Test getting the dimension of a cell."""
        xu2d = self.get_2d_linear_ugrid()
        self.assertEqual(2, xu2d.get_cell_dimension(0))
        self.assertEqual(2, xu2d.get_cell_dimension(1))
        self.assertEqual(2, xu2d.get_cell_dimension(2))
        self.assertEqual(2, xu2d.get_cell_dimension(3))
        self.assertEqual(1, xu2d.get_cell_dimension(4))
        self.assertEqual(1, xu2d.get_cell_dimension(5))

        xu3d = self.get_3d_linear_ugrid()
        self.assertEqual(UGrid.cell_type_enum.INVALID_CELL_TYPE, xu3d.get_cell_dimension(-1))
        self.assertEqual(UGrid.cell_type_enum.INVALID_CELL_TYPE, xu3d.get_cell_dimension(6))
        self.assertEqual(3, xu3d.get_cell_dimension(0))
        self.assertEqual(3, xu3d.get_cell_dimension(1))
        self.assertEqual(3, xu3d.get_cell_dimension(2))
        self.assertEqual(3, xu3d.get_cell_dimension(3))
        self.assertEqual(3, xu3d.get_cell_dimension(4))
        self.assertEqual(3, xu3d.get_cell_dimension(5))

    def test_cell_functions(self):
        """Test various cell functions."""
        import numpy as np
        ugrid = self.get_simple_quad_ugrid()

        # Test get_cell_points
        points_of_cell = ugrid.get_cell_points(0)
        expected_points = (0, 3, 4, 1)
        self.assertEqual(expected_points, points_of_cell)
        # Test overload
        points_of_cell = ugrid.get_cell_points(0)
        self.assertEqual(expected_points, points_of_cell)
        locations = ugrid.get_cell_locations(0)
        expected_locations = np.array(((0.0, 10.0, 0.0), (0.0, 0.0, 0.0), (10.0, 0.0, 0.0), (10.0, 10.0, 0.0)))
        np.testing.assert_array_equal(expected_locations, locations)

        # Test get_cell_extents
        extents = ugrid.get_cell_extents(0)
        expected_extents = [(0.0, 0.0, 0.0), (10.0, 10.0, 0.0)]
        np.testing.assert_array_equal(expected_extents, extents)

        # Test get_cell_type
        self.assertEqual(UGrid.cell_type_enum.QUAD, ugrid.get_cell_type(0))

        # Test get_dimension_counts
        expected_dimensions = (0, 0, 4, 0)
        self.assertEqual(expected_dimensions, ugrid.dimension_counts)

        # Test get_cell_dimension
        self.assertEqual(2, ugrid.get_cell_dimension(0))

        # Test get_cell_centroid
        result = ugrid.get_cell_centroid(0)
        self.assertEqual(True, result[0])
        self.assertEqual((5, 5, 0), result[1])
        result = ugrid.get_cell_centroid(-1)
        self.assertEqual(False, result[0])

    def test_cellstream(self):
        """Test getting the cellstream."""
        import numpy as np
        xu = self.get_simple_quad_ugrid()
        cellstream = xu.cellstream
        expected_cellstream = np.array((UGrid.cell_type_enum.QUAD, 4, 0, 3, 4, 1,
                                        UGrid.cell_type_enum.QUAD, 4, 1, 4, 5, 2,
                                        UGrid.cell_type_enum.QUAD, 4, 3, 6, 7, 4,
                                        UGrid.cell_type_enum.QUAD, 4, 4, 7, 8, 5))
        np.testing.assert_array_equal(expected_cellstream, cellstream)

    def test_set_cellstream(self):
        """Test setting the cellstream."""
        import numpy as np
        points = np.array(((0, 10, 0), (10, 10, 0), (20, 10, 0), (0, 0, 0), (10, 0, 0),
                           (20, 0, 0), (0, -10, 0), (10, -10, 0), (20, -10, 0)))
        cells = np.array((9, 4, 0, 3, 4, 1, 9, 4, 1, 4, 5, 2, 9, 4, 3, 6, 7, 4, 9, 4, 4, 7, 8, 5))
        xu = UGrid()
        xu.locations = points
        xu.cellstream = cells
        expected_cells = xu.cellstream
        self.assertEqual(len(points), xu.point_count)
        np.testing.assert_array_equal(expected_cells, cells)

    def test_get_cell_cellstream(self):
        """Test getting the cellstream."""
        import numpy as np
        xu = self.get_simple_quad_ugrid()
        ret, cellstream = xu.get_cell_cellstream(0)
        expected_cellstream = np.array((UGrid.cell_type_enum.QUAD, 4, 0, 3, 4, 1))
        np.testing.assert_array_equal(expected_cellstream, cellstream)

    def test_get_cell_adjacent_cells(self):
        """Test getting cells adjacent to a cell."""
        import numpy as np
        xu = self.get_simple_quad_ugrid()

        expected_cells = np.array(())
        retrieved_cells = xu.get_cell_adjacent_cells(-1)
        np.testing.assert_array_equal(expected_cells, retrieved_cells)
        retrieved_cells = xu.get_cell_adjacent_cells(0)
        expected_cells = np.array((2, 1, 3))
        np.testing.assert_array_equal(expected_cells, retrieved_cells)
        expected_cells = np.array(())
        retrieved_cells = xu.get_cell_adjacent_cells(4)
        np.testing.assert_array_equal(expected_cells, retrieved_cells)
        expected_cells = np.array(())
        retrieved_cells = xu.get_cell_adjacent_cells(5)
        np.testing.assert_array_equal(expected_cells, retrieved_cells)

    def test_get_cell_edge_count(self):
        """Test getting cell edge count."""
        xu2d = self.get_2d_linear_ugrid()
        self.assertEqual(-1, xu2d.get_cell_edge_count(-1))
        self.assertEqual(-1, xu2d.get_cell_edge_count(6))
        self.assertEqual(4, xu2d.get_cell_edge_count(0))
        self.assertEqual(4, xu2d.get_cell_edge_count(1))
        self.assertEqual(3, xu2d.get_cell_edge_count(2))
        self.assertEqual(6, xu2d.get_cell_edge_count(3))
        self.assertEqual(2, xu2d.get_cell_edge_count(4))
        self.assertEqual(1, xu2d.get_cell_edge_count(5))

        xu3d = self.get_3d_linear_ugrid()
        self.assertEqual(-1, xu3d.get_cell_edge_count(-1))
        self.assertEqual(-1, xu3d.get_cell_edge_count(6))
        self.assertEqual(6, xu3d.get_cell_edge_count(0))
        self.assertEqual(12, xu3d.get_cell_edge_count(1))
        self.assertEqual(12, xu3d.get_cell_edge_count(2))
        self.assertEqual(12, xu3d.get_cell_edge_count(3))
        self.assertEqual(9, xu3d.get_cell_edge_count(4))
        self.assertEqual(8, xu3d.get_cell_edge_count(5))

    def test_cell_edge(self):
        """Test getting cell edges."""
        xu2d = self.get_simple_quad_ugrid()
        edge0 = (0, 3)
        edge1 = (3, 4)
        edge2 = (4, 1)
        edge3 = (1, 0)
        edge4 = (1, 4)
        edge5 = (4, 5)
        edge6 = (5, 2)
        edge7 = (2, 1)
        edge8 = (3, 6)
        edge9 = (6, 7)
        edge10 = (7, 4)
        edge11 = (4, 3)
        edge12 = (4, 7)
        edge13 = (7, 8)
        edge14 = (8, 5)
        edge15 = (5, 4)

        self.assertEqual(xu2d.get_cell_edge(0, -1), (0, 0))
        self.assertEqual(xu2d.get_cell_edge(0, xu2d.get_cell_edge_count(0)), (0, 0))

        expected_cell_edges = [[edge0, edge1, edge2, edge3],
                               [edge4, edge5, edge6, edge7],
                               [edge8, edge9, edge10, edge11],
                               [edge12, edge13, edge14, edge15]]
        self.assertEqual(len(expected_cell_edges), xu2d.cell_count)
        for i in range(0, xu2d.cell_count):
            self.assertEqual(len(expected_cell_edges[i]), xu2d.get_cell_edge_count(i))
            for j in range(0, xu2d.get_cell_edge_count(i)):
                self.assertEqual(xu2d.get_cell_edge(i, j), expected_cell_edges[i][j])

        edge0 = (0, 1)
        edge1 = (1, 6)
        edge2 = (6, 5)
        edge3 = (5, 0)
        edge4 = (1, 2)
        edge5 = (2, 7)
        edge6 = (7, 6)
        edge7 = (6, 1)
        edge8 = (2, 3)
        edge9 = (3, 7)
        edge10 = (7, 2)
        edge11 = (3, 4)
        edge12 = (4, 8)
        edge13 = (8, 13)
        edge14 = (13, 12)
        edge15 = (12, 7)
        edge16 = (7, 3)
        edge17 = (7, 11)
        edge18 = (11, 10)
        edge19 = (5, 9)

        xu2d = self.get_2d_linear_ugrid()
        expected_cell_edges = [[edge0, edge1, edge2, edge3],
                               [edge4, edge5, edge6, edge7],
                               [edge8, edge9, edge10],
                               [edge11, edge12, edge13, edge14, edge15, edge16],
                               [edge17, edge18],
                               [edge19]]
        self.assertEqual(len(expected_cell_edges), xu2d.cell_count)
        for i in range(0, xu2d.cell_count):
            self.assertEqual(len(expected_cell_edges[i]), xu2d.get_cell_edge_count(i))
            for j in range(0, xu2d.get_cell_edge_count(i)):
                self.assertEqual(expected_cell_edges[i][j], xu2d.get_cell_edge(i, j))

        xu3d = self.get_3d_linear_ugrid()
        expected_cell_edges = [
            [(0, 1), (1, 5), (5, 0), (0, 15), (1, 15), (5, 15)],  # TETRA
            # VOXEL
            [(1, 2), (2, 7), (6, 7), (1, 6), (16, 17), (17, 22), (21, 22), (16, 21), (1, 16), (2, 17), (6, 21),
             (7, 22)],
            # HEXAHEDRON
            [(2, 3), (3, 8), (7, 8), (2, 7), (17, 18), (18, 23), (22, 23), (17, 22), (2, 17), (3, 18), (7, 22),
             (8, 23)],
            # POLYHEDRON
            [(8, 9), (8, 13), (8, 23), (9, 14), (9, 24), (13, 14), (13, 28), (14, 29), (23, 24), (23, 28), (24, 29),
             (28, 29)],
            [(3, 4), (4, 18), (18, 3), (8, 9), (9, 23), (23, 8), (3, 8), (4, 9), (18, 23)],  # WEDGE
            [(5, 6), (6, 11), (11, 10), (10, 5), (5, 20), (6, 20), (11, 20), (10, 20)]  # PYRAMID
        ]

        self.assertEqual(xu3d.cell_count, len(expected_cell_edges))
        for i in range(0, xu3d.cell_count):
            self.assertEqual(len(expected_cell_edges[i]), xu3d.get_cell_edge_count(i))
            for j in range(0, xu3d.get_cell_edge_count(i)):
                self.assertEqual(xu3d.get_cell_edge(i, j), expected_cell_edges[i][j])

    def test_adjacent_cell_functions(self):
        """Test getting cells adjacent to edges."""
        xuquad = self.get_simple_quad_ugrid()
        expected_cells = [(), (2,), (1,), ()]
        expected_2d_cells = [-1, 2, 1, -1]
        for edge_idx in range(0, xuquad.get_cell_edge_count(0)):
            self.assertEqual(expected_cells[edge_idx], xuquad.get_cell_edge_adjacent_cells(0, edge_idx))
            self.assertEqual(expected_2d_cells[edge_idx], xuquad.get_cell_2d_edge_adjacent_cell(0, edge_idx))

        expected_cells_from_edge = [(0, 1), (0, 2), (0,)]
        edges = [(1, 4), (3, 4), (0, 3)]
        for i in range(0, len(edges)):
            self.assertEqual(expected_cells_from_edge[i], xuquad.get_edge_adjacent_cells(edges[i]))

    def test_point_adjacent_get_points_locations(self):
        """Test get_point_adjacent_points and get_point_adjacent_locations."""
        #     0-----1-----2
        #     |  0  |  1  |
        #     3-----4-----5
        #     |  2  |  3  |
        #     6-----7-----8
        import numpy as np
        grid = self.get_simple_quad_ugrid()
        attached_idxs = grid.get_point_adjacent_points(0)
        expected_idxs = (1, 3)
        self.assertEqual(expected_idxs, attached_idxs)
        attached_idxs = grid.get_point_adjacent_points(3)
        expected_idxs = (0, 4, 6)
        self.assertEqual(expected_idxs, attached_idxs)
        attached_idxs = grid.get_point_adjacent_points(4)
        expected_idxs = (1, 3, 5, 7)
        self.assertEqual(expected_idxs, attached_idxs)

        attached_points = grid.get_point_adjacent_locations(0)
        expected_points = np.array(((10, 10, 0), (0, 0, 0)))
        np.testing.assert_array_equal(expected_points, attached_points)
        attached_points = grid.get_point_adjacent_locations(3)
        expected_points = ((0, 10, 0), (10, 0, 0), (0, -10, 0))
        np.testing.assert_array_equal(expected_points, attached_points)
        attached_points = grid.get_point_adjacent_locations(4)
        expected_points = ((10, 10, 0), (0, 0, 0), (20, 0, 0), (10, -10, 0))
        np.testing.assert_array_equal(expected_points, attached_points)

    def test_cell_edges(self):
        """Test getting cell edges."""
        xuquad = self.get_simple_quad_ugrid()
        expected_edges = ((0, 3), (3, 4), (4, 1), (1, 0))
        edges = xuquad.get_cell_edges(0)
        self.assertEqual(expected_edges, edges)

    def test_get_cell_3d_face_count(self):
        """Test getting 3D cell face count."""
        xu2d = self.get_2d_linear_ugrid()
        self.assertEqual(-1, xu2d.get_cell_3d_face_count(-1))
        for i in range(0, xu2d.cell_count):
            self.assertEqual(0, xu2d.get_cell_3d_face_count(i))
        self.assertEqual(-1, xu2d.get_cell_3d_face_count(xu2d.cell_count))

        xu3d = self.get_3d_linear_ugrid()

        self.assertEqual(-1, xu3d.get_cell_3d_face_count(-1))
        self.assertEqual(-1, xu3d.get_cell_3d_face_count(6))
        self.assertEqual(4, xu3d.get_cell_3d_face_count(0))
        self.assertEqual(6, xu3d.get_cell_3d_face_count(1))
        self.assertEqual(6, xu3d.get_cell_3d_face_count(2))
        self.assertEqual(6, xu3d.get_cell_3d_face_count(3))
        self.assertEqual(5, xu3d.get_cell_3d_face_count(4))
        self.assertEqual(5, xu3d.get_cell_3d_face_count(5))

    def test_get_cell_3d_face_point_count(self):
        """Test getting the number of face points for a cell face."""
        xu2d = self.get_2d_linear_ugrid()
        # test 1D and 2D cells - should return 0 for valid cell index
        self.assertEqual(-1, xu2d.get_cell_3d_face_point_count(-1, 0))
        self.assertEqual(0, xu2d.get_cell_3d_face_point_count(1, 0))
        self.assertEqual(-1, xu2d.get_cell_3d_face_point_count(xu2d.cell_count, 0))

        xu3d = self.get_3d_linear_ugrid()

        self.assertEqual(-1, xu3d.get_cell_3d_face_point_count(-1, 0))
        self.assertEqual(-1, xu3d.get_cell_3d_face_point_count(6, 0))
        self.assertEqual(4, xu3d.get_cell_3d_face_point_count(1, 3))
        self.assertEqual(4, xu3d.get_cell_3d_face_point_count(3, 2))

    def test_get_cell_3d_face_points(self):
        """Test getting 3D cell face points."""
        xu2d = self.get_2d_linear_ugrid()
        self.assertEqual((), xu2d.get_cell_3d_face_points(-1, 0))
        self.assertEqual((), xu2d.get_cell_3d_face_points(0, -1))
        for i in range(0, xu2d.cell_count):
            self.assertEqual((), xu2d.get_cell_3d_face_points(i, 0))
        self.assertEqual((), xu2d.get_cell_3d_face_points(xu2d.cell_count, 0))
        self.assertEqual((), xu2d.get_cell_3d_face_points(0, 1))

        xu3d = self.get_3d_linear_ugrid()
        expected_cell_faces = [  # Tetra
            (0, 1, 15),
            (1, 5, 15),
            (5, 0, 15),
            (0, 5, 1),
            # Voxel
            (1, 16, 21, 6),
            (2, 7, 22, 17),
            (1, 2, 17, 16),
            (6, 21, 22, 7),
            (1, 6, 7, 2),
            (16, 17, 22, 21),
            # Hexahedron
            (2, 17, 22, 7),
            (3, 8, 23, 18),
            (2, 3, 18, 17),
            (7, 22, 23, 8),
            (2, 7, 8, 3),
            (17, 18, 23, 22),
            # Polyhedron
            (9, 8, 13, 14),
            (8, 9, 24, 23),
            (9, 14, 29, 24),
            (14, 13, 28, 29),
            (8, 13, 28, 23),
            (23, 24, 29, 28),
            # Wedge
            (3, 4, 18),
            (8, 23, 9),
            (3, 8, 9, 4),
            (4, 9, 23, 18),
            (18, 23, 8, 3),
            # Pyramid
            (5, 10, 11, 6),
            (5, 6, 20),
            (6, 11, 20),
            (11, 10, 20),
            (10, 5, 20)]
        curr_id = 0
        for i in range(0, xu3d.cell_count):
            for j in range(0, xu3d.get_cell_3d_face_count(i)):
                self.assertEqual(xu3d.get_cell_3d_face_points(i, j), expected_cell_faces[curr_id])
                curr_id += 1

    def test_get_faces_of_cell(self):
        """Test getting cell faces."""
        xu3d = self.get_3d_linear_ugrid()
        expected_cell_faces = [  # Tetra
            (0, 1, 15),
            (1, 5, 15),
            (5, 0, 15),
            (0, 5, 1),
            # Voxel
            (1, 16, 21, 6),
            (2, 7, 22, 17),
            (1, 2, 17, 16),
            (6, 21, 22, 7),
            (1, 6, 7, 2),
            (16, 17, 22, 21),
            # Hexahedron
            (2, 17, 22, 7),
            (3, 8, 23, 18),
            (2, 3, 18, 17),
            (7, 22, 23, 8),
            (2, 7, 8, 3),
            (17, 18, 23, 22),
            # Polyhedron
            (9, 8, 13, 14),
            (8, 9, 24, 23),
            (9, 14, 29, 24),
            (14, 13, 28, 29),
            (8, 13, 28, 23),
            (23, 24, 29, 28),
            # Wedge
            (3, 4, 18),
            (8, 23, 9),
            (3, 8, 9, 4),
            (4, 9, 23, 18),
            (18, 23, 8, 3),
            # Pyramid
            (5, 10, 11, 6),
            (5, 6, 20),
            (6, 11, 20),
            (11, 10, 20),
            (10, 5, 20)]
        curr_id = 0
        for i in range(0, xu3d.cell_count):
            faces = xu3d.get_cell_3d_faces_points(i)
            for j in range(0, len(faces)):
                self.assertEqual(faces[j], expected_cell_faces[curr_id])
                curr_id += 1

    def test_get_cell_3d_face_adjacent_cell(self):
        """Test getting 3D cell face adjacent cells."""
        xuhex = self.get_hexahedron_ugrid(3, 2, 2, (0, 0, 0))
        expected_neighbor = [-1, -1, -1, 1, -1, -1, -1, -1, 0, -1, -1, -1]
        self.assertEqual(-1, xuhex.get_cell_3d_face_adjacent_cell(-1, 0))
        self.assertEqual(-1, xuhex.get_cell_3d_face_adjacent_cell(0, -1))
        neighbor = []
        for i in range(0, xuhex.cell_count):
            for j in range(0, xuhex.get_cell_3d_face_count(i)):
                neighbor.append(xuhex.get_cell_3d_face_adjacent_cell(i, j))
        self.assertEqual(expected_neighbor, neighbor)
        self.assertEqual(-1, xuhex.get_cell_3d_face_adjacent_cell(xuhex.cell_count, 0))
        self.assertEqual(-1, xuhex.get_cell_3d_face_adjacent_cell(0, xuhex.cell_count))

        xuhex = self.get_hexahedron_ugrid(3, 3, 3, (0, 0, 0))
        expected_neighbor = [-1, 1, -1, 2, -1, 4, 0, -1, -1, 3, -1, 5, -1, 3, 0, -1, -1, 6, 2, -1, 1, -1, -1, 7, -1, 5,
                             -1, 6, 0, -1, 4, -1, -1, 7, 1, -1, -1, 7, 4, -1, 2, -1, 6, -1, 5, -1, 3, -1]
        neighbor = []
        for i in range(0, xuhex.cell_count):
            for j in range(0, xuhex.get_cell_3d_face_count(i)):
                neighbor.append(xuhex.get_cell_3d_face_adjacent_cell(i, j))
        self.assertEqual(expected_neighbor, neighbor)

    def test_is_valid_point_change(self):
        """Test point change validation."""
        #     0-----1-----2
        #     |  0  |  1  |
        #     3-----4-----5
        #     |  2  |  3  |
        #     6-----7-----8

        ugrid = self.get_simple_quad_ugrid()

        valid_pt = (5.0, 5.0, 0.0)
        invalid = (500.0, 500.0, 0.0)

        self.assertTrue(ugrid.is_valid_point_change(4, valid_pt))
        self.assertFalse(ugrid.is_valid_point_change(4, invalid))

        ugrid3d = self.get_hexahedron_ugrid(4, 4, 4, (0.0, 0.0, 0.0))

        valid_pt = ugrid3d.get_point_location(21)
        valid_pt = (valid_pt[0] + 0.05, valid_pt[1] + 0.05, valid_pt[2] + 0.05)
        self.assertTrue(ugrid3d.is_valid_point_change(21, valid_pt))
        self.assertFalse(ugrid3d.is_valid_point_change(21, invalid))

        self.assertTrue(ugrid.set_point_location(4, valid_pt))
        self.assertTrue(ugrid.set_point_location(4, invalid))
        self.assertTrue(ugrid3d.set_point_location(21, valid_pt))
        self.assertTrue(ugrid3d.set_point_location(21, invalid))

    def test_cell_3d_face_functions(self):
        """Test 3D cell face functions."""
        # 3D Shapes
        ugrid3d = self.get_3d_linear_ugrid()
        expected_cell_faces = ((0, 1, 15),  # Tetra
                               (1, 5, 15),
                               (5, 0, 15),
                               (0, 5, 1),
                               # Voxel
                               (1, 16, 21, 6),
                               (2, 7, 22, 17),
                               (1, 2, 17, 16),
                               (6, 21, 22, 7),
                               (1, 6, 7, 2),
                               (16, 17, 22, 21),
                               # Hexahedron
                               (2, 17, 22, 7),
                               (3, 8, 23, 18),
                               (2, 3, 18, 17),
                               (7, 22, 23, 8),
                               (2, 7, 8, 3),
                               (17, 18, 23, 22),
                               # Polyhedron
                               (9, 8, 13, 14),
                               (8, 9, 24, 23),
                               (9, 14, 29, 24),
                               (14, 13, 28, 29),
                               (8, 13, 28, 23),
                               (23, 24, 29, 28),
                               # Wedge
                               (3, 4, 18),
                               (8, 23, 9),
                               (3, 8, 9, 4),
                               (4, 9, 23, 18),
                               (18, 23, 8, 3),
                               # Pyramid
                               (5, 10, 11, 6),
                               (5, 6, 20),
                               (6, 11, 20),
                               (11, 10, 20),
                               (10, 5, 20))
        expected_idx = 0
        for cell_idx in range(0, ugrid3d.cell_count):
            for face_idx in range(0, ugrid3d.get_cell_3d_face_count(cell_idx)):
                face_points = ugrid3d.get_cell_3d_face_points(cell_idx, face_idx)
                self.assertEqual(expected_cell_faces[expected_idx], face_points)
                expected_idx += 1

        expected_idx = 0
        for cell_idx in range(0, ugrid3d.cell_count):
            faces_points = ugrid3d.get_cell_3d_faces_points(cell_idx)
            self.assertEqual(len(faces_points), ugrid3d.get_cell_3d_face_count(cell_idx))
            for face_idx in range(0, ugrid3d.get_cell_3d_face_count(cell_idx)):
                self.assertEqual(expected_cell_faces[expected_idx], faces_points[face_idx])
                expected_idx += 1

        orientation = []
        for cell_idx in range(0, ugrid3d.cell_count):
            for face_idx in range(0, ugrid3d.get_cell_3d_face_count(cell_idx)):
                orientation.append(ugrid3d.get_cell_3d_face_orientation(cell_idx, face_idx))

        expected_orientation = [UGrid.face_orientation_enum.ORIENTATION_SIDE,  # Tetra
                                UGrid.face_orientation_enum.ORIENTATION_TOP,
                                UGrid.face_orientation_enum.ORIENTATION_SIDE,
                                UGrid.face_orientation_enum.ORIENTATION_BOTTOM,
                                # Voxel
                                UGrid.face_orientation_enum.ORIENTATION_SIDE,
                                UGrid.face_orientation_enum.ORIENTATION_SIDE,
                                UGrid.face_orientation_enum.ORIENTATION_SIDE,
                                UGrid.face_orientation_enum.ORIENTATION_SIDE,
                                UGrid.face_orientation_enum.ORIENTATION_BOTTOM,
                                UGrid.face_orientation_enum.ORIENTATION_TOP,
                                # Hexahedron
                                UGrid.face_orientation_enum.ORIENTATION_SIDE,
                                UGrid.face_orientation_enum.ORIENTATION_SIDE,
                                UGrid.face_orientation_enum.ORIENTATION_SIDE,
                                UGrid.face_orientation_enum.ORIENTATION_SIDE,
                                UGrid.face_orientation_enum.ORIENTATION_BOTTOM,
                                UGrid.face_orientation_enum.ORIENTATION_TOP,
                                # Polyhedron
                                UGrid.face_orientation_enum.ORIENTATION_BOTTOM,
                                UGrid.face_orientation_enum.ORIENTATION_SIDE,
                                UGrid.face_orientation_enum.ORIENTATION_SIDE,
                                UGrid.face_orientation_enum.ORIENTATION_SIDE,
                                UGrid.face_orientation_enum.ORIENTATION_SIDE,
                                UGrid.face_orientation_enum.ORIENTATION_TOP,
                                # Wedge
                                UGrid.face_orientation_enum.ORIENTATION_SIDE,
                                UGrid.face_orientation_enum.ORIENTATION_SIDE,
                                UGrid.face_orientation_enum.ORIENTATION_BOTTOM,
                                UGrid.face_orientation_enum.ORIENTATION_TOP,
                                UGrid.face_orientation_enum.ORIENTATION_SIDE,
                                # Pyramid
                                UGrid.face_orientation_enum.ORIENTATION_BOTTOM,
                                UGrid.face_orientation_enum.ORIENTATION_SIDE,
                                UGrid.face_orientation_enum.ORIENTATION_TOP,
                                UGrid.face_orientation_enum.ORIENTATION_TOP,
                                UGrid.face_orientation_enum.ORIENTATION_SIDE]

        self.assertEqual(expected_orientation, orientation)

    def test_get_cell_3d_face_orientation(self):
        """Test getting 3D cell face orientation."""
        # vertically prismatic concave cell
        nodes = ((1620022.8468, 6134363.759, 0), (1620009.9411, 6134414.9476, 0),
                 (1619994.9996, 6134289.4991, 0), (1619866.1047, 6134542.8755, 0),
                 (1619745.5374, 6134167.0467, 0), (1619829.9996, 6134192.9991, 0),
                 (1619773.3077, 6134545.2322, 0), (1619710.0815, 6134182.8542, 0),
                 (1619693.1618, 6134208.2547, 0), (1619645.5529, 6134438.0278, 0),
                 (1619774.9993, 6134371.9982, 0), (1620022.8468, 6134363.759, -10),
                 (1620009.9411, 6134414.9476, -10), (1619994.9996, 6134289.4991, -10),
                 (1619866.1047, 6134542.8755, -10), (1619745.5374, 6134167.0467, -10),
                 (1619829.9996, 6134192.9991, -10), (1619773.3077, 6134545.2322, -10),
                 (1619710.0815, 6134182.8542, -10), (1619693.1618, 6134208.2547, -10),
                 (1619645.5529, 6134438.0278, -10), (1619774.9993, 6134371.9982, -10))
        elements = (
            UGrid.cell_type_enum.POLYHEDRON,
            13,  # number of faces
            11, 5, 10, 2, 0, 1, 3, 6, 9, 8, 7, 4,  # top
            11, 16, 15, 18, 19, 20, 17, 14, 12, 11, 13, 21,  # bottom
            4, 5, 16, 21, 10,  # sides
            4, 10, 21, 13, 2,
            4, 2, 13, 11, 0,
            4, 0, 11, 12, 1,
            4, 1, 12, 14, 3,
            4, 3, 14, 17, 6,
            4, 6, 17, 20, 9,
            4, 9, 20, 19, 8,
            4, 8, 19, 18, 7,
            4, 7, 18, 15, 4,
            4, 4, 1, 16, 5)

        ugrid = UGrid(nodes, elements)
        actual = []
        for face_idx in range(0, ugrid.get_cell_3d_face_count(0)):
            actual.append(ugrid.get_cell_3d_face_orientation(0, face_idx))
        expected = [UGrid.face_orientation_enum.ORIENTATION_TOP,
                    UGrid.face_orientation_enum.ORIENTATION_BOTTOM,
                    UGrid.face_orientation_enum.ORIENTATION_SIDE,
                    UGrid.face_orientation_enum.ORIENTATION_SIDE,
                    UGrid.face_orientation_enum.ORIENTATION_SIDE,
                    UGrid.face_orientation_enum.ORIENTATION_SIDE,
                    UGrid.face_orientation_enum.ORIENTATION_SIDE,
                    UGrid.face_orientation_enum.ORIENTATION_SIDE,
                    UGrid.face_orientation_enum.ORIENTATION_SIDE,
                    UGrid.face_orientation_enum.ORIENTATION_SIDE,
                    UGrid.face_orientation_enum.ORIENTATION_SIDE,
                    UGrid.face_orientation_enum.ORIENTATION_SIDE,
                    UGrid.face_orientation_enum.ORIENTATION_SIDE]
        self.assertEqual(expected, actual)

    def test_cell_3d_function_caching(self):
        """Test 3D cell function caching."""
        ugrid = self.get_hexahedron_ugrid(2, 3, 2, (0, 0, 0))

        expected_neighbors = [[-1, 1, -1, -1, -1, -1],
                              [0, -1, -1, -1, -1, -1]]
        expected_orientations = ((UGrid.face_orientation_enum.ORIENTATION_SIDE,
                                  UGrid.face_orientation_enum.ORIENTATION_SIDE,
                                  UGrid.face_orientation_enum.ORIENTATION_SIDE,
                                  UGrid.face_orientation_enum.ORIENTATION_SIDE,
                                  UGrid.face_orientation_enum.ORIENTATION_TOP,
                                  UGrid.face_orientation_enum.ORIENTATION_BOTTOM),
                                 (UGrid.face_orientation_enum.ORIENTATION_SIDE,
                                  UGrid.face_orientation_enum.ORIENTATION_SIDE,
                                  UGrid.face_orientation_enum.ORIENTATION_SIDE,
                                  UGrid.face_orientation_enum.ORIENTATION_SIDE,
                                  UGrid.face_orientation_enum.ORIENTATION_TOP,
                                  UGrid.face_orientation_enum.ORIENTATION_BOTTOM))

        # test four times, to fill the cache, read from the cache, turn off the cache,
        # and turn on the cache
        use_cache_values = (True, True, False, True)
        for i in range(0, 4):
            ugrid.use_cache(use_cache_values[i])
            neighbors = []
            for cell_idx in range(0, ugrid.cell_count):
                self.assertEqual(6, ugrid.get_cell_3d_face_count(cell_idx))
                cell_neighbors = []
                for face_idx in range(0, ugrid.get_cell_3d_face_count(cell_idx)):
                    cell_neighbors.append(ugrid.get_cell_3d_face_adjacent_cell(cell_idx, face_idx))
                    orientation = ugrid.get_cell_3d_face_orientation(cell_idx, face_idx)
                    self.assertEqual(expected_orientations[cell_idx][face_idx], orientation)
                neighbors.append(cell_neighbors)
            self.assertEqual(expected_neighbors, neighbors)

        # change to different points and cells and test again
        expected_neighbors = [[-1, 1, -1, -1, -1, -1],
                              [0, 2, -1, -1, -1, -1],
                              [1, -1, -1, -1, -1, -1]]
        expected_orientations = ((UGrid.face_orientation_enum.ORIENTATION_SIDE,
                                  UGrid.face_orientation_enum.ORIENTATION_SIDE,
                                  UGrid.face_orientation_enum.ORIENTATION_SIDE,
                                  UGrid.face_orientation_enum.ORIENTATION_SIDE,
                                  UGrid.face_orientation_enum.ORIENTATION_TOP,
                                  UGrid.face_orientation_enum.ORIENTATION_BOTTOM),
                                 (UGrid.face_orientation_enum.ORIENTATION_SIDE,
                                  UGrid.face_orientation_enum.ORIENTATION_SIDE,
                                  UGrid.face_orientation_enum.ORIENTATION_SIDE,
                                  UGrid.face_orientation_enum.ORIENTATION_SIDE,
                                  UGrid.face_orientation_enum.ORIENTATION_TOP,
                                  UGrid.face_orientation_enum.ORIENTATION_BOTTOM),
                                 (UGrid.face_orientation_enum.ORIENTATION_SIDE,
                                  UGrid.face_orientation_enum.ORIENTATION_SIDE,
                                  UGrid.face_orientation_enum.ORIENTATION_SIDE,
                                  UGrid.face_orientation_enum.ORIENTATION_SIDE,
                                  UGrid.face_orientation_enum.ORIENTATION_TOP,
                                  UGrid.face_orientation_enum.ORIENTATION_BOTTOM))
        new_ugrid = self.get_hexahedron_ugrid(2, 4, 2, (0, 0, 0))
        ugrid.locations = new_ugrid.locations
        ugrid.cellstream = new_ugrid.cellstream
        for i in range(0, 4):
            ugrid.use_cache(use_cache_values[i])
            neighbors = []
            for cell_idx in range(0, ugrid.cell_count):
                self.assertEqual(6, ugrid.get_cell_3d_face_count(cell_idx))
                cell_neighbors = []
                for face_idx in range(0, ugrid.get_cell_3d_face_count(cell_idx)):
                    cell_neighbors.append(ugrid.get_cell_3d_face_adjacent_cell(cell_idx, face_idx))
                    orientation = ugrid.get_cell_3d_face_orientation(cell_idx, face_idx)
                    self.assertEqual(expected_orientations[cell_idx][face_idx], orientation)
                neighbors.append(cell_neighbors)
            self.assertEqual(expected_neighbors, neighbors)

    def test_cell_ordering(self):
        """Test cell ordering bindings."""
        ugrid = self.get_hexahedron_ugrid(4, 3, 3, (0, 0, 0))
        self.assertEqual(UGrid.cell_ordering_enum.CELL_ORDER_INCREASING_DOWN, ugrid.get_cell_ordering())
        ugrid.set_cell_ordering(UGrid.cell_ordering_enum.CELL_ORDER_UNKNOWN)
        self.assertEqual(UGrid.cell_ordering_enum.CELL_ORDER_INCREASING_DOWN, ugrid.calculate_cell_ordering())
        ugrid.set_cell_ordering(UGrid.cell_ordering_enum.CELL_ORDER_INCREASING_UP)
        self.assertEqual(UGrid.cell_ordering_enum.CELL_ORDER_INCREASING_UP, ugrid.get_cell_ordering())


class TestUGridCellTypeEnum(unittest.TestCase):
    """CellType enum tests."""

    def test_ugrid_celltype_enum(self):
        """Test the UGrid cell_type_enum enum."""
        from xms.grid.ugrid import UGrid
        self.assertEqual("ugrid_celltype_enum.INVALID_CELL_TYPE",
                         str(UGrid.cell_type_enum.INVALID_CELL_TYPE))
        self.assertEqual("ugrid_celltype_enum.EMPTY_CELL", str(UGrid.cell_type_enum.EMPTY_CELL))
        self.assertEqual("ugrid_celltype_enum.VERTEX", str(UGrid.cell_type_enum.VERTEX))
        self.assertEqual("ugrid_celltype_enum.POLY_VERTEX", str(UGrid.cell_type_enum.POLY_VERTEX))
        self.assertEqual("ugrid_celltype_enum.LINE", str(UGrid.cell_type_enum.LINE))
        self.assertEqual("ugrid_celltype_enum.POLY_LINE", str(UGrid.cell_type_enum.POLY_LINE))
        self.assertEqual("ugrid_celltype_enum.TRIANGLE", str(UGrid.cell_type_enum.TRIANGLE))
        self.assertEqual("ugrid_celltype_enum.TRIANGLE_STRIP",
                         str(UGrid.cell_type_enum.TRIANGLE_STRIP))
        self.assertEqual("ugrid_celltype_enum.POLYGON", str(UGrid.cell_type_enum.POLYGON))
        self.assertEqual("ugrid_celltype_enum.PIXEL", str(UGrid.cell_type_enum.PIXEL))
        self.assertEqual("ugrid_celltype_enum.QUAD", str(UGrid.cell_type_enum.QUAD))
        self.assertEqual("ugrid_celltype_enum.TETRA", str(UGrid.cell_type_enum.TETRA))
        self.assertEqual("ugrid_celltype_enum.VOXEL", str(UGrid.cell_type_enum.VOXEL))
        self.assertEqual("ugrid_celltype_enum.HEXAHEDRON", str(UGrid.cell_type_enum.HEXAHEDRON))
        self.assertEqual("ugrid_celltype_enum.WEDGE", str(UGrid.cell_type_enum.WEDGE))
        self.assertEqual("ugrid_celltype_enum.PYRAMID", str(UGrid.cell_type_enum.PYRAMID))
        self.assertEqual("ugrid_celltype_enum.PENTAGONAL_PRISM",
                         str(UGrid.cell_type_enum.PENTAGONAL_PRISM))
        self.assertEqual("ugrid_celltype_enum.HEXAGONAL_PRISM",
                         str(UGrid.cell_type_enum.HEXAGONAL_PRISM))
        self.assertEqual("ugrid_celltype_enum.QUADRATIC_EDGE",
                         str(UGrid.cell_type_enum.QUADRATIC_EDGE))
        self.assertEqual("ugrid_celltype_enum.QUADRATIC_TRIANGLE",
                         str(UGrid.cell_type_enum.QUADRATIC_TRIANGLE))
        self.assertEqual("ugrid_celltype_enum.QUADRATIC_QUAD",
                         str(UGrid.cell_type_enum.QUADRATIC_QUAD))
        self.assertEqual("ugrid_celltype_enum.QUADRATIC_POLYGON",
                         str(UGrid.cell_type_enum.QUADRATIC_POLYGON))
        self.assertEqual("ugrid_celltype_enum.QUADRATIC_TETRA",
                         str(UGrid.cell_type_enum.QUADRATIC_TETRA))
        self.assertEqual("ugrid_celltype_enum.QUADRATIC_HEXAHEDRON",
                         str(UGrid.cell_type_enum.QUADRATIC_HEXAHEDRON))
        self.assertEqual("ugrid_celltype_enum.QUADRATIC_WEDGE",
                         str(UGrid.cell_type_enum.QUADRATIC_WEDGE))
        self.assertEqual("ugrid_celltype_enum.QUADRATIC_PYRAMID",
                         str(UGrid.cell_type_enum.QUADRATIC_PYRAMID))
        self.assertEqual("ugrid_celltype_enum.BIQUADRATIC_QUAD",
                         str(UGrid.cell_type_enum.BIQUADRATIC_QUAD))
        self.assertEqual("ugrid_celltype_enum.TRIQUADRATIC_HEXAHEDRON",
                         str(UGrid.cell_type_enum.TRIQUADRATIC_HEXAHEDRON))
        self.assertEqual("ugrid_celltype_enum.QUADRATIC_LINEAR_QUAD",
                         str(UGrid.cell_type_enum.QUADRATIC_LINEAR_QUAD))
        self.assertEqual("ugrid_celltype_enum.QUADRATIC_LINEAR_WEDGE",
                         str(UGrid.cell_type_enum.QUADRATIC_LINEAR_WEDGE))
        self.assertEqual("ugrid_celltype_enum.BIQUADRATIC_QUADRATIC_WEDGE",
                         str(UGrid.cell_type_enum.BIQUADRATIC_QUADRATIC_WEDGE))
        self.assertEqual("ugrid_celltype_enum.BIQUADRATIC_QUADRATIC_HEXAHEDRON",
                         str(UGrid.cell_type_enum.BIQUADRATIC_QUADRATIC_HEXAHEDRON))
        self.assertEqual("ugrid_celltype_enum.BIQUADRATIC_TRIANGLE",
                         str(UGrid.cell_type_enum.BIQUADRATIC_TRIANGLE))
        self.assertEqual("ugrid_celltype_enum.CUBIC_LINE", str(UGrid.cell_type_enum.CUBIC_LINE))
        self.assertEqual("ugrid_celltype_enum.CONVEX_POINT_SET",
                         str(UGrid.cell_type_enum.CONVEX_POINT_SET))
        self.assertEqual("ugrid_celltype_enum.POLYHEDRON",
                         str(UGrid.cell_type_enum.POLYHEDRON))
        self.assertEqual("ugrid_celltype_enum.PARAMETRIC_CURVE",
                         str(UGrid.cell_type_enum.PARAMETRIC_CURVE))
        self.assertEqual("ugrid_celltype_enum.PARAMETRIC_SURFACE",
                         str(UGrid.cell_type_enum.PARAMETRIC_SURFACE))
        self.assertEqual("ugrid_celltype_enum.PARAMETRIC_TRI_SURFACE",
                         str(UGrid.cell_type_enum.PARAMETRIC_TRI_SURFACE))
        self.assertEqual("ugrid_celltype_enum.PARAMETRIC_QUAD_SURFACE",
                         str(UGrid.cell_type_enum.PARAMETRIC_QUAD_SURFACE))
        self.assertEqual("ugrid_celltype_enum.PARAMETRIC_TETRA_REGION",
                         str(UGrid.cell_type_enum.PARAMETRIC_TETRA_REGION))
        self.assertEqual("ugrid_celltype_enum.PARAMETRIC_HEX_REGION",
                         str(UGrid.cell_type_enum.PARAMETRIC_HEX_REGION))
        self.assertEqual("ugrid_celltype_enum.HIGHER_ORDER_EDGE",
                         str(UGrid.cell_type_enum.HIGHER_ORDER_EDGE))
        self.assertEqual("ugrid_celltype_enum.HIGHER_ORDER_TRIANGLE",
                         str(UGrid.cell_type_enum.HIGHER_ORDER_TRIANGLE))
        self.assertEqual("ugrid_celltype_enum.HIGHER_ORDER_QUAD",
                         str(UGrid.cell_type_enum.HIGHER_ORDER_QUAD))
        self.assertEqual("ugrid_celltype_enum.HIGHER_ORDER_POLYGON",
                         str(UGrid.cell_type_enum.HIGHER_ORDER_POLYGON))
        self.assertEqual("ugrid_celltype_enum.HIGHER_ORDER_TETRAHEDRON",
                         str(UGrid.cell_type_enum.HIGHER_ORDER_TETRAHEDRON))
        self.assertEqual("ugrid_celltype_enum.HIGHER_ORDER_WEDGE",
                         str(UGrid.cell_type_enum.HIGHER_ORDER_WEDGE))
        self.assertEqual("ugrid_celltype_enum.HIGHER_ORDER_PYRAMID",
                         str(UGrid.cell_type_enum.HIGHER_ORDER_PYRAMID))
        self.assertEqual("ugrid_celltype_enum.HIGHER_ORDER_HEXAHEDRON",
                         str(UGrid.cell_type_enum.HIGHER_ORDER_HEXAHEDRON))
        self.assertEqual("ugrid_celltype_enum.NUMBER_OF_CELL_TYPES",
                         str(UGrid.cell_type_enum.NUMBER_OF_CELL_TYPES))
        self.assertEqual(51, len(UGrid.cell_type_enum.__members__))


class TestUGridCellOrderingEnum(unittest.TestCase):
    """CellOrdering enum tests."""

    def test_ugrid_cell_ordering_enum(self):
        """Test the UGrid CellOrdering enum."""
        from xms.grid.ugrid import UGrid
        self.assertEqual("ugrid_cell_ordering_enum.CELL_ORDER_UNKNOWN",
                         str(UGrid.cell_ordering_enum.CELL_ORDER_UNKNOWN))
        self.assertEqual("ugrid_cell_ordering_enum.CELL_ORDER_INCREASING_DOWN",
                         str(UGrid.cell_ordering_enum.CELL_ORDER_INCREASING_DOWN))
        self.assertEqual("ugrid_cell_ordering_enum.CELL_ORDER_INCREASING_UP",
                         str(UGrid.cell_ordering_enum.CELL_ORDER_INCREASING_UP))


class TestUGridFaceOrientationEnum(unittest.TestCase):
    """FaceOrientation enum tests."""

    def test_ugrid_faceorientation_enum(self):
        """Test the UGrid FaceOrientation enum."""
        from xms.grid.ugrid import UGrid
        self.assertEqual("ugrid_faceorientation_enum.ORIENTATION_UNKNOWN",
                         str(UGrid.face_orientation_enum.ORIENTATION_UNKNOWN))
        self.assertEqual("ugrid_faceorientation_enum.ORIENTATION_SIDE",
                         str(UGrid.face_orientation_enum.ORIENTATION_SIDE))
        self.assertEqual("ugrid_faceorientation_enum.ORIENTATION_TOP",
                         str(UGrid.face_orientation_enum.ORIENTATION_TOP))
        self.assertEqual("ugrid_faceorientation_enum.ORIENTATION_BOTTOM",
                         str(UGrid.face_orientation_enum.ORIENTATION_BOTTOM))
        self.assertEqual(4, len(UGrid.face_orientation_enum.__members__))
