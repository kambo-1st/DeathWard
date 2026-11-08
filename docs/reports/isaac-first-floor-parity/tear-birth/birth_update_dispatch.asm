00757b10 movss xmm0, dword ptr [esp + 0x7c]
00757b16 mulss xmm0, dword ptr [esi + 0x2d4]
00757b1e movss dword ptr [esi + 0x2d4], xmm0
00757b26 movss xmm0, dword ptr [esp + 0x80]
00757b2f movss dword ptr [esi + 0x3b0], xmm0
00757b37 mov ecx, dword ptr [edi + 0x13b4]
00757b3d lea eax, [ecx + 1]
00757b40 mov dword ptr [edi + 0x13b4], eax
00757b46 mov eax, dword ptr [esi]
00757b48 mov dword ptr [esi + 0x3a0], ecx
00757b4e mov ecx, esi
00757b50 call dword ptr [eax + 0xc]
