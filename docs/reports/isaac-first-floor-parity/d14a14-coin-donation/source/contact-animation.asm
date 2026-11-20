0063eff8 mov ecx, 0xb468f8
0063effd cmp eax, 8
0063f000 je 0x63f007
0063f002 cmp eax, 0xb
0063f005 jne 0x63f027
0063f007 movzx edx, word ptr [edi + 0x376]
0063f00e cmp edx, 0x78
0063f011 jbe 0x63f01a
0063f013 mov ecx, 0xb46904
0063f018 jmp 0x63f027
0063f01a cmp edx, 0x3c
0063f01d mov eax, 0xb46948
0063f022 cmovbe eax, ecx
0063f025 mov ecx, eax
0063f027 push 1
0063f029 push ecx
0063f02a lea ecx, [edi + 0x3c]
0063f02d call 0x405bb0
0063f032 test al, al
0063f034 je 0x63f048
0063f036 lea ecx, [edi + 0x8c]
0063f03c call 0x405330
0063f041 mov byte ptr [edi + 0xa0], 1
