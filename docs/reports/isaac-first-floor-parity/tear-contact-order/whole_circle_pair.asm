00689cf0 push ebx
00689cf1 mov ebx, esp
00689cf3 sub esp, 8
00689cf6 and esp, 0xfffffff8
00689cf9 add esp, 4
00689cfc push ebp
00689cfd mov ebp, dword ptr [ebx + 4]
00689d00 mov dword ptr [esp + 4], ebp
00689d04 mov ebp, esp
00689d06 sub esp, 0x38
00689d09 mov eax, dword ptr [edx + 0x28]
00689d0c movss xmm4, dword ptr [0xb6c980]
00689d14 push esi
00689d15 push edi
00689d16 mov edi, ecx
00689d18 mov ecx, edx
00689d1a cmp dword ptr [edi + 0x28], eax
00689d1d cmovle ecx, edi
00689d20 cmovle edi, edx
00689d23 mov esi, ecx
00689d25 mov dword ptr [ebp - 0x20], ecx
00689d28 movss xmm3, dword ptr [edi + 0x294]
00689d30 subss xmm3, dword ptr [esi + 0x294]
00689d38 movss xmm1, dword ptr [edi + 0x2c8]
00689d40 movss xmm2, dword ptr [edi + 0x298]
00689d48 addss xmm1, dword ptr [esi + 0x2c8]
00689d50 subss xmm2, dword ptr [esi + 0x298]
00689d58 movaps xmm0, xmm3
00689d5b movss dword ptr [ebp - 4], xmm3
00689d60 andps xmm0, xmm4
00689d63 movss dword ptr [ebp - 0x38], xmm3
00689d68 comiss xmm0, xmm1
00689d6b movss dword ptr [ebp - 8], xmm2
00689d70 movss dword ptr [ebp - 0x34], xmm2
00689d75 movss dword ptr [ebp - 0xc], xmm1
00689d7a ja 0x68a2b5
00689d80 movaps xmm0, xmm2
00689d83 andps xmm0, xmm4
00689d86 comiss xmm0, xmm1
00689d89 ja 0x68a2b5
00689d8f movaps xmm0, xmm2
00689d92 movaps xmm1, xmm3
00689d95 mulss xmm0, xmm2
00689d99 mulss xmm1, xmm3
00689d9d addss xmm0, xmm1
00689da1 call 0x4228c0
00689da6 comiss xmm0, dword ptr [ebp - 0xc]
00689daa movss dword ptr [ebp - 0x18], xmm0
00689daf jae 0x68a2b5
00689db5 mov edx, edi
00689db7 mov ecx, esi
00689db9 call 0x689840
00689dbe test al, al
00689dc0 jne 0x68a2b5
00689dc6 cmp dword ptr [edi + 0x28], 2
00689dca movss xmm0, dword ptr [0xb6a1b8]
00689dd2 setne al
00689dd5 cmp dword ptr [esi + 0x28], 2
00689dd9 mov byte ptr [esi + 0x184], al
00689ddf setne al
00689de2 comiss xmm0, dword ptr [ebp - 0x18]
00689de6 mov byte ptr [edi + 0x184], al
00689dec ja 0x68a2aa
00689df2 movss xmm1, dword ptr [esi + 0x2bc]
00689dfa subss xmm1, dword ptr [edi + 0x2bc]
00689e02 movss xmm2, dword ptr [esi + 0x2b8]
00689e0a subss xmm2, dword ptr [edi + 0x2b8]
00689e12 movaps xmm0, xmm1
00689e15 movss dword ptr [ebp - 0x1c], xmm1
00689e1a mulss xmm0, xmm1
00689e1e movss dword ptr [ebp - 0x2c], xmm1
00689e23 movaps xmm1, xmm2
00689e26 mulss xmm1, xmm2
00689e2a movss dword ptr [ebp - 0x24], xmm2
00689e2f movss dword ptr [ebp - 0x30], xmm2
00689e34 addss xmm0, xmm1
00689e38 call 0x4228c0
00689e3d movss xmm1, dword ptr [ebp - 0xc]
00689e42 mulss xmm1, dword ptr [0xb6a480]
00689e4a comiss xmm0, xmm1
00689e4d jbe 0x689ef1
00689e53 movss xmm1, dword ptr [ebp - 0x1c]
00689e58 movss xmm0, dword ptr [ebp - 0x24]
00689e5d mulss xmm1, dword ptr [ebp - 8]
00689e62 mulss xmm0, dword ptr [ebp - 4]
00689e67 addss xmm0, xmm1
00689e6b xorps xmm1, xmm1
00689e6e comiss xmm1, xmm0
00689e71 jbe 0x689ef1
00689e73 lea eax, [ebp - 0x28]
00689e76 push eax
00689e77 lea ecx, [ebp - 0x38]
00689e7a call 0x962560
00689e7f mov esi, eax
00689e81 lea ecx, [ebp - 0x30]
00689e84 lea eax, [ebp - 0x38]
00689e87 push eax
00689e88 call 0x962560
00689e8d movss xmm0, dword ptr [esi]
00689e91 movss xmm3, dword ptr [ebp - 4]
00689e96 mulss xmm0, dword ptr [eax]
00689e9a movss xmm1, dword ptr [eax + 4]
00689e9f mulss xmm1, dword ptr [esi + 4]
00689ea4 addss xmm1, xmm0
00689ea8 movaps xmm0, xmm1
00689eab mulss xmm1, dword ptr [ebp - 8]
00689eb0 mulss xmm0, xmm3
00689eb4 addss xmm1, xmm1
00689eb8 addss xmm0, xmm0
00689ebc addss xmm1, dword ptr [ebp - 8]
00689ec1 addss xmm3, xmm0
00689ec5 movaps xmm0, xmm1
00689ec8 movss dword ptr [ebp - 8], xmm1
00689ecd mulss xmm0, xmm1
00689ed1 movaps xmm1, xmm3
00689ed4 movss dword ptr [ebp - 4], xmm3
00689ed9 mulss xmm1, xmm3
00689edd addss xmm0, xmm1
00689ee1 call 0x4228c0
00689ee6 mov esi, dword ptr [ebp - 0x20]
00689ee9 movaps xmm1, xmm0
00689eec movss dword ptr [ebp - 0x18], xmm1
00689ef1 push edi
00689ef2 mov ecx, esi
00689ef4 call 0x689640
00689ef9 movaps xmm1, xmm0
00689efc mov ecx, edi
00689efe push esi
00689eff movss dword ptr [ebp - 0x14], xmm1
00689f04 call 0x689640
00689f09 movss xmm1, dword ptr [ebp - 0x14]
00689f0e movss xmm3, dword ptr [ebp - 0xc]
00689f13 addss xmm0, xmm1
00689f17 subss xmm3, dword ptr [ebp - 0x18]
00689f1c movss xmm2, dword ptr [0xb6a614]
00689f24 mov eax, dword ptr [esi + 0x28]
00689f27 divss xmm1, xmm0
00689f2b divss xmm3, dword ptr [ebp - 0x18]
00689f30 movss dword ptr [ebp - 0x14], xmm1
00689f35 subss xmm2, xmm1
00689f39 movss dword ptr [ebp - 0xc], xmm3
00689f3e movss dword ptr [ebp - 0x10], xmm2
00689f43 cmp eax, 1
00689f46 je 0x689f53
00689f48 cmp eax, 3
00689f4b jne 0x689fb0
00689f4d cmp dword ptr [esi + 0x2c], 0x43
00689f51 jne 0x689fb0
00689f53 movss xmm0, dword ptr [ebp - 4]
00689f58 lea eax, [ebp - 0x38]
00689f5b xorps xmm0, xmmword ptr [0xb6c9b0]
00689f62 mov ecx, esi
00689f64 mulss xmm0, xmm2
00689f68 push eax
00689f69 mulss xmm0, xmm3
00689f6d movss dword ptr [ebp - 0x38], xmm0
00689f72 movss xmm0, dword ptr [ebp - 8]
00689f77 xorps xmm0, xmmword ptr [0xb6c9b0]
00689f7e mulss xmm0, xmm2
00689f82 mulss xmm0, xmm3
00689f86 movss dword ptr [ebp - 0x34], xmm0
00689f8b call 0x683650
00689f90 test al, al
00689f92 je 0x689fab
00689f94 movss xmm0, dword ptr [0xb6a614]
00689f9c xorps xmm2, xmm2
00689f9f movss dword ptr [ebp - 0x10], xmm2
00689fa4 movss dword ptr [ebp - 0x14], xmm0
00689fa9 jmp 0x689fb0
00689fab movss xmm2, dword ptr [ebp - 0x10]
00689fb0 cmp dword ptr [esi + 0x28], 1
00689fb4 jne 0x689fc3
00689fb6 mulss xmm2, dword ptr [0xb6a480]
00689fbe movss dword ptr [ebp - 0x10], xmm2
00689fc3 movss xmm1, dword ptr [edi + 0x2b8]
00689fcb movss xmm0, dword ptr [edi + 0x2bc]
00689fd3 subss xmm0, dword ptr [esi + 0x2bc]
00689fdb subss xmm1, dword ptr [esi + 0x2b8]
00689fe3 mulss xmm0, xmm0
00689fe7 mulss xmm1, xmm1
00689feb addss xmm0, xmm1
00689fef call 0x4228c0
00689ff4 cmp dword ptr [esi + 0x28], 0x393
00689ffb movaps xmm2, xmm0
00689ffe movss xmm1, dword ptr [ebp - 0x18]
0068a003 movss xmm0, dword ptr [ebp - 4]
0068a008 divss xmm0, xmm1
0068a00c movss dword ptr [ebp - 0x34], xmm2
0068a011 mulss xmm0, xmm2
0068a015 movss dword ptr [ebp - 0x18], xmm0
0068a01a movss xmm0, dword ptr [ebp - 8]
0068a01f divss xmm0, xmm1
0068a023 mulss xmm0, xmm2
0068a027 movss dword ptr [ebp - 0x1c], xmm0
0068a02c jne 0x68a0ef
0068a032 cmp dword ptr [esi + 0x2c], 1
0068a036 jne 0x68a0ef
0068a03c cmp dword ptr [edi + 0x28], 0x393
0068a043 jne 0x68a0ef
0068a049 cmp dword ptr [edi + 0x2c], 1
0068a04d jne 0x68a0ef
0068a053 call 0x6c3d90
0068a058 mov esi, dword ptr [0xbfd680]
0068a05e lea ecx, [ebp - 0x24]
0068a061 mov dword ptr [ebp - 0x24], 0x1e7
0068a068 movd xmm0, eax
0068a06c cvtdq2pd xmm0, xmm0
0068a070 shr eax, 0x1f
0068a073 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
0068a07c cvtpd2ps xmm0, xmm0
0068a080 mulss xmm0, dword ptr [0xb6a19c]
0068a088 movss dword ptr [ebp - 0x2c], xmm0
0068a08d call 0x8b1340
0068a092 movss xmm1, dword ptr [ebp - 0x2c]
0068a097 sub esp, 8
0068a09a mulss xmm1, dword ptr [0xb6a350]
0068a0a2 mov dword ptr [esp + 4], 0
0068a0aa addss xmm1, dword ptr [0xb6a5a4]
0068a0b2 movss dword ptr [esp], xmm1
0068a0b7 movss xmm1, dword ptr [ebp - 0x34]
0068a0bc mulss xmm1, dword ptr [0xb6a274]
0068a0c4 push 0
0068a0c6 push 2
0068a0c8 push ecx
0068a0c9 addss xmm1, dword ptr [0xb6a350]
0068a0d1 lea ecx, [esi + 0x29de0]
0068a0d7 minss xmm1, dword ptr [0xb6a670]
0068a0df movss dword ptr [esp], xmm1
0068a0e4 push dword ptr [ebp - 0x24]
0068a0e7 call 0x888de0
0068a0ec mov esi, dword ptr [ebp - 0x20]
0068a0ef push 0
0068a0f1 push 0x40000000
0068a0f6 mov ecx, esi
0068a0f8 call 0x4122f0
0068a0fd movss xmm3, dword ptr [0xb6a38c]
0068a105 test al, al
0068a107 jne 0x68a1d3
0068a10d mov ecx, dword ptr [0xbfd65c]
0068a113 mov ecx, dword ptr [ecx + 0x18190]
0068a119 call 0x7e2590
0068a11e test al, al
0068a120 je 0x68a152
0068a122 cmp dword ptr [esi + 0x28], 1
0068a126 jne 0x68a152
0068a128 movss xmm1, dword ptr [ebp - 0x18]
0068a12d movss xmm0, dword ptr [esi + 0x2b8]
0068a135 mulss xmm1, xmm3
0068a139 mulss xmm1, dword ptr [ebp - 0x10]
0068a13e subss xmm0, xmm1
0068a142 movss xmm1, dword ptr [ebp - 0x1c]
0068a147 mulss xmm1, xmm3
0068a14b mulss xmm1, dword ptr [ebp - 0x10]
0068a150 jmp 0x68a1b7
0068a152 movss xmm2, dword ptr [ebp - 0x10]
0068a157 movss xmm0, dword ptr [esi + 0x294]
0068a15f movaps xmm1, xmm2
0068a162 mulss xmm1, dword ptr [ebp - 4]
0068a167 mulss xmm1, dword ptr [ebp - 0xc]
0068a16c subss xmm0, xmm1
0068a170 movaps xmm1, xmm2
0068a173 mulss xmm1, dword ptr [ebp - 8]
0068a178 mulss xmm1, dword ptr [ebp - 0xc]
0068a17d movss dword ptr [esi + 0x294], xmm0
0068a185 movss xmm0, dword ptr [esi + 0x298]
0068a18d subss xmm0, xmm1
0068a191 movss xmm1, dword ptr [ebp - 0x18]
0068a196 mulss xmm1, xmm2
0068a19a movss dword ptr [esi + 0x298], xmm0
0068a1a2 movss xmm0, dword ptr [esi + 0x2b8]
0068a1aa subss xmm0, xmm1
0068a1ae movss xmm1, dword ptr [ebp - 0x1c]
0068a1b3 mulss xmm1, xmm2
0068a1b7 movss dword ptr [esi + 0x2b8], xmm0
0068a1bf movss xmm0, dword ptr [esi + 0x2bc]
0068a1c7 subss xmm0, xmm1
0068a1cb movss dword ptr [esi + 0x2bc], xmm0
0068a1d3 push 0
0068a1d5 push 0x40000000
0068a1da mov ecx, edi
0068a1dc call 0x4122f0
0068a1e1 test al, al
0068a1e3 jne 0x68a2aa
0068a1e9 mov eax, dword ptr [0xbfd65c]
0068a1ee mov ecx, dword ptr [eax + 0x18190]
0068a1f4 call 0x7e2590
0068a1f9 test al, al
0068a1fb je 0x68a239
0068a1fd cmp dword ptr [edi + 0x28], 1
0068a201 jne 0x68a239
0068a203 movss xmm0, dword ptr [ebp - 0x18]
0068a208 mulss xmm0, dword ptr [0xb6a38c]
0068a210 mulss xmm0, dword ptr [ebp - 0x14]
0068a215 addss xmm0, dword ptr [edi + 0x2b8]
0068a21d movss dword ptr [edi + 0x2b8], xmm0
0068a225 movss xmm0, dword ptr [ebp - 0x1c]
0068a22a mulss xmm0, dword ptr [0xb6a38c]
0068a232 mulss xmm0, dword ptr [ebp - 0x14]
0068a237 jmp 0x68a29a
0068a239 movss xmm2, dword ptr [ebp - 0x14]
0068a23e movaps xmm0, xmm2
0068a241 mulss xmm0, dword ptr [ebp - 4]
0068a246 mulss xmm0, dword ptr [ebp - 0xc]
0068a24b addss xmm0, dword ptr [edi + 0x294]
0068a253 movss dword ptr [edi + 0x294], xmm0
0068a25b movaps xmm0, xmm2
0068a25e mulss xmm0, dword ptr [ebp - 8]
0068a263 mulss xmm0, dword ptr [ebp - 0xc]
0068a268 addss xmm0, dword ptr [edi + 0x298]
0068a270 movss dword ptr [edi + 0x298], xmm0
0068a278 movss xmm0, dword ptr [ebp - 0x18]
0068a27d mulss xmm0, xmm2
0068a281 addss xmm0, dword ptr [edi + 0x2b8]
0068a289 movss dword ptr [edi + 0x2b8], xmm0
0068a291 movss xmm0, dword ptr [ebp - 0x1c]
0068a296 mulss xmm0, xmm2
0068a29a addss xmm0, dword ptr [edi + 0x2bc]
0068a2a2 movss dword ptr [edi + 0x2bc], xmm0
0068a2aa mov al, 1
0068a2ac pop edi
0068a2ad pop esi
0068a2ae mov esp, ebp
0068a2b0 pop ebp
0068a2b1 mov esp, ebx
0068a2b3 pop ebx
0068a2b4 ret 
0068a2b5 pop edi
0068a2b6 xor al, al
0068a2b8 pop esi
0068a2b9 mov esp, ebp
0068a2bb pop ebp
0068a2bc mov esp, ebx
0068a2be pop ebx
0068a2bf ret 
