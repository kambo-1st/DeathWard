0088b6f0 push ebp
0088b6f1 mov ebp, esp
0088b6f3 and esp, 0xfffffff8
0088b6f6 sub esp, 0xc
0088b6f9 push ebx
0088b6fa push esi
0088b6fb push edi
0088b6fc mov edi, ecx
0088b6fe cmp byte ptr [edi + 0x11], 0
0088b702 jne 0x88b7ae
0088b708 mov dword ptr [edi], 0
0088b70e mov esi, dword ptr [edi + 4]
0088b711 mov eax, dword ptr [edi + 8]
0088b714 cmp esi, eax
0088b716 je 0x88b7ae
0088b71c lea ebx, [esi + 0xc]
0088b71f nop
0088b720 mov ecx, dword ptr [esi + 8]
0088b723 test ecx, ecx
0088b725 jle 0x88b7a0
0088b727 lea eax, [ecx - 1]
0088b72a mov dword ptr [esi + 8], eax
0088b72d test eax, eax
0088b72f jne 0x88b795
0088b731 mov eax, dword ptr [esi]
0088b733 mov eax, dword ptr [eax + 0x54]
0088b736 or dword ptr [edi], eax
0088b738 mov eax, dword ptr [esi]
0088b73a mov dword ptr [esp + 0x10], eax
0088b73e mov eax, dword ptr [esi + 4]
0088b741 mov dword ptr [esp + 0x14], eax
0088b745 mov eax, dword ptr [edi + 8]
0088b748 sub eax, ebx
0088b74a push eax
0088b74b push ebx
0088b74c push esi
0088b74d call 0x9ec358
0088b752 add dword ptr [edi + 8], -0xc
0088b756 add esp, 0xc
0088b759 mov ecx, dword ptr [edi + 0x14]
0088b75c test ecx, ecx
0088b75e je 0x88b776
0088b760 push dword ptr [esp + 0x14]
0088b764 push dword ptr [esp + 0x14]
0088b768 call 0x75a130
0088b76d mov byte ptr [edi + 0x10], 1
0088b771 mov eax, dword ptr [edi + 8]
0088b774 jmp 0x88b7a6
0088b776 push ecx
0088b777 mov ecx, dword ptr [0xbfd65c]
0088b77d push dword ptr [esp + 0x14]
0088b781 mov ecx, dword ptr [ecx + 0x18190]
0088b787 call 0x7a8cb0
0088b78c mov byte ptr [edi + 0x10], 1
0088b790 mov eax, dword ptr [edi + 8]
0088b793 jmp 0x88b7a6
0088b795 mov eax, dword ptr [edi + 8]
0088b798 add esi, 0xc
0088b79b add ebx, 0xc
0088b79e jmp 0x88b7a6
0088b7a0 add esi, 0xc
0088b7a3 add ebx, 0xc
0088b7a6 cmp esi, eax
0088b7a8 jne 0x88b720
0088b7ae pop edi
0088b7af pop esi
0088b7b0 pop ebx
0088b7b1 mov esp, ebp
0088b7b3 pop ebp
0088b7b4 ret
