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

### Prerequisites
- NASM 
- MinGW-w64 
- Windows 
