# Triangulate Tutorial

\tableofcontents
# Triangulate Tutorial {#Triangulate_Tutorial}

## Introduction {#Intro_Triangulate}

The `xmsgrid/triangulate` module provides:

* xms::TrTin - a triangulated irregular network (TIN) with topology and
  the modifiers needed to maintain it.
* xms::TrTriangulator (abstract) and xms::TrTriangulatorPoints (concrete)
  - build triangles from a point cloud.
* xms::TrBreaklineAdder - insert constraint lines into an existing TIN.

These types are used by xmsmesher (mesh generation), xmsinterp (linear and
natural-neighbor surfaces), and xmsstamper (terrain modification). The
patterns they share are documented here.

## TrTin: Lifecycle {#Triangulate_TrTinLifecycle}

xms::TrTin follows the interface pattern: the only public type is the
abstract base class, and instances are created via xms::TrTin::New() which
returns a `BSHP<TrTin>`. After construction the TIN is empty; populate it
in one of three ways:

1. Call xms::TrTin::SetPoints, xms::TrTin::SetTriangles, and
   xms::TrTin::SetTrianglesAdjacentToPoints separately. Each setter takes
   a `BSHP<>` to the underlying vector and stores the pointer; the TIN
   *shares ownership* with the caller. This means later mutations to the
   vector via the original pointer are visible to the TIN.
2. Call xms::TrTin::SetGeometry to install all three at once.
3. Set only points (without triangles), then run a triangulator (see
   below) writing into xms::TrTin::TrianglesPtr().

xms::TrTin::BuildTrisAdjToPts rebuilds the adjacency table from the current
points and triangles - call this after manually editing triangles when you
also need topology queries (xms::TrTin::AdjacentTriangle,
xms::TrTin::TriangleAdjacentToEdge, xms::TrTin::CommonEdgeIndex, etc.).

xms::TrTin::Clear empties all three vectors in place.

### Common queries

* xms::TrTin::Points / xms::TrTin::Triangles / xms::TrTin::TrisAdjToPts -
  references to the underlying vectors.
* xms::TrTin::NumPoints / xms::TrTin::NumTriangles - sizes.
* xms::TrTin::GetExtents - bounding box.
* xms::TrTin::GetBoundaryPoints / xms::TrTin::GetBoundaryPolys - boundary
  topology.
* xms::TrTin::TriangleCentroid / xms::TrTin::TriangleArea - per-triangle
  geometry.
* xms::TrTin::LocalIndex / xms::TrTin::GlobalIndex - convert between
  per-triangle local point indices (0-2) and global point indices.
* xms::TrTin::VerticesAreAdjacent - test whether two points share a
  triangle edge.

### Modifiers

* xms::TrTin::SwapEdge - swap the diagonal between two triangles that
  form a convex quadrilateral. By default the call refuses to swap when
  the resulting triangles would be very thin; pass `a_checkAngle = false`
  to override.
* xms::TrTin::OptimizeTriangulation - iteratively swap edges until the
  triangulation is Delaunay.
* xms::TrTin::DeleteTriangles / xms::TrTin::DeletePoints - remove and
  renumber.
* xms::TrTin::RemoveLongThinTrianglesOnPerimeter - clean up sliver
  triangles around the boundary.

### Serialization

xms::TrTin::ExportTinFile writes a TIN file. xms::TrTin::ToString and
xms::TrTin::FromString round-trip a TIN through a string for use with
boost serialization.

## Building a TIN: TrTriangulatorPoints {#Triangulate_TrTriangulatorPoints}

xms::TrTriangulatorPoints is the only concrete xms::TrTriangulator
implementation in xmsgrid. **Unlike the rest of xmsgrid, this type is not
created via a factory; it has a public constructor**:

\code{.cpp}
xms::VecPt3d points = ...;
xms::VecInt   triangles;             // out parameter; will be populated
xms::VecInt2d trisAdjToPts;          // optional out parameter
xms::TrTriangulatorPoints tri(points, triangles, &trisAdjToPts);
tri.Triangulate();                    // fills triangles and trisAdjToPts
\endcode

Important contract:

* `points` is held by const reference; do not destroy it before calling
  Triangulate().
* `triangles` is held by non-const reference and is **populated by
  Triangulate**. Pass an empty vector unless you have a specific reason
  to seed it.
* `trisAdjToPts` is an optional pointer. Pass `nullptr` if adjacency is
  not needed.
* The triangulator may also be plugged into a TIN via
  xms::TrTin::TrianglesPtr() / xms::TrTin::PointsPtr() to triangulate the
  TIN's points in place.

xmsinterp's Python bindings invoke this constructor implicitly when the
user supplies points without triangles; xmsmesher uses it during mesh
generation.

## Adding Constraints: TrBreaklineAdder {#Triangulate_TrBreaklineAdder}

xms::TrBreaklineAdder inserts constraint edges (breaklines) into an
existing TIN, which is needed to enforce features like ridge lines, river
banks, or mesh boundary requirements. Workflow:

1. Build a TIN from the relevant points (often via TrTriangulatorPoints
   followed by xms::TrTin::OptimizeTriangulation).
2. Create the adder with xms::TrBreaklineAdder::New().
3. Call xms::TrBreaklineAdder::SetTin to attach a `BSHP<TrTin>` and
   optionally override the geometric tolerance (a value <= 0 selects an
   automatic tolerance based on the TIN's extents).
4. Call xms::TrBreaklineAdder::AddBreakline (single polyline as a list of
   point indices) or xms::TrBreaklineAdder::AddBreaklines (multiple).
5. Inspect xms::TrBreaklineAdder::ErrorMessage for any per-breakline
   diagnostics.

Once the adder finishes, the TIN has had its triangulation modified so
that every breakline edge is present. The TIN's points and triangle
vectors are mutated in place.

## Free Helpers {#Triangulate_FreeHelpers}

* xms::trRenumberOnDelete - remap indices in a vector after a deletion
  pass; used internally and exposed for callers that need to update
  parallel data when removing points or triangles.
* xms::trSwapEdgeWithMinAngle - convenience wrapper around
  xms::TrTin::SwapEdge that only swaps when the resulting minimum angle
  exceeds the supplied threshold.
* xms::trBuildGridGeomFromTin (declared in
  `xmsgrid/triangulate/triangles.h`) and other helpers in `triangles.h` -
  small utilities used when bridging to the UGrid representation.

## TrTin to XmUGrid {#Triangulate_TinToUGrid}

A TIN is a flat triangulation; an xms::XmUGrid is a richer unstructured
grid that supports mixed cell types, faces, and 3D topology. xmsgrid does
not provide a built-in TIN-to-UGrid converter, but the conversion is
straightforward: build a cellstream of `[XMU_TRIANGLE, 3, p0, p1, p2]`
entries from xms::TrTin::Triangles and pass it to
xms::XmUGrid::New(points, cellstream). xmsmesher's
`meiUGridFromTin` is one example of a thin wrapper around this conversion.
