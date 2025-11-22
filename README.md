# Array Sorting using Pipes and fork()

This program takes an array of integers from the command line, sends it from the parent process to the child process using a pipe, and the child performs Bubble Sort.
After sorting, the child sends the sorted array back to the parent through a second pipe.

# Features

Uses two pipes (p1 for parent → child data, p2 for child → parent data).
Demonstrates fork(), pipe(), read(), write().
Child performs bubble sort.
Parent prints final sorted array.
Demonstrates IPC (Inter-Process Communication).
