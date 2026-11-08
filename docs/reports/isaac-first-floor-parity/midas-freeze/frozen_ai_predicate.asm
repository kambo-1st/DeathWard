0069b0b0 mov edx, dword ptr [ecx + 0x160]
0069b0b6 mov eax, dword ptr [ecx + 0x164]
0069b0bc and edx, 0x20
0069b0bf and eax, 0x2000000
0069b0c4 or edx, eax
0069b0c6 jne 0x69b0d3
0069b0c8 cmp dword ptr [ecx + 0x348], edx
0069b0ce jg 0x69b0d3
0069b0d0 xor al, al
0069b0d2 ret 
0069b0d3 mov al, 1
0069b0d5 ret 
