00757908 call 0x6c3d90
0075790d movd xmm0, eax
00757911 cvtdq2pd xmm0, xmm0
00757915 shr eax, 0x1f
00757918 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
00757921 cvtpd2ps xmm0, xmm0
00757925 mulss xmm0, dword ptr [0xb6a19c]
0075792d mulss xmm0, dword ptr [0xb6a350]
00757935 subss xmm0, dword ptr [edi + 0x13c0]
0075793d jmp 0x75794e
0075793f movss xmm0, dword ptr [edi + 0x13c0]
00757947 xorps xmm0, xmmword ptr [0xb6c9b0]
0075794e mov eax, esi
00757950 push ecx
00757951 mov ecx, esi
00757953 movss dword ptr [eax + 0x364], xmm0
