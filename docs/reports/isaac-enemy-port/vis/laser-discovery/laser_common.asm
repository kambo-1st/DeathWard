008c59e0 push ebp
008c59e1 mov ebp, esp
008c59e3 push ecx
008c59e4 movss xmm0, dword ptr [ecx + 0x2b0]
008c59ec sub esp, 8
008c59ef addss xmm0, dword ptr [ecx + 0x298]
008c59f7 mulss xmm0, dword ptr [0xb6aafc]
008c59ff addss xmm0, dword ptr [0xb6ad3c]
008c5a07 addss xmm0, dword ptr [0xb6a480]
008c5a0f movss dword ptr [ebp - 4], xmm0
008c5a14 fld dword ptr [ebp - 4]
008c5a17 fstp qword ptr [esp]
008c5a1a call 0x9ec3b2
008c5a1f fstp dword ptr [ebp - 4]
008c5a22 fld dword ptr [ebp - 4]
008c5a25 add esp, 8
008c5a28 fstp dword ptr [ebp - 4]
008c5a2b movss xmm0, dword ptr [ebp - 4]
008c5a30 maxss xmm0, dword ptr [0xb6ad38]
008c5a38 call 0x9eb8a0
008c5a3d mov esp, ebp
008c5a3f pop ebp
008c5a40 ret 
008c5a41 int3 
008c5a42 int3 
008c5a43 int3 
008c5a44 int3 
008c5a45 int3 
008c5a46 int3 
008c5a47 int3 
008c5a48 int3 
008c5a49 int3 
008c5a4a int3 
008c5a4b int3 
008c5a4c int3 
008c5a4d int3 
008c5a4e int3 
008c5a4f int3 
008c5a50 mov edx, dword ptr [ecx + 0x314]
008c5a56 test edx, edx
008c5a58 je 0x8c5a7c
008c5a5a mov eax, dword ptr [edx + 0x28]
008c5a5d cmp eax, 2
008c5a60 jne 0x8c5a6b
008c5a62 cmp dword ptr [edx + 0x34], 1
008c5a66 jne 0x8c5a7c
008c5a68 mov al, 1
008c5a6a ret 
008c5a6b cmp eax, 0x3e8
008c5a70 je 0x8c5a62
008c5a72 cmp eax, 1
008c5a75 je 0x8c5a68
008c5a77 cmp eax, 3
008c5a7a je 0x8c5a68
008c5a7c mov eax, dword ptr [ecx + 0x34]
008c5a7f cmp eax, 1
008c5a82 je 0x8c5a68
008c5a84 cmp eax, 3
008c5a87 je 0x8c5a68
008c5a89 xor al, al
008c5a8b ret 
008c5a8c int3 
008c5a8d int3 
008c5a8e int3 
008c5a8f int3 
008c5a90 push ebp
008c5a91 mov ebp, esp
008c5a93 push ecx
008c5a94 push ebx
008c5a95 push esi
008c5a96 push edi
008c5a97 mov edi, dword ptr [ebp + 8]
008c5a9a mov dword ptr [ebp - 4], ecx
008c5a9d mov esi, dword ptr [edi + 0x28]
008c5aa0 cmp esi, 0x11
008c5aa3 je 0x8c5bc0
008c5aa9 mov edx, dword ptr [ecx + 0x314]
008c5aaf test edx, edx
008c5ab1 je 0x8c5acd
008c5ab3 mov eax, dword ptr [edx + 0x28]
008c5ab6 mov dword ptr [ebp + 8], eax
008c5ab9 mov eax, dword ptr [edx + 0x160]
008c5abf and eax, 0x100
008c5ac4 or eax, 0
008c5ac7 je 0x8c5ad4
008c5ac9 mov bh, 1
008c5acb jmp 0x8c5ad6
008c5acd mov dword ptr [ebp + 8], 0
008c5ad4 xor bh, bh
008c5ad6 cmp esi, 3
008c5ad9 jne 0x8c5b03
008c5adb mov eax, dword ptr [edi + 0x2c]
008c5ade cmp eax, 0x3e
008c5ae1 je 0x8c5aff
008c5ae3 cmp eax, 0x43
008c5ae6 je 0x8c5aff
008c5ae8 cmp eax, 0xd3
008c5aed je 0x8c5aff
008c5aef cmp eax, 0xce
008c5af4 jne 0x8c5b03
008c5af6 cmp dword ptr [edi + 0x30], 0x1ab
008c5afd jne 0x8c5b03
008c5aff mov bl, 1
008c5b01 jmp 0x8c5b05
008c5b03 xor bl, bl
008c5b05 cmp edi, edx
008c5b07 je 0x8c5b27
008c5b09 cmp byte ptr [edi + 0x16b], 0
008c5b10 jne 0x8c5b27
008c5b12 cmp dword ptr [edi + 0x180], 0
008c5b19 je 0x8c5b27
008c5b1b xorps xmm0, xmm0
008c5b1e comiss xmm0, dword ptr [edi + 0x2dc]
008c5b25 jb 0x8c5b2f
008c5b27 test bl, bl
008c5b29 je 0x8c5bc0
008c5b2f cmp dword ptr [ebp + 8], esi
008c5b32 jne 0x8c5b3c
008c5b34 test bh, bh
008c5b36 je 0x8c5bc0
008c5b3c mov eax, dword ptr [ecx + 0x47c]
008c5b42 test eax, eax
008c5b44 je 0x8c5b5e
008c5b46 mov ecx, dword ptr [eax + 0x47c]
008c5b4c test ecx, ecx
008c5b4e je 0x8c5b57
008c5b50 call 0x8c5980
008c5b55 jmp 0x8c5b64
008c5b57 add eax, 0x470
008c5b5c jmp 0x8c5b64
008c5b5e lea eax, [ecx + 0x470]
008c5b64 push edi
008c5b65 mov ecx, eax
008c5b67 call 0x422d00
008c5b6c test al, al
008c5b6e jne 0x8c5bc0
008c5b70 mov ecx, dword ptr [ebp - 4]
008c5b73 call 0x8c5a50
008c5b78 test al, al
008c5b7a je 0x8c5bcb
008c5b7c cmp dword ptr [ebp + 8], 3
008c5b80 jne 0x8c5b86
008c5b82 test bh, bh
008c5b84 jne 0x8c5bcb
008c5b86 lea eax, [esi - 0xa]
008c5b89 cmp eax, 0x3dd
008c5b8e ja 0x8c5ba2
008c5b90 push 0
008c5b92 push 0x20000000
008c5b97 mov ecx, edi
008c5b99 call 0x4122f0
008c5b9e test al, al
008c5ba0 je 0x8c5bde
008c5ba2 cmp dword ptr [edi + 0x180], 0
008c5ba9 je 0x8c5bc0
008c5bab cmp esi, 0x21
008c5bae je 0x8c5bde
008c5bb0 cmp esi, 0x124
008c5bb6 je 0x8c5bde
008c5bb8 cmp esi, 0xf5
008c5bbe je 0x8c5bde
008c5bc0 xor al, al
008c5bc2 pop edi
008c5bc3 pop esi
008c5bc4 pop ebx
008c5bc5 mov esp, ebp
008c5bc7 pop ebp
008c5bc8 ret 4
008c5bcb cmp esi, 1
008c5bce je 0x8c5bde
008c5bd0 lea eax, [esi - 0xa]
008c5bd3 cmp eax, 0x3dd
008c5bd8 jbe 0x8c5bde
008c5bda test bl, bl
008c5bdc je 0x8c5bc0
008c5bde pop edi
008c5bdf pop esi
008c5be0 mov al, 1
008c5be2 pop ebx
008c5be3 mov esp, ebp
008c5be5 pop ebp
008c5be6 ret 4
008c5be9 int3 
008c5bea int3 
008c5beb int3 
008c5bec int3 
008c5bed int3 
008c5bee int3 
008c5bef int3 
008c5bf0 push ebp
008c5bf1 mov ebp, esp
008c5bf3 and esp, 0xfffffff8
008c5bf6 sub esp, 0x14
008c5bf9 push ebx
008c5bfa mov edx, ecx
008c5bfc movaps xmm0, xmm1
008c5bff push esi
008c5c00 push edi
008c5c01 movss dword ptr [esp + 0x10], xmm0
008c5c07 mov ebx, dword ptr [edx + 0x3d4]
008c5c0d mov edi, dword ptr [edx + 0x3d0]
008c5c13 sub ebx, edi
008c5c15 sar ebx, 3
008c5c18 mov dword ptr [esp + 0x14], edx
008c5c1c cmp ebx, 2
008c5c1f jae 0x8c5c7e
008c5c21 mov ecx, dword ptr [ebp + 8]
008c5c24 mov eax, dword ptr [edx + 0x294]
008c5c2a mov dword ptr [ecx], eax
008c5c2c mov eax, dword ptr [edx + 0x298]
008c5c32 mov dword ptr [ecx + 4], eax
008c5c35 movss xmm0, dword ptr [edx + 0x36c]
008c5c3d mulss xmm0, dword ptr [0xb6a230]
008c5c45 movss dword ptr [esp + 0x14], xmm0
008c5c4b call 0x411fe0
008c5c50 movss dword ptr [esp + 0x10], xmm0
008c5c56 movss xmm0, dword ptr [esp + 0x14]
008c5c5c call 0x412010
008c5c61 mov eax, dword ptr [ebp + 0xc]
008c5c64 movss xmm1, dword ptr [esp + 0x10]
008c5c6a movss dword ptr [eax], xmm1
008c5c6e movss dword ptr [eax + 4], xmm0
008c5c73 xor al, al
008c5c75 pop edi
008c5c76 pop esi
008c5c77 pop ebx
008c5c78 mov esp, ebp
008c5c7a pop ebp
008c5c7b ret 8
008c5c7e xorps xmm1, xmm1
008c5c81 comiss xmm1, xmm0
008c5c84 jb 0x8c5cd4
008c5c86 mov ecx, dword ptr [ebp + 8]
008c5c89 mov eax, dword ptr [edi]
008c5c8b mov dword ptr [ecx], eax
008c5c8d mov eax, dword ptr [edi + 4]
008c5c90 mov dword ptr [ecx + 4], eax
008c5c93 movss xmm1, dword ptr [edi + 8]
008c5c98 subss xmm1, dword ptr [edi]
008c5c9c movss xmm2, dword ptr [edi + 0xc]
008c5ca1 subss xmm2, dword ptr [edi + 4]
008c5ca6 movaps xmm0, xmm1
008c5ca9 movss dword ptr [esp + 0xc], xmm1
008c5caf mulss xmm0, xmm1
008c5cb3 movaps xmm1, xmm2
008c5cb6 movss dword ptr [esp + 0x10], xmm2
008c5cbc mulss xmm1, xmm2
008c5cc0 addss xmm0, xmm1
008c5cc4 call 0x4228c0
008c5cc9 movss xmm2, dword ptr [esp + 0xc]
008c5ccf jmp 0x8c5dc9
008c5cd4 fld dword ptr [esp + 0x10]
008c5cd8 push ecx
008c5cd9 fstp dword ptr [esp]
008c5cdc call 0x9ec36a
008c5ce1 add esp, 4
008c5ce4 test ax, ax
008c5ce7 jg 0x8c5d63
008c5ce9 lea eax, [ebx - 1]
008c5cec xorps xmm0, xmm0
008c5cef xor esi, esi
008c5cf1 movss dword ptr [esp + 0xc], xmm0
008c5cf7 test eax, eax
008c5cf9 je 0x8c5d63
008c5cfb nop dword ptr [eax + eax]
008c5d00 movss xmm1, dword ptr [edi + esi*8 + 0xc]
008c5d06 subss xmm1, dword ptr [edi + esi*8 + 4]
008c5d0c movss xmm2, dword ptr [edi + esi*8 + 8]
008c5d12 subss xmm2, dword ptr [edi + esi*8]
008c5d17 movaps xmm0, xmm1
008c5d1a movss dword ptr [esp + 0x1c], xmm1
008c5d20 mulss xmm0, xmm1
008c5d24 movaps xmm1, xmm2
008c5d27 movss dword ptr [esp + 0x18], xmm2
008c5d2d mulss xmm1, xmm2
008c5d31 addss xmm0, xmm1
008c5d35 call 0x4228c0
008c5d3a movaps xmm4, xmm0
008c5d3d movss xmm0, dword ptr [esp + 0xc]
008c5d43 movaps xmm1, xmm4
008c5d46 addss xmm1, xmm0
008c5d4a comiss xmm1, dword ptr [esp + 0x10]
008c5d4f ja 0x8c5df5
008c5d55 inc esi
008c5d56 movss dword ptr [esp + 0xc], xmm1
008c5d5c lea eax, [ebx - 1]
008c5d5f cmp esi, eax
008c5d61 jb 0x8c5d00
008c5d63 mov ecx, dword ptr [ebp + 8]
008c5d66 mov eax, dword ptr [edi + ebx*8 - 8]
008c5d6a mov dword ptr [ecx], eax
008c5d6c mov eax, dword ptr [edi + ebx*8 - 4]
008c5d70 mov dword ptr [ecx + 4], eax
008c5d73 mov eax, dword ptr [esp + 0x14]
008c5d77 mov ecx, dword ptr [eax + 0x3d4]
008c5d7d mov eax, dword ptr [eax + 0x3d0]
008c5d83 sub ecx, edi
008c5d85 sar ecx, 3
008c5d88 movss xmm1, dword ptr [eax + ecx*8 - 8]
008c5d8e subss xmm1, dword ptr [eax + ecx*8 - 0x10]
008c5d94 movss xmm2, dword ptr [eax + ecx*8 - 4]
008c5d9a subss xmm2, dword ptr [eax + ecx*8 - 0xc]
008c5da0 movaps xmm0, xmm1
008c5da3 movss dword ptr [esp + 0x14], xmm1
008c5da9 mulss xmm0, xmm1
008c5dad movaps xmm1, xmm2
008c5db0 movss dword ptr [esp + 0x10], xmm2
008c5db6 mulss xmm1, xmm2
008c5dba addss xmm0, xmm1
008c5dbe call 0x4228c0
008c5dc3 movss xmm2, dword ptr [esp + 0x14]
008c5dc9 comiss xmm0, dword ptr [0xb6a18c]
008c5dd0 jbe 0x8c5e5a
008c5dd6 movss xmm1, dword ptr [0xb6a614]
008c5dde divss xmm1, xmm0
008c5de2 movaps xmm0, xmm1
008c5de5 mulss xmm2, xmm0
008c5de9 movss xmm0, dword ptr [esp + 0x10]
008c5def mulss xmm0, xmm1
008c5df3 jmp 0x8c5e60
008c5df5 mov eax, dword ptr [esp + 0x14]
008c5df9 movss xmm2, dword ptr [esp + 0x18]
008c5dff movss xmm3, dword ptr [esp + 0x1c]
008c5e05 movss xmm1, dword ptr [eax + 0x4a8]
008c5e0d subss xmm1, xmm0
008c5e11 mov eax, dword ptr [ebp + 8]
008c5e14 movaps xmm0, xmm1
008c5e17 mulss xmm1, xmm3
008c5e1b mulss xmm0, xmm2
008c5e1f divss xmm1, xmm4
008c5e23 divss xmm0, xmm4
008c5e27 addss xmm1, dword ptr [edi + esi*8 + 4]
008c5e2d addss xmm0, dword ptr [edi + esi*8]
008c5e32 divss xmm2, xmm4
008c5e36 divss xmm3, xmm4
008c5e3a movss dword ptr [eax], xmm0
008c5e3e movss dword ptr [eax + 4], xmm1
008c5e43 mov eax, dword ptr [ebp + 0xc]
008c5e46 movss dword ptr [eax], xmm2
008c5e4a movss dword ptr [eax + 4], xmm3
008c5e4f mov al, 1
008c5e51 pop edi
008c5e52 pop esi
008c5e53 pop ebx
008c5e54 mov esp, ebp
008c5e56 pop ebp
008c5e57 ret 8
008c5e5a movss xmm0, dword ptr [esp + 0x10]
008c5e60 mov eax, dword ptr [ebp + 0xc]
008c5e63 pop edi
008c5e64 pop esi
008c5e65 pop ebx
008c5e66 movss dword ptr [eax], xmm2
008c5e6a movss dword ptr [eax + 4], xmm0
008c5e6f xor al, al
008c5e71 mov esp, ebp
008c5e73 pop ebp
008c5e74 ret 8
008c5e77 int3 
008c5e78 int3 
008c5e79 int3 
008c5e7a int3 
008c5e7b int3 
008c5e7c int3 
008c5e7d int3 
008c5e7e int3 
008c5e7f int3 
008c5e80 push ebp
008c5e81 mov ebp, esp
008c5e83 and esp, 0xfffffff0
008c5e86 sub esp, 0x98
008c5e8c mov eax, dword ptr [0xbaa3b4]
008c5e91 xor eax, esp
008c5e93 mov dword ptr [esp + 0x94], eax
008c5e9a mov eax, dword ptr [ebp + 8]
008c5e9d movss xmm4, dword ptr [0xb6a974]
008c5ea5 movss xmm3, dword ptr [0xb6a8cc]
008c5ead push esi
008c5eae push edi
008c5eaf mov edi, ecx
008c5eb1 mov dword ptr [esp + 0x4c], eax
008c5eb5 mov dword ptr [esp + 0x64], edi
008c5eb9 mov ecx, dword ptr [edi + 0x378]
008c5ebf mov eax, dword ptr [edi + 0x37c]
008c5ec5 mov edx, dword ptr [edi + 0x380]
008c5ecb mov esi, dword ptr [edi + 0x384]
008c5ed1 and ecx, dword ptr [0xbc4ca0]
008c5ed7 and eax, dword ptr [0xbc4ca4]
008c5edd and edx, dword ptr [0xbc4ca8]
008c5ee3 and esi, dword ptr [0xbc4cac]
008c5ee9 or ecx, eax
008c5eeb jne 0x8c5ef5
008c5eed or edx, esi
008c5eef je 0x8c6a19
008c5ef5 cmp byte ptr [edi + 0x3ac], 0
008c5efc jne 0x8c5f1b
008c5efe xorps xmm2, xmm2
008c5f01 movaps xmm1, xmm3
008c5f04 mov ecx, edi
008c5f06 call 0x6847e0
008c5f0b test eax, eax
008c5f0d je 0x8c6a11
008c5f13 movss xmm4, dword ptr [0xb6a974]
008c5f1b mov eax, dword ptr [edi + 0x30]
008c5f1e movss xmm3, dword ptr [0xb6aa0c]
008c5f26 cmp eax, 1
008c5f29 je 0x8c5f3a
008c5f2b cmp eax, 2
008c5f2e je 0x8c5f35
008c5f30 cmp eax, 3
008c5f33 jne 0x8c5f61
008c5f35 cmp eax, 1
008c5f38 jne 0x8c5f4c
008c5f3a movss xmm0, dword ptr [edi + 0x2fc]
008c5f42 comiss xmm0, xmm3
008c5f45 jae 0x8c5f61
008c5f47 jmp 0x8c6a11
008c5f4c movss xmm0, dword ptr [edi + 0x2fc]
008c5f54 comiss xmm0, dword ptr [0xb6a8f4]
008c5f5b jb 0x8c6a11
008c5f61 movss xmm1, dword ptr [edi + 0x430]
008c5f69 movss xmm0, dword ptr [0xb6a614]
008c5f71 comiss xmm0, xmm1
008c5f74 movss xmm2, dword ptr [0xb6aa8c]
008c5f7c jbe 0x8c5f88
008c5f7e mulss xmm1, xmm2
008c5f82 maxss xmm1, xmm3
008c5f86 jmp 0x8c5f9a
008c5f88 movaps xmm0, xmm1
008c5f8b movaps xmm1, xmm2
008c5f8e mulss xmm0, xmm4
008c5f92 addss xmm0, xmm3
008c5f96 maxss xmm1, xmm0
008c5f9a movaps xmm0, xmm1
008c5f9d mov eax, dword ptr [ebp + 0xc]
008c5fa0 divss xmm0, xmm2
008c5fa4 mov ecx, dword ptr [esp + 0x4c]
008c5fa8 push ecx
008c5fa9 mov dword ptr [esp], 0x3f800000
008c5fb0 push edi
008c5fb1 sub esp, 0x10
008c5fb4 movss dword ptr [esp + 0x28], xmm1
008c5fba movss dword ptr [esp + 0x60], xmm0
008c5fc0 movss xmm0, dword ptr [eax]
008c5fc4 mulss xmm0, xmm4
008c5fc8 addss xmm0, dword ptr [ecx]
008c5fcc movss dword ptr [esp + 0x50], xmm0
008c5fd2 movss xmm0, dword ptr [eax + 4]
008c5fd7 mov eax, esp
008c5fd9 mulss xmm0, xmm4
008c5fdd push ecx
008c5fde addss xmm0, dword ptr [ecx + 4]
008c5fe3 mov ecx, dword ptr [0xbfd65c]
008c5fe9 movss dword ptr [esp + 0x58], xmm0
008c5fef movups xmm0, xmmword ptr [edi + 0x378]
008c5ff6 movups xmmword ptr [eax], xmm0
008c5ff9 lea eax, [esp + 0x54]
008c5ffd movss dword ptr [esp], xmm1
008c6002 push eax
008c6003 call 0x6d2fb0
008c6008 movss xmm1, dword ptr [edi + 0x2e0]
008c6010 movups xmm0, xmmword ptr [edi + 0x378]
008c6017 mov ecx, dword ptr [0xbfd65c]
008c601d addss xmm1, xmm1
008c6021 push 0
008c6023 push 0
008c6025 push 4
008c6027 sub esp, 0x10
008c602a addss xmm1, dword ptr [0xb6a974]
008c6032 mov eax, esp
008c6034 push edi
008c6035 push 1
008c6037 sub esp, 8
008c603a movups xmmword ptr [eax], xmm0
008c603d lea eax, [esp + 0x64]
008c6041 movss xmm0, dword ptr [esp + 0x3c]
008c6047 movss dword ptr [esp + 4], xmm0
008c604d movss dword ptr [esp], xmm1
008c6052 push eax
008c6053 call 0x6d1750
008c6058 mov ecx, dword ptr [edi + 0x378]
008c605e mov eax, dword ptr [edi + 0x37c]
008c6064 mov edx, dword ptr [edi + 0x380]
008c606a mov esi, dword ptr [edi + 0x384]
008c6070 and ecx, dword ptr [0xbc4c30]
008c6076 and eax, dword ptr [0xbc4c34]
008c607c and edx, dword ptr [0xbc4c38]
008c6082 and esi, dword ptr [0xbc4c3c]
008c6088 or ecx, eax
008c608a jne 0x8c6094
008c608c or edx, esi
008c608e je 0x8c66e8
008c6094 mov esi, dword ptr [0xbfd65c]
008c609a mov dword ptr [esp + 0x2c], esi
008c609e call 0x6c3d90
008c60a3 mov dword ptr [esp + 0x34], eax
008c60a7 lea eax, [esp + 0x34]
008c60ab push eax
008c60ac lea eax, [esp + 0x20]
008c60b0 mov dword ptr [esp + 0x20], 0
008c60b8 push eax
008c60b9 push 0
008c60bb push 0xc02fec
008c60c0 lea eax, [esp + 0x48]
008c60c4 mov dword ptr [esp + 0x30], 7
008c60cc push eax
008c60cd lea eax, [esp + 0x34]
008c60d1 mov dword ptr [esp + 0x28], 0x3e8
008c60d9 push eax
008c60da lea eax, [esp + 0x2c]
008c60de push eax
008c60df call 0x800fb0
008c60e4 mov ecx, dword ptr [esi + 0x1c3198]
008c60ea push 0
008c60ec push dword ptr [esp + 0x18]
008c60f0 call 0x6c4b30
008c60f5 mov esi, eax
008c60f7 mov dword ptr [esp + 0x10], esi
008c60fb test esi, esi
008c60fd je 0x8c6324
008c6103 call dword ptr [0xa064c0]
008c6109 mov ecx, dword ptr [esi + 0x320]
008c610f mov dword ptr [esp + 0x18], eax
008c6113 lea eax, [esi + 0x320]
008c6119 mov dword ptr [esi + 0x34], 0
008c6120 mov dword ptr [esi + 0x38], 0
008c6127 test ecx, ecx
008c6129 je 0x8c6145
008c612b mov dword ptr [esp + 0x50], eax
008c612f add ecx, 0x324
008c6135 lea eax, [esp + 0x50]
008c6139 push eax
008c613a call 0x4bc3c0
008c613f lea eax, [esi + 0x320]
008c6145 push dword ptr [esp + 0x34]
008c6149 mov dword ptr [eax], 0
008c614f mov ecx, esi
008c6151 movss xmm0, dword ptr [esp + 0x3c]
008c6157 push dword ptr [esp + 0x20]
008c615b mov eax, dword ptr [esi]
008c615d push dword ptr [esp + 0x28]
008c6161 movss dword ptr [esi + 0x294], xmm0
008c6169 movss xmm0, dword ptr [esp + 0x48]
008c616f push dword ptr [esp + 0x20]
008c6173 movss dword ptr [esi + 0x298], xmm0
008c617b movss xmm0, dword ptr [0xc02fec]
008c6183 movss dword ptr [esi + 0x2b8], xmm0
008c618b movss xmm0, dword ptr [0xc02ff0]
008c6193 movss dword ptr [esi + 0x2bc], xmm0
008c619b call dword ptr [eax + 4]
008c619e mov eax, dword ptr [esp + 0x2c]
008c61a2 push esi
008c61a3 mov edx, dword ptr [eax + 0x18190]
008c61a9 mov ecx, dword ptr [edx + 0x1214]
008c61af lea eax, [ecx + 1]
008c61b2 mov dword ptr [edx + 0x1214], eax
008c61b8 mov dword ptr [esi + 0x20], ecx
008c61bb lea ecx, [edx + 0x1218]
008c61c1 call 0x413280
008c61c6 push esi
008c61c7 call 0x6d94d0
008c61cc test al, al
008c61ce je 0x8c61d7
008c61d0 push ecx
008c61d1 push esi
008c61d2 call 0x6d9590
008c61d7 cmp byte ptr [esi + 0x16a], 0
008c61de je 0x8c6314
008c61e4 mov ecx, dword ptr [esp + 0x2c]
008c61e8 mov eax, dword ptr [ecx + 0x283c20]
008c61ee cmp eax, dword ptr [ecx + 0x283c24]
008c61f4 je 0x8c6314
008c61fa mov eax, dword ptr [esi + 0x28]
008c61fd mov dword ptr [esp + 0x40], eax
008c6201 mov eax, dword ptr [esi + 0x2c]
008c6204 mov dword ptr [esp + 0x44], eax
008c6208 lea eax, [ecx + 0x283c48]
008c620e lea ecx, [esp + 0x40]
008c6212 mov dword ptr [esp + 0x50], eax
008c6216 push ecx
008c6217 lea ecx, [esp + 0x30]
008c621b push ecx
008c621c mov ecx, eax
008c621e call 0x937c80
008c6223 mov ecx, dword ptr [esp + 0x50]
008c6227 mov eax, dword ptr [ecx]
008c6229 mov dword ptr [esp + 0x50], eax
008c622d cmp dword ptr [esp + 0x2c], eax
008c6231 jne 0x8c625d
008c6233 mov eax, dword ptr [esi + 0x28]
008c6236 mov dword ptr [esp + 0x40], eax
008c623a lea eax, [esp + 0x40]
008c623e push eax
008c623f lea eax, [esp + 0x6c]
008c6243 mov dword ptr [esp + 0x48], 0xffffffff
008c624b push eax
008c624c call 0x937c80
008c6251 mov ecx, dword ptr [esp + 0x50]
008c6255 cmp dword ptr [eax], ecx
008c6257 je 0x8c6314
008c625d mov esi, dword ptr [0xbfd65c]
008c6263 xor edx, edx
008c6265 mov dword ptr [esp + 0x14], edx
008c6269 mov eax, dword ptr [esi + 0x1ba54]
008c626f sub eax, dword ptr [esi + 0x1ba50]
008c6275 sar eax, 2
008c6278 test eax, eax
008c627a je 0x8c6310
008c6280 mov edi, dword ptr [esp + 0x10]
008c6284 nop dword ptr [eax]
008c6288 nop dword ptr [eax + eax]
008c6290 mov ecx, dword ptr [esi + 0x1ba54]
008c6296 mov eax, ecx
008c6298 sub eax, dword ptr [esi + 0x1ba50]
008c629e test eax, 0xfffffffc
008c62a3 jne 0x8c62be
008c62a5 push 0xb3f4d0
008c62aa push 3
008c62ac call 0x95e330
008c62b1 mov ecx, dword ptr [esi + 0x1ba54]
008c62b7 add esp, 8
008c62ba mov edx, dword ptr [esp + 0x14]
008c62be mov eax, dword ptr [esi + 0x1ba50]
008c62c4 sub ecx, eax
008c62c6 sar ecx, 2
008c62c9 cmp edx, ecx
008c62cb jae 0x8c62d0
008c62cd lea eax, [eax + edx*4]
008c62d0 push 0xc02fec
008c62d5 lea ecx, [esp + 0x3c]
008c62d9 push ecx
008c62da mov ecx, dword ptr [eax]
008c62dc push edi
008c62dd push 6
008c62df add ecx, 0x1ec0
008c62e5 call 0x935fd0
008c62ea mov esi, dword ptr [0xbfd65c]
008c62f0 mov edx, dword ptr [esp + 0x14]
008c62f4 inc edx
008c62f5 mov dword ptr [esp + 0x14], edx
008c62f9 mov eax, dword ptr [esi + 0x1ba54]
008c62ff sub eax, dword ptr [esi + 0x1ba50]
008c6305 sar eax, 2
008c6308 cmp edx, eax
008c630a jb 0x8c6290
008c630c mov edi, dword ptr [esp + 0x64]
008c6310 mov esi, dword ptr [esp + 0x10]
008c6314 call dword ptr [0xa064c0]
008c631a sub eax, dword ptr [esp + 0x18]
008c631e add dword ptr [0xbffe0c], eax
008c6324 push 0
008c6326 push 0xbeaaec
008c632b push 0xbeab18
008c6330 push 0
008c6332 push esi
008c6333 call 0x9ec34c
008c6338 add esp, 0x14
008c633b mov esi, eax
008c633d call 0x6c3d90
008c6342 push 1
008c6344 push 0
008c6346 push 0xff
008c634b movd xmm0, eax
008c634f lea ecx, [esp + 0x7c]
008c6353 cvtdq2pd xmm0, xmm0
008c6357 shr eax, 0x1f
008c635a push -1
008c635c push ecx
008c635d mov ecx, esi
008c635f mov dword ptr [esp + 0xa4], 0
008c636a mov dword ptr [esp + 0xa8], 0x3eaaaaab
008c6375 mov dword ptr [esp + 0xac], 0
008c6380 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
008c6389 mov eax, dword ptr [esi]
008c638b cvtpd2ps xmm0, xmm0
008c638f mulss xmm0, dword ptr [0xb6a19c]
008c6397 addss xmm0, dword ptr [0xb6a614]
008c639f mulss xmm0, dword ptr [esp + 0x5c]
008c63a5 movss dword ptr [esi + 0xd8], xmm0
008c63ad movss dword ptr [esi + 0xdc], xmm0
008c63b5 xorps xmm0, xmm0
008c63b8 movups xmmword ptr [esp + 0x94], xmm0
008c63c0 movaps xmm0, xmmword ptr [0xb6bed0]
008c63c7 movups xmmword ptr [esp + 0x84], xmm0
008c63cf call dword ptr [eax + 0x38]
008c63d2 mov eax, dword ptr [esi]
008c63d4 mov ecx, esi
008c63d6 call dword ptr [eax + 0xc]
008c63d9 mov esi, dword ptr [0xbfd65c]
008c63df mov dword ptr [esp + 0x34], esi
008c63e3 call 0x6c3d90
008c63e8 mov dword ptr [esp + 0x2c], eax
008c63ec lea eax, [esp + 0x2c]
008c63f0 push eax
008c63f1 lea eax, [esp + 0x24]
008c63f5 mov dword ptr [esp + 0x24], 4
008c63fd push eax
008c63fe push 0
008c6400 push 0xc02fec
008c6405 lea eax, [esp + 0x48]
008c6409 mov dword ptr [esp + 0x2c], 2
008c6411 push eax
008c6412 lea eax, [esp + 0x30]
008c6416 mov dword ptr [esp + 0x24], 0x3e8
008c641e push eax
008c641f lea eax, [esp + 0x28]
008c6423 push eax
008c6424 call 0x800fb0
008c6429 mov ecx, dword ptr [esi + 0x1c3198]
008c642f push 0
008c6431 push dword ptr [esp + 0x14]
008c6435 call 0x6c4b30
008c643a mov esi, eax
008c643c mov dword ptr [esp + 0x14], esi
008c6440 test esi, esi
008c6442 je 0x8c6664
008c6448 call dword ptr [0xa064c0]
008c644e mov ecx, dword ptr [esi + 0x320]
008c6454 mov dword ptr [esp + 0x24], eax
008c6458 lea eax, [esi + 0x320]
008c645e mov dword ptr [esi + 0x34], 0
008c6465 mov dword ptr [esi + 0x38], 0
008c646c test ecx, ecx
008c646e je 0x8c648a
008c6470 mov dword ptr [esp + 0x18], eax
008c6474 add ecx, 0x324
008c647a lea eax, [esp + 0x18]
008c647e push eax
008c647f call 0x4bc3c0
008c6484 lea eax, [esi + 0x320]
008c648a push dword ptr [esp + 0x2c]
008c648e mov dword ptr [eax], 0
008c6494 mov ecx, esi
008c6496 movss xmm0, dword ptr [esp + 0x3c]
008c649c push dword ptr [esp + 0x24]
008c64a0 mov eax, dword ptr [esi]
008c64a2 push dword ptr [esp + 0x24]
008c64a6 movss dword ptr [esi + 0x294], xmm0
008c64ae movss xmm0, dword ptr [esp + 0x48]
008c64b4 push dword ptr [esp + 0x1c]
008c64b8 movss dword ptr [esi + 0x298], xmm0
008c64c0 movss xmm0, dword ptr [0xc02fec]
008c64c8 movss dword ptr [esi + 0x2b8], xmm0
008c64d0 movss xmm0, dword ptr [0xc02ff0]
008c64d8 movss dword ptr [esi + 0x2bc], xmm0
008c64e0 call dword ptr [eax + 4]
008c64e3 mov eax, dword ptr [esp + 0x34]
008c64e7 push esi
008c64e8 mov edx, dword ptr [eax + 0x18190]
008c64ee mov ecx, dword ptr [edx + 0x1214]
008c64f4 lea eax, [ecx + 1]
008c64f7 mov dword ptr [edx + 0x1214], eax
008c64fd mov dword ptr [esi + 0x20], ecx
008c6500 lea ecx, [edx + 0x1218]
008c6506 call 0x413280
008c650b push esi
008c650c call 0x6d94d0
008c6511 test al, al
008c6513 je 0x8c651c
008c6515 push ecx
008c6516 push esi
008c6517 call 0x6d9590
008c651c cmp byte ptr [esi + 0x16a], 0
008c6523 je 0x8c6654
008c6529 mov ecx, dword ptr [esp + 0x34]
008c652d mov eax, dword ptr [ecx + 0x283c20]
008c6533 cmp eax, dword ptr [ecx + 0x283c24]
008c6539 je 0x8c6654
008c653f mov eax, dword ptr [esi + 0x28]
008c6542 mov dword ptr [esp + 0x40], eax
008c6546 mov eax, dword ptr [esi + 0x2c]
008c6549 mov dword ptr [esp + 0x44], eax
008c654d lea eax, [ecx + 0x283c48]
008c6553 lea ecx, [esp + 0x40]
008c6557 mov dword ptr [esp + 0x18], eax
008c655b push ecx
008c655c lea ecx, [esp + 0x54]
008c6560 push ecx
008c6561 mov ecx, eax
008c6563 call 0x937c80
008c6568 mov ecx, dword ptr [esp + 0x18]
008c656c mov eax, dword ptr [ecx]
008c656e mov dword ptr [esp + 0x18], eax
008c6572 cmp dword ptr [esp + 0x50], eax
008c6576 jne 0x8c65a2
008c6578 mov eax, dword ptr [esi + 0x28]
008c657b mov dword ptr [esp + 0x50], eax
008c657f lea eax, [esp + 0x50]
008c6583 push eax
008c6584 lea eax, [esp + 0x44]
008c6588 mov dword ptr [esp + 0x58], 0xffffffff
008c6590 push eax
008c6591 call 0x937c80
008c6596 mov ecx, dword ptr [esp + 0x18]
008c659a cmp dword ptr [eax], ecx
008c659c je 0x8c6654
008c65a2 mov esi, dword ptr [0xbfd65c]
008c65a8 xor edx, edx
008c65aa mov dword ptr [esp + 0x10], edx
008c65ae mov eax, dword ptr [esi + 0x1ba54]
008c65b4 sub eax, dword ptr [esi + 0x1ba50]
008c65ba sar eax, 2
008c65bd test eax, eax
008c65bf je 0x8c6650
008c65c5 mov edi, dword ptr [esp + 0x14]
008c65c9 nop dword ptr [eax]
008c65d0 mov ecx, dword ptr [esi + 0x1ba54]
008c65d6 mov eax, ecx
008c65d8 sub eax, dword ptr [esi + 0x1ba50]
008c65de test eax, 0xfffffffc
008c65e3 jne 0x8c65fe
008c65e5 push 0xb3f4d0
008c65ea push 3
008c65ec call 0x95e330
008c65f1 mov ecx, dword ptr [esi + 0x1ba54]
008c65f7 add esp, 8
008c65fa mov edx, dword ptr [esp + 0x10]
008c65fe mov eax, dword ptr [esi + 0x1ba50]
008c6604 sub ecx, eax
008c6606 sar ecx, 2
008c6609 cmp edx, ecx
008c660b jae 0x8c6610
008c660d lea eax, [eax + edx*4]
008c6610 push 0xc02fec
008c6615 lea ecx, [esp + 0x3c]
008c6619 push ecx
008c661a mov ecx, dword ptr [eax]
008c661c push edi
008c661d push 6
008c661f add ecx, 0x1ec0
008c6625 call 0x935fd0
008c662a mov esi, dword ptr [0xbfd65c]
008c6630 mov edx, dword ptr [esp + 0x10]
008c6634 inc edx
008c6635 mov dword ptr [esp + 0x10], edx
008c6639 mov eax, dword ptr [esi + 0x1ba54]
008c663f sub eax, dword ptr [esi + 0x1ba50]
008c6645 sar eax, 2
008c6648 cmp edx, eax
008c664a jb 0x8c65d0
008c664c mov edi, dword ptr [esp + 0x64]
008c6650 mov esi, dword ptr [esp + 0x14]
008c6654 call dword ptr [0xa064c0]
008c665a sub eax, dword ptr [esp + 0x24]
008c665e add dword ptr [0xbffe0c], eax
008c6664 mov eax, dword ptr [esi]
008c6666 lea ecx, [esp + 0x70]
008c666a push 1
008c666c push 0
008c666e push 0xff
008c6673 xorps xmm0, xmm0
008c6676 mov dword ptr [esp + 0x9c], 0x3d20a0a1
008c6681 push -1
008c6683 movups xmmword ptr [esp + 0x90], xmm0
008c668b push ecx
008c668c movaps xmm0, xmmword ptr [0xb6bed0]
008c6693 mov ecx, esi
008c6695 movups xmmword ptr [esp + 0x84], xmm0
008c669d mov dword ptr [esp + 0xa8], 0x3ec8c8ca
008c66a8 mov dword ptr [esp + 0xac], 0
008c66b3 call dword ptr [eax + 0x38]
008c66b6 movss xmm1, dword ptr [esp + 0x48]
008c66bc mov ecx, esi
008c66be mov eax, dword ptr [esi]
008c66c0 movaps xmm0, xmm1
008c66c3 mulss xmm0, dword ptr [0xb6a434]
008c66cb mov dword ptr [esi + 0x2b0], 0xc0a00000
008c66d5 movss dword ptr [esi + 0xd8], xmm1
008c66dd movss dword ptr [esi + 0xdc], xmm0
008c66e5 call dword ptr [eax + 0xc]
008c66e8 mov esi, dword ptr [0xbfd65c]
008c66ee mov dword ptr [esp + 0x34], esi
008c66f2 call 0x6c3d90
008c66f7 mov dword ptr [esp + 0x2c], eax
008c66fb lea eax, [esp + 0x2c]
008c66ff push eax
008c6700 lea eax, [esp + 0x24]
008c6704 mov dword ptr [esp + 0x24], 0
008c670c push eax
008c670d push 0
008c670f push 0xc02fec
008c6714 lea eax, [esp + 0x48]
008c6718 mov dword ptr [esp + 0x2c], 1
008c6720 push eax
008c6721 lea eax, [esp + 0x30]
008c6725 mov dword ptr [esp + 0x24], 0x3e8
008c672d push eax
008c672e lea eax, [esp + 0x28]
008c6732 push eax
008c6733 call 0x800fb0
008c6738 mov ecx, dword ptr [esi + 0x1c3198]
008c673e push 0
008c6740 push dword ptr [esp + 0x14]
008c6744 call 0x6c4b30
008c6749 mov esi, eax
008c674b mov dword ptr [esp + 0x14], esi
008c674f test esi, esi
008c6751 je 0x8c6974
008c6757 call dword ptr [0xa064c0]
008c675d mov ecx, dword ptr [esi + 0x320]
008c6763 mov dword ptr [esp + 0x50], eax
008c6767 lea eax, [esi + 0x320]
008c676d mov dword ptr [esi + 0x34], 0
008c6774 mov dword ptr [esi + 0x38], 0
008c677b test ecx, ecx
008c677d je 0x8c6799
008c677f mov dword ptr [esp + 0x24], eax
008c6783 add ecx, 0x324
008c6789 lea eax, [esp + 0x24]
008c678d push eax
008c678e call 0x4bc3c0
008c6793 lea eax, [esi + 0x320]
008c6799 push dword ptr [esp + 0x2c]
008c679d mov dword ptr [eax], 0
008c67a3 mov ecx, esi
008c67a5 movss xmm0, dword ptr [esp + 0x3c]
008c67ab push dword ptr [esp + 0x24]
008c67af mov eax, dword ptr [esi]
008c67b1 push dword ptr [esp + 0x24]
008c67b5 movss dword ptr [esi + 0x294], xmm0
008c67bd movss xmm0, dword ptr [esp + 0x48]
008c67c3 push dword ptr [esp + 0x1c]
008c67c7 movss dword ptr [esi + 0x298], xmm0
008c67cf movss xmm0, dword ptr [0xc02fec]
008c67d7 movss dword ptr [esi + 0x2b8], xmm0
008c67df movss xmm0, dword ptr [0xc02ff0]
008c67e7 movss dword ptr [esi + 0x2bc], xmm0
008c67ef call dword ptr [eax + 4]
008c67f2 mov eax, dword ptr [esp + 0x34]
008c67f6 push esi
008c67f7 mov edx, dword ptr [eax + 0x18190]
008c67fd mov ecx, dword ptr [edx + 0x1214]
008c6803 lea eax, [ecx + 1]
008c6806 mov dword ptr [edx + 0x1214], eax
008c680c mov dword ptr [esi + 0x20], ecx
008c680f lea ecx, [edx + 0x1218]
008c6815 call 0x413280
008c681a push esi
008c681b call 0x6d94d0
008c6820 test al, al
008c6822 je 0x8c682b
008c6824 push ecx
008c6825 push esi
008c6826 call 0x6d9590
008c682b cmp byte ptr [esi + 0x16a], 0
008c6832 je 0x8c6964
008c6838 mov ecx, dword ptr [esp + 0x34]
008c683c mov eax, dword ptr [ecx + 0x283c20]
008c6842 cmp eax, dword ptr [ecx + 0x283c24]
008c6848 je 0x8c6964
008c684e mov eax, dword ptr [esi + 0x28]
008c6851 mov dword ptr [esp + 0x2c], eax
008c6855 mov eax, dword ptr [esi + 0x2c]
008c6858 mov dword ptr [esp + 0x30], eax
008c685c lea eax, [ecx + 0x283c48]
008c6862 lea ecx, [esp + 0x2c]
008c6866 mov dword ptr [esp + 0x24], eax
008c686a push ecx
008c686b lea ecx, [esp + 0x1c]
008c686f push ecx
008c6870 mov ecx, eax
008c6872 call 0x937c80
008c6877 mov ecx, dword ptr [esp + 0x24]
008c687b mov eax, dword ptr [ecx]
008c687d mov dword ptr [esp + 0x24], eax
008c6881 cmp dword ptr [esp + 0x18], eax
008c6885 jne 0x8c68b1
008c6887 mov eax, dword ptr [esi + 0x28]
008c688a mov dword ptr [esp + 0x2c], eax
008c688e lea eax, [esp + 0x2c]
008c6892 push eax
008c6893 lea eax, [esp + 0x1c]
008c6897 mov dword ptr [esp + 0x34], 0xffffffff
008c689f push eax
008c68a0 call 0x937c80
008c68a5 mov ecx, dword ptr [esp + 0x24]
008c68a9 cmp dword ptr [eax], ecx
008c68ab je 0x8c6964
008c68b1 mov esi, dword ptr [0xbfd65c]
008c68b7 xor edx, edx
008c68b9 mov dword ptr [esp + 0x10], edx
008c68bd mov eax, dword ptr [esi + 0x1ba54]
008c68c3 sub eax, dword ptr [esi + 0x1ba50]
008c68c9 sar eax, 2
008c68cc test eax, eax
008c68ce je 0x8c6960
008c68d4 mov edi, dword ptr [esp + 0x14]
008c68d8 nop dword ptr [eax + eax]
008c68e0 mov ecx, dword ptr [esi + 0x1ba54]
008c68e6 mov eax, ecx
008c68e8 sub eax, dword ptr [esi + 0x1ba50]
008c68ee test eax, 0xfffffffc
008c68f3 jne 0x8c690e
008c68f5 push 0xb3f4d0
008c68fa push 3
008c68fc call 0x95e330
008c6901 mov ecx, dword ptr [esi + 0x1ba54]
008c6907 add esp, 8
008c690a mov edx, dword ptr [esp + 0x10]
008c690e mov eax, dword ptr [esi + 0x1ba50]
008c6914 sub ecx, eax
008c6916 sar ecx, 2
008c6919 cmp edx, ecx
008c691b jae 0x8c6920
008c691d lea eax, [eax + edx*4]
008c6920 push 0xc02fec
008c6925 lea ecx, [esp + 0x3c]
008c6929 push ecx
008c692a mov ecx, dword ptr [eax]
008c692c push edi
008c692d push 6
008c692f add ecx, 0x1ec0
008c6935 call 0x935fd0
008c693a mov esi, dword ptr [0xbfd65c]
008c6940 mov edx, dword ptr [esp + 0x10]
008c6944 inc edx
008c6945 mov dword ptr [esp + 0x10], edx
008c6949 mov eax, dword ptr [esi + 0x1ba54]
008c694f sub eax, dword ptr [esi + 0x1ba50]
008c6955 sar eax, 2
008c6958 cmp edx, eax
008c695a jb 0x8c68e0
008c695c mov edi, dword ptr [esp + 0x64]
008c6960 mov esi, dword ptr [esp + 0x14]
008c6964 call dword ptr [0xa064c0]
008c696a sub eax, dword ptr [esp + 0x50]
008c696e add dword ptr [0xbffe0c], eax
008c6974 push 0
008c6976 push 0xbeaaec
008c697b push 0xbeab18
008c6980 push 0
008c6982 push esi
008c6983 call 0x9ec34c
008c6988 movss xmm1, dword ptr [esp + 0x5c]
008c698e add esp, 0x14
008c6991 ucomiss xmm1, dword ptr [0xb6a614]
008c6998 mov ecx, eax
008c699a lahf 
008c699b test ah, 0x44
008c699e jnp 0x8c69c3
008c69a0 movaps xmm0, xmm1
008c69a3 mulss xmm1, dword ptr [ecx + 0xdc]
008c69ab mulss xmm0, dword ptr [ecx + 0xd8]
008c69b3 movss dword ptr [ecx + 0xdc], xmm1
008c69bb movss dword ptr [ecx + 0xd8], xmm0
008c69c3 mov edx, dword ptr [ecx]
008c69c5 lea eax, [edi + 0xe4]
008c69cb push 1
008c69cd push 0
008c69cf push 0xff
008c69d4 push -1
008c69d6 push eax
008c69d7 call dword ptr [edx + 0x38]
008c69da mov esi, dword ptr [0xbc4ca8]
008c69e0 mov ecx, dword ptr [0xbc4ca0]
008c69e6 not esi
008c69e8 mov eax, dword ptr [0xbc4ca4]
008c69ed not ecx
008c69ef mov edx, dword ptr [0xbc4cac]
008c69f5 not eax
008c69f7 and dword ptr [edi + 0x388], ecx
008c69fd not edx
008c69ff and dword ptr [edi + 0x38c], eax
008c6a05 and dword ptr [edi + 0x390], esi
008c6a0b and dword ptr [edi + 0x394], edx
008c6a11 movss xmm3, dword ptr [0xb6a8cc]
008c6a19 mov esi, dword ptr [edi + 0x380]
008c6a1f mov eax, esi
008c6a21 and eax, dword ptr [0xbc4a08]
008c6a27 mov edx, dword ptr [edi + 0x384]
008c6a2d mov ecx, dword ptr [0xbc4a00]
008c6a33 and ecx, dword ptr [edi + 0x378]
008c6a39 mov dword ptr [esp + 0x24], eax
008c6a3d mov eax, dword ptr [0xbc4a0c]
008c6a42 and eax, edx
008c6a44 mov dword ptr [esp + 0x18], eax
008c6a48 mov eax, dword ptr [0xbc4a04]
008c6a4d and eax, dword ptr [edi + 0x37c]
008c6a53 or ecx, eax
008c6a55 jne 0x8c6a65
008c6a57 mov eax, dword ptr [esp + 0x24]
008c6a5b or eax, dword ptr [esp + 0x18]
008c6a5f je 0x8c6e13
008c6a65 cmp byte ptr [edi + 0x3ac], 0
008c6a6c jne 0x8c6a87
008c6a6e xorps xmm2, xmm2
008c6a71 mov dword ptr [esp + 0x48], edx
008c6a75 movaps xmm1, xmm3
008c6a78 mov ecx, edi
008c6a7a call 0x6847e0
008c6a7f test eax, eax
008c6a81 je 0x8c6e0f
008c6a87 mov ecx, dword ptr [0xbfd65c]
008c6a8d lea eax, [esp + 0x68]
008c6a91 movss xmm3, dword ptr [0xb6a614]
008c6a99 sub esp, 0xc
008c6a9c mov ecx, dword ptr [ecx + 0x18190]
008c6aa2 mov dword ptr [esp + 8], 0x3f800000
008c6aaa mov dword ptr [esp + 4], 0x3f800000
008c6ab2 mov dword ptr [esp], 0x3f800000
008c6ab9 push dword ptr [esp + 0x58]
008c6abd push eax
008c6abe call 0x7cec10
008c6ac3 call 0x6c3d90
008c6ac8 movd xmm0, eax
008c6acc cvtdq2pd xmm0, xmm0
008c6ad0 shr eax, 0x1f
008c6ad3 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
008c6adc cvtpd2ps xmm0, xmm0
008c6ae0 mulss xmm0, dword ptr [0xb6a19c]
008c6ae8 mulss xmm0, dword ptr [0xb6a874]
008c6af0 addss xmm0, xmm0
008c6af4 movss dword ptr [esp + 0x24], xmm0
008c6afa call 0x411fe0
008c6aff mulss xmm0, dword ptr [0xb6a974]
008c6b07 movss dword ptr [esp + 0x20], xmm0
008c6b0d movss xmm0, dword ptr [esp + 0x24]
008c6b13 call 0x412010
008c6b18 mov esi, dword ptr [0xbc48a0]
008c6b1e or esi, dword ptr [0xbc46b0]
008c6b24 or esi, dword ptr [0xbc46c0]
008c6b2a or esi, dword ptr [0xbc4890]
008c6b30 or esi, dword ptr [0xbc4a30]
008c6b36 or esi, dword ptr [0xbc4ce0]
008c6b3c or esi, dword ptr [0xbc49e0]
008c6b42 mov edx, dword ptr [0xbc48a4]
008c6b48 or edx, dword ptr [0xbc46b4]
008c6b4e or edx, dword ptr [0xbc46c4]
008c6b54 or edx, dword ptr [0xbc4894]
008c6b5a or edx, dword ptr [0xbc4a34]
008c6b60 or edx, dword ptr [0xbc4ce4]
008c6b66 or edx, dword ptr [0xbc49e4]
008c6b6c or esi, dword ptr [0xbc4a00]
008c6b72 or edx, dword ptr [0xbc4a04]
008c6b78 not esi
008c6b7a mov ecx, dword ptr [0xbc4be0]
008c6b80 not edx
008c6b82 or ecx, dword ptr [edi + 0x378]
008c6b88 mov eax, dword ptr [0xbc4be4]
008c6b8d and esi, ecx
008c6b8f or eax, dword ptr [edi + 0x37c]
008c6b95 mov ecx, dword ptr [edi + 0x380]
008c6b9b and edx, eax
008c6b9d or ecx, dword ptr [0xbc4be8]
008c6ba3 mov eax, dword ptr [edi + 0x384]
008c6ba9 mulss xmm0, dword ptr [0xb6a974]
008c6bb1 or eax, dword ptr [0xbc4bec]
008c6bb7 mov dword ptr [esp + 0x50], esi
008c6bbb mov esi, dword ptr [0xbc48a8]
008c6bc1 or esi, dword ptr [0xbc46b8]
008c6bc7 or esi, dword ptr [0xbc46c8]
008c6bcd or esi, dword ptr [0xbc4898]
008c6bd3 or esi, dword ptr [0xbc4a38]
008c6bd9 or esi, dword ptr [0xbc4ce8]
008c6bdf or esi, dword ptr [0xbc49e8]
008c6be5 or esi, dword ptr [0xbc4a08]
008c6beb mov dword ptr [esp + 0x54], edx
008c6bef not esi
008c6bf1 mov edx, dword ptr [0xbc48ac]
008c6bf7 and esi, ecx
008c6bf9 or edx, dword ptr [0xbc46bc]
008c6bff or edx, dword ptr [0xbc46cc]
008c6c05 or edx, dword ptr [0xbc489c]
008c6c0b or edx, dword ptr [0xbc4a3c]
008c6c11 or edx, dword ptr [0xbc4cec]
008c6c17 or edx, dword ptr [0xbc49ec]
008c6c1d or edx, dword ptr [0xbc4a0c]
008c6c23 not edx
008c6c25 movss dword ptr [esp + 0x2c], xmm0
008c6c2b and edx, eax
008c6c2d mov dword ptr [esp + 0x58], esi
008c6c31 mov dword ptr [esp + 0x5c], edx
008c6c35 lea eax, [esp + 0x70]
008c6c39 push eax
008c6c3a mov ecx, edi
008c6c3c call 0x8c7070
008c6c41 xor eax, eax
008c6c43 mov dword ptr [esp + 0x1c], eax
008c6c47 movss xmm2, dword ptr [0xb6c9b0]
008c6c4f cmp eax, 2
008c6c52 jae 0x8c6c62
008c6c54 movss xmm1, dword ptr [esp + 0x20]
008c6c5a movss xmm0, dword ptr [esp + 0x2c]
008c6c60 jmp 0x8c6c71
008c6c62 movss xmm0, dword ptr [esp + 0x20]
008c6c68 movss xmm1, dword ptr [esp + 0x2c]
008c6c6e xorps xmm0, xmm2
008c6c71 movss dword ptr [esp + 0x44], xmm0
008c6c77 movss dword ptr [esp + 0x40], xmm1
008c6c7d test al, 1
008c6c7f je 0x8c6c93
008c6c81 xorps xmm1, xmm2
008c6c84 xorps xmm0, xmm2
008c6c87 movss dword ptr [esp + 0x40], xmm1
008c6c8d movss dword ptr [esp + 0x44], xmm0
008c6c93 call 0x6c3d90
008c6c98 mov ecx, dword ptr [ebp + 0xc]
008c6c9b movss xmm0, dword ptr [esp + 0x68]
008c6ca1 push 0
008c6ca3 push eax
008c6ca4 movss xmm1, dword ptr [ecx]
008c6ca8 lea eax, [esp + 0x48]
008c6cac mulss xmm1, dword ptr [0xb6a8cc]
008c6cb4 push 0
008c6cb6 push dword ptr [edi + 0x320]
008c6cbc subss xmm0, xmm1
008c6cc0 movss xmm1, dword ptr [ecx + 4]
008c6cc5 mulss xmm1, dword ptr [0xb6a8cc]
008c6ccd mov ecx, dword ptr [0xbfd65c]
008c6cd3 push eax
008c6cd4 lea eax, [esp + 0x38]
008c6cd8 movss dword ptr [esp + 0x38], xmm0
008c6cde movss xmm0, dword ptr [esp + 0x80]
008c6ce7 subss xmm0, xmm1
008c6ceb push eax
008c6cec push 0
008c6cee push 2
008c6cf0 movss dword ptr [esp + 0x48], xmm0
008c6cf6 call 0x6d0ca0
008c6cfb movss xmm1, dword ptr [0xb6aec0]
008c6d03 mov esi, eax
008c6d05 mov ecx, esi
008c6d07 mov dword ptr [esi + 0x360], 0xc13e0000
008c6d11 call 0x650150
008c6d16 mov ecx, dword ptr [0xbfd65c]
008c6d1c movss dword ptr [esi + 0x2a8], xmm0
008c6d24 mov ecx, dword ptr [ecx + 0x18190]
008c6d2a cmp dword ptr [ecx + 8], 0x10
008c6d2e jne 0x8c6d3a
008c6d30 mov dword ptr [esi + 0x2a8], 0xc1900000
008c6d3a movaps xmm0, xmmword ptr [esp + 0x50]
008c6d3f sub esp, 0x10
008c6d42 mov eax, esp
008c6d44 mov ecx, esi
008c6d46 movups xmmword ptr [eax], xmm0
008c6d49 call 0x650280
008c6d4e movss xmm0, dword ptr [edi + 0x2e0]
008c6d56 mulss xmm0, dword ptr [0xb6a480]
008c6d5e mov eax, dword ptr [esi]
008c6d60 push ecx
008c6d61 mov ecx, esi
008c6d63 movss dword ptr [esp], xmm0
008c6d68 call dword ptr [eax + 0x3c]
008c6d6b movss xmm0, dword ptr [edi + 0x430]
008c6d73 mov ecx, esi
008c6d75 mulss xmm0, dword ptr [0xb6a4c4]
008c6d7d maxss xmm0, dword ptr [0xb6a214]
008c6d85 movss dword ptr [esi + 0x374], xmm0
008c6d8d movss dword ptr [esi + 0x370], xmm0
008c6d95 call 0x651770
008c6d9a mov eax, dword ptr [esi]
008c6d9c lea ecx, [esp + 0x70]
008c6da0 push 1
008c6da2 push 0
008c6da4 push 0xff
008c6da9 push -1
008c6dab push ecx
008c6dac mov ecx, esi
008c6dae call dword ptr [eax + 0x38]
008c6db1 mov eax, dword ptr [esi]
008c6db3 mov ecx, esi
008c6db5 call dword ptr [eax + 0xc]
008c6db8 mov eax, dword ptr [esp + 0x1c]
008c6dbc inc eax
008c6dbd mov dword ptr [esp + 0x1c], eax
008c6dc1 cmp eax, 4
008c6dc4 jl 0x8c6c47
008c6dca mov esi, dword ptr [0xbc4a08]
008c6dd0 mov ecx, dword ptr [0xbc4a00]
008c6dd6 not esi
008c6dd8 mov eax, dword ptr [0xbc4a04]
008c6ddd not ecx
008c6ddf mov edx, dword ptr [0xbc4a0c]
008c6de5 not eax
008c6de7 and dword ptr [edi + 0x388], ecx
008c6ded not edx
008c6def and dword ptr [edi + 0x38c], eax
008c6df5 and dword ptr [edi + 0x390], esi
008c6dfb and dword ptr [edi + 0x394], edx
008c6e01 mov esi, dword ptr [edi + 0x380]
008c6e07 mov edx, dword ptr [edi + 0x384]
008c6e0d jmp 0x8c6e13
008c6e0f mov edx, dword ptr [esp + 0x48]
008c6e13 mov ecx, dword ptr [0xbc4970]
008c6e19 mov eax, esi
008c6e1b and eax, dword ptr [0xbc4978]
008c6e21 and ecx, dword ptr [edi + 0x378]
008c6e27 movss xmm0, dword ptr [0xb6a7b0]
008c6e2f mov dword ptr [esp + 0x24], eax
008c6e33 mov eax, dword ptr [0xbc497c]
008c6e38 and eax, edx
008c6e3a mov dword ptr [esp + 0x18], eax
008c6e3e mov eax, dword ptr [0xbc4974]
008c6e43 and eax, dword ptr [edi + 0x37c]
008c6e49 or ecx, eax
008c6e4b jne 0x8c6e5b
008c6e4d mov eax, dword ptr [esp + 0x24]
008c6e51 or eax, dword ptr [esp + 0x18]
008c6e55 je 0x8c6edc
008c6e5b cmp byte ptr [edi + 0x3ac], 0
008c6e62 jne 0x8c6e79
008c6e64 xorps xmm2, xmm2
008c6e67 mov dword ptr [esp + 0x48], edx
008c6e6b movaps xmm1, xmm0
008c6e6e mov ecx, edi
008c6e70 call 0x6847e0
008c6e75 test eax, eax
008c6e77 je 0x8c6ed0
008c6e79 push dword ptr [edi + 0x320]
008c6e7f movss xmm2, dword ptr [edi + 0x2e0]
008c6e87 movups xmm0, xmmword ptr [edi + 0x378]
008c6e8e sub esp, 0x10
008c6e91 mulss xmm2, dword ptr [0xb6a480]
008c6e99 mov eax, esp
008c6e9b push dword ptr [esp + 0x60]
008c6e9f movups xmmword ptr [eax], xmm0
008c6ea2 call 0x6d9820
008c6ea7 mov esi, eax
008c6ea9 lea ecx, [edi + 0x470]
008c6eaf push ecx
008c6eb0 lea ecx, [esi + 0x3cc]
008c6eb6 call 0x71ed10
008c6ebb mov edx, dword ptr [esi]
008c6ebd mov ecx, esi
008c6ebf call dword ptr [edx + 0xc]
008c6ec2 mov esi, dword ptr [edi + 0x380]
008c6ec8 mov edx, dword ptr [edi + 0x384]
008c6ece jmp 0x8c6ed4
008c6ed0 mov edx, dword ptr [esp + 0x48]
008c6ed4 movss xmm0, dword ptr [0xb6a7b0]
008c6edc mov eax, dword ptr [0xbc49cc]
008c6ee1 mov ecx, dword ptr [0xbc49c0]
008c6ee7 and eax, edx
008c6ee9 and ecx, dword ptr [edi + 0x378]
008c6eef and esi, dword ptr [0xbc49c8]
008c6ef5 mov dword ptr [esp + 0x24], eax
008c6ef9 mov eax, dword ptr [0xbc49c4]
008c6efe and eax, dword ptr [edi + 0x37c]
008c6f04 or ecx, eax
008c6f06 jne 0x8c6f12
008c6f08 or esi, dword ptr [esp + 0x24]
008c6f0c je 0x8c7059
008c6f12 cmp byte ptr [edi + 0x3ac], 0
008c6f19 jne 0x8c6f30
008c6f1b xorps xmm2, xmm2
008c6f1e movaps xmm1, xmm0
008c6f21 mov ecx, edi
008c6f23 call 0x6847e0
008c6f28 test eax, eax
008c6f2a je 0x8c7059
008c6f30 mov esi, dword ptr [0xbfd65c]
008c6f36 push ecx
008c6f37 mov dword ptr [esp], 0xc1200000
008c6f3e push dword ptr [esp + 0x50]
008c6f42 mov ecx, dword ptr [esi + 0x18190]
008c6f48 call 0x7cf0a0
008c6f4d test al, al
008c6f4f je 0x8c7059
008c6f55 movss xmm0, dword ptr [edi + 0x2e0]
008c6f5d lea eax, [esp + 0x38]
008c6f61 mulss xmm0, dword ptr [0xb6a480]
008c6f69 sub esp, 0xc
008c6f6c mov ecx, dword ptr [esi + 0x18190]
008c6f72 xorps xmm3, xmm3
008c6f75 mov dword ptr [esp + 8], 0
008c6f7d mov dword ptr [esp + 4], 0
008c6f85 mov dword ptr [esp], 0
008c6f8c push dword ptr [esp + 0x58]
008c6f90 movss dword ptr [esp + 0x34], xmm0
008c6f96 push eax
008c6f97 call 0x7cec10
008c6f9c call 0x6c3d90
008c6fa1 push 0
008c6fa3 push eax
008c6fa4 push 0
008c6fa6 push dword ptr [edi + 0x320]
008c6fac lea eax, [esp + 0x48]
008c6fb0 mov ecx, esi
008c6fb2 push 0xc02fec
008c6fb7 push eax
008c6fb8 push 0xb4
008c6fbd push 0x3e8
008c6fc2 call 0x6d0ca0
008c6fc7 movss xmm1, dword ptr [edi + 0x430]
008c6fcf mov esi, eax
008c6fd1 movaps xmm0, xmm1
008c6fd4 mulss xmm1, dword ptr [0xbc7a2c]
008c6fdc push ecx
008c6fdd mulss xmm0, dword ptr [0xbc7a28]
008c6fe5 mov ecx, esi
008c6fe7 mov eax, dword ptr [esi]
008c6fe9 movss dword ptr [esi + 0xdc], xmm1
008c6ff1 movss dword ptr [esi + 0xd8], xmm0
008c6ff9 movss xmm0, dword ptr [esp + 0x28]
008c6fff movss dword ptr [esp], xmm0
008c7004 call dword ptr [eax + 0x3c]
008c7007 mov eax, dword ptr [esi]
008c7009 mov ecx, esi
008c700b mov dword ptr [esi + 0x3ac], 0x3c
008c7015 mov dword ptr [esi + 0x3b0], 0x3c
008c701f call dword ptr [eax + 0xc]
008c7022 mov esi, dword ptr [0xbc49c8]
008c7028 mov ecx, dword ptr [0xbc49c0]
008c702e not esi
008c7030 mov eax, dword ptr [0xbc49c4]
008c7035 not ecx
008c7037 mov edx, dword ptr [0xbc49cc]
008c703d not eax
008c703f and dword ptr [edi + 0x388], ecx
008c7045 not edx
008c7047 and dword ptr [edi + 0x38c], eax
008c704d and dword ptr [edi + 0x390], esi
008c7053 and dword ptr [edi + 0x394], edx
008c7059 mov ecx, dword ptr [esp + 0x9c]
008c7060 pop edi
008c7061 pop esi
008c7062 xor ecx, esp
008c7064 call 0x9eacd7
008c7069 mov esp, ebp
008c706b pop ebp
008c706c ret 8
008c706f int3 
008c7070 push ebp
008c7071 mov ebp, esp
008c7073 and esp, 0xfffffff0
008c7076 mov eax, dword ptr [ecx + 0x2c]
008c7079 sub esp, 0x80
008c707f cmp eax, 3
008c7082 je 0x8c717e
008c7088 cmp eax, 0xa
008c708b je 0x8c717e
008c7091 cmp eax, 2
008c7094 lea edx, [ecx + 0xe4]
008c709a lea eax, [esp]
008c709d push eax
008c709e jne 0x8c70db
008c70a0 movaps xmm0, xmmword ptr [0xb6bdc0]
008c70a7 movups xmmword ptr [esp + 4], xmm0
008c70ac lea ecx, [esp + 0x14]
008c70b0 call 0x4d1ee0
008c70b5 add esp, 4
008c70b8 movups xmm0, xmmword ptr [eax]
008c70bb movups xmmword ptr [esp], xmm0
008c70bf movss xmm6, dword ptr [esp + 0xc]
008c70c5 movss xmm4, dword ptr [esp + 8]
008c70cb movss xmm2, dword ptr [esp + 4]
008c70d1 movss xmm3, dword ptr [esp]
008c70d6 jmp 0x8c7246
008c70db movaps xmm0, xmmword ptr [0xb6c5e0]
008c70e2 lea ecx, [esp + 0x24]
008c70e6 mov eax, dword ptr [edx + 0x28]
008c70e9 movups xmmword ptr [esp + 4], xmm0
008c70ee mov dword ptr [esp + 0x4c], eax
008c70f2 lea eax, [esp + 0x58]
008c70f6 xorps xmm0, xmm0
008c70f9 mov dword ptr [esp + 0x78], 0
008c7101 movups xmmword ptr [esp + 0x68], xmm0
008c7106 push eax
008c7107 movaps xmm0, xmmword ptr [0xb6bdc0]
008c710e movups xmmword ptr [esp + 0x5c], xmm0
008c7113 mov dword ptr [esp + 0x80], 0
008c711e movups xmm0, xmmword ptr [edx]
008c7121 mov dword ptr [esp + 0x84], 0
008c712c movups xmmword ptr [esp + 0x28], xmm0
008c7131 movups xmm0, xmmword ptr [edx + 0x10]
008c7135 movups xmmword ptr [esp + 0x38], xmm0
008c713a movq xmm0, qword ptr [edx + 0x20]
008c713f movq qword ptr [esp + 0x48], xmm0
008c7145 call 0x65b0f0
008c714a movups xmm0, xmmword ptr [esp + 0x24]
008c714f mov eax, dword ptr [esp + 0x4c]
008c7153 lea edx, [esp + 0x58]
008c7157 mov dword ptr [esp + 0x80], eax
008c715e movups xmmword ptr [esp + 0x58], xmm0
008c7163 movups xmm0, xmmword ptr [esp + 0x34]
008c7168 movups xmmword ptr [esp + 0x68], xmm0
008c716d movq xmm0, qword ptr [esp + 0x44]
008c7173 movq qword ptr [esp + 0x78], xmm0
008c7179 jmp 0x8c70ac
008c717e movss xmm5, dword ptr [ecx + 0x100]
008c7186 ucomiss xmm5, dword ptr [0xb6a18c]
008c718d movss xmm3, dword ptr [ecx + 0xe4]
008c7195 movss xmm2, dword ptr [ecx + 0xe8]
008c719d mulss xmm3, dword ptr [0xb6a588]
008c71a5 mulss xmm2, dword ptr [0xb6a5a4]
008c71ad movss xmm4, dword ptr [ecx + 0xec]
008c71b5 movss xmm6, dword ptr [ecx + 0xf0]
008c71bd lahf 
008c71be test ah, 0x44
008c71c1 jnp 0x8c722e
008c71c3 movaps xmm1, xmm3
008c71c6 movaps xmm0, xmm2
008c71c9 mulss xmm0, dword ptr [0xb6a52c]
008c71d1 mulss xmm1, dword ptr [0xb6a370]
008c71d9 addss xmm1, xmm0
008c71dd movaps xmm0, xmm4
008c71e0 mulss xmm0, dword ptr [0xb6a298]
008c71e8 addss xmm1, xmm0
008c71ec movaps xmm0, xmm1
008c71ef mulss xmm0, dword ptr [ecx + 0xf4]
008c71f7 subss xmm0, xmm3
008c71fb mulss xmm0, xmm5
008c71ff addss xmm3, xmm0
008c7203 movaps xmm0, xmm1
008c7206 mulss xmm0, dword ptr [ecx + 0xf8]
008c720e mulss xmm1, dword ptr [ecx + 0xfc]
008c7216 subss xmm0, xmm2
008c721a subss xmm1, xmm4
008c721e mulss xmm0, xmm5
008c7222 mulss xmm1, xmm5
008c7226 addss xmm2, xmm0
008c722a addss xmm4, xmm1
008c722e addss xmm3, dword ptr [ecx + 0x104]
008c7236 addss xmm2, dword ptr [ecx + 0x108]
008c723e addss xmm4, dword ptr [ecx + 0x10c]
008c7246 mov eax, dword ptr [ebp + 8]
008c7249 movss xmm0, dword ptr [0xb6a480]
008c7251 mulss xmm3, xmm0
008c7255 mulss xmm2, xmm0
008c7259 mov dword ptr [eax], 0x3f800000
008c725f mulss xmm4, xmm0
008c7263 mov dword ptr [eax + 4], 0x3f800000
008c726a mov dword ptr [eax + 8], 0x3f800000
008c7271 movss dword ptr [eax + 0xc], xmm6
008c7276 movss dword ptr [eax + 0x10], xmm3
008c727b movss dword ptr [eax + 0x14], xmm2
008c7280 movss dword ptr [eax + 0x18], xmm4
008c7285 mov dword ptr [eax + 0x1c], 0x3f800000
008c728c movss dword ptr [eax + 0x20], xmm3
008c7291 movss dword ptr [eax + 0x24], xmm2
008c7296 movss dword ptr [eax + 0x28], xmm4
008c729b mov esp, ebp
008c729d pop ebp
008c729e ret 4
008c72a1 int3 
008c72a2 int3 
008c72a3 int3 
008c72a4 int3 
008c72a5 int3 
008c72a6 int3 
008c72a7 int3 
008c72a8 int3 
008c72a9 int3 
008c72aa int3 
008c72ab int3 
008c72ac int3 
008c72ad int3 
008c72ae int3 
008c72af int3 
008c72b0 push ebp
008c72b1 mov ebp, esp
008c72b3 and esp, 0xfffffff8
008c72b6 mov eax, dword ptr fs:[0x2c]
008c72bc sub esp, 0xc
008c72bf mov edx, dword ptr [eax]
008c72c1 mov eax, dword ptr [0xc07084]
008c72c6 push ebx
008c72c7 push esi
008c72c8 push edi
008c72c9 mov edi, ecx
008c72cb cmp eax, dword ptr [edx + 0xc]
008c72d1 jg 0x8c749f
008c72d7 cmp byte ptr [ebp + 0xc], 0
008c72db mov ebx, dword ptr [ebp + 8]
008c72de je 0x8c73a5
008c72e4 mov eax, dword ptr [ebx + 0x334]
008c72ea lea esi, [edi + 0x320]
008c72f0 movq xmm0, qword ptr [0xa08c08]
008c72f8 mov dword ptr [edi + 0x334], eax
008c72fe mov eax, dword ptr [0xa08c10]
008c7303 movq qword ptr [edi + 0x338], xmm0
008c730b mov dword ptr [edi + 0x340], eax
008c7311 mov eax, dword ptr [ebx + 0x424]
008c7317 mov ecx, dword ptr [esi]
008c7319 mov dword ptr [edi + 0x424], eax
008c731f mov eax, dword ptr [ebx + 0x34]
008c7322 mov dword ptr [edi + 0x34], eax
008c7325 mov eax, dword ptr [ebx + 0x38]
008c7328 mov dword ptr [edi + 0x38], eax
008c732b mov eax, dword ptr [ebx + 0x320]
008c7331 mov dword ptr [esp + 0x14], eax
008c7335 test ecx, ecx
008c7337 je 0x8c7351
008c7339 lea eax, [esp + 0x10]
008c733d mov dword ptr [esp + 0x10], esi
008c7341 push eax
008c7342 add ecx, 0x324
008c7348 call 0x4bc3c0
008c734d mov eax, dword ptr [esp + 0x14]
008c7351 mov dword ptr [esi], eax
008c7353 test eax, eax
008c7355 je 0x8c735f
008c7357 push esi
008c7358 mov ecx, eax
008c735a call 0x4bae70
008c735f movzx eax, byte ptr [ebx + 0x465]
008c7366 mov ecx, edi
008c7368 mov byte ptr [edi + 0x465], al
008c736e movzx eax, byte ptr [ebx + 0x450]
008c7375 mov byte ptr [edi + 0x450], al
008c737b movzx eax, byte ptr [ebx + 0x464]
008c7382 mov byte ptr [edi + 0x464], al
008c7388 mov eax, dword ptr [ebx + 0x430]
008c738e mov dword ptr [edi + 0x430], eax
008c7394 call 0x8d7d90
008c7399 mov eax, dword ptr [ebx + 0x4b0]
008c739f mov dword ptr [edi + 0x4b0], eax
008c73a5 mov edx, dword ptr [edi]
008c73a7 lea eax, [ebx + 0xe4]
008c73ad push 1
008c73af push 0
008c73b1 push 0xff
008c73b6 push -1
008c73b8 push eax
008c73b9 mov ecx, edi
008c73bb call dword ptr [edx + 0x38]
008c73be mov ecx, dword ptr [0xc07090]
008c73c4 mov esi, dword ptr [0xc07098]
008c73ca mov edx, dword ptr [ebx + 0x394]
008c73d0 and ecx, dword ptr [ebx + 0x388]
008c73d6 mov eax, dword ptr [ebx + 0x38c]
008c73dc and eax, dword ptr [0xc07094]
008c73e2 and esi, dword ptr [ebx + 0x390]
008c73e8 and edx, dword ptr [0xc0709c]
008c73ee mov dword ptr [edi + 0x378], ecx
008c73f4 mov dword ptr [edi + 0x37c], eax
008c73fa mov dword ptr [edi + 0x380], esi
008c7400 mov dword ptr [edi + 0x384], edx
008c7406 mov eax, dword ptr [edi]
008c7408 movss xmm0, dword ptr [ebx + 0x2e0]
008c7410 push ecx
008c7411 mov ecx, edi
008c7413 movss dword ptr [esp], xmm0
008c7418 call dword ptr [eax + 0x3c]
008c741b cmp byte ptr [ebp + 0xc], 0
008c741f mov eax, dword ptr [ebx + 0x444]
008c7425 mov dword ptr [edi + 0x444], eax
008c742b mov eax, dword ptr [ebx + 0x420]
008c7431 mov dword ptr [edi + 0x420], eax
008c7437 mov al, byte ptr [ebx + 0x169]
008c743d mov byte ptr [edi + 0x169], al
008c7443 mov eax, dword ptr [ebx + 0x2b0]
008c7449 mov dword ptr [edi + 0x2b0], eax
008c744f mov eax, dword ptr [ebx + 0x17c]
008c7455 mov dword ptr [edi + 0x17c], eax
008c745b mov eax, dword ptr [ebx + 0x180]
008c7461 mov dword ptr [edi + 0x180], eax
008c7467 mov eax, dword ptr [ebx + 0x2d4]
008c746d mov dword ptr [edi + 0x2d4], eax
008c7473 jne 0x8c747e
008c7475 cmp byte ptr [edi + 0x465], 0
008c747c jne 0x8c7496
008c747e mov eax, dword ptr [ebx + 0x3a8]
008c7484 mov dword ptr [edi + 0x3a8], eax
008c748a mov al, byte ptr [ebx + 0x3ae]
008c7490 mov byte ptr [edi + 0x3ae], al
008c7496 pop edi
008c7497 pop esi
008c7498 pop ebx
008c7499 mov esp, ebp
008c749b pop ebp
008c749c ret 8
008c749f push 0xc07084
008c74a4 call 0x9eb26f
008c74a9 add esp, 4
008c74ac cmp dword ptr [0xc07084], -1
008c74b3 jne 0x8c72d7
008c74b9 mov ecx, dword ptr [0xbc4790]
008c74bf or ecx, dword ptr [0xbc4890]
008c74c5 or ecx, dword ptr [0xbc49e0]
008c74cb mov eax, dword ptr [0xbc4794]
008c74d0 or eax, dword ptr [0xbc4894]
008c74d6 or eax, dword ptr [0xbc49e4]
008c74dc or ecx, dword ptr [0xbc4860]
008c74e2 or eax, dword ptr [0xbc4864]
008c74e8 not ecx
008c74ea not eax
008c74ec mov dword ptr [0xc07090], ecx
008c74f2 mov ecx, dword ptr [0xbc4798]
008c74f8 or ecx, dword ptr [0xbc4898]
008c74fe or ecx, dword ptr [0xbc49e8]
008c7504 or ecx, dword ptr [0xbc4868]
008c750a mov dword ptr [0xc07094], eax
008c750f not ecx
008c7511 mov eax, dword ptr [0xbc479c]
008c7516 or eax, dword ptr [0xbc489c]
008c751c or eax, dword ptr [0xbc49ec]
008c7522 or eax, dword ptr [0xbc486c]
008c7528 not eax
008c752a mov dword ptr [0xc07098], ecx
008c7530 push 0xc07084
008c7535 mov dword ptr [0xc0709c], eax
008c753a call 0x9eb225
008c753f add esp, 4
008c7542 jmp 0x8c72d7
008c7547 int3 
008c7548 int3 
008c7549 int3 
008c754a int3 
008c754b int3 
008c754c int3 
008c754d int3 
008c754e int3 
008c754f int3 
