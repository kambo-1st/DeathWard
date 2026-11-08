006500f0 push ebp
006500f1 mov ebp, esp
006500f3 movss xmm2, dword ptr [ebp + 8]
006500f8 push esi
006500f9 mov esi, ecx
006500fb movaps xmm1, xmm2
006500fe movss dword ptr [esi + 0x360], xmm2
00650106 call 0x650150
0065010b mov eax, dword ptr [0xbfd65c]
00650110 movss dword ptr [esi + 0x2a8], xmm0
00650118 mov eax, dword ptr [eax + 0x18190]
0065011e cmp dword ptr [eax + 8], 0x10
00650122 jne 0x650141
00650124 comiss xmm2, dword ptr [0xb6ae9c]
0065012b mov dword ptr [esi + 0x2a8], 0xc1900000
00650135 jbe 0x650141
00650137 mov dword ptr [esi + 0x360], 0xc0a33333
00650141 pop esi
00650142 pop ebp
