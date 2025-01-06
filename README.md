# Page-Replacement-Algorithms

This C program simulates the most common page replacement algorithms used in operating systems to manage virtual memory. The program implements the following page replacement algorithms:

- **FIFO (First-In-First-Out)**  
- **LRU (Least Recently Used)**  
- **LFU (Least Frequently Used)**  
- **Random**  
- **Weighted Random**

The program reads a list of page accesses from a file (`input.txt`) and applies the page replacement algorithms to determine the number of page faults for each algorithm.

## Requirements

- A C compiler (e.g., GCC)
- A Linux/Unix-based operating system
- A file named `input.txt` containing page access sequences.

Example input.txt 
```
0, 1, 2, 1, 0, 3, 2, 1, 4, 3, 2, 5, 4, 3, 6, 5, 4, 7, 6, 5
0, 0, 1, 1, 2, 0, 1, 3, 0, 1, 3, 0, 4, 3, 0, 4, 3, 2, 4, 3
0, 0, 1, 1, 2, 3, 4, 0, 1, 5, 2, 3, 0, 1, 4, 6, 2, 0, 1, 3, 5, 4, 0, 1
1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4
1, 2, 3, 4, 1, 5, 6, 7, 1, 5, 8, 9, 1, 5, 8, 0, 1, 5, 10, 11
```
