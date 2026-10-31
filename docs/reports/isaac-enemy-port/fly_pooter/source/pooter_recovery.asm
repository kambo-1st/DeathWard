004f5a1d mov eax, dword ptr [esi + 0xab4]
004f5a23 cmp eax, 4
004f5a26 ja 0x4f5a39
004f5a28 push 0
004f5a2a push 0xb405b4
004f5a2f lea ecx, [esi + 0x3c]
004f5a32 call 0x4054f0
004f5a37 jmp 0x4f5ab2
004f5a39 cmp eax, 8
004f5a3c jne 0x4f5ab2
004f5a3e push 0xa081d4
004f5a43 lea ecx, [esi + 0x3c]
004f5a46 call 0x4056c0
004f5a4b test al, al
004f5a4d je 0x4f5ab2
004f5a4f mov dword ptr [esi + 0xab4], 4
004f5a59 jmp 0x4f5ab2
