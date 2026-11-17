006a8134 mov esi, dword ptr [edi + 8]
006a8137 xor ecx, ecx
006a8139 movss xmm5, dword ptr [0xb6a614]
006a8141 mov eax, 0x92492493
006a8146 mov dword ptr [ebp - 0x70], ecx
006a8149 mov ecx, dword ptr [edi + 0xc]
006a814c sub ecx, esi
006a814e imul ecx
006a8150 add edx, ecx
006a8152 sar edx, 5
006a8155 mov eax, edx
006a8157 shr eax, 0x1f
006a815a add eax, edx
006a815c je 0x6a8203
006a8162 movss xmm4, dword ptr [0xb6a974]
006a816a xor ebx, ebx
006a816c movss xmm3, dword ptr [0xb6a864]
006a8174 movss xmm2, dword ptr [0xb6a7b0]
006a817c nop dword ptr [eax]
006a8180 movss xmm0, dword ptr [esi + ebx]
006a8185 comiss xmm0, xmm4
006a8188 jbe 0x6a81a1
006a818a call 0x6c3d90
006a818f xor edx, edx
006a8191 mov ecx, 3
006a8196 div ecx
006a8198 test edx, edx
006a819a jne 0x6a81b8
006a819c movaps xmm1, xmm3
006a819f jmp 0x6a81c0
006a81a1 comiss xmm0, xmm1
006a81a4 jbe 0x6a81d7
006a81a6 call 0x6c3d90
006a81ab xor edx, edx
006a81ad mov ecx, 3
006a81b2 div ecx
006a81b4 test edx, edx
006a81b6 jne 0x6a81bd
006a81b8 movaps xmm1, xmm2
006a81bb jmp 0x6a81c0
006a81bd movaps xmm1, xmm5
006a81c0 movss xmm0, dword ptr [edi + 0x2d8]
006a81c8 subss xmm0, xmm1
006a81cc xorps xmm1, xmm1
006a81cf movss dword ptr [edi + 0x2d8], xmm0
006a81d7 mov ecx, dword ptr [edi + 0xc]
006a81da mov eax, 0x92492493
006a81df mov esi, dword ptr [edi + 8]
006a81e2 add ebx, 0x38
006a81e5 inc dword ptr [ebp - 0x70]
006a81e8 sub ecx, esi
006a81ea imul ecx
006a81ec add edx, ecx
006a81ee sar edx, 5
006a81f1 mov eax, edx
006a81f3 shr eax, 0x1f
006a81f6 add eax, edx
006a81f8 cmp dword ptr [ebp - 0x70], eax
006a81fb jb 0x6a8180
006a81fd lea ebx, [edi + 0x294]
006a8203 movss xmm0, dword ptr [edi + 0x2d8]
006a820b lea esi, [edi + 0x2d8]
006a8211 comiss xmm0, xmm5
006a8214 lea eax, [ebp - 0x7c]
006a8217 mov dword ptr [ebp - 0x7c], 0x3f800000
006a821e lea ecx, [edi + 0x3c]
006a8221 push 1
006a8223 cmova eax, esi
006a8226 movss xmm1, dword ptr [eax]
006a822a movss dword ptr [esi], xmm1
