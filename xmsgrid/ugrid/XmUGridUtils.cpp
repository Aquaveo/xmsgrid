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

// 6. Non-shared code headers
#include <xmsgrid/dataio/daStreamIo.h>
#include <xmsgrid/ugrid/detail/XmUGridIo.h>
#include <xmsgrid/ugrid/XmUGrid.h>

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

class XmUGridReaderVersion2 : public XmUGridReader
{
public:
  explicit XmUGridReaderVersion2(DaStreamReader& a_reader);
  bool ReadLocations(VecPt3d& a_locations) final;
  bool ReadCellstream(VecInt& a_cellstream) final;
  bool ReadIntArrays(IntArrays& a_intArrays) final;

private:
  DaStreamReader& m_reader;
};

class XmUGridWriterVersion2 : public XmUGridWriter
{
public:
  explicit XmUGridWriterVersion2(DaStreamWriter& a_writer);
  bool WriteLocations(const VecPt3d& a_locations) final;
  bool WriteCellstream(const VecInt& a_cellstream) final;
  bool WriteIntArrays(ConstIntArrays& a_intArrays) final;

private:
  DaStreamWriter& m_writer;
};

//------------------------------------------------------------------------------
/// \brief Get a bi-map from a cell type string to a cell type integer.
/// \return The bi-map from a cell type string to a cell type integer.
//------------------------------------------------------------------------------
const CellNameToType& iCellTypeStringIntPair()
{
  static CellNameToType cellNameToInt;
  if (cellNameToInt.empty())
  {
    // clang-format off
    cellNameToInt.insert(CellNameToType::value_type("INVALID_CELL_TYPE", XMU_INVALID_CELL_TYPE));
    cellNameToInt.insert(CellNameToType::value_type("EMPTY_CELL", XMU_EMPTY_CELL));
    cellNameToInt.insert(CellNameToType::value_type("VERTEX", XMU_VERTEX));
    cellNameToInt.insert(CellNameToType::value_type("POLY_VERTEX", XMU_POLY_VERTEX));
    cellNameToInt.insert(CellNameToType::value_type("LINE", XMU_LINE));
    cellNameToInt.insert(CellNameToType::value_type("POLY_LINE", XMU_POLY_LINE));
    cellNameToInt.insert(CellNameToType::value_type("TRIANGLE", XMU_TRIANGLE));
    cellNameToInt.insert(CellNameToType::value_type("TRIANGLE_STRIP", XMU_TRIANGLE_STRIP));
    cellNameToInt.insert(CellNameToType::value_type("POLYGON", XMU_POLYGON));
    cellNameToInt.insert(CellNameToType::value_type("PIXEL", XMU_PIXEL));
    cellNameToInt.insert(CellNameToType::value_type("QUAD", XMU_QUAD));
    cellNameToInt.insert(CellNameToType::value_type("TETRA", XMU_TETRA));
    cellNameToInt.insert(CellNameToType::value_type("VOXEL", XMU_VOXEL));
    cellNameToInt.insert(CellNameToType::value_type("HEXAHEDRON", XMU_HEXAHEDRON));
    cellNameToInt.insert(CellNameToType::value_type("WEDGE", XMU_WEDGE));
    cellNameToInt.insert(CellNameToType::value_type("PYRAMID", XMU_PYRAMID));
    cellNameToInt.insert(CellNameToType::value_type("PENTAGONAL_PRISM", XMU_PENTAGONAL_PRISM));
    cellNameToInt.insert(CellNameToType::value_type("HEXAGONAL_PRISM", XMU_HEXAGONAL_PRISM));
    cellNameToInt.insert(CellNameToType::value_type("QUADRATIC_EDGE", XMU_QUADRATIC_EDGE));
    cellNameToInt.insert(CellNameToType::value_type("QUADRATIC_TRIANGLE", XMU_QUADRATIC_TRIANGLE));
    cellNameToInt.insert(CellNameToType::value_type("QUADRATIC_QUAD", XMU_QUADRATIC_QUAD));
    cellNameToInt.insert(CellNameToType::value_type("QUADRATIC_POLYGON", XMU_QUADRATIC_POLYGON));
    cellNameToInt.insert(CellNameToType::value_type("QUADRATIC_TETRA", XMU_QUADRATIC_TETRA));
    cellNameToInt.insert(CellNameToType::value_type("QUADRATIC_HEXAHEDRON", XMU_QUADRATIC_HEXAHEDRON));
    cellNameToInt.insert(CellNameToType::value_type("QUADRATIC_WEDGE", XMU_QUADRATIC_WEDGE));
    cellNameToInt.insert(CellNameToType::value_type("QUADRATIC_PYRAMID", XMU_QUADRATIC_PYRAMID));
    cellNameToInt.insert(CellNameToType::value_type("BIQUADRATIC_QUAD", XMU_BIQUADRATIC_QUAD));
    cellNameToInt.insert(CellNameToType::value_type("TRIQUADRATIC_HEXAHEDRON", XMU_TRIQUADRATIC_HEXAHEDRON));
    cellNameToInt.insert(CellNameToType::value_type("QUADRATIC_LINEAR_QUAD", XMU_QUADRATIC_LINEAR_QUAD));
    cellNameToInt.insert(CellNameToType::value_type("QUADRATIC_LINEAR_WEDGE", XMU_QUADRATIC_LINEAR_WEDGE));
    cellNameToInt.insert(CellNameToType::value_type("BIQUADRATIC_QUADRATIC_WEDGE", XMU_BIQUADRATIC_QUADRATIC_WEDGE));
    cellNameToInt.insert(CellNameToType::value_type("BIQUADRATIC_QUADRATIC_HEXAHEDRON", XMU_BIQUADRATIC_QUADRATIC_HEXAHEDRON));
    cellNameToInt.insert(CellNameToType::value_type("BIQUADRATIC_TRIANGLE", XMU_BIQUADRATIC_TRIANGLE));
    cellNameToInt.insert(CellNameToType::value_type("CUBIC_LINE", XMU_CUBIC_LINE));
    cellNameToInt.insert(CellNameToType::value_type("CONVEX_POINT_SET", XMU_CONVEX_POINT_SET));
    cellNameToInt.insert(CellNameToType::value_type("POLYHEDRON", XMU_POLYHEDRON));
    cellNameToInt.insert(CellNameToType::value_type("PARAMETRIC_CURVE", XMU_PARAMETRIC_CURVE));
    cellNameToInt.insert(CellNameToType::value_type("PARAMETRIC_SURFACE", XMU_PARAMETRIC_SURFACE));
    cellNameToInt.insert(CellNameToType::value_type("PARAMETRIC_TRI_SURFACE", XMU_PARAMETRIC_TRI_SURFACE));
    cellNameToInt.insert(CellNameToType::value_type("PARAMETRIC_QUAD_SURFACE", XMU_PARAMETRIC_QUAD_SURFACE));
    cellNameToInt.insert(CellNameToType::value_type("PARAMETRIC_TETRA_REGION", XMU_PARAMETRIC_TETRA_REGION));
    cellNameToInt.insert(CellNameToType::value_type("PARAMETRIC_HEX_REGION", XMU_PARAMETRIC_HEX_REGION));
    cellNameToInt.insert(CellNameToType::value_type("HIGHER_ORDER_EDGE", XMU_HIGHER_ORDER_EDGE));
    cellNameToInt.insert(CellNameToType::value_type("HIGHER_ORDER_TRIANGLE", XMU_HIGHER_ORDER_TRIANGLE));
    cellNameToInt.insert(CellNameToType::value_type("HIGHER_ORDER_QUAD", XMU_HIGHER_ORDER_QUAD));
    cellNameToInt.insert(CellNameToType::value_type("HIGHER_ORDER_POLYGON", XMU_HIGHER_ORDER_POLYGON));
    cellNameToInt.insert(CellNameToType::value_type("HIGHER_ORDER_TETRAHEDRON", XMU_HIGHER_ORDER_TETRAHEDRON));
    cellNameToInt.insert(CellNameToType::value_type("HIGHER_ORDER_WEDGE", XMU_HIGHER_ORDER_WEDGE));
    cellNameToInt.insert(CellNameToType::value_type("HIGHER_ORDER_PYRAMID", XMU_HIGHER_ORDER_PYRAMID));
    cellNameToInt.insert(CellNameToType::value_type("HIGHER_ORDER_HEXAHEDRON", XMU_HIGHER_ORDER_HEXAHEDRON));
    // clang-format on
    std::cout << '\n';
  }

  return cellNameToInt;
} // iCellTypeStringIntPair

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

//------------------------------------------------------------------------------
/// \brief Read points for version 1 XmUGrid file.
/// \param a_inStream The stream to read from.
/// \param locations The read locations.
/// \return True on success.
//------------------------------------------------------------------------------
bool iReadPointsVersion1(DaStreamReader& a_reader, VecPt3d& locations)
{
  int pointCount;
  if (!a_reader.ReadIntLine("NUM_POINTS", pointCount))
  {
    XM_LOG(xmlog::error, "Unable to read XmUGrid point count.");
    return false;
  }

  locations.reserve(pointCount);
  for (int pointIdx = 0; pointIdx < pointCount; ++pointIdx)
  {
    Pt3d point;
    if (a_reader.Read3DoubleLine("POINT", point.x, point.y, point.z))
    {
      locations.push_back(point);
    }
    else
    {
      XM_LOG(xmlog::error, "Unable to read XmUGrid point.");
      return false;
    }
  }

  return true;
} // iReadPointsVersion1

//------------------------------------------------------------------------------
/// \brief Read a line for cell stream size for an XmUGrid file.
/// \param a_inStream The stream to read from.
/// \param cellStreamSize The number of values in the cell stream.
/// \return True on success.
//------------------------------------------------------------------------------
bool iReadCellStreamSizeVersion1(DaStreamReader& a_reader, int& cellStreamSize)
{
  if (!a_reader.ReadIntLine("NUM_CELL_ITEMS", cellStreamSize))
  {
    XM_LOG(xmlog::error, "Unable to read XmUGrid cells.");
    return false;
  }
  return true;
} // iReadCellStreamSizeVersion1

//------------------------------------------------------------------------------
/// \brief Read a line for cell stream size for an XmUGrid file.
/// \param a_inStream The stream to read from.
/// \param cellStreamSize The number of values in the cell stream.
/// \return True on success.
//------------------------------------------------------------------------------
bool iReadCellStreamSizeVersion2(DaStreamReader& a_reader, int& cellStreamSize)
{
  if (!a_reader.ReadIntLine("CELL_STREAM", cellStreamSize))
  {
    XM_LOG(xmlog::error, "Unable to read XmUGrid cells.");
    return false;
  }
  return true;
} // iReadCellStreamSizeVersion1

//------------------------------------------------------------------------------
/// \brief Read line contents for a version 1 "CELL" line.
/// \param a_inStream The stream to read from.
/// \param a_cellLine The line to read from.
/// \param a_cellType The cell type.
/// \return True on success.
//------------------------------------------------------------------------------
bool iReadCellLineVersion1(DaStreamReader& a_reader, std::string& a_cellLine, int& a_cellType)
{
  a_cellType = XMU_INVALID_CELL_TYPE;
  std::string cellTypeString;
  if (daReadIntFromLine(a_cellLine, a_cellType))
  {
    cellTypeString = iStringFromCellType(a_cellType);
    if (cellTypeString.empty())
      a_cellType = XMU_INVALID_CELL_TYPE;
  }
  else
  {
    a_cellType = XMU_INVALID_CELL_TYPE;
  }

  if (a_cellType == XMU_INVALID_CELL_TYPE)
  {
    XM_LOG(xmlog::error, "Found invalid cell type.");
    return false;
  }
  return true;
} // iReadCellLineVersion1

//------------------------------------------------------------------------------
/// \brief Read line contents for a version 2 "CELL" line.
/// \param a_inStream The stream to read from.
/// \param a_cellIdx The zero based index of the cell to read.
/// \param a_cellType The cell type.
/// \return True on success.
//------------------------------------------------------------------------------
bool iReadCellLineVersion2(DaStreamReader& a_reader,
                           int a_cellIdx,
                           int& a_cellType)
{
  int readCellIdx = -1;
  if (!a_reader.ReadInt(readCellIdx) || readCellIdx != a_cellIdx)
  {
    XM_LOG(xmlog::error, "Unable to read cell line.");
    return false;
  }

  a_cellType = XMU_INVALID_CELL_TYPE;
  std::string cellTypeString;
  if (a_reader.ReadString(cellTypeString))
  {
    a_cellType = iCellTypeFromString(cellTypeString);
  }
  else
  {
    a_cellType = XMU_INVALID_CELL_TYPE;
  }

  if (a_cellType == XMU_INVALID_CELL_TYPE)
  {
    XM_LOG(xmlog::error, "Found invalid cell type.");
    return false;
  }

  return true;
} // iReadCellLineVersion2

//------------------------------------------------------------------------------
/// \brief
/// \param a_inStream The stream to read from.
/// \param a_cellLine The line to read from.
/// \param a_cellType The cell type.
/// \param a_cellstream The output cell stream.
/// \return True on success.
//------------------------------------------------------------------------------
bool iReadCellStreamVersion1(DaStreamReader& a_reader,
                             std::string& a_cellLine,
                             int a_cellType,
                             VecInt& a_cellstream)
{
  a_cellstream.push_back(a_cellType);
  if (a_cellType == XMU_POLYHEDRON)
  {
    int numFaces;
    std::string faceString;
    daReadIntFromLine(a_cellLine, numFaces);
    a_cellstream.push_back(numFaces);
    for (int faceIdx = 0; faceIdx < numFaces; ++faceIdx)
    {
      if (!a_reader.ReadLine(a_cellLine))
      {
        XM_LOG(xmlog::error, "Unable to read cell stream.");
        return false;
      }

      int numPoints;
      daReadIntFromLine(a_cellLine, numPoints);
      a_cellstream.push_back(numPoints);
      for (int i = 0; i < numPoints; ++i)
      {
        int ptIdx;
        daReadIntFromLine(a_cellLine, ptIdx);
        a_cellstream.push_back(ptIdx);
      }
    }
  }
  else
  {
    int numPoints;
    daReadIntFromLine(a_cellLine, numPoints);
    a_cellstream.push_back(numPoints);
    for (int i = 0; i < numPoints; ++i)
    {
      int ptIdx;
      daReadIntFromLine(a_cellLine, ptIdx);
      a_cellstream.push_back(ptIdx);
    }
  }
  return true;
} // iReadCellStreamVersion1

//------------------------------------------------------------------------------
/// \brief
/// \param a_inStream The stream to read from.
/// \param a_cellType The cell type.
/// \param a_cellstream The output cell stream.
/// \return True on success.
//------------------------------------------------------------------------------
bool iReadCellStreamVersion2(DaStreamReader& a_reader,
                             int a_cellType,
                             VecInt& a_cellstream)
{
  a_cellstream.push_back(a_cellType);
  if (a_cellType == XMU_POLYHEDRON)
  {
    int numFaces;
    std::string faceString;
    a_reader.ReadInt(numFaces);

    a_cellstream.push_back(numFaces);
    for (int faceIdx = 0; faceIdx < numFaces; ++faceIdx)
    {
      if (!a_reader.NextLine())
      {
        XM_LOG(xmlog::error, "Unable to read cell stream.");
        return false;
      }

      a_reader.ReadString(faceString);
      if (faceString != "FACE")
      {
        XM_LOG(xmlog::error, "Unable to read cell stream.");
        return false;
      }

      int faceIdxRead;
      a_reader.ReadInt(faceIdxRead);
      if (faceIdxRead != faceIdx)
      {
        XM_LOG(xmlog::error, "Unable to read cell stream.");
        return false;
      }

      int numPoints;
      a_reader.ReadInt(numPoints);
      a_cellstream.push_back(numPoints);
      for (int i = 0; i < numPoints; ++i)
      {
        int ptIdx;
        a_reader.ReadInt(ptIdx);
        a_cellstream.push_back(ptIdx);
      }
    }
  }
  else
  {
    int numPoints;
    a_reader.ReadInt(numPoints);
    a_cellstream.push_back(numPoints);
    for (int i = 0; i < numPoints; ++i)
    {
      int ptIdx;
      a_reader.ReadInt(ptIdx);
      a_cellstream.push_back(ptIdx);
    }
  }
  return true;
} // iReadCellStreamVersion2

//------------------------------------------------------------------------------
/// \brief Read the cells for a version 1 XmUGrid file.
/// \param a_inStream The stream to read from.
/// \param cellstream The resulting cell stream.
/// \return True on success.
//------------------------------------------------------------------------------
bool iReadCellsVersion1(DaStreamReader& a_reader, VecInt& cellstream)
{
  int cellStreamSize;
  if (!iReadCellStreamSizeVersion1(a_reader, cellStreamSize))
    return false;

  cellstream.reserve(cellStreamSize);
  while ((int)cellstream.size() < cellStreamSize)
  {
    std::string cellLine;
    a_reader.ReadLine(cellLine);
    std::string cardName;
    DaStreamReader::ReadStringFromLine(cellLine, cardName);
    if (cardName != "CELL")
    {
      XM_LOG(xmlog::error, "Unable to read XmUGrid cell.");
      return false;
    }

    int cellType;
    if (!iReadCellLineVersion1(a_reader, cellLine, cellType))
      return false;

    if (!iReadCellStreamVersion1(a_reader, cellLine, cellType, cellstream))
      return false;
  }

  return true;
} // iReadCellsVersion1

//------------------------------------------------------------------------------
/// \brief Read the cells for a version 1 XmUGrid file.
/// \param a_inStream The stream to read from.
/// \param cellstream The resulting cell stream.
/// \return True on success.
//------------------------------------------------------------------------------
bool iReadCellsVersion2(DaStreamReader& a_reader, VecInt& cellstream)
{
  int cellStreamSize;
  if (!iReadCellStreamSizeVersion2(a_reader, cellStreamSize))
    return false;

  cellstream.reserve(cellStreamSize);
  int cellIdx = 0;
  while ((int)cellstream.size() < cellStreamSize)
  {
    std::string cardName;
    a_reader.ReadString(cardName);
    if (cardName != "CELL")
    {
      XM_LOG(xmlog::error, "Unable to read XmUGrid cell.");
      return false;
    }

    int cellType;
    if (!iReadCellLineVersion2(a_reader, cellIdx, cellType))
      return false;

    if (!iReadCellStreamVersion2(a_reader, cellType, cellstream))
      return false;
    ++cellIdx;
  }

  return true;
} // iReadCellsVersion2
//------------------------------------------------------------------------------
/// \brief Write XmUGrid cell stream as text.
/// \param a_outStream The output stream.
/// \param a_ugrid The UGrid.
//------------------------------------------------------------------------------
void iWriteCellStream(DaStreamWriter& a_writer, const VecInt& a_cellstream)
{
  // number of cell stream items
  int cellstreamSize = (int)a_cellstream.size();
  a_writer.WriteIntLine("CELL_STREAM", cellstreamSize);

  // cells
  std::ostringstream out;
  int currIdx = 0;
  int cellIdx = 0;
  while (currIdx < cellstreamSize)
  {
    int cellType = a_cellstream[currIdx++];
    a_writer.WriteString("  CELL");
    a_writer.AppendInt(cellIdx);
    std::string cellTypeString = iStringFromCellType(cellType);
    if (!cellTypeString.empty())
    {
      a_writer.AppendString(cellTypeString);
    }
    else
    {
      std::ostringstream err;
      err << "Unknow cell type (" << cellType << ").";
      XM_LOG(xmlog::error, err.str());
      return;
    }

    int numItems = a_cellstream[currIdx++];
    if (cellType == XMU_POLYHEDRON)
    {
      int numFaces = numItems;
      a_writer.AppendInt(numFaces);
      a_writer.EndLine();
      for (int faceIdx = 0; faceIdx < numFaces; ++faceIdx)
      {
        a_writer.WriteString("    FACE");
        a_writer.AppendInt(faceIdx);
        numItems = a_cellstream[currIdx++];
        a_writer.AppendInt(numItems);
        a_writer.AppendInts(&a_cellstream[currIdx], numItems);
        a_writer.EndLine();
        currIdx += numItems;
      }
    }
    else
    {
      a_writer.AppendInt(numItems);
      a_writer.AppendInts(&a_cellstream[currIdx], numItems);
      a_writer.EndLine();
      currIdx += numItems;
    }
    ++cellIdx;
  }
} // iWriteCellStream
////////////////////////////////////////////////////////////////////////////////
/// \class XmUGridReaderVersion2
////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
/// \brief Constructor.
/// \param a_inStream The input stream.
//------------------------------------------------------------------------------
XmUGridReaderVersion2::XmUGridReaderVersion2(DaStreamReader& a_reader)
: m_reader(a_reader)
{
} // XmUGridReaderVersion2::XmUGridReaderVersion2
//------------------------------------------------------------------------------
/// \brief Read XmUGrid locations.
/// \param a_locations The locations.
//------------------------------------------------------------------------------
bool XmUGridReaderVersion2::ReadLocations(VecPt3d& a_locations)
{
  return m_reader.ReadVecPt3d("LOCATIONS", a_locations);
} // XmUGridReaderVersion2::WriteLocations
//------------------------------------------------------------------------------
/// \brief Read XmUGrid cell stream.
/// \param a_cellstream The cell stream.
//------------------------------------------------------------------------------
bool XmUGridReaderVersion2::ReadCellstream(VecInt& a_cellstream)
{
  if (m_reader.IsBinary())
    return m_reader.ReadVecInt("CELL_STREAM", a_cellstream);
  return iReadCellsVersion2(m_reader, a_cellstream);
} // XmUGridReaderVersion2::ReadCellstream
//------------------------------------------------------------------------------
/// \brief Read XmUGrid private integer arrays.
/// \param a_intArrays The private integer arrays.
//------------------------------------------------------------------------------
bool XmUGridReaderVersion2::ReadIntArrays(IntArrays& a_intArrays)
{
  bool success = true;
  //if (m_binary)
  //{
  //  for (auto& intArray : a_intArrays)
  //  {
  //    int count;
  //    success = daReadIntLine(m_inStream, "CELL_STREAM", count);
  //    if (count > 0)
  //    {
  //      VecInt& intVec = *intArray.second;
  //      intVec.resize(count);
  //      iReadBase64Bytes(m_inStream, (char*)&intVec[0]);
  //    }
  //  }
  //}
  return success;
} // XmUGridReaderVersion2::WriteIntArrays
////////////////////////////////////////////////////////////////////////////////
/// \class XmUGridWriterVersion2
////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
/// \brief Constructor.
/// \param a_outStream The output stream.
//------------------------------------------------------------------------------
XmUGridWriterVersion2::XmUGridWriterVersion2(DaStreamWriter& a_writer)
: m_writer(a_writer)
{
} // XmUGridWriterVersion2::XmUGridWriterVersion2
//------------------------------------------------------------------------------
/// \brief Write XmUGrid locations.
/// \param a_locations The locations.
//------------------------------------------------------------------------------
bool XmUGridWriterVersion2::WriteLocations(const VecPt3d& a_locations)
{
  m_writer.WriteVecPt3d("LOCATIONS", a_locations);
  return true;
} // XmUGridWriterVersion2::WriteLocations
//------------------------------------------------------------------------------
/// \brief Write XmUGrid cell stream.
/// \param a_cellstream The cell stream.
//------------------------------------------------------------------------------
bool XmUGridWriterVersion2::WriteCellstream(const VecInt& a_cellstream)
{
  if (m_writer.IsBinary())
    m_writer.WriteVecInt("CELL_STREAM", a_cellstream);
  else
    iWriteCellStream(m_writer, a_cellstream);
  return true;
} // XmUGridWriterVersion2::WriteCellstream
//------------------------------------------------------------------------------
/// \brief Write XmUGrid private integer arrays.
/// \param a_intArrays The private integer arrays.
//------------------------------------------------------------------------------
bool XmUGridWriterVersion2::WriteIntArrays(ConstIntArrays& a_intArrays)
{
  bool success = true;
  //if (m_binary)
  //{
  //  for (auto& intArray : a_intArrays)
  //  {
  //    const VecInt& vecInts = *intArray.second;
  //    int arraySize = (int)vecInts.size();
  //    daWriteIntLine(m_outStream, intArray.first, arraySize);
  //    std::cerr << intArray.first << '\n';
  //    if (arraySize > 0)
  //      iWriteBase64Bytes(m_outStream, (const char*)&vecInts[0], arraySize * sizeof(int));
  //  }
  //}
  return success;
} // XmUGridWriterVersion2::WriteIntArrays

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

  int version;
  bool binary = false;
  if (versionString == "ASCII XmUGrid Version 1.0")
  {
    version = 1;
  }
  else if (versionString == "ASCII XmUGrid Version 2")
  {
    version = 2;
  }
  else if (versionString == "Binary XmUGrid Version 2")
  {
    version = 2;
    binary = true;
  }
  else
  {
    XM_LOG(xmlog::error, "Unsupported file version or file type.");
    return nullptr;
  }

  if (version == 1)
  {
    DaStreamReader reader(a_inStream, false);
    VecPt3d locations;
    if (version == 1 && !iReadPointsVersion1(reader, locations))
      return nullptr;
    VecInt cellstream;
    if (version == 1 && !iReadCellsVersion1(reader, cellstream))
      return nullptr;
    BSHP<XmUGrid> xmUGrid = XmUGrid::New(locations, cellstream);
    return xmUGrid;
  }

  DaStreamReader reader(a_inStream, binary);
  XmUGridReaderVersion2 gridReader(reader);
  BSHP<XmUGrid> xmUGrid = XmUGrid::New(gridReader);
  return xmUGrid;
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
void XmWriteUGridToStream(const XmUGrid& a_ugrid,
                          std::ostream& a_outStream,
                          bool a_binary /*= true*/)
{
  if (a_binary)
    a_outStream << "Binary XmUGrid Version 2\n";
  else
    a_outStream << "ASCII XmUGrid Version 2\n";
  DaStreamWriter writer(a_outStream, a_binary);
  XmUGridWriterVersion2 gridWriter(writer);
  a_ugrid.WriteXmUGrid(gridWriter);
} // XmWriteUGridToStream

} // namespace xms

#ifdef CXX_TEST
//------------------------------------------------------------------------------
// Unit Tests
//------------------------------------------------------------------------------
using namespace xms;
#include <xmsgrid/ugrid/XmUGrid.t.h>
#include <xmsgrid/ugrid/XmUGridUtils.t.h>

namespace
{
//------------------------------------------------------------------------------
/// \brief Path to test files.
/// \return Returns path to test files.
//------------------------------------------------------------------------------
std::string TestFilesPath()
{
  return std::string(XMS_TEST_PATH);
} // TestFilesPath
} // namespace

////////////////////////////////////////////////////////////////////////////////
/// \class XmUGridUtilsTests
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
    "ASCII XmUGrid Version 2\n"
    "LOCATIONS 0\n"
    "CELL_STREAM 0\n";
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
    "ASCII XmUGrid Version 2\n"
    "LOCATIONS 3\n"
    "  POINT 0 0.0 0.0 0.0\n"
    "  POINT 1 20.0 0.0 0.0\n"
    "  POINT 2 0.0 20.0 0.0\n"
    "CELL_STREAM 5\n"
    "  CELL 0 TRIANGLE 3 0 1 2\n";
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
    "ASCII XmUGrid Version 2\n"
    "LOCATIONS 8\n"
    "  POINT 0 0.0 0.0 10.0\n"
    "  POINT 1 10.0 0.0 10.0\n"
    "  POINT 2 10.0 10.0 10.0\n"
    "  POINT 3 0.0 10.0 10.0\n"
    "  POINT 4 0.0 0.0 0.0\n"
    "  POINT 5 10.0 0.0 0.0\n"
    "  POINT 6 10.0 10.0 0.0\n"
    "  POINT 7 0.0 10.0 0.0\n"
    "CELL_STREAM 32\n"
    "  CELL 0 POLYHEDRON 6\n"
    "    FACE 0 4 0 1 2 3\n"
    "    FACE 1 4 4 5 7 2\n"
    "    FACE 2 4 5 6 2 1\n"
    "    FACE 3 4 6 7 3 2\n"
    "    FACE 4 4 7 4 0 3\n"
    "    FACE 5 4 4 7 6 5\n";
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
    "ASCII XmUGrid Version 2\n"
    "LOCATIONS 14\n"
    "  POINT 0 0.0 0.0 0.0\n"
    "  POINT 1 10.0 0.0 0.0\n"
    "  POINT 2 20.0 0.0 0.0\n"
    "  POINT 3 30.0 0.0 0.0\n"
    "  POINT 4 40.0 0.0 0.0\n"
    "  POINT 5 0.0 10.0 0.0\n"
    "  POINT 6 10.0 10.0 0.0\n"
    "  POINT 7 20.0 10.0 0.0\n"
    "  POINT 8 40.0 10.0 0.0\n"
    "  POINT 9 0.0 20.0 0.0\n"
    "  POINT 10 10.0 20.0 0.0\n"
    "  POINT 11 20.0 20.0 0.0\n"
    "  POINT 12 30.0 20.0 0.0\n"
    "  POINT 13 40.0 20.0 0.0\n"
    "CELL_STREAM 34\n"
    "  CELL 0 QUAD 4 0 1 6 5\n"
    "  CELL 1 PIXEL 4 1 2 6 7\n"
    "  CELL 2 TRIANGLE 3 2 3 7\n"
    "  CELL 3 POLYGON 6 3 4 8 13 12 7\n"
    "  CELL 4 POLY_LINE 3 7 11 10\n"
    "  CELL 5 LINE 2 5 9\n";
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
    "ASCII XmUGrid Version 2\n"
    "LOCATIONS 30\n"
    "  POINT 0 0.0 0.0 0.0\n"
    "  POINT 1 10.0 0.0 0.0\n"
    "  POINT 2 20.0 0.0 0.0\n"
    "  POINT 3 30.0 0.0 0.0\n"
    "  POINT 4 40.0 0.0 0.0\n"
    "  POINT 5 0.0 10.0 0.0\n"
    "  POINT 6 10.0 10.0 0.0\n"
    "  POINT 7 20.0 10.0 0.0\n"
    "  POINT 8 30.0 10.0 0.0\n"
    "  POINT 9 40.0 10.0 0.0\n"
    "  POINT 10 0.0 20.0 0.0\n"
    "  POINT 11 10.0 20.0 0.0\n"
    "  POINT 12 20.0 20.0 0.0\n"
    "  POINT 13 30.0 20.0 0.0\n"
    "  POINT 14 40.0 20.0 0.0\n"
    "  POINT 15 0.0 0.0 10.0\n"
    "  POINT 16 10.0 0.0 10.0\n"
    "  POINT 17 20.0 0.0 10.0\n"
    "  POINT 18 30.0 0.0 10.0\n"
    "  POINT 19 40.0 0.0 10.0\n"
    "  POINT 20 0.0 10.0 10.0\n"
    "  POINT 21 10.0 10.0 10.0\n"
    "  POINT 22 20.0 10.0 10.0\n"
    "  POINT 23 30.0 10.0 10.0\n"
    "  POINT 24 40.0 10.0 10.0\n"
    "  POINT 25 0.0 20.0 10.0\n"
    "  POINT 26 10.0 20.0 10.0\n"
    "  POINT 27 20.0 20.0 10.0\n"
    "  POINT 28 30.0 20.0 10.0\n"
    "  POINT 29 40.0 20.0 10.0\n"
    "CELL_STREAM 73\n"
    "  CELL 0 TETRA 4 0 1 5 15\n"
    "  CELL 1 VOXEL 8 1 2 6 7 16 17 21 22\n"
    "  CELL 2 HEXAHEDRON 8 2 3 8 7 17 18 23 22\n"
    "  CELL 3 POLYHEDRON 6\n"
    "    FACE 0 4 9 8 13 14\n"
    "    FACE 1 4 8 9 24 23\n"
    "    FACE 2 4 9 14 29 24\n"
    "    FACE 3 4 14 13 28 29\n"
    "    FACE 4 4 8 13 28 23\n"
    "    FACE 5 4 23 24 29 28\n"
    "  CELL 4 WEDGE 6 3 4 18 8 9 23\n"
    "  CELL 5 PYRAMID 5 5 6 11 10 20\n";
  std::string outputString = output.str();
  TS_ASSERT_EQUALS(outputBase, outputString);
} // XmUGridUtilsTests::testWriteLinear3dCells
//------------------------------------------------------------------------------
/// \brief Test reading an ASCII file for an empty UGrid.
//------------------------------------------------------------------------------
void XmUGridUtilsTests::testReadEmptyUGridAsciiFile()
{
  std::string inputText =
    "ASCII XmUGrid Version 2\n"
    "LOCATIONS 0\n"
    "CELL_STREAM 0\n";
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
    "ASCII XmUGrid Version 2\n"
    "LOCATIONS 3\n"
    "  POINT 0 0.0 0.0 0.0\n"
    "  POINT 1 20.0 0.0 0.0\n"
    "  POINT 2 0.0 20.0 0.0\n"
    "CELL_STREAM 5\n"
    "  CELL 0 TRIANGLE 3 0 1 2\n";
  std::istringstream input;
  input.str(inputText);
  BSHP<XmUGrid> ugrid = XmReadUGridFromStream(input);
  if (!ugrid)
    TS_FAIL("Failed to read UGrid.");

  BSHP<XmUGrid> ugridBase = TEST_XmUGrid1Left90Tri();
  VecPt3d locations = ugrid->GetLocations();
  TS_ASSERT_EQUALS(ugridBase->GetLocations(), locations);
  VecInt cellstream = ugrid->GetCellstream();
  TS_ASSERT_EQUALS(ugridBase->GetCellstream(), cellstream);
} // XmUGridUtilsTests::testReadBasicUGrid
//------------------------------------------------------------------------------
/// \brief Test reading an ASCII file for a single triangle UGrid.
//------------------------------------------------------------------------------
void XmUGridUtilsTests::testReadPolyhedronUGrid()
{
  std::string inputText =
    "ASCII XmUGrid Version 2\n"
    "LOCATIONS 8\n"
    "  POINT 0 0.0 0.0 10.0\n"
    "  POINT 1 10.0 0.0 10.0\n"
    "  POINT 2 10.0 10.0 10.0\n"
    "  POINT 3 0.0 10.0 10.0\n"
    "  POINT 4 0.0 0.0 0.0\n"
    "  POINT 5 10.0 0.0 0.0\n"
    "  POINT 6 10.0 10.0 0.0\n"
    "  POINT 7 0.0 10.0 0.0\n"
    "CELL_STREAM 32\n"
    "  CELL 0 POLYHEDRON 6\n"
    "    FACE 0 4 0 1 2 3\n"
    "    FACE 1 4 4 5 7 2\n"
    "    FACE 2 4 5 6 2 1\n"
    "    FACE 3 4 6 7 3 2\n"
    "    FACE 4 4 7 4 0 3\n"
    "    FACE 5 4 4 7 6 5\n";
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
/// \brief
//------------------------------------------------------------------------------
void XmUGridUtilsTests::testReadVersion1Dot0File()
{
  std::string inputText =
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
  std::istringstream input(inputText);
  BSHP<XmUGrid> ugrid = XmReadUGridFromStream(input);
  if (!ugrid)
    TS_FAIL("Failed to read UGrid.");

  BSHP<XmUGrid> ugridBase = TEST_XmUGrid3dLinear();
  TS_ASSERT_EQUALS(ugridBase->GetLocations(), ugrid->GetLocations());
  TS_ASSERT_EQUALS(ugridBase->GetCellstream(), ugrid->GetCellstream());
} // XmUGridUtilsTests::testReadVersion1Dot0File
//------------------------------------------------------------------------------
/// \brief Test writing then reading an XmUGrid binary file.
//------------------------------------------------------------------------------
void XmUGridUtilsTests::testWriteThenReadUGridBinary()
{
  BSHP<XmUGrid> ugridOut = TEST_XmUGrid3dLinear();
  std::ostringstream output;
  bool binary = true;
  XmWriteUGridToStream(*ugridOut, output, binary);

  std::string outputBase =
    "Binary XmUGrid Version 2\n"
    "LOCATIONS 30\n"
    "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAJEAAAAAAAAAAAAAAAAAAAAAAAAAAAAAANEAAAAAAAAAAAAAAAAAAAA"
    "AAAAAAAAAAPkAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAREAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAkQAAAAAAA"
    "AAAAAAAAAAAAJEAAAAAAAAAkQAAAAAAAAAAAAAAAAAAANEAAAAAAAAAkQAAAAAAAAAAAAAAAAAAAPkAAAAAAAAAkQAAAAA"
    "AAAAAAAAAAAAAAREAAAAAAAAAkQAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA0QAAAAAAAAAAAAAAAAAAAJEAAAAAAAAA0QAAA"
    "AAAAAAAAAAAAAAAANEAAAAAAAAA0QAAAAAAAAAAAAAAAAAAAPkAAAAAAAAA0QAAAAAAAAAAAAAAAAAAAREAAAAAAAAA0QA"
    "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAACRAAAAAAAAAJEAAAAAAAAAAAAAAAAAAACRAAAAAAAAANEAAAAAAAAAA"
    "AAAAAAAAACRAAAAAAAAAPkAAAAAAAAAAAAAAAAAAACRAAAAAAAAAREAAAAAAAAAAAAAAAAAAACRAAAAAAAAAAAAAAAAAAA"
    "AkQAAAAAAAACRAAAAAAAAAJEAAAAAAAAAkQAAAAAAAACRAAAAAAAAANEAAAAAAAAAkQAAAAAAAACRAAAAAAAAAPkAAAAAA"
    "AAAkQAAAAAAAACRAAAAAAAAAREAAAAAAAAAkQAAAAAAAACRAAAAAAAAAAAAAAAAAAAA0QAAAAAAAACRAAAAAAAAAJEAAAA"
    "AAAAA0QAAAAAAAACRAAAAAAAAANEAAAAAAAAA0QAAAAAAAACRAAAAAAAAAPkAAAAAAAAA0QAAAAAAAACRAAAAAAAAAREAA"
    "AAAAAAA0QAAAAAAAACRA\n"
    "CELL_STREAM 73\n"
    "CgAAAAQAAAAAAAAAAQAAAAUAAAAPAAAACwAAAAgAAAABAAAAAgAAAAYAAAAHAAAAEAAAABEAAAAVAAAAFgAAAAwAAAAIAA"
    "AAAgAAAAMAAAAIAAAABwAAABEAAAASAAAAFwAAABYAAAAqAAAABgAAAAQAAAAJAAAACAAAAA0AAAAOAAAABAAAAAgAAAAJ"
    "AAAAGAAAABcAAAAEAAAACQAAAA4AAAAdAAAAGAAAAAQAAAAOAAAADQAAABwAAAAdAAAABAAAAAgAAAANAAAAHAAAABcAAA"
    "AEAAAAFwAAABgAAAAdAAAAHAAAAA0AAAAGAAAAAwAAAAQAAAASAAAACAAAAAkAAAAXAAAADgAAAAUAAAAFAAAABgAAAAsA"
    "AAAKAAAAFAAAAA\n";
  std::string outputString = output.str();
  TS_ASSERT_EQUALS(outputBase, outputString);

  std::istringstream input(outputString);
  BSHP<XmUGrid> ugridIn = XmReadUGridFromStream(input);
  if (!ugridIn)
    TS_FAIL("Failed to read UGrid.");
  TS_ASSERT_EQUALS(ugridOut->GetLocations(), ugridIn->GetLocations());
  TS_ASSERT_EQUALS(ugridOut->GetCellstream(), ugridIn->GetCellstream());

} // XmUGridUtilsTests::testWriteThenReadUGridBinary
//------------------------------------------------------------------------------
/// \brief Test conversion between cell type string and cell type enum.
//------------------------------------------------------------------------------
void XmUGridUtilsTests::testCellStringToEnum()
{
  TS_ASSERT_EQUALS("INVALID_CELL_TYPE", iStringFromCellType(XMU_INVALID_CELL_TYPE));
  TS_ASSERT_EQUALS("EMPTY_CELL", iStringFromCellType(XMU_EMPTY_CELL));
  TS_ASSERT_EQUALS("VERTEX", iStringFromCellType(XMU_VERTEX));
  TS_ASSERT_EQUALS("POLY_VERTEX", iStringFromCellType(XMU_POLY_VERTEX));
  TS_ASSERT_EQUALS("LINE", iStringFromCellType(XMU_LINE));
  TS_ASSERT_EQUALS("POLY_LINE", iStringFromCellType(XMU_POLY_LINE));
  TS_ASSERT_EQUALS("TRIANGLE", iStringFromCellType(XMU_TRIANGLE));
  TS_ASSERT_EQUALS("TRIANGLE_STRIP", iStringFromCellType(XMU_TRIANGLE_STRIP));
  TS_ASSERT_EQUALS("POLYGON", iStringFromCellType(XMU_POLYGON));
  TS_ASSERT_EQUALS("PIXEL", iStringFromCellType(XMU_PIXEL));
  TS_ASSERT_EQUALS("QUAD", iStringFromCellType(XMU_QUAD));
  TS_ASSERT_EQUALS("TETRA", iStringFromCellType(XMU_TETRA));
  TS_ASSERT_EQUALS("VOXEL", iStringFromCellType(XMU_VOXEL));
  TS_ASSERT_EQUALS("HEXAHEDRON", iStringFromCellType(XMU_HEXAHEDRON));
  TS_ASSERT_EQUALS("WEDGE", iStringFromCellType(XMU_WEDGE));
  TS_ASSERT_EQUALS("PYRAMID", iStringFromCellType(XMU_PYRAMID));
  TS_ASSERT_EQUALS("PENTAGONAL_PRISM", iStringFromCellType(XMU_PENTAGONAL_PRISM));
  TS_ASSERT_EQUALS("HEXAGONAL_PRISM", iStringFromCellType(XMU_HEXAGONAL_PRISM));
  TS_ASSERT_EQUALS("QUADRATIC_EDGE", iStringFromCellType(XMU_QUADRATIC_EDGE));
  TS_ASSERT_EQUALS("QUADRATIC_TRIANGLE", iStringFromCellType(XMU_QUADRATIC_TRIANGLE));
  TS_ASSERT_EQUALS("QUADRATIC_QUAD", iStringFromCellType(XMU_QUADRATIC_QUAD));
  TS_ASSERT_EQUALS("QUADRATIC_POLYGON", iStringFromCellType(XMU_QUADRATIC_POLYGON));
  TS_ASSERT_EQUALS("QUADRATIC_TETRA", iStringFromCellType(XMU_QUADRATIC_TETRA));
  TS_ASSERT_EQUALS("QUADRATIC_HEXAHEDRON", iStringFromCellType(XMU_QUADRATIC_HEXAHEDRON));
  TS_ASSERT_EQUALS("QUADRATIC_WEDGE", iStringFromCellType(XMU_QUADRATIC_WEDGE));
  TS_ASSERT_EQUALS("QUADRATIC_PYRAMID", iStringFromCellType(XMU_QUADRATIC_PYRAMID));
  TS_ASSERT_EQUALS("BIQUADRATIC_QUAD", iStringFromCellType(XMU_BIQUADRATIC_QUAD));
  TS_ASSERT_EQUALS("TRIQUADRATIC_HEXAHEDRON", iStringFromCellType(XMU_TRIQUADRATIC_HEXAHEDRON));
  TS_ASSERT_EQUALS("QUADRATIC_LINEAR_QUAD", iStringFromCellType(XMU_QUADRATIC_LINEAR_QUAD));
  TS_ASSERT_EQUALS("QUADRATIC_LINEAR_WEDGE", iStringFromCellType(XMU_QUADRATIC_LINEAR_WEDGE));
  TS_ASSERT_EQUALS("BIQUADRATIC_QUADRATIC_WEDGE", iStringFromCellType(XMU_BIQUADRATIC_QUADRATIC_WEDGE));
  TS_ASSERT_EQUALS("BIQUADRATIC_QUADRATIC_HEXAHEDRON", iStringFromCellType(XMU_BIQUADRATIC_QUADRATIC_HEXAHEDRON));
  TS_ASSERT_EQUALS("BIQUADRATIC_TRIANGLE", iStringFromCellType(XMU_BIQUADRATIC_TRIANGLE));
  TS_ASSERT_EQUALS("CUBIC_LINE", iStringFromCellType(XMU_CUBIC_LINE));
  TS_ASSERT_EQUALS("CONVEX_POINT_SET", iStringFromCellType(XMU_CONVEX_POINT_SET));
  TS_ASSERT_EQUALS("POLYHEDRON", iStringFromCellType(XMU_POLYHEDRON));
  TS_ASSERT_EQUALS("PARAMETRIC_CURVE", iStringFromCellType(XMU_PARAMETRIC_CURVE));
  TS_ASSERT_EQUALS("PARAMETRIC_SURFACE", iStringFromCellType(XMU_PARAMETRIC_SURFACE));
  TS_ASSERT_EQUALS("PARAMETRIC_TRI_SURFACE", iStringFromCellType(XMU_PARAMETRIC_TRI_SURFACE));
  TS_ASSERT_EQUALS("PARAMETRIC_QUAD_SURFACE", iStringFromCellType(XMU_PARAMETRIC_QUAD_SURFACE));
  TS_ASSERT_EQUALS("PARAMETRIC_TETRA_REGION", iStringFromCellType(XMU_PARAMETRIC_TETRA_REGION));
  TS_ASSERT_EQUALS("PARAMETRIC_HEX_REGION", iStringFromCellType(XMU_PARAMETRIC_HEX_REGION));
  TS_ASSERT_EQUALS("HIGHER_ORDER_EDGE", iStringFromCellType(XMU_HIGHER_ORDER_EDGE));
  TS_ASSERT_EQUALS("HIGHER_ORDER_TRIANGLE", iStringFromCellType(XMU_HIGHER_ORDER_TRIANGLE));
  TS_ASSERT_EQUALS("HIGHER_ORDER_QUAD", iStringFromCellType(XMU_HIGHER_ORDER_QUAD));
  TS_ASSERT_EQUALS("HIGHER_ORDER_POLYGON", iStringFromCellType(XMU_HIGHER_ORDER_POLYGON));
  TS_ASSERT_EQUALS("HIGHER_ORDER_TETRAHEDRON", iStringFromCellType(XMU_HIGHER_ORDER_TETRAHEDRON));
  TS_ASSERT_EQUALS("HIGHER_ORDER_WEDGE", iStringFromCellType(XMU_HIGHER_ORDER_WEDGE));
  TS_ASSERT_EQUALS("HIGHER_ORDER_PYRAMID", iStringFromCellType(XMU_HIGHER_ORDER_PYRAMID));
  TS_ASSERT_EQUALS("HIGHER_ORDER_HEXAHEDRON", iStringFromCellType(XMU_HIGHER_ORDER_HEXAHEDRON));

  TS_ASSERT_EQUALS(XMU_INVALID_CELL_TYPE, iCellTypeFromString("INVALID_CELL_TYPE"));
  TS_ASSERT_EQUALS(XMU_EMPTY_CELL, iCellTypeFromString("EMPTY_CELL"));
  TS_ASSERT_EQUALS(XMU_VERTEX, iCellTypeFromString("VERTEX"));
  TS_ASSERT_EQUALS(XMU_POLY_VERTEX, iCellTypeFromString("POLY_VERTEX"));
  TS_ASSERT_EQUALS(XMU_LINE, iCellTypeFromString("LINE"));
  TS_ASSERT_EQUALS(XMU_POLY_LINE, iCellTypeFromString("POLY_LINE"));
  TS_ASSERT_EQUALS(XMU_TRIANGLE, iCellTypeFromString("TRIANGLE"));
  TS_ASSERT_EQUALS(XMU_TRIANGLE_STRIP, iCellTypeFromString("TRIANGLE_STRIP"));
  TS_ASSERT_EQUALS(XMU_POLYGON, iCellTypeFromString("POLYGON"));
  TS_ASSERT_EQUALS(XMU_PIXEL, iCellTypeFromString("PIXEL"));
  TS_ASSERT_EQUALS(XMU_QUAD, iCellTypeFromString("QUAD"));
  TS_ASSERT_EQUALS(XMU_TETRA, iCellTypeFromString("TETRA"));
  TS_ASSERT_EQUALS(XMU_VOXEL, iCellTypeFromString("VOXEL"));
  TS_ASSERT_EQUALS(XMU_HEXAHEDRON, iCellTypeFromString("HEXAHEDRON"));
  TS_ASSERT_EQUALS(XMU_WEDGE, iCellTypeFromString("WEDGE"));
  TS_ASSERT_EQUALS(XMU_PYRAMID, iCellTypeFromString("PYRAMID"));
  TS_ASSERT_EQUALS(XMU_PENTAGONAL_PRISM, iCellTypeFromString("PENTAGONAL_PRISM"));
  TS_ASSERT_EQUALS(XMU_HEXAGONAL_PRISM, iCellTypeFromString("HEXAGONAL_PRISM"));
  TS_ASSERT_EQUALS(XMU_QUADRATIC_EDGE, iCellTypeFromString("QUADRATIC_EDGE"));
  TS_ASSERT_EQUALS(XMU_QUADRATIC_TRIANGLE, iCellTypeFromString("QUADRATIC_TRIANGLE"));
  TS_ASSERT_EQUALS(XMU_QUADRATIC_QUAD, iCellTypeFromString("QUADRATIC_QUAD"));
  TS_ASSERT_EQUALS(XMU_QUADRATIC_POLYGON, iCellTypeFromString("QUADRATIC_POLYGON"));
  TS_ASSERT_EQUALS(XMU_QUADRATIC_TETRA, iCellTypeFromString("QUADRATIC_TETRA"));
  TS_ASSERT_EQUALS(XMU_QUADRATIC_HEXAHEDRON, iCellTypeFromString("QUADRATIC_HEXAHEDRON"));
  TS_ASSERT_EQUALS(XMU_QUADRATIC_WEDGE, iCellTypeFromString("QUADRATIC_WEDGE"));
  TS_ASSERT_EQUALS(XMU_QUADRATIC_PYRAMID, iCellTypeFromString("QUADRATIC_PYRAMID"));
  TS_ASSERT_EQUALS(XMU_BIQUADRATIC_QUAD, iCellTypeFromString("BIQUADRATIC_QUAD"));
  TS_ASSERT_EQUALS(XMU_TRIQUADRATIC_HEXAHEDRON, iCellTypeFromString("TRIQUADRATIC_HEXAHEDRON"));
  TS_ASSERT_EQUALS(XMU_QUADRATIC_LINEAR_QUAD, iCellTypeFromString("QUADRATIC_LINEAR_QUAD"));
  TS_ASSERT_EQUALS(XMU_QUADRATIC_LINEAR_WEDGE, iCellTypeFromString("QUADRATIC_LINEAR_WEDGE"));
  TS_ASSERT_EQUALS(XMU_BIQUADRATIC_QUADRATIC_WEDGE, iCellTypeFromString("BIQUADRATIC_QUADRATIC_WEDGE"));
  TS_ASSERT_EQUALS(XMU_BIQUADRATIC_QUADRATIC_HEXAHEDRON, iCellTypeFromString("BIQUADRATIC_QUADRATIC_HEXAHEDRON"));
  TS_ASSERT_EQUALS(XMU_BIQUADRATIC_TRIANGLE, iCellTypeFromString("BIQUADRATIC_TRIANGLE"));
  TS_ASSERT_EQUALS(XMU_CUBIC_LINE, iCellTypeFromString("CUBIC_LINE"));
  TS_ASSERT_EQUALS(XMU_CONVEX_POINT_SET, iCellTypeFromString("CONVEX_POINT_SET"));
  TS_ASSERT_EQUALS(XMU_POLYHEDRON, iCellTypeFromString("POLYHEDRON"));
  TS_ASSERT_EQUALS(XMU_PARAMETRIC_CURVE, iCellTypeFromString("PARAMETRIC_CURVE"));
  TS_ASSERT_EQUALS(XMU_PARAMETRIC_SURFACE, iCellTypeFromString("PARAMETRIC_SURFACE"));
  TS_ASSERT_EQUALS(XMU_PARAMETRIC_TRI_SURFACE, iCellTypeFromString("PARAMETRIC_TRI_SURFACE"));
  TS_ASSERT_EQUALS(XMU_PARAMETRIC_QUAD_SURFACE, iCellTypeFromString("PARAMETRIC_QUAD_SURFACE"));
  TS_ASSERT_EQUALS(XMU_PARAMETRIC_TETRA_REGION, iCellTypeFromString("PARAMETRIC_TETRA_REGION"));
  TS_ASSERT_EQUALS(XMU_PARAMETRIC_HEX_REGION, iCellTypeFromString("PARAMETRIC_HEX_REGION"));
  TS_ASSERT_EQUALS(XMU_HIGHER_ORDER_EDGE, iCellTypeFromString("HIGHER_ORDER_EDGE"));
  TS_ASSERT_EQUALS(XMU_HIGHER_ORDER_TRIANGLE, iCellTypeFromString("HIGHER_ORDER_TRIANGLE"));
  TS_ASSERT_EQUALS(XMU_HIGHER_ORDER_QUAD, iCellTypeFromString("HIGHER_ORDER_QUAD"));
  TS_ASSERT_EQUALS(XMU_HIGHER_ORDER_POLYGON, iCellTypeFromString("HIGHER_ORDER_POLYGON"));
  TS_ASSERT_EQUALS(XMU_HIGHER_ORDER_TETRAHEDRON, iCellTypeFromString("HIGHER_ORDER_TETRAHEDRON"));
  TS_ASSERT_EQUALS(XMU_HIGHER_ORDER_WEDGE, iCellTypeFromString("HIGHER_ORDER_WEDGE"));
  TS_ASSERT_EQUALS(XMU_HIGHER_ORDER_PYRAMID, iCellTypeFromString("HIGHER_ORDER_PYRAMID"));
  TS_ASSERT_EQUALS(XMU_HIGHER_ORDER_HEXAHEDRON, iCellTypeFromString("HIGHER_ORDER_HEXAHEDRON"));
  TS_ASSERT_EQUALS(50, iCellTypeStringIntPair().size());
}
// XmUGridUtilsTests::testCellStringToEnum
//------------------------------------------------------------------------------
/// \brief Tests creating a large UGrid and checks the time spent.
//------------------------------------------------------------------------------
#define SPEEDTEST
#ifdef SPEEDTEST
#include <boost/timer/timer.hpp>
#endif
void XmUGridUtilsTests::testLargeUGridBinarySpeed()
{
#ifdef SPEEDTEST
  int rows = 1000;
  int cols = 500;
  int lays = 4;
  BSHP<xms::XmUGrid> grid;
  {
    boost::timer::cpu_timer timer;
    grid = TEST_XmUBuildPolyhedronUgrid(rows, cols, lays);
    TS_FAIL("Build time: " + timer.format());
  }

  {
    std::ofstream output("C:\\temp\\speed_test_out.txt");
    boost::timer::cpu_timer timer;
    bool binary = true;
    XmWriteUGridToStream(*grid, output, binary);
    TS_FAIL("Write time: " + timer.format());
  }

  BSHP<XmUGrid> gridRead;
  {
    std::ifstream input("C:\\temp\\speed_test_out.txt");
    boost::timer::cpu_timer timer;
    gridRead = XmReadUGridFromStream(input);
    TS_FAIL("Read time: " + timer.format());
  }

  TS_ASSERT_EQUALS(grid->GetLocations(), gridRead->GetLocations());
  TS_ASSERT_EQUALS(grid->GetCellstream(), gridRead->GetCellstream());

#endif
} // XmUGridUtilsTests::testLargeUGridBinarySpeed

#endif
