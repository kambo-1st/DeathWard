006a15a0 push ebp
006a15a1 mov ebp, esp
006a15a3 sub esp, 0x14
006a15a6 push ebx
006a15a7 push esi
006a15a8 mov esi, ecx
006a15aa movss dword ptr [ebp - 0xc], xmm1
006a15af push edi
006a15b0 mov eax, dword ptr [esi + 0x164]
006a15b6 mov ecx, dword ptr [esi + 0x160]
006a15bc mov dword ptr [ebp - 4], eax
006a15bf mov eax, ecx
006a15c1 and eax, 0x200
006a15c6 or eax, 0
006a15c9 jne 0x6a1743
006a15cf and ecx, 0x1000800
006a15d5 or ecx, eax
006a15d7 jne 0x6a1743
006a15dd cmp dword ptr [esi + 0xe6c], -1
006a15e4 mov ecx, esi
006a15e6 je 0x6a162d
006a15e8 movss xmm2, dword ptr [0xb6a2cc]
006a15f0 lea eax, [ebp - 0x10]
006a15f3 push eax
006a15f4 call 0x6af380
006a15f9 mov ecx, eax
006a15fb movss xmm0, dword ptr [ecx]
006a15ff ucomiss xmm0, dword ptr [0xc02fec]
006a1606 lahf 
006a1607 test ah, 0x44
006a160a jp 0x6a1622
006a160c movss xmm0, dword ptr [ecx + 4]
006a1611 ucomiss xmm0, dword ptr [0xc02ff0]
006a1618 lahf 
006a1619 test ah, 0x44
006a161c jnp 0x6a1743
006a1622 mov al, 1
006a1624 pop edi
006a1625 pop esi
006a1626 pop ebx
006a1627 mov esp, ebp
006a1629 pop ebp
006a162a ret 8
006a162d call 0x695680
006a1632 mov ecx, esi
006a1634 mov edi, eax
006a1636 call 0x695680
006a163b push eax
006a163c mov ecx, esi
006a163e call 0x6aeb40
006a1643 test al, al
006a1645 je 0x6a1743
006a164b cmp byte ptr [ebp + 8], 0
006a164f lea ebx, [esi + 0x294]
006a1655 je 0x6a169c
006a1657 movss xmm1, dword ptr [edi + 0x2b8]
006a165f movss xmm2, dword ptr [edi + 0x2bc]
006a1667 mulss xmm1, dword ptr [0xb6a8f4]
006a166f mulss xmm2, dword ptr [0xb6a8f4]
006a1677 addss xmm1, dword ptr [edi + 0x294]
006a167f addss xmm2, dword ptr [edi + 0x298]
006a1687 subss xmm1, dword ptr [ebx]
006a168b subss xmm2, dword ptr [ebx + 4]
006a1690 movss dword ptr [ebp + 8], xmm1
006a1695 movss dword ptr [ebp - 4], xmm2
006a169a jmp 0x6a16bf
006a169c movss xmm0, dword ptr [edi + 0x294]
006a16a4 movss xmm1, dword ptr [edi + 0x298]
006a16ac subss xmm0, dword ptr [ebx]
006a16b0 subss xmm1, dword ptr [ebx + 4]
006a16b5 movss dword ptr [ebp + 8], xmm0
006a16ba movss dword ptr [ebp - 4], xmm1
006a16bf mov eax, dword ptr [ebp + 0xc]
006a16c2 test eax, eax
006a16c4 je 0x6a16d5
006a16c6 push dword ptr [esi + 0x20]
006a16c9 mov ecx, esi
006a16cb push eax
006a16cc call 0x684790
006a16d1 test al, al
006a16d3 je 0x6a1743
006a16d5 movss xmm1, dword ptr [ebp - 4]
006a16da movss xmm0, dword ptr [ebp + 8]
006a16df mulss xmm1, xmm1
006a16e3 mulss xmm0, xmm0
006a16e7 addss xmm0, xmm1
006a16eb movss xmm1, dword ptr [ebp - 0xc]
006a16f0 mulss xmm1, xmm1
006a16f4 comiss xmm1, xmm0
006a16f7 jbe 0x6a1743
006a16f9 mov ecx, dword ptr [edi + 0x298]
006a16ff mov eax, dword ptr [edi + 0x294]
006a1705 push 0
006a1707 push 0
006a1709 push 0
006a170b push 0x3e7
006a1710 mov dword ptr [ebp - 0xc], ecx
006a1713 mov ecx, dword ptr [0xbfd65c]
006a1719 mov dword ptr [ebp - 0x10], eax
006a171c lea eax, [ebp - 0x10]
006a171f push 3
006a1721 push eax
006a1722 mov ecx, dword ptr [ecx + 0x18190]
006a1728 push ebx
006a1729 call 0x7af4b0
006a172e test al, al
006a1730 jne 0x6a1622
006a1736 cmp dword ptr [esi + 0xbb4], 8
006a173d je 0x6a1622
006a1743 pop edi
006a1744 pop esi
006a1745 xor al, al
006a1747 pop ebx
006a1748 mov esp, ebp
006a174a pop ebp
006a174b ret 8
006a174e int3 
006a174f int3 
006a1750 push ebp
006a1751 mov ebp, esp
006a1753 sub esp, 0xa0
006a1759 mov eax, dword ptr [0xbaa3b4]
006a175e xor eax, ebp
006a1760 mov dword ptr [ebp - 8], eax
006a1763 push ebx
006a1764 mov ebx, dword ptr [ebp + 0x10]
006a1767 push esi
006a1768 mov esi, ecx
006a176a movss dword ptr [ebp - 0x40], xmm1
006a176f mov ecx, dword ptr [ebp + 8]
006a1772 mov eax, ecx
006a1774 push edi
006a1775 and eax, 0x80
006a177a mov edi, edx
006a177c or eax, 0
006a177f mov dword ptr [ebp - 0x3c], edi
006a1782 je 0x6a179a
006a1784 mov eax, dword ptr [esi + 0x38c]
006a178a or dword ptr [esi + 0x388], 0x1000000
006a1794 mov dword ptr [esi + 0x38c], eax
006a179a mov eax, ecx
006a179c and eax, 0x100
006a17a1 or eax, 0
006a17a4 je 0x6a17bc
006a17a6 mov eax, dword ptr [esi + 0x38c]
006a17ac or dword ptr [esi + 0x388], 0x80
006a17b6 mov dword ptr [esi + 0x38c], eax
006a17bc and ecx, 0x20000000
006a17c2 or ecx, 0
006a17c5 je 0x6a17dd
006a17c7 mov eax, dword ptr [esi + 0x38c]
006a17cd or dword ptr [esi + 0x388], 0x80000000
006a17d7 mov dword ptr [esi + 0x38c], eax
006a17dd mov ecx, dword ptr [ebp + 0xc]
006a17e0 test ebx, ebx
006a17e2 je 0x6a1874
006a17e8 mov eax, dword ptr [ebx + 0x28]
006a17eb sub eax, 0xa
006a17ee cmp eax, 0x3dd
006a17f3 ja 0x6a182b
006a17f5 mov ecx, dword ptr [0xbfd65c]
006a17fb push 1
006a17fd add ecx, 0x1ba40
006a1803 push ecx
006a1804 push 0x187
006a1809 call 0x91d340
006a180e mov ecx, dword ptr [ebp + 0xc]
006a1811 test eax, eax
006a1813 je 0x6a182b
006a1815 mov eax, dword ptr [esi + 0x38c]
006a181b or dword ptr [esi + 0x388], 0x80
006a1825 mov dword ptr [esi + 0x38c], eax
006a182b mov eax, dword ptr [esi + 0x388]
006a1831 and eax, 0x80
006a1836 or eax, 0
006a1839 jne 0x6a1845
006a183b and ecx, 0x100000
006a1841 or eax, ecx
006a1843 je 0x6a1874
006a1845 mov ecx, dword ptr [esi + 0x314]
006a184b lea edi, [esi + 0x314]
006a1851 test ecx, ecx
006a1853 je 0x6a1867
006a1855 lea eax, [ebp - 0x38]
006a1858 mov dword ptr [ebp - 0x38], edi
006a185b push eax
006a185c add ecx, 0x324
006a1862 call 0x4bc3c0
006a1867 push edi
006a1868 mov ecx, ebx
006a186a mov dword ptr [edi], ebx
006a186c call 0x4bae70
006a1871 mov edi, dword ptr [ebp - 0x3c]
006a1874 movss xmm0, dword ptr [0xb6a614]
006a187c test edi, edi
006a187e js 0x6a1972
006a1884 cmp dword ptr [esi + 0x2c], 1
006a1888 jne 0x6a191b
006a188e lea eax, [ebp - 0xa0]
006a1894 push eax
006a1895 mov eax, edi
006a1897 shl eax, 4
006a189a sub eax, edi
006a189c lea ecx, [eax*4 + 0xbc5700]
006a18a3 call 0x4f3e00
006a18a8 movups xmm0, xmmword ptr [esi + 0x1b0]
006a18af push eax
006a18b0 mov eax, dword ptr [esi + 0x1d8]
006a18b6 lea ecx, [ebp - 0x74]
006a18b9 movups xmmword ptr [ebp - 0x74], xmm0
006a18bd mov dword ptr [ebp - 0x4c], eax
006a18c0 movups xmm0, xmmword ptr [esi + 0x1c0]
006a18c7 movups xmmword ptr [ebp - 0x64], xmm0
006a18cb movq xmm0, qword ptr [esi + 0x1d0]
006a18d3 movq qword ptr [ebp - 0x54], xmm0
006a18d8 call 0x65b0f0
006a18dd movups xmm0, xmmword ptr [ebp - 0x74]
006a18e1 mov eax, dword ptr [ebp - 0x4c]
006a18e4 lea ecx, [ebp - 0x34]
006a18e7 push 1
006a18e9 push 0
006a18eb movups xmmword ptr [ebp - 0x34], xmm0
006a18ef push 0xff
006a18f4 movups xmm0, xmmword ptr [ebp - 0x64]
006a18f8 mov dword ptr [ebp - 0xc], eax
006a18fb mov eax, dword ptr [esi]
006a18fd push -1
006a18ff movups xmmword ptr [ebp - 0x24], xmm0
006a1903 push ecx
006a1904 movq xmm0, qword ptr [ebp - 0x54]
006a1909 mov ecx, esi
006a190b movq qword ptr [ebp - 0x14], xmm0
006a1910 call dword ptr [eax + 0x38]
006a1913 movss xmm0, dword ptr [0xb6a614]
006a191b cmp edi, 0x12
006a191e je 0x6a1972
006a1920 movss xmm0, dword ptr [esi + 0x2e0]
006a1928 mov eax, dword ptr [esi]
006a192a addss xmm0, xmm0
006a192e push ecx
006a192f mov ecx, esi
006a1931 minss xmm0, dword ptr [0xb6a7b0]
006a1939 movss dword ptr [esp], xmm0
006a193e call dword ptr [eax + 0x3c]
006a1941 movss xmm0, dword ptr [0xb6a674]
006a1949 cmp edi, 3
006a194c jne 0x6a195a
006a194e or dword ptr [esi + 0x388], 0x200
006a1958 jmp 0x6a1966
006a195a cmp edi, 8
006a195d jne 0x6a1972
006a195f or dword ptr [esi + 0x388], 0x10
006a1966 mov eax, dword ptr [esi + 0x38c]
006a196c mov dword ptr [esi + 0x38c], eax
006a1972 mov ecx, dword ptr [ebp + 0xc]
006a1975 xor eax, eax
006a1977 mulss xmm0, dword ptr [ebp - 0x40]
006a197c and ecx, 0x400000
006a1982 or eax, ecx
006a1984 je 0x6a198e
006a1986 mulss xmm0, dword ptr [0xb6a560]
006a198e ucomiss xmm0, dword ptr [0xb6a614]
006a1995 lahf 
006a1996 test ah, 0x44
006a1999 jnp 0x6a19ab
006a199b mulss xmm0, dword ptr [esi + 0x370]
006a19a3 movss dword ptr [esi + 0x370], xmm0
006a19ab mov ecx, dword ptr [ebp - 8]
006a19ae pop edi
006a19af pop esi
006a19b0 xor ecx, ebp
006a19b2 pop ebx
006a19b3 call 0x9eacd7
006a19b8 mov esp, ebp
006a19ba pop ebp
006a19bb ret 
006a19bc int3 
006a19bd int3 
006a19be int3 
006a19bf int3 
006a19c0 push ebp
006a19c1 mov ebp, esp
006a19c3 and esp, 0xfffffff8
006a19c6 cmp byte ptr [ecx + 0xbb3], 0
006a19cd je 0x6a19d7
006a19cf mov edx, dword ptr [ecx + 0xbb4]
006a19d5 jmp 0x6a19da
006a19d7 or edx, 0xffffffff
006a19da movss xmm1, dword ptr [ecx + 0xb88]
006a19e2 push ecx
006a19e3 push dword ptr [ecx + 0x164]
006a19e9 push dword ptr [ecx + 0x160]
006a19ef mov ecx, dword ptr [ebp + 8]
006a19f2 call 0x6a1750
006a19f7 add esp, 0xc
006a19fa mov esp, ebp
006a19fc pop ebp
006a19fd ret 4
006a1a00 int3 
006a1a01 int3 
006a1a02 int3 
006a1a03 int3 
006a1a04 int3 
006a1a05 int3 
006a1a06 int3 
006a1a07 int3 
006a1a08 int3 
006a1a09 int3 
006a1a0a int3 
006a1a0b int3 
006a1a0c int3 
006a1a0d int3 
006a1a0e int3 
006a1a0f int3 
006a1a10 int3 
006a1a11 int3 
006a1a12 int3 
006a1a13 int3 
006a1a14 int3 
006a1a15 int3 
006a1a16 int3 
006a1a17 int3 
006a1a18 int3 
006a1a19 int3 
006a1a1a int3 
006a1a1b int3 
006a1a1c int3 
006a1a1d int3 
006a1a1e int3 
006a1a1f int3 
