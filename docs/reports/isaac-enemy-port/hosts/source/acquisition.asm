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
