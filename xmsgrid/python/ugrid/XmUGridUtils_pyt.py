# Place holder for XMUGridUtils Tests
import unittest
from xmsgrid_py.ugrid import XmUGridUtils
from xmsgrid_py.ugrid import XmUGrid


class TestXmUGridUtilFunctions(unittest.TestCase):
    """XmUGridUtil function tests"""

    @staticmethod
    def get_3d_linear_ugrid():
        points = ((0, 0, 0), (10, 0, 0), (20, 0, 0), (30, 0, 0), (40, 0, 0),
                  (0, 10, 0), (10, 10, 0), (20, 10, 0), (30, 10, 0), (40, 10, 0)
                  ,(0, 20, 0), (10, 20, 0), (20, 20, 0), (30, 20, 0), (40, 20, 0
                  ),(0, 0, 10), (10, 0, 10), (20, 0, 10), (30, 0, 10), (40, 0, 
                  10), (0, 10, 10), (10, 10, 10), (20, 10, 10), (30, 10, 10), 
                  (40, 10, 10), (0, 20, 10), (10, 20, 10), (20, 20, 10), (30, 20
                  , 10), (40, 20, 10));
        cells = (XmUGrid.xmugrid_celltype_enum.XMU_TETRA, 4, 0, 1, 5, 15,
                 XmUGrid.xmugrid_celltype_enum.XMU_VOXEL, 8, 1, 2, 6, 7, 16, 17, 
                 21, 22, XmUGrid.xmugrid_celltype_enum.XMU_HEXAHEDRON, 8, 2, 3, 
                 8, 7, 17, 18, 23, 22, 
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

    def test_xm_write_and_read_ugrid_to_ascii_file(self):
        import numpy as np
        xu3d = self.get_3d_linear_ugrid()
        # write
        out_file_name = "PLACEHOLDER FOR TEST FILES PATH" + 
        "3d_grid_linear.xmugrid"
        XmUGridUtils.write_ugrid_to_ascii_file(xu3d, out_file_name)
        # read
        xu_read = XmUGridUtils.read_ugrid_from_ascii_file(out_file_name)
        np.testing.assert_array_equal(xu3d.get_locations(), 
            xu_read.get_locations())
        np.testing.assert_array_equal(xu3d.get_cellstream(), 
            xu3d.get_cellstream())

    def test_cross(self):
        self.assertEqual(XmUGridUtils.cross((0, 0, 0), (5, 5, 0), (3, 4, 0)), 5)
        self.assertEqual(XmUGridUtils.cross((7, 3, 0), (10, 5, 0), (11, 9, 0)), 
            10)
        self.assertEqual(XmUGridUtils.cross((4, 5, 0), (3, 8, 0), (6, 2, 0)), 
            -3)

    def test_do_line_segments_cross(self):
        # Test 1 Segments do not intersect
        point1 = (1, 2, 0)
        point2 = (1, 4, 0)
        point3 = (2, 1, 0)
        point4 = (4, 1, 0)
        self.assertEqual(False, XmUGridUtils.do_line_segments_cross(point1,
            point2, point3, point4))

        # Test 2 Segments that do intersect (generic)
        point1 = (2, 2, 0)
        point2 = (4, 4, 0)
        point3 = (2, 4, 0)
        point4 = (4, 2, 0)
        self.assertEqual(True, XmUGridUtils.do_line_segments_cross(point1, 
            point2, point3, point4))

        # Test 3 Colinear
        point1 = (1, 5, 0)
        point2 = (1, 8, 0)
        point3 = (1, 5, 0)
        point4 = (1, 8, 0)
        self.assertEqual(True, XmUGridUtils.do_line_segments_cross(point1, 
            point2, point3, point4))

        # Test 4 T intersection (which does not cross)
        point1 = (6, 2, 0)
        point2 = (6, 4, 0)
        point3 = (5, 5, 0)
        point4 = (7, 4, 0)
        self.assertEqual(False, XmUGridUtils.do_line_segments_cross(point1, 
            point2, point3, point4))

        # Test 5 L intersection (not cross)
        point1 = (2, 5, 0)
        point2 = (2, 8, 0)
        point3 = (2, 8, 0)
        point4 = (4, 8, 0)
        self.assertEqual(False, XmUGridUtils.do_line_segments_cross(point1, 
            point2, point3, point4))

        # Test 6 Near miss
        point1 = (5, 5, 0)
        point2 = (7, 5, 0)
        point3 = (5, 6, 0)
        point4 = (5, 8, 0)
        self.assertEqual(False, XmUGridUtils.do_line_segments_cross(point1, 
            point2, point3, point4))
