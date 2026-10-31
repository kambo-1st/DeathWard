0050145c cmp dword ptr [edi + 0x70], 0
00501460 je 0x50146b
00501462 cmp byte ptr [edi + 0x80], 0
00501469 jne 0x5014d9
0050146b mov esi, dword ptr [edi + 0x70]
0050146e test esi, esi
00501470 je 0x5014b7
00501472 cmp dword ptr [esi + 0x14], 0x10
00501476 mov eax, esi
00501478 jb 0x50147c
0050147a mov eax, dword ptr [esi]
0050147c mov ecx, 0xb41e80
00501481 mov dl, byte ptr [eax]
00501483 cmp dl, byte ptr [ecx]
00501485 jne 0x5014a1
00501487 test dl, dl
00501489 je 0x50149d
0050148b mov dl, byte ptr [eax + 1]
0050148e cmp dl, byte ptr [ecx + 1]
00501491 jne 0x5014a1
00501493 add eax, 2
00501496 add ecx, 2
00501499 test dl, dl
0050149b jne 0x501481
0050149d xor eax, eax
0050149f jmp 0x5014a6
005014a1 sbb eax, eax
005014a3 or eax, 1
005014a6 test eax, eax
005014a8 jne 0x5014b7
005014aa cmp byte ptr [esi + 0x34], al
005014ad je 0x5014d9
005014af cmp byte ptr [edi + 0x80], al
005014b5 jne 0x5014d9
005014b7 push 1
005014b9 push 0xb41e80
005014be lea ecx, [edi + 0x3c]
005014c1 call 0x405740
005014c6 test al, al
005014c8 je 0x5014d9
005014ca lea ecx, [edi + 0x6c]
005014cd call 0x405330
005014d2 mov byte ptr [edi + 0x80], 1
005014d9 mov ecx, dword ptr [esp + 0x124]
005014e0 pop edi
005014e1 pop esi
005014e2 pop ebx
005014e3 xor ecx, esp
005014e5 call 0x9eacd7
005014ea mov esp, ebp
005014ec pop ebp
005014ed ret 
