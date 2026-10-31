; Installed-binary disassembly; field interpretations require the source review.
006a7ae0 push ebp
006a7ae1 mov ebp, esp
006a7ae3 push -1
006a7ae5 push 0x9f49b0
006a7aea mov eax, dword ptr fs:[0]
006a7af0 push eax
006a7af1 sub esp, 0xdc
006a7af7 mov eax, dword ptr [0xbaa3b4]
006a7afc xor eax, ebp
006a7afe mov dword ptr [ebp - 0x10], eax
006a7b01 push ebx
006a7b02 push esi
006a7b03 push edi
006a7b04 push eax
006a7b05 lea eax, [ebp - 0xc]
006a7b08 mov dword ptr fs:[0], eax
006a7b0e mov edi, ecx
006a7b10 mov dword ptr [ebp - 0x74], edi
006a7b13 mov esi, dword ptr [edi + 0x2c]
006a7b16 movss xmm1, dword ptr [0xb6a350]
006a7b1e cmp esi, 2
006a7b21 je 0x6a7b7d
006a7b23 cmp esi, 3
006a7b26 je 0x6a7b7d
006a7b28 cmp esi, 4
006a7b2b je 0x6a7b7d
006a7b2d mov eax, dword ptr [0xbfd65c]
006a7b32 mov byte ptr [ebp - 0x69], 0
006a7b36 mov eax, dword ptr [eax + 0x18190]
006a7b3c movss xmm0, dword ptr [eax + 0x7134]
006a7b44 comiss xmm0, xmm1
006a7b47 jbe 0x6a7b81
006a7b49 push dword ptr [edi + 0x20]
006a7b4c push 5
006a7b4e call 0x684790
006a7b53 test al, al
006a7b55 je 0x6a7b81
006a7b57 mov edx, dword ptr [edi]
006a7b59 lea ecx, [ebp - 0xe8]
006a7b5f push 0x1e
006a7b61 call 0x427290
006a7b66 push eax
006a7b67 push 0
006a7b69 push 0
006a7b6b push ecx
006a7b6c mov ecx, edi
006a7b6e mov dword ptr [esp], 0x3f800000
006a7b75 call dword ptr [edx + 0x20]
006a7b78 mov esi, dword ptr [edi + 0x2c]
006a7b7b jmp 0x6a7b81
006a7b7d mov byte ptr [ebp - 0x69], 1
006a7b81 cmp esi, 0xb
006a7b84 jne 0x6a7b92
006a7b86 mov ecx, edi
006a7b88 call 0x4e7250
006a7b8d jmp 0x6a8a1d
006a7b92 cmp esi, 0xa
006a7b95 je 0x6a8a16
006a7b9b cmp esi, 0xc
006a7b9e je 0x6a8a16
006a7ba4 cmp esi, 0xd
006a7ba7 je 0x6a8a16
006a7bad mov eax, dword ptr [edi + 0xab4]
006a7bb3 mov ebx, dword ptr [edi + 0x32c]
006a7bb9 mov dword ptr [ebp - 0x84], ebx
006a7bbf test eax, eax
006a7bc1 jne 0x6a7e23
006a7bc7 mov eax, dword ptr [edi + 0x164]
006a7bcd lea ecx, [ebp - 0xc0]
006a7bd3 or dword ptr [edi + 0x160], 0x40000
006a7bdd push 0x23
006a7bdf push dword ptr [edi + 0x344]
006a7be5 mov dword ptr [edi + 0x164], eax
006a7beb call 0x7a7cd0
006a7bf0 mov esi, dword ptr [0xbfd65c]
006a7bf6 mov ecx, dword ptr [esi + 0x18190]
006a7bfc call 0x7cf750
006a7c01 test eax, eax
006a7c03 jne 0x6a7c43
006a7c05 cmp dword ptr [edi + 0x2c], 2
006a7c09 jne 0x6a7c2d
006a7c0b push 0x64
006a7c0d lea ecx, [ebp - 0xc0]
006a7c13 call 0x7a7d50
006a7c18 test eax, eax
006a7c1a jne 0x6a7c2d
006a7c1c push -1
006a7c1e push dword ptr [edi + 0x30]
006a7c21 mov ecx, edi
006a7c23 push 3
006a7c25 push dword ptr [edi + 0x28]
006a7c28 call 0x697c60
006a7c2d push 3
006a7c2f lea ecx, [ebp - 0xc0]
006a7c35 call 0x7a7d50
006a7c3a mov esi, dword ptr [0xbfd65c]
006a7c40 mov dword ptr [edi + 0x30], eax
006a7c43 mov eax, dword ptr [edi + 0x294]
006a7c49 lea ebx, [edi + 0x294]
006a7c4f mov dword ptr [edi + 0x28c], eax
006a7c55 mov eax, dword ptr [ebx + 4]
006a7c58 mov dword ptr [edi + 0x290], eax
006a7c5e call 0x6c3d90
006a7c63 xor edx, edx
006a7c65 movss xmm0, dword ptr [edi + 0x2d8]
006a7c6d mov ecx, 0x1e
006a7c72 div ecx
006a7c74 mov ecx, dword ptr [edi + 0x160]
006a7c7a mov eax, dword ptr [edi + 0x164]
006a7c80 and ecx, 0xfffffffb
006a7c83 add edx, 0x3c
006a7c86 mov dword ptr [edi + 0x164], eax
006a7c8c or ecx, 0x42050011
006a7c92 mov dword ptr [edi + 0xaf0], edx
006a7c98 comiss xmm0, dword ptr [0xb6a6f0]
006a7c9f mov dword ptr [edi + 0x160], ecx
006a7ca5 jbe 0x6a7ce8
006a7ca7 mov eax, dword ptr [esi + 0x18190]
006a7cad movss xmm0, dword ptr [eax + 0x7134]
006a7cb5 comiss xmm0, dword ptr [0xb6a18c]
006a7cbc jbe 0x6a7ccd
006a7cbe cmp byte ptr [ebp - 0x69], 0
006a7cc2 jne 0x6a7ccd
006a7cc4 cmp dword ptr [ebp - 0x84], 0
006a7ccb je 0x6a7cde
006a7ccd mov ecx, esi
006a7ccf call 0x71b600
006a7cd4 mov esi, dword ptr [0xbfd65c]
006a7cda test al, al
006a7cdc je 0x6a7ce8
006a7cde mov dword ptr [edi + 0x2d8], 0x3f800000
006a7ce8 movss xmm0, dword ptr [edi + 0x2d8]
006a7cf0 comiss xmm0, dword ptr [0xb6a6f0]
006a7cf7 jbe 0x6a7db7
006a7cfd cmp dword ptr [ebp - 0x84], 0
006a7d04 jne 0x6a7d21
006a7d06 mov esi, dword ptr [esi + 0x18190]
006a7d0c mov ecx, esi
006a7d0e push 0x3b6
006a7d13 push ebx
006a7d14 call 0x7ce950
006a7d19 push eax
006a7d1a mov ecx, esi
006a7d1c call 0x447f40
006a7d21 mov eax, dword ptr [edi + 0x30]
006a7d24 lea ecx, [edi + 0x3c]
006a7d27 push 0
006a7d29 mov dword ptr [edi + 0xab4], 8
006a7d33 push dword ptr [eax*4 + 0xb46d20]
006a7d3a call 0x4054f0
006a7d3f lea ecx, [edi + 0x6c]
006a7d42 call 0x432ec0
006a7d47 mov ecx, eax
006a7d49 test ecx, ecx
006a7d4b jle 0x6a7d60
006a7d4d mov eax, dword ptr [edi + 0x344]
006a7d53 xor edx, edx
006a7d55 div ecx
006a7d57 lea ecx, [edi + 0x3c]
006a7d5a push edx
006a7d5b call 0x405890
006a7d60 movss xmm1, dword ptr [edi + 0x2d8]
006a7d68 lea ecx, [edi + 0x3c]
006a7d6b divss xmm1, dword ptr [edi + 0x2dc]
006a7d73 push 1
006a7d75 movaps xmm0, xmm1
006a7d78 mulss xmm1, dword ptr [0xbc7a2c]
006a7d80 mulss xmm0, dword ptr [0xbc7a28]
006a7d88 movss dword ptr [ebp - 0x70], xmm1
006a7d8d movss dword ptr [ebp - 0x7c], xmm0
006a7d92 call 0x4062c0
006a7d97 movss xmm0, dword ptr [ebp - 0x7c]
006a7d9c mov ecx, edi
006a7d9e movss dword ptr [eax + 0x34], xmm0
006a7da3 movss xmm0, dword ptr [ebp - 0x70]
006a7da8 movss dword ptr [eax + 0x38], xmm0
006a7dad call 0x6b1270
006a7db2 jmp 0x6a8a1d
006a7db7 cmp dword ptr [ebp - 0x84], 0
006a7dbe jne 0x6a7ddb
006a7dc0 mov esi, dword ptr [esi + 0x18190]
006a7dc6 mov ecx, esi
006a7dc8 push 0x384
006a7dcd push ebx
006a7dce call 0x7ce950
006a7dd3 push eax
006a7dd4 mov ecx, esi
006a7dd6 call 0x447f40
006a7ddb mov eax, dword ptr [edi + 0x30]
006a7dde lea ecx, [edi + 0x3c]
006a7de1 push 0
006a7de3 mov dword ptr [edi + 0xab4], 3
006a7ded mov dword ptr [edi + 0x180], 0
006a7df7 push dword ptr [eax*4 + 0xb46d2c]
006a7dfe mov dword ptr [edi + 0x17c], 0
006a7e08 call 0x4054f0
006a7e0d mov ecx, edi
006a7e0f mov dword ptr [edi + 0x2ac], 0xfffffc18
006a7e19 call 0x6b1270
006a7e1e jmp 0x6a8a1d
006a7e23 cmp eax, 9
006a7e26 jne 0x6a7fb3
006a7e2c mov eax, dword ptr [edi + 0x2dc]
006a7e32 lea ecx, [edi + 0x3c]
006a7e35 mov dword ptr [edi + 0x2d8], eax
006a7e3b mov eax, dword ptr [edi + 0x30]
006a7e3e push 0
006a7e40 mov dword ptr [edi + 0xab4], 8
006a7e4a push dword ptr [eax*4 + 0xb46d20]
006a7e51 call 0x4054f0
006a7e56 lea ecx, [edi + 0x6c]
006a7e59 call 0x432ec0
006a7e5e mov ecx, eax
006a7e60 test ecx, ecx
006a7e62 jle 0x6a7e77
006a7e64 mov eax, dword ptr [edi + 0x344]
006a7e6a xor edx, edx
006a7e6c div ecx
006a7e6e lea ecx, [edi + 0x3c]
006a7e71 push edx
006a7e72 call 0x405890
006a7e77 movss xmm1, dword ptr [edi + 0x2d8]
006a7e7f lea ecx, [edi + 0x3c]
006a7e82 divss xmm1, dword ptr [edi + 0x2dc]
006a7e8a push 1
006a7e8c movaps xmm0, xmm1
006a7e8f mulss xmm1, dword ptr [0xbc7a2c]
006a7e97 mulss xmm0, dword ptr [0xbc7a28]
006a7e9f movss dword ptr [ebp - 0x70], xmm1
006a7ea4 movss dword ptr [ebp - 0x7c], xmm0
006a7ea9 call 0x4062c0
006a7eae movss xmm0, dword ptr [ebp - 0x7c]
006a7eb3 test ebx, ebx
006a7eb5 mov ebx, dword ptr [0xbfd65c]
006a7ebb movss dword ptr [eax + 0x34], xmm0
006a7ec0 movss xmm0, dword ptr [ebp - 0x70]
006a7ec5 movss dword ptr [eax + 0x38], xmm0
006a7eca mov dword ptr [edi + 0x180], 4
006a7ed4 mov dword ptr [edi + 0x2ac], 0
006a7ede jne 0x6a7f01
006a7ee0 mov esi, dword ptr [ebx + 0x18190]
006a7ee6 lea eax, [edi + 0x294]
006a7eec push 0x3b6
006a7ef1 push eax
006a7ef2 mov ecx, esi
006a7ef4 call 0x7ce950
006a7ef9 push eax
006a7efa mov ecx, esi
006a7efc call 0x447f40
006a7f01 call 0x6c3d90
006a7f06 push eax
006a7f07 push 0
006a7f09 push 0
006a7f0b push 0xc02fec
006a7f10 lea eax, [edi + 0x294]
006a7f16 mov ecx, ebx
006a7f18 push eax
006a7f19 push 0xf
006a7f1b push 0x3e8
006a7f20 call 0x422e20
006a7f25 mov dword ptr [eax + 0x2a4], 0
006a7f2f mov dword ptr [eax + 0x2a8], 0xc0c00000
006a7f39 cmp dword ptr [edi + 0x2c], 1
006a7f3d jne 0x6a7f4c
006a7f3f movss xmm1, dword ptr [0xb6a4c4]
006a7f47 xorps xmm0, xmm0
006a7f4a jmp 0x6a7f5c
006a7f4c movss xmm0, dword ptr [0xb6a480]
006a7f54 movss xmm1, dword ptr [0xb6a3f8]
006a7f5c push ecx
006a7f5d movss dword ptr [eax + 0x104], xmm1
006a7f65 mov dword ptr [eax + 0x108], 0
006a7f6f movss dword ptr [eax + 0x10c], xmm0
006a7f77 mov dword ptr [esp], 0x3f800000
006a7f7e push 0
006a7f80 push 2
006a7f82 push ecx
006a7f83 mov dword ptr [esp], 0x3f800000
006a7f8a mov ecx, edi
006a7f8c push 0x1d7
006a7f91 call 0x6ad720
006a7f96 call 0x6c3d90
006a7f9b xor edx, edx
006a7f9d mov ecx, 0x3c
006a7fa2 div ecx
006a7fa4 mov eax, dword ptr [edi + 0xab4]
006a7faa add edx, 0x5a
006a7fad mov dword ptr [edi + 0xaf0], edx
006a7fb3 cmp eax, 8
006a7fb6 jne 0x6a7fdb
006a7fb8 cmp dword ptr [edi + 0x70], 0
006a7fbc lea ecx, [edi + 0x3c]
006a7fbf je 0x6a7fca
006a7fc1 cmp byte ptr [edi + 0x80], 0
006a7fc8 jne 0x6a7fdb
006a7fca mov eax, dword ptr [edi + 0x30]
006a7fcd push 0
006a7fcf push dword ptr [eax*4 + 0xb46d20]
006a7fd6 call 0x4054f0
006a7fdb movss xmm1, dword ptr [edi + 0x28c]
006a7fe3 lea ebx, [edi + 0x294]
006a7fe9 movss xmm0, dword ptr [edi + 0x290]
006a7ff1 subss xmm1, dword ptr [ebx]
006a7ff5 subss xmm0, dword ptr [ebx + 4]
006a7ffa mov dword ptr [ebp - 0x88], ebx
006a8000 movss dword ptr [edi + 0x2b8], xmm1
006a8008 xorps xmm1, xmm1
006a800b movss dword ptr [edi + 0x2bc], xmm0
006a8013 movss xmm0, dword ptr [edi + 0x14]
006a8018 comiss xmm0, xmm1
006a801b ja 0x6a802a
006a801d cmp byte ptr [edi + 0x16b], 0
006a8024 je 0x6a83fc
006a802a mov eax, dword ptr [edi + 0x2c]
006a802d test eax, eax
006a802f je 0x6a8102
006a8035 cmp eax, 1
006a8038 je 0x6a8102
006a803e cmp byte ptr [ebp - 0x69], 0
006a8042 je 0x6a83e2
006a8048 cmp eax, 4
006a804b je 0x6a83e2
006a8051 cmp dword ptr [edi + 0xab4], 8
006a8058 jne 0x6a83e2
006a805e mov eax, dword ptr [edi + 0x18]
006a8061 and eax, 4
006a8064 or eax, 0
006a8067 jne 0x6a8075
006a8069 cmp byte ptr [edi + 0x16b], al
006a806f je 0x6a83fc
006a8075 mov eax, dword ptr [edi + 0x30]
006a8078 lea ecx, [edi + 0x3c]
006a807b push 0
006a807d mov dword ptr [edi + 0x2d8], 0x3f800000
006a8087 mov dword ptr [edi + 0xab4], 3
006a8091 push dword ptr [eax*4 + 0xb46d2c]
006a8098 mov dword ptr [edi + 0x180], 0
006a80a2 mov dword ptr [edi + 0x17c], 0
006a80ac call 0x4054f0
006a80b1 push ecx
006a80b2 mov dword ptr [esp], 0x3f800000
006a80b9 push 0
006a80bb push 2
006a80bd push ecx
006a80be mov dword ptr [esp], 0x3f59999a
006a80c5 mov ecx, edi
006a80c7 push 0x105
006a80cc mov dword ptr [edi + 0x2ac], 0xfffffc18
006a80d6 call 0x6ad720
006a80db call 0x6c3d90
006a80e0 mov ecx, dword ptr [0xbfd65c]
006a80e6 push eax
006a80e7 push 0
006a80e9 push 0
006a80eb push 0xc02fec
006a80f0 push ebx
006a80f1 push 0xf
006a80f3 push 0x3e8
006a80f8 call 0x422e20
006a80fd jmp 0x6a8328
006a8102 cmp byte ptr [edi + 0x16b], 0
006a8109 mov byte ptr [ebp - 0x69], 0
006a810d jne 0x6a8123
006a810f mov eax, dword ptr [edi + 0x18]
006a8112 and eax, 4
006a8115 or eax, 0
006a8118 jne 0x6a8123
006a811a comiss xmm0, dword ptr [0xb6accc]
006a8121 jb 0x6a8127
006a8123 mov byte ptr [ebp - 0x69], 1
006a8127 cmp dword ptr [edi + 0xab4], 8
006a812e jne 0x6a83e2
006a8134 mov esi, dword ptr [edi + 8]
006a8137 xor ecx, ecx
006a8139 movss xmm5, dword ptr [0xb6a614]
006a8141 mov eax, 0x92492493
006a8146 mov dword ptr [ebp - 0x70], ecx
006a8149 mov ecx, dword ptr [edi + 0xc]
006a814c sub ecx, esi
006a814e imul ecx
006a8150 add edx, ecx
006a8152 sar edx, 5
006a8155 mov eax, edx
006a8157 shr eax, 0x1f
006a815a add eax, edx
006a815c je 0x6a8203
006a8162 movss xmm4, dword ptr [0xb6a974]
006a816a xor ebx, ebx
006a816c movss xmm3, dword ptr [0xb6a864]
006a8174 movss xmm2, dword ptr [0xb6a7b0]
006a817c nop dword ptr [eax]
006a8180 movss xmm0, dword ptr [esi + ebx]
006a8185 comiss xmm0, xmm4
006a8188 jbe 0x6a81a1
006a818a call 0x6c3d90
006a818f xor edx, edx
006a8191 mov ecx, 3
006a8196 div ecx
006a8198 test edx, edx
006a819a jne 0x6a81b8
006a819c movaps xmm1, xmm3
006a819f jmp 0x6a81c0
006a81a1 comiss xmm0, xmm1
006a81a4 jbe 0x6a81d7
006a81a6 call 0x6c3d90
006a81ab xor edx, edx
006a81ad mov ecx, 3
006a81b2 div ecx
006a81b4 test edx, edx
006a81b6 jne 0x6a81bd
006a81b8 movaps xmm1, xmm2
006a81bb jmp 0x6a81c0
006a81bd movaps xmm1, xmm5
006a81c0 movss xmm0, dword ptr [edi + 0x2d8]
006a81c8 subss xmm0, xmm1
006a81cc xorps xmm1, xmm1
006a81cf movss dword ptr [edi + 0x2d8], xmm0
006a81d7 mov ecx, dword ptr [edi + 0xc]
006a81da mov eax, 0x92492493
006a81df mov esi, dword ptr [edi + 8]
006a81e2 add ebx, 0x38
006a81e5 inc dword ptr [ebp - 0x70]
006a81e8 sub ecx, esi
006a81ea imul ecx
006a81ec add edx, ecx
006a81ee sar edx, 5
006a81f1 mov eax, edx
006a81f3 shr eax, 0x1f
006a81f6 add eax, edx
006a81f8 cmp dword ptr [ebp - 0x70], eax
006a81fb jb 0x6a8180
006a81fd lea ebx, [edi + 0x294]
006a8203 movss xmm0, dword ptr [edi + 0x2d8]
006a820b lea esi, [edi + 0x2d8]
006a8211 comiss xmm0, xmm5
006a8214 lea eax, [ebp - 0x7c]
006a8217 mov dword ptr [ebp - 0x7c], 0x3f800000
006a821e lea ecx, [edi + 0x3c]
006a8221 push 1
006a8223 cmova eax, esi
006a8226 movss xmm1, dword ptr [eax]
006a822a movss dword ptr [esi], xmm1
006a822e divss xmm1, dword ptr [edi + 0x2dc]
006a8236 movaps xmm0, xmm1
006a8239 mulss xmm1, dword ptr [0xbc7a2c]
006a8241 mulss xmm0, dword ptr [0xbc7a28]
006a8249 movss dword ptr [ebp - 0x70], xmm1
006a824e movss dword ptr [ebp - 0x7c], xmm0
006a8253 call 0x4062c0
006a8258 movss xmm0, dword ptr [ebp - 0x7c]
006a825d movss dword ptr [eax + 0x34], xmm0
006a8262 movss xmm0, dword ptr [ebp - 0x70]
006a8267 movss dword ptr [eax + 0x38], xmm0
006a826c movss xmm0, dword ptr [0xb6a6f0]
006a8274 comiss xmm0, dword ptr [esi]
006a8277 ja 0x6a8283
006a8279 cmp byte ptr [ebp - 0x69], 0
006a827d je 0x6a83df
006a8283 cmp dword ptr [ebp - 0x84], 0
006a828a jne 0x6a82b2
006a828c mov eax, dword ptr [0xbfd65c]
006a8291 push 0x384
006a8296 push ebx
006a8297 mov esi, dword ptr [eax + 0x18190]
006a829d mov ecx, esi
006a829f call 0x7ce950
006a82a4 push eax
006a82a5 mov ecx, esi
006a82a7 call 0x447f40
006a82ac lea esi, [edi + 0x2d8]
006a82b2 mov eax, dword ptr [edi + 0x30]
006a82b5 lea ecx, [edi + 0x3c]
006a82b8 push 0
006a82ba mov dword ptr [esi], 0x3f800000
006a82c0 mov dword ptr [edi + 0xab4], 3
006a82ca push dword ptr [eax*4 + 0xb46d2c]
006a82d1 mov dword ptr [edi + 0x180], 0
006a82db mov dword ptr [edi + 0x17c], 0
006a82e5 call 0x4054f0
006a82ea push ecx
006a82eb mov dword ptr [esp], 0x3f800000
006a82f2 push 0
006a82f4 push 2
006a82f6 push ecx
006a82f7 mov dword ptr [esp], 0x3f59999a
006a82fe mov ecx, edi
006a8300 push 0x105
006a8305 mov dword ptr [edi + 0x2ac], 0xfffffc18
006a830f call 0x6ad720
006a8314 mov eax, dword ptr [edi + 0x30]
006a8317 lea ecx, [edi + 0x3c]
006a831a push 0
006a831c push dword ptr [eax*4 + 0xb4936c]
006a8323 call 0x4054f0
006a8328 push 1
006a832a lea eax, [ebp - 0xb0]
006a8330 mov ecx, edi
006a8332 push eax
006a8333 call 0x6a77b0
006a8338 mov dword ptr [ebp - 4], 0
006a833f mov eax, dword ptr [ebp - 0xa4]
006a8345 mov esi, eax
006a8347 mov ebx, dword ptr [ebp - 0xb0]
006a834d mov edi, dword ptr [ebp - 0x88]
006a8353 mov ecx, dword ptr [ebp - 0xa0]
006a8359 add eax, ecx
006a835b cmp esi, eax
006a835d je 0x6a8392
006a835f test ebx, ebx
006a8361 je 0x6a8367
006a8363 mov eax, dword ptr [ebx]
006a8365 jmp 0x6a8369
006a8367 xor eax, eax
006a8369 mov ecx, dword ptr [eax + 8]
006a836c mov eax, dword ptr [eax + 4]
006a836f dec ecx
006a8370 and ecx, esi
006a8372 push 0
006a8374 push 0xc02fec
006a8379 push edi
006a837a mov ecx, dword ptr [eax + ecx*4]
006a837d call 0x7f86d0
006a8382 mov ecx, eax
006a8384 mov edx, dword ptr [eax]
006a8386 call dword ptr [edx + 0xc]
006a8389 mov eax, dword ptr [ebp - 0xa4]
006a838f inc esi
006a8390 jmp 0x6a8353
006a8392 mov edi, dword ptr [ebp - 0x74]
006a8395 test ecx, ecx
006a8397 je 0x6a83ab
006a8399 mov eax, dword ptr [0xbfd65c]
006a839e mov eax, dword ptr [eax + 0x18190]
006a83a4 mov byte ptr [eax + 0x7778], 1
006a83ab mov ecx, edi
006a83ad call 0x6b1270
006a83b2 lea ecx, [ebp - 0xb0]
006a83b8 mov dword ptr [ebp - 4], 0xffffffff
006a83bf call 0x6b15c0
006a83c4 mov eax, dword ptr [ebp - 0xb0]
006a83ca push 8
006a83cc push eax
006a83cd mov dword ptr [ebp - 0xb0], 0
006a83d7 call 0x9eb08e
006a83dc add esp, 8
006a83df xorps xmm1, xmm1
006a83e2 cmp byte ptr [edi + 0x16b], 0
006a83e9 je 0x6a83fc
006a83eb mov dword ptr [edi + 0x2d8], 0x3f800000
006a83f5 mov byte ptr [edi + 0x16b], 0
006a83fc mov eax, dword ptr [edi + 8]
006a83ff mov dword ptr [edi + 0xc], eax
006a8402 mov dword ptr [edi + 0x14], 0
006a8409 mov dword ptr [edi + 0x18], 0
006a8410 mov dword ptr [edi + 0x1c], 0
006a8417 mov eax, dword ptr [edi + 0x2c]
006a841a cmp eax, 1
006a841d je 0x6a8428
006a841f cmp eax, 3
006a8422 jne 0x6a85b6
006a8428 mov eax, dword ptr [edi + 0x34]
006a842b cmp eax, 0x389
006a8430 je 0x6a85b6
006a8436 cmp eax, 0x397
006a843b je 0x6a85b6
006a8441 cmp dword ptr [edi + 0xaf0], 0
006a8448 jg 0x6a85b6
006a844e cmp dword ptr [edi + 0xab4], 8
006a8455 jne 0x6a85b6
006a845b call 0x6c3d90
006a8460 xor edx, edx
006a8462 mov ecx, 5
006a8467 div ecx
006a8469 test edx, edx
006a846b jne 0x6a85b6
006a8471 movss xmm0, dword ptr [edi + 0x294]
006a8479 lea ebx, [edi + 0x294]
006a847f mov ecx, dword ptr [0xbfd65c]
006a8485 addss xmm0, xmm1
006a8489 push ebx
006a848a movss dword ptr [ebp - 0x70], xmm0
006a848f movss xmm0, dword ptr [ebx + 4]
006a8494 subss xmm0, dword ptr [0xb6a9ac]
006a849c movss dword ptr [ebp - 0x7c], xmm0
006a84a1 call 0x6d5e30
006a84a6 lea ecx, [ebp - 0x9c]
006a84ac movss xmm1, dword ptr [eax + 0x294]
006a84b4 movss xmm0, dword ptr [eax + 0x298]
006a84bc lea eax, [ebp - 0xb8]
006a84c2 movss dword ptr [ebp - 0x94], xmm1
006a84ca subss xmm1, dword ptr [ebp - 0x70]
006a84cf movss dword ptr [ebp - 0x90], xmm0
006a84d7 subss xmm0, dword ptr [ebp - 0x7c]
006a84dc push eax
006a84dd movss dword ptr [ebp - 0x88], xmm1
006a84e5 movss dword ptr [ebp - 0x9c], xmm1
006a84ed movss dword ptr [ebp - 0x74], xmm0
006a84f2 movss dword ptr [ebp - 0x98], xmm0
006a84fa call 0x962560
006a84ff movss xmm0, dword ptr [eax]
006a8503 mulss xmm0, dword ptr [0xb6a9ec]
006a850b movss xmm1, dword ptr [eax + 4]
006a8510 mulss xmm1, dword ptr [0xb6a9ec]
006a8518 addss xmm0, dword ptr [ebp - 0x70]
006a851d addss xmm1, dword ptr [ebp - 0x7c]
006a8522 movss dword ptr [ebp - 0x9c], xmm0
006a852a movss xmm0, dword ptr [ebp - 0x74]
006a852f movss dword ptr [ebp - 0x98], xmm1
006a8537 movss xmm1, dword ptr [ebp - 0x88]
006a853f mulss xmm0, xmm0
006a8543 mulss xmm1, xmm1
006a8547 addss xmm0, xmm1
006a854b call 0x4228c0
006a8550 movss xmm1, dword ptr [0xb6ab70]
006a8558 comiss xmm1, xmm0
006a855b jbe 0x6a85cd
006a855d mov ecx, dword ptr [0xbfd65c]
006a8563 lea eax, [ebp - 0x94]
006a8569 push 0
006a856b push 0
006a856d push 0
006a856f mov ecx, dword ptr [ecx + 0x18190]
006a8575 push 0
006a8577 push 3
006a8579 push eax
006a857a lea eax, [ebp - 0x9c]
006a8580 push eax
006a8581 call 0x7af4b0
006a8586 test al, al
006a8588 je 0x6a85cd
006a858a call 0x6c3d90
006a858f xor edx, edx
006a8591 mov ecx, 0xf
006a8596 div ecx
006a8598 test edx, edx
006a859a jne 0x6a85cd
006a859c push edx
006a859d push 0xb400ac
006a85a2 lea ecx, [edi + 0x3c]
006a85a5 call 0x405a00
006a85aa mov dword ptr [edi + 0xaf0], 0x54
006a85b4 jmp 0x6a85cd
006a85b6 mov eax, dword ptr [edi + 0xaf0]
006a85bc lea ebx, [edi + 0x294]
006a85c2 test eax, eax
006a85c4 jle 0x6a85cd
006a85c6 dec eax
006a85c7 mov dword ptr [edi + 0xaf0], eax
006a85cd cmp byte ptr [edi + 0xa0], 0
006a85d4 je 0x6a87b4
006a85da lea ecx, [edi + 0x8c]
006a85e0 push 0
006a85e2 call 0x405d30
006a85e7 mov dword ptr [ebp - 0x74], eax
006a85ea test eax, eax
006a85ec je 0x6a8651
006a85ee push 1
006a85f0 lea ecx, [edi + 0x3c]
006a85f3 call 0x4062c0
006a85f8 mov edx, dword ptr [ebp - 0x74]
006a85fb push 1
006a85fd mov ecx, dword ptr [edx]
006a85ff mov dword ptr [eax + 0x40], ecx
006a8602 mov ecx, dword ptr [edx + 4]
006a8605 mov dword ptr [eax + 0x44], ecx
006a8608 lea ecx, [edi + 0x3c]
006a860b movss xmm1, dword ptr [edi + 0x2d8]
006a8613 divss xmm1, dword ptr [edi + 0x2dc]
006a861b movaps xmm0, xmm1
006a861e mulss xmm1, dword ptr [edx + 0x14]
006a8623 mulss xmm0, dword ptr [edx + 0x10]
006a8628 movss dword ptr [ebp - 0x88], xmm1
006a8630 movss dword ptr [ebp - 0x74], xmm0
006a8635 call 0x4062c0
006a863a movss xmm0, dword ptr [ebp - 0x74]
006a863f movss dword ptr [eax + 0x34], xmm0
006a8644 movss xmm0, dword ptr [ebp - 0x88]
006a864c movss dword ptr [eax + 0x38], xmm0
006a8651 push 0xb400ac
006a8656 lea ecx, [edi + 0x8c]
006a865c call 0x405e90
006a8661 test al, al
006a8663 je 0x6a87b4
006a8669 mov eax, dword ptr [edi + 0x34]
006a866c cmp eax, 0x389
006a8671 je 0x6a87b4
006a8677 cmp eax, 0x397
006a867c je 0x6a87b4
006a8682 movss xmm0, dword ptr [ebx]
006a8686 addss xmm0, dword ptr [0xb6a18c]
006a868e mov ecx, dword ptr [0xbfd65c]
006a8694 push ebx
006a8695 movss dword ptr [ebp - 0x78], xmm0
006a869a movss xmm0, dword ptr [ebx + 4]
006a869f subss xmm0, dword ptr [0xb6a9ac]
006a86a7 movss dword ptr [ebp - 0x74], xmm0
006a86ac call 0x6d5e30
006a86b1 lea ecx, [ebp - 0x8c]
006a86b7 movss xmm0, dword ptr [eax + 0x294]
006a86bf movss xmm1, dword ptr [eax + 0x298]
006a86c7 lea eax, [ebp - 0xb8]
006a86cd subss xmm0, dword ptr [ebp - 0x78]
006a86d2 subss xmm1, dword ptr [ebp - 0x74]
006a86d7 push eax
006a86d8 movss dword ptr [ebp - 0x8c], xmm0
006a86e0 movss dword ptr [ebp - 0x88], xmm1
006a86e8 call 0x962560
006a86ed movss xmm1, dword ptr [eax + 4]
006a86f2 movss xmm0, dword ptr [eax]
006a86f6 mulss xmm0, dword ptr [0xb6a9ec]
006a86fe mulss xmm1, dword ptr [0xb6a9ec]
006a8706 addss xmm0, dword ptr [ebp - 0x78]
006a870b addss xmm1, dword ptr [ebp - 0x74]
006a8710 movss dword ptr [ebp - 0x78], xmm0
006a8715 movss dword ptr [ebp - 0x74], xmm1
006a871a call 0x6c3d90
006a871f mov esi, eax
006a8721 lea ecx, [ebp - 0x8c]
006a8727 lea eax, [ebp - 0xb8]
006a872d push eax
006a872e call 0x962560
006a8733 mov ecx, dword ptr [0xbfd65c]
006a8739 push 0
006a873b push 0xbeabf4
006a8740 movss xmm0, dword ptr [eax]
006a8744 mulss xmm0, dword ptr [0xb6a8f4]
006a874c push 0xbeab18
006a8751 push 0
006a8753 push esi
006a8754 push 0
006a8756 movss dword ptr [ebp - 0x94], xmm0
006a875e movss xmm0, dword ptr [eax + 4]
006a8763 lea eax, [ebp - 0x94]
006a8769 mulss xmm0, dword ptr [0xb6a8f4]
006a8771 push edi
006a8772 push eax
006a8773 lea eax, [ebp - 0x78]
006a8776 push eax
006a8777 push 0
006a8779 push 9
006a877b movss dword ptr [ebp - 0x90], xmm0
006a8783 call 0x422e20
006a8788 push eax
006a8789 call 0x9ec34c
006a878e add esp, 0x14
006a8791 cmp dword ptr [edi + 0x2c], 3
006a8795 jne 0x6a87b4
006a8797 mov ecx, dword ptr [eax + 0x38c]
006a879d or dword ptr [eax + 0x388], 1
006a87a4 mov dword ptr [eax + 0x38c], ecx
006a87aa mov dword ptr [eax + 0x370], 0x3fc00000
006a87b4 cmp dword ptr [edi + 0xab4], 8
006a87bb jne 0x6a89e1
006a87c1 call 0x6c3d90
006a87c6 xor edx, edx
006a87c8 mov ecx, 7
006a87cd div ecx
006a87cf test edx, edx
006a87d1 jne 0x6a89e1
006a87d7 call 0x6c3d90
006a87dc movss xmm3, dword ptr [0xb6a19c]
006a87e4 movd xmm0, eax
006a87e8 cvtdq2pd xmm0, xmm0
006a87ec shr eax, 0x1f
006a87ef addsd xmm0, qword ptr [eax*8 + 0xb6c940]
006a87f8 cvtpd2ps xmm2, xmm0
006a87fc mulss xmm2, xmm3
006a8800 call 0x6c3d90
006a8805 movss xmm1, dword ptr [0xb6aed0]
006a880d mulss xmm2, dword ptr [0xb6a9ac]
006a8815 movd xmm0, eax
006a8819 cvtdq2pd xmm0, xmm0
006a881d shr eax, 0x1f
006a8820 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
006a8829 cvtpd2ps xmm0, xmm0
006a882d mulss xmm0, xmm3
006a8831 mulss xmm0, dword ptr [0xb6a9b0]
006a8839 subss xmm0, dword ptr [0xb6a940]
006a8841 addss xmm0, dword ptr [ebx]
006a8845 movss dword ptr [ebp - 0x80], xmm0
006a884a movss xmm0, dword ptr [edi + 0x2d8]
006a8852 mulss xmm0, dword ptr [0xb6a9ac]
006a885a divss xmm0, dword ptr [0xb6a910]
006a8862 subss xmm1, xmm0
006a8866 subss xmm1, xmm2
006a886a addss xmm1, dword ptr [ebx + 4]
006a886f movss dword ptr [ebp - 0x7c], xmm1
006a8874 call 0x6c3d90
006a8879 movd xmm0, eax
006a887d cvtdq2pd xmm0, xmm0
006a8881 shr eax, 0x1f
006a8884 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
006a888d cvtpd2ps xmm1, xmm0
006a8891 mulss xmm1, xmm3
006a8895 call 0x6c3d90
006a889a mulss xmm1, dword ptr [0xb6ae58]
006a88a2 movd xmm0, eax
006a88a6 cvtdq2pd xmm0, xmm0
006a88aa shr eax, 0x1f
006a88ad subss xmm1, dword ptr [0xb6a560]
006a88b5 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
006a88be movss dword ptr [ebp - 0x90], xmm1
006a88c6 cvtpd2ps xmm0, xmm0
006a88ca mulss xmm0, xmm3
006a88ce mulss xmm0, dword ptr [0xb6a434]
006a88d6 subss xmm0, dword ptr [0xb6a350]
006a88de movss dword ptr [ebp - 0x94], xmm0
006a88e6 call 0x6c3d90
006a88eb mov ecx, dword ptr [0xbfd65c]
006a88f1 push eax
006a88f2 push 0
006a88f4 push edi
006a88f5 lea eax, [ebp - 0x94]
006a88fb push eax
006a88fc lea eax, [ebp - 0x80]
006a88ff push eax
006a8900 push 0x42
006a8902 push 0x3e8
006a8907 call 0x422e20
006a890c mov esi, eax
006a890e mov eax, dword ptr [edi + 0x2c]
006a8911 cmp eax, 1
006a8914 jne 0x6a894d
006a8916 movss xmm3, dword ptr [0xb6a3b0]
006a891e lea ecx, [ebp - 0x3c]
006a8921 movss xmm2, dword ptr [0xb6a480]
006a8929 movss xmm1, dword ptr [0xb6a614]
006a8931 mov edx, dword ptr [esi]
006a8933 push eax
006a8934 push 0
006a8936 push 0xff
006a893b push -1
006a893d call 0x427080
006a8942 push eax
006a8943 mov ecx, esi
006a8945 call dword ptr [edx + 0x38]
006a8948 jmp 0x6a89e1
006a894d cmp eax, 2
006a8950 jne 0x6a8982
006a8952 movaps xmm0, xmmword ptr [0xb6c610]
006a8959 movups xmmword ptr [ebp - 0x3c], xmm0
006a895d movaps xmm0, xmmword ptr [0xb6c6f0]
006a8964 movups xmmword ptr [ebp - 0x2c], xmm0
006a8968 mov dword ptr [ebp - 0x1c], 0
006a896f lea ecx, [ebp - 0x3c]
006a8972 mov dword ptr [ebp - 0x18], 0
006a8979 mov dword ptr [ebp - 0x14], 0
006a8980 jmp 0x6a89ce
006a8982 cmp eax, 3
006a8985 jne 0x6a899b
006a8987 movaps xmm0, xmmword ptr [0xb6c610]
006a898e movups xmmword ptr [ebp - 0x3c], xmm0
006a8992 movaps xmm0, xmmword ptr [0xb6c570]
006a8999 jmp 0x6a8964
006a899b cmp eax, 4
006a899e jne 0x6a89e1
006a89a0 movaps xmm0, xmmword ptr [0xb6c610]
006a89a7 lea ecx, [ebp - 0x68]
006a89aa movups xmmword ptr [ebp - 0x68], xmm0
006a89ae mov dword ptr [ebp - 0x48], 0
006a89b5 movaps xmm0, xmmword ptr [0xb6c700]
006a89bc movups xmmword ptr [ebp - 0x58], xmm0
006a89c0 mov dword ptr [ebp - 0x44], 0
006a89c7 mov dword ptr [ebp - 0x40], 0
006a89ce mov eax, dword ptr [esi]
006a89d0 push 1
006a89d2 push 0
006a89d4 push 0xff
006a89d9 push -1
006a89db push ecx
006a89dc mov ecx, esi
006a89de call dword ptr [eax + 0x38]
006a89e1 cmp dword ptr [edi + 0xab4], 3
006a89e8 jne 0x6a8a1d
006a89ea push dword ptr [ebx + 4]
006a89ed mov ecx, dword ptr [0xbfd65c]
006a89f3 push dword ptr [ebx]
006a89f5 mov ecx, dword ptr [ecx + 0x18190]
006a89fb call 0x7aee40
006a8a00 test eax, eax
006a8a02 je 0x6a8a1d
006a8a04 cmp dword ptr [ebp - 0x84], 0
006a8a0b jne 0x6a8a1d
006a8a0d mov eax, dword ptr [edi]
006a8a0f mov ecx, edi
006a8a11 call dword ptr [eax + 0x28]
006a8a14 jmp 0x6a8a1d
006a8a16 mov ecx, edi
006a8a18 call 0x6a7090
006a8a1d mov ecx, dword ptr [ebp - 0xc]
006a8a20 mov dword ptr fs:[0], ecx
006a8a27 pop ecx
006a8a28 pop edi
006a8a29 pop esi
006a8a2a pop ebx
006a8a2b mov ecx, dword ptr [ebp - 0x10]
006a8a2e xor ecx, ebp
006a8a30 call 0x9eacd7
006a8a35 mov esp, ebp
006a8a37 pop ebp
006a8a38 ret
