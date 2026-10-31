00416340 push ebp
00416341 mov ebp, esp
00416343 push ecx
00416344 push esi
00416345 mov esi, ecx
00416347 push edi
00416348 mov eax, dword ptr [esi + 0x3c]
0041634b add eax, 0x32
0041634e cmp eax, dword ptr [esi + 0x38]
00416351 jb 0x416369
00416353 push 0xb3f568
00416358 push 0
0041635a call 0x95e330
0041635f add esp, 8
00416362 pop edi
00416363 pop esi
00416364 pop ecx
00416365 pop ebp
00416366 ret 4
00416369 mov edi, dword ptr [ebp + 8]
0041636c lea ecx, [esi + 0x20]
0041636f push edi
00416370 call 0x412500
00416375 mov edx, dword ptr [esi + 0x3c]
00416378 xor ecx, ecx
0041637a test edx, edx
0041637c je 0x41638d
0041637e mov eax, dword ptr [esi + 0x34]
00416381 cmp edi, dword ptr [eax]
00416383 je 0x4163b0
00416385 inc ecx
00416386 add eax, 4
00416389 cmp ecx, edx
0041638b jb 0x416381
0041638d lea eax, [edx + 1]
00416390 cmp eax, dword ptr [esi + 0x38]
00416393 jbe 0x4163a7
00416395 push 0xb3f428
0041639a push 3
0041639c call 0x95e330
004163a1 mov edx, dword ptr [esi + 0x3c]
004163a4 add esp, 8
004163a7 mov eax, dword ptr [esi + 0x34]
004163aa mov dword ptr [eax + edx*4], edi
004163ad inc dword ptr [esi + 0x3c]
004163b0 pop edi
004163b1 pop esi
004163b2 pop ecx
004163b3 pop ebp
004163b4 ret 4
