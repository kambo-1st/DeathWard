006a3059 cmp byte ptr [edi + 0x98], 0
006a3060 jne 0x6a3159
006a3066 mov eax, dword ptr [ebx + 0x10]
006a3069 cmp eax, 6
006a306c je 0x6a30c2
006a306e cmp eax, 7
006a3071 je 0x6a30c2
006a3073 cmp eax, 8
006a3076 je 0x6a30c2
006a3078 cmp eax, 9
006a307b je 0x6a30c2
006a307d test edx, edx
006a307f je 0x6a30b8
006a3081 xor esi, esi
006a3083 nop dword ptr [eax]
006a3087 nop word ptr [eax + eax]
006a3090 mov ecx, dword ptr [ebp - 0x4c]
006a3093 mov eax, dword ptr [ecx + esi*4]
006a3096 mov dword ptr [eax + 0x364], 0xc0400000
006a30a0 mov eax, dword ptr [ecx + esi*4]
006a30a3 inc esi
006a30a4 mov dword ptr [eax + 0x368], 0x3dcccccd
006a30ae cmp esi, edx
006a30b0 jb 0x6a3090
006a30b2 mov esi, dword ptr [ebp - 0x48]
006a30b5 mov eax, dword ptr [ebx + 0x10]
006a30b8 cmp eax, 2
006a30bb je 0x6a30cb
006a30bd cmp eax, 4
006a30c0 je 0x6a30cb
006a30c2 cmp eax, 5
006a30c5 jne 0x6a3159
006a30cb test edx, edx
006a30cd je 0x6a338d
006a30d3 movss xmm3, dword ptr [0xb6a434]
006a30db xor esi, esi
006a30dd movss xmm4, dword ptr [0xb6a670]
006a30e5 movss xmm5, dword ptr [0xb6a614]
006a30ed mov ecx, dword ptr [ebp - 0x14]
006a30f0 mov eax, dword ptr [ebp - 0x4c]
006a30f3 mov eax, dword ptr [eax + esi*4]
006a30f6 inc esi
006a30f7 movss xmm0, dword ptr [eax + 0x364]
006a30ff subss xmm0, xmm5
006a3103 movss dword ptr [eax + 0x364], xmm0
006a310b movss xmm0, dword ptr [eax + 0x2b8]
006a3113 movss xmm1, dword ptr [ecx + 0x2b8]
006a311b movss xmm2, dword ptr [eax + 0x2bc]
006a3123 mulss xmm0, xmm4
006a3127 mulss xmm1, xmm3
006a312b mulss xmm2, xmm4
006a312f addss xmm1, xmm0
006a3133 movss xmm0, dword ptr [ecx + 0x2bc]
006a313b mulss xmm0, xmm3
006a313f movss dword ptr [eax + 0x2b8], xmm1
006a3147 addss xmm2, xmm0
006a314b movss dword ptr [eax + 0x2bc], xmm2
006a3153 cmp esi, edx
006a3155 jb 0x6a30f0
006a3157 jmp 0x6a3169
006a3159 test edx, edx
006a315b je 0x6a338d
006a3161 movss xmm5, dword ptr [0xb6a614]
006a3169 xor edx, edx
006a316b mov dword ptr [ebp - 0x18], edx
006a316e nop 
006a3170 mov ecx, dword ptr [ebp - 0x4c]
006a3173 xorps xmm1, xmm1
006a3176 movss xmm0, dword ptr [edi + 4]
006a317b mov ecx, dword ptr [ecx + edx*4]
006a317e addss xmm0, dword ptr [ecx + 0x360]
006a3186 movss dword ptr [ecx + 0x360], xmm0
006a318e movss xmm0, dword ptr [edi + 8]
006a3193 addss xmm0, dword ptr [ecx + 0x364]
006a319b movss dword ptr [ecx + 0x364], xmm0
006a31a3 movss xmm0, dword ptr [ecx + 0x368]
006a31ab addss xmm0, dword ptr [edi + 0xc]
006a31b0 movss dword ptr [ecx + 0x368], xmm0
006a31b8 mov eax, dword ptr [edi + 0x14]
006a31bb mov dword ptr [ecx + 0x370], eax
006a31c1 movss xmm0, dword ptr [edi + 0x9c]
006a31c9 comiss xmm1, xmm0
006a31cc jbe 0x6a31ed
006a31ce movss xmm0, dword ptr [edi + 0x14]
006a31d3 cvtps2pd xmm0, xmm0
006a31d6 comisd xmm0, xmmword ptr [0xb6a788]
006a31de jbe 0x6a31ea
006a31e0 movss xmm0, dword ptr [0xb6a7b0]
006a31e8 jmp 0x6a31ed
006a31ea movaps xmm0, xmm5
006a31ed mov eax, dword ptr [ebp - 0x4c]
