00403e30 push esi
00403e31 mov esi, ecx
00403e33 cmp byte ptr [esi + 0x109], 0
00403e3a je 0x403e4d
00403e3c lea ecx, [esi + 0x30]
00403e3f call 0x403d60
00403e44 lea ecx, [esi + 0x50]
00403e47 pop esi
00403e48 jmp 0x403d60
00403e4d pop esi
00403e4e ret
00403e4f int3
