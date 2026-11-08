00489420 push ebp
00489421 mov ebp, esp
00489423 sub esp, 0xc
00489426 mov eax, ecx
00489428 push ebx
00489429 push esi
0048942a mov dword ptr [ebp - 0xc], eax
0048942d xor ebx, ebx
0048942f mov esi, dword ptr [eax]
00489431 mov edx, dword ptr [eax + 4]
00489434 xor eax, eax
00489436 sub edx, esi
00489438 mov dword ptr [ebp - 4], esi
0048943b sar edx, 3
0048943e push edi
0048943f test edx, edx
00489441 je 0x4894d7
00489447 cmp edx, 8
0048944a jb 0x4894d7
00489450 mov ecx, edx
00489452 mov edi, edx
00489454 and ecx, 7
00489457 xorps xmm5, xmm5
0048945a sub edi, ecx
0048945c xorps xmm4, xmm4
0048945f nop 
00489460 movd xmm2, dword ptr [esi + eax*8 + 0x1c]
00489466 movd xmm0, dword ptr [esi + eax*8 + 0x14]
0048946c movd xmm1, dword ptr [esi + eax*8 + 0xc]
00489472 movd xmm3, dword ptr [esi + eax*8 + 4]
00489478 punpckldq xmm3, xmm0
0048947c movd xmm0, dword ptr [esi + eax*8 + 0x34]
00489482 punpckldq xmm1, xmm2
00489486 movd xmm2, dword ptr [esi + eax*8 + 0x3c]
0048948c punpckldq xmm3, xmm1
00489490 movd xmm1, dword ptr [esi + eax*8 + 0x2c]
00489496 paddd xmm5, xmm3
0048949a movd xmm3, dword ptr [esi + eax*8 + 0x24]
004894a0 add eax, 8
004894a3 punpckldq xmm3, xmm0
004894a7 punpckldq xmm1, xmm2
004894ab punpckldq xmm3, xmm1
004894af paddd xmm4, xmm3
004894b3 cmp eax, edi
004894b5 jb 0x489460
004894b7 paddd xmm4, xmm5
004894bb movaps xmm0, xmm4
004894be psrldq xmm0, 8
004894c3 paddd xmm4, xmm0
004894c7 movups xmm0, xmm4
004894ca psrldq xmm0, 4
004894cf paddd xmm4, xmm0
004894d3 movd ebx, xmm4
004894d7 xor esi, esi
004894d9 xor edi, edi
004894db cmp eax, edx
004894dd jae 0x48951c
004894df mov ecx, edx
004894e1 sub ecx, eax
004894e3 cmp ecx, 2
004894e6 jb 0x489510
004894e8 lea ecx, [edx - 1]
004894eb mov dword ptr [ebp - 8], ecx
004894ee mov ecx, dword ptr [ebp - 4]
004894f1 add esi, dword ptr [ecx + eax*8 + 4]
004894f5 add edi, dword ptr [ecx + eax*8 + 0xc]
004894f9 add eax, 2
004894fc cmp eax, dword ptr [ebp - 8]
004894ff jb 0x4894f1
00489501 cmp eax, edx
00489503 jae 0x489517
00489505 jmp 0x489513
00489507 nop word ptr [eax + eax]
00489510 mov ecx, dword ptr [ebp - 4]
00489513 add ebx, dword ptr [ecx + eax*8 + 4]
00489517 lea eax, [edi + esi]
0048951a add ebx, eax
0048951c mov edx, dword ptr [ebp + 8]
0048951f test edx, edx
00489521 jne 0x48953a
00489523 push 0xb4d6c4
00489528 push 3
0048952a call 0x95e330
0048952f mov edx, dword ptr [ebp + 8]
00489532 add esp, 8
00489535 test edx, edx
00489537 jne 0x48953a
00489539 int3 
0048953a mov ecx, dword ptr [ebp + 0xc]
0048953d mov eax, edx
0048953f shr eax, cl
00489541 mov ecx, dword ptr [ebp + 0x10]
00489544 xor eax, edx
00489546 mov edx, eax
00489548 shl edx, cl
0048954a mov ecx, dword ptr [ebp + 0x14]
0048954d xor edx, eax
0048954f mov eax, edx
00489551 shr eax, cl
00489553 xor eax, edx
00489555 mov dword ptr [ebp + 8], eax
00489558 test ebx, ebx
0048955a jne 0x489560
0048955c xor edi, edi
0048955e jmp 0x489566
00489560 xor edx, edx
00489562 div ebx
00489564 mov edi, edx
00489566 mov esi, dword ptr [ebp - 0xc]
00489569 xor eax, eax
0048956b xor ecx, ecx
0048956d mov ebx, dword ptr [esi]
0048956f mov esi, dword ptr [esi + 4]
00489572 sub esi, ebx
00489574 sar esi, 3
00489577 test esi, esi
00489579 je 0x489592
0048957b lea edx, [ebx + 4]
0048957e nop 
00489580 add eax, dword ptr [edx]
00489582 cmp edi, eax
00489584 jl 0x4895ac
00489586 inc ecx
00489587 add edx, 8
0048958a cmp ecx, esi
0048958c jb 0x489580
0048958e test eax, eax
00489590 jg 0x4895a1
00489592 push 0xb41340
00489597 push 3
00489599 call 0x95e330
0048959e add esp, 8
004895a1 xor eax, eax
004895a3 pop edi
004895a4 pop esi
004895a5 pop ebx
004895a6 mov esp, ebp
004895a8 pop ebp
004895a9 ret 0x10
004895ac mov eax, dword ptr [ebx + ecx*8]
004895af pop edi
004895b0 pop esi
004895b1 pop ebx
004895b2 mov esp, ebp
004895b4 pop ebp
004895b5 ret 0x10
