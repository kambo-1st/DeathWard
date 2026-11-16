00618860 push ebp
00618861 mov ebp, esp
00618863 and esp, 0xfffffff0
00618866 sub esp, 0x138
0061886c mov eax, dword ptr [0xbaa3b4]
00618871 xor eax, esp
00618873 mov dword ptr [esp + 0x134], eax
0061887a cmp byte ptr [ebp + 0xc], 0
0061887e xorps xmm0, xmm0
00618881 push esi
00618882 mov esi, dword ptr [ebp + 8]
00618885 push edi
00618886 mov edi, ecx
00618888 movss dword ptr [esp + 0x3c], xmm0
0061888e movss xmm3, dword ptr [esi]
00618892 movss xmm4, dword ptr [esi + 4]
00618897 mulss xmm3, dword ptr [0xb6a974]
0061889f mulss xmm4, dword ptr [0xb6a974]
006188a7 movss dword ptr [esp + 0x48], xmm3
006188ad movss dword ptr [esp + 0x50], xmm3
006188b3 movss dword ptr [esp + 0x44], xmm4
006188b9 movss dword ptr [esp + 0x54], xmm4
006188bf jne 0x618b44
006188c5 mov ecx, dword ptr [edi + 0x2c]
006188c8 cmp ecx, 0xc8
006188ce jne 0x618a4e
006188d4 mov eax, dword ptr [edi + 0x360]
006188da movss xmm1, dword ptr [eax + 0x2bc]
006188e2 mulss xmm1, dword ptr [0xb6a4c4]
006188ea movss xmm2, dword ptr [eax + 0x2b8]
006188f2 mulss xmm2, dword ptr [0xb6a4c4]
006188fa addss xmm1, xmm1
006188fe addss xmm2, xmm2
00618902 movss dword ptr [esp + 0x4c], xmm1
00618908 movss xmm1, dword ptr [esi]
0061890c movaps xmm0, xmm1
0061890f movss dword ptr [esp + 0x30], xmm2
00618915 movss xmm2, dword ptr [esi + 4]
0061891a mulss xmm0, xmm1
0061891e movss dword ptr [esp + 0x38], xmm1
00618924 movaps xmm1, xmm2
00618927 mulss xmm1, xmm2
0061892b movss dword ptr [esp + 0x34], xmm2
00618931 addss xmm0, xmm1
00618935 call 0x4228c0
0061893a comiss xmm0, dword ptr [0xb6a18c]
00618941 jbe 0x618965
00618943 movss xmm1, dword ptr [0xb6a614]
0061894b divss xmm1, xmm0
0061894f movss xmm2, dword ptr [esi]
00618953 movaps xmm0, xmm1
00618956 mulss xmm2, xmm0
0061895a movss xmm0, dword ptr [esi + 4]
0061895f mulss xmm0, xmm1
00618963 jmp 0x618971
00618965 movss xmm2, dword ptr [esp + 0x38]
0061896b movss xmm0, dword ptr [esp + 0x34]
00618971 movss xmm1, dword ptr [esp + 0x4c]
00618977 mulss xmm1, xmm0
0061897b movss xmm0, dword ptr [esp + 0x30]
00618981 mulss xmm0, xmm2
00618985 movss xmm2, dword ptr [esi]
00618989 movss dword ptr [esp + 0x38], xmm2
0061898f addss xmm1, xmm0
00618993 movss dword ptr [esp + 0x2c], xmm1
00618999 movss xmm1, dword ptr [esi + 4]
0061899e movaps xmm0, xmm1
006189a1 movss dword ptr [esp + 0x34], xmm1
006189a7 mulss xmm0, xmm1
006189ab movaps xmm1, xmm2
006189ae mulss xmm1, xmm2
006189b2 addss xmm0, xmm1
006189b6 call 0x4228c0
006189bb xorps xmm2, xmm2
006189be comiss xmm0, xmm2
006189c1 jbe 0x6189e5
006189c3 movss xmm1, dword ptr [0xb6a614]
006189cb divss xmm1, xmm0
006189cf movss xmm3, dword ptr [esi]
006189d3 movss xmm4, dword ptr [esi + 4]
006189d8 movaps xmm0, xmm1
006189db mulss xmm3, xmm0
006189df mulss xmm4, xmm1
006189e3 jmp 0x6189f1
006189e5 movss xmm3, dword ptr [esp + 0x38]
006189eb movss xmm4, dword ptr [esp + 0x34]
006189f1 mulss xmm3, dword ptr [esp + 0x2c]
006189f7 mulss xmm4, dword ptr [esp + 0x2c]
006189fd movaps xmm0, xmm3
00618a00 mulss xmm0, dword ptr [esi]
00618a04 movaps xmm1, xmm4
00618a07 mulss xmm1, dword ptr [esi + 4]
00618a0c addss xmm1, xmm0
00618a10 movss xmm0, dword ptr [esp + 0x30]
00618a16 comiss xmm2, xmm1
00618a19 movss xmm1, dword ptr [esp + 0x4c]
00618a1f jbe 0x618a29
00618a21 subss xmm0, xmm3
00618a25 subss xmm1, xmm4
00618a29 movss xmm3, dword ptr [esp + 0x48]
00618a2f addss xmm3, xmm0
00618a33 movss xmm0, dword ptr [esp + 0x44]
00618a39 addss xmm0, xmm1
00618a3d movss dword ptr [esp + 0x48], xmm3
00618a43 movss dword ptr [esp + 0x50], xmm3
00618a49 jmp 0x618b38
00618a4e cmp ecx, 8
00618a51 je 0x618a93
00618a53 cmp ecx, 0xf4
00618a59 je 0x618a93
00618a5b mov eax, dword ptr [edi + 0x360]
00618a61 movss xmm1, dword ptr [eax + 0x2b8]
00618a69 movss xmm2, dword ptr [eax + 0x2bc]
00618a71 mulss xmm1, dword ptr [0xb6a4c4]
00618a79 mulss xmm2, dword ptr [0xb6a4c4]
00618a81 addss xmm1, xmm1
00618a85 addss xmm2, xmm2
00618a89 addss xmm3, xmm1
00618a8d addss xmm4, xmm2
00618a91 jmp 0x618ac9
00618a93 mov eax, dword ptr [edi + 0x360]
00618a99 movss xmm1, dword ptr [eax + 0x2b8]
00618aa1 movss xmm2, dword ptr [eax + 0x2bc]
00618aa9 mulss xmm1, dword ptr [0xb6a4c4]
00618ab1 mulss xmm2, dword ptr [0xb6a4c4]
00618ab9 addss xmm1, xmm1
00618abd addss xmm2, xmm2
00618ac1 subss xmm3, xmm1
00618ac5 subss xmm4, xmm2
00618ac9 movaps xmm0, xmm3
00618acc movss dword ptr [esp + 0x54], xmm4
00618ad2 movaps xmm1, xmm4
00618ad5 mulss xmm0, xmm3
00618ad9 mulss xmm1, xmm4
00618add movss dword ptr [esp + 0x44], xmm4
00618ae3 movss dword ptr [esp + 0x50], xmm3
00618ae9 addss xmm1, xmm0
00618aed movss dword ptr [esp + 0x48], xmm3
00618af3 movss xmm0, dword ptr [0xb6aafc]
00618afb comiss xmm0, xmm1
00618afe jbe 0x618b44
00618b00 cmp ecx, 0x6c
00618b03 je 0x618b44
00618b05 lea eax, [esp + 0x58]
00618b09 push eax
00618b0a lea ecx, [esp + 0x54]
00618b0e call 0x962560
00618b13 movss xmm0, dword ptr [eax]
00618b17 mulss xmm0, dword ptr [0xb6a974]
00618b1f movss dword ptr [esp + 0x48], xmm0
00618b25 movss dword ptr [esp + 0x50], xmm0
00618b2b movss xmm0, dword ptr [eax + 4]
00618b30 mulss xmm0, dword ptr [0xb6a974]
00618b38 movss dword ptr [esp + 0x54], xmm0
00618b3e movss dword ptr [esp + 0x44], xmm0
