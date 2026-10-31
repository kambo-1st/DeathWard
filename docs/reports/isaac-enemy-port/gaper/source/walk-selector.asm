006980a0 push ebp
006980a1 mov ebp, esp
006980a3 and esp, 0xfffffff8
006980a6 sub esp, 8
006980a9 push esi
006980aa push edi
006980ab mov edi, ecx
006980ad cmp byte ptr [edi + 0xbb3], 0
006980b4 je 0x6980d6
006980b6 movss xmm0, dword ptr [0xb6a614]
006980be comiss xmm0, dword ptr [edi + 0xafc]
006980c5 jbe 0x6980d6
006980c7 movss xmm2, dword ptr [ebp + 0x10]
006980cc mulss xmm2, dword ptr [0xb6a480]
006980d4 jmp 0x6980db
006980d6 movss xmm2, dword ptr [ebp + 0x10]
006980db movss xmm3, dword ptr [edi + 0x2b8]
006980e3 movss xmm1, dword ptr [edi + 0x2bc]
006980eb movaps xmm0, xmm3
006980ee mulss xmm0, xmm3
006980f2 mulss xmm1, xmm1
006980f6 mulss xmm2, xmm2
006980fa addss xmm0, xmm1
006980fe comiss xmm2, xmm0
00698101 jbe 0x698168
00698103 mov eax, dword ptr [ebp + 0xc]
00698106 cmp dword ptr [eax + 0x14], 0x10
0069810a jb 0x69810e
0069810c mov eax, dword ptr [eax]
0069810e push 1
00698110 push eax
00698111 lea ecx, [edi + 0x3c]
00698114 call 0x405740
00698119 test al, al
0069811b je 0x69813d
0069811d mov eax, dword ptr [edi + 0x70]
00698120 test eax, eax
00698122 je 0x69813d
00698124 lea ecx, [edi + 0x6c]
00698127 xorps xmm1, xmm1
0069812a call 0x403c00
0069812f mov eax, dword ptr [edi + 0x70]
00698132 test eax, eax
00698134 je 0x69813d
00698136 mov byte ptr [edi + 0x80], 0
0069813d mov edx, 3
00698142 lea ecx, [esp + 8]
00698146 call 0x659400
0069814b mov ecx, dword ptr [eax]
0069814d mov dword ptr [edi + 0xe80], ecx
00698153 movss xmm0, dword ptr [eax + 4]
00698158 movss dword ptr [edi + 0xe84], xmm0
00698160 pop edi
00698161 pop esi
00698162 mov esp, ebp
00698164 pop ebp
00698165 ret 0xc
00698168 movss xmm0, dword ptr [edi + 0x2bc]
00698170 xorps xmm2, xmm2
00698173 andps xmm3, xmmword ptr [0xb6c980]
0069817a andps xmm0, xmmword ptr [0xb6c980]
00698181 comiss xmm3, xmm0
00698184 jbe 0x698223
0069818a mov ecx, dword ptr [ebp + 8]
0069818d cmp dword ptr [ecx + 0x14], 0x10
00698191 jb 0x698198
00698193 mov ecx, dword ptr [ecx]
00698195 mov dword ptr [ebp + 8], ecx
00698198 mov ecx, dword ptr [edi + 0x70]
0069819b test ecx, ecx
0069819d je 0x6981eb
0069819f cmp dword ptr [ecx + 0x14], 0x10
006981a3 mov eax, ecx
006981a5 jb 0x6981a9
006981a7 mov eax, dword ptr [ecx]
006981a9 mov ecx, dword ptr [ebp + 8]
006981ac nop dword ptr [eax]
006981b0 mov dl, byte ptr [eax]
006981b2 cmp dl, byte ptr [ecx]
006981b4 jne 0x6981d0
006981b6 test dl, dl
006981b8 je 0x6981cc
006981ba mov dl, byte ptr [eax + 1]
006981bd cmp dl, byte ptr [ecx + 1]
006981c0 jne 0x6981d0
006981c2 add eax, 2
006981c5 add ecx, 2
006981c8 test dl, dl
006981ca jne 0x6981b0
006981cc xor eax, eax
006981ce jmp 0x6981d5
006981d0 sbb eax, eax
006981d2 or eax, 1
006981d5 test eax, eax
006981d7 jne 0x6981eb
006981d9 mov eax, dword ptr [edi + 0x70]
006981dc cmp byte ptr [eax + 0x34], 0
006981e0 je 0x69820e
006981e2 cmp byte ptr [edi + 0x80], 0
006981e9 jne 0x69820e
006981eb push 1
006981ed push dword ptr [ebp + 8]
006981f0 lea ecx, [edi + 0x3c]
006981f3 call 0x405740
006981f8 test al, al
006981fa je 0x69820b
006981fc lea ecx, [edi + 0x6c]
006981ff call 0x405330
00698204 mov byte ptr [edi + 0x80], 1
0069820b xorps xmm2, xmm2
0069820e comiss xmm2, dword ptr [edi + 0x2b8]
00698215 seta al
00698218 mov byte ptr [edi + 0x13c], al
0069821e jmp 0x6982af
00698223 mov ecx, dword ptr [ebp + 0xc]
00698226 mov dword ptr [esp + 8], ecx
0069822a cmp dword ptr [ecx + 0x14], 0x10
0069822e jb 0x698236
00698230 mov ecx, dword ptr [ecx]
00698232 mov dword ptr [esp + 8], ecx
00698236 mov ecx, dword ptr [edi + 0x70]
00698239 test ecx, ecx
0069823b je 0x69828b
0069823d cmp dword ptr [ecx + 0x14], 0x10
00698241 mov eax, ecx
00698243 jb 0x698247
00698245 mov eax, dword ptr [ecx]
00698247 mov ecx, dword ptr [esp + 8]
0069824b nop dword ptr [eax + eax]
00698250 mov dl, byte ptr [eax]
00698252 cmp dl, byte ptr [ecx]
00698254 jne 0x698270
00698256 test dl, dl
00698258 je 0x69826c
0069825a mov dl, byte ptr [eax + 1]
0069825d cmp dl, byte ptr [ecx + 1]
00698260 jne 0x698270
00698262 add eax, 2
00698265 add ecx, 2
00698268 test dl, dl
0069826a jne 0x698250
0069826c xor eax, eax
0069826e jmp 0x698275
00698270 sbb eax, eax
00698272 or eax, 1
00698275 test eax, eax
00698277 jne 0x69828b
00698279 mov eax, dword ptr [edi + 0x70]
0069827c cmp byte ptr [eax + 0x34], 0
00698280 je 0x6982af
00698282 cmp byte ptr [edi + 0x80], 0
00698289 jne 0x6982af
0069828b push 1
0069828d push dword ptr [esp + 0xc]
00698291 lea ecx, [edi + 0x3c]
00698294 call 0x405740
00698299 test al, al
0069829b je 0x6982ac
0069829d lea ecx, [edi + 0x6c]
006982a0 call 0x405330
006982a5 mov byte ptr [edi + 0x80], 1
006982ac xorps xmm2, xmm2
006982af movss xmm3, dword ptr [edi + 0x2b8]
006982b7 movss xmm4, dword ptr [edi + 0x2bc]
006982bf movaps xmm1, xmm3
006982c2 andps xmm1, xmmword ptr [0xb6c980]
006982c9 movaps xmm0, xmm4
006982cc andps xmm0, xmmword ptr [0xb6c980]
006982d3 comiss xmm1, xmm0
006982d6 jbe 0x6982f1
006982d8 comiss xmm2, xmm3
006982db jbe 0x6982e7
006982dd movss xmm0, dword ptr [0xb6ae44]
006982e5 jmp 0x69830b
006982e7 movss xmm0, dword ptr [0xb6a614]
006982ef jmp 0x69830b
006982f1 comiss xmm2, xmm4
006982f4 movaps xmm0, xmm2
006982f7 jbe 0x698303
006982f9 movss xmm2, dword ptr [0xb6ae44]
00698301 jmp 0x69830b
00698303 movss xmm2, dword ptr [0xb6a614]
0069830b movss dword ptr [edi + 0xe80], xmm0
00698313 movss dword ptr [edi + 0xe84], xmm2
0069831b pop edi
0069831c pop esi
0069831d mov esp, ebp
0069831f pop ebp
00698320 ret 0xc
