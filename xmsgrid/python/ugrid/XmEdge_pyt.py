"""Test UGrid_py.cpp"""
import unittest
import xmsgrid
from xmsgrid.ugrid import edge


class TestEdgeFunctions(unittest.TestCase):
    """edge Function tests"""

    def test_edges_equivalent(self):
        edge1 = (0, 1)
        edge1a = (1, 0)
        edge2 = (1, 2)
        self.assertTrue(edge.edges_equivalent(edge1, edge1a))
        self.assertFalse(edge.edges_equivalent(edge1, edge2))
