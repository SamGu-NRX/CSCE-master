#!/bin/bash

# Find the Git repository root
GIT_ROOT=$(git rev-parse --show-toplevel 2>/dev/null)

if [ -z "$GIT_ROOT" ]; then
    echo "ERROR: Not in a Git repository. Please run this script from within your master Git repository."
    exit 1
fi

# Change to the Git repository root to ensure all file operations are relative to it
cd "$GIT_ROOT" || exit 1

echo "Operating from Git repository root: $(pwd)"
echo "---------------------------------------------------------"

# --- Configuration ---
SUBMODULES_LIST_FILE="submodules.txt"
GITIGNORE_FILE=".gitignore"
MASTER_README="README.md"
GITMODULES_FILE=".gitmodules" # Automatically created/managed by git

# --- Utility Functions ---

# Function to extract repository name from an SSH URL
get_repo_name() {
    local url="$1"
    # Expected format: git@host:user/repo.git
    # Extract "user/repo.git", then "repo.git", then "repo"
    basename_with_ext=$(basename "$url")
    repo_name="${basename_with_ext%.git}"
    echo "$repo_name"
}

# --- Main Logic ---

echo "Starting submodule synchronization from $SUBMODULES_LIST_FILE..."
echo "---------------------------------------------------------"

STAGED_ANY_CHANGES=false
ANY_ERRORS_OCCURRED=false

# Ensure base .gitignore rules exist only once at the beginning
echo "Ensuring base .gitignore rules..."
if [ ! -f "$GITIGNORE_FILE" ]; then
    echo "*" > "$GITIGNORE_FILE"
    echo "!$GITIGNORE_FILE" >> "$GITIGNORE_FILE"
    echo "!$MASTER_README" >> "$GITIGNORE_FILE"
    echo "!$GITMODULES_FILE" >> "$GITIGNORE_FILE"
    echo "Created basic $GITIGNORE_FILE."
    git add "$GITIGNORE_FILE" # Stage initial .gitignore immediately
    STAGED_ANY_CHANGES=true
fi
# Note: Specific submodule un-ignore rules are handled in the loop.

# Read each line from submodules.txt
while IFS= read -r url || [[ -n "$url" ]]; do
    # Skip empty lines and comments
    [[ -z "$url" || "$url" =~ ^#.* ]] && continue

    submodule_path=$(get_repo_name "$url")

    echo "Processing submodule: $submodule_path (URL: $url)"

    # --- Start of robust .gitignore handling for this specific submodule_path ---
    local_gitignore_for_sub_changed=false

    # Remove any existing ignore/un-ignore rule for this submodule path
    # Check if a rule exists for this path to avoid modifying the file unnecessarily
    if grep -qE "^!$submodule_path/$|^$submodule_path/$" "$GITIGNORE_FILE"; then
        echo "  Cleaning existing ignore/un-ignore rules for '$submodule_path/' from $GITIGNORE_FILE."
        # Use sed -i for in-place edit (requires different syntax for macOS vs Linux)
        if [[ "$OSTYPE" == "darwin"* ]]; then # macOS
          sed -i '' "/^$submodule_path\//d" "$GITIGNORE_FILE"
          sed -i '' "/^!$submodule_path\//d" "$GITIGNORE_FILE"
        else # Linux (and others)
          sed -i "/^$submodule_path\//d" "$GITIGNORE_FILE"
          sed -i "/^!$submodule_path\//d" "$GITIGNORE_FILE"
        fi
        local_gitignore_for_sub_changed=true
    fi

    # Ensure the un-ignore rule for the submodule path is always present *at the end* of the file
    if ! grep -q "!$submodule_path/" "$GITIGNORE_FILE"; then
        echo "!$submodule_path/" >> "$GITIGNORE_FILE"
        echo "  Added '!$submodule_path/' to $GITIGNORE_FILE."
        local_gitignore_for_sub_changed=true
    fi

    if [ "$local_gitignore_for_sub_changed" = true ]; then
        git add "$GITIGNORE_FILE" # Stage the .gitignore changes immediately
        STAGED_ANY_CHANGES=true
    fi
    # --- End of robust .gitignore handling ---


    # Now, proceed with submodule operations, confident that .gitignore is correctly configured
    # Check if submodule already exists and is configured in .gitmodules
    is_configured_in_gitmodules=$(grep -q "path = $submodule_path" "$GITMODULES_FILE" 2>/dev/null; echo $?) # 0 if found, 1 if not

    if [ "$is_configured_in_gitmodules" -eq 0 ]; then
        echo "  '$submodule_path' is configured in .gitmodules."
        # Check if the local directory exists and is a valid Git repo/gitlink that git recognizes
        if git submodule status "$submodule_path" > /dev/null 2>&1; then
            echo "  Local directory '$submodule_path' exists and is a Git repo. Updating it."
            if git submodule update --remote "$submodule_path"; then
                echo "  Submodule '$submodule_path' updated successfully."
                # We assume git submodule update --remote also stages the gitlink if it changed.
                # Explicitly add it to be sure, only if update succeeded.
                git add "$submodule_path"
                STAGED_ANY_CHANGES=true
            else
                echo "  WARNING: Failed to update submodule '$submodule_path'. Check access and remote. (Skipping this submodule)"
                ANY_ERRORS_OCCURRED=true
            fi
        else
            echo "  Local directory '$submodule_path' is missing or not a proper Git repo, despite being configured. Re-adding."
            # Remove existing non-git dir if present to avoid conflicts during re-add
            if [ -d "$submodule_path" ]; then
                rm -rf "$submodule_path"
            fi
            # Now proceed to add as if it were a new submodule (using -f)
            if ! git submodule add -f "$url" "$submodule_path"; then
                echo "  ERROR: Failed to re-add submodule '$submodule_path' from '$url'. Check URL/access. (Skipping this submodule)"
                if [ -d "$submodule_path" ]; then rm -rf "$submodule_path"; fi # Clean up partial clone
                ANY_ERRORS_OCCURRED=true
            else
                echo "  Submodule '$submodule_path' re-added successfully."
                git add "$submodule_path" "$GITMODULES_FILE" # Stage submodule gitlink and .gitmodules
                STAGED_ANY_CHANGES=true
            fi
        fi
        continue # Move to next submodule, already handled
    fi

    # If code reaches here, it's a completely new submodule to add
    echo "  '$submodule_path' is not configured in .gitmodules. Adding as a new submodule."

    # Remove local directory if it exists and is NOT a configured submodule (prevents errors)
    if [ -d "$submodule_path" ]; then
        echo "  Local directory '$submodule_path' exists but not configured as submodule. Removing to add."
        rm -rf "$submodule_path"
    fi

    # Add the submodule (using -f to bypass ignore checks)
    if ! git submodule add -f "$url" "$submodule_path"; then
        echo "  ERROR: Failed to add new submodule '$submodule_path' from '$url'."
        echo "  Please check the URL and ensure you have access (e.g., SSH key setup)."
        if [ -d "$submodule_path" ]; then rm -rf "$submodule_path"; fi # Clean up partial clone
        ANY_ERRORS_OCCURRED=true
        continue # Move to next submodule
    fi

    echo "  Submodule '$submodule_path' added successfully."
    git add "$submodule_path" "$GITMODULES_FILE" # Stage submodule gitlink and .gitmodules
    STAGED_ANY_CHANGES=true

done < "$SUBMODULES_LIST_FILE"

echo "---------------------------------------------------------"

if [ "$STAGED_ANY_CHANGES" = true ]; then
    echo "Submodule synchronization complete. Changes have been staged."
    if [ "$ANY_ERRORS_OCCURRED" = true ]; then
        echo "WARNING: Some errors occurred during processing. Review logs above."
    fi
    echo "Please review them with 'git status' and then commit:"
    echo "  git commit -m \"Sync submodules\""
    echo "  git push origin main"
elif [ "$ANY_ERRORS_OCCURRED" = true ]; then
    echo "Submodule synchronization completed with errors. No new changes were staged for commit."
    echo "Please review the errors above and address them (e.g., SSH key issues)."
else
    echo "No new submodules to add or updates needed."
    echo "All existing submodules seem to be up-to-date and correctly configured."
fi
