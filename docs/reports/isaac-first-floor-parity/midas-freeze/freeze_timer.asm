00686757 mov eax, dword ptr [edi + 0x210]
0068675d mov edx, esi
0068675f mov dword ptr [esp + 0x14], ecx
00686763 test eax, eax
00686765 jle 0x686789
00686767 dec eax
00686768 mov dword ptr [esp + 0x14], ecx
0068676c mov dword ptr [edi + 0x210], eax
00686772 test eax, eax
00686774 jg 0x686789
00686776 and edx, 0xffffffdf
00686779 mov esi, ecx
0068677b mov dword ptr [edi + 0x160], edx
00686781 mov dword ptr [edi + 0x164], esi
00686787 jmp 0x68678d
00686789 mov esi, dword ptr [esp + 0x14]
