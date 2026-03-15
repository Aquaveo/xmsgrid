#pragma once
//------------------------------------------------------------------------------
/// \file
/// \ingroup geometry
/// \copyright (C) Copyright Aquaveo 2018. Distributed under FreeBSD License
/// (See accompanying file LICENSE or https://aqaveo.com/bsd/license.txt)
//------------------------------------------------------------------------------

//----- Included files ---------------------------------------------------------

// 3. Standard library headers
#include <memory>

// 5. Shared code headers
#include <xmsgrid/geometry/GmMultiPolyIntersector.h>

//----- Forward declarations ---------------------------------------------------

namespace xms
{
class XmUGrid;
}

//----- Namespace --------------------------------------------------------------

namespace xms
{
//------------------------------------------------------------------------------
/// \brief Edge-walk implementation of GmMultiPolyIntersector.
///
/// Uses XmUGrid adjacency to walk cell-by-cell through the mesh instead of
/// intersecting the line against every candidate polygon and sorting.
//------------------------------------------------------------------------------
class GmMultiPolyIntersectorEdgeWalk : public GmMultiPolyIntersector
{
public:
  GmMultiPolyIntersectorEdgeWalk(std::shared_ptr<XmUGrid> a_ugrid, int a_startingId = 1);
  ~GmMultiPolyIntersectorEdgeWalk() override;

  void SetQuery(GmMultiPolyIntersectorQueryEnum a_query) override;
  void TraverseLineSegment(double a_x1,
                           double a_y1,
                           double a_x2,
                           double a_y2,
                           std::vector<int>& a_polyIds,
                           std::vector<double>& a_tValues) override;
  void TraverseLineSegment(double a_x1,
                           double a_y1,
                           double a_x2,
                           double a_y2,
                           std::vector<int>& a_polyIds) override;
  void TraverseLineSegment(double a_x1,
                           double a_y1,
                           double a_x2,
                           double a_y2,
                           std::vector<int>& a_polyIds,
                           std::vector<Pt3d>& a_pts) override;
  void TraverseLineSegment(double a_x1,
                           double a_y1,
                           double a_x2,
                           double a_y2,
                           std::vector<int>& a_polyIds,
                           std::vector<double>& a_tValues,
                           std::vector<Pt3d>& a_pts) override;
  int PolygonFromPoint(const Pt3d& a_pt) override;

private:
  class Impl;
  std::unique_ptr<Impl> m_impl;
};

} // namespace xms
