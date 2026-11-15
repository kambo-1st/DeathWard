006b1b40 mov edx, ecx
006b1b42 call 0x78cdc0
006b1b47 cmp eax, 1
006b1b4a je 0x6b1b6a
006b1b4c cmp eax, 2
006b1b4f je 0x6b1b6a
006b1b51 mov ecx, dword ptr [edx + 0x1ca8]
006b1b57 mov eax, dword ptr [edx + 0x1290]
006b1b5d lea eax, [eax + ecx*2]
006b1b60 cmp dword ptr [edx + 0x1294], eax
006b1b66 setge al
006b1b69 ret
006b1b6a mov eax, dword ptr [edx + 0x1290]
006b1b70 cmp dword ptr [edx + 0x1294], eax
006b1b76 setge al
006b1b79 ret
