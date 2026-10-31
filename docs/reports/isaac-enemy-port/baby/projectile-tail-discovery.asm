006a301f mov edx, esi
006a3021 xor ecx, ecx
006a3023 sub edx, dword ptr [ebp - 0x4c]
006a3026 sar edx, 2
006a3029 mov dword ptr [ebp - 0x24], ecx
006a302c mov dword ptr [ebp - 0x1c], edx
006a302f test edx, edx
006a3031 je 0x6a3059
006a3033 mov eax, dword ptr [ebp - 0x4c]
006a3036 cmp dword ptr [eax + ecx*4], 0
006a303a jne 0x6a3051
006a303c push 0xb49240
006a3041 push 3
006a3043 call 0x95e330
006a3048 mov edx, dword ptr [ebp - 0x1c]
006a304b add esp, 8
006a304e mov ecx, dword ptr [ebp - 0x24]
006a3051 inc ecx
006a3052 mov dword ptr [ebp - 0x24], ecx
006a3055 cmp ecx, edx
006a3057 jb 0x6a3033
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
006a31f0 mov ecx, dword ptr [eax + edx*4]
006a31f3 push ecx
006a31f4 movss dword ptr [esp], xmm0
006a31f9 mov eax, dword ptr [ecx]
006a31fb call dword ptr [eax + 0x3c]
006a31fe mov edx, dword ptr [ebp - 0x18]
006a3201 mov eax, dword ptr [ebp - 0x4c]
006a3204 movss xmm1, dword ptr [edi + 0x10]
006a3209 movaps xmm0, xmm1
006a320c push 1
006a320e mov ecx, dword ptr [eax + edx*4]
006a3211 push 0
006a3213 push 0xff
006a3218 push -1
006a321a mulss xmm0, dword ptr [ecx + 0x2b8]
006a3222 mulss xmm1, dword ptr [ecx + 0x2bc]
006a322a movss dword ptr [ecx + 0x2b8], xmm0
006a3232 movss dword ptr [ecx + 0x2bc], xmm1
006a323a mov eax, dword ptr [edi + 0x58]
006a323d or dword ptr [ecx + 0x388], eax
006a3243 mov eax, dword ptr [edi + 0x5c]
006a3246 or dword ptr [ecx + 0x38c], eax
006a324c mov eax, dword ptr [ebp - 0x4c]
006a324f mov ecx, dword ptr [eax + edx*4]
006a3252 lea edx, [edi + 0x2c]
006a3255 push edx
006a3256 mov eax, dword ptr [ecx]
006a3258 call dword ptr [eax + 0x38]
006a325b mov edx, dword ptr [ebp - 0x18]
006a325e movss xmm0, dword ptr [edi + 0x68]
006a3263 movss xmm1, dword ptr [edi + 0x6c]
006a3268 mov eax, dword ptr [ebp - 0x4c]
006a326b mov ecx, dword ptr [eax + edx*4]
006a326e movss dword ptr [ecx + 0x28c], xmm0
006a3276 movss dword ptr [ecx + 0x290], xmm1
006a327e mov eax, dword ptr [edi + 0x1c]
006a3281 mov dword ptr [ecx + 0x374], eax
006a3287 mov eax, dword ptr [ebp - 0x4c]
006a328a mov ecx, dword ptr [eax + edx*4]
006a328d mov eax, dword ptr [edi + 0x20]
006a3290 mov dword ptr [ecx + 0x378], eax
006a3296 mov eax, dword ptr [ebp - 0x4c]
006a3299 mov ecx, dword ptr [eax + edx*4]
006a329c mov eax, dword ptr [edi + 0x24]
006a329f mov dword ptr [ecx + 0x37c], eax
006a32a5 mov eax, dword ptr [ebp - 0x4c]
006a32a8 mov ecx, dword ptr [eax + edx*4]
006a32ab mov eax, dword ptr [edi + 0x7c]
006a32ae mov dword ptr [ecx + 0x394], eax
006a32b4 mov eax, dword ptr [ebp - 0x4c]
006a32b7 mov ecx, dword ptr [eax + edx*4]
006a32ba mov eax, dword ptr [edi + 0x80]
006a32c0 or dword ptr [ecx + 0x398], eax
006a32c6 mov eax, dword ptr [edi + 0x84]
006a32cc or dword ptr [ecx + 0x39c], eax
006a32d2 mov eax, dword ptr [ebp - 0x4c]
006a32d5 mov ecx, dword ptr [eax + edx*4]
006a32d8 mov eax, dword ptr [edi + 0x88]
006a32de mov dword ptr [ecx + 0x3a0], eax
006a32e4 mov eax, dword ptr [ebp - 0x4c]
006a32e7 mov ecx, dword ptr [eax + edx*4]
006a32ea mov eax, dword ptr [edi + 0x8c]
006a32f0 mov dword ptr [ecx + 0x3a4], eax
006a32f6 mov ecx, dword ptr [ebp - 0x4c]
006a32f9 movss xmm0, dword ptr [edi + 0x90]
006a3301 subss xmm0, dword ptr [edi + 0x64]
006a3306 mov eax, dword ptr [ecx + edx*4]
006a3309 movss dword ptr [eax + 0x2b0], xmm0
006a3311 mov eax, dword ptr [ecx + edx*4]
006a3314 movss xmm0, dword ptr [0xb6af28]
006a331c mov dword ptr [ebp - 0x18], eax
006a331f comiss xmm0, dword ptr [eax + 0x360]
006a3326 jbe 0x6a334e
006a3328 mov dword ptr [ebp - 0x18], eax
006a332b mov eax, dword ptr [eax + 0x388]
006a3331 and eax, 0x20000
006a3336 or eax, 0
006a3339 jne 0x6a334e
006a333b mov eax, dword ptr [ecx + edx*4]
006a333e mov dword ptr [eax + 0x180], 0
006a3348 mov eax, dword ptr [ecx + edx*4]
006a334b mov dword ptr [ebp - 0x18], eax
006a334e mov ecx, dword ptr [ebp - 0x18]
006a3351 inc edx
006a3352 mov eax, dword ptr [edi + 0xa0]
006a3358 movss xmm5, dword ptr [0xb6a614]
006a3360 mov dword ptr [ebp - 0x18], edx
006a3363 mov dword ptr [ecx + 0x3b8], eax
006a3369 cmp edx, dword ptr [ebp - 0x1c]
006a336c jb 0x6a3170
006a3372 mov esi, dword ptr [ebp - 0x14]
006a3375 xor edi, edi
006a3377 mov eax, dword ptr [ebp - 0x4c]
006a337a mov ecx, esi
006a337c push dword ptr [eax + edi*4]
006a337f call 0x6a19c0
006a3384 inc edi
006a3385 cmp edi, dword ptr [ebp - 0x1c]
006a3388 jb 0x6a3377
006a338a mov esi, dword ptr [ebp - 0x48]
006a338d cmp dword ptr [ebp - 0x4c], esi
006a3390 jne 0x6a3396
006a3392 xor esi, esi
006a3394 jmp 0x6a339b
006a3396 mov eax, dword ptr [ebp - 0x4c]
006a3399 mov esi, dword ptr [eax]
006a339b mov edx, dword ptr [ebp - 0x4c]
006a339e test edx, edx
006a33a0 je 0x6a33d4
006a33a2 mov ecx, dword ptr [ebp - 0x44]
006a33a5 mov eax, edx
006a33a7 sub ecx, edx
006a33a9 and ecx, 0xfffffffc
006a33ac cmp ecx, 0x1000
006a33b2 jb 0x6a33ca
006a33b4 mov edx, dword ptr [edx - 4]
006a33b7 add ecx, 0x23
006a33ba sub eax, edx
006a33bc add eax, -4
006a33bf cmp eax, 0x1f
006a33c2 jbe 0x6a33ca
006a33c4 call dword ptr [0xa065ac]
006a33ca push ecx
006a33cb push edx
006a33cc call 0x9eb08e
006a33d1 add esp, 8
006a33d4 mov eax, esi
006a33d6 mov ecx, dword ptr [ebp - 0xc]
006a33d9 mov dword ptr fs:[0], ecx
006a33e0 pop ecx
006a33e1 pop edi
006a33e2 pop esi
006a33e3 mov esp, ebp
006a33e5 pop ebp
006a33e6 mov esp, ebx
006a33e8 pop ebx
006a33e9 ret 0x10
