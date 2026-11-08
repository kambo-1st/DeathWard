00415960 mov eax, dword ptr [esi + 0x74]
00415963 movaps xmm2, xmm3
00415966 mov ebx, dword ptr [eax + edi*4]
00415969 xor eax, eax
0041596b mov ecx, dword ptr [ebx + 0x164]
00415971 addss xmm2, dword ptr [ebx + 0x2c8]
00415979 and ecx, 0x4000
0041597f or eax, ecx
00415981 jne 0x4159bb
00415983 mov eax, dword ptr [ebp + 0xc]
00415986 mulss xmm2, xmm2
0041598a movss xmm1, dword ptr [eax]
0041598e movss xmm0, dword ptr [eax + 4]
00415993 subss xmm0, dword ptr [ebx + 0x298]
0041599b subss xmm1, dword ptr [ebx + 0x294]
004159a3 mulss xmm0, xmm0
004159a7 mulss xmm1, xmm1
004159ab addss xmm0, xmm1
004159af comiss xmm2, xmm0
004159b2 jbe 0x4159bb
004159b4 mov eax, dword ptr [esi + 0x74]
004159b7 mov dword ptr [eax + edx*4], ebx
004159ba inc edx
004159bb inc edi
004159bc cmp edi, dword ptr [esi + 0x7c]
004159bf jb 0x415960
