006a72e0 add bl, dh
006a72e2 mulps xmm1, xmmword ptr [0xbc7a28]
006a72e9 movss dword ptr [ebp - 8], xmm0
006a72ee movss dword ptr [ebp - 0xc], xmm1
006a72f3 jg 0x6a731b
006a72f5 cmp dword ptr [ebx + 0x14], 0x10
006a72f9 mov eax, ebx
006a72fb jb 0x6a72ff
006a72fd mov eax, dword ptr [ebx]
006a72ff push 0
006a7301 push eax
006a7302 push 0xa0830c
006a7307 push 3
006a7309 call 0x95e330
006a730e movss xmm0, dword ptr [ebp - 8]
006a7313 add esp, 0x10
006a7316 movss xmm1, dword ptr [ebp - 0xc]
006a731b mov eax, dword ptr [ebx + 0x7c]
006a731e movss dword ptr [eax + 0x38], xmm0
006a7323 movss xmm0, dword ptr [0xb6a6f0]
006a732b movss dword ptr [eax + 0x34], xmm1
006a7330 comiss xmm0, dword ptr [edi + 0x2d8]
006a7337 jbe 0x6a7398
006a7339 push 0
006a733b push 0xb4102c
006a7340 mov ecx, ebx
006a7342 mov dword ptr [edi + 0xab4], 0x10
006a734c mov dword ptr [edi + 0x180], 0
006a7356 mov dword ptr [edi + 0x17c], 0
006a7360 call 0x4054f0
006a7365 jmp 0x6a7786
006a736a cmp eax, 0xd
006a736d je 0x6a7398
006a736f mov eax, dword ptr [0xbfd65c]
006a7374 mov edx, 0xb4
006a7379 mov ecx, dword ptr [eax + 0x1a30dc]
006a737f mov eax, 0x12c
006a7384 sub ecx, dword ptr [edi + 0x280]
006a738a cmp dword ptr [edi + 0x17c], 0
006a7391 cmovne eax, edx
006a7394 cmp ecx, eax
006a7396 jg 0x6a7339
006a7398 cmp dword ptr [edi + 0x34], 0x3b7
006a739f jne 0x6a73e1
006a73a1 movss xmm1, dword ptr [0xb6aa0c]
006a73a9 xorps xmm2, xmm2
006a73ac mov ecx, edi
006a73ae call 0x6847e0
006a73b3 test eax, eax
006a73b5 je 0x6a73e1
006a73b7 call 0x6c3d90
006a73bc test al, 3
006a73be jne 0x6a73e1
006a73c0 mov edx, dword ptr [edi]
006a73c2 lea ecx, [ebp - 0x5c]
006a73c5 push 0x1e
006a73c7 call 0x427290
006a73cc push eax
006a73cd push 0
006a73cf push 0x20000
006a73d4 push ecx
006a73d5 mov ecx, edi
006a73d7 mov dword ptr [esp], 0x3f800000
006a73de call dword ptr [edx + 0x20]
006a73e1 movss xmm0, dword ptr [edi + 0x14]
006a73e6 xorps xmm1, xmm1
006a73e9 comiss xmm0, xmm1
006a73ec jbe 0x6a7786
006a73f2 mov eax, dword ptr [edi + 0x18]
006a73f5 and eax, 4
006a73f8 or eax, 0
006a73fb jne 0x6a74be
006a7401 cmp byte ptr [ebp - 1], al
006a7404 jne 0x6a74c8
006a740a mov esi, dword ptr [edi + 8]
006a740d movss xmm5, dword ptr [0xb6a614]
006a7415 cmp esi, dword ptr [edi + 0xc]
006a7418 je 0x6a74b1
006a741e movss xmm4, dword ptr [0xb6a974]
006a7426 lea ebx, [eax + 3]
006a7429 movss xmm2, dword ptr [0xb6a7b0]
006a7431 movss xmm3, dword ptr [0xb6a864]
006a7439 nop dword ptr [eax]
006a7440 movss xmm0, dword ptr [esi]
006a7444 comiss xmm4, xmm0
006a7447 jb 0x6a7478
006a7449 comiss xmm0, xmm1
006a744c jbe 0x6a746e
006a744e call 0x6c3d90
006a7453 xor edx, edx
006a7455 mov ecx, 3
006a745a div ecx
006a745c test edx, edx
006a745e je 0x6a7467
006a7460 movaps xmm1, xmm5
006a7463 mov ebx, ecx
006a7465 jmp 0x6a748d
006a7467 movaps xmm1, xmm2
006a746a mov ebx, ecx
006a746c jmp 0x6a748d
006a746e movss xmm0, dword ptr [edi + 0x2d8]
006a7476 jmp 0x6a74a1
006a7478 call 0x6c3d90
006a747d xor edx, edx
006a747f div ebx
006a7481 test edx, edx
006a7483 je 0x6a748a
006a7485 movaps xmm1, xmm2
006a7488 jmp 0x6a748d
006a748a movaps xmm1, xmm3
006a748d movss xmm0, dword ptr [edi + 0x2d8]
006a7495 subss xmm0, xmm1
006a7499 movss dword ptr [edi + 0x2d8], xmm0
006a74a1 add esi, 0x38
006a74a4 xorps xmm1, xmm1
006a74a7 cmp esi, dword ptr [edi + 0xc]
006a74aa jne 0x6a7440
006a74ac lea ebx, [edi + 0x3c]
006a74af jmp 0x6a74b9
006a74b1 movss xmm0, dword ptr [edi + 0x2d8]
006a74b9 comiss xmm5, xmm0
006a74bc jbe 0x6a74c8
006a74be mov dword ptr [edi + 0x2d8], 0x3f800000
006a74c8 cmp dword ptr [ebx + 0x80], 0
006a74cf movss xmm0, dword ptr [edi + 0x2d8]
006a74d7 mulss xmm0, dword ptr [0xb6a5a4]
006a74df divss xmm0, dword ptr [edi + 0x2dc]
006a74e7 addss xmm0, dword ptr [0xb6a2cc]
006a74ef movaps xmm1, xmm0
006a74f2 mulss xmm0, dword ptr [0xbc7a2c]
006a74fa mulss xmm1, dword ptr [0xbc7a28]
006a7502 movss dword ptr [ebp - 0xc], xmm0
006a7507 movss dword ptr [ebp - 8], xmm1
006a750c jg 0x6a7534
006a750e cmp dword ptr [ebx + 0x14], 0x10
006a7512 mov eax, ebx
006a7514 jb 0x6a7518
006a7516 mov eax, dword ptr [ebx]
006a7518 push 0
006a751a push eax
006a751b push 0xa0830c
006a7520 push 3
006a7522 call 0x95e330
006a7527 movss xmm0, dword ptr [ebp - 0xc]
006a752c add esp, 0x10
006a752f movss xmm1, dword ptr [ebp - 8]
006a7534 mov eax, dword ptr [ebx + 0x7c]
006a7537 movss dword ptr [eax + 0x38], xmm0
006a753c movss xmm0, dword ptr [0xb6a6f0]
006a7544 movss dword ptr [eax + 0x34], xmm1
006a7549 comiss xmm0, dword ptr [edi + 0x2d8]
006a7550 jbe 0x6a7786
006a7556 mov dword ptr [edi + 0xab4], 0x10
006a7560 mov dword ptr [edi + 0x180], 0
006a756a mov dword ptr [edi + 0x17c], 0
006a7574 mov esi, dword ptr [ebx + 0x34]
006a7577 test esi, esi
006a7579 je 0x6a75c3
006a757b cmp dword ptr [esi + 0x14], 0x10
006a757f mov eax, esi
006a7581 jb 0x6a7585
006a7583 mov eax, dword ptr [esi]
006a7585 mov ecx, 0xb4102c
006a758a nop word ptr [eax + eax]
006a7590 mov dl, byte ptr [eax]
006a7592 cmp dl, byte ptr [ecx]
006a7594 jne 0x6a75b0
006a7596 test dl, dl
006a7598 je 0x6a75ac
006a759a mov dl, byte ptr [eax + 1]
006a759d cmp dl, byte ptr [ecx + 1]
006a75a0 jne 0x6a75b0
006a75a2 add eax, 2
006a75a5 add ecx, 2
006a75a8 test dl, dl
006a75aa jne 0x6a7590
006a75ac xor eax, eax
006a75ae jmp 0x6a75b5
006a75b0 sbb eax, eax
006a75b2 or eax, 1
006a75b5 test eax, eax
006a75b7 jne 0x6a75c3
006a75b9 cmp byte ptr [esi + 0x34], al
006a75bc je 0x6a75e1
