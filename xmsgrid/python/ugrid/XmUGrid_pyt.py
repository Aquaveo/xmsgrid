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
                  (0, 20, 10), (10, 20, 10), (20, 20, 10), (30, 20, 10), (40, 20, 10));
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
        points = ((0, 10, 0), (10, 10, 0), (20, 10, 0),  (0, 0, 0),   (10, 0, 0),
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
                              np.array((1, 2, 6, 7)), 
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

        expected_cells = np.array([])
        retrieved_cells = xu.get_cell_neighbors(-1)
        np.testing.assert_array_equal(expected_cells, retrieved_cells)
        retrieved_cells = xu.get_cell_neighbors(0)
        expected_cells = np.array((2, 1, 3))
        np.testing.assert_array_equal(expected_cells, retrieved_cells)
        expected_cells = np.array([])
        retrieved_cells = xu.get_cell_neighbors(4)
        np.testing.assert_array_equal(expected_cells, retrieved_cells)
        expected_cells = np.array([])
        retrieved_cells = xu.get_cell_neighbors(5)
        np.testing.assert_array_equal(expected_cells, retrieved_cells)


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
