set(CMAKE_CXX_STANDARD 11)
cmake_minimum_required(VERSION 3.1.2)
cmake_policy(SET CMP0015 NEW) # Link Directory Pathing
set(CMAKE_DEBUG_POSTFIX _d)

if (APPLE)  
  set(CMAKE_POSITION_INDEPENDENT_CODE False)
else()
  set(CMAKE_POSITION_INDEPENDENT_CODE True)
endif()

set(BUILD_TESTING NO CACHE BOOL "Enable/Disable testing")
set(IS_CONDA_BUILD NO CACHE BOOL "Set this if you want to make a conda package.")
set(CONDA_PREFIX "" CACHE PATH "Path to the conda environment used to build.")
set(IS_PYTHON_BUILD NO CACHE BOOL "Set this if you want to build the python bindings.")
set(XMSGRID_TEST_PATH "../../test_files/" CACHE PATH "Path to test files for testing")

project(xmsgrid C CXX)

if(WIN32)
    if(XMS_BUILD)
        add_definitions(/D _WIN32_WINNT=0x0501)  # Windows XP and higher
        add_definitions(/Zc:wchar_t-)  # Treat wchar_t as built-in type
    else(NOT XMS_BUILD)
        add_definitions(/D BOOST_ALL_NO_LIB)
    endif()
endif()

if(IS_CONDA_BUILD)
  include(${CMAKE_CURRENT_LIST_DIR}/condabuildinfo.cmake)
else() # If we are not using conda, we are using conan
  # Conan setup
  include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
  conan_basic_setup(TARGETS)
  set(EXT_INCLUDE_DIRS ${CONAN_INCLUDE_DIRS})
  set(EXT_LIB_DIRS ${CONAN_LIB_DIRS})
  set(EXT_LIBS ${CONAN_LIBS})
endif(IS_CONDA_BUILD)

message("External Include Dirs: ${EXT_INCLUDE_DIRS}")
message("External Lib Dirs: ${EXT_LIB_DIRS}")
message("Extneral Libs: ${EXT_LIBS}")

include_directories(${CMAKE_CURRENT_LIST_DIR})
include_directories(${EXT_INCLUDE_DIRS})
link_directories(${EXT_LIB_DIRS})

# Static library sources
set(xmsgrid_sources
  xmsgrid/ugrid/XmUGrid.cpp
  xmsgrid/ugrid/XmUGridUtils.cpp
  xmsgrid/ugrid/XmConvexHull.cpp
)

set(xmsgrid_headers
  xmsgrid/ugrid/XmUGrid.h
  xmsgrid/ugrid/XmUGridUtils.h
  xmsgrid/ugrid/XmConvexHull.h
)

# Pybind11 sources
set(xmsgrid_py
  xmsgrid/python/xmsgrid_py.cpp
  #UGrid
  xmsgrid/python/ugrid/ugrid_py.cpp
  xmsgrid/python/ugrid/XmUGrid_py.cpp
  xmsgrid/python/ugrid/XmUGridUtils_py.cpp
)

set(xmsgrid_py_headers
  xmsgrid/python/ugrid/ugrid_py.h
)

# Tests
if (BUILD_TESTING)
 add_definitions(-DXMSGRID_TEST_PATH="${XMSGRID_TEST_PATH}/")
 add_definitions(-DCXX_TEST -DCXXTEST4)

 list(APPEND xmsgrid_sources
   xmsgrid/ugrid/XmUGrid.t.h
   xmsgrid/ugrid/XmUGridUtils.t.h
   xmsgrid/ugrid/XmConvexHull.t.h
 )

 find_package(CxxTest)
 if(CXXTEST_FOUND)
   include_directories(${CXXTEST_INCLUDE_DIR})
   enable_testing()

   set(CXXTEST_TESTGEN_ARGS --xunit-printer --have-eh)
   file(GLOB_RECURSE test_headers ${CMAKE_CURRENT_LIST_DIR}/xmsgrid/*.t.h)
   CXXTEST_ADD_TEST(
     runner runner.cpp ${test_headers}
   )
   target_link_libraries(runner ${PROJECT_NAME})
 endif()
endif ()

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
    find_package(PythonLibs REQUIRED)
    message("PYTHON_INCLUDE: ${PYTHON_INCLUDE_DIRS}")
    message("PYTHON_LIBS: ${PYTHON_LIBRARIES}")

    # Pybind11 module
    if(IS_CONDA_BUILD)
        include("${CONDA_PREFIX}/share/cmake/pybind11/pybind11Targets.cmake")
        include("${CONDA_PREFIX}/share/cmake/pybind11/FindPythonLibsNew.cmake")
        include("${CONDA_PREFIX}/share/cmake/pybind11/pybind11Config.cmake")
        include("${CONDA_PREFIX}/share/cmake/pybind11/pybind11ConfigVersion.cmake")
        include("${CONDA_PREFIX}/share/cmake/pybind11/pybind11Tools.cmake")

    else()
        include("${CONAN_PYBIND11_ROOT}/share/cmake/pybind11/pybind11Targets.cmake")
        include("${CONAN_PYBIND11_ROOT}/share/cmake/pybind11/FindPythonLibsNew.cmake")
        include("${CONAN_PYBIND11_ROOT}/share/cmake/pybind11/pybind11Config.cmake")
        include("${CONAN_PYBIND11_ROOT}/share/cmake/pybind11/pybind11ConfigVersion.cmake")
        include("${CONAN_PYBIND11_ROOT}/share/cmake/pybind11/pybind11Tools.cmake")
    endif()

    pybind11_add_module(xmsgrid_py
      ${xmsgrid_py} ${xmsgrid_py_headers}
    )
    target_include_directories(xmsgrid_py
        PRIVATE
          ${EXT_LIBS}
          PYTHON_INCLUDE_DIRS
    )
    target_link_libraries(xmsgrid_py
      PRIVATE
        ${EXT_LIBS}
        ${PROJECT_NAME}
    )
    set_target_properties(xmsgrid_py PROPERTIES
      LINKER_LANGUAGE CXX
    )

    execute_process(COMMAND python -c "import os; print('${PYTHON_SITE_PACKAGES}'.replace('${CONDA_PREFIX}' + os.sep, ''))" OUTPUT_VARIABLE PYTHON_SITE_PACKAGES_TRIMMED OUTPUT_STRIP_TRAILING_WHITESPACE)

    # Install recipe
    install(
      TARGETS xmsgrid_py
      ARCHIVE DESTINATION ${PYTHON_SITE_PACKAGES_TRIMMED}
      LIBRARY DESTINATION ${PYTHON_SITE_PACKAGES_TRIMMED}
    )

endif()


# Install recipe
install(
  TARGETS ${PROJECT_NAME}
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
)
foreach (header IN LISTS xmsgrid_headers xmsgrid_py_headers)
  get_filename_component(subdir "${header}" DIRECTORY)
  install(
    FILES "${header}"
    DESTINATION "include/${subdir}"
  )
endforeach ()