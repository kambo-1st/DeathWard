00405d10 cmp dword ptr [ecx + 0x54], 0
00405d14 jne 0x405d1a
00405d16 or eax, 0xffffffff
00405d19 ret 
00405d1a cvttss2si eax, dword ptr [ecx + 0x60]
00405d1f ret 
