#pragma once
//------------------------------------------------------------------------------
/// \file
/// \ingroup geometry
/// \copyright (C) Copyright Aquaveo 2018. Distributed under FreeBSD License
/// (See accompanying file LICENSE or https://aqaveo.com/bsd/license.txt)
//------------------------------------------------------------------------------

//----- Included files ---------------------------------------------------------

// 3. Standard library headers
#include <vector>

// 5. Shared code headers
#include <xmscore/misc/base_macros.h> // for XM_DISALLOW_COPY_AND_ASSIGN
#include <xmscore/misc/boost_defines.h>
#include <xmscore/points/ptsfwd.h> // for Pt3d

//----- Namespace --------------------------------------------------------------

namespace xms
{
//----- Forward declarations ---------------------------------------------------

class GmMultiPolyIntersectionSorter;

//----- Classes ----------------------------------------------------------------

/// Type of query
enum GmMultiPolyIntersectorQueryEnum { GMMPIQ_COVEREDBY, GMMPIQ_INTERSECTS };

////////////////////////////////////////////////////////////////////////////////
class GmMultiPolyIntersector
{
public:
  static boost::shared_ptr<GmMultiPolyIntersector> New(
    const std::vector<Pt3d>& a_points,
    const std::vector<std::vector<int> >& a_polys,
    boost::shared_ptr<GmMultiPolyIntersectionSorter> a_sorter,
    int a_startingId = 1);
  /// \cond

  virtual void SetQuery(GmMultiPolyIntersectorQueryEnum a_query) = 0;
  virtual void TraverseLineSegment(double a_x1,
                                   double a_y1,
                                   double a_x2,
                                   double a_y2,
                                   std::vector<int>& a_polyids,
                                   std::vector<double>& a_tvalues) = 0;
  virtual void TraverseLineSegment(double a_x1,
                                   double a_y1,
                                   double a_x2,
                                   double a_y2,
                                   std::vector<int>& a_polyids) = 0;
  virtual void TraverseLineSegment(double a_x1,
                                   double a_y1,
                                   double a_x2,
                                   double a_y2,
                                   std::vector<int>& a_polyids,
                                   std::vector<Pt3d>& a_pts) = 0;
  virtual void TraverseLineSegment(double a_x1,
                                   double a_y1,
                                   double a_x2,
                                   double a_y2,
                                   std::vector<int>& a_polyids,
                                   std::vector<double>& a_tvalues,
                                   std::vector<Pt3d>& a_pts) = 0;
  virtual int PolygonFromPoint(const Pt3d& a_pt) = 0;

  /// \endcond
protected:
  GmMultiPolyIntersector();
  virtual ~GmMultiPolyIntersector();

private:
  XM_DISALLOW_COPY_AND_ASSIGN(GmMultiPolyIntersector)

}; // class GmMultiPolyIntersector

} // namespace xms