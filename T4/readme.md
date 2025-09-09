gcc -fopenmp 1d-openMP.c -o 1d-openMP.exe

# Plot Timing

Input Size -           | 10   | 50    | 100   | 500    | 1000    | 5000     | 10000     | 
Sequential -           | 2e-6 | 11e-6 | 40e-6 | 899e-6 | 2276e-6 | 67489e-6 | 263344e-6 |
1d-OpenMp-2Threads -   | 3e-6 | 9e-6 | 26e-6 | 560e-6 | 2276e-6 | 58517-6 | 253819-6 |
