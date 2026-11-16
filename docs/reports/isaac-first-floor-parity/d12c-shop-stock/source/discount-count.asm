007d1751 mov ecx, dword ptr [0xbfd65c]
007d1757 push 0x40
007d1759 lea ecx, [ecx + 0x1ba40]
007d175f call 0x91d940
007d1764 mov ebx, dword ptr [0xbfd65c]
007d176a mov dword ptr [ebp + 0xc], eax
007d176d test eax, eax
007d176f jne 0x7d17a4
007d1771 test esi, esi
007d1773 js 0x7d1786
007d1775 mov eax, dword ptr [ebp - 4]
007d1778 mov eax, dword ptr [eax + 4]
007d177b movsx eax, word ptr [eax + 0xae]
007d1782 cmp eax, esi
007d1784 je 0x7d179d
007d1786 mov ecx, dword ptr [ebx + 0x18190]
007d178c push 0x40
007d178e add ecx, 0x71f4
007d1794 call 0x88b570
007d1799 test al, al
007d179b je 0x7d17a4
007d179d mov dword ptr [ebp + 0xc], 1
007d17a4 mov eax, dword ptr [ebp - 4]
007d17a7 cmp dword ptr [eax + 8], 2
007d17ab jne 0x7d17cf
007d17ad push 1
007d17af push 0
007d17b1 lea ecx, [ebx + 0x1ba40]
007d17b7 push 0xd
007d17b9 call 0x91d550
007d17be mov ebx, dword ptr [0xbfd65c]
007d17c4 test eax, eax
007d17c6 je 0x7d17cf
007d17c8 mov edi, 0xfffffc18
007d17cd jmp 0x7d1827
007d17cf mov eax, dword ptr [ebp + 0xc]
007d17d2 cmp eax, 1
007d17d5 jl 0x7d1827
007d17d7 cmp edi, 5
007d17da jle 0x7d17ec
007d17dc cmp eax, 1
007d17df jne 0x7d17f0
007d17e1 mov eax, edi
007d17e3 cdq
007d17e4 sub eax, edx
007d17e6 mov edi, eax
007d17e8 sar edi, 1
007d17ea jmp 0x7d1827
007d17ec test edi, edi
007d17ee jle 0x7d1827
007d17f0 inc eax
007d17f1 xorps xmm1, xmm1
007d17f4 xorps xmm0, xmm0
007d17f7 sub esp, 8
007d17fa cvtsi2ss xmm1, edi
007d17fe cvtsi2ss xmm0, eax
007d1802 divss xmm1, xmm0
007d1806 movss dword ptr [ebp + 0xc], xmm1
007d180b fld dword ptr [ebp + 0xc]
007d180e fstp qword ptr [esp]
007d1811 call 0x9ec3ac
007d1816 fstp dword ptr [ebp + 0xc]
007d1819 fld dword ptr [ebp + 0xc]
007d181c add esp, 8
007d181f fstp dword ptr [ebp + 0xc]
007d1822 cvttss2si edi, dword ptr [ebp + 0xc]
