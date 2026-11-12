006b1490 xor eax, eax
006b1492 cmp dword ptr [ecx + eax*4], 0
006b1496 jne 0x6b14a0
006b1498 add eax, 1
006b149b je 0x6b1492
006b149d xor al, al
006b149f ret
006b14a0 mov al, 1
006b14a2 ret
