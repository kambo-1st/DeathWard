0069b5a0 mov edx, dword ptr [edi + 0x274]
0069b5a6 movss xmm1, dword ptr [0xb6a4c4]
0069b5ae test edx, edx
0069b5b0 jne 0x69b5d5
0069b5b2 mov ecx, dword ptr [edi + 0x164]
0069b5b8 xor eax, eax
0069b5ba and ecx, 0x2000000
0069b5c0 or eax, ecx
0069b5c2 jne 0x69b5d5
0069b5c4 mov al, byte ptr [edi + 0x16b]
0069b5ca mov byte ptr [ebp - 0x299], al
0069b5d0 jmp 0x69b756
