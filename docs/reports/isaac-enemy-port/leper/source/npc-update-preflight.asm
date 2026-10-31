0069f000 and al, 0x50
0069f002 lea eax, [ebp - 0x33c]
0069f008 push eax
0069f009 call 0x412130
0069f00e push eax
0069f00f lea eax, [ebp - 0x334]
0069f015 push eax
0069f016 lea ecx, [edi + 0x294]
0069f01c call 0x962ac0
0069f021 mov ecx, eax
0069f023 call 0x9628d0
0069f028 push eax
0069f029 lea ecx, [edi + 0x2b8]
0069f02f call 0x962a90
0069f034 mov esi, dword ptr [ebp - 0x270]
0069f03a test esi, esi
0069f03c je 0x69f091
0069f03e mov ecx, 3
0069f043 call 0x659230
0069f048 test eax, eax
0069f04a jne 0x69f091
0069f04c push ecx
0069f04d mov dword ptr [esp], 0x3f000000
0069f054 lea eax, [ebp - 0x32c]
0069f05a push eax
0069f05b lea eax, [edi + 0x294]
0069f061 mov ecx, esi
0069f063 push eax
0069f064 lea eax, [ebp - 0x324]
0069f06a push eax
0069f06b lea eax, [ebp - 0x31c]
0069f071 push eax
0069f072 call 0x412130
0069f077 mov ecx, eax
0069f079 call 0x962ac0
0069f07e mov ecx, eax
0069f080 call 0x9628d0
0069f085 push eax
0069f086 lea ecx, [edi + 0x2b8]
0069f08c call 0x962a90
0069f091 mov esi, dword ptr [ebp - 0x298]
0069f097 test esi, esi
0069f099 je 0x69f133
0069f09f lea ecx, [edi + 0xea8]
0069f0a5 call 0x4076f0
0069f0aa test eax, eax
0069f0ac jne 0x69f112
0069f0ae call 0x6c3d90
0069f0b3 mov ecx, dword ptr [0xbfd65c]
0069f0b9 push eax
0069f0ba push 3
0069f0bc push esi
0069f0bd push 0xc02fec
0069f0c2 lea eax, [edi + 0x294]
0069f0c8 push eax
0069f0c9 push 0x13
0069f0cb push 0x3e8
0069f0d0 call 0x422e20
0069f0d5 mov esi, eax
0069f0d7 push edi
0069f0d8 mov ecx, esi
0069f0da call 0x681960
0069f0df push dword ptr [ebp - 0x298]
0069f0e5 mov ecx, esi
0069f0e7 call 0x6818e0
0069f0ec mov edx, dword ptr [esi]
0069f0ee push ecx
0069f0ef mov ecx, esi
0069f0f1 mov dword ptr [esp], 0x40600000
0069f0f8 call dword ptr [edx + 0x3c]
0069f0fb mov eax, dword ptr [esi]
0069f0fd mov ecx, esi
0069f0ff call dword ptr [eax + 0xc]
0069f102 push esi
0069f103 lea esi, [edi + 0xea8]
0069f109 mov ecx, esi
0069f10b call 0x4bc380
0069f110 jmp 0x69f118
0069f112 lea esi, [edi + 0xea8]
0069f118 mov ecx, esi
0069f11a call 0x4076f0
0069f11f test eax, eax
0069f121 je 0x69f133
0069f123 push 1
0069f125 mov ecx, esi
0069f127 call 0x4076f0
0069f12c mov ecx, eax
0069f12e call 0x4274c0
0069f133 mov ecx, dword ptr [0xbfd65c]
0069f139 call 0x4023f0
0069f13e mov ecx, eax
0069f140 call 0x7cf750
0069f145 test eax, eax
0069f147 jne 0x69f2f0
0069f14d push eax
0069f14e mov ecx, edi
0069f150 call 0x684630
0069f155 test al, al
0069f157 je 0x69f2f0
0069f15d mov ecx, dword ptr [0xbfd65c]
0069f163 push 0
0069f165 push 0
0069f167 push 0x15e
0069f16c call 0x412740
0069f171 mov ecx, eax
0069f173 call 0x91d340
0069f178 test eax, eax
0069f17a je 0x69f19a
0069f17c push eax
0069f17d lea ecx, [ebp - 0x38]
0069f180 call 0x4229a0
0069f185 push ecx
0069f186 mov dword ptr [esp], 0
0069f18d lea eax, [ebp - 0x38]
0069f190 push 0x28
0069f192 push eax
0069f193 mov ecx, edi
0069f195 call 0x6851c0
0069f19a mov ecx, dword ptr [0xbfd65c]
0069f1a0 push 0
0069f1a2 push 0
0069f1a4 push 0x87
0069f1a9 call 0x412740
0069f1ae mov ecx, eax
0069f1b0 call 0x91d550
0069f1b5 mov esi, eax
0069f1b7 test esi, esi
0069f1b9 je 0x69f23e
0069f1bf push 5
0069f1c1 push dword ptr [edi + 0x344]
0069f1c7 lea ecx, [ebp - 0x20]
0069f1ca call 0x7a7cd0
0069f1cf mov ecx, eax
0069f1d1 mov dword ptr [ebp - 4], 0xe
0069f1d8 call 0x7a7db0
0069f1dd mov ecx, esi
0069f1df fstp dword ptr [ebp - 0x27c]
0069f1e5 call 0x6415d0
0069f1ea mulss xmm0, dword ptr [0xb6a234]
0069f1f2 lea ecx, [ebp - 0x20]
0069f1f5 addss xmm0, dword ptr [0xb6a350]
0069f1fd comiss xmm0, dword ptr [ebp - 0x27c]
0069f204 mov dword ptr [ebp - 4], 0xffffffff
0069f20b seta byte ptr [ebp - 0x281]
0069f212 call 0x407620
0069f217 cmp byte ptr [ebp - 0x281], 0
0069f21e je 0x69f23e
0069f220 push esi
0069f221 lea ecx, [ebp - 0x60]
0069f224 call 0x4229a0
0069f229 push ecx
0069f22a mov dword ptr [esp], 0
0069f231 lea eax, [ebp - 0x60]
0069f234 push 0x5a
0069f236 push eax
0069f237 mov ecx, edi
0069f239 call 0x685ca0
0069f23e mov ecx, dword ptr [0xbfd65c]
0069f244 push 0
0069f246 push 0
0069f248 push 0xbc
0069f24d call 0x412740
0069f252 mov ecx, eax
0069f254 call 0x91d550
0069f259 mov esi, eax
0069f25b test esi, esi
0069f25d je 0x69f2f0
0069f263 push 5
0069f265 push dword ptr [edi + 0x344]
0069f26b lea ecx, [ebp - 0x20]
0069f26e call 0x7a7cd0
0069f273 mov ecx, eax
0069f275 mov dword ptr [ebp - 4], 0xf
0069f27c call 0x7a7db0
0069f281 mov ecx, esi
0069f283 fstp dword ptr [ebp - 0x27c]
0069f289 call 0x6415d0
0069f28e mulss xmm0, dword ptr [0xb6a234]
0069f296 lea ecx, [ebp - 0x20]
0069f299 addss xmm0, dword ptr [0xb6a350]
0069f2a1 comiss xmm0, dword ptr [ebp - 0x27c]
0069f2a8 mov dword ptr [ebp - 4], 0xffffffff
0069f2af seta byte ptr [ebp - 0x281]
0069f2b6 call 0x407620
0069f2bb cmp byte ptr [ebp - 0x281], 0
0069f2c2 je 0x69f2f0
0069f2c4 push esi
0069f2c5 lea ecx, [ebp - 0x38]
0069f2c8 call 0x4229a0
0069f2cd push 0x5a
0069f2cf lea eax, [ebp - 0x38]
0069f2d2 mov ecx, edi
0069f2d4 push eax
0069f2d5 call 0x685080
0069f2da push esi
0069f2db lea ecx, [ebp - 0x60]
0069f2de call 0x4229a0
0069f2e3 push 0x5a
0069f2e5 lea eax, [ebp - 0x60]
0069f2e8 mov ecx, edi
0069f2ea push eax
0069f2eb call 0x68edd0
0069f2f0 mov ecx, edi
0069f2f2 call 0x695680
0069f2f7 mov ecx, eax
0069f2f9 call 0x4866c0
0069f2fe test eax, eax
0069f300 je 0x69f325
0069f302 mov ecx, eax
0069f304 call 0x786be0
0069f309 test al, al
0069f30b je 0x69f325
0069f30d push edi
0069f30e lea ecx, [ebp - 0x38]
0069f311 call 0x4229a0
0069f316 push 0
0069f318 push -2
0069f31a lea eax, [ebp - 0x38]
0069f31d mov ecx, edi
0069f31f push eax
0069f320 call 0x6857d0
0069f325 mov ecx, dword ptr [0xbfd65c]
0069f32b push 0
0069f32d push 0
0069f32f push 0x202
0069f334 call 0x412740
0069f339 mov ecx, eax
0069f33b call 0x91d340
0069f340 test eax, eax
0069f342 je 0x69f3d9
0069f348 mov ecx, dword ptr [0xbfd65c]
0069f34e call 0x412740
0069f353 mov ecx, eax
0069f355 call 0x91dae0
0069f35a cvttss2si eax, xmm0
0069f35e mov ecx, 0x37
0069f363 mov dword ptr [ebp - 0x2a4], 0x26
0069f36d lea edx, [ebp - 0x27c]
0069f373 sub ecx, eax
0069f375 mov dword ptr [ebp - 0x27c], ecx
0069f37b lea ecx, [ebp - 0x2a4]
0069f381 call 0x417c80
0069f386 mov ecx, edi
0069f388 mov esi, dword ptr [eax]
0069f38a mov eax, dword ptr [edi]
0069f38c mov eax, dword ptr [eax + 0x48]
0069f38f call eax
0069f391 xor edx, edx
0069f393 mov ecx, edi
0069f395 test al, al
0069f397 push 0
0069f399 setne dl
0069f39c add edx, 2
0069f39f imul esi, edx
0069f3a2 call 0x684630
0069f3a7 test al, al
0069f3a9 je 0x69f3d9
0069f3ab mov ecx, esi
0069f3ad call 0x659230
0069f3b2 test eax, eax
0069f3b4 jne 0x69f3d9
0069f3b6 cmp byte ptr [edi + 0x16b], al
0069f3bc jne 0x69f3d9
0069f3be mov ecx, edi
0069f3c0 call 0x681360
0069f3c5 mov esi, eax
0069f3c7 push 0
0069f3c9 push 0x20
0069f3cb mov ecx, esi
0069f3cd call 0x4122a0
0069f3d2 mov ecx, esi
0069f3d4 call 0x681390
0069f3d9 push 0
0069f3db mov ecx, edi
0069f3dd call 0x68cf40
0069f3e2 test al, al
0069f3e4 je 0x69f547
0069f3ea push 0
0069f3ec push 0x20
0069f3ee mov ecx, edi
0069f3f0 call 0x4122f0
0069f3f5 test al, al
0069f3f7 je 0x69f547
0069f3fd cmp dword ptr [edi + 0x210], 0
0069f404 jg 0x69f547
0069f40a push 0
0069f40c push 0x32
0069f40e mov ecx, edi
0069f410 call 0x684790
0069f415 test al, al
0069f417 je 0x69f547
0069f41d mov ecx, edi
0069f41f call 0x681360
0069f424 mov esi, eax
0069f426 push 0
0069f428 push 0x20
0069f42a mov ecx, esi
0069f42c call 0x4122c0
0069f431 mov ecx, esi
0069f433 call 0x681390
0069f438 push 0xc02fec
0069f43d lea ecx, [edi + 0x2b8]
0069f443 call 0x962ca0
0069f448 test al, al
0069f44a je 0x69f547
0069f450 lea ecx, [ebp - 0x2b0]
0069f456 call 0x9624d0
0069f45b mov esi, 1
0069f460 mov edx, 2
0069f465 mov ecx, esi
0069f467 call 0x659250
0069f46c lea edx, [esi + 1]
0069f46f mov ecx, esi
0069f471 movd xmm0, eax
0069f475 cvtdq2pd xmm0, xmm0
0069f479 shr eax, 0x1f
0069f47c addsd xmm0, qword ptr [eax*8 + 0xb6c940]
0069f485 cvtpd2ps xmm0, xmm0
0069f489 mulss xmm0, dword ptr [0xb6a9a0]
0069f491 subss xmm0, dword ptr [0xb6a9cc]
0069f499 movss dword ptr [ebp - 0x2b0], xmm0
0069f4a1 call 0x659250
0069f4a6 lea esi, [edi + 0x294]
0069f4ac push esi
0069f4ad push ecx
0069f4ae movd xmm0, eax
0069f4b2 cvtdq2pd xmm0, xmm0
0069f4b6 mov ecx, dword ptr [0xbfd65c]
0069f4bc shr eax, 0x1f
0069f4bf addsd xmm0, qword ptr [eax*8 + 0xb6c940]
0069f4c8 mov dword ptr [esp], 0
0069f4cf lea eax, [ebp - 0x18]
0069f4d2 push esi
0069f4d3 push eax
0069f4d4 cvtpd2ps xmm0, xmm0
0069f4d8 mulss xmm0, dword ptr [0xb6a9a0]
0069f4e0 subss xmm0, dword ptr [0xb6a9cc]
0069f4e8 movss dword ptr [ebp - 0x2ac], xmm0
0069f4f0 call 0x4023f0
0069f4f5 mov ecx, eax
0069f4f7 call 0x427710
0069f4fc mov ecx, eax
0069f4fe call 0x962c70
0069f503 mov byte ptr [ebp - 0x281], al
0069f509 mov ecx, esi
0069f50b lea eax, [ebp - 0x2b0]
0069f511 push eax
0069f512 call 0x962a90
0069f517 cmp byte ptr [ebp - 0x281], 0
0069f51e je 0x69f547
0069f520 push ecx
0069f521 mov ecx, dword ptr [0xbfd65c]
0069f527 lea eax, [ebp - 0x18]
0069f52a mov dword ptr [esp], 0
0069f531 push esi
0069f532 push eax
0069f533 call 0x4023f0
0069f538 mov ecx, eax
0069f53a call 0x427710
0069f53f push eax
0069f540 mov ecx, esi
0069f542 call 0x962cd0
0069f547 push 0
0069f549 push 0x10
0069f54b mov ecx, edi
0069f54d call 0x4122f0
0069f552 test al, al
0069f554 jne 0x69f61f
0069f55a mov ecx, dword ptr [0xbfd65c]
0069f560 xor esi, esi
0069f562 mov dword ptr [ebp - 0x298], eax
0069f568 call 0x412740
0069f56d mov ecx, eax
0069f56f call 0x412730
0069f574 test eax, eax
0069f576 je 0x69f61f
0069f57c lea edi, [esi + 1]
0069f57f nop 
0069f580 mov ecx, dword ptr [0xbfd65c]
0069f586 push 0x5d
0069f588 push esi
0069f589 call 0x412750
0069f58e mov ecx, eax
0069f590 call 0x427860
0069f595 mov ecx, eax
0069f597 call 0x88b570
0069f59c mov ecx, dword ptr [ebp - 0x298]
0069f5a2 test al, al
0069f5a4 movzx ecx, cl
0069f5a7 cmovne ecx, edi
0069f5aa inc esi
0069f5ab mov dword ptr [ebp - 0x298], ecx
0069f5b1 mov ecx, dword ptr [0xbfd65c]
0069f5b7 call 0x412740
0069f5bc mov ecx, eax
0069f5be call 0x412730
0069f5c3 cmp esi, eax
0069f5c5 jb 0x69f580
0069f5c7 cmp byte ptr [ebp - 0x298], 0
0069f5ce mov edi, dword ptr [ebp - 0x2c0]
0069f5d4 je 0x69f61f
0069f5d6 movss xmm3, dword ptr [0xb6a670]
0069f5de lea ecx, [ebp - 0x110]
0069f5e4 movss xmm2, dword ptr [0xb6a480]
0069f5ec movss xmm1, dword ptr [0xb6a3b0]
0069f5f4 mov esi, dword ptr [edi]
0069f5f6 push 1
0069f5f8 push 0
0069f5fa push 0
0069f5fc push 2
0069f5fe call 0x427080
0069f603 push eax
0069f604 mov ecx, edi
0069f606 call dword ptr [esi + 0x38]
0069f609 push edi
0069f60a lea ecx, [ebp - 0x38]
0069f60d call 0x4229a0
0069f612 push -2
0069f614 lea eax, [ebp - 0x38]
0069f617 mov ecx, edi
0069f619 push eax
0069f61a call 0x685ae0
0069f61f mov ecx, dword ptr [0xbfd65c]
0069f625 push 0xe8
0069f62a call 0x4023f0
0069f62f mov ecx, eax
0069f631 call 0x427760
0069f636 mov ecx, eax
0069f638 call 0x88b570
0069f63d test al, al
0069f63f jne 0x69f677
0069f641 mov ecx, dword ptr [0xbfd65c]
0069f647 push 0x42
0069f649 call 0x4023f0
0069f64e mov ecx, eax
0069f650 call 0x427760
0069f655 mov ecx, eax
0069f657 call 0x88b570
0069f65c test al, al
0069f65e jne 0x69f677
0069f660 mov ecx, dword ptr [0xbfd65c]
0069f666 call 0x4023f0
0069f66b mov ecx, eax
0069f66d call 0x7d9f00
0069f672 cmp eax, 1
0069f675 jne 0x69f6d1
0069f677 push 0
0069f679 push 0x20000001
0069f67e mov ecx, edi
0069f680 call 0x4122f0
0069f685 test al, al
0069f687 je 0x69f692
0069f689 cmp dword ptr [edi + 0x28], 0xd4
0069f690 jne 0x69f6d1
0069f692 movss xmm2, dword ptr [0xb6a614]
0069f69a movss xmm3, dword ptr [0xb6a690]
0069f6a2 movaps xmm1, xmm2
0069f6a5 mov esi, dword ptr [edi]
0069f6a7 push 1
0069f6a9 push 0
0069f6ab push 0xfa
0069f6b0 push 2
0069f6b2 push 0x28
0069f6b4 push 0x28
0069f6b6 push 0x28
0069f6b8 push ecx
0069f6b9 lea ecx, [ebp - 0x110]
0069f6bf mov dword ptr [esp], 0x3f800000
0069f6c6 call 0x4270d0
0069f6cb push eax
0069f6cc mov ecx, edi
0069f6ce call dword ptr [esi + 0x38]
0069f6d1 push 0x100000
0069f6d6 push 0
0069f6d8 mov ecx, edi
0069f6da call 0x4122f0
0069f6df test al, al
0069f6e1 je 0x69f708
0069f6e3 movss xmm1, dword ptr [edi + 0x2f4]
0069f6eb movss xmm0, dword ptr [0xb6a5b8]
0069f6f3 call 0x65c960
0069f6f8 mulss xmm0, dword ptr [edi + 0x2c4]
0069f700 movss dword ptr [edi + 0x2c4], xmm0
0069f708 cmp byte ptr [edi + 0xbb3], 0
0069f70f je 0x69f761
0069f711 movss xmm2, dword ptr [0xb6a614]
0069f719 movaps xmm1, xmm2
0069f71c movaps xmm0, xmm2
0069f71f subss xmm0, dword ptr [edi + 0x2c4]
0069f727 subss xmm1, dword ptr [edi + 0xafc]
0069f72f mulss xmm1, xmm0
0069f733 movaps xmm0, xmm2
0069f736 subss xmm0, xmm1
0069f73a movss xmm1, dword ptr [edi + 0x2f4]
0069f742 call 0x65c960
0069f747 lea eax, [ebp - 0x27c]
0069f74d movss dword ptr [ebp - 0x27c], xmm0
0069f755 push eax
0069f756 lea ecx, [edi + 0x2b8]
0069f75c call 0x962bb0
0069f761 lea esi, [edi + 0x3c]
0069f764 push 0xb49158
0069f769 mov ecx, esi
0069f76b mov dword ptr [ebp - 0x27c], esi
0069f771 call 0x4060f0
0069f776 test al, al
0069f778 je 0x69f855
0069f77e push 0xb49158
0069f783 mov ecx, esi
0069f785 call 0x406290
0069f78a mov esi, eax
0069f78c call 0x6c3d90
0069f791 mov ecx, dword ptr [0xbfd65c]
0069f797 push 0
0069f799 push 0xbeaaec
0069f79e push 0xbeab18
0069f7a3 push 0
0069f7a5 push eax
0069f7a6 push 0
0069f7a8 push 0
0069f7aa push 0xc02fec
0069f7af lea eax, [edi + 0x294]
0069f7b5 push eax
0069f7b6 push 0x10
0069f7b8 push 0x3e8
0069f7bd call 0x422e20
0069f7c2 push eax
0069f7c3 call 0x9ec34c
0069f7c8 add esp, 0x14
0069f7cb mov edi, eax
0069f7cd mov ecx, edi
0069f7cf push esi
0069f7d0 call 0x447d00
0069f7d5 movss xmm2, dword ptr [0xb6a3b0]
0069f7dd lea ecx, [ebp - 0x18]
0069f7e0 movaps xmm1, xmm2
0069f7e3 call 0x9624e0
0069f7e8 push eax
0069f7e9 lea eax, [ebp - 0x40]
0069f7ec push eax
0069f7ed lea ecx, [esi + 0x10]
0069f7f0 call 0x962b80
0069f7f5 push eax
0069f7f6 mov ecx, edi
0069f7f8 call 0x427330
0069f7fd push ecx
0069f7fe mov ecx, edi
0069f800 mov dword ptr [esp], 0x41200000
0069f807 call 0x4273d0
0069f80c movss xmm0, dword ptr [0xb6a614]
0069f814 mov esi, dword ptr [edi]
0069f816 movaps xmm3, xmm0
0069f819 push 1
0069f81b push 0
0069f81d push 0xff
0069f822 push -1
0069f824 push 0
0069f826 push 0
0069f828 push 0
0069f82a push ecx
0069f82b movaps xmm2, xmm0
0069f82e mov dword ptr [esp], 0x3f000000
0069f835 movaps xmm1, xmm0
0069f838 lea ecx, [ebp - 0x110]
0069f83e call 0x4270d0
0069f843 push eax
0069f844 mov ecx, edi
0069f846 call dword ptr [esi + 0x38]
0069f849 mov edi, dword ptr [ebp - 0x2c0]
0069f84f mov esi, dword ptr [ebp - 0x27c]
0069f855 mov ecx, edi
0069f857 call 0x6adb50
0069f85c mov ecx, edi
0069f85e call 0x6adfd0
0069f863 test byte ptr [edi + 0xe68], 1
0069f86a je 0x69f887
0069f86c mov ecx, edi
0069f86e mov dword ptr [edi + 0xac4], 1
0069f878 call 0x699730
0069f87d mov dword ptr [edi + 0xac4], 0
0069f887 cmp dword ptr [edi + 0x28], 0x3c5
0069f88e mov ecx, edi
0069f890 movss xmm0, dword ptr [edi + 0x2d8]
0069f898 movss dword ptr [ebp - 0x27c], xmm0
0069f8a0 jne 0x69f8a9
0069f8a2 call 0x4bafb0
0069f8a7 jmp 0x69f8ae
0069f8a9 call 0x6860a0
0069f8ae movss xmm0, dword ptr [ebp - 0x27c]
0069f8b6 lea edx, [ebp - 0x27c]
0069f8bc subss xmm0, dword ptr [edi + 0x2d8]
0069f8c4 lea ecx, [ebp - 0x2a4]
0069f8ca mov dword ptr [ebp - 0x2a4], 0
0069f8d4 movss dword ptr [ebp - 0x27c], xmm0
0069f8dc call 0x417c70
0069f8e1 test byte ptr [edi + 0xe68], 8
0069f8e8 movss xmm0, dword ptr [eax]
0069f8ec addss xmm0, dword ptr [edi + 0xbac]
0069f8f4 movss dword ptr [edi + 0xbac], xmm0
0069f8fc je 0x69f919
0069f8fe mov ecx, edi
0069f900 mov dword ptr [edi + 0xac4], 4
0069f90a call 0x699730
0069f90f mov dword ptr [edi + 0xac4], 0
0069f919 mov ecx, dword ptr [0xbfd65c]
0069f91f push 0xf
0069f921 call 0x641630
0069f926 test al, al
0069f928 je 0x69f9c2
0069f92e mov esi, dword ptr [edi]
0069f930 lea ecx, [ebp - 0x110]
0069f936 push 1
0069f938 push 0
0069f93a push 0xff
0069f93f push -1
0069f941 sub esp, 0x10
0069f944 xorps xmm3, xmm3
0069f947 xorps xmm2, xmm2
0069f94a xorps xmm1, xmm1
0069f94d mov dword ptr [esp + 0xc], 0
0069f955 mov dword ptr [esp + 8], 0
0069f95d mov dword ptr [esp + 4], 0
0069f965 mov dword ptr [esp], 0
0069f96c call 0x408270
0069f971 push eax
0069f972 mov ecx, edi
0069f974 call dword ptr [esi + 0x38]
0069f977 sub esp, 0x10
0069f97a lea ecx, [ebp - 0x23c]
0069f980 xorps xmm3, xmm3
0069f983 xorps xmm2, xmm2
0069f986 xorps xmm1, xmm1
0069f989 mov dword ptr [esp + 0xc], 0
0069f991 mov dword ptr [esp + 8], 0
0069f999 mov dword ptr [esp + 4], 0
0069f9a1 mov dword ptr [esp], 0
0069f9a8 call 0x408270
0069f9ad lea esi, [edi + 0x3c]
0069f9b0 push eax
0069f9b1 mov ecx, esi
0069f9b3 call 0x402370
0069f9b8 mov dword ptr [edi + 0x150], 0
0069f9c2 mov ecx, dword ptr [0xbfd65c]
0069f9c8 push 4
0069f9ca call 0x641630
0069f9cf test al, al
0069f9d1 jne 0x69f9e8
0069f9d3 mov ecx, dword ptr [0xbfd65c]
0069f9d9 push 6
0069f9db call 0x641630
0069f9e0 test al, al
0069f9e2 je 0x69fd6f
0069f9e8 lea eax, [edi + 0x294]
0069f9ee mov ecx, edi
0069f9f0 mov dword ptr [ebp - 0x27c], eax
0069f9f6 call 0x682200
0069f9fb cmp eax, 2
0069f9fe jge 0x69fb10
0069fa04 mov edx, dword ptr [ebp - 0x27c]
0069fa0a lea ecx, [ebp - 0x2b0]
0069fa10 push 1
0069fa12 call 0x659540
0069fa17 mov ecx, dword ptr [0xbfd65c]
0069fa1d add esp, 4
0069fa20 call 0x4023f0
0069fa25 mov ecx, eax
0069fa27 call 0x68f4e0
0069fa2c push eax
0069fa2d lea ecx, [ebp - 0x2b0]
0069fa33 call 0x962af0
0069fa38 mov ecx, dword ptr [0xbfd65c]
0069fa3e lea eax, [ebp - 0x2bc]
0069fa44 push eax
0069fa45 call 0x4023f0
0069fa4a mov ecx, eax
0069fa4c call 0x412670
0069fa51 mov ecx, eax
0069fa53 mov dword ptr [ebp - 4], 0x10
0069fa5a call 0x4076f0
0069fa5f movss xmm0, dword ptr [ebp - 0x2ac]
0069fa67 mov esi, eax
0069fa69 mov edi, dword ptr [esi]
0069fa6b call 0x9eb8a0
0069fa70 movss xmm0, dword ptr [ebp - 0x2b0]
0069fa78 push eax
0069fa79 call 0x9eb8a0
0069fa7e push eax
0069fa7f lea eax, [ebp - 0x20]
0069fa82 mov ecx, esi
0069fa84 push eax
0069fa85 call dword ptr [edi + 0x54]
0069fa88 lea ecx, [ebp - 0x2bc]
0069fa8e mov dword ptr [ebp - 4], 0xffffffff
0069fa95 call 0x407790
0069fa9a mov edi, dword ptr [ebp - 0x2c0]
0069faa0 push 0xff
0069faa5 push 0
0069faa7 push 0
0069faa9 lea esi, [edi + 0xbd0]
0069faaf push 0
0069fab1 mov ecx, esi
0069fab3 call 0x65ae50
0069fab8 push ecx
0069fab9 mov ecx, esi
0069fabb mov dword ptr [esp], 0x3f333333
0069fac2 call 0x402230
0069fac7 movss xmm1, dword ptr [0xb6a5a4]
0069facf sub esp, 0xc
0069fad2 movss xmm0, dword ptr [ebp - 0x18]
0069fad7 mov ecx, esi
0069fad9 mulss xmm0, xmm1
0069fadd movss dword ptr [esp + 8], xmm0
0069fae3 movss xmm0, dword ptr [ebp - 0x1c]
0069fae8 mulss xmm0, xmm1
0069faec movss dword ptr [esp + 4], xmm0
0069faf2 movss xmm0, dword ptr [ebp - 0x20]
0069faf7 mulss xmm0, xmm1
0069fafb movss dword ptr [esp], xmm0
0069fb00 call 0x65aee0
0069fb05 push esi
0069fb06 lea esi, [edi + 0x3c]
0069fb09 mov ecx, esi
0069fb0b call 0x402370
0069fb10 mov ecx, dword ptr [0xbfd65c]
0069fb16 call 0x402400
0069fb1b add eax, dword ptr [edi + 0x20]
0069fb1e xor edx, edx
0069fb20 mov ecx, 0x1e
0069fb25 div ecx
0069fb27 cmp edx, 2
0069fb2a jae 0x69fcdf
0069fb30 push 1
0069fb32 lea edx, [edi + 0x294]
0069fb38 lea ecx, [ebp - 0x2b0]
0069fb3e call 0x659540
0069fb43 mov ecx, dword ptr [0xbfd65c]
0069fb49 add esp, 4
0069fb4c call 0x4023f0
0069fb51 mov ecx, eax
0069fb53 call 0x68f4e0
0069fb58 push eax
0069fb59 lea ecx, [ebp - 0x2b0]
0069fb5f call 0x962af0
0069fb64 mov ecx, dword ptr [0xbfd65c]
0069fb6a lea eax, [ebp - 0x2bc]
0069fb70 push eax
0069fb71 call 0x4023f0
0069fb76 mov ecx, eax
0069fb78 call 0x412670
0069fb7d mov ecx, eax
0069fb7f mov dword ptr [ebp - 4], 0x11
0069fb86 call 0x4076f0
0069fb8b cvttss2si ecx, dword ptr [ebp - 0x2ac]
0069fb93 mov edx, dword ptr [eax]
0069fb95 push ecx
0069fb96 cvttss2si ecx, dword ptr [ebp - 0x2b0]
0069fb9e push ecx
0069fb9f lea ecx, [ebp - 0x20]
0069fba2 push ecx
0069fba3 mov ecx, eax
0069fba5 call dword ptr [edx + 0x54]
0069fba8 lea ecx, [ebp - 0x2bc]
0069fbae mov dword ptr [ebp - 4], 0xffffffff
0069fbb5 call 0x407790
0069fbba lea ecx, [edi + 0xbd0]
0069fbc0 call 0x402220
0069fbc5 movss xmm2, dword ptr [0xb6a3b0]
0069fbcd movss xmm1, dword ptr [0xb6a50c]
0069fbd5 fstp dword ptr [ebp - 0x27c]
0069fbdb movss xmm0, dword ptr [ebp - 0x27c]
0069fbe3 call 0x962380
0069fbe8 push ecx
0069fbe9 lea ecx, [edi + 0xbd0]
0069fbef movss dword ptr [esp], xmm0
0069fbf4 call 0x402230
0069fbf9 movss xmm0, dword ptr [ebp - 0x18]
0069fbfe lea ecx, [edi + 0xbd0]
0069fc04 mulss xmm0, dword ptr [0xb6a5a4]
0069fc0c movss dword ptr [ebp - 0x27c], xmm0
0069fc14 call 0x402280
0069fc19 movss xmm2, dword ptr [0xb6a480]
0069fc21 movss xmm1, dword ptr [ebp - 0x27c]
0069fc29 fstp dword ptr [ebp - 0x2a4]
0069fc2f movss xmm0, dword ptr [ebp - 0x2a4]
0069fc37 call 0x962380
0069fc3c push ecx
0069fc3d movss dword ptr [esp], xmm0
0069fc42 lea ecx, [edi + 0xbd0]
0069fc48 movss xmm0, dword ptr [ebp - 0x1c]
0069fc4d mulss xmm0, dword ptr [0xb6a5a4]
0069fc55 movss dword ptr [ebp - 0x27c], xmm0
0069fc5d call 0x402270
0069fc62 movss xmm2, dword ptr [0xb6a480]
0069fc6a movss xmm1, dword ptr [ebp - 0x27c]
0069fc72 fstp dword ptr [ebp - 0x2a4]
0069fc78 movss xmm0, dword ptr [ebp - 0x2a4]
0069fc80 call 0x962380
0069fc85 push ecx
0069fc86 movss dword ptr [esp], xmm0
0069fc8b lea ecx, [edi + 0xbd0]
0069fc91 movss xmm0, dword ptr [ebp - 0x20]
0069fc96 mulss xmm0, dword ptr [0xb6a5a4]
0069fc9e movss dword ptr [ebp - 0x27c], xmm0
0069fca6 call 0x402260
0069fcab movss xmm2, dword ptr [0xb6a480]
0069fcb3 movss xmm1, dword ptr [ebp - 0x27c]
0069fcbb fstp dword ptr [ebp - 0x2a4]
0069fcc1 movss xmm0, dword ptr [ebp - 0x2a4]
0069fcc9 call 0x962380
0069fcce push ecx
0069fccf movss dword ptr [esp], xmm0
0069fcd4 lea ecx, [edi + 0xbd0]
0069fcda call 0x65aee0
0069fcdf mov ecx, esi
0069fce1 call 0x4023b0
0069fce6 push eax
0069fce7 lea ecx, [ebp - 0x8c]
0069fced call 0x402170
0069fcf2 push ecx
0069fcf3 mov dword ptr [esp], 0x3dcccccd
0069fcfa lea eax, [edi + 0xbd0]
0069fd00 push eax
0069fd01 lea eax, [ebp - 0x8c]
0069fd07 push eax
0069fd08 lea eax, [ebp - 0xb8]
0069fd0e push eax
0069fd0f call 0x65b210
0069fd14 add esp, 0x10
0069fd17 mov ecx, esi
0069fd19 call 0x4023b0
0069fd1e mov ecx, eax
0069fd20 call 0x402220
0069fd25 push ecx
0069fd26 lea ecx, [ebp - 0xb8]
0069fd2c fstp dword ptr [esp]
0069fd2f call 0x402230
0069fd34 sub esp, 0x10
0069fd37 lea ecx, [ebp - 0xb8]
0069fd3d mov dword ptr [esp + 0xc], 0x3f800000
0069fd45 mov dword ptr [esp + 8], 0x3ca3d70a
0069fd4d mov dword ptr [esp + 4], 0x3ca3d70a
0069fd55 mov dword ptr [esp], 0x3ca3d70a
0069fd5c call 0x65ae20
0069fd61 lea eax, [ebp - 0xb8]
0069fd67 mov ecx, esi
0069fd69 push eax
0069fd6a call 0x402370
0069fd6f mov ecx, dword ptr [0xbfd65c]
0069fd75 push 0x19
0069fd77 call 0x641630
0069fd7c test al, al
0069fd7e jne 0x69fd95
0069fd80 mov ecx, dword ptr [0xbfd65c]
0069fd86 push 9
0069fd88 call 0x422e50
0069fd8d test al, al
0069fd8f je 0x6a00f5
0069fd95 push 0
0069fd97 mov ecx, edi
0069fd99 call 0x68cf40
0069fd9e test al, al
0069fda0 je 0x6a00f5
0069fda6 movss xmm0, dword ptr [edi + 0x2dc]
0069fdae divss xmm0, dword ptr [0xb6aa0c]
0069fdb6 mov ecx, dword ptr [0xbfd65c]
0069fdbc push 0x19
0069fdbe divss xmm0, dword ptr [0xb6aa0c]
0069fdc6 movss dword ptr [ebp - 0x274], xmm0
0069fdce call 0x641630
0069fdd3 test al, al
0069fdd5 je 0x69fdde
0069fdd7 mov byte ptr [edi + 0x308], 1
0069fdde mov eax, dword ptr [edi + 0x28]
0069fde1 cmp eax, 0x104
0069fde6 jne 0x69fe32
0069fde8 cmp dword ptr [edi + 0x2c], 0xa
0069fdec jne 0x69fe50
0069fdee movss xmm0, dword ptr [ebp - 0x274]
0069fdf6 mulss xmm0, dword ptr [0xb6a864]
0069fdfe movss dword ptr [ebp - 0x274], xmm0
0069fe06 mov ecx, dword ptr [0xbfd65c]
0069fe0c call 0x4023f0
0069fe11 mov ecx, eax
0069fe13 call 0x430d00
0069fe18 cmp eax, 0x11
0069fe1b jne 0x69feda
0069fe21 movss xmm0, dword ptr [ebp - 0x274]
0069fe29 addss xmm0, xmm0
0069fe2d jmp 0x69ff2a
0069fe32 cmp eax, 0x47
0069fe35 je 0x69fdee
0069fe37 cmp eax, 0x48
0069fe3a je 0x69fdee
0069fe3c cmp eax, 0x49
0069fe3f je 0x69fdee
0069fe41 cmp eax, 0x4a
0069fe44 je 0x69fdee
0069fe46 cmp eax, 0x4b
0069fe49 je 0x69fdee
0069fe4b cmp eax, 0x4c
0069fe4e je 0x69fdee
0069fe50 cmp eax, 0x51
0069fe53 jne 0x69fe6f
0069fe55 mov ecx, dword ptr [0xbfd65c]
0069fe5b call 0x4023f0
0069fe60 mov ecx, eax
0069fe62 call 0x430d60
0069fe67 cmp eax, 0x18
0069fe6a je 0x69fdee
0069fe6c mov eax, dword ptr [edi + 0x28]
0069fe6f cmp eax, 0x112
0069fe74 je 0x69fead
0069fe76 cmp eax, 0x113
0069fe7b je 0x69fead
0069fe7d mov ecx, dword ptr [0xbfd65c]
0069fe83 call 0x4023f0
0069fe88 mov ecx, eax
0069fe8a call 0x430d60
0069fe8f cmp eax, 0x37
0069fe92 jne 0x69fe06
0069fe98 movss xmm0, dword ptr [ebp - 0x274]
0069fea0 mulss xmm0, dword ptr [0xb6a8cc]
0069fea8 jmp 0x69fdfe
0069fead cmp byte ptr [edi + 0x308], 0
0069feb4 movss xmm0, dword ptr [ebp - 0x274]
0069febc mulss xmm0, dword ptr [0xb6a3e0]
0069fec4 movss dword ptr [ebp - 0x274], xmm0
0069fecc je 0x69fe06
0069fed2 xorps xmm0, xmm0
0069fed5 jmp 0x69fdfe
0069feda mov ecx, dword ptr [0xbfd65c]
0069fee0 call 0x4023f0
0069fee5 mov ecx, eax
0069fee7 call 0x430d00
0069feec cmp eax, 6
0069feef jne 0x69ff03
0069fef1 movss xmm0, dword ptr [ebp - 0x274]
0069fef9 mulss xmm0, dword ptr [0xb6a864]
0069ff01 jmp 0x69ff2a
0069ff03 mov ecx, dword ptr [0xbfd65c]
0069ff09 call 0x4023f0
0069ff0e mov ecx, eax
0069ff10 call 0x430d00
0069ff15 cmp eax, 5
0069ff18 je 0x69ff32
0069ff1a movss xmm0, dword ptr [ebp - 0x274]
0069ff22 mulss xmm0, dword ptr [0xb6a910]
0069ff2a movss dword ptr [ebp - 0x274], xmm0
0069ff32 mov ecx, dword ptr [0xbfd65c]
0069ff38 push 9
0069ff3a call 0x422e50
0069ff3f test al, al
0069ff41 je 0x69ff5b
0069ff43 movss xmm0, dword ptr [ebp - 0x274]
0069ff4b mulss xmm0, dword ptr [0xb6aafc]
0069ff53 movss dword ptr [ebp - 0x274], xmm0
0069ff5b mov eax, dword ptr [edi]
0069ff5d mov ecx, edi
0069ff5f mov eax, dword ptr [eax + 0x48]
0069ff62 call eax
0069ff64 test al, al
0069ff66 jne 0x69ff9f
0069ff68 mov ecx, dword ptr [0xbfd65c]
0069ff6e push 9
0069ff70 call 0x422e50
0069ff75 test al, al
0069ff77 jne 0x69ff9f
0069ff79 mov ecx, dword ptr [0xbfd65c]
0069ff7f call 0x4023f0
0069ff84 mov ecx, eax
0069ff86 call 0x448020
0069ff8b test eax, eax
0069ff8d jg 0x6a00f5
0069ff93 mov byte ptr [edi + 0xb8c], 0
0069ff9a jmp 0x6a00f5
0069ff9f mov eax, dword ptr [edi + 0x28]
0069ffa2 cmp eax, 0x4a
0069ffa5 je 0x6a00b2
0069ffab cmp eax, 0x4b
0069ffae je 0x6a00b2
0069ffb4 cmp eax, 0x4c
0069ffb7 je 0x6a00b2
0069ffbd movss xmm0, dword ptr [edi + 0x2d8]
0069ffc5 xorps xmm1, xmm1
0069ffc8 comiss xmm1, xmm0
0069ffcb jb 0x6a00e5
0069ffd1 mov ecx, dword ptr [0xbfd65c]
0069ffd7 push 9
0069ffd9 call 0x422e50
0069ffde test al, al
0069ffe0 jne 0x6a0084
0069ffe6 mov eax, dword ptr [edi + 0x28]
0069ffe9 cmp eax, 0x24
0069ffec je 0x6a0084
0069fff2 cmp eax, 0x106
0069fff7 je 0x6a0084
0069fffd cmp eax, 0x107
006a0002 je 0x6a0084
006a0008 cmp eax, 0x4e
006a000b je 0x6a0084
006a0011 cmp eax, 0x47
006a0014 je 0x6a0084
006a0016 cmp eax, 0x48
006a0019 je 0x6a0084
006a001b cmp eax, 0x49
006a001e je 0x6a0084
006a0020 cmp eax, 0x104
006a0025 jne 0x6a002d
006a0027 cmp dword ptr [edi + 0x2c], 0xa
006a002b je 0x6a0084
006a002d mov ecx, dword ptr [0xbfd65c]
006a0033 call 0x4023f0
006a0038 mov ecx, eax
006a003a call 0x430d00
006a003f cmp eax, 0x11
006a0042 je 0x6a0084
006a0044 mov ecx, dword ptr [0xbfd65c]
006a004a call 0x4023f0
006a004f mov ecx, eax
006a0051 call 0x430d60
006a0056 cmp eax, 0x37
006a0059 je 0x6a0084
006a005b cmp dword ptr [edi + 0x28], 0x51
006a005f jne 0x6a0078
006a0061 mov ecx, dword ptr [0xbfd65c]
006a0067 call 0x4023f0
006a006c mov ecx, eax
006a006e call 0x430d60
006a0073 cmp eax, 0x18
006a0076 je 0x6a0084
006a0078 mov byte ptr [edi + 0xb8c], 0
006a007f jmp 0x6a00f5
006a0084 mov esi, dword ptr [edi]
006a0086 lea ecx, [ebp - 0x38]
006a0089 push 0x1e
006a008b mov byte ptr [edi + 0x308], 0
006a0092 call 0x427290
006a0097 push eax
006a0098 push 0
006a009a push 0
006a009c push ecx
006a009d mov ecx, edi
006a009f mov dword ptr [esp], 0x3f800000
006a00a6 call dword ptr [esi + 0x20]
006a00a9 mov byte ptr [edi + 0x16b], 1
006a00b0 jmp 0x6a00f5
006a00b2 movss xmm0, dword ptr [edi + 0x2d8]
006a00ba xorps xmm1, xmm1
006a00bd comiss xmm1, xmm0
006a00c0 jb 0x6a00e5
006a00c2 cmp dword ptr [edi + 0x180], 0
006a00c9 je 0x6a00e5
006a00cb mov byte ptr [edi + 0x308], 0
006a00d2 mov dword ptr [edi + 0x2d8], 0x3f800000
006a00dc mov byte ptr [edi + 0x16b], 1
006a00e3 jmp 0x6a00f5
006a00e5 subss xmm0, dword ptr [ebp - 0x274]
006a00ed movss dword ptr [edi + 0x2d8], xmm0
006a00f5 mov ecx, edi
006a00f7 call 0x6acb40
006a00fc mov ecx, edi
006a00fe call 0x684740
006a0103 test al, al
006a0105 jne 0x6a0253
006a010b cmp byte ptr [edi + 0x169], al
006a0111 je 0x6a0253
006a0117 push 0
006a0119 mov ecx, edi
006a011b call 0x68cf40
006a0120 test al, al
006a0122 je 0x6a0253
006a0128 lea esi, [edi + 0x2b8]
006a012e mov ecx, esi
006a0130 call 0x962a30
006a0135 fstp dword ptr [ebp - 0x27c]
006a013b movss xmm0, dword ptr [ebp - 0x27c]
006a0143 comiss xmm0, dword ptr [0xb6a614]
006a014a jbe 0x6a0253
006a0150 mov ecx, dword ptr [0xbfd65c]
006a0156 call 0x4023f0
006a015b mov ecx, eax
006a015d call 0x7db890
006a0162 test al, al
006a0164 je 0x6a0253
006a016a push dword ptr [edi + 0x20]
006a016d mov ecx, edi
006a016f push 7
006a0171 call 0x684790
006a0176 test al, al
006a0178 je 0x6a0253
006a017e cmp dword ptr [edi + 0x180], 0
006a0185 je 0x6a0253
006a018b call 0x6c3d90
006a0190 push 0
006a0192 push 0xbeaaec
006a0197 push 0xbeab18
006a019c push 0
006a019e push eax
006a019f push 0
006a01a1 push edi
006a01a2 push 0xc02fec
006a01a7 push esi
006a01a8 lea eax, [ebp - 0x18]
006a01ab push eax
006a01ac lea ecx, [edi + 0x294]
006a01b2 call 0x962a60
006a01b7 mov ecx, dword ptr [0xbfd65c]
006a01bd push eax
006a01be push 0x63
006a01c0 push 0x3e8
006a01c5 call 0x422e20
006a01ca push eax
006a01cb call 0x9ec34c
006a01d0 movss xmm0, dword ptr [edi + 0x2c8]
006a01d8 add esp, 0x14
006a01db mulss xmm0, dword ptr [0xb6a274]
006a01e3 mov esi, eax
006a01e5 lea eax, [ebp - 0x27c]
006a01eb mov ecx, 0xbc7a28
006a01f0 push eax
006a01f1 mulss xmm0, dword ptr [edi + 0xb88]
006a01f9 lea eax, [ebp - 0x40]
006a01fc push eax
006a01fd movss dword ptr [ebp - 0x27c], xmm0
006a0205 call 0x962b50
006a020a push eax
006a020b mov ecx, esi
006a020d call 0x427330
006a0212 push ecx
006a0213 mov ecx, esi
006a0215 mov dword ptr [esp], 0xc1200000
006a021c call 0x4273d0
006a0221 lea eax, [ebp - 0x27c]
006a0227 mov dword ptr [ebp - 0x27c], 0x3f000000
006a0231 push eax
006a0232 lea eax, [ebp - 0x2e4]
006a0238 push eax
006a0239 lea ecx, [edi + 0x2b8]
006a023f call 0x962b50
006a0244 push eax
006a0245 mov ecx, esi
006a0247 call 0x422ae0
006a024c mov eax, dword ptr [esi]
006a024e mov ecx, esi
006a0250 call dword ptr [eax + 0xc]
006a0253 lea esi, [edi + 0x294]
006a0259 push esi
006a025a lea ecx, [edi + 0x26c]
006a0260 mov dword ptr [ebp - 0x2d0], esi
006a0266 call 0x962cd0
006a026b cmp byte ptr [edi + 0xbb0], 0
006a0272 jne 0x6a0293
006a0274 push dword ptr [edi + 0x2c]
006a0277 mov ecx, dword ptr [0xbfd680]
006a027d push dword ptr [edi + 0x28]
006a0280 call 0x41c4a0
006a0285 mov ecx, eax
006a0287 call 0x8861d0
006a028c mov byte ptr [edi + 0xbb0], 1
006a0293 mov eax, dword ptr [edi + 0x288]
006a0299 mov ecx, edi
006a029b push dword ptr [edi + 0x20]
006a029e mov eax, dword ptr [eax + 0xd0]
006a02a4 add eax, eax
006a02a6 push eax
006a02a7 call 0x684790
006a02ac test al, al
006a02ae jne 0x6a02e5
006a02b0 cmp dword ptr [edi + 0x28], 0x322
006a02b7 jne 0x6a02f2
006a02b9 cmp dword ptr [edi + 0xab4], 8
