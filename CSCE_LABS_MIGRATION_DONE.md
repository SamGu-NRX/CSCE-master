# CSCE-labs Migration — Completed Steps

## Done

1. **Labs repo restructured**
   - Added 1040 labs (Lab0, Lab1, Lab1B) under `1040/`
   - Moved 2110 labs (gnu_debugger, lab_00, lab_01-1) under `2110/`
   - Commit: `7529195`

2. **Repo renamed**
   - `SamGu-NRX/labs` → `SamGu-NRX/CSCE-labs` (via `gh repo rename`)
   - History preserved; old URL redirects

3. **2110/.gitmodules**
   - Labs submodule URL updated to `git@github.com:SamGu-NRX/CSCE-labs.git`
   - Commit: `645a2d8`

4. **CSCE-labs notify workflow**
   - Added `.github/workflows/notify-master.yml` to notify CSCE-master on push
   - Requires `MASTER_REPO_TOKEN` secret in CSCE-labs repo

5. **README**
   - CSCE-master README updated to say "CSCE-labs" instead of "labs"

## Remaining (for full target structure)

Per [SUBMODULE_RELATIONSHIP.md](SUBMODULE_RELATIONSHIP.md):

- Convert 1040 and 2110 from submodules to regular folders in CSCE-master
- Add `1040/labs` and `2110/labs` as submodules pointing to CSCE-labs
- Add `2110/sim-city` as direct submodule of CSCE-master

## Note on lab_01-1

The `2110/lab_01-1` folder previously had its own `.git`. That was removed so its content could live in CSCE-labs. The files are preserved; only that nested repo’s history was lost.
