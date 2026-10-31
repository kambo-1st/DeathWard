007d9b50 push ebp
007d9b51 mov ebp, esp
007d9b53 and esp, 0xfffffff8
007d9b56 sub esp, 0x38
007d9b59 push esi
007d9b5a push edi
007d9b5b mov edi, ecx
007d9b5d mov eax, dword ptr [edi + 4]
007d9b60 mov eax, dword ptr [eax + 0x10]
007d9b63 mov eax, dword ptr [eax + 0x48]
007d9b66 add eax, -9
007d9b69 cmp eax, 3
007d9b6c ja 0x7d9d10
007d9b72 lea eax, [esp + 0x20]
007d9b76 push eax
007d9b77 call 0x7da8e0
007d9b7c movss xmm0, dword ptr [ebp + 0xc]
007d9b81 movss xmm1, dword ptr [esp + 0x30]
007d9b87 movss xmm3, dword ptr [esp + 0x20]
007d9b8d subss xmm1, xmm0
007d9b91 movss xmm7, dword ptr [esp + 0x28]
007d9b97 subss xmm3, xmm0
007d9b9b movss xmm4, dword ptr [esp + 0x38]
007d9ba1 addss xmm7, xmm0
007d9ba5 movss xmm2, dword ptr [esp + 0x24]
007d9bab addss xmm4, xmm0
007d9baf movss xmm5, dword ptr [esp + 0x2c]
007d9bb5 subss xmm2, xmm0
007d9bb9 movss xmm6, dword ptr [esp + 0x34]
007d9bbf addss xmm5, xmm0
007d9bc3 movss dword ptr [esp + 0x10], xmm1
007d9bc9 subss xmm6, xmm0
007d9bcd movss xmm1, dword ptr [esp + 0x3c]
007d9bd3 subss xmm7, xmm3
007d9bd7 subss xmm4, dword ptr [esp + 0x10]
007d9bdd movss dword ptr [esp + 0x18], xmm3
007d9be3 addss xmm1, xmm0
007d9be7 comiss xmm4, xmm7
007d9bea jbe 0x7d9bf1
007d9bec movaps xmm5, xmm6
007d9bef jmp 0x7d9bf4
007d9bf1 movaps xmm6, xmm5
007d9bf4 mov esi, dword ptr [ebp + 8]
007d9bf7 subss xmm5, xmm2
007d9bfb subss xmm1, xmm6
007d9bff movaps xmm3, xmm5
007d9c02 mulss xmm3, xmm7
007d9c06 movss dword ptr [esp + 0xc], xmm1
007d9c0c andps xmm3, xmmword ptr [0xb6c980]
007d9c13 call 0x6c3d90
007d9c18 xorps xmm0, xmm0
007d9c1b cvtsi2sd xmm0, eax
007d9c1f shr eax, 0x1f
007d9c22 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
007d9c2b cvtpd2ps xmm1, xmm0
007d9c2f movss xmm0, dword ptr [esp + 0xc]
007d9c35 mulss xmm1, dword ptr [0xb6a19c]
007d9c3d mulss xmm0, xmm4
007d9c41 andps xmm0, xmmword ptr [0xb6c980]
007d9c48 addss xmm0, xmm3
007d9c4c divss xmm3, xmm0
007d9c50 call 0x6c3d90
007d9c55 xorps xmm0, xmm0
007d9c58 cvtsi2sd xmm0, eax
007d9c5c shr eax, 0x1f
007d9c5f comiss xmm1, xmm3
007d9c62 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
007d9c6b cvtpd2ps xmm1, xmm0
007d9c6f mulss xmm1, dword ptr [0xb6a19c]
007d9c77 jb 0x7d9cc4
007d9c79 call 0x6c3d90
007d9c7e xorps xmm0, xmm0
007d9c81 mulss xmm4, xmm1
007d9c85 cvtsi2sd xmm0, eax
007d9c89 shr eax, 0x1f
007d9c8c addss xmm4, dword ptr [esp + 0x10]
007d9c92 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
007d9c9b mov eax, esi
007d9c9d cvtpd2ps xmm0, xmm0
007d9ca1 mulss xmm0, dword ptr [0xb6a19c]
007d9ca9 movss dword ptr [esi], xmm4
007d9cad mulss xmm0, dword ptr [esp + 0xc]
007d9cb3 addss xmm0, xmm6
007d9cb7 movss dword ptr [esi + 4], xmm0
007d9cbc pop edi
007d9cbd pop esi
007d9cbe mov esp, ebp
007d9cc0 pop ebp
007d9cc1 ret 8
007d9cc4 call 0x6c3d90
007d9cc9 xorps xmm0, xmm0
007d9ccc movaps xmm4, xmm7
007d9ccf mulss xmm4, xmm1
007d9cd3 cvtsi2sd xmm0, eax
007d9cd7 shr eax, 0x1f
007d9cda addss xmm4, dword ptr [esp + 0x18]
007d9ce0 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
007d9ce9 mov eax, esi
007d9ceb cvtpd2ps xmm0, xmm0
007d9cef mulss xmm0, dword ptr [0xb6a19c]
007d9cf7 movss dword ptr [esi], xmm4
007d9cfb mulss xmm0, xmm5
007d9cff addss xmm0, xmm2
007d9d03 movss dword ptr [esi + 4], xmm0
007d9d08 pop edi
007d9d09 pop esi
007d9d0a mov esp, ebp
007d9d0c pop ebp
007d9d0d ret 8
007d9d10 call 0x6c3d90
007d9d15 movd xmm0, eax
007d9d19 cvtdq2pd xmm0, xmm0
007d9d1d shr eax, 0x1f
007d9d20 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
007d9d29 cvtpd2ps xmm4, xmm0
007d9d2d mulss xmm4, dword ptr [0xb6a19c]
007d9d35 call 0x6c3d90
007d9d3a mov esi, dword ptr [ebp + 8]
007d9d3d sub esp, 0xc
007d9d40 mov ecx, edi
007d9d42 movd xmm0, eax
007d9d46 cvtdq2pd xmm0, xmm0
007d9d4a shr eax, 0x1f
007d9d4d addsd xmm0, qword ptr [eax*8 + 0xb6c940]
007d9d56 lea eax, [esp + 0x24]
007d9d5a cvtpd2ps xmm3, xmm0
007d9d5e movss xmm0, dword ptr [edi + 0x1c]
007d9d63 subss xmm0, dword ptr [edi + 0x14]
007d9d68 mulss xmm3, dword ptr [0xb6a19c]
007d9d70 mulss xmm0, xmm4
007d9d74 addss xmm0, dword ptr [edi + 0x14]
007d9d79 movss dword ptr [esp + 0x24], xmm0
007d9d7f movss xmm0, dword ptr [edi + 0x20]
007d9d84 subss xmm0, dword ptr [edi + 0x18]
007d9d89 mulss xmm0, xmm3
007d9d8d movss xmm3, dword ptr [ebp + 0xc]
007d9d92 movss dword ptr [esp + 8], xmm3
007d9d98 addss xmm0, dword ptr [edi + 0x18]
007d9d9d movss dword ptr [esp + 4], xmm3
007d9da3 movss dword ptr [esp], xmm3
007d9da8 push eax
007d9da9 push esi
007d9daa movss dword ptr [esp + 0x30], xmm0
007d9db0 call 0x7cec10
007d9db5 pop edi
007d9db6 mov eax, esi
007d9db8 pop esi
007d9db9 mov esp, ebp
007d9dbb pop ebp
007d9dbc ret 8
