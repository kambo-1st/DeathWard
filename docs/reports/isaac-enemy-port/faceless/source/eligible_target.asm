00695620 push ebp
00695621 mov ebp, esp
00695623 mov eax, dword ptr [ecx + 0x160]
00695629 and eax, 0x100
0069562e or eax, 0
00695631 push esi
00695632 je 0x695654
00695634 mov esi, dword ptr [ebp + 8]
00695637 mov ecx, esi
00695639 push 0
0069563b call 0x684630
00695640 test al, al
00695642 je 0x69566d
00695644 mov eax, dword ptr [esi + 0x160]
0069564a and eax, 0x20000000
0069564f or eax, 0
00695652 jmp 0x695664
00695654 mov ecx, dword ptr [ebp + 8]
00695657 cmp dword ptr [ecx + 0x28], 1
0069565b jne 0x69566d
0069565d call 0x786be0
00695662 test al, al
00695664 jne 0x69566d
00695666 mov al, 1
00695668 pop esi
00695669 pop ebp
0069566a ret 4
0069566d xor al, al
0069566f pop esi
00695670 pop ebp
00695671 ret 4
