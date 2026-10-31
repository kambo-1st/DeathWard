005464c0 push ebp
005464c1 mov ebp, esp
005464c3 and esp, 0xfffffff8
005464c6 sub esp, 0xc
005464c9 push ebx
005464ca push esi
005464cb mov esi, ecx
005464cd movss dword ptr [esp + 0xc], xmm2
005464d3 push edi
005464d4 mov ebx, edx
005464d6 mov dword ptr [esp + 0x14], esi
005464da call 0x6c3d90
005464df mov ecx, dword ptr [0xbfd65c]
005464e5 push 0
005464e7 push eax
005464e8 movzx eax, byte ptr [ebp + 8]
005464ec push eax
005464ed push ebx
005464ee push 0xc02fec
005464f3 push esi
005464f4 push 0
005464f6 push 0x328
005464fb call 0x6d0ca0
00546500 mov edi, eax
00546502 test ebx, ebx
00546504 je 0x546534
00546506 mov ecx, dword ptr [edi + 0x314]
0054650c lea esi, [edi + 0x314]
00546512 test ecx, ecx
00546514 je 0x54652a
00546516 lea eax, [esp + 0xc]
0054651a mov dword ptr [esp + 0xc], esi
0054651e push eax
0054651f add ecx, 0x324
00546525 call 0x4bc3c0
0054652a push esi
0054652b mov ecx, ebx
0054652d mov dword ptr [esi], ebx
0054652f call 0x4bae70
00546534 movss xmm0, dword ptr [esp + 0x10]
0054653a and dword ptr [edi + 0x160], 0xfffffffb
00546541 cmp byte ptr [ebp + 8], 0
00546545 mov eax, dword ptr [edi + 0x164]
0054654b movss dword ptr [edi + 0xb00], xmm0
00546553 mov dword ptr [edi + 0xb04], 0x3f800000
0054655d mov dword ptr [edi + 0x164], eax
00546563 je 0x546610
00546569 mov dword ptr [edi + 0xab4], 7
00546573 mov ebx, dword ptr [edi + 0x70]
00546576 test ebx, ebx
00546578 je 0x5465c6
0054657a cmp dword ptr [ebx + 0x14], 0x10
0054657e mov eax, ebx
00546580 jb 0x546584
00546582 mov eax, dword ptr [ebx]
00546584 mov ecx, 0xb4355c
00546589 nop dword ptr [eax]
00546590 mov dl, byte ptr [eax]
00546592 cmp dl, byte ptr [ecx]
00546594 jne 0x5465b0
00546596 test dl, dl
00546598 je 0x5465ac
0054659a mov dl, byte ptr [eax + 1]
0054659d cmp dl, byte ptr [ecx + 1]
005465a0 jne 0x5465b0
005465a2 add eax, 2
005465a5 add ecx, 2
005465a8 test dl, dl
005465aa jne 0x546590
005465ac xor eax, eax
005465ae jmp 0x5465b5
005465b0 sbb eax, eax
005465b2 or eax, 1
005465b5 test eax, eax
005465b7 jne 0x5465c6
005465b9 cmp byte ptr [ebx + 0x34], al
005465bc je 0x5465e8
005465be cmp byte ptr [edi + 0x80], al
005465c4 jne 0x5465e8
005465c6 push 1
005465c8 push 0xb4355c
005465cd lea ecx, [edi + 0x3c]
005465d0 call 0x405740
005465d5 test al, al
005465d7 je 0x5465e8
005465d9 lea ecx, [edi + 0x6c]
005465dc call 0x405330
005465e1 mov byte ptr [edi + 0x80], 1
005465e8 mov ecx, dword ptr [esp + 0x14]
005465ec mov eax, dword ptr [ecx]
005465ee mov dword ptr [edi + 0x28c], eax
005465f4 mov eax, dword ptr [ecx + 4]
005465f7 mov dword ptr [edi + 0x290], eax
005465fd mov eax, edi
005465ff mov dword ptr [edi + 0xaf4], 0
00546609 pop edi
0054660a pop esi
0054660b pop ebx
0054660c mov esp, ebp
0054660e pop ebp
0054660f ret 
00546610 mov dword ptr [edi + 0xab4], 6
0054661a mov ebx, dword ptr [edi + 0x70]
0054661d test ebx, ebx
0054661f je 0x546666
00546621 cmp dword ptr [ebx + 0x14], 0x10
00546625 mov eax, ebx
00546627 jb 0x54662b
00546629 mov eax, dword ptr [ebx]
0054662b mov ecx, 0xb43588
00546630 mov dl, byte ptr [eax]
00546632 cmp dl, byte ptr [ecx]
00546634 jne 0x546650
00546636 test dl, dl
00546638 je 0x54664c
0054663a mov dl, byte ptr [eax + 1]
0054663d cmp dl, byte ptr [ecx + 1]
00546640 jne 0x546650
00546642 add eax, 2
00546645 add ecx, 2
00546648 test dl, dl
0054664a jne 0x546630
0054664c xor eax, eax
0054664e jmp 0x546655
00546650 sbb eax, eax
00546652 or eax, 1
00546655 test eax, eax
00546657 jne 0x546666
00546659 cmp byte ptr [ebx + 0x34], al
0054665c je 0x546688
0054665e cmp byte ptr [edi + 0x80], al
00546664 jne 0x546688
00546666 push 1
00546668 push 0xb43588
0054666d lea ecx, [edi + 0x3c]
00546670 call 0x405740
00546675 test al, al
00546677 je 0x546688
00546679 lea ecx, [edi + 0x6c]
0054667c call 0x405330
00546681 mov byte ptr [edi + 0x80], 1
00546688 mov eax, edi
0054668a pop edi
0054668b pop esi
0054668c pop ebx
0054668d mov esp, ebp
0054668f pop ebp
00546690 ret 
