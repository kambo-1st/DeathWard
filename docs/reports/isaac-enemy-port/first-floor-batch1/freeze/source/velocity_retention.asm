00686406 movss xmm2, dword ptr [edi + 0x2f4]
0068640e movss xmm4, dword ptr [0xb6a614]
00686416 movss xmm3, dword ptr [edi + 0x2c4]
0068641e ucomiss xmm2, xmm4
00686421 lahf 
00686422 test ah, 0x44
00686425 jnp 0x68643d
00686427 movaps xmm1, xmm3
0068642a movaps xmm0, xmm3
0068642d addss xmm1, xmm2
00686431 mulss xmm0, xmm2
00686435 subss xmm1, xmm0
00686439 divss xmm3, xmm1
0068643d mov eax, dword ptr [edi + 0x2c0]
00686443 lea edx, [edi + 0x294]
00686449 movaps xmm1, xmm3
0068644c mulss xmm3, dword ptr [edi + 0x2bc]
00686454 mulss xmm1, dword ptr [edi + 0x2b8]
0068645c movss dword ptr [edi + 0x2bc], xmm3
00686464 movss dword ptr [edi + 0x2b8], xmm1
0068646c movss xmm2, dword ptr [edi + 0x2f4]
00686474 movaps xmm0, xmm2
00686477 mov dword ptr [edi + 0x2c4], eax
0068647d mulss xmm0, xmm1
00686481 mulss xmm2, xmm3
00686485 addss xmm0, dword ptr [edx]
00686489 addss xmm2, dword ptr [edx + 4]
0068648e movss dword ptr [edx], xmm0
