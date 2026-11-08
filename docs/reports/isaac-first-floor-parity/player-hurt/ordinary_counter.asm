00740cfe mov eax, dword ptr [ebp - 0x130]
00740d04 lea edx, [ebp - 0x130]
00740d0a lea ecx, [ebp - 0x2c]
00740d0d mov dword ptr [ebp - 0x130], eax
00740d13 mov dword ptr [ebp - 0x2c], 2
00740d1a call 0x417c60
00740d1f mov eax, dword ptr [eax]
00740d21 mov ecx, eax
00740d23 and dword ptr [edi + 0x164], 0xffffffef
00740d2a shl ecx, 4
00740d2d sub ecx, eax
00740d2f mov eax, dword ptr [edi + 0x160]
00740d35 shl ecx, 2
00740d38 cmp byte ptr [ebp - 0xfa], 0
00740d3f mov dword ptr [edi + 0x1308], ecx
00740d45 mov dword ptr [edi + 0x160], eax
