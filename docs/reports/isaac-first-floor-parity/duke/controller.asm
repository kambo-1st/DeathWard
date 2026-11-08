0045dd40 push ebx
0045dd41 mov ebx, esp
0045dd43 sub esp, 8
0045dd46 and esp, 0xfffffff8
0045dd49 add esp, 4
0045dd4c push ebp
0045dd4d mov ebp, dword ptr [ebx + 4]
0045dd50 mov dword ptr [esp + 4], ebp
0045dd54 mov ebp, esp
0045dd56 push -1
0045dd58 push 0x9edac6
0045dd5d mov eax, dword ptr fs:[0]
0045dd63 push eax
0045dd64 push ebx
0045dd65 sub esp, 0x320
0045dd6b mov eax, dword ptr [0xbaa3b4]
0045dd70 xor eax, ebp
0045dd72 mov dword ptr [ebp - 0x14], eax
0045dd75 push esi
0045dd76 push edi
0045dd77 push eax
0045dd78 lea eax, [ebp - 0xc]
0045dd7b mov dword ptr fs:[0], eax
0045dd81 mov edi, ecx
0045dd83 mov dword ptr [ebp - 0x254], edi
0045dd89 mov ecx, dword ptr [0xbfd65c]
0045dd8f lea esi, [edi + 0x294]
0045dd95 sub esp, 0xc
0045dd98 mov dword ptr [edi + 0x17c], 3
0045dda2 lea eax, [ebp - 0x320]
0045dda8 mov dword ptr [ebp - 0x258], esi
0045ddae xorps xmm3, xmm3
0045ddb1 mov ecx, dword ptr [ecx + 0x18190]
0045ddb7 mov dword ptr [esp + 8], 0
0045ddbf mov dword ptr [esp + 4], 0
0045ddc7 mov dword ptr [esp], 0x42200000
0045ddce push esi
0045ddcf push eax
0045ddd0 call 0x7cec10
0045ddd5 mov edx, dword ptr [0xbfd65c]
0045dddb movss xmm1, dword ptr [0xb6ae44]
0045dde3 movss xmm0, dword ptr [eax]
0045dde7 movss dword ptr [esi], xmm0
0045ddeb mov eax, dword ptr [eax + 4]
0045ddee mov dword ptr [esi + 4], eax
0045ddf1 mov ecx, dword ptr [edx + 0x18190]
0045ddf7 ucomiss xmm0, dword ptr [ecx + 0x1c]
0045ddfb lahf 
0045ddfc test ah, 0x44
0045ddff jp 0x45de11
0045de01 mov dword ptr [edi + 0x2b8], 0xbf800000
0045de0b mov ecx, dword ptr [edx + 0x18190]
0045de11 ucomiss xmm0, dword ptr [ecx + 0x14]
0045de15 movss xmm3, dword ptr [0xb6a614]
0045de1d lahf 
0045de1e test ah, 0x44
0045de21 jp 0x45de33
0045de23 mov dword ptr [edi + 0x2b8], 0x3f800000
0045de2d mov ecx, dword ptr [edx + 0x18190]
0045de33 movss xmm2, dword ptr [edi + 0x298]
0045de3b ucomiss xmm2, dword ptr [ecx + 0x20]
0045de3f lahf 
0045de40 test ah, 0x44
0045de43 jp 0x45de55
0045de45 mov dword ptr [edi + 0x2bc], 0xbf800000
0045de4f mov ecx, dword ptr [edx + 0x18190]
0045de55 movss xmm0, dword ptr [ecx + 0x18]
0045de5a addss xmm0, dword ptr [0xb6aa3c]
0045de62 ucomiss xmm2, xmm0
0045de65 lahf 
0045de66 test ah, 0x44
0045de69 jp 0x45de75
0045de6b mov dword ptr [edi + 0x2bc], 0x3f800000
0045de75 mov edx, dword ptr [edi + 0x2c]
0045de78 movss xmm4, dword ptr [0xb6a434]
0045de80 movss xmm0, dword ptr [0xb6a480]
0045de88 movss xmm6, dword ptr [0xb6a560]
0045de90 cmp edx, 1
0045de93 jne 0x45deb2
0045de95 mov eax, dword ptr [edi + 0x30]
0045de98 movaps xmm4, xmm6
0045de9b cmp eax, 2
0045de9e jne 0x45deaa
0045dea0 movss xmm4, dword ptr [0xb6a64c]
0045dea8 jmp 0x45deb2
0045deaa cmp eax, 1
0045dead jne 0x45deb2
0045deaf movaps xmm4, xmm0
0045deb2 mov eax, dword ptr [edi + 0x164]
0045deb8 mov ecx, dword ptr [edi + 0x160]
0045debe mov dword ptr [ebp - 0x31c], eax
0045dec4 mov eax, ecx
0045dec6 and eax, 0x200
0045decb or eax, 0
0045dece je 0x45df1b
0045ded0 and ecx, 0x100
0045ded6 or ecx, 0
0045ded9 jne 0x45df1b
0045dedb movss xmm0, dword ptr [edi + 0x2c4]
0045dee3 mulss xmm0, xmm6
0045dee7 movss dword ptr [edi + 0x2c4], xmm0
0045deef test edx, edx
0045def1 jne 0x45df09
0045def3 cmp dword ptr [edi + 0x30], 2
0045def7 jne 0x45df09
0045def9 mulss xmm0, dword ptr [0xb6a5a4]
0045df01 movss dword ptr [edi + 0x2c4], xmm0
0045df09 push 0
0045df0b lea ecx, [edi + 0x364]
0045df11 call 0x7a6180
0045df16 jmp 0x45e102
0045df1b movss xmm0, dword ptr [edi + 0x2bc]
0045df23 comiss xmm0, dword ptr [0xb6a2cc]
0045df2a jb 0x45df31
0045df2c movaps xmm2, xmm3
0045df2f jmp 0x45df34
0045df31 movaps xmm2, xmm1
0045df34 movss xmm5, dword ptr [edi + 0x2b8]
0045df3c xorps xmm0, xmm0
0045df3f comiss xmm5, xmm0
0045df42 jbe 0x45df47
0045df44 movaps xmm1, xmm3
0045df47 movss xmm3, dword ptr [edi + 0x2c4]
0045df4f mulss xmm3, xmm6
0045df53 mulss xmm1, xmm4
0045df57 ucomiss xmm3, xmm0
0045df5a movss dword ptr [edi + 0x2c4], xmm3
0045df62 mulss xmm2, xmm4
0045df66 lahf 
0045df67 test ah, 0x44
0045df6a jnp 0x45dfa0
0045df6c movss xmm0, dword ptr [edi + 0x2f4]
0045df74 mulss xmm1, xmm0
0045df78 mulss xmm2, xmm0
0045df7c divss xmm1, xmm3
0045df80 divss xmm2, xmm3
0045df84 addss xmm1, xmm5
0045df88 addss xmm2, dword ptr [edi + 0x2bc]
0045df90 movss dword ptr [edi + 0x2b8], xmm1
0045df98 movss dword ptr [edi + 0x2bc], xmm2
0045dfa0 cmp dword ptr [edi + 0x2c], 0
0045dfa4 jne 0x45dfbf
0045dfa6 cmp dword ptr [edi + 0x30], 2
0045dfaa jne 0x45dfbf
0045dfac movaps xmm0, xmm3
0045dfaf mulss xmm0, dword ptr [0xb6a5a4]
0045dfb7 movss dword ptr [edi + 0x2c4], xmm0
0045dfbf mov eax, dword ptr [edi + 0x160]
0045dfc5 and eax, 0x1000800
0045dfca or eax, 0
0045dfcd je 0x45e102
0045dfd3 mov ecx, edi
0045dfd5 call 0x695680
0045dfda movss xmm1, dword ptr [eax + 0x294]
0045dfe2 subss xmm1, dword ptr [esi]
0045dfe6 movss xmm2, dword ptr [eax + 0x298]
0045dfee subss xmm2, dword ptr [esi + 4]
0045dff3 xorps xmm1, xmmword ptr [0xb6c9b0]
0045dffa movaps xmm0, xmm1
0045dffd movss dword ptr [ebp - 0x23c], xmm1
0045e005 xorps xmm2, xmmword ptr [0xb6c9b0]
0045e00c mulss xmm0, xmm1
0045e010 movaps xmm1, xmm2
0045e013 mulss xmm1, xmm2
0045e017 movss dword ptr [ebp - 0x240], xmm2
0045e01f addss xmm0, xmm1
0045e023 call 0x4228c0
0045e028 movss xmm1, dword ptr [0xb6ab88]
0045e030 lea eax, [ebp - 0x250]
0045e036 movaps xmm4, xmm0
0045e039 mov dword ptr [ebp - 0x244], 0
0045e043 subss xmm1, xmm4
0045e047 mov dword ptr [ebp - 0x248], 0x3f800000
0045e051 xorps xmm2, xmm2
0045e054 lea ecx, [ebp - 0x244]
0045e05a mulss xmm1, dword ptr [0xb6a234]
0045e062 comiss xmm2, xmm1
0045e065 movss dword ptr [ebp - 0x250], xmm1
0045e06d cmovbe ecx, eax
0045e070 lea eax, [ebp - 0x248]
0045e076 movss xmm0, dword ptr [ecx]
0045e07a comiss xmm0, dword ptr [0xb6a614]
0045e081 cmovbe eax, ecx
0045e084 comiss xmm4, xmm2
0045e087 movss xmm3, dword ptr [eax]
0045e08b jbe 0x45e0a6
0045e08d divss xmm3, xmm4
0045e091 movaps xmm4, xmm3
0045e094 mulss xmm3, dword ptr [ebp - 0x240]
0045e09c mulss xmm4, dword ptr [ebp - 0x23c]
0045e0a4 jmp 0x45e0b6
0045e0a6 movss xmm4, dword ptr [ebp - 0x23c]
0045e0ae movss xmm3, dword ptr [ebp - 0x240]
0045e0b6 movss xmm5, dword ptr [edi + 0x2c4]
0045e0be ucomiss xmm5, xmm2
0045e0c1 lahf 
0045e0c2 test ah, 0x44
0045e0c5 jnp 0x45e102
0045e0c7 movss xmm1, dword ptr [edi + 0x2f4]
0045e0cf movaps xmm0, xmm1
0045e0d2 mulss xmm1, xmm3
0045e0d6 mulss xmm0, xmm4
0045e0da divss xmm1, xmm5
0045e0de divss xmm0, xmm5
0045e0e2 addss xmm1, dword ptr [edi + 0x2bc]
0045e0ea addss xmm0, dword ptr [edi + 0x2b8]
0045e0f2 movss dword ptr [edi + 0x2bc], xmm1
0045e0fa movss dword ptr [edi + 0x2b8], xmm0
0045e102 push dword ptr [edi + 0x20]
0045e105 lea eax, [ebp - 0x29c]
0045e10b mov ecx, edi
0045e10d push eax
0045e10e call 0x6a6f60
0045e113 mov dword ptr [ebp - 4], 0
0045e11a mov eax, dword ptr [0xbfd65c]
0045e11f movss xmm1, dword ptr [0xb6a19c]
0045e127 movss xmm2, dword ptr [0xb6a874]
0045e12f mov dword ptr [ebp - 0x314], 0
0045e139 mov eax, dword ptr [eax + 0x18190]
0045e13f mov ecx, dword ptr [eax + 0x12c4]
0045e145 mov eax, dword ptr [eax + 0x12c0]
0045e14b add eax, ecx
0045e14d xor ecx, ecx
0045e14f test eax, eax
0045e151 cmovg ecx, eax
0045e154 mov eax, dword ptr [edi + 0xab4]
0045e15a mov dword ptr [ebp - 0x23c], ecx
0045e160 cmp eax, 0xe
0045e163 ja 0x45eef6
0045e169 movzx eax, byte ptr [eax + 0x45f5c0]
0045e170 jmp dword ptr [eax*4 + 0x45f5a8]
0045e177 mov dword ptr [edi + 0xab4], 4
0045e181 jmp 0x45eef6
0045e186 call 0x6c3d90
0045e18b xor edx, edx
0045e18d mov esi, dword ptr [ebp - 0x23c]
0045e193 mov ecx, 0x28
0045e198 div ecx
0045e19a test edx, edx
0045e19c jne 0x45e1cd
0045e19e mov eax, dword ptr [ebp - 0x290]
0045e1a4 add eax, esi
0045e1a6 cmp eax, 9
0045e1a9 jge 0x45e1cd
0045e1ab cmp dword ptr [edi + 0x2c], 1
0045e1af jne 0x45e1b7
0045e1b1 cmp dword ptr [edi + 0x30], 2
0045e1b5 je 0x45e1cd
0045e1b7 push 1
0045e1b9 mov dword ptr [edi + 0xab4], 0xd
0045e1c3 push 0xb40314
0045e1c8 jmp 0x45e290
0045e1cd call 0x6c3d90
0045e1d2 xor edx, edx
0045e1d4 mov ecx, 0x46
0045e1d9 div ecx
0045e1db test edx, edx
0045e1dd jne 0x45e20e
0045e1df mov eax, esi
0045e1e1 sub eax, dword ptr [ebp - 0x290]
0045e1e7 cmp eax, 0xa
0045e1ea jge 0x45e20e
0045e1ec cmp dword ptr [edi + 0x2c], 1
0045e1f0 jne 0x45e1f8
0045e1f2 cmp dword ptr [edi + 0x30], 2
0045e1f6 je 0x45e20e
0045e1f8 push 1
0045e1fa mov dword ptr [edi + 0xab4], 0xe
0045e204 push 0xb4032c
0045e209 jmp 0x45e290
0045e20e call 0x6c3d90
0045e213 xor edx, edx
0045e215 mov ecx, 0x2d
0045e21a div ecx
0045e21c test edx, edx
0045e21e jne 0x45e23d
0045e220 mov eax, dword ptr [ebp - 0x290]
0045e226 cmp eax, 4
0045e229 jle 0x45e23d
0045e22b sub esi, eax
0045e22d cmp esi, 5
0045e230 jge 0x45e23d
0045e232 cmp dword ptr [edi + 0x2c], edx
0045e235 jne 0x45e27f
0045e237 cmp dword ptr [edi + 0x30], 1
0045e23b jne 0x45e27f
0045e23d call 0x6c3d90
0045e242 xor edx, edx
0045e244 mov ecx, 0x46
0045e249 div ecx
0045e24b test edx, edx
0045e24d jne 0x45e261
0045e24f mov eax, dword ptr [edi + 0x2c]
0045e252 cmp eax, 1
0045e255 je 0x45e27f
0045e257 test eax, eax
0045e259 jne 0x45e2ba
0045e25b cmp dword ptr [edi + 0x30], 1
0045e25f je 0x45e27f
0045e261 cmp dword ptr [edi + 0x2c], 1
0045e265 jne 0x45e2ba
0045e267 cmp dword ptr [edi + 0x30], 2
0045e26b jne 0x45e2ba
0045e26d call 0x6c3d90
0045e272 xor edx, edx
0045e274 mov ecx, 0x14
0045e279 div ecx
0045e27b test edx, edx
0045e27d jne 0x45e2ba
0045e27f push 1
0045e281 mov dword ptr [edi + 0xab4], 8
0045e28b push 0xb40320
0045e290 lea ecx, [edi + 0x3c]
0045e293 call 0x405740
0045e298 test al, al
0045e29a je 0x45e2c9
0045e29c lea ecx, [edi + 0x6c]
0045e29f call 0x405330
0045e2a4 mov byte ptr [edi + 0x80], 1
0045e2ab mov dword ptr [edi + 0x360], 0
0045e2b5 jmp 0x45eee6
0045e2ba push 0
0045e2bc push 0xb41264
0045e2c1 lea ecx, [edi + 0x3c]
0045e2c4 call 0x4054f0
0045e2c9 mov dword ptr [edi + 0x360], 0
0045e2d3 jmp 0x45eee6
0045e2d8 cmp dword ptr [edi + 0x360], 0x14
0045e2df jne 0x45eef6
0045e2e5 push ecx
0045e2e6 mov dword ptr [esp], 0x3f800000
0045e2ed push 0
0045e2ef push 2
0045e2f1 push ecx
0045e2f2 mov dword ptr [esp], 0x3f800000
0045e2f9 mov ecx, edi
0045e2fb push 0x6c
0045e2fd call 0x6ad720
0045e302 mov dword ptr [ebp - 0x240], 0
0045e30c nop dword ptr [eax]
0045e310 call 0x6c3d90
0045e315 mov ecx, dword ptr [0xbfd65c]
0045e31b push 0
0045e31d push 0xbeaaec
0045e322 push 0xbeab18
0045e327 push 0
0045e329 push eax
0045e32a push 0
0045e32c push edi
0045e32d push 0xc02fec
0045e332 push esi
0045e333 push 1
0045e335 push 0x3e8
0045e33a call 0x422e20
0045e33f push eax
0045e340 call 0x9ec34c
0045e345 add esp, 0x14
0045e348 mov esi, eax
0045e34a cmp dword ptr [ebp - 0x240], 0
0045e351 jne 0x45e35d
0045e353 movss xmm0, dword ptr [0xb6aae4]
0045e35b jmp 0x45e365
0045e35d movss xmm0, dword ptr [0xb6af48]
0045e365 movss dword ptr [esi + 0x3c4], xmm0
0045e36d lea ecx, [ebp - 0x40]
0045e370 mov eax, dword ptr [esi + 0x164]
0045e376 xorps xmm0, xmm0
0045e379 or dword ptr [esi + 0x160], 0x10000
0045e383 push 1
0045e385 push 0
0045e387 push 0xff
0045e38c mov dword ptr [esi + 0x164], eax
0045e392 mov eax, dword ptr [esi]
0045e394 push -1
0045e396 movups xmmword ptr [ebp - 0x30], xmm0
0045e39a push ecx
0045e39b movaps xmm0, xmmword ptr [0xb6ba00]
0045e3a2 mov ecx, esi
0045e3a4 movups xmmword ptr [ebp - 0x40], xmm0
0045e3a8 mov dword ptr [ebp - 0x20], 0
0045e3af mov dword ptr [ebp - 0x1c], 0
0045e3b6 mov dword ptr [ebp - 0x18], 0
0045e3bd call dword ptr [eax + 0x38]
0045e3c0 mov eax, dword ptr [esi]
0045e3c2 mov ecx, esi
0045e3c4 mov dword ptr [esi + 0x2a4], 0
0045e3ce mov dword ptr [esi + 0x2a8], 0xc2200000
0045e3d8 call dword ptr [eax + 0xc]
0045e3db mov eax, dword ptr [ebp - 0x240]
0045e3e1 lea esi, [edi + 0x294]
0045e3e7 inc eax
0045e3e8 mov dword ptr [ebp - 0x240], eax
0045e3ee cmp eax, 2
0045e3f1 jl 0x45e310
0045e3f7 cmp dword ptr [edi + 0x2c], 1
0045e3fb jne 0x45e45a
0045e3fd cmp dword ptr [edi + 0x30], 1
0045e401 jne 0x45e45a
0045e403 movss xmm0, dword ptr [edi + 0x294]
0045e40b lea esi, [edi + 0x294]
0045e411 movss dword ptr [ebp - 0x2a4], xmm0
0045e419 movss xmm0, dword ptr [edi + 0x298]
0045e421 addss xmm0, dword ptr [0xb6a9c8]
0045e429 movss dword ptr [ebp - 0x2a0], xmm0
0045e431 call 0x6c3d90
0045e436 mov ecx, dword ptr [0xbfd65c]
0045e43c push eax
0045e43d push 0
0045e43f push edi
0045e440 push 0xc02fec
0045e445 lea eax, [ebp - 0x2a4]
0045e44b push eax
0045e44c push 0
0045e44e push 0x19
0045e450 call 0x422e20
0045e455 jmp 0x45e723
0045e45a push 0x40
0045e45c mov byte ptr [ebp - 0x26c], 0
0045e463 mov dword ptr [ebp - 0x264], 0x10
0045e46d mov dword ptr [ebp - 0x260], 0
0045e477 call 0x9eb09c
0045e47c add esp, 4
0045e47f mov dword ptr [ebp - 0x268], eax
0045e485 mov byte ptr [ebp - 4], 1
0045e489 lea esi, [edi + 0x294]
0045e48f movss xmm1, dword ptr [edi + 0x298]
0045e497 addss xmm1, dword ptr [0xb6a9c8]
0045e49f movss xmm0, dword ptr [esi]
0045e4a3 movss dword ptr [ebp - 0x25c], xmm0
0045e4ab movss dword ptr [ebp - 0x258], xmm1
0045e4b3 call 0x6c3d90
0045e4b8 mov ecx, dword ptr [0xbfd65c]
0045e4be push eax
0045e4bf push 0
0045e4c1 push edi
0045e4c2 push 0xc02fec
0045e4c7 lea eax, [ebp - 0x25c]
0045e4cd push eax
0045e4ce push 0
0045e4d0 push 0x12
0045e4d2 call 0x422e20
0045e4d7 mov ecx, dword ptr [ebp - 0x268]
0045e4dd mov dword ptr [ebp - 0x260], 1
0045e4e7 mov dword ptr [ecx], eax
0045e4e9 movss xmm0, dword ptr [ebp - 0x25c]
0045e4f1 addss xmm0, dword ptr [0xb6a974]
0045e4f9 movss dword ptr [ebp - 0x25c], xmm0
0045e501 call 0x6c3d90
0045e506 mov ecx, dword ptr [0xbfd65c]
0045e50c push eax
0045e50d push 0
0045e50f push edi
0045e510 push 0xc02fec
0045e515 lea eax, [ebp - 0x25c]
0045e51b push eax
0045e51c push 0
0045e51e push 0x12
0045e520 call 0x422e20
0045e525 mov ecx, dword ptr [ebp - 0x268]
0045e52b mov dword ptr [ebp - 0x260], 2
0045e535 mov dword ptr [ecx + 4], eax
0045e538 mov eax, dword ptr [edi + 0x2c]
0045e53b test eax, eax
0045e53d jne 0x45e58c
0045e53f movss xmm0, dword ptr [ebp - 0x25c]
0045e547 subss xmm0, dword ptr [0xb6a9c8]
0045e54f movss dword ptr [ebp - 0x25c], xmm0
0045e557 call 0x6c3d90
0045e55c mov ecx, dword ptr [0xbfd65c]
0045e562 push eax
0045e563 push 0
0045e565 push edi
0045e566 push 0xc02fec
0045e56b lea eax, [ebp - 0x25c]
0045e571 push eax
0045e572 push 0
0045e574 push 0x12
0045e576 call 0x422e20
0045e57b push eax
0045e57c lea ecx, [ebp - 0x26c]
0045e582 call 0x4124c0
0045e587 jmp 0x45e650
0045e58c cmp eax, 1
0045e58f jne 0x45e656
0045e595 movss xmm0, dword ptr [esi]
0045e599 mov ecx, edi
0045e59b mulss xmm0, dword ptr [0xb6a480]
0045e5a3 movss dword ptr [ebp - 0x248], xmm0
0045e5ab movss xmm0, dword ptr [esi + 4]
0045e5b0 mulss xmm0, dword ptr [0xb6a480]
0045e5b8 movss dword ptr [ebp - 0x250], xmm0
0045e5c0 call 0x695680
0045e5c5 push 0
0045e5c7 push 0
0045e5c9 push ecx
0045e5ca movss xmm0, dword ptr [eax + 0x294]
0045e5d2 movss xmm1, dword ptr [eax + 0x298]
0045e5da lea eax, [ebp - 0x2ac]
0045e5e0 mulss xmm0, dword ptr [0xb6a480]
0045e5e8 mov ecx, dword ptr [0xbfd65c]
0045e5ee mulss xmm1, dword ptr [0xb6a480]
0045e5f6 mov dword ptr [esp], 0x428c0000
0045e5fd addss xmm0, dword ptr [ebp - 0x248]
0045e605 mov ecx, dword ptr [ecx + 0x18190]
0045e60b addss xmm1, dword ptr [ebp - 0x250]
0045e613 push eax
0045e614 lea eax, [ebp - 0x2b4]
0045e61a push eax
0045e61b movss dword ptr [ebp - 0x2ac], xmm0
0045e623 movss dword ptr [ebp - 0x2a8], xmm1
0045e62b call 0x7cf240
0045e630 push ecx
0045e631 mov dword ptr [esp], 0xc1f00000
0045e638 push 0
0045e63a push dword ptr [ebp - 0x2b0]
0045e640 push dword ptr [ebp - 0x2b4]
0045e646 push edi
0045e647 push esi
0045e648 call 0x6994f0
0045e64d add esp, 0x18
0045e650 mov ecx, dword ptr [ebp - 0x268]
0045e656 xor eax, eax
0045e658 mov dword ptr [ebp - 0x23c], eax
0045e65e cmp dword ptr [ebp - 0x260], eax
0045e664 jbe 0x45e707
0045e66a nop word ptr [eax + eax]
0045e670 push 0
0045e672 push 0xbeab70
0045e677 push 0xbeab18
0045e67c push 0
0045e67e push dword ptr [ecx + eax*4]
0045e681 call 0x9ec34c
0045e686 mov ecx, dword ptr [edi + 0x20]
0045e689 mov esi, eax
0045e68b lea eax, [esi + 0x314]
0045e691 add esp, 0x14
0045e694 mov dword ptr [esi + 0xbcc], ecx
0045e69a mov ecx, dword ptr [eax]
0045e69c test ecx, ecx
0045e69e je 0x45e6be
0045e6a0 mov dword ptr [ebp - 0x254], eax
0045e6a6 add ecx, 0x324
0045e6ac lea eax, [ebp - 0x254]
0045e6b2 push eax
0045e6b3 call 0x4bc3c0
0045e6b8 lea eax, [esi + 0x314]
0045e6be push eax
0045e6bf mov ecx, edi
0045e6c1 mov dword ptr [eax], edi
0045e6c3 call 0x4bae70
0045e6c8 mov eax, dword ptr [esi + 0x164]
0045e6ce and dword ptr [esi + 0x160], 0xfffffffb
0045e6d5 mov ecx, dword ptr [ebp - 0x268]
0045e6db mov dword ptr [esi + 0x164], eax
0045e6e1 mov eax, dword ptr [ebp - 0x23c]
0045e6e7 inc eax
0045e6e8 mov byte ptr [esi + 0x16c], 1
0045e6ef mov dword ptr [ebp - 0x23c], eax
0045e6f5 cmp eax, dword ptr [ebp - 0x260]
0045e6fb jb 0x45e670
0045e701 lea esi, [edi + 0x294]
0045e707 mov byte ptr [ebp - 4], 0
0045e70b cmp byte ptr [ebp - 0x26c], 0
0045e712 jne 0x45e723
0045e714 mov ecx, dword ptr [ebp - 0x268]
0045e71a push ecx
0045e71b call 0x9eace5
0045e720 add esp, 4
0045e723 push 0
0045e725 push 1
0045e727 push -1
0045e729 push 0x21
0045e72b push 0x3e8
0045e730 lea eax, [ebp - 0x330]
0045e736 push eax
0045e737 mov eax, dword ptr [0xbfd65c]
0045e73c mov ecx, dword ptr [eax + 0x18190]
0045e742 add ecx, 0x1218
0045e748 call 0x415ed0
0045e74d cmp byte ptr [ebp - 0x330], 0
0045e754 mov eax, dword ptr [eax + 0xc]
0045e757 mov dword ptr [ebp - 0x248], eax
0045e75d jne 0x45e773
0045e75f push dword ptr [ebp - 0x32c]
0045e765 call 0x9eace5
0045e76a mov eax, dword ptr [ebp - 0x248]
0045e770 add esp, 4
0045e773 cmp eax, 0x19
0045e776 jae 0x45eee6
0045e77c call 0x6c3d90
0045e781 xor edx, edx
0045e783 movss xmm0, dword ptr [esi]
0045e787 mov ecx, 5
0045e78c movss dword ptr [ebp - 0x258], xmm0
0045e794 div ecx
0045e796 movss xmm0, dword ptr [edi + 0x298]
0045e79e addss xmm0, dword ptr [0xb6a9c8]
0045e7a6 inc edx
0045e7a7 mov dword ptr [ebp - 0x23c], edx
0045e7ad movss dword ptr [ebp - 0x240], xmm0
0045e7b5 test edx, edx
0045e7b7 jle 0x45eee6
0045e7bd nop dword ptr [eax]
0045e7c0 call 0x6c3d90
0045e7c5 movd xmm0, eax
0045e7c9 cvtdq2pd xmm0, xmm0
0045e7cd shr eax, 0x1f
0045e7d0 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
0045e7d9 cvtpd2ps xmm0, xmm0
0045e7dd mulss xmm0, dword ptr [0xb6a19c]
0045e7e5 mulss xmm0, dword ptr [0xb6aa3c]
0045e7ed movss dword ptr [ebp - 0x254], xmm0
0045e7f5 call 0x6c3d90
0045e7fa mov esi, eax
0045e7fc call 0x6c3d90
0045e801 movd xmm0, eax
0045e805 cvtdq2pd xmm0, xmm0
0045e809 shr eax, 0x1f
0045e80c addsd xmm0, qword ptr [eax*8 + 0xb6c940]
0045e815 cvtpd2ps xmm0, xmm0
0045e819 mulss xmm0, dword ptr [0xb6a19c]
0045e821 mulss xmm0, dword ptr [0xb6a874]
0045e829 addss xmm0, xmm0
0045e82d movss dword ptr [ebp - 0x248], xmm0
0045e835 call 0x411fe0
0045e83a movss dword ptr [ebp - 0x2bc], xmm0
0045e842 movss xmm0, dword ptr [ebp - 0x248]
0045e84a call 0x412010
0045e84f movss dword ptr [ebp - 0x2b8], xmm0
0045e857 call 0x6c3d90
0045e85c movd xmm0, eax
0045e860 cvtdq2pd xmm0, xmm0
0045e864 shr eax, 0x1f
0045e867 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
0045e870 cvtpd2ps xmm0, xmm0
0045e874 mulss xmm0, dword ptr [0xb6a19c]
0045e87c mulss xmm0, dword ptr [0xb6a874]
0045e884 addss xmm0, xmm0
0045e888 movss dword ptr [ebp - 0x248], xmm0
0045e890 call 0x411fe0
0045e895 movss dword ptr [ebp - 0x250], xmm0
0045e89d movss xmm0, dword ptr [ebp - 0x248]
0045e8a5 call 0x412010
0045e8aa movss xmm1, dword ptr [ebp - 0x258]
0045e8b2 lea eax, [ebp - 0x2bc]
0045e8b8 mov ecx, dword ptr [0xbfd65c]
0045e8be movaps xmm2, xmm0
0045e8c1 movss xmm0, dword ptr [ebp - 0x250]
0045e8c9 mulss xmm0, dword ptr [ebp - 0x254]
0045e8d1 push esi
0045e8d2 mulss xmm2, dword ptr [ebp - 0x254]
0045e8da push 0
0045e8dc push edi
0045e8dd addss xmm1, xmm0
0045e8e1 movss xmm0, dword ptr [ebp - 0x240]
0045e8e9 push eax
0045e8ea lea eax, [ebp - 0x304]
0045e8f0 addss xmm0, xmm2
0045e8f4 push eax
0045e8f5 push 0x21
0045e8f7 push 0x3e8
0045e8fc movss dword ptr [ebp - 0x304], xmm1
0045e904 movss dword ptr [ebp - 0x300], xmm0
0045e90c call 0x422e20
0045e911 mov esi, eax
0045e913 mov ecx, dword ptr [esi + 0x314]
0045e919 lea eax, [esi + 0x314]
0045e91f test ecx, ecx
0045e921 je 0x45e941
0045e923 mov dword ptr [ebp - 0x24c], eax
0045e929 add ecx, 0x324
0045e92f lea eax, [ebp - 0x24c]
0045e935 push eax
0045e936 call 0x4bc3c0
0045e93b lea eax, [esi + 0x314]
0045e941 push eax
0045e942 mov ecx, edi
0045e944 mov dword ptr [eax], edi
0045e946 call 0x4bae70
0045e94b mov eax, dword ptr [esi + 0x164]
0045e951 mov ecx, esi
0045e953 and dword ptr [esi + 0x160], 0xfffffffb
0045e95a mov dword ptr [esi + 0x164], eax
0045e960 mov eax, dword ptr [esi]
0045e962 call dword ptr [eax + 0xc]
0045e965 sub dword ptr [ebp - 0x23c], 1
0045e96c jne 0x45e7c0
0045e972 jmp 0x45eee6
0045e977 cmp dword ptr [edi + 0x360], 0x12
0045e97e jne 0x45eef6
0045e984 push ecx
0045e985 mov dword ptr [esp], 0x3f800000
0045e98c push 0
0045e98e push 2
0045e990 push ecx
0045e991 mov dword ptr [esp], 0x3f800000
0045e998 mov ecx, edi
0045e99a push 0x6a
0045e99c call 0x6ad720
0045e9a1 mov eax, dword ptr [edi + 0x2c]
0045e9a4 test eax, eax
0045e9a6 jne 0x45eadd
0045e9ac mov ecx, dword ptr [edi + 0x30]
0045e9af mov eax, 0x12
0045e9b4 cmp ecx, 1
0045e9b7 jne 0x45e9c5
0045e9b9 mov dword ptr [ebp - 0x23c], 0x50
0045e9c3 jmp 0x45e9d6
0045e9c5 cmp ecx, 2
0045e9c8 mov edx, 0x3d
0045e9cd cmove eax, edx
0045e9d0 mov dword ptr [ebp - 0x23c], eax
0045e9d6 call 0x6c3d90
0045e9db movss xmm0, dword ptr [esi]
0045e9df mov ecx, dword ptr [0xbfd65c]
0045e9e5 push 0
0045e9e7 push 0xbeab70
0045e9ec push 0xbeab18
0045e9f1 push 0
0045e9f3 push eax
0045e9f4 push 0
0045e9f6 push edi
0045e9f7 movss dword ptr [ebp - 0x2fc], xmm0
0045e9ff lea eax, [ebp - 0x2fc]
0045ea05 movss xmm0, dword ptr [edi + 0x298]
0045ea0d addss xmm0, dword ptr [0xb6a9c8]
0045ea15 push 0xc02fec
0045ea1a push eax
0045ea1b push 0
0045ea1d push dword ptr [ebp - 0x23c]
0045ea23 movss dword ptr [ebp - 0x2f8], xmm0
0045ea2b call 0x422e20
0045ea30 push eax
0045ea31 call 0x9ec34c
0045ea36 movss xmm2, dword ptr [0xb6a874]
0045ea3e add esp, 0x14
0045ea41 mov ecx, dword ptr [eax + 0x164]
0045ea47 and dword ptr [eax + 0x160], 0xfffffffb
0045ea4e mov byte ptr [eax + 0x16c], 1
0045ea55 mov dword ptr [eax + 0x164], ecx
0045ea5b cmp dword ptr [edi + 0x30], 0
0045ea5f jne 0x45eeee
0045ea65 movss xmm1, dword ptr [eax + 0xb88]
0045ea6d mulss xmm1, dword ptr [0xb6a680]
0045ea75 movss dword ptr [eax + 0xb88], xmm1
0045ea7d mulss xmm1, dword ptr [eax + 0x30c]
0045ea85 movaps xmm0, xmm1
0045ea88 mulss xmm1, dword ptr [0xbc7a2c]
0045ea90 mulss xmm0, dword ptr [0xbc7a28]
0045ea98 movss dword ptr [eax + 0xdc], xmm1
0045eaa0 movss dword ptr [eax + 0xd8], xmm0
0045eaa8 movss xmm0, dword ptr [eax + 0x2dc]
0045eab0 mulss xmm0, dword ptr [0xb6a754]
0045eab8 movss dword ptr [eax + 0x2dc], xmm0
0045eac0 movss xmm0, dword ptr [eax + 0x2d8]
0045eac8 mulss xmm0, dword ptr [0xb6a754]
0045ead0 movss dword ptr [eax + 0x2d8], xmm0
0045ead8 jmp 0x45eeee
0045eadd cmp eax, 1
0045eae0 jne 0x45eee6
0045eae6 mov ecx, edi
0045eae8 call 0x695680
0045eaed mov ecx, dword ptr [eax + 0x294]
0045eaf3 mov eax, dword ptr [eax + 0x298]
0045eaf9 mov dword ptr [ebp - 0x2f4], ecx
0045eaff lea ecx, [ebp - 0x190]
0045eb05 mov dword ptr [ebp - 0x2f0], eax
0045eb0b call 0x430d70
0045eb10 push eax
0045eb11 push ecx
0045eb12 mov dword ptr [esp], 0
0045eb19 lea eax, [ebp - 0x2f4]
0045eb1f push eax
0045eb20 push 0xa
0045eb22 mov ecx, edi
0045eb24 call 0x6a3420
0045eb29 jmp 0x45eee6
0045eb2e cmp dword ptr [edi + 0x360], 0x11
0045eb35 jne 0x45eef6
0045eb3b push ecx
0045eb3c mov dword ptr [esp], 0x3f800000
0045eb43 push 0
0045eb45 push 2
0045eb47 push ecx
0045eb48 mov dword ptr [esp], 0x3f800000
0045eb4f mov ecx, edi
0045eb51 push 0x70
0045eb53 call 0x6ad720
0045eb58 xor ecx, ecx
0045eb5a mov dword ptr [ebp - 0x244], ecx
0045eb60 cmp dword ptr [ebp - 0x290], ecx
0045eb66 jbe 0x45eccd
0045eb6c mov edi, dword ptr [ebp - 0x258]
0045eb72 mov eax, dword ptr [ebp - 0x298]
0045eb78 push 0
0045eb7a push 0xbeab70
0045eb7f push 0xbeab18
0045eb84 push 0
0045eb86 push dword ptr [eax + ecx*4]
0045eb89 call 0x9ec34c
0045eb8e mov esi, eax
0045eb90 add esp, 0x14
0045eb93 test esi, esi
0045eb95 je 0x45ecae
0045eb9b mov ecx, dword ptr [esi + 0x314]
0045eba1 lea eax, [esi + 0x314]
0045eba7 test ecx, ecx
0045eba9 je 0x45ebc9
0045ebab mov dword ptr [ebp - 0x23c], eax
0045ebb1 add ecx, 0x324
0045ebb7 lea eax, [ebp - 0x23c]
0045ebbd push eax
0045ebbe call 0x4bc3c0
0045ebc3 lea eax, [esi + 0x314]
0045ebc9 movss xmm1, dword ptr [esi + 0x298]
0045ebd1 movss xmm0, dword ptr [esi + 0x294]
0045ebd9 mov dword ptr [eax], 0
0045ebdf mov dword ptr [esi + 0xbcc], 0xffffffff
0045ebe9 subss xmm1, dword ptr [edi + 4]
0045ebee subss xmm0, dword ptr [edi]
0045ebf2 movaps xmm2, xmm1
0045ebf5 movss dword ptr [ebp - 0x240], xmm1
0045ebfd mulss xmm2, xmm1
0045ec01 movaps xmm1, xmm0
0045ec04 mulss xmm1, xmm0
0045ec08 movss dword ptr [ebp - 0x23c], xmm0
0045ec10 addss xmm2, xmm1
0045ec14 comiss xmm2, dword ptr [0xb6a214]
0045ec1b jbe 0x45ecae
0045ec21 movaps xmm0, xmm2
0045ec24 call 0x4228c0
0045ec29 movaps xmm2, xmm0
0045ec2c xorps xmm0, xmm0
0045ec2f comiss xmm2, xmm0
0045ec32 jbe 0x45ec55
0045ec34 movss xmm1, dword ptr [0xb6a9bc]
0045ec3c divss xmm1, xmm2
0045ec40 movaps xmm2, xmm1
0045ec43 mulss xmm1, dword ptr [ebp - 0x240]
0045ec4b mulss xmm2, dword ptr [ebp - 0x23c]
0045ec53 jmp 0x45ec65
0045ec55 movss xmm2, dword ptr [ebp - 0x23c]
0045ec5d movss xmm1, dword ptr [ebp - 0x240]
0045ec65 movss xmm3, dword ptr [esi + 0x2c4]
0045ec6d ucomiss xmm3, xmm0
0045ec70 lahf 
0045ec71 test ah, 0x44
0045ec74 jnp 0x45ecae
0045ec76 movss xmm0, dword ptr [esi + 0x2f4]
0045ec7e mulss xmm2, xmm0
0045ec82 mulss xmm1, xmm0
0045ec86 divss xmm2, xmm3
0045ec8a divss xmm1, xmm3
0045ec8e addss xmm2, dword ptr [esi + 0x2b8]
0045ec96 addss xmm1, dword ptr [esi + 0x2bc]
0045ec9e movss dword ptr [esi + 0x2b8], xmm2
0045eca6 movss dword ptr [esi + 0x2bc], xmm1
0045ecae mov ecx, dword ptr [ebp - 0x244]
0045ecb4 inc ecx
0045ecb5 mov dword ptr [ebp - 0x244], ecx
0045ecbb cmp ecx, dword ptr [ebp - 0x290]
0045ecc1 jb 0x45eb72
0045ecc7 mov edi, dword ptr [ebp - 0x254]
0045eccd push 0
0045eccf push 1
0045ecd1 push -1
0045ecd3 push 0x21
0045ecd5 push 0x3e8
0045ecda lea eax, [ebp - 0x27c]
0045ece0 push eax
0045ece1 mov eax, dword ptr [0xbfd65c]
0045ece6 mov ecx, dword ptr [eax + 0x18190]
0045ecec add ecx, 0x1218
0045ecf2 call 0x415ed0
0045ecf7 mov byte ptr [ebp - 4], 2
0045ecfb xor esi, esi
0045ecfd mov eax, dword ptr [ebp - 0x270]
0045ed03 mov dword ptr [ebp - 0x240], esi
0045ed09 test eax, eax
0045ed0b je 0x45ee27
0045ed11 mov edi, dword ptr [ebp - 0x258]
0045ed17 mov ecx, dword ptr [ebp - 0x278]
0045ed1d nop dword ptr [eax]
0045ed20 mov esi, dword ptr [ecx + esi*4]
0045ed23 test esi, esi
0045ed25 je 0x45ee0c
0045ed2b movss xmm0, dword ptr [esi + 0x294]
0045ed33 movss xmm2, dword ptr [esi + 0x298]
0045ed3b subss xmm0, dword ptr [edi]
0045ed3f subss xmm2, dword ptr [edi + 4]
0045ed44 movaps xmm3, xmm0
0045ed47 movss dword ptr [ebp - 0x258], xmm0
0045ed4f movaps xmm1, xmm2
0045ed52 mulss xmm3, xmm0
0045ed56 mulss xmm1, xmm2
0045ed5a movss dword ptr [ebp - 0x23c], xmm2
0045ed62 addss xmm3, xmm1
0045ed66 comiss xmm3, dword ptr [0xb6a214]
0045ed6d jbe 0x45ee0c
0045ed73 movaps xmm0, xmm3
0045ed76 call 0x4228c0
0045ed7b movaps xmm2, xmm0
0045ed7e xorps xmm0, xmm0
0045ed81 comiss xmm2, xmm0
0045ed84 jbe 0x45eda7
0045ed86 movss xmm1, dword ptr [0xb6a864]
0045ed8e divss xmm1, xmm2
0045ed92 movaps xmm2, xmm1
0045ed95 mulss xmm1, dword ptr [ebp - 0x23c]
0045ed9d mulss xmm2, dword ptr [ebp - 0x258]
0045eda5 jmp 0x45edb7
0045eda7 movss xmm2, dword ptr [ebp - 0x258]
0045edaf movss xmm1, dword ptr [ebp - 0x23c]
0045edb7 movss xmm3, dword ptr [esi + 0x2c4]
0045edbf mov ecx, dword ptr [ebp - 0x278]
0045edc5 ucomiss xmm3, xmm0
0045edc8 lahf 
0045edc9 test ah, 0x44
0045edcc mov eax, dword ptr [ebp - 0x270]
0045edd2 jnp 0x45ee0c
0045edd4 movss xmm0, dword ptr [esi + 0x2f4]
0045eddc mulss xmm2, xmm0
0045ede0 mulss xmm1, xmm0
0045ede4 divss xmm2, xmm3
0045ede8 divss xmm1, xmm3
0045edec addss xmm2, dword ptr [esi + 0x2b8]
0045edf4 addss xmm1, dword ptr [esi + 0x2bc]
0045edfc movss dword ptr [esi + 0x2b8], xmm2
0045ee04 movss dword ptr [esi + 0x2bc], xmm1
0045ee0c mov esi, dword ptr [ebp - 0x240]
0045ee12 inc esi
0045ee13 mov dword ptr [ebp - 0x240], esi
0045ee19 cmp esi, eax
0045ee1b jb 0x45ed20
0045ee21 mov edi, dword ptr [ebp - 0x254]
0045ee27 cmp dword ptr [edi + 0x2c], 1
0045ee2b jne 0x45ee8e
0045ee2d movss xmm1, dword ptr [edi + 0x294]
0045ee35 lea ecx, [ebp - 0x238]
0045ee3b movss xmm0, dword ptr [edi + 0x298]
0045ee43 subss xmm0, dword ptr [0xb6aa3c]
0045ee4b subss xmm1, dword ptr [0xb6a18c]
0045ee53 mov dword ptr [ebp - 0x30c], 0x41000000
0045ee5d mov dword ptr [ebp - 0x308], 0x41000000
0045ee67 movss dword ptr [ebp - 0x2c0], xmm0
0045ee6f movss dword ptr [ebp - 0x2c4], xmm1
0045ee77 call 0x430d70
0045ee7c push eax
0045ee7d lea eax, [ebp - 0x30c]
0045ee83 push 9
0045ee85 push eax
0045ee86 lea eax, [ebp - 0x2c4]
0045ee8c jmp 0x45eec3
0045ee8e cmp dword ptr [edi + 0x30], 1
0045ee92 jne 0x45eecb
0045ee94 lea ecx, [ebp - 0xe8]
0045ee9a mov dword ptr [ebp - 0x2cc], 0x40e00000
0045eea4 mov dword ptr [ebp - 0x2c8], 0x41000000
0045eeae call 0x430d70
0045eeb3 push eax
0045eeb4 lea eax, [ebp - 0x2cc]
0045eeba push 9
0045eebc push eax
0045eebd lea eax, [edi + 0x294]
0045eec3 push eax
0045eec4 mov ecx, edi
0045eec6 call 0x6a1a20
0045eecb mov byte ptr [ebp - 4], 0
0045eecf cmp byte ptr [ebp - 0x27c], 0
0045eed6 jne 0x45eee6
0045eed8 push dword ptr [ebp - 0x278]
0045eede call 0x9eace5
0045eee3 add esp, 4
0045eee6 movss xmm2, dword ptr [0xb6a874]
0045eeee movss xmm1, dword ptr [0xb6a19c]
0045eef6 inc dword ptr [edi + 0x360]
0045eefc cmp dword ptr [edi + 0x360], 0x28
0045ef03 jl 0x45ef0f
0045ef05 mov dword ptr [edi + 0xab4], 4
0045ef0f cmp byte ptr [edi + 0x16b], 0
0045ef16 je 0x45f571
0045ef1c mov dword ptr [ebp - 0x254], 0
0045ef26 call 0x6c3d90
0045ef2b xor edx, edx
0045ef2d mov ecx, 0xa
0045ef32 div ecx
0045ef34 add edx, 5
0045ef37 je 0x45f053
0045ef3d nop dword ptr [eax]
0045ef40 call 0x6c3d90
0045ef45 movd xmm0, eax
0045ef49 cvtdq2pd xmm0, xmm0
0045ef4d shr eax, 0x1f
0045ef50 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
0045ef59 cvtpd2ps xmm0, xmm0
0045ef5d mulss xmm0, xmm1
0045ef61 mulss xmm0, dword ptr [0xb6aa60]
0045ef69 movss dword ptr [ebp - 0x250], xmm0
0045ef71 call 0x6c3d90
0045ef76 mov esi, eax
0045ef78 call 0x6c3d90
0045ef7d movd xmm0, eax
0045ef81 cvtdq2pd xmm0, xmm0
0045ef85 shr eax, 0x1f
0045ef88 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
0045ef91 cvtpd2ps xmm0, xmm0
0045ef95 mulss xmm0, xmm1
0045ef99 mulss xmm0, xmm2
0045ef9d addss xmm0, xmm0
0045efa1 movss dword ptr [ebp - 0x24c], xmm0
0045efa9 call 0x411fe0
0045efae movss dword ptr [ebp - 0x248], xmm0
0045efb6 movss xmm0, dword ptr [ebp - 0x24c]
0045efbe call 0x412010
0045efc3 movss xmm1, dword ptr [ebp - 0x248]
0045efcb lea eax, [ebp - 0x2d4]
0045efd1 mulss xmm1, dword ptr [ebp - 0x250]
0045efd9 mov ecx, dword ptr [0xbfd65c]
0045efdf mulss xmm0, dword ptr [ebp - 0x250]
0045efe7 push esi
0045efe8 addss xmm1, dword ptr [edi + 0x294]
0045eff0 push 0
0045eff2 addss xmm0, dword ptr [edi + 0x298]
0045effa push edi
0045effb push 0xc02fec
0045f000 push eax
0045f001 push 0x21
0045f003 push 0x3e8
0045f008 movss dword ptr [ebp - 0x2d4], xmm1
0045f010 movss dword ptr [ebp - 0x2d0], xmm0
0045f018 call 0x422e20
0045f01d mov esi, dword ptr [ebp - 0x254]
0045f023 inc esi
0045f024 mov dword ptr [ebp - 0x254], esi
0045f02a call 0x6c3d90
0045f02f xor edx, edx
0045f031 movss xmm1, dword ptr [0xb6a19c]
0045f039 mov ecx, 0xa
0045f03e movss xmm2, dword ptr [0xb6a874]
0045f046 div ecx
0045f048 add edx, 5
0045f04b cmp esi, edx
0045f04d jb 0x45ef40
0045f053 cmp dword ptr [edi + 0x2c], 1
0045f057 movq xmm0, qword ptr [0xa08c44]
0045f05f mov esi, dword ptr [edi + 0x344]
0045f065 mov eax, dword ptr [0xa08c4c]
0045f06a mov dword ptr [ebp - 0x244], esi
0045f070 movq qword ptr [ebp - 0x288], xmm0
0045f078 mov dword ptr [ebp - 0x240], eax
0045f07e jne 0x45f3f6
0045f084 test esi, esi
0045f086 jne 0x45f098
0045f088 push 0xb4d6c4
0045f08d push 3
0045f08f call 0x95e330
0045f094 add esp, 8
0045f097 int3 
0045f098 mov ecx, dword ptr [ebp - 0x288]
0045f09e mov eax, esi
0045f0a0 shr eax, cl
0045f0a2 mov ecx, dword ptr [ebp - 0x284]
0045f0a8 xor esi, eax
0045f0aa mov eax, esi
0045f0ac shl eax, cl
0045f0ae mov ecx, dword ptr [ebp - 0x240]
0045f0b4 xor esi, eax
0045f0b6 mov eax, esi
0045f0b8 shr eax, cl
0045f0ba xor esi, eax
0045f0bc mov eax, 0xaaaaaaab
0045f0c1 mul esi
0045f0c3 mov ecx, esi
0045f0c5 mov dword ptr [ebp - 0x244], esi
0045f0cb shr edx, 1
0045f0cd lea eax, [edx + edx*2]
0045f0d0 sub ecx, eax
0045f0d2 add ecx, 4
0045f0d5 mov dword ptr [ebp - 0x24c], ecx
0045f0db test ecx, ecx
0045f0dd jle 0x45f258
0045f0e3 mov esi, ecx
0045f0e5 call 0x6c3d90
0045f0ea movd xmm0, eax
0045f0ee cvtdq2pd xmm0, xmm0
0045f0f2 shr eax, 0x1f
0045f0f5 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
0045f0fe cvtpd2ps xmm0, xmm0
0045f102 mulss xmm0, dword ptr [0xb6a19c]
0045f10a mulss xmm0, dword ptr [0xb6a560]
0045f112 mulss xmm0, dword ptr [edi + 0x2c8]
0045f11a movss dword ptr [ebp - 0x250], xmm0
0045f122 call 0x6c3d90
0045f127 movd xmm0, eax
0045f12b cvtdq2pd xmm0, xmm0
0045f12f shr eax, 0x1f
0045f132 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
0045f13b cvtpd2ps xmm0, xmm0
0045f13f mulss xmm0, dword ptr [0xb6a19c]
0045f147 mulss xmm0, dword ptr [0xb6a874]
0045f14f addss xmm0, xmm0
0045f153 movss dword ptr [ebp - 0x24c], xmm0
0045f15b call 0x411fe0
0045f160 movss dword ptr [ebp - 0x248], xmm0
0045f168 movss xmm0, dword ptr [ebp - 0x24c]
0045f170 call 0x412010
0045f175 movss xmm1, dword ptr [ebp - 0x248]
0045f17d mulss xmm1, dword ptr [ebp - 0x250]
0045f185 mulss xmm0, dword ptr [ebp - 0x250]
0045f18d addss xmm1, dword ptr [edi + 0x294]
0045f195 addss xmm0, dword ptr [edi + 0x298]
0045f19d movss dword ptr [ebp - 0x2dc], xmm1
0045f1a5 movss dword ptr [ebp - 0x2d8], xmm0
0045f1ad call 0x6c3d90
0045f1b2 mov edx, dword ptr [ebp - 0x244]
0045f1b8 mov dword ptr [ebp - 0x24c], eax
0045f1be test edx, edx
0045f1c0 jne 0x45f1d8
0045f1c2 push 0xb4d6c4
0045f1c7 push 3
0045f1c9 call 0x95e330
0045f1ce add esp, 8
0045f1d1 int3 
0045f1d2 mov edx, dword ptr [ebp - 0x244]
0045f1d8 mov ecx, dword ptr [ebp - 0x288]
0045f1de mov eax, edx
0045f1e0 push dword ptr [ebp - 0x24c]
0045f1e6 shr eax, cl
0045f1e8 mov ecx, dword ptr [ebp - 0x284]
0045f1ee xor edx, eax
0045f1f0 mov eax, edx
0045f1f2 shl eax, cl
0045f1f4 mov ecx, dword ptr [ebp - 0x240]
0045f1fa xor edx, eax
0045f1fc push 0
0045f1fe mov eax, edx
0045f200 shr eax, cl
0045f202 mov ecx, 0xd
0045f207 xor edx, eax
0045f209 lea eax, [ebp - 0x2dc]
0045f20f push 0
0045f211 push 0xc02fec
0045f216 push eax
0045f217 test dl, 1
0045f21a mov dword ptr [ebp - 0x244], edx
0045f220 mov eax, 0x12
0045f225 cmovne eax, ecx
0045f228 mov ecx, dword ptr [0xbfd65c]
0045f22e push 0
0045f230 push eax
0045f231 call 0x422e20
0045f236 and dword ptr [eax + 0x160], 0xfffffffb
0045f23d mov ecx, dword ptr [eax + 0x164]
0045f243 mov dword ptr [eax + 0x164], ecx
0045f249 sub esi, 1
0045f24c jne 0x45f0e5
0045f252 mov esi, dword ptr [ebp - 0x244]
0045f258 mov eax, dword ptr [edi + 0x30]
0045f25b mov dword ptr [ebp - 0x23c], 0xe
0045f265 mov dword ptr [ebp - 0x244], 0
0045f26f cmp eax, 1
0045f272 jne 0x45f280
0045f274 mov dword ptr [ebp - 0x244], 0
0045f27e jmp 0x45f28f
0045f280 cmp eax, 2
0045f283 jne 0x45f299
0045f285 mov dword ptr [ebp - 0x244], 1
0045f28f mov dword ptr [ebp - 0x23c], 0x19
0045f299 test esi, esi
0045f29b jne 0x45f2ad
0045f29d push 0xb4d6c4
0045f2a2 push 3
0045f2a4 call 0x95e330
0045f2a9 add esp, 8
0045f2ac int3 
0045f2ad mov ecx, dword ptr [ebp - 0x288]
0045f2b3 mov eax, esi
0045f2b5 shr eax, cl
0045f2b7 mov ecx, dword ptr [ebp - 0x284]
0045f2bd xor esi, eax
0045f2bf mov eax, esi
0045f2c1 shl eax, cl
0045f2c3 mov ecx, dword ptr [ebp - 0x240]
0045f2c9 xor esi, eax
0045f2cb mov eax, esi
0045f2cd shr eax, cl
0045f2cf xor esi, eax
0045f2d1 and esi, 1
0045f2d4 add esi, 1
0045f2d7 je 0x45f571
0045f2dd nop dword ptr [eax]
0045f2e0 call 0x6c3d90
0045f2e5 movd xmm0, eax
0045f2e9 cvtdq2pd xmm0, xmm0
0045f2ed shr eax, 0x1f
0045f2f0 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
0045f2f9 cvtpd2ps xmm0, xmm0
0045f2fd mulss xmm0, dword ptr [0xb6a19c]
0045f305 mulss xmm0, dword ptr [0xb6a560]
0045f30d mulss xmm0, dword ptr [edi + 0x2c8]
0045f315 movss dword ptr [ebp - 0x250], xmm0
0045f31d call 0x6c3d90
0045f322 movd xmm0, eax
0045f326 cvtdq2pd xmm0, xmm0
0045f32a shr eax, 0x1f
0045f32d addsd xmm0, qword ptr [eax*8 + 0xb6c940]
0045f336 cvtpd2ps xmm0, xmm0
0045f33a mulss xmm0, dword ptr [0xb6a19c]
0045f342 mulss xmm0, dword ptr [0xb6a874]
0045f34a addss xmm0, xmm0
0045f34e movss dword ptr [ebp - 0x24c], xmm0
0045f356 call 0x411fe0
0045f35b movss dword ptr [ebp - 0x248], xmm0
0045f363 movss xmm0, dword ptr [ebp - 0x24c]
0045f36b call 0x412010
0045f370 movss xmm1, dword ptr [ebp - 0x248]
0045f378 mulss xmm1, dword ptr [ebp - 0x250]
0045f380 mulss xmm0, dword ptr [ebp - 0x250]
0045f388 addss xmm1, dword ptr [edi + 0x294]
0045f390 addss xmm0, dword ptr [edi + 0x298]
0045f398 movss dword ptr [ebp - 0x2e4], xmm1
0045f3a0 movss dword ptr [ebp - 0x2e0], xmm0
0045f3a8 call 0x6c3d90
0045f3ad mov ecx, dword ptr [0xbfd65c]
0045f3b3 push eax
0045f3b4 push 0
0045f3b6 push 0
0045f3b8 push 0xc02fec
0045f3bd lea eax, [ebp - 0x2e4]
0045f3c3 push eax
0045f3c4 push dword ptr [ebp - 0x244]
0045f3ca push dword ptr [ebp - 0x23c]
0045f3d0 call 0x422e20
0045f3d5 and dword ptr [eax + 0x160], 0xfffffffb
0045f3dc mov ecx, dword ptr [eax + 0x164]
0045f3e2 mov dword ptr [eax + 0x164], ecx
0045f3e8 sub esi, 1
0045f3eb jne 0x45f2e0
0045f3f1 jmp 0x45f571
0045f3f6 mov dword ptr [ebp - 0x254], 6
0045f400 mov esi, 0xd
0045f405 call 0x6c3d90
0045f40a movd xmm0, eax
0045f40e cvtdq2pd xmm0, xmm0
0045f412 shr eax, 0x1f
0045f415 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
0045f41e cvtpd2ps xmm0, xmm0
0045f422 mulss xmm0, dword ptr [0xb6a19c]
0045f42a mulss xmm0, dword ptr [0xb6a560]
0045f432 mulss xmm0, dword ptr [edi + 0x2c8]
0045f43a movss dword ptr [ebp - 0x250], xmm0
0045f442 call 0x6c3d90
0045f447 movd xmm0, eax
0045f44b cvtdq2pd xmm0, xmm0
0045f44f shr eax, 0x1f
0045f452 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
0045f45b cvtpd2ps xmm0, xmm0
0045f45f mulss xmm0, dword ptr [0xb6a19c]
0045f467 mulss xmm0, dword ptr [0xb6a874]
0045f46f addss xmm0, xmm0
0045f473 movss dword ptr [ebp - 0x24c], xmm0
0045f47b call 0x411fe0
0045f480 movss dword ptr [ebp - 0x248], xmm0
0045f488 movss xmm0, dword ptr [ebp - 0x24c]
0045f490 call 0x412010
0045f495 movss xmm1, dword ptr [ebp - 0x248]
0045f49d mulss xmm1, dword ptr [ebp - 0x250]
0045f4a5 mulss xmm0, dword ptr [ebp - 0x250]
0045f4ad addss xmm1, dword ptr [edi + 0x294]
0045f4b5 addss xmm0, dword ptr [edi + 0x298]
0045f4bd movss dword ptr [ebp - 0x2ec], xmm1
0045f4c5 movss dword ptr [ebp - 0x2e8], xmm0
0045f4cd call 0x6c3d90
0045f4d2 mov edx, dword ptr [ebp - 0x244]
0045f4d8 mov dword ptr [ebp - 0x24c], eax
0045f4de test edx, edx
0045f4e0 jne 0x45f4f8
0045f4e2 push 0xb4d6c4
0045f4e7 push 3
0045f4e9 call 0x95e330
0045f4ee add esp, 8
0045f4f1 int3 
0045f4f2 mov edx, dword ptr [ebp - 0x244]
0045f4f8 mov ecx, dword ptr [ebp - 0x288]
0045f4fe mov eax, edx
0045f500 push dword ptr [ebp - 0x24c]
0045f506 shr eax, cl
0045f508 mov ecx, dword ptr [ebp - 0x284]
0045f50e xor edx, eax
0045f510 mov eax, edx
0045f512 shl eax, cl
0045f514 mov ecx, dword ptr [ebp - 0x240]
0045f51a xor edx, eax
0045f51c push 0
0045f51e mov eax, edx
0045f520 shr eax, cl
0045f522 mov ecx, dword ptr [0xbfd65c]
0045f528 xor edx, eax
0045f52a push 0
0045f52c push 0xc02fec
0045f531 lea eax, [ebp - 0x2ec]
0045f537 mov dword ptr [ebp - 0x244], edx
0045f53d push eax
0045f53e test dl, 1
0045f541 mov eax, 0x12
0045f546 push 0
0045f548 cmovne eax, esi
0045f54b push eax
0045f54c call 0x422e20
0045f551 and dword ptr [eax + 0x160], 0xfffffffb
0045f558 sub dword ptr [ebp - 0x254], 1
0045f55f mov ecx, dword ptr [eax + 0x164]
0045f565 mov dword ptr [eax + 0x164], ecx
0045f56b jne 0x45f405
0045f571 cmp byte ptr [ebp - 0x29c], 0
0045f578 jne 0x45f588
0045f57a push dword ptr [ebp - 0x298]
0045f580 call 0x9eace5
0045f585 add esp, 4
0045f588 mov ecx, dword ptr [ebp - 0xc]
0045f58b mov dword ptr fs:[0], ecx
0045f592 pop ecx
0045f593 pop edi
0045f594 pop esi
0045f595 mov ecx, dword ptr [ebp - 0x14]
0045f598 xor ecx, ebp
0045f59a call 0x9eacd7
0045f59f mov esp, ebp
0045f5a1 pop ebp
0045f5a2 mov esp, ebx
0045f5a4 pop ebx
0045f5a5 ret 
0045f5a6 nop 
