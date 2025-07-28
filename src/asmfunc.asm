section .text
bits 64
default rel

global asmDotProduct

; Function signature:
; void asmDotProduct(double* A (rcx), double* B (rdx), long n (r8), double* sdot (r9))

asmDotProduct:
    xorpd xmm0, xmm0          ; Clear xmm0: xmm0 = 0.0, will hold the final dot product sum
    xor rax, rax              ; Set loop counter i = 0

.loop:
    movsd xmm1, [rcx + rax*8] ; Load A[i] (double) into xmm1
    mulsd xmm1, [rdx + rax*8] ; Multiply xmm1 = A[i] * B[i]
    addsd xmm0, xmm1          ; Accumulate the product into xmm0

    inc rax                   ; i++
    cmp rax, r8               ; Compare i with n
    jl .loop                  ; If i < n, repeat loop

    movsd [r9], xmm0          ; Store the final dot product value into *sdot
    ret                       ; Return from function
