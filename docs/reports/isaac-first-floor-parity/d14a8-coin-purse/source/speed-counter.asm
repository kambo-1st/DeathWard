007339e7 push 0xe
007339e9 lea ecx, [edi + 0x15fc]
007339ef call 0x430970
007339f4 push 0xd
007339f6 lea ecx, [edi + 0x15fc]
007339fc mov esi, dword ptr [eax]
007339fe call 0x430970
00733a03 mov edi, dword ptr [ebp - 0x428]
00733a09 movd xmm1, esi
00733a0d cvtdq2ps xmm1, xmm1
00733a10 movd xmm0, dword ptr [eax]
00733a14 mulss xmm1, dword ptr [0xb6a480]
00733a1c cvtdq2ps xmm0, xmm0
00733a1f mulss xmm0, dword ptr [0xb6a434]
00733a27 subss xmm1, xmm0
00733a2b movss dword ptr [ebp - 0x42c], xmm1
