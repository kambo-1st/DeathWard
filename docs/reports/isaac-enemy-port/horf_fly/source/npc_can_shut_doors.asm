0068f550 cmp byte ptr [ecx + 0xb8c], 0
0068f557 je 0x68f56c
0068f559 mov eax, dword ptr [ecx + 0x160]
0068f55f and eax, 0x20000000
0068f564 or eax, 0
0068f567 jne 0x68f56c
0068f569 mov al, 1
0068f56b ret 
0068f56c xor al, al
0068f56e ret 
