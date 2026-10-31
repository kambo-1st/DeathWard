004f651a mov eax, dword ptr [esi + 0x28]
004f651d cmp eax, 0xd
004f6520 je 0x4f6527
004f6522 cmp eax, 0xe
004f6525 jne 0x4f6553
004f6527 cmp dword ptr [esi + 0x34], 0x66
004f652b jne 0x4f6533
004f652d cmp dword ptr [esi + 0x30], 0
004f6531 jne 0x4f6553
004f6533 movss xmm0, dword ptr [0xc02fec]
004f653b movss dword ptr [esi + 0x28c], xmm0
004f6543 movss xmm0, dword ptr [0xc02ff0]
004f654b movss dword ptr [esi + 0x290], xmm0
