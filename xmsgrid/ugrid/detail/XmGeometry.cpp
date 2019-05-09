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
#include <xmsgrid/geometry/geoms.h>
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

//------------------------------------------------------------------------------
/// \brief Returns the convex hull of a set of points (Deprecated).
/// \param[in] a_points: The list of points
/// \return the list of points in the convex hull
/// \note a convex hull is the minimum set of points which contains (not connects)
///   all of the points in a set and is convex.
//------------------------------------------------------------------------------
// TODO: Deprecated. Remove in major version change.
VecPt3d ConvexHull(const std::vector<Pt3<double>>& a_points)
{
  VecPt3d hull;
  gmGetConvexHull(a_points, hull, false);
  return hull;
} // ConvexHull
//------------------------------------------------------------------------------
/// \brief Returns the convex hull of a set of points (Deprecated).
/// \param[in] a_points: The list of indices to points
/// \param[in] a_ugrid: The ugrid that contains the points.
/// \return the list of indices to points in the convex hull
/// \note a convex hull is the minimum set of points which contains (not connects)
///   all of the points in a set and is convex.
//------------------------------------------------------------------------------
// TODO: Deprecated. Remove in major version change.
VecInt ConvexHullWithIndices(const std::vector<int>& a_points, BSHP<XmUGrid> a_ugrid)
{
  VecPt3d points3d(a_points.size());
  for (int i = 0; i < a_points.size(); ++i)
  {
    points3d.push_back(a_ugrid->GetPointLocation(a_points[i]));
  }
  VecPt3d convexHull = ConvexHull(points3d);
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
/// \brief Determine whether 2 line segments intersect (Deprecated).
/// \param[in] a_segment1: The first line segment
/// \param[in] a_segment2: The second line segment
/// \return true if the line segments intersect
//------------------------------------------------------------------------------
// TODO: Deprecated. Remove in major version change.
bool DoLineSegmentsCross(const std::pair<Pt3<double>, Pt3<double>>& a_segment1,
                         const std::pair<Pt3<double>, Pt3<double>>& a_segment2)
{
  return gmLinesCross(a_segment1.first, a_segment1.second, a_segment2.first,
                             a_segment2.second);;
} // DoLineSegmentsCross

//------------------------------------------------------------------------------
/// \brief Determine whether 2 line segments cross (Deprecated).
/// \param[in] a_segment1Point1: First point 3d of line segment 1
/// \param[in] a_segment1Point2: Second point 3d of line segment 1
/// \param[in] a_segment2Point1: First point 3d of line segment 2
/// \param[in] a_segment2Point2: Second point 3d of line segment 2
/// \return true if the line segments cross
//------------------------------------------------------------------------------
// TODO: Deprecated. Remove in major version change.
bool DoLineSegmentsCross(const Pt3<double>& a_segment1Point1,
                         const Pt3<double>& a_segment1Point2,
                         const Pt3<double>& a_segment2Point1,
                         const Pt3<double>& a_segment2Point2)
{
  return gmLinesCross(a_segment1Point1, a_segment1Point2, a_segment2Point1, a_segment2Point2);
} // DoLineSegmentsCross

} // namespace xms

#ifdef CXX_TEST
//------------------------------------------------------------------------------
// Unit Tests
//------------------------------------------------------------------------------
using namespace xms;
//#include <xmsgrid/ugrid/detail/XmGeometry.t.h>

#endif
