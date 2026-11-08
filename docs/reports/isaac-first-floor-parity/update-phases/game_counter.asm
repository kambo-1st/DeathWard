006ce598 mov esi, dword ptr [edi + 0x1a30dc]
006ce59e mov eax, 0x88888889
006ce5a3 inc dword ptr [edi + 0x1a30e0]
006ce5a9 inc esi
006ce5aa imul esi
006ce5ac mov dword ptr [edi + 0x1a30dc], esi
006ce5b2 add edx, esi
006ce5b4 sar edx, 4
006ce5b7 mov ecx, edx
006ce5b9 shr ecx, 0x1f
006ce5bc add ecx, edx
006ce5be mov eax, ecx
006ce5c0 shl eax, 4
006ce5c3 sub eax, ecx
006ce5c5 add eax, eax
006ce5c7 sub esi, eax
006ce5c9 jne 0x6ce5e8
006ce5cb cmp dword ptr [edi + 0x101904], 2
006ce5d2 je 0x6ce5e8
006ce5d4 mov dword ptr [edi + 0x101904], 1
006ce5de mov dword ptr [edi + 0x10190c], 2
