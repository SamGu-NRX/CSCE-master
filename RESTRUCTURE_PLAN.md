# CSCE Repo Restructure Implementation Plan

## Overview

Restructure CSCE repos so:

- Submodules use course-prefixed names (2110-labs, 2110-sim-city, etc.)
- Folders organized: labs/, assignments/, exams/
- Google Test: init script, not committed
- 3444 UNTangle: Turborepo monorepo with backend (UNT-Schedule-Optimizer) + Next.js frontend

---

## 1. GitHub Repos to Create

Create these repos on GitHub (SamGu-NRX):

| Repo              | Content                                                                                                           |
| ----------------- | ----------------------------------------------------------------------------------------------------------------- |
| 2110-labs         | labs/ content (rename from labs)                                                                                  |
| 2110-sim-city     | sim-city content (rename from sim-city)                                                                           |
| 2110-assignment-2 | Assignment 1.1 (Library system)                                                                                   |
| 2110-assignment-3 | Assignment 3 (graph)                                                                                              |
| 2110-exam-2       | Exam 2 content                                                                                                    |
| 1040-labs         | Lab0, Lab1, Lab1B                                                                                                 |
| 1040-assignments  | HW1, HW2, HW3, HW4                                                                                                |
| UNTangle          | UNTangle monorepo (backend submodule + frontend). Lives under 3444/ in CSCE-master; repo name is just "UNTangle". |

---

## 2. 2110 New Structure

```
2110/
├── labs/              ← submodule 2110-labs
├── assignments/
│   ├── sim-city/      ← submodule 2110-sim-city
│   ├── assignment-2/  ← submodule 2110-assignment-2
│   ├── assignment-3/  ← submodule 2110-assignment-3
│   └── exam-2/        ← submodule 2110-exam-2
├── scripts/
│   └── init-googletest.sh
├── third_party/       (optional shared deps)
└── .gitmodules
```

---

## 3. 1040 New Structure

```
1040/
├── labs/              ← submodule 1040-labs (Lab0, Lab1, Lab1B)
└── assignments/       ← submodule 1040-assignments (HW1-HW4)
```

---

## 4. 3444 / UNTangle

Repo name: **UNTangle** (no "3444" prefix). In CSCE-master it lives at `3444/UNTangle/`.

```
3444/
└── UNTangle/           ← submodule SamGu-NRX/UNTangle
    ├── backend/       ← submodule sunnyD1000/UNT-Schedule-Optimizer
    ├── frontend/      ← Next.js TypeScript
    ├── turbo.json
    └── package.json
```

---

## 5. Manual Steps

1. Create GitHub repos (gh repo create or GitHub UI)
2. Push content to each new repo
3. Update .gitmodules in 2110, 1040
4. Run init-googletest.sh for sim-city tests
