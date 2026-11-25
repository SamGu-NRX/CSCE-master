# Cursor Chat Recovery - CSCE-master

Your conversation **"CSCE-master folder structure recovery"** was found.

- **Conversation ID:** `c5ea810c-a2ba-4bc4-a881-b4bd9e51d41d`
- **Status:** Data exists (24 bubbles, 10.9 KB)
- **Sidebar:** Present in workspace `85dcbd475fdb9e8d9b757c19586947d6` (CSCE/2110)
- **Missing from:** `1cf5bef6f90a2faa101c87d74998b061` (CSCE) and `4c419c162d065934f0476fdc6bdcb6e7` (CSCE/2110)

## If you can't see the chat

1. **Close Cursor completely** (Cmd+Q or `pkill -9 -f Cursor`)

2. **Add to sidebar** (for workspaces where it's missing):

   ```bash
   python3 fix_sidebar.py c5ea810c-a2ba-4bc4-a881-b4bd9e51d41d 1cf5bef6f90a2faa101c87d74998b061
   python3 fix_sidebar.py c5ea810c-a2ba-4bc4-a881-b4bd9e51d41d 4c419c162d065934f0476fdc6bdcb6e7
   ```

3. **If the chat appears but messages are empty** (status was "aborted"):

   ```bash
   python3 fix_bubble_headers.py c5ea810c-a2ba-4bc4-a881-b4bd9e51d41d
   ```

4. **Reopen Cursor**

## Backup first (recommended)

```bash
cp ~/Library/Application\ Support/Cursor/User/globalStorage/state.vscdb /path/to/backup/
cp ~/Library/Application\ Support/Cursor/User/globalStorage/state.vscdb-wal /path/to/backup/
cp ~/Library/Application\ Support/Cursor/User/globalStorage/state.vscdb-shm /path/to/backup/
```

Reference: [How I Recovered my Vanished Cursor Chat](https://forum.cursor.com/t/how-i-recovered-my-vanished-cursor-chat-so-you-dont-have-to/151158)
