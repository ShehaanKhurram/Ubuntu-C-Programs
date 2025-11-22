# 1.Array Sorting using Pipes and fork()
This program takes an array of integers from the command line, sends it from the parent process to the child process using a pipe, and the child performs Bubble Sort.
After sorting, the child sends the sorted array back to the parent through a second pipe.

# Features
Uses two pipes (p1 for parent → child data, p2 for child → parent data).
Demonstrates fork(), pipe(), read(), write().
Child performs bubble sort.
Parent prints final sorted array.
Demonstrates IPC (Inter-Process Communication).
# ______________________________________________________

# 2. Minimum of Each Half using Two Child Processes
This program reads an array from the user, divides it into two equal halves, and creates two child processes.
Each child finds the minimum element in its respective half using inter-process communication through pipes.

# Features
Uses two fork() calls → creates Child 1 and Child 2.
Multiple pipes (p1, p2, p3, p4) for sending and receiving data.
Each child receives its half via a pipe, computes the minimum, and sends the result back.
Parent waits for both children using waitpid() and prints both minimums.
Demonstrates advanced IPC + multi-process computation.
