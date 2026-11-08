0095a261 mov edi, dword ptr [ebp - 0xcc]
0095a267 mov eax, dword ptr [esi + 4]
0095a26a test eax, eax
0095a26c je 0x95a288
0095a26e movss xmm0, dword ptr [eax + 0x294]
0095a276 movss dword ptr [ebp - 0xec], xmm0
0095a27e movss xmm0, dword ptr [eax + 0x298]
0095a286 jmp 0x95a2a0
0095a288 movss xmm0, dword ptr [0xc02fec]
0095a290 movss dword ptr [ebp - 0xec], xmm0
0095a298 movss xmm0, dword ptr [0xc02ff0]
0095a2a0 movss dword ptr [ebp - 0xe8], xmm0
