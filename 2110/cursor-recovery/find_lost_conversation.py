#!/usr/bin/env python3
"""List all Cursor conversations from global DB, sorted by most recent."""
import sqlite3
import json
import os
from datetime import datetime

global_db = os.path.expanduser(
    "~/Library/Application Support/Cursor/User/globalStorage/state.vscdb"
)

conn = sqlite3.connect(global_db)
c = conn.cursor()

# List all conversations sorted by most recent
c.execute("SELECT key, value FROM cursorDiskKV WHERE key LIKE 'composerData:%'")
convos = []
for key, val in c.fetchall():
    try:
        obj = json.loads(val)
        convos.append(
            {
                "id": key.replace("composerData:", ""),
                "name": obj.get("name", "(unnamed)"),
                "lastUpdatedAt": obj.get("lastUpdatedAt", 0),
                "status": obj.get("status", "?"),
                "bubbles": len(obj.get("fullConversationHeadersOnly", [])),
            }
        )
    except Exception:
        pass

convos.sort(key=lambda x: x["lastUpdatedAt"], reverse=True)
for co in convos[:50]:
    ts = (
        datetime.fromtimestamp(co["lastUpdatedAt"] / 1000).strftime("%Y-%m-%d %H:%M")
        if co["lastUpdatedAt"]
        else "?"
    )
    print(f"{ts} | {co['status']:10s} | {co['bubbles']:5d} bubbles | {co['name'][:60]}")
    print(f"  ID: {co['id']}")

conn.close()
