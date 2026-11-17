005f0b99 mov eax, dword ptr [ebp - 0xf4]
005f0b9f lea eax, [eax + eax*4]
005f0ba2 shl eax, 2
005f0ba5 mov dword ptr [ebp - 0xf4], eax
005f0bab test edx, edx
005f0bad je 0x5f0c9e
005f0bb3 movd xmm0, edx
005f0bb7 mov eax, edx
005f0bb9 cvtdq2pd xmm0, xmm0
005f0bbd shr eax, 0x1f
005f0bc0 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
005f0bc9 cvtpd2ps xmm0, xmm0
005f0bcd movss dword ptr [ebp - 0x104], xmm0
005f0bd5 nop word ptr [eax + eax]
005f0be0 mov eax, dword ptr [ebp - 0x100]
005f0be6 push 0
005f0be8 push 0xbeab40
005f0bed push 0xbeab18
005f0bf2 push 0
005f0bf4 push dword ptr [eax + ecx*4]
005f0bf7 call 0x9ec34c
005f0bfc movd xmm0, dword ptr [ebp - 0xec]
005f0c04 add esp, 0x14
005f0c07 cvtdq2ps xmm0, xmm0
005f0c0a mov esi, eax
005f0c0c push 0
005f0c0e push 0x70
005f0c10 mulss xmm0, dword ptr [0xb6a914]
005f0c18 divss xmm0, dword ptr [ebp - 0x104]
005f0c20 movss dword ptr [esi + 0xcb0], xmm0
005f0c28 mov ecx, dword ptr [edi + 0x360]
005f0c2e call 0x73af30
005f0c33 test al, al
005f0c35 mov eax, dword ptr [ebp - 0xf4]
005f0c3b je 0x5f0c57
005f0c3d movss xmm0, dword ptr [eax + 0xbc453c]
005f0c45 mulss xmm0, dword ptr [eax + 0xbc4538]
005f0c4d mulss xmm0, dword ptr [ebp - 0xf0]
005f0c55 jmp 0x5f0c67
005f0c57 movss xmm0, dword ptr [ebp - 0xf0]
005f0c5f mulss xmm0, dword ptr [eax + 0xbc4538]
005f0c67 movss dword ptr [esi + 0xcbc], xmm0
005f0c6f cmp dword ptr [esi + 0x2c], 0x3c
005f0c73 jne 0x5f0c85
005f0c75 mulss xmm0, dword ptr [0xb6a864]
005f0c7d movss dword ptr [esi + 0xcbc], xmm0
005f0c85 mov ecx, dword ptr [ebp - 0xec]
005f0c8b inc ecx
005f0c8c mov dword ptr [ebp - 0xec], ecx
005f0c92 cmp ecx, dword ptr [ebp - 0x10c]
005f0c98 jb 0x5f0be0
005f0c9e cmp byte ptr [ebp - 0x38], 0
005f0ca2 jne 0x5f0cb2
005f0ca4 push dword ptr [ebp - 0x100]
005f0caa call 0x9eace5
005f0caf add esp, 4
005f0cb2 mov dword ptr [ebp - 4], 0xffffffff
005f0cb9 mov ecx, dword ptr [edi + 0xcc0]
005f0cbf lea eax, [ecx + ecx*4]
005f0cc2 movss xmm0, dword ptr [eax*4 + 0xbc4530]
005f0ccb movss xmm1, dword ptr [eax*4 + 0xbc4534]
005f0cd4 movss dword ptr [edi + 0xcb4], xmm0
005f0cdc movss dword ptr [edi + 0xcb8], xmm1
