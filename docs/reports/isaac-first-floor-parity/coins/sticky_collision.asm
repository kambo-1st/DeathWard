006bf087 mov edx, dword ptr [esi + 0x2c]
006bf08a cmp edx, 0x14
006bf08d jne 0x6bf0bd
006bf08f cmp dword ptr [esi + 0x30], 6
006bf093 jne 0x6bf0bd
006bf095 cmp dword ptr [edi + 0x28], 1
006bf099 jne 0x6c2825
006bf09f push 0
006bf0a1 push 0xb45798
006bf0a6 lea ecx, [esi + 0x3c]
006bf0a9 call 0x4054f0
006bf0ae mov dword ptr [esi + 0x498], 0xa
006bf0b8 jmp 0x6c2825
