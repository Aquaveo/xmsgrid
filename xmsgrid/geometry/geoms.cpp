//------------------------------------------------------------------------------
/// \file
/// \brief Functions dealing with geometry.
/// \ingroup geometry
/// \copyright (C) Copyright Aquaveo 2018. Distributed under FreeBSD License
/// (See accompanying file LICENSE or https://aqaveo.com/bsd/license.txt)
//------------------------------------------------------------------------------

// 1. Precompiled header

// 2. My own header
#include <xmsgrid/geometry/geoms.h>

// 3. Standard library headers
#include <cfloat>
#include <algorithm>

// 4. External library headers

// 5. Shared code headers
#include <xmscore/math/math.h> // GT_TOL, LT_TOL
#include <xmscore/misc/XmError.h>
#include <xmscore/points/pt.h> // Pt3d
#include <xmscore/stl/vector.h>
#include <xmsgrid/geometry/GmPolygon.h>
#include <xmscore/misc/xmstype.h> // XM_ZERO_TOL
#include <xmsgrid/triangulate/triangles.h>
#include <xmscore/misc/XmConst.h>

// 6. Non-shared code headers

//----- Namespace declaration --------------------------------------------------

namespace xms
{
//----- Constants / Enumerations -----------------------------------------------
#define LEFT_MASK 1
#define RIGHT_MASK 2
#define BOTTOM_MASK 4
#define TOP_MASK 8

//----- Forward declarations ---------------------------------------------------

//----- External globals -------------------------------------------------------

//----- Internal function prototypes -------------------------------------------

namespace
{
//------------------------------------------------------------------------------
/// \brief Compute the cross product of two 2d vectors.
/// \param v0: First vector.
/// \param v1: Second vector.
/// \return The cross product.
//------------------------------------------------------------------------------
static double gmiCross2D(const Pt2d& v0, const Pt2d& v1)
{
  return v0.x * v1.y - v0.y * v1.x;
}
//------------------------------------------------------------------------------
/// \brief Test if an instance of a Turn_enum represents a right turn.
/// \param turn: The Turn_enum instance to test.
/// \param includeCollinear: Whether to classify 180 degree turns
///        as right turns.
/// \return Whether the turn was classified as a right turn.
//------------------------------------------------------------------------------
bool isRightTurn(Turn_enum turn, bool includeCollinear)
{
  if (includeCollinear)
    return turn == TURN_RIGHT || turn == TURN_COLINEAR_180;
  else
    return turn == TURN_RIGHT;
} // isRightTurn
//------------------------------------------------------------------------------
/// \brief Adds a new point to an array of points, resizing the array if
///        necessary.
/// \author MJK.
/// \param points: The array to add a point to.
/// \param n: The index of the last point in the array. Initialized to the index
///           of the new last point in the array.
/// \param a: x coordinate of the new point.
/// \param b: y coordinate of the new point.
/// \param numalloced: The size of the array. Initialized to the new size of
///                    the array if the array is resized.
/// \return Whether the operation could be completed.
//------------------------------------------------------------------------------
bool gmiOutputMpoint3Vert(Pt3d* points[], int* n, double a, double b, int* numalloced)
{
  (*n)++;
  if (*n > *numalloced)
  { /* See if array is big enough. If not, add some more */
    *numalloced += 25;
    *points = (Pt3d*)realloc(*points, *numalloced * sizeof(Pt3d));
    if (!*points)
    {
      // gnNullMemoryErrorMessage("cpiOutputVert");
      return false;
    }
  }
  (*points)[(*n) - 1].x = a;
  (*points)[(*n) - 1].y = b;
  return true;
} // gmiOutputMpoint3Vert
//------------------------------------------------------------------------------
/// \brief Find the plan projection intersection of two line segments.
/// \note line v01 defined by points p0 and p1.
///       line v23 defined by points p2 and p3.
/// \param p0: First point on first line.
/// \param p1: Second point on first line.
/// \param p2: First point on second line.
/// \param p3: Second point on second line.
/// \param xi: x coordinate of intersection point.
/// \param yi: y coordinate of intersection point.
/// \param t01: % distance (0.0 to 1.0) of intersection on line 1 from p0.
/// \param t23: % distance (0.0 to 1.0) of intersection on line 2 from p2.
/// \return Whether the lines intersect.
//------------------------------------------------------------------------------
static bool gmiIntersectLines2D(const Pt3d& p0,
  const Pt3d& p1,
  const Pt3d& p2,
  const Pt3d& p3,
  double* xi,
  double* yi,
  double& t01,
  double& t23)
{
  // Derivation Notes (Rob Zundel)
  // Let vab be the vector from 2d point pa to point pb; OR vab = pb - pa;
  // So v01 and v23 represent the vectors from points p0 to p1 and p2 to p3.
  // Let pt be any point on v23 = p2 + t*v23.
  // let cross(va, vb) = va.x*vb.y - vb.x*va.y
  // At the intersection point pi (on v23), pi = p2 + i*v23
  // then v0i is parallel to v01 and cross(v01,v0i) == 0,
  // 0 = cross(v01,v0i) = v01.x*v0i.y - v01.y*v0i.x
  //   = v01.x*(pi.y - p0.y) - v01.y*(pi.x - p0.x)
  //   = v01.x*(p2.y + i*v23.y - p0.y) - v01.y*(p2.x + i*(v23.x) - p0.x)
  //   = v01.x*(p2.y-p0.y) - v01.y*(p2.x-p0.x) + i*(v01.x*v23.y - v01.y*v23.x)
  //    = v01.x* v02.y      - v01.y*v02.x       + i*(cross(v01,v23))
  //   = cross(v01,v02) + i*cross(v01,v23)
  // i = -cross(v01,v02) / cross(v01,v23)
  //   = cross(v02,v01)/cross(v01,v23)

  // for pj = p0 + j*(v01) as the point on v01 that intersect with v23
  // 0 = cross(v23,v2j) = v23.x*v2j.y - v23.y*v2j.x
  //   = v23.x*(pj-p2).y - v23.y*(pj-p2).x
  //   = v23.x*(p0.y + j*v01.y - p2.y) - v23.y*(p0.x + j*v01.x - p2.x)
  //   = v23.x*v20.y - v23.y*v20.x + j*(v23.x*v01.y - v23.y*v01.x)
  //   = cross(v23,v20) + j*(cross(v23,v01))
  // j = -cross(v23,v20) / cross(v23,v01) = cross(v20,v23) / cross(v23,v01)
  //   =  cross(v02,v23) / cross(v01,v23)

  Pt2d v01(p1);
  v01 -= p0;
  Pt2d v23(p3);
  v23 -= p2;
  Pt2d v02(p2);
  v02 -= p0;

  // The angle between the lines, and hence this cross product will be 0 if the
  // lines are parallel.  Avoid division by zero.
  double v01xv23 = gmiCross2D(v01, v23);
  if (EQ_EPS(fabs(v01xv23), 0.0, DBL_EPSILON))
  {
    return false;
  }
  // t01,t23 are i,j in explanation above. Parameters of intersection points
  // from p0 to p1 and from p2 to p3, respectively.
  t01 = (v01xv23 ? gmiCross2D(v02, v23) / v01xv23 : 0);
  t23 = (v01xv23 ? gmiCross2D(v02, v01) / v01xv23 : 0);

  // compute intersection
  *xi = p2.x + t23 * v23.x;
  *yi = p2.y + t23 * v23.y;
  return true;
} // gmiIntersectLines2D
}

//------------------------------------------------------------------------------
/// \brief Updates a_min and a_max such that the coordinates of a_min are less
///        than or equal to the respective coordinates of a_pt, and the
///        coordinates of a_max are greater than or equal to the respective ones
///        in a_pt.
/// \param[in] a_pt: A point.
/// \param[in,out] a_min: Minimum.
/// \param[in,out] a_max: Maximum.
//------------------------------------------------------------------------------
void gmAddToExtents(const Pt2d& a_pt, Pt3d& a_min, Pt3d& a_max)
{
  a_min.x = std::min(a_pt.x, a_min.x);
  a_min.y = std::min(a_pt.y, a_min.y);
  a_max.x = std::max(a_pt.x, a_max.x);
  a_max.y = std::max(a_pt.y, a_max.y);
} // gmAddToExtents
//------------------------------------------------------------------------------
/// \brief Updates a_min and a_max such that the coordinates of a_min are less
///        than or equal to the respective coordinates of a_pt, and the
///        coordinates of a_max are greater than or equal to the respective ones
///        in a_pt.
/// \param[in] a_pt: A point.
/// \param[in,out] a_min: Minimum.
/// \param[in,out] a_max: Maximum.
//------------------------------------------------------------------------------
void gmAddToExtents(const Pt3d& a_pt, Pt2d& a_min, Pt2d& a_max)
{
  a_min.x = std::min(a_pt.x, a_min.x);
  a_min.y = std::min(a_pt.y, a_min.y);
  a_max.x = std::max(a_pt.x, a_max.x);
  a_max.y = std::max(a_pt.y, a_max.y);
} // gmAddToExtents
//------------------------------------------------------------------------------
/// \brief Updates a_min and a_max such that the coordinates of a_min are less
///        than or equal to the respective coordinates of a_pt, and the
///        coordinates of a_max are greater than or equal to the respective ones
///        in a_pt.
/// \param[in] a_pt: A point.
/// \param[in,out] a_min: Minimum.
/// \param[in,out] a_max: Maximum.
//------------------------------------------------------------------------------
void gmAddToExtents(const Pt3d& a_pt, Pt3d& a_min, Pt3d& a_max)
{
  a_min.x = std::min(a_pt.x, a_min.x);
  a_min.y = std::min(a_pt.y, a_min.y);
  a_min.z = std::min(a_pt.z, a_min.z);
  a_max.x = std::max(a_pt.x, a_max.x);
  a_max.y = std::max(a_pt.y, a_max.y);
  a_max.z = std::max(a_pt.z, a_max.z);
} // gmAddToExtents
//------------------------------------------------------------------------------
/// \brief Get the 2D extents of a vector of points.
/// \param[in] a_points: The points.
/// \param[out] a_min: Minimum point (xy) of bounding rectangle.
/// \param[out] a_max: Maximum point (xy) of bounding rectangle.
//------------------------------------------------------------------------------
void gmExtents2D(const VecPt3d& a_points, Pt2d& a_min, Pt2d& a_max)
{
  XM_ENSURE_TRUE_VOID_NO_ASSERT(!a_points.empty());

  a_min.x = a_max.x = a_points.at(0).x;
  a_min.y = a_max.y = a_points.at(0).y;
  for (int i = 1; i < (int)a_points.size(); i++)
  {
    gmAddToExtents(a_points[i], a_min, a_max);
  }
} // gmExtents2D
//------------------------------------------------------------------------------
/// \brief Get the 2D extents of a vector of points.
/// \param[in] a_points: Vector of points.
/// \param[in,out] a_min: Minimum value.
/// \param[in,out] a_max: Maximum value.
//------------------------------------------------------------------------------
void gmExtents2D(const VecPt3d& a_points, Pt3d& a_min, Pt3d& a_max)
{
  XM_ENSURE_TRUE_VOID_NO_ASSERT(!a_points.empty());

  a_min.x = a_max.x = a_points.at(0).x;
  a_min.y = a_max.y = a_points.at(0).y;
  a_min.z = a_max.z = 0.0;
  for (int i = 1; i < (int)a_points.size(); i++)
  {
    gmAddToExtents((Pt2d)a_points[i], a_min, a_max);
  }
} // gmExtents2D
//------------------------------------------------------------------------------
/// \brief Get the 3D extents of a vector of points.
/// \param[in] a_points: The points.
/// \param[out] a_min: Minimum point (xyz) of bounding box.
/// \param[out] a_max: Maximum point (xyz) of bounding box.
//------------------------------------------------------------------------------
void gmExtents3D(const VecPt3d& a_points, Pt3d& a_min, Pt3d& a_max)
{
  XM_ENSURE_TRUE_VOID_NO_ASSERT(!a_points.empty());

  a_min.x = a_max.x = a_points.at(0).x;
  a_min.y = a_max.y = a_points.at(0).y;
  a_min.z = a_max.z = a_points.at(0).z;
  for (int i = 1; i < (int)a_points.size(); i++)
  {
    gmAddToExtents(a_points[i], a_min, a_max);
  }
} // gmExtents3D
//------------------------------------------------------------------------------
/// \brief Calculate the envelope of a vector of points
/// \param[in] a_pts: Array of points
/// \param[out] a_min: Min x,y,z of the points
/// \param[out] a_max: Max x,y,z of the points
//------------------------------------------------------------------------------
void gmEnvelopeOfPts(const VecPt3d& a_pts, Pt3d& a_min, Pt3d& a_max)
{
  a_min = a_max = Pt3d();
  XM_ENSURE_TRUE(!a_pts.empty());
  a_min = a_max = a_pts.front();
  for (size_t i = 0; i < a_pts.size(); ++i)
  {
    if (a_pts[i].x < a_min.x)
      a_min.x = a_pts[i].x;
    if (a_pts[i].y < a_min.y)
      a_min.y = a_pts[i].y;
    if (a_pts[i].z < a_min.z)
      a_min.z = a_pts[i].z;
    if (a_pts[i].x > a_max.x)
      a_max.x = a_pts[i].x;
    if (a_pts[i].y > a_max.y)
      a_max.y = a_pts[i].y;
    if (a_pts[i].z > a_max.z)
      a_max.z = a_pts[i].z;
  }
} // gmEnvelopeOfPts
//------------------------------------------------------------------------------
/// \brief Compute the angle, in radians, between the edges p and n.
///        based on a ccw rotation from p to n.
/// \note Computed angle will be in the range [0-2PI).
/// \param[in] dxp: x coordinate of vector p.
/// \param[in] dyp: y coordinate of vector p.
/// \param[in] dxn: x coordinate of vector n.
/// \param[in] dyn: y coordinate of vector n.
/// \return The angle between p and n.
//------------------------------------------------------------------------------
double gmAngleBetween2DVectors(double dxp, double dyp, double dxn, double dyn)
{
  double magn, magp;

  magn = sqrt(sqr(dxn) + sqr(dyn));
  magp = sqrt(sqr(dxp) + sqr(dyp));
  return gmAngleBetween2DVectors(dxp, dyp, dxn, dyn, magn, magp);
} // gmAngleBetween2DVectors
//------------------------------------------------------------------------------
/// \brief Compute the angle, in radians, between the edges p and n.
///        based on a ccw rotation from p to n.
/// \note Computed angle will be in the range [0-2PI).
/// \param[in] dxp: x component of vector p.
/// \param[in] dyp: y component of vector p.
/// \param[in] dxn: x component of vector n.
/// \param[in] dyn: y component of vector n.
/// \param[in] a_magn: Magnitude of n.
/// \param[in] a_magp: Magnitude of p.
/// \return The angle between p and n.
//------------------------------------------------------------------------------
double gmAngleBetween2DVectors(double dxp,
                               double dyp,
                               double dxn,
                               double dyn,
                               double a_magn,
                               double a_magp)
{
  double theangle, cosign;

  if (a_magn == 0.0 || a_magp == 0.0)
    return (0.0);
  cosign = (dxn * dxp + dyn * dyp) / (a_magn * a_magp);
  if (cosign > 1.0)
    cosign = 1.0;
  if (cosign < -1.0)
    cosign = -1.0;
  theangle = acos(cosign);
  if (theangle == 0.0)
  {
    if ((dxn * dxp) + (dyn * dyp) < 0.0)
      theangle = XM_PI;
  }
  else if (gmCross2D(dxp, dyp, dxn, dyn) < 0.0)
    theangle = 2 * XM_PI - theangle;
  return theangle;
} // gmAngleBetween2DVectors
//-----------------------------------------------------------------------------
/// \brief Compute the counter-clockwise angle in radians between two vectors.
/// \note Resulting angle will be in range [0, 2pi).
/// \param v1: The first vector.
/// \param v2: The second vector.
/// \return The angle between vectors.
//-----------------------------------------------------------------------------
double gmAngleBetween3DVectors(const Pt3d& v1, const Pt3d& v2)
{
  double mag1, mag2, theangle, cosign;

  mag1 = sqrt(v1.x * v1.x + v1.y * v1.y + v1.z * v1.z);
  if (mag1 < 1e-20)
    mag1 = 1e-20;
  mag2 = sqrt(v2.x * v2.x + v2.y * v2.y + v2.z * v2.z);
  if (mag2 < 1e-20)
    mag2 = 1e-20;
  cosign = (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z) / (mag1 * mag2);
  if (cosign > .99999)
    cosign = 1.0;
  if (cosign < -.99999)
    cosign = -1.0;
  theangle = acos(cosign);
  return theangle;
} // gmAngleBetween3DVectors
//------------------------------------------------------------------------------
/// \brief Compute the counter-clockwise angle, in radians, between the edges
///        defined by p1-p2 and p2-p3.
/// \note Computed angle will be in the range [0-2PI).
/// \brief Returns the ccw angle (0-2pi) between p2-p1 and p2-p3
/// \param[in] p1: Point 1.
/// \param[in] p2: Point 2.
/// \param[in] p3: Point 3.
/// \return The angle between the two segments.
//------------------------------------------------------------------------------
double gmAngleBetweenEdges(const Pt2d& p1, const Pt2d& p2, const Pt2d& p3)
{
  double dxp, dyp, dxn, dyn;
  /* compute the vectors */
  dxp = p1.x - p2.x;
  dyp = p1.y - p2.y;
  dxn = p3.x - p2.x;
  dyn = p3.y - p2.y;
  return gmAngleBetween2DVectors(dxp, dyp, dxn, dyn);
} // gmAngleBetweenEdges
//------------------------------------------------------------------------------
/// \brief Compute the counter-clockwise angle, in radians, between the edges
///        defined by p1-p2 and p2-p3.
/// \note Computed angle will be in the range [0-2PI).
/// \brief Returns the ccw angle (0-2pi) between p2-p1 and p2-p3
/// \param[in] p1: Point 1.
/// \param[in] p2: Point 2.
/// \param[in] p3: Point 3.
/// \return The angle between the two segments.
//------------------------------------------------------------------------------
double gmAngleBetweenEdges(const Pt3d& p1, const Pt3d& p2, const Pt3d& p3)
{
  double dxp, dyp, dxn, dyn;
  /* compute the vectors */
  dxp = p1.x - p2.x;
  dyp = p1.y - p2.y;
  dxn = p3.x - p2.x;
  dyn = p3.y - p2.y;
  return gmAngleBetween2DVectors(dxp, dyp, dxn, dyn);
} // gmAngleBetweenEdges
//------------------------------------------------------------------------------
/// \brief Compute the deviation in direction from one segment to next.
/// \note segment 1 is from a_p0 to a_p1, segment 2 is from a_p1 to a_p2.
/// \note A magnitude of 0 results in a deviation of Pi. This indicates that
///       there could be a discontinuity.
/// \note This is a streamlined version of gmAngleBetweenEdges. That function
///       computes a directed internal difference and requires an extra cross
///       product and several compares and multiplies. This function still uses
///       sqrt and acos, so the difference may not be significant.
/// \param[in] a_p0: 1st point on 1st segment.
/// \param[in] a_p1: 2nd point on 1st segment and 1st point on second segment.
/// \param[in] a_p2: 2nd point on 2nd segment.
/// \return A deviation between 0 and Pi.
//------------------------------------------------------------------------------
double gmComputeDeviationInDirection(const Pt3d& a_p0, const Pt3d& a_p1, const Pt3d& a_p2)
{
  double x1, y1, x2, y2, m, cosine_dev;
  x1 = a_p1.x - a_p0.x;
  y1 = a_p1.y - a_p0.y;
  x2 = a_p2.x - a_p1.x;
  y2 = a_p2.y - a_p1.y;
  m = sqrt(x1 * x1 + y1 * y1) * sqrt(x2 * x2 + y2 * y2);
  if (m > 0.0)
  {
    cosine_dev = Mmin((x1 * x2 + y1 * y2) / (m), 1.0);
    cosine_dev = Mmax(cosine_dev, -1.0);
    return acos(cosine_dev);
  }
  else
  {
    return XM_PI;
  }
} // gmComputeDeviationInDirection
//------------------------------------------------------------------------------
/// \brief Compute the counter-clockwise angle in [0, 2pi) which bisects
///        another angle defined by two connected edges.
/// \param[in] a_p1: The unshared endpoint of the first edge.
/// \param[in] a_p2: The shared endpoint.
/// \param[in] a_p3: The unshared endpoint of the second edge.
/// \return Angle that bisects the edges.
//------------------------------------------------------------------------------
double gmBisectingAngle(const Pt3d& a_p1, const Pt3d& a_p2, const Pt3d& a_p3)
{
  double dxn, dyn, dxp, dyp, magn, magp, angletoedge1, theanglebetween;
  double cosign;

  dxp = a_p1.x - a_p2.x;
  dyp = a_p1.y - a_p2.y;
  dxn = a_p3.x - a_p2.x;
  dyn = a_p3.y - a_p2.y;
  angletoedge1 = atan2(dyp, dxp);
  magn = sqrt(sqr(dxn) + sqr(dyn));
  magp = sqrt(sqr(dxp) + sqr(dyp));
  cosign = (dxn * dxp + dyn * dyp) / (magn * magp);
  if (cosign > .99999)
    cosign = 1.0;
  if (cosign < -.99999)
    cosign = -1.0;
  theanglebetween = acos(cosign);
  if (theanglebetween == 0.0)
  {
    if ((dxn * dxp) + (dyn * dyp) < 0.0)
      theanglebetween = XM_PI;
  }
  else if (gmCross2D(dxp, dyp, dxn, dyn) < 0.0)
    theanglebetween = 2 * XM_PI - theanglebetween;
  return angletoedge1 + theanglebetween / 2.0;
} // gmBisectingAngle
//------------------------------------------------------------------------------
/// \brief Compute the angle, in radians, perpendicular to an edge defined by
///        two points.
/// \param[in] a_pt1: The first point defining an edge.
/// \param[in] a_pt2: The second point defining an edge.
/// \return Angle perpendicular to the edge.
//------------------------------------------------------------------------------
double gmPerpendicularAngle(const Pt3d& a_pt1, const Pt3d& a_pt2)
{
  double hypot;
  double deltax, deltay, arad, theangle;

  deltax = a_pt1.x - a_pt2.x;
  deltay = a_pt1.y - a_pt2.y;
  hypot = sqrt(sqr(deltax) + sqr(deltay));
  arad = deltax / hypot;
  if (arad > .9999)
    arad = 1.0;
  else if (arad < -.9999)
    arad = -1.0;
  if (deltay >= 0.0)
    theangle = acos(arad);
  else
    theangle = 2 * XM_PI - acos(arad);
  return (theangle - (XM_PI / 2));
} // gmPerpendicularAngle
//------------------------------------------------------------------------------
/// \brief Find a 2d unit vector perpendicular to a 2D vector defined
///        by two points.
/// \note Ignores Z values of points when finding perpendicular vector.
/// \returns The perpendicular unit vector. Z component is 0.
//------------------------------------------------------------------------------
void gmUnitVector2DPerp(const Pt3d& p1, const Pt3d& p2, Pt3d* v)
{
  double x, y, dist;

  if (v)
  {
    /* determine 2d vector from p1 to p2 */
    x = p2.x - p1.x;
    y = p2.y - p1.y;
    /* compute vector length */
    dist = sqrt(sqr(x) + sqr(y));
    /* get unit vector values */
    x /= dist;
    y /= dist;
    /* return perpendicular vector */
    v->x = y;
    v->y = -x;
    v->z = 0.0;
  }
} // gmUnitVector2DPerp
//------------------------------------------------------------------------------
/// \brief Convert and map an angle to the range [0, 360) degrees.
/// \note Angles that are too big or small are mapped to an equivalent angle
///       in range.
/// \param[in] a_angle: The angle to convert and map.
/// \param[in] a_InDegrees: Whether the angle is in degrees (true) or radians
///                         (false).
/// \return An angle in the range [0, 360) degrees.
//------------------------------------------------------------------------------
double gmConvertAngleToBetween0And360(double a_angle, bool a_InDegrees /*= true*/)
{
  double ang = a_angle;

  if (!a_InDegrees)
  {
    ang *= (180.0 / XM_PI);
  }
#if BOOST_OS_WINDOWS
  while (LT_TOL(ang, 0.0, DBL_EPSILON) && _finite(ang))
  {
#else
  while (LT_TOL(ang, 0.0, DBL_EPSILON) && std::isfinite(ang))
  {
#endif
    ang += 360.0;
  }
#if BOOST_OS_WINDOWS
  while (GTEQ_TOL(ang, 360.0, DBL_EPSILON) && _finite(ang))
  {
#else
  while (GTEQ_TOL(ang, 360.0, DBL_EPSILON) && std::isfinite(ang))
  {
#endif
    ang -= 360.0;
  }

  return ang;
} // gmConvertAngleToBetween0And360
//------------------------------------------------------------------------------
/// \brief Convert a counterclockwise angle starting on the positive x-axis to
///        a clockwise angle starting on the positive y-axis, or vice versa.
/// \note You can pass an angle in either form to get an angle in the other form
///       back.
/// \param a_angle: The angle to convert.
/// \return The converted angle.
///
///  north_coord(-north_coord) = x_axis_coord(-x_axis_coord)
///
///                      0(0) = 90(-270)
///                           |
///                           |
/// 270(-90) = 180(180) ------*------ 90(-270) = 0(0)
///                           |
///                           |
///                  180(180) = 270(-90)
//------------------------------------------------------------------------------
void gmConvertAngleBetweenXAndNorth(double* a_angle)
{
  // put between 0 and 360
  while (*a_angle < 0.0)
    *a_angle += 360.0;
  while (*a_angle > 360.0)
    *a_angle -= 360.0;

  if (*a_angle <= 90.0)
    *a_angle = 90.0 - *a_angle;
  else
    *a_angle = 450.0 - *a_angle;
} // gmConvertAngleBetweenXAndNorth
//------------------------------------------------------------------------------
/// \brief Determine if an angle is a left turn, a right turn, colinear 180
///        degrees, or colinear 0 degrees.
/// \note This function will only classify two segments as colinear if the angle
///       between edges is less than an angle tol, or greater than 180-tol. In
///       cases where this is not true, it will classify the turn as either
///       TURN_COLINEAR_180 or TURN_COLINEAR_0.
/// \param a_v1: Unshared endpoint of first segment.
/// \param a_v2: Shared endpoint of segments.
/// \param a_v3: Unshared endpoint of second segment.
/// \param a_angtol: The sine of the minimum angle to be considered a turn at all,
///                  i.e. sine(tol) as described in the note. Defaults to 0.0017453
///                  (sine 0.1 and sine 179.9).
/// \return The type of turn defined by the angle.
//------------------------------------------------------------------------------
Turn_enum gmTurn(const Pt3d& a_v1, const Pt3d& a_v2, const Pt3d& a_v3, double a_angtol /* = 0.0017453 */)
{
  // compute sin T = (v3-v2)x(v1-v2)/(d12*d32)
  double dx32 = a_v3.x - a_v2.x;
  double dy32 = a_v3.y - a_v2.y;
  double dx12 = a_v1.x - a_v2.x;
  double dy12 = a_v1.y - a_v2.y;
  double d32 = sqrt(dx32 * dx32 + dy32 * dy32);
  double d12 = sqrt(dx12 * dx12 + dy12 * dy12);
  double mag = d12 * d32;
  double sint = (dx32 * dy12 - dx12 * dy32) / mag;

  // for 99.999 > T > 0.1 deg - sin T > 0.0017
  if (sint > a_angtol)
    return TURN_LEFT;
  else if (sint < -a_angtol)
    return TURN_RIGHT;

  // compute cos T = (v3-v2)DOT(v1-v2)/(d12*d32)
  // Near colinear case, Cosine should be near 1 or -1,
  // -1 indicates 180 deg
  double cost = (dx12 * dx32 + dy12 * dy32) / mag;
  if (cost < 0.0)
    return TURN_COLINEAR_180;
  return TURN_COLINEAR_0;
} // gmTurn
//------------------------------------------------------------------------------
/// \brief Determine if angle v1-v2-v3 is a left turn.
/// \note Collinear is counted as left if the angle is 180 degrees, but not 0.
/// \param v1: The independent endpoint of the first line segment.
/// \param v2: The shared endpoint.
/// \param v3: The independent endpoint of the second line segment.
/// \return Whether the angle is a left turn.
//------------------------------------------------------------------------------
bool gmLeftTurn(const Pt2d* v1, const Pt2d* v2, const Pt2d* v3)
{
  Pt3d p1, p2, p3;

  p1.x = v1->x;
  p1.y = v1->y;
  p1.z = 0.0;
  p2.x = v2->x;
  p2.y = v2->y;
  p2.z = 0.0;
  p3.x = v3->x;
  p3.y = v3->y;
  p3.z = 0.0;
  return gmLeftTurn(&p1, &p2, &p3);
} // gmLeftTurn
//------------------------------------------------------------------------------
/// \brief Determine if angle v1-v2-v3 is a left turn.
/// \note Collinear is counted as left if the angle is 180 degrees, but not 0.
/// \param v1: The independent endpoint of the first line segment.
/// \param v2: The shared endpoint.
/// \param v3: The independent endpoint of the second line segment.
/// \return Whether the angle is a left turn.
//------------------------------------------------------------------------------
bool gmLeftTurn(const Pt3d* v1, const Pt3d* v2, const Pt3d* v3)
{
  return (gmTurn(*v1, *v2, *v3) == TURN_LEFT || gmTurn(*v1, *v2, *v3) == TURN_COLINEAR_180);
} // gmLeftTurn
//------------------------------------------------------------------------------
/// \brief Determine if angle v1-v2-v3 is a left turn.
/// \note Collinear is not counted as a left turn.
/// \param v1: The independent endpoint of the first line segment.
/// \param v2: The shared endpoint.
/// \param v3: The independent endpoint of the second line segment.
/// \return Whether the angle is a left turn.
//------------------------------------------------------------------------------
bool gmStrictlyLeftTurn(const Pt3d* v1, const Pt3d* v2, const Pt3d* v3)
{
  return (gmTurn(*v1, *v2, *v3) == TURN_LEFT);
} // gmStrictlyLeftTurn
//------------------------------------------------------------------------------
/// \brief Compute Cartesian coords given a triangle & Barycentric coords.
/// \param p1: First vertex of the triangle.
/// \param p2: Second vertex of the triangle.
/// \param p3: Third vertex of the triangle.
/// \param bary: Barycentric coordinates.
/// \param cart: Cartesian coordinates.
/// \return XM_SUCCESS, always
//------------------------------------------------------------------------------
int gmBaryToCart(const Pt3d* p1, const Pt3d* p2, const Pt3d* p3, const Pt3d* bary, Pt3d* cart)
{
  double x, y, z;

  x = bary->x;
  y = bary->y;
  z = bary->z;

  cart->x = x * p1->x + y * p2->x + z * p3->x;
  cart->y = x * p1->y + y * p2->y + z * p3->y;
  cart->z = x * p1->z + y * p2->z + z * p3->z;
  return (XM_SUCCESS);
} // gmBaryToCart
//------------------------------------------------------------------------------
/// \brief Compute the direction and coefficients of a triangle for use with
///        gmCartToBary.
/// \param p1: 1st vertex of triangle.
/// \param p2: 2nd vertex of triangle.
/// \param p3: 3rd vertex of triangle.
/// \param norm: Triangle normal.
/// \param orig: The origin of the triangle. Either used or initialized based
///              on value of flag.
/// \param coef: Coefficients.
/// \param dir: Direction.
/// \param flag: Whether to use the given origin or initialize it.
///              If true, origin will be computed from the triangle as the
///              minimum XYZ of p1, p2, and p3 and orig will be initialized to
///              that value. If false, the given value of orig will be used as
///              the origin and orig will be unmodified.
/// \return XM_SUCCESS, always.
//------------------------------------------------------------------------------
int gmBaryPrepare(const Pt3d* p1,
                  const Pt3d* p2,
                  const Pt3d* p3,
                  const Pt3d* norm,
                  Pt3d* orig,
                  double coef[6],
                  int* dir,
                  bool flag)
{
  double x1, x2, x3, y1, y2, y3, z1, z2, z3, sizeinv;
  /* compute the direction */
  x1 = fabs(norm->x);
  y1 = fabs(norm->y);
  z1 = fabs(norm->z);
  if (x1 > y1 && x1 > z1)
    *dir = 0;
  else if (y1 > z1)
    *dir = 1;
  else
    *dir = 2;
  /* get the origin */
  if (flag)
  {
    orig->x = Mmin(p1->x, Mmin(p2->x, p3->x));
    orig->y = Mmin(p1->y, Mmin(p2->y, p3->y));
    orig->z = Mmin(p1->z, Mmin(p2->z, p3->z));
  }
  /* compute the coefficients */
  x1 = p1->x - orig->x;
  y1 = p1->y - orig->y;
  z1 = p1->z - orig->z;
  x2 = p2->x - orig->x;
  y2 = p2->y - orig->y;
  z2 = p2->z - orig->z;
  x3 = p3->x - orig->x;
  y3 = p3->y - orig->y;
  z3 = p3->z - orig->z;
  switch (*dir)
  {
  case (0):
    sizeinv = 1.0 / ((y2 - y3) * (z1 - z3) - (z2 - z3) * (y1 - y3));
    coef[0] = (z3 - z2) * sizeinv;
    coef[1] = (y2 - y3) * sizeinv;
    coef[2] = (y3 * z2 - z3 * y2) * sizeinv;
    coef[3] = (z1 - z3) * sizeinv;
    coef[4] = (y3 - y1) * sizeinv;
    coef[5] = (y1 * z3 - z1 * y3) * sizeinv;
    break;
  case (1):
    sizeinv = 1.0 / ((z2 - z3) * (x1 - x3) - (x2 - x3) * (z1 - z3));
    coef[0] = (x3 - x2) * sizeinv;
    coef[1] = (z2 - z3) * sizeinv;
    coef[2] = (z3 * x2 - x3 * z2) * sizeinv;
    coef[3] = (x1 - x3) * sizeinv;
    coef[4] = (z3 - z1) * sizeinv;
    coef[5] = (z1 * x3 - x1 * z3) * sizeinv;
    break;
  case (2):
    sizeinv = 1.0 / ((x2 - x3) * (y1 - y3) - (y2 - y3) * (x1 - x3));
    coef[0] = (y3 - y2) * sizeinv;
    coef[1] = (x2 - x3) * sizeinv;
    coef[2] = (x3 * y2 - y3 * x2) * sizeinv;
    coef[3] = (y1 - y3) * sizeinv;
    coef[4] = (x3 - x1) * sizeinv;
    coef[5] = (x1 * y3 - y1 * x3) * sizeinv;
    break;
  }
  return (XM_SUCCESS);
} // gmBaryPrepare
//------------------------------------------------------------------------------
/// \brief Compute Barycentric coords for point.
/// \note Use gmBaryPrepare to get the coefficients and direction.
/// \param[in] cart: Cartesian coordinates.
/// \param[in] orig: Origin of Cartesian coordinates.
/// \param[in] coef: Coefficients from gmBaryPrepare.
/// \param[in] dir: Direction from gmBaryPrepare.
/// \param[out] bary: Initialized to the Barycentric value.
/// \return XM_SUCCESS, always.
//------------------------------------------------------------------------------
int gmCartToBary(const Pt3d* cart, const Pt3d* orig, double coef[6], int dir, Pt3d* bary)
{
  double x, y, z;
  x = cart->x - orig->x;
  y = cart->y - orig->y;
  z = cart->z - orig->z;
  /* get magnitudes of the plane normal */
  switch (dir)
  {
  case (0):
    bary->x = coef[0] * y + coef[1] * z + coef[2];
    bary->y = coef[3] * y + coef[4] * z + coef[5];
    bary->z = 1.0 - bary->x - bary->y;
    break;
  case (1):
    bary->x = coef[0] * z + coef[1] * x + coef[2];
    bary->y = coef[3] * z + coef[4] * x + coef[5];
    bary->z = 1.0 - bary->x - bary->y;
    break;
  case (2):
    bary->x = coef[0] * x + coef[1] * y + coef[2];
    bary->y = coef[3] * x + coef[4] * y + coef[5];
    bary->z = 1.0 - bary->x - bary->y;
    break;
  }
  return (XM_SUCCESS);
} // gmCartToBary
//------------------------------------------------------------------------------
/// \brief Test if two points are equal to within gmXyTol().
/// \param x1: x coordinate of point 1.
/// \param y1: y coordinate of point 1.
/// \param x2: x coordinate of point 2.
/// \param y2: y coordinate of point 2.
/// \return Whether the points are considered equal.
//------------------------------------------------------------------------------
bool gmEqualPointsXY(double x1, double y1, double x2, double y2)
{
  return gmEqualPointsXY(x1, y1, x2, y2, gmXyTol());
} // gmEqualPointsXY
//------------------------------------------------------------------------------
/// \brief Test if two points are equal to within tolerance.
/// \param x1: x coordinate of point 1.
/// \param y1: y coordinate of point 1.
/// \param x2: x coordinate of point 2.
/// \param y2: y coordinate of point 2.
/// \param tolerance: Tolerance.
/// \return Whether the points are considered equal.
//------------------------------------------------------------------------------
bool gmEqualPointsXY(double x1, double y1, double x2, double y2, double tolerance)
{
  double dx = fabs(x1 - x2);
  double dy = fabs(y1 - y2);
  if (dx > tolerance || dy > tolerance)
    return false;
  else if (sqrt(dx * dx + dy * dy) <= tolerance)
    return true;
  else
    return false;
} // gmEqualPointsXY
//------------------------------------------------------------------------------
/// \brief Test if two points are exactly equal.
/// \param point1: Point 1.
/// \param point2: Point 2.
/// \return Whether the points are considered equal.
//------------------------------------------------------------------------------
bool gmEqualPointsXY(const Pt2i& point1, const Pt2i& point2)
{
  if (point1.x == point2.x && point1.y == point2.y)
    return true;
  return false;
} // gmEqualPointsXY
//------------------------------------------------------------------------------
/// \brief Test if two points are equal to within tolerance.
/// \param a_pt1: Point 1.
/// \param a_pt2: Point 2.
/// \param tol: Tolerance.
/// \return Whether the points are considered equal.
//------------------------------------------------------------------------------
bool gmEqualPointsXY(const Pt2d& a_pt1, const Pt2d& a_pt2, double tol)
{
  return gmEqualPointsXY(a_pt1.x, a_pt1.y, a_pt2.x, a_pt2.y, tol);
} // gmEqualPointsXY
//------------------------------------------------------------------------------
/// \brief Test if two points are equal to within tolerance.
/// \param a_pt1: Point 1.
/// \param a_pt2: Point 2.
/// \param tol: Tolerance.
/// \return Whether the points are considered equal.
//------------------------------------------------------------------------------
bool gmEqualPointsXY(const Pt3d& a_pt1, const Pt3d& a_pt2, double tol)
{
  return gmEqualPointsXY(a_pt1.x, a_pt1.y, a_pt2.x, a_pt2.y, tol);
} // gmEqualPointsXY
//------------------------------------------------------------------------------
/// \brief Test if two points are equal to within gmXyTol().
/// \param x1: x of point 1.
/// \param y1: y of point 1.
/// \param z1: z of point 1.
/// \param x2: x of point 2.
/// \param y2: y of point 2.
/// \param z2: z of point 2.
/// \return Whether the points are considered equal.
//------------------------------------------------------------------------------
bool gmEqualPointsXYZ(double x1, double y1, double z1, double x2, double y2, double z2)
{
  return gmEqualPointsXYZ(x1, y1, z1, x2, y2, z2, gmXyTol());
} // gmEqualPointsXYZ
//------------------------------------------------------------------------------
/// \brief Test if two points are equal to within tolerance.
/// \param x1: x of point 1.
/// \param y1: y of point 1.
/// \param z1: z of point 1.
/// \param x2: x of point 2.
/// \param y2: y of point 2.
/// \param z2: z of point 2.
/// \param tolerance: Tolerance.
/// \return Whether the points are considered equal.
//------------------------------------------------------------------------------
bool gmEqualPointsXYZ(double x1,
                      double y1,
                      double z1,
                      double x2,
                      double y2,
                      double z2,
                      double tolerance)
{
  if ((fabs(x1 - x2) <= tolerance) && (fabs(y1 - y2) <= tolerance) && (fabs(z1 - z2) <= tolerance))
    return true;
  return false;
} // gmEqualPointsXYZ
//------------------------------------------------------------------------------
/// \brief Test if two points are equal to within tolerance.
/// \param pt1: Point 1.
/// \param pt2: Point 2.
/// \param tol: Tolerance.
/// \return Whether the points are considered equal.
//------------------------------------------------------------------------------
bool gmEqualPointsXYZ(const Pt3d& pt1, const Pt3d& pt2, double tol)
{
  return gmEqualPointsXYZ(pt1.x, pt1.y, pt1.z, pt2.x, pt2.y, pt2.z, tol);
} // gmEqualPointsXYZ
//------------------------------------------------------------------------------
/// \brief Compute the cross product of two 2D vectors.
/// \note vector 1 = dx1i + dy1j
///       vector 2 = dx2i + dy2j
/// \param dx1: x component of vector 1.
/// \param dy1: y component of vector 1.
/// \param dx2: x component of vector 2.
/// \param dy2: y component of vector 2.
/// \return cross product of 2 vectors.
//------------------------------------------------------------------------------
double gmCross2D(const double& dx1, const double& dy1, const double& dx2, const double& dy2)
{
  return (dx1 * dy2) - (dx2 * dy1);
} // gmCross2D
//------------------------------------------------------------------------------
/// \brief Compute the cross product of two 2D points.
/// \param[in] a_origin: origin point for the "vectors"
/// \param[in] a_A: first vector
/// \param[in] a_B: second vector
/// \return the cross product
//------------------------------------------------------------------------------
double gmCross2D(const Pt3d& a_origin, const Pt3d& a_A, const Pt3d& a_B)
{
  return (a_A.x - a_origin.x) * (a_B.y - a_origin.y) - (a_A.y - a_origin.y) * (a_B.x - a_origin.x);
} // gmCross2D
//------------------------------------------------------------------------------
/// \brief Compute the cross product of two vectors.
/// \param[in] a_vec1: First vector to cross.
/// \param[in] a_vec2: Second vector to cross.
/// \param[out] a_vec3: Initialized to the cross product.
//------------------------------------------------------------------------------
void gmCross3D(const Pt3d& a_vec1, const Pt3d& a_vec2, Pt3d* a_vec3)
{
  a_vec3->x = a_vec1.y * a_vec2.z - a_vec1.z * a_vec2.y;
  a_vec3->y = a_vec1.z * a_vec2.x - a_vec1.x * a_vec2.z;
  a_vec3->z = a_vec1.x * a_vec2.y - a_vec1.y * a_vec2.x;
} // gmCross3D
//------------------------------------------------------------------------------
/// \brief Perform a dot product of two vectors.
/// \note The dot product has the geometric interpretation as the length of the
///       projection of a_vec1 onto the unit vector a_vec2 when the two vectors
///       are placed so that their tails coincide.
/// \param[in] a_vec1: First vector to dot.
/// \param[in] a_vec2: Second vector to dot.
/// \return The dot product.
//------------------------------------------------------------------------------
inline float gmDot3D(const Pt3f& vec1, const Pt3f& vec2)
{
  return (vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z);
} // gmDot3D
//------------------------------------------------------------------------------
/// \brief Compute the dot product of two vectors.
/// \note The dot product has the geometric interpretation as the length of the
///       projection of a_vec1 onto the unit vector a_vec2 when the two vectors
///       are placed so that their tails coincide.
/// \param[in] a_vec1: First vector to dot.
/// \param[in] a_vec2: Second vector to dot.
/// \return The dot product.
//------------------------------------------------------------------------------
inline double gmDot3D(const Pt3d& a_vec1, const Pt3d& a_vec2)
{
  return (a_vec1.x * a_vec2.x + a_vec1.y * a_vec2.y + a_vec1.z * a_vec2.z);
} // gmDot3D
//------------------------------------------------------------------------------
/// \brief Perform the operation sum = vec1 + scale * vec2
/// \param scale: Scale value for vec2.
/// \param vec1: Unscaled vector to add.
/// \param vec2: Vector to scale and add.
/// \param sum: Initialized to the result of the operation.
/// \return XM_SUCCESS, always.
//------------------------------------------------------------------------------
int gmVectorAdd(double scale, const Pt3d& vec1, const Pt3d& vec2, Pt3d* sum)
{
  sum->x = vec1.x + scale * vec2.x;
  sum->y = vec1.y + scale * vec2.y;
  sum->z = vec1.z + scale * vec2.z;
  return (XM_SUCCESS);
}
//------------------------------------------------------------------------------
/// \brief Average two 3D points.
/// \param a: The first point.
/// \param b: The second point.
/// \param result: Initialized to the average of a and b.
/// \author   MJK
//------------------------------------------------------------------------------
void gmVectorAverage(const Pt3d& a, const Pt3d& b, Pt3d* result)
{
  result->x = (a.x + b.x) * 0.5;
  result->y = (a.y + b.y) * 0.5;
  result->z = (a.z + b.z) * 0.5;
} // gmVectorAverage
//------------------------------------------------------------------------------
/// \brief Average two 4D points as if they were 3D points.
/// \note: This only averages the location not the scalar value
/// \param a: The first point.
/// \param b: The second point.
/// \param result: Initialized to the average of a and b.
//------------------------------------------------------------------------------
void gmVectorAverage(const Pt4d& a, const Pt4d& b, Pt4d* result)
{
  result->x = (a.x + b.x) * 0.5;
  result->y = (a.y + b.y) * 0.5;
  result->z = (a.z + b.z) * 0.5;
} // gmVectorAverage
//------------------------------------------------------------------------------
/// \brief Rotate a 2D vector by an angle in degrees.
/// \param in: The vector to rotate.
/// \param a_angle: The angle to rotate the vector by.
/// \param out: Initialized to the rotated vector.
//------------------------------------------------------------------------------
void gmVectorRotate2D(const Pt3d& in, double a_angle, Pt3d& out)
{
  double rad(a_angle * DEGREES_TO_RADIANS);
  double cosangle(cos(rad));
  double sinangle(sin(rad));
  out.x = cosangle * in.x - sinangle * in.y;
  out.y = sinangle * in.x + cosangle * in.y;
} // gmVectorRotate2D
//------------------------------------------------------------------------------
/// \brief Perform the operation dif = vec1 - vec2
/// \param vec1: Left hand side vector to subtract.
/// \param vec2: Vector to subtract.
/// \param dif: Initialized to the result of the operation.
//------------------------------------------------------------------------------
void gmVectorSubtract(const Pt3d* vec1, const Pt3d* vec2, Pt3d* dif)
{
  dif->x = vec1->x - vec2->x;
  dif->y = vec1->y - vec2->y;
  dif->z = vec1->z - vec2->z;
} // gmVectorSubtract
//------------------------------------------------------------------------------
/// \brief Create a unit vector representing the direction from one
///        point to another.
/// \param p1: The point to point from.
/// \param p2: The point to point to.
/// \return A unit vector with x,y,z components representing the direction.
//------------------------------------------------------------------------------
Pt3d gmUnitVector(const Pt3d& p1, const Pt3d& p2)
{
  double d;
  Pt3d vector;

  vector = gmCreateVector(p1, p2);
  d = sqrt(sqr(vector.x) + sqr(vector.y) + sqr(vector.z));
  if (d < 1e-20)
    d = 1e-20;
  vector.x = vector.x / d;
  vector.y = vector.y / d;
  vector.z = vector.z / d;
  return vector;
} // gmUnitVector
//------------------------------------------------------------------------------
/// \brief Convert a magnitude and angle to xy components or vice versa.
/// \param[in,out] a_x: Vector x component, either specified or calculated from
///                     a_mag, a_dir.
/// \param[in,out] a_y: Vector y component, either specified or calculated from
///                     a_mag, a_dir.
/// \param[in,out] a_mag: Vector magnitude, either specified or calculated from
///                       a_x, a_y.
/// \param[in,out] a_dir: Vector direction, in degrees, either specified or
///                       calculated from a_x, a_y.
/// \param[in] a_tomagdir: True to calculate a_mag and a_dir from a_x and a_y;
///                        False to calculate a_x and a_y from a_mag and a_dir.
//------------------------------------------------------------------------------
void gmComponentMagnitudes(double* a_x, double* a_y, double* a_mag, double* a_dir, bool a_tomagdir)
{
  double rads;

  if (a_tomagdir)
  { // convert (x,y) to (mag,dir)
    if (fabs(*a_x) < XM_ZERO_TOL && fabs(*a_y) < XM_ZERO_TOL)
    {
      *a_mag = 0.0;
      *a_dir = 0.0;
    }
    else
    {
      if (*a_x == 0)
        *a_x = XM_ZERO_TOL;
      *a_mag = sqrt(sqr(*a_x) + sqr(*a_y));
      *a_dir = (atan(*a_y / *a_x)) * (180 / XM_PI);
      if (*a_x < 0)
        (*a_dir) += 180;
      if (*a_dir < 0)
        (*a_dir) += 360;
    }
  }
  else
  { // convert (mag,dir) to (x,y)
    rads = *a_dir * (XM_PI / 180);
    *a_x = cos(rads) * *a_mag;
    *a_y = sin(rads) * *a_mag;
    if (fabs(*a_x) < XM_ZERO_TOL)
      *a_x = 0;
    if (fabs(*a_y) < XM_ZERO_TOL)
      *a_y = 0;
  }
} // gmComponentMagnitudes
//------------------------------------------------------------------------------
/// \brief Create a vector representing the direction from one point to another.
/// \param[in] a_p1: The point being pointed from.
/// \param[in] a_p2: The point being pointed to.
/// \return A vector with x,y,z components representing the direction.
//------------------------------------------------------------------------------
Pt3d gmCreateVector(const Pt3d& a_p1, const Pt3d& a_p2)
{
  Pt3d vector;
  vector.x = a_p2.x - a_p1.x;
  vector.y = a_p2.y - a_p1.y;
  vector.z = a_p2.z - a_p1.z;
  return vector;
} // gmCreateVector
//------------------------------------------------------------------------------
/// \brief Determine whether a point is inside, on, or outside a polygon.
/// \note DON'T repeat the first point at the end of the polygon array
/// \see EFastPointInPoly, gmPolygon
/// \param[in] a_verts: The polygon in CW or CCW order (doesn't matter which).
/// \param[in] a_num: Number of vertices in a_verts.
/// \param[in] a_x: x coordinate of point to test.
/// \param[in] a_y: y coordinate of point to test.
/// \param[in] a_tol: Tolerance for geometric comparison.
/// \return 1 if the point is inside the polygon, 0 if on, or -1 if outside.
//------------------------------------------------------------------------------
template <typename T>
int gmPointInPolygon2D(const T* a_verts,
                       const size_t a_num,
                       const double a_x,
                       const double a_y,
                       const double a_tol)
{
  if (a_verts && a_num)
  {
    int nmleft = 0, nmrght = 0;
    double dy2 = fabs(a_verts[0].y - a_y);
    double diff;
    for (size_t i = 0; i < a_num; i++)
    {
      size_t i2 = 0;
      if (i != a_num - 1)
        i2 = i + 1;
      double dy1 = dy2;
      dy2 = fabs(a_verts[i2].y - a_y);
      if (dy1 <= a_tol)
      {
        if (dy2 <= a_tol)
        {
          // Case #1 - edge is on the same y value as the point
          //         - see if the point is on the edge
          if (((a_verts[i].x >= a_x) && (a_verts[i2].x <= a_x)) ||
              ((a_verts[i].x <= a_x) && (a_verts[i2].x >= a_x)))
            return (0);
        }
        else
        {
          // Case #2 - first vertex has same y value as point
          //         - see if the point actually coincides with
          //           the ith vertex
          diff = a_verts[i].x - a_x;
          if (fabs(diff) <= a_tol)
            return (0);
          else if (a_verts[i].y < a_verts[i2].y)
          {
            // edge ascends, classify as right or left
            if (diff > 0)
              ++nmrght;
            else
              ++nmleft;
          }
        }
      }
      else if (dy2 <= a_tol)
      {
        // Case #3 - 2nd vertex of edge lies on dividing plane
        //         - see if the point actually coincides with
        //           the i2-th vertex
        diff = a_verts[i2].x - a_x;
        if (fabs(diff) <= a_tol)
          return (0);
        else if (a_verts[i2].y < a_verts[i].y)
        {
          // if edge descends classify as right or left
          if (diff > 0)
            ++nmrght;
          else
            ++nmleft;
        }
      }
      else if (((a_verts[i].y < a_y) && (a_verts[i2].y > a_y)) ||
               ((a_verts[i].y > a_y) && (a_verts[i2].y < a_y)))
      {
        // Case #4 - edge cleanly intersects dividing plane
        //         - flag edge as left, right or on edge
        double val = a_verts[i].x + (a_verts[i2].x - a_verts[i].x) * (a_y - a_verts[i].y) /
                                      (a_verts[i2].y - a_verts[i].y);
        diff = val - a_x;
        if (fabs(diff) <= a_tol)
          return (0);
        else if (diff > 0)
          ++nmrght;
        else
          ++nmleft;
      }
    }
    nmleft = nmleft % 2;
    nmrght = nmrght % 2;
    if (nmleft != nmrght)
      return (-1); // this should never happen actually
    else if (nmleft == 1)
      return (1);
    else
      return (-1);
  }
  return (-1);
} // gmPointInPolygon2D
//------------------------------------------------------------------------------
/// \brief Determine whether a point is inside, on, or outside a polygon.
/// \note DON'T repeat the first point at the end of the polygon array
/// \see EFastPointInPoly, gmPolygon
/// \param[in] a_verts: The polygon in CW or CCW order (doesn't matter which).
/// \param[in] a_num: Number of vertices in a_verts.
/// \param[in] a_x: x coordinate of point to test.
/// \param[in] a_y: y coordinate of point to test.
/// \param[in] a_tol: Tolerance for geometric comparison.
/// \return 1 if the point is inside the polygon, 0 if on, or -1 if outside.
//------------------------------------------------------------------------------
int gmPointInPolygon2D(const Pt2i* a_verts, size_t a_num, Pt2i a_pt)
{
  return gmPointInPolygon2D(a_verts, a_num, a_pt.x, a_pt.y, gmXyTol());
} // gmPointInPolygon2D
//------------------------------------------------------------------------------
/// \brief Determine whether a point is inside, on, or outside a polygon.
/// \note DON'T repeat the first point at the end of the polygon array
/// \see EFastPointInPoly, gmPolygon
/// \param[in] a_verts: The polygon in CW or CCW order (doesn't matter which).
/// \param[in] a_num: Number of vertices in a_verts.
/// \param[in] a_x: x coordinate of point to test.
/// \param[in] a_y: y coordinate of point to test.
/// \param[in] a_tol: Tolerance for geometric comparison.
/// \return 1 if the point is inside the polygon, 0 if on, or -1 if outside.
//------------------------------------------------------------------------------
int gmPointInPolygon2D(const Pt2i* a_verts, size_t a_num, Pt2d a_pt)
{
  return gmPointInPolygon2D(a_verts, a_num, a_pt.x, a_pt.y, gmXyTol());
} // gmPointInPolygon2D
//------------------------------------------------------------------------------
/// \brief Determine whether a point is inside, on, or outside a polygon.
/// \note DON'T repeat the first point at the end of the polygon array
/// \see EFastPointInPoly, gmPolygon
/// \param[in] a_verts: The polygon in CW or CCW order (doesn't matter which).
/// \param[in] a_num: Number of vertices in a_verts.
/// \param[in] a_x: x coordinate of point to test.
/// \param[in] a_y: y coordinate of point to test.
/// \param[in] a_tol: Tolerance for geometric comparison.
/// \return 1 if the point is inside the polygon, 0 if on, or -1 if outside.
//------------------------------------------------------------------------------
int gmPointInPolygon2D(const Pt2i* a_verts, size_t a_num, Pt3d a_pt)
{
  return gmPointInPolygon2D(a_verts, a_num, a_pt.x, a_pt.y, gmXyTol());
} // gmPointInPolygon2D
//------------------------------------------------------------------------------
/// \brief Determine whether a point is inside, on, or outside a polygon.
/// \note DON'T repeat the first point at the end of the polygon array
/// \see EFastPointInPoly, gmPolygon
/// \param[in] a_verts: The polygon in CW or CCW order (doesn't matter which).
/// \param[in] a_num: Number of vertices in a_verts.
/// \param[in] a_x: x coordinate of point to test.
/// \param[in] a_y: y coordinate of point to test.
/// \param[in] a_tol: Tolerance for geometric comparison.
/// \return 1 if the point is inside the polygon, 0 if on, or -1 if outside.
//------------------------------------------------------------------------------
int gmPointInPolygon2D(const Pt3d* a_verts, size_t a_num, double a_x, double a_y)
{
  return gmPointInPolygon2D(a_verts, a_num, a_x, a_y, gmXyTol());
} // gmPointInPolygon2D
//------------------------------------------------------------------------------
/// \brief Determine whether a point is inside, on, or outside a polygon.
/// \note DON'T repeat the first point at the end of the polygon array
/// \see EFastPointInPoly, gmPolygon
/// \param[in] a_verts: The polygon in CW or CCW order (doesn't matter which).
/// \param[in] a_num: Number of vertices in a_verts.
/// \param[in] a_x: x coordinate of point to test.
/// \param[in] a_y: y coordinate of point to test.
/// \param[in] a_tol: Tolerance for geometric comparison.
/// \return 1 if the point is inside the polygon, 0 if on, or -1 if outside.
//------------------------------------------------------------------------------
int gmPointInPolygon2D(const Pt3d* a_verts, size_t a_num, Pt3d a_pt)
{
  return gmPointInPolygon2D(a_verts, a_num, a_pt.x, a_pt.y, gmXyTol());
} // gmPointInPolygon2D
//------------------------------------------------------------------------------
/// \brief Determine whether a point is inside, on, or outside a polygon.
/// \note DON'T repeat the first point at the end of the polygon array
/// \see EFastPointInPoly, gmPolygon
/// \param[in] a_verts: The polygon in CW or CCW order (doesn't matter which).
/// \param[in] a_num: Number of vertices in a_verts.
/// \param[in] a_x: x coordinate of point to test.
/// \param[in] a_y: y coordinate of point to test.
/// \param[in] a_tol: Tolerance for geometric comparison.
/// \return 1 if the point is inside the polygon, 0 if on, or -1 if outside.
//------------------------------------------------------------------------------
int gmPointInPolygon2D(const VecPt3d& a_verts, const Pt3d& a_pt)
{
  return gmPointInPolygon2D(&a_verts[0], a_verts.size(), a_pt.x, a_pt.y, gmXyTol());
} // gmPointInPolygon2D
//------------------------------------------------------------------------------
/// \brief Determine whether a point is inside, on, or outside a polygon.
/// \note DON'T repeat the first point at the end of the polygon array
/// \see EFastPointInPoly, gmPolygon
/// \param[in] a_verts: The polygon in CW or CCW order (doesn't matter which).
/// \param[in] a_num: Number of vertices in a_verts.
/// \param[in] a_x: x coordinate of point to test.
/// \param[in] a_y: y coordinate of point to test.
/// \param[in] a_tol: Tolerance for geometric comparison.
/// \return 1 if the point is inside the polygon, 0 if on, or -1 if outside.
//------------------------------------------------------------------------------
template int gmPointInPolygon2D<Pt2i>(const Pt2i* a_verts,
                                      const size_t a_num,
                                      const double a_x,
                                      const double a_y,
                                      const double a_tol);
//------------------------------------------------------------------------------
/// \brief Determine whether a point is inside, on, or outside a polygon.
/// \note DON'T repeat the first point at the end of the polygon array
/// \see EFastPointInPoly, gmPolygon
/// \param[in] a_verts: The polygon in CW or CCW order (doesn't matter which).
/// \param[in] a_num: Number of vertices in a_verts.
/// \param[in] a_x: x coordinate of point to test.
/// \param[in] a_y: y coordinate of point to test.
/// \param[in] a_tol: Tolerance for geometric comparison.
/// \return 1 if the point is inside the polygon, 0 if on, or -1 if outside.
//------------------------------------------------------------------------------
template int gmPointInPolygon2D<Pt2d>(const Pt2d* a_verts,
                                      const size_t a_num,
                                      const double a_x,
                                      const double a_y,
                                      const double a_tol);
//------------------------------------------------------------------------------
/// \brief Determine whether a point is inside, on, or outside a polygon.
/// \note DON'T repeat the first point at the end of the polygon array
/// \see EFastPointInPoly, gmPolygon
/// \param[in] a_verts: The polygon in CW or CCW order (doesn't matter which).
/// \param[in] a_num: Number of vertices in a_verts.
/// \param[in] a_x: x coordinate of point to test.
/// \param[in] a_y: y coordinate of point to test.
/// \param[in] a_tol: Tolerance for geometric comparison.
/// \return 1 if the point is inside the polygon, 0 if on, or -1 if outside.
//------------------------------------------------------------------------------
template int gmPointInPolygon2D<Pt3d>(const Pt3d* a_verts,
                                      const size_t a_num,
                                      const double a_x,
                                      const double a_y,
                                      const double a_tol);
//------------------------------------------------------------------------------
/// \brief Determine whether a point is inside, on, or outside a polygon.
/// \note See unit tests. Doesn't check if point is actually in the plane of
///       the polygon. You'd need gmDistanceFromPointToPlane for that.
/// \param[in] a_verts: The polygon in CW or CCW order (doesn't matter which).
/// \param[in] a_num:   Number of verts in a_verts.
/// \param[in] a_x:     X coordinate of point to test.
/// \param[in] a_y:     Y coordinate of point to test.
/// \param[in] a_tol:   Tolerance.
/// \return 1 if the point is inside the polygon, 0 if on, -1 if outside, -999
///         on error.
//------------------------------------------------------------------------------
int gmPointInPolygon3DWithTol(const Pt3d& pt,
  int nvtx,
  const Pt3d* vertex,
  const int* poly,
  const Pt3d& nrm,
  double tol)
{
  register int i, id0, id1;
  register double diff, val;
  int plndir, divdir, nmcrs1, nmcrs2;
  double p0, p1, p2;
  p0 = fabs(nrm.x);
  p1 = fabs(nrm.y);
  p2 = fabs(nrm.z);
  if ((p0 <= p1) && (p0 <= p2))
  {
    plndir = 0;
    if (p1 <= p2)
      divdir = 1;
    else
      divdir = 2;
  }
  else if ((p1 <= p0) && (p1 <= p2))
  {
    plndir = 1;
    if (p0 <= p2)
      divdir = 0;
    else
      divdir = 2;
  }
  else
  {
    plndir = 2;
    if (p0 <= p1)
      divdir = 0;
    else
      divdir = 1;
  }
  /* init counters for edges above & below */
  nmcrs1 = 0;
  nmcrs2 = 0;
  /* process each edge                        */
  for (i = 0; i < nvtx; ++i)
  {
    id0 = poly[i];
    if (i == nvtx - 1)
      id1 = poly[0];
    else
      id1 = poly[i + 1];
    if (plndir == 0)
    {
      /* case #1 and #2 - first vertex lies on
      dividing plane                           */
      if (fabs(vertex[id0].x - pt.x) <= tol)
      {
        if (fabs(vertex[id1].x - pt.x) <= tol)
        {
          if (divdir == 1)
          {
            if ((vertex[id0].y >= pt.y && vertex[id1].y <= pt.y) ||
              (vertex[id0].y <= pt.y && vertex[id1].y >= pt.y))
              return (0);
          }
          else
          {
            if ((vertex[id0].z >= pt.z && vertex[id1].z <= pt.z) ||
              (vertex[id0].z <= pt.z && vertex[id1].z >= pt.z))
              return (0);
          }
        }
        else
        {
          if (divdir == 1)
            diff = vertex[id0].y - pt.y;
          else
            diff = vertex[id0].z - pt.z;
          if (fabs(diff) <= tol)
            return (0);
          else if (vertex[id0].x < vertex[id1].x)
          {
            if (diff > tol)
              ++nmcrs1;
            else
              ++nmcrs2;
          }
        }
      }
      /* case #3 - second vertex of edge lies
      on dividing plane                      */
      else if (fabs(vertex[id1].x - pt.x) <= tol)
      {
        if (divdir == 1)
          diff = vertex[id1].y - pt.y;
        else
          diff = vertex[id1].z - pt.z;
        if (fabs(diff) <= tol)
          return (0);
        else if (vertex[id1].x < vertex[id0].x)
        {
          if (diff > tol)
            ++nmcrs1;
          else
            ++nmcrs2;
        }
      }
      /* case #4 - edge cleanly intersects
      dividing plane                          */
      else if ((vertex[id0].x < pt.x && vertex[id1].x > pt.x) ||
        (vertex[id0].x > pt.x && vertex[id1].x < pt.x))
      {
        if (divdir == 1)
        {
          val = vertex[id0].y + (vertex[id1].y - vertex[id0].y) * (pt.x - vertex[id0].x) /
            (vertex[id1].x - vertex[id0].x);
          diff = val - pt.y;
        }
        else
        {
          val = vertex[id0].z + (vertex[id1].z - vertex[id0].z) * (pt.x - vertex[id0].x) /
            (vertex[id1].x - vertex[id0].x);
          diff = val - pt.z;
        }
        if (fabs(diff) <= tol)
          return (0);
        else if (diff > tol)
          ++nmcrs1;
        else
          ++nmcrs2;
      }
    }
    else if (plndir == 1)
    {
      /* case #1 and #2 - first vertex lies on
      dividing plane                           */
      if (fabs(vertex[id0].y - pt.y) <= tol)
      {
        if (fabs(vertex[id1].y - pt.y) <= tol)
        {
          if (divdir == 0)
          {
            if ((vertex[id0].x >= pt.x && vertex[id1].x <= pt.x) ||
              (vertex[id0].x <= pt.x && vertex[id1].x >= pt.x))
              return (0);
          }
          else
          {
            if ((vertex[id0].z >= pt.z && vertex[id1].z <= pt.z) ||
              (vertex[id0].z <= pt.z && vertex[id1].z >= pt.z))
              return (0);
          }
        }
        else
        {
          if (divdir == 0)
            diff = vertex[id0].x - pt.x;
          else
            diff = vertex[id0].z - pt.z;
          if (fabs(diff) <= tol)
            return (0);
          else if (vertex[id0].y < vertex[id1].y)
          {
            if (diff > tol)
              ++nmcrs1;
            else
              ++nmcrs2;
          }
        }
      }
      /* case #3 - second vertex of edge lies
      on dividing plane                      */
      else if (fabs(vertex[id1].y - pt.y) <= tol)
      {
        if (divdir == 0)
          diff = vertex[id1].x - pt.x;
        else
          diff = vertex[id1].z - pt.z;
        if (fabs(diff) <= tol)
          return (0);
        else if (vertex[id1].y < vertex[id0].y)
        {
          if (diff > tol)
            ++nmcrs1;
          else
            ++nmcrs2;
        }
      }
      /* case #4 - edge cleanly intersects
      dividing plane                          */
      else if ((vertex[id0].y < pt.y && vertex[id1].y > pt.y) ||
        (vertex[id0].y > pt.y && vertex[id1].y < pt.y))
      {
        if (divdir == 0)
        {
          val = vertex[id0].x + (vertex[id1].x - vertex[id0].x) * (pt.y - vertex[id0].y) /
            (vertex[id1].y - vertex[id0].y);
          diff = val - pt.x;
        }
        else
        {
          val = vertex[id0].z + (vertex[id1].z - vertex[id0].z) * (pt.y - vertex[id0].y) /
            (vertex[id1].y - vertex[id0].y);
          diff = val - pt.z;
        }
        if (fabs(diff) <= tol)
          return (0);
        else if (diff > tol)
          ++nmcrs1;
        else
          ++nmcrs2;
      }
    }
    else
    {
      /* case #1 and #2 - first vertex lies on
      dividing plane                           */
      if (fabs(vertex[id0].z - pt.z) <= tol)
      {
        if (fabs(vertex[id1].z - pt.z) <= tol)
        {
          if (divdir == 1)
          {
            if ((vertex[id0].y >= pt.y && vertex[id1].y <= pt.y) ||
              (vertex[id0].y <= pt.y && vertex[id1].y >= pt.y))
              return (0);
          }
          else
          {
            if ((vertex[id0].x >= pt.x && vertex[id1].x <= pt.x) ||
              (vertex[id0].x <= pt.x && vertex[id1].x >= pt.x))
              return (0);
          }
        }
        else
        {
          if (divdir == 1)
            diff = vertex[id0].y - pt.y;
          else
            diff = vertex[id0].x - pt.x;
          if (fabs(diff) <= tol)
            return (0);
          else if (vertex[id0].z < vertex[id1].z)
          {
            if (diff > tol)
              ++nmcrs1;
            else
              ++nmcrs2;
          }
        }
      }
      /* case #3 - second vertex of edge lies
      on dividing plane                      */
      else if (fabs(vertex[id1].z - pt.z) <= tol)
      {
        if (divdir == 1)
          diff = vertex[id1].y - pt.y;
        else
          diff = vertex[id1].x - pt.x;
        if (fabs(diff) <= tol)
          return (0);
        else if (vertex[id1].z < vertex[id0].z)
        {
          if (diff > tol)
            ++nmcrs1;
          else
            ++nmcrs2;
        }
      }
      /* case #4 - edge cleanly intersects
      dividing plane                          */
      else if ((vertex[id0].z < pt.z && vertex[id1].z > pt.z) ||
        (vertex[id0].z > pt.z && vertex[id1].z < pt.z))
      {
        if (divdir == 1)
        {
          val = vertex[id0].y + (vertex[id1].y - vertex[id0].y) * (pt.z - vertex[id0].z) /
            (vertex[id1].z - vertex[id0].z);
          diff = val - pt.y;
        }
        else
        {
          val = vertex[id0].x + (vertex[id1].x - vertex[id0].x) * (pt.z - vertex[id0].z) /
            (vertex[id1].z - vertex[id0].z);
          diff = val - pt.x;
        }
        if (fabs(diff) <= tol)
          return (0);
        else if (diff > tol)
          ++nmcrs1;
        else
          ++nmcrs2;
      }
    }
  }
  nmcrs1 = nmcrs1 % 2;
  nmcrs2 = nmcrs2 % 2;
  if (nmcrs1 != nmcrs2)
  {
    printf("error here in CLPT");
    return -999;
  }
  else if (nmcrs1 == 1)
    return (1); /* return point in */
  else
    return (-1); /* return point out */
} //  gmPointInPolygon3DWithTol
//------------------------------------------------------------------------------
/// \brief Check if two points are separated by a distance of at most radius.
/// \param pt1: First point.
/// \param pt2: Second point.
/// \param radius: The maximum distance between the two points.
/// \return Whether the two points are within the radius of each other.
//------------------------------------------------------------------------------
bool gmPointsInRadiusXY(const Pt3d& pt1, const Pt3d& pt2, double radius)

{
  return gmPointsInRadiusXY(pt1.x, pt1.y, pt2.x, pt2.y, radius);
} // gmPointsInRadiusXY
//------------------------------------------------------------------------------
/// \brief Check if two points are separated by a distance of at most radius.
/// \param x1: x coordinate of the first point.
/// \param y1: y coordinate of the first point.
/// \param x2: x coordinate of the second point.
/// \param y2: y coordinate of the second point.
/// \param radius: The maximum distance between the two points.
/// \return Whether the two points are within radius of each other.
//------------------------------------------------------------------------------
bool gmPointsInRadiusXY(double x1, double y1, double x2, double y2, double radius)
{
  if ((fabs(x2 - x1) < radius) && (fabs(y2 - y1) < radius) && (Mdist(x2, y2, x1, y1) < radius))
  {
    return true;
  }
  return false;
} // gmPointsInRadiusXY
//------------------------------------------------------------------------------
/// \brief Check whether a point is in a circumcircle defined by three other
///        points.
/// \param pt: The point to check.
/// \param circumcirclePts: 3 points on the circumcircle.
/// \return Whether the point is in, out of, or on the circle.
//------------------------------------------------------------------------------
PtInOutOrOn_enum gmPtInCircumcircle(const Pt3d& pt, Pt3d circumcirclePts[3])
{
  double xc, yc, r2;

  if (!gmCircumcircleWithTol(&circumcirclePts[0], &circumcirclePts[1], &circumcirclePts[2], &xc,
    &yc, &r2, gmXyTol()))
  {
    return PT_ERROR;
  }
  /* compute distance from (xc,yc) to pt squared */
  double delta = sqrt(r2) - sqrt(sqr(pt.x - xc) + sqr(pt.y - yc));
  if (fabs(delta) > gmXyTol())
  {
    if (delta > gmXyTol())
    {
      return PT_IN;
    }
    else
    {
      return PT_OUT;
    }
  }
  return PT_ON;
} // gmPtInCircumcircle
//------------------------------------------------------------------------------
/// \brief Check whether a point is in or on a box in 2D.
/// \param[in] a_bMin Min x,y of box.
/// \param[in] a_bMax Max x,y of box.
/// \param[in] a_pt point being tested.
/// \return Whether the point is on or on the box.
//------------------------------------------------------------------------------
bool gmPointInOrOnBox2d(const Pt3d& a_bMin, const Pt3d& a_bMax, const Pt3d& a_pt)
{
  if (a_pt.x < a_bMin.x || a_pt.y < a_bMin.y || a_pt.x > a_bMax.x || a_pt.y > a_bMax.y)
    return false;
  return true;
} // gmPointInOrOnBox2d
//------------------------------------------------------------------------------
/// \brief Test whether a point is in a rectangle.
/// \param thepoint: The point to test.
/// \param tl: The top left corner of the rectangle.
/// \param br: The bottom right corner of the rectangle.
/// \return Whether the point is inside the rectangle.
//------------------------------------------------------------------------------
bool gmPointInRect(const Pt2i& thepoint, const Pt2i& tl, const Pt2i& br)
{
  if ((thepoint.x >= tl.x) && (thepoint.x <= br.x))
  {
    if ((thepoint.y >= tl.y) && (thepoint.y <= br.y))
    {
      return true;
    }
  }

  return false;
} // gmPointInRect
//------------------------------------------------------------------------------
/// \brief Test whether a point is in a rectangle.
/// \param thepoint: The point to test.
/// \param tl: The top left corner of the rectangle.
/// \param br: The bottom right corner of the rectangle.
/// \return Whether the point is inside the rectangle.
//------------------------------------------------------------------------------
bool gmPointInRect(const Pt3d& a_pt, const Pt3d& a_tl, const Pt3d& a_br)
{
  return (gmPointInRect2(a_pt, a_tl.y, a_br.y, a_tl.x, a_br.x) == true);
} // gmPointInRect
//------------------------------------------------------------------------------
/// \brief Test whether a point is in a rectangle.
/// \param thepoint: The point to test.
/// \param etop: The top edge of the rectangle.
/// \param ebottom: The bottom edge of the rectangle.
/// \param eleft: The left edge of the rectangle.
/// \param eright: The right edge of the rectangle.
/// \return Whether the point is inside the rectangle.
//------------------------------------------------------------------------------
bool gmPointInRect2(const Pt3d& thepoint, double etop, double ebottom, double eleft, double eright)
{
  double swap;
  if (etop < ebottom)
  {
    swap = etop;
    etop = ebottom;
    ebottom = swap;
  }
  if (eleft > eright)
  {
    swap = eleft;
    eleft = eright;
    eright = swap;
  }

  if ((thepoint.x <= eright) && (thepoint.x >= eleft))
    if ((thepoint.y <= etop) && (thepoint.y >= ebottom))
      return true;
  return false;
} // gmPointInRect2
//------------------------------------------------------------------------------
/// \brief Test whether a point is bounded by a triangle.
/// \param[in] p1: First vertex of triangle.
/// \param[in] p2: Second vertex of triangle.
/// \param[in] p3: Third vertex of triangle.
/// \param[in] x: x coordinate of point.
/// \param[in] y: y coordinate of point.
/// \return Whether the point is inside the triangle.
//------------------------------------------------------------------------------
bool gmPointInTriangle(const Pt3d* p1, const Pt3d* p2, const Pt3d* p3, double x, double y)
{
  return gmPointInTriangleWithTol(p1, p2, p3, x, y, gmXyTol());
} // gmPointInTriangle
//------------------------------------------------------------------------------
/// \brief Test whether a point is bounded by a triangle.
/// \param[in] p1: First vertex of triangle.
/// \param[in] p2: Second vertex of triangle.
/// \param[in] p3: Third vertex of triangle.
/// \param[in] x: x coordinate of point.
/// \param[in] y: y coordinate of point.
/// \param[in] tol: Tolerance.
/// \return Whether the point is inside the triangle.
//------------------------------------------------------------------------------
bool gmPointInTriangleWithTol(const Pt3d* p1,
  const Pt3d* p2,
  const Pt3d* p3,
  double x,
  double y,
  double tol)
{
  if (gmInsideOrOnLineWithTol(p1, p2, p3, x, y, tol))
    if (gmInsideOrOnLineWithTol(p2, p3, p1, x, y, tol))
      if (gmInsideOrOnLineWithTol(p3, p1, p2, x, y, tol))
        return true;
  return false;
} // gmPointInTriangleWithTol
//------------------------------------------------------------------------------
/// \brief Compute the minimum 2D distance from a point to a line segment.
/// \note The closest point may be one of the endpoints of the segment.
/// \param pt1: First point defining the line segment.
/// \param pt2: Second point defining the line segment.
/// \param pt3: The point to find the distance to.
/// \return Minimum distance from the point to the line segment.
//------------------------------------------------------------------------------
double gm2DDistanceToLineSegment(const Pt3d& pt1, const Pt3d& pt2, const Pt3d& pt3)
{
  return gm2DDistanceToLineSegmentWithTol(&pt1, &pt2, pt3.x, pt3.y, gmXyTol());
} // gm2DDistanceToLineSegment
//------------------------------------------------------------------------------
/// \brief Compute the minimum 2D distance from a point to a line segment.
/// \note The closest point may be one of the endpoints of the segment.
/// \param pt1: First point defining the line segment.
/// \param pt2: Second point defining the line segment.
/// \param x: x coordinate of the point.
/// \param y: y coordinate of the point.
/// \param tol: Tolerance for geometric comparisons.
/// \return Minimum distance from the point to the line segment.
//------------------------------------------------------------------------------
double gm2DDistanceToLineSegmentWithTol(const Pt3d* pt1,
                                        const Pt3d* pt2,
                                        double x,
                                        double y,
                                        double tol)
{
  Pt3d pt(x, y, 0.0);
  Pt3d newpt;

  if (gmFindClosestPtOnSegment(*pt1, *pt2, pt, newpt, &tol) == 0.0)
    return sqrt(sqr(pt1->x - x) + sqr(pt1->y - y));
  else
    return sqrt(sqr(pt.x - newpt.x) + sqr(pt.y - newpt.y));
} // gm2DDistanceToLineSegmentWithTol
//------------------------------------------------------------------------------
/// \brief Compute the xy distance from a point to a line.
/// \note Resulting distance will have correct magnitude, but sign may be wrong.
/// \note Unlike gm2DDistanceToLineSegmentWithTol, the resulting distance may
///       be closest to a point outside the segment defined by a_pt1 and a_pt2.
/// \param[in] a_pt1: First point defining a line.
/// \param[in] a_pt2: Second point defining a line.
/// \param[in] a_x: x location of test point.
/// \param[in] a_y: y location of test point.
/// \param[in] a_tol: Tolerance used in geometric computations.
/// \return Distance from the line to the test point.
//------------------------------------------------------------------------------
double gm2DDistanceToLineWithTol(const Pt3d* a_pt1,
                                 const Pt3d* a_pt2,
                                 double a_x,
                                 double a_y,
                                 double a_tol)
{
  double a1, b1, c, mag;
  double dist;
  // see if the (x,y) is on infinite line
  a1 = a_pt2->x - a_pt1->x;
  b1 = a_pt2->y - a_pt1->y;
  mag = sqrt(a1 * a1 + b1 * b1);
  // handle case of line segment with length < tol distance to either point (pt1)
  if (mag <= a_tol)
  {
    return sqrt(sqr(a_pt1->x - a_x) + sqr(a_pt1->y - a_y));
  }

  // compute line equation
  double a, b;
  a = -b1 / mag;
  b = a1 / mag;
  c = -a * a_pt1->x - b * a_pt1->y;
  // compute distance from the line to (x,y)
  dist = a * a_x + b * a_y + c;

  return dist;
} // gm2DDistanceToLineWithTol
//------------------------------------------------------------------------------
/// \brief Compute the 2D distance in model units between 2 points.
/// \note See gmActualDistance if you don't want the distance in model units.
/// \param[in] pt1: Point 1.
/// \param[in] pt2: Point 2.
/// \return Distance between point 1 and 2.
//------------------------------------------------------------------------------
double gmXyDistance(const Pt3d& pt1, const Pt3d& pt2)
{
  return sqrt(sqr(pt1.x - pt2.x) + sqr(pt1.y - pt2.y));
} // gmXyDistance
//------------------------------------------------------------------------------
/// \brief Compute the 2D distance in model units between 2 points.
/// \note See gmActualDistance if you don't want the distance in model units.
/// \param x1: x coord of location 1.
/// \param y1: y coord of location 1.
/// \param x2: x coord of location 2.
/// \param y2: y coord of location 2.
/// \return Distance between location 1 and 2.
//------------------------------------------------------------------------------
double gmXyDistance(double x1, double y1, double x2, double y2)
{
  return sqrt(sqr(x1 - x2) + sqr(y1 - y2));
} // gmXyDistance
//------------------------------------------------------------------------------
/// \brief Calculate 2D distance squared between two points.
/// \param[in] pt1: First point.
/// \param[in] pt2: Second point.
/// \return Distance squared.
//------------------------------------------------------------------------------
double gmXyDistanceSquared(const Pt3d& pt1, const Pt3d& pt2)
{
  return (sqr(pt1.x - pt2.x) + sqr(pt1.y - pt2.y));
} // gmXyDistanceSqared
//------------------------------------------------------------------------------
/// \brief Compute the 3d distance between two points.
/// \param p1: The first point.
/// \param p2: The second point.
/// \return The distance between the points.
//------------------------------------------------------------------------------
double gmXYZDistanceBetweenPoints(const Pt4d& p1, const Pt4d& p2)
{
  double dx(p1.x - p2.x);
  double dy(p1.y - p2.y);
  double dz(p1.z - p2.z);
  double d(sqrt(dx * dx + dy * dy + dz * dz));
  return (d);
}
//------------------------------------------------------------------------------
/// \brief Compute the 3d distance between two points.
/// \param p1: The first point.
/// \param p2: The second point.
/// \return The distance between the points.
//------------------------------------------------------------------------------
double gmXYZDistanceBetweenPoints(const Pt3d& p1, const Pt3d& p2)
{
  double dx(p1.x - p2.x);
  double dy(p1.y - p2.y);
  double dz(p1.z - p2.z);
  double d(sqrt(dx * dx + dy * dy + dz * dz));
  return (d);
}
//------------------------------------------------------------------------------
/// \brief Compute the 3d distance squared between two points.
/// \param p1: The first point.
/// \param p2: The second point.
/// \return The distance squared between the points.
//------------------------------------------------------------------------------
double gmXYZDistanceSquared(const Pt3d& p1, const Pt3d& p2)
{
  double dx, dy, dz, d;
  dx = p1.x - p2.x;
  dy = p1.y - p2.y;
  dz = p1.z - p2.z;
  d = dx * dx + dy * dy + dz * dz;
  return (d);
} // gmXYZDistanceSquared
//------------------------------------------------------------------------------
/// \brief Compute the great circle distance between two latitude/longitude
///        points in meters.
/// \param[in] a_pt1: Point1. x = longitude, y = latitude. Can be negative.
/// \param[in] a_pt2: Point2. x = longitude, y = latitude. Can be negative.
/// \return The great circle distance between the two points.
//------------------------------------------------------------------------------
double gmGreatCircleDistanceMeters(const Pt2d& a_pt1, const Pt2d& a_pt2)
{
  // See Haversine formula. Assumes the earth is a sphere.

  const double kEarthRadiusMeters = 6.371e6;
  // Convert degrees to radians
  double lat1r = a_pt1.y * XM_PI / 180.0;
  double lon1r = a_pt1.x * XM_PI / 180.0;
  double lat2r = a_pt2.y * XM_PI / 180.0;
  double lon2r = a_pt2.x * XM_PI / 180.0;
  double u = sin((lat2r - lat1r) / 2);
  double v = sin((lon2r - lon1r) / 2);
  return 2.0 * kEarthRadiusMeters * asin(sqrt(u * u + cos(lat1r) * cos(lat2r) * v * v));
} // gmGreatCircleDistanceMeters
//------------------------------------------------------------------------------
/// \brief Find the minimum distance between two lines, the two closest points
///        on the lines, and the t values of those points.
/// \param p0: A point on the first line.
/// \param p1: Another point on the first line.
/// \param q0: A point on the second line.
/// \param q1: Another point on the second line.
/// \param ip1: The point on the first line which is closest to the second line.
/// \param ip2: The point on the second line which is closest to the first line.
/// \param t: The t value for ip1.
/// \param s: The t value for ip2.
/// \param tol: Tolerance for geometric comparison.
/// \return Distance between closest points if found, or -1 if lines parallel.
//------------------------------------------------------------------------------
double gmMinDistBetweenLinesWithTol(const Pt3d* p0,
  const Pt3d* p1,
  const Pt3d* q0,
  const Pt3d* q1,
  Pt3d* ip1,
  Pt3d* ip2,
  double* t,
  double* s,
  double tol)
{
  Pt3d u, v, r, d;
  double ru, rv, uu, uv, vv, den;
  /* generate vector from p0 to p1  */
  gmVectorSubtract(p1, p0, &v);
  /* generate vector from q0 to q1  */
  gmVectorSubtract(q1, q0, &u);
  /* generate vector from q0 to p0  */
  gmVectorSubtract(q0, p0, &r);
  /* compute dot products */
  ru = gmDot3D(r, u);
  rv = gmDot3D(r, v);
  uu = gmDot3D(u, u);
  uv = gmDot3D(u, v);
  vv = gmDot3D(v, v);
  /* compute denominator */
  den = uv * uv - uu * vv;
  /* see if the lines are parallel */
  if (LT_EPS(fabs(den), tol, DBL_EPSILON))
    return -1;
  else
  {
    *t = (rv * uu - ru * uv) / den;
    *s = -1 * (rv + (*t) * vv) / uv;
    *t = *t * -1;
    gmVectorAdd(*t, *p0, v, ip1);
    gmVectorAdd(*s, *q0, u, ip2);
    gmVectorSubtract(ip2, ip1, &d);
    return gmDot3D(d, d);
  }
} // gmMinDistBetweenLines
//------------------------------------------------------------------------------
/// \brief Compute the minimum 3D distance from a point to a plane.
/// \param pt1: First point defining the plane.
/// \param pt2: Second point defining the plane.
/// \param pt3: Third point defining the plane.
/// \param thePoint: The point to find the distance to.
/// \returns The 3D distance from thePoint to the plane.
//------------------------------------------------------------------------------
double gmDistanceFromPointToPlane(const Pt3d& pt1,
                                  const Pt3d& pt2,
                                  const Pt3d& pt3,
                                  const Pt3d& thePoint)
{
  double a, b, c, d;
  Pt3d vec1, vec2;
  double mag;
  double d1;

  vec1.x = pt1.x - pt2.x;
  vec1.y = pt1.y - pt2.y;
  vec1.z = pt1.z - pt2.z;
  vec2.x = pt3.x - pt2.x;
  vec2.y = pt3.y - pt2.y;
  vec2.z = pt3.z - pt2.z;
  a = vec1.y * vec2.z - vec1.z * vec2.y;
  b = vec1.z * vec2.x - vec1.x * vec2.z;
  c = vec1.x * vec2.y - vec1.y * vec2.x;
  mag = sqrt(sqr(a) + sqr(b) + sqr(c));
  a /= mag;
  b /= mag;
  c /= mag;
  d = -a * pt1.x - b * pt1.y - c * pt1.z;
  /* compute the distance from the plane to the Point */
  d1 = a * thePoint.x + b * thePoint.y + c * thePoint.z + d;
  return d1;
} // gmDistanceFromPointToPlane
//------------------------------------------------------------------------------
/// \brief Clip a convex polygon in NDC space.
/// \param npts: The number of points in the vertex array. Initialized to the
///              number of points in the clipped vertex array.
/// \param pts: Array of the polygon's vertices. Initialized to the array of the
///             clipped polygon's vertices.
//------------------------------------------------------------------------------
void gmClipNDCPoly(int* npts, Pt4d* pts)
{
  register int i, k, tmpnpts;
  double dx, dy, fracx, fracy;
  double x0, y0, x1, y1;
  Pt4d oldpts[10], *curr, *prev;

  tmpnpts = *npts;
  for (k = 1; k < 5; k++)
  {
    curr = prev = nullptr;
    *npts = tmpnpts;
    for (i = 0; i < tmpnpts; i++)
    {
      memcpy(&oldpts[i], &pts[i], sizeof(Pt4d));
    }
    tmpnpts = 0;
    for (i = 1; i <= *npts; i++)
    {
      prev = &oldpts[i - 1];
      if (i < *npts)
        curr = &oldpts[i];
      else
        curr = &oldpts[0];
      switch (k)
      {
      case 1: /* clip to x-min                            */
        if (i > 0 && prev)
        {
          if ((curr->x > 0.0 && prev->x < 0.0) || (curr->x < 0.0 && prev->x > 0.0))
          {
            x0 = curr->x;
            y0 = curr->y;
            x1 = prev->x;
            y1 = prev->y;
            pts[tmpnpts].x = 0.0;
            if (y0 == y1)
              pts[tmpnpts].y = y0;
            else
            {
              dx = x1 - x0;
              dy = y1 - y0;
              fracx = (0.0 - x0) / dx;
              pts[tmpnpts].y = y0 + fracx * dy;
              pts[tmpnpts].z = curr->z + fracx * (prev->z - curr->z);
            }
            tmpnpts++;
          }
        }
        if (curr->x >= 0.0)
        {
          memcpy(&pts[tmpnpts], curr, sizeof(Pt4d));
          tmpnpts++;
        }
        break;

      case 2: /* clip to y-min                            */
        if (i > 0 && prev)
        {
          if ((curr->y > 0.0 && prev->y < 0.0) || (curr->y < 0.0 && prev->y > 0.0))
          {
            x0 = curr->x;
            y0 = curr->y;
            x1 = prev->x;
            y1 = prev->y;
            pts[tmpnpts].y = 0.0;
            if (x0 == x1)
              pts[tmpnpts].x = x0;
            else
            {
              dx = x1 - x0;
              dy = y1 - y0;
              fracy = (0.0 - y0) / dy;
              pts[tmpnpts].x = x0 + fracy * dx;
              pts[tmpnpts].z = curr->z + fracy * (prev->z - curr->z);
            }
            tmpnpts++;
          }
        }
        if (curr->y >= 0.0)
        {
          memcpy(&pts[tmpnpts], curr, sizeof(Pt4d));
          tmpnpts++;
        }
        break;

      case 3: /* clip to x-max                            */
        if (i > 0 && prev)
        {
          if ((curr->x > 1.0 && prev->x < 1.0) || (curr->x < 1.0 && prev->x > 1.0))
          {
            x0 = curr->x;
            y0 = curr->y;
            x1 = prev->x;
            y1 = prev->y;
            pts[tmpnpts].x = 1.0;
            if (y0 == y1)
              pts[tmpnpts].y = y0;
            else
            {
              dx = x1 - x0;
              dy = y1 - y0;
              fracx = (1.0 - x0) / dx;
              pts[tmpnpts].y = y0 + fracx * dy;
              pts[tmpnpts].z = curr->z + fracx * (prev->z - curr->z);
            }
            tmpnpts++;
          }
        }
        if (curr->x <= 1.0)
        {
          memcpy(&pts[tmpnpts], curr, sizeof(Pt4d));
          tmpnpts++;
        }

        break;
      case 4: /* clip to y-max                            */
        if (i > 0 && prev)
        {
          if ((curr->y > 1.0 && prev->y < 1.0) || (curr->y < 1.0 && prev->y > 1.0))
          {
            x0 = curr->x;
            y0 = curr->y;
            x1 = prev->x;
            y1 = prev->y;
            pts[tmpnpts].y = 1.0;
            if (x0 == x1)
              pts[tmpnpts].x = x0;
            else
            {
              dx = x1 - x0;
              dy = y1 - y0;
              fracy = (1.0 - y0) / dy;
              pts[tmpnpts].x = x0 + fracy * dx;
              pts[tmpnpts].z = curr->z + fracy * (prev->z - curr->z);
            }
            tmpnpts++;
          }
        }
        if (curr->y <= 1.0)
        {
          memcpy(&pts[tmpnpts], curr, sizeof(Pt4d));
          tmpnpts++;
        }

        break;
      }
    }
  }
  *npts = tmpnpts;
} // gmClipNDCPoly
//------------------------------------------------------------------------------
/// \brief Clip a polygon to a rectangle.
/// \author MJK
/// \param pts: Array of vertices of the unclipped polygon.
/// \param n: Number of vertices of the unclipped polygon.
/// \param outpts: Initialized to the vertices in the clipped polygon.
/// \param outCount: Initialized to the number of vertices in the
///                  clipped polygon.
/// \param xMax: Maximum x coordinate of bounding box.
/// \param xMin: Minimum x coordinate of bounding box.
/// \param yMax: Maximum y coordinate of bounding box.
/// \param yMin: Minimum y coordinate of bounding box.
/// \return: Whether the operation could be completed.
//------------------------------------------------------------------------------
bool gmClipMpoint3PolyToRect(Pt3d pts[],
                             int n,
                             Pt3d* outpts[],
                             int* outCount,
                             double xMax,
                             double xMin,
                             double yMax,
                             double yMin)
{
  // Adapted from Computer Graphics Principles and Practice,
  // Liang - Barsky algorithm on page 935-937.
  // Modified to better handle horizontal and vertical lines.

  double xIn, xOut, yIn, yOut;     /* Coordinates of entry and exit points */
  double tOut1, tIn2, tOut2;       /* Parameter values of same */
  double tInX, tOutX, tInY, tOutY; /* Parameter values for intersections */
  double deltaX, deltaY;           /* Direction of edge */
  int i, numalloced = 25;

  *outCount = 0; /* Initialize output vertex counter */
  /* Malloc a big chunk at first so we don't have to realloc for each point */
  if (*outpts)
  {
    free(*outpts);
    *outpts = nullptr;
  }
  *outpts = (Pt3d*)malloc(numalloced * sizeof(Pt3d));
  if (!*outpts)
  {
    // gnNullMemoryErrorMessage("gmClipMpoint3PolyToRect");
    return false;
  }

  for (i = 0; i < n; i++)
  {
    if (i < n - 1)
    {
      deltaX = pts[i + 1].x - pts[i].x; /* Determine direction of edge */
      deltaY = pts[i + 1].y - pts[i].y;
    }
    else
    {
      deltaX = pts[0].x - pts[i].x;
      deltaY = pts[0].y - pts[i].y;
    }
    if (deltaX > 0.0 || (deltaX == 0.0 && pts[i].x > xMax))
    {
      /* headed right */
      xIn = xMin;
      xOut = xMax;
    }
    else
    {
      /* headed left */
      xIn = xMax;
      xOut = xMin;
    }
    if (deltaY > 0.0 || (deltaY == 0.0 && pts[i].y > yMax))
    {
      /* headed up */
      yIn = yMin;
      yOut = yMax;
    }
    else
    {
      /* headed down */
      yIn = yMax;
      yOut = yMin;
    }

    /* Find the t values for the x and y exit points. */
    if (deltaX != 0.0) /* non vertical line */
      tOutX = (xOut - pts[i].x) / deltaX;
    else if (pts[i].x <= xMax && xMin <= pts[i].x) /* vert. line in rectangle */
      tOutX = XM_DBL_HIGHEST;
    else /* vertical line outside the rectangle */
      tOutX = XM_DBL_LOWEST;

    if (deltaY != 0.0) /* non horizontal line */
      tOutY = (yOut - pts[i].y) / deltaY;
    else if (pts[i].y <= yMax && yMin <= pts[i].y) /* horiz. line in rectangle */
      tOutY = XM_DBL_HIGHEST;
    else /* horizontal line outside the rectangle */
      tOutY = XM_DBL_LOWEST;

    /* Order the two exit points */
    tOut1 = Mmin(tOutX, tOutY);
    tOut2 = Mmax(tOutX, tOutY);

    if (tOut2 > 0.0)
    {                    /* There could be output - compute tIn2. */
      if (deltaX != 0.0) /* non vertical line */
        tInX = (xIn - pts[i].x) / deltaX;
      else                    /* vertical line */
        tInX = XM_DBL_LOWEST; /* (negative infinity) */
      if (deltaY != 0.0)      /* non horizontal line */
        tInY = (yIn - pts[i].y) / deltaY;
      else                    /* horizontal line */
        tInY = XM_DBL_LOWEST; /* (negative infinity) */

      tIn2 = Mmax(tInX, tInY);

      if (tOut1 < tIn2)
      { /* segment leaves rect before it enters */
        if (0.0 < tOut1 && tOut1 <= 1.0)
        {
          /* Line crosses over intermediate corner region, add corner point */
          if (tInX < tInY)
            gmiOutputMpoint3Vert(outpts, outCount, xOut, yIn, &numalloced);
          else
            gmiOutputMpoint3Vert(outpts, outCount, xIn, yOut, &numalloced);
        }
      }
      else
      { /* Line crosses through window */
        if (0.0 < tOut1 && tIn2 <= 1.0)
        { /* Visible segment */
          if (0.0 < tIn2)
          {                  /* segment starts outside of rectangle */
            if (tInX > tInY) /* clip to the Y boundary */
              gmiOutputMpoint3Vert(outpts, outCount, xIn, pts[i].y + tInX * deltaY, &numalloced);
            else /* clip to the X boundary */
              gmiOutputMpoint3Vert(outpts, outCount, pts[i].x + tInY * deltaX, yIn, &numalloced);
          }
          else
          { /* segment starts inside rectangle */
          }
          if (1.0 > tOut1)
          {                    /* segment leaves the rectangle; needs a clip */
            if (tOutX < tOutY) /* clip to the X boundary */
              gmiOutputMpoint3Vert(outpts, outCount, xOut, pts[i].y + tOutX * deltaY, &numalloced);
            else /* clip to the Y boundary */
              gmiOutputMpoint3Vert(outpts, outCount, pts[i].x + tOutY * deltaX, yOut, &numalloced);
          }
          else
          { /* segment ends inside rectangle, add next point */
            if (i < n - 1)
              gmiOutputMpoint3Vert(outpts, outCount, pts[i + 1].x, pts[i + 1].y, &numalloced);
            else
              gmiOutputMpoint3Vert(outpts, outCount, pts[0].x, pts[0].y, &numalloced);
          }
        }
      }
      if (0.0 < tOut2 && tOut2 <= 1.0) /* add corner point */
        gmiOutputMpoint3Vert(outpts, outCount, xOut, yOut, &numalloced);
    }
  }
  /* Get rid of any extra memory we may have allocated */
  *outpts = (Pt3d*)realloc(*outpts, *outCount * sizeof(Pt3d));
  return true;
} // gmClipMpoint3PolyToRect
//------------------------------------------------------------------------------
/// \brief Get the Boundary Coordinates and OutCode for a 2D node.
/// \author   Mark Belnap, Michael Kennard
/// \param x: x coordinate of the node.
/// \param y: y coordinate of the node.
/// \param minx: Minimum x coordinate to clip to.
/// \param maxx: Maximum x coordinate to clip to.
/// \param miny: Minimum y coordinate to clip to.
/// \param maxy: Maximum y coordinate to clip to.
/// \return The clip codes in four bits of the int.
//------------------------------------------------------------------------------
int gmComputeClipCodes2(double x, double y, double minx, double maxx, double miny, double maxy)
{
  int OC = 0;

  if (x - minx < 0.0)
    OC = OC | LEFT_MASK; /* x is to the left of minx   */
  if (maxx - x < 0.0)
    OC = OC | RIGHT_MASK; /* x is to the right of maxx  */
  if (y - miny < 0.0)
    OC = OC | TOP_MASK; /* y is above the top of maxy */
  if (maxy - y < 0.0)
    OC = OC | BOTTOM_MASK; /* y is below the bottom maxy  */
  return OC;
} // gmComputeClipCodes2
//------------------------------------------------------------------------------
/// \brief Clip a line segment to fit inside a bounding box.
/// \pre OC1 and OC2 are outcodes computed by gmComputeClipCodes2.
/// \param x1: x coordinate of first endpoint of line segment. Initialized to
///            clipped value.
/// \param y1: y coordinate of first endpoint of line segment. Initialized to
///            clipped value.
/// \param x2: x coordinate of second endpoint of line segment. Initialized to
///            clipped value.
/// \param y2: y coordinate of second endpoint of line segment. Initialized to
///            clipped value.
/// \param OC1: OutCodes for the first endpoint, as computed
///             by gmComputeClipCodes2.
/// \param OC1: OutCodes for the second endpoint, as computed
///             by gmComputeClipCodes2.
/// \param minx: Minimum x coordinate to clip to.
/// \param maxx: Maximum x coordinate to clip to.
/// \param miny: Minimum y coordinate to clip to.
/// \param maxy: Maximum y coordinate to clip to.
/// \return XM_SUCCESS if the clipped line is within the bounding box and
///         should be drawn, else XM_FAILURE.
/// \author Mark Belnap
//------------------------------------------------------------------------------
int gmClipLine(double* x1,
               double* y1,
               double* x2,
               double* y2,
               int OC1,
               int OC2,
               double minx,
               double maxx,
               double miny,
               double maxy)
{
  int out1, out2; /* whether point 1 or 2 is outside */
                  /* of a particular side       */
  double t;

  /* trivially accept line if possible  */
  if (!(OC1 | OC2))
    return (XM_SUCCESS);
  /* trivially reject line if possible  */
  if (OC1 & OC2)
    return (XM_FAILURE);
  /*-------1---------2---------C---------c---------5---------6----------7-------*/
  /* clip left side if necessary */
  out1 = OC1 & LEFT_MASK;
  out2 = OC2 & LEFT_MASK;
  if (out1)
  { /* point one is outside to the left */
    t = (minx - *x1) / (*x2 - *x1);
    *x1 = (1.0 - t) * (*x1) + t * (*x2);
    *y1 = (1.0 - t) * (*y1) + t * (*y2);
    OC1 = gmComputeClipCodes2(*x1, *y1, minx, maxx, miny, maxy);
    if (!(OC1 | OC2)) /* trivially accept line if possible  */
      return (XM_SUCCESS);
    if (OC1 & OC2) /* trivially reject line if possible  */
      return (XM_FAILURE);
  }
  else if (out2)
  { /* point two is outside to the left */
    t = (minx - *x2) / (*x1 - *x2);
    *x2 = (1.0 - t) * (*x2) + t * (*x1);
    *y2 = (1.0 - t) * (*y2) + t * (*y1);
    OC2 = gmComputeClipCodes2(*x2, *y2, minx, maxx, miny, maxy);
    if (!(OC1 | OC2)) /* trivially accept line if possible  */
      return (XM_SUCCESS);
    if (OC1 & OC2) /* trivially reject line if possible  */
      return (XM_FAILURE);
  }
  /*-------1---------2---------C---------c---------5---------6----------7-------*/
  /* clip right side if necessary */
  out1 = OC1 & RIGHT_MASK;
  out2 = OC2 & RIGHT_MASK;
  if (out1)
  { /* point one is outside to the right */
    t = (*x1 - maxx) / (*x1 - *x2);
    *x1 = (1.0 - t) * (*x1) + t * (*x2);
    *y1 = (1.0 - t) * (*y1) + t * (*y2);
    OC1 = gmComputeClipCodes2(*x1, *y1, minx, maxx, miny, maxy);
    if (!(OC1 | OC2)) /* trivially accept line if possible  */
      return (XM_SUCCESS);
    if (OC1 & OC2) /* trivially reject line if possible  */
      return (XM_FAILURE);
  }
  else if (out2)
  { /* point two is outside to the right */
    t = (*x2 - maxx) / (*x2 - *x1);
    *x2 = (1.0 - t) * (*x2) + t * (*x1);
    *y2 = (1.0 - t) * (*y2) + t * (*y1);
    OC2 = gmComputeClipCodes2(*x2, *y2, minx, maxx, miny, maxy);
    if (!(OC1 | OC2)) /* trivially accept line if possible  */
      return (XM_SUCCESS);
    if (OC1 & OC2) /* trivially reject line if possible  */
      return (XM_FAILURE);
  }
  /*-------1---------2---------C---------c---------5---------6----------7-------*/
  /* clip top side if necessary */
  out1 = OC1 & TOP_MASK;
  out2 = OC2 & TOP_MASK;
  if (out1)
  { /* point one is outside to the top */
    t = (miny - *y1) / (*y2 - *y1);
    *x1 = (1.0 - t) * (*x1) + t * (*x2);
    *y1 = (1.0 - t) * (*y1) + t * (*y2);
    OC1 = gmComputeClipCodes2(*x1, *y1, minx, maxx, miny, maxy);
    if (!(OC1 | OC2)) /* trivially accept line if possible  */
      return (XM_SUCCESS);
    if (OC1 & OC2) /* trivially reject line if possible  */
      return (XM_FAILURE);
  }
  else if (out2)
  { /* point two is outside to the top */
    t = (miny - *y2) / (*y1 - *y2);
    *x2 = (1.0 - t) * (*x2) + t * (*x1);
    *y2 = (1.0 - t) * (*y2) + t * (*y1);
    OC2 = gmComputeClipCodes2(*x2, *y2, minx, maxx, miny, maxy);
    if (!(OC1 | OC2)) /* trivially accept line if possible  */
      return (XM_SUCCESS);
    if (OC1 & OC2) /* trivially reject line if possible  */
      return (XM_FAILURE);
  }
  /*-------1---------2---------C---------c---------5---------6----------7-------*/
  /* clip bottom side if necessary */
  out1 = OC1 & BOTTOM_MASK;
  out2 = OC2 & BOTTOM_MASK;
  if (out1)
  { /* point one is outside to the bottom */
    t = (*y1 - maxy) / (*y1 - *y2);
    *x1 = (1.0 - t) * (*x1) + t * (*x2);
    *y1 = (1.0 - t) * (*y1) + t * (*y2);
    OC1 = gmComputeClipCodes2(*x1, *y1, minx, maxx, miny, maxy);
    if (!(OC1 | OC2)) /* trivially accept line if possible  */
      return (XM_SUCCESS);
    if (OC1 & OC2) /* trivially reject line if possible  */
      return (XM_FAILURE);
  }
  else if (out2)
  { /* point two is outside to the bottom */
    t = (*y2 - maxy) / (*y2 - *y1);
    *x2 = (1.0 - t) * (*x2) + t * (*x1);
    *y2 = (1.0 - t) * (*y2) + t * (*y1);
    OC2 = gmComputeClipCodes2(*x2, *y2, minx, maxx, miny, maxy);
    if (!(OC1 | OC2)) /* trivially accept line if possible  */
      return (XM_SUCCESS);
    if (OC1 & OC2) /* trivially reject line if possible  */
      return (XM_FAILURE);
  }
  return XM_SUCCESS;
} // gmClipLine
//------------------------------------------------------------------------------
/// \brief Find the plan projection intersection of two line segments.
/// \note: segment 1 = one1,one2  = one1 + lambda(one2 - one1).
///        segment 2 = two1,two2  = two1 + mu (two2 - two1).
/// \param one1: First endpoint of segment 1.
/// \param one2: Second endpoint of segment 1.
/// \param two1: First endpoint of segment 2.
/// \param two2: Second endpoint of segment 2.
/// \param xi: Initialized to the x coord of intersection.
/// \param yi: Initialized to the y coord of intersection.
/// \param zi1: Initialized to the z coord of intersection on segment 1.
/// \param zi2: Initialized to the z coord of intersection on segemnt 2.
/// \param tol: Tolerance for geometric comparison.
/// \return Whether the line segments intersect.
//------------------------------------------------------------------------------
bool gmIntersectLineSegmentsWithTol(const Pt3d& one1,
                                    const Pt3d& one2,
                                    const Pt3d& two1,
                                    const Pt3d& two2,
                                    double* xi /*=NULL*/,
                                    double* yi /*=NULL*/,
                                    double* zi1 /*=NULL*/,
                                    double* zi2 /*=NULL*/,
                                    double tol /*=0.0*/)
{
  double minx1, minx2, miny1, miny2, maxx1, maxx2, maxy1, maxy2;
  double dx1, dy1, dz1, dx2, dy2, dz2, lambda, mu, cross;
  // do a trivial rejection
  // RDJ - 4/20/2004 Do tests one at a time so if we fail on one we stop
  minx1 = std::min(one1.x, one2.x);
  maxx2 = std::max(two1.x, two2.x);
  if (GT_TOL(minx1, maxx2, tol))
  {
    return false;
  }
  maxx1 = std::max(one1.x, one2.x);
  minx2 = std::min(two1.x, two2.x);
  if (LT_TOL(maxx1, minx2, tol))
  {
    return false;
  }
  miny1 = std::min(one1.y, one2.y);
  maxy2 = std::max(two1.y, two2.y);
  if (GT_TOL(miny1, maxy2, tol))
  {
    return false;
  }
  maxy1 = std::max(one1.y, one2.y);
  miny2 = std::min(two1.y, two2.y);
  if (LT_TOL(maxy1, miny2, tol))
  {
    return false;
  }
  // define the vectors
  dx1 = one2.x - one1.x;
  dy1 = one2.y - one1.y;
  dz1 = one2.z - one1.z;
  dx2 = two2.x - two1.x;
  dy2 = two2.y - two1.y;
  dz2 = two2.z - two1.z;
  /* see if lines are parallel */
  cross = (dx1 * dy2) -
          (dy1 * dx2); // dy1/dx1 = dy2/dx2 lines have same slope
                       // This checks the line slopes. If equal then the lines are parallel or
                       // the same line. We assume they are parallel and exit.
                       // But really theta should be computed using vector magnitudes
  if (EQ_TOL(cross, 0.0, tol))
    return false;
  // compute the value of lambda
  lambda = (dy2 * (two1.x - one1.x) + dx2 * (one1.y - two1.y)) / cross;

  // There is some question as to what effect the tolerance should have on this
  // function. It was decided that in the case where the segments do not
  // intersect, but the minimum distance between the two segments is within
  // tolerance, then the location of the minimum will be returned as the
  // point of intersection.
  // If the point of intersection is off the end of the first segment, then
  // set it to be at the end and set the checkDistance flag.
  bool checkDistance(false);
  if (lambda < 0.0)
  {
    lambda = 0.0;
    checkDistance = true;
  }
  else if (lambda > 1.0)
  {
    lambda = 1.0;
    checkDistance = true;
  }
  // The intersection is inside of segment 1, so we need to check segment 2
  // Compute mu from lambda and the two parametric segment equations
  //     two1 + mu (two2 - two1) = one1 + lambda ( one2 - one1)
  //                    so
  //     mu = (one1 + lambda (one2-one1) - two1)/(two2-two1)
  if (fabs(dx2) > fabs(dy2))
    mu = (one1.x + lambda * dx1 - two1.x) / dx2;
  else
    mu = (one1.y + lambda * dy1 - two1.y) / dy2;

  // If the point of intersection is off the end of the second segment, then
  // set it to be at the end and set the checkDistance flag.
  if (mu < 0.0)
  {
    mu = 0.0;
    checkDistance = true;
  }
  else if (mu > 1.0)
  {
    mu = 1.0;
    checkDistance = true;
  }
  // if checkDistance flag is true check distance between mu/lambda
  // positions (nearest points). If it is not within tolerance, return false.
  Pt3d lambdapos = one1 + Pt3d(lambda * dx1, lambda * dy1, lambda * dz1);
  Pt3d mupos = two1 + Pt3d(mu * dx2, mu * dy2, mu * dz2);
  if (checkDistance)
  {
    if (!gmEqualPointsXY(lambdapos, mupos, tol))
    {
      return false;
    }
  }

  if (gmColinearWithTol(one1, one2, lambdapos, tol / 2) &&
      gmColinearWithTol(two1, two2, lambdapos, tol / 2))
  {
    if (xi)
    {
      *xi = lambdapos.x;
    }
    if (yi)
    {
      *yi = lambdapos.y;
    }
  }
  else
  {
    if (xi)
    {
      *xi = mupos.x;
    }
    if (yi)
    {
      *yi = mupos.y;
    }
  }
  if (zi2)
    *zi2 = mupos.z;
  if (zi1)
    *zi1 = lambdapos.z;
  return true;
} // gmIntersectLineSegmentsWithTol
//------------------------------------------------------------------------------
/// \brief Find the plan projection intersection of two line segments.
/// \note: segment 1 = one1,one2  = one1 + lambda(one2 - one1).
///        segment 2 = two1,two2  = two1 + mu (two2 - two1).
/// \param one1: First point on segment 1.
/// \param one2: Second point on segment 1.
/// \param two1: First point on segment 2.
/// \param two2: Second point on segment 2.
/// \param xi: Initialized to the x coord of intersection.
/// \param yi: Initialized to the y coord of intersection.
/// \param zi1: Initialized to the z coord of intersection on segment 1.
/// \param zi2: Initialized to the z coord of intersection on segemnt 2.
/// \param: Ignored.
/// \return Whether the line segments intersect.
bool gmIntersectLineSegmentsNoTol(const Pt3d& one1,
                                  const Pt3d& one2,
                                  const Pt3d& two1,
                                  const Pt3d& two2,
                                  double* xi,
                                  double* yi,
                                  double* zi1,
                                  double* zi2,
                                  double)
{
  return gmIntersectLineSegmentsWithTol(one1, one2, two1, two2, xi, yi, zi1, zi2, 0.0);
} // gmIntersectLineSegmentsNoTol
//------------------------------------------------------------------------------
/// \brief Finds the intersection of a 2d line with a 2d line segment.
/// \param p1: First point on line segment.
/// \param p2: Second point on line segment.
/// \param l1: First point on line.
/// \param l2: Second point on line.
/// \param inter: Point of intersection.
/// \return Whether the line and segment intersect.
//------------------------------------------------------------------------------
bool gmIntersectSegmentWithLine(const Pt2d& p1,
                                const Pt2d& p2,
                                const Pt2d& l1,
                                const Pt2d& l2,
                                Pt2d* inter)
{
  return gmIntersectSegmentWithLine(p1, p2, l1, l2, inter, gmXyTol());
}
//------------------------------------------------------------------------------
/// \brief Finds the intersection of a 2d line with a 2d line segment.
/// \param p1: First point on line segment.
/// \param p2: Second point on line segment.
/// \param l1: First point on line.
/// \param l2: Second point on line.
/// \param inter: Point of intersection.
/// \param tol: Ignored.
/// \return Whether the line and segment intersect.
//------------------------------------------------------------------------------
bool gmIntersectSegmentWithLine(const Pt2d& p1,
                                const Pt2d& p2,
                                const Pt2d& l1,
                                const Pt2d& l2,
                                Pt2d* inter,
                                double /*tol*/)
{
  double a1(p2.x - p1.x), b1(p2.y - p1.y), a2(l2.x - l1.x), b2(l2.y - l1.y);
  /* see if lines are parallel */
  double cross((a1 * b2) - (b1 * a2));
  // AKZ 3/7/2011 - changed to compare to zero avoids divide by ZERO but
  //                handles small vectors
  if (cross == 0.0)
    return false;
  /* compute t of intersection on segment */
  double t1((b2 * (l1.x - p1.x) + a2 * (p1.y - l1.y)) / cross);
  /* make sure intersection is on segment */
  if ((t1 < 0) || (t1 > 1))
    return false;
  /* compute intersection */
  inter->x = p1.x + t1 * a1;
  inter->y = p1.y + t1 * b1;
  return true;
} // gmIntersectSegmentWithLine
//------------------------------------------------------------------------------
/// \brief Finds the intersection of a 2d line with a 2d line segment.
/// \param p1: First point on line segment.
/// \param p2: Second point on line segment.
/// \param l1: First point on line.
/// \param l2: Second point on line.
/// \param inter: Point of intersection.
/// \return Whether the line and segment intersect.
//------------------------------------------------------------------------------
bool gmIntersectSegmentWithLine(const Pt3d& p1,
                                const Pt3d& p2,
                                const Pt3d& l1,
                                const Pt3d& l2,
                                Pt3d* inter)
{
  return gmIntersectSegmentWithLine(p1, p2, l1, l2, inter, gmXyTol());
}
//------------------------------------------------------------------------------
/// \brief Finds the intersection of a 2d line with a 2d line segment.
/// \param p1: First point on line segment.
/// \param p2: Second point on line segment.
/// \param l1: First point on line.
/// \param l2: Second point on line.
/// \param inter: Point of intersection.
/// \param tol: Tolerance for geometric comparison.
/// \return Whether the line and segment intersect.
//------------------------------------------------------------------------------
bool gmIntersectSegmentWithLine(const Pt3d& p1,
                                const Pt3d& p2,
                                const Pt3d& l1,
                                const Pt3d& l2,
                                Pt3d* inter,
                                double tol)
{
  Pt2d pt1(p1);
  Pt2d pt2(p2);
  Pt2d ln1(l1);
  Pt2d ln2(l2);
  Pt2d intertemp;
  // call the mpoint2 version
  bool ok(gmIntersectSegmentWithLine(pt1, pt2, ln1, ln2, &intertemp, tol));
  inter->x = intertemp.x;
  inter->y = intertemp.y;
  inter->z = 0.0;
  return ok;
} // gmIntersectSegmentWithLine
//------------------------------------------------------------------------------
/// \brief Find the plan projection intersection of two lines.
/// \param one1: First point on first line.
/// \param one2: Second point on first line.
/// \param two1: First point on second line.
/// \param two2: Second point on second line.
/// \param xi: x coordinate of intersection point.
/// \param yi: y coordinate of intersection point.
/// \param tol: Ignored.
/// \return Whether the lines intersect.
//------------------------------------------------------------------------------
bool gmIntersectLines(const Pt3d& one1,
                      const Pt3d& one2,
                      const Pt3d& two1,
                      const Pt3d& two2,
                      double* xi,
                      double* yi,
                      double /*tol*/)
{
  double onet(0.0), twot(0.0);
  return gmiIntersectLines2D(one1, one2, two1, two2, xi, yi, onet, twot);
} // gmIntersectLines
//------------------------------------------------------------------------------
/// \brief Find the plan projection intersection of two lines.
/// \param one1: First point on first line.
/// \param one2: Second point on first line.
/// \param two1: First point on second line.
/// \param two2: Second point on second line.
/// \param xi: x coordinate of intersection point.
/// \param yi: y coordinate of intersection point.
/// \param zi: z coordinate of intersection point.
/// \param tol: Ignored.
/// \return Whether the lines intersect.
//------------------------------------------------------------------------------
bool gmIntersectLines(const Pt3d& one1,
                      const Pt3d& one2,
                      const Pt3d& two1,
                      const Pt3d& two2,
                      double* xi,
                      double* yi,
                      double* zi,
                      double /*tol*/)
{
  double c1(two2.z - two1.z);
  double onet(0.0), twot(0.);
  if (gmiIntersectLines2D(one1, one2, two1, two2, xi, yi, onet, twot))
  {
    *zi = two1.z + twot * c1;
    return true;
  }
  return false;
} // gmIntersectLines
//------------------------------------------------------------------------------
/// \brief Find the plan projection intersection of two lines.
/// \param one1: First point on line 1.
/// \param one2: Second point on line 1.
/// \param two1: First point on line 2.
/// \param two2: Second point on line 2.
/// \param xi: x coordinate of intersection point.
/// \param yi: y coordinate of intersection point.
/// \param zi: z coordinate of intersection point on line 1.
/// \param onet: % distance (0.0 to 1.0) of intersection on line 1 from p0.
/// \param twot: % distance (0.0 to 1.0) of intersection on line 2 from p2.
/// \return Whether the two lines intersect.
//------------------------------------------------------------------------------
bool gmIntersectLines(const Pt3d& one1,
                      const Pt3d& one2,
                      const Pt3d& two1,
                      const Pt3d& two2,
                      double* xi,
                      double* yi,
                      double* zi,
                      double& onet,
                      double& twot,
                      double /*tol*/)
{
  onet = twot = 0.0;
  if (gmiIntersectLines2D(one1, one2, two1, two2, xi, yi, onet, twot))
  {
    double c1(two2.z - two1.z);
    *zi = two1.z + twot * c1;
    return true;
  }
  return false;
} // gmIntersectLines
//------------------------------------------------------------------------------
/// \brief Check whether two plan projection line segments intersect.
/// \note segment 1 = one1,one2  = one1 + lambda(one2 - one1)
///       segment 2 = two1,two2  = two1 + mu (two2 - two1)
/// \param one1: First endpoint of first segment.
/// \param one2: Second endpoint of first segment.
/// \param two1: First endpoint of second segment.
/// \param two2: Second endpoint of second segment.
/// \return Whether the segments intersect.
//------------------------------------------------------------------------------
bool gmLinesIntersect(const Pt3d& one1, const Pt3d& one2, const Pt3d& two1, const Pt3d& two2)
{
  // do a trivial rejection
  double min = std::min(one1.x, one2.x);
  double max = std::max(two1.x, two2.x);
  const double tol(XM_ZERO_TOL);
  if (GT_TOL(min, max, tol))
    return false;
  max = std::max(one1.x, one2.x);
  min = std::min(two1.x, two2.x);
  if (LT_TOL(max, min, tol))
    return false;
  min = std::min(one1.y, one2.y);
  max = std::max(two1.y, two2.y);
  if (GT_TOL(min, max, tol))
    return false;
  max = std::max(one1.y, one2.y);
  min = std::min(two1.y, two2.y);
  if (LT_TOL(max, min, tol))
    return false;
  // define the vectors
  Pt2d d1(one2 - one1), d2(two2 - two1);
  // see if lines are parallel
  // SMS bug fix: replaced tolerance check with a non-zero check.
  // Sometimes we have very small tolerances
  double cross = (d2.x * d1.y) - (d2.y * d1.x);
  if (cross == 0.0)
    return false;
  // if the lines intersect s should be between 0.0 and 1.0
  double s = ((d1.x * (two1.y - one1.y)) + (d1.y * (one1.x - two1.x))) / cross;
  if (LT_TOL(s, 0.0, tol) || GT_TOL(s, 1.0, tol))
    return false;
  // if the lines intersect t should be between -1.0 and 0.0
  double t = ((d2.x * (one1.y - two1.y)) + (d2.y * (two1.x - one1.x))) / cross;
  if (LT_TOL(t, -1.0, tol) || GT_TOL(t, 0.0, tol))
    return false;
  return true;
} // gmLinesIntersect
//------------------------------------------------------------------------------
/// \brief Determine whether 2 line segments cross. The segments may touch at
///        the end points.
/// \note Crossing is similar to intersection, except that the segments are
///       allowed to have different z values at the crossing.
/// \param[in] a_segment1Point1: First endpoint of line segment 1
/// \param[in] a_segment1Point2: Second endpoint of line segment 1
/// \param[in] a_segment2Point1: First endpoint of line segment 2
/// \param[in] a_segment2Point2: Second endpoint of line segment 2
/// \return true if the line segments cross
//------------------------------------------------------------------------------
bool gmLinesCross(const Pt3d& a_segment1Point1,
                  const Pt3d& a_segment1Point2,
                  const Pt3d& a_segment2Point1,
                  const Pt3d& a_segment2Point2)
{
  // Boundary case checks
  // Any of the points from line segment 1 are the same as any points from line segment 2
  if ((a_segment1Point1 == a_segment2Point1 || a_segment1Point1 == a_segment2Point2) &&
      (a_segment1Point2 == a_segment2Point1 || a_segment1Point2 == a_segment2Point2))
    return true;

  // The segments AB and CD intersect if and only if both of the following are true:
  //
  // A and B lie on different sides of the line through C and D
  // C and D lie on different sides of the line through A and B
  // These two conditions can be tested for using the notion of a scalar cross product(formulas
  // below).

  // is true if and only if the scalar cross products CA->=CD-> and CB->=CD-> have opposite signs.
  // is true if and only if the scalar cross products AC->=AB-> and AD->=AB-> have opposite signs.

  // Conclusion: the line segments intersect if and only if both are negative
  double result1 = gmCross2D(a_segment2Point1, a_segment1Point1, a_segment2Point2);
  double result2 = gmCross2D(a_segment2Point1, a_segment1Point2, a_segment2Point2);
  double result3 = gmCross2D(a_segment1Point1, a_segment2Point1, a_segment1Point2);
  double result4 = gmCross2D(a_segment2Point1, a_segment2Point2, a_segment1Point2);

  return (result1 * result2 < 0 && result3 * result4 < 0);
} // gmLinesCross
//------------------------------------------------------------------------------
/// \brief Determine if a line segment intersects a triangle.
/// \param[in] a_pt1: First endpoint of the line segment.
/// \param[in] a_pt2: Second endpoint of the line segment.
/// \param[in] a_t0: First vertex defining a triangle.
/// \param[in] a_t1: Second vertex defining a triangle.
/// \param[in] a_t2: Third vertex defining a triangle.
/// \param[out] a_IntersectPt: Initialized to the point of intersection, if
///                            it exists.
/// \return -1 if triangle is degenerate (a point or a line)
///          0 if line does not intersect triangle
///          1 if line does intersect triangle
///          2 if line and triangle are in the same plane
//
// Copyright 2001, softSurfer (www.softsurfer.com)
//   This code may be freely used and modified for any purpose providing that
//   this copyright notice is included with it.  SoftSurfer makes no warranty
//   for this code, and cannot be held liable for any real or imagined damage
//   resulting from its use.  Users of this code must verify correctness for
//   their application.
// http://geometryalgorithms.com/Archive/algorithm_0105/algorithm_0105.htm
//------------------------------------------------------------------------------
int gmIntersectTriangleAndLineSegment(const Pt3d& a_pt1,
                                      const Pt3d& a_pt2,
                                      const Pt3d& a_t0,
                                      const Pt3d& a_t1,
                                      const Pt3d& a_t2,
                                      Pt3d& a_IntersectPt)
{
  double a, b, r;
  Pt3d dir, n, NullVector(0.0, 0.0, 0.0), u, v, w, w0;

  // get the triangle edge vectors and plane normal
  u = a_t1 - a_t0;
  v = a_t2 - a_t0;
  gmCross3D(u, v, &n);

  // check if the triangle is degenerate
  if (n == NullVector)
  {
    return -1;
  }

  // get the ray direction vector
  dir = a_pt2 - a_pt1;
  w0 = a_pt1 - a_t0;
  a = -gmDot3D(n, w0);
  b = gmDot3D(n, dir);

  // see if ray is parallel to the triangle
  if (fabs(b) < XM_ZERO_TOL)
  {
    // see if ray lies in triangle plane
    if (a == 0)
    {
      return 2;
    }
    // else ray is disjoint from the triangle plane
    else
    {
      return 0;
    }
  }

  // get the intersection point or ray with triangle plane
  r = a / b;

  // see if there is an intersection
  // if (r < 0.0 || r > 1.0) {
  if (r < -FLT_EPSILON || r > 1.0 + FLT_EPSILON)
  {
    return 0;
  }

  // intersect point of ray and plane
  a_IntersectPt = a_pt1 + dir * r;

  // see if the intersection is inside of the triangle
  double D, uu, uv, vv, wu, wv;

  uu = gmDot3D(u, u);
  uv = gmDot3D(u, v);
  vv = gmDot3D(v, v);
  w = a_IntersectPt - a_t0;
  wu = gmDot3D(w, u);
  wv = gmDot3D(w, v);
  D = uv * uv - uu * vv;

  // get the test parametric coords
  double s, t;

  s = (uv * wv - vv * wu) / D;
  if (s < 0.0 || s > 1.0)
  {
    // the intersect point is outside the triangle
    return 0;
  }
  t = (uv * wu - uu * wv) / D;
  if (t < 0.0 || (s + t) > 1.0)
  {
    // the intersect point is outside the triangle
    return 0;
  }

  // the intersect point is inside the triangle
  return 1;
} // gmIntersectTriangleAndLineSegment
//------------------------------------------------------------------------------
/// \brief Test whether a 3d ray intersects a 3d triangle.
/// \note Algorithm taken from Graphics Gems I.
/// \pre Triangle vertices must be in counter clockwise order.
/// \param origin: Origin of the ray.
/// \param vert1: A point on the ray.
/// \param v30: First vertex of the triangle.
/// \param v31: Second vertex of the triangle.
/// \param v32: Third vertex of the triangle.
/// \param theisect: Initialized to the point where the ray intersects the
///                  triangle, if they intersect. Value is undefined otherwise.
/// \return Whether the ray intersects the triangle.
//------------------------------------------------------------------------------
bool gmLineAndTriangleIntersect(const Pt3d& origin,
                                const Pt3d& vert1,
                                const Pt3d& v30,
                                const Pt3d& v31,
                                const Pt3d& v32,
                                Pt3d* theisect /*NULL*/)
{
  Pt3d vector;
  double t, d, denom;
  double u0, u1, u2, v0, v1, v2;
  double alpha, beta;
  Pt3d normal, isect;
  Pt3d v20, v21, v22, isect2;
  bool inter;
  int plane;
  double abx, aby, abz;

  /* convert the line segment into a ray */

  vector.x = vert1.x - origin.x;
  vector.y = vert1.y - origin.y;
  vector.z = vert1.z - origin.z;

  /* determine the plane coefficients */

  normal = gmComputePlaneNormal(v30, v31, v32);
  d = -normal.x * v30.x - normal.y * v30.y - normal.z * v30.z;

  /* detrmine the ray intersection with the plane of the triangle */
  denom = gmDot3D(normal, vector);
  if (denom == 0.0) // orthogonal vectors no unique intersection
    return false;
  t = -(d + gmDot3D(normal, origin)) / denom;
  isect.x = origin.x + vector.x * t;
  isect.y = origin.y + vector.y * t;
  isect.z = origin.z + vector.z * t;

  if (theisect)
    *theisect = isect;
  /* now determine if the intersection point was inside triangle */
  /* map the triangle to the best 2d plane */

  abx = fabs(normal.x);
  aby = fabs(normal.y);
  abz = fabs(normal.z);
  if (GTEQ_EPS(abx, aby, FLT_EPSILON) && GTEQ_EPS(abx, abz, FLT_EPSILON))
    plane = 0;
  else if (GTEQ_EPS(aby, abx, FLT_EPSILON) && GTEQ_EPS(aby, abz, FLT_EPSILON))
    plane = 1;
  else
    plane = 2;

  v20 = gmProjectVectorToPlane(v30, plane);
  v21 = gmProjectVectorToPlane(v31, plane);
  v22 = gmProjectVectorToPlane(v32, plane);
  isect2 = gmProjectVectorToPlane(isect, plane);

  u0 = isect2.x - v20.x;
  v0 = isect2.y - v20.y;
  u1 = v21.x - v20.x;
  u2 = v22.x - v20.x;
  v1 = v21.y - v20.y;
  v2 = v22.y - v20.y;

  if (EQ_EPS(u1, 0.0, FLT_EPSILON))
  {
    beta = u0 / u2;
    if (GTEQ_EPS(beta, 0.0, FLT_EPSILON) && LTEQ_EPS(beta, 1.0, FLT_EPSILON))
    {
      alpha = (v0 - beta * v2) / v1;
      inter = ((alpha >= 0.) && ((alpha + beta) <= 1.));
    }
    else
      inter = false;
  }
  else
  {
    beta = (v0 * u1 - u0 * v1) / (v2 * u1 - u2 * v1);
    if (GTEQ_EPS(beta, 0.0, FLT_EPSILON) && LTEQ_EPS(beta, 1.0, FLT_EPSILON))
    {
      alpha = (u0 - beta * u2) / u1;
      inter = (GTEQ_EPS(alpha, 0.0, FLT_EPSILON) && LTEQ_EPS((alpha + beta), 1.0, FLT_EPSILON));
    }
    else
      inter = false;
  }
  return (inter);

} // gmLineAndTriangleIntersect
//------------------------------------------------------------------------------
/// \brief Find the points of intersection of a line segment with a sphere.
/// \param a_l1: First endpoint of the line segment.
/// \param a_l2: Second endpoint of the line segment.
/// \param a_sc: Center of the sphere.
/// \param a_r: Radius of the sphere.
/// \param a_pts: Initialized to contain the points of intersection. May have
///               0, 1, or 2 values depending on number of intersections.
//------------------------------------------------------------------------------
void gmSphereLineIntersection(const Pt3d& a_l1,
                              const Pt3d& a_l2,
                              const Pt3d& a_sc,
                              double a_r,
                              VecPt3d& a_pts)
{
  // This function returns a pointer array which first index indicates
  // the number of intersection point, followed by coordinate pairs.
  a_pts.clear();

  double a, b, c, i;

  a = sqr(a_l2.x - a_l1.x) + sqr(a_l2.y - a_l1.y) + sqr(a_l2.z - a_l1.z);
  b = 2 * ((a_l2.x - a_l1.x) * (a_l1.x - a_sc.x) + (a_l2.y - a_l1.y) * (a_l1.y - a_sc.y) +
           (a_l2.z - a_l1.z) * (a_l1.z - a_sc.z));
  c = sqr(a_sc.x) + sqr(a_sc.y) + sqr(a_sc.z) + sqr(a_l1.x) + sqr(a_l1.y) + sqr(a_l1.z) -
      2 * (a_sc.x * a_l1.x + a_sc.y * a_l1.y + a_sc.z * a_l1.z) - sqr(a_r);
  i = b * b - 4 * a * c;

  if (LT_EPS(i, 0.0, DBL_EPSILON))
  {
    // no intersection
  }
  else if (EQ_EPS(i, 0.0, DBL_EPSILON))
  {
    // one intersection
    double mu = -b / (2 * a);
    a_pts.push_back(Pt3d(a_l1.x + mu * (a_l2.x - a_l1.x), a_l1.y + mu * (a_l2.y - a_l1.y),
                         a_l1.z + mu * (a_l2.z - a_l1.z)));
  }
  else // i > 0.0
  {
    // two intersections

    // first intersection
    double mu = (-b + sqrt(sqr(b) - 4 * a * c)) / (2 * a);
    a_pts.push_back(Pt3d(a_l1.x + mu * (a_l2.x - a_l1.x), a_l1.y + mu * (a_l2.y - a_l1.y),
                         a_l1.z + mu * (a_l2.z - a_l1.z)));

    // second intersection
    mu = (-b - sqrt(sqr(b) - 4 * a * c)) / (2 * a);
    a_pts.push_back(Pt3d(a_l1.x + mu * (a_l2.x - a_l1.x), a_l1.y + mu * (a_l2.y - a_l1.y),
                         a_l1.z + mu * (a_l2.z - a_l1.z)));
  }
} // gmSphereLineIntersection

//------------------------------------------------------------------------------
/// \brief Check whether any intersections between a plane and aconvex polygon
///        occurs.
/// \param pln: Coefficients in the plane equation. Ordered a, b, c, d.
/// \param nnodes: Ignored.
/// \param poly: Polygon vertices.
/// \param tripln: Plane equation for triangle.
/// \param seg: Coordinates of intx points.
/// \param tol: Tolerance for geometric comparison.
/// \return 0 if no intersection
///         1 if intersection
///         2 if polygon lies on the plane (up)
///         3 if polygon lies on the plane (down)
//------------------------------------------------------------------------------
int gmIntersectPlnWithPolWithTol(const double pln[4],
                                 int /*nnodes*/,
                                 Pt3d* poly,
                                 const double tripln[4],
                                 Pt3d seg[2],
                                 double tol)
{
  int npts, stat;
  double d1, d2, d3, len1, len2, len3, percent;
  Pt3d *pt1, *pt2, *pt3, polvec, plnvec, segvec, lftvec;
  /* get local copy of plane direction vector*/
  plnvec.x = pln[0];
  plnvec.y = pln[1];
  plnvec.z = pln[2];
  /* check for polygon laying on the plane   */
  if (fabs(tripln[0] - pln[0]) < tol && fabs(tripln[1] - pln[1]) < tol &&
      fabs(tripln[2] - pln[2]) < tol && fabs(tripln[3] - pln[3]) < tol)
    return (2);
  if (fabs(tripln[0] + pln[0]) < tol && fabs(tripln[1] + pln[1]) < tol &&
      fabs(tripln[2] + pln[2]) < tol && fabs(tripln[3] + pln[3]) < tol)
    return (3);
  /* get distance for the 3 pts from plane */
  pt1 = &poly[0];
  d1 = gmDot3D(plnvec, *pt1) + pln[3];
  len1 = fabs(d1);
  pt2 = &poly[1];
  d2 = gmDot3D(plnvec, *pt2) + pln[3];
  len2 = fabs(d2);
  pt3 = &poly[2];
  d3 = gmDot3D(plnvec, *pt3) + pln[3];
  len3 = fabs(d3);
  npts = 0;
  /* check first edge for an intersection */
  if (d1 * d2 < 0.0 && len1 > tol && len2 > tol)
  {
    /* clean intersection */
    percent = len1 / (len1 + len2);
    seg[npts].x = pt1->x + percent * (pt2->x - pt1->x);
    seg[npts].y = pt1->y + percent * (pt2->y - pt1->y);
    seg[npts].z = pt1->z + percent * (pt2->z - pt1->z);
    ++npts;
  }
  else if (len1 < tol && len2 < tol)
  {
    /* polygon edge lies on plane */
    seg[0].x = pt1->x;
    seg[0].y = pt1->y;
    seg[0].z = pt1->z;
    seg[1].x = pt2->x;
    seg[1].y = pt2->y;
    seg[1].z = pt2->z;
    npts = 2;
  }
  else if (len1 < tol)
  {
    /* polygon edge starts on plane */
    seg[npts].x = pt1->x;
    seg[npts].y = pt1->y;
    seg[npts].z = pt1->z;
    ++npts;
  }
  /* check second edge for an intersection */
  if (d2 * d3 < 0.0 && len2 > tol && len3 > tol)
  {
    /* clean intersection */
    percent = len2 / (len2 + len3);
    seg[npts].x = pt2->x + percent * (pt3->x - pt2->x);
    seg[npts].y = pt2->y + percent * (pt3->y - pt2->y);
    seg[npts].z = pt2->z + percent * (pt3->z - pt2->z);
    ++npts;
  }
  else if (len2 < tol && len3 < tol)
  {
    /* polygon edge lies on plane */
    seg[0].x = pt2->x;
    seg[0].y = pt2->y;
    seg[0].z = pt2->z;
    seg[1].x = pt3->x;
    seg[1].y = pt3->y;
    seg[1].z = pt3->z;
    npts = 2;
  }
  else if (len2 < tol)
  {
    /* polygon edge starts on plane */
    seg[npts].x = pt2->x;
    seg[npts].y = pt2->y;
    seg[npts].z = pt2->z;
    ++npts;
  }
  /* check third edge for an intersection */
  if (d3 * d1 < 0.0 && len3 > tol && len1 > tol)
  {
    /* clean intersection */
    percent = len3 / (len3 + len1);
    seg[npts].x = pt3->x + percent * (pt1->x - pt3->x);
    seg[npts].y = pt3->y + percent * (pt1->y - pt3->y);
    seg[npts].z = pt3->z + percent * (pt1->z - pt3->z);
    ++npts;
  }
  else if (len3 < tol && len1 < tol)
  {
    /* polygon edge lies on plane */
    seg[0].x = pt3->x;
    seg[0].y = pt3->y;
    seg[0].z = pt3->z;
    seg[1].x = pt1->x;
    seg[1].y = pt1->y;
    seg[1].z = pt1->z;
    npts = 2;
  }
  else if (len3 < tol)
  {
    /* polygon edge starts on plane */
    seg[npts].x = pt3->x;
    seg[npts].y = pt3->y;
    seg[npts].z = pt3->z;
    ++npts;
  }

  if (npts < 2)
    stat = 0;
  else
  {
    /* make sure line direction is right */
    segvec.x = seg[1].x - seg[0].x;
    polvec.x = tripln[0];
    segvec.y = seg[1].y - seg[0].y;
    polvec.y = tripln[1];
    segvec.z = seg[1].z - seg[0].z;
    polvec.z = tripln[2];
    gmCross3D(segvec, polvec, &lftvec);
    d1 = gmDot3D(lftvec, plnvec);
    if (d1 < 0.0)
    { /* wrong direction, swap */
      segvec.x = seg[0].x;
      segvec.y = seg[0].y;
      segvec.z = seg[0].z;
      seg[0].x = seg[1].x;
      seg[0].y = seg[1].y;
      seg[0].z = seg[1].z;
      seg[1].x = segvec.x;
      seg[1].y = segvec.y;
      seg[1].z = segvec.z;
    }
    stat = 1;
  }
  return (stat);
} // gmIntersectPlnWithPolWithTol
//------------------------------------------------------------------------------
/// \brief Determines whether a point is inside, outside, or on a plane defined
///        by three points.
/// \pre Points must not be coincident.
/// \param point1: First point defining the plane.
/// \param point2: Second point defining the plane.
/// \param point3: Third point defining the plane.
/// \param oppositepoint: A point on the "inside" of the plane.
/// \param x: x coordinate of a point to test.
/// \param y: y coordinate of a point to test.
/// \param z: z coordinate of a point to test.
/// \param tolerance: Tolerance for geometric comparison.
/// \return 0 if the point is on the plane
///         1 if the point is on the same side of the plane as oppositepoint
///         2 if the point is on the opposite side of the plane from oppositepoint
//------------------------------------------------------------------------------
int gmClassifyPointFromPlane(const Pt3d& point1,
                             const Pt3d& point2,
                             const Pt3d& point3,
                             const Pt3d& oppositepoint,
                             double x,
                             double y,
                             double z,
                             double tolerance)
{
  double a, b, c, d;
  Pt3d vec1, vec2, pt;
  double mag;

  vec1.x = point1.x - point2.x;
  vec1.y = point1.y - point2.y;
  vec1.z = point1.z - point2.z;
  vec2.x = point3.x - point2.x;
  vec2.y = point3.y - point2.y;
  vec2.z = point3.z - point2.z;
  a = vec1.y * vec2.z - vec1.z * vec2.y;
  b = vec1.z * vec2.x - vec1.x * vec2.z;
  c = vec1.x * vec2.y - vec1.y * vec2.x;
  mag = sqrt(sqr(a) + sqr(b) + sqr(c));
  a /= mag;
  b /= mag;
  c /= mag;
  d = -a * point2.x - b * point2.y - c * point2.z;

  pt.x = x;
  pt.y = y;
  pt.z = z;
  return (gmClassifyPointFromPlane(a, b, c, d, oppositepoint, pt, tolerance));
} // gmClassifyPointFromPlane
//------------------------------------------------------------------------------
/// \brief Determines whether a point is inside, outside, or on a plane defined
///        by its plane coefficients.
/// \param a: a coefficient in the plane's equation.
/// \param b: b coefficient in the plane's equation.
/// \param c: c coefficient in the plane's equation.
/// \param d: d constant in the plane's equation.
/// \param oppositepoint: A point on the "inside" of the plane.
/// \param pt: The point to test.
/// \param tolerance: Tolerance for geometric comparison.
/// \return 0 if the point is on the plane
///         1 if the point is on the same side of the plane as oppositepoint
///         2 if the point is on the opposite side of the plane from oppositepoint
//------------------------------------------------------------------------------
int gmClassifyPointFromPlane(double a,
                             double b,
                             double c,
                             double d,
                             const Pt3d& oppositepoint,
                             const Pt3d& pt,
                             double tolerance)
{
  double d1, d2;
  /* compute distance from plane to Point */
  d1 = a * pt.x + b * pt.y + c * pt.z + d;
  if (fabs(d1) <= tolerance)
    return (0); /* On plane */
                /* compute distance from plane to oppositepoint */
  d2 = a * oppositepoint.x + b * oppositepoint.y + c * oppositepoint.z + d;
  if (((d1 < 0.0) && (d2 < 0.0)) || ((d1 > 0.0) && (d2 > 0.0)))
    return (1); /* Inside plane */
  else
    return (2); /* Outside plane */
} // gmClassifyPointFromPlane
//------------------------------------------------------------------------------
/// \brief Test if a point is on a line segment.
/// \note For simple test of colinearity, call gmOnLine or gmColinear.
/// \param p1: First endpoint of the segment.
/// \param p2: Second endpoint of the segment.
/// \param x: x coordinate of the point to test.
/// \param y: y coordinate of the point to test.
/// \return Whether the point is on the line segment.
//------------------------------------------------------------------------------
bool gmOnLineAndBetweenEndpoints(const Pt3d* p1, const Pt3d* p2, const double x, const double y)
{
  if ((Mmin(p1->x, p2->x) - gmXyTol() <= x && Mmax(p1->x, p2->x) + gmXyTol() >= x) &&
    (Mmin(p1->y, p2->y) - gmXyTol() <= y && Mmax(p1->y, p2->y) + gmXyTol() >= y))
    return gmOnLine(p1, p2, x, y);
  else
    return false;
} // gmOnLineAndBetweenEndpoints
//------------------------------------------------------------------------------
/// \brief Check if a point is on a line segment.
/// \note For simple test of colinearity, call gmOnLineWithTol or gmColinear.
/// \param a_pt1: First location defining segment.
/// \param a_pt2: Second location defining segment.
/// \param a_x: x coord.
/// \param a_y: y coord.
/// \param a_tol: Tolerance for comparison.
/// \return Whether the point (x,y) is on the line segment.
//------------------------------------------------------------------------------
bool gmOnLineAndBetweenEndpointsWithTol(const Pt3d& a_pt1,
                                        const Pt3d& a_pt2,
                                        const double a_x,
                                        const double a_y,
                                        double a_tol)
{
  if ((Mmin(a_pt1.x, a_pt2.x) - a_tol <= a_x && Mmax(a_pt1.x, a_pt2.x) + a_tol >= a_x) &&
    (Mmin(a_pt1.y, a_pt2.y) - a_tol <= a_y && Mmax(a_pt1.y, a_pt2.y) + a_tol >= a_y))
    return gmOnLineWithTol(a_pt1, a_pt2, a_x, a_y, a_tol) == true;
  else
    return false;
} // gmOnLineAndBetweenEndpointsWithTol
//------------------------------------------------------------------------------
/// \brief Test if a point is in the middle third of a line segment.
/// \param v1: The point to test.
/// \param v2: The first endpoint of the segment.
/// \param v3: The second endpoint of the segment.
/// \param tol: Tolerance for geometric comparison.
//------------------------------------------------------------------------------
bool gmMiddleThird(const Pt3d* v1, const Pt3d* v2, const Pt3d* v3)
{
  return gmMiddleThirdWithTol(*v1, *v2, *v3, gmXyTol());
} // gmMiddleThird
//------------------------------------------------------------------------------
/// \brief Test if a point is in the middle third of a line segment.
/// \param v1: The point to test.
/// \param v2: The first endpoint of the segment.
/// \param v3: The second endpoint of the segment.
/// \param tol: Tolerance for geometric comparison.
//------------------------------------------------------------------------------
bool gmMiddleThirdWithTol(const Pt3d& v1, const Pt3d& v2, const Pt3d& v3, double tol)
{
  double dist, m1, m2, dx, dy, b1, b2; /* y = mx + b */
  double fval;
  Pt3d pt, p1, p2;

  /* get distance and other parameters */
  dist = gm2DDistanceToLineSegmentWithTol(&v2, &v3, v1.x, v1.y, tol);
  dx = v3.x - v2.x;
  dy = v3.y - v2.y;
  if (dist > Mdist(v3.x, v3.y, v2.x, v2.y) / 3.0)
    return false;
  /* get test point on line */
  if (dist <= tol)
  {
    pt.x = v1.x;
    pt.y = v1.y;
  }
  else if (dx == 0.0)
  {
    pt.x = v2.x;
    pt.y = v1.y;
  }
  else if (dy == 0.0)
  {
    pt.y = v2.y;
    pt.x = v1.x;
  }
  else
  {
    /* find intersection of lines */
    m1 = dy / dx;
    b1 = v3.y - m1 * v3.x;
    m2 = -1 / m1;
    b2 = v1.y - m2 * v1.x;
    pt.x = (b2 - b1) / (m1 - m2);
    pt.y = m1 * pt.x + b1;
  }
  /* get control points on line */
  p1.x = v2.x + (dx / 3.0);
  p1.y = v2.y + (dy / 3.0);
  p2.x = v3.x - (dx / 3.0);
  p2.y = v3.y - (dy / 3.0);
  if ((p1.x > p2.x && p1.y < p2.y) || (p1.y > p2.y && p1.x < p2.x))
  {
#define SWAP(a, b, c) (c = a, a = b, b = c) ///< Swaps
    SWAP(p1.x, p2.x, fval);
  }
  /* check if pt is between p1 and p2 */
  if ((pt.x <= p2.x && pt.x >= p1.x) && (pt.y <= p2.y && pt.y >= p1.y) ||
    (pt.x <= p1.x && pt.x >= p2.x) && (pt.y <= p1.y && pt.y >= p2.y))
    return true;
  else
    return false;
} // gmMiddleThirdWithTol
//------------------------------------------------------------------------------
/// \brief Test if a point is on a line.
/// \note Robust collinear test requires use of gmColinear.
/// \param p1: A point on the line.
/// \param p2: Another point on the line.
/// \param x: x coordinate of the point to test.
/// \param y: y coordinate of the point to test.
/// \return Whether the point is on the line.
//------------------------------------------------------------------------------
bool gmOnLine(const Pt3d* p1, const Pt3d* p2, const double x, const double y)
{
  return gmOnLineWithTol(*p1, *p2, x, y, gmXyTol());
} // gmOnLine
//------------------------------------------------------------------------------
/// \brief Check if a point is on a line.
/// \note Assumes points defining the line aren't the same.
/// \note Be careful to consider the case where the points on the line are very
///       close to each other, but not to the test point. In this case, this
///       function will produce unreliable results because it will be
///       susceptible to roundoff error. If you need to know if three points are
///       colinear, use the gmColinear function instead.
/// \param p1: First point on the line.
/// \param p2: Second point on the line.
/// \param x: x coord of point to test
/// \param y: y coord of point to test
/// \param tol: Tolerance for geometric comparison
/// \return Whether (x,y) is on the line passing through p1 and p2.
//------------------------------------------------------------------------------
bool gmOnLineWithTol(const Pt3d& p1,
                     const Pt3d& p2,
                     const double x,
                     const double y,
                     const double tol)
{
  // compute vector components
  double dx = p2.x - p1.x;
  double dy = p2.y - p1.y;
  double mag = sqrt(sqr(dx) + sqr(dy));
  // check for extremely small segment
  if (mag <= tol)
    return gmEqualPointsXY(p1.x, p1.y, x, y);
  else
  {
    double a = -dy / mag;
    double b = dx / mag;
    double c = -a * p2.x - b * p2.y;
    // compute distance from line to (x,y)
    double d = a * x + b * y + c;
    return fabs(d) <= tol;
  }
} // gmOnLineWithTol
//------------------------------------------------------------------------------
/// \brief Test if a point is on a line segment or on the same side of
///        the segment as another point.
/// \param[in] p1: First endpoint of the segment.
/// \param[in] p2: Second endpoint of the segment.
/// \param[in] oppositepoint: Point on the "in" side of the segment.
/// \param[in] x: x coordinate of point.
/// \param[in] y: y coordinate of point.
/// \return Whether the point is inside or on the line.
//------------------------------------------------------------------------------
bool gmInsideOrOnLine(const Pt3d* p1,
                      const Pt3d* p2,
                      const Pt3d* oppositepoint,
                      const double x,
                      const double y)
{
  return gmInsideOrOnLineWithTol(p1, p2, oppositepoint, x, y, gmXyTol());
} // gmInsideOrOnLine
//------------------------------------------------------------------------------
/// \brief Test if a point is on a line segment or on the same side of
///        the segment as another point.
/// \note ASSERTs in debug if "inpoint" is on the line (within tol).
/// \param[in] p1: First endpoint of the segment.
/// \param[in] p2: Second endpoint of the segment.
/// \param[in] inpoint: Point on the "in" side of the line.
/// \param[in] x: x coordinate of point.
/// \param[in] y: y coordinate of point.
/// \param[in] tol: Tolerance.
/// \param[out] dist: Initialized to how far "outside" the point is. A negative
///                   distance indicates point is on the "in" side by that
///                   distance.
/// \return Whether the point is inside or on the line.
//------------------------------------------------------------------------------
bool gmInsideOrOnLineWithTol(const Pt3d* p1,
                             const Pt3d* p2,
                             const Pt3d* inpoint,
                             const double x,
                             const double y,
                             const double tol,
                             double* dist /*= NULL */)
{
  double dx, dy, a, b, c, mag;
  double d1, d2;
  /* make sure line is not a point */
  dx = p2->x - p1->x;
  dy = p2->y - p1->y;
  mag = sqrt(sqr(dx) + sqr(dy));
  if (mag <= tol)
  {
    return gmEqualPointsXY(p1->x, p1->y, x, y);
  }
  else
  {
    a = -dy / mag;
    b = dx / mag;
    c = -a * p1->x - b * p1->y;
    /* compute distance from line to (x,y) */
    d1 = a * x + b * y + c;
    /* compute distance from line to opposite p */
    d2 = a * inpoint->x + b * inpoint->y + c;
    // if inpoint is really on, we can't make a judgment on the point
    if (Mfabs(d2) <= tol)
    {
      // AKZ - Since "inpoint" is usually the other point in a triangle
      //       this usually indicates a poorly formed triangle.
      //       You should determine how this triangle was formed.
      //      XM_ASSERT(0);
      return false;
    }
    /* return true if point on line */
    if (Mfabs(d1) <= tol)
    {
      if (dist)
      {
        if (d1 * d2 < 0.0)
        {
          *dist = Mfabs(d1);
        }
        else
        {
          *dist = -Mfabs(d1);
        }
      }
      return true;
    }
    /* return true if d1 and d2 have same sign */
    if ((d1 < 0.0) && (d2 < 0.0))
    {
      if (dist)
      {
        *dist = -Mfabs(d1);
      }
      return true;
    }
    else if ((d1 > 0.0) && (d2 > 0.0))
    {
      if (dist)
      {
        *dist = -Mfabs(d1);
      }
      return true;
    }
    else
    {
      if (dist)
      {
        *dist = Mfabs(d1);
      }
      return false;
    }
  }
} // gmInsideOrOnLineWithTol
//------------------------------------------------------------------------------
/// \brief Test if a point is on a line segment or on the same side of
///        the line as another point.
/// \note ASSERTs in debug if "inpoint" is on the line (within tol).
/// \param[in] p1: First endpoint of the segment.
/// \param[in] p2: Second endpoint of the segment.
/// \param[in] inpoint: Point on the "in" side of the line
/// \param[in] x: x coordinate of test point.
/// \param[in] y: y coordinate of test point.
/// \param[in] tol: Tolerance.
/// \return Whether the test point is on the line or on the same side of the
///         line as inpoint.
//------------------------------------------------------------------------------
bool gmInsideOfLineWithTol(const Pt3d& a_vertex1,
                           const Pt3d& a_vertex2,
                           const Pt3d& a_oppositevertex,
                           const double a_x,
                           const double a_y,
                           const double a_tol)
{
  double dx = a_vertex2.x - a_vertex1.x;
  double dy = a_vertex2.y - a_vertex1.y;
  double mag = sqrt(sqr(dx) + sqr(dy));
  if (mag <= a_tol)
  {
    return gmEqualPointsXY(a_vertex1.x, a_vertex1.y, a_x, a_y);
  }
  else
  {
    double a = -dy / mag;
    double b = dx / mag;
    double c = -a * a_vertex1.x - b * a_vertex1.y;
    /* compute the distance from the line to the Point */
    double d1 = a * a_x + b * a_y + c;
    /* compute the distance from the line to the opposite vertex */
    double d2 = a * a_oppositevertex.x + b * a_oppositevertex.y + c;
    if (fabs(d1) <= a_tol)
      return false;
    else if ((d1 < 0.0) && (d2 < 0.0))
      return true;
    else if ((d1 > 0.0) && (d2 > 0.0))
      return true;
    else
      return false;
  }
} // gmInsideOfLineWithTol
//------------------------------------------------------------------------------
/// \brief Returns the squared distance from a point to the nearest point on a
///        line segment.
/// \param p1: First endpoint of the line segment.
/// \param p2: Second endpoint of the line segment.
/// \param q: Point to find distance from.
/// \param thepoint: Initialized to the nearest point on the line segment to q.
/// \return The distance squared from q to the line segment.
//------------------------------------------------------------------------------
double gmNearestPointOnLineSegment2D(const Pt3d& p1, const Pt3d& p2, const Pt3d& q, Pt3d* thepoint)
{
  Pt3d deltap1p2(p2.x - p1.x, p2.y - p1.y, p2.z - p1.z),
    deltaqp1(q.x - p1.x, q.y - p1.y, q.z - p1.z);
  double t(0.0);
  // compute t of line segment perpendicular to line segment and q
  if ((deltap1p2.x * deltap1p2.x + deltap1p2.y * deltap1p2.y) != 0.0)
  {
    t = ((deltap1p2.x * deltaqp1.x + deltap1p2.y * deltaqp1.y) /
         (deltap1p2.x * deltap1p2.x + deltap1p2.y * deltap1p2.y));
  }
  else
  {
    // p1 and p2 are at the same location--return the squared distance
    // between p1 and q
    deltap1p2 = Pt3d(q.x - p1.x, q.y - p1.y, 0.0);
    return (deltap1p2.x * deltap1p2.x + deltap1p2.y * deltap1p2.y);
  }

  if (t >= 1.0)
  {
    // point is outside line segment but closest to p2
    *thepoint = p2;
  }
  else if (t <= 0.0)
  {
    // point is outside line segment but closest to p1
    *thepoint = p1;
  }
  else
  {
    // compute the nearest point on the line
    *thepoint = p1 + t * deltap1p2;
  }
  // compute the distance
  deltap1p2 = Pt3d(q.x - thepoint->x, q.y - thepoint->y, 0.0);
  return (deltap1p2.x * deltap1p2.x + deltap1p2.y * deltap1p2.y);
} // gmNearestPointOnLineSegment2D
//------------------------------------------------------------------------------
/// \brief Find the distance along a segment for the location
///        closest to a point.
/// \param[in] a_pt1: First point of segment.
/// \param[in] a_pt2: Second point of segment.
/// \param[in] a_pt: Test point.
/// \param[in] a_tol: Tolerance.
/// \return Parametric value along the line of the point that is the closest
///         location to the test point.
//------------------------------------------------------------------------------
double gmPtDistanceAlongSegment(const Pt3d& a_pt1,
                                const Pt3d& a_pt2,
                                const Pt3d& a_pt,
                                const double a_tol)
{
  double dx, dy, t;

  dx = a_pt2.x - a_pt1.x;
  dy = a_pt2.y - a_pt1.y;

  if ((dx == 0.0 && dy == 0.0) || (sqrt(dx * dx + dy * dy) <= a_tol))
  {
    t = -1.0;
  }
  else
  {
    t = ((a_pt.x - a_pt1.x) * dx + (a_pt.y - a_pt1.y) * dy) / (dx * dx + dy * dy);
  }

  return t;
} // gmPtDistanceAlongSegment
//------------------------------------------------------------------------------
/// \brief Find the closest point on a segment to another point.
/// \param[in] a_pt1: First endpoint of segment.
/// \param[in] a_pt2: Second endpoint of segment.
/// \param[in] a_pt: Test point.
/// \param[out] a_newpt: Initialized to the point on the segment that is
///                      closest to the test point.
/// \param[in] a_tol: Tolerance.
/// \return Parametric value along the line a_pt1, a_pt2 that is the location
///         of a_newpt.
//------------------------------------------------------------------------------
double gmFindClosestPtOnSegment(const Pt3d& a_pt1,
                                const Pt3d& a_pt2,
                                const Pt3d& a_pt,
                                Pt3d& a_newpt,
                                const double a_tol)
{
  double t = gmPtDistanceAlongSegment(a_pt1, a_pt2, a_pt, a_tol);
  if (t < 0.0)
  {
    a_newpt.x = a_pt1.x;
    a_newpt.y = a_pt1.y;
  }
  else if (t > 1.0)
  {
    a_newpt.x = a_pt2.x;
    a_newpt.y = a_pt2.y;
  }
  else
  {
    double dx = a_pt2.x - a_pt1.x;
    double dy = a_pt2.y - a_pt1.y;
    a_newpt.x = a_pt1.x + dx * t;
    a_newpt.y = a_pt1.y + dy * t;
  }
  return t;
} // gmFindClosestPtOnSegment
//------------------------------------------------------------------------------
/// \brief Find the closest point on a segment to another point.
/// \param pt1: First endpoint of segment.
/// \param pt2: Second endpoint of segment.
/// \param pt: Point used to find closest point on the segment.
/// \param[in] dx: pt2->x - pt1->x  (passed in for potential efficiency).
/// \param[in] dy: pt2->y - pt1->y  (passed in for potential efficiency).
/// \param[in] mag2: Length of segment squared (leave squared for efficiency).
/// \param[out] newpt: Initialized to the point on the segment closest to pt.
/// \return The 2D distance from pt to newpt.
//------------------------------------------------------------------------------
double gmFindClosestPtOnSegment2D(const Pt3d& pt1,
  const Pt3d& pt2,
  const Pt3d& pt,
  double dx,
  double dy,
  double mag2,
  Pt3d* newpt)
{
  double t;

  // compute t of line segment perpendicular to line segment and pt
  t = ((pt.x - pt1.x) * dx + (pt.y - pt1.y) * dy) / mag2;

  if (t <= 0.0)
  { /* point is outside line segment but closest to pt1 */
    newpt->x = pt1.x;
    newpt->y = pt1.y;
    newpt->z = pt1.z;
  }
  else if (t >= 1.0)
  { /* point is outside line segment but closest to pt2 */
    newpt->x = pt2.x;
    newpt->y = pt2.y;
    newpt->z = pt2.z;
  }
  else
  { /* compute the nearest point on the line */
    newpt->x = pt1.x + t * dx;
    newpt->y = pt1.y + t * dy;
    newpt->z = pt1.z;
  }

  return sqrt(sqr(newpt->x - pt.x) + sqr(newpt->y - pt.y));

} // gmFindClosestPtOnSegment2D
//------------------------------------------------------------------------------
/// \brief Find the closest point on a segment to another point.
/// \param pt1: First endpoint of segment.
/// \param pt2: Second endpoint of segment.
/// \param pt: Point used to find closest point on the segment.
/// \param newpt: Initialized to the point on the segment (pt1, pt2) that is
///               closest to pt.
/// \param a_tol: Tolerance.
/// \return The 3D distance from pt to newpt.
//------------------------------------------------------------------------------
double gmFindClosestPtOnSegment3D(const Pt3d& pt1, const Pt3d& pt2, const Pt3d& pt, Pt3d* newpt)
{
  double dx, dy, dz, mag2, t;

  dx = pt2.x - pt1.x;
  dy = pt2.y - pt1.y;
  dz = pt2.z - pt1.z;
  mag2 = dx * dx + dy * dy + dz * dz;

  /* compute t of line segment perpendicular to line segment and pt */
  t = ((pt.x - pt1.x) * dx + (pt.y - pt1.y) * dy + (pt.z - pt1.z) * dz) / mag2;

  if (t <= 0.0)
  { /* point is outside line segment but closest to pt1 */
    newpt->x = pt1.x;
    newpt->y = pt1.y;
    newpt->z = pt1.z;
  }
  else if (t >= 1.0)
  { /* point is outside line segment but closest to pt2 */
    newpt->x = pt2.x;
    newpt->y = pt2.y;
    newpt->z = pt2.z;
  }
  else
  { /* compute the nearest point on the line */
    newpt->x = pt1.x + t * dx;
    newpt->y = pt1.y + t * dy;
    newpt->z = pt1.z + t * dz;
  }

  return sqrt(sqr(newpt->x - pt.x) + sqr(newpt->y - pt.y) + sqr(newpt->z - pt.z));

} // gmFindClosestPtOnSegment3D
//------------------------------------------------------------------------------
/// \brief  Given minimum and maximum extents, compute a tolerance for the xy
///         plane to be used with geometric functions.
/// \param a_mn: Minimum.
/// \param a_mx: Maximum.
/// \return Tolerance.
//------------------------------------------------------------------------------
double gmComputeXyTol(const Pt3d& a_mn, const Pt3d& a_mx)
{
  double d = gmXyDistance(a_mn, a_mx);
  double const kFactor = 1e-9;
  double xytol = d * kFactor;
  if (xytol < kFactor)
  {
    xytol = kFactor;
  }
  return xytol;
} // gmComputeXyTol
//------------------------------------------------------------------------------
/// \brief Get or set global xy tolerance for float operations.
/// \note Always sets the first time it is called.
/// \param a_set: True to set, false to get.
/// \param a_value: The value if setting.
/// \return XY tolerance.
//------------------------------------------------------------------------------
double gmXyTol(bool a_set /*false*/, double a_value /*1e-9*/)
{
  static double xytol = a_value;
  if (a_set)
    xytol = a_value;
  return xytol;
} // gmXyTol
//------------------------------------------------------------------------------
/// \brief  Get or set global z tolerance for float operations.
/// \note Always sets the first time it is called.
/// \param a_set: True to set, false to get.
/// \param a_value: The value if setting.
/// \return Z tolerance.
//------------------------------------------------------------------------------
double gmZTol(bool a_set, double a_value)
{
  static double ztol = a_value;
  if (a_set)
    ztol = a_value;
  return ztol;
} // gmZTol
//------------------------------------------------------------------------------
/// \brief Check whether a triangle is wrapped counter clockwise.
/// \param[in] vtx0: Triangle's first vertex.
/// \param[in] vtx1: Triangle's first vertex.
/// \param[in] vtx2: Triangle's first vertex.
/// \return Whether vertex order is counter clockwise.
//------------------------------------------------------------------------------
bool gmCounterClockwiseTri(const Pt3d& vtx0, const Pt3d& vtx1, const Pt3d& vtx2)
{
  double triarea1 = trArea(vtx0, vtx1, vtx2);
  return (triarea1 > 0.0);
} // gmCounterClockwiseTri
//------------------------------------------------------------------------------
/// \brief Determine if a quadrilateral is wrapped clockwise or
///        counter clockwise.
/// \param da1: First vertex of the quadrilateral.
/// \param db1: Second vertex of the quadrilateral.
/// \param da2: Third vertex of the quadrilateral.
/// \param db2: Fourth vertex of the quadrilateral.
/// \return Whether the quad is wrapped counter clockwise.
//------------------------------------------------------------------------------
bool gmCounterClockwiseQuad(const Pt3d& da1, const Pt3d& db1, const Pt3d& da2, const Pt3d& db2)
{
  double quadrea1 = (da1.x * db1.y + db1.x * da2.y + da2.x * db2.y + db2.x * da1.y - da1.y * db1.x -
                     db1.y * da2.x - da2.y * db2.x - db2.y * da1.x);
  bool ccwWrap = (quadrea1 > 0.0);

  return ccwWrap;
} // gmCounterClockwiseQuad
//------------------------------------------------------------------------------
/// \brief Reorder a clockwise polygon's vertices to be counter clockwise. No
///        effect on polygons that are already counter clockwise.
/// \pre The last point must not be the same as the first. The polygon's
///      vertices must be in either clockwise or counter clockwise order.
/// \author MMB copied this function from myiMakePolygonCounterclockwise 9-20-95
///         to make it external an more general.
/// \param pts: An array of points defining the polygon's vertices.
/// \param numpts: The number of points in the array.
//------------------------------------------------------------------------------
void gmMakePolygonClockwise(Pt3d* pts, int numpts)
{
  long i, halfcount;
  Pt3d temppt;

  /* See if the polygon was input in CW order by checking the sign
  on the polygon area. (CCW = positive area) */

  if (gmPolygonArea(pts, numpts) > 0)
  {
    /* reverse the polygon */
    halfcount = numpts / 2;
    for (i = 0; i < halfcount; i++)
    {
      temppt = pts[i];
      pts[i] = pts[numpts - 1 - i];
      pts[numpts - 1 - i] = temppt;
    }
  }
} // gmMakePolygonClockwise
//------------------------------------------------------------------------------
/// \brief Reorder a clockwise polygon's vertices to be counter clockwise. No
///        effect on polygons that are already counter clockwise.
/// \pre The last point must not be the same as the first. The polygon's
///      vertices must be in either clockwise or counter clockwise order.
/// \author MMB copied this function from myiMakePolygonCounterclockwise 9-20-95
///         to make it external an more general.
/// \param pts: An array of points defining the polygon's vertices.
/// \param numpts: The number of points in the array.
//------------------------------------------------------------------------------
void gmMakePolygonClockwise(Pt2i* pts, int numpts)
{
  long i, halfcount;
  Pt2i temppt;

  /* See if the polygon was input in CCW order by checking the sign
  on the polygon area. (CW = negative area) */

  if (gmPolygonArea(pts, numpts) > 0)
  {
    /* reverse the polygon */
    halfcount = numpts / 2;
    for (i = 0; i < halfcount; i++)
    {
      temppt = pts[i];
      pts[i] = pts[numpts - 1 - i];
      pts[numpts - 1 - i] = temppt;
    }
  }
} // gmMakePolygonClockwise
//------------------------------------------------------------------------------
/// \brief Reorder a clockwise polygon's vertices to be counter clockwise. No
///        effect on polygons that are already counter clockwise.
/// \pre The last point must not be the same as the first. The polygon's
///      vertices must be in either clockwise or counter clockwise order.
/// \author MMB copied this function from myiMakePolygonCounterclockwise 9-20-95
///         to make it external an more general.
/// \param pts: An array of points defining the polygon's vertices.
/// \param numpts: The number of points in the array.
//------------------------------------------------------------------------------
void gmMakePolygonCounterclockwise(Pt2i* pts, int numpts)
{
  long i, halfcount;
  Pt2i temppt;

  /* See if the polygon was input in CCW order by checking the sign
  on the polygon area. (CCW = positive area) */

  if (gmPolygonArea(pts, numpts) < 0)
  {
    /* reverse the polygon */
    halfcount = numpts / 2;
    for (i = 0; i < halfcount; i++)
    {
      temppt.x = pts[i].x;
      temppt.y = pts[i].y;
      pts[i].x = pts[numpts - 1 - i].x;
      pts[i].y = pts[numpts - 1 - i].y;
      pts[numpts - 1 - i].x = temppt.x;
      pts[numpts - 1 - i].y = temppt.y;
    }
  }
} // gmMakePolygonCounterclockwise
//------------------------------------------------------------------------------
/// \brief Reorder a clockwise polygon's vertices to be counter clockwise. No
///        effect on polygons that are already counter clockwise.
/// \pre The last point must not be the same as the first. The polygon's
///      vertices must be in either clockwise or counter clockwise order.
/// \author MMB copied this function from myiMakePolygonCounterclockwise 9-20-95
///         to make it external an more general.
/// \param pts: An array of points defining the polygon's vertices.
/// \param numpts: The number of points in the array.
//------------------------------------------------------------------------------
void gmMakePolygonCounterclockwise(Pt3d* pts, int numpts)
{
  long i, halfcount;
  Pt3d temppt;

  /* See if the polygon was input in CCW order by checking the sign
  on the polygon area. (CCW = positive area) */

  if (gmPolygonArea(pts, numpts) < 0)
  {
    /* reverse the polygon */
    halfcount = numpts / 2;
    for (i = 0; i < halfcount; i++)
    {
      temppt.x = pts[i].x;
      temppt.y = pts[i].y;
      temppt.z = pts[i].z;
      pts[i].x = pts[numpts - 1 - i].x;
      pts[i].y = pts[numpts - 1 - i].y;
      pts[i].z = pts[numpts - 1 - i].z;
      pts[numpts - 1 - i].x = temppt.x;
      pts[numpts - 1 - i].y = temppt.y;
      pts[numpts - 1 - i].z = temppt.z;
    }
  }
} // gmMakePolygonCounterclockwise
//------------------------------------------------------------------------------
/// \brief Determine how to sort a vector of points such that they are in
///        counter-clockwise order relative to their centroid.
/// \param[in] a_pts: Array of points.
/// \param[out] a_ccwOrder: Initialized to a vector mapping indices to points.
/// \param[in] a_startindex: The index of the point that should start the
///                          polygon.
//------------------------------------------------------------------------------
void gmOrderPointsCounterclockwise(const VecPt3d& a_pts, VecInt& a_ccwOrder, int a_startindex)
{
  int numnodes = (int)a_pts.size();

  // compute centroid of points
  Pt2d center;
  double sumx = 0.0;
  double sumy = 0.0;
  for (int i = 0; i < numnodes; i++)
  {
    sumx += a_pts[i].x;
    sumy += a_pts[i].y;
  }

  center.x = sumx / numnodes;
  center.y = sumy / numnodes;

  // compute polar angle for each node about the centroid of the element
  // along with the original point index
  std::vector<std::pair<float, int> > angleIndex(numnodes);
  for (int i = 0; i < numnodes; i++)
  {
    float angle = (float)(atan2(a_pts[i].y - center.y, a_pts[i].x - center.x));
    angleIndex[i] = std::pair<float, int>(angle, i);
  }

  std::stable_sort(angleIndex.begin(), angleIndex.end());

  // find where starting index is in sorted array
  auto startIter = angleIndex.begin();
  while (startIter != angleIndex.end() && startIter->second != a_startindex)
  {
    ++startIter;
  }
  if (startIter == angleIndex.end())
    startIter = angleIndex.begin();

  // assign the result preserving the order with a_startindex the first node
  a_ccwOrder.resize(numnodes, 0);
  size_t j = 0;
  for (auto iter = startIter; iter != angleIndex.end(); ++iter)
  {
    a_ccwOrder[j] = iter->second;
    j++;
  }
  for (auto iter = angleIndex.begin(); iter != startIter; ++iter)
  {
    a_ccwOrder[j] = iter->second;
    j++;
  }
} // gmOrderPointsCounterclockwise
//------------------------------------------------------------------------------
/// \brief Sort a vector of points such that they are in counter-clockwise order
///        relative to their centroid.
/// \param[in,out] a_pts: Vector of points. Sorted by this function.
//------------------------------------------------------------------------------
void gmOrderPointsCounterclockwise(VecPt3d& a_pts)
{
  if (a_pts.empty())
    return;

  VecInt ccwOrder;
  VecPt3d pts(a_pts);
  gmOrderPointsCounterclockwise(pts, ccwOrder);
  for (size_t i = 0; i < ccwOrder.size(); ++i)
  {
    a_pts[i] = pts[ccwOrder[i]];
  }
} // gmOrderPointsCounterclockwise
//------------------------------------------------------------------------------
/// \brief Compute the normal to the plane defined by three points in the plane.
/// \note Normal will not been normalized.
/// \pre The points are assumed to be ordered CCW and non-colinear.
/// \param point1: The first point.
/// \param point2: The second point.
/// \param point3: The third point.
/// \return A normal vector for the plane.
//------------------------------------------------------------------------------
Pt3f gmComputePlaneNormal(const Pt3f& point1, const Pt3f& point2, const Pt3f& point3)
{
  Pt3f vec1, vec2, normal;

  vec1.x = point3.x - point2.x;
  vec1.y = point3.y - point2.y;
  vec1.z = point3.z - point2.z;
  vec2.x = point1.x - point2.x;
  vec2.y = point1.y - point2.y;
  vec2.z = point1.z - point2.z;
  normal.x = vec1.y * vec2.z - vec1.z * vec2.y;
  normal.y = vec1.z * vec2.x - vec1.x * vec2.z;
  normal.z = vec1.x * vec2.y - vec1.y * vec2.x;
  return normal;
} // gmComputePlaneNormal
//------------------------------------------------------------------------------
/// \brief Compute the normal to the plane defined by three points in the plane.
/// \note Normal will not been normalized.
/// \pre The points are assumed to be ordered CCW and non-colinear.
/// \param point1: The first point.
/// \param point2: The second point.
/// \param point3: The third point.
/// \return A normal vector for the plane.
//------------------------------------------------------------------------------
Pt3d gmComputePlaneNormal(const Pt3d& point1, const Pt3d& point2, const Pt3d& point3)
{
  Pt3d vec1, vec2, normal;

  vec1.x = point3.x - point2.x;
  vec1.y = point3.y - point2.y;
  vec1.z = point3.z - point2.z;
  vec2.x = point1.x - point2.x;
  vec2.y = point1.y - point2.y;
  vec2.z = point1.z - point2.z;
  normal.x = vec1.y * vec2.z - vec1.z * vec2.y;
  normal.y = vec1.z * vec2.x - vec1.x * vec2.z;
  normal.z = vec1.x * vec2.y - vec1.y * vec2.x;
  return normal;
} // gmComputePlaneNormal
//------------------------------------------------------------------------------
/// \brief Compute the normal to the plane defined by three points in the plane.
/// \note Normal will not been normalized.
/// \pre The points are assumed to be ordered CCW and non-colinear.
/// \param point1: The first point.
/// \param point2: The second point.
/// \param point3: The third point.
/// \return A normal vector for the plane.
//------------------------------------------------------------------------------
Pt3d gmComputePlaneNormal(const Pt4d& point1, const Pt4d& point2, const Pt4d& point3)
{
  Pt3d vec1, vec2, normal;

  vec1.x = point3.x - point2.x;
  vec1.y = point3.y - point2.y;
  vec1.z = point3.z - point2.z;
  vec2.x = point1.x - point2.x;
  vec2.y = point1.y - point2.y;
  vec2.z = point1.z - point2.z;
  normal.x = vec1.y * vec2.z - vec1.z * vec2.y;
  normal.y = vec1.z * vec2.x - vec1.x * vec2.z;
  normal.z = vec1.x * vec2.y - vec1.y * vec2.x;
  return normal;
} // gmComputePlaneNormal
//------------------------------------------------------------------------------
/// \brief Compute the normal to the plane defined by three points in the plane.
/// \note Normal will not been normalized.
/// \pre The points are assumed to be ordered CCW and non-colinear.
/// \param pt1: The first point.
/// \param pt2: The second point.
/// \param pt3: The third point.
/// \return A normal vector for the plane.
//------------------------------------------------------------------------------
Pt3f gmComputeUnitPlaneNormal(const Pt3f& pt1, const Pt3f& pt2, const Pt3f& pt3)
{
  Pt3f normal;

  normal = gmComputePlaneNormal(pt1, pt2, pt3);
  gmNormalizeXYZ(normal, &normal);
  return (normal);
} // gmComputeUnitPlaneNormal
//------------------------------------------------------------------------------
/// \brief Compute the normal to the plane defined by three points in the plane.
/// \note Normal will not been normalized.
/// \pre The points are assumed to be ordered CCW and non-colinear.
/// \param pt1: The first point.
/// \param pt2: The second point.
/// \param pt3: The third point.
/// \return A normal vector for the plane.
//------------------------------------------------------------------------------
Pt3d gmComputeUnitPlaneNormal(const Pt3d& pt1, const Pt3d& pt2, const Pt3d& pt3)
{
  Pt3d normal;

  normal = gmComputePlaneNormal(pt1, pt2, pt3);
  gmNormalizeXYZ(normal, &normal);
  return (normal);
} // gmComputeUnitPlaneNormal
//------------------------------------------------------------------------------
/// \brief Calculate the plane coefficients for a triangle.
/// \note Plane ==> ax+by+cz+d=0
/// \param p1: First vertex of the triangle.
/// \param p2: Second vertex of the triangle.
/// \param p3: Third vertex of the triangle.
/// \param a: Initialized to the x coefficient of the plane equation.
/// \param b: Initialized to the y coefficient of the plane equation.
/// \param c: Initialized to the z coefficient of the plane equation.
/// \param d: Initialized to the d constant of the plane equation.
//------------------------------------------------------------------------------
void gmCalculatePlaneCoeffs(const Pt3d& point1,
                            const Pt3d& point2,
                            const Pt3d& point3,
                            double* a,
                            double* b,
                            double* c,
                            double* d)
{
  gmCalculatePlaneCoeffs(&point1, &point2, &point3, a, b, c, d);
} // gmCalculatePlaneCoeffs
//------------------------------------------------------------------------------
/// \brief Calculate the plane coefficients for a triangle.
/// \note Plane ==> ax+by+cz+d=0
/// \param p1: First vertex of the triangle.
/// \param p2: Second vertex of the triangle.
/// \param p3: Third vertex of the triangle.
/// \param a: Initialized to the x coefficient of the plane equation.
/// \param b: Initialized to the y coefficient of the plane equation.
/// \param c: Initialized to the z coefficient of the plane equation.
/// \param d: Initialized to the d constant of the plane equation.
//------------------------------------------------------------------------------
void gmCalculatePlaneCoefficients(const Pt3d* p1,
                                  const Pt3d* p2,
                                  const Pt3d* p3,
                                  double* a,
                                  double* b,
                                  double* c,
                                  double* d)
{
  gmCalculatePlaneCoeffs(p1, p2, p3, a, b, c, d);
} // gmCalculatePlaneCoefficients
//------------------------------------------------------------------------------
/// \brief Calculate the plane coefficients for a triangle.
/// \note Plane ==> ax+by+cz+d=0
/// \param p1: First vertex of the triangle.
/// \param p2: Second vertex of the triangle.
/// \param p3: Third vertex of the triangle.
/// \param a: Initialized to the x coefficient of the plane equation.
/// \param b: Initialized to the y coefficient of the plane equation.
/// \param c: Initialized to the z coefficient of the plane equation.
/// \param d: Initialized to the d constant of the plane equation.
//------------------------------------------------------------------------------
void gmCalculatePlaneCoeffs(const Pt3d* p1,
                            const Pt3d* p2,
                            const Pt3d* p3,
                            double* a,
                            double* b,
                            double* c,
                            double* d,
                            double tol /*=XM_ZERO_TOL*/)
{
  double x1(p1->x), y1(p1->y), z1(p1->z);
  double x2(p2->x), y2(p2->y), z2(p2->z);
  double x3(p3->x), y3(p3->y), z3(p3->z);
  double dx23(x2 - x3), dx31(x3 - x1), dx12(x1 - x2);
  double dy23(y2 - y3), dy31(y3 - y1), dy12(y1 - y2);
  double dz23(z2 - z3), dz31(z3 - z1), dz12(z1 - z2);
  *a = (y1 * dz23 + y2 * dz31 + y3 * dz12);
  *b = (z1 * dx23 + z2 * dx31 + z3 * dx12);
  *c = (x1 * dy23 + x2 * dy31 + x3 * dy12);
  // normalize if c is small
  if (*c < tol)
  {
    double mag(sqrt((*a) * (*a) + (*b) * (*b) + (*c) * (*c)));
    // JDH BUGFIX #394 BEG
    if (mag < tol)
    {
      // compute tight tol
      double tolscale(Mmax3(fabs(dy23), fabs(dy31), fabs(dy12)));
      tolscale = Mmax(tolscale, Mmax3(fabs(dx23), fabs(dx31), fabs(dx12)));
      tolscale = Mmax(tolscale, Mmax3(fabs(dz23), fabs(dz31), fabs(dz12)));
      if (mag < tolscale * tol)
      {
        *a = *b = *c = *d = 0.0;
        return;
      }
    }
    // JDH BUGFIX #394 END
    *a /= mag;
    *b /= mag;
    *c /= mag;
  }
  *d = -(*a) * x1 - (*b) * y1 - (*c) * z1;
} // gmCalculatePlaneCoeffs
//------------------------------------------------------------------------------
/// \brief Calculates the plane coefficients for a triangle.
///        Given points, calculate coefficents for plane (ax+by+cz+d=0).
/// \param[in] p1: First point.
/// \param[in] p2: Second point.
/// \param[in] p3: Third point.
/// \param[out] a: Coefficient a.
/// \param[out] b: Coefficient b.
/// \param[out] c: Coefficient c.
/// \param[out] d: Coefficient d.
//------------------------------------------------------------------------------
void gmCalculateNormalizedPlaneCoefficients(const Pt3d& p1,
                                            const Pt3d& p2,
                                            const Pt3d& p3,
                                            double* a,
                                            double* b,
                                            double* c,
                                            double* d)
{
  // call the other version
  gmCalculateNormalizedPlaneCoefficients(&p1, &p2, &p3, a, b, c, d);
} // gmCalculateNormalizedPlaneCoefficients
//------------------------------------------------------------------------------
/// \brief Calculates the plane coefficients for a triangle.
///        Given points, calculate coefficents for plane (ax+by+cz+d=0).
/// \param[in] p1: First point.
/// \param[in] p2: Second point.
/// \param[in] p3: Third point.
/// \param[out] a: Coefficient a.
/// \param[out] b: Coefficient b.
/// \param[out] c: Coefficient c.
/// \param[out] d: Coefficient d.
//------------------------------------------------------------------------------
void gmCalculateNormalizedPlaneCoefficients(const Pt3d* p1,
                                            const Pt3d* p2,
                                            const Pt3d* p3,
                                            double* a,
                                            double* b,
                                            double* c,
                                            double* d)
{
  double x1(p1->x), y1(p1->y), z1(p1->z);
  double x2(p2->x), y2(p2->y), z2(p2->z);
  double x3(p3->x), y3(p3->y), z3(p3->z);
  *a = (y1 * (z2 - z3) + y2 * (z3 - z1) + y3 * (z1 - z2));
  *b = (z1 * (x2 - x3) + z2 * (x3 - x1) + z3 * (x1 - x2));
  *c = (x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2));
  double mag(sqrt((*a) * (*a) + (*b) * (*b) + (*c) * (*c)));
  *a /= mag;
  *b /= mag;
  *c /= mag;
  *d = -(*a) * x1 - (*b) * y1 - (*c) * z1;
} // gmCalculateNormalizedPlaneCoefficients
//------------------------------------------------------------------------------
/// \brief Finds three points on a plane given the coefficients of its equation.
/// \note plane equation: ax+by+cz+d=0
/// \param p1: Initialized to the first point in the plane.
/// \param p2: Initialized to the second point in the plane.
/// \param p3: Initialized to the third point in the plane.
/// \param a: The a coefficient in the equation of the plane.
/// \param b: The b coefficient in the equation of the plane.
/// \param c: The c coefficient in the equation of the plane.
/// \param d: The d constant in the equation of the plane.
//------------------------------------------------------------------------------
void gmCalculatePointsFromPlane(Pt3d* p1,
                                Pt3d* p2,
                                Pt3d* p3,
                                double a,
                                double b,
                                double c,
                                double d)
{
  double vx, vy, vz;
  Pt3d delta1, delta2;

  if (a >= b && a >= c)
  {
    p1->y = p1->z = 1.0;
    p1->x = (b + c + d) / a;
    p1->x = -p1->x;
  }
  else if (b >= c)
  {
    p1->x = p1->z = 1.0;
    p1->y = (a + c + d) / b;
    p1->y = -p1->y;
  }
  else
  {
    p1->x = p1->y = 1.0;
    p1->z = (a + b + d) / c;
    p1->z = -p1->z;
  }

  vx = vy = vz = 0.0;
  if (a <= b && a <= c)
    vx = 1.0;
  else if (b <= c)
    vy = 1.0;
  else
    vz = 1.0;

  delta1.x = (b * vz) - (c * vy);
  delta1.y = (c * vx) - (a * vz);
  delta1.z = (a * vy) - (b * vx);
  p2->x = p1->x + delta1.x;
  p2->y = p1->y + delta1.y;
  p2->z = p1->z + delta1.z;

  delta2.x = (b * delta1.z) - (c * delta1.y);
  delta2.y = (c * delta1.x) - (a * delta1.z);
  delta2.z = (a * delta1.y) - (b * delta1.x);
  p3->x = p1->x + delta2.x;
  p3->y = p1->y + delta2.y;
  p3->z = p1->z + delta2.z;

} // gmCalculatePointsFromPlane
//------------------------------------------------------------------------------
/// \brief Calculates the z value from an x and y value and the plane
///        coefficients.
/// \param x: x coordinate.
/// \param y: y coordinate.
/// \param a: a coefficient in the plane's equation.
/// \param b: b coefficient in the plane's equation.
/// \param c: c coefficient in the plane's equation.
/// \param d: d constant in the plane's equation.
/// \return z, such that ax+by+cz+d=0.
//------------------------------------------------------------------------------
double gmCalculateZFromPlaneCoefficients(double x, double y, double a, double b, double c, double d)
{
  return -(a / c) * x - (b / c) * y - d / c;
} // gmCalculateZFromPlaneCoefficients
//------------------------------------------------------------------------------
/// \brief Compute the midpoint of two points.
/// \param The first point.
/// \param The second point.
/// \return The midpoint.
//------------------------------------------------------------------------------
Pt3d gmInterpolateMpoint3(const Pt3d& p1, const Pt3d& p2)
{
  Pt3d thepoint;
  thepoint.x = (p1.x + p2.x) / 2;
  thepoint.y = (p1.y + p2.y) / 2;
  thepoint.z = (p1.z + p2.z) / 2;
  return thepoint;
} // gmInterpolateMpoint3
//------------------------------------------------------------------------------
/// \brief Fit a 1d spline through an array of values.
/// \param in: An array of values.
/// \param nin: The number of values.
/// \param nout: The number of points in the spline.
/// \param bias: Bias.
/// \return: An array of values for the spline.
//------------------------------------------------------------------------------
double* gmDistributeValues(const double* in, int nin, int nout, double bias)
{
#define NUMSPLINEINTERVALS 20 /* # if pts/segment of the spline */
  int i, j, i0, i1;
  double s, s1, s_squ, s1_squ, ds, dl, frac, suml, tempbias;
  double v1, v2, tprime, d, x, tmp1, tmp2;
  double *din, *dout, *out;
  /* Get memory for operation */
  din = (double*)malloc((nin) * sizeof(double));
  out = (double*)malloc((nout) * sizeof(double));
  dout = (double*)malloc((nout) * sizeof(double));
  /* CHECK FOR XM_SUCCESS */
  if (din == nullptr || out == nullptr || dout == nullptr)
  {
    if (din)
      free(din);
    if (out)
      free(out);
    if (dout)
      free(dout);
    return nullptr;
  }
  /* put input nodes into spline points */
  out[0] = in[0];              /* 1st point is the same */
  out[nout - 1] = in[nin - 1]; /* Last point is the same */
  if (nout > 2)
  {
    /* compute interior spline tangents */
    for (i = 1; i < nin - 1; ++i)
      din[i] = (in[i + 1] - in[i - 1]) * 0.5;
    /* end spline tangents */
    if (nin > 2)
    {
      din[0] = 2.0 * (in[1] - in[0]) - din[1];
      din[i] = 2.0 * (in[i] - in[i - 1]) - din[i - 1];
    }
    else
      din[0] = din[1] = in[1] - in[0];
    /* Compute total length of spline */
    ds = 1.0 / NUMSPLINEINTERVALS;
    suml = 0.0;
    for (i0 = 0, i1 = 1; i1 < nin; ++i0, ++i1)
    {
      s = ds;
      s_squ = s * s;
      s1 = s - 1.0;
      s1_squ = s1 * s1;
      v1 = in[i0];
      for (j = 0; j < NUMSPLINEINTERVALS; ++j)
      {
        v2 = (2 * (s + 0.5) * s1_squ) * in[i0] + (s * s1_squ) * din[i0] -
             (2 * s_squ * (s - 1.5)) * in[i1] + (s_squ * s1) * din[i1];
        suml += v2 - v1;
        s += ds;
        s_squ = s * s;
        s1 = s - 1.0;
        s1_squ = s1 * s1;
        v1 = v2;
      }
    }
    /* calculate the bias dout */
    if (bias > 1.0)
      tempbias = 1 / bias;
    else
      tempbias = bias;
    s = pow(10.0, (log10(tempbias) / (nout - 2)));
    x = d = 1.0;
    for (i0 = 1; i0 < nout - 1; ++i0)
    {
      x *= s;
      d += x;
    }
    dout[0] = 0.0;
    tprime = dout[1] = 1 / d;
    for (i0 = 2; i0 < nout - 1; ++i0)
    {
      tprime *= s;
      dout[i0] = dout[i0 - 1] + tprime;
    }
    dout[nout - 1] = 1.0;
    /* invert & swap if elems getting larger */
    if (bias > 1.0)
    {
      for (i0 = 0, i1 = nout - 1; i0 <= i1; ++i0, --i1)
      {
        tmp1 = 1.0 - dout[i0];
        tmp2 = 1.0 - dout[i1];
        dout[i0] = tmp2;
        dout[i1] = tmp1;
      }
    }
    /* scale up to length */
    for (i0 = 1; i0 < nout; ++i0)
      dout[i0] *= suml;
    /* Compute new point coords */
    i = 1;
    suml = 0.0;
    for (i0 = 0, i1 = 1; i1 < nin && i < nout - 1; ++i0, ++i1)
    {
      s = ds;
      s_squ = s * s;
      s1 = s - 1.0;
      s1_squ = s1 * s1;
      v1 = in[i0];
      for (j = 0; j < NUMSPLINEINTERVALS && i < nout - 1; ++j)
      {
        v2 = (2 * (s + 0.5) * s1_squ) * in[i0] + (s * s1_squ) * din[i0] -
             (2 * s_squ * (s - 1.5)) * in[i1] + (s_squ * s1) * din[i1];
        dl = v2 - v1;
        while ((suml + dl >= dout[i]) && (i < nout - 1))
        {
          frac = (dout[i] - suml) / dl;
          out[i] = v1 + frac * (v2 - v1);
          ++i;
        }
        suml += dl;
        s += ds;
        s_squ = s * s;
        s1 = s - 1.0;
        s1_squ = s1 * s1;
        v1 = v2;
      }
    }
  }
  free(dout);
  free(din);
  return out;
} // gmDistributeValues
//------------------------------------------------------------------------------
/// \brief Subdivide a line segment into intervals.
/// \note Return value will be malloced but not freed here.
/// \param endpt1: The first endpoint.
/// \param endpt2: The second endpoint.
/// \param numdiv: The number of divisions.
/// \return An array of points of size numdiv, where each point is on the line
///         segment and equidistint from each other.
//------------------------------------------------------------------------------
Pt3d* gmLinearSubdivideLine(const Pt3d& endpt1, const Pt3d& endpt2, int numdiv)
{
  bool firsttime = true;
  int i;
  Pt3d* middlepts;
  double xspacing, yspacing, zspacing;

  middlepts = (Pt3d*)malloc((numdiv - 1) * sizeof(Pt3d));
  if (middlepts == nullptr)
  {
    // gnNullMemoryErrorMessage("gmLinearSubdivideLine");
    return nullptr;
  }

  xspacing = (endpt2.x - endpt1.x) / numdiv;
  yspacing = (endpt2.y - endpt1.y) / numdiv;
  zspacing = (endpt2.z - endpt1.z) / numdiv;
  for (i = 0; i < numdiv - 1; i++)
  {
    if (firsttime)
    {
      middlepts[i].x = endpt1.x + xspacing;
      middlepts[i].y = endpt1.y + yspacing;
      middlepts[i].z = endpt1.z + zspacing;
      firsttime = false;
    }
    else
    {
      middlepts[i].x = middlepts[i - 1].x + xspacing;
      middlepts[i].y = middlepts[i - 1].y + yspacing;
      middlepts[i].z = middlepts[i - 1].z + zspacing;
    }
  }
  return (middlepts);
} // gmLinearSubdivideLine

//------------------------------------------------------------------------------
/// \brief Take all values in col1 and extrapolate them across to col2 to create
///        newcol.
/// \note All memory should already have been allocated. The newcol will have
///       the same number of points as col1 (np1).
/// \param col1: First column of values.
/// \param col2: Second column of values.
/// \param newcol: Column of new values.
/// \param pcnt: Initialized to the size of newcol.
/// \param np1: Number of values in col1.
/// \param np2: Number of values in col2.
/// \param tol: Tolerance for geometric comparison.
//------------------------------------------------------------------------------
void gmExtrapolatePointsWithTol(const Pt3d* col1,
                                const Pt3d* col2,
                                Pt3d* newcol,
                                double* pcnt,
                                int np1,
                                int np2,
                                double tol)
{
  int i, j;
  double dist1, dist2, len1, len2, delta, pcnt1, pcnt2;

  /* get length of the two columns */
  for (len1 = 0.0, i = 1; i < np1; i++)
    len1 += Mdist(col1[i].x, col1[i].y, col1[i - 1].x, col1[i - 1].y);
  for (len2 = 0.0, i = 1; i < np2; i++)
    len2 += Mdist(col2[i].x, col2[i].y, col2[i - 1].x, col2[i - 1].y);
  /* set first and last points of newcol */
  newcol[0] = col2[0];
  pcnt[0] = 0.0;
  newcol[np1 - 1] = col2[np2 - 1];
  pcnt[np1 - 1] = 1.0;
  /* loop through the middle points */
  for (dist1 = dist2 = 0.0, i = j = 1; i < np1 - 1; i++)
  {
    delta = Mdist(col1[i].x, col1[i].y, col1[i - 1].x, col1[i - 1].y);
    /* see if two points are the same */
    if (fabs(delta) < tol)
    {
      newcol[i] = newcol[i - 1];
      pcnt[i] = pcnt[i - 1];
    }
    /* otherwise, do the extrapolation */
    else
    {
      dist1 += delta;
      /* find percent of length reached on col1 */
      pcnt1 = pcnt[i] = dist1 / len1;
      /* find where this percent is located on col2.
         this is based on the following two equations:
         1.  (dist2 + val) / (len2) = pcnt1
             -> solve this for "val"
         2.  pcnt2 = (val) / (delta)
             where pcnt2 is the percentage from col2[j-1]
             to col2[j] to get the correct point */

      delta = Mdist(col2[j].x, col2[j].y, col2[j - 1].x, col2[j - 1].y);
      while (((dist2 + delta) / len2) < pcnt1)
      {
        dist2 += delta;
        j++;
        delta = Mdist(col2[j].x, col2[j].y, col2[j - 1].x, col2[j - 1].y);
      }
      pcnt2 = ((len2 * pcnt1) - (dist2)) / delta; /*delta should never be zero*/
                                                  /* now put the new point in newcol */
      newcol[i].x = col2[j].x * pcnt2 + col2[j - 1].x * (1.0 - pcnt2);
      newcol[i].y = col2[j].y * pcnt2 + col2[j - 1].y * (1.0 - pcnt2);
      newcol[i].z = col2[j].z * pcnt2 + col2[j - 1].z * (1.0 - pcnt2);
    }
  }
} // gmExtrapolatePointsWithTol
//------------------------------------------------------------------------------
/// \brief Normalize a 3D vector.
/// \param vect The vector to scale.
/// \param norm Initialized to the scaled vector.
//------------------------------------------------------------------------------
void gmNormalizeXYZ(const Pt3d& vect, Pt3d* norm)
{
  register double magvec;
  register double x, y, z;

  x = vect.x;
  y = vect.y;
  z = vect.z;
  if ((magvec = sqrt(x * x + y * y + z * z)) < 1e-9)
  {
    norm->x = 0.0;
    norm->y = 0.0;
    norm->z = 0.0;
    return;
  }
  magvec = 1.0 / magvec;
  norm->x = x * magvec;
  norm->y = y * magvec;
  norm->z = z * magvec;
} // gmNormalizeXYZ
//------------------------------------------------------------------------------
/// \brief Normalize a 3D vector.
/// \param vect The vector to scale.
/// \param norm Initialized to the scaled vector.
//------------------------------------------------------------------------------
void gmNormalizeXYZ(const Pt3f& vect, Pt3f* norm)
{
  register float magvec;
  register float x, y, z;

  x = vect.x;
  y = vect.y;
  z = vect.z;
  if ((magvec = sqrt(x * x + y * y + z * z)) < 1e-9)
  {
    norm->x = 0.0;
    norm->y = 0.0;
    norm->z = 0.0;
    return;
  }
  magvec = (float)(1.0 / magvec);
  norm->x = x * magvec;
  norm->y = y * magvec;
  norm->z = z * magvec;
} // gmNormalizeXYZ
//------------------------------------------------------------------------------
/// \brief Normalize a 3D vector.
/// \param vect The vector to scale.
/// \param norm Initialized to the scaled vector.
/// \return The magnitude of vect if it isn't zero, or -1.0 otherwise.
//------------------------------------------------------------------------------
double gmNormalizeXYZWithMag(const Pt3d& vect, Pt3d* norm)
{
  register double magsq, magvec;
  register double x, y, z;

  x = vect.x;
  y = vect.y;
  z = vect.z;
  magsq = x * x + y * y + z * z;
  if ((magvec = sqrt(magsq)) < 1e-9)
  {
    norm->x = 0.0;
    norm->y = 0.0;
    norm->z = 0.0;
    return -1.0;
  }
  magvec = 1.0 / magvec;
  norm->x = x * magvec;
  norm->y = y * magvec;
  norm->z = z * magvec;
  return (sqrt(magsq));
} // gmNormalizeXYZWithMag
//------------------------------------------------------------------------------
/// \brief Normalize a 3D vector.
/// \param vect The vector to scale.
/// \param norm Initialized to the scaled vector.
/// \param magvec Initialized to the magnitude of vect if the magnitude is
///        nonzero, else -1.0.
/// \return Whether the magnitude was nonzero.
//------------------------------------------------------------------------------
int gmNormalizeXYWithMag(const Pt2d& vect, Pt2d* norm, double* magvec)
{
  double magsq;
  double x, y;
  double asmallnum = 0.00001;

  if (*magvec == -1.0)
    asmallnum = 0.0001;
  x = vect.x;
  y = vect.y;
  magsq = x * x + y * y;
  if (((*magvec) = sqrt(magsq)) < asmallnum)
  {
    norm->x = 0.0;
    norm->y = 0.0;
    return XM_FAILURE;
  }
  x /= (*magvec);
  y /= (*magvec);
  norm->x = x;
  norm->y = y;
  return XM_SUCCESS;
} // gmNormalizeXYWithMag
//------------------------------------------------------------------------------
/// \brief Compute 2d planview projection of area of polygon.
/// \note If points are in CCW order, the area will be positive. If in CW order,
///       it will be negative. The magnitude will be correct in either case.
/// \param pts: Vertices defining the polygon. Do not repeat the last point.
/// \param npoints: Number of points in the array.
/// \return Area of the polygon.
//------------------------------------------------------------------------------
double gmPolygonArea(const Pt2i* pts, size_t npoints)
{
  size_t id;
  double area = 0.0;

  if (npoints < 3)
    return area;

  // This implementation translates the polygon so the first point is at
  // the origin. This reduces roundoff error due to large coordinates
  // and reduces the number of computations because the first and last
  // computations in the loop would be 0.
  VecInt x, y;
  int x0 = pts[0].x;
  int y0 = pts[0].y;
  for (id = 1; id < npoints; id++)
  {
    x.push_back((pts[id].x - x0));
    y.push_back((pts[id].y - y0));
  }
  for (id = 0; id < npoints - 2; id++)
  {
    area += (x[id] * y[id + 1]);
    area -= (y[id] * x[id + 1]);
  }
  area /= 2.0;
  return (area);

} // gmPolygonArea
//------------------------------------------------------------------------------
/// \brief Compute 2d planview projection of area of polygon.
/// \note If points are in CCW order, the area will be positive. If in CW order,
///       it will be negative. The magnitude will be correct in either case.
/// \param pts: Vertices defining the polygon. Do not repeat the last vertex.
/// \param npoints: Number of points in the array.
/// \return Area of the polygon.
//------------------------------------------------------------------------------
double gmPolygonArea(const Pt3d* pts, size_t npoints)
{
  if (npoints < 3)
    return 0.0;
  size_t id;
  double area = 0.0;

  // This implementation translates the polygon so the first point is at
  // the origin. This reduces roundoff error due to large coordinates
  // and reduces the number of computations because the first and last
  // computations in the loop would be 0.
  VecDbl x, y;
  double x0 = pts[0].x;
  double y0 = pts[0].y;
  for (id = 1; id < npoints; id++)
  {
    x.push_back((pts[id].x - x0));
    y.push_back((pts[id].y - y0));
  }
  for (id = 0; id < npoints - 2; id++)
  {
    area += (x[id] * y[id + 1]);
    area -= (y[id] * x[id + 1]);
  }
  area /= 2.0;

  return (area);
} // gmPolygonArea
//------------------------------------------------------------------------------
/// \brief Caluculate the volume of a tetrahedron.
/// \note The vertices are assumed to be noncoincident.
/// \note Equivalent to gmTetrahedronVolume2, but accepts different
///       vertex types.
/// \param point1: First vertex of the tetrahedron.
/// \param point2: Second vertex of the tetrahedron.
/// \param point3: Third vertex of the tetrahedron.
/// \param point4: Fourth vertex of the tetrahedron.
/// \param error: Always initialized to false.
/// \return The volume of the tetrahedron.
//------------------------------------------------------------------------------
double gmTetrahedronVolumeMpoint3(const Pt3d& point1,
                                  const Pt3d& point2,
                                  const Pt3d& point3,
                                  const Pt3d& point4,
                                  bool* error)
{
  // Implementation uses the following formula:
  //                          |  1.0  x1  y1  z1  |
  //         volume = (1/6) * |  1.0  x2  y2  z2  |
  //                          |  1.0  x3  y3  z3  |
  //                          |  1.0  x4  y4  z4  |
  double C41, C42, C43, C44;
  double determinant;

  *error = false;

  /* calculate the cofactors of the 4x4 matrix */
  C41 = point1.x * point2.y * point3.z + point1.y * point2.z * point3.x +
        point1.z * point2.x * point3.y -
        (point1.z * point2.y * point3.x + point1.y * point2.x * point3.z +
         point1.x * point2.z * point3.y);
  C42 = 1.0 * point2.y * point3.z + point1.y * point2.z * 1.0 + point1.z * 1.0 * point3.y -
        (point1.z * point2.y * 1.0 + point1.y * 1.0 * point3.z + 1.0 * point2.z * point3.y);
  C43 = point2.x * 1.0 * point3.z + 1.0 * point2.z * point1.x + point1.z * point3.x * 1.0 -
        (point1.z * 1.0 * point2.x + 1.0 * point3.x * point2.z + point1.x * point3.z * 1.0);
  C44 = point1.x * point2.y * 1.0 + point1.y * 1.0 * point3.x + 1.0 * point2.x * point3.y -
        (1.0 * point2.y * point3.x + point1.y * point2.x * 1.0 + point1.x * 1.0 * point3.y);

  determinant = -C41 + (point4.x) * C42 - (point4.y) * C43 + (point4.z) * C44;
  return determinant / 6.0;
} // gmTetrahedronVolumeMpoint3
//------------------------------------------------------------------------------
/// \brief Project a 3d vector to the specified plane.
/// \param vector: The vector to project.
/// \param plane: 0 for YZ plane, 1 for XZ plane, 2 for XY plane.
/// \return Projected 2d vector.
//------------------------------------------------------------------------------
Pt3d gmProjectVectorToPlane(const Pt3d& vector, int plane)
{
  Pt3d vector2D;

  switch (plane)
  {
  case 0:
    vector2D.x = vector.y;
    vector2D.y = vector.z;
    break;
  case 1:
    vector2D.x = vector.x;
    vector2D.y = vector.z;
    break;
  case 2:
    vector2D.x = vector.x;
    vector2D.y = vector.y;
    break;
  }
  vector2D.z = 0.0;
  return vector2D;

} // gmProjectVectorToPlane
//------------------------------------------------------------------------------
/// \brief Find the best XYZ plane to project a triangle onto.
/// \pre Assumes v0,v1,v2 are in CCW order.
/// \note The largest component of the normal to the plane is the winner.
/// \param v0: First vertex of the triangle.
/// \param v1: Second vertex of the triangle.
/// \param v2: Third vertex of the triangle.
/// \return 0 for yz plane, 1 for xz plane, 2 for xy plane.
//------------------------------------------------------------------------------
int gmProjectTriangleToPln(const Pt3d& v0, const Pt3d& v1, const Pt3d& v2)
{
  Pt3d normal;
  int plane;
  double abx, aby, abz;

  normal = gmComputePlaneNormal(v0, v1, v2);

  abx = fabs(normal.x);
  aby = fabs(normal.y);
  abz = fabs(normal.z);
  if (abx >= aby && abx >= abz)
    plane = 0;
  else if (aby >= abx && aby >= abz)
    plane = 1;
  else
    plane = 2;
  return plane;
} // gmProjectTriangleToPln
//------------------------------------------------------------------------------
/// \brief Test if three nodes are collinear.
/// \note Result is insensitive to the order of the nodes.
/// \param p1: The first point.
/// \param p2: The second point.
/// \param p3: The third point.
/// \return Whether the nodes are colinear.
//------------------------------------------------------------------------------
bool gmColinear(const Pt3d* p1, const Pt3d* p2, const Pt3d* p3)
{
  return gmColinearWithTol(*p1, *p2, *p3, gmXyTol());
} // gmColinear
//------------------------------------------------------------------------------
/// \brief Check whether three points are colinear.
/// \param[in] p1: First point.
/// \param[in] p2: Second point.
/// \param[in] p3: Third point.
/// \param[in] tol: Tolerance for geometric comparisons.
/// \return Whether the points are colinear.
//------------------------------------------------------------------------------
bool gmColinearWithTol(const Pt3d& p1, const Pt3d& p2, const Pt3d& p3, const double tol)
{
  if (gmOnLineWithTol(p1, p2, p3.x, p3.y, tol))
    return true;
  else if (gmOnLineWithTol(p2, p3, p1.x, p1.y, tol))
    return true;
  else if (gmOnLineWithTol(p3, p1, p2.x, p2.y, tol))
    return true;
  else
    return false;
} // gmColinearWithTol
//------------------------------------------------------------------------------
/// \brief Test if four vertices are coplanar.
/// \note Result is insensitive to the order of the vertices.
/// \param v1: First vertex.
/// \param v2: Second vertex.
/// \param v3: Third vertex.
/// \param v4: Fourth vertex.
/// \param tolerance: Tolerance for geometric comparisons.
/// \return Whether the vertices are coplanar.
//------------------------------------------------------------------------------
bool gmCoplanarWithTol(const Pt3d& v1,
                       const Pt3d& v2,
                       const Pt3d& v3,
                       const Pt3d& v4,
                       double tolerance)
{
  Pt3d oppositepoint;
  oppositepoint.x = oppositepoint.y = oppositepoint.z = 0.0;
  /* gmClassifyPointFromPlane needs the parameter, oppositepoint.  However,
     it is not used to determine if a point is on the plane.  Hence, it is
     set simply to 0 */

  if (gmClassifyPointFromPlane(v1, v2, v3, oppositepoint, v4.x, v4.y, v4.z, tolerance) == 0)
    return true;
  else if (gmClassifyPointFromPlane(v1, v2, v4, oppositepoint, v3.x, v3.y, v3.z, tolerance) == 0)
    return true;
  else if (gmClassifyPointFromPlane(v1, v3, v4, oppositepoint, v2.x, v2.y, v2.z, tolerance) == 0)
    return true;
  else if (gmClassifyPointFromPlane(v2, v3, v4, oppositepoint, v1.x, v1.y, v1.z, tolerance) == 0)
    return true;
  else
    return false;
} // gmCoplanarWithTol
//------------------------------------------------------------------------------
/// \brief Compute center & radius squared for circumcircle of triangle defined
///        by three points.
/// \note This function may fail if the triangle's area is 0.
/// \param pt1: First point of the triangle.
/// \param pt2: Second point of the triangle.
/// \param pt3: Third point of the triangle.
/// \param xc: x coordinate of the center of the circle.
/// \param yc: y coordinate of the center of the circle.
/// \param r2: Radius squared of the circle.
/// \return Whether the function succeeded.
//------------------------------------------------------------------------------
bool gmCircumcircle(const Pt3d* pt1,
                    const Pt3d* pt2,
                    const Pt3d* pt3,
                    double* xc,
                    double* yc,
                    double* r2)
{
  return gmCircumcircleWithTol(pt1, pt2, pt3, xc, yc, r2, gmXyTol());
} // gmCircumcircle
//------------------------------------------------------------------------------
/// \brief Compute center & radius squared for circumcircle of triangle
///        defined by the three points.
/// \note  May fail if triangle has zero area.
/// \param pt1: First vertex of the triangle.
/// \param pt2: Second vertex of the triangle.
/// \param pt3: Third vertex of the triangle.
/// \param xc: Initialized to the circumcenter x coord.
/// \param yc: Initialized to the circumcenter y coord.
/// \param r2: Initialized to the radius squared of circumcircle.
/// \param tol: Tolerance for geometric comparison.
/// \return Whether the operation succeeded.
//------------------------------------------------------------------------------
bool gmCircumcircleWithTol(const Pt3d* pt1,
                           const Pt3d* pt2,
                           const Pt3d* pt3,
                           double* xc,
                           double* yc,
                           double* r2,
                           double tol)
{
  bool ok = true;
  double det11, det12, det13, det21, det22, det23;
  double determinate;
  /* compute these */
  det11 = pt1->x - pt2->x;
  det12 = pt1->y - pt2->y;
  det13 = det11 * (pt1->x + pt2->x) / 2.0 + det12 * (pt1->y + pt2->y) / 2.0;

  det21 = pt3->x - pt2->x;
  det22 = pt3->y - pt2->y;
  det23 = det21 * (pt3->x + pt2->x) / 2.0 + det22 * (pt3->y + pt2->y) / 2.0;
  /* compute determinant */
  determinate = det11 * det22 - det12 * det21;
  /* zero determinate indicates collinear pts */
  if (fabs(determinate) < tol)
  {
    ok = false;
    determinate = tol;
  }
  *xc = (det13 * det22 - det23 * det12) / determinate;
  *yc = (det11 * det23 - det21 * det13) / determinate;
  *r2 = sqr(pt1->x - *xc) + sqr(pt1->y - *yc);
  return ok;
} // gmCircumcircleWithTol
//------------------------------------------------------------------------------
/// \brief Converts an array of doubles to a VecPt3d with Z coordinates all 0.
/// \note Useful in testing to create a VecPt3d from a C array of xy pairs.
/// \param[in] a_array: Array of xy pairs ([x][y][x][y]...). Must have even
///                     length.
/// \param[in] a_size: Array size.
/// \return Vector of Pt3d.
//------------------------------------------------------------------------------
VecPt3d gmArrayToVecPt3d(double* a_array, int a_size)
{
  VecPt3d v(a_size / 2);
  for (int i = 0; i < a_size; i += 2)
  {
    v[i / 2].x = a_array[i];
    v[i / 2].y = a_array[i + 1];
  }
  return v;
} // gmArrayToVecPt3d
//------------------------------------------------------------------------------
/// \brief Test if all three values are within a tolerance of each other.
/// \param z1: The first value.
/// \param z1: The second value.
/// \param z1: The third value.
/// \param tol: Tolerance for comparison.
/// \return Whether all three values are within a tolerance of each other.
//------------------------------------------------------------------------------
int gmThreeEqualZSWithTol(double z1, double z2, double z3, double tol)
{
  double maxz, minz;
  maxz = Mmax3(z1, z2, z3);
  minz = Mmin3(z1, z2, z3);
  if (fabs(maxz - minz) < tol)
    return true;
  return false;
} // gmThreeEqualZSWithTol
//------------------------------------------------------------------------------
/// \brief Convert a vector of Pt3d to three vectors of doubles.
/// \note May silently fail in release mode with one or more vectors
///       over-allocated if insufficient memory.
/// \param a_pt: Vector of points to convert.
/// \param a_x: Initialized to the x coordinates of the points in a_pt.
/// \param a_y: Initialized to the y coordinates of the points in a_pt.
/// \param a_z: Initialized to the z coordinates of the points in a_pt.
//------------------------------------------------------------------------------
void gmSplitPtVector(const VecPt3d& a_pt, VecDbl& a_x, VecDbl& a_y, VecDbl& a_z)
{
  try
  {
    a_x.resize(a_pt.size(), 0.0);
    a_y.resize(a_pt.size(), 0.0);
    a_z.resize(a_pt.size(), 0.0);
    for (int i = 0; i < (int)a_pt.size(); ++i)
    {
      a_x.at(i) = a_pt.at(i).x;
      a_y.at(i) = a_pt.at(i).y;
      a_z.at(i) = a_pt.at(i).z;
    }
  }
  catch (std::exception&)
  {
    XM_ASSERT(false);
  }
} // gmSplitPtVector
//------------------------------------------------------------------------------
/// \brief Removes adjacent points that are duplicates in 2D.
/// \param a_pts: Vector of points to remove adjacent duplicates from.
/// \param a_tol: Ignored. Implicitely uses gmXyTol() instead.
//------------------------------------------------------------------------------
void gmRemoveAdjacentDuplicatePoints2D(VecPt3d& a_pts, double /*a_tol*/)
{
  for (VecPt3d::iterator itr = a_pts.begin(); itr != a_pts.end();)
  {
    VecPt3d::iterator itrNext = itr;
    ++itrNext;
    if (itrNext != a_pts.end() &&
      gmEqualPointsXY(itr->x, itr->y, itrNext->x, itrNext->y, gmXyTol()))
    {
      itr = a_pts.erase(itr);
    }
    else
    {
      ++itr;
    }
  }
} // gmRemoveAdjacentDuplicatePoints2D
//------------------------------------------------------------------------------
/// \brief Check if 2 boxes overlap in 2D.
/// \param[in] a_b1Min Min x,y of first box.
/// \param[in] a_b1Max Max x,y of first box.
/// \param[in] a_b2Min Min x,y of second box.
/// \param[in] a_b2Max Max x,y of second box.
/// \return Whether the point is on or on the box.
//------------------------------------------------------------------------------
bool gmBoxesOverlap2d(const Pt3d& a_b1Min,
                      const Pt3d& a_b1Max,
                      const Pt3d& a_b2Min,
                      const Pt3d& a_b2Max)
{
  if (a_b1Max.x < a_b2Min.x)
    return false;
  if (a_b1Min.x > a_b2Max.x)
    return false;
  if (a_b1Max.y < a_b2Min.y)
    return false;
  if (a_b1Min.y > a_b2Max.y)
    return false;
  return true;
} // gmBoxesOverlap2d
//------------------------------------------------------------------------------
/// \brief Check if 2 boxes overlap in 3d.
/// \param[in] a_b1Min Min x,y of first box.
/// \param[in] a_b1Max Max x,y of first box.
/// \param[in] a_b2Min Min x,y of second box.
/// \param[in] a_b2Max Max x,y of second box.
/// \return 1 if they overlap, else 0.
//------------------------------------------------------------------------------
int gmBoxOverlap(const Pt3d& min1, const Pt3d& max1, const Pt3d& min2, const Pt3d& max2)
{
  int overlap = 0;
  if (min1.x < max2.x)
    if (min2.x < max1.x)
      if (min1.y < max2.y)
        if (min2.y < max1.y)
          if (min1.z < max2.z)
            if (min2.z < max1.z)
              overlap = 1;
  return overlap;
} // gmBoxOverlap
//------------------------------------------------------------------------------
/// \brief Compute the line equation coefficients of a line that passes through
///        two points.
/// \pre The distance between the two points must be greater than the tolerance.
/// \param pt1: A point on the line.
/// \param pt2: Another point on the line.
/// \param a: Initialized to the a coefficient in the line equation.
/// \param b: Initialized to the b coefficient in the line equation.
/// \param c: Initialized to the c constant in the line equation.
/// \param tol: Tolerance for geometric comparison.
/// \return Whether the precondition was met.
//------------------------------------------------------------------------------
bool gmComputeLineEquation(const Pt3d& pt1,
                           const Pt3d& pt2,
                           double& a,
                           double& b,
                           double& c,
                           double tol)
{
  double a1, b1, mag;
  /* see if the (x,y) is on infinite line */
  a1 = pt2.x - pt1.x;
  b1 = pt2.y - pt1.y;
  mag = sqrt(a1 * a1 + b1 * b1);
  /* handle case of line segment with length < tol*/
  if (mag <= tol)
  {
    return false;
  }
  /* compute line equation */
  a = -b1 / mag;
  b = a1 / mag;
  c = -a * pt1.x - b * pt1.y;
  return true;
} // gmComputeLineEquation
//------------------------------------------------------------------------------
/// \brief Compute the centroid of a set of points.
/// \note The centroid this function computes is not the same as the centroid
///       of a polygon.
/// \param[in] a_points: A vector of points. Must not be empty. Order is
///                      unimportant.
/// \return The centroid.
//------------------------------------------------------------------------------
Pt3d gmComputeCentroid(const VecPt3d& a_points)
{
  Pt3d centroid;
  size_t size = a_points.size();
  for (size_t i = 0; i < size; ++i)
    centroid += a_points[i];
  return (centroid / (double)size);
} // gmComputeCentroid
//------------------------------------------------------------------------------
/// \brief Compute the plan view centroid of a non-self-intersecting polygon.
/// \param[in] pts: A vector of vertices defining the polygon.
/// \return The centroid.
//------------------------------------------------------------------------------
Pt3d gmComputePolygonCentroid(const VecPt3d& pts)
{
  Pt3d centroid;
  if (pts.empty())
    return centroid;
  // get offset to use in calculation below to fix precision issues
  double xMax = XM_DBL_LOWEST, yMax = XM_DBL_LOWEST, xMin = XM_DBL_HIGHEST, yMin = XM_DBL_HIGHEST;
  size_t i = 0;
  for (i = 0; i < pts.size(); ++i)
  {
    double x = pts[i].x;
    double y = pts[i].y;
    xMax = (x > xMax) ? x : xMax;
    yMax = (y > yMax) ? y : yMax;
    xMin = (x < xMin) ? x : xMin;
    yMin = (y < yMin) ? y : yMin;
  }
  double xOffset = (xMax + xMin) / 2.0;
  double yOffset = (yMax + yMin) / 2.0;
  // For all vertices except last
  double signedArea = 0.0;
  for (i = 0; i < pts.size() - 1; ++i)
  {
    double x0 = pts[i].x - xOffset;
    double y0 = pts[i].y - yOffset;
    double x1 = pts[i + 1].x - xOffset;
    double y1 = pts[i + 1].y - yOffset;
    double a = x0 * y1 - x1 * y0;
    signedArea += a;
    centroid.x += (x0 + x1) * a;
    centroid.y += (y0 + y1) * a;
  }
  // Do last vertex
  double x0 = pts[i].x - xOffset;
  double y0 = pts[i].y - yOffset;
  double x1 = pts[0].x - xOffset;
  double y1 = pts[0].y - yOffset;
  double a = x0 * y1 - x1 * y0;
  signedArea += a;
  centroid.x += (x0 + x1) * a;
  centroid.y += (y0 + y1) * a;
  signedArea *= 0.5;
  centroid.x /= (6.0 * signedArea);
  centroid.y /= (6.0 * signedArea);
  centroid.x += xOffset;
  centroid.y += yOffset;
  return centroid;
} // gmComputePolygonCentroid
//------------------------------------------------------------------------------
/// \brief Find the z value halfway between the max and min z.
/// \note  Different from the average z in that it ignores all but the min and
///        max z when finding the midpoint.
/// \param a_points: A vector of points.
/// \return Middle z value.
//------------------------------------------------------------------------------
double gmMiddleZ(const VecPt3d& a_points)
{
  double zmin = XM_DBL_HIGHEST;
  double zmax = XM_DBL_LOWEST;
  for (size_t i = 0; i < a_points.size(); ++i)
  {
    double z = a_points[i].z;
    zmin = std::min(zmin, z);
    zmax = std::max(zmax, z);
  }
  return (zmin + zmax) / 2.0;
} // gmMiddleZ
//------------------------------------------------------------------------------
/// \brief Determine which nodes to use to split a quadrilateral
///        element into a triangular element.
/// \note da1-da2 and db1-db2 should be the quad's diagonals.
/// \param da1: First vertex of the quadrilateral.
/// \param db1: Second vertex of the quadrilateral.
/// \param da2: Third vertex of the quadrilateral.
/// \param db2: Fourth vertex of the quadrilateral.
/// \return True to split into da1-db1-da2 and da1-da2-db2.
///         False to split into da1-db1-db2 and db1-da2-db2.
//------------------------------------------------------------------------------
bool gmQuadToTriAreaCheck(const Pt3d& da1, const Pt3d& db1, const Pt3d& da2, const Pt3d& db2)
{
  bool usea = false;
  bool tri1 = false, tri2 = false;
  // square of the diagonals
  double da = sqr(da1.x - da2.x) + sqr(da1.y - da2.y);
  double db = sqr(db1.x - db2.x) + sqr(db1.y - db2.y);

  if (da < db)
  {
    tri1 = gmCounterClockwiseTri(da1, db1, da2);
    tri2 = gmCounterClockwiseTri(da1, da2, db2);
    usea = tri1 && tri2;
  }
  else
  {
    tri1 = gmCounterClockwiseTri(da1, db1, db2);
    tri2 = gmCounterClockwiseTri(db2, db1, da2);
    usea = !tri1 || !tri2;
  }
  return usea;
}
//------------------------------------------------------------------------------
/// \brief Calculate convex hull using Monotone chain aka Andrew's algorithm.
/// \param[in] a_pts: The input points.
/// \param[out] a_hull: The convex hull polygon. First point is NOT repeated.
/// \param[in] a_includeOn: Whether to include points on the hull's
///                         line segment.
//------------------------------------------------------------------------------
void gmGetConvexHull(const VecPt3d& a_pts, VecPt3d& a_hull, bool a_includeOn /*=false*/)
{
  a_hull.clear();

  // copy points with only x/y values
  VecPt3d points(a_pts);
  for (size_t i = 0; i < points.size(); ++i)
    points[i].z = 0.0;

  // sort and remove duplicates
  std::sort(points.begin(), points.end());
  auto end = std::unique(points.begin(), points.end());
  size_t size = end - points.begin();
  points.resize(size);

  if (size < 3)
  {
    a_hull = points;
    return;
  }

  // build lower hull
  VecPt3d lower;
  for (auto p = points.begin(); p != points.end(); ++p)
  {
    size_t lsize = lower.size();
    while (lsize > 1 && isRightTurn(gmTurn(lower[lsize - 2], lower[lsize - 1], *p), !a_includeOn))
    {
      lower.pop_back();
      lsize = lower.size();
    }
    lower.push_back(*p);
  }
  lower.pop_back();

  // build upper hull
  VecPt3d upper;
  for (auto p = points.rbegin(); p != points.rend(); ++p)
  {
    size_t usize = upper.size();
    while (usize > 1 && isRightTurn(gmTurn(upper[usize - 2], upper[usize - 1], *p), !a_includeOn))
    {
      upper.pop_back();
      usize = upper.size();
    }
    upper.push_back(*p);
  }
  upper.pop_back();

  a_hull = lower;
  a_hull.insert(a_hull.end(), upper.begin(), upper.end());
} // gmGetConvexHull
//------------------------------------------------------------------------------
/// \brief Calculate the celerity at a node.
/// \note Taken from some FORTRAN code.
/// \param period: Period.
/// \param depth: Depth.
/// \param gravity: Gravity.
//------------------------------------------------------------------------------
double gmCalculateCelerity(double period, double depth, double gravity)
{
  double w, fx, gx, vx, wx, fpr;
  double wavelength, celerity, k;

  if (depth < 0.5)
    depth = .5;

  w = 2.0 * XM_PI / period;
  gx = w * w * depth / gravity;
  vx = 1.0;
  do
  {
    wx = tanh(vx);
    fx = (vx * wx) - gx;
    fpr = vx * (1.0 - wx * wx) + wx;
    vx = vx - (fx / fpr);
  } while (fabs(fx) > 0.1e-3);
  wavelength = 2.0 * XM_PI * depth / vx;
  k = vx / depth;
  celerity = sqrt((gravity / k) * tanh(vx));

  return (celerity);
} // gmCalculateCelerity
//------------------------------------------------------------------------------
/// \brief Calculate the transition wavelength at a depth.
/// \note Taken from some FORTRAN code.
/// \param period: Period.
/// \param depth: Depth.
/// \param gravity: Gravity.
/// \return The wavelength.
//------------------------------------------------------------------------------
double gmCalculateWavelength(double period, double depth, double gravity)
{
  double w, fx, gx, vx, wx, fpr;
  double wavelength;

  if (depth < 0.0)
    depth = .5;

  w = 2.0 * XM_PI / period;
  gx = w * w * depth / gravity;
  vx = 1.0;
  do
  {
    wx = tanh(vx);
    fx = (vx * wx) - gx;
    fpr = vx * (1.0 - wx * wx) + wx;
    vx = vx - (fx / fpr);
  } while (fabs(fx) > 0.1e-3);
  wavelength = 2.0 * XM_PI * depth / vx;

  return (wavelength);
} // gmCalculateWavelength



} // namespace xms

//----- Tests ------------------------------------------------------------------

#ifdef CXX_TEST

//#include <RunTest.h>

#include <boost/timer/timer.hpp>

#include <xmscore/testing/TestTools.h>
#include <xmsgrid/geometry/GmPolygon.t.h>
#include <xmsgrid/geometry/geoms.t.h>
#include <xmscore/misc/XmLog.h>

//----- Namespace declaration --------------------------------------------------

// namespace xms {

////////////////////////////////////////////////////////////////////////////////
/// \class GmPointInPolyUnitTests
/// \brief Used for speed tests of various point in poly functions / classes.
///
/// Uses non-virtual interface pattern. You must override TestPoint and MaxTime.
////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
/// \brief constructor
//------------------------------------------------------------------------------
GmPointInPolyUnitTests::GmPointInPolyUnitTests()
: m_outPoly()
, m_inPoly()
, m_timer()
, m_count(0)
, m_status(XM_NODATA)
{
} // GmPointInPolyUnitTests::GmPointInPolyUnitTests
//------------------------------------------------------------------------------
/// \brief Run the test. This is the main function to call.
//------------------------------------------------------------------------------
void GmPointInPolyUnitTests::DoTest()
{
  Setup();
  CheckPoints();
  GetResults();
} // GmPointInPolyUnitTests::DoTest
//------------------------------------------------------------------------------
/// \brief Setup the polygons
//------------------------------------------------------------------------------
void GmPointInPolyUnitTests::Setup()
{
  GmPolygonUnitTests::SetUpPolyWithHole(m_outPoly, m_inPoly);
} // GmPointInPolyUnitTests::Setup
//------------------------------------------------------------------------------
/// \brief Check a lot of points to see if they are in the polys.
//------------------------------------------------------------------------------
void GmPointInPolyUnitTests::CheckPoints()
{
  xms::Pt3d pt;
  const double xStart = -5;
  const double xEnd = 55;
  const double yStart = 35;
  const double yEnd = -5;
  const double kIncrement = 1e-1;
  m_timer.start();
  for (double y = yStart; y >= yEnd; y -= kIncrement)
  {
    for (double x = xStart; x <= xEnd; x += kIncrement)
    {
      pt.Set(x, y, 0);
      CheckPoint(pt);
      ++m_count;
    }
  }
} // GmPointInPolyUnitTests::CheckPoints
//--------------------------------------------------------------------------
/// \brief Get the timer results and do some assertions.
//--------------------------------------------------------------------------
void GmPointInPolyUnitTests::GetResults()
{
  // Using elapsed user + system time, not wall clock time, so this should be
  // similar on other computers. "For a production process, the wall clock
  // time may be what is most important. To study the efficiency of code,
  // total CPU time (user + system) is often a much better measure."
  // http://www.boost.org/doc/libs/1_59_0/libs/timer/doc/cpu_timers.html

  // Get elapsed user + system time, not wall clock time
  boost::timer::cpu_times const elapsed_times(m_timer.elapsed());
  boost::timer::nanosecond_type time = elapsed_times.system + elapsed_times.user;

  // convert nanoseconds to seconds
  const double NANO_PER_SEC = 1e9;
  double seconds = time / NANO_PER_SEC;

  // Make sure we checked a bunch of points
  int const kCountTotal = 240000;
  TS_ASSERT_EQUALS(m_count, kCountTotal);

  // For speed tests we don't check correctness of every point. We just
  // make sure m_status has changed.
  TS_ASSERT(m_status != XM_NODATA);

  // Check that the time is below a max time and write the time to the log
  // so we can check this in release.
  TS_ASSERT(seconds < MaxTime());
  XM_LOG(xmlog::debug, std::to_string((long long)seconds));
} // GmPointInPolyUnitTests::GetResults

////////////////////////////////////////////////////////////////////////////////
/// For testing point in polygon speed
class GmPointInPolyTester_gmPointInPolygon2D : public GmPointInPolyUnitTests
{
public:
  //----------------------------------------------------------------------------
  /// \brief Constructor
  //----------------------------------------------------------------------------
  GmPointInPolyTester_gmPointInPolygon2D()
  : GmPointInPolyUnitTests()
  {
  }

private:
  //----------------------------------------------------------------------------
  /// \brief Determine if a point is in or out.
  /// \param a_pt: The point to check.
  //----------------------------------------------------------------------------
  virtual void CheckPoint(const xms::Pt3d& a_pt) override
  {
    /// \brief   Determines whether (a_x, a_y) is inside=1, on=0, or
    ///          outside=-1 the polygon defined by the given vertices.
    int outer = xms::gmPointInPolygon2D(&m_outPoly[0], m_outPoly.size(), a_pt);
    int inner = xms::gmPointInPolygon2D(&m_inPoly[0], m_inPoly.size(), a_pt);
    if (outer == 1 && inner == -1)
    {
      m_status = 1; // in
    }
    else if (outer == -1 || inner == 1)
    {
      m_status = 0; // completely out or in the hole
    }
    else if (outer == 0 || inner == 0)
    {
      m_status = 2; // on the outer poly or the inner poly
    }
  } // CheckPoint
  //----------------------------------------------------------------------------
  /// \brief Maximum time test should take.
  /// \return The maximum time.
  //----------------------------------------------------------------------------
  virtual double MaxTime() override
  {
    // It takes .09 - .17 seconds on my machine in release.
    return 0.5;
    // Hopefully big enough for the tests to pass on all machines but give us
    // an error if it starts going a lot slower for some reason.
  } // MaxTime

private:
  /// prevent copy/assign compiler generated functions
  XM_DISALLOW_COPY_AND_ASSIGN(GmPointInPolyTester_gmPointInPolygon2D);
}; // GmPointInPolyTester_gmPointInPolygon2D

////////////////////////////////////////////////////////////////////////////////
/// \class GeomsXmsngUnitTests
/// \brief Tests for functions in geoms.cpp
////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
/// \brief
/// \return CxxTest::TestGroup reference.
//------------------------------------------------------------------------------
// virtual
// const CxxTest::TestGroup& GeomsXmsngUnitTests::group ()
//{
//  return *CxxTest::TestGroup::GetGroup(CxxTest::TG_INTERMEDIATE);
//} // GeomsXmsngUnitTests::group
//------------------------------------------------------------------------------
/// \brief
/// \verbatim
// 10 *------*
//    |      |
//    |      *
//    |      |
//  0 *------*
//    0     10
/// \endverbatim
//------------------------------------------------------------------------------
void GeomsXmsngUnitTests::test_gmComputeCentroid()
{
  using xms::Pt3d;

  // 10 *------*
  //    |      |
  //    |      *
  //    |      |
  //  0 *------*
  //    0     10

  std::vector<Pt3d> points{{0, 0, 0}, {10, 0, 0}, {10, 5, 0}, {10, 10, 0}, {0, 10, 0}};
  const double kDelta = 1e-5;
  TS_ASSERT_DELTA_PT3D(xms::gmComputeCentroid(points), Pt3d(6, 5, 0), kDelta);
  // Notice the 6 above means it's not the centroid, but the average
} // GeomsXmsngUnitTests::test_gmComputeCentroid
//------------------------------------------------------------------------------
/// \brief
/// \verbatim
// 10 *------*
//    |      |
//    |      *
//    |      |
//  0 *------*
//    0     10
/// \endverbatim
//------------------------------------------------------------------------------
void GeomsXmsngUnitTests::test_gmComputePolygonCentroid()
{
  using xms::Pt3d;

  std::vector<Pt3d> points{{0, 0, 0}, {10, 0, 0}, {10, 5, 0}, {10, 10, 0}, {0, 10, 0}};
  const double kDelta = 1e-5;
  TS_ASSERT_DELTA_PT3D(xms::gmComputePolygonCentroid(points), Pt3d(5, 5, 0), kDelta);
} // GeomsXmsngUnitTests::test_gmComputePolygonCentroid
//------------------------------------------------------------------------------
/// \brief Test lots of points for timing purposes. Only in release, not debug.
/// \see PointInPolyTests::testSpeed
/// \verbatim
// 30 -       45--44  41--40  37--36  33--32  29------28
//    |        |   |   |   |   |   |   |   |   |       |
// 25 -       46  43--42  39--38  35--34  31--30  26--27
//    |        |                                   |
// 20 -       47---48  2---3---4---5---6---7---8  25--24
//    |            |   |                       |       |
// 15 -       50---49  1  18---17 14---13 10---9  22--23
//    |        |       |   |   |   |   |   |       |
// 10 -       51       0---19 16---15 12---11     21--20
//    |        |                                       |
//  5 -       52   2---3   6---7  10--11  14--15  18--19
//    |        |   |   |   |   |   |   |   |   |   |
//  0 -        0---1   4---5   8---9  12--13  16--17
//
//             |---|---|---|---|---|---|---|---|---|---|
//             0   5  10  15  20  25  30  35  40  45  50  55
/// \endverbatim
//------------------------------------------------------------------------------
void GeomsXmsngUnitTests::test_gmPointInPolygon2D_Speed()
{
#ifndef _DEBUG
  GmPointInPolyTester_gmPointInPolygon2D tester;
  tester.DoTest();
#endif
} // GeomsXmsngUnitTests::test_gmPointInPolygon2D_Speed
//------------------------------------------------------------------------------
/// \brief Test building a convex hull
//------------------------------------------------------------------------------
void GeomsXmsngUnitTests::testConvexHull()
{
  using namespace xms;
  VecPt3d inputPoints;
  VecPt3d expectedHull;
  VecPt3d hull;
  // Pyramid
  expectedHull = {{0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {1.0, 1.0, 0.0}, {0.0, 1.0, 0.0}};
  for (int i = 0; i < 2; ++i)
  {
    for (int j = 0; j < 2; ++j)
    {
      inputPoints.push_back(Pt3d(i, j));
    }
  }
  inputPoints.push_back(Pt3d(.5, .5));
  gmGetConvexHull(inputPoints, hull);
  TS_ASSERT_EQUALS(expectedHull, hull);

  // bounds test
  expectedHull.clear();
  inputPoints.clear();
  gmGetConvexHull(inputPoints, hull);
  TS_ASSERT_EQUALS(expectedHull, hull);
} // GeomsXmsngUnitTests::TestConvexHull
//------------------------------------------------------------------------------
/// \brief Test determining if two lines intersect
//------------------------------------------------------------------------------
void GeomsXmsngUnitTests::testDoLineSegmentsCross()
{
  using namespace xms;
  // Test 1 Segments do not intersect
  {
    Pt3d point1(1, 2);
    Pt3d point2(1, 4);
    Pt3d point3(2, 1);
    Pt3d point4(4, 1);
    bool expected = false;
    TS_ASSERT_EQUALS(expected, gmLinesCross(point1, point2, point3, point4));
  }
  // Test 2 Segments that do intersect (generic)
  {
    Pt3d point1(2, 2);
    Pt3d point2(4, 4);
    Pt3d point3(2, 4);
    Pt3d point4(4, 2);
    bool expected = true;
    TS_ASSERT_EQUALS(expected, gmLinesCross(point1, point2, point3, point4));
  }
  // Test 3 Colinear
  {
    Pt3d point1(1, 5);
    Pt3d point2(1, 8);
    Pt3d point3(1, 5);
    Pt3d point4(1, 8);
    bool expected = true;
    TS_ASSERT_EQUALS(expected, gmLinesCross(point1, point2, point3, point4));
  }
  // Test 4 T intersection (false because it does not cross)
  {
    Pt3d point1(6, 2);
    Pt3d point2(6, 4);
    Pt3d point3(5, 4);
    Pt3d point4(7, 4);
    bool expected = false;
    TS_ASSERT_EQUALS(expected, gmLinesCross(point1, point2, point3, point4));
  }
  // Test 5 L intersection (which is allowed for valid shapes, so return false)
  {
    Pt3d point1(2, 5);
    Pt3d point2(2, 8);
    Pt3d point3(2, 8);
    Pt3d point4(4, 8);
    bool expected = false;
    TS_ASSERT_EQUALS(expected, gmLinesCross(point1, point2, point3, point4));
  }
  // Test 6 Near miss
  {
    Pt3d point1(5, 5);
    Pt3d point2(7, 5);
    Pt3d point3(5, 6);
    Pt3d point4(5, 8);
    bool expected = false;
    TS_ASSERT_EQUALS(expected, gmLinesCross(point1, point2, point3, point4));
  }
} // GeomsXmsngUnitTests::testDoLineSegmentsCross

////////////////////////////////////////////////////////////////////////////////
/// \class GeomsXmsngIntermediateTests
/// \brief Intermediate tests for functions in geoms.cpp
////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
/// \brief
/// \verbatim
// 15 -    0   1   2   3   4
//    |
// 10 -    5   6---7---8   9
//    |        |       |
//  5 -   10  11  12  13  14
//    |        |       |
//  0 -   15  16--17--18  19
//    |
// -15-   20  21  22  23  24
//
//         |---|---|---|---|
//        -5   0   5   10  15
/// \endverbatim
//------------------------------------------------------------------------------
void GeomsXmsngIntermediateTests::test_gmPointInPolygon2D()
{
  using xms::Pt3d;
  using xms::gmPointInPolygon2D;

  // CCW, first point not repeated. We also test it CW below.
  xms::VecPt3d poly{{0, 0, 0}, {5, 0, 0}, {10, 0, 0}, {10, 5, 0}, {10, 10, 0}, {0, 10, 0}};
  for (size_t i = 0; i < 2; ++i)
  {
    if (i == 1)
    {
      // Make it CW and recheck
      std::reverse(poly.begin(), poly.end());
    }
    TS_ASSERT_EQUALS(gmPointInPolygon2D(&poly[0], poly.size(), Pt3d(-5, 15, 0)), -1); // 0
    TS_ASSERT_EQUALS(gmPointInPolygon2D(&poly[0], poly.size(), Pt3d(0, 15, 0)), -1);  // 1
    TS_ASSERT_EQUALS(gmPointInPolygon2D(&poly[0], poly.size(), Pt3d(5, 15, 0)), -1);  // 2
    TS_ASSERT_EQUALS(gmPointInPolygon2D(&poly[0], poly.size(), Pt3d(10, 15, 0)), -1); // 3
    TS_ASSERT_EQUALS(gmPointInPolygon2D(&poly[0], poly.size(), Pt3d(15, 15, 0)), -1); // 4
    TS_ASSERT_EQUALS(gmPointInPolygon2D(&poly[0], poly.size(), Pt3d(-5, 10, 0)), -1); // 5
    TS_ASSERT_EQUALS(gmPointInPolygon2D(&poly[0], poly.size(), Pt3d(0, 10, 0)), 0);   // 6
    TS_ASSERT_EQUALS(gmPointInPolygon2D(&poly[0], poly.size(), Pt3d(5, 10, 0)), 0);   // 7
    TS_ASSERT_EQUALS(gmPointInPolygon2D(&poly[0], poly.size(), Pt3d(10, 10, 0)), 0);  // 8
    TS_ASSERT_EQUALS(gmPointInPolygon2D(&poly[0], poly.size(), Pt3d(15, 10, 0)), -1); // 9
    TS_ASSERT_EQUALS(gmPointInPolygon2D(&poly[0], poly.size(), Pt3d(-5, 5, 0)), -1);  // 10
    TS_ASSERT_EQUALS(gmPointInPolygon2D(&poly[0], poly.size(), Pt3d(0, 5, 0)), 0);    // 11
    TS_ASSERT_EQUALS(gmPointInPolygon2D(&poly[0], poly.size(), Pt3d(5, 5, 0)), 1);    // 12
    TS_ASSERT_EQUALS(gmPointInPolygon2D(&poly[0], poly.size(), Pt3d(10, 5, 0)), 0);   // 13
    TS_ASSERT_EQUALS(gmPointInPolygon2D(&poly[0], poly.size(), Pt3d(15, 5, 0)), -1);  // 14
    TS_ASSERT_EQUALS(gmPointInPolygon2D(&poly[0], poly.size(), Pt3d(-5, 0, 0)), -1);  // 15
    TS_ASSERT_EQUALS(gmPointInPolygon2D(&poly[0], poly.size(), Pt3d(0, 0, 0)), 0);    // 16
    TS_ASSERT_EQUALS(gmPointInPolygon2D(&poly[0], poly.size(), Pt3d(5, 0, 0)), 0);    // 17
    TS_ASSERT_EQUALS(gmPointInPolygon2D(&poly[0], poly.size(), Pt3d(10, 0, 0)), 0);   // 18
    TS_ASSERT_EQUALS(gmPointInPolygon2D(&poly[0], poly.size(), Pt3d(15, 0, 0)), -1);  // 19
    TS_ASSERT_EQUALS(gmPointInPolygon2D(&poly[0], poly.size(), Pt3d(-5, -5, 0)), -1); // 20
    TS_ASSERT_EQUALS(gmPointInPolygon2D(&poly[0], poly.size(), Pt3d(0, -5, 0)), -1);  // 21
    TS_ASSERT_EQUALS(gmPointInPolygon2D(&poly[0], poly.size(), Pt3d(5, -5, 0)), -1);  // 22
    TS_ASSERT_EQUALS(gmPointInPolygon2D(&poly[0], poly.size(), Pt3d(10, -5, 0)), -1); // 23
    TS_ASSERT_EQUALS(gmPointInPolygon2D(&poly[0], poly.size(), Pt3d(15, -5, 0)), -1); // 24
  }
} // GeomsXmsngIntermediateTests::test_gmPointInPolygon2D

//------------------------------------------------------------------------------
/// \brief
//------------------------------------------------------------------------------
void GeomsUnitTests::test_gmCounterClockwise()
{
  // TS_FAIL("GeomsUnitTest::test_gmCounterClockwise");

  //  2
  //  | \
    //  0---1

  Pt3d pt0(0, 0, 0);
  Pt3d pt1(10, 0, 0);
  Pt3d pt2(0, 10, 0);

  TS_ASSERT_EQUALS(gmCounterClockwiseTri(pt0, pt1, pt2), true);
  TS_ASSERT_EQUALS(gmCounterClockwiseTri(pt0, pt2, pt1), false);
} // GeomsUnitTest::test_gmCounterClockwise
//------------------------------------------------------------------------------
/// \brief
//------------------------------------------------------------------------------
void GeomsUnitTests::test_gmQuadToTriAreaCheck()
{
  // TS_FAIL("GeomsUnitTest::test_gmQuadToTriAreaCheck");

  //  3---2
  //  |   |
  //  0---1

  Pt3d pt0(0, 0, 0);
  Pt3d pt1(10, 0, 0);
  Pt3d pt2(10, 10, 0);
  Pt3d pt3(0, 10, 0);

  TS_ASSERT_EQUALS(gmQuadToTriAreaCheck(pt0, pt1, pt2, pt3), false);
  TS_ASSERT_EQUALS(gmQuadToTriAreaCheck(pt0, pt3, pt2, pt1), true);
} // GeomsUnitTest::test_gmQuadToTriAreaCheck

//------------------------------------------------------------------------------
/// \brief
//------------------------------------------------------------------------------
void GeomsUnitTest::test_gmConvertAngleBetweenXAndNorth()
{
  // TS_FAIL("GeomsUnitTest::test_gmConvertAngleBetweenXAndNorth");

  double angle;
  const double DELTA = 0.01;

  angle = 0.0;
  gmConvertAngleBetweenXAndNorth(&angle);
  TS_ASSERT_DELTA(angle, 90.0, DELTA);

  angle = 90.0;
  gmConvertAngleBetweenXAndNorth(&angle);
  TS_ASSERT_DELTA(angle, 0.0, DELTA);

  angle = 180.0;
  gmConvertAngleBetweenXAndNorth(&angle);
  TS_ASSERT_DELTA(angle, 270.0, DELTA);

  angle = 270.0;
  gmConvertAngleBetweenXAndNorth(&angle);
  TS_ASSERT_DELTA(angle, 180.0, DELTA);

  angle = 360.0;
  gmConvertAngleBetweenXAndNorth(&angle);
  TS_ASSERT_DELTA(angle, 90.0, DELTA);

  angle = 450.0;
  gmConvertAngleBetweenXAndNorth(&angle);
  TS_ASSERT_DELTA(angle, 0.0, DELTA);

  angle = -90.0;
  gmConvertAngleBetweenXAndNorth(&angle);
  TS_ASSERT_DELTA(angle, 180.0, DELTA);

  angle = -180.0;
  gmConvertAngleBetweenXAndNorth(&angle);
  TS_ASSERT_DELTA(angle, 270.0, DELTA);

  angle = -270.0;
  gmConvertAngleBetweenXAndNorth(&angle);
  TS_ASSERT_DELTA(angle, 0.0, DELTA);

  angle = -360.0;
  gmConvertAngleBetweenXAndNorth(&angle);
  TS_ASSERT_DELTA(angle, 90.0, DELTA);

  angle = -450.0;
  gmConvertAngleBetweenXAndNorth(&angle);
  TS_ASSERT_DELTA(angle, 180.0, DELTA);

} // GeomsUnitTest::test_gmConvertAngleBetweenXAndNorth
//------------------------------------------------------------------------------
/// \brief
//------------------------------------------------------------------------------
void GeomsUnitTest::test_gmAddToExtents()
{
  // TS_FAIL("GeomsUnitTest::test_gmAddToExtents");

  Pt3d min;
  min = XM_DBL_HIGHEST;
  Pt3d max;
  max = XM_DBL_LOWEST;
  const double DELTA = 0.0001;

  gmAddToExtents(Pt3d(0, 0, 0), min, max);
  TS_ASSERT_DELTA_PT3D(min, Pt3d(0, 0, 0), DELTA);
  TS_ASSERT_DELTA_PT3D(max, Pt3d(0, 0, 0), DELTA);

  gmAddToExtents(Pt3d(1, 0, 0), min, max);
  TS_ASSERT_DELTA_PT3D(min, Pt3d(0, 0, 0), DELTA);
  TS_ASSERT_DELTA_PT3D(max, Pt3d(1, 0, 0), DELTA);

  gmAddToExtents(Pt3d(0, 0, -1), min, max);
  TS_ASSERT_DELTA_PT3D(min, Pt3d(0, 0, -1), DELTA);
  TS_ASSERT_DELTA_PT3D(max, Pt3d(1, 0, 0), DELTA);

  gmAddToExtents(Pt3d(1, 0, -1), min, max);
  TS_ASSERT_DELTA_PT3D(min, Pt3d(0, 0, -1), DELTA);
  TS_ASSERT_DELTA_PT3D(max, Pt3d(1, 0, 0), DELTA);

} // GeomsUnitTest::test_gmAddToExtents
//------------------------------------------------------------------------------
/// \brief
//------------------------------------------------------------------------------
void GeomsUnitTest::test_gmExtents2D()
{
  // TS_FAIL("GeomsUnitTest::test_gmExtents2D");

  const double DELTA = 0.0001;
  Pt2d mn, mx;
  Pt3d mn3, mx3;

  VecPt3d points = { { 0, 0, 0 }, { -1, -1, -1 }, { 1, 0, 0 } };
  gmExtents2D(points, mn, mx);
  TS_ASSERT_DELTA_PT2D(mn, Pt2d(-1, -1), DELTA);
  TS_ASSERT_DELTA_PT2D(mx, Pt2d(1, 0), DELTA);

  gmExtents2D(points, mn3, mx3);
  TS_ASSERT_DELTA_PT2D(mn3, Pt3d(-1, -1, 0), DELTA);
  TS_ASSERT_DELTA_PT2D(mx3, Pt3d(1, 0, 0), DELTA);

} // GeomsUnitTest::test_gmExtents2D
//------------------------------------------------------------------------------
/// \brief
//------------------------------------------------------------------------------
void GeomsUnitTest::test_gmExtents3D()
{
  // TS_FAIL("GeomsUnitTest::test_gmExtents3D");

  const double DELTA = 0.0001;
  Pt3d min, max;

  VecPt3d points = { { 0, 0, 0 }, { -1, -1, -1 }, { 1, 0, 0 } };
  gmExtents3D(points, min, max);
  TS_ASSERT_DELTA_PT3D(min, Pt3d(-1, -1, -1), DELTA);
  TS_ASSERT_DELTA_PT3D(max, Pt3d(1, 0, 0), DELTA);

} // GeomsUnitTest::test_gmExtents3D
//------------------------------------------------------------------------------
/// \brief
//------------------------------------------------------------------------------
void GeomsUnitTest::test_gmEqualPoints()
{
  // TS_FAIL("GeomsUnitTest::test_gmEqualPoints");

  double old_g_xytol = gmXyTol();
  gmXyTol(true, 0.00001);

  // XY

  TS_ASSERT_EQUALS(gmEqualPointsXY(0.0, 0.0, 0.0, 0.0), true);
  TS_ASSERT_EQUALS(gmEqualPointsXY(0.0, 0.0, 0.0, 0.0, gmXyTol()), true);
  TS_ASSERT_EQUALS(gmEqualPointsXY(Pt2i(0, 0), Pt2i(0, 0)), true);
  TS_ASSERT_EQUALS(gmEqualPointsXY(Pt2d(0, 0), Pt2d(0, 0), gmXyTol()), true);
  TS_ASSERT_EQUALS(gmEqualPointsXY(Pt3d(0, 0, 0), Pt3d(0, 0, 0), gmXyTol()), true);

  // XYZ

  TS_ASSERT_EQUALS(gmEqualPointsXYZ(0.0, 0.0, 0.0, 0.0, 0.0, 0.0), true);
  TS_ASSERT_EQUALS(gmEqualPointsXYZ(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, gmXyTol()), true);
  TS_ASSERT_EQUALS(gmEqualPointsXYZ(Pt3d(0, 0, 0), Pt3d(0, 0, 0), gmXyTol()), true);

  gmXyTol(true, old_g_xytol);

} // GeomsUnitTest::test_gmEqualPoints
//------------------------------------------------------------------------------
/// \brief
//------------------------------------------------------------------------------
void GeomsUnitTest::test_gmPolygonArea()
{
  // TS_FAIL("GeomsUnitTest::test_gmPolygonArea");

  const double DELTA = 1e-5;

  // CCW (positive)
  VecPt3d pts1 = { { 0, 0, 0 }, { 5, 0, 5 }, { 5, 5, 0 }, { 0, 5, 0 } };
  TS_ASSERT_DELTA(gmPolygonArea(&pts1[0], static_cast<int>(pts1.size())), 25.0, DELTA);

  // CW (negative)
  VecPt3d pts2 = { { 0, 0, 0 }, { 0, 5, 0 }, { 5, 5, 0 }, { 5, 0, 5 } };
  TS_ASSERT_DELTA(gmPolygonArea(&pts2[0], static_cast<int>(pts2.size())), -25.0, DELTA);
  // Remove this green build return when updated to the new xmsgrid library with the correct
  // function
  TS_GREEN_BUILD_RETURN;
  // Test a single point to make sure it doesn't crash (see bug 0011900: Mapping Shapefile to
  // Features crashes WMS)
  VecPt3d ptsBogus = { { 0, 0, 0 } };
  TS_ASSERT_DELTA(gmPolygonArea(&ptsBogus[0], static_cast<int>(ptsBogus.size())), 0.0, DELTA);
} // GeomsUnitTest::test_gmPolygonArea
//------------------------------------------------------------------------------
/// \brief
//------------------------------------------------------------------------------
void GeomsUnitTest::test_gmPointInPolygon3DWithTol()
{
  // TS_FAIL("GeomsUnitTest::test_gmPointInPolygon3DWithTol");

  // Vertical triangle looking down (you only see the edge)
  //
  //       y
  //       ^
  //       |
  //    15 -    *
  //       |    |
  //    10 -    |
  //       |    |
  //     5 -    *
  //       |
  //     0 +----|----|----|--> x
  //       0    5   10   15

  // Set up the polygon, plane and normals
  VecPt3d verts = { { 5, 5, 0 }, { 5, 5, 5 }, { 5, 15, 5 } };
  VecInt ids = { 0, 1, 2 };
  Pt3d pt;
  Pt3d nrm;
  double d;
  gmCalculateNormalizedPlaneCoefficients(verts[0], verts[1], verts[2], &nrm.x, &nrm.y, &nrm.z, &d);

  // Point to the right
  //
  //       y
  //       ^
  //       |
  //    15 -    *
  //       |    |
  //    10 -    |    +
  //       |    |
  //     5 -    *
  //       |
  //     0 +----|----|----|--> x
  //       0    5   10   15

  // This test shows that gmPointInPolygon3DWithTol says the point is on
  // the polygon, which it is if you are talking about the perpendicular
  // projection of the point onto the plane, but it's not if you are thinking
  // about it in 3d. You'd need to also call gmDistanceFromPointToPlane to
  // see if it's actually in the plane.

  pt.Set(10, 10, 5);
  TS_ASSERT_EQUALS(gmPointInPolygon3DWithTol(pt, 3, &verts[0], &ids[0], nrm, XM_ZERO_TOL), 0);

  // Point on edge
  //
  //       y
  //       ^
  //       |
  //    15 -    *
  //       |    |
  //    10 -    +
  //       |    |
  //     5 -    *
  //       |
  //     0 +----|----|----|--> x
  //       0    5   10   15

  pt.Set(5, 10, 5);
  TS_ASSERT_EQUALS(gmPointInPolygon3DWithTol(pt, 3, &verts[0], &ids[0], nrm, XM_ZERO_TOL), 0);

  // Point inside poly
  //
  //       y
  //       ^
  //       |
  //    15 -    *
  //       |    |
  //    10 -    +
  //       |    |
  //     5 -    *
  //       |
  //     0 +----|----|----|--> x
  //       0    5   10   15

  pt.Set(5, 10, 4);
  TS_ASSERT_EQUALS(gmPointInPolygon3DWithTol(pt, 3, &verts[0], &ids[0], nrm, XM_ZERO_TOL), 1);

  // Point in plane but outside poly
  //
  //       y
  //       ^    +
  //       |
  //    15 -    *
  //       |    |
  //    10 -    |
  //       |    |
  //     5 -    *
  //       |
  //     0 +----|----|----|--> x
  //       0    5   10   15

  pt.Set(5, 20, 4);
  TS_ASSERT_EQUALS(gmPointInPolygon3DWithTol(pt, 3, &verts[0], &ids[0], nrm, XM_ZERO_TOL), -1);

} // GeomsUnitTest::test_gmPointInPolygon3DWithTol
//------------------------------------------------------------------------------
/// \brief
//------------------------------------------------------------------------------
void GeomsUnitTest::test_gmIntersectLineSegmentsWithTol()
{
  Pt3d one1, one2;
  Pt3d two1, two2;
  Pt3d out1;
  double xi, yi, zi1, zi2;
  double tol(0.0);
  xi = yi = zi1 = zi2 = 0.0;

  // Do some simple examples
  one1.Set(-5.0, 0.0, 10.0);
  one2.Set(5.0, 0.0, -10.0);
  two1.Set(0.0, -5.0, 50.0);
  two2.Set(0.0, 5.0, 100.0);

  TS_ASSERT_EQUALS(true, gmIntersectLineSegmentsWithTol(one1, one2, two1, two2, &out1.x, &out1.y,
    &out1.z, &zi2, tol) == true);
  Pt3d outTest(0.0, 0.0, 0.0);
  TS_ASSERT(gmEqualPointsXYZ(outTest, out1, tol));
  if (!_finite(zi2))
  {
    TS_FAIL("infinite");
    return;
  }
  TS_ASSERT_DELTA(75.0, zi2, 0.000001);

  // Swap segments one and two
  std::swap(one1, two1);
  std::swap(one2, two2);
  TS_ASSERT_EQUALS(true, gmIntersectLineSegmentsWithTol(one1, one2, two1, two2, &out1.x, &out1.y,
    &out1.z, &zi2, tol) == true);
  outTest.z = 75.0;
  TS_ASSERT(gmEqualPointsXYZ(outTest, out1, tol));
  TS_ASSERT_DELTA(0.0, zi2, 0.000001);

  // We are counting colinear as not intersecting for the purposes of this
  one1.Set(0.0, 0.0, 0.0);
  one2.Set(10.0, 0.0, 0.0);
  two1.Set(5.0, 0.0, 0.0);
  two2.Set(15.0, 0.0, 0.0);
  TS_ASSERT_EQUALS(false, gmIntersectLineSegmentsWithTol(one1, one2, two1, two2, &out1.x, &out1.y,
    &out1.z, &zi2, tol) == true);

  // These points were causing trouble with the original implementation
  // because we shouldn't intersect but we were finding one
  // (due to tolerance?)
  one1.Set(-88.17592213795, 30.2297178671644, 0.0);
  one2.Set(-88.1711631843, 30.229083809523, 0.0);
  two1.Set(-88.17116253901, 30.229083723548, 0.0);
  two2.Set(-88.1727133856442, 30.2309557578415, 0.0);
  tol = 0.000001;
  TS_ASSERT_EQUALS(false, gmIntersectLineSegmentsNoTol(one1, one2, two1, two2, &out1.x, &out1.y,
    &out1.z, &zi2) == true);

  // endpoints in common
  one1.Set(0.000000, -32.000000, 0.000000);
  one2.Set(480.000000, 38.000000, 0.000000);
  two1.Set(480.000000, 40.000000, 0.000000);
  two2.Set(480.000000, 38.000000, 0.000000);
  tol = 0.001000;
  TS_ASSERT_EQUALS(true, gmIntersectLineSegmentsWithTol(one1, one2, two1, two2, &xi, &yi, &zi1,
    &zi2, tol) == true);
  TS_ASSERT_DELTA(480.000000, xi, tol);
  TS_ASSERT_DELTA(38.000000, yi, tol);
  TS_ASSERT_DELTA(0.000000, zi1, tol);
  TS_ASSERT_DELTA(0.000000, zi2, tol);

  // endpoints almost in common
  one1.Set(0.000000, -32.000000, 0.000000);
  one2.Set(480.000000, 38.000500, 0.000000);
  two1.Set(480.000000, 40.000000, 0.000000);
  two2.Set(480.000000, 38.000000, 0.000000);
  tol = 0.001000;
  TS_ASSERT_EQUALS(true, gmIntersectLineSegmentsWithTol(one1, one2, two1, two2, &xi, &yi, &zi1,
    &zi2, tol) == true);
  TS_ASSERT_DELTA(480.000000, xi, tol);
  TS_ASSERT_DELTA(38.000500, yi, tol);
  TS_ASSERT_DELTA(0.000000, zi1, tol);
  TS_ASSERT_DELTA(0.000000, zi2, tol);

  // endpoint almost touches segment
  one1.Set(0.000000, 0.000000, 0.000000);
  one2.Set(1.000000, 1.000000, 0.000000);
  two1.Set(1.000000, 0.000000, 0.000000);
  two2.Set(0.500100, 0.499900, 0.000000);
  tol = 0.001000;
  TS_ASSERT_EQUALS(true, gmIntersectLineSegmentsWithTol(one1, one2, two1, two2, &xi, &yi, &zi1,
    &zi2, tol) == true);
  TS_ASSERT_DELTA(0.500000, xi, tol);
  TS_ASSERT_DELTA(0.500000, yi, tol);
  TS_ASSERT_DELTA(0.000000, zi1, tol);
  TS_ASSERT_DELTA(0.000000, zi2, tol);

} // GeomsUnitTest::test_gmIntersectLineSegmentsWithTol
//------------------------------------------------------------------------------
/// \brief
//------------------------------------------------------------------------------
void GeomsUnitTest::test_gmIntersectLineSegmentsWithTol2()
{
  // This situation was causing problems because it should be within tolerance
  Pt3d one1, one2;
  Pt3d two1, two2;
  Pt3d out1;
  double zi2(0.0);
  double tol(0.00000479);

  one1.Set(206257.24738645, 4769600.0000167, 10.0);
  one2.Set(216317.41982991, 4769600.000011, -10.0);
  two1.Set(200000.0, 4769600.000021, 50.0);
  two2.Set(207182.99426299, 4769600.000021, 100.0);

  Pt3d ip1, ip2;
  double t(0.0), s(0.0);
  double mindist(gmMinDistBetweenLinesWithTol(&one1, &one2, &two1, &two2, &ip1, &ip2, &t, &s, tol));
  TS_ASSERT_LESS_THAN(mindist, tol);

  TS_ASSERT_EQUALS(true, gmIntersectLineSegmentsWithTol(one1, one2, two1, two2, &out1.x, &out1.y,
    &out1.z, &zi2, tol));

  // parallel, overlapping in x not y
  one1.Set(10.0, 10.0, 0.0);
  one2.Set(20.0, 10.0, 10.0);
  two1.Set(5.0, 20.0, 20.0);
  two2.Set(15.0, 20.0, 15.0);

  TS_ASSERT_EQUALS(false, gmIntersectLineSegmentsWithTol(one1, one2, two1, two2, &out1.x, &out1.y,
    &out1.z, &zi2, tol));

  //  crossing
  one1.Set(10.0, 10.0, 0.0);
  one2.Set(25.0, 25.0, 10.0);
  two1.Set(10.0, 15.0, 20.0);
  two2.Set(20.0, 10.0, 15.0);

  TS_ASSERT_EQUALS(true, gmIntersectLineSegmentsWithTol(one1, one2, two1, two2, &out1.x, &out1.y,
    &out1.z, &zi2, tol));

  // overlapping in x and y, not crossing, within tolerance
  one1.Set(10.0, 10.0, 0.0);
  one2.Set(25.0, 25.0, 0.0);
  two1.Set(15.0, 30.00000473, 0.0);
  two2.Set(35.0, 20.00000473, 0.0);

  TS_ASSERT_EQUALS(true, gmIntersectLineSegmentsWithTol(one1, one2, two1, two2, &out1.x, &out1.y,
    &out1.z, &zi2, tol));

  // overlapping in x and y, not crossing, out of tolerance
  one1.Set(10.0, 10.0, 0.0);
  one2.Set(25.0, 25.0, 0.0);
  two1.Set(15.0, 30.00000480, 0.0);
  two2.Set(35.0, 20.00000480, 0.0);

  TS_ASSERT_EQUALS(false, gmIntersectLineSegmentsWithTol(one1, one2, two1, two2, &out1.x, &out1.y,
    &out1.z, &zi2, tol));

  // overlapping in x (at end) and y, not crossing, within tolerance
  one1.Set(10.0, 10.0, 0.0);
  one2.Set(25.0, 25.0, 0.0);
  two1.Set(25.0, 25.00000473, 0.0);
  two2.Set(45.0, 15.00000473, 0.0);

  TS_ASSERT_EQUALS(true, gmIntersectLineSegmentsWithTol(one1, one2, two1, two2, &out1.x, &out1.y,
    &out1.z, &zi2, tol));

  // overlapping in y not x, not crossing, within tolerance
  one1.Set(10.0, 10.0, 0.0);
  one2.Set(25.0, 25.0, 0.0);
  two1.Set(25.1, 25.00000473, 0.0);
  two2.Set(45.1, 15.00000473, 0.0);

  TS_ASSERT_EQUALS(false, gmIntersectLineSegmentsWithTol(one1, one2, two1, two2, &out1.x, &out1.y,
    &out1.z, &zi2, tol));
} // GeomsUnitTest::test_gmIntersectLineSegmentsWithTol2
//------------------------------------------------------------------------------
/// \brief
//------------------------------------------------------------------------------
void GeomsUnitTest::test_gmMakePolygonClockwise()
{
  //   10-  3--2                         10-  0--1
  //        |  |           ==>                |  |
  //    0-  0--1                          0-  3--2
  //        0  10                             0  10

  // Pt2i version
  {
    VecPt2i pts = { { 0, 0 }, { 10, 0 }, { 10, 10 }, { 0, 10 } };
    gmMakePolygonClockwise(&pts[0], static_cast<int>(pts.size()));

    TS_ASSERT_EQUALS(pts.at(0), Pt2i(0, 10));
    TS_ASSERT_EQUALS(pts.at(1), Pt2i(10, 10));
    TS_ASSERT_EQUALS(pts.at(2), Pt2i(10, 0));
    TS_ASSERT_EQUALS(pts.at(3), Pt2i(0, 0));
  }

  // Pt3d version
  {
    VecPt3d pts = { { 0, 0, 0 }, { 10, 0, 0 }, { 10, 10, 0 }, { 0, 10, 0 } };
    gmMakePolygonClockwise(&pts[0], static_cast<int>(pts.size()));

    TS_ASSERT_EQUALS(pts.at(0), Pt3d(0, 10, 0));
    TS_ASSERT_EQUALS(pts.at(1), Pt3d(10, 10, 0));
    TS_ASSERT_EQUALS(pts.at(2), Pt3d(10, 0, 0));
    TS_ASSERT_EQUALS(pts.at(3), Pt3d(0, 0, 0));
  }

  // Already clockwise (no change)
  //
  //   10-  1--2                         10-  1--2
  //        |  |           ==>                |  |
  //    0-  0--3                          0-  0--3
  //        0  10                             0  10

  // Pt2i version
  {
    VecPt2i pts = { { 0, 0 }, { 0, 10 }, { 10, 10 }, { 10, 0 } };
    gmMakePolygonClockwise(&pts[0], static_cast<int>(pts.size()));

    TS_ASSERT_EQUALS(pts.at(0), Pt2i(0, 0));
    TS_ASSERT_EQUALS(pts.at(1), Pt2i(0, 10));
    TS_ASSERT_EQUALS(pts.at(2), Pt2i(10, 10));
    TS_ASSERT_EQUALS(pts.at(3), Pt2i(10, 0));
  }

  // Pt3d version
  {
    VecPt3d pts = { { 0, 0, 0 }, { 0, 10, 0 }, { 10, 10, 0 }, { 10, 0, 0 } };
    gmMakePolygonClockwise(&pts[0], static_cast<int>(pts.size()));

    TS_ASSERT_EQUALS(pts.at(0), Pt3d(0, 0, 0));
    TS_ASSERT_EQUALS(pts.at(1), Pt3d(0, 10, 0));
    TS_ASSERT_EQUALS(pts.at(2), Pt3d(10, 10, 0));
    TS_ASSERT_EQUALS(pts.at(3), Pt3d(10, 0, 0));
  }

} // GeomsUnitTest::test_gmMakePolygonClockwise
//------------------------------------------------------------------------------
/// \brief
//------------------------------------------------------------------------------
// void GeomsUnitTest::test_gmCounterClockwise ()
//{
//  //TS_FAIL("GeomsUnitTest::test_gmCounterClockwise");
//
//  //  2
//  //  | \
//  //  0---1
//
//  Pt3d pt0(0,0,0);
//  Pt3d pt1(10,0,0);
//  Pt3d pt2(0,10,0);
//
//  TS_ASSERT_EQUALS(gmCounterClockwiseTri(pt0, pt1, pt2), true);
//  TS_ASSERT_EQUALS(gmCounterClockwiseTri(pt0, pt2, pt1), false);
//} // GeomsUnitTest::test_gmCounterClockwise

//------------------------------------------------------------------------------
/// \brief
//------------------------------------------------------------------------------
void GeomsUnitTest::test_gmCounterClockwiseQuad()
{
  // TS_FAIL("GeomsUnitTest::test_gmCounterClockwiseQuad");

  //  3---2
  //  |   |
  //  0---1

  Pt3d pt0(0, 0, 0);
  Pt3d pt1(10, 0, 0);
  Pt3d pt2(10, 10, 0);
  Pt3d pt3(0, 10, 0);

  TS_ASSERT_EQUALS(gmCounterClockwiseQuad(pt0, pt1, pt2, pt3), true);
  TS_ASSERT_EQUALS(gmCounterClockwiseQuad(pt0, pt3, pt2, pt1), false);
} // GeomsUnitTest::test_gmCounterClockwiseQuad
//------------------------------------------------------------------------------
///// \brief
//------------------------------------------------------------------------------
// void GeomsUnitTest::test_gmQuadToTriAreaCheck ()
//{
//  //TS_FAIL("GeomsUnitTest::test_gmQuadToTriAreaCheck");
//
//  //  3---2
//  //  |   |
//  //  0---1
//
//  Pt3d pt0(0,0,0);
//  Pt3d pt1(10,0,0);
//  Pt3d pt2(10,10,0);
//  Pt3d pt3(0,10,0);
//
//  TS_ASSERT_EQUALS(gmQuadToTriAreaCheck(pt0, pt1, pt2, pt3), false);
//  TS_ASSERT_EQUALS(gmQuadToTriAreaCheck(pt0, pt3, pt2, pt1), true);
//} // GeomsUnitTest::test_gmQuadToTriAreaCheck
//------------------------------------------------------------------------------
/// \brief
//------------------------------------------------------------------------------
void GeomsUnitTest::test_gmAngleBetween2DVectors()
{
  // TS_FAIL("GeomsUnitTest::test_gmAngleBetween2DVectors");

  const double DELTA = 1e-4;
  double a;

  a = RADIANS_TO_DEGREES * gmAngleBetween2DVectors(10, 0, 5, 5);
  TS_ASSERT_DELTA(a, 45, DELTA);
  a = RADIANS_TO_DEGREES * gmAngleBetween2DVectors(5, 5, 10, 0);
  TS_ASSERT_DELTA(a, 315, DELTA);
  a = RADIANS_TO_DEGREES * gmAngleBetween2DVectors(10, 0, 0, 10);
  TS_ASSERT_DELTA(a, 90, DELTA);

} // GeomsUnitTest::test_gmQuadToTriAreaCheck
//------------------------------------------------------------------------------
/// \brief
//------------------------------------------------------------------------------
void GeomsUnitTest::test_gmAngleBetweenEdges()
{
  // TS_FAIL("GeomsUnitTest::test_gmAngleBetweenEdges");

  const double DELTA = 1e-4;
  const double TO_DEG = RADIANS_TO_DEGREES;
  double a, am, b, bm, c, cm;

  {
    Pt3d p0(0, 0, 0), p1(10, 0, 0), p2(10, 5, 0);

    //  5         c 2
    //       a    b |
    //  0  0--------1
    //     0       10

    a = TO_DEG * gmAngleBetweenEdges(p1, p0, p2);
    TS_ASSERT_DELTA(a, 26.565, DELTA);
    am = TO_DEG * gmAngleBetweenEdges(p2, p0, p1);
    TS_ASSERT_DELTA(am, 333.4349, DELTA);
    b = TO_DEG * gmAngleBetweenEdges(p2, p1, p0);
    TS_ASSERT_DELTA(b, 90, DELTA);
    bm = TO_DEG * gmAngleBetweenEdges(p0, p1, p2);
    TS_ASSERT_DELTA(bm, 270, DELTA);
    c = TO_DEG * gmAngleBetweenEdges(p0, p2, p1);
    TS_ASSERT_DELTA(c, 63.4349, DELTA);
    cm = TO_DEG * gmAngleBetweenEdges(p1, p2, p0);
    TS_ASSERT_DELTA(cm, 296.5650, DELTA);
  }

  {
    Pt3d p0(0, 0, 0), p1(10, 0, 0), p2(10, -5, 0);

    //     0       10
    //  0  0--------1
    //       a    b |
    // -5         c 2

    a = TO_DEG * gmAngleBetweenEdges(p1, p0, p2);
    TS_ASSERT_DELTA(a, 333.4349, DELTA);
    am = TO_DEG * gmAngleBetweenEdges(p2, p0, p1);
    TS_ASSERT_DELTA(am, 26.5650, DELTA);
    b = TO_DEG * gmAngleBetweenEdges(p2, p1, p0);
    TS_ASSERT_DELTA(b, 270, DELTA);
    bm = TO_DEG * gmAngleBetweenEdges(p0, p1, p2);
    TS_ASSERT_DELTA(bm, 90, DELTA);
    c = TO_DEG * gmAngleBetweenEdges(p0, p2, p1);
    TS_ASSERT_DELTA(c, 296.5650, DELTA);
    cm = TO_DEG * gmAngleBetweenEdges(p1, p2, p0);
    TS_ASSERT_DELTA(cm, 63.4349, DELTA);
  }

} // GeomsUnitTest::test_gmAngleBetweenEdges
//------------------------------------------------------------------------------
/// \brief
//------------------------------------------------------------------------------
void GeomsUnitTest::test_gmBaryPrepare()
{
  // 20 2
  //    | \
    //    |  \
    // 10 0---1
  //    10  20

  Pt3d pt0(10, 10, 0);
  Pt3d pt1(20, 10, 0);
  Pt3d pt2(10, 20, 0);
  Pt3d norm(0, 0, 1); // normal to the triangle
  Pt3d orig(0, 0, 0);
  double coef[6];
  int dir = 0;
  bool flag = true;
  const double kDelta = 1e-5;

  int r = gmBaryPrepare(&pt0, &pt1, &pt2, &norm, &orig, coef, &dir, flag);

  TS_ASSERT_EQUALS(r, XM_SUCCESS);
  TS_ASSERT_DELTA_PT3D(orig, Pt3d(10, 10, 0), kDelta);
  TS_ASSERT_DELTA(coef[0], -0.1, kDelta);
  TS_ASSERT_DELTA(coef[1], -0.1, kDelta);
  TS_ASSERT_DELTA(coef[2], 1.0, kDelta);
  TS_ASSERT_DELTA(coef[3], 0.1, kDelta);
  TS_ASSERT_DELTA(coef[4], 0.0, kDelta);
  TS_ASSERT_DELTA(coef[5], 0.0, kDelta);
  TS_ASSERT_EQUALS(dir, 2);

  Pt3d node(0, 0, 0);
  Pt3d bary(0, 0, 0);
  gmCartToBary(&node, &orig, coef, dir, &bary);
  TS_ASSERT_DELTA_PT3D(bary, Pt3d(3.0, -1.0, -1.0), kDelta);

  node = pt0;
  gmCartToBary(&node, &orig, coef, dir, &bary);
  TS_ASSERT_DELTA_PT3D(bary, Pt3d(1, 0, 0), kDelta);

  node = pt1;
  gmCartToBary(&node, &orig, coef, dir, &bary);
  TS_ASSERT_DELTA_PT3D(bary, Pt3d(0, 1, 0), kDelta);

  node = pt2;
  gmCartToBary(&node, &orig, coef, dir, &bary);
  TS_ASSERT_DELTA_PT3D(bary, Pt3d(0, 0, 1), kDelta);

  node.Set(15, 10, 0);
  gmCartToBary(&node, &orig, coef, dir, &bary);
  TS_ASSERT_DELTA_PT3D(bary, Pt3d(.5, .5, 0), kDelta);

  node.Set(15, 15, 0);
  gmCartToBary(&node, &orig, coef, dir, &bary);
  TS_ASSERT_DELTA_PT3D(bary, Pt3d(0, .5, .5), kDelta);

  node.Set(10, 15, 0);
  gmCartToBary(&node, &orig, coef, dir, &bary);
  TS_ASSERT_DELTA_PT3D(bary, Pt3d(.5, 0, .5), kDelta);

} // GeomsUnitTest::test_gmBaryPrepare
//------------------------------------------------------------------------------
/// \brief
//------------------------------------------------------------------------------
void GeomsUnitTest::test_gmIntersectLines()
{
  using xms::Pt3d;
  using xms::gmIntersectLines;

  double xi, yi, zi, onet, twot, tol(1000); // tol is ignored
  const double tolerance(1e-5);
  bool rv;

  {
    //      |
    //  ----|----
    //      |

    Pt3d one1(0, 0), one2(100, 0, 50), two1(50, 50, 200), two2(50, -50, 100);
    rv = gmIntersectLines(one1, one2, two1, two2, &xi, &yi, &zi, onet, twot, tol);
    TS_ASSERT_EQUALS(rv, true);
    TS_ASSERT_DELTA(xi, 50, tolerance);
    TS_ASSERT_DELTA(yi, 0, tolerance);
    TS_ASSERT_DELTA(zi, 150, tolerance);
    TS_ASSERT_DELTA(onet, 0.5, tolerance);
    TS_ASSERT_DELTA(twot, 0.5, tolerance);
  }

  {
    //  ---------
    //
    //  ---------

    Pt3d one1(0, 0), one2(100, 0, 50), two1(0, 50, 200), two2(100, 50, 100);
    rv = gmIntersectLines(one1, one2, two1, two2, &xi, &yi, &zi, onet, twot, tol);
    TS_ASSERT_EQUALS(rv, false);
    TS_ASSERT_DELTA(onet, 0.0, tolerance);
    TS_ASSERT_DELTA(twot, 0.0, tolerance);
  }
  {
    //      |
    //  ----|
    //      |

    Pt3d one1(0, 0), one2(50, 0, 50), two1(50, 50, 200), two2(50, -50, 100);
    rv = gmIntersectLines(one1, one2, two1, two2, &xi, &yi, &zi, onet, twot, tol);
    TS_ASSERT_EQUALS(rv, true);
    TS_ASSERT_DELTA(xi, 50, tolerance);
    TS_ASSERT_DELTA(yi, 0, tolerance);
    TS_ASSERT_DELTA(zi, 150, tolerance);
    TS_ASSERT_DELTA(onet, 1.0, tolerance);
    TS_ASSERT_DELTA(twot, 0.5, tolerance);
  }
  {
    //      |
    //  ----*

    Pt3d one1(0, 0), one2(50, 0, 50), two1(50, 50, 200), two2(50, 0, 100);
    rv = gmIntersectLines(one1, one2, two1, two2, &xi, &yi, &zi, onet, twot, tol);
    TS_ASSERT_EQUALS(rv, true);
    TS_ASSERT_DELTA(xi, 50, tolerance);
    TS_ASSERT_DELTA(yi, 0, tolerance);
    TS_ASSERT_DELTA(zi, 100, tolerance);
    TS_ASSERT_DELTA(onet, 1.0, tolerance);
    TS_ASSERT_DELTA(twot, 1.0, tolerance);
  }
  {
    //      |
    //
    //  ----*

    Pt3d one1(0, 0), one2(50, 0), two1(50, 50), two2(50, 10);
    rv = gmIntersectLines(one1, one2, two1, two2, &xi, &yi, &zi, onet, twot, tol);
    TS_ASSERT_EQUALS(rv, true);
    TS_ASSERT_DELTA(xi, 50, tolerance);
    TS_ASSERT_DELTA(yi, 0, tolerance);
    TS_ASSERT_DELTA(zi, 0, tolerance);
    TS_ASSERT_DELTA(onet, 1.0, tolerance);
    TS_ASSERT_DELTA(twot, 1.25, tolerance);
  }
  {
    //  ----  ----

    Pt3d one1(0, 0), one2(50, 0), two1(60, 0), two2(100, 0);
    rv = gmIntersectLines(one1, one2, two1, two2, &xi, &yi, &zi, onet, twot, tol);
    TS_ASSERT_EQUALS(rv, false);
  }
} // GeomsUnitTest::test_gmIntersectLines
//------------------------------------------------------------------------------
/// \brief
//------------------------------------------------------------------------------
void GeomsUnitTest::test_gmMiddleThirdWithTol()
{
  const double tol = 1e-5;

  // Test horizontally
  TS_ASSERT_EQUALS(gmMiddleThirdWithTol({ 2, 0, 0 }, { 0, 0, 0 }, { 9, 0, 0 }, tol), false);
  TS_ASSERT_EQUALS(gmMiddleThirdWithTol({ 3, 0, 0 }, { 0, 0, 0 }, { 9, 0, 0 }, tol), true);
  TS_ASSERT_EQUALS(gmMiddleThirdWithTol({ 4, 0, 0 }, { 0, 0, 0 }, { 9, 0, 0 }, tol), true);
  TS_ASSERT_EQUALS(gmMiddleThirdWithTol({ 5, 0, 0 }, { 0, 0, 0 }, { 9, 0, 0 }, tol), true);
  TS_ASSERT_EQUALS(gmMiddleThirdWithTol({ 6, 0, 0 }, { 0, 0, 0 }, { 9, 0, 0 }, tol), true);
  TS_ASSERT_EQUALS(gmMiddleThirdWithTol({ 7, 0, 0 }, { 0, 0, 0 }, { 9, 0, 0 }, tol), false);

  // Test vertically
  TS_ASSERT_EQUALS(gmMiddleThirdWithTol({ 0, 2, 0 }, { 0, 0, 0 }, { 0, 9, 0 }, tol), false);
  TS_ASSERT_EQUALS(gmMiddleThirdWithTol({ 0, 3, 0 }, { 0, 0, 0 }, { 0, 9, 0 }, tol), true);
  TS_ASSERT_EQUALS(gmMiddleThirdWithTol({ 0, 4, 0 }, { 0, 0, 0 }, { 0, 9, 0 }, tol), true);
  TS_ASSERT_EQUALS(gmMiddleThirdWithTol({ 0, 5, 0 }, { 0, 0, 0 }, { 0, 9, 0 }, tol), true);
  TS_ASSERT_EQUALS(gmMiddleThirdWithTol({ 0, 6, 0 }, { 0, 0, 0 }, { 0, 9, 0 }, tol), true);
  TS_ASSERT_EQUALS(gmMiddleThirdWithTol({ 0, 7, 0 }, { 0, 0, 0 }, { 0, 9, 0 }, tol), false);
} // GeomsUnitTest::test_gmMiddleThirdWithTol
//------------------------------------------------------------------------------
/// \brief Test gmGreatCircleDistanceMeters.
//------------------------------------------------------------------------------
void GeomsUnitTest::testGreatCircleDistanceMeters()
{
  const double kDelta = 1e-5;
  TS_ASSERT_DELTA(gmGreatCircleDistanceMeters({ 0, 0 }, { 1, 0 }), 111194.92664455874, kDelta);
  TS_ASSERT_DELTA(gmGreatCircleDistanceMeters({ 0, 0 }, { 0, 1 }), 111194.92664455874, kDelta);
  TS_ASSERT_DELTA(gmGreatCircleDistanceMeters({ 1, 0 }, { 0, 0 }), 111194.92664455874, kDelta);
  TS_ASSERT_DELTA(gmGreatCircleDistanceMeters({ 0, 1 }, { 0, 0 }), 111194.92664455874, kDelta);
  TS_ASSERT_DELTA(gmGreatCircleDistanceMeters({ 0, 0 }, { -1, 0 }), 111194.92664455874, kDelta);
  TS_ASSERT_DELTA(gmGreatCircleDistanceMeters({ 0, 0 }, { 0, -1 }), 111194.92664455874, kDelta);
  TS_ASSERT_DELTA(gmGreatCircleDistanceMeters({ -1, 0 }, { 0, 0 }), 111194.92664455874, kDelta);
  TS_ASSERT_DELTA(gmGreatCircleDistanceMeters({ 0, -1 }, { 0, 0 }), 111194.92664455874, kDelta);

  TS_ASSERT_DELTA(gmGreatCircleDistanceMeters({ 0, 0 }, { 0, 90 }), 10007543.398010287, kDelta);
  TS_ASSERT_DELTA(gmGreatCircleDistanceMeters({ 0, 0 }, { 90, 0 }), 10007543.398010287, kDelta);

  TS_ASSERT_DELTA(gmGreatCircleDistanceMeters({ 0, 0 }, { 180, 0 }), 20015086.796020571, kDelta);
  TS_ASSERT_DELTA(gmGreatCircleDistanceMeters({ 0, 0 }, { 359, 0 }), 111194.92664456471, kDelta);
  TS_ASSERT_DELTA(gmGreatCircleDistanceMeters({ 0, 0 }, { 360, 0 }), 1.5604449514735575e-9, kDelta);
  TS_ASSERT_DELTA(gmGreatCircleDistanceMeters({ 0, 0 }, { 361, 0 }), 111194.92664455590, kDelta);
} // GeomsUnitTest::testGreatCircleDistanceMeters

#endif
