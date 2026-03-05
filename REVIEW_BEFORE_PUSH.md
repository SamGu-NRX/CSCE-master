# Review Before Push

Summary of all changes and git status. **Nothing has been pushed.** Review and push when ready.

---

## 1. 2110 (CSCE-2110-master)

**Location:** `CSCE/2110/`

**Changes:**

- `scripts/init-googletest.sh` — Fetches googletest to sim-city/third_party (not committed)
- `scripts/README.md` — Docs for init script
- `.gitignore` — Added !assignments/, !exams/
- `README.md` — Restored original style (submodules list)
- `MIGRATION_GUIDE.md` — Steps for restructure (rename repos, move submodules)

**Submodules:** labs, sim-city (unchanged paths; migration not run)

**To review:**

```bash
cd CSCE/2110
git status
git diff .gitignore README.md
```

**To commit (when ready):**

```bash
git add scripts/ .gitignore README.md MIGRATION_GUIDE.md
git commit -m "Add init-googletest script, migration guide"
# Do NOT push until you've committed sim-city changes (see below)
```

---

## 2. sim-city (submodule of 2110)

**Location:** `CSCE/2110/sim-city/`

**Changes:**

- `Makefile` — GTEST_ROOT uses third_party/ (init script) instead of tests/googletest-v1.17.0
- `.gitignore` — Added third_party/
- `README.md` — Updated test setup instructions

**To review:**

```bash
cd CSCE/2110/sim-city
git status
git diff Makefile .gitignore README.md
```

**To commit (when ready):**

```bash
git add Makefile .gitignore README.md
git commit -m "Use init script for googletest, update Makefile"
git push origin main
```

**Then** update 2110 to point to the new sim-city commit and push 2110.

---

## 3. UNTangle (3444)

**Location:** `CSCE/3444/UNTangle/`

**Status:** Repo initialized, one commit. Uncommitted: README.md, package.json (name → UNTangle).

**Structure:**

- `backend/` — Submodule → sunnyD1000/UNT-Schedule-Optimizer (Django)
- `frontend/` — Next.js TypeScript (bun)
- `turbo.json`, `package.json` — Turborepo

**Repo name:** UNTangle (no 3444 prefix). Create `SamGu-NRX/UNTangle` on GitHub.

**To review:**

```bash
cd CSCE/3444/UNTangle
git status
git diff README.md package.json
```

**To commit (when ready):**

```bash
git add README.md package.json
git commit -m "Update README style, package name to UNTangle"
# Create repo on GitHub: SamGu-NRX/UNTangle
git remote add origin https://github.com/SamGu-NRX/UNTangle.git
git push -u origin main
```

---

## 4. CSCE-master (done)

**Status:** Initialized. One commit. Remote: CSCE-master.

**Structure:** 1040/, 2100/, 2110/, 3444/UNTangle (submodules); scripts/; .github/workflows/

**To push:** Create `SamGu-NRX/UNTangle` on GitHub first if needed. Then `git push -u origin main`

---

## 5. Optional

- Repo renames (labs → 2110-labs, sim-city → 2110-sim-city) — see MIGRATION_GUIDE

---

## Quick status

| Repo        | Status           | Push?                     |
| ----------- | ---------------- | ------------------------- |
| CSCE-master | 1 commit         | Yes (after UNTangle repo) |
| 2110        | Local changes    | After sim-city            |
| sim-city    | Local changes    | First                     |
| UNTangle    | 1 commit + local | Create GitHub repo first  |

---

## Run status script

From the CSCE folder:

```bash
cd "/Users/samgu/All things TAMS/CSCE"
bash scripts/review-status.sh
```
