********************
MultiPolyIntersector
********************

Intersects a 2D line segment with any number of polygons and returns the
polygons traversed in order, along with the parametric ``t`` values where
the segment enters and exits each polygon. This is the same primitive used
by xmsmesher (mesh generation across domains), xmsextractor (extraction
line traversal), and xmsstamper.

The polygons are described by a single point list and a list of polygons,
where each polygon is itself a list of indices into the point list. The
first point is **not** repeated as the last point. Polygon IDs returned by
:meth:`traverse_line_segment` are 1-based by default; pass a different
``starting_id`` to the constructor to change this. The ``query`` argument
selects the intersection rule (``'covered_by'`` requires the segment to be
covered by the polygon, ``'intersects'`` accepts any non-empty
intersection).

The Python wrapper hides the C++ ``GmMultiPolyIntersectionSorter``
abstraction; results are always returned with the standard "terse"
ordering (one enter/exit run per polygon). When a polygon id of ``-1``
appears in the returned id sequence it is the end-of-traversal marker.

.. autoclass:: xms.grid.geometry.MultiPolyIntersector
   :members:

   .. automethod:: __init__
