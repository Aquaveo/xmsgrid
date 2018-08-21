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

// 4. External library headers

// 5. Shared code headers
#include <xmscore/misc/base_macros.h>
#include <xmscore/misc/boost_defines.h>
#include <xmscore/stl/vector.h>

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
  XmEdge(int a_idx1, int a_idx2, bool a_sorted = false);
  XmEdge(const std::pair<int, int>& a_edge);

  bool operator<(const XmEdge& a_rhs) const;
  bool operator==(const XmEdge& a_rhs) const;

  int GetFirst() const;
  void SetFirst(int a_idx);
  int GetSecond() const;
  void SetSecond(int a_idx);
  bool IsEquivalent(const XmEdge& a_edge) const;
  void SortIndexes();

private:
  int m_idx1;
  int m_idx2;
};

//----- Function prototypes ----------------------------------------------------


} // namespace xms
