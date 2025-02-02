section .text
default rel
global x86

x86:

    xorps xmm0, xmm0
    xorps xmm3, xmm3
    mov r10, rcx

L1:
    movsd xmm0, [r8]
    movsd xmm1, [r9]
    mulsd xmm0, xmm1           ; multiply a[i] * b[i]
    addsd xmm3, xmm0           ; add the answer to xmm3

    add r8, 8
    add r9, 8

    dec r10
    jnz L1

    movsd [rdx], xmm3          ; store the ans

    ret
