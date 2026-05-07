*****
UGrid
*****

A class for representing unstructured grid geometries with 0D, 1D, 2D, and 3D
cells. Cell connectivity is described with a VTK-compatible cellstream:
``[cell_type, num_points, p0, p1, ...]`` for ordinary cells, with
:class:`UGrid.cell_type_enum` providing the cell type constants. For 3D
polyhedral cells the cellstream uses
``[cell_type, num_faces, face_0_num_points, face_0_p0, ...]`` per face.

.. autoclass:: xms.grid.ugrid.UGrid
   :members:

   .. attribute:: cell_type_enum

      Enumeration of supported VTK cell types (e.g. ``XMU_TRIANGLE``,
      ``XMU_QUAD``, ``XMU_HEXAHEDRON``, ``XMU_POLYHEDRON``). Use these values
      when building or interpreting cellstreams.

   .. attribute:: cell_ordering_enum

      Enumeration of cell orderings for layered 3D UGrids
      (``XMU_CELL_ORDER_INCREASING_DOWN``, ``XMU_CELL_ORDER_INCREASING_UP``,
      ``XMU_CELL_ORDER_UNKNOWN``). The cell ordering controls how face
      orientations (top/bottom/side) are computed for prismatic cells.

   .. attribute:: face_orientation_enum

      Enumeration of face orientations
      (``XMU_ORIENTATION_TOP``, ``XMU_ORIENTATION_BOTTOM``,
      ``XMU_ORIENTATION_SIDE``, ``XMU_ORIENTATION_UNKNOWN``). Returned by
      :meth:`UGrid.get_cell_3d_face_orientation`.
