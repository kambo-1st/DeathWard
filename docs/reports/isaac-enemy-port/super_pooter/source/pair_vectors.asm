006a1afb call 0x6c3d90
006a1b00 mov edi, dword ptr [ebx + 0xc]
006a1b03 mov ecx, dword ptr [ebx + 0x14]
006a1b06 mov esi, dword ptr [ebx + 8]
006a1b09 push 0
006a1b0b movss xmm3, dword ptr [edi + 4]
006a1b10 movss xmm4, dword ptr [edi]
006a1b14 movaps xmm0, xmm3
006a1b17 mulss xmm0, dword ptr [0xb6a39c]
006a1b1f movaps xmm1, xmm4
006a1b22 push 0xbeabf4
006a1b27 mulss xmm1, dword ptr [0xb6a5ec]
006a1b2f push 0xbeab18
006a1b34 mulss xmm0, dword ptr [ecx + 0x28]
006a1b39 push 0
006a1b3b mulss xmm4, dword ptr [0xb6a39c]
006a1b43 push eax
006a1b44 mulss xmm3, dword ptr [0xb6a5ec]
006a1b4c subss xmm1, xmm0
006a1b50 lea eax, [ebp - 0x38]
006a1b53 movss xmm0, dword ptr [esi]
006a1b57 addss xmm0, dword ptr [ecx + 0x60]
006a1b5c mulss xmm4, dword ptr [ecx + 0x28]
006a1b61 push 0
006a1b63 push dword ptr [ebp - 0x14]
006a1b66 movss dword ptr [ebp - 0x38], xmm1
006a1b6b push eax
006a1b6c movss dword ptr [ebp - 0x30], xmm0
006a1b71 lea eax, [ebp - 0x30]
006a1b74 movss xmm0, dword ptr [ecx + 0x64]
006a1b79 addss xmm4, xmm3
006a1b7d addss xmm0, dword ptr [esi + 4]
006a1b82 push eax
006a1b83 push dword ptr [ecx + 0x94]
006a1b89 mov ecx, dword ptr [0xbfd65c]
006a1b8f push 9
006a1b91 movss dword ptr [ebp - 0x34], xmm4
006a1b96 movss dword ptr [ebp - 0x2c], xmm0
006a1b9b call 0x422e20
006a1ba0 push eax
006a1ba1 call 0x9ec34c
006a1ba6 add esp, 0x14
006a1ba9 mov dword ptr [ebp - 0x24], eax
006a1bac lea eax, [ebp - 0x24]
006a1baf lea ecx, [ebp - 0x4c]
006a1bb2 push eax
006a1bb3 push 0
006a1bb5 call 0x426fb0
006a1bba call 0x6c3d90
006a1bbf movss xmm4, dword ptr [edi + 4]
006a1bc4 mov ecx, dword ptr [ebx + 0x14]
006a1bc7 movaps xmm1, xmm4
006a1bca movss xmm2, dword ptr [edi]
006a1bce mov edi, ecx
006a1bd0 mulss xmm1, dword ptr [0xb6a39c]
006a1bd8 movaps xmm0, xmm2
006a1bdb push 0
006a1bdd mulss xmm0, dword ptr [0xb6a5ec]
006a1be5 push 0xbeabf4
006a1bea mulss xmm1, dword ptr [ecx + 0x28]
006a1bef push 0xbeab18
006a1bf4 mulss xmm2, dword ptr [0xb6a39c]
006a1bfc push 0
006a1bfe mulss xmm4, dword ptr [0xb6a5ec]
006a1c06 addss xmm1, xmm0
006a1c0a push eax
006a1c0b movss xmm0, dword ptr [esi]
006a1c0f lea eax, [ebp - 0x38]
006a1c12 addss xmm0, dword ptr [edi + 0x60]
006a1c17 mulss xmm2, dword ptr [ecx + 0x28]
006a1c1c push 0
006a1c1e push dword ptr [ebp - 0x14]
006a1c21 movss dword ptr [ebp - 0x38], xmm1
006a1c26 movss dword ptr [ebp - 0x30], xmm0
006a1c2b subss xmm4, xmm2
006a1c2f movss xmm0, dword ptr [edi + 0x64]
006a1c34 addss xmm0, dword ptr [esi + 4]
006a1c39 push eax
006a1c3a lea eax, [ebp - 0x30]
006a1c3d movss dword ptr [ebp - 0x34], xmm4
006a1c42 movss dword ptr [ebp - 0x2c], xmm0
006a1c47 mov ecx, dword ptr [0xbfd65c]
006a1c4d push eax
006a1c4e push dword ptr [edi + 0x94]
006a1c54 push 9
006a1c56 call 0x422e20
006a1c5b push eax
006a1c5c call 0x9ec34c
006a1c61 mov esi, dword ptr [ebp - 0x48]
006a1c64 add esp, 0x14
006a1c67 mov dword ptr [ebp - 0x24], eax
006a1c6a cmp esi, dword ptr [ebp - 0x44]
006a1c6d je 0x6a1c7c
006a1c6f mov dword ptr [esi], eax
006a1c71 add esi, 4
006a1c74 mov dword ptr [ebp - 0x48], esi
006a1c77 jmp 0x6a301f
006a1c7c lea eax, [ebp - 0x24]
006a1c7f push eax
006a1c80 push esi
006a1c81 lea ecx, [ebp - 0x4c]
006a1c84 call 0x426fb0
006a1c89 mov esi, dword ptr [ebp - 0x48]
006a1c8c jmp 0x6a301f
