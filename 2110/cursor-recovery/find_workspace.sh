#!/bin/bash
# Find workspace hash for your project
# Replace YOUR_PROJECT_FOLDER_NAME with: 2110, CSCE, CSCE-master, etc.

SEARCH="CSCE"  # Try: 2110, CSCE, CSCE-master

for dir in ~/Library/Application\ Support/Cursor/User/workspaceStorage/*/; do
  if [ -f "$dir/workspace.json" ]; then
    if grep -q "$SEARCH" "$dir/workspace.json" 2>/dev/null; then
      echo "FOUND: $dir"
      cat "$dir/workspace.json"
      echo ""
    fi
  fi
done
