005a1360 push ebp
005a1361 mov ebp, esp
005a1363 push -1
005a1365 push 0x9f0b7d
005a136a mov eax, dword ptr fs:[0]
005a1370 push eax
005a1371 mov eax, 0x1664
005a1376 call 0x9ebab0
005a137b mov eax, dword ptr [0xbaa3b4]
005a1380 xor eax, ebp
005a1382 mov dword ptr [ebp - 0x10], eax
005a1385 push esi
005a1386 push edi
005a1387 push eax
005a1388 lea eax, [ebp - 0xc]
005a138b mov dword ptr fs:[0], eax
005a1391 mov eax, ecx
005a1393 mov dword ptr [ebp - 0x588], eax
005a1399 mov ecx, dword ptr [ebp + 0x10]
005a139c mov edi, dword ptr [ebp + 0xc]
005a139f mov esi, dword ptr [ebp + 8]
005a13a2 mov edx, dword ptr [ebp + 0x14]
005a13a5 mov dword ptr [ebp - 0x5bc], ecx
005a13ab xor ecx, ecx
005a13ad mov dword ptr [ebp - 0x5c4], ecx
005a13b3 mov dword ptr [ebp - 0x5e0], edi
005a13b9 mov dword ptr [ebp - 0x894], esi
005a13bf mov dword ptr [ebp - 0x5c0], edx
005a13c5 mov dword ptr [ebp - 0x5a0], ecx
005a13cb mov byte ptr [ebp - 0x5ac], 1
005a13d2 mov byte ptr [ebp - 0x5ab], cl
005a13d8 test edi, edi
005a13da je 0x5b2346
005a13e0 push dword ptr [ebp + 0x18]
005a13e3 mov ecx, eax
005a13e5 push edx
005a13e6 push dword ptr [ebp - 0x5bc]
005a13ec push eax
005a13ed push edi
005a13ee call 0x59ffc0
005a13f3 mov ecx, dword ptr [0xbfd674]
005a13f9 push eax
005a13fa push edi
005a13fb call 0x7ffef0
005a1400 test al, al
005a1402 jne 0x5b2346
005a1408 mov ecx, dword ptr [ebp - 0x5bc]
005a140e mov al, cl
005a1410 not al
005a1412 and al, 1
005a1414 mov byte ptr [ebp - 0x5ad], al
005a141a mov eax, ecx
005a141c shr eax, 3
005a141f and eax, 0xffffff01
005a1424 mov dword ptr [ebp - 0x590], eax
005a142a mov eax, ecx
005a142c shr eax, 1
005a142e not al
