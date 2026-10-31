00405640 push ebp
00405641 mov ebp, esp
00405643 mov eax, dword ptr [ecx + 0x34]
00405646 test eax, eax
00405648 je 0x40568f
0040564a cmp byte ptr [ecx + 0x44], 0
0040564e je 0x40568f
00405650 mov ecx, dword ptr [ebp + 8]
00405653 cmp byte ptr [ecx], 0
00405656 je 0x405689
00405658 cmp dword ptr [eax + 0x14], 0x10
0040565c jb 0x405660
0040565e mov eax, dword ptr [eax]
00405660 mov dl, byte ptr [eax]
00405662 cmp dl, byte ptr [ecx]
00405664 jne 0x405680
00405666 test dl, dl
00405668 je 0x40567c
0040566a mov dl, byte ptr [eax + 1]
0040566d cmp dl, byte ptr [ecx + 1]
00405670 jne 0x405680
00405672 add eax, 2
00405675 add ecx, 2
00405678 test dl, dl
0040567a jne 0x405660
0040567c xor eax, eax
0040567e jmp 0x405685
00405680 sbb eax, eax
00405682 or eax, 1
00405685 test eax, eax
00405687 jne 0x40568f
00405689 mov al, 1
0040568b pop ebp
0040568c ret 4
0040568f xor al, al
00405691 pop ebp
00405692 ret 4
