00517f60 movss xmm0, dword ptr [eax + 0x2b8]
00517f68 movss xmm1, dword ptr [eax + 0x2bc]
00517f70 lea eax, [ebp - 0x38]
00517f73 mulss xmm0, dword ptr [0xb6a974]
00517f7b mov ecx, dword ptr [ecx + 0x18190]
00517f81 mulss xmm1, dword ptr [0xb6a974]
00517f89 addss xmm0, dword ptr [ebp - 0x38]
00517f8e movss dword ptr [esp + 8], xmm3
00517f94 addss xmm1, dword ptr [ebp - 0x34]
00517f99 movss dword ptr [esp + 4], xmm3
00517f9f movss dword ptr [esp], xmm3
00517fa4 push eax
00517fa5 lea eax, [ebp - 0x50]
00517fa8 movss dword ptr [ebp - 0x38], xmm0
00517fad push eax
00517fae movss dword ptr [ebp - 0x34], xmm1
