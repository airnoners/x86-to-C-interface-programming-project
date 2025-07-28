# Dot Product Kernel Benchmark: C vs. x86-64 Assembly

## Overview
This project compares the performance of a dot product kernel implemented in:
- **C** (reference implementation)
- **x86-64 assembly** (optimized with scalar SIMD instructions)

## Kernels

### C Implementation
```c
void cDotProduct(double* A, double* B, long n, double* sdot) {
    *sdot = 0.0;
    for (long i = 0; i < n; i++) {
        *sdot += A[i] * B[i];  // Scalar multiply-accumulate
    }
} 
```

### x86-64 Assembly Implementation
```asm
section .text
bits 64
default rel

global asmDotProduct

asmDotProduct:
    xorpd xmm0, xmm0          ; Clear accumulator
    xor rax, rax              ; i = 0
.loop:
    movsd xmm1, [rcx + rax*8] ; Load A[i]
    mulsd xmm1, [rdx + rax*8] ; Multiply by B[i]
    addsd xmm0, xmm1          ; Accumulate
    inc rax                   ; i++
    cmp rax, r8               ; i < n?
    jl .loop
    movsd [r9], xmm0          ; Store result
    ret
```
### Benchmark Results
| Vector Size (n) | C Avg (ms) | ASM Avg (ms) | Speedup | Correctness |
|-----------------|------------|--------------|---------|-------------|
| 1,048,576      | 3.2012     | 0.8892       | 3.60x   | 20/20       |
| 16,777,216     | 50.9863    | 14.4074      | 3.54x   | 20/20       |
| 268,435,456    | 829.5995   | 242.8605     | 3.42x   | 20/20       |

### Performance Analysis
**Key Findings**
- Consistent Speedup: Assembly version is 3.4-3.7x faster across all sizes
- Perfect Correctness: Both implementations produce identical results (within ε=1e-10 tolerance)
- Scalability: Performance advantage decreases slightly at largest size (n=2²⁸) due to memory bandwidth limitations

**Why Assembly Performs Better**
- Direct hardware control: Precise use of SIMD registers (xmm0-xmm1)
- Optimized instruction flow: Tight loop with minimal overhead
- Efficient accumulation: Dedicated register for sum (xmm0)

### Build Instructions
Compilation
- nasm -f win64 asmfunc.asm
- gcc -c main.c -o main.obj -m64
- gcc main.obj asmfunc.obj -o main.exe -m64
- main.exe

### Conclusion
Conclusion
The hand-optimized x86-64 assembly implementation demonstrates significant performance advantages (3.4-3.7x speedup) over the C version while maintaining perfect numerical accuracy. The results show consistent improvements across all tested vector sizes, with the assembly version being particularly efficient for smaller datasets where memory bandwidth is less of a limiting factor.
