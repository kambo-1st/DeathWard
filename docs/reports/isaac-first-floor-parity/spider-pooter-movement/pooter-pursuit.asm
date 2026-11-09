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
