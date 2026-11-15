006bfa0c dec eax
006bfa0d mov dword ptr [ebp - 0xb8], 0
006bfa17 mov dword ptr [ebp - 0xd8], 0
006bfa21 cmp eax, 8
006bfa24 ja 0x6bfa74
006bfa26 movzx eax, byte ptr [eax + 0x6c2854]
006bfa2d jmp dword ptr [eax*4 + 0x6c2844]
006bfa34 mov dword ptr [ebp - 0xb8], 2
006bfa3e mov dword ptr [ebp - 0xd8], 3
006bfa48 jmp 0x6bfa74
006bfa4a mov dword ptr [ebp - 0xb8], 1
006bfa54 mov dword ptr [ebp - 0xd8], 1
006bfa5e jmp 0x6bfa74
006bfa60 mov dword ptr [ebp - 0xb8], 4
006bfa6a mov dword ptr [ebp - 0xd8], 6
