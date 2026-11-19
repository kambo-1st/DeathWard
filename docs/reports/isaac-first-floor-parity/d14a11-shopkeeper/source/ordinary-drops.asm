00698988 mov eax, dword ptr [ebp - 0x40]
0069898b lea edi, [ebp - 0x24]
0069898e movups xmm0, xmmword ptr [esi + 0x334]
00698995 add esi, 0x334
0069899b cmp byte ptr [ebx + 0xc], 0
0069899f mov eax, dword ptr [eax + 0x2c]
006989a2 cmovne edi, esi
006989a5 movups xmmword ptr [ebp - 0x24], xmm0
006989a9 cmp eax, 3
006989ac je 0x698b6d
006989b2 cmp eax, 4
006989b5 je 0x698b6d
006989bb mov eax, dword ptr [edi]
006989bd test eax, eax
006989bf jne 0x6989d7
006989c1 push 0xb4d6c4
006989c6 push 3
006989c8 call 0x95e330
006989cd mov eax, dword ptr [edi]
006989cf add esp, 8
006989d2 test eax, eax
006989d4 jne 0x6989d7
006989d6 int3
006989d7 mov ecx, dword ptr [edi + 4]
006989da mov esi, eax
006989dc shr esi, cl
006989de mov ecx, dword ptr [edi + 8]
006989e1 xor esi, eax
006989e3 mov eax, esi
006989e5 shl eax, cl
006989e7 mov ecx, dword ptr [edi + 0xc]
006989ea xor esi, eax
006989ec mov eax, esi
006989ee shr eax, cl
006989f0 xor esi, eax
006989f2 mov eax, 0x51eb851f
006989f7 mul esi
006989f9 mov dword ptr [edi], esi
006989fb shr edx, 5
006989fe imul eax, edx, 0x64
00698a01 sub esi, eax
00698a03 mov al, byte ptr [ebx + 0xc]
00698a06 jne 0x698a3a
00698a08 mov ecx, dword ptr [0xbfd65c]
00698a0e xor al, 1
00698a10 push eax
00698a11 push 1
00698a13 push 0x40
00698a15 lea ecx, [ecx + 0x1a5cc]
00698a1b mov dword ptr [ebp - 0x28], eax
00698a1e call 0x701bd0
00698a23 test al, al
00698a25 je 0x698a3e
00698a27 mov ecx, edi
00698a29 call 0x7a7e20
00698a2e push 0
00698a30 push eax
00698a31 push 0x40
00698a33 push 0x64
00698a35 jmp 0x698d80
00698a3a xor al, 1
00698a3c jmp 0x698a41
00698a3e mov eax, dword ptr [ebp - 0x28]
00698a41 push 0x64
00698a43 mov ecx, edi
00698a45 mov byte ptr [ebp - 0x28], al
00698a48 call 0x7a7d50
00698a4d mov esi, dword ptr [ebp - 0x28]
00698a50 test eax, eax
00698a52 jne 0x698a87
00698a54 mov ecx, dword ptr [0xbfd65c]
00698a5a push esi
00698a5b push 1
00698a5d push 0x1ad
00698a62 lea ecx, [ecx + 0x1a5cc]
00698a68 call 0x701bd0
00698a6d test al, al
00698a6f je 0x698a87
00698a71 mov ecx, edi
00698a73 call 0x7a7e20
00698a78 push 0
00698a7a push eax
00698a7b push 0x1ad
00698a80 push 0x64
00698a82 jmp 0x698d80
00698a87 push 0x64
00698a89 mov ecx, edi
00698a8b call 0x7a7d50
00698a90 test eax, eax
00698a92 jne 0x698af1
00698a94 mov eax, dword ptr [0xbfd680]
00698a99 mov ecx, dword ptr [0xbfd65c]
00698a9f cmp byte ptr [eax + 0x1b8], 0
00698aa6 jne 0x698ac4
00698aa8 cmp dword ptr [eax + 8], 2
00698aac jne 0x698af1
00698aae test ecx, ecx
00698ab0 je 0x698af1
00698ab2 cmp dword ptr [ecx + 0x1c3204], 0
00698ab9 ja 0x698ac4
00698abb cmp byte ptr [ecx + 0x1c31a1], 0
00698ac2 je 0x698af1
00698ac4 push esi
00698ac5 push 1
00698ac7 push 0x209
00698acc add ecx, 0x1a5cc
00698ad2 call 0x701bd0
00698ad7 test al, al
00698ad9 je 0x698af1
00698adb mov ecx, edi
00698add call 0x7a7e20
00698ae2 push 0
00698ae4 push eax
00698ae5 push 0x209
00698aea push 0x64
00698aec jmp 0x698d80
00698af1 push 3
00698af3 mov ecx, edi
00698af5 call 0x7a7d50
00698afa sub eax, 1
00698afd je 0x698b31
00698aff sub eax, 1
00698b02 jne 0x698d8a
00698b08 mov ecx, edi
00698b0a call 0x7a7e20
00698b0f push 0
00698b11 push eax
00698b12 push 0
00698b14 push 0x14
00698b16 push 5
00698b18 lea ecx, [ebp - 0x3c]
00698b1b call 0x68f5d0
00698b20 mov ecx, edi
00698b22 call 0x7a7e20
00698b27 push 0
00698b29 push eax
00698b2a push 0
00698b2c jmp 0x698d7e
00698b31 mov esi, dword ptr [ebp - 0x40]
00698b34 add esi, 0x334
00698b3a push esi
00698b3b push ecx
00698b3c mov ecx, edi
00698b3e call 0x7a7e20
00698b43 add esp, 4
00698b46 lea ecx, [ebp - 0x3c]
00698b49 push eax
00698b4a push 0
00698b4c push 0
00698b4e push 0x55
00698b50 call 0x68f5d0
00698b55 push esi
00698b56 push ecx
00698b57 mov ecx, edi
00698b59 call 0x7a7e20
00698b5e add esp, 4
00698b61 push eax
00698b62 push 0
00698b64 push 0
00698b66 push 0x55
00698b68 jmp 0x698d82
