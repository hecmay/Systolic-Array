#!/bin/bash

# Check if the user provided a filename as an argument
if [ $# -ne 1 ]; then
    echo "Usage: $0 <filename>"
    exit 1
fi

# Store the filename from the command line argument
filename="$1"

sed -i 's/HLS RESOURCE/HLS BIND_STORAGE/g' "$filename"
sed -i 's/core=RAM_2P_BRAM/type=RAM_2P impl=BRAM/g' "$filename"
sed -i 's/core=FIFO_SRL/type=FIFO impl=SRL/g' "$filename"

# Check if the sed command was successful
if [ $? -eq 0 ]; then
    echo "Replacement completed successfully in $filename"
else
    echo "An error occurred while replacing text in $filename"
fi