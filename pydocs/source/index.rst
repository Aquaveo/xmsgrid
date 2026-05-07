.. image:: _static/aquaveo.png
   :height: 35px
   :width: 250px
   :align: right

*****************
XmsGrid |version|
*****************

The xmsgrid library is a grid library for other Aquaveo products. It provides
classes and utilities for creating and manipulating unstructured grids
(``UGrid``), triangulated irregular networks (``Tin``), and supporting
geometric primitives such as polygon intersection and triangle search.

The Python package is named ``xms.grid`` and is organized into three
sub-modules:

* :mod:`xms.grid.ugrid` -- Unstructured grid creation, query, and IO.
* :mod:`xms.grid.geometry` -- Geometric primitives, free functions, and
  spatial searches.
* :mod:`xms.grid.triangulate` -- Triangulated irregular networks (TINs).

Examples
========

Runnable examples for this library can be found in the ``examples`` folder of
the `GitHub repository <https://github.com/Aquaveo/xmsgrid>`_.

Index
=====

**Getting Started**

* :doc:`getting_started`

.. toctree::
   :maxdepth: 2
   :hidden:
   :caption: Getting Started

   getting_started.rst

**User Interface**

* :doc:`modules/ugrid/UGrid`
* :doc:`modules/ugrid/ugrid_utils`
* :doc:`modules/geometry/geometry`
* :doc:`modules/geometry/MultiPolyIntersector`
* :doc:`modules/geometry/TriSearch`
* :doc:`modules/triangulate/Tin`

.. toctree::
   :maxdepth: 1
   :hidden:
   :caption: User Interface

   modules/ugrid/UGrid.rst
   modules/ugrid/ugrid_utils.rst
   modules/geometry/geometry.rst
   modules/geometry/MultiPolyIntersector.rst
   modules/geometry/TriSearch.rst
   modules/triangulate/Tin.rst

Acknowledgements
================

This library is the work of Aquaveo developers and supports other Aquaveo
libraries (xmsinterp, xmsmesh, xmsstamper, xmsextractor, etc.).
