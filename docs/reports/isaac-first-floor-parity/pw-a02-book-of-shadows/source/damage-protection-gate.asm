00786a60 push ebp
00786a61 mov ebp, esp
00786a63 push ebx
00786a64 push esi
00786a65 push edi
00786a66 mov edi, ecx
00786a68 mov ecx, dword ptr [ebp + 8]
00786a6b mov eax, ecx
00786a6d and eax, 0x2000
00786a72 or eax, 0
00786a75 je 0x786a80
00786a77 xor al, al
00786a79 pop edi
00786a7a pop esi
00786a7b pop ebx
00786a7c pop ebp
00786a7d ret 8
00786a80 and ecx, 0x20
00786a83 or ecx, 0
00786a86 je 0x786a8c
00786a88 mov bl, 1
00786a8a jmp 0x786a8e
00786a8c xor bl, bl
00786a8e lea esi, [edi + 0x1450]
00786a94 push 0x3a
00786a96 mov ecx, esi
00786a98 call 0x88b570
00786a9d test al, al
00786a9f jne 0x786ba8
00786aa5 push 0x5d
00786aa7 mov ecx, esi
00786aa9 call 0x88b570
00786aae test al, al
00786ab0 jne 0x786ba8
