00685400 push ebp
00685401 mov ebp, esp
00685403 and esp, 0xfffffff8
00685406 push esi
00685407 push edi
00685408 mov edi, dword ptr [ebp + 8]
0068540b mov esi, ecx
0068540d push edi
0068540e call 0x684b00
00685413 test al, al
00685415 jne 0x685500
0068541b push edi
0068541c push dword ptr [ebp + 0xc]
0068541f mov ecx, esi
00685421 call 0x685020
00685426 mov ecx, esi
00685428 mov edx, eax
0068542a call 0x681710
0068542f test al, al
00685431 je 0x68544c
00685433 mov ecx, dword ptr [esi + 0x314]
00685439 test ecx, ecx
0068543b je 0x68544c
0068543d nop dword ptr [eax]
00685440 mov esi, ecx
00685442 mov ecx, dword ptr [esi + 0x314]
00685448 test ecx, ecx
0068544a jne 0x685440
0068544c test edx, edx
0068544e jle 0x6854b8
00685450 mov ecx, dword ptr [esi + 0x160]
00685456 mov eax, ecx
00685458 mov edi, dword ptr [esi + 0x164]
0068545e and eax, 1
00685461 or eax, 0
00685464 jne 0x6854ec
0068546a cmp dword ptr [esi + 0x230], eax
00685470 jg 0x6854ec
00685472 mov eax, dword ptr [esi]
00685474 or ecx, 0x80
0068547a add dword ptr [esi + 0x218], edx
00685480 push 1
00685482 push 0
00685484 push 0xff
00685489 mov dword ptr [esi + 0x160], ecx
0068548f lea ecx, [ebp + 0x14]
00685492 push edx
00685493 push ecx
00685494 mov ecx, esi
00685496 mov dword ptr [esi + 0x164], edi
0068549c call dword ptr [eax + 0x38]
0068549f mov eax, dword ptr [esi]
006854a1 mov ecx, esi
006854a3 mov eax, dword ptr [eax + 0x48]
006854a6 call eax
006854a8 test al, al
006854aa je 0x6854ec
006854ac mov dword ptr [esi + 0x230], 0xf0
006854b6 jmp 0x6854ec
006854b8 jns 0x6854ec
006854ba mov ecx, dword ptr [esi + 0x160]
006854c0 mov eax, ecx
006854c2 mov edx, dword ptr [esi + 0x164]
006854c8 and eax, 1
006854cb or eax, 0
006854ce jne 0x6854ec
006854d0 or ecx, 0x80
006854d6 mov dword ptr [esi + 0x218], 2
006854e0 mov dword ptr [esi + 0x160], ecx
006854e6 mov dword ptr [esi + 0x164], edx
006854ec movss xmm0, dword ptr [ebp + 0x10]
006854f1 mov ecx, esi
006854f3 movss dword ptr [esi + 0x304], xmm0
006854fb call 0x681390
00685500 pop edi
00685501 pop esi
00685502 mov esp, ebp
00685504 pop ebp
00685505 ret 0x38
