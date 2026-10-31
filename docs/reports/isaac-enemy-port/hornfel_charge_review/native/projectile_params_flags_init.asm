; Repentance 1.7.9b bounded evidence. Interpretive names are not exported symbols.
00430d70 push esi
00430d71 mov esi, ecx
00430d73 mov byte ptr [esi], 1
00430d76 mov dword ptr [esi + 4], 0
00430d7d mov dword ptr [esi + 8], 0
00430d84 mov dword ptr [esi + 0xc], 0
00430d8b mov dword ptr [esi + 0x10], 0x3f800000
00430d92 mov dword ptr [esi + 0x14], 0x3f800000
00430d99 call 0x6c3d90
00430d9e mov dword ptr [esi + 0x1c], 0x3f800000
00430da5 mov dword ptr [esi + 0x20], 0x3ba3d70a
00430dac mov dword ptr [esi + 0x24], 0x3f8147ae
00430db3 movd xmm0, eax
00430db7 cvtdq2pd xmm0, xmm0
00430dbb shr eax, 0x1f
00430dbe mov dword ptr [esi + 0x28], 0x3f800000
00430dc5 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
00430dce mov eax, esi
00430dd0 cvtpd2ps xmm0, xmm0
00430dd4 mulss xmm0, dword ptr [0xb6a19c] ; f32=2.32830644e-10
00430ddc mulss xmm0, dword ptr [0xb6a874] ; f32=3.14159274
00430de4 movss dword ptr [esi + 0x18], xmm0
00430de9 mov dword ptr [esi + 0x2c], 0x3f800000
00430df0 mov dword ptr [esi + 0x30], 0x3f800000
00430df7 mov dword ptr [esi + 0x34], 0x3f800000
00430dfe mov dword ptr [esi + 0x38], 0x3f800000
00430e05 mov dword ptr [esi + 0x3c], 0
00430e0c mov dword ptr [esi + 0x40], 0
00430e13 mov dword ptr [esi + 0x44], 0
00430e1a mov dword ptr [esi + 0x48], 0
00430e21 mov dword ptr [esi + 0x4c], 0
00430e28 mov dword ptr [esi + 0x50], 0
00430e2f mov dword ptr [esi + 0x54], 0
00430e36 mov dword ptr [esi + 0x58], 0
00430e3d mov dword ptr [esi + 0x5c], 0
