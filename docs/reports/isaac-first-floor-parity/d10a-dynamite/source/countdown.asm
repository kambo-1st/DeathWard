0067caf0 mov edx, dword ptr [edi + 0x360]
0067caf6 test edx, edx
0067caf8 jle 0x67cca9
0067cafe cmp dword ptr [edi + 0x34], 1
0067cb02 jne 0x67cb30
0067cb04 mov eax, dword ptr [ebp - 0xac]
0067cb0a test eax, eax
0067cb0c je 0x67cb30
0067cb0e add eax, 0x1450
0067cb13 push 0x89
0067cb18 mov ecx, eax
0067cb1a mov dword ptr [ebp - 0x6c], eax
0067cb1d call 0x88b570
0067cb22 test al, al
0067cb24 jne 0x67ccba
0067cb2a mov edx, dword ptr [edi + 0x360]
0067cb30 mov eax, dword ptr [edi + 0x2c]
0067cb33 cmp eax, 0x13
0067cb36 je 0x67cb3d
0067cb38 cmp eax, 0x14
0067cb3b jne 0x67cb4f
0067cb3d mov ecx, dword ptr [edi + 0x164]
0067cb43 xor eax, eax
0067cb45 and ecx, 0x2000000
0067cb4b or eax, ecx
0067cb4d jne 0x67cb58
0067cb4f lea eax, [edx - 1]
0067cb52 mov dword ptr [edi + 0x360], eax
