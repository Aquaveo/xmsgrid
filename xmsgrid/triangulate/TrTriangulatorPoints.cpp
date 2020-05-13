//------------------------------------------------------------------------------
/// \file
/// \ingroup triangulate
/// \copyright (C) Copyright Aquaveo 2018. Distributed under FreeBSD License
/// (See accompanying file LICENSE or https://aqaveo.com/bsd/license.txt)
//------------------------------------------------------------------------------

//----- Included files ---------------------------------------------------------

// 1. Precompiled header

// 2. My own header
#include <xmsgrid/triangulate/TrTriangulatorPoints.h>

// 3. Standard library headers

// 4. External library headers

// 5. Shared code headers
#include <xmscore/stl/vector.h>
#include <xmscore/misc/XmError.h>
#include <xmsgrid/geometry/geoms.h>
#include <xmscore/misc/Observer.h>
#include <xmsgrid/triangulate/triangles.h>

// 6. Non-shared code headers

//----- Forward declarations ---------------------------------------------------

//----- External globals -------------------------------------------------------

//----- Namespace declaration --------------------------------------------------

namespace xms
{
//----- Constants / Enumerations -----------------------------------------------

//----- Classes / Structs ------------------------------------------------------

//----- Internal functions -----------------------------------------------------

//----- Class / Function definitions -------------------------------------------

////////////////////////////////////////////////////////////////////////////////
/// \class TrTriangulatorPoints
/// \brief Class to triangulate simple points.
////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
/// \brief Triangulate Pt3ds returning triangles in a single 1D vector.
/// \param a_pts: The points to triangulate.
/// \param a_tris: 0-based indices into a_pts defining the triangles. Every
///                three elements defines a triangle. Size of num triangles * 3.
/// \param a_trisAdjToPts: 0-based triangles adjacent to points. Size of a_pts.
///                        Optional - include if you want this info.
///
/// The point and edge order is shown in the following figure:
///
/// \verbatim
///          2
///         / \
///        /   \
///      2/     \1     Point and edge numbering and order
///      /       \
///     /         \
///    0-----0-----1
/// \endverbatim
///
/// For example, the 0th point goes with the 0th edge and that edge
/// consists of points 0 and 1.
///
/// \verbatim
/// 10-        3-----------4
///   |       / \         / \
///   |      /   \   2   /   \
///   |     /     \     /     \
///   |    /   0   \   /   1   \
///   |   /         \ /         \
///  0-  0-----------1-----------2
///
///      |-----|-----|-----|-----|
///      0     5    10    15    20
///
/// a_tris          =  3,0,1,  1,2,4,  1,4,3
/// a_trisAdjToPts  = [0][0,1,2][1][0,2][1,2]
/// \endverbatim
//------------------------------------------------------------------------------
TrTriangulatorPoints::TrTriangulatorPoints(const VecPt3d& a_pts,
                                           VecInt& a_tris,
                                           VecInt2d* a_trisAdjToPts)
: m_pts(a_pts)
, m_idx(0)
, m_tris(a_tris)
, m_trisAdjToPts(a_trisAdjToPts)
, m_areaTol(-1)
, m_observer()
{
  UpdateAreaTolerance();
}
//------------------------------------------------------------------------------
/// \brief
//------------------------------------------------------------------------------
TrTriangulatorPoints::~TrTriangulatorPoints()
{
}
//------------------------------------------------------------------------------
/// \brief Set the observer to use for feedback while processing.
/// \param a_: The observer.
//------------------------------------------------------------------------------
void TrTriangulatorPoints::SetObserver(BSHP<Observer> a_)
{
  m_observer = a_;
} // TrTriangulatorPoints::SetObserver
//------------------------------------------------------------------------------
/// \brief Return the current point index (0-based).
/// \return The current point index.
//------------------------------------------------------------------------------
int TrTriangulatorPoints::GetID() const
{
  return m_idx;
}
//------------------------------------------------------------------------------
/// \brief Get location of current point.
/// \return Location of current point.
//------------------------------------------------------------------------------
Pt3d TrTriangulatorPoints::GetLocation() const
{
  return m_pts[m_idx];
}
//------------------------------------------------------------------------------
/// \brief Return the number of points to be triangulated.
/// \return Number of points to be triangulated.
//------------------------------------------------------------------------------
int TrTriangulatorPoints::GetNPoints() const
{
  return (int)m_pts.size();
}
//------------------------------------------------------------------------------
/// \brief Increment the current point index by 1.
//------------------------------------------------------------------------------
void TrTriangulatorPoints::IncrementPoint()
{
  ++m_idx;
}
//------------------------------------------------------------------------------
/// \brief Called just before triangles are created.
//------------------------------------------------------------------------------
void TrTriangulatorPoints::PrepareToReceiveTriangles()
{
  if (m_trisAdjToPts)
  {
    m_trisAdjToPts->resize(m_pts.size(), VecInt());
  }
} // TrTriangulatorPoints::PrepareToReceiveTriangles
//------------------------------------------------------------------------------
/// \brief Called after all triangles have been received.
//------------------------------------------------------------------------------
void TrTriangulatorPoints::FinalizeTriangulation()
{
  stShrinkCapacity(m_tris);
  if (m_trisAdjToPts)
  {
    stShrinkCapacity(*m_trisAdjToPts);
  }
} // TrTriangulatorPoints::FinalizeTriangulation
//------------------------------------------------------------------------------
/// \brief Receive a triangle consisting of the 3 points.
/// \param[in] a_id1: First point of triangle.
/// \param[in] a_id2: Second point of triangle.
/// \param[in] a_id3: Third point of triangle.
//------------------------------------------------------------------------------
void TrTriangulatorPoints::ReceiveTriangle(int a_id1, int a_id2, int a_id3)
{
  // make sure the triangle has positive area
  double area = trArea(m_pts[a_id1 - 1], m_pts[a_id2 - 1], m_pts[a_id3 - 1]);
  if (area < m_areaTol)
  {
    if (gmColinearWithTol(m_pts[a_id1 - 1], m_pts[a_id2 - 1], m_pts[a_id3 - 1],
                          m_areaTol))
    {
      return;
    }
  }

  m_tris.push_back(a_id1 - 1);
  m_tris.push_back(a_id2 - 1);
  m_tris.push_back(a_id3 - 1);

  if (m_trisAdjToPts)
  {
    int triIdx = ((int)m_tris.size() / 3) - 1;
    (*m_trisAdjToPts)[a_id1 - 1].push_back(triIdx);
    (*m_trisAdjToPts)[a_id2 - 1].push_back(triIdx);
    (*m_trisAdjToPts)[a_id3 - 1].push_back(triIdx);
  }
} // TrTriangulatorPoints::ReceiveTriangle
//------------------------------------------------------------------------------
/// \brief calculates the area tolerance
//------------------------------------------------------------------------------
void TrTriangulatorPoints::UpdateAreaTolerance()
{
  if (m_pts.empty())
    return;

  Pt3d ptMin(m_pts[0]), ptMax(m_pts[0]);
  for (const auto& p : m_pts)
    gmAddToExtents(p, ptMin, ptMax);
  m_areaTol = gmComputeXyTol(ptMin, ptMax);
  // areaTol is used to check if we should see if the points are colinear. So we
  // will set it to be equal to an XY tol

  // we don't do this anymore

  //m_areaTol *= m_areaTol;
  // this was originally m_areaTol *= 100. That seemed to work most of the time
  // but test_bug12336 is a case where it did not work so we changed the
  // tolerance to be multiplied by 1000
  //m_areaTol *= 1000;
} // TrTriangulatorPoints::UpdateAreaTolerance

} // namespace xms

#if CXX_TEST
////////////////////////////////////////////////////////////////////////////////
// UNIT TESTS
////////////////////////////////////////////////////////////////////////////////

#include <xmsgrid/triangulate/TrTriangulatorPoints.t.h>

#include <xmscore/testing/TestTools.h>
#include <xmsgrid/triangulate/detail/triangulate.h>

//----- Namespace declaration --------------------------------------------------

// namespace xms {
using namespace xms;

////////////////////////////////////////////////////////////////////////////////
/// \class TrTriangulatorPointsUnitTests
/// \brief Tests for TrTriangulatorPoints.
////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
/// \brief tests triangulating points
//------------------------------------------------------------------------------
void TrTriangulatorPointsUnitTests::test1()
{
  // 10-        3-----------4
  //   |       / \         / \
        //   |      /   \   2   /   \
        //   |     /     \     /     \
        //   |    /   0   \   /   1   \
        //   |   /         \ /         \
        //  0-  0-----------1-----------2
  //
  //      |-----|-----|-----|-----|
  //      0     5    10    15    20
  //
  // m_tris          =  3,0,1,  1,2,4,  1,4,3
  // m_trisAdjToPts  = [0][0,1,2][1][0,2][1,2]

  VecPt3d pts = {{0, 0, 0}, {10, 0, 0}, {20, 0, 0}, {5, 10, 0}, {15, 10, 0}};
  VecInt tris;
  VecInt2d trisAdjToPts;
  TrTriangulatorPoints client(pts, tris, &trisAdjToPts);
  trTriangulateIt(client);

  TS_ASSERT_EQUALS(tris.size(), 9);
  TS_ASSERT_EQUALS(tris[0], 3);
  TS_ASSERT_EQUALS(tris[1], 0);
  TS_ASSERT_EQUALS(tris[2], 1);
  TS_ASSERT_EQUALS(tris[3], 1);
  TS_ASSERT_EQUALS(tris[4], 2);
  TS_ASSERT_EQUALS(tris[5], 4);
  TS_ASSERT_EQUALS(tris[6], 1);
  TS_ASSERT_EQUALS(tris[7], 4);
  TS_ASSERT_EQUALS(tris[8], 3);

  TS_ASSERT_EQUALS(trisAdjToPts.size(), pts.size());
  TS_ASSERT_EQUALS((VecInt{0}), trisAdjToPts[0]);
  TS_ASSERT_EQUALS((VecInt{0, 1, 2}), trisAdjToPts[1]);
  TS_ASSERT_EQUALS((VecInt{1}), trisAdjToPts[2]);
  TS_ASSERT_EQUALS((VecInt{0, 2}), trisAdjToPts[3]);
  TS_ASSERT_EQUALS((VecInt{1, 2}), trisAdjToPts[4]);

} // TrTriangulatorPointsUnitTests::test1
//------------------------------------------------------------------------------
/// \brief tests triangulating points
//------------------------------------------------------------------------------
void TrTriangulatorPointsUnitTests::test_bug12336()
{
  VecPt3d pts = { 
    { 1149577.3999999999, 269746.50000000000, 262.60000000000002 },
    { 1149627.6000000001, 269588.40000000002, 262.60000000000002 },
    { 1149970.7503655001, 269500.66684485000, 262.60000000000002 },
    { 1149582.1655385382, 269748.01315644925, 262.60000000000002 },
    { 1149607.1846158644, 269755.95722780772, 241.59999999999974 },
    { 1149631.0330864443, 269592.03509524878, 262.60000000000002 },
    { 1149649.0567902755, 269611.11934530485, 241.59999999999974 },
    { 1149971.9888759241, 269505.51102609449, 262.60000000000002 },
    { 1149978.4910556506, 269530.94297762803, 241.59999999999974 },
    { 1149572.6344614616, 269744.98684355075, 262.60000000000002 },
    { 1149547.6153841354, 269737.04277219228, 241.59999999999974 },
    { 1149624.1669135559, 269584.76490475127, 262.60000000000002 },
    { 1149606.1432097247, 269565.68065469520, 241.59999999999974 },
    { 1149969.5118550761, 269495.82266360550, 262.60000000000002 },
    { 1149963.0096753496, 269470.39071207197, 241.59999999999974 }
  };

  VecInt tris;
  VecInt2d trisAdjToPts;
  TrTriangulatorPoints client(pts, tris, &trisAdjToPts);
  trTriangulateIt(client);
  
  VecInt baseTris = { 10, 12, 11, 11, 12, 14, 9, 10, 6, 0, 9, 6, 6, 3, 0, 6, 4,
                      3, 10, 11, 1, 6, 14, 13, 6, 13, 2, 6, 2, 7, 5, 6, 10, 1,
                      14, 5, 6, 8, 4, 6, 5, 14, 8, 6, 7, 5, 10, 1, 14, 1, 11 };
  TS_ASSERT_EQUALS_VEC(baseTris, tris);
} // TrTriangulatorPointsUnitTests::test_bug12336

  //} // namespace xms

#endif // CXX_TEST
