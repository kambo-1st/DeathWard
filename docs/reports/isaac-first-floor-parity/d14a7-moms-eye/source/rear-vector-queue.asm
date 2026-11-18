0095a6f7 cmp byte ptr [ebp - 0x17], 0
0095a6fb mov eax, dword ptr [0xc07194]
0095a700 mov dword ptr [0xc07198], eax
0095a705 je 0x95a85a
0095a70b movss xmm1, dword ptr [ebp - 0xb4]
0095a713 movss xmm0, dword ptr [ebp - 0x114]
0095a71b movss xmm2, dword ptr [ebp - 0x110]
0095a723 xorps xmm0, xmmword ptr [0xb6c9b0]
0095a72a xorps xmm2, xmmword ptr [0xb6c9b0]
0095a731 ucomiss xmm1, xmm3
0095a734 movss dword ptr [ebp - 0xc0], xmm0
0095a73c movss dword ptr [ebp - 0xb8], xmm2
0095a744 lahf
0095a745 test ah, 0x44
0095a748 jnp 0x95a7f0
0095a74e call 0x6c3d90
0095a753 xorps xmm0, xmm0
0095a756 cvtsi2sd xmm0, eax
0095a75a shr eax, 0x1f
0095a75d addsd xmm0, qword ptr [eax*8 + 0xb6c940]
0095a766 cvtpd2ps xmm0, xmm0
0095a76a mulss xmm0, dword ptr [0xb6a19c]
0095a772 subss xmm0, dword ptr [0xb6a480]
0095a77a mulss xmm0, xmm1
0095a77e mulss xmm0, dword ptr [0xb6a230]
0095a786 movss dword ptr [ebp - 0xac], xmm0
0095a78e call 0x411fe0
0095a793 movss dword ptr [ebp - 0xbc], xmm0
0095a79b movss xmm0, dword ptr [ebp - 0xac]
0095a7a3 call 0x412010
0095a7a8 movss xmm3, dword ptr [ebp - 0xbc]
0095a7b0 movaps xmm1, xmm0
0095a7b3 mulss xmm1, dword ptr [ebp - 0xb8]
0095a7bb movaps xmm2, xmm3
0095a7be mulss xmm2, dword ptr [ebp - 0xc0]
0095a7c6 mulss xmm3, dword ptr [ebp - 0xb8]
0095a7ce mulss xmm0, dword ptr [ebp - 0xc0]
0095a7d6 subss xmm2, xmm1
0095a7da addss xmm3, xmm0
0095a7de movss dword ptr [ebp - 0x184], xmm2
0095a7e6 movss dword ptr [ebp - 0x180], xmm3
0095a7ee jmp 0x95a800
0095a7f0 movss dword ptr [ebp - 0x184], xmm0
0095a7f8 movss dword ptr [ebp - 0x180], xmm2
0095a800 movss xmm0, dword ptr [ebp - 0xb0]
0095a808 lea eax, [ebp - 0x184]
0095a80e push ecx
0095a80f movss dword ptr [esp], xmm0
0095a814 mov ecx, esi
0095a816 push 1
0095a818 push 0
0095a81a push eax
0095a81b push 1
0095a81d lea eax, [ebp - 0xec]
0095a823 push eax
0095a824 call 0x945e40
0095a829 mov ecx, dword ptr [0xc07198]
0095a82f mov dword ptr [ebp - 0xac], eax
0095a835 cmp ecx, dword ptr [0xc0719c]
0095a83b je 0x95a848
0095a83d mov dword ptr [ecx], eax
0095a83f add dword ptr [0xc07198], 4
0095a846 jmp 0x95a85a
0095a848 lea eax, [ebp - 0xac]
0095a84e push eax
0095a84f push ecx
0095a850 mov ecx, 0xc07194
0095a855 call 0x426fb0
