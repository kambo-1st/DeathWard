004feb40 push ebp
004feb41 mov ebp, esp
004feb43 and esp, 0xfffffff8
004feb46 sub esp, 0x11c
004feb4c mov eax, dword ptr [0xbaa3b4]
004feb51 xor eax, esp
004feb53 mov dword ptr [esp + 0x118], eax
004feb5a push ebx
004feb5b push esi
004feb5c push edi
004feb5d mov edi, ecx
004feb5f cmp dword ptr [edi + 0xab4], 0
004feb66 jne 0x4fec00
004feb6c cmp dword ptr [edi + 0x2c], 2
004feb70 mov dword ptr [edi + 0xab4], 4
004feb7a jne 0x4ff1e2
004feb80 call 0x6c3d90
004feb85 mov ecx, dword ptr [0xbfd65c]
004feb8b push 0
004feb8d push eax
004feb8e push 0
004feb90 push edi
004feb91 push 0xc02fec
004feb96 lea eax, [edi + 0x294]
004feb9c push eax
004feb9d push 0
004feb9f push 0x60
004feba1 call 0x6d0ca0
004feba6 push 0
004feba8 push 0xbeab70
004febad push 0xbeab18
004febb2 push 0
004febb4 push eax
004febb5 call 0x9ec34c
004febba mov ecx, dword ptr [eax + 0x314]
004febc0 add esp, 0x14
004febc3 lea esi, [eax + 0x314]
004febc9 test ecx, ecx
004febcb je 0x4febe1
004febcd lea eax, [esp + 0x1c]
004febd1 mov dword ptr [esp + 0x1c], esi
004febd5 push eax
004febd6 add ecx, 0x324
004febdc call 0x4bc3c0
004febe1 push esi
004febe2 mov ecx, edi
004febe4 mov dword ptr [esi], edi
004febe6 call 0x4bae70
004febeb pop edi
004febec pop esi
004febed pop ebx
004febee mov ecx, dword ptr [esp + 0x118]
004febf5 xor ecx, esp
004febf7 call 0x9eacd7
004febfc mov esp, ebp
004febfe pop ebp
004febff ret 
004fec00 mov ecx, dword ptr [0xbfd65c]
004fec06 lea ebx, [edi + 0x294]
004fec0c movss xmm0, dword ptr [0xb6a974]
004fec14 lea eax, [esp + 0x14]
004fec18 sub esp, 0xc
004fec1b movss dword ptr [esp + 0x28], xmm0
004fec21 xorps xmm3, xmm3
004fec24 mov ecx, dword ptr [ecx + 0x18190]
004fec2a mov dword ptr [esp + 8], 0x41200000
004fec32 mov dword ptr [esp + 4], 0
004fec3a mov dword ptr [esp], 0x41f00000
004fec41 push ebx
004fec42 push eax
004fec43 call 0x7cec10
004fec48 mov ecx, dword ptr [eax]
004fec4a mov dword ptr [ebx], ecx
004fec4c mov eax, dword ptr [eax + 4]
004fec4f mov dword ptr [ebx + 4], eax
004fec52 call 0x6c3d90
004fec57 xor edx, edx
004fec59 mov ecx, 0xa
004fec5e div ecx
004fec60 test edx, edx
004fec62 jne 0x4feca6
004fec64 call 0x6c3d90
004fec69 push ecx
004fec6a mov ecx, edi
004fec6c movd xmm0, eax
004fec70 cvtdq2pd xmm0, xmm0
004fec74 shr eax, 0x1f
004fec77 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
004fec80 cvtpd2ps xmm0, xmm0
004fec84 mulss xmm0, dword ptr [0xb6a19c]
004fec8c mulss xmm0, dword ptr [0xb6a480]
004fec94 addss xmm0, dword ptr [0xb6a434]
004fec9c movss dword ptr [esp], xmm0
004feca1 call 0x68d7b0
004feca6 push ecx
004feca7 lea eax, [esp + 0x18]
004fecab mov dword ptr [esp], 0
004fecb2 push eax
004fecb3 mov ecx, edi
004fecb5 call 0x695a30
004fecba cmp dword ptr [edi + 0xe6c], -1
004fecc1 movss xmm1, dword ptr [eax]
004fecc5 subss xmm1, dword ptr [ebx]
004fecc9 movss dword ptr [esp + 0xc], xmm1
004feccf movss xmm1, dword ptr [eax + 4]
004fecd4 subss xmm1, dword ptr [ebx + 4]
004fecd9 movss dword ptr [esp + 0x10], xmm1
004fecdf je 0x4fed05
004fece1 lea eax, [esp + 0x14]
004fece5 xorps xmm2, xmm2
004fece8 push eax
004fece9 mov ecx, edi
004feceb call 0x6af0c0
004fecf0 movss xmm0, dword ptr [eax]
004fecf4 movss dword ptr [esp + 0xc], xmm0
004fecfa movss xmm0, dword ptr [eax + 4]
004fecff movss dword ptr [esp + 0x10], xmm0
004fed05 mov eax, dword ptr [edi + 0xab4]
004fed0b cmp eax, 4
004fed0e jne 0x4fee83
004fed14 mov eax, dword ptr [edi + 0x70]
004fed17 test eax, eax
004fed19 je 0x4fed21
004fed1b cmp byte ptr [eax + 0x34], 0
004fed1f jne 0x4fed30
004fed21 push 0
004fed23 push 0xb3fd8c
004fed28 lea ecx, [edi + 0x3c]
004fed2b call 0x4054f0
004fed30 cmp dword ptr [edi + 0x2c], 1
004fed34 je 0x4fedd1
004fed3a cmp dword ptr [edi + 0xaf0], 0
004fed41 jg 0x4fedd1
004fed47 movss xmm1, dword ptr [0xb6aba8]
004fed4f mov ecx, edi
004fed51 push 7
004fed53 push 0
004fed55 call 0x6a15a0
004fed5a test al, al
004fed5c je 0x4fedd1
004fed5e push 1
004fed60 push 0xb400ac
004fed65 lea ecx, [edi + 0x3c]
004fed68 mov dword ptr [edi + 0xab4], 8
004fed72 call 0x405740
004fed77 test al, al
004fed79 je 0x4fed8a
004fed7b lea ecx, [edi + 0x6c]
004fed7e call 0x405330
004fed83 mov byte ptr [edi + 0x80], 1
004fed8a push 1
004fed8c mov ecx, edi
004fed8e mov dword ptr [edi + 0xaf0], 0x1c
004fed98 call 0x6afe20
004fed9d movss xmm1, dword ptr [esp + 0xc]
004feda3 xor eax, eax
004feda5 cmp dword ptr [edi + 0xe6c], -1
004fedac xorps xmm0, xmm0
004fedaf je 0x4fedc3
004fedb1 comiss xmm0, dword ptr [edi + 0xe70]
004fedb8 seta al
004fedbb mov byte ptr [edi + 0x13c], al
004fedc1 jmp 0x4fedd7
004fedc3 comiss xmm0, xmm1
004fedc6 seta al
004fedc9 mov byte ptr [edi + 0x13c], al
004fedcf jmp 0x4fedd7
004fedd1 movss xmm1, dword ptr [esp + 0xc]
004fedd7 movaps xmm0, xmm1
004fedda mulss xmm0, xmm1
004fedde movss xmm1, dword ptr [esp + 0x10]
004fede4 mulss xmm1, xmm1
004fede8 addss xmm0, xmm1
004fedec call 0x4228c0
004fedf1 movaps xmm2, xmm0
004fedf4 xorps xmm0, xmm0
004fedf7 comiss xmm2, xmm0
004fedfa jbe 0x4ff14e
004fee00 cmp dword ptr [edi + 0x2c], 1
004fee04 movss xmm1, dword ptr [0xb6a2f0]
004fee0c divss xmm1, xmm2
004fee10 jne 0x4fee1a
004fee12 mulss xmm1, dword ptr [0xb6a864]
004fee1a movss xmm4, dword ptr [edi + 0x2c4]
004fee22 movss xmm2, dword ptr [esp + 0xc]
004fee28 movss xmm3, dword ptr [esp + 0x10]
004fee2e ucomiss xmm4, xmm0
004fee31 mulss xmm2, xmm1
004fee35 lahf 
004fee36 mulss xmm3, xmm1
004fee3a test ah, 0x44
004fee3d jnp 0x4ff14e
004fee43 movss xmm1, dword ptr [edi + 0x2f4]
004fee4b movaps xmm0, xmm1
004fee4e mulss xmm1, xmm3
004fee52 mulss xmm0, xmm2
004fee56 divss xmm1, xmm4
004fee5a divss xmm0, xmm4
004fee5e addss xmm1, dword ptr [edi + 0x2bc]
004fee66 addss xmm0, dword ptr [edi + 0x2b8]
004fee6e movss dword ptr [edi + 0x2bc], xmm1
004fee76 movss dword ptr [edi + 0x2b8], xmm0
004fee7e jmp 0x4ff14e
004fee83 cmp eax, 8
004fee86 jne 0x4ff14e
004fee8c push 0
004fee8e mov ecx, edi
004fee90 call 0x6afe20
004fee95 cmp dword ptr [edi + 0x70], 0
004fee99 je 0x4ff0cd
004fee9f push 0xb400ac
004feea4 lea ecx, [edi + 0x6c]
004feea7 call 0x405e90
004feeac test al, al
004feeae je 0x4ff0ba
004feeb4 cmp dword ptr [edi + 0x2c], 2
004feeb8 mov eax, 0xb2
004feebd push ecx
004feebe mov dword ptr [esp], 0x3f800000
004feec5 push 0
004feec7 push 2
004feec9 push ecx
004feeca mov ecx, 0x92
004feecf mov dword ptr [esp], 0x3f800000
004feed6 cmovne eax, ecx
004feed9 mov ecx, edi
004feedb push eax
004feedc call 0x6ad720
004feee1 mov ecx, edi
004feee3 call 0x695680
004feee8 cmp dword ptr [edi + 0xe6c], -1
004feeef movss xmm2, dword ptr [eax + 0x294]
004feef7 movss xmm1, dword ptr [eax + 0x298]
004feeff subss xmm2, dword ptr [ebx]
004fef03 subss xmm1, dword ptr [ebx + 4]
004fef08 movss dword ptr [esp + 0x10], xmm2
004fef0e movss dword ptr [esp + 0x14], xmm2
004fef14 movss dword ptr [esp + 0xc], xmm1
004fef1a movss dword ptr [esp + 0x18], xmm1
004fef20 je 0x4fef57
004fef22 lea ecx, [edi + 0xe70]
004fef28 push 0xc02fec
004fef2d call 0x962ca0
004fef32 test al, al
004fef34 je 0x4fef57
004fef36 movss xmm2, dword ptr [ecx]
004fef3a movss xmm1, dword ptr [ecx + 4]
004fef3f movss dword ptr [esp + 0x10], xmm2
004fef45 movss dword ptr [esp + 0x14], xmm2
004fef4b movss dword ptr [esp + 0xc], xmm1
004fef51 movss dword ptr [esp + 0x18], xmm1
004fef57 call 0x6af030
004fef5c test eax, eax
004fef5e jg 0x4fef6e
004fef60 movss xmm0, dword ptr [0xb6a928]
004fef68 movss dword ptr [esp + 0x1c], xmm0
004fef6e movaps xmm0, xmm1
004fef71 mulss xmm0, xmm1
004fef75 movaps xmm1, xmm2
004fef78 mulss xmm1, xmm2
004fef7c addss xmm0, xmm1
004fef80 call 0x4228c0
004fef85 comiss xmm0, dword ptr [0xb6a18c]
004fef8c jbe 0x4fefb8
004fef8e movss xmm1, dword ptr [esp + 0x1c]
004fef94 divss xmm1, xmm0
004fef98 movss xmm0, dword ptr [esp + 0x10]
004fef9e mulss xmm0, xmm1
004fefa2 movss dword ptr [esp + 0x14], xmm0
004fefa8 movss xmm0, dword ptr [esp + 0xc]
004fefae mulss xmm0, xmm1
004fefb2 movss dword ptr [esp + 0x18], xmm0
004fefb8 push 0xc02fec
004fefbd lea ecx, [esp + 0xfc]
004fefc4 mov dword ptr [esp + 0x20], 0
004fefcc mov dword ptr [esp + 0x24], 0xc1c00000
004fefd4 call 0x402120
004fefd9 push eax
004fefda lea eax, [esp + 0x24]
004fefde mov edx, ebx
004fefe0 push eax
004fefe1 mov ecx, 5
004fefe6 call 0x6aead0
004fefeb add esp, 0xc
004fefee mov esi, eax
004feff0 mov ecx, esi
004feff2 push edi
004feff3 mov dword ptr [esi + 0x2b0], 0x3f800000
004feffd call 0x447de0
004ff002 lea ecx, [esp + 0x50]
004ff006 mov byte ptr [esi + 0x13c], 1
004ff00d call 0x430d70
004ff012 cmp dword ptr [edi + 0x2c], 2
004ff016 lea ecx, [esp + 0x24]
004ff01a push 1
004ff01c push 0
004ff01e push 0xff
004ff023 push -1
004ff025 push ecx
004ff026 mov ecx, esi
004ff028 jne 0x4ff075
004ff02a movaps xmm0, xmmword ptr [0xb6bb40]
004ff031 mov eax, dword ptr [esp + 0xc0]
004ff038 or dword ptr [esp + 0xbc], 1
004ff040 movups xmmword ptr [esp + 0x38], xmm0
004ff045 mov dword ptr [esp + 0x78], 0x3fc00000
004ff04d movaps xmm0, xmmword ptr [0xb6c550]
004ff054 mov dword ptr [esp + 0xc0], eax
004ff05b mov dword ptr [esp + 0x58], 0x3e851eb8
004ff063 mov dword ptr [esp + 0x5c], 0x3d4ccccd
004ff06b mov dword ptr [esp + 0x60], 0x3ecccccd
004ff073 jmp 0x4ff09c
004ff075 movaps xmm0, xmmword ptr [0xb6b9f0]
004ff07c movups xmmword ptr [esp + 0x38], xmm0
004ff081 mov dword ptr [esp + 0x58], 0x3f19999a
004ff089 xorps xmm0, xmm0
004ff08c mov dword ptr [esp + 0x5c], 0x3dcccccd
004ff094 mov dword ptr [esp + 0x60], 0x3dcccccd
004ff09c mov eax, dword ptr [esi]
004ff09e movups xmmword ptr [esp + 0x48], xmm0
004ff0a3 call dword ptr [eax + 0x38]
004ff0a6 lea eax, [esp + 0x50]
004ff0aa mov ecx, edi
004ff0ac push eax
004ff0ad push 0
004ff0af lea eax, [esp + 0x1c]
004ff0b3 push eax
004ff0b4 push ebx
004ff0b5 call 0x6a1a20
004ff0ba cmp dword ptr [edi + 0x70], 0
004ff0be je 0x4ff0cd
004ff0c0 cmp byte ptr [edi + 0x80], 0
004ff0c7 jne 0x4ff14e
004ff0cd mov dword ptr [edi + 0xab4], 4
004ff0d7 mov esi, dword ptr [edi + 0x70]
004ff0da test esi, esi
004ff0dc je 0x4ff126
004ff0de cmp dword ptr [esi + 0x14], 0x10
004ff0e2 mov eax, esi
004ff0e4 jb 0x4ff0e8
004ff0e6 mov eax, dword ptr [esi]
004ff0e8 mov ecx, 0xb3fd8c
004ff0ed nop dword ptr [eax]
004ff0f0 mov dl, byte ptr [eax]
004ff0f2 cmp dl, byte ptr [ecx]
004ff0f4 jne 0x4ff110
004ff0f6 test dl, dl
004ff0f8 je 0x4ff10c
004ff0fa mov dl, byte ptr [eax + 1]
004ff0fd cmp dl, byte ptr [ecx + 1]
004ff100 jne 0x4ff110
004ff102 add eax, 2
004ff105 add ecx, 2
004ff108 test dl, dl
004ff10a jne 0x4ff0f0
004ff10c xor eax, eax
004ff10e jmp 0x4ff115
004ff110 sbb eax, eax
004ff112 or eax, 1
004ff115 test eax, eax
004ff117 jne 0x4ff126
004ff119 cmp byte ptr [esi + 0x34], al
004ff11c je 0x4ff148
004ff11e cmp byte ptr [edi + 0x80], al
004ff124 jne 0x4ff148
004ff126 push 1
004ff128 push 0xb3fd8c
004ff12d lea ecx, [edi + 0x3c]
004ff130 call 0x405740
004ff135 test al, al
004ff137 je 0x4ff148
004ff139 lea ecx, [edi + 0x6c]
004ff13c call 0x405330
004ff141 mov byte ptr [edi + 0x80], 1
004ff148 lea ebx, [edi + 0x294]
004ff14e mov edx, dword ptr [edi + 0xaf0]
004ff154 test edx, edx
004ff156 jle 0x4ff172
004ff158 cvttss2si eax, dword ptr [edi + 0x2fc]
004ff160 cvttss2si ecx, dword ptr [edi + 0x2f8]
004ff168 sub ecx, eax
004ff16a add ecx, edx
004ff16c mov dword ptr [edi + 0xaf0], ecx
004ff172 cmp byte ptr [edi + 0x16b], 0
004ff179 movss xmm0, dword ptr [edi + 0x2c4]
004ff181 mulss xmm0, dword ptr [0xb6a5c4]
004ff189 movss dword ptr [edi + 0x2c4], xmm0
004ff191 je 0x4ff1e2
004ff193 cmp dword ptr [edi + 0x2c], 1
004ff197 jne 0x4ff1e2
004ff199 lea ecx, [esp + 0x50]
004ff19d mov dword ptr [esp + 0x14], 0x41000000
004ff1a5 mov dword ptr [esp + 0x18], 0
004ff1ad call 0x430d70
004ff1b2 push eax
004ff1b3 push 6
004ff1b5 lea eax, [esp + 0x1c]
004ff1b9 mov ecx, edi
004ff1bb push eax
004ff1bc push ebx
004ff1bd call 0x6a1a20
004ff1c2 push ecx
004ff1c3 mov dword ptr [esp], 0x3f800000
004ff1ca push 0
004ff1cc push 2
004ff1ce push ecx
004ff1cf mov dword ptr [esp], 0x3f800000
004ff1d6 mov ecx, edi
004ff1d8 push 0x92
004ff1dd call 0x6ad720
004ff1e2 mov ecx, dword ptr [esp + 0x124]
004ff1e9 pop edi
004ff1ea pop esi
004ff1eb pop ebx
004ff1ec xor ecx, esp
004ff1ee call 0x9eacd7
004ff1f3 mov esp, ebp
004ff1f5 pop ebp
004ff1f6 ret 
