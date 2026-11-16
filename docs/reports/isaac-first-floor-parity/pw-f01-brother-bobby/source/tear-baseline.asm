00618b60 xor esi, esi
00618b62 mov ecx, edi
00618b64 mov dword ptr [esp + 0x2c], esi
00618b68 movlpd qword ptr [esp + 0x10], xmm0
00618b6e movlpd qword ptr [esp + 0x18], xmm0
00618b74 call 0x5efe20
00618b79 mov ecx, edi
00618b7b movss dword ptr [esp + 0x38], xmm0
00618b81 call 0x5efe20
00618b86 movss xmm4, dword ptr [0xb6a53c]
00618b8e lea ecx, [esp + 0xa4]
00618b95 movss xmm3, dword ptr [0xb6a560]
00618b9d movaps xmm1, xmm0
00618ba0 mulss xmm1, dword ptr [0xb6a38c]
00618ba8 xorps xmm2, xmm2
00618bab movss xmm0, dword ptr [0xb6a8a0]
00618bb3 movss dword ptr [esp + 0x24], xmm0
00618bb9 addss xmm1, xmm4
00618bbd movss dword ptr [esp + 0x30], xmm2
00618bc3 mulss xmm1, xmm3
00618bc7 movss dword ptr [esp + 0x28], xmm1
00618bcd call 0x402120
00618bd2 mov eax, dword ptr [edi + 0x2c]
00618bd5 cmp eax, 0x4a
00618bd8 jne 0x618be3
00618bda mov edx, dword ptr [edi + 0x30]
00618bdd mov dword ptr [esp + 0x4c], edx
00618be1 jmp 0x618bef
00618be3 or edx, 0xffffffff
00618be6 mov dword ptr [esp + 0x4c], edx
00618bea cmp eax, 0xb
00618bed je 0x618bfa
00618bef xor ecx, ecx
00618bf1 mov dword ptr [esp + 0x34], ecx
