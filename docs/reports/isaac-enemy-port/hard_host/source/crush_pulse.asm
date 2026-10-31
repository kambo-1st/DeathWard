006d1750 push ebx
006d1751 mov ebx, esp
006d1753 sub esp, 8
006d1756 and esp, 0xfffffff8
006d1759 add esp, 4
006d175c push ebp
006d175d mov ebp, dword ptr [ebx + 4]
006d1760 mov dword ptr [esp + 4], ebp
006d1764 mov ebp, esp
006d1766 push -1
006d1768 push 0x9f5c77
006d176d mov eax, dword ptr fs:[0]
006d1773 push eax
006d1774 push ebx
006d1775 sub esp, 0x110
006d177b push esi
006d177c push edi
006d177d mov eax, dword ptr [0xbaa3b4]
006d1782 xor eax, ebp
006d1784 push eax
006d1785 lea eax, [ebp - 0xc]
006d1788 mov dword ptr fs:[0], eax
006d178e mov edi, ecx
006d1790 mov dword ptr [ebp - 0x34], edi
006d1793 movss xmm0, dword ptr [ebx + 0xc]
006d1798 comiss xmm0, dword ptr [0xb6ab78]
006d179f jae 0x6d17cc
006d17a1 push 0xbc48c0
006d17a6 lea edx, [ebx + 0x1c]
006d17a9 lea ecx, [ebp - 0x60]
006d17ac call 0x412050
006d17b1 add esp, 4
006d17b4 mov ecx, dword ptr [eax]
006d17b6 or ecx, dword ptr [eax + 4]
006d17b9 jne 0x6d17c3
006d17bb mov ecx, dword ptr [eax + 8]
006d17be or ecx, dword ptr [eax + 0xc]
006d17c1 je 0x6d17e4
006d17c3 comiss xmm0, dword ptr [0xb6ab28]
006d17ca jb 0x6d17e4
006d17cc call 0x6c3d90
006d17d1 xor edx, edx
006d17d3 mov ecx, 7
006d17d8 div ecx
006d17da add edx, ecx
006d17dc mov ecx, edi
006d17de push edx
006d17df call 0x6d5ad0
006d17e4 mov esi, dword ptr [ebx + 0x18]
006d17e7 test esi, esi
006d17e9 je 0x6d17fb
006d17eb cmp dword ptr [esi + 0x28], 1
006d17ef jne 0x6d17fb
006d17f1 cmp byte ptr [ebx + 0x34], 0
006d17f5 mov byte ptr [ebp - 0x11], 1
006d17f9 je 0x6d17ff
006d17fb mov byte ptr [ebp - 0x11], 0
006d17ff mov ecx, dword ptr [edi + 0x18190]
006d1805 lea eax, [ebp - 0x60]
006d1808 movss xmm3, dword ptr [ebx + 0x10]
006d180d add ecx, 0x1218
006d1813 push -1
006d1815 push dword ptr [ebx + 8]
006d1818 push eax
006d1819 call 0x4157f0
006d181e xor edi, edi
006d1820 mov dword ptr [ebp - 4], 0
006d1827 mov dword ptr [ebp - 0x30], edi
006d182a cmp dword ptr [ebp - 0x54], edi
006d182d jbe 0x6d20d4
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
006d19af movss xmm0, dword ptr [ebp - 0x1c]
006d19b4 xorps xmm1, xmm1
006d19b7 comiss xmm0, xmm1
006d19ba jbe 0x6d1b50
006d19c0 cmp dword ptr [edi + 0x28], 0x3e8
006d19c7 je 0x6d1b50
006d19cd push 0
006d19cf push 0xbeab9c
006d19d4 push 0xbeab18
006d19d9 push 0
006d19db push edi
006d19dc call 0x9ec34c
006d19e1 mov ecx, dword ptr [edi + 0x160]
006d19e7 add esp, 0x14
006d19ea and ecx, 0x4000000
006d19f0 or ecx, 0
006d19f3 jne 0x6d1b4d
006d19f9 cmp dword ptr [edi + 0x28], 1
006d19fd jne 0x6d1a3e
006d19ff test eax, eax
006d1a01 je 0x6d1a1c
006d1a03 movss xmm0, dword ptr [eax + 0x2d4]
006d1a0b ucomiss xmm0, dword ptr [0xb6accc]
006d1a12 lahf 
006d1a13 test ah, 0x44
006d1a16 jnp 0x6d1b4d
006d1a1c test esi, esi
006d1a1e je 0x6d1a34
006d1a20 mov eax, dword ptr [esi + 0x160]
006d1a26 and eax, 0x20000000
006d1a2b or eax, 0
006d1a2e jne 0x6d1b4d
006d1a34 cmp byte ptr [ebp - 0x11], 0
006d1a38 jne 0x6d1b4d
006d1a3e movss xmm0, dword ptr [ebp - 0x2c]
006d1a43 lea eax, [ebp - 0x24]
006d1a46 movss xmm2, dword ptr [ebp - 0x1c]
006d1a4b lea ecx, [ebp - 0x2c]
006d1a4e movss xmm1, dword ptr [edi + 0x2d4]
006d1a56 subss xmm0, xmm2
006d1a5a mov dword ptr [ebp - 0x24], 0x41700000
006d1a61 comiss xmm0, dword ptr [0xb6a9ac]
006d1a68 movss dword ptr [ebp - 0x2c], xmm0
006d1a6d cmovbe eax, ecx
006d1a70 comiss xmm1, dword ptr [0xb6a9c8]
006d1a77 movss xmm0, dword ptr [eax]
006d1a7b jbe 0x6d1a8b
006d1a7d movss xmm5, dword ptr [0xb6a480]
006d1a85 mulss xmm0, xmm5
006d1a89 jmp 0x6d1aca
006d1a8b comiss xmm1, dword ptr [0xb6aa0c]
006d1a92 jbe 0x6d1a9e
006d1a94 mulss xmm0, dword ptr [0xb6a350]
006d1a9c jmp 0x6d1ac2
006d1a9e comiss xmm1, dword ptr [0xb6aa60]
006d1aa5 jbe 0x6d1ab1
006d1aa7 mulss xmm0, dword ptr [0xb6a220]
006d1aaf jmp 0x6d1ac2
006d1ab1 comiss xmm1, dword ptr [0xb6ab58]
006d1ab8 jbe 0x6d1ac2
006d1aba mulss xmm0, dword ptr [0xb6a1fc]
006d1ac2 movss xmm5, dword ptr [0xb6a480]
006d1aca push 0xbc4ae0
006d1acf lea edx, [ebx + 0x1c]
006d1ad2 lea ecx, [ebp - 0xa8]
006d1ad8 call 0x412050
006d1add add esp, 4
006d1ae0 mov ecx, dword ptr [eax]
006d1ae2 or ecx, dword ptr [eax + 4]
006d1ae5 jne 0x6d1af3
006d1ae7 mov ecx, dword ptr [eax + 8]
006d1aea or ecx, dword ptr [eax + 0xc]
006d1aed je 0x6d1c7f
006d1af3 mov eax, dword ptr [edi + 0x28]
006d1af6 cmp eax, 1
006d1af9 je 0x6d1c82
006d1aff movss xmm3, dword ptr [ebp - 0x20]
006d1b04 addss xmm0, xmm0
006d1b08 movss xmm4, dword ptr [ebp - 0x18]
006d1b0d divss xmm3, xmm2
006d1b11 divss xmm4, xmm2
006d1b15 movss xmm1, dword ptr [edi + 0x2b8]
006d1b1d movss xmm2, dword ptr [edi + 0x2bc]
006d1b25 mulss xmm3, xmm0
006d1b29 mulss xmm4, xmm0
006d1b2d mulss xmm2, xmm5
006d1b31 mulss xmm1, xmm5
006d1b35 addss xmm2, xmm4
006d1b39 addss xmm1, xmm3
006d1b3d movss dword ptr [edi + 0x2bc], xmm2
006d1b45 movss dword ptr [edi + 0x2b8], xmm1
006d1b4d xorps xmm1, xmm1
006d1b50 mov eax, dword ptr [edi + 0x28]
006d1b53 cmp eax, 1
006d1b56 je 0x6d205b
006d1b5c cmp eax, 3
006d1b5f je 0x6d205b
006d1b65 cmp eax, 0x3e8
006d1b6a jne 0x6d1ec7
006d1b70 mov eax, dword ptr [edi + 0x2c]
006d1b73 cmp eax, 0x15
006d1b76 je 0x6d1ebb
006d1b7c cmp eax, 0x21
006d1b7f je 0x6d1ebb
006d1b85 cmp eax, 0x3f
006d1b88 je 0x6d1ebb
006d1b8e cmp eax, 0x40
006d1b91 je 0x6d1ebb
006d1b97 cmp eax, 0x9f
006d1b9c je 0x6d1ebb
006d1ba2 cmp eax, 0x9e
006d1ba7 je 0x6d1ebb
006d1bad cmp eax, 0x4a
006d1bb0 jne 0x6d1ec7
006d1bb6 cmp dword ptr [edi + 0x30], 0
006d1bba jne 0x6d20c4
006d1bc0 mov eax, dword ptr [0xbfd65c]
006d1bc5 mov eax, dword ptr [eax + 0x18190]
006d1bcb cmp dword ptr [eax + 8], 0x12
006d1bcf jne 0x6d1e0a
006d1bd5 call 0x6c3d90
006d1bda mov esi, dword ptr [0xbfd65c]
006d1be0 mov dword ptr [ebp - 0x24], eax
006d1be3 lea eax, [ebp - 0x68]
006d1be6 push eax
006d1be7 mov ecx, dword ptr [esi + 0x18190]
006d1bed call 0x7ce9c0
006d1bf2 movss xmm1, dword ptr [0xb6aa3c]
006d1bfa mov esi, dword ptr [esi + 0x18190]
006d1c00 mov dword ptr [ebp - 0x20], esi
006d1c03 movss xmm0, dword ptr [eax]
006d1c07 subss xmm0, xmm1
006d1c0b divss xmm0, xmm1
006d1c0f addss xmm0, dword ptr [0xb6a480]
006d1c17 cvttss2si edx, xmm0
006d1c1b movss xmm0, dword ptr [eax + 4]
006d1c20 subss xmm0, dword ptr [0xb6ab20]
006d1c28 divss xmm0, xmm1
006d1c2c addss xmm0, dword ptr [0xb6a480]
006d1c34 cvttss2si ecx, xmm0
006d1c38 test edx, edx
006d1c3a js 0x6d1d47
006d1c40 mov eax, dword ptr [esi + 0xc]
006d1c43 cmp edx, eax
006d1c45 jge 0x6d1d47
006d1c4b test ecx, ecx
006d1c4d js 0x6d1d47
006d1c53 cmp ecx, dword ptr [esi + 0x10]
006d1c56 jge 0x6d1d47
006d1c5c imul eax, ecx
006d1c5f add eax, edx
006d1c61 mov dword ptr [ebp - 0x18], eax
006d1c64 js 0x6d1d51
006d1c6a mov ecx, eax
006d1c6c mov dword ptr [ebp - 0x18], ecx
006d1c6f cmp eax, 0x1c0
006d1c74 jl 0x6d1d63
006d1c7a jmp 0x6d1d51
006d1c7f mov eax, dword ptr [edi + 0x28]
006d1c82 movss xmm3, dword ptr [ebp - 0x20]
006d1c87 movss xmm4, dword ptr [ebp - 0x18]
006d1c8c movss xmm1, dword ptr [edi + 0x2b8]
006d1c94 divss xmm3, xmm2
006d1c98 divss xmm4, xmm2
006d1c9c movss xmm2, dword ptr [edi + 0x2bc]
006d1ca4 mulss xmm3, xmm0
006d1ca8 mulss xmm4, xmm0
006d1cac cmp eax, 1
006d1caf jne 0x6d1b2d
006d1cb5 mulss xmm1, xmm5
006d1cb9 mov dword ptr [ebp - 0x24], 0x41200000
006d1cc0 mulss xmm2, xmm5
006d1cc4 addss xmm1, xmm3
006d1cc8 addss xmm2, xmm4
006d1ccc movaps xmm0, xmm1
006d1ccf movss dword ptr [ebp - 0x1c], xmm1
006d1cd4 mulss xmm0, xmm1
006d1cd8 movaps xmm1, xmm2
006d1cdb movss dword ptr [ebp - 0x20], xmm2
006d1ce0 mulss xmm1, xmm2
006d1ce4 addss xmm0, xmm1
006d1ce8 call 0x4228c0
006d1ced comiss xmm0, dword ptr [0xb6a974]
006d1cf4 lea eax, [ebp - 0x24]
006d1cf7 lea ecx, [ebp - 0x2c]
006d1cfa movss xmm1, dword ptr [ebp - 0x1c]
006d1cff movss dword ptr [ebp - 0x2c], xmm0
006d1d04 cmovbe eax, ecx
006d1d07 comiss xmm0, dword ptr [0xb6a18c]
006d1d0e movss xmm2, dword ptr [eax]
006d1d12 jbe 0x6d1d35
006d1d14 divss xmm2, xmm0
006d1d18 movaps xmm0, xmm2
006d1d1b mulss xmm1, xmm0
006d1d1f movss xmm0, dword ptr [ebp - 0x20]
006d1d24 mulss xmm0, xmm2
006d1d28 movss dword ptr [edi + 0x2bc], xmm0
006d1d30 jmp 0x6d1b45
006d1d35 movss xmm0, dword ptr [ebp - 0x20]
006d1d3a movss dword ptr [edi + 0x2bc], xmm0
006d1d42 jmp 0x6d1b45
006d1d47 mov dword ptr [ebp - 0x18], 0xffffffff
006d1d4e mov dword ptr [ebp - 0x20], esi
006d1d51 push 0xb4d8a0
006d1d56 push 3
006d1d58 call 0x95e330
006d1d5d mov ecx, dword ptr [ebp - 0x18]
006d1d60 add esp, 8
006d1d63 push ecx
006d1d64 mov ecx, esi
006d1d66 call 0x7aeec0
006d1d6b test eax, eax
006d1d6d jg 0x6d1eac
006d1d73 push 0x154
006d1d78 call 0x9eacf8
006d1d7d mov esi, eax
006d1d7f add esp, 4
006d1d82 mov dword ptr [ebp - 0x40], esi
006d1d85 mov ecx, esi
006d1d87 mov byte ptr [ebp - 4], 0x11
006d1d8b call 0x6dad90
006d1d90 mov ecx, dword ptr [ebp - 0x18]
006d1d93 mov eax, dword ptr [ebp - 0x20]
006d1d96 mov dword ptr [esi], 0xb5a138
006d1d9c mov byte ptr [ebp - 4], 0
006d1da0 mov dword ptr [esi + 4], 0x12
006d1da7 mov dword ptr [esi + 0x24], ecx
006d1daa mov edx, dword ptr [eax + ecx*4 + 0x24]
006d1dae test edx, edx
006d1db0 je 0x6d1dc0
006d1db2 mov eax, dword ptr [edx]
006d1db4 mov ecx, edx
006d1db6 push 1
006d1db8 call dword ptr [eax]
006d1dba mov eax, dword ptr [ebp - 0x20]
006d1dbd mov ecx, dword ptr [ebp - 0x18]
006d1dc0 mov dword ptr [eax + ecx*4 + 0x24], esi
006d1dc4 mov ecx, esi
006d1dc6 mov eax, dword ptr [ebp - 0x24]
006d1dc9 mov dword ptr [esi + 0x14], eax
006d1dcc mov eax, dword ptr [esi]
006d1dce mov dword ptr [esi + 8], 0
006d1dd5 mov dword ptr [esi + 0x18], 0
006d1ddc mov dword ptr [esi + 0x3c], 0
006d1de3 call dword ptr [eax + 0x28]
006d1de6 mov eax, dword ptr [0xbfd65c]
006d1deb inc dword ptr [esi + 0x10]
006d1dee mov byte ptr [esi + 0x1c], 1
006d1df2 mov eax, dword ptr [eax + 0x1a30dc]
006d1df8 mov dword ptr [esi + 0x28], eax
006d1dfb mov esi, dword ptr [ebx + 0x18]
006d1dfe mov dword ptr [edi + 0x30], 0x3e8
006d1e05 jmp 0x6d20c4
006d1e0a mov ecx, dword ptr [0xbfd65c]
006d1e10 call 0x718620
006d1e15 test al, al
006d1e17 je 0x6d1eaf
006d1e1d call 0x6c3d90
006d1e22 mov esi, dword ptr [0xbfd65c]
006d1e28 mov dword ptr [ebp - 0x24], eax
006d1e2b lea eax, [ebp - 0x70]
006d1e2e push eax
006d1e2f mov ecx, dword ptr [esi + 0x18190]
006d1e35 call 0x7ce9c0
006d1e3a movss xmm1, dword ptr [0xb6aa3c]
006d1e42 mov edx, dword ptr [esi + 0x18190]
006d1e48 movss xmm0, dword ptr [eax]
006d1e4c subss xmm0, xmm1
006d1e50 divss xmm0, xmm1
006d1e54 addss xmm0, dword ptr [0xb6a480]
006d1e5c cvttss2si esi, xmm0
006d1e60 movss xmm0, dword ptr [eax + 4]
006d1e65 subss xmm0, dword ptr [0xb6ab20]
006d1e6d divss xmm0, xmm1
006d1e71 addss xmm0, dword ptr [0xb6a480]
006d1e79 cvttss2si ecx, xmm0
006d1e7d test esi, esi
006d1e7f js 0x6d1e98
006d1e81 mov eax, dword ptr [edx + 0xc]
006d1e84 cmp esi, eax
006d1e86 jge 0x6d1e98
006d1e88 test ecx, ecx
006d1e8a js 0x6d1e98
006d1e8c cmp ecx, dword ptr [edx + 0x10]
006d1e8f jge 0x6d1e98
006d1e91 imul eax, ecx
006d1e94 add eax, esi
006d1e96 jmp 0x6d1e9b
006d1e98 or eax, 0xffffffff
006d1e9b push 0
006d1e9d push dword ptr [ebp - 0x24]
006d1ea0 mov ecx, edx
006d1ea2 push 0
006d1ea4 push 0x11
006d1ea6 push eax
006d1ea7 call 0x7aa9b0
006d1eac mov esi, dword ptr [ebx + 0x18]
006d1eaf mov dword ptr [edi + 0x30], 0x3e8
006d1eb6 jmp 0x6d20c4
006d1ebb mov byte ptr [edi + 0x16b], 1
006d1ec2 jmp 0x6d20c4
006d1ec7 movss xmm1, dword ptr [ebx + 0xc]
006d1ecc lea edx, [ebx + 0x1c]
006d1ecf push 0xbc48c0
006d1ed4 lea ecx, [ebp - 0xb8]
006d1eda movss dword ptr [ebp - 0x1c], xmm1
006d1edf call 0x412050
006d1ee4 add esp, 4
006d1ee7 mov ecx, dword ptr [eax]
006d1ee9 or ecx, dword ptr [eax + 4]
006d1eec jne 0x6d1ef6
006d1eee mov ecx, dword ptr [eax + 8]
006d1ef1 or ecx, dword ptr [eax + 0xc]
006d1ef4 je 0x6d1f71
006d1ef6 mov eax, dword ptr [edi + 8]
006d1ef9 xor esi, esi
006d1efb mov ecx, dword ptr [edi + 0xc]
006d1efe sub ecx, eax
006d1f00 mov dword ptr [ebp - 0x24], eax
006d1f03 mov eax, 0x92492493
006d1f08 mov dword ptr [ebp - 0x1c], esi
006d1f0b imul ecx
006d1f0d add edx, ecx
006d1f0f sar edx, 5
006d1f12 mov eax, edx
006d1f14 shr eax, 0x1f
006d1f17 add eax, edx
006d1f19 mov dword ptr [ebp - 0x2c], eax
006d1f1c je 0x6d1f44
006d1f1e xor ecx, ecx
006d1f20 mov edx, dword ptr [ebp - 0x24]
006d1f23 lea ecx, [ecx + 0x38]
006d1f26 mov edi, dword ptr [ebx + 0x18]
006d1f29 mov eax, esi
006d1f2b cmp dword ptr [edx + ecx - 4], edi
006d1f2f mov edi, dword ptr [ebp - 0x1c]
006d1f32 lea esi, [eax + 1]
006d1f35 cmovne esi, eax
006d1f38 inc edi
006d1f39 mov dword ptr [ebp - 0x1c], edi
006d1f3c cmp edi, dword ptr [ebp - 0x2c]
006d1f3f jb 0x6d1f20
006d1f41 mov edi, dword ptr [ebp - 0x28]
006d1f44 mov ecx, esi
006d1f46 mov eax, 1
006d1f4b shl eax, cl
006d1f4d mov esi, dword ptr [ebx + 0x18]
006d1f50 movd xmm0, eax
006d1f54 cvtdq2pd xmm0, xmm0
006d1f58 shr eax, 0x1f
006d1f5b addsd xmm0, qword ptr [eax*8 + 0xb6c940]
006d1f64 cvtpd2ps xmm0, xmm0
006d1f68 divss xmm1, xmm0
006d1f6c movss dword ptr [ebp - 0x1c], xmm1
006d1f71 lea eax, [ebp - 0xc8]
006d1f77 mov ecx, 0xbc4ca0
006d1f7c push eax
006d1f7d call 0x57f3a0
006d1f82 push eax
006d1f83 lea edx, [ebx + 0x1c]
006d1f86 lea ecx, [ebp - 0xd8]
006d1f8c call 0x412050
006d1f91 add esp, 4
006d1f94 lea edx, [ebx + 0x2c]
006d1f97 movups xmm0, xmmword ptr [eax]
006d1f9a push esi
006d1f9b sub esp, 0x14
006d1f9e mov ecx, esp
006d1fa0 push ecx
006d1fa1 movups xmmword ptr [ecx], xmm0
006d1fa4 call 0x656c90
006d1fa9 add esp, 0x1c
006d1fac lea ecx, [ebp - 0x120]
006d1fb2 push esi
006d1fb3 call 0x4229a0
006d1fb8 mov eax, dword ptr [edi]
006d1fba lea ecx, [ebp - 0x120]
006d1fc0 movss xmm0, dword ptr [ebp - 0x1c]
006d1fc5 push 0x1e
006d1fc7 push ecx
006d1fc8 push dword ptr [ebx + 0x30]
006d1fcb push dword ptr [ebx + 0x2c]
006d1fce push ecx
006d1fcf mov ecx, edi
006d1fd1 movss dword ptr [esp], xmm0
006d1fd6 call dword ptr [eax + 0x20]
006d1fd9 mov eax, dword ptr [ebx + 0x1c]
006d1fdc or eax, dword ptr [ebx + 0x20]
006d1fdf jne 0x6d1fed
006d1fe1 mov eax, dword ptr [ebx + 0x24]
006d1fe4 or eax, dword ptr [ebx + 0x28]
006d1fe7 je 0x6d20c4
006d1fed test esi, esi
006d1fef je 0x6d20c4
006d1ff5 mov eax, dword ptr [esi + 0x34]
006d1ff8 cmp eax, 0xa
006d1ffb jl 0x6d2008
006d1ffd cmp eax, 0x3e8
006d2002 jl 0x6d20c4
006d2008 push 0
006d200a mov ecx, edi
006d200c call 0x684630
006d2011 test al, al
006d2013 je 0x6d20c4
006d2019 lea eax, [ebp - 0xe8]
006d201f mov ecx, 0xbc4ca0
006d2024 push eax
006d2025 call 0x57f3a0
006d202a push eax
006d202b lea edx, [ebx + 0x1c]
006d202e lea ecx, [ebp - 0xf8]
006d2034 call 0x412050
006d2039 mov dword ptr [esp], 0x40600000
006d2040 mov ecx, edi
006d2042 push esi
006d2043 sub esp, 0x10
006d2046 movups xmm0, xmmword ptr [eax]
006d2049 mov edx, esp
006d204b movups xmmword ptr [edx], xmm0
006d204e mov edx, dword ptr [ebx + 8]
006d2051 call 0x654de0
006d2056 add esp, 0x18
006d2059 jmp 0x6d20c4
006d205b movss xmm0, dword ptr [ebx + 0xc]
006d2060 comiss xmm0, xmm1
006d2063 jbe 0x6d20c4
006d2065 push esi
006d2066 lea ecx, [ebp - 0x98]
006d206c call 0x4229a0
006d2071 movzx eax, byte ptr [ebp - 0x11]
006d2075 movss xmm1, dword ptr [0xb6a614]
006d207d add eax, eax
006d207f or dword ptr [ebp - 0x78], eax
006d2082 comiss xmm0, dword ptr [0xb6aad8]
006d2089 jb 0x6d2095
006d208b movss xmm0, dword ptr [0xb6a7b0]
006d2093 jmp 0x6d2098
006d2095 movaps xmm0, xmm1
006d2098 mov ecx, dword ptr [ebx + 0x2c]
006d209b mov eax, ecx
006d209d and eax, 0x10000000
006d20a2 or eax, 0
006d20a5 je 0x6d20aa
006d20a7 movaps xmm0, xmm1
006d20aa mov eax, dword ptr [edi]
006d20ac lea edx, [ebp - 0x98]
006d20b2 push 0x1e
006d20b4 push edx
006d20b5 push dword ptr [ebx + 0x30]
006d20b8 push ecx
006d20b9 push ecx
006d20ba mov ecx, edi
006d20bc movss dword ptr [esp], xmm0
006d20c1 call dword ptr [eax + 0x20]
006d20c4 mov edi, dword ptr [ebp - 0x30]
006d20c7 inc edi
006d20c8 mov dword ptr [ebp - 0x30], edi
006d20cb cmp edi, dword ptr [ebp - 0x54]
006d20ce jb 0x6d1833
006d20d4 push 0x14
006d20d6 mov dword ptr [ebp - 0x3c], 0
006d20dd mov dword ptr [ebp - 0x38], 0
006d20e4 call 0x9eacf8
006d20e9 mov esi, eax
006d20eb mov dword ptr [ebp - 0x24], esi
006d20ee mov dword ptr [esi], esi
006d20f0 mov dword ptr [esi + 4], esi
006d20f3 mov dword ptr [esi + 8], esi
006d20f6 mov word ptr [esi + 0xc], 0x101
006d20fc mov dword ptr [ebp - 0x3c], esi
006d20ff movss xmm0, dword ptr [ebx + 0x10]
006d2104 mov byte ptr [ebp - 4], 0x17
006d2108 mulss xmm0, dword ptr [0xb6a940]
006d2110 push ecx
006d2111 divss xmm0, dword ptr [0xb6aa3c]
006d2119 movss dword ptr [ebp - 0x28], xmm0
006d211e fld dword ptr [ebp - 0x28]
006d2121 fstp qword ptr [esp]
006d2124 call 0x9ec3ac
006d2129 mov ecx, dword ptr [ebx + 8]
006d212c add esp, 8
006d212f movss xmm1, dword ptr [0xb6a914]
006d2137 movss xmm2, dword ptr [0xb6aa3c]
006d213f fstp dword ptr [ebp - 0x28]
006d2142 fld dword ptr [ebp - 0x28]
006d2145 fstp dword ptr [ebp - 0x28]
006d2148 cvttss2si edi, dword ptr [ebp - 0x28]
006d214d mov eax, dword ptr [0xbfd65c]
006d2152 mov eax, dword ptr [eax + 0x18190]
006d2158 mov dword ptr [ebp - 0x28], eax
006d215b mov dword ptr [ebp - 0x30], edi
006d215e movd xmm0, edi
006d2162 cvtdq2ps xmm0, xmm0
006d2165 divss xmm1, xmm0
006d2169 movss xmm0, dword ptr [ecx]
006d216d subss xmm0, xmm2
006d2171 movss dword ptr [ebp - 0x20], xmm1
006d2176 xorps xmm1, xmm1
006d2179 movss dword ptr [ebp - 0x18], xmm1
006d217e divss xmm0, xmm2
006d2182 addss xmm0, dword ptr [0xb6a480]
006d218a cvttss2si edx, xmm0
006d218e movss xmm0, dword ptr [ecx + 4]
006d2193 subss xmm0, dword ptr [0xb6ab20]
006d219b divss xmm0, xmm2
006d219f addss xmm0, dword ptr [0xb6a480]
006d21a7 cvttss2si ecx, xmm0
006d21ab test edx, edx
006d21ad js 0x6d21e7
006d21af mov eax, dword ptr [eax + 0xc]
006d21b2 cmp edx, eax
006d21b4 jge 0x6d21e7
006d21b6 test ecx, ecx
006d21b8 js 0x6d21e7
006d21ba mov esi, dword ptr [ebp - 0x28]
006d21bd cmp ecx, dword ptr [esi + 0x10]
006d21c0 mov esi, dword ptr [ebp - 0x24]
006d21c3 jge 0x6d21e7
006d21c5 imul eax, ecx
006d21c8 add eax, edx
006d21ca mov dword ptr [ebp - 0x28], eax
006d21cd js 0x6d21e7
006d21cf lea eax, [ebp - 0x28]
006d21d2 push eax
006d21d3 lea eax, [ebp - 0x4c]
006d21d6 push eax
006d21d7 lea ecx, [ebp - 0x3c]
006d21da call 0x4d1cd0
006d21df mov esi, dword ptr [ebp - 0x3c]
006d21e2 movss xmm1, dword ptr [ebp - 0x18]
006d21e7 test edi, edi
006d21e9 jle 0x6d231f
006d21ef nop 
006d21f0 movaps xmm0, xmm1
006d21f3 call 0x411fe0
006d21f8 movss dword ptr [ebp - 0x28], xmm0
006d21fd movss xmm0, dword ptr [ebp - 0x18]
006d2202 call 0x412010
006d2207 movaps xmm1, xmm0
006d220a xorps xmm3, xmm3
006d220d movss xmm0, dword ptr [ebx + 0x10]
006d2212 xorps xmm2, xmm2
006d2215 comiss xmm0, xmm3
006d2218 movss dword ptr [ebp - 0x1c], xmm1
006d221d jbe 0x6d2301
006d2223 movss xmm3, dword ptr [0xb6aa3c]
006d222b movss xmm4, dword ptr [0xb6a480]
006d2233 mov edi, dword ptr [ebx + 8]
006d2236 nop word ptr [eax + eax]
006d2240 addss xmm2, dword ptr [0xb6a9c8]
006d2248 mov eax, dword ptr [0xbfd65c]
006d224d minss xmm2, xmm0
006d2251 mov esi, dword ptr [eax + 0x18190]
006d2257 movss xmm0, dword ptr [ebp - 0x28]
006d225c mulss xmm0, xmm2
006d2260 mulss xmm1, xmm2
006d2264 addss xmm0, dword ptr [edi]
006d2268 movss dword ptr [ebp - 0x2c], xmm2
006d226d addss xmm1, dword ptr [edi + 4]
006d2272 subss xmm0, xmm3
006d2276 subss xmm1, dword ptr [0xb6ab20]
006d227e divss xmm0, xmm3
006d2282 divss xmm1, xmm3
006d2286 addss xmm0, xmm4
006d228a addss xmm1, xmm4
006d228e cvttss2si ecx, xmm0
006d2292 cvttss2si eax, xmm1
006d2296 test ecx, ecx
006d2298 js 0x6d22ea
006d229a mov edx, dword ptr [esi + 0xc]
006d229d cmp ecx, edx
006d229f jge 0x6d22ea
006d22a1 test eax, eax
006d22a3 js 0x6d22ea
006d22a5 cmp eax, dword ptr [esi + 0x10]
006d22a8 jge 0x6d22ea
006d22aa imul eax, edx
006d22ad add eax, ecx
006d22af js 0x6d22ea
006d22b1 mov esi, dword ptr [esi + eax*4 + 0x24]
006d22b5 test esi, esi
006d22b7 je 0x6d22ea
006d22b9 mov eax, dword ptr [esi + 0x24]
006d22bc lea ecx, [ebp - 0x3c]
006d22bf mov dword ptr [ebp - 0x24], eax
006d22c2 lea eax, [ebp - 0x24]
006d22c5 push eax
006d22c6 lea eax, [ebp - 0x4c]
006d22c9 push eax
006d22ca call 0x4d1cd0
006d22cf cmp dword ptr [esi + 4], 3
006d22d3 je 0x6d22fe
006d22d5 movss xmm2, dword ptr [ebp - 0x2c]
006d22da movss xmm3, dword ptr [0xb6aa3c]
006d22e2 movss xmm4, dword ptr [0xb6a480]
006d22ea movss xmm0, dword ptr [ebx + 0x10]
006d22ef comiss xmm0, xmm2
006d22f2 jbe 0x6d22fe
006d22f4 movss xmm1, dword ptr [ebp - 0x1c]
006d22f9 jmp 0x6d2240
006d22fe mov edi, dword ptr [ebp - 0x30]
006d2301 movss xmm1, dword ptr [ebp - 0x18]
006d2306 sub edi, 1
006d2309 addss xmm1, dword ptr [ebp - 0x20]
006d230e mov dword ptr [ebp - 0x30], edi
006d2311 movss dword ptr [ebp - 0x18], xmm1
006d2316 jne 0x6d21f0
006d231c mov esi, dword ptr [ebp - 0x3c]
006d231f mov edi, dword ptr [esi]
006d2321 mov dword ptr [ebp - 0x2c], edi
006d2324 cmp edi, esi
006d2326 je 0x6d2699
006d232c movss xmm4, dword ptr [0xb6aa3c]
006d2334 movss xmm1, dword ptr [0xb6ab20]
006d233c nop dword ptr [eax]
006d2340 mov ecx, dword ptr [0xbfd65c]
006d2346 mov eax, dword ptr [edi + 0x10]
006d2349 cdq 
006d234a push 0
006d234c mov ecx, dword ptr [ecx + 0x18190]
006d2352 push 0
006d2354 push 0
006d2356 push 0
006d2358 mov ecx, dword ptr [ecx + 0xc]
006d235b idiv ecx
006d235d push 2
006d235f movd xmm0, edx
006d2363 cvtdq2ps xmm0, xmm0
006d2366 mulss xmm0, xmm4
006d236a addss xmm0, xmm4
006d236e movss dword ptr [ebp - 0x44], xmm0
006d2373 movd xmm0, eax
006d2377 lea eax, [ebp - 0x44]
006d237a cvtdq2ps xmm0, xmm0
006d237d push eax
006d237e mov eax, dword ptr [ebp - 0x34]
006d2381 push dword ptr [ebx + 8]
006d2384 mov ecx, dword ptr [eax + 0x18190]
006d238a mulss xmm0, xmm4
006d238e addss xmm0, xmm1
006d2392 movss dword ptr [ebp - 0x40], xmm0
006d2397 call 0x7af4b0
006d239c test al, al
006d239e je 0x6d2673
006d23a4 mov eax, dword ptr [ebp - 0x34]
006d23a7 mov esi, dword ptr [edi + 0x10]
006d23aa mov ecx, dword ptr [eax + 0x18190]
006d23b0 mov eax, dword ptr [ecx + 4]
006d23b3 mov eax, dword ptr [eax + 0x10]
006d23b6 test eax, eax
006d23b8 je 0x6d23ce
006d23ba cmp dword ptr [eax + 8], 0x10
006d23be jne 0x6d23ce
006d23c0 cmp dword ptr [eax], 0x23
006d23c3 jne 0x6d23ce
006d23c5 mov dword ptr [ebp - 0x18], 0
006d23cc jmp 0x6d2418
006d23ce test esi, esi
006d23d0 jns 0x6d23db
006d23d2 mov dword ptr [ebp - 0x18], 4
006d23d9 jmp 0x6d2418
006d23db mov eax, dword ptr [ecx + esi*4 + 0x24]
006d23df test eax, eax
006d23e1 jne 0x6d2412
006d23e3 mov edx, dword ptr [ecx + esi*4 + 0x76c]
006d23ea lea eax, [edx - 0xbb8]
006d23f0 cmp eax, 0x3e7
006d23f5 ja 0x6d2400
006d23f7 mov dword ptr [ebp - 0x18], 1
006d23fe jmp 0x6d2418
006d2400 xor eax, eax
006d2402 cmp edx, 0x3e8
006d2408 mov edx, 3
006d240d cmovge eax, edx
006d2410 jmp 0x6d2415
006d2412 mov eax, dword ptr [eax + 0x3c]
006d2415 mov dword ptr [ebp - 0x18], eax
006d2418 cmp esi, 0x1bf
006d241e ja 0x6d2537
006d2424 mov esi, dword ptr [ecx + esi*4 + 0x24]
006d2428 mov dword ptr [ebp - 0x20], esi
006d242b test esi, esi
006d242d je 0x6d2539
006d2433 cmp dword ptr [esi + 4], 0xb
006d2437 jne 0x6d2539
006d243d cmp dword ptr [esi + 0xc], 0
006d2441 jne 0x6d24f0
006d2447 mov eax, dword ptr [0xbfd680]
006d244c mov esi, dword ptr [0xbfd65c]
006d2452 mov dword ptr [ebp - 0x30], esi
006d2455 mov ecx, dword ptr [eax + 0x29e90]
006d245b mov eax, dword ptr [eax + 0x29e94]
006d2461 sub eax, ecx
006d2463 and eax, 0xfffffffc
006d2466 cmp eax, 0x220
006d246b jle 0x6d248d
006d246d mov eax, dword ptr [ecx + 0x220]
006d2473 test eax, eax
006d2475 je 0x6d248d
006d2477 mov eax, dword ptr [eax + 0xb8]
006d247d and eax, 0x80000000
006d2482 or eax, 0
006d2485 je 0x6d248d
006d2487 mov byte ptr [ebp - 0x11], 1
006d248b jmp 0x6d2492
006d248d xor al, al
006d248f mov byte ptr [ebp - 0x11], al
006d2492 mov eax, dword ptr [ebp - 0x30]
006d2495 mov esi, dword ptr [esi + 0x1ba50]
006d249b cmp esi, dword ptr [eax + 0x1ba54]
006d24a1 je 0x6d24ed
006d24a3 mov eax, dword ptr [esi]
006d24a5 mov dword ptr [ebp - 0x1c], eax
006d24a8 cmp dword ptr [eax + 0x2c], 0
006d24ac jne 0x6d24df
006d24ae push 0x88
006d24b3 mov ecx, eax
006d24b5 call 0x78d4c0
006d24ba test eax, eax
006d24bc jg 0x6d250c
006d24be cmp byte ptr [ebp - 0x11], 0
006d24c2 je 0x6d24df
006d24c4 mov eax, dword ptr [ebp - 0x1c]
006d24c7 mov ecx, dword ptr [eax + 0x1d84]
006d24cd test ecx, ecx
006d24cf je 0x6d24df
006d24d1 push 0x88
006d24d6 call 0x78d4c0
006d24db test eax, eax
006d24dd jg 0x6d2501
006d24df mov eax, dword ptr [ebp - 0x30]
006d24e2 add esi, 4
006d24e5 cmp esi, dword ptr [eax + 0x1ba54]
006d24eb jne 0x6d24a3
006d24ed mov esi, dword ptr [ebp - 0x20]
006d24f0 mov eax, dword ptr [esi]
006d24f2 mov ecx, esi
006d24f4 push 4
006d24f6 mov eax, dword ptr [eax + 0x10]
006d24f9 call eax
006d24fb test al, al
006d24fd jne 0x6d256e
006d24ff jmp 0x6d2539
006d2501 mov eax, dword ptr [ebp - 0x1c]
006d2504 mov eax, dword ptr [eax + 0x1d84]
006d250a jmp 0x6d250f
006d250c mov eax, dword ptr [ebp - 0x1c]
006d250f mov esi, dword ptr [ebp - 0x20]
006d2512 test eax, eax
006d2514 je 0x6d24f0
006d2516 push 0
006d2518 mov ecx, esi
006d251a call 0x6e2140
006d251f cmp dword ptr [esi + 0x74], 0
006d2523 je 0x6d256e
006d2525 movss xmm1, dword ptr [0xb6a9c8]
006d252d lea ecx, [esi + 0x70]
006d2530 call 0x403c00
006d2535 jmp 0x6d256e
006d2537 xor esi, esi
006d2539 mov ecx, dword ptr [edi + 0x10]
006d253c cmp ecx, 0x1bf
006d2542 ja 0x6d2673
006d2548 mov eax, dword ptr [ebp - 0x34]
006d254b mov eax, dword ptr [eax + 0x18190]
006d2551 mov ecx, dword ptr [eax + ecx*4 + 0x24]
006d2555 test ecx, ecx
006d2557 je 0x6d2673
006d255d mov eax, dword ptr [ecx]
006d255f push 0
006d2561 mov eax, dword ptr [eax + 0x14]
006d2564 call eax
006d2566 test al, al
006d2568 je 0x6d2673
006d256e cmp dword ptr [ebp - 0x18], 3
006d2572 jne 0x6d2673
006d2578 mov eax, dword ptr [ebx + 8]
006d257b xorps xmm6, xmm6
006d257e movss xmm2, dword ptr [ebp - 0x44]
006d2583 movss xmm3, dword ptr [ebp - 0x40]
006d2588 movaps xmm4, xmm2
006d258b movaps xmm5, xmm3
006d258e subss xmm4, dword ptr [eax]
006d2592 subss xmm5, dword ptr [eax + 4]
006d2597 movaps xmm1, xmm4
006d259a andps xmm1, xmmword ptr [0xb6c980]
006d25a1 movaps xmm0, xmm5
006d25a4 andps xmm0, xmmword ptr [0xb6c980]
006d25ab comiss xmm1, xmm0
006d25ae jbe 0x6d25cc
006d25b0 comiss xmm6, xmm4
006d25b3 xorps xmm1, xmm1
006d25b6 jbe 0x6d25c2
006d25b8 movss xmm0, dword ptr [0xb6ae44]
006d25c0 jmp 0x6d25e6
006d25c2 movss xmm0, dword ptr [0xb6a614]
006d25ca jmp 0x6d25e6
006d25cc comiss xmm6, xmm5
006d25cf xorps xmm0, xmm0
006d25d2 jbe 0x6d25de
006d25d4 movss xmm1, dword ptr [0xb6ae44]
006d25dc jmp 0x6d25e6
006d25de movss xmm1, dword ptr [0xb6a614]
006d25e6 movss xmm4, dword ptr [0xb6aa3c]
006d25ee mulss xmm0, xmm4
006d25f2 mov eax, dword ptr [0xbfd65c]
006d25f7 mulss xmm1, xmm4
006d25fb addss xmm2, xmm0
006d25ff mov edi, dword ptr [eax + 0x18190]
006d2605 addss xmm3, xmm1
006d2609 movss xmm1, dword ptr [0xb6ab20]
006d2611 subss xmm2, xmm4
006d2615 subss xmm3, xmm1
006d2619 divss xmm2, xmm4
006d261d divss xmm3, xmm4
006d2621 addss xmm2, dword ptr [0xb6a480]
006d2629 addss xmm3, dword ptr [0xb6a480]
006d2631 cvttss2si ecx, xmm2
006d2635 cvttss2si eax, xmm3
006d2639 test ecx, ecx
006d263b js 0x6d2683
006d263d mov edx, dword ptr [edi + 0xc]
006d2640 cmp ecx, edx
006d2642 jge 0x6d2683
006d2644 test eax, eax
006d2646 js 0x6d2683
006d2648 cmp eax, dword ptr [edi + 0x10]
006d264b jge 0x6d2683
006d264d imul eax, edx
006d2650 add eax, ecx
006d2652 js 0x6d2683
006d2654 mov ecx, dword ptr [ebp - 0x34]
006d2657 mov ecx, dword ptr [ecx + 0x18190]
006d265d cmp eax, 0x1c0
006d2662 jge 0x6d266a
006d2664 mov eax, dword ptr [ecx + eax*4 + 0x24]
006d2668 jmp 0x6d266c
006d266a xor eax, eax
006d266c push esi
006d266d push eax
006d266e call 0x7d9890
006d2673 movss xmm1, dword ptr [0xb6ab20]
006d267b movss xmm4, dword ptr [0xb6aa3c]
006d2683 lea ecx, [ebp - 0x2c]
006d2686 call 0x40f830
006d268b mov edi, dword ptr [ebp - 0x2c]
006d268e mov esi, dword ptr [ebp - 0x3c]
006d2691 cmp edi, esi
006d2693 jne 0x6d2340
006d2699 push dword ptr [esi + 4]
006d269c lea eax, [ebp - 0x3c]
006d269f push eax
006d26a0 mov ecx, eax
006d26a2 call 0x420480
006d26a7 push 0x14
006d26a9 push dword ptr [ebp - 0x3c]
006d26ac call 0x9eb08e
006d26b1 add esp, 8
006d26b4 cmp byte ptr [ebp - 0x60], 0
006d26b8 jne 0x6d26c5
006d26ba push dword ptr [ebp - 0x5c]
006d26bd call 0x9eace5
006d26c2 add esp, 4
006d26c5 mov ecx, dword ptr [ebp - 0xc]
006d26c8 mov dword ptr fs:[0], ecx
006d26cf pop ecx
006d26d0 pop edi
006d26d1 pop esi
006d26d2 mov esp, ebp
006d26d4 pop ebp
006d26d5 mov esp, ebx
006d26d7 pop ebx
006d26d8 ret 0x30
006d26db int3 
006d26dc int3 
006d26dd int3 
006d26de int3 
006d26df int3 
