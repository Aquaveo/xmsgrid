//------------------------------------------------------------------------------
/// \file
/// \ingroup ugrid
/// \copyright (C) Copyright Aquaveo 2018.
//------------------------------------------------------------------------------

//----- Included files ---------------------------------------------------------

// 1. Precompiled header

// 2. My own header
#include <xmsgrid/ugrid/XmUGrid.h>

// 3. Standard library headers
#include <set>

// 4. External library headers

// 5. Shared code headers
#include <xmscore/misc/XmLog.h>

// 6. Non-shared code headers

//----- Forward declarations ---------------------------------------------------

//----- External globals -------------------------------------------------------

//----- Namespace declaration --------------------------------------------------
namespace xms
{
//----- Constants / Enumerations -----------------------------------------------

//----- Classes / Structs ------------------------------------------------------

//----- Internal functions -----------------------------------------------------

//----- Class / Function definitions -------------------------------------------

////////////////////////////////////////////////////////////////////////////////
class XmUGridImpl : public XmUGrid
{
public:
  XmUGridImpl();

  virtual int GetNumberOfPoints() const override;
  virtual int GetNumberOfCells() const override;
  virtual XmUGridCellType GetCellType(int a_cellIdx) const override;
  virtual int GetCellDimension(int a_cellIdx) const override;
  virtual std::vector<int> GetDimensionCount() const override;
  virtual int GetNumberOfCellEdges(const int a_cellIdx) const override;

  virtual const VecPt3d& GetPoints() const override;
  virtual void SetPoints(const VecPt3d& a_points) override;

  virtual bool GetSingleCellStream(const int a_cellIdx, VecInt& a_cellStream) const override;
  virtual const VecInt& GetCellStream() const override;
  virtual bool SetCellStream(const VecInt& a_cellStream) override;

private:
  void UpdateCellLinks();
  static int DimensionFromCellType(const XmUGridCellType a_cellType);
  int GetNumberOfItemsForCell(const int a_cellIdx) const;
  void GetSingleCellStream(const int a_cellIdx, const int** a_start, int &a_length) const;
  int GetNumberOfPolyhedronEdges(const int a_cellIdx) const;

  VecPt3d m_points; ///< UGrid points
  VecInt m_cellStream; ///< UGrid cell stream. For description see SetCellStream
  VecInt m_cellIdxToStreamIdx; ///< Indexes for each cell in the cell stream
};


////////////////////////////////////////////////////////////////////////////////
/// \class XmUGrid
/// \brief Merges two UGrids.
////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
/// \brief
//------------------------------------------------------------------------------
XmUGridImpl::XmUGridImpl()
{
} // XmUGridImpl::XmUGridImpl
//------------------------------------------------------------------------------
/// \brief Get the number of points.
/// \return the number of points
//------------------------------------------------------------------------------
int XmUGridImpl::GetNumberOfPoints() const
{
  return (int)m_points.size();
} // XmUGridImpl::GetNumberOfPoints
//------------------------------------------------------------------------------
/// \brief Get the number of cells.
/// \return the number of cells
//------------------------------------------------------------------------------
int XmUGridImpl::GetNumberOfCells() const
{
  if (m_cellIdxToStreamIdx.empty())
    return 0;
  else
    return (int)m_cellIdxToStreamIdx.size() - 1;
} // XmUGridImpl::GetNumberOfCells
//------------------------------------------------------------------------------
/// \brief Get the number of cells.
/// \return the number of cells or -1 if invalid index
//------------------------------------------------------------------------------
XmUGridCellType XmUGridImpl::GetCellType(int a_cellIdx) const
{
  if (m_cellIdxToStreamIdx.size() < 2 || a_cellIdx > m_cellIdxToStreamIdx.size() - 2)
  {
    return XMU_INVALID_CELL_TYPE;
  }
  else
  {
    int cellStart = m_cellIdxToStreamIdx[a_cellIdx];
    return (XmUGridCellType)m_cellStream[cellStart];
  }
} // XmUGridImpl::GetCellType
//------------------------------------------------------------------------------
/// \brief Get the dimension of the specified cell.
/// \param[in] a_cellIdx: the index of the cell
/// \return the dimension of the cells or -1 if invalid index or invalid dimension
//------------------------------------------------------------------------------
int XmUGridImpl::GetCellDimension(int a_cellIdx) const
{
  return DimensionFromCellType(GetCellType(a_cellIdx));
} // XmUGridImpl::GetCellDimension

//------------------------------------------------------------------------------
/// \brief Count all number of the cells with each dimenion (0, 1, 2, 3)
/// \return the count of dimensions of all of the cells of the ugrid
//------------------------------------------------------------------------------
std::vector<int> XmUGridImpl::GetDimensionCount() const
{
  std::vector<int> m_dimensionCounts(4, 0);
  int itemp(0);
  for (int i(0); i<m_cellIdxToStreamIdx.size()-1; i++)
  {
    itemp = GetCellDimension(i);
    if (itemp >= 0)
    {
      m_dimensionCounts[itemp]++;
    }
  }
  return m_dimensionCounts;
} // XmUGridImpl::GetDimensionCount

//------------------------------------------------------------------------------
/// \brief Get the number of the edges with specified cell
/// \param[in] a_cellIdx: the index of the cell
/// \return the count of cell edges
//------------------------------------------------------------------------------
int XmUGridImpl::GetNumberOfCellEdges(const int a_cellIdx) const
{
  
  int cellType(GetCellType(a_cellIdx));
  switch (cellType)
  {
  // invalid
  case XMU_INVALID_CELL_TYPE:
    return -1;
    break;

  // 0D
  case XMU_EMPTY_CELL:
  case XMU_VERTEX:
  case XMU_POLY_VERTEX:
  case XMU_CONVEX_POINT_SET: // Special class of cells formed by convex group of points
    return 0;
    break;

  // 1D
  case XMU_LINE:
  case XMU_POLY_LINE:

  case XMU_QUADRATIC_EDGE:
  case XMU_PARAMETRIC_CURVE:
  case XMU_HIGHER_ORDER_EDGE:
  case XMU_CUBIC_LINE:  // Cubic, isoparametric cell
    return 0;
    break;

  case XMU_TRIANGLE:
  case XMU_TRIANGLE_STRIP:
  case XMU_QUADRATIC_TRIANGLE:
  case XMU_BIQUADRATIC_TRIANGLE:
  case XMU_HIGHER_ORDER_TRIANGLE:
    return 3;
  break;

  case XMU_PIXEL:
  case XMU_QUAD:
  case XMU_QUADRATIC_QUAD:
  case XMU_BIQUADRATIC_QUAD:
  case XMU_QUADRATIC_LINEAR_QUAD:
  case XMU_HIGHER_ORDER_QUAD:
    return 4;
  break;

  case XMU_POLYGON:
  case XMU_HIGHER_ORDER_POLYGON:
    return GetNumberOfItemsForCell(a_cellIdx)-1;
    break;
  case XMU_QUADRATIC_POLYGON:
    return -1; // Not yet supported
  break;

  case XMU_PARAMETRIC_SURFACE:
  case XMU_PARAMETRIC_TRI_SURFACE:
  case XMU_PARAMETRIC_QUAD_SURFACE:
    return -1; // Not yet supported
  break;
 
  // 3D dimensions
  case XMU_TETRA:
  case XMU_QUADRATIC_TETRA:
  case XMU_HIGHER_ORDER_TETRAHEDRON:
    return 6;
    break;
    
  case XMU_WEDGE:
  case XMU_QUADRATIC_WEDGE:
  case XMU_QUADRATIC_LINEAR_WEDGE:
  case XMU_BIQUADRATIC_QUADRATIC_WEDGE:
  case XMU_HIGHER_ORDER_WEDGE:
    return 9;
    break;

  case XMU_VOXEL:
  case XMU_HEXAHEDRON:
  case XMU_QUADRATIC_HEXAHEDRON:
  case XMU_TRIQUADRATIC_HEXAHEDRON:
  case XMU_BIQUADRATIC_QUADRATIC_HEXAHEDRON:
  case XMU_HIGHER_ORDER_HEXAHEDRON:
    return 12;
    break;

  case XMU_PYRAMID:
  case XMU_QUADRATIC_PYRAMID:
  case XMU_HIGHER_ORDER_PYRAMID:
    return 8;
    break;

  case XMU_PENTAGONAL_PRISM:
    return 15;
    break;
  case XMU_HEXAGONAL_PRISM:
    return 18;
    break;

  case XMU_POLYHEDRON:
    return GetNumberOfPolyhedronEdges(a_cellIdx);
    break;

  case XMU_PARAMETRIC_TETRA_REGION:
  case XMU_PARAMETRIC_HEX_REGION:
    return -1; // Not yet supported
    break;
  }
  return -1;  
} // XmUGridImpl::GetNumberOfCellEdges
//------------------------------------------------------------------------------
/// \brief Get vector of UGrid points.
/// \return constant reference to vector of points
//------------------------------------------------------------------------------
const VecPt3d& XmUGridImpl::GetPoints() const
{
  return m_points;
} // XmUGridImpl::GetPoints
//------------------------------------------------------------------------------
/// \brief Set UGrid points.
/// \param[in] a_points: the points
//------------------------------------------------------------------------------
void XmUGridImpl::SetPoints(const VecPt3d& a_points)
{
  m_points = a_points;
} // XmUGridImpl::SetPoints
//------------------------------------------------------------------------------
/// \brief Get cell stream vector for a single cell.
/// \param[in] a_cellIdx: the index of the cell
/// \param[in] a_cellStream: The cellstream of the cell, see SetCellStream for 
///    more detail on cell stream definitions.
/// \return whether it was successfull or not
//------------------------------------------------------------------------------
bool XmUGridImpl::GetSingleCellStream(const int a_cellIdx, VecInt& a_cellStream) const
{
  a_cellStream.clear();
  if (m_cellIdxToStreamIdx.size() < 2 || a_cellIdx > m_cellIdxToStreamIdx.size() - 2)
  {
    return false;
  }
  int startIndex(m_cellIdxToStreamIdx[a_cellIdx]),
    endIndex(m_cellIdxToStreamIdx[a_cellIdx+1]);
  a_cellStream.assign(m_cellStream.begin()+startIndex, m_cellStream.begin()+endIndex);
  return true;
} // XmUGridImpl::GetSingleCellStream
//------------------------------------------------------------------------------
/// \brief Get cell stream vector.
/// \return constant reference to the cell stream vector
//------------------------------------------------------------------------------
const VecInt& XmUGridImpl::GetCellStream() const
{
  return m_cellStream;
} // XmUGridImpl::GetCellStream
//------------------------------------------------------------------------------
/// \brief Set the ugrid cells using a cell stream.
/// \param[in] a_cellStream: cells defined as follows:
///              Hexahedrons, polygons, quads, triangles etc:
///                Cell type (ElemTypeEnum), number of points, point numbers.
///                Generally 1-based, CCW, bottom, then top. Not true
///                for pixel or voxel.
///              Polyhedrons:
///                Cell type, number of faces, [num points in face,
///                point numbers (1-based, CCW when looking in)] repeated
///                for each face.
//------------------------------------------------------------------------------
bool XmUGridImpl::SetCellStream(const VecInt& a_cellStream)
{
  if (ValidCellStream(a_cellStream))
  {
    m_cellStream = a_cellStream;
    UpdateCellLinks();
    return true;
  }
  else
  {
    XM_LOG(xmlog::error, "Invalid cell stream data.");
    return false;
  }
} // XmUGridImpl::SetCellStream
//------------------------------------------------------------------------------
/// \brief Set the ugrid cells using a cell stream.
//------------------------------------------------------------------------------
void XmUGridImpl::UpdateCellLinks()
{
  m_cellIdxToStreamIdx.clear();

  int currIdx = 0;
  if (m_cellStream.empty())
  {
    m_cellIdxToStreamIdx.push_back(currIdx);
    return;
  }

  int numItems = (int)m_cellStream.size();
  while (currIdx < numItems)
  {
    m_cellIdxToStreamIdx.push_back(currIdx);

    // get cell type
    int cellType = m_cellStream[currIdx++];
    if (currIdx >= numItems)
      return;

    // get the number of items
    int numPoints = m_cellStream[currIdx++];
    if (currIdx >= numItems)
      return;

    if (cellType == XMU_POLYHEDRON)
    {
      int numFaces = numPoints;
      for (int faceIdx = 0; faceIdx < numFaces; ++faceIdx)
      {
        int numPoints = m_cellStream[currIdx++];
        currIdx += numPoints;
      }
    }
    else
    {
      currIdx += numPoints;
    }
  }

  m_cellIdxToStreamIdx.push_back(currIdx);
} // XmUGridImpl::UpdateCellLinks
//------------------------------------------------------------------------------
/// \brief Get the dimension given the cell type (0d, 1d, 2d, or 3d).
/// \param[in] a_cellType: the cell type
/// \return the dimension of the cell type
//------------------------------------------------------------------------------
int XmUGridImpl::DimensionFromCellType(const XmUGridCellType a_cellType)
{
  switch (a_cellType)
  {
  // invalid
  case XMU_INVALID_CELL_TYPE:
    return -1;
    break;

  // 0D
  case XMU_EMPTY_CELL:
  case XMU_VERTEX:
  case XMU_POLY_VERTEX:
  case XMU_CONVEX_POINT_SET: // Special class of cells formed by convex group of points
    return 0;
    break;

  // 1D
  case XMU_LINE:
  case XMU_POLY_LINE:

  case XMU_QUADRATIC_EDGE:
  case XMU_PARAMETRIC_CURVE:
  case XMU_HIGHER_ORDER_EDGE:
  case XMU_CUBIC_LINE:  // Cubic, isoparametric cell
    return 1;
    break;
  // 2D
  case XMU_TRIANGLE:
  case XMU_TRIANGLE_STRIP:
  case XMU_POLYGON:
  case XMU_PIXEL:
  case XMU_QUAD:

  case XMU_QUADRATIC_TRIANGLE:
  case XMU_QUADRATIC_QUAD:
  case XMU_BIQUADRATIC_QUAD:
  case XMU_QUADRATIC_LINEAR_QUAD:
  case XMU_BIQUADRATIC_TRIANGLE:
  case XMU_QUADRATIC_POLYGON:

  case XMU_PARAMETRIC_SURFACE:
  case XMU_PARAMETRIC_TRI_SURFACE:
  case XMU_PARAMETRIC_QUAD_SURFACE:

  case XMU_HIGHER_ORDER_TRIANGLE:
  case XMU_HIGHER_ORDER_QUAD:
  case XMU_HIGHER_ORDER_POLYGON:

    return 2;
    break;

    // assuming the rest are 3D
  default:
    return 3;
    break;
#if 0  // Remaining definitions
    XMU_TETRA = 10,
    XMU_VOXEL = 11,
    XMU_HEXAHEDRON = 12,
    XMU_WEDGE = 13,
    XMU_PYRAMID = 14,
    XMU_PENTAGONAL_PRISM = 15,
    XMU_HEXAGONAL_PRISM = 16,

    // Quadratic, isoparametric cells
    XMU_QUADRATIC_TETRA = 24,
    XMU_QUADRATIC_HEXAHEDRON = 25,
    XMU_QUADRATIC_WEDGE = 26,
    XMU_QUADRATIC_PYRAMID = 27,
    XMU_TRIQUADRATIC_HEXAHEDRON = 29,
    XMU_QUADRATIC_LINEAR_WEDGE = 31,
    XMU_BIQUADRATIC_QUADRATIC_WEDGE = 32,
    XMU_BIQUADRATIC_QUADRATIC_HEXAHEDRON = 33,

    // Polyhedron cell (consisting of polygonal faces)
    XMU_POLYHEDRON = 42,

    // Higher order cells in parametric form
    XMU_PARAMETRIC_TETRA_REGION = 55,
    XMU_PARAMETRIC_HEX_REGION = 56,

    // Higher order cells
    XMU_HIGHER_ORDER_TETRAHEDRON = 64,
    XMU_HIGHER_ORDER_WEDGE = 65,
    XMU_HIGHER_ORDER_PYRAMID = 66,
    XMU_HIGHER_ORDER_HEXAHEDRON = 67,
#endif

  }
  return -1;

} // XmUGridImpl::DimensionFromCellType

//------------------------------------------------------------------------------
/// \brief Get number of items given cell. For polyhedron number of items is
///        number of faces. For other cell types it is number of points.
/// \param[in] a_cellIdx: the cell
/// \return the number of faces for polyhedron or number of points.
//------------------------------------------------------------------------------
int XmUGridImpl::GetNumberOfItemsForCell(const int a_cellIdx) const
{
  int cellType = GetCellType(a_cellIdx);
  if (cellType == XMU_INVALID_CELL_TYPE)
  {
    return 0;
  }
  else if (cellType != XMU_POLYHEDRON)
  {
    // Number of points is right after cell type
    int startIndex = m_cellIdxToStreamIdx[a_cellIdx];
    return m_cellStream[startIndex + 1];
  }
  else
  { // Polyhedron case, same value is number of faces
    int startIndex = m_cellIdxToStreamIdx[a_cellIdx];
    return m_cellStream[startIndex + 1];
  }
}  // XmUGridImpl::GetNumberOfPointsForCell
//------------------------------------------------------------------------------
/// \brief Internal function to get start of cell stream for an individual cell.
///        Returns nullptr and zero length for invalid cellIdx.
/// \param[in] a_cellIdx: the cell
/// \param[out] a_start: pointer to the start of the stream for the cell
/// \param[out] a_length: the length of the stream for the cell
//------------------------------------------------------------------------------
void XmUGridImpl::GetSingleCellStream(const int a_cellIdx, const int** a_start, int &a_length) const
{
  int cellType = GetCellType(a_cellIdx);
  if (cellType == XMU_INVALID_CELL_TYPE)
  {
    *a_start = nullptr;
    a_length = 0;
  }
  else
  {
    int startIndex = m_cellIdxToStreamIdx[a_cellIdx];
    int nextCellIndex = m_cellIdxToStreamIdx[a_cellIdx+1];
    *a_start = &m_cellStream[startIndex];
    a_length = nextCellIndex - startIndex;
  }
} // XmUGridImpl::GetSingleCellStream
//------------------------------------------------------------------------------
/// \brief Get the number of edges for a polyhedron cell.
/// \param[in] a_cellIdx: the cell
/// \return the number of edges
//------------------------------------------------------------------------------
int XmUGridImpl::GetNumberOfPolyhedronEdges(const int a_cellIdx) const
{
  const int* cellStream;
  int streamLength;
  GetSingleCellStream(a_cellIdx, &cellStream, streamLength);
  if (cellStream && streamLength > 0 && cellStream[0] == XMU_POLYHEDRON)
  {
    std::set<std::pair<int, int>> edges;
    int currItem = 2;
    while (currItem < streamLength)
    {
      int numPoints = cellStream[currItem++];
      int firstPointIdx = currItem;
      for (int pointIdx = 0; pointIdx < numPoints; ++pointIdx)
      {
        int pt1Idx = pointIdx;
        int pt2Idx = (pointIdx + 1) % numPoints; 
        // The % operator will reset the index back 0 so the final loop will
        // provide the last and first point
        int pt1 = cellStream[currItem + pt1Idx];
        int pt2 = cellStream[currItem + pt2Idx];
        // We want unique edges, so we add the lower point index first
        if (pt1 < pt2)
          edges.insert(std::pair<int, int>(pt1, pt2));
        else
          edges.insert(std::pair<int, int>(pt2, pt1));
      }
      currItem += numPoints;
    }
    return (int)edges.size();
  }
  return 0;
} // XmUGridImpl::GetNumberOfPolyhedronEdges

////////////////////////////////////////////////////////////////////////////////
/// \class XmUGrid
/// \brief Merges two UGrids.
////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
/// \brief Create a new XmUGrid.
/// \return the new XmUGrid.
//------------------------------------------------------------------------------
BSHP<XmUGrid> XmUGrid::New()
{
  BSHP<XmUGrid> ugrid(new XmUGridImpl());
  return ugrid;
} // XmUGrid::New
//------------------------------------------------------------------------------
/// \brief Create a new XmUGrid.
/// \param[in] a_points: the UGrid points
/// \param[in] a_cellStream: the UGrid cell stream
/// \return the new XmUGrid.
//------------------------------------------------------------------------------
BSHP<XmUGrid> XmUGrid::New(const VecPt3d& a_points, const VecInt& a_cellStream)
{
  BSHP<XmUGrid> ugrid = XmUGrid::New();
  ugrid->SetPoints(a_points);
  ugrid->SetCellStream(a_cellStream);
  return ugrid;
} // XmUGrid::New
//------------------------------------------------------------------------------
/// \brief Constructor
//------------------------------------------------------------------------------
XmUGrid::XmUGrid()
{
} // XmUGrid::XmUGrid
//------------------------------------------------------------------------------
/// \brief Destructor
//------------------------------------------------------------------------------
XmUGrid::~XmUGrid()
{
} // XmUGrid::~XmUGrid
//------------------------------------------------------------------------------
/// \brief Check a cell stream to make sure it's valid. Compares cell type
///        against expected number of points.
/// \param[in] a_cellStream: the cell stream to check
/// \return true if cell stream is valid
//------------------------------------------------------------------------------
bool XmUGrid::ValidCellStream(const VecInt& a_cellStream)
{
  if (a_cellStream.empty())
    return true;

  int numItems = (int)a_cellStream.size();
  int currIdx = 0;
  while (currIdx < numItems)
  {
    // get cell type
    int cellType = a_cellStream[currIdx++];
    if (currIdx >= numItems)
      return false;

    // get the number of points
    int numPoints = a_cellStream[currIdx++];
    if (currIdx >= numItems)
      return false;

    switch (cellType)
    {
    case XMU_EMPTY_CELL:
      if (numPoints != 0)
        return false;
      break;
    case XMU_VERTEX:
      if (numPoints != 1)
        return false;
      currIdx += numPoints;
      break;
    case XMU_LINE:
      if (numPoints != 2)
        return false;
      currIdx += numPoints;
      break;
    case XMU_TRIANGLE:
      if (numPoints != 3)
        return false;
      currIdx += numPoints;
      break;
    case XMU_PIXEL:
    case XMU_QUAD:
    case XMU_TETRA:
      if (numPoints != 4)
        return false;
      currIdx += numPoints;
      break;
    case XMU_PYRAMID:
      if (numPoints != 5)
        return false;
      currIdx += numPoints;
      break;
    case XMU_WEDGE:
    case XMU_PENTAGONAL_PRISM:
      if (numPoints != 6)
        return false;
      currIdx += numPoints;
      break;
    case XMU_HEXAGONAL_PRISM:
      if (numPoints != 7)
        return false;
      currIdx += numPoints;
      break;
    case XMU_VOXEL:
    case XMU_HEXAHEDRON:
      if (numPoints != 8)
        return false;
      currIdx += numPoints;
      break;
    case XMU_POLY_VERTEX:
      if (numPoints < 1)
        return false;
      currIdx += numPoints;
      break;
    case XMU_POLY_LINE:
      if (numPoints < 2)
        return false;
      currIdx += numPoints;
      break;
    case XMU_TRIANGLE_STRIP:
    case XMU_POLYGON:
      if (numPoints < 3)
        return false;
      currIdx += numPoints;
      break;
    case XMU_POLYHEDRON:
    {
      int numFaces = numPoints;
      if (numFaces < 3)
        return false;
      for (int faceIdx = 0; faceIdx < numFaces; ++faceIdx)
      {
        if (currIdx >= numItems)
          return false;
        int numPoints = a_cellStream[currIdx++];
        if (numPoints < 3)
          return false;
        currIdx += numPoints;
      }
    }
      break;
    default:
      currIdx += numPoints;
      break;
    }

    if (currIdx > numItems)
      return false;
  }

  return true;
} // XmUGrid::ValidCellStream

} // namespace xms

#ifdef CXX_TEST
//------------------------------------------------------------------------------
// Unit Tests
//------------------------------------------------------------------------------
using namespace xms;
#include <xmsgrid/ugrid/XmUGrid.t.h>

//------------------------------------------------------------------------------
/// \brief Builds a 1 cell (left 90 degree triangle) 2D XmUGrid for testing.
/// \code
///  2
///  | \ 
///  |  \ 
///  |   \ 
///  0----1
///
/// \endcode
/// \return Returns a builder for the UGrid.
BSHP<XmUGrid> TEST_XmUGrid1Left90Tri()
{
  VecPt3d points = {{0, 0, 0}, {20, 0, 0}, {0, 20, 0}};

  // Cell type (5), number of points (3), point numbers, counterclockwise
  std::vector<int> cells = {5, 3, 0, 1, 2};

  BSHP<XmUGrid> ugrid = XmUGrid::New(points, cells);

  return ugrid;
} // TEST_UGrid1Left90Tri
//------------------------------------------------------------------------------
/// \brief Builds an XmUGrid with supported 1D and 2D linear cells for testing.
/// \return Returns the XmUGrid.
//------------------------------------------------------------------------------
BSHP<XmUGrid> TEST_XmUGrid2dLinear()
{
  VecPt3d points = {
    {0, 0, 0},
    {10, 0, 0},
    {20, 0, 0},
    {30, 0, 0},
    {40, 0, 0},
    {0, 10, 0},
    {10, 10, 0},
    {20, 10, 0},
    {40, 10, 0},
    {0, 20, 0},
    {10, 20, 0},
    {20, 20, 0},
    {30, 20, 0},
    {40, 20, 0}
  };

  // Cell type (5), number of points (3), point numbers, counterclockwise
  std::vector<int> cells = {
    (int)XMU_QUAD, 4, 0, 1, 6, 5,
    (int)XMU_PIXEL, 4, 1, 2, 6, 7,
    (int)XMU_TRIANGLE, 3, 2, 3, 7,
    (int)XMU_POLYGON, 6, 3, 4, 8, 13, 12, 7,
    (int)XMU_POLY_LINE, 3, 7, 11, 10,
    (int)XMU_LINE, 2, 5, 9
  };

  BSHP<XmUGrid> ugrid = XmUGrid::New(points, cells);

  return ugrid;
} // TEST_XmUGrid2dLinear
//------------------------------------------------------------------------------
/// \brief Builds an XmUGrid with supported 1D and 2D linear cells for testing.
/// \return Returns the XmUGrid.
//------------------------------------------------------------------------------
BSHP<XmUGrid> TEST_XmUGrid3dLinear()
{
  VecPt3d points = {
    {0, 0, 0},
    {10, 0, 0},
    {20, 0, 0},
    {30, 0, 0},
    {40, 0, 0},
    {0, 10, 0},
    {10, 10, 0},
    {20, 10, 0},
    {30, 10, 0},
    {40, 10, 0},
    {0, 10, 0},
    {10, 20, 0},
    {20, 20, 0},
    {30, 20, 0},
    {40, 20, 0},
    {0, 0, 10},
    {10, 0, 10},
    {20, 0, 10},
    {30, 0, 10},
    {40, 0, 10},
    {0, 10, 10},
    {10, 10, 10},
    {20, 10, 10},
    {30, 10, 10},
    {40, 10, 10},
    {0, 10, 10},
    {10, 20, 10},
    {20, 20, 10},
    {30, 20, 10},
    {40, 20, 10}
  };

  // Cell type (5), number of points (3), point numbers, counterclockwise
  std::vector<int> cells = {
    (int)XMU_TETRA, 4, 0, 1, 5, 15,
    (int)XMU_VOXEL, 8, 1, 2, 6, 7, 16, 17, 21, 22,
    (int)XMU_HEXAHEDRON, 8, 2, 3, 8, 7, 17, 18, 22, 23,
    (int)XMU_POLYHEDRON, 6,
      4, 8, 9, 14, 13,
      4, 8, 9, 24, 23,
      4, 8, 13, 28, 23,
      4, 13, 14, 29, 28,
      4, 9, 14, 29, 24,
      4, 23, 24, 29, 28,
    (int)XMU_WEDGE, 6, 3, 4, 18, 8, 9, 23,
    (int)XMU_PYRAMID, 5, 5, 6, 11, 10, 20
  };

  BSHP<XmUGrid> ugrid = XmUGrid::New(points, cells);

  return ugrid;
} // TEST_XmUGrid3dLinear
//------------------------------------------------------------------------------
/// \brief Builds a 1 cell hexagon with cell type polyhedron.
/// \return Returns a builder for the UGrid.
//------------------------------------------------------------------------------
BSHP<XmUGrid> TEST_XmUGridHexagonalPolyhedron()
{
  VecPt3d points = {
    {0, 0, 10},
    {10, 0, 10},
    {10, 10, 10},
    {0, 10, 10},
    {0, 0, 0},
    {10, 0, 0},
    {10, 10, 0},
    {0, 10, 0},
  };

  // Cell type (5), number of points (3), point numbers, counterclockwise
  std::vector<int> cells = {(int)XMU_POLYHEDRON, 6,
    4, 0, 1, 2, 3,
    4, 4, 5, 7, 2,
    4, 5, 6, 2, 1,
    4, 6, 7, 3, 2,
    4, 7, 4, 0, 3,
    4, 4, 7, 6, 5
  };

  BSHP<XmUGrid> ugrid = XmUGrid::New(points, cells);

  return ugrid;
} // TEST_XmUGridHexagonalPolyhedron

////////////////////////////////////////////////////////////////////////////////
/// \class XmUGridTests
/// \brief Tests XmUGrids.
////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
/// \brief Test XmUGrid point and cell streams.
//------------------------------------------------------------------------------
void XmUGridTests::testUGridStreams()
{
  // test empty UGrid
  BSHP<XmUGrid> emptyUGrid = XmUGrid::New();
  VecPt3d points = emptyUGrid->GetPoints();
  TS_ASSERT_EQUALS(0, points.size());

  VecInt cellStream = emptyUGrid->GetCellStream();
  TS_ASSERT(XmUGrid::ValidCellStream(cellStream));
  TS_ASSERT_EQUALS(0, cellStream.size());

  // test adding points and cell stream

  /// \code
  ///
  ///     0----1----2
  ///     |    |    |
  ///     3----4----5
  ///     |    |    |
  ///     6----7----8
  /// \endcode
  BSHP<XmUGrid> ugrid = XmUGrid::New();

  points = {{0, 10, 0}, {10, 10, 0}, {20, 10, 0},  {0, 0, 0}, {10, 0, 0},
            {20, 0, 0}, {0, -10, 0}, {10, -10, 0}, {20, -10, 0}};

  // Cell type (9), number of points (4), point numbers, counterclockwise
  cellStream = {
    9, 4, 0, 3, 4, 1,
    9, 4, 1, 4, 5, 2,
    9, 4, 3, 6, 7, 4,
    9, 4, 4, 7, 8, 5};

  ugrid->SetPoints(points);
  VecPt3d pointsOut = ugrid->GetPoints();
  TS_ASSERT_EQUALS(points, pointsOut);

  TS_ASSERT(ugrid->SetCellStream(cellStream));
  VecInt cellStreamOut = ugrid->GetCellStream();
  TS_ASSERT_EQUALS(cellStream, cellStreamOut);

  // Test invalid cell streams
  cellStream = { -1 };
  TS_ASSERT(!XmUGrid::ValidCellStream(cellStream));
  cellStream = { 9, 4, 0, 3, 4 };
  TS_ASSERT(!XmUGrid::ValidCellStream(cellStream));
  cellStream = { 9, 3, 0, 3, 4, 1 };
  TS_ASSERT(!XmUGrid::ValidCellStream(cellStream));
} // XmUGridTests::testUGridStreams
//------------------------------------------------------------------------------
/// \brief Test getting number of points, cells, and cell type.
//------------------------------------------------------------------------------
void XmUGridTests::testGetCellType()
{
  BSHP<XmUGrid> ugrid2d = TEST_XmUGrid2dLinear();
  if (!ugrid2d)
  {
    TS_FAIL("Unable to create UGrid.");
    return;
  }
  TS_ASSERT_EQUALS(14, ugrid2d->GetNumberOfPoints());
  TS_ASSERT_EQUALS(6, ugrid2d->GetNumberOfCells());
  TS_ASSERT_EQUALS(XMU_INVALID_CELL_TYPE, ugrid2d->GetCellType(-1));
  TS_ASSERT_EQUALS(XMU_INVALID_CELL_TYPE, ugrid2d->GetCellType(6));
  TS_ASSERT_EQUALS(XMU_QUAD, ugrid2d->GetCellType(0));
  TS_ASSERT_EQUALS(XMU_PIXEL, ugrid2d->GetCellType(1));
  TS_ASSERT_EQUALS(XMU_TRIANGLE, ugrid2d->GetCellType(2));
  TS_ASSERT_EQUALS(XMU_POLYGON, ugrid2d->GetCellType(3));
  TS_ASSERT_EQUALS(XMU_POLY_LINE, ugrid2d->GetCellType(4));
  TS_ASSERT_EQUALS(XMU_LINE, ugrid2d->GetCellType(5));

  BSHP<XmUGrid> ugrid3d = TEST_XmUGrid3dLinear();
  if (!ugrid3d)
  {
    TS_FAIL("Unable to create UGrid.");
    return;
  }
  TS_ASSERT_EQUALS(30, ugrid3d->GetNumberOfPoints());
  TS_ASSERT_EQUALS(6, ugrid3d->GetNumberOfCells());
  TS_ASSERT_EQUALS(XMU_INVALID_CELL_TYPE, ugrid3d->GetCellType(-1));
  TS_ASSERT_EQUALS(XMU_INVALID_CELL_TYPE, ugrid3d->GetCellType(6));
  TS_ASSERT_EQUALS(XMU_TETRA, ugrid3d->GetCellType(0));
  TS_ASSERT_EQUALS(XMU_VOXEL, ugrid3d->GetCellType(1));
  TS_ASSERT_EQUALS(XMU_HEXAHEDRON, ugrid3d->GetCellType(2));
  TS_ASSERT_EQUALS(XMU_POLYHEDRON, ugrid3d->GetCellType(3));
  TS_ASSERT_EQUALS(XMU_WEDGE, ugrid3d->GetCellType(4));
  TS_ASSERT_EQUALS(XMU_PYRAMID, ugrid3d->GetCellType(5));
} // XmUGridTests::testGetCellType
//------------------------------------------------------------------------------
/// \brief Test getting dimension of single cells and all cells
//------------------------------------------------------------------------------
void XmUGridTests::testGetCellDimension()
{
  BSHP<XmUGrid> ugrid2d = TEST_XmUGrid2dLinear();
  if (!ugrid2d)
  {
    TS_FAIL("Unable to create UGrid.");
    return;
  }

  TS_ASSERT_EQUALS(XMU_INVALID_CELL_TYPE, ugrid2d->GetCellDimension(-1));
  TS_ASSERT_EQUALS(XMU_INVALID_CELL_TYPE, ugrid2d->GetCellDimension(6));
  TS_ASSERT_EQUALS(2, ugrid2d->GetCellDimension(0));
  TS_ASSERT_EQUALS(2, ugrid2d->GetCellDimension(1));
  TS_ASSERT_EQUALS(2, ugrid2d->GetCellDimension(2));
  TS_ASSERT_EQUALS(2, ugrid2d->GetCellDimension(3));
  TS_ASSERT_EQUALS(1, ugrid2d->GetCellDimension(4));
  TS_ASSERT_EQUALS(1, ugrid2d->GetCellDimension(5));

  BSHP<XmUGrid> ugrid3d = TEST_XmUGrid3dLinear();
  if (!ugrid3d)
  {
    TS_FAIL("Unable to create UGrid.");
    return;
  }
  TS_ASSERT_EQUALS(XMU_INVALID_CELL_TYPE, ugrid3d->GetCellDimension(-1));
  TS_ASSERT_EQUALS(XMU_INVALID_CELL_TYPE, ugrid3d->GetCellDimension(6));
  TS_ASSERT_EQUALS(3, ugrid3d->GetCellDimension(0));
  TS_ASSERT_EQUALS(3, ugrid3d->GetCellDimension(1));
  TS_ASSERT_EQUALS(3, ugrid3d->GetCellDimension(2));
  TS_ASSERT_EQUALS(3, ugrid3d->GetCellDimension(3));
  TS_ASSERT_EQUALS(3, ugrid3d->GetCellDimension(4));
  TS_ASSERT_EQUALS(3, ugrid3d->GetCellDimension(5));

  // Test Dimension Counts
  std::vector<int> twoDResults(4, 0),
    threeDResults(4, 0);
  twoDResults[1] = 2;
  twoDResults[2] = 4;
  threeDResults[3] = 6;
  TS_ASSERT_EQUALS(twoDResults, ugrid2d->GetDimensionCount());
  TS_ASSERT_EQUALS(threeDResults, ugrid3d->GetDimensionCount());
} // XmUGridTests::testGetCellDimension

//------------------------------------------------------------------------------
/// \brief Test getting edges of single cells
//------------------------------------------------------------------------------
void XmUGridTests::testGetNumberOfCellEdges()
{
  BSHP<XmUGrid> ugrid2d = TEST_XmUGrid2dLinear();
  if (!ugrid2d)
  {
    TS_FAIL("Unable to create UGrid.");
    return;
  }

  TS_ASSERT_EQUALS(-1, ugrid2d->GetNumberOfCellEdges(-1));
  TS_ASSERT_EQUALS(-1, ugrid2d->GetNumberOfCellEdges(6));
  TS_ASSERT_EQUALS(4, ugrid2d->GetNumberOfCellEdges(0));
  TS_ASSERT_EQUALS(4, ugrid2d->GetNumberOfCellEdges(1));
  TS_ASSERT_EQUALS(3, ugrid2d->GetNumberOfCellEdges(2));
  TS_ASSERT_EQUALS(5, ugrid2d->GetNumberOfCellEdges(3));
  TS_ASSERT_EQUALS(0, ugrid2d->GetNumberOfCellEdges(4));
  TS_ASSERT_EQUALS(0, ugrid2d->GetNumberOfCellEdges(5));

  BSHP<XmUGrid> ugrid3d = TEST_XmUGrid3dLinear();
  if (!ugrid3d)
  {
    TS_FAIL("Unable to create UGrid.");
    return;
  }

  TS_ASSERT_EQUALS(-1, ugrid3d->GetNumberOfCellEdges(-1));
  TS_ASSERT_EQUALS(-1, ugrid3d->GetNumberOfCellEdges(6));
  TS_ASSERT_EQUALS(6, ugrid3d->GetNumberOfCellEdges(0));
  TS_ASSERT_EQUALS(12, ugrid3d->GetNumberOfCellEdges(1));
  TS_ASSERT_EQUALS(12, ugrid3d->GetNumberOfCellEdges(2));
  TS_ASSERT_EQUALS(12, ugrid3d->GetNumberOfCellEdges(3));
  TS_ASSERT_EQUALS(9, ugrid3d->GetNumberOfCellEdges(4));
  TS_ASSERT_EQUALS(8, ugrid3d->GetNumberOfCellEdges(5));

} // XmUGridTests::testGetNumberOfCellEdges
#endif
