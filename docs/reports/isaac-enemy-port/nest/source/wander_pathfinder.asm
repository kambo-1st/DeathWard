007a6180 push ebp
007a6181 mov ebp, esp
007a6183 and esp, 0xfffffff8
007a6186 sub esp, 0x10
007a6189 push esi
007a618a push edi
007a618b mov edi, ecx
007a618d mov esi, dword ptr [edi]
007a618f cmp dword ptr [esi + 0x32c], 0
007a6196 jne 0x7a649f
007a619c cmp byte ptr [ebp + 8], 0
007a61a0 jne 0x7a6254
007a61a6 call 0x7a35d0
007a61ab test al, al
007a61ad je 0x7a61fa
007a61af push 0
007a61b1 push 0xbeab70
007a61b6 push 0xbeab18
007a61bb push 0
007a61bd push esi
007a61be call 0x9ec34c
007a61c3 add esp, 0x14
007a61c6 lea ecx, [esp + 0x10]
007a61ca push 1
007a61cc push 0
007a61ce sub esp, 8
007a61d1 mov dword ptr [esp + 4], 0x3f000000
007a61d9 mov dword ptr [esp], 0
007a61e0 push ecx
007a61e1 mov ecx, eax
007a61e3 call 0x695a30
007a61e8 push eax
007a61e9 mov ecx, edi
007a61eb call 0x7a3650
007a61f0 mov al, 1
007a61f2 pop edi
007a61f3 pop esi
007a61f4 mov esp, ebp
007a61f6 pop ebp
007a61f7 ret 4
007a61fa mov eax, dword ptr [esi + 0x160]
007a6200 and eax, 0x1000800
007a6205 or eax, 0
007a6208 je 0x7a6254
007a620a push 0
007a620c push 0xbeab70
007a6211 push 0xbeab18
007a6216 push 0
007a6218 push esi
007a6219 call 0x9ec34c
007a621e add esp, 0x14
007a6221 mov ecx, eax
007a6223 call 0x695680
007a6228 push 0
007a622a mov ecx, dword ptr [eax + 0x294]
007a6230 mov eax, dword ptr [eax + 0x298]
007a6236 mov dword ptr [esp + 0x18], eax
007a623a lea eax, [esp + 0x14]
007a623e mov dword ptr [esp + 0x14], ecx
007a6242 mov ecx, edi
007a6244 push eax
007a6245 call 0x7a4830
007a624a mov al, 1
007a624c pop edi
007a624d pop esi
007a624e mov esp, ebp
007a6250 pop ebp
007a6251 ret 4
007a6254 movss xmm1, dword ptr [0xc02fec]
007a625c movss xmm0, dword ptr [edi + 4]
007a6261 ucomiss xmm0, xmm1
007a6264 movss dword ptr [esp + 8], xmm1
007a626a lahf 
007a626b test ah, 0x44
007a626e jp 0x7a6348
007a6274 movss xmm0, dword ptr [edi + 8]
007a6279 ucomiss xmm0, dword ptr [0xc02ff0]
007a6280 lahf 
007a6281 test ah, 0x44
007a6284 jp 0x7a6348
007a628a call 0x6c3d90
007a628f mov esi, dword ptr [edi]
007a6291 movd xmm0, eax
007a6295 cvtdq2pd xmm0, xmm0
007a6299 shr eax, 0x1f
007a629c addsd xmm0, qword ptr [eax*8 + 0xb6c940]
007a62a5 cvtpd2ps xmm0, xmm0
007a62a9 mulss xmm0, dword ptr [0xb6a19c]
007a62b1 mulss xmm0, dword ptr [0xb6a874]
007a62b9 addss xmm0, xmm0
007a62bd movss dword ptr [esp + 0xc], xmm0
007a62c3 call 0x411fe0
007a62c8 mulss xmm0, dword ptr [0xb6aa3c]
007a62d0 addss xmm0, dword ptr [esi + 0x294]
007a62d8 movss dword ptr [esp + 0x10], xmm0
007a62de movss xmm0, dword ptr [esp + 0xc]
007a62e4 call 0x412010
007a62e9 mulss xmm0, dword ptr [0xb6aa3c]
007a62f1 mov ecx, dword ptr [0xbfd65c]
007a62f7 addss xmm0, dword ptr [esi + 0x298]
007a62ff mov ecx, dword ptr [ecx + 0x18190]
007a6305 movss dword ptr [esp + 0x14], xmm0
007a630b push dword ptr [esp + 0x14]
007a630f push dword ptr [esp + 0x14]
007a6313 call 0x7aee40
007a6318 test eax, eax
007a631a jne 0x7a6342
007a631c movss xmm0, dword ptr [esp + 0x10]
007a6322 movss dword ptr [edi + 4], xmm0
007a6327 movss xmm0, dword ptr [esp + 0x14]
007a632d movss dword ptr [edi + 8], xmm0
007a6332 movss xmm1, dword ptr [0xc02fec]
007a633a movss dword ptr [esp + 8], xmm1
007a6340 jmp 0x7a6348
007a6342 movss xmm1, dword ptr [esp + 8]
007a6348 movss xmm2, dword ptr [edi + 4]
007a634d ucomiss xmm2, xmm1
007a6350 lahf 
007a6351 test ah, 0x44
007a6354 jp 0x7a636c
007a6356 movss xmm0, dword ptr [edi + 8]
007a635b ucomiss xmm0, dword ptr [0xc02ff0]
007a6362 lahf 
007a6363 test ah, 0x44
007a6366 jnp 0x7a647d
007a636c mov esi, dword ptr [edi]
007a636e movss xmm1, dword ptr [edi + 8]
007a6373 subss xmm1, dword ptr [esi + 0x298]
007a637b subss xmm2, dword ptr [esi + 0x294]
007a6383 movaps xmm0, xmm1
007a6386 movss dword ptr [esp + 0x10], xmm1
007a638c mulss xmm0, xmm1
007a6390 movaps xmm1, xmm2
007a6393 mulss xmm1, xmm2
007a6397 movss dword ptr [esp + 0xc], xmm2
007a639d addss xmm0, xmm1
007a63a1 call 0x4228c0
007a63a6 movss xmm1, dword ptr [0xb6a864]
007a63ae movaps xmm3, xmm0
007a63b1 comiss xmm1, xmm3
007a63b4 ja 0x7a6487
007a63ba cmp byte ptr [esi + 0x188], 0
007a63c1 jne 0x7a6487
007a63c7 movss xmm0, dword ptr [esi + 0x2b8]
007a63cf movss xmm1, dword ptr [esi + 0x2bc]
007a63d7 mulss xmm0, xmm0
007a63db mulss xmm1, xmm1
007a63df addss xmm1, xmm0
007a63e3 movss xmm0, dword ptr [0xb6a2cc]
007a63eb comiss xmm0, xmm1
007a63ee jbe 0x7a6406
007a63f0 call 0x6c3d90
007a63f5 xor edx, edx
007a63f7 mov ecx, 0xa
007a63fc div ecx
007a63fe test edx, edx
007a6400 je 0x7a6487
007a6406 xorps xmm4, xmm4
007a6409 comiss xmm3, xmm4
007a640c jbe 0x7a647d
007a640e movss xmm1, dword ptr [esp + 0xc]
007a6414 movss xmm2, dword ptr [esp + 0x10]
007a641a mov ecx, dword ptr [edi]
007a641c divss xmm1, xmm3
007a6420 divss xmm2, xmm3
007a6424 movss xmm3, dword ptr [ecx + 0x2c4]
007a642c mulss xmm1, dword ptr [0xb6a480]
007a6434 mulss xmm2, dword ptr [0xb6a480]
007a643c ucomiss xmm3, xmm4
007a643f lahf 
007a6440 test ah, 0x44
007a6443 jnp 0x7a647d
007a6445 movss xmm0, dword ptr [ecx + 0x2f4]
007a644d mulss xmm1, xmm0
007a6451 mulss xmm2, xmm0
007a6455 divss xmm1, xmm3
007a6459 divss xmm2, xmm3
007a645d addss xmm1, dword ptr [ecx + 0x2b8]
007a6465 addss xmm2, dword ptr [ecx + 0x2bc]
007a646d movss dword ptr [ecx + 0x2b8], xmm1
007a6475 movss dword ptr [ecx + 0x2bc], xmm2
007a647d xor al, al
007a647f pop edi
007a6480 pop esi
007a6481 mov esp, ebp
007a6483 pop ebp
007a6484 ret 4
007a6487 movss xmm0, dword ptr [esp + 8]
007a648d movss dword ptr [edi + 4], xmm0
007a6492 movss xmm0, dword ptr [0xc02ff0]
007a649a movss dword ptr [edi + 8], xmm0
007a649f pop edi
007a64a0 mov al, 1
007a64a2 pop esi
007a64a3 mov esp, ebp
007a64a5 pop ebp
