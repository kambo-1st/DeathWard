007a51e0 push ebp
007a51e1 mov ebp, esp
007a51e3 and esp, 0xfffffff0
007a51e6 sub esp, 0x98
007a51ec mov eax, dword ptr [0xbaa3b4]
007a51f1 xor eax, esp
007a51f3 mov dword ptr [esp + 0x94], eax
007a51fa push esi
007a51fb push edi
007a51fc mov edi, ecx
007a51fe mov dword ptr [esp + 8], edi
007a5202 mov esi, dword ptr [edi]
007a5204 cmp dword ptr [esi + 0x32c], 0
007a520b jne 0x7a6167
007a5211 cmp byte ptr [ebp + 0xc], 0
007a5215 jne 0x7a537d
007a521b call 0x7a35d0
007a5220 test al, al
007a5222 je 0x7a537d
007a5228 push 0
007a522a push 0xbeab70
007a522f push 0xbeab18
007a5234 push 0
007a5236 push esi
007a5237 call 0x9ec34c
007a523c add esp, 0x10
007a523f mov esi, eax
007a5241 lea eax, [esp + 0x34]
007a5245 mov ecx, esi
007a5247 mov dword ptr [esp], 0
007a524e push eax
007a524f call 0x695a30
007a5254 mov ecx, dword ptr [edi]
007a5256 mov ecx, dword ptr [ecx + 0x160]
007a525c and ecx, 0x20000000
007a5262 or ecx, 0
007a5265 je 0x7a52d9
007a5267 mov ecx, esi
007a5269 call 0x695680
007a526e cmp dword ptr [eax + 0x28], 1
007a5272 jne 0x7a52d9
007a5274 movss xmm0, dword ptr [esp + 0x30]
007a527a movss xmm1, dword ptr [esp + 0x34]
007a5280 subss xmm0, dword ptr [esi + 0x294]
007a5288 subss xmm1, dword ptr [esi + 0x298]
007a5290 mulss xmm0, xmm0
007a5294 mulss xmm1, xmm1
007a5298 addss xmm1, xmm0
007a529c movss xmm0, dword ptr [0xb6ace4]
007a52a4 comiss xmm0, xmm1
007a52a7 jbe 0x7a52d9
007a52a9 mov eax, dword ptr [edi]
007a52ab movss xmm0, dword ptr [eax + 0x2c4]
007a52b3 mulss xmm0, dword ptr [0xb6a560]
007a52bb movss dword ptr [eax + 0x2c4], xmm0
007a52c3 pop edi
007a52c4 pop esi
007a52c5 mov ecx, dword ptr [esp + 0x94]
007a52cc xor ecx, esp
007a52ce call 0x9eacd7
007a52d3 mov esp, ebp
007a52d5 pop ebp
007a52d6 ret 8
007a52d9 movss xmm0, dword ptr [ebp + 8]
007a52de lea eax, [esp + 0x30]
007a52e2 push 1
007a52e4 push 0
007a52e6 sub esp, 8
007a52e9 mov ecx, esi
007a52eb movss dword ptr [esp + 4], xmm0
007a52f1 mov dword ptr [esp], 0
007a52f8 push eax
007a52f9 call 0x695a30
007a52fe push eax
007a52ff mov ecx, edi
007a5301 call 0x7a3650
007a5306 movss xmm1, dword ptr [esi + 0x2bc]
007a530e movss xmm0, dword ptr [esi + 0x2b8]
007a5316 mulss xmm0, xmm0
007a531a mulss xmm1, xmm1
007a531e addss xmm0, xmm1
007a5322 call 0x4228c0
007a5327 mov ecx, dword ptr [esi + 0x2bc]
007a532d lea edx, [esp + 0x30]
007a5331 mov eax, dword ptr [esi + 0x2b8]
007a5337 movaps xmm1, xmm0
007a533a mov dword ptr [esp + 0x34], ecx
007a533e lea ecx, [esp + 0x3c]
007a5342 mov dword ptr [esp + 0x30], eax
007a5346 call 0x6593a0
007a534b movaps xmm0, xmm1
007a534e mulss xmm0, dword ptr [eax]
007a5352 mulss xmm1, dword ptr [eax + 4]
007a5357 movss dword ptr [esi + 0x2b8], xmm0
007a535f movss dword ptr [esi + 0x2bc], xmm1
007a5367 pop edi
007a5368 pop esi
007a5369 mov ecx, dword ptr [esp + 0x94]
007a5370 xor ecx, esp
007a5372 call 0x9eacd7
007a5377 mov esp, ebp
007a5379 pop ebp
007a537a ret 8
007a537d mov ecx, dword ptr [0xbfd65c]
007a5383 movaps xmm0, xmmword ptr [0xb6c9d0]
007a538a movups xmmword ptr [esp + 0x7c], xmm0
007a538f mov eax, dword ptr [ecx + 0x1a30dc]
007a5395 mov edx, eax
007a5397 sub edx, dword ptr [edi + 0x1c]
007a539a movaps xmm0, xmmword ptr [0xb6bdc0]
007a53a1 mov dword ptr [edi + 0x1c], eax
007a53a4 mov eax, dword ptr [ecx + 0x18190]
007a53aa mov ecx, 0xa
007a53af movups xmmword ptr [esp + 0x8c], xmm0
007a53b7 mov dword ptr [esp + 0x3c], edx
007a53bb movss xmm4, dword ptr [eax + 0x14]
007a53c0 movss xmm0, dword ptr [eax + 0x1c]
007a53c5 movss dword ptr [esp + 0x48], xmm4
007a53cb movss dword ptr [esp + 0x30], xmm4
007a53d1 movss xmm4, dword ptr [eax + 0x18]
007a53d6 movss dword ptr [esp + 0x4c], xmm0
007a53dc movss xmm0, dword ptr [eax + 0x20]
007a53e1 movss dword ptr [esp + 0x24], xmm4
007a53e7 movss dword ptr [esp + 0x34], xmm4
007a53ed movss dword ptr [esp + 0x28], xmm0
007a53f3 movss xmm2, dword ptr [0xc02fec]
007a53fb movss xmm1, dword ptr [edi + 4]
007a5400 movss xmm7, dword ptr [0xb6a480]
007a5408 movss xmm6, dword ptr [0xb6aa3c]
007a5410 movss xmm3, dword ptr [0xc02ff0]
007a5418 ucomiss xmm1, xmm2
007a541b movss dword ptr [esp + 0x18], xmm2
007a5421 lahf 
007a5422 test ah, 0x44
007a5425 jp 0x7a5e0d
007a542b movss xmm0, dword ptr [edi + 8]
007a5430 ucomiss xmm0, xmm3
007a5433 lahf 
007a5434 test ah, 0x44
007a5437 jp 0x7a5e0d
007a543d test ecx, ecx
007a543f jle 0x7a5e0d
007a5445 dec ecx
007a5446 mov dword ptr [esp + 0x10], 1
007a544e xorps xmm0, xmm0
007a5451 mov dword ptr [esp + 0x44], ecx
007a5455 lea eax, [esp + 0x60]
007a5459 movaps xmmword ptr [esp + 0x60], xmm0
007a545e lea esi, [esp + 0x7c]
007a5462 mov dword ptr [esp + 0x14], eax
007a5466 mov dword ptr [esp + 0x20], esi
007a546a mov dword ptr [esp + 0xc], 4
007a5472 call 0x6c3d90
007a5477 xor edx, edx
007a5479 mov ecx, 0xc
007a547e div ecx
007a5480 mov ecx, dword ptr [edi]
007a5482 mov dword ptr [esp + 0x38], edx
007a5486 mov dword ptr [esp + 0x2c], ecx
007a548a mov eax, dword ptr [ecx + 0x160]
007a5490 and eax, 0x1000800
007a5495 or eax, 0
007a5498 je 0x7a54af
007a549a call 0x6c3d90
007a549f mov ecx, dword ptr [edi]
007a54a1 mov edx, eax
007a54a3 and edx, 3
007a54a6 mov dword ptr [esp + 0x2c], ecx
007a54aa inc edx
007a54ab mov dword ptr [esp + 0x38], edx
007a54af movss xmm3, dword ptr [esi]
007a54b3 lea eax, [edx + edx*4]
007a54b6 movss xmm4, dword ptr [esi + 4]
007a54bb movss xmm5, dword ptr [ecx + 0x298]
007a54c3 shl eax, 3
007a54c6 movd xmm0, eax
007a54ca cvtdq2ps xmm0, xmm0
007a54cd movaps xmm1, xmm0
007a54d0 mulss xmm0, xmm4
007a54d4 mulss xmm1, xmm3
007a54d8 addss xmm0, xmm5
007a54dc addss xmm1, dword ptr [ecx + 0x294]
007a54e4 comiss xmm1, dword ptr [esp + 0x4c]
007a54e9 ja 0x7a5518
007a54eb movss xmm7, dword ptr [esp + 0x48]
007a54f1 comiss xmm7, xmm1
007a54f4 movss xmm7, dword ptr [0xb6a480]
007a54fc ja 0x7a5518
007a54fe comiss xmm0, dword ptr [esp + 0x28]
007a5503 ja 0x7a5518
007a5505 movss xmm6, dword ptr [esp + 0x24]
007a550b comiss xmm6, xmm0
007a550e movss xmm6, dword ptr [0xb6aa3c]
007a5516 jbe 0x7a5523
007a5518 movss xmm0, dword ptr [0xc02ff0]
007a5520 movaps xmm1, xmm2
007a5523 ucomiss xmm1, xmm2
007a5526 lahf 
007a5527 test ah, 0x44
007a552a jp 0x7a553d
007a552c ucomiss xmm0, dword ptr [0xc02ff0]
007a5533 lahf 
007a5534 test ah, 0x44
007a5537 jnp 0x7a5866
007a553d mov esi, 1
007a5542 cmp edx, esi
007a5544 jle 0x7a566d
007a554a mov eax, dword ptr [0xbfd65c]
007a554f mov edi, dword ptr [eax + 0x18190]
007a5555 mov eax, 0x28
007a555a mov dword ptr [esp + 0x1c], eax
007a555e nop 
007a5560 movd xmm0, eax
007a5564 movaps xmm1, xmm3
007a5567 cvtdq2ps xmm0, xmm0
007a556a movaps xmm2, xmm4
007a556d mulss xmm1, xmm0
007a5571 mulss xmm2, xmm0
007a5575 addss xmm1, dword ptr [ecx + 0x294]
007a557d subss xmm1, xmm6
007a5581 divss xmm1, xmm6
007a5585 addss xmm1, xmm7
007a5589 cvttss2si ecx, xmm1
007a558d test ecx, ecx
007a558f js 0x7a55d2
007a5591 mov edx, dword ptr [edi + 0xc]
007a5594 cmp ecx, edx
007a5596 jge 0x7a55d2
007a5598 movaps xmm0, xmm5
007a559b addss xmm0, xmm2
007a559f subss xmm0, dword ptr [0xb6ab20]
007a55a7 divss xmm0, xmm6
007a55ab addss xmm0, xmm7
007a55af cvttss2si eax, xmm0
007a55b3 test eax, eax
007a55b5 js 0x7a55d2
007a55b7 cmp eax, dword ptr [edi + 0x10]
007a55ba jge 0x7a55d2
007a55bc imul eax, edx
007a55bf add ecx, eax
007a55c1 cmp ecx, 0x1bf
007a55c7 ja 0x7a55d2
007a55c9 mov ecx, dword ptr [edi + ecx*4 + 0x76c]
007a55d0 jmp 0x7a55d4
007a55d2 xor ecx, ecx
007a55d4 mov edx, dword ptr [esp + 0x2c]
007a55d8 mov eax, dword ptr [edx + 0x17c]
007a55de cmp eax, 6
007a55e1 jne 0x7a55f5
007a55e3 lea eax, [ecx - 0xbb8]
007a55e9 cmp eax, 0x3e7
