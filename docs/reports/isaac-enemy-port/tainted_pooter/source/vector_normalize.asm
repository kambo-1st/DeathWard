00962560 push ebp
00962561 mov ebp, esp
00962563 push ecx
00962564 mov eax, dword ptr [ecx]
00962566 mov ecx, dword ptr [ecx + 4]
00962569 push esi
0096256a mov esi, dword ptr [ebp + 8]
0096256d mov dword ptr [esi], eax
0096256f movss xmm1, dword ptr [esi]
00962573 movaps xmm0, xmm1
00962576 mov dword ptr [esi + 4], ecx
00962579 movss xmm2, dword ptr [esi + 4]
0096257e mulss xmm0, xmm1
00962582 movss dword ptr [ebp + 8], xmm1
00962587 movaps xmm1, xmm2
0096258a mulss xmm1, xmm2
0096258e movss dword ptr [ebp - 4], xmm2
00962593 addss xmm0, xmm1
00962597 call 0x4228c0
0096259c comiss xmm0, dword ptr [0xb6a18c]
009625a3 mov eax, esi
009625a5 jbe 0x9625ce
009625a7 movss xmm1, dword ptr [0xb6a614]
009625af divss xmm1, xmm0
009625b3 movss xmm0, dword ptr [ebp + 8]
009625b8 mulss xmm0, xmm1
009625bc movss dword ptr [esi], xmm0
009625c0 movss xmm0, dword ptr [ebp - 4]
009625c5 mulss xmm0, xmm1
009625c9 movss dword ptr [esi + 4], xmm0
009625ce pop esi
009625cf mov esp, ebp
009625d1 pop ebp
009625d2 ret 4
009625d5 int3 
009625d6 int3 
009625d7 int3 
009625d8 int3 
009625d9 int3 
009625da int3 
009625db int3 
009625dc int3 
009625dd int3 
009625de int3 
009625df int3 
009625e0 movss xmm0, dword ptr [ecx + 4]
009625e5 movss xmm1, dword ptr [ecx]
009625e9 mulss xmm0, dword ptr [edx + 4]
009625ee mulss xmm1, dword ptr [edx]
009625f2 addss xmm0, xmm1
009625f6 ret 
009625f7 int3 
009625f8 int3 
009625f9 int3 
009625fa int3 
009625fb int3 
009625fc int3 
009625fd int3 
009625fe int3 
009625ff int3 
