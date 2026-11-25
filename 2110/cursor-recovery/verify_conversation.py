#!/usr/bin/env python3
"""Verify that conversation data exists in global DB."""
import sqlite3
import json
import os
import sys

CONV_ID = sys.argv[1] if len(sys.argv) > 1 else "YOUR_CONVERSATION_ID_HERE"
global_db = os.path.expanduser(
    "~/Library/Application Support/Cursor/User/globalStorage/state.vscdb"
)

conn = sqlite3.connect(global_db)
c = conn.cursor()

c.execute("SELECT length(value) FROM cursorDiskKV WHERE key = ?", (f"composerData:{CONV_ID}",))
r = c.fetchone()
print(f"composerData: {r[0] if r else 'MISSING'} bytes")

c.execute("SELECT COUNT(*) FROM cursorDiskKV WHERE key LIKE ?", (f"bubbleId:{CONV_ID}:%",))
print(f"bubbleId entries: {c.fetchone()[0]}")

conn.close()
