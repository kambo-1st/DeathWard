006a1a20 push ebx
006a1a21 mov ebx, esp
006a1a23 sub esp, 8
006a1a26 and esp, 0xfffffff8
006a1a29 add esp, 4
006a1a2c push ebp
006a1a2d mov ebp, dword ptr [ebx + 4]
006a1a30 mov dword ptr [esp + 4], ebp
006a1a34 mov ebp, esp
006a1a36 push -1
006a1a38 push 0x9f48fd
006a1a3d mov eax, dword ptr fs:[0]
006a1a43 push eax
006a1a44 push ebx
006a1a45 sub esp, 0x40
006a1a48 push esi
006a1a49 push edi
006a1a4a mov eax, dword ptr [0xbaa3b4]
006a1a4f xor eax, ebp
006a1a51 push eax
006a1a52 lea eax, [ebp - 0xc]
006a1a55 mov dword ptr fs:[0], eax
006a1a5b mov dword ptr [ebp - 0x14], ecx
006a1a5e xor esi, esi
006a1a60 mov dword ptr [ebp - 0x4c], 0
006a1a67 mov dword ptr [ebp - 0x48], esi
006a1a6a mov dword ptr [ebp - 0x44], esi
006a1a6d mov eax, dword ptr [ebx + 0x10]
006a1a70 mov dword ptr [ebp - 4], esi
006a1a73 cmp eax, 9
006a1a76 ja 0x6a301c
006a1a7c jmp dword ptr [eax*4 + 0x6a33ec]
006a1a83 call 0x6c3d90
006a1a88 mov ecx, dword ptr [ebx + 8]
006a1a8b mov edi, dword ptr [ebx + 0x14]
006a1a8e push 0
006a1a90 push 0xbeabf4
006a1a95 movss xmm0, dword ptr [ecx]
006a1a99 addss xmm0, dword ptr [edi + 0x60]
006a1a9e push 0xbeab18
006a1aa3 push 0
006a1aa5 push eax
006a1aa6 push 0
006a1aa8 push dword ptr [ebp - 0x14]
006a1aab movss dword ptr [ebp - 0x38], xmm0
006a1ab0 lea eax, [ebp - 0x38]
006a1ab3 push dword ptr [ebx + 0xc]
006a1ab6 movss xmm0, dword ptr [edi + 0x64]
006a1abb addss xmm0, dword ptr [ecx + 4]
006a1ac0 mov ecx, dword ptr [0xbfd65c]
006a1ac6 push eax
006a1ac7 push dword ptr [edi + 0x94]
006a1acd push 9
006a1acf movss dword ptr [ebp - 0x34], xmm0
006a1ad4 call 0x422e20
006a1ad9 push eax
006a1ada call 0x9ec34c
006a1adf add esp, 0x14
006a1ae2 mov dword ptr [ebp - 0x24], eax
006a1ae5 lea eax, [ebp - 0x24]
006a1ae8 lea ecx, [ebp - 0x4c]
006a1aeb push eax
006a1aec push 0
006a1aee call 0x426fb0
006a1af3 mov esi, dword ptr [ebp - 0x48]
006a1af6 jmp 0x6a301f
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
006a1c91 call 0x6c3d90
006a1c96 mov ecx, dword ptr [ebx + 8]
006a1c99 mov edi, dword ptr [ebx + 0x14]
006a1c9c mov esi, dword ptr [ebp - 0x14]
006a1c9f push 0
006a1ca1 movss xmm0, dword ptr [ecx]
006a1ca5 addss xmm0, dword ptr [edi + 0x60]
006a1caa push 0xbeabf4
006a1caf push 0xbeab18
006a1cb4 push 0
006a1cb6 push eax
006a1cb7 push 0
006a1cb9 push esi
006a1cba push dword ptr [ebx + 0xc]
006a1cbd movss dword ptr [ebp - 0x38], xmm0
006a1cc2 lea eax, [ebp - 0x38]
006a1cc5 movss xmm0, dword ptr [edi + 0x64]
006a1cca addss xmm0, dword ptr [ecx + 4]
006a1ccf mov ecx, dword ptr [0xbfd65c]
006a1cd5 push eax
006a1cd6 push dword ptr [edi + 0x94]
006a1cdc push 9
006a1cde movss dword ptr [ebp - 0x34], xmm0
006a1ce3 call 0x422e20
006a1ce8 push eax
006a1ce9 call 0x9ec34c
006a1cee add esp, 0x14
006a1cf1 mov dword ptr [ebp - 0x24], eax
006a1cf4 lea eax, [ebp - 0x24]
006a1cf7 lea ecx, [ebp - 0x4c]
006a1cfa push eax
006a1cfb push 0
006a1cfd call 0x426fb0
006a1d02 call 0x6c3d90
006a1d07 mov ecx, dword ptr [ebx + 0xc]
006a1d0a movss xmm5, dword ptr [0xb6a5a4]
006a1d12 push 0
006a1d14 push 0xbeabf4
006a1d19 movss xmm3, dword ptr [ecx + 4]
006a1d1e movss xmm4, dword ptr [ecx]
006a1d22 movaps xmm0, xmm3
006a1d25 mulss xmm0, dword ptr [0xb6a39c]
006a1d2d movaps xmm1, xmm4
006a1d30 mov ecx, dword ptr [ebx + 8]
006a1d33 mulss xmm1, dword ptr [0xb6a5ec]
006a1d3b push 0xbeab18
006a1d40 mulss xmm4, dword ptr [0xb6a39c]
006a1d48 push 0
006a1d4a mulss xmm3, dword ptr [0xb6a5ec]
006a1d52 push eax
006a1d53 mulss xmm0, xmm5
006a1d57 lea eax, [ebp - 0x38]
006a1d5a push 0
006a1d5c mulss xmm1, xmm5
006a1d60 push esi
006a1d61 mulss xmm0, dword ptr [edi + 0x28]
006a1d66 push eax
006a1d67 mulss xmm4, xmm5
006a1d6b lea eax, [ebp - 0x30]
006a1d6e push eax
006a1d6f push dword ptr [edi + 0x94]
006a1d75 subss xmm1, xmm0
006a1d79 mulss xmm3, xmm5
006a1d7d push 9
006a1d7f movss xmm0, dword ptr [ecx]
006a1d83 addss xmm0, dword ptr [edi + 0x60]
006a1d88 mulss xmm4, dword ptr [edi + 0x28]
006a1d8d movss dword ptr [ebp - 0x38], xmm1
006a1d92 movss dword ptr [ebp - 0x30], xmm0
006a1d97 addss xmm4, xmm3
006a1d9b movss xmm0, dword ptr [edi + 0x64]
006a1da0 addss xmm0, dword ptr [ecx + 4]
006a1da5 mov ecx, dword ptr [0xbfd65c]
006a1dab movss dword ptr [ebp - 0x34], xmm4
006a1db0 movss dword ptr [ebp - 0x2c], xmm0
006a1db5 call 0x422e20
006a1dba push eax
006a1dbb call 0x9ec34c
006a1dc0 mov esi, dword ptr [ebp - 0x48]
006a1dc3 add esp, 0x14
006a1dc6 mov dword ptr [ebp - 0x24], eax
006a1dc9 cmp esi, dword ptr [ebp - 0x44]
006a1dcc je 0x6a1dd8
006a1dce mov dword ptr [esi], eax
006a1dd0 add esi, 4
006a1dd3 mov dword ptr [ebp - 0x48], esi
006a1dd6 jmp 0x6a1de8
006a1dd8 lea eax, [ebp - 0x24]
006a1ddb push eax
006a1ddc push esi
006a1ddd lea ecx, [ebp - 0x4c]
006a1de0 call 0x426fb0
006a1de5 mov esi, dword ptr [ebp - 0x48]
006a1de8 call 0x6c3d90
006a1ded mov ecx, dword ptr [ebx + 0xc]
006a1df0 movss xmm5, dword ptr [0xb6a5a4]
006a1df8 push 0
006a1dfa push 0xbeabf4
006a1dff movss xmm4, dword ptr [ecx + 4]
006a1e04 movss xmm2, dword ptr [ecx]
006a1e08 movaps xmm1, xmm4
006a1e0b mulss xmm1, dword ptr [0xb6a39c]
006a1e13 movaps xmm0, xmm2
006a1e16 mov ecx, dword ptr [ebx + 8]
006a1e19 mulss xmm0, dword ptr [0xb6a5ec]
006a1e21 push 0xbeab18
006a1e26 mulss xmm2, dword ptr [0xb6a39c]
006a1e2e push 0
006a1e30 mulss xmm4, dword ptr [0xb6a5ec]
006a1e38 push eax
006a1e39 mulss xmm1, xmm5
006a1e3d lea eax, [ebp - 0x38]
006a1e40 push 0
006a1e42 push dword ptr [ebp - 0x14]
006a1e45 mulss xmm0, xmm5
006a1e49 push eax
006a1e4a mulss xmm1, dword ptr [edi + 0x28]
006a1e4f lea eax, [ebp - 0x30]
006a1e52 push eax
006a1e53 push dword ptr [edi + 0x94]
006a1e59 mulss xmm2, xmm5
006a1e5d push 9
006a1e5f addss xmm1, xmm0
006a1e63 mulss xmm4, xmm5
006a1e67 movss xmm0, dword ptr [ecx]
006a1e6b addss xmm0, dword ptr [edi + 0x60]
006a1e70 mulss xmm2, dword ptr [edi + 0x28]
006a1e75 movss dword ptr [ebp - 0x38], xmm1
006a1e7a movss dword ptr [ebp - 0x30], xmm0
006a1e7f subss xmm4, xmm2
006a1e83 movss xmm0, dword ptr [edi + 0x64]
006a1e88 addss xmm0, dword ptr [ecx + 4]
006a1e8d mov ecx, dword ptr [0xbfd65c]
006a1e93 movss dword ptr [ebp - 0x34], xmm4
006a1e98 movss dword ptr [ebp - 0x2c], xmm0
006a1e9d call 0x422e20
006a1ea2 push eax
006a1ea3 call 0x9ec34c
006a1ea8 jmp 0x6a1c64
006a1ead call 0x6c3d90
006a1eb2 mov ecx, dword ptr [ebx + 8]
006a1eb5 mov edi, dword ptr [ebx + 0x14]
006a1eb8 mov esi, dword ptr [ebp - 0x14]
006a1ebb push 0
006a1ebd movss xmm0, dword ptr [ecx]
006a1ec1 addss xmm0, dword ptr [edi + 0x60]
006a1ec6 push 0xbeabf4
006a1ecb push 0xbeab18
006a1ed0 push 0
006a1ed2 push eax
006a1ed3 push 0
006a1ed5 push esi
006a1ed6 push dword ptr [ebx + 0xc]
006a1ed9 movss dword ptr [ebp - 0x38], xmm0
006a1ede lea eax, [ebp - 0x38]
006a1ee1 movss xmm0, dword ptr [edi + 0x64]
006a1ee6 addss xmm0, dword ptr [ecx + 4]
006a1eeb mov ecx, dword ptr [0xbfd65c]
006a1ef1 push eax
006a1ef2 push dword ptr [edi + 0x94]
006a1ef8 push 9
006a1efa movss dword ptr [ebp - 0x34], xmm0
006a1eff call 0x422e20
006a1f04 push eax
006a1f05 call 0x9ec34c
006a1f0a add esp, 0x14
006a1f0d mov dword ptr [ebp - 0x24], eax
006a1f10 lea eax, [ebp - 0x24]
006a1f13 lea ecx, [ebp - 0x4c]
006a1f16 push eax
006a1f17 push 0
006a1f19 call 0x426fb0
006a1f1e call 0x6c3d90
006a1f23 mov ecx, dword ptr [ebx + 0xc]
006a1f26 push 0
006a1f28 push 0xbeabf4
006a1f2d push 0xbeab18
006a1f32 movss xmm3, dword ptr [ecx + 4]
006a1f37 movss xmm4, dword ptr [ecx]
006a1f3b movaps xmm0, xmm3
006a1f3e mulss xmm0, dword ptr [0xb6a43c]
006a1f46 movaps xmm1, xmm4
006a1f49 mov ecx, dword ptr [ebx + 8]
006a1f4c mulss xmm1, dword ptr [0xb6a5b0]
006a1f54 push 0
006a1f56 mulss xmm0, dword ptr [edi + 0x28]
006a1f5b push eax
006a1f5c mulss xmm4, dword ptr [0xb6a43c]
006a1f64 lea eax, [ebp - 0x38]
006a1f67 push 0
006a1f69 mulss xmm3, dword ptr [0xb6a5b0]
006a1f71 subss xmm1, xmm0
006a1f75 push esi
006a1f76 movss xmm0, dword ptr [edi + 0x60]
006a1f7b addss xmm0, dword ptr [ecx]
006a1f7f mulss xmm4, dword ptr [edi + 0x28]
006a1f84 push eax
006a1f85 lea eax, [ebp - 0x30]
006a1f88 movss dword ptr [ebp - 0x38], xmm1
006a1f8d push eax
006a1f8e push dword ptr [edi + 0x94]
006a1f94 movss dword ptr [ebp - 0x30], xmm0
006a1f99 addss xmm4, xmm3
006a1f9d movss xmm0, dword ptr [edi + 0x64]
006a1fa2 addss xmm0, dword ptr [ecx + 4]
006a1fa7 mov ecx, dword ptr [0xbfd65c]
006a1fad push 9
006a1faf movss dword ptr [ebp - 0x34], xmm4
006a1fb4 movss dword ptr [ebp - 0x2c], xmm0
006a1fb9 call 0x422e20
006a1fbe push eax
006a1fbf call 0x9ec34c
006a1fc4 mov esi, dword ptr [ebp - 0x48]
006a1fc7 add esp, 0x14
006a1fca mov dword ptr [ebp - 0x24], eax
006a1fcd cmp esi, dword ptr [ebp - 0x44]
006a1fd0 je 0x6a1fdc
006a1fd2 mov dword ptr [esi], eax
006a1fd4 add esi, 4
006a1fd7 mov dword ptr [ebp - 0x48], esi
006a1fda jmp 0x6a1fec
006a1fdc lea eax, [ebp - 0x24]
006a1fdf push eax
006a1fe0 push esi
006a1fe1 lea ecx, [ebp - 0x4c]
006a1fe4 call 0x426fb0
006a1fe9 mov esi, dword ptr [ebp - 0x48]
006a1fec call 0x6c3d90
006a1ff1 mov ecx, dword ptr [ebx + 0xc]
006a1ff4 movss xmm4, dword ptr [ecx + 4]
006a1ff9 movss xmm2, dword ptr [ecx]
006a1ffd movaps xmm1, xmm4
006a2000 mulss xmm1, dword ptr [0xb6a43c]
006a2008 movaps xmm0, xmm2
006a200b mulss xmm0, dword ptr [0xb6a5b0]
006a2013 mulss xmm4, dword ptr [0xb6a5b0]
006a201b mulss xmm2, dword ptr [0xb6a43c]
006a2023 mulss xmm1, dword ptr [edi + 0x28]
006a2028 mulss xmm2, dword ptr [edi + 0x28]
006a202d addss xmm1, xmm0
006a2031 subss xmm4, xmm2
006a2035 movss dword ptr [ebp - 0x38], xmm1
006a203a movss dword ptr [ebp - 0x34], xmm4
006a203f mov ecx, dword ptr [ebx + 8]
006a2042 movss xmm0, dword ptr [edi + 0x60]
006a2047 addss xmm0, dword ptr [ecx]
006a204b push 0
006a204d push 0xbeabf4
006a2052 push 0xbeab18
006a2057 push 0
006a2059 push eax
006a205a push 0
006a205c push dword ptr [ebp - 0x14]
006a205f lea eax, [ebp - 0x38]
006a2062 movss dword ptr [ebp - 0x30], xmm0
006a2067 movss xmm0, dword ptr [edi + 0x64]
006a206c addss xmm0, dword ptr [ecx + 4]
006a2071 mov ecx, dword ptr [0xbfd65c]
006a2077 push eax
006a2078 lea eax, [ebp - 0x30]
006a207b push eax
006a207c push dword ptr [edi + 0x94]
006a2082 movss dword ptr [ebp - 0x2c], xmm0
006a2087 push 9
006a2089 call 0x422e20
006a208e push eax
006a208f call 0x9ec34c
006a2094 jmp 0x6a1c64
006a2099 call 0x6c3d90
006a209e mov ecx, dword ptr [ebx + 0xc]
006a20a1 mov edi, dword ptr [ebx + 0x14]
006a20a4 mov esi, dword ptr [ebp - 0x14]
006a20a7 push 0
006a20a9 movss xmm3, dword ptr [ecx + 4]
006a20ae movss xmm4, dword ptr [ecx]
006a20b2 movaps xmm0, xmm3
006a20b5 mulss xmm0, dword ptr [0xb6a2f8]
006a20bd movaps xmm1, xmm4
006a20c0 mov ecx, dword ptr [ebx + 8]
006a20c3 mulss xmm1, dword ptr [0xb6a60c]
006a20cb push 0xbeabf4
006a20d0 mulss xmm0, dword ptr [edi + 0x28]
006a20d5 push 0xbeab18
006a20da mulss xmm4, dword ptr [0xb6a2f8]
006a20e2 push 0
006a20e4 mulss xmm3, dword ptr [0xb6a60c]
006a20ec subss xmm1, xmm0
006a20f0 push eax
006a20f1 movss xmm0, dword ptr [edi + 0x60]
006a20f6 lea eax, [ebp - 0x38]
006a20f9 addss xmm0, dword ptr [ecx]
006a20fd mulss xmm4, dword ptr [edi + 0x28]
006a2102 push 0
006a2104 push esi
006a2105 push eax
006a2106 movss dword ptr [ebp - 0x30], xmm0
006a210b lea eax, [ebp - 0x30]
006a210e movss xmm0, dword ptr [edi + 0x64]
006a2113 addss xmm4, xmm3
006a2117 addss xmm0, dword ptr [ecx + 4]
006a211c mov ecx, dword ptr [0xbfd65c]
006a2122 push eax
006a2123 push dword ptr [edi + 0x94]
006a2129 movss dword ptr [ebp - 0x38], xmm1
006a212e push 9
006a2130 movss dword ptr [ebp - 0x34], xmm4
006a2135 movss dword ptr [ebp - 0x2c], xmm0
006a213a call 0x422e20
006a213f push eax
006a2140 call 0x9ec34c
006a2145 add esp, 0x14
006a2148 mov dword ptr [ebp - 0x24], eax
006a214b lea eax, [ebp - 0x24]
006a214e lea ecx, [ebp - 0x4c]
006a2151 push eax
006a2152 push 0
006a2154 call 0x426fb0
006a2159 call 0x6c3d90
006a215e mov ecx, dword ptr [ebx + 0xc]
006a2161 push 0
006a2163 push 0xbeabf4
006a2168 push 0xbeab18
006a216d movss xmm4, dword ptr [ecx + 4]
006a2172 movss xmm2, dword ptr [ecx]
006a2176 movaps xmm1, xmm4
006a2179 mulss xmm1, dword ptr [0xb6a2f8]
006a2181 movaps xmm0, xmm2
006a2184 mov ecx, dword ptr [ebx + 8]
006a2187 mulss xmm0, dword ptr [0xb6a60c]
006a218f push 0
006a2191 mulss xmm1, dword ptr [edi + 0x28]
006a2196 push eax
006a2197 mulss xmm2, dword ptr [0xb6a2f8]
006a219f lea eax, [ebp - 0x38]
006a21a2 push 0
006a21a4 mulss xmm4, dword ptr [0xb6a60c]
006a21ac addss xmm1, xmm0
006a21b0 push esi
006a21b1 movss xmm0, dword ptr [edi + 0x60]
006a21b6 addss xmm0, dword ptr [ecx]
006a21ba mulss xmm2, dword ptr [edi + 0x28]
006a21bf push eax
006a21c0 movss dword ptr [ebp - 0x38], xmm1
006a21c5 movss dword ptr [ebp - 0x30], xmm0
006a21ca subss xmm4, xmm2
006a21ce movss xmm0, dword ptr [edi + 0x64]
006a21d3 addss xmm0, dword ptr [ecx + 4]
006a21d8 movss dword ptr [ebp - 0x34], xmm4
006a21dd movss dword ptr [ebp - 0x2c], xmm0
006a21e2 mov ecx, dword ptr [0xbfd65c]
006a21e8 lea eax, [ebp - 0x30]
006a21eb push eax
006a21ec push dword ptr [edi + 0x94]
006a21f2 push 9
006a21f4 call 0x422e20
006a21f9 push eax
006a21fa call 0x9ec34c
006a21ff mov esi, dword ptr [ebp - 0x48]
006a2202 add esp, 0x14
006a2205 mov dword ptr [ebp - 0x24], eax
006a2208 cmp esi, dword ptr [ebp - 0x44]
006a220b je 0x6a2217
006a220d mov dword ptr [esi], eax
006a220f add esi, 4
006a2212 mov dword ptr [ebp - 0x48], esi
006a2215 jmp 0x6a2227
006a2217 lea eax, [ebp - 0x24]
006a221a push eax
006a221b push esi
006a221c lea ecx, [ebp - 0x4c]
006a221f call 0x426fb0
006a2224 mov esi, dword ptr [ebp - 0x48]
006a2227 call 0x6c3d90
006a222c mov ecx, dword ptr [ebx + 0xc]
006a222f movss xmm5, dword ptr [0xb6a5a4]
006a2237 push 0
006a2239 push 0xbeabf4
006a223e movss xmm3, dword ptr [ecx + 4]
006a2243 movss xmm4, dword ptr [ecx]
006a2247 movaps xmm0, xmm3
006a224a mulss xmm0, dword ptr [0xb6a43c]
006a2252 movaps xmm1, xmm4
006a2255 mov ecx, dword ptr [ebx + 8]
006a2258 mulss xmm1, dword ptr [0xb6a5b0]
006a2260 push 0xbeab18
006a2265 mulss xmm4, dword ptr [0xb6a43c]
006a226d push 0
006a226f mulss xmm3, dword ptr [0xb6a5b0]
006a2277 push eax
006a2278 mulss xmm0, xmm5
006a227c lea eax, [ebp - 0x38]
006a227f push 0
006a2281 push dword ptr [ebp - 0x14]
006a2284 mulss xmm1, xmm5
006a2288 push eax
006a2289 mulss xmm0, dword ptr [edi + 0x28]
006a228e lea eax, [ebp - 0x30]
006a2291 push eax
006a2292 push dword ptr [edi + 0x94]
006a2298 mulss xmm4, xmm5
006a229c push 9
006a229e subss xmm1, xmm0
006a22a2 mulss xmm3, xmm5
006a22a6 movss xmm0, dword ptr [edi + 0x60]
006a22ab addss xmm0, dword ptr [ecx]
006a22af mulss xmm4, dword ptr [edi + 0x28]
006a22b4 movss dword ptr [ebp - 0x38], xmm1
006a22b9 movss dword ptr [ebp - 0x30], xmm0
006a22be addss xmm4, xmm3
006a22c2 movss xmm0, dword ptr [edi + 0x64]
006a22c7 addss xmm0, dword ptr [ecx + 4]
006a22cc mov ecx, dword ptr [0xbfd65c]
006a22d2 movss dword ptr [ebp - 0x34], xmm4
006a22d7 movss dword ptr [ebp - 0x2c], xmm0
006a22dc call 0x422e20
006a22e1 push eax
006a22e2 call 0x9ec34c
006a22e7 add esp, 0x14
006a22ea mov dword ptr [ebp - 0x24], eax
006a22ed cmp esi, dword ptr [ebp - 0x44]
006a22f0 je 0x6a22fc
006a22f2 mov dword ptr [esi], eax
006a22f4 add esi, 4
006a22f7 mov dword ptr [ebp - 0x48], esi
006a22fa jmp 0x6a230c
006a22fc lea eax, [ebp - 0x24]
006a22ff push eax
006a2300 push esi
006a2301 lea ecx, [ebp - 0x4c]
006a2304 call 0x426fb0
006a2309 mov esi, dword ptr [ebp - 0x48]
006a230c call 0x6c3d90
006a2311 mov ecx, dword ptr [ebx + 0xc]
006a2314 movss xmm5, dword ptr [0xb6a5a4]
006a231c movss xmm4, dword ptr [ecx + 4]
006a2321 movss xmm2, dword ptr [ecx]
006a2325 movaps xmm1, xmm4
006a2328 mulss xmm1, dword ptr [0xb6a43c]
006a2330 movaps xmm0, xmm2
006a2333 mulss xmm0, dword ptr [0xb6a5b0]
006a233b mulss xmm4, dword ptr [0xb6a5b0]
006a2343 mulss xmm2, dword ptr [0xb6a43c]
006a234b mulss xmm1, xmm5
006a234f mulss xmm0, xmm5
006a2353 mulss xmm4, xmm5
006a2357 mulss xmm2, xmm5
006a235b jmp 0x6a2023
006a2360 call 0x6c3d90
006a2365 mov edi, dword ptr [ebx + 0x14]
006a2368 mov ecx, dword ptr [ebx + 8]
006a236b mov esi, dword ptr [ebp - 0x14]
006a236e push 0
006a2370 movss xmm0, dword ptr [edi + 0x60]
006a2375 addss xmm0, dword ptr [ecx]
006a2379 push 0xbeabf4
006a237e push 0xbeab18
006a2383 push 0
006a2385 push eax
006a2386 push 0
006a2388 push esi
006a2389 push dword ptr [ebx + 0xc]
006a238c movss dword ptr [ebp - 0x38], xmm0
006a2391 lea eax, [ebp - 0x38]
006a2394 movss xmm0, dword ptr [edi + 0x64]
006a2399 addss xmm0, dword ptr [ecx + 4]
006a239e mov ecx, dword ptr [0xbfd65c]
006a23a4 push eax
006a23a5 push dword ptr [edi + 0x94]
006a23ab push 9
006a23ad movss dword ptr [ebp - 0x34], xmm0
006a23b2 call 0x422e20
006a23b7 push eax
006a23b8 call 0x9ec34c
006a23bd add esp, 0x14
006a23c0 mov dword ptr [ebp - 0x24], eax
006a23c3 lea eax, [ebp - 0x24]
006a23c6 lea ecx, [ebp - 0x4c]
006a23c9 push eax
006a23ca push 0
006a23cc call 0x426fb0
006a23d1 call 0x6c3d90
006a23d6 mov ecx, dword ptr [ebx + 0xc]
006a23d9 push 0
006a23db push 0xbeabf4
006a23e0 push 0xbeab18
006a23e5 movss xmm3, dword ptr [ecx + 4]
006a23ea movss xmm4, dword ptr [ecx]
006a23ee movaps xmm0, xmm3
006a23f1 mulss xmm0, dword ptr [0xb6a360]
006a23f9 movaps xmm1, xmm4
006a23fc mov ecx, dword ptr [ebx + 8]
006a23ff mulss xmm1, dword ptr [0xb6a600]
006a2407 push 0
006a2409 mulss xmm0, dword ptr [edi + 0x28]
006a240e push eax
006a240f mulss xmm4, dword ptr [0xb6a360]
006a2417 lea eax, [ebp - 0x38]
006a241a push 0
006a241c mulss xmm3, dword ptr [0xb6a600]
006a2424 subss xmm1, xmm0
006a2428 push esi
006a2429 movss xmm0, dword ptr [ecx]
006a242d addss xmm0, dword ptr [edi + 0x60]
006a2432 mulss xmm4, dword ptr [edi + 0x28]
006a2437 push eax
006a2438 lea eax, [ebp - 0x30]
006a243b movss dword ptr [ebp - 0x38], xmm1
006a2440 push eax
006a2441 push dword ptr [edi + 0x94]
006a2447 movss dword ptr [ebp - 0x30], xmm0
006a244c addss xmm4, xmm3
006a2450 movss xmm0, dword ptr [edi + 0x64]
006a2455 addss xmm0, dword ptr [ecx + 4]
006a245a mov ecx, dword ptr [0xbfd65c]
006a2460 push 9
006a2462 movss dword ptr [ebp - 0x34], xmm4
006a2467 movss dword ptr [ebp - 0x2c], xmm0
006a246c call 0x422e20
006a2471 push eax
006a2472 call 0x9ec34c
006a2477 mov esi, dword ptr [ebp - 0x48]
006a247a add esp, 0x14
006a247d mov dword ptr [ebp - 0x24], eax
006a2480 cmp esi, dword ptr [ebp - 0x44]
006a2483 je 0x6a248f
006a2485 mov dword ptr [esi], eax
006a2487 add esi, 4
006a248a mov dword ptr [ebp - 0x48], esi
006a248d jmp 0x6a249f
006a248f lea eax, [ebp - 0x24]
006a2492 push eax
006a2493 push esi
006a2494 lea ecx, [ebp - 0x4c]
006a2497 call 0x426fb0
006a249c mov esi, dword ptr [ebp - 0x48]
006a249f call 0x6c3d90
006a24a4 mov ecx, dword ptr [ebx + 0xc]
006a24a7 push 0
006a24a9 push 0xbeabf4
006a24ae push 0xbeab18
006a24b3 movss xmm4, dword ptr [ecx + 4]
006a24b8 movss xmm2, dword ptr [ecx]
006a24bc movaps xmm1, xmm4
006a24bf mulss xmm1, dword ptr [0xb6a360]
006a24c7 movaps xmm0, xmm2
006a24ca mov ecx, dword ptr [ebx + 8]
006a24cd mulss xmm0, dword ptr [0xb6a600]
006a24d5 push 0
006a24d7 mulss xmm1, dword ptr [edi + 0x28]
006a24dc push eax
006a24dd mulss xmm2, dword ptr [0xb6a360]
006a24e5 lea eax, [ebp - 0x38]
006a24e8 push 0
006a24ea push dword ptr [ebp - 0x14]
006a24ed mulss xmm4, dword ptr [0xb6a600]
006a24f5 addss xmm1, xmm0
006a24f9 push eax
006a24fa movss xmm0, dword ptr [ecx]
006a24fe lea eax, [ebp - 0x30]
006a2501 addss xmm0, dword ptr [edi + 0x60]
006a2506 mulss xmm2, dword ptr [edi + 0x28]
006a250b push eax
006a250c push dword ptr [edi + 0x94]
006a2512 movss dword ptr [ebp - 0x38], xmm1
006a2517 movss dword ptr [ebp - 0x30], xmm0
006a251c subss xmm4, xmm2
006a2520 movss xmm0, dword ptr [edi + 0x64]
006a2525 addss xmm0, dword ptr [ecx + 4]
006a252a mov ecx, dword ptr [0xbfd65c]
006a2530 push 9
006a2532 movss dword ptr [ebp - 0x34], xmm4
006a2537 movss dword ptr [ebp - 0x2c], xmm0
006a253c call 0x422e20
006a2541 push eax
006a2542 call 0x9ec34c
006a2547 add esp, 0x14
006a254a mov dword ptr [ebp - 0x24], eax
006a254d cmp esi, dword ptr [ebp - 0x44]
006a2550 je 0x6a255c
006a2552 mov dword ptr [esi], eax
006a2554 add esi, 4
006a2557 mov dword ptr [ebp - 0x48], esi
006a255a jmp 0x6a256c
006a255c lea eax, [ebp - 0x24]
006a255f push eax
006a2560 push esi
006a2561 lea ecx, [ebp - 0x4c]
006a2564 call 0x426fb0
006a2569 mov esi, dword ptr [ebp - 0x48]
006a256c call 0x6c3d90
006a2571 mov ecx, dword ptr [ebx + 0xc]
006a2574 push 0
006a2576 push 0xbeabf4
006a257b push 0xbeab18
006a2580 movss xmm3, dword ptr [ecx + 4]
006a2585 movss xmm4, dword ptr [ecx]
006a2589 movaps xmm0, xmm3
006a258c mulss xmm0, dword ptr [0xb6a43c]
006a2594 movaps xmm1, xmm4
006a2597 mov ecx, dword ptr [ebx + 8]
006a259a mulss xmm1, dword ptr [0xb6a5b0]
006a25a2 push 0
006a25a4 mulss xmm0, dword ptr [edi + 0x28]
006a25a9 push eax
006a25aa mulss xmm4, dword ptr [0xb6a43c]
006a25b2 lea eax, [ebp - 0x38]
006a25b5 push 0
006a25b7 push dword ptr [ebp - 0x14]
006a25ba mulss xmm3, dword ptr [0xb6a5b0]
006a25c2 subss xmm1, xmm0
006a25c6 push eax
006a25c7 movss xmm0, dword ptr [ecx]
006a25cb lea eax, [ebp - 0x30]
006a25ce addss xmm0, dword ptr [edi + 0x60]
006a25d3 mulss xmm4, dword ptr [edi + 0x28]
006a25d8 push eax
006a25d9 push dword ptr [edi + 0x94]
006a25df movss dword ptr [ebp - 0x38], xmm1
006a25e4 movss dword ptr [ebp - 0x30], xmm0
006a25e9 addss xmm4, xmm3
006a25ed movss xmm0, dword ptr [edi + 0x64]
006a25f2 addss xmm0, dword ptr [ecx + 4]
006a25f7 mov ecx, dword ptr [0xbfd65c]
006a25fd push 9
006a25ff movss dword ptr [ebp - 0x34], xmm4
006a2604 movss dword ptr [ebp - 0x2c], xmm0
006a2609 call 0x422e20
006a260e push eax
006a260f call 0x9ec34c
006a2614 add esp, 0x14
006a2617 mov dword ptr [ebp - 0x24], eax
006a261a cmp esi, dword ptr [ebp - 0x44]
006a261d je 0x6a2629
006a261f mov dword ptr [esi], eax
006a2621 add esi, 4
006a2624 mov dword ptr [ebp - 0x48], esi
006a2627 jmp 0x6a2639
006a2629 lea eax, [ebp - 0x24]
006a262c push eax
006a262d push esi
006a262e lea ecx, [ebp - 0x4c]
006a2631 call 0x426fb0
006a2636 mov esi, dword ptr [ebp - 0x48]
006a2639 call 0x6c3d90
006a263e mov ecx, dword ptr [ebx + 0xc]
006a2641 movss xmm4, dword ptr [ecx + 4]
006a2646 movss xmm2, dword ptr [ecx]
006a264a movaps xmm1, xmm4
006a264d mulss xmm1, dword ptr [0xb6a43c]
006a2655 movaps xmm0, xmm2
006a2658 mov ecx, dword ptr [ebx + 8]
006a265b mulss xmm2, dword ptr [0xb6a43c]
006a2663 mulss xmm0, dword ptr [0xb6a5b0]
006a266b mulss xmm1, dword ptr [edi + 0x28]
006a2670 mulss xmm4, dword ptr [0xb6a5b0]
006a2678 mulss xmm2, dword ptr [edi + 0x28]
006a267d addss xmm1, xmm0
006a2681 movss xmm0, dword ptr [ecx]
006a2685 addss xmm0, dword ptr [edi + 0x60]
006a268a subss xmm4, xmm2
006a268e movss dword ptr [ebp - 0x38], xmm1
006a2693 movss dword ptr [ebp - 0x34], xmm4
006a2698 jmp 0x6a204b
006a269d mov eax, dword ptr [ebx + 0xc]
006a26a0 movss xmm0, dword ptr [eax]
006a26a4 movss dword ptr [ebp - 0x1c], xmm0
006a26a9 call 0x6c3d90
006a26ae mov ecx, dword ptr [ebx + 8]
006a26b1 mov edi, dword ptr [ebx + 0x14]
006a26b4 mov esi, dword ptr [ebp - 0x14]
006a26b7 push 0
006a26b9 push 0xbeabf4
006a26be push 0xbeab18
006a26c3 push 0
006a26c5 push eax
006a26c6 movss dword ptr [ebp - 0x38], xmm0
006a26cb lea eax, [ebp - 0x38]
006a26ce movss xmm0, dword ptr [ecx]
006a26d2 addss xmm0, dword ptr [edi + 0x60]
006a26d7 push 0
006a26d9 push esi
006a26da push eax
006a26db lea eax, [ebp - 0x30]
006a26de mov dword ptr [ebp - 0x34], 0
006a26e5 movss dword ptr [ebp - 0x30], xmm0
006a26ea movss xmm0, dword ptr [edi + 0x64]
006a26ef addss xmm0, dword ptr [ecx + 4]
006a26f4 mov ecx, dword ptr [0xbfd65c]
006a26fa push eax
006a26fb push dword ptr [edi + 0x94]
006a2701 push 9
006a2703 movss dword ptr [ebp - 0x2c], xmm0
006a2708 call 0x422e20
006a270d push eax
006a270e call 0x9ec34c
006a2713 add esp, 0x14
006a2716 mov dword ptr [ebp - 0x24], eax
006a2719 lea eax, [ebp - 0x24]
006a271c lea ecx, [ebp - 0x4c]
006a271f push eax
006a2720 push 0
006a2722 call 0x426fb0
006a2727 call 0x6c3d90
006a272c movss xmm0, dword ptr [ebp - 0x1c]
006a2731 xorps xmm0, xmmword ptr [0xb6c9b0]
006a2738 mov ecx, dword ptr [ebx + 8]
006a273b push 0
006a273d push 0xbeabf4
006a2742 push 0xbeab18
006a2747 push 0
006a2749 push eax
006a274a movss dword ptr [ebp - 0x20], xmm0
006a274f lea eax, [ebp - 0x38]
006a2752 movss dword ptr [ebp - 0x38], xmm0
006a2757 movss xmm0, dword ptr [ecx]
006a275b addss xmm0, dword ptr [edi + 0x60]
006a2760 push 0
006a2762 push esi
006a2763 push eax
006a2764 lea eax, [ebp - 0x30]
006a2767 mov dword ptr [ebp - 0x34], 0
006a276e movss dword ptr [ebp - 0x30], xmm0
006a2773 movss xmm0, dword ptr [edi + 0x64]
006a2778 addss xmm0, dword ptr [ecx + 4]
006a277d mov ecx, dword ptr [0xbfd65c]
006a2783 push eax
006a2784 push dword ptr [edi + 0x94]
006a278a push 9
006a278c movss dword ptr [ebp - 0x2c], xmm0
006a2791 call 0x422e20
006a2796 push eax
006a2797 call 0x9ec34c
006a279c mov esi, dword ptr [ebp - 0x48]
006a279f add esp, 0x14
006a27a2 mov dword ptr [ebp - 0x24], eax
006a27a5 cmp esi, dword ptr [ebp - 0x44]
006a27a8 je 0x6a27b4
006a27aa mov dword ptr [esi], eax
006a27ac add esi, 4
006a27af mov dword ptr [ebp - 0x48], esi
006a27b2 jmp 0x6a27c4
006a27b4 lea eax, [ebp - 0x24]
006a27b7 push eax
006a27b8 push esi
006a27b9 lea ecx, [ebp - 0x4c]
006a27bc call 0x426fb0
006a27c1 mov esi, dword ptr [ebp - 0x48]
006a27c4 call 0x6c3d90
006a27c9 movss xmm0, dword ptr [ebp - 0x1c]
006a27ce mov ecx, dword ptr [ebx + 8]
006a27d1 push 0
006a27d3 push 0xbeabf4
006a27d8 push 0xbeab18
006a27dd push 0
006a27df push eax
006a27e0 movss dword ptr [ebp - 0x34], xmm0
006a27e5 lea eax, [ebp - 0x38]
006a27e8 movss xmm0, dword ptr [edi + 0x60]
006a27ed addss xmm0, dword ptr [ecx]
006a27f1 push 0
006a27f3 push dword ptr [ebp - 0x14]
006a27f6 mov dword ptr [ebp - 0x38], 0
006a27fd push eax
006a27fe movss dword ptr [ebp - 0x30], xmm0
006a2803 lea eax, [ebp - 0x30]
006a2806 movss xmm0, dword ptr [edi + 0x64]
006a280b addss xmm0, dword ptr [ecx + 4]
006a2810 mov ecx, dword ptr [0xbfd65c]
006a2816 push eax
006a2817 push dword ptr [edi + 0x94]
006a281d push 9
006a281f movss dword ptr [ebp - 0x2c], xmm0
006a2824 call 0x422e20
006a2829 push eax
006a282a call 0x9ec34c
006a282f add esp, 0x14
006a2832 mov dword ptr [ebp - 0x24], eax
006a2835 cmp esi, dword ptr [ebp - 0x44]
006a2838 je 0x6a2844
006a283a mov dword ptr [esi], eax
006a283c add esi, 4
006a283f mov dword ptr [ebp - 0x48], esi
006a2842 jmp 0x6a2854
006a2844 lea eax, [ebp - 0x24]
006a2847 push eax
006a2848 push esi
006a2849 lea ecx, [ebp - 0x4c]
006a284c call 0x426fb0
006a2851 mov esi, dword ptr [ebp - 0x48]
006a2854 call 0x6c3d90
006a2859 movss xmm0, dword ptr [ebp - 0x20]
006a285e mov dword ptr [ebp - 0x38], 0
006a2865 movss dword ptr [ebp - 0x34], xmm0
006a286a jmp 0x6a203f
006a286f mov eax, dword ptr [ebx + 0xc]
006a2872 movss xmm0, dword ptr [eax]
006a2876 mulss xmm0, dword ptr [0xb6a524]
006a287e movss dword ptr [ebp - 0x1c], xmm0
006a2883 call 0x6c3d90
006a2888 mov ecx, dword ptr [ebx + 8]
006a288b mov edi, dword ptr [ebx + 0x14]
006a288e mov esi, dword ptr [ebp - 0x14]
006a2891 push 0
006a2893 push 0xbeabf4
006a2898 push 0xbeab18
006a289d push 0
006a289f push eax
006a28a0 movss dword ptr [ebp - 0x38], xmm0
006a28a5 lea eax, [ebp - 0x38]
006a28a8 movss dword ptr [ebp - 0x34], xmm0
006a28ad movss xmm0, dword ptr [ecx]
006a28b1 addss xmm0, dword ptr [edi + 0x60]
006a28b6 push 0
006a28b8 push esi
006a28b9 push eax
006a28ba lea eax, [ebp - 0x30]
006a28bd movss dword ptr [ebp - 0x30], xmm0
006a28c2 movss xmm0, dword ptr [edi + 0x64]
006a28c7 addss xmm0, dword ptr [ecx + 4]
006a28cc mov ecx, dword ptr [0xbfd65c]
006a28d2 push eax
006a28d3 push dword ptr [edi + 0x94]
006a28d9 push 9
006a28db movss dword ptr [ebp - 0x2c], xmm0
006a28e0 call 0x422e20
006a28e5 push eax
006a28e6 call 0x9ec34c
006a28eb add esp, 0x14
006a28ee mov dword ptr [ebp - 0x24], eax
006a28f1 lea eax, [ebp - 0x24]
006a28f4 lea ecx, [ebp - 0x4c]
006a28f7 push eax
006a28f8 push 0
006a28fa call 0x426fb0
006a28ff call 0x6c3d90
006a2904 mov ecx, dword ptr [ebx + 8]
006a2907 movss xmm0, dword ptr [ebp - 0x1c]
006a290c push 0
006a290e push 0xbeabf4
006a2913 push 0xbeab18
006a2918 push 0
006a291a movaps xmm1, xmm0
006a291d movss dword ptr [ebp - 0x34], xmm0
006a2922 movss xmm0, dword ptr [ecx]
006a2926 addss xmm0, dword ptr [edi + 0x60]
006a292b xorps xmm1, xmmword ptr [0xb6c9b0]
006a2932 push eax
006a2933 push 0
006a2935 push esi
006a2936 lea eax, [ebp - 0x38]
006a2939 movss dword ptr [ebp - 0x30], xmm0
006a293e movss xmm0, dword ptr [edi + 0x64]
006a2943 addss xmm0, dword ptr [ecx + 4]
006a2948 mov ecx, dword ptr [0xbfd65c]
006a294e push eax
006a294f lea eax, [ebp - 0x30]
006a2952 movss dword ptr [ebp - 0x18], xmm1
006a2957 push eax
006a2958 push dword ptr [edi + 0x94]
006a295e movss dword ptr [ebp - 0x38], xmm1
006a2963 push 9
006a2965 movss dword ptr [ebp - 0x2c], xmm0
006a296a call 0x422e20
006a296f push eax
006a2970 call 0x9ec34c
006a2975 mov esi, dword ptr [ebp - 0x48]
006a2978 add esp, 0x14
006a297b mov dword ptr [ebp - 0x24], eax
006a297e cmp esi, dword ptr [ebp - 0x44]
006a2981 je 0x6a298d
006a2983 mov dword ptr [esi], eax
006a2985 add esi, 4
006a2988 mov dword ptr [ebp - 0x48], esi
006a298b jmp 0x6a299d
006a298d lea eax, [ebp - 0x24]
006a2990 push eax
006a2991 push esi
006a2992 lea ecx, [ebp - 0x4c]
006a2995 call 0x426fb0
006a299a mov esi, dword ptr [ebp - 0x48]
006a299d call 0x6c3d90
006a29a2 movss xmm0, dword ptr [ebp - 0x1c]
006a29a7 mov ecx, dword ptr [ebx + 8]
006a29aa push 0
006a29ac push 0xbeabf4
006a29b1 push 0xbeab18
006a29b6 movss dword ptr [ebp - 0x38], xmm0
006a29bb movss xmm0, dword ptr [ebp - 0x18]
006a29c0 push 0
006a29c2 push eax
006a29c3 movss dword ptr [ebp - 0x34], xmm0
006a29c8 lea eax, [ebp - 0x38]
006a29cb movss xmm0, dword ptr [edi + 0x60]
006a29d0 addss xmm0, dword ptr [ecx]
006a29d4 push 0
006a29d6 push dword ptr [ebp - 0x14]
006a29d9 push eax
006a29da movss dword ptr [ebp - 0x30], xmm0
006a29df lea eax, [ebp - 0x30]
006a29e2 movss xmm0, dword ptr [edi + 0x64]
006a29e7 addss xmm0, dword ptr [ecx + 4]
006a29ec mov ecx, dword ptr [0xbfd65c]
006a29f2 push eax
006a29f3 push dword ptr [edi + 0x94]
006a29f9 push 9
006a29fb movss dword ptr [ebp - 0x2c], xmm0
006a2a00 call 0x422e20
006a2a05 push eax
006a2a06 call 0x9ec34c
006a2a0b add esp, 0x14
006a2a0e mov dword ptr [ebp - 0x24], eax
006a2a11 cmp esi, dword ptr [ebp - 0x44]
006a2a14 je 0x6a2a20
006a2a16 mov dword ptr [esi], eax
006a2a18 add esi, 4
006a2a1b mov dword ptr [ebp - 0x48], esi
006a2a1e jmp 0x6a2a30
006a2a20 lea eax, [ebp - 0x24]
006a2a23 push eax
006a2a24 push esi
006a2a25 lea ecx, [ebp - 0x4c]
006a2a28 call 0x426fb0
006a2a2d mov esi, dword ptr [ebp - 0x48]
006a2a30 call 0x6c3d90
006a2a35 movss xmm0, dword ptr [ebp - 0x18]
006a2a3a movss dword ptr [ebp - 0x38], xmm0
006a2a3f movss dword ptr [ebp - 0x34], xmm0
006a2a44 jmp 0x6a203f
006a2a49 mov eax, dword ptr [ebx + 0xc]
006a2a4c movss xmm0, dword ptr [eax]
006a2a50 movss dword ptr [ebp - 0x18], xmm0
006a2a55 call 0x6c3d90
006a2a5a mov ecx, dword ptr [ebx + 8]
006a2a5d mov edi, dword ptr [ebx + 0x14]
006a2a60 mov esi, dword ptr [ebp - 0x14]
006a2a63 push 0
006a2a65 push 0xbeabf4
006a2a6a push 0xbeab18
006a2a6f push 0
006a2a71 push eax
006a2a72 movss dword ptr [ebp - 0x38], xmm0
006a2a77 lea eax, [ebp - 0x38]
006a2a7a movss xmm0, dword ptr [ecx]
006a2a7e addss xmm0, dword ptr [edi + 0x60]
006a2a83 push 0
006a2a85 push esi
006a2a86 push eax
006a2a87 lea eax, [ebp - 0x30]
006a2a8a mov dword ptr [ebp - 0x34], 0
006a2a91 movss dword ptr [ebp - 0x30], xmm0
006a2a96 movss xmm0, dword ptr [edi + 0x64]
006a2a9b addss xmm0, dword ptr [ecx + 4]
006a2aa0 mov ecx, dword ptr [0xbfd65c]
006a2aa6 push eax
006a2aa7 push dword ptr [edi + 0x94]
006a2aad push 9
006a2aaf movss dword ptr [ebp - 0x2c], xmm0
006a2ab4 call 0x422e20
006a2ab9 push eax
006a2aba call 0x9ec34c
006a2abf add esp, 0x14
006a2ac2 mov dword ptr [ebp - 0x24], eax
006a2ac5 lea eax, [ebp - 0x24]
006a2ac8 lea ecx, [ebp - 0x4c]
006a2acb push eax
006a2acc push 0
006a2ace call 0x426fb0
006a2ad3 call 0x6c3d90
006a2ad8 movss xmm0, dword ptr [ebp - 0x18]
006a2add xorps xmm0, xmmword ptr [0xb6c9b0]
006a2ae4 mov ecx, dword ptr [ebx + 8]
006a2ae7 push 0
006a2ae9 push 0xbeabf4
006a2aee push 0xbeab18
006a2af3 push 0
006a2af5 push eax
006a2af6 movss dword ptr [ebp - 0x20], xmm0
006a2afb lea eax, [ebp - 0x38]
006a2afe movss dword ptr [ebp - 0x38], xmm0
006a2b03 movss xmm0, dword ptr [ecx]
006a2b07 addss xmm0, dword ptr [edi + 0x60]
006a2b0c push 0
006a2b0e push esi
006a2b0f push eax
006a2b10 lea eax, [ebp - 0x30]
006a2b13 mov dword ptr [ebp - 0x34], 0
006a2b1a movss dword ptr [ebp - 0x30], xmm0
006a2b1f movss xmm0, dword ptr [edi + 0x64]
006a2b24 addss xmm0, dword ptr [ecx + 4]
006a2b29 mov ecx, dword ptr [0xbfd65c]
006a2b2f push eax
006a2b30 push dword ptr [edi + 0x94]
006a2b36 push 9
006a2b38 movss dword ptr [ebp - 0x2c], xmm0
006a2b3d call 0x422e20
006a2b42 push eax
006a2b43 call 0x9ec34c
006a2b48 mov esi, dword ptr [ebp - 0x48]
006a2b4b add esp, 0x14
006a2b4e mov dword ptr [ebp - 0x24], eax
006a2b51 cmp esi, dword ptr [ebp - 0x44]
006a2b54 je 0x6a2b60
006a2b56 mov dword ptr [esi], eax
006a2b58 add esi, 4
006a2b5b mov dword ptr [ebp - 0x48], esi
006a2b5e jmp 0x6a2b70
006a2b60 lea eax, [ebp - 0x24]
006a2b63 push eax
006a2b64 push esi
006a2b65 lea ecx, [ebp - 0x4c]
006a2b68 call 0x426fb0
006a2b6d mov esi, dword ptr [ebp - 0x48]
006a2b70 call 0x6c3d90
006a2b75 movss xmm0, dword ptr [ebp - 0x18]
006a2b7a mov ecx, dword ptr [ebx + 8]
006a2b7d push 0
006a2b7f push 0xbeabf4
006a2b84 push 0xbeab18
006a2b89 push 0
006a2b8b push eax
006a2b8c movss dword ptr [ebp - 0x34], xmm0
006a2b91 lea eax, [ebp - 0x38]
006a2b94 movss xmm0, dword ptr [edi + 0x60]
006a2b99 addss xmm0, dword ptr [ecx]
006a2b9d push 0
006a2b9f push dword ptr [ebp - 0x14]
006a2ba2 mov dword ptr [ebp - 0x38], 0
006a2ba9 push eax
006a2baa movss dword ptr [ebp - 0x30], xmm0
006a2baf lea eax, [ebp - 0x30]
006a2bb2 movss xmm0, dword ptr [edi + 0x64]
006a2bb7 addss xmm0, dword ptr [ecx + 4]
006a2bbc mov ecx, dword ptr [0xbfd65c]
006a2bc2 push eax
006a2bc3 push dword ptr [edi + 0x94]
006a2bc9 push 9
006a2bcb movss dword ptr [ebp - 0x2c], xmm0
006a2bd0 call 0x422e20
006a2bd5 push eax
006a2bd6 call 0x9ec34c
006a2bdb add esp, 0x14
006a2bde mov dword ptr [ebp - 0x24], eax
006a2be1 cmp esi, dword ptr [ebp - 0x44]
006a2be4 je 0x6a2bf0
006a2be6 mov dword ptr [esi], eax
006a2be8 add esi, 4
006a2beb mov dword ptr [ebp - 0x48], esi
006a2bee jmp 0x6a2c00
006a2bf0 lea eax, [ebp - 0x24]
006a2bf3 push eax
006a2bf4 push esi
006a2bf5 lea ecx, [ebp - 0x4c]
006a2bf8 call 0x426fb0
006a2bfd mov esi, dword ptr [ebp - 0x48]
006a2c00 call 0x6c3d90
006a2c05 movss xmm0, dword ptr [ebp - 0x20]
006a2c0a mov ecx, dword ptr [ebx + 8]
006a2c0d push 0
006a2c0f push 0xbeabf4
006a2c14 push 0xbeab18
006a2c19 push 0
006a2c1b push eax
006a2c1c movss dword ptr [ebp - 0x34], xmm0
006a2c21 lea eax, [ebp - 0x38]
006a2c24 movss xmm0, dword ptr [edi + 0x60]
006a2c29 addss xmm0, dword ptr [ecx]
006a2c2d push 0
006a2c2f push dword ptr [ebp - 0x14]
006a2c32 mov dword ptr [ebp - 0x38], 0
006a2c39 push eax
006a2c3a movss dword ptr [ebp - 0x30], xmm0
006a2c3f lea eax, [ebp - 0x30]
006a2c42 movss xmm0, dword ptr [edi + 0x64]
006a2c47 addss xmm0, dword ptr [ecx + 4]
006a2c4c mov ecx, dword ptr [0xbfd65c]
006a2c52 push eax
006a2c53 push dword ptr [edi + 0x94]
006a2c59 push 9
006a2c5b movss dword ptr [ebp - 0x2c], xmm0
006a2c60 call 0x422e20
006a2c65 push eax
006a2c66 call 0x9ec34c
006a2c6b add esp, 0x14
006a2c6e mov dword ptr [ebp - 0x24], eax
006a2c71 cmp esi, dword ptr [ebp - 0x44]
006a2c74 je 0x6a2c80
006a2c76 mov dword ptr [esi], eax
006a2c78 add esi, 4
006a2c7b mov dword ptr [ebp - 0x48], esi
006a2c7e jmp 0x6a2c90
006a2c80 lea eax, [ebp - 0x24]
006a2c83 push eax
006a2c84 push esi
006a2c85 lea ecx, [ebp - 0x4c]
006a2c88 call 0x426fb0
006a2c8d mov esi, dword ptr [ebp - 0x48]
006a2c90 movss xmm0, dword ptr [ebp - 0x18]
006a2c95 mulss xmm0, dword ptr [0xb6a524]
006a2c9d movss dword ptr [ebp - 0x18], xmm0
006a2ca2 call 0x6c3d90
006a2ca7 mov ecx, dword ptr [ebx + 8]
006a2caa push 0
006a2cac push 0xbeabf4
006a2cb1 push 0xbeab18
006a2cb6 push 0
006a2cb8 push eax
006a2cb9 movss dword ptr [ebp - 0x38], xmm0
006a2cbe lea eax, [ebp - 0x38]
006a2cc1 movss dword ptr [ebp - 0x34], xmm0
006a2cc6 movss xmm0, dword ptr [ecx]
006a2cca addss xmm0, dword ptr [edi + 0x60]
006a2ccf push 0
006a2cd1 push dword ptr [ebp - 0x14]
006a2cd4 push eax
006a2cd5 movss dword ptr [ebp - 0x30], xmm0
006a2cda lea eax, [ebp - 0x30]
006a2cdd movss xmm0, dword ptr [edi + 0x64]
006a2ce2 addss xmm0, dword ptr [ecx + 4]
006a2ce7 mov ecx, dword ptr [0xbfd65c]
006a2ced push eax
006a2cee push dword ptr [edi + 0x94]
006a2cf4 push 9
006a2cf6 movss dword ptr [ebp - 0x2c], xmm0
006a2cfb call 0x422e20
006a2d00 push eax
006a2d01 call 0x9ec34c
006a2d06 add esp, 0x14
006a2d09 mov dword ptr [ebp - 0x24], eax
006a2d0c cmp esi, dword ptr [ebp - 0x44]
006a2d0f je 0x6a2d1b
006a2d11 mov dword ptr [esi], eax
006a2d13 add esi, 4
006a2d16 mov dword ptr [ebp - 0x48], esi
006a2d19 jmp 0x6a2d2b
006a2d1b lea eax, [ebp - 0x24]
006a2d1e push eax
006a2d1f push esi
006a2d20 lea ecx, [ebp - 0x4c]
006a2d23 call 0x426fb0
006a2d28 mov esi, dword ptr [ebp - 0x48]
006a2d2b call 0x6c3d90
006a2d30 mov ecx, dword ptr [ebx + 8]
006a2d33 movss xmm0, dword ptr [ebp - 0x18]
006a2d38 push 0
006a2d3a push 0xbeabf4
006a2d3f push 0xbeab18
006a2d44 push 0
006a2d46 push eax
006a2d47 movaps xmm1, xmm0
006a2d4a movss dword ptr [ebp - 0x34], xmm0
006a2d4f movss xmm0, dword ptr [ecx]
006a2d53 lea eax, [ebp - 0x38]
006a2d56 addss xmm0, dword ptr [edi + 0x60]
006a2d5b xorps xmm1, xmmword ptr [0xb6c9b0]
006a2d62 push 0
006a2d64 push dword ptr [ebp - 0x14]
006a2d67 movss dword ptr [ebp - 0x1c], xmm1
006a2d6c push eax
006a2d6d movss dword ptr [ebp - 0x30], xmm0
006a2d72 lea eax, [ebp - 0x30]
006a2d75 movss xmm0, dword ptr [edi + 0x64]
006a2d7a addss xmm0, dword ptr [ecx + 4]
006a2d7f mov ecx, dword ptr [0xbfd65c]
006a2d85 push eax
006a2d86 push dword ptr [edi + 0x94]
006a2d8c movss dword ptr [ebp - 0x38], xmm1
006a2d91 push 9
006a2d93 movss dword ptr [ebp - 0x2c], xmm0
006a2d98 call 0x422e20
006a2d9d push eax
006a2d9e call 0x9ec34c
006a2da3 add esp, 0x14
006a2da6 mov dword ptr [ebp - 0x24], eax
006a2da9 cmp esi, dword ptr [ebp - 0x44]
006a2dac je 0x6a2db8
006a2dae mov dword ptr [esi], eax
006a2db0 add esi, 4
006a2db3 mov dword ptr [ebp - 0x48], esi
006a2db6 jmp 0x6a2dc8
006a2db8 lea eax, [ebp - 0x24]
006a2dbb push eax
006a2dbc push esi
006a2dbd lea ecx, [ebp - 0x4c]
006a2dc0 call 0x426fb0
006a2dc5 mov esi, dword ptr [ebp - 0x48]
006a2dc8 call 0x6c3d90
006a2dcd movss xmm0, dword ptr [ebp - 0x18]
006a2dd2 mov ecx, dword ptr [ebx + 8]
006a2dd5 push 0
006a2dd7 push 0xbeabf4
006a2ddc push 0xbeab18
006a2de1 movss dword ptr [ebp - 0x38], xmm0
006a2de6 movss xmm0, dword ptr [ebp - 0x1c]
006a2deb push 0
006a2ded push eax
006a2dee movss dword ptr [ebp - 0x34], xmm0
006a2df3 lea eax, [ebp - 0x38]
006a2df6 movss xmm0, dword ptr [edi + 0x60]
006a2dfb addss xmm0, dword ptr [ecx]
006a2dff push 0
006a2e01 push dword ptr [ebp - 0x14]
006a2e04 push eax
006a2e05 movss dword ptr [ebp - 0x30], xmm0
006a2e0a lea eax, [ebp - 0x30]
006a2e0d movss xmm0, dword ptr [edi + 0x64]
006a2e12 addss xmm0, dword ptr [ecx + 4]
006a2e17 mov ecx, dword ptr [0xbfd65c]
006a2e1d push eax
006a2e1e push dword ptr [edi + 0x94]
006a2e24 push 9
006a2e26 movss dword ptr [ebp - 0x2c], xmm0
006a2e2b call 0x422e20
006a2e30 push eax
006a2e31 call 0x9ec34c
006a2e36 add esp, 0x14
006a2e39 mov dword ptr [ebp - 0x24], eax
006a2e3c cmp esi, dword ptr [ebp - 0x44]
006a2e3f je 0x6a2e4b
006a2e41 mov dword ptr [esi], eax
006a2e43 add esi, 4
006a2e46 mov dword ptr [ebp - 0x48], esi
006a2e49 jmp 0x6a2e5b
006a2e4b lea eax, [ebp - 0x24]
006a2e4e push eax
006a2e4f push esi
006a2e50 lea ecx, [ebp - 0x4c]
006a2e53 call 0x426fb0
006a2e58 mov esi, dword ptr [ebp - 0x48]
006a2e5b call 0x6c3d90
006a2e60 movss xmm0, dword ptr [ebp - 0x1c]
006a2e65 movss dword ptr [ebp - 0x38], xmm0
006a2e6a movss dword ptr [ebp - 0x34], xmm0
006a2e6f jmp 0x6a203f
006a2e74 mov eax, dword ptr [ebx + 0xc]
006a2e77 movss xmm2, dword ptr [0xb6a914]
006a2e7f mov edi, dword ptr [ebx + 0x14]
006a2e82 movss xmm0, dword ptr [eax + 4]
006a2e87 addss xmm0, dword ptr [0xb6a480]
006a2e8f movss xmm1, dword ptr [edi + 0x18]
006a2e94 cvttss2si ecx, xmm0
006a2e98 mov dword ptr [ebp - 0x20], ecx
006a2e9b movd xmm0, ecx
006a2e9f cvtdq2ps xmm0, xmm0
006a2ea2 divss xmm2, xmm0
006a2ea6 movss xmm0, dword ptr [eax]
006a2eaa movss dword ptr [ebp - 0x2c], xmm2
006a2eaf movss dword ptr [ebp - 0x1c], xmm0
006a2eb4 test ecx, ecx
006a2eb6 jle 0x6a301f
006a2ebc nop dword ptr [eax]
006a2ec0 movaps xmm0, xmm2
006a2ec3 addss xmm1, xmm0
006a2ec7 movaps xmm0, xmm1
006a2eca movss dword ptr [ebp - 0x24], xmm1
006a2ecf call 0x411fe0
006a2ed4 mulss xmm0, dword ptr [ebp - 0x1c]
006a2ed9 movss dword ptr [ebp - 0x18], xmm0
006a2ede movss dword ptr [ebp - 0x38], xmm0
006a2ee3 movss xmm0, dword ptr [ebp - 0x24]
006a2ee8 call 0x412010
006a2eed movaps xmm2, xmm0
006a2ef0 movss xmm0, dword ptr [edi + 0x70]
006a2ef5 ucomiss xmm0, dword ptr [0xc02fec]
006a2efc mulss xmm2, dword ptr [ebp - 0x1c]
006a2f01 lahf 
006a2f02 movss dword ptr [ebp - 0x28], xmm0
006a2f07 movss dword ptr [ebp - 0x34], xmm2
006a2f0c test ah, 0x44
006a2f0f jp 0x6a2f23
006a2f11 movss xmm0, dword ptr [edi + 0x74]
006a2f16 ucomiss xmm0, dword ptr [0xc02ff0]
006a2f1d lahf 
006a2f1e test ah, 0x44
006a2f21 jnp 0x6a2f87
006a2f23 movss xmm0, dword ptr [ebp - 0x18]
006a2f28 movaps xmm1, xmm2
006a2f2b mulss xmm0, xmm0
006a2f2f mulss xmm1, xmm2
006a2f33 addss xmm0, xmm1
006a2f37 call 0x4228c0
006a2f3c comiss xmm0, dword ptr [0xb6a18c]
006a2f43 jbe 0x6a2f69
006a2f45 movss xmm1, dword ptr [0xb6a614]
006a2f4d divss xmm1, xmm0
006a2f51 movaps xmm0, xmm1
006a2f54 mulss xmm0, dword ptr [ebp - 0x18]
006a2f59 movss dword ptr [ebp - 0x18], xmm0
006a2f5e movss xmm0, dword ptr [ebp - 0x34]
006a2f63 mulss xmm0, xmm1
006a2f67 jmp 0x6a2f6e
006a2f69 movss xmm0, dword ptr [ebp - 0x34]
006a2f6e movss xmm1, dword ptr [ebp - 0x28]
006a2f73 mulss xmm0, dword ptr [edi + 0x74]
006a2f78 mulss xmm1, dword ptr [ebp - 0x18]
006a2f7d addss xmm0, xmm1
006a2f81 comiss xmm0, dword ptr [edi + 0x78]
006a2f85 jbe 0x6a3006
006a2f87 call 0x6c3d90
006a2f8c mov ecx, dword ptr [ebx + 8]
006a2f8f push 0
006a2f91 push 0xbeabf4
006a2f96 push 0xbeab18
006a2f9b movss xmm0, dword ptr [ecx]
006a2f9f addss xmm0, dword ptr [edi + 0x60]
006a2fa4 push 0
006a2fa6 push eax
006a2fa7 push 0
006a2fa9 push dword ptr [ebp - 0x14]
006a2fac lea eax, [ebp - 0x38]
006a2faf movss dword ptr [ebp - 0x40], xmm0
006a2fb4 movss xmm0, dword ptr [edi + 0x64]
006a2fb9 addss xmm0, dword ptr [ecx + 4]
006a2fbe mov ecx, dword ptr [0xbfd65c]
006a2fc4 push eax
006a2fc5 lea eax, [ebp - 0x40]
006a2fc8 push eax
006a2fc9 push dword ptr [edi + 0x94]
006a2fcf movss dword ptr [ebp - 0x3c], xmm0
006a2fd4 push 9
006a2fd6 call 0x422e20
006a2fdb push eax
006a2fdc call 0x9ec34c
006a2fe1 add esp, 0x14
006a2fe4 mov dword ptr [ebp - 0x28], eax
006a2fe7 cmp esi, dword ptr [ebp - 0x44]
006a2fea je 0x6a2ff6
006a2fec mov dword ptr [esi], eax
006a2fee add esi, 4
006a2ff1 mov dword ptr [ebp - 0x48], esi
006a2ff4 jmp 0x6a3006
006a2ff6 lea eax, [ebp - 0x28]
006a2ff9 push eax
006a2ffa push esi
006a2ffb lea ecx, [ebp - 0x4c]
006a2ffe call 0x426fb0
006a3003 mov esi, dword ptr [ebp - 0x48]
006a3006 sub dword ptr [ebp - 0x20], 1
006a300a movss xmm1, dword ptr [ebp - 0x24]
006a300f movss xmm2, dword ptr [ebp - 0x2c]
006a3014 jne 0x6a2ec0
006a301a jmp 0x6a301f
006a301c mov edi, dword ptr [ebx + 0x14]
006a301f mov edx, esi
006a3021 xor ecx, ecx
006a3023 sub edx, dword ptr [ebp - 0x4c]
006a3026 sar edx, 2
006a3029 mov dword ptr [ebp - 0x24], ecx
006a302c mov dword ptr [ebp - 0x1c], edx
006a302f test edx, edx
006a3031 je 0x6a3059
006a3033 mov eax, dword ptr [ebp - 0x4c]
006a3036 cmp dword ptr [eax + ecx*4], 0
006a303a jne 0x6a3051
006a303c push 0xb49240
006a3041 push 3
006a3043 call 0x95e330
006a3048 mov edx, dword ptr [ebp - 0x1c]
006a304b add esp, 8
006a304e mov ecx, dword ptr [ebp - 0x24]
006a3051 inc ecx
006a3052 mov dword ptr [ebp - 0x24], ecx
006a3055 cmp ecx, edx
006a3057 jb 0x6a3033
006a3059 cmp byte ptr [edi + 0x98], 0
006a3060 jne 0x6a3159
006a3066 mov eax, dword ptr [ebx + 0x10]
006a3069 cmp eax, 6
006a306c je 0x6a30c2
006a306e cmp eax, 7
006a3071 je 0x6a30c2
006a3073 cmp eax, 8
006a3076 je 0x6a30c2
006a3078 cmp eax, 9
006a307b je 0x6a30c2
006a307d test edx, edx
006a307f je 0x6a30b8
006a3081 xor esi, esi
006a3083 nop dword ptr [eax]
006a3087 nop word ptr [eax + eax]
006a3090 mov ecx, dword ptr [ebp - 0x4c]
006a3093 mov eax, dword ptr [ecx + esi*4]
006a3096 mov dword ptr [eax + 0x364], 0xc0400000
006a30a0 mov eax, dword ptr [ecx + esi*4]
006a30a3 inc esi
006a30a4 mov dword ptr [eax + 0x368], 0x3dcccccd
006a30ae cmp esi, edx
006a30b0 jb 0x6a3090
006a30b2 mov esi, dword ptr [ebp - 0x48]
006a30b5 mov eax, dword ptr [ebx + 0x10]
006a30b8 cmp eax, 2
006a30bb je 0x6a30cb
006a30bd cmp eax, 4
006a30c0 je 0x6a30cb
006a30c2 cmp eax, 5
006a30c5 jne 0x6a3159
006a30cb test edx, edx
006a30cd je 0x6a338d
006a30d3 movss xmm3, dword ptr [0xb6a434]
006a30db xor esi, esi
006a30dd movss xmm4, dword ptr [0xb6a670]
006a30e5 movss xmm5, dword ptr [0xb6a614]
006a30ed mov ecx, dword ptr [ebp - 0x14]
006a30f0 mov eax, dword ptr [ebp - 0x4c]
006a30f3 mov eax, dword ptr [eax + esi*4]
006a30f6 inc esi
006a30f7 movss xmm0, dword ptr [eax + 0x364]
006a30ff subss xmm0, xmm5
006a3103 movss dword ptr [eax + 0x364], xmm0
006a310b movss xmm0, dword ptr [eax + 0x2b8]
006a3113 movss xmm1, dword ptr [ecx + 0x2b8]
006a311b movss xmm2, dword ptr [eax + 0x2bc]
006a3123 mulss xmm0, xmm4
006a3127 mulss xmm1, xmm3
006a312b mulss xmm2, xmm4
006a312f addss xmm1, xmm0
006a3133 movss xmm0, dword ptr [ecx + 0x2bc]
006a313b mulss xmm0, xmm3
006a313f movss dword ptr [eax + 0x2b8], xmm1
006a3147 addss xmm2, xmm0
006a314b movss dword ptr [eax + 0x2bc], xmm2
006a3153 cmp esi, edx
006a3155 jb 0x6a30f0
006a3157 jmp 0x6a3169
006a3159 test edx, edx
006a315b je 0x6a338d
006a3161 movss xmm5, dword ptr [0xb6a614]
006a3169 xor edx, edx
006a316b mov dword ptr [ebp - 0x18], edx
006a316e nop 
006a3170 mov ecx, dword ptr [ebp - 0x4c]
006a3173 xorps xmm1, xmm1
006a3176 movss xmm0, dword ptr [edi + 4]
006a317b mov ecx, dword ptr [ecx + edx*4]
006a317e addss xmm0, dword ptr [ecx + 0x360]
006a3186 movss dword ptr [ecx + 0x360], xmm0
006a318e movss xmm0, dword ptr [edi + 8]
006a3193 addss xmm0, dword ptr [ecx + 0x364]
006a319b movss dword ptr [ecx + 0x364], xmm0
006a31a3 movss xmm0, dword ptr [ecx + 0x368]
006a31ab addss xmm0, dword ptr [edi + 0xc]
006a31b0 movss dword ptr [ecx + 0x368], xmm0
006a31b8 mov eax, dword ptr [edi + 0x14]
006a31bb mov dword ptr [ecx + 0x370], eax
006a31c1 movss xmm0, dword ptr [edi + 0x9c]
006a31c9 comiss xmm1, xmm0
006a31cc jbe 0x6a31ed
006a31ce movss xmm0, dword ptr [edi + 0x14]
006a31d3 cvtps2pd xmm0, xmm0
006a31d6 comisd xmm0, xmmword ptr [0xb6a788]
006a31de jbe 0x6a31ea
006a31e0 movss xmm0, dword ptr [0xb6a7b0]
006a31e8 jmp 0x6a31ed
006a31ea movaps xmm0, xmm5
006a31ed mov eax, dword ptr [ebp - 0x4c]
006a31f0 mov ecx, dword ptr [eax + edx*4]
006a31f3 push ecx
006a31f4 movss dword ptr [esp], xmm0
006a31f9 mov eax, dword ptr [ecx]
006a31fb call dword ptr [eax + 0x3c]
006a31fe mov edx, dword ptr [ebp - 0x18]
006a3201 mov eax, dword ptr [ebp - 0x4c]
006a3204 movss xmm1, dword ptr [edi + 0x10]
006a3209 movaps xmm0, xmm1
006a320c push 1
006a320e mov ecx, dword ptr [eax + edx*4]
006a3211 push 0
006a3213 push 0xff
006a3218 push -1
006a321a mulss xmm0, dword ptr [ecx + 0x2b8]
006a3222 mulss xmm1, dword ptr [ecx + 0x2bc]
006a322a movss dword ptr [ecx + 0x2b8], xmm0
006a3232 movss dword ptr [ecx + 0x2bc], xmm1
006a323a mov eax, dword ptr [edi + 0x58]
006a323d or dword ptr [ecx + 0x388], eax
006a3243 mov eax, dword ptr [edi + 0x5c]
006a3246 or dword ptr [ecx + 0x38c], eax
006a324c mov eax, dword ptr [ebp - 0x4c]
006a324f mov ecx, dword ptr [eax + edx*4]
006a3252 lea edx, [edi + 0x2c]
006a3255 push edx
006a3256 mov eax, dword ptr [ecx]
006a3258 call dword ptr [eax + 0x38]
006a325b mov edx, dword ptr [ebp - 0x18]
006a325e movss xmm0, dword ptr [edi + 0x68]
006a3263 movss xmm1, dword ptr [edi + 0x6c]
006a3268 mov eax, dword ptr [ebp - 0x4c]
006a326b mov ecx, dword ptr [eax + edx*4]
006a326e movss dword ptr [ecx + 0x28c], xmm0
006a3276 movss dword ptr [ecx + 0x290], xmm1
006a327e mov eax, dword ptr [edi + 0x1c]
006a3281 mov dword ptr [ecx + 0x374], eax
006a3287 mov eax, dword ptr [ebp - 0x4c]
006a328a mov ecx, dword ptr [eax + edx*4]
006a328d mov eax, dword ptr [edi + 0x20]
006a3290 mov dword ptr [ecx + 0x378], eax
006a3296 mov eax, dword ptr [ebp - 0x4c]
006a3299 mov ecx, dword ptr [eax + edx*4]
006a329c mov eax, dword ptr [edi + 0x24]
006a329f mov dword ptr [ecx + 0x37c], eax
006a32a5 mov eax, dword ptr [ebp - 0x4c]
006a32a8 mov ecx, dword ptr [eax + edx*4]
006a32ab mov eax, dword ptr [edi + 0x7c]
006a32ae mov dword ptr [ecx + 0x394], eax
006a32b4 mov eax, dword ptr [ebp - 0x4c]
006a32b7 mov ecx, dword ptr [eax + edx*4]
006a32ba mov eax, dword ptr [edi + 0x80]
006a32c0 or dword ptr [ecx + 0x398], eax
006a32c6 mov eax, dword ptr [edi + 0x84]
006a32cc or dword ptr [ecx + 0x39c], eax
006a32d2 mov eax, dword ptr [ebp - 0x4c]
006a32d5 mov ecx, dword ptr [eax + edx*4]
006a32d8 mov eax, dword ptr [edi + 0x88]
006a32de mov dword ptr [ecx + 0x3a0], eax
006a32e4 mov eax, dword ptr [ebp - 0x4c]
006a32e7 mov ecx, dword ptr [eax + edx*4]
006a32ea mov eax, dword ptr [edi + 0x8c]
006a32f0 mov dword ptr [ecx + 0x3a4], eax
006a32f6 mov ecx, dword ptr [ebp - 0x4c]
006a32f9 movss xmm0, dword ptr [edi + 0x90]
006a3301 subss xmm0, dword ptr [edi + 0x64]
006a3306 mov eax, dword ptr [ecx + edx*4]
006a3309 movss dword ptr [eax + 0x2b0], xmm0
006a3311 mov eax, dword ptr [ecx + edx*4]
006a3314 movss xmm0, dword ptr [0xb6af28]
006a331c mov dword ptr [ebp - 0x18], eax
006a331f comiss xmm0, dword ptr [eax + 0x360]
006a3326 jbe 0x6a334e
006a3328 mov dword ptr [ebp - 0x18], eax
006a332b mov eax, dword ptr [eax + 0x388]
006a3331 and eax, 0x20000
006a3336 or eax, 0
006a3339 jne 0x6a334e
006a333b mov eax, dword ptr [ecx + edx*4]
006a333e mov dword ptr [eax + 0x180], 0
006a3348 mov eax, dword ptr [ecx + edx*4]
006a334b mov dword ptr [ebp - 0x18], eax
006a334e mov ecx, dword ptr [ebp - 0x18]
006a3351 inc edx
006a3352 mov eax, dword ptr [edi + 0xa0]
006a3358 movss xmm5, dword ptr [0xb6a614]
006a3360 mov dword ptr [ebp - 0x18], edx
006a3363 mov dword ptr [ecx + 0x3b8], eax
006a3369 cmp edx, dword ptr [ebp - 0x1c]
006a336c jb 0x6a3170
006a3372 mov esi, dword ptr [ebp - 0x14]
006a3375 xor edi, edi
006a3377 mov eax, dword ptr [ebp - 0x4c]
006a337a mov ecx, esi
006a337c push dword ptr [eax + edi*4]
006a337f call 0x6a19c0
006a3384 inc edi
006a3385 cmp edi, dword ptr [ebp - 0x1c]
006a3388 jb 0x6a3377
006a338a mov esi, dword ptr [ebp - 0x48]
006a338d cmp dword ptr [ebp - 0x4c], esi
006a3390 jne 0x6a3396
006a3392 xor esi, esi
006a3394 jmp 0x6a339b
006a3396 mov eax, dword ptr [ebp - 0x4c]
006a3399 mov esi, dword ptr [eax]
006a339b mov edx, dword ptr [ebp - 0x4c]
006a339e test edx, edx
006a33a0 je 0x6a33d4
006a33a2 mov ecx, dword ptr [ebp - 0x44]
006a33a5 mov eax, edx
006a33a7 sub ecx, edx
006a33a9 and ecx, 0xfffffffc
006a33ac cmp ecx, 0x1000
006a33b2 jb 0x6a33ca
006a33b4 mov edx, dword ptr [edx - 4]
006a33b7 add ecx, 0x23
006a33ba sub eax, edx
006a33bc add eax, -4
006a33bf cmp eax, 0x1f
006a33c2 jbe 0x6a33ca
006a33c4 call dword ptr [0xa065ac]
006a33ca push ecx
006a33cb push edx
006a33cc call 0x9eb08e
006a33d1 add esp, 8
006a33d4 mov eax, esi
006a33d6 mov ecx, dword ptr [ebp - 0xc]
006a33d9 mov dword ptr fs:[0], ecx
006a33e0 pop ecx
006a33e1 pop edi
006a33e2 pop esi
006a33e3 mov esp, ebp
006a33e5 pop ebp
006a33e6 mov esp, ebx
006a33e8 pop ebx
006a33e9 ret 0x10
