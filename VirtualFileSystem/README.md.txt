# Virtual File System (VFS) in C

## Overview
This project implements a simple **Virtual File System** (VFS) using the C programming language.  
It simulates basic file and directory management in memory — similar to how an operating system organizes data on disk.

## Design Summary
- The system uses a **doubly linked list** to manage free disk blocks.
- Each directory maintains a **circular linked list** of its entries (files or subdirectories).
- Files store their data in simulated disk blocks (an in-memory 2D array).

## Key Functionalities
- Create directories and files
- Write and read file data
- Delete files and reuse freed blocks
- List directory contents
- Display disk usage statistics

## How It Works
When the program runs, it:
1. Initializes a virtual disk of 1024 blocks.
2. Creates a directory `/docs`.
3. Creates a file `notes.txt` under `/docs`.
4. Writes text into the file.
5. Reads and prints its contents.
6. Deletes the file.
7. Displays updated disk status.

## Example Output
