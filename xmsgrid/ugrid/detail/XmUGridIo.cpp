//------------------------------------------------------------------------------
/// \file
/// \ingroup ugrid
/// \copyright (C) Copyright Aquaveo 2018. Distributed under FreeBSD License
/// (See accompanying file LICENSE or https://aqaveo.com/bsd/license.txt)
//------------------------------------------------------------------------------

//----- Included files ---------------------------------------------------------

// 1. Precompiled header

// 2. My own header
#include <xmsgrid/ugrid/detail/XmUGridIo.h>

// 3. Standard library headers
#include <cmath>

// 4. External library headers
#include <boost/container/flat_set.hpp>

// 5. Shared code headers

// 6. Non-shared code headers

//----- Forward declarations ---------------------------------------------------

//----- External globals -------------------------------------------------------

//----- Namespace declaration --------------------------------------------------

//----- Constants / Enumerations -----------------------------------------------

//----- Classes / Structs ------------------------------------------------------

//----- Class / Function definitions -------------------------------------------

/// XMS Namespace
namespace xms
{
} // namespace xms

#ifdef CXX_TEST
//------------------------------------------------------------------------------
// Unit Tests
//------------------------------------------------------------------------------
#include <xmsgrid/ugrid/detail/XmUGridIo.t.h>

#include <xmsgrid/ugrid/XmUGrid.h>

using namespace xms;

class TestIoWriter : public XmUGridWriter
{
public:
  bool WriteLocations(const VecPt3d& a_locations) final
  {
    m_locations = a_locations;
    return true;
  }
  bool WriteCellstream(const VecInt& a_cellstream) final
  {
    m_cellstream = a_cellstream;
    return true;
  }
  bool WriteIntArrays(ConstIntArrays& a_intArrays) final
  {
    for (auto& intArray : a_intArrays)
    {
      m_intNames.push_back(intArray.first);
      m_intArrays.push_back(*intArray.second);
    }
    return true;
  }

  VecPt3d m_locations;
  VecInt m_cellstream;
  std::vector<const char*> m_intNames;
  VecInt2d m_intArrays;
};

class TestIoReader : public XmUGridReader
{
public:
  TestIoReader(TestIoWriter& a_writer)
  : m_writer(a_writer)
  {
  }
  bool ReadLocations(VecPt3d& a_locations) final
  {
    a_locations = m_writer.m_locations;
    return true;
  }
  bool ReadCellstream(VecInt& a_cellstream) final
  {
    a_cellstream = m_writer.m_cellstream;
    return true;
  }
  bool ReadIntArrays(IntArrays& a_intArrays) final
  {
    for (size_t i = 0; i < m_writer.m_intNames.size(); ++i)
    {
      a_intArrays.emplace_back(m_writer.m_intNames[i], &m_writer.m_intArrays[i]);
    }
    return true;
  }

  TestIoWriter& m_writer;
};
//------------------------------------------------------------------------------
/// \brief Test IO support functions for reading and writing an XmUGrid.
//------------------------------------------------------------------------------
void XmUGridIoUnitTests::testWriteAndRead()
{
  BSHP<XmUGrid> original = TEST_XmUBuildHexahedronUgrid(2, 3, 4);
  TestIoWriter ioWriter;
  original->WriteXmUGrid(ioWriter);
  TestIoReader ioReader(ioWriter);
  BSHP<XmUGrid> fromReader = XmUGrid::New(ioReader);
  TS_ASSERT_EQUALS(original->GetLocations(), fromReader->GetLocations());
  TS_ASSERT_EQUALS(original->GetCellstream(), fromReader->GetCellstream());
} // XmUGridIoUnitTests::testWriteAndRead

#endif
