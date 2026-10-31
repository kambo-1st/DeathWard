; Installed Repentance 1.7.9b; bounded evidence, names are interpretations.
004a64a2 cmp dword ptr [edi + 0x2c], 1
004a64a6 jne 0x4a64d4
004a64a8 mov eax, dword ptr [edi + 0x164]
004a64ae or dword ptr [edi + 0x160], 0x140011
004a64b8 mov dword ptr [edi + 0xab4], 0x10
004a64c2 mov byte ptr [edi + 0x308], 1
004a64c9 mov dword ptr [edi + 0x164], eax
004a64cf jmp 0x4a79e8
004a64d4 mov esi, dword ptr [edi + 0x32c]
004a64da mov dword ptr [ebp - 0x120], esi
004a64e0 test esi, esi
004a64e2 jne 0x4a65ac
004a64e8 push 0xc02fec
