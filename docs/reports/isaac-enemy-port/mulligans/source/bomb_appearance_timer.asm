0067afe6 mov ecx, dword ptr [edi + 0x354]
0067afec movss xmm1, dword ptr [0xb6a4c4]
0067aff4 test ecx, ecx
0067aff6 je 0x67b053
0067aff8 movss xmm0, dword ptr [edi + 0x2c4]
0067b000 mov eax, dword ptr [edi + 0x360]
0067b006 mulss xmm0, xmm1
0067b00a movss dword ptr [edi + 0x2c4], xmm0
0067b012 test eax, eax
0067b014 jle 0x67b01d
0067b016 inc eax
0067b017 mov dword ptr [edi + 0x360], eax
0067b01d cmp dword ptr [edi + 0x70], 0
0067b021 je 0x67b02c
0067b023 cmp byte ptr [edi + 0x80], 0
0067b02a jne 0x67b053
0067b02c cmp ecx, 1
0067b02f jne 0x67b053
0067b031 cmp dword ptr [edi + 0x314], 0
0067b038 mov dword ptr [edi + 0x354], 2
0067b042 jne 0x67b053
0067b044 mov eax, dword ptr [edi]
0067b046 mov ecx, edi
0067b048 call dword ptr [eax + 0x28]
0067b04b movss xmm5, dword ptr [0xb6ae7c]
