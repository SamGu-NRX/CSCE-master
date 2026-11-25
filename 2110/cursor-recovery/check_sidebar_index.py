#!/usr/bin/env python3
"""Check if conversation is in the workspace sidebar index."""
import sqlite3
import json
import os
import sys

CONV_ID = sys.argv[1] if len(sys.argv) > 1 else "YOUR_CONVERSATION_ID_HERE"
WORKSPACE_HASH = sys.argv[2] if len(sys.argv) > 2 else "YOUR_WORKSPACE_HASH"

ws_db = os.path.expanduser(
    f"~/Library/Application Support/Cursor/User/workspaceStorage/{WORKSPACE_HASH}/state.vscdb"
)

conn = sqlite3.connect(ws_db)
c = conn.cursor()
c.execute("SELECT value FROM ItemTable WHERE key = ?", ("composer.composerData",))
obj = json.loads(c.fetchone()[0])

all_composers = obj.get("allComposers", [])
found = any(
    isinstance(e, dict) and e.get("composerId") == CONV_ID for e in all_composers
)
print(f"allComposers has {len(all_composers)} entries")
print(f"Your conversation is in the list: {found}")
conn.close()
