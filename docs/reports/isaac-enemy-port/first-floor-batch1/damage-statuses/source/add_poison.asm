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
