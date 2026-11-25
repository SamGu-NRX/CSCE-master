#!/usr/bin/env bash
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
if [ -d "$GTEST_DIR/googletest" ]; then
  echo "Google Test already initialized at $GTEST_DIR"
  exit 0
fi
echo "Cloning Google Test $GTEST_VERSION to $GTEST_DIR"
mkdir -p "$(dirname "$GTEST_DIR")"
git clone --depth 1 --branch "$GTEST_VERSION" https://github.com/google/googletest.git "$GTEST_DIR"
echo "Done. Run 'make test' from sim-city/"
