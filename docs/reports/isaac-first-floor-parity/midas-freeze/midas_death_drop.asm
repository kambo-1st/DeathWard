0069e7f8 push 0
0069e7fa push 0x400
0069e7ff mov ecx, edi
0069e801 call 0x4122f0
0069e806 test al, al
0069e808 je 0x69e8d0
0069e80e push 0x400
0069e813 push 0
0069e815 mov ecx, edi
0069e817 call 0x4122f0
0069e81c test al, al
0069e81e jne 0x69e8d0
0069e824 mov ecx, dword ptr [0xbfd65c]
0069e82a lea eax, [edi + 0x294]
0069e830 push 1
0069e832 push 0
0069e834 push 1
0069e836 push eax
0069e837 mov dword ptr [ebp - 0x27c], eax
0069e83d call 0x6d5f90
0069e842 test eax, eax
0069e844 je 0x69e85d
0069e846 mov ecx, eax
0069e848 call 0x78cdc0
0069e84d cmp eax, 3
0069e850 jne 0x69e85d
0069e852 mov ecx, eax
0069e854 call 0x659230
0069e859 mov esi, eax
0069e85b jmp 0x69e86a
0069e85d mov ecx, 3
0069e862 call 0x659230
0069e867 lea esi, [eax + 1]
0069e86a test esi, esi
0069e86c jle 0x69e8d0
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
