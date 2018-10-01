"""Test XmUGrid_py.cpp"""
import unittest
import xmsgrid_py
from xmsgrid_py.ugrid import XmUGrid


class TestXmUGridPointFunctions(unittest.TestCase):
    """XmUGrid Point Functions tests"""

    @staticmethod
    def get_simple_quad_ugrid():
        import numpy as np
        points = np.array(((0, 10, 0), (10, 10, 0), (20, 10, 0), (0, 0, 0), (10, 0, 0),
                           (20, 0, 0), (0, -10, 0), (10, -10, 0), (20, -10, 0)))
        cells = np.array((9, 4, 0, 3, 4, 1, 9, 4, 1, 4, 5, 2, 9, 4, 3, 6, 7, 4, 9, 4, 4, 7, 8, 5))
        xu = XmUGrid(points, cells)
        return xu

    @staticmethod
    def get_2d_linear_ugrid():
        points = ((0, 0, 0), (10, 0, 0), (20, 0, 0), (30, 0, 0), (40, 0, 0),
                  (0, 10, 0), (10, 10, 0), (20, 10, 0), (40, 10, 0), (0, 20, 0),
                  (10, 20, 0), (20, 20, 0), (30, 20, 0), (40, 20, 0))
        cells = (XmUGrid.xmugrid_celltype_enum.XMU_QUAD, 4, 0, 1, 6, 5,
                 XmUGrid.xmugrid_celltype_enum.XMU_PIXEL, 4, 1, 2, 6, 7,
                 XmUGrid.xmugrid_celltype_enum.XMU_TRIANGLE, 3, 2, 3, 7,
                 XmUGrid.xmugrid_celltype_enum.XMU_POLYGON, 6, 3, 4, 8, 13, 12, 7,
                 XmUGrid.xmugrid_celltype_enum.XMU_POLY_LINE, 3, 7, 11, 10,
                 XmUGrid.xmugrid_celltype_enum.XMU_LINE, 2, 5, 9)
        xu = XmUGrid(points, cells)
        return xu

    @staticmethod
    def get_3d_linear_ugrid():
        points = ((0, 0, 0), (10, 0, 0), (20, 0, 0), (30, 0, 0), (40, 0, 0),
                  (0, 10, 0), (10, 10, 0), (20, 10, 0), (30, 10, 0), (40, 10, 0),
                  (0, 20, 0), (10, 20, 0), (20, 20, 0), (30, 20, 0), (40, 20, 0),
                  (0, 0, 10), (10, 0, 10), (20, 0, 10), (30, 0, 10), (40, 0, 10),
                  (0, 10, 10), (10, 10, 10), (20, 10, 10), (30, 10, 10), (40, 10, 10),
                  (0, 20, 10), (10, 20, 10), (20, 20, 10), (30, 20, 10), (40, 20, 10))
        cells = (XmUGrid.xmugrid_celltype_enum.XMU_TETRA, 4, 0, 1, 5, 15,
                 XmUGrid.xmugrid_celltype_enum.XMU_VOXEL, 8, 1, 2, 6, 7, 16, 17, 21, 22,
                 XmUGrid.xmugrid_celltype_enum.XMU_HEXAHEDRON, 8, 2, 3, 8, 7, 17, 18, 23, 22,
                 XmUGrid.xmugrid_celltype_enum.XMU_POLYHEDRON, 6,
                 4, 8, 9, 14, 13,
                 4, 8, 9, 24, 23,
                 4, 9, 14, 29, 24,
                 4, 13, 14, 29, 28,
                 4, 8, 13, 28, 23,
                 4, 23, 24, 29, 28,
                 XmUGrid.xmugrid_celltype_enum.XMU_WEDGE, 6, 3, 4, 18, 8, 9, 23,
                 XmUGrid.xmugrid_celltype_enum.XMU_PYRAMID, 5, 5, 6, 11, 10, 20)
        xu = XmUGrid(points, cells)
        return xu

    @staticmethod
    def get_hexahedron_ugrid(rows, cols, lays, origin):
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
                    cells[curr_id] = XmUGrid.xmugrid_celltype_enum.XMU_HEXAHEDRON
                    cells[curr_id + 1] = 8
                    cells[curr_id + 2] = j + cols * i + lay_offset
                    cells[curr_id + 3] = j + cols * (i + 1) + lay_offset
                    cells[curr_id + 4] = j + 1 + cols * (i + 1) + lay_offset
                    cells[curr_id + 5] = j + 1 + cols * i + lay_offset
                    cells[curr_id + 6] = j + cols * i + lay_offset + num_in_layer
                    cells[curr_id + 7] = j + cols * (i + 1) + lay_offset + num_in_layer
                    cells[curr_id + 8] = j + 1 + cols * (i + 1) + lay_offset + num_in_layer
                    cells[curr_id + 9] = j + 1 + cols * i + lay_offset + num_in_layer
                    curr_id += 10
        xu = XmUGrid(points, cells)
        return xu

    def test_xmugrid_new_default(self):
        xu = XmUGrid()
        self.assertIsInstance(xu, XmUGrid)

    def test_xmugrid_new(self):
        points = ((0, 0, 0), (20, 0, 0), (0, 20, 0))
        cells = (5, 3, 0, 1, 2)
        xu = XmUGrid(points, cells)
        self.assertIsInstance(xu, XmUGrid)

    def test_xmugrid_new_numpy(self):
        import numpy as np
        points = np.array(((0, 0, 0), (20, 0, 0), (0, 20, 0)))
        cells = np.array((5, 3, 0, 1, 2))
        xu = XmUGrid(points, cells)
        self.assertIsInstance(xu, XmUGrid)

    def test_xmugrid_get_number_of_points(self):
        points = ((0, 0, 0), (20, 0, 0), (0, 20, 0))
        cells = (5, 3, 0, 1, 2)
        xu = XmUGrid(points, cells)
        num_points_base = len(points)
        self.assertEqual(num_points_base, xu.get_number_of_points())

    def test_xmugrid_get_points(self):
        import numpy as np
        points = ((0, 0, 0), (20, 0, 0), (0, 20, 0))
        cells = (5, 3, 0, 1, 2)
        xu = XmUGrid(points, cells)
        points_out = xu.get_points()
        np.testing.assert_array_equal(np.array(points), points_out)

    def test_xmugrid_set_points(self):
        import numpy as np
        points = ((0, 0, 0), (20, 0, 0), (0, 20, 0))
        xu = XmUGrid()
        self.assertEqual(0, xu.get_number_of_points())  # Should be empty
        xu.set_points(points)
        num_points_base = len(points)
        self.assertEqual(num_points_base, xu.get_number_of_points())
        points_out = xu.get_points()
        np.testing.assert_array_equal(np.array(points), points_out)

    def test_xmugrid_set_points_numpy(self):
        import numpy as np
        points = np.array(((0, 0, 0), (20, 0, 0), (0, 20, 0)))
        xu = XmUGrid()
        self.assertEqual(0, xu.get_number_of_points())  # Should be empty
        xu.set_points(points)
        num_points_base = len(points)
        self.assertEqual(num_points_base, xu.get_number_of_points())
        points_out = xu.get_points()
        np.testing.assert_array_equal(np.array(points), points_out)

    def test_xmugrid_get_point(self):
        points = ((0, 0, 0), (20, 0, 0), (0, 20, 0))
        cells = (5, 3, 0, 1, 2)
        xu = XmUGrid(points, cells)
        p1 = xu.get_point(0)
        p2 = xu.get_point(1)
        p3 = xu.get_point(2)
        p4 = xu.get_point(3)
        self.assertEqual((0, 0, 0), p1)
        self.assertEqual((20, 0, 0), p2)
        self.assertEqual((0, 20, 0), p3)
        self.assertEqual((0, 0, 0), p4)

    def test_xmugrid_get_xy_point(self):
        points = ((0, 0, 2), (20, 0, 1), (0, 20, 0))
        cells = (5, 3, 0, 1, 2)
        xu = XmUGrid(points, cells)
        p1 = xu.get_xy_point(0)
        p2 = xu.get_xy_point(1)
        p3 = xu.get_xy_point(2)
        p4 = xu.get_xy_point(3)
        self.assertEqual((0, 0, 0), p1)
        self.assertEqual((20, 0, 0), p2)
        self.assertEqual((0, 20, 0), p3)
        self.assertEqual((0, 0, 0), p4)

    def test_xmugrid_set_point(self):
        points = ((0, 10, 0), (10, 10, 0), (20, 10, 0), (0, 0, 0), (10, 0, 0),
                  (20, 0, 0), (0, -10, 0), (10, -10, 0), (20, -10, 0))
        cells = (9, 4, 0, 3, 4, 1, 9, 4, 1, 4, 5, 2, 9, 4, 3, 6, 7, 4, 9, 4, 4, 7, 8, 5)
        xu = XmUGrid(points, cells)
        self.assertFalse(xu.set_point(-1, (0, 0, 0)))
        self.assertFalse(xu.set_point(len(points), (0, 0, 0)))
        self.assertTrue(xu.set_point(0, (-10, -10, 0)))
        self.assertEqual((-10, -10, 0), xu.get_point(0))

    def test_xmugrid_set_point_numpy(self):
        import numpy as np
        points = np.array(((0, 10, 0), (10, 10, 0), (20, 10, 0), (0, 0, 0), (10, 0, 0),
                           (20, 0, 0), (0, -10, 0), (10, -10, 0), (20, -10, 0)))
        cells = np.array((9, 4, 0, 3, 4, 1, 9, 4, 1, 4, 5, 2, 9, 4, 3, 6, 7, 4, 9, 4, 4, 7, 8, 5))
        xu = XmUGrid(points, cells)
        self.assertFalse(xu.set_point(-1, (0, 0, 0)))
        self.assertFalse(xu.set_point(len(points), (0, 0, 0)))
        self.assertTrue(xu.set_point(0, (-10, -10, 0)))
        self.assertEqual((-10, -10, 0), xu.get_point(0))

    def test_xmugrid_get_points_from_point_indxs(self):
        import numpy as np
        points = np.array(((0, 10, 0), (10, 10, 0), (20, 10, 0), (0, 0, 0), (10, 0, 0),
                           (20, 0, 0), (0, -10, 0), (10, -10, 0), (20, -10, 0)))
        cells = np.array((9, 4, 0, 3, 4, 1, 9, 4, 1, 4, 5, 2, 9, 4, 3, 6, 7, 4, 9, 4, 4, 7, 8, 5))
        xu = XmUGrid(points, cells)
        point_indices = np.array((0, 3, 6))
        expected_points = np.array(((0, 10, 0), (0, 0, 0), (0, -10, 0)))
        points_from_indxs = xu.get_points_from_point_idxs(point_indices)
        np.testing.assert_array_equal(expected_points, points_from_indxs)

    def test_xmugrid_get_extents(self):
        points = ((0, 0, 0), (10, 0, 0), (20, 0, 0), (30, 0, 0), (40, 0, 0),
                  (0, 10, 0), (10, 10, 0), (20, 10, 0), (40, 10, 0), (0, 20, 0),
                  (10, 20, 0), (20, 20, 0), (30, 20, 0), (40, 20, 0))
        cells = (XmUGrid.xmugrid_celltype_enum.XMU_QUAD, 4, 0, 1, 6, 5,
                 XmUGrid.xmugrid_celltype_enum.XMU_PIXEL, 4, 1, 2, 6, 7,
                 XmUGrid.xmugrid_celltype_enum.XMU_TRIANGLE, 3, 2, 3, 7,
                 XmUGrid.xmugrid_celltype_enum.XMU_POLYGON, 6, 3, 4, 8, 13, 12, 7,
                 XmUGrid.xmugrid_celltype_enum.XMU_POLY_LINE, 3, 7, 11, 10,
                 XmUGrid.xmugrid_celltype_enum.XMU_LINE, 2, 5, 9)
        xu = XmUGrid(points, cells)
        exp_min = (0, 0, 0)
        exp_max = (40, 20, 0)
        act_min, act_max = xu.get_extents()
        self.assertEqual(exp_min, act_min)
        self.assertEqual(exp_max, act_max)

    def test_get_point_cells(self):
        points = ((0, 10, 0), (10, 10, 0), (20, 10, 0), (0, 0, 0), (10, 0, 0), (20, 0, 0))
        cellStream = (XmUGrid.xmugrid_celltype_enum.XMU_QUAD, 4, 0, 3, 4, 1,
                      XmUGrid.xmugrid_celltype_enum.XMU_QUAD, 4, 1, 4, 5, 2)
        xu = XmUGrid(points, cellStream)

        cell_empty = ()
        cell_zero = (0,)
        cell_zero_and_one = (0, 1)
        cell_one = (1,)

        self.assertEqual(cell_empty, xu.get_point_cells(-1))
        self.assertEqual(cell_zero, xu.get_point_cells(0))
        self.assertEqual(cell_zero_and_one, xu.get_point_cells(1))
        self.assertEqual(cell_one, xu.get_point_cells(2))
        self.assertEqual(cell_zero, xu.get_point_cells(3))
        self.assertEqual(cell_zero_and_one, xu.get_point_cells(4))
        self.assertEqual(cell_one, xu.get_point_cells(5))
        self.assertEqual(cell_empty, xu.get_point_cells(6))

    def test_get_common_cells(self):
        points = ((0, 10, 0), (10, 10, 0), (20, 10, 0), (0, 0, 0), (10, 0, 0),
                  (20, 0, 0), (0, -10, 0), (10, -10, 0), (20, -10, 0))
        cell_stream = (XmUGrid.xmugrid_celltype_enum.XMU_QUAD, 4, 0, 3, 4, 1,
                       XmUGrid.xmugrid_celltype_enum.XMU_QUAD, 4, 1, 4, 5, 2,
                       XmUGrid.xmugrid_celltype_enum.XMU_QUAD, 4, 3, 6, 7, 4,
                       XmUGrid.xmugrid_celltype_enum.XMU_QUAD, 4, 4, 7, 8, 5)
        xu = XmUGrid(points, cell_stream)
        expected_cells = ()

        points = (-1, 0)
        retrieved_cells = xu.get_common_cells(points)
        self.assertEqual(expected_cells, retrieved_cells)

        points = (0, -1)
        retrieved_cells = xu.get_common_cells(points)
        self.assertEqual(expected_cells, retrieved_cells)

        points = (0, 8)
        retrieved_cells = xu.get_common_cells(points)
        self.assertEqual(expected_cells, retrieved_cells)

        expected_cells = (0, 2)
        points = (3, 4)
        retrieved_cells = xu.get_common_cells(points)
        self.assertEqual(expected_cells, retrieved_cells)

        expected_cells = (0,)
        points = (0, 3)
        retrieved_cells = xu.get_common_cells(points)
        self.assertEqual(expected_cells, retrieved_cells)

        expected_cells = ()
        points = (3, 4, 5)
        retrieved_cells = xu.get_common_cells(points)
        self.assertEqual(expected_cells, retrieved_cells)

        expected_cells = ()
        points = (xu.get_number_of_points(), 0)
        retrieved_cells = xu.get_common_cells(points)
        self.assertEqual(expected_cells, retrieved_cells)

        expected_cells = ()
        points = (0, xu.get_number_of_points())
        retrieved_cells = xu.get_common_cells(points)
        self.assertEqual(expected_cells, retrieved_cells)

    def test_get_number_of_cells(self):
        points = ((0, 0, 0), (20, 0, 0), (0, 20, 0))
        cells = (5, 3, 0, 1, 2)
        xu = XmUGrid(points, cells)
        num_cells_base = 1
        self.assertEqual(num_cells_base, xu.get_number_of_cells())

    def test_get_points_of_cell(self):
        import numpy as np
        xu = self.get_simple_quad_ugrid()
        invalid1 = xu.get_points_of_cell(-1)
        invalid2 = xu.get_points_of_cell(5)
        self.assertEqual(0, len(invalid1))
        self.assertEqual(0, len(invalid2))

        expected_cell_points = [np.array((0, 3, 4, 1)),
                                np.array((1, 4, 5, 2)),
                                np.array((3, 6, 7, 4)),
                                np.array((4, 7, 8, 5))]
        for i in range(0, len(expected_cell_points)):
            cell_points = xu.get_points_of_cell(i)
            np.testing.assert_array_equal(expected_cell_points[i], cell_points)

        xu2d = self.get_2d_linear_ugrid()
        expected_cell_points_2d = [np.array((0, 1, 6, 5)),
                                   np.array((1, 2, 7, 6)),
                                   np.array((2, 3, 7)),
                                   np.array((3, 4, 8, 13, 12, 7)),
                                   np.array((7, 11, 10)),
                                   np.array((5, 9))]
        for i in range(0, len(expected_cell_points_2d)):
            cell_points = xu2d.get_points_of_cell(i)
            np.testing.assert_array_equal(expected_cell_points_2d[i], cell_points)

        xu3d = self.get_3d_linear_ugrid()
        expected_cell_points_3d = [np.array((0, 1, 5, 15)),
                                   np.array((1, 2, 6, 7, 16, 17, 21, 22)),
                                   np.array((2, 3, 8, 7, 17, 18, 23, 22)),
                                   np.array((8, 9, 14, 13, 24, 23, 29, 28)),
                                   np.array((3, 4, 18, 8, 9, 23)),
                                   np.array((5, 6, 11, 10, 20))]
        for i in range(0, len(expected_cell_points_3d)):
            cell_points = xu3d.get_points_of_cell(i)
            np.testing.assert_array_equal(expected_cell_points_3d[i], cell_points)

    def test_get_cell_type(self):
        xu2d = self.get_2d_linear_ugrid()
        self.assertEqual(14, xu2d.get_number_of_points())
        self.assertEqual(6, xu2d.get_number_of_cells())
        self.assertEqual(XmUGrid.xmugrid_celltype_enum.XMU_INVALID_CELL_TYPE, xu2d.get_cell_type(-1))
        self.assertEqual(XmUGrid.xmugrid_celltype_enum.XMU_INVALID_CELL_TYPE, xu2d.get_cell_type(6))
        self.assertEqual(XmUGrid.xmugrid_celltype_enum.XMU_QUAD, xu2d.get_cell_type(0))
        self.assertEqual(XmUGrid.xmugrid_celltype_enum.XMU_PIXEL, xu2d.get_cell_type(1))
        self.assertEqual(XmUGrid.xmugrid_celltype_enum.XMU_TRIANGLE, xu2d.get_cell_type(2))
        self.assertEqual(XmUGrid.xmugrid_celltype_enum.XMU_POLYGON, xu2d.get_cell_type(3))
        self.assertEqual(XmUGrid.xmugrid_celltype_enum.XMU_POLY_LINE, xu2d.get_cell_type(4))
        self.assertEqual(XmUGrid.xmugrid_celltype_enum.XMU_LINE, xu2d.get_cell_type(5))

        xu3d = self.get_3d_linear_ugrid()
        self.assertEqual(30, xu3d.get_number_of_points())
        self.assertEqual(6, xu3d.get_number_of_cells())
        self.assertEqual(XmUGrid.xmugrid_celltype_enum.XMU_INVALID_CELL_TYPE, xu3d.get_cell_type(-1))
        self.assertEqual(XmUGrid.xmugrid_celltype_enum.XMU_INVALID_CELL_TYPE, xu3d.get_cell_type(6))
        self.assertEqual(XmUGrid.xmugrid_celltype_enum.XMU_TETRA, xu3d.get_cell_type(0))
        self.assertEqual(XmUGrid.xmugrid_celltype_enum.XMU_VOXEL, xu3d.get_cell_type(1))
        self.assertEqual(XmUGrid.xmugrid_celltype_enum.XMU_HEXAHEDRON, xu3d.get_cell_type(2))
        self.assertEqual(XmUGrid.xmugrid_celltype_enum.XMU_POLYHEDRON, xu3d.get_cell_type(3))
        self.assertEqual(XmUGrid.xmugrid_celltype_enum.XMU_WEDGE, xu3d.get_cell_type(4))
        self.assertEqual(XmUGrid.xmugrid_celltype_enum.XMU_PYRAMID, xu3d.get_cell_type(5))

    def test_get_dimension_count(self):
        import numpy as np
        xu2d = self.get_2d_linear_ugrid()
        results_2d = np.array((0, 2, 4, 0))
        np.testing.assert_array_equal(results_2d, xu2d.get_dimension_count())
        xu3d = self.get_3d_linear_ugrid()
        results_3d = np.array((0, 0, 0, 6))
        np.testing.assert_array_equal(results_3d, xu3d.get_dimension_count())

    def test_get_cell_dimension(self):
        xu2d = self.get_2d_linear_ugrid()
        self.assertEqual(2, xu2d.get_cell_dimension(0))
        self.assertEqual(2, xu2d.get_cell_dimension(1))
        self.assertEqual(2, xu2d.get_cell_dimension(2))
        self.assertEqual(2, xu2d.get_cell_dimension(3))
        self.assertEqual(1, xu2d.get_cell_dimension(4))
        self.assertEqual(1, xu2d.get_cell_dimension(5))

        xu3d = self.get_3d_linear_ugrid()
        self.assertEqual(XmUGrid.xmugrid_celltype_enum.XMU_INVALID_CELL_TYPE, xu3d.get_cell_dimension(-1))
        self.assertEqual(XmUGrid.xmugrid_celltype_enum.XMU_INVALID_CELL_TYPE, xu3d.get_cell_dimension(6))
        self.assertEqual(3, xu3d.get_cell_dimension(0))
        self.assertEqual(3, xu3d.get_cell_dimension(1))
        self.assertEqual(3, xu3d.get_cell_dimension(2))
        self.assertEqual(3, xu3d.get_cell_dimension(3))
        self.assertEqual(3, xu3d.get_cell_dimension(4))
        self.assertEqual(3, xu3d.get_cell_dimension(5))

    def test_cell_functions(self):
        """Test various cell functions"""
        import numpy as np
        ugrid = self.get_simple_quad_ugrid()

        # Test get_points_of_cell
        points_of_cell = ugrid.get_points_of_cell(0)
        expected_points = (0, 3, 4, 1)
        self.assertEqual(expected_points, points_of_cell)
        # Test overload
        points_of_cell = ugrid.get_points_of_cell(0)
        self.assertEqual(expected_points, points_of_cell)
        locations = ugrid.get_cell_point_locations(0)
        expected_locations = np.array(((0.0, 10.0, 0.0), (0.0, 0.0, 0.0), (10.0, 0.0, 0.0), (10.0, 10.0, 0.0)))
        np.testing.assert_array_equal(expected_locations, locations)

        # Test get_cell_extents
        extents = ugrid.get_cell_extents(0)
        expected_extents = [(0.0, 0.0, 0.0), (10.0, 10.0, 0.0)]
        np.testing.assert_array_equal(expected_extents, extents)

        # Test get_cell_type
        self.assertEqual(XmUGrid.xmugrid_celltype_enum.XMU_QUAD, ugrid.get_cell_type(0))

        # Test get_dimension_count
        expected_dimensions = (0, 0, 4, 0)
        self.assertEqual(expected_dimensions, ugrid.get_dimension_count())

        # Test get_cell_dimension
        self.assertEqual(2, ugrid.get_cell_dimension(0))

        # Test get_centroid
        result = ugrid.get_centroid(0)
        self.assertEqual(True, result[0])
        self.assertEqual((5, 5, 0), result[1])
        result = ugrid.get_centroid(-1)
        self.assertEqual(False, result[0])

    def test_get_cell_stream(self):
        import numpy as np
        xu = self.get_simple_quad_ugrid()
        cell_stream = xu.get_cell_stream()
        expected_cell_stream = np.array((XmUGrid.xmugrid_celltype_enum.XMU_QUAD, 4, 0, 3, 4, 1,
                                         XmUGrid.xmugrid_celltype_enum.XMU_QUAD, 4, 1, 4, 5, 2,
                                         XmUGrid.xmugrid_celltype_enum.XMU_QUAD, 4, 3, 6, 7, 4,
                                         XmUGrid.xmugrid_celltype_enum.XMU_QUAD, 4, 4, 7, 8, 5))
        np.testing.assert_array_equal(expected_cell_stream, cell_stream)

    def test_set_cell_stream(self):
        import numpy as np
        points = np.array(((0, 10, 0), (10, 10, 0), (20, 10, 0), (0, 0, 0), (10, 0, 0),
                           (20, 0, 0), (0, -10, 0), (10, -10, 0), (20, -10, 0)))
        cells = np.array((9, 4, 0, 3, 4, 1, 9, 4, 1, 4, 5, 2, 9, 4, 3, 6, 7, 4, 9, 4, 4, 7, 8, 5))
        xu = XmUGrid()
        xu.set_points(points)
        xu.set_cell_stream(cells)
        expected_cells = xu.get_cell_stream()
        self.assertEqual(len(points), xu.get_number_of_points())
        np.testing.assert_array_equal(expected_cells, cells)

    def test_get_single_cell_stream(self):
        import numpy as np
        xu = self.get_simple_quad_ugrid()
        ret, cell_stream = xu.get_single_cell_stream(0)
        expected_cell_stream = np.array((XmUGrid.xmugrid_celltype_enum.XMU_QUAD, 4, 0, 3, 4, 1))
        np.testing.assert_array_equal(expected_cell_stream, cell_stream)

    def test_get_cell_neighbors(self):
        import numpy as np
        xu = self.get_simple_quad_ugrid()

        expected_cells = np.array(())
        retrieved_cells = xu.get_cell_neighbors(-1)
        np.testing.assert_array_equal(expected_cells, retrieved_cells)
        retrieved_cells = xu.get_cell_neighbors(0)
        expected_cells = np.array((2, 1, 3))
        np.testing.assert_array_equal(expected_cells, retrieved_cells)
        expected_cells = np.array(())
        retrieved_cells = xu.get_cell_neighbors(4)
        np.testing.assert_array_equal(expected_cells, retrieved_cells)
        expected_cells = np.array(())
        retrieved_cells = xu.get_cell_neighbors(5)
        np.testing.assert_array_equal(expected_cells, retrieved_cells)

    def test_get_number_of_cell_edges(self):
        xu2d = self.get_2d_linear_ugrid()
        self.assertEqual(-1, xu2d.get_number_of_cell_edges(-1))
        self.assertEqual(-1, xu2d.get_number_of_cell_edges(6))
        self.assertEqual(4, xu2d.get_number_of_cell_edges(0))
        self.assertEqual(4, xu2d.get_number_of_cell_edges(1))
        self.assertEqual(3, xu2d.get_number_of_cell_edges(2))
        self.assertEqual(6, xu2d.get_number_of_cell_edges(3))
        self.assertEqual(2, xu2d.get_number_of_cell_edges(4))
        self.assertEqual(1, xu2d.get_number_of_cell_edges(5))

        xu3d = self.get_3d_linear_ugrid()
        self.assertEqual(-1, xu3d.get_number_of_cell_edges(-1))
        self.assertEqual(-1, xu3d.get_number_of_cell_edges(6))
        self.assertEqual(6, xu3d.get_number_of_cell_edges(0))
        self.assertEqual(12, xu3d.get_number_of_cell_edges(1))
        self.assertEqual(12, xu3d.get_number_of_cell_edges(2))
        self.assertEqual(12, xu3d.get_number_of_cell_edges(3))
        self.assertEqual(9, xu3d.get_number_of_cell_edges(4))
        self.assertEqual(8, xu3d.get_number_of_cell_edges(5))

    def test_get_cell_edge_from_edge_index(self):
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

        self.assertEqual(xu2d.get_cell_edge_from_edge_index(0, -1), (0, 0))
        self.assertEqual(xu2d.get_cell_edge_from_edge_index(0, xu2d.get_number_of_cell_edges(0)), (0, 0))

        expected_cell_edges = [[edge0, edge1, edge2, edge3]
            , [edge4, edge5, edge6, edge7]
            , [edge8, edge9, edge10, edge11]
            , [edge12, edge13, edge14, edge15]]
        self.assertEqual(len(expected_cell_edges), xu2d.get_number_of_cells())
        for i in range(0, xu2d.get_number_of_cells()):
            self.assertEqual(len(expected_cell_edges[i]), xu2d.get_number_of_cell_edges(i))
            for j in range(0, xu2d.get_number_of_cell_edges(i)):
                self.assertEqual(xu2d.get_cell_edge_from_edge_index(i, j), expected_cell_edges[i][j])

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
        self.assertEqual(len(expected_cell_edges), xu2d.get_number_of_cells())
        for i in range(0, xu2d.get_number_of_cells()):
            self.assertEqual(len(expected_cell_edges[i]), xu2d.get_number_of_cell_edges(i))
            for j in range(0, xu2d.get_number_of_cell_edges(i)):
                self.assertEqual(expected_cell_edges[i][j], xu2d.get_cell_edge_from_edge_index(i, j))

        xu3d = self.get_3d_linear_ugrid()
        expected_cell_edges = [
          [(0, 1), (1, 5), (5, 0), (0, 15), (1, 15), (5, 15)], # XMU_TETRA
          [(1, 2), (2, 7), (6, 7), (1, 6), (16, 17), (17, 22), (21, 22), (16, 21), (1, 16), (2, 17), (6, 21), (7, 22)], # XMU_VOXEL
          [(2, 3), (3, 8), (7, 8), (2, 7), (17, 18), (18, 23), (22, 23), (17, 22), (2, 17), (3, 18), (7, 22), (8, 23)], # XMU_HEXAHEDRON
          [(8, 9), (8, 13), (8, 23), (9, 14), (9, 24), (13, 14), (13, 28), (14, 29), (23, 24), (23, 28), (24, 29), (28, 29)], # XMU_POLYHEDRON
          [(3, 4), (4, 18), (18, 3), (8, 9), (9, 23), (23, 8), (3, 8), (4, 9), (18, 23)], # XMU_WEDGE
          [(5, 6), (6, 11), (11, 10), (10, 5), (5, 20), (6, 20), (11, 20), (10, 20)] # XMU_PYRAMID
        ]

        self.assertEqual(xu3d.get_number_of_cells(), len(expected_cell_edges))
        for i in range(0, xu3d.get_number_of_cells()):
            self.assertEqual(len(expected_cell_edges[i]), xu3d.get_number_of_cell_edges(i))
            for j in range(0, xu3d.get_number_of_cell_edges(i)):
                self.assertEqual(xu3d.get_cell_edge_from_edge_index(i, j), expected_cell_edges[i][j])

    def test_get_adjacent_cell_functions(self):
        xuquad = self.get_simple_quad_ugrid()
        expected_cells = [(), (2,), (1,), ()]
        expected_2d_cells = [-1, 2, 1, -1]
        for i in range(0, xuquad.get_number_of_cell_edges(0)):
            self.assertEqual(expected_cells[i], xuquad.get_adjacent_cells(0, i))
            self.assertEqual(expected_2d_cells[i], xuquad.get_2d_adjacent_cell(0, i))

        expected_cells_from_edge = [(0, 1), (0, 2), (0,)]
        edges = [(1, 4), (3, 4), (0, 3)]
        for i in range(0, len(edges)):
            self.assertEqual(expected_cells_from_edge[i], xuquad.get_adjacent_cells_from_given_edge(edges[i][0],edges[i][1]))
        self.assertEqual(expected_cells_from_edge[0],
                         xuquad.get_adjacent_cells_from_given_edge(edges[0][0], edges[1][1]))

    def test_get_edges_from_point(self):
        xuquad = self.get_simple_quad_ugrid()
        expected_cell = [(0, 0), (0, 0, 1, 1), (1, 1), (0, 0, 2, 2), (0, 0, 1, 1, 2, 2, 3, 3), (1, 1, 3, 3), (2, 2),
                         (2, 2, 3, 3), (3, 3)]
        expected_edge_indxs = [(0, 3), (2, 3, 0, 3), (2, 3), (0, 1, 0, 3), (1, 2, 0, 1, 2, 3, 0, 3), (1, 2, 2, 3),
                               (0, 1), (1, 2, 0, 1), (1, 2)]
        result = xuquad.get_edges_from_point(-1)
        self.assertEqual(result[0], False)
        self.assertEqual(result[1], ())
        self.assertEqual(result[2], ())
        for i in range(0, xuquad.get_number_of_points()):
            result = xuquad.get_edges_from_point(i)
            self.assertEqual(result[0], True)
            self.assertEqual(expected_cell[i], result[1])
            self.assertEqual(expected_edge_indxs[i], result[2])
        result = xuquad.get_edges_from_point(xuquad.get_number_of_points())
        self.assertEqual(result[0], False)
        self.assertEqual(result[1], ())
        self.assertEqual(result[2], ())

    def test_get_points_attached_by_edge(self):
        """Test get_point_idxs_attached_by_edge and get_points_attached_by_edge."""
        #     0-----1-----2
        #     |  0  |  1  |
        #     3-----4-----5
        #     |  2  |  3  |
        #     6-----7-----8
        import numpy as np
        grid = self.get_simple_quad_ugrid()
        attached_idxs = grid.get_point_idxs_attached_by_edge(0)
        expected_idxs = (1, 3)
        self.assertEqual(expected_idxs, attached_idxs)
        attached_idxs = grid.get_point_idxs_attached_by_edge(3)
        expected_idxs = (0, 4, 6)
        self.assertEqual(expected_idxs, attached_idxs)
        attached_idxs = grid.get_point_idxs_attached_by_edge(4)
        expected_idxs = (1, 3, 5, 7)
        self.assertEqual(expected_idxs, attached_idxs)

        attached_points = grid.get_points_attached_by_edge(0)
        expected_points = np.array(((10, 10, 0), (0, 0, 0)))
        np.testing.assert_array_equal(expected_points, attached_points)
        attached_points = grid.get_points_attached_by_edge(3)
        expected_points = ((0, 10, 0), (10, 0, 0), (0, -10, 0))
        np.testing.assert_array_equal(expected_points, attached_points)
        attached_points = grid.get_points_attached_by_edge(4)
        expected_points = ((10, 10, 0), (0, 0, 0), (20, 0, 0), (10, -10, 0))
        np.testing.assert_array_equal(expected_points, attached_points)

    def test_get_edges_of_cell(self):
        xuquad = self.get_simple_quad_ugrid()
        expected_edges = ((0, 3), (3, 4), (4, 1), (1, 0))
        edges = xuquad.get_edges_of_cell(0)
        self.assertEqual(expected_edges, edges)

    def test_get_number_of_cell_faces(self):
        xu2d = self.get_2d_linear_ugrid()
        self.assertEqual(-1, xu2d.get_number_of_cell_faces(-1))
        for i in range(0, xu2d.get_number_of_cells()):
            self.assertEqual(0, xu2d.get_number_of_cell_faces(i))
        self.assertEqual(-1, xu2d.get_number_of_cell_faces(xu2d.get_number_of_cells()))

        xu3d = self.get_3d_linear_ugrid()

        self.assertEqual(-1, xu3d.get_number_of_cell_faces(-1))
        self.assertEqual(-1, xu3d.get_number_of_cell_faces(6))
        self.assertEqual(4, xu3d.get_number_of_cell_faces(0))
        self.assertEqual(6, xu3d.get_number_of_cell_faces(1))
        self.assertEqual(6, xu3d.get_number_of_cell_faces(2))
        self.assertEqual(6, xu3d.get_number_of_cell_faces(3))
        self.assertEqual(5, xu3d.get_number_of_cell_faces(4))
        self.assertEqual(5, xu3d.get_number_of_cell_faces(5))

    def test_get_number_of_face_points(self):
        """Test getting the number of face points for a cell face."""
        xu2d = self.get_2d_linear_ugrid()
        # test 1D and 2D cells - should return 0 for valid cell index
        self.assertEqual(-1, xu2d.get_number_of_face_points(-1, 0))
        self.assertEqual(0, xu2d.get_number_of_face_points(1, 0))
        self.assertEqual(-1, xu2d.get_number_of_face_points(xu2d.get_number_of_cells(), 0))

        xu3d = self.get_3d_linear_ugrid()

        self.assertEqual(-1, xu3d.get_number_of_face_points(-1, 0))
        self.assertEqual(-1, xu3d.get_number_of_face_points(6, 0))
        self.assertEqual(4, xu3d.get_number_of_face_points(1, 3))
        self.assertEqual(4, xu3d.get_number_of_face_points(3, 2))

    def test_get_cell_face(self):
        xu2d = self.get_2d_linear_ugrid()
        self.assertEqual((), xu2d.get_cell_face(-1, 0))
        self.assertEqual((), xu2d.get_cell_face(0, -1))
        for i in range(0, xu2d.get_number_of_cells()):
            self.assertEqual((), xu2d.get_cell_face(i, 0))
        self.assertEqual((), xu2d.get_cell_face(xu2d.get_number_of_cells(), 0))
        self.assertEqual((), xu2d.get_cell_face(0, 1))

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
            (8, 9, 14, 13),
            (8, 9, 24, 23),
            (9, 14, 29, 24),
            (13, 14, 29, 28),
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
        for i in range(0, xu3d.get_number_of_cells()):
            for j in range(0, xu3d.get_number_of_cell_faces(i)):
                self.assertEqual(xu3d.get_cell_face(i, j), expected_cell_faces[curr_id])
                curr_id += 1

    def test_get_faces_of_cell(self):
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
            (8, 9, 14, 13),
            (8, 9, 24, 23),
            (9, 14, 29, 24),
            (13, 14, 29, 28),
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
        for i in range(0, xu3d.get_number_of_cells()):
            faces = xu3d.get_faces_of_cell(i)
            for j in range(0, len(faces)):
                self.assertEqual(faces[j], expected_cell_faces[curr_id])
                curr_id += 1

    def test_get_faces_from_point(self):
        xuhex = self.get_hexahedron_ugrid(3, 2, 2, (0, 0, 0))
        expected_cell = [
            (0, 0, 0), (0, 0, 0), (0, 0, 0, 1, 1, 1), (0, 0, 0, 1, 1, 1), (1, 1, 1), (1, 1, 1),
            (0, 0, 0), (0, 0, 0), (0, 0, 0, 1, 1, 1), (0, 0, 0, 1, 1, 1), (1, 1, 1), (1, 1, 1)]
        expected_faces = [
            (0, 2, 4), (0, 3, 4), (1, 2, 4, 0, 2, 4), (1, 3, 4, 0, 3, 4), (1, 2, 4), (1, 3, 4),
            (0, 2, 5), (0, 3, 5), (1, 2, 5, 0, 2, 5), (1, 3, 5, 0, 3, 5), (1, 2, 5), (1, 3, 5)]
        result = xuhex.get_faces_from_point(-1)
        self.assertEqual(result[0], False)
        self.assertEqual(result[1], ())
        self.assertEqual(result[2], ())
        for i in range(0, xuhex.get_number_of_points()):
            result = xuhex.get_faces_from_point(i)
            self.assertEqual(result[0], True)
            self.assertEqual(result[1], expected_cell[i])
            self.assertEqual(result[2], expected_faces[i])
        result = xuhex.get_faces_from_point(xuhex.get_number_of_points())
        self.assertEqual(result[0], False)
        self.assertEqual(result[1], ())
        self.assertEqual(result[2], ())

    def test_get_cell_face_neighbor(self):
        xuhex = self.get_hexahedron_ugrid(3, 2, 2, (0, 0, 0))
        expected_neighbor = [-1, 1, -1, -1, -1, -1, 0, -1, -1, -1, -1, -1]
        self.assertEqual(-1, xuhex.get_cell_face_neighbor(-1, 0))
        self.assertEqual(-1, xuhex.get_cell_face_neighbor(0, -1))
        curr_id = 0
        for i in range(0, xuhex.get_number_of_cells()):
            for j in range(0, xuhex.get_number_of_cell_faces(i)):
                neighbor_cell = xuhex.get_cell_face_neighbor(i, j)
                self.assertEqual(expected_neighbor[curr_id], neighbor_cell)
                curr_id += 1
        self.assertEqual(-1, xuhex.get_cell_face_neighbor(xuhex.get_number_of_cells(), 0))
        self.assertEqual(-1, xuhex.get_cell_face_neighbor(0,xuhex.get_number_of_cells()))

        xuhex = self.get_hexahedron_ugrid(3, 3, 3, (0, 0, 0))
        expected_neighbor = [-1, 2, -1, 1, -1, 4, -1, 3, 0, -1, -1, 5, 0, -1, -1, 3, -1, 6, 1, -1, 2, -1,
                             -1, 7, -1, 6, -1, 5, 0, -1, -1, 7, 4, -1, 1, -1, 4, -1, -1, 7, 2, -1, 5, -1,
                             6, -1, 3, -1]
        curr_id = 0
        for i in range(0, xuhex.get_number_of_cells()):
            for j in range(0, xuhex.get_number_of_cell_faces(i)):
                neighbor_cell = xuhex.get_cell_face_neighbor(i, j)
                self.assertEqual(expected_neighbor[curr_id], neighbor_cell)
                curr_id += 1


class TestXmUGridCellTypeEnum(unittest.TestCase):
    """CellType enum tests"""

    def test_xmugrid_celltype_enum(self):
        from xmsgrid_py.ugrid import XmUGrid
        self.assertEqual("xmugrid_celltype_enum.XMU_INVALID_CELL_TYPE",
                         str(XmUGrid.xmugrid_celltype_enum.XMU_INVALID_CELL_TYPE))
        self.assertEqual("xmugrid_celltype_enum.XMU_EMPTY_CELL", str(XmUGrid.xmugrid_celltype_enum.XMU_EMPTY_CELL))
        self.assertEqual("xmugrid_celltype_enum.XMU_VERTEX", str(XmUGrid.xmugrid_celltype_enum.XMU_VERTEX))
        self.assertEqual("xmugrid_celltype_enum.XMU_POLY_VERTEX", str(XmUGrid.xmugrid_celltype_enum.XMU_POLY_VERTEX))
        self.assertEqual("xmugrid_celltype_enum.XMU_LINE", str(XmUGrid.xmugrid_celltype_enum.XMU_LINE))
        self.assertEqual("xmugrid_celltype_enum.XMU_POLY_LINE", str(XmUGrid.xmugrid_celltype_enum.XMU_POLY_LINE))
        self.assertEqual("xmugrid_celltype_enum.XMU_TRIANGLE", str(XmUGrid.xmugrid_celltype_enum.XMU_TRIANGLE))
        self.assertEqual("xmugrid_celltype_enum.XMU_TRIANGLE_STRIP",
                         str(XmUGrid.xmugrid_celltype_enum.XMU_TRIANGLE_STRIP))
        self.assertEqual("xmugrid_celltype_enum.XMU_POLYGON", str(XmUGrid.xmugrid_celltype_enum.XMU_POLYGON))
        self.assertEqual("xmugrid_celltype_enum.XMU_PIXEL", str(XmUGrid.xmugrid_celltype_enum.XMU_PIXEL))
        self.assertEqual("xmugrid_celltype_enum.XMU_QUAD", str(XmUGrid.xmugrid_celltype_enum.XMU_QUAD))
        self.assertEqual("xmugrid_celltype_enum.XMU_TETRA", str(XmUGrid.xmugrid_celltype_enum.XMU_TETRA))
        self.assertEqual("xmugrid_celltype_enum.XMU_VOXEL", str(XmUGrid.xmugrid_celltype_enum.XMU_VOXEL))
        self.assertEqual("xmugrid_celltype_enum.XMU_HEXAHEDRON", str(XmUGrid.xmugrid_celltype_enum.XMU_HEXAHEDRON))
        self.assertEqual("xmugrid_celltype_enum.XMU_WEDGE", str(XmUGrid.xmugrid_celltype_enum.XMU_WEDGE))
        self.assertEqual("xmugrid_celltype_enum.XMU_PYRAMID", str(XmUGrid.xmugrid_celltype_enum.XMU_PYRAMID))
        self.assertEqual("xmugrid_celltype_enum.XMU_PENTAGONAL_PRISM",
                         str(XmUGrid.xmugrid_celltype_enum.XMU_PENTAGONAL_PRISM))
        self.assertEqual("xmugrid_celltype_enum.XMU_HEXAGONAL_PRISM",
                         str(XmUGrid.xmugrid_celltype_enum.XMU_HEXAGONAL_PRISM))
        self.assertEqual("xmugrid_celltype_enum.XMU_QUADRATIC_EDGE",
                         str(XmUGrid.xmugrid_celltype_enum.XMU_QUADRATIC_EDGE))
        self.assertEqual("xmugrid_celltype_enum.XMU_QUADRATIC_TRIANGLE",
                         str(XmUGrid.xmugrid_celltype_enum.XMU_QUADRATIC_TRIANGLE))
        self.assertEqual("xmugrid_celltype_enum.XMU_QUADRATIC_QUAD",
                         str(XmUGrid.xmugrid_celltype_enum.XMU_QUADRATIC_QUAD))
        self.assertEqual("xmugrid_celltype_enum.XMU_QUADRATIC_POLYGON",
                         str(XmUGrid.xmugrid_celltype_enum.XMU_QUADRATIC_POLYGON))
        self.assertEqual("xmugrid_celltype_enum.XMU_QUADRATIC_TETRA",
                         str(XmUGrid.xmugrid_celltype_enum.XMU_QUADRATIC_TETRA))
        self.assertEqual("xmugrid_celltype_enum.XMU_QUADRATIC_HEXAHEDRON",
                         str(XmUGrid.xmugrid_celltype_enum.XMU_QUADRATIC_HEXAHEDRON))
        self.assertEqual("xmugrid_celltype_enum.XMU_QUADRATIC_WEDGE",
                         str(XmUGrid.xmugrid_celltype_enum.XMU_QUADRATIC_WEDGE))
        self.assertEqual("xmugrid_celltype_enum.XMU_QUADRATIC_PYRAMID",
                         str(XmUGrid.xmugrid_celltype_enum.XMU_QUADRATIC_PYRAMID))
        self.assertEqual("xmugrid_celltype_enum.XMU_BIQUADRATIC_QUAD",
                         str(XmUGrid.xmugrid_celltype_enum.XMU_BIQUADRATIC_QUAD))
        self.assertEqual("xmugrid_celltype_enum.XMU_TRIQUADRATIC_HEXAHEDRON",
                         str(XmUGrid.xmugrid_celltype_enum.XMU_TRIQUADRATIC_HEXAHEDRON))
        self.assertEqual("xmugrid_celltype_enum.XMU_QUADRATIC_LINEAR_QUAD",
                         str(XmUGrid.xmugrid_celltype_enum.XMU_QUADRATIC_LINEAR_QUAD))
        self.assertEqual("xmugrid_celltype_enum.XMU_QUADRATIC_LINEAR_WEDGE",
                         str(XmUGrid.xmugrid_celltype_enum.XMU_QUADRATIC_LINEAR_WEDGE))
        self.assertEqual("xmugrid_celltype_enum.XMU_BIQUADRATIC_QUADRATIC_WEDGE",
                         str(XmUGrid.xmugrid_celltype_enum.XMU_BIQUADRATIC_QUADRATIC_WEDGE))
        self.assertEqual("xmugrid_celltype_enum.XMU_BIQUADRATIC_QUADRATIC_HEXAHEDRON",
                         str(XmUGrid.xmugrid_celltype_enum.XMU_BIQUADRATIC_QUADRATIC_HEXAHEDRON))
        self.assertEqual("xmugrid_celltype_enum.XMU_BIQUADRATIC_TRIANGLE",
                         str(XmUGrid.xmugrid_celltype_enum.XMU_BIQUADRATIC_TRIANGLE))
        self.assertEqual("xmugrid_celltype_enum.XMU_CUBIC_LINE", str(XmUGrid.xmugrid_celltype_enum.XMU_CUBIC_LINE))
        self.assertEqual("xmugrid_celltype_enum.XMU_CONVEX_POINT_SET",
                         str(XmUGrid.xmugrid_celltype_enum.XMU_CONVEX_POINT_SET))
        self.assertEqual("xmugrid_celltype_enum.XMU_POLYHEDRON",
                         str(XmUGrid.xmugrid_celltype_enum.XMU_POLYHEDRON))
        self.assertEqual("xmugrid_celltype_enum.XMU_PARAMETRIC_CURVE",
                         str(XmUGrid.xmugrid_celltype_enum.XMU_PARAMETRIC_CURVE))
        self.assertEqual("xmugrid_celltype_enum.XMU_PARAMETRIC_SURFACE",
                         str(XmUGrid.xmugrid_celltype_enum.XMU_PARAMETRIC_SURFACE))
        self.assertEqual("xmugrid_celltype_enum.XMU_PARAMETRIC_TRI_SURFACE",
                         str(XmUGrid.xmugrid_celltype_enum.XMU_PARAMETRIC_TRI_SURFACE))
        self.assertEqual("xmugrid_celltype_enum.XMU_PARAMETRIC_QUAD_SURFACE",
                         str(XmUGrid.xmugrid_celltype_enum.XMU_PARAMETRIC_QUAD_SURFACE))
        self.assertEqual("xmugrid_celltype_enum.XMU_PARAMETRIC_TETRA_REGION",
                         str(XmUGrid.xmugrid_celltype_enum.XMU_PARAMETRIC_TETRA_REGION))
        self.assertEqual("xmugrid_celltype_enum.XMU_PARAMETRIC_HEX_REGION",
                         str(XmUGrid.xmugrid_celltype_enum.XMU_PARAMETRIC_HEX_REGION))
        self.assertEqual("xmugrid_celltype_enum.XMU_HIGHER_ORDER_EDGE",
                         str(XmUGrid.xmugrid_celltype_enum.XMU_HIGHER_ORDER_EDGE))
        self.assertEqual("xmugrid_celltype_enum.XMU_HIGHER_ORDER_TRIANGLE",
                         str(XmUGrid.xmugrid_celltype_enum.XMU_HIGHER_ORDER_TRIANGLE))
        self.assertEqual("xmugrid_celltype_enum.XMU_HIGHER_ORDER_QUAD",
                         str(XmUGrid.xmugrid_celltype_enum.XMU_HIGHER_ORDER_QUAD))
        self.assertEqual("xmugrid_celltype_enum.XMU_HIGHER_ORDER_POLYGON",
                         str(XmUGrid.xmugrid_celltype_enum.XMU_HIGHER_ORDER_POLYGON))
        self.assertEqual("xmugrid_celltype_enum.XMU_HIGHER_ORDER_TETRAHEDRON",
                         str(XmUGrid.xmugrid_celltype_enum.XMU_HIGHER_ORDER_TETRAHEDRON))
        self.assertEqual("xmugrid_celltype_enum.XMU_HIGHER_ORDER_WEDGE",
                         str(XmUGrid.xmugrid_celltype_enum.XMU_HIGHER_ORDER_WEDGE))
        self.assertEqual("xmugrid_celltype_enum.XMU_HIGHER_ORDER_PYRAMID",
                         str(XmUGrid.xmugrid_celltype_enum.XMU_HIGHER_ORDER_PYRAMID))
        self.assertEqual("xmugrid_celltype_enum.XMU_HIGHER_ORDER_HEXAHEDRON",
                         str(XmUGrid.xmugrid_celltype_enum.XMU_HIGHER_ORDER_HEXAHEDRON))
        self.assertEqual("xmugrid_celltype_enum.XMU_NUMBER_OF_CELL_TYPES",
                         str(XmUGrid.xmugrid_celltype_enum.XMU_NUMBER_OF_CELL_TYPES))
        self.assertEqual(51, len(XmUGrid.xmugrid_celltype_enum.__members__))


class TestXmUGridFaceOrientationEnum(unittest.TestCase):
    """FaceOrientation enum tests"""

    def test_xmugrid_faceorientation_enum(self):
        from xmsgrid_py.ugrid import XmUGrid
        self.assertEqual("xmugrid_faceorientation_enum.XMU_ORIENTATION_UNKNOWN",
                         str(XmUGrid.xmugrid_faceorientation_enum.XMU_ORIENTATION_UNKNOWN))
        self.assertEqual("xmugrid_faceorientation_enum.XMU_ORIENTATION_SIDE",
                         str(XmUGrid.xmugrid_faceorientation_enum.XMU_ORIENTATION_SIDE))
        self.assertEqual("xmugrid_faceorientation_enum.XMU_ORIENTATION_TOP",
                         str(XmUGrid.xmugrid_faceorientation_enum.XMU_ORIENTATION_TOP))
        self.assertEqual("xmugrid_faceorientation_enum.XMU_ORIENTATION_BOTTOM",
                         str(XmUGrid.xmugrid_faceorientation_enum.XMU_ORIENTATION_BOTTOM))
        self.assertEqual(4, len(XmUGrid.xmugrid_faceorientation_enum.__members__))
