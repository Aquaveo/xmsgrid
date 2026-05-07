***
Tin
***

Triangulated irregular network (TIN). The :class:`Tin` class encapsulates
arrays of points, triangles (as triples of point indices), and adjacency
information, plus methods to triangulate, optimize, and modify them.

When constructed with ``points`` only, :class:`Tin` runs the
``TrTriangulatorPoints`` algorithm internally, so callers do not need to
build triangles themselves before calling :meth:`Tin.triangulate`.

Common workflows:

* Construct a Tin from a list of points and (optionally) triangles, then call
  :meth:`Tin.triangulate` to compute a Delaunay triangulation.
* Inspect topology with :attr:`Tin.boundary_polys`,
  :meth:`Tin.adjacent_triangle`, :meth:`Tin.triangle_centroid`, etc.
* Modify with :meth:`Tin.swap_edge`, :meth:`Tin.delete_triangles`,
  :meth:`Tin.delete_points`, or :meth:`Tin.optimize_triangulation`.
* Persist with :meth:`Tin.export_tin_file`.

Note: the :attr:`Tin.points`, :attr:`Tin.triangles`, and
:attr:`Tin.triangles_adjacent_to_points` setters install the supplied
sequences directly. After mutating triangles outside the helper API call
:meth:`Tin.build_triangles_adjacent_to_points` to keep adjacency consistent.

.. autoclass:: xms.grid.triangulate.Tin
   :members:

   .. automethod:: __init__
