00544b70 push ebx
00544b71 mov ebx, esp
00544b73 sub esp, 8
00544b76 and esp, 0xfffffff8
00544b79 add esp, 4
00544b7c push ebp
00544b7d mov ebp, dword ptr [ebx + 4]
00544b80 mov dword ptr [esp + 4], ebp
00544b84 mov ebp, esp
00544b86 push -1
00544b88 push 0x9efc75
00544b8d mov eax, dword ptr fs:[0]
00544b93 push eax
00544b94 push ebx
00544b95 sub esp, 0x30
00544b98 push esi
00544b99 push edi
00544b9a mov eax, dword ptr [0xbaa3b4]
00544b9f xor eax, ebp
00544ba1 push eax
00544ba2 lea eax, [ebp - 0xc]
00544ba5 mov dword ptr fs:[0], eax
00544bab mov dword ptr [ebp - 0x20], ecx
00544bae xor eax, eax
00544bb0 xor esi, esi
00544bb2 xor edi, edi
00544bb4 mov dword ptr [ebp - 0x1c], eax
00544bb7 mov dword ptr [ebp - 0x2c], eax
00544bba mov dword ptr [ebp - 0x28], esi
00544bbd mov dword ptr [ebp - 0x24], edi
00544bc0 push edi
00544bc1 push edi
00544bc2 push -1
00544bc4 push -1
00544bc6 mov dword ptr [ebp - 4], edi
00544bc9 lea eax, [ebp - 0x3c]
00544bcc movss xmm0, dword ptr [0xb6ac40]
00544bd4 push 0x328
00544bd9 push eax
00544bda mov eax, dword ptr [0xbfd65c]
00544bdf movss dword ptr [ebp - 0x14], xmm0
00544be4 mov ecx, dword ptr [eax + 0x18190]
00544bea add ecx, 0x1218
00544bf0 call 0x415ed0
00544bf5 xor ecx, ecx
00544bf7 mov byte ptr [ebp - 4], 1
00544bfb mov dword ptr [ebp - 0x18], ecx
00544bfe cmp dword ptr [ebp - 0x30], ecx
00544c01 jbe 0x544d61
00544c07 mov eax, dword ptr [ebp - 0x38]
00544c0a xor edx, edx
00544c0c nop dword ptr [eax]
00544c10 mov edi, dword ptr [eax + ecx*4]
00544c13 mov dword ptr [ebp - 0x1c], edi
00544c16 cmp dword ptr [edi + 0x30], 0
00544c1a jne 0x544c77
00544c1c cmp byte ptr [edi + 0x16b], 0
00544c23 jne 0x544c77
00544c25 mov ecx, dword ptr [ebp - 0x20]
00544c28 mov eax, dword ptr [edi + 0x314]
00544c2e cmp eax, dword ptr [ecx + 0x314]
00544c34 mov ecx, dword ptr [ebp - 0x18]
00544c37 jne 0x544c74
00544c39 cmp esi, edx
00544c3b je 0x544c47
00544c3d mov dword ptr [esi], edi
00544c3f add esi, 4
00544c42 mov dword ptr [ebp - 0x28], esi
00544c45 jmp 0x544c5d
00544c47 lea eax, [ebp - 0x1c]
00544c4a push eax
00544c4b push esi
00544c4c lea ecx, [ebp - 0x2c]
00544c4f call 0x426fb0
00544c54 mov edx, dword ptr [ebp - 0x24]
00544c57 mov esi, dword ptr [ebp - 0x28]
00544c5a mov ecx, dword ptr [ebp - 0x18]
00544c5d movss xmm1, dword ptr [edi + 0xb08]
00544c65 minss xmm1, dword ptr [ebp - 0x14]
00544c6a mov eax, dword ptr [ebp - 0x38]
00544c6d movss dword ptr [ebp - 0x14], xmm1
00544c72 jmp 0x544c7c
00544c74 mov eax, dword ptr [ebp - 0x38]
00544c77 movss xmm1, dword ptr [ebp - 0x14]
00544c7c inc ecx
00544c7d mov dword ptr [ebp - 0x18], ecx
00544c80 cmp ecx, dword ptr [ebp - 0x30]
00544c83 jb 0x544c10
00544c85 mov ecx, dword ptr [ebp - 0x2c]
00544c88 mov dword ptr [ebp - 0x18], edx
00544c8b mov dword ptr [ebp - 0x1c], ecx
00544c8e cmp ecx, esi
00544c90 je 0x544d5e
00544c96 movss xmm3, dword ptr [0xb6a914]
00544c9e sub esi, ecx
00544ca0 sar esi, 2
00544ca3 mov eax, esi
00544ca5 shr eax, 0x1f
00544ca8 movd xmm0, esi
00544cac cvtdq2pd xmm0, xmm0
00544cb0 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
00544cb9 cvtpd2ps xmm0, xmm0
00544cbd divss xmm3, xmm0
00544cc1 movss dword ptr [ebp - 0x20], xmm3
00544cc6 cmp esi, 1
00544cc9 jbe 0x544d5e
00544ccf movss xmm2, dword ptr [0xb6ac40]
00544cd7 xor edi, edi
00544cd9 nop dword ptr [eax]
00544ce0 movd xmm0, edi
00544ce4 mov eax, edi
00544ce6 cvtdq2pd xmm0, xmm0
00544cea shr eax, 0x1f
00544ced addsd xmm0, qword ptr [eax*8 + 0xb6c940]
00544cf6 cvtpd2ps xmm0, xmm0
00544cfa mulss xmm0, xmm3
00544cfe addss xmm0, xmm1
00544d02 movaps xmm1, xmm0
00544d05 andps xmm1, xmmword ptr [0xb6c980]
00544d0c comiss xmm1, xmm2
00544d0f jbe 0x544d29
00544d11 movaps xmm1, xmm2
00544d14 call 0x447b40
00544d19 movss xmm2, dword ptr [0xb6ac40]
00544d21 movss xmm3, dword ptr [ebp - 0x20]
00544d26 mov ecx, dword ptr [ebp - 0x1c]
00544d29 comiss xmm0, dword ptr [0xb6ab88]
00544d30 jbe 0x544d38
00544d32 subss xmm0, xmm2
00544d36 jmp 0x544d49
00544d38 movss xmm1, dword ptr [0xb6af74]
00544d40 comiss xmm1, xmm0
00544d43 jbe 0x544d49
00544d45 addss xmm0, xmm2
00544d49 mov eax, dword ptr [ecx + edi*4]
00544d4c inc edi
00544d4d movss xmm1, dword ptr [ebp - 0x14]
00544d52 movss dword ptr [eax + 0xb08], xmm0
00544d5a cmp edi, esi
00544d5c jb 0x544ce0
00544d5e mov edi, dword ptr [ebp - 0x18]
00544d61 cmp byte ptr [ebp - 0x3c], 0
00544d65 jne 0x544d72
00544d67 push dword ptr [ebp - 0x38]
00544d6a call 0x9eace5
00544d6f add esp, 4
00544d72 mov ecx, dword ptr [ebp - 0x1c]
00544d75 test ecx, ecx
00544d77 je 0x544da8
00544d79 sub edi, ecx
00544d7b mov eax, ecx
00544d7d and edi, 0xfffffffc
00544d80 cmp edi, 0x1000
00544d86 jb 0x544d9e
00544d88 mov ecx, dword ptr [ecx - 4]
00544d8b add edi, 0x23
00544d8e sub eax, ecx
00544d90 add eax, -4
00544d93 cmp eax, 0x1f
00544d96 jbe 0x544d9e
00544d98 call dword ptr [0xa065ac]
00544d9e push edi
00544d9f push ecx
00544da0 call 0x9eb08e
00544da5 add esp, 8
00544da8 mov ecx, dword ptr [ebp - 0xc]
00544dab mov dword ptr fs:[0], ecx
00544db2 pop ecx
00544db3 pop edi
00544db4 pop esi
00544db5 mov esp, ebp
00544db7 pop ebp
00544db8 mov esp, ebx
00544dba pop ebx
00544dbb ret 
