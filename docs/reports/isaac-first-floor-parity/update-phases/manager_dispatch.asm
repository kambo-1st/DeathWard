008b0284 mov eax, dword ptr [edi + 8]
008b0287 dec eax
008b0288 cmp eax, 4
008b028b ja 0x8b049e
008b0291 jmp dword ptr [eax*4 + 0x8b05e8]
008b0298 call 0x6cda60
008b029d cmp byte ptr [edi + 0x1ea6c0], 0
008b02a4 jne 0x8b049e
008b02aa test byte ptr [edi + 0x4a264], 1
008b02b1 jne 0x8b0318
008b02b3 mov eax, dword ptr [0xbfd65c]
008b02b8 xor esi, esi
008b02ba mov ecx, dword ptr [eax + 0x18190]
008b02c0 cmp dword ptr [ecx + 0x1264], esi
008b02c6 jbe 0x8b030f
008b02c8 nop dword ptr [eax + eax]
008b02d0 mov eax, dword ptr [ecx + 0x125c]
008b02d6 mov edx, dword ptr [eax + esi*4]
008b02d9 cmp byte ptr [edx + 0x16d], 0
008b02e0 je 0x8b0301
008b02e2 mov eax, dword ptr [edx + 0x29c]
008b02e8 mov dword ptr [edx + 0x294], eax
008b02ee mov eax, dword ptr [edx + 0x2a0]
008b02f4 mov dword ptr [edx + 0x298], eax
008b02fa mov byte ptr [edx + 0x16d], 0
008b0301 inc esi
008b0302 cmp esi, dword ptr [ecx + 0x1264]
008b0308 jb 0x8b02d0
008b030a mov eax, dword ptr [0xbfd65c]
008b030f mov ecx, eax
008b0311 call 0x6cdcf0
008b0316 jmp 0x8b0326
008b0318 cmp byte ptr [edi + 0x29e73], 0
008b031f je 0x8b0326
008b0321 call 0x6d0400
