00698fb0 push ebx
00698fb1 mov ebx, esp
00698fb3 sub esp, 8
00698fb6 and esp, 0xfffffff8
00698fb9 add esp, 4
00698fbc push ebp
00698fbd mov ebp, dword ptr [ebx + 4]
00698fc0 mov dword ptr [esp + 4], ebp
00698fc4 mov ebp, esp
00698fc6 push -1
00698fc8 push 0x9f478d
00698fcd mov eax, dword ptr fs:[0]
00698fd3 push eax
00698fd4 push ebx
00698fd5 sub esp, 0x68
00698fd8 push esi
00698fd9 push edi
00698fda mov eax, dword ptr [0xbaa3b4]
00698fdf xor eax, ebp
00698fe1 push eax
00698fe2 lea eax, [ebp - 0xc]
00698fe5 mov dword ptr fs:[0], eax
00698feb mov esi, ecx
00698fed mov dword ptr [ebp - 0x18], esi
00698ff0 cmp dword ptr [esi + 0xab4], 0
00698ff7 jne 0x6991a6
00698ffd mov edx, dword ptr [esi + 0x160]
00699003 mov ecx, 9
00699008 mov eax, dword ptr [esi + 0x164]
0069900e and edx, 0xfffffffb
00699011 or edx, 0x11
00699014 mov dword ptr [esi + 0x164], eax
0069901a mov eax, dword ptr [esi + 0x344]
00699020 mov dword ptr [esi + 0x160], edx
00699026 xor edx, edx
00699028 div ecx
0069902a mov eax, dword ptr [esi + 0x2c]
0069902d inc edx
0069902e mov dword ptr [esi + 0x180], 1
00699038 mov dword ptr [esi + 0x17c], 0
00699042 mov dword ptr [esi + 0x30], edx
00699045 cmp eax, 4
00699048 ja 0x699093
0069904a jmp dword ptr [eax*4 + 0x6994d0]
00699051 push edx
00699052 push 0xb49000
00699057 push 0x40
00699059 push 0xc05de0
0069905e call 0x418980
00699063 add esp, 0x10
00699066 jmp 0x699093
00699068 push edx
00699069 push 0xb49010
0069906e push 0x40
00699070 push 0xc05de0
00699075 call 0x418980
0069907a add esp, 0x10
0069907d jmp 0x699093
0069907f push 0xb3fd8c
00699084 push 0x40
00699086 push 0xc05de0
0069908b call 0x418980
00699090 add esp, 0xc
00699093 lea edi, [esi + 0x3c]
00699096 mov esi, dword ptr [edi + 0x34]
00699099 test esi, esi
0069909b je 0x6990e3
0069909d cmp dword ptr [esi + 0x14], 0x10
006990a1 mov eax, esi
006990a3 jb 0x6990a7
006990a5 mov eax, dword ptr [esi]
006990a7 mov ecx, 0xc05de0
006990ac nop dword ptr [eax]
006990b0 mov dl, byte ptr [eax]
006990b2 cmp dl, byte ptr [ecx]
006990b4 jne 0x6990d0
006990b6 test dl, dl
006990b8 je 0x6990cc
006990ba mov dl, byte ptr [eax + 1]
006990bd cmp dl, byte ptr [ecx + 1]
006990c0 jne 0x6990d0
006990c2 add eax, 2
006990c5 add ecx, 2
006990c8 test dl, dl
006990ca jne 0x6990b0
006990cc xor eax, eax
006990ce jmp 0x6990d5
006990d0 sbb eax, eax
006990d2 or eax, 1
006990d5 test eax, eax
006990d7 jne 0x6990e3
006990d9 cmp byte ptr [esi + 0x34], al
006990dc je 0x699101
006990de cmp byte ptr [edi + 0x44], al
006990e1 jne 0x699101
006990e3 push 1
006990e5 push 0xc05de0
006990ea mov ecx, edi
006990ec call 0x405740
006990f1 test al, al
006990f3 je 0x699101
006990f5 lea ecx, [edi + 0x30]
006990f8 call 0x405330
006990fd mov byte ptr [edi + 0x44], 1
00699101 mov esi, dword ptr [ebp - 0x18]
00699104 lea eax, [ebp - 0x74]
00699107 movaps xmm2, xmmword ptr [0xb6c060]
0069910e xorps xmm1, xmm1
00699111 mov dword ptr [ebp - 0x54], 0x3e4ccccd
00699118 mov dword ptr [ebp - 0x50], 0x3e4ccccd
0069911f lea ecx, [esi + 0x1dc]
00699125 mov dword ptr [ebp - 0x4c], 0x3e4ccccd
0069912c cmp ecx, eax
0069912e je 0x699147
00699130 movq xmm0, qword ptr [ebp - 0x54]
00699135 mov eax, dword ptr [ebp - 0x4c]
00699138 movq qword ptr [ecx + 0x20], xmm0
0069913d movups xmmword ptr [ecx], xmm2
00699140 mov dword ptr [ecx + 0x28], eax
00699143 movups xmmword ptr [ecx + 0x10], xmm1
00699147 mov eax, dword ptr [esi + 0x2c]
0069914a test eax, eax
0069914c je 0x699158
0069914e cmp eax, 3
00699151 je 0x699158
00699153 cmp eax, 2
00699156 jne 0x69917d
00699158 mov eax, dword ptr [0xbfd65c]
0069915d mov eax, dword ptr [eax + 0x18190]
00699163 cmp dword ptr [eax + 8], 0x10
00699167 jne 0x69917d
00699169 mov dword ptr [esi + 0xd0], 0
00699173 mov dword ptr [esi + 0xd4], 0x41000000
0069917d mov eax, dword ptr [esi + 0x294]
00699183 mov ecx, esi
00699185 mov dword ptr [esi + 0x28c], eax
0069918b mov eax, dword ptr [esi + 0x298]
00699191 mov dword ptr [esi + 0x290], eax
00699197 mov dword ptr [esi + 0xab4], 3
006991a1 call 0x6b1270
006991a6 cmp byte ptr [esi + 0x16b], 0
006991ad lea ecx, [esi + 0x294]
006991b3 movss xmm0, dword ptr [esi + 0x2c4]
006991bb mov eax, dword ptr [esi + 0x28c]
006991c1 mulss xmm0, dword ptr [0xb6a560]
006991c9 mov dword ptr [ecx], eax
006991cb mov eax, dword ptr [esi + 0x290]
006991d1 mov dword ptr [ebp - 0x20], ecx
006991d4 mov dword ptr [ecx + 4], eax
006991d7 movss dword ptr [esi + 0x2c4], xmm0
006991df je 0x6994b9
006991e5 mov ecx, dword ptr [0xbfd680]
006991eb push 1
006991ed push 0xc
006991ef lea ecx, [ecx + 0x14]
006991f2 call 0x884e40
006991f7 mov ecx, dword ptr [0xbfd65c]
006991fd push 1
006991ff mov eax, dword ptr [ecx + 0x1c316c]
00699205 or dword ptr [ecx + 0x1c3168], 0x80000000
0069920f mov dword ptr [ecx + 0x1c316c], eax
00699215 lea eax, [ebp - 0x48]
00699218 or dword ptr [ecx + 0x1822c], 0x40
0069921f mov ecx, esi
00699221 push eax
00699222 call 0x698850
00699227 mov dword ptr [ebp - 4], 0
0069922e mov edx, dword ptr [ebp - 0x3c]
00699231 mov edi, edx
00699233 mov eax, dword ptr [ebp - 0x48]
00699236 mov dword ptr [ebp - 0x24], edx
00699239 mov dword ptr [ebp - 0x1c], eax
0069923c nop dword ptr [eax]
00699240 mov ecx, dword ptr [ebp - 0x38]
00699243 lea eax, [ecx + edx]
00699246 cmp edi, eax
00699248 je 0x69947f
0069924e mov eax, dword ptr [ebp - 0x1c]
00699251 test eax, eax
00699253 je 0x699259
00699255 mov eax, dword ptr [eax]
00699257 jmp 0x69925b
00699259 xor eax, eax
0069925b mov ecx, dword ptr [eax + 8]
0069925e mov eax, dword ptr [eax + 4]
00699261 dec ecx
00699262 and ecx, edi
00699264 mov eax, dword ptr [eax + ecx*4]
00699267 cmp dword ptr [eax], 0x55
0069926a jne 0x6992f3
00699270 lea eax, [esi + 0x294]
00699276 cmp edi, edx
00699278 jne 0x6992c7
0069927a push 0
0069927c push 0
0069927e push ecx
0069927f mov ecx, dword ptr [0xbfd65c]
00699285 mov dword ptr [esp], 0x428c0000
0069928c push eax
0069928d lea eax, [ebp - 0x34]
00699290 mov ecx, dword ptr [ecx + 0x18190]
00699296 push eax
00699297 call 0x7cf240
0069929c push ecx
0069929d mov dword ptr [esp], 0xc1f00000
006992a4 push 0
006992a6 push dword ptr [eax + 4]
006992a9 push dword ptr [eax]
006992ab lea eax, [esi + 0x294]
006992b1 push esi
006992b2 push eax
006992b3 call 0x6994f0
006992b8 mov edx, dword ptr [ebp - 0x3c]
006992bb add esp, 0x18
006992be inc edi
006992bf mov dword ptr [ebp - 0x24], edi
006992c2 jmp 0x699240
006992c7 push ecx
006992c8 mov dword ptr [esp], 0xc1f00000
006992cf push 0
006992d1 push dword ptr [0xc02ff0]
006992d7 push dword ptr [0xc02fec]
006992dd push esi
006992de push eax
006992df call 0x6994f0
006992e4 mov edx, dword ptr [ebp - 0x3c]
006992e7 add esp, 0x18
006992ea inc edi
006992eb mov dword ptr [ebp - 0x24], edi
006992ee jmp 0x699240
006992f3 mov eax, dword ptr [ebp - 0x1c]
006992f6 test eax, eax
006992f8 je 0x6992fe
006992fa mov eax, dword ptr [eax]
006992fc jmp 0x699300
006992fe xor eax, eax
00699300 mov ecx, dword ptr [eax + 8]
00699303 mov eax, dword ptr [eax + 4]
00699306 dec ecx
00699307 push 0
00699309 and ecx, edi
0069930b push 0xc02fec
00699310 push dword ptr [ebp - 0x20]
00699313 mov ecx, dword ptr [eax + ecx*4]
00699316 call 0x7f86d0
0069931b mov esi, eax
0069931d mov eax, dword ptr [esi + 0x28]
00699320 cmp eax, 0x32
00699323 jne 0x699432
00699329 mov ecx, dword ptr [0xbfd65c]
0069932f mov eax, dword ptr [esi]
00699331 mov edi, dword ptr [ecx + 0x18190]
00699337 mov ecx, esi
00699339 mov eax, dword ptr [eax + 0x44]
0069933c call eax
0069933e test al, al
00699340 je 0x699364
00699342 cmp dword ptr [esi + 0x28], 0x362
00699349 je 0x699364
0069934b inc dword ptr [edi + 0x12c0]
00699351 mov ecx, esi
00699353 mov eax, dword ptr [esi]
00699355 mov eax, dword ptr [eax + 0x48]
00699358 call eax
0069935a test al, al
0069935c je 0x699364
0069935e inc dword ptr [edi + 0x12c8]
00699364 mov eax, dword ptr [esi]
00699366 mov ecx, esi
00699368 call dword ptr [eax + 0xc]
0069936b mov ecx, dword ptr [0xbfd65c]
00699371 mov ecx, dword ptr [ecx + 0x18190]
00699377 call 0x7aa960
0069937c mov eax, dword ptr [0xbfd65c]
00699381 mov edi, 0x724
00699386 mov eax, dword ptr [eax + 0x18190]
0069938c mov byte ptr [eax + 0x711c], 1
00699393 xor eax, eax
00699395 inc eax
00699396 mov dword ptr [ebp - 0x14], eax
00699399 cmp eax, 8
0069939c ja 0x699403
0069939e mov eax, dword ptr [0xbfd65c]
006993a3 mov eax, dword ptr [eax + 0x18190]
006993a9 mov esi, dword ptr [edi + eax]
006993ac test esi, esi
006993ae je 0x699400
006993b0 cmp dword ptr [esi + 0xc], 1
006993b4 je 0x699400
006993b6 mov ecx, esi
006993b8 mov dword ptr [esi + 0xc], 1
006993bf call 0x6df520
006993c4 mov ecx, dword ptr [esi + 0x158]
006993ca cmp ecx, 7
006993cd je 0x6993ee
006993cf mov eax, dword ptr [esi + 0x15c]
006993d5 cmp eax, 7
006993d8 je 0x6993ee
006993da cmp ecx, 8
006993dd je 0x6993ee
006993df cmp eax, 8
006993e2 je 0x6993ee
006993e4 cmp ecx, 0x1d
006993e7 je 0x6993ee
006993e9 cmp eax, 0x1d
006993ec jne 0x699400
006993ee push 4
006993f0 push 0xb41d80
006993f5 lea ecx, [esi + 0x28c]
006993fb call 0x407c80
00699400 mov eax, dword ptr [ebp - 0x14]
00699403 add edi, 4
00699406 cmp edi, 0x744
0069940c jl 0x699395
0069940e mov eax, dword ptr [0xbfd65c]
00699413 mov edi, dword ptr [ebp - 0x24]
00699416 mov esi, dword ptr [ebp - 0x18]
00699419 mov eax, dword ptr [eax + 0x18190]
0069941f mov eax, dword ptr [eax + 4]
00699422 and dword ptr [eax + 0x44], 0xfffffffe
00699426 inc edi
00699427 mov edx, dword ptr [ebp - 0x3c]
0069942a mov dword ptr [ebp - 0x24], edi
0069942d jmp 0x699240
00699432 cmp dword ptr [ebp - 0x38], 1
00699436 jbe 0x699469
00699438 cmp eax, 5
0069943b jne 0x699469
0069943d mov edx, dword ptr [ebp - 0x20]
00699440 lea ecx, [ebp - 0x2c]
00699443 push 0
00699445 push 0
00699447 call 0x6c3450
0069944c movss xmm0, dword ptr [ebp - 0x2c]
00699451 add esp, 8
00699454 movss dword ptr [esi + 0x2b8], xmm0
0069945c movss xmm0, dword ptr [ebp - 0x28]
00699461 movss dword ptr [esi + 0x2bc], xmm0
00699469 mov eax, dword ptr [esi]
0069946b mov ecx, esi
0069946d call dword ptr [eax + 0xc]
00699470 mov esi, dword ptr [ebp - 0x18]
00699473 inc edi
00699474 mov edx, dword ptr [ebp - 0x3c]
00699477 mov dword ptr [ebp - 0x24], edi
0069947a jmp 0x699240
0069947f test ecx, ecx
00699481 je 0x699495
00699483 mov eax, dword ptr [0xbfd65c]
00699488 mov eax, dword ptr [eax + 0x18190]
0069948e mov byte ptr [eax + 0x7778], 1
00699495 mov ecx, esi
00699497 call 0x6b1270
0069949c lea ecx, [ebp - 0x48]
0069949f call 0x6b15c0
006994a4 mov eax, dword ptr [ebp - 0x48]
006994a7 push 8
006994a9 push eax
006994aa mov dword ptr [ebp - 0x48], 0
006994b1 call 0x9eb08e
006994b6 add esp, 8
006994b9 mov ecx, dword ptr [ebp - 0xc]
006994bc mov dword ptr fs:[0], ecx
006994c3 pop ecx
006994c4 pop edi
006994c5 pop esi
006994c6 mov esp, ebp
006994c8 pop ebp
006994c9 mov esp, ebx
006994cb pop ebx
006994cc ret
