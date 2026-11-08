0074a12f cmp dword ptr [edi + 0x1544], 0
0074a136 jg 0x74a901
0074a13c push 0
0074a13e push 0x205
0074a143 mov ecx, edi
0074a145 call 0x73af30
0074a14a test al, al
0074a14c mov ecx, edi
0074a14e mov eax, 0x1e
0074a153 cmovne eax, esi
0074a156 mov esi, 1
0074a15b push 0xa4
0074a160 mov dword ptr [edi + 0x1544], eax
0074a166 mov dword ptr [esp + 0x38], esi
0074a16a call 0x78d4c0
0074a16f test eax, eax
0074a171 jle 0x74a186
0074a173 push 0xa4
0074a178 mov ecx, edi
0074a17a call 0x78d4c0
0074a17f lea esi, [eax + 1]
0074a182 mov dword ptr [esp + 0x34], esi
0074a186 mov dword ptr [esp + 0x28], 0
0074a18e test esi, esi
0074a190 jle 0x74a901
0074a196 push 0
0074a198 lea eax, [esp + 0x74]
0074a19c mov ecx, edi
0074a19e push eax
0074a19f call 0x749480
0074a1a4 push 0
0074a1a6 push 0x6a
0074a1a8 mov ecx, edi
0074a1aa call 0x73af30
0074a1af mov ecx, dword ptr [esp + 0x74]
0074a1b3 test al, al
0074a1b5 mov eax, dword ptr [esp + 0x7c]
0074a1b9 mov edx, dword ptr [esp + 0x78]
0074a1bd mov dword ptr [esp + 0xc], ecx
0074a1c1 mov ecx, dword ptr [esp + 0x70]
0074a1c5 mov dword ptr [esp + 0x5c], eax
0074a1c9 mov dword ptr [esp + 0x50], edx
0074a1cd mov dword ptr [esp + 0x60], ecx
0074a1d1 jne 0x74a203
0074a1d3 and ecx, dword ptr [0xbc49a0]
0074a1d9 mov esi, eax
0074a1db mov eax, dword ptr [esp + 0xc]
0074a1df and eax, dword ptr [0xbc49a4]
0074a1e5 and edx, dword ptr [0xbc49a8]
0074a1eb and esi, dword ptr [0xbc49ac]
0074a1f1 or ecx, eax
0074a1f3 jne 0x74a203
0074a1f5 or edx, esi
0074a1f7 jne 0x74a203
0074a1f9 movss xmm0, dword ptr [0xb6a614]
0074a201 jmp 0x74a20b
0074a203 movss xmm0, dword ptr [0xb6a6f0]
0074a20b movss dword ptr [esp + 0x38], xmm0
0074a211 mov ecx, edi
0074a213 movss xmm0, dword ptr [edi + 0x2b8]
0074a21b mulss xmm0, dword ptr [0xb6a2cc]
0074a223 push 0
0074a225 push 0x247
0074a22a movss dword ptr [esp + 0x28], xmm0
0074a230 movss dword ptr [esp + 0x50], xmm0
0074a236 movss xmm0, dword ptr [edi + 0x2bc]
0074a23e mulss xmm0, dword ptr [0xb6a2cc]
0074a246 movss dword ptr [esp + 0x2c], xmm0
0074a24c movss dword ptr [esp + 0x54], xmm0
0074a252 call 0x73af30
0074a257 test al, al
0074a259 je 0x74a408
0074a25f cmp dword ptr [edi + 0x1560], -1
0074a266 xorps xmm1, xmm1
0074a269 movss xmm5, dword ptr [0xc02ff0]
0074a271 xorps xmm2, xmm2
0074a274 movss xmm4, dword ptr [0xc02fec]
0074a27c movss dword ptr [esp + 0x14], xmm1
0074a282 movss dword ptr [esp + 0x18], xmm2
0074a288 je 0x74a2c3
0074a28a movss xmm3, dword ptr [edi + 0x1564]
0074a292 ucomiss xmm3, xmm4
0074a295 lahf 
0074a296 test ah, 0x44
0074a299 jp 0x74a2ac
0074a29b movss xmm0, dword ptr [edi + 0x1568]
0074a2a3 ucomiss xmm0, xmm5
0074a2a6 lahf 
0074a2a7 test ah, 0x44
0074a2aa jnp 0x74a2c3
0074a2ac movss xmm1, dword ptr [edi + 0x1568]
0074a2b4 movaps xmm2, xmm3
0074a2b7 movss dword ptr [esp + 0x18], xmm2
0074a2bd movss dword ptr [esp + 0x14], xmm1
0074a2c3 ucomiss xmm2, xmm4
0074a2c6 lahf 
0074a2c7 test ah, 0x44
0074a2ca jp 0x74a2d9
0074a2cc ucomiss xmm1, xmm5
0074a2cf lahf 
0074a2d0 test ah, 0x44
0074a2d3 jnp 0x74a408
0074a2d9 movaps xmm0, xmm1
0074a2dc movss dword ptr [esp + 0x44], xmm1
0074a2e2 mulss xmm0, xmm1
0074a2e6 movaps xmm1, xmm2
0074a2e9 mulss xmm1, xmm2
0074a2ed movss dword ptr [esp + 0x40], xmm2
0074a2f3 addss xmm0, xmm1
0074a2f7 call 0x4228c0
0074a2fc comiss xmm0, dword ptr [0xb6a18c]
0074a303 jbe 0x74a33d
0074a305 movss xmm1, dword ptr [0xb6a614]
0074a30d divss xmm1, xmm0
0074a311 movss xmm0, dword ptr [esp + 0x18]
0074a317 mulss xmm0, xmm1
0074a31b movss dword ptr [esp + 0x18], xmm0
0074a321 movss dword ptr [esp + 0x40], xmm0
0074a327 movss xmm0, dword ptr [esp + 0x14]
0074a32d mulss xmm0, xmm1
0074a331 movss dword ptr [esp + 0x14], xmm0
0074a337 movss dword ptr [esp + 0x44], xmm0
0074a33d push 0
0074a33f lea eax, [esp + 0x44]
0074a343 mov ecx, edi
0074a345 push eax
0074a346 lea eax, [esp + 0x88]
0074a34d push eax
0074a34e call 0x76ff80
0074a353 movss xmm1, dword ptr [esp + 0x18]
0074a359 movaps xmm0, xmm1
0074a35c mulss xmm0, dword ptr [0xb6a974]
0074a364 addss xmm0, dword ptr [eax]
0074a368 movss dword ptr [esp + 0x20], xmm0
0074a36e movss dword ptr [esp + 0x48], xmm0
0074a374 movss xmm0, dword ptr [esp + 0x14]
0074a37a movaps xmm2, xmm0
0074a37d mulss xmm2, dword ptr [0xb6a974]
0074a385 addss xmm2, dword ptr [eax + 4]
0074a38a movss dword ptr [esp + 0x24], xmm2
0074a390 movss dword ptr [esp + 0x4c], xmm2
0074a396 call 0x447a80
0074a39b cmp byte ptr [esp + 9], 0
0074a3a0 mov ecx, 0x13
0074a3a5 mulss xmm0, dword ptr [0xb6aa84]
0074a3ad mov dword ptr [esp + 0x30], ecx
0074a3b1 mov byte ptr [esp + 0xb], 1
0074a3b6 movss dword ptr [esp + 0x3c], xmm0
0074a3bc je 0x74a443
0074a3c2 movss xmm1, dword ptr [esp + 0x18]
0074a3c8 mulss xmm1, dword ptr [0xb6a8f4]
0074a3d0 movss xmm0, dword ptr [edi + 0x2b8]
0074a3d8 subss xmm0, xmm1
0074a3dc movss xmm1, dword ptr [esp + 0x14]
0074a3e2 mulss xmm1, dword ptr [0xb6a8f4]
0074a3ea movss dword ptr [edi + 0x2b8], xmm0
0074a3f2 movss xmm0, dword ptr [edi + 0x2bc]
0074a3fa subss xmm0, xmm1
0074a3fe movss dword ptr [edi + 0x2bc], xmm0
0074a406 jmp 0x74a421
0074a408 xor ecx, ecx
0074a40a xorps xmm0, xmm0
0074a40d mov dword ptr [esp + 0x30], ecx
0074a411 mov byte ptr [esp + 0xb], cl
0074a415 movss dword ptr [esp + 0x3c], xmm0
0074a41b cmp byte ptr [esp + 9], cl
0074a41f je 0x74a443
0074a421 movss xmm0, dword ptr [0xb6a614]
0074a429 cmp ecx, 0x13
0074a42c mov eax, 0x11
0074a431 movss dword ptr [esp + 0x38], xmm0
0074a437 mov ecx, 0x14
0074a43c cmove eax, ecx
0074a43f mov dword ptr [esp + 0x30], eax
0074a443 call 0x6c3d90
0074a448 mov ecx, dword ptr [0xbfd65c]
0074a44e push 0
0074a450 push eax
0074a451 push 0
0074a453 push edi
0074a454 lea eax, [esp + 0x58]
0074a458 push eax
0074a459 lea eax, [edi + 0x294]
0074a45f push eax
0074a460 push dword ptr [esp + 0x48]
0074a464 push 4
0074a466 call 0x6d0ca0
0074a46b cmp dword ptr [esp + 0x34], 1
0074a470 mov esi, eax
0074a472 mov dword ptr [esp + 0x14], esi
0074a476 jle 0x74a6c1
0074a47c cmp byte ptr [esp + 0xb], 0
0074a481 je 0x74a63f
0074a487 movss xmm1, dword ptr [esp + 0x20]
0074a48d movss xmm0, dword ptr [esp + 0x24]
0074a493 mulss xmm0, xmm0
0074a497 mulss xmm1, xmm1
0074a49b addss xmm0, xmm1
0074a49f call 0x4228c0
0074a4a4 xorps xmm4, xmm4
0074a4a7 comiss xmm0, xmm4
0074a4aa jbe 0x74a4d8
0074a4ac movss xmm1, dword ptr [0xb6a614]
0074a4b4 divss xmm1, xmm0
0074a4b8 movss xmm0, dword ptr [esp + 0x20]
0074a4be mulss xmm0, xmm1
0074a4c2 movss dword ptr [esp + 0x20], xmm0
0074a4c8 movss xmm0, dword ptr [esp + 0x24]
0074a4ce mulss xmm0, xmm1
0074a4d2 movss dword ptr [esp + 0x24], xmm0
0074a4d8 mov eax, dword ptr [esp + 0x34]
0074a4dc movd xmm2, eax
0074a4e0 dec eax
0074a4e1 cvtdq2ps xmm2, xmm2
0074a4e4 movd xmm1, eax
0074a4e8 mulss xmm2, dword ptr [0xb6a864]
0074a4f0 cvtdq2ps xmm1, xmm1
0074a4f3 movaps xmm3, xmm2
0074a4f6 movss dword ptr [esp + 0x18], xmm2
0074a4fc xorps xmm3, xmmword ptr [0xb6c9b0]
0074a503 ucomiss xmm4, xmm1
0074a506 movss dword ptr [esp + 0x1c], xmm1
0074a50c movss dword ptr [esp + 0x2c], xmm3
0074a512 lahf 
0074a513 test ah, 0x44
0074a516 jp 0x74a53c
0074a518 push 0xb5d590
0074a51d push 3
0074a51f call 0x95e330
0074a524 movss xmm2, dword ptr [esp + 0x20]
0074a52a add esp, 8
0074a52d movss xmm3, dword ptr [esp + 0x2c]
0074a533 xorps xmm4, xmm4
0074a536 movss xmm1, dword ptr [esp + 0x1c]
0074a53c movd xmm0, dword ptr [esp + 0x28]
0074a542 subss xmm1, xmm4
0074a546 cvtdq2ps xmm0, xmm0
0074a549 lea eax, [esp + 0x1c]
0074a54d mov dword ptr [esp + 0x1c], 0
0074a555 lea ecx, [esp + 0x2c]
0074a559 subss xmm0, xmm4
0074a55d divss xmm0, xmm1
0074a561 movss xmm1, dword ptr [0xb6a614]
0074a569 comiss xmm4, xmm0
0074a56c movss dword ptr [esp + 0x2c], xmm0
0074a572 cmovbe eax, ecx
0074a575 movss xmm0, dword ptr [eax]
0074a579 comiss xmm0, xmm1
0074a57c ja 0x74a584
0074a57e movss xmm1, xmm0
0074a582 jmp 0x74a588
0074a584 movss xmm1, xmm1
0074a588 subss xmm2, xmm3
0074a58c mulss xmm2, xmm1
0074a590 addss xmm2, xmm3
0074a594 mulss xmm2, dword ptr [0xb6a230]
0074a59c movaps xmm0, xmm2
0074a59f movss dword ptr [esp + 0x18], xmm2
0074a5a5 call 0x411fe0
0074a5aa movss dword ptr [esp + 0x1c], xmm0
0074a5b0 movss xmm0, dword ptr [esp + 0x18]
0074a5b6 call 0x412010
0074a5bb movss xmm5, dword ptr [esp + 0x20]
0074a5c1 movaps xmm2, xmm0
0074a5c4 movss xmm6, dword ptr [esp + 0x24]
0074a5ca movaps xmm4, xmm5
0074a5cd mulss xmm4, dword ptr [esp + 0x1c]
0074a5d3 movaps xmm1, xmm6
0074a5d6 movss xmm7, dword ptr [0xb6aad4]
0074a5de movss xmm0, dword ptr [edi + 0x294]
0074a5e6 mulss xmm1, xmm2
0074a5ea subss xmm4, xmm1
0074a5ee movaps xmm1, xmm5
0074a5f1 mulss xmm1, xmm7
0074a5f5 mulss xmm5, xmm2
0074a5f9 subss xmm0, xmm1
0074a5fd mulss xmm4, xmm7
0074a601 movaps xmm1, xmm6
0074a604 mulss xmm6, xmm7
0074a608 mulss xmm1, dword ptr [esp + 0x1c]
0074a60e addss xmm4, xmm0
0074a612 movss xmm0, dword ptr [edi + 0x298]
0074a61a subss xmm0, xmm6
0074a61e addss xmm1, xmm5
0074a622 movss dword ptr [esi + 0x294], xmm4
0074a62a mulss xmm1, xmm7
0074a62e addss xmm1, xmm0
0074a632 movss dword ptr [esi + 0x298], xmm1
0074a63a jmp 0x74a6c1
0074a63f call 0x6c3d90
0074a644 xorps xmm0, xmm0
0074a647 cvtsi2sd xmm0, eax
0074a64b shr eax, 0x1f
0074a64e addsd xmm0, qword ptr [eax*8 + 0xb6c940]
0074a657 cvtpd2ps xmm0, xmm0
0074a65b mulss xmm0, dword ptr [0xb6a19c]
0074a663 mulss xmm0, dword ptr [0xb6a874]
0074a66b addss xmm0, xmm0
0074a66f movss dword ptr [esp + 0x1c], xmm0
0074a675 call 0x411fe0
0074a67a mulss xmm0, dword ptr [0xb6a940]
0074a682 addss xmm0, dword ptr [edi + 0x294]
0074a68a movss dword ptr [esp + 0x2c], xmm0
0074a690 movss xmm0, dword ptr [esp + 0x1c]
0074a696 call 0x412010
0074a69b mulss xmm0, dword ptr [0xb6a940]
0074a6a3 movss xmm1, dword ptr [esp + 0x2c]
0074a6a9 addss xmm0, dword ptr [edi + 0x298]
0074a6b1 movss dword ptr [esi + 0x294], xmm1
0074a6b9 movss dword ptr [esi + 0x298], xmm0
0074a6c1 movups xmm0, xmmword ptr [esp + 0x70]
0074a6c6 mov byte ptr [esi + 0x3b3], 1
0074a6cd movss xmm1, dword ptr [esp + 0x38]
0074a6d3 comiss xmm1, dword ptr [0xb6a6f0]
0074a6da movups xmmword ptr [esi + 0x388], xmm0
0074a6e1 movss xmm0, dword ptr [esp + 0x3c]
0074a6e7 movss dword ptr [esi + 0x384], xmm1
0074a6ef movss dword ptr [esi + 0x378], xmm0
0074a6f7 jb 0x74a711
0074a6f9 movss xmm0, dword ptr [esi + 0x368]
0074a701 addss xmm0, dword ptr [0xb6aad8]
0074a709 movss dword ptr [esi + 0x368], xmm0
0074a711 cmp byte ptr [esp + 9], 0
0074a716 je 0x74a742
0074a718 cmp dword ptr [esi + 0x70], 0
0074a71c je 0x74a72e
0074a71e mov eax, dword ptr [esi + 0x70]
0074a721 lea ecx, [esi + 0x6c]
0074a724 mov eax, dword ptr [eax + 0x30]
0074a727 dec eax
0074a728 push eax
0074a729 call 0x403b00
0074a72e mov dword ptr [esi + 0x360], 0x2d
0074a738 mov dword ptr [esi + 0x364], 0x2d
0074a742 cmp dword ptr [esp + 0x28], 0
0074a747 jne 0x74a7a9
0074a749 cmp byte ptr [esp + 0xa], 0
0074a74e jne 0x74a759
0074a750 push -1
0074a752 mov ecx, edi
0074a754 call 0x794cf0
0074a759 cmp byte ptr [esp + 0x10], 0
0074a75e jne 0x74a7a9
0074a760 mov eax, dword ptr [edi + 0x12b4]
0074a766 mov ecx, 0x63
0074a76b dec eax
0074a76c cmp eax, ecx
0074a76e push 4
0074a770 cmovl ecx, eax
0074a773 xor eax, eax
0074a775 test ecx, ecx
0074a777 cmovg eax, ecx
0074a77a mov ecx, edi
0074a77c mov dword ptr [edi + 0x12b4], eax
0074a782 call 0x725af0
0074a787 mov eax, dword ptr [0xbfd65c]
0074a78c cmp dword ptr [eax + 0x101904], 2
0074a793 je 0x74a7a9
0074a795 mov dword ptr [eax + 0x101904], 1
0074a79f mov dword ptr [eax + 0x10190c], 2
0074a7a9 push 0x85
0074a7ae mov ecx, edi
0074a7b0 call 0x78d4c0
0074a7b5 test eax, eax
0074a7b7 jle 0x74a7cd
0074a7b9 mov dword ptr [esi + 0x360], 0x16
0074a7c3 mov dword ptr [esi + 0x364], 0x16
