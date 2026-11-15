00718ae0 mov eax, dword ptr [ecx + 4]
00718ae3 cmp eax, 4
00718ae6 je 0x718af0
00718ae8 cmp eax, 5
00718aeb je 0x718af0
00718aed xor al, al
00718aef ret
00718af0 mov al, 1
00718af2 ret
