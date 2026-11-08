00405740 push ebp
00405741 mov ebp, esp
00405743 sub esp, 8
00405746 push ebx
00405747 mov eax, ecx
00405749 mov ecx, dword ptr [ebp + 8]
0040574c push esi
0040574d push edi
0040574e xor edi, edi
00405750 mov dword ptr [ebp - 4], eax
00405753 mov ebx, dword ptr [eax + 0x78]
00405756 test ebx, ebx
00405758 je 0x4057a7
0040575a mov eax, dword ptr [eax + 0x74]
0040575d mov esi, eax
0040575f mov dword ptr [ebp - 8], eax
00405762 cmp dword ptr [esi + 0x14], 0x10
00405766 mov eax, esi
00405768 jb 0x405770
0040576a mov eax, dword ptr [esi]
0040576c nop dword ptr [eax]
00405770 mov dl, byte ptr [eax]
00405772 cmp dl, byte ptr [ecx]
00405774 jne 0x405790
00405776 test dl, dl
00405778 je 0x40578c
0040577a mov dl, byte ptr [eax + 1]
0040577d cmp dl, byte ptr [ecx + 1]
00405780 jne 0x405790
00405782 add eax, 2
00405785 add ecx, 2
00405788 test dl, dl
0040578a jne 0x405770
0040578c xor eax, eax
0040578e jmp 0x405795
00405790 sbb eax, eax
00405792 or eax, 1
00405795 test eax, eax
00405797 je 0x4057c2
00405799 mov ecx, dword ptr [ebp + 8]
0040579c inc edi
0040579d add esi, 0x13c
004057a3 cmp edi, ebx
004057a5 jb 0x405762
004057a7 push ecx
004057a8 push 0xa082b0
004057ad push 0
004057af call 0x95e330
004057b4 add esp, 0xc
004057b7 xor al, al
004057b9 pop edi
004057ba pop esi
004057bb pop ebx
004057bc mov esp, ebp
004057be pop ebp
004057bf ret 8
004057c2 mov ecx, dword ptr [ebp - 4]
004057c5 imul eax, edi, 0x13c
004057cb add ecx, 0x30
004057ce add eax, dword ptr [ebp - 8]
004057d1 cmp byte ptr [ebp + 0xc], 0
004057d5 push eax
004057d6 je 0x4057e8
004057d8 call 0x403740
004057dd mov al, 1
004057df pop edi
004057e0 pop esi
004057e1 pop ebx
004057e2 mov esp, ebp
004057e4 pop ebp
004057e5 ret 8
004057e8 call 0x403820
004057ed pop edi
004057ee pop esi
004057ef mov al, 1
004057f1 pop ebx
004057f2 mov esp, ebp
004057f4 pop ebp
004057f5 ret 8
