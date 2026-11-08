0076a71f cmp dword ptr [ebx + 0x1298], 0
0076a726 jle 0x76a789
0076a728 mov ecx, ebx
0076a72a mov dword ptr [ebx + 0x1298], 0
0076a734 mov edx, 0xd
0076a739 call 0x78cdc0
0076a73e cmp eax, 1
0076a741 jne 0x76a75d
0076a743 mov eax, dword ptr [ebx + 0x130c]
0076a749 cmp eax, 0xc
0076a74c je 0x76a758
0076a74e mov edx, 6
0076a753 cmp eax, 0x18
0076a756 jne 0x76a75d
0076a758 mov edx, 0x2e
0076a75d mov ecx, dword ptr [0xbfd65c]
0076a763 push 0
0076a765 push 1
0076a767 push edx
0076a768 lea ecx, [ecx + 0x1bcc0]
0076a76e call 0x90dd70
0076a773 push 0
0076a775 push 2
0076a777 mov ecx, ebx
0076a779 call 0x724d50
0076a77e push 0
0076a780 push 2
0076a782 mov ecx, ebx
0076a784 call 0x724f00
