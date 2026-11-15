0072f97a push 0
0072f97c push 1
0072f97e mov ecx, edi
0072f980 movd xmm0, eax
0072f984 cvtdq2ps xmm0, xmm0
0072f987 addss xmm0, dword ptr [ebp - 0x42c]
0072f98f movss dword ptr [ebp - 0x42c], xmm0
0072f997 call 0x73b3b0
0072f99c push 1
0072f99e lea ecx, [edi + 0x1450]
0072f9a4 movd xmm0, eax
0072f9a8 cvtdq2ps xmm0, xmm0
0072f9ab addss xmm0, dword ptr [ebp - 0x42c]
0072f9b3 movss dword ptr [ebp - 0x42c], xmm0
