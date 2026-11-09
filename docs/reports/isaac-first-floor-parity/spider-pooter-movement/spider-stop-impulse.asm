0051845f movss xmm1, dword ptr [edi + 0x28c]
00518467 subss xmm1, dword ptr [edi + 0x294]
0051846f movss xmm0, dword ptr [edi + 0x290]
00518477 subss xmm0, dword ptr [edi + 0x298]
0051847f movss dword ptr [ebp - 0x58], xmm1
00518484 mulss xmm1, xmm1
00518488 movss dword ptr [ebp - 0x54], xmm0
0051848d mulss xmm0, xmm0
00518491 addss xmm0, xmm1
00518495 call 0x4228c0
0051849a movss xmm1, dword ptr [0xb6a9a0]
005184a2 comiss xmm1, xmm0
005184a5 ja 0x5184de
005184a7 movss xmm1, dword ptr [edi + 0x2bc]
005184af movss xmm0, dword ptr [edi + 0x2b8]
005184b7 mulss xmm0, xmm0
005184bb mulss xmm1, xmm1
005184bf addss xmm0, xmm1
005184c3 call 0x4228c0
005184c8 movss xmm1, dword ptr [0xb6a864]
005184d0 comiss xmm1, xmm0
005184d3 jbe 0x518508
005184d5 cmp dword ptr [edi + 0x360], 0
005184dc jge 0x518508
005184de movss xmm0, dword ptr [0xc02fec]
005184e6 movss dword ptr [edi + 0x28c], xmm0
005184ee movss xmm0, dword ptr [0xc02ff0]
005184f6 movss dword ptr [edi + 0x290], xmm0
005184fe mov dword ptr [edi + 0x360], 0
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
