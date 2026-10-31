0068827a cmp dword ptr [edi + 0x28], 1
0068827e lea ebx, [edi + 0x294]
00688284 mov eax, dword ptr [ebx]
00688286 mov ecx, edi
00688288 mov dword ptr [edi + 0x29c], eax
0068828e mov eax, dword ptr [ebx + 4]
00688291 mov dword ptr [edi + 0x2a0], eax
00688297 movss xmm3, dword ptr [edi + 0x2c4]
0068829f movss xmm2, dword ptr [edi + 0x2bc]
006882a7 movaps xmm0, xmm3
006882aa mulss xmm0, dword ptr [edi + 0x2b8]
006882b2 push 1
006882b4 movss xmm1, dword ptr [edi + 0x2f4]
006882bc mulss xmm3, xmm2
006882c0 mov byte ptr [edi + 0x16d], 1
006882c7 mulss xmm0, xmm1
006882cb mulss xmm3, xmm1
006882cf mulss xmm0, dword ptr [0xb6a480]
006882d7 mulss xmm3, dword ptr [0xb6a480]
006882df addss xmm0, dword ptr [ebx]
006882e3 addss xmm3, dword ptr [ebx + 4]
006882e8 movss dword ptr [ebx], xmm0
006882ec movss dword ptr [ebx + 4], xmm3
