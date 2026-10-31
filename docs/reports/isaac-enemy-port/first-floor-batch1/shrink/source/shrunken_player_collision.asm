006a4df2 push 0
006a4df4 push 0x1000000
006a4df9 mov ecx, edi
006a4dfb call 0x4122f0
006a4e00 test al, al
006a4e02 je 0x6a4e1e
006a4e04 cmp dword ptr [ebp - 0xec], 1
006a4e0b jne 0x6a4e1e
006a4e0d mov eax, dword ptr [edi]
006a4e0f mov ecx, edi
006a4e11 mov eax, dword ptr [eax + 0x48]
006a4e14 call eax
006a4e16 test al, al
006a4e18 je 0x6a4d73
