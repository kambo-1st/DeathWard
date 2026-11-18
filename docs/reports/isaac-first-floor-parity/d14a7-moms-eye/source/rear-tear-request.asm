0095af34 movss xmm2, dword ptr [ebp - 0xb4]
0095af3c cmp byte ptr [ebp - 0x17], 0
0095af40 je 0x95b085
0095af46 ucomiss xmm2, dword ptr [0xb6a18c]
0095af4d movss xmm0, dword ptr [ebp - 0xc8]
0095af55 xorps xmm0, xmmword ptr [0xb6c9b0]
0095af5c movss xmm3, dword ptr [ebp - 0x104]
0095af64 movss xmm1, dword ptr [ebp - 0xb8]
0095af6c xorps xmm1, xmmword ptr [0xb6c9b0]
0095af73 mulss xmm3, xmm0
0095af77 movss xmm0, dword ptr [ebp - 0x104]
0095af7f mulss xmm0, xmm1
0095af83 lahf
0095af84 movss dword ptr [ebp - 0xbc], xmm3
0095af8c movss dword ptr [ebp - 0xfc], xmm0
0095af94 test ah, 0x44
0095af97 jnp 0x95b03f
0095af9d call 0x6c3d90
0095afa2 xorps xmm0, xmm0
0095afa5 cvtsi2sd xmm0, eax
0095afa9 shr eax, 0x1f
0095afac addsd xmm0, qword ptr [eax*8 + 0xb6c940]
0095afb5 cvtpd2ps xmm0, xmm0
0095afb9 mulss xmm0, dword ptr [0xb6a19c]
0095afc1 subss xmm0, dword ptr [0xb6a480]
0095afc9 mulss xmm0, xmm2
0095afcd mulss xmm0, dword ptr [0xb6a230]
0095afd5 movss dword ptr [ebp - 0xac], xmm0
0095afdd call 0x411fe0
0095afe2 movss dword ptr [ebp - 0xdc], xmm0
0095afea movss xmm0, dword ptr [ebp - 0xac]
0095aff2 call 0x412010
0095aff7 movss xmm4, dword ptr [ebp - 0xbc]
0095afff movaps xmm1, xmm0
0095b002 movss xmm3, dword ptr [ebp - 0xdc]
0095b00a movaps xmm2, xmm4
0095b00d mulss xmm1, dword ptr [ebp - 0xfc]
0095b015 mulss xmm2, xmm3
0095b019 mulss xmm3, dword ptr [ebp - 0xfc]
0095b021 mulss xmm4, xmm0
0095b025 subss xmm2, xmm1
0095b029 addss xmm4, xmm3
0095b02d movss dword ptr [ebp - 0x174], xmm2
0095b035 movss dword ptr [ebp - 0x170], xmm4
0095b03d jmp 0x95b04f
0095b03f movss dword ptr [ebp - 0x174], xmm3
0095b047 movss dword ptr [ebp - 0x170], xmm0
0095b04f movss xmm0, dword ptr [ebp - 0xd8]
0095b057 lea eax, [ebp - 0x174]
0095b05d sub esp, 0xc
0095b060 mov ecx, esi
0095b062 movss dword ptr [esp + 8], xmm0
0095b068 movss xmm0, dword ptr [ebp - 0xb0]
0095b070 movss dword ptr [esp + 4], xmm0
0095b076 push 6
0095b078 push eax
0095b079 lea eax, [ebp - 0xec]
0095b07f push eax
0095b080 call 0x9453d0
