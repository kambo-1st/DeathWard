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
0068500b int3 
0068500c int3 
0068500d int3 
0068500e int3 
0068500f int3 
00685010 movss xmm0, dword ptr [ecx + 0x14]
00685015 comiss xmm0, dword ptr [ecx + 0x2d8]
0068501c setae al
0068501f ret 
00685020 push ebp
00685021 mov ebp, esp
00685023 push ecx
00685024 cmp dword ptr [ecx + 0x28], 1
00685028 push esi
00685029 je 0x685074
0068502b mov eax, dword ptr [ebp + 0xc]
0068502e mov esi, dword ptr [eax + 0x24]
00685031 test esi, esi
00685033 je 0x685074
00685035 mov eax, dword ptr [esi + 0x320]
0068503b test eax, eax
0068503d je 0x68504c
0068503f nop 
00685040 mov esi, eax
00685042 mov eax, dword ptr [esi + 0x320]
00685048 test eax, eax
0068504a jne 0x685040
0068504c cmp dword ptr [esi + 0x28], 1
00685050 jne 0x685074
00685052 push 0x4e
00685054 mov ecx, esi
00685056 call 0x78d4c0
0068505b test eax, eax
0068505d jle 0x685074
0068505f push 0x4e
00685061 mov ecx, esi
00685063 call 0x78d4c0
00685068 imul eax, dword ptr [ebp + 8]
0068506c add eax, eax
0068506e pop esi
0068506f pop ecx
00685070 pop ebp
00685071 ret 8
00685074 mov eax, dword ptr [ebp + 8]
00685077 pop esi
00685078 pop ecx
00685079 pop ebp
0068507a ret 8
0068507d int3 
0068507e int3 
0068507f int3 
00685080 push ebp
00685081 mov ebp, esp
00685083 and esp, 0xfffffff8
00685086 sub esp, 0x34
00685089 mov eax, dword ptr [0xbaa3b4]
0068508e xor eax, esp
00685090 mov dword ptr [esp + 0x30], eax
00685094 push ebx
00685095 push esi
00685096 push edi
00685097 mov edi, dword ptr [ebp + 8]
0068509a mov esi, ecx
0068509c push edi
0068509d call 0x684b00
006850a2 test al, al
006850a4 jne 0x68519f
006850aa push edi
006850ab push dword ptr [ebp + 0xc]
006850ae mov ecx, esi
006850b0 call 0x685020
006850b5 mov ecx, esi
006850b7 mov edx, eax
006850b9 call 0x681710
006850be test al, al
006850c0 je 0x6850dc
006850c2 mov ecx, dword ptr [esi + 0x314]
006850c8 test ecx, ecx
006850ca je 0x6850dc
006850cc nop dword ptr [eax]
006850d0 mov esi, ecx
006850d2 mov ecx, dword ptr [esi + 0x314]
006850d8 test ecx, ecx
006850da jne 0x6850d0
006850dc test edx, edx
006850de je 0x68519f
006850e4 mov edi, dword ptr [esi + 0x160]
006850ea mov eax, edi
006850ec mov ebx, dword ptr [esi + 0x164]
006850f2 and eax, 1
006850f5 or eax, 0
006850f8 jne 0x68519f
006850fe cmp dword ptr [esi + 0x230], eax
00685104 jg 0x68519f
0068510a mov ecx, dword ptr [esi + 0x210]
00685110 test edx, edx
00685112 jle 0x685123
00685114 lea eax, [ecx + edx]
00685117 mov ecx, 0x78
0068511c cmp eax, ecx
0068511e cmovl ecx, eax
00685121 jmp 0x68512a
00685123 neg edx
00685125 cmp ecx, edx
00685127 cmovl ecx, edx
0068512a mov dword ptr [esi + 0x210], ecx
00685130 xorps xmm0, xmm0
00685133 mov eax, dword ptr [esi]
00685135 or edi, 0x20
00685138 push 1
0068513a push 0
0068513c push 0xff
00685141 push ecx
00685142 lea ecx, [esp + 0x20]
00685146 mov dword ptr [esi + 0x160], edi
0068514c movups xmmword ptr [esp + 0x30], xmm0
00685151 push ecx
00685152 movaps xmm0, xmmword ptr [0xb6c0e0]
00685159 mov ecx, esi
0068515b mov dword ptr [esi + 0x164], ebx
00685161 movups xmmword ptr [esp + 0x24], xmm0
00685166 mov dword ptr [esp + 0x44], 0x3e20a0a1
0068516e mov dword ptr [esp + 0x48], 0x3e20a0a1
00685176 mov dword ptr [esp + 0x4c], 0x3e20a0a1
0068517e call dword ptr [eax + 0x38]
00685181 mov eax, dword ptr [esi]
00685183 mov ecx, esi
00685185 mov eax, dword ptr [eax + 0x48]
00685188 call eax
0068518a test al, al
0068518c je 0x685198
0068518e mov dword ptr [esi + 0x230], 0xf0
00685198 mov ecx, esi
0068519a call 0x681390
0068519f mov ecx, dword ptr [esp + 0x3c]
006851a3 pop edi
006851a4 pop esi
006851a5 pop ebx
006851a6 xor ecx, esp
006851a8 call 0x9eacd7
006851ad mov esp, ebp
006851af pop ebp
006851b0 ret 8
006851b3 int3 
006851b4 int3 
006851b5 int3 
006851b6 int3 
006851b7 int3 
006851b8 int3 
006851b9 int3 
006851ba int3 
006851bb int3 
006851bc int3 
006851bd int3 
006851be int3 
006851bf int3 
006851c0 push ebp
006851c1 mov ebp, esp
006851c3 and esp, 0xfffffff8
006851c6 sub esp, 0x34
006851c9 mov eax, dword ptr [0xbaa3b4]
006851ce xor eax, esp
006851d0 mov dword ptr [esp + 0x30], eax
006851d4 push ebx
006851d5 push esi
006851d6 push edi
006851d7 mov edi, dword ptr [ebp + 8]
006851da mov esi, ecx
006851dc push edi
006851dd call 0x684b00
006851e2 test al, al
006851e4 jne 0x6853de
006851ea cmp dword ptr [esi + 0x28], 1
006851ee jne 0x685206
006851f0 push 0
006851f2 push 0x278
006851f7 mov ecx, esi
006851f9 call 0x73af30
006851fe test al, al
00685200 jne 0x6853de
00685206 push edi
00685207 push dword ptr [ebp + 0xc]
0068520a mov ecx, esi
0068520c call 0x685020
00685211 movss xmm1, dword ptr [ebp + 0x10]
00685216 xorps xmm0, xmm0
00685219 comiss xmm0, xmm1
0068521c mov edx, eax
0068521e jb 0x685264
00685220 cmp dword ptr [esi + 0x28], 1
00685224 je 0x68525c
00685226 mov ecx, dword ptr [edi + 0x24]
00685229 test ecx, ecx
0068522b je 0x68525c
0068522d mov eax, dword ptr [ecx + 0x320]
00685233 test eax, eax
00685235 je 0x68524c
00685237 nop word ptr [eax + eax]
00685240 mov ecx, eax
00685242 mov eax, dword ptr [ecx + 0x320]
00685248 test eax, eax
0068524a jne 0x685240
0068524c cmp dword ptr [ecx + 0x28], 1
00685250 jne 0x68525c
00685252 movss xmm1, dword ptr [ecx + 0x14c0]
0068525a jmp 0x685264
0068525c movss xmm1, dword ptr [0xb6a7b0]
00685264 mov ecx, esi
00685266 call 0x681710
0068526b test al, al
0068526d je 0x68528c
0068526f mov eax, dword ptr [esi + 0x314]
00685275 test eax, eax
00685277 je 0x68528c
00685279 nop dword ptr [eax]
00685280 mov esi, eax
00685282 mov eax, dword ptr [esi + 0x314]
00685288 test eax, eax
0068528a jne 0x685280
0068528c test edx, edx
0068528e je 0x6853de
00685294 mov edi, dword ptr [esi + 0x160]
0068529a mov eax, edi
0068529c mov ebx, dword ptr [esi + 0x164]
006852a2 and eax, 1
006852a5 or eax, 0
006852a8 jne 0x6853de
006852ae cmp dword ptr [esi + 0x230], eax
006852b4 jg 0x6853de
006852ba mov ecx, dword ptr [esi + 0x214]
006852c0 test edx, edx
006852c2 jle 0x6852d3
006852c4 lea eax, [ecx + edx]
006852c7 mov ecx, 0x78
006852cc cmp eax, ecx
006852ce cmovl ecx, eax
006852d1 jmp 0x6852da
006852d3 neg edx
006852d5 cmp ecx, edx
006852d7 cmovl ecx, edx
006852da mov eax, edi
006852dc mov dword ptr [esi + 0x214], ecx
006852e2 and eax, 0x40
006852e5 or eax, 0
006852e8 jne 0x6852f0
006852ea mov dword ptr [esi + 0x238], eax
006852f0 movss xmm0, dword ptr [esi + 0x278]
006852f8 comiss xmm0, xmm1
006852fb ja 0x685303
006852fd movss xmm0, xmm1
00685301 jmp 0x685307
00685303 movss xmm0, xmm0
00685307 or edi, 0x40
0068530a mov dword ptr [esp + 0x14], 0x3f800000
00685312 push 1
00685314 push 0
00685316 push 0xff
0068531b push ecx
0068531c mov dword ptr [esp + 0x2c], 0x3f800000
00685324 movss xmm2, dword ptr [0xb6aba8]
0068532c movss dword ptr [esi + 0x278], xmm0
00685334 movd xmm0, ecx
00685338 lea ecx, [esp + 0x20]
0068533c cvtdq2ps xmm0, xmm0
0068533f push ecx
00685340 mov ecx, esi
00685342 mov dword ptr [esi + 0x160], edi
00685348 mov dword ptr [esi + 0x164], ebx
0068534e mov dword ptr [esp + 0x44], 0
00685356 mov dword ptr [esp + 0x4c], 0
0068535e subss xmm2, xmm0
00685362 xorps xmm0, xmm0
00685365 movups xmmword ptr [esp + 0x34], xmm0
0068536a movss xmm0, dword ptr [0xb6a614]
00685372 divss xmm2, dword ptr [0xb6aba8]
0068537a subss xmm2, dword ptr [0xb6a2cc]
00685382 maxss xmm2, dword ptr [0xb6a4c4]
0068538a subss xmm0, xmm2
0068538e movss dword ptr [esp + 0x24], xmm2
00685394 movss dword ptr [esp + 0x2c], xmm2
0068539a mulss xmm0, dword ptr [0xb6aae4]
006853a2 cvttss2si eax, xmm0
006853a6 movd xmm0, eax
006853aa mov eax, dword ptr [esi]
006853ac cvtdq2ps xmm0, xmm0
006853af mulss xmm0, dword ptr [0xb6a1f4]
006853b7 movss dword ptr [esp + 0x48], xmm0
006853bd call dword ptr [eax + 0x38]
006853c0 mov eax, dword ptr [esi]
006853c2 mov ecx, esi
006853c4 mov eax, dword ptr [eax + 0x48]
006853c7 call eax
006853c9 test al, al
006853cb je 0x6853d7
006853cd mov dword ptr [esi + 0x230], 0xf0
006853d7 mov ecx, esi
006853d9 call 0x681390
006853de mov ecx, dword ptr [esp + 0x3c]
006853e2 pop edi
006853e3 pop esi
006853e4 pop ebx
006853e5 xor ecx, esp
006853e7 call 0x9eacd7
006853ec mov esp, ebp
006853ee pop ebp
006853ef ret 0xc
006853f2 int3 
006853f3 int3 
006853f4 int3 
006853f5 int3 
006853f6 int3 
006853f7 int3 
006853f8 int3 
006853f9 int3 
006853fa int3 
006853fb int3 
006853fc int3 
006853fd int3 
006853fe int3 
006853ff int3 
00685400 push ebp
00685401 mov ebp, esp
00685403 and esp, 0xfffffff8
00685406 push esi
00685407 push edi
00685408 mov edi, dword ptr [ebp + 8]
0068540b mov esi, ecx
0068540d push edi
0068540e call 0x684b00
00685413 test al, al
00685415 jne 0x685500
0068541b push edi
0068541c push dword ptr [ebp + 0xc]
0068541f mov ecx, esi
00685421 call 0x685020
00685426 mov ecx, esi
00685428 mov edx, eax
0068542a call 0x681710
0068542f test al, al
00685431 je 0x68544c
00685433 mov ecx, dword ptr [esi + 0x314]
00685439 test ecx, ecx
0068543b je 0x68544c
0068543d nop dword ptr [eax]
00685440 mov esi, ecx
00685442 mov ecx, dword ptr [esi + 0x314]
00685448 test ecx, ecx
0068544a jne 0x685440
0068544c test edx, edx
0068544e jle 0x6854b8
00685450 mov ecx, dword ptr [esi + 0x160]
00685456 mov eax, ecx
00685458 mov edi, dword ptr [esi + 0x164]
0068545e and eax, 1
00685461 or eax, 0
00685464 jne 0x6854ec
0068546a cmp dword ptr [esi + 0x230], eax
00685470 jg 0x6854ec
00685472 mov eax, dword ptr [esi]
00685474 or ecx, 0x80
0068547a add dword ptr [esi + 0x218], edx
00685480 push 1
00685482 push 0
00685484 push 0xff
00685489 mov dword ptr [esi + 0x160], ecx
0068548f lea ecx, [ebp + 0x14]
00685492 push edx
00685493 push ecx
00685494 mov ecx, esi
00685496 mov dword ptr [esi + 0x164], edi
0068549c call dword ptr [eax + 0x38]
0068549f mov eax, dword ptr [esi]
006854a1 mov ecx, esi
006854a3 mov eax, dword ptr [eax + 0x48]
006854a6 call eax
006854a8 test al, al
006854aa je 0x6854ec
006854ac mov dword ptr [esi + 0x230], 0xf0
006854b6 jmp 0x6854ec
006854b8 jns 0x6854ec
006854ba mov ecx, dword ptr [esi + 0x160]
006854c0 mov eax, ecx
006854c2 mov edx, dword ptr [esi + 0x164]
006854c8 and eax, 1
006854cb or eax, 0
006854ce jne 0x6854ec
006854d0 or ecx, 0x80
006854d6 mov dword ptr [esi + 0x218], 2
006854e0 mov dword ptr [esi + 0x160], ecx
006854e6 mov dword ptr [esi + 0x164], edx
006854ec movss xmm0, dword ptr [ebp + 0x10]
006854f1 mov ecx, esi
006854f3 movss dword ptr [esi + 0x304], xmm0
006854fb call 0x681390
00685500 pop edi
00685501 pop esi
00685502 mov esp, ebp
00685504 pop ebp
00685505 ret 0x38
00685508 int3 
00685509 int3 
0068550a int3 
0068550b int3 
0068550c int3 
0068550d int3 
0068550e int3 
0068550f int3 
00685510 push ebp
00685511 mov ebp, esp
00685513 and esp, 0xfffffff8
00685516 sub esp, 0x3c
00685519 mov eax, dword ptr [0xbaa3b4]
0068551e xor eax, esp
00685520 mov dword ptr [esp + 0x38], eax
00685524 push ebx
00685525 push esi
00685526 push edi
00685527 mov edi, ecx
00685529 mov ecx, dword ptr [ebp + 8]
0068552c mov eax, dword ptr [edi + 0x160]
00685532 and eax, 0x20000000
00685537 or eax, 0
0068553a jne 0x6857ae
00685540 push ecx
00685541 push dword ptr [ebp + 0xc]
00685544 mov ecx, edi
00685546 call 0x685020
0068554b mov ecx, edi
0068554d mov ebx, eax
0068554f mov esi, edi
00685551 call 0x681710
00685556 test al, al
00685558 je 0x685570
0068555a mov ecx, dword ptr [edi + 0x314]
00685560 test ecx, ecx
00685562 je 0x685570
00685564 mov esi, ecx
00685566 mov ecx, dword ptr [esi + 0x314]
0068556c test ecx, ecx
0068556e jne 0x685564
00685570 mov edx, dword ptr [esi + 0x160]
00685576 mov eax, edx
00685578 mov ecx, dword ptr [esi + 0x164]
0068557e and eax, 0x20000100
00685583 or eax, 0
00685586 mov byte ptr [esp + 0x13], 1
0068558b jne 0x685592
0068558d mov byte ptr [esp + 0x13], 0
00685592 test ebx, ebx
00685594 jle 0x68563f
0068559a mov eax, edx
0068559c and eax, 1
0068559f or eax, 0
006855a2 jne 0x685768
006855a8 cmp dword ptr [esi + 0x230], eax
006855ae jg 0x685768
006855b4 mov ecx, dword ptr [esi + 0x21c]
006855ba xorps xmm0, xmm0
006855bd cmp ecx, ebx
006855bf mov dword ptr [esp + 0x38], 0x3e20a0a1
006855c7 push 1
006855c9 cmovl ecx, ebx
006855cc mov dword ptr [esp + 0x40], 0x3e20a0a1
006855d4 mov dword ptr [esi + 0x21c], ecx
006855da or edx, 0x100
006855e0 mov eax, dword ptr [esi + 0x164]
006855e6 push 0
006855e8 push 0xff
006855ed push ecx
006855ee mov dword ptr [esi + 0x164], eax
006855f4 lea ecx, [esp + 0x28]
006855f8 mov eax, dword ptr [esi]
006855fa movups xmmword ptr [esp + 0x38], xmm0
006855ff push ecx
00685600 movaps xmm0, xmmword ptr [0xb6c470]
00685607 mov ecx, esi
00685609 mov dword ptr [esi + 0x160], edx
0068560f movups xmmword ptr [esp + 0x2c], xmm0
00685614 mov dword ptr [esp + 0x54], 0x3e20a0a1
0068561c call dword ptr [eax + 0x38]
0068561f mov eax, dword ptr [esi]
00685621 mov ecx, esi
00685623 mov eax, dword ptr [eax + 0x48]
00685626 call eax
00685628 test al, al
0068562a je 0x685768
00685630 mov dword ptr [esi + 0x230], 0xf0
0068563a jmp 0x685768
0068563f jns 0x685768
00685645 or edx, 0x20000100
0068564b mov dword ptr [esi + 0x164], ecx
00685651 mov dword ptr [esi + 0x21c], 0
0068565b mov ecx, edi
0068565d mov dword ptr [esi + 0x160], edx
00685663 mov eax, dword ptr [edi]
00685665 mov eax, dword ptr [eax + 0x48]
00685668 call eax
0068566a test al, al
0068566c jne 0x6856a4
0068566e push 0
00685670 mov ecx, edi
00685672 call 0x68cf40
00685677 test al, al
00685679 je 0x6856a4
0068567b cmp dword ptr [edi + 0x28], 0x17
0068567f jne 0x68568d
00685681 cmp dword ptr [edi + 0x2c], 0
00685685 jne 0x68568d
00685687 cmp dword ptr [edi + 0x30], 1
0068568b je 0x6856a4
0068568d mov eax, dword ptr [0xbfd65c]
00685692 push edi
00685693 mov ecx, dword ptr [eax + 0x18190]
00685699 add ecx, 0x1218
0068569f call 0x416340
006856a4 mov ecx, dword ptr [0xbfd65c]
006856aa call 0x6d7180
006856af test al, al
006856b1 jne 0x685754
006856b7 mov eax, dword ptr [0xbfd680]
006856bc cmp byte ptr [eax + 0x1cf], 0
006856c3 jne 0x685754
006856c9 cmp dword ptr [eax + 8], 2
006856cd mov eax, dword ptr [0xbfd65c]
006856d2 jne 0x6856ea
006856d4 test eax, eax
006856d6 je 0x6856ea
006856d8 cmp dword ptr [eax + 0x1c3204], 0
006856df ja 0x685754
006856e1 cmp byte ptr [eax + 0x1c31a1], 0
006856e8 jne 0x685754
006856ea mov edx, dword ptr [eax + 0x18190]
006856f0 xor edi, edi
006856f2 mov ebx, dword ptr [edx + 0x1264]
006856f8 test ebx, ebx
006856fa je 0x685754
006856fc mov edx, dword ptr [edx + 0x125c]
00685702 mov ecx, dword ptr [edx]
00685704 mov eax, dword ptr [ecx + 0x28]
00685707 sub eax, 0xa
0068570a cmp eax, 0x3dd
0068570f ja 0x685734
00685711 mov eax, dword ptr [ecx + 0x160]
00685717 and eax, 0x20000000
0068571c or eax, 0
0068571f je 0x685734
00685721 call 0x681710
00685726 test al, al
00685728 je 0x685733
0068572a cmp dword ptr [ecx + 0x314], 0
00685731 jne 0x685734
00685733 inc edi
00685734 add edx, 4
00685737 sub ebx, 1
0068573a jne 0x685702
0068573c cmp edi, 3
0068573f jb 0x685754
00685741 mov ecx, dword ptr [0xbfd680]
00685747 push 0x183
0068574c add ecx, 0x14
0068574f call 0x884c80
00685754 mov eax, dword ptr [esi + 0x28]
00685757 sub eax, 0xa
0068575a cmp eax, 0x3dd
0068575f ja 0x685768
00685761 mov eax, dword ptr [esi]
00685763 mov ecx, esi
00685765 call dword ptr [eax + 0x5c]
00685768 mov ecx, esi
0068576a call 0x681390
0068576f cmp dword ptr [esi + 0x21c], 0
00685776 je 0x6857ae
00685778 cmp byte ptr [esp + 0x13], 0
0068577d jne 0x6857ae
0068577f mov eax, dword ptr [esi + 0x28]
00685782 sub eax, 0xa
00685785 cmp eax, 0x3dd
0068578a ja 0x6857ae
0068578c push 0
0068578e push 0xbeab70
00685793 push 0xbeab18
00685798 push 0
0068579a push esi
0068579b call 0x9ec34c
006857a0 add esp, 0x14
006857a3 test eax, eax
006857a5 je 0x6857ae
006857a7 mov ecx, eax
006857a9 call 0x680df0
006857ae mov ecx, dword ptr [esp + 0x44]
006857b2 pop edi
006857b3 pop esi
006857b4 pop ebx
006857b5 xor ecx, esp
006857b7 call 0x9eacd7
006857bc mov esp, ebp
006857be pop ebp
006857bf ret 8
006857c2 int3 
006857c3 int3 
006857c4 int3 
006857c5 int3 
006857c6 int3 
006857c7 int3 
006857c8 int3 
006857c9 int3 
006857ca int3 
006857cb int3 
006857cc int3 
006857cd int3 
006857ce int3 
006857cf int3 
006857d0 push ebp
006857d1 mov ebp, esp
006857d3 and esp, 0xfffffff8
006857d6 sub esp, 0x3c
006857d9 mov eax, dword ptr [0xbaa3b4]
006857de xor eax, esp
006857e0 mov dword ptr [esp + 0x38], eax
006857e4 push ebx
006857e5 push esi
006857e6 push edi
006857e7 mov edi, dword ptr [ebp + 8]
006857ea mov esi, ecx
006857ec push edi
006857ed call 0x684b00
006857f2 test al, al
006857f4 jne 0x685976
006857fa cmp dword ptr [esi + 0x28], 1
006857fe jne 0x685816
00685800 push 0
00685802 push 0x278
00685807 mov ecx, esi
00685809 call 0x73af30
0068580e test al, al
00685810 jne 0x685976
00685816 push edi
00685817 push dword ptr [ebp + 0xc]
0068581a mov ecx, esi
0068581c call 0x685020
00685821 mov ecx, esi
00685823 mov edi, eax
00685825 call 0x681710
0068582a test al, al
0068582c je 0x68584c
0068582e mov ecx, dword ptr [esi + 0x314]
00685834 test ecx, ecx
00685836 je 0x68584c
00685838 nop dword ptr [eax + eax]
00685840 mov esi, ecx
00685842 mov ecx, dword ptr [esi + 0x314]
00685848 test ecx, ecx
0068584a jne 0x685840
0068584c mov ecx, dword ptr [esi + 0x160]
00685852 mov eax, ecx
00685854 and eax, 0x200
00685859 or eax, 0
0068585c je 0x685862
0068585e mov bl, 1
00685860 jmp 0x685864
00685862 xor bl, bl
00685864 test edi, edi
00685866 je 0x685933
0068586c mov eax, ecx
0068586e and eax, 1
00685871 or eax, 0
00685874 jne 0x685933
0068587a mov bh, byte ptr [ebp + 0x10]
0068587d cmp dword ptr [esi + 0x230], eax
00685883 jle 0x68588d
00685885 test bh, bh
00685887 je 0x685933
0068588d mov edx, dword ptr [esi + 0x220]
00685893 test edi, edi
00685895 jle 0x6858b1
00685897 lea eax, [edx + edi]
0068589a mov ecx, 0x78
0068589f cmp eax, ecx
006858a1 cmovl ecx, eax
006858a4 cmp edx, ecx
006858a6 cmovl edx, ecx
006858a9 mov ecx, dword ptr [esi + 0x160]
006858af jmp 0x6858b8
006858b1 neg edi
006858b3 cmp edx, edi
006858b5 cmovl edx, edi
006858b8 mov dword ptr [esi + 0x220], edx
006858be or ecx, 0x200
006858c4 mov eax, dword ptr [esi + 0x164]
006858ca xorps xmm0, xmm0
006858cd push 1
006858cf push 0
006858d1 push 0xff
006858d6 mov dword ptr [esi + 0x160], ecx
006858dc lea ecx, [esp + 0x24]
006858e0 mov dword ptr [esi + 0x164], eax
006858e6 mov eax, dword ptr [esi]
006858e8 push edx
006858e9 movups xmmword ptr [esp + 0x38], xmm0
006858ee push ecx
006858ef movaps xmm0, xmmword ptr [0xb6c290]
006858f6 mov ecx, esi
006858f8 movups xmmword ptr [esp + 0x2c], xmm0
006858fd mov dword ptr [esp + 0x4c], 0x3e20a0a1
00685905 mov dword ptr [esp + 0x50], 0x3e20a0a1
0068590d mov dword ptr [esp + 0x54], 0x3e20a0a1
00685915 call dword ptr [eax + 0x38]
00685918 test bh, bh
0068591a jne 0x685933
0068591c mov eax, dword ptr [esi]
0068591e mov ecx, esi
00685920 mov eax, dword ptr [eax + 0x48]
00685923 call eax
00685925 test al, al
00685927 je 0x685933
00685929 mov dword ptr [esi + 0x230], 0xf0
00685933 mov ecx, esi
00685935 call 0x681390
0068593a cmp dword ptr [esi + 0x220], 0
00685941 jle 0x685976
00685943 test bl, bl
00685945 jne 0x685976
00685947 mov eax, dword ptr [esi + 0x28]
0068594a sub eax, 0xa
0068594d cmp eax, 0x3dd
00685952 ja 0x685976
00685954 push 0
00685956 push 0xbeab70
0068595b push 0xbeab18
00685960 push 0
00685962 push esi
00685963 call 0x9ec34c
00685968 add esp, 0x14
0068596b test eax, eax
0068596d je 0x685976
0068596f mov ecx, eax
00685971 call 0x680df0
00685976 mov ecx, dword ptr [esp + 0x44]
0068597a pop edi
0068597b pop esi
0068597c pop ebx
0068597d xor ecx, esp
0068597f call 0x9eacd7
00685984 mov esp, ebp
00685986 pop ebp
00685987 ret 0xc
0068598a int3 
0068598b int3 
0068598c int3 
0068598d int3 
0068598e int3 
0068598f int3 
00685990 push ebp
00685991 mov ebp, esp
00685993 and esp, 0xfffffff8
00685996 sub esp, 0x30
00685999 mov eax, dword ptr [0xbaa3b4]
0068599e xor eax, esp
006859a0 mov dword ptr [esp + 0x2c], eax
006859a4 push esi
006859a5 push edi
006859a6 mov edi, dword ptr [ebp + 8]
006859a9 mov esi, ecx
006859ab push edi
006859ac call 0x684b00
006859b1 test al, al
006859b3 jne 0x685ac2
006859b9 push edi
006859ba push dword ptr [ebp + 0xc]
006859bd mov ecx, esi
006859bf call 0x685020
006859c4 mov ecx, esi
006859c6 mov edi, eax
006859c8 call 0x681710
006859cd test al, al
006859cf je 0x6859ec
006859d1 mov ecx, dword ptr [esi + 0x314]
006859d7 test ecx, ecx
006859d9 je 0x6859ec
006859db nop dword ptr [eax + eax]
006859e0 mov esi, ecx
006859e2 mov ecx, dword ptr [esi + 0x314]
006859e8 test ecx, ecx
006859ea jne 0x6859e0
006859ec test edi, edi
006859ee jle 0x685abb
006859f4 cmp dword ptr [esi + 0x224], 0
006859fb jne 0x685abb
00685a01 cmp dword ptr [esi + 0x230], 0
00685a08 jg 0x685abb
00685a0e cmp dword ptr [esi + 0x28], 0xf5
00685a15 jne 0x685a31
00685a17 mov dword ptr [esi + 0x2c], 1
00685a1e pop edi
00685a1f pop esi
00685a20 mov ecx, dword ptr [esp + 0x2c]
00685a24 xor ecx, esp
00685a26 call 0x9eacd7
00685a2b mov esp, ebp
00685a2d pop ebp
00685a2e ret 8
00685a31 push 0
00685a33 push 1
00685a35 mov ecx, esi
00685a37 call 0x4122f0
00685a3c test al, al
00685a3e jne 0x685abb
00685a40 mov eax, dword ptr [esi + 0x164]
00685a46 lea ecx, [esp + 8]
00685a4a or dword ptr [esi + 0x160], 0x420
00685a54 xorps xmm0, xmm0
00685a57 push 1
00685a59 push 0
00685a5b push 0xff
00685a60 mov dword ptr [esi + 0x164], eax
00685a66 mov eax, dword ptr [esi]
00685a68 push edi
00685a69 movups xmmword ptr [esp + 0x28], xmm0
00685a6e push ecx
00685a6f movaps xmm0, xmmword ptr [0xb6c150]
00685a76 mov ecx, esi
00685a78 mov dword ptr [esi + 0x224], edi
00685a7e mov dword ptr [esi + 0x210], edi
00685a84 movups xmmword ptr [esp + 0x1c], xmm0
00685a89 mov dword ptr [esp + 0x3c], 0x3e20a0a1
00685a91 mov dword ptr [esp + 0x40], 0x3e20a0a1
00685a99 mov dword ptr [esp + 0x44], 0x3e20a0a1
00685aa1 call dword ptr [eax + 0x38]
00685aa4 mov eax, dword ptr [esi]
00685aa6 mov ecx, esi
00685aa8 mov eax, dword ptr [eax + 0x48]
00685aab call eax
00685aad test al, al
00685aaf je 0x685abb
00685ab1 mov dword ptr [esi + 0x230], 0xf0
00685abb mov ecx, esi
00685abd call 0x681390
00685ac2 mov ecx, dword ptr [esp + 0x34]
00685ac6 pop edi
00685ac7 pop esi
00685ac8 xor ecx, esp
00685aca call 0x9eacd7
00685acf mov esp, ebp
00685ad1 pop ebp
00685ad2 ret 8
00685ad5 int3 
00685ad6 int3 
00685ad7 int3 
00685ad8 int3 
00685ad9 int3 
00685ada int3 
00685adb int3 
00685adc int3 
00685add int3 
00685ade int3 
00685adf int3 
00685ae0 push ebp
00685ae1 mov ebp, esp
00685ae3 and esp, 0xfffffff8
00685ae6 sub esp, 0x3c
00685ae9 mov eax, dword ptr [0xbaa3b4]
00685aee xor eax, esp
00685af0 mov dword ptr [esp + 0x38], eax
00685af4 push ebx
00685af5 mov ebx, dword ptr [ebp + 8]
00685af8 push esi
00685af9 push edi
00685afa push ebx
00685afb mov esi, ecx
00685afd mov dword ptr [esp + 0x18], ebx
00685b01 call 0x684b00
00685b06 test al, al
00685b08 jne 0x685c89
00685b0e cmp dword ptr [esi + 0x28], 1
00685b12 jne 0x685b2a
00685b14 push 0
00685b16 push 0x278
00685b1b mov ecx, esi
00685b1d call 0x73af30
00685b22 test al, al
00685b24 jne 0x685c89
00685b2a push ebx
00685b2b push dword ptr [ebp + 0xc]
00685b2e mov ecx, esi
00685b30 call 0x685020
00685b35 mov ecx, esi
00685b37 mov ebx, eax
00685b39 call 0x681710
00685b3e test al, al
00685b40 je 0x685b5c
00685b42 mov ecx, dword ptr [esi + 0x314]
00685b48 test ecx, ecx
00685b4a je 0x685b5c
00685b4c nop dword ptr [eax]
00685b50 mov esi, ecx
00685b52 mov ecx, dword ptr [esi + 0x314]
00685b58 test ecx, ecx
00685b5a jne 0x685b50
00685b5c test ebx, ebx
00685b5e je 0x685c89
00685b64 mov eax, dword ptr [esi + 0x160]
00685b6a and eax, 1
00685b6d or eax, 0
00685b70 jne 0x685c89
00685b76 cmp dword ptr [esi + 0x230], eax
00685b7c jg 0x685c89
00685b82 push eax
00685b83 push 0x1000800
00685b88 mov ecx, esi
00685b8a call 0x4122f0
00685b8f mov edi, dword ptr [esi + 0x228]
00685b95 mov byte ptr [esp + 0x13], al
00685b99 test ebx, ebx
00685b9b jle 0x685bac
00685b9d lea ecx, [edi + ebx]
00685ba0 mov edi, 0x78
00685ba5 cmp ecx, edi
00685ba7 cmovl edi, ecx
00685baa jmp 0x685bb3
00685bac neg ebx
00685bae cmp edi, ebx
00685bb0 cmovl edi, ebx
00685bb3 push 1
00685bb5 mov dword ptr [esi + 0x228], edi
00685bbb lea ecx, [esp + 0x1c]
00685bbf movss xmm3, dword ptr [0xb6a480]
00685bc7 movss xmm2, dword ptr [0xb6a2cc]
00685bcf movaps xmm1, xmm3
00685bd2 mov edx, dword ptr [esi]
00685bd4 push 0
00685bd6 push 0xff
00685bdb push edi
00685bdc call 0x427080
00685be1 push eax
00685be2 mov ecx, esi
00685be4 call dword ptr [edx + 0x38]
00685be7 mov eax, dword ptr [esi + 0x164]
00685bed mov ecx, esi
00685bef or dword ptr [esi + 0x160], 0x800
00685bf9 mov dword ptr [esi + 0x164], eax
