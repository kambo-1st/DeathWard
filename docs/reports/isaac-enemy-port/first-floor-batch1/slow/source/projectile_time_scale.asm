0062f440 push ebp
0062f441 mov ebp, esp
0062f443 and esp, 0xfffffff8
0062f446 sub esp, 0x14
0062f449 push ebx
0062f44a push esi
0062f44b mov esi, ecx
0062f44d push edi
0062f44e push esi
0062f44f push ecx
0062f450 mov ecx, dword ptr [0xbfd65c]
0062f456 mov ecx, dword ptr [ecx + 0x18190]
0062f45c call 0x7a8ef0
0062f461 mov eax, dword ptr [esi + 0x38c]
0062f467 mov edi, dword ptr [esi + 0x388]
0062f46d movss xmm1, dword ptr [0xb6a480]
0062f475 mov dword ptr [esp + 0x1c], eax
0062f479 mov eax, edi
0062f47b and eax, 0x80000080
0062f480 movss dword ptr [esp + 0x10], xmm0
0062f486 cmp eax, 0x80000080
0062f48b jne 0x62f4ae
0062f48d mov eax, dword ptr [0xbfd65c]
0062f492 mov eax, dword ptr [eax + 0x18190]
0062f498 cmp dword ptr [eax + 0x7120], 0
0062f49f jle 0x62f5a3
0062f4a5 mulss xmm0, xmm1
0062f4a9 jmp 0x62f5a3
0062f4ae mov eax, dword ptr [esi + 0x314]
0062f4b4 test eax, eax
0062f4b6 je 0x62f4cc
0062f4b8 mov eax, dword ptr [eax + 0x160]
0062f4be and eax, 0x20000000
0062f4c3 or eax, 0
0062f4c6 jne 0x62f5a3
0062f4cc mov ebx, dword ptr [0xbfd65c]
0062f4d2 push 0xe8
0062f4d7 mov eax, dword ptr [ebx + 0x18190]
0062f4dd add eax, 0x71f4
0062f4e2 mov ecx, eax
0062f4e4 mov dword ptr [esp + 0x18], eax
0062f4e8 call 0x88b570
0062f4ed test al, al
0062f4ef jne 0x62f581
0062f4f5 cmp dword ptr [ebx + 0x1c319c], 0x16
0062f4fc je 0x62f50d
0062f4fe mov eax, dword ptr [ebx + 0x18190]
0062f504 cmp dword ptr [eax + 0x1210], 1
0062f50b je 0x62f581
0062f50d mov ecx, dword ptr [esp + 0x14]
0062f511 push 0x42
0062f513 call 0x88b7c0
0062f518 test eax, eax
0062f51a je 0x62f595
0062f51c movd xmm1, dword ptr [eax + 8]
0062f521 lea ecx, [esp + 0x18]
0062f525 cvtdq2ps xmm1, xmm1
0062f528 mov dword ptr [esp + 0x14], 0
0062f530 lea eax, [esp + 0x14]
0062f534 xorps xmm0, xmm0
0062f537 subss xmm1, xmm0
0062f53b divss xmm1, dword ptr [0xb6aa0c]
0062f543 comiss xmm0, xmm1
0062f546 movss dword ptr [esp + 0x18], xmm1
0062f54c movss xmm1, dword ptr [0xb6a614]
0062f554 cmovbe eax, ecx
0062f557 movss xmm0, dword ptr [eax]
0062f55b comiss xmm0, xmm1
0062f55e ja 0x62f566
0062f560 movss xmm0, xmm0
0062f564 jmp 0x62f56a
0062f566 movss xmm0, xmm1
0062f56a mulss xmm0, dword ptr [0xb6a480]
0062f572 subss xmm1, xmm0
0062f576 mulss xmm1, dword ptr [esp + 0x10]
0062f57c movaps xmm0, xmm1
0062f57f jmp 0x62f59b
0062f581 movss xmm0, dword ptr [esp + 0x10]
0062f587 movss xmm1, dword ptr [0xb6a480]
0062f58f mulss xmm0, xmm1
0062f593 jmp 0x62f5a3
0062f595 movss xmm0, dword ptr [esp + 0x10]
0062f59b movss xmm1, dword ptr [0xb6a480]
0062f5a3 and edi, 0x1000000
0062f5a9 or edi, 0
0062f5ac je 0x62f5b2
0062f5ae mulss xmm0, xmm1
0062f5b2 cmp dword ptr [esi + 0x274], 0
0062f5b9 jg 0x62f5c4
0062f5bb cmp dword ptr [esi + 0x348], 0
0062f5c2 jle 0x62f5cc
0062f5c4 mulss xmm0, dword ptr [0xb6a234]
0062f5cc pop edi
0062f5cd pop esi
0062f5ce pop ebx
0062f5cf mov esp, ebp
0062f5d1 pop ebp
0062f5d2 ret 
