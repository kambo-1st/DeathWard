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
