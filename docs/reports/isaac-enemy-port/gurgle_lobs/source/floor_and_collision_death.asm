00636de5 movss xmm1, dword ptr [edi + 0x360]
00636ded comiss xmm1, dword ptr [0xb6ae98]
00636df4 ja 0x636e08
00636df6 cmp byte ptr [edi + 0x188], 0
00636dfd je 0x636e0f
00636dff comiss xmm1, dword ptr [0xb6af28]
00636e06 jb 0x636e0f
00636e08 mov byte ptr [edi + 0x16b], 1
