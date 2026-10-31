0064dff6 cmp byte ptr [ebp - 0xb1], 0
0064dffd jne 0x64e3a7
0064e003 cmp eax, 0x336
0064e008 jne 0x64e3a7
0064e00e cmp dword ptr [esi + 0xab4], 0x10
0064e015 jne 0x64e3a7
0064e01b mov eax, dword ptr [esi + 0x344]
0064e021 lea ecx, [ebp - 0xec]
0064e027 add eax, dword ptr [edi + 0x344]
0064e02d movq xmm0, qword ptr [0xa08c44]
0064e035 mov dword ptr [ebp - 0xec], eax
0064e03b mov eax, dword ptr [0xa08c4c]
0064e040 push 5
0064e042 movq qword ptr [ebp - 0xe8], xmm0
0064e04a mov dword ptr [ebp - 0xe0], eax
0064e050 call 0x7a7d50
0064e055 test eax, eax
0064e057 jne 0x64e3a7
0064e05d movss xmm0, dword ptr [edi + 0x294]
0064e065 lea eax, [ebp - 0xf4]
0064e06b subss xmm0, dword ptr [esi + 0x294]
0064e073 push eax
0064e074 lea ecx, [ebp - 0xd4]
0064e07a movss dword ptr [ebp - 0xd4], xmm0
0064e082 movss xmm0, dword ptr [edi + 0x298]
0064e08a subss xmm0, dword ptr [esi + 0x298]
0064e092 movss dword ptr [ebp - 0xd0], xmm0
0064e09a call 0x962560
0064e09f movss xmm2, dword ptr [edi + 0x2b8]
0064e0a7 movss xmm3, dword ptr [ebp - 0xf0]
0064e0af movaps xmm0, xmm2
0064e0b2 movss xmm4, dword ptr [ebp - 0xf4]
0064e0ba movaps xmm1, xmm3
0064e0bd mulss xmm1, dword ptr [edi + 0x2bc]
0064e0c5 mulss xmm0, xmm4
0064e0c9 addss xmm1, xmm0
0064e0cd xorps xmm0, xmm0
0064e0d0 comiss xmm0, xmm1
0064e0d3 jbe 0x64dde9
0064e0d9 addss xmm1, xmm1
0064e0dd movaps xmm0, xmm1
0064e0e0 mulss xmm1, xmm3
0064e0e4 mulss xmm0, xmm4
0064e0e8 subss xmm2, xmm0
0064e0ec movss xmm0, dword ptr [edi + 0x2bc]
0064e0f4 subss xmm0, xmm1
0064e0f8 movss dword ptr [edi + 0x2b8], xmm2
0064e100 movss dword ptr [edi + 0x2bc], xmm0
0064e108 jmp 0x64dde9
