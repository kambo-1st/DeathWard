005099c0 push ebx
005099c1 mov ebx, esp
005099c3 sub esp, 8
005099c6 and esp, 0xfffffff8
005099c9 add esp, 4
005099cc push ebp
005099cd mov ebp, dword ptr [ebx + 4]
005099d0 mov dword ptr [esp + 4], ebp
005099d4 mov ebp, esp
005099d6 push -1
005099d8 push 0x9ef515
005099dd mov eax, dword ptr fs:[0]
005099e3 push eax
005099e4 push ebx
005099e5 sub esp, 0x178
005099eb mov eax, dword ptr [0xbaa3b4]
005099f0 xor eax, ebp
005099f2 mov dword ptr [ebp - 0x14], eax
005099f5 push esi
005099f6 push edi
005099f7 push eax
005099f8 lea eax, [ebp - 0xc]
005099fb mov dword ptr fs:[0], eax
00509a01 mov edi, ecx
00509a03 mov dword ptr [ebp - 0x11c], edi
00509a09 cmp dword ptr [edi + 0xab4], 0
00509a10 jne 0x509aed
00509a16 mov eax, dword ptr [edi + 0x2c]
00509a19 mov dword ptr [edi + 0xab4], 4
00509a23 cmp eax, 1
00509a26 jne 0x509a86
00509a28 movaps xmm2, xmmword ptr [0xb6c0b0]
00509a2f lea eax, [ebp - 0x150]
00509a35 add edi, 0x1dc
00509a3b mov dword ptr [ebp - 0x130], 0
00509a45 mov dword ptr [ebp - 0x12c], 0x3f000000
00509a4f xorps xmm1, xmm1
00509a52 mov dword ptr [ebp - 0x128], 0
00509a5c cmp edi, eax
00509a5e je 0x50a429
00509a64 movq xmm0, qword ptr [ebp - 0x130]
00509a6c mov eax, dword ptr [ebp - 0x128]
00509a72 movq qword ptr [edi + 0x20], xmm0
00509a77 movups xmmword ptr [edi], xmm2
00509a7a mov dword ptr [edi + 0x28], eax
00509a7d movups xmmword ptr [edi + 0x10], xmm1
00509a81 jmp 0x50a429
00509a86 cmp eax, 2
00509a89 jne 0x50a429
00509a8f movaps xmm2, xmmword ptr [0xb6bd30]
00509a96 lea eax, [ebp - 0x17c]
00509a9c add edi, 0x1dc
00509aa2 mov dword ptr [ebp - 0x15c], 0x3f800000
00509aac mov dword ptr [ebp - 0x158], 0x3f800000
00509ab6 xorps xmm1, xmm1
00509ab9 mov dword ptr [ebp - 0x154], 0x3f800000
00509ac3 cmp edi, eax
00509ac5 je 0x50a429
00509acb movq xmm0, qword ptr [ebp - 0x15c]
00509ad3 mov eax, dword ptr [ebp - 0x154]
00509ad9 movq qword ptr [edi + 0x20], xmm0
00509ade movups xmmword ptr [edi], xmm2
00509ae1 mov dword ptr [edi + 0x28], eax
00509ae4 movups xmmword ptr [edi + 0x10], xmm1
00509ae8 jmp 0x50a429
00509aed movss xmm1, dword ptr [edi + 0x14]
00509af2 xorps xmm0, xmm0
00509af5 comiss xmm1, xmm0
00509af8 jbe 0x509b4a
00509afa mov eax, dword ptr [edi + 8]
00509afd cmp eax, dword ptr [edi + 0xc]
00509b00 je 0x509b4a
00509b02 mov ecx, dword ptr [eax + 0xc]
00509b05 mov edx, dword ptr [eax + 8]
00509b08 mov dword ptr [ebp - 0x10c], ecx
00509b0e mov ecx, edx
00509b10 and ecx, 4
00509b13 or ecx, 0
00509b16 je 0x509b42
00509b18 mov ecx, dword ptr [eax + 0x30]
00509b1b shr ecx, 1
00509b1d test cl, 1
00509b20 jne 0x509b42
00509b22 cmp dword ptr [eax + 0x10], 1
00509b26 je 0x509b42
00509b28 mov ecx, dword ptr [eax + 0x18]
00509b2b cmp ecx, 1
00509b2e je 0x509b42
00509b30 cmp ecx, 3
00509b33 je 0x509b42
00509b35 and edx, 0x1000
00509b3b or edx, 0
00509b3e jne 0x509b42
00509b40 mov dword ptr [eax], edx
00509b42 add eax, 0x38
00509b45 cmp eax, dword ptr [edi + 0xc]
00509b48 jne 0x509b02
00509b4a movss xmm0, dword ptr [edi + 0x2c4]
00509b52 mov ecx, edi
00509b54 mulss xmm0, dword ptr [0xb6a53c]
00509b5c movss dword ptr [edi + 0x2c4], xmm0
00509b64 call 0x695680
00509b69 movss xmm1, dword ptr [eax + 0x294]
00509b71 movss xmm0, dword ptr [eax + 0x298]
00509b79 subss xmm0, dword ptr [edi + 0x298]
00509b81 subss xmm1, dword ptr [edi + 0x294]
00509b89 mulss xmm0, xmm0
00509b8d mulss xmm1, xmm1
00509b91 addss xmm0, xmm1
00509b95 call 0x4228c0
00509b9a cmp dword ptr [edi + 0xab4], 4
00509ba1 movss dword ptr [ebp - 0x114], xmm0
00509ba9 jne 0x509e13
00509baf mov eax, dword ptr [edi + 0x160]
00509bb5 and eax, 0x1000800
00509bba or eax, 0
00509bbd je 0x509c15
00509bbf cmp dword ptr [edi + 0xe6c], -1
00509bc6 jne 0x509c15
00509bc8 mov ecx, edi
00509bca call 0x695680
00509bcf push 0
00509bd1 mov ecx, dword ptr [eax + 0x294]
00509bd7 mov eax, dword ptr [eax + 0x298]
00509bdd mov dword ptr [ebp - 0x10c], eax
00509be3 lea eax, [ebp - 0x110]
00509be9 mov dword ptr [ebp - 0x110], ecx
00509bef lea ecx, [edi + 0x364]
00509bf5 push eax
00509bf6 call 0x7a4830
00509bfb movss xmm0, dword ptr [edi + 0x2c4]
00509c03 mulss xmm0, dword ptr [0xb6a560]
00509c0b movss dword ptr [edi + 0x2c4], xmm0
00509c13 jmp 0x509c22
00509c15 push 0
00509c17 lea ecx, [edi + 0x364]
00509c1d call 0x7a6180
00509c22 mov eax, dword ptr [0xb404ec]
00509c27 mov ecx, dword ptr [0xb404f0]
00509c2d mov dword ptr [ebp - 0x30], 0xf
00509c34 mov dword ptr [ebp - 0x34], 8
00509c3b mov dword ptr [ebp - 0x44], eax
00509c3e mov dword ptr [ebp - 0x40], ecx
00509c41 mov byte ptr [ebp - 0x3c], 0
00509c45 mov dword ptr [ebp - 4], 0
00509c4c mov eax, dword ptr [0xb40504]
00509c51 mov ecx, dword ptr [0xb40508]
00509c57 mov dword ptr [ebp - 0x18], 0xf
00509c5e mov dword ptr [ebp - 0x1c], 8
00509c65 mov dword ptr [ebp - 0x2c], eax
00509c68 mov dword ptr [ebp - 0x28], ecx
00509c6b mov byte ptr [ebp - 0x24], 0
00509c6f push ecx
00509c70 mov byte ptr [ebp - 4], 1
00509c74 lea eax, [ebp - 0x44]
00509c77 mov dword ptr [esp], 0x3dcccccd
00509c7e mov ecx, edi
00509c80 push eax
00509c81 lea eax, [ebp - 0x2c]
00509c84 push eax
00509c85 call 0x6980a0
00509c8a mov byte ptr [ebp - 4], 0
00509c8e mov edx, dword ptr [ebp - 0x18]
00509c91 cmp edx, 0x10
00509c94 jb 0x509cbe
00509c96 mov ecx, dword ptr [ebp - 0x2c]
00509c99 inc edx
00509c9a mov eax, ecx
00509c9c cmp edx, 0x1000
00509ca2 jb 0x509cb4
00509ca4 mov ecx, dword ptr [ecx - 4]
00509ca7 add edx, 0x23
00509caa sub eax, ecx
00509cac add eax, -4
00509caf cmp eax, 0x1f
00509cb2 ja 0x509cfd
00509cb4 push edx
00509cb5 push ecx
00509cb6 call 0x9eb08e
00509cbb add esp, 8
00509cbe mov dword ptr [ebp - 4], 0xffffffff
00509cc5 mov edx, dword ptr [ebp - 0x30]
00509cc8 mov dword ptr [ebp - 0x1c], 0
00509ccf mov dword ptr [ebp - 0x18], 0xf
00509cd6 mov byte ptr [ebp - 0x2c], 0
00509cda cmp edx, 0x10
00509cdd jb 0x509d0d
00509cdf mov ecx, dword ptr [ebp - 0x44]
00509ce2 inc edx
00509ce3 mov eax, ecx
00509ce5 cmp edx, 0x1000
00509ceb jb 0x509d03
00509ced mov ecx, dword ptr [ecx - 4]
00509cf0 add edx, 0x23
00509cf3 sub eax, ecx
00509cf5 add eax, -4
00509cf8 cmp eax, 0x1f
00509cfb jbe 0x509d03
00509cfd call dword ptr [0xa065ac]
00509d03 push edx
00509d04 push ecx
00509d05 call 0x9eb08e
00509d0a add esp, 8
00509d0d cmp dword ptr [edi + 0xe6c], -1
00509d14 je 0x509d2e
00509d16 movss xmm1, dword ptr [0xb6accc]
00509d1e mov ecx, edi
00509d20 push 7
00509d22 push 0
00509d24 call 0x6a15a0
00509d29 movzx edx, al
00509d2c jmp 0x509d41
00509d2e call 0x6c3d90
00509d33 xor edx, edx
00509d35 mov ecx, 0x32
00509d3a div ecx
00509d3c neg edx
00509d3e sbb edx, edx
00509d40 inc edx
00509d41 test edx, edx
00509d43 je 0x509e04
00509d49 mov eax, dword ptr [edi + 0x160]
00509d4f and eax, 0x1000a00
00509d54 or eax, 0
00509d57 jne 0x509e04
00509d5d cmp dword ptr [edi + 0xe6c], -1
00509d64 jne 0x509d84
00509d66 movss xmm0, dword ptr [0xb6abd0]
00509d6e comiss xmm0, dword ptr [ebp - 0x114]
00509d75 ja 0x509d84
00509d77 call 0x6c3d90
00509d7c test al, 3
00509d7e jne 0x509e04
00509d84 cmp dword ptr [edi + 0x2c], 2
00509d88 jne 0x509da1
00509d8a mov ecx, edi
00509d8c call 0x6ad7a0
00509d91 cmp eax, 8
00509d94 jge 0x509e04
00509d96 mov ecx, eax
00509d98 call 0x659230
00509d9d test eax, eax
00509d9f jne 0x509e04
00509da1 cmp dword ptr [edi + 0xe6c], -1
00509da8 jne 0x509dc4
00509daa movss xmm0, dword ptr [0xc02fec]
00509db2 movss dword ptr [edi + 0xe70], xmm0
00509dba movss xmm0, dword ptr [0xc02ff0]
00509dc2 jmp 0x509df2
00509dc4 movss xmm2, dword ptr [0xb6a2cc]
00509dcc lea eax, [ebp - 0x110]
00509dd2 push eax
00509dd3 mov ecx, edi
00509dd5 call 0x6af380
00509dda movss xmm0, dword ptr [ebp - 0x110]
00509de2 movss dword ptr [edi + 0xe70], xmm0
00509dea movss xmm0, dword ptr [ebp - 0x10c]
00509df2 movss dword ptr [edi + 0xe74], xmm0
00509dfa mov dword ptr [edi + 0xab4], 8
00509e04 mov dword ptr [edi + 0xaf0], 0
00509e0e jmp 0x50a429
00509e13 cmp dword ptr [edi + 0xe6c], -1
00509e1a jne 0x509e36
00509e1c movss xmm0, dword ptr [0xc02fec]
00509e24 movss dword ptr [edi + 0xe70], xmm0
00509e2c movss xmm0, dword ptr [0xc02ff0]
00509e34 jmp 0x509e7e
00509e36 movss xmm2, dword ptr [0xb6a2cc]
00509e3e lea eax, [ebp - 0x110]
00509e44 push eax
00509e45 mov ecx, edi
00509e47 call 0x6af380
00509e4c movss xmm1, dword ptr [ebp - 0x110]
00509e54 ucomiss xmm1, dword ptr [0xc02fec]
00509e5b movss xmm0, dword ptr [ebp - 0x10c]
00509e63 lahf 
00509e64 test ah, 0x44
00509e67 jp 0x509e76
00509e69 ucomiss xmm0, dword ptr [0xc02ff0]
00509e70 lahf 
00509e71 test ah, 0x44
00509e74 jnp 0x509e86
00509e76 movss dword ptr [edi + 0xe70], xmm1
00509e7e movss dword ptr [edi + 0xe74], xmm0
00509e86 mov esi, dword ptr [edi + 0x70]
00509e89 test esi, esi
00509e8b je 0x509edb
00509e8d cmp dword ptr [esi + 0x14], 0x10
00509e91 mov eax, esi
00509e93 jb 0x509e97
00509e95 mov eax, dword ptr [esi]
00509e97 mov ecx, 0xb400ac
00509e9c nop dword ptr [eax]
00509ea0 mov dl, byte ptr [eax]
00509ea2 cmp dl, byte ptr [ecx]
00509ea4 jne 0x509ec0
00509ea6 test dl, dl
00509ea8 je 0x509ebc
00509eaa mov dl, byte ptr [eax + 1]
00509ead cmp dl, byte ptr [ecx + 1]
00509eb0 jne 0x509ec0
00509eb2 add eax, 2
00509eb5 add ecx, 2
00509eb8 test dl, dl
00509eba jne 0x509ea0
00509ebc xor eax, eax
00509ebe jmp 0x509ec5
00509ec0 sbb eax, eax
00509ec2 or eax, 1
00509ec5 test eax, eax
00509ec7 jne 0x509edb
00509ec9 cmp byte ptr [esi + 0x34], al
00509ecc je 0x509efc
00509ece cmp byte ptr [edi + 0x80], al
00509ed4 lea esi, [edi + 0x3c]
00509ed7 jne 0x509efc
00509ed9 jmp 0x509ede
00509edb lea esi, [edi + 0x3c]
00509ede push 1
00509ee0 push 0xb400ac
00509ee5 mov ecx, esi
00509ee7 call 0x405740
00509eec test al, al
00509eee je 0x509efc
00509ef0 lea ecx, [esi + 0x30]
00509ef3 call 0x405330
00509ef8 mov byte ptr [esi + 0x44], 1
00509efc cmp dword ptr [edi + 0x70], 0
00509f00 je 0x50a41f
00509f06 push 0xb400ac
00509f0b lea ecx, [edi + 0x6c]
00509f0e call 0x405e90
00509f13 test al, al
00509f15 je 0x50a410
00509f1b call 0x6c3d90
00509f20 movd xmm0, eax
00509f24 cvtdq2pd xmm0, xmm0
00509f28 shr eax, 0x1f
00509f2b addsd xmm0, qword ptr [eax*8 + 0xb6c940]
00509f34 cvtpd2ps xmm1, xmm0
00509f38 movss xmm0, dword ptr [0xb6abec]
00509f40 mulss xmm1, dword ptr [0xb6a19c]
00509f48 mulss xmm1, dword ptr [0xb6a9c8]
00509f50 subss xmm0, xmm1
00509f54 comiss xmm0, dword ptr [ebp - 0x114]
00509f5b jbe 0x509f9b
00509f5d cmp dword ptr [edi + 0x34], 0x24
00509f61 je 0x509f9b
00509f63 mov ecx, edi
00509f65 mov byte ptr [ebp - 0x101], 1
00509f6c call 0x695680
00509f71 movss xmm2, dword ptr [0xc02ff0]
00509f79 movss xmm3, dword ptr [0xc02fec]
00509f81 mov ecx, dword ptr [eax + 0x294]
00509f87 mov eax, dword ptr [eax + 0x298]
00509f8d mov dword ptr [ebp - 0x118], ecx
00509f93 mov dword ptr [ebp - 0x114], eax
00509f99 jmp 0x509fc2
00509f9b movss xmm3, dword ptr [0xc02fec]
00509fa3 movss xmm2, dword ptr [0xc02ff0]
00509fab mov byte ptr [ebp - 0x101], 0
00509fb2 movss dword ptr [ebp - 0x118], xmm3
00509fba movss dword ptr [ebp - 0x114], xmm2
00509fc2 cmp dword ptr [edi + 0xe6c], -1
00509fc9 lea ecx, [ebp - 0x118]
00509fcf movss xmm0, dword ptr [ecx]
00509fd3 movss dword ptr [ebp - 0x110], xmm0
00509fdb movss xmm0, dword ptr [ecx + 4]
00509fe0 movss dword ptr [ebp - 0x10c], xmm0
00509fe8 je 0x50a04f
00509fea movss xmm1, dword ptr [edi + 0xe70]
00509ff2 ucomiss xmm1, xmm3
00509ff5 lahf 
00509ff6 test ah, 0x44
00509ff9 jp 0x50a017
00509ffb movss xmm0, dword ptr [edi + 0xe74]
0050a003 ucomiss xmm0, xmm2
0050a006 lahf 
0050a007 test ah, 0x44
0050a00a jp 0x50a017
0050a00c movss xmm1, dword ptr [ecx]
0050a010 movss xmm2, dword ptr [ecx + 4]
0050a015 jmp 0x50a03f
0050a017 movss xmm2, dword ptr [edi + 0xe74]
0050a01f mulss xmm2, dword ptr [0xb6ab58]
0050a027 mulss xmm1, dword ptr [0xb6ab58]
0050a02f addss xmm2, dword ptr [edi + 0x298]
0050a037 addss xmm1, dword ptr [edi + 0x294]
0050a03f movss dword ptr [ebp - 0x110], xmm1
0050a047 movss dword ptr [ebp - 0x10c], xmm2
0050a04f mov eax, dword ptr [edi + 0x2c]
0050a052 push ecx
0050a053 mov dword ptr [esp], 0x3f800000
0050a05a push 0
0050a05c push 2
0050a05e push ecx
0050a05f mov ecx, edi
0050a061 test eax, eax
0050a063 jne 0x50a0ab
0050a065 mov dword ptr [esp], 0x3f800000
0050a06c push 0xb2
0050a071 call 0x6ad720
0050a076 call 0x6c3d90
0050a07b mov esi, eax
0050a07d lea ecx, [ebp - 0x100]
0050a083 and esi, 1
0050a086 call 0x430d70
0050a08b push eax
0050a08c push ecx
0050a08d mov dword ptr [esp], 0x41200000
0050a094 lea eax, [ebp - 0x110]
0050a09a push eax
0050a09b lea eax, [esi + 3]
0050a09e mov ecx, edi
0050a0a0 push eax
0050a0a1 call 0x6a3420
0050a0a6 jmp 0x50a410
0050a0ab cmp eax, 1
0050a0ae jne 0x50a1ea
0050a0b4 mov dword ptr [esp], 0x3f333333
0050a0bb push 0xd5
0050a0c0 call 0x6ad720
0050a0c5 lea ecx, [ebp - 0x100]
0050a0cb call 0x430d70
0050a0d0 push eax
0050a0d1 push ecx
0050a0d2 mov dword ptr [esp], 0x41200000
0050a0d9 lea eax, [ebp - 0x110]
0050a0df push eax
0050a0e0 push 1
0050a0e2 mov ecx, edi
0050a0e4 call 0x6a3420
0050a0e9 mov esi, eax
0050a0eb or dword ptr [esi + 0x388], 2
0050a0f2 cmp byte ptr [ebp - 0x101], 0
0050a0f9 movss xmm1, dword ptr [esi + 0x2b8]
0050a101 movss xmm2, dword ptr [esi + 0x2bc]
0050a109 mov ecx, dword ptr [esi + 0x38c]
0050a10f mulss xmm1, dword ptr [0xb6a4a0]
0050a117 mov dword ptr [esi + 0x38c], ecx
0050a11d mulss xmm2, dword ptr [0xb6a4a0]
0050a125 mov dword ptr [esi + 0x370], 0x3fcccccd
0050a12f je 0x50a166
0050a131 call 0x6c3d90
0050a136 movd xmm0, eax
0050a13a cvtdq2pd xmm0, xmm0
0050a13e shr eax, 0x1f
0050a141 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
0050a14a cvtpd2ps xmm0, xmm0
0050a14e mulss xmm0, dword ptr [0xb6a19c]
0050a156 addss xmm0, dword ptr [0xb6a4c4]
0050a15e mulss xmm1, xmm0
0050a162 mulss xmm2, xmm0
0050a166 movss xmm0, dword ptr [esi + 0x368]
0050a16e lea ecx, [ebp - 0x58]
0050a171 subss xmm0, dword ptr [0xb6a3b0]
0050a179 movss dword ptr [esi + 0x2b8], xmm1
0050a181 movss dword ptr [esi + 0x2bc], xmm2
0050a189 movss dword ptr [esi + 0x368], xmm0
0050a191 movss xmm0, dword ptr [esi + 0x364]
0050a199 mulss xmm0, dword ptr [0xb6a50c]
0050a1a1 subss xmm0, dword ptr [0xb6a994]
0050a1a9 movss dword ptr [esi + 0x364], xmm0
0050a1b1 movss xmm0, dword ptr [0xb6a614]
0050a1b9 movaps xmm3, xmm0
0050a1bc movaps xmm2, xmm0
0050a1bf movaps xmm1, xmm0
0050a1c2 call 0x427080
0050a1c7 movaps xmm0, xmmword ptr [0xb6c330]
0050a1ce push 1
0050a1d0 push 0
0050a1d2 push 0xff
0050a1d7 movups xmmword ptr [ebp - 0x48], xmm0
0050a1db mov eax, dword ptr [esi]
0050a1dd push -1
0050a1df push ecx
0050a1e0 mov ecx, esi
0050a1e2 call dword ptr [eax + 0x38]
0050a1e5 jmp 0x50a410
0050a1ea mov dword ptr [esp], 0x3f800000
0050a1f1 push 0xb5
0050a1f6 call 0x6ad720
0050a1fb cmp dword ptr [edi + 0xe6c], -1
0050a202 lea esi, [edi + 0x294]
0050a208 je 0x50a25e
0050a20a movss xmm0, dword ptr [edi + 0xe70]
0050a212 lea eax, [ebp - 0x110]
0050a218 mulss xmm0, dword ptr [0xb6aad4]
0050a220 push 0
0050a222 push 0
0050a224 push ecx
0050a225 addss xmm0, dword ptr [esi]
0050a229 mov dword ptr [esp], 0
0050a230 push eax
0050a231 lea eax, [ebp - 0x124]
0050a237 movss dword ptr [ebp - 0x110], xmm0
0050a23f movss xmm0, dword ptr [edi + 0xe74]
0050a247 mulss xmm0, dword ptr [0xb6aad4]
0050a24f addss xmm0, dword ptr [esi + 4]
0050a254 movss dword ptr [ebp - 0x10c], xmm0
0050a25c jmp 0x50a2d5
0050a25e cmp byte ptr [ebp - 0x101], 0
0050a265 je 0x50a2c2
0050a267 mov ecx, edi
0050a269 call 0x695680
0050a26e push 0
0050a270 push 0
0050a272 push ecx
0050a273 movss xmm1, dword ptr [eax + 0x294]
0050a27b movss xmm2, dword ptr [eax + 0x298]
0050a283 lea eax, [ebp - 0x110]
0050a289 addss xmm1, dword ptr [esi]
0050a28d addss xmm2, dword ptr [esi + 4]
0050a292 mov dword ptr [esp], 0x428c0000
0050a299 push eax
0050a29a lea eax, [ebp - 0x124]
0050a2a0 mulss xmm1, dword ptr [0xb6a480]
0050a2a8 mulss xmm2, dword ptr [0xb6a480]
0050a2b0 movss dword ptr [ebp - 0x110], xmm1
0050a2b8 movss dword ptr [ebp - 0x10c], xmm2
0050a2c0 jmp 0x50a2d5
0050a2c2 push 0
0050a2c4 push 0
0050a2c6 push ecx
0050a2c7 mov dword ptr [esp], 0x42c80000
0050a2ce lea eax, [ebp - 0x184]
0050a2d4 push esi
0050a2d5 mov ecx, dword ptr [0xbfd65c]
0050a2db push eax
0050a2dc mov ecx, dword ptr [ecx + 0x18190]
0050a2e2 call 0x7cf240
0050a2e7 movss xmm0, dword ptr [eax]
0050a2eb movss dword ptr [ebp - 0x118], xmm0
0050a2f3 movss xmm0, dword ptr [eax + 4]
0050a2f8 movss dword ptr [ebp - 0x114], xmm0
0050a300 call 0x6c3d90
0050a305 mov ecx, dword ptr [0xbfd65c]
0050a30b push 0
0050a30d push 0xbeab70
0050a312 push 0xbeab18
0050a317 push 0
0050a319 push eax
0050a31a push 0
0050a31c push edi
0050a31d push 0xc02fec
0050a322 lea eax, [ebp - 0x118]
0050a328 push eax
0050a329 push 0
0050a32b push 0x55
0050a32d call 0x422e20
0050a332 push eax
0050a333 call 0x9ec34c
0050a338 mov ecx, dword ptr [0xbfd65c]
0050a33e add esp, 0x14
0050a341 mov edi, eax
0050a343 lea eax, [ebp - 0x118]
0050a349 mov esi, dword ptr [ecx + 0x18190]
0050a34f mov ecx, esi
0050a351 push 0x384
0050a356 push eax
0050a357 call 0x7ce950
0050a35c push eax
0050a35d mov ecx, esi
0050a35f call 0x447f40
0050a364 movss xmm4, dword ptr [edi + 0x294]
0050a36c mov eax, dword ptr [ebp - 0x11c]
0050a372 movss xmm0, dword ptr [edi + 0x2a8]
0050a37a subss xmm0, dword ptr [0xb6aa0c]
0050a382 movss dword ptr [edi + 0x28c], xmm4
0050a38a movss xmm3, dword ptr [edi + 0x298]
0050a392 movss dword ptr [edi + 0x290], xmm3
0050a39a movss xmm2, dword ptr [eax + 0x294]
0050a3a2 movss dword ptr [edi + 0x294], xmm2
0050a3aa subss xmm4, xmm2
0050a3ae movss xmm1, dword ptr [eax + 0x298]
0050a3b6 subss xmm3, xmm1
0050a3ba movss dword ptr [edi + 0x298], xmm1
0050a3c2 movss dword ptr [edi + 0x2a8], xmm0
0050a3ca mov dword ptr [edi + 0xab4], 6
0050a3d4 mulss xmm4, dword ptr [0xb6a264]
0050a3dc mov dword ptr [edi + 0xb0c], 0xc1000000
0050a3e6 mulss xmm3, dword ptr [0xb6a264]
0050a3ee movss dword ptr [edi + 0x2b8], xmm4
0050a3f6 movss dword ptr [edi + 0xb00], xmm4
0050a3fe movss dword ptr [edi + 0x2bc], xmm3
0050a406 movss dword ptr [edi + 0xb04], xmm3
0050a40e mov edi, eax
0050a410 cmp dword ptr [edi + 0x70], 0
0050a414 je 0x50a41f
0050a416 cmp byte ptr [edi + 0x80], 0
0050a41d jne 0x50a429
0050a41f mov dword ptr [edi + 0xab4], 4
0050a429 mov ecx, dword ptr [ebp - 0xc]
0050a42c mov dword ptr fs:[0], ecx
0050a433 pop ecx
0050a434 pop edi
0050a435 pop esi
0050a436 mov ecx, dword ptr [ebp - 0x14]
0050a439 xor ecx, ebp
0050a43b call 0x9eacd7
0050a440 mov esp, ebp
0050a442 pop ebp
0050a443 mov esp, ebx
0050a445 pop ebx
0050a446 ret 
