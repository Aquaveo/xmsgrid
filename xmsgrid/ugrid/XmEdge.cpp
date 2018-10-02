//------------------------------------------------------------------------------
/// \file
/// \ingroup ugrid
/// \copyright (C) Copyright Aquaveo 2018.
//------------------------------------------------------------------------------

//----- Included files ---------------------------------------------------------

// 1. Precompiled header

// 2. My own header
#include <xmsgrid/ugrid/XmEdge.h>

// 3. Standard library headers
#include <algorithm>

// 4. External library headers

// 5. Shared code headers

// 6. Non-shared code headers

//----- Forward declarations ---------------------------------------------------

//----- External globals -------------------------------------------------------

//----- Namespace declaration --------------------------------------------------

/// XMS Namespace
namespace xms
{
//----- Constants / Enumerations -----------------------------------------------

//----- Classes / Structs ------------------------------------------------------

//----- Internal functions -----------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
/// \class XmEdge
/// \brief Two integer values representing an edge of an XmUGrid. By default
///        has a direction. Can be sorted to have minimum index first.
////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
/// \brief Default constructor.
//------------------------------------------------------------------------------
XmEdge::XmEdge()
: m_pt1(0)
, m_pt2(0)
{
} // XmEdge::XmEdge
//------------------------------------------------------------------------------
/// \brief Constructor
/// \param[in] a_pt1 The first index.
/// \param[in] a_pt2 The second index.
/// \param[in] a_sorted If true set the first index to be the minimum index.
//------------------------------------------------------------------------------
XmEdge::XmEdge(int a_pt1, int a_pt2, bool a_sorted /* =false */)
: m_pt1(a_pt1)
, m_pt2(a_pt2)
{
  if (a_sorted)
    SortIndexes();
} // XmEdge::XmEdge
//------------------------------------------------------------------------------
/// \brief Constructor
/// \param[in] a_edge The edge as an int pair.
//------------------------------------------------------------------------------
XmEdge::XmEdge(const std::pair<int, int>& a_edge)
: m_pt1(a_edge.first)
, m_pt2(a_edge.second)
{
} // XmEdge::XmEdge
//------------------------------------------------------------------------------
/// \brief Less than operator by first index then second.
/// \param[in] a_rhs The edge to compare against.
/// \return true if this edge is less than a_rhs.
//------------------------------------------------------------------------------
bool XmEdge::operator<(const XmEdge& a_rhs) const
{
  if (m_pt1 < a_rhs.m_pt1)
    return true;
  else if (m_pt1 > a_rhs.m_pt1)
    return false;
  else if (m_pt2 < a_rhs.m_pt2)
    return true;
  else
    return false;
} // XmEdge::operator<
//------------------------------------------------------------------------------
/// \brief Equals operator.
/// \param[in] a_rhs The edge to compare against.
/// \return true if edges are equal.
//------------------------------------------------------------------------------
bool XmEdge::operator==(const XmEdge& a_rhs) const
{
  return m_pt1 == a_rhs.m_pt1 && m_pt2 == a_rhs.m_pt2;
} // XmEdge::operator==
//------------------------------------------------------------------------------
/// \brief Get the first index.
/// \return The first index.
//------------------------------------------------------------------------------
int XmEdge::GetFirst() const
{
  return m_pt1;
} // XmEdge::GetFirst
//------------------------------------------------------------------------------
/// \brief Set the first index.
/// \param[in] a_pt1 The first index.
//------------------------------------------------------------------------------
void XmEdge::SetFirst(int a_pt1)
{
  m_pt1 = a_pt1;
} // XmEdge::SetFirst
//------------------------------------------------------------------------------
/// \brief Get the second index.
/// \return The second index.
//------------------------------------------------------------------------------
int XmEdge::GetSecond() const
{
  return m_pt2;
} // XmEdge::GetSecond
//------------------------------------------------------------------------------
/// \brief Set the second index.
/// \param[in] a_pt2 The second index.
//------------------------------------------------------------------------------
void XmEdge::SetSecond(int a_pt2)
{
  m_pt2 = a_pt2;
} // XmEdge::SetSecond
//------------------------------------------------------------------------------
/// \brief Test if edge is the same ignoring direction.
/// \param a_edge The edge to compare against.
/// \return True if edges are same when indexes are in sorted order.
//------------------------------------------------------------------------------
bool XmEdge::IsEquivalent(const XmEdge& a_edge) const
{
  int lhsIdx1 = std::min(m_pt1, m_pt2);
  int lhsIdx2 = std::max(m_pt1, m_pt2);
  int rhsIdx1 = std::min(a_edge.m_pt1, a_edge.m_pt2);
  int rhsIdx2 = std::max(a_edge.m_pt1, a_edge.m_pt2);
  return lhsIdx1 == rhsIdx1 && lhsIdx2 == rhsIdx2;
} // XmEdge::IsEquivalent
//------------------------------------------------------------------------------
/// \brief Sort the indexes so minimum index is first.
//------------------------------------------------------------------------------
void XmEdge::SortIndexes()
{
  if (m_pt1 > m_pt2)
    std::swap(m_pt1, m_pt2);
} // XmEdge::SortIndexes

} // namespace xms

#ifdef CXX_TEST
//------------------------------------------------------------------------------
// Unit Tests
//------------------------------------------------------------------------------
using namespace xms;
#include <xmsgrid/ugrid/XmEdge.t.h>

////////////////////////////////////////////////////////////////////////////////
/// \class XmEdgeUnitTests
/// \brief Test XmEdge class.
////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
/// \brief Test XmEdge less than operator.
//------------------------------------------------------------------------------
void XmEdgeUnitTests::testLessThanOperator()
{
  XmEdge edge1(0, 1);
  XmEdge edge1a(1, 0);
  XmEdge edge2(1, 2);
  TS_ASSERT(edge1 < edge2);
  TS_ASSERT(edge1 < edge1a);
  TS_ASSERT(!(edge1a < edge1));
  TS_ASSERT(!(edge2 < edge1));
} // XmEdgeUnitTests::testLessThanOperator
//------------------------------------------------------------------------------
/// \brief Test XmEdge equals operator.
//------------------------------------------------------------------------------
void XmEdgeUnitTests::testEqualsOperator()
{
  XmEdge edge1(0, 1);
  XmEdge edge1a(1, 0, false);
  XmEdge edge1b(1, 0, true);
  XmEdge edge2(1, 2);
  TS_ASSERT(edge1 == edge1);
  TS_ASSERT(!(edge1 == edge1a));
  TS_ASSERT(edge1 == edge1b);
  TS_ASSERT(!(edge2 == edge1));
} // XmEdgeUnitTests::testEqualsOperator
//------------------------------------------------------------------------------
/// \brief Test XmEdge::IsEquivalent.
//------------------------------------------------------------------------------
void XmEdgeUnitTests::testIsEquivalent()
{
  XmEdge edge1(0, 1);
  XmEdge edge1a(1, 0);
  XmEdge edge2(1, 2);
  TS_ASSERT(edge1.IsEquivalent(edge1a));
  TS_ASSERT(!(edge1 == edge1a));
  TS_ASSERT(edge1a.IsEquivalent(edge1));
  TS_ASSERT(!edge1.IsEquivalent(edge2));
} // XmEdgeUnitTests::testIsEquivalent

#endif
