006860e7 movss xmm1, dword ptr [edi + 0x2fc]
006860ef mov eax, edx
006860f1 movss xmm2, dword ptr [edi + 0x2f4]
006860f9 and eax, 0x20
006860fc or eax, 0
006860ff movss dword ptr [edi + 0x2f8], xmm1
00686107 movaps xmm0, xmm2
0068610a addss xmm0, xmm1
0068610e movss dword ptr [edi + 0x2fc], xmm0
