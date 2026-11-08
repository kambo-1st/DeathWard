006bb460 mov ecx, dword ptr [edi + 0x164]
006bb466 xor eax, eax
006bb468 and ecx, 0x4000000
006bb46e or eax, ecx
006bb470 jne 0x6bb48a
006bb472 movss xmm0, dword ptr [edi + 0x2c4]
006bb47a mulss xmm0, dword ptr [0xb6a5f4]
006bb482 movss dword ptr [edi + 0x2c4], xmm0
