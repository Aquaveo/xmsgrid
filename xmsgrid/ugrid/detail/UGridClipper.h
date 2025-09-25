#pragma once
//------------------------------------------------------------------------------
/// \file
/// \brief Code to remove points and cells outside of a polygon.
/// \ingroup ugrid
/// \copyright (C) Copyright Aquaveo 2022. Distributed under FreeBSD License
/// (See accompanying file LICENSE or https://aquaveo.com/bsd/license.txt)
//------------------------------------------------------------------------------

//----- Included files ---------------------------------------------------------

// 3. Standard library headers
#include <memory>

// 4. External library headers

// 5. Shared code headers
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
std::shared_ptr<XmUGrid> XmClipUGrid(std::shared_ptr<XmUGrid> a_ugrid, const VecInt2d& a_loops);
} // namespace xms
