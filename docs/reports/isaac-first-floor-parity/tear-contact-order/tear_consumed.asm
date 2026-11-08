00650049 movss xmm0, dword ptr [esi + 0x2b8]
00650051 lea eax, [edi + 0x294]
00650057 movss xmm1, dword ptr [esi + 0x2bc]
0065005f mulss xmm0, dword ptr [0xb6a560]
00650067 or dword ptr [edi + 0x3c4], 8
0065006e mulss xmm1, dword ptr [0xb6a560]
00650076 mov byte ptr [edi + 0x16b], 1
0065007d addss xmm0, dword ptr [eax]
00650081 addss xmm1, dword ptr [eax + 4]
00650086 movss dword ptr [eax], xmm0
0065008a movss dword ptr [eax + 4], xmm1
