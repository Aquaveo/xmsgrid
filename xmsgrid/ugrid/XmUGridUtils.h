#pragma once
//------------------------------------------------------------------------------
/// \file XmUGridUtils.h
/// \brief Contains IO functions as well as several utility functions for XmUGrid
/// \ingroup ugrid
/// \copyright (C) Copyright Aquaveo 2018. Distributed under the xmsng
///  Software License, Version 1.0. (See accompanying file
///  LICENSE_1_0.txt or copy at http://www.aquaveo.com/xmsng/LICENSE_1_0.txt)
//------------------------------------------------------------------------------

//----- Included files ---------------------------------------------------------

// 3. Standard library headers

// 4. External library headers

// 5. Shared code headers
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

// IO
BSHP<XmUGrid> XmReadUGridFromAsciiFile(const std::string& a_filePath);
void XmWriteUGridToAsciiFile(BSHP<XmUGrid> a_ugrid, const std::string& a_filePath);

// Utility functions
double cross(const Pt3d& a_origin, const Pt3d& a_A, const Pt3d& a_B);

bool DoLineSegmentsCross(const std::pair<Pt3d, Pt3d>& a_segment1,
                         const std::pair<Pt3d, Pt3d>& a_segment2);
bool DoLineSegmentsCross(const Pt3d& a_segment1Point1,
                         const Pt3d& a_segment1Point2,
                         const Pt3d& a_segment2Point1,
                         const Pt3d& a_segment2Point2);

} // namespace xms
