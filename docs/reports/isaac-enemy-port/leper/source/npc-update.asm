006a8a40 push ebp
006a8a41 mov ebp, esp
006a8a43 and esp, 0xfffffff8
006a8a46 sub esp, 8
006a8a49 push esi
006a8a4a mov esi, ecx
006a8a4c push edi
006a8a4d cmp dword ptr [esi + 0x274], 0
006a8a54 jne 0x6a8d3d
006a8a5a cmp dword ptr [esi + 0x28], 0x3c5
006a8a61 jne 0x6a8bdf
006a8a67 mov ecx, dword ptr [esi + 0x160]
006a8a6d mov eax, ecx
006a8a6f mov edx, dword ptr [esi + 0x164]
006a8a75 and eax, 2
006a8a78 or eax, 0
006a8a7b je 0x6a8a91
006a8a7d and ecx, 0xfffffffd
006a8a80 mov dword ptr [esi + 0x164], edx
006a8a86 mov dword ptr [esi + 0x160], ecx
006a8a8c jmp 0x6a8be4
006a8a91 mov eax, dword ptr [esi + 0x294]
006a8a97 mov dword ptr [esi + 0x29c], eax
006a8a9d mov eax, dword ptr [esi + 0x298]
006a8aa3 mov dword ptr [esi + 0x2a0], eax
006a8aa9 cmp dword ptr [esi + 0x348], 0
006a8ab0 jg 0x6a8ac2
006a8ab2 push 1
006a8ab4 mov ecx, esi
006a8ab6 call 0x4bb2b0
006a8abb mov ecx, esi
006a8abd call 0x4bb870
006a8ac2 push 1
006a8ac4 mov ecx, esi
006a8ac6 mov byte ptr [esi + 0x16d], 1
006a8acd call 0x682280
006a8ad2 mov ecx, dword ptr [esi + 0x318]
006a8ad8 test ecx, ecx
006a8ada je 0x6a8afc
006a8adc mov eax, dword ptr [esi + 0x20]
006a8adf cmp eax, dword ptr [ecx + 0x20]
006a8ae2 jbe 0x6a8afc
006a8ae4 mov eax, dword ptr [esi + 0x294]
006a8aea mov dword ptr [ecx + 0x294], eax
006a8af0 mov eax, dword ptr [esi + 0x298]
006a8af6 mov dword ptr [ecx + 0x298], eax
006a8afc cmp dword ptr [esi + 0x2c], 0xa
006a8b00 jne 0x6a8be4
006a8b06 mov ecx, dword ptr [0xbfd65c]
006a8b0c xor edi, edi
006a8b0e mov eax, dword ptr [ecx + 0x1ba54]
006a8b14 sub eax, dword ptr [ecx + 0x1ba50]
006a8b1a sar eax, 2
006a8b1d test eax, eax
006a8b1f je 0x6a8be4
006a8b25 lea edx, [ecx + 0x1ba50]
006a8b2b mov ecx, dword ptr [edx + 4]
006a8b2e mov eax, ecx
006a8b30 sub eax, dword ptr [edx]
006a8b32 mov dword ptr [esp + 0xc], edx
006a8b36 test eax, 0xfffffffc
006a8b3b jne 0x6a8b53
006a8b3d push 0xb3f4d0
006a8b42 push 3
006a8b44 call 0x95e330
006a8b49 mov edx, dword ptr [esp + 0x14]
006a8b4d add esp, 8
006a8b50 mov ecx, dword ptr [edx + 4]
006a8b53 mov eax, dword ptr [edx]
006a8b55 sub ecx, eax
006a8b57 sar ecx, 2
006a8b5a cmp edi, ecx
006a8b5c jae 0x6a8b61
006a8b5e lea eax, [eax + edi*4]
006a8b61 mov ecx, dword ptr [eax]
006a8b63 cmp dword ptr [ecx + 0x32c], esi
006a8b69 jne 0x6a8bbf
006a8b6b movss xmm0, dword ptr [ecx + 0x1f68]
006a8b73 movss xmm1, dword ptr [ecx + 0x1f6c]
006a8b7b addss xmm0, dword ptr [esi + 0x294]
006a8b83 addss xmm1, dword ptr [esi + 0x298]
006a8b8b movss dword ptr [ecx + 0x294], xmm0
006a8b93 movss dword ptr [ecx + 0x298], xmm1
006a8b9b mov eax, dword ptr [esi + 0x2b8]
006a8ba1 mov dword ptr [ecx + 0x2b8], eax
006a8ba7 mov eax, dword ptr [esi + 0x2bc]
006a8bad mov dword ptr [ecx + 0x2bc], eax
006a8bb3 mov eax, dword ptr [esi + 0x2c4]
006a8bb9 mov dword ptr [ecx + 0x2c4], eax
006a8bbf mov ecx, dword ptr [0xbfd65c]
006a8bc5 inc edi
006a8bc6 mov eax, dword ptr [ecx + 0x1ba54]
006a8bcc sub eax, dword ptr [ecx + 0x1ba50]
006a8bd2 sar eax, 2
006a8bd5 cmp edi, eax
006a8bd7 jb 0x6a8b25
006a8bdd jmp 0x6a8be4
006a8bdf call 0x688240
006a8be4 test byte ptr [esi + 0xe68], 2
006a8beb je 0x6a8c08
006a8bed mov ecx, esi
006a8bef mov dword ptr [esi + 0xac4], 2
006a8bf9 call 0x699730
006a8bfe mov dword ptr [esi + 0xac4], 0
006a8c08 push 1
006a8c0a mov ecx, esi
006a8c0c call 0x6afeb0
006a8c11 mov ecx, dword ptr [esi + 0x160]
006a8c17 mov eax, dword ptr [esi + 0x164]
006a8c1d and ecx, 0x20
006a8c20 and eax, 0x2000000
006a8c25 or ecx, eax
006a8c27 jne 0x6a8ccc
006a8c2d cmp dword ptr [esi + 0x348], ecx
006a8c33 jg 0x6a8ccc
006a8c39 mov ecx, dword ptr [esi + 0xab4]
006a8c3f cmp ecx, 1
006a8c42 je 0x6a8ccc
006a8c48 cmp ecx, 0x12
006a8c4b je 0x6a8ccc
006a8c4d cmp ecx, 0x11
006a8c50 je 0x6a8ccc
006a8c52 mov eax, dword ptr [esi + 0x28]
006a8c55 cmp eax, 0x3e
006a8c58 jne 0x6a8c77
006a8c5a cmp dword ptr [esi + 0x2c], 3
006a8c5e je 0x6a8ca4
006a8c60 cmp eax, 0x33e
006a8c65 jne 0x6a8c84
006a8c67 cmp dword ptr [esi + 0x2c], 0xa
006a8c6b jne 0x6a8ccc
006a8c6d movss xmm0, dword ptr [esi + 0xb04]
006a8c75 jmp 0x6a8cac
006a8c77 cmp eax, 0x393
006a8c7c jne 0x6a8c60
006a8c7e cmp dword ptr [esi + 0x2c], 1
006a8c82 je 0x6a8c6d
006a8c84 cmp eax, 0x371
006a8c89 je 0x6a8c9f
006a8c8b cmp eax, 0x32f
006a8c90 je 0x6a8c9f
006a8c92 cmp eax, 0x33f
006a8c97 jne 0x6a8ccc
006a8c99 cmp dword ptr [esi + 0x2c], 0x14
006a8c9d jne 0x6a8ccc
006a8c9f cmp ecx, 6
006a8ca2 jne 0x6a8ccc
006a8ca4 movss xmm0, dword ptr [esi + 0xb00]
006a8cac mulss xmm0, dword ptr [esi + 0x2f4]
006a8cb4 mulss xmm0, dword ptr [0xb6a480]
006a8cbc addss xmm0, dword ptr [esi + 0x2a8]
006a8cc4 movss dword ptr [esi + 0x2a8], xmm0
006a8ccc cmp dword ptr [esi + 0x28], 0x5c
006a8cd0 jne 0x6a8d3d
006a8cd2 cmp dword ptr [esi + 0x2c], 1
006a8cd6 jne 0x6a8d3d
006a8cd8 mov ecx, dword ptr [esi + 0xb3c]
006a8cde test ecx, ecx
006a8ce0 je 0x6a8d3d
006a8ce2 mov eax, dword ptr [ecx + 0x28]
006a8ce5 sub eax, 0xa
006a8ce8 cmp eax, 0x3dd
006a8ced ja 0x6a8d3d
006a8cef movss xmm1, dword ptr [ecx + 0x294]
006a8cf7 movss xmm2, dword ptr [ecx + 0x298]
006a8cff subss xmm1, dword ptr [esi + 0x294]
006a8d07 subss xmm2, dword ptr [esi + 0x298]
006a8d0f movss dword ptr [esi + 0x28c], xmm1
006a8d17 xorps xmm1, xmmword ptr [0xb6c9b0]
006a8d1e movss dword ptr [esi + 0x290], xmm2
006a8d26 xorps xmm2, xmmword ptr [0xb6c9b0]
006a8d2d movss dword ptr [ecx + 0x28c], xmm1
006a8d35 movss dword ptr [ecx + 0x290], xmm2
006a8d3d pop edi
006a8d3e pop esi
006a8d3f mov esp, ebp
006a8d41 pop ebp
006a8d42 ret 
006a8d43 int3 
006a8d44 int3 
006a8d45 int3 
006a8d46 int3 
006a8d47 int3 
006a8d48 int3 
006a8d49 int3 
006a8d4a int3 
006a8d4b int3 
006a8d4c int3 
006a8d4d int3 
006a8d4e int3 
006a8d4f int3 
