006b62bf cmp dword ptr [edi], 0
006b62c2 jne 0x6b57da
006b62c8 mov ecx, dword ptr [0xbfd65c]
006b62ce mov al, dl
006b62d0 xor al, 1
006b62d2 movzx eax, al
006b62d5 push eax
006b62d6 lea ecx, [ecx + 0x1a5cc]
006b62dc call 0x701880
006b62e1 mov dword ptr [edi], eax
006b62e3 test eax, eax
006b62e5 jne 0x6b57da
006b62eb lea ecx, [ebp - 0x6c]
006b62ee mov dword ptr [esi], 0x12c
006b62f4 call 0x7a7e20
006b62f9 push 1
006b62fb push 0xa
006b62fd push 0xa
006b62ff mov esi, eax
006b6301 push 0x19
006b6303 push esi
006b6304 call 0x701da0
006b6309 movq xmm0, qword ptr [0xa08c44]
