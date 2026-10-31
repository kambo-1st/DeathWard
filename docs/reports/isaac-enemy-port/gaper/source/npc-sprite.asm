00692080 push ebx
00692081 mov ebx, esp
00692083 sub esp, 8
00692086 and esp, 0xfffffff8
00692089 add esp, 4
0069208c push ebp
0069208d mov ebp, dword ptr [ebx + 4]
00692090 mov dword ptr [esp + 4], ebp
00692094 mov ebp, esp
00692096 push -1
00692098 push 0x9f45bf
0069209d mov eax, dword ptr fs:[0]
006920a3 push eax
006920a4 push ebx
006920a5 sub esp, 0xf8
006920ab mov eax, dword ptr [0xbaa3b4]
006920b0 xor eax, ebp
006920b2 mov dword ptr [ebp - 0x14], eax
006920b5 push esi
006920b6 push edi
006920b7 push eax
006920b8 lea eax, [ebp - 0xc]
006920bb mov dword ptr fs:[0], eax
006920c1 mov edi, ecx
006920c3 mov dword ptr [ebp - 0xa8], edi
006920c9 xor esi, esi
006920cb cmp byte ptr [ebx + 8], 0
006920cf mov dword ptr [ebp - 0x98], esi
006920d5 je 0x692256
006920db mov eax, dword ptr [edi + 0xbc8]
006920e1 test eax, eax
006920e3 js 0x69212c
006920e5 mov eax, dword ptr [edi + 0x288]
006920eb mov edx, dword ptr [eax + 0x68]
006920ee mov ecx, dword ptr [eax + 0x6c]
006920f1 mov eax, 0x84210843
006920f6 sub ecx, edx
006920f8 mov dword ptr [ebp - 0x9c], edx
006920fe imul ecx
00692100 add edx, ecx
00692102 mov ecx, dword ptr [edi + 0xbc8]
00692108 sar edx, 6
0069210b mov eax, edx
0069210d shr eax, 0x1f
00692110 add eax, edx
00692112 cmp ecx, eax
00692114 jge 0x69212c
00692116 mov eax, dword ptr [ebp - 0x9c]
0069211c imul ecx, ecx, 0x7c
0069211f cmp dword ptr [ecx + eax + 0x54], esi
00692123 je 0x69212c
00692125 add eax, 0x44
00692128 add eax, ecx
0069212a jmp 0x692135
0069212c mov eax, dword ptr [edi + 0x288]
00692132 add eax, 0x74
00692135 push 0
00692137 lea ecx, [edi + 0x3c]
0069213a push eax
0069213b call 0x407160
00692140 mov ecx, dword ptr [0xbfd65c]
00692146 add ecx, 0x1bb58
0069214c mov dword ptr [ebp - 0x9c], 0x4f
00692156 mov eax, dword ptr [ecx]
00692158 mov dword ptr [ebp - 0x98], eax
0069215e lea eax, [ebp - 0x9c]
00692164 push eax
00692165 lea eax, [ebp - 0x38]
00692168 push eax
00692169 call 0x4206b0
0069216e mov eax, dword ptr [ebp - 0x30]
00692171 cmp byte ptr [eax + 0xd], 0
00692175 jne 0x692256
0069217b cmp dword ptr [eax + 0x10], 0x4f
0069217f jg 0x692256
00692185 cmp eax, dword ptr [ebp - 0x98]
0069218b je 0x692256
00692191 cmp dword ptr [edi + 0x28], 0x66
00692195 jne 0x692256
0069219b cmp dword ptr [edi + 0x2c], 1
0069219f jne 0x692256
006921a5 mov dword ptr [ebp - 0x44], esi
006921a8 push 0x40
006921aa mov dword ptr [ebp - 0x34], esi
006921ad mov dword ptr [ebp - 0x30], 0xf
006921b4 mov byte ptr [ebp - 0x44], 0
006921b8 call 0x407de0
006921bd movups xmm0, xmmword ptr [0xb4902c]
006921c4 mov ecx, eax
006921c6 mov dword ptr [ebp - 0x34], 0x35
006921cd mov dword ptr [ebp - 0x30], 0x3f
006921d4 movups xmmword ptr [ecx], xmm0
006921d7 movups xmm0, xmmword ptr [0xb4903c]
006921de movups xmmword ptr [ecx + 0x10], xmm0
006921e2 movups xmm0, xmmword ptr [0xb4904c]
006921e9 movups xmmword ptr [ecx + 0x20], xmm0
006921ed mov eax, dword ptr [0xb4905c]
006921f2 mov dword ptr [ecx + 0x30], eax
006921f5 mov al, byte ptr [0xb49060]
006921fa mov byte ptr [ecx + 0x34], al
006921fd mov byte ptr [ecx + 0x35], 0
00692201 mov dword ptr [ebp - 0x44], ecx
00692204 push 1
00692206 lea eax, [ebp - 0x44]
00692209 mov dword ptr [ebp - 4], 0
00692210 push eax
00692211 lea ecx, [edi + 0x3c]
00692214 call 0x407160
00692219 mov dword ptr [ebp - 4], 0xffffffff
00692220 mov edx, dword ptr [ebp - 0x30]
00692223 cmp edx, 0x10
00692226 jb 0x692256
00692228 mov ecx, dword ptr [ebp - 0x44]
0069222b inc edx
0069222c mov eax, ecx
0069222e cmp edx, 0x1000
00692234 jb 0x69224c
00692236 mov ecx, dword ptr [ecx - 4]
00692239 add edx, 0x23
0069223c sub eax, ecx
0069223e add eax, -4
00692241 cmp eax, 0x1f
00692244 jbe 0x69224c
00692246 call dword ptr [0xa065ac]
0069224c push edx
0069224d push ecx
0069224e call 0x9eb08e
00692253 add esp, 8
00692256 mov dword ptr [ebp - 0x5c], 0
0069225d mov dword ptr [ebp - 0x4c], 0
00692264 mov dword ptr [ebp - 0x48], 0xf
0069226b mov byte ptr [ebp - 0x5c], 0
0069226f mov dword ptr [ebp - 4], 1
00692276 mov eax, dword ptr [edi + 0xbc8]
0069227c test eax, eax
0069227e js 0x6922dc
00692280 mov ecx, dword ptr [edi + 0x288]
00692286 mov eax, dword ptr [ecx + 0x68]
00692289 mov ecx, dword ptr [ecx + 0x6c]
0069228c sub ecx, eax
0069228e mov dword ptr [ebp - 0x9c], eax
00692294 mov eax, 0x84210843
00692299 imul ecx
0069229b add edx, ecx
0069229d mov ecx, dword ptr [edi + 0xbc8]
006922a3 sar edx, 6
006922a6 mov eax, edx
006922a8 shr eax, 0x1f
006922ab add eax, edx
006922ad cmp ecx, eax
006922af jge 0x6922dc
006922b1 imul eax, ecx, 0x7c
006922b4 lea ecx, [ebp - 0x5c]
006922b7 add eax, 0x2c
006922ba add eax, dword ptr [ebp - 0x9c]
006922c0 cmp ecx, eax
006922c2 je 0x692324
006922c4 cmp dword ptr [eax + 0x14], 0x10
006922c8 mov ecx, eax
006922ca jb 0x6922ce
006922cc mov ecx, dword ptr [eax]
006922ce push dword ptr [eax + 0x10]
006922d1 push ecx
006922d2 lea ecx, [ebp - 0x5c]
006922d5 call 0x407c80
006922da jmp 0x692324
006922dc mov eax, dword ptr [edi + 0x288]
006922e2 cmp byte ptr [eax + 0xcd], 0
006922e9 je 0x692324
006922eb call 0x690cc0
006922f0 mov ecx, dword ptr [0xbfd65c]
006922f6 imul eax, eax, 0xc4
006922fc add ecx, 0x187e8
00692302 add eax, ecx
00692304 lea ecx, [ebp - 0x74]
00692307 push eax
00692308 call 0x4079f0
0069230d movups xmm0, xmmword ptr [ebp - 0x74]
00692311 mov esi, 4
00692316 movups xmmword ptr [ebp - 0x5c], xmm0
0069231a movq xmm0, qword ptr [ebp - 0x64]
0069231f movq qword ptr [ebp - 0x4c], xmm0
00692324 xor al, al
00692326 xorps xmm1, xmm1
00692329 mov byte ptr [ebp - 0x8e], al
0069232f mov byte ptr [ebp - 0x8f], al
00692335 cmp byte ptr [edi + 0xbb3], al
0069233b je 0x69236d
0069233d mov ecx, dword ptr [edi + 0xbb4]
00692343 test ecx, ecx
00692345 js 0x69236d
00692347 mov eax, ecx
00692349 shl eax, 4
0069234c sub eax, ecx
0069234e lea ecx, [eax*4 + 0xbc5700]
00692355 mov dword ptr [ebp - 0x9c], ecx
0069235b test ecx, ecx
0069235d je 0x692377
0069235f movss xmm0, dword ptr [ecx + 0xc]
00692364 comiss xmm0, xmm1
00692367 jbe 0x692377
00692369 mov al, 1
0069236b jmp 0x692379
0069236d mov dword ptr [ebp - 0x9c], 0
00692377 xor al, al
00692379 test al, al
0069237b mov dword ptr [ebp - 0x74], 0
00692382 mov ecx, 0xa081d4
00692387 mov dword ptr [ebp - 0x64], 0
0069238e mov edx, 0xb49020
00692393 mov dword ptr [ebp - 0x60], 0xf
0069239a cmove edx, ecx
0069239d mov byte ptr [ebp - 0x74], 0
006923a1 mov ecx, edx
006923a3 lea eax, [ecx + 1]
006923a6 mov dword ptr [ebp - 0x98], eax
006923ac nop dword ptr [eax]
006923b0 mov al, byte ptr [ecx]
006923b2 inc ecx
006923b3 test al, al
006923b5 jne 0x6923b0
006923b7 sub ecx, dword ptr [ebp - 0x98]
006923bd push ecx
006923be push edx
006923bf lea ecx, [ebp - 0x74]
006923c2 call 0x407c80
006923c7 xor ecx, ecx
006923c9 mov byte ptr [ebp - 4], 2
006923cd mov dword ptr [ebp - 0xa4], ecx
006923d3 cmp dword ptr [edi + 0xbc], ecx
006923d9 jbe 0x69283b
006923df add edi, 0x3c
006923e2 xor eax, eax
006923e4 mov dword ptr [ebp - 0xac], edi
006923ea mov dword ptr [ebp - 0xa0], eax
006923f0 jmp 0x6923f8
006923f2 mov edi, dword ptr [ebp - 0xac]
006923f8 test ecx, ecx
006923fa js 0x692404
006923fc cmp ecx, dword ptr [edi + 0x80]
00692402 jl 0x692425
00692404 cmp dword ptr [edi + 0x14], 0x10
00692408 mov eax, edi
0069240a jb 0x69240e
0069240c mov eax, dword ptr [edi]
0069240e push ecx
0069240f push eax
00692410 push 0xa0830c
00692415 push 3
00692417 call 0x95e330
0069241c mov eax, dword ptr [ebp - 0xa0]
00692422 add esp, 0x10
00692425 mov edi, dword ptr [edi + 0x7c]
00692428 or esi, 8
0069242b add edi, eax
0069242d mov eax, dword ptr [edi]
0069242f test eax, eax
00692431 je 0x692447
00692433 add eax, 8
00692436 lea ecx, [ebp - 0x2c]
00692439 push eax
0069243a call 0x4079f0
0069243f mov edx, dword ptr [ebp - 0x1c]
00692442 mov eax, dword ptr [ebp - 0x18]
00692445 jmp 0x69245e
00692447 xor edx, edx
00692449 mov dword ptr [ebp - 0x2c], 0
00692450 mov eax, 0xf
00692455 mov dword ptr [ebp - 0x1c], edx
00692458 mov dword ptr [ebp - 0x18], eax
0069245b mov byte ptr [ebp - 0x2c], dl
0069245e or esi, 1
00692461 mov byte ptr [ebp - 4], 3
00692465 cmp eax, 0x10
00692468 mov dword ptr [ebp - 0x94], esi
0069246e mov eax, dword ptr [ebp - 0x2c]
00692471 lea ecx, [ebp - 0x2c]
00692474 push 4
00692476 cmovae ecx, eax
00692479 mov dword ptr [ebp - 0x98], esi
0069247f push 0xb4631c
00692484 mov dword ptr [ebp - 0xb0], eax
0069248a call 0x408190
0069248f add esp, 8
00692492 test al, al
00692494 jne 0x692507
00692496 mov eax, dword ptr [edi]
00692498 or esi, 0x10
0069249b test eax, eax
0069249d je 0x6924bc
0069249f add eax, 8
006924a2 lea ecx, [ebp - 0x44]
006924a5 push eax
006924a6 call 0x4079f0
006924ab mov eax, dword ptr [ebp - 0x44]
006924ae mov edx, dword ptr [ebp - 0x34]
006924b1 mov dword ptr [ebp - 0x98], eax
006924b7 mov eax, dword ptr [ebp - 0x30]
006924ba jmp 0x6924d4
006924bc xor eax, eax
006924be xor edx, edx
006924c0 mov dword ptr [ebp - 0x98], eax
006924c6 mov dword ptr [ebp - 0x44], eax
006924c9 mov eax, 0xf
006924ce mov dword ptr [ebp - 0x30], eax
006924d1 mov dword ptr [ebp - 0x34], edx
006924d4 or esi, 2
006924d7 lea ecx, [ebp - 0x44]
006924da cmp eax, 0x10
006924dd mov dword ptr [ebp - 0x94], esi
006924e3 mov esi, dword ptr [ebp - 0x98]
006924e9 push 4
006924eb cmovae ecx, esi
006924ee push 0xb40368
006924f3 call 0x408190
006924f8 add esp, 8
006924fb test al, al
006924fd jne 0x69250a
006924ff mov byte ptr [ebp - 0x8d], al
00692505 jmp 0x692511
00692507 mov esi, dword ptr [ebp - 0x44]
0069250a mov byte ptr [ebp - 0x8d], 1
00692511 mov eax, dword ptr [ebp - 0x94]
00692517 test al, 2
00692519 je 0x69255b
0069251b mov ecx, dword ptr [ebp - 0x30]
0069251e and eax, 0xfffffffd
00692521 mov dword ptr [ebp - 0x94], eax
00692527 cmp ecx, 0x10
0069252a jb 0x69255b
0069252c inc ecx
0069252d mov eax, esi
0069252f cmp ecx, 0x1000
00692535 jb 0x69254b
00692537 mov esi, dword ptr [esi - 4]
0069253a add ecx, 0x23
0069253d sub eax, esi
0069253f add eax, -4
00692542 cmp eax, 0x1f
00692545 ja 0x692924
0069254b push ecx
0069254c push esi
0069254d call 0x9eb08e
00692552 mov eax, dword ptr [ebp - 0x94]
00692558 add esp, 8
0069255b mov dword ptr [ebp - 4], 2
00692562 test al, 1
00692564 je 0x6925ac
00692566 mov ecx, dword ptr [ebp - 0x18]
00692569 and eax, 0xfffffffe
0069256c mov dword ptr [ebp - 0x94], eax
00692572 cmp ecx, 0x10
00692575 jb 0x6925ac
00692577 mov edx, dword ptr [ebp - 0xb0]
0069257d inc ecx
0069257e mov eax, edx
00692580 cmp ecx, 0x1000
00692586 jb 0x69259c
00692588 mov edx, dword ptr [edx - 4]
0069258b add ecx, 0x23
0069258e sub eax, edx
00692590 add eax, -4
00692593 cmp eax, 0x1f
00692596 ja 0x692924
0069259c push ecx
0069259d push edx
0069259e call 0x9eb08e
006925a3 mov eax, dword ptr [ebp - 0x94]
006925a9 add esp, 8
006925ac cmp byte ptr [ebp - 0x8d], 0
006925b3 je 0x6925c3
006925b5 or dword ptr [edi + 0x88], 1
006925bc mov byte ptr [ebp - 0x8f], 1
006925c3 mov ecx, dword ptr [edi]
006925c5 or eax, 0x20
006925c8 mov dword ptr [ebp - 0x94], eax
006925ce test ecx, ecx
006925d0 je 0x6925e6
006925d2 lea eax, [ecx + 8]
006925d5 push eax
006925d6 lea ecx, [ebp - 0x2c]
006925d9 call 0x4079f0
006925de mov edx, dword ptr [ebp - 0x1c]
006925e1 mov esi, dword ptr [ebp - 0x2c]
006925e4 jmp 0x6925fd
006925e6 xor esi, esi
006925e8 mov dword ptr [ebp - 0x18], 0xf
006925ef xor edx, edx
006925f1 mov dword ptr [ebp - 0x2c], esi
006925f4 mov dword ptr [ebp - 0x1c], edx
006925f7 mov dword ptr [ebp - 0x94], eax
006925fd cmp dword ptr [ebp - 0x18], 0x10
00692601 lea ecx, [ebp - 0x2c]
00692604 push 5
00692606 cmovae ecx, esi
00692609 push 0xb49064
0069260e call 0x408190
00692613 mov byte ptr [ebp - 0x8d], al
00692619 add esp, 8
0069261c mov eax, dword ptr [ebp - 0x18]
0069261f cmp eax, 0x10
00692622 jb 0x69264f
00692624 lea ecx, [eax + 1]
00692627 mov eax, esi
00692629 cmp ecx, 0x1000
0069262f jb 0x692645
00692631 mov esi, dword ptr [esi - 4]
00692634 add ecx, 0x23
00692637 sub eax, esi
00692639 add eax, -4
0069263c cmp eax, 0x1f
0069263f ja 0x692924
00692645 push ecx
00692646 push esi
00692647 call 0x9eb08e
0069264c add esp, 8
0069264f cmp byte ptr [ebp - 0x8d], 0
00692656 je 0x69265f
00692658 or dword ptr [edi + 0x88], 1
0069265f mov esi, dword ptr [ebp - 0x94]
00692665 mov eax, dword ptr [edi]
00692667 or esi, 0x40
0069266a mov byte ptr [ebp - 0x8d], 0
00692671 test eax, eax
00692673 je 0x692683
00692675 add eax, 0x20
00692678 lea ecx, [ebp - 0x2c]
0069267b push eax
0069267c call 0x4079f0
00692681 jmp 0x69269c
00692683 mov dword ptr [ebp - 0x2c], 0
0069268a mov dword ptr [ebp - 0x18], 0xf
00692691 mov dword ptr [ebp - 0x1c], 0
00692698 mov byte ptr [ebp - 0x2c], 0
0069269c lea eax, [ebp - 0x8d]
006926a2 mov byte ptr [ebp - 4], 4
006926a6 push eax
006926a7 lea eax, [ebp - 0x74]
006926aa push eax
006926ab lea eax, [ebp - 0x5c]
006926ae push eax
006926af lea edx, [ebp - 0x2c]
006926b2 lea ecx, [ebp - 0x8c]
006926b8 call 0x690d20
006926bd add esp, 0xc
006926c0 mov byte ptr [ebp - 4], 6
006926c4 mov edx, dword ptr [ebp - 0x18]
006926c7 cmp edx, 0x10
006926ca jb 0x6926f8
006926cc mov ecx, dword ptr [ebp - 0x2c]
006926cf inc edx
006926d0 mov eax, ecx
006926d2 cmp edx, 0x1000
006926d8 jb 0x6926ee
006926da mov ecx, dword ptr [ecx - 4]
006926dd add edx, 0x23
006926e0 sub eax, ecx
006926e2 add eax, -4
006926e5 cmp eax, 0x1f
006926e8 ja 0x692924
006926ee push edx
006926ef push ecx
006926f0 call 0x9eb08e
006926f5 add esp, 8
006926f8 mov ecx, dword ptr [ebp - 0xa4]
006926fe test ecx, ecx
00692700 js 0x692758
00692702 mov eax, dword ptr [ebp - 0xa8]
00692708 cmp ecx, dword ptr [eax + 0xbc]
0069270e jge 0x692758
00692710 mov ecx, dword ptr [ebp - 0xa0]
00692716 lea edx, [ebp - 0x8c]
0069271c mov eax, dword ptr [eax + 0xb8]
00692722 add ecx, 8
00692725 add ecx, eax
00692727 cmp ecx, edx
00692729 je 0x69274d
0069272b cmp dword ptr [ebp - 0x78], 0x10
0069272f mov eax, edx
00692731 push dword ptr [ebp - 0x7c]
00692734 cmovae eax, dword ptr [ebp - 0x8c]
0069273b push eax
0069273c call 0x407c80
00692741 mov ecx, dword ptr [ebp - 0xa8]
00692747 mov eax, dword ptr [ecx + 0xb8]
0069274d mov ecx, dword ptr [ebp - 0xa0]
00692753 mov byte ptr [ecx + eax + 0x30], 0
00692758 cmp byte ptr [ebp - 0x8d], 0
0069275f mov eax, dword ptr [edi + 0x88]
00692765 je 0x692773
00692767 mov byte ptr [ebp - 0x8e], 1
0069276e or eax, 0x10
00692771 jmp 0x692776
00692773 and eax, 0xffffffef
00692776 mov byte ptr [ebp - 4], 2
0069277a mov edx, dword ptr [ebp - 0x78]
0069277d mov dword ptr [edi + 0x88], eax
00692783 cmp edx, 0x10
00692786 jb 0x6927b7
00692788 mov ecx, dword ptr [ebp - 0x8c]
0069278e inc edx
0069278f mov eax, ecx
00692791 cmp edx, 0x1000
00692797 jb 0x6927ad
00692799 mov ecx, dword ptr [ecx - 4]
0069279c add edx, 0x23
0069279f sub eax, ecx
006927a1 add eax, -4
006927a4 cmp eax, 0x1f
006927a7 ja 0x692924
006927ad push edx
006927ae push ecx
006927af call 0x9eb08e
006927b4 add esp, 8
006927b7 mov ecx, dword ptr [ebp - 0xa4]
006927bd mov edi, dword ptr [ebp - 0xa8]
006927c3 inc ecx
006927c4 mov eax, dword ptr [ebp - 0xa0]
006927ca add eax, 0x9c
006927cf mov dword ptr [ebp - 0xa4], ecx
006927d5 mov dword ptr [ebp - 0xa0], eax
006927db cmp ecx, dword ptr [edi + 0xbc]
006927e1 jb 0x6923f2
006927e7 cmp byte ptr [ebp - 0x8e], 0
006927ee je 0x69283b
006927f0 mov eax, dword ptr [ebp - 0x9c]
006927f6 test eax, eax
006927f8 je 0x69283b
006927fa push eax
006927fb lea ecx, [ebp - 0xdc]
00692801 call 0x439500
00692806 lea ecx, [edi + 0x110]
0069280c lea eax, [ebp - 0xdc]
00692812 cmp ecx, eax
00692814 je 0x69288c
00692816 movups xmm0, xmmword ptr [ebp - 0xdc]
0069281d mov eax, dword ptr [ebp - 0xb4]
00692823 movups xmmword ptr [ecx], xmm0
00692826 movups xmm0, xmmword ptr [ebp - 0xcc]
0069282d movups xmmword ptr [ecx + 0x10], xmm0
00692831 movq xmm0, qword ptr [ebp - 0xbc]
00692839 jmp 0x692884
0069283b lea ecx, [edi + 0x110]
00692841 mov dword ptr [ebp - 0xe8], 0
0069284b lea eax, [ebp - 0x108]
00692851 mov dword ptr [ebp - 0xe4], 0
0069285b mov dword ptr [ebp - 0xe0], 0
00692865 xorps xmm0, xmm0
00692868 xorps xmm1, xmm1
0069286b cmp ecx, eax
0069286d je 0x69288c
0069286f mov eax, dword ptr [ebp - 0xe0]
00692875 movups xmmword ptr [ecx + 0x10], xmm0
00692879 movq xmm0, qword ptr [ebp - 0xe8]
00692881 movups xmmword ptr [ecx], xmm1
00692884 movq qword ptr [ecx + 0x20], xmm0
00692889 mov dword ptr [ecx + 0x28], eax
0069288c mov eax, dword ptr [edi + 0x28]
0069288f cmp eax, 0x3b6
00692894 je 0x6928ac
00692896 cmp eax, 0x3c0
0069289b jne 0x6928a3
0069289d cmp dword ptr [edi + 0x2c], 4
006928a1 je 0x6928ac
006928a3 and dword ptr [edi + 0x14c], 0xffffffdf
006928aa jmp 0x6928b3
006928ac or dword ptr [edi + 0x14c], 0x20
006928b3 push ecx
006928b4 lea ecx, [edi + 0x3c]
006928b7 call 0x4073a0
006928bc cmp byte ptr [ebp - 0x8f], 0
006928c3 je 0x6928ce
006928c5 push 1
006928c7 mov ecx, edi
006928c9 call 0x6971a0
006928ce mov edx, dword ptr [ebp - 0x60]
006928d1 cmp edx, 0x10
006928d4 jb 0x6928fe
006928d6 mov ecx, dword ptr [ebp - 0x74]
006928d9 inc edx
006928da mov eax, ecx
006928dc cmp edx, 0x1000
006928e2 jb 0x6928f4
006928e4 mov ecx, dword ptr [ecx - 4]
006928e7 add edx, 0x23
006928ea sub eax, ecx
006928ec add eax, -4
006928ef cmp eax, 0x1f
006928f2 ja 0x692924
006928f4 push edx
006928f5 push ecx
006928f6 call 0x9eb08e
006928fb add esp, 8
006928fe mov edx, dword ptr [ebp - 0x48]
00692901 cmp edx, 0x10
00692904 jb 0x692934
00692906 mov ecx, dword ptr [ebp - 0x5c]
00692909 inc edx
0069290a mov eax, ecx
0069290c cmp edx, 0x1000
00692912 jb 0x69292a
00692914 mov ecx, dword ptr [ecx - 4]
00692917 add edx, 0x23
0069291a sub eax, ecx
0069291c add eax, -4
0069291f cmp eax, 0x1f
00692922 jbe 0x69292a
00692924 call dword ptr [0xa065ac]
0069292a push edx
0069292b push ecx
0069292c call 0x9eb08e
00692931 add esp, 8
00692934 mov ecx, dword ptr [ebp - 0xc]
00692937 mov dword ptr fs:[0], ecx
0069293e pop ecx
0069293f pop edi
00692940 pop esi
00692941 mov ecx, dword ptr [ebp - 0x14]
00692944 xor ecx, ebp
00692946 call 0x9eacd7
0069294b mov esp, ebp
0069294d pop ebp
0069294e mov esp, ebx
00692950 pop ebx
00692951 ret 4
