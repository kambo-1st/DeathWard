006af030 mov eax, dword ptr [0xbfd65c]
006af035 mov eax, dword ptr [eax + 0x243624]
006af03b cmp eax, 1
006af03e je 0x6af048
006af040 cmp eax, 3
006af043 je 0x6af048
006af045 xor eax, eax
006af047 ret 
006af048 mov eax, 1
006af04d ret 
