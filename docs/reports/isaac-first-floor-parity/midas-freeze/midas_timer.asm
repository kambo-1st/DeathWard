006869dc mov eax, dword ptr [edi + 0x224]
006869e2 mov esi, edx
006869e4 mov dword ptr [esp + 0x14], ecx
006869e8 test eax, eax
006869ea jle 0x686a0f
006869ec dec eax
006869ed mov dword ptr [esp + 0x14], ecx
006869f1 mov dword ptr [edi + 0x224], eax
006869f7 test eax, eax
006869f9 jg 0x686a0f
006869fb and ecx, 0xfffffbff
00686a01 mov dword ptr [edi + 0x164], esi
00686a07 mov dword ptr [edi + 0x160], ecx
00686a0d jmp 0x686a13
00686a0f mov ecx, dword ptr [esp + 0x14]
