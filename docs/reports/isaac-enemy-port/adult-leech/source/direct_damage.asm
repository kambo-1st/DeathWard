00684bb0 push ebp
00684bb1 mov ebp, esp
00684bb3 and esp, 0xfffffff8
00684bb6 sub esp, 0x3c
00684bb9 push ebx
00684bba push esi
00684bbb push edi
00684bbc mov edi, ecx
00684bbe cmp dword ptr [edi + 0x28], 1
00684bc2 jne 0x684bd3
00684bc4 push 0xb48e70
00684bc9 push 3
00684bcb call 0x95e330
00684bd0 add esp, 8
00684bd3 mov esi, dword ptr [ebp + 0x14]
00684bd6 mov ecx, edi
00684bd8 push esi
00684bd9 call 0x684b00
00684bde test al, al
00684be0 jne 0x684e6b
00684be6 movss xmm0, dword ptr [ebp + 8]
00684beb xorps xmm1, xmm1
00684bee comiss xmm0, xmm1
00684bf1 jbe 0x684e7e
00684bf7 push 0
00684bf9 mov ecx, edi
00684bfb call 0x684630
00684c00 test al, al
00684c02 jne 0x684c16
00684c04 cmp dword ptr [edi + 0x28], 0x3b6
00684c0b jne 0x684e76
00684c11 mov eax, dword ptr [edi + 0x28]
00684c14 jmp 0x684c24
00684c16 mov eax, dword ptr [edi + 0x28]
00684c19 cmp eax, 0x325
00684c1e je 0x684e76
00684c24 cmp eax, 0x340
00684c29 jne 0x684c56
00684c2b cmp dword ptr [edi + 0x2c], 1
00684c2f jne 0x684c9a
00684c31 mov ebx, dword ptr [edi + 0x320]
00684c37 test ebx, ebx
00684c39 je 0x684c9a
00684c3b cmp dword ptr [ebx + 0x28], 0x389
00684c42 jne 0x684c9a
00684c44 mov eax, dword ptr [edi + 0xab4]
00684c4a cmp eax, 0x10
00684c4d je 0x684cc8
00684c4f cmp eax, 5
00684c52 jne 0x684c9a
00684c54 jmp 0x684cc8
00684c56 cmp eax, 0x3b6
00684c5b jne 0x684c6f
00684c5d cmp dword ptr [edi + 0x2c], 0
00684c61 jne 0x684c9a
00684c63 mov ebx, dword ptr [edi + 0x314]
00684c69 test ebx, ebx
00684c6b je 0x684c9a
00684c6d jmp 0x684cc8
00684c6f cmp eax, 0x379
00684c74 jne 0x684c9a
00684c76 mov ebx, dword ptr [edi + 0x314]
00684c7c test ebx, ebx
00684c7e je 0x684c9a
00684c80 cmp dword ptr [ebx + 0x28], 0x399
00684c87 jne 0x684c9a
00684c89 cmp dword ptr [ebx + 0x318], edi
00684c8f jne 0x684cc8
00684c91 cmp dword ptr [ebx + 0x180], 0
00684c98 jne 0x684cc8
00684c9a push 0
00684c9c push 0x20000000
00684ca1 mov ecx, edi
00684ca3 call 0x4122f0
00684ca8 movzx eax, al
00684cab lea ecx, [edi + 0x294]
00684cb1 push eax
00684cb2 lea edx, [esp + 0x10]
00684cb6 call 0x4d52c0
00684cbb mov ebx, eax
00684cbd add esp, 4
00684cc0 test ebx, ebx
00684cc2 je 0x684e76
00684cc8 mov esi, dword ptr [0xbfd680]
00684cce lea ecx, [esp + 0xc]
00684cd2 mov dword ptr [esp + 0xc], 0x1f5
00684cda call 0x8b1340
00684cdf sub esp, 8
00684ce2 mov dword ptr [esp + 4], 0
00684cea mov dword ptr [esp], 0x3f800000
00684cf1 push 0
00684cf3 push 0xa
00684cf5 push ecx
00684cf6 mov dword ptr [esp], 0x3f800000
00684cfd lea ecx, [esi + 0x29de0]
00684d03 push dword ptr [esp + 0x20]
00684d07 call 0x888de0
00684d0c mov ecx, dword ptr [edi + 0x330]
00684d12 test ecx, ecx
00684d14 je 0x684d1b
00684d16 mov eax, dword ptr [ecx]
00684d18 call dword ptr [eax + 0x28]
00684d1b call 0x6c3d90
00684d20 mov ecx, dword ptr [0xbfd65c]
00684d26 push 0
00684d28 push eax
00684d29 push 0
00684d2b push ebx
00684d2c push 0xc02fec
00684d31 lea eax, [edi + 0x294]
00684d37 push eax
00684d38 push 0xa0
00684d3d push 0x3e8
00684d42 call 0x6d0ca0
00684d47 mov esi, eax
00684d49 mov ecx, dword ptr [esi + 0x314]
00684d4f lea eax, [esi + 0x314]
00684d55 test ecx, ecx
00684d57 je 0x684d73
00684d59 mov dword ptr [esp + 0xc], eax
00684d5d add ecx, 0x324
00684d63 lea eax, [esp + 0xc]
00684d67 push eax
00684d68 call 0x4bc3c0
00684d6d lea eax, [esi + 0x314]
00684d73 mov dword ptr [eax], ebx
00684d75 test ebx, ebx
00684d77 je 0x684d81
00684d79 push eax
00684d7a mov ecx, ebx
00684d7c call 0x4bae70
00684d81 mov ecx, dword ptr [esi + 0x31c]
00684d87 lea ebx, [esi + 0x31c]
00684d8d test ecx, ecx
00684d8f je 0x684da5
00684d91 lea eax, [esp + 0xc]
00684d95 mov dword ptr [esp + 0xc], ebx
00684d99 push eax
00684d9a add ecx, 0x324
00684da0 call 0x4bc3c0
00684da5 push ebx
00684da6 mov ecx, edi
00684da8 mov dword ptr [ebx], edi
00684daa call 0x4bae70
00684daf mov dword ptr [esi + 0x3b8], 0
00684db9 mov dword ptr [esi + 0x3bc], 0xc1c00000
00684dc3 cmp dword ptr [edi + 0x70], 0
00684dc7 je 0x684e32
00684dc9 push 0xb40e34
00684dce lea ecx, [edi + 0x6c]
00684dd1 call 0x405da0
00684dd6 test eax, eax
00684dd8 je 0x684e32
00684dda movss xmm3, dword ptr [eax]
00684dde xorps xmm2, xmm2
00684de1 subss xmm3, xmm2
00684de5 movss xmm2, dword ptr [eax + 4]
00684dea subss xmm2, dword ptr [0xb6a8cc]
00684df2 mulss xmm3, dword ptr [0xb6a480]
00684dfa mulss xmm2, dword ptr [0xb6a480]
00684e02 divss xmm3, dword ptr [0xb6a4dc]
00684e0a divss xmm2, dword ptr [0xb6a4dc]
00684e12 addss xmm3, dword ptr [edi + 0x2a4]
00684e1a addss xmm2, dword ptr [edi + 0x2a8]
00684e22 movss dword ptr [esi + 0x2a4], xmm3
00684e2a movss dword ptr [esi + 0x2a8], xmm2
00684e32 mov eax, dword ptr [esi]
00684e34 mov ecx, esi
00684e36 call dword ptr [eax + 0xc]
00684e39 mov ecx, dword ptr [edi + 0x330]
00684e3f lea ebx, [edi + 0x330]
00684e45 cmp ecx, esi
00684e47 je 0x684e6b
00684e49 test ecx, ecx
00684e4b je 0x684e61
00684e4d lea eax, [esp + 0xc]
00684e51 mov dword ptr [esp + 0xc], ebx
00684e55 push eax
00684e56 add ecx, 0x324
00684e5c call 0x4bc3c0
00684e61 push ebx
00684e62 mov ecx, esi
00684e64 mov dword ptr [ebx], esi
00684e66 call 0x4bae70
00684e6b xor al, al
00684e6d pop edi
00684e6e pop esi
00684e6f pop ebx
00684e70 mov esp, ebp
00684e72 pop ebp
00684e73 ret 0x14
00684e76 movss xmm0, dword ptr [ebp + 8]
00684e7b xorps xmm1, xmm1
00684e7e mov ebx, dword ptr [ebp + 0xc]
00684e81 mov eax, ebx
00684e83 and eax, 2
00684e86 or eax, 0
00684e89 je 0x684ea3
00684e8b comiss xmm0, xmm1
00684e8e jbe 0x684ea3
00684e90 cmp dword ptr [edi + 0x208], 0
00684e97 jg 0x684e6b
00684e99 mov dword ptr [edi + 0x208], 0xa
00684ea3 mov eax, ebx
00684ea5 and eax, 0x40
00684ea8 or eax, 0
00684eab je 0x684ebf
00684ead cmp dword ptr [edi + 0x20c], 0
00684eb4 jg 0x684e6b
00684eb6 mov eax, dword ptr [ebp + 0x18]
00684eb9 mov dword ptr [edi + 0x20c], eax
00684ebf mov eax, ebx
00684ec1 and eax, 0x2000
00684ec6 or eax, 0
00684ec9 jne 0x684f65
00684ecf mov eax, dword ptr [edi]
00684ed1 mov ecx, edi
00684ed3 mov eax, dword ptr [eax + 0x48]
00684ed6 call eax
00684ed8 test al, al
00684eda je 0x684f65
00684ee0 mov ecx, dword ptr [0xbfd65c]
00684ee6 mov eax, dword ptr [ecx + 0x1ba54]
00684eec sub eax, dword ptr [ecx + 0x1ba50]
00684ef2 sar eax, 2
00684ef5 cmp eax, 1
00684ef8 jbe 0x684f65
00684efa xor ebx, ebx
00684efc xor esi, esi
00684efe nop 
00684f00 push esi
00684f01 call 0x412750
00684f06 mov edx, dword ptr [eax + 0x1d80]
00684f0c test edx, edx
00684f0e je 0x684f22
00684f10 mov ecx, dword ptr [edx + 0x1550]
00684f16 cmp ecx, dword ptr [eax + 0x1550]
00684f1c jge 0x684f22
00684f1e cmp eax, edx
00684f20 jne 0x684f2c
00684f22 cmp dword ptr [eax + 0x314], 0
00684f29 jne 0x684f2c
00684f2b inc ebx
00684f2c mov ecx, dword ptr [0xbfd65c]
00684f32 inc esi
00684f33 mov eax, dword ptr [ecx + 0x1ba54]
00684f39 sub eax, dword ptr [ecx + 0x1ba50]
00684f3f sar eax, 2
00684f42 cmp esi, eax
00684f44 jb 0x684f00
00684f46 movss xmm1, dword ptr [ebp + 8]
00684f4b cmp ebx, 1
00684f4e mov esi, dword ptr [ebp + 0x14]
00684f51 mov ebx, dword ptr [ebp + 0xc]
00684f54 jle 0x684f6a
00684f56 mulss xmm1, dword ptr [0xb6a560]
00684f5e movss dword ptr [ebp + 8], xmm1
00684f63 jmp 0x684f6a
00684f65 movss xmm1, dword ptr [ebp + 8]
00684f6a mov ecx, dword ptr [edi + 0x164]
00684f70 xor eax, eax
00684f72 and ecx, 0x400000
00684f78 or eax, ecx
00684f7a je 0x684f88
00684f7c movaps xmm0, xmm1
00684f7f addss xmm1, xmm0
00684f83 movss dword ptr [ebp + 8], xmm1
00684f88 movss xmm0, dword ptr [edi + 0x2dc]
00684f90 xorps xmm2, xmm2
00684f93 comiss xmm0, xmm2
00684f96 jbe 0x684e6b
00684f9c push dword ptr [ebp + 0x18]
00684f9f movaps xmm2, xmm1
00684fa2 push esi
00684fa3 mov esi, dword ptr [ebp + 0x10]
00684fa6 push esi
00684fa7 push ebx
00684fa8 push edi
00684fa9 call 0x800e30
00684fae test al, al
00684fb0 je 0x684e6b
00684fb6 lea ecx, [esp + 0x10]
00684fba call 0x680d60
00684fbf movss xmm0, dword ptr [ebp + 8]
00684fc4 lea ecx, [esp + 0x20]
00684fc8 push dword ptr [ebp + 0x14]
00684fcb movss dword ptr [esp + 0x14], xmm0
00684fd1 mov dword ptr [esp + 0x1c], ebx
00684fd5 mov dword ptr [esp + 0x20], esi
00684fd9 call 0x4862d0
00684fde lea eax, [esp + 0x10]
00684fe2 push eax
00684fe3 lea ecx, [edi + 8]
00684fe6 call 0x68f0f0
00684feb movss xmm0, dword ptr [ebp + 8]
00684ff0 mov al, 1
00684ff2 addss xmm0, dword ptr [edi + 0x14]
00684ff7 or dword ptr [edi + 0x18], ebx
00684ffa or dword ptr [edi + 0x1c], esi
00684ffd movss dword ptr [edi + 0x14], xmm0
00685002 pop edi
00685003 pop esi
00685004 pop ebx
00685005 mov esp, ebp
00685007 pop ebp
00685008 ret 0x14
