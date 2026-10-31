; Repentance1.7.9b bounded native evidence; names are interpretive.
0068ff80 push esi
0068ff81 mov esi, ecx
0068ff83 cmp dword ptr [esi + 0x28], 0x362
0068ff8a jne 0x68ffa1
0068ff8c cmp dword ptr [esi + 0x2c], 0
0068ff90 jne 0x68ffa1
0068ff92 mov ecx, dword ptr [esi + 0x318]
0068ff98 test ecx, ecx
0068ff9a je 0x68ffa1
0068ff9c mov eax, dword ptr [ecx]
0068ff9e call dword ptr [eax + 0x28]
0068ffa1 mov ecx, esi
0068ffa3 pop esi
0068ffa4 jmp 0x6848f0
0068ffa9 int3 
0068ffaa int3 
0068ffab int3 
0068ffac int3 
0068ffad int3 
0068ffae int3 
0068ffaf int3 
