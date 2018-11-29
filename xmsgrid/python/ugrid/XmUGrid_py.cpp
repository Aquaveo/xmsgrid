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
    const char* xmUGrid_doc = R"pydoc(
        Class is a grid geometry library.
    )pydoc";
    py::class_<xms::XmUGrid, boost::shared_ptr<xms::XmUGrid>> xmUg(m, "XmUGrid",
                                                                   xmUGrid_doc);


    //Init
    xmUg.def(py::init([]() {
            return boost::shared_ptr<xms::XmUGrid>(xms::XmUGrid::New());
        }));
  // ---------------------------------------------------------------------------
  // function: init
  // ---------------------------------------------------------------------------       
    xmUg.def(py::init([](py::iterable pts, py::iterable cellstream) {
            boost::shared_ptr<xms::VecPt3d> points = 
                xms::VecPt3dFromPyIter(pts);
            boost::shared_ptr<xms::VecInt> _cellstream = 
                xms::VecIntFromPyIter(cellstream);
            return boost::shared_ptr<xms::XmUGrid>(
                xms::XmUGrid::New(*points, *_cellstream));
        }));
  // Misc Functions
  // ---------------------------------------------------------------------------
  // function: get_modified
  // --------------------------------------------------------------------------- 
    const char* get_modified_doc = R"pydoc(
        Determine if the UGrid has been modified.

        Returns:
            bool: The modified flag.
    )pydoc";
    xmUg.def("get_modified", &xms::XmUGrid::GetModified,
             get_modified_doc);
    // ---------------------------------------------------------------------------
    // function: set_unmodified
    // --------------------------------------------------------------------------- 
    const char* set_unmodified_doc = R"pydoc(
        Set the UGrid unmodified.
    )pydoc";
    xmUg.def("set_unmodified", &xms::XmUGrid::SetUnmodified,
             set_unmodified_doc);
    // ---------------------------------------------------------------------------
    // function: set_use_cache
    // --------------------------------------------------------------------------- 
    const char* set_use_cache_doc = R"pydoc(
        Turn on or off use of caching to speed up some operations.

        Args:
            use_cache (bool): Flag to determine if caching will be used.
    )pydoc";
    xmUg.def("set_use_cache", &xms::XmUGrid::SetUseCache,
             set_use_cache_doc);
  // Point Functions
  // ---------------------------------------------------------------------------
  // function: get_point_count
  // ---------------------------------------------------------------------------        
    const char* point_count_doc = R"pydoc(
        Get the number of points.

        Returns:
            int: The number of points.
    )pydoc";
    xmUg.def("get_point_count", &xms::XmUGrid::GetPointCount,
             point_count_doc);
  // ---------------------------------------------------------------------------
  // function: get_locations
  // ---------------------------------------------------------------------------  
    const char* get_locations_doc = R"pydoc(
        Get vector of UGrid points.

        Returns:
            iterable: Constant reference to vector of points.
    )pydoc";
    xmUg.def("get_locations", [](xms::XmUGrid &self) -> py::iterable {
            return xms::PyIterFromVecPt3d(self.GetLocations());
        }, get_locations_doc);
  // ---------------------------------------------------------------------------
  // function: set_locations
  // ---------------------------------------------------------------------------
    const char* set_locations_doc = R"pydoc(
        Set UGrid points.

        Args:
            locations (iterable): Vector of point locations.
    )pydoc";
    xmUg.def("set_locations", [](xms::XmUGrid &self, py::iterable locations) {
            boost::shared_ptr<xms::VecPt3d> locs = xms::VecPt3dFromPyIter(
                locations);
            self.SetLocations(*locs);
        }, set_locations_doc,py::arg("locations"));
  // ---------------------------------------------------------------------------
  // function: get_point_location
  // ---------------------------------------------------------------------------
    const char* get_point_location_doc = R"pydoc(
        Get the point.

        Args:
            point_idx (int): The index of the point.
        Returns:
            iterable: The point or an initialize point if the index is invalid.
    )pydoc";
    xmUg.def("get_point_location", [](xms::XmUGrid &self, int point_idx) -> 
    py::iterable {
            return xms::PyIterFromPt3d(self.GetPointLocation(point_idx));
        }, get_point_location_doc,py::arg("point_idx"));
  // ---------------------------------------------------------------------------
  // function: set_point_location
  // ---------------------------------------------------------------------------
    const char* set_point_location_doc = R"pydoc(
        Set the point.

        Args:
            point_idx (int): The index of the point.

            location (iterable): The new location of the specified point.
        Returns:
            bool: Whether the point was successfully set.
    )pydoc";
    xmUg.def("set_point_location", [](xms::XmUGrid &self, int point_idx, py::iterable location) -> bool {
            xms::Pt3d loc = xms::Pt3dFromPyIter(location);
            return self.SetPointLocation(point_idx, loc);
        }, set_point_location_doc,py::arg("point_idx"),py::arg("location"));
  // ---------------------------------------------------------------------------
  // function: get_point_xy0
  // ---------------------------------------------------------------------------
    const char* get_point_xy0_doc = R"pydoc(
        Get the X, Y location of a point.

        Args:
            point_idx (int): The index of the point.
        Returns:
            iterable: The location of the point with Z set to 0.0.
    )pydoc";
    xmUg.def("get_point_xy0", [](xms::XmUGrid &self, int point_idx) 
        -> py::iterable {
      return xms::PyIterFromPt3d(self.GetPointXy0(point_idx));
    }, get_point_xy0_doc, py::arg("point_idx"));
  // ---------------------------------------------------------------------------
  // function: get_points_locations
  // ---------------------------------------------------------------------------
    const char* get_points_locations_doc = R"pydoc(
        Convert a vector of point indices into a vector of point 3d.

        Args:
            point_idxs (iterable): A vector of point indices.

        Returns:
            iterable: Vector of point 3d.
    )pydoc";
    xmUg.def("get_points_locations", [](xms::XmUGrid &self, 
    py::iterable point_idxs) -> py::iterable {
            boost::shared_ptr<xms::VecInt> point_indices = 
            xms::VecIntFromPyIter(point_idxs);
            xms::VecPt3d locations = self.GetPointsLocations(*point_indices);
            return xms::PyIterFromVecPt3d(locations);
        }, get_points_locations_doc,py::arg("point_idxs"));
  // ---------------------------------------------------------------------------
  // function: get_extents
  // ---------------------------------------------------------------------------
    const char* get_extents_doc = R"pydoc(
        Get extents of all points in UGrid.

        Returns:
            iterable: Contains the minimum extent of all points and maximum extent of all points.
    )pydoc";
    xmUg.def("get_extents", [](xms::XmUGrid &self) -> py::iterable {
            xms::Pt3d p_min, p_max;
            self.GetExtents(p_min, p_max);
            return py::make_tuple(xms::PyIterFromPt3d(p_min), 
                xms::PyIterFromPt3d(p_max));
        }, get_extents_doc);
  // ---------------------------------------------------------------------------
  // function: get_point_adjacent_cells
  // ---------------------------------------------------------------------------
    const char* get_point_adjacent_cells_doc = R"pydoc(
        Get the cells that are associated with the specified point.

        Args:
            point_idx (int): The index of the point. 
        Returns:
            iterable: A vector of the cell indices associated with this point.
    )pydoc";
    xmUg.def("get_point_adjacent_cells", [](xms::XmUGrid &self, int point_idx) 
        -> py::iterable {
            return xms::PyIterFromVecInt(self.GetPointAdjacentCells(point_idx));
        }, get_point_adjacent_cells_doc,py::arg("point_idx"));
  // ---------------------------------------------------------------------------
  // function: get_points_adjacent_cells
  // ---------------------------------------------------------------------------
    const char* get_points_adjacent_cells_doc = R"pydoc(
        Gets the common cells from a vector of points.

        Args:
            point_idxs (iterable): A vector of unique points.
        Returns:
            iterable: A vector of cell indices.
    )pydoc";
    xmUg.def("get_points_adjacent_cells", [](xms::XmUGrid &self, 
                                            py::iterable point_idxs) 
        -> py::iterable {
            boost::shared_ptr<xms::VecInt> points = xms::VecIntFromPyIter(
                point_idxs);
            return xms::PyIterFromVecInt(self.GetPointsAdjacentCells(*points));
        }, get_points_adjacent_cells_doc,py::arg("point_idxs"));

    // ---------------------------------------------------------------------------
    // function: is_valid_point_change
    // ---------------------------------------------------------------------------
      const char* is_valid_point_change_doc = R"pydoc(
          Determine if adjacent cells would be valid upon changing a point.

          Args:
              point_idx (int): The index of the point.
              new_location (iterable): The proposed new location of the point.
          Returns:
              bool: Whether the change would be valid.
      )pydoc";
      xmUg.def("is_valid_point_change", [](xms::XmUGrid &self, int point_idx,
                                           py::iterable new_location) -> bool {
        xms::Pt3d location = xms::Pt3dFromPyIter(new_location);
        return self.IsValidPointChange(point_idx, location);
      }, is_valid_point_change_doc, py::arg("point_idx"), py::arg("new_location"));
        // Cell Functions
  // ---------------------------------------------------------------------------
  // function: get_cell_count
  // ---------------------------------------------------------------------------
    const char* get_cell_count_doc = R"pydoc(
        Get the number of cells.

        Returns:
            int: The number of cells.
    )pydoc";
    xmUg.def("get_cell_count", &xms::XmUGrid::GetCellCount,
             get_cell_count_doc);
  // ---------------------------------------------------------------------------
  // function: get_cell_points
  // ---------------------------------------------------------------------------
    const char* get_cell_points_doc = R"pydoc(
        Get the points of a cell (including polyhedron).

        Args:
            cell_idx (int): The index of the cell.

        Returns:
            iterable: A vector of point indices.
    )pydoc";
    xmUg.def("get_cell_points", [](xms::XmUGrid &self, int cell_idx) 
        -> py::iterable {
            return xms::PyIterFromVecInt(self.GetCellPoints(cell_idx));
        }, get_cell_points_doc,py::arg("cell_idx"));
// -----------------------------------------------------------------------------
// function: get_cell_locations
// -----------------------------------------------------------------------------
    const char* get_cell_locations_doc = R"pydoc(
        Get the locations of the points of a specified cell.

        Args:
            cell_idx (int): The index of the specified cell.

        Returns:
            iterable: The locations of the points associated with the cell.
    )pydoc";
    xmUg.def("get_cell_locations", [](xms::XmUGrid &self, int cell_idx) ->
     py::iterable {
      xms::VecPt3d locations;
      self.GetCellLocations(cell_idx, locations);
      return xms::PyIterFromVecPt3d(locations);
    }, get_cell_locations_doc, py::arg("cell_idx"));
  // ---------------------------------------------------------------------------
  // function: get_cell_type
  // ---------------------------------------------------------------------------
    const char* get_cell_type_doc = R"pydoc(
        Get the cell type of a specified cell.

        Args:
            cell_idx (int): The index of the specified cell.

        Returns:
            xmugrid_celltype_enum: The type of the specified cell.
    )pydoc";
    xmUg.def("get_cell_type", &xms::XmUGrid::GetCellType, get_cell_type_doc,
        py::arg("cell_idx"));
  // ---------------------------------------------------------------------------
  // function: get_dimension_counts
  // ---------------------------------------------------------------------------
    const char* get_dimension_counts_doc = R"pydoc(
        Count all number of the cells with each dimenion (0, 1, 2, 3).

        Returns:
            iterable: The count of dimensions of all of the cells of the ugrid.
    )pydoc";
    xmUg.def("get_dimension_counts", [](xms::XmUGrid &self) -> py::iterable {
            return xms::PyIterFromVecInt(self.GetDimensionCounts());
        }, get_dimension_counts_doc);
  // ---------------------------------------------------------------------------
  // function: get_cell_dimension
  // ---------------------------------------------------------------------------
    const char* get_cell_dimension_doc = R"pydoc(
        Get the dimension of the specified cell.

        Args:
            cell_idx (int): The index of the cell.

        Returns:
            int: The dimension of the cells or -1 if invalid index or invalid dimension.
    )pydoc";
    xmUg.def("get_cell_dimension", &xms::XmUGrid::GetCellDimension,
             get_cell_dimension_doc,py::arg("cell_idx")
        );
  // ---------------------------------------------------------------------------
  // function: get_cell_extents
  // ---------------------------------------------------------------------------
    const char* get_cell_extents_doc = R"pydoc(
        Get the extents of the given cell.

        Args:
            cell_idx (int): The cell index to get the extents of.

        Returns:
            iterable: A tuple of the minimum and maximum locations.
    )pydoc";
    xmUg.def("get_cell_extents", [](xms::XmUGrid &self, int cell_idx) -> 
    py::iterable {
        xms::VecPt3d extents(2);
        self.GetCellExtents(cell_idx, extents[0], extents[1]);
        return xms::PyIterFromVecPt3d(extents);
    }, get_cell_extents_doc,py::arg("cell_idx"));
  // ---------------------------------------------------------------------------
  // function: get_cellstream
  // ---------------------------------------------------------------------------
    const char* get_cellstream_doc = R"pydoc(
        Get cell stream vector for the entire UGrid.

        Returns:
            iterable: Constant reference to the cell stream vector.
    )pydoc";
    xmUg.def("get_cellstream", [](xms::XmUGrid &self) -> py::iterable {
            return xms::PyIterFromVecInt(self.GetCellStream());
        }, get_cellstream_doc);
  // ---------------------------------------------------------------------------
  // function: set_cellstream
  // ---------------------------------------------------------------------------
    const char* set_cellstream_doc = R"pydoc(
        Set the ugrid cells for the entire UGrid using a cell stream. The cells
        are defined into two groups. First hexahedrons, polygons, quads, 
        triangles contain the cell type (ElemTypeEnum), number of points, and 
        point numbers. They are generally 0-based, CCW, bottom, then top. Not 
        true for pixel or voxel. Second polyhedrons contain the cell type, 
        number of faces, [num points in face, point numbers (0-based, CCW when 
        looking in)] repeated for each face.

        Args:
            cellstream (iterable): A stream of cells.

        Returns:
            bool: If successfully set.
    )pydoc";
    xmUg.def("set_cellstream", [](xms::XmUGrid &self, py::iterable cellstream) 
    -> bool {
            boost::shared_ptr<xms::VecInt> _cellstream = 
            xms::VecIntFromPyIter(cellstream);
            return self.SetCellstream(*_cellstream);
        },set_cellstream_doc,py::arg("cellstream"));
  // ---------------------------------------------------------------------------
  // function: get_cell_cellstream
  // ---------------------------------------------------------------------------
    const char* get_cell_cellstream_doc = R"pydoc(
        Get cell stream vector for a single cell.

        Args:
            cell_idx (int): The index of the cell.
        Returns:
            iterable: Contains whether it was successfull or not and the cellstream for the specified point..
    )pydoc";
    xmUg.def("get_cell_cellstream", [](xms::XmUGrid &self, int cell_idx) ->
     py::iterable {
            xms::VecInt cellstream;
            bool ret_val = self.GetCellCellstream(cell_idx, cellstream);
            return py::make_tuple(ret_val, xms::PyIterFromVecInt(cellstream));
        }, get_cell_cellstream_doc,py::arg("cell_idx"));
  // ---------------------------------------------------------------------------
  // function: get_cell_adjacent_cells
  // ---------------------------------------------------------------------------
    const char* get_cell_adjacent_cells_doc = R"pydoc(
        Get the cells neighboring a cell (cells associated with any of it's 
        points).

        Args:
            cell_idx (int): The index of the cell.

        Returns:
            iterable: Vector of cell indices.
    )pydoc";
    xmUg.def("get_cell_adjacent_cells", [](xms::XmUGrid &self, int cell_idx) ->
     py::iterable {
            return xms::PyIterFromVecInt(self.GetCellAdjacentCells(cell_idx));
        }, get_cell_adjacent_cells_doc,py::arg("cell_idx"));
  // ---------------------------------------------------------------------------
  // function: get_cell_plan_view_polygon
  // ---------------------------------------------------------------------------
    const char* get_cell_plan_view_polygon_doc = R"pydoc(
        Get a plan view polygon of a specified cell.

        Args:
            cell_idx (int): The index of the cell.

        Returns:
            iterable: Contains a bool that is false if the cell index does not exist or if the cell is not 2 or 3 dimensional and a vector of Pt3d that is the plan view polygon.
    )pydoc";
    xmUg.def("get_cell_plan_view_polygon", [](xms::XmUGrid &self, int cell_idx) 
    -> py::iterable {
            xms::VecPt3d polygon;
            bool ret_val = self.GetCellPlanViewPolygon(cell_idx, polygon);
            return py::make_tuple(ret_val, xms::PyIterFromVecPt3d(polygon));
        }, get_cell_plan_view_polygon_doc,py::arg("cell_idx"));
  // ---------------------------------------------------------------------------
  // function: get_cell_centroid
  // ---------------------------------------------------------------------------
    const char* get_cell_centroid_doc = R"pydoc(
        Get the centroid location of a cell.

        Args:
            cell_idx (int): The index of the cell.

        Returns:
            iterable: Contains a bool that is false if the cell index does not exist and the location of the cell centroid.
    )pydoc";
    xmUg.def("get_cell_centroid", [](xms::XmUGrid &self, int cell_idx) 
    -> py::iterable {
        xms::Pt3d centroid;
        bool ret_val = self.GetCellCentroid(cell_idx, centroid);
        return py::make_tuple(ret_val, xms::PyIterFromPt3d(centroid));
    }, get_cell_centroid_doc, py::arg("cell_idx"));


      // Edges Functions
  // ---------------------------------------------------------------------------
  // function: get_cell_edge_count
  // ---------------------------------------------------------------------------
    const char* get_cell_edge_count_doc = R"pydoc(
        Get the number of edges for a cell.

        Args:
            cell_idx (int): The index of the cell.

        Returns:
            int: The count of cell edges.
    )pydoc";
    xmUg.def("get_cell_edge_count", &xms::XmUGrid::GetCellEdgeCount,
             get_cell_edge_count_doc, py::arg("cell_idx")
		);
  // ---------------------------------------------------------------------------
  // function: get_cell_edge
  // ---------------------------------------------------------------------------
    const char* get_cell_edge_doc = R"pydoc(
        Get the points of a cell.

        Args:
            cell_idx (int): The index of the cell.

            edge_idx (int): The index of the edge.

        Returns:
            iterable: A standard pair of point indices (which is an edge).
    )pydoc";
    xmUg.def("get_cell_edge", [](xms::XmUGrid &self, int cell_idx, int edge_idx) 
    -> py::iterable {
            xms::XmEdge edge = self.GetCellEdge(cell_idx, edge_idx);
            return py::make_tuple(edge.GetFirst(), edge.GetSecond());
        }, get_cell_edge_doc,py::arg("cell_idx"),py::arg("edge_idx"));
  // ---------------------------------------------------------------------------
  // function: get_cell_edge_adjacent_cells
  // ---------------------------------------------------------------------------
    const char* get_cell_edge_adjacent_cells_doc = R"pydoc(
        Get the index of the adjacent cells (that share the same cell edge).

        Args:
            cell_idx (int): The index of the cell.

            edge_idx (int): The index of the edge.

        Returns:
            iterable: A vector of cell indices of the adjacent cells.
    )pydoc";
    xmUg.def("get_cell_edge_adjacent_cells", [](xms::XmUGrid &self, int cell_idx
    , int edge_idx) -> py::iterable {
            return xms::PyIterFromVecInt(self.GetCellEdgeAdjacentCells(cell_idx,
             edge_idx));
        }, get_cell_edge_adjacent_cells_doc,py::arg("cell_idx"),
        py::arg("edge_idx"));
  // ---------------------------------------------------------------------------
  // function: get_cell2d_edge_adjacent_cell
  // ---------------------------------------------------------------------------
    const char* get_cell2d_edge_adjacent_cell_doc = R"pydoc(
        Get the index of the adjacent cells (that share the same cell edge).

        Args:
            cell_idx (int): The index of the cell.

            edge_idx (int): The index of the edge.

        Returns:
            int: The index of the adjacent cell (or -1 if none).
    )pydoc";
    xmUg.def("get_cell2d_edge_adjacent_cell", 
    &xms::XmUGrid::GetCell2dEdgeAdjacentCell,
             get_cell2d_edge_adjacent_cell_doc,py::arg("cell_idx"),
             py::arg("edge_idx"));
  // ---------------------------------------------------------------------------
  // function: get_edge_adjacent_cells
  // ---------------------------------------------------------------------------
    const char* get_edge_adjacent_cells_doc = R"pydoc(
        Get the indices of the adjacent cells (that share the same cell edge).

        Args:
            edge (iterable): The edge (a pair of point indices).

        Returns:
            iterable: A vector of cell indices of the adjacent cells.
    )pydoc";
    xmUg.def("get_edge_adjacent_cells", [](xms::XmUGrid &self, py::iterable edge
    ) -> py::iterable {
            xms::XmEdge a_edge = XmEdgeFromPyIter(edge);
            //std::pair<int, int> a_edge = xms::IntPairFromPyIter(edge);
            return xms::PyIterFromVecInt(self.GetEdgeAdjacentCells(a_edge));
        }, get_edge_adjacent_cells_doc,py::arg("edge"));
  // ---------------------------------------------------------------------------
  // function: get_cell_edges
  // ---------------------------------------------------------------------------
    const char* get_cell_edges_doc = R"pydoc(
        Get the Edges of a cell.

        Args:
            cell_idx (int): The cells to whom the edges belong.

        Returns:
            iterable: A vector of edges.
    )pydoc";
    xmUg.def("get_cell_edges", [](xms::XmUGrid &self, int cell_idx) 
    -> py::iterable {
            std::vector<xms::XmEdge> edges = self.GetCellEdges(cell_idx);
            return PyIterFromVecXmEdge(edges);
        }, get_cell_edges_doc,py::arg("cell_idx"));
  // ---------------------------------------------------------------------------
  // function: get_point_adjacent_points
  // ---------------------------------------------------------------------------
    const char* get_point_adjacent_points_doc = R"pydoc(
        Given a point gets point indices attached to the point by an edge.

        Args:
            point_idx (int): The point to get adjacent points from.

        Returns:
            iterable: The indices of the adjacent points.
    )pydoc";
    xmUg.def("get_point_adjacent_points", [](xms::XmUGrid &self, int point_idx) 
    -> py::iterable {
      xms::VecInt adj_idxs;
      self.GetPointAdjacentPoints(point_idx, adj_idxs);
      return xms::PyIterFromVecInt(adj_idxs);
    }, get_point_adjacent_points_doc, py::arg("point_idx"));
  // ---------------------------------------------------------------------------
  // function: get_point_adjacent_locations
  // ---------------------------------------------------------------------------
    const char* get_point_adjacent_locations_doc = R"pydoc(
        Given a point gets point locations attached to the point by an edge.

        Args:
            point_idx (int): The point to get attached point from.

        Returns:
            iterable: A vector of points attached across edges.
    )pydoc";
    xmUg.def("get_point_adjacent_locations", [](xms::XmUGrid &self, int 
    point_idx) -> py::iterable {
      xms::VecPt3d adj_points;
      self.GetPointAdjacentLocations(point_idx, adj_points);
      return xms::PyIterFromVecPt3d(adj_points);
    }, get_point_adjacent_locations_doc, py::arg("point_idx"));

        // Face Functions
  // ---------------------------------------------------------------------------
  // function: get_cell3d_face_count
  // ---------------------------------------------------------------------------
    const char* get_cell3d_face_count_doc = R"pydoc(
        Get the number of cell faces for given cell.

        Args:
            cell_idx (int): The index of the cell.

        Returns:
            int: The count of cell faces.
    )pydoc";
    xmUg.def("get_cell3d_face_count", &xms::XmUGrid::GetCell3dFaceCount,
             get_cell3d_face_count_doc,py::arg("cell_idx"));
  // ---------------------------------------------------------------------------
  // function: get_cell3d_face_point_count
  // ---------------------------------------------------------------------------
    const char* get_cell3d_face_point_count_doc = R"pydoc(
        Get the number of face points for a given cell and face.

        Args:
            cell_idx (int): The cell.

            face_idx (int): The face.

        Returns:
            int: The number of face points or -1 if invalid face or cell index.
    )pydoc";
    xmUg.def("get_cell3d_face_point_count", 
    &xms::XmUGrid::GetCell3dFacePointCount,
             get_cell3d_face_point_count_doc, py::arg("cell_idx"), py::arg(
                 "face_idx"));
  // ---------------------------------------------------------------------------
  // function: get_cell3d_face_points
  // ---------------------------------------------------------------------------
    const char* get_cell3d_face_points_doc = R"pydoc(
        Get the cell face for given cell and face index.

        Args:
            cell_idx (int): The index of the cell.

            face_idx (int): The face index of the cell.

        Returns:
            iterable: A vector of point indices for the face index of the cell.
    )pydoc";
    xmUg.def("get_cell3d_face_points", [](xms::XmUGrid &self, int cell_idx, int 
    face_idx) -> py::iterable {
            return xms::PyIterFromVecInt(self.GetCell3dFacePoints(cell_idx, 
            face_idx));
        }, get_cell3d_face_points_doc,py::arg("cell_idx"),py::arg("face_idx"));
  // ---------------------------------------------------------------------------
  // function: get_cell3d_faces_points
  // ---------------------------------------------------------------------------
    const char* get_cell3d_faces_points_doc = R"pydoc(
        Get the faces of a cell.

        Args:
            cell_idx (int): The cells to whom the faces belong.

        Returns:
            iterable: A vector of faces, which is a vector of point indices.
    )pydoc";
    xmUg.def("get_cell3d_faces_points", [](xms::XmUGrid &self, int cell_idx) 
    -> py::iterable {
            return xms::PyIterFromVecInt2d(self.GetCell3dFacesPoints(cell_idx));
        }, get_cell3d_faces_points_doc,py::arg("cell_idx"));
  // ---------------------------------------------------------------------------
  // function: get_cell3d_face_adjacent_cell
  // ---------------------------------------------------------------------------
    const char* get_cell3d_face_adjacent_cell_doc = R"pydoc(
        Get the cell face neighbors for given cell and face index.

        Args:
            cell_idx (int): The index of the cell.
            
            face_idx (int): The face index of the cell.

        Returns:
            int: A cell index of the neighbor.
    )pydoc";
    xmUg.def("get_cell3d_face_adjacent_cell", [](xms::XmUGrid &self, int 
    cell_idx, int face_idx) -> int {
            return self.GetCell3dFaceAdjacentCell(cell_idx, face_idx);
        }, get_cell3d_face_adjacent_cell_doc,py::arg("cell_idx"),py::arg(
            "face_idx"));
    // ---------------------------------------------------------------------------
    // function: get_cell3d_face_orientation
    // ---------------------------------------------------------------------------
    const char* get_cell3d_face_orientation_doc = R"pydoc(
        Get the orientation of the face of a vertically prismatic cell.

        Args:
            cell_idx (int): The index of the cell.

            face_idx (int): The face index of the cell.

        Returns:
            xmugrid_face_orientation_enum: The orientation of the face.
    )pydoc";
    xmUg.def("get_cell3d_face_orientation", &xms::XmUGrid::GetCell3dFaceOrientation,
             get_cell3d_face_orientation_doc, py::arg("cell_idx"), py::arg("face_idx"));

    // UGrid CellType
    py::enum_<xms::XmUGridCellType>(xmUg, "xmugrid_celltype_enum",
                                    "ugrid_celltype_enum for XmUGrid class")
        .value("XMU_INVALID_CELL_TYPE", 
            xms::XmUGridCellType::XMU_INVALID_CELL_TYPE)
        .value("XMU_EMPTY_CELL", xms::XmUGridCellType::XMU_EMPTY_CELL)
        .value("XMU_VERTEX", xms::XmUGridCellType::XMU_VERTEX)
        .value("XMU_POLY_VERTEX", xms::XmUGridCellType::XMU_POLY_VERTEX)
        .value("XMU_LINE", xms::XmUGridCellType::XMU_LINE)
        .value("XMU_POLY_LINE", xms::XmUGridCellType::XMU_POLY_LINE)
        .value("XMU_TRIANGLE", xms::XmUGridCellType::XMU_TRIANGLE)
        .value("XMU_TRIANGLE_STRIP", xms::XmUGridCellType::XMU_TRIANGLE_STRIP)
        .value("XMU_POLYGON", xms::XmUGridCellType::XMU_POLYGON)
        .value("XMU_PIXEL", xms::XmUGridCellType::XMU_PIXEL)
        .value("XMU_QUAD", xms::XmUGridCellType::XMU_QUAD)
        .value("XMU_TETRA", xms::XmUGridCellType::XMU_TETRA)
        .value("XMU_VOXEL", xms::XmUGridCellType::XMU_VOXEL)
        .value("XMU_HEXAHEDRON", xms::XmUGridCellType::XMU_HEXAHEDRON)
        .value("XMU_WEDGE", xms::XmUGridCellType::XMU_WEDGE)
        .value("XMU_PYRAMID", xms::XmUGridCellType::XMU_PYRAMID)
        .value("XMU_PENTAGONAL_PRISM", 
            xms::XmUGridCellType::XMU_PENTAGONAL_PRISM)
        .value("XMU_HEXAGONAL_PRISM", xms::XmUGridCellType::XMU_HEXAGONAL_PRISM)
        .value("XMU_QUADRATIC_EDGE", xms::XmUGridCellType::XMU_QUADRATIC_EDGE)
        .value("XMU_QUADRATIC_TRIANGLE", 
            xms::XmUGridCellType::XMU_QUADRATIC_TRIANGLE)
        .value("XMU_QUADRATIC_QUAD", xms::XmUGridCellType::XMU_QUADRATIC_QUAD)
        .value("XMU_QUADRATIC_POLYGON", 
            xms::XmUGridCellType::XMU_QUADRATIC_POLYGON)
        .value("XMU_QUADRATIC_TETRA", xms::XmUGridCellType::XMU_QUADRATIC_TETRA)
        .value("XMU_QUADRATIC_HEXAHEDRON", 
            xms::XmUGridCellType::XMU_QUADRATIC_HEXAHEDRON)
        .value("XMU_QUADRATIC_WEDGE", xms::XmUGridCellType::XMU_QUADRATIC_WEDGE)
        .value("XMU_QUADRATIC_PYRAMID", 
            xms::XmUGridCellType::XMU_QUADRATIC_PYRAMID)
        .value("XMU_BIQUADRATIC_QUAD", 
            xms::XmUGridCellType::XMU_BIQUADRATIC_QUAD)
        .value("XMU_TRIQUADRATIC_HEXAHEDRON", 
            xms::XmUGridCellType::XMU_TRIQUADRATIC_HEXAHEDRON)
        .value("XMU_QUADRATIC_LINEAR_QUAD", 
            xms::XmUGridCellType::XMU_QUADRATIC_LINEAR_QUAD)
        .value("XMU_QUADRATIC_LINEAR_WEDGE", 
            xms::XmUGridCellType::XMU_QUADRATIC_LINEAR_WEDGE)
        .value("XMU_BIQUADRATIC_QUADRATIC_WEDGE", 
            xms::XmUGridCellType::XMU_BIQUADRATIC_QUADRATIC_WEDGE)
        .value("XMU_BIQUADRATIC_QUADRATIC_HEXAHEDRON", 
            xms::XmUGridCellType::XMU_BIQUADRATIC_QUADRATIC_HEXAHEDRON)
        .value("XMU_BIQUADRATIC_TRIANGLE", 
            xms::XmUGridCellType::XMU_BIQUADRATIC_TRIANGLE)
        .value("XMU_CUBIC_LINE", xms::XmUGridCellType::XMU_CUBIC_LINE)
        .value("XMU_CONVEX_POINT_SET", 
            xms::XmUGridCellType::XMU_CONVEX_POINT_SET)
        .value("XMU_POLYHEDRON", xms::XmUGridCellType::XMU_POLYHEDRON)
        .value("XMU_PARAMETRIC_CURVE", 
            xms::XmUGridCellType::XMU_PARAMETRIC_CURVE)
        .value("XMU_PARAMETRIC_SURFACE", 
            xms::XmUGridCellType::XMU_PARAMETRIC_SURFACE)
        .value("XMU_PARAMETRIC_TRI_SURFACE", 
            xms::XmUGridCellType::XMU_PARAMETRIC_TRI_SURFACE)
        .value("XMU_PARAMETRIC_QUAD_SURFACE", 
            xms::XmUGridCellType::XMU_PARAMETRIC_QUAD_SURFACE)
        .value("XMU_PARAMETRIC_TETRA_REGION", 
            xms::XmUGridCellType::XMU_PARAMETRIC_TETRA_REGION)
        .value("XMU_PARAMETRIC_HEX_REGION", 
            xms::XmUGridCellType::XMU_PARAMETRIC_HEX_REGION)
        .value("XMU_HIGHER_ORDER_EDGE", 
            xms::XmUGridCellType::XMU_HIGHER_ORDER_EDGE)
        .value("XMU_HIGHER_ORDER_TRIANGLE", 
            xms::XmUGridCellType::XMU_HIGHER_ORDER_TRIANGLE)
        .value("XMU_HIGHER_ORDER_QUAD", 
            xms::XmUGridCellType::XMU_HIGHER_ORDER_QUAD)
        .value("XMU_HIGHER_ORDER_POLYGON", 
            xms::XmUGridCellType::XMU_HIGHER_ORDER_POLYGON)
        .value("XMU_HIGHER_ORDER_TETRAHEDRON", 
            xms::XmUGridCellType::XMU_HIGHER_ORDER_TETRAHEDRON)
        .value("XMU_HIGHER_ORDER_WEDGE", 
            xms::XmUGridCellType::XMU_HIGHER_ORDER_WEDGE)
        .value("XMU_HIGHER_ORDER_PYRAMID", 
            xms::XmUGridCellType::XMU_HIGHER_ORDER_PYRAMID)
        .value("XMU_HIGHER_ORDER_HEXAHEDRON", 
            xms::XmUGridCellType::XMU_HIGHER_ORDER_HEXAHEDRON)
        .value("XMU_NUMBER_OF_CELL_TYPES", 
            xms::XmUGridCellType::XMU_NUMBER_OF_CELL_TYPES)
        .export_values();

    // UGrid FaceOrientation
    py::enum_<xms::XmUGridFaceOrientation>(xmUg, "xmugrid_faceorientation_enum",
                            "xmugrid_faceorientation_enum for XmUGrid class")
        .value("XMU_ORIENTATION_UNKNOWN", 
            xms::XmUGridFaceOrientation::XMU_ORIENTATION_UNKNOWN)
        .value("XMU_ORIENTATION_SIDE", 
            xms::XmUGridFaceOrientation::XMU_ORIENTATION_SIDE)
        .value("XMU_ORIENTATION_TOP", 
            xms::XmUGridFaceOrientation::XMU_ORIENTATION_TOP)
        .value("XMU_ORIENTATION_BOTTOM", 
            xms::XmUGridFaceOrientation::XMU_ORIENTATION_BOTTOM)
        .export_values();
}