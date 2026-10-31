00685080 push ebp
00685081 mov ebp, esp
00685083 and esp, 0xfffffff8
00685086 sub esp, 0x34
00685089 mov eax, dword ptr [0xbaa3b4]
0068508e xor eax, esp
00685090 mov dword ptr [esp + 0x30], eax
00685094 push ebx
00685095 push esi
00685096 push edi
00685097 mov edi, dword ptr [ebp + 8]
0068509a mov esi, ecx
0068509c push edi
0068509d call 0x684b00
006850a2 test al, al
006850a4 jne 0x68519f
006850aa push edi
006850ab push dword ptr [ebp + 0xc]
006850ae mov ecx, esi
006850b0 call 0x685020
006850b5 mov ecx, esi
006850b7 mov edx, eax
006850b9 call 0x681710
006850be test al, al
006850c0 je 0x6850dc
006850c2 mov ecx, dword ptr [esi + 0x314]
006850c8 test ecx, ecx
006850ca je 0x6850dc
006850cc nop dword ptr [eax]
006850d0 mov esi, ecx
006850d2 mov ecx, dword ptr [esi + 0x314]
006850d8 test ecx, ecx
006850da jne 0x6850d0
006850dc test edx, edx
006850de je 0x68519f
006850e4 mov edi, dword ptr [esi + 0x160]
006850ea mov eax, edi
006850ec mov ebx, dword ptr [esi + 0x164]
006850f2 and eax, 1
006850f5 or eax, 0
006850f8 jne 0x68519f
006850fe cmp dword ptr [esi + 0x230], eax
00685104 jg 0x68519f
0068510a mov ecx, dword ptr [esi + 0x210]
00685110 test edx, edx
00685112 jle 0x685123
00685114 lea eax, [ecx + edx]
00685117 mov ecx, 0x78
0068511c cmp eax, ecx
0068511e cmovl ecx, eax
00685121 jmp 0x68512a
00685123 neg edx
00685125 cmp ecx, edx
00685127 cmovl ecx, edx
0068512a mov dword ptr [esi + 0x210], ecx
00685130 xorps xmm0, xmm0
00685133 mov eax, dword ptr [esi]
00685135 or edi, 0x20
00685138 push 1
0068513a push 0
0068513c push 0xff
00685141 push ecx
00685142 lea ecx, [esp + 0x20]
00685146 mov dword ptr [esi + 0x160], edi
0068514c movups xmmword ptr [esp + 0x30], xmm0
00685151 push ecx
00685152 movaps xmm0, xmmword ptr [0xb6c0e0]
00685159 mov ecx, esi
0068515b mov dword ptr [esi + 0x164], ebx
00685161 movups xmmword ptr [esp + 0x24], xmm0
00685166 mov dword ptr [esp + 0x44], 0x3e20a0a1
0068516e mov dword ptr [esp + 0x48], 0x3e20a0a1
00685176 mov dword ptr [esp + 0x4c], 0x3e20a0a1
0068517e call dword ptr [eax + 0x38]
00685181 mov eax, dword ptr [esi]
00685183 mov ecx, esi
00685185 mov eax, dword ptr [eax + 0x48]
00685188 call eax
0068518a test al, al
0068518c je 0x685198
0068518e mov dword ptr [esi + 0x230], 0xf0
00685198 mov ecx, esi
0068519a call 0x681390
0068519f mov ecx, dword ptr [esp + 0x3c]
006851a3 pop edi
006851a4 pop esi
006851a5 pop ebx
006851a6 xor ecx, esp
006851a8 call 0x9eacd7
006851ad mov esp, ebp
006851af pop ebp
006851b0 ret 8
