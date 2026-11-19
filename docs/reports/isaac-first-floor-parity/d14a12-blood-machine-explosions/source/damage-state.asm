0064087e mov eax, dword ptr [ebx + 0x360]
00640884 cmp eax, 3
00640887 je 0x6400b8
0064088d cmp ecx, 9
00640890 jne 0x6408ea
00640892 and edx, 0x1000000
00640898 or edx, 0
0064089b jne 0x6408ea
0064089d cmp eax, 1
006408a0 jne 0x6400b8
006408a6 mov eax, dword ptr [ebp + 0x14]
006408a9 cmp dword ptr [eax + 8], 6
006408ad je 0x6400b8
006408b3 push 1
006408b5 push 0xb42f20
006408ba lea ecx, [ebx + 0x3c]
006408bd call 0x405740
006408c2 test al, al
006408c4 je 0x6408d5
006408c6 lea ecx, [ebx + 0x6c]
006408c9 call 0x405330
006408ce mov byte ptr [ebx + 0x80], 1
006408d5 mov dword ptr [ebx + 0x360], 5
006408df xor al, al
006408e1 pop edi
006408e2 pop esi
006408e3 pop ebx
006408e4 mov esp, ebp
006408e6 pop ebp
006408e7 ret 0x14
006408ea mov dword ptr [ebx + 0x360], 3
006408f4 cmp ecx, 1
006408f7 jne 0x64090d
006408f9 push ecx
006408fa mov ecx, dword ptr [0xbfd680]
00640900 push 0x12
00640902 lea ecx, [ecx + 0x14]
00640905 call 0x884e40
0064090a mov ecx, dword ptr [ebx + 0x2c]
0064090d cmp ecx, 2
00640910 jne 0x640df4
