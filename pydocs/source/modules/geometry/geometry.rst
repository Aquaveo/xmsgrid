********
geometry
********

Free functions for low-level 2D geometric operations: point-in-polygon
tests, polygon area and centroid, line/segment queries, and tolerance
management. These helpers mirror the C++ free functions declared in
``xmsgrid/geometry/geoms.h``.

These helpers operate on points represented as ``(x, y, z)`` tuples and
generally project to the XY plane (the Z component is ignored - even by
functions named ``..._2d`` that take 3D points). The default tolerance for
floating-point comparisons can be queried with :func:`get_tol_2d` and
overridden with :func:`set_tol_2d`; most query functions also accept an
explicit ``tol`` argument.

.. note::

   :func:`set_tol_2d` updates a process-global tolerance used by every
   xmsgrid helper that does not receive an explicit ``tol``. Prefer the
   per-call ``tol`` arguments when a specific section of code needs a
   different tolerance, and reset the global value if you must change it.

.. automodule:: xms.grid.geometry.geometry
   :members:
