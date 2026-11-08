004054f0 push ebp
004054f1 mov ebp, esp
004054f3 cmp byte ptr [ebp + 0xc], 0
004054f7 push esi
004054f8 push edi
004054f9 mov edi, ecx
004054fb jne 0x405544
004054fd mov esi, dword ptr [edi + 0x34]
00405500 test esi, esi
00405502 je 0x405544
00405504 cmp dword ptr [esi + 0x14], 0x10
00405508 mov eax, esi
0040550a jb 0x40550e
0040550c mov eax, dword ptr [esi]
0040550e mov ecx, dword ptr [ebp + 8]
00405511 mov dl, byte ptr [eax]
00405513 cmp dl, byte ptr [ecx]
00405515 jne 0x405531
00405517 test dl, dl
00405519 je 0x40552d
0040551b mov dl, byte ptr [eax + 1]
0040551e cmp dl, byte ptr [ecx + 1]
00405521 jne 0x405531
00405523 add eax, 2
00405526 add ecx, 2
00405529 test dl, dl
0040552b jne 0x405511
0040552d xor eax, eax
0040552f jmp 0x405536
00405531 sbb eax, eax
00405533 or eax, 1
00405536 test eax, eax
00405538 jne 0x405544
0040553a cmp byte ptr [esi + 0x34], al
0040553d je 0x405560
0040553f cmp byte ptr [edi + 0x44], al
00405542 jne 0x405560
00405544 push 1
00405546 push dword ptr [ebp + 8]
00405549 mov ecx, edi
0040554b call 0x405740
00405550 test al, al
00405552 je 0x405560
00405554 lea ecx, [edi + 0x30]
00405557 call 0x405330
0040555c mov byte ptr [edi + 0x44], 1
00405560 pop edi
00405561 pop esi
00405562 pop ebp
00405563 ret 8
