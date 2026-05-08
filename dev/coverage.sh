#!/usr/bin/env bash
# Generate C++ and Python coverage reports for xmsgrid.
#
# C++ coverage comes from a Debug+testing Conan build instrumented with
# --coverage. ctest runs as part of the build; gcovr scans the resulting
# build folder in the conan cache.
#
# Python coverage comes from a separate pytest run against the built wheel
# in a clean venv with pytest-cov. Cross-credit (Python tests measuring C++
# code) is not in scope for Phase 1.
#
# Outputs:
#   cov-cpp.xml                 Cobertura, C++
#   cov-py.xml                  Cobertura, Python
#   build/coverage-html-cpp/    Browsable C++ report
#   build/coverage-html-py/     Browsable Python report
#
# Requirements: gcc/clang, gcovr, python, conan, xmsconan, gcc tools (gcov).

set -euo pipefail

REPO_ROOT="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$REPO_ROOT"

if [[ "$(uname -s)" == MINGW* || "$(uname -s)" == CYGWIN* ]]; then
    echo "error: coverage is GCC/Clang-only; Windows is unsupported in Phase 1" >&2
    exit 1
fi

# Tool checks.
for tool in python gcovr gcov conan xmsconan_gen; do
    if ! command -v "$tool" >/dev/null 2>&1; then
        echo "error: required tool '$tool' not on PATH" >&2
        exit 1
    fi
done

XMS_VERSION="${XMS_VERSION:-0.0.0}"

echo "==> Generating xmsconan build artifacts"
xmsconan_gen --version "$XMS_VERSION" build.toml

MARK="$REPO_ROOT/.coverage-mark"
trap 'rm -f "$MARK"' EXIT
touch "$MARK"
sleep 1  # Ensure subsequent file mtimes strictly exceed the marker.

echo "==> C++ coverage build (Debug, testing=True, instrumented)"
XMSGRID_COVERAGE=1 python build.py \
    --filter='{"build_type":"Debug","testing":true}'

echo "==> Python wheel build (Release, pybind=True, not instrumented)"
mkdir -p wheelhouse
python build.py \
    --filter='{"build_type":"Release","pybind":true}' \
    --wheel-dir wheelhouse

echo "==> Locating Conan build folders that wrote .gcda files"
CONAN_HOME="${CONAN_HOME:-$HOME/.conan2}"
mapfile -t GCDA_FILES < <(find "$CONAN_HOME/p" -newer "$MARK" -name '*.gcda' 2>/dev/null || true)

if [[ ${#GCDA_FILES[@]} -eq 0 ]]; then
    echo "error: no .gcda files found under $CONAN_HOME/p; did the C++ build run?" >&2
    exit 1
fi

# Walk up from each .gcda to find the directory containing CMakeCache.txt
# (the build folder), then walk further up looking for the conan source
# folder — the first parent that contains a sibling 'xmsgrid' directory.
declare -A BUILD_TO_SOURCE=()
for gcda in "${GCDA_FILES[@]}"; do
    dir="$(dirname "$gcda")"
    while [[ "$dir" != "/" && ! -f "$dir/CMakeCache.txt" ]]; do
        dir="$(dirname "$dir")"
    done
    if [[ ! -f "$dir/CMakeCache.txt" ]]; then
        continue
    fi
    src_dir="$(dirname "$dir")"
    while [[ "$src_dir" != "/" && ! -d "$src_dir/xmsgrid" ]]; do
        src_dir="$(dirname "$src_dir")"
    done
    if [[ ! -d "$src_dir/xmsgrid" ]]; then
        echo "error: could not locate a parent of $dir containing xmsgrid/" >&2
        exit 1
    fi
    BUILD_TO_SOURCE["$dir"]="$src_dir"
done

if [[ ${#BUILD_TO_SOURCE[@]} -eq 0 ]]; then
    echo "error: could not locate any CMakeCache.txt above the discovered .gcda files" >&2
    exit 1
fi

echo "==> Found ${#BUILD_TO_SOURCE[@]} build folder(s):"
for bf in "${!BUILD_TO_SOURCE[@]}"; do
    echo "    build:  $bf"
    echo "    source: ${BUILD_TO_SOURCE[$bf]}"
done

mkdir -p build/coverage-html-cpp build/coverage-html-py

# Thresholds. Default 0 means "do not fail". Override via env var to gate.
CPP_COVERAGE_THRESHOLD="${CPP_COVERAGE_THRESHOLD:-0}"
PY_COVERAGE_THRESHOLD="${PY_COVERAGE_THRESHOLD:-0}"

GCOVR_COMMON=(
    --filter 'xmsgrid/'
    --exclude '.*\.t\.h$'
    --exclude 'xmsgrid/python/.*'
    --exclude '_package/tests/.*'
)
GCOVR_OUTPUT=(
    --xml-pretty --output cov-cpp.xml
    --html-details "build/coverage-html-cpp/index.html"
    --print-summary
    --fail-under-line "$CPP_COVERAGE_THRESHOLD"
)

echo "==> Aggregating C++ coverage with gcovr (threshold: $CPP_COVERAGE_THRESHOLD%)"
# gcovr's --root must be the source folder; the build folder argument tells
# it where to find .gcda files. With one build folder we emit directly;
# with multiple we collect JSON intermediates then merge.
if [[ ${#BUILD_TO_SOURCE[@]} -eq 1 ]]; then
    bf="${!BUILD_TO_SOURCE[*]}"
    src="${BUILD_TO_SOURCE[$bf]}"
    gcovr --root "$src" "${GCOVR_COMMON[@]}" "${GCOVR_OUTPUT[@]}" "$bf"
else
    JSON_FILES=()
    i=0
    for bf in "${!BUILD_TO_SOURCE[@]}"; do
        src="${BUILD_TO_SOURCE[$bf]}"
        out="build/coverage-cpp-$i.json"
        gcovr --root "$src" "${GCOVR_COMMON[@]}" --json --output "$out" "$bf"
        JSON_FILES+=(--add-tracefile "$out")
        i=$((i + 1))
    done
    # Merge: --root here only affects how merged paths are rendered, not
    # which gcda files are read. Use the first source folder as the root.
    first_src="${BUILD_TO_SOURCE[$(printf '%s\n' "${!BUILD_TO_SOURCE[@]}" | head -n1)]}"
    gcovr --root "$first_src" "${GCOVR_COMMON[@]}" "${JSON_FILES[@]}" "${GCOVR_OUTPUT[@]}"
fi

echo "==> Python coverage run (threshold: $PY_COVERAGE_THRESHOLD%)"
PY_VENV="$REPO_ROOT/.coverage-venv"
rm -rf "$PY_VENV"
python -m venv "$PY_VENV"
"$PY_VENV/bin/pip" install --quiet --upgrade pip
"$PY_VENV/bin/pip" install --quiet pytest pytest-cov
WHEEL=$(ls wheelhouse/*.whl | head -n1)
if [[ -z "$WHEEL" ]]; then
    echo "error: no wheel found in wheelhouse/" >&2
    exit 1
fi
# xmsgrid wheels declare an xmscore dependency that lives on Aquaveo devpi,
# not PyPI. Pass the public devpi index so pip can resolve it.
DEVPI_INDEX="${COVERAGE_PIP_INDEX:-https://public.aquapi.aquaveo.com/aquaveo/dev/+simple}"
"$PY_VENV/bin/pip" install --quiet --extra-index-url "$DEVPI_INDEX" "$WHEEL"

"$PY_VENV/bin/pytest" \
    --cov=xms.grid \
    --cov-report=xml:cov-py.xml \
    --cov-report=html:build/coverage-html-py \
    --cov-report=term \
    --cov-fail-under="$PY_COVERAGE_THRESHOLD" \
    _package/tests

# Optional: append summary to GitHub Actions step summary.
if [[ -n "${GITHUB_STEP_SUMMARY:-}" ]]; then
    {
        echo "## Coverage Summary"
        echo
        echo "| Layer | Threshold |"
        echo "|-------|-----------|"
        echo "| C++ | $CPP_COVERAGE_THRESHOLD% |"
        echo "| Python | $PY_COVERAGE_THRESHOLD% |"
        echo
        echo "See \`gcovr\` and \`pytest --cov\` output above for actual percentages."
        echo "Browseable HTML reports are uploaded as the \`coverage-html\` artifact."
    } >> "$GITHUB_STEP_SUMMARY"
fi

echo
echo "==> Coverage reports written:"
echo "    cov-cpp.xml                  Cobertura, C++"
echo "    cov-py.xml                   Cobertura, Python"
echo "    build/coverage-html-cpp/     Browsable C++ report"
echo "    build/coverage-html-py/      Browsable Python report"
