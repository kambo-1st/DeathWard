0064dcd0 push ebp
0064dcd1 mov ebp, esp
0064dcd3 push -1
0064dcd5 push 0x9f1f10
0064dcda mov eax, dword ptr fs:[0]
0064dce0 push eax
0064dce1 sub esp, 0x1a0
0064dce7 mov eax, dword ptr [0xbaa3b4]
0064dcec xor eax, ebp
0064dcee mov dword ptr [ebp - 0x10], eax
0064dcf1 push esi
0064dcf2 push edi
0064dcf3 push eax
0064dcf4 lea eax, [ebp - 0xc]
0064dcf7 mov dword ptr fs:[0], eax
0064dcfd mov edi, ecx
0064dcff mov dword ptr [ebp - 0xf0], edi
0064dd05 push dword ptr [ebp + 0xc]
0064dd08 mov esi, dword ptr [ebp + 8]
0064dd0b push esi
0064dd0c push edi
0064dd0d mov dword ptr [ebp - 0xb8], esi
0064dd13 call 0x7ff420
0064dd18 cmp eax, 1
0064dd1b je 0x64dde9
0064dd21 cmp eax, -1
0064dd24 je 0x6500c5
0064dd2a lea edx, [edi + 0x378]
0064dd30 push 0xbc4ca0
0064dd35 lea ecx, [ebp - 0xec]
0064dd3b call 0x412050
0064dd40 add esp, 4
0064dd43 mov ecx, dword ptr [eax]
0064dd45 or ecx, dword ptr [eax + 4]
0064dd48 jne 0x64dd52
0064dd4a mov ecx, dword ptr [eax + 8]
0064dd4d or ecx, dword ptr [eax + 0xc]
0064dd50 je 0x64dd81
0064dd52 push 0xbc4ce0
0064dd57 lea edx, [edi + 0x378]
0064dd5d lea ecx, [ebp - 0xdc]
0064dd63 call 0x412050
0064dd68 add esp, 4
0064dd6b mov ecx, dword ptr [eax]
0064dd6d or ecx, dword ptr [eax + 4]
0064dd70 jne 0x64dd81
0064dd72 mov ecx, dword ptr [eax + 8]
0064dd75 or ecx, dword ptr [eax + 0xc]
0064dd78 mov byte ptr [ebp - 0xb1], 1
0064dd7f je 0x64dd88
0064dd81 mov byte ptr [ebp - 0xb1], 0
0064dd88 cmp byte ptr [ebp + 0xc], 0
0064dd8c je 0x6500c5
0064dd92 cmp byte ptr [edi + 0x16b], 0
0064dd99 jne 0x6500c5
0064dd9f mov eax, dword ptr [edi + 0x320]
0064dda5 mov dword ptr [ebp - 0xac], eax
0064ddab test eax, eax
0064ddad je 0x64ddb5
0064ddaf cmp dword ptr [eax + 0x28], 1
0064ddb3 je 0x64ddbf
0064ddb5 mov dword ptr [ebp - 0xac], 0
0064ddbf mov ecx, dword ptr [esi + 0x28]
0064ddc2 cmp ecx, 0x362
0064ddc8 je 0x64dde9
0064ddca cmp ecx, 0xa
0064ddcd jl 0x64de08
0064ddcf cmp ecx, 0x3e8
0064ddd5 jge 0x64de1b
0064ddd7 push 0
0064ddd9 push 0x20000000
0064ddde mov ecx, esi
0064dde0 call 0x4122f0
0064dde5 test al, al
0064dde7 je 0x64de18
0064dde9 mov al, 1
0064ddeb mov ecx, dword ptr [ebp - 0xc]
0064ddee mov dword ptr fs:[0], ecx
0064ddf5 pop ecx
0064ddf6 pop edi
0064ddf7 pop esi
0064ddf8 mov ecx, dword ptr [ebp - 0x10]
0064ddfb xor ecx, ebp
0064ddfd call 0x9eacd7
0064de02 mov esp, ebp
0064de04 pop ebp
0064de05 ret 8
0064de08 cmp ecx, 4
0064de0b jne 0x64de1b
0064de0d mov ecx, esi
0064de0f call 0x67ab80
0064de14 test al, al
0064de16 jne 0x64dde9
0064de18 mov ecx, dword ptr [esi + 0x28]
0064de1b cmp dword ptr [edi + 0x2c], 9
0064de1f jne 0x64deb1
0064de25 cmp ecx, 0x3c0
0064de2b je 0x64dde9
0064de2d cmp ecx, 0x3b6
0064de33 jne 0x64de3d
0064de35 cmp dword ptr [esi + 0x2c], 0
0064de39 jne 0x64de91
0064de3b jmp 0x64dde9
0064de3d cmp ecx, 0x3b7
0064de43 je 0x64de35
0064de45 cmp ecx, 0x19c
0064de4b jne 0x64de87
0064de4d mov eax, dword ptr [edi]
0064de4f mov ecx, edi
0064de51 call dword ptr [eax + 0x28]
0064de54 mov ecx, dword ptr [esi + 0xb30]
0064de5a mov eax, dword ptr [esi + 0xb34]
0064de60 and ecx, 0xffff807f
0064de66 or ecx, 0x7f80
0064de6c mov dword ptr [ebp - 0xe0], eax
0064de72 mov dword ptr [esi + 0xb30], ecx
0064de78 mov dword ptr [esi + 0xb34], 0
0064de82 jmp 0x64dde9
0064de87 lea eax, [ecx - 0xa]
0064de8a cmp eax, 0x3dd
0064de8f ja 0x64deb1
0064de91 mov eax, dword ptr [esi]
0064de93 mov ecx, esi
0064de95 call dword ptr [eax + 0x24]
0064de98 cmp dword ptr [esi + 0x28], 0x38b
0064de9f jne 0x64dde9
0064dea5 mov eax, dword ptr [edi]
0064dea7 mov ecx, edi
0064dea9 call dword ptr [eax + 0x28]
0064deac jmp 0x64dde9
0064deb1 cmp ecx, 0x197
0064deb7 jne 0x64decb
0064deb9 cmp byte ptr [esi + 0x308], 0
0064dec0 je 0x64dfd0
0064dec6 jmp 0x64dde9
0064decb cmp ecx, 4
0064dece jne 0x64dfd0
0064ded4 push 0xbc4820
0064ded9 lea edx, [edi + 0x378]
0064dedf lea ecx, [ebp - 0xec]
0064dee5 call 0x412050
0064deea add esp, 4
0064deed mov ecx, eax
0064deef call 0x412090
0064def4 test al, al
0064def6 jne 0x64dde9
0064defc push 0xbc47f0
0064df01 lea edx, [edi + 0x378]
0064df07 lea ecx, [ebp - 0xec]
0064df0d call 0x412050
0064df12 add esp, 4
0064df15 mov ecx, eax
0064df17 call 0x412090
0064df1c test al, al
0064df1e jne 0x64dde9
0064df24 movss xmm0, dword ptr [esi + 0x294]
0064df2c movss xmm1, dword ptr [esi + 0x298]
0064df34 subss xmm0, dword ptr [edi + 0x294]
0064df3c subss xmm1, dword ptr [edi + 0x298]
0064df44 mulss xmm0, dword ptr [edi + 0x2b8]
0064df4c mulss xmm1, dword ptr [edi + 0x2bc]
0064df54 addss xmm1, xmm0
0064df58 xorps xmm0, xmm0
0064df5b comiss xmm0, xmm1
0064df5e jbe 0x64df7a
0064df60 mov eax, dword ptr [0xbfd65c]
0064df65 mov eax, dword ptr [eax + 0x1a30dc]
0064df6b sub eax, dword ptr [edi + 0x280]
0064df71 cmp eax, 3
0064df74 jl 0x64dde9
0064df7a push 0
0064df7c push 0xbeacac
0064df81 push 0xbeab18
0064df86 push 0
0064df88 push esi
0064df89 call 0x9ec34c
0064df8e add esp, 0x14
0064df91 test eax, eax
0064df93 je 0x64dfd0
0064df95 cmp byte ptr [eax + 0x398], 0
0064df9c je 0x64dfd0
0064df9e cmp dword ptr [edi + 0x34], 1
0064dfa2 jne 0x64dde9
0064dfa8 push 0xbc48a0
0064dfad lea edx, [edi + 0x378]
0064dfb3 lea ecx, [ebp - 0xec]
0064dfb9 call 0x412050
0064dfbe add esp, 4
0064dfc1 mov ecx, eax
0064dfc3 call 0x412090
0064dfc8 test al, al
0064dfca jne 0x64dde9
0064dfd0 mov eax, dword ptr [esi + 0x28]
0064dfd3 cmp eax, 0x123
0064dfd8 je 0x64dde9
0064dfde cmp eax, 0x19b
0064dfe3 jne 0x64e10d
0064dfe9 cmp byte ptr [esi + 0x308], 0
0064dff0 jne 0x64dde9
0064dff6 cmp byte ptr [ebp - 0xb1], 0
0064dffd jne 0x64e3a7
0064e003 cmp eax, 0x336
0064e008 jne 0x64e3a7
0064e00e cmp dword ptr [esi + 0xab4], 0x10
0064e015 jne 0x64e3a7
0064e01b mov eax, dword ptr [esi + 0x344]
0064e021 lea ecx, [ebp - 0xec]
0064e027 add eax, dword ptr [edi + 0x344]
0064e02d movq xmm0, qword ptr [0xa08c44]
0064e035 mov dword ptr [ebp - 0xec], eax
0064e03b mov eax, dword ptr [0xa08c4c]
0064e040 push 5
0064e042 movq qword ptr [ebp - 0xe8], xmm0
0064e04a mov dword ptr [ebp - 0xe0], eax
0064e050 call 0x7a7d50
0064e055 test eax, eax
0064e057 jne 0x64e3a7
0064e05d movss xmm0, dword ptr [edi + 0x294]
0064e065 lea eax, [ebp - 0xf4]
0064e06b subss xmm0, dword ptr [esi + 0x294]
0064e073 push eax
0064e074 lea ecx, [ebp - 0xd4]
0064e07a movss dword ptr [ebp - 0xd4], xmm0
0064e082 movss xmm0, dword ptr [edi + 0x298]
0064e08a subss xmm0, dword ptr [esi + 0x298]
0064e092 movss dword ptr [ebp - 0xd0], xmm0
0064e09a call 0x962560
0064e09f movss xmm2, dword ptr [edi + 0x2b8]
0064e0a7 movss xmm3, dword ptr [ebp - 0xf0]
0064e0af movaps xmm0, xmm2
0064e0b2 movss xmm4, dword ptr [ebp - 0xf4]
0064e0ba movaps xmm1, xmm3
0064e0bd mulss xmm1, dword ptr [edi + 0x2bc]
0064e0c5 mulss xmm0, xmm4
0064e0c9 addss xmm1, xmm0
0064e0cd xorps xmm0, xmm0
0064e0d0 comiss xmm0, xmm1
0064e0d3 jbe 0x64dde9
0064e0d9 addss xmm1, xmm1
0064e0dd movaps xmm0, xmm1
0064e0e0 mulss xmm1, xmm3
0064e0e4 mulss xmm0, xmm4
0064e0e8 subss xmm2, xmm0
0064e0ec movss xmm0, dword ptr [edi + 0x2bc]
0064e0f4 subss xmm0, xmm1
0064e0f8 movss dword ptr [edi + 0x2b8], xmm2
0064e100 movss dword ptr [edi + 0x2bc], xmm0
0064e108 jmp 0x64dde9
0064e10d cmp eax, 3
0064e110 jne 0x64dff6
0064e116 cmp dword ptr [esi + 0x2c], 0xef
0064e11d jne 0x64dff6
0064e123 lea ecx, [edi + 0x394]
0064e129 push esi
0064e12a call 0x422d00
0064e12f test al, al
0064e131 jne 0x64dde9
0064e137 mov ecx, esi
0064e139 call 0x68d5a0
0064e13e push eax
0064e13f lea ecx, [edi + 0x394]
0064e145 call 0x422c30
0064e14a movss xmm1, dword ptr [esi + 0x298]
0064e152 subss xmm1, dword ptr [edi + 0x298]
0064e15a movss xmm2, dword ptr [esi + 0x294]
0064e162 subss xmm2, dword ptr [edi + 0x294]
0064e16a movaps xmm0, xmm1
0064e16d movss dword ptr [ebp - 0xa8], xmm1
0064e175 mulss xmm0, xmm1
0064e179 movss dword ptr [ebp - 0xd0], xmm1
0064e181 movaps xmm1, xmm2
0064e184 mulss xmm1, xmm2
0064e188 movss dword ptr [ebp - 0xac], xmm2
0064e190 movss dword ptr [ebp - 0xd4], xmm2
0064e198 addss xmm0, xmm1
0064e19c call 0x4228c0
0064e1a1 comiss xmm0, dword ptr [0xb6a1b8]
0064e1a8 movss dword ptr [ebp - 0xf8], xmm0
0064e1b0 jb 0x64dde9
0064e1b6 movss xmm0, dword ptr [edi + 0x2bc]
0064e1be subss xmm0, dword ptr [esi + 0x2bc]
0064e1c6 movss xmm1, dword ptr [edi + 0x2b8]
0064e1ce subss xmm1, dword ptr [esi + 0x2b8]
0064e1d6 movaps xmm2, xmm0
0064e1d9 movss dword ptr [ebp - 0xf0], xmm0
0064e1e1 mulss xmm2, xmm0
0064e1e5 movss dword ptr [ebp - 0x108], xmm0
0064e1ed movaps xmm0, xmm1
0064e1f0 mulss xmm0, xmm1
0064e1f4 movss dword ptr [ebp - 0xb0], xmm1
0064e1fc movss dword ptr [ebp - 0x10c], xmm1
0064e204 addss xmm2, xmm0
0064e208 movaps xmm0, xmm2
0064e20b movss dword ptr [ebp - 0x118], xmm2
0064e213 call 0x4228c0
0064e218 movss xmm1, dword ptr [esi + 0x2c8]
0064e220 addss xmm1, dword ptr [edi + 0x2c8]
0064e228 mulss xmm1, dword ptr [0xb6a480]
0064e230 comiss xmm0, xmm1
0064e233 jbe 0x64e305
0064e239 movss xmm1, dword ptr [ebp - 0xb0]
0064e241 movss xmm0, dword ptr [ebp - 0xf0]
0064e249 mulss xmm1, dword ptr [ebp - 0xac]
0064e251 mulss xmm0, dword ptr [ebp - 0xa8]
0064e259 addss xmm0, xmm1
0064e25d xorps xmm1, xmm1
0064e260 comiss xmm1, xmm0
0064e263 jbe 0x64e305
0064e269 lea eax, [ebp - 0xe4]
0064e26f push eax
0064e270 lea ecx, [ebp - 0xd4]
0064e276 call 0x962560
0064e27b mov esi, eax
0064e27d lea ecx, [ebp - 0x10c]
0064e283 lea eax, [ebp - 0xd4]
0064e289 push eax
0064e28a call 0x962560
0064e28f movss xmm0, dword ptr [esi]
0064e293 movss xmm2, dword ptr [ebp - 0xac]
0064e29b mulss xmm0, dword ptr [eax]
0064e29f movss xmm1, dword ptr [eax + 4]
0064e2a4 mulss xmm1, dword ptr [esi + 4]
0064e2a9 addss xmm1, xmm0
0064e2ad movaps xmm0, xmm1
0064e2b0 mulss xmm1, dword ptr [ebp - 0xa8]
0064e2b8 mulss xmm0, xmm2
0064e2bc addss xmm1, xmm1
0064e2c0 addss xmm0, xmm0
0064e2c4 addss xmm1, dword ptr [ebp - 0xa8]
0064e2cc addss xmm2, xmm0
0064e2d0 movaps xmm0, xmm1
0064e2d3 movss dword ptr [ebp - 0xa8], xmm1
0064e2db mulss xmm0, xmm1
0064e2df movaps xmm1, xmm2
0064e2e2 movss dword ptr [ebp - 0xac], xmm2
0064e2ea mulss xmm1, xmm2
0064e2ee addss xmm0, xmm1
0064e2f2 call 0x4228c0
0064e2f7 mov esi, dword ptr [ebp - 0xb8]
0064e2fd movss dword ptr [ebp - 0xf8], xmm0
0064e305 push esi
0064e306 mov ecx, edi
0064e308 call 0x689640
0064e30d mulss xmm0, dword ptr [0xb6a2cc]
0064e315 mov ecx, esi
0064e317 push edi
0064e318 movss dword ptr [ebp - 0xb8], xmm0
0064e320 call 0x689640
0064e325 movss xmm1, dword ptr [ebp - 0xb8]
0064e32d addss xmm0, xmm1
0064e331 divss xmm1, xmm0
0064e335 movss xmm0, dword ptr [ebp - 0x118]
0064e33d movss dword ptr [ebp - 0xb8], xmm1
0064e345 call 0x4228c0
0064e34a movss xmm2, dword ptr [ebp - 0xac]
0064e352 divss xmm2, dword ptr [ebp - 0xf8]
0064e35a mulss xmm2, xmm0
0064e35e mulss xmm2, dword ptr [ebp - 0xb8]
0064e366 addss xmm2, dword ptr [esi + 0x2b8]
0064e36e movss dword ptr [esi + 0x2b8], xmm2
0064e376 movss xmm2, dword ptr [ebp - 0xa8]
0064e37e divss xmm2, dword ptr [ebp - 0xf8]
0064e386 mulss xmm2, xmm0
0064e38a mulss xmm2, dword ptr [ebp - 0xb8]
0064e392 addss xmm2, dword ptr [esi + 0x2bc]
0064e39a movss dword ptr [esi + 0x2bc], xmm2
0064e3a2 jmp 0x64dde9
0064e3a7 cmp dword ptr [esi + 0x28], 9
0064e3ab jne 0x64e40a
0064e3ad push 0xbc4cf0
0064e3b2 lea edx, [edi + 0x378]
0064e3b8 lea ecx, [ebp - 0xec]
0064e3be call 0x412050
0064e3c3 add esp, 4
0064e3c6 mov ecx, eax
0064e3c8 call 0x427260
0064e3cd lea edx, [esi + 0x388]
0064e3d3 test al, al
0064e3d5 jne 0x64e3e3
0064e3d7 mov eax, dword ptr [edx]
0064e3d9 and eax, 0x80000000
0064e3de or eax, 0
0064e3e1 je 0x64e3f6
0064e3e3 mov ecx, dword ptr [edx + 4]
0064e3e6 xor eax, eax
0064e3e8 and ecx, 0x1000
0064e3ee or eax, ecx
0064e3f0 je 0x64dde9
0064e3f6 mov dword ptr [edx], 0
0064e3fc mov dword ptr [edx + 4], 0
0064e403 mov byte ptr [esi + 0x16b], 1
0064e40a lea ecx, [edi + 0x394]
0064e410 push esi
0064e411 call 0x422d00
0064e416 test al, al
0064e418 je 0x64e4ea
0064e41e push 0xbc48a0
0064e423 push 0xbc4830
0064e428 push 0xbc4950
0064e42d push 0xbc4b50
0064e432 push 0xbc4ce0
0064e437 push 0xbc4c10
0064e43c push 0xbc4cc0
0064e441 push 0xbc49a0
0064e446 mov edx, 0xbc4be0
0064e44b lea ecx, [ebp - 0xec]
0064e451 call 0x427220
0064e456 add esp, 4
0064e459 lea ecx, [ebp - 0xdc]
0064e45f mov edx, eax
0064e461 call 0x427220
0064e466 add esp, 4
0064e469 lea ecx, [ebp - 0x124]
0064e46f mov edx, eax
0064e471 call 0x427220
0064e476 add esp, 4
0064e479 lea ecx, [ebp - 0x104]
0064e47f mov edx, eax
0064e481 call 0x427220
0064e486 add esp, 4
0064e489 lea ecx, [ebp - 0x114]
0064e48f mov edx, eax
0064e491 call 0x427220
0064e496 add esp, 4
0064e499 lea ecx, [ebp - 0x154]
0064e49f mov edx, eax
0064e4a1 call 0x427220
0064e4a6 add esp, 4
0064e4a9 lea ecx, [ebp - 0x144]
0064e4af mov edx, eax
0064e4b1 call 0x427220
0064e4b6 add esp, 4
0064e4b9 lea ecx, [ebp - 0x134]
0064e4bf mov edx, eax
0064e4c1 call 0x427220
0064e4c6 push eax
0064e4c7 lea edx, [edi + 0x378]
0064e4cd lea ecx, [ebp - 0xcc]
0064e4d3 call 0x412050
0064e4d8 add esp, 8
0064e4db mov ecx, eax
0064e4dd call 0x412090
0064e4e2 test al, al
0064e4e4 jne 0x64dde9
0064e4ea mov ecx, esi
0064e4ec call 0x68d5a0
0064e4f1 push eax
0064e4f2 lea ecx, [edi + 0x394]
0064e4f8 call 0x422c30
0064e4fd push 0
0064e4ff mov ecx, esi
0064e501 call 0x68cf40
0064e506 lea edx, [edi + 0x378]
0064e50c test al, al
0064e50e je 0x64e7fe
0064e514 push 0xbc4950
0064e519 lea ecx, [ebp - 0xcc]
0064e51f call 0x412050
0064e524 add esp, 4
0064e527 mov ecx, eax
0064e529 call 0x412090
0064e52e test al, al
0064e530 jne 0x64e57e
0064e532 push 0xbc4b50
0064e537 lea edx, [edi + 0x378]
0064e53d lea ecx, [ebp - 0xcc]
0064e543 call 0x412050
0064e548 add esp, 4
0064e54b mov ecx, eax
0064e54d call 0x412090
0064e552 test al, al
0064e554 jne 0x64e57e
0064e556 push 0xbc4830
0064e55b lea edx, [edi + 0x378]
0064e561 lea ecx, [ebp - 0xcc]
0064e567 call 0x412050
0064e56c add esp, 4
0064e56f mov ecx, eax
0064e571 call 0x412090
0064e576 test al, al
0064e578 je 0x64e7f8
0064e57e push 0xbc4ce0
0064e583 lea edx, [edi + 0x378]
0064e589 lea ecx, [ebp - 0xcc]
0064e58f call 0x412050
0064e594 add esp, 4
0064e597 mov ecx, eax
0064e599 call 0x412090
0064e59e test al, al
0064e5a0 je 0x64eb47
0064e5a6 movss xmm1, dword ptr [edi + 0x298]
0064e5ae subss xmm1, dword ptr [esi + 0x298]
0064e5b6 movss xmm2, dword ptr [edi + 0x294]
0064e5be subss xmm2, dword ptr [esi + 0x294]
0064e5c6 movaps xmm0, xmm1
0064e5c9 movss dword ptr [ebp - 0x108], xmm1
0064e5d1 mulss xmm0, xmm1
0064e5d5 movaps xmm1, xmm2
0064e5d8 movss dword ptr [ebp - 0xa8], xmm2
0064e5e0 mulss xmm1, xmm2
0064e5e4 addss xmm0, xmm1
0064e5e8 call 0x4228c0
0064e5ed movss xmm2, dword ptr [esi + 0x2c8]
0064e5f5 comiss xmm0, xmm2
0064e5f8 jbe 0x64e620
0064e5fa xorps xmm1, xmm1
0064e5fd comiss xmm0, xmm1
0064e600 movss xmm1, dword ptr [ebp - 0x108]
0064e608 jbe 0x64e628
0064e60a divss xmm2, xmm0
0064e60e movss xmm0, dword ptr [ebp - 0xa8]
0064e616 mulss xmm0, xmm2
0064e61a mulss xmm1, xmm2
0064e61e jmp 0x64e630
0064e620 movss xmm1, dword ptr [ebp - 0x108]
0064e628 movss xmm0, dword ptr [ebp - 0xa8]
0064e630 push 0xbc4b50
0064e635 lea edx, [edi + 0x378]
0064e63b lea ecx, [ebp - 0xcc]
0064e641 call 0x412050
0064e646 add esp, 4
0064e649 mov ecx, eax
0064e64b call 0x412090
0064e650 test al, al
0064e652 je 0x64e660
0064e654 mov dword ptr [ebp - 0xf8], 0x1a
0064e65e jmp 0x64e695
0064e660 push 0xbc4830
0064e665 lea edx, [edi + 0x378]
0064e66b lea ecx, [ebp - 0xcc]
0064e671 call 0x412050
0064e676 add esp, 4
0064e679 mov ecx, eax
0064e67b call 0x412090
0064e680 test al, al
0064e682 mov ecx, 0x13
0064e687 mov edx, 0x30
0064e68c cmovne ecx, edx
0064e68f mov dword ptr [ebp - 0xf8], ecx
0064e695 call 0x6c3d90
0064e69a addss xmm0, dword ptr [esi + 0x294]
0064e6a2 addss xmm1, dword ptr [esi + 0x298]
0064e6aa mov ecx, dword ptr [0xbfd65c]
0064e6b0 push eax
0064e6b1 push 0
0064e6b3 push dword ptr [edi + 0x320]
0064e6b9 lea eax, [ebp - 0xd4]
0064e6bf movss dword ptr [ebp - 0xd4], xmm0
0064e6c7 push 0xc02fec
0064e6cc push eax
0064e6cd push dword ptr [ebp - 0xf8]
0064e6d3 movss dword ptr [ebp - 0xd0], xmm1
0064e6db push 2
0064e6dd call 0x422e20
0064e6e2 mov ecx, eax
0064e6e4 mov dword ptr [ebp - 0xa8], eax
0064e6ea mov edx, dword ptr [eax]
0064e6ec call dword ptr [edx + 0xc]
0064e6ef lea eax, [ebp - 0xcc]
0064e6f5 mov ecx, 0xbc4ce0
0064e6fa push eax
0064e6fb call 0x57f3a0
0064e700 push eax
0064e701 lea edx, [edi + 0x378]
0064e707 lea ecx, [ebp - 0x134]
0064e70d call 0x412050
0064e712 sub esp, 0xc
0064e715 mov ecx, esp
0064e717 movups xmm0, xmmword ptr [eax]
0064e71a movups xmmword ptr [ecx], xmm0
0064e71d mov ecx, dword ptr [ebp - 0xa8]
0064e723 call 0x650280
0064e728 mov ecx, dword ptr [ebp - 0xa8]
0064e72e movss xmm0, dword ptr [edi + 0x2e0]
0064e736 push ecx
0064e737 movss dword ptr [esp], xmm0
0064e73c mov eax, dword ptr [ecx]
0064e73e call dword ptr [eax + 0x3c]
0064e741 movss xmm0, dword ptr [edi + 0x370]
0064e749 maxss xmm0, dword ptr [0xb6a214]
0064e751 mov eax, dword ptr [ebp - 0xa8]
0064e757 mov ecx, eax
0064e759 movss dword ptr [eax + 0x374], xmm0
0064e761 movss dword ptr [eax + 0x370], xmm0
0064e769 call 0x651770
0064e76e cmp dword ptr [ebp - 0xac], 0
0064e775 je 0x64e7cf
0064e777 push 0
0064e779 call 0x6c3d90
0064e77e and eax, 1
0064e781 lea eax, [eax*2 - 1]
0064e788 push eax
0064e789 push ecx
0064e78a mov ecx, dword ptr [ebp - 0xac]
0064e790 lea eax, [ebp - 0xa4]
0064e796 mov dword ptr [esp], 0x3f800000
0064e79d push 1
0064e79f push eax
0064e7a0 call 0x7836a0
0064e7a5 movss xmm0, dword ptr [ebp - 0x58]
0064e7aa maxss xmm0, dword ptr [0xb6a214]
0064e7b2 mov eax, dword ptr [ebp - 0xa8]
0064e7b8 mov ecx, eax
0064e7ba movss dword ptr [eax + 0x374], xmm0
0064e7c2 movss dword ptr [eax + 0x370], xmm0
0064e7ca call 0x651770
0064e7cf mov ecx, dword ptr [ebp - 0xa8]
0064e7d5 inc dword ptr [0xbffe08]
0064e7db push 1
0064e7dd push esi
0064e7de mov eax, dword ptr [ecx]
0064e7e0 call dword ptr [eax + 0x58]
0064e7e3 mov eax, dword ptr [esi]
0064e7e5 mov ecx, esi
0064e7e7 push 0
0064e7e9 push dword ptr [ebp - 0xa8]
0064e7ef call dword ptr [eax + 0x58]
0064e7f2 dec dword ptr [0xbffe08]
0064e7f8 lea edx, [edi + 0x378]
0064e7fe cmp byte ptr [ebp - 0xb1], 0
0064e805 jne 0x64f9a3
0064e80b xorps xmm0, xmm0
0064e80e movlpd qword ptr [ebp - 0xd4], xmm0
0064e816 movss xmm0, dword ptr [edi + 0x2e0]
0064e81e push edi
0064e81f sub esp, 0x14
0064e822 movss dword ptr [ebp - 0xb0], xmm0
0064e82a movups xmm0, xmmword ptr [edx]
0064e82d mov eax, esp
0064e82f lea edx, [ebp - 0xd4]
0064e835 push ecx
0064e836 movups xmmword ptr [eax], xmm0
0064e839 call 0x656c90
0064e83e mov eax, dword ptr [esi + 0x28]
0064e841 add esp, 0x1c
0064e844 sub eax, 0xa
0064e847 cmp eax, 0x3dd
0064e84c ja 0x64e8e2
0064e852 push 0xbc4be0
0064e857 lea edx, [edi + 0x378]
0064e85d lea ecx, [ebp - 0xcc]
0064e863 call 0x412050
0064e868 add esp, 4
0064e86b mov ecx, eax
0064e86d call 0x412090
0064e872 test al, al
0064e874 je 0x64e881
0064e876 mov ecx, esi
0064e878 call 0x6846e0
0064e87d test al, al
0064e87f je 0x64e8e2
0064e881 push 0xbc4cc0
0064e886 lea edx, [edi + 0x378]
0064e88c lea ecx, [ebp - 0xcc]
0064e892 call 0x412050
0064e897 add esp, 4
0064e89a mov ecx, eax
0064e89c call 0x412090
0064e8a1 test al, al
0064e8a3 je 0x64e8b0
0064e8a5 mov ecx, esi
0064e8a7 call 0x6846e0
0064e8ac test al, al
0064e8ae jne 0x64e8e2
0064e8b0 push dword ptr [edi + 0x2bc]
0064e8b6 push dword ptr [edi + 0x2b8]
0064e8bc push 0
0064e8be push 0xbeab70
0064e8c3 push 0xbeab18
0064e8c8 push 0
0064e8ca push esi
0064e8cb call 0x9ec34c
0064e8d0 add esp, 0x14
0064e8d3 mov ecx, eax
0064e8d5 call 0x6aa830
0064e8da test al, al
0064e8dc je 0x64f061
0064e8e2 push 0xbc4cc0
0064e8e7 lea edx, [edi + 0x378]
0064e8ed lea ecx, [ebp - 0xcc]
0064e8f3 call 0x412050
0064e8f8 add esp, 4
0064e8fb mov ecx, eax
0064e8fd call 0x412090
0064e902 test al, al
0064e904 je 0x64e939
0064e906 mov ecx, esi
0064e908 call 0x6846e0
0064e90d test al, al
0064e90f je 0x64e939
0064e911 push 0xbc48d0
0064e916 lea edx, [edi + 0x378]
0064e91c lea ecx, [ebp - 0xcc]
0064e922 call 0x412050
0064e927 add esp, 4
0064e92a mov ecx, eax
0064e92c call 0x412090
0064e931 test al, al
0064e933 jne 0x64dde9
0064e939 push edi
0064e93a lea ecx, [ebp - 0x38]
0064e93d call 0x4229a0
0064e942 mov eax, dword ptr [esi]
0064e944 lea ecx, [ebp - 0x38]
0064e947 movss xmm0, dword ptr [ebp - 0xb0]
0064e94f push 0x1e
0064e951 push ecx
0064e952 push dword ptr [ebp - 0xd0]
0064e958 push dword ptr [ebp - 0xd4]
0064e95e push ecx
0064e95f mov ecx, esi
0064e961 movss dword ptr [esp], xmm0
0064e966 call dword ptr [eax + 0x20]
0064e969 push 0xbc48a0
0064e96e lea edx, [edi + 0x378]
0064e974 lea ecx, [ebp - 0xcc]
0064e97a call 0x412050
0064e97f add esp, 4
0064e982 mov ecx, eax
0064e984 call 0x412090
0064e989 test al, al
0064e98b je 0x64ef88
0064e991 mov ecx, esi
0064e993 call 0x6846e0
0064e998 test al, al
0064e99a jne 0x64ef88
0064e9a0 push 0xbc49a0
0064e9a5 mov edx, 0xbc4be0
0064e9aa lea ecx, [ebp - 0xcc]
0064e9b0 call 0x427220
0064e9b5 push eax
0064e9b6 lea edx, [edi + 0x378]
0064e9bc lea ecx, [ebp - 0x134]
0064e9c2 call 0x412050
0064e9c7 add esp, 8
0064e9ca mov ecx, eax
0064e9cc call 0x427260
0064e9d1 test al, al
0064e9d3 je 0x64ea95
0064e9d9 movss xmm0, dword ptr [edi + 0x294]
0064e9e1 subss xmm0, dword ptr [esi + 0x294]
0064e9e9 movss xmm2, dword ptr [edi + 0x2b8]
0064e9f1 movss xmm1, dword ptr [edi + 0x2bc]
0064e9f9 mulss xmm1, xmm1
0064e9fd movss dword ptr [ebp - 0xd4], xmm0
0064ea05 movss xmm0, dword ptr [edi + 0x298]
0064ea0d subss xmm0, dword ptr [esi + 0x298]
0064ea15 movss dword ptr [ebp - 0xd0], xmm0
0064ea1d movaps xmm0, xmm2
0064ea20 mulss xmm0, xmm2
0064ea24 addss xmm0, xmm1
0064ea28 call 0x4228c0
0064ea2d mulss xmm0, dword ptr [0xb6a480]
0064ea35 lea eax, [ebp - 0xe4]
0064ea3b push ecx
0064ea3c lea ecx, [ebp - 0xd4]
0064ea42 addss xmm0, dword ptr [0xb6a7b0]
0064ea4a minss xmm0, dword ptr [0xb6a974]
0064ea52 movss dword ptr [esp], xmm0
0064ea57 push eax
0064ea58 call 0x9628d0
0064ea5d movss xmm1, dword ptr [edi + 0x2f4]
0064ea65 movaps xmm0, xmm1
0064ea68 movss xmm2, dword ptr [eax + 4]
0064ea6d mulss xmm0, dword ptr [eax]
0064ea71 mulss xmm2, xmm1
0064ea75 addss xmm0, dword ptr [edi + 0x2b8]
0064ea7d addss xmm2, dword ptr [edi + 0x2bc]
0064ea85 movss dword ptr [edi + 0x2b8], xmm0
0064ea8d movss dword ptr [edi + 0x2bc], xmm2
0064ea95 mov eax, dword ptr [edi + 0x3c0]
0064ea9b test eax, eax
0064ea9d jne 0x64ef56
0064eaa3 push 0xbc4900
0064eaa8 lea edx, [edi + 0x378]
0064eaae lea ecx, [ebp - 0xcc]
0064eab4 call 0x412050
0064eab9 add esp, 4
0064eabc mov ecx, eax
0064eabe call 0x412090
0064eac3 test al, al
0064eac5 je 0x64ef54
0064eacb lea eax, [ebp - 0xcc]
0064ead1 mov ecx, 0xbc4900
0064ead6 push eax
0064ead7 call 0x57f3a0
0064eadc movss xmm0, dword ptr [0xb6a614]
0064eae4 lea edx, [edi + 0x378]
0064eaea movss xmm2, dword ptr [0xb6a480]
0064eaf2 movss dword ptr [ebp - 0x108], xmm0
0064eafa mov ecx, dword ptr [eax]
0064eafc and dword ptr [edx], ecx
0064eafe mov ecx, dword ptr [eax + 4]
0064eb01 and dword ptr [edx + 4], ecx
0064eb04 mov ecx, dword ptr [eax + 8]
0064eb07 and dword ptr [edx + 8], ecx
0064eb0a mov eax, dword ptr [eax + 0xc]
0064eb0d and dword ptr [edx + 0xc], eax
0064eb10 cmp dword ptr [ebp - 0xac], 0
0064eb17 movss xmm1, dword ptr [edi + 0x370]
0064eb1f mulss xmm1, xmm2
0064eb23 je 0x64ed9b
0064eb29 movss xmm0, dword ptr [0xb6a4a0]
0064eb31 comiss xmm0, xmm1
0064eb34 jb 0x64ed7e
0064eb3a movss xmm0, dword ptr [0xb6a4dc]
0064eb42 jmp 0x64ed93
0064eb47 cmp dword ptr [edi + 0x3c8], 0
0064eb4e jne 0x64e7f8
0064eb54 mov eax, dword ptr [esi + 0x294]
0064eb5a movss xmm3, dword ptr [esi + 0x2c8]
0064eb62 mov ecx, dword ptr [esi + 0x298]
0064eb68 addss xmm3, xmm3
0064eb6c mov dword ptr [ebp - 0xd4], eax
0064eb72 lea eax, [ebp - 0xd4]
0064eb78 push 4
0064eb7a push eax
0064eb7b lea eax, [ebp - 0xec]
0064eb81 mov dword ptr [ebp - 0xd0], ecx
0064eb87 addss xmm3, dword ptr [0xb6aafc]
0064eb8f push eax
0064eb90 mov eax, dword ptr [0xbfd65c]
0064eb95 mov ecx, dword ptr [eax + 0x18190]
0064eb9b add ecx, 0x1218
0064eba1 call 0x4157f0
0064eba6 xor eax, eax
0064eba8 mov dword ptr [ebp - 4], 0
0064ebaf xor edx, edx
0064ebb1 cmp dword ptr [ebp - 0xe0], eax
0064ebb7 jbe 0x64ec11
0064ebb9 mov edi, dword ptr [ebp - 0xe8]
0064ebbf nop 
0064ebc0 mov ecx, dword ptr [edi + eax*4]
0064ebc3 test ecx, ecx
0064ebc5 je 0x64ebd6
0064ebc7 cmp dword ptr [ecx + 0x28], 2
0064ebcb jne 0x64ebd6
0064ebcd cmp dword ptr [ecx + 0x3c8], esi
0064ebd3 jne 0x64ebd6
0064ebd5 inc edx
0064ebd6 inc eax
0064ebd7 cmp eax, dword ptr [ebp - 0xe0]
0064ebdd jb 0x64ebc0
0064ebdf mov edi, dword ptr [ebp - 0xf0]
0064ebe5 cmp edx, 0x10
0064ebe8 jb 0x64ec11
0064ebea mov eax, dword ptr [edi]
0064ebec mov ecx, edi
0064ebee call dword ptr [eax + 0x28]
0064ebf1 cmp byte ptr [ebp - 0xec], 0
0064ebf8 jne 0x64dde9
0064ebfe push dword ptr [ebp - 0xe8]
0064ec04 call 0x9eace5
0064ec09 add esp, 4
0064ec0c jmp 0x64dde9
0064ec11 mov ecx, dword ptr [edi + 0x3c8]
0064ec17 lea eax, [edi + 0x3c8]
0064ec1d test ecx, ecx
0064ec1f je 0x64ec3f
0064ec21 mov dword ptr [ebp - 0xb0], eax
0064ec27 add ecx, 0x324
0064ec2d lea eax, [ebp - 0xb0]
0064ec33 push eax
0064ec34 call 0x4bc3c0
0064ec39 lea eax, [edi + 0x3c8]
0064ec3f push eax
0064ec40 mov ecx, esi
0064ec42 mov dword ptr [eax], esi
0064ec44 call 0x4bae70
0064ec49 movss xmm1, dword ptr [edi + 0x294]
0064ec51 lea edx, [edi + 0x378]
0064ec57 movss xmm0, dword ptr [edi + 0x298]
0064ec5f lea ecx, [ebp - 0xcc]
0064ec65 subss xmm1, dword ptr [esi + 0x294]
0064ec6d subss xmm0, dword ptr [esi + 0x298]
0064ec75 push 0xbc4950
0064ec7a movss dword ptr [edi + 0x3cc], xmm1
0064ec82 movss dword ptr [edi + 0x3d0], xmm0
0064ec8a call 0x412050
0064ec8f add esp, 4
0064ec92 mov ecx, eax
0064ec94 call 0x412090
0064ec99 test al, al
0064ec9b jne 0x64ecf1
0064ec9d push 0xbc4830
0064eca2 lea edx, [edi + 0x378]
0064eca8 lea ecx, [ebp - 0xcc]
0064ecae call 0x412050
0064ecb3 add esp, 4
0064ecb6 mov ecx, eax
0064ecb8 call 0x412090
0064ecbd test al, al
0064ecbf jne 0x64ecf1
0064ecc1 push 0xbc4b50
0064ecc6 lea edx, [edi + 0x378]
0064eccc lea ecx, [ebp - 0xcc]
0064ecd2 call 0x412050
0064ecd7 add esp, 4
0064ecda mov ecx, eax
0064ecdc call 0x412090
0064ece1 test al, al
0064ece3 je 0x64ed08
0064ece5 mov dword ptr [edi + 0x3d4], 0x12c
0064ecef jmp 0x64ecfb
0064ecf1 mov dword ptr [edi + 0x3d4], 0x3c
0064ecfb cmp dword ptr [edi + 0x70], 0
0064ecff je 0x64ed08
0064ed01 mov byte ptr [edi + 0x80], 0
0064ed08 lea eax, [ebp - 0xcc]
0064ed0e mov edx, 0xbc4bc0
0064ed13 push eax
0064ed14 push 0xbc4c60
0064ed19 lea ecx, [ebp - 0x134]
0064ed1f call 0x427220
0064ed24 add esp, 4
0064ed27 mov ecx, eax
0064ed29 call 0x57f3a0
0064ed2e lea edx, [edi + 0x378]
0064ed34 mov ecx, dword ptr [eax]
0064ed36 and dword ptr [edx], ecx
0064ed38 mov ecx, dword ptr [eax + 4]
0064ed3b and dword ptr [edx + 4], ecx
0064ed3e mov ecx, dword ptr [eax + 8]
0064ed41 and dword ptr [edx + 8], ecx
0064ed44 mov eax, dword ptr [eax + 0xc]
0064ed47 and dword ptr [edx + 0xc], eax
0064ed4a cmp dword ptr [0xbffe08], 0
0064ed51 ja 0x64ebf1
0064ed57 mov dword ptr [ebp - 4], 0xffffffff
0064ed5e cmp byte ptr [ebp - 0xec], 0
0064ed65 jne 0x64e7fe
0064ed6b push dword ptr [ebp - 0xe8]
0064ed71 call 0x9eace5
0064ed76 add esp, 4
0064ed79 jmp 0x64e7f8
0064ed7e movss xmm0, dword ptr [0xb6a53c]
0064ed86 comiss xmm0, xmm1
0064ed89 jb 0x64ed9b
0064ed8b movss xmm0, dword ptr [0xb6a560]
0064ed93 movss dword ptr [ebp - 0x108], xmm0
0064ed9b movss xmm0, dword ptr [edi + 0x2e0]
0064eda3 mulss xmm0, xmm2
0064eda7 movss dword ptr [ebp - 0xb0], xmm0
0064edaf call 0x6c3d90
0064edb4 mov ecx, dword ptr [0xbfd65c]
0064edba push 0
0064edbc push 0xbeacac
0064edc1 push 0xbeab18
0064edc6 push 0
0064edc8 push eax
0064edc9 push 0
0064edcb push dword ptr [edi + 0x320]
0064edd1 lea eax, [edi + 0x294]
0064edd7 push 0xc02fec
0064eddc push eax
0064eddd push 0
0064eddf push 4
0064ede1 call 0x422e20
0064ede6 push eax
0064ede7 call 0x9ec34c
0064edec mov esi, eax
0064edee add esp, 0x14
0064edf1 mov byte ptr [esi + 0x398], 1
0064edf8 mov ecx, dword ptr [edi + 0x34]
0064edfb mov dword ptr [esi + 0x34], ecx
0064edfe mov ecx, dword ptr [edi + 0x38]
0064ee01 mov dword ptr [esi + 0x38], ecx
0064ee04 movups xmm0, xmmword ptr [edi + 0x378]
0064ee0b mov byte ptr [esi + 0x3b3], 1
0064ee12 push -1
0064ee14 movups xmmword ptr [esi + 0x388], xmm0
0064ee1b movss xmm0, dword ptr [edi + 0x370]
0064ee23 mulss xmm0, dword ptr [0xb6a480]
0064ee2b movss dword ptr [esi + 0x384], xmm0
0064ee33 movss xmm0, dword ptr [0xbc7a28]
0064ee3b xorps xmm0, xmmword ptr [0xb6c9b0]
0064ee42 movss dword ptr [ebp - 0xd4], xmm0
0064ee4a movss xmm0, dword ptr [0xbc7a2c]
0064ee52 xorps xmm0, xmmword ptr [0xb6c9b0]
0064ee59 movss dword ptr [ebp - 0xd0], xmm0
0064ee61 push dword ptr [ebp - 0xd0]
0064ee67 movss xmm0, dword ptr [edi + 0x370]
0064ee6f push dword ptr [ebp - 0xd4]
0064ee75 mulss xmm0, dword ptr [0xb6a480]
0064ee7d push ecx
0064ee7e mov ecx, esi
0064ee80 movss dword ptr [esp], xmm0
0064ee85 call 0x6843a0
0064ee8a movss xmm1, dword ptr [ebp - 0xb0]
0064ee92 movaps xmm0, xmm1
0064ee95 mulss xmm1, dword ptr [0xb6a974]
0064ee9d mulss xmm0, dword ptr [0xb6a8f4]
0064eea5 addss xmm0, dword ptr [0xb6aa0c]
0064eead minss xmm0, xmm1
0064eeb1 movss dword ptr [esi + 0x368], xmm0
0064eeb9 movss xmm0, dword ptr [ebp - 0x108]
0064eec1 movss dword ptr [esi + 0x39c], xmm0
0064eec9 call 0x6c3d90
0064eece or dword ptr [esi + 0x160], 0x4000000
0064eed8 mov dword ptr [esi + 0x2a4], 0
0064eee2 mov dword ptr [esi + 0x2a8], 0xc0400000
0064eeec movd xmm0, eax
0064eef0 cvtdq2pd xmm0, xmm0
0064eef4 shr eax, 0x1f
0064eef7 or dword ptr [esi + 0x164], 0x400
0064ef01 mov dword ptr [esi + 0x360], 0x14
0064ef0b mov dword ptr [esi + 0x364], 0x14
0064ef15 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
0064ef1e cvtpd2ps xmm1, xmm0
0064ef22 movss xmm0, dword ptr [0xb6ae7c]
0064ef2a mulss xmm1, dword ptr [0xb6a19c]
0064ef32 mulss xmm1, dword ptr [0xb6a8f4]
0064ef3a subss xmm0, xmm1
0064ef3e movss dword ptr [esi + 0x36c], xmm0
0064ef46 mov eax, dword ptr [edi + 0x3c0]
0064ef4c mov esi, dword ptr [ebp - 0xb8]
0064ef52 jmp 0x64ef56
0064ef54 xor eax, eax
0064ef56 inc eax
0064ef57 lea edx, [edi + 0x378]
0064ef5d push 0xbc4790
0064ef62 lea ecx, [ebp - 0xcc]
0064ef68 mov dword ptr [edi + 0x3c0], eax
0064ef6e call 0x412050
0064ef73 add esp, 4
0064ef76 mov ecx, eax
0064ef78 call 0x412090
0064ef7d test al, al
0064ef7f je 0x64ef88
0064ef81 inc word ptr [edi + 0x3bc]
0064ef88 mov ecx, dword ptr [esi + 0x28]
0064ef8b lea eax, [ecx - 0xa]
0064ef8e cmp eax, 0x3dd
0064ef93 ja 0x64ef9f
0064ef95 mov byte ptr [edi + 0x738], 0
0064ef9c mov ecx, dword ptr [esi + 0x28]
0064ef9f lea eax, [ecx - 0xa]
0064efa2 cmp eax, 0x3dd
0064efa7 ja 0x64f021
0064efa9 push 0xbc4b50
0064efae lea edx, [edi + 0x378]
0064efb4 lea ecx, [ebp - 0xcc]
0064efba call 0x412050
0064efbf add esp, 4
0064efc2 mov ecx, eax
0064efc4 call 0x412090
0064efc9 test al, al
0064efcb jne 0x64dde9
0064efd1 push 0xbc4950
0064efd6 lea edx, [edi + 0x378]
0064efdc lea ecx, [ebp - 0xcc]
0064efe2 call 0x412050
0064efe7 add esp, 4
0064efea mov ecx, eax
0064efec call 0x412090
0064eff1 test al, al
0064eff3 jne 0x64dde9
0064eff9 push 0xbc4830
0064effe lea edx, [edi + 0x378]
0064f004 lea ecx, [ebp - 0xcc]
0064f00a call 0x412050
0064f00f add esp, 4
0064f012 mov ecx, eax
0064f014 call 0x412090
0064f019 test al, al
0064f01b jne 0x64dde9
0064f021 push 0
0064f023 mov ecx, esi
0064f025 call 0x68cf40
0064f02a test al, al
0064f02c je 0x64f061
0064f02e mov eax, dword ptr [edi + 0x314]
0064f034 mov dword ptr [ebp - 0xb0], eax
0064f03a test eax, eax
0064f03c je 0x64f061
0064f03e cmp dword ptr [eax + 0x28], 1
0064f042 jne 0x64f061
0064f044 push 0
0064f046 push 0x175
0064f04b mov ecx, eax
0064f04d call 0x73af30
0064f052 test al, al
0064f054 je 0x64f061
0064f056 mov ecx, dword ptr [ebp - 0xb0]
0064f05c call 0x78a6f0
0064f061 push 0xbc4c70
0064f066 lea edx, [edi + 0x378]
0064f06c lea ecx, [ebp - 0xcc]
0064f072 call 0x412050
0064f077 add esp, 4
0064f07a mov ecx, eax
0064f07c call 0x412090
0064f081 test al, al
0064f083 je 0x64f126
0064f089 cmp dword ptr [esi + 0x28], 0x21
0064f08d je 0x64f126
0064f093 mov eax, dword ptr [ebp - 0xac]
0064f099 test eax, eax
0064f09b je 0x64f0a7
0064f09d movss xmm0, dword ptr [eax + 0x14b0]
0064f0a5 jmp 0x64f0aa
0064f0a7 xorps xmm0, xmm0
0064f0aa mulss xmm0, dword ptr [0xb6a50c]
0064f0b2 mov ecx, 0xa
0064f0b7 cvttss2si eax, xmm0
0064f0bb sub ecx, eax
0064f0bd mov eax, 1
0064f0c2 cmp ecx, eax
0064f0c4 cmovl ecx, eax
0064f0c7 call 0x659230
0064f0cc test eax, eax
0064f0ce jne 0x64f126
0064f0d0 push 0xbc4ce0
0064f0d5 lea edx, [edi + 0x378]
0064f0db lea ecx, [ebp - 0xcc]
0064f0e1 call 0x412050
0064f0e6 add esp, 4
0064f0e9 mov ecx, eax
0064f0eb call 0x427260
0064f0f0 test al, al
0064f0f2 jne 0x64f0ff
0064f0f4 mov ecx, edi
0064f0f6 call 0x6520e0
0064f0fb test al, al
0064f0fd je 0x64f126
0064f0ff mov eax, dword ptr [0xbc4ca0]
0064f104 lea ecx, [edi + 0x378]
0064f10a or dword ptr [ecx], eax
0064f10c mov eax, dword ptr [0xbc4ca4]
0064f111 or dword ptr [ecx + 4], eax
0064f114 mov eax, dword ptr [0xbc4ca8]
0064f119 or dword ptr [ecx + 8], eax
0064f11c mov eax, dword ptr [0xbc4cac]
0064f121 or dword ptr [ecx + 0xc], eax
0064f124 jmp 0x64f12c
0064f126 lea ecx, [edi + 0x378]
0064f12c mov eax, dword ptr [edi + 0x2c]
0064f12f cmp eax, 2
0064f132 je 0x64f13d
0064f134 cmp eax, 0x1e
0064f137 jne 0x64f22f
0064f13d mov edx, ecx
0064f13f lea ecx, [ebp - 0xcc]
0064f145 push 0xbc4ce0
0064f14a call 0x412050
0064f14f add esp, 4
0064f152 mov ecx, eax
0064f154 call 0x412090
0064f159 test al, al
0064f15b je 0x64f22f
0064f161 push 0
0064f163 mov ecx, esi
0064f165 call 0x684630
0064f16a test al, al
0064f16c je 0x64f22f
0064f172 lea eax, [edi + 0xe4]
0064f178 push eax
0064f179 lea ecx, [ebp - 0x3c]
0064f17c call 0x402170
0064f181 cmp dword ptr [edi + 0x2c], 0x1e
0064f185 jne 0x64f1ca
0064f187 movss xmm0, dword ptr [0xb6a3b0]
0064f18f lea ecx, [ebp - 0x180]
0064f195 movaps xmm3, xmm0
0064f198 movaps xmm2, xmm0
0064f19b movaps xmm1, xmm0
0064f19e call 0x427080
0064f1a3 sub esp, 0x2c
0064f1a6 mov edx, eax
0064f1a8 lea eax, [ebp - 0x3c]
0064f1ab mov ecx, esp
0064f1ad push eax
0064f1ae call 0x402170
0064f1b3 lea ecx, [ebp - 0x1ac]
0064f1b9 call 0x402290
0064f1be add esp, 0x2c
0064f1c1 lea ecx, [ebp - 0x3c]
0064f1c4 push eax
0064f1c5 call 0x4021a0
0064f1ca call 0x6c3d90
0064f1cf push 0
0064f1d1 push ecx
0064f1d2 movd xmm0, eax
0064f1d6 cvtdq2pd xmm0, xmm0
0064f1da shr eax, 0x1f
0064f1dd addsd xmm0, qword ptr [eax*8 + 0xb6c940]
0064f1e6 lea eax, [ebp - 0x3c]
0064f1e9 cvtpd2ps xmm1, xmm0
0064f1ed movss xmm0, dword ptr [edi + 0x360]
0064f1f5 mulss xmm1, dword ptr [0xb6a19c]
0064f1fd movss dword ptr [esp], xmm0
0064f202 push eax
0064f203 mulss xmm1, dword ptr [0xb6a864]
0064f20b lea eax, [edi + 0x294]
0064f211 push ecx
0064f212 mov ecx, dword ptr [0xbfd65c]
0064f218 addss xmm1, dword ptr [0xb6a7b0]
0064f220 movss dword ptr [esp], xmm1
0064f225 push 1
0064f227 push 0x23
0064f229 push eax
0064f22a call 0x6d57a0
0064f22f push 0xbc4b30
0064f234 lea edx, [edi + 0x378]
0064f23a lea ecx, [ebp - 0xcc]
0064f240 call 0x412050
0064f245 add esp, 4
0064f248 mov ecx, eax
0064f24a call 0x412090
0064f24f test al, al
0064f251 je 0x64f64d
0064f257 call 0x6c3d90
0064f25c push eax
0064f25d push 0
0064f25f push edi
0064f260 push 0xc02fec
0064f265 lea ecx, [edi + 0x294]
0064f26b push ecx
0064f26c mov ecx, dword ptr [0xbfd65c]
0064f272 push 0x2c
0064f274 push 0x3e8
0064f279 call 0x422e20
0064f27e mov ecx, eax
0064f280 mov edx, dword ptr [eax]
0064f282 call dword ptr [edx + 0xc]
0064f285 push 0
0064f287 push 0xbeab9c
0064f28c push 0xbeab18
0064f291 push 0
0064f293 push dword ptr [edi + 0x314]
0064f299 call 0x9ec34c
0064f29e add esp, 0x14
0064f2a1 mov dword ptr [ebp - 0xac], eax
0064f2a7 test eax, eax
0064f2a9 jne 0x64f2bd
0064f2ab mov ecx, dword ptr [0xbfd65c]
0064f2b1 push eax
0064f2b2 call 0x412750
0064f2b7 mov dword ptr [ebp - 0xac], eax
0064f2bd push 0
0064f2bf mov ecx, esi
0064f2c1 call 0x684630
0064f2c6 test al, al
0064f2c8 jne 0x64f2db
0064f2ca mov eax, dword ptr [esi]
0064f2cc mov ecx, esi
0064f2ce mov eax, dword ptr [eax + 0x44]
0064f2d1 call eax
0064f2d3 test al, al
0064f2d5 je 0x64f64d
0064f2db call 0x6c3d90
0064f2e0 mov esi, dword ptr [0xbfd680]
0064f2e6 lea ecx, [ebp - 0xf8]
0064f2ec mov dword ptr [ebp - 0xf8], 0xb5
0064f2f6 movd xmm0, eax
0064f2fa cvtdq2pd xmm0, xmm0
0064f2fe shr eax, 0x1f
0064f301 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
0064f30a cvtpd2ps xmm0, xmm0
0064f30e mulss xmm0, dword ptr [0xb6a19c]
0064f316 movss dword ptr [ebp - 0xb0], xmm0
0064f31e call 0x8b1340
0064f323 movss xmm0, dword ptr [ebp - 0xb0]
0064f32b sub esp, 8
0064f32e mulss xmm0, dword ptr [0xb6a350]
0064f336 mov dword ptr [esp + 4], 0
0064f33e addss xmm0, dword ptr [0xb6a614]
0064f346 movss dword ptr [esp], xmm0
0064f34b push 0
0064f34d push 2
0064f34f push ecx
0064f350 mov dword ptr [esp], 0x3f000000
0064f357 lea ecx, [esi + 0x29de0]
0064f35d push dword ptr [ebp - 0xf8]
0064f363 call 0x888de0
0064f368 call 0x6c3d90
0064f36d test al, 1
0064f36f jne 0x64f591
0064f375 call 0x6c3d90
0064f37a mov esi, dword ptr [ebp - 0xb8]
0064f380 and eax, 1
0064f383 add eax, 1
0064f386 mov dword ptr [ebp - 0xb0], eax
0064f38c je 0x64f64d
0064f392 movss xmm0, dword ptr [edi + 0x294]
0064f39a lea eax, [ebp - 0xe4]
0064f3a0 subss xmm0, dword ptr [edi + 0x2b8]
0064f3a8 mov ecx, dword ptr [ebp - 0xac]
0064f3ae push esi
0064f3af push eax
0064f3b0 push 1
0064f3b2 movss dword ptr [ebp - 0xe4], xmm0
0064f3ba movss xmm0, dword ptr [edi + 0x298]
0064f3c2 subss xmm0, dword ptr [edi + 0x2bc]
0064f3ca movss dword ptr [ebp - 0xe0], xmm0
0064f3d2 call 0x725cc0
0064f3d7 mov dword ptr [ebp - 0x118], eax
0064f3dd call 0x6c3d90
0064f3e2 movd xmm0, eax
0064f3e6 cvtdq2pd xmm0, xmm0
0064f3ea shr eax, 0x1f
0064f3ed addsd xmm0, qword ptr [eax*8 + 0xb6c940]
0064f3f6 mov eax, dword ptr [ebp - 0xac]
0064f3fc movss xmm1, dword ptr [eax + 0x294]
0064f404 subss xmm1, dword ptr [edi + 0x294]
0064f40c movss xmm2, dword ptr [eax + 0x298]
0064f414 subss xmm2, dword ptr [edi + 0x298]
0064f41c cvtpd2ps xmm0, xmm0
0064f420 movss dword ptr [ebp - 0xa8], xmm1
0064f428 mulss xmm0, dword ptr [0xb6a19c]
0064f430 movss dword ptr [ebp - 0xf8], xmm2
0064f438 movss dword ptr [ebp - 0x108], xmm0
0064f440 movaps xmm0, xmm1
0064f443 mulss xmm0, xmm1
0064f447 movaps xmm1, xmm2
0064f44a mulss xmm1, xmm2
0064f44e addss xmm0, xmm1
0064f452 call 0x4228c0
0064f457 comiss xmm0, dword ptr [0xb6a18c]
0064f45e jbe 0x64f494
0064f460 movss xmm1, dword ptr [0xb6a614]
0064f468 divss xmm1, xmm0
0064f46c movss xmm0, dword ptr [ebp - 0xa8]
0064f474 mulss xmm0, xmm1
0064f478 movss dword ptr [ebp - 0xa8], xmm0
0064f480 movss xmm0, dword ptr [ebp - 0xf8]
0064f488 mulss xmm0, xmm1
0064f48c movss dword ptr [ebp - 0xf8], xmm0
0064f494 movss xmm0, dword ptr [ebp - 0x108]
0064f49c mulss xmm0, dword ptr [0xb6aa58]
0064f4a4 subss xmm0, dword ptr [0xb6a9e8]
0064f4ac mulss xmm0, dword ptr [0xb6a230]
0064f4b4 movss dword ptr [ebp - 0x108], xmm0
0064f4bc call 0x411fe0
0064f4c1 movss dword ptr [ebp - 0xd0], xmm0
0064f4c9 movss xmm0, dword ptr [ebp - 0x108]
0064f4d1 call 0x412010
0064f4d6 movaps xmm3, xmm0
0064f4d9 call 0x6c3d90
0064f4de movss xmm6, dword ptr [ebp - 0xa8]
0064f4e6 movss xmm5, dword ptr [ebp - 0xf8]
0064f4ee movaps xmm2, xmm6
0064f4f1 mulss xmm2, dword ptr [ebp - 0xd0]
0064f4f9 movaps xmm0, xmm5
0064f4fc mulss xmm5, dword ptr [ebp - 0xd0]
0064f504 movd xmm1, eax
0064f508 cvtdq2pd xmm1, xmm1
0064f50c shr eax, 0x1f
0064f50f mulss xmm0, xmm3
0064f513 addsd xmm1, qword ptr [eax*8 + 0xb6c940]
0064f51c mov eax, dword ptr [ebp - 0x118]
0064f522 mulss xmm6, xmm3
0064f526 subss xmm2, xmm0
0064f52a cvtpd2ps xmm1, xmm1
0064f52e addss xmm5, xmm6
0064f532 mulss xmm1, dword ptr [0xb6a19c]
0064f53a mulss xmm1, dword ptr [0xb6a8cc]
0064f542 addss xmm1, dword ptr [0xb6a974]
0064f54a mulss xmm2, xmm1
0064f54e mulss xmm5, xmm1
0064f552 movss dword ptr [eax + 0x2b8], xmm2
0064f55a movss dword ptr [eax + 0x2bc], xmm5
0064f562 call 0x6c3d90
0064f567 xor edx, edx
0064f569 mov ecx, 0xa
0064f56e div ecx
0064f570 mov eax, dword ptr [ebp - 0x118]
0064f576 add edx, 0x14
0064f579 sub dword ptr [ebp - 0xb0], 1
0064f580 mov dword ptr [eax + 0xcd4], edx
0064f586 jne 0x64f392
0064f58c jmp 0x64f64d
0064f591 call 0x6c3d90
0064f596 and eax, 1
0064f599 add eax, 1
0064f59c mov dword ptr [ebp - 0xb0], eax
0064f5a2 je 0x64f647
0064f5a8 mov esi, dword ptr [ebp - 0xac]
0064f5ae nop 
0064f5b0 movss xmm0, dword ptr [edi + 0x294]
0064f5b8 subss xmm0, dword ptr [edi + 0x2b8]
0064f5c0 mov ecx, dword ptr [esi + 0x298]
0064f5c6 mov eax, dword ptr [esi + 0x294]
0064f5cc push 0
0064f5ce push 0
0064f5d0 movss dword ptr [ebp - 0xd4], xmm0
0064f5d8 movss xmm0, dword ptr [edi + 0x298]
0064f5e0 subss xmm0, dword ptr [edi + 0x2bc]
0064f5e8 push ecx
0064f5e9 mov dword ptr [ebp - 0xe4], eax
0064f5ef lea eax, [ebp - 0xe4]
0064f5f5 mov dword ptr [ebp - 0xe0], ecx
0064f5fb mov ecx, dword ptr [0xbfd65c]
0064f601 mov dword ptr [esp], 0
0064f608 push eax
0064f609 lea eax, [ebp - 0x11c]
0064f60f movss dword ptr [ebp - 0xd0], xmm0
0064f617 mov ecx, dword ptr [ecx + 0x18190]
0064f61d push eax
0064f61e call 0x7cf240
0064f623 inc dword ptr [esi + 0x12c0]
0064f629 lea ecx, [ebp - 0xd4]
0064f62f push eax
0064f630 mov edx, esi
0064f632 call 0x6180f0
0064f637 add esp, 4
0064f63a sub dword ptr [ebp - 0xb0], 1
0064f641 jne 0x64f5b0
0064f647 mov esi, dword ptr [ebp - 0xb8]
0064f64d push 0xbc48a0
0064f652 push 0xbc49a0
0064f657 mov edx, 0xbc4be0
0064f65c lea ecx, [ebp - 0xcc]
0064f662 call 0x427220
0064f667 add esp, 4
0064f66a lea ecx, [ebp - 0x134]
0064f670 mov edx, eax
0064f672 call 0x427220
0064f677 push eax
0064f678 lea edx, [edi + 0x378]
0064f67e lea ecx, [ebp - 0x144]
0064f684 call 0x412050
0064f689 add esp, 8
0064f68c mov ecx, eax
0064f68e call 0x412090
0064f693 test al, al
0064f695 je 0x64f91d
0064f69b push 0
0064f69d push 0x40000000
0064f6a2 mov ecx, esi
0064f6a4 call 0x4122f0
0064f6a9 test al, al
0064f6ab jne 0x64f91d
0064f6b1 movss xmm1, dword ptr [esi + 0x298]
0064f6b9 subss xmm1, dword ptr [edi + 0x298]
0064f6c1 movss xmm2, dword ptr [esi + 0x294]
0064f6c9 subss xmm2, dword ptr [edi + 0x294]
0064f6d1 movaps xmm0, xmm1
0064f6d4 movss dword ptr [ebp - 0xa8], xmm1
0064f6dc mulss xmm0, xmm1
0064f6e0 movss dword ptr [ebp - 0xe0], xmm1
0064f6e8 movaps xmm1, xmm2
0064f6eb mulss xmm1, xmm2
0064f6ef movss dword ptr [ebp - 0xac], xmm2
0064f6f7 movss dword ptr [ebp - 0xe4], xmm2
0064f6ff addss xmm0, xmm1
0064f703 call 0x4228c0
0064f708 comiss xmm0, dword ptr [0xb6a1b8]
0064f70f movss dword ptr [ebp - 0xb0], xmm0
0064f717 jb 0x64f91d
0064f71d movss xmm1, dword ptr [edi + 0x2bc]
0064f725 subss xmm1, dword ptr [esi + 0x2bc]
0064f72d movss xmm2, dword ptr [edi + 0x2b8]
0064f735 subss xmm2, dword ptr [esi + 0x2b8]
0064f73d movaps xmm0, xmm1
0064f740 movss dword ptr [ebp - 0xd0], xmm1
0064f748 mulss xmm0, xmm1
0064f74c movss dword ptr [ebp - 0xf8], xmm1
0064f754 movaps xmm1, xmm2
0064f757 mulss xmm1, xmm2
0064f75b movss dword ptr [ebp - 0x118], xmm2
0064f763 movss dword ptr [ebp - 0xfc], xmm2
0064f76b addss xmm0, xmm1
0064f76f call 0x4228c0
0064f774 movss xmm1, dword ptr [esi + 0x2c8]
0064f77c addss xmm1, dword ptr [edi + 0x2c8]
0064f784 mulss xmm1, dword ptr [0xb6a480]
0064f78c comiss xmm0, xmm1
0064f78f jbe 0x64f861
0064f795 movss xmm1, dword ptr [ebp - 0x118]
0064f79d movss xmm0, dword ptr [ebp - 0xd0]
0064f7a5 mulss xmm1, dword ptr [ebp - 0xac]
0064f7ad mulss xmm0, dword ptr [ebp - 0xa8]
0064f7b5 addss xmm0, xmm1
0064f7b9 xorps xmm1, xmm1
0064f7bc comiss xmm1, xmm0
0064f7bf jbe 0x64f861
0064f7c5 lea eax, [ebp - 0xd4]
0064f7cb push eax
0064f7cc lea ecx, [ebp - 0xe4]
0064f7d2 call 0x962560
0064f7d7 mov esi, eax
0064f7d9 lea ecx, [ebp - 0xfc]
0064f7df lea eax, [ebp - 0xe4]
0064f7e5 push eax
0064f7e6 call 0x962560
0064f7eb movss xmm1, dword ptr [esi + 4]
0064f7f0 movss xmm0, dword ptr [esi]
0064f7f4 movss xmm2, dword ptr [ebp - 0xac]
0064f7fc mulss xmm1, dword ptr [eax + 4]
0064f801 mulss xmm0, dword ptr [eax]
0064f805 addss xmm1, xmm0
0064f809 movaps xmm0, xmm1
0064f80c mulss xmm1, dword ptr [ebp - 0xa8]
0064f814 mulss xmm0, xmm2
0064f818 addss xmm1, xmm1
0064f81c addss xmm0, xmm0
0064f820 addss xmm1, dword ptr [ebp - 0xa8]
0064f828 addss xmm2, xmm0
0064f82c movaps xmm0, xmm1
0064f82f movss dword ptr [ebp - 0xa8], xmm1
0064f837 mulss xmm0, xmm1
0064f83b movaps xmm1, xmm2
0064f83e movss dword ptr [ebp - 0xac], xmm2
0064f846 mulss xmm1, xmm2
0064f84a addss xmm0, xmm1
0064f84e call 0x4228c0
0064f853 mov esi, dword ptr [ebp - 0xb8]
0064f859 movss dword ptr [ebp - 0xb0], xmm0
0064f861 push esi
0064f862 mov ecx, edi
0064f864 call 0x689640
0064f869 movaps xmm1, xmm0
0064f86c mov ecx, esi
0064f86e push edi
0064f86f movss dword ptr [ebp - 0xf8], xmm1
0064f877 call 0x689640
0064f87c movss xmm1, dword ptr [ebp - 0xf8]
0064f884 addss xmm0, xmm1
0064f888 divss xmm1, xmm0
0064f88c movss xmm0, dword ptr [esi + 0x2bc]
0064f894 subss xmm0, dword ptr [edi + 0x2bc]
0064f89c movss dword ptr [ebp - 0xf8], xmm1
0064f8a4 movss xmm1, dword ptr [esi + 0x2b8]
0064f8ac subss xmm1, dword ptr [edi + 0x2b8]
0064f8b4 mulss xmm0, xmm0
0064f8b8 mulss xmm1, xmm1
0064f8bc addss xmm0, xmm1
0064f8c0 call 0x4228c0
0064f8c5 movss xmm2, dword ptr [ebp - 0xac]
0064f8cd divss xmm2, dword ptr [ebp - 0xb0]
0064f8d5 mulss xmm2, xmm0
0064f8d9 mulss xmm2, dword ptr [ebp - 0xf8]
0064f8e1 addss xmm2, dword ptr [esi + 0x2b8]
0064f8e9 movss dword ptr [esi + 0x2b8], xmm2
0064f8f1 movss xmm2, dword ptr [ebp - 0xa8]
0064f8f9 divss xmm2, dword ptr [ebp - 0xb0]
0064f901 mulss xmm2, xmm0
0064f905 mulss xmm2, dword ptr [ebp - 0xf8]
0064f90d addss xmm2, dword ptr [esi + 0x2bc]
0064f915 movss dword ptr [esi + 0x2bc], xmm2
0064f91d mov eax, dword ptr [esi + 0x28]
0064f920 cmp eax, 0xe
0064f923 je 0x64f92e
0064f925 cmp eax, 0x12
0064f928 jne 0x64f9a3
0064f92e push 0xbc49a0
0064f933 mov edx, 0xbc4be0
0064f938 lea ecx, [ebp - 0xcc]
0064f93e call 0x427220
0064f943 push eax
0064f944 lea edx, [edi + 0x378]
0064f94a lea ecx, [ebp - 0x134]
0064f950 call 0x412050
0064f955 add esp, 8
0064f958 mov ecx, eax
0064f95a call 0x427260
0064f95f test al, al
0064f961 je 0x64f9a3
0064f963 movss xmm1, dword ptr [edi + 0x2b8]
0064f96b movss xmm0, dword ptr [edi + 0x2bc]
0064f973 mulss xmm1, dword ptr [0xb6a480]
0064f97b mulss xmm0, dword ptr [0xb6a480]
0064f983 addss xmm1, dword ptr [esi + 0x2b8]
0064f98b addss xmm0, dword ptr [esi + 0x2bc]
0064f993 movss dword ptr [esi + 0x2b8], xmm1
0064f99b movss dword ptr [esi + 0x2bc], xmm0
0064f9a3 movss xmm0, dword ptr [edi + 0x2e0]
0064f9ab lea edx, [edi + 0x294]
0064f9b1 push ecx
0064f9b2 movss dword ptr [esp], xmm0
0064f9b7 mov ecx, esi
0064f9b9 movups xmm0, xmmword ptr [edi + 0x378]
0064f9c0 push edi
0064f9c1 sub esp, 0x10
0064f9c4 mov eax, esp
0064f9c6 movups xmmword ptr [eax], xmm0
0064f9c9 call 0x654de0
0064f9ce add esp, 0x18
0064f9d1 cmp dword ptr [edi + 0x2c], 0x2d
0064f9d5 jne 0x64fad2
0064f9db push 0
0064f9dd mov ecx, esi
0064f9df call 0x684630
0064f9e4 test al, al
0064f9e6 je 0x64fad2
0064f9ec mov eax, dword ptr [esi]
0064f9ee mov ecx, esi
0064f9f0 mov eax, dword ptr [eax + 0x48]
0064f9f3 call eax
0064f9f5 test al, al
0064f9f7 je 0x64fa0b
0064f9f9 movss xmm0, dword ptr [esi + 0x14]
0064f9fe comiss xmm0, dword ptr [esi + 0x2d8]
0064fa05 jb 0x64fad2
0064fa0b push esi
0064fa0c mov byte ptr [ebp - 0xb9], 0
0064fa13 call 0x6d9420
0064fa18 mov eax, dword ptr [0xbfd65c]
0064fa1d mov eax, dword ptr [eax + 0x18190]
0064fa23 cmp dword ptr [eax + 0x1264], 0
0064fa2a jbe 0x64fad2
0064fa30 xor esi, esi
0064fa32 mov edi, eax
0064fa34 mov eax, dword ptr [edi + 0x125c]
0064fa3a mov eax, dword ptr [eax + esi*4]
0064fa3d push eax
0064fa3e mov dword ptr [ebp - 0xd0], eax
0064fa44 call 0x6d94d0
0064fa49 test al, al
0064fa4b je 0x64fa63
0064fa4d push ecx
0064fa4e push dword ptr [ebp - 0xd0]
0064fa54 call 0x6d9590
0064fa59 mov al, 1
0064fa5b mov byte ptr [ebp - 0xb9], al
0064fa61 jmp 0x64fa69
0064fa63 mov al, byte ptr [ebp - 0xb9]
0064fa69 inc esi
0064fa6a cmp esi, dword ptr [edi + 0x1264]
0064fa70 jb 0x64fa34
0064fa72 mov edi, dword ptr [ebp - 0xf0]
0064fa78 mov esi, dword ptr [ebp - 0xb8]
0064fa7e test al, al
0064fa80 je 0x64fad2
0064fa82 mov esi, dword ptr [0xbfd680]
0064fa88 lea ecx, [ebp - 0xf0]
0064fa8e mov dword ptr [ebp - 0xf0], 0xed
0064fa98 call 0x8b1340
0064fa9d sub esp, 8
0064faa0 mov dword ptr [esp + 4], 0
0064faa8 mov dword ptr [esp], 0x3f800000
0064faaf push 0
0064fab1 push 2
0064fab3 push ecx
0064fab4 mov dword ptr [esp], 0x3f800000
0064fabb lea ecx, [esi + 0x29de0]
0064fac1 push dword ptr [ebp - 0xf0]
0064fac7 call 0x888de0
0064facc mov esi, dword ptr [ebp - 0xb8]
0064fad2 push 0xbc46f0
0064fad7 lea edx, [edi + 0x378]
0064fadd lea ecx, [ebp - 0xcc]
0064fae3 call 0x412050
0064fae8 add esp, 4
0064faeb mov ecx, eax
0064faed call 0x412090
0064faf2 test al, al
0064faf4 je 0x64fb18
0064faf6 push 0
0064faf8 mov ecx, esi
0064fafa call 0x684630
0064faff test al, al
0064fb01 je 0x64fb18
0064fb03 mov eax, dword ptr [esi]
0064fb05 mov ecx, esi
0064fb07 mov eax, dword ptr [eax + 0x48]
0064fb0a call eax
0064fb0c test al, al
0064fb0e jne 0x64fb18
0064fb10 push ecx
0064fb11 mov ecx, esi
0064fb13 call 0x68c810
0064fb18 cmp byte ptr [ebp - 0xb1], 0
0064fb1f je 0x64fb9c
0064fb25 or dword ptr [edi + 0x3c4], 0x28
0064fb2c lea edx, [edi + 0x378]
0064fb32 push 0xbc4ce0
0064fb37 lea ecx, [ebp - 0xcc]
0064fb3d mov byte ptr [edi + 0x16b], 1
0064fb44 call 0x412050
0064fb49 add esp, 4
0064fb4c mov ecx, eax
0064fb4e call 0x412090
0064fb53 test al, al
0064fb55 je 0x65008f
0064fb5b mov ecx, edi
0064fb5d call 0x6520e0
0064fb62 test al, al
0064fb64 je 0x65008f
0064fb6a mov eax, dword ptr [edi + 0x318]
0064fb70 mov dword ptr [ebp - 0xd0], eax
0064fb76 test eax, eax
0064fb78 je 0x65008f
0064fb7e mov esi, eax
0064fb80 mov eax, dword ptr [esi]
0064fb82 mov ecx, esi
0064fb84 call dword ptr [eax + 0x24]
0064fb87 mov esi, dword ptr [esi + 0x318]
0064fb8d test esi, esi
0064fb8f jne 0x64fb80
0064fb91 mov esi, dword ptr [ebp - 0xb8]
0064fb97 jmp 0x65008f
0064fb9c push esi
0064fb9d mov ecx, edi
0064fb9f call 0x650dd0
0064fba4 push 0xbc4990
0064fba9 lea edx, [edi + 0x378]
0064fbaf lea ecx, [ebp - 0xcc]
0064fbb5 call 0x412050
0064fbba add esp, 4
0064fbbd mov ecx, eax
0064fbbf call 0x412090
0064fbc4 test al, al
0064fbc6 je 0x64fceb
0064fbcc lea eax, [ebp - 0xcc]
0064fbd2 mov ecx, 0xbc4990
0064fbd7 push eax
0064fbd8 call 0x57f3a0
0064fbdd mov edx, eax
0064fbdf mov ecx, dword ptr [edx]
0064fbe1 and dword ptr [edi + 0x378], ecx
0064fbe7 mov ecx, dword ptr [edx + 4]
0064fbea and dword ptr [edi + 0x37c], ecx
0064fbf0 mov eax, dword ptr [edx + 8]
0064fbf3 and dword ptr [edi + 0x380], eax
0064fbf9 mov eax, dword ptr [edx + 0xc]
0064fbfc lea edx, [edi + 0x378]
0064fc02 and dword ptr [edx + 0xc], eax
0064fc05 mov esi, dword ptr [edi + 0x378]
0064fc0b or esi, dword ptr [0xbc4cb0]
0064fc11 mov eax, dword ptr [0xbc4cb4]
0064fc16 or dword ptr [edx + 4], eax
0064fc19 mov ecx, dword ptr [edx + 8]
0064fc1c mov dword ptr [edx], esi
0064fc1e or ecx, dword ptr [0xbc4cb8]
0064fc24 mov eax, dword ptr [0xbc4cbc]
0064fc29 or dword ptr [edx + 0xc], eax
0064fc2c mov dword ptr [edx + 8], ecx
0064fc2f mov eax, dword ptr [edi + 0x2c]
0064fc32 cmp eax, 0x23
0064fc35 je 0x64fc50
0064fc37 cmp eax, 0x25
0064fc3a je 0x64fc50
0064fc3c cmp eax, 0x26
0064fc3f je 0x64fc50
0064fc41 push 0x20
0064fc43 mov ecx, edi
0064fc45 call 0x654270
0064fc4a lea edx, [edi + 0x378]
0064fc50 movss xmm0, dword ptr [edi + 0x2e0]
0064fc58 lea ecx, [ebp - 0xcc]
0064fc5e addss xmm0, xmm0
0064fc62 push 0xbc4ce0
0064fc67 movss dword ptr [edi + 0x2e0], xmm0
0064fc6f call 0x412050
0064fc74 add esp, 4
0064fc77 mov ecx, eax
0064fc79 call 0x427260
0064fc7e test al, al
0064fc80 je 0x64fcb9
0064fc82 movss xmm0, dword ptr [edi + 0x374]
0064fc8a mov ecx, edi
0064fc8c mulss xmm0, dword ptr [0xb6a690]
0064fc94 minss xmm0, dword ptr [0xb6aa18]
0064fc9c maxss xmm0, dword ptr [0xb6a214]
0064fca4 movss dword ptr [edi + 0x374], xmm0
0064fcac movss dword ptr [edi + 0x370], xmm0
0064fcb4 call 0x651770
0064fcb9 movss xmm0, dword ptr [edi + 0x3b4]
0064fcc1 movss xmm1, dword ptr [0xb6a3b0]
0064fcc9 comiss xmm0, xmm1
0064fccc ja 0x64fcd4
0064fcce movss xmm0, xmm1
0064fcd2 jmp 0x64fcd8
0064fcd4 movss xmm0, xmm0
0064fcd8 push ecx
0064fcd9 mov ecx, edi
0064fcdb movss dword ptr [esp], xmm0
0064fce0 call 0x653e00
0064fce5 mov esi, dword ptr [ebp - 0xb8]
0064fceb push 0xbc48a0
0064fcf0 lea edx, [edi + 0x378]
0064fcf6 lea ecx, [ebp - 0xcc]
0064fcfc call 0x412050
0064fd01 add esp, 4
0064fd04 mov ecx, eax
0064fd06 call 0x412090
0064fd0b test al, al
0064fd0d jne 0x64fe00
0064fd13 push 0xbc4c10
0064fd18 lea edx, [edi + 0x378]
0064fd1e lea ecx, [ebp - 0xcc]
0064fd24 call 0x412050
0064fd29 add esp, 4
0064fd2c mov ecx, eax
0064fd2e call 0x412090
0064fd33 test al, al
0064fd35 je 0x64fe0c
0064fd3b push 0xbc4be0
0064fd40 lea edx, [edi + 0x378]
0064fd46 lea ecx, [ebp - 0xcc]
0064fd4c call 0x412050
0064fd51 add esp, 4
0064fd54 mov ecx, eax
0064fd56 call 0x412090
0064fd5b test al, al
0064fd5d je 0x64fd77
0064fd5f mov ecx, esi
0064fd61 call 0x6846e0
0064fd66 test al, al
0064fd68 jne 0x64fd77
0064fd6a call 0x6c3d90
0064fd6f test al, 3
0064fd71 jne 0x64fe0c
0064fd77 movss xmm1, dword ptr [edi + 0x2bc]
0064fd7f movss xmm0, dword ptr [edi + 0x2b8]
0064fd87 mulss xmm0, xmm0
0064fd8b mulss xmm1, xmm1
0064fd8f addss xmm0, xmm1
0064fd93 call 0x4228c0
0064fd98 lea eax, [ebp - 0xe4]
0064fd9e movss dword ptr [ebp - 0xd0], xmm0
0064fda6 push eax
0064fda7 call 0x659290
0064fdac movss xmm0, dword ptr [ebp - 0xd0]
0064fdb4 add esp, 4
0064fdb7 movaps xmm1, xmm0
0064fdba mov ecx, 0xbc46a0
0064fdbf mulss xmm1, dword ptr [eax]
0064fdc3 mulss xmm0, dword ptr [eax + 4]
0064fdc8 lea eax, [ebp - 0xcc]
0064fdce push eax
0064fdcf movss dword ptr [edi + 0x2b8], xmm1
0064fdd7 movss dword ptr [edi + 0x2bc], xmm0
0064fddf call 0x57f3a0
0064fde4 lea edx, [edi + 0x378]
0064fdea mov ecx, dword ptr [eax]
0064fdec and dword ptr [edx], ecx
0064fdee mov ecx, dword ptr [eax + 4]
0064fdf1 and dword ptr [edx + 4], ecx
0064fdf4 mov ecx, dword ptr [eax + 8]
0064fdf7 and dword ptr [edx + 8], ecx
0064fdfa mov eax, dword ptr [eax + 0xc]
0064fdfd and dword ptr [edx + 0xc], eax
0064fe00 mov byte ptr [edi + 0x738], 0
0064fe07 jmp 0x64dde9
0064fe0c push 0xbc49a0
0064fe11 lea edx, [edi + 0x378]
0064fe17 lea ecx, [ebp - 0xcc]
0064fe1d call 0x412050
0064fe22 add esp, 4
0064fe25 mov ecx, eax
0064fe27 call 0x412090
0064fe2c test al, al
0064fe2e je 0x64ffb1
0064fe34 push 0xbc4be0
0064fe39 lea edx, [edi + 0x378]
0064fe3f lea ecx, [ebp - 0xcc]
0064fe45 call 0x412050
0064fe4a add esp, 4
0064fe4d mov ecx, eax
0064fe4f call 0x412090
0064fe54 test al, al
0064fe56 je 0x64fe67
0064fe58 mov ecx, esi
0064fe5a call 0x6846e0
0064fe5f test al, al
0064fe61 je 0x64ffb1
0064fe67 push 0xbc4ce0
0064fe6c lea edx, [edi + 0x378]
0064fe72 lea ecx, [ebp - 0xcc]
0064fe78 call 0x412050
0064fe7d add esp, 4
0064fe80 mov ecx, eax
0064fe82 call 0x427260
0064fe87 test al, al
0064fe89 je 0x64ffb1
0064fe8f push 0xbc4cc0
0064fe94 lea edx, [edi + 0x378]
0064fe9a lea ecx, [ebp - 0xcc]
0064fea0 call 0x412050
0064fea5 add esp, 4
0064fea8 mov ecx, eax
0064feaa call 0x412090
0064feaf test al, al
0064feb1 je 0x64fec2
0064feb3 mov ecx, esi
0064feb5 call 0x6846e0
0064feba test al, al
0064febc jne 0x64ffb1
0064fec2 push 0
0064fec4 push 0xbeab70
0064fec9 push 0xbeab18
0064fece push 0
0064fed0 push esi
0064fed1 call 0x9ec34c
0064fed6 movss xmm0, dword ptr [edi + 0x2e0]
0064fede add esp, 0x14
0064fee1 comiss xmm0, dword ptr [esi + 0x2d8]
0064fee8 jbe 0x64ff58
0064feee test eax, eax
0064fef0 je 0x64ff09
0064fef2 push dword ptr [edi + 0x2bc]
0064fef8 mov ecx, eax
0064fefa push dword ptr [edi + 0x2b8]
0064ff00 call 0x6aa830
0064ff05 test al, al
0064ff07 je 0x64ff58
0064ff09 movss xmm0, dword ptr [edi + 0x2e0]
0064ff11 mov ecx, edi
0064ff13 movaps xmm1, xmm0
0064ff16 subss xmm1, dword ptr [esi + 0x2d8]
0064ff1e movss dword ptr [edi + 0x2e0], xmm1
0064ff26 mulss xmm1, dword ptr [edi + 0x374]
0064ff2e divss xmm1, xmm0
0064ff32 maxss xmm1, dword ptr [0xb6a214]
0064ff3a movss dword ptr [edi + 0x374], xmm1
0064ff42 movss dword ptr [edi + 0x370], xmm1
0064ff4a call 0x651770
0064ff4f mov byte ptr [edi + 0x738], 0
0064ff56 jmp 0x64ff66
0064ff58 or dword ptr [edi + 0x3c4], 8
0064ff5f mov byte ptr [edi + 0x16b], 1
0064ff66 mov edi, dword ptr [edi + 0x314]
0064ff6c test edi, edi
0064ff6e je 0x64dde9
0064ff74 push 0
0064ff76 mov ecx, esi
0064ff78 call 0x68cf40
0064ff7d test al, al
0064ff7f je 0x64dde9
0064ff85 cmp dword ptr [edi + 0x28], 1
0064ff89 jne 0x64dde9
0064ff8f push 0
0064ff91 push 0x175
0064ff96 mov ecx, edi
0064ff98 call 0x73af30
0064ff9d test al, al
0064ff9f je 0x64dde9
0064ffa5 mov ecx, edi
0064ffa7 call 0x78a6f0
0064ffac jmp 0x64dde9
0064ffb1 push 0xbc4be0
0064ffb6 lea edx, [edi + 0x378]
0064ffbc lea ecx, [ebp - 0xcc]
0064ffc2 call 0x412050
0064ffc7 add esp, 4
0064ffca mov ecx, eax
0064ffcc call 0x412090
0064ffd1 test al, al
0064ffd3 je 0x64ffe4
0064ffd5 mov ecx, esi
0064ffd7 call 0x6846e0
0064ffdc test al, al
0064ffde je 0x64dde9
0064ffe4 push 0xbc4ce0
0064ffe9 lea edx, [edi + 0x378]
0064ffef lea ecx, [ebp - 0xcc]
0064fff5 call 0x412050
0064fffa add esp, 4
0064fffd mov ecx, eax
0064ffff call 0x427260
00650004 test al, al
00650006 je 0x64dde9
0065000c push 0xbc4cc0
00650011 lea edx, [edi + 0x378]
00650017 lea ecx, [ebp - 0x144]
0065001d call 0x412050
00650022 add esp, 4
00650025 mov ecx, eax
00650027 call 0x412090
0065002c test al, al
0065002e je 0x65003f
00650030 mov ecx, esi
00650032 call 0x6846e0
00650037 test al, al
00650039 jne 0x64dde9
0065003f cmp dword ptr [edi + 0x2c], 9
00650043 je 0x64dde9
00650049 movss xmm0, dword ptr [esi + 0x2b8]
00650051 lea eax, [edi + 0x294]
00650057 movss xmm1, dword ptr [esi + 0x2bc]
0065005f mulss xmm0, dword ptr [0xb6a560]
00650067 or dword ptr [edi + 0x3c4], 8
0065006e mulss xmm1, dword ptr [0xb6a560]
00650076 mov byte ptr [edi + 0x16b], 1
0065007d addss xmm0, dword ptr [eax]
00650081 addss xmm1, dword ptr [eax + 4]
00650086 movss dword ptr [eax], xmm0
0065008a movss dword ptr [eax + 4], xmm1
0065008f mov edi, dword ptr [edi + 0x314]
00650095 test edi, edi
00650097 je 0x6500c5
00650099 push 0
0065009b mov ecx, esi
0065009d call 0x68cf40
006500a2 test al, al
006500a4 je 0x6500c5
006500a6 cmp dword ptr [edi + 0x28], 1
006500aa jne 0x6500c5
006500ac push 0
006500ae push 0x175
006500b3 mov ecx, edi
006500b5 call 0x73af30
006500ba test al, al
006500bc je 0x6500c5
006500be mov ecx, edi
006500c0 call 0x78a6f0
006500c5 xor al, al
006500c7 jmp 0x64ddeb
006500cc int3 
006500cd int3 
006500ce int3 
006500cf int3 
