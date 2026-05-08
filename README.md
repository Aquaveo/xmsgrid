XMSGrid
========
Grid library for XMS products

Master Branch Status
--------------------

![XmsGrid-CI](https://github.com/Aquaveo/xmsgrid/workflows/XmsGrid-5.0/badge.svg)

Prerequisites
--------------
In order to build this library, you must first have a few things installed.
1. [Conan](https://conan.io)
2. [CMake](https://cmake.org)

Building
--------
See xmscore build [instructions](https://github.com/Aquaveo/xmscore/wiki/Building-Libraries).

Documentation
-------------

[C++ Documentation](https://aquaveo.github.io/xmsgrid/)

[Python Documentation](https://aquaveo.github.io/xmsgrid/pydocs)

Coverage
--------

Coverage runs on Linux/macOS via `dev/coverage.sh`. The script runs an
instrumented Debug build with the C++ test suite, then a release wheel build
with pytest in a clean venv. Outputs:

- `cov-cpp.xml` / `cov-py.xml` — Cobertura XML.
- `build/coverage-html-cpp/` and `build/coverage-html-py/` — browsable HTML.

Prerequisites: `gcovr` (`pip install gcovr`) and a working Conan toolchain
(see Building above). Phase 1 is GCC/Clang-only; Windows MSVC coverage is
not supported.

CI runs the same script and uploads the HTML and XML reports as workflow
artifacts. Coverage is gated by simple percentage thresholds set in
`.github/workflows/Coverage.yaml` (`CPP_COVERAGE_THRESHOLD` and
`PY_COVERAGE_THRESHOLD`); the job fails if either layer falls below.
Initial values are `0` until a baseline is established.
