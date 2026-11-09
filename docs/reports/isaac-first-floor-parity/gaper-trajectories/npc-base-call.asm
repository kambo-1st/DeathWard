0069b6c9 mov ecx, edi
0069b6cb je 0x69b6d4
0069b6cd call 0x6860a0
0069b6d2 jmp 0x69b6f7
0069b6d4 xor dword ptr [edi + 0x160], 0
0069b6db xor edx, 1
0069b6de mov dword ptr [edi + 0x164], edx
0069b6e4 call 0x6860a0
0069b6e9 xor dword ptr [edi + 0x160], 0
0069b6f0 xor dword ptr [edi + 0x164], 1
