005ef580 push ebp
005ef581 mov ebp, esp
005ef583 mov eax, dword ptr [ecx + 0x10]
005ef586 mov ecx, dword ptr [ecx + 0x14]
005ef589 push esi
005ef58a cmp eax, ecx
005ef58c je 0x5ef5a8
005ef58e mov esi, dword ptr [ebp + 8]
005ef591 mov edx, dword ptr [eax]
005ef593 cmp dword ptr [edx + 0x2c], 0
005ef597 jne 0x5ef5a1
005ef599 cmp dword ptr [edx + 0x130c], esi
005ef59f je 0x5ef5aa
005ef5a1 add eax, 4
005ef5a4 cmp eax, ecx
005ef5a6 jne 0x5ef591
005ef5a8 xor edx, edx
005ef5aa test edx, edx
005ef5ac pop esi
005ef5ad setne al
005ef5b0 pop ebp
005ef5b1 ret 4
