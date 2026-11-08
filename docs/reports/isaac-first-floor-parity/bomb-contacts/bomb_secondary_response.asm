0067f025 cmp eax, 9
0067f028 je 0x67e896
0067f02e cmp eax, 2
0067f031 jne 0x67f04c
0067f033 cmp dword ptr [esi + 0x34], 1
0067f037 je 0x67f055
0067f039 cmp byte ptr [edi + 0x398], 0
0067f040 je 0x67f055
0067f042 mov al, 1
0067f044 pop edi
0067f045 pop esi
0067f046 mov esp, ebp
0067f048 pop ebp
0067f049 ret 8
0067f04c cmp eax, 8
0067f04f je 0x67e896
0067f055 test cl, cl
0067f057 je 0x67f0d0
0067f059 cmp eax, 4
0067f05c jne 0x67f06b
0067f05e mov ecx, esi
0067f060 call 0x67ab80
0067f065 test al, al
0067f067 jne 0x67f0d0
0067f069 jmp 0x67f070
0067f06b cmp eax, 0x3e
0067f06e je 0x67f0d0
0067f070 movss xmm1, dword ptr [esi + 0x2b8]
0067f078 movss xmm2, dword ptr [esi + 0x2bc]
0067f080 mulss xmm1, dword ptr [0xb6a350]
0067f088 mulss xmm2, dword ptr [0xb6a350]
0067f090 movss dword ptr [esi + 0x2b8], xmm1
0067f098 movss dword ptr [esi + 0x2bc], xmm2
0067f0a0 movss xmm0, dword ptr [edi + 0x2b8]
0067f0a8 mulss xmm0, dword ptr [0xb6a480]
0067f0b0 movss dword ptr [edi + 0x2b8], xmm0
0067f0b8 movss xmm0, dword ptr [edi + 0x2bc]
0067f0c0 mulss xmm0, dword ptr [0xb6a480]
0067f0c8 movss dword ptr [edi + 0x2bc], xmm0
0067f0d0 pop edi
0067f0d1 xor al, al
0067f0d3 pop esi
0067f0d4 mov esp, ebp
0067f0d6 pop ebp
