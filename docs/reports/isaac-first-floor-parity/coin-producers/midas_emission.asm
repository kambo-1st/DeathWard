0069e86e mov edi, dword ptr [ebp - 0x27c]
0069e874 call 0x659200
0069e879 mulss xmm0, dword ptr [0xb6a864]
0069e881 movss dword ptr [ebp - 0x27c], xmm0
0069e889 call 0x6c3d90
0069e88e push eax
0069e88f push 1
0069e891 push 0
0069e893 lea eax, [ebp - 0x27c]
0069e899 push eax
0069e89a lea eax, [ebp - 0x40]
0069e89d push eax
0069e89e lea eax, [ebp - 0x2e4]
0069e8a4 push eax
0069e8a5 call 0x659290
0069e8aa add esp, 4
0069e8ad mov ecx, eax
0069e8af call 0x962b50
0069e8b4 mov ecx, dword ptr [0xbfd65c]
0069e8ba push eax
0069e8bb push edi
0069e8bc push 0x14
0069e8be push 5
0069e8c0 call 0x422e20
0069e8c5 sub esi, 1
0069e8c8 jne 0x69e874
0069e8ca mov edi, dword ptr [ebp - 0x2c0]
