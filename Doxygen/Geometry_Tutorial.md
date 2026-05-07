# Geometry Tutorial

\tableofcontents
# Geometry Tutorial {#Geometry_Tutorial}

## Introduction {#Intro_Geometry}

The `xmsgrid/geometry` module supplies the geometric primitives, spatial
indexes, and free functions used throughout xmsgrid and by the consuming
xms libraries (xmsinterp, xmsmesher, xmsextractor, xmsstamper). This tutorial
covers the parts of the module that are most commonly consumed from outside
xmsgrid. For grid-level geometry queries (cell centroid, cell extents, plan
view polygon) see the [2D](TwoD_Tutorial.md) and [3D](ThreeD_Tutorial.md) UGrid
tutorials.

## Factory Convention {#Geometry_FactoryConvention}

Most xmsgrid classes follow the interface pattern: an abstract base class is
the only public type, and a static `New()` member returns a `BSHP<T>`
(boost shared pointer) to the concrete `Impl` instance. Examples in the
geometry module:

* xms::GmTriSearch::New()
* xms::GmPtSearch::New(bool a_2dSearch)
* xms::GmPolygon::New()
* xms::GmMultiPolyIntersector::New(points, polys, sorter, startingId)

Because consumers only ever hold the shared pointer, copying and assigning
these types is disabled. Always create instances through `New()`; never
attempt to construct them directly.

The notable exception is xms::TrTriangulatorPoints, which is a concrete
class with a public constructor (see the [Triangulate
Tutorial](Triangulate_Tutorial.md)).

## Spatial Search: GmTriSearch {#Geometry_GmTriSearch}

xms::GmTriSearch indexes a set of triangles for point-in-triangle and
envelope-overlap queries, and exposes interpolation-weight helpers. The
typical workflow is:

1. Create the searcher with xms::GmTriSearch::New().
2. Hand it the points and triangle indices via xms::GmTriSearch::TrisToSearch.
   Both arguments are `BSHP<>` containers that the searcher *holds by
   reference*; the caller must keep them alive for the lifetime of the
   searcher.
3. Optionally restrict which points or triangles participate via
   xms::GmTriSearch::SetPtActivity / xms::GmTriSearch::SetTriActivity. The
   activity is a `DynBitset` (one bit per point or per triangle) where bit
   `i` set to true means index `i` is active.
4. Query with xms::GmTriSearch::TriContainingPt,
   xms::GmTriSearch::TriEnvelopsContainingPt, or
   xms::GmTriSearch::TriEnvelopesOverlap. Use
   xms::GmTriSearch::InterpWeights or
   xms::GmTriSearch::InterpWeightsTriangleIdx to retrieve barycentric
   interpolation weights at a point.

This is the spatial backbone of xmsinterp's linear and natural-neighbor
interpolators. xmsextractor uses it to look up the cell that contains an
extraction point.

## Spatial Search: GmPtSearch {#Geometry_GmPtSearch}

xms::GmPtSearch indexes a set of points for nearest-neighbor and
within-distance queries. The boolean argument to xms::GmPtSearch::New
selects the index dimensionality:

* `New(true)` builds a 2D R-tree (the Z component is ignored). Use this
  when "nearest" is measured in plan view.
* `New(false)` builds a 3D R-tree.

Pass the points to xms::GmPtSearch::PtsToSearch (held by reference). For
incremental construction, use xms::GmPtSearch::VectorThatGrowsToSearch
together with xms::GmPtSearch::AddPtToVectorIfUnique, which only inserts
points that are not within tolerance of an existing one. Activity is
controlled with xms::GmPtSearch::SetActivity / xms::GmPtSearch::GetActivity.

Common queries:

* xms::GmPtSearch::NearestPtsToPt - find the N points closest to a given
  point, with an optional quad/oct-tree mode that biases the result to be
  spread across quadrants/octants rather than clustered.
* xms::GmPtSearch::PtsWithinDistanceToPtInRtree - all points within a given
  distance.
* xms::GmPtSearch::PtInRTree - check whether a point already exists within
  tolerance.

## Polygons: GmPolygon {#Geometry_GmPolygon}

xms::GmPolygon wraps a `boost::geometry::polygon` so callers can avoid a
direct boost dependency. Construct with xms::GmPolygon::New, then call
xms::GmPolygon::Setup with the outer boundary and a list of inner
boundaries (holes). After setup the polygon can:

* Test point containment with xms::GmPolygon::CoveredBy (boundary counts as
  inside) or xms::GmPolygon::Within (strict interior).
* Compute distance from a point to the polygon boundary with
  xms::GmPolygon::MinDistanceToBoundary.
* Combine with another polygon via xms::GmPolygon::Intersection or
  xms::GmPolygon::Union, both of which return a vector of result polygons.

## Multi-polygon Intersection: GmMultiPolyIntersector {#Geometry_GmMultiPolyIntersector}

xms::GmMultiPolyIntersector intersects a 2D line segment with many
polygons at once and reports the polygons that the segment crossed in the
order it crossed them. This is used by xmsmesher (mesh generation across
domains), xmsextractor (extraction-line traversal), and xmsstamper.

The factory takes four arguments:

* `a_points` - one shared point list referenced by every polygon.
* `a_polys` - polygons described as 0-based index lists into `a_points`. The
  first point is **not** repeated as the last point.
* `a_sorter` - a `BSHP<GmMultiPolyIntersectionSorter>` that decides how the
  raw intersection events are ordered. The standard choice is
  xms::GmMultiPolyIntersectionSorterTerse, which produces a compact
  enter/exit run per polygon. The sorter is decoupled from the intersector
  so callers can substitute alternative orderings without re-implementing
  the geometry.
* `a_startingId` - id of the first polygon (default 1). A returned id of
  `-1` is the special end marker.

Use xms::GmMultiPolyIntersector::SetQuery to switch between
`GMMPIQ_COVEREDBY` (segment must be covered by the polygon) and
`GMMPIQ_INTERSECTS` (any non-empty intersection counts). The
xms::GmMultiPolyIntersector::TraverseLineSegment overloads return the
sequence of polygon ids, plus optionally the parametric `t` values along
the line and/or the actual intersection points. xms::GmMultiPolyIntersector::PolygonFromPoint
returns the id of the polygon containing a single point.

## Polyline Redistribution: GmPolyLinePtRedistributer {#Geometry_GmPolyLinePtRedistributer}

xms::GmPolyLinePtRedistributer redistributes the points along a polyline to
target a desired spacing. Construct with `New()`, supply the polyline, and
call the redistribute method to receive a new polyline whose vertices are
spaced at (approximately) the requested distance.

## Free Functions in geoms.h {#Geometry_FreeFunctions}

`xmsgrid/geometry/geoms.h` contains a large set of free functions for low
level geometric tests. The most commonly consumed ones are listed below.
Refer to the header for the full list and exact signatures.

### Tolerance management

* xms::gmGetXyTol / xms::gmSetXyTol - read or override the global 2D
  tolerance used by helpers that don't take an explicit `tol`.
* xms::gmEqualPointsXY - compare two `Pt3d`s in plan view (Z ignored)
  within tolerance.

### Polygon and area

* xms::gmPointInPolygon2D - return +1 inside, 0 on boundary, -1 outside.
* xms::gmPolygonArea - signed plan-view area; positive for CCW polygons.
* xms::gmComputePolygonCentroid - plan-view centroid of a non
  self-intersecting polygon.

### Lines and segments

* xms::gmOnLineWithTol - test whether a point lies on the infinite line
  through two points.
* xms::gmOnLineAndBetweenEndpointsWithTol - same, but constrained to the
  segment.
* xms::gmInsideOrOnLineWithTol / xms::gmInsideOfLineWithTol - half-plane
  tests against a reference point.
* xms::gmLinesIntersect - boolean segment-segment intersection.
* xms::gmIntersectLineSegmentsWithTol - segment-segment intersection that
  also returns the intersection coordinates and z-values from each
  segment. Prefer xms::gmIntersectLineSegments where the tolerance variant
  is not required (the comment in `geoms.cpp` flags subtle behavior in the
  `WithTol` variant).
* xms::gmFindClosestPtOnSegment / xms::gmPtDistanceAlongSegment - project a
  point onto a segment.
* xms::gm2DDistanceToLineSegmentWithTol / xms::gm2DDistanceToLineWithTol -
  distance helpers.

### Vectors and angles

* xms::gmTurn - returns one of `TURN_LEFT`, `TURN_RIGHT`,
  `TURN_COLINEAR_180` (the three points lie on a line and the third
  continues past the second), or `TURN_COLINEAR_0` (the third point
  doubles back along the segment). The optional angle tolerance
  controls when nearly-collinear configurations are flagged as one of
  the colinear values. Used heavily by xmsextractor's triangle
  traversal code.
* xms::gmCross2D / xms::gmCross3D - 2D and 3D cross products.
* xms::gmAngleBetweenEdges - CCW angle (0..2pi) between two edges sharing
  a vertex.
* xms::gmBisectingAngle, xms::gmPerpendicularAngle, xms::gmConvertAngleToBetween0And360
  - angle utilities used by mesh smoothing and stamping.

### Triangle helpers

* xms::gmIntersectTriangleAndLineSegment - intersect a 3D triangle with a
  line segment; used by xmsstamper for surface clipping.
* xms::gmBaryPrepare / xms::gmCartToBary - precompute and apply
  barycentric coordinate transforms, used by interpolation.

### Extents

* xms::gmExtents2D / xms::gmExtents3D - bounding box from a point set.
  Despite the name, xms::gmExtents2D operates on `Pt3d` inputs and simply
  ignores Z.
* xms::gmAddToExtents - grow an existing min/max pair to include a new
  point.

## Reference vs. Copy Semantics {#Geometry_ReferenceSemantics}

Several geometry classes hold the input data by reference rather than
copying it:

* xms::GmTriSearch::TrisToSearch - holds the supplied points and triangle
  vectors by `BSHP<>`.
* xms::GmPtSearch::PtsToSearch and xms::GmPtSearch::VectorThatGrowsToSearch
  - same.
* xms::TrTriangulatorPoints - holds references to the caller's `points`
  and output `tris` / `trisAdjToPts` (see Triangulate tutorial).

Callers must keep these vectors alive (and unmodified, where applicable)
for the lifetime of the dependent object. Mutating the underlying vector
while a search is active will produce undefined behavior.
