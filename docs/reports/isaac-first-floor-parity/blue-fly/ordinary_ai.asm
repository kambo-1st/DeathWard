005f7340 push ebp
005f7341 mov ebp, esp
005f7343 and esp, 0xfffffff8
005f7346 sub esp, 0x10
005f7349 push esi
005f734a mov esi, ecx
005f734c push edi
005f734d mov eax, dword ptr [esi + 0xcd4]
005f7353 test eax, eax
005f7355 jle 0x5f7398
005f7357 movss xmm0, dword ptr [esi + 0x2c4]
005f735f add eax, -1
005f7362 mulss xmm0, dword ptr [0xb6a5e8]
005f736a mov dword ptr [esi + 0xcd4], eax
005f7370 mov dword ptr [esi + 0x180], 0
005f737a movss dword ptr [esi + 0x2c4], xmm0
005f7382 jne 0x5f75ed
005f7388 mov dword ptr [esi + 0x180], 4
005f7392 pop edi
005f7393 pop esi
005f7394 mov esp, ebp
005f7396 pop ebp
005f7397 ret 
005f7398 cmp dword ptr [esi + 0x30], 1
005f739c movss xmm0, dword ptr [0xb6aba8]
005f73a4 jne 0x5f73dd
005f73a6 mov eax, dword ptr [0xbfd65c]
005f73ab movss xmm0, dword ptr [0xb6ac60]
005f73b3 mov ecx, dword ptr [eax + 0x18190]
005f73b9 cmp byte ptr [ecx], 0
005f73bc je 0x5f73cf
005f73be mov eax, dword ptr [eax + 0x1a30dc]
005f73c4 sub eax, dword ptr [ecx + 0x11f0]
005f73ca cmp eax, 0x3c
005f73cd jge 0x5f73dd
005f73cf mov dword ptr [esi + 0x31c], 0
005f73d9 xor eax, eax
005f73db jmp 0x5f7418
005f73dd call 0x6c3d90
005f73e2 xor edx, edx
005f73e4 mov ecx, 3
005f73e9 div ecx
005f73eb test edx, edx
005f73ed je 0x5f73f5
005f73ef cmp dword ptr [esi + 0x30], 1
005f73f3 jne 0x5f7413
005f73f5 push ecx
005f73f6 mov dword ptr [esp], 0x41700000
005f73fd push 0xc02fec
005f7402 push 0
005f7404 push 0xd
005f7406 push ecx
005f7407 mov ecx, esi
005f7409 movss dword ptr [esp], xmm0
005f740e call 0x5f6830
005f7413 mov eax, 4
005f7418 lea edi, [esi + 0x314]
005f741e mov dword ptr [esi + 0x180], eax
005f7424 mov ecx, dword ptr [edi]
005f7426 test ecx, ecx
005f7428 je 0x5f7474
005f742a cmp byte ptr [ecx + 0x16b], 0
005f7431 jne 0x5f743c
005f7433 cmp dword ptr [ecx + 0x180], 0
005f743a jne 0x5f7474
005f743c lea eax, [esp + 8]
005f7440 mov dword ptr [esp + 8], edi
005f7444 push eax
005f7445 add ecx, 0x324
005f744b call 0x4bc3c0
005f7450 mov eax, dword ptr [esi + 0xcc0]
005f7456 mov dword ptr [edi], 0
005f745c test eax, eax
005f745e js 0x5f7474
005f7460 push 0
005f7462 push eax
005f7463 mov ecx, esi
005f7465 call 0x5f3a70
005f746a mov dword ptr [esi + 0xcc0], 0xffffffff
005f7474 mov eax, dword ptr [esi + 0x31c]
005f747a test eax, eax
005f747c jne 0x5f74fb
005f747e cmp dword ptr [esi + 0xcc0], -1
005f7485 jne 0x5f74bc
005f7487 mov dword ptr [esi + 0xcc0], 1
005f7491 mov ecx, esi
005f7493 movss xmm1, dword ptr [0xbc4548]
005f749b movss xmm0, dword ptr [0xbc4544]
005f74a3 push 1
005f74a5 push 1
005f74a7 movss dword ptr [esi + 0xcb4], xmm0
005f74af movss dword ptr [esi + 0xcb8], xmm1
005f74b7 call 0x5f3a70
005f74bc mov ecx, esi
005f74be call 0x5f39b0
005f74c3 mov ecx, dword ptr [eax + 0x294]
005f74c9 mov eax, dword ptr [eax + 0x298]
005f74cf mov dword ptr [esp + 0x14], eax
005f74d3 lea eax, [esp + 0x10]
005f74d7 push eax
005f74d8 lea eax, [esp + 0xc]
005f74dc mov dword ptr [esp + 0x14], ecx
005f74e0 push eax
005f74e1 mov ecx, esi
005f74e3 call 0x5f4f60
005f74e8 mov ecx, dword ptr [eax]
005f74ea mov dword ptr [esi + 0x28c], ecx
005f74f0 mov eax, dword ptr [eax + 4]
005f74f3 mov dword ptr [esi + 0x290], eax
005f74f9 jmp 0x5f7539
005f74fb movss xmm0, dword ptr [eax + 0x294]
005f7503 movss xmm1, dword ptr [eax + 0x298]
005f750b movss dword ptr [esi + 0x28c], xmm0
005f7513 movss dword ptr [esi + 0x290], xmm1
005f751b mov eax, dword ptr [esi + 0xcc0]
005f7521 test eax, eax
005f7523 js 0x5f7539
005f7525 push 0
005f7527 push eax
005f7528 mov ecx, esi
005f752a call 0x5f3a70
005f752f mov dword ptr [esi + 0xcc0], 0xffffffff
005f7539 movss xmm1, dword ptr [esi + 0x290]
005f7541 subss xmm1, dword ptr [esi + 0x298]
005f7549 movss xmm2, dword ptr [esi + 0x28c]
005f7551 subss xmm2, dword ptr [esi + 0x294]
005f7559 movaps xmm0, xmm1
005f755c movss dword ptr [esp + 0x10], xmm1
005f7562 mulss xmm0, xmm1
005f7566 movaps xmm1, xmm2
005f7569 movss dword ptr [esp + 8], xmm2
005f756f mulss xmm1, xmm2
005f7573 addss xmm0, xmm1
005f7577 call 0x4228c0
005f757c comiss xmm0, dword ptr [0xb6a2cc]
005f7583 jb 0x5f759e
005f7585 movaps xmm1, xmm0
005f7588 mulss xmm1, dword ptr [0xb6a304]
005f7590 minss xmm1, dword ptr [0xb6a7b0]
005f7598 divss xmm1, xmm0
005f759c jmp 0x5f75a1
005f759e xorps xmm1, xmm1
005f75a1 movss xmm0, dword ptr [esp + 8]
005f75a7 mulss xmm0, xmm1
005f75ab addss xmm0, dword ptr [esi + 0x2b8]
005f75b3 movss dword ptr [esi + 0x2b8], xmm0
005f75bb movss xmm0, dword ptr [esp + 0x10]
005f75c1 mulss xmm0, xmm1
005f75c5 addss xmm0, dword ptr [esi + 0x2bc]
005f75cd movss dword ptr [esi + 0x2bc], xmm0
005f75d5 movss xmm0, dword ptr [esi + 0x2c4]
005f75dd mulss xmm0, dword ptr [0xb6a560]
005f75e5 movss dword ptr [esi + 0x2c4], xmm0
005f75ed pop edi
005f75ee pop esi
005f75ef mov esp, ebp
005f75f1 pop ebp
005f75f2 ret 
