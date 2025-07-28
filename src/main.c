#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <math.h>
#include <immintrin.h>  // For _mm_malloc and _mm_free

#define NUM_TESTS 20
#define EPSILON 1e-10   // For floating-point comparison tolerance

// External ASM function declaration
extern void asmDotProduct(double* A, double* B, long n, double* sdot);

// C version of dot product for correctness and comparison
void cDotProduct(double* A, double* B, long n, double* sdot) {
    *sdot = 0.0;
    for (long i = 0; i < n; i++) {
        *sdot += A[i] * B[i];  // Multiply and accumulate each pair of elements
    }
}

int main() {
    const long sizes[] = {1<<20, 1<<24, 1<<28}; // 2^20, 2^24, 2^28
    srand(time(NULL));

    for (int s = 0; s < 3; s++) {
        long n = sizes[s];
        double *A = _mm_malloc(n * sizeof(double), 32);
        double *B = _mm_malloc(n * sizeof(double), 32);

        if (!A || !B) {
            fprintf(stderr, "Memory allocation failed for n = %ld\n", n);
            return 1;
        }

        // Initialize with random values
        for (long i = 0; i < n; i++) {
            A[i] = (double)rand() / RAND_MAX;
            B[i] = (double)rand() / RAND_MAX;
        }

        double c_result, asm_result;
        LARGE_INTEGER freq, start, end;
        QueryPerformanceFrequency(&freq);

        printf("=== n = 2^%d (%ld) ===\n", (int)(log2(n)), n);
        printf("Run | C Time (ms) | ASM Time (ms) | Correct\n");
        printf("----|-------------|---------------|--------\n");

        double c_time_total = 0, asm_time_total = 0;
        int correct_total = 0;

        for (int i = 0; i < NUM_TESTS; i++) {
            // Time C version
            QueryPerformanceCounter(&start);
            cDotProduct(A, B, n, &c_result);
            QueryPerformanceCounter(&end);
            double c_time = (double)(end.QuadPart - start.QuadPart) * 1000.0 / freq.QuadPart;
            c_time_total += c_time;

            // Time ASM version
            QueryPerformanceCounter(&start);
            asmDotProduct(A, B, n, &asm_result);
            QueryPerformanceCounter(&end);
            double asm_time = (double)(end.QuadPart - start.QuadPart) * 1000.0 / freq.QuadPart;
            asm_time_total += asm_time;

            // Check correctness
            int correct = (fabs(asm_result - c_result) < EPSILON) ? 1 : 0;
            correct_total += correct;

            // Print individual run results
            printf("%3d | %10.4f | %13.4f | %7s\n", 
                   i+1, c_time, asm_time, 
                   correct ? "YES" : "NO");
        }

        // Print summary
        printf("\nSummary for n = 2^%d (%ld):\n", (int)(log2(n)), n);
        printf("C avg: %.4f ms\n", c_time_total / NUM_TESTS);
        printf("ASM avg: %.4f ms\n", asm_time_total / NUM_TESTS);
        printf("Correctness: %d/%d\n", correct_total, NUM_TESTS);
        printf("Speedup: %.2fx\n\n", c_time_total / asm_time_total);

        _mm_free(A);
        _mm_free(B);
    }
    return 0;
}

/* - TO PRINT ONLY RESULTS
int main() {
    const long sizes[] = {1<<20, 1<<24, 1<<28}; // Different test sizes: 2^20, 2^24, 2^28
    srand(time(NULL)); // Seed the random number generator

    for (int s = 0; s < 3; s++) {
        long n = sizes[s]; // Set size of current test
        // Aligned memory allocation for SIMD compatibility
        double *A = _mm_malloc(n * sizeof(double), 32);
        double *B = _mm_malloc(n * sizeof(double), 32);

        // Error handling if allocation fails
        if (!A || !B) {
            fprintf(stderr, "Memory allocation failed for n = %ld\n", n);
            return 1;
        }

        // Initialize vectors A and B with random doubles in [0, 1]
        for (long i = 0; i < n; i++) {
            A[i] = (double)rand() / RAND_MAX;
            B[i] = (double)rand() / RAND_MAX;
        }

        double c_result, asm_result;
        LARGE_INTEGER freq, start, end;
        QueryPerformanceFrequency(&freq); // Get clock frequency for high-precision timing

        // Time C implementation
        double c_time = 0;
        for (int i = 0; i < NUM_TESTS; i++) {
            QueryPerformanceCounter(&start);
            cDotProduct(A, B, n, &c_result);
            QueryPerformanceCounter(&end);
            c_time += (double)(end.QuadPart - start.QuadPart) * 1000.0 / freq.QuadPart;
        }

        // Time ASM implementation
        double asm_time = 0;
        int correct = 0;
        for (int i = 0; i < NUM_TESTS; i++) {
            QueryPerformanceCounter(&start);
            asmDotProduct(A, B, n, &asm_result);
            QueryPerformanceCounter(&end);
            asm_time += (double)(end.QuadPart - start.QuadPart) * 1000.0 / freq.QuadPart;

            // Check if result is within acceptable error margin
            if (fabs(asm_result - c_result) < EPSILON) {
                correct++;
            }
        }

        // Output performance and correctness metrics
        printf("n = 2^%d (%ld)\n", (int)(log2(n)), n);
        printf("C avg: %.4f ms\n", c_time / NUM_TESTS);
        printf("ASM avg: %.4f ms\n", asm_time / NUM_TESTS);
        printf("Correctness: %d/%d\n", correct, NUM_TESTS);
        printf("Speedup: %.2fx\n\n", c_time / asm_time);

        // Free allocated memory
        _mm_free(A);
        _mm_free(B);
    }
    return 0;
}
*/