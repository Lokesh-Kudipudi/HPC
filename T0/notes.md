# Task - Text

Your job is to measure performance, find bottlenecks, and suggest optimizations using timing functions and GPROF.

Task:
You have a dataset of simulated daily temperatures for 50 years (≈ 18,250 values).
Implement two versions to sort this dataset: Bubble Sort (for baseline) and Quicksort (efficient approach)
Measure: Execution time for each algorithm.
GPROF report for each.
Analyze:

1. Which is faster and why?
2. Measure and compare the execution time of different algorithms.
3. Identify performance bottlenecks using GPROF.
4. Analyze how problem size affects performance.

# What I observed

1. mysortqs.c with 1M elements - 0.29s
2. mysortqs.c with 5M elements - 2.31s
3. mysortqs.c with 10M elements - 6.07s
4. Partition is taking more time in Quick Sort followed by swap function
5. I made the swap function inline for 1M - 0.21s
6. I made the swap function inline for 10M - 5.22s

# To do

1. Plot a graph of time vs size for without optimization, o1, o2 and o3 compiler optimizations
