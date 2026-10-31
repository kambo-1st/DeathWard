009628d0 push ebp
009628d1 mov ebp, esp
009628d3 push esi
009628d4 mov esi, ecx
009628d6 movss xmm1, dword ptr [esi + 4]
009628db movss xmm0, dword ptr [esi]
009628df mulss xmm0, xmm0
009628e3 mulss xmm1, xmm1
009628e7 addss xmm0, xmm1
009628eb call 0x4228c0
009628f0 comiss xmm0, dword ptr [0xb6a18c]
009628f7 mov eax, dword ptr [ebp + 8]
009628fa jbe 0x962924
009628fc movss xmm1, dword ptr [ebp + 0xc]
00962901 divss xmm1, xmm0
00962905 movss xmm0, dword ptr [esi]
00962909 mulss xmm0, xmm1
0096290d movss dword ptr [eax], xmm0
00962911 movss xmm0, dword ptr [esi + 4]
00962916 mulss xmm0, xmm1
0096291a pop esi
0096291b movss dword ptr [eax + 4], xmm0
00962920 pop ebp
00962921 ret 8
00962924 mov ecx, dword ptr [esi]
00962926 mov edx, dword ptr [esi + 4]
00962929 mov dword ptr [eax], ecx
0096292b mov dword ptr [eax + 4], edx
0096292e pop esi
0096292f pop ebp
00962930 ret 8
