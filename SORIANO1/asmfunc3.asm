section .text
    default rel

global SIMDX
SIMDX:
    vxorpd xmm0, xmm0, xmm0
    vxorpd xmm3, xmm3, xmm3
    shr rcx, 2
    
.loop:
    vmovupd xmm1, [r8]           ; vector a 2 double
    vmovupd xmm2, [r9]           ; vector b 2 double
    vmulpd xmm4, xmm1, xmm2      ; mul the first pairs
    vaddpd xmm0, xmm0, xmm4      ; add
     
    ; next pair
    vmovupd xmm1, [r8 + 16]
    vmovupd xmm2, [r9 + 16]
    vmulpd xmm4, xmm1, xmm2
    vaddpd xmm3, xmm3, xmm4
    
    add r8, 32
    add r9, 32
    dec rcx
    jnz .loop
 
    vhaddpd xmm0, xmm0, xmm0
   
    vaddpd xmm0, xmm0, xmm0

    movsd [rdx], xmm0   ; storing final ans
    ret

