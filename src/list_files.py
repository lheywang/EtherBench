# ================================================================================
# file : list_files.py
# brief : List all files into a folder, before adding it into a CMakeLists.txt
#
# author : l.heywang <leonard.heywang@proton.me>
# date : 23/02/2026
# ================================================================================

import glob
import os

# Set the extensions you want to track
extensions = ['*.c', '*.cpp']

# Grab all matching files recursively from the current directory
source_files = []
for ext in extensions:
    # The '**/' and recursive=True tells Python to look in all subfolders too
    source_files.extend(glob.glob(f'**/{ext}', recursive=True))

# Sort alphabetically so your CMakeLists stays beautifully organized
source_files.sort()

# Generate the CMake-ready output
if source_files:
    print("list(APPEND SOURCES")
    for file in source_files:
        # CMake strictly requires forward slashes, even on Windows
        clean_path = file.replace('\\', '/')
        print(f"    {clean_path}")
    print(")")
else:
    print("# No source files found in the current directory or subdirectories.")




