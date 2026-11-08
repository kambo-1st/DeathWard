006c25d6 cmp dword ptr [esi + 0x2c], 0x14
006c25da jne 0x6c26cc
006c25e0 cmp dword ptr [esi + 0x30], 7
006c25e4 jne 0x6c26cc
006c25ea movd xmm1, dword ptr [esi + 0x4e8]
006c25f2 movss xmm0, dword ptr [0xb6a604]
006c25fa cvtdq2ps xmm1, xmm1
006c25fd call 0x4c3f60
006c2602 lea eax, [esi + 0x334]
006c2608 movss dword ptr [ebp - 0xc4], xmm0
006c2610 mov ecx, eax
006c2612 mov dword ptr [ebp - 0x8c], eax
006c2618 call 0x7a7db0
006c261d movss xmm0, dword ptr [ebp - 0xc4]
006c2625 fstp dword ptr [ebp - 0x14]
006c2628 comiss xmm0, dword ptr [ebp - 0x14]
006c262c jb 0x6c26cc
006c2632 mov esi, dword ptr [0xbfd65c]
006c2638 lea eax, [ebp - 0xbc]
006c263e push 0
006c2640 push 1
006c2642 sub esp, 8
006c2645 mov ecx, dword ptr [esi + 0x18190]
006c264b mov dword ptr [esp + 4], 0
006c2653 mov dword ptr [esp], 0
006c265a push eax
006c265b call 0x7d9b50
006c2660 mov ecx, dword ptr [esi + 0x18190]
006c2666 push eax
006c2667 lea eax, [ebp - 0xcc]
006c266d push eax
006c266e call 0x7cf240
006c2673 mov ecx, dword ptr [ebp - 0x8c]
006c2679 inc dword ptr [0xbfd658]
006c267f call 0x7a7e20
006c2684 mov esi, dword ptr [ebp - 0x7c]
006c2687 mov ecx, dword ptr [0xbfd65c]
006c268d push eax
006c268e lea eax, [ebp - 0xcc]
006c2694 push dword ptr [esi + 0x30]
006c2697 push 0
006c2699 push 0xc02fec
006c269e push eax
006c269f push dword ptr [esi + 0x2c]
006c26a2 push dword ptr [esi + 0x28]
006c26a5 call 0x422e20
006c26aa mov ecx, dword ptr [esi + 0x4e8]
006c26b0 inc ecx
006c26b1 push 0
006c26b3 mov dword ptr [eax + 0x4e8], ecx
006c26b9 lea ecx, [eax + 0x3c]
006c26bc push 0xb49744
006c26c1 call 0x4054f0
006c26c6 dec dword ptr [0xbfd658]
