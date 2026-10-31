00500fdd test edx, edx
00500fdf jle 0x50106c
00500fe5 cvttss2si eax, dword ptr [edi + 0x2fc]
00500fed cvttss2si ecx, dword ptr [edi + 0x2f8]
00500ff5 sub ecx, eax
00500ff7 add ecx, edx
00500ff9 cmp dword ptr [edi + 0xe6c], -1
00501000 mov dword ptr [edi + 0xaf0], ecx
