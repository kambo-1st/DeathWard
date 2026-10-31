00519dd0 push ebx
00519dd1 mov ebx, esp
00519dd3 sub esp, 8
00519dd6 and esp, 0xfffffff8
00519dd9 add esp, 4
00519ddc push ebp
00519ddd mov ebp, dword ptr [ebx + 4]
00519de0 mov dword ptr [esp + 4], ebp
00519de4 mov ebp, esp
00519de6 push -1
00519de8 push 0x9ef6cd
00519ded mov eax, dword ptr fs:[0]
00519df3 push eax
00519df4 push ebx
00519df5 sub esp, 0x120
00519dfb mov eax, dword ptr [0xbaa3b4]
00519e00 xor eax, ebp
00519e02 mov dword ptr [ebp - 0x14], eax
00519e05 push esi
00519e06 push edi
00519e07 push eax
00519e08 lea eax, [ebp - 0xc]
00519e0b mov dword ptr fs:[0], eax
00519e11 mov esi, ecx
00519e13 mov eax, dword ptr [esi + 0x2c]
00519e16 cmp eax, 0x16
00519e19 jne 0x519e25
00519e1b call 0x519980
00519e20 jmp 0x51af76
00519e25 cmp dword ptr [esi + 0xab4], 0
00519e2c jne 0x51a064
00519e32 cmp dword ptr [esi + 0x34], 0x109
00519e39 mov dword ptr [esi + 0xab4], 4
00519e43 jne 0x519fd5
00519e49 cmp dword ptr [esi + 0x28], 0x27
00519e4d jne 0x51af76
00519e53 test eax, eax
00519e55 jne 0x51af76
00519e5b push 0x30
00519e5d call 0x407de0
00519e62 movups xmm0, xmmword ptr [0xb4316c]
00519e69 mov edx, eax
00519e6b mov dword ptr [ebp - 0x34], 0x2c
00519e72 mov ecx, 0x2f
00519e77 mov dword ptr [ebp - 0x44], edx
00519e7a mov dword ptr [ebp - 0x30], ecx
00519e7d movups xmmword ptr [edx], xmm0
00519e80 movups xmm0, xmmword ptr [0xb4317c]
00519e87 movups xmmword ptr [edx + 0x10], xmm0
00519e8b movq xmm0, qword ptr [0xb4318c]
00519e93 movq qword ptr [edx + 0x20], xmm0
00519e98 mov eax, dword ptr [0xb43194]
00519e9d mov dword ptr [edx + 0x28], eax
00519ea0 mov byte ptr [edx + 0x2c], 0
00519ea4 mov dword ptr [ebp - 4], 0
00519eab lea edi, [esi + 0x3c]
00519eae cmp dword ptr [esi + 0xbc], 1
00519eb5 jle 0x519ef4
00519eb7 mov eax, dword ptr [esi + 0xb8]
00519ebd lea ecx, [ebp - 0x44]
00519ec0 lea edi, [eax + 0xa4]
00519ec6 cmp edi, ecx
00519ec8 mov dword ptr [ebp - 0x104], edi
00519ece mov ecx, dword ptr [ebp - 0x30]
00519ed1 lea edi, [esi + 0x3c]
00519ed4 je 0x519eed
00519ed6 mov ecx, dword ptr [ebp - 0x104]
00519edc push 0x2c
00519ede push edx
00519edf call 0x407c80
00519ee4 mov eax, dword ptr [edi + 0x7c]
00519ee7 mov ecx, dword ptr [ebp - 0x30]
00519eea mov edx, dword ptr [ebp - 0x44]
00519eed mov byte ptr [eax + 0xcc], 0
00519ef4 mov dword ptr [ebp - 4], 0xffffffff
00519efb cmp ecx, 0x10
00519efe jb 0x519f2b
00519f00 inc ecx
00519f01 mov eax, edx
00519f03 cmp ecx, 0x1000
00519f09 jb 0x519f21
00519f0b mov edx, dword ptr [edx - 4]
00519f0e add ecx, 0x23
00519f11 sub eax, edx
00519f13 add eax, -4
00519f16 cmp eax, 0x1f
00519f19 jbe 0x519f21
00519f1b call dword ptr [0xa065ac]
00519f21 push ecx
00519f22 push edx
00519f23 call 0x9eb08e
00519f28 add esp, 8
00519f2b push ecx
00519f2c mov ecx, edi
00519f2e call 0x4073a0
00519f33 cmp dword ptr [edi + 0x80], 0
00519f3a jg 0x519f58
00519f3c cmp dword ptr [edi + 0x14], 0x10
00519f40 mov eax, edi
00519f42 jb 0x519f46
00519f44 mov eax, dword ptr [edi]
00519f46 push 0
00519f48 push eax
00519f49 push 0xa0830c
00519f4e push 3
00519f50 call 0x95e330
00519f55 add esp, 0x10
00519f58 mov eax, dword ptr [edi + 0x7c]
00519f5b lea ecx, [ebp - 0x58]
00519f5e push 0x50
00519f60 push 0x64
00519f62 push 0x64
00519f64 push 0xff
00519f69 push 0xa
00519f6b push 0x50
00519f6d push 0xa
00519f6f mov dword ptr [eax + 0x48], 0x3ef0f0f2
00519f76 mov dword ptr [eax + 0x4c], 0x3f028283
00519f7d mov dword ptr [eax + 0x50], 0x3f028283
00519f84 mov dword ptr [eax + 0x54], 0x3f800000
00519f8b call 0x447b90
00519f90 push eax
00519f91 lea ecx, [esi + 0x1dc]
00519f97 call 0x4021a0
00519f9c mov esi, dword ptr [0xbfd680]
00519fa2 push 2
00519fa4 push 0x32
00519fa6 push 0x3e8
00519fab lea ecx, [esi + 0x29f88]
00519fb1 call 0x66d910
00519fb6 test eax, eax
00519fb8 je 0x519fc6
00519fba push eax
00519fbb lea ecx, [esi + 0x29f88]
00519fc1 call 0x6744f0
00519fc6 push 0xb4319c
00519fcb call 0x4097a0
00519fd0 jmp 0x51af76
00519fd5 mov esi, dword ptr [0xbfd680]
00519fdb push 1
00519fdd push 0x32
00519fdf push 0x3e8
00519fe4 lea ecx, [esi + 0x29f88]
00519fea call 0x66d910
00519fef test eax, eax
00519ff1 je 0x51a005
00519ff3 push eax
00519ff4 lea ecx, [esi + 0x29f88]
00519ffa call 0x6744f0
00519fff mov esi, dword ptr [0xbfd680]
0051a005 lea eax, [ebp - 0x104]
0051a00b mov dword ptr [ebp - 0x104], 0x700100
0051a015 push eax
0051a016 lea eax, [ebp - 0x20]
0051a019 add esi, 0x29f88
0051a01f push eax
0051a020 mov ecx, esi
0051a022 call 0x411300
0051a027 mov eax, dword ptr [ebp - 0x18]
0051a02a cmp byte ptr [eax + 0xd], 0
0051a02e jne 0x51a042
0051a030 cmp dword ptr [eax + 0x10], 0x700100
0051a037 ja 0x51a042
0051a039 cmp eax, dword ptr [esi]
0051a03b je 0x51a042
0051a03d add eax, 0x18
0051a040 jmp 0x51a04f
0051a042 push 0
0051a044 push 0
0051a046 push 7
0051a048 mov ecx, esi
0051a04a call 0x66d910
0051a04f test eax, eax
0051a051 je 0x51af76
0051a057 push eax
0051a058 mov ecx, esi
0051a05a call 0x6744f0
0051a05f jmp 0x51af76
0051a064 cmp dword ptr [esi + 0xe6c], -1
0051a06b jne 0x51a0a5
0051a06d mov eax, dword ptr [0xbfd65c]
0051a072 mov edi, dword ptr [eax + 0x18190]
0051a078 lea eax, [esi + 0x294]
0051a07e push eax
0051a07f mov ecx, edi
0051a081 call 0x7ce950
0051a086 cmp eax, 0x1bf
0051a08b ja 0x51a0a5
0051a08d cmp dword ptr [edi + eax*4 + 0x76c], 0x3b6
0051a098 jg 0x51a0a5
0051a09a mov dword ptr [edi + eax*4 + 0x76c], 0x384
0051a0a5 mov ecx, esi
0051a0a7 call 0x695680
0051a0ac lea edi, [esi + 0x294]
0051a0b2 movss xmm0, dword ptr [eax + 0x294]
0051a0ba movss xmm1, dword ptr [eax + 0x298]
0051a0c2 subss xmm0, dword ptr [edi]
0051a0c6 subss xmm1, dword ptr [edi + 4]
0051a0cb mov eax, dword ptr [esi + 0xab4]
0051a0d1 movss dword ptr [ebp - 0x104], xmm0
0051a0d9 movss dword ptr [ebp - 0x110], xmm1
0051a0e1 movss dword ptr [ebp - 0x10c], xmm0
0051a0e9 movss dword ptr [ebp - 0x108], xmm1
0051a0f1 cmp eax, 4
0051a0f4 jne 0x51a543
0051a0fa mov ecx, dword ptr [0xb40504]
0051a100 mov eax, dword ptr [0xb40508]
0051a105 mov dword ptr [ebp - 0x30], 0xf
0051a10c mov dword ptr [ebp - 0x34], 8
0051a113 mov dword ptr [ebp - 0x44], ecx
0051a116 mov dword ptr [ebp - 0x40], eax
0051a119 mov byte ptr [ebp - 0x3c], 0
0051a11d mov dword ptr [ebp - 4], 1
0051a124 mov dword ptr [ebp - 0x18], 0xf
0051a12b mov dword ptr [ebp - 0x1c], 8
0051a132 mov dword ptr [ebp - 0x2c], ecx
0051a135 mov dword ptr [ebp - 0x28], eax
0051a138 mov byte ptr [ebp - 0x24], 0
0051a13c push ecx
0051a13d mov byte ptr [ebp - 4], 2
0051a141 lea eax, [ebp - 0x44]
0051a144 mov dword ptr [esp], 0x3dcccccd
0051a14b mov ecx, esi
0051a14d push eax
0051a14e lea eax, [ebp - 0x2c]
0051a151 push eax
0051a152 call 0x6980a0
0051a157 mov byte ptr [ebp - 4], 1
0051a15b mov edx, dword ptr [ebp - 0x18]
0051a15e cmp edx, 0x10
0051a161 jb 0x51a18b
0051a163 mov ecx, dword ptr [ebp - 0x2c]
0051a166 inc edx
0051a167 mov eax, ecx
0051a169 cmp edx, 0x1000
0051a16f jb 0x51a181
0051a171 mov ecx, dword ptr [ecx - 4]
0051a174 add edx, 0x23
0051a177 sub eax, ecx
0051a179 add eax, -4
0051a17c cmp eax, 0x1f
0051a17f ja 0x51a1ca
0051a181 push edx
0051a182 push ecx
0051a183 call 0x9eb08e
0051a188 add esp, 8
0051a18b mov dword ptr [ebp - 4], 0xffffffff
0051a192 mov edx, dword ptr [ebp - 0x30]
0051a195 mov dword ptr [ebp - 0x1c], 0
0051a19c mov dword ptr [ebp - 0x18], 0xf
0051a1a3 mov byte ptr [ebp - 0x2c], 0
0051a1a7 cmp edx, 0x10
0051a1aa jb 0x51a1da
0051a1ac mov ecx, dword ptr [ebp - 0x44]
0051a1af inc edx
0051a1b0 mov eax, ecx
0051a1b2 cmp edx, 0x1000
0051a1b8 jb 0x51a1d0
0051a1ba mov ecx, dword ptr [ecx - 4]
0051a1bd add edx, 0x23
0051a1c0 sub eax, ecx
0051a1c2 add eax, -4
0051a1c5 cmp eax, 0x1f
0051a1c8 jbe 0x51a1d0
0051a1ca call dword ptr [0xa065ac]
0051a1d0 push edx
0051a1d1 push ecx
0051a1d2 call 0x9eb08e
0051a1d7 add esp, 8
0051a1da cmp dword ptr [esi + 0xe6c], -1
0051a1e1 lea ecx, [esi + 0x364]
0051a1e7 je 0x51a201
0051a1e9 push 1
0051a1eb push 0
0051a1ed push ecx
0051a1ee mov dword ptr [esp], 0x3f333333
0051a1f5 push 0xc02fec
0051a1fa call 0x7a3650
0051a1ff jmp 0x51a210
0051a201 push 0
0051a203 push ecx
0051a204 mov dword ptr [esp], 0x3f333333
0051a20b call 0x7a51e0
0051a210 mov edi, dword ptr [esi + 0xe6c]
0051a216 cmp edi, -1
0051a219 jne 0x51a22f
0051a21b push dword ptr [esi + 0x20]
0051a21e mov ecx, esi
0051a220 push 3
0051a222 call 0x684790
0051a227 test al, al
0051a229 je 0x51ace1
0051a22f cmp dword ptr [esi + 0x28], 0x31
0051a233 jne 0x51a2f1
0051a239 cmp edi, -1
0051a23c je 0x51a251
0051a23e push 9
0051a240 mov ecx, esi
0051a242 call 0x6af050
0051a247 test al, al
0051a249 je 0x51a2f1
0051a24f jmp 0x51a2d0
0051a251 call 0x6c3d90
0051a256 xor edx, edx
0051a258 mov ecx, 0xa
0051a25d div ecx
0051a25f mov edi, edx
0051a261 call 0x6c3d90
0051a266 xor edx, edx
0051a268 mov ecx, 7
0051a26d div ecx
0051a26f test edx, edx
0051a271 jne 0x51a2e9
0051a273 movss xmm1, dword ptr [ebp - 0x104]
0051a27b movss xmm0, dword ptr [ebp - 0x110]
0051a283 mulss xmm1, xmm1
0051a287 mulss xmm0, xmm0
0051a28b addss xmm0, xmm1
0051a28f call 0x4228c0
0051a294 movaps xmm2, xmm0
0051a297 call 0x6c3d90
0051a29c xorps xmm1, xmm1
0051a29f cvtsi2sd xmm1, eax
0051a2a3 shr eax, 0x1f
0051a2a6 addsd xmm1, qword ptr [eax*8 + 0xb6c940]
0051a2af cvtpd2ps xmm0, xmm1
0051a2b3 mulss xmm0, dword ptr [0xb6a19c]
0051a2bb mulss xmm0, dword ptr [0xb6ab34]
0051a2c3 addss xmm0, dword ptr [0xb6aab4]
0051a2cb comiss xmm0, xmm2
0051a2ce jbe 0x51a2f1
0051a2d0 mov dword ptr [esi + 0xab4], 8
0051a2da mov dword ptr [esi + 0x360], 0
0051a2e4 jmp 0x51ace1
0051a2e9 test edi, edi
0051a2eb jne 0x51ace1
0051a2f1 push 0
0051a2f3 push 0x1000a00
0051a2f8 mov ecx, esi
0051a2fa call 0x4122f0
0051a2ff test al, al
0051a301 jne 0x51ace1
0051a307 cmp dword ptr [esi + 0xe6c], -1
0051a30e movss xmm3, dword ptr [0xb6c980]
0051a316 je 0x51a332
0051a318 movss xmm1, dword ptr [0xb6accc]
0051a320 mov ecx, esi
0051a322 push 7
0051a324 push 0
0051a326 call 0x6a15a0
0051a32b movzx eax, al
0051a32e test eax, eax
0051a330 jmp 0x51a3a5
0051a332 movss xmm2, dword ptr [ebp - 0x104]
0051a33a movss xmm4, dword ptr [0xb6a9c8]
0051a342 movaps xmm0, xmm2
0051a345 andps xmm0, xmm3
0051a348 comiss xmm4, xmm0
0051a34b movss xmm0, dword ptr [ebp - 0x110]
0051a353 ja 0x51a364
0051a355 movaps xmm1, xmm0
0051a358 andps xmm1, xmm3
0051a35b comiss xmm4, xmm1
0051a35e jbe 0x51ace1
0051a364 mulss xmm2, xmm2
0051a368 mulss xmm0, xmm0
0051a36c addss xmm0, xmm2
0051a370 call 0x4228c0
0051a375 movss xmm1, dword ptr [0xb6ac60]
0051a37d comiss xmm1, xmm0
0051a380 jbe 0x51ace1
0051a386 lea eax, [esi + 0x294]
0051a38c push eax
0051a38d mov eax, dword ptr [0xbfd65c]
0051a392 mov ecx, dword ptr [eax + 0x18190]
0051a398 mov ecx, dword ptr [ecx + 0x11f8]
0051a39e call 0x89fbb0
0051a3a3 test al, al
0051a3a5 je 0x51ace1
0051a3ab cmp dword ptr [esi + 0xe6c], -1
0051a3b2 je 0x51a3cf
0051a3b4 lea eax, [ebp - 0x120]
0051a3ba xorps xmm2, xmm2
0051a3bd push eax
0051a3be mov ecx, esi
0051a3c0 call 0x6af380
0051a3c5 mov edx, eax
0051a3c7 lea ecx, [ebp - 0x130]
0051a3cd jmp 0x51a3db
0051a3cf lea edx, [ebp - 0x10c]
0051a3d5 lea ecx, [ebp - 0x120]
0051a3db call 0x6593a0
0051a3e0 mov ecx, dword ptr [eax]
0051a3e2 mov dword ptr [esi + 0xb00], ecx
0051a3e8 movss xmm0, dword ptr [eax + 4]
0051a3ed xor eax, eax
0051a3ef movss dword ptr [esi + 0xb04], xmm0
0051a3f7 cmp dword ptr [esi + 0x2c], 2
0051a3fb mov dword ptr [esi + 0x360], 0
0051a405 sete al
0051a408 add eax, 9
0051a40b mov dword ptr [esi + 0xab4], eax
0051a411 movss xmm0, dword ptr [0xc02fec]
0051a419 movss dword ptr [esi + 0x28c], xmm0
0051a421 movss xmm0, dword ptr [0xc02ff0]
0051a429 movss dword ptr [esi + 0x290], xmm0
0051a431 cmp dword ptr [esi + 0xab4], 0xa
0051a438 jne 0x51a47d
0051a43a movss xmm0, dword ptr [esi + 0xb00]
0051a442 lea ecx, [esi + 0x3c]
0051a445 andps xmm0, xmmword ptr [0xb6c980]
0051a44c xorps xmm1, xmm1
0051a44f comiss xmm0, xmm1
0051a452 push 0
0051a454 jbe 0x51a460
0051a456 push 0xb43150
0051a45b jmp 0x51a4e3
0051a460 comiss xmm1, dword ptr [esi + 0xb04]
0051a467 jbe 0x51a473
0051a469 push 0xb43160
0051a46e jmp 0x51a512
0051a473 push 0xb431e8
0051a478 jmp 0x51a512
0051a47d mov eax, dword ptr [esi + 0x2c]
0051a480 inc eax
0051a481 push eax
0051a482 push 0xb431f8
0051a487 push 0x40
0051a489 push 0xc04358
0051a48e call 0x418980
0051a493 mov eax, dword ptr [esi + 0x2c]
0051a496 inc eax
0051a497 push eax
0051a498 push 0xb431c8
0051a49d push 0x40
0051a49f push 0xc042d8
0051a4a4 call 0x418980
0051a4a9 mov eax, dword ptr [esi + 0x2c]
0051a4ac inc eax
0051a4ad push eax
0051a4ae push 0xb431d8
0051a4b3 push 0x40
0051a4b5 push 0xc04318
0051a4ba call 0x418980
0051a4bf movss xmm0, dword ptr [esi + 0xb00]
0051a4c7 lea ecx, [esi + 0x3c]
0051a4ca andps xmm0, xmmword ptr [0xb6c980]
0051a4d1 add esp, 0x30
0051a4d4 xorps xmm1, xmm1
0051a4d7 comiss xmm0, xmm1
0051a4da push 0
0051a4dc jbe 0x51a4fd
0051a4de push 0xc04318
0051a4e3 call 0x4054f0
0051a4e8 xorps xmm3, xmm3
0051a4eb comiss xmm3, dword ptr [esi + 0xb00]
0051a4f2 seta al
0051a4f5 mov byte ptr [esi + 0x13c], al
0051a4fb jmp 0x51a517
0051a4fd comiss xmm1, dword ptr [esi + 0xb04]
0051a504 jbe 0x51a50d
0051a506 push 0xc04358
0051a50b jmp 0x51a512
0051a50d push 0xc042d8
0051a512 call 0x4054f0
0051a517 cmp dword ptr [esi + 0xe6c], -1
0051a51e je 0x51ace1
0051a524 cmp dword ptr [esi + 0x70], 0
0051a528 je 0x51ace1
0051a52e movss xmm1, dword ptr [0xb6a940]
0051a536 lea ecx, [esi + 0x6c]
0051a539 call 0x403c00
0051a53e jmp 0x51ace1
0051a543 cmp eax, 8
0051a546 jne 0x51a616
0051a54c push 0
0051a54e push 0xb43220
0051a553 lea ecx, [esi + 0x3c]
0051a556 call 0x4054f0
0051a55b cmp dword ptr [esi + 0x70], 0
0051a55f je 0x51acd7
0051a565 push 0xb400ac
0051a56a lea ecx, [esi + 0x6c]
0051a56d call 0x405e90
0051a572 test al, al
0051a574 je 0x51acc8
0051a57a call 0x6af030
0051a57f test eax, eax
0051a581 jle 0x51a58d
0051a583 movss xmm0, dword ptr [0xb6a98c]
0051a58b jmp 0x51a595
0051a58d movss xmm0, dword ptr [0xb6a940]
0051a595 lea ecx, [ebp - 0x100]
0051a59b movss dword ptr [ebp - 0x10c], xmm0
0051a5a3 mov dword ptr [ebp - 0x108], 0
0051a5ad call 0x430d70
0051a5b2 push eax
0051a5b3 push 8
0051a5b5 lea eax, [ebp - 0x10c]
0051a5bb mov ecx, esi
0051a5bd push eax
0051a5be push edi
0051a5bf call 0x6a1a20
0051a5c4 cmp dword ptr [esi + 0x2c], 1
0051a5c8 jne 0x51ace1
0051a5ce mov ecx, esi
0051a5d0 call 0x695680
0051a5d5 mov ecx, dword ptr [eax + 0x294]
0051a5db mov eax, dword ptr [eax + 0x298]
0051a5e1 mov dword ptr [ebp - 0x10c], ecx
0051a5e7 lea ecx, [ebp - 0x100]
0051a5ed mov dword ptr [ebp - 0x108], eax
0051a5f3 call 0x430d70
0051a5f8 push eax
0051a5f9 push ecx
0051a5fa mov dword ptr [esp], 0
0051a601 lea eax, [ebp - 0x10c]
0051a607 push eax
0051a608 push 5
0051a60a mov ecx, esi
0051a60c call 0x6a3420
0051a611 jmp 0x51ace1
0051a616 cmp eax, 9
0051a619 jne 0x51abcb
0051a61f cmp dword ptr [esi + 0x28], 0x344
0051a626 jne 0x51a778
0051a62c cmp dword ptr [esi + 0xe6c], -1
0051a633 je 0x51a6f4
0051a639 movss xmm2, dword ptr [0xb6ae44]
0051a641 mov ecx, esi
0051a643 push 0
0051a645 call 0x6af8d0
0051a64a lea edi, [esi + 0x28c]
0051a650 push 0xc02fec
0051a655 mov ecx, edi
0051a657 call 0x962c70
0051a65c test al, al
0051a65e je 0x51a67d
0051a660 lea eax, [ebp - 0x120]
0051a666 mov ecx, esi
0051a668 push eax
0051a669 call 0x6afac0
0051a66e mov ecx, dword ptr [eax]
0051a670 mov dword ptr [edi], ecx
0051a672 mov eax, dword ptr [eax + 4]
0051a675 mov dword ptr [edi + 4], eax
0051a678 jmp 0x51a772
0051a67d movss xmm2, dword ptr [esi + 0x2f4]
0051a685 movss xmm3, dword ptr [0xb6a614]
0051a68d movss xmm1, dword ptr [0xb6a5a4]
0051a695 ucomiss xmm2, xmm3
0051a698 lahf 
0051a699 test ah, 0x44
0051a69c jnp 0x51a6b1
0051a69e movaps xmm0, xmm2
0051a6a1 mulss xmm2, xmm1
0051a6a5 addss xmm0, xmm1
0051a6a9 subss xmm0, xmm2
0051a6ad divss xmm1, xmm0
0051a6b1 lea eax, [ebp - 0x120]
0051a6b7 movaps xmm4, xmm3
0051a6ba push eax
0051a6bb mov ecx, esi
0051a6bd subss xmm4, xmm1
0051a6c1 call 0x6afac0
0051a6c6 movss xmm3, dword ptr [eax + 4]
0051a6cb movss xmm0, dword ptr [eax]
0051a6cf subss xmm0, dword ptr [edi]
0051a6d3 subss xmm3, dword ptr [edi + 4]
0051a6d8 mulss xmm0, xmm4
0051a6dc mulss xmm3, xmm4
0051a6e0 addss xmm0, dword ptr [edi]
0051a6e4 addss xmm3, dword ptr [edi + 4]
0051a6e9 movss dword ptr [edi], xmm0
0051a6ed movss dword ptr [edi + 4], xmm3
0051a6f2 jmp 0x51a772
0051a6f4 cmp dword ptr [esi + 0x360], 6
0051a6fb jl 0x51a778
0051a6fd push 0xc02fec
0051a702 lea ecx, [esi + 0x28c]
0051a708 call 0x962c70
0051a70d test al, al
0051a70f je 0x51a772
0051a711 mov ecx, esi
0051a713 call 0x695680
0051a718 lea edi, [esi + 0x31c]
0051a71e mov dword ptr [ebp - 0x110], eax
0051a724 movss xmm0, dword ptr [eax + 0x294]
0051a72c movss xmm1, dword ptr [eax + 0x298]
0051a734 movss dword ptr [esi + 0x28c], xmm0
0051a73c movss dword ptr [esi + 0x290], xmm1
0051a744 mov ecx, dword ptr [edi]
0051a746 test ecx, ecx
0051a748 je 0x51a768
0051a74a lea eax, [ebp - 0x104]
0051a750 mov dword ptr [ebp - 0x104], edi
0051a756 push eax
0051a757 add ecx, 0x324
0051a75d call 0x4bc3c0
0051a762 mov eax, dword ptr [ebp - 0x110]
0051a768 push edi
0051a769 mov ecx, eax
0051a76b mov dword ptr [edi], eax
0051a76d call 0x4bae70
0051a772 lea edi, [esi + 0x294]
0051a778 push 0xb400ac
0051a77d lea ecx, [esi + 0x3c]
0051a780 call 0x4060f0
0051a785 test al, al
0051a787 je 0x51acc8
0051a78d movss xmm4, dword ptr [esi + 0xb04]
0051a795 movss xmm0, dword ptr [0xb6ae20]
0051a79d comiss xmm0, xmm4
0051a7a0 jbe 0x51a7ac
0051a7a2 movss xmm0, dword ptr [0xb6aeb8]
0051a7aa jmp 0x51a7b4
0051a7ac movss xmm0, dword ptr [0xb6ad00]
0051a7b4 movss xmm1, dword ptr [esi + 0xb00]
0051a7bc lea eax, [ebp - 0x10c]
0051a7c2 movss xmm2, dword ptr [edi + 4]
0051a7c7 xorps xmm3, xmm3
0051a7ca movss dword ptr [ebp - 0x104], xmm0
0051a7d2 addss xmm2, xmm3
0051a7d6 movaps xmm0, xmm1
0051a7d9 mov dword ptr [ebp - 0x10c], 0
0051a7e3 mulss xmm0, dword ptr [0xb6a910]
0051a7eb push 0
0051a7ed push esi
0051a7ee push eax
0051a7ef addss xmm0, dword ptr [edi]
0051a7f3 push 0x20
0051a7f5 mov dword ptr [ebp - 0x108], 0xc1a00000
0051a7ff movss dword ptr [ebp - 0x114], xmm2
0051a807 movss dword ptr [ebp - 0x118], xmm0
0051a80f movaps xmm0, xmm4
0051a812 call 0x447a80
0051a817 mulss xmm0, dword ptr [0xb6aa84]
0051a81f lea eax, [ebp - 0x118]
0051a825 push ecx
0051a826 movss dword ptr [esp], xmm0
0051a82b push eax
0051a82c push 1
0051a82e call 0x8c7550
0051a833 movss xmm0, dword ptr [ebp - 0x104]
0051a83b mov edi, eax
0051a83d add esp, 0x1c
0051a840 movss dword ptr [edi + 0x2b0], xmm0
0051a848 cmp dword ptr [esi + 0x28], 0x344
0051a84f jne 0x51a8e3
0051a855 mov ecx, dword ptr [esi + 0x318]
0051a85b lea eax, [esi + 0x318]
0051a861 test ecx, ecx
0051a863 je 0x51a883
0051a865 mov dword ptr [ebp - 0x104], eax
0051a86b add ecx, 0x324
0051a871 lea eax, [ebp - 0x104]
0051a877 push eax
0051a878 call 0x4bc3c0
0051a87d lea eax, [esi + 0x318]
0051a883 push eax
0051a884 mov ecx, edi
0051a886 mov dword ptr [eax], edi
0051a888 call 0x4bae70
0051a88d movss xmm0, dword ptr [esi + 0x28c]
0051a895 movss xmm1, dword ptr [esi + 0x290]
0051a89d push ecx
0051a89e mov ecx, dword ptr [0xbfd65c]
0051a8a4 movss dword ptr [edi + 0x28c], xmm0
0051a8ac movss dword ptr [edi + 0x290], xmm1
0051a8b4 call 0x706110
0051a8b9 cmp eax, 0x20
0051a8bc je 0x51a8d5
0051a8be mov eax, dword ptr [edi]
0051a8c0 mov ecx, edi
0051a8c2 push 1
0051a8c4 push 0
0051a8c6 push 0xff
0051a8cb push -1
0051a8cd push 0xbc51d0
0051a8d2 call dword ptr [eax + 0x38]
0051a8d5 movups xmm0, xmmword ptr [0xbc4c00]
0051a8dc movups xmmword ptr [edi + 0x378], xmm0
0051a8e3 mov eax, dword ptr [edi]
0051a8e5 mov ecx, edi
0051a8e7 call dword ptr [eax + 0xc]
0051a8ea mov eax, dword ptr [esi + 0x28]
0051a8ed movss xmm2, dword ptr [0xb6c9b0]
0051a8f5 cmp eax, 0x27
0051a8f8 jne 0x51a90c
0051a8fa mov eax, dword ptr [esi + 0x2c]
0051a8fd cmp eax, 1
0051a900 je 0x51a91f
0051a902 cmp eax, 3
0051a905 je 0x51a91f
0051a907 jmp 0x51aa02
0051a90c cmp eax, 0x31
0051a90f jne 0x51a9f9
0051a915 cmp dword ptr [esi + 0x2c], 1
0051a919 jne 0x51ace1
0051a91f movss xmm1, dword ptr [esi + 0xb00]
0051a927 movss xmm0, dword ptr [esi + 0xb04]
0051a92f xorps xmm1, xmm2
0051a932 xorps xmm0, xmm2
0051a935 mov dword ptr [ebp - 0x10c], 0
0051a93f mov dword ptr [ebp - 0x108], 0xc1a00000
0051a949 movss dword ptr [ebp - 0x104], xmm1
0051a951 call 0x447a80
0051a956 movss xmm1, dword ptr [esi + 0x298]
0051a95e lea eax, [ebp - 0x10c]
0051a964 addss xmm1, dword ptr [0xb6a18c]
0051a96c push 0
0051a96e movaps xmm2, xmm0
0051a971 movss xmm0, dword ptr [ebp - 0x104]
0051a979 mulss xmm0, dword ptr [0xb6a910]
0051a981 push esi
0051a982 mulss xmm2, dword ptr [0xb6aa84]
0051a98a push eax
0051a98b addss xmm0, dword ptr [esi + 0x294]
0051a993 push 0x20
0051a995 push ecx
0051a996 movss dword ptr [esp], xmm2
0051a99b lea eax, [ebp - 0x118]
0051a9a1 push eax
0051a9a2 push 1
0051a9a4 movss dword ptr [ebp - 0x118], xmm0
0051a9ac movss dword ptr [ebp - 0x114], xmm1
0051a9b4 call 0x8c7550
0051a9b9 movss xmm0, dword ptr [0xb6ae20]
0051a9c1 add esp, 0x1c
0051a9c4 comiss xmm0, dword ptr [esi + 0xb04]
0051a9cb mov ecx, eax
0051a9cd jbe 0x51a9d9
0051a9cf movss xmm0, dword ptr [0xb6ad00]
0051a9d7 jmp 0x51a9e1
0051a9d9 movss xmm0, dword ptr [0xb6aeb8]
0051a9e1 mov eax, dword ptr [ecx]
0051a9e3 movss dword ptr [ecx + 0x2b0], xmm0
0051a9eb call dword ptr [eax + 0xc]
0051a9ee mov eax, dword ptr [esi + 0x28]
0051a9f1 movss xmm2, dword ptr [0xb6c9b0]
0051a9f9 cmp eax, 0x27
0051a9fc jne 0x51ace1
0051aa02 cmp dword ptr [esi + 0x2c], 3
0051aa06 jne 0x51ace1
0051aa0c movss xmm0, dword ptr [esi + 0xb00]
0051aa14 movss xmm1, dword ptr [esi + 0xb04]
0051aa1c xorps xmm0, xmm2
0051aa1f mov dword ptr [ebp - 0x10c], 0
0051aa29 mov dword ptr [ebp - 0x108], 0xc1a00000
0051aa33 call 0x447a80
0051aa38 movss xmm1, dword ptr [esi + 0x294]
0051aa40 lea eax, [ebp - 0x10c]
0051aa46 movaps xmm2, xmm0
0051aa49 movss xmm0, dword ptr [esi + 0xb04]
0051aa51 mulss xmm0, dword ptr [0xb6a910]
0051aa59 push 0
0051aa5b mulss xmm2, dword ptr [0xb6aa84]
0051aa63 push esi
0051aa64 subss xmm1, xmm0
0051aa68 push eax
0051aa69 push 0x20
0051aa6b push ecx
0051aa6c movss dword ptr [esp], xmm2
0051aa71 lea eax, [ebp - 0x118]
0051aa77 movss dword ptr [ebp - 0x118], xmm1
0051aa7f movss xmm1, dword ptr [esi + 0x298]
0051aa87 addss xmm1, dword ptr [0xb6a18c]
0051aa8f push eax
0051aa90 push 1
0051aa92 movss dword ptr [ebp - 0x114], xmm1
0051aa9a call 0x8c7550
0051aa9f movss xmm0, dword ptr [0xb6ae20]
0051aaa7 add esp, 0x1c
0051aaaa comiss xmm0, dword ptr [esi + 0xb04]
0051aab1 mov ecx, eax
0051aab3 ja 0x51aad0
0051aab5 movss xmm0, dword ptr [esi + 0xb00]
0051aabd comiss xmm0, dword ptr [0xb6a480]
0051aac4 ja 0x51aad0
0051aac6 movss xmm0, dword ptr [0xb6ad00]
0051aace jmp 0x51aad8
0051aad0 movss xmm0, dword ptr [0xb6aeb8]
0051aad8 mov eax, dword ptr [ecx]
0051aada movss dword ptr [ecx + 0x2b0], xmm0
0051aae2 call dword ptr [eax + 0xc]
0051aae5 movss xmm1, dword ptr [esi + 0xb04]
0051aaed xorps xmm1, xmmword ptr [0xb6c9b0]
0051aaf4 movss xmm0, dword ptr [esi + 0xb00]
0051aafc mov dword ptr [ebp - 0x10c], 0
0051ab06 mov dword ptr [ebp - 0x108], 0xc1a00000
0051ab10 call 0x447a80
0051ab15 movss xmm1, dword ptr [esi + 0x298]
0051ab1d lea eax, [ebp - 0x10c]
0051ab23 addss xmm1, dword ptr [0xb6a18c]
0051ab2b push 0
0051ab2d movaps xmm2, xmm0
0051ab30 movss xmm0, dword ptr [esi + 0xb04]
0051ab38 mulss xmm0, dword ptr [0xb6a910]
0051ab40 push esi
0051ab41 mulss xmm2, dword ptr [0xb6aa84]
0051ab49 push eax
0051ab4a addss xmm0, dword ptr [esi + 0x294]
0051ab52 push 0x20
0051ab54 push ecx
0051ab55 movss dword ptr [esp], xmm2
0051ab5a lea eax, [ebp - 0x118]
0051ab60 push eax
0051ab61 push 1
0051ab63 movss dword ptr [ebp - 0x118], xmm0
0051ab6b movss dword ptr [ebp - 0x114], xmm1
0051ab73 call 0x8c7550
0051ab78 movss xmm0, dword ptr [0xb6ae20]
0051ab80 add esp, 0x1c
0051ab83 comiss xmm0, dword ptr [esi + 0xb04]
0051ab8a mov ecx, eax
0051ab8c ja 0x51abb1
0051ab8e comiss xmm0, dword ptr [esi + 0xb00]
0051ab95 ja 0x51abb1
0051ab97 mov eax, dword ptr [ecx]
0051ab99 movss xmm0, dword ptr [0xb6ad00]
0051aba1 movss dword ptr [ecx + 0x2b0], xmm0
0051aba9 call dword ptr [eax + 0xc]
0051abac jmp 0x51ace1
0051abb1 mov eax, dword ptr [ecx]
0051abb3 movss xmm0, dword ptr [0xb6aeb8]
0051abbb movss dword ptr [ecx + 0x2b0], xmm0
0051abc3 call dword ptr [eax + 0xc]
0051abc6 jmp 0x51ace1
0051abcb cmp eax, 0xa
0051abce jne 0x51ace1
0051abd4 push 0xb400ac
0051abd9 lea ecx, [esi + 0x3c]
0051abdc call 0x4060f0
0051abe1 test al, al
0051abe3 je 0x51acc8
0051abe9 movss xmm0, dword ptr [esi + 0xb04]
0051abf1 mulss xmm0, dword ptr [0xb6a9b0]
0051abf9 movss dword ptr [ebp - 0x108], xmm0
0051ac01 movss xmm0, dword ptr [esi + 0xb00]
0051ac09 mulss xmm0, dword ptr [0xb6a9b0]
0051ac11 mulss xmm0, dword ptr [0xb6a6c8]
0051ac19 movss dword ptr [ebp - 0x10c], xmm0
0051ac21 call 0x6c3d90
0051ac26 mov ecx, dword ptr [0xbfd65c]
0051ac2c push 0
0051ac2e push 0xbeab70
0051ac33 push 0xbeab18
0051ac38 push 0
0051ac3a push eax
0051ac3b push 0
0051ac3d push esi
0051ac3e lea eax, [ebp - 0x10c]
0051ac44 push eax
0051ac45 push edi
0051ac46 push 0x16
0051ac48 push dword ptr [esi + 0x28]
0051ac4b call 0x422e20
0051ac50 push eax
0051ac51 call 0x9ec34c
0051ac56 add esp, 0x14
0051ac59 mov edi, eax
0051ac5b mov ecx, edi
0051ac5d push esi
0051ac5e mov dword ptr [edi + 0xab4], 0
0051ac68 call 0x6818e0
0051ac6d movss xmm2, dword ptr [esi + 0xb00]
0051ac75 movss xmm0, dword ptr [esi + 0xb04]
0051ac7d andps xmm2, xmmword ptr [0xb6c980]
0051ac84 andps xmm0, xmmword ptr [0xb6c980]
0051ac8b comiss xmm2, xmm0
0051ac8e jbe 0x51acbf
0051ac90 movss xmm0, dword ptr [edi + 0x294]
0051ac98 xorps xmm3, xmm3
0051ac9b movss xmm1, dword ptr [edi + 0x298]
0051aca3 addss xmm0, xmm3
0051aca7 addss xmm1, dword ptr [0xb6a2cc]
0051acaf movss dword ptr [edi + 0x294], xmm0
0051acb7 movss dword ptr [edi + 0x298], xmm1
0051acbf mov eax, dword ptr [edi]
0051acc1 mov ecx, edi
0051acc3 call dword ptr [eax + 0xc]
0051acc6 jmp 0x51ace1
0051acc8 cmp dword ptr [esi + 0x70], 0
0051accc je 0x51acd7
0051acce cmp byte ptr [esi + 0x80], 0
0051acd5 jne 0x51ace1
0051acd7 mov dword ptr [esi + 0xab4], 4
0051ace1 cmp dword ptr [esi + 0x28], 0x344
0051ace8 jne 0x51af46
0051acee mov eax, dword ptr [esi + 0x318]
0051acf4 test eax, eax
0051acf6 je 0x51acfe
0051acf8 cmp dword ptr [eax + 0x28], 7
0051acfc je 0x51ad0b
0051acfe cmp dword ptr [esi + 0xab4], 9
0051ad05 jne 0x51af10
0051ad0b mov ecx, dword ptr [esi + 0x31c]
0051ad11 test ecx, ecx
0051ad13 jne 0x51ad38
0051ad15 cmp dword ptr [esi + 0xe6c], -1
0051ad1c je 0x51aede
0051ad22 mov edi, dword ptr [esi + 0xe6c]
0051ad28 lea eax, [ebp - 0x120]
0051ad2e push eax
0051ad2f mov ecx, esi
0051ad31 call 0x6afac0
0051ad36 jmp 0x51ad71
0051ad38 mov edi, dword ptr [esi + 0xe6c]
0051ad3e cmp edi, -1
0051ad41 je 0x51ad53
0051ad43 lea eax, [ebp - 0x120]
0051ad49 mov ecx, esi
0051ad4b push eax
0051ad4c call 0x6afac0
0051ad51 jmp 0x51ad71
0051ad53 mov eax, dword ptr [ecx + 0x294]
0051ad59 mov ecx, dword ptr [ecx + 0x298]
0051ad5f mov dword ptr [ebp - 0x10c], eax
0051ad65 lea eax, [ebp - 0x10c]
0051ad6b mov dword ptr [ebp - 0x108], ecx
0051ad71 movss xmm0, dword ptr [eax]
0051ad75 movss xmm1, dword ptr [esi + 0x28c]
0051ad7d movss xmm3, dword ptr [eax + 4]
0051ad82 movss xmm2, dword ptr [esi + 0x290]
0051ad8a movss dword ptr [ebp - 0x128], xmm0
0051ad92 subss xmm0, xmm1
0051ad96 movss dword ptr [ebp - 0x114], xmm3
0051ad9e movss dword ptr [ebp - 0x108], xmm1
0051ada6 movss dword ptr [ebp - 0x124], xmm0
0051adae movss dword ptr [ebp - 0x120], xmm0
0051adb6 movaps xmm0, xmm3
0051adb9 subss xmm0, xmm2
0051adbd movss dword ptr [ebp - 0x104], xmm0
0051adc5 movss dword ptr [ebp - 0x11c], xmm0
0051adcd movss xmm0, dword ptr [0xb6a7b0]
0051add5 movss dword ptr [ebp - 0x110], xmm0
0051addd cmp edi, -1
0051ade0 je 0x51adf2
0051ade2 movss xmm0, dword ptr [0xb6a434]
0051adea movss dword ptr [ebp - 0x110], xmm0
0051adf2 subss xmm2, dword ptr [esi + 0x298]
0051adfa movaps xmm0, xmm1
0051adfd lea eax, [ebp - 0x1c]
0051ae00 subss xmm0, dword ptr [esi + 0x294]
0051ae08 push eax
0051ae09 lea ecx, [ebp - 0x130]
0051ae0f movss dword ptr [ebp - 0x12c], xmm2
0051ae17 movss dword ptr [ebp - 0x130], xmm0
0051ae1f call 0x962560
0051ae24 movss xmm0, dword ptr [esi + 0xb00]
0051ae2c movss xmm2, dword ptr [ebp - 0x110]
0051ae34 movss xmm1, dword ptr [eax + 4]
0051ae39 mulss xmm0, dword ptr [eax]
0051ae3d mulss xmm1, dword ptr [esi + 0xb04]
0051ae45 addss xmm1, xmm0
0051ae49 xorps xmm0, xmm0
0051ae4c comiss xmm0, xmm1
0051ae4f jbe 0x51ae5d
0051ae51 addss xmm1, dword ptr [0xb6a614]
0051ae59 mulss xmm2, xmm1
0051ae5d movss xmm0, dword ptr [ebp - 0x124]
0051ae65 movss xmm1, dword ptr [ebp - 0x104]
0051ae6d mulss xmm0, xmm0
0051ae71 mulss xmm1, xmm1
0051ae75 addss xmm1, xmm0
0051ae79 movss xmm0, dword ptr [0xb6a214]
0051ae81 comiss xmm0, xmm1
0051ae84 jb 0x51aea0
0051ae86 movss xmm0, dword ptr [ebp - 0x128]
0051ae8e movss dword ptr [esi + 0x28c], xmm0
0051ae96 movss xmm0, dword ptr [ebp - 0x114]
0051ae9e jmp 0x51aed6
0051aea0 push ecx
0051aea1 lea eax, [ebp - 0x1c]
0051aea4 movss dword ptr [esp], xmm2
0051aea9 push eax
0051aeaa lea ecx, [ebp - 0x120]
0051aeb0 call 0x9628d0
0051aeb5 movss xmm0, dword ptr [ebp - 0x108]
0051aebd addss xmm0, dword ptr [eax]
0051aec1 movss dword ptr [esi + 0x28c], xmm0
0051aec9 movss xmm0, dword ptr [eax + 4]
0051aece addss xmm0, dword ptr [esi + 0x290]
0051aed6 movss dword ptr [esi + 0x290], xmm0
0051aede mov eax, dword ptr [esi + 0x318]
0051aee4 test eax, eax
0051aee6 je 0x51af46
0051aee8 cmp dword ptr [eax + 0x28], 7
0051aeec jne 0x51af46
0051aeee movss xmm0, dword ptr [esi + 0x28c]
0051aef6 movss xmm1, dword ptr [esi + 0x290]
0051aefe movss dword ptr [eax + 0x28c], xmm0
0051af06 movss dword ptr [eax + 0x290], xmm1
0051af0e jmp 0x51af46
0051af10 lea ecx, [esi + 0x28c]
0051af16 push 0xc02fec
0051af1b call 0x962ca0
0051af20 test al, al
0051af22 je 0x51af46
0051af24 movss xmm0, dword ptr [0xc02fec]
0051af2c movss dword ptr [ecx], xmm0
0051af30 movss xmm0, dword ptr [0xc02ff0]
0051af38 movss dword ptr [ecx + 4], xmm0
0051af3d mov ecx, esi
0051af3f push 0
0051af41 call 0x681960
0051af46 cvttss2si ecx, dword ptr [esi + 0x2fc]
0051af4e cvttss2si eax, dword ptr [esi + 0x2f8]
0051af56 movss xmm0, dword ptr [esi + 0x2c4]
0051af5e mulss xmm0, dword ptr [0xb6a560]
0051af66 sub ecx, eax
0051af68 add dword ptr [esi + 0x360], ecx
0051af6e movss dword ptr [esi + 0x2c4], xmm0
0051af76 mov ecx, dword ptr [ebp - 0xc]
0051af79 mov dword ptr fs:[0], ecx
0051af80 pop ecx
0051af81 pop edi
0051af82 pop esi
0051af83 mov ecx, dword ptr [ebp - 0x14]
0051af86 xor ecx, ebp
0051af88 call 0x9eacd7
0051af8d mov esp, ebp
0051af8f pop ebp
0051af90 mov esp, ebx
0051af92 pop ebx
0051af93 ret 
