00731769 call 0x88b920
0073176e movd xmm0, eax
00731772 cvtdq2ps xmm0, xmm0
00731775 mulss xmm0, dword ptr [0xb6a350]
0073177d addss xmm0, dword ptr [ebp - 0x42c]
00731785 addss xmm0, dword ptr [edi]
00731789 movss dword ptr [edi], xmm0
