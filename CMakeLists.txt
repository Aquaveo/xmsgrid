cmake_minimum_required(VERSION 3.11.0)
cmake_policy(SET CMP0015 NEW) # Link Directory Pathing
cmake_policy(SET CMP0091 NEW)
set(CMAKE_DEBUG_POSTFIX _d)
set(CMAKE_CXX_STANDARD 17)

project(xmsgridlib C CXX)

# ---------------------------------------------------
# Cache Variables
# ---------------------------------------------------
set(BUILD_TESTING NO CACHE BOOL "Enable/Disable testing")
set(IS_CONDA_BUILD NO CACHE BOOL "Set this if you want to make a conda package.")
set(IS_EMSCRIPTEN_BUILD NO CACHE BOOL "Set this to build with emscripten using cmake.")
set(PYTHON_TARGET_VERSION 3.10 CACHE STRING "Version of python to link to for python wrapping.")
set(CONDA_PREFIX "" CACHE PATH "Path to the conda environment used to build.")
set(IS_PYTHON_BUILD NO CACHE BOOL "Set this if you want to build the python bindings.")
set(XMS_TEST_PATH ${PROJECT_SOURCE_DIR}/test_files/ CACHE PATH "Path to test files for testing")
set(XMS_VERSION "99.99.99" CACHE STRING "Library Version")
set(USE_TYPEDEF_WCHAR_T NO CACHE BOOL "Define wchar_t as a typedef")

# ---------------------------------------------------
# Static library sources
# ---------------------------------------------------
set(xmsgrid_sources
  # Geometry
  xmsgrid/geometry/geoms.cpp
  xmsgrid/geometry/GmExtents.cpp
  xmsgrid/geometry/GmMultiPolyIntersectionSorterTerse.cpp
  xmsgrid/geometry/GmMultiPolyIntersector.cpp
  xmsgrid/geometry/GmPolygon.cpp
  xmsgrid/geometry/GmPolyLinePtRedistributer.cpp
  xmsgrid/geometry/GmPtSearch.cpp
  xmsgrid/geometry/GmTriSearch.cpp
  # Matrices
  xmsgrid/matrices/matrix.cpp
  # Triangulate
  xmsgrid/triangulate/TrBreaklineAdder.cpp
  xmsgrid/triangulate/triangles.cpp
  xmsgrid/triangulate/TrTin.cpp
  xmsgrid/triangulate/TrTriangulator.cpp
  xmsgrid/triangulate/TrTriangulatorPoints.cpp
  xmsgrid/triangulate/detail/TrAutoFixFourTrianglePts.cpp
  xmsgrid/triangulate/detail/triangulate.cpp
  xmsgrid/triangulate/detail/TrOuterTriangleDeleter.cpp
  # UGrid
  xmsgrid/ugrid/detail/UGridClipper.cpp
  xmsgrid/ugrid/detail/XmGeometry.cpp
  xmsgrid/ugrid/XmEdge.cpp
  xmsgrid/ugrid/XmUGrid.cpp
  xmsgrid/ugrid/XmUGridUtils.cpp
)

set(xmsgrid_headers
  # Geometry
  xmsgrid/geometry/geoms.h
  xmsgrid/geometry/GmBoostTypes.h
  xmsgrid/geometry/GmExtents.h
  xmsgrid/geometry/GmMultiPolyIntersectionSorter.h
  xmsgrid/geometry/GmMultiPolyIntersectionSorterTerse.h
  xmsgrid/geometry/GmMultiPolyIntersector.h
  xmsgrid/geometry/GmMultiPolyIntersectorData.h
  xmsgrid/geometry/GmPolygon.h
  xmsgrid/geometry/GmPolyLinePtRedistributer.h
  xmsgrid/geometry/GmPtSearch.h
  xmsgrid/geometry/GmTriSearch.h
  # Matrices
  xmsgrid/matrices/matrix.h
  # Triangulate
  xmsgrid/triangulate/TrBreaklineAdder.h
  xmsgrid/triangulate/triangles.h
  xmsgrid/triangulate/TrTin.h
  xmsgrid/triangulate/TrTriangulator.h
  xmsgrid/triangulate/TrTriangulatorPoints.h
  xmsgrid/triangulate/detail/TrAutoFixFourTrianglePts.h
  xmsgrid/triangulate/detail/triangulate.h
  xmsgrid/triangulate/detail/TrOuterTriangleDeleter.h
  # Ugrid
  xmsgrid/ugrid/detail/UGridClipper.h
  xmsgrid/ugrid/detail/XmGeometry.h
  xmsgrid/ugrid/XmEdge.h
  xmsgrid/ugrid/XmUGrid.h
  xmsgrid/ugrid/XmUGridUtils.h
)

# ---------------------------------------------------
# CXX Standard
# ---------------------------------------------------
if (APPLE OR WIN32 OR IS_EMSCRIPTEN_BUILD)
    # Target C++17 on MacOS and Windows. If building with version of Visual Studio without
    # support, has no effect.
    set(CMAKE_CXX_STANDARD 17)
else()
    set(CMAKE_CXX_STANDARD 11)
endif()

# ---------------------------------------------------
# Compiler Flags
# ---------------------------------------------------
if (APPLE)
    set(CMAKE_POSITION_INDEPENDENT_CODE False)
    add_compile_definitions(_LIBCPP_ENABLE_CXX17_REMOVED_UNARY_BINARY_FUNCTION)
else()
    set(CMAKE_POSITION_INDEPENDENT_CODE True)
endif()

if(IS_PYTHON_BUILD AND BUILD_TESTING)
    message(FATAL_ERROR "Cannot build python module when testing is enabled")
endif()


add_definitions(-DXMS_VERSION=\"${XMS_VERSION}\")


if(IS_CONDA_BUILD)
    include(${CMAKE_CURRENT_LIST_DIR}/condabuildinfo.cmake)
elseif(IS_EMSCRIPTEN_BUILD)
    include(${CMAKE_CURRENT_LIST_DIR}/emscriptenbuildinfo.cmake)
else() # If we are not using conda or emscripten, we are using conan
    # Conan 2 setup
    find_package(Boost REQUIRED)
    find_package(ZLIB REQUIRED)
    set(EXT_INCLUDE_DIRS ${Boost_INCLUDE_DIRS})
    list(APPEND EXT_INCLUDE_DIRS ${ZLIB_INCLUDE_DIRS})
    set(EXT_LIB_DIRS ${Boost_LIBRARY_DIRS})
    list(APPEND EXT_LIB_DIRS ${ZLIB_LIBRARY_DIRS})  
    set(EXT_LIBS ${Boost_LIBRARIES})
    list(APPEND EXT_LIBS ${ZLIB_LIBRARIES})
endif()


if(WIN32)
    string(COMPARE EQUAL "${CONAN_SETTINGS_COMPILER_RUNTIME}" "MT" USES_MT)
    if(NOT USES_MT)
        string(COMPARE EQUAL "${CONAN_SETTINGS_COMPILER_RUNTIME}" "MTd" USES_MT)
    endif()

    if(USE_TYPEDEF_WCHAR_T)
        add_definitions(/Zc:wchar_t-)  # Treat wchar_t as a typedef
    endif()

    add_definitions(/D BOOST_ALL_NO_LIB)

    if(USES_MT)
        set(CompilerFlags
                CMAKE_CXX_FLAGS
                CMAKE_CXX_FLAGS_DEBUG
                CMAKE_CXX_FLAGS_RELEASE
                CMAKE_C_FLAGS
                CMAKE_C_FLAGS_DEBUG
                CMAKE_C_FLAGS_RELEASE
        )
        foreach(CompilerFlag ${CompilerFlags})
            string(REPLACE "/MD" "/MT" ${CompilerFlag} "${${CompilerFlag}}")
        endforeach()
    endif()
endif()


# ---------------------------------------------------
# Setup Pybind11
# ---------------------------------------------------
if(IS_PYTHON_BUILD)
    find_package(pybind11 REQUIRED)
    list(APPEND EXT_INCLUDE_DIRS
            ${pybind11_INCLUDE_DIR}
    )

    find_package(PythonLibsNew ${PYTHON_TARGET_VERSION} EXACT REQUIRED)

    # Have to add this after conda because it doesn't get the path for pybind if we don't.
    list(APPEND EXT_INCLUDE_DIRS
            ${PYTHON_INCLUDE_DIRS}
    )
endif()

# ---------------------------------------------------
# Tests
# ---------------------------------------------------
if (BUILD_TESTING)
    message(STATUS "Adding test dependencies...")
    add_definitions(-DXMS_TEST_PATH="${XMS_TEST_PATH}/")
    add_definitions(-DCXX_TEST -DCXXTEST4)

   list(APPEND xmsgrid_sources
       # Geometry
       xmsgrid/geometry/geoms.t.h
       xmsgrid/geometry/GmExtents.t.h
       xmsgrid/geometry/GmMultiPolyIntersector.t.h
       xmsgrid/geometry/GmPolygon.t.h
       xmsgrid/geometry/GmPolyLinePtRedistributer.t.h
       xmsgrid/geometry/GmPtSearch.t.h
       xmsgrid/geometry/GmTriSearch.t.h
       # Triangulate
       xmsgrid/triangulate/TrBreaklineAdder.t.h
       xmsgrid/triangulate/TrTin.t.h
       xmsgrid/triangulate/TrTriangulatorPoints.t.h
       xmsgrid/triangulate/detail/TrAutoFixFourTrianglePts.t.h
       xmsgrid/triangulate/detail/TrOuterTriangleDeleter.t.h
       # UGrid
       xmsgrid/ugrid/detail/UGridClipper.t.h
       xmsgrid/ugrid/XmEdge.t.h
       xmsgrid/ugrid/XmUGrid.t.h
       xmsgrid/ugrid/XmUGridUtils.t.h
   )

   find_package(cxxtest REQUIRED)
   list(APPEND EXT_INCLUDE_DIRS ${cxxtest_INCLUDE_DIRS})
   list(APPEND EXT_LIB_DIRS ${cxxtest_LIBRARY_DIRS})  
   list(APPEND EXT_LIBS ${cxxtest_LIBRARIES})
    
    if(cxxtest_FOUND)
        include("FindCxxTest")
        include_directories(${CXXTEST_INCLUDE_DIR})
        enable_testing()

        set(cxxtest_TESTGEN_ARGS --xunit-printer)
        file(GLOB_RECURSE test_headers ${CMAKE_CURRENT_LIST_DIR}/xmsgrid/*.t.h)
        message(STATUS "Prefix Path: ${CMAKE_PREFIX_PATH}")
        message(STATUS "Module Path: ${CMAKE_MODULE_PATH}")
        CXXTEST_ADD_TEST(
                runner runner.cpp ${test_headers}
        )
        target_link_libraries(runner ${PROJECT_NAME})

        if(WIN32)
            set(RUNNERNAME "runner.exe")
        else()
            set(RUNNERNAME "runner")
        endif()
    endif()
endif ()


# ---------------------------------------------------
# Find XMS Packages
# ---------------------------------------------------
find_package(xmscore REQUIRED)
list(APPEND EXT_INCLUDE_DIRS ${xmscore_INCLUDE_DIRS})
list(APPEND EXT_LIB_DIRS ${xmscore_LIBRARY_DIRS})
list(APPEND EXT_LIBS ${xmscore_LIBRARIES})


# ---------------------------------------------------
# List and set include and lib directories
# ---------------------------------------------------
message("External Include Dirs: ${EXT_INCLUDE_DIRS}")
message("External Lib Dirs: ${EXT_LIB_DIRS}")
message("Extneral Libs: ${EXT_LIBS}")

include_directories(${CMAKE_CURRENT_LIST_DIR})
include_directories(${EXT_INCLUDE_DIRS})
link_directories(${EXT_LIB_DIRS})

# ---------------------------------------------------
# Setup Pybind Sources
# ---------------------------------------------------
if(IS_PYTHON_BUILD)
  # Pybind11 sources
  set(xmsgrid_py
    xmsgrid/python/xmsgrid_py.cpp
    # Geometry
    xmsgrid/python/geometry/geometry_py.cpp
    xmsgrid/python/geometry/GmMultiPolyIntersector_py.cpp
    xmsgrid/python/geometry/GmTriSearch_py.cpp
    # Triangulate
    xmsgrid/python/triangulate/triangulate_py.cpp
    xmsgrid/python/triangulate/TrTin_py.cpp
    #UGrid
    xmsgrid/python/ugrid/ugrid_py.cpp
    xmsgrid/python/ugrid/XmUGrid_py.cpp
    xmsgrid/python/ugrid/XmUGridUtils_py.cpp
  )

  set(xmsgrid_py_headers
    # Geometry
    xmsgrid/python/geometry/geometry_py.h
    # Triangulate
    xmsgrid/python/triangulate/triangulate_py.h
    xmsgrid/python/ugrid/ugrid_py.h
  )
endif()


# Static library
add_library(${PROJECT_NAME} STATIC
  ${xmsgrid_sources} ${xmsgrid_headers}
)
target_include_directories(${PROJECT_NAME}
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include/>
    ${Boost_INCLUDE_DIR}
 )
find_package(Threads REQUIRED)
target_link_libraries(${PROJECT_NAME}
  ${EXT_LIBS}
)
target_link_libraries(${PROJECT_NAME}
  ${CMAKE_THREAD_LIBS_INIT}
)
if(UNIX AND NOT APPLE)
    target_link_libraries(${PROJECT_NAME} rt)
endif()

if(IS_PYTHON_BUILD)
    pybind11_add_module(_xmsgrid
      ${xmsgrid_py} ${xmsgrid_py_headers}
    )
    target_include_directories(_xmsgrid
        PRIVATE
          ${EXT_LIBS}
          ${PYTHON_INCLUDE_DIRS}
    )
    target_link_libraries(_xmsgrid
      PRIVATE
        ${EXT_LIBS}
        ${PROJECT_NAME}
    )
    set_target_properties(_xmsgrid PROPERTIES
      LINKER_LANGUAGE CXX
    )

    # Install recipe
    install(
      TARGETS _xmsgrid
      ARCHIVE DESTINATION "_package/xms/grid"
      LIBRARY DESTINATION "_package/xms/grid"
    )

    install(DIRECTORY "_package/" DESTINATION "_package"
             FILES_MATCHING PATTERN "*.py"
             PATTERN "_package/tests" EXCLUDE)
endif()

# Disable Optimization for GCC6 for now... Report issue to gcc and pybind
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" AND IS_PYTHON_BUILD)
  if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL 6 AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS 7)
    Message("Disabling Optimization for GCC 6...")
    STRING(REPLACE "-O3" "" CMAKE_CXX_FLAGS_RELEASE ${CMAKE_CXX_FLAGS_RELEASE})
    STRING(REPLACE "-O3" "" CMAKE_C_FLAGS_RELEASE ${CMAKE_C_FLAGS_RELEASE})
  endif()
endif()

# Use C++14 if VS2015 or later
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC" AND CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL 19)
    message("CMAKE_CXX_STANDARD: ${CMAKE_CXX_STANDARD}")
endif()

# Install recipe
install(
  TARGETS ${PROJECT_NAME}
  ARCHIVE DESTINATION "lib"
  LIBRARY DESTINATION "lib"
)
foreach (header IN LISTS xmsgrid_headers xmsgrid_py_headers)
  get_filename_component(subdir "${header}" DIRECTORY)
  install(
    FILES "${header}"
    DESTINATION "include/${subdir}"
  )
endforeach ()
