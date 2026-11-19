00640070 push ebp
00640071 mov ebp, esp
00640073 and esp, 0xfffffff8
00640076 sub esp, 0x74
00640079 push ebx
0064007a mov ebx, ecx
0064007c push esi
0064007d push edi
0064007e mov dword ptr [esp + 0x1c], ebx
00640082 mov ecx, dword ptr [ebx + 0x2c]
00640085 cmp ecx, 0xe
00640088 jne 0x6400c3
0064008a cmp dword ptr [ebx + 0x360], 1
00640091 jne 0x6400b8
00640093 push 0
00640095 mov eax, 0x1e
0064009a mov dword ptr [ebx + 0x360], 2
006400a4 push 0xb4688c
006400a9 lea ecx, [ebx + 0x3c]
006400ac mov word ptr [ebx + 0x36a], ax
006400b3 call 0x4054f0
006400b8 xor al, al
006400ba pop edi
006400bb pop esi
006400bc pop ebx
006400bd mov esp, ebp
006400bf pop ebp
006400c0 ret 0x14
006400c3 mov edx, dword ptr [ebp + 0xc]
006400c6 mov eax, edx
006400c8 and eax, 4
006400cb or eax, 0
006400ce je 0x6400b8
006400d0 cmp ecx, 8
006400d3 jne 0x640586
