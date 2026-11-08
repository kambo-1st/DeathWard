007a4687 cdq 
007a4688 idiv dword ptr [ebp - 0x60]
007a468b movss xmm0, dword ptr [0xb6aa3c]
007a4693 movd xmm2, edx
007a4697 movd xmm1, eax
007a469b cvtdq2ps xmm2, xmm2
007a469e cvtdq2ps xmm1, xmm1
007a46a1 mulss xmm2, xmm0
007a46a5 mulss xmm1, xmm0
007a46a9 addss xmm2, xmm0
007a46ad addss xmm1, dword ptr [0xb6ab20]
