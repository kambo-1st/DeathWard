0074d378 push 0
0074d37a push 0x8000000
0074d37f mov ecx, edi
0074d381 call 0x4122f0
0074d386 test al, al
0074d388 je 0x74d396
0074d38a mov dword ptr [edi + 0x1590], 0x3c
0074d394 jmp 0x74d3aa
0074d396 mov eax, dword ptr [edi + 0x1590]
0074d39c xor ecx, ecx
0074d39e add eax, -1
0074d3a1 cmovs eax, ecx
0074d3a4 mov dword ptr [edi + 0x1590], eax
