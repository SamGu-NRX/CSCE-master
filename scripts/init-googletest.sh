#!/usr/bin/env bash
<<<<<<< HEAD
# Wrapper: delegates to CSCE shared script when under CSCE-master.
# Otherwise clones to sim-city/third_party for standalone 2110.
set -e
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
CSCE_SCRIPT="$(cd "$SCRIPT_DIR/../.." 2>/dev/null && pwd)/scripts/init-googletest.sh"
if [ -f "$CSCE_SCRIPT" ]; then
  exec "$CSCE_SCRIPT"
fi
# Fallback for standalone 2110
GTEST_DIR="${GTEST_DIR:-$SCRIPT_DIR/../sim-city/third_party/googletest-v1.17.0}"
GTEST_VERSION="v1.17.0"
=======
# Shared Google Test (v1.17.0) for all C++ projects in CSCE master.
# Run from CSCE root: ./scripts/init-googletest.sh
# Clones to CSCE/third_party/googletest-v1.17.0 (gitignored)

set -e
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
CSCE_ROOT="$(cd "$SCRIPT_DIR/.." && pwd)"
GTEST_DIR="${GTEST_DIR:-$CSCE_ROOT/third_party/googletest-v1.17.0}"
GTEST_VERSION="v1.17.0"

>>>>>>> 45fc47a (Initial commit: CSCE master with 1040, 2110, 3444/UNTangle submodules, 2100 content, shared scripts)
if [ -d "$GTEST_DIR/googletest" ]; then
  echo "Google Test already initialized at $GTEST_DIR"
  exit 0
fi
<<<<<<< HEAD
echo "Cloning Google Test $GTEST_VERSION to $GTEST_DIR"
mkdir -p "$(dirname "$GTEST_DIR")"
git clone --depth 1 --branch "$GTEST_VERSION" https://github.com/google/googletest.git "$GTEST_DIR"
echo "Done. Run 'make test' from sim-city/"
=======

echo "Cloning Google Test $GTEST_VERSION to $GTEST_DIR"
mkdir -p "$(dirname "$GTEST_DIR")"
git clone --depth 1 --branch "$GTEST_VERSION" https://github.com/google/googletest.git "$GTEST_DIR"

echo "Done. Projects use GTEST_ROOT=$GTEST_DIR/googletest"
>>>>>>> 45fc47a (Initial commit: CSCE master with 1040, 2110, 3444/UNTangle submodules, 2100 content, shared scripts)
