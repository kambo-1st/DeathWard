0094557f movss xmm2, dword ptr [esi + 0x2b8]
00945587 movss xmm3, dword ptr [esi + 0x2bc]
0094558f movss xmm4, dword ptr [ebp + 0x1c]
00945594 mulss xmm2, xmm4
00945598 mulss xmm3, xmm4
0094559c addss xmm2, dword ptr [esi + 0x294]
009455a4 addss xmm3, dword ptr [esi + 0x298]
009455ac movss dword ptr [esi + 0x294], xmm2
009455b4 movss dword ptr [esi + 0x298], xmm3
009455bc mov eax, dword ptr [ebx + 4]
009455bf test eax, eax
009455c1 je 0x94561b
009455c3 test edi, edi
009455c5 je 0x9455cb
009455c7 cmp edi, eax
009455c9 jne 0x94561b
009455cb cmp dword ptr [eax + 0x28], 1
009455cf jne 0x9455eb
009455d1 movss xmm0, dword ptr [eax + 0x1594]
009455d9 movss xmm1, dword ptr [eax + 0x1598]
009455e1 addss xmm0, xmm0
009455e5 addss xmm1, xmm1
009455e9 jmp 0x9455fb
009455eb movss xmm0, dword ptr [eax + 0x2b8]
009455f3 movss xmm1, dword ptr [eax + 0x2bc]
009455fb mulss xmm1, xmm4
009455ff mulss xmm0, xmm4
00945603 subss xmm3, xmm1
00945607 subss xmm2, xmm0
0094560b movss dword ptr [esi + 0x298], xmm3
00945613 movss dword ptr [esi + 0x294], xmm2
