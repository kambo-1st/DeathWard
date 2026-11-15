0072fb55 push 6
0072fb57 lea ecx, [edi + 0x1450]
0072fb5d movd xmm0, eax
0072fb61 cvtdq2ps xmm0, xmm0
0072fb64 addss xmm0, dword ptr [ebp - 0x42c]
0072fb6c mulss xmm0, dword ptr [0xb6a50c]
0072fb74 movss dword ptr [ebp - 0x42c], xmm0
