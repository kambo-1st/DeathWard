006a4e1e push 0
006a4e20 push 0x20000000
006a4e25 mov ecx, edi
006a4e27 call 0x4122f0
006a4e2c mov ecx, dword ptr [ebp - 0xec]
006a4e32 test al, al
006a4e34 je 0x6a4e71
006a4e36 cmp ecx, 1
006a4e39 je 0x6a5c9a
006a4e3f cmp ecx, 3
006a4e42 je 0x6a5c9a
006a4e48 mov eax, dword ptr [esi + 0x28]
006a4e4b sub eax, 0xa
006a4e4e cmp eax, 0x3dd
006a4e53 ja 0x6a4e71
006a4e55 push 0
006a4e57 push 0x20000000
006a4e5c mov ecx, esi
006a4e5e call 0x4122f0
006a4e63 test al, al
006a4e65 jne 0x6a5c9a
006a4e6b mov ecx, dword ptr [ebp - 0xec]
