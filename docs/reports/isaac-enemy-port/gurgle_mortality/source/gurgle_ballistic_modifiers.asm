0050987f movss xmm1, dword ptr [esi + 0x2b8]
00509887 add esp, 0xc
0050988a movss xmm0, dword ptr [esi + 0x368]
00509892 subss xmm0, dword ptr [0xb6a4c4]
0050989a mulss xmm1, dword ptr [0xb6a4a0]
005098a2 movss xmm2, dword ptr [esi + 0x2bc]
005098aa mulss xmm2, dword ptr [0xb6a4a0]
005098b2 movss dword ptr [esi + 0x368], xmm0
005098ba movss xmm0, dword ptr [esi + 0x364]
005098c2 movss dword ptr [esi + 0x2b8], xmm1
005098ca movss xmm1, dword ptr [0xb6a50c]
005098d2 mulss xmm0, xmm1
005098d6 movss dword ptr [esi + 0x2bc], xmm2
005098de subss xmm0, dword ptr [0xb6a864]
005098e6 movss dword ptr [esi + 0x364], xmm0
