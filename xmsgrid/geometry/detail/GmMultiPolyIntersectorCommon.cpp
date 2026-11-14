//------------------------------------------------------------------------------
/// \file
/// \ingroup geometry
/// \copyright (C) Copyright Aquaveo 2026. Distributed under FreeBSD License
/// (See accompanying file LICENSE or https://aquaveo.com/bsd/license.txt)
//------------------------------------------------------------------------------

//----- Included files ---------------------------------------------------------

// 1. Precompiled header

// 2. My own header
#include <xmsgrid/geometry/detail/GmMultiPolyIntersectorCommon.h>

// 3. Standard library headers
#include <algorithm>
#include <functional>

// 4. External library headers

// 5. Shared code headers
#include <xmscore/math/math.h>      // GTEQ_TOL
#include <xmscore/misc/xmstype.h>   // XM_ZERO_TOL
#include <xmscore/points/pt.h>      // Pt3d
#include <xmsgrid/geometry/geoms.h> // gmXyTol

//----- Namespace declaration --------------------------------------------------

namespace xms
{
//----- Class / Function definitions -------------------------------------------

////////////////////////////////////////////////////////////////////////////////
/// \class GmXyTolGuard
////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
/// \brief Remember the current gmXyTol() and replace it with a_tol.
/// \param a_tol: The tolerance to use until the guard is destroyed.
//------------------------------------------------------------------------------
GmXyTolGuard::GmXyTolGuard(double a_tol)
: m_previousTol(gmXyTol())
{
  gmXyTol(true, a_tol);
} // GmXyTolGuard::GmXyTolGuard
//------------------------------------------------------------------------------
/// \brief Restore the gmXyTol() that was current when the guard was created.
//------------------------------------------------------------------------------
GmXyTolGuard::~GmXyTolGuard()
{
  gmXyTol(true, m_previousTol);
} // GmXyTolGuard::~GmXyTolGuard
//------------------------------------------------------------------------------
/// \brief Removes duplicate T Values and updates the polygon ID and point vectors
/// \param a_polyIds: list of polygons intersected by line segment. Can be zero
///                  or 1 based depending on a_startingId passed to constructor.
/// \param a_tValues: Values from 0.0 to 1.0 representing where on the line
///                  segment the intersection with the polygon in polyids
///                  occurs. If there are any t values there are always at
///                  least 2 and all represent where the line enters the
///                  polygon, except the last which represents where it exited.
///                  There would therefore be one more t value than poly id
///                  but we make the sizes equal by always making the last
///                  poly id -1.
/// \param a_pts: Intersection points.
//------------------------------------------------------------------------------
void gmRemoveDuplicateTValues(VecInt& a_polyIds, VecDbl& a_tValues, VecPt3d& a_pts)
{
  VecInt indexesToRemove;
  int size((int)a_tValues.size());
  for (int i = size - 1; i > 0; --i)
  {
    // Check for multiple T-values close to 1.0 (at the end of the line segment).
    if (GTEQ_TOL(a_tValues[i], 1.0, XM_ZERO_TOL) && GTEQ_TOL(a_tValues[i - 1], 1.0, XM_ZERO_TOL))
    {
      for (int j = i - 1; j > 0; --j)
      {
        // If the T-values are 1.0 and the polygon IDs are the same (for example, -1), go ahead and
        // remove these intersections
        if (GTEQ_TOL(a_tValues[i], 1.0, XM_ZERO_TOL) && GTEQ_TOL(a_tValues[j], 1.0, XM_ZERO_TOL) &&
            a_polyIds[i] == a_polyIds[j])
          indexesToRemove.push_back(j);
      }
    }
    else if (a_polyIds[i] == -1 && a_polyIds[i - 1] == -1)
    {
      // Remove excess "end" (-1) polygon IDs
      for (int j = i - 1; j > 0; --j)
      {
        // Use 0.1 for the tolerance here because you have multiple end points and
        // there really should only be a single end point unless your T-value is less
        // than 0.9 and you've gone outside the mesh.
        if (GTEQ_TOL(a_tValues[i], 1.0, 0.1) && GTEQ_TOL(a_tValues[j], 1.0, 0.1) &&
            a_polyIds[j] == -1)
          indexesToRemove.push_back(j);
      }
    }
    else
      break;
  }
  if (!indexesToRemove.empty())
  {
    // Each trailing entry appended its own descending run of indexes, so an
    // index can appear in several runs. Erase each one once, highest first, so
    // an erase never shifts an index still waiting to be erased.
    std::sort(indexesToRemove.begin(), indexesToRemove.end(), std::greater<int>());
    auto it = std::unique(indexesToRemove.begin(), indexesToRemove.end());
    indexesToRemove.erase(it, indexesToRemove.end());
    for (int i : indexesToRemove)
    {
      a_polyIds.erase(a_polyIds.begin() + i);
      a_tValues.erase(a_tValues.begin() + i);
      a_pts.erase(a_pts.begin() + i);
    }
  }
} // gmRemoveDuplicateTValues

} // namespace xms

#ifdef CXX_TEST
////////////////////////////////////////////////////////////////////////////////
// UNIT TESTS
////////////////////////////////////////////////////////////////////////////////

#include <xmsgrid/geometry/detail/GmMultiPolyIntersectorCommon.t.h>

#include <stdexcept>

#include <xmscore/testing/TestTools.h>

////////////////////////////////////////////////////////////////////////////////
/// \class GmMultiPolyIntersectorCommonUnitTests
/// \brief Tests for the code the GmMultiPolyIntersector implementations share.
////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
/// \brief Four trailing intersections at t = 1.0 that share an id.
///
/// Each one appends a run of indexes to remove, so indexes 2 and 1 are listed
/// more than once and not next to each other. Erasing an index twice used to
/// erase past the end of the vectors.
//------------------------------------------------------------------------------
void GmMultiPolyIntersectorCommonUnitTests::testRemoveDuplicateTValuesManyAtOne()
{
  xms::VecInt polyIds = {5, -1, -1, -1, -1};
  xms::VecDbl tValues = {0.0, 1.0, 1.0, 1.0, 1.0};
  xms::VecPt3d pts = {{0, 0, 0}, {1, 0, 0}, {2, 0, 0}, {3, 0, 0}, {4, 0, 0}};
  xms::gmRemoveDuplicateTValues(polyIds, tValues, pts);
  xms::VecInt expectedIds = {5, -1};
  xms::VecDbl expectedTvals = {0.0, 1.0};
  xms::VecPt3d expectedPoints = {{0, 0, 0}, {4, 0, 0}};
  TS_ASSERT_EQUALS_VEC(expectedIds, polyIds);
  TS_ASSERT_DELTA_VEC(expectedTvals, tValues, 1e-12);
  TS_ASSERT_DELTA_VECPT3D(expectedPoints, pts, 1e-12);
} // GmMultiPolyIntersectorCommonUnitTests::testRemoveDuplicateTValuesManyAtOne
//------------------------------------------------------------------------------
/// \brief Four trailing end (-1) ids near, but not at, t = 1.0.
///
/// Exercises the second removal branch, which collects indexes the same way.
//------------------------------------------------------------------------------
void GmMultiPolyIntersectorCommonUnitTests::testRemoveDuplicateTValuesManyEndIds()
{
  xms::VecInt polyIds = {5, -1, -1, -1, -1};
  xms::VecDbl tValues = {0.0, 0.95, 0.96, 0.97, 0.98};
  xms::VecPt3d pts = {{0, 0, 0}, {1, 0, 0}, {2, 0, 0}, {3, 0, 0}, {4, 0, 0}};
  xms::gmRemoveDuplicateTValues(polyIds, tValues, pts);
  xms::VecInt expectedIds = {5, -1};
  xms::VecDbl expectedTvals = {0.0, 0.98};
  xms::VecPt3d expectedPoints = {{0, 0, 0}, {4, 0, 0}};
  TS_ASSERT_EQUALS_VEC(expectedIds, polyIds);
  TS_ASSERT_DELTA_VEC(expectedTvals, tValues, 1e-12);
  TS_ASSERT_DELTA_VECPT3D(expectedPoints, pts, 1e-12);
} // GmMultiPolyIntersectorCommonUnitTests::testRemoveDuplicateTValuesManyEndIds
//------------------------------------------------------------------------------
/// \brief GmXyTolGuard restores gmXyTol() when an exception leaves its scope.
//------------------------------------------------------------------------------
void GmMultiPolyIntersectorCommonUnitTests::testXyTolGuardRestoresOnThrow()
{
  const double before = xms::gmXyTol();
  try
  {
    xms::GmXyTolGuard guard(0.125);
    TS_ASSERT_EQUALS(0.125, xms::gmXyTol());
    throw std::runtime_error("unwind");
  }
  catch (const std::runtime_error&)
  {
  }
  TS_ASSERT_EQUALS(before, xms::gmXyTol());
} // GmMultiPolyIntersectorCommonUnitTests::testXyTolGuardRestoresOnThrow

#endif // CXX_TEST
