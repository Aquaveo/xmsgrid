//------------------------------------------------------------------------------
/// \file
/// \ingroup dataio
/// \copyright (C) Copyright Aquaveo 2018. Distributed under FreeBSD License
/// (See accompanying file LICENSE or https://aqaveo.com/bsd/license.txt)
//------------------------------------------------------------------------------

//----- Included files ---------------------------------------------------------

// 1. Precompiled header

// 2. My header
#include <xmsgrid/dataio/daStreamIo.h>

// 3. Standard Library Headers
#include <fstream>
#include <regex>
#include <sstream>

// 4. External Library Headers
#include <boost/unordered_map.hpp>

// 5. Shared Headers
#include <xmscore/dataio/daStreamIo.h>
#include <xmscore/misc/StringUtil.h>
#include <xmscore/misc/XmError.h>
#include <xmscore/misc/XmLog.h>

//----- Forward declarations ---------------------------------------------------

//----- External globals -------------------------------------------------------

//----- Namespace declaration --------------------------------------------------

namespace xms
{
//----- Constants / Enumerations -----------------------------------------------

//----- Classes / Structs ------------------------------------------------------

//----- Class / Function definitions -------------------------------------------

class DaStreamReader::Impl
{
public:
  Impl(std::istream& a_inStream)
    : m_inStream(a_inStream)
  {
  }

  std::istream& m_inStream;
  bool m_binaryArrays;
};

class DaStreamWriter::Impl
{
public:
  Impl(std::ostream& a_outStream)
    : m_outStream(a_outStream)
  {
  }

  std::ostream& m_outStream;
  bool m_binaryArrays;
};

namespace
{
//------------------------------------------------------------------------------
/// \brief Read line of name (beginning of line) followed with up to 3 expected
/// values.
/// \param a_inStream The stream to write too. \param a_prefix The
/// string to expect before the values. \param a_val1 Optional first value.
/// \param a_val2 Optional second value.
/// \param a_val3 Optional third value.
/// \return true if name was found and all expected values.
//------------------------------------------------------------------------------
template <typename _T1 = int, typename _T2 = int, typename _T3 = int>
bool iReadLine(std::istream& a_inStream,
               const std::string& a_prefix,
               _T1* a_val1 = nullptr,
               _T2* a_val2 = nullptr,
               _T3* a_val3 = nullptr)
{
  // assert that a_prefix is entire line only if all a_val are null
  XM_ASSERT((!a_val1 && !a_val2 && !a_val3) ||
            !std::regex_match(a_prefix, std::regex("[^ \t]+[ \t]+[^ \t]+")));
  std::string line;
  if (!daReadLine(a_inStream, line))
    return false;
  for (int ii = 0; ii < a_prefix.size(); ++ii)
  {
    if (a_prefix[ii] != line[ii])
      return false;
  }

  std::string afterName = line.substr(a_prefix.size());
  std::stringstream ssline(afterName); // remainder of line
  if (a_val1)
  {
    ssline >> *a_val1;
    if (ssline.bad())
      return false;
  }
  if (a_val2)
  {
    ssline >> *a_val2;
    if (ssline.bad())
      return false;
  }
  if (a_val3)
  {
    ssline >> *a_val3;
    if (ssline.bad())
      return false;
  }
  return true;
} // iReadLine
//------------------------------------------------------------------------------
/// \brief Read a line into a std::stringstream.
/// \param a_inStream The stream to read from.
/// \param a_name The expected name before the value.
/// \param a_ss The std::stringstream to write to.
/// \return True on success.
//------------------------------------------------------------------------------
bool iReadLineToSStream(std::istream& a_inStream, const char* a_name, std::stringstream& a_ss)
{
  std::string line;
  if (!daReadLine(a_inStream, line))
    return false;

  auto position = line.find(a_name);
  if (position == std::string::npos)
    return false;
  else
  {
    for (size_t i = 0; i < position; ++i)
    {
      if (!isspace(line[i]))
        return false;
    }
  }

  a_ss.clear();
  std::replace(line.begin(), line.end(), ',', ' ');
  a_ss.str(line.substr(position));
  return !a_ss.fail();
} // iReadLineToSStream
//------------------------------------------------------------------------------
/// \brief Read a single value from a line.
/// \param a_inStream The stream to read from.
/// \param a_val The value to read.
/// \return True on success.
//------------------------------------------------------------------------------
template <typename _T>
bool iReadLineValue(std::istream& a_inStream, _T& a_val)
{
  std::string line;
  if (!daReadLine(a_inStream, line))
    return false;
  std::stringstream ss;
  ss.str(line);
  ss >> a_val;
  return !ss.fail();
} // iReadLineValue
//------------------------------------------------------------------------------
/// \brief Read named vector of values from multiple lines.
/// \param a_inStream The stream to read from.
/// \param a_name The expected name before the value.
/// \param a_vec The vector of values.
/// \return True on success.
//------------------------------------------------------------------------------
template <typename _T>
bool iReadVector(std::istream& a_inStream, const char* a_name, std::vector<_T>& a_vec)
{
  a_vec.clear();
  int size;
  if (!daReadIntLine(a_inStream, a_name, size))
    return false;
  for (int ii = 0; ii < size; ++ii)
  {
    _T val;
    if (!iReadLineValue(a_inStream, val))
      return false;
    a_vec.push_back(val);
  }
  return true;
} // iReadVector
//------------------------------------------------------------------------------
/// \brief Read a named data value from a line.
/// \param a_inStream The stream to read from.
/// \param a_name The expected name before the value.
/// \param a_d1 The data value.
/// \return True on success.
//------------------------------------------------------------------------------
template <typename _T>
bool iReadValue(std::istream& a_inStream, const char* a_name, _T& a_d1)
{
  std::stringstream ss;
  if (!iReadLineToSStream(a_inStream, a_name, ss))
    return false;
  std::string name;
  ss >> name;
  ss >> a_d1;
  return !ss.fail();
} // iReadValue
//------------------------------------------------------------------------------
/// \brief Read a named triplet of data values from a line.
/// \param a_inStream The stream to read from.
/// \param a_name The expected name before the value.
/// \param d1 The first value.
/// \param d2 The second value.
/// \param d3 The third value.
/// \return True on success.
//------------------------------------------------------------------------------
template <typename _T>
bool iRead3Values(std::istream& a_inStream, const char* a_name, _T& d1, _T& d2, _T& d3)
{
  std::stringstream ss;
  if (!iReadLineToSStream(a_inStream, a_name, ss))
    return false;
  std::string name;
  ss >> name;
  ss >> d1;
  ss >> d2;
  ss >> d3;
  return !ss.fail();
} // iRead3Values
//------------------------------------------------------------------------------
/// \brief Read a named pair of data values from a line.
/// \param a_inStream The stream to read from.
/// \param a_name The expected name before the value.
/// \param d1 The first value.
/// \param d2 The second value.
/// \return True on success.
//------------------------------------------------------------------------------
template <typename _T>
bool iRead2Values(std::istream& a_inStream, const char* a_name, _T& d1, _T& d2)
{
  std::stringstream ss;
  if (!iReadLineToSStream(a_inStream, a_name, ss))
    return false;
  std::string name;
  ss >> name;
  ss >> d1;
  ss >> d2;
  return !ss.fail();
} // iRead2Values
//------------------------------------------------------------------------------
/// \brief Write name followed with up to 3 optional values each preceded by a
/// space, and a new line after the last value.
/// \param a_outStream The stream to write too.
/// \param a_name The name to be written before the value.
/// \param a_val1 The optional first value.
/// \param a_val2 The optional second value.
/// \param a_val3 The optional third value.
//------------------------------------------------------------------------------
template <typename _T1 = int, typename _T2 = int, typename _T3 = int>
void iWriteLine(std::ostream& a_outStream,
                const std::string& a_name,
                const _T1* a_val1 = nullptr,
                const _T2* a_val2 = nullptr,
                const _T3* a_val3 = nullptr)
{
  // assert that a_name is multiple words only if all a_val are null
  XM_ASSERT((!a_val1 && !a_val2 && !a_val3) ||
            !std::regex_match(a_name, std::regex("[^ \t]+[ \t]+[^ \t]+")));
  a_outStream << a_name;
  if (a_val1)
    a_outStream << ' ' << *a_val1;
  if (a_val2)
    a_outStream << ' ' << *a_val2;
  if (a_val3)
    a_outStream << ' ' << *a_val3;
  a_outStream << '\n';
} // iWriteLine
//------------------------------------------------------------------------------
/// \brief Write a named vector of values to multiple lines.
/// \param a_outStream The stream to write too.
/// \param a_name The name to be written before the value.
/// \param a_vec The vector of values.
//------------------------------------------------------------------------------
template <typename _T>
void iWriteVec(std::ostream& a_outStream, const char* a_name, const _T& a_vec)
{
  size_t size = a_vec.size();
  iWriteLine(a_outStream, a_name, &size);
  for (auto val : a_vec)
  {
    std::string sval(STRstd(val));
    iWriteLine(a_outStream, " ", &sval); // name is an indentation of spaces
  }
}
//------------------------------------------------------------------------------
/// \brief Read an integer value from a string. Return the remaining string.
/// \param a_line The string to read from. Returns the remaining string.
/// \param a_val The value to read.
/// \return True if no errors.
//------------------------------------------------------------------------------
template <typename _T>
bool iReadValueFromLine(std::string& a_line, _T& a_val)
{
  std::string line = a_line;
  std::string stringValue;
  if (!daReadStringFromLine(line, stringValue))
    return false;

  std::istringstream inStream(stringValue);
  _T tempVal;
  inStream >> tempVal;
  if (inStream.fail() || !inStream.eof())
    return false;
  a_val = tempVal;
  a_line = line;
  return true;
} // iReadValueFromLine

} // namespace

////////////////////////////////////////////////////////////////////////////////
/// \class DaStreamReader
////////////////////////////////////////////////////////////////////////////////
DaStreamReader::DaStreamReader(std::istream& a_inStream, bool a_binary /*= false*/)
  : m_impl(new Impl(a_inStream))
{
} // DaStreamReader::DaStreamReader
//------------------------------------------------------------------------------
/// \brief Destructor.
//------------------------------------------------------------------------------
DaStreamReader::~DaStreamReader()
{
} // DaStreamReader::~DaStreamReader
//------------------------------------------------------------------------------
/// \brief Are array values read as binary?
/// \return If the array values will be read as binary.
//------------------------------------------------------------------------------
bool DaStreamReader::IsBinary() const
{
  return m_impl->m_binaryArrays;
} // DaStreamReader::IsBinary
//------------------------------------------------------------------------------
/// \brief Read a line that begins with a name.
/// \param a_name The expected name before the value.
/// \return True if no errors.
//------------------------------------------------------------------------------
bool DaStreamReader::ReadNamedLine(const char* a_name)
{
  std::stringstream ss;
  return iReadLineToSStream(m_impl->m_inStream, a_name, ss);
} // DaStreamReader::ReadNamedLine
//------------------------------------------------------------------------------
/// \brief Read a line from a stream with the following line endings: CR LF, LF,
/// CR, or none.
/// \param a_inStream The stream to read from.
/// \param a_line The line that was read.
/// \return True if no errors.
//------------------------------------------------------------------------------
bool DaStreamReader::ReadLine(std::string& a_line)
{
  a_line.clear();

  // The characters in the stream are read one-by-one using a std::streambuf.
  // That is faster than reading them one-by-one using the std::istream.
  // Code that uses streambuf this way must be guarded by a sentry object.
  // The sentry object performs various tasks,
  // such as thread synchronization and updating the stream state.

  std::istream::sentry se(m_impl->m_inStream, true);
  std::streambuf* sb = m_impl->m_inStream.rdbuf();

  for (;;)
  {
    int c = sb->sbumpc();
    if (c == '\n')
    {
      return !!m_impl->m_inStream;
    }

    if (c == '\r')
    {
      if (sb->sgetc() == '\n')
        sb->sbumpc();
      return !!m_impl->m_inStream;
    }

    if (c == std::streambuf::traits_type::eof())
    {
      // Also handle the case when the last line has no line ending
      if (a_line.empty())
        m_impl->m_inStream.setstate(std::ios::eofbit);
      return !!m_impl->m_inStream;
    }

    a_line += (char)c;
  }
} // DaStreamReader::ReadLine
//------------------------------------------------------------------------------
/// \brief Read a named integer value from a line.
/// \param a_name The expected name before the value.
/// \param a_val The integer value.
/// \return True if no errors.
//------------------------------------------------------------------------------
bool DaStreamReader::ReadIntLine(const char* a_name, int& a_val)
{
  return iReadValue(m_impl->m_inStream, a_name, a_val);
} // DaStreamReader::ReadIntLine
//------------------------------------------------------------------------------
/// \brief Read a named double value from a line.
/// \param a_name The expected name before the value.
/// \param a_val The double value.
/// \return True if no errors.
//------------------------------------------------------------------------------
bool DaStreamReader::ReadDoubleLine(const char* a_name, double& a_val)
{
  return iReadValue(m_impl->m_inStream, a_name, a_val);
} // DaStreamReader::ReadDoubleLine
//------------------------------------------------------------------------------
/// \brief Read a named string value from a line.
/// \param a_name The expected name before the value.
/// \param a_val The string value.
/// \return True if no errors.
//------------------------------------------------------------------------------
bool DaStreamReader::ReadStringLine(const char* a_name, std::string& a_val)
{
  return iReadValue(m_impl->m_inStream, a_name, a_val);
} // DaStreamReader::ReadStringLine
//------------------------------------------------------------------------------
/// \brief Read named vector of integers from multiple lines.
/// \param a_name The expected name before the value.
/// \param a_vec The vector of integers.
/// \return True if no errors.
//------------------------------------------------------------------------------
bool DaStreamReader::ReadVecInt(const char* a_name, VecInt& a_vec)
{
  return iReadVector(m_impl->m_inStream, a_name, a_vec);
} // DaStreamReader::ReadVecInt
//------------------------------------------------------------------------------
/// \brief Read named vector of doubles from multiple lines.
/// \param a_name The expected name before the value.
/// \param a_vec The vector of doubles.
/// \return True if no errors.
//------------------------------------------------------------------------------
bool DaStreamReader::ReadVecDbl(const char* a_name, VecDbl& a_vec)
{
  return iReadVector(m_impl->m_inStream, a_name, a_vec);
} // DaStreamReader::ReadVecDbl
//------------------------------------------------------------------------------
/// \brief Read named vector of Pt3d from multiple lines.
/// \param a_name The expected name before the value.
/// \param a_vec The vector of Pt3d.
/// \return True if no errors.
//------------------------------------------------------------------------------
bool DaStreamReader::ReadVecPt3d(const char* a_name, VecPt3d& a_vec)
{
  int size;
  if (!daReadIntLine(m_impl->m_inStream, a_name, size))
    return false;

  a_vec.resize(0);
  a_vec.reserve(size);
  std::string pointLine;
  std::string pointValue;
  for (int i = 0; i < size; ++i)
  {
    if (!daReadLine(m_impl->m_inStream, pointLine))
      return false;

    bool success = daReadStringFromLine(pointLine, pointValue);
    success = success && pointValue == "POINT";
    int readPointIdx = -1;
    success = success && daReadIntFromLine(pointLine, readPointIdx);
    success = success && readPointIdx == (int)i;
    Pt3d pt;
    success = success && daReadDoubleFromLine(pointLine, pt.x);
    success = success && daReadDoubleFromLine(pointLine, pt.y);
    success = success && daReadDoubleFromLine(pointLine, pt.z);
    if (!success)
      return false;
    a_vec.push_back(pt);
  }

  return true;
} // DaStreamReader::ReadVecPt3d
//------------------------------------------------------------------------------
/// \brief Read a named pair of words from a line.
/// \param a_name The expected name before the value.
/// \param a_val1 The first word.
/// \param a_val2 The second word.
/// \return True if no errors.
//------------------------------------------------------------------------------
bool DaStreamReader::Read2StringLine(
                       const char* a_name,
                       std::string& a_val1,
                       std::string& a_val2)
{
  return iRead2Values(m_impl->m_inStream, a_name, a_val1, a_val2);
} // DaStreamReader::Read2StringLine
//------------------------------------------------------------------------------
/// \brief Read a named triplet of words from a line.
/// \param a_name The expected name before the value.
/// \param a_val1 The first word.
/// \param a_val2 The second word.
/// \param a_val3 The third word.
/// \return True if no errors.
//------------------------------------------------------------------------------
bool DaStreamReader::Read3StringLine(
                       const char* a_name,
                       std::string& a_val1,
                       std::string& a_val2,
                       std::string& a_val3)
{
  return iRead3Values(m_impl->m_inStream, a_name, a_val1, a_val2, a_val3);
} // DaStreamReader::Read3StringLine
//------------------------------------------------------------------------------
/// \brief Read a named triplet of doubles from a line.
/// \param a_name The expected name before the value.
/// \param a_val1 The first double.
/// \param a_val2 The second double.
/// \param a_val3 The third double.
/// \return True if no errors.
//------------------------------------------------------------------------------
bool DaStreamReader::Read3DoubleLine(
                       const char* a_name,
                       double& a_val1,
                       double& a_val2,
                       double& a_val3)
{
  return iRead3Values(m_impl->m_inStream, a_name, a_val1, a_val2, a_val3);
} // DaStreamReader::Read3DoubleLine
//------------------------------------------------------------------------------
/// \brief Read an integer value from a string. Return the remaining string.
/// \param a_line The string to read from. Returns the remaining string.
/// \param a_val The value to read.
/// \return True if no errors.
//------------------------------------------------------------------------------
bool DaStreamReader::ReadIntFromLine(std::string& a_line, int& a_val)
{
  return iReadValueFromLine(a_line, a_val);
} // DaStreamReader::ReadIntFromLine
//------------------------------------------------------------------------------
/// \brief Read a string value from a string. Return the remaining string.
/// \param a_line The string to read from. Returns the remaining string.
/// \param a_val The value to read.
/// \return True if no errors.
//------------------------------------------------------------------------------
bool DaStreamReader::ReadStringFromLine(std::string& a_line, std::string& a_val)
{
  std::istringstream inStream(a_line);
  inStream >> a_val;
  if (inStream.fail())
    return false;
  size_t position = inStream.tellg();
  if (position != std::string::npos)
    a_line = inStream.str().substr(position);
  else
    a_line = "";
  return true;
} // DaStreamReader::ReadStringFromLine
//------------------------------------------------------------------------------
/// \brief Read a double value from a string. Return the remaining string.
/// \param a_line The string to read from. Returns the remaining string.
/// \param a_val The value to read.
/// \return True if no errors.
//------------------------------------------------------------------------------
bool DaStreamReader::ReadDoubleFromLine(std::string& a_line, double& a_val)
{
  return iReadValueFromLine(a_line, a_val);
} // DaStreamReader::ReadDoubleFromLine
////////////////////////////////////////////////////////////////////////////////
/// \class DaStreamWriter
////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
/// \brief Constructor.
//------------------------------------------------------------------------------
DaStreamWriter::DaStreamWriter(std::ostream& a_outStream, bool a_binary /*= false*/)
  : m_impl(new Impl(a_outStream))
{
} // DaStreamWriter::DaStreamWriter
//------------------------------------------------------------------------------
/// \brief Destructor.
//------------------------------------------------------------------------------
DaStreamWriter::~DaStreamWriter()
{
} // DaStreamWriter::~DaStreamWriter
//------------------------------------------------------------------------------
/// \brief Are array values written as binary?
/// \return If the array values will be written as binary.
//------------------------------------------------------------------------------
bool DaStreamWriter::IsBinary() const
{
  return m_impl->m_binaryArrays;
} // DaStreamWriter::IsBinary
//------------------------------------------------------------------------------
/// \brief Write a given line to a stream.
/// \param a_name The line of text to be written.
//------------------------------------------------------------------------------
void DaStreamWriter::WriteNamedLine(const char* a_name)
{
  iWriteLine(m_impl->m_outStream, a_name);
} // DaStreamWriter::WriteNamedLine
//------------------------------------------------------------------------------
/// \brief Write a given line to a stream.
/// \param a_line The line of text to be written.
//------------------------------------------------------------------------------
void DaStreamWriter::WriteLine(const std::string& a_line)
{
  iWriteLine(m_impl->m_outStream, a_line);
} // DaStreamWriter::WriteLine
//------------------------------------------------------------------------------
/// \brief Write a named double line value.
/// \param a_name The name to be written before the value.
/// \param a_val The double value to write.
//------------------------------------------------------------------------------
void DaStreamWriter::WriteDoubleLine(const char* a_name, double a_val)
{
  iWriteLine(m_impl->m_outStream, a_name, &a_val);
} // DaStreamWriter::WriteDoubleLine
//------------------------------------------------------------------------------
/// \brief Write a named word line.
/// \param a_name The name to be written before the value.
/// \param a_val The word.
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void DaStreamWriter::WriteStringLine(const char* a_name, const std::string& a_val)
{
  iWriteLine(m_impl->m_outStream, a_name, &a_val);
} // DaStreamWriter::WriteStringLine
//------------------------------------------------------------------------------
/// \brief Write a named vector of integers to several lines.
/// \param a_name The name to be written before the value.
/// \param a_vec The vector of integers.
//------------------------------------------------------------------------------
void DaStreamWriter::WriteVecInt(const char* a_name, const VecInt& a_vec)
{
  iWriteVec(m_impl->m_outStream, a_name, a_vec);
} // DaStreamWriter::WriteVecInt
//------------------------------------------------------------------------------
/// \brief Write a named pair of words to a line.
/// \param a_name The name to be written before the value.
/// \param a_val1 The first word.
/// \param a_val2 The second word.
//------------------------------------------------------------------------------
void DaStreamWriter::Write2StringLine(
                        const char* a_name,
                        const std::string& a_val1,
                        const std::string& a_val2)
{
  iWriteLine(m_impl->m_outStream, a_name, &a_val1, &a_val2);
} // DaStreamWriter::Write2StringLine
//------------------------------------------------------------------------------
/// \brief Write a named triplet of words to a line.
/// \param a_name The name to be written before the value.
/// \param a_val1 The first word.
/// \param a_val2 The second word.
/// \param a_val3 The third word.
//------------------------------------------------------------------------------
void DaStreamWriter::Write3StringLine(
                        const char* a_name,
                        const std::string& a_val1,
                        const std::string& a_val2,
                        const std::string& a_val3)
{
  iWriteLine(m_impl->m_outStream, a_name, &a_val1, &a_val2, &a_val3);
} // DaStreamWriter::Write3StringLine
//------------------------------------------------------------------------------
/// \brief Write a named triplet of doubles to a line.
/// \param a_name The name to be written before the value.
/// \param a_val1 The first double.
/// \param a_val2 The second double.
/// \param a_val3 The third double.
//------------------------------------------------------------------------------
void DaStreamWriter::Write3DoubleLine(
                        const char* a_name,
                        const double& a_val1,
                        const double& a_val2,
                        const double& a_val3)
{
  iWriteLine(m_impl->m_outStream, a_name, &a_val1, &a_val2, &a_val3);
} // DaStreamWriter::Write3DoubleLine
//------------------------------------------------------------------------------
/// \brief Write a named integer value to a line.
/// \param a_name The name to be written before the value.
/// \param a_val The integer value.
//------------------------------------------------------------------------------
void DaStreamWriter::WriteIntLine(const char* a_name, int a_val)
{
  iWriteLine(m_impl->m_outStream, a_name, &a_val);
} // DaStreamWriter::WriteIntLine
//------------------------------------------------------------------------------
/// \brief Write a named vector of doubles to multiple lines.
/// \param a_name The name to be written before the value.
/// \param a_vec The vector of doubles.
//------------------------------------------------------------------------------
void DaStreamWriter::WriteVecDbl(const char* a_name, const VecDbl& a_vec)
{
  iWriteVec(m_impl->m_outStream, a_name, a_vec);
} // DaStreamWriter::WriteVecDbl
//------------------------------------------------------------------------------
/// \brief Write a named vector of Pt3d to multiple lines.
/// \param a_name The name to be written before the value.
/// \param a_points The vector of Pt3d.
//------------------------------------------------------------------------------
void DaStreamWriter::WriteVecPt3d(const char* a_name, const VecPt3d& a_points)
{
  // write name and size of vector
  const size_t size = a_points.size();
  iWriteLine(m_impl->m_outStream, a_name, &size);

  // write each indented point and XYZ (why not remove POINT text?)
  for (size_t i = 0; i < a_points.size(); ++i)
  {
    const Pt3d& point = a_points[i];
    std::string sx(STRstd(point.x));
    std::string sy(STRstd(point.y));
    std::string sz(STRstd(point.z));
    m_impl->m_outStream << "  POINT " << i << ' ' << sx << ' ' << sy << ' ' << sz << '\n';
  }
} // DaStreamWriter::WriteVecPt3d

} // namespace xms

#if CXX_TEST
///////////////////////////////////////////////////////////////////////////////
// TESTS
///////////////////////////////////////////////////////////////////////////////

#include <xmsgrid/dataio/daStreamIo.t.h>

using namespace xms;

////////////////////////////////////////////////////////////////////////////////
/// \class StreamIoUnitTests
/// \brief Tests for Stream IO utilities.
////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
/// \brief Test ReadNamedLine.
//------------------------------------------------------------------------------
void StreamIoUnitTests::testReadNamedLine()
{
  // test read with CR LF, LF, CR, and no line endings
  std::string lineEndingsInput =
    "Windows Line\r\n"
    "Unix Line\n"
    "Mac Line\r"
    "Last Line";
  std::istringstream inStream(lineEndingsInput);
  DaStreamReader reader(inStream);
  TS_ASSERT(reader.ReadNamedLine("Windows Line"));
  TS_ASSERT(reader.ReadNamedLine("Unix Line"));
  TS_ASSERT(reader.ReadNamedLine("Mac Line"));
  TS_ASSERT(reader.ReadNamedLine("Last Line"));
} // StreamIoUnitTests::testReadNamedLine
//------------------------------------------------------------------------------
/// \brief Test WriteLine and ReadLine.
//------------------------------------------------------------------------------
void StreamIoUnitTests::testReadWriteLine()
{
  std::ostringstream outputStream;
  DaStreamWriter writer(outputStream);
  writer.WriteLine("daWriteLine version 1.0");
  std::string expected = "daWriteLine version 1.0\n";
  std::string found = outputStream.str();
  TS_ASSERT_EQUALS(expected, found);

  std::istringstream inputStream(outputStream.str());
  DaStreamReader reader(inputStream);
  std::string value;
  reader.ReadLine(value);
  expected = "daWriteLine version 1.0";
  TS_ASSERT_EQUALS(expected, value);

  // test read with CR LF, LF, CR, and no line endings
  std::string lineEndingsInput =
    "Windows Line\r\n"
    "Unix Line\n"
    "Mac Line\r"
    "Last Line";
  std::istringstream endingsIn(lineEndingsInput);
  DaStreamReader readerIn(endingsIn);
  readerIn.ReadLine(value);
  TS_ASSERT_EQUALS("Windows Line", value);
  readerIn.ReadLine(value);
  TS_ASSERT_EQUALS("Unix Line", value);
  readerIn.ReadLine(value);
  TS_ASSERT_EQUALS("Mac Line", value);
  readerIn.ReadLine(value);
  TS_ASSERT_EQUALS("Last Line", value);
} // StreamIoUnitTests::testReadWriteLine
//------------------------------------------------------------------------------
/// \brief Test daWriteStringLine and ReadStringLine.
//------------------------------------------------------------------------------
void StreamIoUnitTests::testReadWriteStringLine()
{
  std::ostringstream outputStream;
  DaStreamWriter writer(outputStream);
  const char* name = "LINE_NAME";
  std::string expectedValue = "VALUE";
  writer.WriteStringLine(name, expectedValue);
  std::string expected = "LINE_NAME VALUE\n";
  std::string found = outputStream.str();
  TS_ASSERT_EQUALS(expected, found);

  std::istringstream inputStream(outputStream.str());
  DaStreamReader reader(inputStream);
  std::string foundValue;
  TS_ASSERT(reader.ReadStringLine(name, foundValue));
  TS_ASSERT_EQUALS(expectedValue, foundValue);
} // StreamIoUnitTests::testReadWriteStringLine
//------------------------------------------------------------------------------
/// \brief Test daWrite2StringLine and Read2StringLine.
//------------------------------------------------------------------------------
void StreamIoUnitTests::testReadWrite2StringLine()
{
  std::ostringstream outputStream;
  DaStreamWriter writer(outputStream);
  const char* name = "LINE_NAME";
  std::string expectedValue1 = "VALUE1";
  std::string expectedValue2 = "VALUE2";
  writer.Write2StringLine(name, expectedValue1, expectedValue2);
  std::string expected = "LINE_NAME VALUE1 VALUE2\n";
  std::string found = outputStream.str();
  TS_ASSERT_EQUALS(expected, found);

  std::istringstream inputStream(outputStream.str());
  DaStreamReader reader(inputStream);
  std::string foundValue1;
  std::string foundValue2;
  TS_ASSERT(reader.Read2StringLine(name, foundValue1, foundValue2));
  TS_ASSERT_EQUALS(expectedValue1, foundValue1);
  TS_ASSERT_EQUALS(expectedValue2, foundValue2);
} // StreamIoUnitTests::testReadWrite2StringLine
//------------------------------------------------------------------------------
/// \brief Test daWrite3StringLine and Read3StringLine.
//------------------------------------------------------------------------------
void StreamIoUnitTests::testReadWrite3StringLine()
{
  std::ostringstream outputStream;
  DaStreamWriter writer(outputStream);
  const char* name = "LINE_NAME";
  std::string expectedValue1 = "VALUE1";
  std::string expectedValue2 = "VALUE2";
  std::string expectedValue3 = "VALUE3";
  writer.Write3StringLine(name, expectedValue1, expectedValue2, expectedValue3);
  std::string expected = "LINE_NAME VALUE1 VALUE2 VALUE3\n";
  std::string found = outputStream.str();
  TS_ASSERT_EQUALS(expected, found);

  std::istringstream inputStream(outputStream.str());
  DaStreamReader reader(inputStream);
  std::string foundValue1;
  std::string foundValue2;
  std::string foundValue3;
  TS_ASSERT(reader.Read3StringLine(name, foundValue1, foundValue2, foundValue3));
  TS_ASSERT_EQUALS(expectedValue1, foundValue1);
  TS_ASSERT_EQUALS(expectedValue2, foundValue2);
  TS_ASSERT_EQUALS(expectedValue3, foundValue3);
} // StreamIoUnitTests::testReadWrite3StringLine
//------------------------------------------------------------------------------
/// \brief Test ReadIntFromLine.
//------------------------------------------------------------------------------
void StreamIoUnitTests::testReadIntFromLine()
{
  std::string line;

  // read from front
  int intValue;
  line = "1 -1 A 2.0 B 4";
  TS_ASSERT(DaStreamReader::ReadIntFromLine(line, intValue));
  TS_ASSERT_EQUALS(1, intValue);
  TS_ASSERT_EQUALS(" -1 A 2.0 B 4", line);

  // read second value (with a space)
  line = " -1 A 2.0 B 4";
  TS_ASSERT(DaStreamReader::ReadIntFromLine(line, intValue));
  TS_ASSERT_EQUALS(-1, intValue);
  TS_ASSERT_EQUALS(" A 2.0 B 4", line);

  // fails to read alpha (int value stays the same)
  line = " A 2.0 B 4";
  intValue = -1;
  TS_ASSERT(!DaStreamReader::ReadIntFromLine(line, intValue));
  TS_ASSERT_EQUALS(-1, intValue);
  TS_ASSERT_EQUALS(" A 2.0 B 4", line);

  // fails to read double (int value stays the same)
  line = " A 2.0 B 4";
  intValue = -1;
  TS_ASSERT(!DaStreamReader::ReadIntFromLine(line, intValue));
  TS_ASSERT_EQUALS(-1, intValue);
  TS_ASSERT_EQUALS(" A 2.0 B 4", line);

  // fails with empty line
  line = "";
  intValue = -1;
  TS_ASSERT(!DaStreamReader::ReadIntFromLine(line, intValue));
  TS_ASSERT_EQUALS(-1, intValue);
  TS_ASSERT_EQUALS("", line);
} // StreamIoUnitTests::testReadIntFromLine
//------------------------------------------------------------------------------
/// \brief Test ReadStringFromLine.
//------------------------------------------------------------------------------
void StreamIoUnitTests::testReadStringFromLine()
{
  std::string line;

  // read from front
  std::string stringValue;
  line = "value1 value2 3";
  TS_ASSERT(DaStreamReader::ReadStringFromLine(line, stringValue));
  TS_ASSERT_EQUALS("value1", stringValue);
  TS_ASSERT_EQUALS(" value2 3", line);

  // read second value (with a space)
  line = " value2 value3";
  TS_ASSERT(DaStreamReader::ReadStringFromLine(line, stringValue));
  TS_ASSERT_EQUALS("value2", stringValue);
  TS_ASSERT_EQUALS(" value3", line);

  // read last value
  line = "3";
  TS_ASSERT(DaStreamReader::ReadStringFromLine(line, stringValue));
  TS_ASSERT_EQUALS("3", stringValue);
  TS_ASSERT_EQUALS("", line);

  // fails with empty line (string value stays the same)
  line = "";
  stringValue = "3";
  TS_ASSERT(!DaStreamReader::ReadStringFromLine(line, stringValue));
  TS_ASSERT_EQUALS("3", stringValue);
  TS_ASSERT_EQUALS("", line);
} // StreamIoUnitTests::testReadStringFromLine
//------------------------------------------------------------------------------
/// \brief Test ReadDoubleFromLine.
//------------------------------------------------------------------------------
void StreamIoUnitTests::testReadDoubleFromLine()
{
  std::string line;

  // read from front
  double doubleValue;
  line = "1.1 -1.0e-3 3";
  TS_ASSERT(DaStreamReader::ReadDoubleFromLine(line, doubleValue));
  TS_ASSERT_EQUALS(1.1, doubleValue);
  TS_ASSERT_EQUALS(" -1.0e-3 3", line);

  // read second value (with a space)
  line = " -1.0e-3 3";
  TS_ASSERT(DaStreamReader::ReadDoubleFromLine(line, doubleValue));
  TS_ASSERT_EQUALS(-1.0e-3, doubleValue);
  TS_ASSERT_EQUALS(" 3", line);

  // read last value
  line = "3";
  TS_ASSERT(DaStreamReader::ReadDoubleFromLine(line, doubleValue));
  TS_ASSERT_EQUALS(3, doubleValue);
  TS_ASSERT_EQUALS("", line);

  // fails with empty line (string value stays the same)
  line = "";
  doubleValue = 3;
  TS_ASSERT(!DaStreamReader::ReadDoubleFromLine(line, doubleValue));
  TS_ASSERT_EQUALS(3, doubleValue);
  TS_ASSERT_EQUALS("", line);
} // StreamIoUnitTests::testReadDoubleFromLine
//------------------------------------------------------------------------------
/// \brief Test daWriteIntLine and ReadIntLine.
//------------------------------------------------------------------------------
void StreamIoUnitTests::testReadWriteIntLine()
{
  std::ostringstream outputStream;
  DaStreamWriter writer(outputStream);
  const char* name = "LINE_NAME";
  const int expect = 22;
  writer.WriteIntLine(name, expect);
  std::string outputExpected = "LINE_NAME 22\n";
  std::string outputFound = outputStream.str();
  TS_ASSERT_EQUALS(outputExpected, outputFound);

  std::istringstream inputStream(outputStream.str());
  DaStreamReader reader(inputStream);
  int found;
  TS_ASSERT(reader.ReadIntLine(name, found));
  TS_ASSERT_EQUALS(expect, found);
} // StreamIoUnitTests::testReadWriteIntLine
//------------------------------------------------------------------------------
/// \brief Test daWriteDoubleLine and ReadDoubleLine.
//------------------------------------------------------------------------------
void StreamIoUnitTests::testReadWriteDoubleLine()
{
  std::ostringstream outputStream;
  DaStreamWriter writer(outputStream);
  const char* name = "LINE_NAME";
  const double expect = 22.1;
  writer.WriteDoubleLine(name, expect);
  std::string outputExpected = "LINE_NAME 22.1\n";
  std::string outputFound = outputStream.str();
  TS_ASSERT_EQUALS(outputExpected, outputFound);

  std::istringstream inputStream(outputStream.str());
  DaStreamReader reader(inputStream);
  double found;
  TS_ASSERT(reader.ReadDoubleLine(name, found));
  TS_ASSERT_EQUALS(expect, found);
} // StreamIoUnitTests::testReadWriteDoubleLine
//------------------------------------------------------------------------------
/// \brief Test daWrite3DoubleLine and reader.Read3DoubleLine.
//------------------------------------------------------------------------------
void StreamIoUnitTests::testReadWrite3DoubleLine()
{
  std::ostringstream outputStream;
  DaStreamWriter writer(outputStream);
  const char* name = "LINE_NAME";
  const double expect1 = 22.1;
  const double expect2 = 22.2;
  const double expect3 = 22.3;
  writer.Write3DoubleLine(name, expect1, expect2, expect3);
  std::string outputExpected = "LINE_NAME 22.1 22.2 22.3\n";
  std::string outputFound = outputStream.str();
  TS_ASSERT_EQUALS(outputExpected, outputFound);

  std::istringstream inputStream(outputStream.str());
  DaStreamReader reader(inputStream);
  double found1;
  double found2;
  double found3;
  TS_ASSERT(reader.Read3DoubleLine(name, found1, found2, found3));
  TS_ASSERT_EQUALS(expect1, found1);
  TS_ASSERT_EQUALS(expect2, found2);
  TS_ASSERT_EQUALS(expect3, found3);
} // StreamIoUnitTests::testReadWrite3DoubleLine
//------------------------------------------------------------------------------
/// \brief Test daWriteVecInt and ReadVecInt.
//------------------------------------------------------------------------------
void StreamIoUnitTests::testReadWriteVecInt()
{
  std::ostringstream outputStream;
  DaStreamWriter writer(outputStream);
  const char* name = "VECTOR_NAME";
  const VecInt expect = {1, 2, 3};
  writer.WriteVecInt(name, expect);
  std::string outputExpected =
    "VECTOR_NAME 3\n"
    "  1\n"
    "  2\n"
    "  3\n";
  std::string outputFound = outputStream.str();
  TS_ASSERT_EQUALS(outputExpected, outputFound);

  std::istringstream inputStream(outputStream.str());
  DaStreamReader reader(inputStream);
  VecInt found;
  TS_ASSERT(reader.ReadVecInt(name, found));
  TS_ASSERT_EQUALS(expect, found);
} // StreamIoUnitTests::testReadWriteVecInt
//------------------------------------------------------------------------------
/// \brief Test daWriteVecDbl and ReadVecDbl.
//------------------------------------------------------------------------------
void StreamIoUnitTests::testReadWriteVecDbl()
{
  std::ostringstream outputStream;
  DaStreamWriter writer(outputStream);
  const char* name = "VECTOR_NAME";
  const VecDbl expect = {1.1, 2.2, 3.3};
  writer.WriteVecDbl(name, expect);
  std::string outputExpected =
    "VECTOR_NAME 3\n"
    "  1.1\n"
    "  2.2\n"
    "  3.3\n";
  std::string outputFound = outputStream.str();
  TS_ASSERT_EQUALS(outputExpected, outputFound);

  std::istringstream inputStream(outputStream.str());
  DaStreamReader reader(inputStream);
  VecDbl found;
  TS_ASSERT(reader.ReadVecDbl(name, found));
  TS_ASSERT_EQUALS(expect, found);
} // StreamIoUnitTests::testReadWriteVecDbl
//------------------------------------------------------------------------------
/// \brief Test daWriteVecPt3d and ReadVecPt3d.
//------------------------------------------------------------------------------
void StreamIoUnitTests::testReadWriteVecPt3d()
{
  std::ostringstream outputStream;
  DaStreamWriter writer(outputStream);
  const char* name = "VECTOR_NAME";
  const VecPt3d expect = {
    {1.1, 1.2, 1.3},
    {2.1, 2.2, 2.3},
  };
  writer.WriteVecPt3d(name, expect);
  std::string outputExpected =
    "VECTOR_NAME 2\n"
    "  POINT 0 1.1 1.2 1.3\n"
    "  POINT 1 2.1 2.2 2.3\n";
  std::string outputFound = outputStream.str();
  TS_ASSERT_EQUALS(outputExpected, outputFound);

  std::istringstream inputStream(outputStream.str());
  DaStreamReader reader(inputStream);
  VecPt3d found;
  TS_ASSERT(reader.ReadVecPt3d(name, found));
  TS_ASSERT_EQUALS(expect, found);
} // StreamIoUnitTests::testReadWriteVecPt3d

#endif
