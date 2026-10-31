00519980 push ebx
00519981 mov ebx, esp
00519983 sub esp, 8
00519986 and esp, 0xfffffff8
00519989 add esp, 4
0051998c push ebp
0051998d mov ebp, dword ptr [ebx + 4]
00519990 mov dword ptr [esp + 4], ebp
00519994 mov ebp, esp
00519996 sub esp, 0x10
00519999 push esi
0051999a mov esi, ecx
0051999c push edi
0051999d cmp dword ptr [esi + 0xab4], 0
005199a4 jne 0x519a00
005199a6 mov eax, dword ptr [esi + 0x2b8]
005199ac mov dword ptr [esi + 0xb00], eax
005199b2 mov eax, dword ptr [esi + 0x2bc]
005199b8 mov dword ptr [esi + 0xb04], eax
005199be mov dword ptr [esi + 0xab4], 4
005199c8 mov dword ptr [esi + 0x360], 0
005199d2 mov dword ptr [esi + 0x2d8], 0
005199dc mov dword ptr [esi + 0x2dc], 0
005199e6 mov dword ptr [esi + 0x17c], 0
005199f0 mov byte ptr [esi + 0xb8c], 0
005199f7 pop edi
005199f8 pop esi
005199f9 mov esp, ebp
005199fb pop ebp
005199fc mov esp, ebx
005199fe pop ebx
005199ff ret 
00519a00 cmp dword ptr [esi + 0x30], 1
00519a04 xorps xmm1, xmm1
00519a07 jne 0x519a54
00519a09 mov eax, dword ptr [esi + 0xb00]
00519a0f lea edi, [esi + 0x2b8]
00519a15 push ecx
00519a16 mov ecx, dword ptr [0xbfd65c]
00519a1c mov dword ptr [edi], eax
00519a1e mov eax, dword ptr [esi + 0xb04]
00519a24 mov dword ptr [edi + 4], eax
00519a27 lea eax, [esi + 0x294]
00519a2d mov ecx, dword ptr [ecx + 0x18190]
00519a33 mov dword ptr [esp], 0xc2a00000
00519a3a push eax
00519a3b call 0x7cf0a0
00519a40 test al, al
00519a42 jne 0x519b94
00519a48 mov eax, dword ptr [esi]
00519a4a mov ecx, esi
00519a4c call dword ptr [eax + 0x28]
00519a4f jmp 0x519b94
00519a54 mov edi, dword ptr [esi + 0x360]
00519a5a movss xmm2, dword ptr [0xb6a614]
00519a62 mov eax, dword ptr [esi + 0x314]
00519a68 movd xmm0, edi
00519a6c cvtdq2ps xmm0, xmm0
00519a6f divss xmm0, dword ptr [0xb6a9cc]
00519a77 subss xmm2, xmm0
00519a7b movss dword ptr [ebp - 0xc], xmm2
00519a80 test eax, eax
00519a82 je 0x519b38
00519a88 comiss xmm1, xmm2
00519a8b jbe 0x519b38
00519a91 movss xmm1, dword ptr [eax + 0x298]
00519a99 subss xmm1, dword ptr [esi + 0x298]
00519aa1 movss xmm2, dword ptr [eax + 0x294]
00519aa9 subss xmm2, dword ptr [esi + 0x294]
00519ab1 movaps xmm0, xmm1
00519ab4 movss dword ptr [ebp - 4], xmm1
00519ab9 mulss xmm0, xmm1
00519abd movaps xmm1, xmm2
00519ac0 movss dword ptr [ebp - 8], xmm2
00519ac5 mulss xmm1, xmm2
00519ac9 addss xmm0, xmm1
00519acd call 0x4228c0
00519ad2 comiss xmm0, dword ptr [0xb6a18c]
00519ad9 movss xmm2, dword ptr [ebp - 8]
00519ade jbe 0x519afd
00519ae0 movaps xmm1, xmm0
00519ae3 subss xmm1, dword ptr [0xb6a9c8]
00519aeb divss xmm1, xmm0
00519aef movaps xmm0, xmm1
00519af2 mulss xmm1, dword ptr [ebp - 4]
00519af7 mulss xmm2, xmm0
00519afb jmp 0x519b02
00519afd movss xmm1, dword ptr [ebp - 4]
00519b02 mov ecx, 0x2b
00519b07 movss xmm3, dword ptr [ebp - 0xc]
00519b0c sub ecx, edi
00519b0e xorps xmm3, xmmword ptr [0xb6c9b0]
00519b15 mov eax, 1
00519b1a cmp ecx, eax
00519b1c cmovg eax, ecx
00519b1f movd xmm0, eax
00519b23 cvtdq2ps xmm0, xmm0
00519b26 divss xmm1, xmm0
00519b2a divss xmm2, xmm0
00519b2e mulss xmm1, xmm3
00519b32 mulss xmm2, xmm3
00519b36 jmp 0x519b4b
00519b38 movaps xmm1, xmm2
00519b3b mulss xmm2, dword ptr [esi + 0xb00]
00519b43 mulss xmm1, dword ptr [esi + 0xb04]
00519b4b lea edi, [esi + 0x2b8]
00519b51 mov eax, edi
00519b53 movss dword ptr [edi], xmm2
00519b57 movss dword ptr [eax + 4], xmm1
00519b5c cmp dword ptr [esi + 0x314], 0
00519b63 jne 0x519b75
00519b65 mov eax, dword ptr [esi]
00519b67 mov ecx, esi
00519b69 call dword ptr [eax + 0x24]
00519b6c pop edi
00519b6d pop esi
00519b6e mov esp, ebp
00519b70 pop ebp
00519b71 mov esp, ebx
00519b73 pop ebx
00519b74 ret 
00519b75 mov eax, dword ptr [esi + 0x360]
00519b7b cmp eax, 0x2a
00519b7e jle 0x519b8d
00519b80 mov eax, dword ptr [esi]
00519b82 mov ecx, esi
00519b84 call dword ptr [eax + 0x28]
00519b87 mov eax, dword ptr [esi + 0x360]
00519b8d inc eax
00519b8e mov dword ptr [esi + 0x360], eax
00519b94 movss xmm3, dword ptr [edi]
00519b98 xorps xmm4, xmm4
00519b9b movss xmm2, dword ptr [edi + 4]
00519ba0 movaps xmm1, xmm3
00519ba3 movss xmm5, dword ptr [0xb6c980]
00519bab movaps xmm0, xmm2
00519bae andps xmm1, xmm5
00519bb1 andps xmm0, xmm5
00519bb4 comiss xmm1, xmm0
00519bb7 jbe 0x519bc8
00519bb9 xor eax, eax
00519bbb mov ecx, 2
00519bc0 comiss xmm4, xmm3
00519bc3 cmova ecx, eax
00519bc6 jmp 0x519bd7
00519bc8 xor ecx, ecx
00519bca comiss xmm4, xmm2
00519bcd setbe cl
00519bd0 lea ecx, [ecx*2 + 1]
00519bd7 movss xmm0, dword ptr [0xb6a1c8]
00519bdf mulss xmm2, xmm2
00519be3 mov dword ptr [ebp - 4], ecx
00519be6 mulss xmm3, xmm3
00519bea addss xmm2, xmm3
00519bee comiss xmm0, xmm2
00519bf1 jbe 0x519c91
00519bf7 movss xmm2, dword ptr [esi + 0xb00]
00519bff movss xmm3, dword ptr [esi + 0xb04]
00519c07 movaps xmm1, xmm2
00519c0a movaps xmm0, xmm3
00519c0d andps xmm1, xmm5
00519c10 andps xmm0, xmm5
00519c13 comiss xmm1, xmm0
00519c16 jbe 0x519c59
00519c18 comiss xmm4, xmm2
00519c1b jbe 0x519c39
00519c1d xor edi, edi
00519c1f mov byte ptr [esi + 0x13c], 1
00519c26 push edi
00519c27 push 0xb43138
00519c2c lea ecx, [esi + 0x3c]
00519c2f call 0x4054f0
00519c34 jmp 0x519cdf
00519c39 push 0
00519c3b push 0xb43138
00519c40 lea ecx, [esi + 0x3c]
00519c43 mov byte ptr [esi + 0x13c], 0
00519c4a mov edi, 2
00519c4f call 0x4054f0
00519c54 jmp 0x519cdf
00519c59 comiss xmm4, xmm3
00519c5c mov byte ptr [esi + 0x13c], 0
00519c63 jbe 0x519c7b
00519c65 push 0
00519c67 push 0xb406e4
00519c6c lea ecx, [esi + 0x3c]
00519c6f mov edi, 1
00519c74 call 0x4054f0
00519c79 jmp 0x519cdf
00519c7b push 0
00519c7d push 0xb406f0
00519c82 lea ecx, [esi + 0x3c]
00519c85 mov edi, 3
00519c8a call 0x4054f0
00519c8f jmp 0x519cdf
00519c91 test ecx, ecx
00519c93 sete al
00519c96 mov byte ptr [esi + 0x13c], al
00519c9c jmp dword ptr [ecx*4 + 0x519da4]
00519ca3 mov edi, dword ptr [ebp - 4]
00519ca6 lea ecx, [esi + 0x3c]
00519ca9 push 0
00519cab push 0xb43138
00519cb0 call 0x4054f0
00519cb5 jmp 0x519cdf
00519cb7 mov edi, dword ptr [ebp - 4]
00519cba lea ecx, [esi + 0x3c]
00519cbd push 0
00519cbf push 0xb406e4
00519cc4 call 0x4054f0
00519cc9 jmp 0x519cdf
00519ccb mov edi, dword ptr [ebp - 4]
00519cce lea ecx, [esi + 0x3c]
00519cd1 push 0
00519cd3 push 0xb406f0
00519cd8 call 0x4054f0
00519cdd jmp 0x519cdf
00519cdf cmp dword ptr [esi + 0x30], 0
00519ce3 jbe 0x519d9b
00519ce9 movss xmm1, dword ptr [esi + 0xb00]
00519cf1 movss xmm0, dword ptr [esi + 0xb04]
00519cf9 movaps xmm2, xmm1
00519cfc mulss xmm2, dword ptr [esi + 0x2b8]
00519d04 movaps xmm3, xmm0
00519d07 mulss xmm3, dword ptr [esi + 0x2bc]
00519d0f addss xmm3, xmm2
00519d13 mulss xmm1, xmm3
00519d17 mulss xmm0, xmm3
00519d1b call 0x447a80
00519d20 movaps xmm1, xmm0
00519d23 mulss xmm1, dword ptr [0xb6aa84]
00519d2b movss dword ptr [ebp - 4], xmm1
00519d30 jmp dword ptr [edi*4 + 0x519db4]
00519d37 movss xmm0, dword ptr [0xb6ab88]
00519d3f subss xmm0, xmm1
00519d43 jmp 0x519d5a
00519d45 addss xmm1, dword ptr [0xb6aae4]
00519d4d jmp 0x519d57
00519d4f subss xmm1, dword ptr [0xb6aae4]
00519d57 movaps xmm0, xmm1
00519d5a call 0x65a640
00519d5f movss dword ptr [ebp - 4], xmm0
00519d64 cmp dword ptr [esi + 0xbc], 0
00519d6b jg 0x519d8b
00519d6d cmp dword ptr [esi + 0x50], 0x10
00519d71 lea eax, [esi + 0x3c]
00519d74 jb 0x519d79
00519d76 mov eax, dword ptr [esi + 0x3c]
00519d79 push 0
00519d7b push eax
00519d7c push 0xa0830c
00519d81 push 3
00519d83 call 0x95e330
00519d88 add esp, 0x10
00519d8b mov eax, dword ptr [esi + 0xb8]
00519d91 movss xmm0, dword ptr [ebp - 4]
00519d96 movss dword ptr [eax + 0x3c], xmm0
00519d9b pop edi
00519d9c pop esi
00519d9d mov esp, ebp
00519d9f pop ebp
00519da0 mov esp, ebx
00519da2 pop ebx
00519da3 ret 
