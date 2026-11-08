00414f80 push ebp
00414f81 mov ebp, esp
00414f83 and esp, 0xfffffff8
00414f86 sub esp, 0x18
00414f89 push esi
00414f8a mov esi, ecx
00414f8c push edi
00414f8d mov dword ptr [esp + 0x18], esi
00414f91 mov ecx, dword ptr [esi]
00414f93 mov dword ptr [esi + 0x6c], 0
00414f9a call 0x416980
00414f9f mov ecx, dword ptr [esi + 4]
00414fa2 call 0x416980
00414fa7 mov ecx, dword ptr [esi + 8]
00414faa call 0x416980
00414faf mov ecx, dword ptr [esi + 0xc]
00414fb2 call 0x416980
00414fb7 mov ecx, dword ptr [esi + 0x10]
00414fba call 0x416980
00414fbf mov ecx, dword ptr [esi + 0x14]
00414fc2 call 0x416980
00414fc7 mov ecx, dword ptr [esi + 0x18]
00414fca call 0x416980
00414fcf mov ecx, dword ptr [esi + 0x1c]
00414fd2 call 0x416980
00414fd7 xor eax, eax
00414fd9 xor edx, edx
00414fdb mov dword ptr [esp + 0x14], eax
00414fdf mov byte ptr [esp + 0xa], al
00414fe3 mov dword ptr [esp + 0xc], edx
00414fe7 cmp dword ptr [esi + 0x4c], eax
00414fea jbe 0x415204
00414ff0 mov eax, dword ptr [esi + 0x44]
00414ff3 mov edi, dword ptr [eax + edx*4]
00414ff6 cmp dword ptr [edi + 0x180], 0
00414ffd mov byte ptr [edi + 0x184], 0
00415004 je 0x4151f2
0041500a mov ecx, dword ptr [edi + 0x28]
0041500d cmp ecx, 3
00415010 jne 0x415037
00415012 cmp dword ptr [edi + 0x2c], 0xef
00415019 jne 0x41502e
0041501b mov ecx, dword ptr [esi + 8]
0041501e push edi
0041501f call 0x4169e0
00415024 lea ecx, [esi + 0x1c]
00415027 mov ecx, dword ptr [ecx]
00415029 jmp 0x4151a7
0041502e mov ecx, esi
00415030 mov ecx, dword ptr [ecx]
00415032 jmp 0x4151a7
00415037 cmp ecx, 9
0041503a jne 0x41507f
0041503c mov ecx, dword ptr [esi + 0xc]
0041503f push edi
00415040 call 0x4169e0
00415045 cmp byte ptr [esp + 0xa], 0
0041504a jne 0x415063
0041504c mov ecx, dword ptr [edi + 0x38c]
00415052 xor eax, eax
00415054 and ecx, 0x1000
0041505a or eax, ecx
0041505c je 0x415063
0041505e mov byte ptr [esp + 0xa], 1
00415063 mov eax, dword ptr [edi + 0x388]
00415069 and eax, 0x80
0041506e or eax, 0
00415071 je 0x4151ad
00415077 mov ecx, dword ptr [esi + 0x14]
0041507a jmp 0x4151a7
0041507f cmp ecx, 2
00415082 je 0x415141
00415088 cmp ecx, 8
0041508b je 0x415141
00415091 lea eax, [ecx - 0xa]
00415094 cmp eax, 0x3dd
00415099 jbe 0x4150c0
0041509b cmp ecx, 4
0041509e je 0x4150c0
004150a0 cmp ecx, 5
004150a3 je 0x4150b8
004150a5 cmp ecx, 6
004150a8 je 0x4150b8
004150aa cmp ecx, 1
004150ad jne 0x4151c0
004150b3 jmp 0x4151b1
004150b8 mov ecx, dword ptr [esi + 0x10]
004150bb jmp 0x4151a7
004150c0 mov ecx, dword ptr [esi + 8]
004150c3 push edi
004150c4 call 0x4169e0
004150c9 mov ecx, dword ptr [edi + 0x28]
004150cc cmp ecx, 0x196
004150d2 je 0x4150f0
004150d4 cmp ecx, 0x394
004150da je 0x4150f0
004150dc cmp ecx, 4
004150df jne 0x4150fc
004150e1 mov eax, dword ptr [edi + 0x2c]
004150e4 cmp eax, 0x13
004150e7 je 0x4150f0
004150e9 cmp eax, 0x14
004150ec je 0x4150f0
004150ee jmp 0x4150fc
004150f0 mov ecx, dword ptr [esi + 0x18]
004150f3 push edi
004150f4 call 0x4169e0
004150f9 mov ecx, dword ptr [edi + 0x28]
004150fc mov eax, dword ptr [edi + 0x160]
00415102 mov edx, dword ptr [edi + 0x164]
00415108 and eax, 0x20000000
0041510d or eax, 0
00415110 jne 0x41513c
00415112 cmp ecx, 0xf5
00415118 je 0x41513c
0041511a cmp ecx, 0x3c3
00415120 je 0x41513c
00415122 and edx, 0x100000
00415128 or eax, edx
0041512a jne 0x41513c
0041512c cmp ecx, 0x322
00415132 je 0x41513c
00415134 cmp ecx, 0x362
0041513a jne 0x4151ad
0041513c mov ecx, dword ptr [esi + 0x1c]
0041513f jmp 0x4151a7
00415141 cmp byte ptr [esp + 0xa], 0
00415146 jne 0x4151a4
00415148 cmp ecx, 2
0041514b jne 0x4151a4
0041514d movups xmm1, xmmword ptr [edi + 0x378]
00415154 movaps xmm0, xmm1
00415157 movd ecx, xmm1
0041515b psrldq xmm0, 8
00415160 movd edx, xmm0
00415164 movaps xmm0, xmm1
00415167 and ecx, dword ptr [0xbc4cf0]
0041516d psrldq xmm0, 0xc
00415172 and edx, dword ptr [0xbc4cf8]
00415178 movd eax, xmm0
0041517c psrldq xmm1, 4
00415181 and eax, dword ptr [0xbc4cfc]
00415187 mov dword ptr [esp + 0x1c], eax
0041518b movd eax, xmm1
0041518f and eax, dword ptr [0xbc4cf4]
00415195 or ecx, eax
00415197 jne 0x41519f
00415199 or edx, dword ptr [esp + 0x1c]
0041519d je 0x4151a4
0041519f mov byte ptr [esp + 0xa], 1
004151a4 mov ecx, dword ptr [esi + 4]
004151a7 push edi
004151a8 call 0x4169e0
004151ad mov edx, dword ptr [esp + 0xc]
004151b1 mov eax, dword ptr [esp + 0x14]
004151b5 mov ecx, dword ptr [edi + 0x28]
004151b8 mov dword ptr [edi + 0x24], eax
004151bb inc eax
004151bc mov dword ptr [esp + 0x14], eax
004151c0 cmp ecx, 0x3e8
004151c6 jne 0x4151f2
004151c8 mov ecx, dword ptr [esi + 0x6c]
004151cb lea eax, [ecx + 1]
004151ce cmp eax, dword ptr [esi + 0x68]
004151d1 jbe 0x4151e5
004151d3 push 0xb3f428
004151d8 push 3
004151da call 0x95e330
004151df mov ecx, dword ptr [esi + 0x6c]
004151e2 add esp, 8
004151e5 mov eax, dword ptr [esi + 0x64]
004151e8 mov edx, dword ptr [esp + 0xc]
004151ec mov dword ptr [eax + ecx*4], edi
004151ef inc dword ptr [esi + 0x6c]
004151f2 inc edx
004151f3 mov dword ptr [esp + 0xc], edx
004151f7 cmp edx, dword ptr [esi + 0x4c]
004151fa jb 0x414ff0
00415200 mov eax, dword ptr [esp + 0x14]
00415204 mov ecx, eax
00415206 mov byte ptr [esp + 0xb], 0
0041520b imul ecx, eax
0041520e mov eax, dword ptr [esi + 0xc4]
00415214 push 0
00415216 push eax
00415217 mov dword ptr [esi + 0xc8], eax
0041521d mov dword ptr [esp + 0x24], ecx
00415221 push ecx
00415222 lea ecx, [esi + 0xc4]
00415228 mov dword ptr [esi + 0xd0], 0
00415232 call 0x417b20
00415237 mov ecx, dword ptr [esi + 0xc4]
0041523d mov dword ptr [esp + 0xc], ecx
00415241 lea ecx, [esp + 0xc]
00415245 push eax
00415246 mov dword ptr [esp + 0x14], 0
0041524e call 0x417980
00415253 mov edi, dword ptr [esp + 0xc]
00415257 lea ecx, [esp + 0xc]
0041525b mov esi, dword ptr [esp + 0x10]
0041525f push dword ptr [esp + 0x1c]
00415263 mov dword ptr [esp + 0x10], edi
00415267 mov dword ptr [esp + 0x14], esi
0041526b call 0x417980
00415270 push dword ptr [esp + 0x10]
00415274 lea ecx, [esp + 0xf]
00415278 push dword ptr [esp + 0x10]
0041527c push esi
0041527d push edi
0041527e call 0x417c90
00415283 mov esi, dword ptr [esp + 0x28]
00415287 add esp, 0x10
0041528a mov eax, dword ptr [esp + 0x14]
0041528e push dword ptr [esi + 0xc]
00415291 mov ecx, dword ptr [esi]
00415293 mov dword ptr [esi + 0xd4], eax
00415299 call 0x416f10
0041529e push dword ptr [esi + 8]
004152a1 mov ecx, dword ptr [esi]
004152a3 call 0x416f10
004152a8 mov edi, dword ptr [0xbfd65c]
004152ae xor edx, edx
004152b0 mov dword ptr [esp + 0x14], edx
004152b4 mov eax, dword ptr [edi + 0x1ba54]
004152ba sub eax, dword ptr [edi + 0x1ba50]
004152c0 sar eax, 2
004152c3 test eax, eax
004152c5 je 0x41533c
004152c7 nop word ptr [eax + eax]
004152d0 mov ecx, dword ptr [edi + 0x1ba54]
004152d6 mov eax, ecx
004152d8 sub eax, dword ptr [edi + 0x1ba50]
004152de test eax, 0xfffffffc
004152e3 jne 0x4152fe
004152e5 push 0xb3f4d0
004152ea push 3
004152ec call 0x95e330
004152f1 mov ecx, dword ptr [edi + 0x1ba54]
004152f7 add esp, 8
004152fa mov edx, dword ptr [esp + 0x14]
004152fe mov eax, dword ptr [edi + 0x1ba50]
00415304 sub ecx, eax
00415306 sar ecx, 2
00415309 cmp edx, ecx
0041530b jae 0x415310
0041530d lea eax, [eax + edx*4]
00415310 mov eax, dword ptr [eax]
00415312 mov ecx, dword ptr [esi]
00415314 push eax
00415315 call 0x416c90
0041531a mov edi, dword ptr [0xbfd65c]
00415320 mov edx, dword ptr [esp + 0x14]
00415324 inc edx
00415325 mov dword ptr [esp + 0x14], edx
00415329 mov eax, dword ptr [edi + 0x1ba54]
0041532f sub eax, dword ptr [edi + 0x1ba50]
00415335 sar eax, 2
00415338 cmp edx, eax
0041533a jb 0x4152d0
0041533c push dword ptr [esi + 8]
0041533f mov ecx, dword ptr [esi + 4]
00415342 call 0x416f10
00415347 mov ecx, dword ptr [esi + 8]
0041534a call 0x417140
0041534f mov edi, dword ptr [0xbfd65c]
00415355 xor edx, edx
00415357 mov dword ptr [esp + 0x14], edx
0041535b mov eax, dword ptr [edi + 0x1ba54]
00415361 sub eax, dword ptr [edi + 0x1ba50]
00415367 sar eax, 2
0041536a test eax, eax
0041536c je 0x4153dd
0041536e nop 
00415370 mov ecx, dword ptr [edi + 0x1ba54]
00415376 mov eax, ecx
00415378 sub eax, dword ptr [edi + 0x1ba50]
0041537e test eax, 0xfffffffc
00415383 jne 0x41539e
00415385 push 0xb3f4d0
0041538a push 3
0041538c call 0x95e330
00415391 mov ecx, dword ptr [edi + 0x1ba54]
00415397 add esp, 8
0041539a mov edx, dword ptr [esp + 0x14]
0041539e mov eax, dword ptr [edi + 0x1ba50]
004153a4 sub ecx, eax
004153a6 sar ecx, 2
004153a9 cmp edx, ecx
004153ab jae 0x4153b0
004153ad lea eax, [eax + edx*4]
004153b0 mov eax, dword ptr [eax]
004153b2 mov ecx, dword ptr [esi + 8]
004153b5 push eax
004153b6 call 0x416c90
004153bb mov edi, dword ptr [0xbfd65c]
004153c1 mov edx, dword ptr [esp + 0x14]
004153c5 inc edx
004153c6 mov dword ptr [esp + 0x14], edx
004153ca mov eax, dword ptr [edi + 0x1ba54]
004153d0 sub eax, dword ptr [edi + 0x1ba50]
004153d6 sar eax, 2
004153d9 cmp edx, eax
004153db jb 0x415370
004153dd mov eax, dword ptr [edi + 0x1ba54]
004153e3 xor edx, edx
004153e5 sub eax, dword ptr [edi + 0x1ba50]
004153eb sar eax, 2
004153ee mov dword ptr [esp + 0x14], edx
004153f2 test eax, eax
004153f4 je 0x41546d
004153f6 nop word ptr [eax + eax]
00415400 mov ecx, dword ptr [edi + 0x1ba54]
00415406 mov eax, ecx
00415408 sub eax, dword ptr [edi + 0x1ba50]
0041540e test eax, 0xfffffffc
00415413 jne 0x41542e
00415415 push 0xb3f4d0
0041541a push 3
0041541c call 0x95e330
00415421 mov ecx, dword ptr [edi + 0x1ba54]
00415427 add esp, 8
0041542a mov edx, dword ptr [esp + 0x14]
0041542e mov eax, dword ptr [edi + 0x1ba50]
00415434 sub ecx, eax
00415436 sar ecx, 2
00415439 cmp edx, ecx
0041543b jae 0x415440
0041543d lea eax, [eax + edx*4]
00415440 mov eax, dword ptr [eax]
00415442 mov ecx, dword ptr [esi + 0xc]
00415445 push eax
00415446 call 0x416c90
0041544b mov edi, dword ptr [0xbfd65c]
00415451 mov edx, dword ptr [esp + 0x14]
00415455 inc edx
00415456 mov dword ptr [esp + 0x14], edx
0041545a mov eax, dword ptr [edi + 0x1ba54]
00415460 sub eax, dword ptr [edi + 0x1ba50]
00415466 sar eax, 2
00415469 cmp edx, eax
0041546b jb 0x415400
0041546d mov eax, dword ptr [edi + 0x1ba54]
00415473 xor edx, edx
00415475 sub eax, dword ptr [edi + 0x1ba50]
0041547b sar eax, 2
0041547e mov dword ptr [esp + 0x14], edx
00415482 test eax, eax
00415484 je 0x4154fd
00415486 nop word ptr [eax + eax]
00415490 mov ecx, dword ptr [edi + 0x1ba54]
00415496 mov eax, ecx
00415498 sub eax, dword ptr [edi + 0x1ba50]
0041549e test eax, 0xfffffffc
004154a3 jne 0x4154be
004154a5 push 0xb3f4d0
004154aa push 3
004154ac call 0x95e330
004154b1 mov ecx, dword ptr [edi + 0x1ba54]
004154b7 add esp, 8
004154ba mov edx, dword ptr [esp + 0x14]
004154be mov eax, dword ptr [edi + 0x1ba50]
004154c4 sub ecx, eax
004154c6 sar ecx, 2
004154c9 cmp edx, ecx
004154cb jae 0x4154d0
004154cd lea eax, [eax + edx*4]
004154d0 mov eax, dword ptr [eax]
004154d2 mov ecx, dword ptr [esi + 0x10]
004154d5 push eax
004154d6 call 0x416c90
004154db mov edi, dword ptr [0xbfd65c]
004154e1 mov edx, dword ptr [esp + 0x14]
004154e5 inc edx
004154e6 mov dword ptr [esp + 0x14], edx
004154ea mov eax, dword ptr [edi + 0x1ba54]
004154f0 sub eax, dword ptr [edi + 0x1ba50]
004154f6 sar eax, 2
004154f9 cmp edx, eax
004154fb jb 0x415490
004154fd mov ecx, dword ptr [esi + 0x10]
00415500 call 0x417140
00415505 push dword ptr [esi + 0x18]
00415508 mov ecx, dword ptr [esi + 0x10]
0041550b call 0x416f10
00415510 push dword ptr [esi + 8]
00415513 mov ecx, dword ptr [esi + 0x14]
00415516 call 0x416f10
0041551b cmp byte ptr [esp + 0xa], 0
00415520 je 0x41552d
00415522 push dword ptr [esi + 4]
00415525 mov ecx, dword ptr [esi + 0xc]
00415528 call 0x416f10
0041552d push dword ptr [esi + 0xc]
00415530 mov ecx, dword ptr [esi + 0x1c]
00415533 call 0x416f10
00415538 push dword ptr [esi + 8]
0041553b mov ecx, dword ptr [esi + 0x1c]
0041553e call 0x416f10
00415543 mov ecx, dword ptr [0xbfd65c]
00415549 xor edi, edi
0041554b mov dword ptr [esp + 0x14], edi
0041554f mov eax, dword ptr [ecx + 0x1ba54]
00415555 sub eax, dword ptr [ecx + 0x1ba50]
0041555b sar eax, 2
0041555e test eax, eax
00415560 je 0x4157af
00415566 nop word ptr [eax + eax]
00415570 mov esi, dword ptr [0xbfd65c]
00415576 mov ecx, dword ptr [esi + 0x1ba54]
0041557c mov eax, ecx
0041557e sub eax, dword ptr [esi + 0x1ba50]
00415584 test eax, 0xfffffffc
00415589 jne 0x4155a0
0041558b push 0xb3f4d0
00415590 push 3
00415592 call 0x95e330
00415597 mov ecx, dword ptr [esi + 0x1ba54]
0041559d add esp, 8
004155a0 mov esi, dword ptr [esi + 0x1ba50]
004155a6 sub ecx, esi
004155a8 sar ecx, 2
004155ab cmp edi, ecx
004155ad jae 0x4155b2
004155af lea esi, [esi + edi*4]
004155b2 mov esi, dword ptr [esi]
004155b4 mov edi, dword ptr [esi + 0x1d80]
004155ba test edi, edi
004155bc je 0x415785
004155c2 mov eax, dword ptr [edi + 0x1550]
004155c8 cmp eax, dword ptr [esi + 0x1550]
004155ce jge 0x4155d8
004155d0 cmp edi, esi
004155d2 jne 0x415785
004155d8 mov eax, dword ptr [0xbfd65c]
004155dd movss xmm1, dword ptr [0xbc7a28]
004155e5 test byte ptr [eax + 0x1a30dc], 1
004155ec jne 0x4156bd
004155f2 movss xmm0, dword ptr [esi + 0x2cc]
004155fa ucomiss xmm0, xmm1
004155fd lahf 
004155fe test ah, 0x44
00415601 jp 0x415649
00415603 movss xmm0, dword ptr [esi + 0x2d0]
0041560b movss xmm2, dword ptr [0xbc7a2c]
00415613 ucomiss xmm0, xmm2
00415616 lahf 
00415617 test ah, 0x44
0041561a jp 0x415649
0041561c movss xmm0, dword ptr [edi + 0x2cc]
00415624 ucomiss xmm0, xmm1
00415627 lahf 
00415628 test ah, 0x44
0041562b jp 0x415649
0041562d movss xmm0, dword ptr [edi + 0x2d0]
00415635 ucomiss xmm0, xmm2
00415638 lahf 
00415639 test ah, 0x44
0041563c jp 0x415649
0041563e mov edx, edi
00415640 mov ecx, esi
00415642 call 0x689cf0
00415647 jmp 0x415652
00415649 mov edx, edi
0041564b mov ecx, esi
0041564d call 0x689980
00415652 movss xmm0, dword ptr [edi + 0x2cc]
0041565a movss xmm2, dword ptr [0xbc7a28]
00415662 ucomiss xmm0, xmm2
00415665 lahf 
00415666 test ah, 0x44
00415669 jp 0x4156b4
0041566b movss xmm0, dword ptr [edi + 0x2d0]
00415673 movss xmm1, dword ptr [0xbc7a2c]
0041567b ucomiss xmm0, xmm1
0041567e lahf 
0041567f test ah, 0x44
00415682 jp 0x4156b4
00415684 movss xmm0, dword ptr [esi + 0x2cc]
0041568c ucomiss xmm0, xmm2
0041568f lahf 
00415690 test ah, 0x44
00415693 jp 0x4156b4
00415695 movss xmm0, dword ptr [esi + 0x2d0]
0041569d ucomiss xmm0, xmm1
004156a0 lahf 
004156a1 test ah, 0x44
004156a4 jp 0x4156b4
004156a6 mov edx, esi
004156a8 mov ecx, edi
004156aa call 0x689cf0
004156af jmp 0x415785
004156b4 mov edx, esi
004156b6 mov ecx, edi
004156b8 jmp 0x415780
004156bd movss xmm0, dword ptr [edi + 0x2cc]
004156c5 ucomiss xmm0, xmm1
004156c8 lahf 
004156c9 test ah, 0x44
004156cc jp 0x415714
004156ce movss xmm0, dword ptr [edi + 0x2d0]
004156d6 movss xmm2, dword ptr [0xbc7a2c]
004156de ucomiss xmm0, xmm2
004156e1 lahf 
004156e2 test ah, 0x44
004156e5 jp 0x415714
004156e7 movss xmm0, dword ptr [esi + 0x2cc]
004156ef ucomiss xmm0, xmm1
004156f2 lahf 
004156f3 test ah, 0x44
004156f6 jp 0x415714
004156f8 movss xmm0, dword ptr [esi + 0x2d0]
00415700 ucomiss xmm0, xmm2
00415703 lahf 
00415704 test ah, 0x44
00415707 jp 0x415714
00415709 mov edx, esi
0041570b mov ecx, edi
0041570d call 0x689cf0
00415712 jmp 0x41571d
00415714 mov edx, esi
00415716 mov ecx, edi
00415718 call 0x689980
0041571d movss xmm0, dword ptr [esi + 0x2cc]
00415725 movss xmm2, dword ptr [0xbc7a28]
0041572d ucomiss xmm0, xmm2
00415730 lahf 
00415731 test ah, 0x44
00415734 jp 0x41577c
00415736 movss xmm0, dword ptr [esi + 0x2d0]
0041573e movss xmm1, dword ptr [0xbc7a2c]
00415746 ucomiss xmm0, xmm1
00415749 lahf 
0041574a test ah, 0x44
0041574d jp 0x41577c
0041574f movss xmm0, dword ptr [edi + 0x2cc]
00415757 ucomiss xmm0, xmm2
0041575a lahf 
0041575b test ah, 0x44
0041575e jp 0x41577c
00415760 movss xmm0, dword ptr [edi + 0x2d0]
00415768 ucomiss xmm0, xmm1
0041576b lahf 
0041576c test ah, 0x44
0041576f jp 0x41577c
00415771 mov edx, edi
00415773 mov ecx, esi
00415775 call 0x689cf0
0041577a jmp 0x415785
0041577c mov edx, edi
0041577e mov ecx, esi
00415780 call 0x689980
00415785 mov ecx, dword ptr [0xbfd65c]
0041578b mov edi, dword ptr [esp + 0x14]
0041578f inc edi
00415790 mov dword ptr [esp + 0x14], edi
00415794 mov eax, dword ptr [ecx + 0x1ba54]
0041579a sub eax, dword ptr [ecx + 0x1ba50]
004157a0 sar eax, 2
004157a3 cmp edi, eax
004157a5 jb 0x415570
004157ab mov esi, dword ptr [esp + 0x18]
004157af xor edi, edi
004157b1 cmp dword ptr [esi + 0x4c], edi
004157b4 jbe 0x4157dd
004157b6 mov eax, dword ptr [esi + 0x44]
004157b9 mov ecx, dword ptr [eax + edi*4]
004157bc mov eax, dword ptr [ecx + 0x28]
004157bf cmp eax, 7
004157c2 je 0x4157d7
004157c4 push 0
004157c6 cmp eax, 1
004157c9 jne 0x4157d2
004157cb call 0x683850
004157d0 jmp 0x4157d7
004157d2 call 0x682280
004157d7 inc edi
004157d8 cmp edi, dword ptr [esi + 0x4c]
004157db jb 0x4157b6
004157dd pop edi
004157de pop esi
004157df mov esp, ebp
004157e1 pop ebp
004157e2 ret 
