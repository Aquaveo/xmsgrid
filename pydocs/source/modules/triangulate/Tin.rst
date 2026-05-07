***
Tin
***

Triangulated irregular network (TIN). The :class:`Tin` class encapsulates
arrays of points, triangles (as triples of point indices), and adjacency
information, plus methods to triangulate, optimize, and modify them.

Constructing :class:`Tin` with ``points`` only stores the points but leaves
the triangle list empty; call :meth:`Tin.triangulate` to build triangles
using ``TrTriangulatorPoints`` internally. Constructing with both
``points`` and ``triangles`` skips that step and uses the triangles
verbatim.

Common workflows:

* Construct a Tin from a list of points (no triangles) and call
  :meth:`Tin.triangulate` to compute a Delaunay triangulation.
* Construct a Tin from existing points *and* triangles when the
  triangulation is already known.
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
