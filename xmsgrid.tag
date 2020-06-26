<?xml version='1.0' encoding='UTF-8' standalone='yes' ?>
<tagfile>
  <compound kind="file">
    <name>geoms.cpp</name>
    <path>/home/conan/xmsgrid/geometry/</path>
    <filename>geoms_8cpp</filename>
    <includes id="geoms_8h" name="geoms.h" local="no" imported="no">xmsgrid/geometry/geoms.h</includes>
    <includes id="_gm_polygon_8h" name="GmPolygon.h" local="no" imported="no">xmsgrid/geometry/GmPolygon.h</includes>
    <includes id="triangles_8h" name="triangles.h" local="no" imported="no">xmsgrid/triangulate/triangles.h</includes>
    <includes id="_gm_polygon_8t_8h" name="GmPolygon.t.h" local="no" imported="no">xmsgrid/geometry/GmPolygon.t.h</includes>
    <includes id="geoms_8t_8h" name="geoms.t.h" local="no" imported="no">xmsgrid/geometry/geoms.t.h</includes>
    <class kind="class">GmPointInPolyTester_gmPointInPolygon2D</class>
    <namespace>xms</namespace>
    <member kind="function">
      <type>bool</type>
      <name>gmPointInOrOnBox2d</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a1460ad596726029e888ef3a0c67cb3ec</anchor>
      <arglist>(const Pt3d &amp;a_bMin, const Pt3d &amp;a_bMax, const Pt3d &amp;a_pt)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>gmBoxesOverlap2d</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a0a8640978d427b51b4ba6c217bb47b12</anchor>
      <arglist>(const Pt3d &amp;a_b1Min, const Pt3d &amp;a_b1Max, const Pt3d &amp;a_b2Min, const Pt3d &amp;a_b2Max)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>gmCalculateNormalizedPlaneCoefficients</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a815c09c53387db67255d3dce98695778</anchor>
      <arglist>(const Pt3d &amp;p1, const Pt3d &amp;p2, const Pt3d &amp;p3, double *a, double *b, double *c, double *d)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>gmCalculateNormalizedPlaneCoefficients</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ad18b77815c5b85e99429ee9240768473</anchor>
      <arglist>(const Pt3d *p1, const Pt3d *p2, const Pt3d *p3, double *a, double *b, double *c, double *d)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>gmMiddleZ</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>aca28f3227dce2e445d25080fbecbc2c6</anchor>
      <arglist>(const VecPt3d &amp;a_points)</arglist>
    </member>
    <member kind="function">
      <type>PtInOutOrOn_enum</type>
      <name>gmPtInCircumcircle</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ade7879f66ffa765c6ee005573218a4cd</anchor>
      <arglist>(const Pt3d &amp;pt, Pt3d circumcirclePts[3])</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>gmXyDistanceSquared</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>abfc383f1bd2f48276705d624db7144c8</anchor>
      <arglist>(const Pt3d &amp;pt1, const Pt3d &amp;pt2)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>gmCircumcircleWithTol</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a72205354f6d55c7907f6badfbc2e08b0</anchor>
      <arglist>(const Pt3d *pt1, const Pt3d *pt2, const Pt3d *pt3, double *xc, double *yc, double *r2, double tol)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>gmCartToBary</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ad512367ef48bf109240552ff3c30cc7a</anchor>
      <arglist>(const Pt3d *cart, const Pt3d *orig, double coef[6], int dir, Pt3d *bary)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>gmBaryPrepare</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a065cd6d71205487312c1e03496f5ca08</anchor>
      <arglist>(const Pt3d *p1, const Pt3d *p2, const Pt3d *p3, const Pt3d *norm, Pt3d *orig, double coef[6], int *dir, bool flag)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>gmColinearWithTol</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a546070340fe9bdf56641efa002a27ac9</anchor>
      <arglist>(const Pt3d &amp;p1, const Pt3d &amp;p2, const Pt3d &amp;p3, const double tol)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>gmIntersectLineSegmentsWithTol</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ac96bb6c54af013c284ac2c3657626c67</anchor>
      <arglist>(const Pt3d &amp;one1, const Pt3d &amp;one2, const Pt3d &amp;two1, const Pt3d &amp;two2, double *xi, double *yi, double *zi1, double *zi2, double tol)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>gmCounterClockwiseTri</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a098ef608f7092e087f9a456709714fea</anchor>
      <arglist>(const Pt3d &amp;vtx0, const Pt3d &amp;vtx1, const Pt3d &amp;vtx2)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>gmCross2D</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a06f4c8c6bc396759e5d8953d85530b46</anchor>
      <arglist>(const double &amp;dx1, const double &amp;dy1, const double &amp;dx2, const double &amp;dy2)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>gmCross2D</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a477b039c6c57c8bbe95fe341eb5b1164</anchor>
      <arglist>(const Pt3d &amp;a_origin, const Pt3d &amp;a_A, const Pt3d &amp;a_B)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>gmAngleBetween2DVectors</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>aacf14a948fef6fc782b4e7210652ad35</anchor>
      <arglist>(double dxp, double dyp, double dxn, double dyn)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>gmAngleBetween2DVectors</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ae9ee7df906ccbedcb3b364d1a5571f60</anchor>
      <arglist>(double dxp, double dyp, double dxn, double dyn, double a_magn, double a_magp)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>gmAngleBetweenEdges</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ad5d19a71ee810d5a16ea601d9ca7dda8</anchor>
      <arglist>(const Pt3d &amp;p1, const Pt3d &amp;p2, const Pt3d &amp;p3)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>gmAngleBetweenEdges</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a93b051e3a396a16ae9a9a24b4350164c</anchor>
      <arglist>(const Pt2d &amp;p1, const Pt2d &amp;p2, const Pt2d &amp;p3)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>gmComputeDeviationInDirection</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a7d7bbeb7ef537825868d7e70021d918c</anchor>
      <arglist>(const Pt3d &amp;a_p0, const Pt3d &amp;a_p1, const Pt3d &amp;a_p2)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>gmOnLineWithTol</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a45139efe30e550bbc370542f8e69a76f</anchor>
      <arglist>(const Pt3d &amp;p1, const Pt3d &amp;p2, const double x, const double y, const double tol)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>gmOnLineAndBetweenEndpointsWithTol</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a169625a9f18e45ac2b67fac67c5db715</anchor>
      <arglist>(const Pt3d &amp;a_pt1, const Pt3d &amp;a_pt2, const double a_x, const double a_y, double a_tol)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>gmAddToExtents</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a7b4416101125e2de1d4301a09f34cc4a</anchor>
      <arglist>(const Pt3d &amp;a_pt, Pt3d &amp;a_min, Pt3d &amp;a_max)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>gmAddToExtents</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a3d89b95b5652b82ece1415a73f6d102b</anchor>
      <arglist>(const Pt3d &amp;a_pt, Pt2d &amp;a_min, Pt2d &amp;a_max)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>gmAddToExtents</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a6c3d405fd7c3488c385b0caa932f9cba</anchor>
      <arglist>(const Pt2d &amp;a_pt, Pt3d &amp;a_min, Pt3d &amp;a_max)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>gmXyDistance</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a67d8975fe80c8ec9c9b424cf26e5e755</anchor>
      <arglist>(double x1, double y1, double x2, double y2)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>gmXyDistance</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a9a89d9544f63308d7a3c31e99c8281a9</anchor>
      <arglist>(const Pt3d &amp;pt1, const Pt3d &amp;pt2)</arglist>
    </member>
    <member kind="function">
      <type>Turn_enum</type>
      <name>gmTurn</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a4700adae0c06deec6e84e436c86f276b</anchor>
      <arglist>(const Pt3d &amp;a_v1, const Pt3d &amp;a_v2, const Pt3d &amp;a_v3, double a_angtol)</arglist>
    </member>
    <member kind="function">
      <type>Pt3d</type>
      <name>gmComputeCentroid</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ac462cb8b1fc78478a3f6cad9073a37e9</anchor>
      <arglist>(const VecPt3d &amp;a_points)</arglist>
    </member>
    <member kind="function">
      <type>Pt3d</type>
      <name>gmComputePolygonCentroid</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a728b2937701be72dc73f3f66ac2e7fbf</anchor>
      <arglist>(const VecPt3d &amp;pts)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>gmLinesIntersect</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>adc56691197d92d60abcb0e77e48df4ea</anchor>
      <arglist>(const Pt3d &amp;one1, const Pt3d &amp;one2, const Pt3d &amp;two1, const Pt3d &amp;two2)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>gmLinesCross</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a576c914d0519eaeab0e4494e4f000c75</anchor>
      <arglist>(const Pt3d &amp;a_segment1Point1, const Pt3d &amp;a_segment1Point2, const Pt3d &amp;a_segment2Point1, const Pt3d &amp;a_segment2Point2)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>gmPointInPolygon2D</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a43bab17fe8d6f6b67de11a49e5127424</anchor>
      <arglist>(const T *a_verts, const size_t a_num, const double a_x, const double a_y, const double a_tol)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>gmPointInPolygon2D</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a457f87dda88f474bebe491ec094b693f</anchor>
      <arglist>(const Pt3d *a_verts, size_t a_num, double a_x, double a_y)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>gmPointInPolygon2D</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>aa32ddc6f5892464bfe6d596c1922f7f5</anchor>
      <arglist>(const Pt3d *a_verts, size_t a_num, Pt3d a_pt)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>gmPointInPolygon2D</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a959d71253e45c5f67e1bf202a5a122fd</anchor>
      <arglist>(const Pt2i *a_verts, size_t a_num, Pt2d a_pt)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>gmPointInPolygon2D</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>aac4a8fdb18373864527f2fad0bb8c433</anchor>
      <arglist>(const Pt2i *a_verts, size_t a_num, Pt3d a_pt)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>gmPointInPolygon2D</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a3b879e6c80208a8780496137ac51c3c9</anchor>
      <arglist>(const Pt2i *a_verts, size_t a_num, Pt2i a_pt)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>gmPointInPolygon2D</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>aad56bb08be2f1969cd7912f59d49d9e2</anchor>
      <arglist>(const VecPt3d &amp;a_verts, const Pt3d &amp;a_pt)</arglist>
    </member>
    <member kind="function">
      <type>template int</type>
      <name>gmPointInPolygon2D&lt; Pt3d &gt;</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a241b33f3ef73ed56ca73fdbb830e14a3</anchor>
      <arglist>(const Pt3d *a_verts, const size_t a_num, const double a_x, const double a_y, const double a_tol)</arglist>
    </member>
    <member kind="function">
      <type>template int</type>
      <name>gmPointInPolygon2D&lt; Pt2d &gt;</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a84aea859e24101dbd69dc902d4f423f8</anchor>
      <arglist>(const Pt2d *a_verts, const size_t a_num, const double a_x, const double a_y, const double a_tol)</arglist>
    </member>
    <member kind="function">
      <type>template int</type>
      <name>gmPointInPolygon2D&lt; Pt2i &gt;</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a296ceeadef9d9d4e4ba698f52c44c6c9</anchor>
      <arglist>(const Pt2i *a_verts, const size_t a_num, const double a_x, const double a_y, const double a_tol)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>gmComputeXyTol</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a03126d64edc4ecb587a357fbfa5fb08c</anchor>
      <arglist>(const Pt3d &amp;a_mn, const Pt3d &amp;a_mx)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>gmXyTol</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a7a33258adddbd27ad36954f6ccdcdef7</anchor>
      <arglist>(bool a_set, double a_value)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>gmZTol</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>af0e7dba5dafe577d6345afe25580777a</anchor>
      <arglist>(bool a_set, double a_value)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>gmEqualPointsXY</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a9a226e666728d9fde914f18db63a4714</anchor>
      <arglist>(double x1, double y1, double x2, double y2, double tolerance)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>gmEqualPointsXY</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ac504f8315cad401c34447f06c5b6b07d</anchor>
      <arglist>(double x1, double y1, double x2, double y2)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>gmEqualPointsXY</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a427db5d209d5d8d22ec417417de4d702</anchor>
      <arglist>(const Pt2d &amp;a_pt1, const Pt2d &amp;a_pt2, double tol)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>gmEqualPointsXY</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a6724be333a3994b7cb0bbe1ec832f244</anchor>
      <arglist>(const Pt3d &amp;a_pt1, const Pt3d &amp;a_pt2, double tol)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>gmEqualPointsXY</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a878ec06b0e9bbd3afccd2bf70ec54621</anchor>
      <arglist>(const Pt2i &amp;point1, const Pt2i &amp;point2)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>gmEqualPointsXYZ</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a8c3a08ccd01c4230e7498d793a9d90cd</anchor>
      <arglist>(double x1, double y1, double z1, double x2, double y2, double z2, double tolerance)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>gmEqualPointsXYZ</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a6e4ba75c670a283360048a5365558916</anchor>
      <arglist>(double x1, double y1, double z1, double x2, double y2, double z2)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>gmEqualPointsXYZ</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a326b40120fd0517c654d9a94a963e83e</anchor>
      <arglist>(const Pt3d &amp;pt1, const Pt3d &amp;pt2, double tol)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>gmPointInTriangleWithTol</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a5b2cb41a4510b0ba885d4a4691781506</anchor>
      <arglist>(const Pt3d *p1, const Pt3d *p2, const Pt3d *p3, double x, double y, double tol)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>gmInsideOrOnLineWithTol</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a33f9850dc05d9598dcd1e4d06d7a64a2</anchor>
      <arglist>(const Pt3d *p1, const Pt3d *p2, const Pt3d *inpoint, const double x, const double y, const double tol, double *dist)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>gmPolygonArea</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a299579fe39539f353e245d1c41c8eb0f</anchor>
      <arglist>(const Pt3d *pts, size_t npoints)</arglist>
    </member>
    <member kind="function">
      <type>VecPt3d</type>
      <name>gmArrayToVecPt3d</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a7877ffa4620ae49b12d0b49de2289135</anchor>
      <arglist>(double *a_array, int a_size)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>gmEnvelopeOfPts</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>aeb0fecb3c9d9aa77f4ff42ec6a608f26</anchor>
      <arglist>(const VecPt3d &amp;a_pts, Pt3d &amp;a_min, Pt3d &amp;a_max)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>gmOrderPointsCounterclockwise</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ac3222874630da8f1f8537f1a6135846f</anchor>
      <arglist>(const VecPt3d &amp;a_pts, VecInt &amp;a_ccwOrder, int a_startindex)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>gmOrderPointsCounterclockwise</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>aed9ee1170ee7004d626347f8886e4943</anchor>
      <arglist>(VecPt3d &amp;a_pts)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>gmFindClosestPtOnSegment</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ad89c693cc48610a4a7dcf89f22d55118</anchor>
      <arglist>(const Pt3d &amp;a_pt1, const Pt3d &amp;a_pt2, const Pt3d &amp;a_pt, Pt3d &amp;a_newpt, const double a_tol)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>gmPtDistanceAlongSegment</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a9f9e75d979ef1bc5c0c217115eb34a04</anchor>
      <arglist>(const Pt3d &amp;a_pt1, const Pt3d &amp;a_pt2, const Pt3d &amp;a_pt, const double a_tol)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>gmInsideOfLineWithTol</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>aa78a4612aa080741e2ce7aa301aab615</anchor>
      <arglist>(const Pt3d &amp;a_vertex1, const Pt3d &amp;a_vertex2, const Pt3d &amp;a_oppositevertex, const double a_x, const double a_y, const double a_tol)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>gmExtents2D</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a38a42e7eea0d9ce1dfebc230e50ad166</anchor>
      <arglist>(const VecPt3d &amp;a_points, Pt2d &amp;a_min, Pt2d &amp;a_max)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>gmExtents2D</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ac21eba0393f3071a3af665e8cfedb7bd</anchor>
      <arglist>(const VecPt3d &amp;a_points, Pt3d &amp;a_min, Pt3d &amp;a_max)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>gmExtents3D</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ac4c2eb4bc4667e6479497b0b529562c8</anchor>
      <arglist>(const VecPt3d &amp;a_points, Pt3d &amp;a_min, Pt3d &amp;a_max)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>gmPerpendicularAngle</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a8397c11d92c81098edabbc41ab06bffa</anchor>
      <arglist>(const Pt3d &amp;a_pt1, const Pt3d &amp;a_pt2)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>gmBisectingAngle</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>afbc887b28d4ef88ce8c14aab5482765a</anchor>
      <arglist>(const Pt3d &amp;a_p1, const Pt3d &amp;a_p2, const Pt3d &amp;a_p3)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>gmComponentMagnitudes</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a214f89ef03c8dd4f0ca2e4418fc1757d</anchor>
      <arglist>(double *a_x, double *a_y, double *a_mag, double *a_dir, bool a_tomagdir)</arglist>
    </member>
    <member kind="function">
      <type>Pt3d</type>
      <name>gmCreateVector</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ae15d7a7439937df12789f169f594c3df</anchor>
      <arglist>(const Pt3d &amp;a_p1, const Pt3d &amp;a_p2)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>gmConvertAngleToBetween0And360</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a3de1bfdf51c7b4ee1b3c2a3f1ecb96ba</anchor>
      <arglist>(double a_angle, bool a_InDegrees)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>gmCross3D</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>afff1edecd418a115ea72edd1fffc115e</anchor>
      <arglist>(const Pt3d &amp;a_vec1, const Pt3d &amp;a_vec2, Pt3d *a_vec3)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>gmDot3D</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a02f5cd9ea7e783cdb00ba6ec4f88a357</anchor>
      <arglist>(const Pt3d &amp;a_vec1, const Pt3d &amp;a_vec2)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>gmIntersectTriangleAndLineSegment</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ab82e28a71a8e0794c21d756c2308fd3b</anchor>
      <arglist>(const Pt3d &amp;a_pt1, const Pt3d &amp;a_pt2, const Pt3d &amp;a_t0, const Pt3d &amp;a_t1, const Pt3d &amp;a_t2, Pt3d &amp;a_IntersectPt)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>gm2DDistanceToLineWithTol</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a9684415f055c6e1f7b779d3a9e84f609</anchor>
      <arglist>(const Pt3d *a_pt1, const Pt3d *a_pt2, double a_x, double a_y, double a_tol)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>gmGetConvexHull</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a74e3df59e816303d09c6923d6e8d7272</anchor>
      <arglist>(const VecPt3d &amp;a_pts, VecPt3d &amp;a_hull, bool a_includeOn)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>geoms.h</name>
    <path>/home/conan/xmsgrid/geometry/</path>
    <filename>geoms_8h</filename>
    <namespace>xms</namespace>
    <member kind="enumeration">
      <type></type>
      <name>Turn_enum</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a0682e25caba7c1d65216a5680cc0217b</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>TURN_LEFT</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a0682e25caba7c1d65216a5680cc0217babc1acb082c93789cb378bf87597f42dd</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>TURN_RIGHT</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a0682e25caba7c1d65216a5680cc0217ba4a1de04425d6c2953fbf40f2b29c15c7</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>TURN_COLINEAR_180</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a0682e25caba7c1d65216a5680cc0217badbc22a212895c3de629b927b410a7065</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>TURN_COLINEAR_0</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a0682e25caba7c1d65216a5680cc0217ba06d649a650f4acb061afb7acd5a2dbd7</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>PtInOutOrOn_enum</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a89f7d814569daefeabe9f5e3b5fbd213</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>PT_ERROR</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a89f7d814569daefeabe9f5e3b5fbd213a75f63694d4c2fbd0065900d8a51dcf54</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>PT_IN</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a89f7d814569daefeabe9f5e3b5fbd213a5f2058ee26998db92e7beedea5fd7e1c</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>PT_OUT</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a89f7d814569daefeabe9f5e3b5fbd213af6c0802668cf9ce14590690ec216dc6a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>PT_ON</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a89f7d814569daefeabe9f5e3b5fbd213afef40dd1d13df2164ce1a2ba841a3b6a</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>gmPointInOrOnBox2d</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a1460ad596726029e888ef3a0c67cb3ec</anchor>
      <arglist>(const Pt3d &amp;a_bMin, const Pt3d &amp;a_bMax, const Pt3d &amp;a_pt)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>gmBoxesOverlap2d</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a0a8640978d427b51b4ba6c217bb47b12</anchor>
      <arglist>(const Pt3d &amp;a_b1Min, const Pt3d &amp;a_b1Max, const Pt3d &amp;a_b2Min, const Pt3d &amp;a_b2Max)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>gmCalculateNormalizedPlaneCoefficients</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a815c09c53387db67255d3dce98695778</anchor>
      <arglist>(const Pt3d &amp;p1, const Pt3d &amp;p2, const Pt3d &amp;p3, double *a, double *b, double *c, double *d)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>gmCalculateNormalizedPlaneCoefficients</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ad18b77815c5b85e99429ee9240768473</anchor>
      <arglist>(const Pt3d *p1, const Pt3d *p2, const Pt3d *p3, double *a, double *b, double *c, double *d)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>gmMiddleZ</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>aca28f3227dce2e445d25080fbecbc2c6</anchor>
      <arglist>(const VecPt3d &amp;a_points)</arglist>
    </member>
    <member kind="function">
      <type>PtInOutOrOn_enum</type>
      <name>gmPtInCircumcircle</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ade7879f66ffa765c6ee005573218a4cd</anchor>
      <arglist>(const Pt3d &amp;pt, Pt3d circumcirclePts[3])</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>gmXyDistanceSquared</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>abfc383f1bd2f48276705d624db7144c8</anchor>
      <arglist>(const Pt3d &amp;pt1, const Pt3d &amp;pt2)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>gmCircumcircleWithTol</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a72205354f6d55c7907f6badfbc2e08b0</anchor>
      <arglist>(const Pt3d *pt1, const Pt3d *pt2, const Pt3d *pt3, double *xc, double *yc, double *r2, double tol)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>gmCartToBary</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ad512367ef48bf109240552ff3c30cc7a</anchor>
      <arglist>(const Pt3d *cart, const Pt3d *orig, double coef[6], int dir, Pt3d *bary)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>gmBaryPrepare</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a065cd6d71205487312c1e03496f5ca08</anchor>
      <arglist>(const Pt3d *p1, const Pt3d *p2, const Pt3d *p3, const Pt3d *norm, Pt3d *orig, double coef[6], int *dir, bool flag)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>gmColinearWithTol</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a546070340fe9bdf56641efa002a27ac9</anchor>
      <arglist>(const Pt3d &amp;p1, const Pt3d &amp;p2, const Pt3d &amp;p3, const double tol)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>gmIntersectLineSegmentsWithTol</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ac96bb6c54af013c284ac2c3657626c67</anchor>
      <arglist>(const Pt3d &amp;one1, const Pt3d &amp;one2, const Pt3d &amp;two1, const Pt3d &amp;two2, double *xi, double *yi, double *zi1, double *zi2, double tol)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>gmCounterClockwiseTri</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a098ef608f7092e087f9a456709714fea</anchor>
      <arglist>(const Pt3d &amp;vtx0, const Pt3d &amp;vtx1, const Pt3d &amp;vtx2)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>gmCross2D</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a06f4c8c6bc396759e5d8953d85530b46</anchor>
      <arglist>(const double &amp;dx1, const double &amp;dy1, const double &amp;dx2, const double &amp;dy2)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>gmCross2D</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a477b039c6c57c8bbe95fe341eb5b1164</anchor>
      <arglist>(const Pt3d &amp;a_origin, const Pt3d &amp;a_A, const Pt3d &amp;a_B)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>gmAngleBetween2DVectors</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>aacf14a948fef6fc782b4e7210652ad35</anchor>
      <arglist>(double dxp, double dyp, double dxn, double dyn)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>gmAngleBetween2DVectors</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ae9ee7df906ccbedcb3b364d1a5571f60</anchor>
      <arglist>(double dxp, double dyp, double dxn, double dyn, double a_magn, double a_magp)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>gmAngleBetweenEdges</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ad5d19a71ee810d5a16ea601d9ca7dda8</anchor>
      <arglist>(const Pt3d &amp;p1, const Pt3d &amp;p2, const Pt3d &amp;p3)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>gmAngleBetweenEdges</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a93b051e3a396a16ae9a9a24b4350164c</anchor>
      <arglist>(const Pt2d &amp;p1, const Pt2d &amp;p2, const Pt2d &amp;p3)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>gmComputeDeviationInDirection</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a7d7bbeb7ef537825868d7e70021d918c</anchor>
      <arglist>(const Pt3d &amp;a_p0, const Pt3d &amp;a_p1, const Pt3d &amp;a_p2)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>gmOnLineAndBetweenEndpointsWithTol</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a169625a9f18e45ac2b67fac67c5db715</anchor>
      <arglist>(const Pt3d &amp;a_pt1, const Pt3d &amp;a_pt2, const double a_x, const double a_y, double a_tol)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>gmOnLineWithTol</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a45139efe30e550bbc370542f8e69a76f</anchor>
      <arglist>(const Pt3d &amp;p1, const Pt3d &amp;p2, const double x, const double y, const double tol)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>gmAddToExtents</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a7b4416101125e2de1d4301a09f34cc4a</anchor>
      <arglist>(const Pt3d &amp;a_pt, Pt3d &amp;a_min, Pt3d &amp;a_max)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>gmAddToExtents</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a3d89b95b5652b82ece1415a73f6d102b</anchor>
      <arglist>(const Pt3d &amp;a_pt, Pt2d &amp;a_min, Pt2d &amp;a_max)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>gmAddToExtents</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a6c3d405fd7c3488c385b0caa932f9cba</anchor>
      <arglist>(const Pt2d &amp;a_pt, Pt3d &amp;a_min, Pt3d &amp;a_max)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>gmXyDistance</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a67d8975fe80c8ec9c9b424cf26e5e755</anchor>
      <arglist>(double x1, double y1, double x2, double y2)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>gmXyDistance</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a9a89d9544f63308d7a3c31e99c8281a9</anchor>
      <arglist>(const Pt3d &amp;pt1, const Pt3d &amp;pt2)</arglist>
    </member>
    <member kind="function">
      <type>Turn_enum</type>
      <name>gmTurn</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a4700adae0c06deec6e84e436c86f276b</anchor>
      <arglist>(const Pt3d &amp;a_v1, const Pt3d &amp;a_v2, const Pt3d &amp;a_v3, double a_angtol)</arglist>
    </member>
    <member kind="function">
      <type>Pt3d</type>
      <name>gmComputeCentroid</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ac462cb8b1fc78478a3f6cad9073a37e9</anchor>
      <arglist>(const VecPt3d &amp;a_points)</arglist>
    </member>
    <member kind="function">
      <type>Pt3d</type>
      <name>gmComputePolygonCentroid</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a728b2937701be72dc73f3f66ac2e7fbf</anchor>
      <arglist>(const VecPt3d &amp;pts)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>gmLinesIntersect</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>adc56691197d92d60abcb0e77e48df4ea</anchor>
      <arglist>(const Pt3d &amp;one1, const Pt3d &amp;one2, const Pt3d &amp;two1, const Pt3d &amp;two2)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>gmLinesCross</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a576c914d0519eaeab0e4494e4f000c75</anchor>
      <arglist>(const Pt3d &amp;a_segment1Point1, const Pt3d &amp;a_segment1Point2, const Pt3d &amp;a_segment2Point1, const Pt3d &amp;a_segment2Point2)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>gmPointInPolygon2D</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a457f87dda88f474bebe491ec094b693f</anchor>
      <arglist>(const Pt3d *a_verts, size_t a_num, double a_x, double a_y)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>gmPointInPolygon2D</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>aa32ddc6f5892464bfe6d596c1922f7f5</anchor>
      <arglist>(const Pt3d *a_verts, size_t a_num, Pt3d a_pt)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>gmPointInPolygon2D</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a959d71253e45c5f67e1bf202a5a122fd</anchor>
      <arglist>(const Pt2i *a_verts, size_t a_num, Pt2d a_pt)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>gmPointInPolygon2D</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a3b879e6c80208a8780496137ac51c3c9</anchor>
      <arglist>(const Pt2i *a_verts, size_t a_num, Pt2i a_pt)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>gmPointInPolygon2D</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>aac4a8fdb18373864527f2fad0bb8c433</anchor>
      <arglist>(const Pt2i *a_verts, size_t a_num, Pt3d a_pt)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>gmPointInPolygon2D</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>aad56bb08be2f1969cd7912f59d49d9e2</anchor>
      <arglist>(const VecPt3d &amp;a_verts, const Pt3d &amp;a_pt)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>gmPointInPolygon2D</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a43bab17fe8d6f6b67de11a49e5127424</anchor>
      <arglist>(const T *a_verts, const size_t a_num, const double a_x, const double a_y, const double a_tol)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>gmComputeXyTol</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a03126d64edc4ecb587a357fbfa5fb08c</anchor>
      <arglist>(const Pt3d &amp;a_mn, const Pt3d &amp;a_mx)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>gmXyTol</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a7a33258adddbd27ad36954f6ccdcdef7</anchor>
      <arglist>(bool a_set, double a_value)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>gmZTol</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>af0e7dba5dafe577d6345afe25580777a</anchor>
      <arglist>(bool a_set, double a_value)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>gmEqualPointsXY</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ac504f8315cad401c34447f06c5b6b07d</anchor>
      <arglist>(double x1, double y1, double x2, double y2)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>gmEqualPointsXY</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a9a226e666728d9fde914f18db63a4714</anchor>
      <arglist>(double x1, double y1, double x2, double y2, double tolerance)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>gmEqualPointsXY</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a878ec06b0e9bbd3afccd2bf70ec54621</anchor>
      <arglist>(const Pt2i &amp;point1, const Pt2i &amp;point2)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>gmEqualPointsXY</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a427db5d209d5d8d22ec417417de4d702</anchor>
      <arglist>(const Pt2d &amp;a_pt1, const Pt2d &amp;a_pt2, double tol)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>gmEqualPointsXY</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a6724be333a3994b7cb0bbe1ec832f244</anchor>
      <arglist>(const Pt3d &amp;a_pt1, const Pt3d &amp;a_pt2, double tol)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>gmEqualPointsXYZ</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a6e4ba75c670a283360048a5365558916</anchor>
      <arglist>(double x1, double y1, double z1, double x2, double y2, double z2)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>gmEqualPointsXYZ</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a8c3a08ccd01c4230e7498d793a9d90cd</anchor>
      <arglist>(double x1, double y1, double z1, double x2, double y2, double z2, double tolerance)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>gmEqualPointsXYZ</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a326b40120fd0517c654d9a94a963e83e</anchor>
      <arglist>(const Pt3d &amp;pt1, const Pt3d &amp;pt2, double tol)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>gmPointInTriangleWithTol</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a5b2cb41a4510b0ba885d4a4691781506</anchor>
      <arglist>(const Pt3d *p1, const Pt3d *p2, const Pt3d *p3, double x, double y, double tol)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>gmInsideOrOnLineWithTol</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a33f9850dc05d9598dcd1e4d06d7a64a2</anchor>
      <arglist>(const Pt3d *p1, const Pt3d *p2, const Pt3d *inpoint, const double x, const double y, const double tol, double *dist)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>gmPolygonArea</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a299579fe39539f353e245d1c41c8eb0f</anchor>
      <arglist>(const Pt3d *pts, size_t npoints)</arglist>
    </member>
    <member kind="function">
      <type>VecPt3d</type>
      <name>gmArrayToVecPt3d</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a7877ffa4620ae49b12d0b49de2289135</anchor>
      <arglist>(double *a_array, int a_size)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>gmEnvelopeOfPts</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>aeb0fecb3c9d9aa77f4ff42ec6a608f26</anchor>
      <arglist>(const VecPt3d &amp;a_pts, Pt3d &amp;a_min, Pt3d &amp;a_max)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>gmOrderPointsCounterclockwise</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ac3222874630da8f1f8537f1a6135846f</anchor>
      <arglist>(const VecPt3d &amp;a_pts, VecInt &amp;a_ccwOrder, int a_startindex)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>gmOrderPointsCounterclockwise</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>aed9ee1170ee7004d626347f8886e4943</anchor>
      <arglist>(VecPt3d &amp;a_pts)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>gmFindClosestPtOnSegment</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ad89c693cc48610a4a7dcf89f22d55118</anchor>
      <arglist>(const Pt3d &amp;a_pt1, const Pt3d &amp;a_pt2, const Pt3d &amp;a_pt, Pt3d &amp;a_newpt, const double a_tol)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>gmPtDistanceAlongSegment</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a9f9e75d979ef1bc5c0c217115eb34a04</anchor>
      <arglist>(const Pt3d &amp;a_pt1, const Pt3d &amp;a_pt2, const Pt3d &amp;a_pt, const double a_tol)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>gmInsideOfLineWithTol</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>aa78a4612aa080741e2ce7aa301aab615</anchor>
      <arglist>(const Pt3d &amp;a_vertex1, const Pt3d &amp;a_vertex2, const Pt3d &amp;a_oppositevertex, const double a_x, const double a_y, const double a_tol)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>gmExtents2D</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a38a42e7eea0d9ce1dfebc230e50ad166</anchor>
      <arglist>(const VecPt3d &amp;a_points, Pt2d &amp;a_min, Pt2d &amp;a_max)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>gmExtents2D</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ac21eba0393f3071a3af665e8cfedb7bd</anchor>
      <arglist>(const VecPt3d &amp;a_points, Pt3d &amp;a_min, Pt3d &amp;a_max)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>gmExtents3D</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ac4c2eb4bc4667e6479497b0b529562c8</anchor>
      <arglist>(const VecPt3d &amp;a_points, Pt3d &amp;a_min, Pt3d &amp;a_max)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>gmPerpendicularAngle</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a8397c11d92c81098edabbc41ab06bffa</anchor>
      <arglist>(const Pt3d &amp;a_pt1, const Pt3d &amp;a_pt2)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>gmBisectingAngle</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>afbc887b28d4ef88ce8c14aab5482765a</anchor>
      <arglist>(const Pt3d &amp;a_p1, const Pt3d &amp;a_p2, const Pt3d &amp;a_p3)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>gmComponentMagnitudes</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a214f89ef03c8dd4f0ca2e4418fc1757d</anchor>
      <arglist>(double *a_x, double *a_y, double *a_mag, double *a_dir, bool a_tomagdir)</arglist>
    </member>
    <member kind="function">
      <type>Pt3d</type>
      <name>gmCreateVector</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ae15d7a7439937df12789f169f594c3df</anchor>
      <arglist>(const Pt3d &amp;a_p1, const Pt3d &amp;a_p2)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>gmConvertAngleToBetween0And360</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a3de1bfdf51c7b4ee1b3c2a3f1ecb96ba</anchor>
      <arglist>(double a_angle, bool a_InDegrees)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>gmCross3D</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>afff1edecd418a115ea72edd1fffc115e</anchor>
      <arglist>(const Pt3d &amp;a_vec1, const Pt3d &amp;a_vec2, Pt3d *a_vec3)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>gmDot3D</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a02f5cd9ea7e783cdb00ba6ec4f88a357</anchor>
      <arglist>(const Pt3d &amp;a_vec1, const Pt3d &amp;a_vec2)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>gmIntersectTriangleAndLineSegment</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ab82e28a71a8e0794c21d756c2308fd3b</anchor>
      <arglist>(const Pt3d &amp;a_pt1, const Pt3d &amp;a_pt2, const Pt3d &amp;a_t0, const Pt3d &amp;a_t1, const Pt3d &amp;a_t2, Pt3d &amp;a_IntersectPt)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>gm2DDistanceToLineWithTol</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a9684415f055c6e1f7b779d3a9e84f609</anchor>
      <arglist>(const Pt3d *a_pt1, const Pt3d *a_pt2, double a_x, double a_y, double a_tol)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>gmGetConvexHull</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a74e3df59e816303d09c6923d6e8d7272</anchor>
      <arglist>(const VecPt3d &amp;a_pts, VecPt3d &amp;a_hull, bool a_includeOn)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>geoms.t.h</name>
    <path>/home/conan/xmsgrid/geometry/</path>
    <filename>geoms_8t_8h</filename>
    <class kind="class">GeomsXmsngUnitTests</class>
    <class kind="class">GmPointInPolyUnitTests</class>
    <class kind="class">GeomsXmsngIntermediateTests</class>
  </compound>
  <compound kind="file">
    <name>GmBoostTypes.h</name>
    <path>/home/conan/xmsgrid/geometry/</path>
    <filename>_gm_boost_types_8h</filename>
    <namespace>xms</namespace>
    <member kind="typedef">
      <type>boost::geometry::model::d2::point_xy&lt; double &gt;</type>
      <name>GmBstPt2d</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a5f1677620ca85b6bcc1065b757f3e337</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>boost::geometry::model::polygon&lt; GmBstPt2d &gt;</type>
      <name>GmBstPoly2d</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a93e3d438c33ced49f413cd84323982d5</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>boost::geometry::model::polygon&lt; Pt3d &gt;</type>
      <name>GmBstPoly3d</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a05c9c43c740eaf5b56f436ec992dca5f</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>boost::geometry::model::box&lt; Pt3d &gt;</type>
      <name>GmBstBox3d</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>af7ac61e434c47abf90a1349336f7e8b7</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>boost::geometry::model::linestring&lt; Pt3d &gt;</type>
      <name>GmBstLine3d</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a9bb6715848b64f01474619d28cd619d9</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>boost::geometry::ring_type&lt; GmBstPoly3d &gt;::type</type>
      <name>GmBstRing3d</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a4d04b2e2f10cd613e47211b9ac69784e</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>GmExtents.cpp</name>
    <path>/home/conan/xmsgrid/geometry/</path>
    <filename>_gm_extents_8cpp</filename>
    <includes id="_gm_extents_8h" name="GmExtents.h" local="no" imported="no">xmsgrid/geometry/GmExtents.h</includes>
    <includes id="_gm_extents_8t_8h" name="GmExtents.t.h" local="no" imported="no">xmsgrid/geometry/GmExtents.t.h</includes>
    <namespace>xms</namespace>
  </compound>
  <compound kind="file">
    <name>GmExtents.h</name>
    <path>/home/conan/xmsgrid/geometry/</path>
    <filename>_gm_extents_8h</filename>
    <class kind="class">xms::GmExtents2d</class>
    <class kind="class">xms::GmExtents3d</class>
    <namespace>xms</namespace>
  </compound>
  <compound kind="file">
    <name>GmExtents.t.h</name>
    <path>/home/conan/xmsgrid/geometry/</path>
    <filename>_gm_extents_8t_8h</filename>
    <class kind="class">GmExtents3dUnitTests</class>
  </compound>
  <compound kind="file">
    <name>GmMultiPolyIntersectionSorter.h</name>
    <path>/home/conan/xmsgrid/geometry/</path>
    <filename>_gm_multi_poly_intersection_sorter_8h</filename>
    <class kind="class">xms::GmMultiPolyIntersectionSorter</class>
    <namespace>xms</namespace>
  </compound>
  <compound kind="file">
    <name>GmMultiPolyIntersectionSorterTerse.cpp</name>
    <path>/home/conan/xmsgrid/geometry/</path>
    <filename>_gm_multi_poly_intersection_sorter_terse_8cpp</filename>
    <includes id="_gm_multi_poly_intersection_sorter_terse_8h" name="GmMultiPolyIntersectionSorterTerse.h" local="no" imported="no">xmsgrid/geometry/GmMultiPolyIntersectionSorterTerse.h</includes>
    <includes id="_gm_multi_poly_intersector_data_8h" name="GmMultiPolyIntersectorData.h" local="no" imported="no">xmsgrid/geometry/GmMultiPolyIntersectorData.h</includes>
    <includes id="geoms_8h" name="geoms.h" local="no" imported="no">xmsgrid/geometry/geoms.h</includes>
    <namespace>xms</namespace>
  </compound>
  <compound kind="file">
    <name>GmMultiPolyIntersectionSorterTerse.h</name>
    <path>/home/conan/xmsgrid/geometry/</path>
    <filename>_gm_multi_poly_intersection_sorter_terse_8h</filename>
    <includes id="_gm_multi_poly_intersection_sorter_8h" name="GmMultiPolyIntersectionSorter.h" local="no" imported="no">xmsgrid/geometry/GmMultiPolyIntersectionSorter.h</includes>
    <class kind="class">xms::GmMultiPolyIntersectionSorterTerse</class>
    <namespace>xms</namespace>
  </compound>
  <compound kind="file">
    <name>GmMultiPolyIntersector.cpp</name>
    <path>/home/conan/xmsgrid/geometry/</path>
    <filename>_gm_multi_poly_intersector_8cpp</filename>
    <includes id="_gm_multi_poly_intersector_8h" name="GmMultiPolyIntersector.h" local="no" imported="no">xmsgrid/geometry/GmMultiPolyIntersector.h</includes>
    <includes id="_gm_boost_types_8h" name="GmBoostTypes.h" local="no" imported="no">xmsgrid/geometry/GmBoostTypes.h</includes>
    <includes id="_gm_multi_poly_intersection_sorter_8h" name="GmMultiPolyIntersectionSorter.h" local="no" imported="no">xmsgrid/geometry/GmMultiPolyIntersectionSorter.h</includes>
    <includes id="_gm_multi_poly_intersector_data_8h" name="GmMultiPolyIntersectorData.h" local="no" imported="no">xmsgrid/geometry/GmMultiPolyIntersectorData.h</includes>
    <includes id="geoms_8h" name="geoms.h" local="no" imported="no">xmsgrid/geometry/geoms.h</includes>
    <includes id="_gm_multi_poly_intersector_8t_8h" name="GmMultiPolyIntersector.t.h" local="no" imported="no">xmsgrid/geometry/GmMultiPolyIntersector.t.h</includes>
    <includes id="_gm_multi_poly_intersection_sorter_terse_8h" name="GmMultiPolyIntersectionSorterTerse.h" local="no" imported="no">xmsgrid/geometry/GmMultiPolyIntersectionSorterTerse.h</includes>
    <includes id="triangles_8h" name="triangles.h" local="no" imported="no">xmsgrid/triangulate/triangles.h</includes>
    <class kind="class">xms::GmMultiPolyIntersectorImpl</class>
    <namespace>xms</namespace>
    <member kind="typedef">
      <type>std::pair&lt; GmBstBox3d, int &gt;</type>
      <name>ValueBox</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ad371b9317cd9cab40e2625cb4e35df05</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>bgi::rtree&lt; ValueBox, bgi::quadratic&lt; 8 &gt; &gt;</type>
      <name>RtreeBox</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>aa547c53279be0830c2afc7536f557044</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>GmMultiPolyIntersector.h</name>
    <path>/home/conan/xmsgrid/geometry/</path>
    <filename>_gm_multi_poly_intersector_8h</filename>
    <class kind="class">xms::GmMultiPolyIntersector</class>
    <namespace>xms</namespace>
    <member kind="enumeration">
      <type></type>
      <name>GmMultiPolyIntersectorQueryEnum</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>af3e9dae61009fe77b79327ee8ebe9b2e</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>GmMultiPolyIntersector.t.h</name>
    <path>/home/conan/xmsgrid/geometry/</path>
    <filename>_gm_multi_poly_intersector_8t_8h</filename>
    <class kind="class">GmMultiPolyIntersectorUnitTests</class>
    <class kind="class">GmMultiPolyIntersector2IntermediateTests</class>
  </compound>
  <compound kind="file">
    <name>GmMultiPolyIntersectorData.h</name>
    <path>/home/conan/xmsgrid/geometry/</path>
    <filename>_gm_multi_poly_intersector_data_8h</filename>
    <class kind="class">xms::ix</class>
    <class kind="struct">xms::GmMultiPolyIntersectorData</class>
    <namespace>xms</namespace>
  </compound>
  <compound kind="file">
    <name>GmPolygon.cpp</name>
    <path>/home/conan/xmsgrid/geometry/</path>
    <filename>_gm_polygon_8cpp</filename>
    <includes id="_gm_polygon_8h" name="GmPolygon.h" local="no" imported="no">xmsgrid/geometry/GmPolygon.h</includes>
    <includes id="_gm_boost_types_8h" name="GmBoostTypes.h" local="no" imported="no">xmsgrid/geometry/GmBoostTypes.h</includes>
    <includes id="_gm_polygon_8t_8h" name="GmPolygon.t.h" local="no" imported="no">xmsgrid/geometry/GmPolygon.t.h</includes>
    <includes id="geoms_8h" name="geoms.h" local="no" imported="no">xmsgrid/geometry/geoms.h</includes>
    <includes id="geoms_8t_8h" name="geoms.t.h" local="no" imported="no">xmsgrid/geometry/geoms.t.h</includes>
    <class kind="class">xms::GmPolygonImpl</class>
    <class kind="class">GmPointInPolyTester_GmPolygon</class>
    <namespace>xms</namespace>
    <member kind="function" static="yes">
      <type>static double</type>
      <name>iDistanceToRing</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a99db03c7ac0beff008fd1d9b5795f7cb</anchor>
      <arglist>(const GmBstRing3d &amp;a_ring, const Pt3d &amp;a_pt)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>GmPolygon.h</name>
    <path>/home/conan/xmsgrid/geometry/</path>
    <filename>_gm_polygon_8h</filename>
    <class kind="class">xms::GmPolygon</class>
    <namespace>xms</namespace>
  </compound>
  <compound kind="file">
    <name>GmPolygon.t.h</name>
    <path>/home/conan/xmsgrid/geometry/</path>
    <filename>_gm_polygon_8t_8h</filename>
    <class kind="class">GmPolygonUnitTests</class>
    <class kind="class">GmPolygonIntermediateTests</class>
  </compound>
  <compound kind="file">
    <name>GmPolyLinePtRedistributer.cpp</name>
    <path>/home/conan/xmsgrid/geometry/</path>
    <filename>_gm_poly_line_pt_redistributer_8cpp</filename>
    <includes id="_gm_poly_line_pt_redistributer_8h" name="GmPolyLinePtRedistributer.h" local="no" imported="no">xmsgrid/geometry/GmPolyLinePtRedistributer.h</includes>
    <includes id="_gm_poly_line_pt_redistributer_8t_8h" name="GmPolyLinePtRedistributer.t.h" local="no" imported="no">xmsgrid/geometry/GmPolyLinePtRedistributer.t.h</includes>
    <includes id="geoms_8h" name="geoms.h" local="no" imported="no">xmsgrid/geometry/geoms.h</includes>
    <class kind="class">xms::GmPolyLinePtRedistributerImpl</class>
    <namespace>xms</namespace>
  </compound>
  <compound kind="file">
    <name>GmPolyLinePtRedistributer.h</name>
    <path>/home/conan/xmsgrid/geometry/</path>
    <filename>_gm_poly_line_pt_redistributer_8h</filename>
    <class kind="class">xms::GmPolyLinePtRedistributer</class>
    <namespace>xms</namespace>
  </compound>
  <compound kind="file">
    <name>GmPolyLinePtRedistributer.t.h</name>
    <path>/home/conan/xmsgrid/geometry/</path>
    <filename>_gm_poly_line_pt_redistributer_8t_8h</filename>
    <class kind="class">GmPolyLinePtRedistributerUnitTests</class>
  </compound>
  <compound kind="file">
    <name>GmPtSearch.cpp</name>
    <path>/home/conan/xmsgrid/geometry/</path>
    <filename>_gm_pt_search_8cpp</filename>
    <includes id="_gm_pt_search_8h" name="GmPtSearch.h" local="no" imported="no">xmsgrid/geometry/GmPtSearch.h</includes>
    <includes id="_gm_pt_search_8t_8h" name="GmPtSearch.t.h" local="no" imported="no">xmsgrid/geometry/GmPtSearch.t.h</includes>
    <class kind="class">xms::fSatisfies</class>
    <class kind="class">xms::idx_pt</class>
    <class kind="class">xms::GmPtSearchImpl</class>
    <namespace>xms</namespace>
    <member kind="define">
      <type>#define</type>
      <name>_TS_ASSERT_POINTS_FOUND</name>
      <anchorfile>_gm_pt_search_8cpp.html</anchorfile>
      <anchor>a8fbe8336b8c27d45710889fd77f4f9c6</anchor>
      <arglist>(a_file, a_line, a_required, a_optional, a_found)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>TS_ASSERT_POINTS_FOUND</name>
      <anchorfile>_gm_pt_search_8cpp.html</anchorfile>
      <anchor>ab1484d89355833010a52b160bb7f1e64</anchor>
      <arglist>(a_required, a_optional, a_found)</arglist>
    </member>
    <member kind="typedef">
      <type>bg::model::box&lt; bPt &gt;</type>
      <name>box</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>af3aa99ee2ee766e1f9c1480f8f4fa2f8</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>size_t</type>
      <name>value</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ac246bb2df10f44751d78d40e43d88da2</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>bgi::quadratic&lt; 8 &gt;</type>
      <name>qRtree</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a528acc66ce7a7889c76de85b6d5d5a23</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BOOST_GEOMETRY_REGISTER_POINT_3D</name>
      <anchorfile>_gm_pt_search_8cpp.html</anchorfile>
      <anchor>a1c1e59c4b2db3b2f5756f01c668924bb</anchor>
      <arglist>(bPt, double, cs::cartesian, x, y, z)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>iGetPoints2</name>
      <anchorfile>_gm_pt_search_8cpp.html</anchorfile>
      <anchor>a63c7b825306d0e4094c4f4a7cfca60da</anchor>
      <arglist>(std::vector&lt; Pt3d &gt; &amp;a_pts, std::vector&lt; float &gt; &amp;a_scalar, std::vector&lt; Pt3d &gt; &amp;a_iPts)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>iAssertPointsFound</name>
      <anchorfile>_gm_pt_search_8cpp.html</anchorfile>
      <anchor>ad94d7d97e0ce5c2bd382b874e657391b</anchor>
      <arglist>(const char *a_file, int a_line, const std::vector&lt; int &gt; &amp;a_required, const std::vector&lt; int &gt; &amp;a_optional, const std::vector&lt; int &gt; &amp;a_found)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>iSetupPts</name>
      <anchorfile>_gm_pt_search_8cpp.html</anchorfile>
      <anchor>a5a1426a86969ec4ea6e1ebb3bddf6809</anchor>
      <arglist>(std::vector&lt; Pt3d &gt; &amp;pts, bool a_2d)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>iSetupPtsOctant</name>
      <anchorfile>_gm_pt_search_8cpp.html</anchorfile>
      <anchor>a5a5d4b2dca9706e51c1c427ce4f8d058</anchor>
      <arglist>(std::vector&lt; Pt3d &gt; &amp;pts)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>GmPtSearch.h</name>
    <path>/home/conan/xmsgrid/geometry/</path>
    <filename>_gm_pt_search_8h</filename>
    <class kind="class">xms::GmPtSearch</class>
    <namespace>xms</namespace>
  </compound>
  <compound kind="file">
    <name>GmPtSearch.t.h</name>
    <path>/home/conan/xmsgrid/geometry/</path>
    <filename>_gm_pt_search_8t_8h</filename>
    <class kind="class">PtSearchUnitTests</class>
  </compound>
  <compound kind="file">
    <name>GmTriSearch.cpp</name>
    <path>/home/conan/xmsgrid/geometry/</path>
    <filename>_gm_tri_search_8cpp</filename>
    <includes id="_gm_tri_search_8h" name="GmTriSearch.h" local="no" imported="no">xmsgrid/geometry/GmTriSearch.h</includes>
    <includes id="_gm_boost_types_8h" name="GmBoostTypes.h" local="no" imported="no">xmsgrid/geometry/GmBoostTypes.h</includes>
    <includes id="geoms_8h" name="geoms.h" local="no" imported="no">xmsgrid/geometry/geoms.h</includes>
    <includes id="_gm_pt_search_8h" name="GmPtSearch.h" local="no" imported="no">xmsgrid/geometry/GmPtSearch.h</includes>
    <includes id="_gm_tri_search_8t_8h" name="GmTriSearch.t.h" local="no" imported="no">xmsgrid/geometry/GmTriSearch.t.h</includes>
    <includes id="_tr_tin_8h" name="TrTin.h" local="no" imported="no">xmsgrid/triangulate/TrTin.h</includes>
    <includes id="_tr_tin_8t_8h" name="TrTin.t.h" local="no" imported="no">xmsgrid/triangulate/TrTin.t.h</includes>
    <class kind="class">xms::idx_tri</class>
    <class kind="struct">xms::BarycentricVals</class>
    <class kind="class">xms::GmTriSearchImpl</class>
    <namespace>xms</namespace>
    <member kind="define">
      <type>#define</type>
      <name>BARYTOL</name>
      <anchorfile>_gm_tri_search_8cpp.html</anchorfile>
      <anchor>a3dc37a63219351ec125b2545bbdcdda3</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>iCartToBary</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>af5d39c8118d6484eca6f5dc22cfe082a</anchor>
      <arglist>(const Pt3d &amp;a_pt1, const Pt3d &amp;a_pt2, const Pt3d &amp;a_pt3, BarycentricVals &amp;a_b)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>iGetBarycentricCoords</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a4e909346571623b3e32310fd0877dea6</anchor>
      <arglist>(const Pt3d &amp;a_p, BarycentricVals &amp;a_b, Pt3d &amp;weights)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>GmTriSearch.h</name>
    <path>/home/conan/xmsgrid/geometry/</path>
    <filename>_gm_tri_search_8h</filename>
    <class kind="class">xms::GmTriSearch</class>
    <namespace>xms</namespace>
  </compound>
  <compound kind="file">
    <name>GmTriSearch.t.h</name>
    <path>/home/conan/xmsgrid/geometry/</path>
    <filename>_gm_tri_search_8t_8h</filename>
    <class kind="class">TriSearchUnitTests</class>
  </compound>
  <compound kind="file">
    <name>matrix.cpp</name>
    <path>/home/conan/xmsgrid/matrices/</path>
    <filename>matrix_8cpp</filename>
    <includes id="matrix_8h" name="matrix.h" local="no" imported="no">xmsgrid/matrices/matrix.h</includes>
    <namespace>xms</namespace>
    <member kind="function">
      <type>int</type>
      <name>mxLUDecomp</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>abafef2cc31ff622207da56d429af5a54</anchor>
      <arglist>(double **mat, int n, int *indx, double *d)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>mxLUBcksub</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>af4f904018cc928a778a7167b13fee704</anchor>
      <arglist>(double **mat, int n, const int *indx, double *b)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>mxiLudcmp3</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a83378019fa1d29c6f64e692118946a30</anchor>
      <arglist>(double mat[3][3], int indx[3], double *d)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>mxiLubksb3</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a1417150425cc14d57c2749d4f55a2945</anchor>
      <arglist>(const double mat[3][3], const int indx[3], double b[3])</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>mxSolveNxN</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a6b98843e685aab775941c3b89baa1d05</anchor>
      <arglist>(double **A, double *x, double *b, int n)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>mxSolveBandedEquations</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a6db76770e358ca141899b2a7c49d0a4d</anchor>
      <arglist>(double **a, double *x, double *b, int numeqs, int halfbandwidth)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>mxSolve3x3</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>aeed277bbc30a62f34e143baf5e6b04d4</anchor>
      <arglist>(double A[3][3], double x[3], double b[3])</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>mxInvert4x4</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ac76184db2a6a79c7a900ccf094f2bc5d</anchor>
      <arglist>(const double matrix[4][4], double inv[4][4])</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>mxPointMult</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a5e1a072632bb9cbda8df1442f70aa79a</anchor>
      <arglist>(Pt3d *pt, const double ctm[4][4])</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>mxCopy4x4</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ad30f45f6b87cb251f568c5afd565ac0f</anchor>
      <arglist>(double copy[4][4], const double matrix[4][4])</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>mxIdent4x4</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a817c4c41acd08d13bfc16e7f2982b5c2</anchor>
      <arglist>(double matrix[4][4])</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>mxMult4x4</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a5af15ec8654dced904d8c0b5b1e0ec99</anchor>
      <arglist>(double product[4][4], const double matrix1[4][4], const double matrix2[4][4])</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>mxRotate4x4</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ab8a23ab457d1a300fee82511b9dcccad</anchor>
      <arglist>(double xrot, double yrot, double zrot, double rMatt[4][4])</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>mxTranslate4x4</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ad8e2621b9cbd6773239bd1c9ad604e0a</anchor>
      <arglist>(const Pt3d &amp;a_translation, double a_mx[4][4])</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>matrix.h</name>
    <path>/home/conan/xmsgrid/matrices/</path>
    <filename>matrix_8h</filename>
    <namespace>xms</namespace>
    <member kind="function">
      <type>int</type>
      <name>mxLUDecomp</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>abafef2cc31ff622207da56d429af5a54</anchor>
      <arglist>(double **mat, int n, int *indx, double *d)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>mxLUBcksub</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>af4f904018cc928a778a7167b13fee704</anchor>
      <arglist>(double **mat, int n, const int *indx, double *b)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>mxiLudcmp3</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a83378019fa1d29c6f64e692118946a30</anchor>
      <arglist>(double mat[3][3], int indx[3], double *d)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>mxiLubksb3</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a1417150425cc14d57c2749d4f55a2945</anchor>
      <arglist>(const double mat[3][3], const int indx[3], double b[3])</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>mxSolveNxN</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a6b98843e685aab775941c3b89baa1d05</anchor>
      <arglist>(double **A, double *x, double *b, int n)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>mxSolveBandedEquations</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a6db76770e358ca141899b2a7c49d0a4d</anchor>
      <arglist>(double **a, double *x, double *b, int numeqs, int halfbandwidth)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>mxSolve3x3</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>aeed277bbc30a62f34e143baf5e6b04d4</anchor>
      <arglist>(double A[3][3], double x[3], double b[3])</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>mxInvert4x4</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ac76184db2a6a79c7a900ccf094f2bc5d</anchor>
      <arglist>(const double matrix[4][4], double inv[4][4])</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>mxPointMult</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a5e1a072632bb9cbda8df1442f70aa79a</anchor>
      <arglist>(Pt3d *pt, const double ctm[4][4])</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>mxCopy4x4</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ad30f45f6b87cb251f568c5afd565ac0f</anchor>
      <arglist>(double copy[4][4], const double matrix[4][4])</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>mxIdent4x4</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a817c4c41acd08d13bfc16e7f2982b5c2</anchor>
      <arglist>(double matrix[4][4])</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>mxMult4x4</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a5af15ec8654dced904d8c0b5b1e0ec99</anchor>
      <arglist>(double product[4][4], const double matrix1[4][4], const double matrix2[4][4])</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>mxRotate4x4</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ab8a23ab457d1a300fee82511b9dcccad</anchor>
      <arglist>(double xrot, double yrot, double zrot, double rMatt[4][4])</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>mxTranslate4x4</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ad8e2621b9cbd6773239bd1c9ad604e0a</anchor>
      <arglist>(const Pt3d &amp;a_translation, double a_mx[4][4])</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>TrAutoFixFourTrianglePts.cpp</name>
    <path>/home/conan/xmsgrid/triangulate/detail/</path>
    <filename>_tr_auto_fix_four_triangle_pts_8cpp</filename>
    <includes id="_tr_auto_fix_four_triangle_pts_8h" name="TrAutoFixFourTrianglePts.h" local="no" imported="no">xmsgrid/triangulate/detail/TrAutoFixFourTrianglePts.h</includes>
    <includes id="_tr_tin_8h" name="TrTin.h" local="no" imported="no">xmsgrid/triangulate/TrTin.h</includes>
    <includes id="_tr_auto_fix_four_triangle_pts_8t_8h" name="TrAutoFixFourTrianglePts.t.h" local="no" imported="no">xmsgrid/triangulate/detail/TrAutoFixFourTrianglePts.t.h</includes>
    <includes id="_tr_triangulator_points_8h" name="TrTriangulatorPoints.h" local="no" imported="no">xmsgrid/triangulate/TrTriangulatorPoints.h</includes>
    <class kind="class">xms::TrAutoFixFourTrianglePtsImpl</class>
    <namespace>xms</namespace>
  </compound>
  <compound kind="file">
    <name>TrAutoFixFourTrianglePts.h</name>
    <path>/home/conan/xmsgrid/triangulate/detail/</path>
    <filename>_tr_auto_fix_four_triangle_pts_8h</filename>
    <class kind="class">xms::TrAutoFixFourTrianglePts</class>
    <namespace>xms</namespace>
  </compound>
  <compound kind="file">
    <name>TrAutoFixFourTrianglePts.t.h</name>
    <path>/home/conan/xmsgrid/triangulate/detail/</path>
    <filename>_tr_auto_fix_four_triangle_pts_8t_8h</filename>
    <class kind="class">TrAutoFixFourTrianglePtsUnitTests</class>
  </compound>
  <compound kind="file">
    <name>triangulate.cpp</name>
    <path>/home/conan/xmsgrid/triangulate/detail/</path>
    <filename>triangulate_8cpp</filename>
    <includes id="triangulate_8h" name="triangulate.h" local="no" imported="no">xmsgrid/triangulate/detail/triangulate.h</includes>
    <includes id="_tr_triangulator_8h" name="TrTriangulator.h" local="no" imported="no">xmsgrid/triangulate/TrTriangulator.h</includes>
    <namespace>xms</namespace>
    <member kind="function">
      <type>bool</type>
      <name>trTriangulateIt</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ae7e3768a7e434634406ea7ee25bc0648</anchor>
      <arglist>(TrTriangulator &amp;a_Client)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>triangulate.h</name>
    <path>/home/conan/xmsgrid/triangulate/detail/</path>
    <filename>triangulate_8h</filename>
    <namespace>xms</namespace>
    <member kind="function">
      <type>bool</type>
      <name>trTriangulateIt</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ae7e3768a7e434634406ea7ee25bc0648</anchor>
      <arglist>(TrTriangulator &amp;a_Client)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>TrOuterTriangleDeleter.cpp</name>
    <path>/home/conan/xmsgrid/triangulate/detail/</path>
    <filename>_tr_outer_triangle_deleter_8cpp</filename>
    <includes id="_tr_outer_triangle_deleter_8h" name="TrOuterTriangleDeleter.h" local="no" imported="no">xmsgrid/triangulate/detail/TrOuterTriangleDeleter.h</includes>
    <includes id="_tr_tin_8h" name="TrTin.h" local="no" imported="no">xmsgrid/triangulate/TrTin.h</includes>
    <includes id="triangles_8h" name="triangles.h" local="no" imported="no">xmsgrid/triangulate/triangles.h</includes>
    <includes id="_tr_outer_triangle_deleter_8t_8h" name="TrOuterTriangleDeleter.t.h" local="no" imported="no">xmsgrid/triangulate/detail/TrOuterTriangleDeleter.t.h</includes>
    <includes id="_tr_tin_8t_8h" name="TrTin.t.h" local="no" imported="no">xmsgrid/triangulate/TrTin.t.h</includes>
    <class kind="class">xms::TrOuterTriangleDeleterImpl</class>
    <namespace>xms</namespace>
  </compound>
  <compound kind="file">
    <name>TrOuterTriangleDeleter.h</name>
    <path>/home/conan/xmsgrid/triangulate/detail/</path>
    <filename>_tr_outer_triangle_deleter_8h</filename>
    <class kind="class">xms::TrOuterTriangleDeleter</class>
    <namespace>xms</namespace>
  </compound>
  <compound kind="file">
    <name>TrOuterTriangleDeleter.t.h</name>
    <path>/home/conan/xmsgrid/triangulate/detail/</path>
    <filename>_tr_outer_triangle_deleter_8t_8h</filename>
    <class kind="class">TrOuterTriangleDeleterUnitTests</class>
  </compound>
  <compound kind="file">
    <name>TrBreaklineAdder.cpp</name>
    <path>/home/conan/xmsgrid/triangulate/</path>
    <filename>_tr_breakline_adder_8cpp</filename>
    <includes id="_tr_breakline_adder_8h" name="TrBreaklineAdder.h" local="no" imported="no">xmsgrid/triangulate/TrBreaklineAdder.h</includes>
    <includes id="geoms_8h" name="geoms.h" local="no" imported="no">xmsgrid/geometry/geoms.h</includes>
    <includes id="_gm_boost_types_8h" name="GmBoostTypes.h" local="no" imported="no">xmsgrid/geometry/GmBoostTypes.h</includes>
    <includes id="_gm_pt_search_8h" name="GmPtSearch.h" local="no" imported="no">xmsgrid/geometry/GmPtSearch.h</includes>
    <includes id="_gm_multi_poly_intersector_8h" name="GmMultiPolyIntersector.h" local="no" imported="no">xmsgrid/geometry/GmMultiPolyIntersector.h</includes>
    <includes id="_gm_multi_poly_intersection_sorter_terse_8h" name="GmMultiPolyIntersectionSorterTerse.h" local="no" imported="no">xmsgrid/geometry/GmMultiPolyIntersectionSorterTerse.h</includes>
    <includes id="triangles_8h" name="triangles.h" local="no" imported="no">xmsgrid/triangulate/triangles.h</includes>
    <includes id="_tr_tin_8h" name="TrTin.h" local="no" imported="no">xmsgrid/triangulate/TrTin.h</includes>
    <includes id="_tr_breakline_adder_8t_8h" name="TrBreaklineAdder.t.h" local="no" imported="no">xmsgrid/triangulate/TrBreaklineAdder.t.h</includes>
    <includes id="_tr_triangulator_points_8h" name="TrTriangulatorPoints.h" local="no" imported="no">xmsgrid/triangulate/TrTriangulatorPoints.h</includes>
    <includes id="_tr_tin_8t_8h" name="TrTin.t.h" local="no" imported="no">xmsgrid/triangulate/TrTin.t.h</includes>
    <class kind="struct">xms::edgerecord</class>
    <class kind="class">xms::TrBreaklineAdderImpl</class>
    <namespace>xms</namespace>
    <member kind="typedef">
      <type>std::vector&lt; edgerecord &gt;</type>
      <name>VecEdge</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a7541b74c2b86c70e57e863b57304bdcc</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>TrBreaklineAdder.h</name>
    <path>/home/conan/xmsgrid/triangulate/</path>
    <filename>_tr_breakline_adder_8h</filename>
    <class kind="class">xms::TrBreaklineAdder</class>
    <namespace>xms</namespace>
  </compound>
  <compound kind="file">
    <name>TrBreaklineAdder.t.h</name>
    <path>/home/conan/xmsgrid/triangulate/</path>
    <filename>_tr_breakline_adder_8t_8h</filename>
    <class kind="class">TrBreaklineAdderUnitTests</class>
  </compound>
  <compound kind="file">
    <name>triangles.cpp</name>
    <path>/home/conan/xmsgrid/triangulate/</path>
    <filename>triangles_8cpp</filename>
    <includes id="geoms_8h" name="geoms.h" local="no" imported="no">xmsgrid/geometry/geoms.h</includes>
    <includes id="triangles_8h" name="triangles.h" local="no" imported="no">xmsgrid/triangulate/triangles.h</includes>
    <namespace>xms</namespace>
    <member kind="function">
      <type>double</type>
      <name>trArea</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a3ab795fd4e5d3ebcedb00230e73392dc</anchor>
      <arglist>(const Pt3d &amp;a_pt1, const Pt3d &amp;a_pt2, const Pt3d &amp;a_pt3)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>trBuildGridTrianglePolys</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a176da2f77435c7baf90a2507e5841362</anchor>
      <arglist>(int rows, int cols, VecPt3d &amp;a_points, VecInt2d &amp;a_polys)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>trBuildGridPolys</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a5c5d655291110f3f2ff13fa3a733b689</anchor>
      <arglist>(int rows, int cols, VecPt3d &amp;pts, VecInt2d &amp;polys)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>triangles.h</name>
    <path>/home/conan/xmsgrid/triangulate/</path>
    <filename>triangles_8h</filename>
    <namespace>xms</namespace>
    <member kind="function">
      <type>double</type>
      <name>trArea</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a3ab795fd4e5d3ebcedb00230e73392dc</anchor>
      <arglist>(const Pt3d &amp;a_pt1, const Pt3d &amp;a_pt2, const Pt3d &amp;a_pt3)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>trBuildGridPolys</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a5c5d655291110f3f2ff13fa3a733b689</anchor>
      <arglist>(int rows, int cols, VecPt3d &amp;pts, VecInt2d &amp;polys)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>trBuildGridTrianglePolys</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a176da2f77435c7baf90a2507e5841362</anchor>
      <arglist>(int rows, int cols, VecPt3d &amp;a_points, VecInt2d &amp;a_polys)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>trIncrementIndex</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a3522d0baa47f21d6355b87f5c7173260</anchor>
      <arglist>(int i)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>trDecrementIndex</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a5b6d3f9afa689aac0cfcdf1097ae62cf</anchor>
      <arglist>(int i)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>TrTin.cpp</name>
    <path>/home/conan/xmsgrid/triangulate/</path>
    <filename>_tr_tin_8cpp</filename>
    <includes id="_tr_tin_8h" name="TrTin.h" local="no" imported="no">xmsgrid/triangulate/TrTin.h</includes>
    <includes id="geoms_8h" name="geoms.h" local="no" imported="no">xmsgrid/geometry/geoms.h</includes>
    <includes id="triangles_8h" name="triangles.h" local="no" imported="no">xmsgrid/triangulate/triangles.h</includes>
    <includes id="_tr_tin_8t_8h" name="TrTin.t.h" local="no" imported="no">xmsgrid/triangulate/TrTin.t.h</includes>
    <includes id="_tr_triangulator_points_8h" name="TrTriangulatorPoints.h" local="no" imported="no">xmsgrid/triangulate/TrTriangulatorPoints.h</includes>
    <class kind="class">xms::TrTinImpl</class>
    <namespace>xms</namespace>
    <member kind="function">
      <type></type>
      <name>BOOST_CLASS_EXPORT</name>
      <anchorfile>_tr_tin_8cpp.html</anchorfile>
      <anchor>a7244a742c140134d2c13f8714f1af76c</anchor>
      <arglist>(xms::TrTinImpl)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>trRenumberOnDelete</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a66eebefbcd706efc80c4ca1cdceb05d3</anchor>
      <arglist>(const SetInt &amp;a_deleting, VecInt &amp;a_vec)</arglist>
    </member>
    <member kind="function">
      <type>BSHP&lt; TrTin &gt;</type>
      <name>trBuildTestTin</name>
      <anchorfile>_tr_tin_8cpp.html</anchorfile>
      <anchor>a0c925ae34b78a1dac382e317833dbec1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>BSHP&lt; TrTin &gt;</type>
      <name>trBuildTestTin2</name>
      <anchorfile>_tr_tin_8cpp.html</anchorfile>
      <anchor>a9ce87b91b5012a999ddbc87ad8820029</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>BSHP&lt; TrTin &gt;</type>
      <name>trBuildTestTin6</name>
      <anchorfile>_tr_tin_8cpp.html</anchorfile>
      <anchor>a60fe241cf170639ac6a6c0d2b342821c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>BSHP&lt; TrTin &gt;</type>
      <name>trBuildTestTin7</name>
      <anchorfile>_tr_tin_8cpp.html</anchorfile>
      <anchor>a068ae1567736bd473d51b406c9ade227</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>BSHP&lt; TrTin &gt;</type>
      <name>trBuildTestTin8</name>
      <anchorfile>_tr_tin_8cpp.html</anchorfile>
      <anchor>a310ee9097c8a7ff014c12621714077fa</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>BSHP&lt; TrTin &gt;</type>
      <name>trBuildTestTin9</name>
      <anchorfile>_tr_tin_8cpp.html</anchorfile>
      <anchor>a386420cc59bd28676fe65c2b57f17127</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>TrTin.h</name>
    <path>/home/conan/xmsgrid/triangulate/</path>
    <filename>_tr_tin_8h</filename>
    <class kind="class">xms::TrTin</class>
    <namespace>xms</namespace>
    <member kind="function">
      <type>void</type>
      <name>trRenumberOnDelete</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a66eebefbcd706efc80c4ca1cdceb05d3</anchor>
      <arglist>(const SetInt &amp;a_deleting, VecInt &amp;a_vec)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>TrTin.t.h</name>
    <path>/home/conan/xmsgrid/triangulate/</path>
    <filename>_tr_tin_8t_8h</filename>
    <class kind="class">TrTinUnitTests</class>
    <namespace>xms</namespace>
    <member kind="function">
      <type>boost::shared_ptr&lt; xms::TrTin &gt;</type>
      <name>trBuildTestTin</name>
      <anchorfile>_tr_tin_8t_8h.html</anchorfile>
      <anchor>af323a53c7f6fbba3a645dcd33a8ac450</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>boost::shared_ptr&lt; xms::TrTin &gt;</type>
      <name>trBuildTestTin2</name>
      <anchorfile>_tr_tin_8t_8h.html</anchorfile>
      <anchor>a1eda7b31829ff99f4d5b15c2188a997b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>boost::shared_ptr&lt; xms::TrTin &gt;</type>
      <name>trBuildTestTin6</name>
      <anchorfile>_tr_tin_8t_8h.html</anchorfile>
      <anchor>ac4f1ed3125ba5cd229fc1d04bb9fefe3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>boost::shared_ptr&lt; xms::TrTin &gt;</type>
      <name>trBuildTestTin7</name>
      <anchorfile>_tr_tin_8t_8h.html</anchorfile>
      <anchor>ae9477606ec0f20782f1bc2dbe94213d4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>boost::shared_ptr&lt; xms::TrTin &gt;</type>
      <name>trBuildTestTin8</name>
      <anchorfile>_tr_tin_8t_8h.html</anchorfile>
      <anchor>a1492a1c9c30f02dc6dccad115531126b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>boost::shared_ptr&lt; xms::TrTin &gt;</type>
      <name>trBuildTestTin9</name>
      <anchorfile>_tr_tin_8t_8h.html</anchorfile>
      <anchor>a36ccf1dbfe10bcde1d187234d0e8e619</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>TrTriangulator.cpp</name>
    <path>/home/conan/xmsgrid/triangulate/</path>
    <filename>_tr_triangulator_8cpp</filename>
    <includes id="_tr_triangulator_8h" name="TrTriangulator.h" local="no" imported="no">xmsgrid/triangulate/TrTriangulator.h</includes>
    <includes id="triangulate_8h" name="triangulate.h" local="no" imported="no">xmsgrid/triangulate/detail/triangulate.h</includes>
    <namespace>xms</namespace>
  </compound>
  <compound kind="file">
    <name>TrTriangulator.h</name>
    <path>/home/conan/xmsgrid/triangulate/</path>
    <filename>_tr_triangulator_8h</filename>
    <class kind="class">xms::TrTriangulator</class>
    <namespace>xms</namespace>
  </compound>
  <compound kind="file">
    <name>TrTriangulatorPoints.cpp</name>
    <path>/home/conan/xmsgrid/triangulate/</path>
    <filename>_tr_triangulator_points_8cpp</filename>
    <includes id="_tr_triangulator_points_8h" name="TrTriangulatorPoints.h" local="no" imported="no">xmsgrid/triangulate/TrTriangulatorPoints.h</includes>
    <includes id="geoms_8h" name="geoms.h" local="no" imported="no">xmsgrid/geometry/geoms.h</includes>
    <includes id="triangles_8h" name="triangles.h" local="no" imported="no">xmsgrid/triangulate/triangles.h</includes>
    <includes id="_tr_triangulator_points_8t_8h" name="TrTriangulatorPoints.t.h" local="no" imported="no">xmsgrid/triangulate/TrTriangulatorPoints.t.h</includes>
    <includes id="triangulate_8h" name="triangulate.h" local="no" imported="no">xmsgrid/triangulate/detail/triangulate.h</includes>
    <namespace>xms</namespace>
  </compound>
  <compound kind="file">
    <name>TrTriangulatorPoints.h</name>
    <path>/home/conan/xmsgrid/triangulate/</path>
    <filename>_tr_triangulator_points_8h</filename>
    <includes id="_tr_triangulator_8h" name="TrTriangulator.h" local="no" imported="no">xmsgrid/triangulate/TrTriangulator.h</includes>
    <class kind="class">xms::TrTriangulatorPoints</class>
    <namespace>xms</namespace>
  </compound>
  <compound kind="file">
    <name>TrTriangulatorPoints.t.h</name>
    <path>/home/conan/xmsgrid/triangulate/</path>
    <filename>_tr_triangulator_points_8t_8h</filename>
    <class kind="class">TrTriangulatorPointsUnitTests</class>
  </compound>
  <compound kind="file">
    <name>XmGeometry.cpp</name>
    <path>/home/conan/xmsgrid/ugrid/detail/</path>
    <filename>_xm_geometry_8cpp</filename>
    <includes id="_xm_geometry_8h" name="XmGeometry.h" local="no" imported="no">xmsgrid/ugrid/detail/XmGeometry.h</includes>
    <includes id="geoms_8h" name="geoms.h" local="no" imported="no">xmsgrid/geometry/geoms.h</includes>
    <includes id="_xm_u_grid_8h" name="XmUGrid.h" local="no" imported="no">xmsgrid/ugrid/XmUGrid.h</includes>
    <includes id="_xm_u_grid_utils_8h" name="XmUGridUtils.h" local="no" imported="no">xmsgrid/ugrid/XmUGridUtils.h</includes>
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
      <anchor>a00d2ba2d5a847f521e5ef4b8760673b1</anchor>
      <arglist>(const std::vector&lt; int &gt; &amp;a_points, std::shared_ptr&lt; XmUGrid &gt; a_ugrid)</arglist>
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
      <anchor>a00d2ba2d5a847f521e5ef4b8760673b1</anchor>
      <arglist>(const std::vector&lt; int &gt; &amp;a_points, std::shared_ptr&lt; XmUGrid &gt; a_ugrid)</arglist>
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
    <includes id="geoms_8h" name="geoms.h" local="no" imported="no">xmsgrid/geometry/geoms.h</includes>
    <includes id="_xm_geometry_8h" name="XmGeometry.h" local="no" imported="no">xmsgrid/ugrid/detail/XmGeometry.h</includes>
    <includes id="_xm_u_grid_8t_8h" name="XmUGrid.t.h" local="no" imported="no">xmsgrid/ugrid/XmUGrid.t.h</includes>
    <class kind="class">xms::XmUGrid::Impl</class>
    <namespace>xms</namespace>
    <member kind="function">
      <type>std::shared_ptr&lt; XmUGrid &gt;</type>
      <name>TEST_XmUGrid1Left90Tri</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a20c36b8eb6452f2d1875b0247c14d31e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::shared_ptr&lt; XmUGrid &gt;</type>
      <name>TEST_XmUGridSimpleQuad</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a3e1912532173494a8d160ac5d82a392a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::shared_ptr&lt; XmUGrid &gt;</type>
      <name>TEST_XmUGrid2dLinear</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ac0c59b6cb5d5cec46437e61eedec1084</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::shared_ptr&lt; XmUGrid &gt;</type>
      <name>TEST_XmUGrid3dLinear</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ae7d1f554521e831a8f9ccaaf416437bd</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::shared_ptr&lt; XmUGrid &gt;</type>
      <name>TEST_XmUGridHexagonalPolyhedron</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a6a1e92629d5aea37e379767e4eee20ab</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::shared_ptr&lt; xms::XmUGrid &gt;</type>
      <name>TEST_XmUBuildQuadUGrid</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a752ee43c318c0d776a4922f2a7fad2d7</anchor>
      <arglist>(int a_rows, int a_cols)</arglist>
    </member>
    <member kind="function">
      <type>std::shared_ptr&lt; xms::XmUGrid &gt;</type>
      <name>TEST_XmUBuildQuadUGrid</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a73b81475327580e61ccc7ab6501404b6</anchor>
      <arglist>(int a_rows, int a_cols, const xms::Pt3d &amp;a_origin)</arglist>
    </member>
    <member kind="function">
      <type>std::shared_ptr&lt; xms::XmUGrid &gt;</type>
      <name>TEST_XmUBuildHexahedronUgrid</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a47daf228f70ea022c26d3f75f7d81f6f</anchor>
      <arglist>(int a_rows, int a_cols, int a_lays)</arglist>
    </member>
    <member kind="function">
      <type>std::shared_ptr&lt; xms::XmUGrid &gt;</type>
      <name>TEST_XmUBuildHexahedronUgrid</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>aa8a343a956e47e7e1cf02e519692e457</anchor>
      <arglist>(int a_rows, int a_cols, int a_lays, const xms::Pt3d &amp;a_origin)</arglist>
    </member>
    <member kind="function">
      <type>std::shared_ptr&lt; xms::XmUGrid &gt;</type>
      <name>TEST_XmUBuildPolyhedronUgrid</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ab1b974ca6051709e16e6bfe888bb5ac0</anchor>
      <arglist>(int a_rows, int a_cols, int a_lays)</arglist>
    </member>
    <member kind="function">
      <type>std::shared_ptr&lt; xms::XmUGrid &gt;</type>
      <name>TEST_XmUBuildPolyhedronUgrid</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a4d3536ed21ff9fe41c5f6be1214efa8b</anchor>
      <arglist>(int a_rows, int a_cols, int a_lays, const xms::Pt3d &amp;a_origin)</arglist>
    </member>
    <member kind="function">
      <type>std::shared_ptr&lt; xms::XmUGrid &gt;</type>
      <name>TEST_XmUBuild3DChevronUgrid</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>adb5e5abe3d445643a032581a904d3be1</anchor>
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
      <type>std::shared_ptr&lt; XmUGrid &gt;</type>
      <name>TEST_XmUGrid1Left90Tri</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a20c36b8eb6452f2d1875b0247c14d31e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::shared_ptr&lt; XmUGrid &gt;</type>
      <name>TEST_XmUGridSimpleQuad</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a3e1912532173494a8d160ac5d82a392a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::shared_ptr&lt; XmUGrid &gt;</type>
      <name>TEST_XmUGrid2dLinear</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ac0c59b6cb5d5cec46437e61eedec1084</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::shared_ptr&lt; XmUGrid &gt;</type>
      <name>TEST_XmUGrid3dLinear</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ae7d1f554521e831a8f9ccaaf416437bd</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::shared_ptr&lt; XmUGrid &gt;</type>
      <name>TEST_XmUGridHexagonalPolyhedron</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a6a1e92629d5aea37e379767e4eee20ab</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::shared_ptr&lt; xms::XmUGrid &gt;</type>
      <name>TEST_XmUBuildQuadUGrid</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a752ee43c318c0d776a4922f2a7fad2d7</anchor>
      <arglist>(int a_rows, int a_cols)</arglist>
    </member>
    <member kind="function">
      <type>std::shared_ptr&lt; xms::XmUGrid &gt;</type>
      <name>TEST_XmUBuildQuadUGrid</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a73b81475327580e61ccc7ab6501404b6</anchor>
      <arglist>(int a_rows, int a_cols, const xms::Pt3d &amp;a_origin)</arglist>
    </member>
    <member kind="function">
      <type>std::shared_ptr&lt; xms::XmUGrid &gt;</type>
      <name>TEST_XmUBuildHexahedronUgrid</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a47daf228f70ea022c26d3f75f7d81f6f</anchor>
      <arglist>(int a_rows, int a_cols, int a_lays)</arglist>
    </member>
    <member kind="function">
      <type>std::shared_ptr&lt; xms::XmUGrid &gt;</type>
      <name>TEST_XmUBuildHexahedronUgrid</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>aa8a343a956e47e7e1cf02e519692e457</anchor>
      <arglist>(int a_rows, int a_cols, int a_lays, const xms::Pt3d &amp;a_origin)</arglist>
    </member>
    <member kind="function">
      <type>std::shared_ptr&lt; xms::XmUGrid &gt;</type>
      <name>TEST_XmUBuildPolyhedronUgrid</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ab1b974ca6051709e16e6bfe888bb5ac0</anchor>
      <arglist>(int a_rows, int a_cols, int a_lays)</arglist>
    </member>
    <member kind="function">
      <type>std::shared_ptr&lt; xms::XmUGrid &gt;</type>
      <name>TEST_XmUBuildPolyhedronUgrid</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a4d3536ed21ff9fe41c5f6be1214efa8b</anchor>
      <arglist>(int a_rows, int a_cols, int a_lays, const xms::Pt3d &amp;a_origin)</arglist>
    </member>
    <member kind="function">
      <type>std::shared_ptr&lt; xms::XmUGrid &gt;</type>
      <name>TEST_XmUBuild3DChevronUgrid</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>adb5e5abe3d445643a032581a904d3be1</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>XmUGrid.t.h</name>
    <path>/home/conan/xmsgrid/ugrid/</path>
    <filename>_xm_u_grid_8t_8h</filename>
    <class kind="class">XmUGridUnitTests</class>
    <namespace>xms</namespace>
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
      <type>std::shared_ptr&lt; XmUGrid &gt;</type>
      <name>XmReadUGridFromAsciiFile</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ab9624f114b63071fd74602311eab24d4</anchor>
      <arglist>(const std::string &amp;a_filePath)</arglist>
    </member>
    <member kind="function">
      <type>std::shared_ptr&lt; XmUGrid &gt;</type>
      <name>XmReadUGridFromStream</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a567badd7a8307c065bb1d98fc00c6d64</anchor>
      <arglist>(std::istream &amp;a_inStream)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>XmWriteUGridToAsciiFile</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a2cb05982d077fe5a46ecf41202723d14</anchor>
      <arglist>(std::shared_ptr&lt; XmUGrid &gt; a_ugrid, const std::string &amp;a_filePath)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>XmWriteUGridToStream</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a5c12f5e36da024c353837d9558c6c9c8</anchor>
      <arglist>(std::shared_ptr&lt; XmUGrid &gt; a_ugrid, std::ostream &amp;a_outStream)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>XmWriteUGridToStream</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a089a787adbb806cc55d8751b8ffb3a8d</anchor>
      <arglist>(const XmUGrid &amp;a_ugrid, std::ostream &amp;a_outStream, bool a_binary)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>XmUGridUtils.h</name>
    <path>/home/conan/xmsgrid/ugrid/</path>
    <filename>_xm_u_grid_utils_8h</filename>
    <namespace>xms</namespace>
    <member kind="function">
      <type>std::shared_ptr&lt; XmUGrid &gt;</type>
      <name>XmReadUGridFromAsciiFile</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ab9624f114b63071fd74602311eab24d4</anchor>
      <arglist>(const std::string &amp;a_filePath)</arglist>
    </member>
    <member kind="function">
      <type>std::shared_ptr&lt; XmUGrid &gt;</type>
      <name>XmReadUGridFromStream</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a567badd7a8307c065bb1d98fc00c6d64</anchor>
      <arglist>(std::istream &amp;a_inStream)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>XmWriteUGridToAsciiFile</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a2cb05982d077fe5a46ecf41202723d14</anchor>
      <arglist>(std::shared_ptr&lt; XmUGrid &gt; a_ugrid, const std::string &amp;a_filePath)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>XmWriteUGridToStream</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a5c12f5e36da024c353837d9558c6c9c8</anchor>
      <arglist>(std::shared_ptr&lt; XmUGrid &gt; a_ugrid, std::ostream &amp;a_outStream)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>XmWriteUGridToStream</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a089a787adbb806cc55d8751b8ffb3a8d</anchor>
      <arglist>(const XmUGrid &amp;a_ugrid, std::ostream &amp;a_outStream, bool a_binary)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>XmUGridUtils.t.h</name>
    <path>/home/conan/xmsgrid/ugrid/</path>
    <filename>_xm_u_grid_utils_8t_8h</filename>
    <class kind="class">XmUGridUtilsTests</class>
  </compound>
  <compound kind="struct">
    <name>xms::BarycentricVals</name>
    <filename>structxms_1_1_barycentric_vals.html</filename>
    <member kind="variable">
      <type>Pt3d</type>
      <name>orig</name>
      <anchorfile>structxms_1_1_barycentric_vals.html</anchorfile>
      <anchor>ae88c2de12a80a534faf78addd416f38c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>double</type>
      <name>coef</name>
      <anchorfile>structxms_1_1_barycentric_vals.html</anchorfile>
      <anchor>aebed3bc5a1c410ee503863972249b13b</anchor>
      <arglist>[6]</arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>dir</name>
      <anchorfile>structxms_1_1_barycentric_vals.html</anchorfile>
      <anchor>acb8bf1c437d7b0141c565730738b297a</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>xms::edgerecord</name>
    <filename>structxms_1_1edgerecord.html</filename>
    <member kind="variable">
      <type>int</type>
      <name>pt1</name>
      <anchorfile>structxms_1_1edgerecord.html</anchorfile>
      <anchor>a628ba61db2c8c725a8b5a603620f35cb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>pt2</name>
      <anchorfile>structxms_1_1edgerecord.html</anchorfile>
      <anchor>a37a472bed46ccd144b62eb755ad8770e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Pt3d</type>
      <name>intersection</name>
      <anchorfile>structxms_1_1edgerecord.html</anchorfile>
      <anchor>a34b4f43309c69d116fad70ebe6cf0dfb</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>xms::fSatisfies</name>
    <filename>classxms_1_1f_satisfies.html</filename>
    <member kind="function">
      <type></type>
      <name>fSatisfies</name>
      <anchorfile>classxms_1_1f_satisfies.html</anchorfile>
      <anchor>ab363650297804f81ac7f6fa1179b6bc0</anchor>
      <arglist>(size_t a_nVals)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator()</name>
      <anchorfile>classxms_1_1f_satisfies.html</anchorfile>
      <anchor>aba3fb24836d4e09c49644fd394fe191e</anchor>
      <arglist>(value const &amp;a_) const</arglist>
    </member>
    <member kind="variable">
      <type>DynBitset</type>
      <name>m_bits</name>
      <anchorfile>classxms_1_1f_satisfies.html</anchorfile>
      <anchor>abb625b439183cff97cde9dede033f7aa</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>GeomsXmsngIntermediateTests</name>
    <filename>class_geoms_xmsng_intermediate_tests.html</filename>
    <member kind="function">
      <type>void</type>
      <name>test_gmPointInPolygon2D</name>
      <anchorfile>class_geoms_xmsng_intermediate_tests.html</anchorfile>
      <anchor>a06e3aae3a26f0358d21daf3ae69ccdf2</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>GeomsXmsngUnitTests</name>
    <filename>class_geoms_xmsng_unit_tests.html</filename>
    <member kind="function">
      <type>void</type>
      <name>test_gmComputePolygonCentroid</name>
      <anchorfile>class_geoms_xmsng_unit_tests.html</anchorfile>
      <anchor>a55f61c470b2c64974edeedda4523d500</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>test_gmComputeCentroid</name>
      <anchorfile>class_geoms_xmsng_unit_tests.html</anchorfile>
      <anchor>a6221ee23de11b511e5920baa908cb6a3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>test_gmPointInPolygon2D_Speed</name>
      <anchorfile>class_geoms_xmsng_unit_tests.html</anchorfile>
      <anchor>a3c7aa86a05eb6c65edbfd2739adae675</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testConvexHull</name>
      <anchorfile>class_geoms_xmsng_unit_tests.html</anchorfile>
      <anchor>ac45c185deb053fda8149b2d72dffce5f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testDoLineSegmentsCross</name>
      <anchorfile>class_geoms_xmsng_unit_tests.html</anchorfile>
      <anchor>ad8f57e79cd7c87606b3da6b142fcf0e6</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>xms::GmExtents2d</name>
    <filename>classxms_1_1_gm_extents2d.html</filename>
    <member kind="function">
      <type></type>
      <name>GmExtents2d</name>
      <anchorfile>classxms_1_1_gm_extents2d.html</anchorfile>
      <anchor>a7713120ed10fdf972a7d9cd4727695e7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>GmExtents2d</name>
      <anchorfile>classxms_1_1_gm_extents2d.html</anchorfile>
      <anchor>ac6ca00863adaed8c44fdf229ba55cee2</anchor>
      <arglist>(const GmExtents3d &amp;a_extents)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>GmExtents2d</name>
      <anchorfile>classxms_1_1_gm_extents2d.html</anchorfile>
      <anchor>a41f7becb48eb6566a0d8446c0af744e8</anchor>
      <arglist>(const Pt2d &amp;a_min, const Pt2d &amp;a_max)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>GmExtents2d</name>
      <anchorfile>classxms_1_1_gm_extents2d.html</anchorfile>
      <anchor>a59954fe5dcff4393c789b9b5310d3b00</anchor>
      <arglist>(const Pt3d &amp;a_min, const Pt3d &amp;a_max)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~GmExtents2d</name>
      <anchorfile>classxms_1_1_gm_extents2d.html</anchorfile>
      <anchor>a199a9513a66ab4e8ca031c93a60502ce</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>operator+=</name>
      <anchorfile>classxms_1_1_gm_extents2d.html</anchorfile>
      <anchor>ae42c798434698c97fdd26298ac26f6e0</anchor>
      <arglist>(const GmExtents2d &amp;a_rhs)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>AddToExtents</name>
      <anchorfile>classxms_1_1_gm_extents2d.html</anchorfile>
      <anchor>a961a392986a503fd2a08b2dcd4c19644</anchor>
      <arglist>(const Pt3d &amp;pt)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Add</name>
      <anchorfile>classxms_1_1_gm_extents2d.html</anchorfile>
      <anchor>ae5cc44c6efd560195817f1d1d32cc17c</anchor>
      <arglist>(ItrType a_begin, ItrType a_end)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>IsValid</name>
      <anchorfile>classxms_1_1_gm_extents2d.html</anchorfile>
      <anchor>a8808cc09d89e82f4ab38c6fc649a026d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>Overlap</name>
      <anchorfile>classxms_1_1_gm_extents2d.html</anchorfile>
      <anchor>a78e80fd3786ba85959a85df3896c5c13</anchor>
      <arglist>(const GmExtents2d &amp;a_b) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Clear</name>
      <anchorfile>classxms_1_1_gm_extents2d.html</anchorfile>
      <anchor>a60780f3b3471ce34744412fed1938f47</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>GetExtents</name>
      <anchorfile>classxms_1_1_gm_extents2d.html</anchorfile>
      <anchor>a12db96218f2b4f7c1ff5242ba8bab3d7</anchor>
      <arglist>(double *a_MinX, double *a_MaxX, double *a_MinY, double *a_MaxY)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>GetExtents</name>
      <anchorfile>classxms_1_1_gm_extents2d.html</anchorfile>
      <anchor>abdadfa5471353d9186adf9118790a95a</anchor>
      <arglist>(Pt3d &amp;a_dMin, Pt3d &amp;a_dMax)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>GetMinX</name>
      <anchorfile>classxms_1_1_gm_extents2d.html</anchorfile>
      <anchor>a77bf9cf316f868751b5beb1266a2b75f</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>GetMaxX</name>
      <anchorfile>classxms_1_1_gm_extents2d.html</anchorfile>
      <anchor>ab46d3290c8986ddaf08562d0fad62caf</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>GetMinY</name>
      <anchorfile>classxms_1_1_gm_extents2d.html</anchorfile>
      <anchor>a2149daf43a184dd06ade5b9c78d4645b</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>GetMaxY</name>
      <anchorfile>classxms_1_1_gm_extents2d.html</anchorfile>
      <anchor>aa8f7bfbeaba83b82e321f72c562addca</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>Pt2d</type>
      <name>GetMin</name>
      <anchorfile>classxms_1_1_gm_extents2d.html</anchorfile>
      <anchor>af1491a3798bcb600e4cd47f1ef333d2f</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>Pt2d</type>
      <name>GetMax</name>
      <anchorfile>classxms_1_1_gm_extents2d.html</anchorfile>
      <anchor>ada4543fe674250cab6f1e582c6f091af</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Set</name>
      <anchorfile>classxms_1_1_gm_extents2d.html</anchorfile>
      <anchor>a65c98975328fe846704c7fc91a006e1e</anchor>
      <arglist>(const Pt2d &amp;a_min, const Pt2d &amp;a_max)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>serialize</name>
      <anchorfile>classxms_1_1_gm_extents2d.html</anchorfile>
      <anchor>aa7a591f9d935ef8aea0402d746c56fc9</anchor>
      <arglist>(Archive &amp;archive, const unsigned int version)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>SetTolerance</name>
      <anchorfile>classxms_1_1_gm_extents2d.html</anchorfile>
      <anchor>af91bf63e31dc46c63a0165d267f7ad19</anchor>
      <arglist>(double a_Tol)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static double</type>
      <name>GetTolerance</name>
      <anchorfile>classxms_1_1_gm_extents2d.html</anchorfile>
      <anchor>a7db9964a1b49f1bd8e3003a5c592dbc0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Pt2d</type>
      <name>m_min</name>
      <anchorfile>classxms_1_1_gm_extents2d.html</anchorfile>
      <anchor>aff08e09f489359e779cc9a068fed293a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Pt2d</type>
      <name>m_max</name>
      <anchorfile>classxms_1_1_gm_extents2d.html</anchorfile>
      <anchor>aee80084ccb1fc4d9aa069c232678ff0d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected" static="yes">
      <type>static double</type>
      <name>m_tolerance</name>
      <anchorfile>classxms_1_1_gm_extents2d.html</anchorfile>
      <anchor>a96ea5046f0d2a697ab852e2e6e37b0de</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>xms::GmExtents3d</name>
    <filename>classxms_1_1_gm_extents3d.html</filename>
    <member kind="function">
      <type></type>
      <name>GmExtents3d</name>
      <anchorfile>classxms_1_1_gm_extents3d.html</anchorfile>
      <anchor>aee049dcde88efdf2266b9ddac3700626</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>GmExtents3d</name>
      <anchorfile>classxms_1_1_gm_extents3d.html</anchorfile>
      <anchor>aee5d872568e8585f8e24db8678c5a246</anchor>
      <arglist>(const GmExtents2d &amp;a_extents)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>GmExtents3d</name>
      <anchorfile>classxms_1_1_gm_extents3d.html</anchorfile>
      <anchor>a1954ff9b989d3e13f414e142dd5404d1</anchor>
      <arglist>(const Pt3d &amp;a_min, const Pt3d &amp;a_max)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>GmExtents3d</name>
      <anchorfile>classxms_1_1_gm_extents3d.html</anchorfile>
      <anchor>a11ec30b976bd5ddfde9a9ecdf3248702</anchor>
      <arglist>(const Pt2d &amp;a_min, const Pt2d &amp;a_max)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>operator+=</name>
      <anchorfile>classxms_1_1_gm_extents3d.html</anchorfile>
      <anchor>ac0a55b7e31742d3dfff48cbc321ccca2</anchor>
      <arglist>(const GmExtents3d &amp;a_rhs)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>AddToExtents</name>
      <anchorfile>classxms_1_1_gm_extents3d.html</anchorfile>
      <anchor>a1f41c66ac6b67c60982044093ada302e</anchor>
      <arglist>(const Pt3d &amp;pt)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>IsValid</name>
      <anchorfile>classxms_1_1_gm_extents3d.html</anchorfile>
      <anchor>a078c56a4d36e3db9fd038082418964fc</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>Overlap</name>
      <anchorfile>classxms_1_1_gm_extents3d.html</anchorfile>
      <anchor>a5eab9f9515caa8e15d344bca95d3a783</anchor>
      <arglist>(GmExtents3d &amp;a_b) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Clear</name>
      <anchorfile>classxms_1_1_gm_extents3d.html</anchorfile>
      <anchor>af7b8f4955c9068c0853354ab1f34f297</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>IsPointWithin</name>
      <anchorfile>classxms_1_1_gm_extents3d.html</anchorfile>
      <anchor>a902eb81668d4f9cf77dd6ddc558b40a7</anchor>
      <arglist>(const Pt3d &amp;pt) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>GetExtents</name>
      <anchorfile>classxms_1_1_gm_extents3d.html</anchorfile>
      <anchor>a1afb775183a2020c66e937d9d8df5ede</anchor>
      <arglist>(double *a_MinX, double *a_MaxX, double *a_MinY, double *a_MaxY, double *a_MinZ, double *a_MaxZ) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>GetExtents</name>
      <anchorfile>classxms_1_1_gm_extents3d.html</anchorfile>
      <anchor>ac77ae8b5172628c3266bc774951c29d6</anchor>
      <arglist>(Pt3d &amp;a_dMin, Pt3d &amp;a_dMax) const</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>GetMinX</name>
      <anchorfile>classxms_1_1_gm_extents3d.html</anchorfile>
      <anchor>a9a3f36f9da0e09ba773590d6ff36da60</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>GetMaxX</name>
      <anchorfile>classxms_1_1_gm_extents3d.html</anchorfile>
      <anchor>ab5827886d151465fbb902eff452bb978</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>GetMinY</name>
      <anchorfile>classxms_1_1_gm_extents3d.html</anchorfile>
      <anchor>ac7a8ae51c57f09c4f8487d851fcf31a8</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>GetMaxY</name>
      <anchorfile>classxms_1_1_gm_extents3d.html</anchorfile>
      <anchor>ad932aba529c8cfb6bbe73e2f9eaa6f49</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>GetMinZ</name>
      <anchorfile>classxms_1_1_gm_extents3d.html</anchorfile>
      <anchor>a4863256f0eed7d7b6b71b08e1178c8de</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>GetMaxZ</name>
      <anchorfile>classxms_1_1_gm_extents3d.html</anchorfile>
      <anchor>a3ef27d65b4d3931937f647486059fc02</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>Pt3d</type>
      <name>GetMin</name>
      <anchorfile>classxms_1_1_gm_extents3d.html</anchorfile>
      <anchor>a608b517961d6745d92f15d6278a8e5e4</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>Pt3d</type>
      <name>GetMax</name>
      <anchorfile>classxms_1_1_gm_extents3d.html</anchorfile>
      <anchor>ad9558c795fc8b7350567f178e27eca8a</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Set</name>
      <anchorfile>classxms_1_1_gm_extents3d.html</anchorfile>
      <anchor>a79314a735a92ef987b6412fcf404beea</anchor>
      <arglist>(const Pt3d &amp;a_min, const Pt3d &amp;a_max)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>serialize</name>
      <anchorfile>classxms_1_1_gm_extents3d.html</anchorfile>
      <anchor>a0b0221f18c9e5c9262606c3ac89aff67</anchor>
      <arglist>(Archive &amp;archive, const unsigned int version)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>SetTolerance</name>
      <anchorfile>classxms_1_1_gm_extents3d.html</anchorfile>
      <anchor>a6b4934250f1e3b40181595cf45ec52cf</anchor>
      <arglist>(double a_Tol)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static double</type>
      <name>GetTolerance</name>
      <anchorfile>classxms_1_1_gm_extents3d.html</anchorfile>
      <anchor>accc7b2a33b04d17b07af0db56df8b328</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Pt3d</type>
      <name>m_min</name>
      <anchorfile>classxms_1_1_gm_extents3d.html</anchorfile>
      <anchor>af9468191aa5196a5013db9c0e14b1d71</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Pt3d</type>
      <name>m_max</name>
      <anchorfile>classxms_1_1_gm_extents3d.html</anchorfile>
      <anchor>ad4235d1ff4b577bcfad2dbfe0524afdd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected" static="yes">
      <type>static double</type>
      <name>m_tolerance</name>
      <anchorfile>classxms_1_1_gm_extents3d.html</anchorfile>
      <anchor>a7a1ee26cd395da7b0d36e605571f8ea5</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>GmExtents3dUnitTests</name>
    <filename>class_gm_extents3d_unit_tests.html</filename>
    <member kind="function">
      <type>void</type>
      <name>testSinglePt</name>
      <anchorfile>class_gm_extents3d_unit_tests.html</anchorfile>
      <anchor>adedf8a67b016f09f4e95672841cead5c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testMultiplePts</name>
      <anchorfile>class_gm_extents3d_unit_tests.html</anchorfile>
      <anchor>a1c9c9993c46633c84692110933f34e41</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testNoPts</name>
      <anchorfile>class_gm_extents3d_unit_tests.html</anchorfile>
      <anchor>ac38da518f4b94df3f4cd1cf49d847a5e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testOverlapping</name>
      <anchorfile>class_gm_extents3d_unit_tests.html</anchorfile>
      <anchor>aa3e1b36f174ffc0f1607c3cb31b8c4d0</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>xms::GmMultiPolyIntersectionSorter</name>
    <filename>classxms_1_1_gm_multi_poly_intersection_sorter.html</filename>
  </compound>
  <compound kind="class">
    <name>xms::GmMultiPolyIntersectionSorterTerse</name>
    <filename>classxms_1_1_gm_multi_poly_intersection_sorter_terse.html</filename>
    <base>xms::GmMultiPolyIntersectionSorter</base>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>Sort</name>
      <anchorfile>classxms_1_1_gm_multi_poly_intersection_sorter_terse.html</anchorfile>
      <anchor>aab32ba927a9062f1c95c5a2e1bedb62d</anchor>
      <arglist>(GmMultiPolyIntersectorData &amp;a_data, std::vector&lt; int &gt; &amp;polyids, std::vector&lt; double &gt; &amp;tvalues, std::vector&lt; Pt3d &gt; &amp;a_pts, double a_tol) override</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>RemoveCornerTouches</name>
      <anchorfile>classxms_1_1_gm_multi_poly_intersection_sorter_terse.html</anchorfile>
      <anchor>ac86036c81726449c8121c1a05fd73db3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>RemoveDuplicateEdges</name>
      <anchorfile>classxms_1_1_gm_multi_poly_intersection_sorter_terse.html</anchorfile>
      <anchor>a1ef5deaea8e21cd99a88376758bc6c64</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>SwapAdjacents</name>
      <anchorfile>classxms_1_1_gm_multi_poly_intersection_sorter_terse.html</anchorfile>
      <anchor>a230088635ebb08581d8701911068be0a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>IntersectionsToPolyIdsAndTValuesFor2</name>
      <anchorfile>classxms_1_1_gm_multi_poly_intersection_sorter_terse.html</anchorfile>
      <anchor>a6b310a7f9545a6629edbc8250eefcb24</anchor>
      <arglist>(std::vector&lt; int &gt; &amp;polyids, std::vector&lt; double &gt; &amp;tvalues, std::vector&lt; Pt3d &gt; &amp;a_pts) const</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>IntersectionsToPolyIdsAndTValuesFor3OrMore</name>
      <anchorfile>classxms_1_1_gm_multi_poly_intersection_sorter_terse.html</anchorfile>
      <anchor>ae3c73099c3b23d94416fc14601b91ee5</anchor>
      <arglist>(std::vector&lt; int &gt; &amp;polyids, std::vector&lt; double &gt; &amp;tvalues, std::vector&lt; Pt3d &gt; &amp;a_pts) const</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>IntersectionsToPolyIdsAndTValues</name>
      <anchorfile>classxms_1_1_gm_multi_poly_intersection_sorter_terse.html</anchorfile>
      <anchor>a9cd8f532b56f11e5600f2910051daaff</anchor>
      <arglist>(std::vector&lt; int &gt; &amp;polyids, std::vector&lt; double &gt; &amp;tvalues, std::vector&lt; Pt3d &gt; &amp;a_pts) const</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>FixArrays</name>
      <anchorfile>classxms_1_1_gm_multi_poly_intersection_sorter_terse.html</anchorfile>
      <anchor>af5a86f40ed9c1962c81950074ac9a598</anchor>
      <arglist>(std::vector&lt; int &gt; &amp;polyids, std::vector&lt; double &gt; &amp;tvalues, std::vector&lt; Pt3d &gt; &amp;a_pts) const</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>AddToPolyIdsAndTValues</name>
      <anchorfile>classxms_1_1_gm_multi_poly_intersection_sorter_terse.html</anchorfile>
      <anchor>a0cb9995b0273c1953428f420f12eaffb</anchor>
      <arglist>(const ix &amp;a_ix, std::vector&lt; int &gt; &amp;polyids, std::vector&lt; double &gt; &amp;tvalues, std::vector&lt; Pt3d &gt; &amp;a_pts) const</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>FindPreviousNextNeither</name>
      <anchorfile>classxms_1_1_gm_multi_poly_intersection_sorter_terse.html</anchorfile>
      <anchor>ab8b8a8153fae932c73a83a639f8ac7ad</anchor>
      <arglist>(const std::vector&lt; int &gt; &amp;tChange, const int idx, std::vector&lt; int &gt; *inPrev, std::vector&lt; int &gt; *inNext, std::vector&lt; int &gt; *inNeither) const</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>Swap</name>
      <anchorfile>classxms_1_1_gm_multi_poly_intersection_sorter_terse.html</anchorfile>
      <anchor>a484addfe624bb88f1980496ccb922692</anchor>
      <arglist>(int a, int b)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>FindWhereTValuesChange</name>
      <anchorfile>classxms_1_1_gm_multi_poly_intersection_sorter_terse.html</anchorfile>
      <anchor>ab19ab5f34e20a4cce4d5ef18e6e914f3</anchor>
      <arglist>(std::vector&lt; int &gt; &amp;tChange) const</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>GmMultiPolyIntersectorData *</type>
      <name>m_d</name>
      <anchorfile>classxms_1_1_gm_multi_poly_intersection_sorter_terse.html</anchorfile>
      <anchor>a7bacf816a4c3b4eae33cd5a36007655a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>double</type>
      <name>m_tol</name>
      <anchorfile>classxms_1_1_gm_multi_poly_intersection_sorter_terse.html</anchorfile>
      <anchor>afe1b7c2e44e9d9837c446666d4995d48</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>xms::GmMultiPolyIntersector</name>
    <filename>classxms_1_1_gm_multi_poly_intersector.html</filename>
    <member kind="function" static="yes">
      <type>static boost::shared_ptr&lt; GmMultiPolyIntersector &gt;</type>
      <name>New</name>
      <anchorfile>classxms_1_1_gm_multi_poly_intersector.html</anchorfile>
      <anchor>a225f2e577e682f6fbd603fa56dce2253</anchor>
      <arglist>(const std::vector&lt; Pt3d &gt; &amp;a_points, const std::vector&lt; std::vector&lt; int &gt; &gt; &amp;a_polys, boost::shared_ptr&lt; GmMultiPolyIntersectionSorter &gt; a_sorter, int a_startingId=1)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>GmMultiPolyIntersector2IntermediateTests</name>
    <filename>class_gm_multi_poly_intersector2_intermediate_tests.html</filename>
    <member kind="function">
      <type>void</type>
      <name>testLargeNumPolys</name>
      <anchorfile>class_gm_multi_poly_intersector2_intermediate_tests.html</anchorfile>
      <anchor>af3432feef6f5f052b418fb4e8aeb5868</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testLargeNumPolysAndSegments</name>
      <anchorfile>class_gm_multi_poly_intersector2_intermediate_tests.html</anchorfile>
      <anchor>accf890a54adf98d863387d7d6c714109</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>xms::GmMultiPolyIntersectorData</name>
    <filename>structxms_1_1_gm_multi_poly_intersector_data.html</filename>
    <member kind="variable">
      <type>std::vector&lt; Pt3d &gt;</type>
      <name>m_points</name>
      <anchorfile>structxms_1_1_gm_multi_poly_intersector_data.html</anchorfile>
      <anchor>aafe89c90dca39c321b5a71af95256c2c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::vector&lt; std::vector&lt; int &gt; &gt;</type>
      <name>m_polys</name>
      <anchorfile>structxms_1_1_gm_multi_poly_intersector_data.html</anchorfile>
      <anchor>a4b6f906b82daa91ae96450abf8071509</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::set&lt; int &gt;</type>
      <name>m_polys1</name>
      <anchorfile>structxms_1_1_gm_multi_poly_intersector_data.html</anchorfile>
      <anchor>a34a35f421f49e17ec2e1f3a2b4d678a8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::set&lt; int &gt;</type>
      <name>m_polys2</name>
      <anchorfile>structxms_1_1_gm_multi_poly_intersector_data.html</anchorfile>
      <anchor>aca483d0445e27801f910b40c93d22c96</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::vector&lt; ix &gt;</type>
      <name>m_ixs</name>
      <anchorfile>structxms_1_1_gm_multi_poly_intersector_data.html</anchorfile>
      <anchor>a3e30a6edc79fdb107f575508b14e5ea5</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>xms::GmMultiPolyIntersectorImpl</name>
    <filename>classxms_1_1_gm_multi_poly_intersector_impl.html</filename>
    <base>xms::GmMultiPolyIntersector</base>
    <member kind="function">
      <type></type>
      <name>GmMultiPolyIntersectorImpl</name>
      <anchorfile>classxms_1_1_gm_multi_poly_intersector_impl.html</anchorfile>
      <anchor>ac5a0b775408588b9d96a228d7185f5cd</anchor>
      <arglist>(const VecPt3d &amp;a_points, const VecInt2d &amp;a_polys, BSHP&lt; GmMultiPolyIntersectionSorter &gt; a_sorter, int a_startingId=1)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>SetQuery</name>
      <anchorfile>classxms_1_1_gm_multi_poly_intersector_impl.html</anchorfile>
      <anchor>ad44f26ecf4069c3406c27806dabf13f8</anchor>
      <arglist>(GmMultiPolyIntersectorQueryEnum a_query) override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>TraverseLineSegment</name>
      <anchorfile>classxms_1_1_gm_multi_poly_intersector_impl.html</anchorfile>
      <anchor>ada393f1506eb1026d0997c9b88578a8d</anchor>
      <arglist>(double a_x1, double a_y1, double a_x2, double a_y2, VecInt &amp;a_polyIds, VecDbl &amp;a_tValues) override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>TraverseLineSegment</name>
      <anchorfile>classxms_1_1_gm_multi_poly_intersector_impl.html</anchorfile>
      <anchor>a2fb6caeb7f6fc67201502cbf92753092</anchor>
      <arglist>(double a_x1, double a_y1, double a_x2, double a_y2, VecInt &amp;a_polyIds) override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>TraverseLineSegment</name>
      <anchorfile>classxms_1_1_gm_multi_poly_intersector_impl.html</anchorfile>
      <anchor>a32ca6f99b230794b6373411ec4e4d28b</anchor>
      <arglist>(double a_x1, double a_y1, double a_x2, double a_y2, VecInt &amp;a_polyIds, VecPt3d &amp;a_pts) override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>TraverseLineSegment</name>
      <anchorfile>classxms_1_1_gm_multi_poly_intersector_impl.html</anchorfile>
      <anchor>a98a84ed115d65b313f0f97ec16c91a4e</anchor>
      <arglist>(double a_x1, double a_y1, double a_x2, double a_y2, VecInt &amp;a_polyIds, VecDbl &amp;a_tValues, VecPt3d &amp;a_pts) override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>PolygonFromPoint</name>
      <anchorfile>classxms_1_1_gm_multi_poly_intersector_impl.html</anchorfile>
      <anchor>a704347586a5fa15a9f66fd088f8d7353</anchor>
      <arglist>(const Pt3d &amp;a_pt) override</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>RemoveDuplicateTValues</name>
      <anchorfile>classxms_1_1_gm_multi_poly_intersector_impl.html</anchorfile>
      <anchor>a38545696a626fedc3d6c98e6cfc59e4f</anchor>
      <arglist>(VecInt &amp;a_polyIds, VecDbl &amp;a_tValues, VecPt3d &amp;a_pts)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>CalculateBuffer</name>
      <anchorfile>classxms_1_1_gm_multi_poly_intersector_impl.html</anchorfile>
      <anchor>a535aad59183701eae8532bcb4c2ed2f0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>BufferTheBox</name>
      <anchorfile>classxms_1_1_gm_multi_poly_intersector_impl.html</anchorfile>
      <anchor>ae6d9d3489cc6f4ffad6bbdbaefadddf5</anchor>
      <arglist>(GmBstBox3d &amp;box) const</arglist>
    </member>
    <member kind="function" protection="private">
      <type>GmBstPoly3d &amp;</type>
      <name>GetBoostPoly</name>
      <anchorfile>classxms_1_1_gm_multi_poly_intersector_impl.html</anchorfile>
      <anchor>a9205979073697853ffdc62c0e5a87cac</anchor>
      <arglist>(int a_polyIdx)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>BuildBoostPoly</name>
      <anchorfile>classxms_1_1_gm_multi_poly_intersector_impl.html</anchorfile>
      <anchor>a34751018aeada5236adb5c55eb2e7c07</anchor>
      <arglist>(int a_polyIdx, GmBstPoly3d &amp;a_boostPoly) const</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>BuildRTree</name>
      <anchorfile>classxms_1_1_gm_multi_poly_intersector_impl.html</anchorfile>
      <anchor>af1174b0ddef285f93ba48e5aaadd6bbb</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>CreateLine</name>
      <anchorfile>classxms_1_1_gm_multi_poly_intersector_impl.html</anchorfile>
      <anchor>a3c3d8a9dd135301536427efe7e08a21a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>GetPolysForPoint</name>
      <anchorfile>classxms_1_1_gm_multi_poly_intersector_impl.html</anchorfile>
      <anchor>aeeca34e061a08d03164142275666c15d</anchor>
      <arglist>(Pt3d pt, SetInt &amp;poly)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>EnsureEndPointsRepresented</name>
      <anchorfile>classxms_1_1_gm_multi_poly_intersector_impl.html</anchorfile>
      <anchor>a0d3c6c5b4daa721d5fb2edec53d28dbb</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>IntersectEachPolyWithLine</name>
      <anchorfile>classxms_1_1_gm_multi_poly_intersector_impl.html</anchorfile>
      <anchor>ae78756aa2652d524131bb6259534df04</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>ComputeTValues</name>
      <anchorfile>classxms_1_1_gm_multi_poly_intersector_impl.html</anchorfile>
      <anchor>ab1525012537a7fe8d974de6c1c7c1080</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>SortIntersections</name>
      <anchorfile>classxms_1_1_gm_multi_poly_intersector_impl.html</anchorfile>
      <anchor>ad8a8d896823f5f70b3ffc250b453434c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>OffsetPolyIds</name>
      <anchorfile>classxms_1_1_gm_multi_poly_intersector_impl.html</anchorfile>
      <anchor>ad7d468b9c1de82c05149fc6bf429dab1</anchor>
      <arglist>(VecInt &amp;polyIds) const</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>PointsOnSegment</name>
      <anchorfile>classxms_1_1_gm_multi_poly_intersector_impl.html</anchorfile>
      <anchor>a425a8860d5df3720cee68cdd32f1bb9f</anchor>
      <arglist>(const GmBstPoly3d &amp;a_poly, const GmBstLine3d &amp;a_line, std::deque&lt; Pt3d &gt; &amp;a_output)</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>GmMultiPolyIntersectorData</type>
      <name>m_d</name>
      <anchorfile>classxms_1_1_gm_multi_poly_intersector_impl.html</anchorfile>
      <anchor>a6deb7afa1a20058c93d83ef912ee890a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>Pt3d</type>
      <name>m_pt1</name>
      <anchorfile>classxms_1_1_gm_multi_poly_intersector_impl.html</anchorfile>
      <anchor>aab0dadb74472f2aa11c1f2838c5b18b2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>Pt3d</type>
      <name>m_pt2</name>
      <anchorfile>classxms_1_1_gm_multi_poly_intersector_impl.html</anchorfile>
      <anchor>a165515a3528656302865abe9b060d052</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>RtreeBox *</type>
      <name>m_rtree</name>
      <anchorfile>classxms_1_1_gm_multi_poly_intersector_impl.html</anchorfile>
      <anchor>a79c692d08b0a79ba2823a92a98402d04</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>GmBstLine3d</type>
      <name>m_line</name>
      <anchorfile>classxms_1_1_gm_multi_poly_intersector_impl.html</anchorfile>
      <anchor>ac8c9bc9edcf78e66b2b19b429fdd748b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>double</type>
      <name>m_buffer</name>
      <anchorfile>classxms_1_1_gm_multi_poly_intersector_impl.html</anchorfile>
      <anchor>aece8a77964a59bb161d95a8d0f36e598</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>int</type>
      <name>m_startingId</name>
      <anchorfile>classxms_1_1_gm_multi_poly_intersector_impl.html</anchorfile>
      <anchor>af8d56b114f4feb8359cccfb904429dd8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>std::vector&lt; GmBstPoly3d &gt;</type>
      <name>m_boostPolys</name>
      <anchorfile>classxms_1_1_gm_multi_poly_intersector_impl.html</anchorfile>
      <anchor>a0bf794580c7158c6295b62dc6d359308</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>BSHP&lt; GmMultiPolyIntersectionSorter &gt;</type>
      <name>m_sorter</name>
      <anchorfile>classxms_1_1_gm_multi_poly_intersector_impl.html</anchorfile>
      <anchor>aee888465df13dc924b99fc607071223e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>GmMultiPolyIntersectorQueryEnum</type>
      <name>m_query</name>
      <anchorfile>classxms_1_1_gm_multi_poly_intersector_impl.html</anchorfile>
      <anchor>ae25a886c347f59cc97cdd4d09d0f2ecf</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>GmMultiPolyIntersectorUnitTests</name>
    <filename>class_gm_multi_poly_intersector_unit_tests.html</filename>
    <member kind="function">
      <type>void</type>
      <name>test1OutOut</name>
      <anchorfile>class_gm_multi_poly_intersector_unit_tests.html</anchorfile>
      <anchor>a9bc1d133022a08f727d0c14d5ffc8c5a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>test1OutIn</name>
      <anchorfile>class_gm_multi_poly_intersector_unit_tests.html</anchorfile>
      <anchor>a7d9bca80f562c2dae434abaea557dd24</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>test1InOut</name>
      <anchorfile>class_gm_multi_poly_intersector_unit_tests.html</anchorfile>
      <anchor>a50cb9ccfc4935064d0a2506841d57a23</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>test1InIn</name>
      <anchorfile>class_gm_multi_poly_intersector_unit_tests.html</anchorfile>
      <anchor>aa5baa916d12383da4dbe7877af0a956e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>test1OnOn</name>
      <anchorfile>class_gm_multi_poly_intersector_unit_tests.html</anchorfile>
      <anchor>a47ee3ffbab44e06feb633d5b15724cee</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>test1OnIn</name>
      <anchorfile>class_gm_multi_poly_intersector_unit_tests.html</anchorfile>
      <anchor>a056d2db6357740fadb0a5a2a6aa6219a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>test1InOn</name>
      <anchorfile>class_gm_multi_poly_intersector_unit_tests.html</anchorfile>
      <anchor>ae3cc91a790599b69ab905e1a24936abf</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>test1OutOn</name>
      <anchorfile>class_gm_multi_poly_intersector_unit_tests.html</anchorfile>
      <anchor>a0e343e3648cc68f7cb30e4a51df5dd0d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>test1OnOut</name>
      <anchorfile>class_gm_multi_poly_intersector_unit_tests.html</anchorfile>
      <anchor>a04ad35a38490fd441747be17c7d06898</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>test1EdgeInIn</name>
      <anchorfile>class_gm_multi_poly_intersector_unit_tests.html</anchorfile>
      <anchor>a846dba3e81acd4b114248e867c5fbf17</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>test1EdgePtPt</name>
      <anchorfile>class_gm_multi_poly_intersector_unit_tests.html</anchorfile>
      <anchor>ac3df56c4be517755e6e1a5080a4a35e8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>test1EdgeOutOut</name>
      <anchorfile>class_gm_multi_poly_intersector_unit_tests.html</anchorfile>
      <anchor>af82efa33125fcbf89662cf346daa4bcf</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>test1EdgeOutIn</name>
      <anchorfile>class_gm_multi_poly_intersector_unit_tests.html</anchorfile>
      <anchor>a78fd1c347b853f365d36bde2a1164208</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>test1EdgeInOut</name>
      <anchorfile>class_gm_multi_poly_intersector_unit_tests.html</anchorfile>
      <anchor>ac81760456d448049194f1b0b1dd06d92</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>test1OutPt</name>
      <anchorfile>class_gm_multi_poly_intersector_unit_tests.html</anchorfile>
      <anchor>aa9d101ac50cce7df1ad548edbe558d25</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>test1OutPtOut</name>
      <anchorfile>class_gm_multi_poly_intersector_unit_tests.html</anchorfile>
      <anchor>ae32cf8a87707053e10443d7373795450</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>test1AllOut</name>
      <anchorfile>class_gm_multi_poly_intersector_unit_tests.html</anchorfile>
      <anchor>a25a7d6c55a01f1877e31fed5f09cebe5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>test1PtIn</name>
      <anchorfile>class_gm_multi_poly_intersector_unit_tests.html</anchorfile>
      <anchor>a97587425f176cde3ee00ce7828987a85</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>test1InPt</name>
      <anchorfile>class_gm_multi_poly_intersector_unit_tests.html</anchorfile>
      <anchor>ae42d2fac80e867f29ba2b22c3a005ab6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>test2OnOn</name>
      <anchorfile>class_gm_multi_poly_intersector_unit_tests.html</anchorfile>
      <anchor>abc34eb869b0922314dae22aa2a164f7f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>test2InOn</name>
      <anchorfile>class_gm_multi_poly_intersector_unit_tests.html</anchorfile>
      <anchor>aa6ebb5373b16aea4f77837dd3f3b7091</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>test2OnIn</name>
      <anchorfile>class_gm_multi_poly_intersector_unit_tests.html</anchorfile>
      <anchor>ab02b7de0c41d00d91983178ed2cc1ba9</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>test2OutOut</name>
      <anchorfile>class_gm_multi_poly_intersector_unit_tests.html</anchorfile>
      <anchor>aa41bf64c185e5d23e7fb2081cb4cf315</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>test2OutIn</name>
      <anchorfile>class_gm_multi_poly_intersector_unit_tests.html</anchorfile>
      <anchor>a6d4b387f9a12ed3a3e4992b4f11d6ef6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>test2InOut</name>
      <anchorfile>class_gm_multi_poly_intersector_unit_tests.html</anchorfile>
      <anchor>ac6698da2b89c2110c5044f65faf474e5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>test2InIn</name>
      <anchorfile>class_gm_multi_poly_intersector_unit_tests.html</anchorfile>
      <anchor>aba39959cfea6f33feb66b19ae4864cc1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>test2InPt</name>
      <anchorfile>class_gm_multi_poly_intersector_unit_tests.html</anchorfile>
      <anchor>aab29e414a3c777ea2e6a6ab6d4842c5f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>test2PtIn</name>
      <anchorfile>class_gm_multi_poly_intersector_unit_tests.html</anchorfile>
      <anchor>a9666cf0a6ed89edd4c3e36739516c54b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>test2InEdgePt</name>
      <anchorfile>class_gm_multi_poly_intersector_unit_tests.html</anchorfile>
      <anchor>a00fe4843d3173ee19212b6d58d61f8fb</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testCorners</name>
      <anchorfile>class_gm_multi_poly_intersector_unit_tests.html</anchorfile>
      <anchor>a5097eece91dfafe0e1a1d111bfb1f7cb</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testQuadCorners</name>
      <anchorfile>class_gm_multi_poly_intersector_unit_tests.html</anchorfile>
      <anchor>abdef87477e39a8084bb0319a5578870c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testQuadCornersBug12396</name>
      <anchorfile>class_gm_multi_poly_intersector_unit_tests.html</anchorfile>
      <anchor>af58b71d869e3258f7f863c4195f049f5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>test2InOutIn</name>
      <anchorfile>class_gm_multi_poly_intersector_unit_tests.html</anchorfile>
      <anchor>abc2aacee320789fcd0548cb3a9244afa</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testInsideToInside</name>
      <anchorfile>class_gm_multi_poly_intersector_unit_tests.html</anchorfile>
      <anchor>a72a7ad9e8759e3a4cf0b9c3675a64c3e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testOutsideToOutside</name>
      <anchorfile>class_gm_multi_poly_intersector_unit_tests.html</anchorfile>
      <anchor>a3fb7e8f8e878592caa011cc15e769587</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testTouchesVertex</name>
      <anchorfile>class_gm_multi_poly_intersector_unit_tests.html</anchorfile>
      <anchor>abe52de87107ad86a5af6cd0430952b5d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testTouchesEdge</name>
      <anchorfile>class_gm_multi_poly_intersector_unit_tests.html</anchorfile>
      <anchor>a679656ec0fe0368c1f25b35fc345ccca</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testAlongEdgesInsideToInside</name>
      <anchorfile>class_gm_multi_poly_intersector_unit_tests.html</anchorfile>
      <anchor>ac913a37cc74a0b363c4b4d5647dc194d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testAlongEdgesOutsideToOutside</name>
      <anchorfile>class_gm_multi_poly_intersector_unit_tests.html</anchorfile>
      <anchor>ac5d233ab7cbde987ca5f5ad5e6f37c97</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testEdgeThroughOppositeVertexAtAngle</name>
      <anchorfile>class_gm_multi_poly_intersector_unit_tests.html</anchorfile>
      <anchor>af54ca54fb1ec6a2495e9fb0fb127aaa3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testStartAtEdgeThroughAdjacent</name>
      <anchorfile>class_gm_multi_poly_intersector_unit_tests.html</anchorfile>
      <anchor>a89bac4f7c03a3d6ffaad8d7776613bcf</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testInsideToEdgeThenThroughAdjacent</name>
      <anchorfile>class_gm_multi_poly_intersector_unit_tests.html</anchorfile>
      <anchor>a704778a5c7167a957eeba146415930f2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testEndAtEdgeFromAdjacent</name>
      <anchorfile>class_gm_multi_poly_intersector_unit_tests.html</anchorfile>
      <anchor>ae3b9191a3d4e3af3866b04c3458b778d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testSmsCase1</name>
      <anchorfile>class_gm_multi_poly_intersector_unit_tests.html</anchorfile>
      <anchor>aa22cd3c8a7facdc51f8767d8185bbb12</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testMap2MfBug</name>
      <anchorfile>class_gm_multi_poly_intersector_unit_tests.html</anchorfile>
      <anchor>a05ca020d15aa52adaeb42df71db2c748</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>GmPointInPolyTester_gmPointInPolygon2D</name>
    <filename>class_gm_point_in_poly_tester__gm_point_in_polygon2_d.html</filename>
    <base>GmPointInPolyUnitTests</base>
    <member kind="function">
      <type></type>
      <name>GmPointInPolyTester_gmPointInPolygon2D</name>
      <anchorfile>class_gm_point_in_poly_tester__gm_point_in_polygon2_d.html</anchorfile>
      <anchor>a139a56adbb9597d361b30e0ceb65905d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private" virtualness="virtual">
      <type>virtual void</type>
      <name>CheckPoint</name>
      <anchorfile>class_gm_point_in_poly_tester__gm_point_in_polygon2_d.html</anchorfile>
      <anchor>a49d08071fc94eaade3a90093804d1583</anchor>
      <arglist>(const xms::Pt3d &amp;a_pt) override</arglist>
    </member>
    <member kind="function" protection="private" virtualness="virtual">
      <type>virtual double</type>
      <name>MaxTime</name>
      <anchorfile>class_gm_point_in_poly_tester__gm_point_in_polygon2_d.html</anchorfile>
      <anchor>a922ad92f9b9b0fad1f3167b111abed16</anchor>
      <arglist>() override</arglist>
    </member>
    <member kind="function" protection="private">
      <type></type>
      <name>XM_DISALLOW_COPY_AND_ASSIGN</name>
      <anchorfile>class_gm_point_in_poly_tester__gm_point_in_polygon2_d.html</anchorfile>
      <anchor>a93106a8027d1f7a54029804e94a478c3</anchor>
      <arglist>(GmPointInPolyTester_gmPointInPolygon2D)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>GmPointInPolyTester_GmPolygon</name>
    <filename>class_gm_point_in_poly_tester___gm_polygon.html</filename>
    <base>GmPointInPolyUnitTests</base>
    <member kind="function">
      <type></type>
      <name>GmPointInPolyTester_GmPolygon</name>
      <anchorfile>class_gm_point_in_poly_tester___gm_polygon.html</anchorfile>
      <anchor>af73511361067f8a19790783068097aa9</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private" virtualness="virtual">
      <type>virtual void</type>
      <name>Setup</name>
      <anchorfile>class_gm_point_in_poly_tester___gm_polygon.html</anchorfile>
      <anchor>ac0cf4568292ffeb7626320453460a1ae</anchor>
      <arglist>() override</arglist>
    </member>
    <member kind="function" protection="private" virtualness="virtual">
      <type>virtual void</type>
      <name>CheckPoint</name>
      <anchorfile>class_gm_point_in_poly_tester___gm_polygon.html</anchorfile>
      <anchor>a6266bdf8e4c1276bda6063a2c419576c</anchor>
      <arglist>(const xms::Pt3d &amp;a_pt) override</arglist>
    </member>
    <member kind="function" protection="private" virtualness="virtual">
      <type>virtual double</type>
      <name>MaxTime</name>
      <anchorfile>class_gm_point_in_poly_tester___gm_polygon.html</anchorfile>
      <anchor>a7c2b20442710d8f70394600de6fd9342</anchor>
      <arglist>() override</arglist>
    </member>
    <member kind="function" protection="private">
      <type></type>
      <name>XM_DISALLOW_COPY_AND_ASSIGN</name>
      <anchorfile>class_gm_point_in_poly_tester___gm_polygon.html</anchorfile>
      <anchor>a55c128adfb44a4c87abd9f00a9ebd806</anchor>
      <arglist>(GmPointInPolyTester_GmPolygon)</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>BSHP&lt; xms::GmPolygon &gt;</type>
      <name>m_poly</name>
      <anchorfile>class_gm_point_in_poly_tester___gm_polygon.html</anchorfile>
      <anchor>ab36a65f45d348e61c2c54700187523c3</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>GmPointInPolyUnitTests</name>
    <filename>class_gm_point_in_poly_unit_tests.html</filename>
    <member kind="function">
      <type></type>
      <name>GmPointInPolyUnitTests</name>
      <anchorfile>class_gm_point_in_poly_unit_tests.html</anchorfile>
      <anchor>a242ee9e55d08b8eab4105d7592bf1dd1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>DoTest</name>
      <anchorfile>class_gm_point_in_poly_unit_tests.html</anchorfile>
      <anchor>aad892797953c9679e60aacab95c59a27</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual void</type>
      <name>CheckPoint</name>
      <anchorfile>class_gm_point_in_poly_unit_tests.html</anchorfile>
      <anchor>a6c8f3ccf1f1fc9b26f4354bea316c6a2</anchor>
      <arglist>(const xms::Pt3d &amp;a_pt)=0</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual double</type>
      <name>MaxTime</name>
      <anchorfile>class_gm_point_in_poly_unit_tests.html</anchorfile>
      <anchor>ab3908f443552a3365b065a8c9a8cf0c9</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual void</type>
      <name>Setup</name>
      <anchorfile>class_gm_point_in_poly_unit_tests.html</anchorfile>
      <anchor>a4a90399854ed590bb00b89598880f443</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual void</type>
      <name>CheckPoints</name>
      <anchorfile>class_gm_point_in_poly_unit_tests.html</anchorfile>
      <anchor>a9fbcdd807e9e110065b9b44fe07755c0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual void</type>
      <name>GetResults</name>
      <anchorfile>class_gm_point_in_poly_unit_tests.html</anchorfile>
      <anchor>a6faf1c86377a32334873eb63bcb6cfad</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>std::vector&lt; xms::Pt3d &gt;</type>
      <name>m_outPoly</name>
      <anchorfile>class_gm_point_in_poly_unit_tests.html</anchorfile>
      <anchor>ae4af81c2000f795508bdff86bd95891c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>std::vector&lt; xms::Pt3d &gt;</type>
      <name>m_inPoly</name>
      <anchorfile>class_gm_point_in_poly_unit_tests.html</anchorfile>
      <anchor>a8d9672a8e39a9b6e40b45e9ee4d6d4a6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>boost::timer::cpu_timer</type>
      <name>m_timer</name>
      <anchorfile>class_gm_point_in_poly_unit_tests.html</anchorfile>
      <anchor>abb3f853c60745ea6285525833cf5a1ee</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>m_count</name>
      <anchorfile>class_gm_point_in_poly_unit_tests.html</anchorfile>
      <anchor>a1e67ce3271a3d8cee046bbc18ee040f2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>m_status</name>
      <anchorfile>class_gm_point_in_poly_unit_tests.html</anchorfile>
      <anchor>a1ed8b155abbce252e8bacc00d91d0e36</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" protection="private">
      <type></type>
      <name>XM_DISALLOW_COPY_AND_ASSIGN</name>
      <anchorfile>class_gm_point_in_poly_unit_tests.html</anchorfile>
      <anchor>ad7cbb8b88a9b3d04a585dac034e7d5e3</anchor>
      <arglist>(GmPointInPolyUnitTests)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>xms::GmPolygon</name>
    <filename>classxms_1_1_gm_polygon.html</filename>
    <member kind="function">
      <type></type>
      <name>GmPolygon</name>
      <anchorfile>classxms_1_1_gm_polygon.html</anchorfile>
      <anchor>a5c9b3f01094c446f998eb5d898ff5ff4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~GmPolygon</name>
      <anchorfile>classxms_1_1_gm_polygon.html</anchorfile>
      <anchor>a044fc1abedbc680be3610e0078383b9c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static BSHP&lt; GmPolygon &gt;</type>
      <name>New</name>
      <anchorfile>classxms_1_1_gm_polygon.html</anchorfile>
      <anchor>ad8093f52a1162981b9385f02ab74f020</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>xms::GmPolygonImpl</name>
    <filename>classxms_1_1_gm_polygon_impl.html</filename>
    <base>xms::GmPolygon</base>
    <member kind="function">
      <type></type>
      <name>GmPolygonImpl</name>
      <anchorfile>classxms_1_1_gm_polygon_impl.html</anchorfile>
      <anchor>af30376ca5d7e9312c1ac5d9c7be5fb0d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>Setup</name>
      <anchorfile>classxms_1_1_gm_polygon_impl.html</anchorfile>
      <anchor>af66ebecefe6f91f7cb9d79a1937dfa34</anchor>
      <arglist>(const VecPt3d &amp;a_poly, const VecPt3d2d &amp;a_inPolys) override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>GetPoints</name>
      <anchorfile>classxms_1_1_gm_polygon_impl.html</anchorfile>
      <anchor>ad1a1750096fbfda938910e3ec19d573a</anchor>
      <arglist>(VecPt3d &amp;a_poly, VecPt3d2d &amp;a_inPolys) const override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>CoveredBy</name>
      <anchorfile>classxms_1_1_gm_polygon_impl.html</anchorfile>
      <anchor>ab532f128e5d4ac3c9d5084d639d0c3bf</anchor>
      <arglist>(Pt3d a_point) const override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>Within</name>
      <anchorfile>classxms_1_1_gm_polygon_impl.html</anchorfile>
      <anchor>ab4fb31f5ae09331f8abb148e9374a0fa</anchor>
      <arglist>(Pt3d a_point) const override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual double</type>
      <name>MinDistanceToBoundary</name>
      <anchorfile>classxms_1_1_gm_polygon_impl.html</anchorfile>
      <anchor>a9fc163819fdbfc8e49b6a1ad1716661f</anchor>
      <arglist>(Pt3d a_pt) const override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>Intersection</name>
      <anchorfile>classxms_1_1_gm_polygon_impl.html</anchorfile>
      <anchor>a3dbbbff726ffd85dfeca5b5bd0a1e81e</anchor>
      <arglist>(const GmPolygon &amp;a_, std::vector&lt; BSHP&lt; GmPolygon &gt;&gt; &amp;a_out) const override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>Union</name>
      <anchorfile>classxms_1_1_gm_polygon_impl.html</anchorfile>
      <anchor>ae30032a3f50f76e8698cd3279c1441db</anchor>
      <arglist>(const GmPolygon &amp;a_, std::vector&lt; BSHP&lt; GmPolygon &gt;&gt; &amp;a_out) const override</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>GmBstPoly3d</type>
      <name>m_poly</name>
      <anchorfile>classxms_1_1_gm_polygon_impl.html</anchorfile>
      <anchor>a1b8f4cc90f8c30f3f2b8ede8b5403054</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>GmPolygonIntermediateTests</name>
    <filename>class_gm_polygon_intermediate_tests.html</filename>
    <member kind="function">
      <type>void</type>
      <name>testSpeed</name>
      <anchorfile>class_gm_polygon_intermediate_tests.html</anchorfile>
      <anchor>af601eb8418e0b14047243e8fe948a757</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>GmPolygonUnitTests</name>
    <filename>class_gm_polygon_unit_tests.html</filename>
    <member kind="function">
      <type>void</type>
      <name>testNoHoles</name>
      <anchorfile>class_gm_polygon_unit_tests.html</anchorfile>
      <anchor>a0978e7f7e86b26f1a4e971b3e5d8a31a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testWithHoles</name>
      <anchorfile>class_gm_polygon_unit_tests.html</anchorfile>
      <anchor>aebc8f3e95304faa3551b291634bcfa40</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testMinDistanceToBoundary</name>
      <anchorfile>class_gm_polygon_unit_tests.html</anchorfile>
      <anchor>a7bc270e0a221a9f869972d6fe695feff</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testIntersection</name>
      <anchorfile>class_gm_polygon_unit_tests.html</anchorfile>
      <anchor>a06d62122ec097576fbe8e2831c434259</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testUnion</name>
      <anchorfile>class_gm_polygon_unit_tests.html</anchorfile>
      <anchor>a41d0b777472b559dcada412c42ee2f3d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>SetUpPolyWithHoles1</name>
      <anchorfile>class_gm_polygon_unit_tests.html</anchorfile>
      <anchor>aadbd64575fc6bf90021c7ddaa10b3e28</anchor>
      <arglist>(xms::VecPt3d &amp;a_outPoly, xms::VecPt3d2d &amp;a_inPolys, xms::VecPt3d &amp;a_ptsToTest)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>SetUpPolyWithHole</name>
      <anchorfile>class_gm_polygon_unit_tests.html</anchorfile>
      <anchor>abb784f9e329491d2e69532a3834a8226</anchor>
      <arglist>(xms::VecPt3d &amp;a_outPoly, xms::VecPt3d &amp;a_inPolys)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>xms::GmPolyLinePtRedistributer</name>
    <filename>classxms_1_1_gm_poly_line_pt_redistributer.html</filename>
    <member kind="function" static="yes">
      <type>static BSHP&lt; GmPolyLinePtRedistributer &gt;</type>
      <name>New</name>
      <anchorfile>classxms_1_1_gm_poly_line_pt_redistributer.html</anchorfile>
      <anchor>a058c1ce2832a7e0b76aaa6586199cc2d</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>xms::GmPolyLinePtRedistributerImpl</name>
    <filename>classxms_1_1_gm_poly_line_pt_redistributer_impl.html</filename>
    <base>xms::GmPolyLinePtRedistributer</base>
    <member kind="function" virtualness="virtual">
      <type>virtual VecPt3d</type>
      <name>Redistribute</name>
      <anchorfile>classxms_1_1_gm_poly_line_pt_redistributer_impl.html</anchorfile>
      <anchor>a0fc65a7270b63dd43103de7051d82f44</anchor>
      <arglist>(const VecPt3d &amp;a_input, double a_size) override</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>PolyLineLengths</name>
      <anchorfile>classxms_1_1_gm_poly_line_pt_redistributer_impl.html</anchorfile>
      <anchor>a1d78dd1114e60e22ba262a26d3fa364f</anchor>
      <arglist>(const VecPt3d &amp;a_pts, VecDbl &amp;a_lengths)</arglist>
    </member>
    <member kind="function">
      <type>VecPt3d</type>
      <name>RedistPolyLineWithNumSeg</name>
      <anchorfile>classxms_1_1_gm_poly_line_pt_redistributer_impl.html</anchorfile>
      <anchor>a9d3e8de1f6238353c11aa3e72f136696</anchor>
      <arglist>(const VecPt3d &amp;a_pts, double a_totalLength, const VecDbl &amp;a_lengths, int a_nSeg)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>GmPolyLinePtRedistributerUnitTests</name>
    <filename>class_gm_poly_line_pt_redistributer_unit_tests.html</filename>
    <member kind="function">
      <type>void</type>
      <name>testCreateClass</name>
      <anchorfile>class_gm_poly_line_pt_redistributer_unit_tests.html</anchorfile>
      <anchor>a408aa5befac9d84f88fe51828a343ddd</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testRedistribute</name>
      <anchorfile>class_gm_poly_line_pt_redistributer_unit_tests.html</anchorfile>
      <anchor>a35539a5b291d522f2e6cfc597c368028</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testRedistribute1</name>
      <anchorfile>class_gm_poly_line_pt_redistributer_unit_tests.html</anchorfile>
      <anchor>ae730c8c2625bc12b21001743446a9ce8</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>xms::GmPtSearch</name>
    <filename>classxms_1_1_gm_pt_search.html</filename>
    <member kind="function" static="yes">
      <type>static BSHP&lt; GmPtSearch &gt;</type>
      <name>New</name>
      <anchorfile>classxms_1_1_gm_pt_search.html</anchorfile>
      <anchor>a883ee1e554d92caaed23923ebb39f4f8</anchor>
      <arglist>(bool a_2dSearch)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>xms::GmPtSearchImpl</name>
    <filename>classxms_1_1_gm_pt_search_impl.html</filename>
    <base>xms::GmPtSearch</base>
    <member kind="function">
      <type></type>
      <name>GmPtSearchImpl</name>
      <anchorfile>classxms_1_1_gm_pt_search_impl.html</anchorfile>
      <anchor>ac5241a77c7018ec67738437fc0117549</anchor>
      <arglist>(bool a_2dSearch)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>PtsToSearch</name>
      <anchorfile>classxms_1_1_gm_pt_search_impl.html</anchorfile>
      <anchor>aab9e1586fb5cdb066d25e8e63d4ab10e</anchor>
      <arglist>(BSHP&lt; std::vector&lt; Pt3d &gt;&gt; a_pts) override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>VectorThatGrowsToSearch</name>
      <anchorfile>classxms_1_1_gm_pt_search_impl.html</anchorfile>
      <anchor>a8397d8d68e7de98085af3ebc3e198308</anchor>
      <arglist>(BSHP&lt; std::vector&lt; Pt3d &gt;&gt; a_) override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>AddPtToVectorIfUnique</name>
      <anchorfile>classxms_1_1_gm_pt_search_impl.html</anchorfile>
      <anchor>ae4a7236045f1e28491e378f727faea78</anchor>
      <arglist>(const Pt3d &amp;a_, double a_tol, int &amp;a_ptIdx) override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>NearestPtsToPt</name>
      <anchorfile>classxms_1_1_gm_pt_search_impl.html</anchorfile>
      <anchor>acb07d6a4f730c02e2044c52ae9877f9e</anchor>
      <arglist>(const Pt3d &amp;a_pt, int a_numPtsToFind, bool a_quad_oct_Search, std::vector&lt; int &gt; &amp;a_nearest) const override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>NearestPtsToPtInRtree</name>
      <anchorfile>classxms_1_1_gm_pt_search_impl.html</anchorfile>
      <anchor>a1bcb75c2e478882e10daacb9768be4f0</anchor>
      <arglist>(int a_ptIdx, const Pt3d &amp;a_pt, int a_numPtsToFind, bool a_quad_oct_Search, std::vector&lt; int &gt; &amp;a_nearest) const override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>PtInRTree</name>
      <anchorfile>classxms_1_1_gm_pt_search_impl.html</anchorfile>
      <anchor>abc2c132b03146ef72209c914418ebf2a</anchor>
      <arglist>(const Pt3d &amp;a_pt, const double a_tol) override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>PtsWithinDistanceToPtInRtree</name>
      <anchorfile>classxms_1_1_gm_pt_search_impl.html</anchorfile>
      <anchor>a7c3348725a96a2bbef9bc9ed28742c03</anchor>
      <arglist>(int a_ptIdx, const Pt3d &amp;a_pt, double a_dist, std::vector&lt; int &gt; &amp;a_nearest) const override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>NearestPtsToPt</name>
      <anchorfile>classxms_1_1_gm_pt_search_impl.html</anchorfile>
      <anchor>a798982ff06d8f2b9d702e8c524770448</anchor>
      <arglist>(const Pt3d &amp;a_pt, int a_numPtsToFind, bool a_quad_oct_Search, std::vector&lt; int &gt; &amp;a_nearest, fSatisfies *a_fsat) const</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>SetActivity</name>
      <anchorfile>classxms_1_1_gm_pt_search_impl.html</anchorfile>
      <anchor>af92eb3184ddbb6ff6844f6e5c4563912</anchor>
      <arglist>(DynBitset &amp;a_activity) override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual DynBitset</type>
      <name>GetActivity</name>
      <anchorfile>classxms_1_1_gm_pt_search_impl.html</anchorfile>
      <anchor>a6e2738c96014e542d8ba2977ce996eac</anchor>
      <arglist>() override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const BSHP&lt; VecPt3d &gt;</type>
      <name>GetPointsPtr</name>
      <anchorfile>classxms_1_1_gm_pt_search_impl.html</anchorfile>
      <anchor>a501ca6b9d117c035425e3ad64de30edf</anchor>
      <arglist>() const override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>Is2D</name>
      <anchorfile>classxms_1_1_gm_pt_search_impl.html</anchorfile>
      <anchor>a106b0a5f562d15608e27969a8fed1f5b</anchor>
      <arglist>() const override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual std::string</type>
      <name>ToString</name>
      <anchorfile>classxms_1_1_gm_pt_search_impl.html</anchorfile>
      <anchor>a4b7acbdee40b84ef7d8f4b695a04ce4f</anchor>
      <arglist>() const override</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>UpdateMinMax</name>
      <anchorfile>classxms_1_1_gm_pt_search_impl.html</anchorfile>
      <anchor>a025de6d0fd6c227670e92acef587bfb1</anchor>
      <arglist>(const Pt3d *a_pts, size_t a_npts)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>CreateOctants</name>
      <anchorfile>classxms_1_1_gm_pt_search_impl.html</anchorfile>
      <anchor>aae9c54c626d2860a7be4fc122fb917ae</anchor>
      <arglist>(const Pt3d &amp;a_pt, std::vector&lt; box &gt; &amp;a_boxes) const</arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>m_2dSearch</name>
      <anchorfile>classxms_1_1_gm_pt_search_impl.html</anchorfile>
      <anchor>acc23253ca6b707d8a84854c23c1e6914</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Pt3d</type>
      <name>m_min</name>
      <anchorfile>classxms_1_1_gm_pt_search_impl.html</anchorfile>
      <anchor>a2d87fb7faa5dc23ad3cb7a2a5fd3c451</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Pt3d</type>
      <name>m_max</name>
      <anchorfile>classxms_1_1_gm_pt_search_impl.html</anchorfile>
      <anchor>aab93492b32a85bd6ce63b6266bea5b3e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>DynBitset</type>
      <name>m_activity</name>
      <anchorfile>classxms_1_1_gm_pt_search_impl.html</anchorfile>
      <anchor>a97f39190bddeb60d645f96a140898553</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bgi::rtree&lt; value, qRtree, idx_pt &gt; *</type>
      <name>m_rTree</name>
      <anchorfile>classxms_1_1_gm_pt_search_impl.html</anchorfile>
      <anchor>a412dbf1256bcb8d0666aa1a493737350</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>BSHP&lt; VecPt3d &gt;</type>
      <name>m_bshpPt3d</name>
      <anchorfile>classxms_1_1_gm_pt_search_impl.html</anchorfile>
      <anchor>a4d1a3ea0ffb1a2ca48d8d5e00146e750</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>xms::GmTriSearch</name>
    <filename>classxms_1_1_gm_tri_search.html</filename>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~GmTriSearch</name>
      <anchorfile>classxms_1_1_gm_tri_search.html</anchorfile>
      <anchor>ac56072f01e9da1702618ee7255bb91c0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static BSHP&lt; GmTriSearch &gt;</type>
      <name>New</name>
      <anchorfile>classxms_1_1_gm_tri_search.html</anchorfile>
      <anchor>a2df03859534cd0296e57bb87b7d418a2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type></type>
      <name>GmTriSearch</name>
      <anchorfile>classxms_1_1_gm_tri_search.html</anchorfile>
      <anchor>ae944fa5ccf34141894a79b803b78fadc</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>xms::GmTriSearchImpl</name>
    <filename>classxms_1_1_gm_tri_search_impl.html</filename>
    <base>xms::GmTriSearch</base>
    <member kind="function">
      <type></type>
      <name>GmTriSearchImpl</name>
      <anchorfile>classxms_1_1_gm_tri_search_impl.html</anchorfile>
      <anchor>a9b2ed0cf16ebef3d93ad379d21438d35</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~GmTriSearchImpl</name>
      <anchorfile>classxms_1_1_gm_tri_search_impl.html</anchorfile>
      <anchor>a611da2725a598042a153313f8042e4e5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>TrisToSearch</name>
      <anchorfile>classxms_1_1_gm_tri_search_impl.html</anchorfile>
      <anchor>ab12d667cf4931879e49158ca27a7d0da</anchor>
      <arglist>(BSHP&lt; std::vector&lt; Pt3d &gt;&gt; a_pts, BSHP&lt; std::vector&lt; int &gt;&gt; a_tris) override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>SetPtActivity</name>
      <anchorfile>classxms_1_1_gm_tri_search_impl.html</anchorfile>
      <anchor>a8f22b0237cb737b390ba5c4fc1512d64</anchor>
      <arglist>(DynBitset &amp;a_activity) override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>SetTriActivity</name>
      <anchorfile>classxms_1_1_gm_tri_search_impl.html</anchorfile>
      <anchor>a70c35b1902abf36b4b13a6d1eebbf3cc</anchor>
      <arglist>(DynBitset &amp;a_activity) override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual DynBitset</type>
      <name>GetPtActivity</name>
      <anchorfile>classxms_1_1_gm_tri_search_impl.html</anchorfile>
      <anchor>a7ef7b01bc917d68bc9cbe258b6e6a9b4</anchor>
      <arglist>() const override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual DynBitset</type>
      <name>GetTriActivity</name>
      <anchorfile>classxms_1_1_gm_tri_search_impl.html</anchorfile>
      <anchor>a07303c6ed2b3ddc399cd218d439c0446</anchor>
      <arglist>() const override</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>ActiveTri</name>
      <anchorfile>classxms_1_1_gm_tri_search_impl.html</anchorfile>
      <anchor>ac281a7bee912f5a25c2f29596d85c8c7</anchor>
      <arglist>(int a_idx) const</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>TriContainingPt</name>
      <anchorfile>classxms_1_1_gm_tri_search_impl.html</anchorfile>
      <anchor>a57e36ef11703b604721b833587277e3b</anchor>
      <arglist>(const Pt3d &amp;a_pt) override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>TriEnvelopsContainingPt</name>
      <anchorfile>classxms_1_1_gm_tri_search_impl.html</anchorfile>
      <anchor>a2499bd15424d39940d7a22c0ee90862a</anchor>
      <arglist>(const Pt3d &amp;a_pt, std::vector&lt; int &gt; &amp;a_tris) override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>TriEnvelopesOverlap</name>
      <anchorfile>classxms_1_1_gm_tri_search_impl.html</anchorfile>
      <anchor>a884a53233410d94455ac562ae22d783f</anchor>
      <arglist>(const Pt3d &amp;a_pMin, const Pt3d &amp;a_pMax, std::vector&lt; int &gt; &amp;a_tris) override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>InterpWeights</name>
      <anchorfile>classxms_1_1_gm_tri_search_impl.html</anchorfile>
      <anchor>a89161f03d360c52d22a4d0995e1a5869</anchor>
      <arglist>(const Pt3d &amp;a_pt, std::vector&lt; int &gt; &amp;a_idxs, std::vector&lt; double &gt; &amp;a_wts) override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>InterpWeightsTriangleIdx</name>
      <anchorfile>classxms_1_1_gm_tri_search_impl.html</anchorfile>
      <anchor>a6f831e143724ccc2a55c0daa7995e449</anchor>
      <arglist>(const Pt3d &amp;a_pt, int &amp;a_triangleIdx, std::vector&lt; int &gt; &amp;a_idxs, std::vector&lt; double &gt; &amp;a_wts) override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const BSHP&lt; VecPt3d &gt;</type>
      <name>GetPoints</name>
      <anchorfile>classxms_1_1_gm_tri_search_impl.html</anchorfile>
      <anchor>a681a886b30b96254f6b3ab5e9cf1b1fc</anchor>
      <arglist>() const override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const BSHP&lt; VecInt &gt;</type>
      <name>GetTriangles</name>
      <anchorfile>classxms_1_1_gm_tri_search_impl.html</anchorfile>
      <anchor>ac3f2d17dc8d0568e1f67b9049d3cb827</anchor>
      <arglist>() const override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual std::string</type>
      <name>ToString</name>
      <anchorfile>classxms_1_1_gm_tri_search_impl.html</anchorfile>
      <anchor>ab61cf81f803d0d87fcbf6e2410ae2d25</anchor>
      <arglist>() const override</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>CreateRTree</name>
      <anchorfile>classxms_1_1_gm_tri_search_impl.html</anchorfile>
      <anchor>ae9759f6aa25a8897ecc21e3f7edb80d7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>PointIdxesFromTriIdx</name>
      <anchorfile>classxms_1_1_gm_tri_search_impl.html</anchorfile>
      <anchor>ab3a89a592db07b714e4a5eb8d12037c6</anchor>
      <arglist>(int a_triIdx, int a_ptIdxes[3])</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>FindTriangle</name>
      <anchorfile>classxms_1_1_gm_tri_search_impl.html</anchorfile>
      <anchor>a040343fd456349661bbbf82dda01e9c5</anchor>
      <arglist>(const Pt3d &amp;a_pt, int ix[3], Pt3d &amp;weights)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>GetTriBarycentricVals</name>
      <anchorfile>classxms_1_1_gm_tri_search_impl.html</anchorfile>
      <anchor>a21de9e3170fcd10467c14aeea25d74be</anchor>
      <arglist>(int a_idx, int a_ix[3], BarycentricVals &amp;a_b)</arglist>
    </member>
    <member kind="function">
      <type>DynBitset</type>
      <name>PointActivityFromTriActivity</name>
      <anchorfile>classxms_1_1_gm_tri_search_impl.html</anchorfile>
      <anchor>aa3ae01b7bd0dfc9648e51550dfc8d8b9</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>BSHP&lt; GmPtSearch &gt;</type>
      <name>CreatePtSearch</name>
      <anchorfile>classxms_1_1_gm_tri_search_impl.html</anchorfile>
      <anchor>a61ab221cb9ff1755cf300597fbc10600</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable">
      <type>Pt3d</type>
      <name>m_min</name>
      <anchorfile>classxms_1_1_gm_tri_search_impl.html</anchorfile>
      <anchor>ab5dafd8842cf0404cc3ea8aa0d1aa610</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Pt3d</type>
      <name>m_max</name>
      <anchorfile>classxms_1_1_gm_tri_search_impl.html</anchorfile>
      <anchor>a5abff431d736788f27904778ea9ef0cb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>BSHP&lt; std::vector&lt; Pt3d &gt; &gt;</type>
      <name>m_pts</name>
      <anchorfile>classxms_1_1_gm_tri_search_impl.html</anchorfile>
      <anchor>a34d64d02d4d92142cb47b368c86ec739</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>BSHP&lt; std::vector&lt; int &gt; &gt;</type>
      <name>m_tris</name>
      <anchorfile>classxms_1_1_gm_tri_search_impl.html</anchorfile>
      <anchor>a500ef32dbd0fc06a8384a67656b5e6a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>DynBitset</type>
      <name>m_triActivity</name>
      <anchorfile>classxms_1_1_gm_tri_search_impl.html</anchorfile>
      <anchor>aad9adb0543bcb70198143b35a71bc950</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>boost::unordered_map&lt; size_t, BarycentricVals &gt;</type>
      <name>m_cache</name>
      <anchorfile>classxms_1_1_gm_tri_search_impl.html</anchorfile>
      <anchor>a02245069dba9182140afe37cbc08d6f0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bgi::rtree&lt; value, qRtree, idx_tri &gt; *</type>
      <name>m_rTree</name>
      <anchorfile>classxms_1_1_gm_tri_search_impl.html</anchorfile>
      <anchor>a91899c759fe0fd8b1e230c1efb650138</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>xms::idx_pt</name>
    <filename>classxms_1_1idx__pt.html</filename>
    <member kind="typedef">
      <type>const bPt</type>
      <name>result_type</name>
      <anchorfile>classxms_1_1idx__pt.html</anchorfile>
      <anchor>ad127b38c3e9fb6c1d652fa2b6f75880d</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>idx_pt</name>
      <anchorfile>classxms_1_1idx__pt.html</anchorfile>
      <anchor>a2b7929bfcd2024966dd873f3e952a345</anchor>
      <arglist>(const Pt3d *a_, bool a_2d)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>idx_pt</name>
      <anchorfile>classxms_1_1idx__pt.html</anchorfile>
      <anchor>a709964a4e328dd7f2e693eb9833031c1</anchor>
      <arglist>(BSHP&lt; std::vector&lt; Pt3d &gt;&gt; a_, bool a_2d)</arglist>
    </member>
    <member kind="function">
      <type>result_type</type>
      <name>operator()</name>
      <anchorfile>classxms_1_1idx__pt.html</anchorfile>
      <anchor>ab7d7c2492883daab3ed8211b1a4468c2</anchor>
      <arglist>(size_t i) const</arglist>
    </member>
    <member kind="variable">
      <type>const Pt3d *</type>
      <name>m_</name>
      <anchorfile>classxms_1_1idx__pt.html</anchorfile>
      <anchor>a0187e9f5054b0c3388e299239311646b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>m_2d</name>
      <anchorfile>classxms_1_1idx__pt.html</anchorfile>
      <anchor>aec9584b8b51e6795e4e0106187b68a5f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>BSHP&lt; std::vector&lt; Pt3d &gt; &gt;</type>
      <name>m_v</name>
      <anchorfile>classxms_1_1idx__pt.html</anchorfile>
      <anchor>a90678c68a3faa676fb06b081a6e070c6</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>xms::idx_tri</name>
    <filename>classxms_1_1idx__tri.html</filename>
    <member kind="typedef">
      <type>const GmBstBox3d</type>
      <name>result_type</name>
      <anchorfile>classxms_1_1idx__tri.html</anchorfile>
      <anchor>a88c4b0524e400a243b939e69b13fa9fa</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>idx_tri</name>
      <anchorfile>classxms_1_1idx__tri.html</anchorfile>
      <anchor>a18b7dba501483fa3ebb141f439497dfc</anchor>
      <arglist>(const Pt3d *a_pts, const int *a_tris, double a_tol)</arglist>
    </member>
    <member kind="function">
      <type>result_type</type>
      <name>operator()</name>
      <anchorfile>classxms_1_1idx__tri.html</anchorfile>
      <anchor>acb9ee91c68bfa303474a193eb7769614</anchor>
      <arglist>(size_t i) const</arglist>
    </member>
    <member kind="variable">
      <type>const Pt3d *</type>
      <name>m_pts</name>
      <anchorfile>classxms_1_1idx__tri.html</anchorfile>
      <anchor>a13730645297b2eb5f6ef6e657d878dc4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const int *</type>
      <name>m_tris</name>
      <anchorfile>classxms_1_1idx__tri.html</anchorfile>
      <anchor>a2f6cabf2a7d2ac6ae5fe7c349262fcf9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>double</type>
      <name>m_tol</name>
      <anchorfile>classxms_1_1idx__tri.html</anchorfile>
      <anchor>ad89989a3a633daba4bcea58b7168ab79</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>xms::XmUGrid::Impl</name>
    <filename>classxms_1_1_xm_u_grid_1_1_impl.html</filename>
    <member kind="function">
      <type></type>
      <name>Impl</name>
      <anchorfile>classxms_1_1_xm_u_grid_1_1_impl.html</anchorfile>
      <anchor>a794a282fb57b10f2ac4f838c0481347c</anchor>
      <arglist>()=default</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Impl</name>
      <anchorfile>classxms_1_1_xm_u_grid_1_1_impl.html</anchorfile>
      <anchor>ab4ae9aa5fa2e7c0cac72e48639680ec6</anchor>
      <arglist>(const Impl &amp;)=default</arglist>
    </member>
    <member kind="function">
      <type>Impl &amp;</type>
      <name>operator=</name>
      <anchorfile>classxms_1_1_xm_u_grid_1_1_impl.html</anchorfile>
      <anchor>a3fd9c6988e12eb86d8af43d555934cad</anchor>
      <arglist>(const Impl &amp;a_xmUGrid)=default</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>GetModified</name>
      <anchorfile>classxms_1_1_xm_u_grid_1_1_impl.html</anchorfile>
      <anchor>ae518405691dab6a15d12f51a0cdde53e</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetUnmodified</name>
      <anchorfile>classxms_1_1_xm_u_grid_1_1_impl.html</anchorfile>
      <anchor>aefeac1f7ac003960ab3f4b63d5e01438</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetUseCache</name>
      <anchorfile>classxms_1_1_xm_u_grid_1_1_impl.html</anchorfile>
      <anchor>a12862fa22006392539fa9fcb32ee4aed</anchor>
      <arglist>(bool a_useCache)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetPointCount</name>
      <anchorfile>classxms_1_1_xm_u_grid_1_1_impl.html</anchorfile>
      <anchor>ab5ef774a1d193685699175b371941592</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>const VecPt3d &amp;</type>
      <name>GetLocations</name>
      <anchorfile>classxms_1_1_xm_u_grid_1_1_impl.html</anchorfile>
      <anchor>ad19c86a81d7b38a2f4eb420ff6e579c0</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetLocations</name>
      <anchorfile>classxms_1_1_xm_u_grid_1_1_impl.html</anchorfile>
      <anchor>aab2ab453d8c6b68f715205fe3d1aa331</anchor>
      <arglist>(const VecPt3d &amp;a_locations)</arglist>
    </member>
    <member kind="function">
      <type>Pt3d</type>
      <name>GetPointLocation</name>
      <anchorfile>classxms_1_1_xm_u_grid_1_1_impl.html</anchorfile>
      <anchor>a135de22d2514c15a72065971a810c4d4</anchor>
      <arglist>(int a_pointIdx) const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>SetPointLocation</name>
      <anchorfile>classxms_1_1_xm_u_grid_1_1_impl.html</anchorfile>
      <anchor>abc06de93643bf9a6211285ab81258b0e</anchor>
      <arglist>(int a_pointIdx, const Pt3d &amp;a_location)</arglist>
    </member>
    <member kind="function">
      <type>Pt3d</type>
      <name>GetPointXy0</name>
      <anchorfile>classxms_1_1_xm_u_grid_1_1_impl.html</anchorfile>
      <anchor>aafb163b2d1b7a2706f96d1deae5735d4</anchor>
      <arglist>(int a_pointIdx) const</arglist>
    </member>
    <member kind="function">
      <type>VecPt3d</type>
      <name>GetPointsLocations</name>
      <anchorfile>classxms_1_1_xm_u_grid_1_1_impl.html</anchorfile>
      <anchor>aaef2f250144dd0dac22ba49fbdca8a00</anchor>
      <arglist>(const VecInt &amp;a_points) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>GetExtents</name>
      <anchorfile>classxms_1_1_xm_u_grid_1_1_impl.html</anchorfile>
      <anchor>a2bbe67c03fe0d69eb7296c47fa2fc41c</anchor>
      <arglist>(Pt3d &amp;a_min, Pt3d &amp;a_max) const</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetPointAdjacentCellCount</name>
      <anchorfile>classxms_1_1_xm_u_grid_1_1_impl.html</anchorfile>
      <anchor>a1dd359edb9ba008a62a84fe359c533bd</anchor>
      <arglist>(int a_pointIdx) const</arglist>
    </member>
    <member kind="function">
      <type>VecInt</type>
      <name>GetPointAdjacentCells</name>
      <anchorfile>classxms_1_1_xm_u_grid_1_1_impl.html</anchorfile>
      <anchor>a1aa2cc531ff1e4f5637f8fab3e039017</anchor>
      <arglist>(int a_pointIdx) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>GetPointAdjacentCells</name>
      <anchorfile>classxms_1_1_xm_u_grid_1_1_impl.html</anchorfile>
      <anchor>a13f23d6189b9f0c71f65b921ca1fb7cd</anchor>
      <arglist>(int a_pointIdx, VecInt &amp;a_adjacentCells) const</arglist>
    </member>
    <member kind="function">
      <type>VecInt</type>
      <name>GetPointsAdjacentCells</name>
      <anchorfile>classxms_1_1_xm_u_grid_1_1_impl.html</anchorfile>
      <anchor>a9dfaf24de23416d19fb1380f3af53506</anchor>
      <arglist>(const VecInt &amp;a_points) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>GetPointsAdjacentCells</name>
      <anchorfile>classxms_1_1_xm_u_grid_1_1_impl.html</anchorfile>
      <anchor>a7d316706b02334cbd6abe329fc569da2</anchor>
      <arglist>(const int *a_pointIdxs, int a_numpointIdxs, VecInt &amp;a_commonCellIdxs) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>GetPointsAdjacentCells</name>
      <anchorfile>classxms_1_1_xm_u_grid_1_1_impl.html</anchorfile>
      <anchor>a8c0181625a17f334668596c6aaf05339</anchor>
      <arglist>(const VecInt &amp;a_pointIdxs, VecInt &amp;a_commonCellIdxs) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>GetPointsAdjacentCells</name>
      <anchorfile>classxms_1_1_xm_u_grid_1_1_impl.html</anchorfile>
      <anchor>aa699efb9ac38f1654055a6b609eba204</anchor>
      <arglist>(int a_pointIdx1, int a_pointIdx2, VecInt &amp;a_adjacentCellIdxs) const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>IsValidPointChange</name>
      <anchorfile>classxms_1_1_xm_u_grid_1_1_impl.html</anchorfile>
      <anchor>a8ecccf25dacbf9b57a457c80b63d6e98</anchor>
      <arglist>(int a_changedPtIdx, const Pt3d &amp;a_newPosition) const</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetCellCount</name>
      <anchorfile>classxms_1_1_xm_u_grid_1_1_impl.html</anchorfile>
      <anchor>ac8872ed79979abda1fafab34ca320bdf</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetCellPointCount</name>
      <anchorfile>classxms_1_1_xm_u_grid_1_1_impl.html</anchorfile>
      <anchor>a53bcafbeea8267271ca78037caec1bc2</anchor>
      <arglist>(int a_cellIdx) const</arglist>
    </member>
    <member kind="function">
      <type>VecInt</type>
      <name>GetCellPoints</name>
      <anchorfile>classxms_1_1_xm_u_grid_1_1_impl.html</anchorfile>
      <anchor>a7d5f542d3d1c5247f34e446bd308a71a</anchor>
      <arglist>(int a_cellIdx) const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>GetCellPoints</name>
      <anchorfile>classxms_1_1_xm_u_grid_1_1_impl.html</anchorfile>
      <anchor>ae0cc43c0bf9dd0c217f4ac1b3c93ca51</anchor>
      <arglist>(int a_cellIdx, VecInt &amp;a_cellPoints) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>GetCellLocations</name>
      <anchorfile>classxms_1_1_xm_u_grid_1_1_impl.html</anchorfile>
      <anchor>aa3b8b2455cb833b3c53b77e61bf8f702</anchor>
      <arglist>(int a_cellIdx, VecPt3d &amp;a_cellLocations) const</arglist>
    </member>
    <member kind="function">
      <type>XmUGridCellType</type>
      <name>GetCellType</name>
      <anchorfile>classxms_1_1_xm_u_grid_1_1_impl.html</anchorfile>
      <anchor>a3219b9dec208d67d518670973c92819b</anchor>
      <arglist>(int a_cellIdx) const</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; int &gt;</type>
      <name>GetDimensionCounts</name>
      <anchorfile>classxms_1_1_xm_u_grid_1_1_impl.html</anchorfile>
      <anchor>a86b94aba16dce9b2235504854c938cae</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetCellDimension</name>
      <anchorfile>classxms_1_1_xm_u_grid_1_1_impl.html</anchorfile>
      <anchor>a6b2a6559bedc76985da8a3feabde9f96</anchor>
      <arglist>(int a_cellIdx) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>GetCellExtents</name>
      <anchorfile>classxms_1_1_xm_u_grid_1_1_impl.html</anchorfile>
      <anchor>a66a38f1efbd222fdf76d0751a13c9ec4</anchor>
      <arglist>(int a_cellIdx, Pt3d &amp;a_min, Pt3d &amp;a_max) const</arglist>
    </member>
    <member kind="function">
      <type>const VecInt &amp;</type>
      <name>GetCellstream</name>
      <anchorfile>classxms_1_1_xm_u_grid_1_1_impl.html</anchorfile>
      <anchor>a904be5bd02a3131ac8779cd9dd6492ac</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>SetCellstream</name>
      <anchorfile>classxms_1_1_xm_u_grid_1_1_impl.html</anchorfile>
      <anchor>aca2a729d5f44c52cd7a09a78e729752b</anchor>
      <arglist>(const VecInt &amp;a_cellstream)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>GetCellCellstream</name>
      <anchorfile>classxms_1_1_xm_u_grid_1_1_impl.html</anchorfile>
      <anchor>a1e607f3f071ac4f80f4a41f866f04b5a</anchor>
      <arglist>(int a_cellIdx, VecInt &amp;a_cellstream) const</arglist>
    </member>
    <member kind="function">
      <type>VecInt</type>
      <name>GetCellAdjacentCells</name>
      <anchorfile>classxms_1_1_xm_u_grid_1_1_impl.html</anchorfile>
      <anchor>a39846172608687da5c9c09677600b0c8</anchor>
      <arglist>(int a_cellIdx) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>GetCellAdjacentCells</name>
      <anchorfile>classxms_1_1_xm_u_grid_1_1_impl.html</anchorfile>
      <anchor>a8e1c87c9a2a5574cf255b44c574e9294</anchor>
      <arglist>(int a_cellIdx, VecInt &amp;a_cellNeighbors) const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>GetCellPlanViewPolygon</name>
      <anchorfile>classxms_1_1_xm_u_grid_1_1_impl.html</anchorfile>
      <anchor>a1d0da41383ebbd27978a3a8a7cc3314e</anchor>
      <arglist>(int a_cellIdx, VecPt3d &amp;a_polygon) const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>GetCellCentroid</name>
      <anchorfile>classxms_1_1_xm_u_grid_1_1_impl.html</anchorfile>
      <anchor>a3cdd3dc32f9ddb40cfbe4234478b63db</anchor>
      <arglist>(int a_cellIdx, Pt3d &amp;a_centroid) const</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetCellEdgeCount</name>
      <anchorfile>classxms_1_1_xm_u_grid_1_1_impl.html</anchorfile>
      <anchor>a723969a55c7347676ab4d9c3afc9b938</anchor>
      <arglist>(int a_cellIdx) const</arglist>
    </member>
    <member kind="function">
      <type>XmEdge</type>
      <name>GetCellEdge</name>
      <anchorfile>classxms_1_1_xm_u_grid_1_1_impl.html</anchorfile>
      <anchor>a5c058ea03f779903b428e513e580101e</anchor>
      <arglist>(int a_cellIdx, int a_edgeIdx) const</arglist>
    </member>
    <member kind="function">
      <type>VecInt</type>
      <name>GetCellEdgeAdjacentCells</name>
      <anchorfile>classxms_1_1_xm_u_grid_1_1_impl.html</anchorfile>
      <anchor>a60a6a73258c6ae2a360a8fbfb3f29a38</anchor>
      <arglist>(int a_cellIdx, int a_edgeIdx) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>GetCellEdgeAdjacentCells</name>
      <anchorfile>classxms_1_1_xm_u_grid_1_1_impl.html</anchorfile>
      <anchor>a0580a7c401eca45cb2d4f73e53434c2a</anchor>
      <arglist>(int a_cellIdx, int a_edgeIdx, VecInt &amp;a_adjacentCellIdxs) const</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetCell2dEdgeAdjacentCell</name>
      <anchorfile>classxms_1_1_xm_u_grid_1_1_impl.html</anchorfile>
      <anchor>a0add3d81f229cb7c3aa1e1add1e3aea9</anchor>
      <arglist>(int a_cellIdx, int a_edgeIdx) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>GetEdgeAdjacentCells</name>
      <anchorfile>classxms_1_1_xm_u_grid_1_1_impl.html</anchorfile>
      <anchor>ab60c90f74485fcf29fa0105015478616</anchor>
      <arglist>(const XmEdge &amp;a_edge, VecInt &amp;a_adjacentCellIdxs) const</arglist>
    </member>
    <member kind="function">
      <type>VecInt</type>
      <name>GetEdgeAdjacentCells</name>
      <anchorfile>classxms_1_1_xm_u_grid_1_1_impl.html</anchorfile>
      <anchor>a8a2e3ba91021f20ba92db640bcd0dac8</anchor>
      <arglist>(const XmEdge &amp;a_edge) const</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; XmEdge &gt;</type>
      <name>GetCellEdges</name>
      <anchorfile>classxms_1_1_xm_u_grid_1_1_impl.html</anchorfile>
      <anchor>a2b49191b916c98f89e11e8fd6caf81c8</anchor>
      <arglist>(int a_cellIdx) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>GetCellEdges</name>
      <anchorfile>classxms_1_1_xm_u_grid_1_1_impl.html</anchorfile>
      <anchor>aed236f61eaf98e12576c8849deda1e47</anchor>
      <arglist>(int a_cellIdx, std::vector&lt; XmEdge &gt; &amp;a_edges) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>GetPointAdjacentPoints</name>
      <anchorfile>classxms_1_1_xm_u_grid_1_1_impl.html</anchorfile>
      <anchor>a55794b180d8759e45cf2968e90db50fb</anchor>
      <arglist>(int a_pointIdx, VecInt &amp;a_edgePoints) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>GetPointAdjacentLocations</name>
      <anchorfile>classxms_1_1_xm_u_grid_1_1_impl.html</anchorfile>
      <anchor>a09d68ef6f5f359284da3033941769a3b</anchor>
      <arglist>(int a_pointIdx, VecPt3d &amp;a_edgePoints) const</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetCell3dFaceCount</name>
      <anchorfile>classxms_1_1_xm_u_grid_1_1_impl.html</anchorfile>
      <anchor>ad288a00c4966178d05fe722f76b92b05</anchor>
      <arglist>(int a_cellIdx) const</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetCell3dFacePointCount</name>
      <anchorfile>classxms_1_1_xm_u_grid_1_1_impl.html</anchorfile>
      <anchor>aa97a36c0237482ff6d188ce5554a4174</anchor>
      <arglist>(int a_cellIdx, int a_faceIdx) const</arglist>
    </member>
    <member kind="function">
      <type>VecInt</type>
      <name>GetCell3dFacePoints</name>
      <anchorfile>classxms_1_1_xm_u_grid_1_1_impl.html</anchorfile>
      <anchor>ac5958b9821e87a7bd00c03c8837c70f1</anchor>
      <arglist>(int a_cellIdx, int a_faceIdx) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>GetCell3dFacePoints</name>
      <anchorfile>classxms_1_1_xm_u_grid_1_1_impl.html</anchorfile>
      <anchor>a9028fd7d75a1a1d680f7efba2e0bdd68</anchor>
      <arglist>(int a_cellIdx, int a_faceIdx, VecInt &amp;a_facePtIdxs) const</arglist>
    </member>
    <member kind="function">
      <type>VecInt2d</type>
      <name>GetCell3dFacesPoints</name>
      <anchorfile>classxms_1_1_xm_u_grid_1_1_impl.html</anchorfile>
      <anchor>a73b55f8d7470f60d3007ad90ba3edeb8</anchor>
      <arglist>(int a_cellIdx) const</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetCell3dFaceAdjacentCell</name>
      <anchorfile>classxms_1_1_xm_u_grid_1_1_impl.html</anchorfile>
      <anchor>a3a4b336e5dd535d74e515cfc4e9b7362</anchor>
      <arglist>(int a_cellIdx, int a_faceIdx) const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>GetCell3dFaceAdjacentCell</name>
      <anchorfile>classxms_1_1_xm_u_grid_1_1_impl.html</anchorfile>
      <anchor>a14182d4d416c2d586e589254beff0d4e</anchor>
      <arglist>(int a_cellIdx, int a_faceIdx, int &amp;a_neighborCell, int &amp;a_neighborFace) const</arglist>
    </member>
    <member kind="function">
      <type>XmUGridFaceOrientation</type>
      <name>GetCell3dFaceOrientation</name>
      <anchorfile>classxms_1_1_xm_u_grid_1_1_impl.html</anchorfile>
      <anchor>ad3f7eac540a84c2614de7ec55932283f</anchor>
      <arglist>(int a_cellIdx, int a_faceIdx) const</arglist>
    </member>
    <member kind="function">
      <type>XmUGridFaceOrientation</type>
      <name>FaceOrientation</name>
      <anchorfile>classxms_1_1_xm_u_grid_1_1_impl.html</anchorfile>
      <anchor>a9eb19e84aa68a154aff7cdbd8780fd7e</anchor>
      <arglist>(int a_cellIdx, int a_faceIdx) const</arglist>
    </member>
    <member kind="function">
      <type>XmUGridFaceOrientation</type>
      <name>VerticalOrientationFromOpposing</name>
      <anchorfile>classxms_1_1_xm_u_grid_1_1_impl.html</anchorfile>
      <anchor>abf3ae75f6d1f16eec630155685430638</anchor>
      <arglist>(int a_cellIdx, int a_faceIdx) const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>IsSideFace</name>
      <anchorfile>classxms_1_1_xm_u_grid_1_1_impl.html</anchorfile>
      <anchor>a45d8a91f6642c71c48f440ab4178ddf0</anchor>
      <arglist>(int a_cellIdx, int a_faceIdx) const</arglist>
    </member>
    <member kind="function">
      <type>XmUGridFaceOrientation</type>
      <name>ConnectedTopOrBottom</name>
      <anchorfile>classxms_1_1_xm_u_grid_1_1_impl.html</anchorfile>
      <anchor>a9f6c0ee548eef71afecd775c83ccb86e</anchor>
      <arglist>(int a_cellIdx, int a_faceIdx) const</arglist>
    </member>
    <member kind="function">
      <type>XmUGridFaceOrientation</type>
      <name>GetOrientationFromArea</name>
      <anchorfile>classxms_1_1_xm_u_grid_1_1_impl.html</anchorfile>
      <anchor>af3572d7e847a8f2d29c9279f6ec57561</anchor>
      <arglist>(int a_cellIdx, int a_faceIdx) const</arglist>
    </member>
    <member kind="enumeration" protection="private">
      <type></type>
      <name>XmUGridCacheHolder</name>
      <anchorfile>classxms_1_1_xm_u_grid_1_1_impl.html</anchorfile>
      <anchor>add50ec06c2d860dd6d020847a0e23643</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue" protection="private">
      <name>NEEDS_CALCULATION</name>
      <anchorfile>classxms_1_1_xm_u_grid_1_1_impl.html</anchorfile>
      <anchor>add50ec06c2d860dd6d020847a0e23643ae0e3f54004ccff9594d88272ab05c741</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue" protection="private">
      <name>NEEDS_CALCULATION</name>
      <anchorfile>classxms_1_1_xm_u_grid_1_1_impl.html</anchorfile>
      <anchor>add50ec06c2d860dd6d020847a0e23643ae0e3f54004ccff9594d88272ab05c741</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>UpdateLinks</name>
      <anchorfile>classxms_1_1_xm_u_grid_1_1_impl.html</anchorfile>
      <anchor>ae9cea863c5fb47e52d186d0625f3a20c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>UpdateCellLinks</name>
      <anchorfile>classxms_1_1_xm_u_grid_1_1_impl.html</anchorfile>
      <anchor>af0d3298e3c009aa57767c7cf4f069857</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>UpdatePointLinks</name>
      <anchorfile>classxms_1_1_xm_u_grid_1_1_impl.html</anchorfile>
      <anchor>aa2c3f8e0eff7312c86d3c3fcaa9c5e71</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>SetModified</name>
      <anchorfile>classxms_1_1_xm_u_grid_1_1_impl.html</anchorfile>
      <anchor>a9173fe0edfd36179cb1966ba84ab0f76</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type>bool</type>
      <name>IsCellValidWithPointChange</name>
      <anchorfile>classxms_1_1_xm_u_grid_1_1_impl.html</anchorfile>
      <anchor>a09ae3b174d5af42dfd469a9958b2ae88</anchor>
      <arglist>(int a_cellIdx, int a_changedPtIdx, const Pt3d &amp;a_newPosition) const</arglist>
    </member>
    <member kind="function" protection="private">
      <type>bool</type>
      <name>IsValidCellIdx</name>
      <anchorfile>classxms_1_1_xm_u_grid_1_1_impl.html</anchorfile>
      <anchor>a65105ba803d2b8f4549af16f1288935b</anchor>
      <arglist>(int a_cellIdx) const</arglist>
    </member>
    <member kind="function" protection="private">
      <type>int</type>
      <name>GetNumberOfItemsForCell</name>
      <anchorfile>classxms_1_1_xm_u_grid_1_1_impl.html</anchorfile>
      <anchor>afdde3f12fd80141fdeab7e056dbcd5b9</anchor>
      <arglist>(int a_cellIdx) const</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>GetCellCellstream</name>
      <anchorfile>classxms_1_1_xm_u_grid_1_1_impl.html</anchorfile>
      <anchor>afac6948e8c1c37280dd423f6a39e7d89</anchor>
      <arglist>(int a_cellIdx, const int **a_start, int &amp;a_length) const</arglist>
    </member>
    <member kind="function" protection="private">
      <type>int</type>
      <name>GetNumberOfPolyhedronEdges</name>
      <anchorfile>classxms_1_1_xm_u_grid_1_1_impl.html</anchorfile>
      <anchor>abdfb807435a7f365bc7d4fedd0767264</anchor>
      <arglist>(int a_cellIdx) const</arglist>
    </member>
    <member kind="function" protection="private">
      <type>bool</type>
      <name>GetPlanViewPolygon2d</name>
      <anchorfile>classxms_1_1_xm_u_grid_1_1_impl.html</anchorfile>
      <anchor>a423be87a3285264990c74768176a7766</anchor>
      <arglist>(int a_cellIdx, VecPt3d &amp;a_polygon) const</arglist>
    </member>
    <member kind="function" protection="private">
      <type>bool</type>
      <name>GetPlanViewPolygon3d</name>
      <anchorfile>classxms_1_1_xm_u_grid_1_1_impl.html</anchorfile>
      <anchor>a1f0e7082ce341f6a8e56c899cf19f123</anchor>
      <arglist>(int a_cellIdx, VecPt3d &amp;a_polygon) const</arglist>
    </member>
    <member kind="function" protection="private">
      <type>bool</type>
      <name>IsFaceSide</name>
      <anchorfile>classxms_1_1_xm_u_grid_1_1_impl.html</anchorfile>
      <anchor>a303c120693eb4565e57a2c3dfa26fe7b</anchor>
      <arglist>(const VecInt &amp;a_facePts) const</arglist>
    </member>
    <member kind="function" protection="private">
      <type>bool</type>
      <name>GetCellXySegments</name>
      <anchorfile>classxms_1_1_xm_u_grid_1_1_impl.html</anchorfile>
      <anchor>af17d4e776fa180ddcda3c6802d6d6515</anchor>
      <arglist>(int cellIdx, VecPt3d &amp;a_segments) const</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>GetEdgesOfFace</name>
      <anchorfile>classxms_1_1_xm_u_grid_1_1_impl.html</anchorfile>
      <anchor>ac5bcbe6cca697450c07882ba7491e946</anchor>
      <arglist>(const VecInt &amp;a_face, std::vector&lt; XmEdge &gt; &amp;a_edges) const</arglist>
    </member>
    <member kind="function" protection="private">
      <type>bool</type>
      <name>DoEdgesCrossWithPointChange</name>
      <anchorfile>classxms_1_1_xm_u_grid_1_1_impl.html</anchorfile>
      <anchor>a9e7bda59308fa62bd96f6cd77cd46200</anchor>
      <arglist>(int a_changedPtIdx, const Pt3d &amp;a_newPosition, const std::vector&lt; XmEdge &gt; &amp;a_edges) const</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>GetExtentsFromPoints</name>
      <anchorfile>classxms_1_1_xm_u_grid_1_1_impl.html</anchorfile>
      <anchor>a360af39400414b2be2c433dd94260f37</anchor>
      <arglist>(const VecPt3d &amp;a_locations, Pt3d &amp;a_min, Pt3d &amp;a_max) const</arglist>
    </member>
    <member kind="function" protection="private">
      <type>bool</type>
      <name>GetFaceXySegments</name>
      <anchorfile>classxms_1_1_xm_u_grid_1_1_impl.html</anchorfile>
      <anchor>ade7231cbe2ea12da7fa51bcab64118be</anchor>
      <arglist>(int a_cellIdx, int a_faceIdx, VecPt3d &amp;a_segments) const</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>CalculateCacheValues</name>
      <anchorfile>classxms_1_1_xm_u_grid_1_1_impl.html</anchorfile>
      <anchor>ae85717c35acdc3db675b3f7b19b8d642</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>ClearCacheValues</name>
      <anchorfile>classxms_1_1_xm_u_grid_1_1_impl.html</anchorfile>
      <anchor>a890c84b58b098e06e6fd91ffb002faa2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type>int</type>
      <name>GetCell3dFaceCountNoCache</name>
      <anchorfile>classxms_1_1_xm_u_grid_1_1_impl.html</anchorfile>
      <anchor>a151a304ca08a4ec637514eb41682184d</anchor>
      <arglist>(int a_cellIdx) const</arglist>
    </member>
    <member kind="function" protection="private">
      <type>int</type>
      <name>GetCell3dFaceAdjacentCellNoCache</name>
      <anchorfile>classxms_1_1_xm_u_grid_1_1_impl.html</anchorfile>
      <anchor>a37877445f73c5ed1404006f36a5be432</anchor>
      <arglist>(int a_cellIdx, int a_faceIdx) const</arglist>
    </member>
    <member kind="function" protection="private">
      <type>XmUGridFaceOrientation</type>
      <name>GetCell3dFaceOrientationNoCache</name>
      <anchorfile>classxms_1_1_xm_u_grid_1_1_impl.html</anchorfile>
      <anchor>a803cc3e0de7ca5daf52711525cf82caa</anchor>
      <arglist>(int a_cellIdx, int a_faceIdx) const</arglist>
    </member>
    <member kind="function" protection="private">
      <type>bool</type>
      <name>GetNextFaceColumn</name>
      <anchorfile>classxms_1_1_xm_u_grid_1_1_impl.html</anchorfile>
      <anchor>a69ed57719e5e3c73c42b41b2936aca50</anchor>
      <arglist>(const VecInt &amp;a_facePoints, int a_starti, int &amp;a_columnBegin, int &amp;a_columnEnd) const</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>GetFacePointSegments</name>
      <anchorfile>classxms_1_1_xm_u_grid_1_1_impl.html</anchorfile>
      <anchor>a28356424189ea421a4d7cd3464b8f564</anchor>
      <arglist>(const VecInt &amp;a_facePts, int a_columnBegin, int a_columnEnd, VecPt3d &amp;a_segments) const</arglist>
    </member>
    <member kind="function" protection="private">
      <type>XmUGridFaceOrientation</type>
      <name>FaceOrientationWithFail</name>
      <anchorfile>classxms_1_1_xm_u_grid_1_1_impl.html</anchorfile>
      <anchor>aad48cc3e2385f9c5c67739e3f48543de</anchor>
      <arglist>(int a_cellIdx, int a_faceIdx) const</arglist>
    </member>
    <member kind="function" protection="private" static="yes">
      <type>static int</type>
      <name>DimensionFromCellType</name>
      <anchorfile>classxms_1_1_xm_u_grid_1_1_impl.html</anchorfile>
      <anchor>a0ca4d25cab8b22c82957a5d860fd973a</anchor>
      <arglist>(XmUGridCellType a_cellType)</arglist>
    </member>
    <member kind="function" protection="private" static="yes">
      <type>static void</type>
      <name>GetUniquePointsFromPolyhedronCellstream</name>
      <anchorfile>classxms_1_1_xm_u_grid_1_1_impl.html</anchorfile>
      <anchor>a2aa5396a2523183b70859fdec932c81c</anchor>
      <arglist>(const VecInt &amp;a_cellstream, int a_numCellItems, int &amp;a_currIdx, VecInt &amp;a_uniqueGetCellPoints, VecInt &amp;a_pointLastUsedIdx)</arglist>
    </member>
    <member kind="function" protection="private" static="yes">
      <type>static bool</type>
      <name>GetUniquePointsFromPolyhedronSingleCellstream</name>
      <anchorfile>classxms_1_1_xm_u_grid_1_1_impl.html</anchorfile>
      <anchor>a16cdc5cef949b02ceccc5c7f4d890edd</anchor>
      <arglist>(const VecInt &amp;a_cellstream, VecInt &amp;a_cellPoints)</arglist>
    </member>
    <member kind="function" protection="private" static="yes">
      <type>static void</type>
      <name>GetUniqueEdgesFromPolyhedronCellstream</name>
      <anchorfile>classxms_1_1_xm_u_grid_1_1_impl.html</anchorfile>
      <anchor>a95dbd634d789083141c3b41a43d44c38</anchor>
      <arglist>(const int *a_start, int &amp;a_length, boost::container::flat_set&lt; XmEdge &gt; &amp;a_cellEdges, int &amp;a_currIdx)</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>VecPt3d</type>
      <name>m_locations</name>
      <anchorfile>classxms_1_1_xm_u_grid_1_1_impl.html</anchorfile>
      <anchor>ae3d833b1ec45a6f7996df86552081656</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>VecInt</type>
      <name>m_cellstream</name>
      <anchorfile>classxms_1_1_xm_u_grid_1_1_impl.html</anchorfile>
      <anchor>a74a2368c058266c3e9a08b9104e7e80d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>VecInt</type>
      <name>m_cellIdxToStreamIdx</name>
      <anchorfile>classxms_1_1_xm_u_grid_1_1_impl.html</anchorfile>
      <anchor>a0148bf16323202eb86e82758190cc973</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>VecInt</type>
      <name>m_pointsToCells</name>
      <anchorfile>classxms_1_1_xm_u_grid_1_1_impl.html</anchorfile>
      <anchor>ab82f892ad0046c1bf604d3abc8514507</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>VecInt</type>
      <name>m_pointIdxToPointsToCells</name>
      <anchorfile>classxms_1_1_xm_u_grid_1_1_impl.html</anchorfile>
      <anchor>a3eba8986328cb0b0b5bde2142b38c091</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>bool</type>
      <name>m_modified</name>
      <anchorfile>classxms_1_1_xm_u_grid_1_1_impl.html</anchorfile>
      <anchor>aed34d7849e34999cbc0f08dfe33b14fe</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>bool</type>
      <name>m_useCache</name>
      <anchorfile>classxms_1_1_xm_u_grid_1_1_impl.html</anchorfile>
      <anchor>a20f333aa5bd6ff6ac93ec6e9d7450c97</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>VecInt</type>
      <name>m_numberOfFaces</name>
      <anchorfile>classxms_1_1_xm_u_grid_1_1_impl.html</anchorfile>
      <anchor>a9e6a3c30576007664d17c83fda231cf4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>VecInt</type>
      <name>m_cellFaceOffset</name>
      <anchorfile>classxms_1_1_xm_u_grid_1_1_impl.html</anchorfile>
      <anchor>a004dd9aca169c7579009fb3756bdab91</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>VecInt</type>
      <name>m_faceOrientation</name>
      <anchorfile>classxms_1_1_xm_u_grid_1_1_impl.html</anchorfile>
      <anchor>aed7dfe7457ed5ffbd58e47e8980335f0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>VecInt</type>
      <name>m_faceNeighbor</name>
      <anchorfile>classxms_1_1_xm_u_grid_1_1_impl.html</anchorfile>
      <anchor>a23f3488b84af2975bfc39c44d5d2367d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>VecInt</type>
      <name>m_cellDimensionCounts</name>
      <anchorfile>classxms_1_1_xm_u_grid_1_1_impl.html</anchorfile>
      <anchor>a543a4cf657143a4fc3ca29c1595395d7</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>xms::ix</name>
    <filename>classxms_1_1ix.html</filename>
    <member kind="function">
      <type></type>
      <name>ix</name>
      <anchorfile>classxms_1_1ix.html</anchorfile>
      <anchor>ab86596c140cee4b9ad0bc1e0865c3c2a</anchor>
      <arglist>(Pt3d a_pt, int a_i, double a_t)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator==</name>
      <anchorfile>classxms_1_1ix.html</anchorfile>
      <anchor>ad7ebc7d3dfc72319be03ff49294aae00</anchor>
      <arglist>(const ix &amp;rhs)</arglist>
    </member>
    <member kind="variable">
      <type>Pt3d</type>
      <name>m_pt</name>
      <anchorfile>classxms_1_1ix.html</anchorfile>
      <anchor>a6a4aaf5674e38b0b1ff89f00afc9c32e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>m_i</name>
      <anchorfile>classxms_1_1ix.html</anchorfile>
      <anchor>a4185fe410fd0c5b45dc440483e745b15</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>double</type>
      <name>m_t</name>
      <anchorfile>classxms_1_1ix.html</anchorfile>
      <anchor>ab40238d7edca655589518e4688d1aa49</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>PtSearchUnitTests</name>
    <filename>class_pt_search_unit_tests.html</filename>
    <member kind="function">
      <type>void</type>
      <name>testCreateClass</name>
      <anchorfile>class_pt_search_unit_tests.html</anchorfile>
      <anchor>a8e322359ace1af03b7ed680f5295693b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testTest2d</name>
      <anchorfile>class_pt_search_unit_tests.html</anchorfile>
      <anchor>a73d2a85aa0fbc316a421dcf912981fa8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testTest2dTutData</name>
      <anchorfile>class_pt_search_unit_tests.html</anchorfile>
      <anchor>add78e0a8851b7ac7f7a2410a1b1fa5b1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testTest3d</name>
      <anchorfile>class_pt_search_unit_tests.html</anchorfile>
      <anchor>a7f493292989b1e6e6c5d01516d5b2d64</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testTest3dOct</name>
      <anchorfile>class_pt_search_unit_tests.html</anchorfile>
      <anchor>a5d78214e1fef2096a0c61d36399c7584</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testActivity2d</name>
      <anchorfile>class_pt_search_unit_tests.html</anchorfile>
      <anchor>a9c68362b8c6522297a6b4f987428fb74</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testActivity3d</name>
      <anchorfile>class_pt_search_unit_tests.html</anchorfile>
      <anchor>a5070b8bb3b9419bbd813a56e42899455</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testPtsWithinDist</name>
      <anchorfile>class_pt_search_unit_tests.html</anchorfile>
      <anchor>a24c64ac92355da4e5384c20b9279acc3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testVectorThatGrows</name>
      <anchorfile>class_pt_search_unit_tests.html</anchorfile>
      <anchor>ac74456c2b966531869f579c2a7875740</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>xms::TrAutoFixFourTrianglePts</name>
    <filename>classxms_1_1_tr_auto_fix_four_triangle_pts.html</filename>
    <member kind="function" static="yes">
      <type>static BSHP&lt; TrAutoFixFourTrianglePts &gt;</type>
      <name>New</name>
      <anchorfile>classxms_1_1_tr_auto_fix_four_triangle_pts.html</anchorfile>
      <anchor>a58773a2774574706c01b09c1d1ac3048</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>xms::TrAutoFixFourTrianglePtsImpl</name>
    <filename>classxms_1_1_tr_auto_fix_four_triangle_pts_impl.html</filename>
    <base>xms::TrAutoFixFourTrianglePts</base>
    <member kind="function">
      <type></type>
      <name>TrAutoFixFourTrianglePtsImpl</name>
      <anchorfile>classxms_1_1_tr_auto_fix_four_triangle_pts_impl.html</anchorfile>
      <anchor>a0f4600beeb16d689a3e0b32230506cff</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>Fix</name>
      <anchorfile>classxms_1_1_tr_auto_fix_four_triangle_pts_impl.html</anchorfile>
      <anchor>af147444a1e2e287a72e382f30692cf0c</anchor>
      <arglist>(BSHP&lt; TrTin &gt; a_tin) override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>SetObserver</name>
      <anchorfile>classxms_1_1_tr_auto_fix_four_triangle_pts_impl.html</anchorfile>
      <anchor>a9e38e41ebbd28ca092257ea1809ea731</anchor>
      <arglist>(BSHP&lt; Observer &gt; a_) override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>SetUndeleteablePtIdxs</name>
      <anchorfile>classxms_1_1_tr_auto_fix_four_triangle_pts_impl.html</anchorfile>
      <anchor>a0c5da7045cd27850ac698f3f06f48379</anchor>
      <arglist>(VecInt &amp;a_ptIdx) override</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>FillAdjTrisIfNeeded</name>
      <anchorfile>classxms_1_1_tr_auto_fix_four_triangle_pts_impl.html</anchorfile>
      <anchor>a7bafc03b8a5a97ba3f8fea1ce5238aa8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>GetPtsAndTrisToDelete</name>
      <anchorfile>classxms_1_1_tr_auto_fix_four_triangle_pts_impl.html</anchorfile>
      <anchor>a295a366f04639d09928b3d8295fd8e2c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::pair&lt; int, int &gt;</type>
      <name>EdgeOppositePt</name>
      <anchorfile>classxms_1_1_tr_auto_fix_four_triangle_pts_impl.html</anchorfile>
      <anchor>a68551fa49d119b1e7d6ed1a47b69ca9c</anchor>
      <arglist>(int a_ptIdx, int a_tri, VecInt &amp;a_tris)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>MakeTwoNewTriangles</name>
      <anchorfile>classxms_1_1_tr_auto_fix_four_triangle_pts_impl.html</anchorfile>
      <anchor>a98dd5e7d4469d59171b8497e99463d25</anchor>
      <arglist>(VecPt3d &amp;a_pts, std::map&lt; int, int &gt; a_edges, int a_tris[2][3])</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>ReplaceTriangle</name>
      <anchorfile>classxms_1_1_tr_auto_fix_four_triangle_pts_impl.html</anchorfile>
      <anchor>a4ddad45d4285e669efb1e7b5881ad957</anchor>
      <arglist>(int &amp;a_tIdx, int a_newTri[3], VecInt &amp;a_tris)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>RenumberPts</name>
      <anchorfile>classxms_1_1_tr_auto_fix_four_triangle_pts_impl.html</anchorfile>
      <anchor>aae03f8c6f46aea41f01595b0e83d565a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>RenumberTris</name>
      <anchorfile>classxms_1_1_tr_auto_fix_four_triangle_pts_impl.html</anchorfile>
      <anchor>a1c685b02542d9985b962f6dfc04be6c5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>RemovePts</name>
      <anchorfile>classxms_1_1_tr_auto_fix_four_triangle_pts_impl.html</anchorfile>
      <anchor>a8c1abb56f3123fc5a41e7ac155e4a886</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>RemoveTris</name>
      <anchorfile>classxms_1_1_tr_auto_fix_four_triangle_pts_impl.html</anchorfile>
      <anchor>a94350c394e0cab1a5491210257567dff</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>ClearAdjTrisIfCreated</name>
      <anchorfile>classxms_1_1_tr_auto_fix_four_triangle_pts_impl.html</anchorfile>
      <anchor>a359ac2134d3f2bc3b4c0c551f1cd27d7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>BSHP&lt; TrTin &gt;</type>
      <name>m_tin</name>
      <anchorfile>classxms_1_1_tr_auto_fix_four_triangle_pts_impl.html</anchorfile>
      <anchor>a6df5fba0dfca93533acc9febafc732b0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>BSHP&lt; Observer &gt;</type>
      <name>m_observer</name>
      <anchorfile>classxms_1_1_tr_auto_fix_four_triangle_pts_impl.html</anchorfile>
      <anchor>af0f22a3314f8a951657a112e3dc61a11</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>bool</type>
      <name>m_removeAdjTris</name>
      <anchorfile>classxms_1_1_tr_auto_fix_four_triangle_pts_impl.html</anchorfile>
      <anchor>a28c1a4f2b4c06c2d3e5915499fbce30a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>SetInt</type>
      <name>m_ptsToDelete</name>
      <anchorfile>classxms_1_1_tr_auto_fix_four_triangle_pts_impl.html</anchorfile>
      <anchor>aecab7c30b6be74785e7708750940ea81</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>SetInt</type>
      <name>m_trisToDelete</name>
      <anchorfile>classxms_1_1_tr_auto_fix_four_triangle_pts_impl.html</anchorfile>
      <anchor>a8decce1f1994328ae11f20eb08efe780</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>SetInt</type>
      <name>m_noDelete</name>
      <anchorfile>classxms_1_1_tr_auto_fix_four_triangle_pts_impl.html</anchorfile>
      <anchor>ab1b475420cf47491c7600270b02dbee5</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>TrAutoFixFourTrianglePtsUnitTests</name>
    <filename>class_tr_auto_fix_four_triangle_pts_unit_tests.html</filename>
    <member kind="function">
      <type>void</type>
      <name>test1</name>
      <anchorfile>class_tr_auto_fix_four_triangle_pts_unit_tests.html</anchorfile>
      <anchor>ab21bd9cb12084ff3dc1eb734f2626081</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>xms::TrBreaklineAdder</name>
    <filename>classxms_1_1_tr_breakline_adder.html</filename>
    <member kind="function" static="yes">
      <type>static boost::shared_ptr&lt; TrBreaklineAdder &gt;</type>
      <name>New</name>
      <anchorfile>classxms_1_1_tr_breakline_adder.html</anchorfile>
      <anchor>abdc62fc265ddc89580ad12885076c9c9</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>xms::TrBreaklineAdderImpl</name>
    <filename>classxms_1_1_tr_breakline_adder_impl.html</filename>
    <base>xms::TrBreaklineAdder</base>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>SetObserver</name>
      <anchorfile>classxms_1_1_tr_breakline_adder_impl.html</anchorfile>
      <anchor>a1efc7eeb292ed74fb20c505f8c63245c</anchor>
      <arglist>(BSHP&lt; Observer &gt; a_) override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>SetTin</name>
      <anchorfile>classxms_1_1_tr_breakline_adder_impl.html</anchorfile>
      <anchor>a14da3950a8bad04e99e01118ff098c67</anchor>
      <arglist>(BSHP&lt; TrTin &gt; a_tin, double a_tol=-1) override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>AddBreakline</name>
      <anchorfile>classxms_1_1_tr_breakline_adder_impl.html</anchorfile>
      <anchor>a7190431ec5a664f390974a1b9e6a7e16</anchor>
      <arglist>(const VecInt &amp;a_breakline) override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>AddBreaklines</name>
      <anchorfile>classxms_1_1_tr_breakline_adder_impl.html</anchorfile>
      <anchor>afdc00ed49ed8eebd1d0d40085158ee8a</anchor>
      <arglist>(const VecInt2d &amp;a_breakline) override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual std::string</type>
      <name>ErrorMessage</name>
      <anchorfile>classxms_1_1_tr_breakline_adder_impl.html</anchorfile>
      <anchor>aa4036d3ba5e6ab3e3b9eba71cae6dbc3</anchor>
      <arglist>(int) const override</arglist>
    </member>
    <member kind="function" protection="private">
      <type>bool</type>
      <name>GetExtents</name>
      <anchorfile>classxms_1_1_tr_breakline_adder_impl.html</anchorfile>
      <anchor>a330e8badc1b3f6f14c95c07d66ba709c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>ComputeTolerance</name>
      <anchorfile>classxms_1_1_tr_breakline_adder_impl.html</anchorfile>
      <anchor>ae71390adafd684e944c4e5ba132eb1a3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type>bool</type>
      <name>CrossesBoundary</name>
      <anchorfile>classxms_1_1_tr_breakline_adder_impl.html</anchorfile>
      <anchor>a239990bf3ccb0b3039d1e02ce7fb10f6</anchor>
      <arglist>(int a_blpt1, int a_blpt2)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>ProcessSegmentBySwapping</name>
      <anchorfile>classxms_1_1_tr_breakline_adder_impl.html</anchorfile>
      <anchor>a741b37559be486816ba50cf36ea75b7e</anchor>
      <arglist>(int a_vtx1, int a_vtx2)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>GetIntersectingEdges</name>
      <anchorfile>classxms_1_1_tr_breakline_adder_impl.html</anchorfile>
      <anchor>acb8d69c9277b12db44ff851377264652</anchor>
      <arglist>(int a_blpt1, int a_blpt2, VecEdge &amp;a_edges)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>FindIntersectingEdgeFromPoint</name>
      <anchorfile>classxms_1_1_tr_breakline_adder_impl.html</anchorfile>
      <anchor>a3cb98a64932a06a92665236dceb7b1fe</anchor>
      <arglist>(int a_blpt1, int a_blpt2, int *a_intpt1, int *a_intpt2, double *a_x, double *a_y, double *a_z1, double *a_z2)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>FindIntersectingEdgeFromEdge</name>
      <anchorfile>classxms_1_1_tr_breakline_adder_impl.html</anchorfile>
      <anchor>a25e0d6e4454a500d1720681e023aecb3</anchor>
      <arglist>(int a_ept1, int a_ept2, int a_blpt1, int a_blpt2, int *a_intpt1, int *a_intpt2, double *a_x, double *a_y, double *a_z1, double *a_z2)</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>BSHP&lt; TrTin &gt;</type>
      <name>m_tin</name>
      <anchorfile>classxms_1_1_tr_breakline_adder_impl.html</anchorfile>
      <anchor>a3e1ef5566a50db9c950ad3f25f87b7eb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>BSHP&lt; Observer &gt;</type>
      <name>m_observer</name>
      <anchorfile>classxms_1_1_tr_breakline_adder_impl.html</anchorfile>
      <anchor>a4d101ef2d3e4e463803db9f05373ab13</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>double</type>
      <name>m_xyTol</name>
      <anchorfile>classxms_1_1_tr_breakline_adder_impl.html</anchorfile>
      <anchor>a78e61b3d04bb68dc283c2b4170270e11</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>VecInt *</type>
      <name>m_tris</name>
      <anchorfile>classxms_1_1_tr_breakline_adder_impl.html</anchorfile>
      <anchor>a4832c9d590ee0eade459297b359e4636</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>VecPt3d *</type>
      <name>m_pts</name>
      <anchorfile>classxms_1_1_tr_breakline_adder_impl.html</anchorfile>
      <anchor>a0f1ea456ca21a815d85be9befa601b84</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>VecInt2d *</type>
      <name>m_trisAdjToPts</name>
      <anchorfile>classxms_1_1_tr_breakline_adder_impl.html</anchorfile>
      <anchor>a6255379baf587e613b1d8a4f25f9f690</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>Pt3d</type>
      <name>m_mn</name>
      <anchorfile>classxms_1_1_tr_breakline_adder_impl.html</anchorfile>
      <anchor>a75db23f8349bd1002d3981d2786e4cad</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>Pt3d</type>
      <name>m_mx</name>
      <anchorfile>classxms_1_1_tr_breakline_adder_impl.html</anchorfile>
      <anchor>aafff781bcf0960594d71e1ef7acad578</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>BSHP&lt; GmMultiPolyIntersector &gt;</type>
      <name>m_multiPolyIntersector</name>
      <anchorfile>classxms_1_1_tr_breakline_adder_impl.html</anchorfile>
      <anchor>a73d62e228718e67c814d3669eef1cf27</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>BSHP&lt; GmPtSearch &gt;</type>
      <name>m_searcher</name>
      <anchorfile>classxms_1_1_tr_breakline_adder_impl.html</anchorfile>
      <anchor>ae928c362b7672a133aee9b3babf50637</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>TrBreaklineAdderUnitTests</name>
    <filename>class_tr_breakline_adder_unit_tests.html</filename>
    <member kind="function">
      <type>void</type>
      <name>test1</name>
      <anchorfile>class_tr_breakline_adder_unit_tests.html</anchorfile>
      <anchor>aed5fc7ad1065440d05eb8e4387a19d6a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>test2</name>
      <anchorfile>class_tr_breakline_adder_unit_tests.html</anchorfile>
      <anchor>a29102789708793c51d7204d464c31e34</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testCrossingBoundary</name>
      <anchorfile>class_tr_breakline_adder_unit_tests.html</anchorfile>
      <anchor>af46bc719d5a27acd4a02f4f6ba2ea27d</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>TriSearchUnitTests</name>
    <filename>class_tri_search_unit_tests.html</filename>
    <member kind="function">
      <type>void</type>
      <name>testCreateClass</name>
      <anchorfile>class_tri_search_unit_tests.html</anchorfile>
      <anchor>ab3d5e1da43f73a8071876dc0516fead6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testInterpWeights</name>
      <anchorfile>class_tri_search_unit_tests.html</anchorfile>
      <anchor>a1364caa71954c0da28fe0be43b104c02</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testPtActivity</name>
      <anchorfile>class_tri_search_unit_tests.html</anchorfile>
      <anchor>ad3db5f8baf65200980ce9ce64cf4e076</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testTriActivity</name>
      <anchorfile>class_tri_search_unit_tests.html</anchorfile>
      <anchor>aaafe145f2ebb470f3604248b2a26c3fd</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testSmsCase1</name>
      <anchorfile>class_tri_search_unit_tests.html</anchorfile>
      <anchor>a5d1aa17f366ee0dddf326af59b775b8e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testTouch</name>
      <anchorfile>class_tri_search_unit_tests.html</anchorfile>
      <anchor>af0c83cdfee2822cd88b5e784e5d646ea</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testTriEnvelopesOverlap</name>
      <anchorfile>class_tri_search_unit_tests.html</anchorfile>
      <anchor>a9115acc6d9662f1d757bb082cb730450</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>xms::TrOuterTriangleDeleter</name>
    <filename>classxms_1_1_tr_outer_triangle_deleter.html</filename>
    <member kind="function" static="yes">
      <type>static boost::shared_ptr&lt; TrOuterTriangleDeleter &gt;</type>
      <name>New</name>
      <anchorfile>classxms_1_1_tr_outer_triangle_deleter.html</anchorfile>
      <anchor>a0c647ff8f268d6f6cf8d46f2327a7f8f</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>xms::TrOuterTriangleDeleterImpl</name>
    <filename>classxms_1_1_tr_outer_triangle_deleter_impl.html</filename>
    <base>xms::TrOuterTriangleDeleter</base>
    <member kind="enumeration">
      <type></type>
      <name>BoundaryEnum</name>
      <anchorfile>classxms_1_1_tr_outer_triangle_deleter_impl.html</anchorfile>
      <anchor>af029069b0274826a71ae5677357d8041</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>TrOuterTriangleDeleterImpl</name>
      <anchorfile>classxms_1_1_tr_outer_triangle_deleter_impl.html</anchorfile>
      <anchor>a71d9018e45d0db42a74cfdaf97c9d108</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>Delete</name>
      <anchorfile>classxms_1_1_tr_outer_triangle_deleter_impl.html</anchorfile>
      <anchor>ae68038220e16a9ad8cfb09088ec18b05</anchor>
      <arglist>(const VecInt2d &amp;a_polys, BSHP&lt; TrTin &gt; a_tin) override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>SetObserver</name>
      <anchorfile>classxms_1_1_tr_outer_triangle_deleter_impl.html</anchorfile>
      <anchor>abc04a864841bfbb4d75978de497eaed0</anchor>
      <arglist>(BSHP&lt; Observer &gt; a_) override</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>FlagTrianglesAlongPolygon</name>
      <anchorfile>classxms_1_1_tr_outer_triangle_deleter_impl.html</anchorfile>
      <anchor>af243755c164dc8b6af8504aa6a037b8d</anchor>
      <arglist>(const VecInt &amp;a_poly, VecInt &amp;a_flags)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>MarkNeighbors</name>
      <anchorfile>classxms_1_1_tr_outer_triangle_deleter_impl.html</anchorfile>
      <anchor>a98c87038a67b2dbad2caa84d97700b1a</anchor>
      <arglist>(VecInt &amp;a_flags)</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>VecInt2d</type>
      <name>m_polys</name>
      <anchorfile>classxms_1_1_tr_outer_triangle_deleter_impl.html</anchorfile>
      <anchor>a4c2c88e77f16bda161d8ce8811688fb5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>BSHP&lt; TrTin &gt;</type>
      <name>m_tin</name>
      <anchorfile>classxms_1_1_tr_outer_triangle_deleter_impl.html</anchorfile>
      <anchor>acf5005baf48c97e177782c0926d4644b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>BSHP&lt; Observer &gt;</type>
      <name>m_observer</name>
      <anchorfile>classxms_1_1_tr_outer_triangle_deleter_impl.html</anchorfile>
      <anchor>ac7c0d7113b1bcc08e14becfbf66fb449</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>TrOuterTriangleDeleterUnitTests</name>
    <filename>class_tr_outer_triangle_deleter_unit_tests.html</filename>
    <member kind="function">
      <type>void</type>
      <name>test1</name>
      <anchorfile>class_tr_outer_triangle_deleter_unit_tests.html</anchorfile>
      <anchor>a294ae02e69ef1ba5ee88016a54af2882</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>xms::TrTin</name>
    <filename>classxms_1_1_tr_tin.html</filename>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~TrTin</name>
      <anchorfile>classxms_1_1_tr_tin.html</anchorfile>
      <anchor>acbac3ff7b8a488bec68feace756d1234</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static BSHP&lt; TrTin &gt;</type>
      <name>New</name>
      <anchorfile>classxms_1_1_tr_tin.html</anchorfile>
      <anchor>ab1227a106b70c3061bd03cb3fb9833a7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type></type>
      <name>TrTin</name>
      <anchorfile>classxms_1_1_tr_tin.html</anchorfile>
      <anchor>a13e29683d761b3f8e663c2a69098bfd3</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>xms::TrTinImpl</name>
    <filename>classxms_1_1_tr_tin_impl.html</filename>
    <base>xms::TrTin</base>
    <member kind="function">
      <type></type>
      <name>TrTinImpl</name>
      <anchorfile>classxms_1_1_tr_tin_impl.html</anchorfile>
      <anchor>adec0a5b6a63e3dd34c1871b1c7d8b52f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~TrTinImpl</name>
      <anchorfile>classxms_1_1_tr_tin_impl.html</anchorfile>
      <anchor>a73d34d1e66565922cbe1b440094b128a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>SetPoints</name>
      <anchorfile>classxms_1_1_tr_tin_impl.html</anchorfile>
      <anchor>a0c46d52ba123ea89d983831713de21de</anchor>
      <arglist>(BSHP&lt; VecPt3d &gt; a_pts) override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>SetTriangles</name>
      <anchorfile>classxms_1_1_tr_tin_impl.html</anchorfile>
      <anchor>ad93d04787d4dba68f1bdb521cfbc8486</anchor>
      <arglist>(BSHP&lt; VecInt &gt; a_tris) override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>SetTrianglesAdjacentToPoints</name>
      <anchorfile>classxms_1_1_tr_tin_impl.html</anchorfile>
      <anchor>a3ece59ead0d9335a0039c1d0cec4f5f7</anchor>
      <arglist>(BSHP&lt; VecInt2d &gt; a_trisAdjToPts) override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>SetGeometry</name>
      <anchorfile>classxms_1_1_tr_tin_impl.html</anchorfile>
      <anchor>a4a7c309bad7babf5b2e0e7e46ee626a5</anchor>
      <arglist>(BSHP&lt; VecPt3d &gt; a_pts, BSHP&lt; VecInt &gt; a_tris, BSHP&lt; VecInt2d &gt; a_trisAdjToPts) override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual VecPt3d &amp;</type>
      <name>Points</name>
      <anchorfile>classxms_1_1_tr_tin_impl.html</anchorfile>
      <anchor>a4722de3f7981842b5fbfc5f48dc72c95</anchor>
      <arglist>() override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual VecInt &amp;</type>
      <name>Triangles</name>
      <anchorfile>classxms_1_1_tr_tin_impl.html</anchorfile>
      <anchor>abaddc41c2727beca5ffc08a94aa9b6e1</anchor>
      <arglist>() override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual VecInt2d &amp;</type>
      <name>TrisAdjToPts</name>
      <anchorfile>classxms_1_1_tr_tin_impl.html</anchorfile>
      <anchor>a8dbab5f6b33aeb379c704a7b2343269a</anchor>
      <arglist>() override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const VecPt3d &amp;</type>
      <name>Points</name>
      <anchorfile>classxms_1_1_tr_tin_impl.html</anchorfile>
      <anchor>a0db58a1aa456297fd3bd5a6807dd355d</anchor>
      <arglist>() const override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const VecInt &amp;</type>
      <name>Triangles</name>
      <anchorfile>classxms_1_1_tr_tin_impl.html</anchorfile>
      <anchor>a5560841bc5a87539eb17a6af8bdd3839</anchor>
      <arglist>() const override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const VecInt2d &amp;</type>
      <name>TrisAdjToPts</name>
      <anchorfile>classxms_1_1_tr_tin_impl.html</anchorfile>
      <anchor>a477102512bf2d7c9b15c5c6eb49d75f5</anchor>
      <arglist>() const override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual BSHP&lt; VecPt3d &gt;</type>
      <name>PointsPtr</name>
      <anchorfile>classxms_1_1_tr_tin_impl.html</anchorfile>
      <anchor>a1b1b98c5dd65471d090946399f31770b</anchor>
      <arglist>() override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual BSHP&lt; VecInt &gt;</type>
      <name>TrianglesPtr</name>
      <anchorfile>classxms_1_1_tr_tin_impl.html</anchorfile>
      <anchor>a64478436f8fdc5482ce9e9fcea8b42fb</anchor>
      <arglist>() override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>NumPoints</name>
      <anchorfile>classxms_1_1_tr_tin_impl.html</anchorfile>
      <anchor>a376cc601aa1f16cffd49c459fc9c9f7f</anchor>
      <arglist>() const override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>NumTriangles</name>
      <anchorfile>classxms_1_1_tr_tin_impl.html</anchorfile>
      <anchor>a5195a84d6cea132e8066316fbd5ba320</anchor>
      <arglist>() const override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>TriangleFromEdge</name>
      <anchorfile>classxms_1_1_tr_tin_impl.html</anchorfile>
      <anchor>ade7ecff4a4b370270258659328575c0f</anchor>
      <arglist>(int a_pt1, int a_pt2, int &amp;a_tri, int &amp;a_idx1, int &amp;a_idx2) const override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>TriangleAdjacentToEdge</name>
      <anchorfile>classxms_1_1_tr_tin_impl.html</anchorfile>
      <anchor>a388567825f27fe8d6b183125af0cef1c</anchor>
      <arglist>(int a_pt1, int a_pt2) const override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>LocalIndex</name>
      <anchorfile>classxms_1_1_tr_tin_impl.html</anchorfile>
      <anchor>ac60ab20aba505a86b7eaca1a6935f540</anchor>
      <arglist>(int a_tri, int a_pt) const override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>GlobalIndex</name>
      <anchorfile>classxms_1_1_tr_tin_impl.html</anchorfile>
      <anchor>af2da41ae14938890b4fa3b6f1a96ca89</anchor>
      <arglist>(int a_triIdx, int a_localVtxIdx) const override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>VerticesAreAdjacent</name>
      <anchorfile>classxms_1_1_tr_tin_impl.html</anchorfile>
      <anchor>a70f4eb6dd87eb85eaca86e34f11da4fc</anchor>
      <arglist>(int a_pt1, int a_pt2) const override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>CommonEdgeIndex</name>
      <anchorfile>classxms_1_1_tr_tin_impl.html</anchorfile>
      <anchor>afffd7788db43b8ef041f2719fb8d8431</anchor>
      <arglist>(int a_tri, int a_adjTri) const override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>AdjacentTriangle</name>
      <anchorfile>classxms_1_1_tr_tin_impl.html</anchorfile>
      <anchor>ae50a008ac967323421d9574df798d69b</anchor>
      <arglist>(int a_triIdx, int a_edgeIdx) const override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual Pt3d</type>
      <name>TriangleCentroid</name>
      <anchorfile>classxms_1_1_tr_tin_impl.html</anchorfile>
      <anchor>a48c546057a0e95fd7ebe06f7a6aca7de</anchor>
      <arglist>(int a_tri) const override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual double</type>
      <name>TriangleArea</name>
      <anchorfile>classxms_1_1_tr_tin_impl.html</anchorfile>
      <anchor>a5c88f3679d65d282b0a67c6aff1341c6</anchor>
      <arglist>(int a_tri) const override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>NextBoundaryPoint</name>
      <anchorfile>classxms_1_1_tr_tin_impl.html</anchorfile>
      <anchor>ac145283448f45f0b1ac4e5435421a8a2</anchor>
      <arglist>(int a_point) const override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>PreviousBoundaryPoint</name>
      <anchorfile>classxms_1_1_tr_tin_impl.html</anchorfile>
      <anchor>a798082ec079562c1616f0b0a509567a1</anchor>
      <arglist>(int a_point) const override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>GetBoundaryPoints</name>
      <anchorfile>classxms_1_1_tr_tin_impl.html</anchorfile>
      <anchor>a03191327872b758392b0dd2c4fa1f60c</anchor>
      <arglist>(VecInt &amp;a_boundaryPoints) const override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>GetBoundaryPolys</name>
      <anchorfile>classxms_1_1_tr_tin_impl.html</anchorfile>
      <anchor>a8b2ebdfcba14a1d76554c9cd077a7026</anchor>
      <arglist>(VecInt2d &amp;a_polys) const override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>GetExtents</name>
      <anchorfile>classxms_1_1_tr_tin_impl.html</anchorfile>
      <anchor>a7ec5b4c0b8cf8d22eb0251a66f8c3eac</anchor>
      <arglist>(Pt3d &amp;a_mn, Pt3d &amp;a_mx) const override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>ExportTinFile</name>
      <anchorfile>classxms_1_1_tr_tin_impl.html</anchorfile>
      <anchor>a89fad78d3d1f79fbfff7684e9323cc0b</anchor>
      <arglist>(std::ostream &amp;a_os) const override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>SwapEdge</name>
      <anchorfile>classxms_1_1_tr_tin_impl.html</anchorfile>
      <anchor>a1466863471faaca3ac55bf4101fa972f</anchor>
      <arglist>(int a_triA, int a_triB, bool a_checkAngle=true) override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>DeleteTriangles</name>
      <anchorfile>classxms_1_1_tr_tin_impl.html</anchorfile>
      <anchor>a0a160157240d033a400f55c730bb18f6</anchor>
      <arglist>(const SetInt &amp;a_trisToDelete) override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>DeletePoints</name>
      <anchorfile>classxms_1_1_tr_tin_impl.html</anchorfile>
      <anchor>af26463b8da49e0aa9bf2577468c28182</anchor>
      <arglist>(const SetInt &amp;a_points) override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>OptimizeTriangulation</name>
      <anchorfile>classxms_1_1_tr_tin_impl.html</anchorfile>
      <anchor>a3edf221597262055cb3847430bd36ab8</anchor>
      <arglist>() override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>RemoveLongThinTrianglesOnPerimeter</name>
      <anchorfile>classxms_1_1_tr_tin_impl.html</anchorfile>
      <anchor>a6539e41ceec60374722e504d8e38dfb2</anchor>
      <arglist>(const double a_ratio) override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>Clear</name>
      <anchorfile>classxms_1_1_tr_tin_impl.html</anchorfile>
      <anchor>ac56cedd2e8a867bb3122716f8d30e1b8</anchor>
      <arglist>() override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>BuildTrisAdjToPts</name>
      <anchorfile>classxms_1_1_tr_tin_impl.html</anchorfile>
      <anchor>ae287535a7320100651aa21e10edead5b</anchor>
      <arglist>() override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual std::string</type>
      <name>ToString</name>
      <anchorfile>classxms_1_1_tr_tin_impl.html</anchorfile>
      <anchor>a2cdc1c1c647cbb7ee180e55e5add6835</anchor>
      <arglist>() const override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>FromString</name>
      <anchorfile>classxms_1_1_tr_tin_impl.html</anchorfile>
      <anchor>a1b7c1dacb8e701e5f5229f8a9624c47f</anchor>
      <arglist>(const std::string &amp;) override</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>serialize</name>
      <anchorfile>classxms_1_1_tr_tin_impl.html</anchorfile>
      <anchor>a83741ee7a8ad569412bb6715f500f3df</anchor>
      <arglist>(Archive &amp;archive, const unsigned int version)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>InsertAdjacentTriangle</name>
      <anchorfile>classxms_1_1_tr_tin_impl.html</anchorfile>
      <anchor>a0d1478852f239878bae47c9e685e2453</anchor>
      <arglist>(int a_pt, int a_tri)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>DeleteAdjacentTriangle</name>
      <anchorfile>classxms_1_1_tr_tin_impl.html</anchorfile>
      <anchor>a472a843922d633fdf17061006fce3868</anchor>
      <arglist>(int a_pt, int a_tri)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>bool</type>
      <name>TriIndexFound</name>
      <anchorfile>classxms_1_1_tr_tin_impl.html</anchorfile>
      <anchor>a253a5434ce056758375e7ee7b565c12e</anchor>
      <arglist>(const int &amp;a_triPt) const</arglist>
    </member>
    <member kind="function" protection="private">
      <type>bool</type>
      <name>PointIndexFound</name>
      <anchorfile>classxms_1_1_tr_tin_impl.html</anchorfile>
      <anchor>a8947cb759381812e9b2b906b48874553</anchor>
      <arglist>(const Pt3d &amp;a_point) const</arglist>
    </member>
    <member kind="function" protection="private">
      <type>bool</type>
      <name>AdjacentIndexFound</name>
      <anchorfile>classxms_1_1_tr_tin_impl.html</anchorfile>
      <anchor>ab66a31615263d8ea599d92d20316d329</anchor>
      <arglist>(const VecInt &amp;a_point) const</arglist>
    </member>
    <member kind="function" protection="private">
      <type>bool</type>
      <name>CheckAndSwap</name>
      <anchorfile>classxms_1_1_tr_tin_impl.html</anchorfile>
      <anchor>a2283ff7bbf56262e0ba0d4ecbfb15b35</anchor>
      <arglist>(int a_triA, int a_triB, bool a_propagate, const VecInt &amp;a_flags)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>bool</type>
      <name>PointIsInCircumcircle</name>
      <anchorfile>classxms_1_1_tr_tin_impl.html</anchorfile>
      <anchor>a208635ddaf084e5baae40c2538ff1dd1</anchor>
      <arglist>(int a_tri1, int a_tri2, int id)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>BuildTrisAdjToPtsConst</name>
      <anchorfile>classxms_1_1_tr_tin_impl.html</anchorfile>
      <anchor>a92fa71c48a02cb66695487cf01fef1cc</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>CheckTriangle</name>
      <anchorfile>classxms_1_1_tr_tin_impl.html</anchorfile>
      <anchor>a819d105df8de79aae59791e7316ee209</anchor>
      <arglist>(const int a_tri, const int a_index, const double a_ratio, VecInt &amp;a_flags, SetInt &amp;a_trisToDelete) const</arglist>
    </member>
    <member kind="function" protection="private">
      <type>int</type>
      <name>AdjacentTriangleIndex</name>
      <anchorfile>classxms_1_1_tr_tin_impl.html</anchorfile>
      <anchor>a5fd85293103096659f5d7311c1e5f252</anchor>
      <arglist>(const int a_currTri, const int a_adjTri) const</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>BSHP&lt; VecPt3d &gt;</type>
      <name>m_pts</name>
      <anchorfile>classxms_1_1_tr_tin_impl.html</anchorfile>
      <anchor>a30b990ac9bc359b54d476992c140db4c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>BSHP&lt; VecInt &gt;</type>
      <name>m_tris</name>
      <anchorfile>classxms_1_1_tr_tin_impl.html</anchorfile>
      <anchor>a68fa36caa1358e96e27dcdf47023c1aa</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>BSHP&lt; VecInt2d &gt;</type>
      <name>m_trisAdjToPts</name>
      <anchorfile>classxms_1_1_tr_tin_impl.html</anchorfile>
      <anchor>a9f129e46ee51dbc0b3d3fef0cb794b0a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>boost::unordered_set&lt; int &gt;</type>
      <name>m_toDelete</name>
      <anchorfile>classxms_1_1_tr_tin_impl.html</anchorfile>
      <anchor>ae197cb5a74cb139418af07ea12161ab6</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>TrTinUnitTests</name>
    <filename>class_tr_tin_unit_tests.html</filename>
    <member kind="function">
      <type>void</type>
      <name>test1</name>
      <anchorfile>class_tr_tin_unit_tests.html</anchorfile>
      <anchor>a198e55ca6fc0831488240809cffddea2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testOptimizeTriangulation</name>
      <anchorfile>class_tr_tin_unit_tests.html</anchorfile>
      <anchor>a29a07efdba13d58663f8a61fd5404d4f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testSwap</name>
      <anchorfile>class_tr_tin_unit_tests.html</anchorfile>
      <anchor>ab978361fc941ce007bfa7d419a0bce92</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testBoundaries</name>
      <anchorfile>class_tr_tin_unit_tests.html</anchorfile>
      <anchor>a9a7adf7f4b8ab36ef62d3d7e55bf5c92</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testDeleteTriangles</name>
      <anchorfile>class_tr_tin_unit_tests.html</anchorfile>
      <anchor>a390a1322e40b297601fccea53fad2472</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testDeletePoints</name>
      <anchorfile>class_tr_tin_unit_tests.html</anchorfile>
      <anchor>a609dc373196faee1173a89d9955d1559</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testRemoveLongThinTrianglesOnPerimeter</name>
      <anchorfile>class_tr_tin_unit_tests.html</anchorfile>
      <anchor>a2393a141eb2f1bc3d75b8f45094e915d</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>xms::TrTriangulator</name>
    <filename>classxms_1_1_tr_triangulator.html</filename>
    <member kind="function">
      <type></type>
      <name>TrTriangulator</name>
      <anchorfile>classxms_1_1_tr_triangulator.html</anchorfile>
      <anchor>ac54bc210a1de778f7b6350170e31da26</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~TrTriangulator</name>
      <anchorfile>classxms_1_1_tr_triangulator.html</anchorfile>
      <anchor>abfb9ab61fc0a609f964751b493275366</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>Triangulate</name>
      <anchorfile>classxms_1_1_tr_triangulator.html</anchorfile>
      <anchor>a76a62ce7b12c2cc317d8725dba3cef16</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>xms::TrTriangulatorPoints</name>
    <filename>classxms_1_1_tr_triangulator_points.html</filename>
    <base>xms::TrTriangulator</base>
    <member kind="function">
      <type></type>
      <name>TrTriangulatorPoints</name>
      <anchorfile>classxms_1_1_tr_triangulator_points.html</anchorfile>
      <anchor>a06ec7a3c688accca4f7c72a3354e1400</anchor>
      <arglist>(const VecPt3d &amp;a_pts, VecInt &amp;a_tris, VecInt2d *a_trisAdjToPts=nullptr)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>SetObserver</name>
      <anchorfile>classxms_1_1_tr_triangulator_points.html</anchorfile>
      <anchor>a9a4225d2e6a3b30d020e0bffffb6351b</anchor>
      <arglist>(BSHP&lt; Observer &gt; a_)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>GetID</name>
      <anchorfile>classxms_1_1_tr_triangulator_points.html</anchorfile>
      <anchor>a5a2ab0245a79750a3212e2400edca40a</anchor>
      <arglist>() const override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual Pt3d</type>
      <name>GetLocation</name>
      <anchorfile>classxms_1_1_tr_triangulator_points.html</anchorfile>
      <anchor>adde88d87e5db9f9be2c13e9075da6eca</anchor>
      <arglist>() const override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>GetNPoints</name>
      <anchorfile>classxms_1_1_tr_triangulator_points.html</anchorfile>
      <anchor>adbc913759a325fd2f01283e8112a8c0e</anchor>
      <arglist>() const override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>IncrementPoint</name>
      <anchorfile>classxms_1_1_tr_triangulator_points.html</anchorfile>
      <anchor>ab1dcfd044e79eadc9c91a6feebbb5726</anchor>
      <arglist>() override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>PrepareToReceiveTriangles</name>
      <anchorfile>classxms_1_1_tr_triangulator_points.html</anchorfile>
      <anchor>a5e04e8e6077b2456782889f83170123b</anchor>
      <arglist>() override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>FinalizeTriangulation</name>
      <anchorfile>classxms_1_1_tr_triangulator_points.html</anchorfile>
      <anchor>a91c8c4eb53d2b252c816b168d0b5f7e5</anchor>
      <arglist>() override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>ReceiveTriangle</name>
      <anchorfile>classxms_1_1_tr_triangulator_points.html</anchorfile>
      <anchor>ab4fb455a7ae86c84b8e29b5d03db916d</anchor>
      <arglist>(int a_id1, int a_id2, int a_id3) override</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>UpdateAreaTolerance</name>
      <anchorfile>classxms_1_1_tr_triangulator_points.html</anchorfile>
      <anchor>a172065079973143ab239b0b983b01074</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>const VecPt3d &amp;</type>
      <name>m_pts</name>
      <anchorfile>classxms_1_1_tr_triangulator_points.html</anchorfile>
      <anchor>aaa180402a34969a95e0b3db430d731ec</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>int</type>
      <name>m_idx</name>
      <anchorfile>classxms_1_1_tr_triangulator_points.html</anchorfile>
      <anchor>ab14bc4456e99495852a63020ee1c644f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>VecInt &amp;</type>
      <name>m_tris</name>
      <anchorfile>classxms_1_1_tr_triangulator_points.html</anchorfile>
      <anchor>ade8f4a814000a26fede635f25b2d4d41</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>VecInt2d *</type>
      <name>m_trisAdjToPts</name>
      <anchorfile>classxms_1_1_tr_triangulator_points.html</anchorfile>
      <anchor>a39ab26cea9e757db19322c7393fbfdfa</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>double</type>
      <name>m_areaTol</name>
      <anchorfile>classxms_1_1_tr_triangulator_points.html</anchorfile>
      <anchor>af1b6f3704855069f790350cd0e77ebd0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>BSHP&lt; Observer &gt;</type>
      <name>m_observer</name>
      <anchorfile>classxms_1_1_tr_triangulator_points.html</anchorfile>
      <anchor>a051d44b473938bc5da0b4810bc3d912d</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>TrTriangulatorPointsUnitTests</name>
    <filename>class_tr_triangulator_points_unit_tests.html</filename>
    <member kind="function">
      <type>void</type>
      <name>test1</name>
      <anchorfile>class_tr_triangulator_points_unit_tests.html</anchorfile>
      <anchor>a33422cef521b757882239d403bc6569d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>test_bug12336</name>
      <anchorfile>class_tr_triangulator_points_unit_tests.html</anchorfile>
      <anchor>a45f0a0eccf070955b6160074cb12653b</anchor>
      <arglist>()</arglist>
    </member>
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
    <class kind="class">xms::XmUGrid::Impl</class>
    <member kind="function">
      <type></type>
      <name>XmUGrid</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>a2830cab0aca6c776321d58294dbc2208</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>XmUGrid</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>a9cd98317e176227dabbe6ce31e21f69a</anchor>
      <arglist>(const XmUGrid &amp;a_xmUGrid)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>XmUGrid</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>ad5227c0f60db617fb19c0db89dc4579f</anchor>
      <arglist>(XmUGrid &amp;&amp;a_xmUGrid)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~XmUGrid</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>a00ece5dcb23ebc06e2651f4a3f3695c4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>XmUGrid &amp;</type>
      <name>operator=</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>a144689f60ae3157b080c617420a7bd17</anchor>
      <arglist>(XmUGrid a_xmUGrid)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Swap</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>a56681228c462d86ad37ac39b79fef8ed</anchor>
      <arglist>(XmUGrid &amp;a_xmUGrid)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>GetModified</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>aa9f238376138ec0816f51c33d684c26b</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetUnmodified</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>ad93994968c195f50261368007dc17483</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetUseCache</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>ab504c9a10bf80273f1be4fa1502fa22c</anchor>
      <arglist>(bool a_useCache)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetPointCount</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>a732f3875ec4feea7ea4b1bce7cc694f4</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>const VecPt3d &amp;</type>
      <name>GetLocations</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>a5158c0579e4fa01a996eb3a040df934e</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetLocations</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>a55d821ad2f74bbbd46c6464cd6ec341b</anchor>
      <arglist>(const VecPt3d &amp;a_locations)</arglist>
    </member>
    <member kind="function">
      <type>Pt3d</type>
      <name>GetPointLocation</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>a4b50cc701b16d945e7290cbc76bbe8a1</anchor>
      <arglist>(int a_pointIdx) const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>SetPointLocation</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>adf88f5654fe38f32b90e0955e7b9fcb1</anchor>
      <arglist>(int a_pointIdx, const Pt3d &amp;a_location)</arglist>
    </member>
    <member kind="function">
      <type>Pt3d</type>
      <name>GetPointXy0</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>ab7e6e60efaf02736073aea05fa92402a</anchor>
      <arglist>(int a_pointIdx) const</arglist>
    </member>
    <member kind="function">
      <type>VecPt3d</type>
      <name>GetPointsLocations</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>a7d9980598e2cb18706ede2f034b5dafe</anchor>
      <arglist>(const VecInt &amp;a_points) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>GetExtents</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>a281fa5dee32e50749922fbb1d00067a8</anchor>
      <arglist>(Pt3d &amp;a_min, Pt3d &amp;a_max) const</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetPointAdjacentCellCount</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>a878d36f0c58b0e3b063365051f3cf517</anchor>
      <arglist>(int a_pointIdx) const</arglist>
    </member>
    <member kind="function">
      <type>VecInt</type>
      <name>GetPointAdjacentCells</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>a6313c612dd5595e1fee26c2d494ca5bf</anchor>
      <arglist>(int a_pointIdx) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>GetPointAdjacentCells</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>a6fba439a090ff2cb4d65967e83a29ebd</anchor>
      <arglist>(int a_pointIdx, VecInt &amp;a_adjacentCells) const</arglist>
    </member>
    <member kind="function">
      <type>VecInt</type>
      <name>GetPointsAdjacentCells</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>a1c62c748d691edf679e2dd1b095fb4ee</anchor>
      <arglist>(const VecInt &amp;a_points) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>GetPointsAdjacentCells</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>a0ea07dac522558693ab73af415be9290</anchor>
      <arglist>(const VecInt &amp;a_pointIdxs, VecInt &amp;a_adjacentCellIdxs) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>GetPointsAdjacentCells</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>a089c13a5fa6448fb0d51f5cef06949c2</anchor>
      <arglist>(int a_pointIdx1, int a_pointIdx2, VecInt &amp;a_adjacentCellIdxs) const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>IsValidPointChange</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>a2c8a52e670a12f898b8026c73e88b692</anchor>
      <arglist>(int a_changedPtIdx, const Pt3d &amp;a_newPosition) const</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetCellCount</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>a469a8f1d2a6a4540f0d25362e857c222</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetCellPointCount</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>a5305c74c30921245d093dbc456fee5c5</anchor>
      <arglist>(int a_cellIdx) const</arglist>
    </member>
    <member kind="function">
      <type>VecInt</type>
      <name>GetCellPoints</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>a024d6aa8e612a3b30456b18a06ef7fbf</anchor>
      <arglist>(int a_cellIdx) const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>GetCellPoints</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>adc868641da9ddef2ec47da9473767254</anchor>
      <arglist>(int a_cellIdx, VecInt &amp;a_cellPoints) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>GetCellLocations</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>aeb804883dc5921f6612cec387a244577</anchor>
      <arglist>(int a_cellIdx, VecPt3d &amp;a_cellLocations) const</arglist>
    </member>
    <member kind="function">
      <type>XmUGridCellType</type>
      <name>GetCellType</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>a5c71c10f43d60eb8b7a97efeb30ee0f5</anchor>
      <arglist>(int a_cellIdx) const</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; int &gt;</type>
      <name>GetDimensionCounts</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>a201cce89a36520c46294f2ec7988d606</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetCellDimension</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>aef1f3a125baa6ff2e9ce4e46bac21ad5</anchor>
      <arglist>(int a_cellIdx) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>GetCellExtents</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>a6b04b49656e0c5219a0e45c9ccd98ff7</anchor>
      <arglist>(int a_cellIdx, Pt3d &amp;a_min, Pt3d &amp;a_max) const</arglist>
    </member>
    <member kind="function">
      <type>const VecInt &amp;</type>
      <name>GetCellstream</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>a9ff80eccf0af7b61b68280d448e85b46</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>SetCellstream</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>acc4a301e82f0c2261d555b58421aa340</anchor>
      <arglist>(const VecInt &amp;a_cellstream)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>GetCellCellstream</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>a0e01703e4a82dc83eb8004b641bdbf95</anchor>
      <arglist>(int a_cellIdx, VecInt &amp;a_cellstream) const</arglist>
    </member>
    <member kind="function">
      <type>VecInt</type>
      <name>GetCellAdjacentCells</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>a245101a12bfc6f7e771aed418003fb68</anchor>
      <arglist>(int a_cellIdx) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>GetCellAdjacentCells</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>a34f60b4760b9b19e9c7a5601b42b5e1e</anchor>
      <arglist>(int a_cellIdx, VecInt &amp;a_cellNeighbors) const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>GetCellPlanViewPolygon</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>a8da8b2a035d4c9e5f6c1803b366043af</anchor>
      <arglist>(int a_cellIdx, VecPt3d &amp;a_polygon) const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>GetCellCentroid</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>a9a30301fb0c14ac49c88a41084c1dde5</anchor>
      <arglist>(int a_cellIdx, Pt3d &amp;a_centroid) const</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetCellEdgeCount</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>a14171153a6cc758c301c077a3f63161f</anchor>
      <arglist>(int a_cellIdx) const</arglist>
    </member>
    <member kind="function">
      <type>XmEdge</type>
      <name>GetCellEdge</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>a460f19f1b421ba88bdada5c449fa9f22</anchor>
      <arglist>(int a_cellIdx, int a_edgeIdx) const</arglist>
    </member>
    <member kind="function">
      <type>VecInt</type>
      <name>GetCellEdgeAdjacentCells</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>a05ee683b3fccc23ce217efc63fb00d22</anchor>
      <arglist>(int a_cellIdx, int a_edgeIdx) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>GetCellEdgeAdjacentCells</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>a2e1a39725bcf7ef8ad9b1713a7ebfffc</anchor>
      <arglist>(int a_cellIdx, int a_edgeIdx, VecInt &amp;a_adjacentCellIdxs) const</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetCell2dEdgeAdjacentCell</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>a0ced9b5c9faec8796466e7f5328a705a</anchor>
      <arglist>(int a_cellIdx, int a_edgeIdx) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>GetEdgeAdjacentCells</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>ae8246c10536e58b54a8baa5397dcbecb</anchor>
      <arglist>(const XmEdge &amp;a_edge, VecInt &amp;a_adjacentCellIdxs) const</arglist>
    </member>
    <member kind="function">
      <type>VecInt</type>
      <name>GetEdgeAdjacentCells</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>a706c49d3e9698d2495e2ae2ecb00e3a8</anchor>
      <arglist>(const XmEdge &amp;a_edge) const</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; XmEdge &gt;</type>
      <name>GetCellEdges</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>a2af7a9f3c3d463c41d71aa864fb45cc6</anchor>
      <arglist>(int a_cellIdx) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>GetCellEdges</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>af0260bcd0a21d8a54568052de09ca502</anchor>
      <arglist>(int a_cellIdx, std::vector&lt; XmEdge &gt; &amp;a_edges) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>GetPointAdjacentPoints</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>a66e1d9932d95b9d4cfddc8b28ee07b0f</anchor>
      <arglist>(int a_pointIdx, VecInt &amp;a_edgePoints) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>GetPointAdjacentLocations</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>a2d2720920c5d255109951f0d163b2592</anchor>
      <arglist>(int a_pointIdx, VecPt3d &amp;a_edgePoints) const</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetCell3dFaceCount</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>ada33af9a4818ae8fe787898deb9c3fec</anchor>
      <arglist>(int a_cellIdx) const</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetCell3dFacePointCount</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>abf21d23d34fba88d4f7631e4fd7b99e0</anchor>
      <arglist>(int a_cellIdx, int a_faceIdx) const</arglist>
    </member>
    <member kind="function">
      <type>VecInt</type>
      <name>GetCell3dFacePoints</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>a24c408b1f0455a521b55161f9f04da85</anchor>
      <arglist>(int a_cellIdx, int a_faceIdx) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>GetCell3dFacePoints</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>a52f8b3d8df9a7bd4a07606d4a3ae413d</anchor>
      <arglist>(int a_cellIdx, int a_faceIdx, VecInt &amp;a_facePtIdxs) const</arglist>
    </member>
    <member kind="function">
      <type>VecInt2d</type>
      <name>GetCell3dFacesPoints</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>a86a8b47a0f93b5f19eb69a6b5f3a4bda</anchor>
      <arglist>(int a_cellIdx) const</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetCell3dFaceAdjacentCell</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>a3d0f21726e22a125ee2b5d2d1592fa78</anchor>
      <arglist>(int a_cellIdx, int a_faceIdx) const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>GetCell3dFaceAdjacentCell</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>a7bc3d322776fecbe013bd160c3b99cdd</anchor>
      <arglist>(int a_cellIdx, int a_faceIdx, int &amp;a_neighborCell, int &amp;a_neighborFace) const</arglist>
    </member>
    <member kind="function">
      <type>XmUGridFaceOrientation</type>
      <name>GetCell3dFaceOrientation</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>a32d0acd01ca8415b821e94d371e29f2d</anchor>
      <arglist>(int a_cellIdx, int a_faceIdx) const</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static std::shared_ptr&lt; XmUGrid &gt;</type>
      <name>New</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>a3d126c7ea0f8146dd6230670b019345e</anchor>
      <arglist>(const VecPt3d &amp;a_locations, const VecInt &amp;a_cellstream)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static std::shared_ptr&lt; XmUGrid &gt;</type>
      <name>New</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>aacc53cd53574bc280fcfb6e10b047390</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static bool</type>
      <name>IsValidCellstream</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>a75064634282c829c88596c6da646f4f3</anchor>
      <arglist>(const VecInt &amp;a_cellstream)</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>std::unique_ptr&lt; Impl &gt;</type>
      <name>m_impl</name>
      <anchorfile>classxms_1_1_xm_u_grid.html</anchorfile>
      <anchor>abb2d35d37c75d3575f25628c732c7439</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>XmUGridUnitTests</name>
    <filename>class_xm_u_grid_unit_tests.html</filename>
    <member kind="function">
      <type>void</type>
      <name>testOperators</name>
      <anchorfile>class_xm_u_grid_unit_tests.html</anchorfile>
      <anchor>a5daf146c15730c2ca6e70a355b890ede</anchor>
      <arglist>()</arglist>
    </member>
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
      <name>testGetCell3dFaceOrientationHexahedrons</name>
      <anchorfile>class_xm_u_grid_unit_tests.html</anchorfile>
      <anchor>aa9a46b443946cb2927bcf013142fe3b0</anchor>
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
    <member kind="function">
      <type>void</type>
      <name>testReadVersion1Dot0File</name>
      <anchorfile>class_xm_u_grid_utils_tests.html</anchorfile>
      <anchor>a70cb1ed7fb602a8d80d3ae3cdb83d7f4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testWriteThenReadUGridBinary</name>
      <anchorfile>class_xm_u_grid_utils_tests.html</anchorfile>
      <anchor>ad06ced2d379a907ec3262d543cb76649</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testCellStringToEnum</name>
      <anchorfile>class_xm_u_grid_utils_tests.html</anchorfile>
      <anchor>a8a4beb0da82a4916eda48ac5322fb74c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testLargeUGridBinarySpeed</name>
      <anchorfile>class_xm_u_grid_utils_tests.html</anchorfile>
      <anchor>a7aafdf034b01a40e88c19ebc66f6183c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>testReadReadyAtNextLine</name>
      <anchorfile>class_xm_u_grid_utils_tests.html</anchorfile>
      <anchor>ab972a75e2f368476daa0893227f8f23e</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="namespace">
    <name>xms</name>
    <filename>namespacexms.html</filename>
    <class kind="struct">xms::BarycentricVals</class>
    <class kind="struct">xms::edgerecord</class>
    <class kind="class">xms::fSatisfies</class>
    <class kind="class">xms::GmExtents2d</class>
    <class kind="class">xms::GmExtents3d</class>
    <class kind="class">xms::GmMultiPolyIntersectionSorter</class>
    <class kind="class">xms::GmMultiPolyIntersectionSorterTerse</class>
    <class kind="class">xms::GmMultiPolyIntersector</class>
    <class kind="struct">xms::GmMultiPolyIntersectorData</class>
    <class kind="class">xms::GmMultiPolyIntersectorImpl</class>
    <class kind="class">xms::GmPolygon</class>
    <class kind="class">xms::GmPolygonImpl</class>
    <class kind="class">xms::GmPolyLinePtRedistributer</class>
    <class kind="class">xms::GmPolyLinePtRedistributerImpl</class>
    <class kind="class">xms::GmPtSearch</class>
    <class kind="class">xms::GmPtSearchImpl</class>
    <class kind="class">xms::GmTriSearch</class>
    <class kind="class">xms::GmTriSearchImpl</class>
    <class kind="class">xms::idx_pt</class>
    <class kind="class">xms::idx_tri</class>
    <class kind="class">xms::ix</class>
    <class kind="class">xms::TrAutoFixFourTrianglePts</class>
    <class kind="class">xms::TrAutoFixFourTrianglePtsImpl</class>
    <class kind="class">xms::TrBreaklineAdder</class>
    <class kind="class">xms::TrBreaklineAdderImpl</class>
    <class kind="class">xms::TrOuterTriangleDeleter</class>
    <class kind="class">xms::TrOuterTriangleDeleterImpl</class>
    <class kind="class">xms::TrTin</class>
    <class kind="class">xms::TrTinImpl</class>
    <class kind="class">xms::TrTriangulator</class>
    <class kind="class">xms::TrTriangulatorPoints</class>
    <class kind="class">xms::XmEdge</class>
    <class kind="class">xms::XmUGrid</class>
    <member kind="typedef">
      <type>boost::geometry::model::d2::point_xy&lt; double &gt;</type>
      <name>GmBstPt2d</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a5f1677620ca85b6bcc1065b757f3e337</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>boost::geometry::model::polygon&lt; GmBstPt2d &gt;</type>
      <name>GmBstPoly2d</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a93e3d438c33ced49f413cd84323982d5</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>boost::geometry::model::polygon&lt; Pt3d &gt;</type>
      <name>GmBstPoly3d</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a05c9c43c740eaf5b56f436ec992dca5f</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>boost::geometry::model::box&lt; Pt3d &gt;</type>
      <name>GmBstBox3d</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>af7ac61e434c47abf90a1349336f7e8b7</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>boost::geometry::model::linestring&lt; Pt3d &gt;</type>
      <name>GmBstLine3d</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a9bb6715848b64f01474619d28cd619d9</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>boost::geometry::ring_type&lt; GmBstPoly3d &gt;::type</type>
      <name>GmBstRing3d</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a4d04b2e2f10cd613e47211b9ac69784e</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::pair&lt; GmBstBox3d, int &gt;</type>
      <name>ValueBox</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ad371b9317cd9cab40e2625cb4e35df05</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>bgi::rtree&lt; ValueBox, bgi::quadratic&lt; 8 &gt; &gt;</type>
      <name>RtreeBox</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>aa547c53279be0830c2afc7536f557044</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>bg::model::box&lt; bPt &gt;</type>
      <name>box</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>af3aa99ee2ee766e1f9c1480f8f4fa2f8</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>size_t</type>
      <name>value</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ac246bb2df10f44751d78d40e43d88da2</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>bgi::quadratic&lt; 8 &gt;</type>
      <name>qRtree</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a528acc66ce7a7889c76de85b6d5d5a23</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::vector&lt; edgerecord &gt;</type>
      <name>VecEdge</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a7541b74c2b86c70e57e863b57304bdcc</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>Turn_enum</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a0682e25caba7c1d65216a5680cc0217b</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>TURN_LEFT</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a0682e25caba7c1d65216a5680cc0217babc1acb082c93789cb378bf87597f42dd</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>TURN_RIGHT</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a0682e25caba7c1d65216a5680cc0217ba4a1de04425d6c2953fbf40f2b29c15c7</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>TURN_COLINEAR_180</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a0682e25caba7c1d65216a5680cc0217badbc22a212895c3de629b927b410a7065</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>TURN_COLINEAR_0</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a0682e25caba7c1d65216a5680cc0217ba06d649a650f4acb061afb7acd5a2dbd7</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>PtInOutOrOn_enum</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a89f7d814569daefeabe9f5e3b5fbd213</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>PT_ERROR</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a89f7d814569daefeabe9f5e3b5fbd213a75f63694d4c2fbd0065900d8a51dcf54</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>PT_IN</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a89f7d814569daefeabe9f5e3b5fbd213a5f2058ee26998db92e7beedea5fd7e1c</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>PT_OUT</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a89f7d814569daefeabe9f5e3b5fbd213af6c0802668cf9ce14590690ec216dc6a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>PT_ON</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a89f7d814569daefeabe9f5e3b5fbd213afef40dd1d13df2164ce1a2ba841a3b6a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>GmMultiPolyIntersectorQueryEnum</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>af3e9dae61009fe77b79327ee8ebe9b2e</anchor>
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
      <type>bool</type>
      <name>gmPointInOrOnBox2d</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a1460ad596726029e888ef3a0c67cb3ec</anchor>
      <arglist>(const Pt3d &amp;a_bMin, const Pt3d &amp;a_bMax, const Pt3d &amp;a_pt)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>gmBoxesOverlap2d</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a0a8640978d427b51b4ba6c217bb47b12</anchor>
      <arglist>(const Pt3d &amp;a_b1Min, const Pt3d &amp;a_b1Max, const Pt3d &amp;a_b2Min, const Pt3d &amp;a_b2Max)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>gmCalculateNormalizedPlaneCoefficients</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a815c09c53387db67255d3dce98695778</anchor>
      <arglist>(const Pt3d &amp;p1, const Pt3d &amp;p2, const Pt3d &amp;p3, double *a, double *b, double *c, double *d)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>gmCalculateNormalizedPlaneCoefficients</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ad18b77815c5b85e99429ee9240768473</anchor>
      <arglist>(const Pt3d *p1, const Pt3d *p2, const Pt3d *p3, double *a, double *b, double *c, double *d)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>gmMiddleZ</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>aca28f3227dce2e445d25080fbecbc2c6</anchor>
      <arglist>(const VecPt3d &amp;a_points)</arglist>
    </member>
    <member kind="function">
      <type>PtInOutOrOn_enum</type>
      <name>gmPtInCircumcircle</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ade7879f66ffa765c6ee005573218a4cd</anchor>
      <arglist>(const Pt3d &amp;pt, Pt3d circumcirclePts[3])</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>gmXyDistanceSquared</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>abfc383f1bd2f48276705d624db7144c8</anchor>
      <arglist>(const Pt3d &amp;pt1, const Pt3d &amp;pt2)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>gmCircumcircleWithTol</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a72205354f6d55c7907f6badfbc2e08b0</anchor>
      <arglist>(const Pt3d *pt1, const Pt3d *pt2, const Pt3d *pt3, double *xc, double *yc, double *r2, double tol)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>gmCartToBary</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ad512367ef48bf109240552ff3c30cc7a</anchor>
      <arglist>(const Pt3d *cart, const Pt3d *orig, double coef[6], int dir, Pt3d *bary)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>gmBaryPrepare</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a065cd6d71205487312c1e03496f5ca08</anchor>
      <arglist>(const Pt3d *p1, const Pt3d *p2, const Pt3d *p3, const Pt3d *norm, Pt3d *orig, double coef[6], int *dir, bool flag)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>gmColinearWithTol</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a546070340fe9bdf56641efa002a27ac9</anchor>
      <arglist>(const Pt3d &amp;p1, const Pt3d &amp;p2, const Pt3d &amp;p3, const double tol)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>gmIntersectLineSegmentsWithTol</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ac96bb6c54af013c284ac2c3657626c67</anchor>
      <arglist>(const Pt3d &amp;one1, const Pt3d &amp;one2, const Pt3d &amp;two1, const Pt3d &amp;two2, double *xi, double *yi, double *zi1, double *zi2, double tol)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>gmCounterClockwiseTri</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a098ef608f7092e087f9a456709714fea</anchor>
      <arglist>(const Pt3d &amp;vtx0, const Pt3d &amp;vtx1, const Pt3d &amp;vtx2)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>gmCross2D</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a06f4c8c6bc396759e5d8953d85530b46</anchor>
      <arglist>(const double &amp;dx1, const double &amp;dy1, const double &amp;dx2, const double &amp;dy2)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>gmCross2D</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a477b039c6c57c8bbe95fe341eb5b1164</anchor>
      <arglist>(const Pt3d &amp;a_origin, const Pt3d &amp;a_A, const Pt3d &amp;a_B)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>gmAngleBetween2DVectors</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>aacf14a948fef6fc782b4e7210652ad35</anchor>
      <arglist>(double dxp, double dyp, double dxn, double dyn)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>gmAngleBetween2DVectors</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ae9ee7df906ccbedcb3b364d1a5571f60</anchor>
      <arglist>(double dxp, double dyp, double dxn, double dyn, double a_magn, double a_magp)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>gmAngleBetweenEdges</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ad5d19a71ee810d5a16ea601d9ca7dda8</anchor>
      <arglist>(const Pt3d &amp;p1, const Pt3d &amp;p2, const Pt3d &amp;p3)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>gmAngleBetweenEdges</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a93b051e3a396a16ae9a9a24b4350164c</anchor>
      <arglist>(const Pt2d &amp;p1, const Pt2d &amp;p2, const Pt2d &amp;p3)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>gmComputeDeviationInDirection</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a7d7bbeb7ef537825868d7e70021d918c</anchor>
      <arglist>(const Pt3d &amp;a_p0, const Pt3d &amp;a_p1, const Pt3d &amp;a_p2)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>gmOnLineWithTol</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a45139efe30e550bbc370542f8e69a76f</anchor>
      <arglist>(const Pt3d &amp;p1, const Pt3d &amp;p2, const double x, const double y, const double tol)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>gmOnLineAndBetweenEndpointsWithTol</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a169625a9f18e45ac2b67fac67c5db715</anchor>
      <arglist>(const Pt3d &amp;a_pt1, const Pt3d &amp;a_pt2, const double a_x, const double a_y, double a_tol)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>gmAddToExtents</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a7b4416101125e2de1d4301a09f34cc4a</anchor>
      <arglist>(const Pt3d &amp;a_pt, Pt3d &amp;a_min, Pt3d &amp;a_max)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>gmAddToExtents</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a3d89b95b5652b82ece1415a73f6d102b</anchor>
      <arglist>(const Pt3d &amp;a_pt, Pt2d &amp;a_min, Pt2d &amp;a_max)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>gmAddToExtents</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a6c3d405fd7c3488c385b0caa932f9cba</anchor>
      <arglist>(const Pt2d &amp;a_pt, Pt3d &amp;a_min, Pt3d &amp;a_max)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>gmXyDistance</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a67d8975fe80c8ec9c9b424cf26e5e755</anchor>
      <arglist>(double x1, double y1, double x2, double y2)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>gmXyDistance</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a9a89d9544f63308d7a3c31e99c8281a9</anchor>
      <arglist>(const Pt3d &amp;pt1, const Pt3d &amp;pt2)</arglist>
    </member>
    <member kind="function">
      <type>Turn_enum</type>
      <name>gmTurn</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a4700adae0c06deec6e84e436c86f276b</anchor>
      <arglist>(const Pt3d &amp;a_v1, const Pt3d &amp;a_v2, const Pt3d &amp;a_v3, double a_angtol)</arglist>
    </member>
    <member kind="function">
      <type>Pt3d</type>
      <name>gmComputeCentroid</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ac462cb8b1fc78478a3f6cad9073a37e9</anchor>
      <arglist>(const VecPt3d &amp;a_points)</arglist>
    </member>
    <member kind="function">
      <type>Pt3d</type>
      <name>gmComputePolygonCentroid</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a728b2937701be72dc73f3f66ac2e7fbf</anchor>
      <arglist>(const VecPt3d &amp;pts)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>gmLinesIntersect</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>adc56691197d92d60abcb0e77e48df4ea</anchor>
      <arglist>(const Pt3d &amp;one1, const Pt3d &amp;one2, const Pt3d &amp;two1, const Pt3d &amp;two2)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>gmLinesCross</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a576c914d0519eaeab0e4494e4f000c75</anchor>
      <arglist>(const Pt3d &amp;a_segment1Point1, const Pt3d &amp;a_segment1Point2, const Pt3d &amp;a_segment2Point1, const Pt3d &amp;a_segment2Point2)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>gmPointInPolygon2D</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a43bab17fe8d6f6b67de11a49e5127424</anchor>
      <arglist>(const T *a_verts, const size_t a_num, const double a_x, const double a_y, const double a_tol)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>gmPointInPolygon2D</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a457f87dda88f474bebe491ec094b693f</anchor>
      <arglist>(const Pt3d *a_verts, size_t a_num, double a_x, double a_y)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>gmPointInPolygon2D</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>aa32ddc6f5892464bfe6d596c1922f7f5</anchor>
      <arglist>(const Pt3d *a_verts, size_t a_num, Pt3d a_pt)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>gmPointInPolygon2D</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a959d71253e45c5f67e1bf202a5a122fd</anchor>
      <arglist>(const Pt2i *a_verts, size_t a_num, Pt2d a_pt)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>gmPointInPolygon2D</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>aac4a8fdb18373864527f2fad0bb8c433</anchor>
      <arglist>(const Pt2i *a_verts, size_t a_num, Pt3d a_pt)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>gmPointInPolygon2D</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a3b879e6c80208a8780496137ac51c3c9</anchor>
      <arglist>(const Pt2i *a_verts, size_t a_num, Pt2i a_pt)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>gmPointInPolygon2D</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>aad56bb08be2f1969cd7912f59d49d9e2</anchor>
      <arglist>(const VecPt3d &amp;a_verts, const Pt3d &amp;a_pt)</arglist>
    </member>
    <member kind="function">
      <type>template int</type>
      <name>gmPointInPolygon2D&lt; Pt3d &gt;</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a241b33f3ef73ed56ca73fdbb830e14a3</anchor>
      <arglist>(const Pt3d *a_verts, const size_t a_num, const double a_x, const double a_y, const double a_tol)</arglist>
    </member>
    <member kind="function">
      <type>template int</type>
      <name>gmPointInPolygon2D&lt; Pt2d &gt;</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a84aea859e24101dbd69dc902d4f423f8</anchor>
      <arglist>(const Pt2d *a_verts, const size_t a_num, const double a_x, const double a_y, const double a_tol)</arglist>
    </member>
    <member kind="function">
      <type>template int</type>
      <name>gmPointInPolygon2D&lt; Pt2i &gt;</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a296ceeadef9d9d4e4ba698f52c44c6c9</anchor>
      <arglist>(const Pt2i *a_verts, const size_t a_num, const double a_x, const double a_y, const double a_tol)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>gmComputeXyTol</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a03126d64edc4ecb587a357fbfa5fb08c</anchor>
      <arglist>(const Pt3d &amp;a_mn, const Pt3d &amp;a_mx)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>gmXyTol</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a7a33258adddbd27ad36954f6ccdcdef7</anchor>
      <arglist>(bool a_set, double a_value)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>gmZTol</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>af0e7dba5dafe577d6345afe25580777a</anchor>
      <arglist>(bool a_set, double a_value)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>gmEqualPointsXY</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a9a226e666728d9fde914f18db63a4714</anchor>
      <arglist>(double x1, double y1, double x2, double y2, double tolerance)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>gmEqualPointsXY</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ac504f8315cad401c34447f06c5b6b07d</anchor>
      <arglist>(double x1, double y1, double x2, double y2)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>gmEqualPointsXY</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a427db5d209d5d8d22ec417417de4d702</anchor>
      <arglist>(const Pt2d &amp;a_pt1, const Pt2d &amp;a_pt2, double tol)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>gmEqualPointsXY</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a6724be333a3994b7cb0bbe1ec832f244</anchor>
      <arglist>(const Pt3d &amp;a_pt1, const Pt3d &amp;a_pt2, double tol)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>gmEqualPointsXY</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a878ec06b0e9bbd3afccd2bf70ec54621</anchor>
      <arglist>(const Pt2i &amp;point1, const Pt2i &amp;point2)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>gmEqualPointsXYZ</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a8c3a08ccd01c4230e7498d793a9d90cd</anchor>
      <arglist>(double x1, double y1, double z1, double x2, double y2, double z2, double tolerance)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>gmEqualPointsXYZ</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a6e4ba75c670a283360048a5365558916</anchor>
      <arglist>(double x1, double y1, double z1, double x2, double y2, double z2)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>gmEqualPointsXYZ</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a326b40120fd0517c654d9a94a963e83e</anchor>
      <arglist>(const Pt3d &amp;pt1, const Pt3d &amp;pt2, double tol)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>gmPointInTriangleWithTol</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a5b2cb41a4510b0ba885d4a4691781506</anchor>
      <arglist>(const Pt3d *p1, const Pt3d *p2, const Pt3d *p3, double x, double y, double tol)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>gmInsideOrOnLineWithTol</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a33f9850dc05d9598dcd1e4d06d7a64a2</anchor>
      <arglist>(const Pt3d *p1, const Pt3d *p2, const Pt3d *inpoint, const double x, const double y, const double tol, double *dist)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>gmPolygonArea</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a299579fe39539f353e245d1c41c8eb0f</anchor>
      <arglist>(const Pt3d *pts, size_t npoints)</arglist>
    </member>
    <member kind="function">
      <type>VecPt3d</type>
      <name>gmArrayToVecPt3d</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a7877ffa4620ae49b12d0b49de2289135</anchor>
      <arglist>(double *a_array, int a_size)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>gmEnvelopeOfPts</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>aeb0fecb3c9d9aa77f4ff42ec6a608f26</anchor>
      <arglist>(const VecPt3d &amp;a_pts, Pt3d &amp;a_min, Pt3d &amp;a_max)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>gmOrderPointsCounterclockwise</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ac3222874630da8f1f8537f1a6135846f</anchor>
      <arglist>(const VecPt3d &amp;a_pts, VecInt &amp;a_ccwOrder, int a_startindex)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>gmOrderPointsCounterclockwise</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>aed9ee1170ee7004d626347f8886e4943</anchor>
      <arglist>(VecPt3d &amp;a_pts)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>gmFindClosestPtOnSegment</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ad89c693cc48610a4a7dcf89f22d55118</anchor>
      <arglist>(const Pt3d &amp;a_pt1, const Pt3d &amp;a_pt2, const Pt3d &amp;a_pt, Pt3d &amp;a_newpt, const double a_tol)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>gmPtDistanceAlongSegment</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a9f9e75d979ef1bc5c0c217115eb34a04</anchor>
      <arglist>(const Pt3d &amp;a_pt1, const Pt3d &amp;a_pt2, const Pt3d &amp;a_pt, const double a_tol)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>gmInsideOfLineWithTol</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>aa78a4612aa080741e2ce7aa301aab615</anchor>
      <arglist>(const Pt3d &amp;a_vertex1, const Pt3d &amp;a_vertex2, const Pt3d &amp;a_oppositevertex, const double a_x, const double a_y, const double a_tol)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>gmExtents2D</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a38a42e7eea0d9ce1dfebc230e50ad166</anchor>
      <arglist>(const VecPt3d &amp;a_points, Pt2d &amp;a_min, Pt2d &amp;a_max)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>gmExtents2D</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ac21eba0393f3071a3af665e8cfedb7bd</anchor>
      <arglist>(const VecPt3d &amp;a_points, Pt3d &amp;a_min, Pt3d &amp;a_max)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>gmExtents3D</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ac4c2eb4bc4667e6479497b0b529562c8</anchor>
      <arglist>(const VecPt3d &amp;a_points, Pt3d &amp;a_min, Pt3d &amp;a_max)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>gmPerpendicularAngle</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a8397c11d92c81098edabbc41ab06bffa</anchor>
      <arglist>(const Pt3d &amp;a_pt1, const Pt3d &amp;a_pt2)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>gmBisectingAngle</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>afbc887b28d4ef88ce8c14aab5482765a</anchor>
      <arglist>(const Pt3d &amp;a_p1, const Pt3d &amp;a_p2, const Pt3d &amp;a_p3)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>gmComponentMagnitudes</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a214f89ef03c8dd4f0ca2e4418fc1757d</anchor>
      <arglist>(double *a_x, double *a_y, double *a_mag, double *a_dir, bool a_tomagdir)</arglist>
    </member>
    <member kind="function">
      <type>Pt3d</type>
      <name>gmCreateVector</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ae15d7a7439937df12789f169f594c3df</anchor>
      <arglist>(const Pt3d &amp;a_p1, const Pt3d &amp;a_p2)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>gmConvertAngleToBetween0And360</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a3de1bfdf51c7b4ee1b3c2a3f1ecb96ba</anchor>
      <arglist>(double a_angle, bool a_InDegrees)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>gmCross3D</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>afff1edecd418a115ea72edd1fffc115e</anchor>
      <arglist>(const Pt3d &amp;a_vec1, const Pt3d &amp;a_vec2, Pt3d *a_vec3)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>gmDot3D</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a02f5cd9ea7e783cdb00ba6ec4f88a357</anchor>
      <arglist>(const Pt3d &amp;a_vec1, const Pt3d &amp;a_vec2)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>gmIntersectTriangleAndLineSegment</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ab82e28a71a8e0794c21d756c2308fd3b</anchor>
      <arglist>(const Pt3d &amp;a_pt1, const Pt3d &amp;a_pt2, const Pt3d &amp;a_t0, const Pt3d &amp;a_t1, const Pt3d &amp;a_t2, Pt3d &amp;a_IntersectPt)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>gm2DDistanceToLineWithTol</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a9684415f055c6e1f7b779d3a9e84f609</anchor>
      <arglist>(const Pt3d *a_pt1, const Pt3d *a_pt2, double a_x, double a_y, double a_tol)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>gmGetConvexHull</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a74e3df59e816303d09c6923d6e8d7272</anchor>
      <arglist>(const VecPt3d &amp;a_pts, VecPt3d &amp;a_hull, bool a_includeOn)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static double</type>
      <name>iDistanceToRing</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a99db03c7ac0beff008fd1d9b5795f7cb</anchor>
      <arglist>(const GmBstRing3d &amp;a_ring, const Pt3d &amp;a_pt)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>iCartToBary</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>af5d39c8118d6484eca6f5dc22cfe082a</anchor>
      <arglist>(const Pt3d &amp;a_pt1, const Pt3d &amp;a_pt2, const Pt3d &amp;a_pt3, BarycentricVals &amp;a_b)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>iGetBarycentricCoords</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a4e909346571623b3e32310fd0877dea6</anchor>
      <arglist>(const Pt3d &amp;a_p, BarycentricVals &amp;a_b, Pt3d &amp;weights)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>mxLUDecomp</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>abafef2cc31ff622207da56d429af5a54</anchor>
      <arglist>(double **mat, int n, int *indx, double *d)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>mxLUBcksub</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>af4f904018cc928a778a7167b13fee704</anchor>
      <arglist>(double **mat, int n, const int *indx, double *b)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>mxiLudcmp3</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a83378019fa1d29c6f64e692118946a30</anchor>
      <arglist>(double mat[3][3], int indx[3], double *d)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>mxiLubksb3</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a1417150425cc14d57c2749d4f55a2945</anchor>
      <arglist>(const double mat[3][3], const int indx[3], double b[3])</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>mxSolveNxN</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a6b98843e685aab775941c3b89baa1d05</anchor>
      <arglist>(double **A, double *x, double *b, int n)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>mxSolveBandedEquations</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a6db76770e358ca141899b2a7c49d0a4d</anchor>
      <arglist>(double **a, double *x, double *b, int numeqs, int halfbandwidth)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>mxSolve3x3</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>aeed277bbc30a62f34e143baf5e6b04d4</anchor>
      <arglist>(double A[3][3], double x[3], double b[3])</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>mxInvert4x4</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ac76184db2a6a79c7a900ccf094f2bc5d</anchor>
      <arglist>(const double matrix[4][4], double inv[4][4])</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>mxPointMult</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a5e1a072632bb9cbda8df1442f70aa79a</anchor>
      <arglist>(Pt3d *pt, const double ctm[4][4])</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>mxCopy4x4</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ad30f45f6b87cb251f568c5afd565ac0f</anchor>
      <arglist>(double copy[4][4], const double matrix[4][4])</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>mxIdent4x4</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a817c4c41acd08d13bfc16e7f2982b5c2</anchor>
      <arglist>(double matrix[4][4])</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>mxMult4x4</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a5af15ec8654dced904d8c0b5b1e0ec99</anchor>
      <arglist>(double product[4][4], const double matrix1[4][4], const double matrix2[4][4])</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>mxRotate4x4</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ab8a23ab457d1a300fee82511b9dcccad</anchor>
      <arglist>(double xrot, double yrot, double zrot, double rMatt[4][4])</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>mxTranslate4x4</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ad8e2621b9cbd6773239bd1c9ad604e0a</anchor>
      <arglist>(const Pt3d &amp;a_translation, double a_mx[4][4])</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>trTriangulateIt</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ae7e3768a7e434634406ea7ee25bc0648</anchor>
      <arglist>(TrTriangulator &amp;a_Client)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>trArea</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a3ab795fd4e5d3ebcedb00230e73392dc</anchor>
      <arglist>(const Pt3d &amp;a_pt1, const Pt3d &amp;a_pt2, const Pt3d &amp;a_pt3)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>trBuildGridTrianglePolys</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a176da2f77435c7baf90a2507e5841362</anchor>
      <arglist>(int rows, int cols, VecPt3d &amp;a_points, VecInt2d &amp;a_polys)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>trBuildGridPolys</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a5c5d655291110f3f2ff13fa3a733b689</anchor>
      <arglist>(int rows, int cols, VecPt3d &amp;pts, VecInt2d &amp;polys)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>trIncrementIndex</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a3522d0baa47f21d6355b87f5c7173260</anchor>
      <arglist>(int i)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>trDecrementIndex</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a5b6d3f9afa689aac0cfcdf1097ae62cf</anchor>
      <arglist>(int i)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>trRenumberOnDelete</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a66eebefbcd706efc80c4ca1cdceb05d3</anchor>
      <arglist>(const SetInt &amp;a_deleting, VecInt &amp;a_vec)</arglist>
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
      <anchor>a00d2ba2d5a847f521e5ef4b8760673b1</anchor>
      <arglist>(const std::vector&lt; int &gt; &amp;a_points, std::shared_ptr&lt; XmUGrid &gt; a_ugrid)</arglist>
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
      <type>std::shared_ptr&lt; XmUGrid &gt;</type>
      <name>TEST_XmUGrid1Left90Tri</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a20c36b8eb6452f2d1875b0247c14d31e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::shared_ptr&lt; XmUGrid &gt;</type>
      <name>TEST_XmUGridSimpleQuad</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a3e1912532173494a8d160ac5d82a392a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::shared_ptr&lt; XmUGrid &gt;</type>
      <name>TEST_XmUGrid2dLinear</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ac0c59b6cb5d5cec46437e61eedec1084</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::shared_ptr&lt; XmUGrid &gt;</type>
      <name>TEST_XmUGrid3dLinear</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ae7d1f554521e831a8f9ccaaf416437bd</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::shared_ptr&lt; XmUGrid &gt;</type>
      <name>TEST_XmUGridHexagonalPolyhedron</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a6a1e92629d5aea37e379767e4eee20ab</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::shared_ptr&lt; xms::XmUGrid &gt;</type>
      <name>TEST_XmUBuildQuadUGrid</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a752ee43c318c0d776a4922f2a7fad2d7</anchor>
      <arglist>(int a_rows, int a_cols)</arglist>
    </member>
    <member kind="function">
      <type>std::shared_ptr&lt; xms::XmUGrid &gt;</type>
      <name>TEST_XmUBuildQuadUGrid</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a73b81475327580e61ccc7ab6501404b6</anchor>
      <arglist>(int a_rows, int a_cols, const xms::Pt3d &amp;a_origin)</arglist>
    </member>
    <member kind="function">
      <type>std::shared_ptr&lt; xms::XmUGrid &gt;</type>
      <name>TEST_XmUBuildHexahedronUgrid</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a47daf228f70ea022c26d3f75f7d81f6f</anchor>
      <arglist>(int a_rows, int a_cols, int a_lays)</arglist>
    </member>
    <member kind="function">
      <type>std::shared_ptr&lt; xms::XmUGrid &gt;</type>
      <name>TEST_XmUBuildHexahedronUgrid</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>aa8a343a956e47e7e1cf02e519692e457</anchor>
      <arglist>(int a_rows, int a_cols, int a_lays, const xms::Pt3d &amp;a_origin)</arglist>
    </member>
    <member kind="function">
      <type>std::shared_ptr&lt; xms::XmUGrid &gt;</type>
      <name>TEST_XmUBuildPolyhedronUgrid</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ab1b974ca6051709e16e6bfe888bb5ac0</anchor>
      <arglist>(int a_rows, int a_cols, int a_lays)</arglist>
    </member>
    <member kind="function">
      <type>std::shared_ptr&lt; xms::XmUGrid &gt;</type>
      <name>TEST_XmUBuildPolyhedronUgrid</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a4d3536ed21ff9fe41c5f6be1214efa8b</anchor>
      <arglist>(int a_rows, int a_cols, int a_lays, const xms::Pt3d &amp;a_origin)</arglist>
    </member>
    <member kind="function">
      <type>std::shared_ptr&lt; xms::XmUGrid &gt;</type>
      <name>TEST_XmUBuild3DChevronUgrid</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>adb5e5abe3d445643a032581a904d3be1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::shared_ptr&lt; XmUGrid &gt;</type>
      <name>XmReadUGridFromAsciiFile</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>ab9624f114b63071fd74602311eab24d4</anchor>
      <arglist>(const std::string &amp;a_filePath)</arglist>
    </member>
    <member kind="function">
      <type>std::shared_ptr&lt; XmUGrid &gt;</type>
      <name>XmReadUGridFromStream</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a567badd7a8307c065bb1d98fc00c6d64</anchor>
      <arglist>(std::istream &amp;a_inStream)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>XmWriteUGridToAsciiFile</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a2cb05982d077fe5a46ecf41202723d14</anchor>
      <arglist>(std::shared_ptr&lt; XmUGrid &gt; a_ugrid, const std::string &amp;a_filePath)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>XmWriteUGridToStream</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a5c12f5e36da024c353837d9558c6c9c8</anchor>
      <arglist>(std::shared_ptr&lt; XmUGrid &gt; a_ugrid, std::ostream &amp;a_outStream)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>XmWriteUGridToStream</name>
      <anchorfile>namespacexms.html</anchorfile>
      <anchor>a089a787adbb806cc55d8751b8ffb3a8d</anchor>
      <arglist>(const XmUGrid &amp;a_ugrid, std::ostream &amp;a_outStream, bool a_binary)</arglist>
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
