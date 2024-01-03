#pragma once
//------------------------------------------------------------------------------
/// \file
/// \brief initializer functions for members of ugrid python module.
/// \copyright (C) Copyright Aquaveo 2018. Distributed under FreeBSD License
/// (See accompanying file LICENSE or https://aquaveo.com/bsd/license.txt)
//------------------------------------------------------------------------------

//----- Included files ---------------------------------------------------------
#include <pybind11/pybind11.h>

//----- Namespace declaration --------------------------------------------------
namespace py = pybind11;

//----- Function declarations --------------------------------------------------
void initUGrid(py::module &);

void initXmEdge(py::module &);
void initXmUGrid(py::module &);
void initXmUGridUtils(py::module &);
