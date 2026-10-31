005265c3 cmp dword ptr [edi + 0x70], 0
005265c7 je 0x5265d6
005265c9 cmp byte ptr [edi + 0x80], 0
005265d0 jne 0x52668a
005265d6 cmp dword ptr [edi + 0x28], 0x115
005265dd jne 0x526680
005265e3 cmp dword ptr [edi + 0x360], 2
005265ea jge 0x526680
005265f0 lea eax, [ebp - 0x44]
005265f3 push eax
005265f4 lea ecx, [edi + 0x6c]
005265f7 call 0x444be0
005265fc mov dword ptr [ebp - 4], 2
00526603 cmp dword ptr [eax + 0x14], 0x10
00526607 jb 0x52660b
00526609 mov eax, dword ptr [eax]
0052660b push 1
0052660d push eax
0052660e lea ecx, [edi + 0x3c]
00526611 call 0x405740
00526616 test al, al
00526618 je 0x526629
0052661a lea ecx, [edi + 0x6c]
0052661d call 0x405330
00526622 mov byte ptr [edi + 0x80], 1
00526629 mov dword ptr [ebp - 4], 0xffffffff
00526630 mov edx, dword ptr [ebp - 0x30]
00526633 cmp edx, 0x10
00526636 jb 0x526666
00526638 mov ecx, dword ptr [ebp - 0x44]
0052663b inc edx
0052663c mov eax, ecx
0052663e cmp edx, 0x1000
00526644 jb 0x52665c
00526646 mov ecx, dword ptr [ecx - 4]
00526649 add edx, 0x23
0052664c sub eax, ecx
0052664e add eax, -4
00526651 cmp eax, 0x1f
00526654 jbe 0x52665c
00526656 call dword ptr [0xa065ac]
0052665c push edx
0052665d push ecx
0052665e call 0x9eb08e
00526663 add esp, 8
00526666 inc dword ptr [edi + 0x360]
0052666c mov dword ptr [ebp - 0x34], 0
00526673 mov dword ptr [ebp - 0x30], 0xf
0052667a mov byte ptr [ebp - 0x44], 0
0052667e jmp 0x52668a
00526680 mov dword ptr [edi + 0xab4], 4
