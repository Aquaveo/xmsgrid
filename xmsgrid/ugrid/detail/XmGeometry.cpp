//------------------------------------------------------------------------------
/// \file
/// \ingroup ugrid
/// \copyright (C) Copyright Aquaveo 2018. Distributed under FreeBSD License
/// (See accompanying file LICENSE or https://aqaveo.com/bsd/license.txt)
//------------------------------------------------------------------------------

//----- Included files ---------------------------------------------------------

// 1. Precompiled header

// 2. My own header
#include <xmsgrid/ugrid/detail/XmGeometry.h>

// 3. Standard library headers
#include <set>

// 4. External library headers
#include <boost/container/flat_set.hpp>

// 5. Shared code headers
#include <xmscore/misc/XmConst.h>
#include <xmscore/misc/XmLog.h>

// 6. Non-shared code headers
#include <xmsgrid/ugrid/XmUGrid.h>
#include <xmsgrid/ugrid/XmUGridUtils.h>

//----- Forward declarations ---------------------------------------------------

//----- External globals -------------------------------------------------------

//----- Namespace declaration --------------------------------------------------

/// XMS Namespace
namespace xms
{
//----- Constants / Enumerations -----------------------------------------------

//----- Classes / Structs ------------------------------------------------------

//----- Internal functions -----------------------------------------------------

//----- Class / Function definitions -------------------------------------------

namespace
{

//------------------------------------------------------------------------------
/// \brief 2D cross product of two points
/// \param[in] a_origin: origin point for the "vectors"
/// \param[in] a_A: first vector
/// \param[in] a_B: second vector
/// \return the cross product
//------------------------------------------------------------------------------
double iCross(const Pt3d& a_origin, const Pt3d& a_A, const Pt3d& a_B)
{
  return (a_A.x - a_origin.x) * (a_B.y - a_origin.y) - (a_A.y - a_origin.y) * (a_B.x - a_origin.x);
} // cross

}

//------------------------------------------------------------------------------
/// \brief Returns the convex hull of a set of points
/// \param[in] a_points: The list of points
/// \return the list of points in the convex hull
/// \note a convex hull is the minimum set of points which contains (not connects)
///   all of the points in a set and is convex.
//------------------------------------------------------------------------------
std::vector<Pt3d> ConvexHull(std::vector<Pt3d> a_points)
{
  size_t n = a_points.size(), j = 0;
  if (n <= 3)
    return a_points;
  std::vector<Pt3d> convexHull(2 * n);

  // Sort points lexicographically
  sort(a_points.begin(), a_points.end());

  // Build lower hull
  for (size_t i = 0; i < n; ++i)
  {
    while (j >= 2 && iCross(convexHull[j - 2], convexHull[j - 1], a_points[i]) <= 0)
      j--;
    convexHull[j++] = a_points[i];
  }

  // Build upper hull
  for (size_t i = n - 1, t = j + 1; i > 0; --i)
  {
    while (j >= t && iCross(convexHull[j - 2], convexHull[j - 1], a_points[i - 1]) <= 0)
      j--;
    convexHull[j++] = a_points[i - 1];
  }

  convexHull.resize(j - 1);
  return convexHull;
} // ConvexHull
//------------------------------------------------------------------------------
/// \brief Returns the convex hull of a set of points
/// \param[in] a_points: The list of indices to points
/// \param[in] a_ugrid: The ugrid that contains the points.
/// \return the list of indices to points in the convex hull
/// \note a convex hull is the minimum set of points which contains (not connects)
///   all of the points in a set and is convex.
//------------------------------------------------------------------------------
VecInt ConvexHullWithIndices(const VecInt& a_points, BSHP<XmUGrid> a_ugrid)
{
  std::vector<Pt3d> points3d(a_points.size());
  for (int i = 0; i < a_points.size(); ++i)
  {
    points3d.push_back(a_ugrid->GetPointLocation(a_points[i]));
  }
  std::vector<Pt3d> convexHull = ConvexHull(points3d);
  VecInt returnPoints(convexHull.size());
  for (int i(0); i < convexHull.size(); i++)
  {
    for (int j(0); i < points3d.size(); j++)
    {
      if (convexHull[i] == points3d[j])
      {
        returnPoints.push_back(a_points[j]);
        break;
      }
    }
  }
  return returnPoints;
} // ConvexHullWithIndices
//------------------------------------------------------------------------------
/// \brief Determine whether 2 line segments intersect
/// \param[in] a_segment1: The first line segment
/// \param[in] a_segment2: The second line segment
/// \return true if the line segments intersect
//------------------------------------------------------------------------------
bool DoLineSegmentsCross(const std::pair<Pt3d, Pt3d>& a_segment1,
                         const std::pair<Pt3d, Pt3d>& a_segment2)
{
  return DoLineSegmentsCross(a_segment1.first, a_segment1.second, a_segment2.first,
                             a_segment2.second);
} // DoLineSegmentsCross

//------------------------------------------------------------------------------
/// \brief Determine whether 2 line segments cross
/// \param[in] a_segment1Point1: First point 3d of line segment 1
/// \param[in] a_segment1Point2: Second point 3d of line segment 1
/// \param[in] a_segment2Point1: First point 3d of line segment 2
/// \param[in] a_segment2Point2: Second point 3d of line segment 2
/// \return true if the line segments cross
//------------------------------------------------------------------------------
bool DoLineSegmentsCross(const Pt3d& a_segment1Point1,
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

  // is true if and only if the scalar cross products CA->�CD-> and CB->�CD-> have opposite signs.
  // is true if and only if the scalar cross products AC->�AB-> and AD->�AB-> have opposite signs.

  // Conclusion: the line segments intersect if and only if both are negative
  double result1 = iCross(a_segment2Point1, a_segment1Point1, a_segment2Point2);
  double result2 = iCross(a_segment2Point1, a_segment1Point2, a_segment2Point2);
  double result3 = iCross(a_segment1Point1, a_segment2Point1, a_segment1Point2);
  double result4 = iCross(a_segment2Point1, a_segment2Point2, a_segment1Point2);

  return (result1 * result2 < 0 && result3 * result4 < 0);

} // DoLineSegmentsCross

} // namespace xms

#ifdef CXX_TEST
//------------------------------------------------------------------------------
// Unit Tests
//------------------------------------------------------------------------------
using namespace xms;
#include <xmsgrid/ugrid/detail/XmGeometry.t.h>

//------------------------------------------------------------------------------
/// \brief Test building a convex hull
//------------------------------------------------------------------------------
void XmGeometryUnitTests::testConvexHull()
{
  std::vector<Pt3d> inputPoints;
  std::vector<Pt3d> expectedHull;
  std::vector<Pt3d> hull;
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
  hull = ConvexHull(inputPoints);
  TS_ASSERT_EQUALS(expectedHull, hull);

  // bounds test
  expectedHull.clear();
  inputPoints.clear();
  hull = ConvexHull(inputPoints);
  TS_ASSERT_EQUALS(expectedHull, hull);
} // XmGeometryUnitTests::TestConvexHull
////////////////////////////////////////////////////////////////////////////////
/// \class XmUGridTests
/// \brief Tests XmUGrids.
////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
/// \brief Test determining if two lines intersect
//------------------------------------------------------------------------------
void XmGeometryUnitTests::testDoLineSegmentsCross()
{
  // Test 1 Segments do not intersect
  {
    Pt3d point1(1, 2);
    Pt3d point2(1, 4);
    Pt3d point3(2, 1);
    Pt3d point4(4, 1);
    std::pair<Pt3d, Pt3d> segment1;
    std::pair<Pt3d, Pt3d> segment2;
    segment1.first = point1;
    segment1.second = point2;
    segment2.first = point3;
    segment2.second = point4;
    bool expected = false;
    TS_ASSERT_EQUALS(expected, DoLineSegmentsCross(point1, point2, point3, point4));
    TS_ASSERT_EQUALS(expected, DoLineSegmentsCross(segment1, segment2));
  }
  // Test 2 Segments that do intersect (generic)
  {
    Pt3d point1(2, 2);
    Pt3d point2(4, 4);
    Pt3d point3(2, 4);
    Pt3d point4(4, 2);
    std::pair<Pt3d, Pt3d> segment1;
    std::pair<Pt3d, Pt3d> segment2;
    segment1.first = point1;
    segment1.second = point2;
    segment2.first = point3;
    segment2.second = point4;
    bool expected = true;
    TS_ASSERT_EQUALS(expected, DoLineSegmentsCross(point1, point2, point3, point4));
    TS_ASSERT_EQUALS(expected, DoLineSegmentsCross(segment1, segment2));
  }
  // Test 3 Colinear
  {
    Pt3d point1(1, 5);
    Pt3d point2(1, 8);
    Pt3d point3(1, 5);
    Pt3d point4(1, 8);
    std::pair<Pt3d, Pt3d> segment1;
    std::pair<Pt3d, Pt3d> segment2;
    segment1.first = point1;
    segment1.second = point2;
    segment2.first = point3;
    segment2.second = point4;
    bool expected = true;
    TS_ASSERT_EQUALS(expected, DoLineSegmentsCross(point1, point2, point3, point4));
    TS_ASSERT_EQUALS(expected, DoLineSegmentsCross(segment1, segment2));
  }
  // Test 4 T intersection (false because it does not cross)
  {
    Pt3d point1(6, 2);
    Pt3d point2(6, 4);
    Pt3d point3(5, 4);
    Pt3d point4(7, 4);
    std::pair<Pt3d, Pt3d> segment1;
    std::pair<Pt3d, Pt3d> segment2;
    segment1.first = point1;
    segment1.second = point2;
    segment2.first = point3;
    segment2.second = point4;
    bool expected = false;
    TS_ASSERT_EQUALS(expected, DoLineSegmentsCross(point1, point2, point3, point4));
    TS_ASSERT_EQUALS(expected, DoLineSegmentsCross(segment1, segment2));
  }
  // Test 5 L intersection (which is allowed for valid shapes, so return false)
  {
    Pt3d point1(2, 5);
    Pt3d point2(2, 8);
    Pt3d point3(2, 8);
    Pt3d point4(4, 8);
    std::pair<Pt3d, Pt3d> segment1;
    std::pair<Pt3d, Pt3d> segment2;
    segment1.first = point1;
    segment1.second = point2;
    segment2.first = point3;
    segment2.second = point4;
    bool expected = false;
    TS_ASSERT_EQUALS(expected, DoLineSegmentsCross(point1, point2, point3, point4));
    TS_ASSERT_EQUALS(expected, DoLineSegmentsCross(segment1, segment2));
  }
  // Test 6 Near miss
  {
    Pt3d point1(5, 5);
    Pt3d point2(7, 5);
    Pt3d point3(5, 6);
    Pt3d point4(5, 8);
    std::pair<Pt3d, Pt3d> segment1;
    std::pair<Pt3d, Pt3d> segment2;
    segment1.first = point1;
    segment1.second = point2;
    segment2.first = point3;
    segment2.second = point4;
    bool expected = false;
    TS_ASSERT_EQUALS(expected, DoLineSegmentsCross(point1, point2, point3, point4));
    TS_ASSERT_EQUALS(expected, DoLineSegmentsCross(segment1, segment2));
  }
} // XmGeometryUnitTests::testDoLineSegmentsCross

#endif
