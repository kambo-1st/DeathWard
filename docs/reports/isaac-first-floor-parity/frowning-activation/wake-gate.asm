004f80ed cmp dword ptr [edi + 0x2c], 0
004f80f1 jne 0x4f812f
004f80f3 cmp byte ptr [edi + 0xa90], 0
004f80fa je 0x4f812f
004f80fc mov eax, dword ptr [edi + 0x28]
004f80ff cmp eax, 0xd0
004f8104 je 0x4f812f
004f8106 cmp eax, 0x101
004f810b je 0x4f812f
004f810d cmp eax, 0x12e
004f8112 je 0x4f812f
004f8114 lea ecx, [edi + 0x3c]
004f8117 call 0x405d10
004f811c test eax, eax
004f811e jg 0x4f812f
004f8120 push 1
004f8122 push 0xb41e78
004f8127 lea ecx, [edi + 0x3c]
004f812a call 0x405a00
