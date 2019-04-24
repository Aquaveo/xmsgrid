//------------------------------------------------------------------------------
/// \file
/// \brief Python bindings for XmUGrid.
/// \copyright (C) Copyright Aquaveo 2018. Distributed under FreeBSD License
/// (See accompanying file LICENSE or https://aqaveo.com/bsd/license.txt)
//------------------------------------------------------------------------------

//----- Included files ---------------------------------------------------------
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <boost/shared_ptr.hpp>
#include <xmscore/python/misc/PyUtils.h>
#include <xmsgrid/ugrid/XmEdge.h>
#include <xmsgrid/ugrid/XmUGrid.h>

//----- Namespace declaration --------------------------------------------------
namespace py = pybind11;

//----- Python Interface -------------------------------------------------------
PYBIND11_DECLARE_HOLDER_TYPE(T, boost::shared_ptr<T>);

namespace {
//------------------------------------------------------------------------------
/// \brief Create XmEdge from py::iterable
/// \param[in] a_intpair py::iterable object that represents an XmEdge
/// \return The edge.
//------------------------------------------------------------------------------
xms::XmEdge XmEdgeFromPyIter(const py::iterable& a_intpair)
{
    py::tuple pr = a_intpair.cast<py::tuple>();
    if (py::len(pr) != 2) {
        throw py::type_error("arg must be an 2-tuple");
    } else {
        xms::XmEdge edge(pr[0].cast<int>(), pr[1].cast<int>());
        return edge;
    }
} // XmEdgeFromPyIter

//------------------------------------------------------------------------------
/// \brief Create py::iterable from XmEdge
/// \param[in] a_edge An XmEdge that represents a py::iterable
/// \return a py::iterable
//------------------------------------------------------------------------------
py::iterable PyIterFromXmEdge(const xms::XmEdge& a_edge)
{
  return py::make_tuple(a_edge.GetFirst(), a_edge.GetSecond());
} // PyIterFromXmEdge


//------------------------------------------------------------------------------
/// \brief Create py::iterable from std::vector<std::pair<int, int>>
/// \param[in] a_edge: std::vector<std::pair<int, int>> object that represents a
///     py::iterable
/// \return a py::iterable
//------------------------------------------------------------------------------
py::iterable PyIterFromVecXmEdge(const std::vector<xms::XmEdge>& a_edges)
{
  // NOTE: This is a copy operation
  auto tuple_ret = py::tuple(a_edges.size());
  for (size_t i = 0; i < tuple_ret.size(); ++i) {
    tuple_ret[i] = PyIterFromXmEdge(a_edges.at(i));
  }
  return tuple_ret;
} // PyIterFromVecXmEdge

} // namespace {

void initXmUGrid(py::module &m) {
    // XmUGrid Class
    py::class_<xms::XmUGrid, boost::shared_ptr<xms::XmUGrid>> xmUg(m, "XmUGrid");

  // ---------------------------------------------------------------------------
  // function: init
  // ---------------------------------------------------------------------------
    xmUg.def(py::init([]() {
            return boost::shared_ptr<xms::XmUGrid>(xms::XmUGrid::New());
        }));

    xmUg.def(py::init([](py::iterable pts, py::iterable cellstream) {
            boost::shared_ptr<xms::VecPt3d> points = xms::VecPt3dFromPyIter(pts);
            boost::shared_ptr<xms::VecInt> _cellstream = xms::VecIntFromPyIter(cellstream);
            return boost::shared_ptr<xms::XmUGrid>(xms::XmUGrid::New(*points, *_cellstream));
        }), py::arg("pts"), py::arg("cellstream"));
  // Misc Functions
  // ---------------------------------------------------------------------------
  // function: GetModified
  // ---------------------------------------------------------------------------
    xmUg.def("GetModified", &xms::XmUGrid::GetModified);
    // ---------------------------------------------------------------------------
    // function: SetUnmodified
    // ---------------------------------------------------------------------------
    xmUg.def("SetUnmodified", &xms::XmUGrid::SetUnmodified);
    // ---------------------------------------------------------------------------
    // function: SetUseCache
    // ---------------------------------------------------------------------------
    xmUg.def("SetUseCache", &xms::XmUGrid::SetUseCache);
  // Point Functions
  // ---------------------------------------------------------------------------
  // function: GetPointCount
  // ---------------------------------------------------------------------------
    xmUg.def("GetPointCount", [](xms::XmUGrid &self) -> int {
        return self.GetPointCount();
    });
  // ---------------------------------------------------------------------------
  // function: GetLocations
  // ---------------------------------------------------------------------------
    xmUg.def("GetLocations", [](xms::XmUGrid &self) -> py::iterable {
            return xms::PyIterFromVecPt3d(self.GetLocations());
        });
  // ---------------------------------------------------------------------------
  // function: SetLocations
  // ---------------------------------------------------------------------------
    xmUg.def("SetLocations", [](xms::XmUGrid &self, py::iterable locations) {
            xms::VecPt3d locs = *xms::VecPt3dFromPyIter(locations);
            self.SetLocations(locs);
        }, py::arg("locations"));
  // ---------------------------------------------------------------------------
  // function: GetPointLocation
  // ---------------------------------------------------------------------------
    xmUg.def("GetPointLocation", [](xms::XmUGrid &self, int point_idx) -> py::iterable {
            return xms::PyIterFromPt3d(self.GetPointLocation(point_idx));
        }, py::arg("point_idx"));
  // ---------------------------------------------------------------------------
  // function: SetPointLocation
  // ---------------------------------------------------------------------------
    xmUg.def("SetPointLocation", [](xms::XmUGrid &self, int point_idx, py::iterable location) -> bool {
            xms::Pt3d loc = xms::Pt3dFromPyIter(location);
            return self.SetPointLocation(point_idx, loc);
        }, py::arg("point_idx"),py::arg("location"));
  // ---------------------------------------------------------------------------
  // function: GetPointXy0
  // ---------------------------------------------------------------------------
    xmUg.def("GetPointXy0", [](xms::XmUGrid &self, int point_idx) -> py::iterable {
      return xms::PyIterFromPt3d(self.GetPointXy0(point_idx));
    }, py::arg("point_idx"));
  // ---------------------------------------------------------------------------
  // function: GetPointsLocations
  // ---------------------------------------------------------------------------
    xmUg.def("GetPointsLocations", [](xms::XmUGrid &self, py::iterable point_indices) -> py::iterable {
            boost::shared_ptr<xms::VecInt> pt_indxs = xms::VecIntFromPyIter(point_indices);
            return xms::PyIterFromVecPt3d(self.GetPointsLocations(*pt_indxs));
        }, py::arg("point_indices"));
  // ---------------------------------------------------------------------------
  // function: GetExtents
  // ---------------------------------------------------------------------------
    xmUg.def("GetExtents", [](xms::XmUGrid &self) -> py::iterable {
            xms::Pt3d p_min, p_max;
            self.GetExtents(p_min, p_max);
            return py::make_tuple(xms::PyIterFromPt3d(p_min), xms::PyIterFromPt3d(p_max));
        });
  // ---------------------------------------------------------------------------
  // function: GetPointAdjacentCells
  // ---------------------------------------------------------------------------
    xmUg.def("GetPointAdjacentCells", [](xms::XmUGrid &self, int point_idx) -> py::iterable {
            return xms::PyIterFromVecInt(self.GetPointAdjacentCells(point_idx));
        }, py::arg("point_idx"));
  // ---------------------------------------------------------------------------
  // function: GetPointsAdjacentCells
  // ---------------------------------------------------------------------------
    xmUg.def("GetPointsAdjacentCells", [](xms::XmUGrid &self, py::iterable point_idxs) -> py::iterable {
            boost::shared_ptr<xms::VecInt> points = xms::VecIntFromPyIter(point_idxs);
            return xms::PyIterFromVecInt(self.GetPointsAdjacentCells(*points));
        }, py::arg("point_idxs"));

    // ---------------------------------------------------------------------------
    // function: IsValidPointChange
    // ---------------------------------------------------------------------------
      xmUg.def("IsValidPointChange", [](xms::XmUGrid &self, int point_idx, py::iterable new_location) -> bool {
        return self.IsValidPointChange(point_idx, xms::Pt3dFromPyIter(new_location));
      }, py::arg("point_idx"), py::arg("new_location"));
        // Cell Functions
  // ---------------------------------------------------------------------------
  // function: GetCellCount
  // ---------------------------------------------------------------------------
    xmUg.def("GetCellCount", &xms::XmUGrid::GetCellCount);
  // ---------------------------------------------------------------------------
  // function: GetCellPoints
  // ---------------------------------------------------------------------------
    xmUg.def("GetCellPoints", [](xms::XmUGrid &self, int cell_idx) -> py::iterable {
            return xms::PyIterFromVecInt(self.GetCellPoints(cell_idx));
        }, py::arg("cell_idx"));
// -----------------------------------------------------------------------------
// function: GetCellLocations
// -----------------------------------------------------------------------------
    xmUg.def("GetCellLocations", [](xms::XmUGrid &self, int cell_idx) -> py::iterable {
      xms::VecPt3d locations;
      self.GetCellLocations(cell_idx, locations);
      return xms::PyIterFromVecPt3d(locations);
    }, py::arg("cell_idx"));
  // ---------------------------------------------------------------------------
  // function: GetCellType
  // ---------------------------------------------------------------------------
    xmUg.def("GetCellType", &xms::XmUGrid::GetCellType, py::arg("cell_idx"));
  // ---------------------------------------------------------------------------
  // function: GetDimensionCounts
  // ---------------------------------------------------------------------------
    xmUg.def("GetDimensionCounts", [](xms::XmUGrid &self) -> py::iterable {
            return xms::PyIterFromVecInt(self.GetDimensionCounts());
        });
  // ---------------------------------------------------------------------------
  // function: GetCellDimension
  // ---------------------------------------------------------------------------
    xmUg.def("GetCellDimension", &xms::XmUGrid::GetCellDimension, py::arg("cell_idx"));
  // ---------------------------------------------------------------------------
  // function: GetCellExtents
  // ---------------------------------------------------------------------------
    xmUg.def("GetCellExtents", [](xms::XmUGrid &self, int cell_idx) -> py::iterable {
        xms::VecPt3d extents(2);
        self.GetCellExtents(cell_idx, extents[0], extents[1]);
        return xms::PyIterFromVecPt3d(extents);
    }, py::arg("cell_idx"));
  // ---------------------------------------------------------------------------
  // function: GetCellstream
  // ---------------------------------------------------------------------------
    xmUg.def("GetCellstream", [](xms::XmUGrid &self) -> py::iterable {
            return xms::PyIterFromVecInt(self.GetCellstream());
        });
  // ---------------------------------------------------------------------------
  // function: SetCellstream
  // ---------------------------------------------------------------------------
    xmUg.def("SetCellstream", [](xms::XmUGrid &self, py::iterable cellstream) -> bool {
            boost::shared_ptr<xms::VecInt> _cellstream = xms::VecIntFromPyIter(cellstream);
            return self.SetCellstream(*_cellstream);
        }, py::arg("cellstream"));
  // ---------------------------------------------------------------------------
  // function: GetCellCellstream
  // ---------------------------------------------------------------------------
    xmUg.def("GetCellCellstream", [](xms::XmUGrid &self, int cell_idx) -> py::iterable {
            xms::VecInt cellstream;
            bool ret_val = self.GetCellCellstream(cell_idx, cellstream);
            return py::make_tuple(ret_val, xms::PyIterFromVecInt(cellstream));
        }, py::arg("cell_idx"));
  // ---------------------------------------------------------------------------
  // function: GetCellAdjacentCells
  // ---------------------------------------------------------------------------
    xmUg.def("GetCellAdjacentCells", [](xms::XmUGrid &self, int cell_idx) -> py::iterable {
            return xms::PyIterFromVecInt(self.GetCellAdjacentCells(cell_idx));
        }, py::arg("cell_idx"));
  // ---------------------------------------------------------------------------
  // function: GetCellPlanViewPolygon
  // ---------------------------------------------------------------------------
    xmUg.def("GetCellPlanViewPolygon", [](xms::XmUGrid &self, int cell_idx) -> py::iterable {
            xms::VecPt3d polygon;
            bool ret_val = self.GetCellPlanViewPolygon(cell_idx, polygon);
            return py::make_tuple(ret_val, xms::PyIterFromVecPt3d(polygon));
        }, py::arg("cell_idx"));
  // ---------------------------------------------------------------------------
  // function: GetCellCentroid
  // ---------------------------------------------------------------------------
    xmUg.def("GetCellCentroid", [](xms::XmUGrid &self, int cell_idx) -> py::iterable {
        xms::Pt3d centroid;
        bool ret_val = self.GetCellCentroid(cell_idx, centroid);
        return py::make_tuple(ret_val, xms::PyIterFromPt3d(centroid));
    }, py::arg("cell_idx"));


      // Edges Functions
  // ---------------------------------------------------------------------------
  // function: GetCellEdgeCount
  // ---------------------------------------------------------------------------
    xmUg.def("GetCellEdgeCount", &xms::XmUGrid::GetCellEdgeCount, py::arg("cell_idx"));
  // ---------------------------------------------------------------------------
  // function: GetCellEdge
  // ---------------------------------------------------------------------------
    xmUg.def("GetCellEdge", [](xms::XmUGrid &self, int cell_idx, int edge_idx) -> py::iterable {
            xms::XmEdge edge = self.GetCellEdge(cell_idx, edge_idx);
            return py::make_tuple(edge.GetFirst(), edge.GetSecond());
        }, py::arg("cell_idx"),py::arg("edge_idx"));
  // ---------------------------------------------------------------------------
  // function: GetCellEdgeAdjacentCells
  // ---------------------------------------------------------------------------
    xmUg.def("GetCellEdgeAdjacentCells", [](xms::XmUGrid &self, int cell_idx, int edge_idx) -> py::iterable {
            return xms::PyIterFromVecInt(self.GetCellEdgeAdjacentCells(cell_idx, edge_idx));
        }, py::arg("cell_idx"), py::arg("edge_idx"));
  // ---------------------------------------------------------------------------
  // function: GetCell2dEdgeAdjacentCell
  // ---------------------------------------------------------------------------
    xmUg.def("GetCell2dEdgeAdjacentCell", &xms::XmUGrid::GetCell2dEdgeAdjacentCell,
      py::arg("cell_idx"), py::arg("edge_idx"));
  // ---------------------------------------------------------------------------
  // function: GetEdgeAdjacentCells
  // ---------------------------------------------------------------------------
    xmUg.def("GetEdgeAdjacentCells", [](xms::XmUGrid &self, py::iterable edge) -> py::iterable {
            xms::XmEdge a_edge = XmEdgeFromPyIter(edge);
            return xms::PyIterFromVecInt(self.GetEdgeAdjacentCells(a_edge));
        }, py::arg("edge"));
  // ---------------------------------------------------------------------------
  // function: GetCellEdges
  // ---------------------------------------------------------------------------
    xmUg.def("GetCellEdges", [](xms::XmUGrid &self, int cell_idx) -> py::iterable {
            std::vector<xms::XmEdge> edges = self.GetCellEdges(cell_idx);
            return PyIterFromVecXmEdge(edges);
        }, py::arg("cell_idx"));
  // ---------------------------------------------------------------------------
  // function: GetPointAdjacentPoints
  // ---------------------------------------------------------------------------
    xmUg.def("GetPointAdjacentPoints", [](xms::XmUGrid &self, int point_idx) -> py::iterable {
      xms::VecInt adj_idxs;
      self.GetPointAdjacentPoints(point_idx, adj_idxs);
      return xms::PyIterFromVecInt(adj_idxs);
    }, py::arg("point_idx"));
  // ---------------------------------------------------------------------------
  // function: GetPointAdjacentLocations
  // ---------------------------------------------------------------------------
    xmUg.def("GetPointAdjacentLocations", [](xms::XmUGrid &self, int point_idx) -> py::iterable {
      xms::VecPt3d adj_points;
      self.GetPointAdjacentLocations(point_idx, adj_points);
      return xms::PyIterFromVecPt3d(adj_points);
    }, py::arg("point_idx"));

        // Face Functions
  // ---------------------------------------------------------------------------
  // function: GetCell3dFaceCount
  // ---------------------------------------------------------------------------
    xmUg.def("GetCell3dFaceCount", &xms::XmUGrid::GetCell3dFaceCount, py::arg("cell_idx"));
  // ---------------------------------------------------------------------------
  // function: GetCell3dFacePointCount
  // ---------------------------------------------------------------------------
    xmUg.def("GetCell3dFacePointCount", &xms::XmUGrid::GetCell3dFacePointCount,
      py::arg("cell_idx"), py::arg("face_idx"));
  // ---------------------------------------------------------------------------
  // function: GetCell3dFacePoints
  // ---------------------------------------------------------------------------
    xmUg.def("GetCell3dFacePoints", [](xms::XmUGrid &self, int cell_idx, int face_idx) -> py::iterable {
            return xms::PyIterFromVecInt(self.GetCell3dFacePoints(cell_idx, face_idx));
        }, py::arg("cell_idx"),py::arg("face_idx"));
  // ---------------------------------------------------------------------------
  // function: GetCell3dFacesPoints
  // ---------------------------------------------------------------------------
    xmUg.def("GetCell3dFacesPoints", [](xms::XmUGrid &self, int cell_idx) -> py::iterable {
            return xms::PyIterFromVecInt2d(self.GetCell3dFacesPoints(cell_idx));
        }, py::arg("cell_idx"));
  // ---------------------------------------------------------------------------
  // function: GetCell3dFaceAdjacentCell
  // ---------------------------------------------------------------------------
    xmUg.def("GetCell3dFaceAdjacentCell", [](xms::XmUGrid &self, int cell_idx, int face_idx) -> int {
            return self.GetCell3dFaceAdjacentCell(cell_idx, face_idx);
        }, py::arg("cell_idx"),py::arg("face_idx"));
    // ---------------------------------------------------------------------------
    // function: GetCell3dFaceOrientation
    // ---------------------------------------------------------------------------
    xmUg.def("GetCell3dFaceOrientation", &xms::XmUGrid::GetCell3dFaceOrientation,
      py::arg("cell_idx"), py::arg("face_idx"));

    // UGrid CellType
    py::enum_<xms::XmUGridCellType>(xmUg, "ugrid_celltype_enum",
                                    "ugrid_celltype_enum for UGrid class")
        .value("INVALID_CELL_TYPE",
            xms::XmUGridCellType::XMU_INVALID_CELL_TYPE)
        .value("EMPTY_CELL", xms::XmUGridCellType::XMU_EMPTY_CELL)
        .value("VERTEX", xms::XmUGridCellType::XMU_VERTEX)
        .value("POLY_VERTEX", xms::XmUGridCellType::XMU_POLY_VERTEX)
        .value("LINE", xms::XmUGridCellType::XMU_LINE)
        .value("POLY_LINE", xms::XmUGridCellType::XMU_POLY_LINE)
        .value("TRIANGLE", xms::XmUGridCellType::XMU_TRIANGLE)
        .value("TRIANGLE_STRIP", xms::XmUGridCellType::XMU_TRIANGLE_STRIP)
        .value("POLYGON", xms::XmUGridCellType::XMU_POLYGON)
        .value("PIXEL", xms::XmUGridCellType::XMU_PIXEL)
        .value("QUAD", xms::XmUGridCellType::XMU_QUAD)
        .value("TETRA", xms::XmUGridCellType::XMU_TETRA)
        .value("VOXEL", xms::XmUGridCellType::XMU_VOXEL)
        .value("HEXAHEDRON", xms::XmUGridCellType::XMU_HEXAHEDRON)
        .value("WEDGE", xms::XmUGridCellType::XMU_WEDGE)
        .value("PYRAMID", xms::XmUGridCellType::XMU_PYRAMID)
        .value("PENTAGONAL_PRISM",
            xms::XmUGridCellType::XMU_PENTAGONAL_PRISM)
        .value("HEXAGONAL_PRISM", xms::XmUGridCellType::XMU_HEXAGONAL_PRISM)
        .value("QUADRATIC_EDGE", xms::XmUGridCellType::XMU_QUADRATIC_EDGE)
        .value("QUADRATIC_TRIANGLE",
            xms::XmUGridCellType::XMU_QUADRATIC_TRIANGLE)
        .value("QUADRATIC_QUAD", xms::XmUGridCellType::XMU_QUADRATIC_QUAD)
        .value("QUADRATIC_POLYGON",
            xms::XmUGridCellType::XMU_QUADRATIC_POLYGON)
        .value("QUADRATIC_TETRA", xms::XmUGridCellType::XMU_QUADRATIC_TETRA)
        .value("QUADRATIC_HEXAHEDRON",
            xms::XmUGridCellType::XMU_QUADRATIC_HEXAHEDRON)
        .value("QUADRATIC_WEDGE", xms::XmUGridCellType::XMU_QUADRATIC_WEDGE)
        .value("QUADRATIC_PYRAMID",
            xms::XmUGridCellType::XMU_QUADRATIC_PYRAMID)
        .value("BIQUADRATIC_QUAD",
            xms::XmUGridCellType::XMU_BIQUADRATIC_QUAD)
        .value("TRIQUADRATIC_HEXAHEDRON",
            xms::XmUGridCellType::XMU_TRIQUADRATIC_HEXAHEDRON)
        .value("QUADRATIC_LINEAR_QUAD",
            xms::XmUGridCellType::XMU_QUADRATIC_LINEAR_QUAD)
        .value("QUADRATIC_LINEAR_WEDGE",
            xms::XmUGridCellType::XMU_QUADRATIC_LINEAR_WEDGE)
        .value("BIQUADRATIC_QUADRATIC_WEDGE",
            xms::XmUGridCellType::XMU_BIQUADRATIC_QUADRATIC_WEDGE)
        .value("BIQUADRATIC_QUADRATIC_HEXAHEDRON",
            xms::XmUGridCellType::XMU_BIQUADRATIC_QUADRATIC_HEXAHEDRON)
        .value("BIQUADRATIC_TRIANGLE",
            xms::XmUGridCellType::XMU_BIQUADRATIC_TRIANGLE)
        .value("CUBIC_LINE", xms::XmUGridCellType::XMU_CUBIC_LINE)
        .value("CONVEX_POINT_SET",
            xms::XmUGridCellType::XMU_CONVEX_POINT_SET)
        .value("POLYHEDRON", xms::XmUGridCellType::XMU_POLYHEDRON)
        .value("PARAMETRIC_CURVE",
            xms::XmUGridCellType::XMU_PARAMETRIC_CURVE)
        .value("PARAMETRIC_SURFACE",
            xms::XmUGridCellType::XMU_PARAMETRIC_SURFACE)
        .value("PARAMETRIC_TRI_SURFACE",
            xms::XmUGridCellType::XMU_PARAMETRIC_TRI_SURFACE)
        .value("PARAMETRIC_QUAD_SURFACE",
            xms::XmUGridCellType::XMU_PARAMETRIC_QUAD_SURFACE)
        .value("PARAMETRIC_TETRA_REGION",
            xms::XmUGridCellType::XMU_PARAMETRIC_TETRA_REGION)
        .value("PARAMETRIC_HEX_REGION",
            xms::XmUGridCellType::XMU_PARAMETRIC_HEX_REGION)
        .value("HIGHER_ORDER_EDGE",
            xms::XmUGridCellType::XMU_HIGHER_ORDER_EDGE)
        .value("HIGHER_ORDER_TRIANGLE",
            xms::XmUGridCellType::XMU_HIGHER_ORDER_TRIANGLE)
        .value("HIGHER_ORDER_QUAD",
            xms::XmUGridCellType::XMU_HIGHER_ORDER_QUAD)
        .value("HIGHER_ORDER_POLYGON",
            xms::XmUGridCellType::XMU_HIGHER_ORDER_POLYGON)
        .value("HIGHER_ORDER_TETRAHEDRON",
            xms::XmUGridCellType::XMU_HIGHER_ORDER_TETRAHEDRON)
        .value("HIGHER_ORDER_WEDGE",
            xms::XmUGridCellType::XMU_HIGHER_ORDER_WEDGE)
        .value("HIGHER_ORDER_PYRAMID",
            xms::XmUGridCellType::XMU_HIGHER_ORDER_PYRAMID)
        .value("HIGHER_ORDER_HEXAHEDRON",
            xms::XmUGridCellType::XMU_HIGHER_ORDER_HEXAHEDRON)
        .value("NUMBER_OF_CELL_TYPES",
            xms::XmUGridCellType::XMU_NUMBER_OF_CELL_TYPES)
        .export_values();

    // UGrid FaceOrientation
    py::enum_<xms::XmUGridFaceOrientation>(xmUg, "ugrid_faceorientation_enum",
                            "xmugrid_faceorientation_enum for XmUGrid class")
        .value("ORIENTATION_UNKNOWN",
            xms::XmUGridFaceOrientation::XMU_ORIENTATION_UNKNOWN)
        .value("ORIENTATION_SIDE",
            xms::XmUGridFaceOrientation::XMU_ORIENTATION_SIDE)
        .value("ORIENTATION_TOP",
            xms::XmUGridFaceOrientation::XMU_ORIENTATION_TOP)
        .value("ORIENTATION_BOTTOM",
            xms::XmUGridFaceOrientation::XMU_ORIENTATION_BOTTOM)
        .export_values();
}