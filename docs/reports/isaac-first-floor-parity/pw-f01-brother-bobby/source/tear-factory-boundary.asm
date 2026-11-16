00619a1e call 0x6c3d90
00619a23 mov ecx, dword ptr [0xbfd65c]
00619a29 push 0
00619a2b push eax
00619a2c push 0
00619a2e push edi
00619a2f lea eax, [esp + 0x60]
00619a33 push eax
00619a34 lea eax, [edi + 0x294]
00619a3a push eax
00619a3b push esi
00619a3c push 2
00619a3e call 0x6d0ca0
00619a43 mov esi, eax
00619a45 call 0x6c3d90
00619a4a push ecx
00619a4b mov ecx, esi
00619a4d movd xmm0, eax
00619a51 cvtdq2pd xmm0, xmm0
00619a55 shr eax, 0x1f
00619a58 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
00619a61 mov eax, dword ptr [esi]
00619a63 cvtpd2ps xmm0, xmm0
00619a67 mulss xmm0, dword ptr [0xb6a19c]
00619a6f mulss xmm0, dword ptr [0xb6a350]
00619a77 addss xmm0, dword ptr [esp + 0x40]
00619a7d movss dword ptr [esi + 0x364], xmm0
00619a85 movss xmm0, dword ptr [esp + 0x34]
00619a8b movss dword ptr [esi + 0x368], xmm0
00619a93 movss xmm0, dword ptr [esp + 0x28]
00619a99 movss dword ptr [esp], xmm0
00619a9e call dword ptr [eax + 0x3c]
00619aa1 movups xmm0, xmmword ptr [esp + 0x10]
00619aa6 sub esp, 0x10
00619aa9 mov ecx, esi
00619aab mov eax, esp
00619aad movups xmmword ptr [eax], xmm0
00619ab0 call 0x650280
00619ab5 movss xmm0, dword ptr [esp + 0x28]
00619abb mov ecx, esi
00619abd movss dword ptr [esi + 0x374], xmm0
00619ac5 movss dword ptr [esi + 0x370], xmm0
00619acd call 0x651770
00619ad2 mov ecx, dword ptr [esi + 0x314]
00619ad8 lea eax, [esi + 0x314]
00619ade test ecx, ecx
00619ae0 je 0x619afc
00619ae2 mov dword ptr [esp + 0x40], eax
00619ae6 add ecx, 0x324
00619aec lea eax, [esp + 0x40]
00619af0 push eax
00619af1 call 0x4bc3c0
00619af6 lea eax, [esi + 0x314]
00619afc push eax
00619afd mov ecx, edi
00619aff mov dword ptr [eax], edi
00619b01 call 0x4bae70
00619b06 mov eax, dword ptr [esi]
00619b08 lea ecx, [esp + 0xa4]
00619b0f push 1
00619b11 push 0
00619b13 push 0xff
00619b18 push -1
00619b1a push ecx
00619b1b mov ecx, esi
00619b1d call dword ptr [eax + 0x38]
00619b20 call 0x6c3d90
00619b25 and eax, 1
00619b28 mov ecx, edi
00619b2a push esi
00619b2b mov dword ptr [esi + 0x3a0], eax
00619b31 call 0x628a30
00619b36 mov eax, esi
00619b38 pop edi
00619b39 pop esi
00619b3a mov ecx, dword ptr [esp + 0x134]
00619b41 xor ecx, esp
00619b43 call 0x9eacd7
00619b48 mov esp, ebp
00619b4a pop ebp
