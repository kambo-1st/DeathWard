006860e7 movss xmm1, dword ptr [edi + 0x2fc]
006860ef mov eax, edx
006860f1 movss xmm2, dword ptr [edi + 0x2f4]
006860f9 and eax, 0x20
006860fc or eax, 0
006860ff movss dword ptr [edi + 0x2f8], xmm1
00686107 movaps xmm0, xmm2
0068610a addss xmm0, xmm1
0068610e movss dword ptr [edi + 0x2fc], xmm0
00686116 jne 0x686120
00686118 cmp dword ptr [edi + 0x348], eax
0068611e jle 0x686129
00686120 cmp byte ptr [edi + 0x16b], 0
00686127 je 0x68618c
00686129 mov ecx, esi
0068612b mov dword ptr [esp + 0x10], edx
0068612f and ecx, 1
00686132 xor eax, eax
00686134 or eax, ecx
00686136 jne 0x68618c
00686138 movss xmm0, dword ptr [edi + 0x140]
00686140 movss dword ptr [esp + 0x1c], xmm0
00686146 mulss xmm0, xmm2
0068614a movss dword ptr [edi + 0x140], xmm0
00686152 cmp byte ptr [edi + 0x145], 0
00686159 je 0x68617e
0068615b lea ecx, [edi + 0x6c]
0068615e call 0x403d60
00686163 lea ecx, [edi + 0x8c]
00686169 call 0x403d60
0068616e mov eax, dword ptr [edi + 0x160]
00686174 mov esi, dword ptr [edi + 0x164]
0068617a mov dword ptr [esp + 0x10], eax
0068617e movss xmm0, dword ptr [esp + 0x1c]
00686184 movss dword ptr [edi + 0x140], xmm0
