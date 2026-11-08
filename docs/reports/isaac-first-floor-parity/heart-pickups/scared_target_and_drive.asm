006bada1 cmp eax, 0xa
006bada4 jne 0x6bb18c
006badaa cmp dword ptr [edi + 0x30], 9
006badae jne 0x6bb18c
006badb4 cmp dword ptr [edi + 0x480], 0
006badbb jne 0x6bb18c
006badc1 cmp byte ptr [edi + 0x16b], 0
006badc8 jne 0x6bb18c
006badce lea eax, [edi + 0x294]
006badd4 mov ecx, esi
006badd6 push eax
006badd7 call 0x6d5e30
006baddc movss xmm3, dword ptr [0xb6aa60]
006bade4 lea esi, [edi + 0x294]
006badea push 1
006badec push esi
006baded movss xmm0, dword ptr [eax + 0x2b8]
006badf5 movss xmm1, dword ptr [eax + 0x2bc]
006badfd addss xmm0, xmm0
006bae01 addss xmm1, xmm1
006bae05 addss xmm0, dword ptr [eax + 0x294]
006bae0d addss xmm1, dword ptr [eax + 0x298]
006bae15 lea eax, [ebp - 0x40]
006bae18 push eax
006bae19 mov eax, dword ptr [0xbfd65c]
006bae1e subss xmm0, dword ptr [esi]
006bae22 subss xmm1, dword ptr [esi + 4]
006bae27 mov ecx, dword ptr [eax + 0x18190]
006bae2d add ecx, 0x1218
006bae33 movss dword ptr [ebp - 0xc4], xmm0
006bae3b movss dword ptr [ebp - 0xbc], xmm1
006bae43 call 0x4157f0
006bae48 xor ecx, ecx
006bae4a mov dword ptr [ebp - 4], 3
006bae51 cmp dword ptr [ebp - 0x34], ecx
006bae54 jbe 0x6baefb
006bae5a nop word ptr [eax + eax]
006bae60 mov eax, dword ptr [ebp - 0x3c]
006bae63 mov eax, dword ptr [eax + ecx*4]
006bae66 cmp dword ptr [eax + 0x28], 3
006bae6a jne 0x6baef1
006bae70 mov edx, dword ptr [eax + 0x2c]
006bae73 cmp edx, 0x40
006bae76 je 0x6bae7d
006bae78 cmp edx, 0x66
006bae7b jne 0x6baef1
006bae7d movss xmm3, dword ptr [eax + 0x2b8]
006bae85 movss xmm4, dword ptr [eax + 0x2bc]
006bae8d addss xmm3, xmm3
006bae91 movss xmm1, dword ptr [ebp - 0xc4]
006bae99 addss xmm4, xmm4
006bae9d mulss xmm1, xmm1
006baea1 addss xmm3, dword ptr [eax + 0x294]
006baea9 addss xmm4, dword ptr [eax + 0x298]
006baeb1 subss xmm3, dword ptr [esi]
006baeb5 subss xmm4, dword ptr [esi + 4]
006baeba movaps xmm0, xmm3
006baebd movaps xmm2, xmm4
006baec0 mulss xmm0, xmm3
006baec4 mulss xmm2, xmm4
006baec8 addss xmm2, xmm0
006baecc movss xmm0, dword ptr [ebp - 0xbc]
006baed4 mulss xmm0, xmm0
006baed8 addss xmm1, xmm0
006baedc comiss xmm1, xmm2
006baedf jbe 0x6baef1
006baee1 movss dword ptr [ebp - 0xc4], xmm3
006baee9 movss dword ptr [ebp - 0xbc], xmm4
006baef1 inc ecx
006baef2 cmp ecx, dword ptr [ebp - 0x34]
006baef5 jb 0x6bae60
006baefb movss xmm0, dword ptr [ebp - 0xbc]
006baf03 movss xmm2, dword ptr [ebp - 0xc4]
006baf0b mulss xmm0, xmm0
006baf0f mulss xmm2, xmm2
006baf13 addss xmm2, xmm0
006baf17 movss xmm0, dword ptr [0xb6acf4]
006baf1f comiss xmm0, xmm2
006baf22 movss dword ptr [ebp - 0x9c], xmm2
006baf2a jbe 0x6bb129
006baf30 mov eax, dword ptr [0xbfd65c]
006baf35 movq xmm0, qword ptr [0xa08c44]
006baf3d movq qword ptr [ebp - 0xb4], xmm0
006baf45 mov ecx, dword ptr [eax + 0x1a30dc]
006baf4b mov eax, 0x66666667
006baf50 sub ecx, dword ptr [edi + 0x280]
006baf56 imul ecx
006baf58 mov ecx, dword ptr [edi + 0x344]
006baf5e sar edx, 2
006baf61 mov eax, edx
006baf63 shr eax, 0x1f
006baf66 add eax, edx
006baf68 imul ecx, eax
006baf6b mov eax, 1
006baf70 test ecx, ecx
006baf72 cmove ecx, eax
006baf75 mov eax, dword ptr [0xa08c4c]
006baf7a mov dword ptr [ebp - 0xb8], ecx
006baf80 lea ecx, [ebp - 0xb8]
006baf86 mov dword ptr [ebp - 0xac], eax
006baf8c call 0x7a7e20
006baf91 mov eax, dword ptr [ebp - 0xb8]
006baf97 movd xmm0, eax
006baf9b cvtdq2pd xmm0, xmm0
006baf9f shr eax, 0x1f
006bafa2 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
006bafab cvtpd2ps xmm0, xmm0
006bafaf mulss xmm0, dword ptr [0xb6a198]
006bafb7 mulss xmm0, dword ptr [0xb6ab88]
006bafbf subss xmm0, dword ptr [0xb6aae4]
006bafc7 movss dword ptr [ebp - 0xac], xmm0
006bafcf movss xmm0, dword ptr [ebp - 0x9c]
006bafd7 mulss xmm0, dword ptr [0xb6a864]
006bafdf divss xmm0, dword ptr [0xb6acf4]
006bafe7 movss dword ptr [ebp - 0x94], xmm0
006bafef movss xmm0, dword ptr [ebp - 0x9c]
006baff7 call 0x4228c0
006baffc movaps xmm1, xmm0
006bafff comiss xmm1, dword ptr [0xb6a18c]
006bb006 jbe 0x6bb031
006bb008 movss xmm0, dword ptr [ebp - 0x94]
006bb010 divss xmm0, xmm1
006bb014 movaps xmm1, xmm0
006bb017 mulss xmm0, dword ptr [ebp - 0xbc]
006bb01f mulss xmm1, dword ptr [ebp - 0xc4]
006bb027 movss dword ptr [ebp - 0x8c], xmm1
006bb02f jmp 0x6bb049
006bb031 movss xmm0, dword ptr [ebp - 0xc4]
006bb039 movss dword ptr [ebp - 0x8c], xmm0
006bb041 movss xmm0, dword ptr [ebp - 0xbc]
006bb049 movss dword ptr [ebp - 0x94], xmm0
006bb051 movss xmm0, dword ptr [ebp - 0xac]
006bb059 mulss xmm0, dword ptr [0xb6a230]
006bb061 movss dword ptr [ebp - 0xac], xmm0
006bb069 call 0x411fe0
006bb06e movss dword ptr [ebp - 0x9c], xmm0
006bb076 movss xmm0, dword ptr [ebp - 0xac]
006bb07e call 0x412010
006bb083 movss xmm2, dword ptr [edi + 0x2c4]
006bb08b movaps xmm1, xmm0
006bb08e movss xmm3, dword ptr [ebp - 0x9c]
006bb096 ucomiss xmm2, dword ptr [0xb6a18c]
006bb09d mulss xmm1, dword ptr [ebp - 0x94]
006bb0a5 movaps xmm4, xmm3
006bb0a8 mulss xmm4, dword ptr [ebp - 0x8c]
006bb0b0 mulss xmm3, dword ptr [ebp - 0x94]
006bb0b8 mulss xmm0, dword ptr [ebp - 0x8c]
006bb0c0 subss xmm4, xmm1
006bb0c4 lahf 
006bb0c5 addss xmm3, xmm0
006bb0c9 xorps xmm4, xmmword ptr [0xb6c9b0]
006bb0d0 xorps xmm3, xmmword ptr [0xb6c9b0]
006bb0d7 test ah, 0x44
006bb0da jnp 0x6bb117
006bb0dc movss xmm1, dword ptr [edi + 0x2f4]
006bb0e4 movaps xmm0, xmm1
006bb0e7 mulss xmm1, xmm3
006bb0eb mulss xmm0, xmm4
006bb0ef divss xmm1, xmm2
006bb0f3 divss xmm0, xmm2
006bb0f7 addss xmm1, dword ptr [edi + 0x2bc]
006bb0ff addss xmm0, dword ptr [edi + 0x2b8]
006bb107 movss dword ptr [edi + 0x2bc], xmm1
006bb10f movss dword ptr [edi + 0x2b8], xmm0
006bb117 cmp dword ptr [edi + 0x180], 0
006bb11e je 0x6bb16e
006bb120 push 0
006bb122 push 0xb49738
006bb127 jmp 0x6bb166
006bb129 movss xmm0, dword ptr [edi + 0x2bc]
006bb131 movss xmm1, dword ptr [edi + 0x2b8]
006bb139 mulss xmm0, xmm0
006bb13d mulss xmm1, xmm1
006bb141 addss xmm1, xmm0
006bb145 movss xmm0, dword ptr [0xb6a8cc]
006bb14d comiss xmm0, xmm1
006bb150 jb 0x6bb16e
006bb152 mov eax, dword ptr [edi + 0x70]
006bb155 test eax, eax
006bb157 je 0x6bb16e
006bb159 cmp byte ptr [eax + 0x34], 0
006bb15d je 0x6bb16e
006bb15f push 0
006bb161 push 0xb3fd8c
006bb166 lea ecx, [edi + 0x3c]
006bb169 call 0x4054f0
006bb16e mov dword ptr [ebp - 4], 0xffffffff
006bb175 cmp byte ptr [ebp - 0x40], 0
006bb179 jne 0x6bb186
006bb17b push dword ptr [ebp - 0x3c]
006bb17e call 0x9eace5
006bb183 add esp, 4
