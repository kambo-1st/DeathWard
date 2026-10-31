004f6bb9 movss xmm0, dword ptr [esi + 0x28c]
004f6bc1 ucomiss xmm0, dword ptr [0xc02fec]
004f6bc8 lahf 
004f6bc9 test ah, 0x44
004f6bcc jp 0x4f6d0e
004f6bd2 movss xmm0, dword ptr [esi + 0x290]
004f6bda ucomiss xmm0, dword ptr [0xc02ff0]
004f6be1 lahf 
004f6be2 test ah, 0x44
004f6be5 jp 0x4f6d0e
004f6beb cmp dword ptr [esi + 0xe6c], -1
004f6bf2 je 0x4f6c6e
004f6bf4 movss xmm1, dword ptr [0xb6a7b0]
004f6bfc xorps xmm2, xmm2
004f6bff mov ecx, esi
004f6c01 call 0x6847e0
004f6c06 test eax, eax
004f6c08 je 0x4f6d0e
004f6c0e lea eax, [esp + 0xc]
004f6c12 xorps xmm2, xmm2
004f6c15 push eax
004f6c16 mov ecx, esi
004f6c18 call 0x6af0c0
004f6c1d movss xmm0, dword ptr [esp + 0xc]
004f6c23 mulss xmm0, dword ptr [0xb6a64c]
004f6c2b movss xmm1, dword ptr [esi + 0x2f4]
004f6c33 mulss xmm0, xmm1
004f6c37 addss xmm0, dword ptr [esi + 0x2b8]
004f6c3f movss dword ptr [esi + 0x2b8], xmm0
004f6c47 movss xmm0, dword ptr [esp + 0x10]
004f6c4d mulss xmm0, dword ptr [0xb6a64c]
004f6c55 mulss xmm0, xmm1
004f6c59 addss xmm0, dword ptr [esi + 0x2bc]
004f6c61 movss dword ptr [esi + 0x2bc], xmm0
004f6c69 jmp 0x4f6d0e
004f6c6e call 0x6c3d90
004f6c73 xor edx, edx
004f6c75 mov ecx, 5
004f6c7a div ecx
004f6c7c test edx, edx
004f6c7e jne 0x4f6d0e
004f6c84 mov ecx, esi
004f6c86 call 0x695680
004f6c8b lea ecx, [esp + 0xc]
004f6c8f movss xmm0, dword ptr [eax + 0x294]
004f6c97 movss xmm1, dword ptr [eax + 0x298]
004f6c9f lea eax, [esp + 0x44]
004f6ca3 subss xmm0, dword ptr [esi + 0x294]
004f6cab subss xmm1, dword ptr [esi + 0x298]
004f6cb3 push eax
004f6cb4 movss dword ptr [esp + 0x10], xmm0
004f6cba movss dword ptr [esp + 0x14], xmm1
004f6cc0 call 0x962560
004f6cc5 movss xmm1, dword ptr [esi + 0x2f4]
004f6ccd movss xmm2, dword ptr [eax + 4]
004f6cd2 movss xmm0, dword ptr [eax]
004f6cd6 mulss xmm0, dword ptr [0xb6a50c]
004f6cde mulss xmm2, dword ptr [0xb6a50c]
004f6ce6 mulss xmm0, xmm1
004f6cea mulss xmm2, xmm1
004f6cee addss xmm0, dword ptr [esi + 0x2b8]
004f6cf6 addss xmm2, dword ptr [esi + 0x2bc]
004f6cfe movss dword ptr [esi + 0x2b8], xmm0
004f6d06 movss dword ptr [esi + 0x2bc], xmm2
