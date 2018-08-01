<?xml version='1.0' encoding='UTF-8' standalone='yes' ?>
<tagfile>
  <compound kind="file">
    <name>ugrid_py.cpp</name>
    <path>/home/travis/build/Aquaveo/xmsgrid/xmsgrid/python/ugrid/</path>
    <filename>ugrid__py_8cpp</filename>
    <includes id="ugrid__py_8h" name="ugrid_py.h" local="no" imported="no">xmsgrid/python/ugrid/ugrid_py.h</includes>
  </compound>
  <compound kind="file">
    <name>ugrid_py.h</name>
    <path>/home/travis/build/Aquaveo/xmsgrid/xmsgrid/python/ugrid/</path>
    <filename>ugrid__py_8h</filename>
  </compound>
  <compound kind="file">
    <name>XmUGrid_py.cpp</name>
    <path>/home/travis/build/Aquaveo/xmsgrid/xmsgrid/python/ugrid/</path>
    <filename>_xm_u_grid__py_8cpp</filename>
    <includes id="_xm_u_grid_8h" name="XmUGrid.h" local="no" imported="no">xmsgrid/ugrid/XmUGrid.h</includes>
  </compound>
  <compound kind="file">
    <name>XmUGridUtils_py.cpp</name>
    <path>/home/travis/build/Aquaveo/xmsgrid/xmsgrid/python/ugrid/</path>
    <filename>_xm_u_grid_utils__py_8cpp</filename>
    <includes id="_xm_u_grid_utils_8h" name="XmUGridUtils.h" local="no" imported="no">xmsgrid/ugrid/XmUGridUtils.h</includes>
    <includes id="_xm_u_grid_8h" name="XmUGrid.h" local="no" imported="no">xmsgrid/ugrid/XmUGrid.h</includes>
  </compound>
  <compound kind="file">
    <name>xmsgrid_py.cpp</name>
    <path>/home/travis/build/Aquaveo/xmsgrid/xmsgrid/python/</path>
    <filename>xmsgrid__py_8cpp</filename>
    <includes id="ugrid__py_8h" name="ugrid_py.h" local="no" imported="no">xmsgrid/python/ugrid/ugrid_py.h</includes>
  </compound>
  <compound kind="file">
    <name>XmConvexHull.cpp</name>
    <path>/home/travis/build/Aquaveo/xmsgrid/xmsgrid/ugrid/</path>
    <filename>_xm_convex_hull_8cpp</filename>
    <includes id="_xm_convex_hull_8h" name="XmConvexHull.h" local="no" imported="no">xmsgrid/ugrid/XmConvexHull.h</includes>
    <includes id="_xm_u_grid_8h" name="XmUGrid.h" local="no" imported="no">xmsgrid/ugrid/XmUGrid.h</includes>
    <includes id="_xm_u_grid_utils_8h" name="XmUGridUtils.h" local="no" imported="no">xmsgrid/ugrid/XmUGridUtils.h</includes>
    <namespace>xms</namespace>
    <member kind="function">
      <type>std::vector&lt; Pt3d &gt;</type>
      <name>ConvexHull</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a1973dbb5cf1431334a569f565b1c7d13</anchor>
      <arglist>(std::vector&lt; Pt3d &gt; a_points)</arglist>
    </member>
    <member kind="function">
      <type>VecInt</type>
      <name>ConvexHullWithIndices</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ac022fbaa831f7fc3362547238bad840a</anchor>
      <arglist>(const VecInt &amp;a_points, BSHP&lt; XmUGrid &gt; a_ugrid)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>XmConvexHull.h</name>
    <path>/home/travis/build/Aquaveo/xmsgrid/xmsgrid/ugrid/</path>
    <filename>_xm_convex_hull_8h</filename>
    <namespace>xms</namespace>
  </compound>
  <compound kind="file">
    <name>XmUGrid.cpp</name>
    <path>/home/travis/build/Aquaveo/xmsgrid/xmsgrid/ugrid/</path>
    <filename>_xm_u_grid_8cpp</filename>
    <includes id="_xm_u_grid_8h" name="XmUGrid.h" local="no" imported="no">xmsgrid/ugrid/XmUGrid.h</includes>
    <includes id="_xm_convex_hull_8h" name="XmConvexHull.h" local="no" imported="no">xmsgrid/ugrid/XmConvexHull.h</includes>
    <includes id="_xm_u_grid_utils_8h" name="XmUGridUtils.h" local="no" imported="no">xmsgrid/ugrid/XmUGridUtils.h</includes>
    <includes id="_xm_u_grid_8t_8h" name="XmUGrid.t.h" local="no" imported="no">xmsgrid/ugrid/XmUGrid.t.h</includes>
    <class kind="class">xms::XmUGridImpl</class>
    <namespace>xms</namespace>
    <member kind="function">
      <type>BSHP&lt; XmUGrid &gt;</type>
      <name>TEST_XmUGrid1Left90Tri</name>
      <anchorfile>_xm_u_grid_8cpp.html</anchorfile>
      <anchor>ae83c6c4067dad45c2649d38372ee4d98</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>BSHP&lt; XmUGrid &gt;</type>
      <name>TEST_XmUGridSimpleQuad</name>
      <anchorfile>_xm_u_grid_8cpp.html</anchorfile>
      <anchor>a1f7881528f1497337689118149933f6b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>BSHP&lt; XmUGrid &gt;</type>
      <name>TEST_XmUGrid2dLinear</name>
      <anchorfile>_xm_u_grid_8cpp.html</anchorfile>
      <anchor>aae054eb972140e14bf5c8bd873c8b282</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>BSHP&lt; XmUGrid &gt;</type>
      <name>TEST_XmUGrid3dLinear</name>
      <anchorfile>_xm_u_grid_8cpp.html</anchorfile>
      <anchor>adae3b643305100b325b7fd7ee3b42e50</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>BSHP&lt; XmUGrid &gt;</type>
      <name>TEST_XmUGridHexagonalPolyhedron</name>
      <anchorfile>_xm_u_grid_8cpp.html</anchorfile>
      <anchor>a35ea59a275774db42c8581755f643d0c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>BSHP&lt; xms::XmUGrid &gt;</type>
      <name>TEST_XmUBuildQuadUGrid</name>
      <anchorfile>_xm_u_grid_8cpp.html</anchorfile>
      <anchor>a95cce469cb2bf795b70937e09bea4a78</anchor>
      <arglist>(const int a_rows, const int a_cols)</arglist>
    </member>
    <member kind="function">
      <type>BSHP&lt; xms::XmUGrid &gt;</type>
      <name>TEST_XmUBuildQuadUGrid</name>
      <anchorfile>_xm_u_grid_8cpp.html</anchorfile>
      <anchor>a21c30167b814e37425f763241ec39063</anchor>
      <arglist>(const int a_rows, const int a_cols, const xms::Pt3d &amp;a_origin)</arglist>
    </member>
    <member kind="function">
      <type>BSHP&lt; xms::XmUGrid &gt;</type>
      <name>TEST_XmUBuildHexahedronUgrid</name>
      <anchorfile>_xm_u_grid_8cpp.html</anchorfile>
      <anchor>a04813632c5ac95012309de3bfb012ecd</anchor>
      <arglist>(const int a_rows, const int a_cols, const int a_lays)</arglist>
    </member>
    <member kind="function">
      <type>BSHP&lt; xms::XmUGrid &gt;</type>
      <name>TEST_XmUBuildHexahedronUgrid</name>
      <anchorfile>_xm_u_grid_8cpp.html</anchorfile>
      <anchor>a2f51be4a06745affc9b668b5dc6f98e4</anchor>
      <arglist>(const int a_rows, const int a_cols, const int a_lays, const xms::Pt3d &amp;a_origin)</arglist>
    </member>
    <member kind="function">
      <type>BSHP&lt; xms::XmUGrid &gt;</type>
      <name>TEST_XmUBuildPolyhedronUgrid</name>
      <anchorfile>_xm_u_grid_8cpp.html</anchorfile>
      <anchor>adeaa5d1fea81372470f12da9ec83ba78</anchor>
      <arglist>(const int a_rows, const int a_cols, const int a_lays)</arglist>
    </member>
    <member kind="function">
      <type>BSHP&lt; xms::XmUGrid &gt;</type>
      <name>TEST_XmUBuildPolyhedronUgrid</name>
      <anchorfile>_xm_u_grid_8cpp.html</anchorfile>
      <anchor>ae9fdec50edd37d192bde9fdfb7670bf6</anchor>
      <arglist>(const int a_rows, const int a_cols, const int a_lays, const xms::Pt3d &amp;a_origin)</arglist>
    </member>
    <member kind="function">
      <type>BSHP&lt; xms::XmUGrid &gt;</type>
      <name>TEST_XmUBuild3DChevronUgrid</name>
      <anchorfile>_xm_u_grid_8cpp.html</anchorfile>
      <anchor>ab1a6ab331c942a001ff9b1ec8547f0fc</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>TestFilesPath</name>
      <anchorfile>_xm_u_grid_8cpp.html</anchorfile>
      <anchor>a5077e9a31a7514c737aec71ff1732e1c</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>XmUGrid.h</name>
    <path>/home/travis/build/Aquaveo/xmsgrid/xmsgrid/ugrid/</path>
    <filename>_xm_u_grid_8h</filename>
    <class kind="class">xms::XmUGrid</class>
    <namespace>xms</namespace>
    <member kind="enumeration">
      <type></type>
      <name>XmUGridCellType</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ac31bf74ccc479f6e1c2ae761d3d727a9</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>XmUGridFaceOrientation</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a136ad631d47aa5714f72cdc84fd8dca5</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>XmUGrid.t.h</name>
    <path>/home/travis/build/Aquaveo/xmsgrid/xmsgrid/ugrid/</path>
    <filename>_xm_u_grid_8t_8h</filename>
    <class kind="class">XmUGridUnitTests</class>
    <namespace>xms</namespace>
    <member kind="function">
      <type>BSHP&lt; xms::XmUGrid &gt;</type>
      <name>TEST_XmUGrid1Left90Tri</name>
      <anchorfile>_xm_u_grid_8t_8h.html</anchorfile>
      <anchor>aca49995f7999090d4bbc65064b3b8030</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>BSHP&lt; xms::XmUGrid &gt;</type>
      <name>TEST_XmUGridSimpleQuad</name>
      <anchorfile>_xm_u_grid_8t_8h.html</anchorfile>
      <anchor>aca819ffe97cb3a3312d0721806f23e84</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>BSHP&lt; xms::XmUGrid &gt;</type>
      <name>TEST_XmUGrid2dLinear</name>
      <anchorfile>_xm_u_grid_8t_8h.html</anchorfile>
      <anchor>a5976110638c41e3737f1ffeb4616a2af</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>BSHP&lt; xms::XmUGrid &gt;</type>
      <name>TEST_XmUGrid3dLinear</name>
      <anchorfile>_xm_u_grid_8t_8h.html</anchorfile>
      <anchor>a898484f0cee714496582b3023a1d0ab5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>BSHP&lt; xms::XmUGrid &gt;</type>
      <name>TEST_XmUGridHexagonalPolyhedron</name>
      <anchorfile>_xm_u_grid_8t_8h.html</anchorfile>
      <anchor>aa4c036b5a8c4a975166c4f846315c183</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>BSHP&lt; xms::XmUGrid &gt;</type>
      <name>TEST_XmUBuildQuadUGrid</name>
      <anchorfile>_xm_u_grid_8t_8h.html</anchorfile>
      <anchor>a95cce469cb2bf795b70937e09bea4a78</anchor>
      <arglist>(const int a_rows, const int a_cols)</arglist>
    </member>
    <member kind="function">
      <type>BSHP&lt; xms::XmUGrid &gt;</type>
      <name>TEST_XmUBuildQuadUGrid</name>
      <anchorfile>_xm_u_grid_8t_8h.html</anchorfile>
      <anchor>a21c30167b814e37425f763241ec39063</anchor>
      <arglist>(const int a_rows, const int a_cols, const xms::Pt3d &amp;a_origin)</arglist>
    </member>
    <member kind="function">
      <type>BSHP&lt; xms::XmUGrid &gt;</type>
      <name>TEST_XmUBuildHexahedronUgrid</name>
      <anchorfile>_xm_u_grid_8t_8h.html</anchorfile>
      <anchor>a04813632c5ac95012309de3bfb012ecd</anchor>
      <arglist>(const int a_rows, const int a_cols, const int a_lays)</arglist>
    </member>
    <member kind="function">
      <type>BSHP&lt; xms::XmUGrid &gt;</type>
      <name>TEST_XmUBuildHexahedronUgrid</name>
      <anchorfile>_xm_u_grid_8t_8h.html</anchorfile>
      <anchor>a2f51be4a06745affc9b668b5dc6f98e4</anchor>
      <arglist>(const int a_rows, const int a_cols, const int a_lays, const xms::Pt3d &amp;a_origin)</arglist>
    </member>
    <member kind="function">
      <type>BSHP&lt; xms::XmUGrid &gt;</type>
      <name>TEST_XmUBuildPolyhedronUgrid</name>
      <anchorfile>_xm_u_grid_8t_8h.html</anchorfile>
      <anchor>adeaa5d1fea81372470f12da9ec83ba78</anchor>
      <arglist>(const int a_rows, const int a_cols, const int a_lays)</arglist>
    </member>
    <member kind="function">
      <type>BSHP&lt; xms::XmUGrid &gt;</type>
      <name>TEST_XmUBuildPolyhedronUgrid</name>
      <anchorfile>_xm_u_grid_8t_8h.html</anchorfile>
      <anchor>ae9fdec50edd37d192bde9fdfb7670bf6</anchor>
      <arglist>(const int a_rows, const int a_cols, const int a_lays, const xms::Pt3d &amp;a_origin)</arglist>
    </member>
    <member kind="function">
      <type>BSHP&lt; xms::XmUGrid &gt;</type>
      <name>TEST_XmUBuild3DChevronUgrid</name>
      <anchorfile>_xm_u_grid_8t_8h.html</anchorfile>
      <anchor>ab1a6ab331c942a001ff9b1ec8547f0fc</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>TestFilesPath</name>
      <anchorfile>_xm_u_grid_8t_8h.html</anchorfile>
      <anchor>a5077e9a31a7514c737aec71ff1732e1c</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>XmUGridUtils.cpp</name>
    <path>/home/travis/build/Aquaveo/xmsgrid/xmsgrid/ugrid/</path>
    <filename>_xm_u_grid_utils_8cpp</filename>
    <includes id="_xm_u_grid_utils_8h" name="XmUGridUtils.h" local="no" imported="no">xmsgrid/ugrid/XmUGridUtils.h</includes>
    <includes id="_xm_u_grid_8h" name="XmUGrid.h" local="no" imported="no">xmsgrid/ugrid/XmUGrid.h</includes>
    <includes id="_xm_u_grid_8t_8h" name="XmUGrid.t.h" local="no" imported="no">xmsgrid/ugrid/XmUGrid.t.h</includes>
    <includes id="_xm_u_grid_utils_8t_8h" name="XmUGridUtils.t.h" local="no" imported="no">xmsgrid/ugrid/XmUGridUtils.t.h</includes>
    <namespace>xms</namespace>
    <member kind="function">
      <type>BSHP&lt; XmUGrid &gt;</type>
      <name>XmReadUGridFromAsciiFile</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a92b5c5c0a9e2455db6d671eb7134a76e</anchor>
      <arglist>(const std::string &amp;a_filePath)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>XmWriteUGridToAsciiFile</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>aad684d8d566604305a00cc4d875dd51e</anchor>
      <arglist>(BSHP&lt; XmUGrid &gt; a_ugrid, const std::string &amp;a_filePath)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>cross</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a19d9cf623f58dfd2c0f07818b00c3ef0</anchor>
      <arglist>(const Pt3d &amp;a_origin, const Pt3d &amp;a_A, const Pt3d &amp;a_B)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>DoLineSegmentsCross</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ae637b67d3f1510d9d944bbf58b357f96</anchor>
      <arglist>(const std::pair&lt; Pt3d, Pt3d &gt; &amp;a_segment1, const std::pair&lt; Pt3d, Pt3d &gt; &amp;a_segment2)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>DoLineSegmentsCross</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a65c87e21852eec5a00868110b3cdc729</anchor>
      <arglist>(const Pt3d &amp;a_segment1Point1, const Pt3d &amp;a_segment1Point2, const Pt3d &amp;a_segment2Point1, const Pt3d &amp;a_segment2Point2)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>XmUGridUtils.h</name>
    <path>/home/travis/build/Aquaveo/xmsgrid/xmsgrid/ugrid/</path>
    <filename>_xm_u_grid_utils_8h</filename>
    <namespace>xms</namespace>
  </compound>
  <compound kind="file">
    <name>XmUGridUtils.t.h</name>
    <path>/home/travis/build/Aquaveo/xmsgrid/xmsgrid/ugrid/</path>
    <filename>_xm_u_grid_utils_8t_8h</filename>
    <class kind="class">XmUGridUtilsTests</class>
  </compound>
  <compound kind="page">
    <name>md_FileIO_Tutorial</name>
    <title>UGrid File IO Tutorial</title>
    <filename>md__file_i_o__tutorial</filename>
    <docanchor file="md__file_i_o__tutorial" title="UGrid File IO Tutorial">FileIO_Tutorial</docanchor>
    <docanchor file="md__file_i_o__tutorial" title="Introduction">Intro_FileIO</docanchor>
    <docanchor file="md__file_i_o__tutorial" title="Example - Writing UGrid data to ASCII file format">Example_XmWriteUGridFromAsciiFile</docanchor>
    <docanchor file="md__file_i_o__tutorial" title="Example - Reading a UGrid from ASCII file format">Example_XmReadUGridFromAsciiFile</docanchor>
  </compound>
  <compound kind="page">
    <name>md_ThreeD_Tutorial</name>
    <title>3D UGrid Tutorial</title>
    <filename>md__three_d__tutorial</filename>
    <docanchor file="md__three_d__tutorial" title="3D UGrid Tutorial">ThreeD_Tutorial</docanchor>
    <docanchor file="md__three_d__tutorial" title="Introduction">Intro_3Ugrid</docanchor>
    <docanchor file="md__three_d__tutorial" title="Example - Defining Ugrid Cells">Example_DefiningA3dUGridCell</docanchor>
    <docanchor file="md__three_d__tutorial" title="Example - Creating a New 3D UGrid With Data">Example_New_With_Data_3d</docanchor>
    <docanchor file="md__three_d__tutorial" title="Example - Creating a New 3D UGrid">Example_New3d</docanchor>
    <docanchor file="md__three_d__tutorial" title="Example - Setting the UGrid Points">Example_SetPoints3d</docanchor>
    <docanchor file="md__three_d__tutorial" title="Example - Setting the UGrid Cell Stream">Example_SetCellStream3d</docanchor>
    <docanchor file="md__three_d__tutorial" title="Example - Validating the Cellstream">Example_ValidatingCellStream3d</docanchor>
    <docanchor file="md__three_d__tutorial" title="Example - Get Number Of Points">Example_GetNumberOfPoints3d</docanchor>
    <docanchor file="md__three_d__tutorial" title="Example - Get Points">Example_GetPoints3d</docanchor>
    <docanchor file="md__three_d__tutorial" title="Example - Get Point">Example_GetPoint3d</docanchor>
    <docanchor file="md__three_d__tutorial" title="Example - Set Point">Example_SetPoint3d</docanchor>
    <docanchor file="md__three_d__tutorial" title="Example - Get Points from Point Indices">Example_GetPointsFromPointIdxs3d</docanchor>
    <docanchor file="md__three_d__tutorial" title="Example - Get Extents of UGrid">Example_GetExtents3d</docanchor>
    <docanchor file="md__three_d__tutorial" title="Example - Get Cells Associated with a Point">Example_GetPointCells3d</docanchor>
    <docanchor file="md__three_d__tutorial" title="Example - Get the Cells that Share the Same Point or Points">Example_GetCommonCells3d</docanchor>
    <docanchor file="md__three_d__tutorial" title="Example - Get the Points of a Cell">Example_GetPointsOfCell3d</docanchor>
    <docanchor file="md__three_d__tutorial" title="Example - Get the Type of a Cell">Example_GetCellType3d</docanchor>
    <docanchor file="md__three_d__tutorial" title="Example - Get the Count of the Dimensions of Cells used in a UGrid">Example_GetDimensionCount3d</docanchor>
    <docanchor file="md__three_d__tutorial" title="Example - Get the Dimension of a Cell">Example_GetCellDimension3d</docanchor>
    <docanchor file="md__three_d__tutorial" title="Example - Get the Cellstream of the UGrid">Example_GetCellStream3d</docanchor>
    <docanchor file="md__three_d__tutorial" title="Example - Get a Single Cellstream for One Cell">Example_GetSingleCellStream3d</docanchor>
    <docanchor file="md__three_d__tutorial" title="Example - Get the Cells that Neighbor a Given Cell">Example_GetCellNeighbors3d</docanchor>
    <docanchor file="md__three_d__tutorial" title="Example - Get a Plan View Polygon">Example_GetPlanViewPolygon3d</docanchor>
    <docanchor file="md__three_d__tutorial" title="Example - Get Number of Cell Edges">Example_GetNumberOfCellEdges3d</docanchor>
    <docanchor file="md__three_d__tutorial" title="Example - Get Cell Edge from Edge Index">Example_GetCellEdgeFromEdgeIndex3d</docanchor>
    <docanchor file="md__three_d__tutorial" title="Example Get Adjacent Cells">Example_GetAdjacentCells3d</docanchor>
    <docanchor file="md__three_d__tutorial" title="Example Get Adjacent Cells from Given Edge">Example_GetAdjacentCellsFromAGivenEdge3d</docanchor>
    <docanchor file="md__three_d__tutorial" title="Example Get Edges Associated with a Point">Example_GetEdgesFromPoint3d</docanchor>
    <docanchor file="md__three_d__tutorial" title="Example Get Edges Associated with a Cell">Example_GetEdgesOfCell3d</docanchor>
    <docanchor file="md__three_d__tutorial" title="Example Get Number of Faces for a Cell">Example_GetNumberOfFacesForCell</docanchor>
    <docanchor file="md__three_d__tutorial" title="Example Get Cell Face">Example_GetCellFace</docanchor>
    <docanchor file="md__three_d__tutorial" title="Example Get Faces of Cell">Example_GetFacesOfCell</docanchor>
    <docanchor file="md__three_d__tutorial" title="Example GetFacesFromPoint">Example_GetFacesFromPoint</docanchor>
    <docanchor file="md__three_d__tutorial" title="Example Get Cell Face Neighbor">Example_GetCellFaceNeighbor</docanchor>
  </compound>
  <compound kind="page">
    <name>md_TwoD_Tutorial</name>
    <title>2D UGrid Tutorial</title>
    <filename>md__two_d__tutorial</filename>
    <docanchor file="md__two_d__tutorial" title="2D UGrid Tutorial">TwoD_Tutorial</docanchor>
    <docanchor file="md__two_d__tutorial" title="Introduction">Intro_2Ugrid</docanchor>
    <docanchor file="md__two_d__tutorial" title="Example - Defining Ugrid Cells">Example_DefiningA2dUGridCell</docanchor>
    <docanchor file="md__two_d__tutorial" title="Example - Creating a New 2D UGrid With Data">Example_New_With_Data_2d</docanchor>
    <docanchor file="md__two_d__tutorial" title="Example - Creating a New 2D UGrid">Example_New2d</docanchor>
    <docanchor file="md__two_d__tutorial" title="Example - Setting the UGrid Points">Example_SetPoints2d</docanchor>
    <docanchor file="md__two_d__tutorial" title="Example - Setting the UGrid Cell Stream">Example_SetCellStream2d</docanchor>
    <docanchor file="md__two_d__tutorial" title="Example - Validating the Cellstream">Example_ValidatingCellStream2d</docanchor>
    <docanchor file="md__two_d__tutorial" title="Example - Get Number Of Points">Example_GetNumberOfPoints2d</docanchor>
    <docanchor file="md__two_d__tutorial" title="Example - Get Points">Example_GetPoints2d</docanchor>
    <docanchor file="md__two_d__tutorial" title="Example - Get Point">Example_GetPoint2d</docanchor>
    <docanchor file="md__two_d__tutorial" title="Example - Set Point">Example_SetPoint2d</docanchor>
    <docanchor file="md__two_d__tutorial" title="Example - Get Points from Point Indices">Example_GetPointsFromPointIdxs2d</docanchor>
    <docanchor file="md__two_d__tutorial" title="Example - Get Extents of UGrid">Example_GetExtents2d</docanchor>
    <docanchor file="md__two_d__tutorial" title="Example - Get Cells Associated with a Point">Example_GetPointCells2d</docanchor>
    <docanchor file="md__two_d__tutorial" title="Example - Get the Cells that Share the Same Point or Points">Example_GetCommonCells2d</docanchor>
    <docanchor file="md__two_d__tutorial" title="Example - Get the Points of a Cell">Example_GetPointsOfCell2d</docanchor>
    <docanchor file="md__two_d__tutorial" title="Example - Get the Type of a Cell">Example_GetCellType2d</docanchor>
    <docanchor file="md__two_d__tutorial" title="Example - Get the Count of the Dimensions of Cells used in a UGrid">Example_GetDimensionCount2d</docanchor>
    <docanchor file="md__two_d__tutorial" title="Example - Get the Dimension of a Cell">Example_GetCellDimension2d</docanchor>
    <docanchor file="md__two_d__tutorial" title="Example - Get the Cellstream of the UGrid">Example_GetCellStream2d</docanchor>
    <docanchor file="md__two_d__tutorial" title="Example - Get a Single Cellstream for One Cell">Example_GetSingleCellStream2d</docanchor>
    <docanchor file="md__two_d__tutorial" title="Example - Get the Cells that Neighbor a Given Cell">Example_GetCellNeighbors2d</docanchor>
    <docanchor file="md__two_d__tutorial" title="Example - Get a Plan View Polygon">Example_GetPlanViewPolygon2d</docanchor>
    <docanchor file="md__two_d__tutorial" title="Example - Get Number of Cell Edges">Example_GetNumberOfCellEdges2d</docanchor>
    <docanchor file="md__two_d__tutorial" title="Example - Get Cell Edge from Edge Index">Example_GetCellEdgeFromEdgeIndex2d</docanchor>
    <docanchor file="md__two_d__tutorial" title="Example Get Adjacent Cells">Example_GetAdjacentCells2d</docanchor>
    <docanchor file="md__two_d__tutorial" title="Example 2D Get Adjacent Cell">Example_GetAdjacent2DCell</docanchor>
    <docanchor file="md__two_d__tutorial" title="Example Get Adjacent Cells from Given Edge">Example_GetAdjacentCellsFromAGivenEdge2d</docanchor>
    <docanchor file="md__two_d__tutorial" title="Example Get Edges Associated with a Point">Example_GetEdgesFromPoint2d</docanchor>
    <docanchor file="md__two_d__tutorial" title="Example Get Edges Associated with a Cell">Example_GetEdgesOfCell2d</docanchor>
  </compound>
  <compound kind="class">
    <name>XmUGridConvexHullTests</name>
    <filename>class_xm_u_grid_convex_hull_tests.html</filename>
    <member kind="function">
      <type>void</type>
      <name>testConvexHull</name>
      <anchorfile>class_xm_u_grid_convex_hull_tests.html</anchorfile>
      <anchor>a9932d57a000ebc02420243211c67858c</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>XmUGridTests</name>
    <filename>class_xm_u_grid_tests.html</filename>
  </compound>
  <compound kind="class">
    <name>XmUGridUnitTests</name>
    <filename>class_xm_u_grid_unit_tests.html</filename>
    <member kind="function">
      <type>void</type>
      <name>testUGridStreams</name>
      <anchorfile>class_xm_u_grid_unit_tests.html</anchorfile>
      <anchor>afecce71921cd7ff64d695314747a48aa</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testGetSetPoint</name>
      <anchorfile>class_xm_u_grid_unit_tests.html</anchorfile>
      <anchor>a8e9168df5e65f86cfbc2dbb22a44e9af</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testGetSingleCellStream</name>
      <anchorfile>class_xm_u_grid_unit_tests.html</anchorfile>
      <anchor>a956c11f1adbf6731ace66141e05a572c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testGetCellType</name>
      <anchorfile>class_xm_u_grid_unit_tests.html</anchorfile>
      <anchor>afa1aba19187a3773dfd67177f69fd61c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testGetCellDimension</name>
      <anchorfile>class_xm_u_grid_unit_tests.html</anchorfile>
      <anchor>af94b78cd1c7f2bb1824cb970907825c2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testGetExtents</name>
      <anchorfile>class_xm_u_grid_unit_tests.html</anchorfile>
      <anchor>a77d4e944bf291f94ededbcbedb295fe9</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testGetNumberOfCellEdges</name>
      <anchorfile>class_xm_u_grid_unit_tests.html</anchorfile>
      <anchor>ac283bd38692be27a8563e21442ce5a7f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testGetNumberOfCellFaces</name>
      <anchorfile>class_xm_u_grid_unit_tests.html</anchorfile>
      <anchor>a0b7654d480a614b3c72111a747fbe81a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testGetPointCellsSimple</name>
      <anchorfile>class_xm_u_grid_unit_tests.html</anchorfile>
      <anchor>ab50f5c7cf55771608109343a1bd3a9e6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testGetPointCells</name>
      <anchorfile>class_xm_u_grid_unit_tests.html</anchorfile>
      <anchor>a187f111d6cafc089a46c3f82d8d77bd4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testGetPointsOfCell</name>
      <anchorfile>class_xm_u_grid_unit_tests.html</anchorfile>
      <anchor>aa23a5330e8dc3a8856f45b27f87f7c96</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testGetCellEdgeFromEdgeIndex</name>
      <anchorfile>class_xm_u_grid_unit_tests.html</anchorfile>
      <anchor>ae97216226f2f4d5d684f86b0608d97c0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testGetCommonCells</name>
      <anchorfile>class_xm_u_grid_unit_tests.html</anchorfile>
      <anchor>a99cb1ad502fe6c389fc506794c1d47dc</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testGetCellNeighbors</name>
      <anchorfile>class_xm_u_grid_unit_tests.html</anchorfile>
      <anchor>a10b3052cdef189ebcc6e28576a76dcfe</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testGetAdjacentCell</name>
      <anchorfile>class_xm_u_grid_unit_tests.html</anchorfile>
      <anchor>ad1668ba70a8c5e40716a6c5623f77487</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testGetAdjacentCellsFromGivenEdge</name>
      <anchorfile>class_xm_u_grid_unit_tests.html</anchorfile>
      <anchor>a22bf030434d4e2e88f5ad2c6b9af0d32</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testGetCellFace</name>
      <anchorfile>class_xm_u_grid_unit_tests.html</anchorfile>
      <anchor>ae7786d38753b3f9d38fe53b6209c8689</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testGetCellFaceNeighbor</name>
      <anchorfile>class_xm_u_grid_unit_tests.html</anchorfile>
      <anchor>ab7b72fe22de02cf826a13b56cf0b5c1f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testGetEdgesFromPoint</name>
      <anchorfile>class_xm_u_grid_unit_tests.html</anchorfile>
      <anchor>ab6185927ee58d0fb24bc6ec8d20f36d5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testGetFacesFromPoint</name>
      <anchorfile>class_xm_u_grid_unit_tests.html</anchorfile>
      <anchor>a3bfd0a5f476433f5cf129ea8809b213b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testGetPlanViewPolygon</name>
      <anchorfile>class_xm_u_grid_unit_tests.html</anchorfile>
      <anchor>a9ea4bb73723dd9b65ad043e9bc4f4144</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testIsCellValidWithPointChange</name>
      <anchorfile>class_xm_u_grid_unit_tests.html</anchorfile>
      <anchor>ac5a30921fdb122b8ef60fbd12365957e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testPointFunctions</name>
      <anchorfile>class_xm_u_grid_unit_tests.html</anchorfile>
      <anchor>ae950f2efb2ef0e1d655bf12ed1803f83</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testCellFunctions</name>
      <anchorfile>class_xm_u_grid_unit_tests.html</anchorfile>
      <anchor>aa04937d86269192d53cf353366f6fdd5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testGetCellStreamFunctions</name>
      <anchorfile>class_xm_u_grid_unit_tests.html</anchorfile>
      <anchor>a161f884b0ca131ac8c9a689a0413b1e5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testGetAdjacentCellFunctions</name>
      <anchorfile>class_xm_u_grid_unit_tests.html</anchorfile>
      <anchor>aed54639cef412b0227d0726bce50ea08</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testGetEdgesOfCell</name>
      <anchorfile>class_xm_u_grid_unit_tests.html</anchorfile>
      <anchor>a9fbe5c625e131c222db1d9a39db33030</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testGetFaces</name>
      <anchorfile>class_xm_u_grid_unit_tests.html</anchorfile>
      <anchor>ac8fa905af3b1c7f8c37e45a407a9d879</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testLargeUGridLinkSpeed</name>
      <anchorfile>class_xm_u_grid_unit_tests.html</anchorfile>
      <anchor>a8e9078332f58080823880c04eb37b94f</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>XmUGridUtilsTests</name>
    <filename>class_xm_u_grid_utils_tests.html</filename>
    <member kind="function">
      <type>void</type>
      <name>testDoLineSegmentsCross</name>
      <anchorfile>class_xm_u_grid_utils_tests.html</anchorfile>
      <anchor>abdb6587684de536f93a0905e482d089e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testWriteEmptyUGrid</name>
      <anchorfile>class_xm_u_grid_utils_tests.html</anchorfile>
      <anchor>ae129def9be2e32d8c6d83d78c9c37ae7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testWriteBasicUGrid</name>
      <anchorfile>class_xm_u_grid_utils_tests.html</anchorfile>
      <anchor>a172a6cebc93b9994ecf18a3ba9bb132d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testWritePolyhedronUGrid</name>
      <anchorfile>class_xm_u_grid_utils_tests.html</anchorfile>
      <anchor>a949bc5905ca9a311a092d2f374c5d5d0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testWriteLinear2dCells</name>
      <anchorfile>class_xm_u_grid_utils_tests.html</anchorfile>
      <anchor>a9df062db461cc199119fbe4adedaa691</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testWriteLinear3dCells</name>
      <anchorfile>class_xm_u_grid_utils_tests.html</anchorfile>
      <anchor>a629b501a387b6524a57d95a7045f1831</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testReadEmptyUGridAsciiFile</name>
      <anchorfile>class_xm_u_grid_utils_tests.html</anchorfile>
      <anchor>a5607c25084625c39f57b4543d92be1a0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testReadBasicUGrid</name>
      <anchorfile>class_xm_u_grid_utils_tests.html</anchorfile>
      <anchor>a7be71d4f80017a95dd49dbadb4cd65dd</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testReadPolyhedronUGrid</name>
      <anchorfile>class_xm_u_grid_utils_tests.html</anchorfile>
      <anchor>a4687768140c2f7e1144fdf4fd7d8a788</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testLinear2dWriteThenRead</name>
      <anchorfile>class_xm_u_grid_utils_tests.html</anchorfile>
      <anchor>a227b7f77870cc134ba5f2f990c21394a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testLinear3dWriteThenRead</name>
      <anchorfile>class_xm_u_grid_utils_tests.html</anchorfile>
      <anchor>a3d076a2cc5eb610df6af33d449dfe2a3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testWriteThenReadUGridFile</name>
      <anchorfile>class_xm_u_grid_utils_tests.html</anchorfile>
      <anchor>a9e19de983e2643b00e9df0f8df8c77e0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testWriteThenReadUGridFileToAscii</name>
      <anchorfile>class_xm_u_grid_utils_tests.html</anchorfile>
      <anchor>a3fae7052c1ceee482e3453f7c45247f8</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="namespace">
    <name>python::ugrid::XmUGrid_pyt</name>
    <filename>namespacepython_1_1ugrid_1_1_xm_u_grid__pyt.html</filename>
    <class kind="class">python::ugrid::XmUGrid_pyt::TestXmUGridPointFunctions</class>
    <class kind="class">python::ugrid::XmUGrid_pyt::TestXmUGridCellTypeEnum</class>
    <class kind="class">python::ugrid::XmUGrid_pyt::TestXmUGridFaceOrientationEnum</class>
  </compound>
  <compound kind="class">
    <name>python::ugrid::XmUGrid_pyt::TestXmUGridPointFunctions</name>
    <filename>classpython_1_1ugrid_1_1_xm_u_grid__pyt_1_1_test_xm_u_grid_point_functions.html</filename>
  </compound>
  <compound kind="class">
    <name>python::ugrid::XmUGrid_pyt::TestXmUGridCellTypeEnum</name>
    <filename>classpython_1_1ugrid_1_1_xm_u_grid__pyt_1_1_test_xm_u_grid_cell_type_enum.html</filename>
  </compound>
  <compound kind="class">
    <name>python::ugrid::XmUGrid_pyt::TestXmUGridFaceOrientationEnum</name>
    <filename>classpython_1_1ugrid_1_1_xm_u_grid__pyt_1_1_test_xm_u_grid_face_orientation_enum.html</filename>
  </compound>
  <compound kind="class">
    <name>python::ugrid::XmUGridUtils_pyt::TestXmUGridUtilFunctions</name>
    <filename>classpython_1_1ugrid_1_1_xm_u_grid_utils__pyt_1_1_test_xm_u_grid_util_functions.html</filename>
  </compound>
  <compound kind="namespace">
    <name>xms</name>
    <filename>namespacexms.html</filename>
    <class kind="class">xms::XmUGridImpl</class>
    <class kind="class">xms::XmUGrid</class>
    <member kind="enumeration">
      <type></type>
      <name>XmUGridCellType</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ac31bf74ccc479f6e1c2ae761d3d727a9</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>XmUGridFaceOrientation</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a136ad631d47aa5714f72cdc84fd8dca5</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; Pt3d &gt;</type>
      <name>ConvexHull</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a1973dbb5cf1431334a569f565b1c7d13</anchor>
      <arglist>(std::vector&lt; Pt3d &gt; a_points)</arglist>
    </member>
    <member kind="function">
      <type>VecInt</type>
      <name>ConvexHullWithIndices</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ac022fbaa831f7fc3362547238bad840a</anchor>
      <arglist>(const VecInt &amp;a_points, BSHP&lt; XmUGrid &gt; a_ugrid)</arglist>
    </member>
    <member kind="function">
      <type>BSHP&lt; XmUGrid &gt;</type>
      <name>XmReadUGridFromAsciiFile</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a92b5c5c0a9e2455db6d671eb7134a76e</anchor>
      <arglist>(const std::string &amp;a_filePath)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>XmWriteUGridToAsciiFile</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>aad684d8d566604305a00cc4d875dd51e</anchor>
      <arglist>(BSHP&lt; XmUGrid &gt; a_ugrid, const std::string &amp;a_filePath)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>cross</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a19d9cf623f58dfd2c0f07818b00c3ef0</anchor>
      <arglist>(const Pt3d &amp;a_origin, const Pt3d &amp;a_A, const Pt3d &amp;a_B)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>DoLineSegmentsCross</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ae637b67d3f1510d9d944bbf58b357f96</anchor>
      <arglist>(const std::pair&lt; Pt3d, Pt3d &gt; &amp;a_segment1, const std::pair&lt; Pt3d, Pt3d &gt; &amp;a_segment2)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>DoLineSegmentsCross</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a65c87e21852eec5a00868110b3cdc729</anchor>
      <arglist>(const Pt3d &amp;a_segment1Point1, const Pt3d &amp;a_segment1Point2, const Pt3d &amp;a_segment2Point1, const Pt3d &amp;a_segment2Point2)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>xms::XmUGridImpl</name>
    <filename>classxms_1_1_xm_u_grid_impl.html</filename>
    <base>xms::XmUGrid</base>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>GetNumberOfPoints</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>a7d11b54530e3925943587e1f4480355b</anchor>
      <arglist>() const override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const VecPt3d &amp;</type>
      <name>GetPoints</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>a033f6aaa6e64b716bfa334148198630c</anchor>
      <arglist>() const override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>SetPoints</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>a3dd17d1fd619346f4d0e90a34ae94cf9</anchor>
      <arglist>(const VecPt3d &amp;a_points) override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual Pt3d</type>
      <name>GetPoint</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>ac3354503ac19b717b8619391b0a3eb01</anchor>
      <arglist>(const int a_pointIdx) const override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>SetPoint</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>aeb29c91957f552beae6f922d963070b6</anchor>
      <arglist>(const int a_pointIdx, const Pt3d &amp;a_point) override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual VecPt3d</type>
      <name>GetPointsFromPointIdxs</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>a5033536262ea9abed24cca4da985aa60</anchor>
      <arglist>(const VecInt &amp;a_points) const override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>GetExtents</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>a110228f473bdce917fdae9edfd3ea970</anchor>
      <arglist>(Pt3d &amp;a_min, Pt3d &amp;a_max) const override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual VecInt</type>
      <name>GetPointCells</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>a5914a901abb898e83ec0dbb5e466ef2d</anchor>
      <arglist>(const int a_pointIdx) const override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>GetPointCells</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>aeb1b007fd36f0b4863952632373ae8e2</anchor>
      <arglist>(const int a_pointIdx, VecInt &amp;a_attachedCellIdxs) const override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual VecInt</type>
      <name>GetCommonCells</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>a5a1c0c6182486cdc3af32029df1997ea</anchor>
      <arglist>(const VecInt &amp;a_points) const override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>GetCommonCells</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>a930d9c285a2fb10f4973b12589423fa2</anchor>
      <arglist>(const int *a_pointIdxs, int a_numpointIdxs, VecInt &amp;a_commonCellIdxs) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>GetCommonCells</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>a767a1ea118fa6c3f91760a4375bb6047</anchor>
      <arglist>(const VecInt &amp;a_points, VecInt &amp;a_commonCellIdxs) const override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>GetCommonCells</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>ac02a9605873e356f281ea7f4901a9642</anchor>
      <arglist>(const int a_ptIdx1, const int a_ptIdx2, VecInt &amp;a_commonCellIdxs) const override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>GetNumberOfCells</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>a00a62d8ed93904cbd4cf270394cfe748</anchor>
      <arglist>() const override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual VecInt</type>
      <name>GetPointsOfCell</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>a33e622b0d2bae98669f462ad43518235</anchor>
      <arglist>(const int a_cellIdx) const override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>GetPointsOfCell</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>a6599776c7ebcd8db5339bbb40289bf46</anchor>
      <arglist>(const int a_cellIdx, VecInt &amp;a_cellPoints) const override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual XmUGridCellType</type>
      <name>GetCellType</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>a36d0b59da6296f1e990583cad17c86f5</anchor>
      <arglist>(const int a_cellIdx) const override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual std::vector&lt; int &gt;</type>
      <name>GetDimensionCount</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>a3a1f3e0d8166e40b1f23cfe20827c2b0</anchor>
      <arglist>() const override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>GetCellDimension</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>a672fe28101f211d9291001e0ce6a5318</anchor>
      <arglist>(const int a_cellIdx) const override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const VecInt &amp;</type>
      <name>GetCellStream</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>a01973db2557667f57acd11fc1c5af393</anchor>
      <arglist>() const override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>SetCellStream</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>a207213ebc3c71b3b616d153985e10a29</anchor>
      <arglist>(const VecInt &amp;a_cellStream) override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>GetSingleCellStream</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>a0e5b02d9ed300c32ca8ca9fab9e2538f</anchor>
      <arglist>(const int a_cellIdx, VecInt &amp;a_cellStream) const override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual VecInt</type>
      <name>GetCellNeighbors</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>a1d3d657289605c92c9060aa4caf82788</anchor>
      <arglist>(const int a_cellIdx) const override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>GetCellNeighbors</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>aaa181863e578e2335811f268d8de89d0</anchor>
      <arglist>(const int a_cellIdx, VecInt &amp;a_cellNeighbors) const override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>GetPlanViewPolygon</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>ac697de12080085c4390901b6886f3c34</anchor>
      <arglist>(int a_cellIdx, VecPt3d &amp;a_polygon) const override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>GetNumberOfCellEdges</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>a5a61c779956a8fe779165f424e5f207f</anchor>
      <arglist>(const int a_cellIdx) const override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual std::pair&lt; int, int &gt;</type>
      <name>GetCellEdgeFromEdgeIndex</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>af384b14abc004867fd83c648a409ba42</anchor>
      <arglist>(const int a_cellIdx, const int a_edgeIdx) const override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual VecInt</type>
      <name>GetAdjacentCells</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>aca7001e994cb008ff79ce51ab6dade80</anchor>
      <arglist>(const int a_cellIdx, const int a_edgeIdx) const override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>GetAdjacentCells</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>a5ecc5936065410531ad8aa1dad85ffa0</anchor>
      <arglist>(const int a_cellIdx, const int a_edgeIdx, VecInt &amp;a_adjacentCellIdxs) const override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>Get2dAdjacentCell</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>aa92a854c953c726ac57593b5b4b0106f</anchor>
      <arglist>(const int a_cellIdx, const int a_edgeIdx) const override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual VecInt</type>
      <name>GetAdjacentCellsFromGivenEdge</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>ac371852cdb7b830b52f29a8e9b63895d</anchor>
      <arglist>(const int a_pointIdx1, const int a_pointIdx2) const override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>GetAdjacentCellsFromGivenEdge</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>a68b8994e2b85f742b1098c3d57c56e5f</anchor>
      <arglist>(const int a_pointIdx1, const int a_pointIdx2, VecInt &amp;a_adjacentCellIdxs) const override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual VecInt</type>
      <name>GetAdjacentCellsFromGivenEdge</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>a52a55a45f08e054c19427e60cde0473d</anchor>
      <arglist>(const std::pair&lt; int, int &gt; a_edge) const override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>GetEdgesFromPoint</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>a5661f008bb6e01543cc80b8279f5be0b</anchor>
      <arglist>(const int a_pointId, VecInt &amp;a_cellIdxs, VecInt &amp;a_edgeIdxs) const override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>GetEdgesFromPoint</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>ac5d1a726d9602b06b3578f9bb40fe822</anchor>
      <arglist>(const int a_pointId, VecInt &amp;a_cellIdxs, std::vector&lt; std::pair&lt; int, int &gt;&gt; &amp;a_edges) const override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>GetEdgesFromPoint</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>a07b1eecb9de76ca50a995d19e2f58b48</anchor>
      <arglist>(const int a_pointId, VecInt &amp;a_cellIdxs, VecInt &amp;a_edgePoints1, VecInt &amp;a_edgePoints2) const override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual std::vector&lt; std::pair&lt; int, int &gt; &gt;</type>
      <name>GetEdgesOfCell</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>a8222666c6e8747a5f81f602ad87a7c44</anchor>
      <arglist>(const int a_cellIdx) const override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>GetEdgesOfCell</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>ad572516a6cd31d2d4abcfd1234edc616</anchor>
      <arglist>(const int a_cellIdx, std::vector&lt; std::pair&lt; int, int &gt;&gt; &amp;a_edges) const override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>GetNumberOfCellFaces</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>a43ecb6e3a520df054be4b4f9dfdaeac4</anchor>
      <arglist>(const int a_cellIdx) const override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual VecInt</type>
      <name>GetCellFace</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>a2559e30a768709cf32b41bc8eb315d48</anchor>
      <arglist>(const int a_cellIdx, const int a_faceIdx) const override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>GetCellFace</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>a568b8aeeaff9c6c8ee5fc790fa8ddc22</anchor>
      <arglist>(const int a_cellIdx, const int a_faceIdx, VecInt &amp;a_facePtIdxs) const override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual VecInt2d</type>
      <name>GetFacesOfCell</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>a6a6bbe57df7df77b3be92ceaa4aa998a</anchor>
      <arglist>(const int a_cellIdx) const override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>GetCellFaceNeighbor</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>a3fb19dcb7956ef6be59d8945e9dab2fc</anchor>
      <arglist>(const int a_cellIdx, const int a_faceIdx) const override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>GetCellFaceNeighbor</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>a7131482b77f4f447a3ba30b4533ad385</anchor>
      <arglist>(const int a_cellIdx, const int a_faceIdx, int &amp;a_neighborCell, int &amp;a_neighborFace) const override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>GetFacesFromPoint</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>a9b9df42409864a7a30b099a2b18f8100</anchor>
      <arglist>(const int a_pointId, VecInt &amp;a_cellIdxs, VecInt &amp;a_faceIdxs) const override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~XmUGrid</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>a00ece5dcb23ebc06e2651f4a3f3695c4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>UpdateLinks</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>ad3da23ee4f06663ef4be50bb1ed461af</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>UpdateCellLinks</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>a643e4add9e15493c23dc1276c52dc5d7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>UpdatePointLinks</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>ab4e7a86c2f130d5c32db8c8b8544a57f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type>int</type>
      <name>GetNumberOfItemsForCell</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>a832173fd11b6328d131ba5a81602e5a3</anchor>
      <arglist>(const int a_cellIdx) const </arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>GetSingleCellStream</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>a84261d1726614d6be7045299823ca480</anchor>
      <arglist>(const int a_cellIdx, const int **a_start, int &amp;a_length) const </arglist>
    </member>
    <member kind="function" protection="private">
      <type>int</type>
      <name>GetNumberOfPolyhedronEdges</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>a7af8237646c3a2f03c1e6c96df27d8a7</anchor>
      <arglist>(const int a_cellIdx) const </arglist>
    </member>
    <member kind="function" protection="private">
      <type>bool</type>
      <name>GetPlanViewPolygon2d</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>a53f1f7cc1dd384a6c40b8e01a76f75d1</anchor>
      <arglist>(int a_cellIdx, VecPt3d &amp;a_polygon) const </arglist>
    </member>
    <member kind="function" protection="private">
      <type>bool</type>
      <name>GetPlanViewPolygon3d</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>a27b9e9634e5cacaad9f66f673488b2c0</anchor>
      <arglist>(int a_cellIdx, VecPt3d &amp;a_polygon) const </arglist>
    </member>
    <member kind="function" protection="private">
      <type>bool</type>
      <name>IsFaceSide</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>af58fa7a901ed95cd28b67417bb511ee8</anchor>
      <arglist>(const VecInt &amp;a_facePts) const </arglist>
    </member>
    <member kind="function" protection="private">
      <type>bool</type>
      <name>GetCellXySegments</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>a4a14d466d4e09e40ba5b13a8a77c6b7f</anchor>
      <arglist>(int cellIdx, VecPt3d &amp;segments) const </arglist>
    </member>
    <member kind="function" protection="private">
      <type>bool</type>
      <name>IsCellValidWithPointChange</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>ac199ae8bef7c8fc4b0c840ba6428dbf5</anchor>
      <arglist>(const int a_cellIdx, const int a_changedPtIdx, const Pt3d &amp;a_newPosition) const </arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>GetEdgesOfFace</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>a696c700c32e8447677009c8c69e9ca7a</anchor>
      <arglist>(const VecInt &amp;a_face, std::vector&lt; std::pair&lt; int, int &gt;&gt; &amp;a_edges) const </arglist>
    </member>
    <member kind="function" protection="private">
      <type>bool</type>
      <name>DoEdgesCrossWithPointChange</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>a97f2f8639c9e89744a725b0df378aea1</anchor>
      <arglist>(const int a_changedPtIdx, const Pt3d &amp;a_newPosition, const std::vector&lt; std::pair&lt; int, int &gt;&gt; &amp;a_edges) const </arglist>
    </member>
    <member kind="function" protection="private" static="yes">
      <type>static int</type>
      <name>DimensionFromCellType</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>ab402b9ad4de156cd3fcb726dbb6daba5</anchor>
      <arglist>(const XmUGridCellType a_cellType)</arglist>
    </member>
    <member kind="function" protection="private" static="yes">
      <type>static void</type>
      <name>GetUniquePointsFromPolyhedronCellStream</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>a2183538fb67d17147789963c6a41c741</anchor>
      <arglist>(const VecInt &amp;a_cellStream, const int a_numCellItems, int &amp;a_currIdx, VecInt &amp;a_uniquePoints, VecInt &amp;a_cellMask)</arglist>
    </member>
    <member kind="function" protection="private" static="yes">
      <type>static bool</type>
      <name>GetUniquePointsFromPolyhedronSingleCellStream</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>a5785da3617144417d4b071529cc7486e</anchor>
      <arglist>(const VecInt &amp;a_cellStream, VecInt &amp;a_cellPoints)</arglist>
    </member>
    <member kind="function" protection="private" static="yes">
      <type>static void</type>
      <name>GetUniqueEdgesFromPolyhedronCellStream</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>a0159fb385445f033a12395ae0b11ce2b</anchor>
      <arglist>(const int **a_start, int &amp;a_length, boost::container::flat_set&lt; std::pair&lt; int, int &gt;&gt; &amp;a_cellEdges, int &amp;a_currIdx)</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>VecPt3d</type>
      <name>m_points</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>a98029f169f5a0222608a173c9cfa8427</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>VecInt</type>
      <name>m_cellStream</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>ac86ea32fb8ffca206bec78eec482b614</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>VecInt</type>
      <name>m_cellIdxToStreamIdx</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>a5c7a094095537254a5ea5f773acdc2c1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>VecInt</type>
      <name>m_pointsToCells</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>a6c196a9a4a80b6bbe64d9f26d90d6c95</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>VecInt</type>
      <name>m_pointIdxToPointsToCells</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>abf9068082d14f0782f7332b08b34bb61</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" static="yes">
      <type>static BSHP&lt; XmUGrid &gt;</type>
      <name>New</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>ad95e11b54ca04baa73571cc4f939a27d</anchor>
      <arglist>(const VecPt3d &amp;a_points, const VecInt &amp;a_cellStream)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static BSHP&lt; XmUGrid &gt;</type>
      <name>New</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>a51464b4cc71bddbb97e9e8a6ff7fb798</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static bool</type>
      <name>ValidCellStream</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>addf4c365d29c55d7624100b35c7bf223</anchor>
      <arglist>(const VecInt &amp;a_cellStream)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type></type>
      <name>XmUGrid</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>a2830cab0aca6c776321d58294dbc2208</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>xms::XmUGrid</name>
    <filename>classxms_1_1_xm_u_grid.html</filename>
  </compound>
  <compound kind="dir">
    <name>/home/travis/build/Aquaveo/xmsgrid/xmsgrid/python</name>
    <path>/home/travis/build/Aquaveo/xmsgrid/xmsgrid/python/</path>
    <filename>dir_ed63beb1e79dd2a15db8cfd74099fc48.html</filename>
    <dir>/home/travis/build/Aquaveo/xmsgrid/xmsgrid/python/ugrid</dir>
    <file>__init__.py</file>
    <file>xmsgrid_py.cpp</file>
  </compound>
  <compound kind="dir">
    <name>/home/travis/build/Aquaveo/xmsgrid/xmsgrid/ugrid</name>
    <path>/home/travis/build/Aquaveo/xmsgrid/xmsgrid/ugrid/</path>
    <filename>dir_a4f80c8107f4df91c21d011369fb1e1d.html</filename>
    <file>XmConvexHull.cpp</file>
    <file>XmConvexHull.h</file>
    <file>XmConvexHull.t.h</file>
    <file>XmUGrid.cpp</file>
    <file>XmUGrid.h</file>
    <file>XmUGrid.t.h</file>
    <file>XmUGridUtils.cpp</file>
    <file>XmUGridUtils.h</file>
    <file>XmUGridUtils.t.h</file>
  </compound>
  <compound kind="dir">
    <name>/home/travis/build/Aquaveo/xmsgrid/xmsgrid/python/ugrid</name>
    <path>/home/travis/build/Aquaveo/xmsgrid/xmsgrid/python/ugrid/</path>
    <filename>dir_df63a72722e2a18a23dc615b97003480.html</filename>
    <file>__init__.py</file>
    <file>ugrid_py.cpp</file>
    <file>ugrid_py.h</file>
    <file>XmUGrid_py.cpp</file>
    <file>XmUGrid_pyt.py</file>
    <file>XmUGridUtils_py.cpp</file>
    <file>XmUGridUtils_pyt.py</file>
  </compound>
  <compound kind="dir">
    <name>/home/travis/build/Aquaveo/xmsgrid/xmsgrid</name>
    <path>/home/travis/build/Aquaveo/xmsgrid/xmsgrid/</path>
    <filename>dir_063f5bb27051e7adf91034aa3d93de96.html</filename>
    <dir>/home/travis/build/Aquaveo/xmsgrid/xmsgrid/python</dir>
    <dir>/home/travis/build/Aquaveo/xmsgrid/xmsgrid/ugrid</dir>
  </compound>
  <compound kind="page">
    <name>index</name>
    <title></title>
    <filename>index</filename>
    <docanchor file="index" title="xmsgrid ">xmsgrid</docanchor>
    <docanchor file="index" title="Introduction ">XmsugridIntroduction</docanchor>
    <docanchor file="index" title="License ">XmsgridLicense</docanchor>
    <docanchor file="index" title="Features ">XmsgridFeatures</docanchor>
    <docanchor file="index" title="Testing ">XmsgridTesting</docanchor>
    <docanchor file="index" title="The Code ">XmsgridTheCode</docanchor>
    <docanchor file="index" title="Namespaces">XmsgridNamespaces</docanchor>
    <docanchor file="index" title="Interface pattern">XmsgridInterfacePattern</docanchor>
    <docanchor file="index" title="&quot;xmsgrid&quot; Name ">xmsgridName</docanchor>
  </compound>
</tagfile>
