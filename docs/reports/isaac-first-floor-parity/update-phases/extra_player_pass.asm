00413ce8 mov eax, dword ptr [0xbfd680]
00413ced cmp byte ptr [eax + 0x29e73], 0
00413cf4 jne 0x413e4a
00413cfa mov eax, dword ptr [0xbfd65c]
00413cff xor edx, edx
00413d01 mov dword ptr [ebp - 0x58], edx
00413d04 mov ecx, dword ptr [eax + 0x1ba54]
00413d0a sub ecx, dword ptr [eax + 0x1ba50]
00413d10 sar ecx, 2
00413d13 test ecx, ecx
00413d15 je 0x413ddc
00413d1b nop dword ptr [eax + eax]
00413d20 mov esi, dword ptr [0xbfd65c]
00413d26 mov ecx, dword ptr [esi + 0x1ba54]
00413d2c mov eax, ecx
00413d2e sub eax, dword ptr [esi + 0x1ba50]
00413d34 cmp eax, 4
00413d37 jae 0x413d51
00413d39 push 0xb3f4d0
00413d3e push 3
00413d40 call 0x95e330
00413d45 mov ecx, dword ptr [esi + 0x1ba54]
00413d4b add esp, 8
00413d4e mov edx, dword ptr [ebp - 0x58]
00413d51 mov esi, dword ptr [esi + 0x1ba50]
00413d57 sub ecx, esi
00413d59 sar ecx, 2
00413d5c cmp edx, ecx
00413d5e jae 0x413d63
00413d60 lea esi, [esi + edx*4]
00413d63 cmp byte ptr [ebx + 8], 0
00413d67 mov esi, dword ptr [esi]
00413d69 je 0x413d7d
00413d6b mov ecx, dword ptr [esi + 0x164]
00413d71 xor eax, eax
00413d73 and ecx, 0x1000
00413d79 or eax, ecx
00413d7b je 0x413dbc
00413d7d mov eax, dword ptr [esi + 0x164]
00413d83 mov ecx, esi
00413d85 or dword ptr [esi + 0x160], 0x4000
00413d8f mov dword ptr [esi + 0x164], eax
00413d95 mov eax, dword ptr [esi]
00413d97 call dword ptr [eax + 0xc]
00413d9a push 0
00413d9c mov ecx, esi
00413d9e call 0x683850
00413da3 mov eax, dword ptr [esi + 0x164]
00413da9 and dword ptr [esi + 0x160], 0xffffbfff
00413db3 mov edx, dword ptr [ebp - 0x58]
00413db6 mov dword ptr [esi + 0x164], eax
00413dbc mov eax, dword ptr [0xbfd65c]
00413dc1 inc edx
00413dc2 mov dword ptr [ebp - 0x58], edx
00413dc5 mov ecx, dword ptr [eax + 0x1ba54]
00413dcb sub ecx, dword ptr [eax + 0x1ba50]
00413dd1 sar ecx, 2
00413dd4 cmp edx, ecx
00413dd6 jb 0x413d20
00413ddc mov ecx, dword ptr [0xbfd65c]
00413de2 add ecx, 0x1ba5c
00413de8 mov eax, dword ptr [ecx + 4]
00413deb sub eax, dword ptr [ecx]
00413ded sar eax, 2
00413df0 test eax, eax
00413df2 je 0x413e4a
00413df4 xor edi, edi
00413df6 mov eax, dword ptr [ecx]
00413df8 mov esi, dword ptr [eax + edi*4]
00413dfb mov ecx, esi
00413dfd mov eax, dword ptr [esi + 0x164]
00413e03 or dword ptr [esi + 0x160], 0x4000
00413e0d mov dword ptr [esi + 0x164], eax
00413e13 mov eax, dword ptr [esi]
00413e15 call dword ptr [eax + 0xc]
00413e18 mov ecx, dword ptr [0xbfd65c]
00413e1e inc edi
00413e1f and dword ptr [esi + 0x160], 0xffffbfff
00413e29 add ecx, 0x1ba5c
00413e2f mov eax, dword ptr [esi + 0x164]
00413e35 mov dword ptr [esi + 0x164], eax
00413e3b mov eax, dword ptr [ecx + 4]
00413e3e sub eax, dword ptr [ecx]
00413e40 sar eax, 2
00413e43 cmp edi, eax
00413e45 jb 0x413df6
00413e47 mov edi, dword ptr [ebp - 0x70]
