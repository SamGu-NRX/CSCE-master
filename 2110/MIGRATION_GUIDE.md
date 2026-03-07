# 2110 Restructure Migration Guide

**Non-destructive steps.** Your commit history stays intact. Run these when ready.

## Prerequisites

1. **Commit and push all changes** in submodules:
   ```bash
   cd sim-city && git add -A && git status  # review
   git commit -m "Use init script for googletest, update Makefile"
   git push origin main
   cd ../labs && git add -A && git status
   git commit -m "..." && git push origin main
   ```

2. **Create/rename GitHub repos** (Settings → General → Repository name):
   - `sim-city` → `2110-sim-city` (preserves history)
   - `labs` → `2110-labs` (preserves history)

   Or create new repos and push: `2110-assignment-2`, `2110-assignment-3`, `2110-exam-2`

## Restructure Steps

After renaming, update 2110:

```bash
cd /path/to/CSCE/2110

# 1. Remove old submodule refs (does NOT delete remote repos)
git submodule deinit -f sim-city labs
git rm sim-city labs

# 2. Add at new paths
git submodule add git@github.com:SamGu-NRX/2110-sim-city.git assignments/sim-city
git submodule add git@github.com:SamGu-NRX/2110-labs.git labs

# 3. Update .gitignore to allow assignments/
# 4. Commit and push
git add .gitmodules assignments/ .gitignore
git commit -m "Restructure: labs/, assignments/sim-city"
git push origin main
```

## Rollback

If something goes wrong, the remote repos (2110-sim-city, 2110-labs) still have full history. Re-clone and re-add.
