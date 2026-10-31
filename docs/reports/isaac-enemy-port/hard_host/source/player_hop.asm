0074c275 movss xmm0, dword ptr [0xb6a350]
0074c27d xorps xmm2, xmm2
0074c280 movss xmm4, dword ptr [0xb6a4c4]
0074c288 test al, al
0074c28a je 0x74c29b
0074c28c mov dword ptr [edi + 0x1d88], 0
0074c296 jmp 0x74c49e
0074c29b comiss xmm2, dword ptr [edi + 0x2a8]
0074c2a2 ja 0x74c2b1
0074c2a4 comiss xmm2, dword ptr [edi + 0x1d88]
0074c2ab jbe 0x74c49e
0074c2b1 cmp byte ptr [edi + 0x14b4], 0
0074c2b8 jne 0x74c2c3
0074c2ba cmp dword ptr [edi + 0x17c], 5
0074c2c1 je 0x74c2f6
0074c2c3 push 0x4000000
0074c2c8 push 0
0074c2ca mov ecx, edi
0074c2cc call 0x4122f0
0074c2d1 test al, al
0074c2d3 jne 0x74c2ee
0074c2d5 mov dword ptr [edi + 0x2a8], 0
0074c2df mov dword ptr [edi + 0x1d88], 0
0074c2e9 jmp 0x74c493
0074c2ee movss xmm0, dword ptr [0xb6a350]
0074c2f6 movss xmm1, dword ptr [edi + 0x1e84]
0074c2fe movss xmm2, dword ptr [edi + 0x1d88]
0074c306 subss xmm1, xmm2
0074c30a comiss xmm1, dword ptr [0xb6a18c]
0074c311 movss dword ptr [edi + 0x1e84], xmm1
0074c319 jbe 0x74c333
0074c31b mulss xmm1, xmm0
0074c31f movss xmm0, dword ptr [edi + 0x1e88]
0074c327 subss xmm0, xmm1
0074c32b movss dword ptr [edi + 0x1e88], xmm0
0074c333 addss xmm2, dword ptr [edi + 0x2a8]
0074c33b push 0x4000000
0074c340 push 0
0074c342 mov ecx, edi
0074c344 movss dword ptr [edi + 0x2a8], xmm2
0074c34c call 0x4122f0
0074c351 movss xmm0, dword ptr [edi + 0x1d88]
0074c359 xorps xmm2, xmm2
0074c35c movss xmm4, dword ptr [0xb6a4c4]
0074c364 test al, al
0074c366 je 0x74c3b1
0074c368 addss xmm0, xmm4
0074c36c comiss xmm2, xmm0
0074c36f movss dword ptr [edi + 0x1d88], xmm0
0074c377 ja 0x74c3a4
0074c379 movss xmm0, dword ptr [0xb6aefc]
0074c381 comiss xmm0, dword ptr [edi + 0x2a8]
0074c388 ja 0x74c3a4
0074c38a xor eax, eax
0074c38c cmp byte ptr [edi + 0x14b4], al
0074c392 sete al
0074c395 lea eax, [eax*2 + 3]
0074c39c mov dword ptr [edi + 0x17c], eax
0074c3a2 jmp 0x74c3c1
0074c3a4 mov eax, 3
0074c3a9 mov dword ptr [edi + 0x17c], eax
0074c3af jmp 0x74c3c1
0074c3b1 addss xmm0, dword ptr [0xb6a64c]
0074c3b9 movss dword ptr [edi + 0x1d88], xmm0
0074c3c1 movss xmm0, dword ptr [edi + 0x2a8]
0074c3c9 comiss xmm0, xmm2
0074c3cc jbe 0x74c49e
0074c3d2 push 0x4000000
0074c3d7 push 0
0074c3d9 mov ecx, edi
0074c3db mov dword ptr [edi + 0x2a8], 0
0074c3e5 mov dword ptr [edi + 0x1d88], 0
