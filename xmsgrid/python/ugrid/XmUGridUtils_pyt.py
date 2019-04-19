# Place holder for ugrid_utils Tests
import unittest
from xmsgrid.ugrid import ugrid_utils
from xmsgrid.ugrid import UGrid


class TestUGridUtilFunctions(unittest.TestCase):
    """ugrid_util function tests"""

    @staticmethod
    def get_3d_linear_ugrid():
        points = ((0, 0, 0), (10, 0, 0), (20, 0, 0), (30, 0, 0), (40, 0, 0),
                  (0, 10, 0), (10, 10, 0), (20, 10, 0), (30, 10, 0), (40, 10, 0)
                  ,(0, 20, 0), (10, 20, 0), (20, 20, 0), (30, 20, 0), (40, 20, 0
                  ),(0, 0, 10), (10, 0, 10), (20, 0, 10), (30, 0, 10), (40, 0, 
                  10), (0, 10, 10), (10, 10, 10), (20, 10, 10), (30, 10, 10), 
                  (40, 10, 10), (0, 20, 10), (10, 20, 10), (20, 20, 10), (30, 20
                  , 10), (40, 20, 10));
        cells = (UGrid.cell_type_enum.TETRA, 4, 0, 1, 5, 15,
                 UGrid.cell_type_enum.VOXEL, 8, 1, 2, 6, 7, 16, 17, 21, 22,
                 UGrid.cell_type_enum.HEXAHEDRON, 8, 2, 3, 8, 7, 17, 18, 23, 22,
                 UGrid.cell_type_enum.POLYHEDRON, 6, 4, 8, 9, 14, 13, 4, 8, 9, 24, 23,
                               4, 9, 14, 29, 24, 4, 13, 14, 29, 28,
                               4, 8, 13, 28, 23, 4, 23, 24, 29, 28,
                 UGrid.cell_type_enum.WEDGE, 6, 3, 4, 18, 8, 9, 23,
                 UGrid.cell_type_enum.PYRAMID, 5, 5, 6, 11, 10, 20)
        xu = UGrid(points, cells)
        return xu

    def test_xm_write_and_read_ugrid_to_ascii_file(self):
        import numpy as np
        xu3d = self.get_3d_linear_ugrid()
        # write
        # TODO Get this path set correctly
        out_file_name = "PLACEHOLDER FOR TEST FILES PATH" + "3d_grid_linear.xmugrid"
        ugrid_utils.write_ugrid_to_ascii_file(xu3d, out_file_name)
        # read
        xu_read = ugrid_utils.read_ugrid_from_ascii_file(out_file_name)
        np.testing.assert_array_equal(xu3d.locations, xu_read.locations)
        np.testing.assert_array_equal(xu3d.cellstream, xu3d.cellstream)
