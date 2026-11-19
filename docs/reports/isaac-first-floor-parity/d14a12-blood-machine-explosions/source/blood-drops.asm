0063f841 cmp eax, 2
0063f844 jne 0x63f93e
0063f84a lea edi, [ebx + 0x334]
0063f850 push eax
0063f851 mov ecx, edi
0063f853 mov dword ptr [ebp - 0x34], edi
0063f856 call 0x7a7d50
0063f85b lea esi, [eax + 1]
0063f85e mov dword ptr [ebp - 0x44], esi
0063f861 test esi, esi
0063f863 jle 0x640053
0063f869 mov esi, dword ptr [ebp - 0x48]
0063f86c nop dword ptr [eax]
0063f870 push 2
0063f872 mov ecx, edi
0063f874 call 0x7a7d50
0063f879 test eax, eax
0063f87b je 0x63f8c9
0063f87d test esi, esi
0063f87f je 0x63f88e
0063f881 push 5
0063f883 mov ecx, esi
0063f885 call 0x7a7d50
0063f88a test eax, eax
0063f88c jne 0x63f8c9
0063f88e lea eax, [ebp - 0x68]
0063f891 push eax
0063f892 lea esi, [ebx + 0x294]
0063f898 push 1
0063f89a mov edx, esi
0063f89c lea ecx, [ebp - 0x3c]
0063f89f call 0x6c3450
0063f8a4 add esp, 8
0063f8a7 mov ecx, edi
0063f8a9 call 0x7a7e20
0063f8ae mov ecx, dword ptr [0xbfd65c]
0063f8b4 push eax
0063f8b5 push 0
0063f8b7 push 0
0063f8b9 lea eax, [ebp - 0x3c]
0063f8bc push eax
0063f8bd push esi
0063f8be push 0xa
0063f8c0 push 5
0063f8c2 call 0x422e20
0063f8c7 jmp 0x63f920
0063f8c9 push 4
0063f8cb mov ecx, edi
0063f8cd call 0x7a7d50
0063f8d2 lea esi, [eax + 1]
0063f8d5 test esi, esi
0063f8d7 jle 0x63f920
0063f8d9 lea edi, [ebx + 0x294]
0063f8df mov ebx, dword ptr [ebp - 0x34]
0063f8e2 lea eax, [ebp - 0x68]
0063f8e5 mov edx, edi
0063f8e7 push eax
0063f8e8 push 1
0063f8ea lea ecx, [ebp - 0x70]
0063f8ed call 0x6c3450
0063f8f2 add esp, 8
0063f8f5 mov ecx, ebx
0063f8f7 call 0x7a7e20
0063f8fc mov ecx, dword ptr [0xbfd65c]
0063f902 push eax
0063f903 push 0
0063f905 push 0
0063f907 lea eax, [ebp - 0x70]
0063f90a push eax
0063f90b push edi
0063f90c push 0x14
0063f90e push 5
0063f910 call 0x422e20
0063f915 sub esi, 1
0063f918 jne 0x63f8e2
0063f91a mov ebx, dword ptr [ebp - 0x4c]
0063f91d mov edi, dword ptr [ebp - 0x34]
0063f920 sub dword ptr [ebp - 0x44], 1
0063f924 mov esi, dword ptr [ebp - 0x48]
0063f927 jne 0x63f870
0063f92d pop edi
0063f92e pop esi
0063f92f pop ebx
0063f930 mov ecx, dword ptr [ebp - 4]
0063f933 xor ecx, ebp
0063f935 call 0x9eacd7
0063f93a mov esp, ebp
0063f93c pop ebp
0063f93d ret
