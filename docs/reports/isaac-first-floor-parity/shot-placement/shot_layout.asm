0074aef0 push ebp
0074aef1 mov ebp, esp
0074aef3 and esp, 0xfffffff8
0074aef6 sub esp, 0x20
0074aef9 mov ecx, dword ptr [ebp + 0xc]
0074aefc mov eax, ecx
0074aefe cdq 
0074aeff idiv dword ptr [ebp + 0x34]
0074af02 movss xmm0, dword ptr [ebp + 0x24]
0074af07 push esi
0074af08 push edi
0074af09 mov edi, dword ptr [ebp + 0x10]
0074af0c mov dword ptr [esp + 0x20], edx
0074af10 mov dword ptr [esp + 0x18], eax
0074af14 movss dword ptr [esp + 0xc], xmm0
0074af1a cmp edi, 3
0074af1d je 0x74af50
0074af1f cmp edi, 2
0074af22 je 0x74af50
0074af24 cmp edi, 9
0074af27 jne 0x74af30
0074af29 movss xmm0, dword ptr [ebp + 0x2c]
0074af2e jmp 0x74af55
0074af30 cmp edi, 4
0074af33 jne 0x74af3c
0074af35 movss xmm0, dword ptr [ebp + 0x30]
0074af3a jmp 0x74af55
0074af3c cmp edi, 0xa
0074af3f jne 0x74af5b
0074af41 movss xmm0, dword ptr [ebp + 0x30]
0074af46 mulss xmm0, dword ptr [0xb6a864]
0074af4e jmp 0x74af55
0074af50 movss xmm0, dword ptr [ebp + 0x28]
0074af55 movss dword ptr [esp + 0xc], xmm0
0074af5b cmp byte ptr [ebp + 0x3c], 0
0074af5f mov esi, dword ptr [ebp + 8]
0074af62 mov dword ptr [esi + 4], 0
0074af69 mov dword ptr [esi], 0
0074af6f mov dword ptr [esi + 0xc], 0
0074af76 mov dword ptr [esi + 8], 0
0074af7d je 0x74b024
0074af83 movsx edx, word ptr [ebp + 0x20]
0074af87 lea eax, [edx - 2]
0074af8a cmp ecx, eax
0074af8c jl 0x74b024
0074af92 lea eax, [edx - 1]
0074af95 cmp ecx, eax
0074af97 jne 0x74afb6
0074af99 movss xmm0, dword ptr [0xb6a554]
0074afa1 call 0x411fe0
0074afa6 movss dword ptr [esp + 0x1c], xmm0
0074afac movss xmm0, dword ptr [0xb6a554]
0074afb4 jmp 0x74afd1
0074afb6 movss xmm0, dword ptr [0xb6ae3c]
0074afbe call 0x411fe0
0074afc3 movss dword ptr [esp + 0x1c], xmm0
0074afc9 movss xmm0, dword ptr [0xb6ae3c]
0074afd1 call 0x412010
0074afd6 movss xmm2, dword ptr [ebp + 0x18]
0074afdb mov eax, esi
0074afdd movss xmm4, dword ptr [ebp + 0x14]
0074afe2 movaps xmm1, xmm2
0074afe5 mulss xmm1, dword ptr [esp + 0x1c]
0074afeb movaps xmm5, xmm4
0074afee mulss xmm4, dword ptr [esp + 0x1c]
0074aff4 mulss xmm2, xmm0
0074aff8 mulss xmm5, xmm0
0074affc subss xmm4, xmm2
0074b000 addss xmm5, xmm1
0074b004 movss xmm1, dword ptr [ebp + 0x1c]
0074b009 movaps xmm0, xmm1
0074b00c mulss xmm1, xmm4
0074b010 mulss xmm0, xmm5
0074b014 movss dword ptr [esi + 8], xmm1
0074b019 movss dword ptr [esi + 0xc], xmm0
0074b01e pop edi
0074b01f pop esi
0074b020 mov esp, ebp
0074b022 pop ebp
0074b023 ret 
0074b024 movss xmm0, dword ptr [ebp + 0x14]
0074b029 xorps xmm2, xmm2
0074b02c mov eax, dword ptr [ebp + 0x34]
0074b02f xorps xmm1, xmm1
0074b032 movss dword ptr [esp + 0x24], xmm0
0074b038 movss xmm0, dword ptr [ebp + 0x18]
0074b03d movss dword ptr [esp + 0x10], xmm0
0074b043 cmp eax, 1
0074b046 jle 0x74b0fa
0074b04c movss xmm1, dword ptr [ebp + 0x38]
0074b051 movd xmm3, eax
0074b055 movaps xmm4, xmm1
0074b058 xorps xmm4, xmmword ptr [0xb6c9b0]
0074b05f cvtdq2ps xmm3, xmm3
0074b062 movss dword ptr [esp + 0x14], xmm4
0074b068 subss xmm3, dword ptr [0xb6a614]
0074b070 ucomiss xmm2, xmm3
0074b073 movss dword ptr [esp + 0x1c], xmm3
0074b079 lahf 
0074b07a test ah, 0x44
0074b07d jp 0x74b0a2
0074b07f push 0xb5d590
0074b084 push 3
0074b086 call 0x95e330
0074b08b movss xmm1, dword ptr [ebp + 0x38]
0074b090 add esp, 8
0074b093 movss xmm3, dword ptr [esp + 0x1c]
0074b099 xorps xmm2, xmm2
0074b09c movss xmm4, dword ptr [esp + 0x14]
0074b0a2 xorps xmm0, xmm0
0074b0a5 subss xmm3, xmm2
0074b0a9 cvtsi2ss xmm0, dword ptr [esp + 0x20]
0074b0af lea eax, [esp + 0x20]
0074b0b3 mov dword ptr [esp + 0x20], 0
0074b0bb lea ecx, [esp + 0x1c]
0074b0bf subss xmm0, xmm2
0074b0c3 divss xmm0, xmm3
0074b0c7 comiss xmm2, xmm0
0074b0ca movss xmm2, dword ptr [0xb6a614]
0074b0d2 movss dword ptr [esp + 0x1c], xmm0
0074b0d8 cmovbe eax, ecx
0074b0db movss xmm0, dword ptr [eax]
0074b0df comiss xmm0, xmm2
0074b0e2 ja 0x74b0ea
0074b0e4 movss xmm0, xmm0
0074b0e8 jmp 0x74b0ee
0074b0ea movss xmm0, xmm2
0074b0ee subss xmm1, xmm4
0074b0f2 mulss xmm1, xmm0
0074b0f6 addss xmm1, xmm4
0074b0fa mulss xmm1, dword ptr [0xb6a230]
0074b102 movaps xmm0, xmm1
0074b105 movss dword ptr [esp + 0x20], xmm1
0074b10b call 0x411fe0
0074b110 movss dword ptr [esp + 0x1c], xmm0
0074b116 movss xmm0, dword ptr [esp + 0x20]
0074b11c call 0x412010
0074b121 movss xmm3, dword ptr [esp + 0x10]
0074b127 movss xmm5, dword ptr [esp + 0x24]
0074b12d movaps xmm1, xmm3
0074b130 movss xmm2, dword ptr [esp + 0x1c]
0074b136 movaps xmm4, xmm5
0074b139 mov ax, word ptr [ebp + 0x22]
0074b13d mulss xmm1, xmm0
0074b141 mulss xmm5, xmm0
0074b145 mulss xmm4, xmm2
0074b149 mulss xmm3, xmm2
0074b14d subss xmm4, xmm1
0074b151 addss xmm3, xmm5
0074b155 movss dword ptr [esp + 0x1c], xmm4
0074b15b movaps xmm1, xmm4
0074b15e mulss xmm1, dword ptr [ebp + 0x1c]
0074b163 movss dword ptr [esp + 0x10], xmm3
0074b169 movaps xmm0, xmm3
0074b16c mulss xmm0, dword ptr [ebp + 0x1c]
0074b171 movss dword ptr [esi + 8], xmm1
0074b176 movss dword ptr [esi + 0xc], xmm0
0074b17b cmp ax, 1
0074b17f jle 0x74b432
0074b185 cmp edi, 1
0074b188 je 0x74b198
0074b18a cmp edi, 9
0074b18d je 0x74b198
0074b18f cmp edi, 5
0074b192 jne 0x74b325
0074b198 cwde 
0074b199 xorps xmm1, xmm1
0074b19c movd xmm2, eax
0074b1a0 cvtdq2ps xmm2, xmm2
0074b1a3 subss xmm2, dword ptr [0xb6a614]
0074b1ab ucomiss xmm1, xmm2
0074b1ae movss dword ptr [esp + 0x24], xmm2
0074b1b4 lahf 
0074b1b5 test ah, 0x44
0074b1b8 jp 0x74b1de
0074b1ba push 0xb5d590
0074b1bf push 3
0074b1c1 call 0x95e330
0074b1c6 movss xmm3, dword ptr [esp + 0x18]
0074b1cc add esp, 8
0074b1cf movss xmm2, dword ptr [esp + 0x24]
0074b1d5 xorps xmm1, xmm1
0074b1d8 movss xmm4, dword ptr [esp + 0x1c]
0074b1de mov edi, dword ptr [esp + 0x18]
0074b1e2 subss xmm2, xmm1
0074b1e6 lea eax, [esp + 0x24]
0074b1ea mov dword ptr [esp + 0x24], 0
0074b1f2 lea ecx, [esp + 0x20]
0074b1f6 movd xmm0, edi
0074b1fa cvtdq2ps xmm0, xmm0
0074b1fd subss xmm0, xmm1
0074b201 divss xmm0, xmm2
0074b205 comiss xmm1, xmm0
0074b208 movss xmm1, dword ptr [0xb6a614]
0074b210 movss dword ptr [esp + 0x20], xmm0
0074b216 cmovbe eax, ecx
0074b219 movss xmm0, dword ptr [eax]
0074b21d comiss xmm0, xmm1
0074b220 ja 0x74b228
0074b222 movss xmm0, xmm0
0074b226 jmp 0x74b22c
0074b228 movss xmm0, xmm1
0074b22c movss dword ptr [esp + 0x14], xmm0
0074b232 movaps xmm1, xmm4
0074b235 movaps xmm0, xmm3
0074b238 mulss xmm1, xmm4
0074b23c mulss xmm0, xmm3
0074b240 addss xmm0, xmm1
0074b244 call 0x4228c0
0074b249 movss dword ptr [esp + 0x18], xmm0
0074b24f movss xmm0, dword ptr [esp + 0x14]
0074b255 mulss xmm0, dword ptr [0xb6ab88]
0074b25d subss xmm0, dword ptr [0xb6aae4]
0074b265 mulss xmm0, dword ptr [0xb6a230]
0074b26d movss dword ptr [esp + 0x14], xmm0
0074b273 call 0x411fe0
0074b278 mulss xmm0, dword ptr [0xb6a660]
0074b280 mulss xmm0, dword ptr [esp + 0x18]
0074b286 movss dword ptr [esp + 0x20], xmm0
0074b28c movss xmm0, dword ptr [esp + 0x14]
0074b292 call 0x412010
0074b297 mulss xmm0, dword ptr [0xb6a560]
0074b29f movss xmm1, dword ptr [esp + 0x1c]
0074b2a5 mulss xmm0, dword ptr [esp + 0x18]
0074b2ab movss dword ptr [esp + 0x18], xmm0
0074b2b1 movss xmm0, dword ptr [esp + 0x10]
0074b2b7 call 0x447a80
0074b2bc mulss xmm0, dword ptr [0xb6aa84]
0074b2c4 mulss xmm0, dword ptr [0xb6a230]
0074b2cc movss dword ptr [esp + 0x24], xmm0
0074b2d2 call 0x411fe0
0074b2d7 movss dword ptr [esp + 0x1c], xmm0
0074b2dd movss xmm0, dword ptr [esp + 0x24]
0074b2e3 call 0x412010
0074b2e8 movss xmm5, dword ptr [esp + 0x20]
0074b2ee movss xmm4, dword ptr [esp + 0x18]
0074b2f4 movaps xmm3, xmm5
0074b2f7 mulss xmm3, dword ptr [esp + 0x1c]
0074b2fd movaps xmm1, xmm4
0074b300 mov ax, word ptr [ebp + 0x22]
0074b304 mulss xmm4, dword ptr [esp + 0x1c]
0074b30a mulss xmm1, xmm0
0074b30e mulss xmm5, xmm0
0074b312 subss xmm3, xmm1
0074b316 addss xmm4, xmm5
0074b31a movss dword ptr [esi], xmm3
0074b31e movss dword ptr [esi + 4], xmm4
0074b323 jmp 0x74b329
0074b325 mov edi, dword ptr [esp + 0x18]
0074b329 movss xmm3, dword ptr [esp + 0xc]
0074b32f xorps xmm1, xmm1
0074b332 cwde 
0074b333 xorps xmm3, xmmword ptr [0xb6c9b0]
0074b33a movss dword ptr [esp + 0x20], xmm3
0074b340 movd xmm2, eax
0074b344 cvtdq2ps xmm2, xmm2
0074b347 subss xmm2, dword ptr [0xb6a614]
0074b34f ucomiss xmm1, xmm2
0074b352 movss dword ptr [esp + 0x24], xmm2
0074b358 lahf 
0074b359 test ah, 0x44
0074b35c jp 0x74b37c
0074b35e push 0xb5d590
0074b363 push 3
0074b365 call 0x95e330
0074b36a movss xmm2, dword ptr [esp + 0x2c]
0074b370 add esp, 8
0074b373 movss xmm3, dword ptr [esp + 0x20]
0074b379 xorps xmm1, xmm1
0074b37c movd xmm0, edi
0074b380 subss xmm2, xmm1
0074b384 cvtdq2ps xmm0, xmm0
0074b387 lea eax, [esp + 0x24]
0074b38b mov dword ptr [esp + 0x24], 0
0074b393 lea ecx, [esp + 0x20]
0074b397 subss xmm0, xmm1
0074b39b divss xmm0, xmm2
0074b39f comiss xmm1, xmm0
0074b3a2 movss xmm1, dword ptr [0xb6a614]
0074b3aa movss dword ptr [esp + 0x20], xmm0
0074b3b0 cmovbe eax, ecx
0074b3b3 movss xmm0, dword ptr [eax]
0074b3b7 comiss xmm0, xmm1
0074b3ba ja 0x74b3c2
0074b3bc movss xmm1, xmm0
0074b3c0 jmp 0x74b3c6
0074b3c2 movss xmm1, xmm1
0074b3c6 movss xmm0, dword ptr [esp + 0xc]
0074b3cc subss xmm0, xmm3
0074b3d0 mulss xmm0, xmm1
0074b3d4 addss xmm0, xmm3
0074b3d8 mulss xmm0, dword ptr [0xb6a230]
0074b3e0 movss dword ptr [esp + 0xc], xmm0
0074b3e6 call 0x411fe0
0074b3eb movss dword ptr [esp + 0x24], xmm0
0074b3f1 movss xmm0, dword ptr [esp + 0xc]
0074b3f7 call 0x412010
0074b3fc movss xmm3, dword ptr [esi + 8]
0074b401 movss xmm5, dword ptr [esi + 0xc]
0074b406 movaps xmm2, xmm3
0074b409 mulss xmm2, dword ptr [esp + 0x24]
0074b40f movaps xmm1, xmm5
0074b412 mulss xmm5, dword ptr [esp + 0x24]
0074b418 mulss xmm1, xmm0
0074b41c mulss xmm3, xmm0
0074b420 subss xmm2, xmm1
0074b424 addss xmm5, xmm3
0074b428 movss dword ptr [esi + 8], xmm2
0074b42d movss dword ptr [esi + 0xc], xmm5
0074b432 pop edi
0074b433 mov eax, esi
0074b435 pop esi
0074b436 mov esp, ebp
0074b438 pop ebp
0074b439 ret 
