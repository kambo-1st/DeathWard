006b57da mov esi, dword ptr [ebp - 0x48]
006b57dd mov ecx, dword ptr [0xbfd65c]
006b57e3 push 1
006b57e5 add ecx, 0x1ba40
006b57eb push ecx
006b57ec push 0xcb
006b57f1 call 0x91d340
006b57f6 test eax, eax
006b57f8 je 0x6b5806
006b57fa test dword ptr [ebp - 0xa4], 0x8000
006b5804 je 0x6b5830
006b5806 cmp dword ptr [esi], 0x28
006b5809 jne 0x6b6361
006b580f mov ecx, dword ptr [0xbfd65c]
006b5815 push 1
006b5817 add ecx, 0x1ba40
006b581d push ecx
006b581e push 0xfa
006b5823 call 0x91d340
006b5828 test eax, eax
006b582a je 0x6b6361
006b5830 mov edx, dword ptr [0xbfd658]
006b5836 mov ecx, dword ptr [ebp - 0x48]
006b5839 test edx, edx
006b583b jne 0x6b636a
006b5841 mov eax, dword ptr [ecx]
006b5843 cmp eax, 0xa
006b5846 jne 0x6b585c
006b5848 mov esi, dword ptr [edi]
006b584a cmp esi, 1
006b584d je 0x6b5854
006b584f cmp esi, 9
006b5852 jne 0x6b585c
006b5854 mov dword ptr [edi], 5
006b585a mov eax, dword ptr [ecx]
006b585c cmp eax, 0x14
006b585f jne 0x6b586e
006b5861 cmp dword ptr [edi], 1
006b5864 jne 0x6b586e
006b5866 mov dword ptr [edi], 4
006b586c mov eax, dword ptr [ecx]
006b586e cmp eax, 0x1e
006b5871 jne 0x6b5884
006b5873 cmp dword ptr [edi], 1
006b5876 jne 0x6b636a
006b587c mov dword ptr [edi], 3
006b5882 mov eax, dword ptr [ecx]
006b5884 cmp eax, 0x28
006b5887 jne 0x6b636a
006b588d cmp dword ptr [edi], 1
006b5890 jne 0x6b636a
006b5896 mov dword ptr [edi], 2
006b589c jmp 0x6b636a
