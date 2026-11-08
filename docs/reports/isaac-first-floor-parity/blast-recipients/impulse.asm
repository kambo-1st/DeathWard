006d19af movss xmm0, dword ptr [ebp - 0x1c]
006d19b4 xorps xmm1, xmm1
006d19b7 comiss xmm0, xmm1
006d19ba jbe 0x6d1b50
006d19c0 cmp dword ptr [edi + 0x28], 0x3e8
006d19c7 je 0x6d1b50
006d19cd push 0
006d19cf push 0xbeab9c
006d19d4 push 0xbeab18
006d19d9 push 0
006d19db push edi
006d19dc call 0x9ec34c
006d19e1 mov ecx, dword ptr [edi + 0x160]
006d19e7 add esp, 0x14
006d19ea and ecx, 0x4000000
006d19f0 or ecx, 0
006d19f3 jne 0x6d1b4d
006d19f9 cmp dword ptr [edi + 0x28], 1
006d19fd jne 0x6d1a3e
006d19ff test eax, eax
006d1a01 je 0x6d1a1c
006d1a03 movss xmm0, dword ptr [eax + 0x2d4]
006d1a0b ucomiss xmm0, dword ptr [0xb6accc]
006d1a12 lahf 
006d1a13 test ah, 0x44
006d1a16 jnp 0x6d1b4d
006d1a1c test esi, esi
006d1a1e je 0x6d1a34
006d1a20 mov eax, dword ptr [esi + 0x160]
006d1a26 and eax, 0x20000000
006d1a2b or eax, 0
006d1a2e jne 0x6d1b4d
006d1a34 cmp byte ptr [ebp - 0x11], 0
006d1a38 jne 0x6d1b4d
006d1a3e movss xmm0, dword ptr [ebp - 0x2c]
006d1a43 lea eax, [ebp - 0x24]
006d1a46 movss xmm2, dword ptr [ebp - 0x1c]
006d1a4b lea ecx, [ebp - 0x2c]
006d1a4e movss xmm1, dword ptr [edi + 0x2d4]
006d1a56 subss xmm0, xmm2
006d1a5a mov dword ptr [ebp - 0x24], 0x41700000
006d1a61 comiss xmm0, dword ptr [0xb6a9ac]
006d1a68 movss dword ptr [ebp - 0x2c], xmm0
006d1a6d cmovbe eax, ecx
006d1a70 comiss xmm1, dword ptr [0xb6a9c8]
006d1a77 movss xmm0, dword ptr [eax]
006d1a7b jbe 0x6d1a8b
006d1a7d movss xmm5, dword ptr [0xb6a480]
006d1a85 mulss xmm0, xmm5
006d1a89 jmp 0x6d1aca
006d1a8b comiss xmm1, dword ptr [0xb6aa0c]
006d1a92 jbe 0x6d1a9e
006d1a94 mulss xmm0, dword ptr [0xb6a350]
006d1a9c jmp 0x6d1ac2
006d1a9e comiss xmm1, dword ptr [0xb6aa60]
006d1aa5 jbe 0x6d1ab1
006d1aa7 mulss xmm0, dword ptr [0xb6a220]
006d1aaf jmp 0x6d1ac2
006d1ab1 comiss xmm1, dword ptr [0xb6ab58]
006d1ab8 jbe 0x6d1ac2
006d1aba mulss xmm0, dword ptr [0xb6a1fc]
006d1ac2 movss xmm5, dword ptr [0xb6a480]
006d1aca push 0xbc4ae0
006d1acf lea edx, [ebx + 0x1c]
006d1ad2 lea ecx, [ebp - 0xa8]
006d1ad8 call 0x412050
006d1add add esp, 4
006d1ae0 mov ecx, dword ptr [eax]
006d1ae2 or ecx, dword ptr [eax + 4]
006d1ae5 jne 0x6d1af3
006d1ae7 mov ecx, dword ptr [eax + 8]
006d1aea or ecx, dword ptr [eax + 0xc]
006d1aed je 0x6d1c7f
006d1af3 mov eax, dword ptr [edi + 0x28]
006d1af6 cmp eax, 1
006d1af9 je 0x6d1c82
006d1aff movss xmm3, dword ptr [ebp - 0x20]
006d1b04 addss xmm0, xmm0
006d1b08 movss xmm4, dword ptr [ebp - 0x18]
006d1b0d divss xmm3, xmm2
006d1b11 divss xmm4, xmm2
006d1b15 movss xmm1, dword ptr [edi + 0x2b8]
006d1b1d movss xmm2, dword ptr [edi + 0x2bc]
006d1b25 mulss xmm3, xmm0
006d1b29 mulss xmm4, xmm0
006d1b2d mulss xmm2, xmm5
006d1b31 mulss xmm1, xmm5
006d1b35 addss xmm2, xmm4
006d1b39 addss xmm1, xmm3
006d1b3d movss dword ptr [edi + 0x2bc], xmm2
006d1b45 movss dword ptr [edi + 0x2b8], xmm1
006d1b4d xorps xmm1, xmm1
