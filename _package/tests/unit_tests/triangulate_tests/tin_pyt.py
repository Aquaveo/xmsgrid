"""Tests for the Tin class."""
import os
import unittest

import numpy as np

import xms.grid.triangulate as xt


class TestTrTin(unittest.TestCase):
    """Test Tin Class."""

    def setUp(self):
        """Set up for each test case."""
        self.pts = ((0, 0, 0), (10, 0, 0), (20, 0, 0), (5, 10, 0), (15, 10, 0))
        self.pts_np = np.array([(0, 0, 0), (10, 0, 0), (20, 0, 0), (5, 10, 0), (15, 10, 0)])
        self.tris = (3, 0, 1, 1, 2, 4, 1, 4, 3)
        self.tris_np = np.array([3, 0, 1, 1, 2, 4, 1, 4, 3])
        self.tris_adj_tuple = ((0,), (0, 1, 2), (1,), (0, 2), (1, 2))
        self.tris_adj_list = [[0], [0, 1, 2], [1], [0, 2], [1, 2]]
        self.Tin = xt.Tin(self.pts, self.tris)

    def test_set_pts(self):
        """Test setting the points of a tin."""
        trtin = xt.Tin(self.pts)
        pts = self.pts
        trtin.points = pts
        np.testing.assert_array_equal(pts, trtin.points)

    def test_set_pts_numpy(self):
        """Test setting the points of a tin using numpy arrays."""
        trtin = xt.Tin(self.pts)
        pts = self.pts_np
        trtin.points = pts
        np.testing.assert_array_equal(pts, trtin.points)

    def test_set_tris(self):
        """Test setting the triangles of a tin."""
        trtin = xt.Tin(self.pts, self.tris)

        np.testing.assert_array_equal(self.pts, trtin.points)
        np.testing.assert_array_equal(self.tris, trtin.triangles)

    def test_set_tris_numpy(self):
        """Test setting the triangles of a tin using numpy arrays."""
        trtin = xt.Tin(self.pts)
        tris = self.tris_np
        trtin.triangles = tris

        np.testing.assert_array_equal(tris, trtin.triangles)

    def test_set_tris_adj(self):
        """Test setting the triangles adjacent to points of a tin."""
        trtin = xt.Tin(self.pts)
        tris_adj = self.tris_adj_tuple
        trtin.triangles_adjacent_to_points = tris_adj
        self.assertEqual(self.tris_adj_tuple, trtin.triangles_adjacent_to_points)

    def test_set_tris_adj_list(self):
        """Test setting the triangles adjacent to points of a tin using a list."""
        trtin = xt.Tin(self.pts)
        tris_adj = self.tris_adj_list
        trtin.triangles_adjacent_to_points = tris_adj
        self.assertEqual(self.tris_adj_tuple, trtin.triangles_adjacent_to_points)

    def test_set_geometry(self):
        """Test setting the geometry of a tin."""
        trtin = xt.Tin(self.pts)
        pts = self.pts
        tris = self.tris
        tris_adj = self.tris_adj_tuple
        trtin.set_geometry(pts, tris, tris_adj)

        np.testing.assert_array_equal(pts, trtin.points)
        np.testing.assert_array_equal(tris, trtin.triangles)
        self.assertEqual(self.tris_adj_tuple, trtin.triangles_adjacent_to_points)

    def test_set_geometry_numpy(self):
        """Test setting the geometry of a tin using numpy arrays."""
        trtin = xt.Tin(self.pts)
        pts = self.pts_np
        tris = self.tris_np
        tris_adj = np.array(self.tris_adj_list, dtype=object)
        trtin.set_geometry(pts, tris, tris_adj)

        np.testing.assert_array_equal(pts, trtin.points)
        np.testing.assert_array_equal(tris, trtin.triangles)
        self.assertEqual(self.tris_adj_tuple, trtin.triangles_adjacent_to_points)

    def test_get_pts(self):
        """Test getting the points of a tin."""
        trtin = xt.Tin(self.pts)
        pts = self.pts
        trtin.points = pts
        np.testing.assert_array_equal(pts, trtin.points)

    def test_get_tris(self):
        """Test getting the triangles of a tin."""
        trtin = xt.Tin(self.pts)
        tris = self.tris
        trtin.triangles = tris
        np.testing.assert_array_equal(tris, trtin.triangles)

    def test_get_tris_adj(self):
        """Test getting the triangles adjacent to points."""
        trtin = xt.Tin(self.pts)
        tris_adj = self.tris_adj_tuple
        trtin.triangles_adjacent_to_points = tris_adj
        self.assertEqual(self.tris_adj_tuple, trtin.triangles_adjacent_to_points)

    def test_num_points(self):
        """Test getting the number of points in a tin."""
        trtin = xt.Tin(self.pts)
        pts = self.pts_np
        trtin.points = pts
        self.assertEqual(5, trtin.number_of_points)

    def test_num_triangles(self):
        """Test getting the number of triangles in a tin."""
        trtin = xt.Tin(self.pts)
        tris = self.tris_np
        trtin.triangles = tris
        self.assertEqual(3, trtin.number_of_triangles)

    def test_triangle_from_edge(self):
        """Test getting a triangle from an edge."""
        trtin = xt.Tin(self.pts)
        trtin.set_geometry(self.pts, self.tris, self.tris_adj_tuple)
        rv, tri, idx1, idx2 = trtin.triangle_from_edge(1, 3)
        self.assertEqual(rv, True)
        self.assertEqual(tri, 0)
        self.assertEqual(idx1, 2)
        self.assertEqual(idx2, 0)
        rv, tri, idx1, idx2 = trtin.triangle_from_edge(3, 1)
        self.assertEqual(rv, True)
        self.assertEqual(tri, 2)
        self.assertEqual(idx1, 2)
        self.assertEqual(idx2, 0)
        rv, tri, idx1, idx2 = trtin.triangle_from_edge(1, 0)
        self.assertEqual(rv, False)

    def test_triangle_adjacent_to_edge(self):
        """Test getting the triangle adjacent to an edge."""
        trtin = xt.Tin(self.pts)
        trtin.set_geometry(self.pts, self.tris, self.tris_adj_tuple)
        tri = trtin.triangle_adjacent_to_edge(1, 3)
        self.assertEqual(2, tri)
        tri = trtin.triangle_adjacent_to_edge(3, 1)
        self.assertEqual(0, tri)
        tri = trtin.triangle_adjacent_to_edge(1, 0)
        self.assertEqual(0, tri)

    def test_local_index(self):
        """Test getting local indices."""
        trtin = xt.Tin(self.pts)
        trtin.set_geometry(self.pts, self.tris, self.tris_adj_tuple)
        self.assertEqual(1, trtin.local_index(0, 0))
        self.assertEqual(2, trtin.local_index(0, 1))
        self.assertEqual(0, trtin.local_index(0, 3))
        self.assertEqual(-1, trtin.local_index(0, 4))

    def test_global_index(self):
        """Test getting global indices."""
        trtin = xt.Tin(self.pts)
        trtin.set_geometry(self.pts, self.tris, self.tris_adj_tuple)
        self.assertEqual(3, trtin.global_index(0, 0))
        self.assertEqual(0, trtin.global_index(0, 1))
        self.assertEqual(1, trtin.global_index(0, 2))
        self.assertEqual(-1, trtin.global_index(3, 2))

    def test_common_edge_index(self):
        """Test getting the common edge between two adjacent triangles."""
        trtin = xt.Tin(self.pts)
        trtin.set_geometry(self.pts, self.tris, self.tris_adj_tuple)
        self.assertEqual(2, trtin.common_edge_index(0, 2))
        self.assertEqual(2, trtin.common_edge_index(2, 0))
        self.assertEqual(2, trtin.common_edge_index(1, 2))
        self.assertEqual(0, trtin.common_edge_index(2, 1))
        self.assertEqual(-1, trtin.common_edge_index(0, 1))

    def test_adjacent_triangle(self):
        """Test getting the triangles adjacent to another triangle."""
        trtin = xt.Tin(self.pts)
        trtin.set_geometry(self.pts, self.tris, self.tris_adj_tuple)
        self.assertEqual(-1, trtin.adjacent_triangle(0, 0))
        self.assertEqual(-1, trtin.adjacent_triangle(0, 1))
        self.assertEqual(2, trtin.adjacent_triangle(0, 2))
        self.assertEqual(-1, trtin.adjacent_triangle(1, 0))
        self.assertEqual(-1, trtin.adjacent_triangle(1, 1))
        self.assertEqual(2, trtin.adjacent_triangle(1, 2))
        self.assertEqual(1, trtin.adjacent_triangle(2, 0))
        self.assertEqual(-1, trtin.adjacent_triangle(2, 1))
        self.assertEqual(0, trtin.adjacent_triangle(2, 2))

    def test_triangle_centroid(self):
        """Test getting the centroid of a triangle."""
        trtin = xt.Tin(self.pts)
        trtin.set_geometry(self.pts, self.tris, self.tris_adj_tuple)
        x0, y0, z0 = trtin.triangle_centroid(0)
        self.assertEqual(5, x0)
        self.assertAlmostEqual(3.333333333, y0, places=8)
        self.assertEqual(0, z0)
        x1, y1, z1 = trtin.triangle_centroid(1)
        self.assertEqual(15, x1)
        self.assertAlmostEqual(3.333333333, y1, places=8)
        self.assertEqual(0, z1)
        x2, y2, z2 = trtin.triangle_centroid(2)
        self.assertEqual(10, x2)
        self.assertAlmostEqual(6.666666666, y2, places=8)
        self.assertEqual(0, z2)

    def test_triangle_area(self):
        """Test getting the area of a triangle."""
        trtin = xt.Tin(self.pts)
        trtin.set_geometry(self.pts, self.tris, self.tris_adj_tuple)
        self.assertAlmostEqual(50.00000, trtin.triangle_area(0), places=4)
        self.assertAlmostEqual(50.00000, trtin.triangle_area(1), places=4)
        self.assertAlmostEqual(50.00000, trtin.triangle_area(2), places=4)

    def test_next_boundry_point(self):
        """Test getting the boundary point after another boundary point."""
        trtin = xt.Tin(self.pts)
        trtin.set_geometry(self.pts, self.tris, self.tris_adj_tuple)
        self.assertEqual(3, trtin.next_boundary_point(0))
        self.assertEqual(4, trtin.next_boundary_point(3))
        self.assertEqual(2, trtin.next_boundary_point(4))
        self.assertEqual(1, trtin.next_boundary_point(2))
        self.assertEqual(0, trtin.next_boundary_point(1))

    def test_previous_boundary_point(self):
        """Test getting the boundary point previous to another boundary point."""
        trtin = xt.Tin(self.pts)
        trtin.set_geometry(self.pts, self.tris, self.tris_adj_tuple)
        self.assertEqual(1, trtin.previous_boundary_point(0))
        self.assertEqual(2, trtin.previous_boundary_point(1))
        self.assertEqual(4, trtin.previous_boundary_point(2))
        self.assertEqual(3, trtin.previous_boundary_point(4))
        self.assertEqual(0, trtin.previous_boundary_point(3))

    def test_get_boundary_points(self):
        """Test getting the boundary points of a tin."""
        trtin = xt.Tin(self.pts)
        pts = ((0, 0, 0), (10, 0, 0), (20, 0, 0), (0, 10, 0), (10, 10, 0),
               (20, 10, 0), (0, 20, 0), (10, 20, 0), (20, 20, 0),)
        tris = (0, 1, 3, 1, 6, 3, 1, 4, 6, 4, 7, 6,
                1, 2, 4, 2, 7, 4, 2, 5, 7, 5, 8, 7)
        tris_adj = ((0,), (0, 1, 2, 4), (4, 5, 6), (0, 1), (2, 4, 5, 3),
                    (6, 7), (1, 2, 3), (3, 5, 6, 7), (7,))
        trtin.set_geometry(pts, tris, tris_adj)
        np.testing.assert_array_equal(
            np.array([0, 1, 2, 3, 5, 6, 7, 8]),
            trtin.boundary_points
        )

    def test_get_boundary_polys(self):
        """Test getting the boundary polygons of a tin."""
        trtin = xt.Tin(self.pts)
        trtin.set_geometry(self.pts, self.tris, self.tris_adj_tuple)
        self.assertEqual(((0, 3, 4, 2, 1, 0),), trtin.boundary_polys)

    def test_get_extents(self):
        """Test getting the extents of a tin."""
        trtin = xt.Tin(self.pts)
        trtin.set_geometry(self.pts, self.tris, self.tris_adj_tuple)
        mn, mx = trtin.extents
        self.assertEqual((0, 0, 0), mn)
        self.assertEqual((20, 10, 0), mx)

    def test_export_tin_file(self):
        """Test exporting a tin to an ASCII file."""
        trtin = xt.Tin(self.pts)
        trtin.set_geometry(self.pts, self.tris, self.tris_adj_tuple)
        trtin.export_tin_file("testfile.txt")
        self.assertTrue(os.path.isfile("testfile.txt"))

    def test_swap_edge(self):
        """Test swapping edges of a tin."""
        trtin = xt.Tin(self.pts)
        trtin.set_geometry(self.pts, self.tris, self.tris_adj_tuple)
        rv = trtin.swap_edge(0, 2, True)
        self.assertEqual(True, rv)
        self.assertEqual(trtin.triangles[0], 3)
        self.assertEqual(trtin.triangles[1], 0)
        self.assertEqual(trtin.triangles[2], 4)
        self.assertEqual(trtin.triangles[3], 1)
        self.assertEqual(trtin.triangles[4], 2)
        self.assertEqual(trtin.triangles[5], 4)
        self.assertEqual(trtin.triangles[6], 1)
        self.assertEqual(trtin.triangles[7], 4)
        self.assertEqual(trtin.triangles[8], 0)

        tris_adj = trtin.triangles_adjacent_to_points
        self.assertEqual((0, 2), tris_adj[0])
        self.assertEqual((1, 2), tris_adj[1])
        self.assertEqual((1,), tris_adj[2])
        self.assertEqual((0,), tris_adj[3])
        self.assertEqual((1, 2, 0), tris_adj[4])

    def test_delete_triangles(self):
        """Test deleting triangles from a tin."""
        # TODO: I don't think this is right.
        trtin = xt.Tin(self.pts)
        trtin.set_geometry(self.pts, self.tris, self.tris_adj_tuple)
        to_delete = (1, 0)
        trtin.delete_triangles(to_delete)
        self.assertEqual(5, trtin.number_of_points)
        self.assertEqual(1, trtin.number_of_triangles)

    def test_delete_points(self):
        """Test deleting points from a tin."""
        trtin = xt.Tin(self.pts)
        trtin.set_geometry(self.pts, self.tris, self.tris_adj_tuple)
        to_delete = (2, 4)
        trtin.delete_points(to_delete)
        self.assertEqual(3, trtin.number_of_points)
        self.assertEqual(1, trtin.number_of_triangles)

    def test_optimize_triangulation(self):
        """Test optimized triangulation."""
        trtin = xt.Tin(self.pts)
        pts = ((0, 0, 0), (10, 0, 0), (20, 0, 0), (0, 10, 0), (10, 10, 0),
               (20, 10, 0), (0, 20, 0), (10, 20, 0), (20, 20, 0),)
        tris = (0, 1, 3, 1, 6, 3, 1, 4, 6, 4, 7, 6,
                1, 2, 4, 2, 7, 4, 2, 5, 7, 5, 8, 7)
        tris_adj = ((0,), (0, 1, 2, 4), (4, 5, 6), (0, 1), (2, 4, 5, 3),
                    (6, 7), (1, 2, 3), (3, 5, 6, 7), (7,))
        trtin.set_geometry(pts, tris, tris_adj)
        trtin.optimize_triangulation()
        np.testing.assert_array_equal(np.array(tris), trtin.triangles)

    def test_build_tris_adj_to_pts(self):
        """Test building triangles adjacent to points."""
        trtin = xt.Tin(self.pts)
        trtin.set_geometry(self.pts, self.tris, self.tris_adj_tuple)
        trtin.build_triangles_adjacent_to_points()
        self.assertEqual(((0,), (0, 1, 2), (1,), (0, 2), (1, 2)), trtin.triangles_adjacent_to_points)

    def test_clear(self):
        """Test clearing a tin."""
        trtin = xt.Tin(self.pts)
        trtin.set_geometry(self.pts, self.tris, self.tris_adj_tuple)
        np.testing.assert_array_equal(self.pts_np, trtin.points)
        np.testing.assert_array_equal(self.tris_np, trtin.triangles)
        self.assertEqual(self.tris_adj_tuple, trtin.triangles_adjacent_to_points)
        trtin.clear()
        self.assertEqual(0, len(trtin.points))
        self.assertEqual(0, len(trtin.triangles))
        self.assertEqual((), trtin.triangles_adjacent_to_points)
