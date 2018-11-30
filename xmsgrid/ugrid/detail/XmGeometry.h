#pragma once
//------------------------------------------------------------------------------
/// \file
/// \brief Code to calculate the convex hull of a set of points in two dimensions.
/// \ingroup ugrid
/// \copyright (C) Copyright Aquaveo 2018. Distributed under FreeBSD License
/// (See accompanying file LICENSE or https://aqaveo.com/bsd/license.txt)
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

/// XMS Namespace
namespace xms
{
//----- Forward declarations ---------------------------------------------------
class XmUGrid;

//----- Constants / Enumerations -----------------------------------------------

//----- Structs / Classes ------------------------------------------------------

//----- Function prototypes ----------------------------------------------------
std::vector<Pt3d> ConvexHull(std::vector<Pt3d> a_points);
VecInt ConvexHullWithIndices(const VecInt& a_points, BSHP<XmUGrid> a_ugrid);

bool DoLineSegmentsCross(const std::pair<Pt3d, Pt3d>& a_segment1,
                         const std::pair<Pt3d, Pt3d>& a_segment2);
bool DoLineSegmentsCross(const Pt3d& a_segment1Point1,
                         const Pt3d& a_segment1Point2,
                         const Pt3d& a_segment2Point1,
                         const Pt3d& a_segment2Point2);

} // namespace xms
