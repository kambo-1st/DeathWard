004c5c20 push ebp
004c5c21 mov ebp, esp
004c5c23 and esp, 0xfffffff8
004c5c26 sub esp, 0x120
004c5c2c mov eax, dword ptr [0xbaa3b4]
004c5c31 xor eax, esp
004c5c33 mov dword ptr [esp + 0x11c], eax
004c5c3a mov eax, dword ptr [0xbfd65c]
004c5c3f movaps xmm0, xmmword ptr [0xb6c610]
004c5c46 push esi
004c5c47 push edi
004c5c48 mov eax, dword ptr [eax + 0x18190]
004c5c4e mov edi, ecx
004c5c50 mov dword ptr [esp + 0x18], eax
004c5c54 movups xmmword ptr [esp + 0x20], xmm0
004c5c59 mov dword ptr [esp + 0x40], 0
004c5c61 cvttss2si eax, dword ptr [edi + 0x2f8]
004c5c69 mov dword ptr [esp + 0x44], 0
004c5c71 mov dword ptr [esp + 0x48], 0
004c5c79 cvttss2si esi, dword ptr [edi + 0x2fc]
004c5c81 movaps xmm0, xmmword ptr [0xb6c400]
004c5c88 sub esi, eax
004c5c8a mov eax, dword ptr [edi + 0xab4]
004c5c90 mov dword ptr [esp + 8], esi
004c5c94 movups xmmword ptr [esp + 0x30], xmm0
004c5c99 cmp eax, 0xa
004c5c9c ja 0x4c6ed9
004c5ca2 jmp dword ptr [eax*4 + 0x4c70b0]
004c5ca9 mov dword ptr [edi + 0xab4], 3
004c5cb3 mov dword ptr [edi + 0xb10], 0
004c5cbd mov dword ptr [edi + 0x360], 0xffffffff
004c5cc7 jmp 0x4c6ed9
004c5ccc mov eax, dword ptr [edi + 0xb10]
004c5cd2 test eax, eax
004c5cd4 jle 0x4c5cfb
004c5cd6 sub eax, esi
004c5cd8 mov dword ptr [edi + 0xb10], eax
004c5cde movss xmm0, dword ptr [edi + 0x2c4]
004c5ce6 mulss xmm0, dword ptr [0xb6a5a4]
004c5cee movss dword ptr [edi + 0x2c4], xmm0
004c5cf6 jmp 0x4c6ed9
004c5cfb movss xmm0, dword ptr [edi + 0x2c4]
004c5d03 mulss xmm0, dword ptr [0xb6a560]
004c5d0b push 0
004c5d0d push 0x100
004c5d12 movss dword ptr [edi + 0x2c4], xmm0
004c5d1a call 0x4122f0
004c5d1f test al, al
004c5d21 jne 0x4c5f1c
004c5d27 cmp dword ptr [edi + 0xe88], 0
004c5d2e jne 0x4c5f1c
004c5d34 push 0
004c5d36 push 0x800
004c5d3b mov ecx, edi
004c5d3d call 0x4122f0
004c5d42 test al, al
004c5d44 je 0x4c5d78
004c5d46 mov ecx, edi
004c5d48 call 0x695680
004c5d4d push 0
004c5d4f mov ecx, dword ptr [eax + 0x294]
004c5d55 mov eax, dword ptr [eax + 0x298]
004c5d5b mov dword ptr [esp + 0x10], eax
004c5d5f lea eax, [esp + 0xc]
004c5d63 mov dword ptr [esp + 0xc], ecx
004c5d67 lea ecx, [edi + 0x364]
004c5d6d push eax
004c5d6e call 0x7a4830
004c5d73 jmp 0x4c5f4a
004c5d78 lea esi, [edi + 0x370]
004c5d7e push 0xc02fec
004c5d83 mov ecx, esi
004c5d85 call 0x962c70
004c5d8a test al, al
004c5d8c je 0x4c5db9
004c5d8e push dword ptr [edi + 0x298]
004c5d94 mov ecx, edi
004c5d96 push dword ptr [edi + 0x294]
004c5d9c call 0x695680
004c5da1 mov edx, eax
004c5da3 lea ecx, [esp + 0x10]
004c5da7 call 0x4c5b50
004c5dac add esp, 8
004c5daf mov ecx, dword ptr [eax]
004c5db1 mov dword ptr [esi], ecx
004c5db3 mov eax, dword ptr [eax + 4]
004c5db6 mov dword ptr [esi + 4], eax
004c5db9 movss xmm2, dword ptr [edi + 0x2c4]
004c5dc1 ucomiss xmm2, dword ptr [0xb6a18c]
004c5dc8 movss xmm1, dword ptr [esi]
004c5dcc movss xmm3, dword ptr [esi + 4]
004c5dd1 mulss xmm1, dword ptr [0xb6a50c]
004c5dd9 mulss xmm3, dword ptr [0xb6a50c]
004c5de1 lahf 
004c5de2 test ah, 0x44
004c5de5 jnp 0x4c5e1f
004c5de7 movss xmm0, dword ptr [edi + 0x2f4]
004c5def mulss xmm1, xmm0
004c5df3 mulss xmm0, xmm3
004c5df7 divss xmm1, xmm2
004c5dfb divss xmm0, xmm2
004c5dff addss xmm1, dword ptr [edi + 0x2b8]
004c5e07 addss xmm0, dword ptr [edi + 0x2bc]
004c5e0f movss dword ptr [edi + 0x2b8], xmm1
004c5e17 movss dword ptr [edi + 0x2bc], xmm0
004c5e1f push dword ptr [edi + 0x298]
004c5e25 mov ecx, dword ptr [esp + 0x1c]
004c5e29 push dword ptr [edi + 0x294]
004c5e2f call 0x7aee40
004c5e34 test eax, eax
004c5e36 jne 0x4c5ea9
004c5e38 call 0x6c3d90
004c5e3d xor edx, edx
004c5e3f mov ecx, 0x1e
004c5e44 div ecx
004c5e46 test edx, edx
004c5e48 jne 0x4c5e75
004c5e4a push dword ptr [edi + 0x298]
004c5e50 mov ecx, edi
004c5e52 push dword ptr [edi + 0x294]
004c5e58 call 0x695680
004c5e5d mov edx, eax
004c5e5f lea ecx, [esp + 0x10]
004c5e63 call 0x4c5b50
004c5e68 add esp, 8
004c5e6b mov ecx, dword ptr [eax]
004c5e6d mov dword ptr [esi], ecx
004c5e6f mov eax, dword ptr [eax + 4]
004c5e72 mov dword ptr [esi + 4], eax
004c5e75 cmp byte ptr [edi + 0x188], 0
004c5e7c je 0x4c5f4a
004c5e82 movss xmm0, dword ptr [esi]
004c5e86 mulss xmm0, dword ptr [0xb6ae44]
004c5e8e movss dword ptr [esi], xmm0
004c5e92 movss xmm0, dword ptr [esi + 4]
004c5e97 mulss xmm0, dword ptr [0xb6ae44]
004c5e9f movss dword ptr [esi + 4], xmm0
004c5ea4 jmp 0x4c5f4a
004c5ea9 call 0x6c3d90
004c5eae xor edx, edx
004c5eb0 mov ecx, 0x1e
004c5eb5 div ecx
004c5eb7 test edx, edx
004c5eb9 jne 0x4c5f4a
004c5ebf push edx
004c5ec0 push edx
004c5ec1 push ecx
004c5ec2 mov ecx, dword ptr [esp + 0x24]
004c5ec6 lea eax, [edi + 0x294]
004c5ecc mov dword ptr [esp], edx
004c5ecf push eax
004c5ed0 lea eax, [esp + 0x18]
004c5ed4 push eax
004c5ed5 call 0x7cf240
004c5eda movss xmm0, dword ptr [esp + 8]
004c5ee0 lea eax, [esp + 8]
004c5ee4 subss xmm0, dword ptr [edi + 0x294]
004c5eec push eax
004c5eed lea ecx, [esp + 0x14]
004c5ef1 movss dword ptr [esp + 0x14], xmm0
004c5ef7 movss xmm0, dword ptr [esp + 0x10]
004c5efd subss xmm0, dword ptr [edi + 0x298]
004c5f05 movss dword ptr [esp + 0x18], xmm0
004c5f0b call 0x962560
004c5f10 mov ecx, dword ptr [eax]
004c5f12 mov dword ptr [esi], ecx
004c5f14 mov eax, dword ptr [eax + 4]
004c5f17 mov dword ptr [esi + 4], eax
004c5f1a jmp 0x4c5f4a
004c5f1c push 1
004c5f1e push 0
004c5f20 sub esp, 8
004c5f23 lea eax, [esp + 0x18]
004c5f27 mov ecx, edi
004c5f29 mov dword ptr [esp + 4], 0x3f333333
004c5f31 mov dword ptr [esp], 0
004c5f38 push eax
004c5f39 call 0x695a30
004c5f3e push eax
004c5f3f lea ecx, [edi + 0x364]
004c5f45 call 0x7a3650
004c5f4a push 0
004c5f4c push 0xb42404
004c5f51 lea ecx, [edi + 0x3c]
004c5f54 call 0x4054f0
004c5f59 xorps xmm0, xmm0
004c5f5c mov ecx, edi
004c5f5e comiss xmm0, dword ptr [edi + 0x2b8]
004c5f65 push 0
004c5f67 push 0x1000a00
004c5f6c seta al
004c5f6f mov byte ptr [edi + 0x13c], al
004c5f75 call 0x4122f0
004c5f7a test al, al
004c5f7c jne 0x4c6ed9
004c5f82 mov ecx, edi
004c5f84 call 0x695680
004c5f89 cmp dword ptr [edi + 0x360], 0
004c5f90 lea esi, [edi + 0x294]
004c5f96 movss xmm3, dword ptr [0xb6c980]
004c5f9e movss xmm2, dword ptr [eax + 0x294]
004c5fa6 movss xmm0, dword ptr [eax + 0x298]
004c5fae subss xmm2, dword ptr [esi]
004c5fb2 subss xmm0, dword ptr [esi + 4]
004c5fb7 movss dword ptr [esp + 8], xmm2
004c5fbd movss dword ptr [esp + 0x10], xmm0
004c5fc3 jge 0x4c6099
004c5fc9 movaps xmm1, xmm0
004c5fcc movaps xmm0, xmm2
004c5fcf andps xmm1, xmm3
004c5fd2 andps xmm0, xmm3
004c5fd5 comiss xmm1, xmm0
004c5fd8 ja 0x4c5fe7
004c5fda comiss xmm1, dword ptr [0xb6aad4]
004c5fe1 jbe 0x4c6093
004c5fe7 movss xmm1, dword ptr [edi + 0x2d8]
004c5fef divss xmm1, dword ptr [edi + 0x2dc]
004c5ff7 movss xmm0, dword ptr [0xb6a4e0]
004c5fff comiss xmm0, xmm1
004c6002 jbe 0x4c6093
004c6008 call 0x6c3d90
004c600d xor edx, edx
004c600f mov ecx, 3
004c6014 div ecx
004c6016 test edx, edx
004c6018 jne 0x4c6093
004c601a push dword ptr [esi + 4]
004c601d mov ecx, dword ptr [esp + 0x1c]
004c6021 push dword ptr [esi]
004c6023 call 0x7aee40
004c6028 test eax, eax
004c602a jne 0x4c608b
004c602c push esi
004c602d mov esi, dword ptr [esp + 0x1c]
004c6031 mov ecx, esi
004c6033 mov dword ptr [edi + 0x360], eax
004c6039 mov dword ptr [edi + 0xab4], 6
004c6043 call 0x7ce950
004c6048 cdq 
004c6049 idiv dword ptr [esi + 0xc]
004c604c movss xmm2, dword ptr [0xb6aa3c]
004c6054 movd xmm1, edx
004c6058 cvtdq2ps xmm1, xmm1
004c605b movd xmm0, eax
004c605f cvtdq2ps xmm0, xmm0
004c6062 mulss xmm1, xmm2
004c6066 mulss xmm0, xmm2
004c606a addss xmm1, xmm2
004c606e addss xmm0, dword ptr [0xb6ab20]
004c6076 movss dword ptr [edi + 0x28c], xmm1
004c607e movss dword ptr [edi + 0x290], xmm0
004c6086 jmp 0x4c6ed9
004c608b movss xmm3, dword ptr [0xb6c980]
004c6093 movss xmm0, dword ptr [esp + 0x10]
004c6099 call 0x6c3d90
004c609e xor edx, edx
004c60a0 mov ecx, 3
004c60a5 div ecx
004c60a7 test edx, edx
004c60a9 jne 0x4c6ed9
004c60af movss xmm1, dword ptr [0xb6aa0c]
004c60b7 andps xmm0, xmm3
004c60ba comiss xmm1, xmm0
004c60bd jbe 0x4c6ed9
004c60c3 push ecx
004c60c4 mov dword ptr [esp], 0x3f800000
004c60cb push edx
004c60cc push 0xa
004c60ce push ecx
004c60cf mov dword ptr [esp], 0x3f800000
004c60d6 mov ecx, edi
004c60d8 push 0x1fe
004c60dd call 0x6ad720
004c60e2 movss xmm0, dword ptr [esp + 8]
004c60e8 comiss xmm0, dword ptr [0xb6a18c]
004c60ef jbe 0x4c60fb
004c60f1 movss xmm0, dword ptr [0xb6a614]
004c60f9 jmp 0x4c6103
004c60fb movss xmm0, dword ptr [0xb6ae44]
004c6103 movss dword ptr [edi + 0x28c], xmm0
004c610b mov dword ptr [edi + 0x290], 0
004c6115 mov dword ptr [edi + 0xab4], 8
004c611f mov dword ptr [edi + 0xb0c], 0x3f000000
004c6129 jmp 0x4c6ed9
004c612e movss xmm0, dword ptr [edi + 0x2c4]
004c6136 lea ecx, [edi + 0x3c]
004c6139 mulss xmm0, dword ptr [0xb6a58c]
004c6141 push 0
004c6143 push 0xb42404
004c6148 movss dword ptr [edi + 0x2c4], xmm0
004c6150 call 0x4054f0
004c6155 movss xmm1, dword ptr [edi + 0x28c]
004c615d xorps xmm0, xmm0
004c6160 comiss xmm0, xmm1
004c6163 push 0
004c6165 push 0x1000a00
004c616a mov ecx, edi
004c616c movss dword ptr [esp + 0x10], xmm1
004c6172 seta al
004c6175 mov byte ptr [edi + 0x13c], al
004c617b call 0x4122f0
004c6180 test al, al
004c6182 jne 0x4c6305
004c6188 cmp byte ptr [edi + 0x188], al
004c618e jne 0x4c6312
004c6194 movss xmm0, dword ptr [edi + 0x290]
004c619c mov ecx, edi
004c619e movss dword ptr [esp + 0x10], xmm0
004c61a4 call 0x695680
004c61a9 movss xmm2, dword ptr [edi + 0x298]
004c61b1 movss xmm1, dword ptr [0xb6a974]
004c61b9 movaps xmm0, xmm2
004c61bc addss xmm0, xmm1
004c61c0 movss xmm3, dword ptr [eax + 0x298]
004c61c8 movss xmm6, dword ptr [eax + 0x294]
004c61d0 comiss xmm3, xmm0
004c61d3 jbe 0x4c61df
004c61d5 movss xmm0, dword ptr [0xb6a2e4]
004c61dd jmp 0x4c61f0
004c61df subss xmm2, xmm1
004c61e3 comiss xmm2, xmm3
004c61e6 jbe 0x4c61f6
004c61e8 movss xmm0, dword ptr [0xb6adf0]
004c61f0 movss dword ptr [esp + 0x10], xmm0
004c61f6 movss xmm3, dword ptr [edi + 0xb0c]
004c61fe lea eax, [esp + 8]
004c6202 movss xmm1, dword ptr [0xb6ae6c]
004c620a lea ecx, [esp + 0x10]
004c620e movaps xmm0, xmm3
004c6211 movaps xmm5, xmm3
004c6214 mulss xmm0, dword ptr [esp + 0x10]
004c621a mulss xmm5, dword ptr [esp + 8]
004c6220 mov dword ptr [esp + 8], 0xc0000000
004c6228 comiss xmm1, xmm0
004c622b movss dword ptr [esp + 0x10], xmm0
004c6231 movss xmm0, dword ptr [0xb6a7b0]
004c6239 cmovbe eax, ecx
004c623c movss xmm1, dword ptr [eax]
004c6240 comiss xmm1, xmm0
004c6243 ja 0x4c624b
004c6245 movss xmm2, xmm1
004c6249 jmp 0x4c624f
004c624b movss xmm2, xmm0
004c624f movss xmm4, dword ptr [edi + 0x2c4]
004c6257 ucomiss xmm4, dword ptr [0xb6a18c]
004c625e lahf 
004c625f test ah, 0x44
004c6262 jnp 0x4c62a7
004c6264 movss xmm1, dword ptr [edi + 0x2f4]
004c626c movaps xmm0, xmm1
004c626f mulss xmm2, xmm1
004c6273 mulss xmm0, xmm5
004c6277 divss xmm2, xmm4
004c627b divss xmm0, xmm4
004c627f addss xmm2, dword ptr [edi + 0x2bc]
004c6287 addss xmm0, dword ptr [edi + 0x2b8]
004c628f movss dword ptr [edi + 0x2bc], xmm2
004c6297 movss dword ptr [edi + 0x2b8], xmm0
004c629f movss xmm3, dword ptr [edi + 0xb0c]
004c62a7 movss xmm0, dword ptr [0xb6a614]
004c62af comiss xmm0, xmm3
004c62b2 ja 0x4c62d8
004c62b4 movss xmm1, dword ptr [edi + 0x294]
004c62bc movss xmm0, dword ptr [0xb6ac8c]
004c62c4 subss xmm1, xmm6
004c62c8 andps xmm1, xmmword ptr [0xb6c980]
004c62cf comiss xmm0, xmm1
004c62d2 jbe 0x4c6ed9
004c62d8 movss xmm1, dword ptr [edi + 0x2f4]
004c62e0 mulss xmm1, dword ptr [0xb6a350]
004c62e8 movss xmm0, dword ptr [0xb6a8f4]
004c62f0 addss xmm1, xmm3
004c62f4 minss xmm0, xmm1
004c62f8 movss dword ptr [edi + 0xb0c], xmm0
004c6300 jmp 0x4c6ed9
004c6305 cmp byte ptr [edi + 0x188], 0
004c630c je 0x4c6525
004c6312 movss xmm1, dword ptr [edi + 0x190]
004c631a movss xmm0, dword ptr [edi + 0x18c]
004c6322 mulss xmm0, xmm0
004c6326 mulss xmm1, xmm1
004c632a addss xmm0, xmm1
004c632e call 0x4228c0
004c6333 comiss xmm0, dword ptr [0xb6a974]
004c633a jbe 0x4c6525
004c6340 lea eax, [esp + 8]
004c6344 push eax
004c6345 lea ecx, [edi + 0x18c]
004c634b call 0x962560
004c6350 movss xmm1, dword ptr [edi + 0x198]
004c6358 movss xmm0, dword ptr [edi + 0x194]
004c6360 mulss xmm1, dword ptr [eax + 4]
004c6365 mulss xmm0, dword ptr [eax]
004c6369 addss xmm1, xmm0
004c636d comiss xmm1, dword ptr [0xb6a4c4]
004c6374 jbe 0x4c6525
004c637a mov ecx, dword ptr [0xbfd65c]
004c6380 push 6
004c6382 call 0x6d5ad0
004c6387 push ecx
004c6388 mov dword ptr [esp], 0x3f800000
004c638f push 0
004c6391 push 2
004c6393 push ecx
004c6394 mov dword ptr [esp], 0x3f800000
004c639b mov ecx, edi
004c639d push 0x48
004c639f call 0x6ad720
004c63a4 movss xmm1, dword ptr [edi + 0x194]
004c63ac lea ecx, [esp + 0x4c]
004c63b0 mulss xmm1, dword ptr [0xb6a820]
004c63b8 push 0xc02fec
004c63bd movss xmm0, dword ptr [edi + 0x2b8]
004c63c5 movss xmm3, dword ptr [edi + 0x198]
004c63cd mulss xmm3, dword ptr [0xb6a820]
004c63d5 subss xmm0, xmm1
004c63d9 mov dword ptr [esp + 0xc], 0
004c63e1 mov dword ptr [esp + 0x10], 0xc1600000
004c63e9 movss dword ptr [edi + 0x2b8], xmm0
004c63f1 movss xmm0, dword ptr [edi + 0x2bc]
004c63f9 subss xmm0, xmm3
004c63fd movss dword ptr [edi + 0x2bc], xmm0
004c6405 mov dword ptr [edi + 0xb10], 0xc
004c640f movss xmm0, dword ptr [edi + 0x28c]
004c6417 mulss xmm0, dword ptr [0xb6a9a0]
004c641f addss xmm0, dword ptr [edi + 0x294]
004c6427 movss dword ptr [esp + 0x14], xmm0
004c642d movss xmm0, dword ptr [edi + 0x290]
004c6435 mulss xmm0, dword ptr [0xb6a9a0]
004c643d addss xmm0, dword ptr [edi + 0x298]
004c6445 movss dword ptr [esp + 0x18], xmm0
004c644b call 0x402120
004c6450 push eax
004c6451 lea eax, [esp + 0x10]
004c6455 mov ecx, 3
004c645a push eax
004c645b lea edx, [esp + 0x1c]
004c645f call 0x6aead0
004c6464 add esp, 0xc
004c6467 lea ecx, [esp + 0x20]
004c646b mov edx, dword ptr [eax]
004c646d push 1
004c646f push 0
004c6471 push 0xff
004c6476 push -1
004c6478 push ecx
004c6479 mov ecx, eax
004c647b mov dword ptr [eax + 0x2b0], 0x40a00000
004c6485 call dword ptr [edx + 0x38]
004c6488 lea ecx, [esp + 0x78]
004c648c call 0x430d70
004c6491 movss xmm0, dword ptr [edi + 0x28c]
004c6499 lea eax, [esp + 0x78]
004c649d mulss xmm0, dword ptr [0xb6a940]
004c64a5 mov ecx, edi
004c64a7 push eax
004c64a8 push 9
004c64aa lea eax, [esp + 0x10]
004c64ae mov dword ptr [esp + 0x8c], 0x3da3d70a
004c64b9 addss xmm0, dword ptr [edi + 0x294]
004c64c1 push eax
004c64c2 lea eax, [esp + 0x1c]
004c64c6 mov dword ptr [esp + 0x14], 0x41200000
004c64ce push eax
004c64cf mov dword ptr [esp + 0x1c], 0x41400000
004c64d7 movss dword ptr [esp + 0x20], xmm0
004c64dd movss xmm0, dword ptr [edi + 0x290]
004c64e5 mulss xmm0, dword ptr [0xb6a940]
004c64ed addss xmm0, dword ptr [edi + 0x298]
004c64f5 movss dword ptr [esp + 0x24], xmm0
004c64fb call 0x6a1a20
004c6500 push 1
004c6502 push 0xb42420
004c6507 lea ecx, [edi + 0x3c]
004c650a call 0x405bb0
004c650f test al, al
004c6511 je 0x4c6525
004c6513 lea ecx, [edi + 0x8c]
004c6519 call 0x405330
004c651e mov byte ptr [edi + 0xa0], 1
004c6525 mov dword ptr [edi + 0xab4], 3
004c652f movss xmm0, dword ptr [0xc02fec]
004c6537 movss dword ptr [edi + 0x28c], xmm0
004c653f movss xmm0, dword ptr [0xc02ff0]
004c6547 movss dword ptr [edi + 0x290], xmm0
004c654f jmp 0x4c6ed9
004c6554 mov dword ptr [edi + 0x2c4], 0x3f4ccccd
004c655e lea ecx, [edi + 0x3c]
004c6561 movss xmm0, dword ptr [edi + 0x28c]
004c6569 subss xmm0, dword ptr [edi + 0x294]
004c6571 movss xmm3, dword ptr [edi + 0x290]
004c6579 push 0
004c657b push 0xb42430
004c6580 mulss xmm0, dword ptr [0xb6a3b0]
004c6588 divss xmm0, dword ptr [0xb6a560]
004c6590 addss xmm0, dword ptr [edi + 0x2b8]
004c6598 movss dword ptr [edi + 0x2b8], xmm0
004c65a0 subss xmm3, dword ptr [edi + 0x298]
004c65a8 mulss xmm3, dword ptr [0xb6a3b0]
004c65b0 divss xmm3, dword ptr [0xb6a560]
004c65b8 addss xmm3, dword ptr [edi + 0x2bc]
004c65c0 movss dword ptr [edi + 0x2bc], xmm3
004c65c8 call 0x4054f0
004c65cd cmp dword ptr [edi + 0x70], 0
004c65d1 lea esi, [edi + 0x6c]
004c65d4 je 0x4c6653
004c65d6 push 0xb400b4
004c65db mov ecx, esi
004c65dd call 0x405e90
004c65e2 test al, al
004c65e4 je 0x4c6603
004c65e6 push ecx
004c65e7 mov dword ptr [esp], 0x3f800000
004c65ee push 0
004c65f0 push 2
004c65f2 push ecx
004c65f3 mov dword ptr [esp], 0x3f800000
004c65fa mov ecx, edi
004c65fc push 0x48
004c65fe call 0x6ad720
004c6603 cmp dword ptr [edi + 0x70], 0
004c6607 je 0x4c6653
004c6609 push 0xb40190
004c660e mov ecx, esi
004c6610 call 0x405e90
004c6615 test al, al
004c6617 je 0x4c6640
004c6619 push ecx
004c661a mov dword ptr [esp], 0x3f800000
004c6621 push 0
004c6623 push 2
004c6625 push ecx
004c6626 mov dword ptr [esp], 0x3f800000
004c662d mov ecx, edi
004c662f push 0x42
004c6631 call 0x6ad720
004c6636 mov dword ptr [edi + 0x180], 0
004c6640 cmp dword ptr [edi + 0x70], 0
004c6644 je 0x4c6653
004c6646 cmp byte ptr [edi + 0x80], 0
004c664d jne 0x4c6ed9
004c6653 mov eax, dword ptr [esp + 8]
004c6657 add dword ptr [edi + 0x360], eax
004c665d movss xmm0, dword ptr [0xc02fec]
004c6665 movss dword ptr [edi + 0x28c], xmm0
004c666d movss xmm0, dword ptr [0xc02ff0]
004c6675 movss dword ptr [edi + 0x290], xmm0
004c667d movss xmm0, dword ptr [0xc02fec]
004c6685 movss dword ptr [edi + 0x2b8], xmm0
004c668d movss xmm0, dword ptr [0xc02ff0]
004c6695 movss dword ptr [edi + 0x2bc], xmm0
004c669d cmp dword ptr [edi + 0x360], 0x1e
004c66a4 jle 0x4c6ed9
004c66aa call 0x6c3d90
004c66af xor edx, edx
004c66b1 mov ecx, 0xf
004c66b6 div ecx
004c66b8 test edx, edx
004c66ba jne 0x4c6ed9
004c66c0 mov ecx, edi
004c66c2 call 0x695680
004c66c7 push ecx
004c66c8 mov dword ptr [esp], 0x3f800000
004c66cf push 0
004c66d1 movss xmm0, dword ptr [eax + 0x294]
004c66d9 movss xmm1, dword ptr [eax + 0x298]
004c66e1 push 0xa
004c66e3 push ecx
004c66e4 mov dword ptr [edi + 0xab4], 7
004c66ee mov ecx, edi
004c66f0 mov dword ptr [edi + 0x17c], 5
004c66fa mov dword ptr [esp], 0x3f800000
004c6701 movss dword ptr [edi + 0x294], xmm0
004c6709 movss dword ptr [edi + 0x298], xmm1
004c6711 push 0x1fe
004c6716 mov dword ptr [edi + 0x360], 0
004c6720 call 0x6ad720
004c6725 jmp 0x4c6ed9
004c672a movss xmm0, dword ptr [edi + 0x2c4]
004c6732 lea ecx, [edi + 0x3c]
004c6735 mulss xmm0, dword ptr [0xb6a58c]
004c673d push 0
004c673f push 0xb40410
004c6744 movss dword ptr [edi + 0x2c4], xmm0
004c674c call 0x4054f0
004c6751 movss xmm1, dword ptr [edi + 0x28c]
004c6759 xorps xmm0, xmm0
004c675c comiss xmm0, xmm1
004c675f movss dword ptr [esp + 8], xmm1
004c6765 seta al
004c6768 mov byte ptr [edi + 0x13c], al
004c676e movss xmm1, dword ptr [edi + 0x2bc]
004c6776 movss xmm0, dword ptr [edi + 0x2b8]
004c677e mulss xmm0, xmm0
004c6782 mulss xmm1, xmm1
004c6786 addss xmm0, xmm1
004c678a call 0x4228c0
004c678f movss xmm1, dword ptr [0xb6a864]
004c6797 comiss xmm1, xmm0
004c679a jbe 0x4c67a4
004c679c add dword ptr [edi + 0x360], esi
004c67a2 jmp 0x4c67ae
004c67a4 mov dword ptr [edi + 0x360], 0
004c67ae movss xmm0, dword ptr [esp + 8]
004c67b4 lea eax, [esp + 8]
004c67b8 mulss xmm0, dword ptr [0xb6a8c4]
004c67c0 mov ecx, edi
004c67c2 push 0
004c67c4 push eax
004c67c5 movss dword ptr [esp + 0x10], xmm0
004c67cb movss xmm0, dword ptr [edi + 0x290]
004c67d3 mulss xmm0, dword ptr [0xb6a8c4]
004c67db movss dword ptr [esp + 0x14], xmm0
004c67e1 call 0x422b60
004c67e6 cmp byte ptr [edi + 0x188], 0
004c67ed je 0x4c691a
004c67f3 movss xmm1, dword ptr [edi + 0x198]
004c67fb movss xmm0, dword ptr [edi + 0x28c]
004c6803 mulss xmm1, dword ptr [edi + 0x290]
004c680b mulss xmm0, dword ptr [edi + 0x194]
004c6813 addss xmm1, xmm0
004c6817 comiss xmm1, dword ptr [0xb6a4c4]
004c681e jbe 0x4c691a
004c6824 mov ecx, dword ptr [0xbfd65c]
004c682a push 0xc
004c682c call 0x6d5ad0
004c6831 push ecx
004c6832 mov dword ptr [esp], 0x3f800000
004c6839 push 0
004c683b push 2
004c683d push ecx
004c683e mov dword ptr [esp], 0x3f800000
004c6845 mov ecx, edi
004c6847 push 0x4d
004c6849 call 0x6ad720
004c684e movss xmm0, dword ptr [0xc02fec]
004c6856 lea eax, [esp + 0x20]
004c685a movss dword ptr [edi + 0x2b8], xmm0
004c6862 lea edx, [esp + 0x10]
004c6866 movss xmm0, dword ptr [0xc02ff0]
004c686e mov ecx, 4
004c6873 movss dword ptr [edi + 0x2bc], xmm0
004c687b movss xmm1, dword ptr [edi + 0x294]
004c6883 movss dword ptr [edi + 0x28c], xmm1
004c688b movss xmm2, dword ptr [edi + 0x298]
004c6893 mulss xmm1, dword ptr [0xb6a9a0]
004c689b push 0xc02fec
004c68a0 movss dword ptr [edi + 0x290], xmm2
004c68a8 mulss xmm2, dword ptr [0xb6a9a0]
004c68b0 push eax
004c68b1 addss xmm1, dword ptr [edi + 0x294]
004c68b9 lea eax, [esp + 0x10]
004c68bd mov dword ptr [esp + 0x10], 0
004c68c5 addss xmm2, dword ptr [edi + 0x298]
004c68cd push eax
004c68ce mov dword ptr [esp + 0x18], 0xc1600000
004c68d6 movss dword ptr [esp + 0x1c], xmm1
004c68dc movss dword ptr [esp + 0x20], xmm2
004c68e2 call 0x6aead0
004c68e7 add esp, 0xc
004c68ea lea ecx, [esp + 0x78]
004c68ee call 0x430d70
004c68f3 lea eax, [esp + 0x78]
004c68f7 push eax
004c68f8 push ecx
004c68f9 mov dword ptr [esp], 0
004c6900 mov ecx, edi
004c6902 push 0xc02fec
004c6907 push 0xc
004c6909 call 0x6a3420
004c690e mov dword ptr [edi + 0xab4], 0xa
004c6918 jmp 0x4c694d
004c691a cmp dword ptr [edi + 0x360], 0xa
004c6921 jle 0x4c694d
004c6923 mov dword ptr [edi + 0xab4], 3
004c692d movss xmm0, dword ptr [0xc02fec]
004c6935 movss dword ptr [edi + 0x28c], xmm0
004c693d movss xmm0, dword ptr [0xc02ff0]
004c6945 movss dword ptr [edi + 0x290], xmm0
004c694d call 0x6c3d90
004c6952 test al, 1
004c6954 jne 0x4c6ed9
004c695a call 0x6c3d90
004c695f push ecx
004c6960 mov ecx, edi
004c6962 movd xmm0, eax
004c6966 cvtdq2pd xmm0, xmm0
004c696a shr eax, 0x1f
004c696d addsd xmm0, qword ptr [eax*8 + 0xb6c940]
004c6976 cvtpd2ps xmm0, xmm0
004c697a mulss xmm0, dword ptr [0xb6a19c]
004c6982 mulss xmm0, dword ptr [0xb6a6c8]
004c698a addss xmm0, dword ptr [0xb6a480]
004c6992 movss dword ptr [esp], xmm0
004c6997 call 0x68d7b0
004c699c jmp 0x4c6ed9
004c69a1 push 0
004c69a3 push 0xb42470
004c69a8 lea ecx, [edi + 0x3c]
004c69ab call 0x4054f0
004c69b0 push 0xb400b4
004c69b5 lea ecx, [edi + 0x3c]
004c69b8 call 0x4060f0
004c69bd test al, al
004c69bf je 0x4c6a4e
004c69c5 push ecx
004c69c6 mov dword ptr [esp], 0x3f800000
004c69cd push 0
004c69cf push 2
004c69d1 push ecx
004c69d2 mov dword ptr [esp], 0x3f800000
004c69d9 mov ecx, edi
004c69db push 0x48
004c69dd call 0x6ad720
004c69e2 cmp byte ptr [edi + 0x13c], 0
004c69e9 je 0x4c69f5
004c69eb movss xmm0, dword ptr [0xb6a614]
004c69f3 jmp 0x4c69fd
004c69f5 movss xmm0, dword ptr [0xb6ae44]
004c69fd mulss xmm0, dword ptr [0xb6a8f4]
004c6a05 lea ecx, [edi + 0x28c]
004c6a0b addss xmm0, dword ptr [edi + 0x2b8]
004c6a13 movss dword ptr [edi + 0x2b8], xmm0
004c6a1b movss xmm0, dword ptr [edi + 0x2bc]
004c6a23 addss xmm0, dword ptr [0xb6a18c]
004c6a2b movss dword ptr [edi + 0x2bc], xmm0
004c6a33 movss xmm0, dword ptr [0xc02fec]
004c6a3b movss dword ptr [ecx], xmm0
004c6a3f movss xmm0, dword ptr [0xc02ff0]
004c6a47 movss dword ptr [ecx + 4], xmm0
004c6a4c jmp 0x4c6a54
004c6a4e lea ecx, [edi + 0x28c]
004c6a54 movss xmm1, dword ptr [edi + 0x2c4]
004c6a5c push 0xc02fec
004c6a61 call 0x962c70
004c6a66 test al, al
004c6a68 je 0x4c6a7c
004c6a6a mulss xmm1, dword ptr [0xb6a5a4]
004c6a72 movss dword ptr [edi + 0x2c4], xmm1
004c6a7a jmp 0x4c6ac6
004c6a7c mulss xmm1, dword ptr [0xb6a50c]
004c6a84 lea eax, [esp + 8]
004c6a88 push 0
004c6a8a push eax
004c6a8b mov ecx, edi
004c6a8d movss dword ptr [edi + 0x2c4], xmm1
004c6a95 movss xmm0, dword ptr [edi + 0x28c]
004c6a9d subss xmm0, dword ptr [edi + 0x294]
004c6aa5 movss dword ptr [esp + 0x10], xmm0
004c6aab movss xmm0, dword ptr [edi + 0x290]
004c6ab3 subss xmm0, dword ptr [edi + 0x298]
004c6abb movss dword ptr [esp + 0x14], xmm0
004c6ac1 call 0x422b60
004c6ac6 cmp dword ptr [edi + 0x70], 0
004c6aca je 0x4c6525
004c6ad0 cmp byte ptr [edi + 0x80], 0
004c6ad7 jne 0x4c6ed9
004c6add jmp 0x4c6525
004c6ae2 push 0
004c6ae4 lea ecx, [edi + 0x3c]
004c6ae7 push 0xb41c5c
004c6aec call 0x4054f0
004c6af1 lea esi, [edi + 0x28c]
004c6af7 push 0xc02fec
004c6afc mov ecx, esi
004c6afe call 0x962c70
004c6b03 test al, al
004c6b05 je 0x4c6b63
004c6b07 cmp dword ptr [edi + 0x17c], 5
004c6b0e jne 0x4c6b49
004c6b10 mov ecx, edi
004c6b12 call 0x695680
004c6b17 push 1
004c6b19 push 0
004c6b1b mov ecx, dword ptr [eax + 0x294]
004c6b21 mov eax, dword ptr [eax + 0x298]
004c6b27 push ecx
004c6b28 mov dword ptr [esp + 0x18], eax
004c6b2c lea eax, [esp + 0x14]
004c6b30 mov dword ptr [esp + 0x14], ecx
004c6b34 lea ecx, [edi + 0x364]
004c6b3a mov dword ptr [esp], 0x3f4ccccd
004c6b41 push eax
004c6b42 call 0x7a3650
004c6b47 jmp 0x4c6bae
004c6b49 movss xmm0, dword ptr [edi + 0x2c4]
004c6b51 mulss xmm0, dword ptr [0xb6a560]
004c6b59 movss dword ptr [edi + 0x2c4], xmm0
004c6b61 jmp 0x4c6bae
004c6b63 movss xmm0, dword ptr [edi + 0x2c4]
004c6b6b lea eax, [esp + 8]
004c6b6f mulss xmm0, dword ptr [0xb6a50c]
004c6b77 mov ecx, edi
004c6b79 push 0
004c6b7b push eax
004c6b7c movss dword ptr [edi + 0x2c4], xmm0
004c6b84 movss xmm0, dword ptr [esi]
004c6b88 subss xmm0, dword ptr [edi + 0x294]
004c6b90 movss dword ptr [esp + 0x10], xmm0
004c6b96 movss xmm0, dword ptr [esi + 4]
004c6b9b subss xmm0, dword ptr [edi + 0x298]
004c6ba3 movss dword ptr [esp + 0x14], xmm0
004c6ba9 call 0x422b60
004c6bae push 0xb40190
004c6bb3 lea ecx, [edi + 0x3c]
004c6bb6 call 0x4060f0
004c6bbb test al, al
004c6bbd je 0x4c6ca4
004c6bc3 mov ecx, dword ptr [0xbfd65c]
004c6bc9 push 0xc
004c6bcb mov dword ptr [edi + 0x17c], 3
004c6bd5 call 0x6d5ad0
004c6bda push ecx
004c6bdb mov dword ptr [esp], 0x3f800000
004c6be2 push 0
004c6be4 push 2
004c6be6 push ecx
004c6be7 mov dword ptr [esp], 0x3f800000
004c6bee mov ecx, edi
004c6bf0 push 0x4d
004c6bf2 call 0x6ad720
004c6bf7 movss xmm0, dword ptr [0xc02fec]
004c6bff lea esi, [edi + 0x294]
004c6c05 movss dword ptr [edi + 0x2b8], xmm0
004c6c0d mov edx, esi
004c6c0f movss xmm0, dword ptr [0xc02ff0]
004c6c17 mov ecx, 4
004c6c1c movss dword ptr [edi + 0x2bc], xmm0
004c6c24 mov eax, dword ptr [esi]
004c6c26 mov dword ptr [edi + 0x28c], eax
004c6c2c mov eax, dword ptr [esi + 4]
004c6c2f mov dword ptr [edi + 0x290], eax
004c6c35 lea eax, [esp + 0x20]
004c6c39 push 0xc02fec
004c6c3e push eax
004c6c3f lea eax, [esp + 0x10]
004c6c43 mov dword ptr [edi + 0x180], 4
004c6c4d push eax
004c6c4e mov dword ptr [esp + 0x14], 0
004c6c56 mov dword ptr [esp + 0x18], 0xc1600000
004c6c5e call 0x6aead0
004c6c63 add esp, 0xc
004c6c66 lea ecx, [esp + 0x78]
004c6c6a call 0x430d70
004c6c6f lea eax, [esp + 0x78]
004c6c73 mov dword ptr [esp + 0x84], 0xbca3d70a
004c6c7e push eax
004c6c7f push 9
004c6c81 lea eax, [esp + 0x10]
004c6c85 mov dword ptr [esp + 0x10], 0x41000000
004c6c8d push eax
004c6c8e push esi
004c6c8f mov ecx, edi
004c6c91 mov dword ptr [esp + 0x1c], 0x41200000
004c6c99 call 0x6a1a20
004c6c9e lea esi, [edi + 0x28c]
004c6ca4 push 0xb400b4
004c6ca9 lea ecx, [edi + 0x3c]
004c6cac call 0x4060f0
004c6cb1 test al, al
004c6cb3 je 0x4c6ceb
004c6cb5 push ecx
004c6cb6 mov dword ptr [esp], 0x3f800000
004c6cbd push 0
004c6cbf push 2
004c6cc1 push ecx
004c6cc2 mov dword ptr [esp], 0x3f800000
004c6cc9 mov ecx, edi
004c6ccb push 0x48
004c6ccd call 0x6ad720
004c6cd2 movss xmm0, dword ptr [0xc02fec]
004c6cda movss dword ptr [esi], xmm0
004c6cde movss xmm0, dword ptr [0xc02ff0]
004c6ce6 movss dword ptr [esi + 4], xmm0
004c6ceb cmp dword ptr [edi + 0x70], 0
004c6cef je 0x4c6cfe
004c6cf1 cmp byte ptr [edi + 0x80], 0
004c6cf8 jne 0x4c6ed9
004c6cfe mov dword ptr [edi + 0xab4], 3
004c6d08 movss xmm0, dword ptr [0xc02fec]
004c6d10 movss dword ptr [esi], xmm0
004c6d14 movss xmm0, dword ptr [0xc02ff0]
004c6d1c movss dword ptr [esi + 4], xmm0
004c6d21 jmp 0x4c6ed9
004c6d26 movss xmm0, dword ptr [0xb6a7b0]
004c6d2e comiss xmm0, dword ptr [edi + 0xb0c]
004c6d35 jbe 0x4c6d41
004c6d37 mov dword ptr [edi + 0xb0c], 0x40000000
004c6d41 movss xmm0, dword ptr [edi + 0x2c4]
004c6d49 lea ecx, [edi + 0x3c]
004c6d4c mulss xmm0, dword ptr [0xb6a58c]
004c6d54 push 0
004c6d56 push 0xb42404
004c6d5b movss dword ptr [edi + 0x2c4], xmm0
004c6d63 call 0x4054f0
004c6d68 xorps xmm0, xmm0
004c6d6b mov ecx, edi
004c6d6d comiss xmm0, dword ptr [edi + 0x28c]
004c6d74 movss xmm0, dword ptr [edi + 0x28c]
004c6d7c movss dword ptr [esp + 8], xmm0
004c6d82 movss xmm0, dword ptr [edi + 0x290]
004c6d8a seta al
004c6d8d mov byte ptr [edi + 0x13c], al
004c6d93 movss dword ptr [esp + 0x10], xmm0
004c6d99 call 0x695680
004c6d9e movss xmm2, dword ptr [edi + 0x298]
004c6da6 movss xmm1, dword ptr [0xb6a974]
004c6dae movaps xmm0, xmm2
004c6db1 addss xmm0, xmm1
004c6db5 movss xmm3, dword ptr [eax + 0x298]
004c6dbd comiss xmm3, xmm0
004c6dc0 jbe 0x4c6dcc
004c6dc2 movss xmm0, dword ptr [0xb6a2e4]
004c6dca jmp 0x4c6ddd
004c6dcc subss xmm2, xmm1
004c6dd0 comiss xmm2, xmm3
004c6dd3 jbe 0x4c6de3
004c6dd5 movss xmm0, dword ptr [0xb6adf0]
004c6ddd movss dword ptr [esp + 0x10], xmm0
004c6de3 movss xmm1, dword ptr [edi + 0xb0c]
004c6deb lea eax, [esp + 8]
004c6def movaps xmm0, xmm1
004c6df2 lea ecx, [esp + 0x10]
004c6df6 mulss xmm0, dword ptr [esp + 8]
004c6dfc mov dword ptr [esp + 8], 0xc0000000
004c6e04 mulss xmm1, dword ptr [esp + 0x10]
004c6e0a movss dword ptr [esp + 0x18], xmm0
004c6e10 movss xmm0, dword ptr [0xb6ae6c]
004c6e18 comiss xmm0, xmm1
004c6e1b movss dword ptr [esp + 0x10], xmm1
004c6e21 movss xmm1, dword ptr [0xb6a7b0]
004c6e29 cmovbe eax, ecx
004c6e2c movss xmm0, dword ptr [eax]
004c6e30 comiss xmm0, xmm1
004c6e33 ja 0x4c6e3b
004c6e35 movss xmm0, xmm0
004c6e39 jmp 0x4c6e3f
004c6e3b movss xmm0, xmm1
004c6e3f push 0
004c6e41 lea eax, [esp + 0x1c]
004c6e45 mov ecx, edi
004c6e47 push eax
004c6e48 movss dword ptr [esp + 0x24], xmm0
004c6e4e call 0x422b60
004c6e53 movss xmm1, dword ptr [edi + 0xb0c]
004c6e5b xorps xmm2, xmm2
004c6e5e addss xmm1, dword ptr [0xb6a350]
004c6e66 movss xmm0, dword ptr [0xb6a8f4]
004c6e6e movss xmm4, dword ptr [0xb6aad4]
004c6e76 minss xmm0, xmm1
004c6e7a movss dword ptr [edi + 0xb0c], xmm0
004c6e82 movss xmm3, dword ptr [edi + 0x2b8]
004c6e8a comiss xmm3, xmm2
004c6e8d jbe 0x4c6eb0
004c6e8f mov eax, dword ptr [0xbfd65c]
004c6e94 movss xmm0, dword ptr [edi + 0x294]
004c6e9c mov eax, dword ptr [eax + 0x18190]
004c6ea2 movss xmm1, dword ptr [eax + 0x1c]
004c6ea7 addss xmm1, xmm4
004c6eab comiss xmm0, xmm1
004c6eae ja 0x4c6ed2
004c6eb0 comiss xmm2, xmm3
004c6eb3 jbe 0x4c6ed9
004c6eb5 mov eax, dword ptr [0xbfd65c]
004c6eba mov eax, dword ptr [eax + 0x18190]
004c6ec0 movss xmm0, dword ptr [eax + 0x14]
004c6ec5 subss xmm0, xmm4
004c6ec9 comiss xmm0, dword ptr [edi + 0x294]
004c6ed0 jbe 0x4c6ed9
004c6ed2 mov eax, dword ptr [edi]
004c6ed4 mov ecx, edi
004c6ed6 call dword ptr [eax + 0x28]
004c6ed9 cmp dword ptr [edi + 0x90], 0
004c6ee0 je 0x4c6f3f
004c6ee2 push 0xb4247c
004c6ee7 lea ecx, [edi + 0x8c]
004c6eed call 0x405da0
004c6ef2 mov edx, eax
004c6ef4 mov dword ptr [esp + 8], edx
004c6ef8 test edx, edx
004c6efa je 0x4c6f3f
004c6efc cmp byte ptr [edx + 0xc], 0
004c6f00 je 0x4c6f3f
004c6f02 cmp dword ptr [edi + 0xbc], 0
004c6f09 jg 0x4c6f2d
004c6f0b cmp dword ptr [edi + 0x50], 0x10
004c6f0f lea eax, [edi + 0x3c]
004c6f12 jb 0x4c6f17
004c6f14 mov eax, dword ptr [edi + 0x3c]
004c6f17 push 0
004c6f19 push eax
004c6f1a push 0xa0830c
004c6f1f push 3
004c6f21 call 0x95e330
004c6f26 mov edx, dword ptr [esp + 0x18]
004c6f2a add esp, 0x10
004c6f2d mov ecx, dword ptr [edi + 0xb8]
004c6f33 mov eax, dword ptr [edx + 0x10]
004c6f36 mov dword ptr [ecx + 0x34], eax
004c6f39 mov eax, dword ptr [edx + 0x14]
004c6f3c mov dword ptr [ecx + 0x38], eax
004c6f3f cmp byte ptr [edi + 0x16b], 0
004c6f46 je 0x4c709a
004c6f4c mov dword ptr [esp + 0x10], 3
004c6f54 call 0x6c3d90
004c6f59 movd xmm0, eax
004c6f5d cvtdq2pd xmm0, xmm0
004c6f61 shr eax, 0x1f
004c6f64 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
004c6f6d cvtpd2ps xmm1, xmm0
004c6f71 mulss xmm1, dword ptr [0xb6a19c]
004c6f79 call 0x6c3d90
004c6f7e subss xmm1, dword ptr [0xb6a480]
004c6f86 lea ecx, [esp + 0x4c]
004c6f8a movd xmm0, eax
004c6f8e cvtdq2pd xmm0, xmm0
004c6f92 shr eax, 0x1f
004c6f95 mulss xmm1, dword ptr [0xb6aa0c]
004c6f9d addsd xmm0, qword ptr [eax*8 + 0xb6c940]
004c6fa6 addss xmm1, dword ptr [edi + 0x298]
004c6fae cvtpd2ps xmm0, xmm0
004c6fb2 movss dword ptr [esp + 0x1c], xmm1
004c6fb8 mulss xmm0, dword ptr [0xb6a19c]
004c6fc0 subss xmm0, dword ptr [0xb6a480]
004c6fc8 mulss xmm0, dword ptr [0xb6aad4]
004c6fd0 addss xmm0, dword ptr [edi + 0x294]
004c6fd8 movss dword ptr [esp + 0x18], xmm0
004c6fde call 0x65add0
004c6fe3 call 0x6c3d90
004c6fe8 movss xmm1, dword ptr [0xb6aeb8]
004c6ff0 movd xmm0, eax
004c6ff4 cvtdq2pd xmm0, xmm0
004c6ff8 shr eax, 0x1f
004c6ffb addsd xmm0, qword ptr [eax*8 + 0xb6c940]
004c7004 cvtpd2ps xmm0, xmm0
004c7008 mulss xmm0, dword ptr [0xb6a19c]
004c7010 mulss xmm0, dword ptr [0xb6aa3c]
004c7018 subss xmm1, xmm0
004c701c movss dword ptr [esp + 8], xmm1
004c7022 call 0x6c3d90
004c7027 mov esi, eax
004c7029 and esi, 1
004c702c call 0x6c3d90
004c7031 mov ecx, dword ptr [0xbfd65c]
004c7037 push eax
004c7038 lea eax, [esi + 3]
004c703b push eax
004c703c push 0
004c703e push 0xc02fec
004c7043 lea eax, [esp + 0x28]
004c7047 push eax
004c7048 push 2
004c704a push 0x3e8
004c704f call 0x422e20
004c7054 push 1
004c7056 mov esi, eax
004c7058 lea eax, [esp + 0x50]
004c705c push 0
004c705e push 0xff
004c7063 push -1
004c7065 mov edx, dword ptr [esi]
004c7067 mov ecx, esi
004c7069 push eax
004c706a call dword ptr [edx + 0x38]
004c706d sub dword ptr [esp + 0x10], 1
004c7072 movss xmm0, dword ptr [esp + 8]
004c7078 mov dword ptr [esi + 0xd0], 0
004c7082 movss dword ptr [esi + 0xd4], xmm0
004c708a mov dword ptr [esi + 0x2b0], 0x41200000
004c7094 jne 0x4c6f54
004c709a mov ecx, dword ptr [esp + 0x124]
004c70a1 pop edi
004c70a2 pop esi
004c70a3 xor ecx, esp
004c70a5 call 0x9eacd7
004c70aa mov esp, ebp
004c70ac pop ebp
004c70ad ret 
