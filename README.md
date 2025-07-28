# x86-64 to C Interface: Dot Product Optimization

![Benchmark Results](/docs/screenshots/benchmark_summary.png) *Benchmark output*

## Project Overview
This project demonstrates high-performance dot product computation through:
- A pure C implementation (reference)
- An optimized x86-64 assembly version using scalar SIMD instructions
- Rigorous benchmarking and correctness validation

**Key Features:**
- 3.4–3.6x speedup over C with perfect numerical accuracy
- Handles vectors up to 268,435,456 elements (2²⁸)
- Fully compliant with Windows x64 calling conventions

## Technical Specifications

### Kernel Implementations
| Component       | Technology Used              | Key Instructions           |
|----------------|------------------------------|---------------------------|
| C Version      | Standard C                   | `for` loop, `+=` operator |
| ASM Version    | x86-64 Assembly (NASM)       | `movsd`, `mulsd`, `addsd` |

### Benchmarking
- Tests vector sizes: 2²⁰, 2²⁴, 2²⁸
- 20 runs per size for statistical significance
- High-resolution timing via `QueryPerformanceCounter`

## Results Summary

| Vector Size (n) | C Avg (ms) | ASM Avg (ms) | Speedup | Correctness |
|-----------------|------------|--------------|---------|-------------|
| 1,048,576      | 3.2012     | 0.8892       | 3.60x   | 20/20       |
| 16,777,216     | 50.9863    | 14.4074      | 3.54x   | 20/20       |
| 268,435,456    | 829.5995   | 242.8605     | 3.42x   | 20/20       |

## Getting Started

### Prerequisites
- NASM (v2.15+)
- MinGW-w64 or Visual Studio (x64)
- Windows 10/11 (for performance counters)

### Build & Run
nasm -f win64 asmfunc.asm
gcc -c main.c -o main.obj -m64
gcc main.obj asmfunc.obj -o main.exe -m64
main.exe
