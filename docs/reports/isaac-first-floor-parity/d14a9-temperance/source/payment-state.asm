0063ee09 cmp eax, 2
0063ee0c jne 0x63eedc
0063ee12 mov ecx, dword ptr [0xbfd680]
0063ee18 push 1
0063ee1a push 0x11
0063ee1c lea ecx, [ecx + 0x14]
0063ee1f call 0x884e40
0063ee24 mov dword ptr [esp + 0x10], 0xae
0063ee2c mov esi, dword ptr [0xbfd680]
0063ee32 lea ecx, [esp + 0x10]
0063ee36 call 0x8b1340
0063ee3b sub esp, 8
0063ee3e mov dword ptr [esp + 4], 0
0063ee46 mov dword ptr [esp], 0x3f800000
0063ee4d push 0
0063ee4f push 2
0063ee51 push ecx
0063ee52 mov dword ptr [esp], 0x3f800000
0063ee59 lea ecx, [esi + 0x29de0]
0063ee5f push dword ptr [esp + 0x24]
0063ee63 call 0x888de0
0063ee68 mov eax, 0x1e
0063ee6d mov dword ptr [edi + 0x360], 2
0063ee77 push 0
0063ee79 mov word ptr [edi + 0x36a], ax
0063ee80 push 0xb4693c
0063ee85 lea ecx, [edi + 0x3c]
0063ee88 call 0x4054f0
