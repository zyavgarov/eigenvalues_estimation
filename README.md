# Estimation of eigenvalues for a graph on points with distance O(N)

This is application for a university work.
This file contains only the description of running the program.
Description of the purpose can be found in the work itself.

For running the program computer must have at least 3.5 GB of RAM.
Normally it takes 7 hours to complete but there is big area for efficiency improvements.

Compilation: `g++ main.cpp Cell.cpp launcher.cpp -o main.exe `

Running on Windows: `./main.exe`

By default, the results are saved to 4 files:
- `eigenalues_1.txt` (l_1 metrics with N/10)
- `eigenalues_infty.txt` (l_infinity metrics with N/10)
- `eigenalues_2_10.txt` (l_2 metrics with N/10)
- `eigenalues_2_2.txt` (l_2 metrics with N/2)

However, editing of main.cpp and recompilation can give an opportunity for different calculations.
Instructions for such editing can be found in main.cpp