00732b12 mov ecx, dword ptr [ebp - 0x428]
00732b18 push 0x1b
00732b1a call 0x78d4c0
00732b1f mov ecx, dword ptr [ebp - 0x428]
00732b25 push 0
00732b27 push 5
00732b29 movd xmm0, eax
00732b2d cvtdq2ps xmm0, xmm0
00732b30 mulss xmm0, dword ptr [0xb6a480]
00732b38 addss xmm0, dword ptr [edi]
00732b3c movss dword ptr [edi], xmm0
