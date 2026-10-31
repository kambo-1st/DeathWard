008c7950 add bh, al
008c7952 xchg dword ptr [ebx + eax], ebx
008c7959 add byte ptr [eax], al
008c795b mov dword ptr [edi + 0x3a0], 0
008c7965 mov dword ptr [edi + 0x3a4], 0
008c796f mov dword ptr [edi + 0x44c], 0
008c7979 mov dword ptr [edi + 0x448], 0
008c7983 mov dword ptr [edi + 0x3a8], 0
008c798d mov word ptr [edi + 0x3ac], 0xff01
008c7996 mov dword ptr [edi + 0x17c], 3
008c79a0 mov dword ptr [edi + 0x3b0], 0
008c79aa mov dword ptr [edi + 0x408], 0
008c79b4 mov byte ptr [edi + 0x3ae], 0
008c79bb mov byte ptr [edi + 0x410], 0
008c79c2 mov dword ptr [edi + 0x424], 0
008c79cc mov dword ptr [edi + 0x420], 0
008c79d6 mov dword ptr [edi + 0x40c], 0x42a00000
008c79e0 mov byte ptr [edi + 0x434], 0
008c79e7 mov dword ptr [edi + 0x438], 0
008c79f1 mov byte ptr [edi + 0x450], 0
008c79f8 mov word ptr [edi + 0x464], 0
008c7a01 mov dword ptr [edi + 0x440], 0
008c7a0b mov dword ptr [edi + 0x43c], 0
008c7a15 mov dword ptr [edi + 0x454], 0
008c7a1f mov dword ptr [edi + 0x458], 0
008c7a29 mov dword ptr [edi + 0x45c], 0
008c7a33 mov dword ptr [edi + 0x460], 0
008c7a3d mov eax, dword ptr [edi + 0x470]
008c7a43 mov dword ptr [edi + 0x474], eax
008c7a49 mov eax, dword ptr [edi + 0x3fc]
008c7a4f mov dword ptr [edi + 0x400], eax
008c7a55 mov eax, dword ptr [edi + 0x3d0]
008c7a5b mov dword ptr [edi + 0x3d4], eax
008c7a61 mov eax, dword ptr [edi + 0x3e8]
008c7a67 mov dword ptr [edi + 0x3ec], eax
008c7a6d mov eax, dword ptr [edi + 0x3dc]
008c7a73 push edi
008c7a74 mov dword ptr [edi + 0x3e0], eax
008c7a7a mov dword ptr [edi + 0x444], 0
008c7a84 mov dword ptr [edi + 0x494], 0x7f800000
008c7a8e mov dword ptr [edi + 0x4a8], 0x7f800000
008c7a98 mov dword ptr [edi + 0x4ac], 0
008c7aa2 mov dword ptr [edi + 0x4b0], 0
008c7aac call 0x7fdc60
008c7ab1 pop edi
008c7ab2 pop esi
008c7ab3 pop ebx
008c7ab4 mov esp, ebp
008c7ab6 pop ebp
008c7ab7 ret 0x10
008c7aba int3 
008c7abb int3 
008c7abc int3 
008c7abd int3 
008c7abe int3 
008c7abf int3 
008c7ac0 push ebp
008c7ac1 mov ebp, esp
008c7ac3 push ecx
008c7ac4 push esi
008c7ac5 mov esi, ecx
008c7ac7 cmp byte ptr [esi + 0x468], 0
008c7ace jne 0x8c7e19
008c7ad4 mov eax, dword ptr [esi + 0x314]
008c7ada test eax, eax
008c7adc je 0x8c7ae8
008c7ade cmp dword ptr [eax + 0x28], 7
008c7ae2 je 0x8c7e19
008c7ae8 cmp byte ptr [esi + 0x169], 0
008c7aef je 0x8c7e19
008c7af5 mov eax, dword ptr [esi + 0x2c]
008c7af8 dec eax
008c7af9 cmp eax, 0xe
008c7afc ja 0x8c7e19
008c7b02 movzx eax, byte ptr [eax + 0x8c7e44]
008c7b09 jmp dword ptr [eax*4 + 0x8c7e20]
008c7b10 mov eax, dword ptr [esi + 0x320]
008c7b16 test eax, eax
008c7b18 je 0x8c7dd8
008c7b1e mov eax, dword ptr [eax + 0x28]
008c7b21 movss xmm1, dword ptr [esi + 0x430]
008c7b29 add eax, -0x2b
008c7b2c movss dword ptr [ebp - 4], xmm1
008c7b31 cmp eax, 0x29
008c7b34 ja 0x8c7b68
008c7b36 movzx eax, byte ptr [eax + 0x8c7e64]
008c7b3d jmp dword ptr [eax*4 + 0x8c7e54]
008c7b44 mov dword ptr [ebp - 4], 7
008c7b4b jmp 0x8c7ddf
008c7b50 mov dword ptr [ebp - 4], 0xd3
008c7b57 jmp 0x8c7ddf
008c7b5c mov dword ptr [ebp - 4], 0x87
008c7b63 jmp 0x8c7ddf
008c7b68 mov eax, dword ptr [esi + 0x30]
008c7b6b test eax, eax
008c7b6d jne 0x8c7b9e
008c7b6f movss xmm0, dword ptr [0xb6a53c]
008c7b77 movss xmm2, dword ptr [0xb6a614]
008c7b7f comiss xmm0, xmm1
008c7b82 push ecx
008c7b83 mov dword ptr [esp], 0x3f800000
008c7b8a push eax
008c7b8b push 2
008c7b8d seta al
008c7b90 add eax, 5
008c7b93 push eax
008c7b94 call 0x8b1480
008c7b99 pop esi
008c7b9a mov esp, ebp
008c7b9c pop ebp
008c7b9d ret 
008c7b9e cmp eax, 2
008c7ba1 jne 0x8c7e19
008c7ba7 movss xmm0, dword ptr [0xb6a53c]
008c7baf movss xmm2, dword ptr [0xb6a4c4]
008c7bb7 push ecx
008c7bb8 mov dword ptr [esp], 0x3f800000
008c7bbf push 0
008c7bc1 push eax
008c7bc2 xor eax, eax
008c7bc4 comiss xmm0, xmm1
008c7bc7 seta al
008c7bca add eax, 5
008c7bcd push eax
008c7bce call 0x8b1480
008c7bd3 movss xmm0, dword ptr [0xb6a53c]
008c7bdb xor eax, eax
008c7bdd comiss xmm0, dword ptr [ebp - 4]
008c7be1 push ecx
008c7be2 mov dword ptr [esp], 0x3f800000
008c7be9 push 0
008c7beb push 2
008c7bed movss xmm2, dword ptr [0xb6a614]
008c7bf5 setbe al
008c7bf8 lea eax, [eax*2 + 0x10f]
008c7bff push eax
008c7c00 call 0x8b1480
008c7c05 pop esi
008c7c06 mov esp, ebp
008c7c08 pop ebp
008c7c09 ret 
008c7c0a mov eax, dword ptr [esi + 0x30]
008c7c0d cmp eax, 2
008c7c10 jne 0x8c7c5f
008c7c12 mov esi, dword ptr [0xbfd680]
008c7c18 lea ecx, [ebp - 4]
008c7c1b mov dword ptr [ebp - 4], 0xa
008c7c22 call 0x8b1340
008c7c27 sub esp, 8
008c7c2a mov dword ptr [esp + 4], 0
008c7c32 mov dword ptr [esp], 0x3f800000
008c7c39 push 0
008c7c3b push 2
008c7c3d push ecx
008c7c3e mov dword ptr [esp], 0x3f19999a
008c7c45 lea ecx, [esi + 0x29de0]
008c7c4b push dword ptr [ebp - 4]
008c7c4e call 0x888de0
008c7c53 mov dword ptr [ebp - 4], 0x111
008c7c5a jmp 0x8c7ddf
008c7c5f cmp eax, 1
008c7c62 je 0x8c7e19
008c7c68 mov dword ptr [ebp - 4], 0xa
008c7c6f jmp 0x8c7ddf
008c7c74 mov dword ptr [ebp - 4], 0x24d
008c7c7b jmp 0x8c7ddf
008c7c80 movss xmm1, dword ptr [esi + 0x430]
008c7c88 movss xmm2, dword ptr [0xb6a614]
008c7c90 call 0x6c3d90
008c7c95 movss xmm4, dword ptr [0xb6a588]
008c7c9d movd xmm0, eax
008c7ca1 cvtdq2pd xmm0, xmm0
008c7ca5 shr eax, 0x1f
008c7ca8 cmp dword ptr [esi + 0x30], 2
008c7cac addsd xmm0, qword ptr [eax*8 + 0xb6c940]
008c7cb5 cvtpd2ps xmm3, xmm0
008c7cb9 movss xmm0, dword ptr [0xb6a53c]
008c7cc1 mulss xmm3, dword ptr [0xb6a19c]
008c7cc9 mulss xmm3, dword ptr [0xb6a3b0]
008c7cd1 addss xmm3, xmm4
008c7cd5 jne 0x8c7cfb
008c7cd7 comiss xmm0, xmm1
008c7cda mov eax, 0x10f
008c7cdf jbe 0x8c7ceb
008c7ce1 mov eax, 0x110
008c7ce6 movaps xmm2, xmm4
008c7ce9 jmp 0x8c7d2a
008c7ceb comiss xmm1, dword ptr [0xb6a6e0]
008c7cf2 jbe 0x8c7d2a
008c7cf4 mov eax, 0x111
008c7cf9 jmp 0x8c7d22
008c7cfb comiss xmm0, xmm1
008c7cfe mov eax, 0x85
008c7d03 jbe 0x8c7d14
008c7d05 movss xmm2, dword ptr [0xb6a480]
008c7d0d mov eax, 0x86
008c7d12 jmp 0x8c7d2a
008c7d14 comiss xmm1, dword ptr [0xb6a6e0]
008c7d1b jbe 0x8c7d2a
008c7d1d mov eax, 0x87
008c7d22 movss xmm2, dword ptr [0xb6a64c]
008c7d2a mov ecx, dword ptr [esi + 0x320]
008c7d30 test ecx, ecx
008c7d32 je 0x8c7d5b
008c7d34 mov ecx, dword ptr [ecx + 0x28]
008c7d37 cmp ecx, 1
008c7d3a je 0x8c7d53
008c7d3c cmp ecx, 3
008c7d3f je 0x8c7d53
008c7d41 cmp ecx, 0xc9
008c7d47 jne 0x8c7d5b
008c7d49 mulss xmm2, dword ptr [0xb6a434]
008c7d51 jmp 0x8c7d5b
008c7d53 mulss xmm2, dword ptr [0xb6a5a4]
008c7d5b push ecx
008c7d5c movss dword ptr [esp], xmm3
008c7d61 push 0
008c7d63 push 1
008c7d65 push eax
008c7d66 call 0x8b1480
008c7d6b pop esi
008c7d6c mov esp, ebp
008c7d6e pop ebp
008c7d6f ret 
008c7d70 call 0x6c3d90
008c7d75 movss xmm2, dword ptr [0xb6a4c4]
008c7d7d push ecx
008c7d7e movd xmm0, eax
008c7d82 cvtdq2pd xmm0, xmm0
008c7d86 shr eax, 0x1f
008c7d89 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
008c7d92 cvtpd2ps xmm0, xmm0
008c7d96 mulss xmm0, dword ptr [0xb6a19c]
008c7d9e mulss xmm0, dword ptr [0xb6a350]
008c7da6 addss xmm0, dword ptr [0xb6a5a4]
008c7dae movss dword ptr [esp], xmm0
008c7db3 push 0
008c7db5 push 2
008c7db7 push 0x86
008c7dbc call 0x8b1480
008c7dc1 pop esi
008c7dc2 mov esp, ebp
008c7dc4 pop ebp
008c7dc5 ret 
008c7dc6 mov dword ptr [ebp - 4], 0x114
008c7dcd jmp 0x8c7ddf
008c7dcf mov dword ptr [ebp - 4], 0x116
008c7dd6 jmp 0x8c7ddf
008c7dd8 mov dword ptr [ebp - 4], 5
008c7ddf mov esi, dword ptr [0xbfd680]
008c7de5 lea ecx, [ebp - 4]
008c7de8 call 0x8b1340
008c7ded sub esp, 8
008c7df0 mov dword ptr [esp + 4], 0
008c7df8 mov dword ptr [esp], 0x3f800000
008c7dff push 0
008c7e01 push 2
008c7e03 push ecx
008c7e04 mov dword ptr [esp], 0x3f800000
008c7e0b lea ecx, [esi + 0x29de0]
008c7e11 push dword ptr [ebp - 4]
008c7e14 call 0x888de0
008c7e19 pop esi
008c7e1a mov esp, ebp
008c7e1c pop ebp
008c7e1d ret 
008c7e1e nop 
008c7e20 adc byte ptr [ebx - 0x74], bh
008c7e23 add byte ptr [eax - 0x27ff7384], al
008c7e29 jge 0x8c7db7
008c7e2b add dh, al
008c7e2d jge 0x8c7dbb
008c7e2f add bh, cl
008c7e31 jge 0x8c7dbf
008c7e33 add byte ptr [eax + 0x7d], dh
008c7e36 mov word ptr [eax], es
008c7e38 or bh, byte ptr [esp + ecx*4]
008c7e3c je 0x8c7eba
008c7e3e mov word ptr [eax], es
008c7e40 sbb dword ptr [esi - 0x74], edi
008c7e43 add byte ptr [eax], al
008c7e45 add dword ptr [edx], eax
008c7e47 or byte ptr [ebx], al
008c7e49 add al, 8
008c7e4b add byte ptr [eax], al
008c7e4d add eax, 0x6080706
008c7e52 add al, 0x90
008c7e54 inc esp
008c7e55 jnp 0x8c7de3
008c7e57 add byte ptr [ebx + edi*2 - 0x74], bl
008c7e5b add byte ptr [eax + 0x7b], dl
008c7e5e mov word ptr [eax], es
008c7e60 push 0x8c7b
008c7e65 add eax, dword ptr [ebx]
008c7e67 add eax, dword ptr [ebx]
008c7e69 add eax, dword ptr [eax]
008c7e6b add eax, dword ptr [ebx]
008c7e6d add eax, dword ptr [ebx]
008c7e6f add eax, dword ptr [ebx]
008c7e71 add eax, dword ptr [ebx]
008c7e73 add eax, dword ptr [ebx]
008c7e75 add dword ptr [ebx], eax
008c7e77 add eax, dword ptr [ebx]
008c7e79 add eax, dword ptr [ebx]
008c7e7b add eax, dword ptr [ebx]
008c7e7d add eax, dword ptr [ebx]
008c7e7f add eax, dword ptr [ebx]
008c7e81 add eax, dword ptr [ebx]
008c7e83 add eax, dword ptr [ebx]
008c7e85 add eax, dword ptr [ebx]
008c7e87 add eax, dword ptr [ebx]
008c7e89 add eax, dword ptr [ebx]
008c7e8b add eax, dword ptr [ebx]
008c7e8d add cl, ah
008c7e8f int3 
008c7e90 push ebp
008c7e91 mov ebp, esp
008c7e93 and esp, 0xfffffff8
008c7e96 push ecx
008c7e97 movss xmm0, dword ptr [0xb6a9c8]
008c7e9f push ebx
008c7ea0 push esi
008c7ea1 push edi
008c7ea2 mov edi, ecx
008c7ea4 mov eax, dword ptr [edi + 0x384]
008c7eaa and eax, dword ptr [0xbc494c]
008c7eb0 mov esi, dword ptr [edi + 0x378]
008c7eb6 mov ecx, esi
008c7eb8 mov edx, dword ptr [edi + 0x380]
008c7ebe mov ebx, edx
008c7ec0 and ecx, dword ptr [0xbc4940]
008c7ec6 and ebx, dword ptr [0xbc4948]
008c7ecc mov dword ptr [esp + 0xc], eax
008c7ed0 mov eax, dword ptr [edi + 0x37c]
008c7ed6 and eax, dword ptr [0xbc4944]
008c7edc or ecx, eax
008c7ede jne 0x8c7ee6
008c7ee0 or ebx, dword ptr [esp + 0xc]
008c7ee4 je 0x8c7eee
008c7ee6 movss xmm0, dword ptr [0xb6ab44]
008c7eee mov eax, dword ptr [0xbfd65c]
008c7ef3 mov eax, dword ptr [eax + 0x18190]
008c7ef9 mov eax, dword ptr [eax + 4]
008c7efc mov eax, dword ptr [eax + 0x44]
008c7eff shr eax, 0xf
008c7f02 test al, 1
008c7f04 jne 0x8c7f0c
008c7f06 cmp dword ptr [edi + 0x2c], 5
008c7f0a jne 0x8c7f4a
008c7f0c mov ecx, dword ptr [edi + 0x37c]
008c7f12 mov eax, dword ptr [edi + 0x384]
008c7f18 and esi, dword ptr [0xbc4c00]
008c7f1e and ecx, dword ptr [0xbc4c04]
008c7f24 and edx, dword ptr [0xbc4c08]
008c7f2a and eax, dword ptr [0xbc4c0c]
008c7f30 or esi, ecx
008c7f32 jne 0x8c7f42
008c7f34 or edx, eax
008c7f36 jne 0x8c7f42
008c7f38 movss xmm0, dword ptr [0xb6adc4]
008c7f40 jmp 0x8c7f4a
008c7f42 movss xmm0, dword ptr [0xb6aafc]
008c7f4a mov esi, dword ptr [ebp + 8]
008c7f4d lea eax, [edi + 0x2a4]
008c7f53 push ecx
008c7f54 movss dword ptr [esp], xmm0
008c7f59 push dword ptr [edi + 0x314]
008c7f5f push eax
008c7f60 push dword ptr [ebp + 0x10]
008c7f63 push dword ptr [ebp + 0xc]
008c7f66 push esi
008c7f67 call 0x8c7f80
008c7f6c add esp, 0x18
008c7f6f mov eax, esi
008c7f71 pop edi
008c7f72 pop esi
008c7f73 pop ebx
008c7f74 mov esp, ebp
008c7f76 pop ebp
008c7f77 ret 0xc
008c7f7a int3 
008c7f7b int3 
008c7f7c int3 
008c7f7d int3 
008c7f7e int3 
008c7f7f int3 
008c7f80 push ebp
008c7f81 mov ebp, esp
008c7f83 and esp, 0xfffffff8
008c7f86 sub esp, 0x40
008c7f89 mov eax, dword ptr [ebp + 0x14]
008c7f8c movss xmm6, dword ptr [ebp + 0x1c]
008c7f91 movss xmm1, dword ptr [0xb6acd8]
008c7f99 push esi
008c7f9a mov esi, dword ptr [ebp + 8]
008c7f9d push edi
008c7f9e mov edi, dword ptr [0xbfd65c]
008c7fa4 movss dword ptr [esp + 0x20], xmm1
008c7faa cmp dword ptr [edi + 0x1c319c], 0x1e
008c7fb1 mov ecx, dword ptr [edi + 0x18190]
008c7fb7 movss xmm4, dword ptr [ecx + 0x1c]
008c7fbc movss xmm5, dword ptr [ecx + 0x14]
008c7fc1 movss xmm2, dword ptr [ecx + 0x18]
008c7fc6 movss xmm3, dword ptr [ecx + 0x20]
008c7fcb subss xmm4, dword ptr [eax]
008c7fcf subss xmm5, dword ptr [eax]
008c7fd3 subss xmm2, dword ptr [eax + 4]
008c7fd8 subss xmm3, dword ptr [eax + 4]
008c7fdd mov eax, dword ptr [ebp + 0x10]
008c7fe0 mov ecx, dword ptr [ebp + 0xc]
008c7fe3 addss xmm4, xmm6
008c7fe7 subss xmm5, xmm6
008c7feb subss xmm2, xmm6
008c7fef movss xmm0, dword ptr [eax]
008c7ff3 addss xmm3, xmm6
008c7ff7 mulss xmm0, xmm1
008c7ffb xorps xmm6, xmm6
008c7ffe movss dword ptr [esp + 0x18], xmm4
008c8004 movss xmm4, dword ptr [ecx]
008c8008 addss xmm0, xmm4
008c800c movss dword ptr [esp + 0x10], xmm5
008c8012 movss xmm5, dword ptr [ecx + 4]
008c8017 movss dword ptr [esp + 0x14], xmm2
008c801d movaps xmm2, xmm5
008c8020 movss dword ptr [esp + 0x1c], xmm3
008c8026 movaps xmm3, xmm4
008c8029 movss dword ptr [esp + 8], xmm3
008c802f movss dword ptr [esi], xmm0
008c8033 movss xmm0, dword ptr [eax + 4]
008c8038 mulss xmm0, xmm1
008c803c movss dword ptr [esp + 0xc], xmm2
008c8042 addss xmm0, xmm5
008c8046 movss dword ptr [esi + 4], xmm0
008c804b jne 0x8c81c2
008c8051 mov eax, dword ptr [ebp + 0x18]
008c8054 test eax, eax
008c8056 je 0x8c8085
008c8058 mov eax, dword ptr [eax + 0x28]
008c805b movss dword ptr [esp + 8], xmm3
008c8061 movss dword ptr [esp + 0xc], xmm2
008c8067 cmp eax, 1
008c806a je 0x8c81c2
008c8070 movss dword ptr [esp + 8], xmm3
008c8076 movss dword ptr [esp + 0xc], xmm2
008c807c cmp eax, 3
008c807f je 0x8c81c2
008c8085 mov eax, dword ptr [edi + 0x1ba54]
008c808b xor edx, edx
008c808d sub eax, dword ptr [edi + 0x1ba50]
008c8093 movaps xmm3, xmm4
008c8096 sar eax, 2
008c8099 movaps xmm2, xmm5
008c809c mov dword ptr [esp + 0x24], edx
008c80a0 movss dword ptr [esp + 8], xmm3
008c80a6 movss dword ptr [esp + 0xc], xmm2
008c80ac test eax, eax
008c80ae je 0x8c81c2
008c80b4 nop dword ptr [eax]
008c80b8 nop dword ptr [eax + eax]
008c80c0 mov ecx, dword ptr [edi + 0x1ba54]
008c80c6 mov eax, ecx
008c80c8 sub eax, dword ptr [edi + 0x1ba50]
008c80ce test eax, 0xfffffffc
008c80d3 jne 0x8c80f1
008c80d5 push 0xb3f4d0
008c80da push 3
008c80dc call 0x95e330
008c80e1 mov ecx, dword ptr [edi + 0x1ba54]
008c80e7 add esp, 8
008c80ea mov edx, dword ptr [esp + 0x24]
008c80ee xorps xmm6, xmm6
008c80f1 mov eax, dword ptr [edi + 0x1ba50]
008c80f7 sub ecx, eax
008c80f9 sar ecx, 2
008c80fc cmp edx, ecx
008c80fe jae 0x8c8103
008c8100 lea eax, [eax + edx*4]
008c8103 mov eax, dword ptr [eax]
008c8105 movss xmm1, dword ptr [eax + 0x298]
008c810d movss xmm2, dword ptr [eax + 0x294]
008c8115 mov eax, dword ptr [ebp + 0xc]
008c8118 movss xmm4, dword ptr [eax]
008c811c movss xmm3, dword ptr [eax + 4]
008c8121 subss xmm2, xmm4
008c8125 mov eax, dword ptr [ebp + 0x10]
008c8128 subss xmm1, xmm3
008c812c movss dword ptr [esp + 8], xmm4
008c8132 movss dword ptr [esp + 0xc], xmm3
008c8138 movss xmm7, dword ptr [eax]
008c813c movaps xmm5, xmm2
008c813f movaps xmm0, xmm1
008c8142 mulss xmm5, xmm7
008c8146 mulss xmm0, dword ptr [eax + 4]
008c814b mulss xmm1, xmm7
008c814f addss xmm5, xmm0
008c8153 movss xmm0, dword ptr [eax + 4]
008c8158 mulss xmm2, xmm0
008c815c subss xmm2, xmm1
008c8160 movss xmm1, dword ptr [ebp + 0x1c]
008c8165 andps xmm2, xmmword ptr [0xb6c980]
008c816c comiss xmm1, xmm2
008c816f jbe 0x8c81a0
008c8171 comiss xmm5, xmm6
008c8174 jbe 0x8c81a0
008c8176 movss xmm1, dword ptr [esp + 0x20]
008c817c comiss xmm1, xmm5
008c817f jbe 0x8c81a0
008c8181 mulss xmm7, xmm5
008c8185 mulss xmm0, xmm5
008c8189 addss xmm7, xmm4
008c818d movss dword ptr [esp + 0x20], xmm5
008c8193 addss xmm0, xmm3
008c8197 movss dword ptr [esi], xmm7
008c819b movss dword ptr [esi + 4], xmm0
008c81a0 mov edi, dword ptr [0xbfd65c]
008c81a6 inc edx
008c81a7 mov dword ptr [esp + 0x24], edx
008c81ab mov eax, dword ptr [edi + 0x1ba54]
008c81b1 sub eax, dword ptr [edi + 0x1ba50]
008c81b7 sar eax, 2
008c81ba cmp edx, eax
008c81bc jb 0x8c80c0
008c81c2 fld dword ptr [ebp + 0x1c]
008c81c5 push ecx
008c81c6 fstp dword ptr [esp]
008c81c9 call 0x9ec36a
008c81ce add esp, 4
008c81d1 test ax, ax
008c81d4 jg 0x8c86b1
008c81da movss xmm2, dword ptr [esp + 8]
008c81e0 xorps xmm5, xmm5
008c81e3 movss xmm0, dword ptr [esp + 0x10]
008c81e9 comiss xmm2, xmm0
008c81ec movss xmm3, dword ptr [esi]
008c81f0 movss xmm4, dword ptr [esi + 4]
008c81f5 subss xmm3, xmm2
008c81f9 movss xmm1, dword ptr [esp + 0xc]
008c81ff subss xmm4, xmm1
008c8203 jbe 0x8c823a
008c8205 movaps xmm6, xmm0
008c8208 movaps xmm7, xmm3
008c820b subss xmm6, xmm2
008c820f movaps xmm0, xmm4
008c8212 mulss xmm0, xmm5
008c8216 mulss xmm7, xmm6
008c821a mulss xmm6, xmm6
008c821e addss xmm7, xmm0
008c8222 addss xmm6, xmm5
008c8226 comiss xmm7, xmm6
008c8229 jb 0x8c823a
008c822b divss xmm6, xmm7
008c822f movaps xmm0, xmm6
008c8232 mulss xmm4, xmm6
008c8236 mulss xmm3, xmm0
008c823a movss xmm0, dword ptr [esp + 0x18]
008c8240 comiss xmm0, xmm2
008c8243 jbe 0x8c8277
008c8245 movaps xmm6, xmm0
008c8248 movaps xmm7, xmm3
008c824b subss xmm6, xmm2
008c824f movaps xmm0, xmm4
008c8252 mulss xmm0, xmm5
008c8256 mulss xmm7, xmm6
008c825a mulss xmm6, xmm6
008c825e addss xmm7, xmm0
008c8262 addss xmm6, xmm5
008c8266 comiss xmm7, xmm6
008c8269 jb 0x8c8277
008c826b divss xmm6, xmm7
008c826f mulss xmm3, xmm6
008c8273 mulss xmm4, xmm6
008c8277 movss xmm0, dword ptr [esp + 0x14]
008c827d comiss xmm1, xmm0
008c8280 jbe 0x8c82b4
008c8282 movaps xmm6, xmm0
008c8285 movaps xmm7, xmm4
008c8288 subss xmm6, xmm1
008c828c movaps xmm0, xmm3
008c828f mulss xmm0, xmm5
008c8293 mulss xmm7, xmm6
008c8297 mulss xmm6, xmm6
008c829b addss xmm7, xmm0
008c829f addss xmm6, xmm5
008c82a3 comiss xmm7, xmm6
008c82a6 jb 0x8c82b4
008c82a8 divss xmm6, xmm7
008c82ac mulss xmm3, xmm6
008c82b0 mulss xmm4, xmm6
008c82b4 movss xmm0, dword ptr [esp + 0x1c]
008c82ba comiss xmm0, xmm1
008c82bd jbe 0x8c82f1
008c82bf movaps xmm6, xmm0
008c82c2 movaps xmm7, xmm4
008c82c5 subss xmm6, xmm1
008c82c9 movaps xmm0, xmm3
008c82cc mulss xmm0, xmm5
008c82d0 mulss xmm7, xmm6
008c82d4 mulss xmm6, xmm6
008c82d8 addss xmm7, xmm0
008c82dc addss xmm6, xmm5
008c82e0 comiss xmm7, xmm6
008c82e3 jb 0x8c82f1
008c82e5 divss xmm6, xmm7
008c82e9 mulss xmm3, xmm6
008c82ed mulss xmm4, xmm6
008c82f1 mov ecx, dword ptr [edi + 0x18190]
008c82f7 addss xmm3, xmm2
008c82fb addss xmm4, xmm1
008c82ff mov eax, dword ptr [ecx + 4]
008c8302 movss dword ptr [esi], xmm3
008c8306 movss dword ptr [esi + 4], xmm4
008c830b mov eax, dword ptr [eax + 0x10]
008c830e mov eax, dword ptr [eax + 0x48]
008c8311 add eax, -9
008c8314 cmp eax, 3
008c8317 ja 0x8c86b1
008c831d subss xmm2, xmm3
008c8321 subss xmm1, xmm4
008c8325 lea eax, [esp + 0x28]
008c8329 push eax
008c832a movss dword ptr [esp + 0xc], xmm2
008c8330 movss dword ptr [esp + 0x10], xmm1
008c8336 call 0x7da8e0
008c833b mov eax, dword ptr [edi + 0x18190]
008c8341 mov eax, dword ptr [eax + 4]
008c8344 test eax, eax
008c8346 je 0x8c8664
008c834c mov eax, dword ptr [eax + 0x10]
008c834f test eax, eax
008c8351 je 0x8c8664
008c8357 mov eax, dword ptr [eax + 0x48]
008c835a movss xmm4, dword ptr [esp + 8]
008c8360 sub eax, 9
008c8363 movss xmm1, dword ptr [esp + 0xc]
008c8369 movaps xmm3, xmm4
008c836c movaps xmm2, xmm1
008c836f cmp eax, 3
008c8372 ja 0x8c8670
008c8378 jmp dword ptr [eax*4 + 0x8c86bc]
008c837f movss xmm6, dword ptr [esp + 0x10]
008c8385 movaps xmm3, xmm4
008c8388 addss xmm6, dword ptr [0xb6ac90]
008c8390 movss xmm0, dword ptr [esi]
008c8394 movaps xmm2, xmm1
008c8397 comiss xmm6, xmm0
008c839a jbe 0x8c8670
008c83a0 movss xmm5, dword ptr [esp + 0x14]
008c83a6 addss xmm5, dword ptr [0xb6ac04]
008c83ae comiss xmm5, dword ptr [esi + 4]
008c83b2 jbe 0x8c8670
008c83b8 subss xmm6, xmm0
008c83bc xorps xmm7, xmm7
008c83bf movaps xmm0, xmm1
008c83c2 mulss xmm0, xmm7
008c83c6 movaps xmm2, xmm6
008c83c9 mulss xmm6, xmm6
008c83cd mulss xmm2, xmm4
008c83d1 addss xmm6, xmm7
008c83d5 addss xmm2, xmm0
008c83d9 movss dword ptr [esp + 0x24], xmm2
008c83df movaps xmm2, xmm1
008c83e2 movss xmm0, dword ptr [esp + 0x24]
008c83e8 comiss xmm0, xmm6
008c83eb jb 0x8c83ff
008c83ed movaps xmm2, xmm6
008c83f0 divss xmm2, xmm0
008c83f4 movaps xmm3, xmm2
008c83f7 mulss xmm2, xmm1
008c83fb mulss xmm3, xmm4
008c83ff subss xmm5, dword ptr [esi + 4]
008c8404 movaps xmm1, xmm2
008c8407 movaps xmm0, xmm3
008c840a mulss xmm0, xmm7
008c840e mulss xmm1, xmm5
008c8412 mulss xmm5, xmm5
008c8416 addss xmm1, xmm0
008c841a addss xmm5, xmm7
008c841e comiss xmm1, xmm5
008c8421 jb 0x8c8670
008c8427 divss xmm5, xmm1
008c842b mulss xmm3, xmm5
008c842f mulss xmm2, xmm5
008c8433 jmp 0x8c8670
008c8438 movss xmm6, dword ptr [esp + 0x10]
008c843e movaps xmm3, xmm4
008c8441 addss xmm6, dword ptr [0xb6ac90]
008c8449 movss xmm7, dword ptr [esi]
008c844d movaps xmm2, xmm1
008c8450 comiss xmm6, xmm7
008c8453 jbe 0x8c8670
008c8459 movss xmm5, dword ptr [esp + 0x1c]
008c845f subss xmm5, dword ptr [0xb6ac04]
008c8467 movss xmm0, dword ptr [esi + 4]
008c846c comiss xmm0, xmm5
008c846f jbe 0x8c8670
008c8475 subss xmm6, xmm7
008c8479 movaps xmm0, xmm1
008c847c xorps xmm7, xmm7
008c847f mulss xmm0, xmm7
008c8483 movaps xmm2, xmm6
008c8486 mulss xmm6, xmm6
008c848a mulss xmm2, xmm4
008c848e addss xmm6, xmm7
008c8492 addss xmm2, xmm0
008c8496 movss dword ptr [esp + 0x24], xmm2
008c849c movaps xmm2, xmm1
008c849f movss xmm0, dword ptr [esp + 0x24]
008c84a5 comiss xmm0, xmm6
008c84a8 jb 0x8c84bc
008c84aa movaps xmm2, xmm6
008c84ad divss xmm2, xmm0
008c84b1 movaps xmm3, xmm2
008c84b4 mulss xmm2, xmm1
008c84b8 mulss xmm3, xmm4
008c84bc subss xmm5, dword ptr [esi + 4]
008c84c1 movaps xmm1, xmm2
008c84c4 movaps xmm0, xmm3
008c84c7 mulss xmm0, xmm7
008c84cb mulss xmm1, xmm5
008c84cf mulss xmm5, xmm5
008c84d3 addss xmm1, xmm0
008c84d7 addss xmm5, xmm7
008c84db comiss xmm1, xmm5
008c84de jb 0x8c8670
008c84e4 divss xmm5, xmm1
008c84e8 mulss xmm3, xmm5
008c84ec mulss xmm2, xmm5
008c84f0 jmp 0x8c8670
008c84f5 movss xmm6, dword ptr [esp + 0x18]
008c84fb movaps xmm3, xmm4
008c84fe subss xmm6, dword ptr [0xb6ac90]
008c8506 movss xmm0, dword ptr [esi]
008c850a movaps xmm2, xmm1
008c850d comiss xmm0, xmm6
008c8510 jbe 0x8c8670
008c8516 movss xmm5, dword ptr [esp + 0x14]
008c851c addss xmm5, dword ptr [0xb6ac04]
008c8524 comiss xmm5, dword ptr [esi + 4]
008c8528 jbe 0x8c8670
008c852e subss xmm6, xmm0
008c8532 xorps xmm7, xmm7
008c8535 movaps xmm0, xmm1
008c8538 mulss xmm0, xmm7
008c853c movaps xmm2, xmm6
008c853f mulss xmm6, xmm6
008c8543 mulss xmm2, xmm4
008c8547 addss xmm6, xmm7
008c854b addss xmm2, xmm0
008c854f movss dword ptr [esp + 0x24], xmm2
008c8555 movaps xmm2, xmm1
008c8558 movss xmm0, dword ptr [esp + 0x24]
008c855e comiss xmm0, xmm6
008c8561 jb 0x8c8575
008c8563 movaps xmm2, xmm6
008c8566 divss xmm2, xmm0
008c856a movaps xmm3, xmm2
008c856d mulss xmm2, xmm1
008c8571 mulss xmm3, xmm4
008c8575 subss xmm5, dword ptr [esi + 4]
008c857a movaps xmm1, xmm2
008c857d movaps xmm0, xmm3
008c8580 mulss xmm0, xmm7
008c8584 mulss xmm1, xmm5
008c8588 mulss xmm5, xmm5
008c858c addss xmm1, xmm0
008c8590 addss xmm5, xmm7
008c8594 comiss xmm1, xmm5
008c8597 jb 0x8c8670
008c859d divss xmm5, xmm1
008c85a1 mulss xmm3, xmm5
008c85a5 mulss xmm2, xmm5
008c85a9 jmp 0x8c8670
008c85ae movss xmm6, dword ptr [esp + 0x18]
008c85b4 movaps xmm3, xmm4
008c85b7 subss xmm6, dword ptr [0xb6ac90]
008c85bf movss xmm7, dword ptr [esi]
008c85c3 movaps xmm2, xmm1
008c85c6 comiss xmm7, xmm6
008c85c9 jbe 0x8c8670
008c85cf movss xmm5, dword ptr [esp + 0x1c]
008c85d5 subss xmm5, dword ptr [0xb6ac04]
008c85dd movss xmm0, dword ptr [esi + 4]
008c85e2 comiss xmm0, xmm5
008c85e5 jbe 0x8c8670
008c85eb subss xmm6, xmm7
008c85ef movaps xmm0, xmm1
008c85f2 xorps xmm7, xmm7
008c85f5 mulss xmm0, xmm7
008c85f9 movaps xmm2, xmm6
008c85fc mulss xmm6, xmm6
008c8600 mulss xmm2, xmm4
008c8604 addss xmm6, xmm7
008c8608 addss xmm2, xmm0
008c860c movss dword ptr [esp + 0x24], xmm2
008c8612 movaps xmm2, xmm1
008c8615 movss xmm0, dword ptr [esp + 0x24]
008c861b comiss xmm0, xmm6
008c861e jb 0x8c8632
008c8620 movaps xmm2, xmm6
008c8623 divss xmm2, xmm0
008c8627 movaps xmm3, xmm2
008c862a mulss xmm2, xmm1
008c862e mulss xmm3, xmm4
008c8632 subss xmm5, dword ptr [esi + 4]
008c8637 movaps xmm1, xmm2
008c863a movaps xmm0, xmm3
008c863d mulss xmm0, xmm7
008c8641 mulss xmm1, xmm5
008c8645 mulss xmm5, xmm5
008c8649 addss xmm1, xmm0
008c864d addss xmm5, xmm7
008c8651 comiss xmm1, xmm5
008c8654 jb 0x8c8670
008c8656 divss xmm5, xmm1
008c865a mulss xmm3, xmm5
008c865e mulss xmm2, xmm5
008c8662 jmp 0x8c8670
008c8664 movss xmm3, dword ptr [esp + 8]
008c866a movss xmm2, dword ptr [esp + 0xc]
008c8670 addss xmm3, dword ptr [esi]
008c8674 addss xmm2, dword ptr [esi + 4]
008c8679 mov eax, dword ptr [ebp + 0xc]
008c867c movaps xmm1, xmm3
008c867f subss xmm1, dword ptr [eax]
008c8683 movaps xmm0, xmm2
008c8686 subss xmm0, dword ptr [eax + 4]
008c868b mov eax, esi
008c868d mulss xmm1, xmm1
008c8691 mulss xmm0, xmm0
008c8695 addss xmm0, xmm1
008c8699 comiss xmm0, dword ptr [0xb6a214]
008c86a0 jbe 0x8c86b3
008c86a2 movss dword ptr [esi], xmm3
008c86a6 movss dword ptr [esi + 4], xmm2
008c86ab pop edi
008c86ac pop esi
008c86ad mov esp, ebp
008c86af pop ebp
008c86b0 ret 
008c86b1 mov eax, esi
008c86b3 pop edi
008c86b4 pop esi
008c86b5 mov esp, ebp
008c86b7 pop ebp
008c86b8 ret 
008c86b9 nop dword ptr [eax]
008c86bc jg 0x8c8641
008c86be mov word ptr [eax], es
008c86c0 cmc 
008c86c1 test byte ptr [eax + eax + 0x8c8438], cl
008c86c8 scasb al, byte ptr es:[edi]
008c86c9 test dword ptr [eax + eax - 0x33333334], ecx
008c86d0 push ebp
008c86d1 mov ebp, esp
008c86d3 and esp, 0xfffffff8
008c86d6 sub esp, 0x70
008c86d9 push esi
008c86da mov esi, ecx
008c86dc push edi
008c86dd mov dword ptr [esp + 0x4c], esi
008c86e1 call 0x8c7ac0
008c86e6 cmp dword ptr [esi + 0x2c], 4
008c86ea movss xmm0, dword ptr [esi + 0x36c]
008c86f2 movaps xmm1, xmm0
008c86f5 mulss xmm1, dword ptr [0xb6a230]
008c86fd movss dword ptr [esp + 0x2c], xmm1
008c8703 jne 0x8c878f
008c8709 movss dword ptr [esi + 0xe0], xmm0
008c8711 movaps xmm0, xmm1
008c8714 mov dword ptr [esi + 0x3b0], 0x43960000
008c871e call 0x411fe0
008c8723 movss xmm1, dword ptr [esi + 0x294]
008c872b mulss xmm0, dword ptr [0xb6ac14]
008c8733 addss xmm1, dword ptr [esi + 0x2a4]
008c873b addss xmm0, xmm1
008c873f movss dword ptr [esp + 0x38], xmm0
008c8745 movss xmm0, dword ptr [esp + 0x2c]
008c874b call 0x412010
008c8750 movss xmm1, dword ptr [esi + 0x298]
008c8758 addss xmm1, dword ptr [esi + 0x2a8]
008c8760 mulss xmm0, dword ptr [0xb6ac14]
008c8768 addss xmm0, xmm1
008c876c movss xmm1, dword ptr [esp + 0x38]
008c8772 movss dword ptr [esi + 0x428], xmm1
008c877a movss dword ptr [esi + 0x42c], xmm0
008c8782 mov byte ptr [esi + 0x3ad], 0
008c8789 pop edi
008c878a pop esi
008c878b mov esp, ebp
008c878d pop ebp
008c878e ret 
008c878f movaps xmm0, xmm1
008c8792 call 0x411fe0
008c8797 movss dword ptr [esp + 0x50], xmm0
008c879d movss xmm0, dword ptr [esp + 0x2c]
008c87a3 call 0x412010
008c87a8 movss xmm1, dword ptr [esp + 0x50]
008c87ae movss xmm2, dword ptr [0xb6c980]
008c87b6 movss xmm3, dword ptr [0xb6a1b8]
008c87be andps xmm1, xmm2
008c87c1 comiss xmm3, xmm1
008c87c4 movss dword ptr [esp + 0x54], xmm0
008c87ca xorps xmm1, xmm1
008c87cd jbe 0x8c87d5
008c87cf movss dword ptr [esp + 0x50], xmm1
008c87d5 andps xmm0, xmm2
008c87d8 comiss xmm3, xmm0
008c87db jbe 0x8c87e6
008c87dd xorps xmm0, xmm0
008c87e0 movss dword ptr [esp + 0x54], xmm0
008c87e6 mov eax, dword ptr [esi + 0x344]
008c87ec mov ecx, esi
008c87ee shr eax, 8
008c87f1 and al, 1
008c87f3 mov byte ptr [esi + 0x13c], al
008c87f9 call 0x8d7d90
008c87fe push ecx
008c87ff mov ecx, esi
008c8801 call 0x8d79b0
008c8806 mov al, byte ptr [esi + 0x3ad]
008c880c test al, al
008c880e jns 0x8c896a
008c8814 mov ecx, dword ptr [esi + 0x314]
008c881a test ecx, ecx
008c881c je 0x8c8960
008c8822 mov eax, dword ptr [ecx + 0x28]
008c8825 cmp eax, 1
008c8828 je 0x8c8956
008c882e cmp dword ptr [esi + 0x34], 1
008c8832 je 0x8c8956
008c8838 cmp eax, 0x3e
008c883b je 0x8c8956
008c8841 cmp eax, 0x3e8
008c8846 jne 0x8c885a
008c8848 cmp dword ptr [ecx + 0x2c], 0xb2
008c884f jne 0x8c88f5
008c8855 jmp 0x8c8956
008c885a cmp eax, 0x107
008c885f je 0x8c8956
008c8865 cmp eax, 0x10c
008c886a je 0x8c8956
008c8870 cmp eax, 0x19a
008c8875 je 0x8c8956
008c887b cmp eax, 0x104
008c8880 jne 0x8c888e
008c8882 cmp dword ptr [ecx + 0x30], 2
008c8886 je 0x8c8956
008c888c jmp 0x8c88f5
008c888e cmp eax, 3
008c8891 jne 0x8c88f5
008c8893 mov eax, dword ptr [ecx + 0x2c]
008c8896 cmp eax, 0x50
008c8899 je 0x8c8956
008c889f cmp eax, 0x78
008c88a2 je 0x8c8956
008c88a8 mov ecx, dword ptr [esi + 0x378]
008c88ae and ecx, dword ptr [0xbc4cb0]
008c88b4 mov eax, dword ptr [esi + 0x37c]
008c88ba and eax, dword ptr [0xbc4cb4]
008c88c0 mov dword ptr [esp + 0x68], ecx
008c88c4 mov ecx, dword ptr [esi + 0x380]
008c88ca and ecx, dword ptr [0xbc4cb8]
008c88d0 mov dword ptr [esp + 0x6c], eax
008c88d4 mov eax, dword ptr [esi + 0x384]
008c88da and eax, dword ptr [0xbc4cbc]
008c88e0 mov dword ptr [esp + 0x70], ecx
008c88e4 lea ecx, [esp + 0x68]
008c88e8 mov dword ptr [esp + 0x74], eax
008c88ec call 0x412090
008c88f1 test al, al
008c88f3 jne 0x8c8956
008c88f5 cmp byte ptr [esi + 0x410], 0
008c88fc jne 0x8c8956
008c88fe mov ecx, esi
008c8900 call 0x4275d0
008c8905 test al, al
008c8907 jne 0x8c8956
008c8909 mov ecx, dword ptr [esi + 0x378]
008c890f and ecx, dword ptr [0xbc4c00]
008c8915 mov eax, dword ptr [esi + 0x37c]
008c891b and eax, dword ptr [0xbc4c04]
008c8921 mov dword ptr [esp + 0x68], ecx
008c8925 mov ecx, dword ptr [esi + 0x380]
008c892b and ecx, dword ptr [0xbc4c08]
008c8931 mov dword ptr [esp + 0x6c], eax
008c8935 mov eax, dword ptr [esi + 0x384]
008c893b and eax, dword ptr [0xbc4c0c]
008c8941 mov dword ptr [esp + 0x70], ecx
008c8945 lea ecx, [esp + 0x68]
008c8949 mov dword ptr [esp + 0x74], eax
008c894d call 0x412090
008c8952 test al, al
008c8954 je 0x8c8960
008c8956 cmp dword ptr [esi + 0x2c], 7
008c895a je 0x8c8960
008c895c mov al, 1
008c895e jmp 0x8c8962
008c8960 xor al, al
008c8962 mov byte ptr [esi + 0x3ad], al
008c8968 test al, al
008c896a je 0x8c8994
008c896c mov ecx, esi
008c896e call 0x8c7720
008c8973 mov eax, dword ptr [esi + 0x30]
008c8976 cmp eax, 1
008c8979 je 0x8c8989
008c897b cmp eax, 2
008c897e je 0x8c8989
008c8980 cmp eax, 3
008c8983 jne 0x8c8ef2
008c8989 call 0x8d4160
008c898e pop edi
008c898f pop esi
008c8990 mov esp, ebp
008c8992 pop ebp
008c8993 ret 
008c8994 movss xmm5, dword ptr [esi + 0x294]
008c899c movss xmm3, dword ptr [esi + 0x2a8]
008c89a4 addss xmm5, dword ptr [esi + 0x2a4]
008c89ac addss xmm3, dword ptr [esi + 0x298]
008c89b4 mov eax, dword ptr [esi + 0x17c]
008c89ba movss dword ptr [esp + 0xc], xmm5
008c89c0 movss dword ptr [esp + 0x60], xmm5
008c89c6 movss dword ptr [esp + 0x10], xmm3
008c89cc movss dword ptr [esp + 0x64], xmm3
008c89d2 cmp eax, 6
008c89d5 jne 0x8c8db9
008c89db movss xmm2, dword ptr [esp + 0x50]
008c89e1 lea edi, [esi + 0x428]
008c89e7 movss xmm1, dword ptr [esp + 0x54]
008c89ed movaps xmm6, xmm2
008c89f0 mulss xmm6, dword ptr [0xb6ad38]
008c89f8 mov eax, dword ptr [0xbfd65c]
008c89fd mulss xmm2, dword ptr [0xb6a8cc]
008c8a05 movss xmm4, dword ptr [esp + 0xc]
008c8a0b addss xmm6, xmm5
008c8a0f movaps xmm5, xmm1
008c8a12 mov edx, dword ptr [eax + 0x18190]
008c8a18 mulss xmm5, dword ptr [0xb6ad38]
008c8a20 subss xmm4, xmm2
008c8a24 mov dword ptr [esp + 0x30], edx
008c8a28 mulss xmm1, dword ptr [0xb6a8cc]
008c8a30 movss xmm2, dword ptr [0xb6aa3c]
008c8a38 addss xmm5, xmm3
008c8a3c movaps xmm0, xmm4
008c8a3f movss dword ptr [esp + 0x68], xmm6
008c8a45 movss dword ptr [esp + 0x28], xmm0
008c8a4b subss xmm3, xmm1
008c8a4f movss dword ptr [esp + 0x58], xmm0
008c8a55 subss xmm6, xmm4
008c8a59 movss dword ptr [esp + 0x34], xmm4
008c8a5f movss dword ptr [esp + 0x6c], xmm5
008c8a65 movaps xmm0, xmm3
008c8a68 movss dword ptr [esp + 0x38], xmm3
008c8a6e movss dword ptr [esp + 0x2c], xmm0
008c8a74 subss xmm5, xmm3
008c8a78 movss dword ptr [esp + 0x5c], xmm0
008c8a7e movaps xmm0, xmm4
008c8a81 subss xmm0, xmm2
008c8a85 movss dword ptr [esp + 0x3c], xmm6
008c8a8b movss dword ptr [esp + 0x40], xmm5
008c8a91 divss xmm0, xmm2
008c8a95 addss xmm0, dword ptr [0xb6a480]
008c8a9d cvttss2si eax, xmm0
008c8aa1 movaps xmm0, xmm3
008c8aa4 subss xmm0, dword ptr [0xb6ab20]
008c8aac mov dword ptr [esp + 0x18], eax
008c8ab0 xor eax, eax
008c8ab2 divss xmm0, xmm2
008c8ab6 xorps xmm2, xmm2
008c8ab9 comiss xmm6, xmm2
008c8abc addss xmm0, dword ptr [0xb6a480]
008c8ac4 seta al
008c8ac7 cvttss2si ecx, xmm0
008c8acb lea eax, [eax*2 - 1]
008c8ad2 mov dword ptr [esp + 0x14], eax
008c8ad6 xor eax, eax
008c8ad8 xorps xmm0, xmm0
008c8adb comiss xmm5, xmm2
008c8ade mov dword ptr [esp + 0x20], ecx
008c8ae2 movss dword ptr [esp + 8], xmm0
008c8ae8 seta al
008c8aeb ucomiss xmm6, dword ptr [0xc02fec]
008c8af2 lea eax, [eax*2 - 1]
008c8af9 mov dword ptr [esp + 0x1c], eax
008c8afd lahf 
008c8afe test ah, 0x44
008c8b01 jp 0x8c8b14
008c8b03 ucomiss xmm5, dword ptr [0xc02ff0]
008c8b0a lahf 
008c8b0b test ah, 0x44
008c8b0e jnp 0x8c8cc5
008c8b14 mov esi, dword ptr [esp + 0x18]
008c8b18 lea eax, [ecx + ecx*4]
008c8b1b shl eax, 3
008c8b1e mov dword ptr [esp + 0x24], eax
008c8b22 lea eax, [esi + esi*4]
008c8b25 shl eax, 3
008c8b28 mov dword ptr [esp + 0x18], eax
008c8b2c mov eax, dword ptr [esp + 0x1c]
008c8b30 lea eax, [eax + eax*4]
008c8b33 shl eax, 3
008c8b36 mov dword ptr [esp + 0x48], eax
008c8b3a mov eax, dword ptr [esp + 0x14]
008c8b3e lea eax, [eax + eax*4]
008c8b41 shl eax, 3
008c8b44 mov dword ptr [esp + 0x44], eax
008c8b48 test esi, esi
008c8b4a js 0x8c8b7d
008c8b4c mov eax, dword ptr [edx + 0xc]
008c8b4f cmp esi, eax
008c8b51 jge 0x8c8b7d
008c8b53 test ecx, ecx
008c8b55 js 0x8c8b7d
008c8b57 cmp ecx, dword ptr [edx + 0x10]
008c8b5a jge 0x8c8b7d
008c8b5c mov edi, ecx
008c8b5e mov ecx, edx
008c8b60 imul edi, eax
008c8b63 add edi, esi
008c8b65 push edi
008c8b66 call 0x7aeec0
008c8b6b cmp edi, 0x1bf
008c8b71 ja 0x8c8b86
008c8b73 mov edx, dword ptr [esp + 0x30]
008c8b77 mov ecx, dword ptr [edx + edi*4 + 0x24]
008c8b7b jmp 0x8c8b8c
008c8b7d push -1
008c8b7f mov ecx, edx
008c8b81 call 0x7aeec0
008c8b86 mov edx, dword ptr [esp + 0x30]
008c8b8a xor ecx, ecx
008c8b8c cmp eax, 2
008c8b8f je 0x8c8ba0
008c8b91 cmp eax, 3
008c8b94 je 0x8c8ba0
008c8b96 cmp eax, 4
008c8b99 je 0x8c8ba0
008c8b9b cmp eax, 5
008c8b9e jne 0x8c8bb9
008c8ba0 test ecx, ecx
008c8ba2 je 0x8c8cb5
008c8ba8 mov eax, dword ptr [ecx + 4]
008c8bab cmp eax, 0xf
008c8bae je 0x8c8bb9
008c8bb0 cmp eax, 0x10
008c8bb3 jne 0x8c8cb5
008c8bb9 movss xmm6, dword ptr [esp + 0x3c]
008c8bbf xorps xmm2, xmm2
008c8bc2 mov ecx, dword ptr [esp + 0x18]
008c8bc6 movss xmm7, dword ptr [0xb6adc4]
008c8bce ucomiss xmm6, xmm2
008c8bd1 lahf 
008c8bd2 test ah, 0x44
008c8bd5 jnp 0x8c8bf7
008c8bd7 mov eax, dword ptr [esp + 0x14]
008c8bdb lea eax, [eax + eax*4]
008c8bde add eax, 0xa
008c8be1 lea eax, [ecx + eax*4]
008c8be4 movd xmm1, eax
008c8be8 cvtdq2ps xmm1, xmm1
008c8beb subss xmm1, dword ptr [esp + 0x28]
008c8bf1 divss xmm1, xmm6
008c8bf5 jmp 0x8c8bfa
008c8bf7 movaps xmm1, xmm7
008c8bfa movss xmm5, dword ptr [esp + 0x40]
008c8c00 mov edi, dword ptr [esp + 0x24]
008c8c04 ucomiss xmm5, xmm2
008c8c07 lahf 
008c8c08 test ah, 0x44
008c8c0b jnp 0x8c8c2d
008c8c0d mov eax, dword ptr [esp + 0x1c]
008c8c11 lea eax, [eax + eax*4]
008c8c14 add eax, 0x1e
008c8c17 lea eax, [edi + eax*4]
008c8c1a movd xmm0, eax
008c8c1e cvtdq2ps xmm0, xmm0
008c8c21 subss xmm0, dword ptr [esp + 0x2c]
008c8c27 divss xmm0, xmm5
008c8c2b jmp 0x8c8c30
008c8c2d movaps xmm0, xmm7
008c8c30 comiss xmm0, xmm1
008c8c33 jbe 0x8c8c50
008c8c35 addss xmm1, dword ptr [esp + 8]
008c8c3b add esi, dword ptr [esp + 0x14]
008c8c3f add ecx, dword ptr [esp + 0x44]
008c8c43 mov dword ptr [esp + 0x18], ecx
008c8c47 mov ecx, dword ptr [esp + 0x20]
008c8c4b movaps xmm0, xmm1
008c8c4e jmp 0x8c8c6a
008c8c50 mov ecx, dword ptr [esp + 0x20]
008c8c54 add ecx, dword ptr [esp + 0x1c]
008c8c58 add edi, dword ptr [esp + 0x48]
008c8c5c addss xmm0, dword ptr [esp + 8]
008c8c62 mov dword ptr [esp + 0x20], ecx
008c8c66 mov dword ptr [esp + 0x24], edi
008c8c6a movss xmm1, dword ptr [0xb6a614]
008c8c72 movaps xmm4, xmm0
008c8c75 comiss xmm1, xmm0
008c8c78 movaps xmm3, xmm0
008c8c7b mulss xmm4, xmm5
008c8c7f mulss xmm3, xmm6
008c8c83 addss xmm4, dword ptr [esp + 0x38]
008c8c89 movss dword ptr [esp + 8], xmm0
008c8c8f addss xmm3, dword ptr [esp + 0x34]
008c8c95 movss dword ptr [esp + 0x5c], xmm4
008c8c9b movss dword ptr [esp + 0x2c], xmm4
008c8ca1 movss dword ptr [esp + 0x58], xmm3
008c8ca7 movss dword ptr [esp + 0x28], xmm3
008c8cad ja 0x8c8b48
008c8cb3 jmp 0x8c8cbb
008c8cb5 movss xmm0, dword ptr [esp + 8]
008c8cbb mov esi, dword ptr [esp + 0x4c]
008c8cbf lea edi, [esi + 0x428]
008c8cc5 movss xmm1, dword ptr [0xb6a614]
008c8ccd test edi, edi
008c8ccf je 0x8c8ce9
008c8cd1 comiss xmm0, xmm1
008c8cd4 lea eax, [esp + 0x58]
008c8cd8 lea ecx, [esp + 0x68]
008c8cdc cmovb ecx, eax
008c8cdf mov eax, dword ptr [ecx]
008c8ce1 mov dword ptr [edi], eax
008c8ce3 mov eax, dword ptr [ecx + 4]
008c8ce6 mov dword ptr [edi + 4], eax
008c8ce9 comiss xmm0, xmm1
008c8cec jb 0x8c8d26
008c8cee lea eax, [esp + 0x50]
008c8cf2 mov ecx, esi
008c8cf4 push eax
008c8cf5 lea eax, [esp + 0x64]
008c8cf9 push eax
008c8cfa lea eax, [esp + 0x70]
008c8cfe push eax
008c8cff call 0x8c7e90
008c8d04 movss xmm0, dword ptr [esi + 0x2a8]
008c8d0c movss xmm1, dword ptr [eax]
008c8d10 addss xmm1, dword ptr [esi + 0x2a4]
008c8d18 addss xmm0, dword ptr [eax + 4]
008c8d1d movss dword ptr [edi], xmm1
008c8d21 movss dword ptr [edi + 4], xmm0
008c8d26 movss xmm5, dword ptr [esp + 0xc]
008c8d2c movss xmm2, dword ptr [esi + 0x420]
008c8d34 xorps xmm0, xmm0
008c8d37 comiss xmm2, xmm0
008c8d3a movss dword ptr [esp + 0x4c], xmm2
008c8d40 jbe 0x8c8e5e
008c8d46 movss xmm0, dword ptr [edi + 4]
008c8d4b subss xmm0, dword ptr [esp + 0x10]
008c8d51 movss xmm1, dword ptr [edi]
008c8d55 subss xmm1, xmm5
008c8d59 movaps xmm3, xmm0
008c8d5c movss dword ptr [esp + 0x34], xmm0
008c8d62 mulss xmm3, xmm0
008c8d66 movaps xmm0, xmm1
008c8d69 movss dword ptr [esp + 0x38], xmm1
008c8d6f mulss xmm0, xmm1
008c8d73 movaps xmm1, xmm2
008c8d76 mulss xmm1, xmm2
008c8d7a addss xmm3, xmm0
008c8d7e comiss xmm3, xmm1
008c8d81 jbe 0x8c8e5e
008c8d87 movaps xmm0, xmm3
008c8d8a call 0x4228c0
008c8d8f xorps xmm1, xmm1
008c8d92 comiss xmm0, xmm1
008c8d95 jbe 0x8c8e30
008c8d9b movss xmm1, dword ptr [esp + 0x4c]
008c8da1 divss xmm1, xmm0
008c8da5 movaps xmm2, xmm1
008c8da8 mulss xmm1, dword ptr [esp + 0x34]
008c8dae mulss xmm2, dword ptr [esp + 0x38]
008c8db4 jmp 0x8c8e3c
008c8db9 cmp eax, 3
008c8dbc jne 0x8c8df8
008c8dbe lea eax, [esp + 0x50]
008c8dc2 mov ecx, esi
008c8dc4 push eax
008c8dc5 lea eax, [esp + 0x64]
008c8dc9 push eax
008c8dca lea eax, [esp + 0x70]
008c8dce push eax
008c8dcf call 0x8c7e90
008c8dd4 movss xmm1, dword ptr [esi + 0x2a4]
008c8ddc lea edi, [esi + 0x428]
008c8de2 movss xmm0, dword ptr [esi + 0x2a8]
008c8dea addss xmm1, dword ptr [eax]
008c8dee addss xmm0, dword ptr [eax + 4]
008c8df3 jmp 0x8c8d1d
008c8df8 movss xmm2, dword ptr [esp + 0x50]
008c8dfe lea edi, [esi + 0x428]
008c8e04 movss xmm1, dword ptr [esp + 0x54]
008c8e0a mulss xmm2, dword ptr [0xb6accc]
008c8e12 mulss xmm1, dword ptr [0xb6accc]
008c8e1a addss xmm2, xmm5
008c8e1e addss xmm1, xmm3
008c8e22 movss dword ptr [edi], xmm2
008c8e26 movss dword ptr [edi + 4], xmm1
008c8e2b jmp 0x8c8d2c
008c8e30 movss xmm2, dword ptr [esp + 0x38]
008c8e36 movss xmm1, dword ptr [esp + 0x34]
008c8e3c movss xmm5, dword ptr [esp + 0xc]
008c8e42 movaps xmm0, xmm5
008c8e45 addss xmm0, xmm2
008c8e49 movss xmm2, dword ptr [esp + 0x10]
008c8e4f addss xmm1, xmm2
008c8e53 movss dword ptr [edi], xmm0
008c8e57 movss dword ptr [edi + 4], xmm1
008c8e5c jmp 0x8c8e64
008c8e5e movss xmm2, dword ptr [esp + 0x10]
008c8e64 movss xmm1, dword ptr [edi]
008c8e68 movss xmm0, dword ptr [edi + 4]
008c8e6d subss xmm1, xmm5
008c8e71 subss xmm0, xmm2
008c8e75 mulss xmm1, xmm1
008c8e79 mulss xmm0, xmm0
008c8e7d addss xmm0, xmm1
008c8e81 call 0x4228c0
008c8e86 mov eax, dword ptr [esi + 0x2c]
008c8e89 movaps xmm1, xmm0
008c8e8c movss dword ptr [esi + 0x3b0], xmm1
008c8e94 cmp eax, 6
008c8e97 je 0x8c8e9e
008c8e99 cmp eax, 0xf
008c8e9c jne 0x8c8ed8
008c8e9e cmp dword ptr [esi + 0x34], 0x19a
008c8ea5 jne 0x8c8ec8
008c8ea7 movss xmm0, dword ptr [0xb6aae0]
008c8eaf comiss xmm0, xmm1
008c8eb2 ja 0x8c8eba
008c8eb4 movss xmm0, xmm1
008c8eb8 jmp 0x8c8ebe
008c8eba movss xmm0, xmm0
008c8ebe movss dword ptr [esi + 0x3b0], xmm0
008c8ec6 jmp 0x8c8ed8
008c8ec8 addss xmm1, dword ptr [0xb6aafc]
008c8ed0 movss dword ptr [esi + 0x3b0], xmm1
008c8ed8 movss xmm0, dword ptr [esi + 0x36c]
008c8ee0 mov ecx, esi
008c8ee2 subss xmm0, dword ptr [0xb6aae4]
008c8eea movss dword ptr [esi + 0xe0], xmm0
008c8ef2 call 0x8cc300
008c8ef7 pop edi
008c8ef8 pop esi
008c8ef9 mov esp, ebp
008c8efb pop ebp
008c8efc ret 
008c8efd int3 
008c8efe int3 
008c8eff int3 
008c8f00 push ebx
008c8f01 mov ebx, esp
008c8f03 sub esp, 8
008c8f06 and esp, 0xfffffff8
008c8f09 add esp, 4
008c8f0c push ebp
008c8f0d mov ebp, dword ptr [ebx + 4]
008c8f10 mov dword ptr [esp + 4], ebp
008c8f14 mov ebp, esp
008c8f16 push -1
008c8f18 push 0x9ff77d
008c8f1d mov eax, dword ptr fs:[0]
008c8f23 push eax
008c8f24 push ebx
008c8f25 sub esp, 0xb0
008c8f2b push esi
008c8f2c push edi
008c8f2d mov eax, dword ptr [0xbaa3b4]
008c8f32 xor eax, ebp
008c8f34 push eax
008c8f35 lea eax, [ebp - 0xc]
008c8f38 mov dword ptr fs:[0], eax
008c8f3e mov edi, ecx
008c8f40 cmp byte ptr [edi + 0x3ad], 0
008c8f47 je 0x8c95da
008c8f4d push 0x1c
008c8f4f mov dword ptr [ebp - 0x38], 0
008c8f56 mov dword ptr [ebp - 0x34], 0
008c8f5d call 0x9eacf8
008c8f62 add esp, 4
008c8f65 mov dword ptr [eax], eax
008c8f67 mov dword ptr [eax + 4], eax
008c8f6a mov dword ptr [eax + 8], eax
008c8f6d mov word ptr [eax + 0xc], 0x101
008c8f73 mov dword ptr [ebp - 0x38], eax
008c8f76 mov dword ptr [ebp - 4], 0
008c8f7d mov esi, dword ptr [edi + 0x3e0]
008c8f83 mov ecx, dword ptr [edi + 0x3dc]
008c8f89 sub esi, ecx
008c8f8b sar esi, 3
008c8f8e mov dword ptr [ebp - 0x6c], esi
008c8f91 cmp esi, 2
008c8f94 jb 0x8c95ba
008c8f9a mov eax, dword ptr [ebx + 0xc]
008c8f9d xorps xmm0, xmm0
008c8fa0 movss xmm3, dword ptr [ecx + 4]
008c8fa5 xorps xmm1, xmm1
008c8fa8 xor edx, edx
008c8faa movss dword ptr [ebp - 0x5c], xmm0
008c8faf movss dword ptr [ebp - 0x58], xmm0
008c8fb4 movss xmm2, dword ptr [eax]
008c8fb8 addss xmm2, dword ptr [ecx]
008c8fbc addss xmm3, dword ptr [eax + 4]
008c8fc1 movss dword ptr [ebp - 0x4c], xmm1
008c8fc6 mov dword ptr [ebp - 0x48], edx
008c8fc9 movss dword ptr [ebp - 0x40], xmm2
008c8fce movss dword ptr [ebp - 0x50], xmm2
008c8fd3 xorps xmm2, xmm2
008c8fd6 movss dword ptr [ebp - 0x28], xmm3
008c8fdb movss dword ptr [ebp - 0x54], xmm3
008c8fe0 movss dword ptr [ebp - 0x24], xmm2
008c8fe5 mov ecx, dword ptr [edi + 0x3dc]
008c8feb cmp edx, esi
008c8fed jae 0x8c9046
008c8fef movss xmm1, dword ptr [ecx + edx*8]
008c8ff4 movss xmm0, dword ptr [ecx + edx*8 + 4]
008c8ffa addss xmm1, dword ptr [eax]
008c8ffe addss xmm0, dword ptr [eax + 4]
008c9003 lea eax, [esi - 1]
008c9006 movss dword ptr [ebp - 0x20], xmm1
008c900b movss dword ptr [ebp - 0x1c], xmm0
008c9010 cmp edx, eax
008c9012 jae 0x8c902d
008c9014 movss xmm2, dword ptr [ecx + edx*8 + 0xc]
008c901a movss xmm1, dword ptr [ecx + edx*8 + 8]
008c9020 subss xmm2, dword ptr [ecx + edx*8 + 4]
008c9026 subss xmm1, dword ptr [ecx + edx*8]
008c902b jmp 0x8c9095
008c902d movss xmm2, dword ptr [ecx + edx*8 + 4]
008c9033 movss xmm1, dword ptr [ecx + edx*8]
008c9038 subss xmm2, dword ptr [ecx + edx*8 - 4]
008c903e subss xmm1, dword ptr [ecx + edx*8 - 8]
008c9044 jmp 0x8c9095
008c9046 movss xmm2, dword ptr [ecx + esi*8 - 8]
008c904c subss xmm2, dword ptr [ecx + esi*8 - 0x10]
008c9052 movss xmm0, dword ptr [ecx + esi*8 - 4]
008c9058 subss xmm0, dword ptr [ecx + esi*8 - 0xc]
008c905e movss xmm1, dword ptr [ecx + esi*8 - 8]
008c9064 subss xmm1, dword ptr [ecx + esi*8 - 0x10]
008c906a addss xmm2, dword ptr [ecx + esi*8 - 8]
008c9070 addss xmm0, dword ptr [ecx + esi*8 - 4]
008c9076 addss xmm2, dword ptr [eax]
008c907a addss xmm0, dword ptr [eax + 4]
008c907f movss dword ptr [ebp - 0x20], xmm2
008c9084 movss xmm2, dword ptr [ecx + esi*8 - 4]
008c908a subss xmm2, dword ptr [ecx + esi*8 - 0xc]
008c9090 movss dword ptr [ebp - 0x1c], xmm0
008c9095 movaps xmm0, xmm1
008c9098 movss dword ptr [ebp - 0x18], xmm1
008c909d mulss xmm0, xmm1
008c90a1 movaps xmm1, xmm2
008c90a4 mulss xmm1, xmm2
008c90a8 movss dword ptr [ebp - 0x14], xmm2
008c90ad addss xmm0, xmm1
008c90b1 call 0x4228c0
008c90b6 movss xmm1, dword ptr [ebp - 0x18]
008c90bb lea eax, [ebp - 0x20]
008c90be movaps xmm2, xmm0
008c90c1 movss xmm0, dword ptr [ebp - 0x14]
008c90c6 divss xmm0, xmm2
008c90ca push ecx
008c90cb mov ecx, dword ptr [0xbfd65c]
008c90d1 mov dword ptr [esp], 0
008c90d8 push eax
008c90d9 mov ecx, dword ptr [ecx + 0x18190]
008c90df divss xmm1, xmm2
008c90e3 movss dword ptr [ebp - 0x14], xmm0
008c90e8 movaps xmm0, xmm1
008c90eb movss dword ptr [ebp - 0x44], xmm2
008c90f0 xorps xmm0, xmmword ptr [0xb6c9b0]
008c90f7 movss dword ptr [ebp - 0x18], xmm1
008c90fc movss dword ptr [ebp - 0x60], xmm0
008c9101 call 0x7cf0a0
008c9106 movss xmm3, dword ptr [ebp - 0x1c]
008c910b movss xmm4, dword ptr [ebp - 0x20]
008c9110 movss xmm1, dword ptr [ebp - 0x14]
008c9115 test al, al
008c9117 je 0x8c913c
008c9119 movss xmm0, dword ptr [ebp - 0x24]
008c911e movss dword ptr [ebp - 0x4c], xmm0
008c9123 movss xmm0, dword ptr [ebp - 0x18]
008c9128 movss dword ptr [ebp - 0x50], xmm4
008c912d movss dword ptr [ebp - 0x54], xmm3
008c9132 movss dword ptr [ebp - 0x58], xmm0
008c9137 movss dword ptr [ebp - 0x5c], xmm1
008c913c movss xmm0, dword ptr [edi + 0x2c8]
008c9144 xorps xmm2, xmm2
008c9147 comiss xmm0, xmm2
008c914a movss dword ptr [ebp - 0x3c], xmm2
008c914f jbe 0x8c94a2
008c9155 nop word ptr [eax + eax]
008c9160 movss xmm2, dword ptr [ebp - 0x60]
008c9165 lea eax, [ebp - 0x30]
008c9168 mulss xmm1, dword ptr [ebp - 0x3c]
008c916d mov esi, dword ptr [0xbfd65c]
008c9173 mulss xmm2, dword ptr [ebp - 0x3c]
008c9178 push ecx
008c9179 addss xmm4, xmm1
008c917d mov dword ptr [esp], 0x41000000
008c9184 mov ecx, dword ptr [esi + 0x18190]
008c918a addss xmm3, xmm2
008c918e movss dword ptr [ebp - 0x64], xmm1
008c9193 push eax
008c9194 movss dword ptr [ebp - 0x68], xmm2
008c9199 movss dword ptr [ebp - 0x30], xmm4
008c919e movss dword ptr [ebp - 0x2c], xmm3
008c91a3 call 0x7cf0a0
008c91a8 test al, al
008c91aa je 0x8c9266
008c91b0 movss xmm1, dword ptr [0xb6aa3c]
008c91b8 movss xmm0, dword ptr [ebp - 0x30]
008c91bd subss xmm0, xmm1
008c91c1 mov ecx, dword ptr [esi + 0x18190]
008c91c7 divss xmm0, xmm1
008c91cb addss xmm0, dword ptr [0xb6a480]
008c91d3 cvttss2si edx, xmm0
008c91d7 movss xmm0, dword ptr [ebp - 0x2c]
008c91dc subss xmm0, dword ptr [0xb6ab20]
008c91e4 divss xmm0, xmm1
008c91e8 addss xmm0, dword ptr [0xb6a480]
008c91f0 cvttss2si eax, xmm0
008c91f4 test edx, edx
008c91f6 js 0x8c92dc
008c91fc mov esi, dword ptr [ecx + 0xc]
008c91ff cmp edx, esi
008c9201 jge 0x8c92dc
008c9207 test eax, eax
008c9209 js 0x8c92dc
008c920f cmp eax, dword ptr [ecx + 0x10]
008c9212 jge 0x8c92dc
008c9218 imul esi, eax
008c921b add esi, edx
008c921d js 0x8c92dc
008c9223 push esi
008c9224 call 0x7aeec0
008c9229 cmp eax, 1
008c922c je 0x8c92dc
008c9232 test eax, eax
008c9234 je 0x8c92dc
008c923a movss xmm0, dword ptr [ebp - 0x18]
008c923f lea eax, [ebp - 0x80]
008c9242 push eax
008c9243 movss dword ptr [ebp - 0x7c], xmm0
008c9248 lea eax, [ebp - 0x94]
008c924e movss xmm0, dword ptr [ebp - 0x14]
008c9253 lea ecx, [ebp - 0x38]
008c9256 push eax
008c9257 mov dword ptr [ebp - 0x80], esi
008c925a movss dword ptr [ebp - 0x78], xmm0
008c925f call 0x8d8740
008c9264 jmp 0x8c928e
008c9266 push 0xbc4940
008c926b lea edx, [edi + 0x378]
008c9271 lea ecx, [ebp - 0xb0]
008c9277 call 0x412050
008c927c add esp, 4
008c927f mov ecx, dword ptr [eax]
008c9281 or ecx, dword ptr [eax + 4]
008c9284 jne 0x8c928e
008c9286 mov ecx, dword ptr [eax + 8]
008c9289 or ecx, dword ptr [eax + 0xc]
008c928c je 0x8c92dc
008c928e movss xmm1, dword ptr [ebp - 0x24]
008c9293 movss xmm0, dword ptr [edi + 0x494]
008c929b comiss xmm0, xmm1
008c929e jbe 0x8c92dc
008c92a0 movss xmm0, dword ptr [ebp - 0x40]
008c92a5 movss dword ptr [edi + 0x494], xmm1
008c92ad movss dword ptr [edi + 0x498], xmm0
008c92b5 movss xmm0, dword ptr [ebp - 0x28]
008c92ba movss dword ptr [edi + 0x49c], xmm0
008c92c2 movss xmm0, dword ptr [ebp - 0x18]
008c92c7 movss dword ptr [edi + 0x4a0], xmm0
008c92cf movss xmm0, dword ptr [ebp - 0x14]
008c92d4 movss dword ptr [edi + 0x4a4], xmm0
008c92dc movss xmm1, dword ptr [ebp - 0x3c]
008c92e1 ucomiss xmm1, dword ptr [0xb6a18c]
008c92e8 lahf 
008c92e9 test ah, 0x44
008c92ec jnp 0x8c946d
008c92f2 movss xmm1, dword ptr [ebp - 0x20]
008c92f7 lea eax, [ebp - 0x30]
008c92fa movss xmm0, dword ptr [ebp - 0x1c]
008c92ff subss xmm1, dword ptr [ebp - 0x64]
008c9304 subss xmm0, dword ptr [ebp - 0x68]
008c9309 mov esi, dword ptr [0xbfd65c]
008c930f push ecx
008c9310 mov dword ptr [esp], 0x41000000
008c9317 push eax
008c9318 mov ecx, dword ptr [esi + 0x18190]
008c931e movss dword ptr [ebp - 0x30], xmm1
008c9323 movss dword ptr [ebp - 0x2c], xmm0
008c9328 call 0x7cf0a0
008c932d test al, al
008c932f je 0x8c9445
008c9335 movss xmm1, dword ptr [0xb6aa3c]
008c933d movss xmm0, dword ptr [ebp - 0x30]
008c9342 subss xmm0, xmm1
008c9346 mov ecx, dword ptr [esi + 0x18190]
008c934c divss xmm0, xmm1
008c9350 addss xmm0, dword ptr [0xb6a480]
008c9358 cvttss2si edx, xmm0
008c935c movss xmm0, dword ptr [ebp - 0x2c]
008c9361 subss xmm0, dword ptr [0xb6ab20]
008c9369 divss xmm0, xmm1
008c936d addss xmm0, dword ptr [0xb6a480]
008c9375 cvttss2si eax, xmm0
008c9379 test edx, edx
008c937b js 0x8c946d
008c9381 mov esi, dword ptr [ecx + 0xc]
008c9384 cmp edx, esi
008c9386 jge 0x8c946d
008c938c test eax, eax
008c938e js 0x8c946d
008c9394 cmp eax, dword ptr [ecx + 0x10]
008c9397 jge 0x8c946d
008c939d imul esi, eax
008c93a0 add esi, edx
008c93a2 js 0x8c946d
008c93a8 push esi
008c93a9 call 0x7aeec0
008c93ae cmp eax, 1
008c93b1 je 0x8c946d
008c93b7 test eax, eax
008c93b9 je 0x8c946d
008c93bf movss xmm0, dword ptr [ebp - 0x18]
008c93c4 lea eax, [ebp - 0x8c]
008c93ca push eax
008c93cb movss dword ptr [ebp - 0x88], xmm0
008c93d3 lea eax, [ebp - 0x9c]
008c93d9 movss xmm0, dword ptr [ebp - 0x14]
008c93de lea ecx, [ebp - 0x38]
008c93e1 push eax
008c93e2 mov dword ptr [ebp - 0x8c], esi
008c93e8 movss dword ptr [ebp - 0x84], xmm0
008c93f0 call 0x8d8740
008c93f5 movss xmm0, dword ptr [edi + 0x494]
008c93fd movss xmm2, dword ptr [ebp - 0x24]
008c9402 comiss xmm0, xmm2
008c9405 movss xmm1, dword ptr [ebp - 0x14]
008c940a jbe 0x8c9472
008c940c movss xmm0, dword ptr [ebp - 0x30]
008c9411 movss dword ptr [edi + 0x494], xmm2
008c9419 movss dword ptr [edi + 0x498], xmm0
008c9421 movss xmm0, dword ptr [ebp - 0x2c]
008c9426 movss dword ptr [edi + 0x49c], xmm0
008c942e movss xmm0, dword ptr [ebp - 0x18]
008c9433 movss dword ptr [edi + 0x4a0], xmm0
008c943b movss dword ptr [edi + 0x4a4], xmm1
008c9443 jmp 0x8c9472
008c9445 push 0xbc4940
008c944a lea edx, [edi + 0x378]
008c9450 lea ecx, [ebp - 0xc0]
008c9456 call 0x412050
008c945b add esp, 4
008c945e mov ecx, dword ptr [eax]
008c9460 or ecx, dword ptr [eax + 4]
008c9463 jne 0x8c93f5
008c9465 mov ecx, dword ptr [eax + 8]
008c9468 or ecx, dword ptr [eax + 0xc]
008c946b jne 0x8c93f5
008c946d movss xmm1, dword ptr [ebp - 0x14]
008c9472 movss xmm2, dword ptr [ebp - 0x3c]
008c9477 addss xmm2, dword ptr [0xb6a9c8]
008c947f movss xmm0, dword ptr [edi + 0x2c8]
008c9487 movss xmm3, dword ptr [ebp - 0x1c]
008c948c movss xmm4, dword ptr [ebp - 0x20]
008c9491 comiss xmm0, xmm2
008c9494 movss dword ptr [ebp - 0x3c], xmm2
008c9499 ja 0x8c9160
008c949f mov esi, dword ptr [ebp - 0x6c]
008c94a2 movss xmm1, dword ptr [ebp - 0x24]
008c94a7 movaps xmm0, xmm4
008c94aa addss xmm1, dword ptr [ebp - 0x44]
008c94af mov edx, dword ptr [ebp - 0x48]
008c94b2 mov eax, dword ptr [ebx + 0xc]
008c94b5 inc edx
008c94b6 movss dword ptr [ebp - 0x40], xmm0
008c94bb movss dword ptr [ebp - 0x74], xmm0
008c94c0 movaps xmm0, xmm3
008c94c3 movss dword ptr [ebp - 0x28], xmm0
008c94c8 movss dword ptr [ebp - 0x70], xmm0
008c94cd movss dword ptr [ebp - 0x24], xmm1
008c94d2 mov dword ptr [ebp - 0x48], edx
008c94d5 cmp edx, esi
008c94d7 jbe 0x8c8fe5
008c94dd mov eax, dword ptr [ebp - 0x38]
008c94e0 mov esi, dword ptr [eax]
008c94e2 cmp esi, eax
008c94e4 je 0x8c9536
008c94e6 lea eax, [esi + 0x14]
008c94e9 push eax
008c94ea push ecx
008c94eb push dword ptr [esi + 0x10]
008c94ee mov ecx, edi
008c94f0 call 0x8c97a0
008c94f5 mov eax, dword ptr [esi + 8]
008c94f8 cmp byte ptr [eax + 0xd], 0
008c94fc je 0x8c951b
