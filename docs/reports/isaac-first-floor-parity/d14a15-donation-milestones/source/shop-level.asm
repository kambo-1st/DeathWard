007b1717 mov eax, dword ptr [0xbfd65c]
007b171c mov ecx, dword ptr [eax + 0x243624]
007b1722 cmp ecx, 2
007b1725 je 0x7b1803
007b172b cmp ecx, 3
007b172e je 0x7b1803
007b1734 mov ecx, dword ptr [0xbfd680]
007b173a mov dword ptr [edi + 0x6f5c], 1
007b1744 cmp byte ptr [ecx + 0xe6], 0
007b174b jne 0x7b17f7
007b1751 mov edx, dword ptr [ecx + 8]
007b1754 cmp edx, 2
007b1757 jne 0x7b1773
007b1759 cmp dword ptr [eax + 0x1c3204], 0
007b1760 ja 0x7b17f7
007b1766 cmp byte ptr [eax + 0x1c31a1], 0
007b176d jne 0x7b17f7
007b1773 cmp byte ptr [ecx + 0xe5], 0
007b177a jne 0x7b17eb
007b177c cmp edx, 2
007b177f jne 0x7b1793
007b1781 cmp dword ptr [eax + 0x1c3204], 0
007b1788 ja 0x7b17eb
007b178a cmp byte ptr [eax + 0x1c31a1], 0
007b1791 jne 0x7b17eb
007b1793 cmp byte ptr [ecx + 0xe4], 0
007b179a jne 0x7b17df
007b179c cmp edx, 2
007b179f jne 0x7b17b3
007b17a1 cmp dword ptr [eax + 0x1c3204], 0
007b17a8 ja 0x7b17df
007b17aa cmp byte ptr [eax + 0x1c31a1], 0
007b17b1 jne 0x7b17df
007b17b3 cmp byte ptr [ecx + 0xe3], 0
007b17ba jne 0x7b17d3
007b17bc cmp edx, 2
007b17bf jne 0x7b1834
007b17c1 cmp dword ptr [eax + 0x1c3204], 0
007b17c8 ja 0x7b17d3
007b17ca cmp byte ptr [eax + 0x1c31a1], 0
007b17d1 je 0x7b1834
007b17d3 mov dword ptr [edi + 0x6f5c], 2
007b17dd jmp 0x7b1834
007b17df mov dword ptr [edi + 0x6f5c], 3
007b17e9 jmp 0x7b1834
007b17eb mov dword ptr [edi + 0x6f5c], 4
007b17f5 jmp 0x7b1834
007b17f7 mov dword ptr [edi + 0x6f5c], 5
007b1801 jmp 0x7b1834
007b1803 mov eax, dword ptr [eax]
007b1805 dec eax
007b1806 cmp eax, 5
007b1809 ja 0x7b1834
007b180b jmp dword ptr [eax*4 + 0x7b5924]
007b1812 mov dword ptr [edi + 0x6f5c], 1
007b181c jmp 0x7b1834
007b181e xor eax, eax
007b1820 cmp dword ptr [edi + 8], 1
007b1824 sete al
007b1827 lea eax, [eax*4 + 1]
007b182e mov dword ptr [edi + 0x6f5c], eax
