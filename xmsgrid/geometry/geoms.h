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
#include <xmscore/points/pt.h> // Pt3d, Pt2d, etc.
#include <xmscore/stl/vector.h>

// 5. Shared Headers

// 6. Non-shared Headers

//----- Namespace declaration --------------------------------------------------

namespace xms
{
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

double gmAngleBetweenEdges(const Pt2d& p1, const Pt2d& p2, const Pt2d& p3);
double gmAngleBetweenEdges(const Pt3d& p1, const Pt3d& p2, const Pt3d& p3);
double gmComputeDeviationInDirection(const Pt3d& a_p0, const Pt3d& a_p1, const Pt3d& a_p2);

double gmBisectingAngle(const Pt3d& a_p1, const Pt3d& a_p2, const Pt3d& a_p3);
double gmPerpendicularAngle(const Pt3d& a_pt1, const Pt3d& a_pt2);

double gmConvertAngleToBetween0And360(double a_angle, bool a_InDegrees = true);

Turn_enum gmTurn(const Pt3d& a_v1, const Pt3d& a_v2, const Pt3d& a_v3, double a_angtol = 0.0017453);


// Barycenters
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


// Algebraic functions
double gmCross2D(const double& dx1, const double& dy1, const double& dx2, const double& dy2);
double gmCross2D(const Pt3d& a_origin, const Pt3d& a_A, const Pt3d& a_B);
void gmCross3D(const Pt3d& a_vec1, const Pt3d& a_vec2, Pt3d* a_vec3);
inline double gmDot3D(const Pt3d& a_vec1, const Pt3d& a_vec2);
void gmComponentMagnitudes(double* a_x, double* a_y, double* a_mag, double* a_dir, bool a_tomagdir);
Pt3d gmCreateVector(const Pt3d& a_p1, const Pt3d& a_p2);


// Polygon bounds
int gmPointInPolygon2D(const Pt2i* a_verts, size_t a_num, Pt2i a_pt);
int gmPointInPolygon2D(const Pt2i* a_verts, size_t a_num, Pt2d a_pt);
int gmPointInPolygon2D(const Pt2i* a_verts, size_t a_num, Pt3d a_pt);
int gmPointInPolygon2D(const Pt3d* a_verts, size_t a_num, double a_x, double a_y);
int gmPointInPolygon2D(const Pt3d* a_verts, size_t a_num, Pt3d a_pt);
int gmPointInPolygon2D(const VecPt3d& a_verts, const Pt3d& a_pt);
template <typename T>
int gmPointInPolygon2D(const T* theverts,
                       const size_t numverts,
                       const double xpt,
                       const double ypt,
                       const double tol);

// Distance
double gm2DDistanceToLineWithTol(const Pt3d* a_pt1,
                                 const Pt3d* a_pt2,
                                 double a_x,
                                 double a_y,
                                 double a_tol);

double gmXyDistance(const Pt3d& pt1, const Pt3d& pt2);
double gmXyDistance(double x1, double y1, double x2, double y2);
double gmXyDistanceSquared(const Pt3d& pt1, const Pt3d& pt2);


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
int gmIntersectTriangleAndLineSegment(const Pt3d& a_pt1,
                                      const Pt3d& a_pt2,
                                      const Pt3d& a_t0,
                                      const Pt3d& a_t1,
                                      const Pt3d& a_t2,
                                      Pt3d& a_IntersectPt);

bool gmLinesIntersect(const Pt3d& one1, const Pt3d& one2, const Pt3d& two1, const Pt3d& two2);
bool gmLinesCross(const Pt3d& a_segment1Point1,
                  const Pt3d& a_segment1Point2,
                  const Pt3d& a_segment2Point1,
                  const Pt3d& a_segment2Point2);




// Testing if points are in/on objects
bool gmOnLineAndBetweenEndpointsWithTol(const Pt3d& a_pt1,
                                        const Pt3d& a_pt2,
                                        const double a_x,
                                        const double a_y,
                                        double a_tol);
bool gmOnLineWithTol(const Pt3d& p1,
                     const Pt3d& p2,
                     const double x,
                     const double y,
                     const double tol);

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

PtInOutOrOn_enum gmPtInCircumcircle(const Pt3d& pt, Pt3d circumcirclePts[3]);
bool gmPointInTriangleWithTol(const Pt3d* p1,
                              const Pt3d* p2,
                              const Pt3d* p3,
                              double x,
                              double y,
                              double tol);
bool gmPointInOrOnBox2d(const Pt3d& a_bMin, const Pt3d& a_bMax, const Pt3d& a_pt);


// Finding points on lines
double gmFindClosestPtOnSegment(const Pt3d& a_pt1,
                                const Pt3d& a_pt2,
                                const Pt3d& a_pt,
                                Pt3d& a_newpt,
                                const double a_tol);

double gmPtDistanceAlongSegment(const Pt3d& a_pt1,
                                const Pt3d& a_pt2,
                                const Pt3d& a_pt,
                                const double a_tol);


// Tolerance
double gmComputeXyTol(const Pt3d& a_mn, const Pt3d& a_mx);
double gmXyTol(bool a_set = false, double a_value = 1e-9);
double gmZTol(bool a_set = false, double a_value = 1e-6);


// Vertex ordering
bool gmCounterClockwiseTri(const Pt3d& vtx0, const Pt3d& vtx1, const Pt3d& vtx2);
void gmOrderPointsCounterclockwise(const VecPt3d& a_pts, VecInt& a_ccwOrder, int a_startindex = 0);
void gmOrderPointsCounterclockwise(VecPt3d& a_pts);


// Equation solving
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

bool gmCircumcircleWithTol(const Pt3d* pt1,
                           const Pt3d* pt2,
                           const Pt3d* pt3,
                           double* xc,
                           double* yc,
                           double* r2,
                           double tol);


// Misc.
bool gmBoxesOverlap2d(const Pt3d& a_b1Min,
                      const Pt3d& a_b1Max,
                      const Pt3d& a_b2Min,
                      const Pt3d& a_b2Max);

bool gmColinearWithTol(const Pt3d& p1, const Pt3d& p2, const Pt3d& p3, const double tol);

Pt3d gmComputeCentroid(const VecPt3d& a_points);
Pt3d gmComputePolygonCentroid(const VecPt3d& pts);

void gmGetConvexHull(const VecPt3d& a_pts, VecPt3d& a_hull, bool a_includeOn = false);

double gmPolygonArea(const Pt3d* pts, size_t npoints);


// Utility functions
VecPt3d gmArrayToVecPt3d(double* a_array, int a_size);
double gmMiddleZ(const VecPt3d& a_points);

} // namespace xms
