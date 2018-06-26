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
#include <boost/container/flat_set.hpp>

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
/// Implementation for XmUGrid
class XmUGridImpl : public XmUGrid
{
public:
  XmUGridImpl();

  virtual int GetNumberOfPoints() const override;
  virtual int GetNumberOfCells() const override;

  virtual Pt3d GetPoint(const int a_pointIdx) const override;
  virtual bool SetPoint(const int a_pointIdx, const Pt3d& a_point) override;

  virtual XmUGridCellType GetCellType(const int a_cellIdx) const override;
  virtual int GetCellDimension(const int a_cellIdx) const override;
  virtual std::vector<int> GetDimensionCount() const override;
  virtual int GetNumberOfCellEdges(const int a_cellIdx) const override;
  virtual int GetNumberOfCellFaces(const int a_cellIdx) const override;

  virtual const VecPt3d& GetPoints() const override;
  virtual void SetPoints(const VecPt3d& a_points) override;

  virtual VecInt GetPointCells(const int a_pointIdx) const override;

  virtual bool GetSingleCellStream(const int a_cellIdx, VecInt& a_cellStream) const override;
  virtual const VecInt& GetCellStream() const override;
  virtual bool SetCellStream(const VecInt& a_cellStream) override;

private:
  void UpdateLinks();
  void UpdateCellLinks();
  void UpdatePointLinks();
  static int DimensionFromCellType(const XmUGridCellType a_cellType);
  int GetNumberOfItemsForCell(const int a_cellIdx) const;
  void GetSingleCellStream(const int a_cellIdx, const int** a_start, int &a_length) const;
  int GetNumberOfPolyhedronEdges(const int a_cellIdx) const;

  VecPt3d m_points; ///< UGrid points
  VecInt m_cellStream; ///< UGrid cell stream. @see SetCellStream, GetCellStream
  VecInt m_cellIdxToStreamIdx; ///< Indexes for each cell in the cell stream
  VecInt m_pointIdxToPointsToCells; ///< Indexes for each point in array of points cells
  VecInt m_pointsToCells; ///< Array of points cells (goes from pointIdx to list of cells)
public:
  static int m_pointLinkReserveSize; ///< Amount to reserve in 1D portion of 2D link array
};



////////////////////////////////////////////////////////////////////////////////
/// \class XmUGrid
/// \brief Implementation for XmUGrid which provides geometry for an
///        unstructured grid.
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
/// \brief Get the point
/// \param[in] a_pointIdx: the index of the point
/// \return the point or an initialize point if the index is invalid
//------------------------------------------------------------------------------
Pt3d XmUGridImpl::GetPoint(const int a_pointIdx) const
{
  if (a_pointIdx >= 0 && a_pointIdx < m_points.size())
    return m_points[a_pointIdx];
  return Pt3d();
} // XmUGridImpl::GetPoint
//------------------------------------------------------------------------------
/// \brief Set the point
/// \param[in] a_pointIdx: the index of the point
/// \return whether the point was successfully set
//------------------------------------------------------------------------------
bool XmUGridImpl::SetPoint(const int a_pointIdx, const Pt3d& a_point)
{
  if (a_pointIdx >= 0 && a_pointIdx < m_points.size())
  {
    m_points[a_pointIdx] = a_point;
    return true;
  }
  return false;
} // XmUGridImpl::GetPoint
//------------------------------------------------------------------------------
/// \brief Get the number of cells.
/// \param[in] a_cellIdx: the index of the cell
/// \return the number of cells or -1 if invalid index
//------------------------------------------------------------------------------
XmUGridCellType XmUGridImpl::GetCellType(const int a_cellIdx) const
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
int XmUGridImpl::GetCellDimension(const int a_cellIdx) const
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
/// \brief Get the number of edges with specified cell
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
    return 1;
    break;
  case XMU_POLY_LINE:
    return GetNumberOfItemsForCell(a_cellIdx)-1;
    break;

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
/// \brief Get the number of cell faces for given cell.
/// \param[in] a_cellIdx: the index of the cell
/// \return the count of cell faces
//------------------------------------------------------------------------------
int XmUGridImpl::GetNumberOfCellFaces(const int a_cellIdx) const
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

  // 2D
  case XMU_TRIANGLE:
  case XMU_TRIANGLE_STRIP:
  case XMU_QUADRATIC_TRIANGLE:
  case XMU_BIQUADRATIC_TRIANGLE:
  case XMU_HIGHER_ORDER_TRIANGLE:
  case XMU_PIXEL:
  case XMU_QUAD:
  case XMU_QUADRATIC_QUAD:
  case XMU_BIQUADRATIC_QUAD:
  case XMU_QUADRATIC_LINEAR_QUAD:
  case XMU_HIGHER_ORDER_QUAD:
  case XMU_POLYGON:
  case XMU_HIGHER_ORDER_POLYGON:
  case XMU_QUADRATIC_POLYGON:
  case XMU_PARAMETRIC_SURFACE:
  case XMU_PARAMETRIC_TRI_SURFACE:
  case XMU_PARAMETRIC_QUAD_SURFACE:
    return 0;
  break;
 
  // 3D dimensions
  case XMU_TETRA:
  case XMU_QUADRATIC_TETRA:
  case XMU_HIGHER_ORDER_TETRAHEDRON:
    return 4;
    break;
    
  case XMU_WEDGE:
  case XMU_QUADRATIC_WEDGE:
  case XMU_QUADRATIC_LINEAR_WEDGE:
  case XMU_BIQUADRATIC_QUADRATIC_WEDGE:
  case XMU_HIGHER_ORDER_WEDGE:
    return 5;
    break;

  case XMU_VOXEL:
  case XMU_HEXAHEDRON:
  case XMU_QUADRATIC_HEXAHEDRON:
  case XMU_TRIQUADRATIC_HEXAHEDRON:
  case XMU_BIQUADRATIC_QUADRATIC_HEXAHEDRON:
  case XMU_HIGHER_ORDER_HEXAHEDRON:
    return 6;
    break;

  case XMU_PYRAMID:
  case XMU_QUADRATIC_PYRAMID:
  case XMU_HIGHER_ORDER_PYRAMID:
    return 5;
    break;

  case XMU_PENTAGONAL_PRISM:
    return 7;
    break;
  case XMU_HEXAGONAL_PRISM:
    return 8;
    break;

  case XMU_POLYHEDRON:
    return GetNumberOfItemsForCell(a_cellIdx);
    break;

  case XMU_PARAMETRIC_TETRA_REGION:
  case XMU_PARAMETRIC_HEX_REGION:
    return -1; // Not yet supported
    break;
  }
  return -1;  
} // XmUGridImpl::GetNumberOfCellFaces
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
/// \brief Get the cells that are associated with the specified point
/// \param[in] a_pointIdx: the index of the point
/// \return a vector of the cell indexes associated with this point
//------------------------------------------------------------------------------
VecInt XmUGridImpl::GetPointCells(const int a_pointIdx) const
{
  VecInt cellsOfPoint;
  int numCells = m_pointsToCells[m_pointIdxToPointsToCells[a_pointIdx]];
  for (int cellIdx=0; cellIdx<numCells; cellIdx++)
  {
    cellsOfPoint.push_back(m_pointsToCells[m_pointIdxToPointsToCells[a_pointIdx]+cellIdx+1]);
  }
  return cellsOfPoint;
} // XmUGridImpl::GetPointCells
//------------------------------------------------------------------------------
/// \brief Get cell stream vector for a single cell.
/// \param[in] a_cellIdx: the index of the cell
/// \param[in] a_cellStream: The cellstream of the cell
/// @see SetCellStream for more detail on cell stream definitions.
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
/// \brief Get cell stream vector for the entire UGrid.
/// \return constant reference to the cell stream vector
//------------------------------------------------------------------------------
const VecInt& XmUGridImpl::GetCellStream() const
{
  return m_cellStream;
} // XmUGridImpl::GetCellStream
//------------------------------------------------------------------------------
/// \brief Set the ugrid cells for the entire UGrid using a cell stream.
/// \param[in] a_cellStream: cells defined as follows:
///              Hexahedrons, polygons, quads, triangles etc:
///                Cell type (ElemTypeEnum), number of points, point numbers.
///                Generally 1-based, CCW, bottom, then top. Not true
///                for pixel or voxel.
///              Polyhedrons:
///                Cell type, number of faces, [num points in face,
///                point numbers (1-based, CCW when looking in)] repeated
///                for each face.
/// \return if successfully set
//------------------------------------------------------------------------------
bool XmUGridImpl::SetCellStream(const VecInt& a_cellStream)
{
  if (ValidCellStream(a_cellStream))
  {
    m_cellStream = a_cellStream;
    UpdateLinks();
    return true;
  }
  else
  {
    XM_LOG(xmlog::error, "Invalid cell stream data.");
    return false;
  }
} // XmUGridImpl::SetCellStream
//------------------------------------------------------------------------------
/// \brief Update internal links to navigate between associated points and
///        cells.
//------------------------------------------------------------------------------
void XmUGridImpl::UpdateLinks()
{
  UpdateCellLinks();
  UpdatePointLinks();
} // XmUGridImpl::UpdateLinks
//------------------------------------------------------------------------------
/// \brief Update internal link from cells to cell stream index.
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
/// \brief Update internal links from points to associated cells.
//------------------------------------------------------------------------------
void XmUGridImpl::UpdatePointLinks()
{
  m_pointIdxToPointsToCells.clear();
  m_pointIdxToPointsToCells.resize(m_points.size(), 0);
  m_pointsToCells.clear();

  // get number of cells for each point
  boost::container::flat_set<int> cellPoints;
  int numStreamItems = (int)m_cellStream.size();
  int cellIdx = 0;
  int currIdx = 0;
  while (currIdx < numStreamItems)
  {
    // get cell type
    int cellType = m_cellStream[currIdx++];
    if (currIdx >= numStreamItems)
      return;

    // get the number of items (points or faces depending on cell type)
    int numCellItems = m_cellStream[currIdx++];
    if (currIdx >= numStreamItems)
      return;

    if (cellType == XMU_POLYHEDRON)
    {
      cellPoints.clear();
      int numFaces = numCellItems;
      for (int faceIdx = 0; faceIdx < numFaces; ++faceIdx)
      {
        int numFacePoints = m_cellStream[currIdx++];
        for (int ptIdx = 0; ptIdx < numFacePoints; ++ptIdx)
        {
          int pt = m_cellStream[currIdx++];
          cellPoints.insert(pt);
        }
      }

      //std::stable_sort(cellPoints.begin(), cellPoints.end());
      //auto uniqueEnd = std::unique(cellPoints.begin(), cellPoints.end());

      //for (auto pt = cellPoints.begin(); pt != uniqueEnd; ++pt)
      for (auto pt = cellPoints.begin(); pt != cellPoints.end(); ++pt)
      {
        m_pointIdxToPointsToCells[*pt] += 1;
      }
    }
    else
    {
      // iterate on points
      int numPoints = numCellItems;
      for (int ptIdx = 0; ptIdx < numPoints; ++ptIdx)
      {
        int pt = m_cellStream[currIdx++];
        m_pointIdxToPointsToCells[pt] += 1;
      }
    }

    ++cellIdx;
  }
  m_pointIdxToPointsToCells.push_back(0);

  // change array of counts to array of offsets
  int currCount = 0;
  for (auto& item: m_pointIdxToPointsToCells)
  {
    int count = item + 1;
    item = currCount;
    currCount += count;
  }

  cellIdx = 0;
  currIdx = 0;
  m_pointsToCells.resize(currCount, 0);
  while (currIdx < numStreamItems)
  {
    // get cell type
    int cellType = m_cellStream[currIdx++];
    if (currIdx >= numStreamItems)
      return;

    // get the number of items (points or faces depending on cell type)
    int numCellItems = m_cellStream[currIdx++];
    if (currIdx >= numStreamItems)
      return;

    if (cellType == XMU_POLYHEDRON)
    {
      cellPoints.clear();
      int numFaces = numCellItems;
      for (int faceIdx = 0; faceIdx < numFaces; ++faceIdx)
      {
        int numFacePoints = m_cellStream[currIdx++];
        for (int ptIdx = 0; ptIdx < numFacePoints; ++ptIdx)
        {
          int pt = m_cellStream[currIdx++];
          cellPoints.insert(pt);
        }
      }

      //std::stable_sort(cellPoints.begin(), cellPoints.end());
      //auto uniqueEnd = std::unique(cellPoints.begin(), cellPoints.end());

      //for (auto pt = cellPoints.begin(); pt != uniqueEnd; ++pt)
      for (auto pt = cellPoints.begin(); pt != cellPoints.end(); ++pt)
      {
        int countIdx = m_pointIdxToPointsToCells[*pt];
        int& count = m_pointsToCells[countIdx]; // point's cell count
        ++count; // incrementing point's cell count
        int updateIdx = countIdx + count;
        m_pointsToCells[updateIdx] = cellIdx;
      }
    }
    else
    {
      // iterate on points
      int numPoints = numCellItems;
      for (int ptIdx = 0; ptIdx < numPoints; ++ptIdx)
      {
        int pt = m_cellStream[currIdx++];
        int countIdx = m_pointIdxToPointsToCells[pt];
        int& count = m_pointsToCells[countIdx]; // point's cell count
        ++count; // incrementing point's cell count
        int updateIdx = countIdx + count;
        m_pointsToCells[updateIdx] = cellIdx;
      }
    }

    ++cellIdx;
  }
} // XmUGridImpl::UpdatePointLinks

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
/// \param[in] a_cellIdx: the index of the cell
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
///        Returns nullptr and zero length for invalid cell index.
/// \param[in] a_cellIdx: the index of the cell
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
/// \param[in] a_cellIdx: the index of the cell
/// \return the number of edges
//------------------------------------------------------------------------------
int XmUGridImpl::GetNumberOfPolyhedronEdges(const int a_cellIdx) const
{
  const int* cellStream;
  int streamLength;
  GetSingleCellStream(a_cellIdx, &cellStream, streamLength);
  if (cellStream && streamLength > 0 && cellStream[0] == XMU_POLYHEDRON)
  {
    boost::container::flat_set<std::pair<int, int>> edges;
    int currItem = 2;
    while (currItem < streamLength)
    {
      int numPoints = cellStream[currItem++];
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
/// \brief Geometry for an unstructured grid.
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
/// \return Returns the UGrid.
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
//------------------------------------------------------------------------------
/// \brief Builds a UGrid of Quads at 1 spacing for rows & cols specified
/// \param[in] a_rows: number of rows in UGrid
/// \param[in] a_cols: number of columns in UGrid
/// \return Returns the UGrid.
//------------------------------------------------------------------------------
BSHP<xms::XmUGrid> TEST_XmUBuildQuadUGrid(const int a_rows, const int a_cols)
{
  VecPt3d points;
  points.reserve(a_rows*a_cols);
  for (int i = 0; i < a_rows; ++i)
  {
    for (int j = 0; j < a_cols; ++j)
    {
      points.push_back(Pt3d(j, a_rows-i));
    }
  }

  VecInt cells;
  cells.reserve((a_rows-1)*(a_cols-1)*6);
  for (int i = 0; i < a_rows-1; ++i)
  {
    for (int j = 0; j < a_cols-1; ++j)
    {
      cells.push_back(XMU_QUAD);
      cells.push_back(4);
      cells.push_back(j+a_cols*i);
      cells.push_back(j+a_cols*(i+1));
      cells.push_back(j+1+a_cols*(i+1));
      cells.push_back(j+1+a_cols*i);
    }
  }
  
  return XmUGrid::New(points, cells);
}  // TEST_XmUBuildQuadUGrid
//------------------------------------------------------------------------------
/// \brief Builds a UGrid of Quads at 1 spacing for rows & cols specified
/// \param[in] a_rows: number of rows in UGrid
/// \param[in] a_cols: number of columns in UGrid
/// \param[in] a_lays: number of layers in UGrid
/// \return Returns the UGrid.
//------------------------------------------------------------------------------
BSHP<xms::XmUGrid> TEST_XmUBuildHexadronUgrid(const int a_rows, const int a_cols, const int a_lays)
{
  VecPt3d points;
  points.reserve(a_rows*a_cols);
  for (int k = 0; k < a_lays; ++k)
  {
    for (int i = 0; i < a_rows; ++i)
    {
      for (int j = 0; j < a_cols; ++j)
      {
        points.push_back(Pt3d(j, a_rows-i, a_lays-k));
      }
    }
  }

  VecInt cells;
  cells.reserve((a_rows-1)*(a_cols-1)*(a_lays-1)*10);
  int numInLayer = a_rows*a_cols;
  for (int k = 0; k < a_lays-1; ++k)
  {
    int layOffset = numInLayer*k;
    for (int i = 0; i < a_rows-1; ++i)
    {
      for (int j = 0; j < a_cols-1; ++j)
      {
        cells.push_back(XMU_HEXAHEDRON);
        cells.push_back(8);
        cells.push_back(j + a_cols*i + layOffset);
        cells.push_back(j + a_cols*(i+1) + layOffset);
        cells.push_back(j + 1 + a_cols*(i+1) + layOffset);
        cells.push_back(j + 1 + a_cols*i + layOffset);
        cells.push_back(j + a_cols*i + layOffset + numInLayer);
        cells.push_back(j + a_cols*(i+1) + layOffset + numInLayer);
        cells.push_back(j + 1 + a_cols*(i+1) + layOffset + numInLayer);
        cells.push_back(j + 1 + a_cols*i + layOffset + numInLayer);
      }
    }
  }
  return XmUGrid::New(points, cells);
} // TEST_XmUBuildHexadronUgrid
//------------------------------------------------------------------------------
/// \brief Builds a UGrid of Quads at 1 spacing for rows & cols specified
/// \param[in] a_rows: number of rows in UGrid
/// \param[in] a_cols: number of columns in UGrid
/// \param[in] a_lays: number of layers in UGrid
/// \return Returns the UGrid.
//------------------------------------------------------------------------------
BSHP<xms::XmUGrid> TEST_XmUBuildPolyhedronUgrid(const int a_rows, const int a_cols, const int a_lays)
{
  VecPt3d points;
  points.reserve(a_rows*a_cols);
  for (int k = 0; k < a_lays; ++k)
  {
    for (int i = 0; i < a_rows; ++i)
    {
      for (int j = 0; j < a_cols; ++j)
      {
        points.push_back(Pt3d(j, a_rows-i, a_lays-k));
      }
    }
  }

  VecInt cells;
  cells.reserve((a_rows-1)*(a_cols-1)*(a_lays-1)*10);
  int numInLayer = a_rows*a_cols;
  for (int k = 0; k < a_lays-1; ++k)
  {
    int layOffset = numInLayer*k;
    for (int i = 0; i < a_rows-1; ++i)
    {
      for (int j = 0; j < a_cols-1; ++j)
      {
        int pt0 = j + a_cols*i + layOffset;
        int pt1 = j + a_cols*(i+1) + layOffset;
        int pt2 = j + 1 + a_cols*(i+1) + layOffset;
        int pt3 = j + 1 + a_cols*i + layOffset;
        int pt4 = j + a_cols*i + layOffset + numInLayer;
        int pt5 = j + a_cols*(i+1) + layOffset + numInLayer;
        int pt6 = j + 1 + a_cols*(i+1) + layOffset + numInLayer;
        int pt7 = j + 1 + a_cols*i + layOffset + numInLayer;

        cells.push_back(XMU_POLYHEDRON);
        cells.push_back(6);
        // top
        cells.push_back(4);
        cells.push_back(pt0);
        cells.push_back(pt1);
        cells.push_back(pt2);
        cells.push_back(pt3);
        // front
        cells.push_back(4);
        cells.push_back(pt0);
        cells.push_back(pt1);
        cells.push_back(pt5);
        cells.push_back(pt7);
        // right
        cells.push_back(4);
        cells.push_back(pt1);
        cells.push_back(pt3);
        cells.push_back(pt7);
        cells.push_back(pt5);
        // back
        cells.push_back(4);
        cells.push_back(pt3);
        cells.push_back(pt2);
        cells.push_back(pt6);
        cells.push_back(pt7);
        // left
        cells.push_back(4);
        cells.push_back(pt2);
        cells.push_back(pt0);
        cells.push_back(pt4);
        cells.push_back(pt6);
        // bottom
        cells.push_back(4);
        cells.push_back(pt4);
        cells.push_back(pt5);
        cells.push_back(pt6);
        cells.push_back(pt7);
      }
    }
  }
  return XmUGrid::New(points, cells);
}  // TEST_XmUBuildPolyhedronUgrid
//------------------------------------------------------------------------------
/// \brief Path to test files.
/// \return Returns path to test files.
//------------------------------------------------------------------------------
std::string TestFilesPath()
{
  //return "../" + std::string(XMSNG_TEST_PATH);
  return "J:/xmsgrid/test_files/";
} // TestFilesPath

////////////////////////////////////////////////////////////////////////////////
/// \class XmUGridUnitTests
/// \brief Tests XmUGrids.
////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
/// \brief Test XmUGrid point and cell streams.
//------------------------------------------------------------------------------
void XmUGridUnitTests::testUGridStreams()
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
} // XmUGridUnitTests::testUGridStreams
////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
/// \brief Test Getting a point
/// \code
  ///
  ///     0----1----2
  ///     |    |    |
  ///     3----4----5
  ///     |    |    |
  ///     6----7----8
  ///
  /// \endcode
//------------------------------------------------------------------------------
void XmUGridUnitTests::testGetSetPoint()
{
  VecPt3d points = {{0, 10, 0}, {10, 10, 0}, {20, 10, 0},  {0, 0, 0}, {10, 0, 0},
            {20, 0, 0}, {0, -10, 0}, {10, -10, 0}, {20, -10, 0}};

  // Cell type (9), number of points (4), point numbers, counterclockwise
  VecInt cellStream = {
    9, 4, 0, 3, 4, 1,
    9, 4, 1, 4, 5, 2,
    9, 4, 3, 6, 7, 4,
    9, 4, 4, 7, 8, 5};

  BSHP<XmUGrid> ugrid = XmUGrid::New(points, cellStream);

  TS_ASSERT_EQUALS(Pt3d(), ugrid->GetPoint(-1));
  for (int i=0; i < (int)points.size(); i++)
  {
    TS_ASSERT_EQUALS(points[i], ugrid->GetPoint(i));
  }
  TS_ASSERT_EQUALS(Pt3d(), ugrid->GetPoint((int)points.size()));
  
  TS_ASSERT(!ugrid->SetPoint(-1, Pt3d()));
  TS_ASSERT(!ugrid->SetPoint((int)points.size(), Pt3d()));

  TS_ASSERT(ugrid->SetPoint(0, Pt3d(-10, 10, 0)));
  TS_ASSERT_EQUALS(Pt3d(-10, 10, 0), ugrid->GetPoint(0));

} // XmUGridUnitTests::testGetSetPoint
////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
/// \brief Test Getting a cell stream.
/// \code
  ///
  ///     0-----1-----2
  ///     |  0  |  1  |
  ///     3-----4-----5
  ///     |  2  |  3  |
  ///     6-----7-----8
  ///
  /// \endcode
//------------------------------------------------------------------------------
void XmUGridUnitTests::testGetSingleCellStream()
{
  VecPt3d points = {{0, 10, 0}, {10, 10, 0}, {20, 10, 0},  {0, 0, 0}, {10, 0, 0},
            {20, 0, 0}, {0, -10, 0}, {10, -10, 0}, {20, -10, 0}};

  VecInt cell0 = {9, 4, 0, 3, 4, 1},
    cell1 = {9, 4, 1, 4, 5, 2},
    cell2 = {9, 4, 3, 6, 7, 4},
    cell3 = {9, 4, 4, 7, 8, 5};
  // Cell type (9), number of points (4), point numbers, counterclockwise
  VecInt cellStream;
  cellStream.insert(cellStream.end(), cell0.begin(), cell0.end());
  cellStream.insert(cellStream.end(), cell1.begin(), cell1.end());
  cellStream.insert(cellStream.end(), cell2.begin(), cell2.end());
  cellStream.insert(cellStream.end(), cell3.begin(), cell3.end());

  BSHP<XmUGrid> ugrid = XmUGrid::New(points, cellStream);
  VecInt cellResult;

  TS_ASSERT_EQUALS(false, ugrid->GetSingleCellStream(-1, cellResult));
  
  TS_ASSERT_EQUALS(true, ugrid->GetSingleCellStream(0, cellResult));
  TS_ASSERT_EQUALS(cell0, cellResult);
  TS_ASSERT_EQUALS(true, ugrid->GetSingleCellStream(1, cellResult));
  TS_ASSERT_EQUALS(cell1, cellResult);
  TS_ASSERT_EQUALS(true, ugrid->GetSingleCellStream(2, cellResult));
  TS_ASSERT_EQUALS(cell2, cellResult);
  TS_ASSERT_EQUALS(true, ugrid->GetSingleCellStream(3, cellResult));
  TS_ASSERT_EQUALS(cell3, cellResult);

  TS_ASSERT_EQUALS(false, ugrid->GetSingleCellStream((int)points.size(), cellResult));

} // XmUGridUnitTests::testGetSingleCellStream
//------------------------------------------------------------------------------
/// \brief Test getting number of points, cells, and cell type.
//------------------------------------------------------------------------------
void XmUGridUnitTests::testGetCellType()
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
} // XmUGridUnitTests::testGetCellType
//------------------------------------------------------------------------------
/// \brief Test getting dimension of single cells and all cells.
//------------------------------------------------------------------------------
void XmUGridUnitTests::testGetCellDimension()
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
} // XmUGridUnitTests::testGetCellDimension
//------------------------------------------------------------------------------
/// \brief Test getting edges of single cells.
//------------------------------------------------------------------------------
void XmUGridUnitTests::testGetNumberOfCellEdges()
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
  TS_ASSERT_EQUALS(2, ugrid2d->GetNumberOfCellEdges(4));
  TS_ASSERT_EQUALS(1, ugrid2d->GetNumberOfCellEdges(5));

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

} // XmUGridUnitTests::testGetNumberOfCellEdges
//------------------------------------------------------------------------------
/// \brief Test getting edges of single cells.
//------------------------------------------------------------------------------
void XmUGridUnitTests::testGetNumberOfCellFaces()
{
  BSHP<XmUGrid> ugrid2d = TEST_XmUGrid2dLinear();
  if (!ugrid2d)
  {
    TS_FAIL("Unable to create UGrid.");
    return;
  }

  // test 1D and 2D cells
  TS_ASSERT_EQUALS(-1, ugrid2d->GetNumberOfCellFaces(-1));
  for (int cellIdx = 0; cellIdx < ugrid2d->GetNumberOfCells(); ++cellIdx)
  {
    TS_ASSERT_EQUALS(0, ugrid2d->GetNumberOfCellFaces(cellIdx));
  }
  TS_ASSERT_EQUALS(-1, ugrid2d->GetNumberOfCellFaces(ugrid2d->GetNumberOfCells()));

  BSHP<XmUGrid> ugrid3d = TEST_XmUGrid3dLinear();
  if (!ugrid3d)
  {
    TS_FAIL("Unable to create UGrid.");
    return;
  }

  // test 3D cells
  TS_ASSERT_EQUALS(-1, ugrid3d->GetNumberOfCellFaces(-1));
  TS_ASSERT_EQUALS(-1, ugrid3d->GetNumberOfCellFaces(6));
  TS_ASSERT_EQUALS(4, ugrid3d->GetNumberOfCellFaces(0));
  TS_ASSERT_EQUALS(6, ugrid3d->GetNumberOfCellFaces(1));
  TS_ASSERT_EQUALS(6, ugrid3d->GetNumberOfCellFaces(2));
  TS_ASSERT_EQUALS(6, ugrid3d->GetNumberOfCellFaces(3));
  TS_ASSERT_EQUALS(5, ugrid3d->GetNumberOfCellFaces(4));
  TS_ASSERT_EQUALS(5, ugrid3d->GetNumberOfCellFaces(5));
} // XmUGridUnitTests::testGetNumberOfCellFaces
//------------------------------------------------------------------------------
/// \brief Test getting the cells attached to points.
/// \code
///
///     0----1----2
///     |    |    |
///     3----4----5
///
/// \endcode
//------------------------------------------------------------------------------
void XmUGridUnitTests::testGetPointCellsSimple()
{
  VecPt3d points = {{0, 10, 0}, {10, 10, 0}, {20, 10, 0},  
                    {0, 0, 0},  {10, 0, 0},  {20, 0, 0}};

  VecInt cellStream = {XMU_QUAD, 4, 0, 3, 4, 1, XMU_QUAD, 4, 1, 4, 5, 2};

  BSHP<XmUGrid> ugrid = XmUGrid::New(points, cellStream);

  VecInt cellZero = {0};
  VecInt cellZeroAndOne = {0,1};
  VecInt cellOne = {1};
  TS_ASSERT_EQUALS(cellZero, ugrid->GetPointCells(0));
  TS_ASSERT_EQUALS(cellZeroAndOne, ugrid->GetPointCells(1));
  TS_ASSERT_EQUALS(cellOne, ugrid->GetPointCells(2));
  TS_ASSERT_EQUALS(cellZero, ugrid->GetPointCells(3));
  TS_ASSERT_EQUALS(cellZeroAndOne, ugrid->GetPointCells(4));
  TS_ASSERT_EQUALS(cellOne, ugrid->GetPointCells(5));

} // XmUGridUnitTests::testGetNumberOfCellFaces

//------------------------------------------------------------------------------
/// \brief Test getting edges of single cells.
//------------------------------------------------------------------------------
void XmUGridUnitTests::testGetPointCells()
{
  BSHP<XmUGrid> ugrid2d = TEST_XmUGrid2dLinear();
  if (!ugrid2d)
  {
    TS_FAIL("Unable to create UGrid.");
    return;
  }

  VecInt2d cellsFor2DPoints = 
    {{ 0},         // point 0
    {0, 1},        // point 1
    {1, 2},        // point 2
    {2, 3},        // point 3
    {3},           // point 4
    {0, 5},        // point 5
    {0, 1},        // point 6
    {1, 2, 3, 4},  // point 7
    {3},           // point 8
    {5},           // point 9
    {4},           // point 10
    {4},           // point 11
    {3},           // point 12
    {3}};          // point 13

  // test 1D and 2D cells
  for (int i(0); i<cellsFor2DPoints.size(); i++)
  {
    TS_ASSERT_EQUALS(cellsFor2DPoints[i], ugrid2d->GetPointCells(i));
  }
  

  BSHP<XmUGrid> ugrid3d = TEST_XmUGrid3dLinear();
  if (!ugrid3d)
  {
    TS_FAIL("Unable to create UGrid.");
    return;
  }
  VecInt2d cellsFor3DPoints = 
    {{ 0},         // point 0
    {0, 1},        // point 1
    {1, 2},        // point 2
    {2, 4},        // point 3
    {4},           // point 4
    {0, 5},           // point 5
    {1,5},           // point 6
    {1,2},           // point 7
    {2,3,4},           // point 8
    {3,4},           // point 9
    {5},           // point 10
    {5},           // point 11
    {},           // point 12
    {3},           // point 13
    {3},           // point 14
    {0},           // point 15
    {1},           // point 16
    {1,2},           // point 17
    {2,4},           // point 18
    {},           // point 19
    {5},           // point 20
    {1},           // point 21
    {1,2},           // point 22
    {2,3,4},           // point 23
    {3},           // point 24
    {},           // point 25
    {},           // point 26
    {},           // point 27
    {3},           // point 28
    {3},           // point 29
    {}};           // point 30

  // test 3D cells
  for (int i(0); i<cellsFor3DPoints.size(); i++)
  {
    if (cellsFor3DPoints[i] != ugrid3d->GetPointCells(i))
    {
      TS_FAIL(i);
    }
    TS_ASSERT_EQUALS(cellsFor3DPoints[i], ugrid3d->GetPointCells(i));
  }

} // XmUGridUnitTests::testGetPointCells
//------------------------------------------------------------------------------
/// \brief Timer Code
//------------------------------------------------------------------------------

#include <chrono>

class Timer
{
public:
    Timer() : beg_(clock_::now()) {}
    void reset() { beg_ = clock_::now(); }
    double elapsed() const { 
        return std::chrono::duration_cast<second_>
            (clock_::now() - beg_).count(); }

private:
    typedef std::chrono::high_resolution_clock clock_;
    typedef std::chrono::duration<double, std::ratio<1> > second_;
    std::chrono::time_point<clock_> beg_;
};


//------------------------------------------------------------------------------
/// \brief Tests creating a large UGrid and checks the time spent.
//------------------------------------------------------------------------------
void XmUGridUnitTests::testLargeUGridLinkSpeed()
{
//#define SPEEDTEST 5
#ifdef SPEEDTEST
  int rows = 500;
  int cols = 500;
  int lays = 4;

  BSHP<xms::XmUGrid> grid = TEST_XmUBuildQuadUGrid(rows, cols);
  //BSHP<xms::XmUGrid> grid = TEST_XmUBuildHexadronUgrid(rows, cols, lays);
  //BSHP<xms::XmUGrid> grid = TEST_XmUBuildPolyhedronUgrid(rows, cols, lays);

  {
    Timer timer2;
    BSHP<XmUGrid> ugrid = XmUGrid::New(grid->GetPoints(), grid->GetCellStream());
    double seconds2 = timer2.elapsed();
    TS_ASSERT_EQUALS(0.0, seconds2);
  }
#endif
} // XmUGridUnitTests::testLargeUGridLinkSpeed

#endif
