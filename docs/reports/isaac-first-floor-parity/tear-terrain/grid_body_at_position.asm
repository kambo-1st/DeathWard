00447f80 push ebp
00447f81 mov ebp, esp
00447f83 mov edx, dword ptr [ebp + 8]
00447f86 movss xmm1, dword ptr [0xb6aa3c]
00447f8e movss xmm2, dword ptr [0xb6a480]
00447f96 push esi
00447f97 movss xmm0, dword ptr [edx]
00447f9b subss xmm0, xmm1
00447f9f divss xmm0, xmm1
00447fa3 addss xmm0, xmm2
00447fa7 cvttss2si esi, xmm0
00447fab test esi, esi
00447fad js 0x447fe8
00447faf mov eax, dword ptr [ecx + 0xc]
00447fb2 cmp esi, eax
00447fb4 jge 0x447fe8
00447fb6 movss xmm0, dword ptr [edx + 4]
00447fbb subss xmm0, dword ptr [0xb6ab20]
00447fc3 divss xmm0, xmm1
00447fc7 addss xmm0, xmm2
00447fcb cvttss2si edx, xmm0
00447fcf test edx, edx
00447fd1 js 0x447fe8
00447fd3 cmp edx, dword ptr [ecx + 0x10]
00447fd6 jge 0x447fe8
00447fd8 imul eax, edx
00447fdb add eax, esi
00447fdd js 0x447fe8
00447fdf mov eax, dword ptr [ecx + eax*4 + 0x24]
00447fe3 pop esi
00447fe4 pop ebp
00447fe5 ret 4
00447fe8 xor eax, eax
00447fea pop esi
00447feb pop ebp
00447fec ret 4
