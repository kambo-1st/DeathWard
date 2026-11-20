0063e6b9 movzx ecx, word ptr [edi + 0x374]
0063e6c0 test cx, cx
0063e6c3 je 0x63e6d8
0063e6c5 inc word ptr [edi + 0x376]
0063e6cc lea eax, [ecx - 1]
0063e6cf mov word ptr [edi + 0x374], ax
0063e6d6 jmp 0x63e6e1
0063e6d8 xor eax, eax
0063e6da mov word ptr [edi + 0x376], ax
