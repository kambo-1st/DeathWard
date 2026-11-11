006bb8a1 cmp byte ptr [ebp - 0x8e], 0
006bb8a8 je 0x6bb8c5
006bb8aa cmp dword ptr [edi + 0x70], 0
006bb8ae je 0x6bb8b9
006bb8b0 cmp byte ptr [edi + 0x80], 0
006bb8b7 jne 0x6bb8c5
006bb8b9 mov eax, dword ptr [edi]
006bb8bb mov ecx, edi
006bb8bd call dword ptr [eax + 0x28]
006bb8c0 jmp 0x6bba3b
