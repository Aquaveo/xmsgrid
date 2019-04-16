<?xml version='1.0' encoding='UTF-8' standalone='yes' ?>
<tagfile>
  <compound kind="file">
    <name>XmGeometry.cpp</name>
    <path>/home/conan/xmsgrid/ugrid/detail/</path>
    <filename>_xm_geometry_8cpp</filename>
    <includes id="_xm_geometry_8h" name="XmGeometry.h" local="no" imported="no">xmsgrid/ugrid/detail/XmGeometry.h</includes>
    <includes id="_xm_u_grid_8h" name="XmUGrid.h" local="no" imported="no">xmsgrid/ugrid/XmUGrid.h</includes>
    <includes id="_xm_u_grid_utils_8h" name="XmUGridUtils.h" local="no" imported="no">xmsgrid/ugrid/XmUGridUtils.h</includes>
    <includes id="_xm_geometry_8t_8h" name="XmGeometry.t.h" local="no" imported="no">xmsgrid/ugrid/detail/XmGeometry.t.h</includes>
    <namespace>xms</namespace>
    <member kind="function">
      <type>VecPt3d</type>
      <name>ConvexHull</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a8bf3a5f5a2e5003c8de8e44a75fa9cde</anchor>
      <arglist>(const std::vector&lt; Pt3&lt; double &gt;&gt; &amp;a_points)</arglist>
    </member>
    <member kind="function">
      <type>VecInt</type>
      <name>ConvexHullWithIndices</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a8d5547f30586a0da0391aa281a4ef559</anchor>
      <arglist>(const std::vector&lt; int &gt; &amp;a_points, BSHP&lt; XmUGrid &gt; a_ugrid)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>DoLineSegmentsCross</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>aea9cf0b2bb6a3c1fc4d36d6defebecfe</anchor>
      <arglist>(const std::pair&lt; Pt3&lt; double &gt;, Pt3&lt; double &gt;&gt; &amp;a_segment1, const std::pair&lt; Pt3&lt; double &gt;, Pt3&lt; double &gt;&gt; &amp;a_segment2)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>DoLineSegmentsCross</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ac3978b6fc01a80623f117b8642e64f85</anchor>
      <arglist>(const Pt3&lt; double &gt; &amp;a_segment1Point1, const Pt3&lt; double &gt; &amp;a_segment1Point2, const Pt3&lt; double &gt; &amp;a_segment2Point1, const Pt3&lt; double &gt; &amp;a_segment2Point2)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>XmGeometry.h</name>
    <path>/home/conan/xmsgrid/ugrid/detail/</path>
    <filename>_xm_geometry_8h</filename>
    <namespace>xms</namespace>
    <member kind="function">
      <type>VecPt3d</type>
      <name>ConvexHull</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a8bf3a5f5a2e5003c8de8e44a75fa9cde</anchor>
      <arglist>(const std::vector&lt; Pt3&lt; double &gt;&gt; &amp;a_points)</arglist>
    </member>
    <member kind="function">
      <type>VecInt</type>
      <name>ConvexHullWithIndices</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a8d5547f30586a0da0391aa281a4ef559</anchor>
      <arglist>(const std::vector&lt; int &gt; &amp;a_points, BSHP&lt; XmUGrid &gt; a_ugrid)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>DoLineSegmentsCross</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>aea9cf0b2bb6a3c1fc4d36d6defebecfe</anchor>
      <arglist>(const std::pair&lt; Pt3&lt; double &gt;, Pt3&lt; double &gt;&gt; &amp;a_segment1, const std::pair&lt; Pt3&lt; double &gt;, Pt3&lt; double &gt;&gt; &amp;a_segment2)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>DoLineSegmentsCross</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ac3978b6fc01a80623f117b8642e64f85</anchor>
      <arglist>(const Pt3&lt; double &gt; &amp;a_segment1Point1, const Pt3&lt; double &gt; &amp;a_segment1Point2, const Pt3&lt; double &gt; &amp;a_segment2Point1, const Pt3&lt; double &gt; &amp;a_segment2Point2)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>XmGeometry.t.h</name>
    <path>/home/conan/xmsgrid/ugrid/detail/</path>
    <filename>_xm_geometry_8t_8h</filename>
    <class kind="class">XmGeometryUnitTests</class>
    <namespace>xms</namespace>
  </compound>
  <compound kind="file">
    <name>XmEdge.cpp</name>
    <path>/home/conan/xmsgrid/ugrid/</path>
    <filename>_xm_edge_8cpp</filename>
    <includes id="_xm_edge_8t_8h" name="XmEdge.t.h" local="no" imported="no">xmsgrid/ugrid/XmEdge.t.h</includes>
    <namespace>xms</namespace>
    <member kind="function">
      <type>bool</type>
      <name>XmEdgesEquivalent</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a78f807814aab6186ecac3c7f44a9af37</anchor>
      <arglist>(const XmEdge &amp;a_edge1, const XmEdge &amp;a_edge2)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>XmEdge.t.h</name>
    <path>/home/conan/xmsgrid/ugrid/</path>
    <filename>_xm_edge_8t_8h</filename>
    <class kind="class">XmEdgeUnitTests</class>
    <namespace>xms</namespace>
  </compound>
  <compound kind="file">
    <name>XmUGrid.cpp</name>
    <path>/home/conan/xmsgrid/ugrid/</path>
    <filename>_xm_u_grid_8cpp</filename>
    <includes id="_xm_u_grid_8h" name="XmUGrid.h" local="no" imported="no">xmsgrid/ugrid/XmUGrid.h</includes>
    <includes id="_xm_geometry_8h" name="XmGeometry.h" local="no" imported="no">xmsgrid/ugrid/detail/XmGeometry.h</includes>
    <includes id="_xm_u_grid_utils_8h" name="XmUGridUtils.h" local="no" imported="no">xmsgrid/ugrid/XmUGridUtils.h</includes>
    <includes id="_xm_u_grid_8t_8h" name="XmUGrid.t.h" local="no" imported="no">xmsgrid/ugrid/XmUGrid.t.h</includes>
    <class kind="class">xms::XmUGridImpl</class>
    <namespace>xms</namespace>
    <member kind="typedef">
      <type>std::vector&lt; XmEdge &gt;</type>
      <name>VecEdge</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>acd21e8de7357a71eb268548c301c9f43</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>BSHP&lt; XmUGrid &gt;</type>
      <name>TEST_XmUGrid1Left90Tri</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>acf4c5713f23e0600ec26bb0294263068</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>BSHP&lt; XmUGrid &gt;</type>
      <name>TEST_XmUGridSimpleQuad</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a65e5eef7f0e8c64484b1aaa0924364b7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>BSHP&lt; XmUGrid &gt;</type>
      <name>TEST_XmUGrid2dLinear</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a8260f0723d0bdca40b077369e5321ac8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>BSHP&lt; XmUGrid &gt;</type>
      <name>TEST_XmUGrid3dLinear</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>af931fa91f04abddf2d9469ef64ecfa70</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>BSHP&lt; XmUGrid &gt;</type>
      <name>TEST_XmUGridHexagonalPolyhedron</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a15d3f924e7e8424b2c491ef2132b700c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>BSHP&lt; xms::XmUGrid &gt;</type>
      <name>TEST_XmUBuildQuadUGrid</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a66cfca71e0f54169d0175e75a1da1b9f</anchor>
      <arglist>(const int a_rows, const int a_cols)</arglist>
    </member>
    <member kind="function">
      <type>BSHP&lt; xms::XmUGrid &gt;</type>
      <name>TEST_XmUBuildQuadUGrid</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ae795f753066bfd3749f441b965aba896</anchor>
      <arglist>(const int a_rows, const int a_cols, const xms::Pt3d &amp;a_origin)</arglist>
    </member>
    <member kind="function">
      <type>BSHP&lt; xms::XmUGrid &gt;</type>
      <name>TEST_XmUBuildHexahedronUgrid</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a0a50a2c6d678fa5e90212d03fecd3f44</anchor>
      <arglist>(const int a_rows, const int a_cols, const int a_lays)</arglist>
    </member>
    <member kind="function">
      <type>BSHP&lt; xms::XmUGrid &gt;</type>
      <name>TEST_XmUBuildHexahedronUgrid</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a9b7018697957bbe8aed198fe6cf69a07</anchor>
      <arglist>(const int a_rows, const int a_cols, const int a_lays, const xms::Pt3d &amp;a_origin)</arglist>
    </member>
    <member kind="function">
      <type>BSHP&lt; xms::XmUGrid &gt;</type>
      <name>TEST_XmUBuildPolyhedronUgrid</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a512cd32ebbe039154d962c0d47a6e4fc</anchor>
      <arglist>(const int a_rows, const int a_cols, const int a_lays)</arglist>
    </member>
    <member kind="function">
      <type>BSHP&lt; xms::XmUGrid &gt;</type>
      <name>TEST_XmUBuildPolyhedronUgrid</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a6b241889d06a379363e269e80a06ea1c</anchor>
      <arglist>(const int a_rows, const int a_cols, const int a_lays, const xms::Pt3d &amp;a_origin)</arglist>
    </member>
    <member kind="function">
      <type>BSHP&lt; xms::XmUGrid &gt;</type>
      <name>TEST_XmUBuild3DChevronUgrid</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a18cc668860be57dfc3d4800446ab6dfb</anchor>
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
    <path>/home/conan/xmsgrid/ugrid/</path>
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
    <member kind="function">
      <type>BSHP&lt; XmUGrid &gt;</type>
      <name>TEST_XmUGrid1Left90Tri</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>acf4c5713f23e0600ec26bb0294263068</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>BSHP&lt; XmUGrid &gt;</type>
      <name>TEST_XmUGridSimpleQuad</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a65e5eef7f0e8c64484b1aaa0924364b7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>BSHP&lt; XmUGrid &gt;</type>
      <name>TEST_XmUGrid2dLinear</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a8260f0723d0bdca40b077369e5321ac8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>BSHP&lt; XmUGrid &gt;</type>
      <name>TEST_XmUGrid3dLinear</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>af931fa91f04abddf2d9469ef64ecfa70</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>BSHP&lt; XmUGrid &gt;</type>
      <name>TEST_XmUGridHexagonalPolyhedron</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a15d3f924e7e8424b2c491ef2132b700c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>BSHP&lt; xms::XmUGrid &gt;</type>
      <name>TEST_XmUBuildQuadUGrid</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a66cfca71e0f54169d0175e75a1da1b9f</anchor>
      <arglist>(const int a_rows, const int a_cols)</arglist>
    </member>
    <member kind="function">
      <type>BSHP&lt; xms::XmUGrid &gt;</type>
      <name>TEST_XmUBuildQuadUGrid</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ae795f753066bfd3749f441b965aba896</anchor>
      <arglist>(const int a_rows, const int a_cols, const xms::Pt3d &amp;a_origin)</arglist>
    </member>
    <member kind="function">
      <type>BSHP&lt; xms::XmUGrid &gt;</type>
      <name>TEST_XmUBuildHexahedronUgrid</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a0a50a2c6d678fa5e90212d03fecd3f44</anchor>
      <arglist>(const int a_rows, const int a_cols, const int a_lays)</arglist>
    </member>
    <member kind="function">
      <type>BSHP&lt; xms::XmUGrid &gt;</type>
      <name>TEST_XmUBuildHexahedronUgrid</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a9b7018697957bbe8aed198fe6cf69a07</anchor>
      <arglist>(const int a_rows, const int a_cols, const int a_lays, const xms::Pt3d &amp;a_origin)</arglist>
    </member>
    <member kind="function">
      <type>BSHP&lt; xms::XmUGrid &gt;</type>
      <name>TEST_XmUBuildPolyhedronUgrid</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a512cd32ebbe039154d962c0d47a6e4fc</anchor>
      <arglist>(const int a_rows, const int a_cols, const int a_lays)</arglist>
    </member>
    <member kind="function">
      <type>BSHP&lt; xms::XmUGrid &gt;</type>
      <name>TEST_XmUBuildPolyhedronUgrid</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a6b241889d06a379363e269e80a06ea1c</anchor>
      <arglist>(const int a_rows, const int a_cols, const int a_lays, const xms::Pt3d &amp;a_origin)</arglist>
    </member>
    <member kind="function">
      <type>BSHP&lt; xms::XmUGrid &gt;</type>
      <name>TEST_XmUBuild3DChevronUgrid</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a18cc668860be57dfc3d4800446ab6dfb</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>XmUGrid.t.h</name>
    <path>/home/conan/xmsgrid/ugrid/</path>
    <filename>_xm_u_grid_8t_8h</filename>
    <class kind="class">XmUGridUnitTests</class>
    <namespace>xms</namespace>
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
    <path>/home/conan/xmsgrid/ugrid/</path>
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
      <type>BSHP&lt; XmUGrid &gt;</type>
      <name>XmReadUGridFromStream</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a9d5b4a9ea7c259666b64babd5e190cf8</anchor>
      <arglist>(std::istream &amp;a_inStream)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>XmWriteUGridToAsciiFile</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>aad684d8d566604305a00cc4d875dd51e</anchor>
      <arglist>(BSHP&lt; XmUGrid &gt; a_ugrid, const std::string &amp;a_filePath)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>XmWriteUGridToStream</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>adcf5db1fd47ba0560a24e9ae63b942df</anchor>
      <arglist>(BSHP&lt; XmUGrid &gt; a_ugrid, std::ostream &amp;a_outStream)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>XmUGridUtils.h</name>
    <path>/home/conan/xmsgrid/ugrid/</path>
    <filename>_xm_u_grid_utils_8h</filename>
    <namespace>xms</namespace>
    <member kind="function">
      <type>BSHP&lt; XmUGrid &gt;</type>
      <name>XmReadUGridFromAsciiFile</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a92b5c5c0a9e2455db6d671eb7134a76e</anchor>
      <arglist>(const std::string &amp;a_filePath)</arglist>
    </member>
    <member kind="function">
      <type>BSHP&lt; XmUGrid &gt;</type>
      <name>XmReadUGridFromStream</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a9d5b4a9ea7c259666b64babd5e190cf8</anchor>
      <arglist>(std::istream &amp;a_inStream)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>XmWriteUGridToAsciiFile</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>aad684d8d566604305a00cc4d875dd51e</anchor>
      <arglist>(BSHP&lt; XmUGrid &gt; a_ugrid, const std::string &amp;a_filePath)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>XmWriteUGridToStream</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>adcf5db1fd47ba0560a24e9ae63b942df</anchor>
      <arglist>(BSHP&lt; XmUGrid &gt; a_ugrid, std::ostream &amp;a_outStream)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>XmUGridUtils.t.h</name>
    <path>/home/conan/xmsgrid/ugrid/</path>
    <filename>_xm_u_grid_utils_8t_8h</filename>
    <class kind="class">XmUGridUtilsTests</class>
  </compound>
  <compound kind="class">
    <name>xms::XmEdge</name>
    <filename>classxms_1_1_xm_edge.html</filename>
    <member kind="function">
      <type></type>
      <name>XmEdge</name>
      <anchorfile>classxms_1_1_xm_edge.html</anchorfile>
      <anchor>ac469ef46c007327f5e7ba35a386e238b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>XmEdge</name>
      <anchorfile>classxms_1_1_xm_edge.html</anchorfile>
      <anchor>a448df3ee696594baa8f89e8019d0c8d9</anchor>
      <arglist>(int a_pt1, int a_pt2, bool a_sorted=false)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>XmEdge</name>
      <anchorfile>classxms_1_1_xm_edge.html</anchorfile>
      <anchor>a4a07febba9a95f90eeb614cdfbac5b77</anchor>
      <arglist>(const std::pair&lt; int, int &gt; &amp;a_edge)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator&lt;</name>
      <anchorfile>classxms_1_1_xm_edge.html</anchorfile>
      <anchor>a21d0f5c55feafd3819c2ad516cda2ab5</anchor>
      <arglist>(const XmEdge &amp;a_rhs) const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator==</name>
      <anchorfile>classxms_1_1_xm_edge.html</anchorfile>
      <anchor>a92e1457e12fa3d2a77ec7eb7ef0547f1</anchor>
      <arglist>(const XmEdge &amp;a_rhs) const</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetFirst</name>
      <anchorfile>classxms_1_1_xm_edge.html</anchorfile>
      <anchor>ac479839b7406aac11f3a3d624b793123</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetFirst</name>
      <anchorfile>classxms_1_1_xm_edge.html</anchorfile>
      <anchor>ae2f5a7f6121e0c00cffea8d1bf0a60b4</anchor>
      <arglist>(int a_pt1)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetSecond</name>
      <anchorfile>classxms_1_1_xm_edge.html</anchorfile>
      <anchor>a97d5c78c70d94f1a7acdff01df8aeb0d</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetSecond</name>
      <anchorfile>classxms_1_1_xm_edge.html</anchorfile>
      <anchor>a716212978dff3a81a74e03c46229e269</anchor>
      <arglist>(int a_pt2)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>IsEquivalent</name>
      <anchorfile>classxms_1_1_xm_edge.html</anchorfile>
      <anchor>a52861e0857ac6dc0f19a5ed224eb2ebb</anchor>
      <arglist>(const XmEdge &amp;a_edge) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SortIndexes</name>
      <anchorfile>classxms_1_1_xm_edge.html</anchorfile>
      <anchor>a4d8007a8537dbebf557b5f90b9c928ec</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>int</type>
      <name>m_pt1</name>
      <anchorfile>classxms_1_1_xm_edge.html</anchorfile>
      <anchor>a339473fd1bb3227edc863900adc59b14</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>int</type>
      <name>m_pt2</name>
      <anchorfile>classxms_1_1_xm_edge.html</anchorfile>
      <anchor>a6614bd4c9e7f9547a9cf916d979a9686</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>XmEdgeUnitTests</name>
    <filename>class_xm_edge_unit_tests.html</filename>
    <member kind="function">
      <type>void</type>
      <name>testLessThanOperator</name>
      <anchorfile>class_xm_edge_unit_tests.html</anchorfile>
      <anchor>ac7df1f4c361d336adb719160851f2004</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testEqualsOperator</name>
      <anchorfile>class_xm_edge_unit_tests.html</anchorfile>
      <anchor>aa339f25fa5dfbeb817a4c6d6023f5be7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testIsEquivalent</name>
      <anchorfile>class_xm_edge_unit_tests.html</anchorfile>
      <anchor>a692a8037d9755b7e5a6966f97c0cfd33</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>XmGeometryUnitTests</name>
    <filename>class_xm_geometry_unit_tests.html</filename>
    <member kind="function">
      <type>void</type>
      <name>testConvexHull</name>
      <anchorfile>class_xm_geometry_unit_tests.html</anchorfile>
      <anchor>a0a46d1422bef14f571b2265655a25b48</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testDoLineSegmentsCross</name>
      <anchorfile>class_xm_geometry_unit_tests.html</anchorfile>
      <anchor>a2b0c287752ece2befba276583c7869c3</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>xms::XmUGrid</name>
    <filename>classxms_1_1_xm_u_grid.html</filename>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~XmUGrid</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>a00ece5dcb23ebc06e2651f4a3f3695c4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>GetModified</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>a07e34c7999367a543dd4cefcfa9507a8</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>SetUnmodified</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>acbc96a0841007f895e8169cd1c310e35</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>SetUseCache</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>abe7ce5b7fefbfd545fb3da579528b21c</anchor>
      <arglist>(bool a_useCache)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>GetPointCount</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>a9475f0253ff1ea4fbf9c8e96b0ada784</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual const VecPt3d &amp;</type>
      <name>GetLocations</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>acca1315fd4948f73d62c3a2f23d36fd0</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>SetLocations</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>a097f42fb1696612e316a576d5dd79083</anchor>
      <arglist>(const VecPt3d &amp;a_locations)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual Pt3d</type>
      <name>GetPointLocation</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>abcf4127cfd961e75bdfe445a6816fcc9</anchor>
      <arglist>(const int a_pointIdx) const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>SetPointLocation</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>ad738abdda85a724b7677fac67f663539</anchor>
      <arglist>(const int a_pointIdx, const Pt3d &amp;a_location)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual Pt3d</type>
      <name>GetPointXy0</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>ae91a9014ce352ffcd04e9f5cefc32abf</anchor>
      <arglist>(const int a_pointIdx) const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual VecPt3d</type>
      <name>GetPointsLocations</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>a8d7b8b87d255095224d0004946ac8192</anchor>
      <arglist>(const VecInt &amp;a_points) const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>GetExtents</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>a49d600d7857cfcaaa7fe04440136866d</anchor>
      <arglist>(Pt3d &amp;a_min, Pt3d &amp;a_max) const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual VecInt</type>
      <name>GetPointAdjacentCells</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>a0f4708efacb13ae29dd4e57f98aec9d9</anchor>
      <arglist>(const int a_pointIdx) const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>GetPointAdjacentCells</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>ab27c613c1e9916b0727c2ce461fde681</anchor>
      <arglist>(const int a_pointIdx, VecInt &amp;a_adjacentCells) const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual VecInt</type>
      <name>GetPointsAdjacentCells</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>a1dcd067fcfb353dae765a731d2df7282</anchor>
      <arglist>(const VecInt &amp;a_points) const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>GetPointsAdjacentCells</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>aef04f51dc3e35f16425bceff7f8fefe0</anchor>
      <arglist>(const VecInt &amp;a_pointIdxs, VecInt &amp;a_adjacentCellIdxs) const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>GetPointsAdjacentCells</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>ae5038fe12f39352f0701d30b743a5b3d</anchor>
      <arglist>(const int a_pointIdx1, const int a_pointIdx2, VecInt &amp;a_adjacentCellIdxs) const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>IsValidPointChange</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>ad6f3d7d765531ee84a37e14358c2bf57</anchor>
      <arglist>(const int a_changedPtIdx, const Pt3d &amp;a_newPosition) const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>GetCellCount</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>a52cf65faae233be569bb14bd73e09449</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>GetCellPointCount</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>a114e30713605c5fe8affd578232aacda</anchor>
      <arglist>(const int a_cellIdx) const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual VecInt</type>
      <name>GetCellPoints</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>a768d1f03936ec142895b4c89ba305a0a</anchor>
      <arglist>(const int a_cellIdx) const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>GetCellPoints</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>ac69f3687dec8cc12956ace0049e8dac9</anchor>
      <arglist>(const int a_cellIdx, VecInt &amp;a_cellPoints) const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>GetCellLocations</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>a0a7b5afd0becce46368ff3736c38311e</anchor>
      <arglist>(const int a_cellIdx, VecPt3d &amp;a_cellLocations) const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual XmUGridCellType</type>
      <name>GetCellType</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>a1cdc6b0ed97cfbef84d2529b14c79f0d</anchor>
      <arglist>(const int a_cellIdx) const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual std::vector&lt; int &gt;</type>
      <name>GetDimensionCounts</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>a7eb4afae2e77ddf6a7fedfcee18a72e7</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>GetCellDimension</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>a046db5d518cc1f2e250f402bcc0cc21a</anchor>
      <arglist>(const int a_cellIdx) const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>GetCellExtents</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>a9cc849c9e815e1650aa2584c65528b5f</anchor>
      <arglist>(const int a_cellIdx, Pt3d &amp;a_min, Pt3d &amp;a_max) const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual const VecInt &amp;</type>
      <name>GetCellstream</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>a06104da983f629140cdba388cc69b34f</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>SetCellstream</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>af4757d88c6874cf636b968827e62c184</anchor>
      <arglist>(const VecInt &amp;a_cellstream)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>GetCellCellstream</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>a780c96b0be08754ac120574192c17d91</anchor>
      <arglist>(const int a_cellIdx, VecInt &amp;a_cellstream) const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual VecInt</type>
      <name>GetCellAdjacentCells</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>ae4761217c3999fb3153527ec56d3a1ee</anchor>
      <arglist>(const int a_cellIdx) const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>GetCellAdjacentCells</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>a98dd14c7ab9e527eacbc229d6e2e2a02</anchor>
      <arglist>(const int a_cellIdx, VecInt &amp;a_cellNeighbors) const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>GetCellPlanViewPolygon</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>a493091705fb4d7b05f294950afb52018</anchor>
      <arglist>(int a_cellIdx, VecPt3d &amp;a_polygon) const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>GetCellCentroid</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>aef337606cfbd43cc04e64333cf95a02b</anchor>
      <arglist>(int a_cellIdx, Pt3d &amp;a_centroid) const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>GetCellEdgeCount</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>aa0227de33b3905bfb2f34cf12176e45b</anchor>
      <arglist>(const int a_cellIdx) const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual XmEdge</type>
      <name>GetCellEdge</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>a0cfeae5f8e045aa26de22f0f12968770</anchor>
      <arglist>(const int a_cellIdx, const int a_edgeIdx) const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual VecInt</type>
      <name>GetCellEdgeAdjacentCells</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>ab6022c9cadb27816b426bdc62f5635f5</anchor>
      <arglist>(const int a_cellIdx, const int a_edgeIdx) const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>GetCellEdgeAdjacentCells</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>a6f2de396eb174cf1acd5e6a640cdc96a</anchor>
      <arglist>(const int a_cellIdx, const int a_edgeIdx, VecInt &amp;a_adjacentCellIdxs) const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>GetCell2dEdgeAdjacentCell</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>aafb5073097a30d0c5a64153eae76ac3e</anchor>
      <arglist>(const int a_cellIdx, const int a_edgeIdx) const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>GetEdgeAdjacentCells</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>a5eac64030b549a8805147908ae5b738e</anchor>
      <arglist>(const XmEdge &amp;a_edge, VecInt &amp;a_adjacentCellIdxs) const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual VecInt</type>
      <name>GetEdgeAdjacentCells</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>a39d44fc045be2bc895dc94f354d23502</anchor>
      <arglist>(const XmEdge &amp;a_edge) const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual std::vector&lt; XmEdge &gt;</type>
      <name>GetCellEdges</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>afae1758d8433f3a9112aa0a5661505b8</anchor>
      <arglist>(const int a_cellIdx) const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>GetCellEdges</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>abd543b795f3968837dcd591b7b3dcf7c</anchor>
      <arglist>(const int a_cellIdx, std::vector&lt; XmEdge &gt; &amp;a_edges) const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>GetPointAdjacentPoints</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>aafd7cd6f70a335e67f4251543af72990</anchor>
      <arglist>(int a_pointIdx, VecInt &amp;a_edgePoints) const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>GetPointAdjacentLocations</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>a9ee7727ba92139fd26cebc41f0982419</anchor>
      <arglist>(int a_pointIdx, VecPt3d &amp;a_edgePoints) const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>GetCell3dFaceCount</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>acad05ff1b6cc4352dc7ba150a315dde0</anchor>
      <arglist>(const int a_cellIdx) const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>GetCell3dFacePointCount</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>a8a8b79f7bd67deba4a12a36b39ec8858</anchor>
      <arglist>(const int a_cellIdx, const int a_faceIdx) const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual VecInt</type>
      <name>GetCell3dFacePoints</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>aba063b951d106385dc680be3f7942731</anchor>
      <arglist>(const int a_cellIdx, const int a_faceIdx) const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>GetCell3dFacePoints</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>aa56e589cf053ede93c849b977c408cd2</anchor>
      <arglist>(const int a_cellIdx, const int a_faceIdx, VecInt &amp;a_facePtIdxs) const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual VecInt2d</type>
      <name>GetCell3dFacesPoints</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>a517137f93176ed8883356771f3f1bc9b</anchor>
      <arglist>(const int a_cellIdx) const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>GetCell3dFaceAdjacentCell</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>a15628550e1b02ae974f0d4948f4e9912</anchor>
      <arglist>(const int a_cellIdx, const int a_faceIdx) const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>GetCell3dFaceAdjacentCell</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>a1a8edc40d0386aac81162b18d57368b0</anchor>
      <arglist>(const int a_cellIdx, const int a_faceIdx, int &amp;a_neighborCell, int &amp;a_neighborFace) const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual XmUGridFaceOrientation</type>
      <name>GetCell3dFaceOrientation</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>afc440eea2b974d32c4aa8e33007c5f0c</anchor>
      <arglist>(int a_cellIdx, int a_faceIdx) const =0</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static BSHP&lt; XmUGrid &gt;</type>
      <name>New</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>a45106b162bbdb8cfacb6a17e57d6b271</anchor>
      <arglist>(const VecPt3d &amp;a_points, const VecInt &amp;a_cellstream)</arglist>
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
      <name>IsValidCellstream</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>a75064634282c829c88596c6da646f4f3</anchor>
      <arglist>(const VecInt &amp;a_cellstream)</arglist>
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
    <name>xms::XmUGridImpl</name>
    <filename>classxms_1_1_xm_u_grid_impl.html</filename>
    <base>xms::XmUGrid</base>
    <member kind="function">
      <type></type>
      <name>XmUGridImpl</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>a0ec8140212d29927620c6010fd5fa8f1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>GetModified</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>a0d7a79c355cabf0173d28a3f60899928</anchor>
      <arglist>() const override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>SetUnmodified</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>aef492cc16d1627d6738d739eb0715aee</anchor>
      <arglist>() override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>SetUseCache</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>a34f681f73b06c6182b804de4f7e828a5</anchor>
      <arglist>(bool a_useCache) override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>GetPointCount</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>acf4be3401b60ad6a46f66a80022098e7</anchor>
      <arglist>() const override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const VecPt3d &amp;</type>
      <name>GetLocations</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>a21ed238c5e4c9118e3c5ad0a5099e250</anchor>
      <arglist>() const override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>SetLocations</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>a7c8c4f205d39d31f42859c35f28800d3</anchor>
      <arglist>(const VecPt3d &amp;a_locations) override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual Pt3d</type>
      <name>GetPointLocation</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>af34e4c2d2b7eb8a414c89f78fbaecc37</anchor>
      <arglist>(const int a_pointIdx) const override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>SetPointLocation</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>a828a910ecb2a5b934ea9b869b5330220</anchor>
      <arglist>(const int a_pointIdx, const Pt3d &amp;a_point) override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual Pt3d</type>
      <name>GetPointXy0</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>a86b5100050202c6e7e1ae940212da0a5</anchor>
      <arglist>(const int a_pointIdx) const override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual VecPt3d</type>
      <name>GetPointsLocations</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>a1fb343e6970ad37b346fd8161c887a17</anchor>
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
      <name>GetPointAdjacentCells</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>aa68ec80d9faae0e377c95257c01e1dac</anchor>
      <arglist>(const int a_pointIdx) const override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>GetPointAdjacentCells</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>a4cc86f3c153e86e4fdfe8c7b19046a04</anchor>
      <arglist>(const int a_pointIdx, VecInt &amp;a_adjacentCells) const override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual VecInt</type>
      <name>GetPointsAdjacentCells</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>a8c026bafde697ca475712d6c09982954</anchor>
      <arglist>(const VecInt &amp;a_points) const override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>GetPointsAdjacentCells</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>ae6289e2fd4c023d4d7b8503fa83df117</anchor>
      <arglist>(const int *a_pointIdxs, int a_numpointIdxs, VecInt &amp;a_commonCellIdxs) const</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>GetPointsAdjacentCells</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>a5d04574d7e5dbf707abf9fb8bf703a37</anchor>
      <arglist>(const VecInt &amp;a_points, VecInt &amp;a_commonCellIdxs) const override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>GetPointsAdjacentCells</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>a10eeac62d5cec0c88d6000c2beb02d07</anchor>
      <arglist>(const int a_pointIdx1, const int a_pointIdx2, VecInt &amp;a_commonCellIdxs) const override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>IsValidPointChange</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>ab1ad52b8dce2a65557b73ebe57daad08</anchor>
      <arglist>(const int a_changedPtIdx, const Pt3d &amp;a_newPosition) const override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>GetCellCount</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>ab7675dc5297790cb3a467fedcb70bf07</anchor>
      <arglist>() const override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>GetCellPointCount</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>a27b8d19e26fa258bce61dfe220715590</anchor>
      <arglist>(const int a_cellIdx) const override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual VecInt</type>
      <name>GetCellPoints</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>a61251e6f9231a3079467aa0155ce28c9</anchor>
      <arglist>(const int a_cellIdx) const override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>GetCellPoints</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>a938ceec91449a093548dcaaa384a0f37</anchor>
      <arglist>(const int a_cellIdx, VecInt &amp;a_cellPoints) const override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>GetCellLocations</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>ae6157c33f9f5475fc077a42a135f19fb</anchor>
      <arglist>(const int a_cellIdx, VecPt3d &amp;a_cellLocations) const override</arglist>
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
      <name>GetDimensionCounts</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>a2c20ecde4a30a8cc9ceb9481c6354f29</anchor>
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
      <type>virtual void</type>
      <name>GetCellExtents</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>a6aecf50ac2c0a8c1e7688faa5950cd2e</anchor>
      <arglist>(const int a_cellIdx, Pt3d &amp;a_min, Pt3d &amp;a_max) const override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const VecInt &amp;</type>
      <name>GetCellstream</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>a6b8383b51fe5dedc41211ba9f81d234b</anchor>
      <arglist>() const override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>SetCellstream</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>a31f9108df0577b749c739b0c507d23e5</anchor>
      <arglist>(const VecInt &amp;a_cellstream) override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>GetCellCellstream</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>a597d3c60eec441b2176141211ec258d1</anchor>
      <arglist>(const int a_cellIdx, VecInt &amp;a_cellstream) const override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual VecInt</type>
      <name>GetCellAdjacentCells</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>a4acb3c229c93c1364265b9e757f7c611</anchor>
      <arglist>(const int a_cellIdx) const override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>GetCellAdjacentCells</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>af29e62d8167b41176724eb058de46987</anchor>
      <arglist>(const int a_cellIdx, VecInt &amp;a_cellNeighbors) const override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>GetCellPlanViewPolygon</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>ac688327b72a4bd20526dc62302785eaf</anchor>
      <arglist>(int a_cellIdx, VecPt3d &amp;a_polygon) const override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>GetCellCentroid</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>af5bad30c44856f0eda9e6158700c3b9f</anchor>
      <arglist>(int a_cellIdx, Pt3d &amp;a_centroid) const override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>GetCellEdgeCount</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>a76313735b4b511047eadf7c4c41df8d1</anchor>
      <arglist>(const int a_cellIdx) const override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual XmEdge</type>
      <name>GetCellEdge</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>a6c543f756089e1a14bf3298e9b6046ba</anchor>
      <arglist>(const int a_cellIdx, const int a_edgeIdx) const override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual VecInt</type>
      <name>GetCellEdgeAdjacentCells</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>a054fae8cf18dd3a3345f2871c3413b5a</anchor>
      <arglist>(const int a_cellIdx, const int a_edgeIdx) const override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>GetCellEdgeAdjacentCells</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>aba4f1740a78221cc88d14ed119ff128b</anchor>
      <arglist>(const int a_cellIdx, const int a_edgeIdx, VecInt &amp;a_adjacentCellIdxs) const override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>GetCell2dEdgeAdjacentCell</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>acd3be022b5d2952635bbf2a46d872c3b</anchor>
      <arglist>(const int a_cellIdx, const int a_edgeIdx) const override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>GetEdgeAdjacentCells</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>a3ab06fe0d32a5e77d95c2e9820d9e267</anchor>
      <arglist>(const XmEdge &amp;a_edge, VecInt &amp;a_adjacentCellIdxs) const override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual VecInt</type>
      <name>GetEdgeAdjacentCells</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>a105a352f0b1364105b8be45e1463dbdc</anchor>
      <arglist>(const XmEdge &amp;a_edge) const override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual std::vector&lt; XmEdge &gt;</type>
      <name>GetCellEdges</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>a7751b8e82fd63b1390c7231cef3c77ca</anchor>
      <arglist>(const int a_cellIdx) const override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>GetCellEdges</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>af9cde4a78ab9b3b94e7af14f6c7b20cd</anchor>
      <arglist>(const int a_cellIdx, std::vector&lt; XmEdge &gt; &amp;a_edges) const override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>GetPointAdjacentPoints</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>a4e406ce976e7f8b33ea4c0e15aef0dea</anchor>
      <arglist>(int a_pointIdx, VecInt &amp;a_edgePoints) const override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>GetPointAdjacentLocations</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>a0f2bcba9f04aa6b6e4140e678273c1d0</anchor>
      <arglist>(int a_pointIdx, VecPt3d &amp;a_edgePoints) const override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>GetCell3dFaceCount</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>ad504659993e196d1edbde16421e56d9a</anchor>
      <arglist>(const int a_cellIdx) const override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>GetCell3dFacePointCount</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>a7669685008f40cea3d79aa93ea9e1b85</anchor>
      <arglist>(const int a_cellIdx, const int a_faceIdx) const override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual VecInt</type>
      <name>GetCell3dFacePoints</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>a69f889294477362c7c1a1c9362ec62b1</anchor>
      <arglist>(const int a_cellIdx, const int a_faceIdx) const override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>GetCell3dFacePoints</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>ad4945cd666a17e2b1d7fceb0730b9c8c</anchor>
      <arglist>(const int a_cellIdx, const int a_faceIdx, VecInt &amp;a_facePtIdxs) const override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual VecInt2d</type>
      <name>GetCell3dFacesPoints</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>a8cc422be8230daead9995d6c52b567bd</anchor>
      <arglist>(const int a_cellIdx) const override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>GetCell3dFaceAdjacentCell</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>a2d867bf0312d37fb6e53deb8f285a99f</anchor>
      <arglist>(const int a_cellIdx, const int a_faceIdx) const override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>GetCell3dFaceAdjacentCell</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>a71f6e717cb390605927b80f31f615d5a</anchor>
      <arglist>(const int a_cellIdx, const int a_faceIdx, int &amp;a_neighborCell, int &amp;a_neighborFace) const override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual XmUGridFaceOrientation</type>
      <name>GetCell3dFaceOrientation</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>ad6da550e854dfbb7b565a1ca7dddd978</anchor>
      <arglist>(int a_cellIdx, int a_faceIdx) const override</arglist>
    </member>
    <member kind="enumeration" protection="private">
      <type></type>
      <name>XmUGridCacheHolder</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>a063c57c4185e1646128d2ff0b9aea66c</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue" protection="private">
      <name>NEEDS_CALCULATION</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>a063c57c4185e1646128d2ff0b9aea66ca608b3d3fe801a049e476384b632bc6a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue" protection="private">
      <name>NEEDS_CALCULATION</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>a063c57c4185e1646128d2ff0b9aea66ca608b3d3fe801a049e476384b632bc6a0</anchor>
      <arglist></arglist>
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
      <type>void</type>
      <name>SetModified</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>a20068651e307621d342160ec296c7749</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type>bool</type>
      <name>IsCellValidWithPointChange</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>a456aa05765a4760f5bf049bb74cb585a</anchor>
      <arglist>(const int a_cellIdx, const int a_changedPtIdx, const Pt3d &amp;a_newPosition) const</arglist>
    </member>
    <member kind="function" protection="private">
      <type>bool</type>
      <name>IsValidCellIdx</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>a8d88be6f40691b7c91a58ec64c6ffe80</anchor>
      <arglist>(const int a_cellIdx) const</arglist>
    </member>
    <member kind="function" protection="private">
      <type>int</type>
      <name>GetNumberOfItemsForCell</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>aa14488b1965a7562e67c6a99e7c91792</anchor>
      <arglist>(const int a_cellIdx) const</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>GetCellCellstream</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>a34383b5ef80603a87d105cbfe976e927</anchor>
      <arglist>(const int a_cellIdx, const int **a_start, int &amp;a_length) const</arglist>
    </member>
    <member kind="function" protection="private">
      <type>int</type>
      <name>GetNumberOfPolyhedronEdges</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>a9d4d8f4d15160284c6855fe4aa1c687b</anchor>
      <arglist>(const int a_cellIdx) const</arglist>
    </member>
    <member kind="function" protection="private">
      <type>bool</type>
      <name>GetPlanViewPolygon2d</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>aa77ad55636528bf5d28b7fc4b2808699</anchor>
      <arglist>(int a_cellIdx, VecPt3d &amp;a_polygon) const</arglist>
    </member>
    <member kind="function" protection="private">
      <type>bool</type>
      <name>GetPlanViewPolygon3d</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>a2fc2c482c80bc2099c0cf5d07af16e05</anchor>
      <arglist>(int a_cellIdx, VecPt3d &amp;a_polygon) const</arglist>
    </member>
    <member kind="function" protection="private">
      <type>bool</type>
      <name>IsFaceSide</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>aa5ebf9ac8a6f4081f373847bc6994a98</anchor>
      <arglist>(const VecInt &amp;a_facePts) const</arglist>
    </member>
    <member kind="function" protection="private">
      <type>bool</type>
      <name>GetCellXySegments</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>a511559caac8d5a84e69a1f8865ea2895</anchor>
      <arglist>(int cellIdx, VecPt3d &amp;a_segments) const</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>GetEdgesOfFace</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>a8ce0398bbbf8662634798ebce20867c9</anchor>
      <arglist>(const VecInt &amp;a_face, std::vector&lt; XmEdge &gt; &amp;a_edges) const</arglist>
    </member>
    <member kind="function" protection="private">
      <type>bool</type>
      <name>DoEdgesCrossWithPointChange</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>a7c8c0c2ec2226d4a7460d65ab7994330</anchor>
      <arglist>(const int a_changedPtIdx, const Pt3d &amp;a_newPosition, const std::vector&lt; XmEdge &gt; &amp;a_edges) const</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>GetExtentsFromPoints</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>a3b19c32fb82cdb9cbc761211a70e81cc</anchor>
      <arglist>(const VecPt3d &amp;a_points, Pt3d &amp;a_min, Pt3d &amp;a_max) const</arglist>
    </member>
    <member kind="function" protection="private">
      <type>bool</type>
      <name>GetFaceXySegments</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>a347945682633bfac0879e20ff18d0cc5</anchor>
      <arglist>(int a_cellIdx, int a_faceIdx, VecPt3d &amp;a_segments) const</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>CalculateCacheValues</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>af33a11a9617da87d751bdb50c98e3db0</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>ClearCacheValues</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>a6474fa0178a7f2c86f75118791a7dd0b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type>int</type>
      <name>GetCell3dFaceCountNoCache</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>a659b5e4dd8659b458e1b21dfc1a87a1a</anchor>
      <arglist>(const int a_cellIdx) const</arglist>
    </member>
    <member kind="function" protection="private">
      <type>int</type>
      <name>GetCell3dFaceAdjacentCellNoCache</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>a2a717f1a9f42230612d42f2a03c4dbaa</anchor>
      <arglist>(const int a_cellIdx, const int a_faceIdx) const</arglist>
    </member>
    <member kind="function" protection="private">
      <type>XmUGridFaceOrientation</type>
      <name>GetCell3dFaceOrientationNoCache</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>afb5d36285f4da085c49d6d62658525b0</anchor>
      <arglist>(int a_cellIdx, int a_faceIdx) const</arglist>
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
      <name>GetUniquePointsFromPolyhedronCellstream</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>a172161043e4b904ea193065fd9d7ec96</anchor>
      <arglist>(const VecInt &amp;a_cellstream, const int a_numCellItems, int &amp;a_currIdx, VecInt &amp;a_uniquePoints, VecInt &amp;a_cellMask)</arglist>
    </member>
    <member kind="function" protection="private" static="yes">
      <type>static bool</type>
      <name>GetUniquePointsFromPolyhedronSingleCellstream</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>a064c4371806371a73bcfe95b01d1c547</anchor>
      <arglist>(const VecInt &amp;a_cellstream, VecInt &amp;a_cellPoints)</arglist>
    </member>
    <member kind="function" protection="private" static="yes">
      <type>static void</type>
      <name>GetUniqueEdgesFromPolyhedronCellstream</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>ac8fa7d38ae9f3b018316ba332debd678</anchor>
      <arglist>(const int *a_start, int &amp;a_length, boost::container::flat_set&lt; XmEdge &gt; &amp;a_cellEdges, int &amp;a_currIdx)</arglist>
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
      <name>m_cellstream</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>a59e0b9e3384561442e755ca74d007d07</anchor>
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
    <member kind="variable" protection="private">
      <type>bool</type>
      <name>m_modified</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>a64fc398df8d76becf856bbbd48669ef6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>bool</type>
      <name>m_useCache</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>a93c18aa3a2d29b9b455e9d8c75a50aed</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>VecInt</type>
      <name>m_numberOfFaces</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>ac93711d0f88770cd061a315226743199</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>VecInt</type>
      <name>m_cellFaceOffset</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>adad40b59e2a7b8270be1b1e304089e49</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>VecInt</type>
      <name>m_faceOrientation</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>a720a8128eafe6e5a9871659a1e973359</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>VecInt</type>
      <name>m_faceNeighbor</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>ac35eccf00a94559ea6b5f39cbc41cbaa</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>VecInt</type>
      <name>m_cellDimensionCounts</name>
      <anchorfile>classxms_1_1_xm_u_grid_impl.html</anchorfile>
      <anchor>a8dddb36d5519ee8a76d61f39ad6be47b</anchor>
      <arglist></arglist>
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
      <name>testGetCellCellstream</name>
      <anchorfile>class_xm_u_grid_unit_tests.html</anchorfile>
      <anchor>ae73fd2b8e90884a9cba99bd116fc1420</anchor>
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
      <name>testGetCellEdgeCount</name>
      <anchorfile>class_xm_u_grid_unit_tests.html</anchorfile>
      <anchor>abc5b4f556d07a27d80d5e300bc470123</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testGetCell3dFaceCount</name>
      <anchorfile>class_xm_u_grid_unit_tests.html</anchorfile>
      <anchor>a24af8a3e33913422fe3ad15c0e092583</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testGetCell3dFacePointCount</name>
      <anchorfile>class_xm_u_grid_unit_tests.html</anchorfile>
      <anchor>aa64c5e0c1cb6b4c7d215e9353c8eb94e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testGetPointAdjacentCellsSimple</name>
      <anchorfile>class_xm_u_grid_unit_tests.html</anchorfile>
      <anchor>a96b2c359b67c2ca38a965f61c7ad7ad3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testGetPointAdjacentCells</name>
      <anchorfile>class_xm_u_grid_unit_tests.html</anchorfile>
      <anchor>a233fd26970ec2d93297a91dc55405b96</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testGetCellPoints</name>
      <anchorfile>class_xm_u_grid_unit_tests.html</anchorfile>
      <anchor>a0fd4ec904f001bd1c46811c626b40b44</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testGetCellEdge</name>
      <anchorfile>class_xm_u_grid_unit_tests.html</anchorfile>
      <anchor>a879170cb8bc9ea1ec63d642c0a17da7a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testGetPointsAdjacentCells</name>
      <anchorfile>class_xm_u_grid_unit_tests.html</anchorfile>
      <anchor>a1e7c907b9b39e0581157e422d5613932</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testGetCellAdjacentCells</name>
      <anchorfile>class_xm_u_grid_unit_tests.html</anchorfile>
      <anchor>af64a6531be327452cc4a1ad83990acf5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testGetCellEdgeAdjacentCells</name>
      <anchorfile>class_xm_u_grid_unit_tests.html</anchorfile>
      <anchor>a5097b385a23b1507a4620aec2e706beb</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testEdgeAdjacentCells</name>
      <anchorfile>class_xm_u_grid_unit_tests.html</anchorfile>
      <anchor>a018edbf128d35d7b7b26f0df7d7431e6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testGetCell3dFacePoints</name>
      <anchorfile>class_xm_u_grid_unit_tests.html</anchorfile>
      <anchor>a4b745c672b7c2efbc42ecdc8bf6f6035</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testGetCell3dFaceAdjacentCell</name>
      <anchorfile>class_xm_u_grid_unit_tests.html</anchorfile>
      <anchor>ad0716e5ca692e4d3f3f01d9e70c9d42c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testGetPointAdjacentPoints</name>
      <anchorfile>class_xm_u_grid_unit_tests.html</anchorfile>
      <anchor>a95e4da4737130b850d934d54592857ef</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testGetCellPlanViewPolygon</name>
      <anchorfile>class_xm_u_grid_unit_tests.html</anchorfile>
      <anchor>a2a501c42695c70642a07a142391f3a10</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testGetCellPlanViewPolygonMultiSideFace</name>
      <anchorfile>class_xm_u_grid_unit_tests.html</anchorfile>
      <anchor>a197e0b6f082a9946dd3510348ecd0593</anchor>
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
      <name>testCellstreamFunctions</name>
      <anchorfile>class_xm_u_grid_unit_tests.html</anchorfile>
      <anchor>ae0cb4872e49b607a2aa891b80c77e486</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testCellEdgeAdjacentCellFunctions</name>
      <anchorfile>class_xm_u_grid_unit_tests.html</anchorfile>
      <anchor>aa118ce2f164bd551986c80b1d6a27a1f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testCellEdges</name>
      <anchorfile>class_xm_u_grid_unit_tests.html</anchorfile>
      <anchor>aa9a555c44558cf7e26637161a6e587dd</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testCell3dFaceFunctions</name>
      <anchorfile>class_xm_u_grid_unit_tests.html</anchorfile>
      <anchor>aa80efbd54ce772c637dc76f41176f32a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testGetCell3dFaceOrientationConcaveCell</name>
      <anchorfile>class_xm_u_grid_unit_tests.html</anchorfile>
      <anchor>a17d270a72f90ec49c8783aa5173d3aa4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testCell3dFunctionCaching</name>
      <anchorfile>class_xm_u_grid_unit_tests.html</anchorfile>
      <anchor>aad8fbd811c9adb8e731e4d41133f6230</anchor>
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
    <name>xms</name>
    <filename>namespacexms.html</filename>
    <class kind="class">xms::XmEdge</class>
    <class kind="class">xms::XmUGrid</class>
    <class kind="class">xms::XmUGridImpl</class>
    <member kind="typedef">
      <type>std::vector&lt; XmEdge &gt;</type>
      <name>VecEdge</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>acd21e8de7357a71eb268548c301c9f43</anchor>
      <arglist></arglist>
    </member>
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
      <type>VecPt3d</type>
      <name>ConvexHull</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a8bf3a5f5a2e5003c8de8e44a75fa9cde</anchor>
      <arglist>(const std::vector&lt; Pt3&lt; double &gt;&gt; &amp;a_points)</arglist>
    </member>
    <member kind="function">
      <type>VecInt</type>
      <name>ConvexHullWithIndices</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a8d5547f30586a0da0391aa281a4ef559</anchor>
      <arglist>(const std::vector&lt; int &gt; &amp;a_points, BSHP&lt; XmUGrid &gt; a_ugrid)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>DoLineSegmentsCross</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>aea9cf0b2bb6a3c1fc4d36d6defebecfe</anchor>
      <arglist>(const std::pair&lt; Pt3&lt; double &gt;, Pt3&lt; double &gt;&gt; &amp;a_segment1, const std::pair&lt; Pt3&lt; double &gt;, Pt3&lt; double &gt;&gt; &amp;a_segment2)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>DoLineSegmentsCross</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ac3978b6fc01a80623f117b8642e64f85</anchor>
      <arglist>(const Pt3&lt; double &gt; &amp;a_segment1Point1, const Pt3&lt; double &gt; &amp;a_segment1Point2, const Pt3&lt; double &gt; &amp;a_segment2Point1, const Pt3&lt; double &gt; &amp;a_segment2Point2)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>XmEdgesEquivalent</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a78f807814aab6186ecac3c7f44a9af37</anchor>
      <arglist>(const XmEdge &amp;a_edge1, const XmEdge &amp;a_edge2)</arglist>
    </member>
    <member kind="function">
      <type>BSHP&lt; XmUGrid &gt;</type>
      <name>TEST_XmUGrid1Left90Tri</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>acf4c5713f23e0600ec26bb0294263068</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>BSHP&lt; XmUGrid &gt;</type>
      <name>TEST_XmUGridSimpleQuad</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a65e5eef7f0e8c64484b1aaa0924364b7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>BSHP&lt; XmUGrid &gt;</type>
      <name>TEST_XmUGrid2dLinear</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a8260f0723d0bdca40b077369e5321ac8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>BSHP&lt; XmUGrid &gt;</type>
      <name>TEST_XmUGrid3dLinear</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>af931fa91f04abddf2d9469ef64ecfa70</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>BSHP&lt; XmUGrid &gt;</type>
      <name>TEST_XmUGridHexagonalPolyhedron</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a15d3f924e7e8424b2c491ef2132b700c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>BSHP&lt; xms::XmUGrid &gt;</type>
      <name>TEST_XmUBuildQuadUGrid</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a66cfca71e0f54169d0175e75a1da1b9f</anchor>
      <arglist>(const int a_rows, const int a_cols)</arglist>
    </member>
    <member kind="function">
      <type>BSHP&lt; xms::XmUGrid &gt;</type>
      <name>TEST_XmUBuildQuadUGrid</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ae795f753066bfd3749f441b965aba896</anchor>
      <arglist>(const int a_rows, const int a_cols, const xms::Pt3d &amp;a_origin)</arglist>
    </member>
    <member kind="function">
      <type>BSHP&lt; xms::XmUGrid &gt;</type>
      <name>TEST_XmUBuildHexahedronUgrid</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a0a50a2c6d678fa5e90212d03fecd3f44</anchor>
      <arglist>(const int a_rows, const int a_cols, const int a_lays)</arglist>
    </member>
    <member kind="function">
      <type>BSHP&lt; xms::XmUGrid &gt;</type>
      <name>TEST_XmUBuildHexahedronUgrid</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a9b7018697957bbe8aed198fe6cf69a07</anchor>
      <arglist>(const int a_rows, const int a_cols, const int a_lays, const xms::Pt3d &amp;a_origin)</arglist>
    </member>
    <member kind="function">
      <type>BSHP&lt; xms::XmUGrid &gt;</type>
      <name>TEST_XmUBuildPolyhedronUgrid</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a512cd32ebbe039154d962c0d47a6e4fc</anchor>
      <arglist>(const int a_rows, const int a_cols, const int a_lays)</arglist>
    </member>
    <member kind="function">
      <type>BSHP&lt; xms::XmUGrid &gt;</type>
      <name>TEST_XmUBuildPolyhedronUgrid</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a6b241889d06a379363e269e80a06ea1c</anchor>
      <arglist>(const int a_rows, const int a_cols, const int a_lays, const xms::Pt3d &amp;a_origin)</arglist>
    </member>
    <member kind="function">
      <type>BSHP&lt; xms::XmUGrid &gt;</type>
      <name>TEST_XmUBuild3DChevronUgrid</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a18cc668860be57dfc3d4800446ab6dfb</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>BSHP&lt; XmUGrid &gt;</type>
      <name>XmReadUGridFromAsciiFile</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a92b5c5c0a9e2455db6d671eb7134a76e</anchor>
      <arglist>(const std::string &amp;a_filePath)</arglist>
    </member>
    <member kind="function">
      <type>BSHP&lt; XmUGrid &gt;</type>
      <name>XmReadUGridFromStream</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a9d5b4a9ea7c259666b64babd5e190cf8</anchor>
      <arglist>(std::istream &amp;a_inStream)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>XmWriteUGridToAsciiFile</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>aad684d8d566604305a00cc4d875dd51e</anchor>
      <arglist>(BSHP&lt; XmUGrid &gt; a_ugrid, const std::string &amp;a_filePath)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>XmWriteUGridToStream</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>adcf5db1fd47ba0560a24e9ae63b942df</anchor>
      <arglist>(BSHP&lt; XmUGrid &gt; a_ugrid, std::ostream &amp;a_outStream)</arglist>
    </member>
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
    <docanchor file="md__three_d__tutorial" title="Example - Setting the UGrid Cell Stream">Example_SetCellstream3d</docanchor>
    <docanchor file="md__three_d__tutorial" title="Example - Get Number Of Points">Example_GetPointCount3d</docanchor>
    <docanchor file="md__three_d__tutorial" title="Example - Get Point Locations">Example_GetLocations3d</docanchor>
    <docanchor file="md__three_d__tutorial" title="Example - Get Location of a Point">Example_PointLocation3d</docanchor>
    <docanchor file="md__three_d__tutorial" title="Example - Set Point Location">Example_SetLocation3d</docanchor>
    <docanchor file="md__three_d__tutorial" title="Example - Get Locations of an Array of Points">Example_GetPointsLocations3d</docanchor>
    <docanchor file="md__three_d__tutorial" title="Example - Get GetExtents of UGrid">Example_GetExtents3d</docanchor>
    <docanchor file="md__three_d__tutorial" title="Example - Get Cells Associated with a Point">Example_PointCells3d</docanchor>
    <docanchor file="md__three_d__tutorial" title="Example - Get the Cells that Share the Same Point or Points">Example_GetPointsAdjacentCells3d</docanchor>
    <docanchor file="md__three_d__tutorial" title="Example - Get the Points of a Cell">Example_GetCellPointsLocations3d</docanchor>
    <docanchor file="md__three_d__tutorial" title="Example - Get the Type of a Cell">Example_GetCellType3d</docanchor>
    <docanchor file="md__three_d__tutorial" title="Example - Get the Number of the Cells of each Dimension in a UGrid">Example_GetDimensionCounts3d</docanchor>
    <docanchor file="md__three_d__tutorial" title="Example - Get the Dimension of a Cell">Example_GetCellDimension3d</docanchor>
    <docanchor file="md__three_d__tutorial" title="Example - Get the Cellstream of the UGrid">Example_GetCellstream3d</docanchor>
    <docanchor file="md__three_d__tutorial" title="Example - Get a Single Cellstream for One Cell">Example_GetCellCellstream3d</docanchor>
    <docanchor file="md__three_d__tutorial" title="Example - Get the Cells Adjacent to a Given Cell">Example_GetCellAdjacentCells3d</docanchor>
    <docanchor file="md__three_d__tutorial" title="Example - Get a Plan View Polygon">Example_GetCellPlanViewPolygon3d</docanchor>
    <docanchor file="md__three_d__tutorial" title="Example - Get Number of Cell Edges">Example_GetCellEdgeCount3d</docanchor>
    <docanchor file="md__three_d__tutorial" title="Example Get Cell Edge Adjacent Cells">Example_GetCellEdgeAdjacentCells3d</docanchor>
    <docanchor file="md__three_d__tutorial" title="Example Get Edges Associated with a Cell">Example_GetCellEdges3d</docanchor>
    <docanchor file="md__three_d__tutorial" title="Example Get Number of Faces for a Cell">Example_GetCell3dFaceCount3d</docanchor>
    <docanchor file="md__three_d__tutorial" title="Example Get Cell Face">Example_GetCell3dFacePoints3d</docanchor>
    <docanchor file="md__three_d__tutorial" title="Example Get Faces of Cell">Example_GetCell3dFacesPoints3d</docanchor>
    <docanchor file="md__three_d__tutorial" title="Example Get Cell Face Ajacent Cell">Example_GetCell3dFaceAdjacentCell3d</docanchor>
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
    <docanchor file="md__two_d__tutorial" title="Example - Setting the UGrid Cell Stream">Example_SetCellstream2d</docanchor>
    <docanchor file="md__two_d__tutorial" title="Example - Get Number Of Points">Example_GetPointCount</docanchor>
    <docanchor file="md__two_d__tutorial" title="Example - Get Points (Locations)">Example_GetLocations</docanchor>
    <docanchor file="md__two_d__tutorial" title="Example - Get Point Location">Example_GetPointLocation</docanchor>
    <docanchor file="md__two_d__tutorial" title="Example - Set Point Location">Example_SetLocation</docanchor>
    <docanchor file="md__two_d__tutorial" title="Example - Get Locations of Many Points">Example_GetPointsLocations</docanchor>
    <docanchor file="md__two_d__tutorial" title="Example - Get Extents of UGrid">Example_GetExtents</docanchor>
    <docanchor file="md__two_d__tutorial" title="Example - Get Cells Adjacent to a Point">Example_GetPointAdjacentCells</docanchor>
    <docanchor file="md__two_d__tutorial" title="Example - Get the Cells that Share All of Group of Points">Example_GetPointsAdjacentCells</docanchor>
    <docanchor file="md__two_d__tutorial" title="Example - Get the Points (or their Locations) Adjacent to Point">Example_GetPointAdjacentPoints</docanchor>
    <docanchor file="md__two_d__tutorial" title="Example - Get the Points or Locations of a Cell">Example_GetCellPointsLocations</docanchor>
    <docanchor file="md__two_d__tutorial" title="Example - Get the Type of a Cell">Example_GetCellType</docanchor>
    <docanchor file="md__two_d__tutorial" title="Example - Get the Count of Cells in a UGrid of each of the possible Dimensions">Example_GetDimensionCounts</docanchor>
    <docanchor file="md__two_d__tutorial" title="Example - Get the Dimension of a Cell">Example_GetCellDimension</docanchor>
    <docanchor file="md__two_d__tutorial" title="Example - Get the Cellstream of the UGrid">Example_GetCellstream</docanchor>
    <docanchor file="md__two_d__tutorial" title="Example - Get a the Cellstream for Single Cell">Example_GetCellCellstream</docanchor>
    <docanchor file="md__two_d__tutorial" title="Example - Get the Cells Adjacent to a Given Cell">Example_GetCellAdjacentCells</docanchor>
    <docanchor file="md__two_d__tutorial" title="Example - Get a Plan View Polygon">Example_GetCellPlanViewPolygon</docanchor>
    <docanchor file="md__two_d__tutorial" title="Example - Get Number of Cell Edges">Example_GetCellEdgeCount</docanchor>
    <docanchor file="md__two_d__tutorial" title="Example - Get Cell Edge from Edge Index">Example_GetCellEdge</docanchor>
    <docanchor file="md__two_d__tutorial" title="Example Get Cells Adjacent to an Edge of a Cell">Example_GetCellEdgeAdjacentCells</docanchor>
    <docanchor file="md__two_d__tutorial" title="Example 2D Get the Other Cell Adjacent to a particular Cell Edge">Example_GetCell2dEdgeAdjacentCell</docanchor>
    <docanchor file="md__two_d__tutorial" title="Example Get Cells Adjacent to a Given Edge">Example_GetEdgeAdjacentCells</docanchor>
    <docanchor file="md__two_d__tutorial" title="Example Get Edges of a Cell">Example_GetCellEdges</docanchor>
  </compound>
  <compound kind="page">
    <name>index</name>
    <title>xmsgrid</title>
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
