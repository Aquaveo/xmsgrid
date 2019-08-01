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

// !!!Deprecated!!!
std::vector<Pt3d> ConvexHull(const std::vector<Pt3<double>>& a_points);

// !!!Deprecated!!!
VecInt ConvexHullWithIndices(const std::vector<int>& a_points, std::shared_ptr<XmUGrid> a_ugrid);

// !!!Deprecated!!!
bool DoLineSegmentsCross(const std::pair<Pt3<double>, Pt3<double>>& a_segment1,
                         const std::pair<Pt3<double>, Pt3<double>>& a_segment2);

// !!!Deprecated!!!
bool DoLineSegmentsCross(const Pt3<double>& a_segment1Point1,
                         const Pt3<double>& a_segment1Point2,
                         const Pt3<double>& a_segment2Point1,
                         const Pt3<double>& a_segment2Point2);

} // namespace xms
