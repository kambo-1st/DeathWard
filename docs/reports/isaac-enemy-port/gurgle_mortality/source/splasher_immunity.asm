004f8f99 cmp dword ptr [edi + 0x28], 0xee
004f8fa0 xorps xmm1, xmm1
004f8fa3 jne 0x4f9008
004f8fa5 movss xmm0, dword ptr [edi + 0x14]
004f8faa comiss xmm0, xmm1
004f8fad jbe 0x4f9008
004f8faf mov eax, dword ptr [edi + 8]
004f8fb2 cmp eax, dword ptr [edi + 0xc]
004f8fb5 je 0x4f9008
004f8fb7 nop word ptr [eax + eax]
004f8fc0 mov ecx, dword ptr [eax + 0xc]
004f8fc3 mov edx, dword ptr [eax + 8]
004f8fc6 mov dword ptr [ebp - 0x11c], ecx
004f8fcc mov ecx, edx
004f8fce and ecx, 4
004f8fd1 or ecx, 0
004f8fd4 je 0x4f9000
004f8fd6 mov ecx, dword ptr [eax + 0x30]
004f8fd9 shr ecx, 1
004f8fdb test cl, 1
004f8fde jne 0x4f9000
004f8fe0 cmp dword ptr [eax + 0x10], 1
004f8fe4 je 0x4f9000
004f8fe6 mov ecx, dword ptr [eax + 0x18]
004f8fe9 cmp ecx, 1
004f8fec je 0x4f9000
004f8fee cmp ecx, 3
004f8ff1 je 0x4f9000
004f8ff3 and edx, 0x1000
004f8ff9 or edx, 0
004f8ffc jne 0x4f9000
004f8ffe mov dword ptr [eax], edx
004f9000 add eax, 0x38
004f9003 cmp eax, dword ptr [edi + 0xc]
004f9006 jne 0x4f8fc0
