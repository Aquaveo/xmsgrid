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

// 5. Shared code headers
#include <xmscore/misc/StringUtil.h>
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
//------------------------------------------------------------------------------
/// \brief Save an XmUGrid ASCII text to output stream.
/// \param[in] a_ugrid: the UGrid to save
/// \param[in] a_outStream: the stream to write
//------------------------------------------------------------------------------
void iWriteUGridToAsciiFile(BSHP<XmUGrid> a_ugrid, std::ostream& a_outStream)
{
  a_outStream << "ASCII XmUGrid Version 1.0\n";

  // number of points
  const VecPt3d& points = a_ugrid->GetLocations();
  a_outStream << "NUM_POINTS " << points.size() << "\n";

  // points
  for (size_t i = 0; i < points.size(); ++i)
  {
    const Pt3d& p = points[i];
    a_outStream << "  POINT " << STRstd(p.x) << " " << STRstd(p.y) << " " << STRstd(p.z) << "\n";
  }

  // number of cell stream items
  const VecInt& cellstream = a_ugrid->GetCellStream();
  int cellstreamSize = (int)cellstream.size();
  a_outStream << "NUM_CELL_ITEMS " << cellstreamSize << "\n";

  // cells
  int currIdx = 0;
  while (currIdx < cellstreamSize)
  {
    int cellType = cellstream[currIdx++];
    int numItems = cellstream[currIdx++];
    a_outStream << "  CELL " << cellType;
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
} // iWriteUGridToAsciiFile
//------------------------------------------------------------------------------
/// \brief Read an XmUGrid from ASCII text from an input stream.
/// \param[in] a_inStream: the stream to read
/// \return the UGrid
//------------------------------------------------------------------------------
BSHP<XmUGrid> iReadUGridFromAsciiFile(std::istream& a_inStream)
{
  if (a_inStream.eof())
  {
    return nullptr;
  }

  std::string line;
  std::getline(a_inStream, line);
  if (line != "ASCII XmUGrid Version 1.0")
  {
    XM_LOG(xmlog::error, "Unsupported file version or file type: " + line);
    return nullptr;
  }

  std::string cardName;
  VecPt3d points;
  VecInt cells;
  while (!a_inStream.eof())
  {
    cardName = "";
    a_inStream >> cardName;
    if (cardName == "NUM_POINTS")
    {
      int numPoints;
      a_inStream >> numPoints;
      points.reserve(numPoints);
    }
    else if (cardName == "POINT")
    {
      Pt3d pt;
      a_inStream >> pt.x >> pt.y >> pt.z;
      points.push_back(pt);
    }
    else if (cardName == "NUM_CELL_ITEMS")
    {
      int numCellItems;
      a_inStream >> numCellItems;
      cells.reserve(numCellItems);
    }
    else if (cardName == "CELL")
    {
      int cellType;
      a_inStream >> cellType;
      cells.push_back(cellType);
      if (cellType == XMU_POLYHEDRON)
      {
        int numFaces;
        a_inStream >> numFaces;
        cells.push_back(numFaces);
        for (int faceIdx = 0; faceIdx < numFaces; ++faceIdx)
        {
          int numPoints;
          a_inStream >> numPoints;
          cells.push_back(numPoints);
          for (int i = 0; i < numPoints; ++i)
          {
            int ptIdx;
            a_inStream >> ptIdx;
            cells.push_back(ptIdx);
          }
        }
      }
      else
      {
        int numPoints;
        a_inStream >> numPoints;
        cells.push_back(numPoints);
        for (int i = 0; i < numPoints; ++i)
        {
          int ptIdx;
          a_inStream >> ptIdx;
          cells.push_back(ptIdx);
        }
      }
    }
  }

  BSHP<XmUGrid> ugrid = XmUGrid::New(points, cells);
  return ugrid;
} // iReadUGridFromAsciiFile

} // namespace

//------------------------------------------------------------------------------
/// \brief Read XmUGrid from an ASCII file.
/// \param[in] a_filePath: filename to read including path, file name, and
/// extension
/// \return the UGrid that was read from the file
//------------------------------------------------------------------------------
BSHP<XmUGrid> XmReadUGridFromAsciiFile(const std::string& a_filePath)
{
  std::ifstream inFile(a_filePath);
  return iReadUGridFromAsciiFile(inFile);
} // XmReadUGridFromAsciiFile
//------------------------------------------------------------------------------
/// \brief Write an XmUGrid to an ASCII file.
/// \param[in] a_ugrid: The UGrid to write to the file
/// \param[in] a_filePath: filename to write including path, file name, and
/// extension
//------------------------------------------------------------------------------
void XmWriteUGridToAsciiFile(BSHP<XmUGrid> a_ugrid, const std::string& a_filePath)
{
  std::ofstream outFile(a_filePath);
  iWriteUGridToAsciiFile(a_ugrid, outFile);
} // XmWriteUGridToAsciiFile

//------------------------------------------------------------------------------
/// \brief 2D cross product of two points
/// \param[in] a_origin: origin point for the "vectors"
/// \param[in] a_A: first vector
/// \param[in] a_B: second vector
/// \return the cross product
//------------------------------------------------------------------------------
double cross(const Pt3d& a_origin, const Pt3d& a_A, const Pt3d& a_B)
{
  return (a_A.x - a_origin.x) * (a_B.y - a_origin.y) - (a_A.y - a_origin.y) * (a_B.x - a_origin.x);
} // cross
//------------------------------------------------------------------------------
/// \brief Determine whether 2 line segments intersect
/// \param[in] a_segment1: The first line segment
/// \param[in] a_segment2: The second line segment
/// \return true if the line segments intersect
//------------------------------------------------------------------------------
bool DoLineSegmentsCross(const std::pair<Pt3d, Pt3d>& a_segment1,
                         const std::pair<Pt3d, Pt3d>& a_segment2)
{
  return DoLineSegmentsCross(a_segment1.first, a_segment1.second, a_segment2.first,
                             a_segment2.second);
} // DoLineSegmentsCross

//------------------------------------------------------------------------------
/// \brief Determine whether 2 line segments cross
/// \param[in] a_segment1Point1: First point 3d of line segment 1
/// \param[in] a_segment1Point2: Second point 3d of line segment 1
/// \param[in] a_segment2Point1: First point 3d of line segment 2
/// \param[in] a_segment2Point2: Second point 3d of line segment 2
/// \return true if the line segments cross
//------------------------------------------------------------------------------
bool DoLineSegmentsCross(const Pt3d& a_segment1Point1,
                         const Pt3d& a_segment1Point2,
                         const Pt3d& a_segment2Point1,
                         const Pt3d& a_segment2Point2)
{
  // Boundary case checks
  // Any of the points from line segment 1 are the same as any points from line segment 2
  if ((a_segment1Point1 == a_segment2Point1 || a_segment1Point1 == a_segment2Point2) &&
      (a_segment1Point2 == a_segment2Point1 || a_segment1Point2 == a_segment2Point2))
    return true;

  // The segments AB and CD intersect if and only if both of the following are true:
  //
  // A and B lie on different sides of the line through C and D
  // C and D lie on different sides of the line through A and B
  // These two conditions can be tested for using the notion of a scalar cross product(formulas
  // below).

  // is true if and only if the scalar cross products CA->�CD-> and CB->�CD-> have opposite signs.
  // is true if and only if the scalar cross products AC->�AB-> and AD->�AB-> have opposite signs.

  // Conclusion: the line segments intersect if and only if both are negative
  double result1 = cross(a_segment2Point1, a_segment1Point1, a_segment2Point2);
  double result2 = cross(a_segment2Point1, a_segment1Point2, a_segment2Point2);
  double result3 = cross(a_segment1Point1, a_segment2Point1, a_segment1Point2);
  double result4 = cross(a_segment2Point1, a_segment2Point2, a_segment1Point2);

  return (result1 * result2 < 0 && result3 * result4 < 0);

} // DoLineSegmentsCross
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
/// \brief Test determining if two lines intersect
//------------------------------------------------------------------------------
void XmUGridUtilsTests::testDoLineSegmentsCross()
{
  // Test 1 Segments do not intersect
  {
    Pt3d point1(1, 2);
    Pt3d point2(1, 4);
    Pt3d point3(2, 1);
    Pt3d point4(4, 1);
    std::pair<Pt3d, Pt3d> segment1;
    std::pair<Pt3d, Pt3d> segment2;
    segment1.first = point1;
    segment1.second = point2;
    segment2.first = point3;
    segment2.second = point4;
    bool expected = false;
    TS_ASSERT_EQUALS(expected, DoLineSegmentsCross(point1, point2, point3, point4));
    TS_ASSERT_EQUALS(expected, DoLineSegmentsCross(segment1, segment2));
  }
  // Test 2 Segments that do intersect (generic)
  {
    Pt3d point1(2, 2);
    Pt3d point2(4, 4);
    Pt3d point3(2, 4);
    Pt3d point4(4, 2);
    std::pair<Pt3d, Pt3d> segment1;
    std::pair<Pt3d, Pt3d> segment2;
    segment1.first = point1;
    segment1.second = point2;
    segment2.first = point3;
    segment2.second = point4;
    bool expected = true;
    TS_ASSERT_EQUALS(expected, DoLineSegmentsCross(point1, point2, point3, point4));
    TS_ASSERT_EQUALS(expected, DoLineSegmentsCross(segment1, segment2));
  }
  // Test 3 Colinear
  {
    Pt3d point1(1, 5);
    Pt3d point2(1, 8);
    Pt3d point3(1, 5);
    Pt3d point4(1, 8);
    std::pair<Pt3d, Pt3d> segment1;
    std::pair<Pt3d, Pt3d> segment2;
    segment1.first = point1;
    segment1.second = point2;
    segment2.first = point3;
    segment2.second = point4;
    bool expected = true;
    TS_ASSERT_EQUALS(expected, DoLineSegmentsCross(point1, point2, point3, point4));
    TS_ASSERT_EQUALS(expected, DoLineSegmentsCross(segment1, segment2));
  }
  // Test 4 T intersection (false because it does not cross)
  {
    Pt3d point1(6, 2);
    Pt3d point2(6, 4);
    Pt3d point3(5, 4);
    Pt3d point4(7, 4);
    std::pair<Pt3d, Pt3d> segment1;
    std::pair<Pt3d, Pt3d> segment2;
    segment1.first = point1;
    segment1.second = point2;
    segment2.first = point3;
    segment2.second = point4;
    bool expected = false;
    TS_ASSERT_EQUALS(expected, DoLineSegmentsCross(point1, point2, point3, point4));
    TS_ASSERT_EQUALS(expected, DoLineSegmentsCross(segment1, segment2));
  }
  // Test 5 L intersection (which is allowed for valid shapes, so return false)
  {
    Pt3d point1(2, 5);
    Pt3d point2(2, 8);
    Pt3d point3(2, 8);
    Pt3d point4(4, 8);
    std::pair<Pt3d, Pt3d> segment1;
    std::pair<Pt3d, Pt3d> segment2;
    segment1.first = point1;
    segment1.second = point2;
    segment2.first = point3;
    segment2.second = point4;
    bool expected = false;
    TS_ASSERT_EQUALS(expected, DoLineSegmentsCross(point1, point2, point3, point4));
    TS_ASSERT_EQUALS(expected, DoLineSegmentsCross(segment1, segment2));
  }
  // Test 6 Near miss
  {
    Pt3d point1(5, 5);
    Pt3d point2(7, 5);
    Pt3d point3(5, 6);
    Pt3d point4(5, 8);
    std::pair<Pt3d, Pt3d> segment1;
    std::pair<Pt3d, Pt3d> segment2;
    segment1.first = point1;
    segment1.second = point2;
    segment2.first = point3;
    segment2.second = point4;
    bool expected = false;
    TS_ASSERT_EQUALS(expected, DoLineSegmentsCross(point1, point2, point3, point4));
    TS_ASSERT_EQUALS(expected, DoLineSegmentsCross(segment1, segment2));
  }
} // XmUGridUtilsTests::testDoLineSegmentsCross
//------------------------------------------------------------------------------
/// \brief Test writing an ASCII file for an empty UGrid.
//------------------------------------------------------------------------------
void XmUGridUtilsTests::testWriteEmptyUGrid()
{
  BSHP<XmUGrid> ugrid = XmUGrid::New();
  std::ostringstream output;
  iWriteUGridToAsciiFile(ugrid, output);

  std::string outputBase =
    "ASCII XmUGrid Version 1.0\n"
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
  iWriteUGridToAsciiFile(ugrid, output);

  std::string outputBase =
    "ASCII XmUGrid Version 1.0\n"
    "NUM_POINTS 3\n"
    "  POINT 0.0 0.0 0.0\n"
    "  POINT 20.0 0.0 0.0\n"
    "  POINT 0.0 20.0 0.0\n"
    //"NUM_CELLS 1\n"
    "NUM_CELL_ITEMS 5\n"
    "  CELL 5 3 0 1 2\n";
  TS_ASSERT_EQUALS(outputBase, output.str());
} // XmUGridUtilsTests::testWriteBasicUGrid
//------------------------------------------------------------------------------
/// \brief Test writing an ASCII file for a single polyhedron UGrid.
//------------------------------------------------------------------------------
void XmUGridUtilsTests::testWritePolyhedronUGrid()
{
  BSHP<XmUGrid> ugrid = TEST_XmUGridHexagonalPolyhedron();
  std::ostringstream output;
  iWriteUGridToAsciiFile(ugrid, output);

  std::string outputBase =
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
    //"NUM_CELLS 1\n"
    "NUM_CELL_ITEMS 32\n"
    "  CELL 42 6\n"
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
  iWriteUGridToAsciiFile(ugrid, output);

  std::string outputBase =
    "ASCII XmUGrid Version 1.0\n"
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
    "  CELL 9 4 0 1 6 5\n"
    "  CELL 8 4 1 2 6 7\n"
    "  CELL 5 3 2 3 7\n"
    "  CELL 7 6 3 4 8 13 12 7\n"
    "  CELL 4 3 7 11 10\n"
    "  CELL 3 2 5 9\n";
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
  iWriteUGridToAsciiFile(ugrid, output);

  std::string outputBase =
    "ASCII XmUGrid Version 1.0\n"
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
    "  CELL 10 4 0 1 5 15\n"
    "  CELL 11 8 1 2 6 7 16 17 21 22\n"
    "  CELL 12 8 2 3 8 7 17 18 23 22\n"
    "  CELL 42 6\n"
    "    4 9 8 13 14\n"
    "    4 8 9 24 23\n"
    "    4 9 14 29 24\n"
    "    4 14 13 28 29\n"
    "    4 8 13 28 23\n"
    "    4 23 24 29 28\n"
    "  CELL 13 6 3 4 18 8 9 23\n"
    "  CELL 14 5 5 6 11 10 20\n";
  TS_ASSERT_EQUALS(outputBase, output.str());
} // XmUGridUtilsTests::testWriteLinear3dCells
//------------------------------------------------------------------------------
/// \brief Test reading an ASCII file for an empty UGrid.
//------------------------------------------------------------------------------
void XmUGridUtilsTests::testReadEmptyUGridAsciiFile()
{
  std::string inputText =
    "ASCII XmUGrid Version 1.0\n"
    "NUM_POINTS 0\n"
    "NUM_CELL_ITEMS 0\n";
  std::istringstream input;
  input.str(inputText);
  BSHP<XmUGrid> ugrid = iReadUGridFromAsciiFile(input);
  if (!ugrid)
    TS_FAIL("Failed to read UGrid.");

  TS_ASSERT(ugrid->GetLocations().empty());
  TS_ASSERT(ugrid->GetCellStream().empty());
} // XmUGridReaderTests::testReadEmptyUGridAsciiFile
//------------------------------------------------------------------------------
/// \brief Test reading an ASCII file for a single triangle UGrid.
//------------------------------------------------------------------------------
void XmUGridUtilsTests::testReadBasicUGrid()
{
  std::string inputText =
    "ASCII XmUGrid Version 1.0\n"
    "NUM_POINTS 3\n"
    "  POINT 0.0 0.0 0.0\n"
    "  POINT 20.0 0.0 0.0\n"
    "  POINT 0.0 20.0 0.0\n"
    //"NUM_CELLS 1\n"
    "NUM_CELL_ITEMS 5\n"
    "  CELL 5 3 0 1 2\n";
  std::istringstream input;
  input.str(inputText);
  BSHP<XmUGrid> ugrid = iReadUGridFromAsciiFile(input);
  if (!ugrid)
    TS_FAIL("Failed to read UGrid.");

  BSHP<XmUGrid> ugridBase = TEST_XmUGrid1Left90Tri();
  TS_ASSERT_EQUALS(ugridBase->GetLocations(), ugrid->GetLocations());
  TS_ASSERT_EQUALS(ugridBase->GetCellStream(), ugrid->GetCellStream());
} // XmUGridUtilsTests::testReadBasicUGrid
//------------------------------------------------------------------------------
/// \brief Test reading an ASCII file for a single triangle UGrid.
//------------------------------------------------------------------------------
void XmUGridUtilsTests::testReadPolyhedronUGrid()
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
    //"NUM_CELLS 1\n"
    "NUM_CELL_ITEMS 32\n"
    "  CELL 42 6\n"
    "    4 0 1 2 3\n"
    "    4 4 5 7 2\n"
    "    4 5 6 2 1\n"
    "    4 6 7 3 2\n"
    "    4 7 4 0 3\n"
    "    4 4 7 6 5\n";
  std::istringstream input;
  input.str(inputText);
  BSHP<XmUGrid> ugrid = iReadUGridFromAsciiFile(input);
  if (!ugrid)
    TS_FAIL("Failed to read UGrid.");

  BSHP<XmUGrid> ugridBase = TEST_XmUGridHexagonalPolyhedron();
  TS_ASSERT_EQUALS(ugridBase->GetLocations(), ugrid->GetLocations());
  TS_ASSERT_EQUALS(ugridBase->GetCellStream(), ugrid->GetCellStream());
} // XmUGridUtilsTests::testReadPolyhedronUGrid
//------------------------------------------------------------------------------
/// \brief Test reading an ASCII file for a single triangle UGrid.
//------------------------------------------------------------------------------
void XmUGridUtilsTests::testLinear2dWriteThenRead()
{
  BSHP<XmUGrid> ugridBase = TEST_XmUGrid2dLinear();

  // write
  std::ostringstream output;
  iWriteUGridToAsciiFile(ugridBase, output);

  // read
  std::istringstream input;
  input.str(output.str());
  BSHP<XmUGrid> ugridOut = iReadUGridFromAsciiFile(input);

  TS_ASSERT_EQUALS(ugridBase->GetLocations(), ugridOut->GetLocations());
  TS_ASSERT_EQUALS(ugridBase->GetCellStream(), ugridOut->GetCellStream());
} // XmUGridUtilsTests::testLinear2dWriteThenRead
//------------------------------------------------------------------------------
/// \brief Test reading an ASCII file for a single triangle UGrid.
//------------------------------------------------------------------------------
void XmUGridUtilsTests::testLinear3dWriteThenRead()
{
  BSHP<XmUGrid> ugridBase = TEST_XmUGrid3dLinear();

  // write
  std::ostringstream output;
  iWriteUGridToAsciiFile(ugridBase, output);

  // read
  std::istringstream input;
  input.str(output.str());
  BSHP<XmUGrid> ugridOut = iReadUGridFromAsciiFile(input);

  TS_ASSERT_EQUALS(ugridBase->GetLocations(), ugridOut->GetLocations());
  TS_ASSERT_EQUALS(ugridBase->GetCellStream(), ugridOut->GetCellStream());
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
  iWriteUGridToAsciiFile(ugridBase, output);
  output.close();

  // read
  std::ifstream input(TestFilesPath() + "3d_grid_linear.xmugrid");
  BSHP<XmUGrid> ugridOut = iReadUGridFromAsciiFile(input);
  input.close();
  if (!ugridOut)
  {
    TS_FAIL("Unable to read ugrid.");
    return;
  }

  TS_ASSERT_EQUALS(ugridBase->GetLocations(), ugridOut->GetLocations());
  TS_ASSERT_EQUALS(ugridBase->GetCellStream(), ugridOut->GetCellStream());
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
  TS_ASSERT_EQUALS(ugridBase->GetCellStream(), ugridOut->GetCellStream());
} // XmUGridUtilsTests::testWriteThenReadUGridFile
  //! [snip_test_WriteReadAscii]

#endif
