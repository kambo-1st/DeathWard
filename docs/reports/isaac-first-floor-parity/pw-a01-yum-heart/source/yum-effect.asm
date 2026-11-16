005a2818 mov eax, dword ptr [ebp - 0x588]
005a281e cmp dword ptr [eax + 0x2c], 0
005a2822 jne 0x5a26bb
005a2828 mov esi, dword ptr [ebp - 0x588]
005a282e mov eax, 0x9d
005a2833 movss xmm2, dword ptr [0xb6a614]
005a283b push ecx
005a283c mov dword ptr [esp], 0x3f800000
005a2843 mov ecx, 0x266
005a2848 cmp dword ptr [esi + 0x130c], 0x16
005a284f push 0
005a2851 cmove eax, ecx
005a2854 mov ecx, esi
005a2856 push 2
005a2858 push eax
005a2859 call 0x68d750
005a285e mov ecx, dword ptr [0xbfd65c]
005a2864 xor edi, edi
005a2866 call 0x4127b0
005a286b test eax, eax
005a286d je 0x5a289e
005a286f nop
005a2870 mov ecx, dword ptr [0xbfd65c]
005a2876 push edi
005a2877 call 0x412750
005a287c mov ecx, eax
005a287e xor eax, eax
005a2880 cmp ecx, esi
005a2882 push 0
005a2884 sete al
005a2887 inc eax
005a2888 push eax
005a2889 call 0x724f00
005a288e mov ecx, dword ptr [0xbfd65c]
005a2894 inc edi
005a2895 call 0x4127b0
005a289a cmp edi, eax
005a289c jb 0x5a2870
005a289e mov eax, esi
005a28a0 jmp 0x5a26b5
