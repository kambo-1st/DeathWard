007c31a7 mov eax, dword ptr [ebx + 4]
007c31aa mov eax, dword ptr [eax + 0x44]
007c31ad shr eax, 7
007c31b0 test al, 1
007c31b2 jne 0x7c31e2
007c31b4 mov eax, dword ptr [esi + 0x243624]
007c31ba cmp eax, 2
007c31bd je 0x7c31c4
007c31bf cmp eax, 3
007c31c2 jne 0x7c31ca
007c31c4 cmp dword ptr [ebx + 8], 1
007c31c8 je 0x7c31d5
007c31ca lea ecx, [esi + 0x1ba40]
007c31d0 call 0x91aa70
007c31d5 mov ecx, ebx
007c31d7 call 0x7b8b10
007c31dc mov esi, dword ptr [0xbfd65c]
