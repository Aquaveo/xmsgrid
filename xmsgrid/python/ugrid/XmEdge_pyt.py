"""Test XmUGrid_py.cpp"""
import unittest
import xmsgrid_py
from xmsgrid_py.ugrid import XmEdge


class TestXmEdgeFunctions(unittest.TestCase):
    """XmEdge Function tests"""

    def test_edges_equivalent(self):
        edge1 = (0, 1)
        edge1a = (1, 0)
        edge2 = (1, 2)
        self.assertTrue(XmEdge.edges_equivalent(edge1, edge1a))
        self.assertFalse(XmEdge.edges_equivalent(edge1, edge2))
