006adfd0 push ebp
006adfd1 mov ebp, esp
006adfd3 and esp, 0xfffffff8
006adfd6 sub esp, 0x1c
006adfd9 push ebx
006adfda push esi
006adfdb mov ebx, ecx
006adfdd mov esi, ebx
006adfdf mov dword ptr [esp + 0x20], ebx
006adfe3 push edi
006adfe4 mov dword ptr [esp + 0xc], esi
006adfe8 call 0x681710
006adfed test al, al
006adfef je 0x6ae010
006adff1 mov eax, dword ptr [ebx + 0x314]
006adff7 mov dword ptr [esp + 0xc], esi
006adffb test eax, eax
006adffd je 0x6ae010
006adfff nop 
006ae000 mov esi, eax
006ae002 mov dword ptr [esp + 0xc], eax
006ae006 mov eax, dword ptr [esi + 0x314]
006ae00c test eax, eax
006ae00e jne 0x6ae000
006ae010 test esi, esi
006ae012 je 0x6ae021
006ae014 mov eax, dword ptr [esi + 0x28]
006ae017 sub eax, 0xa
006ae01a cmp eax, 0x3dd
006ae01f jbe 0x6ae027
006ae021 mov esi, ebx
006ae023 mov dword ptr [esp + 0xc], esi
006ae027 movss xmm0, dword ptr [esi + 0xb90]
006ae02f xorps xmm1, xmm1
006ae032 comiss xmm0, xmm1
006ae035 jbe 0x6ae30e
006ae03b mov ecx, dword ptr [ebx + 0xc]
006ae03e mov eax, 0x92492493
006ae043 mov edi, dword ptr [ebx + 8]
006ae046 xorps xmm0, xmm0
006ae049 sub ecx, edi
006ae04b movss dword ptr [esp + 0x14], xmm0
006ae051 imul ecx
006ae053 add edx, ecx
006ae055 sar edx, 5
006ae058 mov ecx, edx
006ae05a shr ecx, 0x1f
006ae05d add ecx, edx
006ae05f je 0x6ae080
006ae061 mov eax, dword ptr [edi + 8]
006ae064 and eax, 0x2000
006ae069 or eax, 0
006ae06c jne 0x6ae072
006ae06e addss xmm0, dword ptr [edi]
006ae072 add edi, 0x38
006ae075 sub ecx, 1
006ae078 jne 0x6ae061
006ae07a movss dword ptr [esp + 0x14], xmm0
006ae080 mov eax, dword ptr [esi + 0xba8]
006ae086 cmp eax, dword ptr [esi + 0xb94]
006ae08c jb 0x6ae13d
006ae092 mov ecx, dword ptr [esi + 0xb98]
006ae098 xor eax, eax
006ae09a mov edi, dword ptr [esi + 0xba4]
006ae0a0 xor edx, edx
006ae0a2 mov dword ptr [esp + 0x10], edi
006ae0a6 test ecx, ecx
006ae0a8 je 0x6ae0b8
006ae0aa mov eax, dword ptr [ecx]
006ae0ac test eax, eax
006ae0ae je 0x6ae0b4
006ae0b0 mov eax, dword ptr [eax]
006ae0b2 jmp 0x6ae0b6
006ae0b4 xor eax, eax
006ae0b6 mov edx, eax
006ae0b8 sub esp, 0xc
006ae0bb mov ecx, esp
006ae0bd test edx, edx
006ae0bf je 0x6ae0f1
006ae0c1 mov edx, dword ptr [eax]
006ae0c3 test edx, edx
006ae0c5 je 0x6ae0cb
006ae0c7 mov edx, dword ptr [edx]
006ae0c9 jmp 0x6ae0cd
006ae0cb xor edx, edx
006ae0cd inc edi
006ae0ce mov dword ptr [ecx], 0
006ae0d4 mov dword ptr [ecx + 4], 0
006ae0db test edx, edx
006ae0dd je 0x6ae0ff
006ae0df mov edx, dword ptr [edx]
006ae0e1 test edx, edx
006ae0e3 je 0x6ae0eb
006ae0e5 mov edx, dword ptr [edx]
006ae0e7 mov dword ptr [ecx], edx
006ae0e9 jmp 0x6ae0ff
006ae0eb xor edx, edx
006ae0ed mov dword ptr [ecx], edx
006ae0ef jmp 0x6ae0ff
006ae0f1 mov dword ptr [ecx], 0
006ae0f7 inc edi
006ae0f8 mov dword ptr [ecx + 4], 0
006ae0ff mov dword ptr [ecx + 8], edi
006ae102 sub esp, 0xc
006ae105 mov ecx, esp
006ae107 mov dword ptr [ecx], 0
006ae10d mov dword ptr [ecx + 4], 0
006ae114 test eax, eax
006ae116 je 0x6ae126
006ae118 mov eax, dword ptr [eax]
006ae11a test eax, eax
006ae11c je 0x6ae122
006ae11e mov eax, dword ptr [eax]
006ae120 jmp 0x6ae124
006ae122 xor eax, eax
006ae124 mov dword ptr [ecx], eax
006ae126 mov eax, dword ptr [esp + 0x28]
006ae12a mov dword ptr [ecx + 8], eax
006ae12d lea eax, [esp + 0x30]
006ae131 push eax
006ae132 lea ecx, [esi + 0xb98]
006ae138 call 0x6b1650
006ae13d mov ecx, dword ptr [esi + 0xba8]
006ae143 lea edi, [esi + 0xb98]
006ae149 mov edx, dword ptr [edi + 0xc]
006ae14c mov dword ptr [esp + 0x10], ecx
006ae150 lea eax, [edx + ecx]
006ae153 test al, 3
006ae155 jne 0x6ae178
006ae157 lea eax, [ecx + 4]
006ae15a mov dword ptr [esp + 0x10], ecx
006ae15e shr eax, 2
006ae161 cmp dword ptr [edi + 8], eax
006ae164 ja 0x6ae178
006ae166 push ecx
006ae167 mov ecx, edi
006ae169 call 0x43dad0
006ae16e mov eax, dword ptr [edi + 0x10]
006ae171 mov edx, dword ptr [edi + 0xc]
006ae174 mov dword ptr [esp + 0x10], eax
006ae178 mov ecx, dword ptr [edi + 8]
006ae17b lea eax, [ecx*4 - 1]
006ae182 dec ecx
006ae183 and eax, edx
006ae185 mov edx, dword ptr [esp + 0x10]
006ae189 add edx, eax
006ae18b mov dword ptr [edi + 0xc], eax
006ae18e mov eax, edx
006ae190 mov dword ptr [esp + 0x18], edx
006ae194 shr eax, 2
006ae197 and ecx, eax
006ae199 mov eax, dword ptr [edi + 4]
006ae19c mov dword ptr [esp + 0x10], ecx
006ae1a0 cmp dword ptr [eax + ecx*4], 0
006ae1a4 jne 0x6ae1c3
006ae1a6 push 0x10
006ae1a8 call 0x9eacf8
006ae1ad mov edx, dword ptr [esp + 0x14]
006ae1b1 add esp, 4
006ae1b4 mov ecx, dword ptr [edi + 4]
006ae1b7 mov dword ptr [ecx + edx*4], eax
006ae1ba mov ecx, edx
006ae1bc mov eax, dword ptr [edi + 4]
006ae1bf mov edx, dword ptr [esp + 0x18]
006ae1c3 mov eax, dword ptr [eax + ecx*4]
006ae1c6 and edx, 3
006ae1c9 movss xmm0, dword ptr [esp + 0x14]
006ae1cf xorps xmm4, xmm4
006ae1d2 xorps xmm1, xmm1
006ae1d5 movss dword ptr [eax + edx*4], xmm0
006ae1da inc dword ptr [edi + 0x10]
006ae1dd mov eax, dword ptr [esi + 0xba8]
006ae1e3 mov dword ptr [esp + 0x14], eax
006ae1e7 test eax, eax
006ae1e9 je 0x6ae224
006ae1eb mov eax, dword ptr [edi + 0xc]
006ae1ee xor ebx, ebx
006ae1f0 mov esi, dword ptr [esp + 0x14]
006ae1f4 lea edx, [eax + ebx]
006ae1f7 mov eax, dword ptr [edi + 8]
006ae1fa dec eax
006ae1fb mov ecx, edx
006ae1fd shr ecx, 2
006ae200 and edx, 3
006ae203 and ecx, eax
006ae205 inc ebx
006ae206 mov eax, dword ptr [edi + 4]
006ae209 mov eax, dword ptr [eax + ecx*4]
006ae20c addss xmm1, dword ptr [eax + edx*4]
006ae211 mov eax, dword ptr [edi + 0xc]
006ae214 cmp ebx, esi
006ae216 jb 0x6ae1f4
006ae218 mov esi, dword ptr [esp + 0xc]
006ae21c mov ebx, dword ptr [esp + 0x24]
006ae220 mov eax, dword ptr [esp + 0x14]
006ae224 movss xmm3, dword ptr [ebx + 0x2dc]
006ae22c divss xmm3, dword ptr [esi + 0xb90]
006ae234 movd xmm0, eax
006ae238 cvtdq2pd xmm0, xmm0
006ae23c shr eax, 0x1f
006ae23f movss xmm2, dword ptr [0xb6a614]
006ae247 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
006ae250 cvtpd2ps xmm0, xmm0
006ae254 divss xmm1, xmm0
006ae258 mulss xmm1, dword ptr [0xb6aa0c]
006ae260 comiss xmm1, xmm3
006ae263 jbe 0x6ae288
006ae265 divss xmm3, xmm1
006ae269 movss xmm2, dword ptr [0xb6a2b4]
006ae271 movaps xmm0, xmm3
006ae274 mulss xmm0, dword ptr [0xb6a330]
006ae27c subss xmm2, xmm0
006ae280 maxss xmm2, xmm4
006ae284 addss xmm2, xmm3
006ae288 xor ecx, ecx
006ae28a mov dword ptr [ebx + 0x14], 0
006ae291 mov esi, dword ptr [ebx + 8]
006ae294 mov eax, 0x92492493
006ae299 mov dword ptr [esp + 0x10], ecx
006ae29d mov ecx, dword ptr [ebx + 0xc]
006ae2a0 sub ecx, esi
006ae2a2 imul ecx
006ae2a4 add edx, ecx
006ae2a6 sar edx, 5
006ae2a9 mov eax, edx
006ae2ab shr eax, 0x1f
006ae2ae add eax, edx
006ae2b0 je 0x6ae30e
006ae2b2 xor edi, edi
006ae2b4 nop dword ptr [eax]
006ae2b8 nop dword ptr [eax + eax]
006ae2c0 mov eax, dword ptr [edi + esi + 8]
006ae2c4 movss xmm0, dword ptr [edi + esi]
006ae2c9 and eax, 0x40002000
006ae2ce or eax, 0
006ae2d1 jne 0x6ae2dc
006ae2d3 mulss xmm0, xmm2
006ae2d7 movss dword ptr [edi + esi], xmm0
006ae2dc addss xmm0, dword ptr [ebx + 0x14]
006ae2e1 inc dword ptr [esp + 0x10]
006ae2e5 mov eax, 0x92492493
006ae2ea add edi, 0x38
006ae2ed movss dword ptr [ebx + 0x14], xmm0
006ae2f2 mov ecx, dword ptr [ebx + 0xc]
006ae2f5 mov esi, dword ptr [ebx + 8]
006ae2f8 sub ecx, esi
006ae2fa imul ecx
006ae2fc add edx, ecx
006ae2fe sar edx, 5
006ae301 mov eax, edx
006ae303 shr eax, 0x1f
006ae306 add eax, edx
006ae308 cmp dword ptr [esp + 0x10], eax
006ae30c jb 0x6ae2c0
006ae30e pop edi
006ae30f pop esi
006ae310 pop ebx
006ae311 mov esp, ebp
006ae313 pop ebp
006ae314 ret 
