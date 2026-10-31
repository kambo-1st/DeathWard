00509479 call 0x6c3d90
0050947e xor edx, edx
00509480 mov ecx, 0x3c
00509485 div ecx
00509487 neg edx
00509489 sbb edx, edx
0050948b inc edx
0050948c test edx, edx
0050948e je 0x509998
00509494 cmp dword ptr [edi + 0x34], 0x38a
0050949b je 0x509998
005094a1 mov eax, dword ptr [edi + 0x160]
005094a7 and eax, 0x1000a00
005094ac or eax, 0
005094af jne 0x509998
005094b5 push 1
005094b7 mov ecx, edi
005094b9 call 0x6afe20
005094be mov ecx, edi
005094c0 call 0x695680
005094c5 cmp dword ptr [edi + 0xe6c], -1
005094cc movss xmm2, dword ptr [edi + 0x294]
005094d4 movss xmm0, dword ptr [edi + 0x298]
005094dc subss xmm2, dword ptr [eax + 0x294]
005094e4 subss xmm0, dword ptr [eax + 0x298]
005094ec movss dword ptr [ebp - 0x124], xmm2
005094f4 je 0x50950e
005094f6 movss xmm2, dword ptr [edi + 0xe70]
005094fe movss xmm0, dword ptr [edi + 0xe74]
00509506 movss dword ptr [ebp - 0x124], xmm2
0050950e movaps xmm1, xmm2
00509511 mulss xmm0, xmm0
00509515 mulss xmm1, xmm2
00509519 addss xmm1, xmm0
0050951d movss xmm0, dword ptr [0xb6ad48]
00509525 comiss xmm0, xmm1
00509528 jbe 0x509998
0050952e push 1
00509530 push 0xb40510
00509535 lea ecx, [edi + 0x3c]
00509538 mov dword ptr [edi + 0x360], 0
00509542 mov dword ptr [edi + 0xab4], 8
0050954c call 0x405740
00509551 test al, al
00509553 je 0x509564
00509555 lea ecx, [edi + 0x6c]
00509558 call 0x405330
0050955d mov byte ptr [edi + 0x80], 1
00509564 movss xmm0, dword ptr [ebp - 0x124]
0050956c comiss xmm0, dword ptr [0xb6a18c]
00509573 seta al
00509576 mov byte ptr [edi + 0x13c], al
0050957c jmp 0x509998
