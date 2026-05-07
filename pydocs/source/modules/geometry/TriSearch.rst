*********
TriSearch
*********

Spatial index for searching triangles. Given a set of points and triangles
(point-index triples), :class:`TriSearch` answers queries such as which
triangle contains a given point, which triangle envelopes overlap a region,
and what interpolation weights apply at a query point. It is the spatial
backbone used by xmsinterp's linear and natural-neighbor interpolators.

Points and triangles can each be selectively activated or deactivated via
:attr:`point_activity` and :attr:`triangle_activity` so callers can mask
out portions of the mesh without rebuilding the search. The activity
sequence has one entry per point (or triangle); a ``True`` value marks the
index as active.

.. note::

   The Python wrapper copies the supplied points and triangles into
   internal C++ buffers when the search is constructed; later edits to
   the original Python sequences are not seen by the search. To search
   different data, build a new :class:`TriSearch`.

.. autoclass:: xms.grid.geometry.TriSearch
   :members:

   .. automethod:: __init__
