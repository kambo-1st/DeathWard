005f6b47 test esi, esi
005f6b49 jne 0x5f6e5e
005f6b4f mov ecx, dword ptr [0xbfd65c]
005f6b55 xor eax, eax
005f6b57 xorps xmm2, xmm2
005f6b5a movss dword ptr [esp + 0x34], xmm2
005f6b60 mov ecx, dword ptr [ecx + 0x18190]
005f6b66 mov edx, dword ptr [ecx + 0x1264]
005f6b6c mov dword ptr [esp + 0x3c], edx
005f6b70 test edx, edx
005f6b72 je 0x5f6e50
005f6b78 movss xmm1, dword ptr [edi + 0x294]
005f6b80 xor ebx, ebx
005f6b82 movss xmm3, dword ptr [edi + 0x298]
005f6b8a mov eax, dword ptr [ecx + 0x125c]
005f6b90 mov esi, dword ptr [edi + 0x360]
005f6b96 movss dword ptr [esp + 0x40], xmm1
005f6b9c movss dword ptr [esp + 0x44], xmm3
005f6ba2 mov dword ptr [esp + 0x38], eax
005f6ba6 mov edi, dword ptr [eax]
005f6ba8 movss xmm0, dword ptr [edi + 0x294]
005f6bb0 movss xmm2, dword ptr [edi + 0x298]
005f6bb8 subss xmm1, xmm0
005f6bbc movss dword ptr [esp + 0x18], xmm0
005f6bc2 movaps xmm0, xmm3
005f6bc5 subss xmm0, xmm2
005f6bc9 movss dword ptr [esp + 0x1c], xmm2
005f6bcf mulss xmm1, xmm1
005f6bd3 mulss xmm0, xmm0
005f6bd7 addss xmm0, xmm1
005f6bdb call 0x4228c0
005f6be0 movss xmm1, dword ptr [esi + 0x294]
005f6be8 subss xmm1, dword ptr [edi + 0x294]
005f6bf0 movss dword ptr [esp + 0x28], xmm0
005f6bf6 movss xmm0, dword ptr [esi + 0x298]
005f6bfe subss xmm0, dword ptr [edi + 0x298]
005f6c06 mulss xmm1, xmm1
005f6c0a mulss xmm0, xmm0
005f6c0e addss xmm0, xmm1
005f6c12 call 0x4228c0
005f6c17 mov eax, dword ptr [edi + 0x28]
005f6c1a add eax, -0xa
005f6c1d movss dword ptr [esp + 0x30], xmm0
005f6c23 cmp eax, 0x3dd
005f6c28 ja 0x5f6e0a
005f6c2e mov eax, dword ptr [edi + 0x180]
005f6c34 cmp eax, 1
005f6c37 je 0x5f6e0a
005f6c3d test eax, eax
005f6c3f je 0x5f6e0a
005f6c45 cmp byte ptr [edi + 0x308], 0
005f6c4c jne 0x5f6e0a
005f6c52 cmp byte ptr [edi + 0x16b], 0
005f6c59 jne 0x5f6e0a
005f6c5f push 0
005f6c61 push 0x10
005f6c63 mov ecx, edi
005f6c65 call 0x4122f0
005f6c6a mov ecx, dword ptr [edi + 0x28]
005f6c6d test al, al
005f6c6f je 0x5f6c85
005f6c71 cmp ecx, 0x322
005f6c77 je 0x5f6c85
005f6c79 cmp ecx, 0x362
005f6c7f jne 0x5f6e0a
005f6c85 mov eax, dword ptr [edi + 0x160]
005f6c8b and eax, 0x20000010
005f6c90 or eax, 0
005f6c93 jne 0x5f6e0a
005f6c99 cmp ecx, 0x322
005f6c9f je 0x5f6e0a
005f6ca5 movss xmm0, dword ptr [esp + 0x28]
005f6cab movss xmm1, dword ptr [ebp + 8]
005f6cb0 comiss xmm1, xmm0
005f6cb3 jae 0x5f6cca
005f6cb5 cmp byte ptr [esp + 0x2c], al
005f6cb9 je 0x5f6e0a
005f6cbf comiss xmm1, dword ptr [esp + 0x30]
005f6cc4 jbe 0x5f6e0a
005f6cca cmp byte ptr [esp + 0x12], 0
005f6ccf xorps xmm3, xmm3
005f6cd2 xorps xmm1, xmm1
005f6cd5 je 0x5f6d7a
005f6cdb movss xmm1, dword ptr [esp + 0x18]
005f6ce1 subss xmm1, dword ptr [esp + 0x40]
005f6ce7 movss xmm2, dword ptr [esp + 0x1c]
005f6ced subss xmm2, dword ptr [esp + 0x44]
005f6cf3 movaps xmm0, xmm1
005f6cf6 movss dword ptr [esp + 0x18], xmm1
005f6cfc mulss xmm0, xmm1
005f6d00 movaps xmm1, xmm2
005f6d03 movss dword ptr [esp + 0x1c], xmm2
005f6d09 mulss xmm1, xmm2
005f6d0d addss xmm0, xmm1
005f6d11 call 0x4228c0
005f6d16 movss xmm2, dword ptr [esp + 0x18]
005f6d1c xorps xmm3, xmm3
005f6d1f comiss xmm0, xmm3
005f6d22 movss xmm4, dword ptr [esp + 0x1c]
005f6d28 jbe 0x5f6d41
005f6d2a movss xmm1, dword ptr [0xb6a614]
005f6d32 divss xmm1, xmm0
005f6d36 movaps xmm0, xmm1
005f6d39 mulss xmm4, xmm1
005f6d3d mulss xmm2, xmm0
005f6d41 movss xmm0, dword ptr [esp + 0x24]
005f6d47 movss xmm1, dword ptr [esp + 0x20]
005f6d4d mulss xmm0, xmm2
005f6d51 mulss xmm1, xmm4
005f6d55 addss xmm1, xmm0
005f6d59 movss xmm0, dword ptr [esp + 0x48]
005f6d5f comiss xmm0, xmm1
005f6d62 ja 0x5f6e0a
005f6d68 mulss xmm1, dword ptr [0xb6acec]
005f6d70 movss xmm0, dword ptr [esp + 0x28]
005f6d76 addss xmm1, xmm3
005f6d7a cmp byte ptr [ebp + 0x10], 0
005f6d7e movss xmm4, dword ptr [0xb6ac60]
005f6d86 jne 0x5f6d92
005f6d88 cmp edi, dword ptr [esp + 0x14]
005f6d8c jne 0x5f6d92
005f6d8e addss xmm1, xmm4
005f6d92 cmp byte ptr [esp + 0x2c], 0
005f6d97 movss xmm2, dword ptr [0xb6acc0]
005f6d9f subss xmm2, xmm0
005f6da3 maxss xmm2, xmm3
005f6da7 addss xmm2, xmm1
005f6dab je 0x5f6dc6
005f6dad movaps xmm0, xmm4
005f6db0 subss xmm0, dword ptr [esp + 0x30]
005f6db6 maxss xmm0, xmm3
005f6dba mulss xmm0, dword ptr [0xb6a864]
005f6dc2 addss xmm2, xmm0
005f6dc6 cmp byte ptr [esp + 0x4c], 0
005f6dcb je 0x5f6de0
005f6dcd movaps xmm0, xmm4
005f6dd0 subss xmm0, dword ptr [edi + 0x2d8]
005f6dd8 maxss xmm0, xmm3
005f6ddc addss xmm2, xmm0
005f6de0 cmp byte ptr [esp + 0x50], 0
005f6de5 je 0x5f6dfb
005f6de7 movss xmm0, dword ptr [edi + 0x2d8]
005f6def minss xmm0, dword ptr [0xb6accc]
005f6df7 addss xmm2, xmm0
005f6dfb comiss xmm2, dword ptr [esp + 0x34]
005f6e00 jbe 0x5f6e0a
005f6e02 movss dword ptr [esp + 0x34], xmm2
005f6e08 mov ebx, edi
005f6e0a mov eax, dword ptr [esp + 0x38]
005f6e0e mov edi, ebx
005f6e10 movss xmm1, dword ptr [esp + 0x40]
005f6e16 add eax, 4
005f6e19 sub dword ptr [esp + 0x3c], 1
005f6e1e movss xmm3, dword ptr [esp + 0x44]
005f6e24 mov dword ptr [esp + 0x38], eax
005f6e28 jne 0x5f6ba6
005f6e2e mov ebx, dword ptr [esp + 0x54]
005f6e32 mov eax, edi
005f6e34 mov ecx, dword ptr [ebx]
005f6e36 test ecx, ecx
005f6e38 je 0x5f6e50
005f6e3a lea eax, [esp + 0x54]
005f6e3e mov dword ptr [esp + 0x54], ebx
005f6e42 push eax
005f6e43 add ecx, 0x324
005f6e49 call 0x4bc3c0
005f6e4e mov eax, edi
