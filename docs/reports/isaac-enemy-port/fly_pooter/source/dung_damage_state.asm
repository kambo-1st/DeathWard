006e6596 mov ecx, dword ptr [esp + 0x10]
006e659a add ecx, ebx
006e659c movss dword ptr [esp + 0x20], xmm0
006e65a2 mov dword ptr [edi + 0xc], ecx
006e65a5 cmp ecx, 0x3e8
006e65ab jle 0x6e65bb
006e65ad mov dword ptr [edi + 0xc], 0x3e8
006e65b4 mov eax, 4
006e65b9 jmp 0x6e65e7
006e65bb jne 0x6e65c4
006e65bd mov eax, 4
006e65c2 jmp 0x6e65e7
006e65c4 mov eax, 0x10624dd3
006e65c9 imul ecx
006e65cb mov ecx, 3
006e65d0 sar edx, 4
006e65d3 mov eax, edx
006e65d5 shr eax, 0x1f
006e65d8 add eax, edx
006e65da cmp eax, 3
006e65dd cmovl ecx, eax
006e65e0 xor eax, eax
006e65e2 test ecx, ecx
006e65e4 cmovg eax, ecx
006e65e7 inc eax
