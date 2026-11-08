004f6d93 cmp edx, 2
004f6d96 jne 0x4f6e78
004f6d9c cmp dword ptr [esi + 0x34], 0x43
004f6da0 je 0x4f6e2e
004f6da6 movss xmm2, dword ptr [esi + 0x298]
004f6dae movss xmm0, dword ptr [0xb6abd0]
004f6db6 comiss xmm0, xmm2
004f6db9 movss xmm1, dword ptr [0xb6a278]
004f6dc1 jbe 0x4f6dd1
004f6dc3 movss xmm0, dword ptr [esi + 0xb04]
004f6dcb addss xmm0, xmm1
004f6dcf jmp 0x4f6de6
004f6dd1 comiss xmm2, dword ptr [0xb6ac6c]
004f6dd8 jbe 0x4f6dee
004f6dda movss xmm0, dword ptr [esi + 0xb04]
004f6de2 subss xmm0, xmm1
004f6de6 movss dword ptr [esi + 0xb04], xmm0
004f6dee movss xmm2, dword ptr [esi + 0x294]
004f6df6 comiss xmm2, dword ptr [0xb6ac94]
004f6dfd jbe 0x4f6e0d
004f6dff movss xmm0, dword ptr [esi + 0xb00]
004f6e07 subss xmm0, xmm1
004f6e0b jmp 0x4f6e26
004f6e0d movss xmm0, dword ptr [0xb6aad4]
004f6e15 comiss xmm0, xmm2
004f6e18 jbe 0x4f6e2e
004f6e1a movss xmm0, dword ptr [esi + 0xb00]
004f6e22 addss xmm0, xmm1
004f6e26 movss dword ptr [esi + 0xb00], xmm0
