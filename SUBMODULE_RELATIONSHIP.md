# Git Submodule Relationship — CSCE Master

**CSCE-master is the only master repo.** There is no 2110-master, no 1040-master.

---

## Target Structure

```
CSCE-master/                    ← single repo (the only master)
├── 1040/                      ← tracked folder (NOT submodule)
│   ├── labs/                   ← submodule → CSCE-labs (1040 + 2110 labs)
│   └── assignments/
├── 2100/                      ← tracked folder (NOT submodule)
├── 2110/                      ← tracked folder (NOT submodule)
│   ├── sim-city/               ← submodule (project)
│   ├── labs/                   ← submodule → CSCE-labs (1040 + 2110 labs)
│   ├── assignments/
│   ├── scripts/
│   └── ...
├── 3444/                      ← tracked folder (NOT submodule)
│   └── UNTangle/              ← submodule (project)
├── scripts/
└── README.md
```

---

## Submodules (projects only)

| Path              | Repo                  | Notes                              |
| ----------------- | --------------------- | ---------------------------------- |
| **1040/labs**     | SamGu-NRX/CSCE-labs   | Labs from 1040 and 2110 (unified)   |
| **2110/sim-city** | SamGu-NRX/sim-city    | Project                             |
| **2110/labs**     | SamGu-NRX/CSCE-labs   | Same repo as 1040/labs             |
| **3444/UNTangle** | SamGu-NRX/UNTangle    | Project                             |

**CSCE-labs** (renamed from `labs`): Single repo containing all CSCE labs. Structure:
- `1040/` — Lab0, Lab1, Lab1B, etc.
- `2110/` — gnu_debugger, lab_00, lab_01-1, etc.

---

## Not Submodules

| Path      | Content                                                      |
| --------- | ------------------------------------------------------------ |
| **1040/** | assignments tracked; labs → submodule CSCE-labs               |
| **2100/** | Course content — tracked in CSCE-master                      |
| **2110/** | Course content + project submodules — tracked in CSCE-master |

---

## Current vs Target

| Item          | Current (wrong)              | Target                                 |
| ------------- | ---------------------------- | -------------------------------------- |
| 1040          | Submodule → CSCE_1040        | Regular folder, content in CSCE-master |
| 2110          | Submodule → CSCE-2110-master | Regular folder, content in CSCE-master |
| 1040/labs     | Part of 1040 submodule       | Submodule → CSCE-labs                  |
| 2110/sim-city | Nested in 2110 submodule     | Direct submodule of CSCE-master        |
| 2110/labs     | Nested in 2110 submodule → labs | Direct submodule → CSCE-labs        |
| 3444/UNTangle | Submodule                    | Submodule (correct)                    |

---

## README (correct)

```markdown
# CSCE Master

This repository serves as a central hub for various of my CSCE projects, managed as Git submodules.

## Submodules

- **sim-city:** Basic Simulation - 2D Vectors & BFS
- **CSCE-labs:** All the different labs and small projects (1040 + 2110)
- **3444/UNTangle:** Schedule optimizing full-stack app
```

---

## Migration Steps

1. Rename `labs` repo on GitHub to `CSCE-labs` (Settings → General → Repository name)
2. Merge 1040 labs content into CSCE-labs (add `1040/` folder with Lab0, Lab1, Lab1B)
3. Remove 1040 and 2110 from CSCE-master `.gitmodules`
4. Deinit and convert 1040, 2110 to regular tracked content (or re-add their content)
5. Add `1040/labs`, `2110/sim-city`, `2110/labs` as submodules (labs → CSCE-labs)
6. Update README
