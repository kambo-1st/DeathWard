006098ca cmp dword ptr [esi + 0x28], 9
006098ce jne 0x609cf4
006098d4 mov eax, dword ptr [esi + 0x388]
006098da and eax, 0x80000000
006098df or eax, 0
006098e2 je 0x6098eb
006098e4 mov dl, 1
006098e6 jmp 0x609cf8
006098eb mov ecx, edi
006098ed call 0x5efae0
006098f2 test al, al
006098f4 je 0x609b22
006098fa cmp dword ptr [edi + 0x2c], 0x33
006098fe jne 0x60992d
