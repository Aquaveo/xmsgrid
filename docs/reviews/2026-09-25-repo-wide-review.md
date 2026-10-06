# Review: repo-wide audit of `xmsgrid`

Generated 2026-09-25 by `/aquaveo-workflow:review --all --repo --validate` on branch `aquaveo-workflow-review-eb3ce8` (base `master`, HEAD `6cf0b20`; rebased onto `ad625a6`, which only regenerated the CI workflow).

Validated 15 of 47 findings (12 confirmed, 3 dropped, 0 uncertain; 32 past the cap, unvalidated).

---

**What changed.** This is not a diff review: nine specialists audited all 167 tracked files of the xmsgrid C++ library and its pybind11 Python package (`_package/xms/grid`). Findings cluster in the legacy C-heritage geometry kernel (`xmsgrid/geometry/geoms.cpp`, `GmExtents.cpp`, `GmMultiPolyIntersector.cpp`, `GmTriSearch.cpp`, `GmPtSearch.cpp`), the triangulator (`xmsgrid/triangulate/`), UGrid I/O (`xmsgrid/ugrid/XmUGridUtils.cpp`), the untested `matrices/` module, and the Python wrapper and its tests. Nothing here is security-sensitive, but several findings are memory-safety defects (double free, out-of-bounds indexing) in public API. Notably, `xmsgrid/triangulate/TrTin.h:56-58` already provides const-qualified overloads of `Points()`/`Triangles()`/`TrisAdjToPts()` beside the mutable ones, so the encapsulation fix in M24 is an API tightening, not a new surface.

Validation: 15 of 47 CRITICAL+MAJOR rollup entries were independently validated (12 confirmed, 3 dropped, 0 uncertain); the remaining 32 MAJOR entries were past the validator cap and are tagged `[unvalidated]`. Per-specialist verdicts: writer-reviewer BLOCK, complexity-reviewer BLOCK, all others REQUEST CHANGES.

Specialists dispatched (9): aquaveo-workflow:writer-reviewer, aquaveo-workflow:silent-failure-reviewer, aquaveo-workflow:complexity-reviewer, aquaveo-workflow:pr-coverage-reviewer, xunit-patterns-python:test-reviewer, xunit-patterns:test-smell-reviewer, aquaveo-python:type-design-reviewer, aquaveo-cpp:type-design-reviewer, aquaveo-cpp:cmake-structure-reviewer. Skipped as not applicable: image-baseline-reviewer (no baseline directories), clean-architecture-python:arch-reviewer (no check_architecture.py), ddd-python:ddd-reviewer (no domain/).

**Verdict: BLOCK (C=9 M=35 m=101)**

---

## Critical items

### **C1**: `.flake8:0` — xmsconan-generated file tracked in git, will drift from generator `[validated]`

```gitignore
# ── Generated build files (Conan/CMake) ────────
CMakeLists.txt
conanfile.py
build.py
xms_conan2_file.py
_package/pyproject.toml
```

**Change:** Add `.flake8` to the "Generated build files" block in `.gitignore` and run `git rm --cached .flake8`. The validator confirmed `.github/workflows/XmsGrid-CI.yaml:126-131` regenerates it via `xmsconan job lint` (at the reviewed commit `6cf0b20`, lines 46-50 ran `xmsconan_gen build.toml`).

**Why:** A tracked copy of a generated file silently diverges from what CI actually lints against, so local and CI flake8 results disagree with no signal.

### **C2**: `_package/xms/grid/ugrid/ugrid.py:208` — `get_cells_adjacent_to_edge` always raises TypeError `[validated]`

```python
    def get_cells_adjacent_to_edge(self, point1, point2):
        ...
        return self._instance.GetPointsAdjacentCells(point1, point2)
```

**Change:** Pass the two indices as a single iterable: `self._instance.GetPointsAdjacentCells([point1, point2])`. The only binding (`xmsgrid/python/ugrid/XmUGrid_py.cpp:159-162`) takes one `py::arg("point_idxs")`. Add a Python test for the method; none exists.

**Why:** Every call to this public method fails with a pybind11 TypeError; the method is dead on arrival and no test would notice.

### **C3**: `xmsgrid/geometry/GmExtents.cpp:86` — `GmExtents2d::operator+=` mixes `m_min.y` into `m_min.x` `[validated]`

```cpp
void GmExtents2d::operator+=(const GmExtents2d& a_rhs)
{
  m_min.x = std::min(m_min.y, a_rhs.m_min.x);
  m_max.x = std::max(m_max.x, a_rhs.m_max.x);
  m_min.y = std::min(m_min.y, a_rhs.m_min.y);
  m_max.y = std::max(m_max.y, a_rhs.m_max.y);
}
```

**Change:** Replace `m_min.y` with `m_min.x` on line 86 (compare the correct `GmExtents3d::operator+=` at :309 and `AddToExtents` at :99). Add a cxxtest for `GmExtents2d::operator+=`; neither `GmExtents.t.h` nor the `CXX_TEST` block at :556-720 calls it.

**Why:** Merging {min=(0,10)} with {min=(5,20)} yields min.x=5 instead of 0, so merged extents silently exclude real data for downstream consumers.

### **C4**: `xmsgrid/geometry/GmMultiPolyIntersector.cpp:707-714` — `RemoveDuplicateTValues` erases stale indices after `std::unique` `[validated]`

```cpp
    auto it = std::unique(indexesToRemove.begin(), indexesToRemove.end());
    indexesToRemove.resize(std::distance(indexesToRemove.begin(), it));
    for (auto&& i : indexesToRemove)
    {
      a_polyIds.erase(a_polyIds.begin() + i);
      a_tValues.erase(a_tValues.begin() + i);
      a_pts.erase(a_pts.begin() + i);
    }
```

**Change:** The validator corrected the finder's mechanism: `indexesToRemove` is a concatenation of descending runs (e.g. `[3,2,1, 2,1, 1]`), so descending erase within a run is fine, but duplicates across runs are non-adjacent and `std::unique` does not collapse them. Sort descending and then `unique` (or collect into a `std::set` and iterate in reverse) before erasing. The `:689-700` branch has identical structure and needs the same fix.

**Why:** With `a_tValues=[0,1,1,1,1]`, `a_polyIds=[5,-1,-1,-1,-1]` the loop erases 3,2,1 leaving size 2, then `erase(begin()+2)` is `erase(end())` (undefined behaviour) and `erase(begin()+1)` removes a legitimately kept intersection. Four or more trailing duplicates trigger it.

### **C5**: `xmsgrid/geometry/GmTriSearch.cpp:269-283` — `TrisToSearch` leaves dangling `m_rTree`, double free in destructor `[validated]`

```cpp
  // remove existing rtree and cache
  if (m_rTree)
    delete (m_rTree);
  m_cache.clear();

  m_pts = a_pts;
  m_tris = a_tris;
  CreateRTree();
}
...
void GmTriSearchImpl::CreateRTree()
{
  if (m_pts->empty() || m_tris->empty())
    return;
```

**Change:** Add `m_rTree = nullptr;` immediately after the `delete` at :270. `CreateRTree` returns early on empty input before its only reassignment at :309.

**Why:** Calling `TrisToSearch` with valid data then with empty input leaves a dangling pointer that the destructor (:255-256) deletes again, and `m_rTree->query` at :411/:437/:559 becomes a use-after-free.

### **C6**: `xmsgrid/geometry/geoms.cpp:1581-1885` — `gmPointInPolygon3DWithTol` ~305 lines, 6-deep nesting, three axis-parallel copies `[validated]`

```cpp
    if (plndir == 0)
    {
      /* case #1 and #2 - first vertex lies on
      dividing plane                           */
      if (fabs(vertex[id0].x - pt.x) <= tol)
      {
        if (fabs(vertex[id1].x - pt.x) <= tol)
        {
          if (divdir == 1)
          {
            if ((vertex[id0].y >= pt.y && vertex[id1].y <= pt.y) ||
```

**Change:** Extract one helper parameterised by projection axis (which of x/y/z is the plane normal and which two are the in-plane coordinates) and call it once per `plndir`. The three branches (1630-1710, 1711-1791, 1792-1872) are byte-for-byte parallel except for axis fields. Validator note: no correctness defect claimed; this is a stable, unit-tested C-heritage kernel and the validator would rate it refactor-grade MAJOR/MINOR rather than CRITICAL.

**Why:** A fix applied to one axis branch and not the other two is invisible to the compiler and to the current tests.

### **C7**: `xmsgrid/geometry/geoms.cpp:2326-2476` — `gmClipNDCPoly` has four near-identical ~30-line clip cases `[validated]`

```cpp
      case 1: /* clip to x-min                            */
        if (i > 0 && prev)
        {
          if ((curr->x > 0.0 && prev->x < 0.0) || (curr->x < 0.0 && prev->x > 0.0))
          {
            ...
            pts[tmpnpts].x = 0.0;
            if (y0 == y1)
              pts[tmpnpts].y = y0;
            else
            {
```

**Change:** Extract a single clip-to-boundary helper parameterised by axis (x/y), bound constant (0.0/1.0), and inside-test direction; the four `switch(k)` cases at :2350-2472 differ only in those three things. Validator note: pure duplication with no correctness defect claimed, legacy C-style code; the validator considers CRITICAL overstated and would rate it minor.

**Why:** Four copies of the same clipping arithmetic mean any fix must be applied four times, and divergence between copies is silent.

### **C8**: `xmsgrid/matrices/matrix.cpp:103` — `mxLUDecomp` singular-pivot fallback writes `mat[0][0]` instead of `mat[j][j]` `[validated]`

```cpp
    indx[j] = imax;
    if (mat[j][j] == 0.0)
      mat[0][0] = 1.0e-20;
    if (j != n)
    { // divide by the pivot element
      tmp = 1.0 / mat[j][j];
```

**Change:** Change `mat[0][0]` to `mat[j][j]` (the Numerical Recipes `ludcmp` pattern is `if (a[j][j] == 0.0) a[j][j] = TINY;`). Pair with the test module requested in M20, since nothing currently exercises this function.

**Why:** For j>0 the write clobbers the already-finalised U element `mat[0][0]`, and :106 then computes `1.0 / mat[j][j]` with a zero pivot, producing inf/NaN through the L column.

### **C9**: `xmsgrid/ugrid/detail/XmGeometry.cpp:72-90` — `ConvexHullWithIndices` pre-sizes then push_backs, and inner loop tests `i` not `j` `[validated]` (severity disagreement: writer-reviewer rated CRITICAL, pr-coverage-reviewer rated MAJOR)

```cpp
  VecPt3d points3d(a_points.size());
  for (int i = 0; i < a_points.size(); ++i)
  {
    points3d.push_back(a_ugrid->GetPointLocation(a_points[i]));
  }
  VecPt3d convexHull = ConvexHull(points3d);
  VecInt returnPoints(convexHull.size());
  for (int i(0); i < convexHull.size(); i++)
  {
    for (int j(0); i < points3d.size(); j++)
    {
      if (convexHull[i] == points3d[j])
```

**Change:** Use `reserve()` instead of sizing constructors for both vectors, and change the inner loop condition to `j < points3d.size()`; or delete the function outright. It is marked deprecated (:69), has no callers, no tests, and no Python binding. If kept, add a cxxtest exercising it. Validator severity note: real and reproducible, but on dead deprecated code, so practical impact is limited to anyone who picks up the public header API (`XmGeometry.h:42`).

**Why:** The hull is contaminated with N default (0,0,0) points, the result carries leading zero indices, and `j` runs past the end of `points3d` (out-of-bounds read).

---

## Major items

### **M1**: `_package/tests/unit_tests/geometry_tests/multi_poly_intersector_pyt.py:57-65` — message asserts inside `assertRaises` blocks are unreachable `[validated]`

```python
        with self.assertRaises(ValueError) as error:
            grid.geometry.MultiPolyIntersector(None, [1, 2, 3])
            assert str(error) == 'points is a required argument.'
```

**Change:** Dedent each `assert` out of its `with` block and compare `str(error.exception)` (not `str(error)`, which stringifies the context-manager object). Same for lines 62 and 65.

**Why:** The raise exits the block before the assert runs, so the error messages are never verified and a wrong message passes.

### **M2**: `_package/tests/unit_tests/triangulate_tests/tin_pyt.py:269-274` — `test_export_tin_file` writes `testfile.txt` to real cwd with no cleanup `[validated]`

```python
    def test_export_tin_file(self):
        """Test exporting a tin to an ASCII file."""
        trtin = xt.Tin(self.pts)
        trtin.set_geometry(self.pts, self.tris, self.tris_adj_tuple)
        trtin.export_tin_file("testfile.txt")
        self.assertTrue(os.path.isfile("testfile.txt"))
```

**Change:** Write to a `tmp_path`/`tempfile` location. The validator confirmed no `chdir`, `tmp_path`, `tempfile`, or tearDown exists anywhere under `_package`.

**Why:** Leaves a stray file wherever pytest runs and collides under parallel test execution.

### **M3**: `_package/tests/unit_tests/ugrid_tests/ugrid_utils_pyt.py:100` — cellstream assertion compares `xu3d` to itself `[validated]`

```python
        xu_read = ugrid_utils.read_ugrid_from_ascii_file(out_file_name)
        np.testing.assert_array_equal(xu3d.locations, xu_read.locations)
        np.testing.assert_array_equal(xu3d.cellstream, xu3d.cellstream)
```

**Change:** Change the second argument on line 100 to `xu_read.cellstream`, matching line 99.

**Why:** The assertion is tautological and can never detect a cellstream round-trip bug.

### **M4**: `_package/xms/grid/ugrid/ugrid.py:20-33` — constructors accept hidden `**kwargs['instance']` backdoor `[unvalidated]`

```python
        if 'instance' not in kwargs:
            if points is None and cellstream is None:
                self._instance = XmUGrid()
            ...
        else:
            if not isinstance(kwargs['instance'], XmUGrid):
                raise ValueError(...)
            self._instance = kwargs['instance']
```

**Change:** Replace with an explicit `_from_native(cls, instance)` classmethod or a named `instance=None` parameter. Also applies to `multi_poly_intersector.py:30-41`, `tri_search.py:16-25`, `tin.py:16-26`.

**Why:** A typo in the string key silently falls through to the `points is None` branch and constructs an empty grid instead of wrapping the native object.

### **M5**: `_package/xms/grid/ugrid/ugrid_utils.py:25,51,66,83,98` — module functions reach into `ugrid._instance` directly `[unvalidated]`

```python
def write_ugrid_to_ascii_file(ugrid, file_name):
    ...
    ugu.write_ugrid_to_ascii_file(ugrid._instance, file_name)
```

**Change:** Add a public `UGrid.native` property or `_unwrap()` helper and use it from these five call sites.

**Why:** Breaks the wrapper's encapsulation from outside its class; any change to the private attribute breaks five external functions.

### **M6**: `xmsgrid/geometry/GmExtents.cpp:108` (decl `GmExtents.h:53`) — `GmExtents2d::IsValid()` non-const; data members protected with no derived class `[unvalidated]` (severity disagreement: writer-reviewer rated MINOR, cpp type-design-reviewer rated MAJOR)

```cpp
  bool IsValid();
  ...
protected:
  Pt2d m_min;                ///< Minimum, maximum extents
  Pt2d m_max;                ///< Maximum, maximum extents
  static double m_tolerance; ///< Tolerance used in comparisons
```

**Change:** Mark `IsValid() const` (the 3D sibling at `GmExtents.h:124` is correct) and make `m_min`/`m_max`/`m_tolerance` private (`GmExtents.h:72-74, 151-153`).

**Why:** A const `GmExtents2d` cannot be validity-checked, and protected data with no subclass is an open invariant with no reason to be open.

### **M7**: `xmsgrid/geometry/GmExtents.cpp:261` (also `:535`) — static `m_tolerance` is process-global mutable state `[unvalidated]`

```cpp
double GmExtents2d::m_tolerance(0.0); ///< Tolerance. Static ?
```

**Change:** Make tolerance an instance member of `GmExtents2d`/`GmExtents3d`.

**Why:** Not thread-safe, and one caller's `SetTolerance` leaks into every other extents comparison in the process.

### **M8**: `xmsgrid/geometry/GmMultiPolyIntersectionSorterTerse.cpp:204-214` — indexes with -1 after `XM_ASSERT` in release builds `[unvalidated]`

```cpp
          XM_ASSERT(edgeEnd != XM_NONE);

          int polyIdx = m_d->m_ixs[edgeBeg].m_i - 1;
          ...
          Turn_enum turn = gmTurn(m_d->m_ixs[edgeBeg].m_pt,
                                  m_d->m_ixs[edgeEnd].m_pt, centroid);
```

**Change:** Return early (or skip the iteration) when `edgeEnd == XM_NONE` rather than relying on the assert.

**Why:** `XM_ASSERT` compiles out in release, so the code proceeds to index with -1: out-of-bounds read.

### **M9**: `xmsgrid/geometry/GmMultiPolyIntersector.cpp:623-653` — mutates global `gmXyTol` and restores it manually `[unvalidated]`

```cpp
  double oldTolerance = gmXyTol();
  gmXyTol(true, m_xyTol);
  ...
  gmXyTol(true, oldTolerance);
} // GmMultiPolyIntersectorImpl::TraverseLineSegment
```

**Change:** Use an RAII guard that restores the tolerance in its destructor, or pass tolerance explicitly to the geometry calls.

**Why:** Not exception-safe (an early throw leaves the global changed) and not thread-safe (see M17).

### **M10**: `xmsgrid/geometry/GmMultiPolyIntersector.cpp:641-643` — division by segment length with no guard `[unvalidated]`

```cpp
    double segmentDistance = gmXyDistance(a_x1, a_y1, a_x2, a_y2);
    double minCellFraction = m_minWidth / segmentDistance;
    kTol = std::min(minCellFraction * kTol, 1e-5);
```

**Change:** Guard `segmentDistance == 0` before dividing (e.g. fall back to the default `kTol`).

**Why:** A zero-length segment yields NaN t-values that propagate into the sort.

### **M11**: `xmsgrid/geometry/GmPolyLinePtRedistributer.cpp:91` — `a_size <= 0` divides by zero, negative vector size at :136 `[unvalidated]`

```cpp
  double length = PolyLineLengths(a_polyLines, lengths);
  int nSeg = (int)((length / a_size) + .5);
  return RedistPolyLineWithNumSeg(a_polyLines, length, lengths, nSeg);
```

**Change:** Validate `a_size > 0` up front with `XM_ENSURE_TRUE`.

**Why:** Division by zero here, and a negative `nSeg` produces a negative vector size at :136.

### **M12**: `xmsgrid/geometry/GmPolygon.h:36,47,48` (and `GmPtSearch.h`, `GmTriSearch.h`, `TrTin.h`, `GmPolyLinePtRedistributer.h`) — pervasive legacy `BSHP<T>` ownership type `[unvalidated]`

```cpp
  static BSHP<GmPolygon> New();
  ...
  virtual void Intersection(const GmPolygon& a_, std::vector<BSHP<GmPolygon>>& a_output) const = 0;
  virtual void Union(const GmPolygon& a_, std::vector<BSHP<GmPolygon>>& a_output) const = 0;
```

**Change:** Migrate factory returns and setup APIs to `Ptr<T>` per the migrate-pointers skill. Sites: `GmPtSearch.h:29,33,35,60`; `GmTriSearch.h:32,37,57,58`; `TrTin.h:40,44-49,60-61`; `GmPolyLinePtRedistributer.h:27`.

**Why:** The boost shared_ptr macro locks public API to a legacy ownership idiom that cannot interoperate with `std::shared_ptr` consumers without conversion.

### **M13**: `xmsgrid/geometry/GmPtSearch.cpp:294` — `&(*m_bshpPt3d)[0]` on an empty vector `[unvalidated]`

```cpp
  UpdateMinMax(&(*m_bshpPt3d)[0], m_bshpPt3d->size());
```

**Change:** Check `m_bshpPt3d->empty()` before taking the address (or use `data()`).

**Why:** Indexing element 0 of an empty vector is undefined behaviour.

### **M14**: `xmsgrid/geometry/GmPtSearch.cpp:425-434` (also `:486, :547, :593`) — `m_rTree` dereferenced without null check `[unvalidated]`

```cpp
  if (!m_bshpPt3d || m_bshpPt3d->empty())
  {
    XM_LOG(xmlog::error, "Unable to find nearest points; no points exist.");
  }
  ...
      m_rTree->query(bgi::satisfies(*a_fsat) && bgi::nearest(tmpPt, a_numPtsToFind),
```

**Change:** `XM_ENSURE_TRUE(m_rTree)` at each entry point; note the log at :427 does not return.

**Why:** Searching before `PtsToSearch` dereferences a null pointer and crashes.

### **M15**: `xmsgrid/geometry/GmTriSearch.cpp:405-417` (also `:426-443`) — `m_rTree` dereferenced with no null guard `[unvalidated]`

```cpp
  std::vector<value> vals;
  m_rTree->query(bgi::intersects(p), std::back_inserter(vals));
```

**Change:** Guard `m_rTree` before use in `TriEnvelopsContainingPt` and its sibling at :426-443.

**Why:** Null dereference when queried before `TrisToSearch` (or after C5 leaves it dangling).

### **M16**: `xmsgrid/geometry/geoms.cpp:1878` — `printf` to stdout in library code `[unvalidated]`

```cpp
  if (nmcrs1 != nmcrs2)
  {
    printf("error here in CLPT");
    return -999;
  }
```

**Change:** Replace with `XM_LOG` or remove.

**Why:** Library output to stdout is invisible to the logging system and pollutes the host application's console.

### **M17**: `xmsgrid/geometry/geoms.cpp:4697-4703` — `gmXyTol` function-local static mutable global `[unvalidated]`

```cpp
double gmXyTol(bool a_set /*false*/, double a_value /*1e-9*/)
{
  static double xytol = a_value;
  if (a_set)
    xytol = a_value;
  return xytol;
}
```

**Change:** Make it `thread_local` or thread an explicit tolerance parameter through the geometry predicates.

**Why:** Every geometry predicate reads it; concurrent callers race on the value (M9 writes it per call).

### **M18**: `xmsgrid/geometry/geoms.cpp:6039-6042` — `gmSplitPtVector` swallows exceptions and returns partial output `[unvalidated]`

```cpp
  catch (std::exception&)
  {
    XM_ASSERT(false);
  }
} // gmSplitPtVector
```

**Change:** Remove the try/catch and let the exception propagate (public function, `geoms.h:805`).

**Why:** In release, `bad_alloc`/`out_of_range` is swallowed and the caller receives partially populated `a_x/a_y/a_z` with no signal (the doc at :6018-6019 admits it).

### **M19**: `xmsgrid/python/triangulate/TrTin_py.cpp:51` — `Triangulate()` bool result discarded `[unvalidated]`

```cpp
      xms::TrTriangulatorPoints triangulator(*vec_pts, *vec_tris, &(*vec_adj_tris));
      triangulator.Triangulate();
      self.SetGeometry(vec_pts, vec_tris, vec_adj_tris);
```

**Change:** Throw `std::runtime_error` when `Triangulate()` returns false, matching the `std::length_error` at :46.

**Why:** A failed triangulation yields a Python TIN with zero triangles and no exception.

### **M20**: `xmsgrid/matrices/matrix.cpp:1-646` — entire matrix module has no test and no in-repo caller `[unvalidated]`

```cpp
int mxLUDecomp(double** mat, int n, int* indx, double* d);
int mxLUBcksub(double** mat, int n, const int* indx, double* b);
bool mxSolveNxN(double** A, double* x, double* b, int n);
bool mxSolveBandedEquations(double** a, double* x, double* b, int numeqs, int halfbandwidth);
bool mxSolve3x3(double A[3][3], double x[3], double b[3]);
int mxInvert4x4(const double matrix[4][4], double inv[4][4]);
```

**Change:** Add `xmsgrid/matrices/matrix.t.h` covering `mxSolveNxN` (n=1,2,3+), `mxInvert4x4` (orthogonal and singular), `mxSolveBandedEquations`, and `mxSolve3x3` round-trips.

**Why:** It is public `xms::` API likely consumed downstream (xmsinterp), so regressions such as C8 go undetected.

### **M21**: `xmsgrid/triangulate/TrBreaklineAdder.cpp:325-442` — `ProcessSegmentBySwapping` has no iteration cap `[unvalidated]`

```cpp
  while (!edges.empty() && edge != edges.end())
  {
    int tri1 = m_tin->TriangleAdjacentToEdge(edge->pt1, edge->pt2);
    int tri2 = m_tin->TriangleAdjacentToEdge(edge->pt2, edge->pt1);
```

**Change:** Cap the halving-minAngle loop and fail with an `XM_LOG` when the cap is hit.

**Why:** If the swap keeps being refused (concave quad) the loop never terminates.

### **M22**: `xmsgrid/triangulate/TrBreaklineAdder.h:15,32,35,36` (also `GmMultiPolyIntersector.h:36,39`) — three ownership idioms coexist `[unvalidated]`

```cpp
#include <boost/shared_ptr.hpp>
...
  static boost::shared_ptr<TrBreaklineAdder> New();
  virtual void SetObserver(boost::shared_ptr<Observer> a) = 0;
  virtual void SetTin(boost::shared_ptr<TrTin> a_tin, double a_tol = -1) = 0;
```

**Change:** Standardise on `Ptr<T>`/`std::shared_ptr` at boundaries (raw `boost::shared_ptr` here, `BSHP<T>` in siblings, `std::shared_ptr` in XmUGrid/UGridClipper).

**Why:** Callers must convert between three incompatible smart-pointer types to move objects across one library's APIs.

### **M23**: `xmsgrid/triangulate/TrTin.cpp:719` (also `:754`) — bounds check accepts index == size `[unvalidated]`

```cpp
  XM_ENSURE_TRUE_NO_ASSERT(a_point >= 0 && a_point <= (int)(*m_pts).size(), XM_NONE);
  XM_ENSURE_TRUE_NO_ASSERT(!(*m_trisAdjToPts)[a_point].empty(), XM_NONE);
```

**Change:** Use `<` instead of `<=`.

**Why:** Off-by-one lets `a_point == size` through to `(*m_trisAdjToPts)[a_point]` on the next line: out-of-bounds read.

### **M24**: `xmsgrid/triangulate/TrTin.h:52-58` — mutable references expose desynchronisable invariants `[unvalidated]`

```cpp
  virtual VecPt3d& Points() = 0;
  virtual VecInt& Triangles() = 0;
  virtual VecInt2d& TrisAdjToPts() = 0; // Triangles adjacent to points
```

**Change:** Return const references publicly and add validated mutators, or route mutation through a builder that re-syncs adjacency. The const overloads at :56-58 already exist.

**Why:** Callers can resize points or triangles independently of `TrisAdjToPts`, breaking the triangulation invariant with no enforcement path.

### **M25**: `xmsgrid/triangulate/detail/TrAutoFixFourTrianglePts.cpp:228-233` — `a_edges.find()` result dereferenced without `end()` check `[unvalidated]`

```cpp
  auto e = a_edges.begin();
  for (int t = 0; t < 4; ++t)
  {
    bound[t] = e->first;
    e = a_edges.find(e->second);
  }
```

**Change:** Check `e != a_edges.end()` inside the loop and bail out. `Fix()` has no guard for boundary points; tests avoid it only via `SetUndeleteablePtIdxs`.

**Why:** Boundary points with 4 adjacent triangles do not form a closed cycle, so `find` returns `end()` and the next iteration dereferences it.

### **M26**: `xmsgrid/triangulate/detail/triangulate.cpp:1724` — `triMakeTriangle` never checks `triPoolAlloc` for null `[unvalidated]`

```cpp
static bool triMakeTriangle(Tedgetype newtedge, TriVars& t)
{
  newtedge->tri = (Ttri*)triPoolAlloc(&t.m_triangles);

  /* Init the adjoining tris to be "outer space" */
  newtedge->tri[0] = (Ttri)t.m_dummytri;
```

**Change:** Return false when `triPoolAlloc` returns null (calloc failure at :2296-2301); same for `triGetPoints` at :980.

**Why:** The function returns true unconditionally, so the "past 32-bit limit" checks at :563/:595 are dead and a null `Ttri*` is dereferenced.

### **M27**: `xmsgrid/triangulate/detail/triangulate.cpp:2678-2705` — failed `triDivConqDelaunay` reports success and leaks `[unvalidated]`

```cpp
      bool ok = triDivConqDelaunay(t);
      if (ok)
      {
        triNumberNodes(t);
        triFillTriList(a_Client, t);
        triPoolDeinit(&t.m_triangles);
        if (t.m_dummytribase)
          free(t.m_dummytribase);
      }
    }
    triPoolDeinit(&t.m_points);
    a_Client.FinalizeTriangulation();
  }
  ...
  return true;
```

**Change:** On `!ok`, free the triangle pool and `m_dummytribase` and return false; add an `XM_LOG` at :493 where `divider == 0` (all points coincident) currently emits nothing.

**Why:** Caller gets zero triangles, a `true` return, and no log; `m_triangles` and `m_dummytribase` leak.

### **M28**: `xmsgrid/ugrid/XmUGrid.cpp:2357-2360` — `GetCellEdge` POLY_LINE/POLYGON indexes with no upper bound; POLY_LINE wraps `[unvalidated]`

```cpp
    case XMU_POLY_LINE:
    case XMU_POLYGON:
    {
      int numPoints = cellstream[1];
      const int* cellPoints = cellstream.data() + 2;
      int idx1 = cellPoints[a_edgeIdx];
      int idx2 = cellPoints[(a_edgeIdx + 1) % numPoints];
```

**Change:** Bounds-check `a_edgeIdx` against `numPoints` (the default case at :2379 does), and do not wrap for `XMU_POLY_LINE`.

**Why:** Out-of-range `a_edgeIdx` reads past the cell stream, and POLY_LINE produces a spurious closing edge from last point to first.

### **M29**: `xmsgrid/ugrid/XmUGrid.cpp:2956-2960` — `GetPlanViewPolygon3d` returns true after `iMergeSegmentsToPoly` failure `[unvalidated]`

```cpp
  if (GetCellXySegments(a_cellIdx, segments))
  {
    // Prismatic cell
    iMergeSegmentsToPoly(segments, a_polygon);
    return true;
  }
```

**Change:** `return !a_polygon.empty();` (contrast `GetPlanViewPolygon2d` at :2938-2942). `iMergeSegmentsToPoly`'s failure signal is `XM_ASSERT(0)` + `a_polygon.clear()` at :708-710, which the test at :6613-6617 relies on.

**Why:** Production callers receive success with an empty polygon.

### **M30**: `xmsgrid/ugrid/XmUGrid.cpp:6698-6701` — `testGoodQuad` tests `XMU_PIXEL` `[unvalidated]`

```cpp
void CellStreamValidationUnitTests::testGoodQuad()
{
  iTestGoodCellStream({XMU_PIXEL, 4, 1, 2, 3, 4});
} // CellStreamValidationUnitTests::testGoodQuad
```

**Change:** Change the literal to `XMU_QUAD`.

**Why:** It is an exact duplicate of `testGoodPixel` (:6690-6693); QUAD cell-stream validation is untested under a name that says otherwise.

### **M31**: `xmsgrid/ugrid/XmUGridUtils.cpp:297` (also `:308, :313, :321, :326`; v2 `:347, :366, :374, :379`) — reader ignores `daReadIntFromLine`/`ReadInt` return values `[unvalidated]`

```cpp
    int numFaces;
    std::string faceString;
    daReadIntFromLine(a_cellLine, numFaces);
    a_cellstream.push_back(numFaces);
```

**Change:** Check each return value and fail the read on false.

**Why:** A malformed file pushes uninitialised ints into the cell stream.

### **M32**: `xmsgrid/ugrid/XmUGridUtils.cpp:704` — `std::ofstream` never checked with `is_open()` `[unvalidated]`

```cpp
void XmWriteUGridToAsciiFile(std::shared_ptr<XmUGrid> a_ugrid, const std::string& a_filePath)
{
  std::ofstream outFile(a_filePath);
  XmWriteUGridToStream(a_ugrid, outFile);
}
```

**Change:** Check `outFile.is_open()`, log via `XM_LOG`, and return.

**Why:** An unwritable path silently produces no file.

### **M33**: `xmsgrid/ugrid/detail/UGridClipper.cpp:59-60` — `cells[0]` after `XM_ASSERT(cells.size() > 0)` `[unvalidated]`

```cpp
  XM_ASSERT(cells.size() > 0);
  int left = cells[0];
  int right = cells.size() > 1 ? cells[1] : -1;
```

**Change:** Return or skip when `cells` is empty.

**Why:** UB in release when a loop edge has no adjacent cells.

### **M34**: `xmsgrid/ugrid/detail/UGridClipper.cpp:68` — `opposite` stays -1 for non-triangle cells, indexes `locations[-1]` at :81 `[unvalidated]`

```cpp
  XM_ASSERT(points.size() == 3);

  for (const auto& point : points)
  {
    if (point != a_a && point != a_b)
    {
      opposite = point;
      break;
    }
  }
  ...
  if (!gmStrictlyLeftTurn(&locations[a_a], &locations[a_b], &locations[opposite]))
```

**Change:** Guard `opposite < 0` before :81.

**Why:** Out-of-bounds read for any non-triangle cell in release.

### **M35**: `xmsgrid/ugrid/detail/UGridClipper.cpp:587,788,811` — tests reference external fixtures with bare index literals (Mystery Guest) `[unvalidated]`

```cpp
  auto grid = XmReadUGridFromAsciiFile(ClipperFilesPath + "octagon.xmugrid");
  VecInt2d loops = {{9, 3, 10}, {7, 6, 5, 4, 3, 2, 1, 0}};
  VecInt expectedVisit = {15, 15, 15};
```

**Change:** Add a comment or diagram describing the fixture geometry (octagon.xmugrid, horn*.xmugrid) next to the index lists.

**Why:** Literals like `{59,60,61,42,71,...}` are meaningless without opening the fixture file, so a failure cannot be diagnosed from the test alone.

---

## Minor items

- `_package/tests/unit_tests/geometry_tests/geometry_pyt.py:139,154,172,180,184,188` — hard-coded floats like 0.7071067811865476 with no derivation; comment the formula.
- `_package/tests/unit_tests/geometry_tests/multi_poly_intersector_pyt.py:67-111` — two structurally identical `_run_test` tests; use `@pytest.mark.parametrize` with ids.
- `_package/tests/unit_tests/triangulate_tests/tin_pyt.py:299-301` — `# TODO: I don't think this is right.` on assertions; resolve TODO, confirm expected values.
- `_package/tests/unit_tests/ugrid_tests/edge_pyt.py` and `ugrid_utils_pyt.py` — `get_3d_linear_ugrid` and round-trip test duplicated verbatim; move builders to a shared helper.
- `_package/tests/unit_tests/ugrid_tests/ugrid_pyt.py:1-1223` — single 1223-line TestUGrid class; split into a class per feature.
- `_package/tests/unit_tests/ugrid_tests/ugrid_pyt.py:604-624,760-763,806-811,820-823,830-834,906-918` — assertEqual in nested loops with no message; add `msg=f"cell {i} face {j}"`.
- `_package/tests/unit_tests/ugrid_tests/ugrid_pyt.py:721-758,768-805,868-904` — 31-entry `expected_cell_faces` copy-pasted three times; hoist to a fixture.
- `_package/xms/grid/geometry/geometry.py:1` — no module docstring; add one.
- `_package/xms/grid/geometry/geometry.py:42-56` — `get_tol_2d`/`set_tol_2d` mutate global C++ state via free functions; wrap or document call-order sensitivity.
- `_package/xms/grid/geometry/multi_poly_intersector.py:19` — `query` typed as bare str; use `Literal['covered_by', 'intersects']`.
- `_package/xms/grid/geometry/multi_poly_intersector.py:52-56` — `__eq__` prints to stdout, no `__hash__`; return NotImplemented, set `__hash__ = None`.
- `_package/xms/grid/geometry/multi_poly_intersector.py:70-77` — commented-out dead code; delete.
- `_package/xms/grid/geometry/tri_search.py:17-20` — `if not points:` misbehaves on numpy arrays; use `is None` checks.
- `_package/xms/grid/geometry/tri_search.py:36-40` — `__eq__` prints to stdout, no `__hash__`; return NotImplemented, `__hash__ = None`.
- `_package/xms/grid/triangulate/tin.py:37-41` — `__eq__` prints to stdout, no `__hash__`; return NotImplemented, `__hash__ = None`.
- `_package/xms/grid/ugrid/ugrid.py:44-48` — `__eq__` prints to stdout, no `__hash__`; return NotImplemented, `__hash__ = None`.
- `_package/xms/grid/ugrid/ugrid_utils.py:28-38` — `edges_equivalent` has no Python-level test; add a one-line assertion.
- `generateDocumentationAndDeploy.sh:84` — `doxygen ... | tee` under `set -e` without pipefail masks crash; add `set -o pipefail` after line 41.
- `xmsgrid/geometry/GmExtents.cpp:97` — needless copy of the Pt3d argument; use the const reference.
- `xmsgrid/geometry/GmExtents.cpp:358-390` (decl `GmExtents.h:127`) — `GmExtents3d::Overlap` takes non-const reference; use `const GmExtents3d&`.
- `xmsgrid/geometry/GmMultiPolyIntersectionSorterTerse.cpp:280` (also `:290, :308`) — signed/unsigned comparisons, inconsistent braces; use size_t.
- `xmsgrid/geometry/GmMultiPolyIntersector.cpp:302` — unused local `pt`; remove.
- `xmsgrid/geometry/GmMultiPolyIntersector.cpp:305` — `poly[0]` on possibly empty polygon; skip empty polygons.
- `xmsgrid/geometry/GmMultiPolyIntersector.cpp:338` — raw `new` into shared_ptr; use make_shared.
- `xmsgrid/geometry/GmMultiPolyIntersectorData.h:24-44` — class `ix` all-public with non-explicit 3-arg ctor; consider struct.
- `xmsgrid/geometry/GmMultiPolyIntersectorData.h:39` — `ix::operator==` not const; add const.
- `xmsgrid/geometry/GmPolyLinePtRedistributer.cpp:158` — `(t1 - t0) == 0` yields NaN; guard zero-length segment.
- `xmsgrid/geometry/GmPolygon.cpp:297` (also `TrTin.cpp:1476`, `TrTriangulatorPoints.cpp:240`, `TrAutoFixFourTrianglePts.cpp:410`, `TrOuterTriangleDeleter.cpp:294`) — `#if CXX_TEST` instead of `#ifdef`; use `#ifdef` consistently.
- `xmsgrid/geometry/GmPtSearch.cpp:284-285` (also `:330-331`) — delete-then-new dangles if new throws; use unique_ptr.
- `xmsgrid/geometry/GmPtSearch.cpp:318-319` — dead code; delete.
- `xmsgrid/geometry/GmPtSearch.cpp:351-378` — min/max extents computed twice; extract helper.
- `xmsgrid/geometry/GmPtSearch.cpp:489` — unchecked index into `m_bshpPt3d`; XM_ENSURE index in range.
- `xmsgrid/geometry/GmPtSearch.cpp:559` — unused locals; remove.
- `xmsgrid/geometry/GmTriSearch.cpp:443` — trailing comment names wrong function; correct.
- `xmsgrid/geometry/GmTriSearch.cpp:619-621` — same map lookup twice; cache the iterator.
- `xmsgrid/geometry/geoms.cpp:270` (also `:2517, :5316-5318, :5452`) — raw malloc/free in C++; use std::vector.
- `xmsgrid/geometry/geoms.cpp:743-758` — both `#if BOOST_OS_WINDOWS` branches identical; remove conditional.
- `xmsgrid/geometry/geoms.cpp:1519` — `&a_verts[0]` on possibly empty vector; check empty first.
- `xmsgrid/geometry/geoms.cpp:2270` — mixes gmXyTol and hard-coded epsilon; use one tolerance.
- `xmsgrid/geometry/geoms.cpp:2280` — returns squared distance while doc says distance; fix doc or sqrt.
- `xmsgrid/geometry/geoms.cpp:2639` — realloc with size 0; guard n == 0.
- `xmsgrid/geometry/geoms.cpp:3537` — comment contradicts code; correct comment.
- `xmsgrid/geometry/geoms.cpp:4248` — `#define SWAP` inside function body, never undef; use std::swap.
- `xmsgrid/geometry/geoms.cpp:4252-4253` — mixed `&&`/`||` without parentheses; parenthesize.
- `xmsgrid/geometry/geoms.cpp:4898-4899` — divide by count with no empty guard; return early on empty.
- `xmsgrid/geometry/geoms.cpp:5131` — `*c < tol` should compare `fabs(*c)`; use fabs.
- `xmsgrid/geometry/geoms.cpp:6152-6158` — `gmComputeCentroid` divides by size() with no empty guard; return early.
- `xmsgrid/geometry/geoms.cpp:6207-6208` — signed area of 0 divides by zero; guard area == 0.
- `xmsgrid/geometry/geoms.cpp:6342-6348` (also `:6374-6380`) — Newton iteration with no cap; add max-iterations.
- `xmsgrid/matrices/matrix.cpp:104` (also `:216`) — `if (j != n)` always true; remove dead condition.
- `xmsgrid/matrices/matrix.cpp:297` — malloc result not null-checked; check or use vector.
- `xmsgrid/matrices/matrix.cpp:344-351` — same condition checked twice; remove duplicate.
- `xmsgrid/matrices/matrix.cpp:565` — memcpy without `<cstring>`; include it.
- `xmsgrid/python/geometry/GmTriSearch_py.cpp:68` — comment says GetPoints for GetTriangles; correct.
- `xmsgrid/python/geometry/geometry_py.cpp:9` — unused `<iostream>`; remove.
- `xmsgrid/python/geometry/geometry_py.cpp:56` — `gmSetXyTol` exposes process-global tolerance to Python; document or scope.
- `xmsgrid/python/triangulate/TrTin_py.cpp:236` — wrong function name in comment; correct.
- `xmsgrid/python/ugrid/XmUGrid_py.cpp:27` — `XmEdgeFromPyIter` duplicated in `XmUGridUtils_py.cpp:29`; share one helper.
- `xmsgrid/python/xmsgrid_py.cpp:19` — `#define XMS_VERSION "99.99.99";` trailing semicolon; drop it.
- `xmsgrid/triangulate/TrBreaklineAdder.cpp:102-104` — raw pointers into TrTin vectors dangle after SetPoints; re-fetch or hold shared_ptr.
- `xmsgrid/triangulate/TrBreaklineAdder.cpp:181` (also `:210`) — `size() - 1` on empty breakline underflows; guard empty.
- `xmsgrid/triangulate/TrBreaklineAdder.cpp:248` (also `:284`) — `//#if 0` leftovers; delete.
- `xmsgrid/triangulate/TrBreaklineAdder.cpp:557` (also `:579`) — undocumented throw from deep helper; document or convert to return/log.
- `xmsgrid/triangulate/TrTin.cpp:312` (also `:340, :382`) — `(*m_trisAdjToPts)[a_pt1]` unchecked; guard index.
- `xmsgrid/triangulate/TrTin.cpp:959` (also `:974, :989`) — pointer-difference predicate via boost::bind is fragile; use lambda with index.
- `xmsgrid/triangulate/TrTin.cpp:1205` — `l12 / (l23 + l31)` divides by zero for degenerate triangle; guard denominator.
- `xmsgrid/triangulate/TrTriangulatorPoints.cpp:140` — `m_pts[m_idx]` unchecked; bounds-check m_idx.
- `xmsgrid/triangulate/detail/TrAutoFixFourTrianglePts.cpp:55` — `SetUndeleteablePtIdxs` takes non-const `VecInt&`; use const&.
- `xmsgrid/triangulate/detail/TrAutoFixFourTrianglePts.cpp:70-71` — duplicate `private:`; remove one.
- `xmsgrid/triangulate/detail/TrAutoFixFourTrianglePts.cpp:77` (also `:123, :187`) — wrong trailing function comments; correct.
- `xmsgrid/triangulate/detail/TrAutoFixFourTrianglePts.cpp:83` — non-const reference params for inputs; use const&.
- `xmsgrid/triangulate/detail/TrAutoFixFourTrianglePts.cpp:135` — unused `itEnd`; remove.
- `xmsgrid/triangulate/detail/TrOuterTriangleDeleter.cpp:115` (also `:157-159`) — `.front()`/`++it1` on empty polygon; skip empty polygons.
- `xmsgrid/triangulate/detail/triangulate.cpp:43-44` — pointmark macros type-pun `double*` as `int*`; use memcpy or a struct.
- `xmsgrid/triangulate/detail/triangulate.cpp:49` (also `:55`) — pointer tag bits via `unsigned long long`; use uintptr_t.
- `xmsgrid/triangulate/detail/triangulate.cpp:457-459` — `int size = m_numpoints * sizeof(Tpt)` overflows; use size_t.
- `xmsgrid/triangulate/detail/triangulate.cpp:957` (also `:1706`) — `#define` inside function body; file-scope constexpr.
- `xmsgrid/triangulate/detail/triangulate.cpp:1118` — memset without `<cstring>`; include it.
- `xmsgrid/triangulate/detail/triangulate.cpp:1711` — `elemattid` computed and unused; remove.
- `xmsgrid/triangulate/detail/triangulate.cpp:2421` — `triPoolRestart` doc copy-pasted from `triRandomnation`; correct.
- `xmsgrid/triangulate/detail/triangulate.cpp:2457` — static `randomseed` shared across threads; move into TriVars.
- `xmsgrid/triangulate/detail/triangulate.cpp:2669` — `throw - 1;` as control flow; return false directly.
- `xmsgrid/triangulate/detail/triangulate.cpp:2698-2704` — `catch(...)` frees pools but not `m_dummytribase`; free it too.
- `xmsgrid/triangulate/detail/triangulate.cpp:2698-2704` — `catch(...)` logs fixed string with no `what()`; catch `std::exception&` first and log it.
- `xmsgrid/ugrid/XmUGrid.cpp:834` (also `:875, :915, :926, :956, :1017, :1207, :1219, :1259, :1272, :1825, :2966`) — signed/unsigned comparisons; use size_t.
- `xmsgrid/ugrid/XmUGrid.cpp:997` — default case validates count against itself (tautology); reject unknown cell types.
- `xmsgrid/ugrid/XmUGrid.cpp:1341-1346` — `#if _DEBUG` + `assert("...")` never fires; use `XM_ASSERT(false)`/`XM_LOG`.
- `xmsgrid/ugrid/XmUGrid.cpp:2179` — `centroid /= cellPoints.size()` for empty cell; guard empty.
- `xmsgrid/ugrid/XmUGrid.cpp:2739-2742` — `VecInt2d faces(numFaces)` with numFaces == -1 throws length_error; guard numFaces < 0.
- `xmsgrid/ugrid/XmUGrid.cpp:2799-2800` (also `:2841-2842`) — duplicated `a_neighborFace = faceIdx;`; remove duplicate.
- `xmsgrid/ugrid/XmUGrid.cpp:3163` — `assert("...")` string-literal pattern never fires; use `XM_ASSERT(false)`.
- `xmsgrid/ugrid/XmUGrid.cpp:3466` — `gmPolygonArea(&facePts[0], ...)` on possibly empty facePts; guard empty.
- `xmsgrid/ugrid/XmUGrid.cpp:3894-3897` (also `:3907-3911`) — doc separator inside parameter list; move separator.
- `xmsgrid/ugrid/XmUGridUtils.cpp:212` — trailing comment names wrong function; correct.
- `xmsgrid/ugrid/XmUGridUtils.cpp:615` — ifstream open unchecked, generic error log; check is_open, specific message.
- `xmsgrid/ugrid/XmUGridUtils.cpp:818` (also `:833`) — `newPtIdxs[oldPtIdx]` may be XM_NONE, assert-only; validate and fail.
- `xmsgrid/ugrid/detail/UGridClipper.cpp:133-135` — empty loop: `b++` past end and `a_loop[0]` at :145; return on empty loop.
- `xmsgrid/ugrid/detail/UGridClipper.cpp:361` — signed/unsigned comparison; use size_t.
- `xmsgrid/ugrid/detail/UGridClipper.cpp:820-822` — `testClipUgrid` writes output into shared fixture directory; write to per-test temp path.
- `xmsgrid/ugrid/detail/XmGeometry.cpp:73` (also `:79`) — signed/unsigned comparison; use size_t.
- `xmsgrid/ugrid/detail/XmGeometry.cpp:103` — stray `;`; remove.

Additional 1 MINOR finding already covered above by higher-severity entries (writer-reviewer's `GmExtents.cpp:108` IsValid-non-const, merged into M6).

---

Bookkeeping: the rollup header states MINOR=98 but lists R48–R148 (101 entries); the Minor section above carries all 101 as written. Dropped in validation: R9 (`XmUGrid.cpp:3497-3554` CalculateCellOrdering nesting), R13 (placeholder-path round-trip tests; validator found the ASCII path is exercised, only hygiene remains), R15 (primitive obsession in Python wrapper signatures). The validator's unrelated observation on C7 (stale `pts[tmpnpts].z` in the `y0 == y1` branches) was not part of any specialist finding and is not reported as one.
