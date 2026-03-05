#!/usr/bin/env bash
# Run from CSCE folder. Shows git status for all repos.
set -e
CSCE_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$CSCE_ROOT"

echo "=== CSCE-master ==="
(git status -s && echo "") 2>/dev/null || echo "Not a repo"

echo "=== 2110 ==="
(cd 2110 && git status -s && echo "") 2>/dev/null || echo "Not a repo"

echo "=== 2110/sim-city ==="
(cd 2110/sim-city && git status -s && echo "") 2>/dev/null || echo "Not found"

echo "=== 2110/labs ==="
(cd 2110/labs && git status -s && echo "") 2>/dev/null || echo "Not found"

echo "=== 3444/UNTangle ==="
(cd 3444/UNTangle && git status -s && git log --oneline -1 2>/dev/null && echo "") 2>/dev/null || echo "Not found"

echo "=== 1040 ==="
(cd 1040 && git status -s && echo "") 2>/dev/null || echo "Not a repo"
