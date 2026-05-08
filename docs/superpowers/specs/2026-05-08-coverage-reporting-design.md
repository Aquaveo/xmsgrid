# Coverage Reporting Design

**Date:** 2026-05-08
**Status:** Approved (design phase)
**Owner:** glarsen@aquaveo.com

## Goal

Add unified line-coverage reporting for both the C++ library and Python
bindings of `xmsgrid`. Reports are generated locally for developer iteration
and in CI for accountability, with results published to Codecov.

The C++ extension is built **once** with coverage instrumentation; both the
ctest and pytest suites run against that single build, and their gcov data is
merged into one C++ report. Python-side coverage is collected separately via
coverage.py.

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
┌─ Coverage Build (Linux, GCC, Debug) ─────────────────────────┐
│  cmake -DXMSGRID_ENABLE_COVERAGE=ON  →  --coverage flags     │
│  builds: libxmsgrid (instrumented)                            │
│          C++ test runner (instrumented)                       │
│          Python extension _xmsgrid (instrumented)             │
└──────────────────────────────────────────────────────────────┘
              │                                │
              ▼                                ▼
     ┌──────────────────┐            ┌─────────────────────┐
     │  ctest           │            │  pytest             │
     │  → *.gcda files  │            │  → *.gcda (C++)     │
     │  (C++ tests)     │            │  → .coverage (py)   │
     └──────────────────┘            └─────────────────────┘
              │                                │
              └─────────────┬──────────────────┘
                            ▼
              ┌─────────────────────────────┐
              │ gcovr → cobertura-cpp.xml   │
              │ coverage → cobertura-py.xml │
              └─────────────────────────────┘
                            ▼
              ┌─────────────────────────────┐
              │ Codecov upload              │
              │  flag: cpp                  │
              │  flag: python               │
              └─────────────────────────────┘
```

The crucial property: pybind11-built objects compiled with `--coverage` emit
`.gcda` files when their code paths run, regardless of whether the caller is
C++ or Python. So pytest exercising the bindings credits the underlying C++
implementation in the C++ report.

## Components

### 1. CMake option (in `build.toml` `extra_cmake_text`)

```cmake
option(XMSGRID_ENABLE_COVERAGE "Build with gcov instrumentation" OFF)
if(XMSGRID_ENABLE_COVERAGE)
    if(MSVC)
        message(FATAL_ERROR "Coverage build is GCC/Clang only")
    endif()
    add_compile_options(--coverage -O0 -g)
    add_link_options(--coverage)
endif()
```

The flag is added to the existing `extra_cmake_text` block — no xmsconan
generator change. Off by default, so non-coverage builds are untouched.

### 2. `dev/coverage.sh`

POSIX shell script (Linux + macOS). Single entry point. Steps:

1. Run the Conan build with the coverage flag:
   ```
   python build.py \
       --filter='{"build_type":"Debug"}' \
       --cmake-args='-DXMSGRID_ENABLE_COVERAGE=ON' \
       --wheel-dir wheelhouse
   ```
2. Run the C++ test suite via `ctest` against the instrumented build (the
   conan recipe already wires this).
3. Install the freshly-built wheel into a throwaway venv:
   ```
   python -m venv .coverage-venv
   .coverage-venv/bin/pip install wheelhouse/*.whl pytest pytest-cov
   ```
4. Run the Python tests with coverage:
   ```
   .coverage-venv/bin/pytest \
       --cov=xms.grid \
       --cov-report=xml:cov-py.xml \
       --cov-report=html:build/coverage-html-py \
       _package/tests
   ```
5. Aggregate C++ gcov data:
   ```
   gcovr --root . \
       --filter 'xmsgrid/' \
       --exclude '.*\.t\.h$' \
       --exclude 'xmsgrid/python/.*' \
       --exclude '_package/tests/.*' \
       --xml cov-cpp.xml \
       --html-details build/coverage-html-cpp/index.html
   ```
6. Print a summary line, e.g. `Coverage: C++ 78.3%, Python 64.1%`.

The wheel installed in step 3 must be the exact one produced in step 1 —
gcov data files reference build-tree absolute paths, so any rebuild between
the two will desync the `.gcda` / `.gcno` pair.

A `dev/coverage.bat` is **not** added in Phase 1; Windows coverage is out
of scope.

### 3. `.github/workflows/Coverage.yaml`

Hand-maintained, separate from the xmsconan-generated `XmsGrid-CI.yaml`.
Single job, Linux, GCC, Debug:

- Triggers: `push`, `pull_request`.
- Checks out source, installs xmsconan + Python deps, sets up Conan login.
- Runs `dev/coverage.sh`.
- Uploads `cov-cpp.xml` to Codecov with flag `cpp`.
- Uploads `cov-py.xml` to Codecov with flag `python`.
- Uploads `build/coverage-html-cpp` and `build/coverage-html-py` as
  workflow artifacts so a developer can download and browse them.

The job uses the same Conan secrets as the existing CI workflow and the
new `CODECOV_TOKEN` repo secret.

### 4. `codecov.yml`

```yaml
coverage:
  status:
    project:
      default:
        informational: true
    patch:
      default:
        informational: true
flags:
  cpp:
    paths:
      - xmsgrid/
    carryforward: true
  python:
    paths:
      - _package/xms/
    carryforward: true
ignore:
  - "_package/tests/"
  - "xmsgrid/**/*.t.h"
  - "xmsgrid/python/"
```

Both project and patch status are informational — Codecov will comment on
PRs with the numbers but won't fail the check. Tightening is a future
decision once we have a baseline.

### 5. README update

Short `## Coverage` section: how to run `dev/coverage.sh`, where the HTML
lands, link to the Codecov project page.

## Repo Setup (one-time, manual)

- Add the `xmsgrid` repo to Codecov via the GitHub app.
- Add `CODECOV_TOKEN` as a repository secret in GitHub settings.

These are operator actions, not code changes; they should be documented in
the implementation plan as prerequisites for the Coverage workflow's first
green run.

## Phase 2 — Lift to xmsconan

After Phase 1 ships and stabilizes (a few real PRs through the new
workflow, no broken Codecov runs for a week), lift the generic pieces
into xmsconan in a follow-up PR.

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
