0054a0c0 push ebx
0054a0c1 mov ebx, esp
0054a0c3 sub esp, 8
0054a0c6 and esp, 0xfffffff8
0054a0c9 add esp, 4
0054a0cc push ebp
0054a0cd mov ebp, dword ptr [ebx + 4]
0054a0d0 mov dword ptr [esp + 4], ebp
0054a0d4 mov ebp, esp
0054a0d6 sub esp, 0x38
0054a0d9 mov eax, dword ptr [0xbaa3b4]
0054a0de xor eax, ebp
0054a0e0 mov dword ptr [ebp - 4], eax
0054a0e3 push esi
0054a0e4 mov esi, ecx
0054a0e6 mov dword ptr [ebp - 0x30], 0
0054a0ed push edi
0054a0ee mov eax, dword ptr [esi + 0xab4]
0054a0f4 cmp eax, 6
0054a0f7 ja 0x54a74f
0054a0fd jmp dword ptr [eax*4 + 0x54a77c]
0054a104 mov dword ptr [esi + 0x17c], 6
0054a10e mov dword ptr [esi + 0x2a8], 0xc1000000
0054a118 mov dword ptr [esi + 0xb00], 0x42b40000
0054a122 jmp 0x54a745
0054a127 mov dword ptr [esi + 0x17c], 3
0054a131 mov dword ptr [esi + 0x180], 0
0054a13b mov eax, dword ptr [esi + 0xb08]
0054a141 mov dword ptr [esi + 0x2b8], eax
0054a147 mov eax, dword ptr [esi + 0xb0c]
0054a14d mov dword ptr [esi + 0x2bc], eax
0054a153 movss xmm1, dword ptr [esi + 0x2f4]
0054a15b movaps xmm0, xmm1
0054a15e mulss xmm0, dword ptr [0xb6a50c]
0054a166 addss xmm0, dword ptr [esi + 0xb00]
0054a16e mulss xmm1, xmm0
0054a172 movss dword ptr [esi + 0xb00], xmm0
0054a17a movaps xmm0, xmm1
0054a17d addss xmm0, dword ptr [esi + 0x2a8]
0054a185 movss dword ptr [esi + 0x2a8], xmm0
0054a18d addss xmm0, xmm1
0054a191 comiss xmm0, dword ptr [0xb6aeac]
0054a198 jbe 0x54a1e7
0054a19a mov dword ptr [esi + 0xb00], 0x42b40000
0054a1a4 mov dword ptr [esi + 0x2a8], 0xc1000000
0054a1ae movss xmm0, dword ptr [0xc02fec]
0054a1b6 movss dword ptr [esi + 0x28c], xmm0
0054a1be movss xmm0, dword ptr [0xc02ff0]
0054a1c6 movss dword ptr [esi + 0x290], xmm0
0054a1ce mov dword ptr [esi + 0x17c], 6
0054a1d8 mov dword ptr [esi + 0x180], 4
0054a1e2 jmp 0x54a745
0054a1e7 push 0
0054a1e9 push 0xb41c8c
0054a1ee lea ecx, [esi + 0x3c]
0054a1f1 call 0x4054f0
0054a1f6 jmp 0x54a74f
0054a1fb lea eax, [ebp - 0x30]
0054a1fe push eax
0054a1ff call 0x549f50
0054a204 push 0
0054a206 lea ecx, [esi + 0x3c]
0054a209 push dword ptr [eax*4 + 0xb42de8]
0054a210 call 0x4054f0
0054a215 cmp dword ptr [esi + 0xe6c], -1
0054a21c movss xmm0, dword ptr [ebp - 0x30]
0054a221 movss dword ptr [esi + 0xe0], xmm0
0054a229 je 0x54a27f
0054a22b movss xmm2, dword ptr [0xb6a2cc]
0054a233 lea eax, [ebp - 0x2c]
0054a236 push eax
0054a237 mov ecx, esi
0054a239 call 0x6af0c0
0054a23e mov ecx, eax
0054a240 movss xmm0, dword ptr [ecx]
0054a244 ucomiss xmm0, dword ptr [0xc02fec]
0054a24b lahf 
0054a24c test ah, 0x44
0054a24f jp 0x54a267
0054a251 movss xmm0, dword ptr [ecx + 4]
0054a256 ucomiss xmm0, dword ptr [0xc02ff0]
0054a25d lahf 
0054a25e test ah, 0x44
0054a261 jnp 0x54a74f
0054a267 movss xmm2, dword ptr [0xb6a2cc]
0054a26f lea eax, [ebp - 0x2c]
0054a272 push eax
0054a273 mov ecx, esi
0054a275 call 0x6af0c0
0054a27a jmp 0x54a341
0054a27f call 0x6c3d90
0054a284 test al, 3
0054a286 jne 0x54a74f
0054a28c mov ecx, esi
0054a28e call 0x695680
0054a293 push 0
0054a295 push 0x200
0054a29a mov ecx, esi
0054a29c mov edi, eax
0054a29e call 0x4122f0
0054a2a3 test al, al
0054a2a5 jne 0x54a335
0054a2ab call 0x6c3d90
0054a2b0 test al, 1
0054a2b2 jne 0x54a31f
0054a2b4 mov eax, dword ptr [edi + 0x294]
0054a2ba mov ecx, dword ptr [edi + 0x298]
0054a2c0 push 0
0054a2c2 push 0
0054a2c4 push 0
0054a2c6 push 0
0054a2c8 mov dword ptr [ebp - 0x2c], eax
0054a2cb lea eax, [ebp - 0x2c]
0054a2ce mov dword ptr [ebp - 0x28], ecx
0054a2d1 mov ecx, dword ptr [0xbfd65c]
0054a2d7 push 3
0054a2d9 push eax
0054a2da lea eax, [esi + 0x294]
0054a2e0 mov ecx, dword ptr [ecx + 0x18190]
0054a2e6 push eax
0054a2e7 call 0x7af4b0
0054a2ec test al, al
0054a2ee je 0x54a31f
0054a2f0 movss xmm0, dword ptr [0xc02fec]
0054a2f8 movss dword ptr [esi + 0xb08], xmm0
0054a300 movss xmm0, dword ptr [0xc02ff0]
0054a308 movss dword ptr [esi + 0xb0c], xmm0
0054a310 mov dword ptr [esi + 0xab4], 4
0054a31a jmp 0x54a74f
0054a31f call 0x6c3d90
0054a324 xor edx, edx
0054a326 mov ecx, 3
0054a32b div ecx
0054a32d test edx, edx
0054a32f jne 0x54a74f
0054a335 lea eax, [ebp - 0x2c]
0054a338 push eax
0054a339 call 0x659290
0054a33e add esp, 4
0054a341 mov ecx, dword ptr [eax]
0054a343 mov dword ptr [esi + 0xb08], ecx
0054a349 mov eax, dword ptr [eax + 4]
0054a34c mov dword ptr [esi + 0xb0c], eax
0054a352 mov dword ptr [esi + 0xab4], 4
0054a35c jmp 0x54a74f
0054a361 lea eax, [ebp - 0x24]
0054a364 push eax
0054a365 call 0x549f50
0054a36a mov edx, dword ptr [esi + 0x70]
0054a36d lea ecx, [esi + 0x6c]
0054a370 mov edi, eax
0054a372 test edx, edx
0054a374 je 0x54a37c
0054a376 cmp byte ptr [edx + 0x34], 0
0054a37a jne 0x54a3a4
0054a37c lea eax, [ebp - 0x1c]
0054a37f push eax
0054a380 call 0x444be0
0054a385 mov dword ptr [ebp - 0x30], 1
0054a38c mov ecx, eax
0054a38e mov edx, dword ptr [edi*4 + 0xb426c4]
0054a395 call 0x447a10
0054a39a test al, al
0054a39c je 0x54a3a4
0054a39e mov byte ptr [ebp - 0x1d], 1
0054a3a2 jmp 0x54a3ae
0054a3a4 test byte ptr [ebp - 0x30], 1
0054a3a8 mov byte ptr [ebp - 0x1d], 0
0054a3ac je 0x54a3e4
0054a3ae mov edx, dword ptr [ebp - 8]
0054a3b1 cmp edx, 0x10
0054a3b4 jb 0x54a3e4
0054a3b6 mov ecx, dword ptr [ebp - 0x1c]
0054a3b9 inc edx
0054a3ba mov eax, ecx
0054a3bc cmp edx, 0x1000
0054a3c2 jb 0x54a3da
0054a3c4 mov ecx, dword ptr [ecx - 4]
0054a3c7 add edx, 0x23
0054a3ca sub eax, ecx
0054a3cc add eax, -4
0054a3cf cmp eax, 0x1f
0054a3d2 jbe 0x54a3da
0054a3d4 call dword ptr [0xa065ac]
0054a3da push edx
0054a3db push ecx
0054a3dc call 0x9eb08e
0054a3e1 add esp, 8
0054a3e4 cmp byte ptr [ebp - 0x1d], 0
0054a3e8 lea ecx, [esi + 0x3c]
0054a3eb mov eax, dword ptr [edi*4 + 0xb426c4]
0054a3f2 push 0
0054a3f4 push eax
0054a3f5 je 0x54a3fe
0054a3f7 call 0x405740
0054a3fc jmp 0x54a403
0054a3fe call 0x4054f0
0054a403 cmp dword ptr [esi + 0xe6c], -1
0054a40a movss xmm0, dword ptr [ebp - 0x24]
0054a40f movss dword ptr [esi + 0xe0], xmm0
0054a417 je 0x54a4b9
0054a41d movss xmm2, dword ptr [0xb6a2cc]
0054a425 lea eax, [ebp - 0x2c]
0054a428 push eax
0054a429 mov ecx, esi
0054a42b call 0x6af0c0
0054a430 movss xmm1, dword ptr [ebp - 0x2c]
0054a435 ucomiss xmm1, dword ptr [0xc02fec]
0054a43c movss xmm0, dword ptr [ebp - 0x28]
0054a441 lahf 
0054a442 test ah, 0x44
0054a445 jp 0x54a4a9
0054a447 ucomiss xmm0, dword ptr [0xc02ff0]
0054a44e lahf 
0054a44f test ah, 0x44
0054a452 jp 0x54a4a9
0054a454 movss xmm2, dword ptr [esi + 0x2f4]
0054a45c ucomiss xmm2, dword ptr [0xb6a614]
0054a463 movss xmm1, dword ptr [0xb6a5f8]
0054a46b lahf 
0054a46c test ah, 0x44
0054a46f jnp 0x54a484
0054a471 movaps xmm0, xmm2
0054a474 mulss xmm2, xmm1
0054a478 addss xmm0, xmm1
0054a47c subss xmm0, xmm2
0054a480 divss xmm1, xmm0
0054a484 movaps xmm0, xmm1
0054a487 mulss xmm1, dword ptr [esi + 0xb0c]
0054a48f mulss xmm0, dword ptr [esi + 0xb08]
0054a497 movss dword ptr [esi + 0xb0c], xmm1
0054a49f movss dword ptr [esi + 0xb08], xmm0
0054a4a7 jmp 0x54a4b9
0054a4a9 movss dword ptr [esi + 0xb08], xmm1
0054a4b1 movss dword ptr [esi + 0xb0c], xmm0
0054a4b9 movss xmm1, dword ptr [esi + 0xb08]
0054a4c1 ucomiss xmm1, dword ptr [0xc02fec]
0054a4c8 movss xmm2, dword ptr [esi + 0xb0c]
0054a4d0 movss dword ptr [ebp - 0x24], xmm1
0054a4d5 lahf 
0054a4d6 movss dword ptr [ebp - 0x30], xmm2
0054a4db test ah, 0x44
0054a4de jp 0x54a57b
0054a4e4 ucomiss xmm2, dword ptr [0xc02ff0]
0054a4eb lahf 
0054a4ec test ah, 0x44
0054a4ef jp 0x54a57b
0054a4f5 mov ecx, esi
0054a4f7 call 0x695680
0054a4fc lea ecx, [ebp - 0x2c]
0054a4ff movss xmm0, dword ptr [eax + 0x294]
0054a507 movss xmm1, dword ptr [eax + 0x298]
0054a50f lea eax, [ebp - 0x34]
0054a512 subss xmm0, dword ptr [esi + 0x294]
0054a51a subss xmm1, dword ptr [esi + 0x298]
0054a522 push eax
0054a523 movss dword ptr [ebp - 0x2c], xmm0
0054a528 movss dword ptr [ebp - 0x28], xmm1
0054a52d call 0x962560
0054a532 push 0
0054a534 push 0x1000800
0054a539 mov ecx, esi
0054a53b movss xmm1, dword ptr [eax]
0054a53f movss dword ptr [ebp - 0x24], xmm1
0054a544 movss xmm1, dword ptr [eax + 4]
0054a549 movss dword ptr [ebp - 0x30], xmm1
0054a54e call 0x4122f0
0054a553 movss xmm1, dword ptr [ebp - 0x24]
0054a558 movss xmm2, dword ptr [ebp - 0x30]
0054a55d test al, al
0054a55f je 0x54a57b
0054a561 mulss xmm1, dword ptr [0xb6ae44]
0054a569 mulss xmm2, dword ptr [0xb6ae44]
0054a571 movss dword ptr [ebp - 0x24], xmm1
0054a576 movss dword ptr [ebp - 0x30], xmm2
0054a57b mov eax, dword ptr [esi + 0x160]
0054a581 and eax, 0x200
0054a586 or eax, 0
0054a589 je 0x54a5ae
0054a58b cmp dword ptr [esi + 0xe6c], -1
0054a592 jne 0x54a5ae
0054a594 mulss xmm1, dword ptr [0xb6a480]
0054a59c mulss xmm2, dword ptr [0xb6a480]
0054a5a4 movss dword ptr [ebp - 0x24], xmm1
0054a5a9 movss dword ptr [ebp - 0x30], xmm2
0054a5ae movss xmm0, dword ptr [esi + 0xb00]
0054a5b6 movss dword ptr [ebp - 0x28], xmm0
0054a5bb movaps xmm0, xmm2
0054a5be call 0x447a80
0054a5c3 movss xmm1, dword ptr [esi + 0xb00]
0054a5cb movaps xmm2, xmm0
0054a5ce mulss xmm2, dword ptr [0xb6aa84]
0054a5d6 movss xmm4, dword ptr [0xb6c980]
0054a5de movss xmm3, dword ptr [0xb6ac40]
0054a5e6 subss xmm2, xmm1
0054a5ea movaps xmm0, xmm2
0054a5ed andps xmm0, xmm4
0054a5f0 comiss xmm0, xmm3
0054a5f3 jbe 0x54a618
0054a5f5 movaps xmm1, xmm3
0054a5f8 movaps xmm0, xmm2
0054a5fb call 0x447b40
0054a600 movss xmm3, dword ptr [0xb6ac40]
0054a608 movaps xmm2, xmm0
0054a60b movss xmm1, dword ptr [ebp - 0x28]
0054a610 movss xmm4, dword ptr [0xb6c980]
0054a618 comiss xmm2, dword ptr [0xb6ab88]
0054a61f jbe 0x54a627
0054a621 subss xmm2, xmm3
0054a625 jmp 0x54a638
0054a627 movss xmm0, dword ptr [0xb6af74]
0054a62f comiss xmm0, xmm2
0054a632 jbe 0x54a638
0054a634 addss xmm2, xmm3
0054a638 mulss xmm2, dword ptr [0xb6a350]
0054a640 addss xmm2, xmm1
0054a644 movaps xmm1, xmm2
0054a647 andps xmm1, xmm4
0054a64a comiss xmm1, xmm3
0054a64d jbe 0x54a665
0054a64f movaps xmm1, xmm3
0054a652 movaps xmm0, xmm2
0054a655 call 0x447b40
0054a65a movss xmm3, dword ptr [0xb6ac40]
0054a662 movaps xmm2, xmm0
0054a665 comiss xmm2, dword ptr [0xb6ab88]
0054a66c jbe 0x54a674
0054a66e subss xmm2, xmm3
0054a672 jmp 0x54a685
0054a674 movss xmm0, dword ptr [0xb6af74]
0054a67c comiss xmm0, xmm2
0054a67f jbe 0x54a685
0054a681 addss xmm2, xmm3
0054a685 movss dword ptr [esi + 0xb00], xmm2
0054a68d cmp dword ptr [esi + 0x70], 0
0054a691 je 0x54a745
0054a697 push 0xb43610
0054a69c lea ecx, [esi + 0x6c]
0054a69f call 0x405e90
0054a6a4 test al, al
0054a6a6 je 0x54a736
0054a6ac cmp dword ptr [esi + 0xe6c], -1
0054a6b3 je 0x54a6bf
0054a6b5 movss xmm2, dword ptr [0xb6a95c]
0054a6bd jmp 0x54a6f4
0054a6bf call 0x6c3d90
0054a6c4 movd xmm0, eax
0054a6c8 cvtdq2pd xmm0, xmm0
0054a6cc shr eax, 0x1f
0054a6cf addsd xmm0, qword ptr [eax*8 + 0xb6c940]
0054a6d8 cvtpd2ps xmm2, xmm0
0054a6dc mulss xmm2, dword ptr [0xb6a19c]
0054a6e4 mulss xmm2, dword ptr [0xb6a864]
0054a6ec addss xmm2, dword ptr [0xb6a910]
0054a6f4 movss xmm1, dword ptr [ebp - 0x24]
0054a6f9 movss xmm0, dword ptr [esi + 0x2f4]
0054a701 mulss xmm1, xmm2
0054a705 mulss xmm1, xmm0
0054a709 addss xmm1, dword ptr [esi + 0x2b8]
0054a711 movss dword ptr [esi + 0x2b8], xmm1
0054a719 movss xmm1, dword ptr [ebp - 0x30]
0054a71e mulss xmm1, xmm2
0054a722 mulss xmm1, xmm0
0054a726 addss xmm1, dword ptr [esi + 0x2bc]
0054a72e movss dword ptr [esi + 0x2bc], xmm1
0054a736 cmp dword ptr [esi + 0x70], 0
0054a73a je 0x54a745
0054a73c cmp byte ptr [esi + 0x80], 0
0054a743 jne 0x54a74f
0054a745 mov dword ptr [esi + 0xab4], 3
0054a74f movss xmm0, dword ptr [esi + 0x2c4]
0054a757 mulss xmm0, dword ptr [0xb6a5d8]
0054a75f mov ecx, dword ptr [ebp - 4]
0054a762 pop edi
0054a763 xor ecx, ebp
0054a765 movss dword ptr [esi + 0x2c4], xmm0
0054a76d pop esi
0054a76e call 0x9eacd7
0054a773 mov esp, ebp
0054a775 pop ebp
0054a776 mov esp, ebx
0054a778 pop ebx
0054a779 ret 
