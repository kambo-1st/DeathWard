00686882 cmp dword ptr [edi + 0x220], 0
00686889 mov eax, edx
0068688b mov esi, ecx
0068688d mov dword ptr [esp + 0x10], eax
00686891 jle 0x6868c6
00686893 mov eax, dword ptr [edi + 0x220]
00686899 dec eax
0068689a mov dword ptr [esp + 0x10], edx
0068689e mov dword ptr [edi + 0x220], eax
006868a4 test eax, eax
006868a6 jg 0x6868c2
006868a8 mov eax, edx
006868aa and esi, 0xfffffdff
006868b0 mov dword ptr [esp + 0x10], eax
006868b4 mov dword ptr [edi + 0x160], esi
006868ba mov dword ptr [edi + 0x164], eax
006868c0 jmp 0x6868c6
006868c2 mov eax, dword ptr [esp + 0x10]
006868c6 mov edx, eax
006868c8 mov ecx, esi
006868ca mov eax, dword ptr [edi + 0x228]
006868d0 test eax, eax
006868d2 jle 0x6868f5
006868d4 mov edx, dword ptr [esp + 0x10]
006868d8 dec eax
006868d9 mov dword ptr [edi + 0x228], eax
006868df test eax, eax
006868e1 jg 0x6868f5
006868e3 and ecx, 0xfffff7ff
006868e9 mov dword ptr [edi + 0x164], edx
006868ef mov dword ptr [edi + 0x160], ecx
