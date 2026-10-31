0068678d mov eax, dword ptr [edi + 0x214]
00686793 mov ecx, edx
00686795 mov dword ptr [esp + 0x14], esi
00686799 test eax, eax
0068679b jle 0x6867c7
0068679d dec eax
0068679e mov dword ptr [esp + 0x14], esi
006867a2 mov dword ptr [edi + 0x214], eax
006867a8 test eax, eax
006867aa jg 0x6867c7
006867ac and ecx, 0xffffffbf
006867af mov dword ptr [edi + 0x164], esi
006867b5 mov dword ptr [edi + 0x160], ecx
006867bb mov dword ptr [edi + 0x278], 0x40000000
006867c5 jmp 0x6867cb
006867c7 mov esi, dword ptr [esp + 0x14]
