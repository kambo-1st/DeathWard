0088b600 push ebp
0088b601 mov ebp, esp
0088b603 cmp byte ptr [ecx + 0x11], 0
0088b607 push esi
0088b608 jne 0x88b62a
0088b60a mov eax, dword ptr [ecx + 4]
0088b60d mov ecx, dword ptr [ecx + 8]
0088b610 cmp eax, ecx
0088b612 je 0x88b62a
0088b614 mov esi, dword ptr [ebp + 8]
0088b617 mov edx, dword ptr [eax]
0088b619 cmp dword ptr [edx], 0
0088b61c jne 0x88b623
0088b61e cmp dword ptr [edx + 4], esi
0088b621 je 0x88b631
0088b623 add eax, 0xc
0088b626 cmp eax, ecx
0088b628 jne 0x88b617
0088b62a xor al, al
0088b62c pop esi
0088b62d pop ebp
0088b62e ret 4
