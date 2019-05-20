#pragma once
//------------------------------------------------------------------------------
/// \file XmUGrid.h
/// \brief Contains the XmUGrid Class and supporting data types.
/// \ingroup ugrid
/// \copyright (C) Copyright Aquaveo 2018. Distributed under FreeBSD License
/// (See accompanying file LICENSE or https://aqaveo.com/bsd/license.txt)
//------------------------------------------------------------------------------

//----- Included files ---------------------------------------------------------

// 3. Standard library headers
#include <memory>

// 4. External library headers

// 5. Shared code headers
#include <xmscore/stl/vector.h>

//----- Forward declarations ---------------------------------------------------

//----- Namespace declaration --------------------------------------------------

/// XMS Namespace
namespace xms
{
//----- Forward declarations ---------------------------------------------------

//----- Constants / Enumerations -----------------------------------------------

//----- Structs / Classes ------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
class XmUGridReader
{
public:
  typedef std::pair<const char*, VecInt*> IntArray;
  typedef std::vector<IntArray> IntArrays;

  virtual ~XmUGridReader() = default;
  virtual bool ReadLocations(VecPt3d& a_locations) = 0;
  virtual bool ReadCellstream(VecInt& a_cellstream) = 0;
  virtual bool ReadIntArrays(IntArrays& a_intArrays) = 0;
};

class XmUGridWriter
{
public:
  typedef std::pair<const char*, const VecInt*> ConstIntArray;
  typedef std::vector<ConstIntArray> ConstIntArrays;

  virtual ~XmUGridWriter() = default;
  virtual bool WriteLocations(const VecPt3d& a_locations) = 0;
  virtual bool WriteCellstream(const VecInt& a_cellstream) = 0;
  virtual bool WriteIntArrays(ConstIntArrays& a_intArrays) = 0;
};

} // namespace xms
