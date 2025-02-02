
section .text
    default rel

global SIMDY

SIMDY:
    vxorpd ymm0, ymm0, ymm0
    shr rcx, 2

L1:
    vmovupd ymm1, [r8]
    vmovupd ymm2, [r9]
    vmulpd ymm1, ymm1, ymm2
    vaddpd ymm0, ymm0, ymm1

    add r8, 32
    add r9, 32

    loop L1

    ; hori sum 
    vhaddpd ymm0, ymm0, ymm0
    vextractf128 xmm1, ymm0, 1
    addpd xmm0, xmm1

    movsd [rdx], xmm0              ; storing final ans
    ret

