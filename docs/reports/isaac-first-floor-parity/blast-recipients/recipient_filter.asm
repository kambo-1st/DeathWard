006d1833 mov eax, dword ptr [ebp - 0x5c]
006d1836 mov edi, dword ptr [eax + edi*4]
006d1839 mov dword ptr [ebp - 0x28], edi
006d183c cmp edi, esi
006d183e jne 0x6d184a
006d1840 cmp byte ptr [ebx + 0x34], 0
006d1844 je 0x6d20c4
006d184a cmp byte ptr [edi + 0x16b], 0
006d1851 jne 0x6d20c4
006d1857 cmp dword ptr [edi + 0x180], 0
006d185e je 0x6d20c4
006d1864 cmp dword ptr [edi + 0x17c], 4
006d186b je 0x6d20c4
006d1871 movss xmm0, dword ptr [edi + 0x2d4]
006d1879 xorps xmm1, xmm1
006d187c ucomiss xmm0, xmm1
006d187f lahf 
006d1880 test ah, 0x44
006d1883 jnp 0x6d20c4
006d1889 mov eax, dword ptr [edi + 0x28]
006d188c cmp eax, 2
006d188f je 0x6d20c4
006d1895 cmp eax, 9
006d1898 je 0x6d20c4
006d189e test esi, esi
006d18a0 je 0x6d18c0
006d18a2 cmp eax, 0x112
006d18a7 jne 0x6d18c0
006d18a9 cmp dword ptr [esi + 0x28], eax
006d18ac jne 0x6d18c0
006d18ae mov eax, dword ptr [0xbfd65c]
006d18b3 cmp dword ptr [eax + 0x1c319c], 0x17
006d18ba jne 0x6d20c4
006d18c0 mov eax, dword ptr [ebx + 8]
006d18c3 movss xmm1, dword ptr [edi + 0x294]
006d18cb movss xmm0, dword ptr [ebx + 0x10]
006d18d0 addss xmm0, dword ptr [edi + 0x2c8]
006d18d8 subss xmm1, dword ptr [eax]
006d18dc movss xmm2, dword ptr [edi + 0x298]
006d18e4 subss xmm2, dword ptr [eax + 4]
006d18e9 movss dword ptr [ebp - 0x2c], xmm0
006d18ee movaps xmm0, xmm1
006d18f1 movss dword ptr [ebp - 0x20], xmm1
006d18f6 mulss xmm0, xmm1
006d18fa movaps xmm1, xmm2
006d18fd movss dword ptr [ebp - 0x18], xmm2
006d1902 mulss xmm1, xmm2
006d1906 addss xmm0, xmm1
006d190a call 0x4228c0
006d190f cmp byte ptr [ebx + 0x14], 0
006d1913 movss dword ptr [ebp - 0x1c], xmm0
006d1918 je 0x6d1956
006d191a mov eax, dword ptr [edi + 0x294]
006d1920 mov ecx, dword ptr [edi + 0x298]
006d1926 push 0
006d1928 push 0
006d192a push 1
006d192c push 0
006d192e mov dword ptr [ebp - 0x48], ecx
006d1931 mov ecx, dword ptr [0xbfd65c]
006d1937 mov dword ptr [ebp - 0x4c], eax
006d193a lea eax, [ebp - 0x4c]
006d193d push 2
006d193f push eax
006d1940 push dword ptr [ebx + 8]
006d1943 mov ecx, dword ptr [ecx + 0x18190]
006d1949 call 0x7af4b0
006d194e test al, al
006d1950 je 0x6d20c4
006d1956 test esi, esi
006d1958 je 0x6d19af
006d195a cmp dword ptr [esi + 0x28], 4
006d195e jne 0x6d19af
006d1960 push 0
006d1962 push 0xbeacac
006d1967 push 0xbeab18
006d196c push 0
006d196e push esi
006d196f call 0x9ec34c
006d1974 add esp, 0x14
006d1977 movups xmm1, xmmword ptr [eax + 0x388]
006d197e movd eax, xmm1
006d1982 movaps xmm0, xmm1
006d1985 psrldq xmm0, 4
006d198a or dword ptr [ebx + 0x1c], eax
006d198d movd eax, xmm0
006d1991 movaps xmm0, xmm1
006d1994 psrldq xmm0, 8
006d1999 psrldq xmm1, 0xc
006d199e or dword ptr [ebx + 0x20], eax
006d19a1 movd eax, xmm0
006d19a5 or dword ptr [ebx + 0x24], eax
006d19a8 movd eax, xmm1
006d19ac or dword ptr [ebx + 0x28], eax
