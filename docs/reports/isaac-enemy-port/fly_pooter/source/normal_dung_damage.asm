006e646a cmp dword ptr [edi + 0xc], 0x3e8
006e6471 je 0x6e6454
006e6473 call 0x6c3d90
006e6478 xor edx, edx
006e647a mov ebx, 3
006e647f div ebx
006e6481 mov eax, dword ptr [ebp + 8]
006e6484 test edx, edx
006e6486 lea esi, [eax + 1]
006e6489 cmovne esi, eax
006e648c cmp dword ptr [edi + 8], 0
006e6490 jne 0x6e64a0
006e6492 call 0x6c3d90
006e6497 xor edx, edx
006e6499 div ebx
006e649b test edx, edx
006e649d jne 0x6e64a0
006e649f inc esi
006e64a0 mov eax, dword ptr [edi + 8]
006e64a3 cmp eax, 3
006e64a6 jne 0x6e64bb
006e64a8 call 0x6c3d90
006e64ad xor edx, edx
006e64af mov ecx, 0x4b
006e64b4 div ecx
006e64b6 lea ebx, [edx + 0x32]
006e64b9 jmp 0x6e64d5
006e64bb cmp eax, 6
006e64be jne 0x6e64c5
006e64c0 lea ebx, [eax + 0x77]
006e64c3 jmp 0x6e64d5
006e64c5 cmp eax, 9
006e64c8 mov ebx, 0xfa
006e64cd mov ecx, 0x14
006e64d2 cmove ebx, ecx
006e64d5 imul ebx, esi
