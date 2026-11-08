00742453 cmp dword ptr [edi + 0x130c], 0x23
0074245a lea ecx, [edi + 0x2b8]
00742460 movd xmm4, dword ptr [edi + 0x1590]
00742468 xorps xmm0, xmm0
0074246b cvtdq2ps xmm4, xmm4
0074246e movss xmm1, dword ptr [ecx]
00742472 subss xmm4, xmm0
00742476 movss xmm3, dword ptr [ecx + 4]
0074247b movss dword ptr [ebp - 0x68], xmm1
00742480 movss dword ptr [ebp - 0x48], xmm3
00742485 divss xmm4, dword ptr [0xb6aa8c]
0074248d movss dword ptr [ebp - 0x50], xmm4
00742492 jne 0x74252d
00742498 cmp byte ptr [edi + 0x1f88], 0
0074249f jne 0x74252d
007424a5 push 0
007424a7 push 0x4000
007424ac mov ecx, edi
007424ae call 0x4122f0
007424b3 test al, al
007424b5 je 0x7424d4
007424b7 movss xmm0, dword ptr [0xb6a614]
007424bf lea eax, [edi + 0x2b8]
007424c5 movss dword ptr [ebp - 0x4c], xmm0
007424ca movss xmm0, dword ptr [ebp - 0x68]
007424cf jmp 0x7427db
007424d4 push 0x4000000
007424d9 push 0
007424db mov ecx, edi
007424dd call 0x4122f0
007424e2 test al, al
007424e4 je 0x742503
007424e6 movss xmm0, dword ptr [0xb6a5f8]
007424ee lea eax, [edi + 0x2b8]
007424f4 movss dword ptr [ebp - 0x4c], xmm0
007424f9 movss xmm0, dword ptr [ebp - 0x68]
007424fe jmp 0x7427db
00742503 movss xmm1, dword ptr [ebp - 0x50]
00742508 lea eax, [edi + 0x2b8]
0074250e mulss xmm1, dword ptr [0xb6a48c]
00742516 movss xmm0, dword ptr [ebp - 0x68]
0074251b addss xmm1, dword ptr [0xb6a468]
00742523 movss dword ptr [ebp - 0x4c], xmm1
00742528 jmp 0x7427db
0074252d mov eax, dword ptr [edi + 0x160]
00742533 mov edx, dword ptr [edi + 0x164]
00742539 and eax, 0x80
0074253e or eax, 0
00742541 je 0x74254b
00742543 xorps xmm4, xmm4
00742546 movss dword ptr [ebp - 0x50], xmm4
0074254b ucomiss xmm5, xmm0
0074254e lahf 
0074254f test ah, 0x44
00742552 jp 0x74256a
00742554 mov eax, dword ptr [edi + 0x160]
0074255a ucomiss xmm7, xmm0
0074255d mov dword ptr [ebp - 0x44], eax
00742560 lahf 
00742561 test ah, 0x44
00742564 jnp 0x742623
0074256a mov eax, dword ptr [edi + 0x160]
00742570 and eax, 0x8000
00742575 or eax, 0
00742578 je 0x742590
0074257a cmp byte ptr [edi + 0x14b4], 0
00742581 mov eax, dword ptr [edi + 0x160]
00742587 mov dword ptr [ebp - 0x44], eax
0074258a je 0x742623
00742590 movaps xmm2, xmm1
00742593 movaps xmm0, xmm3
00742596 mulss xmm0, xmm7
0074259a movaps xmm1, xmm5
0074259d mulss xmm1, xmm2
007425a1 addss xmm1, xmm0
007425a5 movaps xmm0, xmm5
007425a8 mulss xmm0, xmm1
007425ac mulss xmm1, xmm7
007425b0 subss xmm2, xmm0
007425b4 movss dword ptr [ebp - 0x4c], xmm0
007425b9 movaps xmm0, xmm4
007425bc mulss xmm0, dword ptr [0xb6a34c]
007425c4 subss xmm3, xmm1
007425c8 movss dword ptr [ebp - 0x40], xmm1
007425cd movss dword ptr [ebp - 0x68], xmm2
007425d2 addss xmm0, dword ptr [0xb6a560]
007425da movss dword ptr [ebp - 0x48], xmm3
007425df call 0x4228c0
007425e4 movss xmm1, dword ptr [ebp - 0x68]
007425e9 lea ecx, [edi + 0x2b8]
007425ef movss xmm2, dword ptr [ebp - 0x48]
007425f4 movss xmm5, dword ptr [ebp - 0x60]
007425f9 mulss xmm1, xmm0
007425fd mulss xmm2, xmm0
00742601 addss xmm1, dword ptr [ebp - 0x4c]
00742606 addss xmm2, dword ptr [ebp - 0x40]
0074260b movss dword ptr [ecx], xmm1
0074260f movss dword ptr [ecx + 4], xmm2
00742614 mov eax, dword ptr [edi + 0x160]
0074261a mov edx, dword ptr [edi + 0x164]
00742620 mov dword ptr [ebp - 0x44], eax
00742623 movss xmm0, dword ptr [ecx + 4]
00742628 lea eax, [ebp - 0x40]
0074262b movss xmm1, dword ptr [ecx]
0074262f lea ecx, [ebp - 0x4c]
00742632 movss dword ptr [ebp - 0x48], xmm0
00742637 mulss xmm0, dword ptr [ebp - 0x58]
0074263c mov dword ptr [ebp - 0x4c], 0
00742643 movss dword ptr [ebp - 0x68], xmm1
00742648 mulss xmm1, xmm5
0074264c addss xmm1, xmm0
00742650 movss xmm0, dword ptr [ebp - 0x50]
00742655 mulss xmm0, dword ptr [0xb6a50c]
0074265d subss xmm0, dword ptr [0xb6a350]
00742665 mulss xmm0, xmm1
00742669 comiss xmm0, dword ptr [0xb6a18c]
00742670 movss dword ptr [ebp - 0x40], xmm0
00742675 cmovbe eax, ecx
00742678 and edx, 0x4000000
0074267e movss xmm0, dword ptr [eax]
00742682 xor eax, eax
00742684 or eax, edx
00742686 divss xmm0, dword ptr [edi + 0x14ac]
0074268e addss xmm0, dword ptr [0xb6a864]
00742696 mulss xmm0, dword ptr [0xb6a434]
0074269e movss dword ptr [ebp - 0x40], xmm0
007426a3 je 0x7426af
007426a5 movss xmm0, dword ptr [0xb6a614]
007426ad jmp 0x742702
007426af push 0x3f
007426b1 mov ecx, esi
007426b3 call 0x88b600
007426b8 test al, al
007426ba jne 0x7426ed
007426bc cmp dword ptr [edi + 0x1e2c], 1
007426c3 jg 0x7426ed
007426c5 cmp dword ptr [edi + 0x130c], 0x23
007426cc jne 0x7426d6
007426ce cmp byte ptr [edi + 0x1f88], al
007426d4 je 0x7426ed
007426d6 movss xmm0, dword ptr [ebp - 0x50]
007426db mulss xmm0, dword ptr [0xb6a338]
007426e3 addss xmm0, dword ptr [0xb6a544]
007426eb jmp 0x742702
007426ed movss xmm0, dword ptr [ebp - 0x50]
007426f2 mulss xmm0, dword ptr [0xb6a48c]
007426fa addss xmm0, dword ptr [0xb6a468]
00742702 call 0x4228c0
00742707 movss xmm2, dword ptr [ebp - 0x50]
0074270c lea eax, [edi + 0x2b8]
00742712 comiss xmm2, dword ptr [0xb6a18c]
00742719 movss xmm4, dword ptr [ebp - 0x58]
0074271e mulss xmm4, dword ptr [0xb6a480]
00742726 movss dword ptr [ebp - 0x4c], xmm0
0074272b movss xmm0, dword ptr [ebp - 0x40]
00742730 movaps xmm1, xmm0
00742733 movss xmm3, dword ptr [ebp - 0x68]
00742738 mulss xmm1, dword ptr [0xb6a38c]
00742740 movss xmm5, dword ptr [edi + 0x14ac]
00742748 mulss xmm5, dword ptr [0xb6a8dc]
00742750 subss xmm1, xmm0
00742754 mulss xmm1, xmm2
00742758 addss xmm1, xmm0
0074275c movss xmm0, dword ptr [ebp - 0x60]
00742761 mulss xmm0, dword ptr [0xb6a480]
00742769 mulss xmm0, xmm1
0074276d mulss xmm4, xmm1
00742771 addss xmm0, xmm3
00742775 addss xmm4, dword ptr [edi + 0x2bc]
0074277d movaps xmm6, xmm0
00742780 movss dword ptr [eax], xmm0
00742784 movss dword ptr [edi + 0x2bc], xmm4
0074278c jbe 0x7427db
0074278e mulss xmm6, xmm6
00742792 mulss xmm4, xmm4
00742796 mulss xmm5, xmm5
0074279a addss xmm6, xmm4
0074279e comiss xmm6, xmm5
007427a1 jbe 0x7427db
007427a3 movss xmm1, dword ptr [ebp - 0x48]
007427a8 movaps xmm0, xmm3
007427ab mulss xmm0, xmm3
007427af mulss xmm1, xmm1
007427b3 addss xmm0, xmm1
007427b7 call 0x4228c0
007427bc push ecx
007427bd lea ecx, [edi + 0x2b8]
007427c3 movss dword ptr [esp], xmm0
007427c8 call 0x962860
007427cd movss xmm0, dword ptr [edi + 0x2b8]
007427d5 lea eax, [edi + 0x2b8]
007427db movss xmm1, dword ptr [ebp - 0x4c]
007427e0 mulss xmm0, xmm1
007427e4 movss dword ptr [eax], xmm0
007427e8 mov eax, dword ptr [edi + 0x160]
007427ee and eax, 0x8000
007427f3 movss dword ptr [ebp - 0x40], xmm0
007427f8 or eax, 0
007427fb je 0x742820
007427fd cmp byte ptr [edi + 0x14b4], 0
00742804 jne 0x742820
00742806 movss xmm0, dword ptr [edi + 0x2bc]
0074280e addss xmm0, dword ptr [0xb6a380]
00742816 movss dword ptr [edi + 0x2bc], xmm0
0074281e jmp 0x742830
00742820 mulss xmm1, dword ptr [edi + 0x2bc]
00742828 movss dword ptr [edi + 0x2bc], xmm1
