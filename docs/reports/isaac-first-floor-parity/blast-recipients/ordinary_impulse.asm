006d1c7f mov eax, dword ptr [edi + 0x28]
006d1c82 movss xmm3, dword ptr [ebp - 0x20]
006d1c87 movss xmm4, dword ptr [ebp - 0x18]
006d1c8c movss xmm1, dword ptr [edi + 0x2b8]
006d1c94 divss xmm3, xmm2
006d1c98 divss xmm4, xmm2
006d1c9c movss xmm2, dword ptr [edi + 0x2bc]
006d1ca4 mulss xmm3, xmm0
006d1ca8 mulss xmm4, xmm0
006d1cac cmp eax, 1
006d1caf jne 0x6d1b2d
006d1cb5 mulss xmm1, xmm5
006d1cb9 mov dword ptr [ebp - 0x24], 0x41200000
006d1cc0 mulss xmm2, xmm5
006d1cc4 addss xmm1, xmm3
006d1cc8 addss xmm2, xmm4
006d1ccc movaps xmm0, xmm1
006d1ccf movss dword ptr [ebp - 0x1c], xmm1
006d1cd4 mulss xmm0, xmm1
006d1cd8 movaps xmm1, xmm2
006d1cdb movss dword ptr [ebp - 0x20], xmm2
006d1ce0 mulss xmm1, xmm2
006d1ce4 addss xmm0, xmm1
006d1ce8 call 0x4228c0
006d1ced comiss xmm0, dword ptr [0xb6a974]
006d1cf4 lea eax, [ebp - 0x24]
006d1cf7 lea ecx, [ebp - 0x2c]
006d1cfa movss xmm1, dword ptr [ebp - 0x1c]
006d1cff movss dword ptr [ebp - 0x2c], xmm0
006d1d04 cmovbe eax, ecx
006d1d07 comiss xmm0, dword ptr [0xb6a18c]
006d1d0e movss xmm2, dword ptr [eax]
006d1d12 jbe 0x6d1d35
006d1d14 divss xmm2, xmm0
006d1d18 movaps xmm0, xmm2
006d1d1b mulss xmm1, xmm0
006d1d1f movss xmm0, dword ptr [ebp - 0x20]
006d1d24 mulss xmm0, xmm2
006d1d28 movss dword ptr [edi + 0x2bc], xmm0
006d1d30 jmp 0x6d1b45
006d1d35 movss xmm0, dword ptr [ebp - 0x20]
006d1d3a movss dword ptr [edi + 0x2bc], xmm0
006d1d42 jmp 0x6d1b45
