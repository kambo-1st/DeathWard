00786d30 mov eax, dword ptr [ecx + 0x130c]
00786d36 cmp eax, 0x24
00786d39 je 0x786d67
00786d3b cmp eax, 0x28
00786d3e jne 0x786d4e
00786d40 mov eax, dword ptr [ecx + 0x1d80]
00786d46 test eax, eax
00786d48 je 0x786d73
00786d4a mov ecx, eax
00786d4c jmp 0x786d30
00786d4e cmp eax, 0x11
00786d51 jne 0x786d73
00786d53 mov eax, dword ptr [ecx + 0x1cb8]
00786d59 test eax, eax
00786d5b je 0x786d73
00786d5d mov ecx, eax
00786d5f call 0x6b1b40
00786d64 xor al, 1
00786d66 ret 
00786d67 cmp dword ptr [ecx + 0x1ccc], 0x63
00786d6e jge 0x786d73
00786d70 mov al, 1
00786d72 ret 
00786d73 call 0x78cdc0
00786d78 cmp eax, 3
00786d7b jne 0x786d5f
00786d7d xor al, al
00786d7f ret 
