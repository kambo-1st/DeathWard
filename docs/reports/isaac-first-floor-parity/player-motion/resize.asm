00962860 push ebp
00962861 mov ebp, esp
00962863 sub esp, 8
00962866 push esi
00962867 mov esi, ecx
00962869 movss xmm1, dword ptr [esi]
0096286d movss xmm2, dword ptr [esi + 4]
00962872 movaps xmm0, xmm1
00962875 mulss xmm0, xmm1
00962879 movss dword ptr [ebp - 4], xmm1
0096287e movaps xmm1, xmm2
00962881 mulss xmm1, xmm2
00962885 movss dword ptr [ebp - 8], xmm2
0096288a addss xmm0, xmm1
0096288e call 0x4228c0
00962893 comiss xmm0, dword ptr [0xb6a18c]
0096289a jbe 0x9628c0
0096289c movss xmm1, dword ptr [ebp + 8]
009628a1 divss xmm1, xmm0
009628a5 movss xmm0, dword ptr [ebp - 4]
009628aa mulss xmm0, xmm1
009628ae movss dword ptr [esi], xmm0
009628b2 movss xmm0, dword ptr [ebp - 8]
009628b7 mulss xmm0, xmm1
009628bb movss dword ptr [esi + 4], xmm0
009628c0 pop esi
009628c1 mov esp, ebp
009628c3 pop ebp
009628c4 ret 4
