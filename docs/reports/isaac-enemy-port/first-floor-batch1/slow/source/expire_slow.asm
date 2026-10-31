006867cb cmp dword ptr [edi + 0x218], 0
006867d2 mov eax, esi
006867d4 mov edx, ecx
006867d6 mov dword ptr [esp + 0x10], eax
006867da jle 0x68680f
006867dc mov eax, dword ptr [edi + 0x218]
006867e2 dec eax
006867e3 mov dword ptr [esp + 0x10], esi
006867e7 mov dword ptr [edi + 0x218], eax
006867ed test eax, eax
006867ef jg 0x68680b
006867f1 mov eax, esi
006867f3 and edx, 0xffffff7f
006867f9 mov dword ptr [esp + 0x10], eax
006867fd mov dword ptr [edi + 0x160], edx
00686803 mov dword ptr [edi + 0x164], eax
00686809 jmp 0x68680f
0068680b mov eax, dword ptr [esp + 0x10]
