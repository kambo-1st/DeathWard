0051afa0 push ebx
0051afa1 mov ebx, esp
0051afa3 sub esp, 8
0051afa6 and esp, 0xfffffff8
0051afa9 add esp, 4
0051afac push ebp
0051afad mov ebp, dword ptr [ebx + 4]
0051afb0 mov dword ptr [esp + 4], ebp
0051afb4 mov ebp, esp
0051afb6 push -1
0051afb8 push 0x9ef715
0051afbd mov eax, dword ptr fs:[0]
0051afc3 push eax
0051afc4 push ebx
0051afc5 sub esp, 0x288
0051afcb mov eax, dword ptr [0xbaa3b4]
0051afd0 xor eax, ebp
0051afd2 mov dword ptr [ebp - 0x14], eax
0051afd5 push esi
0051afd6 push edi
0051afd7 push eax
0051afd8 lea eax, [ebp - 0xc]
0051afdb mov dword ptr fs:[0], eax
0051afe1 mov edi, ecx
0051afe3 mov dword ptr [ebp - 0x240], edi
0051afe9 mov eax, dword ptr [edi + 0x28]
0051afec cmp eax, 0x17
0051afef jne 0x51b006
0051aff1 cmp dword ptr [edi + 0x2c], 0
0051aff5 jne 0x51b006
0051aff7 cmp dword ptr [edi + 0x30], 1
0051affb jne 0x51b006
0051affd mov byte ptr [ebp - 0x231], 1
0051b004 jmp 0x51b037
0051b006 mov byte ptr [ebp - 0x231], 0
0051b00d cmp eax, 0x37
0051b010 jne 0x51b037
0051b012 cmp dword ptr [edi + 0x2c], 0
0051b016 je 0x51b037
0051b018 mov eax, dword ptr [edi + 0xe6c]
0051b01e cmp eax, -1
0051b021 je 0x51b037
0051b023 push edi
0051b024 push eax
0051b025 push 8
0051b027 call 0x8b10b0
0051b02c test al, al
0051b02e je 0x51b037
0051b030 mov eax, dword ptr [edi]
0051b032 mov ecx, edi
0051b034 call dword ptr [eax + 0x24]
0051b037 cmp byte ptr [edi + 0x16b], 0
0051b03e movss xmm1, dword ptr [0xb6a940]
0051b046 movss xmm2, dword ptr [0xb6a974]
0051b04e je 0x51b11a
0051b054 mov eax, dword ptr [edi + 0x28]
0051b057 cmp eax, 0x37
0051b05a jne 0x51b0c6
0051b05c cmp dword ptr [edi + 0x2c], 0
0051b060 je 0x51b11a
0051b066 movups xmm0, xmmword ptr [0xbfec58]
0051b06d mov ecx, dword ptr [0xbfd65c]
0051b073 lea esi, [edi + 0x294]
0051b079 push 0
0051b07b push 0
0051b07d push 4
0051b07f sub esp, 0x10
0051b082 mov eax, esp
0051b084 push edi
0051b085 push 1
0051b087 sub esp, 8
0051b08a movups xmmword ptr [eax], xmm0
0051b08d mov dword ptr [esp + 4], 0x42700000
0051b095 mov dword ptr [esp], 0x42200000
0051b09c push esi
0051b09d call 0x6d1750
0051b0a2 call 0x6c3d90
0051b0a7 mov ecx, dword ptr [0xbfd65c]
0051b0ad push eax
0051b0ae push 0
0051b0b0 push 0
0051b0b2 push 0xc02fec
0051b0b7 push esi
0051b0b8 push 1
0051b0ba push 0x3e8
0051b0bf call 0x422e20
0051b0c4 jmp 0x51b11a
0051b0c6 cmp eax, 0x17
0051b0c9 jne 0x51b11a
0051b0cb cmp dword ptr [edi + 0x2c], 1
0051b0cf jne 0x51b11a
0051b0d1 mov eax, dword ptr [0xbfd65c]
0051b0d6 mov eax, dword ptr [eax + 0x243624]
0051b0dc cmp eax, 1
0051b0df je 0x51b0eb
0051b0e1 cmp eax, 3
0051b0e4 je 0x51b0eb
0051b0e6 movaps xmm0, xmm1
0051b0e9 jmp 0x51b0ee
0051b0eb movaps xmm0, xmm2
0051b0ee lea ecx, [ebp - 0x218]
0051b0f4 movss dword ptr [ebp - 0x1c], xmm0
0051b0f9 mov dword ptr [ebp - 0x18], 0
0051b100 call 0x430d70
0051b105 push eax
0051b106 push 7
0051b108 lea eax, [ebp - 0x1c]
0051b10b mov ecx, edi
0051b10d push eax
0051b10e lea eax, [edi + 0x294]
0051b114 push eax
0051b115 call 0x6a1a20
0051b11a cmp dword ptr [edi + 0x28], 0xed
0051b121 jne 0x51b161
0051b123 cmp byte ptr [edi + 0xb8d], 0
0051b12a je 0x51b161
0051b12c cmp dword ptr [edi + 0x30], 2
0051b130 jne 0x51b161
0051b132 mov eax, dword ptr [edi + 8]
0051b135 cmp eax, dword ptr [edi + 0xc]
0051b138 je 0x51b161
0051b13a nop word ptr [eax + eax]
0051b140 mov ecx, dword ptr [eax + 8]
0051b143 and ecx, 4
0051b146 or ecx, 0
0051b149 je 0x51b159
0051b14b mov ecx, dword ptr [eax + 0x18]
0051b14e cmp ecx, dword ptr [edi + 0x28]
0051b151 jne 0x51b159
0051b153 mov dword ptr [eax], 0x40a00000
0051b159 add eax, 0x38
0051b15c cmp eax, dword ptr [edi + 0xc]
0051b15f jne 0x51b140
0051b161 push 0
0051b163 push 1
0051b165 push -1
0051b167 push -1
0051b169 push 0x191
0051b16e lea eax, [ebp - 0x48]
0051b171 push eax
0051b172 mov eax, dword ptr [0xbfd65c]
0051b177 mov ecx, dword ptr [eax + 0x18190]
0051b17d add ecx, 0x1218
0051b183 call 0x415ed0
0051b188 mov dword ptr [ebp - 4], 0
0051b18f mov esi, dword ptr [ebp - 0x3c]
0051b192 test esi, esi
0051b194 je 0x51b1f0
0051b196 mov edx, dword ptr [ebp - 0x44]
0051b199 xor edi, edi
0051b19b nop dword ptr [eax + eax]
0051b1a0 mov eax, dword ptr [edx + edi*4]
0051b1a3 cmp dword ptr [eax + 0xab4], 0x10
0051b1aa je 0x51b1e5
0051b1ac cmp edi, esi
0051b1ae jb 0x51b1c2
0051b1b0 push 0xb3f44c
0051b1b5 push 3
0051b1b7 call 0x95e330
0051b1bc mov edx, dword ptr [ebp - 0x44]
0051b1bf add esp, 8
0051b1c2 lea eax, [esi - 1]
0051b1c5 mov ecx, edi
0051b1c7 mov dword ptr [ebp - 0x30], eax
0051b1ca cmp edi, eax
0051b1cc jae 0x51b1df
0051b1ce mov esi, eax
0051b1d0 mov eax, dword ptr [edx + ecx*4 + 4]
0051b1d4 mov dword ptr [edx + ecx*4], eax
0051b1d7 inc ecx
0051b1d8 cmp ecx, esi
0051b1da jb 0x51b1d0
0051b1dc mov esi, dword ptr [ebp - 0x3c]
0051b1df dec esi
0051b1e0 mov dword ptr [ebp - 0x3c], esi
0051b1e3 jmp 0x51b1e6
0051b1e5 inc edi
0051b1e6 cmp edi, esi
0051b1e8 jb 0x51b1a0
0051b1ea mov edi, dword ptr [ebp - 0x240]
0051b1f0 mov ecx, dword ptr [ebp - 0x3c]
0051b1f3 lea esi, [edi + 0x294]
0051b1f9 movss xmm3, dword ptr [esi]
0051b1fd xor eax, eax
0051b1ff movss xmm4, dword ptr [esi + 4]
0051b204 xorps xmm2, xmm2
0051b207 test ecx, ecx
0051b209 je 0x51b268
0051b20b mov eax, dword ptr [ebp - 0x44]
0051b20e xor esi, esi
0051b210 xor edi, edi
0051b212 mov edx, dword ptr [eax + esi*4]
0051b215 test edx, edx
0051b217 je 0x51b24b
0051b219 movss xmm0, dword ptr [edx + 0x294]
0051b221 movss xmm1, dword ptr [edx + 0x298]
0051b229 subss xmm0, xmm3
0051b22d subss xmm1, xmm4
0051b231 mulss xmm0, xmm0
0051b235 mulss xmm1, xmm1
0051b239 addss xmm1, xmm0
0051b23d comiss xmm2, xmm1
0051b240 ja 0x51b246
0051b242 test edi, edi
0051b244 jne 0x51b24b
0051b246 mov edi, edx
0051b248 movaps xmm2, xmm1
0051b24b inc esi
0051b24c cmp esi, ecx
0051b24e jb 0x51b212
0051b250 mov dword ptr [ebp - 0x22c], edi
0051b256 mov edi, dword ptr [ebp - 0x240]
0051b25c mov eax, dword ptr [ebp - 0x22c]
0051b262 lea esi, [edi + 0x294]
0051b268 push 0
0051b26a push 0xbeab70
0051b26f push 0xbeab18
0051b274 push 0
0051b276 push eax
0051b277 call 0x9ec34c
0051b27c add esp, 0x14
0051b27f mov dword ptr [ebp - 4], 0xffffffff
0051b286 cmp byte ptr [ebp - 0x48], 0
0051b28a mov dword ptr [ebp - 0x220], eax
0051b290 jne 0x51b2a3
0051b292 push dword ptr [ebp - 0x44]
0051b295 call 0x9eace5
0051b29a mov eax, dword ptr [ebp - 0x220]
0051b2a0 add esp, 4
0051b2a3 cmp dword ptr [edi + 0xab4], 0
0051b2aa jne 0x51b547
0051b2b0 mov eax, dword ptr [edi + 0x28]
0051b2b3 cmp eax, 0x37
0051b2b6 jne 0x51b34f
0051b2bc cmp dword ptr [edi + 0x2c], 2
0051b2c0 jne 0x51b331
0051b2c2 call 0x6c3d90
0051b2c7 mov ecx, dword ptr [0xbfd65c]
0051b2cd push 0
0051b2cf push 0xbeab70
0051b2d4 push 0xbeab18
0051b2d9 push 0
0051b2db push eax
0051b2dc push 0
0051b2de push edi
0051b2df push 0xc02fec
0051b2e4 push esi
0051b2e5 push 0
0051b2e7 push 0x60
0051b2e9 call 0x422e20
0051b2ee push eax
0051b2ef call 0x9ec34c
0051b2f4 mov ecx, dword ptr [eax + 0x314]
0051b2fa add eax, 0x314
0051b2ff add esp, 0x14
0051b302 mov dword ptr [ebp - 0x22c], eax
0051b308 test ecx, ecx
0051b30a je 0x51b324
0051b30c mov dword ptr [ebp - 0x30], eax
0051b30f add ecx, 0x324
0051b315 lea eax, [ebp - 0x30]
0051b318 push eax
0051b319 call 0x4bc3c0
0051b31e mov eax, dword ptr [ebp - 0x22c]
0051b324 push eax
0051b325 mov ecx, edi
0051b327 mov dword ptr [eax], edi
0051b329 call 0x4bae70
0051b32e mov eax, dword ptr [edi + 0x28]
0051b331 cmp eax, 0x37
0051b334 jne 0x51b34f
0051b336 mov dword ptr [edi + 0x17c], 3
0051b340 mov dword ptr [edi + 0xab4], 4
0051b34a jmp 0x51b464
0051b34f mov dword ptr [edi + 0xab4], 4
0051b359 cmp eax, 0xed
0051b35e jne 0x51b464
0051b364 cmp byte ptr [edi + 0xb8d], 0
0051b36b je 0x51b464
0051b371 cmp dword ptr [edi + 0x34], 0
0051b375 jne 0x51b464
0051b37b cmp dword ptr [edi + 0x30], 1
0051b37f jne 0x51b464
0051b385 push 0
0051b387 push 0
0051b389 push -1
0051b38b push 1
0051b38d push eax
0051b38e lea eax, [ebp - 0x48]
0051b391 push eax
0051b392 mov eax, dword ptr [0xbfd65c]
0051b397 mov ecx, dword ptr [eax + 0x18190]
0051b39d add ecx, 0x1218
0051b3a3 call 0x415ed0
0051b3a8 xor ecx, ecx
0051b3aa mov dword ptr [ebp - 4], 1
0051b3b1 xor edx, edx
0051b3b3 cmp dword ptr [ebp - 0x3c], ecx
0051b3b6 jbe 0x51b3e4
0051b3b8 mov edi, dword ptr [ebp - 0x44]
0051b3bb xor esi, esi
0051b3bd nop dword ptr [eax]
0051b3c0 mov eax, dword ptr [edi + edx*4]
0051b3c3 lea ecx, [esi + 1]
0051b3c6 cmp dword ptr [eax + 0x34], 0
0051b3ca cmovne ecx, esi
0051b3cd inc edx
0051b3ce mov esi, ecx
0051b3d0 cmp edx, dword ptr [ebp - 0x3c]
0051b3d3 jb 0x51b3c0
0051b3d5 mov edi, dword ptr [ebp - 0x240]
0051b3db mov dword ptr [ebp - 0x30], esi
0051b3de lea esi, [edi + 0x294]
0051b3e4 lea eax, [ecx + 1]
0051b3e7 cdq 
0051b3e8 sub eax, edx
0051b3ea sar eax, 1
0051b3ec add eax, ecx
0051b3ee mov ecx, dword ptr [ebp - 0x3c]
0051b3f1 cmp ecx, eax
0051b3f3 jge 0x51b453
0051b3f5 sub eax, ecx
0051b3f7 mov dword ptr [ebp - 0x22c], eax
0051b3fd nop dword ptr [eax]
0051b400 call 0x6c3d90
0051b405 push eax
0051b406 push dword ptr [edi + 0x30]
0051b409 lea eax, [ebp - 0x1c]
0051b40c push edi
0051b40d push 0xc02fec
0051b412 push 0
0051b414 push 0
0051b416 push ecx
0051b417 mov ecx, dword ptr [0xbfd65c]
0051b41d mov dword ptr [esp], 0x42700000
0051b424 push esi
0051b425 push eax
0051b426 mov ecx, dword ptr [ecx + 0x18190]
0051b42c call 0x7cf240
0051b431 mov ecx, dword ptr [0xbfd65c]
0051b437 push eax
0051b438 push dword ptr [edi + 0x2c]
0051b43b push dword ptr [edi + 0x28]
0051b43e call 0x422e20
0051b443 mov ecx, eax
0051b445 mov edx, dword ptr [eax]
0051b447 call dword ptr [edx + 0xc]
0051b44a sub dword ptr [ebp - 0x22c], 1
0051b451 jne 0x51b400
0051b453 cmp byte ptr [ebp - 0x48], 0
0051b457 jne 0x51b464
0051b459 push dword ptr [ebp - 0x44]
0051b45c call 0x9eace5
0051b461 add esp, 4
0051b464 mov eax, dword ptr [edi + 0x28]
0051b467 cmp eax, 0xed
0051b46c jne 0x51b4d6
0051b46e cmp dword ptr [edi + 0x2c], 2
0051b472 jne 0x51ddd5
0051b478 movaps xmm1, xmmword ptr [0xb6bd30]
0051b47f lea eax, [ebp - 0x26c]
0051b485 add edi, 0x1dc
0051b48b mov dword ptr [ebp - 0x24c], 0x3f19999a
0051b495 mov dword ptr [ebp - 0x248], 0x3ecccccd
0051b49f xorps xmm0, xmm0
0051b4a2 mov dword ptr [ebp - 0x244], 0
0051b4ac cmp edi, eax
0051b4ae je 0x51ddd5
0051b4b4 mov eax, dword ptr [ebp - 0x244]
0051b4ba movups xmmword ptr [edi + 0x10], xmm0
0051b4be movq xmm0, qword ptr [ebp - 0x24c]
0051b4c6 movq qword ptr [edi + 0x20], xmm0
0051b4cb movups xmmword ptr [edi], xmm1
0051b4ce mov dword ptr [edi + 0x28], eax
0051b4d1 jmp 0x51ddd5
0051b4d6 cmp eax, 0x17
0051b4d9 jne 0x51ddd5
0051b4df cmp dword ptr [edi + 0x2c], 2
0051b4e3 jne 0x51ddd5
0051b4e9 movaps xmm1, xmmword ptr [0xb6bd30]
0051b4f0 lea eax, [ebp - 0x298]
0051b4f6 add edi, 0x1dc
0051b4fc mov dword ptr [ebp - 0x278], 0
0051b506 mov dword ptr [ebp - 0x274], 0
0051b510 xorps xmm0, xmm0
0051b513 mov dword ptr [ebp - 0x270], 0
0051b51d cmp edi, eax
0051b51f je 0x51ddd5
0051b525 mov eax, dword ptr [ebp - 0x270]
0051b52b movups xmmword ptr [edi + 0x10], xmm0
0051b52f movq xmm0, qword ptr [ebp - 0x278]
0051b537 movq qword ptr [edi + 0x20], xmm0
0051b53c movups xmmword ptr [edi], xmm1
0051b53f mov dword ptr [edi + 0x28], eax
0051b542 jmp 0x51ddd5
0051b547 movss xmm3, dword ptr [0xb6a4c4]
0051b54f mov byte ptr [ebp - 0x222], 0
0051b556 movss dword ptr [ebp - 0x230], xmm3
0051b55e test eax, eax
0051b560 je 0x51b6ad
0051b566 movss xmm2, dword ptr [eax + 0x298]
0051b56e movss xmm0, dword ptr [esi + 4]
0051b573 movss xmm1, dword ptr [eax + 0x294]
0051b57b subss xmm1, dword ptr [esi]
0051b57f divss xmm0, xmm3
0051b583 divss xmm2, xmm3
0051b587 movss dword ptr [ebp - 0x22c], xmm1
0051b58f subss xmm2, xmm0
0051b593 movaps xmm0, xmm1
0051b596 mulss xmm0, xmm1
0051b59a movaps xmm1, xmm2
0051b59d movss dword ptr [ebp - 0x30], xmm2
0051b5a2 mulss xmm1, xmm2
0051b5a6 addss xmm0, xmm1
0051b5aa call 0x4228c0
0051b5af mov eax, dword ptr [ebp - 0x220]
0051b5b5 movaps xmm2, xmm0
0051b5b8 movss xmm4, dword ptr [eax + 0x2c8]
0051b5c0 movaps xmm1, xmm4
0051b5c3 mulss xmm1, dword ptr [0xb6a690]
0051b5cb comiss xmm1, xmm2
0051b5ce jbe 0x51b5e2
0051b5d0 mov dword ptr [edi + 0x2ac], 0x578
0051b5da movss xmm4, dword ptr [eax + 0x2c8]
0051b5e2 comiss xmm4, xmm2
0051b5e5 jbe 0x51b6ad
0051b5eb cmp dword ptr [eax + 0x70], 0
0051b5ef movss xmm0, dword ptr [ebp - 0x30]
0051b5f4 divss xmm0, xmm4
0051b5f8 mov byte ptr [ebp - 0x222], 1
0051b5ff movss xmm1, dword ptr [0xb6a614]
0051b607 andps xmm0, xmmword ptr [0xb6c980]
0051b60e subss xmm1, xmm0
0051b612 movss xmm0, dword ptr [ebp - 0x22c]
0051b61a divss xmm0, xmm4
0051b61e divss xmm2, xmm4
0051b622 mulss xmm0, dword ptr [0xb6aa24]
0051b62a mulss xmm2, xmm2
0051b62e mulss xmm1, xmm0
0051b632 movss xmm0, dword ptr [0xb6a614]
0051b63a subss xmm0, xmm2
0051b63e movss dword ptr [ebp - 0x22c], xmm1
0051b646 movss dword ptr [ebp - 0x30], xmm0
0051b64b je 0x51b693
0051b64d push 0xb4322c
0051b652 lea ecx, [eax + 0x6c]
0051b655 call 0x405da0
0051b65a movss xmm1, dword ptr [ebp - 0x22c]
0051b662 test eax, eax
0051b664 je 0x51b693
0051b666 movss xmm0, dword ptr [ebp - 0x30]
0051b66b mulss xmm0, dword ptr [eax + 4]
0051b670 mov dword ptr [edi + 0xd0], 0
0051b67a movss dword ptr [edi + 0xd4], xmm0
0051b682 movss xmm0, dword ptr [eax + 4]
0051b687 divss xmm0, dword ptr [0xb6a9f4]
0051b68f mulss xmm1, xmm0
0051b693 movss xmm0, dword ptr [edi + 0x2c4]
0051b69b mulss xmm0, dword ptr [0xb6a588]
0051b6a3 movss dword ptr [edi + 0x2c4], xmm0
0051b6ab jmp 0x51b6ce
0051b6ad mov dword ptr [edi + 0xd0], 0
0051b6b7 xorps xmm1, xmm1
0051b6ba mov dword ptr [edi + 0xd4], 0
0051b6c4 mov dword ptr [edi + 0x2ac], 0
0051b6ce movss dword ptr [edi + 0xe0], xmm1
0051b6d6 mov eax, dword ptr [edi + 0x28]
0051b6d9 cmp eax, 0x17
0051b6dc je 0x51b6f1
0051b6de cmp eax, 0x37
0051b6e1 je 0x51b6f1
0051b6e3 mov byte ptr [ebp - 0x238], 0
0051b6ea cmp eax, 0xed
0051b6ef jne 0x51b6f8
0051b6f1 mov byte ptr [ebp - 0x238], 1
0051b6f8 mov ecx, edi
0051b6fa call 0x695680
0051b6ff cmp dword ptr [eax + 0x28], 1
0051b703 jne 0x51b730
0051b705 mov eax, dword ptr [edi + 0x160]
0051b70b and eax, 0x20000000
0051b710 or eax, 0
0051b713 je 0x51b730
0051b715 mov eax, dword ptr [ebp - 0x238]
0051b71b xor ecx, ecx
0051b71d cmp dword ptr [edi + 0xe6c], -1
0051b724 movzx eax, al
0051b727 cmove eax, ecx
0051b72a mov dword ptr [ebp - 0x238], eax
0051b730 mov eax, dword ptr [edi + 0x28]
0051b733 cmp eax, 0x15
0051b736 jne 0x51b74a
0051b738 movss xmm1, dword ptr [0xb6a53c]
0051b740 movss dword ptr [ebp - 0x230], xmm1
0051b748 jmp 0x51b7a2
0051b74a cmp eax, 0x37
0051b74d jne 0x51b761
0051b74f movss xmm3, dword ptr [0xb6a588]
0051b757 movss dword ptr [ebp - 0x230], xmm3
0051b75f jmp 0x51b7aa
0051b761 cmp eax, 0x1f
0051b764 je 0x51b792
0051b766 cmp eax, 0xf3
0051b76b je 0x51b792
0051b76d cmp eax, 0x17
0051b770 jne 0x51b7a2
0051b772 cmp dword ptr [edi + 0x2c], 1
0051b776 movss xmm3, dword ptr [0xb6a588]
0051b77e jne 0x51b7aa
0051b780 movss xmm1, dword ptr [0xb6a498]
0051b788 movss dword ptr [ebp - 0x230], xmm1
0051b790 jmp 0x51b7aa
0051b792 movss xmm0, dword ptr [0xb6a534]
0051b79a movss dword ptr [ebp - 0x230], xmm0
0051b7a2 movss xmm3, dword ptr [0xb6a588]
0051b7aa movss xmm1, dword ptr [0xb6aa3c]
0051b7b2 movss xmm0, dword ptr [esi]
0051b7b6 subss xmm0, xmm1
0051b7ba mov ecx, dword ptr [0xbfd65c]
0051b7c0 mov ecx, dword ptr [ecx + 0x18190]
0051b7c6 divss xmm0, xmm1
0051b7ca addss xmm0, dword ptr [0xb6a480]
0051b7d2 cvttss2si edx, xmm0
0051b7d6 movss xmm0, dword ptr [esi + 4]
0051b7db subss xmm0, dword ptr [0xb6ab20]
0051b7e3 divss xmm0, xmm1
0051b7e7 addss xmm0, dword ptr [0xb6a480]
0051b7ef cvttss2si eax, xmm0
0051b7f3 test edx, edx
0051b7f5 js 0x51b813
0051b7f7 cmp edx, dword ptr [ecx + 0xc]
0051b7fa jge 0x51b813
0051b7fc test eax, eax
0051b7fe js 0x51b813
0051b800 cmp eax, dword ptr [ecx + 0x10]
0051b803 jge 0x51b813
0051b805 imul eax, dword ptr [ecx + 0xc]
0051b809 add eax, edx
0051b80b mov dword ptr [ebp - 0x23c], eax
0051b811 jmp 0x51b81d
0051b813 mov dword ptr [ebp - 0x23c], 0xffffffff
0051b81d push 0x384
0051b822 push esi
0051b823 call 0x4baf00
0051b828 mov edx, dword ptr [edi + 0x28]
0051b82b mov dword ptr [ebp - 0x20], 0xb425a8
0051b832 mov dword ptr [ebp - 0x1c], 0xb425a0
0051b839 mov dword ptr [ebp - 0x18], 0xb425c4
0051b840 mov dword ptr [ebp - 0x60], 0xb42f28
0051b847 mov dword ptr [ebp - 0x5c], 0xb406e4
0051b84e mov dword ptr [ebp - 0x58], 0xb406f0
0051b855 mov dword ptr [ebp - 0x44], 0xb43208
0051b85c mov dword ptr [ebp - 0x40], 0xb41ac8
0051b863 mov dword ptr [ebp - 0x3c], 0xb41abc
0051b86a mov dword ptr [ebp - 0x54], 0xb43214
0051b871 mov dword ptr [ebp - 0x50], 0xb42574
0051b878 mov dword ptr [ebp - 0x4c], 0xb42540
0051b87f mov dword ptr [ebp - 0x6c], 0xb425a8
0051b886 mov dword ptr [ebp - 0x68], 0xb43250
0051b88d mov dword ptr [ebp - 0x64], 0xb43250
0051b894 mov dword ptr [ebp - 0x2c], 0xb43214
0051b89b mov dword ptr [ebp - 0x28], 0xb42540
0051b8a2 mov dword ptr [ebp - 0x24], 0xb42540
0051b8a9 mov dword ptr [ebp - 0x98], 0xb404ec
0051b8b3 mov dword ptr [ebp - 0x94], 0xb404ec
0051b8bd mov dword ptr [ebp - 0x90], 0xb4104c
0051b8c7 mov dword ptr [ebp - 0x8c], 0xb41040
0051b8d1 mov dword ptr [ebp - 0x7c], 0xb41c68
0051b8d8 mov dword ptr [ebp - 0x78], 0xb41c5c
0051b8df mov dword ptr [ebp - 0x74], 0xb41bcc
0051b8e6 mov dword ptr [ebp - 0x70], 0xb41bd8
0051b8ed mov dword ptr [ebp - 0x88], 0xb4325c
0051b8f7 mov dword ptr [ebp - 0x84], 0xb43238
0051b901 mov dword ptr [ebp - 0x80], 0xb43244
0051b908 mov dword ptr [ebp - 0x38], 0xb43278
0051b90f mov dword ptr [ebp - 0x34], 0xb43288
0051b916 mov dword ptr [ebp - 0x30], 0xb43268
0051b91d cmp edx, 0x17
0051b920 jne 0x51b92f
0051b922 cmp dword ptr [edi + 0x2c], 2
0051b926 mov byte ptr [ebp - 0x221], 1
0051b92d je 0x51b936
0051b92f mov byte ptr [ebp - 0x221], 0
0051b936 mov ecx, dword ptr [edi + 0xab4]
0051b93c cmp ecx, 5
0051b93f jne 0x51ba50
0051b945 movss xmm0, dword ptr [edi + 0xb00]
0051b94d ucomiss xmm0, dword ptr [0xc02fec]
0051b954 lahf 
0051b955 test ah, 0x44
0051b958 jp 0x51b987
0051b95a movss xmm0, dword ptr [edi + 0xb04]
0051b962 ucomiss xmm0, dword ptr [0xc02ff0]
0051b969 lahf 
0051b96a test ah, 0x44
0051b96d jp 0x51b987
0051b96f mov eax, dword ptr [edi + 0x28c]
0051b975 mov dword ptr [edi + 0xb00], eax
0051b97b mov eax, dword ptr [edi + 0x290]
0051b981 mov dword ptr [edi + 0xb04], eax
0051b987 movss xmm4, dword ptr [edi + 0x2c4]
0051b98f xorps xmm3, xmm3
0051b992 mulss xmm4, dword ptr [0xb6a5a4]
0051b99a ucomiss xmm4, xmm3
0051b99d movss dword ptr [edi + 0x2c4], xmm4
0051b9a5 lahf 
0051b9a6 test ah, 0x44
0051b9a9 jnp 0x51b9f0
0051b9ab movss xmm1, dword ptr [edi + 0x2f4]
0051b9b3 movaps xmm2, xmm1
0051b9b6 mulss xmm2, dword ptr [edi + 0xb00]
0051b9be divss xmm2, xmm4
0051b9c2 addss xmm2, dword ptr [edi + 0x2b8]
0051b9ca movss dword ptr [edi + 0x2b8], xmm2
0051b9d2 mulss xmm1, dword ptr [edi + 0xb04]
0051b9da divss xmm1, xmm4
0051b9de addss xmm1, dword ptr [edi + 0x2bc]
0051b9e6 movss dword ptr [edi + 0x2bc], xmm1
0051b9ee jmp 0x51b9f8
0051b9f0 movss xmm2, dword ptr [edi + 0x2b8]
0051b9f8 comiss xmm2, xmm3
0051b9fb mov ecx, dword ptr [0xbfd65c]
0051ba01 movss xmm4, dword ptr [0xb6aad4]
0051ba09 jbe 0x51ba23
0051ba0b mov eax, dword ptr [ecx + 0x18190]
0051ba11 movss xmm0, dword ptr [esi]
0051ba15 movss xmm1, dword ptr [eax + 0x1c]
0051ba1a addss xmm1, xmm4
0051ba1e comiss xmm0, xmm1
0051ba21 ja 0x51ba44
0051ba23 comiss xmm3, xmm2
0051ba26 jbe 0x51ddd5
0051ba2c mov eax, dword ptr [ecx + 0x18190]
0051ba32 movss xmm0, dword ptr [eax + 0x14]
0051ba37 subss xmm0, xmm4
0051ba3b comiss xmm0, dword ptr [esi]
0051ba3e jbe 0x51ddd5
0051ba44 mov eax, dword ptr [edi]
0051ba46 mov ecx, edi
0051ba48 call dword ptr [eax + 0x28]
0051ba4b jmp 0x51ddd5
0051ba50 movss xmm6, dword ptr [0xb6ae44]
0051ba58 xor eax, eax
0051ba5a mov dword ptr [ebp - 0x21c], eax
0051ba60 cmp edx, 0xed
0051ba66 jne 0x51bab9
0051ba68 movss xmm4, dword ptr [edi + 0x2b8]
0051ba70 movss xmm5, dword ptr [edi + 0x2bc]
0051ba78 movaps xmm1, xmm4
0051ba7b andps xmm1, xmmword ptr [0xb6c980]
0051ba82 movaps xmm0, xmm5
0051ba85 andps xmm0, xmmword ptr [0xb6c980]
0051ba8c comiss xmm1, xmm0
0051ba8f xorps xmm0, xmm0
0051ba92 jbe 0x51baa8
0051ba94 comiss xmm0, xmm4
0051ba97 setbe al
0051ba9a add eax, 2
0051ba9d mov dword ptr [ebp - 0x21c], eax
0051baa3 jmp 0x51bb43
0051baa8 comiss xmm0, xmm5
0051baab setbe al
0051baae mov dword ptr [ebp - 0x21c], eax
0051bab4 jmp 0x51bb43
0051bab9 cmp ecx, 8
0051babc je 0x51bad7
0051babe cmp byte ptr [ebp - 0x221], al
0051bac4 je 0x51bacb
0051bac6 cmp ecx, 0x10
0051bac9 je 0x51bad7
0051bacb mov dword ptr [ebp - 0x22c], 0x2b8
0051bad5 jmp 0x51bae1
0051bad7 mov dword ptr [ebp - 0x22c], 0xb00
0051bae1 mov esi, dword ptr [ebp - 0x22c]
0051bae7 movss xmm5, dword ptr [esi + edi]
0051baec movss xmm4, dword ptr [esi + edi + 4]
0051baf2 movaps xmm1, xmm5
0051baf5 andps xmm1, xmmword ptr [0xb6c980]
0051bafc lea esi, [edi + 0x294]
0051bb02 movaps xmm0, xmm4
0051bb05 andps xmm0, xmmword ptr [0xb6c980]
0051bb0c comiss xmm1, xmm0
0051bb0f jbe 0x51bc02
0051bb15 cmp ecx, 9
0051bb18 je 0x51bb43
0051bb1a xorps xmm0, xmm0
0051bb1d comiss xmm0, xmm5
0051bb20 seta al
0051bb23 mov byte ptr [edi + 0x13c], al
0051bb29 test al, al
0051bb2b je 0x51bb41
0051bb2d movss xmm0, dword ptr [edi + 0xe0]
0051bb35 mulss xmm0, xmm6
0051bb39 movss dword ptr [edi + 0xe0], xmm0
0051bb41 xor eax, eax
0051bb43 movss xmm4, dword ptr [0xb6a7b0]
0051bb4b movss xmm1, dword ptr [0xb6a560]
0051bb53 mov dword ptr [ebp - 0x240], 3
0051bb5d mov dword ptr [ebp - 0x22c], 2
0051bb67 cmp ecx, 3
0051bb6a jne 0x51bf09
0051bb70 movss xmm0, dword ptr [edi + 0x2c4]
0051bb78 mulss xmm0, xmm3
0051bb7c movss dword ptr [edi + 0x2c4], xmm0
0051bb84 cmp edx, 0xed
0051bb8a jne 0x51bee7
0051bb90 cmp dword ptr [edi + 0x70], 0
0051bb94 je 0x51befa
0051bb9a push 0xb400ac
0051bb9f lea ecx, [edi + 0x6c]
0051bba2 call 0x405e90
0051bba7 test al, al
0051bba9 je 0x51bee7
0051bbaf mov eax, dword ptr [edi + 0x2c]
0051bbb2 test eax, eax
0051bbb4 jne 0x51bc19
0051bbb6 push ecx
0051bbb7 mov dword ptr [esp], 0x3f800000
0051bbbe push eax
0051bbbf push 2
0051bbc1 push ecx
0051bbc2 mov dword ptr [esp], 0x3f800000
0051bbc9 mov ecx, edi
0051bbcb push 0xb2
0051bbd0 call 0x6ad720
0051bbd5 lea ecx, [ebp - 0x218]
0051bbdb mov dword ptr [ebp - 0x1c], 0x40f00000
0051bbe2 mov dword ptr [ebp - 0x18], 0x40c00000
0051bbe9 call 0x430d70
0051bbee push eax
0051bbef push 9
0051bbf1 lea eax, [ebp - 0x1c]
0051bbf4 mov ecx, edi
0051bbf6 push eax
0051bbf7 push esi
0051bbf8 call 0x6a1a20
0051bbfd jmp 0x51bee7
0051bc02 xor eax, eax
0051bc04 xorps xmm0, xmm0
0051bc07 comiss xmm0, xmm4
0051bc0a setbe al
0051bc0d inc eax
0051bc0e mov dword ptr [ebp - 0x21c], eax
0051bc14 jmp 0x51bb43
0051bc19 cmp eax, 2
0051bc1c jne 0x51bddb
0051bc22 mov ecx, edi
0051bc24 call 0x6ad7a0
0051bc29 cmp eax, 8
0051bc2c jg 0x51bdbd
0051bc32 xor eax, eax
0051bc34 mov dword ptr [ebp - 0x228], eax
0051bc3a nop word ptr [eax + eax]
0051bc40 movd xmm0, eax
0051bc44 cvtdq2ps xmm0, xmm0
0051bc47 mulss xmm0, dword ptr [0xb6a38c]
0051bc4f mulss xmm0, dword ptr [0xb6ac40]
0051bc57 mulss xmm0, dword ptr [0xb6a230]
0051bc5f movss dword ptr [ebp - 0x30], xmm0
0051bc64 call 0x411fe0
0051bc69 movss dword ptr [ebp - 0x220], xmm0
0051bc71 movss xmm0, dword ptr [ebp - 0x30]
0051bc76 call 0x412010
0051bc7b movss xmm3, dword ptr [edi + 0x2c8]
0051bc83 movaps xmm2, xmm0
0051bc86 addss xmm3, dword ptr [0xb6a8f4]
0051bc8e call 0x6c3d90
0051bc93 movss xmm1, dword ptr [ebp - 0x220]
0051bc9b mov ecx, dword ptr [0xbfd65c]
0051bca1 movaps xmm0, xmm1
0051bca4 mulss xmm0, dword ptr [0xb6a974]
0051bcac push eax
0051bcad push 0
0051bcaf push edi
0051bcb0 movss dword ptr [ebp - 0x30], xmm0
0051bcb5 lea eax, [ebp - 0x1c]
0051bcb8 movss dword ptr [ebp - 0x1c], xmm0
0051bcbd movaps xmm0, xmm2
0051bcc0 mulss xmm0, dword ptr [0xb6a974]
0051bcc8 push eax
0051bcc9 lea eax, [ebp - 0x28]
0051bccc push eax
0051bccd movss dword ptr [ebp - 0x220], xmm0
0051bcd5 movss dword ptr [ebp - 0x18], xmm0
0051bcda movaps xmm0, xmm3
0051bcdd mulss xmm0, xmm1
0051bce1 push 2
0051bce3 mulss xmm3, xmm2
0051bce7 push 0xd9
0051bcec addss xmm0, dword ptr [esi]
0051bcf0 addss xmm3, dword ptr [edi + 0x298]
0051bcf8 movss dword ptr [ebp - 0x28], xmm0
0051bcfd movss dword ptr [ebp - 0x24], xmm3
0051bd02 call 0x422e20
0051bd07 mov edx, eax
0051bd09 and dword ptr [edx + 0x160], 0xfffffffb
0051bd10 movss xmm2, dword ptr [edx + 0x2c4]
0051bd18 ucomiss xmm2, dword ptr [0xb6a18c]
0051bd1f mov ecx, dword ptr [edx + 0x164]
0051bd25 mov dword ptr [edx + 0x164], ecx
0051bd2b lahf 
0051bd2c test ah, 0x44
0051bd2f jnp 0x51bd71
0051bd31 movss xmm1, dword ptr [edx + 0x2f4]
0051bd39 movaps xmm0, xmm1
0051bd3c mulss xmm1, dword ptr [ebp - 0x220]
0051bd44 mulss xmm0, dword ptr [ebp - 0x30]
0051bd49 divss xmm1, xmm2
0051bd4d divss xmm0, xmm2
0051bd51 addss xmm1, dword ptr [edx + 0x2bc]
0051bd59 addss xmm0, dword ptr [edx + 0x2b8]
0051bd61 movss dword ptr [edx + 0x2bc], xmm1
0051bd69 movss dword ptr [edx + 0x2b8], xmm0
0051bd71 mov eax, dword ptr [edx]
0051bd73 mov ecx, edx
0051bd75 mov dword ptr [edx + 0x2d8], 0x3dcccccd
0051bd7f call dword ptr [eax + 0xc]
0051bd82 mov eax, dword ptr [ebp - 0x228]
0051bd88 inc eax
0051bd89 mov dword ptr [ebp - 0x228], eax
0051bd8f cmp eax, 4
0051bd92 jl 0x51bc40
0051bd98 push ecx
0051bd99 mov dword ptr [esp], 0x3f800000
0051bda0 push 0
0051bda2 push 0xa
0051bda4 push ecx
0051bda5 mov dword ptr [esp], 0x3f4ccccd
0051bdac mov ecx, edi
0051bdae push 0xed
0051bdb3 call 0x6ad720
0051bdb8 jmp 0x51bee7
0051bdbd push 0
0051bdbf push 1
0051bdc1 push edi
0051bdc2 push ecx
0051bdc3 mov ecx, dword ptr [0xbfd65c]
0051bdc9 mov dword ptr [esp], 0x42f00000
0051bdd0 push esi
0051bdd1 call 0x6d6570
0051bdd6 jmp 0x51bee7
0051bddb cmp dword ptr [edi + 0x30], 0
0051bddf jne 0x51bee7
0051bde5 xor eax, eax
0051bde7 mov dword ptr [ebp - 0x220], eax
0051bded call 0x6c3d90
0051bdf2 xor edx, edx
0051bdf4 div dword ptr [ebp - 0x240]
0051bdfa test edx, edx
0051bdfc je 0x51bee7
0051be02 call 0x6c3d90
0051be07 movd xmm0, eax
0051be0b cvtdq2pd xmm0, xmm0
0051be0f shr eax, 0x1f
0051be12 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
0051be1b cvtpd2ps xmm0, xmm0
0051be1f mulss xmm0, dword ptr [0xb6a19c]
0051be27 mulss xmm0, dword ptr [0xb6a874]
0051be2f addss xmm0, xmm0
0051be33 movss dword ptr [ebp - 0x30], xmm0
0051be38 call 0x411fe0
0051be3d movss dword ptr [ebp - 0x228], xmm0
0051be45 movss xmm0, dword ptr [ebp - 0x30]
0051be4a call 0x412010
0051be4f movaps xmm2, xmm0
0051be52 call 0x6c3d90
0051be57 movss xmm0, dword ptr [ebp - 0x228]
0051be5f mov ecx, dword ptr [0xbfd65c]
0051be65 movaps xmm1, xmm0
0051be68 addss xmm1, xmm0
0051be6c mulss xmm0, dword ptr [0xb6aa3c]
0051be74 push eax
0051be75 push 0
0051be77 push edi
0051be78 addss xmm0, dword ptr [esi]
0051be7c movss dword ptr [ebp - 0x1c], xmm1
0051be81 lea eax, [ebp - 0x1c]
0051be84 movaps xmm1, xmm2
0051be87 addss xmm1, xmm2
0051be8b mulss xmm2, dword ptr [0xb6aa3c]
0051be93 push eax
0051be94 lea eax, [ebp - 0x28]
0051be97 movss dword ptr [ebp - 0x28], xmm0
0051be9c push eax
0051be9d addss xmm2, dword ptr [esi + 4]
0051bea2 push 0
0051bea4 push 0x12
0051bea6 movss dword ptr [ebp - 0x18], xmm1
0051beab movss dword ptr [ebp - 0x24], xmm2
0051beb0 call 0x422e20
0051beb5 inc dword ptr [ebp - 0x220]
0051bebb mov ecx, dword ptr [eax + 0x164]
0051bec1 and dword ptr [eax + 0x160], 0xfffffffb
0051bec8 mov dword ptr [eax + 0x164], ecx
0051bece call 0x6c3d90
0051bed3 xor edx, edx
0051bed5 div dword ptr [ebp - 0x240]
0051bedb cmp dword ptr [ebp - 0x220], edx
0051bee1 jb 0x51be02
0051bee7 cmp dword ptr [edi + 0x70], 0
0051beeb je 0x51befa
0051beed cmp byte ptr [edi + 0x80], 0
0051bef4 jne 0x51d1c4
0051befa mov dword ptr [edi + 0xab4], 4
0051bf04 jmp 0x51d1c4
0051bf09 cmp ecx, 4
0051bf0c jne 0x51c9e5
0051bf12 lea esi, [edi + 0x3c]
0051bf15 sub edx, 0x37
0051bf18 je 0x51bf3c
0051bf1a sub edx, 0xb6
0051bf20 je 0x51bf33
0051bf22 sub edx, 6
0051bf25 je 0x51bf2d
0051bf27 mov eax, dword ptr [ebp + eax*4 - 0x20]
0051bf2b jmp 0x51bf40
0051bf2d mov eax, dword ptr [ebp + eax*4 - 0x6c]
0051bf31 jmp 0x51bf40
0051bf33 mov eax, dword ptr [ebp + eax*4 - 0x98]
0051bf3a jmp 0x51bf40
0051bf3c mov eax, dword ptr [ebp + eax*4 - 0x60]
0051bf40 push 0
0051bf42 push eax
0051bf43 mov ecx, esi
0051bf45 call 0x4054f0
0051bf4a mov ecx, dword ptr [ebp - 0x220]
0051bf50 movss xmm0, dword ptr [ebp - 0x230]
0051bf58 test ecx, ecx
0051bf5a jne 0x51bf73
0051bf5c push ecx
0051bf5d push ecx
0051bf5e lea ecx, [edi + 0x364]
0051bf64 movss dword ptr [esp], xmm0
0051bf69 call 0x7a51e0
0051bf6e jmp 0x51bff7
0051bf73 mov eax, dword ptr [ecx + 0x294]
0051bf79 mov ecx, dword ptr [ecx + 0x298]
0051bf7f mulss xmm0, dword ptr [0xb6a6c8]
0051bf87 push 1
0051bf89 push 0
0051bf8b push ecx
0051bf8c mov dword ptr [ebp - 0x1c], eax
0051bf8f lea eax, [ebp - 0x1c]
0051bf92 mov dword ptr [ebp - 0x18], ecx
0051bf95 lea ecx, [edi + 0x364]
0051bf9b movss dword ptr [esp], xmm0
0051bfa0 push eax
0051bfa1 call 0x7a3650
0051bfa6 movss xmm1, dword ptr [edi + 0x2bc]
0051bfae movss xmm0, dword ptr [edi + 0x2b8]
0051bfb6 mulss xmm0, xmm0
0051bfba mulss xmm1, xmm1
0051bfbe addss xmm0, xmm1
0051bfc2 call 0x4228c0
0051bfc7 lea edx, [edi + 0x2b8]
0051bfcd movaps xmm5, xmm0
0051bfd0 lea ecx, [ebp - 0x1c]
0051bfd3 call 0x6593a0
0051bfd8 movaps xmm1, xmm5
0051bfdb lea esi, [edi + 0x3c]
0051bfde mulss xmm1, dword ptr [eax]
0051bfe2 mulss xmm5, dword ptr [eax + 4]
0051bfe7 movss dword ptr [edi + 0x2b8], xmm1
0051bfef movss dword ptr [edi + 0x2bc], xmm5
0051bff7 movss xmm2, dword ptr [edi + 0x2f4]
0051bfff ucomiss xmm2, dword ptr [0xb6a614]
0051c006 movss xmm0, dword ptr [edi + 0x2c4]
0051c00e mulss xmm0, dword ptr [0xb6a588]
0051c016 movss xmm1, dword ptr [0xb6a5f0]
0051c01e lahf 
0051c01f movss dword ptr [edi + 0x2c4], xmm0
0051c027 test ah, 0x44
0051c02a jnp 0x51c03f
0051c02c movaps xmm0, xmm2
0051c02f mulss xmm2, xmm1
0051c033 addss xmm0, xmm1
0051c037 subss xmm0, xmm2
0051c03b divss xmm1, xmm0
0051c03f cmp dword ptr [edi + 0x28], 0x1f
0051c043 mulss xmm1, dword ptr [edi + 0x2bc]
0051c04b movss dword ptr [edi + 0x2bc], xmm1
0051c053 jne 0x51c0c4
0051c055 cmp dword ptr [edi + 0x2c], 1
0051c059 jne 0x51c0c4
0051c05b push 0xb400ac
0051c060 mov ecx, esi
0051c062 call 0x4060f0
0051c067 test al, al
0051c069 je 0x51c0c4
0051c06b push ecx
0051c06c mov dword ptr [esp], 0x3f800000
0051c073 push 0
0051c075 push 2
0051c077 push ecx
0051c078 mov dword ptr [esp], 0x3f800000
0051c07f mov ecx, edi
0051c081 push 0xb2
0051c086 call 0x6ad720
0051c08b lea ecx, [ebp - 0x218]
0051c091 call 0x430d70
0051c096 call 0x6c3d90
0051c09b mov esi, eax
0051c09d lea ecx, [ebp - 0x218]
0051c0a3 and esi, 1
0051c0a6 call 0x430d70
0051c0ab push eax
0051c0ac push ecx
0051c0ad mov dword ptr [esp], 0x41200000
0051c0b4 lea eax, [esi + 3]
0051c0b7 push 0xc02fec
0051c0bc push eax
0051c0bd mov ecx, edi
0051c0bf call 0x6a3420
0051c0c4 cmp byte ptr [ebp - 0x238], 0
0051c0cb je 0x51c92b
0051c0d1 cmp dword ptr [edi + 0xe6c], -1
0051c0d8 mov ecx, edi
0051c0da je 0x51c0e5
0051c0dc push 9
0051c0de call 0x6af050
0051c0e3 jmp 0x51c0ef
0051c0e5 push dword ptr [edi + 0x20]
0051c0e8 push 4
0051c0ea call 0x684790
0051c0ef test al, al
0051c0f1 je 0x51c92b
0051c0f7 mov ecx, dword ptr [0xbfd65c]
0051c0fd xor eax, eax
0051c0ff cmp dword ptr [edi + 0x28], 0x37
0051c103 push dword ptr [ebp - 0x23c]
0051c109 cmove eax, dword ptr [ebp - 0x22c]
0051c110 mov ecx, dword ptr [ecx + 0x18190]
0051c116 mov dword ptr [ebp - 0x18], eax
0051c119 lea eax, [ebp - 0x68]
0051c11c push eax
0051c11d call 0x7cebc0
0051c122 call 0x6c3d90
0051c127 mov ecx, edi
0051c129 movd xmm0, eax
0051c12d cvtdq2pd xmm0, xmm0
0051c131 shr eax, 0x1f
0051c134 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
0051c13d cvtpd2ps xmm0, xmm0
0051c141 mulss xmm0, dword ptr [0xb6a19c]
0051c149 movss dword ptr [ebp - 0x30], xmm0
0051c14e call 0x695680
0051c153 push ecx
0051c154 mov dword ptr [esp], 0
0051c15b mov ecx, edi
0051c15d movss xmm0, dword ptr [eax + 0x2b8]
0051c165 movss dword ptr [ebp - 0x228], xmm0
0051c16d movss xmm0, dword ptr [eax + 0x2bc]
0051c175 lea eax, [ebp - 0x5c]
0051c178 push eax
0051c179 movss dword ptr [ebp - 0x238], xmm0
0051c181 call 0x695a30
0051c186 movss xmm2, dword ptr [ebp - 0x30]
0051c18b movaps xmm0, xmm2
0051c18e mulss xmm2, dword ptr [ebp - 0x238]
0051c196 push ecx
0051c197 mulss xmm0, dword ptr [ebp - 0x228]
0051c19f mov ecx, dword ptr [0xbfd65c]
0051c1a5 mulss xmm2, dword ptr [0xb6a9b0]
0051c1ad mov dword ptr [esp], 0x41a00000
0051c1b4 mulss xmm0, dword ptr [0xb6a9b0]
0051c1bc mov ecx, dword ptr [ecx + 0x18190]
0051c1c2 addss xmm2, dword ptr [eax + 4]
0051c1c7 addss xmm0, dword ptr [eax]
0051c1cb lea eax, [ebp - 0x50]
0051c1ce push eax
0051c1cf lea eax, [ebp - 0x28]
0051c1d2 movss dword ptr [ebp - 0x4c], xmm2
0051c1d7 push eax
0051c1d8 movss dword ptr [ebp - 0x50], xmm0
0051c1dd call 0x427710
0051c1e2 mov eax, dword ptr [ebp - 0x220]
0051c1e8 test eax, eax
0051c1ea je 0x51c208
0051c1ec movss xmm2, dword ptr [eax + 0x294]
0051c1f4 movss xmm1, dword ptr [eax + 0x298]
0051c1fc movss dword ptr [ebp - 0x28], xmm2
0051c201 movss dword ptr [ebp - 0x24], xmm1
0051c206 jmp 0x51c212
0051c208 movss xmm1, dword ptr [ebp - 0x24]
0051c20d movss xmm2, dword ptr [ebp - 0x28]
0051c212 cmp dword ptr [edi + 0xe6c], -1
0051c219 movss dword ptr [ebp - 0x30], xmm2
0051c21e subss xmm2, dword ptr [ebp - 0x68]
0051c223 movss dword ptr [ebp - 0x238], xmm1
0051c22b subss xmm1, dword ptr [ebp - 0x64]
0051c230 movss dword ptr [ebp - 0x228], xmm2
0051c238 movss dword ptr [ebp - 0x50], xmm2
0051c23d movss dword ptr [ebp - 0x220], xmm1
0051c245 movss dword ptr [ebp - 0x4c], xmm1
0051c24a je 0x51c28d
0051c24c lea eax, [ebp - 0x5c]
0051c24f xorps xmm2, xmm2
0051c252 push eax
0051c253 mov ecx, edi
0051c255 call 0x6af0c0
0051c25a movss xmm1, dword ptr [eax]
0051c25e mulss xmm1, dword ptr [0xb6aafc]
0051c266 movss dword ptr [ebp - 0x228], xmm1
0051c26e movss dword ptr [ebp - 0x50], xmm1
0051c273 movss xmm1, dword ptr [eax + 4]
0051c278 mulss xmm1, dword ptr [0xb6aafc]
0051c280 movss dword ptr [ebp - 0x220], xmm1
0051c288 movss dword ptr [ebp - 0x4c], xmm1
0051c28d mov esi, dword ptr [edi + 0x28]
0051c290 cmp esi, 0x17
0051c293 jne 0x51c677
0051c299 cmp dword ptr [edi + 0x2c], 3
0051c29d jne 0x51c677
0051c2a3 movss xmm0, dword ptr [0xb6a554]
0051c2ab call 0x411fe0
0051c2b0 movss dword ptr [ebp - 0x230], xmm0
0051c2b8 movss xmm0, dword ptr [0xb6a554]
0051c2c0 call 0x412010
0051c2c5 movss xmm5, dword ptr [ebp - 0x230]
0051c2cd movss xmm4, dword ptr [ebp - 0x228]
0051c2d5 movaps xmm2, xmm5
0051c2d8 movss xmm1, dword ptr [ebp - 0x220]
0051c2e0 mulss xmm5, dword ptr [ebp - 0x220]
0051c2e8 movss xmm3, dword ptr [0xb6a9c8]
0051c2f0 mulss xmm2, xmm4
0051c2f4 mulss xmm1, xmm0
0051c2f8 mulss xmm4, xmm0
0051c2fc movss xmm0, dword ptr [0xb6c980]
0051c304 subss xmm2, xmm1
0051c308 addss xmm5, xmm4
0051c30c movss dword ptr [ebp - 0x1c], xmm2
0051c311 andps xmm2, xmm0
0051c314 comiss xmm3, xmm2
0051c317 movss dword ptr [ebp - 0x18], xmm5
0051c31c ja 0x51c32a
0051c31e andps xmm5, xmm0
0051c321 comiss xmm3, xmm5
0051c324 jbe 0x51d1c4
0051c32a push 0
0051c32c push 0x1000a00
0051c331 mov ecx, edi
0051c333 call 0x4122f0
0051c338 test al, al
0051c33a jne 0x51d1c4
0051c340 lea edx, [ebp - 0x1c]
0051c343 lea ecx, [ebp - 0x28]
0051c346 call 0x6593a0
0051c34b movss xmm0, dword ptr [0xb6ae3c]
0051c353 mov esi, eax
0051c355 call 0x411fe0
0051c35a movss dword ptr [ebp - 0x228], xmm0
0051c362 movss xmm0, dword ptr [0xb6ae3c]
0051c36a call 0x412010
0051c36f movss xmm2, dword ptr [esi]
0051c373 movss xmm4, dword ptr [esi + 4]
0051c378 movaps xmm5, xmm2
0051c37b mulss xmm5, dword ptr [ebp - 0x228]
0051c383 movaps xmm1, xmm4
0051c386 mulss xmm4, dword ptr [ebp - 0x228]
0051c38e mulss xmm1, xmm0
0051c392 mulss xmm2, xmm0
0051c396 movss xmm0, dword ptr [0xb6a704]
0051c39e subss xmm5, xmm1
0051c3a2 addss xmm4, xmm2
0051c3a6 movss dword ptr [ebp - 0x230], xmm5
0051c3ae movss dword ptr [ebp - 0x228], xmm4
0051c3b6 call 0x411fe0
0051c3bb movss dword ptr [ebp - 0x220], xmm0
0051c3c3 movss xmm0, dword ptr [0xb6a704]
0051c3cb call 0x412010
0051c3d0 movss xmm2, dword ptr [ebp - 0x220]
0051c3d8 lea ecx, [ebp - 0x28]
0051c3db mov eax, dword ptr [0xbfd65c]
0051c3e0 movaps xmm3, xmm2
0051c3e3 mulss xmm3, dword ptr [ebp - 0x230]
0051c3eb movaps xmm1, xmm0
0051c3ee mulss xmm1, dword ptr [ebp - 0x228]
0051c3f6 mov eax, dword ptr [eax + 0x18190]
0051c3fc mulss xmm2, dword ptr [ebp - 0x228]
0051c404 mov dword ptr [ebp - 0x18], eax
0051c407 mulss xmm0, dword ptr [ebp - 0x230]
0051c40f subss xmm3, xmm1
0051c413 push dword ptr [ebp - 0x23c]
0051c419 addss xmm2, xmm0
0051c41d push ecx
0051c41e mov ecx, eax
0051c420 movss dword ptr [ebp - 0x58], xmm3
0051c425 movss dword ptr [ebp - 0x220], xmm2
0051c42d call 0x7cebc0
0051c432 movss xmm7, dword ptr [ebp - 0x24]
0051c437 lea esi, [edi + 0x294]
0051c43d movss xmm6, dword ptr [ebp - 0x28]
0051c442 xorps xmm0, xmm0
0051c445 movss xmm2, dword ptr [esi + 4]
0051c44a movaps xmm5, xmm6
0051c44d addss xmm6, dword ptr [0xb6a9c8]
0051c455 subss xmm5, dword ptr [0xb6a9c8]
0051c45d movss xmm1, dword ptr [esi]
0051c461 movaps xmm4, xmm7
0051c464 addss xmm7, xmm0
0051c468 movaps xmm3, xmm2
0051c46b subss xmm4, xmm0
0051c46f movaps xmm0, xmm1
0051c472 subss xmm1, xmm6
0051c476 movss dword ptr [ebp - 0x4c], xmm6
0051c47b movss xmm6, dword ptr [esi]
0051c47f subss xmm0, xmm5
0051c483 movss dword ptr [ebp - 0x23c], xmm5
0051c48b movss xmm5, dword ptr [ebp - 0x58]
0051c490 subss xmm2, xmm7
0051c494 subss xmm3, xmm4
0051c498 movss dword ptr [ebp - 0x64], xmm4
0051c49d movss xmm4, dword ptr [ebp - 0x220]
0051c4a5 mulss xmm1, xmm5
0051c4a9 mulss xmm2, xmm4
0051c4ad mulss xmm3, xmm4
0051c4b1 mulss xmm0, xmm5
0051c4b5 addss xmm2, xmm1
0051c4b9 movss dword ptr [ebp - 0x24], xmm7
0051c4be movss xmm7, dword ptr [esi + 4]
0051c4c3 addss xmm3, xmm0
0051c4c7 movss dword ptr [ebp - 0x220], xmm2
0051c4cf movss xmm2, dword ptr [ebp - 0x30]
0051c4d4 movss dword ptr [ebp - 0x34], xmm2
0051c4d9 movss dword ptr [ebp - 0x58], xmm3
0051c4de movss xmm0, dword ptr [ebp - 0x220]
0051c4e6 movaps xmm1, xmm3
0051c4e9 andps xmm1, xmmword ptr [0xb6c980]
0051c4f0 andps xmm0, xmmword ptr [0xb6c980]
0051c4f7 comiss xmm0, xmm1
0051c4fa movss xmm3, dword ptr [ebp - 0x238]
0051c502 jbe 0x51c531
0051c504 movss xmm1, dword ptr [ebp - 0x58]
0051c509 movaps xmm0, xmm1
0051c50c mulss xmm1, xmm4
0051c510 mulss xmm0, xmm5
0051c514 subss xmm7, xmm1
0051c518 movaps xmm1, xmm2
0051c51b subss xmm1, dword ptr [ebp - 0x23c]
0051c523 subss xmm6, xmm0
0051c527 movaps xmm0, xmm3
0051c52a subss xmm0, dword ptr [ebp - 0x64]
0051c52f jmp 0x51c55c
0051c531 movss xmm1, dword ptr [ebp - 0x220]
0051c539 movaps xmm0, xmm1
0051c53c mulss xmm1, xmm4
0051c540 mulss xmm0, xmm5
0051c544 subss xmm7, xmm1
0051c548 movaps xmm1, xmm2
0051c54b subss xmm1, dword ptr [ebp - 0x4c]
0051c550 subss xmm6, xmm0
0051c554 movaps xmm0, xmm3
0051c557 subss xmm0, dword ptr [ebp - 0x24]
0051c55c cmp dword ptr [edi + 0xe6c], -1
0051c563 mulss xmm0, xmm4
0051c567 mulss xmm1, xmm5
0051c56b movss dword ptr [ebp - 0x58], xmm7
0051c570 movss dword ptr [ebp - 0x5c], xmm6
0051c575 addss xmm1, xmm0
0051c579 movaps xmm0, xmm1
0051c57c mulss xmm1, xmm4
0051c580 mulss xmm0, xmm5
0051c584 subss xmm3, xmm1
0051c588 subss xmm2, xmm0
0051c58c movss xmm0, dword ptr [ebp - 0x230]
0051c594 mulss xmm0, dword ptr [0xb6a974]
0051c59c subss xmm2, xmm0
0051c5a0 movss xmm0, dword ptr [ebp - 0x228]
0051c5a8 mulss xmm0, dword ptr [0xb6a974]
0051c5b0 subss xmm3, xmm0
0051c5b4 movss dword ptr [ebp - 0x34], xmm2
0051c5b9 movss dword ptr [ebp - 0x30], xmm3
0051c5be jne 0x51c5e2
0051c5c0 mov ecx, dword ptr [ebp - 0x18]
0051c5c3 lea eax, [ebp - 0x34]
0051c5c6 push 0
0051c5c8 push 0
0051c5ca push 0
0051c5cc push 0
0051c5ce push 1
0051c5d0 push eax
0051c5d1 lea eax, [ebp - 0x5c]
0051c5d4 push eax
0051c5d5 call 0x7af4b0
0051c5da test al, al
0051c5dc je 0x51d1ca
0051c5e2 push ecx
0051c5e3 mov dword ptr [esp], 0x3f800000
0051c5ea push 0
0051c5ec push 0x14
0051c5ee push ecx
0051c5ef mov dword ptr [esp], 0x3f800000
0051c5f6 mov ecx, edi
0051c5f8 push 0xe0
0051c5fd call 0x6ad720
0051c602 movss xmm1, dword ptr [ebp - 0x230]
0051c60a movss xmm0, dword ptr [ebp - 0x228]
0051c612 mulss xmm1, dword ptr [0xb6a690]
0051c61a mulss xmm0, dword ptr [0xb6a690]
0051c622 movss dword ptr [edi + 0xb00], xmm1
0051c62a movss dword ptr [edi + 0xb04], xmm0
0051c632 mov dword ptr [edi + 0xab4], 8
0051c63c mov dword ptr [edi + 0x360], 0
0051c646 mov eax, dword ptr [esi]
0051c648 mov dword ptr [edi + 0xb08], eax
0051c64e mov eax, dword ptr [esi + 4]
0051c651 mov dword ptr [edi + 0xb0c], eax
0051c657 mov eax, dword ptr [esi]
0051c659 mov dword ptr [edi + 0xa94], eax
0051c65f mov eax, dword ptr [esi + 4]
0051c662 mov dword ptr [edi + 0xa98], eax
0051c668 mov dword ptr [edi + 0x38c], 0
0051c672 jmp 0x51d1ca
0051c677 push 0
0051c679 push 0x1000a00
0051c67e mov ecx, edi
0051c680 call 0x4122f0
0051c685 test al, al
0051c687 jne 0x51d1c4
0051c68d cmp byte ptr [ebp - 0x222], al
0051c693 jne 0x51d1c4
0051c699 cmp dword ptr [edi + 0xe6c], -1
0051c6a0 jne 0x51c72e
0051c6a6 movss xmm4, dword ptr [ebp - 0x228]
0051c6ae movss xmm2, dword ptr [0xb6c980]
0051c6b6 movaps xmm0, xmm4
0051c6b9 movss xmm3, dword ptr [0xb6a9c8]
0051c6c1 andps xmm0, xmm2
0051c6c4 comiss xmm3, xmm0
0051c6c7 movss xmm1, dword ptr [ebp - 0x220]
0051c6cf ja 0x51c6e0
0051c6d1 movaps xmm0, xmm1
0051c6d4 andps xmm0, xmm2
0051c6d7 comiss xmm3, xmm0
0051c6da jbe 0x51d1c4
0051c6e0 movss xmm0, dword ptr [0xb6ad60]
0051c6e8 mulss xmm1, xmm1
0051c6ec mulss xmm4, xmm4
0051c6f0 addss xmm1, xmm4
0051c6f4 comiss xmm0, xmm1
0051c6f7 ja 0x51c702
0051c6f9 cmp esi, 0x37
0051c6fc jne 0x51d1c4
0051c702 mov ecx, dword ptr [0xbfd65c]
0051c708 lea eax, [ebp - 0x28]
0051c70b push 0
0051c70d push 0
0051c70f push 0
0051c711 mov ecx, dword ptr [ecx + 0x18190]
0051c717 push 0
0051c719 push dword ptr [ebp - 0x18]
0051c71c push eax
0051c71d lea eax, [ebp - 0x68]
0051c720 push eax
0051c721 call 0x7af4b0
0051c726 test al, al
0051c728 je 0x51d1c4
0051c72e mov ecx, dword ptr [edi + 0x28]
0051c731 cmp ecx, 0x37
0051c734 jne 0x51c73d
0051c736 mov eax, 0xdd
0051c73b jmp 0x51c750
0051c73d cmp ecx, 0xed
0051c743 mov eax, 0xe0
0051c748 mov edx, 0x39
0051c74d cmove eax, edx
0051c750 push ecx
0051c751 mov dword ptr [esp], 0x3f800000
0051c758 push 0
0051c75a push 0x14
0051c75c push ecx
0051c75d mov dword ptr [esp], 0x3f800000
0051c764 mov ecx, edi
0051c766 push eax
0051c767 call 0x6ad720
0051c76c cmp dword ptr [edi + 0x28], 0x37
0051c770 jne 0x51c77c
0051c772 movss xmm1, dword ptr [0xb6a700]
0051c77a jmp 0x51c784
0051c77c movss xmm1, dword ptr [0xb6a690]
0051c784 lea edx, [ebp - 0x50]
0051c787 lea ecx, [ebp - 0x1c]
0051c78a call 0x6593a0
0051c78f movaps xmm0, xmm1
0051c792 mulss xmm0, dword ptr [eax]
0051c796 mulss xmm1, dword ptr [eax + 4]
0051c79b movss dword ptr [edi + 0xb00], xmm0
0051c7a3 movss dword ptr [edi + 0xb04], xmm1
0051c7ab mov eax, dword ptr [edi + 0x28]
0051c7ae cmp eax, 0xed
0051c7b3 jne 0x51c7e6
0051c7b5 cmp byte ptr [edi + 0xb8d], 0
0051c7bc je 0x51c813
0051c7be cmp dword ptr [edi + 0x30], 1
0051c7c2 jne 0x51c813
0051c7c4 mulss xmm0, dword ptr [0xb6a6f0]
0051c7cc movss dword ptr [edi + 0xb00], xmm0
0051c7d4 movss xmm0, dword ptr [edi + 0xb04]
0051c7dc mulss xmm0, dword ptr [0xb6a6f0]
0051c7e4 jmp 0x51c83c
0051c7e6 cmp eax, 0x17
0051c7e9 jne 0x51c813
0051c7eb cmp dword ptr [edi + 0x2c], 1
0051c7ef jne 0x51c813
0051c7f1 mulss xmm0, dword ptr [0xb6a5a4]
0051c7f9 movss dword ptr [edi + 0xb00], xmm0
0051c801 movss xmm0, dword ptr [edi + 0xb04]
0051c809 mulss xmm0, dword ptr [0xb6a5a4]
0051c811 jmp 0x51c83c
0051c813 cmp byte ptr [ebp - 0x221], 0
0051c81a je 0x51c844
0051c81c mulss xmm0, dword ptr [0xb6a9a0]
0051c824 movss dword ptr [edi + 0xb00], xmm0
0051c82c movss xmm0, dword ptr [edi + 0xb04]
0051c834 mulss xmm0, dword ptr [0xb6a9a0]
0051c83c movss dword ptr [edi + 0xb04], xmm0
0051c844 cmp byte ptr [ebp - 0x221], 0
0051c84b lea esi, [edi + 0x294]
0051c851 mov dword ptr [edi + 0xab4], 8
0051c85b mov eax, dword ptr [esi]
0051c85d mov dword ptr [edi + 0xa94], eax
0051c863 mov eax, dword ptr [esi + 4]
0051c866 mov dword ptr [edi + 0xa98], eax
0051c86c mov dword ptr [edi + 0x38c], 0
0051c876 mov dword ptr [edi + 0x360], 0
0051c880 mov eax, dword ptr [esi]
0051c882 mov dword ptr [edi + 0xb08], eax
0051c888 mov eax, dword ptr [esi + 4]
0051c88b mov dword ptr [edi + 0xb0c], eax
0051c891 je 0x51d1ca
0051c897 movss xmm4, dword ptr [edi + 0xb00]
0051c89f xor ecx, ecx
0051c8a1 movss xmm3, dword ptr [edi + 0xb04]
0051c8a9 movaps xmm1, xmm4
0051c8ac andps xmm1, xmmword ptr [0xb6c980]
0051c8b3 movaps xmm0, xmm3
0051c8b6 andps xmm0, xmmword ptr [0xb6c980]
0051c8bd comiss xmm1, xmm0
0051c8c0 xorps xmm0, xmm0
0051c8c3 jbe 0x51c908
0051c8c5 comiss xmm0, xmm4
0051c8c8 mov dword ptr [ebp - 0x21c], ecx
0051c8ce seta al
0051c8d1 mov byte ptr [edi + 0x13c], al
0051c8d7 test al, al
0051c8d9 je 0x51c915
0051c8db movss xmm0, dword ptr [edi + 0xe0]
0051c8e3 mulss xmm0, dword ptr [0xb6ae44]
0051c8eb push ecx
0051c8ec push dword ptr [ebp + ecx*4 - 0x88]
0051c8f3 lea ecx, [edi + 0x3c]
0051c8f6 movss dword ptr [edi + 0xe0], xmm0
0051c8fe call 0x4054f0
0051c903 jmp 0x51d1ca
0051c908 comiss xmm0, xmm3
0051c90b setbe cl
0051c90e inc ecx
0051c90f mov dword ptr [ebp - 0x21c], ecx
0051c915 push 0
0051c917 push dword ptr [ebp + ecx*4 - 0x88]
0051c91e lea ecx, [edi + 0x3c]
0051c921 call 0x4054f0
0051c926 jmp 0x51d1ca
0051c92b mov eax, dword ptr [edi + 0x28]
0051c92e cmp eax, 0x1f
0051c931 je 0x51c93e
0051c933 cmp eax, 0xf3
0051c938 jne 0x51d1c4
0051c93e cmp dword ptr [edi + 0xe6c], -1
0051c945 je 0x51c95f
0051c947 movss xmm1, dword ptr [0xb6accc]
0051c94f mov ecx, edi
0051c951 push 7
0051c953 push 0
0051c955 call 0x6a15a0
0051c95a movzx edx, al
0051c95d jmp 0x51c972
0051c95f call 0x6c3d90
0051c964 xor edx, edx
0051c966 mov ecx, 0x23
0051c96b div ecx
0051c96d neg edx
0051c96f sbb edx, edx
0051c971 inc edx
0051c972 test edx, edx
0051c974 je 0x51d1c4
0051c97a push 0
0051c97c push 0x1000a00
0051c981 mov ecx, edi
0051c983 call 0x4122f0
0051c988 test al, al
0051c98a jne 0x51d1c4
0051c990 push 1
0051c992 mov ecx, edi
0051c994 call 0x6afe20
0051c999 cmp dword ptr [edi + 0x28], 0x1f
0051c99d mov eax, dword ptr [ebp - 0x21c]
0051c9a3 mov dword ptr [edi + 0xab4], 9
0051c9ad mov dword ptr [edi + 0x360], 0
0051c9b7 jne 0x51c9bf
0051c9b9 mov eax, dword ptr [ebp + eax*4 - 0x54]
0051c9bd jmp 0x51c9c3
0051c9bf mov eax, dword ptr [ebp + eax*4 - 0x2c]
0051c9c3 push 1
0051c9c5 push eax
0051c9c6 lea ecx, [edi + 0x3c]
0051c9c9 call 0x4054f0
0051c9ce mov edx, dword ptr [ebp - 0x21c]
0051c9d4 lea esi, [edi + 0x294]
0051c9da mov dword ptr [edi + 0xb10], edx
0051c9e0 jmp 0x51d1d0
0051c9e5 cmp ecx, 8
0051c9e8 jne 0x51d252
0051c9ee cmp byte ptr [ebp - 0x221], 0
0051c9f5 je 0x51cd96
0051c9fb movss xmm0, dword ptr [edi + 0x2c4]
0051ca03 lea ecx, [edi + 0x3c]
0051ca06 mulss xmm0, xmm1
0051ca0a movss dword ptr [edi + 0x2c4], xmm0
0051ca12 cmp dword ptr [edi + 0x70], 0
0051ca16 je 0x51ca21
0051ca18 cmp byte ptr [edi + 0x80], 0
0051ca1f jne 0x51ca34
0051ca21 push 0
0051ca23 push dword ptr [ebp + eax*4 - 0x54]
0051ca27 call 0x4054f0
0051ca2c movss xmm6, dword ptr [0xb6ae44]
0051ca34 lea ecx, [edi + 0x6c]
0051ca37 call 0x402350
0051ca3c test al, al
0051ca3e je 0x51d1c4
0051ca44 cmp byte ptr [edi + 0x188], 0
0051ca4b je 0x51ca75
0051ca4d movss xmm0, dword ptr [edi + 0xb00]
0051ca55 mulss xmm0, xmm6
0051ca59 movss dword ptr [edi + 0xb00], xmm0
0051ca61 movss xmm0, dword ptr [edi + 0xb04]
0051ca69 mulss xmm0, xmm6
0051ca6d movss dword ptr [edi + 0xb04], xmm0
0051ca75 cmp dword ptr [edi + 0x360], 0x2d
0051ca7c jle 0x51cada
0051ca7e movss xmm1, dword ptr [edi + 0xb04]
0051ca86 movss xmm0, dword ptr [edi + 0xb00]
0051ca8e mulss xmm0, xmm0
0051ca92 mulss xmm1, xmm1
0051ca96 addss xmm0, xmm1
0051ca9a call 0x4228c0
0051ca9f movss xmm1, dword ptr [0xb6a7b0]
0051caa7 comiss xmm1, xmm0
0051caaa jbe 0x51cada
0051caac lea ecx, [edi + 0x364]
0051cab2 call 0x7a6de0
0051cab7 mov eax, dword ptr [ebp - 0x21c]
0051cabd lea ecx, [edi + 0x3c]
0051cac0 push 0
0051cac2 push dword ptr [ebp + eax*4 - 0x38]
0051cac6 call 0x4054f0
0051cacb mov dword ptr [edi + 0xab4], 0x10
0051cad5 jmp 0x51cc84
0051cada movss xmm1, dword ptr [edi + 0x2f4]
0051cae2 movss xmm0, dword ptr [0xb6a34c]
0051caea mov dword ptr [edi + 0x2c4], 0x3f800000
0051caf4 call 0x65c960
0051caf9 movss xmm5, dword ptr [0xb6a614]
0051cb01 lea eax, [ebp - 0x18]
0051cb04 movss xmm1, dword ptr [edi + 0x2b8]
0051cb0c lea ecx, [ebp - 0x24]
0051cb0f movss xmm3, dword ptr [edi + 0xb04]
0051cb17 movaps xmm4, xmm5
0051cb1a movss xmm2, dword ptr [edi + 0x2bc]
0051cb22 subss xmm4, xmm0
0051cb26 movss xmm0, dword ptr [edi + 0xb00]
0051cb2e subss xmm3, xmm2
0051cb32 subss xmm0, xmm1
0051cb36 mov dword ptr [ebp - 0x18], 0
0051cb3d mulss xmm3, xmm4
0051cb41 mulss xmm0, xmm4
0051cb45 addss xmm3, xmm2
0051cb49 addss xmm0, xmm1
0051cb4d xorps xmm1, xmm1
0051cb50 movss dword ptr [edi + 0x2bc], xmm3
0051cb58 movss dword ptr [edi + 0x2b8], xmm0
0051cb60 movd xmm0, dword ptr [edi + 0x360]
0051cb68 cvtdq2ps xmm0, xmm0
0051cb6b subss xmm0, dword ptr [0xb6a974]
0051cb73 divss xmm0, dword ptr [0xb6aab4]
0051cb7b comiss xmm1, xmm0
0051cb7e movss dword ptr [ebp - 0x24], xmm0
0051cb83 cmovbe eax, ecx
0051cb86 movss xmm0, dword ptr [eax]
0051cb8a comiss xmm0, xmm5
0051cb8d ja 0x51cb95
0051cb8f movss xmm0, xmm0
0051cb93 jmp 0x51cb99
0051cb95 movss xmm0, xmm5
0051cb99 lea eax, [ebp - 0x1c]
0051cb9c mov ecx, dword ptr [0xbfd65c]
0051cba2 mulss xmm0, dword ptr [0xb6a27c]
0051cbaa movaps xmm1, xmm5
0051cbad push dword ptr [ebp - 0x23c]
0051cbb3 subss xmm1, xmm0
0051cbb7 push eax
0051cbb8 movaps xmm0, xmm1
0051cbbb mulss xmm1, dword ptr [edi + 0xb04]
0051cbc3 mulss xmm0, dword ptr [edi + 0xb00]
0051cbcb movss dword ptr [edi + 0xb04], xmm1
0051cbd3 movss dword ptr [edi + 0xb00], xmm0
0051cbdb mov ecx, dword ptr [ecx + 0x18190]
0051cbe1 call 0x7cebc0
0051cbe6 cmp dword ptr [edi + 0xe6c], -1
0051cbed je 0x51cc01
0051cbef movss xmm3, dword ptr [edi + 0xb08]
0051cbf7 movss xmm4, dword ptr [edi + 0xb0c]
0051cbff jmp 0x51cc0b
0051cc01 movss xmm4, dword ptr [ebp - 0x18]
0051cc06 movss xmm3, dword ptr [ebp - 0x1c]
0051cc0b movss xmm1, dword ptr [edi + 0x2b8]
0051cc13 movss xmm0, dword ptr [edi + 0x2bc]
0051cc1b andps xmm1, xmmword ptr [0xb6c980]
0051cc22 andps xmm0, xmmword ptr [0xb6c980]
0051cc29 comiss xmm0, xmm1
0051cc2c jbe 0x51cc4c
0051cc2e movss xmm0, dword ptr [esi]
0051cc32 mulss xmm3, dword ptr [0xb6a2cc]
0051cc3a mulss xmm0, dword ptr [0xb6a5a4]
0051cc42 addss xmm3, xmm0
0051cc46 movss dword ptr [esi], xmm3
0051cc4a jmp 0x51cc70
0051cc4c movss xmm0, dword ptr [edi + 0x298]
0051cc54 mulss xmm4, dword ptr [0xb6a2cc]
0051cc5c mulss xmm0, dword ptr [0xb6a5a4]
0051cc64 addss xmm4, xmm0
0051cc68 movss dword ptr [edi + 0x298], xmm4
0051cc70 mov eax, dword ptr [ebp - 0x21c]
0051cc76 lea ecx, [edi + 0x3c]
0051cc79 push 0
0051cc7b push dword ptr [ebp + eax*4 - 0x54]
0051cc7f call 0x4054f0
0051cc84 call 0x6c3d90
0051cc89 xor edx, edx
0051cc8b mov ecx, 0xa
0051cc90 div ecx
0051cc92 test edx, edx
0051cc94 jne 0x51ccf1
0051cc96 call 0x6c3d90
0051cc9b push ecx
0051cc9c mov ecx, edi
0051cc9e movd xmm0, eax
0051cca2 cvtdq2pd xmm0, xmm0
0051cca6 shr eax, 0x1f
0051cca9 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
0051ccb2 cvtpd2ps xmm0, xmm0
0051ccb6 mulss xmm0, dword ptr [0xb6a19c]
0051ccbe mulss xmm0, dword ptr [0xb6a480]
0051ccc6 addss xmm0, dword ptr [0xb6a350]
0051ccce movss dword ptr [esp], xmm0
0051ccd3 call 0x68d7b0
0051ccd8 push 1
0051ccda push 0
0051ccdc push 0xff
0051cce1 mov edx, dword ptr [eax]
0051cce3 lea ecx, [edi + 0x1dc]
0051cce9 push -1
0051cceb push ecx
0051ccec mov ecx, eax
0051ccee call dword ptr [edx + 0x38]
0051ccf1 push 0
0051ccf3 push 3
0051ccf5 mov ecx, edi
0051ccf7 call 0x684790
0051ccfc test al, al
0051ccfe jne 0x51d1c4
0051cd04 call 0x6c3d90
0051cd09 mov ecx, dword ptr [0xbfd65c]
0051cd0f push 0
0051cd11 push 0xbeaaec
0051cd16 push 0xbeab18
0051cd1b push 0
0051cd1d push eax
0051cd1e push 0
0051cd20 push edi
0051cd21 push 0xc02fec
0051cd26 push esi
0051cd27 push 0x1a
0051cd29 push 0x3e8
0051cd2e call 0x422e20
0051cd33 push eax
0051cd34 call 0x9ec34c
0051cd39 add esp, 0x14
0051cd3c mov esi, eax
0051cd3e mov ecx, esi
0051cd40 push edi
0051cd41 call 0x6818e0
0051cd46 movss xmm1, dword ptr [0xbc7a28]
0051cd4e mov ecx, esi
0051cd50 movss xmm0, dword ptr [0xbc7a2c]
0051cd58 mulss xmm1, dword ptr [0xb6a560]
0051cd60 mov eax, dword ptr [esi]
0051cd62 mulss xmm0, dword ptr [0xb6a560]
0051cd6a mov dword ptr [esi + 0x3ac], 0x5a
0051cd74 movss dword ptr [esi + 0xd8], xmm1
0051cd7c mov dword ptr [esi + 0x3b0], 0x5a
0051cd86 movss dword ptr [esi + 0xdc], xmm0
0051cd8e call dword ptr [eax + 0xc]
0051cd91 jmp 0x51d1c4
0051cd96 movss xmm3, dword ptr [esi]
0051cd9a movss xmm2, dword ptr [esi + 4]
0051cd9f movaps xmm1, xmm3
0051cda2 subss xmm2, dword ptr [edi + 0xa98]
0051cdaa subss xmm1, dword ptr [edi + 0xa94]
0051cdb2 movss xmm0, dword ptr [edi + 0x2f4]
0051cdba mulss xmm0, xmm0
0051cdbe mulss xmm2, xmm2
0051cdc2 mulss xmm1, xmm1
0051cdc6 addss xmm2, xmm1
0051cdca divss xmm2, xmm0
0051cdce comiss xmm4, xmm2
0051cdd1 jbe 0x51cded
0051cdd3 cvttss2si ecx, dword ptr [edi + 0x2fc]
0051cddb cvttss2si eax, dword ptr [edi + 0x2f8]
0051cde3 sub ecx, eax
0051cde5 add dword ptr [edi + 0x38c], ecx
0051cdeb jmp 0x51cdf7
0051cded mov dword ptr [edi + 0x38c], 0
0051cdf7 cmp byte ptr [edi + 0x188], 0
0051cdfe movss dword ptr [edi + 0xa94], xmm3
0051ce06 mov eax, dword ptr [edi + 0x298]
0051ce0c mov dword ptr [edi + 0xa98], eax
0051ce12 jne 0x51d21c
0051ce18 push 0
0051ce1a push 0x1000a00
0051ce1f mov ecx, edi
0051ce21 call 0x4122f0
0051ce26 test al, al
0051ce28 jne 0x51d21c
0051ce2e push 0
0051ce30 push 0x80
0051ce35 mov ecx, edi
0051ce37 call 0x4122f0
0051ce3c test al, al
0051ce3e je 0x51ce72
0051ce40 movss xmm1, dword ptr [edi + 0x2bc]
0051ce48 movss xmm0, dword ptr [edi + 0x2b8]
0051ce50 mulss xmm0, xmm0
0051ce54 mulss xmm1, xmm1
0051ce58 addss xmm0, xmm1
0051ce5c call 0x4228c0
0051ce61 movss xmm1, dword ptr [0xb6a864]
0051ce69 comiss xmm1, xmm0
0051ce6c ja 0x51d21c
0051ce72 cmp dword ptr [edi + 0x38c], 5
0051ce79 jg 0x51d21c
0051ce7f cmp byte ptr [ebp - 0x222], 0
0051ce86 jne 0x51d21c
0051ce8c cmp dword ptr [edi + 0x28], 0x17
0051ce90 jne 0x51ce9c
0051ce92 movss xmm0, dword ptr [0xb6a560]
0051ce9a jmp 0x51cea4
0051ce9c movss xmm0, dword ptr [0xb6a5a4]
0051cea4 mulss xmm0, dword ptr [edi + 0x2c4]
0051ceac lea eax, [edi + 0xb00]
0051ceb2 push 0
0051ceb4 push eax
0051ceb5 mov ecx, edi
0051ceb7 mov dword ptr [ebp - 0x18], eax
0051ceba movss dword ptr [edi + 0x2c4], xmm0
0051cec2 call 0x422b60
0051cec7 cmp dword ptr [edi + 0x28], 0x17
0051cecb jne 0x51d0c8
0051ced1 cmp dword ptr [edi + 0x2c], 3
0051ced5 jne 0x51d0c8
0051cedb xorps xmm0, xmm0
0051cede mov ecx, 0xb42540
0051cee3 comiss xmm0, dword ptr [edi + 0xb04]
0051ceea mov eax, 0xb42574
0051ceef push 0
0051cef1 cmovbe eax, ecx
0051cef4 lea ecx, [edi + 0x3c]
0051cef7 push eax
0051cef8 call 0x4054f0
0051cefd mov eax, dword ptr [ebp - 0x18]
0051cf00 xorps xmm0, xmm0
0051cf03 comiss xmm0, dword ptr [eax]
0051cf06 movss xmm0, dword ptr [0xb6a704]
0051cf0e seta al
0051cf11 mov byte ptr [edi + 0x13c], al
0051cf17 call 0x411fe0
0051cf1c movss dword ptr [ebp - 0x18], xmm0
0051cf21 movss xmm0, dword ptr [0xb6a704]
0051cf29 call 0x412010
0051cf2e movss xmm5, dword ptr [edi + 0xb00]
0051cf36 lea eax, [ebp - 0x1c]
0051cf39 movss xmm4, dword ptr [ebp - 0x18]
0051cf3e lea ecx, [ebp - 0x28]
0051cf41 movss xmm3, dword ptr [edi + 0xb04]
0051cf49 movaps xmm2, xmm5
0051cf4c mulss xmm2, xmm4
0051cf50 movaps xmm1, xmm0
0051cf53 push eax
0051cf54 mulss xmm1, xmm3
0051cf58 mulss xmm5, xmm0
0051cf5c mulss xmm4, xmm3
0051cf60 subss xmm2, xmm1
0051cf64 addss xmm5, xmm4
0051cf68 movss dword ptr [ebp - 0x28], xmm2
0051cf6d movss dword ptr [ebp - 0x24], xmm5
0051cf72 call 0x962560
0051cf77 mov ecx, dword ptr [0xbfd65c]
0051cf7d lea eax, [ebp - 0x28]
0051cf80 push dword ptr [ebp - 0x23c]
0051cf86 push eax
0051cf87 mov ecx, dword ptr [ecx + 0x18190]
0051cf8d call 0x7cebc0
0051cf92 cmp dword ptr [edi + 0xe6c], -1
0051cf99 je 0x51cfad
0051cf9b movss xmm6, dword ptr [edi + 0xb08]
0051cfa3 movss xmm0, dword ptr [edi + 0xb0c]
0051cfab jmp 0x51cfb7
0051cfad movss xmm0, dword ptr [ebp - 0x24]
0051cfb2 movss xmm6, dword ptr [ebp - 0x28]
0051cfb7 movss xmm5, dword ptr [esi + 4]
0051cfbc xorps xmm4, xmm4
0051cfbf movss xmm3, dword ptr [esi]
0051cfc3 movaps xmm7, xmm5
0051cfc6 movss dword ptr [ebp - 0x30], xmm0
0051cfcb movaps xmm1, xmm3
0051cfce subss xmm0, xmm4
0051cfd2 subss xmm7, xmm0
0051cfd6 movaps xmm0, xmm6
0051cfd9 subss xmm0, dword ptr [0xb6a9c8]
0051cfe1 addss xmm6, dword ptr [0xb6a9c8]
0051cfe9 mulss xmm7, dword ptr [ebp - 0x18]
0051cfee subss xmm1, xmm0
0051cff2 movss xmm0, dword ptr [ebp - 0x30]
0051cff7 addss xmm0, xmm4
0051cffb movss xmm4, dword ptr [ebp - 0x1c]
0051d000 subss xmm3, xmm6
0051d004 mulss xmm1, dword ptr [ebp - 0x1c]
0051d009 subss xmm5, xmm0
0051d00d mulss xmm3, xmm4
0051d011 addss xmm7, xmm1
0051d015 mulss xmm5, dword ptr [ebp - 0x18]
0051d01a movaps xmm1, xmm7
0051d01d andps xmm1, xmmword ptr [0xb6c980]
0051d024 addss xmm5, xmm3
0051d028 movaps xmm0, xmm5
0051d02b andps xmm0, xmmword ptr [0xb6c980]
0051d032 comiss xmm0, xmm1
0051d035 ja 0x51d03a
0051d037 movaps xmm7, xmm5
0051d03a movss xmm0, dword ptr [ebp - 0x18]
0051d03f movss xmm6, dword ptr [edi + 0x2bc]
0051d047 movss xmm5, dword ptr [edi + 0x2b8]
0051d04f movss xmm1, dword ptr [edi + 0x2f4]
0051d057 mulss xmm0, xmm6
0051d05b mulss xmm4, xmm5
0051d05f addss xmm4, xmm0
0051d063 movss xmm0, dword ptr [0xb6a50c]
0051d06b call 0x65c960
0051d070 movss xmm2, dword ptr [0xb6a614]
0051d078 movss xmm1, dword ptr [ebp - 0x1c]
0051d07d subss xmm2, xmm0
0051d081 movaps xmm0, xmm7
0051d084 mulss xmm1, xmm4
0051d088 mulss xmm0, dword ptr [ebp - 0x1c]
0051d08d mulss xmm7, dword ptr [ebp - 0x18]
0051d092 addss xmm1, xmm0
0051d096 movss xmm0, dword ptr [ebp - 0x18]
0051d09b mulss xmm0, xmm4
0051d09f addss xmm0, xmm7
0051d0a3 mulss xmm1, xmm2
0051d0a7 subss xmm5, xmm1
0051d0ab mulss xmm0, xmm2
0051d0af subss xmm6, xmm0
0051d0b3 movss dword ptr [edi + 0x2b8], xmm5
0051d0bb movss dword ptr [edi + 0x2bc], xmm6
0051d0c3 jmp 0x51d1c4
0051d0c8 push dword ptr [ebp - 0x23c]
0051d0ce lea eax, [ebp - 0x1c]
0051d0d1 push eax
0051d0d2 mov eax, dword ptr [0xbfd65c]
0051d0d7 mov ecx, dword ptr [eax + 0x18190]
0051d0dd call 0x7cebc0
0051d0e2 cmp dword ptr [edi + 0xe6c], -1
0051d0e9 je 0x51d0fd
0051d0eb movss xmm4, dword ptr [edi + 0xb08]
0051d0f3 movss xmm5, dword ptr [edi + 0xb0c]
0051d0fb jmp 0x51d107
0051d0fd movss xmm5, dword ptr [ebp - 0x18]
0051d102 movss xmm4, dword ptr [ebp - 0x1c]
0051d107 mov ecx, dword ptr [edi + 0x28]
0051d10a cmp ecx, 0xed
0051d110 je 0x51d1a3
0051d116 movss xmm1, dword ptr [edi + 0x2f4]
0051d11e movss xmm0, dword ptr [0xb6a50c]
0051d126 call 0x65c960
0051d12b movss xmm2, dword ptr [edi + 0xb00]
0051d133 movaps xmm3, xmm0
0051d136 movss xmm1, dword ptr [edi + 0xb04]
0051d13e andps xmm2, xmmword ptr [0xb6c980]
0051d145 andps xmm1, xmmword ptr [0xb6c980]
0051d14c comiss xmm1, xmm2
0051d14f movss xmm0, dword ptr [0xb6a614]
0051d157 subss xmm0, xmm3
0051d15b jbe 0x51d17f
0051d15d subss xmm4, dword ptr [esi]
0051d161 movss xmm1, dword ptr [edi + 0x2b8]
0051d169 subss xmm4, xmm1
0051d16d mulss xmm4, xmm0
0051d171 addss xmm4, xmm1
0051d175 movss dword ptr [edi + 0x2b8], xmm4
0051d17d jmp 0x51d1a3
0051d17f subss xmm5, dword ptr [edi + 0x298]
0051d187 movss xmm1, dword ptr [edi + 0x2bc]
0051d18f subss xmm5, xmm1
0051d193 mulss xmm5, xmm0
0051d197 addss xmm5, xmm1
0051d19b movss dword ptr [edi + 0x2bc], xmm5
0051d1a3 mov eax, dword ptr [ebp - 0x21c]
0051d1a9 push 0
0051d1ab cmp ecx, 0x37
0051d1ae je 0x51d213
0051d1b0 cmp ecx, 0xed
0051d1b6 lea ecx, [edi + 0x3c]
0051d1b9 je 0x51d20d
0051d1bb push dword ptr [ebp + eax*4 - 0x54]
0051d1bf call 0x4054f0
0051d1c4 lea esi, [edi + 0x294]
0051d1ca mov edx, dword ptr [ebp - 0x21c]
0051d1d0 cvttss2si eax, dword ptr [edi + 0x2f8]
0051d1d8 cvttss2si ecx, dword ptr [edi + 0x2fc]
0051d1e0 sub ecx, eax
0051d1e2 mov eax, dword ptr [edi + 0x28]
0051d1e5 add dword ptr [edi + 0x360], ecx
0051d1eb cmp eax, 0xed
0051d1f0 jne 0x51d784
0051d1f6 movss xmm0, dword ptr [0xb6a614]
0051d1fe mov dword ptr [edi + 0xe80], 0
0051d208 jmp 0x51d7e4
0051d20d push dword ptr [ebp + eax*4 - 0x7c]
0051d211 jmp 0x51d1bf
0051d213 push dword ptr [ebp + eax*4 - 0x44]
0051d217 lea ecx, [edi + 0x3c]
0051d21a jmp 0x51d1bf
0051d21c lea ecx, [edi + 0x364]
0051d222 call 0x7a6de0
0051d227 cmp dword ptr [edi + 0x28], 0xed
0051d22e jne 0x51befa
0051d234 push 0
0051d236 push 0xb404bc
0051d23b lea ecx, [edi + 0x3c]
0051d23e call 0x4054f0
0051d243 mov dword ptr [edi + 0xab4], 3
0051d24d jmp 0x51d1c4
0051d252 cmp ecx, 9
0051d255 jne 0x51d612
0051d25b movss xmm0, dword ptr [edi + 0x2c4]
0051d263 mov ecx, edi
0051d265 mulss xmm0, xmm3
0051d269 push 0
0051d26b movss dword ptr [edi + 0x2c4], xmm0
0051d273 call 0x6afe20
0051d278 lea ecx, [edi + 0x3c]
0051d27b push 0xb400ac
0051d280 call 0x4060f0
0051d285 test al, al
0051d287 je 0x51d62b
0051d28d push ecx
0051d28e mov dword ptr [esp], 0x3f800000
0051d295 push 0
0051d297 push 2
0051d299 push ecx
0051d29a mov dword ptr [esp], 0x3f800000
0051d2a1 mov ecx, edi
0051d2a3 push 0xb2
0051d2a8 call 0x6ad720
0051d2ad push ecx
0051d2ae mov dword ptr [esp], 0x3f800000
0051d2b5 push 0
0051d2b7 push 2
0051d2b9 push ecx
0051d2ba mov dword ptr [esp], 0x3f800000
0051d2c1 mov ecx, edi
0051d2c3 push 0x13f
0051d2c8 call 0x6ad720
0051d2cd lea ecx, [ebp - 0x218]
0051d2d3 call 0x430d70
0051d2d8 cmp dword ptr [edi + 0xe6c], -1
0051d2df mov eax, 2
0051d2e4 mov dword ptr [ebp - 0x214], 0x41600000
0051d2ee mov dword ptr [ebp - 0x210], 0xbdcccccd
0051d2f8 mov dword ptr [ebp - 0x20c], 0xbdced917
0051d302 mov dword ptr [ebp - 0x230], eax
0051d308 je 0x51d528
0051d30e lea ecx, [edi + 0xe70]
0051d314 call 0x659490
0051d319 mov dword ptr [ebp - 0x230], eax
0051d31f mov byte ptr [edi + 0x13c], 0
0051d326 cmp eax, 1
0051d329 jne 0x51d32f
0051d32b mov ecx, eax
0051d32d jmp 0x51d346
0051d32f cmp eax, 3
0051d332 jne 0x51d339
0051d334 lea ecx, [eax - 1]
0051d337 jmp 0x51d346
0051d339 xor ecx, ecx
0051d33b test eax, eax
0051d33d sete al
0051d340 mov byte ptr [edi + 0x13c], al
0051d346 cmp dword ptr [edi + 0x28], 0x1f
0051d34a mov dword ptr [ebp - 0x21c], ecx
0051d350 jne 0x51d358
0051d352 mov eax, dword ptr [ebp + ecx*4 - 0x54]
0051d356 jmp 0x51d35c
0051d358 mov eax, dword ptr [ebp + ecx*4 - 0x2c]
0051d35c push eax
0051d35d lea ecx, [edi + 0x3c]
0051d360 call 0x405640
0051d365 test al, al
0051d367 jne 0x51d38a
0051d369 cmp dword ptr [edi + 0x28], 0x1f
0051d36d mov eax, dword ptr [ebp - 0x21c]
0051d373 jne 0x51d37b
0051d375 mov eax, dword ptr [ebp + eax*4 - 0x54]
0051d379 jmp 0x51d37f
0051d37b mov eax, dword ptr [ebp + eax*4 - 0x2c]
0051d37f push 0
0051d381 push eax
0051d382 lea ecx, [edi + 0x3c]
0051d385 call 0x405740
0051d38a mov eax, dword ptr [ebp - 0x230]
0051d390 cmp dword ptr [edi + 0x28], 0x1f
0051d394 jne 0x51d571
0051d39a cmp dword ptr [edi + 0x2c], 1
0051d39e jne 0x51d571
0051d3a4 lea ecx, [ebp - 0x140]
0051d3aa call 0x430d70
0051d3af mov edx, dword ptr [ebp - 0x230]
0051d3b5 lea ecx, [ebp - 0x50]
0051d3b8 mov dword ptr [ebp - 0x13c], 0x41200000
0051d3c2 call 0x659400
0051d3c7 xor ecx, ecx
0051d3c9 mov eax, 0xa
0051d3ce mov dword ptr [ebp - 0x30], ecx
0051d3d1 mov dword ptr [ebp - 0x228], eax
0051d3d7 nop word ptr [eax + eax]
0051d3e0 movss xmm0, dword ptr [0xb6a730]
0051d3e8 movd xmm2, ecx
0051d3ec cvtdq2ps xmm2, xmm2
0051d3ef mov dword ptr [ebp - 0xe8], 0x8000000
0051d3f9 mov dword ptr [ebp - 0xe4], 0
0051d403 movaps xmm1, xmm2
0051d406 mulss xmm1, dword ptr [0xb6a2cc]
0051d40e subss xmm0, xmm1
0051d412 movaps xmm1, xmm2
0051d415 mulss xmm1, dword ptr [0xb6a248]
0051d41d movss dword ptr [ebp - 0x12c], xmm0
0051d425 movss xmm0, dword ptr [0xb6a614]
0051d42d subss xmm0, xmm1
0051d431 movss dword ptr [ebp - 0x11c], xmm0
0051d439 movd xmm0, eax
0051d43d cvtdq2ps xmm0, xmm0
0051d440 mulss xmm0, dword ptr [0xb6a1fc]
0051d448 subss xmm0, dword ptr [0xb6a2ac]
0051d450 movss dword ptr [ebp - 0x134], xmm0
0051d458 call 0x6c3d90
0051d45d movd xmm0, eax
0051d461 cvtdq2pd xmm0, xmm0
0051d465 shr eax, 0x1f
0051d468 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
0051d471 cvtpd2ps xmm0, xmm0
0051d475 mulss xmm0, dword ptr [0xb6a19c]
0051d47d subss xmm0, dword ptr [0xb6a480]
0051d485 mulss xmm0, xmm2
0051d489 mulss xmm0, dword ptr [0xb6a230]
0051d491 movss dword ptr [ebp - 0x18], xmm0
0051d496 call 0x411fe0
0051d49b movss dword ptr [ebp - 0x24], xmm0
0051d4a0 movss xmm0, dword ptr [ebp - 0x18]
0051d4a5 call 0x412010
0051d4aa movss xmm1, dword ptr [ebp - 0x4c]
0051d4af lea eax, [ebp - 0x140]
0051d4b5 movss xmm2, dword ptr [ebp - 0x50]
0051d4ba mov ecx, edi
0051d4bc mulss xmm2, dword ptr [ebp - 0x24]
0051d4c1 push eax
0051d4c2 mulss xmm1, xmm0
0051d4c6 lea eax, [ebp - 0x68]
0051d4c9 push 0
0051d4cb push eax
0051d4cc push esi
0051d4cd subss xmm2, xmm1
0051d4d1 movss xmm1, dword ptr [ebp - 0x50]
0051d4d6 mulss xmm1, xmm0
0051d4da movss xmm0, dword ptr [ebp - 0x4c]
0051d4df mulss xmm0, dword ptr [ebp - 0x24]
0051d4e4 mulss xmm2, dword ptr [0xb6a9bc]
0051d4ec addss xmm1, xmm0
0051d4f0 movss dword ptr [ebp - 0x68], xmm2
0051d4f5 mulss xmm1, dword ptr [0xb6a9bc]
0051d4fd movss dword ptr [ebp - 0x64], xmm1
0051d502 call 0x6a1a20
0051d507 mov eax, dword ptr [ebp - 0x228]
0051d50d mov ecx, dword ptr [ebp - 0x30]
0051d510 dec eax
0051d511 inc ecx
0051d512 mov dword ptr [ebp - 0x228], eax
0051d518 mov dword ptr [ebp - 0x30], ecx
0051d51b test eax, eax
0051d51d jg 0x51d3e0
0051d523 jmp 0x51d62b
0051d528 mov ecx, dword ptr [edi + 0xb10]
0051d52e test ecx, ecx
0051d530 jne 0x51d54b
0051d532 cmp byte ptr [edi + 0x13c], cl
0051d538 je 0x51d390
0051d53e xor eax, eax
0051d540 mov dword ptr [ebp - 0x230], eax
0051d546 jmp 0x51d390
0051d54b cmp ecx, 1
0051d54e jne 0x51d55d
0051d550 mov eax, ecx
0051d552 mov dword ptr [ebp - 0x230], eax
0051d558 jmp 0x51d390
0051d55d cmp ecx, eax
0051d55f cmove eax, dword ptr [ebp - 0x240]
0051d566 mov dword ptr [ebp - 0x230], eax
0051d56c jmp 0x51d390
0051d571 mov edx, eax
0051d573 lea ecx, [ebp - 0x28]
0051d576 call 0x659400
0051d57b mov ecx, edi
0051d57d movss xmm1, dword ptr [eax + 4]
0051d582 movss xmm0, dword ptr [eax]
0051d586 lea eax, [ebp - 0x218]
0051d58c mulss xmm1, dword ptr [0xb6a940]
0051d594 push eax
0051d595 mulss xmm0, dword ptr [0xb6a940]
0051d59d lea eax, [ebp - 0x1c]
0051d5a0 push 0
0051d5a2 push eax
0051d5a3 push esi
0051d5a4 movss dword ptr [ebp - 0x1c], xmm0
0051d5a9 movss dword ptr [ebp - 0x18], xmm1
0051d5ae call 0x6a1a20
0051d5b3 cmp dword ptr [edi + 0x28], 0xf3
0051d5ba jne 0x51d62b
0051d5bc mov edx, dword ptr [ebp - 0x230]
0051d5c2 lea ecx, [ebp - 0x28]
0051d5c5 call 0x659400
0051d5ca mov ecx, edi
0051d5cc movss xmm2, dword ptr [eax + 4]
0051d5d1 movss xmm0, dword ptr [eax]
0051d5d5 lea eax, [ebp - 0x218]
0051d5db xorps xmm0, xmmword ptr [0xb6c9b0]
0051d5e2 xorps xmm2, xmmword ptr [0xb6c9b0]
0051d5e9 mulss xmm0, dword ptr [0xb6a940]
0051d5f1 push eax
0051d5f2 mulss xmm2, dword ptr [0xb6a940]
0051d5fa lea eax, [ebp - 0x1c]
0051d5fd push 0
0051d5ff push eax
0051d600 push esi
0051d601 movss dword ptr [ebp - 0x1c], xmm0
0051d606 movss dword ptr [ebp - 0x18], xmm2
0051d60b call 0x6a1a20
0051d610 jmp 0x51d62b
0051d612 cmp ecx, 0x10
0051d615 jne 0x51d65b
0051d617 movss xmm0, dword ptr [edi + 0x2c4]
0051d61f mulss xmm0, xmm1
0051d623 movss dword ptr [edi + 0x2c4], xmm0
0051d62b push 0xa081d4
0051d630 lea ecx, [edi + 0x3c]
0051d633 call 0x4056c0
0051d638 mov edx, dword ptr [ebp - 0x21c]
0051d63e lea esi, [edi + 0x294]
0051d644 test al, al
0051d646 je 0x51d1d0
0051d64c mov dword ptr [edi + 0xab4], 4
0051d656 jmp 0x51d1d0
0051d65b cmp ecx, 0xd
0051d65e jne 0x51d1c4
0051d664 movss xmm0, dword ptr [edi + 0x2c4]
0051d66c lea ecx, [edi + 0x3c]
0051d66f mulss xmm0, xmm1
0051d673 push 0xb400ac
0051d678 movss dword ptr [edi + 0x2c4], xmm0
0051d680 call 0x4060f0
0051d685 test al, al
0051d687 je 0x51d62b
0051d689 push ecx
0051d68a mov dword ptr [esp], 0x3f800000
0051d691 push 0
0051d693 push 2
0051d695 push ecx
0051d696 mov dword ptr [esp], 0x3f800000
0051d69d mov ecx, edi
0051d69f push 0x25
0051d6a1 call 0x6ad720
0051d6a6 mov eax, dword ptr [edi + 0xb10]
0051d6ac test eax, eax
0051d6ae jne 0x51d6c1
0051d6b0 cmp byte ptr [edi + 0x13c], al
0051d6b6 mov edx, dword ptr [ebp - 0x22c]
0051d6bc cmovne edx, eax
0051d6bf jmp 0x51d6d0
0051d6c1 xor edx, edx
0051d6c3 cmp eax, 1
0051d6c6 setne dl
0051d6c9 lea edx, [edx*2 + 1]
0051d6d0 lea ecx, [ebp - 0x1c]
0051d6d3 call 0x659400
0051d6d8 lea ecx, [edi + 0x334]
0051d6de movss xmm2, dword ptr [eax]
0051d6e2 xorps xmm2, xmmword ptr [0xb6c9b0]
0051d6e9 movss xmm3, dword ptr [eax + 4]
0051d6ee movaps xmm0, xmm2
0051d6f1 mulss xmm0, dword ptr [0xb6a910]
0051d6f9 xorps xmm3, xmmword ptr [0xb6c9b0]
0051d700 mulss xmm2, dword ptr [0xb6a940]
0051d708 movss dword ptr [ebp - 0x1c], xmm0
0051d70d movaps xmm0, xmm3
0051d710 mulss xmm3, dword ptr [0xb6a940]
0051d718 addss xmm2, dword ptr [esi]
0051d71c mulss xmm0, dword ptr [0xb6a910]
0051d724 addss xmm3, dword ptr [esi + 4]
0051d729 movss dword ptr [ebp - 0x18], xmm0
0051d72e movss dword ptr [ebp - 0x28], xmm2
0051d733 movss dword ptr [ebp - 0x24], xmm3
0051d738 call 0x7a7e20
0051d73d mov ecx, dword ptr [0xbfd65c]
0051d743 push eax
0051d744 push 0
0051d746 push edi
0051d747 lea eax, [ebp - 0x1c]
0051d74a push eax
0051d74b lea eax, [ebp - 0x28]
0051d74e push eax
0051d74f push 0
0051d751 push 0xd9
0051d756 call 0x422e20
0051d75b mov esi, eax
0051d75d mov ecx, dword ptr [esi + 0x164]
0051d763 mov edx, dword ptr [esi]
0051d765 and dword ptr [esi + 0x160], 0xfffffffb
0051d76c mov dword ptr [esi + 0x164], ecx
0051d772 mov ecx, esi
0051d774 call dword ptr [edx + 0xc]
0051d777 push esi
0051d778 mov ecx, edi
0051d77a call 0x681920
0051d77f jmp 0x51d62b
0051d784 cmp eax, 0x17
0051d787 jne 0x51d7a9
0051d789 cmp dword ptr [edi + 0x2c], 3
0051d78d jne 0x51d7a9
0051d78f cmp dword ptr [edi + 0xab4], 8
0051d796 jne 0x51d7a9
0051d798 lea eax, [ebp - 0x1c]
0051d79b push eax
0051d79c lea ecx, [edi + 0xb00]
0051d7a2 call 0x962560
0051d7a7 jmp 0x51d7d7
0051d7a9 cmp edx, 1
0051d7ac jne 0x51d7b2
0051d7ae mov eax, edx
0051d7b0 jmp 0x51d7cd
0051d7b2 cmp edx, 2
0051d7b5 jne 0x51d7bc
0051d7b7 lea eax, [edx + 1]
0051d7ba jmp 0x51d7cd
0051d7bc mov eax, dword ptr [ebp - 0x22c]
0051d7c2 xor ecx, ecx
0051d7c4 cmp byte ptr [edi + 0x13c], cl
0051d7ca cmovne eax, ecx
0051d7cd mov edx, eax
0051d7cf lea ecx, [ebp - 0x1c]
0051d7d2 call 0x659400
0051d7d7 mov ecx, dword ptr [eax]
0051d7d9 mov dword ptr [edi + 0xe80], ecx
0051d7df movss xmm0, dword ptr [eax + 4]
0051d7e4 movss dword ptr [edi + 0xe84], xmm0
0051d7ec cmp dword ptr [edi + 0x28], 0xed
0051d7f3 jne 0x51dabf
0051d7f9 movss xmm1, dword ptr [edi + 0x2bc]
0051d801 movss xmm0, dword ptr [edi + 0x2b8]
0051d809 mulss xmm0, xmm0
0051d80d mulss xmm1, xmm1
0051d811 addss xmm0, xmm1
0051d815 comiss xmm0, dword ptr [0xb6a95c]
0051d81c jbe 0x51dabf
0051d822 movss xmm1, dword ptr [0xb6a8f4]
0051d82a xorps xmm2, xmm2
0051d82d mov ecx, edi
0051d82f call 0x6847e0
0051d834 test eax, eax
0051d836 je 0x51d893
0051d838 call 0x6c3d90
0051d83d push ecx
0051d83e mov ecx, edi
0051d840 movd xmm0, eax
0051d844 cvtdq2pd xmm0, xmm0
0051d848 shr eax, 0x1f
0051d84b addsd xmm0, qword ptr [eax*8 + 0xb6c940]
0051d854 cvtpd2ps xmm0, xmm0
0051d858 mulss xmm0, dword ptr [0xb6a19c]
0051d860 mulss xmm0, dword ptr [0xb6a424]
0051d868 addss xmm0, dword ptr [0xb6a350]
0051d870 movss dword ptr [esp], xmm0
0051d875 call 0x68d7b0
0051d87a push 1
0051d87c push 0
0051d87e push 0xff
0051d883 mov edx, dword ptr [eax]
0051d885 lea ecx, [edi + 0x1dc]
0051d88b push -1
0051d88d push ecx
0051d88e mov ecx, eax
0051d890 call dword ptr [edx + 0x38]
0051d893 cmp dword ptr [edi + 0x2c], 0
0051d897 je 0x51d8a6
0051d899 cmp dword ptr [edi + 0xab4], 8
0051d8a0 jne 0x51dabf
0051d8a6 mov al, byte ptr [edi + 0xb8d]
0051d8ac mov byte ptr [ebp - 0x222], al
0051d8b2 test al, al
0051d8b4 je 0x51d8c0
0051d8b6 cmp dword ptr [edi + 0x30], 0
0051d8ba jne 0x51da55
0051d8c0 movss xmm1, dword ptr [0xb6a8f4]
0051d8c8 xorps xmm2, xmm2
0051d8cb mov ecx, edi
0051d8cd call 0x6847e0
0051d8d2 test eax, eax
0051d8d4 je 0x51da4c
0051d8da cmp dword ptr [edi + 0x2c], 2
0051d8de mov dword ptr [ebp - 0x30], 0x16
0051d8e5 jne 0x51d98a
0051d8eb mov dword ptr [ebp - 0x30], 0x5e
0051d8f2 call 0x6c3d90
0051d8f7 xor edx, edx
0051d8f9 div dword ptr [ebp - 0x240]
0051d8ff test edx, edx
0051d901 jne 0x51d98a
0051d907 call 0x6c3d90
0051d90c push ecx
0051d90d movd xmm0, eax
0051d911 cvtdq2pd xmm0, xmm0
0051d915 shr eax, 0x1f
0051d918 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
0051d921 cvtpd2ps xmm0, xmm0
0051d925 mulss xmm0, dword ptr [0xb6a19c]
0051d92d mulss xmm0, dword ptr [0xb6a3b0]
0051d935 addss xmm0, dword ptr [0xb6a614]
0051d93d movss dword ptr [esp], xmm0
0051d942 push 0
0051d944 push 2
0051d946 call 0x6c3d90
0051d94b push ecx
0051d94c mov ecx, edi
0051d94e movd xmm0, eax
0051d952 cvtdq2pd xmm0, xmm0
0051d956 shr eax, 0x1f
0051d959 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
0051d962 cvtpd2ps xmm0, xmm0
0051d966 mulss xmm0, dword ptr [0xb6a19c]
0051d96e mulss xmm0, dword ptr [0xb6a3b0]
0051d976 addss xmm0, dword ptr [0xb6a480]
0051d97e movss dword ptr [esp], xmm0
0051d983 push 0x25
0051d985 call 0x6ad720
0051d98a call 0x6c3d90
0051d98f mov ecx, dword ptr [0xbfd65c]
0051d995 push 0
0051d997 push 0xbeaaec
0051d99c push 0xbeab18
0051d9a1 push 0
0051d9a3 push eax
0051d9a4 push 0
0051d9a6 push edi
0051d9a7 push 0xc02fec
0051d9ac push esi
0051d9ad push dword ptr [ebp - 0x30]
0051d9b0 push 0x3e8
0051d9b5 call 0x422e20
0051d9ba push eax
0051d9bb call 0x9ec34c
0051d9c0 mov esi, eax
0051d9c2 add esp, 0x14
0051d9c5 mov ecx, esi
0051d9c7 mov dword ptr [esi + 0xd8], 0x3f9d70a4
0051d9d1 mov dword ptr [esi + 0xdc], 0x3f9d70a4
0051d9db mov edx, dword ptr [esi]
0051d9dd mov dword ptr [esi + 0x3c4], 0
0051d9e7 call dword ptr [edx + 0xc]
0051d9ea cmp byte ptr [edi + 0xbb3], 0
0051d9f1 je 0x51da11
0051d9f3 mov edx, dword ptr [esi]
0051d9f5 lea eax, [edi + 0x1b0]
0051d9fb push 1
0051d9fd push 0
0051d9ff push 0xff
0051da04 push -1
0051da06 push eax
0051da07 mov ecx, esi
0051da09 call dword ptr [edx + 0x38]
0051da0c jmp 0x51dabf
0051da11 cmp dword ptr [edi + 0x2c], 2
0051da15 je 0x51dabf
0051da1b lea eax, [edi + 0x1b0]
0051da21 push eax
0051da22 lea ecx, [ebp - 0x16c]
0051da28 call 0x402170
0051da2d mov eax, dword ptr [esi]
0051da2f push 1
0051da31 push 0
0051da33 push 0xff
0051da38 push -1
0051da3a push ecx
0051da3b mov ecx, esi
0051da3d mov dword ptr [ebp - 0x160], 0x3f800000
0051da47 call dword ptr [eax + 0x38]
0051da4a jmp 0x51dabf
0051da4c cmp byte ptr [ebp - 0x222], 0
0051da53 je 0x51dabf
0051da55 cmp dword ptr [edi + 0x30], 2
0051da59 jne 0x51dabf
0051da5b movss xmm1, dword ptr [0xb6a9ac]
0051da63 xorps xmm2, xmm2
0051da66 mov ecx, edi
0051da68 call 0x6847e0
0051da6d test eax, eax
0051da6f je 0x51dabf
0051da71 call 0x6c3d90
0051da76 mov ecx, dword ptr [0xbfd65c]
0051da7c push eax
0051da7d push 0
0051da7f push edi
0051da80 push 0xc02fec
0051da85 push esi
0051da86 push 3
0051da88 push 4
0051da8a call 0x422e20
0051da8f push 0x384
0051da94 mov dword ptr [eax + 0x180], 1
0051da9e mov eax, dword ptr [0xbfd65c]
0051daa3 mov esi, dword ptr [eax + 0x18190]
0051daa9 lea eax, [edi + 0x294]
0051daaf push eax
0051dab0 mov ecx, esi
0051dab2 call 0x7ce950
0051dab7 push eax
0051dab8 mov ecx, esi
0051daba call 0x447f40
0051dabf cmp byte ptr [edi + 0x16b], 0
0051dac6 je 0x51dba6
0051dacc cmp dword ptr [edi + 0x28], 0x1f
0051dad0 jne 0x51dba6
0051dad6 cmp dword ptr [edi + 0x2c], 1
0051dada jne 0x51dba6
0051dae0 lea ecx, [ebp - 0x140]
0051dae6 call 0x430d70
0051daeb movss xmm0, dword ptr [edi + 0x294]
0051daf3 lea eax, [ebp - 0x140]
0051daf9 push eax
0051dafa lea esi, [edi + 0x294]
0051db00 movss dword ptr [ebp - 0xd8], xmm0
0051db08 movss xmm0, dword ptr [esi + 4]
0051db0d lea eax, [ebp - 0x1c]
0051db10 push 9
0051db12 push eax
0051db13 push esi
0051db14 mov ecx, edi
0051db16 mov dword ptr [ebp - 0x12c], 0x3fa00000
0051db20 movss dword ptr [ebp - 0xd4], xmm0
0051db28 mov dword ptr [ebp - 0x134], 0xbd8f5c29
0051db32 mov dword ptr [ebp - 0x128], 0
0051db3c mov dword ptr [ebp - 0xe8], 0x800
0051db46 mov dword ptr [ebp - 0xe4], 0
0051db50 mov dword ptr [ebp - 0x1c], 0x41000000
0051db57 mov dword ptr [ebp - 0x18], 0x41000000
0051db5e call 0x6a1a20
0051db63 lea eax, [ebp - 0x140]
0051db69 mov dword ptr [ebp - 0x128], 0x3ec90fdb
0051db73 push eax
0051db74 push 9
0051db76 lea eax, [ebp - 0x1c]
0051db79 mov dword ptr [ebp - 0xe8], 0x1000
0051db83 push eax
0051db84 push esi
0051db85 mov ecx, edi
0051db87 mov dword ptr [ebp - 0xe4], 0
0051db91 mov dword ptr [ebp - 0x1c], 0x41000000
0051db98 mov dword ptr [ebp - 0x18], 0x41000000
0051db9f call 0x6a1a20
0051dba4 jmp 0x51dbac
0051dba6 lea esi, [edi + 0x294]
0051dbac cmp byte ptr [ebp - 0x231], 0
0051dbb3 je 0x51ddd5
0051dbb9 cmp dword ptr [edi + 0xab4], 4
0051dbc0 jne 0x51ddd5
0051dbc6 mov eax, dword ptr [edi + 0x344]
0051dbcc lea ecx, [ebp - 0x7c]
0051dbcf xorps xmm0, xmm0
0051dbd2 mov dword ptr [ebp - 0x7c], eax
0051dbd5 mov eax, dword ptr [0xa08b44]
0051dbda movss dword ptr [ebp - 0x228], xmm0
0051dbe2 movss dword ptr [ebp - 0x22c], xmm0
0051dbea movq xmm0, qword ptr [0xa08b3c]
0051dbf2 movq qword ptr [ebp - 0x78], xmm0
0051dbf7 mov dword ptr [ebp - 0x70], eax
0051dbfa call 0x7a7db0
0051dbff fld dword ptr [0xb6a9ac]
0051dc05 movss xmm1, dword ptr [edi + 0x2bc]
0051dc0d movss xmm0, dword ptr [edi + 0x2b8]
0051dc15 fmul st(1), st(0)
0051dc17 mulss xmm0, xmm0
0051dc1b mov dword ptr [ebp - 0x18], 0x3f4ccccd
0051dc22 mulss xmm1, xmm1
0051dc26 faddp st(1)
0051dc28 addss xmm0, xmm1
0051dc2c fstp dword ptr [ebp - 0x4c]
0051dc2f call 0x4228c0
0051dc34 addss xmm0, dword ptr [0xb6a434]
0051dc3c movss xmm1, dword ptr [0xb6a560]
0051dc44 lea eax, [ebp - 0x18]
0051dc47 lea ecx, [ebp - 0x24]
0051dc4a comiss xmm1, xmm0
0051dc4d movss xmm1, dword ptr [0xb6a7b0]
0051dc55 movss dword ptr [ebp - 0x24], xmm0
0051dc5a cmovbe eax, ecx
0051dc5d movss xmm0, dword ptr [eax]
0051dc61 comiss xmm0, xmm1
0051dc64 ja 0x51dc6c
0051dc66 movss xmm0, xmm0
0051dc6a jmp 0x51dc70
0051dc6c movss xmm0, xmm1
0051dc70 push 0
0051dc72 push 0
0051dc74 lea eax, [ebp - 0x48]
0051dc77 push dword ptr [edi + 0x30]
0051dc7a movss dword ptr [ebp - 0x18], xmm0
0051dc7f push dword ptr [edi + 0x2c]
0051dc82 push dword ptr [edi + 0x28]
0051dc85 push eax
0051dc86 mov eax, dword ptr [0xbfd65c]
0051dc8b mov ecx, dword ptr [eax + 0x18190]
0051dc91 add ecx, 0x1218
0051dc97 call 0x415ed0
0051dc9c xor ecx, ecx
0051dc9e mov dword ptr [ebp - 0x30], ecx
0051dca1 cmp dword ptr [ebp - 0x3c], ecx
0051dca4 jbe 0x51dd84
0051dcaa mov eax, dword ptr [ebp - 0x44]
0051dcad nop dword ptr [eax]
0051dcb0 mov ecx, dword ptr [eax + ecx*4]
0051dcb3 test ecx, ecx
0051dcb5 je 0x51dd74
0051dcbb mov eax, dword ptr [ecx + 0x28]
0051dcbe sub eax, 0xa
0051dcc1 cmp eax, 0x3dd
0051dcc6 ja 0x51dd71
0051dccc cmp ecx, edi
0051dcce je 0x51dd71
0051dcd4 movss xmm1, dword ptr [esi + 4]
0051dcd9 subss xmm1, dword ptr [ecx + 0x298]
0051dce1 movss xmm2, dword ptr [esi]
0051dce5 subss xmm2, dword ptr [ecx + 0x294]
0051dced movaps xmm0, xmm1
0051dcf0 movss dword ptr [ebp - 0x64], xmm1
0051dcf5 mulss xmm0, xmm1
0051dcf9 movaps xmm1, xmm2
0051dcfc movss dword ptr [ebp - 0x24], xmm2
0051dd01 mulss xmm1, xmm2
0051dd05 addss xmm0, xmm1
0051dd09 call 0x4228c0
0051dd0e movaps xmm1, xmm0
0051dd11 comiss xmm1, dword ptr [0xb6a18c]
0051dd18 jbe 0x51dd71
0051dd1a movss xmm0, dword ptr [ebp - 0x4c]
0051dd1f comiss xmm0, xmm1
0051dd22 jbe 0x51dd71
0051dd24 movss xmm2, dword ptr [ebp - 0x18]
0051dd29 comiss xmm2, dword ptr [0xb6a2cc]
0051dd30 mov eax, dword ptr [ebp - 0x44]
0051dd33 jbe 0x51dd74
0051dd35 movss xmm0, dword ptr [ebp - 0x24]
0051dd3a divss xmm0, xmm1
0051dd3e mulss xmm0, xmm2
0051dd42 addss xmm0, dword ptr [ebp - 0x22c]
0051dd4a movss dword ptr [ebp - 0x22c], xmm0
0051dd52 movss xmm0, dword ptr [ebp - 0x64]
0051dd57 divss xmm0, xmm1
0051dd5b mulss xmm0, xmm2
0051dd5f addss xmm0, dword ptr [ebp - 0x228]
0051dd67 movss dword ptr [ebp - 0x228], xmm0
0051dd6f jmp 0x51dd74
0051dd71 mov eax, dword ptr [ebp - 0x44]
0051dd74 mov ecx, dword ptr [ebp - 0x30]
0051dd77 inc ecx
0051dd78 mov dword ptr [ebp - 0x30], ecx
0051dd7b cmp ecx, dword ptr [ebp - 0x3c]
0051dd7e jb 0x51dcb0
0051dd84 cmp byte ptr [ebp - 0x48], 0
0051dd88 movss xmm0, dword ptr [edi + 0x2f4]
0051dd90 movss xmm1, dword ptr [ebp - 0x22c]
0051dd98 mulss xmm1, xmm0
0051dd9c addss xmm1, dword ptr [edi + 0x2b8]
0051dda4 movss dword ptr [edi + 0x2b8], xmm1
0051ddac movss xmm1, dword ptr [ebp - 0x228]
0051ddb4 mulss xmm1, xmm0
0051ddb8 addss xmm1, dword ptr [edi + 0x2bc]
0051ddc0 movss dword ptr [edi + 0x2bc], xmm1
0051ddc8 jne 0x51ddd5
0051ddca push dword ptr [ebp - 0x44]
0051ddcd call 0x9eace5
0051ddd2 add esp, 4
0051ddd5 mov ecx, dword ptr [ebp - 0xc]
0051ddd8 mov dword ptr fs:[0], ecx
0051dddf pop ecx
0051dde0 pop edi
0051dde1 pop esi
0051dde2 mov ecx, dword ptr [ebp - 0x14]
0051dde5 xor ecx, ebp
0051dde7 call 0x9eacd7
0051ddec mov esp, ebp
0051ddee pop ebp
0051ddef mov esp, ebx
0051ddf1 pop ebx
0051ddf2 ret 
