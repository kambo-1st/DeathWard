006d7180 push esi
006d7181 mov esi, ecx
006d7183 cmp byte ptr [esi + 0x1bb04], 0
006d718a lea ecx, [esi + 0x1bb04]
006d7190 jne 0x6d71c6
006d7192 call 0x93c4d0
006d7197 test al, al
006d7199 jne 0x6d71c6
006d719b push 0
006d719d call 0x8b3eb0
006d71a2 test al, al
006d71a4 jne 0x6d71c6
006d71a6 cmp byte ptr [esi + 0x1c31a0], al
006d71ac jne 0x6d71c6
006d71ae mov ecx, dword ptr [0xbfd680]
006d71b4 mov eax, dword ptr [ecx + 0x20a9ac]
006d71ba cmp eax, dword ptr [ecx + 0x20a9b0]
006d71c0 jne 0x6d71c6
006d71c2 xor al, al
006d71c4 pop esi
006d71c5 ret
006d71c6 mov al, 1
006d71c8 pop esi
006d71c9 ret
