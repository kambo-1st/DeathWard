006c1b65 cmp eax, 0x45
006c1b68 jne 0x6c1dba
006c1b6e push 1
006c1b70 lea eax, [ebp - 0x100]
006c1b76 mov ecx, esi
006c1b78 push eax
006c1b79 call 0x6b1cc0
006c1b7e push 0x17
006c1b80 mov dword ptr [ebp - 4], 5
006c1b87 lea ecx, [ebp - 0x50]
006c1b8a push dword ptr [esi + 0x344]
006c1b90 call 0x7a7cd0
006c1b95 mov eax, dword ptr [ebp - 0xf4]
006c1b9b lea ecx, [ebp - 0x100]
006c1ba1 mov dword ptr [ebp - 0xac], eax
006c1ba7 mov dword ptr [ebp - 0xe4], eax
006c1bad mov eax, dword ptr [ebp - 0x100]
006c1bb3 mov dword ptr [ebp - 0x8c], eax
006c1bb9 mov dword ptr [ebp - 0xec], eax
006c1bbf lea eax, [ebp - 0xe0]
006c1bc5 push eax
006c1bc6 mov dword ptr [ebp - 0xe8], 0
006c1bd0 call 0x5ee9e0
006c1bd5 mov ecx, dword ptr [ebp - 0xac]
006c1bdb cmp ecx, dword ptr [eax + 8]
006c1bde je 0x6c1d89
006c1be4 mov edx, dword ptr [ebp - 0x8c]
006c1bea nop word ptr [eax + eax]
006c1bf0 test edx, edx
006c1bf2 je 0x6c1bf8
006c1bf4 mov eax, dword ptr [edx]
006c1bf6 jmp 0x6c1bfa
006c1bf8 xor eax, eax
006c1bfa mov ecx, dword ptr [eax + 8]
006c1bfd mov eax, dword ptr [eax + 4]
006c1c00 dec ecx
006c1c01 and ecx, dword ptr [ebp - 0xac]
006c1c07 mov eax, dword ptr [eax + ecx*4]
006c1c0a cmp dword ptr [eax], 3
006c1c0d jne 0x6c1c82
006c1c0f test edx, edx
006c1c11 je 0x6c1c17
006c1c13 mov eax, dword ptr [edx]
006c1c15 jmp 0x6c1c19
006c1c17 xor eax, eax
006c1c19 mov ecx, dword ptr [eax + 8]
006c1c1c mov eax, dword ptr [eax + 4]
006c1c1f dec ecx
006c1c20 and ecx, dword ptr [ebp - 0xac]
006c1c26 mov eax, dword ptr [eax + ecx*4]
006c1c29 cmp dword ptr [eax + 4], 0x2b
006c1c2d jne 0x6c1c46
006c1c2f push 0
006c1c31 lea eax, [esi + 0x294]
006c1c37 mov ecx, edi
006c1c39 push eax
006c1c3a push 1
006c1c3c call 0x725cc0
006c1c41 jmp 0x6c1d42
006c1c46 test edx, edx
006c1c48 je 0x6c1c4e
006c1c4a mov eax, dword ptr [edx]
006c1c4c jmp 0x6c1c50
006c1c4e xor eax, eax
006c1c50 mov ecx, dword ptr [eax + 8]
006c1c53 mov eax, dword ptr [eax + 4]
006c1c56 dec ecx
006c1c57 and ecx, dword ptr [ebp - 0xac]
006c1c5d mov eax, dword ptr [eax + ecx*4]
006c1c60 cmp dword ptr [eax + 4], 0x49
006c1c64 jne 0x6c1d42
006c1c6a push 0xc02fec
006c1c6f lea eax, [esi + 0x294]
006c1c75 mov ecx, edi
006c1c77 push eax
006c1c78 call 0x783600
006c1c7d jmp 0x6c1d42
006c1c82 lea ecx, [ebp - 0x50]
006c1c85 call 0x7a7db0
006c1c8a fmul dword ptr [0xb6a864]
006c1c90 lea ecx, [ebp - 0x50]
006c1c93 fadd dword ptr [0xb6a7b0]
006c1c99 fstp dword ptr [ebp - 0x14]
006c1c9c call 0x7a7e20
006c1ca1 mov edx, eax
006c1ca3 lea ecx, [ebp - 0x30]
006c1ca6 call 0x6592f0
006c1cab movss xmm1, dword ptr [ebp - 0x14]
006c1cb0 lea ecx, [ebp - 0x50]
006c1cb3 movaps xmm0, xmm1
006c1cb6 mulss xmm0, dword ptr [eax]
006c1cba mulss xmm1, dword ptr [eax + 4]
006c1cbf movss dword ptr [ebp - 0x84], xmm0
006c1cc7 movss dword ptr [ebp - 0x80], xmm1
006c1ccc call 0x7a7e20
006c1cd1 mov edx, eax
006c1cd3 lea ecx, [ebp - 0xd4]
006c1cd9 call 0x6592f0
006c1cde movss xmm1, dword ptr [eax]
006c1ce2 movss xmm0, dword ptr [eax + 4]
006c1ce7 addss xmm1, dword ptr [esi + 0x294]
006c1cef addss xmm0, dword ptr [esi + 0x298]
006c1cf7 mov eax, dword ptr [ebp - 0x8c]
006c1cfd movss dword ptr [ebp - 0xa0], xmm1
006c1d05 movss dword ptr [ebp - 0x9c], xmm0
006c1d0d test eax, eax
006c1d0f je 0x6c1d15
006c1d11 mov eax, dword ptr [eax]
006c1d13 jmp 0x6c1d17
006c1d15 xor eax, eax
006c1d17 mov ecx, dword ptr [eax + 8]
006c1d1a lea edx, [ebp - 0x84]
006c1d20 mov eax, dword ptr [eax + 4]
006c1d23 dec ecx
006c1d24 and ecx, dword ptr [ebp - 0xac]
006c1d2a push esi
006c1d2b push edx
006c1d2c lea edx, [ebp - 0xa0]
006c1d32 mov ecx, dword ptr [eax + ecx*4]
006c1d35 push edx
006c1d36 call 0x7f86d0
006c1d3b mov ecx, eax
006c1d3d mov edx, dword ptr [eax]
006c1d3f call dword ptr [edx + 0xc]
006c1d42 push ecx
006c1d43 lea eax, [ebp - 0xc0]
006c1d49 push eax
006c1d4a lea ecx, [ebp - 0xec]
006c1d50 call 0x6b14d0
006c1d55 lea eax, [ebp - 0xe0]
006c1d5b push eax
006c1d5c lea ecx, [ebp - 0x100]
006c1d62 call 0x5ee9e0
006c1d67 mov ecx, dword ptr [ebp - 0xe4]
006c1d6d mov dword ptr [ebp - 0xac], ecx
006c1d73 cmp ecx, dword ptr [eax + 8]
006c1d76 je 0x6c1d89
006c1d78 mov edx, dword ptr [ebp - 0xec]
006c1d7e mov dword ptr [ebp - 0x8c], edx
006c1d84 jmp 0x6c1bf0
006c1d89 mov eax, dword ptr [0xbfd65c]
006c1d8e lea ecx, [ebp - 0x100]
006c1d94 mov byte ptr [ebp - 0x6d], 1
006c1d98 mov byte ptr [ebp - 0x6e], 1
006c1d9c mov eax, dword ptr [eax + 0x18190]
006c1da2 mov dword ptr [ebp - 4], 0xffffffff
006c1da9 mov byte ptr [eax + 0x7778], 1
006c1db0 call 0x68f5b0
006c1db5 jmp 0x6c02a2
