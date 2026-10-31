0067b481 cmp dword ptr [edi + 0x360], 0
0067b488 lea eax, [edi + 0x360]
0067b48e lea edx, [ebp - 0x6c]
0067b491 mov dword ptr [ebp - 0x6c], 0
0067b498 lea ecx, [edi + 0x6c]
0067b49b cmovg edx, eax
0067b49e call 0x432ec0
0067b4a3 mov esi, eax
0067b4a5 sub esi, dword ptr [edx]
0067b4a7 sub esi, 1
0067b4aa jns 0x67b4cf
0067b4ac mov eax, 0x88888889
0067b4b1 imul esi
0067b4b3 add edx, esi
0067b4b5 sar edx, 3
0067b4b8 mov eax, edx
0067b4ba shr eax, 0x1f
0067b4bd add eax, edx
0067b4bf mov ecx, eax
0067b4c1 shl ecx, 4
0067b4c4 sub ecx, eax
0067b4c6 mov eax, 0xf
0067b4cb sub eax, ecx
0067b4cd add esi, eax
0067b4cf lea ecx, [edi + 0x3c]
0067b4d2 call 0x4058f0
0067b4d7 cmp esi, eax
0067b4d9 je 0x67b4e4
0067b4db push esi
0067b4dc lea ecx, [edi + 0x3c]
0067b4df call 0x405890
