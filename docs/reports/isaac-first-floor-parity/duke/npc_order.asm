0069b66e mov al, byte ptr [edi + 0x16b]
0069b674 mov byte ptr [ebp - 0x269], al
0069b67a call 0x6adb50
0069b67f mov ecx, edi
0069b681 call 0x6adfd0
0069b686 test byte ptr [edi + 0xe68], 1
0069b68d je 0x69b6aa
0069b68f mov ecx, edi
0069b691 mov dword ptr [edi + 0xac4], 1
0069b69b call 0x699730
0069b6a0 mov dword ptr [edi + 0xac4], 0
0069b6aa mov edx, dword ptr [edi + 0x164]
0069b6b0 xor eax, eax
0069b6b2 movss xmm0, dword ptr [edi + 0x2d8]
0069b6ba mov ecx, edx
0069b6bc and ecx, 1
0069b6bf movss dword ptr [ebp - 0x270], xmm0
0069b6c7 or eax, ecx
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
