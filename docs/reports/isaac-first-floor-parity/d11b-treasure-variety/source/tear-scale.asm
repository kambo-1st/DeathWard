007862a7 movss xmm0, dword ptr [edi + 0x4c]
007862ac comiss xmm0, dword ptr [0xb6a614]
007862b3 movss dword ptr [esp + 0x14], xmm0
007862b9 jbe 0x7862ce
007862bb call 0x68f440
007862c0 addss xmm0, dword ptr [0xb6a614]
007862c8 movss dword ptr [esp + 0x14], xmm0
007862ce movss xmm0, dword ptr [esp + 0x28]
007862d4 call 0x4228c0
007862d9 cmp byte ptr [esp + 0x24], 0
007862de movss xmm1, dword ptr [esp + 0x14]
007862e4 movss xmm2, dword ptr [esp + 0x28]
007862ea mulss xmm1, dword ptr [0xb6a4a0]
007862f2 mulss xmm2, dword ptr [0xb6a214]
007862fa mulss xmm0, dword ptr [0xb6a384]
00786302 addss xmm1, xmm2
00786306 addss xmm0, xmm1
0078630a mulss xmm0, dword ptr [esp + 0x2c]
00786310 movss dword ptr [edi + 0x4c], xmm0
