006d0380 cmp dword ptr [ecx + 0x1bb80], 0
006d0387 mov edx, dword ptr [0xbfd680]
006d038d je 0x6d039d
006d038f mov eax, dword ptr [edx + 0x20a9ac]
006d0395 cmp eax, dword ptr [edx + 0x20a9b0]
006d039b je 0x6d03f8
006d039d cmp dword ptr [ecx + 0x1a30d8], 0
006d03a4 jg 0x6d03f8
006d03a6 cmp dword ptr [ecx + 0x1d154], 0
006d03ad jne 0x6d03f8
006d03af cmp dword ptr [ecx + 0x3d808], 0
006d03b6 jne 0x6d03f8
006d03b8 cmp dword ptr [ecx + 0x1ba0c], 0
006d03bf jne 0x6d03f8
006d03c1 cmp dword ptr [ecx + 0x1b6c0], 0
006d03c8 jne 0x6d03f8
006d03ca mov eax, dword ptr [ecx + 0x1bcc0]
006d03d0 test eax, eax
006d03d2 je 0x6d03d9
006d03d4 cmp eax, 2
006d03d7 je 0x6d03f8
006d03d9 cmp dword ptr [ecx + 0x10203c], 0
006d03e0 jne 0x6d03f8
006d03e2 cmp dword ptr [edx + 8], 2
006d03e6 jne 0x6d03f8
006d03e8 add ecx, 0x1c33fc
006d03ee call 0x7f23c0
006d03f3 test al, al
006d03f5 jne 0x6d03f8
006d03f7 ret 
006d03f8 mov al, 1
006d03fa ret 
