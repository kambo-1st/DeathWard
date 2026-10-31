006a3970 push ebp
006a3971 mov ebp, esp
006a3973 push -1
006a3975 push 0x9f492d
006a397a mov eax, dword ptr fs:[0]
006a3980 push eax
006a3981 sub esp, 0x160
006a3987 mov eax, dword ptr [0xbaa3b4]
006a398c xor eax, ebp
006a398e mov dword ptr [ebp - 0x10], eax
006a3991 push esi
006a3992 push edi
006a3993 push eax
006a3994 lea eax, [ebp - 0xc]
006a3997 mov dword ptr fs:[0], eax
006a399d mov edi, ecx
006a399f mov dword ptr [ebp - 0x10c], edi
006a39a5 push dword ptr [ebp + 0xc]
006a39a8 mov esi, dword ptr [ebp + 8]
006a39ab push esi
006a39ac push edi
006a39ad mov dword ptr [ebp - 0x118], esi
006a39b3 call 0x7fd2f0
006a39b8 cmp eax, 1
006a39bb je 0x6a46d7
006a39c1 cmp eax, -1
006a39c4 je 0x6a41dc
006a39ca mov eax, dword ptr [edi + 0x28]
006a39cd mov byte ptr [ebp - 0x114], 1
006a39d4 cmp eax, 0x362
006a39d9 jne 0x6a39fc
006a39db mov eax, dword ptr [esi + 0x28]
006a39de cmp eax, 2
006a39e1 je 0x6a46d7
006a39e7 cmp eax, 9
006a39ea je 0x6a46d7
006a39f0 cmp eax, 4
006a39f3 je 0x6a46d7
006a39f9 mov eax, dword ptr [edi + 0x28]
006a39fc mov ecx, dword ptr [esi + 0x28]
006a39ff cmp ecx, 1
006a3a02 jne 0x6a3a39
006a3a04 cmp eax, 0x21
006a3a07 jne 0x6a3da4
006a3a0d cmp dword ptr [edi + 0x2c], 4
006a3a11 jne 0x6a3da4
006a3a17 mov ecx, esi
006a3a19 call 0x78cdc0
006a3a1e cmp eax, 2
006a3a21 je 0x6a46d7
006a3a27 call 0x79c960
006a3a2c test al, al
006a3a2e je 0x6a3da4
006a3a34 jmp 0x6a46d7
006a3a39 cmp ecx, 2
006a3a3c jne 0x6a3da4
006a3a42 movups xmm0, xmmword ptr [esi + 0x378]
006a3a49 push 0xbc4ce0
006a3a4e mov edx, 0xbc4ca0
006a3a53 lea ecx, [ebp - 0x130]
006a3a59 movups xmmword ptr [ebp - 0x20], xmm0
006a3a5d call 0x427220
006a3a62 push eax
006a3a63 lea edx, [ebp - 0x20]
006a3a66 lea ecx, [ebp - 0x140]
006a3a6c call 0x412050
006a3a71 add esp, 8
006a3a74 mov ecx, dword ptr [eax]
006a3a76 or ecx, dword ptr [eax + 4]
006a3a79 jne 0x6a3da4
006a3a7f mov ecx, dword ptr [eax + 8]
006a3a82 or ecx, dword ptr [eax + 0xc]
006a3a85 jne 0x6a3da4
006a3a8b cmp dword ptr [edi + 0x28], 0x29
006a3a8f jne 0x6a3da4
006a3a95 cmp dword ptr [edi + 0x2c], 4
006a3a99 jne 0x6a3da4
006a3a9f movss xmm0, dword ptr [esi + 0x2b8]
006a3aa7 mov ecx, edi
006a3aa9 movss dword ptr [ebp - 0x100], xmm0
006a3ab1 movss xmm0, dword ptr [esi + 0x2bc]
006a3ab9 movss dword ptr [ebp - 0xfc], xmm0
006a3ac1 push dword ptr [ebp - 0xfc]
006a3ac7 push dword ptr [ebp - 0x100]
006a3acd call 0x6aa830
006a3ad2 test al, al
006a3ad4 jne 0x6a3da4
006a3ada call 0x6c3d90
006a3adf movss xmm2, dword ptr [0xb6a53c]
006a3ae7 push ecx
006a3ae8 movd xmm0, eax
006a3aec cvtdq2pd xmm0, xmm0
006a3af0 shr eax, 0x1f
006a3af3 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
006a3afc cvtpd2ps xmm0, xmm0
006a3b00 mulss xmm0, dword ptr [0xb6a19c]
006a3b08 mulss xmm0, dword ptr [0xb6a2ac]
006a3b10 addss xmm0, dword ptr [0xb6a588]
006a3b18 movss dword ptr [esp], xmm0
006a3b1d push 0
006a3b1f push 2
006a3b21 push 0xab
006a3b26 call 0x68d750
006a3b2b cmp dword ptr [edi + 0xaf0], 0
006a3b32 jg 0x6a3da4
006a3b38 xorps xmm0, xmm0
006a3b3b lea eax, [ebp - 0x28]
006a3b3e movss dword ptr [ebp - 0xf0], xmm0
006a3b46 lea ecx, [edi + 0x6c]
006a3b49 movss xmm0, dword ptr [0xb6a614]
006a3b51 push eax
006a3b52 movss dword ptr [ebp - 0xf8], xmm0
006a3b5a call 0x444be0
006a3b5f mov dword ptr [ebp - 4], 0
006a3b66 lea ecx, [ebp - 0x28]
006a3b69 cmp dword ptr [ebp - 0x14], 0x10
006a3b6d mov edx, dword ptr [ebp - 0x18]
006a3b70 cmovae ecx, dword ptr [ebp - 0x28]
006a3b74 push 2
006a3b76 push 0xb406e4
006a3b7b call 0x408190
006a3b80 add esp, 8
006a3b83 test al, al
006a3b85 je 0x6a3b9c
006a3b87 xorps xmm0, xmm0
006a3b8a movss dword ptr [ebp - 0xf0], xmm0
006a3b92 movss xmm0, dword ptr [0xb6ae44]
006a3b9a jmp 0x6a3be3
006a3b9c cmp dword ptr [ebp - 0x14], 0x10
006a3ba0 lea ecx, [ebp - 0x28]
006a3ba3 mov edx, dword ptr [ebp - 0x18]
006a3ba6 cmovae ecx, dword ptr [ebp - 0x28]
006a3baa push 4
006a3bac push 0xb42f28
006a3bb1 call 0x408190
006a3bb6 add esp, 8
006a3bb9 test al, al
006a3bbb je 0x6a3beb
006a3bbd cmp byte ptr [edi + 0x13c], 0
006a3bc4 je 0x6a3bd0
006a3bc6 movss xmm0, dword ptr [0xb6ae44]
006a3bce jmp 0x6a3bd8
006a3bd0 movss xmm0, dword ptr [0xb6a614]
006a3bd8 movss dword ptr [ebp - 0xf0], xmm0
006a3be0 xorps xmm0, xmm0
006a3be3 movss dword ptr [ebp - 0xf8], xmm0
006a3beb mov eax, dword ptr [esi + 0x2b8]
006a3bf1 mov ecx, dword ptr [esi + 0x2bc]
006a3bf7 mov dword ptr [ebp - 0x100], eax
006a3bfd lea eax, [ebp - 0x108]
006a3c03 mov dword ptr [ebp - 0xfc], ecx
006a3c09 lea ecx, [ebp - 0x100]
006a3c0f push eax
006a3c10 call 0x962560
006a3c15 movss xmm5, dword ptr [ebp - 0xf8]
006a3c1d movss xmm4, dword ptr [ebp - 0xf0]
006a3c25 movaps xmm1, xmm5
006a3c28 movaps xmm0, xmm4
006a3c2b mulss xmm1, dword ptr [eax + 4]
006a3c30 mulss xmm0, dword ptr [eax]
006a3c34 addss xmm1, xmm0
006a3c38 movss xmm0, dword ptr [0xb6a3b0]
006a3c40 andps xmm1, xmmword ptr [0xb6c980]
006a3c47 comiss xmm0, xmm1
006a3c4a jbe 0x6a3c97
006a3c4c movss xmm0, dword ptr [esi + 0x294]
006a3c54 lea eax, [ebp - 0x108]
006a3c5a movss xmm1, dword ptr [esi + 0x298]
006a3c62 lea ecx, [ebp - 0x100]
006a3c68 subss xmm0, dword ptr [edi + 0x294]
006a3c70 subss xmm1, dword ptr [edi + 0x298]
006a3c78 push eax
006a3c79 movss dword ptr [ebp - 0x100], xmm0
006a3c81 movss dword ptr [ebp - 0xfc], xmm1
006a3c89 call 0x962560
006a3c8e movss xmm4, dword ptr [eax]
006a3c92 movss xmm5, dword ptr [eax + 4]
006a3c97 lea ecx, [ebp - 0xe4]
006a3c9d call 0x430d70
006a3ca2 movss xmm2, dword ptr [esi + 0x370]
006a3caa mov ecx, 1
006a3caf movss xmm1, dword ptr [0xb6a274]
006a3cb7 mov eax, 0xb46a30
006a3cbc nop dword ptr [eax]
006a3cc0 movss xmm0, dword ptr [eax]
006a3cc4 addss xmm0, xmm1
006a3cc8 comiss xmm2, xmm0
006a3ccb jbe 0x6a3cd8
006a3ccd add eax, 4
006a3cd0 inc ecx
006a3cd1 cmp eax, 0xb46a60
006a3cd6 jl 0x6a3cc0
006a3cd8 mov eax, 0xd
006a3cdd movss xmm3, dword ptr [esi + 0x2b8]
006a3ce5 cmp ecx, eax
006a3ce7 movss xmm2, dword ptr [esi + 0x2bc]
006a3cef movaps xmm0, xmm5
006a3cf2 cmovl eax, ecx
006a3cf5 mulss xmm0, xmm2
006a3cf9 mov ecx, edi
006a3cfb movd xmm1, eax
006a3cff lea eax, [ebp - 0xe4]
006a3d05 cvtdq2ps xmm1, xmm1
006a3d08 push eax
006a3d09 push 0
006a3d0b lea eax, [ebp - 0x100]
006a3d11 push eax
006a3d12 lea eax, [edi + 0x294]
006a3d18 subss xmm1, dword ptr [0xb6a864]
006a3d20 push eax
006a3d21 divss xmm1, dword ptr [0xb6a864]
006a3d29 movss dword ptr [ebp - 0xd0], xmm1
006a3d31 movaps xmm1, xmm4
006a3d34 mulss xmm1, xmm3
006a3d38 addss xmm1, xmm0
006a3d3c addss xmm1, xmm1
006a3d40 mulss xmm4, xmm1
006a3d44 mulss xmm5, xmm1
006a3d48 subss xmm3, xmm4
006a3d4c subss xmm2, xmm5
006a3d50 movss dword ptr [ebp - 0x100], xmm3
006a3d58 movss dword ptr [ebp - 0xfc], xmm2
006a3d60 call 0x6a1a20
006a3d65 mov dword ptr [ebp - 4], 0xffffffff
006a3d6c mov eax, dword ptr [ebp - 0x14]
006a3d6f cmp eax, 0x10
006a3d72 jb 0x6a3da4
006a3d74 mov ecx, dword ptr [ebp - 0x28]
006a3d77 lea edx, [eax + 1]
006a3d7a mov eax, ecx
006a3d7c cmp edx, 0x1000
006a3d82 jb 0x6a3d9a
006a3d84 mov ecx, dword ptr [ecx - 4]
006a3d87 add edx, 0x23
006a3d8a sub eax, ecx
006a3d8c add eax, -4
006a3d8f cmp eax, 0x1f
006a3d92 jbe 0x6a3d9a
006a3d94 call dword ptr [0xa065ac]
006a3d9a push edx
006a3d9b push ecx
006a3d9c call 0x9eb08e
006a3da1 add esp, 8
006a3da4 mov ecx, dword ptr [esi + 0x28]
006a3da7 mov dword ptr [ebp - 0xf0], ecx
006a3dad cmp ecx, 1
006a3db0 jne 0x6a3e82
006a3db6 cmp dword ptr [edi + 0x28], 0x3c5
006a3dbd jne 0x6a3e7c
006a3dc3 cmp dword ptr [edi + 0x2c], 0xa
006a3dc7 jne 0x6a3e7c
006a3dcd mov ecx, dword ptr [0xbfd65c]
006a3dd3 lea eax, [edi + 0x28c]
006a3dd9 push eax
006a3dda mov ecx, dword ptr [ecx + 0x18190]
006a3de0 call 0x7ce950
006a3de5 mov ecx, 0x724
006a3dea mov dword ptr [ebp - 0x104], eax
006a3df0 xor eax, eax
006a3df2 mov dword ptr [ebp - 0xf8], ecx
006a3df8 nop dword ptr [eax + eax]
006a3e00 inc eax
006a3e01 mov dword ptr [ebp - 0xf0], eax
006a3e07 cmp eax, 8
006a3e0a ja 0x6a3e68
006a3e0c mov eax, dword ptr [0xbfd65c]
006a3e11 mov eax, dword ptr [eax + 0x18190]
006a3e17 mov eax, dword ptr [ecx + eax]
006a3e1a mov dword ptr [ebp - 0xec], eax
006a3e20 test eax, eax
006a3e22 je 0x6a3e62
006a3e24 mov ecx, eax
006a3e26 call 0x6dfe30
006a3e2b test al, al
006a3e2d je 0x6a3e5c
006a3e2f mov ecx, dword ptr [ebp - 0xec]
006a3e35 mov eax, dword ptr [0xbfd65c]
006a3e3a push dword ptr [ecx + 0x24]
006a3e3d mov ecx, dword ptr [eax + 0x18190]
006a3e43 push dword ptr [ebp - 0x104]
006a3e49 add ecx, 0x734c
006a3e4f call 0x938de0
006a3e54 test al, al
006a3e56 jne 0x6a409a
006a3e5c mov ecx, dword ptr [ebp - 0xf8]
006a3e62 mov eax, dword ptr [ebp - 0xf0]
006a3e68 add ecx, 4
006a3e6b mov dword ptr [ebp - 0xf8], ecx
006a3e71 cmp ecx, 0x744
006a3e77 jb 0x6a3e00
006a3e79 mov ecx, dword ptr [esi + 0x28]
006a3e7c mov dword ptr [ebp - 0xf0], ecx
006a3e82 lea eax, [ecx - 0xa]
006a3e85 cmp eax, 0x3dd
006a3e8a ja 0x6a3ee5
006a3e8c mov ecx, dword ptr [edi + 0x164]
006a3e92 xor eax, eax
006a3e94 and ecx, 0x80000
006a3e9a or eax, ecx
006a3e9c jne 0x6a3eaf
006a3e9e push 0x80000
006a3ea3 push eax
006a3ea4 mov ecx, esi
006a3ea6 call 0x4122f0
006a3eab test al, al
006a3ead je 0x6a3edf
006a3eaf mov ecx, edi
006a3eb1 call 0x681360
006a3eb6 mov ecx, dword ptr [ebp - 0x118]
006a3ebc mov esi, eax
006a3ebe call 0x681360
006a3ec3 mov ecx, dword ptr [ebp - 0x114]
006a3ec9 xor edx, edx
006a3ecb cmp eax, esi
006a3ecd movzx ecx, cl
006a3ed0 mov esi, dword ptr [ebp - 0x118]
006a3ed6 cmovne ecx, edx
006a3ed9 mov dword ptr [ebp - 0x114], ecx
006a3edf mov ecx, dword ptr [ebp - 0xf0]
006a3ee5 cmp dword ptr [edi + 0x28], 0x3c5
006a3eec je 0x6a3ef7
006a3eee cmp dword ptr [edi + 0x32c], 0
006a3ef5 je 0x6a3f10
006a3ef7 cmp ecx, 0x3c5
006a3efd je 0x6a46d7
006a3f03 cmp dword ptr [esi + 0x32c], 0
006a3f0a jne 0x6a46d7
006a3f10 test byte ptr [edi + 0xe68], 4
006a3f17 je 0x6a3f61
006a3f19 mov eax, dword ptr [ebp + 0xc]
006a3f1c mov ecx, edi
006a3f1e mov dword ptr [edi + 0xacc], esi
006a3f24 mov byte ptr [edi + 0xac8], al
006a3f2a mov dword ptr [edi + 0xad0], 0xffffffff
006a3f34 mov dword ptr [edi + 0xac4], 3
006a3f3e call 0x699730
006a3f43 mov eax, dword ptr [edi + 0xad0]
006a3f49 mov dword ptr [edi + 0xac4], 0
006a3f53 test eax, eax
006a3f55 jg 0x6a41dc
006a3f5b je 0x6a5c9a
006a3f61 cmp dword ptr [edi + 0x28], 0x355
006a3f68 movss xmm1, dword ptr [0xb6a480]
006a3f70 jne 0x6a402f
006a3f76 cmp dword ptr [edi + 0xb10], 2
006a3f7d jne 0x6a402f
006a3f83 mov eax, dword ptr [esi + 0x28]
006a3f86 cmp eax, 4
006a3f89 je 0x6a46d7
006a3f8f cmp eax, 2
006a3f92 je 0x6a46d7
006a3f98 cmp eax, 9
006a3f9b je 0x6a46d7
006a3fa1 mov dword ptr [edi + 0xb10], 1
006a3fab cmp dword ptr [edi + 0xbc], 0
006a3fb2 jg 0x6a3fda
006a3fb4 cmp dword ptr [edi + 0x50], 0x10
006a3fb8 lea ecx, [edi + 0x3c]
006a3fbb jb 0x6a3fc0
006a3fbd mov ecx, dword ptr [edi + 0x3c]
006a3fc0 push 0
006a3fc2 push ecx
006a3fc3 push 0xa0830c
006a3fc8 push 3
006a3fca call 0x95e330
006a3fcf movss xmm1, dword ptr [0xb6a480]
006a3fd7 add esp, 0x10
006a3fda lea ecx, [ebp - 0x3c]
006a3fdd call 0x402120
006a3fe2 mov ecx, dword ptr [edi + 0xb8]
006a3fe8 push eax
006a3fe9 add ecx, 0x48
006a3fec call 0x4021a0
006a3ff1 movss xmm0, dword ptr [edi + 0x2b8]
006a3ff9 mulss xmm0, xmm1
006a3ffd movss dword ptr [edi + 0x2b8], xmm0
006a4005 movss xmm0, dword ptr [edi + 0x2bc]
006a400d mulss xmm0, xmm1
006a4011 movss dword ptr [edi + 0x2bc], xmm0
006a4019 mov eax, dword ptr [edi + 0x164]
006a401f and dword ptr [edi + 0x160], 0xfbffffff
006a4029 mov dword ptr [edi + 0x164], eax
006a402f mov eax, dword ptr [edi + 0x28]
006a4032 cmp eax, 0x397
006a4037 jne 0x6a416f
006a403d cmp dword ptr [esi + 0x28], 0x21
006a4041 je 0x6a46d7
006a4047 mov eax, dword ptr [edi + 0x28]
006a404a cmp eax, 0x21
006a404d jne 0x6a41e3
006a4053 cmp dword ptr [edi + 0x2c], 0xb
006a4057 jne 0x6a43a5
006a405d mov ecx, dword ptr [esi + 0x28]
006a4060 lea eax, [ecx - 0xa]
006a4063 cmp eax, 0x3dd
006a4068 ja 0x6a4211
006a406e cmp ecx, 0x21
006a4071 jne 0x6a407d
006a4073 cmp dword ptr [esi + 0x2c], 0xb
006a4077 je 0x6a4211
006a407d mov ecx, edi
006a407f call 0x448100
006a4084 mov ecx, esi
006a4086 mov dl, al
006a4088 call 0x448100
006a408d cmp al, dl
006a408f jne 0x6a4211
006a4095 jmp 0x6a46d7
006a409a mov eax, dword ptr [ebp - 0xec]
006a40a0 push -1
006a40a2 mov ecx, dword ptr [eax + 0x27c]
006a40a8 cmp ecx, -0x64
006a40ab jg 0x6a40cf
006a40ad push ecx
006a40ae mov ecx, dword ptr [0xbfd65c]
006a40b4 call 0x70e0f0
006a40b9 mov ecx, dword ptr [ebp - 0xec]
006a40bf push dword ptr [eax + 0xc]
006a40c2 push esi
006a40c3 push 0x13
006a40c5 push dword ptr [ecx + 0x160]
006a40cb push dword ptr [eax]
006a40cd jmp 0x6a40d9
006a40cf push esi
006a40d0 push 0x13
006a40d2 push dword ptr [eax + 0x160]
006a40d8 push ecx
006a40d9 mov ecx, dword ptr [0xbfd65c]
006a40df call 0x6d07d0
006a40e4 mov edx, dword ptr [0xbfd65c]
006a40ea mov ecx, dword ptr [edx + 0x1ba04]
006a40f0 lea eax, [edx + 0x1ba04]
006a40f6 mov dword ptr [ebp - 0x104], eax
006a40fc cmp ecx, edi
006a40fe je 0x6a4132
006a4100 test ecx, ecx
006a4102 je 0x6a4122
006a4104 mov dword ptr [ebp - 0x118], eax
006a410a add ecx, 0x324
006a4110 lea eax, [ebp - 0x118]
006a4116 push eax
006a4117 call 0x4bc3c0
006a411c mov eax, dword ptr [ebp - 0x104]
006a4122 push eax
006a4123 mov ecx, edi
006a4125 mov dword ptr [eax], edi
006a4127 call 0x4bae70
006a412c mov edx, dword ptr [0xbfd65c]
006a4132 mov eax, dword ptr [edx + 0x18190]
006a4138 mov ecx, esi
006a413a push 0xb4925c
006a413f mov eax, dword ptr [eax + 4]
006a4142 or dword ptr [eax + 0x44], 4
006a4146 call 0x770e50
006a414b mov eax, dword ptr [edi + 0x28c]
006a4151 mov dword ptr [esi + 0x1a3c], eax
006a4157 mov eax, dword ptr [edi + 0x290]
006a415d mov dword ptr [esi + 0x1a40], eax
006a4163 mov byte ptr [esi + 0x360], 0
006a416a jmp 0x6a46d7
006a416f cmp eax, 0x21
006a4172 jne 0x6a4186
006a4174 cmp dword ptr [esi + 0x28], 0x397
006a417b jne 0x6a4047
006a4181 jmp 0x6a46d7
006a4186 cmp eax, 0x332
006a418b jne 0x6a4047
006a4191 cmp dword ptr [edi + 0x2c], 0
006a4195 je 0x6a41a1
006a4197 cmp dword ptr [edi + 0x2c], 1
006a419b jne 0x6a4047
006a41a1 cmp dword ptr [esi + 0x28], 1
006a41a5 jne 0x6a4047
006a41ab mov ecx, esi
006a41ad call 0x786ca0
006a41b2 test al, al
006a41b4 je 0x6a4047
006a41ba push esi
006a41bb lea ecx, [ebp - 0x38]
006a41be call 0x4229a0
006a41c3 mov eax, dword ptr [edi]
006a41c5 lea ecx, [ebp - 0x38]
006a41c8 push 0x1e
006a41ca push ecx
006a41cb push 0
006a41cd push 0
006a41cf push ecx
006a41d0 mov ecx, edi
006a41d2 mov dword ptr [esp], 0x42c80000
006a41d9 call dword ptr [eax + 0x20]
006a41dc xor al, al
006a41de jmp 0x6a46d9
006a41e3 cmp eax, 0x332
006a41e8 jne 0x6a420c
006a41ea cmp dword ptr [edi + 0x2c], 0
006a41ee jne 0x6a421b
006a41f0 cmp dword ptr [esi + 0x28], 0x21
006a41f4 jne 0x6a421b
006a41f6 push -1
006a41f8 push dword ptr [edi + 0x30]
006a41fb mov ecx, edi
006a41fd push 2
006a41ff push eax
006a4200 call 0x697c60
006a4205 xor al, al
006a4207 jmp 0x6a46d9
006a420c cmp eax, 0x21
006a420f jne 0x6a4248
006a4211 cmp dword ptr [edi + 0x2c], 0xb
006a4215 jne 0x6a43a5
006a421b mov eax, dword ptr [esi + 0x28]
006a421e cmp eax, 0x332
006a4223 je 0x6a4230
006a4225 cmp eax, 0x21
006a4228 jne 0x6a4248
006a422a cmp dword ptr [esi + 0x2c], 0xb
006a422e jne 0x6a4248
006a4230 mov ecx, edi
006a4232 call 0x448100
006a4237 mov ecx, esi
006a4239 mov dl, al
006a423b call 0x448100
006a4240 cmp al, dl
006a4242 je 0x6a46d7
006a4248 mov eax, dword ptr [edi + 0x28]
006a424b cmp eax, 0x333
006a4250 jne 0x6a4333
006a4256 cmp dword ptr [esi + 0x28], 1
006a425a jne 0x6a426e
006a425c push 0
006a425e push 0x20000000
006a4263 mov ecx, edi
006a4265 call 0x4122f0
006a426a test al, al
006a426c je 0x6a42c7
006a426e cmp esi, dword ptr [edi + 0x31c]
006a4274 je 0x6a42c7
006a4276 push 0
006a4278 push 0x20000000
006a427d mov ecx, edi
006a427f call 0x4122f0
006a4284 test al, al
006a4286 mov eax, dword ptr [esi + 0x28]
006a4289 je 0x6a42ac
006a428b cmp eax, 0xa
006a428e jl 0x6a42ac
006a4290 cmp eax, 0x3e8
006a4295 jge 0x6a42ac
006a4297 push 0
006a4299 push 0x20000000
006a429e mov ecx, esi
006a42a0 call 0x4122f0
006a42a5 test al, al
006a42a7 je 0x6a42c7
006a42a9 mov eax, dword ptr [esi + 0x28]
006a42ac cmp eax, 0x335
006a42b1 je 0x6a46d7
006a42b7 cmp eax, 0x38a
006a42bc jne 0x6a43a5
006a42c2 jmp 0x6a46d7
006a42c7 movups xmm0, xmmword ptr [0xbfec58]
006a42ce mov ecx, dword ptr [0xbfd65c]
006a42d4 lea esi, [edi + 0x294]
006a42da push 0
006a42dc push 0
006a42de push 4
006a42e0 sub esp, 0x10
006a42e3 mov eax, esp
006a42e5 push edi
006a42e6 push 1
006a42e8 sub esp, 8
006a42eb movups xmmword ptr [eax], xmm0
006a42ee mov dword ptr [esp + 4], 0x42700000
006a42f6 mov dword ptr [esp], 0x42200000
006a42fd push esi
006a42fe call 0x6d1750
006a4303 call 0x6c3d90
006a4308 mov ecx, dword ptr [0xbfd65c]
006a430e push eax
006a430f push 0
006a4311 push 0
006a4313 push 0xc02fec
006a4318 push esi
006a4319 push 1
006a431b push 0x3e8
006a4320 call 0x422e20
006a4325 mov eax, dword ptr [edi]
006a4327 mov ecx, edi
006a4329 call dword ptr [eax + 0x28]
006a432c xor al, al
006a432e jmp 0x6a46d9
006a4333 cmp eax, 0x13
006a4336 jne 0x6a434c
006a4338 cmp dword ptr [edi + 0x2c], 3
006a433c jne 0x6a43a5
006a433e cmp dword ptr [esi + 0x28], 0x329
006a4345 jne 0x6a43a5
006a4347 jmp 0x6a46d7
006a434c cmp eax, 0x396
006a4351 jne 0x6a43a5
006a4353 cmp dword ptr [edi + 0xab4], 6
006a435a jne 0x6a43a5
006a435c mov eax, dword ptr [esi + 0x28]
006a435f cmp eax, 0xd9
006a4364 je 0x6a436d
006a4366 cmp eax, 0x366
006a436b jne 0x6a43a5
006a436d mov eax, dword ptr [0xbfd65c]
006a4372 mov eax, dword ptr [eax + 0x1a30dc]
006a4378 sub eax, dword ptr [esi + 0x280]
006a437e cmp eax, 8
006a4381 jle 0x6a43a5
006a4383 push edi
006a4384 lea ecx, [ebp - 0x38]
006a4387 call 0x4229a0
006a438c mov eax, dword ptr [esi]
006a438e lea ecx, [ebp - 0x38]
006a4391 push 0x1e
006a4393 push ecx
006a4394 push 0
006a4396 push 0
006a4398 push ecx
006a4399 mov ecx, esi
006a439b mov dword ptr [esp], 0x41200000
006a43a2 call dword ptr [eax + 0x20]
006a43a5 mov eax, dword ptr [edi + 0x28]
006a43a8 cmp eax, 0x336
006a43ad jne 0x6a43d0
006a43af cmp dword ptr [edi + 0xab4], 0x10
006a43b6 jne 0x6a43f1
006a43b8 cmp dword ptr [esi + 0x28], 1
006a43bc je 0x6a43c6
006a43be cmp esi, dword ptr [edi + 0x31c]
006a43c4 jne 0x6a43f1
006a43c6 mov eax, dword ptr [edi]
006a43c8 mov ecx, edi
006a43ca call dword ptr [eax + 0x24]
006a43cd mov eax, dword ptr [edi + 0x28]
006a43d0 cmp eax, 0x38a
006a43d5 jne 0x6a445b
006a43db cmp dword ptr [edi + 0x2c], 1
006a43df jne 0x6a43f1
006a43e1 cmp dword ptr [esi + 0x28], 1
006a43e5 jne 0x6a43f8
006a43e7 mov eax, dword ptr [edi]
006a43e9 mov ecx, edi
006a43eb call dword ptr [eax + 0x24]
006a43ee mov eax, dword ptr [edi + 0x28]
006a43f1 cmp eax, 0x38a
006a43f6 jne 0x6a445b
006a43f8 mov eax, dword ptr [edi + 0x32c]
006a43fe test eax, eax
006a4400 je 0x6a445b
006a4402 movss xmm0, dword ptr [eax + 0xb08]
006a440a comiss xmm0, dword ptr [0xb6a974]
006a4411 jbe 0x6a445b
006a4413 mov eax, dword ptr [esi + 0x28]
006a4416 lea ecx, [ebp - 0x38]
006a4419 sub eax, 0xa
006a441c push edi
006a441d cmp eax, 0x3dd
006a4422 ja 0x6a443d
006a4424 call 0x4229a0
006a4429 push 0x1e
006a442b lea ecx, [ebp - 0x38]
006a442e push ecx
006a442f push 0
006a4431 push 0
006a4433 push ecx
006a4434 mov dword ptr [esp], 0x41c80000
006a443b jmp 0x6a4454
006a443d call 0x4229a0
006a4442 push 0x1e
006a4444 lea ecx, [ebp - 0x38]
006a4447 push ecx
006a4448 push 0
006a444a push 0
006a444c push ecx
006a444d mov dword ptr [esp], 0x3f800000
006a4454 mov eax, dword ptr [esi]
006a4456 mov ecx, esi
006a4458 call dword ptr [eax + 0x20]
006a445b mov eax, dword ptr [edi + 0x28]
006a445e cmp eax, 0x393
006a4463 jne 0x6a446b
006a4465 cmp dword ptr [edi + 0x2c], 1
006a4469 jmp 0x6a4470
006a446b cmp eax, 0x37d
006a4470 jne 0x6a44f8
006a4476 push 0
006a4478 mov ecx, esi
006a447a mov dword ptr [ebp - 0x104], eax
006a4480 call 0x684630
006a4485 test al, al
006a4487 je 0x6a4516
006a448d movss xmm1, dword ptr [edi + 0x2bc]
006a4495 movss xmm0, dword ptr [edi + 0x2b8]
006a449d mulss xmm0, xmm0
006a44a1 mulss xmm1, xmm1
006a44a5 addss xmm0, xmm1
006a44a9 call 0x4228c0
006a44ae comiss xmm0, dword ptr [0xb6a974]
006a44b5 jbe 0x6a44f5
006a44b7 lea ecx, [edi + 0xe50]
006a44bd push esi
006a44be call 0x422d00
006a44c3 test al, al
006a44c5 jne 0x6a44f5
006a44c7 push esi
006a44c8 lea ecx, [edi + 0xe50]
006a44ce call 0x422ce0
006a44d3 push edi
006a44d4 lea ecx, [ebp - 0x38]
006a44d7 call 0x4229a0
006a44dc mov eax, dword ptr [esi]
006a44de lea ecx, [ebp - 0x38]
006a44e1 push 0x1e
006a44e3 push ecx
006a44e4 push 0
006a44e6 push 0
006a44e8 push ecx
006a44e9 mov ecx, esi
006a44eb mov dword ptr [esp], 0x41c80000
006a44f2 call dword ptr [eax + 0x20]
006a44f5 mov eax, dword ptr [edi + 0x28]
006a44f8 cmp eax, 0x387
006a44fd jne 0x6a4531
006a44ff push ecx
006a4500 push esi
006a4501 mov ecx, edi
006a4503 call 0x59c750
006a4508 cmp al, 0xff
006a450a je 0x6a451e
006a450c test al, al
006a450e setne al
006a4511 jmp 0x6a46d9
006a4516 mov eax, dword ptr [ebp - 0x104]
006a451c jmp 0x6a44f8
006a451e cmp dword ptr [esi + 0x28], 0x387
006a4525 jne 0x6a4531
006a4527 cmp dword ptr [edi + 0x2c], 0xa
006a452b je 0x6a46d7
006a4531 mov ecx, dword ptr [edi + 0x28]
006a4534 mov eax, ecx
006a4536 mov dword ptr [ebp - 0xe8], ecx
006a453c cmp ecx, 0x390
006a4542 jne 0x6a4552
006a4544 cmp dword ptr [esi + 0x28], ecx
006a4547 jne 0x6a463c
006a454d jmp 0x6a46d7
006a4552 cmp ecx, 0x3b7
006a4558 jne 0x6a45ca
006a455a cmp dword ptr [esi + 0x28], ecx
006a455d jne 0x6a463c
006a4563 cmp dword ptr [edi + 0x2c], 0xa
006a4567 jne 0x6a46d7
006a456d mov eax, dword ptr [esi]
006a456f mov ecx, esi
006a4571 mov eax, dword ptr [eax + 0x48]
006a4574 call eax
006a4576 test al, al
006a4578 jne 0x6a46d7
006a457e movss xmm1, dword ptr [edi + 0x2bc]
006a4586 movss xmm0, dword ptr [edi + 0x2b8]
006a458e mulss xmm0, xmm0
006a4592 mulss xmm1, xmm1
006a4596 addss xmm0, xmm1
006a459a comiss xmm0, dword ptr [0xb6abcc]
006a45a1 jbe 0x6a46d7
006a45a7 mov edx, dword ptr [esi]
006a45a9 lea ecx, [ebp - 0x38]
006a45ac push 0x1e
006a45ae call 0x427290
006a45b3 push eax
006a45b4 push 0
006a45b6 push 0
006a45b8 push ecx
006a45b9 mov ecx, esi
006a45bb mov dword ptr [esp], 0x43480000
006a45c2 call dword ptr [edx + 0x20]
006a45c5 jmp 0x6a46d7
006a45ca cmp ecx, 0x19
006a45cd jne 0x6a45ec
006a45cf cmp dword ptr [edi + 0xab4], 5
006a45d6 jne 0x6a463c
006a45d8 cmp dword ptr [esi + 0x28], 1
006a45dc jne 0x6a463c
006a45de mov eax, dword ptr [edi]
006a45e0 mov ecx, edi
006a45e2 call dword ptr [eax + 0x24]
006a45e5 xor al, al
006a45e7 jmp 0x6a46d9
006a45ec cmp ecx, 0x38e
006a45f2 jne 0x6a463c
006a45f4 cmp dword ptr [esi + 0x28], 0x355
006a45fb jne 0x6a46bd
006a4601 mov dword ptr [ebp - 0x104], ecx
006a4607 mov ecx, esi
006a4609 push 0
006a460b call 0x684630
006a4610 test al, al
006a4612 je 0x6a4636
006a4614 movss xmm0, dword ptr [esi + 0x2a8]
006a461c xorps xmm1, xmm1
006a461f comiss xmm0, xmm1
006a4622 mov eax, dword ptr [ebp - 0xe8]
006a4628 jb 0x6a463c
006a462a mov eax, dword ptr [esi]
006a462c mov ecx, esi
006a462e call dword ptr [eax + 0x24]
006a4631 mov eax, dword ptr [edi + 0x28]
006a4634 jmp 0x6a463c
006a4636 mov eax, dword ptr [ebp - 0x104]
006a463c mov ecx, eax
006a463e mov dword ptr [ebp - 0xe8], ecx
006a4644 cmp ecx, 0x38d
006a464a jne 0x6a46bd
006a464c cmp dword ptr [esi + 0x28], eax
006a464f je 0x6a46d7
006a4655 cmp dword ptr [edi + 0x2c], 0xa
006a4659 jne 0x6a46bd
006a465b cmp dword ptr [edi + 0x30], 0
006a465f jbe 0x6a46fc
006a4665 push 0
006a4667 mov ecx, esi
006a4669 call 0x684630
006a466e test al, al
006a4670 je 0x6a46f6
006a4676 movss xmm0, dword ptr [esi + 0x2fc]
006a467e comiss xmm0, dword ptr [0xb6aa8c]
006a4685 jbe 0x6a46f6
006a4687 cmp dword ptr [esi + 0x28], 0x355
006a468e jne 0x6a4699
006a4690 mov eax, dword ptr [esi]
006a4692 mov ecx, esi
006a4694 call dword ptr [eax + 0x24]
006a4697 jmp 0x6a46d7
006a4699 push edi
006a469a lea ecx, [ebp - 0x38]
006a469d call 0x4229a0
006a46a2 mov eax, dword ptr [esi]
006a46a4 lea ecx, [ebp - 0x38]
006a46a7 push 0x1e
006a46a9 push ecx
006a46aa push 0
006a46ac push 0
006a46ae push ecx
006a46af mov ecx, esi
006a46b1 mov dword ptr [esp], 0x40a00000
006a46b8 call dword ptr [eax + 0x20]
006a46bb jmp 0x6a46d7
006a46bd cmp ecx, 0x333
006a46c3 jne 0x6a46fc
006a46c5 cmp dword ptr [edi + 0x2c], 1
006a46c9 jne 0x6a46fc
006a46cb cmp esi, dword ptr [edi + 0x314]
006a46d1 jne 0x6a4884
006a46d7 mov al, 1
006a46d9 mov ecx, dword ptr [ebp - 0xc]
006a46dc mov dword ptr fs:[0], ecx
006a46e3 pop ecx
006a46e4 pop edi
006a46e5 pop esi
006a46e6 mov ecx, dword ptr [ebp - 0x10]
006a46e9 xor ecx, ebp
006a46eb call 0x9eacd7
006a46f0 mov esp, ebp
006a46f2 pop ebp
006a46f3 ret 8
006a46f6 mov ecx, dword ptr [ebp - 0xe8]
006a46fc cmp ecx, 0x37d
006a4702 jne 0x6a4725
006a4704 push 0xc02fec
006a4709 lea ecx, [edi + 0x28c]
006a470f call 0x962ca0
006a4714 test al, al
006a4716 je 0x6a4884
006a471c cmp dword ptr [esi + 0x28], 0x37d
006a4723 jmp 0x6a46d1
006a4725 cmp ecx, 0x32f
006a472b jne 0x6a486f
006a4731 cmp dword ptr [esi + 0x28], ecx
006a4734 jne 0x6a4884
006a473a cmp byte ptr [ebp + 0xc], 0
006a473e je 0x6a46d7
006a4740 movss xmm1, dword ptr [edi + 0x2b8]
006a4748 lea eax, [ebp - 0x100]
006a474e movss xmm0, dword ptr [edi + 0x294]
006a4756 lea ecx, [ebp - 0x110]
006a475c movss xmm2, dword ptr [edi + 0x2bc]
006a4764 subss xmm0, xmm1
006a4768 push eax
006a4769 movss dword ptr [ebp - 0x104], xmm1
006a4771 movss dword ptr [ebp - 0x118], xmm2
006a4779 subss xmm0, dword ptr [esi + 0x294]
006a4781 addss xmm0, dword ptr [esi + 0x2b8]
006a4789 movss dword ptr [ebp - 0x110], xmm0
006a4791 movss xmm0, dword ptr [edi + 0x298]
006a4799 subss xmm0, xmm2
006a479d subss xmm0, dword ptr [esi + 0x298]
006a47a5 addss xmm0, dword ptr [esi + 0x2bc]
006a47ad movss dword ptr [ebp - 0x10c], xmm0
006a47b5 call 0x962560
006a47ba movss xmm3, dword ptr [ebp - 0x118]
006a47c2 movss xmm5, dword ptr [ebp - 0x100]
006a47ca movaps xmm1, xmm3
006a47cd movss xmm4, dword ptr [ebp - 0xfc]
006a47d5 movaps xmm0, xmm5
006a47d8 movss xmm2, dword ptr [ebp - 0x104]
006a47e0 movaps xmm6, xmm5
006a47e3 mulss xmm6, dword ptr [0xb6a7b0]
006a47eb movaps xmm7, xmm4
006a47ee mulss xmm7, dword ptr [0xb6a7b0]
006a47f6 mulss xmm0, xmm2
006a47fa mulss xmm1, xmm4
006a47fe addss xmm1, xmm0
006a4802 movaps xmm0, xmm6
006a4805 mulss xmm0, xmm1
006a4809 subss xmm2, xmm0
006a480d movaps xmm0, xmm7
006a4810 mulss xmm0, xmm1
006a4814 subss xmm3, xmm0
006a4818 movss dword ptr [edi + 0x2b8], xmm2
006a4820 movss dword ptr [edi + 0x2bc], xmm3
006a4828 movss xmm2, dword ptr [esi + 0x2bc]
006a4830 movss xmm3, dword ptr [esi + 0x2b8]
006a4838 movaps xmm1, xmm2
006a483b mulss xmm1, xmm4
006a483f mulss xmm5, xmm3
006a4843 addss xmm1, xmm5
006a4847 movaps xmm0, xmm1
006a484a mulss xmm1, xmm7
006a484e mulss xmm0, xmm6
006a4852 subss xmm2, xmm1
006a4856 subss xmm3, xmm0
006a485a movss dword ptr [esi + 0x2bc], xmm2
006a4862 movss dword ptr [esi + 0x2b8], xmm3
006a486a jmp 0x6a46d7
006a486f cmp ecx, 0x390
006a4875 jne 0x6a4884
006a4877 cmp dword ptr [esi + 0x28], 0x355
006a487e je 0x6a4690
006a4884 mov ecx, dword ptr [esi + 0x2c]
006a4887 mov eax, dword ptr [esi + 0x28]
006a488a mov edx, dword ptr [edi + 0x2c]
006a488d mov dword ptr [ebp - 0xf0], ecx
006a4893 mov ecx, dword ptr [ebp - 0xe8]
006a4899 mov dword ptr [ebp - 0xec], eax
006a489f mov dword ptr [ebp - 0x124], edx
006a48a5 cmp ecx, 0x3c4
006a48ab jne 0x6a48df
006a48ad cmp eax, 1
006a48b0 jne 0x6a48ff
006a48b2 mov dword ptr [edi + 0xb00], 0
006a48bc cmp ecx, 0x355
006a48c2 jne 0x6a4955
006a48c8 cmp dword ptr [esi + 0x28], ecx
006a48cb je 0x6a5c9a
006a48d1 cmp esi, dword ptr [edi + 0x320]
006a48d7 je 0x6a5c9a
006a48dd jmp 0x6a4955
006a48df cmp ecx, 0x19c
006a48e5 jne 0x6a48ff
006a48e7 mov ecx, dword ptr [edi + 0xb18]
006a48ed mov edx, dword ptr [edi + 0xb1c]
006a48f3 mov dword ptr [ebp - 0xe8], ecx
006a48f9 mov dword ptr [ebp - 0x124], edx
006a48ff cmp eax, 0x19c
006a4904 jne 0x6a491e
006a4906 mov eax, dword ptr [esi + 0xb18]
006a490c mov dword ptr [ebp - 0xec], eax
006a4912 mov eax, dword ptr [esi + 0xb1c]
006a4918 mov dword ptr [ebp - 0xf0], eax
006a491e cmp ecx, 0x27
006a4921 jne 0x6a49d2
006a4927 cmp edx, 0x16
006a492a jne 0x6a4955
006a492c push 0
006a492e mov ecx, esi
006a4930 call 0x68cf40
006a4935 test al, al
006a4937 je 0x6a494f
006a4939 push 0
006a493b push 0x20000000
006a4940 mov ecx, edi
006a4942 call 0x4122f0
006a4947 test al, al
006a4949 je 0x6a5c9a
006a494f mov ecx, dword ptr [ebp - 0xe8]
006a4955 cmp dword ptr [edi + 0x34], 0x369
006a495c jne 0x6a4978
006a495e cmp dword ptr [edi + 0x314], 0
006a4965 je 0x6a4978
006a4967 mov eax, dword ptr [esi + 0x28]
006a496a sub eax, 0xa
006a496d cmp eax, 0x3dd
006a4972 jbe 0x6a5c9a
006a4978 cmp dword ptr [esi + 0x28], 1
006a497c jne 0x6a4bef
006a4982 cmp ecx, 0x124
006a4988 je 0x6a4996
006a498a cmp ecx, 0xf5
006a4990 jne 0x6a4bef
006a4996 mov ecx, esi
006a4998 call 0x786ca0
006a499d test al, al
006a499f je 0x6a4bef
006a49a5 push esi
006a49a6 lea ecx, [ebp - 0x38]
006a49a9 call 0x4229a0
006a49ae mov eax, dword ptr [edi]
006a49b0 lea ecx, [ebp - 0x38]
006a49b3 push 0x1e
006a49b5 push ecx
006a49b6 push 0
006a49b8 push 4
006a49ba push ecx
006a49bb mov ecx, edi
006a49bd mov dword ptr [esp], 0x41200000
006a49c4 call dword ptr [eax + 0x20]
006a49c7 mov al, byte ptr [ebp - 0x114]
006a49cd jmp 0x6a46d9
006a49d2 cmp ecx, 0x124
006a49d8 jne 0x6a4a06
006a49da cmp dword ptr [esi + 0x28], 1
006a49de jne 0x6a4955
006a49e4 cmp dword ptr [edi + 0xb10], -4
006a49eb jle 0x6a4955
006a49f1 mov al, byte ptr [ebp - 0x114]
006a49f7 mov dword ptr [edi + 0xb10], 0
006a4a01 jmp 0x6a46d9
006a4a06 cmp ecx, 0x21
006a4a09 jne 0x6a4aa4
006a4a0f cmp edx, 0xa
006a4a12 je 0x6a4a22
006a4a14 cmp edx, 0xc
006a4a17 je 0x6a4a22
006a4a19 cmp edx, 0xd
006a4a1c jne 0x6a4955
006a4a22 mov eax, dword ptr [esi + 0x28]
006a4a25 cmp eax, 4
006a4a28 je 0x6a46d7
006a4a2e add eax, -0xa
006a4a31 cmp eax, 0x3dd
006a4a36 ja 0x6a4955
006a4a3c push 0
006a4a3e push 0x20000000
006a4a43 mov ecx, edi
006a4a45 call 0x4122f0
006a4a4a lea ecx, [ebp - 0x38]
006a4a4d push edi
006a4a4e test al, al
006a4a50 je 0x6a4a7b
006a4a52 call 0x4229a0
006a4a57 mov eax, dword ptr [esi]
006a4a59 lea ecx, [ebp - 0x38]
006a4a5c push 0x1e
006a4a5e push ecx
006a4a5f push 0
006a4a61 push 2
006a4a63 push ecx
006a4a64 mov ecx, esi
006a4a66 mov dword ptr [esp], 0x41200000
006a4a6d call dword ptr [eax + 0x20]
006a4a70 mov al, byte ptr [ebp - 0x114]
006a4a76 jmp 0x6a46d9
006a4a7b call 0x4229a0
006a4a80 mov eax, dword ptr [esi]
006a4a82 lea ecx, [ebp - 0x38]
006a4a85 push 0x1e
006a4a87 push ecx
006a4a88 push 0
006a4a8a push 2
006a4a8c push ecx
006a4a8d mov ecx, esi
006a4a8f mov dword ptr [esp], 0
006a4a96 call dword ptr [eax + 0x20]
006a4a99 mov al, byte ptr [ebp - 0x114]
006a4a9f jmp 0x6a46d9
006a4aa4 cmp ecx, 0x328
006a4aaa jne 0x6a4b50
006a4ab0 mov eax, dword ptr [esi + 0x28]
006a4ab3 cmp eax, 1
006a4ab6 jne 0x6a4b21
006a4ab8 cmp dword ptr [edi + 0xaf0], 0
006a4abf jg 0x6a5c9a
006a4ac5 cmp dword ptr [edi + 0x30], 0
006a4ac9 jne 0x6a4955
006a4acf push 0
006a4ad1 lea eax, [ebp - 0x100]
006a4ad7 mov ecx, edi
006a4ad9 push eax
006a4ada call 0x544dc0
006a4adf movss xmm1, dword ptr [edi + 0x294]
006a4ae7 movss xmm0, dword ptr [edi + 0x298]
006a4aef subss xmm0, dword ptr [eax + 4]
006a4af4 subss xmm1, dword ptr [eax]
006a4af8 mulss xmm0, xmm0
006a4afc mulss xmm1, xmm1
006a4b00 addss xmm0, xmm1
006a4b04 call 0x4228c0
006a4b09 comiss xmm0, dword ptr [0xb6aa0c]
006a4b10 jbe 0x6a494f
006a4b16 mov al, byte ptr [ebp - 0x114]
006a4b1c jmp 0x6a46d9
006a4b21 cmp eax, 0xa
006a4b24 jl 0x6a4b3c
006a4b26 cmp eax, 0x3e8
006a4b2b jge 0x6a4955
006a4b31 mov al, byte ptr [ebp - 0x114]
006a4b37 jmp 0x6a46d9
006a4b3c cmp eax, 4
006a4b3f jne 0x6a4955
006a4b45 mov al, byte ptr [ebp - 0x114]
006a4b4b jmp 0x6a46d9
006a4b50 cmp ecx, 0x32a
006a4b56 jne 0x6a4ba5
006a4b58 mov edx, dword ptr [edi + 0x314]
006a4b5e cmp edx, esi
006a4b60 je 0x6a5c9a
006a4b66 mov eax, dword ptr [esi + 0x28]
006a4b69 cmp eax, ecx
006a4b6b jne 0x6a4b80
006a4b6d test edx, edx
006a4b6f je 0x6a4955
006a4b75 mov al, byte ptr [ebp - 0x114]
006a4b7b jmp 0x6a46d9
006a4b80 cmp eax, 2
006a4b83 jne 0x6a4955
006a4b89 cmp dword ptr [edi + 0x17c], 6
006a4b90 jne 0x6a4955
006a4b96 mov dword ptr [edi + 0xb00], 0
006a4ba0 jmp 0x6a4955
006a4ba5 cmp ecx, 0x364
006a4bab jne 0x6a4bce
006a4bad mov eax, dword ptr [esi + 0x28]
006a4bb0 cmp eax, ecx
006a4bb2 je 0x6a5c9a
006a4bb8 cmp eax, 0x358
006a4bbd jne 0x6a4955
006a4bc3 mov al, byte ptr [ebp - 0x114]
006a4bc9 jmp 0x6a46d9
006a4bce cmp ecx, 0xde
006a4bd4 jne 0x6a48bc
006a4bda cmp dword ptr [esi + 0x28], 0x16
006a4bde jne 0x6a4955
006a4be4 mov al, byte ptr [ebp - 0x114]
006a4bea jmp 0x6a46d9
006a4bef mov eax, dword ptr [ebp - 0xe8]
006a4bf5 cmp eax, 0x134
006a4bfa jne 0x6a4c44
006a4bfc mov ecx, dword ptr [esi + 0x28]
006a4bff cmp ecx, 0x19d
006a4c05 je 0x6a5c9a
006a4c0b mov eax, dword ptr [edi + 0x314]
006a4c11 cmp esi, eax
006a4c13 je 0x6a5c9a
006a4c19 cmp ecx, 0x134
006a4c1f jne 0x6a4df2
006a4c25 test eax, eax
006a4c27 je 0x6a4df2
006a4c2d cmp eax, dword ptr [esi + 0x314]
006a4c33 jne 0x6a4df2
006a4c39 mov al, byte ptr [ebp - 0x114]
006a4c3f jmp 0x6a46d9
006a4c44 cmp eax, 0x194
006a4c49 jne 0x6a4d4a
006a4c4f mov eax, dword ptr [esi + 0x28]
006a4c52 cmp eax, 0x19b
006a4c57 jne 0x6a4c6a
006a4c59 cmp dword ptr [esi + 0x2c], 0
006a4c5d je 0x6a4c7c
006a4c5f mov al, byte ptr [ebp - 0x114]
006a4c65 jmp 0x6a46d9
006a4c6a cmp eax, 4
006a4c6d jne 0x6a4c7c
006a4c6f cmp dword ptr [edi + 0x34], 0x19b
006a4c76 je 0x6a5c9a
006a4c7c cmp dword ptr [edi + 0x34], 0x19b
006a4c83 jne 0x6a4df2
006a4c89 cmp dword ptr [ebp - 0xec], 0x19b
006a4c93 jne 0x6a4df2
006a4c99 cmp dword ptr [edi + 0x360], 0x1e
006a4ca0 jle 0x6a4df2
006a4ca6 movss xmm0, dword ptr [edi + 0x294]
006a4cae lea eax, [ebp - 0x108]
006a4cb4 subss xmm0, dword ptr [esi + 0x294]
006a4cbc push eax
006a4cbd lea ecx, [ebp - 0x100]
006a4cc3 movss dword ptr [ebp - 0x100], xmm0
006a4ccb movss xmm0, dword ptr [edi + 0x298]
006a4cd3 subss xmm0, dword ptr [esi + 0x298]
006a4cdb movss dword ptr [ebp - 0xfc], xmm0
006a4ce3 call 0x962560
006a4ce8 movss xmm3, dword ptr [edi + 0x2b8]
006a4cf0 movss xmm4, dword ptr [ebp - 0x104]
006a4cf8 movaps xmm0, xmm3
006a4cfb mulss xmm0, dword ptr [ebp - 0x108]
006a4d03 movaps xmm2, xmm4
006a4d06 mulss xmm2, dword ptr [edi + 0x2bc]
006a4d0e addss xmm2, xmm0
006a4d12 addss xmm2, xmm2
006a4d16 movaps xmm0, xmm2
006a4d19 mulss xmm4, xmm2
006a4d1d mulss xmm0, dword ptr [ebp - 0x108]
006a4d25 subss xmm3, xmm0
006a4d29 movss xmm0, dword ptr [edi + 0x2bc]
006a4d31 subss xmm0, xmm4
006a4d35 movss dword ptr [edi + 0x2b8], xmm3
006a4d3d movss dword ptr [edi + 0x2bc], xmm0
006a4d45 jmp 0x6a4df2
006a4d4a cmp eax, 0x27
006a4d4d je 0x6a4d56
006a4d4f cmp eax, 0xfb
006a4d54 jne 0x6a4d8b
006a4d56 cmp dword ptr [ebp - 0xec], 0x19a
006a4d60 jne 0x6a4d8b
006a4d62 push 0xb40ed8
006a4d67 lea ecx, [esi + 0x3c]
006a4d6a call 0x405640
006a4d6f test al, al
006a4d71 je 0x6a4d85
006a4d73 mov eax, dword ptr [edi]
006a4d75 mov ecx, edi
006a4d77 call dword ptr [eax + 0x24]
006a4d7a mov al, byte ptr [ebp - 0x114]
006a4d80 jmp 0x6a46d9
006a4d85 mov eax, dword ptr [ebp - 0xe8]
006a4d8b cmp eax, 0x19a
006a4d90 jne 0x6a4df2
006a4d92 push 0xb40ed8
006a4d97 lea ecx, [edi + 0x3c]
006a4d9a call 0x405640
006a4d9f test al, al
006a4da1 je 0x6a4df2
006a4da3 cmp dword ptr [ebp - 0xec], 2
006a4daa jne 0x6a4df2
006a4dac cmp dword ptr [esi + 0x34], 1
006a4db0 jne 0x6a4df2
006a4db2 movss xmm0, dword ptr [esi + 0x2b8]
006a4dba movss xmm1, dword ptr [esi + 0x2bc]
006a4dc2 mulss xmm0, dword ptr [0xb6a3b0]
006a4dca mulss xmm1, dword ptr [0xb6a3b0]
006a4dd2 addss xmm0, dword ptr [edi + 0x2b8]
006a4dda addss xmm1, dword ptr [edi + 0x2bc]
006a4de2 movss dword ptr [edi + 0x2b8], xmm0
006a4dea movss dword ptr [edi + 0x2bc], xmm1
006a4df2 push 0
006a4df4 push 0x1000000
006a4df9 mov ecx, edi
006a4dfb call 0x4122f0
006a4e00 test al, al
006a4e02 je 0x6a4e1e
006a4e04 cmp dword ptr [ebp - 0xec], 1
006a4e0b jne 0x6a4e1e
006a4e0d mov eax, dword ptr [edi]
006a4e0f mov ecx, edi
006a4e11 mov eax, dword ptr [eax + 0x48]
006a4e14 call eax
006a4e16 test al, al
006a4e18 je 0x6a4d73
006a4e1e push 0
006a4e20 push 0x20000000
006a4e25 mov ecx, edi
006a4e27 call 0x4122f0
006a4e2c mov ecx, dword ptr [ebp - 0xec]
006a4e32 test al, al
006a4e34 je 0x6a4e71
006a4e36 cmp ecx, 1
006a4e39 je 0x6a5c9a
006a4e3f cmp ecx, 3
006a4e42 je 0x6a5c9a
006a4e48 mov eax, dword ptr [esi + 0x28]
006a4e4b sub eax, 0xa
006a4e4e cmp eax, 0x3dd
006a4e53 ja 0x6a4e71
006a4e55 push 0
006a4e57 push 0x20000000
006a4e5c mov ecx, esi
006a4e5e call 0x4122f0
006a4e63 test al, al
006a4e65 jne 0x6a5c9a
006a4e6b mov ecx, dword ptr [ebp - 0xec]
006a4e71 cmp byte ptr [ebp + 0xc], 0
006a4e75 jne 0x6a4e80
006a4e77 cmp ecx, 9
006a4e7a je 0x6a5c9a
006a4e80 mov ecx, dword ptr [0xbfd65c]
006a4e86 mov eax, dword ptr [ecx + 0x18190]
006a4e8c mov eax, dword ptr [eax + 8]
006a4e8f mov dword ptr [ebp - 0x104], eax
006a4e95 cmp eax, 0xb
006a4e98 je 0x6a4ec3
006a4e9a cmp eax, 0x11
006a4e9d je 0x6a4ec3
006a4e9f call 0x6cba40
006a4ea4 test al, al
006a4ea6 je 0x6a4eb1
006a4ea8 cmp dword ptr [ebp - 0x104], 1
006a4eaf je 0x6a4ec3
006a4eb1 push 0x80
006a4eb6 push 0
006a4eb8 mov ecx, edi
006a4eba call 0x4122f0
006a4ebf test al, al
006a4ec1 je 0x6a4eea
006a4ec3 cmp dword ptr [edi + 0xab4], 1
006a4eca je 0x6a5c9a
006a4ed0 mov eax, dword ptr [0xbfd65c]
006a4ed5 mov eax, dword ptr [eax + 0x1a30dc]
006a4edb sub eax, dword ptr [edi + 0x280]
006a4ee1 cmp eax, 0xa
006a4ee4 jl 0x6a5c9a
006a4eea push 0x100000
006a4eef push 0x100
006a4ef4 mov ecx, edi
006a4ef6 call 0x4122f0
006a4efb test al, al
006a4efd jne 0x6a4f47
006a4eff push 0x100000
006a4f04 push 0x100
006a4f09 mov ecx, esi
006a4f0b call 0x4122f0
006a4f10 test al, al
006a4f12 jne 0x6a4f47
006a4f14 cmp dword ptr [edi + 0x28], 0x322
006a4f1b je 0x6a4f47
006a4f1d mov eax, dword ptr [esi + 0x28]
006a4f20 cmp eax, 0x322
006a4f25 je 0x6a4f47
006a4f27 cmp dword ptr [edi + 0xe88], esi
006a4f2d je 0x6a4f47
006a4f2f cmp eax, 0xa
006a4f32 jl 0x6a4f43
006a4f34 cmp eax, 0x3e8
006a4f39 jge 0x6a4f43
006a4f3b cmp dword ptr [esi + 0xe88], edi
006a4f41 je 0x6a4f47
006a4f43 xor cl, cl
006a4f45 jmp 0x6a4f49
006a4f47 mov cl, 1
006a4f49 mov eax, dword ptr [ebp - 0xec]
006a4f4f mov edx, dword ptr [ebp - 0xe8]
006a4f55 mov byte ptr [ebp - 0xf2], cl
006a4f5b cmp eax, 0x28
006a4f5e jne 0x6a4f7c
006a4f60 cmp edx, eax
006a4f62 jne 0x6a4fe8
006a4f68 test cl, cl
006a4f6a je 0x6a5c9a
006a4f70 mov byte ptr [ebp - 0xf1], 0
006a4f77 jmp 0x6a5014
006a4f7c cmp eax, 0xda
006a4f81 jne 0x6a4f92
006a4f83 cmp edx, eax
006a4f85 jne 0x6a4fe8
006a4f87 mov al, byte ptr [ebp - 0x114]
006a4f8d jmp 0x6a46d9
006a4f92 cmp eax, 0x3e
006a4f95 jne 0x6a4fa6
006a4f97 cmp edx, eax
006a4f99 jne 0x6a4fe8
006a4f9b mov al, byte ptr [ebp - 0x114]
006a4fa1 jmp 0x6a46d9
006a4fa6 cmp eax, 0x119
006a4fab jne 0x6a4fc0
006a4fad cmp edx, eax
006a4faf jne 0x6a4fe8
006a4fb1 test cl, cl
006a4fb3 jne 0x6a5004
006a4fb5 mov al, byte ptr [ebp - 0x114]
006a4fbb jmp 0x6a46d9
006a4fc0 cmp eax, 0x104
006a4fc5 jne 0x6a4fda
006a4fc7 cmp edx, eax
006a4fc9 jne 0x6a4fe8
006a4fcb test cl, cl
006a4fcd jne 0x6a5004
006a4fcf mov al, byte ptr [ebp - 0x114]
006a4fd5 jmp 0x6a46d9
006a4fda cmp eax, 0x1c
006a4fdd jne 0x6a4fe8
006a4fdf cmp edx, 0x1e
006a4fe2 je 0x6a5c9a
006a4fe8 cmp edx, 0x1f
006a4feb je 0x6a500d
006a4fed cmp edx, 0x15
006a4ff0 je 0x6a500d
006a4ff2 cmp edx, 0x17
006a4ff5 je 0x6a500d
006a4ff7 cmp edx, 0x37
006a4ffa je 0x6a500d
006a4ffc cmp edx, 0xf3
006a5002 je 0x6a500d
006a5004 mov byte ptr [ebp - 0xf1], 0
006a500b jmp 0x6a5014
006a500d mov byte ptr [ebp - 0xf1], 1
006a5014 cmp eax, 0x1f
006a5017 je 0x6a5033
006a5019 cmp eax, 0x15
006a501c je 0x6a5033
006a501e cmp eax, 0x17
006a5021 je 0x6a5033
006a5023 cmp eax, 0x37
006a5026 je 0x6a5033
006a5028 cmp eax, 0xf3
006a502d je 0x6a5033
006a502f xor ch, ch
006a5031 jmp 0x6a5035
006a5033 mov ch, 1
006a5035 cmp byte ptr [ebp - 0xf1], 0
006a503c je 0x6a5051
006a503e test ch, ch
006a5040 je 0x6a5059
006a5042 test cl, cl
006a5044 jne 0x6a5059
006a5046 mov al, byte ptr [ebp - 0x114]
006a504c jmp 0x6a46d9
006a5051 cmp edx, 0xed
006a5057 jne 0x6a50a9
006a5059 cmp eax, 0x191
006a505e jne 0x6a50a9
006a5060 test cl, cl
006a5062 jne 0x6a5094
006a5064 push 0
006a5066 push 0xbeab70
006a506b push 0xbeab18
006a5070 push 0
006a5072 push esi
006a5073 call 0x9ec34c
006a5078 add esp, 0x14
006a507b cmp dword ptr [eax + 0xab4], 0x10
006a5082 je 0x6a5c9a
006a5088 mov edx, dword ptr [ebp - 0xe8]
006a508e mov eax, dword ptr [ebp - 0xec]
006a5094 cmp edx, 0x123
006a509a je 0x6a5114
006a509c cmp eax, 0x123
006a50a1 je 0x6a5c9a
006a50a7 jmp 0x6a511f
006a50a9 cmp eax, 0x55
006a50ac je 0x6a50b3
006a50ae cmp eax, 0x1e
006a50b1 jne 0x6a50cb
006a50b3 cmp edx, 0xce
006a50b9 je 0x6a50c3
006a50bb cmp edx, 0xcf
006a50c1 jne 0x6a50cb
006a50c3 test cl, cl
006a50c5 je 0x6a5c9a
006a50cb cmp eax, 0xd8
006a50d0 jne 0x6a50ff
006a50d2 cmp edx, eax
006a50d4 jne 0x6a5094
006a50d6 cmp dword ptr [ebp - 0x124], 1
006a50dd jne 0x6a50ec
006a50df cmp dword ptr [ebp - 0xf0], 1
006a50e6 je 0x6a5c9a
006a50ec cmp dword ptr [esi + 0x314], edi
006a50f2 jne 0x6a511f
006a50f4 mov al, byte ptr [ebp - 0x114]
006a50fa jmp 0x6a46d9
006a50ff cmp eax, 0x121
006a5104 jne 0x6a5094
006a5106 cmp edx, 0x100
006a510c je 0x6a5c9a
006a5112 jmp 0x6a5094
006a5114 cmp eax, 0x123
006a5119 jne 0x6a5c9a
006a511f cmp byte ptr [ebp + 0xc], 0
006a5123 jne 0x6a55fd
006a5129 cmp eax, 1
006a512c jne 0x6a55ba
006a5132 push 0
006a5134 push 0xbeab9c
006a5139 push 0xbeab18
006a513e push 0
006a5140 push esi
006a5141 call 0x9ec34c
006a5146 add esp, 0x14
006a5149 mov dword ptr [ebp - 0xf8], eax
006a514f cmp dword ptr [edi + 0x28], 0x362
006a5156 jne 0x6a51a9
006a5158 mov ecx, dword ptr [0xbfd65c]
006a515e mov ecx, dword ptr [ecx + 0x18190]
006a5164 call 0x7cf750
006a5169 cmp eax, 0xf
006a516c jle 0x6a46d7
006a5172 mov eax, dword ptr [ebp - 0xf8]
006a5178 mov eax, dword ptr [eax + 0x130c]
006a517e cmp eax, 0x13
006a5181 je 0x6a5191
006a5183 cmp eax, 0x25
006a5186 je 0x6a5191
006a5188 cmp eax, 0x27
006a518b jne 0x6a46d7
006a5191 mov eax, dword ptr [edi + 0xab4]
006a5197 cmp eax, 5
006a519a je 0x6a46d7
006a51a0 cmp eax, 0xd
006a51a3 je 0x6a46d7
006a51a9 mov ecx, dword ptr [ebp - 0xe8]
006a51af xorps xmm0, xmm0
006a51b2 movlpd qword ptr [ebp - 0x108], xmm0
006a51ba movss xmm0, dword ptr [edi + 0x2e0]
006a51c2 movss dword ptr [ebp - 0xfc], xmm0
006a51ca cmp ecx, 0x21
006a51cd jne 0x6a51e5
006a51cf mov dword ptr [ebp - 0x104], 2
006a51d9 mov dword ptr [ebp - 0x120], 0
006a51e3 jmp 0x6a522d
006a51e5 cmp ecx, 0x379
006a51eb jne 0x6a5215
006a51ed cmp dword ptr [edi + 0xab4], 0x10
006a51f4 jne 0x6a5215
006a51f6 cmp dword ptr [edi + 0xb14], 0x63
006a51fd jne 0x6a5215
006a51ff mov dword ptr [ebp - 0x104], 2
006a5209 mov dword ptr [ebp - 0x120], 0
006a5213 jmp 0x6a522d
006a5215 mov eax, dword ptr [ebp - 0x104]
006a521b mov dword ptr [ebp - 0x120], eax
006a5221 mov eax, dword ptr [ebp - 0x108]
006a5227 mov dword ptr [ebp - 0x104], eax
006a522d mov eax, dword ptr [edi + 0x288]
006a5233 mov eax, dword ptr [eax + 0xd8]
006a5239 and eax, 1
006a523c or eax, 0
006a523f je 0x6a5262
006a5241 mov ecx, dword ptr [0xbfd65c]
006a5247 push 9
006a5249 lea ecx, [ecx + 0x1ba40]
006a524f call 0x4e6210
006a5254 test al, al
006a5256 jne 0x6a544f
006a525c mov ecx, dword ptr [ebp - 0xe8]
006a5262 mov eax, dword ptr [edi + 0x288]
006a5268 mov eax, dword ptr [eax + 0xd8]
006a526e and eax, 2
006a5271 or eax, 0
006a5274 je 0x6a52ab
006a5276 cmp ecx, 0x332
006a527c jne 0x6a5287
006a527e cmp dword ptr [ebp - 0x124], 2
006a5285 je 0x6a52d7
006a5287 mov ecx, dword ptr [0xbfd65c]
006a528d push 0x179
006a5292 lea ecx, [ecx + 0x1ba40]
006a5298 call 0x4e6210
006a529d test al, al
006a529f jne 0x6a544f
006a52a5 mov ecx, dword ptr [ebp - 0xe8]
006a52ab cmp ecx, 0x371
006a52b1 jne 0x6a52bc
006a52b3 cmp dword ptr [edi + 0xab4], 6
006a52ba jmp 0x6a52d1
006a52bc cmp ecx, 0x379
006a52c2 jne 0x6a52d7
006a52c4 push 0
006a52c6 push 0x10
006a52c8 mov ecx, edi
006a52ca call 0x4122f0
006a52cf test al, al
006a52d1 jne 0x6a544f
006a52d7 movss xmm0, dword ptr [ebp - 0xfc]
006a52df xorps xmm1, xmm1
006a52e2 comiss xmm0, xmm1
006a52e5 jbe 0x6a544f
006a52eb push edi
006a52ec lea ecx, [ebp - 0x38]
006a52ef call 0x4229a0
006a52f4 mov ecx, dword ptr [ebp - 0xf8]
006a52fa lea edx, [ebp - 0x38]
006a52fd push 0x1e
006a52ff push edx
006a5300 push dword ptr [ebp - 0x120]
006a5306 mov eax, dword ptr [ecx]
006a5308 push dword ptr [ebp - 0x104]
006a530e push ecx
006a530f mov eax, dword ptr [eax + 0x20]
006a5312 movss dword ptr [esp], xmm0
006a5317 call eax
006a5319 mov ecx, dword ptr [ebp - 0xf8]
006a531f test al, al
006a5321 je 0x6a5455
006a5327 cmp byte ptr [edi + 0xbb3], 0
006a532e je 0x6a5455
006a5334 cmp dword ptr [edi + 0xbb4], 3
006a533b jne 0x6a5455
006a5341 cmp dword ptr [ecx + 0x12b8], 0
006a5348 jle 0x6a5455
006a534e push -1
006a5350 call 0x725740
006a5355 call 0x6c3d90
006a535a xor edx, edx
006a535c mov ecx, 3
006a5361 div ecx
006a5363 mov eax, dword ptr [ebp - 0xf8]
006a5369 inc edx
006a536a mov eax, dword ptr [eax + 0x12b8]
006a5370 cmp edx, eax
006a5372 cmovl eax, edx
006a5375 mov dword ptr [ebp - 0x120], eax
006a537b test eax, eax
006a537d jle 0x6a5441
006a5383 lea ecx, [edi + 0x294]
006a5389 mov edi, eax
006a538b mov dword ptr [ebp - 0x104], ecx
006a5391 call 0x6c3d90
006a5396 movd xmm0, eax
006a539a cvtdq2pd xmm0, xmm0
006a539e shr eax, 0x1f
006a53a1 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
006a53aa cvtpd2ps xmm0, xmm0
006a53ae mulss xmm0, dword ptr [0xb6a19c]
006a53b6 mulss xmm0, dword ptr [0xb6a8f4]
006a53be addss xmm0, dword ptr [0xb6a7b0]
006a53c6 movss dword ptr [ebp - 0xfc], xmm0
006a53ce call 0x6c3d90
006a53d3 mov esi, eax
006a53d5 lea eax, [ebp - 0x18]
006a53d8 push eax
006a53d9 call 0x659290
006a53de movss xmm1, dword ptr [ebp - 0xfc]
006a53e6 add esp, 4
006a53e9 mov ecx, dword ptr [0xbfd65c]
006a53ef movaps xmm0, xmm1
006a53f2 mulss xmm0, dword ptr [eax]
006a53f6 push esi
006a53f7 mulss xmm1, dword ptr [eax + 4]
006a53fc lea eax, [ebp - 0x128]
006a5402 push 1
006a5404 push 0
006a5406 push eax
006a5407 push dword ptr [ebp - 0x104]
006a540d movss dword ptr [ebp - 0x128], xmm0
006a5415 push 0x14
006a5417 push 5
006a5419 movss dword ptr [ebp - 0x124], xmm1
006a5421 call 0x422e20
006a5426 sub edi, 1
006a5429 jne 0x6a5391
006a542f mov edi, dword ptr [ebp - 0x10c]
006a5435 mov esi, dword ptr [ebp - 0x118]
006a543b mov eax, dword ptr [ebp - 0x120]
006a5441 mov ecx, dword ptr [ebp - 0xf8]
006a5447 neg eax
006a5449 push eax
006a544a call 0x725740
006a544f mov ecx, dword ptr [ebp - 0xf8]
006a5455 mov eax, dword ptr [ebp - 0xec]
006a545b push 0
006a545d push 0xec
006a5462 call 0x73af30
006a5467 test al, al
006a5469 je 0x6a5552
006a546f mov ecx, edi
006a5471 call 0x6aabe0
006a5476 test al, al
006a5478 je 0x6a5552
006a547e mov eax, dword ptr [ebp - 0xe8]
006a5484 cmp eax, 0xf5
006a5489 je 0x6a5552
006a548f cmp eax, 0x1c
006a5492 je 0x6a5552
006a5498 push 0
006a549a mov ecx, edi
006a549c call 0x684630
006a54a1 test al, al
006a54a3 je 0x6a5552
006a54a9 cmp dword ptr [ebp - 0xe8], 0xd5
006a54b3 je 0x6a5552
006a54b9 mov eax, dword ptr [edi]
006a54bb mov ecx, edi
006a54bd call dword ptr [eax + 0x28]
006a54c0 mov ecx, dword ptr [ebp - 0xf8]
006a54c6 push 0
006a54c8 push 0xca
006a54cd call 0x73af30
006a54d2 xor ecx, ecx
006a54d4 test al, al
006a54d6 setne cl
006a54d9 mov dword ptr [ebp - 0x10c], ecx
006a54df call 0x6c3d90
006a54e4 mov ecx, dword ptr [0xbfd65c]
006a54ea push eax
006a54eb push 0
006a54ed push 0
006a54ef push 0xc02fec
006a54f4 lea eax, [edi + 0x294]
006a54fa push eax
006a54fb push dword ptr [ebp - 0x10c]
006a5501 push 0xf5
006a5506 call 0x422e20
006a550b push 0x16
006a550d push 0x19
006a550f push 0x27
006a5511 push ecx
006a5512 mov edx, eax
006a5514 mov dword ptr [esp], 0x3f800000
006a551b xorps xmm3, xmm3
006a551e mov dword ptr [ebp - 0x10c], edx
006a5524 xorps xmm2, xmm2
006a5527 lea ecx, [ebp - 0x16c]
006a552d xorps xmm1, xmm1
006a5530 call 0x4270d0
006a5535 push eax
006a5536 mov ecx, edx
006a5538 call 0x447cc0
006a553d mov ecx, dword ptr [edi + 0x32c]
006a5543 test ecx, ecx
006a5545 je 0x6a5552
006a5547 push dword ptr [ebp - 0x10c]
006a554d call 0x4bc2d0
006a5552 cmp byte ptr [edi + 0x16c], 0
006a5559 je 0x6a5562
006a555b mov eax, dword ptr [edi]
006a555d mov ecx, edi
006a555f call dword ptr [eax + 0x24]
006a5562 cmp dword ptr [edi + 0x28], 0x3d
006a5566 jne 0x6a567c
006a556c cmp dword ptr [edi + 0x2c], 5
006a5570 je 0x6a55a0
006a5572 cmp dword ptr [edi + 0x2c], 6
006a5576 mov ecx, dword ptr [ebp - 0xec]
006a557c mov eax, dword ptr [ebp - 0xf0]
006a5582 mov dword ptr [ebp - 0xec], ecx
006a5588 mov dword ptr [ebp - 0xf0], eax
006a558e jne 0x6a567c
006a5594 mov dword ptr [ebp - 0xec], ecx
006a559a mov dword ptr [ebp - 0xf0], eax
006a55a0 cmp dword ptr [edi + 0xab4], 8
006a55a7 jne 0x6a567c
006a55ad push esi
006a55ae mov ecx, edi
006a55b0 call 0x539620
006a55b5 jmp 0x6a46d7
006a55ba cmp eax, 3
006a55bd jne 0x6a55fd
006a55bf mov ecx, esi
006a55c1 call 0x5efac0
006a55c6 test al, al
006a55c8 je 0x6a55f7
006a55ca push edi
006a55cb lea ecx, [ebp - 0x38]
006a55ce call 0x4229a0
006a55d3 mov eax, dword ptr [esi]
006a55d5 lea ecx, [ebp - 0x38]
006a55d8 movss xmm0, dword ptr [edi + 0x2e0]
006a55e0 push 0x1e
006a55e2 push ecx
006a55e3 push 0
006a55e5 push 0
006a55e7 push ecx
006a55e8 mov ecx, esi
006a55ea movss dword ptr [esp], xmm0
006a55ef call dword ptr [eax + 0x20]
006a55f2 jmp 0x6a567c
006a55f7 mov eax, dword ptr [ebp - 0xec]
006a55fd cmp edx, 0x29
006a5600 jne 0x6a5610
006a5602 cmp dword ptr [edi + 0xab4], 8
006a5609 je 0x6a5638
006a560b jmp 0x6a56bc
006a5610 cmp edx, 0x20
006a5613 jne 0x6a5623
006a5615 cmp dword ptr [edi + 0xab4], 8
006a561c je 0x6a5638
006a561e jmp 0x6a56bc
006a5623 cmp edx, 0xed
006a5629 jne 0x6a5682
006a562b cmp dword ptr [edi + 0xab4], 8
006a5632 jne 0x6a56bc
006a5638 cmp eax, 2
006a563b je 0x6a5682
006a563d cmp eax, 3
006a5640 je 0x6a5682
006a5642 cmp eax, 1
006a5645 je 0x6a5682
006a5647 lea ecx, [edi + 0x364]
006a564d mov dword ptr [edi + 0xab4], 4
006a5657 call 0x7a6de0
006a565c movss xmm0, dword ptr [0xc02fec]
006a5664 movss dword ptr [edi + 0x28c], xmm0
006a566c movss xmm0, dword ptr [0xc02ff0]
006a5674 movss dword ptr [edi + 0x290], xmm0
006a567c mov edx, dword ptr [ebp - 0xe8]
006a5682 cmp edx, 0x21
006a5685 jne 0x6a56bc
006a5687 mov eax, dword ptr [esi + 0x28]
006a568a sub eax, 0xa
006a568d cmp eax, 0x3dd
006a5692 ja 0x6a56bc
006a5694 push edi
006a5695 lea ecx, [ebp - 0x38]
006a5698 call 0x4229a0
006a569d mov eax, dword ptr [esi]
006a569f lea ecx, [ebp - 0x38]
006a56a2 push 0x1e
006a56a4 push ecx
006a56a5 push 0
006a56a7 push 2
006a56a9 push ecx
006a56aa mov ecx, esi
006a56ac mov dword ptr [esp], 0x41800000
006a56b3 call dword ptr [eax + 0x20]
006a56b6 mov edx, dword ptr [ebp - 0xe8]
006a56bc cmp byte ptr [ebp + 0xc], 0
006a56c0 jne 0x6a5703
006a56c2 mov eax, dword ptr [esi + 0x28]
006a56c5 sub eax, 0xa
006a56c8 cmp eax, 0x3dd
006a56cd ja 0x6a5703
006a56cf cmp edx, 0x3f
006a56d2 jne 0x6a5703
006a56d4 cmp dword ptr [edi + 0xab4], 8
006a56db jne 0x6a58f3
006a56e1 mov edx, dword ptr [esi]
006a56e3 lea ecx, [ebp - 0x38]
006a56e6 push 0x1e
006a56e8 call 0x427290
006a56ed push eax
006a56ee push 0
006a56f0 push 0
006a56f2 push ecx
006a56f3 mov ecx, esi
006a56f5 mov dword ptr [esp], 0x41200000
006a56fc call dword ptr [edx + 0x20]
006a56ff xor dl, dl
006a5701 jmp 0x6a5765
006a5703 cmp edx, 0x1c
006a5706 jne 0x6a57a5
006a570c cmp dword ptr [edi + 0xab4], 8
006a5713 jne 0x6a5763
006a5715 mov eax, dword ptr [ebp - 0xec]
006a571b cmp eax, 0x17
006a571e je 0x6a5725
006a5720 cmp eax, 0x55
006a5723 jne 0x6a5763
006a5725 mov edx, dword ptr [esi]
006a5727 lea ecx, [ebp - 0x38]
006a572a push 0x1e
006a572c call 0x427290
006a5731 push eax
006a5732 push 0
006a5734 push 0
006a5736 push ecx
006a5737 mov ecx, esi
006a5739 mov dword ptr [esp], 0x41a00000
006a5740 call dword ptr [edx + 0x20]
006a5743 push ecx
006a5744 mov dword ptr [esp], 0x3f800000
006a574b push 0
006a574d push 2
006a574f push ecx
006a5750 mov dword ptr [esp], 0x3f800000
006a5757 mov ecx, edi
006a5759 push 0x8e
006a575e call 0x6ad720
006a5763 mov dl, 1
006a5765 mov ecx, dword ptr [ebp - 0xec]
006a576b cmp ecx, 0x13
006a576e je 0x6a58fa
006a5774 cmp ecx, 0x59
006a5777 je 0x6a58fa
006a577d cmp ecx, 0xef
006a5783 je 0x6a58fa
006a5789 cmp ecx, 0x1c
006a578c je 0x6a58fa
006a5792 cmp ecx, 0x396
006a5798 je 0x6a58fa
006a579e xor al, al
006a57a0 jmp 0x6a58fc
006a57a5 cmp edx, 0x63
006a57a8 jne 0x6a57cf
006a57aa cmp dword ptr [edi + 0xab4], 8
006a57b1 jne 0x6a58f3
006a57b7 cmp dword ptr [ebp - 0xec], 0xe
006a57be jne 0x6a58f3
006a57c4 mov eax, dword ptr [esi]
006a57c6 mov ecx, esi
006a57c8 call dword ptr [eax + 0x24]
006a57cb xor dl, dl
006a57cd jmp 0x6a5765
006a57cf cmp edx, 0x109
006a57d5 jne 0x6a580c
006a57d7 cmp dword ptr [edi + 0xab4], 8
006a57de jne 0x6a58f3
006a57e4 cmp dword ptr [edi + 0xb10], 1
006a57eb jne 0x6a58f3
006a57f1 cmp dword ptr [ebp - 0xec], 0x27
006a57f8 jne 0x6a58f3
006a57fe mov eax, dword ptr [esi]
006a5800 mov ecx, esi
006a5802 call dword ptr [eax + 0x24]
006a5805 xor dl, dl
006a5807 jmp 0x6a5765
006a580c cmp edx, 0x42
006a580f jne 0x6a586e
006a5811 cmp dword ptr [edi + 0x2c], 0x14
006a5815 jne 0x6a58f3
006a581b cmp dword ptr [ebp - 0xec], edx
006a5821 je 0x6a5c9a
006a5827 push 0
006a5829 mov ecx, esi
006a582b call 0x684630
006a5830 test al, al
006a5832 je 0x6a5856
006a5834 push edi
006a5835 lea ecx, [ebp - 0x38]
006a5838 call 0x4229a0
006a583d mov eax, dword ptr [esi]
006a583f lea ecx, [ebp - 0x38]
006a5842 push 0x1e
006a5844 push ecx
006a5845 push 0
006a5847 push 0
006a5849 push ecx
006a584a mov ecx, esi
006a584c mov dword ptr [esp], 0x41a00000
006a5853 call dword ptr [eax + 0x20]
006a5856 cmp dword ptr [ebp - 0xec], 1
006a585d je 0x6a58f3
006a5863 mov al, byte ptr [ebp - 0x114]
006a5869 jmp 0x6a46d9
006a586e cmp edx, 0x2c
006a5871 jne 0x6a58a5
006a5873 cmp dword ptr [ebp - 0xec], 0x53
006a587a jne 0x6a58f3
006a587c push edi
006a587d lea ecx, [ebp - 0x38]
006a5880 call 0x4229a0
006a5885 mov eax, dword ptr [esi]
006a5887 lea ecx, [ebp - 0x38]
006a588a push 0x1e
006a588c push ecx
006a588d push 0
006a588f push 0
006a5891 push ecx
006a5892 mov ecx, esi
006a5894 mov dword ptr [esp], 0x41200000
006a589b call dword ptr [eax + 0x20]
006a589e xor dl, dl
006a58a0 jmp 0x6a5765
006a58a5 cmp edx, 0x36e
006a58ab jne 0x6a58c9
006a58ad cmp dword ptr [ebp - 0xec], edx
006a58b3 jne 0x6a58f3
006a58b5 cmp byte ptr [ebp - 0xf2], 0
006a58bc jne 0x6a58f3
006a58be mov al, byte ptr [ebp - 0x114]
006a58c4 jmp 0x6a46d9
006a58c9 cmp edx, 0x13
006a58cc je 0x6a5763
006a58d2 cmp edx, 0x59
006a58d5 je 0x6a5763
006a58db cmp edx, 0xef
006a58e1 je 0x6a5763
006a58e7 cmp edx, 0x396
006a58ed je 0x6a5763
006a58f3 xor dl, dl
006a58f5 jmp 0x6a5765
006a58fa mov al, 1
006a58fc test dl, dl
006a58fe je 0x6a5932
006a5900 test al, al
006a5902 je 0x6a5932
006a5904 push esi
006a5905 mov ecx, edi
006a5907 call 0x6815c0
006a590c test al, al
006a590e jne 0x6a5c9a
006a5914 push esi
006a5915 mov ecx, edi
006a5917 call 0x6815c0
006a591c test al, al
006a591e jne 0x6a592c
006a5920 cmp byte ptr [ebp - 0xf2], al
006a5926 je 0x6a5c9a
006a592c mov ecx, dword ptr [ebp - 0xec]
006a5932 mov eax, dword ptr [ebp - 0xe8]
006a5938 cmp eax, 0x23
006a593b jne 0x6a5957
006a593d cmp ecx, eax
006a593f jne 0x6a5957
006a5941 push esi
006a5942 mov ecx, edi
006a5944 call 0x6815c0
006a5949 test al, al
006a594b jne 0x6a46d7
006a5951 mov eax, dword ptr [ebp - 0xe8]
006a5957 cmp byte ptr [ebp + 0xc], 0
006a595b mov ecx, dword ptr [ebp - 0xec]
006a5961 jne 0x6a5ab3
006a5967 cmp ecx, 4
006a596a jne 0x6a5a91
006a5970 cmp eax, 0x1c
006a5973 jne 0x6a599b
006a5975 cmp dword ptr [edi + 0x314], 0
006a597c jne 0x6a6017
006a5982 cmp dword ptr [edi + 0xab4], 8
006a5989 jne 0x6a6017
006a598f mov dword ptr [edi + 0xab4], 0x10
006a5999 jmp 0x6a59e6
006a599b cmp eax, 0x3e
006a599e jne 0x6a5a91
006a59a4 cmp dword ptr [edi + 0x2c], 3
006a59a8 jne 0x6a6017
006a59ae cmp dword ptr [edi + 0x314], 0
006a59b5 jne 0x6a6017
006a59bb mov eax, dword ptr [edi + 0xab4]
006a59c1 cmp eax, 6
006a59c4 je 0x6a59cf
006a59c6 cmp eax, 4
006a59c9 jne 0x6a6017
006a59cf cmp dword ptr [edi + 0xb10], 2
006a59d6 jne 0x6a6017
006a59dc mov dword ptr [edi + 0xab4], 5
006a59e6 push 0
006a59e8 push 0xbeacac
006a59ed push 0xbeab18
006a59f2 push 0
006a59f4 push esi
006a59f5 mov dword ptr [edi + 0x360], 0
006a59ff call 0x9ec34c
006a5a04 mov esi, eax
006a5a06 add esp, 0x14
006a5a09 test esi, esi
006a5a0b je 0x6a5c9a
006a5a11 push 0
006a5a13 mov ecx, esi
006a5a15 call 0x6818e0
006a5a1a mov byte ptr [esi + 0x398], 0
006a5a21 mov ecx, edi
006a5a23 mov dword ptr [esi + 0x360], 0x23
006a5a2d mov dword ptr [esi + 0x364], 0x23
006a5a37 mov dword ptr [esi + 0x180], 0
006a5a41 mov byte ptr [esi + 0x169], 0
006a5a48 mov eax, dword ptr [edi + 0x294]
006a5a4e mov dword ptr [esi + 0x294], eax
006a5a54 mov eax, dword ptr [edi + 0x298]
006a5a5a mov dword ptr [esi + 0x298], eax
006a5a60 movss xmm0, dword ptr [0xc02fec]
006a5a68 movss dword ptr [esi + 0x2b8], xmm0
006a5a70 movss xmm0, dword ptr [0xc02ff0]
006a5a78 push esi
006a5a79 movss dword ptr [esi + 0x2bc], xmm0
006a5a81 call 0x6a6d70
006a5a86 mov al, byte ptr [ebp - 0x114]
006a5a8c jmp 0x6a46d9
006a5a91 cmp eax, 0x24
006a5a94 jne 0x6a5aaa
006a5a96 cmp dword ptr [esi + 0x34], eax
006a5a99 jne 0x6a5d30
006a5a9f mov al, byte ptr [ebp - 0x114]
006a5aa5 jmp 0x6a46d9
006a5aaa cmp eax, 0x11
006a5aad je 0x6a5c9a
006a5ab3 cmp eax, 0xd5
006a5ab8 jne 0x6a5c19
006a5abe cmp dword ptr [edi + 0xab4], 7
006a5ac5 jne 0x6a5d30
006a5acb mov eax, dword ptr [ebp - 0xf0]
006a5ad1 mov dword ptr [edi + 0xb10], ecx
006a5ad7 mov dword ptr [edi + 0xb14], eax
006a5add push 0
006a5adf cmp ecx, 1
006a5ae2 jne 0x6a5b8c
006a5ae8 push 0xbeab9c
006a5aed push 0xbeab18
006a5af2 push 0
006a5af4 push esi
006a5af5 call 0x9ec34c
006a5afa add esp, 0x14
006a5afd mov dword ptr [ebp - 0x10c], eax
006a5b03 cmp byte ptr [eax + 0x360], 0
006a5b0a je 0x6a6017
006a5b10 push 0
006a5b12 push 0
006a5b14 mov ecx, eax
006a5b16 call 0x786a60
006a5b1b test al, al
006a5b1d jne 0x6a6017
006a5b23 mov esi, dword ptr [ebp - 0x10c]
006a5b29 mov ecx, edi
006a5b2b mov eax, dword ptr [esi + 0x28]
006a5b2e mov dword ptr [edi + 0xb10], eax
006a5b34 mov eax, dword ptr [esi + 0x2c]
006a5b37 mov dword ptr [edi + 0xb14], eax
006a5b3d mov dword ptr [edi + 0xab4], 0x10
006a5b47 call 0x685ef0
006a5b4c mov eax, dword ptr [edi + 0x164]
006a5b52 mov ecx, esi
006a5b54 or dword ptr [edi + 0x160], 1
006a5b5b mov byte ptr [edi + 0x308], 1
006a5b62 mov dword ptr [edi + 0x164], eax
006a5b68 mov dword ptr [edi + 0x180], 0
006a5b72 mov dword ptr [edi + 0x360], 0
006a5b7c call 0x77dbf0
006a5b81 mov al, byte ptr [ebp - 0x114]
006a5b87 jmp 0x6a46d9
006a5b8c push 0x100
006a5b91 mov ecx, edi
006a5b93 call 0x4122f0
006a5b98 test al, al
006a5b9a jne 0x6a5bb2
006a5b9c push 0x100000
006a5ba1 push 0
006a5ba3 mov ecx, esi
006a5ba5 call 0x4122f0
006a5baa test al, al
006a5bac je 0x6a5d2a
006a5bb2 push 0
006a5bb4 mov ecx, esi
006a5bb6 call 0x684630
006a5bbb test al, al
006a5bbd je 0x6a5d2a
006a5bc3 mov eax, dword ptr [esi]
006a5bc5 mov ecx, esi
006a5bc7 mov eax, dword ptr [eax + 0x48]
006a5bca call eax
006a5bcc test al, al
006a5bce jne 0x6a5d2a
006a5bd4 mov eax, dword ptr [esi]
006a5bd6 mov ecx, esi
006a5bd8 call dword ptr [eax + 0x28]
006a5bdb mov eax, dword ptr [ebp - 0xec]
006a5be1 mov dword ptr [edi + 0xb10], eax
006a5be7 mov eax, dword ptr [ebp - 0xf0]
006a5bed mov dword ptr [edi + 0xb14], eax
006a5bf3 mov al, byte ptr [ebp - 0x114]
006a5bf9 mov dword ptr [edi + 0xab4], 0x10
006a5c03 mov byte ptr [edi + 0x308], 1
006a5c0a mov dword ptr [edi + 0x360], 0
006a5c14 jmp 0x6a46d9
006a5c19 cmp eax, 0xde
006a5c1e jne 0x6a5c40
006a5c20 cmp ecx, eax
006a5c22 jne 0x6a5d30
006a5c28 cmp byte ptr [ebp - 0xf2], 0
006a5c2f jne 0x6a6017
006a5c35 mov al, byte ptr [ebp - 0x114]
006a5c3b jmp 0x6a46d9
006a5c40 cmp eax, 0x1d
006a5c43 jne 0x6a5c71
006a5c45 cmp ecx, 0x106
006a5c4b je 0x6a5c59
006a5c4d cmp ecx, 0x107
006a5c53 jne 0x6a5d30
006a5c59 cmp byte ptr [ebp - 0xf2], 0
006a5c60 jne 0x6a5d30
006a5c66 mov al, byte ptr [ebp - 0x114]
006a5c6c jmp 0x6a46d9
006a5c71 cmp eax, 0x112
006a5c76 jne 0x6a5c8b
006a5c78 cmp ecx, eax
006a5c7a jne 0x6a5d30
006a5c80 mov al, byte ptr [ebp - 0x114]
006a5c86 jmp 0x6a46d9
006a5c8b cmp eax, 0xd4
006a5c90 jne 0x6a5ca5
006a5c92 cmp ecx, eax
006a5c94 je 0x6a6017
006a5c9a mov al, byte ptr [ebp - 0x114]
006a5ca0 jmp 0x6a46d9
006a5ca5 cmp eax, 0xf5
006a5caa jne 0x6a5cc0
006a5cac cmp dword ptr [esi + 0x17c], 5
006a5cb3 je 0x6a5d30
006a5cb5 mov al, byte ptr [ebp - 0x114]
006a5cbb jmp 0x6a46d9
006a5cc0 cmp eax, 0x192
006a5cc5 jne 0x6a5d03
006a5cc7 mov edx, dword ptr [edi + 0xab4]
006a5ccd cmp edx, 8
006a5cd0 je 0x6a5cd7
006a5cd2 cmp edx, 4
006a5cd5 jne 0x6a5d0a
006a5cd7 cmp ecx, 0xd9
006a5cdd jne 0x6a5d0a
006a5cdf movss xmm0, dword ptr [esi + 0x2d8]
006a5ce7 mov ecx, esi
006a5ce9 addss xmm0, dword ptr [edi + 0x2d8]
006a5cf1 movss dword ptr [edi + 0x2d8], xmm0
006a5cf9 mov eax, dword ptr [esi]
006a5cfb call dword ptr [eax + 0x24]
006a5cfe jmp 0x6a6017
006a5d03 cmp eax, 0x105
006a5d08 jne 0x6a5d12
006a5d0a cmp ecx, 0x127
006a5d10 je 0x6a5c9a
006a5d12 cmp eax, 0x127
006a5d17 jne 0x6a5d30
006a5d19 cmp ecx, 1
006a5d1c jne 0x6a5d30
006a5d1e mov eax, dword ptr [edi]
006a5d20 mov ecx, edi
006a5d22 call dword ptr [eax + 0x24]
006a5d25 jmp 0x6a6017
006a5d2a mov eax, dword ptr [ebp - 0xe8]
006a5d30 mov ecx, dword ptr [ebp - 0xec]
006a5d36 cmp ecx, 9
006a5d39 jne 0x6a5d44
006a5d3b cmp eax, 0x127
006a5d40 je 0x6a5d51
006a5d42 jmp 0x6a5d5e
006a5d44 cmp ecx, 0x127
006a5d4a jne 0x6a5d5e
006a5d4c cmp eax, 9
006a5d4f jne 0x6a5d5e
006a5d51 mov eax, dword ptr [edi]
006a5d53 mov ecx, edi
006a5d55 call dword ptr [eax + 0x24]
006a5d58 mov ecx, dword ptr [ebp - 0xec]
006a5d5e mov eax, dword ptr [ebp - 0xe8]
006a5d64 cmp eax, 0x125
006a5d69 jne 0x6a5e33
006a5d6f cmp dword ptr [edi + 0x2c], 0
006a5d73 jne 0x6a6017
006a5d79 movss xmm0, dword ptr [edi + 0x294]
006a5d81 subss xmm0, dword ptr [esi + 0x294]
006a5d89 movss dword ptr [ebp - 0x100], xmm0
006a5d91 movss xmm0, dword ptr [edi + 0x298]
006a5d99 subss xmm0, dword ptr [esi + 0x298]
006a5da1 movss dword ptr [ebp - 0xfc], xmm0
006a5da9 call 0x6c3d90
006a5dae lea ecx, [ebp - 0x100]
006a5db4 movd xmm0, eax
006a5db8 cvtdq2pd xmm0, xmm0
006a5dbc shr eax, 0x1f
006a5dbf addsd xmm0, qword ptr [eax*8 + 0xb6c940]
006a5dc8 lea eax, [ebp - 0x18]
006a5dcb push eax
006a5dcc cvtpd2ps xmm0, xmm0
006a5dd0 mulss xmm0, dword ptr [0xb6a19c]
006a5dd8 movss dword ptr [ebp - 0x10c], xmm0
006a5de0 call 0x962560
006a5de5 push 0
006a5de7 mov ecx, edi
006a5de9 movss xmm0, dword ptr [eax]
006a5ded mulss xmm0, dword ptr [0xb6a95c]
006a5df5 mulss xmm0, dword ptr [ebp - 0x10c]
006a5dfd movss dword ptr [ebp - 0x110], xmm0
006a5e05 movss xmm0, dword ptr [eax + 4]
006a5e0a lea eax, [ebp - 0x110]
006a5e10 mulss xmm0, dword ptr [0xb6a95c]
006a5e18 push eax
006a5e19 mulss xmm0, dword ptr [ebp - 0x10c]
006a5e21 movss dword ptr [ebp - 0x10c], xmm0
006a5e29 call 0x422b60
006a5e2e jmp 0x6a6017
006a5e33 cmp eax, 0x196
006a5e38 jne 0x6a5f62
006a5e3e mov edx, dword ptr [esi + 0x28]
006a5e41 lea eax, [edx - 0xa]
006a5e44 cmp eax, 0x3dd
006a5e49 mov eax, edx
006a5e4b ja 0x6a5efb
006a5e51 cmp ecx, 0x125
006a5e57 je 0x6a5efb
006a5e5d movss xmm1, dword ptr [edi + 0x2b8]
006a5e65 movss xmm2, dword ptr [edi + 0x2bc]
006a5e6d movaps xmm0, xmm1
006a5e70 mulss xmm0, xmm1
006a5e74 movaps xmm1, xmm2
006a5e77 mov dword ptr [ebp - 0x10c], edx
006a5e7d mulss xmm1, xmm2
006a5e81 addss xmm0, xmm1
006a5e85 call 0x4228c0
006a5e8a comiss xmm0, dword ptr [0xb6a614]
006a5e91 jbe 0x6a5ef5
006a5e93 movss xmm1, dword ptr [esi + 0x294]
006a5e9b movss xmm0, dword ptr [esi + 0x298]
006a5ea3 subss xmm0, dword ptr [edi + 0x298]
006a5eab subss xmm1, dword ptr [edi + 0x294]
006a5eb3 mov eax, dword ptr [esi + 0x28]
006a5eb6 mulss xmm0, dword ptr [edi + 0x2bc]
006a5ebe mulss xmm1, dword ptr [edi + 0x2b8]
006a5ec6 addss xmm0, xmm1
006a5eca xorps xmm1, xmm1
006a5ecd comiss xmm0, xmm1
006a5ed0 jbe 0x6a5efb
006a5ed2 mov edx, dword ptr [esi]
006a5ed4 lea ecx, [ebp - 0x38]
006a5ed7 push 0x1e
006a5ed9 call 0x427290
006a5ede push eax
006a5edf push 0
006a5ee1 push 0x40
006a5ee3 push ecx
006a5ee4 mov ecx, esi
006a5ee6 mov dword ptr [esp], 0x41c80000
006a5eed call dword ptr [edx + 0x20]
006a5ef0 mov eax, dword ptr [esi + 0x28]
006a5ef3 jmp 0x6a5efb
006a5ef5 mov eax, dword ptr [ebp - 0x10c]
006a5efb cmp dword ptr [edi + 0xab4], 0x136
006a5f05 mov ecx, eax
006a5f07 jne 0x6a5f44
006a5f09 cmp eax, 3
006a5f0c jne 0x6a5f17
006a5f0e cmp dword ptr [esi + 0x2c], 0x384
006a5f15 je 0x6a5f37
006a5f17 mov ecx, eax
006a5f19 cmp eax, 1
006a5f1c jne 0x6a5f44
006a5f1e movss xmm0, dword ptr [esi + 0x2d4]
006a5f26 ucomiss xmm0, dword ptr [0xb6accc]
006a5f2d lahf 
006a5f2e test ah, 0x44
006a5f31 jp 0x6a6017
006a5f37 mov dword ptr [edi + 0x360], 0x64
006a5f41 mov ecx, dword ptr [esi + 0x28]
006a5f44 cmp ecx, 5
006a5f47 jne 0x6a6017
006a5f4d cmp dword ptr [esi + 0x2c], 0x64
006a5f51 jne 0x6a6017
006a5f57 mov al, byte ptr [ebp - 0x114]
006a5f5d jmp 0x6a46d9
006a5f62 cmp eax, 0x128
006a5f67 jne 0x6a5f88
006a5f69 cmp ecx, eax
006a5f6b je 0x6a5c9a
006a5f71 cmp ecx, 0x197
006a5f77 jne 0x6a6017
006a5f7d mov al, byte ptr [ebp - 0x114]
006a5f83 jmp 0x6a46d9
006a5f88 cmp eax, 0x197
006a5f8d jne 0x6a5fb5
006a5f8f cmp ecx, 0x128
006a5f95 je 0x6a5c9a
006a5f9b mov eax, dword ptr [esi + 0x28]
006a5f9e sub eax, 0xa
006a5fa1 cmp eax, 0x3dd
006a5fa6 jbe 0x6a6017
006a5fa8 cmp ecx, 1
006a5fab je 0x6a6017
006a5fad cmp ecx, 3
006a5fb0 jmp 0x6a5c94
006a5fb5 cmp eax, 0x36d
006a5fba jne 0x6a6017
006a5fbc mov eax, dword ptr [esi + 0x28]
006a5fbf sub eax, 0xa
006a5fc2 cmp eax, 0x3dd
006a5fc7 ja 0x6a6017
006a5fc9 movss xmm0, dword ptr [edi + 0x2e0]
006a5fd1 xorps xmm1, xmm1
006a5fd4 comiss xmm0, xmm1
006a5fd7 jbe 0x6a6017
006a5fd9 lea ecx, [edi + 0xe50]
006a5fdf push esi
006a5fe0 call 0x422d00
006a5fe5 test al, al
006a5fe7 jne 0x6a6017
006a5fe9 push esi
006a5fea lea ecx, [edi + 0xe50]
006a5ff0 call 0x422ce0
006a5ff5 push edi
006a5ff6 lea ecx, [ebp - 0x38]
006a5ff9 call 0x4229a0
006a5ffe mov eax, dword ptr [esi]
006a6000 lea ecx, [ebp - 0x38]
006a6003 push 0x1e
006a6005 push ecx
006a6006 push 0
006a6008 push 0
006a600a push ecx
006a600b mov ecx, esi
006a600d mov dword ptr [esp], 0x40a00000
006a6014 call dword ptr [eax + 0x20]
006a6017 cmp dword ptr [edi + 0x28], 0x322
006a601e jne 0x6a606f
006a6020 mov eax, dword ptr [esi + 0x28]
006a6023 sub eax, 0xa
006a6026 cmp eax, 0x3dd
006a602b ja 0x6a606f
006a602d lea eax, [edi + 0xe50]
006a6033 push esi
006a6034 mov ecx, eax
006a6036 call 0x422d00
006a603b test al, al
006a603d jne 0x6a6200
006a6043 push esi
006a6044 lea ecx, [edi + 0xe50]
006a604a call 0x422ce0
006a604f cmp dword ptr [edi + 0x2c], 1
006a6053 jne 0x6a6062
006a6055 movss xmm0, dword ptr [0xb6a9ac]
006a605d jmp 0x6a61e0
006a6062 movss xmm0, dword ptr [0xb6a938]
006a606a jmp 0x6a61e0
006a606f mov eax, dword ptr [esi + 0x28]
006a6072 sub eax, 0xa
006a6075 cmp eax, 0x3dd
006a607a ja 0x6a6200
006a6080 push 0
006a6082 mov ecx, edi
006a6084 call 0x68cf40
006a6089 test al, al
006a608b je 0x6a6200
006a6091 push 0
006a6093 mov ecx, esi
006a6095 call 0x68cf40
006a609a test al, al
006a609c je 0x6a6200
006a60a2 push 0
006a60a4 push 0x100
006a60a9 mov ecx, edi
006a60ab call 0x4122f0
006a60b0 push 0
006a60b2 push 0x100
006a60b7 mov ecx, esi
006a60b9 mov byte ptr [ebp - 0xf1], al
006a60bf call 0x4122f0
006a60c4 cmp byte ptr [ebp - 0xf1], al
006a60ca jne 0x6a60e0
006a60cc cmp dword ptr [edi + 0x31c], esi
006a60d2 je 0x6a60e0
006a60d4 cmp dword ptr [edi + 0xe88], esi
006a60da jne 0x6a6200
006a60e0 movss xmm0, dword ptr [edi + 0x2e0]
006a60e8 xorps xmm1, xmm1
006a60eb comiss xmm0, xmm1
006a60ee jbe 0x6a6200
006a60f4 lea eax, [edi + 0xe50]
006a60fa push esi
006a60fb mov ecx, eax
006a60fd call 0x422d00
006a6102 test al, al
006a6104 jne 0x6a6200
006a610a push esi
006a610b lea ecx, [edi + 0xe50]
006a6111 call 0x422ce0
006a6116 movss xmm0, dword ptr [edi + 0x2dc]
006a611e addss xmm0, dword ptr [0xb6ab10]
006a6126 divss xmm0, dword ptr [0xb6aafc]
006a612e call 0x68f440
006a6133 cmp dword ptr [edi + 0x28], 0x27
006a6137 mulss xmm0, dword ptr [0xb6aa1c]
006a613f movss dword ptr [ebp - 0xf0], xmm0
006a6147 jne 0x6a615f
006a6149 cmp dword ptr [edi + 0x2c], 0x16
006a614d jne 0x6a615f
006a614f movss xmm0, dword ptr [0xb6a98c]
006a6157 movss dword ptr [ebp - 0xf0], xmm0
006a615f push 0
006a6161 push 0x20000000
006a6166 mov ecx, esi
006a6168 call 0x4122f0
006a616d test al, al
006a616f je 0x6a6195
006a6171 movss xmm0, dword ptr [ebp - 0xf0]
006a6179 mulss xmm0, dword ptr [0xb6a38c]
006a6181 movss xmm1, dword ptr [0xb6a8a0]
006a6189 minss xmm1, xmm0
006a618d movss dword ptr [ebp - 0xf0], xmm1
006a6195 push 0x100000
006a619a push 0
006a619c mov ecx, esi
006a619e call 0x4122f0
006a61a3 test al, al
006a61a5 je 0x6a61d8
006a61a7 push 0
006a61a9 push 0x20000100
006a61ae mov ecx, edi
006a61b0 call 0x4122f0
006a61b5 test al, al
006a61b7 jne 0x6a61d8
006a61b9 mov eax, dword ptr [edi]
006a61bb mov ecx, edi
006a61bd mov eax, dword ptr [eax + 0x48]
006a61c0 call eax
006a61c2 movss xmm0, dword ptr [ebp - 0xf0]
006a61ca test al, al
006a61cc jne 0x6a61e0
006a61ce mulss xmm0, dword ptr [0xb6a480]
006a61d6 jmp 0x6a61e0
006a61d8 movss xmm0, dword ptr [ebp - 0xf0]
006a61e0 push edi
006a61e1 lea ecx, [ebp - 0x38]
006a61e4 call 0x4229a0
006a61e9 mov eax, dword ptr [esi]
006a61eb lea ecx, [ebp - 0x38]
006a61ee push 0x1e
006a61f0 push ecx
006a61f1 push 0
006a61f3 push 0
006a61f5 push ecx
006a61f6 mov ecx, esi
006a61f8 movss dword ptr [esp], xmm0
006a61fd call dword ptr [eax + 0x20]
006a6200 push 0x8000
006a6205 push 0
006a6207 mov ecx, edi
006a6209 call 0x4122f0
006a620e test al, al
006a6210 je 0x6a6449
006a6216 movss xmm1, dword ptr [edi + 0x264]
006a621e movss xmm0, dword ptr [edi + 0x260]
006a6226 mulss xmm0, xmm0
006a622a mulss xmm1, xmm1
006a622e addss xmm0, xmm1
006a6232 call 0x4228c0
006a6237 comiss xmm0, dword ptr [0xb6a910]
006a623e jbe 0x6a6449
006a6244 push 0x20000
006a6249 push 0
006a624b mov ecx, edi
006a624d call 0x4122f0
006a6252 test al, al
006a6254 je 0x6a63ce
006a625a mov eax, dword ptr [esi + 0x28]
006a625d sub eax, 0xa
006a6260 cmp eax, 0x3dd
006a6265 ja 0x6a63ce
006a626b push 0x20000
006a6270 push 0
006a6272 mov ecx, esi
006a6274 call 0x4122f0
006a6279 test al, al
006a627b je 0x6a63a4
006a6281 movss xmm0, dword ptr [esi + 0x294]
006a6289 lea ecx, [ebp - 0x110]
006a628f movss xmm1, dword ptr [esi + 0x298]
006a6297 subss xmm0, dword ptr [edi + 0x294]
006a629f subss xmm1, dword ptr [edi + 0x298]
006a62a7 movss dword ptr [ebp - 0x110], xmm0
006a62af movss dword ptr [ebp - 0x10c], xmm1
006a62b7 call 0x9624f0
006a62bc lea eax, [ebp - 0x100]
006a62c2 push eax
006a62c3 lea ecx, [edi + 0x2b8]
006a62c9 call 0x962560
006a62ce movss xmm0, dword ptr [ebp - 0x110]
006a62d6 lea eax, [ebp - 0x18]
006a62d9 addss xmm0, dword ptr [ebp - 0x100]
006a62e1 push eax
006a62e2 lea ecx, [ebp - 0x11c]
006a62e8 movss dword ptr [ebp - 0x11c], xmm0
006a62f0 movss xmm0, dword ptr [ebp - 0x10c]
006a62f8 addss xmm0, dword ptr [ebp - 0xfc]
006a6300 movss dword ptr [ebp - 0x118], xmm0
006a6308 call 0x962560
006a630d push 0
006a630f push 1
006a6311 mov ecx, esi
006a6313 movss xmm0, dword ptr [eax]
006a6317 mulss xmm0, dword ptr [0xb6a9bc]
006a631f movss dword ptr [ebp - 0x110], xmm0
006a6327 movss xmm0, dword ptr [eax + 4]
006a632c mulss xmm0, dword ptr [0xb6a9bc]
006a6334 movss dword ptr [ebp - 0x10c], xmm0
006a633c call 0x4122f0
006a6341 mov ecx, dword ptr [esi + 0x164]
006a6347 and dword ptr [esi + 0x160], 0xfffffffe
006a634e mov dword ptr [esi + 0x164], ecx
006a6354 lea ecx, [ebp - 0x38]
006a6357 push edi
006a6358 mov byte ptr [ebp - 0xf1], al
006a635e call 0x4229a0
006a6363 push 1
006a6365 push 0xc8
006a636a lea eax, [ebp - 0x110]
006a6370 mov ecx, esi
006a6372 push eax
006a6373 lea eax, [ebp - 0x38]
006a6376 push eax
006a6377 call 0x68ee80
006a637c cmp byte ptr [ebp - 0xf1], 0
006a6383 je 0x6a63c5
006a6385 mov eax, dword ptr [esi + 0x164]
006a638b mov ecx, edi
006a638d or dword ptr [esi + 0x160], 1
006a6394 mov dword ptr [esi + 0x164], eax
006a639a mov eax, dword ptr [edi]
006a639c call dword ptr [eax + 0x24]
006a639f jmp 0x6a6449
006a63a4 mov edx, dword ptr [esi]
006a63a6 lea ecx, [ebp - 0x38]
006a63a9 push 0x1e
006a63ab call 0x427290
006a63b0 push eax
006a63b1 push 0
006a63b3 push 0x1000000
006a63b8 push ecx
006a63b9 mov ecx, esi
006a63bb mov dword ptr [esp], 0x420c0000
006a63c2 call dword ptr [edx + 0x20]
006a63c5 mov eax, dword ptr [edi]
006a63c7 mov ecx, edi
006a63c9 call dword ptr [eax + 0x24]
006a63cc jmp 0x6a6449
006a63ce push 0
006a63d0 mov ecx, esi
006a63d2 call 0x684630
006a63d7 test al, al
006a63d9 je 0x6a6449
006a63db push 0x10000
006a63e0 push 0
006a63e2 mov ecx, edi
006a63e4 call 0x4122f0
006a63e9 test al, al
006a63eb je 0x6a6449
006a63ed lea eax, [edi + 0xe50]
006a63f3 push esi
006a63f4 mov ecx, eax
006a63f6 call 0x422d00
006a63fb test al, al
006a63fd jne 0x6a6449
006a63ff push esi
006a6400 lea ecx, [edi + 0xe50]
006a6406 call 0x422ce0
006a640b mov ecx, dword ptr [0xbfd65c]
006a6411 call 0x427780
006a6416 mov edx, dword ptr [esi]
006a6418 lea ecx, [ebp - 0x168]
006a641e dec eax
006a641f push 0x1e
006a6421 movd xmm1, eax
006a6425 cvtdq2ps xmm1, xmm1
006a6428 call 0x427290
006a642d push eax
006a642e push 0
006a6430 push 0
006a6432 addss xmm1, xmm1
006a6436 push ecx
006a6437 mov ecx, esi
006a6439 addss xmm1, dword ptr [0xb6a974]
006a6441 movss dword ptr [esp], xmm1
006a6446 call dword ptr [edx + 0x20]
006a6449 cmp dword ptr [edi + 0x28], 0x27
006a644d jne 0x6a41dc
006a6453 cmp dword ptr [edi + 0x2c], 0x16
006a6457 jne 0x6a41dc
006a645d push 0
006a645f push 0x100
006a6464 mov ecx, edi
006a6466 call 0x4122f0
006a646b test al, al
006a646d je 0x6a41dc
006a6473 mov eax, dword ptr [esi + 0x28]
006a6476 sub eax, 0xa
006a6479 cmp eax, 0x3dd
006a647e jbe 0x6a46d7
006a6484 xor al, al
006a6486 jmp 0x6a46d9
006a648b int3 
006a648c int3 
006a648d int3 
006a648e int3 
006a648f int3 
006a6490 push ebp
006a6491 mov ebp, esp
006a6493 mov eax, dword ptr [ebp + 8]
006a6496 push esi
006a6497 mov esi, ecx
006a6499 push edi
006a649a cmp dword ptr [esi + 0xbc8], eax
006a64a0 je 0x6a64e9
006a64a2 push 1
006a64a4 mov dword ptr [esi + 0xbc8], eax
006a64aa call 0x692080
006a64af cmp dword ptr [esi + 0x68], 0x10
006a64b3 lea eax, [esi + 0x54]
006a64b6 jb 0x6a64ba
006a64b8 mov eax, dword ptr [eax]
006a64ba push 1
006a64bc push eax
006a64bd lea ecx, [esi + 0x3c]
006a64c0 call 0x405740
006a64c5 test al, al
006a64c7 je 0x6a64e9
006a64c9 mov eax, dword ptr [esi + 0x70]
006a64cc test eax, eax
006a64ce je 0x6a64e9
006a64d0 lea ecx, [esi + 0x6c]
006a64d3 xorps xmm1, xmm1
006a64d6 call 0x403c00
006a64db mov eax, dword ptr [esi + 0x70]
006a64de test eax, eax
006a64e0 je 0x6a64e9
006a64e2 mov byte ptr [esi + 0x80], 0
006a64e9 mov eax, dword ptr [esi]
006a64eb mov ecx, esi
006a64ed call dword ptr [eax + 0x5c]
006a64f0 pop edi
006a64f1 pop esi
006a64f2 pop ebp
006a64f3 ret 8
006a64f6 int3 
006a64f7 int3 
006a64f8 int3 
006a64f9 int3 
006a64fa int3 
006a64fb int3 
006a64fc int3 
006a64fd int3 
006a64fe int3 
006a64ff int3 
006a6500 push ebp
006a6501 mov ebp, esp
006a6503 and esp, 0xfffffff8
006a6506 mov edx, dword ptr [ebp + 8]
006a6509 mov eax, dword ptr [ecx + 0x28]
006a650c mov dword ptr [edx], eax
006a650e mov eax, dword ptr [ecx + 0x2c]
006a6511 mov dword ptr [edx + 4], eax
006a6514 mov eax, dword ptr [ecx + 0x30]
006a6517 mov dword ptr [edx + 8], eax
006a651a mov eax, dword ptr [ecx + 0xbb4]
006a6520 mov dword ptr [edx + 0xc], eax
006a6523 mov eax, dword ptr [ecx + 0x2d8]
006a6529 mov dword ptr [edx + 0x10], eax
006a652c mov eax, dword ptr [ecx + 0x2dc]
006a6532 mov dword ptr [edx + 0x14], eax
006a6535 mov eax, dword ptr [ecx + 0x160]
006a653b and eax, 0x20000000
006a6540 or eax, 0
006a6543 je 0x6a6559
006a6545 cmp dword ptr [ecx + 0xe6c], -1
006a654c je 0x6a6559
006a654e mov al, 1
006a6550 mov byte ptr [edx + 0x18], al
006a6553 mov esp, ebp
006a6555 pop ebp
006a6556 ret 4
006a6559 xor al, al
006a655b mov byte ptr [edx + 0x18], al
006a655e mov esp, ebp
006a6560 pop ebp
006a6561 ret 4
006a6564 int3 
006a6565 int3 
006a6566 int3 
006a6567 int3 
006a6568 int3 
006a6569 int3 
006a656a int3 
006a656b int3 
006a656c int3 
006a656d int3 
006a656e int3 
006a656f int3 
006a6570 push ebp
006a6571 mov ebp, esp
006a6573 sub esp, 0x58
006a6576 mov eax, dword ptr [0xbaa3b4]
006a657b xor eax, ebp
006a657d mov dword ptr [ebp - 8], eax
006a6580 push ebx
006a6581 push esi
006a6582 push edi
006a6583 mov edi, ecx
006a6585 cmp byte ptr [edi + 0xbb3], 0
006a658c je 0x6a6598
006a658e cmp byte ptr [ebp + 0x10], 0
006a6592 je 0x6a6cfa
006a6598 movss xmm1, dword ptr [edi + 0x2dc]
006a65a0 lea ebx, [edi + 0x2dc]
006a65a6 movq xmm0, qword ptr [0xa08c2c]
006a65ae mov eax, dword ptr [0xa08c34]
006a65b3 mov esi, dword ptr [ebp + 8]
006a65b6 movq qword ptr [ebp - 0x48], xmm0
006a65bb movaps xmm0, xmm1
006a65be addss xmm0, xmm1
006a65c2 mov dword ptr [ebp - 0x38], eax
006a65c5 mov dword ptr [ebp - 0x40], eax
006a65c8 mov eax, dword ptr [edi]
006a65ca movss dword ptr [ebp - 0x54], xmm1
006a65cf movss dword ptr [ebp - 0x50], xmm1
006a65d4 movss dword ptr [ebx], xmm0
006a65d8 call dword ptr [eax + 0x5c]
006a65db movss xmm0, dword ptr [edi + 0x2e0]
006a65e3 xorps xmm1, xmm1
006a65e6 comiss xmm0, xmm1
006a65e9 jbe 0x6a65f5
006a65eb mov dword ptr [edi + 0x2e0], 0x40000000
006a65f5 mov eax, dword ptr [ebp + 0xc]
006a65f8 mov byte ptr [edi + 0xbb3], 1
006a65ff mov dword ptr [edi + 0xbb4], eax
006a6605 test eax, eax
006a6607 jns 0x6a6790
006a660d test esi, esi
006a660f jne 0x6a6621
006a6611 push 0xb4d6c4
006a6616 push 3
006a6618 call 0x95e330
006a661d add esp, 8
006a6620 int3 
006a6621 mov ecx, dword ptr [ebp - 0x48]
006a6624 mov edx, esi
006a6626 shr edx, cl
006a6628 mov ecx, dword ptr [ebp - 0x44]
006a662b xor edx, esi
006a662d mov eax, edx
006a662f shl eax, cl
006a6631 mov ecx, dword ptr [ebp - 0x38]
006a6634 xor eax, edx
006a6636 mov esi, eax
006a6638 shr esi, cl
006a663a xor esi, eax
006a663c mov ecx, dword ptr [0xbfd65c]
006a6642 mov eax, esi
006a6644 mov dword ptr [ebp - 0x4c], esi
006a6647 shr eax, 0x1f
006a664a movd xmm0, esi
006a664e cvtdq2pd xmm0, xmm0
006a6652 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
006a665b cvtpd2ps xmm1, xmm0
006a665f movss xmm0, dword ptr [0xb6a214]
006a6667 mulss xmm1, dword ptr [0xb6a198]
006a666f comiss xmm0, xmm1
006a6672 jbe 0x6a6696
006a6674 cmp dword ptr [ecx], 5
006a6677 jl 0x6a6696
006a6679 movss xmm0, dword ptr [0xb6a1fc]
006a6681 mov eax, 0x19
006a6686 comiss xmm0, xmm1
006a6689 mov ecx, 6
006a668e cmova eax, ecx
006a6691 jmp 0x6a678a
006a6696 movss xmm0, dword ptr [0xb6a274]
006a669e comiss xmm0, xmm1
006a66a1 jbe 0x6a66be
006a66a3 cmp dword ptr [ecx], 5
006a66a6 jl 0x6a66be
006a66a8 push 4
006a66aa lea ecx, [ebp - 0x4c]
006a66ad call 0x7a7d50
006a66b2 mov eax, dword ptr [eax*4 + 0xb492c0]
006a66b9 jmp 0x6a678a
006a66be movss xmm0, dword ptr [0xb6a304]
006a66c6 comiss xmm0, xmm1
006a66c9 jbe 0x6a6711
006a66cb test esi, esi
006a66cd jne 0x6a66df
006a66cf push 0xb4d6c4
006a66d4 push 3
006a66d6 call 0x95e330
006a66db add esp, 8
006a66de int3 
006a66df mov ecx, dword ptr [ebp - 0x48]
006a66e2 mov eax, esi
006a66e4 shr eax, cl
006a66e6 mov ecx, dword ptr [ebp - 0x44]
006a66e9 xor eax, esi
006a66eb mov edx, eax
006a66ed shl edx, cl
006a66ef mov ecx, dword ptr [ebp - 0x38]
006a66f2 xor edx, eax
006a66f4 mov esi, edx
006a66f6 mov eax, 0xaaaaaaab
006a66fb shr esi, cl
006a66fd xor esi, edx
006a66ff mul esi
006a6701 shr edx, 1
006a6703 lea eax, [edx + edx*2]
006a6706 sub esi, eax
006a6708 mov eax, dword ptr [esi*4 + 0xb49418]
006a670f jmp 0x6a678a
006a6711 movss xmm0, dword ptr [0xb6a3b0]
006a6719 comiss xmm0, xmm1
006a671c jbe 0x6a673f
006a671e xor eax, eax
006a6720 cmp dword ptr [ecx], 3
006a6723 lea ecx, [ebp - 0x4c]
006a6726 setge al
006a6729 lea eax, [eax*2 + 4]
006a6730 push eax
006a6731 call 0x7a7d50
006a6736 mov eax, dword ptr [eax*4 + 0xb49400]
006a673d jmp 0x6a678a
006a673f movss xmm0, dword ptr [0xb6a3f8]
006a6747 comiss xmm0, xmm1
006a674a jbe 0x6a6764
006a674c cmp dword ptr [ecx], 5
006a674f jl 0x6a6764
006a6751 push 4
006a6753 lea ecx, [ebp - 0x4c]
006a6756 call 0x7a7d50
006a675b mov eax, dword ptr [eax*4 + 0xb49354]
006a6762 jmp 0x6a678a
006a6764 cmp dword ptr [ecx], 3
006a6767 lea ecx, [ebp - 0x4c]
006a676a jl 0x6a677c
006a676c push 7
006a676e call 0x7a7d50
006a6773 mov eax, dword ptr [eax*4 + 0xb49378]
006a677a jmp 0x6a678a
006a677c push 6
006a677e call 0x7a7d50
006a6783 mov eax, dword ptr [eax*4 + 0xb492d0]
006a678a mov dword ptr [edi + 0xbb4], eax
006a6790 cmp eax, 0xc
006a6793 jne 0x6a67cc
006a6795 mov ecx, dword ptr [edi + 0x28]
006a6798 cmp ecx, 0xf0
006a679e je 0x6a67b8
006a67a0 cmp ecx, 0xf2
006a67a6 je 0x6a67b8
006a67a8 cmp ecx, 0xf1
006a67ae je 0x6a67b8
006a67b0 cmp ecx, 0x130
006a67b6 jne 0x6a67cc
006a67b8 movss xmm1, dword ptr [0xb6a660]
006a67c0 mov dword ptr [edi + 0xbb4], 0
006a67ca jmp 0x6a6844
006a67cc cmp eax, 6
006a67cf jne 0x6a67ee
006a67d1 cmp dword ptr [edi + 0x28], 0x379
006a67d8 jne 0x6a67ee
006a67da movss xmm1, dword ptr [0xb6a660]
006a67e2 mov dword ptr [edi + 0xbb4], 0x11
006a67ec jmp 0x6a6844
006a67ee movss xmm1, dword ptr [0xb6a660]
006a67f6 cmp eax, 0x12
006a67f9 jne 0x6a6837
006a67fb mov eax, dword ptr [edi + 0x288]
006a6801 movss xmm0, dword ptr [edi + 0x2c8]
006a6809 mulss xmm0, dword ptr [0xb6a480]
006a6811 push dword ptr [eax + 0x48]
006a6814 push dword ptr [edi + 0x2d0]
006a681a push dword ptr [edi + 0x2cc]
006a6820 push ecx
006a6821 mov ecx, edi
006a6823 movss dword ptr [esp], xmm0
006a6828 call 0x6843a0
006a682d movss xmm1, dword ptr [0xb6a480]
006a6835 jmp 0x6a6844
006a6837 cmp eax, 0x13
006a683a jne 0x6a6844
006a683c movss xmm1, dword ptr [0xb6a6f0]
006a6844 movss dword ptr [edi + 0xb88], xmm1
006a684c mov ecx, edi
006a684e mulss xmm1, dword ptr [edi + 0x30c]
006a6856 push 0
006a6858 movaps xmm0, xmm1
006a685b mulss xmm1, dword ptr [0xbc7a2c]
006a6863 mulss xmm0, dword ptr [0xbc7a28]
006a686b movss dword ptr [edi + 0xdc], xmm1
006a6873 movss dword ptr [edi + 0xd8], xmm0
006a687b call 0x692080
006a6880 mov eax, dword ptr [edi + 0xbb4]
006a6886 cmp eax, 0x19
006a6889 ja 0x6a6cc6
006a688f movzx eax, byte ptr [eax + 0x6a6d54]
006a6896 jmp dword ptr [eax*4 + 0x6a6d10]
006a689d movss xmm0, dword ptr [ebx]
006a68a1 mulss xmm0, dword ptr [0xb6a6ac]
006a68a9 movss dword ptr [ebx], xmm0
006a68ad jmp 0x6a6cc6
006a68b2 movss xmm0, dword ptr [ebx]
006a68b6 mulss xmm0, dword ptr [0xb6a53c]
006a68be mov dword ptr [edi + 0xafc], 0x3faa9fbe
006a68c8 movss dword ptr [ebx], xmm0
006a68cc jmp 0x6a6cc6
006a68d1 movss xmm0, dword ptr [ebx]
006a68d5 mulss xmm0, dword ptr [0xb6a3d8]
006a68dd movss dword ptr [ebx], xmm0
006a68e1 mov dword ptr [edi + 0xafc], 0x3f4ccccd
006a68eb jmp 0x6a6cc6
006a68f0 mov dword ptr [edi + 0x17c], 3
006a68fa jmp 0x6a6cc6
006a68ff call 0x6c3d90
006a6904 xor edx, edx
006a6906 mov ecx, 0x1e
006a690b div ecx
006a690d add edx, 0x3c
006a6910 mov dword ptr [edi + 0xbb8], edx
006a6916 jmp 0x6a6cc6
006a691b call 0x6c3d90
006a6920 xor edx, edx
006a6922 mov ecx, 0x14
006a6927 div ecx
006a6929 add edx, 0x28
006a692c mov dword ptr [edi + 0xaf8], edx
006a6932 jmp 0x6a6cc6
006a6937 call 0x6c3d90
006a693c mov ecx, dword ptr [0xbfd65c]
006a6942 push eax
006a6943 push 0
006a6945 push edi
006a6946 push 0xc02fec
006a694b lea eax, [edi + 0x294]
006a6951 push eax
006a6952 push 0x39
006a6954 push 0x3e8
006a6959 call 0x422e20
006a695e mov ecx, dword ptr [eax + 0x314]
006a6964 lea esi, [eax + 0x314]
006a696a test ecx, ecx
006a696c je 0x6a6980
006a696e mov dword ptr [ebp - 0x38], esi
006a6971 lea eax, [ebp - 0x38]
006a6974 push eax
006a6975 add ecx, 0x324
006a697b call 0x4bc3c0
006a6980 push esi
006a6981 mov ecx, edi
006a6983 mov dword ptr [esi], edi
006a6985 call 0x4bae70
006a698a jmp 0x6a6cc6
006a698f call 0x6c3d90
006a6994 mov ecx, dword ptr [0xbfd65c]
006a699a push eax
006a699b push 1
006a699d push edi
006a699e push 0xc02fec
006a69a3 lea eax, [edi + 0x294]
006a69a9 push eax
006a69aa push 0x39
006a69ac push 0x3e8
006a69b1 call 0x422e20
006a69b6 mov ecx, dword ptr [eax + 0x314]
006a69bc lea esi, [eax + 0x314]
006a69c2 test ecx, ecx
006a69c4 je 0x6a69d8
006a69c6 lea eax, [ebp - 0x38]
006a69c9 mov dword ptr [ebp - 0x38], esi
006a69cc push eax
006a69cd add ecx, 0x324
006a69d3 call 0x4bc3c0
006a69d8 push esi
006a69d9 mov ecx, edi
006a69db mov dword ptr [esi], edi
006a69dd call 0x4bae70
006a69e2 jmp 0x6a6cc6
006a69e7 call 0x6c3d90
006a69ec mov ecx, dword ptr [0xbfd65c]
006a69f2 push eax
006a69f3 push 2
006a69f5 push edi
006a69f6 push 0xc02fec
006a69fb lea eax, [edi + 0x294]
006a6a01 push eax
006a6a02 push 0x39
006a6a04 push 0x3e8
006a6a09 call 0x422e20
006a6a0e mov ecx, dword ptr [eax + 0x314]
006a6a14 mov dword ptr [ebp - 0x3c], eax
006a6a17 lea esi, [eax + 0x314]
006a6a1d test ecx, ecx
006a6a1f je 0x6a6a33
006a6a21 lea eax, [ebp - 0x38]
006a6a24 mov dword ptr [ebp - 0x38], esi
006a6a27 push eax
006a6a28 add ecx, 0x324
006a6a2e call 0x4bc3c0
006a6a33 push esi
006a6a34 mov ecx, edi
006a6a36 mov dword ptr [esi], edi
006a6a38 call 0x4bae70
006a6a3d mov esi, dword ptr [ebp - 0x3c]
006a6a40 movss xmm3, dword ptr [0xb6a350]
006a6a48 movss xmm1, dword ptr [0xb6a614]
006a6a50 movaps xmm2, xmm3
006a6a53 push 1
006a6a55 mov edx, dword ptr [esi]
006a6a57 push 0
006a6a59 push 0xff
006a6a5e push -1
006a6a60 push ecx
006a6a61 lea ecx, [ebp - 0x34]
006a6a64 mov dword ptr [esp], 0x3f800000
006a6a6b call 0x4325d0
006a6a70 push eax
006a6a71 mov ecx, esi
006a6a73 call dword ptr [edx + 0x38]
006a6a76 jmp 0x6a6cc6
006a6a7b mov cl, byte ptr [ebp + 0x10]
006a6a7e test cl, cl
006a6a80 jne 0x6a6cc9
006a6a86 call 0x6c3d90
006a6a8b mov ecx, dword ptr [0xbfd65c]
006a6a91 push eax
006a6a92 push 0
006a6a94 push edi
006a6a95 push 0xc02fec
006a6a9a lea eax, [edi + 0x294]
006a6aa0 push eax
006a6aa1 push 0
006a6aa3 push 0x60
006a6aa5 call 0x422e20
006a6aaa mov ecx, dword ptr [eax + 0x314]
006a6ab0 lea esi, [eax + 0x314]
006a6ab6 test ecx, ecx
006a6ab8 je 0x6a6980
006a6abe mov dword ptr [ebp - 0x3c], esi
006a6ac1 lea eax, [ebp - 0x3c]
006a6ac4 jmp 0x6a6974
006a6ac9 movss xmm0, dword ptr [ebx]
006a6acd mulss xmm0, dword ptr [0xb6a3d8]
006a6ad5 movss dword ptr [ebx], xmm0
006a6ad9 movss xmm0, dword ptr [edi + 0xafc]
006a6ae1 mulss xmm0, dword ptr [0xb6a6ac]
006a6ae9 movss dword ptr [edi + 0xafc], xmm0
006a6af1 jmp 0x6a6cc6
006a6af6 movss xmm0, dword ptr [ebx]
006a6afa mulss xmm0, dword ptr [0xb6a6f0]
006a6b02 movss dword ptr [ebx], xmm0
006a6b06 movss xmm0, dword ptr [edi + 0xafc]
006a6b0e mulss xmm0, dword ptr [0xb6a5a4]
006a6b16 movss dword ptr [edi + 0xafc], xmm0
006a6b1e movss xmm0, dword ptr [edi + 0x2e0]
006a6b26 xorps xmm1, xmm1
006a6b29 comiss xmm0, xmm1
006a6b2c mov cl, byte ptr [ebp + 0x10]
006a6b2f jbe 0x6a6cc9
006a6b35 mov dword ptr [edi + 0x2e0], 0x40800000
006a6b3f jmp 0x6a6cc9
006a6b44 movss xmm0, dword ptr [ebx]
006a6b48 mulss xmm0, dword ptr [0xb6a864]
006a6b50 movss dword ptr [ebx], xmm0
006a6b54 jmp 0x6a6cc6
006a6b59 movss xmm0, dword ptr [ebx]
006a6b5d mulss xmm0, dword ptr [0xb6a6f0]
006a6b65 mov dword ptr [edi + 0xafc], 0x3faa9fbe
006a6b6f movss dword ptr [ebx], xmm0
006a6b73 call 0x6c3d90
006a6b78 xor edx, edx
006a6b7a mov ecx, 0x14
006a6b7f div ecx
006a6b81 add edx, 0x28
006a6b84 mov dword ptr [edi + 0xaf8], edx
006a6b8a call 0x6c3d90
006a6b8f push eax
006a6b90 push 0
006a6b92 push edi
006a6b93 push 0xc02fec
006a6b98 lea ecx, [edi + 0x294]
006a6b9e push ecx
006a6b9f mov ecx, dword ptr [0xbfd65c]
006a6ba5 push 0x39
006a6ba7 push 0x3e8
006a6bac call 0x422e20
006a6bb1 mov ecx, dword ptr [eax + 0x314]
006a6bb7 lea esi, [eax + 0x314]
006a6bbd test ecx, ecx
006a6bbf je 0x6a6bd3
006a6bc1 lea eax, [ebp - 0x3c]
006a6bc4 mov dword ptr [ebp - 0x3c], esi
006a6bc7 push eax
006a6bc8 add ecx, 0x324
006a6bce call 0x4bc3c0
006a6bd3 push esi
006a6bd4 mov ecx, edi
006a6bd6 mov dword ptr [esi], edi
006a6bd8 call 0x4bae70
006a6bdd cmp byte ptr [ebp + 0x10], 0
006a6be1 jne 0x6a6c33
006a6be3 call 0x6c3d90
006a6be8 mov ecx, dword ptr [0xbfd65c]
006a6bee push eax
006a6bef push 0
006a6bf1 push edi
006a6bf2 push 0xc02fec
006a6bf7 lea eax, [edi + 0x294]
006a6bfd push eax
006a6bfe push 0
006a6c00 push 0x60
006a6c02 call 0x422e20
006a6c07 mov ecx, dword ptr [eax + 0x314]
006a6c0d lea esi, [eax + 0x314]
006a6c13 test ecx, ecx
006a6c15 je 0x6a6c29
006a6c17 lea eax, [ebp - 0x3c]
006a6c1a mov dword ptr [ebp - 0x3c], esi
006a6c1d push eax
006a6c1e add ecx, 0x324
006a6c24 call 0x4bc3c0
006a6c29 push esi
006a6c2a mov ecx, edi
006a6c2c mov dword ptr [esi], edi
006a6c2e call 0x4bae70
006a6c33 mov ecx, dword ptr [0xbfd65c]
006a6c39 mov eax, dword ptr [ecx + 0x18190]
006a6c3f cmp byte ptr [eax], 0
006a6c42 jne 0x6a6c49
006a6c44 or ecx, 0xffffffff
006a6c47 jmp 0x6a6c55
006a6c49 mov ecx, dword ptr [ecx + 0x1a30dc]
006a6c4f sub ecx, dword ptr [eax + 0x11f0]
006a6c55 mov eax, 0xb60b60b7
006a6c5a movss xmm2, dword ptr [0xb6a614]
006a6c62 imul ecx
006a6c64 movaps xmm3, xmm2
006a6c67 push ecx
006a6c68 add edx, ecx
006a6c6a mov dword ptr [esp], 0x3f800000
006a6c71 sar edx, 6
006a6c74 mov eax, edx
006a6c76 shr eax, 0x1f
006a6c79 add eax, edx
006a6c7b imul eax, eax, 0x5a
006a6c7e sub ecx, eax
006a6c80 movd xmm1, ecx
006a6c84 lea ecx, [ebp - 0x4c]
006a6c87 cvtdq2ps xmm1, xmm1
006a6c8a mulss xmm1, dword ptr [0xb6ac40]
006a6c92 divss xmm1, dword ptr [0xb6aae4]
006a6c9a call 0x65c840
006a6c9f movss xmm3, dword ptr [ebp - 0x44]
006a6ca4 lea ecx, [ebp - 0x34]
006a6ca7 movss xmm2, dword ptr [ebp - 0x48]
006a6cac movss xmm1, dword ptr [ebp - 0x4c]
006a6cb1 mov dword ptr [esp], 0x3f800000
006a6cb8 call 0x4325d0
006a6cbd push eax
006a6cbe lea ecx, [edi + 0x3c]
006a6cc1 call 0x68f460
006a6cc6 mov cl, byte ptr [ebp + 0x10]
006a6cc9 cmp dword ptr [edi + 0x28], 0x10
006a6ccd jne 0x6a6ce7
006a6ccf cmp dword ptr [edi + 0x2c], 2
006a6cd3 jne 0x6a6ce7
006a6cd5 movss xmm0, dword ptr [ebx]
006a6cd9 lea eax, [ebp - 0x50]
006a6cdc comiss xmm0, dword ptr [ebp - 0x54]
006a6ce0 cmovbe eax, ebx
006a6ce3 mov eax, dword ptr [eax]
006a6ce5 mov dword ptr [ebx], eax
006a6ce7 test cl, cl
006a6ce9 jne 0x6a6cf3
006a6ceb mov eax, dword ptr [ebx]
006a6ced mov dword ptr [edi + 0x2d8], eax
006a6cf3 mov eax, dword ptr [edi]
006a6cf5 mov ecx, edi
006a6cf7 call dword ptr [eax + 0x5c]
006a6cfa mov ecx, dword ptr [ebp - 8]
006a6cfd pop edi
006a6cfe pop esi
006a6cff xor ecx, ebp
006a6d01 pop ebx
006a6d02 call 0x9eacd7
006a6d07 mov esp, ebp
006a6d09 pop ebp
006a6d0a ret 0xc
006a6d0d nop dword ptr [eax]
006a6d10 popfd 
006a6d11 push 0x68b2006a
006a6d16 push 0
006a6d18 loope 0x6a6d82
006a6d1a push 0
006a6d1c shr dword ptr [eax + 0x6a], 1
006a6d1f add al, dh
006a6d21 push 0x68ff006a
006a6d26 push 0
006a6d28 sbb ebp, dword ptr [ecx + 0x6a]
006a6d2b add byte ptr [edi], dh
006a6d2d imul ebp, dword ptr [edx], 0x6a698f
006a6d34 jnp 0x6a6da0
006a6d36 push 0
006a6d38 leave 
006a6d39 push 0x6a
006a6d3b add dh, dh
006a6d3d push 0x6a
006a6d3f add bh, ah
006a6d41 imul ebp, dword ptr [edx], 0x6a6b44
006a6d48 push ds
006a6d49 imul ebp, dword ptr [edx], 0x59
006a6d4d imul ebp, dword ptr [edx], -0x3a
006a6d51 insb byte ptr es:[edi], dx
006a6d52 push 0
006a6d54 add byte ptr [ecx], al
006a6d56 adc byte ptr [eax], dl
006a6d58 add dl, byte ptr [eax]
006a6d5a adc byte ptr [ebx], al
006a6d5c add al, 5
006a6d5e push es
006a6d5f pop es
006a6d60 adc byte ptr [eax], dl
006a6d62 adc byte ptr [eax], dl
006a6d64 or byte ptr [ecx], cl
006a6d66 or cl, byte ptr [ebx]
006a6d68 or al, 0x10
006a6d6a or eax, 0xcc0f100e
006a6d6f int3 
006a6d70 push ebp
006a6d71 mov ebp, esp
006a6d73 push ecx
006a6d74 push esi
006a6d75 lea esi, [ecx + 0xb3c]
006a6d7b mov ecx, dword ptr [esi]
006a6d7d test ecx, ecx
006a6d7f je 0x6a6d93
006a6d81 lea eax, [ebp - 4]
006a6d84 mov dword ptr [ebp - 4], esi
006a6d87 push eax
006a6d88 add ecx, 0x324
006a6d8e call 0x4bc3c0
006a6d93 mov ecx, dword ptr [ebp + 8]
006a6d96 mov dword ptr [esi], ecx
006a6d98 test ecx, ecx
006a6d9a je 0x6a6da2
006a6d9c push esi
006a6d9d call 0x4bae70
006a6da2 pop esi
006a6da3 mov esp, ebp
006a6da5 pop ebp
006a6da6 ret 4
006a6da9 int3 
006a6daa int3 
006a6dab int3 
006a6dac int3 
006a6dad int3 
006a6dae int3 
006a6daf int3 
006a6db0 push ebp
006a6db1 mov ebp, esp
006a6db3 push ecx
006a6db4 mov ecx, dword ptr [0xbfd65c]
006a6dba push 0
006a6dbc push 0
006a6dbe push -1
006a6dc0 push dword ptr [ebp + 0x10]
006a6dc3 mov ecx, dword ptr [ecx + 0x18190]
006a6dc9 push dword ptr [ebp + 0xc]
006a6dcc add ecx, 0x1218
006a6dd2 push dword ptr [ebp + 8]
006a6dd5 call 0x415ed0
006a6dda mov eax, dword ptr [ebp + 8]
006a6ddd pop ecx
006a6dde pop ebp
006a6ddf ret 0xc
006a6de2 int3 
006a6de3 int3 
006a6de4 int3 
006a6de5 int3 
006a6de6 int3 
006a6de7 int3 
006a6de8 int3 
006a6de9 int3 
006a6dea int3 
006a6deb int3 
006a6dec int3 
006a6ded int3 
006a6dee int3 
006a6def int3 
006a6df0 push ebp
006a6df1 mov ebp, esp
006a6df3 push ecx
006a6df4 mov eax, dword ptr [0xbfd65c]
006a6df9 xor ecx, ecx
006a6dfb push ebx
006a6dfc push esi
006a6dfd push edi
006a6dfe mov edi, dword ptr [eax + 0x18190]
006a6e04 xor ebx, ebx
006a6e06 mov dword ptr [edi + 0x1294], 0
006a6e10 mov edx, dword ptr [eax + 0x18190]
006a6e16 mov dword ptr [ebp - 4], edx
006a6e19 cmp dword ptr [edx + 0x1264], ecx
006a6e1f jbe 0x6a6ef9
006a6e25 nop word ptr [eax + eax]
006a6e30 mov eax, dword ptr [edx + 0x125c]
006a6e36 mov esi, dword ptr [eax + ebx*4]
006a6e39 mov eax, dword ptr [ebp + 0xc]
006a6e3c cmp dword ptr [esi + 0x34], eax
006a6e3f jne 0x6a6ee1
006a6e45 mov eax, dword ptr [ebp + 0x10]
006a6e48 test eax, eax
006a6e4a je 0x6a6e55
006a6e4c cmp dword ptr [esi + 0x28], eax
006a6e4f jne 0x6a6ee1
006a6e55 cmp byte ptr [ebp + 0x14], 0
006a6e59 je 0x6a6ea9
006a6e5b mov ecx, dword ptr [esi + 0x28]
006a6e5e lea eax, [ecx - 0xa]
006a6e61 cmp eax, 0x3dd
006a6e66 ja 0x6a6ee1
006a6e68 cmp ecx, 0x21
006a6e6b je 0x6a6ee1
006a6e6d cmp ecx, 0x11
006a6e70 je 0x6a6ee1
006a6e72 cmp ecx, 0x124
006a6e78 je 0x6a6ee1
006a6e7a cmp ecx, 0x375
006a6e80 jne 0x6a6e88
006a6e82 cmp dword ptr [esi + 0x2c], 0xa
006a6e86 jmp 0x6a6e9e
006a6e88 cmp ecx, 0x3c0
006a6e8e je 0x6a6ee1
006a6e90 cmp ecx, 0x3c5
006a6e96 je 0x6a6ee1
006a6e98 cmp ecx, 0xf5
006a6e9e je 0x6a6ee1
006a6ea0 cmp byte ptr [esi + 0x16b], 0
006a6ea7 jne 0x6a6ee1
006a6ea9 mov ecx, dword ptr [edi + 0x1294]
006a6eaf lea eax, [ecx + 1]
006a6eb2 cmp eax, dword ptr [edi + 0x1290]
006a6eb8 jbe 0x6a6ed2
006a6eba push 0xb3f428
006a6ebf push 3
006a6ec1 call 0x95e330
006a6ec6 mov ecx, dword ptr [edi + 0x1294]
006a6ecc add esp, 8
006a6ecf mov edx, dword ptr [ebp - 4]
006a6ed2 mov eax, dword ptr [edi + 0x128c]
006a6ed8 mov dword ptr [eax + ecx*4], esi
006a6edb inc dword ptr [edi + 0x1294]
006a6ee1 inc ebx
006a6ee2 cmp ebx, dword ptr [edx + 0x1264]
006a6ee8 jb 0x6a6e30
006a6eee mov ecx, dword ptr [edi + 0x1294]
006a6ef4 mov eax, dword ptr [0xbfd65c]
006a6ef9 mov eax, dword ptr [eax + 0x18190]
006a6eff mov esi, dword ptr [ebp + 8]
006a6f02 add eax, 0x1298
006a6f07 push ecx
006a6f08 push eax
006a6f09 mov ecx, esi
006a6f0b call 0x412420
006a6f10 mov ecx, dword ptr [edi + 0x1294]
006a6f16 cmp dword ptr [esi + 8], ecx
006a6f19 jae 0x6a6f30
006a6f1b push 0xb3f4b0
006a6f20 push 3
006a6f22 call 0x95e330
006a6f27 mov ecx, dword ptr [edi + 0x1294]
006a6f2d add esp, 8
006a6f30 shl ecx, 2
006a6f33 push ecx
006a6f34 push dword ptr [edi + 0x128c]
006a6f3a push dword ptr [esi + 4]
006a6f3d call 0x9ec14c
006a6f42 mov ecx, dword ptr [edi + 0x1294]
006a6f48 add esp, 0xc
006a6f4b mov dword ptr [esi + 0xc], ecx
006a6f4e mov eax, esi
006a6f50 pop edi
006a6f51 pop esi
006a6f52 pop ebx
006a6f53 mov esp, ebp
006a6f55 pop ebp
006a6f56 ret 0x10
006a6f59 int3 
006a6f5a int3 
006a6f5b int3 
006a6f5c int3 
006a6f5d int3 
006a6f5e int3 
006a6f5f int3 
006a6f60 push ebp
006a6f61 mov ebp, esp
006a6f63 push ecx
006a6f64 mov ecx, dword ptr [0xbfd65c]
006a6f6a xor edx, edx
006a6f6c push ebx
006a6f6d push esi
006a6f6e push edi
006a6f6f mov esi, dword ptr [ecx + 0x18190]
006a6f75 xor edi, edi
006a6f77 mov dword ptr [esi + 0x1294], 0
006a6f81 mov eax, dword ptr [ecx + 0x18190]
006a6f87 mov dword ptr [ebp - 4], eax
006a6f8a cmp dword ptr [eax + 0x1264], edx
006a6f90 jbe 0x6a702b
006a6f96 nop word ptr [eax + eax]
006a6fa0 mov eax, dword ptr [eax + 0x125c]
006a6fa6 mov ecx, dword ptr [eax + edi*4]
006a6fa9 mov eax, dword ptr [ecx + 0x28]
006a6fac sub eax, 0xa
006a6faf cmp eax, 0x3dd
006a6fb4 ja 0x6a7013
006a6fb6 push 0
006a6fb8 push 0xbeab70
006a6fbd push 0xbeab18
006a6fc2 push 0
006a6fc4 push ecx
006a6fc5 call 0x9ec34c
006a6fca mov ebx, eax
006a6fcc add esp, 0x14
006a6fcf test ebx, ebx
006a6fd1 je 0x6a7013
006a6fd3 mov eax, dword ptr [ebp + 0xc]
006a6fd6 cmp dword ptr [ebx + 0xbcc], eax
006a6fdc jne 0x6a7013
006a6fde mov edx, dword ptr [esi + 0x1294]
006a6fe4 lea ecx, [edx + 1]
006a6fe7 cmp ecx, dword ptr [esi + 0x1290]
006a6fed jbe 0x6a7004
006a6fef push 0xb3f428
006a6ff4 push 3
006a6ff6 call 0x95e330
006a6ffb mov edx, dword ptr [esi + 0x1294]
006a7001 add esp, 8
006a7004 mov eax, dword ptr [esi + 0x128c]
006a700a mov dword ptr [eax + edx*4], ebx
006a700d inc dword ptr [esi + 0x1294]
006a7013 mov eax, dword ptr [ebp - 4]
006a7016 inc edi
006a7017 cmp edi, dword ptr [eax + 0x1264]
006a701d jb 0x6a6fa0
006a701f mov edx, dword ptr [esi + 0x1294]
006a7025 mov ecx, dword ptr [0xbfd65c]
006a702b mov eax, dword ptr [ecx + 0x18190]
006a7031 mov edi, dword ptr [ebp + 8]
006a7034 add eax, 0x1298
006a7039 push edx
006a703a push eax
006a703b mov ecx, edi
006a703d call 0x412420
006a7042 mov ecx, dword ptr [esi + 0x1294]
006a7048 cmp dword ptr [edi + 8], ecx
006a704b jae 0x6a7062
006a704d push 0xb3f4b0
006a7052 push 3
006a7054 call 0x95e330
006a7059 mov ecx, dword ptr [esi + 0x1294]
006a705f add esp, 8
006a7062 shl ecx, 2
006a7065 push ecx
006a7066 push dword ptr [esi + 0x128c]
006a706c push dword ptr [edi + 4]
006a706f call 0x9ec14c
006a7074 mov ecx, dword ptr [esi + 0x1294]
006a707a add esp, 0xc
006a707d mov dword ptr [edi + 0xc], ecx
006a7080 mov eax, edi
006a7082 pop edi
006a7083 pop esi
006a7084 pop ebx
006a7085 mov esp, ebp
006a7087 pop ebp
006a7088 ret 8
006a708b int3 
006a708c int3 
006a708d int3 
006a708e int3 
006a708f int3 
006a7090 push ebp
006a7091 mov ebp, esp
006a7093 sub esp, 0x5c
006a7096 push ebx
006a7097 push esi
006a7098 push edi
006a7099 mov edi, ecx
006a709b mov eax, dword ptr [edi + 0x2c]
006a709e cmp eax, 0xc
006a70a1 je 0x6a70f6
006a70a3 cmp eax, 0xd
006a70a6 je 0x6a70f6
006a70a8 mov eax, dword ptr [0xbfd65c]
006a70ad mov byte ptr [ebp - 1], 0
006a70b1 mov eax, dword ptr [eax + 0x18190]
006a70b7 movss xmm0, dword ptr [eax + 0x7134]
006a70bf comiss xmm0, dword ptr [0xb6a350]
006a70c6 jbe 0x6a70fa
006a70c8 push dword ptr [edi + 0x20]
006a70cb push 5
006a70cd call 0x684790
006a70d2 test al, al
006a70d4 je 0x6a70fa
006a70d6 mov edx, dword ptr [edi]
006a70d8 lea ecx, [ebp - 0x34]
006a70db push 0x1e
006a70dd call 0x427290
006a70e2 push eax
006a70e3 push 0
006a70e5 push 0
006a70e7 push ecx
006a70e8 mov ecx, edi
006a70ea mov dword ptr [esp], 0x3f800000
006a70f1 call dword ptr [edx + 0x20]
006a70f4 jmp 0x6a70fa
006a70f6 mov byte ptr [ebp - 1], 1
006a70fa mov eax, dword ptr [edi + 0xab4]
006a7100 test eax, eax
006a7102 je 0x6a7638
006a7108 cmp eax, 3
006a710b je 0x6a7155
006a710d cmp eax, 0x10
006a7110 jne 0x6a7786
006a7116 movss xmm0, dword ptr [edi + 0x2d8]
006a711e subss xmm0, dword ptr [0xb6a614]
006a7126 maxss xmm0, dword ptr [0xb6a214]
006a712e movss dword ptr [edi + 0x2d8], xmm0
006a7136 cmp dword ptr [edi + 0x70], 0
006a713a je 0x6a7149
006a713c cmp byte ptr [edi + 0x80], 0
006a7143 jne 0x6a7786
006a7149 mov eax, dword ptr [edi]
006a714b mov ecx, edi
006a714d call dword ptr [eax + 0x28]
006a7150 jmp 0x6a7786
006a7155 cmp dword ptr [edi + 0x70], 0
006a7159 lea ebx, [edi + 0x3c]
006a715c je 0x6a7167
006a715e cmp byte ptr [edi + 0x80], 0
006a7165 jne 0x6a71d1
006a7167 mov esi, dword ptr [ebx + 0x34]
006a716a test esi, esi
006a716c je 0x6a71b3
006a716e cmp dword ptr [esi + 0x14], 0x10
006a7172 mov eax, esi
006a7174 jb 0x6a7178
006a7176 mov eax, dword ptr [esi]
006a7178 mov ecx, 0xb3fd8c
006a717d nop dword ptr [eax]
006a7180 mov dl, byte ptr [eax]
006a7182 cmp dl, byte ptr [ecx]
006a7184 jne 0x6a71a0
006a7186 test dl, dl
006a7188 je 0x6a719c
006a718a mov dl, byte ptr [eax + 1]
006a718d cmp dl, byte ptr [ecx + 1]
006a7190 jne 0x6a71a0
006a7192 add eax, 2
006a7195 add ecx, 2
006a7198 test dl, dl
006a719a jne 0x6a7180
006a719c xor eax, eax
006a719e jmp 0x6a71a5
006a71a0 sbb eax, eax
006a71a2 or eax, 1
006a71a5 test eax, eax
006a71a7 jne 0x6a71b3
006a71a9 cmp byte ptr [esi + 0x34], al
006a71ac je 0x6a71d1
006a71ae cmp byte ptr [ebx + 0x44], al
006a71b1 jne 0x6a71d1
006a71b3 push 1
006a71b5 push 0xb3fd8c
006a71ba mov ecx, ebx
006a71bc call 0x405740
006a71c1 test al, al
006a71c3 je 0x6a71d1
006a71c5 lea ecx, [ebx + 0x30]
006a71c8 call 0x405330
006a71cd mov byte ptr [ebx + 0x44], 1
006a71d1 movss xmm1, dword ptr [edi + 0x28c]
006a71d9 ucomiss xmm1, dword ptr [0xc02fec]
006a71e0 lahf 
006a71e1 test ah, 0x44
006a71e4 jp 0x6a7216
006a71e6 movss xmm0, dword ptr [edi + 0x290]
006a71ee ucomiss xmm0, dword ptr [0xc02ff0]
006a71f5 lahf 
006a71f6 test ah, 0x44
006a71f9 jp 0x6a7216
006a71fb cmp dword ptr [edi + 0x34], 0x3b7
006a7202 je 0x6a7256
006a7204 movss xmm0, dword ptr [edi + 0x2c4]
006a720c mulss xmm0, dword ptr [0xb6a5d8]
006a7214 jmp 0x6a724e
006a7216 movss xmm0, dword ptr [edi + 0x290]
006a721e subss xmm0, dword ptr [edi + 0x298]
006a7226 subss xmm1, dword ptr [edi + 0x294]
006a722e movss dword ptr [edi + 0x2bc], xmm0
006a7236 movss dword ptr [edi + 0x2b8], xmm1
006a723e movss xmm0, dword ptr [edi + 0x2c4]
006a7246 mulss xmm0, dword ptr [0xb6a4c4]
006a724e movss dword ptr [edi + 0x2c4], xmm0
006a7256 mov eax, dword ptr [edi + 0x2c]
006a7259 cmp eax, 0xc
006a725c jne 0x6a736a
006a7262 movss xmm0, dword ptr [edi + 0x2f4]
006a726a addss xmm0, dword ptr [edi + 0xb00]
006a7272 movss xmm1, dword ptr [0xb6aae4]
006a727a comiss xmm0, xmm1
006a727d movss dword ptr [edi + 0xb00], xmm0
006a7285 jbe 0x6a7398
006a728b subss xmm0, xmm1
006a728f movss dword ptr [edi + 0xb00], xmm0
006a7297 movss xmm0, dword ptr [edi + 0x2d8]
006a729f subss xmm0, dword ptr [0xb6a614]
006a72a7 maxss xmm0, dword ptr [0xb6a614]
006a72af movss dword ptr [edi + 0x2d8], xmm0
006a72b7 cmp dword ptr [ebx + 0x80], 0
006a72be mulss xmm0, dword ptr [0xb6a5a4]
006a72c6 divss xmm0, dword ptr [edi + 0x2dc]
006a72ce addss xmm0, dword ptr [0xb6a2cc]
006a72d6 movaps xmm1, xmm0
006a72d9 mulss xmm0, dword ptr [0xbc7a2c]
006a72e1 mulss xmm1, dword ptr [0xbc7a28]
006a72e9 movss dword ptr [ebp - 8], xmm0
006a72ee movss dword ptr [ebp - 0xc], xmm1
006a72f3 jg 0x6a731b
006a72f5 cmp dword ptr [ebx + 0x14], 0x10
006a72f9 mov eax, ebx
006a72fb jb 0x6a72ff
006a72fd mov eax, dword ptr [ebx]
006a72ff push 0
006a7301 push eax
006a7302 push 0xa0830c
006a7307 push 3
006a7309 call 0x95e330
006a730e movss xmm0, dword ptr [ebp - 8]
006a7313 add esp, 0x10
006a7316 movss xmm1, dword ptr [ebp - 0xc]
006a731b mov eax, dword ptr [ebx + 0x7c]
006a731e movss dword ptr [eax + 0x38], xmm0
006a7323 movss xmm0, dword ptr [0xb6a6f0]
006a732b movss dword ptr [eax + 0x34], xmm1
006a7330 comiss xmm0, dword ptr [edi + 0x2d8]
006a7337 jbe 0x6a7398
006a7339 push 0
006a733b push 0xb4102c
006a7340 mov ecx, ebx
006a7342 mov dword ptr [edi + 0xab4], 0x10
006a734c mov dword ptr [edi + 0x180], 0
006a7356 mov dword ptr [edi + 0x17c], 0
006a7360 call 0x4054f0
006a7365 jmp 0x6a7786
006a736a cmp eax, 0xd
006a736d je 0x6a7398
006a736f mov eax, dword ptr [0xbfd65c]
006a7374 mov edx, 0xb4
006a7379 mov ecx, dword ptr [eax + 0x1a30dc]
006a737f mov eax, 0x12c
006a7384 sub ecx, dword ptr [edi + 0x280]
006a738a cmp dword ptr [edi + 0x17c], 0
006a7391 cmovne eax, edx
006a7394 cmp ecx, eax
006a7396 jg 0x6a7339
006a7398 cmp dword ptr [edi + 0x34], 0x3b7
006a739f jne 0x6a73e1
006a73a1 movss xmm1, dword ptr [0xb6aa0c]
006a73a9 xorps xmm2, xmm2
006a73ac mov ecx, edi
006a73ae call 0x6847e0
006a73b3 test eax, eax
006a73b5 je 0x6a73e1
006a73b7 call 0x6c3d90
006a73bc test al, 3
006a73be jne 0x6a73e1
006a73c0 mov edx, dword ptr [edi]
006a73c2 lea ecx, [ebp - 0x5c]
006a73c5 push 0x1e
006a73c7 call 0x427290
006a73cc push eax
006a73cd push 0
006a73cf push 0x20000
006a73d4 push ecx
006a73d5 mov ecx, edi
006a73d7 mov dword ptr [esp], 0x3f800000
006a73de call dword ptr [edx + 0x20]
006a73e1 movss xmm0, dword ptr [edi + 0x14]
006a73e6 xorps xmm1, xmm1
006a73e9 comiss xmm0, xmm1
006a73ec jbe 0x6a7786
006a73f2 mov eax, dword ptr [edi + 0x18]
006a73f5 and eax, 4
006a73f8 or eax, 0
006a73fb jne 0x6a74be
006a7401 cmp byte ptr [ebp - 1], al
006a7404 jne 0x6a74c8
006a740a mov esi, dword ptr [edi + 8]
006a740d movss xmm5, dword ptr [0xb6a614]
006a7415 cmp esi, dword ptr [edi + 0xc]
006a7418 je 0x6a74b1
006a741e movss xmm4, dword ptr [0xb6a974]
006a7426 lea ebx, [eax + 3]
006a7429 movss xmm2, dword ptr [0xb6a7b0]
006a7431 movss xmm3, dword ptr [0xb6a864]
006a7439 nop dword ptr [eax]
006a7440 movss xmm0, dword ptr [esi]
006a7444 comiss xmm4, xmm0
006a7447 jb 0x6a7478
006a7449 comiss xmm0, xmm1
006a744c jbe 0x6a746e
006a744e call 0x6c3d90
006a7453 xor edx, edx
006a7455 mov ecx, 3
006a745a div ecx
006a745c test edx, edx
006a745e je 0x6a7467
006a7460 movaps xmm1, xmm5
006a7463 mov ebx, ecx
006a7465 jmp 0x6a748d
006a7467 movaps xmm1, xmm2
006a746a mov ebx, ecx
006a746c jmp 0x6a748d
006a746e movss xmm0, dword ptr [edi + 0x2d8]
006a7476 jmp 0x6a74a1
006a7478 call 0x6c3d90
006a747d xor edx, edx
006a747f div ebx
006a7481 test edx, edx
006a7483 je 0x6a748a
006a7485 movaps xmm1, xmm2
006a7488 jmp 0x6a748d
006a748a movaps xmm1, xmm3
006a748d movss xmm0, dword ptr [edi + 0x2d8]
006a7495 subss xmm0, xmm1
006a7499 movss dword ptr [edi + 0x2d8], xmm0
006a74a1 add esi, 0x38
006a74a4 xorps xmm1, xmm1
006a74a7 cmp esi, dword ptr [edi + 0xc]
006a74aa jne 0x6a7440
006a74ac lea ebx, [edi + 0x3c]
006a74af jmp 0x6a74b9
006a74b1 movss xmm0, dword ptr [edi + 0x2d8]
006a74b9 comiss xmm5, xmm0
006a74bc jbe 0x6a74c8
006a74be mov dword ptr [edi + 0x2d8], 0x3f800000
006a74c8 cmp dword ptr [ebx + 0x80], 0
006a74cf movss xmm0, dword ptr [edi + 0x2d8]
006a74d7 mulss xmm0, dword ptr [0xb6a5a4]
006a74df divss xmm0, dword ptr [edi + 0x2dc]
006a74e7 addss xmm0, dword ptr [0xb6a2cc]
006a74ef movaps xmm1, xmm0
006a74f2 mulss xmm0, dword ptr [0xbc7a2c]
006a74fa mulss xmm1, dword ptr [0xbc7a28]
006a7502 movss dword ptr [ebp - 0xc], xmm0
006a7507 movss dword ptr [ebp - 8], xmm1
006a750c jg 0x6a7534
006a750e cmp dword ptr [ebx + 0x14], 0x10
006a7512 mov eax, ebx
006a7514 jb 0x6a7518
006a7516 mov eax, dword ptr [ebx]
006a7518 push 0
006a751a push eax
006a751b push 0xa0830c
006a7520 push 3
006a7522 call 0x95e330
006a7527 movss xmm0, dword ptr [ebp - 0xc]
006a752c add esp, 0x10
006a752f movss xmm1, dword ptr [ebp - 8]
006a7534 mov eax, dword ptr [ebx + 0x7c]
006a7537 movss dword ptr [eax + 0x38], xmm0
006a753c movss xmm0, dword ptr [0xb6a6f0]
006a7544 movss dword ptr [eax + 0x34], xmm1
006a7549 comiss xmm0, dword ptr [edi + 0x2d8]
006a7550 jbe 0x6a7786
006a7556 mov dword ptr [edi + 0xab4], 0x10
006a7560 mov dword ptr [edi + 0x180], 0
006a756a mov dword ptr [edi + 0x17c], 0
006a7574 mov esi, dword ptr [ebx + 0x34]
006a7577 test esi, esi
006a7579 je 0x6a75c3
006a757b cmp dword ptr [esi + 0x14], 0x10
006a757f mov eax, esi
006a7581 jb 0x6a7585
006a7583 mov eax, dword ptr [esi]
006a7585 mov ecx, 0xb4102c
006a758a nop word ptr [eax + eax]
006a7590 mov dl, byte ptr [eax]
006a7592 cmp dl, byte ptr [ecx]
006a7594 jne 0x6a75b0
006a7596 test dl, dl
006a7598 je 0x6a75ac
006a759a mov dl, byte ptr [eax + 1]
006a759d cmp dl, byte ptr [ecx + 1]
006a75a0 jne 0x6a75b0
006a75a2 add eax, 2
006a75a5 add ecx, 2
006a75a8 test dl, dl
006a75aa jne 0x6a7590
006a75ac xor eax, eax
006a75ae jmp 0x6a75b5
006a75b0 sbb eax, eax
006a75b2 or eax, 1
006a75b5 test eax, eax
006a75b7 jne 0x6a75c3
006a75b9 cmp byte ptr [esi + 0x34], al
006a75bc je 0x6a75e1
006a75be cmp byte ptr [ebx + 0x44], al
006a75c1 jne 0x6a75e1
006a75c3 push 1
006a75c5 push 0xb4102c
006a75ca mov ecx, ebx
006a75cc call 0x405740
006a75d1 test al, al
006a75d3 je 0x6a75e1
006a75d5 lea ecx, [ebx + 0x30]
006a75d8 call 0x405330
006a75dd mov byte ptr [ebx + 0x44], 1
006a75e1 mov eax, dword ptr [edi + 0x18]
006a75e4 and eax, 0x20000
006a75e9 or eax, 0
006a75ec jne 0x6a7786
006a75f2 mov esi, dword ptr [0xbfd680]
006a75f8 lea ecx, [ebp - 8]
006a75fb mov dword ptr [ebp - 8], 0x105
006a7602 call 0x8b1340
006a7607 sub esp, 8
006a760a mov dword ptr [esp + 4], 0
006a7612 mov dword ptr [esp], 0x3f800000
006a7619 push 0
006a761b push 2
006a761d push ecx
006a761e mov dword ptr [esp], 0x3f59999a
006a7625 lea ecx, [esi + 0x29de0]
006a762b push dword ptr [ebp - 8]
006a762e call 0x888de0
006a7633 jmp 0x6a7786
006a7638 movss xmm0, dword ptr [edi + 0x2d8]
006a7640 mulss xmm0, dword ptr [0xb6a5a4]
006a7648 mov ecx, dword ptr [edi + 0x160]
006a764e mov eax, dword ptr [edi + 0x164]
006a7654 and ecx, 0xfffffffb
006a7657 or ecx, 0x42050011
006a765d mov dword ptr [edi + 0x164], eax
006a7663 divss xmm0, dword ptr [edi + 0x2dc]
006a766b mov dword ptr [edi + 0x160], ecx
006a7671 cmp dword ptr [edi + 0xbc], 0
006a7678 addss xmm0, dword ptr [0xb6a2cc]
006a7680 movaps xmm1, xmm0
006a7683 mulss xmm0, dword ptr [0xbc7a2c]
006a768b mulss xmm1, dword ptr [0xbc7a28]
006a7693 movss dword ptr [ebp - 0xc], xmm0
006a7698 movss dword ptr [ebp - 8], xmm1
006a769d jg 0x6a76c7
006a769f cmp dword ptr [edi + 0x50], 0x10
006a76a3 lea eax, [edi + 0x3c]
006a76a6 jb 0x6a76ab
006a76a8 mov eax, dword ptr [edi + 0x3c]
006a76ab push 0
006a76ad push eax
006a76ae push 0xa0830c
006a76b3 push 3
006a76b5 call 0x95e330
006a76ba movss xmm0, dword ptr [ebp - 0xc]
006a76bf add esp, 0x10
006a76c2 movss xmm1, dword ptr [ebp - 8]
006a76c7 mov eax, dword ptr [edi + 0xb8]
006a76cd movss dword ptr [eax + 0x34], xmm1
006a76d2 movss dword ptr [eax + 0x38], xmm0
006a76d7 mov ebx, dword ptr [edi + 0x70]
006a76da test ebx, ebx
006a76dc je 0x6a7726
006a76de cmp dword ptr [ebx + 0x14], 0x10
006a76e2 mov eax, ebx
006a76e4 jb 0x6a76e8
006a76e6 mov eax, dword ptr [ebx]
006a76e8 mov ecx, 0xb40360
006a76ed nop dword ptr [eax]
006a76f0 mov dl, byte ptr [eax]
006a76f2 cmp dl, byte ptr [ecx]
006a76f4 jne 0x6a7710
006a76f6 test dl, dl
006a76f8 je 0x6a770c
006a76fa mov dl, byte ptr [eax + 1]
006a76fd cmp dl, byte ptr [ecx + 1]
006a7700 jne 0x6a7710
006a7702 add eax, 2
006a7705 add ecx, 2
006a7708 test dl, dl
006a770a jne 0x6a76f0
006a770c xor eax, eax
006a770e jmp 0x6a7715
006a7710 sbb eax, eax
006a7712 or eax, 1
006a7715 test eax, eax
006a7717 jne 0x6a7726
006a7719 cmp byte ptr [ebx + 0x34], al
006a771c je 0x6a7748
006a771e cmp byte ptr [edi + 0x80], al
006a7724 jne 0x6a7748
006a7726 push 1
006a7728 push 0xb40360
006a772d lea ecx, [edi + 0x3c]
006a7730 call 0x405740
006a7735 test al, al
006a7737 je 0x6a7748
006a7739 lea ecx, [edi + 0x6c]
006a773c call 0x405330
006a7741 mov byte ptr [edi + 0x80], 1
006a7748 mov dword ptr [edi + 0xab4], 3
006a7752 movss xmm0, dword ptr [edi + 0x28c]
006a775a ucomiss xmm0, dword ptr [0xc02fec]
006a7761 lahf 
006a7762 test ah, 0x44
006a7765 jp 0x6a777c
006a7767 movss xmm0, dword ptr [edi + 0x290]
006a776f ucomiss xmm0, dword ptr [0xc02ff0]
006a7776 lahf 
006a7777 test ah, 0x44
006a777a jnp 0x6a7786
006a777c mov dword ptr [edi + 0x17c], 0
006a7786 mov eax, dword ptr [edi + 8]
006a7789 mov dword ptr [edi + 0x14], 0
006a7790 mov dword ptr [edi + 0x18], 0
006a7797 mov dword ptr [edi + 0x1c], 0
006a779e mov dword ptr [edi + 0xc], eax
006a77a1 pop edi
006a77a2 pop esi
006a77a3 pop ebx
006a77a4 mov esp, ebp
006a77a6 pop ebp
006a77a7 ret 
006a77a8 int3 
006a77a9 int3 
006a77aa int3 
006a77ab int3 
006a77ac int3 
006a77ad int3 
006a77ae int3 
006a77af int3 
006a77b0 push ebx
006a77b1 mov ebx, esp
006a77b3 sub esp, 8
006a77b6 and esp, 0xfffffff8
006a77b9 add esp, 4
006a77bc push ebp
006a77bd mov ebp, dword ptr [ebx + 4]
006a77c0 mov dword ptr [esp + 4], ebp
006a77c4 mov ebp, esp
006a77c6 push -1
006a77c8 push 0x9f496d
006a77cd mov eax, dword ptr fs:[0]
006a77d3 push eax
006a77d4 push ebx
006a77d5 sub esp, 0x40
006a77d8 mov eax, dword ptr [0xbaa3b4]
006a77dd xor eax, ebp
006a77df mov dword ptr [ebp - 0x14], eax
006a77e2 push esi
006a77e3 push edi
006a77e4 push eax
006a77e5 lea eax, [ebp - 0xc]
006a77e8 mov dword ptr fs:[0], eax
006a77ee mov esi, ecx
006a77f0 mov edi, dword ptr [ebx + 8]
006a77f3 push 8
006a77f5 mov dword ptr [ebp - 0x28], edi
006a77f8 mov dword ptr [ebp - 0x40], 0
006a77ff mov dword ptr [ebp - 0x3c], 0
006a7806 mov dword ptr [ebp - 0x38], 0
006a780d mov dword ptr [ebp - 0x34], 0
006a7814 mov dword ptr [ebp - 0x30], 0
006a781b call 0x9eacf8
006a7820 lea ecx, [ebp - 0x40]
006a7823 add esp, 4
006a7826 mov dword ptr [eax + 4], 0
006a782d mov dword ptr [ebp - 0x40], eax
006a7830 mov dword ptr [eax], ecx
006a7832 mov dword ptr [ebp - 4], 0
006a7839 xor eax, eax
006a783b mov ecx, dword ptr [esi + 0x164]
006a7841 and ecx, 0x400
006a7847 or eax, ecx
006a7849 jne 0x6a7a08
006a784f mov ecx, dword ptr [esi + 0x2c]
006a7852 cmp ecx, 0xb
006a7855 je 0x6a7a08
006a785b cmp ecx, 0xa
006a785e je 0x6a7a08
006a7864 cmp ecx, 0xc
006a7867 je 0x6a7a08
006a786d cmp ecx, 0xd
006a7870 je 0x6a7a08
006a7876 cmp ecx, 4
006a7879 je 0x6a7a08
006a787f cmp byte ptr [ebx + 0xc], 0
006a7883 lea eax, [esi + 0x334]
006a7889 movups xmm0, xmmword ptr [eax]
006a788c lea esi, [ebp - 0x24]
006a788f cmovne esi, eax
006a7892 movups xmmword ptr [ebp - 0x24], xmm0
006a7896 cmp ecx, 2
006a7899 je 0x6a7960
006a789f cmp ecx, 3
006a78a2 je 0x6a7960
006a78a8 call 0x6cba20
006a78ad test al, al
006a78af je 0x6a78bb
006a78b1 movss xmm0, dword ptr [0xb6a2cc]
006a78b9 jmp 0x6a78c3
006a78bb movss xmm0, dword ptr [0xb6a38c]
006a78c3 mov ecx, esi
006a78c5 movss dword ptr [ebp - 0x2c], xmm0
006a78ca call 0x7a7db0
006a78cf movss xmm0, dword ptr [ebp - 0x2c]
006a78d4 fstp dword ptr [ebp - 0x28]
006a78d7 comiss xmm0, dword ptr [ebp - 0x28]
006a78db jbe 0x6a79f0
006a78e1 mov ecx, esi
006a78e3 call 0x7a7db0
006a78e8 movss xmm0, dword ptr [0xb6a38c]
006a78f0 fstp dword ptr [ebp - 0x28]
006a78f3 comiss xmm0, dword ptr [ebp - 0x28]
006a78f7 jbe 0x6a794d
006a78f9 mov ecx, dword ptr [0xbfd65c]
006a78ff push 1
006a7901 push 0
006a7903 push 0x16
006a7905 lea ecx, [ecx + 0x1ba40]
006a790b call 0x91d550
006a7910 test eax, eax
006a7912 je 0x6a793c
006a7914 mov eax, dword ptr [esi]
006a7916 lea ecx, [ebp - 0x50]
006a7919 movq xmm0, qword ptr [0xa08ad0]
006a7921 mov dword ptr [ebp - 0x50], eax
006a7924 mov eax, dword ptr [0xa08ad8]
006a7929 push 5
006a792b movq qword ptr [ebp - 0x4c], xmm0
006a7930 mov dword ptr [ebp - 0x44], eax
006a7933 call 0x7a7d50
006a7938 test eax, eax
006a793a jne 0x6a794d
006a793c mov ecx, esi
006a793e call 0x7a7e20
006a7943 push 0
006a7945 push eax
006a7946 push 0
006a7948 jmp 0x6a79e4
006a794d mov ecx, esi
006a794f call 0x7a7e20
006a7954 push 0
006a7956 push eax
006a7957 push 0
006a7959 push 0x14
006a795b jmp 0x6a79e6
006a7960 call 0x6cba20
006a7965 test al, al
006a7967 je 0x6a7973
006a7969 movss xmm0, dword ptr [0xb6a2cc]
006a7971 jmp 0x6a797b
006a7973 movss xmm0, dword ptr [0xb6a38c]
006a797b mov ecx, esi
006a797d movss dword ptr [ebp - 0x2c], xmm0
006a7982 call 0x7a7db0
006a7987 movss xmm0, dword ptr [ebp - 0x2c]
006a798c fstp dword ptr [ebp - 0x28]
006a798f comiss xmm0, dword ptr [ebp - 0x28]
006a7993 jbe 0x6a79f0
006a7995 mov ecx, dword ptr [0xbfd65c]
006a799b push 1
006a799d push 0
006a799f push 0x16
006a79a1 lea ecx, [ecx + 0x1ba40]
006a79a7 call 0x91d550
006a79ac test eax, eax
006a79ae je 0x6a79d8
006a79b0 mov eax, dword ptr [esi]
006a79b2 lea ecx, [ebp - 0x50]
006a79b5 movq xmm0, qword ptr [0xa08ad0]
006a79bd mov dword ptr [ebp - 0x50], eax
006a79c0 mov eax, dword ptr [0xa08ad8]
006a79c5 push 5
006a79c7 movq qword ptr [ebp - 0x4c], xmm0
006a79cc mov dword ptr [ebp - 0x44], eax
006a79cf call 0x7a7d50
006a79d4 test eax, eax
006a79d6 jne 0x6a79f0
006a79d8 mov ecx, esi
006a79da call 0x7a7e20
006a79df push 0
006a79e1 push eax
006a79e2 push 3
006a79e4 push 0xa
006a79e6 push 5
006a79e8 lea ecx, [ebp - 0x40]
006a79eb call 0x68f5d0
006a79f0 lea eax, [ebp - 0x40]
006a79f3 mov ecx, edi
006a79f5 push eax
006a79f6 call 0x698e70
006a79fb lea ecx, [ebp - 0x40]
006a79fe call 0x68f5b0
006a7a03 jmp 0x6a7ab2
006a7a08 lea eax, [ebp - 0x40]
006a7a0b mov ecx, edi
006a7a0d push eax
006a7a0e call 0x698e70
006a7a13 mov ecx, dword ptr [ebp - 0x30]
006a7a16 test ecx, ecx
006a7a18 je 0x6a7a35
006a7a1a mov eax, dword ptr [ebp - 0x34]
006a7a1d nop dword ptr [eax]
006a7a20 sub ecx, 1
006a7a23 mov edx, 0
006a7a28 cmove eax, edx
006a7a2b test ecx, ecx
006a7a2d jne 0x6a7a20
006a7a2f mov dword ptr [ebp - 0x34], eax
006a7a32 mov dword ptr [ebp - 0x30], ecx
006a7a35 mov esi, dword ptr [ebp - 0x38]
006a7a38 mov ecx, dword ptr [ebp - 0x3c]
006a7a3b test esi, esi
006a7a3d je 0x6a7a5e
006a7a3f nop 
006a7a40 mov eax, dword ptr [ecx + esi*4 - 4]
006a7a44 dec esi
006a7a45 test eax, eax
006a7a47 je 0x6a7a57
006a7a49 push 0x14
006a7a4b push eax
006a7a4c call 0x9eb08e
006a7a51 mov ecx, dword ptr [ebp - 0x3c]
006a7a54 add esp, 8
006a7a57 test esi, esi
006a7a59 jne 0x6a7a40
006a7a5b mov esi, dword ptr [ebp - 0x38]
006a7a5e test ecx, ecx
006a7a60 je 0x6a7a8f
006a7a62 shl esi, 2
006a7a65 mov eax, ecx
006a7a67 cmp esi, 0x1000
006a7a6d jb 0x6a7a85
006a7a6f mov ecx, dword ptr [ecx - 4]
006a7a72 add esi, 0x23
006a7a75 sub eax, ecx
006a7a77 add eax, -4
006a7a7a cmp eax, 0x1f
006a7a7d jbe 0x6a7a85
006a7a7f call dword ptr [0xa065ac]
006a7a85 push esi
006a7a86 push ecx
006a7a87 call 0x9eb08e
006a7a8c add esp, 8
006a7a8f mov eax, dword ptr [ebp - 0x40]
006a7a92 push 8
006a7a94 push eax
006a7a95 mov dword ptr [ebp - 0x38], 0
006a7a9c mov dword ptr [ebp - 0x3c], 0
006a7aa3 mov dword ptr [ebp - 0x40], 0
006a7aaa call 0x9eb08e
006a7aaf add esp, 8
006a7ab2 mov eax, edi
006a7ab4 mov ecx, dword ptr [ebp - 0xc]
006a7ab7 mov dword ptr fs:[0], ecx
006a7abe pop ecx
006a7abf pop edi
006a7ac0 pop esi
006a7ac1 mov ecx, dword ptr [ebp - 0x14]
006a7ac4 xor ecx, ebp
006a7ac6 call 0x9eacd7
006a7acb mov esp, ebp
006a7acd pop ebp
006a7ace mov esp, ebx
006a7ad0 pop ebx
006a7ad1 ret 8
006a7ad4 int3 
006a7ad5 int3 
006a7ad6 int3 
006a7ad7 int3 
006a7ad8 int3 
006a7ad9 int3 
006a7ada int3 
006a7adb int3 
006a7adc int3 
006a7add int3 
006a7ade int3 
006a7adf int3 
006a7ae0 push ebp
006a7ae1 mov ebp, esp
006a7ae3 push -1
006a7ae5 push 0x9f49b0
006a7aea mov eax, dword ptr fs:[0]
006a7af0 push eax
006a7af1 sub esp, 0xdc
006a7af7 mov eax, dword ptr [0xbaa3b4]
006a7afc xor eax, ebp
006a7afe mov dword ptr [ebp - 0x10], eax
006a7b01 push ebx
006a7b02 push esi
006a7b03 push edi
006a7b04 push eax
006a7b05 lea eax, [ebp - 0xc]
006a7b08 mov dword ptr fs:[0], eax
006a7b0e mov edi, ecx
006a7b10 mov dword ptr [ebp - 0x74], edi
006a7b13 mov esi, dword ptr [edi + 0x2c]
006a7b16 movss xmm1, dword ptr [0xb6a350]
006a7b1e cmp esi, 2
006a7b21 je 0x6a7b7d
006a7b23 cmp esi, 3
006a7b26 je 0x6a7b7d
006a7b28 cmp esi, 4
006a7b2b je 0x6a7b7d
006a7b2d mov eax, dword ptr [0xbfd65c]
006a7b32 mov byte ptr [ebp - 0x69], 0
006a7b36 mov eax, dword ptr [eax + 0x18190]
006a7b3c movss xmm0, dword ptr [eax + 0x7134]
006a7b44 comiss xmm0, xmm1
006a7b47 jbe 0x6a7b81
006a7b49 push dword ptr [edi + 0x20]
006a7b4c push 5
006a7b4e call 0x684790
006a7b53 test al, al
006a7b55 je 0x6a7b81
006a7b57 mov edx, dword ptr [edi]
006a7b59 lea ecx, [ebp - 0xe8]
006a7b5f push 0x1e
006a7b61 call 0x427290
006a7b66 push eax
006a7b67 push 0
006a7b69 push 0
006a7b6b push ecx
006a7b6c mov ecx, edi
006a7b6e mov dword ptr [esp], 0x3f800000
006a7b75 call dword ptr [edx + 0x20]
006a7b78 mov esi, dword ptr [edi + 0x2c]
006a7b7b jmp 0x6a7b81
006a7b7d mov byte ptr [ebp - 0x69], 1
006a7b81 cmp esi, 0xb
006a7b84 jne 0x6a7b92
006a7b86 mov ecx, edi
006a7b88 call 0x4e7250
006a7b8d jmp 0x6a8a1d
006a7b92 cmp esi, 0xa
006a7b95 je 0x6a8a16
006a7b9b cmp esi, 0xc
006a7b9e je 0x6a8a16
006a7ba4 cmp esi, 0xd
006a7ba7 je 0x6a8a16
006a7bad mov eax, dword ptr [edi + 0xab4]
006a7bb3 mov ebx, dword ptr [edi + 0x32c]
006a7bb9 mov dword ptr [ebp - 0x84], ebx
006a7bbf test eax, eax
006a7bc1 jne 0x6a7e23
006a7bc7 mov eax, dword ptr [edi + 0x164]
006a7bcd lea ecx, [ebp - 0xc0]
006a7bd3 or dword ptr [edi + 0x160], 0x40000
006a7bdd push 0x23
006a7bdf push dword ptr [edi + 0x344]
006a7be5 mov dword ptr [edi + 0x164], eax
006a7beb call 0x7a7cd0
006a7bf0 mov esi, dword ptr [0xbfd65c]
006a7bf6 mov ecx, dword ptr [esi + 0x18190]
006a7bfc call 0x7cf750
006a7c01 test eax, eax
006a7c03 jne 0x6a7c43
006a7c05 cmp dword ptr [edi + 0x2c], 2
006a7c09 jne 0x6a7c2d
006a7c0b push 0x64
006a7c0d lea ecx, [ebp - 0xc0]
006a7c13 call 0x7a7d50
006a7c18 test eax, eax
006a7c1a jne 0x6a7c2d
006a7c1c push -1
006a7c1e push dword ptr [edi + 0x30]
006a7c21 mov ecx, edi
006a7c23 push 3
006a7c25 push dword ptr [edi + 0x28]
006a7c28 call 0x697c60
006a7c2d push 3
006a7c2f lea ecx, [ebp - 0xc0]
006a7c35 call 0x7a7d50
006a7c3a mov esi, dword ptr [0xbfd65c]
006a7c40 mov dword ptr [edi + 0x30], eax
006a7c43 mov eax, dword ptr [edi + 0x294]
006a7c49 lea ebx, [edi + 0x294]
006a7c4f mov dword ptr [edi + 0x28c], eax
006a7c55 mov eax, dword ptr [ebx + 4]
006a7c58 mov dword ptr [edi + 0x290], eax
006a7c5e call 0x6c3d90
006a7c63 xor edx, edx
006a7c65 movss xmm0, dword ptr [edi + 0x2d8]
006a7c6d mov ecx, 0x1e
006a7c72 div ecx
006a7c74 mov ecx, dword ptr [edi + 0x160]
006a7c7a mov eax, dword ptr [edi + 0x164]
006a7c80 and ecx, 0xfffffffb
006a7c83 add edx, 0x3c
006a7c86 mov dword ptr [edi + 0x164], eax
006a7c8c or ecx, 0x42050011
006a7c92 mov dword ptr [edi + 0xaf0], edx
006a7c98 comiss xmm0, dword ptr [0xb6a6f0]
006a7c9f mov dword ptr [edi + 0x160], ecx
006a7ca5 jbe 0x6a7ce8
006a7ca7 mov eax, dword ptr [esi + 0x18190]
006a7cad movss xmm0, dword ptr [eax + 0x7134]
006a7cb5 comiss xmm0, dword ptr [0xb6a18c]
006a7cbc jbe 0x6a7ccd
006a7cbe cmp byte ptr [ebp - 0x69], 0
006a7cc2 jne 0x6a7ccd
006a7cc4 cmp dword ptr [ebp - 0x84], 0
006a7ccb je 0x6a7cde
006a7ccd mov ecx, esi
006a7ccf call 0x71b600
006a7cd4 mov esi, dword ptr [0xbfd65c]
006a7cda test al, al
006a7cdc je 0x6a7ce8
006a7cde mov dword ptr [edi + 0x2d8], 0x3f800000
006a7ce8 movss xmm0, dword ptr [edi + 0x2d8]
006a7cf0 comiss xmm0, dword ptr [0xb6a6f0]
006a7cf7 jbe 0x6a7db7
006a7cfd cmp dword ptr [ebp - 0x84], 0
006a7d04 jne 0x6a7d21
006a7d06 mov esi, dword ptr [esi + 0x18190]
006a7d0c mov ecx, esi
006a7d0e push 0x3b6
006a7d13 push ebx
006a7d14 call 0x7ce950
006a7d19 push eax
006a7d1a mov ecx, esi
006a7d1c call 0x447f40
006a7d21 mov eax, dword ptr [edi + 0x30]
006a7d24 lea ecx, [edi + 0x3c]
006a7d27 push 0
006a7d29 mov dword ptr [edi + 0xab4], 8
006a7d33 push dword ptr [eax*4 + 0xb46d20]
006a7d3a call 0x4054f0
006a7d3f lea ecx, [edi + 0x6c]
006a7d42 call 0x432ec0
006a7d47 mov ecx, eax
006a7d49 test ecx, ecx
006a7d4b jle 0x6a7d60
006a7d4d mov eax, dword ptr [edi + 0x344]
006a7d53 xor edx, edx
006a7d55 div ecx
006a7d57 lea ecx, [edi + 0x3c]
006a7d5a push edx
006a7d5b call 0x405890
006a7d60 movss xmm1, dword ptr [edi + 0x2d8]
006a7d68 lea ecx, [edi + 0x3c]
006a7d6b divss xmm1, dword ptr [edi + 0x2dc]
006a7d73 push 1
006a7d75 movaps xmm0, xmm1
006a7d78 mulss xmm1, dword ptr [0xbc7a2c]
006a7d80 mulss xmm0, dword ptr [0xbc7a28]
006a7d88 movss dword ptr [ebp - 0x70], xmm1
006a7d8d movss dword ptr [ebp - 0x7c], xmm0
006a7d92 call 0x4062c0
006a7d97 movss xmm0, dword ptr [ebp - 0x7c]
006a7d9c mov ecx, edi
006a7d9e movss dword ptr [eax + 0x34], xmm0
006a7da3 movss xmm0, dword ptr [ebp - 0x70]
006a7da8 movss dword ptr [eax + 0x38], xmm0
006a7dad call 0x6b1270
006a7db2 jmp 0x6a8a1d
006a7db7 cmp dword ptr [ebp - 0x84], 0
006a7dbe jne 0x6a7ddb
006a7dc0 mov esi, dword ptr [esi + 0x18190]
006a7dc6 mov ecx, esi
006a7dc8 push 0x384
006a7dcd push ebx
006a7dce call 0x7ce950
006a7dd3 push eax
006a7dd4 mov ecx, esi
006a7dd6 call 0x447f40
006a7ddb mov eax, dword ptr [edi + 0x30]
006a7dde lea ecx, [edi + 0x3c]
006a7de1 push 0
006a7de3 mov dword ptr [edi + 0xab4], 3
006a7ded mov dword ptr [edi + 0x180], 0
006a7df7 push dword ptr [eax*4 + 0xb46d2c]
006a7dfe mov dword ptr [edi + 0x17c], 0
006a7e08 call 0x4054f0
006a7e0d mov ecx, edi
006a7e0f mov dword ptr [edi + 0x2ac], 0xfffffc18
006a7e19 call 0x6b1270
006a7e1e jmp 0x6a8a1d
006a7e23 cmp eax, 9
006a7e26 jne 0x6a7fb3
006a7e2c mov eax, dword ptr [edi + 0x2dc]
006a7e32 lea ecx, [edi + 0x3c]
006a7e35 mov dword ptr [edi + 0x2d8], eax
006a7e3b mov eax, dword ptr [edi + 0x30]
006a7e3e push 0
006a7e40 mov dword ptr [edi + 0xab4], 8
006a7e4a push dword ptr [eax*4 + 0xb46d20]
006a7e51 call 0x4054f0
006a7e56 lea ecx, [edi + 0x6c]
006a7e59 call 0x432ec0
006a7e5e mov ecx, eax
006a7e60 test ecx, ecx
006a7e62 jle 0x6a7e77
006a7e64 mov eax, dword ptr [edi + 0x344]
006a7e6a xor edx, edx
006a7e6c div ecx
006a7e6e lea ecx, [edi + 0x3c]
006a7e71 push edx
006a7e72 call 0x405890
006a7e77 movss xmm1, dword ptr [edi + 0x2d8]
006a7e7f lea ecx, [edi + 0x3c]
006a7e82 divss xmm1, dword ptr [edi + 0x2dc]
006a7e8a push 1
006a7e8c movaps xmm0, xmm1
006a7e8f mulss xmm1, dword ptr [0xbc7a2c]
006a7e97 mulss xmm0, dword ptr [0xbc7a28]
006a7e9f movss dword ptr [ebp - 0x70], xmm1
006a7ea4 movss dword ptr [ebp - 0x7c], xmm0
006a7ea9 call 0x4062c0
006a7eae movss xmm0, dword ptr [ebp - 0x7c]
006a7eb3 test ebx, ebx
006a7eb5 mov ebx, dword ptr [0xbfd65c]
006a7ebb movss dword ptr [eax + 0x34], xmm0
006a7ec0 movss xmm0, dword ptr [ebp - 0x70]
006a7ec5 movss dword ptr [eax + 0x38], xmm0
006a7eca mov dword ptr [edi + 0x180], 4
006a7ed4 mov dword ptr [edi + 0x2ac], 0
006a7ede jne 0x6a7f01
006a7ee0 mov esi, dword ptr [ebx + 0x18190]
006a7ee6 lea eax, [edi + 0x294]
006a7eec push 0x3b6
006a7ef1 push eax
006a7ef2 mov ecx, esi
006a7ef4 call 0x7ce950
006a7ef9 push eax
006a7efa mov ecx, esi
006a7efc call 0x447f40
006a7f01 call 0x6c3d90
006a7f06 push eax
006a7f07 push 0
006a7f09 push 0
006a7f0b push 0xc02fec
006a7f10 lea eax, [edi + 0x294]
006a7f16 mov ecx, ebx
006a7f18 push eax
006a7f19 push 0xf
006a7f1b push 0x3e8
006a7f20 call 0x422e20
006a7f25 mov dword ptr [eax + 0x2a4], 0
006a7f2f mov dword ptr [eax + 0x2a8], 0xc0c00000
006a7f39 cmp dword ptr [edi + 0x2c], 1
006a7f3d jne 0x6a7f4c
006a7f3f movss xmm1, dword ptr [0xb6a4c4]
006a7f47 xorps xmm0, xmm0
006a7f4a jmp 0x6a7f5c
006a7f4c movss xmm0, dword ptr [0xb6a480]
006a7f54 movss xmm1, dword ptr [0xb6a3f8]
006a7f5c push ecx
006a7f5d movss dword ptr [eax + 0x104], xmm1
006a7f65 mov dword ptr [eax + 0x108], 0
006a7f6f movss dword ptr [eax + 0x10c], xmm0
006a7f77 mov dword ptr [esp], 0x3f800000
006a7f7e push 0
006a7f80 push 2
006a7f82 push ecx
006a7f83 mov dword ptr [esp], 0x3f800000
006a7f8a mov ecx, edi
006a7f8c push 0x1d7
006a7f91 call 0x6ad720
006a7f96 call 0x6c3d90
006a7f9b xor edx, edx
006a7f9d mov ecx, 0x3c
006a7fa2 div ecx
006a7fa4 mov eax, dword ptr [edi + 0xab4]
006a7faa add edx, 0x5a
006a7fad mov dword ptr [edi + 0xaf0], edx
006a7fb3 cmp eax, 8
006a7fb6 jne 0x6a7fdb
006a7fb8 cmp dword ptr [edi + 0x70], 0
006a7fbc lea ecx, [edi + 0x3c]
006a7fbf je 0x6a7fca
006a7fc1 cmp byte ptr [edi + 0x80], 0
006a7fc8 jne 0x6a7fdb
006a7fca mov eax, dword ptr [edi + 0x30]
006a7fcd push 0
006a7fcf push dword ptr [eax*4 + 0xb46d20]
006a7fd6 call 0x4054f0
006a7fdb movss xmm1, dword ptr [edi + 0x28c]
006a7fe3 lea ebx, [edi + 0x294]
006a7fe9 movss xmm0, dword ptr [edi + 0x290]
006a7ff1 subss xmm1, dword ptr [ebx]
006a7ff5 subss xmm0, dword ptr [ebx + 4]
006a7ffa mov dword ptr [ebp - 0x88], ebx
006a8000 movss dword ptr [edi + 0x2b8], xmm1
006a8008 xorps xmm1, xmm1
006a800b movss dword ptr [edi + 0x2bc], xmm0
006a8013 movss xmm0, dword ptr [edi + 0x14]
006a8018 comiss xmm0, xmm1
006a801b ja 0x6a802a
006a801d cmp byte ptr [edi + 0x16b], 0
006a8024 je 0x6a83fc
006a802a mov eax, dword ptr [edi + 0x2c]
006a802d test eax, eax
006a802f je 0x6a8102
006a8035 cmp eax, 1
006a8038 je 0x6a8102
006a803e cmp byte ptr [ebp - 0x69], 0
006a8042 je 0x6a83e2
006a8048 cmp eax, 4
006a804b je 0x6a83e2
006a8051 cmp dword ptr [edi + 0xab4], 8
006a8058 jne 0x6a83e2
006a805e mov eax, dword ptr [edi + 0x18]
006a8061 and eax, 4
006a8064 or eax, 0
006a8067 jne 0x6a8075
006a8069 cmp byte ptr [edi + 0x16b], al
006a806f je 0x6a83fc
006a8075 mov eax, dword ptr [edi + 0x30]
006a8078 lea ecx, [edi + 0x3c]
006a807b push 0
006a807d mov dword ptr [edi + 0x2d8], 0x3f800000
006a8087 mov dword ptr [edi + 0xab4], 3
006a8091 push dword ptr [eax*4 + 0xb46d2c]
006a8098 mov dword ptr [edi + 0x180], 0
006a80a2 mov dword ptr [edi + 0x17c], 0
006a80ac call 0x4054f0
006a80b1 push ecx
006a80b2 mov dword ptr [esp], 0x3f800000
006a80b9 push 0
006a80bb push 2
006a80bd push ecx
006a80be mov dword ptr [esp], 0x3f59999a
006a80c5 mov ecx, edi
006a80c7 push 0x105
006a80cc mov dword ptr [edi + 0x2ac], 0xfffffc18
006a80d6 call 0x6ad720
006a80db call 0x6c3d90
006a80e0 mov ecx, dword ptr [0xbfd65c]
006a80e6 push eax
006a80e7 push 0
006a80e9 push 0
006a80eb push 0xc02fec
006a80f0 push ebx
006a80f1 push 0xf
006a80f3 push 0x3e8
006a80f8 call 0x422e20
006a80fd jmp 0x6a8328
006a8102 cmp byte ptr [edi + 0x16b], 0
006a8109 mov byte ptr [ebp - 0x69], 0
006a810d jne 0x6a8123
006a810f mov eax, dword ptr [edi + 0x18]
006a8112 and eax, 4
006a8115 or eax, 0
006a8118 jne 0x6a8123
006a811a comiss xmm0, dword ptr [0xb6accc]
006a8121 jb 0x6a8127
006a8123 mov byte ptr [ebp - 0x69], 1
006a8127 cmp dword ptr [edi + 0xab4], 8
006a812e jne 0x6a83e2
006a8134 mov esi, dword ptr [edi + 8]
006a8137 xor ecx, ecx
006a8139 movss xmm5, dword ptr [0xb6a614]
006a8141 mov eax, 0x92492493
006a8146 mov dword ptr [ebp - 0x70], ecx
006a8149 mov ecx, dword ptr [edi + 0xc]
006a814c sub ecx, esi
006a814e imul ecx
006a8150 add edx, ecx
006a8152 sar edx, 5
006a8155 mov eax, edx
006a8157 shr eax, 0x1f
006a815a add eax, edx
006a815c je 0x6a8203
006a8162 movss xmm4, dword ptr [0xb6a974]
006a816a xor ebx, ebx
006a816c movss xmm3, dword ptr [0xb6a864]
006a8174 movss xmm2, dword ptr [0xb6a7b0]
006a817c nop dword ptr [eax]
006a8180 movss xmm0, dword ptr [esi + ebx]
006a8185 comiss xmm0, xmm4
006a8188 jbe 0x6a81a1
006a818a call 0x6c3d90
006a818f xor edx, edx
006a8191 mov ecx, 3
006a8196 div ecx
006a8198 test edx, edx
006a819a jne 0x6a81b8
006a819c movaps xmm1, xmm3
006a819f jmp 0x6a81c0
006a81a1 comiss xmm0, xmm1
006a81a4 jbe 0x6a81d7
006a81a6 call 0x6c3d90
006a81ab xor edx, edx
006a81ad mov ecx, 3
006a81b2 div ecx
006a81b4 test edx, edx
006a81b6 jne 0x6a81bd
006a81b8 movaps xmm1, xmm2
006a81bb jmp 0x6a81c0
006a81bd movaps xmm1, xmm5
006a81c0 movss xmm0, dword ptr [edi + 0x2d8]
006a81c8 subss xmm0, xmm1
006a81cc xorps xmm1, xmm1
006a81cf movss dword ptr [edi + 0x2d8], xmm0
006a81d7 mov ecx, dword ptr [edi + 0xc]
006a81da mov eax, 0x92492493
006a81df mov esi, dword ptr [edi + 8]
006a81e2 add ebx, 0x38
006a81e5 inc dword ptr [ebp - 0x70]
006a81e8 sub ecx, esi
006a81ea imul ecx
006a81ec add edx, ecx
006a81ee sar edx, 5
006a81f1 mov eax, edx
006a81f3 shr eax, 0x1f
006a81f6 add eax, edx
006a81f8 cmp dword ptr [ebp - 0x70], eax
006a81fb jb 0x6a8180
006a81fd lea ebx, [edi + 0x294]
006a8203 movss xmm0, dword ptr [edi + 0x2d8]
006a820b lea esi, [edi + 0x2d8]
006a8211 comiss xmm0, xmm5
006a8214 lea eax, [ebp - 0x7c]
006a8217 mov dword ptr [ebp - 0x7c], 0x3f800000
006a821e lea ecx, [edi + 0x3c]
006a8221 push 1
006a8223 cmova eax, esi
006a8226 movss xmm1, dword ptr [eax]
006a822a movss dword ptr [esi], xmm1
006a822e divss xmm1, dword ptr [edi + 0x2dc]
006a8236 movaps xmm0, xmm1
006a8239 mulss xmm1, dword ptr [0xbc7a2c]
006a8241 mulss xmm0, dword ptr [0xbc7a28]
006a8249 movss dword ptr [ebp - 0x70], xmm1
006a824e movss dword ptr [ebp - 0x7c], xmm0
006a8253 call 0x4062c0
006a8258 movss xmm0, dword ptr [ebp - 0x7c]
006a825d movss dword ptr [eax + 0x34], xmm0
006a8262 movss xmm0, dword ptr [ebp - 0x70]
006a8267 movss dword ptr [eax + 0x38], xmm0
006a826c movss xmm0, dword ptr [0xb6a6f0]
006a8274 comiss xmm0, dword ptr [esi]
006a8277 ja 0x6a8283
006a8279 cmp byte ptr [ebp - 0x69], 0
006a827d je 0x6a83df
006a8283 cmp dword ptr [ebp - 0x84], 0
006a828a jne 0x6a82b2
006a828c mov eax, dword ptr [0xbfd65c]
006a8291 push 0x384
006a8296 push ebx
006a8297 mov esi, dword ptr [eax + 0x18190]
006a829d mov ecx, esi
006a829f call 0x7ce950
006a82a4 push eax
006a82a5 mov ecx, esi
006a82a7 call 0x447f40
006a82ac lea esi, [edi + 0x2d8]
006a82b2 mov eax, dword ptr [edi + 0x30]
006a82b5 lea ecx, [edi + 0x3c]
006a82b8 push 0
006a82ba mov dword ptr [esi], 0x3f800000
006a82c0 mov dword ptr [edi + 0xab4], 3
006a82ca push dword ptr [eax*4 + 0xb46d2c]
006a82d1 mov dword ptr [edi + 0x180], 0
006a82db mov dword ptr [edi + 0x17c], 0
006a82e5 call 0x4054f0
006a82ea push ecx
006a82eb mov dword ptr [esp], 0x3f800000
006a82f2 push 0
006a82f4 push 2
006a82f6 push ecx
006a82f7 mov dword ptr [esp], 0x3f59999a
006a82fe mov ecx, edi
006a8300 push 0x105
006a8305 mov dword ptr [edi + 0x2ac], 0xfffffc18
006a830f call 0x6ad720
006a8314 mov eax, dword ptr [edi + 0x30]
006a8317 lea ecx, [edi + 0x3c]
006a831a push 0
006a831c push dword ptr [eax*4 + 0xb4936c]
006a8323 call 0x4054f0
006a8328 push 1
006a832a lea eax, [ebp - 0xb0]
006a8330 mov ecx, edi
006a8332 push eax
006a8333 call 0x6a77b0
006a8338 mov dword ptr [ebp - 4], 0
006a833f mov eax, dword ptr [ebp - 0xa4]
006a8345 mov esi, eax
006a8347 mov ebx, dword ptr [ebp - 0xb0]
006a834d mov edi, dword ptr [ebp - 0x88]
006a8353 mov ecx, dword ptr [ebp - 0xa0]
006a8359 add eax, ecx
006a835b cmp esi, eax
006a835d je 0x6a8392
006a835f test ebx, ebx
006a8361 je 0x6a8367
006a8363 mov eax, dword ptr [ebx]
006a8365 jmp 0x6a8369
006a8367 xor eax, eax
006a8369 mov ecx, dword ptr [eax + 8]
006a836c mov eax, dword ptr [eax + 4]
006a836f dec ecx
006a8370 and ecx, esi
006a8372 push 0
006a8374 push 0xc02fec
006a8379 push edi
006a837a mov ecx, dword ptr [eax + ecx*4]
006a837d call 0x7f86d0
006a8382 mov ecx, eax
006a8384 mov edx, dword ptr [eax]
006a8386 call dword ptr [edx + 0xc]
006a8389 mov eax, dword ptr [ebp - 0xa4]
006a838f inc esi
006a8390 jmp 0x6a8353
006a8392 mov edi, dword ptr [ebp - 0x74]
006a8395 test ecx, ecx
006a8397 je 0x6a83ab
006a8399 mov eax, dword ptr [0xbfd65c]
006a839e mov eax, dword ptr [eax + 0x18190]
006a83a4 mov byte ptr [eax + 0x7778], 1
006a83ab mov ecx, edi
006a83ad call 0x6b1270
006a83b2 lea ecx, [ebp - 0xb0]
006a83b8 mov dword ptr [ebp - 4], 0xffffffff
006a83bf call 0x6b15c0
006a83c4 mov eax, dword ptr [ebp - 0xb0]
006a83ca push 8
006a83cc push eax
006a83cd mov dword ptr [ebp - 0xb0], 0
006a83d7 call 0x9eb08e
006a83dc add esp, 8
006a83df xorps xmm1, xmm1
006a83e2 cmp byte ptr [edi + 0x16b], 0
006a83e9 je 0x6a83fc
006a83eb mov dword ptr [edi + 0x2d8], 0x3f800000
006a83f5 mov byte ptr [edi + 0x16b], 0
006a83fc mov eax, dword ptr [edi + 8]
006a83ff mov dword ptr [edi + 0xc], eax
006a8402 mov dword ptr [edi + 0x14], 0
006a8409 mov dword ptr [edi + 0x18], 0
006a8410 mov dword ptr [edi + 0x1c], 0
006a8417 mov eax, dword ptr [edi + 0x2c]
006a841a cmp eax, 1
006a841d je 0x6a8428
006a841f cmp eax, 3
006a8422 jne 0x6a85b6
006a8428 mov eax, dword ptr [edi + 0x34]
006a842b cmp eax, 0x389
006a8430 je 0x6a85b6
006a8436 cmp eax, 0x397
006a843b je 0x6a85b6
006a8441 cmp dword ptr [edi + 0xaf0], 0
006a8448 jg 0x6a85b6
006a844e cmp dword ptr [edi + 0xab4], 8
006a8455 jne 0x6a85b6
006a845b call 0x6c3d90
006a8460 xor edx, edx
006a8462 mov ecx, 5
006a8467 div ecx
006a8469 test edx, edx
006a846b jne 0x6a85b6
006a8471 movss xmm0, dword ptr [edi + 0x294]
006a8479 lea ebx, [edi + 0x294]
006a847f mov ecx, dword ptr [0xbfd65c]
006a8485 addss xmm0, xmm1
006a8489 push ebx
006a848a movss dword ptr [ebp - 0x70], xmm0
006a848f movss xmm0, dword ptr [ebx + 4]
006a8494 subss xmm0, dword ptr [0xb6a9ac]
006a849c movss dword ptr [ebp - 0x7c], xmm0
006a84a1 call 0x6d5e30
006a84a6 lea ecx, [ebp - 0x9c]
006a84ac movss xmm1, dword ptr [eax + 0x294]
006a84b4 movss xmm0, dword ptr [eax + 0x298]
006a84bc lea eax, [ebp - 0xb8]
006a84c2 movss dword ptr [ebp - 0x94], xmm1
006a84ca subss xmm1, dword ptr [ebp - 0x70]
006a84cf movss dword ptr [ebp - 0x90], xmm0
006a84d7 subss xmm0, dword ptr [ebp - 0x7c]
006a84dc push eax
006a84dd movss dword ptr [ebp - 0x88], xmm1
006a84e5 movss dword ptr [ebp - 0x9c], xmm1
006a84ed movss dword ptr [ebp - 0x74], xmm0
006a84f2 movss dword ptr [ebp - 0x98], xmm0
006a84fa call 0x962560
006a84ff movss xmm0, dword ptr [eax]
006a8503 mulss xmm0, dword ptr [0xb6a9ec]
006a850b movss xmm1, dword ptr [eax + 4]
006a8510 mulss xmm1, dword ptr [0xb6a9ec]
006a8518 addss xmm0, dword ptr [ebp - 0x70]
006a851d addss xmm1, dword ptr [ebp - 0x7c]
006a8522 movss dword ptr [ebp - 0x9c], xmm0
006a852a movss xmm0, dword ptr [ebp - 0x74]
006a852f movss dword ptr [ebp - 0x98], xmm1
006a8537 movss xmm1, dword ptr [ebp - 0x88]
006a853f mulss xmm0, xmm0
006a8543 mulss xmm1, xmm1
006a8547 addss xmm0, xmm1
006a854b call 0x4228c0
006a8550 movss xmm1, dword ptr [0xb6ab70]
006a8558 comiss xmm1, xmm0
006a855b jbe 0x6a85cd
006a855d mov ecx, dword ptr [0xbfd65c]
006a8563 lea eax, [ebp - 0x94]
006a8569 push 0
006a856b push 0
006a856d push 0
006a856f mov ecx, dword ptr [ecx + 0x18190]
006a8575 push 0
006a8577 push 3
006a8579 push eax
006a857a lea eax, [ebp - 0x9c]
006a8580 push eax
006a8581 call 0x7af4b0
006a8586 test al, al
006a8588 je 0x6a85cd
006a858a call 0x6c3d90
006a858f xor edx, edx
006a8591 mov ecx, 0xf
006a8596 div ecx
006a8598 test edx, edx
006a859a jne 0x6a85cd
006a859c push edx
006a859d push 0xb400ac
006a85a2 lea ecx, [edi + 0x3c]
006a85a5 call 0x405a00
006a85aa mov dword ptr [edi + 0xaf0], 0x54
006a85b4 jmp 0x6a85cd
006a85b6 mov eax, dword ptr [edi + 0xaf0]
006a85bc lea ebx, [edi + 0x294]
006a85c2 test eax, eax
006a85c4 jle 0x6a85cd
006a85c6 dec eax
006a85c7 mov dword ptr [edi + 0xaf0], eax
006a85cd cmp byte ptr [edi + 0xa0], 0
006a85d4 je 0x6a87b4
006a85da lea ecx, [edi + 0x8c]
006a85e0 push 0
006a85e2 call 0x405d30
006a85e7 mov dword ptr [ebp - 0x74], eax
006a85ea test eax, eax
006a85ec je 0x6a8651
006a85ee push 1
006a85f0 lea ecx, [edi + 0x3c]
006a85f3 call 0x4062c0
006a85f8 mov edx, dword ptr [ebp - 0x74]
006a85fb push 1
006a85fd mov ecx, dword ptr [edx]
006a85ff mov dword ptr [eax + 0x40], ecx
006a8602 mov ecx, dword ptr [edx + 4]
006a8605 mov dword ptr [eax + 0x44], ecx
006a8608 lea ecx, [edi + 0x3c]
006a860b movss xmm1, dword ptr [edi + 0x2d8]
006a8613 divss xmm1, dword ptr [edi + 0x2dc]
006a861b movaps xmm0, xmm1
006a861e mulss xmm1, dword ptr [edx + 0x14]
006a8623 mulss xmm0, dword ptr [edx + 0x10]
006a8628 movss dword ptr [ebp - 0x88], xmm1
006a8630 movss dword ptr [ebp - 0x74], xmm0
006a8635 call 0x4062c0
006a863a movss xmm0, dword ptr [ebp - 0x74]
006a863f movss dword ptr [eax + 0x34], xmm0
006a8644 movss xmm0, dword ptr [ebp - 0x88]
006a864c movss dword ptr [eax + 0x38], xmm0
006a8651 push 0xb400ac
006a8656 lea ecx, [edi + 0x8c]
006a865c call 0x405e90
006a8661 test al, al
006a8663 je 0x6a87b4
006a8669 mov eax, dword ptr [edi + 0x34]
006a866c cmp eax, 0x389
006a8671 je 0x6a87b4
006a8677 cmp eax, 0x397
006a867c je 0x6a87b4
006a8682 movss xmm0, dword ptr [ebx]
006a8686 addss xmm0, dword ptr [0xb6a18c]
006a868e mov ecx, dword ptr [0xbfd65c]
006a8694 push ebx
006a8695 movss dword ptr [ebp - 0x78], xmm0
006a869a movss xmm0, dword ptr [ebx + 4]
006a869f subss xmm0, dword ptr [0xb6a9ac]
006a86a7 movss dword ptr [ebp - 0x74], xmm0
006a86ac call 0x6d5e30
006a86b1 lea ecx, [ebp - 0x8c]
006a86b7 movss xmm0, dword ptr [eax + 0x294]
006a86bf movss xmm1, dword ptr [eax + 0x298]
006a86c7 lea eax, [ebp - 0xb8]
006a86cd subss xmm0, dword ptr [ebp - 0x78]
006a86d2 subss xmm1, dword ptr [ebp - 0x74]
006a86d7 push eax
006a86d8 movss dword ptr [ebp - 0x8c], xmm0
006a86e0 movss dword ptr [ebp - 0x88], xmm1
006a86e8 call 0x962560
006a86ed movss xmm1, dword ptr [eax + 4]
006a86f2 movss xmm0, dword ptr [eax]
006a86f6 mulss xmm0, dword ptr [0xb6a9ec]
006a86fe mulss xmm1, dword ptr [0xb6a9ec]
006a8706 addss xmm0, dword ptr [ebp - 0x78]
006a870b addss xmm1, dword ptr [ebp - 0x74]
006a8710 movss dword ptr [ebp - 0x78], xmm0
006a8715 movss dword ptr [ebp - 0x74], xmm1
006a871a call 0x6c3d90
006a871f mov esi, eax
006a8721 lea ecx, [ebp - 0x8c]
006a8727 lea eax, [ebp - 0xb8]
006a872d push eax
006a872e call 0x962560
006a8733 mov ecx, dword ptr [0xbfd65c]
006a8739 push 0
006a873b push 0xbeabf4
006a8740 movss xmm0, dword ptr [eax]
006a8744 mulss xmm0, dword ptr [0xb6a8f4]
006a874c push 0xbeab18
006a8751 push 0
006a8753 push esi
006a8754 push 0
006a8756 movss dword ptr [ebp - 0x94], xmm0
006a875e movss xmm0, dword ptr [eax + 4]
006a8763 lea eax, [ebp - 0x94]
006a8769 mulss xmm0, dword ptr [0xb6a8f4]
006a8771 push edi
006a8772 push eax
006a8773 lea eax, [ebp - 0x78]
006a8776 push eax
006a8777 push 0
006a8779 push 9
006a877b movss dword ptr [ebp - 0x90], xmm0
006a8783 call 0x422e20
006a8788 push eax
006a8789 call 0x9ec34c
006a878e add esp, 0x14
006a8791 cmp dword ptr [edi + 0x2c], 3
006a8795 jne 0x6a87b4
006a8797 mov ecx, dword ptr [eax + 0x38c]
006a879d or dword ptr [eax + 0x388], 1
006a87a4 mov dword ptr [eax + 0x38c], ecx
006a87aa mov dword ptr [eax + 0x370], 0x3fc00000
006a87b4 cmp dword ptr [edi + 0xab4], 8
006a87bb jne 0x6a89e1
006a87c1 call 0x6c3d90
006a87c6 xor edx, edx
006a87c8 mov ecx, 7
006a87cd div ecx
006a87cf test edx, edx
006a87d1 jne 0x6a89e1
006a87d7 call 0x6c3d90
006a87dc movss xmm3, dword ptr [0xb6a19c]
006a87e4 movd xmm0, eax
006a87e8 cvtdq2pd xmm0, xmm0
006a87ec shr eax, 0x1f
006a87ef addsd xmm0, qword ptr [eax*8 + 0xb6c940]
006a87f8 cvtpd2ps xmm2, xmm0
006a87fc mulss xmm2, xmm3
006a8800 call 0x6c3d90
006a8805 movss xmm1, dword ptr [0xb6aed0]
006a880d mulss xmm2, dword ptr [0xb6a9ac]
006a8815 movd xmm0, eax
006a8819 cvtdq2pd xmm0, xmm0
006a881d shr eax, 0x1f
006a8820 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
006a8829 cvtpd2ps xmm0, xmm0
006a882d mulss xmm0, xmm3
006a8831 mulss xmm0, dword ptr [0xb6a9b0]
006a8839 subss xmm0, dword ptr [0xb6a940]
006a8841 addss xmm0, dword ptr [ebx]
006a8845 movss dword ptr [ebp - 0x80], xmm0
006a884a movss xmm0, dword ptr [edi + 0x2d8]
006a8852 mulss xmm0, dword ptr [0xb6a9ac]
006a885a divss xmm0, dword ptr [0xb6a910]
006a8862 subss xmm1, xmm0
006a8866 subss xmm1, xmm2
006a886a addss xmm1, dword ptr [ebx + 4]
006a886f movss dword ptr [ebp - 0x7c], xmm1
006a8874 call 0x6c3d90
006a8879 movd xmm0, eax
006a887d cvtdq2pd xmm0, xmm0
006a8881 shr eax, 0x1f
006a8884 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
006a888d cvtpd2ps xmm1, xmm0
006a8891 mulss xmm1, xmm3
006a8895 call 0x6c3d90
006a889a mulss xmm1, dword ptr [0xb6ae58]
006a88a2 movd xmm0, eax
006a88a6 cvtdq2pd xmm0, xmm0
006a88aa shr eax, 0x1f
006a88ad subss xmm1, dword ptr [0xb6a560]
006a88b5 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
006a88be movss dword ptr [ebp - 0x90], xmm1
006a88c6 cvtpd2ps xmm0, xmm0
006a88ca mulss xmm0, xmm3
006a88ce mulss xmm0, dword ptr [0xb6a434]
006a88d6 subss xmm0, dword ptr [0xb6a350]
006a88de movss dword ptr [ebp - 0x94], xmm0
006a88e6 call 0x6c3d90
006a88eb mov ecx, dword ptr [0xbfd65c]
006a88f1 push eax
006a88f2 push 0
006a88f4 push edi
006a88f5 lea eax, [ebp - 0x94]
006a88fb push eax
006a88fc lea eax, [ebp - 0x80]
006a88ff push eax
006a8900 push 0x42
006a8902 push 0x3e8
006a8907 call 0x422e20
006a890c mov esi, eax
006a890e mov eax, dword ptr [edi + 0x2c]
006a8911 cmp eax, 1
006a8914 jne 0x6a894d
006a8916 movss xmm3, dword ptr [0xb6a3b0]
006a891e lea ecx, [ebp - 0x3c]
006a8921 movss xmm2, dword ptr [0xb6a480]
006a8929 movss xmm1, dword ptr [0xb6a614]
006a8931 mov edx, dword ptr [esi]
006a8933 push eax
006a8934 push 0
006a8936 push 0xff
006a893b push -1
006a893d call 0x427080
006a8942 push eax
006a8943 mov ecx, esi
006a8945 call dword ptr [edx + 0x38]
006a8948 jmp 0x6a89e1
006a894d cmp eax, 2
006a8950 jne 0x6a8982
006a8952 movaps xmm0, xmmword ptr [0xb6c610]
006a8959 movups xmmword ptr [ebp - 0x3c], xmm0
006a895d movaps xmm0, xmmword ptr [0xb6c6f0]
006a8964 movups xmmword ptr [ebp - 0x2c], xmm0
006a8968 mov dword ptr [ebp - 0x1c], 0
006a896f lea ecx, [ebp - 0x3c]
006a8972 mov dword ptr [ebp - 0x18], 0
006a8979 mov dword ptr [ebp - 0x14], 0
006a8980 jmp 0x6a89ce
006a8982 cmp eax, 3
006a8985 jne 0x6a899b
006a8987 movaps xmm0, xmmword ptr [0xb6c610]
006a898e movups xmmword ptr [ebp - 0x3c], xmm0
006a8992 movaps xmm0, xmmword ptr [0xb6c570]
006a8999 jmp 0x6a8964
006a899b cmp eax, 4
006a899e jne 0x6a89e1
006a89a0 movaps xmm0, xmmword ptr [0xb6c610]
006a89a7 lea ecx, [ebp - 0x68]
006a89aa movups xmmword ptr [ebp - 0x68], xmm0
006a89ae mov dword ptr [ebp - 0x48], 0
006a89b5 movaps xmm0, xmmword ptr [0xb6c700]
006a89bc movups xmmword ptr [ebp - 0x58], xmm0
006a89c0 mov dword ptr [ebp - 0x44], 0
006a89c7 mov dword ptr [ebp - 0x40], 0
006a89ce mov eax, dword ptr [esi]
006a89d0 push 1
006a89d2 push 0
006a89d4 push 0xff
006a89d9 push -1
006a89db push ecx
006a89dc mov ecx, esi
006a89de call dword ptr [eax + 0x38]
006a89e1 cmp dword ptr [edi + 0xab4], 3
006a89e8 jne 0x6a8a1d
006a89ea push dword ptr [ebx + 4]
006a89ed mov ecx, dword ptr [0xbfd65c]
006a89f3 push dword ptr [ebx]
006a89f5 mov ecx, dword ptr [ecx + 0x18190]
006a89fb call 0x7aee40
006a8a00 test eax, eax
006a8a02 je 0x6a8a1d
006a8a04 cmp dword ptr [ebp - 0x84], 0
006a8a0b jne 0x6a8a1d
006a8a0d mov eax, dword ptr [edi]
006a8a0f mov ecx, edi
006a8a11 call dword ptr [eax + 0x28]
006a8a14 jmp 0x6a8a1d
006a8a16 mov ecx, edi
006a8a18 call 0x6a7090
006a8a1d mov ecx, dword ptr [ebp - 0xc]
006a8a20 mov dword ptr fs:[0], ecx
006a8a27 pop ecx
006a8a28 pop edi
006a8a29 pop esi
006a8a2a pop ebx
006a8a2b mov ecx, dword ptr [ebp - 0x10]
006a8a2e xor ecx, ebp
006a8a30 call 0x9eacd7
006a8a35 mov esp, ebp
006a8a37 pop ebp
006a8a38 ret 
006a8a39 int3 
006a8a3a int3 
006a8a3b int3 
006a8a3c int3 
006a8a3d int3 
006a8a3e int3 
006a8a3f int3 
