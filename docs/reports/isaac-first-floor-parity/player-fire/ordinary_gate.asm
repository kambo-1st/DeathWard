00959dee cmp byte ptr [ebp - 0x9d], al
00959df4 je 0x959e39
00959df6 cmp byte ptr [ebp + 0x10], al
00959df9 jne 0x95c703
00959dff comiss xmm2, dword ptr [edi]
00959e02 movss xmm1, dword ptr [0xb6ae44]
00959e0a subss xmm1, dword ptr [edi]
00959e0e movss dword ptr [ebp - 0xd8], xmm1
00959e16 jbe 0x959e32
00959e18 cmp eax, 8
00959e1b jae 0x959e32
00959e1d movaps xmm0, xmm4
00959e20 inc eax
00959e21 addss xmm0, xmm3
00959e25 addss xmm0, dword ptr [edi]
00959e29 comiss xmm2, xmm0
00959e2c movss dword ptr [edi], xmm0
00959e30 ja 0x959e18
00959e32 mov dword ptr [esi + 0x44], 0
