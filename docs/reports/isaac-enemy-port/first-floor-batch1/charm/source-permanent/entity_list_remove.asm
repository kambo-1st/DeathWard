00412500 push ebp
00412501 mov ebp, esp
00412503 push ebx
00412504 push esi
00412505 mov esi, ecx
00412507 push edi
00412508 xor edi, edi
0041250a mov edx, dword ptr [esi + 0xc]
0041250d test edx, edx
0041250f je 0x412578
00412511 mov ebx, dword ptr [ebp + 8]
00412514 mov ecx, edx
00412516 mov eax, dword ptr [esi + 4]
00412519 cmp dword ptr [eax + edi*4], ebx
0041251c je 0x412521
0041251e inc edi
0041251f jmp 0x412572
00412521 cmp edi, edx
00412523 jae 0x412572
00412525 mov eax, dword ptr [esi + 4]
00412528 cmp dword ptr [eax + edi*4], ebx
0041252b jne 0x412572
0041252d cmp edi, edx
0041252f jb 0x412543
00412531 push 0xb3f44c
00412536 push 3
00412538 call 0x95e330
0041253d mov edx, dword ptr [esi + 0xc]
00412540 add esp, 8
00412543 lea ecx, [edx - 1]
00412546 mov eax, edi
00412548 cmp edi, ecx
0041254a jae 0x412566
0041254c nop dword ptr [eax]
00412550 mov ecx, dword ptr [esi + 4]
00412553 lea edx, [ecx + eax*4]
00412556 inc eax
00412557 mov ecx, dword ptr [edx + 4]
0041255a mov dword ptr [edx], ecx
0041255c mov edx, dword ptr [esi + 0xc]
0041255f lea ecx, [edx - 1]
00412562 cmp eax, ecx
00412564 jb 0x412550
00412566 lea ecx, [edx - 1]
00412569 mov dword ptr [esi + 0xc], ecx
0041256c mov edx, ecx
0041256e cmp edi, ecx
00412570 jb 0x412525
00412572 mov edx, ecx
00412574 cmp edi, edx
00412576 jb 0x412516
00412578 pop edi
00412579 pop esi
0041257a pop ebx
0041257b pop ebp
0041257c ret 4
