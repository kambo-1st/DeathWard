006d1280 mov esi, dword ptr [ebx + 0xc]
006d1283 lea ecx, [ebp - 0x68]
006d1286 mov edi, dword ptr [0xbfd65c]
006d128c push esi
006d128d call 0x4229a0
006d1292 mov dl, byte ptr [ebx + 0x18]
006d1295 test esi, esi
006d1297 je 0x6d12c1
006d1299 mov eax, dword ptr [esi + 0x28]
006d129c cmp eax, 1
006d129f je 0x6d12b6
006d12a1 cmp eax, 3
006d12a4 jne 0x6d12c1
006d12a6 mov eax, dword ptr [esi + 0x160]
006d12ac and eax, 0x100
006d12b1 or eax, 0
006d12b4 jne 0x6d12c1
006d12b6 mov al, 1
006d12b8 test dl, dl
006d12ba jne 0x6d12e0
006d12bc mov byte ptr [ebp - 0x11], dl
006d12bf jmp 0x6d12e8
006d12c1 xor al, al
006d12c3 test esi, esi
006d12c5 je 0x6d12e0
006d12c7 mov eax, dword ptr [esi + 0x160]
006d12cd and eax, 0x20000000
006d12d2 or eax, 0
006d12d5 je 0x6d12de
006d12d7 xor al, al
006d12d9 mov byte ptr [ebp - 0x11], al
006d12dc jmp 0x6d12e8
006d12de xor al, al
006d12e0 mov byte ptr [ebp - 0x11], 1
006d12e4 test esi, esi
006d12e6 je 0x6d1311
006d12e8 test al, al
006d12ea jne 0x6d1319
006d12ec mov eax, dword ptr [esi + 0x164]
006d12f2 mov ecx, dword ptr [esi + 0x160]
006d12f8 mov dword ptr [ebp - 0x1c], eax
006d12fb mov eax, ecx
006d12fd and eax, 0x100
006d1302 or eax, 0
006d1305 jne 0x6d1319
006d1307 and ecx, 0x20000000
006d130d or ecx, eax
006d130f jne 0x6d1319
006d1311 mov byte ptr [ebp - 0x12], 0
006d1315 test dl, dl
006d1317 je 0x6d131d
006d1319 mov byte ptr [ebp - 0x12], 1
006d131d mov ecx, dword ptr [edi + 0x18190]
006d1323 lea eax, [ebp - 0x30]
006d1326 push -1
006d1328 push dword ptr [ebx + 8]
006d132b add ecx, 0x1218
006d1331 push eax
006d1332 call 0x4157f0
006d1337 xor esi, esi
006d1339 mov dword ptr [ebp - 4], 0
006d1340 mov dword ptr [ebp - 0x1c], esi
006d1343 cmp dword ptr [ebp - 0x24], esi
006d1346 jbe 0x6d1446
006d134c nop dword ptr [eax]
006d1350 mov eax, dword ptr [ebp - 0x2c]
006d1353 mov esi, dword ptr [eax + esi*4]
006d1356 cmp dword ptr [esi + 0x180], 0
006d135d je 0x6d1436
006d1363 mov edi, dword ptr [esi + 0x28]
006d1366 cmp edi, 1
006d1369 je 0x6d1370
006d136b cmp edi, 3
006d136e jne 0x6d13e4
006d1370 cmp byte ptr [ebp - 0x11], 0
006d1374 je 0x6d13e4
006d1376 push 0xbc4c30
006d137b lea edx, [ebx + 0x24]
006d137e lea ecx, [ebp - 0x40]
006d1381 call 0x412050
006d1386 add esp, 4
006d1389 mov ecx, dword ptr [eax]
006d138b or ecx, dword ptr [eax + 4]
006d138e jne 0x6d1398
006d1390 mov ecx, dword ptr [eax + 8]
006d1393 or ecx, dword ptr [eax + 0xc]
006d1396 je 0x6d13ac
006d1398 cmp edi, 1
006d139b jne 0x6d13ac
006d139d mov ecx, esi
006d139f call 0x786c40
006d13a4 test al, al
006d13a6 jne 0x6d1436
006d13ac movss xmm0, dword ptr [ebp - 0x18]
006d13b1 comiss xmm0, dword ptr [ebx + 0x20]
006d13b5 jb 0x6d13c1
006d13b7 movss xmm0, dword ptr [0xb6a7b0]
006d13bf jmp 0x6d13c9
006d13c1 movss xmm0, dword ptr [0xb6a614]
006d13c9 mov eax, dword ptr [esi]
006d13cb lea ecx, [ebp - 0x68]
006d13ce push 0x1e
006d13d0 push ecx
006d13d1 push dword ptr [ebx + 0x14]
006d13d4 push dword ptr [ebx + 0x10]
006d13d7 push ecx
006d13d8 mov ecx, esi
006d13da movss dword ptr [esp], xmm0
006d13df call dword ptr [eax + 0x20]
006d13e2 jmp 0x6d1436
006d13e4 lea eax, [edi - 0xa]
006d13e7 cmp eax, 0x3dd
006d13ec ja 0x6d1436
006d13ee cmp byte ptr [ebp - 0x12], 0
006d13f2 je 0x6d1436
006d13f4 mov eax, dword ptr [esi]
006d13f6 lea ecx, [ebp - 0x68]
006d13f9 movss xmm0, dword ptr [ebp - 0x18]
006d13fe push 0x1e
006d1400 push ecx
006d1401 push dword ptr [ebx + 0x14]
006d1404 push dword ptr [ebx + 0x10]
006d1407 push ecx
006d1408 mov ecx, esi
006d140a movss dword ptr [esp], xmm0
006d140f call dword ptr [eax + 0x20]
006d1412 movups xmm0, xmmword ptr [ebx + 0x24]
006d1416 mov edx, dword ptr [ebx + 8]
006d1419 push ecx
006d141a mov dword ptr [esp], 0x40600000
006d1421 mov ecx, esi
006d1423 push dword ptr [ebx + 0xc]
006d1426 sub esp, 0x10
006d1429 mov eax, esp
006d142b movups xmmword ptr [eax], xmm0
006d142e call 0x654de0
006d1433 add esp, 0x18
006d1436 mov esi, dword ptr [ebp - 0x1c]
006d1439 inc esi
006d143a mov dword ptr [ebp - 0x1c], esi
006d143d cmp esi, dword ptr [ebp - 0x24]
006d1440 jb 0x6d1350
