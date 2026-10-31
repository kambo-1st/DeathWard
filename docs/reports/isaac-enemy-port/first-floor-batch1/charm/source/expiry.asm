00686815 mov eax, dword ptr [edi + 0x21c]
0068681b test eax, eax
0068681d jle 0x68687e
0068681f mov esi, dword ptr [esp + 0x10]
00686823 dec eax
00686824 mov dword ptr [edi + 0x21c], eax
0068682a mov dword ptr [esp + 0x14], esi
0068682e test eax, eax
00686830 jg 0x68687e
00686832 mov eax, dword ptr [edi + 0x31c]
00686838 mov edx, esi
0068683a lea esi, [edi + 0x31c]
00686840 mov dword ptr [edi + 0x164], edx
00686846 and ecx, 0xfffffeff
0068684c mov dword ptr [edi + 0x160], ecx
00686852 test eax, eax
00686854 je 0x686882
00686856 lea ecx, [esp + 0x1c]
0068685a mov dword ptr [esp + 0x1c], esi
0068685e push ecx
0068685f lea ecx, [eax + 0x324]
00686865 call 0x4bc3c0
0068686a mov ecx, dword ptr [edi + 0x160]
00686870 mov edx, dword ptr [edi + 0x164]
00686876 mov dword ptr [esi], 0
0068687c jmp 0x686882
0068687e mov edx, dword ptr [esp + 0x14]
