00732e47 push 0xc
00732e49 lea ecx, [edi + 0x15fc]
00732e4f call 0x430970
00732e54 push 0xb
00732e56 lea ecx, [edi + 0x15fc]
00732e5c mov esi, dword ptr [eax]
00732e5e call 0x430970
00732e63 mov edi, dword ptr [ebp - 0x428]
00732e69 movd xmm1, esi
00732e6d cvtdq2ps xmm1, xmm1
00732e70 movd xmm0, dword ptr [eax]
00732e74 mulss xmm1, dword ptr [0xb6a480]
00732e7c cvtdq2ps xmm0, xmm0
00732e7f mulss xmm0, dword ptr [0xb6a434]
00732e87 subss xmm1, xmm0
00732e8b movss dword ptr [ebp - 0x450], xmm1
