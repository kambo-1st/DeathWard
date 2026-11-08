0067ae90 push ebp
0067ae91 mov ebp, esp
0067ae93 push -1
0067ae95 push 0x9f4066
0067ae9a mov eax, dword ptr fs:[0]
0067aea0 push eax
0067aea1 sub esp, 0xe4
0067aea7 mov eax, dword ptr [0xbaa3b4]
0067aeac xor eax, ebp
0067aeae mov dword ptr [ebp - 0x10], eax
0067aeb1 push esi
0067aeb2 push edi
0067aeb3 push eax
0067aeb4 lea eax, [ebp - 0xc]
0067aeb7 mov dword ptr fs:[0], eax
0067aebd mov edi, ecx
0067aebf mov dword ptr [ebp - 0x74], edi
0067aec2 cmp byte ptr [edi + 0x3b1], 0
0067aec9 je 0x67aed7
0067aecb mov byte ptr [edi + 0x3b1], 0
0067aed2 jmp 0x67e272
0067aed7 cmp byte ptr [edi + 0x3b3], 0
0067aede je 0x67aee5
0067aee0 call 0x67f870
0067aee5 lea eax, [edi + 0x388]
0067aeeb push 0xbc46c0
0067aef0 mov edx, eax
0067aef2 mov dword ptr [ebp - 0x6c], eax
0067aef5 lea ecx, [ebp - 0xa8]
0067aefb call 0x412050
0067af00 add esp, 4
0067af03 mov ecx, dword ptr [eax]
0067af05 or ecx, dword ptr [eax + 4]
0067af08 jne 0x67af16
0067af0a mov ecx, dword ptr [eax + 8]
0067af0d or ecx, dword ptr [eax + 0xc]
0067af10 jne 0x67af16
0067af12 xor cl, cl
0067af14 jmp 0x67af18
0067af16 mov cl, 1
0067af18 mov eax, dword ptr [0xbfd65c]
0067af1d movss xmm0, dword ptr [edi + 0x378]
0067af25 movss xmm5, dword ptr [0xb6ae7c]
0067af2d mov byte ptr [ebp - 0x89], cl
0067af33 mov eax, dword ptr [eax + 0x1a30dc]
0067af39 sub eax, dword ptr [edi + 0x280]
0067af3f movss dword ptr [ebp - 0xb0], xmm0
0067af47 cmp eax, 1
0067af4a jne 0x67af7b
0067af4c cmp dword ptr [edi + 0x34], 1
0067af50 jne 0x67af63
0067af52 mov eax, dword ptr [0xc038f4]
0067af57 mov dword ptr [edi + 0x3a4], eax
0067af5d inc eax
0067af5e mov dword ptr [0xc038f4], eax
0067af63 test cl, cl
0067af65 je 0x67af7b
0067af67 mov dword ptr [edi + 0x36c], 0xc1000000
0067af71 mov dword ptr [edi + 0x2a8], 0xc0400000
0067af7b cmp byte ptr [edi + 0x16b], 0
0067af82 je 0x67afe6
0067af84 movss xmm0, dword ptr [0xc02fec]
0067af8c mov ecx, edi
0067af8e movss dword ptr [edi + 0x2b8], xmm0
0067af96 movss xmm0, dword ptr [0xc02ff0]
0067af9e movss dword ptr [edi + 0x2bc], xmm0
0067afa6 call 0x6860a0
0067afab mov eax, dword ptr [edi + 0x3a8]
0067afb1 test eax, eax
0067afb3 jle 0x67afc1
0067afb5 dec eax
0067afb6 mov dword ptr [edi + 0x3a8], eax
0067afbc jmp 0x67e272
0067afc1 cmp dword ptr [edi + 0x70], 0
0067afc5 je 0x67afda
0067afc7 cmp byte ptr [edi + 0x80], 0
0067afce je 0x67afda
0067afd0 cmp dword ptr [edi + 0x2c], 2
0067afd4 jne 0x67e272
0067afda mov eax, dword ptr [edi]
0067afdc mov ecx, edi
0067afde call dword ptr [eax + 0x28]
0067afe1 jmp 0x67e272
0067afe6 mov ecx, dword ptr [edi + 0x354]
0067afec movss xmm1, dword ptr [0xb6a4c4]
0067aff4 test ecx, ecx
0067aff6 je 0x67b053
0067aff8 movss xmm0, dword ptr [edi + 0x2c4]
0067b000 mov eax, dword ptr [edi + 0x360]
0067b006 mulss xmm0, xmm1
0067b00a movss dword ptr [edi + 0x2c4], xmm0
0067b012 test eax, eax
0067b014 jle 0x67b01d
0067b016 inc eax
0067b017 mov dword ptr [edi + 0x360], eax
0067b01d cmp dword ptr [edi + 0x70], 0
0067b021 je 0x67b02c
0067b023 cmp byte ptr [edi + 0x80], 0
0067b02a jne 0x67b053
0067b02c cmp ecx, 1
0067b02f jne 0x67b053
0067b031 cmp dword ptr [edi + 0x314], 0
0067b038 mov dword ptr [edi + 0x354], 2
0067b042 jne 0x67b053
0067b044 mov eax, dword ptr [edi]
0067b046 mov ecx, edi
0067b048 call dword ptr [eax + 0x28]
0067b04b movss xmm5, dword ptr [0xb6ae7c]
0067b053 mov eax, dword ptr [edi + 0x160]
0067b059 and eax, 0x20
0067b05c or eax, 0
0067b05f je 0x67b0bf
0067b061 push 0
0067b063 push 0xb3fd8c
0067b068 lea ecx, [edi + 0x3c]
0067b06b call 0x405850
0067b070 cmp byte ptr [edi + 0x3b2], 0
0067b077 je 0x67b0b3
0067b079 mov eax, 5
0067b07e lea esi, [edi + 0x4bd]
0067b084 mov dword ptr [ebp - 0x70], eax
0067b087 cmp byte ptr [esi], 0
0067b08a je 0x67b0a5
0067b08c lea ecx, [esi - 0xd9]
0067b092 call 0x403d60
0067b097 lea ecx, [esi - 0xb9]
0067b09d call 0x403d60
0067b0a2 mov eax, dword ptr [ebp - 0x70]
0067b0a5 add esi, 0x114
0067b0ab sub eax, 1
0067b0ae mov dword ptr [ebp - 0x70], eax
0067b0b1 jne 0x67b087
0067b0b3 mov ecx, edi
0067b0b5 call 0x6860a0
0067b0ba jmp 0x67e272
0067b0bf cmp byte ptr [edi + 0x169], 0
0067b0c6 xorps xmm2, xmm2
0067b0c9 movss xmm4, dword ptr [0xb6a614]
0067b0d1 movss xmm7, dword ptr [0xb6a7b0]
0067b0d9 movss xmm6, dword ptr [0xb6a560]
0067b0e1 je 0x67b342
0067b0e7 cmp dword ptr [edi + 0x354], 0
0067b0ee jne 0x67b342
0067b0f4 cmp byte ptr [edi + 0x16b], 0
0067b0fb jne 0x67b342
0067b101 movss xmm1, dword ptr [edi + 0x2a8]
0067b109 comiss xmm2, xmm1
0067b10c ja 0x67b11b
0067b10e comiss xmm2, dword ptr [edi + 0x36c]
0067b115 jbe 0x67b342
0067b11b movss xmm0, dword ptr [edi + 0x36c]
0067b123 mov ecx, edi
0067b125 movaps xmm3, xmm0
0067b128 addss xmm3, xmm1
0067b12c movss dword ptr [edi + 0x2a8], xmm3
0067b134 call 0x67ab80
0067b139 mov dl, byte ptr [ebp - 0x89]
0067b13f test al, al
0067b141 je 0x67b15b
0067b143 test dl, dl
0067b145 je 0x67b151
0067b147 movss xmm1, dword ptr [0xb6a70c]
0067b14f jmp 0x67b17d
0067b151 movss xmm1, dword ptr [edi + 0x370]
0067b159 jmp 0x67b17d
0067b15b test dl, dl
0067b15d je 0x67b169
0067b15f movss xmm1, dword ptr [0xb6a820]
0067b167 jmp 0x67b17d
0067b169 movss xmm1, dword ptr [edi + 0x370]
0067b171 ucomiss xmm1, xmm2
0067b174 lahf 
0067b175 test ah, 0x44
0067b178 jp 0x67b17d
0067b17a movaps xmm1, xmm6
0067b17d addss xmm1, xmm0
0067b181 movss dword ptr [edi + 0x36c], xmm1
0067b189 movss xmm0, dword ptr [0xb6aefc]
0067b191 comiss xmm0, xmm3
0067b194 jbe 0x67b1a2
0067b196 mov dword ptr [edi + 0x17c], 3
0067b1a0 jmp 0x67b1cf
0067b1a2 comiss xmm5, xmm3
0067b1a5 ja 0x67b1c5
0067b1a7 cmp byte ptr [edi + 0x398], 0
0067b1ae jne 0x67b1c5
0067b1b0 call 0x67ab80
0067b1b5 test al, al
0067b1b7 jne 0x67b1c5
0067b1b9 mov dword ptr [edi + 0x17c], 5
0067b1c3 jmp 0x67b1cf
0067b1c5 mov dword ptr [edi + 0x17c], 6
0067b1cf comiss xmm3, xmm2
0067b1d2 jb 0x67b342
0067b1d8 test dl, dl
0067b1da je 0x67b2c1
0067b1e0 comiss xmm1, xmm7
0067b1e3 jbe 0x67b2c1
0067b1e9 mov eax, dword ptr [edi + 0x374]
0067b1ef cmp eax, 4
0067b1f2 jge 0x67b2c1
0067b1f8 mulss xmm1, dword ptr [0xb6ae2c]
0067b200 inc eax
0067b201 mov dword ptr [edi + 0x374], eax
0067b207 mov dword ptr [edi + 0x2a8], 0
0067b211 movss dword ptr [edi + 0x36c], xmm1
0067b219 call 0x6c3d90
0067b21e mov ecx, dword ptr [0xbfd65c]
0067b224 add edi, 0x294
0067b22a push eax
0067b22b push 0
0067b22d push 0
0067b22f push 0xc02fec
0067b234 push edi
0067b235 push 0xe
0067b237 push 0x3e8
0067b23c call 0x422e20
0067b241 mov ecx, dword ptr [ebp - 0x74]
0067b244 mov esi, eax
0067b246 push 1
0067b248 push 0
0067b24a push 0xff
0067b24f mov edx, dword ptr [esi]
0067b251 add ecx, 0xe4
0067b257 push -1
0067b259 push ecx
0067b25a mov ecx, esi
0067b25c call dword ptr [edx + 0x38]
0067b25f mov eax, dword ptr [esi]
0067b261 mov ecx, esi
0067b263 call dword ptr [eax + 0xc]
0067b266 movss xmm2, dword ptr [0xb6a480]
0067b26e push ecx
0067b26f mov dword ptr [esp], 0x3f800000
0067b276 push 0
0067b278 push 2
0067b27a push 0x96
0067b27f call 0x8b1480
0067b284 mov ecx, dword ptr [ebp - 0x6c]
0067b287 sub esp, 0x10
0067b28a movss xmm1, dword ptr [0xb6aa3c]
0067b292 mov eax, esp
0067b294 movups xmm0, xmmword ptr [ecx]
0067b297 mov ecx, edi
0067b299 movups xmmword ptr [eax], xmm0
0067b29c mov eax, dword ptr [ebp - 0x74]
0067b29f mov edx, eax
0067b2a1 movss xmm2, dword ptr [eax + 0x368]
0067b2a9 mulss xmm2, dword ptr [0xb6a38c]
0067b2b1 call 0x656e40
0067b2b6 mov edi, dword ptr [ebp - 0x74]
0067b2b9 add esp, 0x10
0067b2bc jmp 0x67b342
0067b2c1 mov ecx, edi
0067b2c3 mov dword ptr [edi + 0x2a8], 0
0067b2cd mov dword ptr [edi + 0x36c], 0
0067b2d7 mov dword ptr [edi + 0x2e0], 0
0067b2e1 call 0x67ab80
0067b2e6 test al, al
0067b2e8 je 0x67b2f6
0067b2ea mov dword ptr [edi + 0x360], 0
0067b2f4 jmp 0x67b342
0067b2f6 cmp dword ptr [edi + 0x2c], 0x12
0067b2fa lea ecx, [edi + 0x384]
0067b300 movss xmm0, dword ptr [ecx]
0067b304 lea eax, [ebp - 0x6c]
0067b307 push ecx
0067b308 mov dword ptr [esp], 0x3f800000
0067b30f push 0
0067b311 mov dword ptr [ebp - 0x6c], 0x3f800000
0067b318 push 2
0067b31a jne 0x67b331
0067b31c comiss xmm0, xmm4
0067b31f push 0x1d2
0067b324 cmovbe eax, ecx
0067b327 movss xmm2, dword ptr [eax]
0067b32b mulss xmm2, xmm6
0067b32f jmp 0x67b33d
0067b331 comiss xmm0, xmm4
0067b334 push 0x28
0067b336 cmovbe eax, ecx
0067b339 movss xmm2, dword ptr [eax]
0067b33d call 0x8b1480
0067b342 mov esi, dword ptr [edi + 0x320]
0067b348 mov dword ptr [ebp - 0xac], esi
0067b34e test esi, esi
0067b350 je 0x67b361
0067b352 xor eax, eax
0067b354 cmp dword ptr [esi + 0x28], 1
0067b358 cmovne esi, eax
0067b35b mov dword ptr [ebp - 0xac], esi
0067b361 mov eax, dword ptr [edi + 0x2c]
0067b364 cmp eax, 0x13
0067b367 je 0x67b36e
0067b369 cmp eax, 0x14
0067b36c jne 0x67b3a8
0067b36e push 0x2000000
0067b373 push 0
0067b375 mov ecx, edi
0067b377 call 0x4122f0
0067b37c test al, al
0067b37e je 0x67b3a5
0067b380 push 0
0067b382 lea ecx, [edi + 0x3c]
0067b385 mov dword ptr [edi + 0xe0], 0
0067b38f push 0xb3fd8c
0067b394 call 0x4054f0
0067b399 mov dword ptr [edi + 0x37c], 0
0067b3a3 jmp 0x67b3db
0067b3a5 mov eax, dword ptr [edi + 0x2c]
0067b3a8 mov ecx, dword ptr [edi + 0x70]
0067b3ab test ecx, ecx
0067b3ad je 0x67b3be
0067b3af cmp byte ptr [edi + 0x80], 0
0067b3b6 je 0x67b3be
0067b3b8 cmp byte ptr [ecx + 0x34], 0
0067b3bc je 0x67b3db
0067b3be cmp eax, 2
0067b3c1 je 0x67b3db
0067b3c3 cmp dword ptr [edi + 0x354], 0
0067b3ca jne 0x67b3db
0067b3cc push 0
0067b3ce push 0xb402f8
0067b3d3 lea ecx, [edi + 0x3c]
0067b3d6 call 0x4054f0
0067b3db cmp dword ptr [edi + 0x70], 0
0067b3df je 0x67b4e4
0067b3e5 cmp byte ptr [edi + 0x80], 0
0067b3ec je 0x67b4e4
0067b3f2 mov eax, dword ptr [edi + 0x70]
0067b3f5 test eax, eax
0067b3f7 je 0x67b403
0067b3f9 cmp dword ptr [eax + 0x14], 0x10
0067b3fd jb 0x67b408
0067b3ff mov eax, dword ptr [eax]
0067b401 jmp 0x67b408
0067b403 mov eax, 0xa081d4
0067b408 mov ecx, 0xb402f8
0067b40d nop dword ptr [eax]
0067b410 mov dl, byte ptr [eax]
0067b412 cmp dl, byte ptr [ecx]
0067b414 jne 0x67b430
0067b416 test dl, dl
0067b418 je 0x67b42c
0067b41a mov dl, byte ptr [eax + 1]
0067b41d cmp dl, byte ptr [ecx + 1]
0067b420 jne 0x67b430
0067b422 add eax, 2
0067b425 add ecx, 2
0067b428 test dl, dl
0067b42a jne 0x67b410
0067b42c xor eax, eax
0067b42e jmp 0x67b435
0067b430 sbb eax, eax
0067b432 or eax, 1
0067b435 test eax, eax
0067b437 jne 0x67b4e4
0067b43d mov ecx, edi
0067b43f call 0x67ab80
0067b444 test al, al
0067b446 jne 0x67b4e4
0067b44c cmp byte ptr [edi + 0x398], al
0067b452 jne 0x67b481
0067b454 cmp dword ptr [edi + 0x34], 1
0067b458 jne 0x67b481
0067b45a test esi, esi
0067b45c je 0x67b481
0067b45e push 0
0067b460 push 0x89
0067b465 mov ecx, esi
0067b467 call 0x73af30
0067b46c test al, al
0067b46e je 0x67b481
0067b470 lea ecx, [edi + 0x3c]
0067b473 call 0x4058f0
0067b478 cmp eax, 0xf
0067b47b jl 0x67b4e4
0067b47d push 0
0067b47f jmp 0x67b4dc
0067b481 cmp dword ptr [edi + 0x360], 0
0067b488 lea eax, [edi + 0x360]
0067b48e lea edx, [ebp - 0x6c]
0067b491 mov dword ptr [ebp - 0x6c], 0
0067b498 lea ecx, [edi + 0x6c]
0067b49b cmovg edx, eax
0067b49e call 0x432ec0
0067b4a3 mov esi, eax
0067b4a5 sub esi, dword ptr [edx]
0067b4a7 sub esi, 1
0067b4aa jns 0x67b4cf
0067b4ac mov eax, 0x88888889
0067b4b1 imul esi
0067b4b3 add edx, esi
0067b4b5 sar edx, 3
0067b4b8 mov eax, edx
0067b4ba shr eax, 0x1f
0067b4bd add eax, edx
0067b4bf mov ecx, eax
0067b4c1 shl ecx, 4
0067b4c4 sub ecx, eax
0067b4c6 mov eax, 0xf
0067b4cb sub eax, ecx
0067b4cd add esi, eax
0067b4cf lea ecx, [edi + 0x3c]
0067b4d2 call 0x4058f0
0067b4d7 cmp esi, eax
0067b4d9 je 0x67b4e4
0067b4db push esi
0067b4dc lea ecx, [edi + 0x3c]
0067b4df call 0x405890
0067b4e4 cmp byte ptr [edi + 0x398], 0
0067b4eb lea esi, [edi + 0x388]
0067b4f1 movss xmm2, dword ptr [0xb6c9b0]
0067b4f9 je 0x67ba3d
0067b4ff push 0xbc4cc0
0067b504 mov edx, esi
0067b506 lea ecx, [ebp - 0xa8]
0067b50c call 0x412050
0067b511 add esp, 4
0067b514 mov ecx, eax
0067b516 call 0x412090
0067b51b test al, al
0067b51d je 0x67b529
0067b51f mov dword ptr [edi + 0x17c], 3
0067b529 mov ecx, edi
0067b52b call 0x67ab80
0067b530 lea ecx, [ebp - 0xa8]
0067b536 mov edx, esi
0067b538 push 0xbc4930
0067b53d test al, al
0067b53f je 0x67b6e9
0067b545 movss xmm0, dword ptr [edi + 0x2fc]
0067b54d subss xmm0, dword ptr [0xb6a614]
0067b555 call 0x412050
0067b55a add esp, 4
0067b55d mov ecx, eax
0067b55f call 0x412090
0067b564 test al, al
0067b566 je 0x67b636
0067b56c mulss xmm0, dword ptr [0xb6a560]
0067b574 movss dword ptr [ebp - 0x74], xmm0
0067b579 call 0x412010
0067b57e movss dword ptr [ebp - 0x70], xmm0
0067b583 movss xmm0, dword ptr [edi + 0x378]
0067b58b addss xmm0, dword ptr [0xb6aae4]
0067b593 mulss xmm0, dword ptr [0xb6a230]
0067b59b movss dword ptr [ebp - 0x6c], xmm0
0067b5a0 call 0x412010
0067b5a5 movss dword ptr [ebp - 0x90], xmm0
0067b5ad movss xmm0, dword ptr [ebp - 0x6c]
0067b5b2 call 0x411fe0
0067b5b7 movss xmm3, dword ptr [ebp - 0x90]
0067b5bf movaps xmm1, xmm0
0067b5c2 mulss xmm1, dword ptr [0xb6a910]
0067b5ca mulss xmm3, dword ptr [0xb6a910]
0067b5d2 mulss xmm1, dword ptr [ebp - 0x70]
0067b5d7 mulss xmm3, dword ptr [ebp - 0x70]
0067b5dc movss xmm0, dword ptr [edi + 0x2f4]
0067b5e4 mulss xmm1, xmm0
0067b5e8 mulss xmm3, xmm0
0067b5ec addss xmm1, dword ptr [edi + 0x2b8]
0067b5f4 movss xmm0, dword ptr [ebp - 0x74]
0067b5f9 addss xmm3, dword ptr [edi + 0x2bc]
0067b601 subss xmm0, dword ptr [0xb6a480]
0067b609 movss dword ptr [edi + 0x2b8], xmm1
0067b611 movss dword ptr [edi + 0x2bc], xmm3
0067b619 call 0x412010
0067b61e mulss xmm0, dword ptr [0xb6a9ec]
0067b626 addss xmm0, dword ptr [edi + 0x378]
0067b62e movss dword ptr [ebp - 0xb0], xmm0
0067b636 movss xmm0, dword ptr [edi + 0x370]
0067b63e ucomiss xmm0, dword ptr [0xb6a18c]
0067b645 lahf 
0067b646 test ah, 0x44
0067b649 jnp 0x67ba3d
0067b64f movss xmm1, dword ptr [edi + 0x2bc]
0067b657 movss xmm0, dword ptr [edi + 0x2b8]
0067b65f mulss xmm0, xmm0
0067b663 mulss xmm1, xmm1
0067b667 addss xmm0, xmm1
0067b66b call 0x4228c0
0067b670 movss dword ptr [ebp - 0x6c], xmm0
0067b675 movss xmm0, dword ptr [ebp - 0xb0]
0067b67d mulss xmm0, dword ptr [0xb6a230]
0067b685 movss dword ptr [ebp - 0xb0], xmm0
0067b68d call 0x412010
0067b692 movss dword ptr [ebp - 0x90], xmm0
0067b69a movss xmm0, dword ptr [ebp - 0xb0]
0067b6a2 call 0x411fe0
0067b6a7 mulss xmm0, dword ptr [ebp - 0x6c]
0067b6ac movss xmm2, dword ptr [ebp - 0x90]
0067b6b4 mulss xmm2, dword ptr [ebp - 0x6c]
0067b6b9 addss xmm0, dword ptr [0xb6a18c]
0067b6c1 addss xmm2, dword ptr [edi + 0x36c]
0067b6c9 movaps xmm1, xmm0
0067b6cc movaps xmm0, xmm2
0067b6cf call 0x447a80
0067b6d4 mulss xmm0, dword ptr [0xb6aa84]
0067b6dc movss dword ptr [ebp - 0xb0], xmm0
0067b6e4 jmp 0x67ba3d
0067b6e9 call 0x412050
0067b6ee add esp, 4
0067b6f1 mov ecx, eax
0067b6f3 call 0x412090
0067b6f8 test al, al
0067b6fa je 0x67b7c2
0067b700 movss xmm0, dword ptr [edi + 0x2b8]
0067b708 lea ecx, [ebp - 0x80]
0067b70b movss xmm1, dword ptr [edi + 0x2bc]
0067b713 xorps xmm0, xmm2
0067b716 movss dword ptr [ebp - 0x80], xmm1
0067b71b movss dword ptr [ebp - 0x7c], xmm0
0067b720 call 0x9624f0
0067b725 mov eax, dword ptr [0xbfd65c]
0067b72a movd xmm0, dword ptr [eax + 0x1a30dc]
0067b732 mov eax, dword ptr [edi + 0x20]
0067b735 cvtdq2ps xmm0, xmm0
0067b738 movd xmm1, eax
0067b73c mulss xmm0, dword ptr [0xb6a50c]
0067b744 shr eax, 0x1f
0067b747 cvtdq2pd xmm1, xmm1
0067b74b addsd xmm1, qword ptr [eax*8 + 0xb6c940]
0067b754 cvtpd2ps xmm1, xmm1
0067b758 addss xmm0, xmm1
0067b75c call 0x412010
0067b761 movss xmm1, dword ptr [edi + 0x2bc]
0067b769 movss dword ptr [ebp - 0x6c], xmm0
0067b76e movss xmm0, dword ptr [edi + 0x2b8]
0067b776 mulss xmm0, xmm0
0067b77a mulss xmm1, xmm1
0067b77e addss xmm0, xmm1
0067b782 call 0x4228c0
0067b787 movss xmm2, dword ptr [ebp - 0x6c]
0067b78c movss xmm1, dword ptr [ebp - 0x7c]
0067b791 mulss xmm2, xmm0
0067b795 movss xmm0, dword ptr [ebp - 0x80]
0067b79a mulss xmm0, xmm2
0067b79e mulss xmm1, xmm2
0067b7a2 addss xmm0, dword ptr [edi + 0x294]
0067b7aa addss xmm1, dword ptr [edi + 0x298]
0067b7b2 movss dword ptr [edi + 0x294], xmm0
0067b7ba movss dword ptr [edi + 0x298], xmm1
0067b7c2 cmp byte ptr [edi + 0x188], 0
0067b7c9 je 0x67b7f5
0067b7cb push 0xbc4ca0
0067b7d0 mov edx, esi
0067b7d2 lea ecx, [ebp - 0xa8]
0067b7d8 call 0x412050
0067b7dd add esp, 4
0067b7e0 mov ecx, eax
0067b7e2 call 0x412090
0067b7e7 test al, al
0067b7e9 je 0x67b7f5
0067b7eb mov dword ptr [edi + 0x360], 0
0067b7f5 push 0xbc46a0
0067b7fa mov edx, esi
0067b7fc lea ecx, [ebp - 0xa8]
0067b802 call 0x412050
0067b807 add esp, 4
0067b80a mov ecx, eax
0067b80c call 0x412090
0067b811 test al, al
0067b813 je 0x67b97a
0067b819 mov eax, dword ptr [edi + 0x314]
0067b81f test eax, eax
0067b821 je 0x67b97a
0067b827 cmp dword ptr [eax + 0x28], 1
0067b82b jne 0x67b97a
0067b831 push 0
0067b833 push 0xbeab9c
0067b838 push 0xbeab18
0067b83d push 0
0067b83f push eax
0067b840 call 0x9ec34c
0067b845 push 0
0067b847 push 0xbeabc8
0067b84c push 0xbeab18
0067b851 push 0
0067b853 push dword ptr [eax + 0x1378]
0067b859 mov dword ptr [ebp - 0x70], eax
0067b85c call 0x9ec34c
0067b861 mov ecx, eax
0067b863 add esp, 0x28
0067b866 test ecx, ecx
0067b868 je 0x67b97a
0067b86e mov eax, dword ptr [ebp - 0x70]
0067b871 movss xmm0, dword ptr [edi + 0x294]
0067b879 subss xmm0, dword ptr [eax + 0x294]
0067b881 movss dword ptr [ebp - 0x90], xmm0
0067b889 movss xmm0, dword ptr [edi + 0x298]
0067b891 movss dword ptr [ebp - 0x98], xmm0
0067b899 subss xmm0, dword ptr [eax + 0x298]
0067b8a1 movss dword ptr [ebp - 0x74], xmm0
0067b8a6 movss xmm0, dword ptr [ecx + 0x36c]
0067b8ae mulss xmm0, dword ptr [0xb6a230]
0067b8b6 movss dword ptr [ebp - 0x6c], xmm0
0067b8bb call 0x412010
0067b8c0 movss dword ptr [ebp - 0x78], xmm0
0067b8c5 movss xmm0, dword ptr [ebp - 0x6c]
0067b8ca call 0x411fe0
0067b8cf movss xmm1, dword ptr [ebp - 0x74]
0067b8d4 movaps xmm3, xmm0
0067b8d7 movss xmm0, dword ptr [ebp - 0x90]
0067b8df movss xmm2, dword ptr [ebp - 0x78]
0067b8e4 mulss xmm1, xmm2
0067b8e8 mulss xmm0, xmm3
0067b8ec addss xmm0, xmm1
0067b8f0 xorps xmm1, xmm1
0067b8f3 comiss xmm0, xmm1
0067b8f6 jbe 0x67b97d
0067b8fc mov eax, dword ptr [ebp - 0x70]
0067b8ff movaps xmm1, xmm0
0067b902 mulss xmm0, xmm2
0067b906 mulss xmm1, xmm3
0067b90a movss xmm2, dword ptr [eax + 0x298]
0067b912 addss xmm2, xmm0
0067b916 addss xmm1, dword ptr [eax + 0x294]
0067b91e subss xmm2, dword ptr [ebp - 0x98]
0067b926 subss xmm1, dword ptr [edi + 0x294]
0067b92e mulss xmm2, dword ptr [0xb6a214]
0067b936 mulss xmm1, dword ptr [0xb6a214]
0067b93e movss dword ptr [ebp - 0x7c], xmm2
0067b943 mulss xmm2, xmm2
0067b947 movss dword ptr [ebp - 0x80], xmm1
0067b94c mulss xmm1, xmm1
0067b950 addss xmm2, xmm1
0067b954 comiss xmm2, dword ptr [0xb6a8cc]
0067b95b jbe 0x67b96d
0067b95d push ecx
0067b95e lea ecx, [ebp - 0x80]
0067b961 mov dword ptr [esp], 0x40000000
0067b968 call 0x962860
0067b96d push 0
0067b96f lea eax, [ebp - 0x80]
0067b972 mov ecx, edi
0067b974 push eax
0067b975 call 0x422b60
0067b97a xorps xmm1, xmm1
0067b97d push 0xbc4920
0067b982 mov edx, esi
0067b984 lea ecx, [ebp - 0xa8]
0067b98a call 0x412050
0067b98f add esp, 4
0067b992 mov ecx, eax
0067b994 call 0x412090
0067b999 test al, al
0067b99b je 0x67ba3d
0067b9a1 mov eax, dword ptr [edi + 0x314]
0067b9a7 test eax, eax
0067b9a9 je 0x67ba3d
0067b9af movss xmm0, dword ptr [eax + 0x294]
0067b9b7 lea ecx, [ebp - 0x80]
0067b9ba movss xmm2, dword ptr [eax + 0x298]
0067b9c2 addss xmm0, xmm1
0067b9c6 addss xmm2, dword ptr [0xb6a7b0]
0067b9ce movss xmm1, dword ptr [edi + 0x294]
0067b9d6 lea eax, [ebp - 0xc8]
0067b9dc push eax
0067b9dd subss xmm1, xmm0
0067b9e1 movss xmm0, dword ptr [edi + 0x298]
0067b9e9 subss xmm0, xmm2
0067b9ed movss dword ptr [ebp - 0x80], xmm1
0067b9f2 movss dword ptr [ebp - 0x7c], xmm0
0067b9f7 call 0x962560
0067b9fc movss xmm0, dword ptr [edi + 0x2b8]
0067ba04 movss xmm1, dword ptr [eax]
0067ba08 mulss xmm1, dword ptr [0xb6a4c4]
0067ba10 movss xmm2, dword ptr [eax + 4]
0067ba15 mulss xmm2, dword ptr [0xb6a4c4]
0067ba1d subss xmm0, xmm1
0067ba21 movss dword ptr [edi + 0x2b8], xmm0
0067ba29 movss xmm0, dword ptr [edi + 0x2bc]
0067ba31 subss xmm0, xmm2
0067ba35 movss dword ptr [edi + 0x2bc], xmm0
0067ba3d push 0xbc4c70
0067ba42 mov edx, esi
0067ba44 lea ecx, [ebp - 0xa8]
0067ba4a call 0x412050
0067ba4f add esp, 4
0067ba52 mov ecx, dword ptr [eax]
0067ba54 or ecx, dword ptr [eax + 4]
0067ba57 jne 0x67ba65
0067ba59 mov ecx, dword ptr [eax + 8]
0067ba5c or ecx, dword ptr [eax + 0xc]
0067ba5f je 0x67bc34
0067ba65 cmp dword ptr [edi + 0x34], 1
0067ba69 jne 0x67bb66
0067ba6f movss xmm3, dword ptr [edi + 0x2c8]
0067ba77 lea eax, [edi + 0x294]
0067ba7d push 8
0067ba7f push eax
0067ba80 lea eax, [ebp - 0x88]
0067ba86 push eax
0067ba87 mov eax, dword ptr [0xbfd65c]
0067ba8c mov ecx, dword ptr [eax + 0x18190]
0067ba92 add ecx, 0x1218
0067ba98 call 0x4157f0
0067ba9d xor ecx, ecx
0067ba9f mov dword ptr [ebp - 4], 0
0067baa6 mov dword ptr [ebp - 0x70], ecx
0067baa9 cmp dword ptr [ebp - 0x7c], ecx
0067baac jbe 0x67bb3f
0067bab2 mov eax, dword ptr [ebp - 0x84]
0067bab8 push 0
0067baba mov esi, dword ptr [eax + ecx*4]
0067babd mov ecx, esi
0067babf call 0x684630
0067bac4 test al, al
0067bac6 je 0x67bb2f
0067bac8 movss xmm0, dword ptr [esi + 0x294]
0067bad0 movss xmm1, dword ptr [esi + 0x298]
0067bad8 subss xmm1, dword ptr [edi + 0x298]
0067bae0 subss xmm0, dword ptr [edi + 0x294]
0067bae8 movss xmm2, dword ptr [esi + 0x2c8]
0067baf0 addss xmm2, dword ptr [edi + 0x2c8]
0067baf8 mulss xmm1, xmm1
0067bafc mulss xmm0, xmm0
0067bb00 mulss xmm2, xmm2
0067bb04 addss xmm1, xmm0
0067bb08 comiss xmm2, xmm1
0067bb0b jbe 0x67bb2f
0067bb0d push edi
0067bb0e lea ecx, [ebp - 0x38]
0067bb11 call 0x4229a0
0067bb16 mov eax, dword ptr [esi]
0067bb18 lea ecx, [ebp - 0x38]
0067bb1b push 0x1e
0067bb1d push ecx
0067bb1e push 0
0067bb20 push 2
0067bb22 push ecx
0067bb23 mov ecx, esi
0067bb25 mov dword ptr [esp], 0x41800000
0067bb2c call dword ptr [eax + 0x20]
0067bb2f mov ecx, dword ptr [ebp - 0x70]
0067bb32 inc ecx
0067bb33 mov dword ptr [ebp - 0x70], ecx
0067bb36 cmp ecx, dword ptr [ebp - 0x7c]
0067bb39 jb 0x67bab2
0067bb3f mov dword ptr [ebp - 4], 0xffffffff
0067bb46 cmp byte ptr [ebp - 0x88], 0
0067bb4d jne 0x67bc34
0067bb53 push dword ptr [ebp - 0x84]
0067bb59 call 0x9eace5
0067bb5e add esp, 4
0067bb61 jmp 0x67bc34
0067bb66 mov eax, dword ptr [0xbfd65c]
0067bb6b xor edx, edx
0067bb6d mov dword ptr [ebp - 0x70], edx
0067bb70 mov ecx, dword ptr [eax + 0x1ba54]
0067bb76 sub ecx, dword ptr [eax + 0x1ba50]
0067bb7c sar ecx, 2
0067bb7f test ecx, ecx
0067bb81 je 0x67bc34
0067bb87 nop word ptr [eax + eax]
0067bb90 mov ecx, dword ptr [0xbfd65c]
0067bb96 push edx
0067bb97 call 0x412750
0067bb9c mov esi, eax
0067bb9e test esi, esi
0067bba0 je 0x67bc11
0067bba2 movss xmm2, dword ptr [edi + 0x2c8]
0067bbaa movss xmm0, dword ptr [esi + 0x294]
0067bbb2 movss xmm1, dword ptr [esi + 0x298]
0067bbba addss xmm2, dword ptr [esi + 0x2c8]
0067bbc2 subss xmm1, dword ptr [edi + 0x298]
0067bbca subss xmm0, dword ptr [edi + 0x294]
0067bbd2 addss xmm2, dword ptr [0xb6a6f0]
0067bbda mulss xmm1, xmm1
0067bbde mulss xmm0, xmm0
0067bbe2 mulss xmm2, xmm2
0067bbe6 addss xmm1, xmm0
0067bbea comiss xmm2, xmm1
0067bbed jbe 0x67bc11
0067bbef push edi
0067bbf0 lea ecx, [ebp - 0x38]
0067bbf3 call 0x4229a0
0067bbf8 mov eax, dword ptr [esi]
0067bbfa lea ecx, [ebp - 0x38]
0067bbfd push 0x1e
0067bbff push ecx
0067bc00 push 0
0067bc02 push 2
0067bc04 push ecx
0067bc05 mov ecx, esi
0067bc07 mov dword ptr [esp], 0x3f800000
0067bc0e call dword ptr [eax + 0x20]
0067bc11 mov eax, dword ptr [0xbfd65c]
0067bc16 mov edx, dword ptr [ebp - 0x70]
0067bc19 inc edx
0067bc1a mov dword ptr [ebp - 0x70], edx
0067bc1d mov ecx, dword ptr [eax + 0x1ba54]
0067bc23 sub ecx, dword ptr [eax + 0x1ba50]
0067bc29 sar ecx, 2
0067bc2c cmp edx, ecx
0067bc2e jb 0x67bb90
0067bc34 lea esi, [edi + 0x388]
0067bc3a push 0xbc4c00
0067bc3f mov edx, esi
0067bc41 lea ecx, [ebp - 0xa8]
0067bc47 call 0x412050
0067bc4c add esp, 4
0067bc4f mov ecx, dword ptr [eax]
0067bc51 or ecx, dword ptr [eax + 4]
0067bc54 jne 0x67bc62
0067bc56 mov ecx, dword ptr [eax + 8]
0067bc59 or ecx, dword ptr [eax + 0xc]
0067bc5c je 0x67bdf6
0067bc62 mov eax, dword ptr [edi + 0x314]
0067bc68 mov dword ptr [ebp - 0x74], eax
0067bc6b test eax, eax
0067bc6d je 0x67bdf6
0067bc73 cmp dword ptr [eax + 0x28], 1
0067bc77 jne 0x67bdf6
0067bc7d lea ecx, [ebp - 0x80]
0067bc80 push ecx
0067bc81 mov ecx, eax
0067bc83 call 0x741b00
0067bc88 mov eax, dword ptr [ebp - 0x74]
0067bc8b mov ecx, dword ptr [eax + 0x1354]
0067bc91 test ecx, ecx
0067bc93 je 0x67bcf4
0067bc95 movss xmm0, dword ptr [ecx + 0x294]
0067bc9d movss xmm1, dword ptr [ecx + 0x298]
0067bca5 subss xmm0, dword ptr [edi + 0x294]
0067bcad subss xmm1, dword ptr [edi + 0x298]
0067bcb5 divss xmm0, dword ptr [0xb6a974]
0067bcbd divss xmm1, dword ptr [0xb6a974]
0067bcc5 movss dword ptr [ebp - 0x80], xmm0
0067bcca movss dword ptr [ebp - 0x7c], xmm1
0067bccf mulss xmm0, xmm0
0067bcd3 mulss xmm1, xmm1
0067bcd7 addss xmm0, xmm1
0067bcdb call 0x4228c0
0067bce0 comiss xmm0, dword ptr [0xb6a614]
0067bce7 jbe 0x67bcf1
0067bce9 lea ecx, [ebp - 0x80]
0067bcec call 0x9624f0
0067bcf1 mov eax, dword ptr [ebp - 0x74]
0067bcf4 movss xmm0, dword ptr [eax + 0x13ac]
0067bcfc mov ecx, eax
0067bcfe mulss xmm0, dword ptr [0xb6a864]
0067bd06 push 0
0067bd08 push 5
0067bd0a movss dword ptr [ebp - 0x74], xmm0
0067bd0f call 0x73af30
0067bd14 test al, al
0067bd16 je 0x67bd2a
0067bd18 movss xmm0, dword ptr [ebp - 0x74]
0067bd1d mulss xmm0, dword ptr [0xb6a480]
0067bd25 movss dword ptr [ebp - 0x74], xmm0
0067bd2a movss xmm0, dword ptr [ebp - 0x80]
0067bd2f xorps xmm1, xmm1
0067bd32 ucomiss xmm0, xmm1
0067bd35 lahf 
0067bd36 test ah, 0x44
0067bd39 jp 0x67bdb0
0067bd3b movss xmm0, dword ptr [ebp - 0x7c]
0067bd40 ucomiss xmm0, xmm1
0067bd43 lahf 
0067bd44 test ah, 0x44
0067bd47 jp 0x67bdb0
0067bd49 push 0xbc4920
0067bd4e mov edx, esi
0067bd50 lea ecx, [ebp - 0xa8]
0067bd56 call 0x412050
0067bd5b add esp, 4
0067bd5e mov ecx, eax
0067bd60 call 0x412090
0067bd65 test al, al
0067bd67 je 0x67bd78
0067bd69 mov dword ptr [edi + 0x2c4], 0x3f800000
0067bd73 jmp 0x67bdf9
0067bd78 push 0xbc4cb0
0067bd7d mov edx, esi
0067bd7f lea ecx, [ebp - 0xa8]
0067bd85 call 0x412050
0067bd8a add esp, 4
0067bd8d mov ecx, eax
0067bd8f call 0x412090
0067bd94 test al, al
0067bd96 je 0x67bda4
0067bd98 mov dword ptr [edi + 0x2c4], 0x3f666666
0067bda2 jmp 0x67bdf9
0067bda4 mov dword ptr [edi + 0x2c4], 0x3f4ccccd
0067bdae jmp 0x67bdf9
0067bdb0 lea ecx, [ebp - 0x80]
0067bdb3 call 0x9624f0
0067bdb8 movss xmm0, dword ptr [ebp - 0x80]
0067bdbd movss xmm1, dword ptr [ebp - 0x7c]
0067bdc2 mulss xmm0, dword ptr [ebp - 0x74]
0067bdc7 mulss xmm1, dword ptr [ebp - 0x74]
0067bdcc addss xmm0, dword ptr [edi + 0x2b8]
0067bdd4 addss xmm1, dword ptr [edi + 0x2bc]
0067bddc movss dword ptr [edi + 0x2b8], xmm0
0067bde4 movss dword ptr [edi + 0x2bc], xmm1
0067bdec mov dword ptr [edi + 0x2c4], 0x3f4ccccd
0067bdf6 xorps xmm1, xmm1
0067bdf9 mov edx, dword ptr [edi + 0x2c]
0067bdfc cmp edx, 0x13
0067bdff je 0x67be0a
0067be01 cmp edx, 0x14
0067be04 jne 0x67bfc9
0067be0a movss xmm2, dword ptr [edi + 0x37c]
0067be12 lea eax, [ebp - 0x90]
0067be18 movss xmm5, dword ptr [0xb6a280]
0067be20 lea ecx, [ebp - 0x6c]
0067be23 movss xmm3, dword ptr [0xb6a614]
0067be2b movaps xmm0, xmm2
0067be2e subss xmm0, xmm1
0067be32 mov dword ptr [ebp - 0x6c], 0
0067be39 mov dword ptr [ebp - 0x70], 0x3f800000
0067be40 mulss xmm0, xmm5
0067be44 comiss xmm1, xmm0
0067be47 movss dword ptr [ebp - 0x90], xmm0
0067be4f cmovbe ecx, eax
0067be52 lea eax, [ebp - 0x70]
0067be55 movss xmm0, dword ptr [ecx]
0067be59 comiss xmm0, xmm3
0067be5c movaps xmm0, xmm2
0067be5f subss xmm0, xmm1
0067be63 cmovbe eax, ecx
0067be66 lea ecx, [ebp - 0x6c]
0067be69 movss xmm4, dword ptr [eax]
0067be6d lea eax, [ebp - 0x90]
0067be73 mulss xmm4, dword ptr [0xb6a344]
0067be7b mov dword ptr [ebp - 0x6c], 0
0067be82 mov dword ptr [ebp - 0x70], 0x3f800000
0067be89 addss xmm4, dword ptr [0xb6a560]
0067be91 cmp edx, 0x14
0067be94 jne 0x67bebb
0067be96 mulss xmm0, xmm5
0067be9a comiss xmm1, xmm0
0067be9d movss dword ptr [ebp - 0x90], xmm0
0067bea5 cmovbe ecx, eax
0067bea8 lea eax, [ebp - 0x70]
0067beab movss xmm0, dword ptr [ecx]
0067beaf comiss xmm0, xmm3
0067beb2 cmovbe eax, ecx
0067beb5 movss xmm0, dword ptr [eax]
0067beb9 jmp 0x67bee6
0067bebb mulss xmm0, dword ptr [0xb6a2ec]
0067bec3 comiss xmm1, xmm0
0067bec6 movss dword ptr [ebp - 0x90], xmm0
0067bece cmovbe ecx, eax
0067bed1 lea eax, [ebp - 0x70]
0067bed4 movss xmm0, dword ptr [ecx]
0067bed8 comiss xmm0, xmm3
0067bedb cmovbe eax, ecx
0067bede movss xmm0, dword ptr [eax]
0067bee2 addss xmm0, xmm0
0067bee6 addss xmm2, dword ptr [edi + 0x2f4]
0067beee addss xmm0, xmm1
0067bef2 movss dword ptr [edi + 0x2c4], xmm4
0067befa movss dword ptr [edi + 0x37c], xmm2
0067bf02 movss dword ptr [ebp - 0x90], xmm0
0067bf0a movss xmm0, dword ptr [edi + 0x378]
0067bf12 mulss xmm0, dword ptr [0xb6a230]
0067bf1a movss dword ptr [ebp - 0x6c], xmm0
0067bf1f call 0x412010
0067bf24 movss dword ptr [ebp - 0x70], xmm0
0067bf29 movss xmm0, dword ptr [ebp - 0x6c]
0067bf2e call 0x411fe0
0067bf33 cmp byte ptr [edi + 0x188], 0
0067bf3a movaps xmm3, xmm0
0067bf3d movss xmm0, dword ptr [ebp - 0x90]
0067bf45 movss xmm1, dword ptr [edi + 0x2f4]
0067bf4d mulss xmm3, xmm0
0067bf51 mulss xmm0, dword ptr [ebp - 0x70]
0067bf56 mulss xmm3, xmm1
0067bf5a mulss xmm0, xmm1
0067bf5e addss xmm3, dword ptr [edi + 0x2b8]
0067bf66 addss xmm0, dword ptr [edi + 0x2bc]
0067bf6e movss dword ptr [edi + 0x2b8], xmm3
0067bf76 movss dword ptr [edi + 0x2bc], xmm0
0067bf7e je 0x67bfc9
0067bf80 mov dword ptr [edi + 0x360], 0
0067bf8a movss xmm2, dword ptr [edi + 0x2f4]
0067bf92 movss xmm0, dword ptr [edi + 0x294]
0067bf9a movaps xmm1, xmm2
0067bf9d mulss xmm2, dword ptr [edi + 0x2bc]
0067bfa5 mulss xmm1, xmm3
0067bfa9 subss xmm0, xmm1
0067bfad movss dword ptr [edi + 0x294], xmm0
0067bfb5 movss xmm0, dword ptr [edi + 0x298]
0067bfbd subss xmm0, xmm2
0067bfc1 movss dword ptr [edi + 0x298], xmm0
0067bfc9 mov ecx, edi
0067bfcb call 0x6860a0
0067bfd0 mov eax, dword ptr [edi + 0x2c]
0067bfd3 cmp eax, 0x13
0067bfd6 je 0x67bfe1
0067bfd8 cmp eax, 0x14
0067bfdb jne 0x67c463
0067bfe1 push 0xbc4920
0067bfe6 mov edx, esi
0067bfe8 lea ecx, [ebp - 0xa8]
0067bfee call 0x412050
0067bff3 add esp, 4
0067bff6 mov ecx, dword ptr [eax]
0067bff8 or ecx, dword ptr [eax + 4]
0067bffb jne 0x67c009
0067bffd mov ecx, dword ptr [eax + 8]
0067c000 or ecx, dword ptr [eax + 0xc]
0067c003 je 0x67c0d1
0067c009 mov eax, dword ptr [edi + 0x314]
0067c00f test eax, eax
0067c011 je 0x67c0d1
0067c017 movss xmm1, dword ptr [eax + 0x294]
0067c01f movss xmm0, dword ptr [eax + 0x298]
0067c027 subss xmm1, dword ptr [edi + 0x294]
0067c02f subss xmm0, dword ptr [edi + 0x298]
0067c037 call 0x447a80
0067c03c mulss xmm0, dword ptr [0xb6aa84]
0067c044 subss xmm0, dword ptr [edi + 0x378]
0067c04c call 0x65a640
0067c051 movss xmm1, dword ptr [edi + 0x37c]
0067c059 lea eax, [ebp - 0x90]
0067c05f subss xmm1, dword ptr [0xb6a614]
0067c067 xorps xmm3, xmm3
0067c06a mov dword ptr [ebp - 0x6c], 0
0067c071 movaps xmm2, xmm0
0067c074 mov dword ptr [ebp - 0x70], 0x3f800000
0067c07b lea ecx, [ebp - 0x6c]
0067c07e divss xmm1, dword ptr [0xb6a95c]
0067c086 comiss xmm3, xmm1
0067c089 movss dword ptr [ebp - 0x90], xmm1
0067c091 cmovbe ecx, eax
0067c094 lea eax, [ebp - 0x70]
0067c097 movss xmm0, dword ptr [ecx]
0067c09b comiss xmm0, dword ptr [0xb6a614]
0067c0a2 cmovbe eax, ecx
0067c0a5 movss xmm0, dword ptr [eax]
0067c0a9 mulss xmm0, dword ptr [0xb6a480]
0067c0b1 addss xmm0, xmm3
0067c0b5 mulss xmm0, xmm2
0067c0b9 mulss xmm0, dword ptr [edi + 0x2f4]
0067c0c1 addss xmm0, dword ptr [edi + 0x378]
0067c0c9 movss dword ptr [edi + 0x378], xmm0
0067c0d1 push 0xbc4cb0
0067c0d6 mov edx, esi
0067c0d8 lea ecx, [ebp - 0xa8]
0067c0de call 0x412050
0067c0e3 add esp, 4
0067c0e6 mov ecx, dword ptr [eax]
0067c0e8 or ecx, dword ptr [eax + 4]
0067c0eb jne 0x67c0f9
0067c0ed mov ecx, dword ptr [eax + 8]
0067c0f0 or ecx, dword ptr [eax + 0xc]
0067c0f3 je 0x67c463
0067c0f9 mov eax, dword ptr [edi + 0x344]
0067c0ff lea ecx, [ebp - 0xa8]
0067c105 movq xmm0, qword ptr [0xa08b48]
0067c10d mov dword ptr [ebp - 0xa8], eax
0067c113 mov eax, dword ptr [0xa08b50]
0067c118 movq qword ptr [ebp - 0xa4], xmm0
0067c120 mov dword ptr [ebp - 0x9c], eax
0067c126 call 0x7a7db0
0067c12b fmul dword ptr [0xb6a910]
0067c131 movss xmm2, dword ptr [edi + 0x37c]
0067c139 movss dword ptr [ebp - 0x90], xmm2
0067c141 fadd dword ptr [0xb6a864]
0067c147 fstp dword ptr [ebp - 0x70]
0067c14a movss xmm1, dword ptr [ebp - 0x70]
0067c14f movaps xmm0, xmm1
0067c152 addss xmm0, dword ptr [0xb6a974]
0067c15a ucomiss xmm1, xmm0
0067c15d movss dword ptr [ebp - 0x6c], xmm0
0067c162 lahf 
0067c163 test ah, 0x44
0067c166 jp 0x67c189
0067c168 push 0xb5d590
0067c16d push 3
0067c16f call 0x95e330
0067c174 movss xmm0, dword ptr [ebp - 0x6c]
0067c179 add esp, 8
0067c17c movss xmm2, dword ptr [ebp - 0x90]
0067c184 movss xmm1, dword ptr [ebp - 0x70]
0067c189 subss xmm0, xmm1
0067c18d mov dword ptr [ebp - 0x6c], 0
0067c194 subss xmm2, xmm1
0067c198 mov dword ptr [ebp - 0x70], 0x3f800000
0067c19f xorps xmm1, xmm1
0067c1a2 lea eax, [ebp - 0x90]
0067c1a8 lea ecx, [ebp - 0x6c]
0067c1ab divss xmm2, xmm0
0067c1af comiss xmm1, xmm2
0067c1b2 movss dword ptr [ebp - 0x90], xmm2
0067c1ba cmovbe ecx, eax
0067c1bd lea eax, [ebp - 0x70]
0067c1c0 movss xmm0, dword ptr [ecx]
0067c1c4 comiss xmm0, dword ptr [0xb6a614]
0067c1cb cmovbe eax, ecx
0067c1ce mov ecx, dword ptr [edi + 0x31c]
0067c1d4 movss xmm0, dword ptr [eax]
0067c1d8 lea eax, [edi + 0x31c]
0067c1de addss xmm0, xmm1
0067c1e2 movss dword ptr [ebp - 0x74], xmm0
0067c1e7 test ecx, ecx
0067c1e9 je 0x67c1f8
0067c1eb cmp byte ptr [ecx + 0x16b], 0
0067c1f2 je 0x67c3fd
0067c1f8 movss xmm3, dword ptr [0xb6abf4]
0067c200 lea eax, [edi + 0x294]
0067c206 push -1
0067c208 push eax
0067c209 lea eax, [ebp - 0xa8]
0067c20f push eax
0067c210 mov eax, dword ptr [0xbfd65c]
0067c215 mov ecx, dword ptr [eax + 0x18190]
0067c21b add ecx, 0x1218
0067c221 call 0x4157f0
0067c226 mov dword ptr [ebp - 4], 1
0067c22d xor eax, eax
0067c22f movss xmm1, dword ptr [0xb6adbc]
0067c237 mov dword ptr [ebp - 0x78], 0
0067c23e movss dword ptr [ebp - 0x90], xmm1
0067c246 mov dword ptr [ebp - 0x6c], eax
0067c249 cmp dword ptr [ebp - 0x9c], eax
0067c24f jbe 0x67c3d1
0067c255 mov ecx, dword ptr [ebp - 0xa4]
0067c25b push 0
0067c25d mov esi, dword ptr [ecx + eax*4]
0067c260 mov ecx, esi
0067c262 call 0x684630
0067c267 test al, al
0067c269 je 0x67c37f
0067c26f movss xmm0, dword ptr [edi + 0x378]
0067c277 mulss xmm0, dword ptr [0xb6a230]
0067c27f movss dword ptr [ebp - 0x70], xmm0
0067c284 call 0x412010
0067c289 movss dword ptr [ebp - 0xc4], xmm0
0067c291 movss xmm0, dword ptr [ebp - 0x70]
0067c296 call 0x411fe0
0067c29b movss xmm1, dword ptr [esi + 0x298]
0067c2a3 subss xmm1, dword ptr [edi + 0x298]
0067c2ab movss dword ptr [ebp - 0xb4], xmm0
0067c2b3 movss xmm0, dword ptr [esi + 0x294]
0067c2bb subss xmm0, dword ptr [edi + 0x294]
0067c2c3 movss dword ptr [ebp - 0x70], xmm1
0067c2c8 movaps xmm2, xmm0
0067c2cb movss dword ptr [ebp - 0x98], xmm0
0067c2d3 mulss xmm2, xmm0
0067c2d7 movaps xmm0, xmm1
0067c2da mulss xmm0, xmm1
0067c2de addss xmm2, xmm0
0067c2e2 movaps xmm0, xmm2
0067c2e5 movss dword ptr [ebp - 0x7c], xmm2
0067c2ea call 0x4228c0
0067c2ef comiss xmm0, dword ptr [0xb6a18c]
0067c2f6 movss xmm2, dword ptr [ebp - 0x70]
0067c2fb jbe 0x67c31a
0067c2fd movss xmm1, dword ptr [0xb6a614]
0067c305 divss xmm1, xmm0
0067c309 movaps xmm0, xmm1
0067c30c mulss xmm2, xmm1
0067c310 mulss xmm0, dword ptr [ebp - 0x98]
0067c318 jmp 0x67c322
0067c31a movss xmm0, dword ptr [ebp - 0x98]
0067c322 mulss xmm0, dword ptr [ebp - 0xb4]
0067c32a mulss xmm2, dword ptr [ebp - 0xc4]
0067c332 addss xmm0, xmm2
0067c336 comiss xmm0, dword ptr [0xb6a350]
0067c33d movss dword ptr [ebp - 0x98], xmm0
0067c345 jbe 0x67c37f
0067c347 movss xmm0, dword ptr [ebp - 0x7c]
0067c34c call 0x4228c0
0067c351 movss xmm1, dword ptr [0xb6a614]
0067c359 subss xmm1, dword ptr [ebp - 0x98]
0067c361 mulss xmm1, xmm0
0067c365 movss xmm0, dword ptr [ebp - 0x90]
0067c36d comiss xmm0, xmm1
0067c370 jbe 0x67c37f
0067c372 movss dword ptr [ebp - 0x90], xmm1
0067c37a mov dword ptr [ebp - 0x78], esi
0067c37d jmp 0x67c382
0067c37f mov esi, dword ptr [ebp - 0x78]
0067c382 mov eax, dword ptr [ebp - 0x6c]
0067c385 inc eax
0067c386 mov dword ptr [ebp - 0x6c], eax
0067c389 cmp eax, dword ptr [ebp - 0x9c]
0067c38f jb 0x67c255
0067c395 test esi, esi
0067c397 je 0x67c3cb
0067c399 mov ecx, dword ptr [edi + 0x31c]
0067c39f lea eax, [edi + 0x31c]
0067c3a5 test ecx, ecx
0067c3a7 je 0x67c3c1
0067c3a9 mov dword ptr [ebp - 0x7c], eax
0067c3ac add ecx, 0x324
0067c3b2 lea eax, [ebp - 0x7c]
0067c3b5 push eax
0067c3b6 call 0x4bc3c0
0067c3bb lea eax, [edi + 0x31c]
0067c3c1 push eax
0067c3c2 mov ecx, esi
0067c3c4 mov dword ptr [eax], esi
0067c3c6 call 0x4bae70
0067c3cb lea esi, [edi + 0x388]
0067c3d1 mov dword ptr [ebp - 4], 0xffffffff
0067c3d8 cmp byte ptr [ebp - 0xa8], 0
0067c3df jne 0x67c3ef
0067c3e1 push dword ptr [ebp - 0xa4]
0067c3e7 call 0x9eace5
0067c3ec add esp, 4
0067c3ef movss xmm0, dword ptr [ebp - 0x74]
0067c3f4 lea eax, [edi + 0x31c]
0067c3fa xorps xmm1, xmm1
0067c3fd mov eax, dword ptr [eax]
0067c3ff test eax, eax
0067c401 je 0x67c463
0067c403 comiss xmm0, xmm1
0067c406 jbe 0x67c463
0067c408 movss xmm1, dword ptr [eax + 0x294]
0067c410 movss xmm0, dword ptr [eax + 0x298]
0067c418 subss xmm1, dword ptr [edi + 0x294]
0067c420 subss xmm0, dword ptr [edi + 0x298]
0067c428 call 0x447a80
0067c42d mulss xmm0, dword ptr [0xb6aa84]
0067c435 subss xmm0, dword ptr [edi + 0x378]
0067c43d call 0x65a640
0067c442 movss xmm1, dword ptr [ebp - 0x74]
0067c447 mulss xmm1, dword ptr [edi + 0x2f4]
0067c44f mulss xmm1, xmm0
0067c453 addss xmm1, dword ptr [edi + 0x378]
0067c45b movss dword ptr [edi + 0x378], xmm1
0067c463 cmp byte ptr [edi + 0x398], 0
0067c46a movss xmm0, dword ptr [0xb6ae44]
0067c472 movss dword ptr [ebp - 0x70], xmm0
0067c477 je 0x67c61d
0067c47d cmp dword ptr [edi + 0x314], 0
0067c484 je 0x67c61d
0067c48a push 0xbc4bf0
0067c48f mov edx, esi
0067c491 lea ecx, [ebp - 0xa8]
0067c497 call 0x412050
0067c49c add esp, 4
0067c49f mov ecx, dword ptr [eax]
0067c4a1 or ecx, dword ptr [eax + 4]
0067c4a4 jne 0x67c4b2
0067c4a6 mov ecx, dword ptr [eax + 8]
0067c4a9 or ecx, dword ptr [eax + 0xc]
0067c4ac je 0x67c61d
0067c4b2 mov ecx, edi
0067c4b4 call 0x67ab80
0067c4b9 test al, al
0067c4bb jne 0x67c61d
0067c4c1 test byte ptr [edi + 0x3a4], 1
0067c4c8 jne 0x67c4d2
0067c4ca movss xmm0, dword ptr [0xb6a614]
0067c4d2 mov eax, dword ptr [edi + 0x314]
0067c4d8 movss xmm1, dword ptr [edi + 0x298]
0067c4e0 movss xmm2, dword ptr [edi + 0x294]
0067c4e8 movss dword ptr [ebp - 0x6c], xmm0
0067c4ed subss xmm1, dword ptr [eax + 0x298]
0067c4f5 subss xmm2, dword ptr [eax + 0x294]
0067c4fd movaps xmm0, xmm1
0067c500 movss dword ptr [ebp - 0x78], xmm1
0067c505 mulss xmm0, xmm1
0067c509 movaps xmm1, xmm2
0067c50c mulss xmm1, xmm2
0067c510 movss dword ptr [ebp - 0x74], xmm2
0067c515 addss xmm0, xmm1
0067c519 call 0x4228c0
0067c51e movaps xmm3, xmm0
0067c521 ucomiss xmm3, dword ptr [0xb6a18c]
0067c528 lahf 
0067c529 test ah, 0x44
0067c52c jp 0x67c536
0067c52e movss xmm3, dword ptr [0xb6a2cc]
0067c536 movss xmm1, dword ptr [ebp - 0x74]
0067c53b movss xmm2, dword ptr [ebp - 0x78]
0067c540 movss xmm0, dword ptr [0xb6ab10]
0067c548 divss xmm1, xmm3
0067c54c divss xmm2, xmm3
0067c550 subss xmm0, xmm3
0067c554 movss dword ptr [ebp - 0x74], xmm1
0067c559 xorps xmm1, xmmword ptr [0xb6c9b0]
0067c560 mulss xmm1, dword ptr [ebp - 0x6c]
0067c565 movss dword ptr [ebp - 0x78], xmm2
0067c56a mulss xmm0, dword ptr [0xb6a274]
0067c572 movss dword ptr [ebp - 0xb4], xmm1
0067c57a movss xmm1, dword ptr [edi + 0x2bc]
0067c582 movss dword ptr [ebp - 0x7c], xmm0
0067c587 movss xmm0, dword ptr [ebp - 0x6c]
0067c58c mulss xmm0, xmm2
0067c590 mulss xmm1, xmm1
0067c594 movss dword ptr [ebp - 0xc4], xmm0
0067c59c movss xmm0, dword ptr [edi + 0x2b8]
0067c5a4 mulss xmm0, xmm0
0067c5a8 addss xmm0, xmm1
0067c5ac call 0x4228c0
0067c5b1 movss xmm3, dword ptr [ebp - 0x7c]
0067c5b6 lea eax, [ebp - 0xc8]
0067c5bc movaps xmm2, xmm3
0067c5bf movss dword ptr [ebp - 0x6c], xmm0
0067c5c4 mulss xmm2, dword ptr [ebp - 0x74]
0067c5c9 lea ecx, [ebp - 0x80]
0067c5cc push eax
0067c5cd mulss xmm3, dword ptr [ebp - 0x78]
0067c5d2 movaps xmm1, xmm0
0067c5d5 mulss xmm1, dword ptr [ebp - 0xc4]
0067c5dd mulss xmm0, dword ptr [ebp - 0xb4]
0067c5e5 addss xmm2, xmm1
0067c5e9 addss xmm3, xmm0
0067c5ed movss dword ptr [ebp - 0x80], xmm2
0067c5f2 movss dword ptr [ebp - 0x7c], xmm3
0067c5f7 call 0x962560
0067c5fc movss xmm1, dword ptr [ebp - 0x6c]
0067c601 movaps xmm0, xmm1
0067c604 mulss xmm0, dword ptr [eax]
0067c608 mulss xmm1, dword ptr [eax + 4]
0067c60d movss dword ptr [edi + 0x2b8], xmm0
0067c615 movss dword ptr [edi + 0x2bc], xmm1
0067c61d cmp dword ptr [edi + 0x34], 1
0067c621 movss xmm2, dword ptr [0xb6a8f4]
0067c629 jne 0x67c9e9
0067c62f push 0xbc4cb0
0067c634 mov edx, esi
0067c636 lea ecx, [ebp - 0xd0]
0067c63c call 0x412050
0067c641 add esp, 4
0067c644 mov ecx, dword ptr [eax]
0067c646 or ecx, dword ptr [eax + 4]
0067c649 jne 0x67c657
0067c64b mov ecx, dword ptr [eax + 8]
0067c64e or ecx, dword ptr [eax + 0xc]
0067c651 je 0x67c87f
0067c657 cmp dword ptr [edi + 0x31c], 0
0067c65e jne 0x67c7dd
0067c664 movss xmm1, dword ptr [edi + 0x2b8]
0067c66c lea eax, [ebp - 0x80]
0067c66f movss xmm0, dword ptr [edi + 0x2bc]
0067c677 movss xmm3, dword ptr [0xb6ab58]
0067c67f push 8
0067c681 push eax
0067c682 mulss xmm1, xmm2
0067c686 lea eax, [ebp - 0xa8]
0067c68c push eax
0067c68d mov eax, dword ptr [0xbfd65c]
0067c692 mulss xmm0, xmm2
0067c696 addss xmm1, dword ptr [edi + 0x294]
0067c69e mov ecx, dword ptr [eax + 0x18190]
0067c6a4 addss xmm0, dword ptr [edi + 0x298]
0067c6ac add ecx, 0x1218
0067c6b2 movss dword ptr [ebp - 0x80], xmm1
0067c6b7 movss dword ptr [ebp - 0x7c], xmm0
0067c6bc call 0x4157f0
0067c6c1 xor ecx, ecx
0067c6c3 mov dword ptr [ebp - 4], 2
0067c6ca mov dword ptr [ebp - 0x6c], ecx
0067c6cd cmp dword ptr [ebp - 0x9c], ecx
0067c6d3 jbe 0x67c7b6
0067c6d9 nop dword ptr [eax]
0067c6e0 mov eax, dword ptr [ebp - 0xa4]
0067c6e6 push 0
0067c6e8 mov esi, dword ptr [eax + ecx*4]
0067c6eb mov ecx, esi
0067c6ed call 0x684630
0067c6f2 test al, al
0067c6f4 je 0x67c7a3
0067c6fa mov eax, dword ptr [esi + 0x160]
0067c700 and eax, 0x20000010
0067c705 or eax, 0
0067c708 jne 0x67c7a3
0067c70e call 0x6c3d90
0067c713 and eax, 1
0067c716 je 0x67c7a3
0067c71c push dword ptr [edi + 0x20]
0067c71f mov ecx, edi
0067c721 push 5
0067c723 call 0x684790
0067c728 test al, al
0067c72a je 0x67c7a3
0067c72c mov eax, dword ptr [esi + 0x294]
0067c732 mov ecx, dword ptr [esi + 0x298]
0067c738 push 0
0067c73a push 0
0067c73c push 0
0067c73e push 0
0067c740 mov dword ptr [ebp - 0xc8], eax
0067c746 lea eax, [ebp - 0xc8]
0067c74c mov dword ptr [ebp - 0xc4], ecx
0067c752 mov ecx, dword ptr [0xbfd65c]
0067c758 push 1
0067c75a push eax
0067c75b lea eax, [edi + 0x294]
0067c761 mov ecx, dword ptr [ecx + 0x18190]
0067c767 push eax
0067c768 call 0x7af4b0
0067c76d test al, al
0067c76f je 0x67c7a3
0067c771 mov ecx, dword ptr [edi + 0x31c]
0067c777 lea eax, [edi + 0x31c]
0067c77d test ecx, ecx
0067c77f je 0x67c799
0067c781 mov dword ptr [ebp - 0x7c], eax
0067c784 add ecx, 0x324
0067c78a lea eax, [ebp - 0x7c]
0067c78d push eax
0067c78e call 0x4bc3c0
0067c793 lea eax, [edi + 0x31c]
0067c799 push eax
0067c79a mov ecx, esi
0067c79c mov dword ptr [eax], esi
0067c79e call 0x4bae70
0067c7a3 mov ecx, dword ptr [ebp - 0x6c]
0067c7a6 inc ecx
0067c7a7 mov dword ptr [ebp - 0x6c], ecx
0067c7aa cmp ecx, dword ptr [ebp - 0x9c]
0067c7b0 jb 0x67c6e0
0067c7b6 mov dword ptr [ebp - 4], 0xffffffff
0067c7bd cmp byte ptr [ebp - 0xa8], 0
0067c7c4 jne 0x67c879
0067c7ca push dword ptr [ebp - 0xa4]
0067c7d0 call 0x9eace5
0067c7d5 add esp, 4
0067c7d8 jmp 0x67c879
0067c7dd mov ecx, edi
0067c7df call 0x67ab80
0067c7e4 test al, al
0067c7e6 jne 0x67c879
0067c7ec call 0x6c3d90
0067c7f1 test al, 1
0067c7f3 jne 0x67c879
0067c7f9 mov eax, dword ptr [edi + 0x31c]
0067c7ff lea ecx, [ebp - 0x80]
0067c802 movss xmm0, dword ptr [edi + 0x294]
0067c80a subss xmm0, dword ptr [eax + 0x294]
0067c812 movss dword ptr [ebp - 0x80], xmm0
0067c817 movss xmm0, dword ptr [edi + 0x298]
0067c81f subss xmm0, dword ptr [eax + 0x298]
0067c827 lea eax, [ebp - 0xc8]
0067c82d push eax
0067c82e movss dword ptr [ebp - 0x7c], xmm0
0067c833 call 0x962560
0067c838 movss xmm0, dword ptr [edi + 0x2b8]
0067c840 movss xmm1, dword ptr [eax]
0067c844 mulss xmm1, dword ptr [0xb6a6a8]
0067c84c movss xmm3, dword ptr [eax + 4]
0067c851 mulss xmm3, dword ptr [0xb6a6a8]
0067c859 subss xmm0, xmm1
0067c85d movss dword ptr [edi + 0x2b8], xmm0
0067c865 movss xmm0, dword ptr [edi + 0x2bc]
0067c86d subss xmm0, xmm3
0067c871 movss dword ptr [edi + 0x2bc], xmm0
0067c879 lea esi, [edi + 0x388]
0067c87f cmp byte ptr [edi + 0x16b], 0
0067c886 jne 0x67c9e9
0067c88c push 0xbc4810
0067c891 mov edx, esi
0067c893 lea ecx, [ebp - 0xa8]
0067c899 call 0x412050
0067c89e add esp, 4
0067c8a1 mov ecx, dword ptr [eax]
0067c8a3 or ecx, dword ptr [eax + 4]
0067c8a6 jne 0x67c8b4
0067c8a8 mov ecx, dword ptr [eax + 8]
0067c8ab or ecx, dword ptr [eax + 0xc]
0067c8ae je 0x67c9e9
0067c8b4 push 0
0067c8b6 push 7
0067c8b8 mov ecx, edi
0067c8ba call 0x684790
0067c8bf test al, al
0067c8c1 je 0x67c9e9
0067c8c7 movss xmm0, dword ptr [edi + 0x368]
0067c8cf movss dword ptr [ebp - 0x7c], xmm0
0067c8d4 call 0x6c3d90
0067c8d9 mov ecx, dword ptr [0xbfd65c]
0067c8df push 0
0067c8e1 push 0xbeaaec
0067c8e6 push 0xbeab18
0067c8eb push 0
0067c8ed push eax
0067c8ee push 0
0067c8f0 push dword ptr [edi + 0x320]
0067c8f6 lea eax, [edi + 0x294]
0067c8fc push 0xc02fec
0067c901 push eax
0067c902 push 0x2e
0067c904 push 0x3e8
0067c909 call 0x422e20
0067c90e push eax
0067c90f call 0x9ec34c
0067c914 add esp, 0x14
0067c917 mov esi, eax
0067c919 call 0x6c3d90
0067c91e movss xmm3, dword ptr [0xb6a614]
0067c926 mov edx, dword ptr [esi]
0067c928 movaps xmm2, xmm3
0067c92b push 1
0067c92d movd xmm0, eax
0067c931 cvtdq2pd xmm0, xmm0
0067c935 shr eax, 0x1f
0067c938 push 0
0067c93a push 0xff
0067c93f push -1
0067c941 push 0
0067c943 push 0x64
0067c945 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
0067c94e push 0
0067c950 push ecx
0067c951 lea ecx, [ebp - 0x3c]
0067c954 mov dword ptr [esp], 0x3f800000
0067c95b cvtpd2ps xmm1, xmm0
0067c95f mulss xmm1, dword ptr [0xb6a19c]
0067c967 mulss xmm1, dword ptr [0xb6a4c4]
0067c96f addss xmm1, dword ptr [0xb6a3b0]
0067c977 movaps xmm0, xmm1
0067c97a mulss xmm1, dword ptr [0xbc7a2c]
0067c982 mulss xmm0, dword ptr [0xbc7a28]
0067c98a movss dword ptr [esi + 0xdc], xmm1
0067c992 xorps xmm1, xmm1
0067c995 movss dword ptr [esi + 0xd8], xmm0
0067c99d call 0x4270d0
0067c9a2 push eax
0067c9a3 mov ecx, esi
0067c9a5 call dword ptr [edx + 0x38]
0067c9a8 movss xmm0, dword ptr [ebp - 0x7c]
0067c9ad subss xmm0, dword ptr [0xb6aa0c]
0067c9b5 movss xmm1, dword ptr [0xb6a910]
0067c9bd mov eax, dword ptr [esi]
0067c9bf push ecx
0067c9c0 mov ecx, esi
0067c9c2 divss xmm0, dword ptr [0xb6a864]
0067c9ca maxss xmm1, xmm0
0067c9ce movss dword ptr [esp], xmm1
0067c9d3 call dword ptr [eax + 0x3c]
0067c9d6 mov eax, dword ptr [edi + 0x34]
0067c9d9 mov ecx, esi
0067c9db mov dword ptr [esi + 0x34], eax
0067c9de mov eax, dword ptr [edi + 0x38]
0067c9e1 mov dword ptr [esi + 0x38], eax
0067c9e4 mov eax, dword ptr [esi]
0067c9e6 call dword ptr [eax + 0xc]
0067c9e9 mov eax, dword ptr [edi + 0x2c]
0067c9ec cmp eax, 0x13
0067c9ef je 0x67ca8c
0067c9f5 cmp eax, 0x14
0067c9f8 je 0x67ca8c
0067c9fe movss xmm0, dword ptr [edi + 0x2a8]
0067ca06 comiss xmm0, dword ptr [0xb6a18c]
0067ca0d jae 0x67ca18
0067ca0f cmp byte ptr [edi + 0x398], 0
0067ca16 jne 0x67ca8c
0067ca18 movss xmm2, dword ptr [edi + 0x2b8]
0067ca20 mulss xmm2, dword ptr [0xb6a5d8]
0067ca28 movss xmm1, dword ptr [edi + 0x2bc]
0067ca30 mulss xmm1, dword ptr [0xb6a5d8]
0067ca38 movaps xmm0, xmm2
0067ca3b movss dword ptr [edi + 0x2b8], xmm2
0067ca43 mulss xmm0, xmm2
0067ca47 movss dword ptr [edi + 0x2bc], xmm1
0067ca4f mulss xmm1, xmm1
0067ca53 addss xmm1, xmm0
0067ca57 movss xmm0, dword ptr [0xb6a614]
0067ca5f comiss xmm0, xmm1
0067ca62 jbe 0x67ca8c
0067ca64 movss xmm0, dword ptr [edi + 0x2bc]
0067ca6c mulss xmm2, dword ptr [0xb6a480]
0067ca74 mulss xmm0, dword ptr [0xb6a480]
0067ca7c movss dword ptr [edi + 0x2b8], xmm2
0067ca84 movss dword ptr [edi + 0x2bc], xmm0
0067ca8c lea esi, [edi + 0x388]
0067ca92 push 0xbc4950
0067ca97 mov edx, esi
0067ca99 lea ecx, [ebp - 0xa8]
0067ca9f call 0x412050
0067caa4 add esp, 4
0067caa7 mov ecx, dword ptr [eax]
0067caa9 or ecx, dword ptr [eax + 4]
0067caac jne 0x67cab6
0067caae mov ecx, dword ptr [eax + 8]
0067cab1 or ecx, dword ptr [eax + 0xc]
0067cab4 je 0x67caf0
0067cab6 mov eax, dword ptr [edi + 0x3a0]
0067cabc test eax, eax
0067cabe je 0x67caf0
0067cac0 movss xmm0, dword ptr [eax + 0x2b8]
0067cac8 movss xmm1, dword ptr [eax + 0x2bc]
0067cad0 mulss xmm0, dword ptr [0xb6a5a4]
0067cad8 mulss xmm1, dword ptr [0xb6a5a4]
0067cae0 movss dword ptr [eax + 0x2b8], xmm0
0067cae8 movss dword ptr [eax + 0x2bc], xmm1
0067caf0 mov edx, dword ptr [edi + 0x360]
0067caf6 test edx, edx
0067caf8 jle 0x67cca9
0067cafe cmp dword ptr [edi + 0x34], 1
0067cb02 jne 0x67cb30
0067cb04 mov eax, dword ptr [ebp - 0xac]
0067cb0a test eax, eax
0067cb0c je 0x67cb30
0067cb0e add eax, 0x1450
0067cb13 push 0x89
0067cb18 mov ecx, eax
0067cb1a mov dword ptr [ebp - 0x6c], eax
0067cb1d call 0x88b570
0067cb22 test al, al
0067cb24 jne 0x67ccba
0067cb2a mov edx, dword ptr [edi + 0x360]
0067cb30 mov eax, dword ptr [edi + 0x2c]
0067cb33 cmp eax, 0x13
0067cb36 je 0x67cb3d
0067cb38 cmp eax, 0x14
0067cb3b jne 0x67cb4f
0067cb3d mov ecx, dword ptr [edi + 0x164]
0067cb43 xor eax, eax
0067cb45 and ecx, 0x2000000
0067cb4b or eax, ecx
0067cb4d jne 0x67cb58
0067cb4f lea eax, [edx - 1]
0067cb52 mov dword ptr [edi + 0x360], eax
0067cb58 push 0xbc4b80
0067cb5d mov edx, esi
0067cb5f lea ecx, [ebp - 0xa8]
0067cb65 call 0x412050
0067cb6a add esp, 4
0067cb6d mov ecx, dword ptr [eax]
0067cb6f or ecx, dword ptr [eax + 4]
0067cb72 jne 0x67cb7c
0067cb74 mov ecx, dword ptr [eax + 8]
0067cb77 or ecx, dword ptr [eax + 0xc]
0067cb7a je 0x67cba0
0067cb7c movss xmm3, dword ptr [0xb6abec]
0067cb84 lea eax, [edi + 0x294]
0067cb8a movss xmm2, dword ptr [0xb6a974]
0067cb92 mov ecx, dword ptr [0xbfd65c]
0067cb98 push 0
0067cb9a push eax
0067cb9b call 0x6d7c90
0067cba0 mov ecx, dword ptr [0xbfd65c]
0067cba6 push 1
0067cba8 push 0
0067cbaa push 0x3f
0067cbac lea ecx, [ecx + 0x1ba40]
0067cbb2 call 0x91d550
0067cbb7 test eax, eax
0067cbb9 je 0x67db64
0067cbbf cmp dword ptr [edi + 0x360], 0
0067cbc6 jne 0x67db64
0067cbcc mov eax, dword ptr [edi + 0x2c]
0067cbcf cmp eax, 3
0067cbd2 je 0x67cc0c
0067cbd4 cmp eax, 4
0067cbd7 je 0x67cc0c
0067cbd9 cmp eax, 8
0067cbdc je 0x67cc0c
0067cbde cmp eax, 0x12
0067cbe1 je 0x67cc0c
0067cbe3 cmp eax, 0x11
0067cbe6 jne 0x67db64
0067cbec cmp dword ptr [edi + 0x34], 1
0067cbf0 je 0x67db64
0067cbf6 push 0
0067cbf8 push 0x20000000
0067cbfd mov ecx, edi
0067cbff call 0x4122f0
0067cc04 test al, al
0067cc06 jne 0x67db64
0067cc0c mov eax, dword ptr [edi]
0067cc0e mov ecx, edi
0067cc10 call dword ptr [eax + 0x28]
0067cc13 mov eax, dword ptr [edi + 0x2c]
0067cc16 mov esi, 1
0067cc1b cmp eax, 4
0067cc1e jne 0x67cc25
0067cc20 lea esi, [eax - 2]
0067cc23 jmp 0x67cc3a
0067cc25 cmp eax, 0x12
0067cc28 jne 0x67cc2f
0067cc2a lea esi, [eax - 0xe]
0067cc2d jmp 0x67cc3a
0067cc2f cmp eax, 0x11
0067cc32 mov ecx, 7
0067cc37 cmove esi, ecx
0067cc3a call 0x6c3d90
0067cc3f push eax
0067cc40 push esi
0067cc41 push 0
0067cc43 lea eax, [edi + 0x2b8]
0067cc49 push eax
0067cc4a lea ecx, [edi + 0x294]
0067cc50 push ecx
0067cc51 mov ecx, dword ptr [0xbfd65c]
0067cc57 push 0x28
0067cc59 push 5
0067cc5b call 0x422e20
0067cc60 mov ecx, dword ptr [eax + 0x70]
0067cc63 test ecx, ecx
0067cc65 je 0x67cc7c
0067cc67 mov ecx, dword ptr [ecx + 0x30]
0067cc6a sub ecx, 8
0067cc6d movd xmm1, ecx
0067cc71 lea ecx, [eax + 0x6c]
0067cc74 cvtdq2ps xmm1, xmm1
0067cc77 call 0x403c00
0067cc7c call 0x6c3d90
0067cc81 mov ecx, dword ptr [0xbfd65c]
0067cc87 push eax
0067cc88 push 1
0067cc8a push 0
0067cc8c push 0xc02fec
0067cc91 lea eax, [edi + 0x294]
0067cc97 push eax
0067cc98 push 0xf
0067cc9a push 0x3e8
0067cc9f call 0x422e20
0067cca4 jmp 0x67e272
0067cca9 mov eax, dword ptr [ebp - 0xac]
0067ccaf lea ecx, [eax + 0x1450]
0067ccb5 mov dword ptr [ebp - 0x6c], ecx
0067ccb8 jmp 0x67ccc0
0067ccba mov eax, dword ptr [ebp - 0xac]
0067ccc0 cmp byte ptr [edi + 0x398], 0
0067ccc7 jne 0x67ccfa
0067ccc9 test eax, eax
0067cccb je 0x67ccfa
0067cccd push 0
0067cccf push 0x89
0067ccd4 mov ecx, eax
0067ccd6 call 0x73af30
0067ccdb test al, al
0067ccdd je 0x67ccfa
0067ccdf mov ecx, dword ptr [ebp - 0x6c]
0067cce2 push 0x89
0067cce7 call 0x88b570
0067ccec test al, al
0067ccee jne 0x67ccfa
0067ccf0 cmp dword ptr [edi + 0x34], 1
0067ccf4 je 0x67db64
0067ccfa movups xmm1, xmmword ptr [esi]
0067ccfd mov eax, dword ptr [edi + 0x2c]
0067cd00 movups xmmword ptr [ebp - 0x88], xmm1
0067cd07 cmp eax, 0x11
0067cd0a je 0x67cd11
0067cd0c cmp eax, 0x14
0067cd0f jne 0x67cd48
0067cd11 mov eax, dword ptr [0xbc47d0]
0067cd16 or dword ptr [ebp - 0x88], eax
0067cd1c mov eax, dword ptr [0xbc47d4]
0067cd21 or dword ptr [ebp - 0x84], eax
0067cd27 mov eax, dword ptr [0xbc47d8]
0067cd2c or dword ptr [ebp - 0x80], eax
0067cd2f mov eax, dword ptr [0xbc47dc]
0067cd34 or dword ptr [ebp - 0x7c], eax
0067cd37 movups xmm1, xmmword ptr [ebp - 0x88]
0067cd3e mov dword ptr [edi + 0x3a8], 5
0067cd48 cmp byte ptr [edi + 0x398], 0
0067cd4f mov eax, 4
0067cd54 jne 0x67cd5b
0067cd56 mov eax, 0x40000004
0067cd5b movss xmm0, dword ptr [edi + 0x39c]
0067cd63 lea ecx, [edi + 0x294]
0067cd69 push 0
0067cd6b push 0
0067cd6d push eax
0067cd6e push 1
0067cd70 push ecx
0067cd71 movss dword ptr [esp], xmm0
0067cd76 lea eax, [edi + 0xe4]
0067cd7c movss xmm0, dword ptr [edi + 0x368]
0067cd84 push edi
0067cd85 push eax
0067cd86 sub esp, 0x10
0067cd89 mov eax, esp
0067cd8b push ecx
0067cd8c movups xmmword ptr [eax], xmm1
0067cd8f movss dword ptr [esp], xmm0
0067cd94 push ecx
0067cd95 mov ecx, dword ptr [0xbfd65c]
0067cd9b call 0x6d26e0
0067cda0 cmp dword ptr [ebp - 0xac], 0
0067cda7 je 0x67cdb2
0067cda9 mov dword ptr [ebp - 0x74], 0
0067cdb0 jmp 0x67cdb8
0067cdb2 mov eax, dword ptr [edi + 0x2c]
0067cdb5 mov dword ptr [ebp - 0x74], eax
0067cdb8 push 0xbc47a0
0067cdbd mov edx, esi
0067cdbf lea ecx, [ebp - 0xa8]
0067cdc5 call 0x412050
0067cdca movss xmm1, dword ptr [0xb6a874]
0067cdd2 add esp, 4
0067cdd5 mov ecx, dword ptr [eax]
0067cdd7 or ecx, dword ptr [eax + 4]
0067cdda jne 0x67cde8
0067cddc mov ecx, dword ptr [eax + 8]
0067cddf or ecx, dword ptr [eax + 0xc]
0067cde2 je 0x67d109
0067cde8 call 0x6c3d90
0067cded and eax, 1
0067cdf0 add eax, 4
0067cdf3 mov dword ptr [ebp - 0x6c], eax
0067cdf6 call 0x6c3d90
0067cdfb movd xmm0, eax
0067cdff cvtdq2pd xmm0, xmm0
0067ce03 shr eax, 0x1f
0067ce06 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
0067ce0f cvtpd2ps xmm0, xmm0
0067ce13 mulss xmm0, dword ptr [0xb6a19c]
0067ce1b mulss xmm0, xmm1
0067ce1f addss xmm0, xmm0
0067ce23 movss dword ptr [ebp - 0x7c], xmm0
0067ce28 call 0x411fe0
0067ce2d movss dword ptr [ebp - 0xc4], xmm0
0067ce35 movss xmm0, dword ptr [ebp - 0x7c]
0067ce3a call 0x412010
0067ce3f movaps xmm4, xmm0
0067ce42 call 0x6c3d90
0067ce47 movd xmm1, eax
0067ce4b cvtdq2pd xmm1, xmm1
0067ce4f shr eax, 0x1f
0067ce52 addsd xmm1, qword ptr [eax*8 + 0xb6c940]
0067ce5b cvtpd2ps xmm2, xmm1
0067ce5f mulss xmm2, dword ptr [0xb6a19c]
0067ce67 mulss xmm2, dword ptr [0xb6a928]
0067ce6f addss xmm2, dword ptr [0xb6a864]
0067ce77 call 0x6c3d90
0067ce7c movd xmm0, eax
0067ce80 cvtdq2pd xmm0, xmm0
0067ce84 shr eax, 0x1f
0067ce87 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
0067ce90 cvtpd2ps xmm1, xmm0
0067ce94 mulss xmm1, dword ptr [0xb6a19c]
0067ce9c mulss xmm1, dword ptr [0xb6a9ac]
0067cea4 call 0x6c3d90
0067cea9 push 0
0067ceab mov ecx, dword ptr [0xbfd65c]
0067ceb1 movaps xmm0, xmm2
0067ceb4 mulss xmm0, dword ptr [ebp - 0xc4]
0067cebc push 0xbeacac
0067cec1 push 0xbeab18
0067cec6 push 0
0067cec8 push eax
0067cec9 push 0
0067cecb push dword ptr [edi + 0x320]
0067ced1 movss dword ptr [ebp - 0x94], xmm0
0067ced9 lea eax, [ebp - 0x94]
0067cedf movaps xmm0, xmm1
0067cee2 mulss xmm2, xmm4
0067cee6 push eax
0067cee7 mulss xmm0, dword ptr [ebp - 0xc4]
0067ceef lea eax, [ebp - 0xc0]
0067cef5 push eax
0067cef6 push dword ptr [ebp - 0x74]
0067cef9 mulss xmm1, xmm4
0067cefd addss xmm0, dword ptr [edi + 0x294]
0067cf05 push dword ptr [edi + 0x28]
0067cf08 addss xmm1, dword ptr [edi + 0x298]
0067cf10 movss dword ptr [ebp - 0x90], xmm2
0067cf18 movss dword ptr [ebp - 0xc0], xmm0
0067cf20 movss dword ptr [ebp - 0xbc], xmm1
0067cf28 call 0x422e20
0067cf2d push eax
0067cf2e call 0x9ec34c
0067cf33 mov cl, byte ptr [edi + 0x398]
0067cf39 mov esi, eax
0067cf3b add esp, 0x14
0067cf3e lea eax, [ebp - 0xa8]
0067cf44 mov byte ptr [esi + 0x398], cl
0067cf4a mov ecx, dword ptr [edi + 0x34]
0067cf4d mov dword ptr [esi + 0x34], ecx
0067cf50 mov ecx, dword ptr [edi + 0x38]
0067cf53 mov dword ptr [esi + 0x38], ecx
0067cf56 mov ecx, 0xbc47a0
0067cf5b push eax
0067cf5c call 0x57f3a0
0067cf61 push eax
0067cf62 lea edx, [edi + 0x388]
0067cf68 lea ecx, [ebp - 0xe0]
0067cf6e call 0x412050
0067cf73 add esp, 4
0067cf76 movups xmm0, xmmword ptr [eax]
0067cf79 movups xmmword ptr [esi + 0x388], xmm0
0067cf80 movss xmm1, dword ptr [0xb6a480]
0067cf88 mov byte ptr [esi + 0x3b3], 1
0067cf8f movss xmm0, dword ptr [edi + 0x384]
0067cf97 mulss xmm0, xmm1
0067cf9b push -1
0067cf9d movss dword ptr [esi + 0x384], xmm0
0067cfa5 movss xmm0, dword ptr [edi + 0x368]
0067cfad mulss xmm0, xmm1
0067cfb1 movss dword ptr [esi + 0x368], xmm0
0067cfb9 movss xmm0, dword ptr [edi + 0x39c]
0067cfc1 mulss xmm0, dword ptr [0xb6a4dc]
0067cfc9 movss dword ptr [esi + 0x39c], xmm0
0067cfd1 movss xmm0, dword ptr [0xbc7a28]
0067cfd9 xorps xmm0, xmmword ptr [0xb6c9b0]
0067cfe0 movss dword ptr [ebp - 0xb8], xmm0
0067cfe8 movss xmm0, dword ptr [0xbc7a2c]
0067cff0 xorps xmm0, xmmword ptr [0xb6c9b0]
0067cff7 movss dword ptr [ebp - 0xb4], xmm0
0067cfff push dword ptr [ebp - 0xb4]
0067d005 movss xmm0, dword ptr [esi + 0x2c8]
0067d00d push dword ptr [ebp - 0xb8]
0067d013 mulss xmm0, xmm1
0067d017 push ecx
0067d018 mov ecx, esi
0067d01a movss dword ptr [esp], xmm0
0067d01f call 0x6843a0
0067d024 mov eax, dword ptr [esi + 0x2c]
0067d027 cmp eax, 0x13
0067d02a je 0x67d060
0067d02c cmp eax, 0x14
0067d02f je 0x67d060
0067d031 call 0x6c3d90
0067d036 movd xmm0, eax
0067d03a cvtdq2pd xmm0, xmm0
0067d03e shr eax, 0x1f
0067d041 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
0067d04a cvtpd2ps xmm0, xmm0
0067d04e mulss xmm0, dword ptr [0xb6a19c]
0067d056 mulss xmm0, dword ptr [0xb6a8f4]
0067d05e jmp 0x67d097
0067d060 call 0x6c3d90
0067d065 mov dword ptr [esi + 0x370], 0x3fa66666
0067d06f movd xmm0, eax
0067d073 cvtdq2pd xmm0, xmm0
0067d077 shr eax, 0x1f
0067d07a addsd xmm0, qword ptr [eax*8 + 0xb6c940]
0067d083 cvtpd2ps xmm0, xmm0
0067d087 mulss xmm0, dword ptr [0xb6a19c]
0067d08f mulss xmm0, dword ptr [0xb6a974]
0067d097 movss xmm1, dword ptr [0xb6ae7c]
0067d09f lea ecx, [esi + 0x334]
0067d0a5 subss xmm1, xmm0
0067d0a9 mov eax, esi
0067d0ab push 0xe
0067d0ad movss dword ptr [eax + 0x36c], xmm1
0067d0b5 mov dword ptr [esi + 0x2a4], 0
0067d0bf mov dword ptr [esi + 0x2a8], 0xc0400000
0067d0c9 call 0x7a7d50
0067d0ce or dword ptr [esi + 0x160], 0x4000000
0067d0d8 add eax, 0xa
0067d0db or dword ptr [esi + 0x164], 0x400
0067d0e5 sub dword ptr [ebp - 0x6c], 1
0067d0e9 movss xmm1, dword ptr [0xb6a874]
0067d0f1 mov dword ptr [esi + 0x360], eax
0067d0f7 mov dword ptr [esi + 0x364], eax
0067d0fd jne 0x67cdf6
0067d103 lea esi, [edi + 0x388]
0067d109 push 0xbc4760
0067d10e mov edx, esi
0067d110 lea ecx, [ebp - 0xe0]
0067d116 call 0x412050
0067d11b add esp, 4
0067d11e mov ecx, dword ptr [eax]
0067d120 or ecx, dword ptr [eax + 4]
0067d123 jne 0x67d131
0067d125 mov ecx, dword ptr [eax + 8]
0067d128 or ecx, dword ptr [eax + 0xc]
0067d12b je 0x67d363
0067d131 movss xmm0, dword ptr [0xb6a53c]
0067d139 lea esi, [edi + 0x294]
0067d13f comiss xmm0, dword ptr [edi + 0x384]
0067d146 jb 0x67d1cb
0067d14c mov eax, dword ptr [edi + 0x344]
0067d152 lea ecx, [ebp - 0xa8]
0067d158 movq xmm0, qword ptr [0xa08b3c]
0067d160 mov dword ptr [ebp - 0xa8], eax
0067d166 mov eax, dword ptr [0xa08b44]
0067d16b movq qword ptr [ebp - 0xa4], xmm0
0067d173 mov dword ptr [ebp - 0x9c], eax
0067d179 call 0x7a7e20
0067d17e mov ecx, dword ptr [0xbfd65c]
0067d184 push eax
0067d185 push 1
0067d187 push dword ptr [ebp - 0xac]
0067d18d push 0xc02fec
0067d192 push esi
0067d193 push 0xbd
0067d198 push 0x3e8
0067d19d call 0x422e20
0067d1a2 mov esi, eax
0067d1a4 cmp dword ptr [esi + 0x70], 0
0067d1a8 je 0x67d1ba
0067d1aa mov edx, dword ptr [esi + 0x70]
0067d1ad lea ecx, [esi + 0x6c]
0067d1b0 mov edx, dword ptr [edx + 0x30]
0067d1b3 dec edx
0067d1b4 push edx
0067d1b5 call 0x403b00
0067d1ba movss xmm1, dword ptr [edi + 0x384]
0067d1c2 addss xmm1, xmm1
0067d1c6 jmp 0x67d339
0067d1cb call 0x6c3d90
0067d1d0 mov esi, dword ptr [0xbfd680]
0067d1d6 lea ecx, [ebp - 0x6c]
0067d1d9 mov dword ptr [ebp - 0x6c], 0x2c
0067d1e0 movd xmm0, eax
0067d1e4 cvtdq2pd xmm0, xmm0
0067d1e8 shr eax, 0x1f
0067d1eb addsd xmm0, qword ptr [eax*8 + 0xb6c940]
0067d1f4 cvtpd2ps xmm0, xmm0
0067d1f8 mulss xmm0, dword ptr [0xb6a19c]
0067d200 movss dword ptr [ebp - 0x7c], xmm0
0067d205 call 0x8b1340
0067d20a movss xmm0, dword ptr [ebp - 0x7c]
0067d20f sub esp, 8
0067d212 mulss xmm0, dword ptr [0xb6a434]
0067d21a mov dword ptr [esp + 4], 0
0067d222 addss xmm0, dword ptr [0xb6a7b0]
0067d22a movss dword ptr [esp], xmm0
0067d22f push 0
0067d231 push 2
0067d233 push ecx
0067d234 mov dword ptr [esp], 0x3f333333
0067d23b lea ecx, [esi + 0x29de0]
0067d241 push dword ptr [ebp - 0x6c]
0067d244 call 0x888de0
0067d249 mov eax, dword ptr [edi + 0x344]
0067d24f lea ecx, [ebp - 0xa8]
0067d255 movq xmm0, qword ptr [0xa08b3c]
0067d25d mov dword ptr [ebp - 0xa8], eax
0067d263 mov eax, dword ptr [0xa08b44]
0067d268 movq qword ptr [ebp - 0xa4], xmm0
0067d270 mov dword ptr [ebp - 0x9c], eax
0067d276 call 0x7a7e20
0067d27b mov ecx, dword ptr [0xbfd65c]
0067d281 push eax
0067d282 push 1
0067d284 push dword ptr [ebp - 0xac]
0067d28a lea eax, [edi + 0x294]
0067d290 push 0xc02fec
0067d295 push eax
0067d296 push 0xba
0067d29b push 0x3e8
0067d2a0 call 0x422e20
0067d2a5 cmp byte ptr [edi + 0x398], 0
0067d2ac mov esi, eax
0067d2ae mov eax, 0xb4
0067d2b3 mov ecx, 0x168
0067d2b8 cmovne ecx, eax
0067d2bb push ecx
0067d2bc movss xmm0, dword ptr [esi + 0x2e0]
0067d2c4 mov edx, dword ptr [esi]
0067d2c6 mov dword ptr [esi + 0x3ac], ecx
0067d2cc mov dword ptr [esi + 0x3b0], ecx
0067d2d2 mov ecx, esi
0067d2d4 mulss xmm0, dword ptr [edi + 0x384]
0067d2dc movss dword ptr [esp], xmm0
0067d2e1 call dword ptr [edx + 0x3c]
0067d2e4 movss xmm0, dword ptr [0xbc7a28]
0067d2ec xorps xmm0, xmmword ptr [0xb6c9b0]
0067d2f3 movss dword ptr [ebp - 0x80], xmm0
0067d2f8 movss xmm0, dword ptr [0xbc7a2c]
0067d300 xorps xmm0, xmmword ptr [0xb6c9b0]
0067d307 push -1
0067d309 movss dword ptr [ebp - 0x7c], xmm0
0067d30e push dword ptr [ebp - 0x7c]
0067d311 movss xmm0, dword ptr [esi + 0x2c8]
0067d319 push dword ptr [ebp - 0x80]
0067d31c mulss xmm0, dword ptr [edi + 0x384]
0067d324 push ecx
0067d325 mov ecx, esi
0067d327 movss dword ptr [esp], xmm0
0067d32c call 0x6843a0
0067d331 movss xmm1, dword ptr [edi + 0x384]
0067d339 mov eax, dword ptr [esi]
0067d33b movaps xmm0, xmm1
0067d33e mulss xmm0, dword ptr [0xbc7a28]
0067d346 mov ecx, esi
0067d348 mulss xmm1, dword ptr [0xbc7a2c]
0067d350 movss dword ptr [esi + 0xd8], xmm0
0067d358 movss dword ptr [esi + 0xdc], xmm1
0067d360 call dword ptr [eax + 0xc]
0067d363 cmp dword ptr [edi + 0x354], 0
0067d36a mov byte ptr [edi + 0x16b], 1
0067d371 jne 0x67d382
0067d373 push 0
0067d375 push 0xb42eec
0067d37a lea ecx, [edi + 0x3c]
0067d37d call 0x4054f0
0067d382 cmp byte ptr [edi + 0x398], 0
0067d389 lea edx, [edi + 0x388]
0067d38f je 0x67d960
0067d395 push 0xbc49a0
0067d39a lea ecx, [ebp - 0xe0]
0067d3a0 call 0x412050
0067d3a5 add esp, 4
0067d3a8 mov ecx, dword ptr [eax]
0067d3aa or ecx, dword ptr [eax + 4]
0067d3ad jne 0x67d3bb
0067d3af mov ecx, dword ptr [eax + 8]
0067d3b2 or ecx, dword ptr [eax + 0xc]
0067d3b5 je 0x67d493
0067d3bb call 0x6c3d90
0067d3c0 push 0
0067d3c2 mov ecx, dword ptr [0xbfd65c]
0067d3c8 push 0xbeacac
0067d3cd push 0xbeab18
0067d3d2 push 0
0067d3d4 push eax
0067d3d5 push 0
0067d3d7 push dword ptr [edi + 0x320]
0067d3dd lea eax, [edi + 0x2b8]
0067d3e3 push eax
0067d3e4 lea eax, [edi + 0x294]
0067d3ea push eax
0067d3eb push dword ptr [edi + 0x2c]
0067d3ee push 4
0067d3f0 call 0x422e20
0067d3f5 push eax
0067d3f6 call 0x9ec34c
0067d3fb mov ecx, dword ptr [edi + 0x34]
0067d3fe mov esi, eax
0067d400 add esp, 0x14
0067d403 lea eax, [ebp - 0xe0]
0067d409 mov dword ptr [esi + 0x34], ecx
0067d40c mov ecx, dword ptr [edi + 0x38]
0067d40f mov dword ptr [esi + 0x38], ecx
0067d412 mov ecx, 0xbc49a0
0067d417 push eax
0067d418 mov byte ptr [esi + 0x398], 1
0067d41f call 0x57f3a0
0067d424 push eax
0067d425 lea edx, [edi + 0x388]
0067d42b lea ecx, [ebp - 0xa8]
0067d431 call 0x412050
0067d436 add esp, 4
0067d439 movups xmm0, xmmword ptr [eax]
0067d43c mov eax, dword ptr [esi + 0x2c]
0067d43f mov byte ptr [esi + 0x3b3], 1
0067d446 movups xmmword ptr [esi + 0x388], xmm0
0067d44d cmp eax, 0x13
0067d450 je 0x67d45e
0067d452 cmp eax, 0x14
0067d455 je 0x67d45e
0067d457 mov eax, 0x1e
0067d45c jmp 0x67d46f
0067d45e mov eax, dword ptr [edi + 0x378]
0067d464 mov dword ptr [esi + 0x378], eax
0067d46a mov eax, 0x3c
0067d46f mov edx, esi
0067d471 mov ecx, esi
0067d473 mov dword ptr [edx + 0x360], eax
0067d479 mov dword ptr [ecx + 0x364], eax
0067d47f or dword ptr [esi + 0x160], 0x4000000
0067d489 or dword ptr [esi + 0x164], 0x400
0067d493 push 0xbc49e0
0067d498 lea edx, [edi + 0x388]
0067d49e lea ecx, [ebp - 0xe0]
0067d4a4 call 0x412050
0067d4a9 add esp, 4
0067d4ac mov ecx, dword ptr [eax]
0067d4ae or ecx, dword ptr [eax + 4]
0067d4b1 jne 0x67d4bf
0067d4b3 mov ecx, dword ptr [eax + 8]
0067d4b6 or ecx, dword ptr [eax + 0xc]
0067d4b9 je 0x67d6a2
0067d4bf movss xmm1, dword ptr [edi + 0x2bc]
0067d4c7 movss xmm2, dword ptr [edi + 0x2b8]
0067d4cf movaps xmm0, xmm1
0067d4d2 xorps xmm2, xmmword ptr [0xb6c9b0]
0067d4d9 mulss xmm0, xmm1
0067d4dd movss dword ptr [ebp - 0x98], xmm1
0067d4e5 movaps xmm1, xmm2
0067d4e8 mulss xmm1, xmm2
0067d4ec movss dword ptr [ebp - 0x78], xmm2
0067d4f1 addss xmm0, xmm1
0067d4f5 call 0x4228c0
0067d4fa comiss xmm0, dword ptr [0xb6a18c]
0067d501 movss xmm4, dword ptr [ebp - 0x98]
0067d509 movss xmm3, dword ptr [ebp - 0x78]
0067d50e jbe 0x67d534
0067d510 movss xmm1, dword ptr [0xb6a614]
0067d518 divss xmm1, xmm0
0067d51c movaps xmm0, xmm1
0067d51f mulss xmm3, xmm1
0067d523 mulss xmm4, xmm0
0067d527 movss dword ptr [ebp - 0x78], xmm3
0067d52c movss dword ptr [ebp - 0x98], xmm4
0067d534 movss xmm2, dword ptr [ebp - 0x70]
0067d539 nop dword ptr [eax]
0067d540 call 0x6c3d90
0067d545 movss xmm1, dword ptr [edi + 0x2c8]
0067d54d movaps xmm0, xmm4
0067d550 mulss xmm0, xmm2
0067d554 push 0
0067d556 mov ecx, dword ptr [0xbfd65c]
0067d55c push 0xbeacac
0067d561 mulss xmm0, dword ptr [0xb6a8f4]
0067d569 push 0xbeab18
0067d56e push 0
0067d570 push eax
0067d571 movss dword ptr [ebp - 0xc0], xmm0
0067d579 lea eax, [ebp - 0xc0]
0067d57f movaps xmm0, xmm3
0067d582 mulss xmm0, xmm2
0067d586 push 0
0067d588 push dword ptr [edi + 0x320]
0067d58e mulss xmm0, dword ptr [0xb6a8f4]
0067d596 push eax
0067d597 lea eax, [ebp - 0x80]
0067d59a push eax
0067d59b movss dword ptr [ebp - 0xbc], xmm0
0067d5a3 movaps xmm0, xmm4
0067d5a6 mulss xmm0, xmm1
0067d5aa push dword ptr [ebp - 0x74]
0067d5ad mulss xmm0, xmm2
0067d5b1 push 4
0067d5b3 addss xmm0, dword ptr [edi + 0x294]
0067d5bb movss dword ptr [ebp - 0x80], xmm0
0067d5c0 movaps xmm0, xmm3
0067d5c3 mulss xmm0, xmm1
0067d5c7 mulss xmm0, xmm2
0067d5cb addss xmm0, dword ptr [edi + 0x298]
0067d5d3 movss dword ptr [ebp - 0x7c], xmm0
0067d5d8 call 0x422e20
0067d5dd push eax
0067d5de call 0x9ec34c
0067d5e3 mov ecx, dword ptr [edi + 0x34]
0067d5e6 mov esi, eax
0067d5e8 add esp, 0x14
0067d5eb lea eax, [ebp - 0xe0]
0067d5f1 mov dword ptr [esi + 0x34], ecx
0067d5f4 mov ecx, dword ptr [edi + 0x38]
0067d5f7 mov dword ptr [esi + 0x38], ecx
0067d5fa mov ecx, 0xbc49e0
0067d5ff push eax
0067d600 mov byte ptr [esi + 0x398], 1
0067d607 call 0x57f3a0
0067d60c push eax
0067d60d lea edx, [edi + 0x388]
0067d613 lea ecx, [ebp - 0xa8]
0067d619 call 0x412050
0067d61e movss xmm2, dword ptr [ebp - 0x70]
0067d623 add esp, 4
0067d626 addss xmm2, dword ptr [0xb6a7b0]
0067d62e movss xmm3, dword ptr [ebp - 0x78]
0067d633 movups xmm0, xmmword ptr [eax]
0067d636 or dword ptr [esi + 0x160], 0x4000000
0067d640 or dword ptr [esi + 0x164], 0x400
0067d64a movss xmm4, dword ptr [ebp - 0x98]
0067d652 movups xmmword ptr [esi + 0x388], xmm0
0067d659 mov byte ptr [esi + 0x3b3], 1
0067d660 movss xmm0, dword ptr [esi + 0x368]
0067d668 mulss xmm0, dword ptr [0xb6a434]
0067d670 mov dword ptr [esi + 0x360], 0xf
0067d67a mov dword ptr [esi + 0x364], 0xf
0067d684 movss dword ptr [ebp - 0x70], xmm2
0067d689 movss dword ptr [esi + 0x368], xmm0
0067d691 movss xmm0, dword ptr [0xb6a614]
0067d699 comiss xmm0, xmm2
0067d69c jae 0x67d540
0067d6a2 push 0xbc4a00
0067d6a7 lea edx, [edi + 0x388]
0067d6ad lea ecx, [ebp - 0xe0]
0067d6b3 call 0x412050
0067d6b8 add esp, 4
0067d6bb mov ecx, dword ptr [eax]
0067d6bd or ecx, dword ptr [eax + 4]
0067d6c0 jne 0x67d6ce
0067d6c2 mov ecx, dword ptr [eax + 8]
0067d6c5 or ecx, dword ptr [eax + 0xc]
0067d6c8 je 0x67da0e
0067d6ce call 0x6c3d90
0067d6d3 movd xmm0, eax
0067d6d7 cvtdq2pd xmm0, xmm0
0067d6db shr eax, 0x1f
0067d6de addsd xmm0, qword ptr [eax*8 + 0xb6c940]
0067d6e7 cvtpd2ps xmm0, xmm0
0067d6eb mulss xmm0, dword ptr [0xb6a19c]
0067d6f3 mulss xmm0, dword ptr [0xb6a874]
0067d6fb addss xmm0, xmm0
0067d6ff movss dword ptr [ebp - 0x7c], xmm0
0067d704 call 0x411fe0
0067d709 movss dword ptr [ebp - 0x70], xmm0
0067d70e movss xmm0, dword ptr [ebp - 0x7c]
0067d713 call 0x412010
0067d718 movaps xmm4, xmm0
0067d71b movss xmm0, dword ptr [0xb6a704]
0067d723 movss dword ptr [ebp - 0x78], xmm4
0067d728 call 0x411fe0
0067d72d movss dword ptr [ebp - 0xc4], xmm0
0067d735 movss xmm0, dword ptr [0xb6a704]
0067d73d call 0x412010
0067d742 movss xmm1, dword ptr [0xb6a91c]
0067d74a movss xmm3, dword ptr [ebp - 0x70]
0067d74f movss xmm2, dword ptr [ebp - 0x78]
0067d754 movss dword ptr [ebp - 0x7c], xmm0
0067d759 mov dword ptr [ebp - 0x6c], 4
0067d760 call 0x6c3d90
0067d765 movaps xmm0, xmm3
0067d768 mov ecx, dword ptr [0xbfd65c]
0067d76e mulss xmm0, xmm1
0067d772 push 0
0067d774 push 0xbeacac
0067d779 push 0xbeab18
0067d77e movss dword ptr [ebp - 0xc0], xmm0
0067d786 movaps xmm0, xmm2
0067d789 mulss xmm0, xmm1
0067d78d push 0
0067d78f movss xmm1, dword ptr [edi + 0x2c8]
0067d797 push eax
0067d798 movss dword ptr [ebp - 0xbc], xmm0
0067d7a0 lea eax, [ebp - 0xc0]
0067d7a6 movaps xmm0, xmm3
0067d7a9 mulss xmm0, xmm1
0067d7ad push 0
0067d7af push dword ptr [edi + 0x320]
0067d7b5 addss xmm0, dword ptr [edi + 0x294]
0067d7bd push eax
0067d7be lea eax, [ebp - 0x94]
0067d7c4 push eax
0067d7c5 push dword ptr [ebp - 0x74]
0067d7c8 movss dword ptr [ebp - 0x94], xmm0
0067d7d0 movaps xmm0, xmm2
0067d7d3 push dword ptr [edi + 0x28]
0067d7d6 mulss xmm0, xmm1
0067d7da addss xmm0, dword ptr [edi + 0x298]
0067d7e2 movss dword ptr [ebp - 0x90], xmm0
0067d7ea call 0x422e20
0067d7ef push eax
0067d7f0 call 0x9ec34c
0067d7f5 mov ecx, dword ptr [edi + 0x34]
0067d7f8 mov esi, eax
0067d7fa add esp, 0x14
0067d7fd lea eax, [ebp - 0xa8]
0067d803 mov dword ptr [esi + 0x34], ecx
0067d806 mov ecx, dword ptr [edi + 0x38]
0067d809 mov dword ptr [esi + 0x38], ecx
0067d80c mov ecx, 0xbc4a00
0067d811 push eax
0067d812 mov byte ptr [esi + 0x398], 1
0067d819 call 0x57f3a0
0067d81e push eax
0067d81f lea edx, [edi + 0x388]
0067d825 lea ecx, [ebp - 0xf0]
0067d82b call 0x412050
0067d830 movss xmm1, dword ptr [0xb6a480]
0067d838 add esp, 4
0067d83b movups xmm0, xmmword ptr [eax]
0067d83e mov byte ptr [esi + 0x3b3], 1
0067d845 push -1
0067d847 movups xmmword ptr [esi + 0x388], xmm0
0067d84e movss xmm0, dword ptr [edi + 0x384]
0067d856 mulss xmm0, xmm1
0067d85a movss dword ptr [esi + 0x384], xmm0
0067d862 movss xmm0, dword ptr [esi + 0x368]
0067d86a mulss xmm0, dword ptr [0xb6a3f8]
0067d872 movss dword ptr [esi + 0x368], xmm0
0067d87a movss xmm0, dword ptr [edi + 0x39c]
0067d882 mulss xmm0, xmm1
0067d886 movss dword ptr [esi + 0x39c], xmm0
0067d88e movss xmm0, dword ptr [0xbc7a28]
0067d896 xorps xmm0, xmmword ptr [0xb6c9b0]
0067d89d movss dword ptr [ebp - 0xb8], xmm0
0067d8a5 movss xmm0, dword ptr [0xbc7a2c]
0067d8ad xorps xmm0, xmmword ptr [0xb6c9b0]
0067d8b4 movss dword ptr [ebp - 0xb4], xmm0
0067d8bc push dword ptr [ebp - 0xb4]
0067d8c2 movss xmm0, dword ptr [esi + 0x2c8]
0067d8ca push dword ptr [ebp - 0xb8]
0067d8d0 mulss xmm0, xmm1
0067d8d4 push ecx
0067d8d5 mov ecx, esi
0067d8d7 movss dword ptr [esp], xmm0
0067d8dc call 0x6843a0
0067d8e1 or dword ptr [esi + 0x160], 0x4000000
0067d8eb or dword ptr [esi + 0x164], 0x400
0067d8f5 mov dword ptr [esi + 0x360], 7
0067d8ff mov dword ptr [esi + 0x364], 7
0067d909 sub dword ptr [ebp - 0x6c], 1
0067d90d movss xmm0, dword ptr [ebp - 0x7c]
0067d912 mulss xmm0, dword ptr [ebp - 0x78]
0067d917 movss xmm3, dword ptr [ebp - 0xc4]
0067d91f mulss xmm3, dword ptr [ebp - 0x70]
0067d924 movss xmm2, dword ptr [ebp - 0x7c]
0067d929 mulss xmm2, dword ptr [ebp - 0x70]
0067d92e movss xmm1, dword ptr [0xb6a91c]
0067d936 subss xmm3, xmm0
0067d93a movss xmm0, dword ptr [ebp - 0xc4]
0067d942 mulss xmm0, dword ptr [ebp - 0x78]
0067d947 movss dword ptr [ebp - 0x70], xmm3
0067d94c addss xmm2, xmm0
0067d950 movss dword ptr [ebp - 0x78], xmm2
0067d955 jne 0x67d760
0067d95b jmp 0x67da0e
0067d960 push 0xbc4950
0067d965 lea ecx, [ebp - 0xf0]
0067d96b call 0x412050
0067d970 add esp, 4
0067d973 mov ecx, dword ptr [eax]
0067d975 or ecx, dword ptr [eax + 4]
0067d978 jne 0x67d982
0067d97a mov ecx, dword ptr [eax + 8]
0067d97d or ecx, dword ptr [eax + 0xc]
0067d980 je 0x67d9a2
0067d982 mov ecx, dword ptr [edi + 0x3a0]
0067d988 test ecx, ecx
0067d98a je 0x67d9a2
0067d98c mov eax, dword ptr [ecx + 0x164]
0067d992 or dword ptr [ecx + 0x160], 0x400000
0067d99c mov dword ptr [ecx + 0x164], eax
0067d9a2 cmp dword ptr [edi + 0x2c], 0xd
0067d9a6 je 0x67da0e
0067d9a8 mov esi, dword ptr [ebp - 0xac]
0067d9ae test esi, esi
0067d9b0 je 0x67da0e
0067d9b2 push 0
0067d9b4 push 0x49
0067d9b6 mov ecx, esi
0067d9b8 call 0x73b950
0067d9bd test al, al
0067d9bf je 0x67da0e
0067d9c1 push 0x49
0067d9c3 mov ecx, esi
0067d9c5 call 0x78d4c0
0067d9ca mov ecx, eax
0067d9cc mov eax, 0xa
0067d9d1 cdq 
0067d9d2 idiv ecx
0067d9d4 mov ecx, esi
0067d9d6 push eax
0067d9d7 push 0x49
0067d9d9 call 0x639000
0067d9de mov ecx, eax
0067d9e0 call 0x7a7d50
0067d9e5 test eax, eax
0067d9e7 jne 0x67da0e
0067d9e9 call 0x6c3d90
0067d9ee mov ecx, dword ptr [0xbfd65c]
0067d9f4 push eax
0067d9f5 push 1
0067d9f7 push 0
0067d9f9 push 0xc02fec
0067d9fe lea eax, [edi + 0x294]
0067da04 push eax
0067da05 push 0x28
0067da07 push 5
0067da09 call 0x422e20
0067da0e cmp dword ptr [edi + 0x2c], 0x12
0067da12 jne 0x67dafb
0067da18 lea esi, [edi + 0x334]
0067da1e mov byte ptr [edi + 0x16b], 0
0067da25 mov ecx, esi
0067da27 call 0x7a7e20
0067da2c mov eax, dword ptr [esi]
0067da2e xor edx, edx
0067da30 mov ecx, 0x1e
0067da35 div ecx
0067da37 push 1
0067da39 add edx, 0x3c
0067da3c lea ecx, [edi + 0x3c]
0067da3f push 0xb40360
0067da44 mov dword ptr [edi + 0x360], edx
0067da4a call 0x405740
0067da4f test al, al
0067da51 je 0x67da68
0067da53 lea ecx, [edi + 0x6c]
0067da56 call 0x405330
0067da5b mov byte ptr [edi + 0x80], 1
0067da62 lea esi, [edi + 0x334]
0067da68 cmp dword ptr [edi + 0x70], 0
0067da6c je 0x67da7e
0067da6e movss xmm1, dword ptr [0xb6a940]
0067da76 lea ecx, [edi + 0x6c]
0067da79 call 0x403c00
0067da7e mov ecx, esi
0067da80 call 0x7a7e20
0067da85 mov eax, dword ptr [esi]
0067da87 mov ecx, esi
0067da89 movd xmm0, eax
0067da8d cvtdq2pd xmm0, xmm0
0067da91 shr eax, 0x1f
0067da94 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
0067da9d cvtpd2ps xmm0, xmm0
0067daa1 mulss xmm0, dword ptr [0xb6a198]
0067daa9 mulss xmm0, dword ptr [0xb6a8f4]
0067dab1 addss xmm0, dword ptr [0xb6a8f4]
0067dab9 movss dword ptr [ebp - 0x7c], xmm0
0067dabe call 0x7a7e20
0067dac3 mov edx, eax
0067dac5 lea ecx, [ebp - 0xc8]
0067dacb call 0x6592f0
0067dad0 movss xmm1, dword ptr [ebp - 0x7c]
0067dad5 movaps xmm0, xmm1
0067dad8 mulss xmm0, dword ptr [eax]
0067dadc mulss xmm1, dword ptr [eax + 4]
0067dae1 movss dword ptr [edi + 0x2b8], xmm0
0067dae9 movss dword ptr [edi + 0x2bc], xmm1
0067daf1 mov dword ptr [edi + 0x3ac], 0x5a
0067dafb mov ecx, dword ptr [edi + 0x164]
0067db01 xor eax, eax
0067db03 and ecx, 0x400
0067db09 or eax, ecx
0067db0b jne 0x67db64
0067db0d mov esi, dword ptr [ebp - 0xac]
0067db13 test esi, esi
0067db15 je 0x67db64
0067db17 cmp dword ptr [edi + 0x320], esi
0067db1d jne 0x67db64
0067db1f cmp byte ptr [edi + 0x398], al
0067db25 jne 0x67db64
0067db27 push 0x89
0067db2c lea ecx, [esi + 0x1450]
0067db32 call 0x88b570
0067db37 test al, al
0067db39 je 0x67db64
0067db3b push 0
0067db3d push 0x248
0067db42 mov ecx, esi
0067db44 call 0x73af30
0067db49 test al, al
0067db4b je 0x67db64
0067db4d push 0
0067db4f push 0
0067db51 lea eax, [edi + 0x294]
0067db57 mov ecx, esi
0067db59 push eax
0067db5a push 0x89
0067db5f call 0x5b4730
0067db64 cmp dword ptr [edi + 0x2c], 4
0067db68 jne 0x67dcc7
0067db6e mov ecx, dword ptr [0xbfd65c]
0067db74 lea esi, [edi + 0x294]
0067db7a push esi
0067db7b call 0x6d5e30
0067db80 mov ecx, dword ptr [0xbfd65c]
0067db86 push esi
0067db87 movss xmm2, dword ptr [eax + 0x2b8]
0067db8f movss xmm0, dword ptr [eax + 0x2bc]
0067db97 movss dword ptr [ebp - 0x74], xmm2
0067db9c movss dword ptr [ebp - 0x78], xmm0
0067dba1 call 0x6d5e30
0067dba6 movss xmm0, dword ptr [ebp - 0x78]
0067dbab mulss xmm0, dword ptr [0xb6a8f4]
0067dbb3 movss xmm1, dword ptr [ebp - 0x74]
0067dbb8 mulss xmm1, dword ptr [0xb6a8f4]
0067dbc0 addss xmm0, dword ptr [eax + 0x298]
0067dbc8 addss xmm1, dword ptr [eax + 0x294]
0067dbd0 subss xmm0, dword ptr [esi + 4]
0067dbd5 subss xmm1, dword ptr [esi]
0067dbd9 movaps xmm2, xmm0
0067dbdc movss dword ptr [ebp - 0x78], xmm0
0067dbe1 mulss xmm2, xmm0
0067dbe5 movaps xmm0, xmm1
0067dbe8 movss dword ptr [ebp - 0x74], xmm1
0067dbed mulss xmm0, xmm1
0067dbf1 movss xmm1, dword ptr [0xb6ad78]
0067dbf9 addss xmm2, xmm0
0067dbfd comiss xmm1, xmm2
0067dc00 jbe 0x67dc6b
0067dc02 movaps xmm0, xmm2
0067dc05 call 0x4228c0
0067dc0a comiss xmm0, dword ptr [0xb6a18c]
0067dc11 movss xmm2, dword ptr [ebp - 0x74]
0067dc16 jbe 0x67dc36
0067dc18 movss xmm1, dword ptr [0xb6a614]
0067dc20 divss xmm1, xmm0
0067dc24 movaps xmm0, xmm1
0067dc27 mulss xmm2, xmm0
0067dc2b movss xmm0, dword ptr [ebp - 0x78]
0067dc30 mulss xmm0, xmm1
0067dc34 jmp 0x67dc3b
0067dc36 movss xmm0, dword ptr [ebp - 0x78]
0067dc3b mulss xmm2, dword ptr [0xb6a6f0]
0067dc43 mulss xmm0, dword ptr [0xb6a6f0]
0067dc4b addss xmm2, dword ptr [edi + 0x2b8]
0067dc53 addss xmm0, dword ptr [edi + 0x2bc]
0067dc5b movss dword ptr [edi + 0x2b8], xmm2
0067dc63 movss dword ptr [edi + 0x2bc], xmm0
0067dc6b movss xmm0, dword ptr [edi + 0x2b8]
0067dc73 movss xmm2, dword ptr [0xb6a560]
0067dc7b mov eax, dword ptr [0xbfd65c]
0067dc80 mulss xmm0, xmm2
0067dc84 movss dword ptr [edi + 0x2b8], xmm0
0067dc8c movss xmm0, dword ptr [edi + 0x2bc]
0067dc94 mulss xmm0, xmm2
0067dc98 movss dword ptr [edi + 0x2bc], xmm0
0067dca0 mov eax, dword ptr [eax + 0x1a30dc]
0067dca6 sub eax, dword ptr [edi + 0x280]
0067dcac cmp eax, 0x14
0067dcaf jge 0x67dccf
0067dcb1 movss xmm0, dword ptr [edi + 0x2c4]
0067dcb9 mulss xmm0, xmm2
0067dcbd movss dword ptr [edi + 0x2c4], xmm0
0067dcc5 jmp 0x67dccf
0067dcc7 movss xmm2, dword ptr [0xb6a560]
0067dccf movzx eax, word ptr [edi + 0x380]
0067dcd6 test ax, ax
0067dcd9 jle 0x67dce3
0067dcdb dec eax
0067dcdc mov word ptr [edi + 0x380], ax
0067dce3 movzx eax, word ptr [edi + 0x382]
0067dcea test ax, ax
0067dced jle 0x67dcf7
0067dcef dec eax
0067dcf0 mov word ptr [edi + 0x382], ax
0067dcf7 mov eax, dword ptr [edi + 0x3ac]
0067dcfd test eax, eax
0067dcff jle 0x67dd08
0067dd01 dec eax
0067dd02 mov dword ptr [edi + 0x3ac], eax
0067dd08 mov edx, dword ptr [0xbfd65c]
0067dd0e mov esi, dword ptr [edi + 0x280]
0067dd14 mov ecx, dword ptr [edx + 0x1a30dc]
0067dd1a mov eax, ecx
0067dd1c sub eax, esi
0067dd1e cmp eax, 0xf
0067dd21 jle 0x67dd3c
0067dd23 cmp dword ptr [edi + 0x180], 1
0067dd2a jne 0x67dd3c
0067dd2c mov dword ptr [edi + 0x180], 4
0067dd36 mov ecx, dword ptr [edx + 0x1a30dc]
0067dd3c sub ecx, esi
0067dd3e cmp ecx, dword ptr [edi + 0x360]
0067dd44 jle 0x67dd59
0067dd46 cmp dword ptr [edi + 0x180], 0
0067dd4d jne 0x67dd59
0067dd4f mov dword ptr [edi + 0x180], 4
0067dd59 mov eax, dword ptr [0xbfd65c]
0067dd5e mov eax, dword ptr [eax + 0x18190]
0067dd64 cmp dword ptr [eax + 8], 0x10
0067dd68 jne 0x67dd8f
0067dd6a mov eax, dword ptr [edi + 0x2c]
0067dd6d cmp eax, 0x13
0067dd70 je 0x67dd8f
0067dd72 cmp eax, 0x14
0067dd75 je 0x67dd8f
0067dd77 movss xmm0, dword ptr [edi + 0x2bc]
0067dd7f addss xmm0, dword ptr [0xb6a5a4]
0067dd87 movss dword ptr [edi + 0x2bc], xmm0
0067dd8f cmp dword ptr [edi + 0x2c], 0xf
0067dd93 jne 0x67de22
0067dd99 movss xmm0, dword ptr [edi + 0x2a8]
0067dda1 xorps xmm1, xmm1
0067dda4 comiss xmm0, xmm1
0067dda7 jb 0x67ddca
0067dda9 movss xmm0, dword ptr [edi + 0x36c]
0067ddb1 comiss xmm0, xmm1
0067ddb4 jb 0x67ddca
0067ddb6 movss xmm0, dword ptr [edi + 0x2c4]
0067ddbe mulss xmm0, xmm2
0067ddc2 movss dword ptr [edi + 0x2c4], xmm0
0067ddca cmp dword ptr [edi + 0x70], 0
0067ddce je 0x67de22
0067ddd0 push 0xb48cc4
0067ddd5 lea ecx, [edi + 0x6c]
0067ddd8 call 0x405e90
0067dddd test al, al
0067dddf je 0x67de22
0067dde1 mov esi, dword ptr [0xbfd680]
0067dde7 lea ecx, [ebp - 0x6c]
0067ddea mov dword ptr [ebp - 0x6c], 0xab
0067ddf1 call 0x8b1340
0067ddf6 sub esp, 8
0067ddf9 mov dword ptr [esp + 4], 0
0067de01 mov dword ptr [esp], 0x3fc00000
0067de08 push 0
0067de0a push 2
0067de0c push ecx
0067de0d mov dword ptr [esp], 0x3f800000
0067de14 lea ecx, [esi + 0x29de0]
0067de1a push dword ptr [ebp - 0x6c]
0067de1d call 0x888de0
0067de22 mov eax, dword ptr [edi + 0x3a0]
0067de28 test eax, eax
0067de2a je 0x67de92
0067de2c movss xmm0, dword ptr [eax + 0x2b8]
0067de34 movss xmm1, dword ptr [eax + 0x2bc]
0067de3c movss dword ptr [edi + 0x2b8], xmm0
0067de44 movss dword ptr [edi + 0x2bc], xmm1
0067de4c movss xmm0, dword ptr [eax + 0x294]
0067de54 movss xmm1, dword ptr [eax + 0x298]
0067de5c addss xmm0, dword ptr [edi + 0x28c]
0067de64 addss xmm1, dword ptr [edi + 0x290]
0067de6c movss dword ptr [edi + 0x294], xmm0
0067de74 movss dword ptr [edi + 0x298], xmm1
0067de7c mov dword ptr [edi + 0x180], 0
0067de86 mov dword ptr [edi + 0x17c], 0
0067de90 jmp 0x67dea5
0067de92 cmp dword ptr [edi + 0x17c], 0
0067de99 jne 0x67dea5
0067de9b mov dword ptr [edi + 0x17c], 5
0067dea5 cmp byte ptr [edi + 0x169], 0
0067deac jne 0x67dece
0067deae mov eax, 4
0067deb3 mov dword ptr [edi + 0x180], 0
0067debd mov dword ptr [edi + 0x17c], 0
0067dec7 mov word ptr [edi + 0x380], ax
0067dece cmp dword ptr [edi + 0x70], 0
0067ded2 je 0x67dfa1
0067ded8 push 0xb48ccc
0067dedd lea ecx, [edi + 0x6c]
0067dee0 call 0x405e90
0067dee5 test al, al
0067dee7 je 0x67dfa1
0067deed mov eax, dword ptr [edi + 0x2c]
0067def0 sub esp, 8
0067def3 mov dword ptr [esp + 4], 0
0067defb cmp eax, 0x11
0067defe jne 0x67df35
0067df00 mov dword ptr [esp], 0x3f4ccccd
0067df07 push 0
0067df09 push 4
0067df0b push ecx
0067df0c mov ecx, dword ptr [0xbfd680]
0067df12 mov dword ptr [esp], 0x3f800000
0067df19 push 0x28
0067df1b lea ecx, [ecx + 0x29de0]
0067df21 call 0x888de0
0067df26 mov ecx, dword ptr [0xbfd65c]
0067df2c push 6
0067df2e call 0x6d5ad0
0067df33 jmp 0x67dfa1
0067df35 movss xmm0, dword ptr [edi + 0x384]
0067df3d movss xmm1, dword ptr [0xb6a614]
0067df45 mov dword ptr [esp], 0x3f800000
0067df4c push 0
0067df4e push 4
0067df50 cmp eax, 0x12
0067df53 jne 0x67df79
0067df55 comiss xmm1, xmm0
0067df58 ja 0x67df60
0067df5a movss xmm0, xmm1
0067df5e jmp 0x67df64
0067df60 movss xmm0, xmm0
0067df64 push ecx
0067df65 mulss xmm0, dword ptr [0xb6a560]
0067df6d movss dword ptr [esp], xmm0
0067df72 push 0x1d2
0067df77 jmp 0x67df90
0067df79 comiss xmm1, xmm0
0067df7c ja 0x67df84
0067df7e movss xmm0, xmm1
0067df82 jmp 0x67df88
0067df84 movss xmm0, xmm0
0067df88 push ecx
0067df89 movss dword ptr [esp], xmm0
0067df8e push 0x28
0067df90 mov ecx, dword ptr [0xbfd680]
0067df96 lea ecx, [ecx + 0x29de0]
0067df9c call 0x888de0
0067dfa1 cmp byte ptr [edi + 0x3b2], 0
0067dfa8 je 0x67dfe4
0067dfaa mov eax, 5
0067dfaf lea esi, [edi + 0x4bd]
0067dfb5 mov dword ptr [ebp - 0x6c], eax
0067dfb8 cmp byte ptr [esi], 0
0067dfbb je 0x67dfd6
0067dfbd lea ecx, [esi - 0xd9]
0067dfc3 call 0x403d60
0067dfc8 lea ecx, [esi - 0xb9]
0067dfce call 0x403d60
0067dfd3 mov eax, dword ptr [ebp - 0x6c]
0067dfd6 add esi, 0x114
0067dfdc sub eax, 1
0067dfdf mov dword ptr [ebp - 0x6c], eax
0067dfe2 jne 0x67dfb8
0067dfe4 mov eax, dword ptr [edi + 0x2c]
0067dfe7 cmp eax, 0x13
0067dfea je 0x67dff5
0067dfec cmp eax, 0x14
0067dfef jne 0x67e26c
0067dff5 movss xmm2, dword ptr [ebp - 0xb0]
0067dffd movss xmm3, dword ptr [0xb6ac40]
0067e005 movaps xmm0, xmm2
0067e008 andps xmm0, xmmword ptr [0xb6c980]
0067e00f movaps xmm1, xmm2
0067e012 comiss xmm0, xmm3
0067e015 jbe 0x67e02d
0067e017 movaps xmm1, xmm3
0067e01a movaps xmm0, xmm2
0067e01d call 0x447b40
0067e022 movss xmm3, dword ptr [0xb6ac40]
0067e02a movaps xmm1, xmm0
0067e02d movss xmm2, dword ptr [0xb6ab88]
0067e035 comiss xmm1, xmm2
0067e038 jbe 0x67e040
0067e03a subss xmm1, xmm3
0067e03e jmp 0x67e051
0067e040 movss xmm0, dword ptr [0xb6af74]
0067e048 comiss xmm0, xmm1
0067e04b jbe 0x67e051
0067e04d addss xmm1, xmm3
0067e051 mov ecx, dword ptr [edi + 0x164]
0067e057 xor eax, eax
0067e059 and ecx, 0x2000000
0067e05f or eax, ecx
0067e061 je 0x67e06f
0067e063 mov byte ptr [edi + 0x13c], 0
0067e06a xorps xmm1, xmm1
0067e06d jmp 0x67e09c
0067e06f comiss xmm1, dword ptr [0xb6aae4]
0067e076 ja 0x67e08e
0067e078 movss xmm0, dword ptr [0xb6af48]
0067e080 comiss xmm0, xmm1
0067e083 ja 0x67e08e
0067e085 mov byte ptr [edi + 0x13c], 0
0067e08c jmp 0x67e09c
0067e08e subss xmm2, xmm1
0067e092 mov byte ptr [edi + 0x13c], 1
0067e099 movaps xmm1, xmm2
0067e09c movss dword ptr [edi + 0xe0], xmm1
0067e0a4 xorps xmm2, xmm2
0067e0a7 movss xmm1, dword ptr [0xb6a7b0]
0067e0af mov ecx, edi
0067e0b1 call 0x6847e0
0067e0b6 test eax, eax
0067e0b8 je 0x67e26c
0067e0be cmp byte ptr [edi + 0x169], 0
0067e0c5 je 0x67e26c
0067e0cb call 0x6c3d90
0067e0d0 movss xmm0, dword ptr [edi + 0x2b8]
0067e0d8 mov esi, eax
0067e0da mulss xmm0, dword ptr [0xb6a300]
0067e0e2 movss xmm1, dword ptr [ebp - 0xb0]
0067e0ea mulss xmm1, dword ptr [0xb6a230]
0067e0f2 movss dword ptr [ebp - 0xc0], xmm0
0067e0fa movss xmm0, dword ptr [edi + 0x2bc]
0067e102 mulss xmm0, dword ptr [0xb6a300]
0067e10a movss dword ptr [ebp - 0xb0], xmm1
0067e112 movss dword ptr [ebp - 0xbc], xmm0
0067e11a movaps xmm0, xmm1
0067e11d call 0x411fe0
0067e122 mulss xmm0, dword ptr [0xb6a8f4]
0067e12a movss xmm1, dword ptr [edi + 0x294]
0067e132 mulss xmm0, dword ptr [edi + 0x384]
0067e13a subss xmm1, xmm0
0067e13e movss xmm0, dword ptr [ebp - 0xb0]
0067e146 movss dword ptr [ebp - 0x80], xmm1
0067e14b call 0x412010
0067e150 mulss xmm0, dword ptr [0xb6a8f4]
0067e158 lea eax, [ebp - 0xc0]
0067e15e mov ecx, dword ptr [0xbfd65c]
0067e164 movss xmm1, dword ptr [edi + 0x298]
0067e16c push esi
0067e16d mulss xmm0, dword ptr [edi + 0x384]
0067e175 push 0
0067e177 push 0
0067e179 push eax
0067e17a lea eax, [ebp - 0x80]
0067e17d subss xmm1, xmm0
0067e181 push eax
0067e182 push 0x3b
0067e184 push 0x3e8
0067e189 movss dword ptr [ebp - 0x7c], xmm1
0067e18e call 0x422e20
0067e193 lea ecx, [ebp - 0x68]
0067e196 mov esi, eax
0067e198 call 0x65add0
0067e19d mov edx, dword ptr [esi]
0067e19f lea eax, [ebp - 0x68]
0067e1a2 movaps xmm0, xmmword ptr [0xb6b960]
0067e1a9 mov ecx, esi
0067e1ab push 1
0067e1ad push 0
0067e1af push 0xff
0067e1b4 push -1
0067e1b6 push eax
0067e1b7 movups xmmword ptr [ebp - 0x68], xmm0
0067e1bb call dword ptr [edx + 0x38]
0067e1be call 0x6c3d90
0067e1c3 movd xmm0, eax
0067e1c7 cvtdq2pd xmm0, xmm0
0067e1cb shr eax, 0x1f
0067e1ce addsd xmm0, qword ptr [eax*8 + 0xb6c940]
0067e1d7 cvtpd2ps xmm0, xmm0
0067e1db mulss xmm0, dword ptr [0xb6a19c]
0067e1e3 mulss xmm0, dword ptr [0xb6a974]
0067e1eb addss xmm0, dword ptr [0xb6a7b0]
0067e1f3 movss dword ptr [esi + 0x3c4], xmm0
0067e1fb call 0x6c3d90
0067e200 xor edx, edx
0067e202 mov ecx, 0xf
0067e207 div ecx
0067e209 add edx, ecx
0067e20b mov dword ptr [esi + 0x3ac], edx
0067e211 mov dword ptr [esi + 0x3b0], edx
0067e217 movss xmm1, dword ptr [edi + 0x384]
0067e21f mulss xmm1, dword ptr [0xb6a434]
0067e227 movaps xmm0, xmm1
0067e22a mulss xmm1, dword ptr [0xbc7a2c]
0067e232 mulss xmm0, dword ptr [0xbc7a28]
0067e23a mov dword ptr [esi + 0x2b0], 0xc1900000
0067e244 movss dword ptr [esi + 0xdc], xmm1
0067e24c movss dword ptr [esi + 0xd8], xmm0
0067e254 mov eax, dword ptr [edi + 0x2a4]
0067e25a mov dword ptr [esi + 0x2a4], eax
0067e260 mov eax, dword ptr [edi + 0x2a8]
0067e266 mov dword ptr [esi + 0x2a8], eax
0067e26c push edi
0067e26d call 0x7fe630
0067e272 mov ecx, dword ptr [ebp - 0xc]
0067e275 mov dword ptr fs:[0], ecx
0067e27c pop ecx
0067e27d pop edi
0067e27e pop esi
0067e27f mov ecx, dword ptr [ebp - 0x10]
0067e282 xor ecx, ebp
0067e284 call 0x9eacd7
0067e289 mov esp, ebp
0067e28b pop ebp
0067e28c ret 
0067e28d int3 
0067e28e int3 
0067e28f int3 
