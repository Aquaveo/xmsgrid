//------------------------------------------------------------------------------
/// \file
/// \ingroup ugrid
/// \copyright (C) Copyright Aquaveo 2022. Distributed under FreeBSD License
/// (See accompanying file LICENSE or https://aquaveo.com/bsd/license.txt)
//------------------------------------------------------------------------------

//----- Included files ---------------------------------------------------------

// 1. Precompiled header

// 2. My own header
#include <xmsgrid/ugrid/detail/UGridClipper.h>

// 3. Standard library headers

// 4. External library headers

// 5. Shared code headers
#include <xmscore/misc/XmError.h>

#include <xmsgrid/geometry/geoms.h>
#include <xmsgrid/ugrid/XmEdge.h>
#include <xmsgrid/ugrid/XmUGrid.h>
#include <xmsgrid/ugrid/XmUGridUtils.h>

// 6. Non-shared code headers

//----- Forward declarations ---------------------------------------------------

//----- External globals -------------------------------------------------------

//----- Namespace declaration --------------------------------------------------

/// XMS Namespace
namespace xms
{
//----- Constants / Enumerations -----------------------------------------------

//----- Classes / Structs ------------------------------------------------------

//----- Internal functions -----------------------------------------------------
namespace
{
//------------------------------------------------------------------------------
/// \brief Get the indices of the cells on the left and right side of an edge.
/// \param a_ugrid: XmUGrid to get indices from.
/// \param a_a: Index of first point on edge.
/// \param a_b: Index of second point on edge.
/// \param a_left: Initialized to index of left cell, or -1 if none.
/// \param a_right: Initialized to index of right cell, or -1 if none.
//------------------------------------------------------------------------------
void iGetLeftRightCells(std::shared_ptr<XmUGrid> a_ugrid, int a_a, int a_b, int& a_left, int& a_right)
{
  VecInt cells;
  a_ugrid->GetEdgeAdjacentCells(XmEdge(a_a, a_b), cells);

  // Tentative guess
  XM_ASSERT(cells.size() > 0);
  int left = cells[0];
  int right = cells.size() > 1 ? cells[1] : -1;
  int opposite = -1;

  VecInt points;
  a_ugrid->GetCellPoints(left, points);
  // Not sure it's possible to tell left/right on non-triangles.
  // We didn't need it yet so I didn't implement it.
  XM_ASSERT(points.size() == 3);

  for (const auto& point : points)
  {
    if (point != a_a && point != a_b)
    {
      opposite = point;
      break;
    }
  }

  const VecPt3d& locations = a_ugrid->GetLocations();

  if (!gmStrictlyLeftTurn(&locations[a_a], &locations[a_b], &locations[opposite]))
  {
    // Guess was wrong
    int temp = left;
    left = right;
    right = temp;
  }

  a_left = left;
  a_right = right;
} // iGetLeftRightCells

//------------------------------------------------------------------------------
/// \brief Mark cells on either side of a single edge on a loop.
/// \param a_goodCell: Index of the good cell.
/// \param a_badCell: Index of the bad cell.
/// \param a_visited: Visited flags for the grid.
/// \param a_good: Good flags for the grid.
/// \param a_check: Cells that should be checked for neighbors.
//------------------------------------------------------------------------------
void iMarkEdgeOnLoop(int a_goodCell,
                     int a_badCell,
                     VecBool& a_visited,
                     VecBool& a_good,
                     VecInt& a_check)
{
  if (a_goodCell > -1)
  {
    a_visited[a_goodCell] = true;
  }
  if (a_badCell > -1)
  {
    a_visited[a_badCell] = true;
    a_good[a_badCell] = false;
    a_check.push_back(a_badCell);
  }
} // iMarkEdgeOnLoop

//------------------------------------------------------------------------------
/// \brief Mark cells on either side of a single loop.
/// \param a_ugrid: XmUGrid to mark cells for.
/// \param a_loop: Loop to mark cells along.
/// \param a_visited: Visited flags for the grid.
/// \param a_good: Good flags for the grid.
/// \param a_check: Cells that should be checked for neighbors.
//------------------------------------------------------------------------------
void iMarkCellsOnLoop(std::shared_ptr<XmUGrid> a_ugrid,
                      const VecInt& a_loop,
                      VecBool& a_visited,
                      VecBool& a_good,
                      VecInt& a_check)
{
  auto a = a_loop.begin();
  auto b = a;
  b++;

  for (; b != a_loop.end(); a++, b++)
  {
    int badCell, goodCell;

    iGetLeftRightCells(a_ugrid, *a, *b, badCell, goodCell);
    iMarkEdgeOnLoop(goodCell, badCell, a_visited, a_good, a_check);
  }

  if (a_loop[0] != a_loop.back())
  {
    int badCell, goodCell;

    iGetLeftRightCells(a_ugrid, a_loop.back(), a_loop[0], badCell, goodCell);
    iMarkEdgeOnLoop(goodCell, badCell, a_visited, a_good, a_check);
  }
} // iMarkCellsOnLoop

//------------------------------------------------------------------------------
/// \brief Mark cells on either side of all loops.
/// \param a_ugrid: XmUGrid to mark cells for.
/// \param a_loop: Loops to mark cells along.
/// \param a_visited: Visited flags for the grid.
/// \param a_good: Good flags for the grid.
/// \param a_check: Cells that should be checked for neighbors.
//------------------------------------------------------------------------------
void iMarkCellsOnLoops(std::shared_ptr<XmUGrid> a_ugrid,
                       const VecInt2d& a_loops,
                       VecBool& a_visited,
                       VecBool& a_good,
                       VecInt& a_check)
{
  for (const auto& loop : a_loops)
  {
    iMarkCellsOnLoop(a_ugrid, loop, a_visited, a_good, a_check);
  }
} // iMarkCellsOnLoops

//------------------------------------------------------------------------------
/// \brief Mark the neighbors of a given cell.
/// \param a_ugrid: XmUGrid to mark cells for.
/// \param a_cell: Cell ID to mark neighbors of.
/// \param a_visited: Visited flags for the grid.
/// \param a_good: Good flags for the grid.
/// \param a_check: Cells that should be checked for neighbors.
//------------------------------------------------------------------------------
void iMarkNeighborsOfCell(std::shared_ptr<XmUGrid> a_ugrid,
                          int a_cell,
                          VecBool& a_visited,
                          VecBool& a_good,
                          VecInt& a_check)
{
  VecInt neighbors;
  XM_ASSERT(a_ugrid->GetCellEdgeCount(a_cell) == 3);

  /*
  Using GetCellAdjacentCells gets neighbors that only share one point. Consider:
   |\
   | \
   |  \
   |   \
   |    \
   | A   \    /|
   |      \  / |
   |       \/  |
   |\------/\ E|
   | \ C  /  \ |
   |B \  / D  \|
   |---\/------\
        \      /
         \ F  /
          \  /
           \/
  Where the boundary follows the edges of A, C, D, E, F, but excludes B.
  Initially, A, C, E, and F will be marked as visited-good since they're
  adjacent to the boundary and inside, while B will be visited as
  visited-bad since it's adjacent to the boundary on the wrong side, and D
  will be unvisited since it has no edge in common with the boundary.

  Then we'll visit the unvisited neighbors of B and mark them as bad. Since D
  is an unvisited neighbor of B, it will be marked bad, even though it's inside
  the boundary.

  So we have to make sure we're only visiting neighbors with a whole edge in
  common, not just a single point.
  */
  for (int i = 0; i < 3; i++)
  {
    int neighbor = a_ugrid->GetCell2dEdgeAdjacentCell(a_cell, i);
    if (neighbor > -1)
    {
      neighbors.push_back(neighbor);
    }
  }

  for (const auto& neighbor : neighbors)
  {
    if (!a_visited[neighbor])
    {
      a_visited[neighbor] = true;
      a_good[neighbor] = a_good[a_cell];
      if (!a_good[neighbor])
      {
        a_check.push_back(neighbor);
      }
    }
  }
} // iMarkNeighborsOfCell

//------------------------------------------------------------------------------
/// \brief Mark all unvisited neighbors reachable from the given cells.
/// \param a_ugrid: XmUGrid to mark cells for.
/// \param a_visited: Visited flags for the grid.
/// \param a_good: Good flags for the grid.
/// \param a_check: Cells that should be checked for neighbors.
//------------------------------------------------------------------------------
void iMarkNeighborsOfCells(std::shared_ptr<XmUGrid> a_ugrid,
                           VecBool& a_visited,
                           VecBool& a_good,
                           VecInt& a_check)
{
  while (a_check.size() > 0)
  {
    int cell = a_check.back();
    a_check.pop_back();
    iMarkNeighborsOfCell(a_ugrid, cell, a_visited, a_good, a_check);
  }
} // iMarkNeighborsOfCells

} // namespace

//----- Class / Function definitions -------------------------------------------

//------------------------------------------------------------------------------
/// \brief Deletes points and cells in a_ugrid that are on the wrong side of
///        a boundary loop.
/// \param a_ugrid:   The XmUGrid to be clipped.
/// \param a_loops:   Boundary loop(s) (0-based indices of points in a_ugrid).
/// 	              Repeating the last point in a loop is optional.
/// 	              Loops should be in CW order for boundary loops and CCW
/// 	              order for hole loops.
/// \returns:         A new XmUGrid, with points and cells on the wrong side of
/// 	              the boundary loops removed.
///
/// \note This only detects cells that can be reached by visiting all cells
/// 	  that share an edge with at least one boundary loop, and all of cells
///       that share an edge with those (direct and indirect).
/// 
///       Example: Suppose there is only one loop, which is a boundary loop,
///       and follows the border of A.
/// 
/// +--------+----+----+--------+
/// |        |    |    |        |
/// |   A    | B  | C  |   E    |
/// |        +----+----+        |
/// |        |    | D  |        |
/// +--------+    +----+--------+
/// 
/// 	  A will be kept since it's in the boundary, and B will be deleted
///       since it's adjacent to the boundary and outside. C will also be
///       deleted since it is outside and reachable from B. Likewise, D and E
/// 	  will be deleted since they're outside and reachable from C.
/// 
/// +--------+    +----+--------+
/// |        |    |    |        |
/// |   A    |    | C  |   E    |
/// |        |    +----+        |
/// |        |    | D  |        |
/// +--------+    +----+--------+
/// 
/// 	  A will be kept since it's in the boundary. C, D, and E are all
/// 	  unreachable from A, so they will be kept too, even though they
///       are outside the boundary.
/// 
/// +--------+----+    +--------+
/// |        |    |    |        |
/// |   A    | B  |    |   E    |
/// |        +----+----+        |
/// |        |    | D  |        |
/// +--------+    +----+--------+
/// 
///      A will be kept since it's in the boundary, and B will be deleted
/// 	 since it's adjacent to the boundary and outside. D and E are
/// 	 unreachable from B since they are not adjacent to any other detected
/// 	 cells, so they will be kept too, even though they are outside the
/// 	 boundary.
/// 
/// \note This only deletes points that were became orphaned during the
///       clipping process.
/// 
///       Example: Suppose all the kept points and cells are inside of A below.
/// 
/// +--------+----B
/// |        |   /
/// |   A    |  /
/// |        | /
/// |        |/
/// +--------+
///
/// 	  The point B will be deleted since it was part of a deleted cell.
/// 
/// +--------+    B
/// |        |
/// |   A    |
/// |        |
/// |        |
/// +--------+
///
/// 	  The point B will not be deleted, since it was already orphaned to
/// 	  begin with.
/// 
/// \note Assumes all cells are triangles.
//------------------------------------------------------------------------------
std::shared_ptr<XmUGrid> XmClipUGrid(std::shared_ptr<XmUGrid> a_ugrid, const VecInt2d& a_loops)
{
  VecBool visited;
  visited.assign(a_ugrid->GetCellCount(), false);
  VecBool good;
  good.assign(a_ugrid->GetCellCount(), true);
  VecInt check;

  iMarkCellsOnLoops(a_ugrid, a_loops, visited, good, check);
  iMarkNeighborsOfCells(a_ugrid, visited, good, check);

  SetInt cellsToDelete;
  for (int i = 0; i < good.size(); i++)
  {
    if (!good[i])
    {
      cellsToDelete.insert(i);
    }
  }

  return XmRemoveCells(*a_ugrid, cellsToDelete, true);
} // XmClipUGrid

} // namespace xms

#ifdef CXX_TEST
//------------------------------------------------------------------------------
// Unit Tests
//------------------------------------------------------------------------------
using namespace xms;
#include <xmsgrid/ugrid/detail/UGridClipper.t.h>

#include <xmscore/testing/TestTools.h>

namespace
{
std::string ClipperFilesPath = std::string(XMS_TEST_PATH) + "clipper/";

//------------------------------------------------------------------------------
/// \brief Make a VecBool of a given size with specified values.
/// \param a_size: Number of elements in the VecBool.
/// \param a_default: Default value of elements in the VecBool.
/// \param a_vals: Indices of elements to negate.
/// \returns The VecBool.
//------------------------------------------------------------------------------
VecBool iMakeVecBool(int a_size, bool a_default, const SetInt& a_vals)
{
  VecBool vec;
  vec.assign(a_size, a_default);
  for (const int val : a_vals)
  {
    vec[val] = !a_default;
  }
  return vec;
} // iMakeVecBool

//------------------------------------------------------------------------------
/// \brief Test iGetLeftRightCells.
/// \param a_a: Index of first point on edge.
/// \param a_b: Index of second point on edge.
/// \param a_expectedLeft: Expected index of left cell.
/// \param a_expectedRight: Expected index of right cell.
//------------------------------------------------------------------------------
void iTestGetLeftRightCells(int a_a, int a_b, int a_expectedLeft, int a_expectedRight)
{
  auto grid = XmReadUGridFromAsciiFile(ClipperFilesPath + "octagon.xmugrid");

  int left, right;
  iGetLeftRightCells(grid, a_a, a_b, left, right);
  TS_ASSERT(left == a_expectedLeft);
  TS_ASSERT(right == a_expectedRight);
} // iTestGetLeftRightCells

//------------------------------------------------------------------------------
/// \brief Test iMarkCellsOnLoop.
/// \param a_loop: Boundary loop to mark cells along.
/// \param a_expectedVisited: Expected visited flags.
/// \param a_expectedGood: Expected good flags.
/// \param a_expectedCheck: Expected check list. Should be pre-sorted.
//------------------------------------------------------------------------------
void iTestMarkCellsOnLoop(const VecInt& a_loop,
                          const SetInt& a_expectedVisited,
                          const SetInt& a_expectedGood,
                          const VecInt& a_expectedCheck)
{
  auto grid = XmReadUGridFromAsciiFile(ClipperFilesPath + "octagon.xmugrid");
  int cellCount = grid->GetCellCount();

  VecInt check;
  VecBool visited = iMakeVecBool(cellCount, false, {});
  VecBool good = iMakeVecBool(cellCount, true, {});
  
  VecBool expectedVisited = iMakeVecBool(cellCount, false, a_expectedVisited);
  VecBool expectedGood = iMakeVecBool(cellCount, false, a_expectedGood);

  iMarkCellsOnLoop(grid, a_loop, visited, good, check);

  std::sort(check.begin(), check.end());

  TS_ASSERT_EQUALS_VEC(expectedVisited, visited);
  TS_ASSERT_EQUALS_VEC(expectedGood, good);
  TS_ASSERT_EQUALS_VEC(a_expectedCheck, check);
} // iTestMarkCellsOnLoop

//------------------------------------------------------------------------------
/// \brief Test iMarkNeighborsOfCell.
/// \param a_cell: Cell ID to mark neighbors of.
/// \param a_visited: Visited flags for the grid.
/// \param a_good: Good flags for the grid.
/// \param a_expectedVisited: Expected visited flags after the test finishes.
/// \param a_expectedGood: Expected good flags after the test finishes.
/// \param a_expectedCheck: Expected check list after the test finishes.
//------------------------------------------------------------------------------
void iTestMarkNeighborsOfCell(int a_cell,
                              SetInt& a_visited,
                              SetInt& a_good,
                              const SetInt& a_expectedVisited,
                              const SetInt& a_expectedGood,
                              const VecInt& a_expectedCheck)
{
  auto grid = XmReadUGridFromAsciiFile(ClipperFilesPath + "octagon.xmugrid");
  
  VecBool visited = iMakeVecBool(grid->GetCellCount(), false, a_visited);
  VecBool good = iMakeVecBool(grid->GetCellCount(), false, a_good);
  VecBool expectedVisited = iMakeVecBool(grid->GetCellCount(), false, a_expectedVisited);
  VecBool expectedGood = iMakeVecBool(grid->GetCellCount(), false, a_expectedGood);
  
  VecInt check;
  
  iMarkNeighborsOfCell(grid, a_cell, visited, good, check);

  std::sort(check.begin(), check.end());

  TS_ASSERT_EQUALS_VEC(expectedVisited, visited);
  TS_ASSERT_EQUALS_VEC(expectedGood, good);
  TS_ASSERT_EQUALS_VEC(a_expectedCheck, check);
} // iTestMarkNeighborsOfCell

//------------------------------------------------------------------------------
/// \brief Test iMarkNeighborsOfCells.
/// \param a_visited: Visited flags for the grid.
/// \param a_good: Good flags for the grid.
/// \param a_check: List of cells to check.
/// \param a_expectedVisited: Expected visited flags after the test finishes.
/// \param a_expectedGood: Expected good flags after the test finishes.
//------------------------------------------------------------------------------
void iTestMarkNeighborsOfCells(SetInt& a_visited,
                               SetInt& a_good,
                               VecInt& a_check,
                               const SetInt& a_expectedVisited,
                               const SetInt& a_expectedGood)
{
  auto grid = XmReadUGridFromAsciiFile(ClipperFilesPath + "octagon.xmugrid");
  
  VecBool visited = iMakeVecBool(grid->GetCellCount(), false, a_visited);
  VecBool good = iMakeVecBool(grid->GetCellCount(), false, a_good);
  VecBool expectedVisited = iMakeVecBool(grid->GetCellCount(), false, a_expectedVisited);
  VecBool expectedGood = iMakeVecBool(grid->GetCellCount(), false, a_expectedGood);
  
  iMarkNeighborsOfCells(grid, visited, good, a_check);

  TS_ASSERT_EQUALS_VEC(expectedVisited, visited);
  TS_ASSERT_EQUALS_VEC(expectedGood, good);
  TS_ASSERT(a_check.empty());
} // iTestMarkNeighborsOfCells

} // namespace

//------------------------------------------------------------------------------
/// \brief Test iGetLeftRightCells
//------------------------------------------------------------------------------
void UGridClipperTests::testGetLeftRightCells()
{
  iTestGetLeftRightCells(9, 12, 6, 9);
} // UGridClipperTests::testGetLeftRightCells

//------------------------------------------------------------------------------
/// \brief Test iGetLeftRightCells
//------------------------------------------------------------------------------
void UGridClipperTests::testGetLeftRightCellsReversed()
{
  iTestGetLeftRightCells(12, 9, 9, 6);
} // UGridClipperTests::testGetLeftRightCellsReversed

//------------------------------------------------------------------------------
/// \brief Test iGetLeftRightCells
//------------------------------------------------------------------------------
void UGridClipperTests::testGetLeftRightCellsNoLeft()
{
  iTestGetLeftRightCells(0, 7, -1, 3);
} // UGridClipperTests::testGetLeftRightCellsNoLeft

//------------------------------------------------------------------------------
/// \brief Test iGetLeftRightCells
//------------------------------------------------------------------------------
void UGridClipperTests::testGetLeftRightCellsNoRight()
{
  iTestGetLeftRightCells(3, 4, 7, -1);
} // UGridClipperTests::testGetLeftRightCellsNoRight

//------------------------------------------------------------------------------
/// \brief Test iMarkCellsOnLoop
//------------------------------------------------------------------------------
void UGridClipperTests::testMarkCellsOnLoopBoundary()
{
  iTestMarkCellsOnLoop({7, 6, 5, 4, 3, 2, 1, 0},
                       {0, 1, 3, 4, 7, 8, 10, 12},
                       {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
                       {});
} // UGridClipperTests::testMarkCellsOnLoopBoundary

//------------------------------------------------------------------------------
/// \brief Test iMarkCellsOnLoop
//------------------------------------------------------------------------------
void UGridClipperTests::testMarkCellsOnLoopHole()
{
  iTestMarkCellsOnLoop({0, 1, 2, 3, 4, 5, 6, 7},
                       {0, 1, 3, 4, 7, 8, 10, 12},
                       {2, 5, 6, 9, 11, 13, 14, 15},
                       {0, 1, 3, 4, 7, 8, 10, 12});
} // UGridClipperTests::testMarkCellsOnLoopHole

//------------------------------------------------------------------------------
/// \brief Test iMarkCellsOnLoop
//------------------------------------------------------------------------------
void UGridClipperTests::testMarkCellsOnLoopBoundaryAndHole()
{
  iTestMarkCellsOnLoop({8, 9, 10, 11},
                       {2, 5, 6, 9, 11, 13, 14, 15},
                       {0, 1, 2, 3, 4, 5, 7, 8, 10, 12, 13, 15},
                       {6, 9, 11, 14});
} // UGridClipperTests::testMarkCellsOnLoopBoundaryAndHole

//------------------------------------------------------------------------------
/// \brief Test iMarkCellsOnLoops
//------------------------------------------------------------------------------
void UGridClipperTests::testMarkCellsOnLoops()
{
  auto grid = XmReadUGridFromAsciiFile(ClipperFilesPath + "octagon.xmugrid");
  VecInt2d loops = {{9, 3, 10}, {7, 6, 5, 4, 3, 2, 1, 0}};
  VecInt expectedVisit = {15, 15, 15};
  VecBool expectedVisited =
    iMakeVecBool(grid->GetCellCount(), false, {0, 1, 3, 4, 7, 8, 9, 10, 12, 15});
  VecBool expectedGood =
    iMakeVecBool(grid->GetCellCount(), false, {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14});

  VecInt check;
  VecBool visited, good;
  visited.assign(grid->GetCellCount(), false);
  good.assign(grid->GetCellCount(), true);

  iMarkCellsOnLoops(grid, loops, visited, good, check);

  std::sort(check.begin(), check.end());

  TS_ASSERT_EQUALS_VEC(expectedVisited, visited);
  TS_ASSERT_EQUALS_VEC(expectedGood, good);
  TS_ASSERT_EQUALS_VEC(expectedVisit, check);
} // UGridClipperTests::testMarkCellsOnLoops

//------------------------------------------------------------------------------
/// \brief Test iMarkNeighborsOfCell
//------------------------------------------------------------------------------
void UGridClipperTests::testMarkBoundaryCellNoVisitedNeighbors()
{
  SetInt visited = {0};
  SetInt good = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};

  SetInt expectedVisited = {0, 1, 2};
  SetInt expectedGood = {3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
  VecInt expectedVisit = {1, 2};

  iTestMarkNeighborsOfCell(0, visited, good, expectedVisited, expectedGood, expectedVisit);
} // UGridClipperTests::testMarkBoundaryCellNoVisitedNeighbors

//------------------------------------------------------------------------------
/// \brief Test iMarkNeighborsOfCell
//------------------------------------------------------------------------------
void UGridClipperTests::testMarkBoundaryCellOneVisitedNeighbor()
{
  SetInt visited = {0, 1};
  SetInt good = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};

  SetInt expectedVisited = {0, 1, 2};
  SetInt expectedGood = {1, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
  VecInt expectedVisit = {2};

  iTestMarkNeighborsOfCell(0, visited, good, expectedVisited, expectedGood, expectedVisit);
} // UGridClipperTests::testMarkBoundaryCellNoVisitedNeighbors

//------------------------------------------------------------------------------
/// \brief Test iMarkNeighborsOfCell
//------------------------------------------------------------------------------
void UGridClipperTests::testMarkBoundaryCellAllVisitedNeighbors()
{
  SetInt visited = {0, 1, 2};
  SetInt good = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};

  SetInt expectedVisited = {0, 1, 2};
  SetInt expectedGood = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
  VecInt expectedVisit = {};

  iTestMarkNeighborsOfCell(0, visited, good, expectedVisited, expectedGood, expectedVisit);
} // UGridClipperTests::testMarkBoundaryCellNoVisitedNeighbors

//------------------------------------------------------------------------------
/// \brief Test iMarkNeighborsOfCell
//------------------------------------------------------------------------------
void UGridClipperTests::testMarkInteriorCellNoVisitedNeighbors()
{
  SetInt visited = {14};
  SetInt good = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 15};

  SetInt expectedVisited = {5, 6, 11, 14};
  SetInt expectedGood = {0, 1, 2, 3, 4, 7, 8, 9, 10, 12, 13, 15};
  VecInt expectedVisit = {5, 6, 11};

  iTestMarkNeighborsOfCell(14, visited, good, expectedVisited, expectedGood, expectedVisit);
} // UGridClipperTests::testMarkBoundaryCellNoVisitedNeighbors

//------------------------------------------------------------------------------
/// \brief Test iMarkNeighborsOfCell
//------------------------------------------------------------------------------
void UGridClipperTests::testMarkInteriorCellOneVisitedNeighbor()
{
  SetInt visited = {11, 14};
  SetInt good = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 15};

  SetInt expectedVisited = {5, 6, 11, 14};
  SetInt expectedGood = {0, 1, 2, 3, 4, 7, 8, 9, 10, 11, 12, 13, 15};
  VecInt expectedVisit = {5, 6};

  iTestMarkNeighborsOfCell(14, visited, good, expectedVisited, expectedGood, expectedVisit);
} // UGridClipperTests::testMarkBoundaryCellNoVisitedNeighbors

//------------------------------------------------------------------------------
/// \brief Test iMarkNeighborsOfCell
//------------------------------------------------------------------------------
void UGridClipperTests::testMarkInteriorCellAllVisitedNeighbors()
{
  SetInt visited = {5, 6, 11, 14};
  SetInt good = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};

  SetInt expectedVisited = {5, 6, 11, 14};
  SetInt expectedGood = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
  VecInt expectedVisit = {};

  iTestMarkNeighborsOfCell(14, visited, good, expectedVisited, expectedGood, expectedVisit);
} // UGridClipperTests::testMarkBoundaryCellNoVisitedNeighbors

//------------------------------------------------------------------------------
/// \brief Test iMarkNeighborsOfCells
//------------------------------------------------------------------------------
void UGridClipperTests::testMarkOuterBoundaryAsOutside()
{
  SetInt visited = {0, 1, 3, 4, 7, 8, 10, 12};
  SetInt good = {2, 5, 6, 9, 11, 13, 14, 15};
  VecInt check = {0, 1, 3, 4, 7, 8, 10, 12};

  SetInt expectedVisited = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
  SetInt expectedGood = {};

  iTestMarkNeighborsOfCells(visited, good, check, expectedVisited, expectedGood);
} // UGridClipperTests::testMarkOuterBoundaryAsOutside

//------------------------------------------------------------------------------
/// \brief Test iMarkNeighborsOfCells
//------------------------------------------------------------------------------
void UGridClipperTests::testMarkOuterBoundaryAsInside()
{
  SetInt visited = {0, 1, 3, 4, 7, 8, 10, 12};
  SetInt good = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
  VecInt check = {};

  SetInt expectedVisited = {0, 1, 3, 4, 7, 8, 10, 12};
  SetInt expectedGood = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};

  iTestMarkNeighborsOfCells(visited, good, check, expectedVisited, expectedGood);
} // UGridClipperTests::testMarkOuterBoundaryAsInside

//------------------------------------------------------------------------------
/// \brief Test iMarkNeighborsOfCells
//------------------------------------------------------------------------------
void UGridClipperTests::testMarkInnerBoundaryAsOutside()
{
  SetInt visited = {2, 5, 6, 9, 11, 13, 14, 15};
  SetInt good = {0, 1, 2, 3, 4, 5, 7, 8, 10, 12, 13, 15};
  VecInt check = {6, 9, 11, 14};

  SetInt expectedVisited = {2, 5, 6, 9, 11, 13, 14, 15};
  SetInt expectedGood = {0, 1, 2, 3, 4, 5, 7, 8, 10, 12, 13, 15};

  iTestMarkNeighborsOfCells(visited, good, check, expectedVisited, expectedGood);
} // UGridClipperTests::testMarkInnerBoundaryAsOutside

//------------------------------------------------------------------------------
/// \brief Test iMarkNeighborsOfCells
//------------------------------------------------------------------------------
void UGridClipperTests::testMarkInnerBoundaryAsInside()
{
  SetInt visited = {2, 5, 6, 9, 11, 13, 14, 15};
  SetInt good = {0, 1, 3, 4, 6, 7, 8, 9, 10, 11, 12, 14};
  VecInt check = {2, 5, 13, 15};

  SetInt expectedVisited = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
  SetInt expectedGood = {6, 9, 11, 14};

  iTestMarkNeighborsOfCells(visited, good, check, expectedVisited, expectedGood);
} // UGridClipperTests::testMarkInnerBoundaryAsInside

//------------------------------------------------------------------------------
/// \brief Test iMarkNeighborsOfCells
//------------------------------------------------------------------------------
void UGridClipperTests::testMarkMultipleBoundaries()
{
  SetInt visited = {1,   4,   9,   13,  21,  25,  26,  28,  29,  34,  35,  37,  39,  42,
                    44,  45,  47,  48,  49,  52,  54,  56,  60,  61,  64,  65,  66,  67,
                    68,  69,  70,  71,  75,  84,  88,  89,  90,  91,  92,  96,  97,  99,
                    100, 102, 103, 105, 106, 110, 111, 113, 114, 116, 117, 120, 122, 123,
                    124, 126, 128, 129, 130, 131, 132, 133, 137, 138};

  SetInt good = {1,  4,  9,  13, 21, 25, 26, 28, 29, 34, 35, 37, 39, 42, 44,
                 45, 47, 48, 49, 52, 54, 56, 60, 61, 64, 65, 66, 67, 68, 69,
                 70, 71, 75, 84, 88, 89, 90, 91, 92, 96, 97, 99, 100};

  VecInt check = {102, 103, 105, 106, 110, 111, 113, 114, 116, 117, 120, 122,
                  123, 124, 126, 128, 129, 130, 131, 132, 133, 137, 138};

  SetInt expectedVisited = {1,   4,   9,   13,  21,  25,  26,  28,  29,  34,  35,  37,  39,  42,
                            44,  45,  47,  48,  49,  52,  54,  56,  60,  61,  64,  65,  66,  67,
                            68,  69,  70,  71,  75,  84,  88,  89,  90,  91,  92,  96,  97,  99,
                            100, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114,
                            115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128,
                            129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140};

  SetInt expectedGood = {1,  4,  9,  13, 21, 25, 26, 28, 29, 34, 35, 37, 39, 42, 44,
                         45, 47, 48, 49, 52, 54, 56, 60, 61, 64, 65, 66, 67, 68, 69,
                         70, 71, 75, 84, 88, 89, 90, 91, 92, 96, 97, 99, 100};

  auto grid = XmReadUGridFromAsciiFile(ClipperFilesPath + "horn.xmugrid");
  
  VecBool visitedFlags = iMakeVecBool(grid->GetCellCount(), false, visited);
  VecBool goodFlags = iMakeVecBool(grid->GetCellCount(), false, good);
  VecBool expectedVisitedFlags = iMakeVecBool(grid->GetCellCount(), false, expectedVisited);
  VecBool expectedGoodFlags = iMakeVecBool(grid->GetCellCount(), false, expectedGood);
  
  iMarkNeighborsOfCells(grid, visitedFlags, goodFlags, check);

  TS_ASSERT_EQUALS_VEC(expectedVisitedFlags, visitedFlags);
  TS_ASSERT_EQUALS_VEC(expectedGoodFlags, goodFlags);
  TS_ASSERT(check.empty());
} // UGridClipperTests::testMarkMultipleBoundaries

//------------------------------------------------------------------------------
/// \brief Test XmClipUGrid
//------------------------------------------------------------------------------
void UGridClipperTests::testClipUgrid()
{
  std::string unclippedPath = ClipperFilesPath + "horn.xmugrid";
  std::string clippedPath = ClipperFilesPath + "horn-clipped.xmugrid";
  std::string basePath = ClipperFilesPath + "horn-base.xmugrid";

  auto unclippedGrid = XmReadUGridFromAsciiFile(ClipperFilesPath + "horn.xmugrid");

  VecInt2d loops = {{59, 60, 61, 42, 71, 72, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38,
                     39, 40, 41, 19, 20, 66, 67, 68, 69, 70, 52, 53, 54, 56, 57, 58},
                    {14, 44, 13, 26, 2, 11, 1, 0},
                    {7, 12, 10, 4, 5, 6}};

  auto clippedGrid = XmClipUGrid(unclippedGrid, loops);

  XmWriteUGridToAsciiFile(clippedGrid, clippedPath);

  TS_ASSERT_TXT_FILES_EQUAL(basePath, clippedPath);
} // UGridClipperTests::testClipUgrid

#endif
