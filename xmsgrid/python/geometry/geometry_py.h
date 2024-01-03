#pragma once
//------------------------------------------------------------------------------
/// \file
/// \brief initializer functions for members of geometry python module.
/// \copyright (C) Copyright Aquaveo 2018. Distributed under FreeBSD License
/// (See accompanying file LICENSE or https://aquaveo.com/bsd/license.txt)
//------------------------------------------------------------------------------

//----- Included files ---------------------------------------------------------
#include <pybind11/pybind11.h>

//----- Namespace declaration --------------------------------------------------
namespace py = pybind11;

//----- Function declarations --------------------------------------------------
void initGeometry(py::module &);

void initGmMultiPolyIntersector(py::module &);
void initGmTriSearch(py::module &);
