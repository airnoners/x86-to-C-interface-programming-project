# x86-64 to C Interface: Dot Product Optimization

![Benchmark Results](/docs/screenshots/benchmark_summary.png) *Benchmark output*

## Project Overview
This project demonstrates high-performance dot product computation through:
- A pure C implementation (reference)
- An optimized x86-64 assembly version using scalar SIMD instructions
- Rigorous benchmarking and correctness validation

## Technical Specifications

### Kernel Implementations
| Component       | Technology Used              | Key Instructions           |
|----------------|------------------------------|---------------------------|
| C Version      | Standard C                   | `for` loop, `+=` operator |
| ASM Version    | x86-64 Assembly (NASM)       | `movsd`, `mulsd`, `addsd` |

### Benchmarking
- Tests vector sizes: 2²⁰, 2²⁴, 2²⁸
- 20 runs per size for statistical significance

### Prerequisites
- NASM 
- MinGW-w64 
- Windows 

### Link for the video
https://youtu.be/Go8VMpt8YcM
