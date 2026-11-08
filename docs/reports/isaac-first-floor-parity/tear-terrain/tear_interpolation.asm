00653a6c mov eax, dword ptr [edi + 0x294]
00653a72 lea esi, [edi + 0x294]
00653a78 mov dword ptr [edi + 0x29c], eax
00653a7e mov eax, dword ptr [esi + 4]
00653a81 mov dword ptr [edi + 0x2a0], eax
00653a87 movss xmm3, dword ptr [edi + 0x2c4]
00653a8f movss xmm2, dword ptr [edi + 0x2bc]
00653a97 movaps xmm0, xmm3
00653a9a mulss xmm0, dword ptr [edi + 0x2b8]
00653aa2 test byte ptr [edi + 0x30], 2
00653aa6 movss xmm1, dword ptr [edi + 0x2f4]
00653aae mulss xmm3, xmm2
00653ab2 mulss xmm0, xmm1
00653ab6 mulss xmm3, xmm1
00653aba mulss xmm0, xmm4
00653abe mulss xmm3, xmm4
00653ac2 addss xmm0, dword ptr [esi]
00653ac6 addss xmm3, dword ptr [esi + 4]
00653acb movss dword ptr [esi], xmm0
00653acf movss dword ptr [esi + 4], xmm3
00653ad4 mov byte ptr [edi + 0x16d], 1
00653adb mov edx, dword ptr [edi + 0x314]
00653ae1 mov dword ptr [esp + 0xc], edx
00653ae5 test edx, edx
00653ae7 je 0x653af3
00653ae9 cmp dword ptr [edx + 0x28], 2
00653aed je 0x653b9a
00653af3 mov eax, dword ptr [edi + 0x380]
00653af9 and eax, dword ptr [0xbc4948]
00653aff mov ecx, dword ptr [edi + 0x378]
00653b05 and ecx, dword ptr [0xbc4940]
00653b0b mov dword ptr [esp + 0x24], eax
00653b0f mov eax, dword ptr [edi + 0x384]
00653b15 and eax, dword ptr [0xbc494c]
00653b1b mov dword ptr [esp + 0x1c], eax
00653b1f mov eax, dword ptr [edi + 0x37c]
00653b25 and eax, dword ptr [0xbc4944]
00653b2b or ecx, eax
00653b2d jne 0x653b84
00653b2f mov eax, dword ptr [esp + 0x24]
00653b33 or eax, dword ptr [esp + 0x1c]
00653b37 jne 0x653b84
00653b39 mov ecx, dword ptr [0xbfd65c]
00653b3f sub esp, 0xc
00653b42 xorps xmm3, xmm3
00653b45 mov ecx, dword ptr [ecx + 0x18190]
00653b4b mov dword ptr [esp + 8], eax
00653b4f mov dword ptr [esp + 4], eax
00653b53 mov dword ptr [esp], eax
00653b56 lea eax, [esp + 0x34]
00653b5a push esi
00653b5b push eax
00653b5c call 0x7cec10
00653b61 movss xmm0, dword ptr [esp + 0x28]
00653b67 movss xmm4, dword ptr [0xb6a480]
00653b6f movss dword ptr [esi], xmm0
00653b73 movss xmm0, dword ptr [esp + 0x2c]
00653b79 movss dword ptr [esi + 4], xmm0
00653b7e mov edx, dword ptr [edi + 0x314]
