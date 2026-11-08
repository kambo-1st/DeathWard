009624f0 push ebp
009624f1 mov ebp, esp
009624f3 sub esp, 8
009624f6 push esi
009624f7 mov esi, ecx
009624f9 movss xmm1, dword ptr [esi]
009624fd movss xmm2, dword ptr [esi + 4]
00962502 movaps xmm0, xmm1
00962505 mulss xmm0, xmm1
00962509 movss dword ptr [ebp - 4], xmm1
0096250e movaps xmm1, xmm2
00962511 mulss xmm1, xmm2
00962515 movss dword ptr [ebp - 8], xmm2
0096251a addss xmm0, xmm1
0096251e call 0x4228c0
00962523 comiss xmm0, dword ptr [0xb6a18c]
0096252a jbe 0x962553
0096252c movss xmm1, dword ptr [0xb6a614]
00962534 divss xmm1, xmm0
00962538 movss xmm0, dword ptr [ebp - 4]
0096253d mulss xmm0, xmm1
00962541 movss dword ptr [esi], xmm0
00962545 movss xmm0, dword ptr [ebp - 8]
