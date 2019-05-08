//------------------------------------------------------------------------------
/// \file XmUGridUtils.cpp
/// \ingroup ugrid
/// \copyright (C) Copyright Aquaveo 2018. Distributed under FreeBSD License
/// (See accompanying file LICENSE or https://aqaveo.com/bsd/license.txt)
//------------------------------------------------------------------------------

//----- Included files ---------------------------------------------------------

// 1. Precompiled header

// 2. My own header
#include <xmsgrid/ugrid/XmUGridUtils.h>

// 3. Standard library headers
#include <fstream>

// 4. External library headers
#include <boost/bimap.hpp>

// 5. Shared code headers
#include <xmscore/dataio/daStreamIo.h>
#include <xmscore/misc/StringUtil.h>
#include <xmscore/misc/XmError.h>
#include <xmscore/misc/XmLog.h>
#include <xmscore/stl/vector.h>
#include <xmsgrid/ugrid/XmUGrid.h>

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

//----- Class / Function definitions -------------------------------------------

namespace
{
typedef boost::bimap<std::string, int> CellNameToType;
// makes string int value pairs for enum
#define ENUM_TO_XMU_PAIR(A_ENUM)                                             \
  {                                                                          \
    cellNameToInt.insert(CellNameToType::value_type(#A_ENUM, XMU_##A_ENUM)); \
  }

//------------------------------------------------------------------------------
/// \brief Get a bi-map from a cell type string to a cell type integer.
/// \return The bi-map from a cell type string to a cell type integer.
//------------------------------------------------------------------------------
const CellNameToType& iCellTypeStringIntPair()
{
  static CellNameToType cellNameToInt;
  if (cellNameToInt.empty())
  {
    ENUM_TO_XMU_PAIR(INVALID_CELL_TYPE);
    ENUM_TO_XMU_PAIR(EMPTY_CELL);
    ENUM_TO_XMU_PAIR(VERTEX);
    ENUM_TO_XMU_PAIR(POLY_VERTEX);
    ENUM_TO_XMU_PAIR(LINE);
    ENUM_TO_XMU_PAIR(POLY_LINE);
    ENUM_TO_XMU_PAIR(TRIANGLE);
    ENUM_TO_XMU_PAIR(TRIANGLE_STRIP);
    ENUM_TO_XMU_PAIR(POLYGON);
    ENUM_TO_XMU_PAIR(PIXEL);
    ENUM_TO_XMU_PAIR(QUAD);
    ENUM_TO_XMU_PAIR(TETRA);
    ENUM_TO_XMU_PAIR(VOXEL);
    ENUM_TO_XMU_PAIR(HEXAHEDRON);
    ENUM_TO_XMU_PAIR(WEDGE);
    ENUM_TO_XMU_PAIR(PYRAMID);
    ENUM_TO_XMU_PAIR(PENTAGONAL_PRISM);
    ENUM_TO_XMU_PAIR(HEXAGONAL_PRISM);
    ENUM_TO_XMU_PAIR(QUADRATIC_EDGE);
    ENUM_TO_XMU_PAIR(QUADRATIC_TRIANGLE);
    ENUM_TO_XMU_PAIR(QUADRATIC_QUAD);
    ENUM_TO_XMU_PAIR(QUADRATIC_POLYGON);
    ENUM_TO_XMU_PAIR(QUADRATIC_TETRA);
    ENUM_TO_XMU_PAIR(QUADRATIC_HEXAHEDRON);
    ENUM_TO_XMU_PAIR(QUADRATIC_WEDGE);
    ENUM_TO_XMU_PAIR(QUADRATIC_PYRAMID);
    ENUM_TO_XMU_PAIR(BIQUADRATIC_QUAD);
    ENUM_TO_XMU_PAIR(TRIQUADRATIC_HEXAHEDRON);
    ENUM_TO_XMU_PAIR(QUADRATIC_LINEAR_QUAD);
    ENUM_TO_XMU_PAIR(QUADRATIC_LINEAR_WEDGE);
    ENUM_TO_XMU_PAIR(BIQUADRATIC_QUADRATIC_WEDGE);
    ENUM_TO_XMU_PAIR(BIQUADRATIC_QUADRATIC_HEXAHEDRON);
    ENUM_TO_XMU_PAIR(BIQUADRATIC_TRIANGLE);
    ENUM_TO_XMU_PAIR(CUBIC_LINE);
    ENUM_TO_XMU_PAIR(CONVEX_POINT_SET);
    ENUM_TO_XMU_PAIR(POLYHEDRON);
    ENUM_TO_XMU_PAIR(PARAMETRIC_CURVE);
    ENUM_TO_XMU_PAIR(PARAMETRIC_SURFACE);
    ENUM_TO_XMU_PAIR(PARAMETRIC_TRI_SURFACE);
    ENUM_TO_XMU_PAIR(PARAMETRIC_QUAD_SURFACE);
    ENUM_TO_XMU_PAIR(PARAMETRIC_TETRA_REGION);
    ENUM_TO_XMU_PAIR(PARAMETRIC_HEX_REGION);
    ENUM_TO_XMU_PAIR(HIGHER_ORDER_EDGE);
    ENUM_TO_XMU_PAIR(HIGHER_ORDER_TRIANGLE);
    ENUM_TO_XMU_PAIR(HIGHER_ORDER_QUAD);
    ENUM_TO_XMU_PAIR(HIGHER_ORDER_POLYGON);
    ENUM_TO_XMU_PAIR(HIGHER_ORDER_TETRAHEDRON);
    ENUM_TO_XMU_PAIR(HIGHER_ORDER_WEDGE);
    ENUM_TO_XMU_PAIR(HIGHER_ORDER_PYRAMID);
    ENUM_TO_XMU_PAIR(HIGHER_ORDER_HEXAHEDRON);
  }
  return cellNameToInt;
} // coCellTypesToNumeric

//------------------------------------------------------------------------------
/// \brief Get string for given cell type.
/// \param a_type The cell type.
/// \return The string for the cell type.
//------------------------------------------------------------------------------
std::string iStringFromCellType(int a_type)
{
  const CellNameToType& biMap = iCellTypeStringIntPair();
  auto it = biMap.right.find(a_type);
  if (it != biMap.right.end())
    return it->second;
  XM_ASSERT(0);
  return std::string();
} // iStringFromCellType

//------------------------------------------------------------------------------
/// \brief Get cell type for given string.
/// \param a_type The cell type string.
/// \return The integer cell type.
//------------------------------------------------------------------------------
int iCellTypeFromString(const std::string& a_type)
{
  const CellNameToType& biMap = iCellTypeStringIntPair();
  auto it = biMap.left.find(a_type);
  if (it != biMap.left.end())
    return it->second;
  return XMU_INVALID_CELL_TYPE;
} // iCellTypeFromString

} // namespace {

//------------------------------------------------------------------------------
/// \brief Read XmUGrid from an ASCII file.
/// \param[in] a_filePath: filename to read including path, file name, and
/// extension
/// \return the UGrid that was read from the file
//------------------------------------------------------------------------------
BSHP<XmUGrid> XmReadUGridFromAsciiFile(const std::string& a_filePath)
{
  std::ifstream inFile(a_filePath);
  return XmReadUGridFromStream(inFile);
} // XmReadUGridFromAsciiFile
//------------------------------------------------------------------------------
/// \brief Read an XmUGrid from ASCII text from an input stream.
/// \param[in] a_inStream: the stream to read
/// \return the UGrid
//------------------------------------------------------------------------------
BSHP<XmUGrid> XmReadUGridFromStream(std::istream& a_inStream)
{
  if (a_inStream.eof())
  {
    return nullptr;
  }

  std::string versionString;
  if (!daReadLine(a_inStream, versionString))
  {
    XM_LOG(xmlog::error, "Unable to read file version or file type.");
    return nullptr;
  }

  double version;
  if (versionString == "ASCII XmUGrid Version 1.0")
  {
    version = 1.0;
  }
  else if (versionString == "ASCII XmUGrid Version 1.1")
  {
    version = 1.1;
  }
  else
  {
    XM_LOG(xmlog::error, "Unsupported file version or file type.");
    return nullptr;
  }

  int pointCount;
  if (!daReadIntLine(a_inStream, "NUM_POINTS", pointCount))
  {
    XM_LOG(xmlog::error, "Unable to read XmUGrid point count.");
    return nullptr;
  }

  VecPt3d locations;
  locations.reserve(pointCount);
  for (int pointIdx = 0; pointIdx < pointCount; ++pointIdx)
  {
    Pt3d point;
    if (!daRead3DoubleLine(a_inStream, "POINT", point.x, point.y, point.z))
    {
      XM_LOG(xmlog::error, "Unable to read XmUGrid point.");
      return nullptr;
    }
    locations.push_back(point);
  }

  int cellStreamSize;
  if (!daReadIntLine(a_inStream, "NUM_CELL_ITEMS", cellStreamSize))
  {
    XM_LOG(xmlog::error, "Unable to read XmUGrid cells.");
    return nullptr;
  }

  VecInt cellstream;
  cellstream.reserve(cellStreamSize);
  while ((int)cellstream.size() < cellStreamSize && !a_inStream.eof())
  {
    std::string cardName;
    a_inStream >> cardName;
    if (cardName == "CELL")
    {
      std::string cellLine;
      if (!daReadLine(a_inStream, cellLine))
      {
        XM_LOG(xmlog::error, "Unable to read CELL line.");
        return nullptr;
      }
      int cellType = XMU_INVALID_CELL_TYPE;
      std::string cellTypeString;
      if (version == 1.0 && daReadIntFromLine(cellLine, cellType))
      {
        cellTypeString = iStringFromCellType(cellType);
        if (cellTypeString.empty())
          cellType = XMU_INVALID_CELL_TYPE;
      }
      else if (version == 1.1 && daReadStringFromLine(cellLine, cellTypeString))
      {
        cellType = iCellTypeFromString(cellTypeString);
      }
      else
      {
        cellType = XMU_INVALID_CELL_TYPE;
      }

      if (cellType == XMU_INVALID_CELL_TYPE)
      {
        XM_LOG(xmlog::error, "Found invalid cell type.");
        return nullptr;
      }

      cellstream.push_back(cellType);
      if (cellType == XMU_POLYHEDRON)
      {
        int numFaces;
        daReadIntFromLine(cellLine, numFaces);
        cellstream.push_back(numFaces);
        for (int faceIdx = 0; faceIdx < numFaces; ++faceIdx)
        {
          if (!daReadLine(a_inStream, cellLine))
          {
            XM_LOG(xmlog::error, "Unable to read cell stream.");
            return nullptr;
          }
          int numPoints;
          daReadIntFromLine(cellLine, numPoints);
          cellstream.push_back(numPoints);
          for (int i = 0; i < numPoints; ++i)
          {
            int ptIdx;
            daReadIntFromLine(cellLine, ptIdx);
            cellstream.push_back(ptIdx);
          }
        }
      }
      else
      {
        int numPoints;
        daReadIntFromLine(cellLine, numPoints);
        cellstream.push_back(numPoints);
        for (int i = 0; i < numPoints; ++i)
        {
          int ptIdx;
          daReadIntFromLine(cellLine, ptIdx);
          cellstream.push_back(ptIdx);
        }
      }
    }
    else
    {
      XM_LOG(xmlog::error, "Unable to read XmUGrid cell.");
      return nullptr;
    }
  }

  BSHP<XmUGrid> ugrid = XmUGrid::New(locations, cellstream);
  return ugrid;
} // XmReadUGridFromStream
//------------------------------------------------------------------------------
/// \brief Write an XmUGrid to an ASCII file.
/// \param[in] a_ugrid: The UGrid to write to the file
/// \param[in] a_filePath: filename to write including path, file name, and
/// extension
//------------------------------------------------------------------------------
void XmWriteUGridToAsciiFile(BSHP<XmUGrid> a_ugrid, const std::string& a_filePath)
{
  std::ofstream outFile(a_filePath);
  XmWriteUGridToStream(a_ugrid, outFile);
} // XmWriteUGridToAsciiFile
//------------------------------------------------------------------------------
/// \brief Save an XmUGrid ASCII text to output stream.
/// \param[in] a_ugrid: the UGrid to save
/// \param[in] a_outStream: the stream to write
//------------------------------------------------------------------------------
void XmWriteUGridToStream(BSHP<XmUGrid> a_ugrid, std::ostream& a_outStream)
{
  XmWriteUGridToStream(*a_ugrid, a_outStream);
} // XmWriteUGridToStream
//------------------------------------------------------------------------------
/// \brief Save an XmUGrid ASCII text to output stream.
/// \param[in] a_ugrid: the UGrid to save
/// \param[in] a_outStream: the stream to write
//------------------------------------------------------------------------------
void XmWriteUGridToStream(const XmUGrid& a_ugrid, std::ostream& a_outStream)
{
  a_outStream << "ASCII XmUGrid Version 1.1\n";

  // number of points
  const VecPt3d& points = a_ugrid.GetLocations();
  a_outStream << "NUM_POINTS " << points.size() << "\n";

  // points
  for (size_t i = 0; i < points.size(); ++i)
  {
    const Pt3d& p = points[i];
    a_outStream << "  POINT " << STRstd(p.x) << " " << STRstd(p.y) << " " << STRstd(p.z) << "\n";
  }

  // number of cell stream items
  const VecInt& cellstream = a_ugrid.GetCellstream();
  int cellstreamSize = (int)cellstream.size();
  a_outStream << "NUM_CELL_ITEMS " << cellstreamSize << "\n";

  // cells
  int currIdx = 0;
  while (currIdx < cellstreamSize)
  {
    int cellType = cellstream[currIdx++];
    std::string cellTypeString = iStringFromCellType(cellType);
    int numItems = cellstream[currIdx++];
    a_outStream << "  CELL ";
    if (!cellTypeString.empty())
    {
      a_outStream << cellTypeString;
    }
    else
    {
      std::ostringstream err;
      err << "Unknow cell type (" << cellType << ").";
      XM_LOG(xmlog::error, err.str());
      return;
    }
    if (cellType == -1)
    {
      currIdx += numItems;
    }
    else if (cellType == XMU_POLYHEDRON)
    {
      int numFaces = numItems;
      a_outStream << " " << numFaces;
      for (int faceIdx = 0; faceIdx < numFaces; ++faceIdx)
      {
        numItems = cellstream[currIdx++];
        a_outStream << "\n    " << numItems;
        for (int itemIdx = 0; itemIdx < numItems; ++itemIdx)
        {
          a_outStream << " " << cellstream[currIdx++];
        }
      }
    }
    else
    {
      a_outStream << " " << numItems;
      for (int itemIdx = 0; itemIdx < numItems; ++itemIdx)
      {
        a_outStream << " " << cellstream[currIdx++];
      }
    }
    a_outStream << "\n";
  }
} // XmWriteUGridToStream

} // namespace xms

#ifdef CXX_TEST
//------------------------------------------------------------------------------
// Unit Tests
//------------------------------------------------------------------------------
using namespace xms;
#include <xmsgrid/ugrid/XmUGrid.t.h>
#include <xmsgrid/ugrid/XmUGridUtils.t.h>

////////////////////////////////////////////////////////////////////////////////
/// \class XmUGridTests
/// \brief Tests XmUGrids.
////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
/// \brief Test writing an ASCII file for an empty UGrid.
//------------------------------------------------------------------------------
void XmUGridUtilsTests::testWriteEmptyUGrid()
{
  BSHP<XmUGrid> ugrid = XmUGrid::New();
  std::ostringstream output;
  XmWriteUGridToStream(ugrid, output);

  std::string outputBase =
    "ASCII XmUGrid Version 1.1\n"
    "NUM_POINTS 0\n"
    "NUM_CELL_ITEMS 0\n";
  TS_ASSERT_EQUALS(outputBase, output.str());
} // XmUGridReaderTests::testWriteEmptyUGrid
//------------------------------------------------------------------------------
/// \brief Test writing an ASCII file for a single triangle UGrid.
//------------------------------------------------------------------------------
void XmUGridUtilsTests::testWriteBasicUGrid()
{
  BSHP<XmUGrid> ugrid = TEST_XmUGrid1Left90Tri();
  std::ostringstream output;
  XmWriteUGridToStream(ugrid, output);

  std::string outputBase =
    "ASCII XmUGrid Version 1.1\n"
    "NUM_POINTS 3\n"
    "  POINT 0.0 0.0 0.0\n"
    "  POINT 20.0 0.0 0.0\n"
    "  POINT 0.0 20.0 0.0\n"
    "NUM_CELL_ITEMS 5\n"
    "  CELL TRIANGLE 3 0 1 2\n";
  TS_ASSERT_EQUALS(outputBase, output.str());
} // XmUGridUtilsTests::testWriteBasicUGrid
//------------------------------------------------------------------------------
/// \brief Test writing an ASCII file for a single polyhedron UGrid.
//------------------------------------------------------------------------------
void XmUGridUtilsTests::testWritePolyhedronUGrid()
{
  BSHP<XmUGrid> ugrid = TEST_XmUGridHexagonalPolyhedron();
  std::ostringstream output;
  XmWriteUGridToStream(ugrid, output);

  std::string outputBase =
    "ASCII XmUGrid Version 1.1\n"
    "NUM_POINTS 8\n"
    "  POINT 0.0 0.0 10.0\n"
    "  POINT 10.0 0.0 10.0\n"
    "  POINT 10.0 10.0 10.0\n"
    "  POINT 0.0 10.0 10.0\n"
    "  POINT 0.0 0.0 0.0\n"
    "  POINT 10.0 0.0 0.0\n"
    "  POINT 10.0 10.0 0.0\n"
    "  POINT 0.0 10.0 0.0\n"
    "NUM_CELL_ITEMS 32\n"
    "  CELL POLYHEDRON 6\n"
    "    4 0 1 2 3\n"
    "    4 4 5 7 2\n"
    "    4 5 6 2 1\n"
    "    4 6 7 3 2\n"
    "    4 7 4 0 3\n"
    "    4 4 7 6 5\n";
  TS_ASSERT_EQUALS(outputBase, output.str());
} // XmUGridUtilsTests::testWritePolyhedronUGrid
//------------------------------------------------------------------------------
/// \brief Test writing an ASCII file for UGrid with supported 1D and 2D linear
///        cell types.
//------------------------------------------------------------------------------
void XmUGridUtilsTests::testWriteLinear2dCells()
{
  BSHP<XmUGrid> ugrid = TEST_XmUGrid2dLinear();
  std::ostringstream output;
  XmWriteUGridToStream(ugrid, output);

  std::string outputBase =
    "ASCII XmUGrid Version 1.1\n"
    "NUM_POINTS 14\n"
    "  POINT 0.0 0.0 0.0\n"
    "  POINT 10.0 0.0 0.0\n"
    "  POINT 20.0 0.0 0.0\n"
    "  POINT 30.0 0.0 0.0\n"
    "  POINT 40.0 0.0 0.0\n"
    "  POINT 0.0 10.0 0.0\n"
    "  POINT 10.0 10.0 0.0\n"
    "  POINT 20.0 10.0 0.0\n"
    "  POINT 40.0 10.0 0.0\n"
    "  POINT 0.0 20.0 0.0\n"
    "  POINT 10.0 20.0 0.0\n"
    "  POINT 20.0 20.0 0.0\n"
    "  POINT 30.0 20.0 0.0\n"
    "  POINT 40.0 20.0 0.0\n"
    "NUM_CELL_ITEMS 34\n"
    "  CELL QUAD 4 0 1 6 5\n"
    "  CELL PIXEL 4 1 2 6 7\n"
    "  CELL TRIANGLE 3 2 3 7\n"
    "  CELL POLYGON 6 3 4 8 13 12 7\n"
    "  CELL POLY_LINE 3 7 11 10\n"
    "  CELL LINE 2 5 9\n";
  TS_ASSERT_EQUALS(outputBase, output.str());
} // XmUGridUtilsTests::testWriteLinear2dCells
//------------------------------------------------------------------------------
/// \brief Test writing an ASCII file for UGrid with supported 1D and 2D linear
///        cell types.
//------------------------------------------------------------------------------
void XmUGridUtilsTests::testWriteLinear3dCells()
{
  BSHP<XmUGrid> ugrid = TEST_XmUGrid3dLinear();
  std::ostringstream output;
  XmWriteUGridToStream(ugrid, output);

  std::string outputBase =
    "ASCII XmUGrid Version 1.1\n"
    "NUM_POINTS 30\n"
    "  POINT 0.0 0.0 0.0\n"
    "  POINT 10.0 0.0 0.0\n"
    "  POINT 20.0 0.0 0.0\n"
    "  POINT 30.0 0.0 0.0\n"
    "  POINT 40.0 0.0 0.0\n"
    "  POINT 0.0 10.0 0.0\n"
    "  POINT 10.0 10.0 0.0\n"
    "  POINT 20.0 10.0 0.0\n"
    "  POINT 30.0 10.0 0.0\n"
    "  POINT 40.0 10.0 0.0\n"
    "  POINT 0.0 20.0 0.0\n"
    "  POINT 10.0 20.0 0.0\n"
    "  POINT 20.0 20.0 0.0\n"
    "  POINT 30.0 20.0 0.0\n"
    "  POINT 40.0 20.0 0.0\n"
    "  POINT 0.0 0.0 10.0\n"
    "  POINT 10.0 0.0 10.0\n"
    "  POINT 20.0 0.0 10.0\n"
    "  POINT 30.0 0.0 10.0\n"
    "  POINT 40.0 0.0 10.0\n"
    "  POINT 0.0 10.0 10.0\n"
    "  POINT 10.0 10.0 10.0\n"
    "  POINT 20.0 10.0 10.0\n"
    "  POINT 30.0 10.0 10.0\n"
    "  POINT 40.0 10.0 10.0\n"
    "  POINT 0.0 20.0 10.0\n"
    "  POINT 10.0 20.0 10.0\n"
    "  POINT 20.0 20.0 10.0\n"
    "  POINT 30.0 20.0 10.0\n"
    "  POINT 40.0 20.0 10.0\n"
    "NUM_CELL_ITEMS 73\n"
    "  CELL TETRA 4 0 1 5 15\n"
    "  CELL VOXEL 8 1 2 6 7 16 17 21 22\n"
    "  CELL HEXAHEDRON 8 2 3 8 7 17 18 23 22\n"
    "  CELL POLYHEDRON 6\n"
    "    4 9 8 13 14\n"
    "    4 8 9 24 23\n"
    "    4 9 14 29 24\n"
    "    4 14 13 28 29\n"
    "    4 8 13 28 23\n"
    "    4 23 24 29 28\n"
    "  CELL WEDGE 6 3 4 18 8 9 23\n"
    "  CELL PYRAMID 5 5 6 11 10 20\n";
  std::string outputString = output.str();
  TS_ASSERT_EQUALS(outputBase, outputString);
} // XmUGridUtilsTests::testWriteLinear3dCells
//------------------------------------------------------------------------------
/// \brief Test reading an ASCII file for an empty UGrid.
//------------------------------------------------------------------------------
void XmUGridUtilsTests::testReadEmptyUGridAsciiFile()
{
  std::string inputText =
    "ASCII XmUGrid Version 1.1\n"
    "NUM_POINTS 0\n"
    "NUM_CELL_ITEMS 0\n";
  std::istringstream input;
  input.str(inputText);
  BSHP<XmUGrid> ugrid = XmReadUGridFromStream(input);
  if (!ugrid)
    TS_FAIL("Failed to read UGrid.");

  TS_ASSERT(ugrid->GetLocations().empty());
  TS_ASSERT(ugrid->GetCellstream().empty());
} // XmUGridReaderTests::testReadEmptyUGridAsciiFile
//------------------------------------------------------------------------------
/// \brief Test reading an ASCII file for a single triangle UGrid.
//------------------------------------------------------------------------------
void XmUGridUtilsTests::testReadBasicUGrid()
{
  std::string inputText =
    "ASCII XmUGrid Version 1.1\n"
    "NUM_POINTS 3\n"
    "  POINT 0.0 0.0 0.0\n"
    "  POINT 20.0 0.0 0.0\n"
    "  POINT 0.0 20.0 0.0\n"
    "NUM_CELL_ITEMS 5\n"
    "  CELL TRIANGLE 3 0 1 2\n";
  std::istringstream input;
  input.str(inputText);
  BSHP<XmUGrid> ugrid = XmReadUGridFromStream(input);
  if (!ugrid)
    TS_FAIL("Failed to read UGrid.");

  BSHP<XmUGrid> ugridBase = TEST_XmUGrid1Left90Tri();
  TS_ASSERT_EQUALS(ugridBase->GetLocations(), ugrid->GetLocations());
  TS_ASSERT_EQUALS(ugridBase->GetCellstream(), ugrid->GetCellstream());
} // XmUGridUtilsTests::testReadBasicUGrid
//------------------------------------------------------------------------------
/// \brief Test reading an ASCII file for a single triangle UGrid.
//------------------------------------------------------------------------------
void XmUGridUtilsTests::testReadPolyhedronUGrid()
{
  std::string inputText =
    "ASCII XmUGrid Version 1.1\n"
    "NUM_POINTS 8\n"
    "  POINT 0.0 0.0 10.0\n"
    "  POINT 10.0 0.0 10.0\n"
    "  POINT 10.0 10.0 10.0\n"
    "  POINT 0.0 10.0 10.0\n"
    "  POINT 0.0 0.0 0.0\n"
    "  POINT 10.0 0.0 0.0\n"
    "  POINT 10.0 10.0 0.0\n"
    "  POINT 0.0 10.0 0.0\n"
    "NUM_CELL_ITEMS 32\n"
    "  CELL POLYHEDRON 6\n"
    "    4 0 1 2 3\n"
    "    4 4 5 7 2\n"
    "    4 5 6 2 1\n"
    "    4 6 7 3 2\n"
    "    4 7 4 0 3\n"
    "    4 4 7 6 5\n";
  std::istringstream input;
  input.str(inputText);
  BSHP<XmUGrid> ugrid = XmReadUGridFromStream(input);
  if (!ugrid)
    TS_FAIL("Failed to read UGrid.");

  BSHP<XmUGrid> ugridBase = TEST_XmUGridHexagonalPolyhedron();
  TS_ASSERT_EQUALS(ugridBase->GetLocations(), ugrid->GetLocations());
  TS_ASSERT_EQUALS(ugridBase->GetCellstream(), ugrid->GetCellstream());
} // XmUGridUtilsTests::testReadPolyhedronUGrid
//------------------------------------------------------------------------------
/// \brief Test reading an ASCII file for a single triangle UGrid.
//------------------------------------------------------------------------------
void XmUGridUtilsTests::testLinear2dWriteThenRead()
{
  BSHP<XmUGrid> ugridBase = TEST_XmUGrid2dLinear();

  // write
  std::ostringstream output;
  XmWriteUGridToStream(ugridBase, output);

  // read
  std::istringstream input;
  input.str(output.str());
  BSHP<XmUGrid> ugridOut = XmReadUGridFromStream(input);

  TS_ASSERT_EQUALS(ugridBase->GetLocations(), ugridOut->GetLocations());
  TS_ASSERT_EQUALS(ugridBase->GetCellstream(), ugridOut->GetCellstream());
} // XmUGridUtilsTests::testLinear2dWriteThenRead
//------------------------------------------------------------------------------
/// \brief Test reading an ASCII file for a single triangle UGrid.
//------------------------------------------------------------------------------
void XmUGridUtilsTests::testLinear3dWriteThenRead()
{
  BSHP<XmUGrid> ugridBase = TEST_XmUGrid3dLinear();

  // write
  std::ostringstream output;
  XmWriteUGridToStream(ugridBase, output);

  // read
  std::istringstream input;
  input.str(output.str());
  BSHP<XmUGrid> ugridOut = XmReadUGridFromStream(input);

  TS_ASSERT_EQUALS(ugridBase->GetLocations(), ugridOut->GetLocations());
  TS_ASSERT_EQUALS(ugridBase->GetCellstream(), ugridOut->GetCellstream());
} // XmUGridUtilsTests::testLinear3dWriteThenRead
//------------------------------------------------------------------------------
/// \brief Test reading from file.
//------------------------------------------------------------------------------
void XmUGridUtilsTests::testWriteThenReadUGridFile()
{
  BSHP<XmUGrid> ugridBase = TEST_XmUGrid3dLinear();

  // write
  std::string outFileName(TestFilesPath() + "3d_grid_linear.xmugrid");
  std::ofstream output(outFileName);
  XmWriteUGridToStream(ugridBase, output);
  output.close();

  // read
  std::ifstream input(TestFilesPath() + "3d_grid_linear.xmugrid");
  BSHP<XmUGrid> ugridOut = XmReadUGridFromStream(input);
  input.close();
  if (!ugridOut)
  {
    TS_FAIL("Unable to read ugrid.");
    return;
  }

  TS_ASSERT_EQUALS(ugridBase->GetLocations(), ugridOut->GetLocations());
  TS_ASSERT_EQUALS(ugridBase->GetCellstream(), ugridOut->GetCellstream());
} // XmUGridUtilsTests::testWriteThenReadUGridFile
//! [snip_test_WriteReadAscii]
//------------------------------------------------------------------------------
/// \brief Test reading from file.
//------------------------------------------------------------------------------
void XmUGridUtilsTests::testWriteThenReadUGridFileToAscii()
{
  BSHP<XmUGrid> ugridBase = TEST_XmUGrid3dLinear();

  // write
  std::string outFileName(TestFilesPath() + "3d_grid_linear.xmugrid");
  XmWriteUGridToAsciiFile(ugridBase, outFileName);

  // read
  std::string input(TestFilesPath() + "3d_grid_linear.xmugrid");
  BSHP<XmUGrid> ugridOut = XmReadUGridFromAsciiFile(input);
  if (!ugridOut)
  {
    TS_FAIL("Unable to read ugrid.");
    return;
  }

  TS_ASSERT_EQUALS(ugridBase->GetLocations(), ugridOut->GetLocations());
  TS_ASSERT_EQUALS(ugridBase->GetCellstream(), ugridOut->GetCellstream());
} // XmUGridUtilsTests::testWriteThenReadUGridFile
//! [snip_test_WriteReadAscii]
//------------------------------------------------------------------------------
/// \biref
//------------------------------------------------------------------------------
void XmUGridUtilsTests::testReadVersion1Dot0File()
{
  std::string inputText =
    "ASCII XmUGrid Version 1.0\n"
    "NUM_POINTS 8\n"
    "  POINT 0.0 0.0 10.0\n"
    "  POINT 10.0 0.0 10.0\n"
    "  POINT 10.0 10.0 10.0\n"
    "  POINT 0.0 10.0 10.0\n"
    "  POINT 0.0 0.0 0.0\n"
    "  POINT 10.0 0.0 0.0\n"
    "  POINT 10.0 10.0 0.0\n"
    "  POINT 0.0 10.0 0.0\n"
    "NUM_CELL_ITEMS 32\n"
    "  CELL 42 6\n" // Type 42 is a POLYHEDRON
    "    4 0 1 2 3\n"
    "    4 4 5 7 2\n"
    "    4 5 6 2 1\n"
    "    4 6 7 3 2\n"
    "    4 7 4 0 3\n"
    "    4 4 7 6 5\n";
  std::istringstream input;
  input.str(inputText);
  BSHP<XmUGrid> ugrid = XmReadUGridFromStream(input);
  if (!ugrid)
    TS_FAIL("Failed to read UGrid.");

  BSHP<XmUGrid> ugridBase = TEST_XmUGridHexagonalPolyhedron();
  TS_ASSERT_EQUALS(ugridBase->GetLocations(), ugrid->GetLocations());
  TS_ASSERT_EQUALS(ugridBase->GetCellstream(), ugrid->GetCellstream());
} // XmUGridUtilsTests::testReadVersion1Dot0File

#endif
