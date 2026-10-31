004f9a70 push ebx
004f9a71 mov ebx, esp
004f9a73 sub esp, 8
004f9a76 and esp, 0xfffffff8
004f9a79 add esp, 4
004f9a7c push ebp
004f9a7d mov ebp, dword ptr [ebx + 4]
004f9a80 mov dword ptr [esp + 4], ebp
004f9a84 mov ebp, esp
004f9a86 push -1
004f9a88 push 0x9ef295
004f9a8d mov eax, dword ptr fs:[0]
004f9a93 push eax
004f9a94 push ebx
004f9a95 sub esp, 0x108
004f9a9b mov eax, dword ptr [0xbaa3b4]
004f9aa0 xor eax, ebp
004f9aa2 mov dword ptr [ebp - 0x14], eax
004f9aa5 push esi
004f9aa6 push edi
004f9aa7 push eax
004f9aa8 lea eax, [ebp - 0xc]
004f9aab mov dword ptr fs:[0], eax
004f9ab1 mov edi, ecx
004f9ab3 cmp dword ptr [edi + 0xab4], 0
004f9aba jne 0x4f9acb
004f9abc mov dword ptr [edi + 0xab4], 4
004f9ac6 jmp 0x4fa1bd
004f9acb push ecx
004f9acc lea eax, [ebp - 0x10c]
004f9ad2 mov dword ptr [esp], 0
004f9ad9 push eax
004f9ada call 0x695a30
004f9adf mov eax, dword ptr [edi + 0xab4]
004f9ae5 movss xmm0, dword ptr [0xb6a974]
004f9aed cmp eax, 4
004f9af0 jne 0x4f9e1a
004f9af6 cmp dword ptr [edi + 0x2c], 2
004f9afa jne 0x4f9ba6
004f9b00 push 1
004f9b02 push 0
004f9b04 push ecx
004f9b05 lea eax, [ebp - 0x10c]
004f9b0b mov dword ptr [esp], 0x3f99999a
004f9b12 push eax
004f9b13 lea ecx, [edi + 0x364]
004f9b19 call 0x7a3650
004f9b1e cmp dword ptr [edi + 0xe6c], -1
004f9b25 mov ecx, edi
004f9b27 je 0x4f9b36
004f9b29 push 9
004f9b2b call 0x6af050
004f9b30 test al, al
004f9b32 je 0x4f9b91
004f9b34 jmp 0x4f9b8a
004f9b36 movss xmm1, dword ptr [0xb6a8f4]
004f9b3e xorps xmm2, xmm2
004f9b41 call 0x6847e0
004f9b46 test eax, eax
004f9b48 je 0x4f9b91
004f9b4a mov ecx, edi
004f9b4c call 0x695680
004f9b51 movss xmm0, dword ptr [eax + 0x294]
004f9b59 movss xmm1, dword ptr [eax + 0x298]
004f9b61 subss xmm0, dword ptr [edi + 0x294]
004f9b69 subss xmm1, dword ptr [edi + 0x298]
004f9b71 mulss xmm0, xmm0
004f9b75 mulss xmm1, xmm1
004f9b79 addss xmm1, xmm0
004f9b7d movss xmm0, dword ptr [0xb6ace4]
004f9b85 comiss xmm0, xmm1
004f9b88 jbe 0x4f9b91
004f9b8a mov eax, dword ptr [edi]
004f9b8c mov ecx, edi
004f9b8e call dword ptr [eax + 0x24]
004f9b91 movss xmm0, dword ptr [edi + 0x2c4]
004f9b99 mulss xmm0, dword ptr [0xb6a5a4]
004f9ba1 jmp 0x4f9c5f
004f9ba6 cmp dword ptr [edi + 0xe6c], -1
004f9bad jne 0x4f9bd1
004f9baf mov ecx, edi
004f9bb1 call 0x695680
004f9bb6 push eax
004f9bb7 mov ecx, edi
004f9bb9 call 0x6aeb40
004f9bbe test al, al
004f9bc0 jne 0x4f9bd1
004f9bc2 push 1
004f9bc4 lea ecx, [edi + 0x364]
004f9bca call 0x7a6180
004f9bcf jmp 0x4f9c4f
004f9bd1 push 0
004f9bd3 lea eax, [ebp - 0x10c]
004f9bd9 push eax
004f9bda lea ecx, [edi + 0x364]
004f9be0 call 0x7a4830
004f9be5 cmp dword ptr [edi + 0xe6c], -1
004f9bec je 0x4f9c00
004f9bee push 0xa
004f9bf0 mov ecx, edi
004f9bf2 call 0x6af080
004f9bf7 movzx eax, al
004f9bfa test eax, eax
004f9bfc je 0x4f9c4f
004f9bfe jmp 0x4f9c1f
004f9c00 cmp dword ptr [edi + 0xaa0], 0
004f9c07 jle 0x4f9c4f
004f9c09 mov eax, dword ptr [0xbfd65c]
004f9c0e mov eax, dword ptr [eax + 0x1a30dc]
004f9c14 sub eax, dword ptr [edi + 0x280]
004f9c1a cmp eax, 0xa
004f9c1d jle 0x4f9c4f
004f9c1f call 0x6c3d90
004f9c24 mov ecx, 0x64
004f9c29 xor edx, edx
004f9c2b div ecx
004f9c2d push ecx
004f9c2e mov dword ptr [esp], 0x3f800000
004f9c35 push 0
004f9c37 lea eax, [edx + 0x2d]
004f9c3a push eax
004f9c3b push ecx
004f9c3c mov dword ptr [esp], 0x3f800000
004f9c43 mov ecx, edi
004f9c45 push 0x8f
004f9c4a call 0x6ad720
004f9c4f movss xmm0, dword ptr [edi + 0x2c4]
004f9c57 mulss xmm0, dword ptr [0xb6a560]
004f9c5f movss dword ptr [edi + 0x2c4], xmm0
004f9c67 mov eax, dword ptr [0xb404ec]
004f9c6c mov ecx, dword ptr [0xb404f0]
004f9c72 mov dword ptr [ebp - 0x30], 0xf
004f9c79 mov dword ptr [ebp - 0x34], 8
004f9c80 mov dword ptr [ebp - 0x44], eax
004f9c83 mov dword ptr [ebp - 0x40], ecx
004f9c86 mov byte ptr [ebp - 0x3c], 0
004f9c8a mov dword ptr [ebp - 4], 0
004f9c91 mov eax, dword ptr [0xb40504]
004f9c96 mov ecx, dword ptr [0xb40508]
004f9c9c mov dword ptr [ebp - 0x18], 0xf
004f9ca3 mov dword ptr [ebp - 0x1c], 8
004f9caa mov dword ptr [ebp - 0x2c], eax
004f9cad mov dword ptr [ebp - 0x28], ecx
004f9cb0 mov byte ptr [ebp - 0x24], 0
004f9cb4 push ecx
004f9cb5 mov byte ptr [ebp - 4], 1
004f9cb9 lea eax, [ebp - 0x44]
004f9cbc mov dword ptr [esp], 0x3dcccccd
004f9cc3 mov ecx, edi
004f9cc5 push eax
004f9cc6 lea eax, [ebp - 0x2c]
004f9cc9 push eax
004f9cca call 0x6980a0
004f9ccf mov byte ptr [ebp - 4], 0
004f9cd3 mov edx, dword ptr [ebp - 0x18]
004f9cd6 cmp edx, 0x10
004f9cd9 jb 0x4f9d03
004f9cdb mov ecx, dword ptr [ebp - 0x2c]
004f9cde inc edx
004f9cdf mov eax, ecx
004f9ce1 cmp edx, 0x1000
004f9ce7 jb 0x4f9cf9
004f9ce9 mov ecx, dword ptr [ecx - 4]
004f9cec add edx, 0x23
004f9cef sub eax, ecx
004f9cf1 add eax, -4
004f9cf4 cmp eax, 0x1f
004f9cf7 ja 0x4f9d42
004f9cf9 push edx
004f9cfa push ecx
004f9cfb call 0x9eb08e
004f9d00 add esp, 8
004f9d03 mov dword ptr [ebp - 4], 0xffffffff
004f9d0a mov edx, dword ptr [ebp - 0x30]
004f9d0d mov dword ptr [ebp - 0x1c], 0
004f9d14 mov dword ptr [ebp - 0x18], 0xf
004f9d1b mov byte ptr [ebp - 0x2c], 0
004f9d1f cmp edx, 0x10
004f9d22 jb 0x4f9d52
004f9d24 mov ecx, dword ptr [ebp - 0x44]
004f9d27 inc edx
004f9d28 mov eax, ecx
004f9d2a cmp edx, 0x1000
004f9d30 jb 0x4f9d48
004f9d32 mov ecx, dword ptr [ecx - 4]
004f9d35 add edx, 0x23
004f9d38 sub eax, ecx
004f9d3a add eax, -4
004f9d3d cmp eax, 0x1f
004f9d40 jbe 0x4f9d48
004f9d42 call dword ptr [0xa065ac]
004f9d48 push edx
004f9d49 push ecx
004f9d4a call 0x9eb08e
004f9d4f add esp, 8
004f9d52 cmp dword ptr [edi + 0xaa0], 0
004f9d59 jle 0x4f9d66
004f9d5b cmp dword ptr [edi + 0x2c], 2
004f9d5f mov eax, 0xb42f04
004f9d64 jne 0x4f9d6b
004f9d66 mov eax, 0xb41264
004f9d6b cmp dword ptr [edi + 0x70], 0
004f9d6f je 0x4f9d89
004f9d71 cmp byte ptr [edi + 0x80], 0
004f9d78 je 0x4f9d89
004f9d7a push 0
004f9d7c lea esi, [edi + 0x3c]
004f9d7f push eax
004f9d80 mov ecx, esi
004f9d82 call 0x405a00
004f9d87 jmp 0x4f9dab
004f9d89 push 1
004f9d8b lea esi, [edi + 0x3c]
004f9d8e push eax
004f9d8f mov ecx, esi
004f9d91 call 0x405bb0
004f9d96 test al, al
004f9d98 je 0x4f9dab
004f9d9a cmp dword ptr [esi + 0x54], 0
004f9d9e je 0x4f9dab
004f9da0 lea ecx, [esi + 0x50]
004f9da3 xorps xmm1, xmm1
004f9da6 call 0x403c00
004f9dab mov eax, dword ptr [edi + 0xe6c]
004f9db1 cmp eax, -1
004f9db4 je 0x4f9dd0
004f9db6 push edi
004f9db7 push eax
004f9db8 push 9
004f9dba call 0x8b10b0
004f9dbf xor ecx, ecx
004f9dc1 test al, al
004f9dc3 setne cl
004f9dc6 test ecx, ecx
004f9dc8 je 0x4f9f29
004f9dce jmp 0x4f9df3
004f9dd0 cmp byte ptr [edi + 0x188], 0
004f9dd7 je 0x4f9f29
004f9ddd call 0x6c3d90
004f9de2 xor edx, edx
004f9de4 mov ecx, 0x12c
004f9de9 div ecx
004f9deb test edx, edx
004f9ded jne 0x4f9f29
004f9df3 cmp dword ptr [edi + 0x2c], 2
004f9df7 je 0x4f9f29
004f9dfd push 0
004f9dff push 0xb42eec
004f9e04 mov ecx, esi
004f9e06 call 0x405a00
004f9e0b mov dword ptr [edi + 0xab4], 5
004f9e15 jmp 0x4f9f29
004f9e1a cmp eax, 5
004f9e1d jne 0x4f9f31
004f9e23 movss xmm0, dword ptr [edi + 0x2c4]
004f9e2b mulss xmm0, dword ptr [0xb6a560]
004f9e33 movss dword ptr [edi + 0x2c4], xmm0
004f9e3b cmp dword ptr [edi + 0x90], 0
004f9e42 je 0x4f9e51
004f9e44 cmp byte ptr [edi + 0xa0], 0
004f9e4b jne 0x4f9f29
004f9e51 movups xmm0, xmmword ptr [0xbfec58]
004f9e58 mov ecx, dword ptr [0xbfd65c]
004f9e5e lea esi, [edi + 0x294]
004f9e64 push 0
004f9e66 push 0
004f9e68 push 4
004f9e6a sub esp, 0x10
004f9e6d mov eax, esp
004f9e6f push edi
004f9e70 push 1
004f9e72 sub esp, 8
004f9e75 movups xmmword ptr [eax], xmm0
004f9e78 mov dword ptr [esp + 4], 0x42700000
004f9e80 mov dword ptr [esp], 0x42200000
004f9e87 push esi
004f9e88 call 0x6d1750
004f9e8d call 0x6c3d90
004f9e92 mov ecx, dword ptr [0xbfd65c]
004f9e98 push eax
004f9e99 push 0
004f9e9b push 0
004f9e9d push 0xc02fec
004f9ea2 push esi
004f9ea3 push 1
004f9ea5 push 0x3e8
004f9eaa call 0x422e20
004f9eaf call 0x6c3d90
004f9eb4 mov ecx, dword ptr [0xbfd65c]
004f9eba push eax
004f9ebb push 0
004f9ebd push 0
004f9ebf push 0xc02fec
004f9ec4 push esi
004f9ec5 push 0x12
004f9ec7 push 0x3e8
004f9ecc call 0x422e20
004f9ed1 mov ecx, eax
004f9ed3 mov edx, dword ptr [eax]
004f9ed5 call dword ptr [edx + 0xc]
004f9ed8 call 0x6af030
004f9edd test eax, eax
004f9edf jle 0x4f9eeb
004f9ee1 movss xmm0, dword ptr [0xb6a974]
004f9ee9 jmp 0x4f9ef3
004f9eeb movss xmm0, dword ptr [0xb6a928]
004f9ef3 lea ecx, [ebp - 0xf0]
004f9ef9 movss dword ptr [ebp - 0xf8], xmm0
004f9f01 mov dword ptr [ebp - 0xf4], 0
004f9f0b call 0x430d70
004f9f10 push eax
004f9f11 push 6
004f9f13 lea eax, [ebp - 0xf8]
004f9f19 mov ecx, edi
004f9f1b push eax
004f9f1c push esi
004f9f1d call 0x6a1a20
004f9f22 mov eax, dword ptr [edi]
004f9f24 mov ecx, edi
004f9f26 call dword ptr [eax + 0x24]
004f9f29 movss xmm0, dword ptr [0xb6a974]
004f9f31 cmp byte ptr [edi + 0x16b], 0
004f9f38 je 0x4fa1bd
004f9f3e mov eax, dword ptr [edi + 0x2c]
004f9f41 cmp eax, 2
004f9f44 jne 0x4f9fd6
004f9f4a movups xmm0, xmmword ptr [0xbfec58]
004f9f51 mov ecx, dword ptr [0xbfd65c]
004f9f57 lea esi, [edi + 0x294]
004f9f5d push 0
004f9f5f push 0
004f9f61 push 4
004f9f63 sub esp, 0x10
004f9f66 mov eax, esp
004f9f68 push edi
004f9f69 push 1
004f9f6b sub esp, 8
004f9f6e movups xmmword ptr [eax], xmm0
004f9f71 mov dword ptr [esp + 4], 0x42700000
004f9f79 mov dword ptr [esp], 0x42200000
004f9f80 push esi
004f9f81 call 0x6d1750
004f9f86 call 0x6c3d90
004f9f8b mov ecx, dword ptr [0xbfd65c]
004f9f91 push eax
004f9f92 push 0
004f9f94 push 0
004f9f96 push 0xc02fec
004f9f9b push esi
004f9f9c push 1
004f9f9e push 0x3e8
004f9fa3 call 0x422e20
004f9fa8 call 0x6c3d90
004f9fad mov ecx, dword ptr [0xbfd65c]
004f9fb3 push eax
004f9fb4 push 0
004f9fb6 push 0
004f9fb8 push 0xc02fec
004f9fbd push esi
004f9fbe push 0x12
004f9fc0 push 0x3e8
004f9fc5 call 0x422e20
004f9fca mov ecx, eax
004f9fcc mov edx, dword ptr [eax]
004f9fce call dword ptr [edx + 0xc]
004f9fd1 jmp 0x4fa1bd
004f9fd6 cmp eax, 1
004f9fd9 jne 0x4fa044
004f9fdb call 0x6af030
004f9fe0 test eax, eax
004f9fe2 jg 0x4f9fec
004f9fe4 movss xmm0, dword ptr [0xb6a928]
004f9fec lea ecx, [ebp - 0xf0]
004f9ff2 movss dword ptr [ebp - 0xf8], xmm0
004f9ffa mov dword ptr [ebp - 0xf4], 0
004fa004 lea esi, [edi + 0x294]
004fa00a call 0x430d70
004fa00f push eax
004fa010 push 7
004fa012 lea eax, [ebp - 0xf8]
004fa018 mov ecx, edi
004fa01a push eax
004fa01b push esi
004fa01c call 0x6a1a20
004fa021 call 0x6c3d90
004fa026 mov ecx, dword ptr [0xbfd65c]
004fa02c push eax
004fa02d push 0
004fa02f push edi
004fa030 push 0xc02fec
004fa035 push esi
004fa036 push 3
004fa038 push 4
004fa03a call 0x422e20
004fa03f jmp 0x4fa1bd
004fa044 movss xmm0, dword ptr [edi + 0x2d8]
004fa04c comiss xmm0, dword ptr [0xb6aeb8]
004fa053 jbe 0x4fa1bd
004fa059 movsx eax, word ptr [edi + 0xbc6]
004fa060 mov ecx, 4
004fa065 sub ecx, eax
004fa067 xor esi, esi
004fa069 test ecx, ecx
004fa06b cmovg esi, ecx
004fa06e mov dword ptr [ebp - 0x104], esi
004fa074 test esi, esi
004fa076 jle 0x4fa1bd
004fa07c movss xmm2, dword ptr [0xb6a19c]
004fa084 mov esi, 0xe
004fa089 nop dword ptr [eax]
004fa090 call 0x6c3d90
004fa095 xor edx, edx
004fa097 mov ecx, 0xb
004fa09c div ecx
004fa09e lea eax, [ecx + 2]
004fa0a1 cmp edx, 7
004fa0a4 jbe 0x4fa0b2
004fa0a6 mov dword ptr [ebp - 0x100], 0x12
004fa0b0 jmp 0x4fa0bb
004fa0b2 cmove eax, esi
004fa0b5 mov dword ptr [ebp - 0x100], eax
004fa0bb call 0x6c3d90
004fa0c0 movd xmm0, eax
004fa0c4 cvtdq2pd xmm0, xmm0
004fa0c8 shr eax, 0x1f
004fa0cb addsd xmm0, qword ptr [eax*8 + 0xb6c940]
004fa0d4 cvtpd2ps xmm1, xmm0
004fa0d8 mulss xmm1, xmm2
004fa0dc mulss xmm1, dword ptr [0xb6a874]
004fa0e4 addss xmm1, xmm1
004fa0e8 movss dword ptr [ebp - 0xf4], xmm1
004fa0f0 call 0x6c3d90
004fa0f5 movd xmm0, eax
004fa0f9 cvtdq2pd xmm0, xmm0
004fa0fd shr eax, 0x1f
004fa100 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
004fa109 cvtpd2ps xmm0, xmm0
004fa10d mulss xmm0, xmm2
004fa111 mulss xmm0, dword ptr [0xb6a910]
004fa119 movss dword ptr [ebp - 0xfc], xmm0
004fa121 call 0x6c3d90
004fa126 movaps xmm0, xmm1
004fa129 mov esi, eax
004fa12b call 0x411fe0
004fa130 mulss xmm0, dword ptr [ebp - 0xfc]
004fa138 addss xmm0, dword ptr [edi + 0x294]
004fa140 movss dword ptr [ebp - 0x114], xmm0
004fa148 movss xmm0, dword ptr [ebp - 0xf4]
004fa150 call 0x412010
004fa155 mulss xmm0, dword ptr [ebp - 0xfc]
004fa15d lea eax, [ebp - 0x114]
004fa163 mov ecx, dword ptr [0xbfd65c]
004fa169 push esi
004fa16a push 0
004fa16c addss xmm0, dword ptr [edi + 0x298]
004fa174 push edi
004fa175 push 0xc02fec
004fa17a push eax
004fa17b push 0
004fa17d push dword ptr [ebp - 0x100]
004fa183 movss dword ptr [ebp - 0x110], xmm0
004fa18b call 0x422e20
004fa190 movss xmm2, dword ptr [0xb6a19c]
004fa198 mov esi, 0xe
004fa19d and dword ptr [eax + 0x160], 0xfffffffb
004fa1a4 sub dword ptr [ebp - 0x104], 1
004fa1ab mov ecx, dword ptr [eax + 0x164]
004fa1b1 mov dword ptr [eax + 0x164], ecx
004fa1b7 jne 0x4fa090
004fa1bd mov ecx, dword ptr [ebp - 0xc]
004fa1c0 mov dword ptr fs:[0], ecx
004fa1c7 pop ecx
004fa1c8 pop edi
004fa1c9 pop esi
004fa1ca mov ecx, dword ptr [ebp - 0x14]
004fa1cd xor ecx, ebp
004fa1cf call 0x9eacd7
004fa1d4 mov esp, ebp
004fa1d6 pop ebp
004fa1d7 mov esp, ebx
004fa1d9 pop ebx
004fa1da ret 
