00723f40 push ecx
00723f41 push ecx
00723f42 mov ecx, dword ptr [0xbfd65c]
00723f48 mov ecx, dword ptr [ecx + 0x18190]
00723f4e call 0x7a8ef0
00723f53 mov eax, dword ptr [0xbfd65c]
00723f58 mov eax, dword ptr [eax + 0x18190]
00723f5e cmp dword ptr [eax + 0x7120], 0
00723f65 jle 0x723f6f
00723f67 mulss xmm0, dword ptr [0xb6a53c]
00723f6f ret 
