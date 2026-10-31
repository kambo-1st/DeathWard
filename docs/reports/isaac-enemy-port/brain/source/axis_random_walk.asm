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
007a55ee cmova eax, ecx
007a55f1 mov ecx, eax
007a55f3 jmp 0x7a5616
007a55f5 cmp eax, 5
007a55f8 je 0x7a5616
007a55fa lea eax, [ecx - 0x3e8]
007a5600 cmp eax, 0x3e7
007a5605 cmovbe ecx, eax
007a5608 lea eax, [ecx - 0xbb8]
007a560e cmp eax, 0x3e7
007a5613 cmovbe ecx, eax
007a5616 cmp ecx, 0x12c
007a561c jle 0x7a5645
007a561e cmp dword ptr [esp + 0x44], 0
007a5623 jg 0x7a562d
007a5625 cmp ecx, 0x3e7
007a562b jl 0x7a5645
007a562d mov eax, dword ptr [edx + 0x160]
007a5633 and eax, 0x1000800
007a5638 or eax, 0
007a563b je 0x7a5662
007a563d cmp ecx, 0x320
007a5643 jg 0x7a5662
007a5645 mov eax, dword ptr [esp + 0x1c]
007a5649 inc esi
007a564a mov edx, dword ptr [esp + 0x38]
007a564e add eax, 0x28
007a5651 mov dword ptr [esp + 0x1c], eax
007a5655 cmp esi, edx
007a5657 jge 0x7a5669
007a5659 mov ecx, dword ptr [esp + 0x2c]
007a565d jmp 0x7a5560
007a5662 lea edx, [esi - 1]
007a5665 mov dword ptr [esp + 0x38], edx
007a5669 mov edi, dword ptr [esp + 8]
007a566d mov edi, dword ptr [edi]
007a566f lea eax, [edx + edx*4]
007a5672 shl eax, 3
007a5675 movd xmm5, eax
007a5679 mov eax, dword ptr [esp + 0x10]
007a567d cvtdq2ps xmm5, xmm5
007a5680 lea ecx, [eax + 2]
007a5683 movaps xmm1, xmm5
007a5686 mulss xmm5, xmm4
007a568a mulss xmm1, xmm3
007a568e addss xmm5, dword ptr [edi + 0x298]
007a5696 addss xmm1, dword ptr [edi + 0x294]
007a569e and ecx, 0x80000003
007a56a4 jns 0x7a56ab
007a56a6 dec ecx
007a56a7 or ecx, 0xfffffffc
007a56aa inc ecx
007a56ab movss xmm2, dword ptr [esp + ecx*8 + 0x80]
007a56b4 mulss xmm2, xmm6
007a56b8 and eax, 0x80000003
007a56bd jns 0x7a56c4
007a56bf dec eax
007a56c0 or eax, 0xfffffffc
007a56c3 inc eax
007a56c4 movss xmm0, dword ptr [esp + ecx*8 + 0x7c]
007a56ca mulss xmm0, xmm6
007a56ce movss xmm3, dword ptr [esp + eax*8 + 0x7c]
007a56d4 movss xmm4, dword ptr [esp + eax*8 + 0x80]
007a56dd addss xmm0, xmm1
007a56e1 mov eax, dword ptr [0xbfd65c]
007a56e6 mulss xmm3, xmm6
007a56ea mulss xmm4, xmm6
007a56ee mov esi, dword ptr [eax + 0x18190]
007a56f4 subss xmm0, xmm6
007a56f8 addss xmm3, xmm1
007a56fc addss xmm4, xmm5
007a5700 divss xmm0, xmm6
007a5704 addss xmm0, xmm7
007a5708 cvttss2si edx, xmm0
007a570c test edx, edx
007a570e js 0x7a5752
007a5710 mov eax, dword ptr [esi + 0xc]
007a5713 cmp edx, eax
007a5715 jge 0x7a5752
007a5717 addss xmm2, xmm5
007a571b movss xmm5, dword ptr [0xb6ab20]
007a5723 subss xmm2, xmm5
007a5727 divss xmm2, xmm6
007a572b addss xmm2, xmm7
007a572f cvttss2si ecx, xmm2
007a5733 test ecx, ecx
007a5735 js 0x7a575a
007a5737 cmp ecx, dword ptr [esi + 0x10]
007a573a jge 0x7a575a
007a573c imul eax, ecx
007a573f add edx, eax
007a5741 cmp edx, 0x1bf
007a5747 ja 0x7a575a
007a5749 mov edx, dword ptr [esi + edx*4 + 0x76c]
007a5750 jmp 0x7a575c
007a5752 movss xmm5, dword ptr [0xb6ab20]
007a575a xor edx, edx
007a575c test edi, edi
007a575e je 0x7a579d
007a5760 mov eax, dword ptr [edi + 0x17c]
007a5766 cmp eax, 6
007a5769 jne 0x7a577c
007a576b lea eax, [edx - 0xbb8]
007a5771 cmp eax, 0x3e7
007a5776 ja 0x7a579d
007a5778 mov edx, eax
007a577a jmp 0x7a579d
007a577c cmp eax, 5
007a577f je 0x7a579d
007a5781 lea eax, [edx - 0x3e8]
007a5787 cmp eax, 0x3e7
007a578c cmovbe edx, eax
007a578f lea eax, [edx - 0xbb8]
007a5795 cmp eax, 0x3e7
007a579a cmovbe edx, eax
007a579d subss xmm3, xmm6
007a57a1 subss xmm4, xmm5
007a57a5 divss xmm3, xmm6
007a57a9 divss xmm4, xmm6
007a57ad addss xmm3, xmm7
007a57b1 addss xmm4, xmm7
007a57b5 cvttss2si edi, xmm3
007a57b9 cvttss2si ecx, xmm4
007a57bd test edi, edi
007a57bf js 0x7a57e7
007a57c1 mov eax, dword ptr [esi + 0xc]
007a57c4 cmp edi, eax
007a57c6 jge 0x7a57e7
007a57c8 test ecx, ecx
007a57ca js 0x7a57e7
007a57cc cmp ecx, dword ptr [esi + 0x10]
007a57cf jge 0x7a57e7
007a57d1 imul ecx, eax
007a57d4 add ecx, edi
007a57d6 cmp ecx, 0x1bf
007a57dc ja 0x7a57e7
007a57de mov ecx, dword ptr [esi + ecx*4 + 0x76c]
007a57e5 jmp 0x7a57e9
007a57e7 xor ecx, ecx
007a57e9 mov edi, dword ptr [esp + 8]
007a57ed mov eax, dword ptr [edi]
007a57ef test eax, eax
007a57f1 je 0x7a5830
007a57f3 mov eax, dword ptr [eax + 0x17c]
007a57f9 cmp eax, 6
007a57fc jne 0x7a580f
007a57fe lea eax, [ecx - 0xbb8]
007a5804 cmp eax, 0x3e7
007a5809 ja 0x7a5830
007a580b mov ecx, eax
007a580d jmp 0x7a5830
007a580f cmp eax, 5
007a5812 je 0x7a5830
007a5814 lea eax, [ecx - 0x3e8]
007a581a cmp eax, 0x3e7
007a581f cmovbe ecx, eax
007a5822 lea eax, [ecx - 0xbb8]
007a5828 cmp eax, 0x3e7
007a582d cmovbe ecx, eax
007a5830 cmp edx, 0xc8
007a5836 jl 0x7a5852
007a5838 cmp ecx, 0xc8
007a583e jl 0x7a5852
007a5840 call 0x6c3d90
007a5845 xor edx, edx
007a5847 mov ecx, 0xa
007a584c div ecx
007a584e test edx, edx
007a5850 jne 0x7a585c
007a5852 mov ecx, dword ptr [esp + 0x14]
007a5856 mov eax, dword ptr [esp + 0x38]
007a585a mov dword ptr [ecx], eax
007a585c mov esi, dword ptr [esp + 0x20]
007a5860 movss xmm2, dword ptr [esp + 0x18]
007a5866 inc dword ptr [esp + 0x10]
007a586a add esi, 8
007a586d add dword ptr [esp + 0x14], 4
007a5872 sub dword ptr [esp + 0xc], 1
007a5877 mov dword ptr [esp + 0x20], esi
007a587b jne 0x7a5472
007a5881 mov ecx, dword ptr [esp + 8]
007a5885 xor esi, esi
007a5887 push esi
007a5888 push 0xbeab70
007a588d push 0xbeab18
007a5892 push esi
007a5893 push dword ptr [ecx]
007a5895 or edi, 0xffffffff
007a5898 call 0x9ec34c
007a589d add esp, 0x14
007a58a0 mov dword ptr [esp + 0x20], eax
007a58a4 call 0x6c3d90
007a58a9 mov edx, eax
007a58ab mov eax, dword ptr [esp + 8]
007a58af and edx, 3
007a58b2 mov dword ptr [esp + 0x18], edx
007a58b6 mov eax, dword ptr [eax]
007a58b8 mov ecx, dword ptr [eax + 0x160]
007a58be and ecx, 0x1000800
007a58c4 or ecx, esi
007a58c6 je 0x7a59f5
007a58cc mov ecx, dword ptr [esp + 0x20]
007a58d0 test ecx, ecx
007a58d2 je 0x7a59f5
007a58d8 movss xmm0, dword ptr [eax + 0x294]
007a58e0 movss dword ptr [esp + 0xc], xmm0
007a58e6 movss xmm0, dword ptr [eax + 0x298]
007a58ee movss dword ptr [esp + 0x1c], xmm0
007a58f4 call 0x695680
007a58f9 movss xmm0, dword ptr [eax + 0x294]
007a5901 movss xmm1, dword ptr [eax + 0x298]
007a5909 subss xmm0, dword ptr [esp + 0xc]
007a590f subss xmm1, dword ptr [esp + 0x1c]
007a5915 mov eax, dword ptr [esp + 0x18]
007a5919 mov ecx, eax
007a591b add eax, 4
007a591e mov dword ptr [esp + 0xc], ecx
007a5922 mov dword ptr [esp + 0x2c], eax
007a5926 movss dword ptr [esp + 0x14], xmm0
007a592c movss dword ptr [esp + 0x1c], xmm1
007a5932 mov eax, ecx
007a5934 and eax, 0x80000003
007a5939 jns 0x7a5940
007a593b dec eax
007a593c or eax, 0xfffffffc
007a593f inc eax
007a5940 mov edx, eax
007a5942 mov dword ptr [esp + 0x10], eax
007a5946 lea ecx, [esp + 0x50]
007a594a call 0x659400
007a594f movss xmm3, dword ptr [esp + 0x1c]
007a5955 movss xmm2, dword ptr [esp + 0x14]
007a595b movaps xmm1, xmm3
007a595e movaps xmm0, xmm2
007a5961 mulss xmm0, dword ptr [eax]
007a5965 mulss xmm1, dword ptr [eax + 4]
007a596a addss xmm1, xmm0
007a596e xorps xmm0, xmm0
007a5971 comiss xmm1, xmm0
007a5974 ja 0x7a5986
007a5976 mov eax, dword ptr [esp + 0x10]
007a597a mov ecx, dword ptr [esp + eax*4 + 0x60]
007a597e cmp ecx, esi
007a5980 jle 0x7a5986
007a5982 mov esi, ecx
007a5984 mov edi, eax
007a5986 mov ecx, dword ptr [esp + 0xc]
007a598a inc ecx
007a598b mov dword ptr [esp + 0xc], ecx
007a598f cmp ecx, dword ptr [esp + 0x2c]
007a5993 jl 0x7a5932
007a5995 test esi, esi
007a5997 jne 0x7a5a25
007a599d andps xmm2, xmmword ptr [0xb6c980]
007a59a4 andps xmm3, xmmword ptr [0xb6c980]
007a59ab comiss xmm3, xmm2
007a59ae jbe 0x7a59ce
007a59b0 xor edx, edx
007a59b2 mov ecx, dword ptr [esp + edx*4 + 0x60]
007a59b6 mov eax, edx
007a59b8 cmp ecx, esi
007a59ba cmovle eax, edi
007a59bd cmovle ecx, esi
007a59c0 add edx, 2
007a59c3 mov edi, eax
007a59c5 mov esi, ecx
007a59c7 cmp edx, 4
007a59ca jl 0x7a59b2
007a59cc jmp 0x7a59ed
007a59ce mov edx, 1
007a59d3 mov ecx, dword ptr [esp + edx*4 + 0x60]
007a59d7 mov eax, edx
007a59d9 cmp ecx, esi
007a59db cmovle eax, edi
007a59de cmovle ecx, esi
007a59e1 add edx, 2
007a59e4 mov edi, eax
007a59e6 mov esi, ecx
007a59e8 cmp edx, 4
007a59eb jl 0x7a59d3
007a59ed test esi, esi
007a59ef jne 0x7a5a25
007a59f1 mov edx, dword ptr [esp + 0x18]
007a59f5 lea eax, [edx + 4]
007a59f8 mov dword ptr [esp + 0xc], eax
007a59fc nop dword ptr [eax]
007a5a00 mov eax, edx
007a5a02 and eax, 0x80000003
007a5a07 jns 0x7a5a0e
007a5a09 dec eax
007a5a0a or eax, 0xfffffffc
007a5a0d inc eax
007a5a0e mov ecx, dword ptr [esp + eax*4 + 0x60]
007a5a12 cmp ecx, esi
007a5a14 cmovle eax, edi
007a5a17 cmovle ecx, esi
007a5a1a inc edx
007a5a1b mov edi, eax
007a5a1d mov esi, ecx
007a5a1f cmp edx, dword ptr [esp + 0xc]
007a5a23 jl 0x7a5a00
007a5a25 cmp esi, 2
007a5a28 jge 0x7a5a55
007a5a2a call 0x6c3d90
007a5a2f xor edx, edx
007a5a31 mov ecx, 0xa
007a5a36 div ecx
007a5a38 test edx, edx
007a5a3a je 0x7a5a55
007a5a3c mov eax, dword ptr [esp + 8]
007a5a40 mov eax, dword ptr [eax]
007a5a42 mov eax, dword ptr [eax + 0x160]
007a5a48 and eax, 0x1000800
007a5a4d or eax, 0
007a5a50 jne 0x7a5a55
007a5a52 or edi, 0xffffffff
007a5a55 mov eax, dword ptr [esp + 8]
007a5a59 mov eax, dword ptr [eax + 0x14]
007a5a5c sub eax, edi
007a5a5e cdq 
007a5a5f xor eax, edx
007a5a61 sub eax, edx
007a5a63 cmp eax, 2
007a5a66 jne 0x7a5a96
007a5a68 call 0x6c3d90
007a5a6d xor edx, edx
007a5a6f mov ecx, 5
007a5a74 div ecx
007a5a76 test edx, edx
007a5a78 mov edx, dword ptr [esp + 8]
007a5a7c je 0x7a5a9a
007a5a7e mov eax, dword ptr [edx]
007a5a80 mov eax, dword ptr [eax + 0x160]
007a5a86 and eax, 0x1000800
007a5a8b or eax, 0
007a5a8e je 0x7a5df9
007a5a94 jmp 0x7a5a9a
007a5a96 mov edx, dword ptr [esp + 8]
007a5a9a test edi, edi
007a5a9c js 0x7a5b91
007a5aa2 mov ecx, dword ptr [edx]
007a5aa4 mov eax, dword ptr [ecx + 0x160]
007a5aaa and eax, 0x1000800
007a5aaf or eax, 0
007a5ab2 je 0x7a5b9a
007a5ab8 movss xmm0, dword ptr [ecx + 0x294]
007a5ac0 movss dword ptr [esp + 0xc], xmm0
007a5ac6 movss xmm0, dword ptr [ecx + 0x298]
007a5ace mov ecx, dword ptr [esp + 0x20]
007a5ad2 movss dword ptr [esp + 0x18], xmm0
007a5ad8 call 0x695680
007a5add movss xmm1, dword ptr [eax + 0x294]
007a5ae5 subss xmm1, dword ptr [esp + 0xc]
007a5aeb movss xmm2, dword ptr [eax + 0x298]
007a5af3 subss xmm2, dword ptr [esp + 0x18]
007a5af9 movaps xmm0, xmm1
007a5afc movss dword ptr [esp + 0x10], xmm1
007a5b02 mulss xmm0, xmm1
007a5b06 movaps xmm1, xmm2
007a5b09 movss dword ptr [esp + 0x14], xmm2
007a5b0f mulss xmm1, xmm2
007a5b13 addss xmm0, xmm1
007a5b17 call 0x4228c0
007a5b1c xorps xmm1, xmm1
007a5b1f comiss xmm0, xmm1
007a5b22 jbe 0x7a5b50
007a5b24 movss xmm1, dword ptr [0xb6a614]
007a5b2c divss xmm1, xmm0
007a5b30 movss xmm0, dword ptr [esp + 0x10]
007a5b36 mulss xmm0, xmm1
007a5b3a movss dword ptr [esp + 0x10], xmm0
007a5b40 movss xmm0, dword ptr [esp + 0x14]
007a5b46 mulss xmm0, xmm1
007a5b4a movss dword ptr [esp + 0x14], xmm0
007a5b50 mov edx, edi
007a5b52 lea ecx, [esp + 0x58]
007a5b56 call 0x659400
007a5b5b movss xmm0, dword ptr [esp + 0x14]
007a5b61 movss xmm1, dword ptr [esp + 0x10]
007a5b67 mulss xmm0, dword ptr [eax + 4]
007a5b6c mulss xmm1, dword ptr [eax]
007a5b70 addss xmm0, xmm1
007a5b74 comiss xmm0, dword ptr [0xb6a5d8]
007a5b7b jbe 0x7a5b9a
007a5b7d mov edi, dword ptr [esp + 8]
007a5b81 mov ecx, dword ptr [esp + 0x44]
007a5b85 mov dword ptr [edi + 0x18], 0
007a5b8c jmp 0x7a53f3
007a5b91 cmp edi, -1
007a5b94 jle 0x7a5df9
007a5b9a movss xmm2, dword ptr [0xb6aa3c]
007a5ba2 lea eax, [esi + esi*4]
007a5ba5 shl eax, 3
007a5ba8 movss xmm4, dword ptr [0xb6a480]
007a5bb0 mov esi, dword ptr [0xbfd65c]
007a5bb6 movss xmm5, dword ptr [0xb6ab20]
007a5bbe movd xmm0, eax
007a5bc2 mov eax, dword ptr [esp + 8]
007a5bc6 cvtdq2ps xmm0, xmm0
007a5bc9 mov esi, dword ptr [esi + 0x18190]
007a5bcf mov eax, dword ptr [eax]
007a5bd1 movaps xmm3, xmm0
007a5bd4 mulss xmm0, dword ptr [esp + edi*8 + 0x7c]
007a5bda movss xmm1, dword ptr [eax + 0x298]
007a5be2 mulss xmm3, dword ptr [esp + edi*8 + 0x80]
007a5beb addss xmm0, dword ptr [eax + 0x294]
007a5bf3 subss xmm0, xmm2
007a5bf7 divss xmm0, xmm2
007a5bfb addss xmm0, xmm4
007a5bff cvttss2si eax, xmm0
007a5c03 test eax, eax
007a5c05 js 0x7a5c38
007a5c07 mov ecx, dword ptr [esi + 0xc]
007a5c0a cmp eax, ecx
007a5c0c jge 0x7a5c38
007a5c0e addss xmm1, xmm3
007a5c12 subss xmm1, xmm5
007a5c16 divss xmm1, xmm2
007a5c1a addss xmm1, xmm4
007a5c1e cvttss2si edx, xmm1
007a5c22 test edx, edx
007a5c24 js 0x7a5c38
007a5c26 cmp edx, dword ptr [esi + 0x10]
007a5c29 jge 0x7a5c38
007a5c2b mov eax, ecx
007a5c2d imul eax, edx
007a5c30 cvttss2si edx, xmm0
007a5c34 add eax, edx
007a5c36 jmp 0x7a5c3e
007a5c38 mov ecx, dword ptr [esi + 0xc]
007a5c3b or eax, 0xffffffff
007a5c3e cdq 
007a5c3f xorps xmm0, xmm0
007a5c42 idiv ecx
007a5c44 xorps xmm3, xmm3
007a5c47 cvtsi2ss xmm0, edx
007a5c4b cvtsi2ss xmm3, eax
007a5c4f mulss xmm0, xmm2
007a5c53 mulss xmm3, xmm2
007a5c57 addss xmm0, xmm2
007a5c5b addss xmm3, xmm5
007a5c5f movss dword ptr [esp + 0x1c], xmm0
007a5c65 subss xmm0, xmm2
007a5c69 movss dword ptr [esp + 0x18], xmm3
007a5c6f divss xmm0, xmm2
007a5c73 addss xmm0, xmm4
007a5c77 cvttss2si eax, xmm0
007a5c7b mov dword ptr [esp + 0xc], eax
007a5c7f test eax, eax
007a5c81 js 0x7a5cc0
007a5c83 cmp eax, ecx
007a5c85 jge 0x7a5cc0
007a5c87 movaps xmm1, xmm3
007a5c8a subss xmm1, xmm5
007a5c8e movaps xmm0, xmm1
007a5c91 divss xmm0, xmm2
007a5c95 addss xmm0, xmm4
007a5c99 cvttss2si edx, xmm0
007a5c9d test edx, edx
007a5c9f js 0x7a5cc0
007a5ca1 cmp edx, dword ptr [esi + 0x10]
007a5ca4 jge 0x7a5cc0
007a5ca6 imul ecx, edx
007a5ca9 add ecx, eax
007a5cab js 0x7a5cc7
007a5cad cmp dword ptr [esi + ecx*4 + 0x76c], 0x3e7
007a5cb8 je 0x7a5df9
007a5cbe jmp 0x7a5cc7
007a5cc0 movaps xmm1, xmm3
007a5cc3 subss xmm1, xmm5
007a5cc7 mov ecx, dword ptr [esp + 8]
007a5ccb divss xmm1, xmm2
007a5ccf mov dword ptr [ecx + 0x14], edi
007a5cd2 mov ecx, dword ptr [0xbfd65c]
007a5cd8 mov esi, dword ptr [ecx + 0x18190]
007a5cde addss xmm1, xmm4
007a5ce2 cvttss2si ecx, xmm1
007a5ce6 test eax, eax
007a5ce8 js 0x7a5d02
007a5cea cmp eax, dword ptr [esi + 0xc]
007a5ced jge 0x7a5d02
007a5cef test ecx, ecx
007a5cf1 js 0x7a5d02
007a5cf3 cmp ecx, dword ptr [esi + 0x10]
007a5cf6 jge 0x7a5d02
007a5cf8 mov edx, ecx
007a5cfa imul edx, dword ptr [esi + 0xc]
007a5cfe add edx, eax
007a5d00 jmp 0x7a5d05
007a5d02 or edx, 0xffffffff
007a5d05 mov eax, dword ptr [esi + 4]
007a5d08 mov eax, dword ptr [eax + 0x10]
007a5d0b test eax, eax
007a5d0d je 0x7a5d1a
007a5d0f cmp dword ptr [eax + 8], 0x10
007a5d13 jne 0x7a5d1a
007a5d15 cmp dword ptr [eax], 0x23
007a5d18 je 0x7a5d89
007a5d1a test edx, edx
007a5d1c js 0x7a5d43
007a5d1e mov eax, dword ptr [esi + edx*4 + 0x24]
007a5d22 test eax, eax
007a5d24 jne 0x7a5d3d
007a5d26 mov eax, dword ptr [esi + edx*4 + 0x76c]
007a5d2d cmp eax, 0xbb8
007a5d32 jge 0x7a5d43
007a5d34 cmp eax, 0x3e8
007a5d39 jl 0x7a5d89
007a5d3b jmp 0x7a5d43
007a5d3d cmp dword ptr [eax + 0x3c], 0
007a5d41 je 0x7a5d89
007a5d43 mov eax, dword ptr [esp + 0x20]
007a5d47 cmp dword ptr [eax + 0x17c], 3
007a5d4e jne 0x7a5df9
007a5d54 mov eax, dword ptr [esp + 0xc]
007a5d58 test eax, eax
007a5d5a js 0x7a5d73
007a5d5c mov edx, dword ptr [esi + 0xc]
007a5d5f cmp eax, edx
007a5d61 jge 0x7a5d73
007a5d63 test ecx, ecx
007a5d65 js 0x7a5d73
007a5d67 cmp ecx, dword ptr [esi + 0x10]
007a5d6a jge 0x7a5d73
007a5d6c imul ecx, edx
007a5d6f add ecx, eax
007a5d71 jmp 0x7a5d76
007a5d73 or ecx, 0xffffffff
007a5d76 push ecx
007a5d77 mov ecx, esi
007a5d79 call 0x7aeec0
007a5d7e cmp eax, 4
007a5d81 je 0x7a5df9
007a5d83 movss xmm3, dword ptr [esp + 0x18]
007a5d89 mov eax, dword ptr [esp + 8]
007a5d8d movss xmm0, dword ptr [esp + 0x1c]
007a5d93 movss xmm1, dword ptr [esp + edi*8 + 0x7c]
007a5d99 andps xmm1, xmmword ptr [0xb6c980]
007a5da0 movss dword ptr [eax + 4], xmm0
007a5da5 movss xmm0, dword ptr [esp + edi*8 + 0x80]
007a5dae andps xmm0, xmmword ptr [0xb6c980]
007a5db5 movss dword ptr [eax + 8], xmm3
007a5dba mov eax, dword ptr [eax]
007a5dbc add eax, 0x2b8
007a5dc1 comiss xmm1, xmm0
007a5dc4 jbe 0x7a5de9
007a5dc6 movss xmm0, dword ptr [eax]
007a5dca mov edi, dword ptr [esp + 8]
007a5dce mov ecx, dword ptr [esp + 0x44]
007a5dd2 movss dword ptr [eax], xmm0
007a5dd6 mov dword ptr [eax + 4], 0
007a5ddd mov dword ptr [edi + 0x18], 0
007a5de4 jmp 0x7a53f3
007a5de9 movss xmm0, dword ptr [eax + 4]
007a5dee mov dword ptr [eax], 0
007a5df4 movss dword ptr [eax + 4], xmm0
007a5df9 mov edi, dword ptr [esp + 8]
007a5dfd mov ecx, dword ptr [esp + 0x44]
007a5e01 mov dword ptr [edi + 0x18], 0
007a5e08 jmp 0x7a53f3
007a5e0d ucomiss xmm1, xmm2
007a5e10 lahf 
007a5e11 test ah, 0x44
007a5e14 jp 0x7a5e28
007a5e16 movss xmm0, dword ptr [edi + 8]
007a5e1b ucomiss xmm0, xmm3
007a5e1e lahf 
007a5e1f test ah, 0x44
007a5e22 jnp 0x7a6167
007a5e28 cmp dword ptr [esp + 0x3c], 1
007a5e2d lea ecx, [edi + 4]
007a5e30 jle 0x7a5e59
007a5e32 movss dword ptr [ecx], xmm2
007a5e36 movss xmm0, dword ptr [0xc02ff0]
007a5e3e movss dword ptr [ecx + 4], xmm0
007a5e43 pop edi
007a5e44 pop esi
007a5e45 mov ecx, dword ptr [esp + 0x94]
007a5e4c xor ecx, esp
007a5e4e call 0x9eacd7
007a5e53 mov esp, ebp
007a5e55 pop ebp
007a5e56 ret 8
007a5e59 comiss xmm1, dword ptr [esp + 0x48]
007a5e5e lea eax, [esp + 0x30]
007a5e62 movss xmm4, dword ptr [esp + 0x4c]
007a5e68 cmova eax, ecx
007a5e6b movss xmm0, dword ptr [eax]
007a5e6f comiss xmm4, xmm0
007a5e72 ja 0x7a5e7a
007a5e74 movss xmm1, xmm4
007a5e78 jmp 0x7a5e7e
007a5e7a movss xmm1, xmm0
007a5e7e lea ecx, [edi + 8]
007a5e81 lea eax, [esp + 0x34]
007a5e85 movss xmm4, dword ptr [esp + 0x28]
007a5e8b movss dword ptr [edi + 4], xmm1
007a5e90 movss xmm0, dword ptr [ecx]
007a5e94 comiss xmm0, dword ptr [esp + 0x24]
007a5e99 cmova eax, ecx
007a5e9c movss xmm0, dword ptr [eax]
007a5ea0 comiss xmm4, xmm0
007a5ea3 ja 0x7a5eab
007a5ea5 movss xmm0, xmm4
007a5ea9 jmp 0x7a5eaf
007a5eab movss xmm0, xmm0
007a5eaf mov esi, dword ptr [edi]
007a5eb1 movss dword ptr [ecx], xmm0
007a5eb5 movss xmm2, dword ptr [esi + 0x2b8]
007a5ebd addss xmm2, dword ptr [esi + 0x294]
007a5ec5 subss xmm2, xmm1
007a5ec9 movss xmm1, dword ptr [esi + 0x2bc]
007a5ed1 addss xmm1, dword ptr [esi + 0x298]
007a5ed9 movaps xmm3, xmm2
007a5edc movss dword ptr [esp + 0x28], xmm2
007a5ee2 subss xmm1, xmm0
007a5ee6 mulss xmm3, xmm2
007a5eea movaps xmm0, xmm1
007a5eed movss dword ptr [esp + 0x24], xmm1
007a5ef3 mulss xmm0, xmm1
007a5ef7 addss xmm3, xmm0
007a5efb movaps xmm0, xmm3
007a5efe movss dword ptr [esp + 0x3c], xmm3
007a5f04 call 0x4228c0
007a5f09 movss xmm1, dword ptr [0xb6a8f4]
007a5f11 comiss xmm1, xmm0
007a5f14 jbe 0x7a5f32
007a5f16 movss xmm0, dword ptr [0xc02fec]
007a5f1e movss dword ptr [edi + 4], xmm0
007a5f23 movss xmm0, dword ptr [0xc02ff0]
007a5f2b movss dword ptr [edi + 8], xmm0
007a5f30 jmp 0x7a5f86
007a5f32 movss xmm1, dword ptr [esi + 0x2b8]
007a5f3a movss xmm0, dword ptr [esi + 0x2bc]
007a5f42 mulss xmm0, xmm0
007a5f46 mulss xmm1, xmm1
007a5f4a addss xmm0, xmm1
007a5f4e call 0x4228c0
007a5f53 movss xmm1, dword ptr [0xb6a4c4]
007a5f5b comiss xmm1, xmm0
007a5f5e jbe 0x7a5f86
007a5f60 mov eax, dword ptr [edi + 0x18]
007a5f63 inc eax
007a5f64 mov dword ptr [edi + 0x18], eax
007a5f67 cmp eax, 0xa
007a5f6a jle 0x7a5f86
007a5f6c movss xmm1, dword ptr [0xc02fec]
007a5f74 movss dword ptr [edi + 4], xmm1
007a5f79 movss xmm1, dword ptr [0xc02ff0]
007a5f81 movss dword ptr [edi + 8], xmm1
007a5f86 movss xmm0, dword ptr [esp + 0x3c]
007a5f8c call 0x4228c0
007a5f91 movss xmm2, dword ptr [esp + 0x28]
007a5f97 xorps xmm5, xmm5
007a5f9a comiss xmm0, xmm5
007a5f9d movss xmm3, dword ptr [esp + 0x24]
007a5fa3 jbe 0x7a5fb9
007a5fa5 movss xmm1, dword ptr [0xb6a614]
007a5fad divss xmm1, xmm0
007a5fb1 mulss xmm2, xmm1
007a5fb5 mulss xmm3, xmm1
007a5fb9 movss xmm4, dword ptr [esi + 0x2c4]
007a5fc1 xorps xmm2, xmmword ptr [0xb6c9b0]
007a5fc8 xorps xmm3, xmmword ptr [0xb6c9b0]
007a5fcf mulss xmm2, dword ptr [ebp + 8]
007a5fd4 mulss xmm3, dword ptr [ebp + 8]
007a5fd9 ucomiss xmm4, xmm5
007a5fdc lahf 
007a5fdd test ah, 0x44
007a5fe0 jnp 0x7a601f
007a5fe2 movss xmm1, dword ptr [esi + 0x2f4]
007a5fea movaps xmm0, xmm1
007a5fed mulss xmm1, xmm3
007a5ff1 mulss xmm0, xmm2
007a5ff5 divss xmm1, xmm4
007a5ff9 divss xmm0, xmm4
007a5ffd addss xmm1, dword ptr [esi + 0x2bc]
007a6005 addss xmm0, dword ptr [esi + 0x2b8]
007a600d movss dword ptr [esi + 0x2bc], xmm1
007a6015 movss dword ptr [esi + 0x2b8], xmm0
007a601d mov esi, dword ptr [edi]
007a601f movss xmm0, dword ptr [esi + 0x2b8]
007a6027 movss xmm1, dword ptr [esi + 0x2bc]
007a602f movaps xmm2, xmm0
007a6032 mulss xmm2, xmm0
007a6036 movss dword ptr [esp + 0x28], xmm0
007a603c movaps xmm0, xmm1
007a603f mulss xmm0, xmm1
007a6043 movss dword ptr [esp + 0x3c], xmm1
007a6049 addss xmm2, xmm0
007a604d movaps xmm0, xmm2
007a6050 movss dword ptr [esp + 0x24], xmm2
007a6056 call 0x4228c0
007a605b xorps xmm1, xmm1
007a605e comiss xmm0, xmm1
007a6061 jbe 0x7a608c
007a6063 movss xmm2, dword ptr [0xb6a614]
007a606b divss xmm2, xmm0
007a606f movss xmm1, dword ptr [esi + 0x2b8]
007a6077 movaps xmm0, xmm2
007a607a mulss xmm1, xmm0
007a607e movss xmm0, dword ptr [esi + 0x2bc]
007a6086 mulss xmm0, xmm2
007a608a jmp 0x7a6098
007a608c movss xmm0, dword ptr [esp + 0x3c]
007a6092 movss xmm1, dword ptr [esp + 0x28]
007a6098 movss xmm2, dword ptr [0xb6aa3c]
007a60a0 mulss xmm1, xmm2
007a60a4 mov eax, dword ptr [0xbfd65c]
007a60a9 movss xmm4, dword ptr [0xb6a480]
007a60b1 movss xmm3, dword ptr [esi + 0x298]
007a60b9 addss xmm1, dword ptr [esi + 0x294]
007a60c1 mov edx, dword ptr [eax + 0x18190]
007a60c7 mulss xmm0, xmm2
007a60cb subss xmm1, xmm2
007a60cf divss xmm1, xmm2
007a60d3 addss xmm1, xmm4
007a60d7 cvttss2si esi, xmm1
007a60db test esi, esi
007a60dd js 0x7a611c
007a60df mov eax, dword ptr [edx + 0xc]
007a60e2 cmp esi, eax
007a60e4 jge 0x7a611c
007a60e6 addss xmm0, xmm3
007a60ea subss xmm0, dword ptr [0xb6ab20]
007a60f2 divss xmm0, xmm2
007a60f6 addss xmm0, xmm4
007a60fa cvttss2si ecx, xmm0
007a60fe test ecx, ecx
007a6100 js 0x7a611c
007a6102 cmp ecx, dword ptr [edx + 0x10]
007a6105 jge 0x7a611c
007a6107 imul eax, ecx
007a610a add eax, esi
007a610c cmp eax, 0x1bf
007a6111 ja 0x7a611c
007a6113 mov eax, dword ptr [edx + eax*4 + 0x76c]
007a611a jmp 0x7a611e
007a611c xor eax, eax
007a611e push eax
007a611f mov ecx, edi
007a6121 call 0x7a75b0
007a6126 cmp eax, 0x2bc
007a612b jle 0x7a6167
007a612d movss xmm0, dword ptr [esp + 0x24]
007a6133 call 0x4228c0
007a6138 comiss xmm0, dword ptr [0xb6a864]
007a613f jbe 0x7a6167
007a6141 mov eax, dword ptr [edi + 0x18]
007a6144 inc eax
007a6145 mov dword ptr [edi + 0x18], eax
007a6148 cmp eax, 2
007a614b jle 0x7a6167
007a614d movss xmm0, dword ptr [0xc02fec]
007a6155 movss dword ptr [edi + 4], xmm0
007a615a movss xmm0, dword ptr [0xc02ff0]
007a6162 movss dword ptr [edi + 8], xmm0
007a6167 mov ecx, dword ptr [esp + 0x9c]
007a616e pop edi
007a616f pop esi
007a6170 xor ecx, esp
007a6172 call 0x9eacd7
007a6177 mov esp, ebp
007a6179 pop ebp
007a617a ret 8
