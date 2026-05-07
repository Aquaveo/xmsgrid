Installation
------------

XmsGrid can be installed using `Anaconda <https://www.anaconda.com/download/>`_.

Install with ``conda`` from the ``aquaveo`` channel::

   conda install -c aquaveo xmsgrid

This will install xmsgrid and **all** the needed dependencies.

Usage
-----

The xmsgrid library contains classes for defining geometric grids that can be
used in other Aquaveo libraries.

The most common entry points are:

* :class:`xms.grid.ugrid.UGrid` -- a 0/1/2/3-D unstructured grid built from a
  list of points and a VTK-style cellstream.
* :mod:`xms.grid.ugrid.ugrid_utils` -- read/write UGrids and apply bulk
  modifications (remove points/cells, clip to loops).
* :class:`xms.grid.triangulate.Tin` -- a triangulated irregular network.
* :class:`xms.grid.geometry.MultiPolyIntersector` and
  :class:`xms.grid.geometry.TriSearch` -- spatial queries.
* :mod:`xms.grid.geometry.geometry` -- free functions for low-level 2D
  geometry (point-in-polygon, polygon area, etc.).

Quick Start
-----------

Build a small UGrid programmatically and inspect it::

   from xms.grid.ugrid import UGrid

   points = [
       (0.0, 0.0, 0.0),
       (1.0, 0.0, 0.0),
       (1.0, 1.0, 0.0),
       (0.0, 1.0, 0.0),
   ]
   # Cell type 9 (quad) with 4 points: 0, 1, 2, 3
   cellstream = [9, 4, 0, 1, 2, 3]

   grid = UGrid(points=points, cellstream=cellstream)
   print(grid.point_count, grid.cell_count)
   print(grid.get_cell_locations(0))

Round-trip a UGrid through the ASCII file format::

   from xms.grid.ugrid import ugrid_utils

   ugrid_utils.write_ugrid_to_ascii_file(grid, "grid.ugrid")
   loaded = ugrid_utils.read_ugrid_from_ascii_file("grid.ugrid")
   assert loaded == grid

Usage and documentation for each class can be found in the **User Interface**
section of this site. Additional examples are available in the project's
`examples directory
<https://github.com/Aquaveo/xmsgrid/tree/master/examples>`_, including the
``UGrids.ipynb`` notebook.
