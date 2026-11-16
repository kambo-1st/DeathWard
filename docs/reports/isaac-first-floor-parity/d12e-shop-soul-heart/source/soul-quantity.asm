006bf9e7 xor eax, eax
006bf9e9 mov ecx, edi
006bf9eb cmp dword ptr [esi + 0x30], 3
006bf9ef sete al
006bf9f2 inc eax
006bf9f3 push eax
006bf9f4 mov dword ptr [ebp - 0x80], eax
006bf9f7 call 0x725130
