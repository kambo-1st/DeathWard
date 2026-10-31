004faccb cmp byte ptr [edi + 0x16b], 0
004facd2 je 0x4fb194
004facd8 movss xmm0, dword ptr [edi + 0x2d8]
004face0 comiss xmm0, dword ptr [0xb6aee4]
004face7 jbe 0x4fb194
004faced mov ecx, edi
004facef call 0x6ad7a0
004facf4 movss xmm0, dword ptr [0xb6a8cc]
004facfc sub esp, 8
004facff movd xmm1, eax
004fad03 cvtdq2ps xmm1, xmm1
004fad06 mulss xmm1, dword ptr [0xb6a350]
004fad0e addss xmm1, dword ptr [0xb6a614]
004fad16 divss xmm0, xmm1
004fad1a movss dword ptr [ebp - 0x64], xmm0
004fad1f fld dword ptr [ebp - 0x64]
004fad22 fstp qword ptr [esp]
004fad25 call 0x9ec3ac
004fad2a mov eax, dword ptr [edi + 0x28]
004fad2d add esp, 8
004fad30 fstp dword ptr [ebp - 0x64]
004fad33 fld dword ptr [ebp - 0x64]
004fad36 fstp dword ptr [ebp - 0x64]
004fad39 cvttss2si esi, dword ptr [ebp - 0x64]
004fad3e cmp eax, 0x16
004fad41 jne 0x4fad6a
004fad43 mov eax, dword ptr [edi + 0x2c]
004fad46 cmp eax, 1
004fad49 je 0x4fad5a
004fad4b cmp eax, 2
004fad4e je 0x4fad5a
004fad50 cmp eax, 3
004fad53 jne 0x4fad8c
004fad55 lea esi, [eax - 2]
004fad58 jmp 0x4fad8c
004fad5a call 0x6c3d90
004fad5f and eax, 1
004fad62 inc eax
004fad63 cmp eax, esi
004fad65 cmovl esi, eax
004fad68 jmp 0x4fad8c
004fad6a cmp eax, 0xcd
004fad6f jne 0x4fad78
004fad71 mov esi, 1
004fad76 jmp 0x4fad8c
004fad78 cmp eax, 0x331
004fad7d jne 0x4fad8c
004fad7f lea eax, [esi - 1]
004fad82 mov esi, 1
004fad87 cmp eax, esi
004fad89 cmovg esi, eax
004fad8c movsx eax, word ptr [edi + 0xbc6]
004fad93 xor ecx, ecx
004fad95 sub esi, eax
004fad97 test esi, esi
004fad99 cmovg ecx, esi
004fad9c mov dword ptr [ebp - 0x74], ecx
004fad9f test ecx, ecx
004fada1 jle 0x4fb194
