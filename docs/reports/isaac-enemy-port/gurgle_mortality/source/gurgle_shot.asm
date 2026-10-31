005096c5 lea ecx, [ebp - 0x118]
005096cb call 0x430d70
005096d0 push eax
005096d1 push ecx
005096d2 mov dword ptr [esp], 0x41200000
005096d9 lea eax, [ebp - 0x128]
005096df push eax
005096e0 push 1
005096e2 mov ecx, edi
005096e4 call 0x6a3420
005096e9 mov ecx, dword ptr [edi + 0x2c]
005096ec mov esi, eax
005096ee mov edx, dword ptr [esi + 0x388]
005096f4 mov eax, dword ptr [esi + 0x38c]
005096fa mov dword ptr [esi + 0x370], 0x3fcccccd
00509704 cmp ecx, 1
00509707 jne 0x5097bc
0050970d movaps xmm0, xmmword ptr [0xb6c610]
00509714 or eax, 8
00509717 push ecx
00509718 push 0
0050971a push 0xff
0050971f mov dword ptr [esi + 0x38c], eax
