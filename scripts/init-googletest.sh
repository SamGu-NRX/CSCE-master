#!/usr/bin/env bash
# Shared Google Test (v1.17.0) for all C++ projects in CSCE master.
# Run from CSCE root: ./scripts/init-googletest.sh
# Clones to CSCE/third_party/googletest-v1.17.0 (gitignored)

set -e
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
CSCE_ROOT="$(cd "$SCRIPT_DIR/.." && pwd)"
GTEST_DIR="${GTEST_DIR:-$CSCE_ROOT/third_party/googletest-v1.17.0}"
GTEST_VERSION="v1.17.0"

if [ -d "$GTEST_DIR/googletest" ]; then
  echo "Google Test already initialized at $GTEST_DIR"
  exit 0
fi

echo "Cloning Google Test $GTEST_VERSION to $GTEST_DIR"
mkdir -p "$(dirname "$GTEST_DIR")"
git clone --depth 1 --branch "$GTEST_VERSION" https://github.com/google/googletest.git "$GTEST_DIR"

echo "Done. Projects use GTEST_ROOT=$GTEST_DIR/googletest"
