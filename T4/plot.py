import matplotlib.pyplot as plt

# Data from the files
sizes = [10, 50, 100, 500, 1000, 5000, 10000, 20000, 30000, 50000]

seq_times = [0, 0, 0, 0.001, 0.005, 0.079, 0.315, 1.296, 3.514, 63.687]
omp_2_times = [0, 0.00099993, 0.00099993, 0.00099993, 0.00300002,
               0.06099987, 0.18899989, 0.68799996, 1.64000010, 67.94300008]
omp_4_times = [0, 0, 0, 0.00200009, 0.00500011, 0.03099990,
               0.11500001, 0.41900015, 0.96299982, 38.15100002]
omp_8_times = [0, 0, 0, 0, 0.00399995, 0.03499985,
               0.10800004, 0.41100001, 0.96799994, 32.55399990]
omp2_4_times = [0, 0, 0.00199986, 0.00199986, 0.00300002, 0.02799988,
                0.09799981, 0.43000007, 1.09300017, 51.50799990]
omp2_8_times = [0, 0, 0, 0, 0.00300002, 0.02900004,
                0.10500002, 0.37100005, 0.99500012, 44.21700001]

# Plotting
plt.figure(figsize=(10, 6))
plt.plot(sizes, seq_times, marker='o', label="Sequential")
plt.plot(sizes, omp_2_times, marker='o', label="OpenMP - 1D - 2 threads")
plt.plot(sizes, omp_4_times, marker='o', label="OpenMP - 1D - 4 threads")
plt.plot(sizes, omp_8_times, marker='o', label="OpenMP - 1D - 8 threads")
plt.plot(sizes, omp2_4_times, marker='o', label="OpenMP - 2D - 8 threads")
plt.plot(sizes, omp2_8_times, marker='o', label="OpenMP - 2D - 8 threads")


plt.xlabel("Input Size")
plt.ylabel("Execution Time (seconds)")
plt.title("Execution Time vs Input Size for Different Thread Counts")
plt.legend()
plt.grid(True)
plt.yscale("log")  # log scale for better visualization of wide range
plt.show()
