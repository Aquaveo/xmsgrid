#pragma once
//------------------------------------------------------------------------------
/// \file
/// \ingroup geometry
/// \copyright (C) Copyright Aquaveo 2018. Distributed under FreeBSD License
/// (See accompanying file LICENSE or https://aquaveo.com/bsd/license.txt)
//------------------------------------------------------------------------------

//----- Included files ---------------------------------------------------------

// 3. Standard Library Headers

// 4. External Library Headers

// 5. Shared Headers
#include <xmsgrid/geometry/GmMultiPolyIntersectionSorter.h>

// 6. Non-shared Headers

//----- Namespace --------------------------------------------------------------

namespace xms {
//----- Forward declarations ---------------------------------------------------

struct GmMultiPolyIntersectorData;
class ix;

//----- Classes ----------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
class GmMultiPolyIntersectionSorterTerse
    : public GmMultiPolyIntersectionSorter {
public:
  virtual void Sort(GmMultiPolyIntersectorData &a_data,
                    std::vector<int> &polyids, std::vector<double> &tvalues,
                    std::vector<Pt3d> &a_pts, double a_tol) override;

private:
  void FixTValueAtDuplicateXy();
  void RemoveCornerTouches();
  void RemoveDuplicateEdges();
  void SwapAdjacents();
  void AddMissingEndpointIds(const std::vector<int>& a_tChange);
  void IntersectionsToPolyIdsAndTValuesFor2(std::vector<int> &polyids,
                                            std::vector<double> &tvalues,
                                            std::vector<Pt3d> &a_pts) const;
  void
  IntersectionsToPolyIdsAndTValuesFor3OrMore(std::vector<int> &polyids,
                                             std::vector<double> &tvalues,
                                             std::vector<Pt3d> &a_pts) const;
  void IntersectionsToPolyIdsAndTValues(std::vector<int> &polyids,
                                        std::vector<double> &tvalues,
                                        std::vector<Pt3d> &a_pts) const;
  void FixArrays(std::vector<int> &polyids, std::vector<double> &tvalues,
                 std::vector<Pt3d> &a_pts) const;
  void AddToPolyIdsAndTValues(const ix &a_ix, std::vector<int> &polyids,
                              std::vector<double> &tvalues,
                              std::vector<Pt3d> &a_pts) const;
  void FindPreviousNextNeither(const std::vector<int> &tChange, const int idx,
                               std::vector<int> *inPrev,
                               std::vector<int> *inNext,
                               std::vector<int> *inNeither) const;
  void Swap(int a, int b);
  void FindWhereTValuesChange(std::vector<int> &tChange) const;

private:
  GmMultiPolyIntersectorData
      *m_d;     ///< Intersection data from GmMultiPolyIntersector
  double m_tol; ///< Tolerance used when comparing t values.

}; // class GmMultiPolyIntersectionSorterTerse

} // namespace xms
