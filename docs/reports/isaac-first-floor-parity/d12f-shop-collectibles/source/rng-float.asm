007a7db0 push ebp
007a7db1 mov ebp, esp
007a7db3 push ecx
007a7db4 push esi
007a7db5 mov esi, ecx
007a7db7 mov edx, dword ptr [esi]
007a7db9 test edx, edx
007a7dbb jne 0x7a7dd3
007a7dbd push 0xb4d6c4
007a7dc2 push 3
007a7dc4 call 0x95e330
007a7dc9 mov edx, dword ptr [esi]
007a7dcb add esp, 8
007a7dce test edx, edx
007a7dd0 jne 0x7a7dd3
007a7dd2 int3
007a7dd3 mov ecx, dword ptr [esi + 4]
007a7dd6 mov eax, edx
007a7dd8 shr eax, cl
007a7dda mov ecx, dword ptr [esi + 8]
007a7ddd xor eax, edx
007a7ddf mov edx, eax
007a7de1 shl edx, cl
007a7de3 mov ecx, dword ptr [esi + 0xc]
007a7de6 xor edx, eax
007a7de8 mov eax, edx
007a7dea shr eax, cl
007a7dec xor eax, edx
007a7dee mov dword ptr [esi], eax
007a7df0 pop esi
007a7df1 movd xmm0, eax
007a7df5 cvtdq2pd xmm0, xmm0
007a7df9 shr eax, 0x1f
007a7dfc addsd xmm0, qword ptr [eax*8 + 0xb6c940]
007a7e05 cvtpd2ps xmm0, xmm0
007a7e09 mulss xmm0, dword ptr [0xb6a198]
007a7e11 movss dword ptr [ebp - 4], xmm0
007a7e16 fld dword ptr [ebp - 4]
007a7e19 mov esp, ebp
007a7e1b pop ebp
007a7e1c ret
