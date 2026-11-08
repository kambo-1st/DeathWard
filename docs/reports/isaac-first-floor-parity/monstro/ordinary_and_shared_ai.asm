0045bec0 push ebx
0045bec1 mov ebx, esp
0045bec3 sub esp, 8
0045bec6 and esp, 0xfffffff8
0045bec9 add esp, 4
0045becc push ebp
0045becd mov ebp, dword ptr [ebx + 4]
0045bed0 mov dword ptr [esp + 4], ebp
0045bed4 mov ebp, esp
0045bed6 push -1
0045bed8 push 0x9eda70
0045bedd mov eax, dword ptr fs:[0]
0045bee3 push eax
0045bee4 push ebx
0045bee5 sub esp, 0x210
0045beeb mov eax, dword ptr [0xbaa3b4]
0045bef0 xor eax, ebp
0045bef2 mov dword ptr [ebp - 0x14], eax
0045bef5 push esi
0045bef6 push edi
0045bef7 push eax
0045bef8 lea eax, [ebp - 0xc]
0045befb mov dword ptr fs:[0], eax
0045bf01 mov edi, ecx
0045bf03 movss xmm0, dword ptr [edi + 0x2c4]
0045bf0b lea eax, [ebp - 0x1c4]
0045bf11 mulss xmm0, dword ptr [0xb6a5a4]
0045bf19 push ecx
0045bf1a mov dword ptr [esp], 0
0045bf21 push eax
0045bf22 movss dword ptr [edi + 0x2c4], xmm0
0045bf2a call 0x695a30
0045bf2f mov esi, dword ptr [edi + 0xe6c]
0045bf35 xorps xmm0, xmm0
0045bf38 mov dword ptr [ebp - 0x1a4], esi
0045bf3e xorps xmm1, xmm1
0045bf41 movss dword ptr [ebp - 0x1a8], xmm0
0045bf49 xorps xmm2, xmm2
0045bf4c movss dword ptr [ebp - 0x198], xmm0
0045bf54 movss dword ptr [ebp - 0x1ac], xmm0
0045bf5c movss dword ptr [ebp - 0x19c], xmm0
0045bf64 movss dword ptr [ebp - 0x1d0], xmm2
0045bf6c movss dword ptr [ebp - 0x1c8], xmm1
0045bf74 cmp esi, -1
0045bf77 je 0x45c411
0045bf7d push edi
0045bf7e push esi
0045bf7f push 0
0045bf81 call 0x8b1240
0045bf86 mov eax, dword ptr [edi + 0xe6c]
0045bf8c xorps xmm2, xmm2
0045bf8f subss xmm2, xmm0
0045bf93 xorps xmm1, xmm1
0045bf96 movss dword ptr [ebp - 0x1ac], xmm2
0045bf9e cmp eax, -1
0045bfa1 je 0x45c0e2
0045bfa7 push edi
0045bfa8 push eax
0045bfa9 push 1
0045bfab call 0x8b1240
0045bfb0 movss xmm1, dword ptr [ebp - 0x1ac]
0045bfb8 mov eax, dword ptr [edi + 0xe6c]
0045bfbe addss xmm1, xmm0
0045bfc2 movss dword ptr [ebp - 0x1ac], xmm1
0045bfca movss dword ptr [ebp - 0x19c], xmm1
0045bfd2 cmp eax, -1
0045bfd5 je 0x45c0f8
0045bfdb push edi
0045bfdc push eax
0045bfdd push 2
0045bfdf call 0x8b1240
0045bfe4 mov eax, dword ptr [edi + 0xe6c]
0045bfea xorps xmm1, xmm1
0045bfed subss xmm1, xmm0
0045bff1 movss dword ptr [ebp - 0x1a8], xmm1
0045bff9 cmp eax, -1
0045bffc je 0x45c0fb
0045c002 push edi
0045c003 push eax
0045c004 push 3
0045c006 call 0x8b1240
0045c00b movss xmm2, dword ptr [ebp - 0x1a8]
0045c013 mov eax, dword ptr [edi + 0xe6c]
0045c019 addss xmm2, xmm0
0045c01d movss dword ptr [ebp - 0x1a0], xmm2
0045c025 movaps xmm1, xmm2
0045c028 movss dword ptr [ebp - 0x1a8], xmm1
0045c030 movss dword ptr [ebp - 0x198], xmm1
0045c038 cmp eax, -1
0045c03b je 0x45c139
0045c041 push edi
0045c042 push eax
0045c043 push 4
0045c045 call 0x8b1240
0045c04a mov eax, dword ptr [edi + 0xe6c]
0045c050 xorps xmm1, xmm1
0045c053 subss xmm1, xmm0
0045c057 movss dword ptr [ebp - 0x1c8], xmm1
0045c05f cmp eax, -1
0045c062 je 0x45c158
0045c068 push edi
0045c069 push eax
0045c06a push 5
0045c06c call 0x8b1240
0045c071 movss xmm3, dword ptr [ebp - 0x1c8]
0045c079 mov eax, dword ptr [edi + 0xe6c]
0045c07f addss xmm3, xmm0
0045c083 movss dword ptr [ebp - 0x1b8], xmm3
0045c08b movaps xmm1, xmm3
0045c08e movss dword ptr [ebp - 0x1c8], xmm1
0045c096 cmp eax, -1
0045c099 je 0x45c174
0045c09f push edi
0045c0a0 push eax
0045c0a1 push 6
0045c0a3 call 0x8b1240
0045c0a8 mov eax, dword ptr [edi + 0xe6c]
0045c0ae xorps xmm1, xmm1
0045c0b1 subss xmm1, xmm0
0045c0b5 movss dword ptr [ebp - 0x1d0], xmm1
0045c0bd cmp eax, -1
0045c0c0 je 0x45c17c
0045c0c6 push edi
0045c0c7 push eax
0045c0c8 push 7
0045c0ca call 0x8b1240
0045c0cf mov eax, dword ptr [edi + 0xe6c]
0045c0d5 movss xmm2, dword ptr [ebp - 0x1d0]
0045c0dd jmp 0x45c185
0045c0e2 addss xmm2, xmm1
0045c0e6 movss dword ptr [ebp - 0x1ac], xmm2
0045c0ee movss dword ptr [ebp - 0x19c], xmm2
0045c0f6 jmp 0x45c0fb
0045c0f8 xorps xmm1, xmm1
0045c0fb xorps xmm0, xmm0
0045c0fe addss xmm1, xmm0
0045c102 movaps xmm2, xmm1
0045c105 movss dword ptr [ebp - 0x1a8], xmm1
0045c10d movss dword ptr [ebp - 0x198], xmm1
0045c115 xorps xmm1, xmm1
0045c118 addss xmm1, xmm0
0045c11c movss dword ptr [ebp - 0x1a0], xmm2
0045c124 xorps xmm2, xmm2
0045c127 movss dword ptr [ebp - 0x1c8], xmm1
0045c12f movss dword ptr [ebp - 0x1b8], xmm1
0045c137 jmp 0x45c182
0045c139 xorps xmm0, xmm0
0045c13c xorps xmm1, xmm1
0045c13f addss xmm1, xmm0
0045c143 xorps xmm2, xmm2
0045c146 movss dword ptr [ebp - 0x1c8], xmm1
0045c14e movss dword ptr [ebp - 0x1b8], xmm1
0045c156 jmp 0x45c182
0045c158 xorps xmm0, xmm0
0045c15b xorps xmm2, xmm2
0045c15e addss xmm1, xmm0
0045c162 movss dword ptr [ebp - 0x1c8], xmm1
0045c16a movss dword ptr [ebp - 0x1b8], xmm1
0045c172 jmp 0x45c182
0045c174 xorps xmm0, xmm0
0045c177 xorps xmm2, xmm2
0045c17a jmp 0x45c182
0045c17c xorps xmm0, xmm0
0045c17f movaps xmm2, xmm1
0045c182 or eax, 0xffffffff
0045c185 movss xmm1, dword ptr [ebp - 0x1a0]
0045c18d addss xmm2, xmm0
0045c191 movss xmm0, dword ptr [ebp - 0x1ac]
0045c199 mulss xmm1, xmm1
0045c19d mov dword ptr [ebp - 0x1b0], eax
0045c1a3 mulss xmm0, xmm0
0045c1a7 movss dword ptr [ebp - 0x1d0], xmm2
0045c1af addss xmm0, xmm1
0045c1b3 call 0x4228c0
0045c1b8 movss xmm2, dword ptr [0xb6a614]
0045c1c0 comiss xmm0, xmm2
0045c1c3 jbe 0x45c208
0045c1c5 comiss xmm0, dword ptr [0xb6a18c]
0045c1cc jbe 0x45c208
0045c1ce movaps xmm1, xmm2
0045c1d1 divss xmm1, xmm0
0045c1d5 movaps xmm0, xmm1
0045c1d8 mulss xmm1, dword ptr [ebp - 0x1a0]
0045c1e0 mulss xmm0, dword ptr [ebp - 0x1ac]
0045c1e8 movss dword ptr [ebp - 0x1a8], xmm1
0045c1f0 movss dword ptr [ebp - 0x198], xmm1
0045c1f8 movss dword ptr [ebp - 0x1ac], xmm0
0045c200 movss dword ptr [ebp - 0x19c], xmm0
0045c208 movss xmm1, dword ptr [ebp - 0x1d0]
0045c210 movss xmm0, dword ptr [ebp - 0x1b8]
0045c218 mulss xmm1, xmm1
0045c21c mulss xmm0, xmm0
0045c220 addss xmm0, xmm1
0045c224 call 0x4228c0
0045c229 movaps xmm1, xmm0
0045c22c movss xmm0, dword ptr [0xb6a614]
0045c234 comiss xmm1, xmm0
0045c237 jbe 0x45c26e
0045c239 comiss xmm1, dword ptr [0xb6a18c]
0045c240 jbe 0x45c26e
0045c242 divss xmm0, xmm1
0045c246 movss xmm1, dword ptr [ebp - 0x1b8]
0045c24e mulss xmm1, xmm0
0045c252 movss dword ptr [ebp - 0x1c8], xmm1
0045c25a movss xmm1, dword ptr [ebp - 0x1d0]
0045c262 mulss xmm1, xmm0
0045c266 movss dword ptr [ebp - 0x1d0], xmm1
0045c26e mov eax, dword ptr [ebp - 0x1b0]
0045c274 cmp eax, -1
0045c277 je 0x45c286
0045c279 push edi
0045c27a push eax
0045c27b push 9
0045c27d call 0x8b10b0
0045c282 test al, al
0045c284 jne 0x45c2ca
0045c286 mov eax, dword ptr [edi + 0xe6c]
0045c28c cmp eax, -1
0045c28f je 0x45c29e
0045c291 push edi
0045c292 push eax
0045c293 push 8
0045c295 call 0x8b10b0
0045c29a test al, al
0045c29c jne 0x45c2ca
0045c29e mov eax, dword ptr [edi + 0xe6c]
0045c2a4 cmp eax, -1
0045c2a7 je 0x45c2b6
0045c2a9 push edi
0045c2aa push eax
0045c2ab push 0xa
0045c2ad call 0x8b10b0
0045c2b2 test al, al
0045c2b4 jne 0x45c2ca
0045c2b6 push 0xb
0045c2b8 mov ecx, edi
0045c2ba call 0x6af050
0045c2bf mov byte ptr [ebp - 0x191], 0
0045c2c6 test al, al
0045c2c8 je 0x45c2d1
0045c2ca mov byte ptr [ebp - 0x191], 1
0045c2d1 movss xmm1, dword ptr [ebp - 0x1a8]
0045c2d9 movss xmm0, dword ptr [ebp - 0x1ac]
0045c2e1 mulss xmm1, xmm1
0045c2e5 mulss xmm0, xmm0
0045c2e9 addss xmm0, xmm1
0045c2ed call 0x4228c0
0045c2f2 comiss xmm0, dword ptr [0xb6a480]
0045c2f9 jbe 0x45c31b
0045c2fb movss xmm2, dword ptr [ebp - 0x1ac]
0045c303 movss xmm0, dword ptr [ebp - 0x1a8]
0045c30b movss dword ptr [edi + 0xb00], xmm2
0045c313 movss dword ptr [edi + 0xb04], xmm0
0045c31b movss xmm1, dword ptr [ebp - 0x1d0]
0045c323 movss xmm0, dword ptr [ebp - 0x1c8]
0045c32b mulss xmm1, xmm1
0045c32f mulss xmm0, xmm0
0045c333 addss xmm0, xmm1
0045c337 call 0x4228c0
0045c33c comiss xmm0, dword ptr [0xb6a480]
0045c343 jbe 0x45c365
0045c345 movss xmm0, dword ptr [ebp - 0x1c8]
0045c34d movss xmm2, dword ptr [ebp - 0x1d0]
0045c355 movss dword ptr [edi + 0xb08], xmm0
0045c35d movss dword ptr [edi + 0xb0c], xmm2
0045c365 movss xmm2, dword ptr [edi + 0xb00]
0045c36d lea ecx, [ebp - 0x1c4]
0045c373 movss xmm1, dword ptr [edi + 0xb04]
0045c37b sub esp, 0xc
0045c37e movss xmm3, dword ptr [edi + 0x2c8]
0045c386 mulss xmm2, dword ptr [0xb6abec]
0045c38e mov eax, dword ptr [0xbfd65c]
0045c393 mulss xmm1, dword ptr [0xb6abec]
0045c39b addss xmm2, dword ptr [edi + 0x294]
0045c3a3 movss dword ptr [esp + 8], xmm3
0045c3a9 addss xmm1, dword ptr [edi + 0x298]
0045c3b1 movss dword ptr [esp + 4], xmm3
0045c3b7 movss dword ptr [esp], xmm3
0045c3bc push ecx
0045c3bd lea ecx, [ebp - 0x1b4]
0045c3c3 movss dword ptr [ebp - 0x1c4], xmm2
0045c3cb push ecx
0045c3cc mov ecx, dword ptr [eax + 0x18190]
0045c3d2 movss dword ptr [ebp - 0x1c0], xmm1
0045c3da call 0x7cec10
0045c3df movss xmm1, dword ptr [ebp - 0x1b4]
0045c3e7 movss dword ptr [ebp - 0x1b8], xmm1
0045c3ef movss dword ptr [ebp - 0x1c4], xmm1
0045c3f7 movss xmm1, dword ptr [ebp - 0x1b0]
0045c3ff movss dword ptr [ebp - 0x1a0], xmm1
0045c407 movss dword ptr [ebp - 0x1c0], xmm1
0045c40f jmp 0x45c43d
0045c411 movss xmm0, dword ptr [ebp - 0x1c0]
0045c419 mov al, byte ptr [ebp - 0x1b9]
0045c41f movss dword ptr [ebp - 0x1a0], xmm0
0045c427 movss xmm0, dword ptr [ebp - 0x1c4]
0045c42f movss dword ptr [ebp - 0x1b8], xmm0
0045c437 mov byte ptr [ebp - 0x191], al
0045c43d cmp dword ptr [edi + 0x28], 0x2b
0045c441 jne 0x45c542
0045c447 cmp dword ptr [edi + 0x2c], 0
0045c44b jne 0x45c542
0045c451 mov eax, dword ptr [edi + 0xab4]
0045c457 cmp eax, 7
0045c45a je 0x45c465
0045c45c cmp eax, 4
0045c45f jne 0x45c542
0045c465 cmp dword ptr [edi + 0x70], 0
0045c469 je 0x45c542
0045c46f push 0xb4034c
0045c474 lea ecx, [edi + 0x6c]
0045c477 call 0x405e90
0045c47c test al, al
0045c47e je 0x45c542
0045c484 movss xmm3, dword ptr [0xb6aab4]
0045c48c lea eax, [edi + 0x294]
0045c492 push 8
0045c494 push eax
0045c495 lea eax, [ebp - 0x1e4]
0045c49b push eax
0045c49c mov eax, dword ptr [0xbfd65c]
0045c4a1 mov ecx, dword ptr [eax + 0x18190]
0045c4a7 add ecx, 0x1218
0045c4ad call 0x4157f0
0045c4b2 mov dword ptr [ebp - 4], 0
0045c4b9 xor ecx, ecx
0045c4bb mov edx, dword ptr [ebp - 0x1d8]
0045c4c1 mov dword ptr [ebp - 0x1b0], ecx
0045c4c7 test edx, edx
0045c4c9 je 0x45c524
0045c4cb nop dword ptr [eax + eax]
0045c4d0 mov eax, dword ptr [ebp - 0x1e0]
0045c4d6 mov esi, dword ptr [eax + ecx*4]
0045c4d9 cmp dword ptr [esi + 0x28], 0x3d
0045c4dd jne 0x45c513
0045c4df cmp dword ptr [esi + 0x2c], 0
0045c4e3 jne 0x45c513
0045c4e5 push edi
0045c4e6 lea ecx, [ebp - 0x3c]
0045c4e9 call 0x4229a0
0045c4ee mov eax, dword ptr [esi]
0045c4f0 lea ecx, [ebp - 0x3c]
0045c4f3 push 0x1e
0045c4f5 push ecx
0045c4f6 push 0
0045c4f8 push 0
0045c4fa push ecx
0045c4fb mov ecx, esi
0045c4fd mov dword ptr [esp], 0x41f00000
0045c504 call dword ptr [eax + 0x20]
0045c507 mov edx, dword ptr [ebp - 0x1d8]
0045c50d mov ecx, dword ptr [ebp - 0x1b0]
0045c513 inc ecx
0045c514 mov dword ptr [ebp - 0x1b0], ecx
0045c51a cmp ecx, edx
0045c51c jb 0x45c4d0
0045c51e mov esi, dword ptr [ebp - 0x1a4]
0045c524 mov dword ptr [ebp - 4], 0xffffffff
0045c52b cmp byte ptr [ebp - 0x1e4], 0
0045c532 jne 0x45c542
0045c534 push dword ptr [ebp - 0x1e0]
0045c53a call 0x9eace5
0045c53f add esp, 4
0045c542 mov eax, dword ptr [edi + 0xab4]
0045c548 test eax, eax
0045c54a jne 0x45c708
0045c550 mov dword ptr [edi + 0xab4], 3
0045c55a mov dword ptr [edi + 0xb10], eax
0045c560 mov eax, dword ptr [edi + 0x28]
0045c563 cmp eax, 0x14
0045c566 jne 0x45c60b
0045c56c cmp dword ptr [edi + 0x30], 1
0045c570 jne 0x45c66b
0045c576 cmp dword ptr [edi + 0x34], eax
0045c579 je 0x45c66b
0045c57f call 0x6c3d90
0045c584 movss xmm0, dword ptr [edi + 0x294]
0045c58c addss xmm0, dword ptr [0xb6a9e8]
0045c594 mov ecx, dword ptr [0xbfd65c]
0045c59a push eax
0045c59b push dword ptr [edi + 0x30]
0045c59e lea eax, [edi + 0x2b8]
0045c5a4 push edi
0045c5a5 push eax
0045c5a6 movss dword ptr [ebp - 0x19c], xmm0
0045c5ae lea eax, [ebp - 0x19c]
0045c5b4 movss xmm0, dword ptr [edi + 0x298]
0045c5bc addss xmm0, dword ptr [0xb6a18c]
0045c5c4 push eax
0045c5c5 push dword ptr [edi + 0x2c]
0045c5c8 push dword ptr [edi + 0x28]
0045c5cb movss dword ptr [ebp - 0x198], xmm0
0045c5d3 call 0x422e20
0045c5d8 movss xmm0, dword ptr [edi + 0x294]
0045c5e0 subss xmm0, dword ptr [0xb6a9e8]
0045c5e8 movss dword ptr [edi + 0x294], xmm0
0045c5f0 movss xmm0, dword ptr [edi + 0x298]
0045c5f8 subss xmm0, dword ptr [0xb6a18c]
0045c600 movss dword ptr [edi + 0x298], xmm0
0045c608 mov eax, dword ptr [edi + 0x28]
0045c60b cmp eax, 0x2b
0045c60e jne 0x45c66b
0045c610 cmp dword ptr [edi + 0x2c], 1
0045c614 jne 0x45c66b
0045c616 movaps xmm1, xmmword ptr [0xb6bf20]
0045c61d lea ecx, [edi + 0x1dc]
0045c623 lea eax, [ebp - 0x21c]
0045c629 mov dword ptr [ebp - 0x1fc], 0
0045c633 mov dword ptr [ebp - 0x1f8], 0
0045c63d xorps xmm0, xmm0
0045c640 mov dword ptr [ebp - 0x1f4], 0
0045c64a cmp ecx, eax
0045c64c je 0x45c66b
0045c64e mov eax, dword ptr [ebp - 0x1f4]
0045c654 movups xmmword ptr [ecx + 0x10], xmm0
0045c658 movq xmm0, qword ptr [ebp - 0x1fc]
0045c660 movq qword ptr [ecx + 0x20], xmm0
0045c665 movups xmmword ptr [ecx], xmm1
0045c668 mov dword ptr [ecx + 0x28], eax
0045c66b push ecx
0045c66c mov ecx, dword ptr [0xbfd65c]
0045c672 call 0x706110
0045c677 cmp eax, 0x19
0045c67a jne 0x45d24b
0045c680 and dword ptr [edi + 0x160], 0xfffffffb
0045c687 mov eax, dword ptr [edi + 0x164]
0045c68d mov dword ptr [edi + 0x164], eax
0045c693 mov dword ptr [edi + 0xab4], 7
0045c69d mov dword ptr [edi + 0xb10], 2
0045c6a7 mov esi, dword ptr [edi + 0x70]
0045c6aa test esi, esi
0045c6ac je 0x45d35e
0045c6b2 cmp dword ptr [esi + 0x14], 0x10
0045c6b6 mov eax, esi
0045c6b8 jb 0x45c6bc
0045c6ba mov eax, dword ptr [esi]
0045c6bc mov ecx, 0xb40884
0045c6c1 mov dl, byte ptr [eax]
0045c6c3 cmp dl, byte ptr [ecx]
0045c6c5 jne 0x45c6e1
0045c6c7 test dl, dl
0045c6c9 je 0x45c6dd
0045c6cb mov dl, byte ptr [eax + 1]
0045c6ce cmp dl, byte ptr [ecx + 1]
0045c6d1 jne 0x45c6e1
0045c6d3 add eax, 2
0045c6d6 add ecx, 2
0045c6d9 test dl, dl
0045c6db jne 0x45c6c1
0045c6dd xor eax, eax
0045c6df jmp 0x45c6e6
0045c6e1 sbb eax, eax
0045c6e3 or eax, 1
0045c6e6 test eax, eax
0045c6e8 jne 0x45d35e
0045c6ee cmp byte ptr [esi + 0x34], al
0045c6f1 je 0x45d24b
0045c6f7 cmp byte ptr [edi + 0x80], al
0045c6fd jne 0x45d24b
0045c703 jmp 0x45d35e
0045c708 cmp eax, 3
0045c70b jne 0x45ca1e
0045c711 push 1
0045c713 push 0xb41264
0045c718 lea ecx, [edi + 0x3c]
0045c71b call 0x405740
0045c720 test al, al
0045c722 je 0x45c744
0045c724 mov eax, dword ptr [edi + 0x70]
0045c727 test eax, eax
0045c729 je 0x45c744
0045c72b lea ecx, [edi + 0x6c]
0045c72e xorps xmm1, xmm1
0045c731 call 0x403c00
0045c736 mov eax, dword ptr [edi + 0x70]
0045c739 test eax, eax
0045c73b je 0x45c744
0045c73d mov byte ptr [edi + 0x80], 0
0045c744 cmp dword ptr [edi + 0x28], 0x2b
0045c748 mov dword ptr [edi + 0x180], 4
0045c752 mov dword ptr [edi + 0x17c], 5
0045c75c jne 0x45c86b
0045c762 cmp dword ptr [edi + 0x2c], 0
0045c766 jne 0x45c86b
0045c76c mov ecx, edi
0045c76e call 0x695680
0045c773 movss xmm1, dword ptr [edi + 0x298]
0045c77b subss xmm1, dword ptr [eax + 0x298]
0045c783 andps xmm1, xmmword ptr [0xb6c980]
0045c78a call 0x6c3d90
0045c78f xorps xmm0, xmm0
0045c792 cvtsi2sd xmm0, eax
0045c796 shr eax, 0x1f
0045c799 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
0045c7a2 cvtpd2ps xmm0, xmm0
0045c7a6 mulss xmm0, dword ptr [0xb6a19c]
0045c7ae mulss xmm0, dword ptr [0xb6aa60]
0045c7b6 addss xmm0, dword ptr [0xb6a9c8]
0045c7be comiss xmm0, xmm1
0045c7c1 jbe 0x45c7ca
0045c7c3 mov esi, 1
0045c7c8 jmp 0x45c7da
0045c7ca call 0x6c3d90
0045c7cf movzx esi, al
0045c7d2 xor esi, 0xffffffff
0045c7d5 and esi, 1
0045c7d8 add esi, esi
0045c7da mov eax, dword ptr [edi + 0x28]
0045c7dd cmp eax, 0x2b
0045c7e0 jne 0x45c83f
0045c7e2 cmp dword ptr [edi + 0xb14], esi
0045c7e8 jne 0x45c83f
0045c7ea call 0x6c3d90
0045c7ef movss xmm2, dword ptr [0xb6a5a4]
0045c7f7 movd xmm0, eax
0045c7fb cvtdq2pd xmm0, xmm0
0045c7ff shr eax, 0x1f
0045c802 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
0045c80b cvtpd2ps xmm0, xmm0
0045c80f mulss xmm0, dword ptr [0xb6a19c]
0045c817 comiss xmm2, xmm0
0045c81a jbe 0x45c83f
0045c81c call 0x6c3d90
0045c821 and eax, 1
0045c824 inc eax
0045c825 add esi, eax
0045c827 mov eax, 0x55555555
0045c82c imul esi
0045c82e sub edx, esi
0045c830 sar edx, 1
0045c832 mov ecx, edx
0045c834 shr ecx, 0x1f
0045c837 add ecx, edx
0045c839 lea eax, [ecx + esi]
0045c83c lea esi, [eax + ecx*2]
0045c83f mov eax, dword ptr [ebp - 0x1a4]
0045c845 mov dword ptr [edi + 0xb14], esi
0045c84b cmp eax, -1
0045c84e jne 0x45c897
0045c850 cmp esi, 2
0045c853 je 0x45c8a0
0045c855 cmp esi, 1
0045c858 je 0x45c931
0045c85e test esi, esi
0045c860 je 0x45c9c0
0045c866 jmp 0x45c963
0045c86b call 0x6c3d90
0045c870 xor edx, edx
0045c872 mov ecx, 3
0045c877 div ecx
0045c879 mov eax, dword ptr [edi + 0x28]
0045c87c mov esi, edx
0045c87e cmp eax, 0x14
0045c881 jne 0x45c7dd
0045c887 cmp dword ptr [edi + 0x30], 2
0045c88b jne 0x45c83f
0045c88d cmp esi, 2
0045c890 jne 0x45c83f
0045c892 lea esi, [ecx - 2]
0045c895 jmp 0x45c83f
0045c897 cmp byte ptr [ebp - 0x191], 0
0045c89e je 0x45c907
0045c8a0 push ecx
0045c8a1 mov dword ptr [esp], 0x3f800000
0045c8a8 push 0
0045c8aa push 2
0045c8ac push ecx
0045c8ad mov dword ptr [esp], 0x3f800000
0045c8b4 mov ecx, edi
0045c8b6 push 0xe
0045c8b8 mov dword ptr [edi + 0xab4], 6
0045c8c2 call 0x6ad720
0045c8c7 push 1
0045c8c9 push 0xb408a0
0045c8ce lea ecx, [edi + 0x3c]
0045c8d1 call 0x405740
0045c8d6 test al, al
0045c8d8 je 0x45c8e9
0045c8da lea ecx, [edi + 0x6c]
0045c8dd call 0x405330
0045c8e2 mov byte ptr [edi + 0x80], 1
0045c8e9 cmp dword ptr [edi + 0x28], 0x2b
0045c8ed jne 0x45c95d
0045c8ef cmp dword ptr [edi + 0x30], 1
0045c8f3 mov eax, dword ptr [ebp - 0x1a4]
0045c8f9 jne 0x45c963
0045c8fb mov dword ptr [edi + 0x140], 0x3fc00000
0045c905 jmp 0x45c963
0045c907 movss xmm1, dword ptr [ebp - 0x1c8]
0045c90f movss xmm0, dword ptr [ebp - 0x1d0]
0045c917 mulss xmm0, xmm0
0045c91b mulss xmm1, xmm1
0045c91f addss xmm0, xmm1
0045c923 call 0x4228c0
0045c928 comiss xmm0, dword ptr [0xb6a480]
0045c92f jbe 0x45c996
0045c931 push 1
0045c933 push 0xb40898
0045c938 lea ecx, [edi + 0x3c]
0045c93b mov dword ptr [edi + 0xab4], 8
0045c945 call 0x405740
0045c94a test al, al
0045c94c je 0x45c95d
0045c94e lea ecx, [edi + 0x6c]
0045c951 call 0x405330
0045c956 mov byte ptr [edi + 0x80], 1
0045c95d mov eax, dword ptr [ebp - 0x1a4]
0045c963 cmp dword ptr [edi + 0xab4], 8
0045c96a jne 0x45d24b
0045c970 cmp eax, -1
0045c973 je 0x45c9f3
0045c979 movss xmm0, dword ptr [edi + 0xb08]
0045c981 comiss xmm0, dword ptr [0xb6a18c]
0045c988 setae al
0045c98b mov byte ptr [edi + 0x13c], al
0045c991 jmp 0x45d24b
0045c996 movss xmm1, dword ptr [ebp - 0x1ac]
0045c99e movss xmm0, dword ptr [ebp - 0x1a8]
0045c9a6 mulss xmm0, xmm0
0045c9aa mulss xmm1, xmm1
0045c9ae addss xmm0, xmm1
0045c9b2 call 0x4228c0
0045c9b7 comiss xmm0, dword ptr [0xb6a480]
0045c9be jbe 0x45c95d
0045c9c0 push ecx
0045c9c1 mov dword ptr [esp], 0x3f800000
0045c9c8 push 0
0045c9ca push 2
0045c9cc push ecx
0045c9cd mov dword ptr [esp], 0x3f000000
0045c9d4 mov ecx, edi
0045c9d6 push 0xe
0045c9d8 mov dword ptr [edi + 0xab4], 4
0045c9e2 call 0x6ad720
0045c9e7 push 1
0045c9e9 push 0xb41264
0045c9ee jmp 0x45c8ce
0045c9f3 mov ecx, edi
0045c9f5 call 0x695680
0045c9fa movss xmm1, dword ptr [edi + 0x294]
0045ca02 xorps xmm0, xmm0
0045ca05 subss xmm1, dword ptr [eax + 0x294]
0045ca0d comiss xmm0, xmm1
0045ca10 seta al
0045ca13 mov byte ptr [edi + 0x13c], al
0045ca19 jmp 0x45d24b
0045ca1e cmp eax, 8
0045ca21 jne 0x45cd46
0045ca27 cmp dword ptr [edi + 0x70], 0
0045ca2b je 0x45cd37
0045ca31 push 0xb400ac
0045ca36 lea ecx, [edi + 0x6c]
0045ca39 call 0x405e90
0045ca3e test al, al
0045ca40 je 0x45cd24
0045ca46 mov eax, dword ptr [edi + 0x28]
0045ca49 cmp eax, 0x14
0045ca4c jne 0x45cb5a
0045ca52 push ecx
0045ca53 mov dword ptr [esp], 0x3f800000
0045ca5a push 0
0045ca5c push 2
0045ca5e push ecx
0045ca5f mov dword ptr [esp], 0x3f800000
0045ca66 mov ecx, edi
0045ca68 push 0x10
0045ca6a call 0x6ad720
0045ca6f cmp esi, -1
0045ca72 je 0x45cac6
0045ca74 movss xmm0, dword ptr [edi + 0xb08]
0045ca7c comiss xmm0, dword ptr [0xb6a18c]
0045ca83 mulss xmm0, dword ptr [0xb6aafc]
0045ca8b setae al
0045ca8e mov byte ptr [edi + 0x13c], al
0045ca94 addss xmm0, dword ptr [edi + 0x294]
0045ca9c movss dword ptr [ebp - 0x19c], xmm0
0045caa4 movss xmm0, dword ptr [edi + 0xb0c]
0045caac mulss xmm0, dword ptr [0xb6aafc]
0045cab4 addss xmm0, dword ptr [edi + 0x298]
0045cabc movss dword ptr [ebp - 0x198], xmm0
0045cac4 jmp 0x45cae5
0045cac6 mov ecx, edi
0045cac8 call 0x695680
0045cacd mov ecx, dword ptr [eax + 0x294]
0045cad3 mov eax, dword ptr [eax + 0x298]
0045cad9 mov dword ptr [ebp - 0x19c], ecx
0045cadf mov dword ptr [ebp - 0x198], eax
0045cae5 lea ecx, [ebp - 0xe8]
0045caeb call 0x430d70
0045caf0 push eax
0045caf1 push ecx
0045caf2 mov dword ptr [esp], 0
0045caf9 lea eax, [ebp - 0x19c]
0045caff push eax
0045cb00 push 0xd
0045cb02 mov ecx, edi
0045cb04 call 0x6a3420
0045cb09 movss xmm0, dword ptr [0xb6a614]
0045cb11 push ecx
0045cb12 movaps xmm3, xmm0
0045cb15 mov dword ptr [esp], 0x3f4ccccd
0045cb1c movaps xmm2, xmm0
0045cb1f lea ecx, [ebp - 0x40]
0045cb22 movaps xmm1, xmm0
0045cb25 call 0x4325d0
0045cb2a movss xmm2, dword ptr [0xb6a50c]
0045cb32 mov ecx, edi
0045cb34 push eax
0045cb35 lea eax, [edi + 0x294]
0045cb3b push eax
0045cb3c call 0x68db10
0045cb41 mov dword ptr [eax + 0x2a4], 0
0045cb4b mov dword ptr [eax + 0x2a8], 0xc1e80000
0045cb55 jmp 0x45cd24
0045cb5a cmp eax, 0x2b
0045cb5d jne 0x45cd24
0045cb63 cmp dword ptr [edi + 0x2c], 0
0045cb67 jne 0x45cc18
0045cb6d cmp esi, -1
0045cb70 je 0x45cbb5
0045cb72 movss xmm1, dword ptr [edi + 0xb08]
0045cb7a comiss xmm1, dword ptr [0xb6a18c]
0045cb81 mov dword ptr [ebp - 0x19c], 0
0045cb8b mov dword ptr [ebp - 0x198], 0xc1a00000
0045cb95 setae al
0045cb98 mov byte ptr [edi + 0x13c], al
0045cb9e movss xmm0, dword ptr [edi + 0xb0c]
0045cba6 call 0x447a80
0045cbab mulss xmm0, dword ptr [0xb6aa84]
0045cbb3 jmp 0x45cbdf
0045cbb5 cmp byte ptr [edi + 0x13c], 0
0045cbbc je 0x45cbc3
0045cbbe xorps xmm0, xmm0
0045cbc1 jmp 0x45cbcb
0045cbc3 movss xmm0, dword ptr [0xb6ab88]
0045cbcb mov dword ptr [ebp - 0x19c], 0
0045cbd5 mov dword ptr [ebp - 0x198], 0xc1a00000
0045cbdf push 0
0045cbe1 push edi
0045cbe2 lea eax, [ebp - 0x19c]
0045cbe8 push eax
0045cbe9 push 0x1e
0045cbeb push ecx
0045cbec movss dword ptr [esp], xmm0
0045cbf1 lea eax, [edi + 0x294]
0045cbf7 push eax
0045cbf8 push 1
0045cbfa call 0x8c7550
0045cbff mov ecx, eax
0045cc01 add esp, 0x1c
0045cc04 mov eax, dword ptr [ecx]
0045cc06 mov dword ptr [ecx + 0x2b0], 0x453b8000
0045cc10 call dword ptr [eax + 0xc]
0045cc13 jmp 0x45cd24
0045cc18 cmp esi, -1
0045cc1b je 0x45cc75
0045cc1d movss xmm0, dword ptr [edi + 0xb08]
0045cc25 lea ecx, [ebp - 0xe8]
0045cc2b comiss xmm0, dword ptr [0xb6a18c]
0045cc32 mulss xmm0, dword ptr [0xb6aab4]
0045cc3a setae al
0045cc3d mov byte ptr [edi + 0x13c], al
0045cc43 addss xmm0, dword ptr [edi + 0x294]
0045cc4b movss dword ptr [ebp - 0x19c], xmm0
0045cc53 movss xmm0, dword ptr [edi + 0xb0c]
0045cc5b mulss xmm0, dword ptr [0xb6aab4]
0045cc63 addss xmm0, dword ptr [edi + 0x298]
0045cc6b movss dword ptr [ebp - 0x198], xmm0
0045cc73 jmp 0x45cc9a
0045cc75 mov ecx, edi
0045cc77 call 0x695680
0045cc7c mov ecx, dword ptr [eax + 0x294]
0045cc82 mov eax, dword ptr [eax + 0x298]
0045cc88 mov dword ptr [ebp - 0x19c], ecx
0045cc8e lea ecx, [ebp - 0x190]
0045cc94 mov dword ptr [ebp - 0x198], eax
0045cc9a call 0x430d70
0045cc9f push eax
0045cca0 push ecx
0045cca1 mov dword ptr [esp], 0x41200000
0045cca8 lea eax, [ebp - 0x19c]
0045ccae push eax
0045ccaf push 1
0045ccb1 mov ecx, edi
0045ccb3 call 0x6a3420
0045ccb8 mov ecx, eax
0045ccba push 1
0045ccbc push 0
0045ccbe push 0xff
0045ccc3 movss xmm0, dword ptr [ecx + 0x368]
0045cccb subss xmm0, dword ptr [0xb6a3b0]
0045ccd3 mov eax, dword ptr [ecx + 0x38c]
0045ccd9 or dword ptr [ecx + 0x388], 0xa
0045cce0 mov dword ptr [ecx + 0x38c], eax
0045cce6 mov eax, dword ptr [ecx]
0045cce8 movss dword ptr [ecx + 0x368], xmm0
0045ccf0 movss xmm0, dword ptr [ecx + 0x364]
0045ccf8 mulss xmm0, dword ptr [0xb6a50c]
0045cd00 push -1
0045cd02 push 0xbc5254
0045cd07 mov dword ptr [ecx + 0x370], 0x3fcccccd
0045cd11 subss xmm0, dword ptr [0xb6a994]
0045cd19 movss dword ptr [ecx + 0x364], xmm0
0045cd21 call dword ptr [eax + 0x38]
0045cd24 cmp dword ptr [edi + 0x70], 0
0045cd28 je 0x45cd37
0045cd2a cmp byte ptr [edi + 0x80], 0
0045cd31 jne 0x45d24b
0045cd37 mov dword ptr [edi + 0xab4], 3
0045cd41 jmp 0x45d24b
0045cd46 cmp eax, 4
0045cd49 jne 0x45d2e4
0045cd4f cmp esi, -1
0045cd52 je 0x45cde1
0045cd58 cmp dword ptr [edi + 0x70], 0
0045cd5c je 0x45cd6c
0045cd5e movss xmm0, dword ptr [0xb6a8cc]
0045cd66 comiss xmm0, dword ptr [edi + 0x7c]
0045cd6a jbe 0x45cde1
0045cd6c cmp byte ptr [ebp - 0x191], 0
0045cd73 je 0x45cde1
0045cd75 push ecx
0045cd76 mov dword ptr [esp], 0x3f800000
0045cd7d push 0
0045cd7f push 2
0045cd81 push ecx
0045cd82 mov dword ptr [esp], 0x3f800000
0045cd89 mov ecx, edi
0045cd8b push 0xe
0045cd8d mov dword ptr [edi + 0xab4], 6
0045cd97 call 0x6ad720
0045cd9c push 1
0045cd9e push 0xb408a0
0045cda3 lea ecx, [edi + 0x3c]
0045cda6 call 0x405740
0045cdab test al, al
0045cdad je 0x45cdbe
0045cdaf lea ecx, [edi + 0x6c]
0045cdb2 call 0x405330
0045cdb7 mov byte ptr [edi + 0x80], 1
0045cdbe cmp dword ptr [edi + 0x28], 0x2b
0045cdc2 jne 0x45d24b
0045cdc8 cmp dword ptr [edi + 0x30], 1
0045cdcc jne 0x45d24b
0045cdd2 mov dword ptr [edi + 0x140], 0x3fc00000
0045cddc jmp 0x45d24b
0045cde1 movss xmm0, dword ptr [edi + 0x28c]
0045cde9 ucomiss xmm0, dword ptr [0xc02fec]
0045cdf0 lahf 
0045cdf1 test ah, 0x44
0045cdf4 jp 0x45ceb8
0045cdfa movss xmm0, dword ptr [edi + 0x290]
0045ce02 ucomiss xmm0, dword ptr [0xc02ff0]
0045ce09 lahf 
0045ce0a test ah, 0x44
0045ce0d jp 0x45ceb8
0045ce13 mov eax, dword ptr [0xbfd65c]
0045ce18 push dword ptr [ebp - 0x1c0]
0045ce1e push dword ptr [ebp - 0x1c4]
0045ce24 mov eax, dword ptr [eax + 0x18190]
0045ce2a mov ecx, eax
0045ce2c mov dword ptr [ebp - 0x1b0], eax
0045ce32 call 0x7aee40
0045ce37 test eax, eax
0045ce39 jne 0x45ce93
0045ce3b mov ecx, dword ptr [ebp - 0x1b0]
0045ce41 lea eax, [ebp - 0x1c4]
0045ce47 push eax
0045ce48 call 0x7ce950
0045ce4d mov ecx, dword ptr [ebp - 0x1b0]
0045ce53 cdq 
0045ce54 movss xmm0, dword ptr [0xb6aa3c]
0045ce5c mov ecx, dword ptr [ecx + 0xc]
0045ce5f idiv ecx
0045ce61 movd xmm2, edx
0045ce65 movd xmm1, eax
0045ce69 cvtdq2ps xmm2, xmm2
0045ce6c cvtdq2ps xmm1, xmm1
0045ce6f mulss xmm2, xmm0
0045ce73 mulss xmm1, xmm0
0045ce77 addss xmm2, xmm0
0045ce7b addss xmm1, dword ptr [0xb6ab20]
0045ce83 movss dword ptr [edi + 0x28c], xmm2
0045ce8b movss dword ptr [edi + 0x290], xmm1
0045ce93 cmp esi, -1
0045ce96 je 0x45ceb8
0045ce98 movss xmm0, dword ptr [ebp - 0x1b8]
0045cea0 movss dword ptr [edi + 0x28c], xmm0
0045cea8 movss xmm0, dword ptr [ebp - 0x1a0]
0045ceb0 movss dword ptr [edi + 0x290], xmm0
0045ceb8 movss xmm0, dword ptr [edi + 0x28c]
0045cec0 ucomiss xmm0, dword ptr [0xc02fec]
0045cec7 lahf 
0045cec8 test ah, 0x44
0045cecb jp 0x45ceff
0045cecd movss xmm0, dword ptr [edi + 0x290]
0045ced5 ucomiss xmm0, dword ptr [0xc02ff0]
0045cedc lahf 
0045cedd test ah, 0x44
0045cee0 jp 0x45ceff
0045cee2 movss xmm0, dword ptr [edi + 0x2c4]
0045ceea mulss xmm0, dword ptr [0xb6a560]
0045cef2 movss dword ptr [edi + 0x2c4], xmm0
0045cefa jmp 0x45d24b
0045ceff lea esi, [edi + 0x3c]
0045cf02 push 0xb40338
0045cf07 mov ecx, esi
0045cf09 call 0x406150
0045cf0e push 0xb4034c
0045cf13 mov ecx, esi
0045cf15 mov byte ptr [ebp - 0x192], al
0045cf1b call 0x406150
0045cf20 cmp byte ptr [ebp - 0x192], 0
0045cf27 mov byte ptr [ebp - 0x1b9], al
0045cf2d je 0x45cf3c
0045cf2f test al, al
0045cf31 jne 0x45cf3c
0045cf33 mov ecx, 3
0045cf38 xor edx, edx
0045cf3a jmp 0x45cf46
0045cf3c mov ecx, 5
0045cf41 mov edx, 4
0045cf46 mov dword ptr [edi + 0x180], edx
0045cf4c mov dword ptr [edi + 0x17c], ecx
0045cf52 mov ecx, esi
0045cf54 push 0xb4034c
0045cf59 call 0x4060f0
0045cf5e test al, al
0045cf60 je 0x45d015
0045cf66 push ecx
0045cf67 mov dword ptr [esp], 0x3f800000
0045cf6e push 0
0045cf70 push 2
0045cf72 push ecx
0045cf73 mov dword ptr [esp], 0x3f000000
0045cf7a mov ecx, edi
0045cf7c push 0x30
0045cf7e call 0x6ad720
0045cf83 call 0x6c3d90
0045cf88 mov ecx, dword ptr [0xbfd65c]
0045cf8e push eax
0045cf8f push 2
0045cf91 push edi
0045cf92 push 0xc02fec
0045cf97 lea eax, [edi + 0x294]
0045cf9d push eax
0045cf9e push 0x10
0045cfa0 push 0x3e8
0045cfa5 call 0x422e20
0045cfaa mov esi, eax
0045cfac call 0x6c3d90
0045cfb1 movss xmm0, dword ptr [0xb6a560]
0045cfb9 not al
0045cfbb push 1
0045cfbd push 0
0045cfbf push 0xff
0045cfc4 push -1
0045cfc6 push ecx
0045cfc7 and al, 1
0045cfc9 mov dword ptr [esi + 0xd0], 0
0045cfd3 mov dword ptr [esi + 0xd4], 0x41700000
0045cfdd lea ecx, [ebp - 0x40]
0045cfe0 mov edx, dword ptr [esi]
0045cfe2 movaps xmm3, xmm0
0045cfe5 movaps xmm2, xmm0
0045cfe8 mov byte ptr [esi + 0x13c], al
0045cfee movaps xmm1, xmm0
0045cff1 mov dword ptr [esp], 0x3f333333
0045cff8 call 0x4325d0
0045cffd push eax
0045cffe mov ecx, esi
0045d000 call dword ptr [edx + 0x38]
0045d003 push edi
0045d004 mov ecx, esi
0045d006 call 0x447de0
0045d00b mov eax, dword ptr [esi]
0045d00d mov ecx, esi
0045d00f call dword ptr [eax + 0xc]
0045d012 lea esi, [edi + 0x3c]
0045d015 cmp byte ptr [ebp - 0x1b9], 0
0045d01c jne 0x45d1f2
0045d022 movss xmm1, dword ptr [edi + 0x290]
0045d02a subss xmm1, dword ptr [edi + 0x298]
0045d032 movss xmm2, dword ptr [edi + 0x28c]
0045d03a subss xmm2, dword ptr [edi + 0x294]
0045d042 movaps xmm0, xmm1
0045d045 movss dword ptr [ebp - 0x1b0], xmm1
0045d04d mulss xmm0, xmm1
0045d051 movaps xmm1, xmm2
0045d054 movss dword ptr [ebp - 0x1a0], xmm2
0045d05c mulss xmm1, xmm2
0045d060 addss xmm0, xmm1
0045d064 call 0x4228c0
0045d069 cmp dword ptr [ebp - 0x1a4], -1
0045d070 movaps xmm3, xmm0
0045d073 movss dword ptr [ebp - 0x1b8], xmm3
0045d07b je 0x45d12a
0045d081 cmp byte ptr [ebp - 0x192], 0
0045d088 je 0x45d12a
0045d08e lea eax, [ebp - 0x19c]
0045d094 push eax
0045d095 lea ecx, [edi + 0x2b8]
0045d09b call 0x962560
0045d0a0 movss xmm1, dword ptr [ebp - 0x1a8]
0045d0a8 movss xmm3, dword ptr [ebp - 0x1ac]
0045d0b0 movaps xmm4, xmm1
0045d0b3 movaps xmm0, xmm3
0045d0b6 mulss xmm0, dword ptr [eax]
0045d0ba mulss xmm4, dword ptr [eax + 4]
0045d0bf addss xmm4, xmm0
0045d0c3 xorps xmm0, xmm0
0045d0c6 comiss xmm0, xmm4
0045d0c9 jbe 0x45d0cf
0045d0cb mulss xmm4, xmm0
0045d0cf movaps xmm2, xmm4
0045d0d2 lea ecx, [edi + 0x2b8]
0045d0d8 mulss xmm2, xmm4
0045d0dc push 0xc02fec
0045d0e1 mulss xmm2, xmm4
0045d0e5 andps xmm2, xmmword ptr [0xb6c980]
0045d0ec mulss xmm2, dword ptr [0xb6a4c4]
0045d0f4 addss xmm2, dword ptr [0xb6a434]
0045d0fc call 0x962c70
0045d101 test al, al
0045d103 je 0x45d10d
0045d105 movss xmm2, dword ptr [0xb6a614]
0045d10d movaps xmm4, xmm2
0045d110 mulss xmm2, xmm1
0045d114 mulss xmm4, xmm3
0045d118 movss xmm3, dword ptr [ebp - 0x1b8]
0045d120 mulss xmm2, xmm3
0045d124 mulss xmm4, xmm3
0045d128 jmp 0x45d13a
0045d12a movss xmm4, dword ptr [ebp - 0x1a0]
0045d132 movss xmm2, dword ptr [ebp - 0x1b0]
0045d13a xorps xmm1, xmm1
0045d13d ucomiss xmm3, xmm1
0045d140 lahf 
0045d141 test ah, 0x44
0045d144 jp 0x45d14e
0045d146 movss xmm3, dword ptr [0xb6a1c8]
0045d14e cmp dword ptr [edi + 0x28], 0x2b
0045d152 movss xmm0, dword ptr [0xb6a670]
0045d15a divss xmm0, xmm3
0045d15e jne 0x45d16e
0045d160 cmp dword ptr [edi + 0x30], 1
0045d164 jne 0x45d16e
0045d166 mulss xmm0, dword ptr [0xb6a6f0]
0045d16e movss xmm5, dword ptr [edi + 0x2c4]
0045d176 ucomiss xmm5, xmm1
0045d179 mulss xmm4, xmm0
0045d17d lahf 
0045d17e mulss xmm2, xmm0
0045d182 test ah, 0x44
0045d185 jnp 0x45d1cc
0045d187 movss xmm0, dword ptr [edi + 0x2f4]
0045d18f movaps xmm3, xmm0
0045d192 mulss xmm0, xmm2
0045d196 mulss xmm3, xmm4
0045d19a divss xmm0, xmm5
0045d19e divss xmm3, xmm5
0045d1a2 addss xmm0, dword ptr [edi + 0x2bc]
0045d1aa addss xmm3, dword ptr [edi + 0x2b8]
0045d1b2 movss dword ptr [edi + 0x2bc], xmm0
0045d1ba movss dword ptr [edi + 0x2b8], xmm3
0045d1c2 movss xmm5, dword ptr [edi + 0x2c4]
0045d1ca jmp 0x45d1d4
0045d1cc movss xmm3, dword ptr [edi + 0x2b8]
0045d1d4 mulss xmm5, dword ptr [0xb6a5a4]
0045d1dc comiss xmm3, xmm1
0045d1df movss dword ptr [edi + 0x2c4], xmm5
0045d1e7 seta al
0045d1ea mov byte ptr [edi + 0x13c], al
0045d1f0 jmp 0x45d24b
0045d1f2 cmp dword ptr [edi + 0x70], 0
0045d1f6 je 0x45d205
0045d1f8 cmp byte ptr [edi + 0x80], 0
0045d1ff jne 0x45cee2
0045d205 cmp dword ptr [ebp - 0x1a4], -1
0045d20c movss xmm0, dword ptr [0xc02fec]
0045d214 movss dword ptr [edi + 0x28c], xmm0
0045d21c movss xmm0, dword ptr [0xc02ff0]
0045d224 movss dword ptr [edi + 0x290], xmm0
0045d22c jne 0x45d269
0045d22e call 0x6c3d90
0045d233 test al, 1
0045d235 jne 0x45d2a0
0045d237 mov dword ptr [edi + 0xab4], 3
0045d241 mov dword ptr [edi + 0x140], 0x3f800000
0045d24b mov ecx, dword ptr [ebp - 0xc]
0045d24e mov dword ptr fs:[0], ecx
0045d255 pop ecx
0045d256 pop edi
0045d257 pop esi
0045d258 mov ecx, dword ptr [ebp - 0x14]
0045d25b xor ecx, ebp
0045d25d call 0x9eacd7
0045d262 mov esp, ebp
0045d264 pop ebp
0045d265 mov esp, ebx
0045d267 pop ebx
0045d268 ret 
0045d269 movss xmm1, dword ptr [ebp - 0x1ac]
0045d271 movss xmm0, dword ptr [ebp - 0x1a8]
0045d279 mulss xmm0, xmm0
0045d27d mulss xmm1, xmm1
0045d281 addss xmm0, xmm1
0045d285 call 0x4228c0
0045d28a movss xmm1, dword ptr [0xb6a480]
0045d292 comiss xmm1, xmm0
0045d295 ja 0x45d237
0045d297 cmp byte ptr [ebp - 0x191], 0
0045d29e jne 0x45d237
0045d2a0 push ecx
0045d2a1 mov dword ptr [esp], 0x3f800000
0045d2a8 push 0
0045d2aa push 2
0045d2ac push ecx
0045d2ad mov dword ptr [esp], 0x3ecccccd
0045d2b4 mov ecx, edi
0045d2b6 push 0xe
0045d2b8 call 0x6ad720
0045d2bd push 1
0045d2bf push 0xb41264
0045d2c4 mov ecx, esi
0045d2c6 call 0x405740
0045d2cb test al, al
0045d2cd je 0x45d24b
0045d2d3 lea ecx, [esi + 0x30]
0045d2d6 call 0x405330
0045d2db mov byte ptr [esi + 0x44], 1
0045d2df jmp 0x45d24b
0045d2e4 cmp eax, 6
0045d2e7 jne 0x45d389
0045d2ed mov dword ptr [edi + 0x180], 4
0045d2f7 mov dword ptr [edi + 0x17c], 5
0045d301 cmp dword ptr [edi + 0x70], 0
0045d305 je 0x45d24b
0045d30b push 0xb40338
0045d310 lea ecx, [edi + 0x6c]
0045d313 call 0x405f30
0045d318 test al, al
0045d31a je 0x45d24b
0045d320 mov dword ptr [edi + 0x180], 0
0045d32a mov dword ptr [edi + 0x17c], 3
0045d334 mov dword ptr [edi + 0xab4], 7
0045d33e movss xmm0, dword ptr [0xc02fec]
0045d346 movss dword ptr [edi + 0x28c], xmm0
0045d34e movss xmm0, dword ptr [0xc02ff0]
0045d356 movss dword ptr [edi + 0x290], xmm0
0045d35e push 1
0045d360 push 0xb40884
0045d365 lea ecx, [edi + 0x3c]
0045d368 call 0x405740
0045d36d test al, al
0045d36f je 0x45d24b
0045d375 lea ecx, [edi + 0x6c]
0045d378 call 0x405330
0045d37d mov byte ptr [edi + 0x80], 1
0045d384 jmp 0x45d24b
0045d389 cmp eax, 7
0045d38c jne 0x45d24b
0045d392 lea esi, [edi + 0x28c]
0045d398 push 0xc02fec
0045d39d mov ecx, esi
0045d39f call 0x962c70
0045d3a4 test al, al
0045d3a6 je 0x45d507
0045d3ac cmp dword ptr [edi + 0xb10], 2
0045d3b3 movss xmm0, dword ptr [ebp - 0x1b8]
0045d3bb movss dword ptr [ebp - 0x1c4], xmm0
0045d3c3 movss xmm0, dword ptr [ebp - 0x1a0]
0045d3cb movss dword ptr [ebp - 0x1c0], xmm0
0045d3d3 jne 0x45d471
0045d3d9 mov ecx, edi
0045d3db call 0x695680
0045d3e0 movss xmm0, dword ptr [eax + 0x2c8]
0045d3e8 addss xmm0, dword ptr [edi + 0x2c8]
0045d3f0 mov ecx, dword ptr [eax + 0x2b8]
0045d3f6 mov eax, dword ptr [eax + 0x2bc]
0045d3fc mov dword ptr [ebp - 0x1c8], eax
0045d402 lea eax, [ebp - 0x1d4]
0045d408 mov dword ptr [ebp - 0x1cc], ecx
0045d40e lea ecx, [ebp - 0x1cc]
0045d414 addss xmm0, dword ptr [0xb6a8f4]
0045d41c push eax
0045d41d movss dword ptr [ebp - 0x1b0], xmm0
0045d425 call 0x962560
0045d42a movss xmm2, dword ptr [eax]
0045d42e movss xmm1, dword ptr [eax + 4]
0045d433 xorps xmm2, xmmword ptr [0xb6c9b0]
0045d43a xorps xmm1, xmmword ptr [0xb6c9b0]
0045d441 mulss xmm2, dword ptr [ebp - 0x1b0]
0045d449 mulss xmm1, dword ptr [ebp - 0x1b0]
0045d451 addss xmm2, dword ptr [ebp - 0x1b8]
0045d459 addss xmm1, dword ptr [ebp - 0x1a0]
0045d461 movss dword ptr [ebp - 0x1c4], xmm2
0045d469 movss dword ptr [ebp - 0x1c0], xmm1
0045d471 mov eax, dword ptr [0xbfd65c]
0045d476 push dword ptr [ebp - 0x1c0]
0045d47c push dword ptr [ebp - 0x1c4]
0045d482 mov eax, dword ptr [eax + 0x18190]
0045d488 mov ecx, eax
0045d48a mov dword ptr [ebp - 0x1b0], eax
0045d490 call 0x7aee40
0045d495 test eax, eax
0045d497 jne 0x45d507
0045d499 mov ecx, dword ptr [ebp - 0x1b0]
0045d49f lea eax, [ebp - 0x1c4]
0045d4a5 push eax
0045d4a6 call 0x7ce950
0045d4ab mov ecx, dword ptr [ebp - 0x1b0]
0045d4b1 cdq 
0045d4b2 movss xmm0, dword ptr [0xb6aa3c]
0045d4ba mov ecx, dword ptr [ecx + 0xc]
0045d4bd idiv ecx
0045d4bf movd xmm2, edx
0045d4c3 movd xmm1, eax
0045d4c7 cvtdq2ps xmm2, xmm2
0045d4ca cvtdq2ps xmm1, xmm1
0045d4cd mulss xmm2, xmm0
0045d4d1 mulss xmm1, xmm0
0045d4d5 addss xmm2, xmm0
0045d4d9 addss xmm1, dword ptr [0xb6ab20]
0045d4e1 movss dword ptr [esi], xmm2
0045d4e5 movss dword ptr [esi + 4], xmm1
0045d4ea cmp dword ptr [edi + 0xb10], 2
0045d4f1 jne 0x45d507
0045d4f3 movss dword ptr [edi + 0x294], xmm2
0045d4fb mov eax, dword ptr [edi + 0x290]
0045d501 mov dword ptr [edi + 0x298], eax
0045d507 lea ecx, [edi + 0x3c]
0045d50a push 0xb4034c
0045d50f call 0x406150
0045d514 push 0xc02fec
0045d519 mov ecx, esi
0045d51b mov byte ptr [ebp - 0x192], al
0045d521 call 0x962ca0
0045d526 test al, al
0045d528 je 0x45d6fb
0045d52e cmp byte ptr [ebp - 0x192], 0
0045d535 jne 0x45d6fb
0045d53b cmp dword ptr [ebp - 0x1a4], -1
0045d542 mov dword ptr [edi + 0x180], 0
0045d54c mov dword ptr [edi + 0x17c], 3
0045d556 je 0x45d625
0045d55c lea ecx, [ebp - 0x1c4]
0045d562 push ecx
0045d563 lea ecx, [edi + 0x2b8]
0045d569 call 0x962560
0045d56e movss xmm0, dword ptr [ebp - 0x1a8]
0045d576 lea ecx, [edi + 0x2b8]
0045d57c movss xmm1, dword ptr [ebp - 0x1ac]
0045d584 push 0xc02fec
0045d589 mulss xmm0, dword ptr [eax + 4]
0045d58e mulss xmm1, dword ptr [eax]
0045d592 addss xmm0, xmm1
0045d596 andps xmm0, xmmword ptr [0xb6c980]
0045d59d mulss xmm0, dword ptr [0xb6a66c]
0045d5a5 addss xmm0, dword ptr [0xb6a2cc]
0045d5ad movss dword ptr [ebp - 0x1a8], xmm0
0045d5b5 call 0x962c70
0045d5ba test al, al
0045d5bc je 0x45d5ce
0045d5be movss xmm0, dword ptr [0xb6a690]
0045d5c6 movss dword ptr [ebp - 0x1a8], xmm0
0045d5ce lea eax, [ebp - 0x1c4]
0045d5d4 push eax
0045d5d5 lea ecx, [ebp - 0x19c]
0045d5db call 0x962560
0045d5e0 movss xmm4, dword ptr [edi + 0x2c4]
0045d5e8 ucomiss xmm4, dword ptr [0xb6a18c]
0045d5ef movss xmm2, dword ptr [ebp - 0x1a8]
0045d5f7 movaps xmm3, xmm2
0045d5fa mulss xmm2, dword ptr [eax + 4]
0045d5ff mulss xmm3, dword ptr [eax]
0045d603 lahf 
0045d604 test ah, 0x44
0045d607 jnp 0x45d713
0045d60d movss xmm1, dword ptr [edi + 0x2f4]
0045d615 movaps xmm0, xmm1
0045d618 mulss xmm1, xmm2
0045d61c mulss xmm0, xmm3
0045d620 jmp 0x45d6d1
0045d625 movss xmm1, dword ptr [esi]
0045d629 lea eax, [ebp - 0x1c4]
0045d62f movss xmm2, dword ptr [esi + 4]
0045d634 lea ecx, [ebp - 0x19c]
0045d63a subss xmm1, dword ptr [edi + 0x294]
0045d642 subss xmm2, dword ptr [edi + 0x298]
0045d64a push eax
0045d64b movss dword ptr [ebp - 0x19c], xmm1
0045d653 mulss xmm1, dword ptr [0xb6a200]
0045d65b movss dword ptr [ebp - 0x198], xmm2
0045d663 mulss xmm2, dword ptr [0xb6a200]
0045d66b movss dword ptr [ebp - 0x1b0], xmm1
0045d673 movss dword ptr [ebp - 0x1a0], xmm2
0045d67b call 0x962560
0045d680 movss xmm4, dword ptr [edi + 0x2c4]
0045d688 ucomiss xmm4, dword ptr [0xb6a18c]
0045d68f movss xmm2, dword ptr [eax]
0045d693 movss xmm3, dword ptr [eax + 4]
0045d698 mulss xmm2, dword ptr [0xb6a3b0]
0045d6a0 mulss xmm3, dword ptr [0xb6a3b0]
0045d6a8 addss xmm2, dword ptr [ebp - 0x1b0]
0045d6b0 lahf 
0045d6b1 addss xmm3, dword ptr [ebp - 0x1a0]
0045d6b9 test ah, 0x44
0045d6bc jnp 0x45d713
0045d6be movss xmm1, dword ptr [edi + 0x2f4]
0045d6c6 movaps xmm0, xmm1
0045d6c9 mulss xmm1, xmm3
0045d6cd mulss xmm0, xmm2
0045d6d1 divss xmm0, xmm4
0045d6d5 divss xmm1, xmm4
0045d6d9 addss xmm0, dword ptr [edi + 0x2b8]
0045d6e1 movss dword ptr [edi + 0x2b8], xmm0
0045d6e9 addss xmm1, dword ptr [edi + 0x2bc]
0045d6f1 movss dword ptr [edi + 0x2bc], xmm1
0045d6f9 jmp 0x45d713
0045d6fb movss xmm0, dword ptr [edi + 0x2c4]
0045d703 mulss xmm0, dword ptr [0xb6a560]
0045d70b movss dword ptr [edi + 0x2c4], xmm0
0045d713 cmp dword ptr [edi + 0x70], 0
0045d717 je 0x45dcaf
0045d71d cmp byte ptr [edi + 0x80], 0
0045d724 je 0x45dcaf
0045d72a cmp byte ptr [ebp - 0x192], 0
0045d731 je 0x45d24b
0045d737 push 0xb4034c
0045d73c lea ecx, [edi + 0x3c]
0045d73f mov dword ptr [edi + 0x180], 4
0045d749 mov dword ptr [edi + 0x17c], 5
0045d753 call 0x4060f0
0045d758 test al, al
0045d75a je 0x45d84e
0045d760 push ecx
0045d761 mov dword ptr [esp], 0x3f800000
0045d768 push 0
0045d76a push 2
0045d76c push ecx
0045d76d mov dword ptr [esp], 0x3f800000
0045d774 mov ecx, edi
0045d776 push 0x30
0045d778 call 0x6ad720
0045d77d lea ecx, [ebp - 0x1f0]
0045d783 call 0x447ea0
0045d788 mov ecx, dword ptr [0xbfd65c]
0045d78e lea edx, [ebp - 0x1f0]
0045d794 movss xmm0, dword ptr [edi + 0x294]
0045d79c movss dword ptr [ebp - 0x1f0], xmm0
0045d7a4 movss xmm0, dword ptr [edi + 0x298]
0045d7ac mov eax, dword ptr [ecx + 0x18190]
0045d7b2 mov dword ptr [ebp - 0x1d8], 0xa
0045d7bc mov dword ptr [ebp - 0x1e0], 0x3ccccccd
0045d7c6 mov dword ptr [ebp - 0x1e4], 0x3d0f5c29
0045d7d0 inc dword ptr [eax + 0x6ff0]
0045d7d6 mov eax, dword ptr [eax + 0x6ff0]
0045d7dc movss dword ptr [ebp - 0x1ec], xmm0
0045d7e4 push edx
0045d7e5 and eax, 0x80000001
0045d7ea jns 0x45d7f1
0045d7ec dec eax
0045d7ed or eax, 0xfffffffe
0045d7f0 inc eax
0045d7f1 mov ecx, dword ptr [ecx + 0x18190]
0045d7f7 push eax
0045d7f8 call 0x7d9090
0045d7fd lea ecx, [ebp - 0x40]
0045d800 call 0x402120
0045d805 cmp dword ptr [edi + 0x28], 0x2b
0045d809 jne 0x45d829
0045d80b cmp dword ptr [edi + 0x2c], 1
0045d80f jne 0x45d829
0045d811 movaps xmm0, xmmword ptr [0xb6c830]
0045d818 movups xmmword ptr [ebp - 0x40], xmm0
0045d81c movaps xmm0, xmmword ptr [0xb6bf00]
0045d823 movups xmmword ptr [ebp - 0x30], xmm0
0045d827 jmp 0x45d834
0045d829 movaps xmm0, xmmword ptr [0xb6c610]
0045d830 movups xmmword ptr [ebp - 0x40], xmm0
0045d834 movss xmm2, dword ptr [0xb6a614]
0045d83c lea eax, [ebp - 0x40]
0045d83f push eax
0045d840 lea eax, [edi + 0x294]
0045d846 mov ecx, edi
0045d848 push eax
0045d849 call 0x68d9a0
0045d84e push 0xb400ac
0045d853 lea ecx, [edi + 0x3c]
0045d856 call 0x4060f0
0045d85b test al, al
0045d85d je 0x45d24b
0045d863 mov eax, dword ptr [edi + 0x28]
0045d866 cmp eax, 0x14
0045d869 jne 0x45d892
0045d86b lea ecx, [ebp - 0x190]
0045d871 call 0x430d70
0045d876 push eax
0045d877 push ecx
0045d878 mov dword ptr [esp], 0
0045d87f mov ecx, edi
0045d881 push 0xc02fec
0045d886 push 0x12
0045d888 call 0x6a3420
0045d88d jmp 0x45d24b
0045d892 cmp eax, 0x2b
0045d895 jne 0x45d24b
0045d89b mov eax, dword ptr [edi + 0xb10]
0045d8a1 test eax, eax
0045d8a3 jne 0x45d9d1
0045d8a9 mov eax, dword ptr [edi + 0x2c]
0045d8ac cmp eax, 1
0045d8af jne 0x45d97d
0045d8b5 call 0x6c3d90
0045d8ba mov ecx, dword ptr [0xbfd65c]
0045d8c0 push 0
0045d8c2 push 0xbeaaec
0045d8c7 push 0xbeab18
0045d8cc push 0
0045d8ce push eax
0045d8cf push 0
0045d8d1 push edi
0045d8d2 push 0xc02fec
0045d8d7 lea eax, [edi + 0x294]
0045d8dd push eax
0045d8de push 0x1a
0045d8e0 push 0x3e8
0045d8e5 call 0x422e20
0045d8ea push eax
0045d8eb call 0x9ec34c
0045d8f0 mov esi, eax
0045d8f2 add esp, 0x14
0045d8f5 mov ecx, dword ptr [esi + 0x314]
0045d8fb lea eax, [esi + 0x314]
0045d901 test ecx, ecx
0045d903 je 0x45d923
0045d905 mov dword ptr [ebp - 0x1b0], eax
0045d90b add ecx, 0x324
0045d911 lea eax, [ebp - 0x1b0]
0045d917 push eax
0045d918 call 0x4bc3c0
0045d91d lea eax, [esi + 0x314]
0045d923 push eax
0045d924 mov ecx, edi
0045d926 mov dword ptr [eax], edi
0045d928 call 0x4bae70
0045d92d movss xmm2, dword ptr [0xbc7a28]
0045d935 mov ecx, esi
0045d937 movss xmm1, dword ptr [0xbc7a2c]
0045d93f mulss xmm2, dword ptr [0xb6a864]
0045d947 mov eax, dword ptr [esi]
0045d949 mulss xmm1, dword ptr [0xb6a864]
0045d951 mov dword ptr [esi + 0x3ac], 0
0045d95b movss dword ptr [esi + 0xd8], xmm2
0045d963 mov dword ptr [esi + 0x3b0], 0
0045d96d movss dword ptr [esi + 0xdc], xmm1
0045d975 call dword ptr [eax + 0xc]
0045d978 jmp 0x45d24b
0045d97d test eax, eax
0045d97f jne 0x45d24b
0045d985 lea ecx, [ebp - 0xe8]
0045d98b call 0x430d70
0045d990 lea eax, [ebp - 0xe8]
0045d996 mov dword ptr [ebp - 0xd4], 0x3fb33333
0045d9a0 push eax
0045d9a1 push 8
0045d9a3 lea eax, [ebp - 0x19c]
0045d9a9 mov dword ptr [ebp - 0x19c], 0x41200000
0045d9b3 push eax
0045d9b4 lea eax, [edi + 0x294]
0045d9ba mov dword ptr [ebp - 0x198], 0
0045d9c4 push eax
0045d9c5 mov ecx, edi
0045d9c7 call 0x6a1a20
0045d9cc jmp 0x45d24b
0045d9d1 cmp eax, 1
0045d9d4 jne 0x45d24b
0045d9da mov eax, dword ptr [edi + 0x2c]
0045d9dd cmp eax, 1
0045d9e0 jne 0x45db42
0045d9e6 mov esi, dword ptr [0xbfd65c]
0045d9ec mov eax, dword ptr [esi + 0x18190]
0045d9f2 mov ecx, dword ptr [eax + 0x12c4]
0045d9f8 mov eax, dword ptr [eax + 0x12c0]
0045d9fe add ecx, eax
0045da00 xor eax, eax
0045da02 test ecx, ecx
0045da04 cmovg eax, ecx
0045da07 cmp eax, 3
0045da0a jge 0x45d24b
0045da10 mov dword ptr [ebp - 0x19c], 0x40a00000
0045da1a mov dword ptr [ebp - 0x198], 0
0045da24 call 0x6c3d90
0045da29 push 0
0045da2b push 0xbeab70
0045da30 push 0xbeab18
0045da35 push 0
0045da37 push eax
0045da38 push 0
0045da3a push edi
0045da3b lea eax, [ebp - 0x19c]
0045da41 push eax
0045da42 lea ecx, [edi + 0x294]
0045da48 push ecx
0045da49 push 1
0045da4b push 0xf
0045da4d mov ecx, esi
0045da4f call 0x422e20
0045da54 push eax
0045da55 call 0x9ec34c
0045da5a add esp, 0x14
0045da5d movss xmm0, dword ptr [eax + 0x2d8]
0045da65 subss xmm0, dword ptr [0xb6a8f4]
0045da6d movss dword ptr [eax + 0x2d8], xmm0
0045da75 mov eax, dword ptr [0xbfd65c]
0045da7a mov eax, dword ptr [eax + 0x18190]
0045da80 mov ecx, dword ptr [eax + 0x12c4]
0045da86 mov eax, dword ptr [eax + 0x12c0]
0045da8c add ecx, eax
0045da8e push ecx
0045da8f xor eax, eax
0045da91 mov dword ptr [esp], 0x3f800000
0045da98 test ecx, ecx
0045da9a push 0
0045da9c cmovg eax, ecx
0045da9f push 2
0045daa1 push ecx
0045daa2 mov ecx, edi
0045daa4 cmp eax, 3
0045daa7 jge 0x45db2c
0045daad mov dword ptr [esp], 0x3fc00000
0045dab4 push 0x109
0045dab9 call 0x6ad720
0045dabe call 0x6c3d90
0045dac3 mov ecx, dword ptr [0xbfd65c]
0045dac9 push 0
0045dacb push 0xbeab70
0045dad0 push 0xbeab18
0045dad5 push 0
0045dad7 push eax
0045dad8 push 0
0045dada push edi
0045dadb lea eax, [ebp - 0x19c]
0045dae1 mov dword ptr [ebp - 0x19c], 0xc0a00000
0045daeb push eax
0045daec lea eax, [edi + 0x294]
0045daf2 mov dword ptr [ebp - 0x198], 0x80000000
0045dafc push eax
0045dafd push 1
0045daff push 0xf
0045db01 call 0x422e20
0045db06 push eax
0045db07 call 0x9ec34c
0045db0c add esp, 0x14
0045db0f movss xmm0, dword ptr [eax + 0x2d8]
0045db17 subss xmm0, dword ptr [0xb6a8f4]
0045db1f movss dword ptr [eax + 0x2d8], xmm0
0045db27 jmp 0x45d24b
0045db2c mov dword ptr [esp], 0x3f800000
0045db33 push 0x109
0045db38 call 0x6ad720
0045db3d jmp 0x45d24b
0045db42 test eax, eax
0045db44 jne 0x45d24b
0045db4a mov eax, dword ptr [0xbfd65c]
0045db4f mov eax, dword ptr [eax + 0x18190]
0045db55 mov ecx, dword ptr [eax + 0x12c4]
0045db5b mov eax, dword ptr [eax + 0x12c0]
0045db61 add eax, ecx
0045db63 xor ecx, ecx
0045db65 test eax, eax
0045db67 cmovg ecx, eax
0045db6a cmp ecx, 5
0045db6d jge 0x45d24b
0045db73 cmp dword ptr [edi + 0x28], 0x2b
0045db77 mov dword ptr [ebp - 0x1a0], 4
0045db81 jne 0x45db9d
0045db83 cmp dword ptr [edi + 0x30], 1
0045db87 jne 0x45db9d
0045db89 movss xmm0, dword ptr [0xb6a614]
0045db91 mov dword ptr [ebp - 0x1a0], 2
0045db9b jmp 0x45dba5
0045db9d movss xmm0, dword ptr [0xb6a6f0]
0045dba5 push ecx
0045dba6 mov dword ptr [esp], 0x3f800000
0045dbad push 0
0045dbaf push 2
0045dbb1 push ecx
0045dbb2 movss dword ptr [esp], xmm0
0045dbb7 mov ecx, edi
0045dbb9 push 0x109
0045dbbe call 0x6ad720
0045dbc3 mov dword ptr [ebp - 0x1b0], 0xbe9968
0045dbcd nop dword ptr [eax]
0045dbd0 call 0x6c3d90
0045dbd5 mov esi, eax
0045dbd7 call 0x6c3d90
0045dbdc movd xmm0, eax
0045dbe0 cvtdq2pd xmm0, xmm0
0045dbe4 shr eax, 0x1f
0045dbe7 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
0045dbf0 cvtpd2ps xmm1, xmm0
0045dbf4 mulss xmm1, dword ptr [0xb6a19c]
0045dbfc mulss xmm1, dword ptr [0xb6a874]
0045dc04 addss xmm1, xmm1
0045dc08 movaps xmm0, xmm1
0045dc0b movss dword ptr [ebp - 0x1b8], xmm1
0045dc13 call 0x411fe0
0045dc18 mulss xmm0, dword ptr [edi + 0x2c8]
0045dc20 addss xmm0, dword ptr [edi + 0x294]
0045dc28 movss dword ptr [ebp - 0x1cc], xmm0
0045dc30 movss xmm0, dword ptr [ebp - 0x1b8]
0045dc38 call 0x412010
0045dc3d mulss xmm0, dword ptr [edi + 0x2c8]
0045dc45 lea eax, [ebp - 0x1cc]
0045dc4b mov ecx, dword ptr [0xbfd65c]
0045dc51 push 0
0045dc53 push 0xbeab70
0045dc58 addss xmm0, dword ptr [edi + 0x298]
0045dc60 push 0xbeab18
0045dc65 push 0
0045dc67 push esi
0045dc68 mov esi, dword ptr [ebp - 0x1b0]
0045dc6e push 0
0045dc70 push edi
0045dc71 push esi
0045dc72 push eax
0045dc73 push 0
0045dc75 push 0x3d
0045dc77 movss dword ptr [ebp - 0x1c8], xmm0
0045dc7f call 0x422e20
0045dc84 push eax
0045dc85 call 0x9ec34c
0045dc8a add esi, 8
0045dc8d add esp, 0x14
0045dc90 sub dword ptr [ebp - 0x1a0], 1
0045dc97 mov dword ptr [ebp - 0x1b0], esi
0045dc9d mov byte ptr [eax + 0x16c], 1
0045dca4 jne 0x45dbd0
0045dcaa jmp 0x45d24b
0045dcaf movss xmm0, dword ptr [0xc02fec]
0045dcb7 movss dword ptr [esi], xmm0
0045dcbb movss xmm0, dword ptr [0xc02ff0]
0045dcc3 movss dword ptr [esi + 4], xmm0
0045dcc8 mov ecx, dword ptr [edi + 0xb10]
0045dcce cmp ecx, 2
0045dcd1 jne 0x45dcdf
0045dcd3 mov dword ptr [edi + 0xb10], 0
0045dcdd xor ecx, ecx
0045dcdf cmp dword ptr [edi + 0x28], 0x2b
0045dce3 jne 0x45dcee
0045dce5 xor ecx, 1
0045dce8 mov dword ptr [edi + 0xb10], ecx
0045dcee test ecx, ecx
0045dcf0 mov eax, 6
0045dcf5 mov edx, 3
0045dcfa cmove eax, edx
0045dcfd mov dword ptr [edi + 0xab4], eax
0045dd03 je 0x45d241
0045dd09 push 0
0045dd0b push 0xb408a0
0045dd10 lea ecx, [edi + 0x3c]
0045dd13 call 0x4054f0
0045dd18 cmp dword ptr [edi + 0x28], 0x2b
0045dd1c jne 0x45d24b
0045dd22 cmp dword ptr [edi + 0x30], 1
0045dd26 jne 0x45d24b
0045dd2c mov dword ptr [edi + 0x140], 0x3fc00000
0045dd36 jmp 0x45d24b
