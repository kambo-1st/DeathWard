0064d5eb movss xmm1, dword ptr [edi + 0x2f4]
0064d5f3 movss xmm0, dword ptr [0xb6a5a4]
0064d5fb call 0x65c960
0064d600 movss xmm3, dword ptr [edi + 0x2f4]
0064d608 mulss xmm0, dword ptr [edi + 0x364]
0064d610 movaps xmm1, xmm3
0064d613 mulss xmm1, dword ptr [0xb6a2cc]
0064d61b movaps xmm2, xmm3
0064d61e mulss xmm2, dword ptr [edi + 0x368]
0064d626 addss xmm1, xmm0
0064d62a addss xmm2, xmm1
0064d62e mulss xmm3, xmm2
0064d632 push ecx
0064d633 movss dword ptr [edi + 0x364], xmm2
0064d63b mov ecx, edi
0064d63d addss xmm3, dword ptr [edi + 0x360]
0064d645 movss dword ptr [esp], xmm3
0064d64a call 0x6500f0
