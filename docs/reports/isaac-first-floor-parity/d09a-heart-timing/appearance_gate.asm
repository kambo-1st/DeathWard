006bb8c5 cmp dword ptr [edi + 0x70], 0
006bb8c9 je 0x6bba3b
006bb8cf mov al, byte ptr [edi + 0x80]
006bb8d5 mov byte ptr [ebp - 0x8e], al
006bb8db test al, al
006bb8dd jne 0x6bb9cd
006bb8e3 lea ecx, [edi + 0x6c]
006bb8e6 mov edx, 0xb40360
006bb8eb call 0x402320
006bb8f0 mov cl, byte ptr [eax]
006bb8f2 cmp cl, byte ptr [edx]
006bb8f4 jne 0x6bb910
006bb8f6 test cl, cl
006bb8f8 je 0x6bb90c
006bb8fa mov cl, byte ptr [eax + 1]
006bb8fd cmp cl, byte ptr [edx + 1]
006bb900 jne 0x6bb910
006bb902 add eax, 2
006bb905 add edx, 2
006bb908 test cl, cl
006bb90a jne 0x6bb8f0
006bb90c xor eax, eax
006bb90e jmp 0x6bb915
006bb910 sbb eax, eax
006bb912 or eax, 1
006bb915 test eax, eax
006bb917 je 0x6bb999
006bb91d cmp byte ptr [ebp - 0x8e], 0
006bb924 jne 0x6bb9cd
006bb92a lea ecx, [edi + 0x6c]
006bb92d mov edx, 0xb4978c
006bb932 call 0x402320
006bb937 mov cl, byte ptr [eax]
006bb939 cmp cl, byte ptr [edx]
006bb93b jne 0x6bb957
006bb93d test cl, cl
006bb93f je 0x6bb953
006bb941 mov cl, byte ptr [eax + 1]
006bb944 cmp cl, byte ptr [edx + 1]
006bb947 jne 0x6bb957
006bb949 add eax, 2
006bb94c add edx, 2
006bb94f test cl, cl
006bb951 jne 0x6bb937
006bb953 xor eax, eax
006bb955 jmp 0x6bb95c
006bb957 sbb eax, eax
006bb959 or eax, 1
006bb95c test eax, eax
006bb95e je 0x6bb999
006bb960 lea ecx, [edi + 0x6c]
006bb963 mov edx, 0xb49744
006bb968 call 0x402320
006bb96d nop dword ptr [eax]
006bb970 mov cl, byte ptr [eax]
006bb972 cmp cl, byte ptr [edx]
006bb974 jne 0x6bb990
006bb976 test cl, cl
006bb978 je 0x6bb98c
006bb97a mov cl, byte ptr [eax + 1]
006bb97d cmp cl, byte ptr [edx + 1]
006bb980 jne 0x6bb990
006bb982 add eax, 2
006bb985 add edx, 2
006bb988 test cl, cl
006bb98a jne 0x6bb970
006bb98c xor eax, eax
006bb98e jmp 0x6bb995
006bb990 sbb eax, eax
006bb992 or eax, 1
006bb995 test eax, eax
006bb997 jne 0x6bb9cd
006bb999 cmp byte ptr [ebp - 0x8d], 0
006bb9a0 je 0x6bb9bc
006bb9a2 cmp dword ptr [edi + 0x30], 0
006bb9a6 jne 0x6bb9bc
006bb9a8 push 0
006bb9aa push 0xb41d88
006bb9af lea ecx, [edi + 0x3c]
006bb9b2 call 0x4054f0
006bb9b7 jmp 0x6bba3b
006bb9bc push 0
006bb9be push 0xb3fd8c
006bb9c3 lea ecx, [edi + 0x3c]
006bb9c6 call 0x4054f0
006bb9cb jmp 0x6bba21
006bb9cd push 0xb48ccc
006bb9d2 lea ecx, [edi + 0x6c]
006bb9d5 call 0x405e90
006bb9da test al, al
006bb9dc je 0x6bba3b
006bb9de mov ecx, edi
006bb9e0 call 0x6be0a0
006bb9e5 cmp byte ptr [ebp - 0x8d], 0
006bb9ec jne 0x6bba3b
006bb9ee push 0xb40360
006bb9f3 lea ecx, [edi + 0x3c]
006bb9f6 call 0x405640
006bb9fb test al, al
006bb9fd jne 0x6bba21
006bb9ff push 0xb4978c
006bba04 lea ecx, [edi + 0x3c]
006bba07 call 0x405640
006bba0c test al, al
006bba0e jne 0x6bba21
006bba10 push 0xb49744
006bba15 lea ecx, [edi + 0x3c]
006bba18 call 0x405640
006bba1d test al, al
006bba1f je 0x6bba3b
006bba21 cmp dword ptr [edi + 0x2c], 0x29
006bba25 mov dword ptr [edi + 0x180], 4
006bba2f jne 0x6bba3b
006bba31 mov dword ptr [edi + 0x17c], 5
