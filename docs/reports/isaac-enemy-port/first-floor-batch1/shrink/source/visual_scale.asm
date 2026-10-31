00697d3f movss xmm1, dword ptr [esi + 0x30c]
00697d47 mov ecx, esi
00697d49 movaps xmm0, xmm1
00697d4c mov dword ptr [esi + 0xb88], 0x3f800000
00697d56 mulss xmm0, dword ptr [0xbc7a28]
00697d5e mulss xmm1, dword ptr [0xbc7a2c]
00697d66 movss dword ptr [esi + 0xd8], xmm0
00697d6e movss dword ptr [esi + 0xdc], xmm1
