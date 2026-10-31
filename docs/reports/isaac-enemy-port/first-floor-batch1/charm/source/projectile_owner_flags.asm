006a179a mov eax, ecx
006a179c and eax, 0x100
006a17a1 or eax, 0
006a17a4 je 0x6a17bc
006a17a6 mov eax, dword ptr [esi + 0x38c]
006a17ac or dword ptr [esi + 0x388], 0x80
006a17b6 mov dword ptr [esi + 0x38c], eax
006a17bc and ecx, 0x20000000
006a17c2 or ecx, 0
006a17c5 je 0x6a17dd
006a17c7 mov eax, dword ptr [esi + 0x38c]
006a17cd or dword ptr [esi + 0x388], 0x80000000
006a17d7 mov dword ptr [esi + 0x38c], eax
