00405bb0 push ebp
00405bb1 mov ebp, esp
00405bb3 sub esp, 8
00405bb6 push ebx
00405bb7 mov eax, ecx
00405bb9 mov ecx, dword ptr [ebp + 8]
00405bbc push esi
00405bbd push edi
00405bbe xor edi, edi
00405bc0 mov dword ptr [ebp - 4], eax
00405bc3 mov ebx, dword ptr [eax + 0x78]
00405bc6 test ebx, ebx
00405bc8 je 0x405c17
00405bca mov eax, dword ptr [eax + 0x74]
00405bcd mov esi, eax
00405bcf mov dword ptr [ebp - 8], eax
00405bd2 cmp dword ptr [esi + 0x14], 0x10
00405bd6 mov eax, esi
00405bd8 jb 0x405be0
00405bda mov eax, dword ptr [esi]
00405bdc nop dword ptr [eax]
00405be0 mov dl, byte ptr [eax]
00405be2 cmp dl, byte ptr [ecx]
00405be4 jne 0x405c00
00405be6 test dl, dl
00405be8 je 0x405bfc
00405bea mov dl, byte ptr [eax + 1]
00405bed cmp dl, byte ptr [ecx + 1]
00405bf0 jne 0x405c00
00405bf2 add eax, 2
00405bf5 add ecx, 2
00405bf8 test dl, dl
00405bfa jne 0x405be0
00405bfc xor eax, eax
00405bfe jmp 0x405c05
00405c00 sbb eax, eax
00405c02 or eax, 1
00405c05 test eax, eax
00405c07 je 0x405c32
00405c09 mov ecx, dword ptr [ebp + 8]
00405c0c inc edi
00405c0d add esi, 0x13c
00405c13 cmp edi, ebx
00405c15 jb 0x405bd2
00405c17 push ecx
00405c18 push 0xa082b0
00405c1d push 0
00405c1f call 0x95e330
00405c24 add esp, 0xc
00405c27 xor al, al
00405c29 pop edi
00405c2a pop esi
00405c2b pop ebx
00405c2c mov esp, ebp
00405c2e pop ebp
00405c2f ret 8
00405c32 mov ecx, dword ptr [ebp - 4]
00405c35 imul eax, edi, 0x13c
00405c3b add ecx, 0x50
00405c3e add eax, dword ptr [ebp - 8]
00405c41 cmp byte ptr [ebp + 0xc], 0
00405c45 push eax
00405c46 je 0x405c58
00405c48 call 0x403740
00405c4d mov al, 1
00405c4f pop edi
00405c50 pop esi
00405c51 pop ebx
00405c52 mov esp, ebp
00405c54 pop ebp
00405c55 ret 8
00405c58 call 0x403820
00405c5d pop edi
00405c5e pop esi
00405c5f mov al, 1
00405c61 pop ebx
00405c62 mov esp, ebp
00405c64 pop ebp
00405c65 ret 8
00405c68 int3
