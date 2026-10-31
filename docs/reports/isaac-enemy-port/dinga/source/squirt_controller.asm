00522840 push ebp
00522841 mov ebp, esp
00522843 and esp, 0xfffffff8
00522846 sub esp, 0xf4
0052284c push ebx
0052284d push esi
0052284e push edi
0052284f mov edi, ecx
00522851 mov dword ptr [esp + 0x7c], edi
00522855 mov ecx, dword ptr [edi + 0xab4]
0052285b test ecx, ecx
0052285d jne 0x522939
00522863 cmp dword ptr [edi + 0x2c], 1
00522867 lea ecx, [edi + 0x1dc]
0052286d mov dword ptr [edi + 0xab4], 3
00522877 jne 0x5228d9
00522879 movaps xmm0, xmmword ptr [0xb6bd30]
00522880 lea eax, [esp + 0x80]
00522887 mov dword ptr [esp + 0xa0], 0
00522892 xorps xmm1, xmm1
00522895 mov dword ptr [esp + 0xa4], 0
005228a0 mov dword ptr [esp + 0xa8], 0
005228ab cmp ecx, eax
005228ad je 0x523a7c
005228b3 mov eax, dword ptr [esp + 0xa8]
005228ba movups xmmword ptr [ecx], xmm0
005228bd movq xmm0, qword ptr [esp + 0xa0]
005228c6 movq qword ptr [ecx + 0x20], xmm0
005228cb movups xmmword ptr [ecx + 0x10], xmm1
005228cf mov dword ptr [ecx + 0x28], eax
005228d2 pop edi
005228d3 pop esi
005228d4 pop ebx
005228d5 mov esp, ebp
005228d7 pop ebp
005228d8 ret 
005228d9 movaps xmm1, xmmword ptr [0xb6bd30]
005228e0 lea eax, [esp + 0xac]
005228e7 mov dword ptr [esp + 0xcc], 0x3e828283
005228f2 xorps xmm0, xmm0
005228f5 mov dword ptr [esp + 0xd0], 0x3e24a4a5
00522900 mov dword ptr [esp + 0xd4], 0x3e0c8c8d
0052290b cmp ecx, eax
0052290d je 0x523a7c
00522913 mov eax, dword ptr [esp + 0xd4]
0052291a movups xmmword ptr [ecx + 0x10], xmm0
0052291e movq xmm0, qword ptr [esp + 0xcc]
00522927 movq qword ptr [ecx + 0x20], xmm0
0052292c movups xmmword ptr [ecx], xmm1
0052292f mov dword ptr [ecx + 0x28], eax
00522932 pop edi
00522933 pop esi
00522934 pop ebx
00522935 mov esp, ebp
00522937 pop ebp
00522938 ret 
00522939 mov edx, dword ptr [edi + 0x28]
0052293c xorps xmm1, xmm1
0052293f cmp edx, 0x367
00522945 jne 0x522964
00522947 mov eax, dword ptr [0xbfd65c]
0052294c mov eax, dword ptr [eax + 0x18190]
00522952 movss xmm0, dword ptr [eax + 0x7134]
0052295a mov eax, 6
0052295f comiss xmm0, xmm1
00522962 ja 0x522969
00522964 mov eax, 5
00522969 mov dword ptr [edi + 0x17c], eax
0052296f cmp byte ptr [edi + 0x16b], 0
00522976 je 0x522c70
0052297c cmp word ptr [edi + 0xbc6], 0
00522984 jne 0x522c70
0052298a cmp edx, 0x367
00522990 jne 0x522b1a
00522996 mov ebx, 2
0052299b nop dword ptr [eax + eax]
005229a0 call 0x6c3d90
005229a5 movd xmm0, eax
005229a9 cvtdq2pd xmm0, xmm0
005229ad shr eax, 0x1f
005229b0 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
005229b9 cvtpd2ps xmm0, xmm0
005229bd mulss xmm0, dword ptr [0xb6a19c]
005229c5 mulss xmm0, dword ptr [0xb6a874]
005229cd addss xmm0, xmm0
005229d1 movss dword ptr [esp + 0x20], xmm0
005229d7 call 0x411fe0
005229dc movss dword ptr [esp + 0x1c], xmm0
005229e2 movss xmm0, dword ptr [esp + 0x20]
005229e8 call 0x412010
005229ed movss dword ptr [esp + 0x20], xmm0
005229f3 call 0x6c3d90
005229f8 movss xmm1, dword ptr [esp + 0x1c]
005229fe mulss xmm1, dword ptr [0xb6a974]
00522a06 mov ecx, dword ptr [0xbfd65c]
00522a0c push 0
00522a0e push eax
00522a0f addss xmm1, dword ptr [edi + 0x294]
00522a17 push 0
00522a19 push edi
00522a1a push 0xc02fec
00522a1f lea eax, [esp + 0x40]
00522a23 movss dword ptr [esp + 0x40], xmm1
00522a29 movaps xmm1, xmm0
00522a2c mulss xmm1, dword ptr [0xb6a974]
00522a34 push eax
00522a35 push 0
00522a37 push 0x366
00522a3c addss xmm1, dword ptr [edi + 0x298]
00522a44 movss dword ptr [esp + 0x50], xmm1
00522a4a call 0x6d0ca0
00522a4f mov esi, eax
00522a51 call 0x6c3d90
00522a56 movss xmm2, dword ptr [esi + 0x2c4]
00522a5e movss xmm3, dword ptr [esp + 0x1c]
00522a64 movss xmm4, dword ptr [esp + 0x20]
00522a6a movd xmm0, eax
00522a6e cvtdq2pd xmm0, xmm0
00522a72 shr eax, 0x1f
00522a75 ucomiss xmm2, dword ptr [0xb6a18c]
00522a7c addsd xmm0, qword ptr [eax*8 + 0xb6c940]
00522a85 lahf 
00522a86 cvtpd2ps xmm0, xmm0
00522a8a mulss xmm0, dword ptr [0xb6a19c]
00522a92 addss xmm0, xmm0
00522a96 addss xmm0, dword ptr [0xb6a8cc]
00522a9e mulss xmm3, xmm0
00522aa2 mulss xmm4, xmm0
00522aa6 test ah, 0x44
00522aa9 jnp 0x522ae6
00522aab movss xmm1, dword ptr [esi + 0x2f4]
00522ab3 movaps xmm0, xmm1
00522ab6 mulss xmm1, xmm4
00522aba mulss xmm0, xmm3
00522abe divss xmm1, xmm2
00522ac2 divss xmm0, xmm2
00522ac6 addss xmm1, dword ptr [esi + 0x2bc]
00522ace addss xmm0, dword ptr [esi + 0x2b8]
00522ad6 movss dword ptr [esi + 0x2bc], xmm1
00522ade movss dword ptr [esi + 0x2b8], xmm0
00522ae6 mov eax, dword ptr [esi + 0x164]
00522aec mov ecx, esi
00522aee and dword ptr [esi + 0x160], 0xfffffffb
00522af5 mov dword ptr [esi + 0x164], eax
00522afb mov eax, dword ptr [esi]
00522afd mov dword ptr [esi + 0xab4], 4
00522b07 call dword ptr [eax + 0xc]
00522b0a sub ebx, 1
00522b0d jne 0x5229a0
00522b13 pop edi
00522b14 pop esi
00522b15 pop ebx
00522b16 mov esp, ebp
00522b18 pop ebp
00522b19 ret 
00522b1a cmp dword ptr [edi + 0x2c], 1
00522b1e jne 0x522bc7
00522b24 call 0x6c3d90
00522b29 movss xmm0, dword ptr [edi + 0x294]
00522b31 addss xmm0, dword ptr [0xb6a974]
00522b39 mov ecx, dword ptr [0xbfd65c]
00522b3f push 0
00522b41 push eax
00522b42 push 0
00522b44 push edi
00522b45 movss dword ptr [esp + 0x3c], xmm0
00522b4b lea eax, [esp + 0x3c]
00522b4f movss xmm0, dword ptr [edi + 0x298]
00522b57 push 0xc02fec
00522b5c addss xmm0, xmm1
00522b60 push eax
00522b61 push 1
00522b63 push 0xf
00522b65 movss dword ptr [esp + 0x50], xmm0
00522b6b call 0x6d0ca0
00522b70 call 0x6c3d90
00522b75 movss xmm0, dword ptr [edi + 0x294]
00522b7d subss xmm0, dword ptr [0xb6a974]
00522b85 mov ecx, dword ptr [0xbfd65c]
00522b8b push 0
00522b8d push eax
00522b8e push 0
00522b90 push edi
00522b91 movss dword ptr [esp + 0x3c], xmm0
00522b97 lea eax, [esp + 0x3c]
00522b9b movss xmm0, dword ptr [edi + 0x298]
00522ba3 addss xmm0, dword ptr [0xb6a18c]
00522bab push 0xc02fec
00522bb0 push eax
00522bb1 push 1
00522bb3 push 0xf
00522bb5 movss dword ptr [esp + 0x50], xmm0
00522bbb call 0x6d0ca0
00522bc0 pop edi
00522bc1 pop esi
00522bc2 pop ebx
00522bc3 mov esp, ebp
00522bc5 pop ebp
00522bc6 ret 
00522bc7 call 0x6c3d90
00522bcc movss xmm0, dword ptr [edi + 0x294]
00522bd4 addss xmm0, dword ptr [0xb6a974]
00522bdc mov ecx, dword ptr [0xbfd65c]
00522be2 push 0
00522be4 push eax
00522be5 push 0
00522be7 push edi
00522be8 movss dword ptr [esp + 0x3c], xmm0
00522bee lea eax, [esp + 0x3c]
00522bf2 movss xmm0, dword ptr [edi + 0x298]
00522bfa push 0xc02fec
00522bff addss xmm0, xmm1
00522c03 push eax
00522c04 push 0
00522c06 push 0xd9
00522c0b movss dword ptr [esp + 0x50], xmm0
00522c11 call 0x6d0ca0
00522c16 call 0x6c3d90
00522c1b movss xmm0, dword ptr [edi + 0x294]
00522c23 subss xmm0, dword ptr [0xb6a974]
00522c2b mov ecx, dword ptr [0xbfd65c]
00522c31 push 0
00522c33 push eax
00522c34 push 0
00522c36 push edi
00522c37 movss dword ptr [esp + 0x3c], xmm0
00522c3d lea eax, [esp + 0x3c]
00522c41 movss xmm0, dword ptr [edi + 0x298]
00522c49 addss xmm0, dword ptr [0xb6a18c]
00522c51 push 0xc02fec
00522c56 push eax
00522c57 push 0
00522c59 push 0xd9
00522c5e movss dword ptr [esp + 0x50], xmm0
00522c64 call 0x6d0ca0
00522c69 pop edi
00522c6a pop esi
00522c6b pop ebx
00522c6c mov esp, ebp
00522c6e pop ebp
00522c6f ret 
00522c70 movss xmm0, dword ptr [edi + 0x2c4]
00522c78 mov ebx, 3
00522c7d mulss xmm0, dword ptr [0xb6a5d8]
00522c85 movss dword ptr [edi + 0x2c4], xmm0
00522c8d cmp ecx, ebx
00522c8f jne 0x522e1b
00522c95 push 0
00522c97 push 0xb3fd8c
00522c9c lea ecx, [edi + 0x3c]
00522c9f call 0x4054f0
00522ca4 cmp dword ptr [edi + 0xe6c], -1
00522cab je 0x522cf5
00522cad movss xmm2, dword ptr [0xb6a2cc]
00522cb5 lea eax, [esp + 0x10]
00522cb9 push eax
00522cba mov ecx, edi
00522cbc call 0x6af0c0
00522cc1 mov ecx, eax
00522cc3 movss xmm0, dword ptr [ecx]
00522cc7 ucomiss xmm0, dword ptr [0xc02fec]
00522cce lahf 
00522ccf test ah, 0x44
00522cd2 jp 0x522cec
00522cd4 movss xmm0, dword ptr [ecx + 4]
00522cd9 ucomiss xmm0, dword ptr [0xc02ff0]
00522ce0 lahf 
00522ce1 test ah, 0x44
00522ce4 jp 0x522cec
00522ce6 xor eax, eax
00522ce8 test eax, eax
00522cea jmp 0x522d18
00522cec mov eax, 1
00522cf1 test eax, eax
00522cf3 jmp 0x522d18
00522cf5 call 0x6c3d90
00522cfa xor edx, edx
00522cfc mov ecx, 5
00522d01 div ecx
00522d03 test edx, edx
00522d05 jne 0x522e06
00522d0b push dword ptr [edi + 0x20]
00522d0e push ecx
00522d0f mov ecx, edi
00522d11 call 0x684790
00522d16 test al, al
00522d18 je 0x522e06
00522d1e mov eax, dword ptr [edi + 0x164]
00522d24 mov ecx, dword ptr [edi + 0x160]
00522d2a mov dword ptr [esp + 0x14], eax
00522d2e mov eax, ecx
00522d30 and eax, 0x1000800
00522d35 or eax, 0
00522d38 je 0x522da0
00522d3a cmp dword ptr [edi + 0xe6c], -1
00522d41 jne 0x522da0
00522d43 push ecx
00522d44 mov dword ptr [edi + 0xb00], 0
00522d4e lea eax, [esp + 0x14]
00522d52 mov dword ptr [esp], 0x3f800000
00522d59 mov ecx, edi
00522d5b mov dword ptr [edi + 0xab4], 4
00522d65 push eax
00522d66 mov dword ptr [edi + 0xb10], 0
00522d70 call 0x695a30
00522d75 movss xmm1, dword ptr [eax]
00522d79 movss xmm0, dword ptr [eax + 4]
00522d7e subss xmm1, dword ptr [edi + 0x294]
00522d86 subss xmm0, dword ptr [edi + 0x298]
00522d8e movss dword ptr [edi + 0x2b8], xmm1
00522d96 movss dword ptr [edi + 0x2bc], xmm0
00522d9e jmp 0x522e06
00522da0 and ecx, 0x200
00522da6 or ecx, 0
00522da9 je 0x522df2
00522dab cmp dword ptr [edi + 0xe6c], -1
00522db2 jne 0x522df2
00522db4 mov dword ptr [edi + 0xb00], 0
00522dbe lea eax, [esp + 0x10]
00522dc2 mov dword ptr [edi + 0xab4], 4
00522dcc push eax
00522dcd mov dword ptr [edi + 0xb10], 0
00522dd7 call 0x659290
00522ddc add esp, 4
00522ddf mov ecx, dword ptr [eax]
00522de1 mov dword ptr [edi + 0x2b8], ecx
00522de7 mov eax, dword ptr [eax + 4]
00522dea mov dword ptr [edi + 0x2bc], eax
00522df0 jmp 0x522e06
00522df2 mov dword ptr [edi + 0xab4], 8
00522dfc mov dword ptr [edi + 0xb10], 0
00522e06 movss xmm0, dword ptr [edi + 0x2c4]
00522e0e mulss xmm0, dword ptr [0xb6a50c]
00522e16 jmp 0x52339d
00522e1b cmp ecx, 4
00522e1e je 0x52313f
00522e24 cmp ecx, 6
00522e27 je 0x52313f
00522e2d cmp ecx, 8
00522e30 jne 0x522fb7
00522e36 push 0
00522e38 push 0xb40314
00522e3d lea ecx, [edi + 0x3c]
00522e40 call 0x4054f0
00522e45 movss xmm2, dword ptr [0xb6ae44]
00522e4d mov ecx, edi
00522e4f push 1
00522e51 call 0x6af8d0
00522e56 push 0xb40de4
00522e5b lea ecx, [edi + 0x3c]
00522e5e call 0x4060f0
00522e63 test al, al
00522e65 je 0x522f7c
00522e6b mov ecx, edi
00522e6d lea esi, [edi + 0x294]
00522e73 call 0x695680
00522e78 lea ecx, [esp + 0x10]
00522e7c movss xmm0, dword ptr [eax + 0x294]
00522e84 movss xmm1, dword ptr [eax + 0x298]
00522e8c lea eax, [esp + 0x34]
00522e90 subss xmm0, dword ptr [esi]
00522e94 subss xmm1, dword ptr [esi + 4]
00522e99 push eax
00522e9a movss dword ptr [esp + 0x14], xmm0
00522ea0 movss dword ptr [esp + 0x18], xmm1
00522ea6 call 0x962560
00522eab cmp dword ptr [edi + 0xe6c], -1
00522eb2 je 0x522f13
00522eb4 push esi
00522eb5 push ecx
00522eb6 lea eax, [esp + 0x18]
00522eba mov ecx, edi
00522ebc push eax
00522ebd call 0x6afac0
00522ec2 add esp, 4
00522ec5 mov ecx, eax
00522ec7 call 0x962ca0
00522ecc test al, al
00522ece je 0x522f13
00522ed0 lea eax, [esp + 0x34]
00522ed4 mov ecx, edi
00522ed6 push eax
00522ed7 call 0x6afac0
00522edc lea ecx, [esp + 0x10]
00522ee0 movss xmm0, dword ptr [eax]
00522ee4 subss xmm0, dword ptr [esi]
00522ee8 movss dword ptr [esp + 0x10], xmm0
00522eee movss xmm0, dword ptr [eax + 4]
00522ef3 lea eax, [esp + 0x4c]
00522ef7 subss xmm0, dword ptr [esi + 4]
00522efc push eax
00522efd movss dword ptr [esp + 0x18], xmm0
00522f03 call 0x962560
00522f08 movss xmm2, dword ptr [eax]
00522f0c movss xmm3, dword ptr [eax + 4]
00522f11 jmp 0x522f1f
00522f13 movss xmm3, dword ptr [esp + 0x38]
00522f19 movss xmm2, dword ptr [esp + 0x34]
00522f1f mulss xmm3, dword ptr [0xb6a9c8]
00522f27 push ecx
00522f28 movss xmm1, dword ptr [edi + 0x2c4]
00522f30 mulss xmm2, dword ptr [0xb6a9c8]
00522f38 mov dword ptr [esp], 0x3f800000
00522f3f divss xmm3, xmm1
00522f43 push 0
00522f45 push 0x64
00522f47 push ecx
00522f48 mov dword ptr [esp], 0x3f800000
00522f4f mov ecx, edi
00522f51 push 0x39
00522f53 divss xmm2, xmm1
00522f57 addss xmm3, dword ptr [edi + 0x2bc]
00522f5f addss xmm2, dword ptr [edi + 0x2b8]
00522f67 movss dword ptr [edi + 0x2bc], xmm3
00522f6f movss dword ptr [edi + 0x2b8], xmm2
00522f77 call 0x6ad720
00522f7c cmp dword ptr [edi + 0x70], 0
00522f80 je 0x522f8f
00522f82 cmp byte ptr [edi + 0x80], 0
00522f89 jne 0x5233a5
00522f8f xor eax, eax
00522f91 mov dword ptr [edi + 0xb00], 0
00522f9b cmp dword ptr [edi + 0x28], 0x367
00522fa2 sete al
00522fa5 lea eax, [eax*2 + 4]
00522fac mov dword ptr [edi + 0xab4], eax
00522fb2 jmp 0x5233a5
00522fb7 cmp ecx, 9
00522fba jne 0x5233a5
00522fc0 push 0
00522fc2 push 0xb4032c
00522fc7 lea ecx, [edi + 0x3c]
00522fca call 0x4054f0
00522fcf movss xmm2, dword ptr [0xb6ae44]
00522fd7 mov ecx, edi
00522fd9 push 1
00522fdb call 0x6af8d0
00522fe0 push 0xb40de4
00522fe5 lea ecx, [edi + 0x3c]
00522fe8 call 0x4060f0
00522fed test al, al
00522fef je 0x523113
00522ff5 mov ecx, edi
00522ff7 call 0x695680
00522ffc lea esi, [edi + 0x294]
00523002 lea ecx, [esp + 0x10]
00523006 movss xmm0, dword ptr [eax + 0x294]
0052300e movss xmm1, dword ptr [eax + 0x298]
00523016 lea eax, [esp + 0x34]
0052301a subss xmm0, dword ptr [esi]
0052301e subss xmm1, dword ptr [esi + 4]
00523023 push eax
00523024 movss dword ptr [esp + 0x14], xmm0
0052302a movss dword ptr [esp + 0x18], xmm1
00523030 call 0x962560
00523035 cmp dword ptr [edi + 0xe6c], -1
0052303c je 0x52309d
0052303e push esi
0052303f push ecx
00523040 lea eax, [esp + 0x18]
00523044 mov ecx, edi
00523046 push eax
00523047 call 0x6afac0
0052304c add esp, 4
0052304f mov ecx, eax
00523051 call 0x962ca0
00523056 test al, al
00523058 je 0x52309d
0052305a lea eax, [esp + 0x34]
0052305e mov ecx, edi
00523060 push eax
00523061 call 0x6afac0
00523066 lea ecx, [esp + 0x10]
0052306a movss xmm0, dword ptr [eax]
0052306e subss xmm0, dword ptr [esi]
00523072 movss dword ptr [esp + 0x10], xmm0
00523078 movss xmm0, dword ptr [eax + 4]
0052307d lea eax, [esp + 0x4c]
00523081 subss xmm0, dword ptr [esi + 4]
00523086 push eax
00523087 movss dword ptr [esp + 0x18], xmm0
0052308d call 0x962560
00523092 movss xmm1, dword ptr [eax]
00523096 movss xmm2, dword ptr [eax + 4]
0052309b jmp 0x5230a9
0052309d movss xmm2, dword ptr [esp + 0x38]
005230a3 movss xmm1, dword ptr [esp + 0x34]
005230a9 movss xmm0, dword ptr [edi + 0x2c4]
005230b1 ucomiss xmm0, dword ptr [0xb6a18c]
005230b8 mulss xmm1, dword ptr [0xb6a9c8]
005230c0 mulss xmm2, dword ptr [0xb6a9c8]
005230c8 lahf 
005230c9 test ah, 0x44
005230cc jnp 0x5230f6
005230ce divss xmm1, xmm0
005230d2 divss xmm2, xmm0
005230d6 addss xmm1, dword ptr [edi + 0x2b8]
005230de addss xmm2, dword ptr [edi + 0x2bc]
005230e6 movss dword ptr [edi + 0x2b8], xmm1
005230ee movss dword ptr [edi + 0x2bc], xmm2
005230f6 push ecx
005230f7 mov dword ptr [esp], 0x3f800000
005230fe push 0
00523100 push 0x64
00523102 push ecx
00523103 mov dword ptr [esp], 0x3f800000
0052310a mov ecx, edi
0052310c push 0x39
0052310e call 0x6ad720
00523113 cmp dword ptr [edi + 0x70], 0
00523117 je 0x523126
00523119 cmp byte ptr [edi + 0x80], 0
00523120 jne 0x5233a5
00523126 mov dword ptr [edi + 0xb00], 0
00523130 mov dword ptr [edi + 0xab4], 4
0052313a jmp 0x5233a5
0052313f push 0
00523141 push 0xb40de4
00523146 lea ecx, [edi + 0x3c]
00523149 call 0x4054f0
0052314e cmp dword ptr [edi + 0x28], 0x367
00523155 jne 0x523291
0052315b mov esi, dword ptr [edi + 0xab4]
00523161 cmp esi, 6
00523164 jne 0x52317d
00523166 movss xmm2, dword ptr [0xb6ae44]
0052316e mov ecx, edi
00523170 push 1
00523172 call 0x6af8d0
00523177 mov esi, dword ptr [edi + 0xab4]
0052317d movss xmm2, dword ptr [edi + 0x2f4]
00523185 lea ebx, [edi + 0x2b8]
0052318b movss xmm0, dword ptr [0xb6a974]
00523193 movss dword ptr [esp + 0x20], xmm2
00523199 addss xmm2, dword ptr [edi + 0xb00]
005231a1 comiss xmm0, xmm2
005231a4 movss dword ptr [esp + 0x40], xmm2
005231aa movss dword ptr [edi + 0xb00], xmm2
005231b2 jbe 0x52323d
005231b8 push ecx
005231b9 lea eax, [esp + 0x14]
005231bd mov dword ptr [esp], 0x3f000000
005231c4 push eax
005231c5 mov ecx, ebx
005231c7 call 0x9628d0
005231cc movss xmm3, dword ptr [edi + 0x2c4]
005231d4 mov ecx, eax
005231d6 ucomiss xmm3, dword ptr [0xb6a18c]
005231dd lahf 
005231de test ah, 0x44
005231e1 jnp 0x523235
005231e3 movss xmm2, dword ptr [esp + 0x20]
005231e9 movss xmm1, dword ptr [ecx + 4]
005231ee movaps xmm0, xmm2
005231f1 mulss xmm0, dword ptr [ecx]
005231f5 mulss xmm2, xmm1
005231f9 divss xmm0, xmm3
005231fd divss xmm2, xmm3
00523201 addss xmm0, dword ptr [ebx]
00523205 addss xmm2, dword ptr [ebx + 4]
0052320a movss dword ptr [ebx], xmm0
0052320e movss dword ptr [ebx + 4], xmm2
00523213 mov esi, dword ptr [edi + 0xab4]
00523219 movss xmm2, dword ptr [edi + 0xb00]
00523221 mov ebx, 3
00523226 cmp esi, 6
00523229 jne 0x52327b
0052322b movss xmm0, dword ptr [0xb6a940]
00523233 jmp 0x523283
00523235 movss xmm2, dword ptr [esp + 0x40]
0052323b jmp 0x523221
0052323d movss xmm0, dword ptr [ebx + 4]
00523242 movss xmm1, dword ptr [ebx]
00523246 mulss xmm0, xmm0
0052324a mulss xmm1, xmm1
0052324e addss xmm1, xmm0
00523252 movss xmm0, dword ptr [0xb6a95c]
0052325a comiss xmm0, xmm1
0052325d jbe 0x523221
0052325f mov ebx, 3
00523264 cmp esi, 6
00523267 mov eax, ebx
00523269 mov ecx, 9
0052326e cmove eax, ecx
00523271 mov esi, eax
00523273 mov dword ptr [edi + 0xab4], esi
00523279 jmp 0x523226
0052327b movss xmm0, dword ptr [0xb6aa3c]
00523283 comiss xmm2, xmm0
00523286 jbe 0x5233a5
0052328c jmp 0x52338d
00523291 movss xmm1, dword ptr [edi + 0x2f4]
00523299 lea esi, [edi + 0x2b8]
0052329f movss xmm0, dword ptr [0xb6a974]
005232a7 movss dword ptr [esp + 0x20], xmm1
005232ad addss xmm1, dword ptr [edi + 0xb00]
005232b5 comiss xmm0, xmm1
005232b8 movss dword ptr [edi + 0xb00], xmm1
005232c0 jbe 0x523323
005232c2 push ecx
005232c3 lea eax, [esp + 0x14]
005232c7 mov dword ptr [esp], 0x3f000000
005232ce push eax
005232cf mov ecx, esi
005232d1 call 0x9628d0
005232d6 movss xmm3, dword ptr [edi + 0x2c4]
005232de mov ecx, eax
005232e0 ucomiss xmm3, dword ptr [0xb6a18c]
005232e7 lahf 
005232e8 test ah, 0x44
005232eb jnp 0x523372
005232f1 movss xmm2, dword ptr [esp + 0x20]
005232f7 movss xmm1, dword ptr [ecx + 4]
005232fc movaps xmm0, xmm2
005232ff mulss xmm0, dword ptr [ecx]
00523303 mulss xmm2, xmm1
00523307 divss xmm0, xmm3
0052330b divss xmm2, xmm3
0052330f addss xmm0, dword ptr [esi]
00523313 addss xmm2, dword ptr [esi + 4]
00523318 movss dword ptr [esi], xmm0
0052331c movss dword ptr [esi + 4], xmm2
00523321 jmp 0x523372
00523323 movss xmm0, dword ptr [esi + 4]
00523328 movss xmm1, dword ptr [esi]
0052332c mulss xmm0, xmm0
00523330 mulss xmm1, xmm1
00523334 addss xmm1, xmm0
00523338 movss xmm0, dword ptr [0xb6a614]
00523340 comiss xmm0, xmm1
00523343 jbe 0x52334d
00523345 mov dword ptr [edi + 0xab4], ebx
0052334b jmp 0x523372
0052334d movss xmm0, dword ptr [0xb6a95c]
00523355 comiss xmm0, xmm1
00523358 jbe 0x523372
0052335a movss xmm0, dword ptr [edi + 0x2c4]
00523362 mulss xmm0, dword ptr [0xb6a560]
0052336a movss dword ptr [edi + 0x2c4], xmm0
00523372 cmp byte ptr [edi + 0x188], 0
00523379 mov eax, dword ptr [edi + 0xb10]
0052337f je 0x523388
00523381 inc eax
00523382 mov dword ptr [edi + 0xb10], eax
00523388 cmp eax, 4
0052338b jle 0x5233a5
0052338d movss xmm0, dword ptr [edi + 0x2c4]
00523395 mulss xmm0, dword ptr [0xb6a588]
0052339d movss dword ptr [edi + 0x2c4], xmm0
005233a5 call 0x6c3d90
005233aa xor edx, edx
005233ac mov ecx, 0xa
005233b1 div ecx
005233b3 test edx, edx
005233b5 jne 0x523412
005233b7 call 0x6c3d90
005233bc push ecx
005233bd mov ecx, edi
005233bf movd xmm0, eax
005233c3 cvtdq2pd xmm0, xmm0
005233c7 shr eax, 0x1f
005233ca addsd xmm0, qword ptr [eax*8 + 0xb6c940]
005233d3 cvtpd2ps xmm0, xmm0
005233d7 mulss xmm0, dword ptr [0xb6a19c]
005233df mulss xmm0, dword ptr [0xb6a480]
005233e7 addss xmm0, dword ptr [0xb6a350]
005233ef movss dword ptr [esp], xmm0
005233f4 call 0x68d7b0
005233f9 push 1
005233fb push 0
005233fd push 0xff
00523402 mov edx, dword ptr [eax]
00523404 lea ecx, [edi + 0x1dc]
0052340a push -1
0052340c push ecx
0052340d mov ecx, eax
0052340f call dword ptr [edx + 0x38]
00523412 xorps xmm0, xmm0
00523415 comiss xmm0, dword ptr [edi + 0x2b8]
0052341c seta al
0052341f cmp dword ptr [edi + 0xab4], 9
00523426 mov byte ptr [edi + 0x13c], al
0052342c jne 0x523456
0052342e cmp dword ptr [edi + 0xe6c], -1
00523435 jne 0x523456
00523437 mov ecx, edi
00523439 call 0x695680
0052343e movss xmm0, dword ptr [edi + 0x294]
00523446 comiss xmm0, dword ptr [eax + 0x294]
0052344d seta al
00523450 mov byte ptr [edi + 0x13c], al
00523456 cmp dword ptr [edi + 0x2c], 1
0052345a jne 0x523a7c
00523460 mov eax, dword ptr [edi + 0x160]
00523466 and eax, 0x4000
0052346b or eax, 0
0052346e jne 0x523a7c
00523474 mov esi, dword ptr [0xbfd65c]
0052347a mov ecx, esi
0052347c call 0x6d0380
00523481 test al, al
00523483 jne 0x523a7c
00523489 mov eax, dword ptr [esi + 0x1a30dc]
0052348f cdq 
00523490 idiv ebx
00523492 test edx, edx
00523494 jne 0x523a7c
0052349a mov eax, dword ptr [edi + 0xab4]
005234a0 cmp eax, 4
005234a3 je 0x5234c3
005234a5 cmp eax, 8
005234a8 jne 0x523a7c
005234ae push 0xb40de4
005234b3 lea ecx, [edi + 0x3c]
005234b6 call 0x406150
005234bb test al, al
005234bd je 0x523a7c
005234c3 mov eax, dword ptr [0xbfd65c]
005234c8 lea ebx, [edi + 0x294]
005234ce mov dword ptr [esp + 0x4c], ebx
005234d2 mov dword ptr [esp + 0x28], eax
005234d6 call 0x6c3d90
005234db mov dword ptr [esp + 0x40], eax
005234df lea eax, [esp + 0x40]
005234e3 push eax
005234e4 lea eax, [esp + 0x24]
005234e8 mov dword ptr [esp + 0x24], 0
005234f0 push eax
005234f1 push edi
005234f2 push 0xc02fec
005234f7 push ebx
005234f8 lea eax, [esp + 0x30]
005234fc mov dword ptr [esp + 0x30], 0x1a
00523504 push eax
00523505 lea eax, [esp + 0x54]
00523509 mov dword ptr [esp + 0x54], 0x3e8
00523511 push eax
00523512 call 0x800fb0
00523517 mov eax, dword ptr [edi + 0x160]
0052351d mov ecx, dword ptr [esp + 0x3c]
00523521 and eax, 0x20000000
00523526 or eax, 0
00523529 mov dword ptr [esp + 0x44], ecx
0052352d je 0x523566
0052352f cmp ecx, 0x3e8
00523535 jne 0x523566
00523537 mov esi, dword ptr [esp + 0x1c]
0052353b lea eax, [esi - 0x16]
0052353e cmp eax, 4
00523541 ja 0x52356a
00523543 jmp dword ptr [eax*4 + 0x523a84]
0052354a mov esi, 0x35
0052354f jmp 0x52356a
00523551 mov esi, 0x2e
00523556 jmp 0x52356a
00523558 mov esi, 0x2c
0052355d jmp 0x52356a
0052355f mov esi, 0x2d
00523564 jmp 0x52356a
00523566 mov esi, dword ptr [esp + 0x1c]
0052356a push 0
0052356c push ecx
0052356d mov ecx, dword ptr [esp + 0x30]
00523571 mov ecx, dword ptr [ecx + 0x1c3198]
00523577 call 0x6c4b30
0052357c mov ebx, eax
0052357e test ebx, ebx
00523580 je 0x5239fa
00523586 mov eax, dword ptr [0xa064c0]
0052358b mov dword ptr [esp + 0x34], eax
0052358f call eax
00523591 mov ecx, dword ptr [edi + 0x28]
00523594 mov dword ptr [ebx + 0x34], ecx
00523597 mov ecx, dword ptr [edi + 0x2c]
0052359a mov dword ptr [esp + 0x10], eax
0052359e lea eax, [ebx + 0x320]
005235a4 mov dword ptr [ebx + 0x38], ecx
005235a7 mov ecx, dword ptr [eax]
005235a9 test ecx, ecx
005235ab je 0x5235c7
005235ad mov dword ptr [esp + 0x3c], eax
005235b1 add ecx, 0x324
005235b7 lea eax, [esp + 0x3c]
005235bb push eax
005235bc call 0x4bc3c0
005235c1 lea eax, [ebx + 0x320]
005235c7 push eax
005235c8 mov ecx, edi
005235ca mov dword ptr [eax], edi
005235cc call 0x4bae70
005235d1 mov eax, dword ptr [edi + 0x294]
005235d7 mov ecx, ebx
005235d9 push dword ptr [esp + 0x40]
005235dd mov dword ptr [ebx + 0x294], eax
005235e3 mov eax, dword ptr [edi + 0x298]
005235e9 push dword ptr [esp + 0x24]
005235ed mov dword ptr [ebx + 0x298], eax
005235f3 movss xmm0, dword ptr [0xc02fec]
005235fb mov eax, dword ptr [ebx]
005235fd push esi
005235fe push dword ptr [esp + 0x50]
00523602 movss dword ptr [ebx + 0x2b8], xmm0
0052360a movss xmm0, dword ptr [0xc02ff0]
00523612 movss dword ptr [ebx + 0x2bc], xmm0
0052361a call dword ptr [eax + 4]
0052361d mov esi, dword ptr [esp + 0x28]
00523621 push ebx
00523622 mov edx, dword ptr [esi + 0x18190]
00523628 mov ecx, dword ptr [edx + 0x1214]
0052362e lea eax, [ecx + 1]
00523631 mov dword ptr [edx + 0x1214], eax
00523637 mov dword ptr [ebx + 0x20], ecx
0052363a lea ecx, [edx + 0x1218]
00523640 call 0x413280
00523645 push 1
00523647 mov ecx, edi
00523649 call 0x68cf40
0052364e test al, al
00523650 je 0x5238b5
00523656 mov eax, dword ptr [edi + 0x160]
0052365c and eax, 0x20000000
00523661 or eax, 0
00523664 je 0x52367c
00523666 push -1
00523668 lea ecx, [esp + 0xdc]
0052366f call 0x427290
00523674 push eax
00523675 mov ecx, ebx
00523677 call 0x685510
0052367c mov eax, dword ptr [edi + 0x28]
0052367f xor ecx, ecx
00523681 sub eax, 0xa
00523684 cmp eax, 0x3dd
00523689 mov eax, dword ptr [ebx + 0x28]
0052368c cmovbe ecx, edi
0052368f sub eax, 0xa
00523692 xor esi, esi
00523694 mov dword ptr [esp + 0x20], ecx
00523698 cmp eax, 0x3dd
0052369d cmovbe esi, ebx
005236a0 test ecx, ecx
005236a2 je 0x5238b1
005236a8 test esi, esi
005236aa je 0x5238b1
005236b0 push 0
005236b2 push 1
005236b4 mov ecx, esi
005236b6 call 0x4122f0
005236bb test al, al
005236bd jne 0x5237b9
005236c3 push 0x1000000
005236c8 push 0
005236ca mov ecx, edi
005236cc call 0x4122f0
005236d1 test al, al
005236d3 je 0x52373e
005236d5 movss xmm1, dword ptr [0xc02fec]
005236dd lea eax, [esp + 0x54]
005236e1 movss xmm0, dword ptr [0xc02ff0]
005236e9 mov ecx, esi
005236eb push 0x5a
005236ed push eax
005236ee mov dword ptr [esp + 0x5c], 0
005236f6 mov dword ptr [esp + 0x60], 0
005236fe mov dword ptr [esp + 0x64], 0
00523706 mov dword ptr [esp + 0x68], 0
0052370e movss dword ptr [esp + 0x6c], xmm1
00523714 movss dword ptr [esp + 0x70], xmm0
0052371a movss dword ptr [esp + 0x74], xmm1
00523720 movss dword ptr [esp + 0x78], xmm0
00523726 mov dword ptr [esp + 0x7c], 0
0052372e mov dword ptr [esp + 0x80], 0
00523739 call 0x68ecd0
0052373e push 0
00523740 push 0x1000000
00523745 mov ecx, edi
00523747 call 0x4122f0
0052374c test al, al
0052374e je 0x5237b9
00523750 movss xmm1, dword ptr [0xc02fec]
00523758 lea eax, [esp + 0x54]
0052375c movss xmm0, dword ptr [0xc02ff0]
00523764 mov ecx, esi
00523766 push 0x5a
00523768 push eax
00523769 mov dword ptr [esp + 0x5c], 0
00523771 mov dword ptr [esp + 0x60], 0
00523779 mov dword ptr [esp + 0x64], 0
00523781 mov dword ptr [esp + 0x68], 0
00523789 movss dword ptr [esp + 0x6c], xmm1
0052378f movss dword ptr [esp + 0x70], xmm0
00523795 movss dword ptr [esp + 0x74], xmm1
0052379b movss dword ptr [esp + 0x78], xmm0
005237a1 mov dword ptr [esp + 0x7c], 0
005237a9 mov dword ptr [esp + 0x80], 0
005237b4 call 0x68cfb0
005237b9 mov eax, dword ptr [esp + 0x20]
005237bd mov ecx, esi
005237bf movss xmm1, dword ptr [esi + 0xb88]
005237c7 mulss xmm1, dword ptr [eax + 0xe98]
005237cf movss dword ptr [esi + 0xb88], xmm1
005237d7 mulss xmm1, dword ptr [esi + 0x30c]
005237df movaps xmm0, xmm1
005237e2 mulss xmm1, dword ptr [0xbc7a2c]
005237ea mulss xmm0, dword ptr [0xbc7a28]
005237f2 movss dword ptr [esi + 0xdc], xmm1
005237fa movss dword ptr [esi + 0xd8], xmm0
00523802 movss xmm0, dword ptr [eax + 0xe98]
0052380a mulss xmm0, dword ptr [esi + 0xe98]
00523812 movss dword ptr [esi + 0xe98], xmm0
0052381a movss xmm0, dword ptr [esi + 0xe94]
00523822 mulss xmm0, dword ptr [eax + 0xe94]
0052382a movss dword ptr [esi + 0xe94], xmm0
00523832 movss xmm0, dword ptr [esi + 0x2dc]
0052383a mulss xmm0, dword ptr [eax + 0xe94]
00523842 movss dword ptr [esi + 0x2dc], xmm0
0052384a movss xmm0, dword ptr [esi + 0x2d8]
00523852 mulss xmm0, dword ptr [eax + 0xe94]
0052385a mov eax, dword ptr [esi]
0052385c movss dword ptr [esi + 0x2d8], xmm0
00523864 mov eax, dword ptr [eax + 0x48]
00523867 call eax
00523869 test al, al
0052386b je 0x5238b1
0052386d mov ecx, dword ptr [esp + 0x20]
00523871 add esi, 0xea4
00523877 mov eax, dword ptr [ecx + 0xea4]
0052387d mov ecx, dword ptr [esi]
0052387f mov dword ptr [esp + 0x20], eax
00523883 cmp ecx, eax
00523885 je 0x5238b1
00523887 test ecx, ecx
00523889 je 0x5238a3
0052388b lea eax, [esp + 0x44]
0052388f mov dword ptr [esp + 0x44], esi
00523893 push eax
00523894 add ecx, 0x324
0052389a call 0x4bc3c0
0052389f mov eax, dword ptr [esp + 0x20]
005238a3 mov dword ptr [esi], eax
005238a5 test eax, eax
005238a7 je 0x5238b1
005238a9 push esi
005238aa mov ecx, eax
005238ac call 0x4bae70
005238b1 mov esi, dword ptr [esp + 0x28]
005238b5 push ebx
005238b6 call 0x6d94d0
005238bb test al, al
005238bd je 0x5238c6
005238bf push ecx
005238c0 push ebx
005238c1 call 0x6d9590
005238c6 cmp byte ptr [ebx + 0x16a], 0
005238cd je 0x5239ec
005238d3 mov eax, dword ptr [esi + 0x283c20]
005238d9 cmp eax, dword ptr [esi + 0x283c24]
005238df je 0x5239ec
005238e5 mov eax, dword ptr [ebx + 0x28]
005238e8 lea ecx, [esi + 0x283c48]
005238ee mov dword ptr [esp + 0x20], eax
005238f2 mov eax, dword ptr [ebx + 0x2c]
005238f5 mov dword ptr [esp + 0x24], eax
005238f9 lea eax, [esp + 0x20]
005238fd push eax
005238fe lea eax, [esp + 0x48]
00523902 push eax
00523903 call 0x937c80
00523908 mov eax, dword ptr [esi + 0x283c48]
0052390e cmp dword ptr [esp + 0x44], eax
00523912 jne 0x523946
00523914 mov eax, dword ptr [ebx + 0x28]
00523917 lea ecx, [esi + 0x283c48]
0052391d mov dword ptr [esp + 0x44], eax
00523921 lea eax, [esp + 0x44]
00523925 push eax
00523926 lea eax, [esp + 0x30]
0052392a mov dword ptr [esp + 0x4c], 0xffffffff
00523932 push eax
00523933 call 0x937c80
00523938 mov ecx, dword ptr [esi + 0x283c48]
0052393e cmp dword ptr [eax], ecx
00523940 je 0x5239ec
00523946 mov esi, dword ptr [0xbfd65c]
0052394c xor edx, edx
0052394e mov dword ptr [esp + 0x1c], edx
00523952 mov eax, dword ptr [esi + 0x1ba54]
00523958 sub eax, dword ptr [esi + 0x1ba50]
0052395e sar eax, 2
00523961 test eax, eax
00523963 je 0x5239ec
00523969 mov edi, dword ptr [esp + 0x4c]
0052396d nop dword ptr [eax]
00523970 mov ecx, dword ptr [esi + 0x1ba54]
00523976 mov eax, ecx
00523978 sub eax, dword ptr [esi + 0x1ba50]
0052397e test eax, 0xfffffffc
00523983 jne 0x52399e
00523985 push 0xb3f4d0
0052398a push 3
0052398c call 0x95e330
00523991 mov ecx, dword ptr [esi + 0x1ba54]
00523997 add esp, 8
0052399a mov edx, dword ptr [esp + 0x1c]
0052399e mov eax, dword ptr [esi + 0x1ba50]
005239a4 sub ecx, eax
005239a6 sar ecx, 2
005239a9 cmp edx, ecx
005239ab jae 0x5239b0
005239ad lea eax, [eax + edx*4]
005239b0 mov ecx, dword ptr [eax]
005239b2 push 0xc02fec
005239b7 push edi
005239b8 push ebx
005239b9 push 6
005239bb add ecx, 0x1ec0
005239c1 call 0x935fd0
005239c6 mov esi, dword ptr [0xbfd65c]
005239cc mov edx, dword ptr [esp + 0x1c]
005239d0 inc edx
005239d1 mov dword ptr [esp + 0x1c], edx
005239d5 mov eax, dword ptr [esi + 0x1ba54]
005239db sub eax, dword ptr [esi + 0x1ba50]
005239e1 sar eax, 2
005239e4 cmp edx, eax
005239e6 jb 0x523970
005239e8 mov edi, dword ptr [esp + 0x7c]
005239ec call dword ptr [esp + 0x34]
005239f0 sub eax, dword ptr [esp + 0x10]
005239f4 add dword ptr [0xbffe0c], eax
005239fa push 0
005239fc push 0xbeaaec
00523a01 push 0xbeab18
00523a06 push 0
00523a08 push ebx
00523a09 call 0x9ec34c
00523a0e mov esi, eax
00523a10 add esp, 0x14
00523a13 mov ecx, dword ptr [esi + 0x314]
00523a19 lea ebx, [esi + 0x314]
00523a1f test ecx, ecx
00523a21 je 0x523a37
00523a23 lea eax, [esp + 0x10]
00523a27 mov dword ptr [esp + 0x10], ebx
00523a2b push eax
00523a2c add ecx, 0x324
00523a32 call 0x4bc3c0
00523a37 push ebx
00523a38 mov ecx, edi
00523a3a mov dword ptr [ebx], edi
00523a3c call 0x4bae70
00523a41 movss xmm0, dword ptr [0xbc7a28]
00523a49 mov ecx, esi
00523a4b movss xmm1, dword ptr [0xbc7a2c]
00523a53 mov eax, dword ptr [esi]
00523a55 movss dword ptr [esi + 0xd8], xmm0
00523a5d movss dword ptr [esi + 0xdc], xmm1
00523a65 mov dword ptr [esi + 0x3ac], 0x3c
00523a6f mov dword ptr [esi + 0x3b0], 0x3c
00523a79 call dword ptr [eax + 0xc]
00523a7c pop edi
00523a7d pop esi
00523a7e pop ebx
00523a7f mov esp, ebp
00523a81 pop ebp
00523a82 ret 
