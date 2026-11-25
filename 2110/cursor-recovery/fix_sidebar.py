#!/usr/bin/env python3
"""Add conversation to sidebar index. CLOSE CURSOR FIRST!"""
import sqlite3
import json
import os
import sys

CONV_ID = sys.argv[1] if len(sys.argv) > 1 else "YOUR_CONVERSATION_ID_HERE"
WORKSPACE_HASH = sys.argv[2] if len(sys.argv) > 2 else "YOUR_WORKSPACE_HASH"

global_db = os.path.expanduser(
    "~/Library/Application Support/Cursor/User/globalStorage/state.vscdb"
)
ws_db = os.path.expanduser(
    f"~/Library/Application Support/Cursor/User/workspaceStorage/{WORKSPACE_HASH}/state.vscdb"
)

# Read conversation metadata from global DB
gconn = sqlite3.connect(global_db)
gc = gconn.cursor()
gc.execute("SELECT value FROM cursorDiskKV WHERE key = ?", (f"composerData:{CONV_ID}",))
row = gc.fetchone()
if not row:
    print("ERROR: composerData not found in global DB")
    sys.exit(1)
conv_data = json.loads(row[0])
gconn.close()

# Build the sidebar head entry
head = {
    "type": "head",
    "composerId": CONV_ID,
    "name": conv_data.get("name", "Recovered conversation"),
    "lastUpdatedAt": conv_data.get("lastUpdatedAt", 0),
    "createdAt": conv_data.get("createdAt", 0),
    "unifiedMode": conv_data.get("unifiedMode", "agent"),
    "forceMode": conv_data.get("forceMode", "edit"),
    "hasUnreadMessages": False,
    "contextUsagePercent": conv_data.get("contextUsagePercent", 0),
    "totalLinesAdded": conv_data.get("totalLinesAdded", 0),
    "totalLinesRemoved": conv_data.get("totalLinesRemoved", 0),
    "filesChangedCount": conv_data.get("filesChangedCount", 0),
    "subtitle": conv_data.get("subtitle", ""),
    "isAgentic": conv_data.get("isAgentic", True),
    "status": conv_data.get("status", "completed"),
}

# Add to workspace sidebar index
conn = sqlite3.connect(ws_db)
c = conn.cursor()
c.execute("SELECT value FROM ItemTable WHERE key = ?", ("composer.composerData",))
ws_data = json.loads(c.fetchone()[0])

all_composers = ws_data.get("allComposers", [])
already_present = any(
    isinstance(e, dict) and e.get("composerId") == CONV_ID for e in all_composers
)

if already_present:
    print("Conversation already in sidebar index")
else:
    all_composers.insert(0, head)
    ws_data["allComposers"] = all_composers

    # Also add to selectedComposerIds (open tabs)
    selected = ws_data.get("selectedComposerIds", [])
    if CONV_ID not in selected:
        selected.insert(0, CONV_ID)
        ws_data["selectedComposerIds"] = selected

    # Write as compact JSON (no spaces) to match Cursor's format
    c.execute(
        "UPDATE ItemTable SET value = ? WHERE key = ?",
        (json.dumps(ws_data, separators=(",", ":")), "composer.composerData"),
    )
    conn.commit()
    print(f"SUCCESS: Added to allComposers ({len(all_composers)} total)")
    print(f"Added to selectedComposerIds ({len(selected)} total)")

conn.close()
print("\nReopen Cursor. The conversation should appear in the sidebar.")
