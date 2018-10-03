#pragma once
//------------------------------------------------------------------------------
/// \file XmUGrid.h
/// \brief Contains the XmUGrid Class and supporting data types.
/// \ingroup ugrid
/// \copyright (C) Copyright Aquaveo 2018. Distributed under the xmsng
///  Software License, Version 1.0. (See accompanying file
///  LICENSE_1_0.txt or copy at http://www.aquaveo.com/xmsng/LICENSE_1_0.txt)
//------------------------------------------------------------------------------

//----- Included files ---------------------------------------------------------

// 3. Standard library headers
#include <utility>

// 4. External library headers

// 5. Shared code headers

//----- Forward declarations ---------------------------------------------------

//----- Namespace declaration --------------------------------------------------

/// XMS Namespace
namespace xms
{
//----- Forward declarations ---------------------------------------------------

//----- Constants / Enumerations -----------------------------------------------

//----- Structs / Classes ------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
class XmEdge
{
public:
  XmEdge();
  XmEdge(int a_pt1, int a_pt2, bool a_sorted = false);
  explicit XmEdge(const std::pair<int, int>& a_edge);

  bool operator<(const XmEdge& a_rhs) const;
  bool operator==(const XmEdge& a_rhs) const;

  int GetFirst() const;
  void SetFirst(int a_pt1);
  int GetSecond() const;
  void SetSecond(int a_pt2);
  bool IsEquivalent(const XmEdge& a_edge) const;
  void SortIndexes();

private:
  int m_pt1; ///< First point on the edge.
  int m_pt2; ///< Second point on the edge.
};

//----- Function prototypes ----------------------------------------------------

} // namespace xms
