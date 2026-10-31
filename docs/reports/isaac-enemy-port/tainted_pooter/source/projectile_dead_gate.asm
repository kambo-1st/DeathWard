00631c84 cmp byte ptr [edi + 0x16b], 0
00631c8b je 0x63448c
00631c91 push 0
00631c93 push 0x20
00631c95 mov ecx, edi
00631c97 call 0x4122f0
00631c9c test al, al
00631c9e jne 0x62f7cd
00631ca4 mov eax, dword ptr [edi + 0x388]
00631caa and eax, 2
00631cad mov dword ptr [ebp - 0x330], 0
00631cb7 or eax, 0
00631cba je 0x63213e
00631cc0 call 0x6c3d90
00631cc5 mov ecx, dword ptr [0xbfd65c]
00631ccb lea esi, [edi + 0x294]
00631cd1 push eax
00631cd2 push 0
