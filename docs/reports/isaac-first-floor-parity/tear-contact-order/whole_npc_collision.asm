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
