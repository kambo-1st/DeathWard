00730c0e mov eax, dword ptr [ebp - 0x428]
00730c14 movss xmm0, dword ptr [0xb6aa0c]
00730c1c mulss xmm1, dword ptr [eax + 0x1868]
00730c24 divss xmm0, xmm1
00730c28 subss xmm0, dword ptr [0xb6a614]
00730c30 movss dword ptr [ebp - 0x448], xmm0
