00731524 push 0
00731526 push 4
00731528 mov ecx, edi
0073152a add esi, eax
0073152c call 0x73b3b0
00731531 add eax, esi
00731533 lea ecx, [edi + 0x1450]
00731539 push 0xc9
0073153e movd xmm0, eax
00731542 cvtdq2ps xmm0, xmm0
00731545 mulss xmm0, dword ptr [0xb6a480]
0073154d addss xmm0, dword ptr [ebp - 0x42c]
00731555 movss dword ptr [ebp - 0x42c], xmm0
