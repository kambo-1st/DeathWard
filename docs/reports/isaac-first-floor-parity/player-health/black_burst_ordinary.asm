005a1841 mov eax, dword ptr [ebp - 0x588]
005a1847 cmp dword ptr [eax + 0x2c], 0
005a184b je 0x5a185a
005a184d cmp byte ptr [ebp - 0x590], 0
005a1854 je 0x5a1d01
005a185a push 0
005a185c push 0x106
005a1861 mov ecx, eax
005a1863 call 0x73b3b0
005a1868 mov ecx, dword ptr [ebp - 0x588]
005a186e mov esi, eax
005a1870 push 0x30
005a1872 call 0x78d4c0
005a1877 movss xmm2, dword ptr [0xb6a614]
005a187f add esi, eax
005a1881 push ecx
005a1882 mov ecx, dword ptr [0xbfd680]
005a1888 mov dword ptr [esp], 0x3f800000
005a188f movd xmm1, esi
005a1893 cvtdq2ps xmm1, xmm1
005a1896 push 0
005a1898 push 2
005a189a push 0x21
005a189c mulss xmm1, dword ptr [0xb6aa3c]
005a18a4 addss xmm1, dword ptr [0xb6aa3c]
005a18ac movss dword ptr [ebp - 0x59c], xmm1
005a18b4 call 0x8b1480
005a18b9 mov ecx, dword ptr [0xbfd65c]
005a18bf push 0xf
005a18c1 call 0x6d5ad0
005a18c6 movss xmm1, dword ptr [0xb6a350]
005a18ce lea ecx, [ebp - 0x4a4]
005a18d4 sub esp, 0x20
005a18d7 movaps xmm3, xmm1
005a18da movaps xmm2, xmm1
005a18dd mov dword ptr [esp + 0x1c], 0
005a18e5 mov dword ptr [esp + 0x18], 0
005a18ed mov dword ptr [esp + 0x14], 0
005a18f5 mov dword ptr [esp + 0x10], 0x3f800000
005a18fd mov dword ptr [esp + 0xc], 0x3f800000
005a1905 mov dword ptr [esp + 8], 0x3f800000
005a190d mov dword ptr [esp + 4], 0x3f800000
005a1915 mov dword ptr [esp], 0x3f19999a
005a191c call 0x427150
005a1921 movss xmm1, dword ptr [0xb6a614]
005a1929 mov ecx, dword ptr [ebp - 0x588]
005a192f push eax
005a1930 call 0x68d980
005a1935 mov ecx, dword ptr [0xbfd65c]
005a193b call 0x4023f0
005a1940 mov ecx, eax
005a1942 call 0x427740
005a1947 xor edi, edi
005a1949 mov dword ptr [ebp - 0x5a4], eax
005a194f mov ecx, eax
005a1951 mov dword ptr [ebp - 0x5a0], edi
005a1957 call 0x4083d0
005a195c test eax, eax
005a195e je 0x5a1cf5
005a1964 mov ecx, dword ptr [ebp - 0x5a4]
005a196a push edi
005a196b call 0x4124b0
005a1970 mov edi, dword ptr [eax]
005a1972 mov ecx, edi
005a1974 call 0x684620
005a1979 test al, al
005a197b je 0x5a1cd5
005a1981 push 0
005a1983 push 0x10
005a1985 mov ecx, edi
005a1987 call 0x4122f0
005a198c test al, al
005a198e jne 0x5a1cd5
005a1994 mov ecx, edi
005a1996 call 0x59fd50
005a199b test al, al
005a199d jne 0x5a1cd5
005a19a3 push 0
005a19a5 push 0x20000000
005a19aa mov ecx, edi
005a19ac call 0x4122f0
005a19b1 test al, al
005a19b3 jne 0x5a1cd5
005a19b9 push dword ptr [ebp - 0x588]
005a19bf lea ecx, [ebp - 0x1380]
005a19c5 call 0x4229a0
005a19ca mov eax, dword ptr [edi]
005a19cc lea ecx, [ebp - 0x1380]
005a19d2 movss xmm0, dword ptr [ebp - 0x59c]
005a19da push 0x1e
005a19dc push ecx
005a19dd mov eax, dword ptr [eax + 0x20]
005a19e0 push 0
005a19e2 push 0x40000000
005a19e7 push ecx
005a19e8 mov ecx, edi
005a19ea movss dword ptr [esp], xmm0
005a19ef call eax
