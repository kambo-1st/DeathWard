00742369 movss xmm7, dword ptr [edi + 0x14ac]
00742371 xorps xmm0, xmm0
00742374 mulss xmm7, dword ptr [0xb6a38c]
0074237c mov dword ptr [edi + 0x1558], 0xffffffff
00742386 addss xmm7, dword ptr [0xb6a53c]
0074238e mulss xmm5, xmm7
00742392 mulss xmm7, xmm6
00742396 movaps xmm2, xmm5
00742399 movss dword ptr [ebp - 0x60], xmm5
0074239e andps xmm2, xmmword ptr [0xb6c980]
007423a5 movaps xmm1, xmm7
007423a8 movss dword ptr [ebp - 0x58], xmm7
007423ad andps xmm1, xmmword ptr [0xb6c980]
007423b4 comiss xmm2, xmm1
007423b7 jbe 0x7423ce
007423b9 xor eax, eax
007423bb mov ecx, 2
007423c0 comiss xmm0, xmm5
007423c3 cmovbe eax, ecx
007423c6 mov dword ptr [edi + 0x1558], eax
007423cc jmp 0x7423fb
007423ce comiss xmm0, xmm7
007423d1 jbe 0x7423e4
007423d3 mov dword ptr [edi + 0x1558], 1
007423dd mov eax, 1
007423e2 jmp 0x7423fb
007423e4 or eax, 0xffffffff
007423e7 comiss xmm7, xmm0
007423ea jbe 0x7423fb
007423ec mov dword ptr [edi + 0x1558], 3
007423f6 mov eax, 3
