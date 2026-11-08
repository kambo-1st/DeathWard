0075770e movss xmm0, dword ptr [eax]
00757712 movss xmm1, dword ptr [eax + 4]
00757717 movss dword ptr [esp + 0x14], xmm0
0075771d movss dword ptr [esp + 0xc], xmm1
00757723 test esi, esi
00757725 je 0x757747
00757727 cmp esi, edi
00757729 jne 0x757747
0075772b addss xmm0, dword ptr [edi + 0x1580]
00757733 addss xmm1, dword ptr [edi + 0x1584]
0075773b movss dword ptr [esp + 0x14], xmm0
00757741 movss dword ptr [esp + 0xc], xmm1
