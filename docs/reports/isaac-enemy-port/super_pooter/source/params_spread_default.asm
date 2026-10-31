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
