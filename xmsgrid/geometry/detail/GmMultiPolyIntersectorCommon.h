#pragma once
//------------------------------------------------------------------------------
/// \file
/// \brief Code shared by the GmMultiPolyIntersector implementations.
/// \ingroup geometry
/// \copyright (C) Copyright Aquaveo 2026. Distributed under FreeBSD License
/// (See accompanying file LICENSE or https://aquaveo.com/bsd/license.txt)
//------------------------------------------------------------------------------

//----- Include Files ----------------------------------------------------------

// 3. Standard Library Headers

// 4. External Library Headers

// 5. Shared Headers
#include <xmscore/points/ptsfwd.h> // VecPt3d
#include <xmscore/stl/vector.h>    // VecInt, VecDbl

// 6. Non-shared Headers

//----- Namespace declaration --------------------------------------------------

namespace xms
{
//----- Typdefs / Classes ------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
/// \brief Sets gmXyTol() for the guard's lifetime and restores the previous
///        value when the guard is destroyed, including by an exception.
class GmXyTolGuard
{
public:
  explicit GmXyTolGuard(double a_tol);
  ~GmXyTolGuard();
  GmXyTolGuard(const GmXyTolGuard&) = delete;
  GmXyTolGuard& operator=(const GmXyTolGuard&) = delete;

private:
  double m_previousTol; ///< gmXyTol() when the guard was created
}; // class GmXyTolGuard

//----- Function Prototypes ----------------------------------------------------

void gmRemoveDuplicateTValues(VecInt& a_polyIds, VecDbl& a_tValues, VecPt3d& a_pts);

} // namespace xms
