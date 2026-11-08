0074211c movss xmm1, dword ptr [ebp - 0x50]
00742121 movss xmm0, dword ptr [ebp - 0x60]
00742126 mulss xmm0, xmm0
0074212a mulss xmm1, xmm1
0074212e addss xmm0, xmm1
00742132 call 0x4228c0
00742137 comiss xmm0, dword ptr [0xb6a614]
0074213e jbe 0x74215c
00742140 lea ecx, [ebp - 0x44]
00742143 call 0x9624f0
00742148 movss xmm2, dword ptr [ebp - 0x40]
0074214d movss xmm0, dword ptr [ebp - 0x44]
00742152 movss dword ptr [ebp - 0x50], xmm2
00742157 movss dword ptr [ebp - 0x60], xmm0
