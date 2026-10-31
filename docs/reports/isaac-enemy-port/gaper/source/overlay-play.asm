00405a00 push ebp
00405a01 mov ebp, esp
00405a03 cmp byte ptr [ebp + 0xc], 0
00405a07 push esi
00405a08 push edi
00405a09 mov edi, ecx
00405a0b jne 0x405a54
00405a0d mov esi, dword ptr [edi + 0x54]
00405a10 test esi, esi
00405a12 je 0x405a54
00405a14 cmp dword ptr [esi + 0x14], 0x10
00405a18 mov eax, esi
00405a1a jb 0x405a1e
00405a1c mov eax, dword ptr [esi]
00405a1e mov ecx, dword ptr [ebp + 8]
00405a21 mov dl, byte ptr [eax]
00405a23 cmp dl, byte ptr [ecx]
00405a25 jne 0x405a41
00405a27 test dl, dl
00405a29 je 0x405a3d
00405a2b mov dl, byte ptr [eax + 1]
00405a2e cmp dl, byte ptr [ecx + 1]
00405a31 jne 0x405a41
00405a33 add eax, 2
00405a36 add ecx, 2
00405a39 test dl, dl
00405a3b jne 0x405a21
00405a3d xor eax, eax
00405a3f jmp 0x405a46
00405a41 sbb eax, eax
00405a43 or eax, 1
00405a46 test eax, eax
00405a48 jne 0x405a54
00405a4a cmp byte ptr [esi + 0x34], al
00405a4d je 0x405a70
00405a4f cmp byte ptr [edi + 0x64], al
00405a52 jne 0x405a70
00405a54 push 1
00405a56 push dword ptr [ebp + 8]
00405a59 mov ecx, edi
00405a5b call 0x405bb0
00405a60 test al, al
00405a62 je 0x405a70
00405a64 lea ecx, [edi + 0x50]
00405a67 call 0x405330
00405a6c mov byte ptr [edi + 0x64], 1
00405a70 pop edi
00405a71 pop esi
00405a72 pop ebp
00405a73 ret 8
