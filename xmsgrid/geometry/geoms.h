#pragma once
//------------------------------------------------------------------------------
/// \file
/// \brief Functions dealing with geometry.
/// \ingroup geometry
/// \copyright (C) Copyright Aquaveo 2018. Distributed under FreeBSD License
/// (See accompanying file LICENSE or https://aqaveo.com/bsd/license.txt)
//------------------------------------------------------------------------------

//----- Included files ---------------------------------------------------------

// 3. Standard Library Headers
#include <vector>

// 4. External Library Headers
#include <xmscore/misc/xmstype.h>
#include <xmscore/points/pt.h> // Pt3d, Pt2d, etc.
#include <xmscore/stl/vector.h>

// 5. Shared Headers

// 6. Non-shared Headers

//----- Namespace declaration --------------------------------------------------

namespace xms
{
const double DEGREES_TO_RADIANS(XM_PI / 180.0);
const double RADIANS_TO_DEGREES(180.0 / XM_PI);

/// direction of turn between 3 points
enum Turn_enum {
  TURN_LEFT,         ///< turn left
  TURN_RIGHT,        ///< turn right
  TURN_COLINEAR_180, ///< continue onward
  TURN_COLINEAR_0    ///< turns back on same segment
};

/// point in, out, or on
enum PtInOutOrOn_enum {
  PT_ERROR = -1, ///< error
  PT_IN,         ///< in
  PT_OUT,        ///< out
  PT_ON          ///< on
};

//----- Forward declarations ---------------------------------------------------

//----- Global functions -------------------------------------------------------

// Tolerance
double gmComputeXyTol(const Pt3d& a_mn, const Pt3d& a_mx);
double gmXyTol(bool a_set = false, double a_value = 1e-9);
double gmZTol(bool a_set = false, double a_value = 1e-6);



// Extents
void gmAddToExtents(const Pt2d& a_pt, Pt3d& a_min, Pt3d& a_max);
void gmAddToExtents(const Pt3d& a_pt, Pt2d& a_min, Pt2d& a_max);
void gmAddToExtents(const Pt3d& a_pt, Pt3d& a_min, Pt3d& a_max);

void gmExtents2D(const VecPt3d& a_points, Pt2d& a_min, Pt2d& a_max);
void gmExtents2D(const VecPt3d& a_points, Pt3d& a_min, Pt3d& a_max);
void gmExtents3D(const VecPt3d& a_points, Pt3d& a_min, Pt3d& a_max);

void gmEnvelopeOfPts(const VecPt3d& a_pts, Pt3d& a_min, Pt3d& a_max);



// Angles
double gmAngleBetween2DVectors(double dxp, double dyp, double dxn, double dyn);
double gmAngleBetween2DVectors(double dxp,
                               double dyp,
                               double dxn,
                               double dyn,
                               double a_magn,
                               double a_magp);
double gmAngleBetween3DVectors(const Pt3d& v1, const Pt3d& v2);

double gmAngleBetweenEdges(const Pt2d& p1, const Pt2d& p2, const Pt2d& p3);
double gmAngleBetweenEdges(const Pt3d& p1, const Pt3d& p2, const Pt3d& p3);
double gmComputeDeviationInDirection(const Pt3d& a_p0, const Pt3d& a_p1, const Pt3d& a_p2);

double gmBisectingAngle(const Pt3d& a_p1, const Pt3d& a_p2, const Pt3d& a_p3);
double gmPerpendicularAngle(const Pt3d& a_pt1, const Pt3d& a_pt2);

void gmUnitVector2DPerp(const Pt3d& p1, const Pt3d& p2, Pt3d* v);


double gmConvertAngleToBetween0And360(double a_angle, bool a_InDegrees = true);
void gmConvertAngleBetweenXAndNorth(double* a_angle);

Turn_enum gmTurn(const Pt3d& a_v1, const Pt3d& a_v2, const Pt3d& a_v3, double a_angtol = 0.0017453);
bool gmLeftTurn(const Pt2d* v1, const Pt2d* v2, const Pt2d* v3);
bool gmLeftTurn(const Pt3d* v1, const Pt3d* v2, const Pt3d* v3);

bool gmStrictlyLeftTurn(const Pt3d*, const Pt3d*, const Pt3d*);



// Barycenters
int gmBaryToCart(const Pt3d* p1, const Pt3d* p2, const Pt3d* p3, const Pt3d* bary, Pt3d* cart);
int gmBaryPrepare(const Pt3d* p1,
                  const Pt3d* p2,
                  const Pt3d* p3,
                  const Pt3d* norm,
                  Pt3d* orig,
                  double coef[6],
                  int* dir,
                  bool flag);
int gmCartToBary(const Pt3d* cart, const Pt3d* orig, double coef[6], int dir, Pt3d* bary);



// Points equivalence
bool gmEqualPointsXY(double x1, double y1, double x2, double y2);
bool gmEqualPointsXY(double x1, double y1, double x2, double y2, double tolerance);
bool gmEqualPointsXY(const Pt2i& point1, const Pt2i& point2);
bool gmEqualPointsXY(const Pt2d& a_pt1, const Pt2d& a_pt2, double tol);
bool gmEqualPointsXY(const Pt3d& a_pt1, const Pt3d& a_pt2, double tol);
bool gmEqualPointsXYZ(double x1, double y1, double z1, double x2, double y2, double z2);
bool gmEqualPointsXYZ(double x1,
                      double y1,
                      double z1,
                      double x2,
                      double y2,
                      double z2,
                      double tolerance);
bool gmEqualPointsXYZ(const Pt3d& pt1, const Pt3d& pt2, double tol);



// Vector functions
double gmCross2D(const double& dx1, const double& dy1, const double& dx2, const double& dy2);
double gmCross2D(const Pt3d& a_origin, const Pt3d& a_A, const Pt3d& a_B);
void gmCross3D(const Pt3d& a_vec1, const Pt3d& a_vec2, Pt3d* a_vec3);
inline float gmDot3D(const Pt3f& vec1, const Pt3f& vec2);
inline double gmDot3D(const Pt3d& a_vec1, const Pt3d& a_vec2);
//-----------------------------------------------------------------------------
/// \brief Compute the 3D dot product of two vectors.
/// \param vec1: The first vector.
/// \param vec2: The second vector.
/// \returns The dot product of the two vectors.
//-----------------------------------------------------------------------------
inline float gmDot3Df(const Pt3f& vec1, const Pt3f& vec2)
{
  return (vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z);
}
int gmVectorAdd(double scale, const Pt3d& vec1, const Pt3d& vec2, Pt3d* sum);
void gmVectorAverage(const Pt3d& a, const Pt3d& b, Pt3d* result);
void gmVectorAverage(const Pt4d& a, const Pt4d& b, Pt4d* result);
void gmVectorRotate2D(const Pt3d& in, double a_angle, Pt3d& out);
void gmVectorSubtract(const Pt3d* vec1, const Pt3d* vec2, Pt3d* dif);
Pt3d gmUnitVector(const Pt3d& p1, const Pt3d& p2);
void gmComponentMagnitudes(double* a_x, double* a_y, double* a_mag, double* a_dir, bool a_tomagdir);
Pt3d gmCreateVector(const Pt3d& a_p1, const Pt3d& a_p2);



// Polygon bounds
template <typename T>
int gmPointInPolygon2D(const T* theverts,
                       const size_t numverts,
                       const double xpt,
                       const double ypt,
                       const double tol);
int gmPointInPolygon2D(const Pt2i* a_verts, size_t a_num, Pt2i a_pt);
int gmPointInPolygon2D(const Pt2i* a_verts, size_t a_num, Pt2d a_pt);
int gmPointInPolygon2D(const Pt2i* a_verts, size_t a_num, Pt3d a_pt);
int gmPointInPolygon2D(const Pt3d* a_verts, size_t a_num, double a_x, double a_y);
int gmPointInPolygon2D(const Pt3d* a_verts, size_t a_num, Pt3d a_pt);
int gmPointInPolygon2D(const VecPt3d& a_verts, const Pt3d& a_pt);

int gmPointInPolygon3DWithTol(const Pt3d& pt,
                              int nvtx,
                              const Pt3d* vertex,
                              const int* poly,
                              const Pt3d& nrm,
                              double tol);
bool gmPointsInRadiusXY(const Pt3d& pt1, const Pt3d& pt2, double radius);
bool gmPointsInRadiusXY(double x1, double y1, double x2, double y2, double radius);
PtInOutOrOn_enum gmPtInCircumcircle(const Pt3d& pt, Pt3d circumcirclePts[3]);
bool gmPointInOrOnBox2d(const Pt3d& a_bMin, const Pt3d& a_bMax, const Pt3d& a_pt);

bool gmPointInRect(const Pt2i& thepoint, const Pt2i& tl, const Pt2i& br);
bool gmPointInRect(const Pt3d& a_pt, const Pt3d& a_tl, const Pt3d& a_br);
bool gmPointInRect2(const Pt3d& thepoint, double etop, double ebottom, double eleft, double eright);
bool gmPointInTriangle(const Pt3d* p1, const Pt3d* p2, const Pt3d* p3, double x, double y);
bool gmPointInTriangleWithTol(const Pt3d* p1,
                              const Pt3d* p2,
                              const Pt3d* p3,
                              double x,
                              double y,
                              double tol);
//------------------------------------------------------------------------------
/// \brief Test if the centroid is inside any of the given polygons.
/// \param a_insides: A vector of polygons.
/// \param a_centroid: The centroid.
/// \return Whether the centroid is within any of the given polygons.
//------------------------------------------------------------------------------
template <typename T, typename U>
bool gmInsideInner(T a_insides, U a_centroid)
{
  bool inside_hole = false;
  for (size_t i = 0; i < a_insides.size() && !inside_hole; ++i)
  {
    inside_hole = (gmPointInPolygon2D(&a_insides[i][0], (int)a_insides[i].size(), a_centroid) >= 0);
  }
  return inside_hole;
} // gmInsideInner


// Distance
double gm2DDistanceToLineSegment(const Pt3d&, const Pt3d&, const Pt3d&);
double gm2DDistanceToLineSegmentWithTol(const Pt3d* pt1,
                                        const Pt3d* pt2,
                                        double x,
                                        double y,
                                        double tol);
double gm2DDistanceToLineWithTol(const Pt3d* a_pt1,
                                 const Pt3d* a_pt2,
                                 double a_x,
                                 double a_y,
                                 double a_tol);

double gmXyDistance(const Pt3d& pt1, const Pt3d& pt2);
double gmXyDistance(double x1, double y1, double x2, double y2);
double gmXyDistanceSquared(const Pt3d& pt1, const Pt3d& pt2);
double gmXYZDistanceBetweenPoints(const Pt4d& p1, const Pt4d& p2);
double gmXYZDistanceBetweenPoints(const Pt3d& p1, const Pt3d& p2);
double gmXYZDistanceSquared(const Pt3d& p1, const Pt3d& p2);

double gmGreatCircleDistanceMeters(const Pt2d& a_pt1, const Pt2d& a_pt2);

double gmMinDistBetweenLinesWithTol(const Pt3d* p0,
                                    const Pt3d* p1,
                                    const Pt3d* q0,
                                    const Pt3d* q1,
                                    Pt3d* ip1,
                                    Pt3d* ip2,
                                    double* t,
                                    double* s,
                                    double tol);
double gmDistanceFromPointToPlane(const Pt3d& pt1,
                                  const Pt3d& pt2,
                                  const Pt3d& pt3,
                                  const Pt3d& thePoint);



// Clipping
void gmClipNDCPoly(int* npts, Pt4d* pts);
bool gmClipMpoint3PolyToRect(Pt3d pts[],
                             int n,
                             Pt3d* outpts[],
                             int* outCount,
                             double xMax,
                             double xMin,
                             double yMax,
                             double yMin);
int gmComputeClipCodes2(double x, double y, double minx, double maxx, double miny, double maxy);
int gmClipLine(double* x1,
               double* y1,
               double* x2,
               double* y2,
               int OC1,
               int OC2,
               double minx,
               double maxx,
               double miny,
               double maxy);



// Intersection
bool gmIntersectLineSegmentsWithTol(const Pt3d& one1,
                                    const Pt3d& one2,
                                    const Pt3d& two1,
                                    const Pt3d& two2,
                                    double* xi,
                                    double* yi,
                                    double* zi1,
                                    double* zi2,
                                    double tol);
bool gmIntersectLineSegmentsNoTol(const Pt3d& one1,
                                  const Pt3d& one2,
                                  const Pt3d& two1,
                                  const Pt3d& two2,
                                  double* xi,
                                  double* yi,
                                  double* zi1,
                                  double* zi2,
                                  double = 0.0);
//------------------------------------------------------------------------------
/// \brief Find the plan projection intersection of two line segments.
/// \note: segment 1 = one1,one2  = one1 + lambda(one2 - one1).
///        segment 2 = two1,two2  = two1 + mu (two2 - two1).
/// \note: This function is here for inlining.
/// \param one1: First point on segment 1.
/// \param one2: Second point on segment 1.
/// \param two1: First point on segment 2.
/// \param two2: Second point on segment 2.
/// \param xi: Initialized to the x coord of intersection.
/// \param yi: Initialized to the y coord of intersection.
/// \param zi1: Initialized to the z coord of intersection on segment 1.
/// \param zi2: Initialized to the z coord of intersection on segemnt 2.
/// \param tol: Tolerance for geometric comparison.
/// \return Whether the line segments intersect.
//------------------------------------------------------------------------------
inline bool gmIntersectLineSegments(const Pt3d& one1,
                                    const Pt3d& one2,
                                    const Pt3d& two1,
                                    const Pt3d& two2,
                                    double* xi,
                                    double* yi,
                                    double* zi1,
                                    double* zi2)
{
  return gmIntersectLineSegmentsWithTol(one1, one2, two1, two2, xi, yi, zi1, zi2, gmXyTol());
}
bool gmIntersectSegmentWithLine(const Pt2d& p1,
                                const Pt2d& p2,
                                const Pt2d& l1,
                                const Pt2d& l2,
                                Pt2d* inter);
bool gmIntersectSegmentWithLine(const Pt2d& p1,
                                const Pt2d& p2,
                                const Pt2d& l1,
                                const Pt2d& l2,
                                Pt2d* inter,
                                double tol);
bool gmIntersectSegmentWithLine(const Pt3d& p1,
                                const Pt3d& p2,
                                const Pt3d& l1,
                                const Pt3d& l2,
                                Pt3d* inter);
bool gmIntersectSegmentWithLine(const Pt3d& p1,
                                const Pt3d& p2,
                                const Pt3d& l1,
                                const Pt3d& l2,
                                Pt3d* inter,
                                double tol);
bool gmIntersectLines(const Pt3d& one1,
                      const Pt3d& one2,
                      const Pt3d& two1,
                      const Pt3d& two2,
                      double* xi,
                      double* yi,
                      double tol);
bool gmIntersectLines(const Pt3d& one1,
                      const Pt3d& one2,
                      const Pt3d& two1,
                      const Pt3d& two2,
                      double* xi,
                      double* yi,
                      double* zi,
                      double tol);
bool gmIntersectLines(const Pt3d& one1,
                      const Pt3d& one2,
                      const Pt3d& two1,
                      const Pt3d& two2,
                      double* xi,
                      double* yi,
                      double* zi,
                      double& onet,
                      double& twot,
                      double tol);
bool gmLinesIntersect(const Pt3d& one1, const Pt3d& one2, const Pt3d& two1, const Pt3d& two2);
bool gmLinesCross(const Pt3d& a_segment1Point1,
                  const Pt3d& a_segment1Point2,
                  const Pt3d& a_segment2Point1,
                  const Pt3d& a_segment2Point2);

int gmIntersectTriangleAndLineSegment(const Pt3d& a_pt1,
                                      const Pt3d& a_pt2,
                                      const Pt3d& a_t0,
                                      const Pt3d& a_t1,
                                      const Pt3d& a_t2,
                                      Pt3d& a_IntersectPt);
bool gmLineAndTriangleIntersect(const Pt3d& origin,
                                const Pt3d& vert1,
                                const Pt3d& v30,
                                const Pt3d& v31,
                                const Pt3d& v32,
                                Pt3d* theisect = NULL);

void gmSphereLineIntersection(const Pt3d& a_l1,
                              const Pt3d& a_l2,
                              const Pt3d& a_sc,
                              double a_r,
                              VecPt3d& a_pts);

int gmIntersectPlnWithPolWithTol(const double pln[4],
                                 int nnodes,
                                 Pt3d* poly,
                                 const double tripln[4],
                                 Pt3d seg[2],
                                 double tol);



// Testing if points are in/on lines and planes
int gmClassifyPointFromPlane(const Pt3d& point1,
                             const Pt3d& point2,
                             const Pt3d& point3,
                             const Pt3d& oppositepoint,
                             double x,
                             double y,
                             double z,
                             double tolerance);
int gmClassifyPointFromPlane(double a,
                             double b,
                             double c,
                             double d,
                             const Pt3d& oppositepoint,
                             const Pt3d& pt,
                             double tolerance);
bool gmOnLineAndBetweenEndpoints(const Pt3d* p1, const Pt3d* p2, const double x, const double y);
bool gmOnLineAndBetweenEndpointsWithTol(const Pt3d& a_pt1,
                                        const Pt3d& a_pt2,
                                        const double a_x,
                                        const double a_y,
                                        double a_tol);
bool gmMiddleThird(const Pt3d* v1, const Pt3d* v2, const Pt3d* v3);
bool gmMiddleThirdWithTol(const Pt3d& v1, const Pt3d& v2, const Pt3d& v3, double tol);

bool gmOnLine(const Pt3d* p1, const Pt3d* p2, const double x, const double y);
bool gmOnLineWithTol(const Pt3d& p1,
                     const Pt3d& p2,
                     const double x,
                     const double y,
                     const double tol);

bool gmInsideOrOnLine(const Pt3d* p1,
                      const Pt3d* p2,
                      const Pt3d* oppositepoint,
                      const double x,
                      const double y);
bool gmInsideOrOnLineWithTol(const Pt3d* p1,
                             const Pt3d* p2,
                             const Pt3d* inpoint,
                             const double x,
                             const double y,
                             const double tol,
                             double* dist = NULL);
bool gmInsideOfLineWithTol(const Pt3d& a_vertex1,
                           const Pt3d& a_vertex2,
                           const Pt3d& a_oppositevertex,
                           const double a_x,
                           const double a_y,
                           const double a_tol);



// Finding points on lines
double gmNearestPointOnLineSegment2D(const Pt3d& p1, const Pt3d& p2, const Pt3d& q, Pt3d* thepoint);
double gmPtDistanceAlongSegment(const Pt3d& a_pt1,
                                const Pt3d& a_pt2,
                                const Pt3d& a_pt,
                                const double a_tol);
double gmFindClosestPtOnSegment(const Pt3d& a_pt1,
                                const Pt3d& a_pt2,
                                const Pt3d& a_pt,
                                Pt3d& a_newpt,
                                const double a_tol);
//------------------------------------------------------------------------------
/// \brief Find the closest point on a segment to another point.
/// \param[in] pt1: First endpoint of segment.
/// \param[in] pt2: Second endpoint of segment.
/// \param[in] pt: Test point.
/// \param[out] newpt: Initialized to the point on the segment that is
///                    closest to the test point.
/// \param[in] tol: Tolerance.
/// \return Parametric value along the line a_pt1, a_pt2 that is the location
///         of a_newpt.
//------------------------------------------------------------------------------
template <typename T>
double gmFindClosestPtOnSegment(const T& pt1,
                                const T& pt2,
                                const T& pt,
                                T& newpt,
                                const double* tol = nullptr)
{
  double dx(0.0), dy(0.0);

  const double t = gmPtDistanceAlongSegment(pt1, pt2, pt, tol, &dx, &dy);
  if (t < 0.0)
  {
    newpt.x = pt1.x;
    newpt.y = pt1.y;
  }
  else if (t > 1.0)
  {
    newpt.x = pt2.x;
    newpt.y = pt2.y;
  }
  else
  {
    newpt.x = pt1.x + dx * t;
    newpt.y = pt1.y + dy * t;
  }
  return t;
} // gmFindClosestPtOnSegment
double gmFindClosestPtOnSegment2D(const Pt3d& pt1,
                                  const Pt3d& pt2,
                                  const Pt3d& pt,
                                  double dx,
                                  double dy,
                                  double mag2,
                                  Pt3d* newpt);
double gmFindClosestPtOnSegment3D(const Pt3d& pt1, const Pt3d& pt2, const Pt3d& pt, Pt3d* newpt);

//------------------------------------------------------------------------------
/// \brief Find the distance along a segment to a given point. Distance is a
///        proportion of the segment's length, from 0 to 1.
/// \param pt1: The first endpoint of the segment.
/// \param pt2: The second endpoint of the segment.
/// \param pt: The test point.
/// \param a_dx: Initialized to the horizontal length of the line.
/// \param a_dy: Initialized to the vertical length of the line.
/// \return The distance along the segment to the point. May be <0 or >1 if the
///         test point is not on the line.
//------------------------------------------------------------------------------
template <typename T>
double gmPtDistanceAlongSegment(const T& pt1,
                                const T& pt2,
                                const T& pt,
                                const double* tol = NULL,
                                double* a_dx = NULL,
                                double* a_dy = NULL)
{
  double dx, dy, t;

  dx = pt2.x - pt1.x;
  dy = pt2.y - pt1.y;

  if ((tol == NULL && (dx == 0.0 && dy == 0.0)) ||
      (tol != NULL && (sqrt(dx * dx + dy * dy) <= *tol)))
  {
    t = -1.0;
  }
  else
  {
    t = ((pt.x - pt1.x) * dx + (pt.y - pt1.y) * dy) / (dx * dx + dy * dy);
  }

  if (a_dx)
  {
    *a_dx = dx;
  }
  if (a_dy)
  {
    *a_dy = dy;
  }

  return t;
} // gmPtDistanceAlongSegment


// Vertex ordering
bool gmCounterClockwiseTri(const Pt3d& vtx0, const Pt3d& vtx1, const Pt3d& vtx2);
bool gmCounterClockwiseQuad(const Pt3d& da1, const Pt3d& db1, const Pt3d& da2, const Pt3d& db2);

void gmMakePolygonClockwise(Pt2i* pts, int numpts);
void gmMakePolygonClockwise(Pt3d* pts, int numpts);

void gmMakePolygonCounterclockwise(Pt2i* pts, int numpts);
void gmMakePolygonCounterclockwise(Pt3d* pts, int numpts);
void gmOrderPointsCounterclockwise(const VecPt3d& a_pts, VecInt& a_ccwOrder, int a_startindex = 0);
void gmOrderPointsCounterclockwise(VecPt3d& a_pts);


// Planes
Pt3f gmComputePlaneNormal(const Pt3f& point1, const Pt3f& point2, const Pt3f& point3);
Pt3d gmComputePlaneNormal(const Pt3d& point1, const Pt3d& point2, const Pt3d& point3);
Pt3d gmComputePlaneNormal(const Pt4d& point1, const Pt4d& point2, const Pt4d& point3);

Pt3f gmComputeUnitPlaneNormal(const Pt3f& pt1, const Pt3f& pt2, const Pt3f& pt3);
Pt3d gmComputeUnitPlaneNormal(const Pt3d& pt1, const Pt3d& pt2, const Pt3d& pt3);

void gmCalculatePlaneCoeffs(const Pt3d& point1,
                            const Pt3d& point2,
                            const Pt3d& point3,
                            double* a,
                            double* b,
                            double* c,
                            double* d);
void gmCalculatePlaneCoefficients(const Pt3d* p1,
                                  const Pt3d* p2,
                                  const Pt3d* p3,
                                  double* a,
                                  double* b,
                                  double* c,
                                  double* d);
void gmCalculatePlaneCoeffs(const Pt3d* p1,
                            const Pt3d* p2,
                            const Pt3d* p3,
                            double* a,
                            double* b,
                            double* c,
                            double* d,
                            double tol = XM_ZERO_TOL);
void gmCalculateNormalizedPlaneCoefficients(const Pt3d& p1,
                                            const Pt3d& p2,
                                            const Pt3d& p3,
                                            double* a,
                                            double* b,
                                            double* c,
                                            double* d);
void gmCalculateNormalizedPlaneCoefficients(const Pt3d* p1,
                                            const Pt3d* p2,
                                            const Pt3d* p3,
                                            double* a,
                                            double* b,
                                            double* c,
                                            double* d);
void gmCalculatePointsFromPlane(Pt3d* p1,
                                Pt3d* p2,
                                Pt3d* p3,
                                double a,
                                double b,
                                double c,
                                double d);
double gmCalculateZFromPlaneCoefficients(double x,
                                         double y,
                                         double a,
                                         double b,
                                         double c,
                                         double d);


// Interpolation/Extrapolation
Pt3d gmInterpolateMpoint3(const Pt3d& p1, const Pt3d& p2);
double* gmDistributeValues(const double* in, int nin, int nout, double bias);
Pt3d* gmLinearSubdivideLine(const Pt3d& endpt1, const Pt3d& endpt2, int numdiv);

// TODO: No definition?
// void gmExtrapolatePoints(const Pt3d*, const Pt3d*, Pt3d*, double*, int, int);
void gmExtrapolatePointsWithTol(const Pt3d* col1,
                                const Pt3d* col2,
                                Pt3d* newcol,
                                double* pcnt,
                                int np1,
                                int np2,
                                double tol);


// Normalization
void gmNormalizeXYZ(const Pt3d& vect, Pt3d* norm);
void gmNormalizeXYZ(const Pt3f& vect, Pt3f* norm);
double gmNormalizeXYZWithMag(const Pt3d& vect, Pt3d* norm);
int gmNormalizeXYWithMag(const Pt2d& vect, Pt2d* norm, double* magvec);


// Area and Volume
double gmPolygonArea(const Pt2i* points, size_t npoints);
double gmPolygonArea(const Pt3d* pts, size_t npoints);
template <class PointIter>
double gmPolygonArea(PointIter a_begin, PointIter a_end);
//------------------------------------------------------------------------------
/// \brief Compute the area of a polygon.
/// \param a_begin: An iterator to the beginning of a list of points defining
///                 the polygon.
/// \param a_end: An iterator pointing to the end of the list.
/// \return The area of the polygon.
//------------------------------------------------------------------------------
template <class PointIter>
double gmPolygonArea(PointIter a_begin, PointIter a_end)
{
  double area = 0.0;
  if (a_begin == a_end)
    return area;

  // This implementation translates the polygon so the first point is at
  // the origin. This reduces roundoff error due to large coordinates
  // and reduces the number of computations because the first and last
  // computations in the loop would be 0.

  PointIter itr = a_begin;
  VecDbl x, y;
  int id = 0;
  int npts = 1;
  double x0 = (double)itr->x;
  double y0 = (double)itr->y;
  ++itr;
  for (; itr != a_end; ++itr)
  {
    ++npts;
    x.push_back((double)itr->x - x0);
    y.push_back((double)itr->y - y0);
  }
  if (npts < 3)
    return area;
  for (id = 0; id < npts - 2; id++)
  {
    area += (x[id] * y[id + 1]);
    area -= (y[id] * x[id + 1]);
  }

  area /= 2.0;
  return (area);
} // gmPolygonArea
double gmTetrahedronVolumeMpoint3(const Pt3d& point1,
                                  const Pt3d& point2,
                                  const Pt3d& point3,
                                  const Pt3d& point4,
                                  bool* error);


// Projections
Pt3d gmProjectVectorToPlane(const Pt3d& vector, int plane);
int gmProjectTriangleToPln(const Pt3d& v0, const Pt3d& v1, const Pt3d& v2);



// Colinear and coplanar
bool gmColinear(const Pt3d* p1, const Pt3d* p2, const Pt3d* p3);
bool gmColinearWithTol(const Pt3d& p1, const Pt3d& p2, const Pt3d& p3, const double tol);
bool gmCoplanarWithTol(const Pt3d& v1,
                       const Pt3d& v2,
                       const Pt3d& v3,
                       const Pt3d& v4,
                       double tolerance);


// Circumscription
bool gmCircumcircle(const Pt3d* pt1,
                    const Pt3d* pt2,
                    const Pt3d* pt3,
                    double* xc,
                    double* yc,
                    double* r2);
bool gmCircumcircleWithTol(const Pt3d* pt1,
                           const Pt3d* pt2,
                           const Pt3d* pt3,
                           double* xc,
                           double* yc,
                           double* r2,
                           double tol);


// Utility functions
VecPt3d gmArrayToVecPt3d(double* a_array, int a_size);
int gmThreeEqualZSWithTol(double z1, double z2, double z3, double tol);
void gmSplitPtVector(const VecPt3d& a_pt, VecDbl& a_x, VecDbl& a_y, VecDbl& a_z);
void gmRemoveAdjacentDuplicatePoints2D(VecPt3d& a_pts, double a_tol);
//------------------------------------------------------------------------------
/// \brief Find the minimum and maximum value in an array of values.
/// \param a_vector: The array to search.
/// \param a_size: The number of elements in the array.
/// \param a_max: Initialized to the maximum value of the array.
/// \param a_min: Initialized to the minimum value of the array.
//------------------------------------------------------------------------------
template <class T>
void gmVectorMaxMin(const T* a_vector, int a_size, T* a_max, T* a_min)
{
  int i;
  T mymax, mymin;

  mymax = a_vector[0];
  mymin = a_vector[0];
  for (i = 1; i < a_size; i++)
  {
    mymax = Mmax(mymax, a_vector[i]);
    mymin = Mmin(mymin, a_vector[i]);
  }
  *a_max = mymax;
  *a_min = mymin;

} // gmVectorMaxMin


// Misc.
bool gmBoxesOverlap2d(const Pt3d& a_b1Min,
                      const Pt3d& a_b1Max,
                      const Pt3d& a_b2Min,
                      const Pt3d& a_b2Max);
int gmBoxOverlap(const Pt3d& min1, const Pt3d& max1, const Pt3d& min2, const Pt3d& max2);

bool gmComputeLineEquation(const Pt3d& pt1,
                           const Pt3d& pt2,
                           double& a,
                           double& b,
                           double& c,
                           double tol);
Pt3d gmComputeCentroid(const VecPt3d& a_points);
Pt3d gmComputePolygonCentroid(const VecPt3d& pts);

double gmMiddleZ(const VecPt3d& a_points);

bool gmQuadToTriAreaCheck(const Pt3d& da1, const Pt3d& db1, const Pt3d& da2, const Pt3d& db2);

void gmGetConvexHull(const VecPt3d& a_pts, VecPt3d& a_hull, bool a_includeOn = false);

double gmCalculateCelerity(double period, double depth, double gravity);
double gmCalculateWavelength(double period, double depth, double gravity);

} // namespace xms
