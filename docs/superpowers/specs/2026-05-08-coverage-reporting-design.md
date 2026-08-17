# Coverage Reporting Design

**Date:** 2026-05-08
**Status:** Approved (design phase)
**Owner:** glarsen@aquaveo.com

## Goal

Add unified line-coverage reporting for both the C++ library and Python
bindings of `xmsgrid`. Reports are generated locally for developer iteration
and in CI for accountability. CI gates merges with simple percentage
thresholds rather than a third-party reporting service. Adopting Codecov or
similar is an open follow-up decision after a baseline is established.

In Phase 1, the C++ and Python layers are measured independently:

- **C++ coverage** is collected from a Debug+testing Conan build, instrumented
  with `--coverage`, with ctest running the C++ test suite.
- **Python coverage** is collected from a separate pytest run against the
  built wheel in a developer-controlled venv, using `pytest-cov`.

Cross-credit (Python tests contributing to C++ coverage numbers) is **out of
scope for Phase 1** and is the headline feature of Phase 2 once the
orchestration is lifted into xmsconan. Three structural constraints in
xmsconan's generated `conanfile.py` make cross-credit costly to implement
without xmsconan changes:

1. `BUILD_TESTING` and `IS_PYTHON_BUILD` are mutually exclusive in the
   generated CMakeLists (`message(FATAL_ERROR ...)`).
2. `pybind=True` is forced to `build_type=Release` by `configure_options()`,
   so there is no Debug pybind build available.
3. The pytest run inside `conanfile.build()` creates a venv with only
   `numpy, wheel, pytest` — `pytest-cov` is not installed.

Phase 1 sidesteps all three by treating the suites as independent. Phase 2
addresses them in xmsconan.

## Non-Goals

- Windows / MSVC coverage. gcov is GCC/Clang only; instrumenting MSVC
  requires OpenCppCoverage or clang-cl source-based coverage and is a
  separate effort.
- Branch coverage. Line coverage only for now.
- Hard coverage gates that block PRs. Reporting is informational; tightening
  is a follow-up.
- Refactoring xmsconan. Phase 1 is repo-local. Generic pieces lift in Phase 2.

## Architecture

```
┌─ C++ Coverage Build (Linux, GCC, Debug, testing=True) ───────┐
│  XMSGRID_COVERAGE=1 → CMake adds --coverage to all targets   │
│  python build.py --filter='{"build_type":"Debug",            │
│                              "testing":true}'                │
│  conanfile.run_cxx_tests() → ctest → *.gcda in conan cache   │
└──────────────────────────────────────────────────────────────┘
                            │
                            ▼
              ┌─────────────────────────────┐
              │ gcovr scans conan build     │
              │ folder → cobertura-cpp.xml  │
              └─────────────────────────────┘

┌─ Python Coverage Run (Linux, against built wheel) ───────────┐
│  python build.py --filter='{"build_type":"Release",          │
│                              "pybind":true}'                 │
│                  --wheel-dir wheelhouse                      │
│  Then in a clean venv:                                        │
│    pip install wheelhouse/*.whl pytest pytest-cov            │
│    pytest --cov=xms.grid --cov-report=xml _package/tests     │
└──────────────────────────────────────────────────────────────┘
                            │
                            ▼
              ┌─────────────────────────────┐
              │ coverage.py → cov-py.xml    │
              └─────────────────────────────┘

                            │
                            ▼
              ┌─────────────────────────────┐
              │ Threshold check             │
              │  gcovr --fail-under-line    │
              │  pytest --cov-fail-under    │
              └─────────────────────────────┘
```

The C++ build is instrumented; the Python wheel build is **not**. Python
coverage measures Python-level wrappers in `_package/xms/grid/` only.
Cross-instrumentation is Phase 2.

The reports (Cobertura XML + browsable HTML) upload as workflow artifacts
on every CI run regardless of pass/fail, so reviewers can always inspect
the numbers. If the team later decides to adopt Codecov or a similar
service, the cobertura XMLs are already in the right format to drop in.

## Components

### 1. CMake option (in `build.toml` `extra_cmake_text`)

```cmake
if(DEFINED ENV{XMSGRID_COVERAGE} AND NOT "$ENV{XMSGRID_COVERAGE}" STREQUAL "")
    if(MSVC)
        message(FATAL_ERROR "Coverage build is GCC/Clang only")
    endif()
    message(STATUS "Coverage instrumentation enabled (XMSGRID_COVERAGE)")
    add_compile_options(--coverage -O0 -g)
    add_link_options(--coverage)
endif()
```

Gated on an environment variable instead of a CMake cache variable so the
coverage script can flip it without needing to pass `--cmake-args` through
xmsconan's `build.py`. No xmsconan generator change required. The variable
flows naturally through Conan's `tools.env.virtualenv` and into the CMake
configure step.

### 2. `dev/coverage.sh`

POSIX shell script (Linux + macOS). Single entry point. Steps:

1. Drop a marker file (`.coverage-mark`) — used to identify build folders
   that this run wrote `.gcda` files into.
2. Run the C++ coverage build:
   ```
   XMSGRID_COVERAGE=1 python build.py \
       --filter='{"build_type":"Debug","testing":true}'
   ```
   The conanfile's `run_cxx_tests()` runs ctest as part of `build()`, so
   this single invocation builds, runs, and emits `.gcda` files into
   `~/.conan2/p/<pkg>/b/build/...`.
3. Run the wheel build:
   ```
   python build.py \
       --filter='{"build_type":"Release","pybind":true}' \
       --wheel-dir wheelhouse
   ```
   No coverage env var here — the wheel is for Python coverage only and
   does not need instrumentation in Phase 1.
4. Discover C++ build folders that received fresh `.gcda` files:
   ```
   find ~/.conan2/p -newer .coverage-mark -name '*.gcda'
   ```
   Walk up from each match to the directory containing `CMakeCache.txt`;
   that's the build folder gcovr needs to scan. Deduplicate the set.
5. Run gcovr against the source root with each discovered build folder:
   ```
   gcovr --root . \
         --filter 'xmsgrid/' \
         --exclude '.*\.t\.h$' \
         --exclude 'xmsgrid/python/.*' \
         --exclude '_package/tests/.*' \
         --xml cov-cpp.xml \
         --html-details build/coverage-html-cpp/index.html \
         <build_folder>
   ```
   When multiple build folders are found (rare in Phase 1, but possible
   if shards are used), emit a JSON intermediate per folder via
   `--json-summary`, then merge with `gcovr --add-tracefile a.json -a b.json`.
6. Run Python tests with coverage in a clean venv, gated by the Python
   threshold:
   ```
   python -m venv .coverage-venv
   .coverage-venv/bin/pip install wheelhouse/*.whl pytest pytest-cov
   .coverage-venv/bin/pytest \
       --cov=xms.grid \
       --cov-report=xml:cov-py.xml \
       --cov-report=html:build/coverage-html-py \
       --cov-fail-under="$PY_COVERAGE_THRESHOLD" \
       _package/tests
   ```
7. The C++ gcovr invocation in step 5 passes
   `--fail-under-line "$CPP_COVERAGE_THRESHOLD"` so it exits non-zero when
   the C++ percentage falls below.
8. When running under GitHub Actions (`$GITHUB_STEP_SUMMARY` set), append
   a short markdown summary noting the configured thresholds. The actual
   percentages appear in the gcovr / pytest output above the summary.

Thresholds default to `0` (no gating) via env vars
`CPP_COVERAGE_THRESHOLD` and `PY_COVERAGE_THRESHOLD`. CI sets them
explicitly in `Coverage.yaml`; locally they can be overridden via env.

A `dev/coverage.bat` is **not** added in Phase 1; Windows coverage is out
of scope.

### 3. `.github/workflows/Coverage.yaml`

Hand-maintained, separate from the xmsconan-generated `XmsGrid-CI.yaml`.
Single job, Linux, GCC, Debug:

- Triggers: `push`, `pull_request`.
- Checks out source, installs xmsconan + gcovr + Python deps, sets up Conan
  login.
- Sets `CPP_COVERAGE_THRESHOLD` and `PY_COVERAGE_THRESHOLD` (initially `0`,
  bumped after the first run establishes a baseline).
- Runs `dev/coverage.sh`. The script's gcovr / pytest steps fail the job
  when either threshold is missed.
- Uploads `cov-cpp.xml` and `cov-py.xml` as the `coverage-xml` artifact and
  the HTML reports as the `coverage-html` artifact, with `if: always()` so
  they are available even on threshold failure.

The job uses the same Conan / devpi secrets as the existing CI workflow.
No reporting-service token is required.

### 4. README update

Short `## Coverage` section: how to run `dev/coverage.sh`, where the HTML
lands, how thresholds are configured.

## Repo Setup (one-time, manual)

None for Phase 1 beyond the secrets the existing workflow already requires.
The first CI run establishes a baseline; bump the threshold env values in
`Coverage.yaml` afterwards to enforce no-regression.

## Reporting Service Decision (deferred)

Whether to adopt Codecov or a similar service — for diff coverage,
trend tracking, or PR comments — is intentionally deferred to a follow-up
decision after the team sees a few weeks of threshold-gated runs and can
judge whether richer signal is worth the integration. The cobertura XMLs
emitted by Phase 1 are already in the standard format any of these
services accept, so adopting one later is mechanical.

## Phase 2 — Lift to xmsconan

After Phase 1 ships and stabilizes (a few real PRs through the new
workflow, thresholds set above zero, no flaky failures for a week), lift
the generic pieces into xmsconan in a follow-up PR.

**Lifted into xmsconan:**

- The CMake coverage option block — emitted by `xmsconan_gen` into the
  generated CMakeLists, gated by a flag in `build.toml`.
- `Coverage.yaml` workflow — generated by `xmsconan_gen` alongside the
  existing `<Library>-CI.yaml`, gated by the same flag.
- Orchestration shipped as a console entry point: `xmsconan_coverage`,
  alongside `xmsconan_gen`, `xmsconan_wheel_repair`, `xmsconan_wheel_deploy`.
  The repo-local `dev/coverage.sh` shrinks to a one-liner or is deleted in
  favor of documenting `xmsconan_coverage`.
- Default gcovr exclusion patterns: `*.t.h`, `_package/tests/`,
  `<library_name>/python/`.

**Stays repo-local:**

- A toggle in `build.toml`:
  ```toml
  [ci]
  enable_coverage = true
  ```
- `codecov.yml` (per-repo thresholds and ignore lists).
- `CODECOV_TOKEN` repo secret.

**Migration of xmsgrid in Phase 2:**

1. Bump xmsconan dependency in `build.toml` to the version with coverage
   support.
2. Set `enable_coverage = true` in `build.toml`.
3. Replace `dev/coverage.sh` body with a call to `xmsconan_coverage`, or
   delete the script and document `xmsconan_coverage` directly.
4. Delete `.github/workflows/Coverage.yaml` — now regenerated.
5. Re-run `xmsconan_gen`.
6. Verify the next CI run produces the same Codecov report.

**Why two phases:**

- Phase 1 lets us iterate on script details, gcovr filters, and Codecov
  config without an xmsconan release on every change.
- Phase 2 is mechanical: copy proven files into xmsconan templates, add
  the `build.toml` knob.

A feature issue tracking Phase 2 will be filed in the xmsconan repo when
Phase 1 lands.

## Testing

- Unit testing the coverage script itself is overkill — it's an
  orchestrator. Validation is end-to-end: a successful CI run on a PR
  shows non-zero numbers for both flags in the Codecov comment.
- Local validation: run `dev/coverage.sh` on a clean checkout, confirm
  HTML reports open and show non-zero coverage for at least one file in
  each layer.

## Risks & Open Questions

- **Pybind11 coverage instrumentation overhead.** `--coverage` adds
  significant build time and binary size. Linux Debug coverage build is
  expected to take notably longer than the existing Linux Debug CI job;
  this is acceptable since coverage is its own job and runs in parallel.
- **gcda path mismatch.** If pytest is run from a different working
  directory than the one where the extension was built, gcov may not
  find source files. The script pins `cwd` to the repo root throughout.
- **Codecov free-tier rate limits.** Public repos are unlimited on
  uploads; no concern for xmsgrid specifically.
- **Linux-only signal.** Coverage numbers reflect what runs on Linux. For
  a math/geometry library this is fine — platform-specific code is
  minimal — but anything truly Windows- or Mac-only will show as
  uncovered. Acceptable.
