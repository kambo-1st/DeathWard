0069b0e0 mov eax, dword ptr [ecx + 0x294]
0069b0e6 mov dword ptr [ecx + 0x2e4], eax
0069b0ec mov eax, dword ptr [ecx + 0x298]
0069b0f2 mov dword ptr [ecx + 0x2e8], eax
0069b0f8 mov eax, dword ptr [ecx + 0x2b8]
0069b0fe mov dword ptr [ecx + 0x2ec], eax
0069b104 mov eax, dword ptr [ecx + 0x2bc]
0069b10a mov dword ptr [ecx + 0x2f0], eax
0069b110 cmp dword ptr [ecx + 0x28], 0x340
0069b117 jne 0x69b13a
0069b119 cmp dword ptr [ecx + 0x2c], 0
0069b11d jne 0x69b13a
0069b11f cmp byte ptr [ecx + 0x16b], 0
0069b126 jne 0x69b13a
0069b128 mov eax, dword ptr [0xbfd65c]
0069b12d mov eax, dword ptr [eax + 0x18190]
0069b133 mov byte ptr [eax + 0x764c], 1
0069b13a ret 
0069b13b int3 
0069b13c int3 
0069b13d int3 
0069b13e int3 
0069b13f int3 
