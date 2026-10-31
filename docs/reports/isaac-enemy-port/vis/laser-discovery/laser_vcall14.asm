008d1330 push ebp
008d1331 mov ebp, esp
008d1333 push -1
008d1335 push 0x9ff8a0
008d133a mov eax, dword ptr fs:[0]
008d1340 push eax
008d1341 sub esp, 0x294
008d1347 mov eax, dword ptr [0xbaa3b4]
008d134c xor eax, ebp
008d134e mov dword ptr [ebp - 0x10], eax
008d1351 push esi
008d1352 push edi
008d1353 push eax
008d1354 lea eax, [ebp - 0xc]
008d1357 mov dword ptr fs:[0], eax
008d135d mov esi, ecx
008d135f mov dword ptr [ebp - 0x30], esi
008d1362 cmp byte ptr [esi + 0x169], 0
008d1369 je 0x8d4136
008d136f cmp byte ptr [esi + 0x3ad], 0
008d1376 jl 0x8d4136
008d137c cmp byte ptr [esi + 0x145], 0
008d1383 je 0x8d4136
008d1389 mov eax, dword ptr [0xbfd65c]
008d138e sub esp, 8
008d1391 movss xmm2, dword ptr [esi + 0x2a4]
008d1399 addss xmm2, dword ptr [esi + 0x294]
008d13a1 movss xmm4, dword ptr [0xb6a480]
008d13a9 movss xmm0, dword ptr [eax + 0x1a30f0]
008d13b1 movss xmm3, dword ptr [esi + 0x2a8]
008d13b9 addss xmm3, dword ptr [esi + 0x298]
008d13c1 subss xmm2, dword ptr [0xb6aa8c]
008d13c9 movss xmm1, dword ptr [0xbfec68]
008d13d1 subss xmm1, dword ptr [0xb6ab8c]
008d13d9 movss dword ptr [ebp - 0x68], xmm0
008d13de movss xmm0, dword ptr [eax + 0x1a30f4]
008d13e6 mulss xmm2, dword ptr [0xb6a4dc]
008d13ee subss xmm3, dword ptr [0xb6ab44]
008d13f6 movss dword ptr [ebp - 0x50], xmm0
008d13fb movss xmm0, dword ptr [0xbfec08]
008d1403 subss xmm0, dword ptr [0xb6ac30]
008d140b mulss xmm1, xmm4
008d140f mulss xmm3, dword ptr [0xb6a4dc]
008d1417 mulss xmm0, xmm4
008d141b addss xmm3, xmm1
008d141f addss xmm2, xmm0
008d1423 movss xmm0, dword ptr [0xbaa554]
008d142b mulss xmm0, dword ptr [0xbaa920]
008d1433 movss dword ptr [ebp - 0x3c], xmm3
008d1438 mulss xmm2, xmm0
008d143c movss dword ptr [ebp - 0x28], xmm0
008d1441 addss xmm2, xmm4
008d1445 movss dword ptr [ebp - 0x1c], xmm2
008d144a fld dword ptr [ebp - 0x1c]
008d144d fstp qword ptr [esp]
008d1450 call 0x9ec3b2
008d1455 fstp dword ptr [ebp - 0x1c]
008d1458 movss xmm0, dword ptr [ebp - 0x1c]
008d145d divss xmm0, dword ptr [ebp - 0x28]
008d1462 movss dword ptr [ebp - 0x24], xmm0
008d1467 movss xmm0, dword ptr [ebp - 0x3c]
008d146c mulss xmm0, dword ptr [ebp - 0x28]
008d1471 addss xmm0, dword ptr [0xb6a480]
008d1479 movss dword ptr [ebp - 0x1c], xmm0
008d147e fld dword ptr [ebp - 0x1c]
008d1481 fstp qword ptr [esp]
008d1484 call 0x9ec3b2
008d1489 fstp dword ptr [ebp - 0x1c]
008d148c movss xmm0, dword ptr [ebp - 0x1c]
008d1491 lea edi, [esi + 0x3c]
008d1494 divss xmm0, dword ptr [ebp - 0x28]
008d1499 mov eax, dword ptr [ebp + 8]
008d149c add esp, 8
008d149f mov dword ptr [ebp - 0x20], edi
008d14a2 movss xmm1, dword ptr [ebp - 0x24]
008d14a7 addss xmm1, dword ptr [eax]
008d14ab addss xmm0, dword ptr [eax + 4]
008d14b0 movss dword ptr [esi + 0x19c], xmm1
008d14b8 movss dword ptr [esi + 0x1a0], xmm0
008d14c0 cmp dword ptr [edi + 0x80], 0
008d14c7 jg 0x8d14e5
008d14c9 cmp dword ptr [edi + 0x14], 0x10
008d14cd mov eax, edi
008d14cf jb 0x8d14d3
008d14d1 mov eax, dword ptr [edi]
008d14d3 push 0
008d14d5 push eax
008d14d6 push 0xa0830c
008d14db push 3
008d14dd call 0x95e330
008d14e2 add esp, 0x10
008d14e5 mov ecx, dword ptr [edi + 0x7c]
008d14e8 lea eax, [ebp - 0xac]
008d14ee push eax
008d14ef call 0x403540
008d14f4 mov ecx, dword ptr [eax]
008d14f6 mov dword ptr [ebp - 0x1c], ecx
008d14f9 mov dword ptr [ebp - 4], 0
008d1500 mov ecx, dword ptr [ebp - 0xa8]
008d1506 test ecx, ecx
008d1508 je 0x8d152a
008d150a mov eax, dword ptr [ecx]
008d150c mov eax, dword ptr [eax + 0xc]
008d150f call eax
008d1511 test al, al
008d1513 je 0x8d152a
008d1515 mov eax, dword ptr [0xbfd62c]
008d151a test eax, eax
008d151c je 0x8d152a
008d151e lea ecx, [ebp - 0xac]
008d1524 push ecx
008d1525 call eax
008d1527 add esp, 4
008d152a cmp dword ptr [ebp - 0x1c], 0
008d152e mov dword ptr [ebp - 4], 0xffffffff
008d1535 jne 0x8d154b
008d1537 push 0xb59418
008d153c push 0
008d153e call 0x95e330
008d1543 add esp, 8
008d1546 jmp 0x8d4136
008d154b mov eax, dword ptr [esi + 0x14c]
008d1551 shr eax, 5
008d1554 and eax, 0xffffff01
008d1559 cmp byte ptr [esi + 0x3ad], 0
008d1560 mov dword ptr [ebp - 0xa4], eax
008d1566 mov eax, dword ptr [esi + 0xbc]
008d156c je 0x8d2c9a
008d1572 mov ecx, 1
008d1577 cmp ecx, eax
008d1579 lea ecx, [esi + 0x6c]
008d157c sbb eax, eax
008d157e neg eax
008d1580 push eax
008d1581 mov dword ptr [ebp - 0x94], eax
008d1587 call 0x4053a0
008d158c test eax, eax
008d158e jne 0x8d15a3
008d1590 push 0xb593e4
008d1595 push eax
008d1596 call 0x95e330
008d159b add esp, 8
008d159e jmp 0x8d4136
008d15a3 push eax
008d15a4 lea ecx, [ebp - 0x19c]
008d15aa call 0x4069d0
008d15af push dword ptr [ebp - 0x94]
008d15b5 mov ecx, edi
008d15b7 call 0x4062c0
008d15bc movss xmm1, dword ptr [ebp - 0x184]
008d15c4 mov dword ptr [ebp - 0x7c], 0
008d15cb mov dword ptr [ebp - 0x78], 0
008d15d2 movss xmm0, dword ptr [eax + 0x34]
008d15d7 mulss xmm0, dword ptr [esi + 0xd8]
008d15df mov dword ptr [ebp - 0x74], 0
008d15e6 mulss xmm1, xmm0
008d15ea movss dword ptr [ebp - 0x3c], xmm1
008d15ef mov dword ptr [ebp - 4], 1
008d15f6 lea ecx, [ebp - 0x7c]
008d15f9 mov eax, dword ptr [esi + 0x3d4]
008d15ff sub eax, dword ptr [esi + 0x3d0]
008d1605 sar eax, 3
008d1608 shl eax, 2
008d160b push eax
008d160c call 0x7a7c30
008d1611 cmp dword ptr [edi + 0x80], 0
008d1618 jg 0x8d1636
008d161a cmp dword ptr [edi + 0x14], 0x10
008d161e mov eax, edi
008d1620 jb 0x8d1624
008d1622 mov eax, dword ptr [edi]
008d1624 push 0
008d1626 push eax
008d1627 push 0xa0830c
008d162c push 3
008d162e call 0x95e330
008d1633 add esp, 0x10
008d1636 mov eax, dword ptr [edi + 0x7c]
008d1639 mov dword ptr [eax + 0x28], 0
008d1640 cmp dword ptr [edi + 0x80], 0
008d1647 jg 0x8d1665
008d1649 cmp dword ptr [edi + 0x14], 0x10
008d164d mov eax, edi
008d164f jb 0x8d1653
008d1651 mov eax, dword ptr [edi]
008d1653 push 0
008d1655 push eax
008d1656 push 0xa0830c
008d165b push 3
008d165d call 0x95e330
008d1662 add esp, 0x10
008d1665 mov eax, dword ptr [edi + 0x7c]
008d1668 mov dword ptr [eax + 0x2c], 0
008d166f cmp dword ptr [edi + 0x80], 0
008d1676 jg 0x8d1694
008d1678 cmp dword ptr [edi + 0x14], 0x10
008d167c mov eax, edi
008d167e jb 0x8d1682
008d1680 mov eax, dword ptr [edi]
008d1682 push 0
008d1684 push eax
008d1685 push 0xa0830c
008d168a push 3
008d168c call 0x95e330
008d1691 add esp, 0x10
008d1694 mov ecx, dword ptr [edi + 0x7c]
008d1697 lea eax, [ebp - 0xac]
008d169d push eax
008d169e call 0x403540
008d16a3 mov byte ptr [ebp - 4], 2
008d16a7 xor edx, edx
008d16a9 movss xmm1, dword ptr [esi + 0x2a4]
008d16b1 mulss xmm1, dword ptr [0xb6a4dc]
008d16b9 mov eax, dword ptr [esi + 0x3d4]
008d16bf movss xmm0, dword ptr [ebp - 0x194]
008d16c7 sub eax, dword ptr [esi + 0x3d0]
008d16cd mulss xmm0, dword ptr [0xb6a480]
008d16d5 sar eax, 3
008d16d8 movss dword ptr [ebp - 0xd0], xmm1
008d16e0 movss xmm1, dword ptr [esi + 0x2a8]
008d16e8 mulss xmm1, dword ptr [0xb6a4dc]
008d16f0 mov dword ptr [ebp - 0x90], edx
008d16f6 movss dword ptr [ebp - 0x1c], xmm0
008d16fb movss dword ptr [ebp - 0xa0], xmm1
008d1703 add eax, -1
008d1706 je 0x8d1cca
008d170c xorps xmm0, xmmword ptr [0xb6c9b0]
008d1713 mov eax, dword ptr [ebp - 0x78]
008d1716 mov edi, dword ptr [esi + 0x3d0]
008d171c movss dword ptr [ebp - 0x70], xmm0
008d1721 mov dword ptr [ebp - 0x38], eax
008d1724 nop dword ptr [eax]
008d1728 nop dword ptr [eax + eax]
008d1730 movss xmm3, dword ptr [edi + edx*8 + 8]
008d1736 lea eax, [edx*8]
008d173d movss xmm2, dword ptr [edi + eax + 0xc]
008d1743 subss xmm3, dword ptr [edi + eax]
008d1748 subss xmm2, dword ptr [edi + eax + 4]
008d174e mov dword ptr [ebp - 0x34], eax
008d1751 movaps xmm1, xmm3
008d1754 movss dword ptr [ebp - 0x48], xmm3
008d1759 movaps xmm0, xmm2
008d175c mulss xmm1, xmm3
008d1760 mulss xmm0, xmm2
008d1764 movss dword ptr [ebp - 0x4c], xmm2
008d1769 addss xmm0, xmm1
008d176d call 0x4228c0
008d1772 movss xmm1, dword ptr [ebp - 0x4c]
008d1777 sub esp, 8
008d177a movss xmm2, dword ptr [ebp - 0x48]
008d177f divss xmm1, xmm0
008d1783 mov eax, dword ptr [ebp - 0x34]
008d1786 divss xmm2, xmm0
008d178a movss xmm3, dword ptr [0xb6a480]
008d1792 movaps xmm0, xmm1
008d1795 mulss xmm0, dword ptr [ebp - 0x1c]
008d179a xorps xmm2, xmmword ptr [0xb6c9b0]
008d17a1 movss dword ptr [ebp - 0x4c], xmm1
008d17a6 movaps xmm1, xmm2
008d17a9 mulss xmm0, dword ptr [ebp - 0x3c]
008d17ae mulss xmm1, dword ptr [ebp - 0x1c]
008d17b3 movss dword ptr [ebp - 0x24], xmm0
008d17b8 movss xmm0, dword ptr [0xbfec08]
008d17c0 subss xmm0, dword ptr [0xb6ac30]
008d17c8 mulss xmm1, dword ptr [ebp - 0x3c]
008d17cd movss dword ptr [ebp - 0x48], xmm2
008d17d2 movss xmm2, dword ptr [edi + eax]
008d17d7 subss xmm2, dword ptr [0xb6aa8c]
008d17df mulss xmm0, xmm3
008d17e3 movss dword ptr [ebp - 0x54], xmm1
008d17e8 movss xmm1, dword ptr [0xbfec68]
008d17f0 mulss xmm2, dword ptr [0xb6a4dc]
008d17f8 subss xmm1, dword ptr [0xb6ab8c]
008d1800 addss xmm2, xmm0
008d1804 movss xmm0, dword ptr [edi + eax + 4]
008d180a subss xmm0, dword ptr [0xb6ab44]
008d1812 mulss xmm1, xmm3
008d1816 mulss xmm0, dword ptr [0xb6a4dc]
008d181e addss xmm0, xmm1
008d1822 movss dword ptr [ebp - 0x6c], xmm0
008d1827 movss xmm0, dword ptr [0xbaa554]
008d182f mulss xmm0, dword ptr [0xbaa920]
008d1837 mulss xmm2, xmm0
008d183b movss dword ptr [ebp - 0x28], xmm0
008d1840 addss xmm2, xmm3
008d1844 movss dword ptr [ebp - 0x2c], xmm2
008d1849 fld dword ptr [ebp - 0x2c]
008d184c fstp qword ptr [esp]
008d184f call 0x9ec3b2
008d1854 fstp dword ptr [ebp - 0x2c]
008d1857 movss xmm1, dword ptr [ebp - 0x2c]
008d185c divss xmm1, dword ptr [ebp - 0x28]
008d1861 movss dword ptr [ebp - 0x5c], xmm1
008d1866 movss xmm1, dword ptr [ebp - 0x6c]
008d186b mulss xmm1, dword ptr [ebp - 0x28]
008d1870 addss xmm1, dword ptr [0xb6a480]
008d1878 movss dword ptr [ebp - 0x2c], xmm1
008d187d fld dword ptr [ebp - 0x2c]
008d1880 fstp qword ptr [esp]
008d1883 call 0x9ec3b2
008d1888 fstp dword ptr [ebp - 0x2c]
008d188b movss xmm1, dword ptr [ebp - 0x2c]
008d1890 add esp, 8
008d1893 divss xmm1, dword ptr [ebp - 0x28]
008d1898 mov eax, dword ptr [ebp - 0x38]
008d189b movss xmm0, dword ptr [ebp - 0x5c]
008d18a0 addss xmm0, dword ptr [ebp - 0x24]
008d18a5 addss xmm1, dword ptr [ebp - 0x54]
008d18aa movss dword ptr [ebp - 0x18], xmm0
008d18af movss dword ptr [ebp - 0x14], xmm1
008d18b4 cmp eax, dword ptr [ebp - 0x74]
008d18b7 je 0x8d18ca
008d18b9 movss dword ptr [eax], xmm0
008d18bd movss dword ptr [eax + 4], xmm1
008d18c2 add eax, 8
008d18c5 mov dword ptr [ebp - 0x78], eax
008d18c8 jmp 0x8d18da
008d18ca lea ecx, [ebp - 0x18]
008d18cd push ecx
008d18ce push eax
008d18cf lea ecx, [ebp - 0x7c]
008d18d2 call 0x422130
008d18d7 mov eax, dword ptr [ebp - 0x78]
008d18da movss xmm0, dword ptr [ebp - 0x4c]
008d18df sub esp, 8
008d18e2 mulss xmm0, dword ptr [ebp - 0x70]
008d18e7 mov dword ptr [ebp - 0x38], eax
008d18ea mov eax, dword ptr [esi + 0x3d0]
008d18f0 add eax, dword ptr [ebp - 0x34]
008d18f3 mulss xmm0, dword ptr [ebp - 0x3c]
008d18f8 movss xmm1, dword ptr [ebp - 0x48]
008d18fd mulss xmm1, dword ptr [ebp - 0x70]
008d1902 movss xmm2, dword ptr [eax]
008d1906 subss xmm2, dword ptr [0xb6aa8c]
008d190e movss xmm3, dword ptr [0xb6a480]
008d1916 mulss xmm1, dword ptr [ebp - 0x3c]
008d191b movss dword ptr [ebp - 0x4c], xmm0
008d1920 movss xmm0, dword ptr [0xbfec08]
008d1928 subss xmm0, dword ptr [0xb6ac30]
008d1930 mulss xmm2, dword ptr [0xb6a4dc]
008d1938 movss dword ptr [ebp - 0x48], xmm1
008d193d movss xmm1, dword ptr [0xbfec68]
008d1945 subss xmm1, dword ptr [0xb6ab8c]
008d194d mulss xmm0, xmm3
008d1951 addss xmm2, xmm0
008d1955 mulss xmm1, xmm3
008d1959 movss xmm0, dword ptr [eax + 4]
008d195e subss xmm0, dword ptr [0xb6ab44]
008d1966 mulss xmm0, dword ptr [0xb6a4dc]
008d196e addss xmm0, xmm1
008d1972 movss dword ptr [ebp - 0x6c], xmm0
008d1977 movss xmm0, dword ptr [0xbaa554]
008d197f mulss xmm0, dword ptr [0xbaa920]
008d1987 mulss xmm2, xmm0
008d198b movss dword ptr [ebp - 0x28], xmm0
008d1990 addss xmm2, xmm3
008d1994 movss dword ptr [ebp - 0x2c], xmm2
008d1999 fld dword ptr [ebp - 0x2c]
008d199c fstp qword ptr [esp]
008d199f call 0x9ec3b2
008d19a4 fstp dword ptr [ebp - 0x2c]
008d19a7 movss xmm0, dword ptr [ebp - 0x2c]
008d19ac divss xmm0, dword ptr [ebp - 0x28]
008d19b1 movss dword ptr [ebp - 0x5c], xmm0
008d19b6 movss xmm0, dword ptr [ebp - 0x6c]
008d19bb mulss xmm0, dword ptr [ebp - 0x28]
008d19c0 addss xmm0, dword ptr [0xb6a480]
008d19c8 movss dword ptr [ebp - 0x2c], xmm0
008d19cd fld dword ptr [ebp - 0x2c]
008d19d0 fstp qword ptr [esp]
008d19d3 call 0x9ec3b2
008d19d8 fstp dword ptr [ebp - 0x2c]
008d19db movss xmm2, dword ptr [ebp - 0x2c]
008d19e0 add esp, 8
008d19e3 divss xmm2, dword ptr [ebp - 0x28]
008d19e8 mov eax, dword ptr [ebp - 0x38]
008d19eb movss xmm0, dword ptr [ebp - 0x5c]
008d19f0 addss xmm0, dword ptr [ebp - 0x4c]
008d19f5 addss xmm2, dword ptr [ebp - 0x48]
008d19fa movss dword ptr [ebp - 0x9c], xmm0
008d1a02 movss dword ptr [ebp - 0x98], xmm2
008d1a0a cmp eax, dword ptr [ebp - 0x74]
008d1a0d je 0x8d1a20
008d1a0f movss dword ptr [eax], xmm0
008d1a13 movss dword ptr [eax + 4], xmm2
008d1a18 add eax, 8
008d1a1b mov dword ptr [ebp - 0x78], eax
008d1a1e jmp 0x8d1a33
008d1a20 lea ecx, [ebp - 0x9c]
008d1a26 push ecx
008d1a27 push eax
008d1a28 lea ecx, [ebp - 0x7c]
008d1a2b call 0x422130
008d1a30 mov eax, dword ptr [ebp - 0x78]
008d1a33 mov ecx, dword ptr [ebp - 0x34]
008d1a36 sub esp, 8
008d1a39 movss xmm0, dword ptr [0xbfec08]
008d1a41 subss xmm0, dword ptr [0xb6ac30]
008d1a49 movss xmm3, dword ptr [0xb6a480]
008d1a51 movss xmm1, dword ptr [0xbfec68]
008d1a59 subss xmm1, dword ptr [0xb6ab8c]
008d1a61 mov dword ptr [ebp - 0x38], eax
008d1a64 mov eax, dword ptr [esi + 0x3d0]
008d1a6a mulss xmm0, xmm3
008d1a6e mulss xmm1, xmm3
008d1a72 movss xmm2, dword ptr [eax + ecx + 8]
008d1a78 subss xmm2, dword ptr [0xb6aa8c]
008d1a80 mulss xmm2, dword ptr [0xb6a4dc]
008d1a88 addss xmm2, xmm0
008d1a8c movss xmm0, dword ptr [eax + ecx + 0xc]
008d1a92 subss xmm0, dword ptr [0xb6ab44]
008d1a9a mulss xmm0, dword ptr [0xb6a4dc]
008d1aa2 addss xmm0, xmm1
008d1aa6 movss dword ptr [ebp - 0x6c], xmm0
008d1aab movss xmm0, dword ptr [0xbaa554]
008d1ab3 mulss xmm0, dword ptr [0xbaa920]
008d1abb mulss xmm2, xmm0
008d1abf movss dword ptr [ebp - 0x28], xmm0
008d1ac4 addss xmm2, xmm3
008d1ac8 movss dword ptr [ebp - 0x2c], xmm2
008d1acd fld dword ptr [ebp - 0x2c]
008d1ad0 fstp qword ptr [esp]
008d1ad3 call 0x9ec3b2
008d1ad8 fstp dword ptr [ebp - 0x2c]
008d1adb movss xmm0, dword ptr [ebp - 0x2c]
008d1ae0 divss xmm0, dword ptr [ebp - 0x28]
008d1ae5 movss dword ptr [ebp - 0x5c], xmm0
008d1aea movss xmm0, dword ptr [ebp - 0x6c]
008d1aef mulss xmm0, dword ptr [ebp - 0x28]
008d1af4 addss xmm0, dword ptr [0xb6a480]
008d1afc movss dword ptr [ebp - 0x2c], xmm0
008d1b01 fld dword ptr [ebp - 0x2c]
008d1b04 fstp qword ptr [esp]
008d1b07 call 0x9ec3b2
008d1b0c fstp dword ptr [ebp - 0x2c]
008d1b0f movss xmm1, dword ptr [ebp - 0x2c]
008d1b14 add esp, 8
008d1b17 divss xmm1, dword ptr [ebp - 0x28]
008d1b1c mov eax, dword ptr [ebp - 0x38]
008d1b1f movss xmm0, dword ptr [ebp - 0x24]
008d1b24 addss xmm0, dword ptr [ebp - 0x5c]
008d1b29 addss xmm1, dword ptr [ebp - 0x54]
008d1b2e movss dword ptr [ebp - 0xd8], xmm0
008d1b36 movss dword ptr [ebp - 0xd4], xmm1
008d1b3e cmp eax, dword ptr [ebp - 0x74]
008d1b41 je 0x8d1b54
008d1b43 movss dword ptr [eax], xmm0
008d1b47 movss dword ptr [eax + 4], xmm1
008d1b4c add eax, 8
008d1b4f mov dword ptr [ebp - 0x78], eax
008d1b52 jmp 0x8d1b67
008d1b54 lea ecx, [ebp - 0xd8]
008d1b5a push ecx
008d1b5b push eax
008d1b5c lea ecx, [ebp - 0x7c]
008d1b5f call 0x422130
008d1b64 mov eax, dword ptr [ebp - 0x78]
008d1b67 mov ecx, dword ptr [ebp - 0x34]
008d1b6a sub esp, 8
008d1b6d movss xmm0, dword ptr [0xbfec08]
008d1b75 subss xmm0, dword ptr [0xb6ac30]
008d1b7d movss xmm3, dword ptr [0xb6a480]
008d1b85 movss xmm1, dword ptr [0xbfec68]
008d1b8d subss xmm1, dword ptr [0xb6ab8c]
008d1b95 mov dword ptr [ebp - 0x38], eax
008d1b98 mov eax, dword ptr [esi + 0x3d0]
008d1b9e mulss xmm0, xmm3
008d1ba2 mulss xmm1, xmm3
008d1ba6 movss xmm2, dword ptr [eax + ecx + 8]
008d1bac subss xmm2, dword ptr [0xb6aa8c]
008d1bb4 mulss xmm2, dword ptr [0xb6a4dc]
008d1bbc addss xmm2, xmm0
008d1bc0 movss xmm0, dword ptr [eax + ecx + 0xc]
008d1bc6 subss xmm0, dword ptr [0xb6ab44]
008d1bce mulss xmm0, dword ptr [0xb6a4dc]
008d1bd6 addss xmm0, xmm1
008d1bda movss dword ptr [ebp - 0x34], xmm0
008d1bdf movss xmm0, dword ptr [0xbaa554]
008d1be7 mulss xmm0, dword ptr [0xbaa920]
008d1bef mulss xmm2, xmm0
008d1bf3 movss dword ptr [ebp - 0x28], xmm0
008d1bf8 addss xmm2, xmm3
008d1bfc movss dword ptr [ebp - 0x24], xmm2
008d1c01 fld dword ptr [ebp - 0x24]
008d1c04 fstp qword ptr [esp]
008d1c07 call 0x9ec3b2
008d1c0c fstp dword ptr [ebp - 0x24]
008d1c0f movss xmm0, dword ptr [ebp - 0x24]
008d1c14 divss xmm0, dword ptr [ebp - 0x28]
008d1c19 movss dword ptr [ebp - 0x54], xmm0
008d1c1e movss xmm0, dword ptr [ebp - 0x34]
008d1c23 mulss xmm0, dword ptr [ebp - 0x28]
008d1c28 addss xmm0, dword ptr [0xb6a480]
008d1c30 movss dword ptr [ebp - 0x24], xmm0
008d1c35 fld dword ptr [ebp - 0x24]
008d1c38 fstp qword ptr [esp]
008d1c3b call 0x9ec3b2
008d1c40 fstp dword ptr [ebp - 0x24]
008d1c43 movss xmm1, dword ptr [ebp - 0x24]
008d1c48 add esp, 8
008d1c4b divss xmm1, dword ptr [ebp - 0x28]
008d1c50 mov ecx, dword ptr [ebp - 0x38]
008d1c53 movss xmm0, dword ptr [ebp - 0x4c]
008d1c58 addss xmm0, dword ptr [ebp - 0x54]
008d1c5d addss xmm1, dword ptr [ebp - 0x48]
008d1c62 movss dword ptr [ebp - 0x8c], xmm0
008d1c6a movss dword ptr [ebp - 0x88], xmm1
008d1c72 cmp ecx, dword ptr [ebp - 0x74]
008d1c75 je 0x8d1c88
008d1c77 movss dword ptr [ecx], xmm0
008d1c7b movss dword ptr [ecx + 4], xmm1
008d1c80 add ecx, 8
008d1c83 mov dword ptr [ebp - 0x78], ecx
008d1c86 jmp 0x8d1c9b
008d1c88 lea eax, [ebp - 0x8c]
008d1c8e push eax
008d1c8f push ecx
008d1c90 lea ecx, [ebp - 0x7c]
008d1c93 call 0x422130
008d1c98 mov ecx, dword ptr [ebp - 0x78]
008d1c9b mov eax, dword ptr [esi + 0x3d4]
008d1ca1 mov edi, dword ptr [esi + 0x3d0]
008d1ca7 sub eax, edi
008d1ca9 mov edx, dword ptr [ebp - 0x90]
008d1caf sar eax, 3
008d1cb2 inc edx
008d1cb3 dec eax
008d1cb4 mov dword ptr [ebp - 0x38], ecx
008d1cb7 mov dword ptr [ebp - 0x90], edx
008d1cbd cmp edx, eax
008d1cbf jb 0x8d1730
008d1cc5 lea edi, [esi + 0x3c]
008d1cc8 jmp 0x8d1cd0
008d1cca mov ecx, dword ptr [ebp - 0x78]
008d1ccd mov dword ptr [ebp - 0x38], ecx
008d1cd0 mov eax, dword ptr [esi + 0x30]
008d1cd3 cmp eax, 1
008d1cd6 je 0x8d1ce2
008d1cd8 cmp eax, 2
008d1cdb je 0x8d1ce2
008d1cdd cmp eax, 3
008d1ce0 jne 0x8d1d21
008d1ce2 push ecx
008d1ce3 lea eax, [ecx - 0x10]
008d1ce6 push eax
008d1ce7 lea eax, [ebp - 0x14]
008d1cea push eax
008d1ceb lea ecx, [ebp - 0x7c]
008d1cee call 0x8d8580
008d1cf3 mov ecx, dword ptr [ebp - 0x7c]
008d1cf6 push dword ptr [ebp - 0x14]
008d1cf9 lea eax, [ecx + 0x10]
008d1cfc push eax
008d1cfd push ecx
008d1cfe push dword ptr [ebp - 0x78]
008d1d01 lea ecx, [ebp - 0x7c]
008d1d04 call 0x8d85d0
008d1d09 mov eax, dword ptr [esi + 0x30]
008d1d0c cmp eax, 1
008d1d0f je 0x8d1d2b
008d1d11 cmp eax, 2
008d1d14 je 0x8d1d2b
008d1d16 cmp eax, 3
008d1d19 je 0x8d1d2b
008d1d1b mov eax, dword ptr [ebp - 0x78]
008d1d1e mov dword ptr [ebp - 0x38], eax
008d1d21 xorps xmm1, xmm1
008d1d24 movss dword ptr [ebp - 0x4c], xmm1
008d1d29 jmp 0x8d1d5d
008d1d2b mov eax, dword ptr [0xbfd65c]
008d1d30 xorps xmm1, xmm1
008d1d33 mov eax, dword ptr [eax + 0x1a30dc]
008d1d39 sub eax, dword ptr [esi + 0x280]
008d1d3f movd xmm0, eax
008d1d43 mov eax, dword ptr [ebp - 0x78]
008d1d46 cvtdq2ps xmm0, xmm0
008d1d49 mov dword ptr [ebp - 0x38], eax
008d1d4c mulss xmm0, dword ptr [0xb6a8f4]
008d1d54 addss xmm0, xmm1
008d1d58 movss dword ptr [ebp - 0x4c], xmm0
008d1d5d push dword ptr [ebp - 0x94]
008d1d63 mov ecx, edi
008d1d65 call 0x4062c0
008d1d6a xor ecx, ecx
008d1d6c cmp byte ptr [ebp - 0xa4], cl
008d1d72 push ecx
008d1d73 movups xmm1, xmmword ptr [eax + 0x78]
008d1d77 mov eax, 0x3c
008d1d7c cmove eax, ecx
008d1d7f mov ecx, dword ptr [ebp - 0xac]
008d1d85 movaps xmm0, xmm1
008d1d88 movd dword ptr [0xbc7a34], xmm1
008d1d90 psrldq xmm0, 4
008d1d95 movd dword ptr [0xbc7a38], xmm0
008d1d9d movaps xmm0, xmm1
008d1da0 psrldq xmm0, 8
008d1da5 psrldq xmm1, 0xc
008d1daa mov dword ptr [ebp - 0x14], eax
008d1dad mov eax, dword ptr [eax + 0xa08910]
008d1db3 movd dword ptr [0xbc7a3c], xmm0
008d1dbb movd dword ptr [0xbc7a40], xmm1
008d1dc3 mov dword ptr [0xbc7a44], eax
008d1dc8 call 0x95f690
008d1dcd mov eax, dword ptr [ebp - 0x38]
008d1dd0 mov edx, dword ptr [ebp - 0x7c]
008d1dd3 sub eax, edx
008d1dd5 mov dword ptr [ebp - 0x38], eax
008d1dd8 test al, 0x18
008d1dda je 0x8d1df1
008d1ddc push 0xb593bc
008d1de1 push 3
008d1de3 call 0x95e330
008d1de8 mov eax, dword ptr [ebp - 0x38]
008d1deb add esp, 8
008d1dee mov edx, dword ptr [ebp - 0x7c]
008d1df1 sar eax, 3
008d1df4 xor ecx, ecx
008d1df6 mov dword ptr [ebp - 0x1c], ecx
008d1df9 mov dword ptr [ebp - 0x38], eax
008d1dfc test eax, eax
008d1dfe je 0x8d261f
008d1e04 movss xmm0, dword ptr [ebp - 0x19c]
008d1e0c lea esi, [edx + 0x2c]
008d1e0f addss xmm0, dword ptr [ebp - 0x194]
008d1e17 mov edi, dword ptr [ebp - 0x30]
008d1e1a movss dword ptr [ebp - 0x98], xmm0
008d1e22 movss xmm2, dword ptr [0xb6a480]
008d1e2a add eax, -4
008d1e2d cmp ecx, eax
008d1e2f jae 0x8d1e7c
008d1e31 movss xmm1, dword ptr [esi - 0xc]
008d1e36 addss xmm1, dword ptr [esi - 0x1c]
008d1e3b movss xmm0, dword ptr [esi - 8]
008d1e40 addss xmm0, dword ptr [esi - 0x18]
008d1e45 mulss xmm1, xmm2
008d1e49 mulss xmm0, xmm2
008d1e4d movss dword ptr [esi - 0x1c], xmm1
008d1e52 movss dword ptr [esi - 0x18], xmm0
008d1e57 movss xmm1, dword ptr [esi - 4]
008d1e5c movss xmm0, dword ptr [esi - 0x10]
008d1e61 addss xmm1, dword ptr [esi - 0x14]
008d1e66 addss xmm0, dword ptr [esi]
008d1e6a mulss xmm1, xmm2
008d1e6e mulss xmm0, xmm2
008d1e72 movss dword ptr [esi - 0x14], xmm1
008d1e77 movss dword ptr [esi - 0x10], xmm0
008d1e7c test ecx, ecx
008d1e7e je 0x8d1e9e
008d1e80 mov eax, dword ptr [esi - 0x3c]
008d1e83 mov dword ptr [esi - 0x2c], eax
008d1e86 mov eax, dword ptr [esi - 0x38]
008d1e89 mov dword ptr [esi - 0x28], eax
008d1e8c movss xmm0, dword ptr [esi - 0x34]
008d1e91 movss dword ptr [esi - 0x24], xmm0
008d1e96 mov eax, dword ptr [esi - 0x30]
008d1e99 mov dword ptr [esi - 0x20], eax
008d1e9c jmp 0x8d1ea3
008d1e9e movss xmm0, dword ptr [esi - 0x24]
008d1ea3 movss xmm1, dword ptr [esi - 0x2c]
008d1ea8 movaps xmm3, xmm1
008d1eab movss dword ptr [ebp - 0x2c], xmm1
008d1eb0 movss xmm1, dword ptr [esi - 0x28]
008d1eb5 addss xmm3, xmm0
008d1eb9 movss dword ptr [ebp - 0x6c], xmm0
008d1ebe movaps xmm4, xmm1
008d1ec1 movss xmm0, dword ptr [esi - 0x20]
008d1ec6 addss xmm4, xmm0
008d1eca movss dword ptr [ebp - 0x34], xmm0
008d1ecf movss xmm0, dword ptr [esi - 0x14]
008d1ed4 movaps xmm5, xmm0
008d1ed7 movss dword ptr [ebp - 0x84], xmm1
008d1edf movss xmm1, dword ptr [esi - 0x1c]
008d1ee4 addss xmm5, xmm1
008d1ee8 movss dword ptr [ebp - 0x70], xmm1
008d1eed movss xmm1, dword ptr [esi - 0x10]
008d1ef2 movss dword ptr [ebp - 0x90], xmm0
008d1efa movaps xmm6, xmm1
008d1efd movss xmm0, dword ptr [esi - 0x18]
008d1f02 addss xmm6, xmm0
008d1f06 mulss xmm3, xmm2
008d1f0a mulss xmm5, xmm2
008d1f0e mulss xmm4, xmm2
008d1f12 mulss xmm6, xmm2
008d1f16 movss dword ptr [ebp - 0x48], xmm0
008d1f1b movss dword ptr [ebp - 0x54], xmm1
008d1f20 movaps xmm1, xmm5
008d1f23 movaps xmm0, xmm6
008d1f26 movss dword ptr [ebp - 0x3c], xmm3
008d1f2b subss xmm0, xmm4
008d1f2f movss dword ptr [ebp - 0x94], xmm4
008d1f37 subss xmm1, xmm3
008d1f3b movss dword ptr [ebp - 0x24], xmm5
008d1f40 movss dword ptr [ebp - 0x5c], xmm6
008d1f45 mulss xmm0, xmm0
008d1f49 mulss xmm1, xmm1
008d1f4d addss xmm0, xmm1
008d1f51 call 0x4228c0
008d1f56 push 0xbc4bc0
008d1f5b lea edx, [edi + 0x378]
008d1f61 movss dword ptr [ebp - 0x28], xmm0
008d1f66 lea ecx, [ebp - 0x224]
008d1f6c call 0x412050
008d1f71 add esp, 4
008d1f74 mov ecx, dword ptr [eax]
008d1f76 or ecx, dword ptr [eax + 4]
008d1f79 jne 0x8d1f87
008d1f7b mov ecx, dword ptr [eax + 8]
008d1f7e or ecx, dword ptr [eax + 0xc]
008d1f81 je 0x8d20ff
008d1f87 mov eax, dword ptr [edi + 0x30]
008d1f8a cmp eax, 1
008d1f8d je 0x8d20ff
008d1f93 cmp eax, 2
008d1f96 je 0x8d20ff
008d1f9c movss xmm4, dword ptr [0xb6a614]
008d1fa4 movss xmm7, dword ptr [ebp - 0x2c]
008d1fa9 movss xmm5, dword ptr [ebp - 0x84]
008d1fb1 movss xmm6, dword ptr [ebp - 0x6c]
008d1fb6 cmp eax, 3
008d1fb9 je 0x8d2119
008d1fbf movss xmm0, dword ptr [ebp - 0x4c]
008d1fc4 lea ecx, [ebp - 0xd4]
008d1fca divss xmm0, dword ptr [0xb6accc]
008d1fd2 lea eax, [ebp - 0x88]
008d1fd8 mov dword ptr [ebp - 0xd4], 0x3f800000
008d1fe2 movss xmm2, dword ptr [ebp - 0x3c]
008d1fe7 movss xmm3, dword ptr [ebp - 0x94]
008d1fef subss xmm7, xmm2
008d1ff3 movss xmm1, dword ptr [ebp - 0x34]
008d1ff8 subss xmm6, xmm2
008d1ffc comiss xmm4, xmm0
008d1fff movss dword ptr [ebp - 0x88], xmm0
008d2007 subss xmm1, xmm3
008d200b subss xmm5, xmm3
008d200f cmovbe eax, ecx
008d2012 lea ecx, [ebp - 0x88]
008d2018 movss xmm0, dword ptr [eax]
008d201c lea eax, [ebp - 0xd4]
008d2022 mulss xmm0, dword ptr [0xb6a6f0]
008d202a mov dword ptr [ebp - 0x88], 0x3f800000
008d2034 addss xmm0, xmm4
008d2038 mulss xmm1, xmm0
008d203c mulss xmm7, xmm0
008d2040 mulss xmm5, xmm0
008d2044 addss xmm1, xmm3
008d2048 mulss xmm6, xmm0
008d204c addss xmm7, xmm2
008d2050 movss xmm0, dword ptr [ebp - 0x28]
008d2055 addss xmm5, xmm3
008d2059 addss xmm0, dword ptr [ebp - 0x4c]
008d205e movss xmm3, dword ptr [ebp - 0x70]
008d2063 addss xmm6, xmm2
008d2067 movss xmm2, dword ptr [ebp - 0x24]
008d206c movss dword ptr [ebp - 0x34], xmm1
008d2071 subss xmm3, xmm2
008d2075 movss xmm1, dword ptr [ebp - 0x48]
008d207a divss xmm0, dword ptr [0xb6accc]
008d2082 subss xmm1, dword ptr [ebp - 0x5c]
008d2087 comiss xmm4, xmm0
008d208a movss dword ptr [ebp - 0xd4], xmm0
008d2092 movss dword ptr [ebp - 0x84], xmm5
008d209a cmovbe eax, ecx
008d209d movss xmm0, dword ptr [eax]
008d20a1 mulss xmm0, dword ptr [0xb6a6f0]
008d20a9 addss xmm0, xmm4
008d20ad mulss xmm1, xmm0
008d20b1 mulss xmm3, xmm0
008d20b5 addss xmm1, dword ptr [ebp - 0x5c]
008d20ba addss xmm3, xmm2
008d20be movss dword ptr [ebp - 0x48], xmm1
008d20c3 movss xmm1, dword ptr [ebp - 0x90]
008d20cb subss xmm1, xmm2
008d20cf movss dword ptr [ebp - 0x70], xmm3
008d20d4 movss xmm2, dword ptr [ebp - 0x54]
008d20d9 subss xmm2, dword ptr [ebp - 0x5c]
008d20de mulss xmm1, xmm0
008d20e2 mulss xmm2, xmm0
008d20e6 addss xmm1, dword ptr [ebp - 0x24]
008d20eb addss xmm2, dword ptr [ebp - 0x5c]
008d20f0 movss dword ptr [ebp - 0x90], xmm1
008d20f8 movss dword ptr [ebp - 0x54], xmm2
008d20fd jmp 0x8d211e
008d20ff movss xmm4, dword ptr [0xb6a614]
008d2107 movss xmm6, dword ptr [ebp - 0x6c]
008d210c movss xmm7, dword ptr [ebp - 0x2c]
008d2111 movss xmm5, dword ptr [ebp - 0x84]
008d2119 movss xmm3, dword ptr [ebp - 0x70]
008d211e push 0xbc4c60
008d2123 lea edx, [edi + 0x378]
008d2129 lea ecx, [ebp - 0x234]
008d212f call 0x412050
008d2134 add esp, 4
008d2137 mov ecx, dword ptr [eax]
008d2139 or ecx, dword ptr [eax + 4]
008d213c jne 0x8d214a
008d213e mov ecx, dword ptr [eax + 8]
008d2141 or ecx, dword ptr [eax + 0xc]
008d2144 je 0x8d22dc
008d214a mov eax, dword ptr [edi + 0x30]
008d214d cmp eax, 1
008d2150 je 0x8d22dc
008d2156 cmp eax, 2
008d2159 je 0x8d22dc
008d215f cmp eax, 3
008d2162 je 0x8d22dc
008d2168 movss xmm0, dword ptr [ebp - 0x4c]
008d216d lea ecx, [ebp - 0x88]
008d2173 divss xmm0, dword ptr [0xb6ac14]
008d217b lea eax, [ebp - 0xd4]
008d2181 mov dword ptr [ebp - 0x88], 0x3f800000
008d218b subss xmm5, dword ptr [ebp - 0x94]
008d2193 comiss xmm4, xmm0
008d2196 subss xmm7, dword ptr [ebp - 0x3c]
008d219b movss dword ptr [ebp - 0xd4], xmm0
008d21a3 movaps xmm2, xmm4
008d21a6 cmovbe eax, ecx
008d21a9 movss xmm3, dword ptr [ebp - 0x48]
008d21ae subss xmm3, dword ptr [ebp - 0x5c]
008d21b3 lea ecx, [ebp - 0x88]
008d21b9 movss xmm0, dword ptr [eax]
008d21bd lea eax, [ebp - 0xd4]
008d21c3 mulss xmm0, dword ptr [0xb6a480]
008d21cb mov dword ptr [ebp - 0x88], 0x3f800000
008d21d5 subss xmm2, xmm0
008d21d9 movaps xmm0, xmm2
008d21dc movaps xmm1, xmm2
008d21df mulss xmm0, xmm7
008d21e3 mulss xmm1, xmm5
008d21e7 movss xmm5, dword ptr [ebp - 0x3c]
008d21ec movaps xmm7, xmm5
008d21ef subss xmm6, xmm5
008d21f3 addss xmm7, xmm0
008d21f7 movss xmm0, dword ptr [ebp - 0x94]
008d21ff addss xmm0, xmm1
008d2203 movss xmm1, dword ptr [ebp - 0x34]
008d2208 subss xmm1, dword ptr [ebp - 0x94]
008d2210 movss dword ptr [ebp - 0x84], xmm0
008d2218 movaps xmm0, xmm2
008d221b mulss xmm0, xmm6
008d221f movaps xmm6, xmm5
008d2222 mulss xmm2, xmm1
008d2226 addss xmm6, xmm0
008d222a movss xmm5, dword ptr [ebp - 0x24]
008d222f movss xmm0, dword ptr [ebp - 0x94]
008d2237 addss xmm0, xmm2
008d223b movss xmm1, dword ptr [ebp - 0x70]
008d2240 movaps xmm2, xmm4
008d2243 subss xmm1, xmm5
008d2247 movss dword ptr [ebp - 0x34], xmm0
008d224c movss xmm0, dword ptr [ebp - 0x28]
008d2251 addss xmm0, dword ptr [ebp - 0x4c]
008d2256 divss xmm0, dword ptr [0xb6ac14]
008d225e comiss xmm4, xmm0
008d2261 movss xmm4, dword ptr [ebp - 0x5c]
008d2266 movss dword ptr [ebp - 0xd4], xmm0
008d226e cmovbe eax, ecx
008d2271 movss xmm0, dword ptr [eax]
008d2275 mulss xmm0, dword ptr [0xb6a480]
008d227d subss xmm2, xmm0
008d2281 movaps xmm0, xmm2
008d2284 mulss xmm0, xmm1
008d2288 movaps xmm1, xmm2
008d228b mulss xmm1, xmm3
008d228f movaps xmm3, xmm5
008d2292 addss xmm3, xmm0
008d2296 movaps xmm0, xmm2
008d2299 addss xmm4, xmm1
008d229d movss xmm1, dword ptr [ebp - 0x90]
008d22a5 subss xmm1, xmm5
008d22a9 movss xmm5, dword ptr [ebp - 0x54]
008d22ae subss xmm5, dword ptr [ebp - 0x5c]
008d22b3 mulss xmm0, xmm1
008d22b7 movss xmm1, dword ptr [ebp - 0x24]
008d22bc mulss xmm2, xmm5
008d22c0 addss xmm1, xmm0
008d22c4 movss xmm0, dword ptr [ebp - 0x5c]
008d22c9 addss xmm0, xmm2
008d22cd movss dword ptr [ebp - 0x90], xmm1
008d22d5 movss dword ptr [ebp - 0x54], xmm0
008d22da jmp 0x8d22e1
008d22dc movss xmm4, dword ptr [ebp - 0x48]
008d22e1 cmp byte ptr [edi + 0x13c], 0
008d22e8 movss xmm0, dword ptr [ebp - 0x4c]
008d22ed movss xmm1, dword ptr [ebp - 0x28]
008d22f2 movss xmm5, dword ptr [ebp - 0x19c]
008d22fa addss xmm1, xmm0
008d22fe movss xmm2, dword ptr [ebp - 0x98]
008d2306 movss dword ptr [ebp - 0xf4], xmm5
008d230e movss dword ptr [ebp - 0x104], xmm5
008d2316 movss dword ptr [ebp - 0xec], xmm2
008d231e movss dword ptr [ebp - 0xfc], xmm2
008d2326 movss dword ptr [ebp - 0xf8], xmm0
008d232e movss dword ptr [ebp - 0x100], xmm0
008d2336 movss dword ptr [ebp - 0xe8], xmm1
008d233e movss dword ptr [ebp - 0xf0], xmm1
008d2346 mov dword ptr [ebp - 0xe4], 0
008d2350 je 0x8d2372
008d2352 movss dword ptr [ebp - 0x104], xmm2
008d235a movss dword ptr [ebp - 0xfc], xmm5
008d2362 movss dword ptr [ebp - 0xf4], xmm2
008d236a movss dword ptr [ebp - 0xec], xmm5
008d2372 movss xmm0, dword ptr [ebp - 0xd0]
008d237a lea ecx, [ebp - 0x1bc]
008d2380 mov eax, dword ptr [ebp + 8]
008d2383 addss xmm0, xmm3
008d2387 movss xmm3, dword ptr [ebp - 0xa0]
008d238f addss xmm3, xmm4
008d2393 movss dword ptr [ebp - 0x4c], xmm1
008d2398 movss xmm1, dword ptr [ebp - 0x68]
008d239d movss xmm4, dword ptr [eax + 4]
008d23a2 movss xmm5, dword ptr [eax]
008d23a6 lea eax, [ebp - 0xc4]
008d23ac movaps xmm2, xmm5
008d23af addss xmm2, xmm0
008d23b3 movss xmm0, dword ptr [ebp - 0x50]
008d23b8 addss xmm3, xmm4
008d23bc push eax
008d23bd lea eax, [ebp - 0xcc]
008d23c3 push eax
008d23c4 addss xmm1, xmm2
008d23c8 movss xmm2, dword ptr [ebp - 0x68]
008d23cd addss xmm0, xmm3
008d23d1 movss xmm3, dword ptr [ebp - 0xa0]
008d23d9 addss xmm3, dword ptr [ebp - 0x54]
008d23de lea eax, [ebp - 0x64]
008d23e1 push eax
008d23e2 movss dword ptr [ebp - 0xc4], xmm1
008d23ea lea eax, [ebp - 0x44]
008d23ed movss dword ptr [ebp - 0xc0], xmm0
008d23f5 movaps xmm1, xmm5
008d23f8 movss xmm0, dword ptr [ebp - 0xd0]
008d2400 addss xmm3, xmm4
008d2404 addss xmm0, dword ptr [ebp - 0x90]
008d240c push eax
008d240d addss xmm1, xmm0
008d2411 movss xmm0, dword ptr [ebp - 0x50]
008d2416 addss xmm0, xmm3
008d241a movss xmm3, dword ptr [ebp - 0xa0]
008d2422 addss xmm3, dword ptr [ebp - 0x84]
008d242a addss xmm2, xmm1
008d242e movaps xmm1, xmm5
008d2431 movss dword ptr [ebp - 0xc8], xmm0
008d2439 movss xmm0, dword ptr [ebp - 0xd0]
008d2441 addss xmm3, xmm4
008d2445 addss xmm0, xmm7
008d2449 movss dword ptr [ebp - 0xcc], xmm2
008d2451 movss xmm2, dword ptr [ebp - 0x68]
008d2456 addss xmm1, xmm0
008d245a movss xmm0, dword ptr [ebp - 0x50]
008d245f addss xmm0, xmm3
008d2463 addss xmm2, xmm1
008d2467 movss xmm1, dword ptr [ebp - 0x68]
008d246c movss dword ptr [ebp - 0x60], xmm0
008d2471 movss xmm0, dword ptr [ebp - 0xd0]
008d2479 addss xmm0, xmm6
008d247d movss dword ptr [ebp - 0x64], xmm2
008d2482 movss xmm2, dword ptr [ebp - 0xa0]
008d248a addss xmm2, dword ptr [ebp - 0x34]
008d248f addss xmm5, xmm0
008d2493 movss xmm0, dword ptr [ebp - 0x50]
008d2498 addss xmm2, xmm4
008d249c addss xmm1, xmm5
008d24a0 addss xmm0, xmm2
008d24a4 movss dword ptr [ebp - 0x44], xmm1
008d24a9 movss dword ptr [ebp - 0x40], xmm0
008d24ae call 0x95e620
008d24b3 movups xmm0, xmmword ptr [ebp - 0x16c]
008d24ba mov eax, dword ptr [ebp - 0x144]
008d24c0 mov dword ptr [ebp - 0x1ec], eax
008d24c6 mov eax, dword ptr [edi + 0x10c]
008d24cc movups xmmword ptr [ebp - 0x214], xmm0
008d24d3 mov dword ptr [ebp - 0x108], eax
008d24d9 movups xmm0, xmmword ptr [ebp - 0x15c]
008d24e0 movups xmmword ptr [ebp - 0x204], xmm0
008d24e7 movq xmm0, qword ptr [ebp - 0x14c]
008d24ef movq qword ptr [ebp - 0x1f4], xmm0
008d24f7 movups xmm0, xmmword ptr [edi + 0xe4]
008d24fe movups xmmword ptr [ebp - 0x130], xmm0
008d2505 movups xmm0, xmmword ptr [edi + 0xf4]
008d250c movups xmmword ptr [ebp - 0x120], xmm0
008d2513 movq xmm0, qword ptr [edi + 0x104]
008d251b movq qword ptr [ebp - 0x110], xmm0
008d2523 lea eax, [ebp - 0x214]
008d2529 push eax
008d252a lea ecx, [ebp - 0x130]
008d2530 call 0x65b0f0
008d2535 cmp byte ptr [ebp - 0xa4], 0
008d253c movups xmm0, xmmword ptr [ebp - 0x130]
008d2543 mov eax, dword ptr [ebp - 0x108]
008d2549 mov dword ptr [ebp - 0x1c0], eax
008d254f movups xmmword ptr [ebp - 0x1e8], xmm0
008d2556 movups xmm0, xmmword ptr [ebp - 0x120]
008d255d movups xmmword ptr [ebp - 0x1d8], xmm0
008d2564 movq xmm0, qword ptr [ebp - 0x110]
008d256c movq qword ptr [ebp - 0x1c8], xmm0
008d2574 je 0x8d25a6
008d2576 mov eax, dword ptr [0xbfd65c]
008d257b mov eax, dword ptr [eax + 0x1a30dc]
008d2581 and eax, 0x800000ff
008d2586 jns 0x8d258f
008d2588 dec eax
008d2589 or eax, 0xffffff00
008d258e inc eax
008d258f movd xmm0, eax
008d2593 cvtdq2ps xmm0, xmm0
008d2596 mulss xmm0, dword ptr [0xb6a1f0]
008d259e movss dword ptr [ebp - 0x1cc], xmm0
008d25a6 movups xmm0, xmmword ptr [ebp - 0x130]
008d25ad mov ecx, dword ptr [ebp - 0xac]
008d25b3 lea edx, [ebp - 0xbc]
008d25b9 push edx
008d25ba movups xmmword ptr [ebp - 0xbc], xmm0
008d25c1 lea edx, [ebp - 0x1bc]
008d25c7 mov eax, dword ptr [ecx]
008d25c9 push edx
008d25ca lea edx, [ebp - 0x104]
008d25d0 push edx
008d25d1 mov eax, dword ptr [eax + 0xc]
008d25d4 call eax
008d25d6 mov dword ptr [ebp - 0xd4], eax
008d25dc test eax, eax
008d25de je 0x8d2602
008d25e0 sub esp, 8
008d25e3 lea eax, [ebp - 0xac]
008d25e9 mov ecx, esp
008d25eb push eax
008d25ec call 0x4078a0
008d25f1 push dword ptr [ebp - 0xd4]
008d25f7 lea ecx, [ebp - 0x1e8]
008d25fd call 0x65af60
008d2602 mov ecx, dword ptr [ebp - 0x1c]
008d2605 add esi, 0x20
008d2608 mov eax, dword ptr [ebp - 0x38]
008d260b add ecx, 4
008d260e mov dword ptr [ebp - 0x1c], ecx
008d2611 cmp ecx, eax
008d2613 jb 0x8d1e22
008d2619 mov edi, dword ptr [ebp - 0x20]
008d261c mov esi, dword ptr [ebp - 0x30]
008d261f mov ecx, dword ptr [ebp - 0xac]
008d2625 call 0x95f6d0
008d262a cmp dword ptr [esi + 0xbc], 1
008d2631 jbe 0x8d2c23
008d2637 cmp dword ptr [esi + 0x30], 0
008d263b jne 0x8d2c23
008d2641 push 0
008d2643 lea ecx, [esi + 0x6c]
008d2646 call 0x4053a0
008d264b test eax, eax
008d264d jne 0x8d26a8
008d264f push 0xb59390
008d2654 push eax
008d2655 call 0x95e330
008d265a add esp, 8
008d265d lea ecx, [ebp - 0xac]
008d2663 call 0x407790
008d2668 mov ecx, dword ptr [ebp - 0x7c]
008d266b test ecx, ecx
008d266d je 0x8d4136
008d2673 mov edx, dword ptr [ebp - 0x74]
008d2676 mov eax, ecx
008d2678 sub edx, ecx
008d267a and edx, 0xfffffff8
008d267d cmp edx, 0x1000
008d2683 jb 0x8d2699
008d2685 mov ecx, dword ptr [ecx - 4]
008d2688 add edx, 0x23
008d268b sub eax, ecx
008d268d add eax, -4
008d2690 cmp eax, 0x1f
008d2693 ja 0x8d2c85
008d2699 push edx
008d269a push ecx
008d269b call 0x9eb08e
008d26a0 add esp, 8
008d26a3 jmp 0x8d4136
008d26a8 push eax
008d26a9 lea ecx, [ebp - 0x19c]
008d26af call 0x4069d0
008d26b4 cmp dword ptr [edi + 0x80], 0
008d26bb jg 0x8d26d9
008d26bd cmp dword ptr [edi + 0x14], 0x10
008d26c1 mov eax, edi
008d26c3 jb 0x8d26c7
008d26c5 mov eax, dword ptr [edi]
008d26c7 push 0
008d26c9 push eax
008d26ca push 0xa0830c
008d26cf push 3
008d26d1 call 0x95e330
008d26d6 add esp, 0x10
008d26d9 mov eax, dword ptr [edi + 0x7c]
008d26dc lea ecx, [ebp - 0x44]
008d26df movss xmm0, dword ptr [esi + 0xd8]
008d26e7 movss xmm2, dword ptr [ebp - 0x184]
008d26ef movss xmm3, dword ptr [esi + 0x294]
008d26f7 mulss xmm0, dword ptr [eax + 0x34]
008d26fc movss xmm1, dword ptr [eax + 0x38]
008d2701 mulss xmm1, dword ptr [esi + 0xdc]
008d2709 mov eax, dword ptr [esi + 0x3d0]
008d270f mulss xmm2, xmm0
008d2713 movss xmm0, dword ptr [ebp - 0x180]
008d271b mulss xmm0, xmm1
008d271f movss xmm1, dword ptr [eax + 4]
008d2724 movss dword ptr [ebp - 0x24], xmm2
008d2729 movss dword ptr [ebp - 0x180], xmm0
008d2731 movss xmm0, dword ptr [eax]
008d2735 lea eax, [ebp - 0x58]
008d2738 movss dword ptr [ebp - 0x184], xmm2
008d2740 subss xmm0, xmm3
008d2744 movss xmm2, dword ptr [esi + 0x298]
008d274c subss xmm1, xmm2
008d2750 movss dword ptr [ebp - 0x28], xmm3
008d2755 push eax
008d2756 movss dword ptr [ebp - 0x20], xmm2
008d275b movss dword ptr [ebp - 0x44], xmm0
008d2760 movss dword ptr [ebp - 0x40], xmm1
008d2765 call 0x962560
008d276a cmp dword ptr [esi + 0x440], 0
008d2771 movss xmm4, dword ptr [ebp - 0x58]
008d2776 movss xmm1, dword ptr [ebp - 0x54]
008d277b movaps xmm0, xmm4
008d277e xorps xmm0, xmmword ptr [0xb6c9b0]
008d2785 movaps xmm2, xmm4
008d2788 mulss xmm2, dword ptr [ebp - 0x188]
008d2790 mulss xmm1, dword ptr [ebp - 0x188]
008d2798 movss xmm6, dword ptr [ebp - 0x194]
008d27a0 movss xmm5, dword ptr [0xb6a480]
008d27a8 movaps xmm3, xmm6
008d27ab movss xmm7, dword ptr [ebp - 0x20]
008d27b0 movss dword ptr [ebp - 0x30], xmm0
008d27b5 addss xmm7, xmm1
008d27b9 movss xmm0, dword ptr [ebp - 0x28]
008d27be addss xmm0, xmm2
008d27c2 mulss xmm3, xmm5
008d27c6 movss dword ptr [ebp - 0x28], xmm0
008d27cb jle 0x8d27d5
008d27cd subss xmm7, dword ptr [esi + 0x2a8]
008d27d5 movss xmm0, dword ptr [ebp - 0x190]
008d27dd lea eax, [ebp - 0x20]
008d27e0 movss xmm1, dword ptr [ebp - 0x198]
008d27e8 lea ecx, [ebp - 0x104]
008d27ee addss xmm0, xmm1
008d27f2 addss xmm1, dword ptr [0xb6a214]
008d27fa push 0
008d27fc push eax
008d27fd lea eax, [ebp - 0x98]
008d2803 movss dword ptr [ebp - 0x20], xmm0
008d2808 movss xmm0, dword ptr [ebp - 0x19c]
008d2810 push eax
008d2811 addss xmm0, xmm6
008d2815 movss dword ptr [ebp - 0xd4], xmm1
008d281d lea eax, [ebp - 0xd4]
008d2823 push eax
008d2824 lea eax, [ebp - 0x19c]
008d282a push eax
008d282b movss dword ptr [ebp - 0x98], xmm0
008d2833 call 0x95e9e0
008d2838 cmp byte ptr [esi + 0x13c], 0
008d283f je 0x8d2881
008d2841 movss xmm1, dword ptr [ebp - 0x104]
008d2849 movss xmm0, dword ptr [ebp - 0xfc]
008d2851 movss dword ptr [ebp - 0x104], xmm0
008d2859 movss xmm0, dword ptr [ebp - 0xec]
008d2861 movss dword ptr [ebp - 0xfc], xmm1
008d2869 movss xmm1, dword ptr [ebp - 0xf4]
008d2871 movss dword ptr [ebp - 0xf4], xmm0
008d2879 movss dword ptr [ebp - 0xec], xmm1
008d2881 mov eax, dword ptr [ebp - 0x7c]
008d2884 movaps xmm0, xmm3
008d2887 xorps xmm0, xmmword ptr [0xb6c9b0]
008d288e sub esp, 8
008d2891 movss xmm1, dword ptr [ebp - 0xd0]
008d2899 mov ecx, dword ptr [ebp + 8]
008d289c addss xmm1, dword ptr [eax]
008d28a0 mulss xmm4, dword ptr [0xb6a244]
008d28a8 movss xmm2, dword ptr [ebp - 0x54]
008d28ad movss dword ptr [ebp - 0x34], xmm0
008d28b2 addss xmm1, dword ptr [ecx]
008d28b6 movss xmm0, dword ptr [ebp - 0xa0]
008d28be addss xmm0, dword ptr [eax + 4]
008d28c3 mulss xmm2, dword ptr [0xb6a244]
008d28cb addss xmm1, dword ptr [ebp - 0x68]
008d28d0 subss xmm7, dword ptr [0xb6ab44]
008d28d8 addss xmm0, dword ptr [ecx + 4]
008d28dd addss xmm1, xmm4
008d28e1 mulss xmm7, dword ptr [0xb6a4dc]
008d28e9 addss xmm0, dword ptr [ebp - 0x50]
008d28ee movss dword ptr [ebp - 0x44], xmm1
008d28f3 movss xmm1, dword ptr [ebp - 0xd0]
008d28fb addss xmm1, dword ptr [eax + 8]
008d2900 addss xmm0, xmm2
008d2904 addss xmm1, dword ptr [ecx]
008d2908 movss dword ptr [ebp - 0x40], xmm0
008d290d movss xmm0, dword ptr [ebp - 0xa0]
008d2915 addss xmm0, dword ptr [eax + 0xc]
008d291a addss xmm1, dword ptr [ebp - 0x68]
008d291f addss xmm0, dword ptr [ecx + 4]
008d2924 addss xmm1, xmm4
008d2928 addss xmm0, dword ptr [ebp - 0x50]
008d292d movss dword ptr [ebp - 0x64], xmm1
008d2932 movaps xmm1, xmm3
008d2935 addss xmm0, xmm2
008d2939 movss dword ptr [ebp - 0x60], xmm0
008d293e movaps xmm0, xmm1
008d2941 mulss xmm1, dword ptr [ebp - 0x30]
008d2946 mulss xmm0, dword ptr [ebp - 0x54]
008d294b movss dword ptr [ebp - 0x3c], xmm1
008d2950 movss xmm1, dword ptr [ebp - 0x28]
008d2955 subss xmm1, dword ptr [0xb6aa8c]
008d295d movss dword ptr [ebp - 0xd4], xmm0
008d2965 movss xmm0, dword ptr [0xbfec08]
008d296d subss xmm0, dword ptr [0xb6ac30]
008d2975 mulss xmm1, dword ptr [0xb6a4dc]
008d297d mulss xmm0, xmm5
008d2981 addss xmm0, xmm1
008d2985 movss xmm1, dword ptr [0xbfec68]
008d298d subss xmm1, dword ptr [0xb6ab8c]
008d2995 mulss xmm1, xmm5
008d2999 addss xmm1, xmm7
008d299d movss dword ptr [ebp - 0x98], xmm1
008d29a5 movss xmm1, dword ptr [0xbaa554]
008d29ad mulss xmm1, dword ptr [0xbaa920]
008d29b5 mulss xmm0, xmm1
008d29b9 movss dword ptr [ebp - 0x1c], xmm1
008d29be addss xmm0, xmm5
008d29c2 movss dword ptr [ebp - 0x20], xmm0
008d29c7 fld dword ptr [ebp - 0x20]
008d29ca fstp qword ptr [esp]
008d29cd call 0x9ec3b2
008d29d2 fstp dword ptr [ebp - 0x20]
008d29d5 movss xmm0, dword ptr [ebp - 0x20]
008d29da divss xmm0, dword ptr [ebp - 0x1c]
008d29df movss dword ptr [ebp - 0x88], xmm0
008d29e7 movss xmm0, dword ptr [ebp - 0x98]
008d29ef mulss xmm0, dword ptr [ebp - 0x1c]
008d29f4 addss xmm0, dword ptr [0xb6a480]
008d29fc movss dword ptr [ebp - 0x20], xmm0
008d2a01 fld dword ptr [ebp - 0x20]
008d2a04 fstp qword ptr [esp]
008d2a07 call 0x9ec3b2
008d2a0c movss xmm0, dword ptr [ebp - 0x24]
008d2a11 add esp, 8
008d2a14 movaps xmm1, xmm0
008d2a17 mulss xmm1, dword ptr [ebp - 0xd4]
008d2a1f fstp dword ptr [ebp - 0x20]
008d2a22 movss xmm3, dword ptr [ebp - 0x20]
008d2a27 divss xmm3, dword ptr [ebp - 0x1c]
008d2a2c addss xmm1, dword ptr [ebp - 0x88]
008d2a34 mulss xmm0, dword ptr [ebp - 0x3c]
008d2a39 lea ecx, [ebp - 0x1bc]
008d2a3f mov eax, dword ptr [ebp + 8]
008d2a42 movss xmm7, dword ptr [ebp - 0xd0]
008d2a4a movaps xmm2, xmm7
008d2a4d addss xmm2, xmm1
008d2a51 movss xmm1, dword ptr [ebp - 0xa0]
008d2a59 addss xmm0, xmm3
008d2a5d addss xmm2, dword ptr [eax]
008d2a61 addss xmm1, xmm0
008d2a65 movss xmm0, dword ptr [ebp - 0x24]
008d2a6a addss xmm2, dword ptr [ebp - 0x68]
008d2a6f addss xmm1, dword ptr [eax + 4]
008d2a74 movss dword ptr [ebp - 0xcc], xmm2
008d2a7c addss xmm1, dword ptr [ebp - 0x50]
008d2a81 movss xmm2, dword ptr [ebp - 0x34]
008d2a86 movss dword ptr [ebp - 0xc8], xmm1
008d2a8e movaps xmm1, xmm2
008d2a91 mulss xmm1, dword ptr [ebp - 0x54]
008d2a96 mulss xmm2, dword ptr [ebp - 0x30]
008d2a9b mulss xmm0, xmm1
008d2a9f movss xmm1, dword ptr [ebp - 0x24]
008d2aa4 mulss xmm1, xmm2
008d2aa8 addss xmm0, dword ptr [ebp - 0x88]
008d2ab0 addss xmm1, xmm3
008d2ab4 addss xmm7, xmm0
008d2ab8 movss xmm0, dword ptr [ebp - 0xa0]
008d2ac0 addss xmm0, xmm1
008d2ac4 addss xmm7, dword ptr [eax]
008d2ac8 addss xmm0, dword ptr [eax + 4]
008d2acd lea eax, [ebp - 0x44]
008d2ad0 push eax
008d2ad1 addss xmm7, dword ptr [ebp - 0x68]
008d2ad6 lea eax, [ebp - 0x64]
008d2ad9 addss xmm0, dword ptr [ebp - 0x50]
008d2ade push eax
008d2adf lea eax, [ebp - 0xcc]
008d2ae5 push eax
008d2ae6 lea eax, [ebp - 0xc4]
008d2aec movss dword ptr [ebp - 0xc4], xmm7
008d2af4 push eax
008d2af5 movss dword ptr [ebp - 0xc0], xmm0
008d2afd call 0x95e620
008d2b02 mov ecx, dword ptr [ebp - 0x14]
008d2b05 sub esp, 0x2c
008d2b08 mov eax, dword ptr [ecx + 0xa08910]
008d2b0e mov ecx, esp
008d2b10 mov dword ptr [0xbc7a44], eax
008d2b15 lea eax, [esi + 0xe4]
008d2b1b push eax
008d2b1c call 0x402170
008d2b21 lea edx, [ebp - 0x16c]
008d2b27 lea ecx, [ebp - 0x130]
008d2b2d call 0x402290
008d2b32 add esp, 0x2c
008d2b35 cmp byte ptr [ebp - 0xa4], 0
008d2b3c je 0x8d2b6e
008d2b3e mov eax, dword ptr [0xbfd65c]
008d2b43 mov eax, dword ptr [eax + 0x1a30dc]
008d2b49 and eax, 0x800000ff
008d2b4e jns 0x8d2b57
008d2b50 dec eax
008d2b51 or eax, 0xffffff00
008d2b56 inc eax
008d2b57 movd xmm0, eax
008d2b5b cvtdq2ps xmm0, xmm0
008d2b5e mulss xmm0, dword ptr [0xb6a1f0]
008d2b66 movss dword ptr [ebp - 0x114], xmm0
008d2b6e cmp dword ptr [edi + 0x80], 0
008d2b75 jg 0x8d2b93
008d2b77 cmp dword ptr [edi + 0x14], 0x10
008d2b7b mov eax, edi
008d2b7d jb 0x8d2b81
008d2b7f mov eax, dword ptr [edi]
008d2b81 push 0
008d2b83 push eax
008d2b84 push 0xa0830c
008d2b89 push 3
008d2b8b call 0x95e330
008d2b90 add esp, 0x10
008d2b93 mov ecx, dword ptr [edi + 0x7c]
008d2b96 lea eax, [ebp - 0x44]
008d2b99 push eax
008d2b9a call 0x403540
008d2b9f mov byte ptr [ebp - 4], 3
008d2ba3 lea edx, [ebp - 0xbc]
008d2ba9 mov ecx, dword ptr [eax]
008d2bab movups xmm0, xmmword ptr [ebp - 0x130]
008d2bb2 push edx
008d2bb3 lea edx, [ebp - 0x1bc]
008d2bb9 movups xmmword ptr [ebp - 0xbc], xmm0
008d2bc0 mov eax, dword ptr [ecx]
008d2bc2 push edx
008d2bc3 lea edx, [ebp - 0x104]
008d2bc9 push edx
008d2bca mov eax, dword ptr [eax + 0xc]
008d2bcd call eax
008d2bcf lea ecx, [ebp - 0x44]
008d2bd2 mov dword ptr [ebp - 0x1c], eax
008d2bd5 mov byte ptr [ebp - 4], 2
008d2bd9 call 0x407790
008d2bde cmp dword ptr [ebp - 0x1c], 0
008d2be2 je 0x8d2c23
008d2be4 cmp dword ptr [edi + 0x80], 0
008d2beb jg 0x8d2c09
008d2bed cmp dword ptr [edi + 0x14], 0x10
008d2bf1 mov eax, edi
008d2bf3 jb 0x8d2bf7
008d2bf5 mov eax, dword ptr [edi]
008d2bf7 push 0
008d2bf9 push eax
008d2bfa push 0xa0830c
008d2bff push 3
008d2c01 call 0x95e330
008d2c06 add esp, 0x10
008d2c09 mov ecx, dword ptr [edi + 0x7c]
008d2c0c sub esp, 8
008d2c0f push esp
008d2c10 call 0x403540
008d2c15 push dword ptr [ebp - 0x1c]
008d2c18 lea ecx, [ebp - 0x130]
008d2c1e call 0x65af60
008d2c23 mov byte ptr [ebp - 4], 4
008d2c27 mov ecx, dword ptr [ebp - 0xa8]
008d2c2d test ecx, ecx
008d2c2f je 0x8d2c51
008d2c31 mov eax, dword ptr [ecx]
008d2c33 mov eax, dword ptr [eax + 0xc]
008d2c36 call eax
008d2c38 test al, al
008d2c3a je 0x8d2c51
008d2c3c mov eax, dword ptr [0xbfd62c]
008d2c41 test eax, eax
008d2c43 je 0x8d2c51
008d2c45 lea ecx, [ebp - 0xac]
008d2c4b push ecx
008d2c4c call eax
008d2c4e add esp, 4
008d2c51 mov dword ptr [ebp - 4], 0xffffffff
008d2c58 mov ecx, dword ptr [ebp - 0x7c]
008d2c5b test ecx, ecx
008d2c5d je 0x8d3a35
008d2c63 mov edx, dword ptr [ebp - 0x74]
008d2c66 mov eax, ecx
008d2c68 sub edx, ecx
008d2c6a and edx, 0xfffffff8
008d2c6d cmp edx, 0x1000
008d2c73 jb 0x8d2c8b
008d2c75 mov ecx, dword ptr [ecx - 4]
008d2c78 add edx, 0x23
008d2c7b sub eax, ecx
008d2c7d add eax, -4
008d2c80 cmp eax, 0x1f
008d2c83 jbe 0x8d2c8b
008d2c85 call dword ptr [0xa065ac]
008d2c8b push edx
008d2c8c push ecx
008d2c8d call 0x9eb08e
008d2c92 add esp, 8
008d2c95 jmp 0x8d3a35
008d2c9a cmp eax, 1
008d2c9d jbe 0x8d33f2
008d2ca3 mov ecx, esi
008d2ca5 call 0x8c5940
008d2caa test al, al
008d2cac jne 0x8d2cc4
008d2cae mov eax, dword ptr [esi + 0x2c]
008d2cb1 cmp eax, 2
008d2cb4 je 0x8d2cc4
008d2cb6 cmp eax, 5
008d2cb9 je 0x8d2cc4
008d2cbb cmp eax, 8
008d2cbe jne 0x8d33f2
008d2cc4 cmp byte ptr [esi + 0x13c], 0
008d2ccb movss xmm0, dword ptr [esi + 0xe0]
008d2cd3 movss dword ptr [ebp - 0x14], xmm0
008d2cd8 je 0x8d2ce9
008d2cda xorps xmm0, xmmword ptr [0xb6c9b0]
008d2ce1 movss dword ptr [esi + 0xe0], xmm0
008d2ce9 push 0xc02fec
008d2cee push 0xc02fec
008d2cf3 lea eax, [esi + 0x19c]
008d2cf9 mov ecx, edi
008d2cfb push eax
008d2cfc push 0
008d2cfe call 0x405250
008d2d03 movss xmm0, dword ptr [ebp - 0x14]
008d2d08 movss dword ptr [esi + 0xe0], xmm0
008d2d10 movss xmm0, dword ptr [esi + 0x3b0]
008d2d18 comiss xmm0, dword ptr [0xb6a9ac]
008d2d1f jbe 0x8d3a35
008d2d25 push 0
008d2d27 lea ecx, [esi + 0x6c]
008d2d2a call 0x4053a0
008d2d2f push 1
008d2d31 lea ecx, [esi + 0x6c]
008d2d34 mov dword ptr [ebp - 0x14], eax
008d2d37 call 0x4053a0
008d2d3c mov esi, eax
008d2d3e mov eax, dword ptr [ebp - 0x14]
008d2d41 test eax, eax
008d2d43 je 0x8d33de
008d2d49 test esi, esi
008d2d4b je 0x8d33de
008d2d51 push eax
008d2d52 lea ecx, [ebp - 0x2a0]
008d2d58 call 0x4069d0
008d2d5d push esi
008d2d5e lea ecx, [ebp - 0x19c]
008d2d64 call 0x4069d0
008d2d69 cmp dword ptr [edi + 0x80], 1
008d2d70 jg 0x8d2d8e
008d2d72 cmp dword ptr [edi + 0x14], 0x10
008d2d76 mov eax, edi
008d2d78 jb 0x8d2d7c
008d2d7a mov eax, dword ptr [edi]
008d2d7c push 1
008d2d7e push eax
008d2d7f push 0xa0830c
008d2d84 push 3
008d2d86 call 0x95e330
008d2d8b add esp, 0x10
008d2d8e mov eax, dword ptr [edi + 0x7c]
008d2d91 lea ecx, [ebp - 0x104]
008d2d97 mov esi, dword ptr [ebp - 0x30]
008d2d9a movss xmm1, dword ptr [ebp - 0x184]
008d2da2 push 0
008d2da4 movss xmm0, dword ptr [eax + 0xd0]
008d2dac mulss xmm0, dword ptr [esi + 0xd8]
008d2db4 movss xmm2, dword ptr [eax + 0xd4]
008d2dbc lea eax, [ebp - 0x14]
008d2dbf mulss xmm2, dword ptr [esi + 0xdc]
008d2dc7 push eax
008d2dc8 mulss xmm1, xmm0
008d2dcc lea eax, [ebp - 0x20]
008d2dcf push eax
008d2dd0 mulss xmm2, dword ptr [ebp - 0x180]
008d2dd8 lea eax, [ebp - 0x198]
008d2dde push eax
008d2ddf movss dword ptr [ebp - 0x184], xmm1
008d2de7 lea eax, [ebp - 0x19c]
008d2ded movss xmm1, dword ptr [esi + 0x3b0]
008d2df5 divss xmm1, xmm2
008d2df9 push eax
008d2dfa movss xmm0, dword ptr [ebp - 0x198]
008d2e02 mulss xmm1, dword ptr [0xb6a4dc]
008d2e0a movss dword ptr [ebp - 0x180], xmm2
008d2e12 movss xmm2, dword ptr [ebp - 0x194]
008d2e1a addss xmm0, xmm1
008d2e1e movss dword ptr [ebp - 0x14], xmm0
008d2e23 movaps xmm0, xmm2
008d2e26 addss xmm0, dword ptr [ebp - 0x19c]
008d2e2e movss dword ptr [ebp - 0x20], xmm0
008d2e33 call 0x95e9e0
008d2e38 cmp byte ptr [esi + 0x13c], 0
008d2e3f je 0x8d2e81
008d2e41 movss xmm1, dword ptr [ebp - 0x104]
008d2e49 movss xmm0, dword ptr [ebp - 0xfc]
008d2e51 movss dword ptr [ebp - 0x104], xmm0
008d2e59 movss xmm0, dword ptr [ebp - 0xec]
008d2e61 movss dword ptr [ebp - 0xfc], xmm1
008d2e69 movss xmm1, dword ptr [ebp - 0xf4]
008d2e71 movss dword ptr [ebp - 0xf4], xmm0
008d2e79 movss dword ptr [ebp - 0xec], xmm1
008d2e81 movss xmm0, dword ptr [esi + 0x36c]
008d2e89 mulss xmm2, dword ptr [0xb6a480]
008d2e91 mulss xmm0, dword ptr [0xb6a230]
008d2e99 movss dword ptr [ebp - 0x30], xmm2
008d2e9e movss dword ptr [ebp - 0x14], xmm0
008d2ea3 call 0x412010
008d2ea8 movss dword ptr [ebp - 0x20], xmm0
008d2ead movss xmm0, dword ptr [ebp - 0x14]
008d2eb2 call 0x411fe0
008d2eb7 movss xmm2, dword ptr [ebp - 0x28c]
008d2ebf lea ecx, [ebp - 0xac]
008d2ec5 movss xmm3, dword ptr [ebp - 0x294]
008d2ecd addss xmm2, xmm3
008d2ed1 movss xmm4, dword ptr [ebp - 0x20]
008d2ed6 divss xmm3, dword ptr [0xb6a4dc]
008d2ede movss xmm6, dword ptr [esi + 0xdc]
008d2ee6 movaps xmm1, xmm2
008d2ee9 mulss xmm3, dword ptr [0xb6a480]
008d2ef1 movaps xmm5, xmm6
008d2ef4 mulss xmm2, xmm4
008d2ef8 mulss xmm1, xmm0
008d2efc mulss xmm6, xmm2
008d2f00 movss xmm2, dword ptr [esi + 0x3b0]
008d2f08 subss xmm2, xmm3
008d2f0c mulss xmm5, xmm1
008d2f10 movss dword ptr [ebp - 0x20], xmm6
008d2f15 movss dword ptr [ebp - 0x14], xmm5
008d2f1a movaps xmm1, xmm2
008d2f1d mulss xmm2, xmm4
008d2f21 mulss xmm1, xmm0
008d2f25 movss dword ptr [ebp - 0xd4], xmm2
008d2f2d movss dword ptr [ebp - 0xac], xmm2
008d2f35 movaps xmm0, xmm1
008d2f38 movss dword ptr [ebp - 0x98], xmm1
008d2f40 xorps xmm0, xmmword ptr [0xb6c9b0]
008d2f47 movss dword ptr [ebp - 0xa8], xmm0
008d2f4f call 0x9624f0
008d2f54 movss xmm1, dword ptr [ebp - 0x30]
008d2f59 xorps xmm1, xmmword ptr [0xb6c9b0]
008d2f60 mov eax, dword ptr [ebp + 8]
008d2f63 movaps xmm0, xmm1
008d2f66 mulss xmm0, dword ptr [ebp - 0xac]
008d2f6e mulss xmm1, dword ptr [ebp - 0xa8]
008d2f76 mulss xmm0, dword ptr [ebp - 0x184]
008d2f7e movss xmm7, dword ptr [eax]
008d2f82 mulss xmm1, dword ptr [ebp - 0x184]
008d2f8a movaps xmm6, xmm7
008d2f8d addss xmm0, dword ptr [ebp - 0x14]
008d2f92 movss xmm3, dword ptr [ebp - 0x30]
008d2f97 addss xmm1, dword ptr [ebp - 0x20]
008d2f9c mulss xmm3, dword ptr [ebp - 0xa8]
008d2fa4 addss xmm6, xmm0
008d2fa8 movss xmm2, dword ptr [esi + 0x2a8]
008d2fb0 addss xmm2, dword ptr [esi + 0x298]
008d2fb8 mulss xmm3, dword ptr [ebp - 0x184]
008d2fc0 movss dword ptr [ebp - 0x34], xmm6
008d2fc5 movss xmm6, dword ptr [eax + 4]
008d2fca addss xmm3, dword ptr [ebp - 0x20]
008d2fcf movaps xmm0, xmm6
008d2fd2 addss xmm0, xmm1
008d2fd6 movss xmm1, dword ptr [ebp - 0x34]
008d2fdb addss xmm1, dword ptr [ebp - 0x68]
008d2fe0 addss xmm6, xmm3
008d2fe4 addss xmm0, dword ptr [ebp - 0x50]
008d2fe9 movss dword ptr [ebp - 0x34], xmm1
008d2fee movaps xmm1, xmm2
008d2ff1 addss xmm6, dword ptr [ebp - 0x50]
008d2ff6 movss dword ptr [ebp - 0x3c], xmm0
008d2ffb movss xmm0, dword ptr [ebp - 0x30]
008d3000 mulss xmm0, dword ptr [ebp - 0xac]
008d3008 movss dword ptr [ebp - 0x28], xmm6
008d300d movss dword ptr [ebp - 0x30], xmm2
008d3012 mulss xmm0, dword ptr [ebp - 0x184]
008d301a addss xmm0, dword ptr [ebp - 0x14]
008d301f addss xmm7, xmm0
008d3023 movss xmm0, dword ptr [esi + 0x2a4]
008d302b addss xmm0, dword ptr [esi + 0x294]
008d3033 addss xmm7, dword ptr [ebp - 0x68]
008d3038 movss dword ptr [ebp - 0x88], xmm0
008d3040 addss xmm0, dword ptr [ebp - 0x98]
008d3048 movss dword ptr [ebp - 0x1c], xmm7
008d304d addss xmm1, dword ptr [ebp - 0xd4]
008d3055 movss xmm3, dword ptr [0xbfec68]
008d305d sub esp, 8
008d3060 subss xmm3, dword ptr [0xb6ab8c]
008d3068 movss xmm4, dword ptr [0xb6a480]
008d3070 subss xmm0, dword ptr [0xb6aa8c]
008d3078 subss xmm1, dword ptr [0xb6ab44]
008d3080 movss xmm2, dword ptr [0xbfec08]
008d3088 subss xmm2, dword ptr [0xb6ac30]
008d3090 mulss xmm3, xmm4
008d3094 mulss xmm1, dword ptr [0xb6a4dc]
008d309c mulss xmm0, dword ptr [0xb6a4dc]
008d30a4 addss xmm1, xmm3
008d30a8 mulss xmm2, xmm4
008d30ac movss dword ptr [ebp - 0x54], xmm3
008d30b1 addss xmm0, xmm2
008d30b5 movss dword ptr [ebp - 0xd4], xmm2
008d30bd movss dword ptr [ebp - 0x20], xmm1
008d30c2 movss xmm1, dword ptr [0xbaa554]
008d30ca mulss xmm1, dword ptr [0xbaa920]
008d30d2 mulss xmm0, xmm1
008d30d6 movss dword ptr [ebp - 0x24], xmm1
008d30db addss xmm0, xmm4
008d30df movss dword ptr [ebp - 0x14], xmm0
008d30e4 fld dword ptr [ebp - 0x14]
008d30e7 fstp qword ptr [esp]
008d30ea call 0x9ec3b2
008d30ef fstp dword ptr [ebp - 0x14]
008d30f2 movss xmm0, dword ptr [ebp - 0x14]
008d30f7 divss xmm0, dword ptr [ebp - 0x24]
008d30fc movss dword ptr [ebp - 0x98], xmm0
008d3104 movss xmm0, dword ptr [ebp - 0x20]
008d3109 mulss xmm0, dword ptr [ebp - 0x24]
008d310e addss xmm0, dword ptr [0xb6a480]
008d3116 movss dword ptr [ebp - 0x14], xmm0
008d311b fld dword ptr [ebp - 0x14]
008d311e fstp qword ptr [esp]
008d3121 call 0x9ec3b2
008d3126 fstp dword ptr [ebp - 0x14]
008d3129 movss xmm2, dword ptr [ebp - 0x14]
008d312e divss xmm2, dword ptr [ebp - 0x24]
008d3133 movss xmm3, dword ptr [ebp - 0x98]
008d313b movaps xmm0, xmm2
008d313e movaps xmm1, xmm3
008d3141 addss xmm0, dword ptr [ebp - 0x28]
008d3146 addss xmm1, dword ptr [ebp - 0x1c]
008d314b addss xmm3, dword ptr [ebp - 0x34]
008d3150 addss xmm2, dword ptr [ebp - 0x3c]
008d3155 movss dword ptr [ebp - 0x40], xmm0
008d315a movss xmm0, dword ptr [ebp - 0x88]
008d3162 subss xmm0, dword ptr [0xb6aa8c]
008d316a movss dword ptr [ebp - 0x44], xmm1
008d316f movss xmm1, dword ptr [ebp - 0x30]
008d3174 subss xmm1, dword ptr [0xb6ab44]
008d317c movss dword ptr [ebp - 0x64], xmm3
008d3181 mulss xmm0, dword ptr [0xb6a4dc]
008d3189 movss dword ptr [ebp - 0x60], xmm2
008d318e mulss xmm1, dword ptr [0xb6a4dc]
008d3196 addss xmm0, dword ptr [ebp - 0xd4]
008d319e addss xmm1, dword ptr [ebp - 0x54]
008d31a3 mulss xmm0, dword ptr [ebp - 0x24]
008d31a8 movss dword ptr [ebp - 0x30], xmm1
008d31ad addss xmm0, dword ptr [0xb6a480]
008d31b5 movss dword ptr [ebp - 0x14], xmm0
008d31ba fld dword ptr [ebp - 0x14]
008d31bd fstp qword ptr [esp]
008d31c0 call 0x9ec3b2
008d31c5 movss xmm2, dword ptr [ebp - 0x30]
008d31ca mulss xmm2, dword ptr [ebp - 0x24]
008d31cf fstp dword ptr [ebp - 0x14]
008d31d2 movss xmm0, dword ptr [ebp - 0x14]
008d31d7 divss xmm0, dword ptr [ebp - 0x24]
008d31dc addss xmm2, dword ptr [0xb6a480]
008d31e4 movss dword ptr [ebp - 0x20], xmm0
008d31e9 movss dword ptr [ebp - 0x14], xmm2
008d31ee fld dword ptr [ebp - 0x14]
008d31f1 fstp qword ptr [esp]
008d31f4 call 0x9ec3b2
008d31f9 fstp dword ptr [ebp - 0x14]
008d31fc movss xmm2, dword ptr [ebp - 0x14]
008d3201 add esp, 8
008d3204 divss xmm2, dword ptr [ebp - 0x24]
008d3209 lea eax, [ebp - 0x44]
008d320c lea ecx, [ebp - 0x1bc]
008d3212 push eax
008d3213 lea eax, [ebp - 0x64]
008d3216 push eax
008d3217 lea eax, [ebp - 0xcc]
008d321d push eax
008d321e lea eax, [ebp - 0xc4]
008d3224 push eax
008d3225 movss xmm3, dword ptr [ebp - 0x20]
008d322a movaps xmm1, xmm3
008d322d movaps xmm0, xmm2
008d3230 addss xmm1, dword ptr [ebp - 0x1c]
008d3235 addss xmm0, dword ptr [ebp - 0x28]
008d323a addss xmm3, dword ptr [ebp - 0x34]
008d323f addss xmm2, dword ptr [ebp - 0x3c]
008d3244 movss dword ptr [ebp - 0xcc], xmm1
008d324c movss dword ptr [ebp - 0xc8], xmm0
008d3254 movss dword ptr [ebp - 0xc4], xmm3
008d325c movss dword ptr [ebp - 0xc0], xmm2
008d3264 call 0x95e620
008d3269 cmp dword ptr [edi + 0x80], 0
008d3270 jg 0x8d328e
008d3272 cmp dword ptr [edi + 0x14], 0x10
008d3276 mov eax, edi
008d3278 jb 0x8d327c
008d327a mov eax, dword ptr [edi]
008d327c push 0
008d327e push eax
008d327f push 0xa0830c
008d3284 push 3
008d3286 call 0x95e330
008d328b add esp, 0x10
008d328e mov eax, dword ptr [edi + 0x7c]
008d3291 xor ecx, ecx
008d3293 cmp byte ptr [ebp - 0xa4], cl
008d3299 movups xmm1, xmmword ptr [eax + 0x78]
008d329d mov eax, 0x3c
008d32a2 cmove eax, ecx
008d32a5 sub esp, 0x2c
008d32a8 movaps xmm0, xmm1
008d32ab movd dword ptr [0xbc7a34], xmm1
008d32b3 psrldq xmm0, 4
008d32b8 mov ecx, esp
008d32ba movd dword ptr [0xbc7a38], xmm0
008d32c2 movaps xmm0, xmm1
008d32c5 mov eax, dword ptr [eax + 0xa08910]
008d32cb mov dword ptr [0xbc7a44], eax
008d32d0 lea eax, [esi + 0xe4]
008d32d6 psrldq xmm0, 8
008d32db psrldq xmm1, 0xc
008d32e0 push eax
008d32e1 movd dword ptr [0xbc7a3c], xmm0
008d32e9 movd dword ptr [0xbc7a40], xmm1
008d32f1 call 0x402170
008d32f6 lea edx, [ebp - 0x16c]
008d32fc lea ecx, [ebp - 0x130]
008d3302 call 0x402290
008d3307 add esp, 0x2c
008d330a cmp byte ptr [ebp - 0xa4], 0
008d3311 je 0x8d3343
008d3313 mov eax, dword ptr [0xbfd65c]
008d3318 mov eax, dword ptr [eax + 0x1a30dc]
008d331e and eax, 0x800000ff
008d3323 jns 0x8d332c
008d3325 dec eax
008d3326 or eax, 0xffffff00
008d332b inc eax
008d332c movd xmm0, eax
008d3330 cvtdq2ps xmm0, xmm0
008d3333 mulss xmm0, dword ptr [0xb6a1f0]
008d333b movss dword ptr [ebp - 0x114], xmm0
008d3343 cmp dword ptr [edi + 0x80], 0
008d334a jg 0x8d3368
008d334c cmp dword ptr [edi + 0x14], 0x10
008d3350 mov eax, edi
008d3352 jb 0x8d3356
008d3354 mov eax, dword ptr [edi]
008d3356 push 0
008d3358 push eax
008d3359 push 0xa0830c
008d335e push 3
008d3360 call 0x95e330
008d3365 add esp, 0x10
008d3368 mov eax, dword ptr [edi + 0x7c]
008d336b mov dword ptr [eax + 0x28], 0
008d3372 cmp dword ptr [edi + 0x80], 0
008d3379 jg 0x8d3397
008d337b cmp dword ptr [edi + 0x14], 0x10
008d337f mov eax, edi
008d3381 jb 0x8d3385
008d3383 mov eax, dword ptr [edi]
008d3385 push 0
008d3387 push eax
008d3388 push 0xa0830c
008d338d push 3
008d338f call 0x95e330
008d3394 add esp, 0x10
008d3397 mov eax, dword ptr [edi + 0x7c]
008d339a mov dword ptr [eax + 0x2c], 0
008d33a1 cmp dword ptr [edi + 0x80], 0
008d33a8 jg 0x8d33c6
008d33aa cmp dword ptr [edi + 0x14], 0x10
008d33ae mov eax, edi
008d33b0 jb 0x8d33b4
008d33b2 mov eax, dword ptr [edi]
008d33b4 push 0
008d33b6 push eax
008d33b7 push 0xa0830c
008d33bc push 3
008d33be call 0x95e330
008d33c3 add esp, 0x10
008d33c6 mov ecx, dword ptr [edi + 0x7c]
008d33c9 lea eax, [ebp - 0x44]
008d33cc push eax
008d33cd call 0x403540
008d33d2 mov dword ptr [ebp - 4], 5
008d33d9 jmp 0x8d39b2
008d33de push 0xb59390
008d33e3 push 0
008d33e5 call 0x95e330
008d33ea add esp, 8
008d33ed jmp 0x8d4136
008d33f2 mov eax, dword ptr [esi + 0x2c]
008d33f5 cmp eax, 2
008d33f8 je 0x8d3421
008d33fa cmp eax, 0xa
008d33fd je 0x8d3421
008d33ff cmp eax, 7
008d3402 je 0x8d3421
008d3404 push 0xc02fec
008d3409 push 0xc02fec
008d340e lea eax, [esi + 0x19c]
008d3414 mov ecx, edi
008d3416 push eax
008d3417 call 0x4051e0
008d341c jmp 0x8d3a35
008d3421 push 0
008d3423 lea ecx, [esi + 0x6c]
008d3426 call 0x4053a0
008d342b test eax, eax
008d342d je 0x8d33de
008d342f push eax
008d3430 lea ecx, [ebp - 0x19c]
008d3436 call 0x4069d0
008d343b movss xmm1, dword ptr [esi + 0x3b0]
008d3443 lea eax, [ebp - 0x14]
008d3446 mulss xmm1, dword ptr [0xb6a4dc]
008d344e lea ecx, [ebp - 0x104]
008d3454 push 0
008d3456 movss xmm0, dword ptr [ebp - 0x198]
008d345e movss xmm2, dword ptr [ebp - 0x194]
008d3466 addss xmm0, xmm1
008d346a push eax
008d346b lea eax, [ebp - 0x20]
008d346e push eax
008d346f lea eax, [ebp - 0x198]
008d3475 movss dword ptr [ebp - 0x14], xmm0
008d347a movaps xmm0, xmm2
008d347d addss xmm0, dword ptr [ebp - 0x19c]
008d3485 push eax
008d3486 lea eax, [ebp - 0x19c]
008d348c push eax
008d348d movss dword ptr [ebp - 0x20], xmm0
008d3492 call 0x95e9e0
008d3497 cmp byte ptr [esi + 0x13c], 0
008d349e je 0x8d34e0
008d34a0 movss xmm1, dword ptr [ebp - 0x104]
008d34a8 movss xmm0, dword ptr [ebp - 0xfc]
008d34b0 movss dword ptr [ebp - 0x104], xmm0
008d34b8 movss xmm0, dword ptr [ebp - 0xec]
008d34c0 movss dword ptr [ebp - 0xfc], xmm1
008d34c8 movss xmm1, dword ptr [ebp - 0xf4]
008d34d0 movss dword ptr [ebp - 0xf4], xmm0
008d34d8 movss dword ptr [ebp - 0xec], xmm1
008d34e0 movss xmm0, dword ptr [esi + 0x36c]
008d34e8 mulss xmm2, dword ptr [0xb6a480]
008d34f0 mulss xmm0, dword ptr [0xb6a230]
008d34f8 movss dword ptr [ebp - 0x34], xmm2
008d34fd movss dword ptr [ebp - 0x14], xmm0
008d3502 call 0x412010
008d3507 movaps xmm2, xmm0
008d350a movss xmm0, dword ptr [ebp - 0x14]
008d350f movss dword ptr [ebp - 0x30], xmm2
008d3514 call 0x411fe0
008d3519 movss xmm2, dword ptr [ebp - 0x30]
008d351e lea ecx, [ebp - 0x58]
008d3521 movaps xmm1, xmm0
008d3524 movss xmm0, dword ptr [esi + 0x3b0]
008d352c mulss xmm1, xmm0
008d3530 mulss xmm2, xmm0
008d3534 movss dword ptr [ebp - 0x14], xmm1
008d3539 xorps xmm1, xmmword ptr [0xb6c9b0]
008d3540 movss dword ptr [ebp - 0x30], xmm2
008d3545 movss dword ptr [ebp - 0x58], xmm2
008d354a movss dword ptr [ebp - 0x54], xmm1
008d354f call 0x9624f0
008d3554 movss xmm1, dword ptr [ebp - 0x34]
008d3559 sub esp, 8
008d355c movss xmm2, dword ptr [esi + 0x2a8]
008d3564 movaps xmm0, xmm1
008d3567 xorps xmm0, xmmword ptr [0xb6c9b0]
008d356e addss xmm2, dword ptr [esi + 0x298]
008d3576 movss xmm3, dword ptr [0xbfec68]
008d357e subss xmm3, dword ptr [0xb6ab8c]
008d3586 movss xmm4, dword ptr [0xb6a480]
008d358e movss dword ptr [ebp - 0x3c], xmm0
008d3593 movaps xmm0, xmm1
008d3596 mulss xmm0, dword ptr [ebp - 0x58]
008d359b mulss xmm1, dword ptr [ebp - 0x54]
008d35a0 movss dword ptr [ebp - 0x1c], xmm0
008d35a5 movss xmm0, dword ptr [esi + 0x2a4]
008d35ad addss xmm0, dword ptr [esi + 0x294]
008d35b5 movss dword ptr [ebp - 0x34], xmm1
008d35ba movaps xmm1, xmm2
008d35bd addss xmm1, dword ptr [ebp - 0x30]
008d35c2 movss dword ptr [ebp - 0x28], xmm2
008d35c7 movss xmm2, dword ptr [0xbfec08]
008d35cf subss xmm2, dword ptr [0xb6ac30]
008d35d7 movss dword ptr [ebp - 0xd4], xmm0
008d35df addss xmm0, dword ptr [ebp - 0x14]
008d35e4 subss xmm1, dword ptr [0xb6ab44]
008d35ec mulss xmm3, xmm4
008d35f0 mulss xmm2, xmm4
008d35f4 mulss xmm1, dword ptr [0xb6a4dc]
008d35fc subss xmm0, dword ptr [0xb6aa8c]
008d3604 movss dword ptr [ebp - 0x88], xmm2
008d360c addss xmm1, xmm3
008d3610 movss dword ptr [ebp - 0x30], xmm3
008d3615 mulss xmm0, dword ptr [0xb6a4dc]
008d361d movss dword ptr [ebp - 0x20], xmm1
008d3622 movss xmm1, dword ptr [0xbaa554]
008d362a mulss xmm1, dword ptr [0xbaa920]
008d3632 addss xmm0, xmm2
008d3636 movss dword ptr [ebp - 0x24], xmm1
008d363b mulss xmm0, xmm1
008d363f addss xmm0, xmm4
008d3643 movss dword ptr [ebp - 0x14], xmm0
008d3648 fld dword ptr [ebp - 0x14]
008d364b fstp qword ptr [esp]
008d364e call 0x9ec3b2
008d3653 fstp dword ptr [ebp - 0x14]
008d3656 movss xmm0, dword ptr [ebp - 0x14]
008d365b divss xmm0, dword ptr [ebp - 0x24]
008d3660 movss dword ptr [ebp - 0x98], xmm0
008d3668 movss xmm0, dword ptr [ebp - 0x20]
008d366d mulss xmm0, dword ptr [ebp - 0x24]
008d3672 addss xmm0, dword ptr [0xb6a480]
008d367a movss dword ptr [ebp - 0x14], xmm0
008d367f fld dword ptr [ebp - 0x14]
008d3682 fstp qword ptr [esp]
008d3685 call 0x9ec3b2
008d368a movss xmm1, dword ptr [ebp - 0x1c]
008d368f fstp dword ptr [ebp - 0x14]
008d3692 movss xmm2, dword ptr [ebp - 0x14]
008d3697 divss xmm2, dword ptr [ebp - 0x24]
008d369c addss xmm1, dword ptr [ebp - 0x98]
008d36a4 movss xmm0, dword ptr [ebp - 0x34]
008d36a9 mov eax, dword ptr [ebp + 8]
008d36ac addss xmm0, xmm2
008d36b0 addss xmm1, dword ptr [eax]
008d36b4 addss xmm0, dword ptr [eax + 4]
008d36b9 addss xmm1, dword ptr [ebp - 0x68]
008d36be addss xmm0, dword ptr [ebp - 0x50]
008d36c3 movss dword ptr [ebp - 0x44], xmm1
008d36c8 movss dword ptr [ebp - 0x40], xmm0
008d36cd movss xmm0, dword ptr [ebp - 0x3c]
008d36d2 movaps xmm1, xmm0
008d36d5 mulss xmm0, dword ptr [ebp - 0x54]
008d36da mulss xmm1, dword ptr [ebp - 0x58]
008d36df addss xmm0, xmm2
008d36e3 addss xmm1, dword ptr [ebp - 0x98]
008d36eb addss xmm0, dword ptr [eax + 4]
008d36f0 addss xmm1, dword ptr [eax]
008d36f4 addss xmm0, dword ptr [ebp - 0x50]
008d36f9 addss xmm1, dword ptr [ebp - 0x68]
008d36fe movss dword ptr [ebp - 0x60], xmm0
008d3703 movss xmm0, dword ptr [ebp - 0xd4]
008d370b subss xmm0, dword ptr [0xb6aa8c]
008d3713 movss dword ptr [ebp - 0x64], xmm1
008d3718 movss xmm1, dword ptr [ebp - 0x28]
008d371d subss xmm1, dword ptr [0xb6ab44]
008d3725 mulss xmm0, dword ptr [0xb6a4dc]
008d372d mulss xmm1, dword ptr [0xb6a4dc]
008d3735 addss xmm0, dword ptr [ebp - 0x88]
008d373d addss xmm1, dword ptr [ebp - 0x30]
008d3742 mulss xmm0, dword ptr [ebp - 0x24]
008d3747 movss dword ptr [ebp - 0x28], xmm1
008d374c addss xmm0, dword ptr [0xb6a480]
008d3754 movss dword ptr [ebp - 0x14], xmm0
008d3759 fld dword ptr [ebp - 0x14]
008d375c fstp qword ptr [esp]
008d375f call 0x9ec3b2
008d3764 movss xmm2, dword ptr [ebp - 0x28]
008d3769 mulss xmm2, dword ptr [ebp - 0x24]
008d376e fstp dword ptr [ebp - 0x14]
008d3771 movss xmm0, dword ptr [ebp - 0x14]
008d3776 divss xmm0, dword ptr [ebp - 0x24]
008d377b addss xmm2, dword ptr [0xb6a480]
008d3783 movss dword ptr [ebp - 0x20], xmm0
008d3788 movss dword ptr [ebp - 0x14], xmm2
008d378d fld dword ptr [ebp - 0x14]
008d3790 fstp qword ptr [esp]
008d3793 call 0x9ec3b2
008d3798 fstp dword ptr [ebp - 0x14]
008d379b movss xmm0, dword ptr [ebp - 0x14]
008d37a0 add esp, 8
008d37a3 divss xmm0, dword ptr [ebp - 0x24]
008d37a8 mov eax, dword ptr [ebp + 8]
008d37ab movss xmm5, dword ptr [ebp - 0x34]
008d37b0 movss xmm1, dword ptr [ebp - 0x54]
008d37b5 addss xmm5, xmm0
008d37b9 mulss xmm1, dword ptr [ebp - 0x3c]
008d37be movss xmm4, dword ptr [ebp - 0x1c]
008d37c3 addss xmm4, dword ptr [ebp - 0x20]
008d37c8 addss xmm5, dword ptr [eax + 4]
008d37cd addss xmm1, xmm0
008d37d1 addss xmm4, dword ptr [eax]
008d37d5 addss xmm5, dword ptr [ebp - 0x50]
008d37da addss xmm1, dword ptr [eax + 4]
008d37df addss xmm4, dword ptr [ebp - 0x68]
008d37e4 movss dword ptr [ebp - 0xc8], xmm5
008d37ec movss xmm5, dword ptr [ebp - 0x58]
008d37f1 mulss xmm5, dword ptr [ebp - 0x3c]
008d37f6 addss xmm1, dword ptr [ebp - 0x50]
008d37fb movss dword ptr [ebp - 0xcc], xmm4
008d3803 addss xmm5, dword ptr [ebp - 0x20]
008d3808 movss dword ptr [ebp - 0xc0], xmm1
008d3810 addss xmm5, dword ptr [eax]
008d3814 lea eax, [ebp - 0x44]
008d3817 push eax
008d3818 lea eax, [ebp - 0x64]
008d381b push eax
008d381c addss xmm5, dword ptr [ebp - 0x68]
008d3821 lea eax, [ebp - 0xcc]
008d3827 push eax
008d3828 movss dword ptr [ebp - 0xc4], xmm5
008d3830 lea eax, [ebp - 0xc4]
008d3836 push eax
008d3837 lea ecx, [ebp - 0x1bc]
008d383d call 0x95e620
008d3842 cmp dword ptr [edi + 0x80], 0
008d3849 jg 0x8d3867
008d384b cmp dword ptr [edi + 0x14], 0x10
008d384f mov eax, edi
008d3851 jb 0x8d3855
008d3853 mov eax, dword ptr [edi]
008d3855 push 0
008d3857 push eax
008d3858 push 0xa0830c
008d385d push 3
008d385f call 0x95e330
008d3864 add esp, 0x10
008d3867 mov eax, dword ptr [edi + 0x7c]
008d386a xor ecx, ecx
008d386c cmp byte ptr [ebp - 0xa4], cl
008d3872 movups xmm1, xmmword ptr [eax + 0x78]
008d3876 mov eax, 0x3c
008d387b cmove eax, ecx
008d387e sub esp, 0x2c
008d3881 movaps xmm0, xmm1
008d3884 movd dword ptr [0xbc7a34], xmm1
008d388c psrldq xmm0, 4
008d3891 mov ecx, esp
008d3893 movd dword ptr [0xbc7a38], xmm0
008d389b movaps xmm0, xmm1
008d389e mov eax, dword ptr [eax + 0xa08910]
008d38a4 mov dword ptr [0xbc7a44], eax
008d38a9 lea eax, [esi + 0xe4]
008d38af psrldq xmm0, 8
008d38b4 psrldq xmm1, 0xc
008d38b9 push eax
008d38ba movd dword ptr [0xbc7a3c], xmm0
008d38c2 movd dword ptr [0xbc7a40], xmm1
008d38ca call 0x402170
008d38cf lea edx, [ebp - 0x16c]
008d38d5 lea ecx, [ebp - 0x130]
008d38db call 0x402290
008d38e0 add esp, 0x2c
008d38e3 cmp byte ptr [ebp - 0xa4], 0
008d38ea je 0x8d391c
008d38ec mov eax, dword ptr [0xbfd65c]
008d38f1 mov eax, dword ptr [eax + 0x1a30dc]
008d38f7 and eax, 0x800000ff
008d38fc jns 0x8d3905
008d38fe dec eax
008d38ff or eax, 0xffffff00
008d3904 inc eax
008d3905 movd xmm0, eax
008d3909 cvtdq2ps xmm0, xmm0
008d390c mulss xmm0, dword ptr [0xb6a1f0]
008d3914 movss dword ptr [ebp - 0x114], xmm0
008d391c cmp dword ptr [edi + 0x80], 0
008d3923 jg 0x8d3941
008d3925 cmp dword ptr [edi + 0x14], 0x10
008d3929 mov eax, edi
008d392b jb 0x8d392f
008d392d mov eax, dword ptr [edi]
008d392f push 0
008d3931 push eax
008d3932 push 0xa0830c
008d3937 push 3
008d3939 call 0x95e330
008d393e add esp, 0x10
008d3941 mov eax, dword ptr [edi + 0x7c]
008d3944 mov dword ptr [eax + 0x28], 0
008d394b cmp dword ptr [edi + 0x80], 0
008d3952 jg 0x8d3970
008d3954 cmp dword ptr [edi + 0x14], 0x10
008d3958 mov eax, edi
008d395a jb 0x8d395e
008d395c mov eax, dword ptr [edi]
008d395e push 0
008d3960 push eax
008d3961 push 0xa0830c
008d3966 push 3
008d3968 call 0x95e330
008d396d add esp, 0x10
008d3970 mov eax, dword ptr [edi + 0x7c]
008d3973 mov dword ptr [eax + 0x2c], 0
008d397a cmp dword ptr [edi + 0x80], 0
008d3981 jg 0x8d399f
008d3983 cmp dword ptr [edi + 0x14], 0x10
008d3987 mov eax, edi
008d3989 jb 0x8d398d
008d398b mov eax, dword ptr [edi]
008d398d push 0
008d398f push eax
008d3990 push 0xa0830c
008d3995 push 3
008d3997 call 0x95e330
008d399c add esp, 0x10
008d399f mov ecx, dword ptr [edi + 0x7c]
008d39a2 lea eax, [ebp - 0x44]
008d39a5 push eax
008d39a6 call 0x403540
008d39ab mov dword ptr [ebp - 4], 6
008d39b2 mov ecx, dword ptr [eax]
008d39b4 lea edx, [ebp - 0xbc]
008d39ba movups xmm0, xmmword ptr [ebp - 0x130]
008d39c1 push edx
008d39c2 lea edx, [ebp - 0x1bc]
008d39c8 movups xmmword ptr [ebp - 0xbc], xmm0
008d39cf mov eax, dword ptr [ecx]
008d39d1 push edx
008d39d2 lea edx, [ebp - 0x104]
008d39d8 push edx
008d39d9 mov eax, dword ptr [eax + 0xc]
008d39dc call eax
008d39de lea ecx, [ebp - 0x44]
008d39e1 mov dword ptr [ebp - 0x1c], eax
008d39e4 mov dword ptr [ebp - 4], 0xffffffff
008d39eb call 0x407790
008d39f0 cmp dword ptr [ebp - 0x1c], 0
008d39f4 je 0x8d3a35
008d39f6 cmp dword ptr [edi + 0x80], 0
008d39fd jg 0x8d3a1b
008d39ff cmp dword ptr [edi + 0x14], 0x10
008d3a03 mov eax, edi
008d3a05 jb 0x8d3a09
008d3a07 mov eax, dword ptr [edi]
008d3a09 push 0
008d3a0b push eax
008d3a0c push 0xa0830c
008d3a11 push 3
008d3a13 call 0x95e330
008d3a18 add esp, 0x10
008d3a1b mov ecx, dword ptr [edi + 0x7c]
008d3a1e sub esp, 8
008d3a21 push esp
008d3a22 call 0x403540
008d3a27 push dword ptr [ebp - 0x1c]
008d3a2a lea ecx, [ebp - 0x130]
008d3a30 call 0x65af60
008d3a35 mov ecx, dword ptr [ebp + 8]
008d3a38 push ecx
008d3a39 push esi
008d3a3a call 0x7fde40
008d3a3f mov eax, dword ptr [0xbfd65c]
008d3a44 test byte ptr [eax + 0x1c3164], 1
008d3a4b je 0x8d4136
008d3a51 movss xmm1, dword ptr [0xbfec08]
008d3a59 sub esp, 8
008d3a5c subss xmm1, dword ptr [0xb6ac30]
008d3a64 movss xmm0, dword ptr [esi + 0x294]
008d3a6c subss xmm0, dword ptr [0xb6aa8c]
008d3a74 movss xmm2, dword ptr [0xbaa554]
008d3a7c mulss xmm2, dword ptr [0xbaa920]
008d3a84 mulss xmm1, dword ptr [0xb6a480]
008d3a8c mulss xmm0, dword ptr [0xb6a4dc]
008d3a94 movss dword ptr [ebp - 0x1c], xmm2
008d3a99 addss xmm1, xmm0
008d3a9d mulss xmm1, xmm2
008d3aa1 addss xmm1, dword ptr [0xb6a480]
008d3aa9 movss dword ptr [ebp - 0x14], xmm1
008d3aae fld dword ptr [ebp - 0x14]
008d3ab1 fstp qword ptr [esp]
008d3ab4 call 0x9ec3b2
008d3ab9 fstp dword ptr [ebp - 0x14]
008d3abc fld dword ptr [ebp - 0x14]
008d3abf fstp dword ptr [ebp - 0x14]
008d3ac2 movss xmm0, dword ptr [ebp - 0x14]
008d3ac7 divss xmm0, dword ptr [ebp - 0x1c]
008d3acc movss xmm1, dword ptr [esi + 0x298]
008d3ad4 subss xmm1, dword ptr [0xb6ab44]
008d3adc movss dword ptr [ebp - 0x30], xmm0
008d3ae1 movss xmm0, dword ptr [0xbfec68]
008d3ae9 subss xmm0, dword ptr [0xb6ab8c]
008d3af1 mulss xmm1, dword ptr [0xb6a4dc]
008d3af9 mulss xmm0, dword ptr [0xb6a480]
008d3b01 addss xmm1, xmm0
008d3b05 mulss xmm1, dword ptr [ebp - 0x1c]
008d3b0a addss xmm1, dword ptr [0xb6a480]
008d3b12 movss dword ptr [ebp - 0x14], xmm1
008d3b17 fld dword ptr [ebp - 0x14]
008d3b1a fstp qword ptr [esp]
008d3b1d call 0x9ec3b2
008d3b22 fstp dword ptr [ebp - 0x14]
008d3b25 fld dword ptr [ebp - 0x14]
008d3b28 lea ecx, [ebp - 0xbc]
008d3b2e fstp dword ptr [ebp - 0x14]
008d3b31 movss xmm2, dword ptr [ebp - 0x14]
008d3b36 add esp, 8
008d3b39 divss xmm2, dword ptr [ebp - 0x1c]
008d3b3e mov dword ptr [ebp - 0x14], 0x3f800000
008d3b45 push 0xffffa500
008d3b4a movss dword ptr [ebp - 0x20], xmm2
008d3b4f call 0x960b80
008d3b54 movss xmm0, dword ptr [ebp - 0x30]
008d3b59 lea eax, [ebp - 0x14]
008d3b5c addss xmm0, dword ptr [0xb6a7b0]
008d3b64 xorps xmm4, xmm4
008d3b67 push eax
008d3b68 mov eax, ecx
008d3b6a push eax
008d3b6b movss dword ptr [ebp - 0x44], xmm0
008d3b70 movaps xmm0, xmm2
008d3b73 addss xmm0, xmm4
008d3b77 push eax
008d3b78 lea eax, [ebp - 0x44]
008d3b7b push eax
008d3b7c lea eax, [ebp - 0x64]
008d3b7f movss dword ptr [ebp - 0x40], xmm0
008d3b84 movss xmm0, dword ptr [ebp - 0x30]
008d3b89 subss xmm0, dword ptr [0xb6a7b0]
008d3b91 push eax
008d3b92 movss dword ptr [ebp - 0x64], xmm0
008d3b97 movaps xmm0, xmm2
008d3b9a subss xmm0, xmm4
008d3b9e movss dword ptr [ebp - 0x60], xmm0
008d3ba3 call 0x965520
008d3ba8 push 0xffffa500
008d3bad lea ecx, [ebp - 0xbc]
008d3bb3 mov dword ptr [ebp - 0x14], 0x3f800000
008d3bba call 0x960b80
008d3bbf movss xmm2, dword ptr [ebp - 0x30]
008d3bc4 xorps xmm4, xmm4
008d3bc7 movss xmm1, dword ptr [ebp - 0x20]
008d3bcc movaps xmm0, xmm2
008d3bcf addss xmm0, xmm4
008d3bd3 movss dword ptr [ebp - 0x44], xmm0
008d3bd8 movaps xmm0, xmm1
008d3bdb addss xmm0, dword ptr [0xb6a7b0]
008d3be3 subss xmm1, dword ptr [0xb6a7b0]
008d3beb lea eax, [ebp - 0x14]
008d3bee push eax
008d3bef mov eax, ecx
008d3bf1 subss xmm2, xmm4
008d3bf5 push eax
008d3bf6 push eax
008d3bf7 lea eax, [ebp - 0x44]
008d3bfa movss dword ptr [ebp - 0x40], xmm0
008d3bff push eax
008d3c00 lea eax, [ebp - 0x64]
008d3c03 movss dword ptr [ebp - 0x64], xmm2
008d3c08 push eax
008d3c09 movss dword ptr [ebp - 0x60], xmm1
008d3c0e call 0x965520
008d3c13 cmp byte ptr [esi + 0x3ad], 0
008d3c1a je 0x8d4136
008d3c20 mov eax, dword ptr [esi + 0x3d4]
008d3c26 xor ecx, ecx
008d3c28 mov edi, dword ptr [esi + 0x3d0]
008d3c2e sub eax, edi
008d3c30 sar eax, 3
008d3c33 mov dword ptr [ebp - 0x30], ecx
008d3c36 test eax, eax
008d3c38 je 0x8d3eb6
008d3c3e mov dword ptr [ebp - 0x20], 0x3f733333
008d3c45 mov dword ptr [ebp - 0x98], 0x3f733333
008d3c4f nop 
008d3c50 movss xmm1, dword ptr [0xbfec08]
008d3c58 sub esp, 8
008d3c5b subss xmm1, dword ptr [0xb6ac30]
008d3c63 movss xmm0, dword ptr [edi + ecx*8]
008d3c68 subss xmm0, dword ptr [0xb6aa8c]
008d3c70 movss xmm2, dword ptr [0xbaa554]
008d3c78 mulss xmm2, dword ptr [0xbaa920]
008d3c80 mulss xmm1, dword ptr [0xb6a480]
008d3c88 mulss xmm0, dword ptr [0xb6a4dc]
008d3c90 movss dword ptr [ebp - 0x1c], xmm2
008d3c95 addss xmm1, xmm0
008d3c99 mulss xmm1, xmm2
008d3c9d addss xmm1, dword ptr [0xb6a480]
008d3ca5 movss dword ptr [ebp - 0x14], xmm1
008d3caa fld dword ptr [ebp - 0x14]
008d3cad fstp qword ptr [esp]
008d3cb0 call 0x9ec3b2
008d3cb5 fstp dword ptr [ebp - 0x14]
008d3cb8 fld dword ptr [ebp - 0x14]
008d3cbb fstp dword ptr [ebp - 0x14]
008d3cbe movss xmm0, dword ptr [ebp - 0x14]
008d3cc3 divss xmm0, dword ptr [ebp - 0x1c]
008d3cc8 mov eax, dword ptr [ebp - 0x30]
008d3ccb movss xmm1, dword ptr [0xbfec68]
008d3cd3 subss xmm1, dword ptr [0xb6ab8c]
008d3cdb movss dword ptr [ebp - 0x28], xmm0
008d3ce0 movss xmm0, dword ptr [edi + eax*8 + 4]
008d3ce6 subss xmm0, dword ptr [0xb6ab44]
008d3cee mulss xmm1, dword ptr [0xb6a480]
008d3cf6 mulss xmm0, dword ptr [0xb6a4dc]
008d3cfe addss xmm1, xmm0
008d3d02 mulss xmm1, dword ptr [ebp - 0x1c]
008d3d07 addss xmm1, dword ptr [0xb6a480]
008d3d0f movss dword ptr [ebp - 0x14], xmm1
008d3d14 fld dword ptr [ebp - 0x14]
008d3d17 fstp qword ptr [esp]
008d3d1a call 0x9ec3b2
008d3d1f fstp dword ptr [ebp - 0x14]
008d3d22 fld dword ptr [ebp - 0x14]
008d3d25 lea ecx, [ebp - 0xbc]
008d3d2b fstp dword ptr [ebp - 0x14]
008d3d2e movss xmm2, dword ptr [ebp - 0x14]
008d3d33 add esp, 8
008d3d36 divss xmm2, dword ptr [ebp - 0x1c]
008d3d3b push -1
008d3d3d movss dword ptr [ebp - 0x14], xmm2
008d3d42 call 0x960b80
008d3d47 movss xmm0, dword ptr [ebp - 0x28]
008d3d4c lea eax, [ebp - 0x20]
008d3d4f addss xmm0, dword ptr [0xb6a7b0]
008d3d57 xorps xmm4, xmm4
008d3d5a push eax
008d3d5b mov eax, ecx
008d3d5d push eax
008d3d5e movss dword ptr [ebp - 0x44], xmm0
008d3d63 movaps xmm0, xmm2
008d3d66 addss xmm0, xmm4
008d3d6a push eax
008d3d6b lea eax, [ebp - 0x44]
008d3d6e push eax
008d3d6f lea eax, [ebp - 0x64]
008d3d72 movss dword ptr [ebp - 0x40], xmm0
008d3d77 movss xmm0, dword ptr [ebp - 0x28]
008d3d7c subss xmm0, dword ptr [0xb6a7b0]
008d3d84 push eax
008d3d85 movss dword ptr [ebp - 0x64], xmm0
008d3d8a movaps xmm0, xmm2
008d3d8d subss xmm0, xmm4
008d3d91 movss dword ptr [ebp - 0x60], xmm0
008d3d96 call 0x965520
008d3d9b test eax, eax
008d3d9d je 0x8d3ddf
008d3d9f movss xmm1, dword ptr [0xb6a614]
008d3da7 movss xmm0, dword ptr [eax + 8]
008d3dac subss xmm0, xmm1
008d3db0 movss dword ptr [eax + 8], xmm0
008d3db5 movss xmm0, dword ptr [eax + 0x24]
008d3dba subss xmm0, xmm1
008d3dbe movss dword ptr [eax + 0x24], xmm0
008d3dc3 movss xmm0, dword ptr [eax + 0x40]
008d3dc8 subss xmm0, xmm1
008d3dcc movss dword ptr [eax + 0x40], xmm0
008d3dd1 movss xmm0, dword ptr [eax + 0x5c]
008d3dd6 subss xmm0, xmm1
008d3dda movss dword ptr [eax + 0x5c], xmm0
008d3ddf push -1
008d3de1 lea ecx, [ebp - 0x80]
008d3de4 call 0x960b80
008d3de9 movss xmm1, dword ptr [ebp - 0x28]
008d3dee lea eax, [ebp - 0x98]
008d3df4 movss xmm2, dword ptr [ebp - 0x14]
008d3df9 movaps xmm0, xmm1
008d3dfc xorps xmm4, xmm4
008d3dff push eax
008d3e00 addss xmm0, xmm4
008d3e04 mov eax, ecx
008d3e06 push eax
008d3e07 push eax
008d3e08 subss xmm1, xmm4
008d3e0c lea eax, [ebp - 0xcc]
008d3e12 movss dword ptr [ebp - 0xcc], xmm0
008d3e1a movaps xmm0, xmm2
008d3e1d addss xmm0, dword ptr [0xb6a7b0]
008d3e25 subss xmm2, dword ptr [0xb6a7b0]
008d3e2d push eax
008d3e2e lea eax, [ebp - 0xc4]
008d3e34 movss dword ptr [ebp - 0xc4], xmm1
008d3e3c push eax
008d3e3d movss dword ptr [ebp - 0xc8], xmm0
008d3e45 movss dword ptr [ebp - 0xc0], xmm2
008d3e4d call 0x965520
008d3e52 test eax, eax
008d3e54 je 0x8d3e96
008d3e56 movss xmm1, dword ptr [0xb6a614]
008d3e5e movss xmm0, dword ptr [eax + 8]
008d3e63 subss xmm0, xmm1
008d3e67 movss dword ptr [eax + 8], xmm0
008d3e6c movss xmm0, dword ptr [eax + 0x24]
008d3e71 subss xmm0, xmm1
008d3e75 movss dword ptr [eax + 0x24], xmm0
008d3e7a movss xmm0, dword ptr [eax + 0x40]
008d3e7f subss xmm0, xmm1
008d3e83 movss dword ptr [eax + 0x40], xmm0
008d3e88 movss xmm0, dword ptr [eax + 0x5c]
008d3e8d subss xmm0, xmm1
008d3e91 movss dword ptr [eax + 0x5c], xmm0
008d3e96 mov eax, dword ptr [esi + 0x3d4]
008d3e9c mov ecx, dword ptr [ebp - 0x30]
008d3e9f mov edi, dword ptr [esi + 0x3d0]
008d3ea5 inc ecx
008d3ea6 sub eax, edi
008d3ea8 mov dword ptr [ebp - 0x30], ecx
008d3eab sar eax, 3
008d3eae cmp ecx, eax
008d3eb0 jb 0x8d3c50
008d3eb6 movss xmm1, dword ptr [0xbaa554]
008d3ebe movss xmm0, dword ptr [esi + 0x36c]
008d3ec6 mulss xmm0, dword ptr [0xb6a230]
008d3ece mulss xmm1, dword ptr [0xbaa920]
008d3ed6 movss dword ptr [ebp - 0x20], xmm0
008d3edb movss dword ptr [ebp - 0x24], xmm1
008d3ee0 call 0x411fe0
008d3ee5 mulss xmm0, dword ptr [0xb6a9b0]
008d3eed sub esp, 8
008d3ef0 movss xmm1, dword ptr [edi]
008d3ef4 subss xmm1, xmm0
008d3ef8 movss xmm0, dword ptr [0xbfec08]
008d3f00 subss xmm0, dword ptr [0xb6ac30]
008d3f08 subss xmm1, dword ptr [0xb6aa8c]
008d3f10 mulss xmm0, dword ptr [0xb6a480]
008d3f18 mulss xmm1, dword ptr [0xb6a4dc]
008d3f20 addss xmm1, xmm0
008d3f24 mulss xmm1, dword ptr [ebp - 0x24]
008d3f29 addss xmm1, dword ptr [0xb6a480]
008d3f31 movss dword ptr [ebp - 0x14], xmm1
008d3f36 fld dword ptr [ebp - 0x14]
008d3f39 fstp qword ptr [esp]
008d3f3c call 0x9ec3b2
008d3f41 fstp dword ptr [ebp - 0x14]
008d3f44 fld dword ptr [ebp - 0x14]
008d3f47 fstp dword ptr [ebp - 0x14]
008d3f4a movss xmm0, dword ptr [ebp - 0x14]
008d3f4f divss xmm0, dword ptr [ebp - 0x24]
008d3f54 movss dword ptr [ebp - 0x1c], xmm0
008d3f59 movss xmm0, dword ptr [ebp - 0x20]
008d3f5e call 0x412010
008d3f63 mulss xmm0, dword ptr [0xb6a9b0]
008d3f6b movss xmm1, dword ptr [edi + 4]
008d3f70 subss xmm1, xmm0
008d3f74 movss xmm0, dword ptr [0xbfec68]
008d3f7c subss xmm0, dword ptr [0xb6ab8c]
008d3f84 subss xmm1, dword ptr [0xb6ab44]
008d3f8c mulss xmm0, dword ptr [0xb6a480]
008d3f94 mulss xmm1, dword ptr [0xb6a4dc]
008d3f9c addss xmm1, xmm0
008d3fa0 mulss xmm1, dword ptr [ebp - 0x24]
008d3fa5 addss xmm1, dword ptr [0xb6a480]
008d3fad movss dword ptr [ebp - 0x14], xmm1
008d3fb2 fld dword ptr [ebp - 0x14]
008d3fb5 fstp qword ptr [esp]
008d3fb8 call 0x9ec3b2
008d3fbd fstp dword ptr [ebp - 0x14]
008d3fc0 fld dword ptr [ebp - 0x14]
008d3fc3 lea ecx, [ebp - 0xbc]
008d3fc9 fstp dword ptr [ebp - 0x14]
008d3fcc movss xmm4, dword ptr [ebp - 0x14]
008d3fd1 add esp, 8
008d3fd4 divss xmm4, dword ptr [ebp - 0x24]
008d3fd9 mov dword ptr [ebp - 0x14], 0x3f733333
008d3fe0 push 0xffadff2f
008d3fe5 movss dword ptr [ebp - 0x20], xmm4
008d3fea call 0x960b80
008d3fef movss xmm0, dword ptr [ebp - 0x1c]
008d3ff4 lea eax, [ebp - 0x14]
008d3ff7 addss xmm0, dword ptr [0xb6a7b0]
008d3fff xorps xmm2, xmm2
008d4002 push eax
008d4003 mov eax, ecx
008d4005 push eax
008d4006 movss dword ptr [ebp - 0x44], xmm0
008d400b movaps xmm0, xmm4
008d400e addss xmm0, xmm2
008d4012 push eax
008d4013 lea eax, [ebp - 0x44]
008d4016 push eax
008d4017 lea eax, [ebp - 0x64]
008d401a movss dword ptr [ebp - 0x40], xmm0
008d401f movss xmm0, dword ptr [ebp - 0x1c]
008d4024 subss xmm0, dword ptr [0xb6a7b0]
008d402c push eax
008d402d movss dword ptr [ebp - 0x64], xmm0
008d4032 movaps xmm0, xmm4
008d4035 subss xmm0, xmm2
008d4039 movss dword ptr [ebp - 0x60], xmm0
008d403e call 0x965520
008d4043 test eax, eax
008d4045 je 0x8d4087
008d4047 movss xmm1, dword ptr [0xb6a614]
008d404f movss xmm0, dword ptr [eax + 8]
008d4054 subss xmm0, xmm1
008d4058 movss dword ptr [eax + 8], xmm0
008d405d movss xmm0, dword ptr [eax + 0x24]
008d4062 subss xmm0, xmm1
008d4066 movss dword ptr [eax + 0x24], xmm0
008d406b movss xmm0, dword ptr [eax + 0x40]
008d4070 subss xmm0, xmm1
008d4074 movss dword ptr [eax + 0x40], xmm0
008d4079 movss xmm0, dword ptr [eax + 0x5c]
008d407e subss xmm0, xmm1
008d4082 movss dword ptr [eax + 0x5c], xmm0
008d4087 push 0xffadff2f
008d408c lea ecx, [ebp - 0xe0]
008d4092 mov dword ptr [ebp - 0x14], 0x3f733333
008d4099 call 0x960b80
008d409e movss xmm3, dword ptr [ebp - 0x1c]
008d40a3 lea eax, [ebp - 0x14]
008d40a6 movss xmm4, dword ptr [ebp - 0x20]
008d40ab movaps xmm0, xmm3
008d40ae xorps xmm2, xmm2
008d40b1 push eax
008d40b2 addss xmm0, xmm2
008d40b6 mov eax, ecx
008d40b8 push eax
008d40b9 push eax
008d40ba subss xmm3, xmm2
008d40be lea eax, [ebp - 0x44]
008d40c1 movss dword ptr [ebp - 0x44], xmm0
008d40c6 movaps xmm0, xmm4
008d40c9 addss xmm0, dword ptr [0xb6a7b0]
008d40d1 subss xmm4, dword ptr [0xb6a7b0]
008d40d9 push eax
008d40da lea eax, [ebp - 0x64]
008d40dd movss dword ptr [ebp - 0x64], xmm3
008d40e2 push eax
008d40e3 movss dword ptr [ebp - 0x40], xmm0
008d40e8 movss dword ptr [ebp - 0x60], xmm4
008d40ed call 0x965520
008d40f2 test eax, eax
008d40f4 je 0x8d4136
008d40f6 movss xmm1, dword ptr [0xb6a614]
008d40fe movss xmm0, dword ptr [eax + 8]
008d4103 subss xmm0, xmm1
008d4107 movss dword ptr [eax + 8], xmm0
008d410c movss xmm0, dword ptr [eax + 0x24]
008d4111 subss xmm0, xmm1
008d4115 movss dword ptr [eax + 0x24], xmm0
008d411a movss xmm0, dword ptr [eax + 0x40]
008d411f subss xmm0, xmm1
008d4123 movss dword ptr [eax + 0x40], xmm0
008d4128 movss xmm0, dword ptr [eax + 0x5c]
008d412d subss xmm0, xmm1
008d4131 movss dword ptr [eax + 0x5c], xmm0
008d4136 mov ecx, dword ptr [ebp - 0xc]
008d4139 mov dword ptr fs:[0], ecx
008d4140 pop ecx
008d4141 pop edi
008d4142 pop esi
008d4143 mov ecx, dword ptr [ebp - 0x10]
008d4146 xor ecx, ebp
008d4148 call 0x9eacd7
008d414d mov esp, ebp
008d414f pop ebp
008d4150 ret 4
008d4153 int3 
008d4154 int3 
008d4155 int3 
008d4156 int3 
008d4157 int3 
008d4158 int3 
008d4159 int3 
008d415a int3 
008d415b int3 
008d415c int3 
008d415d int3 
008d415e int3 
008d415f int3 
008d4160 push ebx
008d4161 mov ebx, esp
008d4163 sub esp, 8
008d4166 and esp, 0xfffffff8
008d4169 add esp, 4
008d416c push ebp
008d416d mov ebp, dword ptr [ebx + 4]
008d4170 mov dword ptr [esp + 4], ebp
008d4174 mov ebp, esp
008d4176 push -1
008d4178 push 0x9ff8e5
008d417d mov eax, dword ptr fs:[0]
008d4183 push eax
008d4184 push ebx
008d4185 sub esp, 0xc8
008d418b mov eax, dword ptr [0xbaa3b4]
008d4190 xor eax, ebp
008d4192 mov dword ptr [ebp - 0x14], eax
008d4195 push esi
008d4196 push edi
008d4197 push eax
008d4198 lea eax, [ebp - 0xc]
008d419b mov dword ptr fs:[0], eax
008d41a1 mov edi, ecx
008d41a3 call 0x8cc120
008d41a8 mov al, byte ptr [edi + 0x3ac]
008d41ae test al, al
008d41b0 jne 0x8d41ba
008d41b2 cmp byte ptr [edi + 0x465], al
008d41b8 jne 0x8d41c8
008d41ba movups xmm0, xmmword ptr [edi + 0x378]
008d41c1 movups xmmword ptr [edi + 0x388], xmm0
008d41c8 cmp byte ptr [edi + 0x16b], 0
008d41cf jne 0x8d4215
008d41d1 cmp byte ptr [edi + 0x16d], 0
008d41d8 jne 0x8d4215
008d41da cmp dword ptr [edi + 0x2c], 8
008d41de je 0x8d4215
008d41e0 test al, al
008d41e2 jne 0x8d41fa
008d41e4 movss xmm1, dword ptr [0xb6a7b0]
008d41ec xorps xmm2, xmm2
008d41ef mov ecx, edi
008d41f1 call 0x6847e0
008d41f6 test eax, eax
008d41f8 je 0x8d4215
008d41fa cmp dword ptr [edi + 0x47c], 0
008d4201 mov byte ptr [ebp - 0x35], 1
008d4205 jne 0x8d4219
008d4207 mov eax, dword ptr [edi + 0x470]
008d420d mov dword ptr [edi + 0x474], eax
008d4213 jmp 0x8d4219
008d4215 mov byte ptr [ebp - 0x35], 0
008d4219 cmp byte ptr [edi + 0x16d], 0
008d4220 movss xmm1, dword ptr [0xb6a560]
008d4228 jne 0x8d4244
008d422a cmp dword ptr [edi + 0x30], 1
008d422e jne 0x8d4244
008d4230 movss xmm0, dword ptr [edi + 0x2c4]
008d4238 mulss xmm0, xmm1
008d423c movss dword ptr [edi + 0x2c4], xmm0
008d4244 mov eax, dword ptr [edi + 0x3fc]
008d424a lea esi, [edi + 0x294]
008d4250 movss xmm1, dword ptr [0xb6a614]
008d4258 mov dword ptr [edi + 0x400], eax
008d425e mov eax, dword ptr [esi]
008d4260 mov dword ptr [edi + 0x3b8], eax
008d4266 mov eax, dword ptr [esi + 4]
008d4269 mov dword ptr [edi + 0x3bc], eax
008d426f movss xmm0, dword ptr [0xc02fec]
008d4277 movss dword ptr [edi + 0x3c0], xmm0
008d427f movss xmm0, dword ptr [0xc02ff0]
008d4287 movss dword ptr [edi + 0x3c4], xmm0
008d428f movss xmm0, dword ptr [edi + 0x40c]
008d4297 mov eax, dword ptr [edi + 0x314]
008d429d movss dword ptr [ebp - 0x34], xmm0
008d42a2 movss dword ptr [ebp - 0x3c], xmm1
008d42a7 movss dword ptr [ebp - 0x5c], xmm1
008d42ac test eax, eax
008d42ae je 0x8d42c3
008d42b0 cmp dword ptr [eax + 0x28], 3
008d42b4 jne 0x8d42c3
008d42b6 mulss xmm0, dword ptr [0xb6a53c]
008d42be movss dword ptr [ebp - 0x34], xmm0
008d42c3 mov eax, dword ptr [edi + 0x320]
008d42c9 mov dword ptr [ebp - 0x40], eax
008d42cc test eax, eax
008d42ce je 0x8d42dc
008d42d0 xor ecx, ecx
008d42d2 cmp dword ptr [eax + 0x28], 1
008d42d6 cmovne eax, ecx
008d42d9 mov dword ptr [ebp - 0x40], eax
008d42dc lea edx, [edi + 0x378]
008d42e2 push 0xbc49f0
008d42e7 lea ecx, [ebp - 0xb0]
008d42ed call 0x412050
008d42f2 add esp, 4
008d42f5 mov ecx, dword ptr [eax]
008d42f7 or ecx, dword ptr [eax + 4]
008d42fa jne 0x8d4304
008d42fc mov ecx, dword ptr [eax + 8]
008d42ff or ecx, dword ptr [eax + 0xc]
008d4302 je 0x8d432b
008d4304 movss xmm0, dword ptr [edi + 0x2fc]
008d430c mulss xmm0, dword ptr [0xb6a2cc]
008d4314 call 0x412010
008d4319 mulss xmm0, dword ptr [0xb6a9c8]
008d4321 addss xmm0, dword ptr [ebp - 0x34]
008d4326 movss dword ptr [ebp - 0x34], xmm0
008d432b cmp dword ptr [edi + 0x30], 3
008d432f jne 0x8d4340
008d4331 mov eax, dword ptr [edi + 0x314]
008d4337 cmp eax, dword ptr [ebp - 0x40]
008d433a je 0x8d44b7
008d4340 push 0xbc4bc0
008d4345 lea edx, [edi + 0x378]
008d434b lea ecx, [ebp - 0x58]
008d434e call 0x412050
008d4353 movss xmm1, dword ptr [0xb6ac8c]
008d435b add esp, 4
008d435e mov ecx, dword ptr [eax]
008d4360 or ecx, dword ptr [eax + 4]
008d4363 jne 0x8d436d
008d4365 mov ecx, dword ptr [eax + 8]
008d4368 or ecx, dword ptr [eax + 0xc]
008d436b je 0x8d43e4
008d436d mov eax, dword ptr [ebp - 0x40]
008d4370 test eax, eax
008d4372 je 0x8d43ad
008d4374 movss xmm1, dword ptr [eax + 0x294]
008d437c movss xmm0, dword ptr [eax + 0x298]
008d4384 subss xmm0, dword ptr [esi + 4]
008d4389 subss xmm1, dword ptr [esi]
008d438d mulss xmm0, xmm0
008d4391 mulss xmm1, xmm1
008d4395 addss xmm0, xmm1
008d4399 call 0x4228c0
008d439e movss xmm1, dword ptr [0xb6ac8c]
008d43a6 movss dword ptr [ebp - 0x60], xmm0
008d43ab jmp 0x8d43b7
008d43ad mov dword ptr [ebp - 0x60], 0
008d43b4 xorps xmm0, xmm0
008d43b7 comiss xmm0, xmm1
008d43ba lea eax, [ebp - 0x4c]
008d43bd mov dword ptr [ebp - 0x4c], 0x43fa0000
008d43c4 lea ecx, [ebp - 0x60]
008d43c7 cmovbe eax, ecx
008d43ca movss xmm0, dword ptr [eax]
008d43ce mulss xmm0, dword ptr [0xb6aa60]
008d43d6 divss xmm0, xmm1
008d43da addss xmm0, dword ptr [ebp - 0x34]
008d43df movss dword ptr [ebp - 0x34], xmm0
008d43e4 push 0xbc4c60
008d43e9 lea edx, [edi + 0x378]
008d43ef lea ecx, [ebp - 0x28]
008d43f2 call 0x412050
008d43f7 add esp, 4
008d43fa mov ecx, dword ptr [eax]
008d43fc or ecx, dword ptr [eax + 4]
008d43ff jne 0x8d440d
008d4401 mov ecx, dword ptr [eax + 8]
008d4404 or ecx, dword ptr [eax + 0xc]
008d4407 je 0x8d4496
008d440d mov eax, dword ptr [ebp - 0x40]
008d4410 test eax, eax
008d4412 je 0x8d444d
008d4414 movss xmm1, dword ptr [eax + 0x294]
008d441c movss xmm0, dword ptr [eax + 0x298]
008d4424 subss xmm0, dword ptr [esi + 4]
008d4429 subss xmm1, dword ptr [esi]
008d442d mulss xmm0, xmm0
008d4431 mulss xmm1, xmm1
008d4435 addss xmm0, xmm1
008d4439 call 0x4228c0
008d443e movss xmm1, dword ptr [0xb6ac8c]
008d4446 movss dword ptr [ebp - 0x60], xmm0
008d444b jmp 0x8d4457
008d444d mov dword ptr [ebp - 0x60], 0
008d4454 xorps xmm0, xmm0
008d4457 comiss xmm0, xmm1
008d445a lea eax, [ebp - 0x4c]
008d445d mov dword ptr [ebp - 0x4c], 0x43fa0000
008d4464 lea ecx, [ebp - 0x60]
008d4467 movss xmm3, dword ptr [ebp - 0x3c]
008d446c cmovbe eax, ecx
008d446f movss xmm0, dword ptr [eax]
008d4473 divss xmm0, xmm1
008d4477 movaps xmm1, xmm3
008d447a subss xmm1, xmm0
008d447e movss xmm0, dword ptr [ebp - 0x34]
008d4483 mulss xmm1, dword ptr [0xb6aa60]
008d448b addss xmm0, xmm1
008d448f movss dword ptr [ebp - 0x34], xmm0
008d4494 jmp 0x8d449b
008d4496 movss xmm3, dword ptr [ebp - 0x3c]
008d449b mov eax, dword ptr [edi + 0x30]
008d449e cmp eax, 2
008d44a1 je 0x8d44eb
008d44a3 movss dword ptr [ebp - 0x34], xmm0
008d44a8 cmp eax, 3
008d44ab jne 0x8d4a61
008d44b1 mov eax, dword ptr [edi + 0x314]
008d44b7 test eax, eax
008d44b9 je 0x8d44c8
008d44bb cmp byte ptr [eax + 0x16b], 0
008d44c2 je 0x8d4854
008d44c8 cmp byte ptr [edi + 0x16b], 0
008d44cf jne 0x8d4861
008d44d5 mov byte ptr [edi + 0x16b], 1
008d44dc mov dword ptr [edi + 0x3a8], 0
008d44e6 jmp 0x8d4854
008d44eb mov eax, dword ptr [0xbfd65c]
008d44f0 mov eax, dword ptr [eax + 0x1a30dc]
008d44f6 sub eax, dword ptr [edi + 0x280]
008d44fc cmp eax, 0xa
008d44ff jge 0x8d4594
008d4505 movd xmm0, eax
008d4509 movaps xmm1, xmm3
008d450c cvtdq2ps xmm0, xmm0
008d450f divss xmm0, dword ptr [0xb6a974]
008d4517 subss xmm1, xmm0
008d451b movaps xmm0, xmm1
008d451e movss dword ptr [ebp - 0x4c], xmm1
008d4523 mulss xmm0, dword ptr [0xb6a874]
008d452b call 0x412010
008d4530 movss xmm2, dword ptr [ebp - 0x4c]
008d4535 lea eax, [ebp - 0x4c]
008d4538 movaps xmm1, xmm2
008d453b mulss xmm0, xmm2
008d453f lea ecx, [ebp - 0x68]
008d4542 mov dword ptr [ebp - 0x68], 0x40a00000
008d4549 mulss xmm1, xmm2
008d454d mulss xmm1, xmm2
008d4551 subss xmm1, xmm0
008d4555 movss xmm0, dword ptr [ebp - 0x3c]
008d455a subss xmm0, xmm1
008d455e movss xmm1, dword ptr [ebp - 0x34]
008d4563 mulss xmm0, xmm1
008d4567 comiss xmm0, dword ptr [0xb6a8f4]
008d456e movss dword ptr [ebp - 0x4c], xmm0
008d4573 cmovbe eax, ecx
008d4576 movss xmm0, dword ptr [eax]
008d457a comiss xmm0, xmm1
008d457d jbe 0x8d458a
008d457f divss xmm0, xmm1
008d4583 movss dword ptr [ebp - 0x5c], xmm0
008d4588 jmp 0x8d4599
008d458a movaps xmm1, xmm0
008d458d movss dword ptr [ebp - 0x34], xmm1
008d4592 jmp 0x8d4599
008d4594 movss xmm1, dword ptr [ebp - 0x34]
008d4599 sub esp, 0xc
008d459c lea eax, [ebp - 0x48]
008d459f movaps xmm3, xmm1
008d45a2 movss dword ptr [esp + 8], xmm1
008d45a8 movss dword ptr [esp + 4], xmm1
008d45ae movss dword ptr [esp], xmm1
008d45b3 push esi
008d45b4 push eax
008d45b5 mov eax, dword ptr [0xbfd65c]
008d45ba mov ecx, dword ptr [eax + 0x18190]
008d45c0 call 0x7cec10
008d45c5 push 0xbc4c10
008d45ca lea edx, [edi + 0x378]
008d45d0 lea ecx, [ebp - 0x28]
008d45d3 call 0x412050
008d45d8 add esp, 4
008d45db mov ecx, dword ptr [eax]
008d45dd or ecx, dword ptr [eax + 4]
008d45e0 jne 0x8d4722
008d45e6 mov ecx, dword ptr [eax + 8]
008d45e9 or ecx, dword ptr [eax + 0xc]
008d45ec jne 0x8d4722
008d45f2 push 0xbc4940
008d45f7 lea edx, [edi + 0x378]
008d45fd lea ecx, [ebp - 0x28]
008d4600 call 0x412050
008d4605 add esp, 4
008d4608 mov ecx, dword ptr [eax]
008d460a or ecx, dword ptr [eax + 4]
008d460d jne 0x8d4854
008d4613 mov ecx, dword ptr [eax + 8]
008d4616 or ecx, dword ptr [eax + 0xc]
008d4619 jne 0x8d4854
008d461f movss xmm1, dword ptr [edi + 0x2b8]
008d4627 movss xmm2, dword ptr [edi + 0x2bc]
008d462f movaps xmm0, xmm1
008d4632 mulss xmm0, xmm1
008d4636 movss dword ptr [ebp - 0x68], xmm1
008d463b movaps xmm1, xmm2
008d463e mulss xmm1, xmm2
008d4642 movss dword ptr [ebp - 0x4c], xmm2
008d4647 addss xmm0, xmm1
008d464b call 0x4228c0
008d4650 comiss xmm0, dword ptr [0xb6a18c]
008d4657 jbe 0x8d4684
008d4659 movss xmm1, dword ptr [ebp - 0x3c]
008d465e divss xmm1, xmm0
008d4662 movss xmm0, dword ptr [edi + 0x2b8]
008d466a mulss xmm0, xmm1
008d466e movss dword ptr [ebp - 0x68], xmm0
008d4673 movss xmm0, dword ptr [edi + 0x2bc]
008d467b mulss xmm0, xmm1
008d467f movss dword ptr [ebp - 0x4c], xmm0
008d4684 movss xmm1, dword ptr [ebp - 0x48]
008d4689 subss xmm1, dword ptr [esi]
008d468d movss xmm2, dword ptr [ebp - 0x44]
008d4692 subss xmm2, dword ptr [esi + 4]
008d4697 movaps xmm0, xmm1
008d469a movss dword ptr [ebp - 0x60], xmm1
008d469f mulss xmm0, xmm1
008d46a3 movaps xmm1, xmm2
008d46a6 movss dword ptr [ebp - 0x44], xmm2
008d46ab mulss xmm1, xmm2
008d46af addss xmm0, xmm1
008d46b3 call 0x4228c0
008d46b8 comiss xmm0, dword ptr [0xb6a18c]
008d46bf movss xmm2, dword ptr [ebp - 0x60]
008d46c4 movss xmm3, dword ptr [ebp - 0x44]
008d46c9 jbe 0x8d46df
008d46cb movss xmm1, dword ptr [ebp - 0x3c]
008d46d0 divss xmm1, xmm0
008d46d4 movaps xmm0, xmm1
008d46d7 mulss xmm3, xmm1
008d46db mulss xmm2, xmm0
008d46df movss xmm0, dword ptr [ebp - 0x4c]
008d46e4 movss xmm1, dword ptr [ebp - 0x68]
008d46e9 mulss xmm0, xmm3
008d46ed mulss xmm1, xmm2
008d46f1 addss xmm1, xmm0
008d46f5 movss xmm0, dword ptr [0xb6ae34]
008d46fd comiss xmm0, xmm1
008d4700 jbe 0x8d4854
008d4706 cmp dword ptr [edi + 0x3a8], 0
008d470d jne 0x8d4854
008d4713 mov dword ptr [edi + 0x3a8], 5
008d471d jmp 0x8d4854
008d4722 movss xmm2, dword ptr [esi]
008d4726 lea eax, [edi + 0x2b8]
008d472c movss xmm1, dword ptr [ebp - 0x48]
008d4731 xorps xmm3, xmm3
008d4734 comiss xmm2, xmm1
008d4737 jbe 0x8d4742
008d4739 movss xmm0, dword ptr [eax]
008d473d comiss xmm0, xmm3
008d4740 ja 0x8d4750
008d4742 comiss xmm1, xmm2
008d4745 jbe 0x8d47b8
008d4747 movss xmm0, dword ptr [eax]
008d474b comiss xmm3, xmm0
008d474e jbe 0x8d47b8
008d4750 mulss xmm0, dword ptr [0xb6ae44]
008d4758 mov ecx, 0xbc4c10
008d475d movss dword ptr [esi], xmm1
008d4761 movss dword ptr [eax], xmm0
008d4765 lea eax, [ebp - 0x28]
008d4768 push eax
008d4769 call 0x57f3a0
008d476e lea esi, [edi + 0x378]
008d4774 mov ecx, dword ptr [eax]
008d4776 and dword ptr [esi], ecx
008d4778 mov ecx, dword ptr [eax + 4]
008d477b and dword ptr [esi + 4], ecx
008d477e mov ecx, dword ptr [eax + 8]
008d4781 and dword ptr [esi + 8], ecx
008d4784 mov eax, dword ptr [eax + 0xc]
008d4787 and dword ptr [esi + 0xc], eax
008d478a mov eax, dword ptr [0xbc4c10]
008d478f or dword ptr [edi + 0x398], eax
008d4795 mov eax, dword ptr [0xbc4c14]
008d479a or dword ptr [edi + 0x39c], eax
008d47a0 mov eax, dword ptr [0xbc4c18]
008d47a5 or dword ptr [edi + 0x3a0], eax
008d47ab mov eax, dword ptr [0xbc4c1c]
008d47b0 or dword ptr [edi + 0x3a4], eax
008d47b6 jmp 0x8d47be
008d47b8 lea esi, [edi + 0x378]
008d47be movss xmm2, dword ptr [edi + 0x298]
008d47c6 lea eax, [edi + 0x2bc]
008d47cc movss xmm1, dword ptr [ebp - 0x44]
008d47d1 xorps xmm3, xmm3
008d47d4 comiss xmm2, xmm1
008d47d7 jbe 0x8d47e2
008d47d9 movss xmm0, dword ptr [eax]
008d47dd comiss xmm0, xmm3
008d47e0 ja 0x8d47f0
008d47e2 comiss xmm1, xmm2
008d47e5 jbe 0x8d4854
008d47e7 movss xmm0, dword ptr [eax]
008d47eb comiss xmm3, xmm0
008d47ee jbe 0x8d4854
008d47f0 mulss xmm0, dword ptr [0xb6ae44]
008d47f8 mov ecx, 0xbc4c10
008d47fd movss dword ptr [edi + 0x298], xmm1
008d4805 movss dword ptr [eax], xmm0
008d4809 lea eax, [ebp - 0x28]
008d480c push eax
008d480d call 0x57f3a0
008d4812 mov ecx, dword ptr [eax]
008d4814 and dword ptr [esi], ecx
008d4816 mov ecx, dword ptr [eax + 4]
008d4819 and dword ptr [esi + 4], ecx
008d481c mov ecx, dword ptr [eax + 8]
008d481f and dword ptr [esi + 8], ecx
008d4822 mov eax, dword ptr [eax + 0xc]
008d4825 and dword ptr [esi + 0xc], eax
008d4828 mov eax, dword ptr [0xbc4c10]
008d482d or dword ptr [edi + 0x398], eax
008d4833 mov eax, dword ptr [0xbc4c14]
008d4838 or dword ptr [edi + 0x39c], eax
008d483e mov eax, dword ptr [0xbc4c18]
008d4843 or dword ptr [edi + 0x3a0], eax
008d4849 mov eax, dword ptr [0xbc4c1c]
008d484e or dword ptr [edi + 0x3a4], eax
008d4854 cmp byte ptr [edi + 0x16b], 0
008d485b je 0x8d49aa
008d4861 cmp dword ptr [edi + 0x2c], 2
008d4865 jne 0x8d49a3
008d486b mov ecx, dword ptr [edi + 0x70]
008d486e lea eax, [edi + 0x3c]
008d4871 test ecx, ecx
008d4873 je 0x8d496f
008d4879 cmp byte ptr [ecx + 0x34], 0
008d487d je 0x8d496f
008d4883 lea eax, [ebp - 0x30]
008d4886 push eax
008d4887 lea ecx, [edi + 0x6c]
008d488a call 0x444be0
008d488f push 4
008d4891 push 0xb43774
008d4896 lea ecx, [ebp - 0x30]
008d4899 mov dword ptr [ebp - 4], 0
008d48a0 call 0x417820
008d48a5 cmp dword ptr [ebp - 0x1c], 0x10
008d48a9 lea ecx, [ebp - 0x30]
008d48ac mov esi, dword ptr [ebp - 0x30]
008d48af cmovae ecx, esi
008d48b2 mov dword ptr [ebp - 0x4c], ecx
008d48b5 mov ecx, dword ptr [edi + 0x70]
008d48b8 test ecx, ecx
008d48ba je 0x8d490b
008d48bc cmp dword ptr [ecx + 0x14], 0x10
008d48c0 mov eax, ecx
008d48c2 jb 0x8d48c6
008d48c4 mov eax, dword ptr [ecx]
008d48c6 mov ecx, dword ptr [ebp - 0x4c]
008d48c9 nop dword ptr [eax]
008d48d0 mov dl, byte ptr [eax]
008d48d2 cmp dl, byte ptr [ecx]
008d48d4 jne 0x8d48f0
008d48d6 test dl, dl
008d48d8 je 0x8d48ec
008d48da mov dl, byte ptr [eax + 1]
008d48dd cmp dl, byte ptr [ecx + 1]
008d48e0 jne 0x8d48f0
008d48e2 add eax, 2
008d48e5 add ecx, 2
008d48e8 test dl, dl
008d48ea jne 0x8d48d0
008d48ec xor eax, eax
008d48ee jmp 0x8d48f5
008d48f0 sbb eax, eax
008d48f2 or eax, 1
008d48f5 test eax, eax
008d48f7 jne 0x8d490b
008d48f9 mov eax, dword ptr [edi + 0x70]
008d48fc cmp byte ptr [eax + 0x34], 0
008d4900 je 0x8d492e
008d4902 cmp byte ptr [edi + 0x80], 0
008d4909 jne 0x8d492e
008d490b push 1
008d490d push dword ptr [ebp - 0x4c]
008d4910 lea ecx, [edi + 0x3c]
008d4913 call 0x405740
008d4918 test al, al
008d491a je 0x8d492b
008d491c lea ecx, [edi + 0x6c]
008d491f call 0x405330
008d4924 mov byte ptr [edi + 0x80], 1
008d492b mov esi, dword ptr [ebp - 0x30]
008d492e mov dword ptr [ebp - 4], 0xffffffff
008d4935 mov eax, dword ptr [ebp - 0x1c]
008d4938 cmp eax, 0x10
008d493b jb 0x8d496a
008d493d lea ecx, [eax + 1]
008d4940 mov eax, esi
008d4942 cmp ecx, 0x1000
008d4948 jb 0x8d4960
008d494a mov esi, dword ptr [esi - 4]
008d494d add ecx, 0x23
008d4950 sub eax, esi
008d4952 add eax, -4
008d4955 cmp eax, 0x1f
008d4958 jbe 0x8d4960
008d495a call dword ptr [0xa065ac]
008d4960 push ecx
008d4961 push esi
008d4962 call 0x9eb08e
008d4967 add esp, 8
008d496a mov ecx, dword ptr [edi + 0x70]
008d496d jmp 0x8d4996
008d496f cmp dword ptr [eax + 0x34], 0
008d4973 jne 0x8d497f
008d4975 movss xmm0, dword ptr [0xb6ae44]
008d497d jmp 0x8d4984
008d497f movss xmm0, dword ptr [eax + 0x40]
008d4984 mulss xmm0, dword ptr [0xb6a350]
008d498c addss xmm0, dword ptr [ebp - 0x3c]
008d4991 movss dword ptr [ebp - 0x5c], xmm0
008d4996 test ecx, ecx
008d4998 je 0x8d49a3
008d499a cmp byte ptr [edi + 0x80], 0
008d49a1 jne 0x8d49aa
008d49a3 mov eax, dword ptr [edi]
008d49a5 mov ecx, edi
008d49a7 call dword ptr [eax + 0x28]
008d49aa mov ecx, dword ptr [edi + 0x3a8]
008d49b0 lea esi, [edi + 0x3a8]
008d49b6 test ecx, ecx
008d49b8 jle 0x8d4a56
008d49be cmp byte ptr [edi + 0x16d], 0
008d49c5 jne 0x8d4a56
008d49cb cmp dword ptr [edi + 0x2c], 2
008d49cf mov edx, ecx
008d49d1 je 0x8d4a39
008d49d3 cmp dword ptr [edi + 0x30], 2
008d49d7 jne 0x8d4a39
008d49d9 mov eax, 5
008d49de sub eax, ecx
008d49e0 lea ecx, [edi + 0x3c]
008d49e3 movd xmm0, eax
008d49e7 lea eax, [edi + 0x1b0]
008d49ed cvtdq2ps xmm0, xmm0
008d49f0 push eax
008d49f1 mulss xmm0, dword ptr [0xb6a350]
008d49f9 addss xmm0, dword ptr [ebp - 0x3c]
008d49fe movss dword ptr [ebp - 0x5c], xmm0
008d4a03 call 0x402370
008d4a08 mov edx, dword ptr [esi]
008d4a0a lea eax, [ebp - 0x4c]
008d4a0d cmp edx, 5
008d4a10 mov dword ptr [ebp - 0x4c], 5
008d4a17 cmovl eax, esi
008d4a1a movd xmm0, dword ptr [eax]
008d4a1e cvtdq2ps xmm0, xmm0
008d4a21 mulss xmm0, dword ptr [edi + 0xf0]
008d4a29 divss xmm0, dword ptr [0xb6a8f4]
008d4a31 movss dword ptr [edi + 0xf0], xmm0
008d4a39 movss xmm0, dword ptr [ebp - 0x34]
008d4a3e lea eax, [edx - 1]
008d4a41 mov dword ptr [esi], eax
008d4a43 lea esi, [edi + 0x294]
008d4a49 test eax, eax
008d4a4b jg 0x8d4a61
008d4a4d mov byte ptr [edi + 0x16b], 1
008d4a54 jmp 0x8d4a61
008d4a56 movss xmm0, dword ptr [ebp - 0x34]
008d4a5b lea esi, [edi + 0x294]
008d4a61 cmp dword ptr [edi + 0x30], 3
008d4a65 movss xmm2, dword ptr [0xb6a3b0]
008d4a6d movss dword ptr [ebp - 0x4c], xmm2
008d4a72 jne 0x8d4b93
008d4a78 mov eax, dword ptr [edi + 0x314]
008d4a7e test eax, eax
008d4a80 je 0x8d4ada
008d4a82 cmp byte ptr [edi + 0x434], 0
008d4a89 jne 0x8d4ada
008d4a8b movss xmm0, dword ptr [eax + 0x294]
008d4a93 movss xmm1, dword ptr [eax + 0x298]
008d4a9b addss xmm0, dword ptr [edi + 0x360]
008d4aa3 addss xmm1, dword ptr [edi + 0x364]
008d4aab movss dword ptr [esi], xmm0
008d4aaf movss dword ptr [esi + 4], xmm1
008d4ab4 mov eax, dword ptr [edi + 0x314]
008d4aba movss xmm0, dword ptr [eax + 0x2b8]
008d4ac2 movss xmm1, dword ptr [eax + 0x2bc]
008d4aca movss dword ptr [edi + 0x2b8], xmm0
008d4ad2 movss dword ptr [edi + 0x2bc], xmm1
008d4ada mov eax, dword ptr [edi + 0x2c]
008d4add cmp eax, 1
008d4ae0 je 0x8d4af5
008d4ae2 cmp eax, 9
008d4ae5 je 0x8d4af5
008d4ae7 cmp eax, 0xb
008d4aea je 0x8d4af5
008d4aec cmp eax, 0xe
008d4aef jne 0x8d4ca6
008d4af5 cmp dword ptr [edi + 0x3a8], 0x14
008d4afc lea eax, [edi + 0x3a8]
008d4b02 lea ecx, [ebp - 0x68]
008d4b05 mov dword ptr [ebp - 0x68], 0x14
008d4b0c cmovl ecx, eax
008d4b0f mov dword ptr [ebp - 0xa0], 0x3f800000
008d4b19 lea eax, [ebp - 0xa0]
008d4b1f mov dword ptr [ebp - 0x9c], 0x3f800000
008d4b29 xorps xmm1, xmm1
008d4b2c mov dword ptr [ebp - 0x98], 0x3f800000
008d4b36 mov dword ptr [ebp - 0x80], 0
008d4b3d movd xmm0, dword ptr [ecx]
008d4b41 lea ecx, [edi + 0xe4]
008d4b47 mov dword ptr [ebp - 0x7c], 0
008d4b4e mov dword ptr [ebp - 0x78], 0
008d4b55 cvtdq2ps xmm0, xmm0
008d4b58 divss xmm0, dword ptr [0xb6a9c8]
008d4b60 movss dword ptr [ebp - 0x94], xmm0
008d4b68 cmp ecx, eax
008d4b6a je 0x8d4ca6
008d4b70 movups xmm0, xmmword ptr [ebp - 0xa0]
008d4b77 mov eax, dword ptr [ebp - 0x78]
008d4b7a movups xmmword ptr [ecx + 0x10], xmm1
008d4b7e movups xmmword ptr [ecx], xmm0
008d4b81 movq xmm0, qword ptr [ebp - 0x80]
008d4b86 movq qword ptr [ecx + 0x20], xmm0
008d4b8b mov dword ptr [ecx + 0x28], eax
008d4b8e jmp 0x8d4ca6
008d4b93 push 0xbc4940
008d4b98 lea edx, [edi + 0x378]
008d4b9e lea ecx, [ebp - 0x28]
008d4ba1 call 0x412050
008d4ba6 add esp, 4
008d4ba9 mov ecx, dword ptr [eax]
008d4bab or ecx, dword ptr [eax + 4]
008d4bae jne 0x8d4bfc
008d4bb0 mov ecx, dword ptr [eax + 8]
008d4bb3 or ecx, dword ptr [eax + 0xc]
008d4bb6 jne 0x8d4bfc
008d4bb8 sub esp, 0xc
008d4bbb lea eax, [ebp - 0x6c]
008d4bbe movaps xmm3, xmm0
008d4bc1 movss dword ptr [esp + 8], xmm0
008d4bc7 movss dword ptr [esp + 4], xmm0
008d4bcd movss dword ptr [esp], xmm0
008d4bd2 push esi
008d4bd3 push eax
008d4bd4 mov eax, dword ptr [0xbfd65c]
008d4bd9 mov ecx, dword ptr [eax + 0x18190]
008d4bdf call 0x7cec10
008d4be4 movss xmm0, dword ptr [ebp - 0x6c]
008d4be9 movss dword ptr [esi], xmm0
008d4bed movss xmm0, dword ptr [ebp - 0x68]
008d4bf2 movss dword ptr [esi + 4], xmm0
008d4bf7 jmp 0x8d4ca6
008d4bfc cmp byte ptr [edi + 0x16d], 0
008d4c03 jne 0x8d4ca6
008d4c09 movss xmm0, dword ptr [esi]
008d4c0d lea eax, [ebp - 0x64]
008d4c10 movss xmm3, dword ptr [0xb6af78]
008d4c18 sub esp, 0xc
008d4c1b movss dword ptr [ebp - 0x68], xmm0
008d4c20 movss xmm0, dword ptr [esi + 4]
008d4c25 movss dword ptr [ebp - 0x44], xmm0
008d4c2a mov dword ptr [esp + 8], 0xc3480000
008d4c32 mov dword ptr [esp + 4], 0xc3480000
008d4c3a mov dword ptr [esp], 0xc3480000
008d4c41 push esi
008d4c42 push eax
008d4c43 mov eax, dword ptr [0xbfd65c]
008d4c48 mov ecx, dword ptr [eax + 0x18190]
008d4c4e call 0x7cef20
008d4c53 movss xmm0, dword ptr [ebp - 0x64]
008d4c58 movss dword ptr [esi], xmm0
008d4c5c movss xmm0, dword ptr [ebp - 0x60]
008d4c61 movss dword ptr [esi + 4], xmm0
008d4c66 movss xmm0, dword ptr [esi]
008d4c6a ucomiss xmm0, dword ptr [ebp - 0x68]
008d4c6e lahf 
008d4c6f test ah, 0x44
008d4c72 jp 0x8d4c83
008d4c74 movss xmm0, dword ptr [esi + 4]
008d4c79 ucomiss xmm0, dword ptr [ebp - 0x44]
008d4c7d lahf 
008d4c7e test ah, 0x44
008d4c81 jnp 0x8d4ca6
008d4c83 cmp dword ptr [edi + 0x30], 2
008d4c87 movss xmm0, dword ptr [ebp - 0x3c]
008d4c8c movss dword ptr [ebp - 0x4c], xmm0
008d4c91 jne 0x8d4ca6
008d4c93 cmp dword ptr [edi + 0x3a8], 0
008d4c9a jne 0x8d4ca6
008d4c9c mov dword ptr [edi + 0x3a8], 0x2d
008d4ca6 mov eax, dword ptr [edi + 0x2c]
008d4ca9 cmp eax, 2
008d4cac je 0x8d4cb7
008d4cae cmp eax, 0xa
008d4cb1 jne 0x8d4ddf
008d4cb7 mov esi, dword ptr [edi + 0x318]
008d4cbd test esi, esi
008d4cbf je 0x8d4ddf
008d4cc5 cmp byte ptr [edi + 0x16d], 0
008d4ccc movss xmm3, dword ptr [edi + 0x294]
008d4cd4 movss xmm2, dword ptr [edi + 0x298]
008d4cdc jne 0x8d4d7e
008d4ce2 push 0xbc4940
008d4ce7 lea edx, [edi + 0x378]
008d4ced lea ecx, [ebp - 0x28]
008d4cf0 call 0x412050
008d4cf5 add esp, 4
008d4cf8 mov ecx, dword ptr [eax]
008d4cfa or ecx, dword ptr [eax + 4]
008d4cfd jne 0x8d4d7e
008d4cff mov ecx, dword ptr [eax + 8]
008d4d02 or ecx, dword ptr [eax + 0xc]
008d4d05 jne 0x8d4d7e
008d4d07 cmp dword ptr [edi + 0x30], 3
008d4d0b je 0x8d4d7e
008d4d0d movss xmm0, dword ptr [edi + 0x2c4]
008d4d15 lea eax, [ebp - 0x6c]
008d4d18 movaps xmm1, xmm0
008d4d1b sub esp, 0xc
008d4d1e mulss xmm0, dword ptr [edi + 0x2bc]
008d4d26 mulss xmm1, dword ptr [edi + 0x2b8]
008d4d2e addss xmm2, xmm0
008d4d32 movss xmm0, dword ptr [ebp - 0x34]
008d4d37 movss dword ptr [esp + 8], xmm0
008d4d3d movss dword ptr [esp + 4], xmm0
008d4d43 addss xmm1, xmm3
008d4d47 movss dword ptr [esp], xmm0
008d4d4c movaps xmm3, xmm0
008d4d4f push eax
008d4d50 lea eax, [ebp - 0x48]
008d4d53 movss dword ptr [ebp - 0x68], xmm2
008d4d58 push eax
008d4d59 mov eax, dword ptr [0xbfd65c]
008d4d5e movss dword ptr [ebp - 0x6c], xmm1
008d4d63 mov ecx, dword ptr [eax + 0x18190]
008d4d69 call 0x7cec10
008d4d6e movss xmm3, dword ptr [ebp - 0x48]
008d4d73 movss xmm2, dword ptr [ebp - 0x44]
008d4d78 mov esi, dword ptr [edi + 0x318]
008d4d7e cmp dword ptr [edi + 0x30], 2
008d4d82 jne 0x8d4d94
008d4d84 subss xmm2, dword ptr [edi + 0x2bc]
008d4d8c subss xmm3, dword ptr [edi + 0x2b8]
008d4d94 movss dword ptr [esi + 0x294], xmm3
008d4d9c lea eax, [edi + 0xe4]
008d4da2 push 1
008d4da4 movss dword ptr [esi + 0x298], xmm2
008d4dac mov ecx, dword ptr [edi + 0x318]
008d4db2 push 0
008d4db4 push 0xff
008d4db9 push -1
008d4dbb mov edx, dword ptr [ecx]
008d4dbd push eax
008d4dbe call dword ptr [edx + 0x38]
008d4dc1 mov ecx, dword ptr [edi + 0x318]
008d4dc7 mov eax, dword ptr [edi + 0x2a4]
008d4dcd mov dword ptr [ecx + 0x2a4], eax
008d4dd3 mov eax, dword ptr [edi + 0x2a8]
008d4dd9 mov dword ptr [ecx + 0x2a8], eax
008d4ddf push 0xbc4cb0
008d4de4 lea edx, [edi + 0x378]
008d4dea lea ecx, [ebp - 0x28]
008d4ded call 0x412050
008d4df2 add esp, 4
008d4df5 mov ecx, dword ptr [eax]
008d4df7 or ecx, dword ptr [eax + 4]
008d4dfa jne 0x8d4e08
008d4dfc mov ecx, dword ptr [eax + 8]
008d4dff or ecx, dword ptr [eax + 0xc]
008d4e02 jne 0x8d4e08
008d4e04 xor eax, eax
008d4e06 jmp 0x8d4e0d
008d4e08 mov eax, 1
008d4e0d mov edx, dword ptr [edi + 0x314]
008d4e13 lea ecx, [edi + 0x294]
008d4e19 movss xmm2, dword ptr [ebp - 0x34]
008d4e1e lea esi, [edi + 0x3b4]
008d4e24 mulss xmm2, dword ptr [ebp - 0x5c]
008d4e29 push edx
008d4e2a push eax
008d4e2b push ecx
008d4e2c mov ecx, esi
008d4e2e call 0x8f8680
008d4e33 movss xmm1, dword ptr [ebp - 0x4c]
008d4e38 mov ecx, esi
008d4e3a call 0x8f61a0
008d4e3f movss xmm1, dword ptr [0xb6a1c8]
008d4e47 mov ecx, esi
008d4e49 call 0x8f8bb0
008d4e4e push 0xbc4930
008d4e53 lea edx, [edi + 0x378]
008d4e59 lea ecx, [ebp - 0x28]
008d4e5c call 0x412050
008d4e61 add esp, 4
008d4e64 mov ecx, dword ptr [eax]
008d4e66 or ecx, dword ptr [eax + 4]
008d4e69 jne 0x8d4e73
008d4e6b mov ecx, dword ptr [eax + 8]
008d4e6e or ecx, dword ptr [eax + 0xc]
008d4e71 je 0x8d4ed8
008d4e73 mov eax, dword ptr [edi + 0x314]
008d4e79 test eax, eax
008d4e7b je 0x8d4eb4
008d4e7d cmp dword ptr [eax + 0x28], 8
008d4e81 jne 0x8d4eb4
008d4e83 mov eax, dword ptr [ebp - 0x40]
008d4e86 test eax, eax
008d4e88 je 0x8d4e95
008d4e8a push 0xa
008d4e8c mov ecx, eax
008d4e8e call 0x7866b0
008d4e93 jmp 0x8d4e9a
008d4e95 movss xmm0, dword ptr [ebp - 0x3c]
008d4e9a mov eax, dword ptr [0xbfd65c]
008d4e9f movd xmm2, dword ptr [eax + 0x1a30dc]
008d4ea7 cvtdq2ps xmm2, xmm2
008d4eaa mulss xmm2, dword ptr [0xb6a70c]
008d4eb2 jmp 0x8d4ece
008d4eb4 mov eax, dword ptr [ebp - 0x40]
008d4eb7 test eax, eax
008d4eb9 je 0x8d4ec6
008d4ebb push 0xa
008d4ebd mov ecx, eax
008d4ebf call 0x7866b0
008d4ec4 jmp 0x8d4ecb
008d4ec6 movss xmm0, dword ptr [ebp - 0x3c]
008d4ecb xorps xmm2, xmm2
008d4ece movaps xmm1, xmm0
008d4ed1 mov ecx, esi
008d4ed3 call 0x8f6a40
008d4ed8 mov eax, dword ptr [edi + 0x17c]
008d4ede mov byte ptr [edi + 0x466], 0
008d4ee5 test eax, eax
008d4ee7 je 0x8d4f25
008d4ee9 movss xmm1, dword ptr [edi + 0x2a4]
008d4ef1 mov ecx, esi
008d4ef3 movss xmm0, dword ptr [edi + 0x2a8]
008d4efb mulss xmm1, dword ptr [0xb6a560]
008d4f03 push eax
008d4f04 mulss xmm0, dword ptr [0xb6a560]
008d4f0c lea eax, [ebp - 0x50]
008d4f0f push eax
008d4f10 movss dword ptr [ebp - 0x50], xmm1
008d4f15 movss dword ptr [ebp - 0x4c], xmm0
008d4f1a call 0x8f8350
008d4f1f mov byte ptr [edi + 0x466], al
008d4f25 cmp byte ptr [ebp - 0x35], 0
008d4f29 je 0x8d4f37
008d4f2b mov ecx, edi
008d4f2d call 0x8cbe80
008d4f32 jmp 0x8d5011
008d4f37 cmp byte ptr [edi + 0x16b], 0
008d4f3e jne 0x8d5011
008d4f44 cmp byte ptr [edi + 0x16d], 0
008d4f4b jne 0x8d5011
008d4f51 cmp dword ptr [edi + 0x2c], 8
008d4f55 jne 0x8d5011
008d4f5b movss xmm1, dword ptr [0xb6aa0c]
008d4f63 xorps xmm2, xmm2
008d4f66 mov ecx, edi
008d4f68 call 0x6847e0
008d4f6d test eax, eax
008d4f6f je 0x8d5011
008d4f75 movss xmm3, dword ptr [edi + 0x40c]
008d4f7d lea eax, [edi + 0x294]
008d4f83 push 8
008d4f85 push eax
008d4f86 lea eax, [ebp - 0x74]
008d4f89 push eax
008d4f8a mov eax, dword ptr [0xbfd65c]
008d4f8f mov ecx, dword ptr [eax + 0x18190]
008d4f95 add ecx, 0x1218
008d4f9b call 0x4157f0
008d4fa0 xor esi, esi
008d4fa2 mov dword ptr [ebp - 4], 1
008d4fa9 cmp dword ptr [ebp - 0x68], esi
008d4fac jbe 0x8d4ff9
008d4fae nop 
008d4fb0 mov ecx, dword ptr [ebp - 0x70]
008d4fb3 push 0
008d4fb5 mov ecx, dword ptr [ecx + esi*4]
008d4fb8 call 0x684630
008d4fbd test al, al
008d4fbf je 0x8d4ff3
008d4fc1 push edi
008d4fc2 lea ecx, [ebp - 0xd8]
008d4fc8 call 0x4229a0
008d4fcd mov eax, dword ptr [ebp - 0x70]
008d4fd0 lea edx, [ebp - 0xd8]
008d4fd6 movss xmm0, dword ptr [edi + 0x2e0]
008d4fde push 0x1e
008d4fe0 push edx
008d4fe1 mov ecx, dword ptr [eax + esi*4]
008d4fe4 push 0
008d4fe6 push 0
008d4fe8 push ecx
008d4fe9 mov eax, dword ptr [ecx]
008d4feb movss dword ptr [esp], xmm0
008d4ff0 call dword ptr [eax + 0x20]
008d4ff3 inc esi
008d4ff4 cmp esi, dword ptr [ebp - 0x68]
008d4ff7 jb 0x8d4fb0
008d4ff9 mov dword ptr [ebp - 4], 0xffffffff
008d5000 cmp byte ptr [ebp - 0x74], 0
008d5004 jne 0x8d5011
008d5006 push dword ptr [ebp - 0x70]
008d5009 call 0x9eace5
008d500e add esp, 4
008d5011 movss xmm0, dword ptr [edi + 0x494]
008d5019 movss dword ptr [ebp - 0x4c], xmm0
008d501e fld dword ptr [ebp - 0x4c]
008d5021 push ecx
008d5022 fstp dword ptr [esp]
008d5025 call 0x9ec36a
008d502a add esp, 4
008d502d test ax, ax
008d5030 jle 0x8d503f
008d5032 cmp byte ptr [edi + 0x466], 0
008d5039 jne 0x8d503f
008d503b xor al, al
008d503d jmp 0x8d5041
008d503f mov al, 1
008d5041 cmp byte ptr [ebp - 0x35], 0
008d5045 je 0x8d5068
008d5047 test al, al
008d5049 je 0x8d5068
008d504b movss xmm3, dword ptr [edi + 0x494]
008d5053 lea eax, [edi + 0x4a0]
008d5059 push eax
008d505a lea eax, [edi + 0x498]
008d5060 mov ecx, edi
008d5062 push eax
008d5063 call 0x8c5e80
008d5068 mov ecx, dword ptr [ebp - 0xc]
008d506b mov dword ptr fs:[0], ecx
008d5072 pop ecx
008d5073 pop edi
008d5074 pop esi
008d5075 mov ecx, dword ptr [ebp - 0x14]
008d5078 xor ecx, ebp
008d507a call 0x9eacd7
008d507f mov esp, ebp
008d5081 pop ebp
008d5082 mov esp, ebx
008d5084 pop ebx
008d5085 ret 
008d5086 int3 
008d5087 int3 
008d5088 int3 
008d5089 int3 
008d508a int3 
008d508b int3 
008d508c int3 
008d508d int3 
008d508e int3 
008d508f int3 
