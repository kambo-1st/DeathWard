006ac3e0 cmp dword ptr [ebx + 0x24], 0
006ac3e4 je 0x6ac772
006ac3ea push 1
006ac3ec lea ecx, [esi + 0x1ba40]
006ac3f2 push ecx
006ac3f3 push 0x187
006ac3f8 call 0x91d340
006ac3fd test eax, eax
006ac3ff je 0x6ac76c
006ac405 mov ebx, dword ptr [ebx + 0x24]
006ac408 test ebx, ebx
006ac40a je 0x6ac76c
006ac410 mov eax, dword ptr [ebx + 0x28]
006ac413 sub eax, 0xa
006ac416 cmp eax, 0x3dd
006ac41b jbe 0x6ac42c
006ac41d mov ebx, dword ptr [ebx + 0x314]
006ac423 test ebx, ebx
006ac425 jne 0x6ac410
006ac427 jmp 0x6ac76c
006ac42c cmp ebx, edi
006ac42e je 0x6ac76c
006ac434 mov ecx, ebx
006ac436 call 0x681360
006ac43b mov ecx, edi
006ac43d mov esi, eax
006ac43f call 0x681360
006ac444 cmp esi, eax
006ac446 je 0x6ac76c
006ac44c mov esi, dword ptr [0xbfd65c]
006ac452 mov eax, dword ptr [esi + 0x1a30dc]
006ac458 sub eax, dword ptr [ebx + 0x280]
006ac45e test eax, eax
006ac460 jle 0x6ac772
006ac466 push 0
006ac468 mov ecx, ebx
006ac46a call 0x684630
006ac46f test al, al
006ac471 je 0x6ac772
006ac477 mov eax, dword ptr [edi + 0xe88]
006ac47d test eax, eax
006ac47f je 0x6ac492
006ac481 cmp eax, ebx
006ac483 je 0x6ac492
006ac485 call 0x6c3d90
006ac48a test al, 3
006ac48c jne 0x6ac772
006ac492 mov esi, dword ptr [edi + 0xe88]
006ac498 mov ecx, edi
006ac49a push 0x96
006ac49f push ebx
006ac4a0 call 0x6909f0
006ac4a5 test al, al
006ac4a7 je 0x6ac76c
006ac4ad cmp esi, ebx
006ac4af je 0x6ac76c
