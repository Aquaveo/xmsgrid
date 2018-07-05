#pragma once
//------------------------------------------------------------------------------
/// \file XmConvexHull.cpp
/// \brief
/// \ingroup ugrid
/// \copyright (C) Copyright Aquaveo 2018. Distributed under the xmsng
///  Software License, Version 1.0. (See accompanying file
///  LICENSE_1_0.txt or copy at http://www.aquaveo.com/xmsng/LICENSE_1_0.txt)
//------------------------------------------------------------------------------

//----- Included files ---------------------------------------------------------

// 3. Standard library headers
#include <algorithm>

// 4. External library headers

// 5. Shared code headers
#include <xmscore/misc/base_macros.h>
#include <xmscore/misc/boost_defines.h>
#include <xmscore/stl/vector.h>

//----- Forward declarations ---------------------------------------------------

//----- Namespace declaration --------------------------------------------------
namespace xms
{

//----- Forward declarations ---------------------------------------------------
  class XmUGrid;

//----- Constants / Enumerations -----------------------------------------------


//----- Structs / Classes ------------------------------------------------------
  typedef double coord_t;         // coordinate type
  typedef double coord2_t;  // must be big enough to hold 2*max(|coordinate|)^2

//----- Function prototypes ----------------------------------------------------
  coord2_t cross(const Pt3d &a_origin, const Pt3d &a_A, const Pt3d &a_B);
  std::vector<Pt3d> ConvexHull(std::vector<Pt3d> a_points);
  VecInt ConvexHullWithIndices(const VecInt& a_points, BSHP<XmUGrid> a_ugrid);

} // namespace xms
