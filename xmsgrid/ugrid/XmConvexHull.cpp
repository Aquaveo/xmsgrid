//------------------------------------------------------------------------------
/// \file XmConvexHull.cpp
/// \ingroup ugrid
/// \copyright (C) Copyright Aquaveo 2018.
//------------------------------------------------------------------------------

//----- Included files ---------------------------------------------------------

// 1. Precompiled header

// 2. My own header
#include <xmsgrid/ugrid/XmConvexHull.h>

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

////////////////////////////////////////////////////////////////////////////////

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
    while (j >= 2 && cross(convexHull[j - 2], convexHull[j - 1], a_points[i]) <= 0)
      j--;
    convexHull[j++] = a_points[i];
  }

  // Build upper hull
  for (size_t i = n - 1, t = j + 1; i > 0; --i)
  {
    while (j >= t && cross(convexHull[j - 2], convexHull[j - 1], a_points[i - 1]) <= 0)
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
    points3d.push_back(a_ugrid->GetPoint(a_points[i]));
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
} // namespace xms

#ifdef CXX_TEST
//------------------------------------------------------------------------------
// Unit Tests
//------------------------------------------------------------------------------
using namespace xms;
#include <xmsgrid/ugrid/XmConvexHull.t.h>

//------------------------------------------------------------------------------
/// \brief Test building a convex hull
//------------------------------------------------------------------------------
void XmUGridConvexHullTests::testConvexHull()
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
} // XmUGridConvexHullTests::TestConvexHull

#endif
