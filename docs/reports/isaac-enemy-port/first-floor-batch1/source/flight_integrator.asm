00636567 movss xmm1, dword ptr [edi + 0x2f4]
0063656f lea esi, [edi + 0x2f4]
00636575 movss xmm0, dword ptr [0xb6a5a4]
0063657d call 0x65c960
00636582 cmp dword ptr [edi + 0x2c], 0xf
00636586 lea eax, [edi + 0x2b8]
0063658c movss xmm2, dword ptr [esi]
00636590 mulss xmm0, dword ptr [edi + 0x364]
00636598 movaps xmm1, xmm2
0063659b mulss xmm1, dword ptr [0xb6a2cc]
006365a3 addss xmm1, xmm0
006365a7 movaps xmm0, xmm2
006365aa mulss xmm0, dword ptr [edi + 0x368]
006365b2 addss xmm0, xmm1
006365b6 movaps xmm1, xmm0
006365b9 movss dword ptr [edi + 0x364], xmm0
006365c1 mulss xmm1, xmm2
006365c5 addss xmm1, dword ptr [edi + 0x360]
006365cd movss dword ptr [edi + 0x360], xmm1
