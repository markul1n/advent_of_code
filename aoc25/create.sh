#!/bin/bash

DAY=$1

if [ -z "$DAY" ]; then
    echo "Usage: $0 <day_number>"
    exit 1
fi

FOLDER="day_$DAY"
FILE_CPP="day${DAY}.cpp"

# Create folder
mkdir -p "$FOLDER"

# Copy template
cp template.cpp "$FOLDER/$FILE_CPP"

# Create input file
touch "$FOLDER/input.txt"

echo "Created $FOLDER with $FILE_CPP and input.txt"
