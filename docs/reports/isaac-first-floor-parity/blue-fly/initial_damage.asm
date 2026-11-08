005f0ced mov eax, dword ptr [edi + 0x2c]
005f0cf0 movss xmm2, dword ptr [0xb6a6f0]
005f0cf8 cmp eax, 0x2b
005f0cfb jne 0x5f0d6a
005f0cfd mov eax, dword ptr [edi + 0x360]
005f0d03 movss xmm0, dword ptr [eax + 0x14c0]
005f0d0b mov eax, dword ptr [ebp - 0xfc]
005f0d11 addss xmm0, xmm0
005f0d15 dec eax
005f0d16 movss dword ptr [edi + 0x2e0], xmm0
