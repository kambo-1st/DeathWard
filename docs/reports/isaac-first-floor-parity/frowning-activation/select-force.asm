004f7e45 mov eax, dword ptr [edi + 0x28]
004f7e48 mov dword ptr [edi + 0xb84], 0x3f19999a
004f7e52 cmp eax, 0xd0
004f7e57 je 0x4f7eeb
004f7e5d cmp eax, 0x101
004f7e62 je 0x4f7eeb
004f7e68 cmp eax, 0x12e
004f7e6d jne 0x4f7e88
004f7e6f cmp dword ptr [edi + 0x2c], 0xa
004f7e73 jne 0x4f7f0c
004f7e79 mov dword ptr [edi + 0xb84], 0x3ef5c290
004f7e83 jmp 0x4f7f0c
004f7e88 cmp eax, 0xfc
004f7e8d jne 0x4f7e9b
004f7e8f mov dword ptr [edi + 0xb84], 0x3f666667
004f7e99 jmp 0x4f7f0c
004f7e9b mov edx, dword ptr [edi + 0x2c]
004f7e9e cmp edx, 1
004f7ea1 je 0x4f7edf
004f7ea3 cmp eax, 0x11c
004f7ea8 je 0x4f7edf
004f7eaa lea ecx, [edi + 0x3c]
004f7ead cmp edx, 2
004f7eb0 jne 0x4f7eca
004f7eb2 push 0
004f7eb4 push 0xb41e78
004f7eb9 mov dword ptr [edi + 0xb84], 0x3f0c3c9f
004f7ec3 call 0x405a00
004f7ec8 jmp 0x4f7f0c
004f7eca call 0x405d10
004f7ecf test eax, eax
004f7ed1 jle 0x4f7f0c
004f7ed3 mov dword ptr [edi + 0xb84], 0x3f3851ec
004f7edd jmp 0x4f7f0c
004f7edf mov dword ptr [edi + 0xb84], 0x3efef9db
004f7ee9 jmp 0x4f7f0c
004f7eeb mov dword ptr [edi + 0xb84], 0x3e99999a
004f7ef5 cmp eax, 0xd0
004f7efa jne 0x4f7f0c
004f7efc cmp dword ptr [edi + 0x2c], 2
004f7f00 jne 0x4f7f0c
004f7f02 mov dword ptr [edi + 0xb84], 0x3ea8f5c3
