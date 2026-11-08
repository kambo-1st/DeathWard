00518508 lea eax, [ebp - 0x48]
0051850b push eax
0051850c lea ecx, [ebp - 0x58]
0051850f call 0x962560
00518514 movss xmm3, dword ptr [edi + 0x2c4]
0051851c xorps xmm5, xmm5
0051851f movss xmm2, dword ptr [ebp - 0x3c]
00518524 ucomiss xmm3, xmm5
00518527 movaps xmm4, xmm2
0051852a mulss xmm2, dword ptr [eax + 4]
0051852f mulss xmm4, dword ptr [eax]
00518533 lahf 
00518534 test ah, 0x44
00518537 jnp 0x5183a5
0051853d movss xmm1, dword ptr [edi + 0x2f4]
00518545 movaps xmm0, xmm1
00518548 mulss xmm1, xmm2
0051854c mulss xmm0, xmm4
00518550 divss xmm1, xmm3
00518554 divss xmm0, xmm3
00518558 addss xmm1, dword ptr [edi + 0x2bc]
00518560 addss xmm0, dword ptr [edi + 0x2b8]
00518568 movss dword ptr [edi + 0x2bc], xmm1
00518570 movss dword ptr [edi + 0x2b8], xmm0
