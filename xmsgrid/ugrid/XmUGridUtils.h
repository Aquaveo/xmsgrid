#pragma once
//------------------------------------------------------------------------------
/// \file XmUGridUtils.h
/// \brief Contains IO functions as well as several utility functions for XmUGrid
/// \ingroup ugrid
/// \copyright (C) Copyright Aquaveo 2018. Distributed under FreeBSD License
/// (See accompanying file LICENSE or https://aqaveo.com/bsd/license.txt)
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
BSHP<XmUGrid> XmReadUGridFromStream(std::istream& a_istream);
void XmWriteUGridToAsciiFile(BSHP<XmUGrid> a_ugrid, const std::string& a_filePath);
void XmWriteUGridToStream(BSHP<XmUGrid> a_ugrid, std::ostream& a_ostream);

} // namespace xms
