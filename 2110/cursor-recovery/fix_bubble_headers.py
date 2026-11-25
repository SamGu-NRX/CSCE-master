#!/usr/bin/env python3
"""Fix empty bubble headers in composerData. CLOSE CURSOR FIRST!"""
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

# Get all bubble entries
c.execute("SELECT key, value FROM cursorDiskKV WHERE key LIKE ?", (f"bubbleId:{CONV_ID}:%",))
rows = c.fetchall()

bubbles = []
for key, value in rows:
    try:
        obj = json.loads(value)
        bubbles.append(
            {
                "bubbleId": obj.get("bubbleId", key.split(":")[-1]),
                "type": obj.get("type", 2),
                "createdAt": obj.get("createdAt", ""),
            }
        )
    except Exception:
        pass

bubbles.sort(key=lambda b: b["createdAt"])
headers = [{"bubbleId": b["bubbleId"], "type": b["type"]} for b in bubbles]

# Update composerData
c.execute("SELECT value FROM cursorDiskKV WHERE key = ?", (f"composerData:{CONV_ID}",))
obj = json.loads(c.fetchone()[0])
obj["fullConversationHeadersOnly"] = headers
obj["status"] = "completed"  # Was 'aborted' in our case

# Write as compact JSON to match Cursor's format
c.execute(
    "UPDATE cursorDiskKV SET value = ? WHERE key = ?",
    (json.dumps(obj, separators=(",", ":")), f"composerData:{CONV_ID}"),
)
conn.commit()
print(f"Updated: {len(headers)} bubble headers, status=completed")
conn.close()
