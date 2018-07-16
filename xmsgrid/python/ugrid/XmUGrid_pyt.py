"""Test XmUGrid_py.cpp"""
import unittest
import xmsgrid_py


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
