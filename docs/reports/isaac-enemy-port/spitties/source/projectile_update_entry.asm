0062f6f0 push ebp
0062f6f1 mov ebp, esp
0062f6f3 push -1
0062f6f5 push 0x9f1c63
0062f6fa mov eax, dword ptr fs:[0]
0062f700 push eax
0062f701 sub esp, 0x56c
0062f707 mov eax, dword ptr [0xbaa3b4]
0062f70c xor eax, ebp
0062f70e mov dword ptr [ebp - 0x10], eax
0062f711 push esi
0062f712 push edi
0062f713 push eax
0062f714 lea eax, [ebp - 0xc]
0062f717 mov dword ptr fs:[0], eax
0062f71d mov edi, ecx
0062f71f mov dword ptr [ebp - 0x320], edi
0062f725 mov dword ptr [ebp - 0x334], 0
0062f72f call 0x62f440
0062f734 mov eax, dword ptr [edi + 0x274]
0062f73a movss dword ptr [edi + 0x2f4], xmm0
0062f742 test eax, eax
0062f744 jle 0x62f74d
0062f746 dec eax
0062f747 mov dword ptr [edi + 0x274], eax
0062f74d mov eax, dword ptr [edi + 0x388]
0062f753 and eax, 0x40003810
0062f758 or eax, 0
0062f75b je 0x62f764
0062f75d mov byte ptr [edi + 0x188], 0
0062f764 mov eax, dword ptr [edi + 0x160]
0062f76a and eax, 0x20
0062f76d or eax, 0
0062f770 je 0x62f7d9
0062f772 cmp dword ptr [edi + 0x210], 0
0062f779 jg 0x62f7d9
0062f77b call 0x6c3d90
0062f780 xor edx, edx
0062f782 mov ecx, 7
0062f787 div ecx
0062f789 push 0
0062f78b add edx, 0xc
0062f78e mov ecx, edi
0062f790 push edx
0062f791 call 0x684790
0062f796 test al, al
0062f798 je 0x62f7d9
0062f79a and dword ptr [edi + 0x160], 0xffffffdf
0062f7a1 mov eax, dword ptr [edi + 0x164]
0062f7a7 mov dword ptr [edi + 0x164], eax
0062f7ad movss xmm0, dword ptr [0xc02fec]
0062f7b5 movss dword ptr [edi + 0x3a8], xmm0
0062f7bd movss xmm0, dword ptr [0xc02ff0]
0062f7c5 movss dword ptr [edi + 0x3ac], xmm0
0062f7cd mov eax, dword ptr [edi]
0062f7cf mov ecx, edi
0062f7d1 call dword ptr [eax + 0x28]
0062f7d4 jmp 0x636fba
0062f7d9 mov eax, dword ptr [edi + 0x160]
0062f7df and eax, 0x20
0062f7e2 or eax, 0
0062f7e5 je 0x62f81c
0062f7e7 cmp byte ptr [edi + 0x16b], 0
0062f7ee jne 0x62f81c
0062f7f0 movss xmm0, dword ptr [0xc02fec]
0062f7f8 mov ecx, edi
0062f7fa movss dword ptr [edi + 0x2b8], xmm0
0062f802 movss xmm0, dword ptr [0xc02ff0]
0062f80a movss dword ptr [edi + 0x2bc], xmm0
0062f812 call 0x6860a0
