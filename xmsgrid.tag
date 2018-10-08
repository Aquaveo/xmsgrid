<?xml version='1.0' encoding='UTF-8' standalone='yes' ?>
<tagfile>
  <compound kind="file">
    <name>XmConvexHull.cpp</name>
    <path>/home/conan/xmsgrid/ugrid/</path>
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
    <path>/home/conan/xmsgrid/ugrid/</path>
    <filename>_xm_convex_hull_8h</filename>
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
    <name>XmEdge.cpp</name>
    <path>/home/conan/xmsgrid/ugrid/</path>
    <filename>_xm_edge_8cpp</filename>
    <includes id="_xm_edge_8h" name="XmEdge.h" local="no" imported="no">xmsgrid/ugrid/XmEdge.h</includes>
    <includes id="_xm_edge_8t_8h" name="XmEdge.t.h" local="no" imported="no">xmsgrid/ugrid/XmEdge.t.h</includes>
    <namespace>xms</namespace>
  </compound>
  <compound kind="file">
    <name>XmEdge.h</name>
    <path>/home/conan/xmsgrid/ugrid/</path>
    <filename>_xm_edge_8h</filename>
    <class kind="class">xms::XmEdge</class>
    <namespace>xms</namespace>
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
    <includes id="_xm_edge_8h" name="XmEdge.h" local="no" imported="no">xmsgrid/ugrid/XmEdge.h</includes>
    <includes id="_xm_convex_hull_8h" name="XmConvexHull.h" local="no" imported="no">xmsgrid/ugrid/XmConvexHull.h</includes>
    <includes id="_xm_u_grid_utils_8h" name="XmUGridUtils.h" local="no" imported="no">xmsgrid/ugrid/XmUGridUtils.h</includes>
    <includes id="_xm_u_grid_8t_8h" name="XmUGrid.t.h" local="no" imported="no">xmsgrid/ugrid/XmUGrid.t.h</includes>
    <namespace>xms</namespace>
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
    <member kind="variable" protection="private">
      <type>VecPt3d</type>
      <name>m_points</name>
      <anchorfile>_xm_u_grid_8cpp.html</anchorfile>
      <anchor>aeacd1791f540e1036ebb08ce12527cc1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>VecInt</type>
      <name>m_cellStream</name>
      <anchorfile>_xm_u_grid_8cpp.html</anchorfile>
      <anchor>ab2822cb721f3eb9978217e5073796621</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>VecInt</type>
      <name>m_cellIdxToStreamIdx</name>
      <anchorfile>_xm_u_grid_8cpp.html</anchorfile>
      <anchor>aacfc7f788d6d3214fbe6cc26befb60dc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>VecInt</type>
      <name>m_pointsToCells</name>
      <anchorfile>_xm_u_grid_8cpp.html</anchorfile>
      <anchor>afa15716f111819d325a286496b762156</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>VecInt</type>
      <name>m_pointIdxToPointsToCells</name>
      <anchorfile>_xm_u_grid_8cpp.html</anchorfile>
      <anchor>aa7318377389a0e0c9760f1b211162c3f</anchor>
      <arglist></arglist>
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
    <name>xms::XmUGrid</name>
    <filename>classxms_1_1_xm_u_grid.html</filename>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~XmUGrid</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>a714342c17dc5bb731eb78edcad66336d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static BSHP&lt; XmUGrid &gt;</type>
      <name>New</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>a689177bac440b1879851461f08009502</anchor>
      <arglist>(const VecPt3d &amp;a_points, const VecInt &amp;a_cellStream)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static BSHP&lt; XmUGrid &gt;</type>
      <name>New</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>ab8144c1fe7cb0f3da5d13db63f6937fe</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static bool</type>
      <name>ValidCellStream</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>ae14dda044c695529ea6250f860cafbd2</anchor>
      <arglist>(const VecInt &amp;a_cellStream)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type></type>
      <name>XmUGrid</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>ae30014ef614bff4158d0f1e79785162a</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>XmUGrid</name>
    <filename>class_xm_u_grid.html</filename>
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
      <name>testGetNumberOfFacePoints</name>
      <anchorfile>class_xm_u_grid_unit_tests.html</anchorfile>
      <anchor>ada0855469ef7e7a5321776f60af53600</anchor>
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
      <name>testGetPointsAttachedByEdge</name>
      <anchorfile>class_xm_u_grid_unit_tests.html</anchorfile>
      <anchor>aeb8c4063cacb388295d72bf12711fc2d</anchor>
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
      <name>testGetPlanViewPolygonMultiSideFace</name>
      <anchorfile>class_xm_u_grid_unit_tests.html</anchorfile>
      <anchor>af69608066255afd742fd8cab85d1e4d9</anchor>
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
    <name>xms</name>
    <filename>namespacexms.html</filename>
    <class kind="class">xms::XmEdge</class>
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
