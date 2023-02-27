#!/bin/bash

# Check if a directory name is provided as command line argument
if [ $# -eq 0 ]; then
  # Prompt the user to enter the directory name if not provided
  read -p "Enter the name of the directory: " dir_name
else
  dir_name=$1
fi

# Check if the directory exists
if [ ! -d "$dir_name" ]; then
  echo "Error: The directory '$dir_name' does not exist."
  exit 1
fi

# Scan the directory for files
echo "Scanning the directory '$dir_name' for files..."
echo "Filename                                                Size    Last Modfified"
echo "==============================                          ======  ==============="
for file in "$dir_name"/*; do
  if [ -f "$file" ]; then
    filename=$(basename "$file")
    size=$(stat -c %s "$file")
    last_modified=$(stat -c %y "$file")
    echo "$filename                                                $size  $last_modified"
  fi
done