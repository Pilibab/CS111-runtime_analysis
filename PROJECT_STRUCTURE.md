# CS111 Runtime Analysis Project Structure

## Project Overview
This project benchmarks and compares the performance of six sorting algorithms (Selection, Bubble, Insertion, Merge, Quick, and Heap Sort) on both random and sorted input arrays. It measures execution times and validates correctness of sorting implementations.

---

## Directory Tree with File Descriptions

```
CS111-runtime_analysis/
│
├── random/                                 # Output directory for benchmarks on random input arrays
│   ├── average_results.csv                 # CSV file containing average runtime for each algorithm across multiple runs
│   ├── before_after.txt                    # Text file showing sample array before and after sorting
│   └── detailed_runs.csv                   # CSV file with detailed results for each individual benchmark run
│
├── sorted/                                 # Output directory for benchmarks on sorted (pre-ordered) input arrays
│   ├── average_results.csv                 # CSV file containing average runtime for each algorithm (sorted input)
│   ├── before_after.txt                    # Text file showing sample sorted array before and after sorting
│   └── detailed_runs.csv                   # CSV file with detailed results for sorted input benchmarks
│
├── src/                                    # Source code directory
│   │
│   ├── main.c                              # Main program entry point - handles CLI menu, benchmark execution, and CSV file writing
│   ├── main.h                              # Header for main.c - defines Algorithm struct and report functions
│   ├── type.h                              # Type definitions - defines ArrElement, ArrPtr, and SortFunc function pointer types
│   │
│   ├── algorithms/                         # Sorting algorithm implementations
│   │   ├── algorithm.h                     # Header declaring all six sorting function signatures
│   │   ├── bubble.c                        # Bubble Sort implementation - O(n²) time complexity
│   │   ├── heap.c                          # Heap Sort implementation - O(n log n) time complexity
│   │   ├── insertion.c                     # Insertion Sort implementation - O(n²) time complexity
│   │   ├── merge.c                         # Merge Sort implementation - O(n log n) time complexity
│   │   ├── quick.c                         # Quick Sort implementation - O(n log n) average time complexity
│   │   └── selection.c                     # Selection Sort implementation - O(n²) time complexity
│   │
│   ├── benchmark/                          # Benchmarking utilities
│   │   ├── benchmark.c                     # Implementation of benchmark_algorithm() - times algorithm execution and validates correctness
│   │   └── benchmark.h                     # Header defining BenchMark struct (runtime + is_sorted validation flag)
│   │
│   ├── helpers/                            # Utility functions for array manipulation
│   │   ├── array_gen.c                     # Implementation of array generation functions
│   │   ├── array_gen.h                     # Header declaring functions to generate random/sequential arrays and shuffle
│   │   ├── swap.c                          # Implementation of swap utility for element exchange
│   │   └── swap.h                          # Header for swap function used in sorting algorithms
│   │
│   └── tests/                              # Testing and validation utilities
│       ├── test_shuffle.c                  # Test file for validating array shuffle correctness
│       ├── test_sorted.c                   # Test file for validating array sorting correctness
│       ├── validation.c                    # Implementation of validation functions
│       └── validation.h                    # Header declaring validation functions (validate_sort, validate_shuffle, etc.)
│
├── Makefile                                # Build configuration - compiles all source files and generates executable
├── README.md                               # Project documentation
└── .gitignore                              # Git ignore rules
```

---

## Key File Descriptions

### Core Files
- **main.c/main.h**: Orchestrates the entire benchmark process - loads algorithms, generates test data, measures runtimes, and outputs results to CSV files
- **type.h**: Centralizes type definitions to ensure consistency across the project (element type, array pointer, function pointer for sort functions)

### Algorithm Implementations (`src/algorithms/`)
All sorting algorithms take an array pointer and size, sorting in-place:
- **bubble.c**: Repetitive pairwise comparisons; slowest but simple O(n²)
- **insertion.c**: Builds sorted portion incrementally; O(n²) but efficient for small/nearly-sorted data
- **selection.c**: Finds minimum repeatedly; consistent O(n²) regardless of input
- **merge.c**: Divide-and-conquer recursive approach; O(n log n) stable but requires extra space
- **quick.c**: Divide-and-conquer with pivot partitioning; O(n log n) average but worst-case O(n²)
- **heap.c**: Builds heap structure then extracts elements; O(n log n) guaranteed, in-place

### Support Libraries
- **benchmark.c/benchmark.h**: Wraps sorting function calls with `clock()` timing, returns runtime and correctness validation
- **array_gen.c/array_gen.h**: Generates random arrays, sequential arrays, and performs Fisher-Yates shuffle
- **swap.c/swap.h**: Simple element swap utility used by sorting algorithms
- **validation.c/validation.h**: Validates array is sorted correctly and validates shuffle randomness (checks no more than 10% elements remain in original position)

---

## Output Files

### Random Input Results
- `random/average_results.csv` - Average execution time for each algorithm across all runs
- `random/detailed_runs.csv` - Individual run data for statistical analysis
- `random/before_after.txt` - Sample data snapshot

### Sorted Input Results
- `sorted/average_results.csv` - Average execution time on pre-sorted data (tests best-case performance)
- `sorted/detailed_runs.csv` - Detailed run data for sorted input
- `sorted/before_after.txt` - Sample sorted data snapshot
