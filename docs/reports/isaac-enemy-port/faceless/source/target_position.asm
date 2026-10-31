00695a30 push ebp
00695a31 mov ebp, esp
00695a33 and esp, 0xfffffff8
00695a36 sub esp, 0x1c
00695a39 push ebx
00695a3a push esi
00695a3b mov esi, ecx
00695a3d push edi
00695a3e mov eax, dword ptr [esi + 0x164]
00695a44 mov ecx, dword ptr [esi + 0x160]
00695a4a mov dword ptr [esp + 0x24], eax
00695a4e mov eax, ecx
00695a50 and eax, 0x200
00695a55 or eax, 0
00695a58 je 0x695bf3
00695a5e movss xmm0, dword ptr [esi + 0xb7c]
00695a66 ucomiss xmm0, dword ptr [0xc02fec]
00695a6d mov edi, dword ptr [0xbfd65c]
00695a73 lahf 
00695a74 test ah, 0x44
00695a77 jp 0x695a8e
00695a79 movss xmm0, dword ptr [esi + 0xb80]
00695a81 ucomiss xmm0, dword ptr [0xc02ff0]
00695a88 lahf 
00695a89 test ah, 0x44
00695a8c jnp 0x695ac2
00695a8e and ecx, 0x4000
00695a94 or ecx, 0
00695a97 jne 0x695bd6
00695a9d mov ecx, edi
00695a9f call 0x6d0380
00695aa4 test al, al
00695aa6 jne 0x695bd6
00695aac mov eax, dword ptr [edi + 0x1a30dc]
00695ab2 mov ecx, 0xf
00695ab7 cdq 
00695ab8 idiv ecx
00695aba test edx, edx
00695abc jne 0x695bd6
00695ac2 call 0x6c3d90
00695ac7 movss xmm2, dword ptr [0xb6a19c]
00695acf movd xmm0, eax
00695ad3 cvtdq2pd xmm0, xmm0
00695ad7 shr eax, 0x1f
00695ada addsd xmm0, qword ptr [eax*8 + 0xb6c940]
00695ae3 cvtpd2ps xmm1, xmm0
00695ae7 mulss xmm1, xmm2
00695aeb call 0x6c3d90
00695af0 movd xmm0, eax
00695af4 cvtdq2pd xmm0, xmm0
00695af8 shr eax, 0x1f
00695afb addsd xmm0, qword ptr [eax*8 + 0xb6c940]
00695b04 cvtpd2ps xmm0, xmm0
00695b08 mulss xmm0, xmm2
00695b0c mulss xmm0, xmm1
00695b10 mulss xmm0, dword ptr [0xb6abe4]
00695b18 movss dword ptr [esp + 0xc], xmm0
00695b1e call 0x6c3d90
00695b23 movd xmm0, eax
00695b27 cvtdq2pd xmm0, xmm0
00695b2b shr eax, 0x1f
00695b2e addsd xmm0, qword ptr [eax*8 + 0xb6c940]
00695b37 cvtpd2ps xmm0, xmm0
00695b3b mulss xmm0, xmm2
00695b3f mulss xmm0, dword ptr [0xb6a874]
00695b47 addss xmm0, xmm0
00695b4b movss dword ptr [esp + 0x20], xmm0
00695b51 call 0x411fe0
00695b56 mulss xmm0, dword ptr [esp + 0xc]
00695b5c addss xmm0, dword ptr [esi + 0x294]
00695b64 movss dword ptr [esp + 0x18], xmm0
00695b6a movss xmm0, dword ptr [esp + 0x20]
00695b70 call 0x412010
00695b75 mulss xmm0, dword ptr [esp + 0xc]
00695b7b lea eax, [esp + 0x18]
00695b7f sub esp, 0xc
00695b82 mov ecx, dword ptr [edi + 0x18190]
00695b88 movss xmm3, dword ptr [esi + 0x2c8]
00695b90 addss xmm0, dword ptr [esi + 0x298]
00695b98 movss dword ptr [esp + 8], xmm3
00695b9e movss dword ptr [esp + 4], xmm3
00695ba4 movss dword ptr [esp], xmm3
00695ba9 push eax
00695baa lea eax, [esp + 0x30]
00695bae movss dword ptr [esp + 0x2c], xmm0
00695bb4 push eax
00695bb5 call 0x7cec10
00695bba movss xmm0, dword ptr [esp + 0x20]
00695bc0 movss dword ptr [esi + 0xb7c], xmm0
00695bc8 movss xmm0, dword ptr [esp + 0x24]
00695bce movss dword ptr [esi + 0xb80], xmm0
00695bd6 mov eax, dword ptr [ebp + 8]
00695bd9 mov ecx, dword ptr [esi + 0xb7c]
00695bdf mov edx, dword ptr [esi + 0xb80]
00695be5 mov dword ptr [eax + 4], edx
00695be8 mov dword ptr [eax], ecx
00695bea pop edi
00695beb pop esi
00695bec pop ebx
00695bed mov esp, ebp
00695bef pop ebp
00695bf0 ret 8
00695bf3 and ecx, 0x1000800
00695bf9 or ecx, 0
00695bfc je 0x695c0c
00695bfe mov eax, dword ptr [esi + 0x28]
00695c01 cmp eax, 0x10
00695c04 jne 0x695c30
00695c06 cmp dword ptr [esi + 0x2c], 2
00695c0a je 0x695c3c
00695c0c mov ecx, esi
00695c0e call 0x695680
00695c13 mov ecx, dword ptr [eax + 0x294]
00695c19 mov edx, dword ptr [eax + 0x298]
00695c1f mov eax, dword ptr [ebp + 8]
00695c22 mov dword ptr [eax + 4], edx
00695c25 mov dword ptr [eax], ecx
00695c27 pop edi
00695c28 pop esi
00695c29 pop ebx
00695c2a mov esp, ebp
00695c2c pop ebp
00695c2d ret 8
00695c30 cmp eax, 0x16
00695c33 je 0x695c0c
00695c35 cmp eax, 0xcd
00695c3a je 0x695c0c
00695c3c mov ecx, esi
00695c3e call 0x695680
00695c43 movss xmm1, dword ptr [ebp + 0xc]
00695c48 xorps xmm6, xmm6
00695c4b movss xmm4, dword ptr [esi + 0x294]
00695c53 movss xmm5, dword ptr [esi + 0x298]
00695c5b movss xmm0, dword ptr [eax + 0x294]
00695c63 movss xmm2, dword ptr [eax + 0x298]
00695c6b subss xmm0, xmm4
00695c6f ucomiss xmm1, xmm6
00695c72 subss xmm2, xmm5
00695c76 movss dword ptr [esp + 0x18], xmm4
00695c7c movss dword ptr [esp + 0xc], xmm0
00695c82 lahf 
00695c83 movss dword ptr [esp + 0x20], xmm5
00695c89 movss dword ptr [esp + 0x10], xmm2
00695c8f test ah, 0x44
00695c92 jnp 0x695cf0
00695c94 movaps xmm3, xmm2
00695c97 movaps xmm1, xmm0
00695c9a mulss xmm3, xmm2
00695c9e mulss xmm1, xmm0
00695ca2 addss xmm3, xmm1
00695ca6 ucomiss xmm3, xmm6
00695ca9 lahf 
00695caa test ah, 0x44
00695cad jnp 0x695cf0
00695caf movaps xmm0, xmm3
00695cb2 call 0x4228c0
00695cb7 movss xmm2, dword ptr [esp + 0x10]
00695cbd xorps xmm1, xmm1
00695cc0 comiss xmm0, xmm1
00695cc3 movss xmm4, dword ptr [esp + 0x18]
00695cc9 movss xmm5, dword ptr [esp + 0x20]
00695ccf jbe 0x695cea
00695cd1 movss xmm1, dword ptr [ebp + 0xc]
00695cd6 divss xmm1, xmm0
00695cda movss xmm0, dword ptr [esp + 0xc]
00695ce0 mulss xmm0, xmm1
00695ce4 mulss xmm2, xmm1
00695ce8 jmp 0x695cf0
00695cea movss xmm0, dword ptr [esp + 0xc]
00695cf0 movss xmm3, dword ptr [esi + 0x2c8]
00695cf8 subss xmm4, xmm0
00695cfc mov ebx, dword ptr [0xbfd65c]
00695d02 subss xmm5, xmm2
00695d06 sub esp, 0xc
00695d09 lea eax, [esp + 0x2c]
00695d0d mov ecx, dword ptr [ebx + 0x18190]
00695d13 movss dword ptr [esp + 8], xmm3
00695d19 movss dword ptr [esp + 4], xmm3
00695d1f movss dword ptr [esp], xmm3
00695d24 push eax
00695d25 lea eax, [esp + 0x28]
00695d29 movss dword ptr [esp + 0x30], xmm4
00695d2f push eax
00695d30 movss dword ptr [esp + 0x38], xmm5
00695d36 call 0x7cec10
00695d3b movss xmm0, dword ptr [esp + 0x20]
00695d41 movss xmm2, dword ptr [esp + 0x18]
00695d47 ucomiss xmm0, xmm2
00695d4a lahf 
00695d4b test ah, 0x44
00695d4e jp 0x695d9a
00695d50 movss xmm0, dword ptr [esp + 0x24]
00695d56 movss xmm1, dword ptr [esp + 0x1c]
00695d5c ucomiss xmm0, xmm1
00695d5f lahf 
00695d60 test ah, 0x44
00695d63 jp 0x695d9a
00695d65 movss xmm0, dword ptr [0xc02fec]
00695d6d mov eax, dword ptr [ebp + 8]
00695d70 movss dword ptr [esi + 0xb7c], xmm0
00695d78 movss xmm0, dword ptr [0xc02ff0]
00695d80 movss dword ptr [esi + 0xb80], xmm0
00695d88 movss dword ptr [eax], xmm2
00695d8c movss dword ptr [eax + 4], xmm1
00695d91 pop edi
00695d92 pop esi
00695d93 pop ebx
00695d94 mov esp, ebp
00695d96 pop ebp
00695d97 ret 8
00695d9a push 0xc02fec
00695d9f lea ecx, [esi + 0xb7c]
00695da5 call 0x962c70
00695daa test al, al
00695dac jne 0x695df2
00695dae call 0x6c3d90
00695db3 xor edx, edx
00695db5 mov ecx, 0xf
00695dba div ecx
00695dbc push 0
00695dbe mov ecx, esi
00695dc0 lea eax, [edx + 5]
00695dc3 push eax
00695dc4 call 0x684790
00695dc9 test al, al
00695dcb jne 0x695df2
00695dcd mov eax, dword ptr [ebp + 8]
00695dd0 movss xmm2, dword ptr [esi + 0xb7c]
00695dd8 movss xmm1, dword ptr [esi + 0xb80]
00695de0 movss dword ptr [eax], xmm2
00695de4 movss dword ptr [eax + 4], xmm1
00695de9 pop edi
00695dea pop esi
00695deb pop ebx
00695dec mov esp, ebp
00695dee pop ebp
00695def ret 8
00695df2 call 0x6c3d90
00695df7 movd xmm0, eax
00695dfb cvtdq2pd xmm0, xmm0
00695dff shr eax, 0x1f
00695e02 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
00695e0b lea eax, [esp + 0x10]
00695e0f push eax
00695e10 cvtpd2ps xmm0, xmm0
00695e14 mulss xmm0, dword ptr [0xb6a19c]
00695e1c mulss xmm0, dword ptr [0xb6aafc]
00695e24 movss dword ptr [esp + 0x24], xmm0
00695e2a call 0x659290
00695e2f movss xmm2, dword ptr [esp + 0x24]
00695e35 movss xmm0, dword ptr [esi + 0x294]
00695e3d movaps xmm1, xmm2
00695e40 movss xmm3, dword ptr [esi + 0x2c8]
00695e48 mulss xmm1, dword ptr [eax]
00695e4c mov ecx, dword ptr [ebx + 0x18190]
00695e52 mulss xmm2, dword ptr [eax + 4]
00695e57 lea eax, [esp + 0x24]
00695e5b subss xmm0, xmm1
00695e5f movss dword ptr [esp], xmm3
00695e64 sub esp, 8
00695e67 movss dword ptr [esp + 0x2c], xmm0
00695e6d movss xmm0, dword ptr [esi + 0x298]
00695e75 movss dword ptr [esp + 4], xmm3
00695e7b subss xmm0, xmm2
00695e7f movss dword ptr [esp], xmm3
00695e84 push eax
00695e85 lea eax, [esp + 0x28]
00695e89 push eax
00695e8a movss dword ptr [esp + 0x38], xmm0
00695e90 call 0x7cec10
00695e95 movss xmm2, dword ptr [esp + 0x18]
00695e9b movss xmm1, dword ptr [esp + 0x1c]
00695ea1 mov eax, dword ptr [ebp + 8]
00695ea4 pop edi
00695ea5 movss dword ptr [esi + 0xb7c], xmm2
00695ead movss dword ptr [esi + 0xb80], xmm1
00695eb5 pop esi
00695eb6 movss dword ptr [eax], xmm2
00695eba movss dword ptr [eax + 4], xmm1
00695ebf pop ebx
00695ec0 mov esp, ebp
00695ec2 pop ebp
00695ec3 ret 8
