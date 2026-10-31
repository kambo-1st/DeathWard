00500fbf movss xmm0, dword ptr [edi + 0x2c4]
00500fc7 mulss xmm0, dword ptr [0xb6a50c]
00500fcf mov edx, dword ptr [edi + 0xaf0]
00500fd5 movss dword ptr [edi + 0x2c4], xmm0
00500fdd test edx, edx
00500fdf jle 0x50106c
00500fe5 cvttss2si eax, dword ptr [edi + 0x2fc]
00500fed cvttss2si ecx, dword ptr [edi + 0x2f8]
00500ff5 sub ecx, eax
00500ff7 add ecx, edx
00500ff9 cmp dword ptr [edi + 0xe6c], -1
00501000 mov dword ptr [edi + 0xaf0], ecx
00501006 jne 0x501022
00501008 movss xmm0, dword ptr [0xc02fec]
00501010 movss dword ptr [edi + 0xe70], xmm0
00501018 movss xmm0, dword ptr [0xc02ff0]
00501020 jmp 0x501064
00501022 movss xmm2, dword ptr [0xb6a2cc]
0050102a lea eax, [esp + 0x18]
0050102e push eax
0050102f mov ecx, edi
00501031 call 0x6af380
00501036 movss xmm1, dword ptr [esp + 0x18]
0050103c ucomiss xmm1, dword ptr [0xc02fec]
00501043 movss xmm0, dword ptr [esp + 0x1c]
00501049 lahf 
0050104a test ah, 0x44
0050104d jp 0x50105c
0050104f ucomiss xmm0, dword ptr [0xc02ff0]
00501056 lahf 
00501057 test ah, 0x44
0050105a jnp 0x50106c
0050105c movss dword ptr [edi + 0xe70], xmm1
00501064 movss dword ptr [edi + 0xe74], xmm0
0050106c cmp dword ptr [edi + 0xaf0], 0
00501073 jg 0x501125
00501079 movss xmm1, dword ptr [0xb6aba8]
00501081 mov ecx, edi
00501083 push 7
00501085 push 0
00501087 call 0x6a15a0
0050108c test al, al
0050108e je 0x501125
00501094 mov eax, dword ptr [0xbfd65c]
00501099 mov eax, dword ptr [eax + 0x243624]
0050109f cmp eax, 1
005010a2 je 0x5010ad
005010a4 cmp eax, 3
005010a7 je 0x5010ad
005010a9 xor eax, eax
005010ab jmp 0x5010b2
005010ad mov eax, 1
005010b2 xor ecx, ecx
005010b4 cmp ecx, eax
005010b6 push ecx
005010b7 sbb eax, eax
005010b9 lea ecx, [edi + 0x3c]
005010bc and eax, 0xfffffff2
005010bf add eax, 0x1c
005010c2 push 0xb40510
005010c7 mov dword ptr [edi + 0xaf0], eax
005010cd call 0x4054f0
005010d2 cmp dword ptr [edi + 0xe6c], -1
005010d9 jne 0x5010f5
005010db movss xmm0, dword ptr [0xc02fec]
005010e3 movss dword ptr [edi + 0xe70], xmm0
005010eb movss xmm0, dword ptr [0xc02ff0]
005010f3 jmp 0x50111d
005010f5 movss xmm2, dword ptr [0xb6a2cc]
005010fd lea eax, [esp + 0x18]
00501101 push eax
00501102 mov ecx, edi
00501104 call 0x6af380
00501109 movss xmm0, dword ptr [esp + 0x18]
0050110f movss dword ptr [edi + 0xe70], xmm0
00501117 movss xmm0, dword ptr [esp + 0x1c]
0050111d movss dword ptr [edi + 0xe74], xmm0
