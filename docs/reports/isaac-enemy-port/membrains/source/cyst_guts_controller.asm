005031b0 push ebp
005031b1 mov ebp, esp
005031b3 and esp, 0xfffffff8
005031b6 sub esp, 0x188
005031bc mov eax, dword ptr [0xbaa3b4]
005031c1 xor eax, esp
005031c3 mov dword ptr [esp + 0x184], eax
005031ca push esi
005031cb push edi
005031cc mov edi, ecx
005031ce mov ecx, dword ptr [0xbfd65c]
005031d4 mov dword ptr [esp + 0x4c], edi
005031d8 push dword ptr [ecx + 0x1819c]
005031de push dword ptr [ecx + 0x18194]
005031e4 call 0x70e0f0
005031e9 mov ecx, dword ptr [eax + 0x44]
005031ec mov eax, dword ptr [edi + 0x28]
005031ef shr ecx, 1
005031f1 and ecx, 0xffffff01
005031f7 mov dword ptr [esp + 0x40], ecx
005031fb cmp eax, 0xda
00503200 jne 0x50324c
00503202 test cl, cl
00503204 sete cl
00503207 cmp byte ptr [edi + 0x16b], 0
0050320e mov byte ptr [esp + 0x1b], cl
00503212 je 0x503251
00503214 cmp dword ptr [edi + 0x284], 0
0050321b lea esi, [edi + 0x284]
00503221 jl 0x503251
00503223 mov ecx, dword ptr [0xbfd65c]
00503229 push -1
0050322b push dword ptr [ecx + 0x18194]
00503231 call 0x70e0f0
00503236 push esi
00503237 lea ecx, [esp + 0x24]
0050323b push ecx
0050323c lea ecx, [eax + 0x80]
00503242 call 0x4d1cd0
00503247 mov eax, dword ptr [edi + 0x28]
0050324a jmp 0x503251
0050324c mov byte ptr [esp + 0x1b], 1
00503251 cmp eax, 0x28
00503254 jne 0x50325c
00503256 cmp dword ptr [edi + 0x2c], 2
0050325a jmp 0x503261
0050325c cmp eax, 0x35e
00503261 jne 0x5034c0
00503267 cmp dword ptr [edi + 0x90], 0
0050326e je 0x5033a1
00503274 push 0xb4247c
00503279 lea ecx, [edi + 0x8c]
0050327f call 0x405da0
00503284 mov esi, dword ptr [edi + 0xbc]
0050328a mov dword ptr [esp + 0xc], eax
0050328e test eax, eax
00503290 je 0x5033a7
00503296 xor edx, edx
00503298 mov dword ptr [esp + 0x14], edx
0050329c test esi, esi
0050329e je 0x5034c0
005032a4 lea esi, [edi + 0x3c]
005032a7 mov dword ptr [esp + 0x1c], edx
005032ab nop dword ptr [eax + eax]
005032b0 test edx, edx
005032b2 js 0x5032bc
005032b4 cmp edx, dword ptr [esi + 0x80]
005032ba jl 0x5032db
005032bc cmp dword ptr [esi + 0x14], 0x10
005032c0 mov eax, esi
005032c2 jb 0x5032c6
005032c4 mov eax, dword ptr [esi]
005032c6 push edx
005032c7 push eax
005032c8 push 0xa0830c
005032cd push 3
005032cf call 0x95e330
005032d4 mov eax, dword ptr [esp + 0x1c]
005032d8 add esp, 0x10
005032db mov edx, dword ptr [esp + 0x1c]
005032df mov ecx, dword ptr [esi + 0x7c]
005032e2 mov eax, dword ptr [eax]
005032e4 mov dword ptr [ecx + edx + 0x40], eax
005032e8 mov eax, dword ptr [esp + 0xc]
005032ec mov eax, dword ptr [eax + 4]
005032ef mov dword ptr [ecx + edx + 0x44], eax
005032f3 mov edx, dword ptr [esp + 0x14]
005032f7 test edx, edx
005032f9 js 0x503303
005032fb cmp edx, dword ptr [esi + 0x80]
00503301 jl 0x50331e
00503303 cmp dword ptr [esi + 0x14], 0x10
00503307 mov eax, esi
00503309 jb 0x50330d
0050330b mov eax, dword ptr [esi]
0050330d push edx
0050330e push eax
0050330f push 0xa0830c
00503314 push 3
00503316 call 0x95e330
0050331b add esp, 0x10
0050331e mov edx, dword ptr [esp + 0x1c]
00503322 mov ecx, dword ptr [esi + 0x7c]
00503325 mov eax, dword ptr [esp + 0xc]
00503329 mov eax, dword ptr [eax + 0x10]
0050332c mov dword ptr [ecx + edx + 0x34], eax
00503330 mov eax, dword ptr [esp + 0xc]
00503334 mov eax, dword ptr [eax + 0x14]
00503337 mov dword ptr [ecx + edx + 0x38], eax
0050333b mov edx, dword ptr [esp + 0x14]
0050333f test edx, edx
00503341 js 0x50334b
00503343 cmp edx, dword ptr [esi + 0x80]
00503349 jl 0x50336a
0050334b cmp dword ptr [esi + 0x14], 0x10
0050334f mov eax, esi
00503351 jb 0x503355
00503353 mov eax, dword ptr [esi]
00503355 push edx
00503356 push eax
00503357 push 0xa0830c
0050335c push 3
0050335e call 0x95e330
00503363 mov edx, dword ptr [esp + 0x24]
00503367 add esp, 0x10
0050336a mov ecx, dword ptr [esi + 0x7c]
0050336d inc edx
0050336e mov esi, dword ptr [esp + 0x1c]
00503372 mov eax, dword ptr [esp + 0xc]
00503376 add dword ptr [esp + 0x1c], 0x9c
0050337e mov dword ptr [esp + 0x14], edx
00503382 mov eax, dword ptr [eax + 0x44]
00503385 mov dword ptr [ecx + esi + 0x3c], eax
00503389 lea esi, [edi + 0x3c]
0050338c mov eax, dword ptr [esp + 0xc]
00503390 cmp edx, dword ptr [edi + 0xbc]
00503396 jb 0x5032b0
0050339c jmp 0x5034c0
005033a1 mov esi, dword ptr [edi + 0xbc]
005033a7 xor ecx, ecx
005033a9 mov dword ptr [esp + 0x1c], ecx
005033ad test esi, esi
005033af je 0x5034c0
005033b5 xor edx, edx
005033b7 mov dword ptr [esp + 0x14], edx
005033bb nop dword ptr [eax + eax]
005033c0 test ecx, ecx
005033c2 js 0x5033cc
005033c4 cmp ecx, dword ptr [edi + 0xbc]
005033ca jl 0x5033f1
005033cc cmp dword ptr [edi + 0x50], 0x10
005033d0 lea eax, [edi + 0x3c]
005033d3 jb 0x5033d8
005033d5 mov eax, dword ptr [edi + 0x3c]
005033d8 push ecx
005033d9 push eax
005033da push 0xa0830c
005033df push 3
005033e1 call 0x95e330
005033e6 mov ecx, dword ptr [esp + 0x2c]
005033ea add esp, 0x10
005033ed mov edx, dword ptr [esp + 0x14]
005033f1 mov eax, dword ptr [edi + 0xb8]
005033f7 movss xmm0, dword ptr [0xc02fec]
005033ff movss dword ptr [eax + edx + 0x40], xmm0
00503405 movss xmm0, dword ptr [0xc02ff0]
0050340d movss dword ptr [eax + edx + 0x44], xmm0
00503413 test ecx, ecx
00503415 js 0x50341f
00503417 cmp ecx, dword ptr [edi + 0xbc]
0050341d jl 0x503444
0050341f cmp dword ptr [edi + 0x50], 0x10
00503423 lea eax, [edi + 0x3c]
00503426 jb 0x50342b
00503428 mov eax, dword ptr [edi + 0x3c]
0050342b push ecx
0050342c push eax
0050342d push 0xa0830c
00503432 push 3
00503434 call 0x95e330
00503439 mov ecx, dword ptr [esp + 0x2c]
0050343d add esp, 0x10
00503440 mov edx, dword ptr [esp + 0x14]
00503444 mov eax, dword ptr [edi + 0xb8]
0050344a movss xmm0, dword ptr [0xbc7a28]
00503452 movss dword ptr [eax + edx + 0x34], xmm0
00503458 movss xmm0, dword ptr [0xbc7a2c]
00503460 movss dword ptr [eax + edx + 0x38], xmm0
00503466 test ecx, ecx
00503468 js 0x503472
0050346a cmp ecx, dword ptr [edi + 0xbc]
00503470 jl 0x503497
00503472 cmp dword ptr [edi + 0x50], 0x10
00503476 lea eax, [edi + 0x3c]
00503479 jb 0x50347e
0050347b mov eax, dword ptr [edi + 0x3c]
0050347e push ecx
0050347f push eax
00503480 push 0xa0830c
00503485 push 3
00503487 call 0x95e330
0050348c mov ecx, dword ptr [esp + 0x2c]
00503490 add esp, 0x10
00503493 mov edx, dword ptr [esp + 0x14]
00503497 mov eax, dword ptr [edi + 0xb8]
0050349d inc ecx
0050349e mov dword ptr [esp + 0x1c], ecx
005034a2 mov dword ptr [eax + edx + 0x3c], 0
005034aa add edx, 0x9c
005034b0 mov dword ptr [esp + 0x14], edx
005034b4 cmp ecx, dword ptr [edi + 0xbc]
005034ba jb 0x5033c0
005034c0 xor eax, eax
005034c2 mov dword ptr [esp + 0x1c], eax
005034c6 mov eax, dword ptr [edi + 0x28]
005034c9 cmp eax, 0x28
005034cc jne 0x503702
005034d2 cmp dword ptr [edi + 0x2c], 2
005034d6 jne 0x5036f9
005034dc mov eax, dword ptr [edi + 0x164]
005034e2 mov esi, dword ptr [edi + 0x160]
005034e8 mov dword ptr [esp + 0x24], eax
005034ec mov eax, esi
005034ee and eax, 0x1000a00
005034f3 or eax, 0
005034f6 jne 0x5035f4
005034fc mov eax, esi
005034fe and eax, 0x4000
00503503 or eax, 0
00503506 jne 0x5035f4
0050350c mov ecx, dword ptr [0xbfd65c]
00503512 call 0x6d0380
00503517 test al, al
00503519 jne 0x5035f4
0050351f mov eax, dword ptr [0xbfd65c]
00503524 mov al, byte ptr [eax + 0x1a30dc]
0050352a not al
0050352c and al, 1
0050352e je 0x5035f4
00503534 movss xmm0, dword ptr [0xb6ad20]
0050353c lea ecx, [edi + 0x294]
00503542 and esi, 0x100
00503548 or esi, 0
0050354b je 0x503575
0050354d push 0x503080
00503552 mov edx, edi
00503554 movaps xmm1, xmm0
00503557 call 0x6d90b0
0050355c add esp, 4
0050355f mov dword ptr [esp + 0x1c], eax
00503563 test eax, eax
00503565 jne 0x5035b8
00503567 movss xmm0, dword ptr [0xb6ad20]
0050356f lea ecx, [edi + 0x294]
00503575 mov eax, dword ptr [edi + 0x160]
0050357b and eax, 0x20000000
00503580 mov byte ptr [esp + 0x10], 1
00503585 or eax, 0
00503588 jne 0x50358f
0050358a mov byte ptr [esp + 0x10], 0
0050358f mov eax, dword ptr [edi + 0xad4]
00503595 mov edx, edi
00503597 shr eax, 0x1f
0050359a movaps xmm1, xmm0
0050359d xor al, 1
0050359f push 0x503080
005035a4 movzx eax, al
005035a7 push eax
005035a8 push dword ptr [esp + 0x18]
005035ac call 0x6d8820
005035b1 add esp, 0xc
005035b4 mov dword ptr [esp + 0x1c], eax
005035b8 mov ecx, dword ptr [edi + 0x31c]
005035be lea esi, [edi + 0x31c]
005035c4 test ecx, ecx
005035c6 je 0x5035dc
005035c8 lea eax, [esp + 0x28]
005035cc mov dword ptr [esp + 0x28], esi
005035d0 push eax
005035d1 add ecx, 0x324
005035d7 call 0x4bc3c0
005035dc mov eax, dword ptr [esp + 0x1c]
005035e0 mov dword ptr [esi], eax
005035e2 test eax, eax
005035e4 je 0x5035f4
005035e6 push esi
005035e7 mov ecx, eax
005035e9 call 0x4bae70
005035ee mov eax, dword ptr [esp + 0x1c]
005035f2 jmp 0x5035ff
005035f4 mov ecx, edi
005035f6 call 0x695680
005035fb mov dword ptr [esp + 0x1c], eax
005035ff movss xmm1, dword ptr [eax + 0x294]
00503607 subss xmm1, dword ptr [edi + 0x294]
0050360f movss xmm2, dword ptr [eax + 0x298]
00503617 subss xmm2, dword ptr [edi + 0x298]
0050361f movaps xmm0, xmm1
00503622 movss dword ptr [esp + 0x14], xmm1
00503628 mulss xmm0, xmm1
0050362c movaps xmm1, xmm2
0050362f movss dword ptr [esp + 0xc], xmm2
00503635 mulss xmm1, xmm2
00503639 addss xmm0, xmm1
0050363d call 0x4228c0
00503642 comiss xmm0, dword ptr [0xb6a18c]
00503649 movss xmm2, dword ptr [esp + 0xc]
0050364f jbe 0x50366d
00503651 movss xmm1, dword ptr [0xb6a614]
00503659 divss xmm1, xmm0
0050365d movss xmm0, dword ptr [esp + 0x14]
00503663 mulss xmm0, xmm1
00503667 mulss xmm2, xmm1
0050366b jmp 0x503673
0050366d movss xmm0, dword ptr [esp + 0x14]
00503673 cmp byte ptr [edi + 0x13c], 0
0050367a addss xmm0, xmm0
0050367e addss xmm2, xmm2
00503682 movss dword ptr [esp + 0x14], xmm0
00503688 movss dword ptr [esp + 0xc], xmm2
0050368e je 0x50369d
00503690 xorps xmm0, xmmword ptr [0xb6c9b0]
00503697 movss dword ptr [esp + 0x14], xmm0
0050369d cmp dword ptr [edi + 0xbc], 1
005036a4 jg 0x5036d0
005036a6 cmp dword ptr [edi + 0x50], 0x10
005036aa lea eax, [edi + 0x3c]
005036ad jb 0x5036b2
005036af mov eax, dword ptr [edi + 0x3c]
005036b2 push 1
005036b4 push eax
005036b5 push 0xa0830c
005036ba push 3
005036bc call 0x95e330
005036c1 movss xmm0, dword ptr [esp + 0x24]
005036c7 add esp, 0x10
005036ca movss xmm2, dword ptr [esp + 0xc]
005036d0 mov eax, dword ptr [edi + 0xb8]
005036d6 addss xmm0, dword ptr [eax + 0xdc]
005036de addss xmm2, dword ptr [eax + 0xe0]
005036e6 movss dword ptr [eax + 0xdc], xmm0
005036ee movss dword ptr [eax + 0xe0], xmm2
005036f6 mov eax, dword ptr [edi + 0x28]
005036f9 cmp eax, 0x28
005036fc je 0x50388f
00503702 cmp eax, 0x35e
00503707 je 0x50388f
0050370d cmp eax, 0xda
00503712 jne 0x503901
00503718 mov ecx, dword ptr [0xbfd65c]
0050371e mov eax, dword ptr [ecx + 0x1a30dc]
00503724 sub eax, dword ptr [edi + 0x280]
0050372a cmp eax, 0x1e
0050372d jl 0x503811
00503733 cmp byte ptr [esp + 0x40], 0
00503738 jne 0x503811
0050373e push 1
00503740 push 0
00503742 add ecx, 0x1ba40
00503748 push 0x97
0050374d call 0x91d550
00503752 test eax, eax
00503754 jne 0x503811
0050375a mov eax, dword ptr [0xbfd65c]
0050375f mov eax, dword ptr [eax + 0x1a30dc]
00503765 sub eax, dword ptr [edi + 0x280]
0050376b cmp eax, 0x1e
0050376e jne 0x50379f
00503770 push ecx
00503771 mov dword ptr [esp], 0x3f800000
00503778 push 0
0050377a push 2
0050377c push ecx
0050377d mov dword ptr [esp], 0x3fc00000
00503784 mov ecx, edi
00503786 push 0xcd
0050378b call 0x6ad720
00503790 mov eax, dword ptr [edi + 0x288]
00503796 mov eax, dword ptr [eax + 0x28]
00503799 mov dword ptr [edi + 0x2e0], eax
0050379f mov esi, dword ptr [edi + 0x70]
005037a2 test esi, esi
005037a4 je 0x503802
005037a6 cmp dword ptr [esi + 0x14], 0x10
005037aa mov eax, esi
005037ac jb 0x5037b0
005037ae mov eax, dword ptr [esi]
005037b0 mov ecx, 0xb42f10
005037b5 mov dl, byte ptr [eax]
005037b7 cmp dl, byte ptr [ecx]
005037b9 jne 0x5037d5
005037bb test dl, dl
005037bd je 0x5037d1
005037bf mov dl, byte ptr [eax + 1]
005037c2 cmp dl, byte ptr [ecx + 1]
005037c5 jne 0x5037d5
005037c7 add eax, 2
005037ca add ecx, 2
005037cd test dl, dl
005037cf jne 0x5037b5
005037d1 xor eax, eax
005037d3 jmp 0x5037da
005037d5 sbb eax, eax
005037d7 or eax, 1
005037da test eax, eax
005037dc jne 0x503802
005037de cmp byte ptr [esi + 0x34], al
005037e1 je 0x503901
005037e7 cmp byte ptr [edi + 0x80], al
005037ed lea esi, [edi + 0x3c]
005037f0 jne 0x503901
005037f6 push 1
005037f8 push 0xb42f10
005037fd jmp 0x5038ea
00503802 push 1
00503804 lea esi, [edi + 0x3c]
00503807 push 0xb42f10
0050380c jmp 0x5038ea
00503811 mov esi, dword ptr [edi + 0x70]
00503814 test esi, esi
00503816 je 0x503862
00503818 cmp dword ptr [esi + 0x14], 0x10
0050381c mov eax, esi
0050381e jb 0x503822
00503820 mov eax, dword ptr [esi]
00503822 mov ecx, 0xb42788
00503827 mov dl, byte ptr [eax]
00503829 cmp dl, byte ptr [ecx]
0050382b jne 0x503847
0050382d test dl, dl
0050382f je 0x503843
00503831 mov dl, byte ptr [eax + 1]
00503834 cmp dl, byte ptr [ecx + 1]
00503837 jne 0x503847
00503839 add eax, 2
0050383c add ecx, 2
0050383f test dl, dl
00503841 jne 0x503827
00503843 xor eax, eax
00503845 jmp 0x50384c
00503847 sbb eax, eax
00503849 or eax, 1
0050384c test eax, eax
0050384e jne 0x503862
00503850 cmp byte ptr [esi + 0x34], al
00503853 je 0x503883
00503855 cmp byte ptr [edi + 0x80], al
0050385b lea esi, [edi + 0x3c]
0050385e jne 0x503883
00503860 jmp 0x503865
00503862 lea esi, [edi + 0x3c]
00503865 push 1
00503867 push 0xb42788
0050386c mov ecx, esi
0050386e call 0x405740
00503873 test al, al
00503875 je 0x503883
00503877 lea ecx, [esi + 0x30]
0050387a call 0x405330
0050387f mov byte ptr [esi + 0x44], 1
00503883 mov dword ptr [edi + 0x2e0], 0
0050388d jmp 0x503901
0050388f mov esi, dword ptr [edi + 0x70]
00503892 test esi, esi
00503894 je 0x5038e0
00503896 cmp dword ptr [esi + 0x14], 0x10
0050389a mov eax, esi
0050389c jb 0x5038a0
0050389e mov eax, dword ptr [esi]
005038a0 mov ecx, 0xb41458
005038a5 mov dl, byte ptr [eax]
005038a7 cmp dl, byte ptr [ecx]
005038a9 jne 0x5038c5
005038ab test dl, dl
005038ad je 0x5038c1
005038af mov dl, byte ptr [eax + 1]
005038b2 cmp dl, byte ptr [ecx + 1]
005038b5 jne 0x5038c5
005038b7 add eax, 2
005038ba add ecx, 2
005038bd test dl, dl
005038bf jne 0x5038a5
005038c1 xor eax, eax
005038c3 jmp 0x5038ca
005038c5 sbb eax, eax
005038c7 or eax, 1
005038ca test eax, eax
005038cc jne 0x5038e0
005038ce cmp byte ptr [esi + 0x34], al
005038d1 je 0x503901
005038d3 cmp byte ptr [edi + 0x80], al
005038d9 lea esi, [edi + 0x3c]
005038dc jne 0x503901
005038de jmp 0x5038e3
005038e0 lea esi, [edi + 0x3c]
005038e3 push 1
005038e5 push 0xb41458
005038ea mov ecx, esi
005038ec call 0x405740
005038f1 test al, al
005038f3 je 0x503901
005038f5 lea ecx, [esi + 0x30]
005038f8 call 0x405330
005038fd mov byte ptr [esi + 0x44], 1
00503901 cmp dword ptr [edi + 0xab4], 0
00503908 jne 0x503b07
0050390e mov dword ptr [edi + 0xb10], 0xffffffff
00503918 mov byte ptr [edi + 0xb14], 0
0050391f mov dword ptr [edi + 0xaf0], 0x3c
00503929 movss xmm0, dword ptr [0xc02fec]
00503931 movss dword ptr [edi + 0x28c], xmm0
00503939 movss xmm0, dword ptr [0xc02ff0]
00503941 movss dword ptr [edi + 0x290], xmm0
00503949 mov eax, dword ptr [edi + 0x28]
0050394c mov byte ptr [edi + 0x13c], 1
00503953 mov dword ptr [edi + 0xab4], 4
0050395d mov dword ptr [edi + 0xb84], 0x3f800000
00503967 cmp eax, 0x28
0050396a jne 0x5039cb
0050396c cmp dword ptr [edi + 0x2c], 2
00503970 jne 0x503a0a
00503976 movaps xmm0, xmmword ptr [0xb6c610]
0050397d lea ecx, [edi + 0x1dc]
00503983 movaps xmm1, xmmword ptr [0xb6c060]
0050398a lea eax, [esp + 0x5c]
0050398e mov dword ptr [esp + 0x7c], 0
00503996 mov dword ptr [esp + 0x80], 0
005039a1 mov dword ptr [esp + 0x84], 0
005039ac cmp ecx, eax
005039ae je 0x503a0a
005039b0 mov eax, dword ptr [esp + 0x84]
005039b7 movups xmmword ptr [ecx], xmm0
005039ba movq xmm0, qword ptr [esp + 0x7c]
005039c0 movups xmmword ptr [ecx + 0x10], xmm1
005039c4 movq qword ptr [ecx + 0x20], xmm0
005039c9 jmp 0x503a07
005039cb cmp eax, 0x35e
005039d0 jne 0x503a0a
005039d2 lea ecx, [edi + 0x1dc]
005039d8 cmp ecx, 0xbc52ac
005039de je 0x503a0a
005039e0 movups xmm0, xmmword ptr [0xbc52ac]
005039e7 movups xmmword ptr [ecx], xmm0
005039ea movups xmm0, xmmword ptr [0xbc52bc]
005039f1 movups xmmword ptr [ecx + 0x10], xmm0
005039f5 movq xmm0, qword ptr [0xbc52cc]
005039fd movq qword ptr [ecx + 0x20], xmm0
00503a02 mov eax, dword ptr [0xbc52d4]
00503a07 mov dword ptr [ecx + 0x28], eax
00503a0a cmp dword ptr [edi + 0x28], 0xda
00503a11 jne 0x503aba
00503a17 mov ecx, dword ptr [edi + 0x160]
00503a1d lea eax, [esp + 0x88]
00503a24 or dword ptr [edi + 0x164], 8
00503a2b and ecx, 0xfffffffb
00503a2e movaps xmm0, xmmword ptr [0xb6c610]
00503a35 or ecx, 1
00503a38 mov dword ptr [edi + 0x160], ecx
00503a3e xorps xmm1, xmm1
00503a41 lea ecx, [edi + 0x1dc]
00503a47 mov byte ptr [edi + 0x308], 1
00503a4e mov dword ptr [esp + 0xa8], 0
00503a59 mov dword ptr [esp + 0xac], 0
00503a64 mov dword ptr [esp + 0xb0], 0
00503a6f cmp ecx, eax
00503a71 je 0x503a92
00503a73 mov eax, dword ptr [esp + 0xb0]
00503a7a movups xmmword ptr [ecx], xmm0
00503a7d movq xmm0, qword ptr [esp + 0xa8]
00503a86 movq qword ptr [ecx + 0x20], xmm0
00503a8b movups xmmword ptr [ecx + 0x10], xmm1
00503a8f mov dword ptr [ecx + 0x28], eax
00503a92 mov dword ptr [edi + 0x1ec], 0x3f800000
00503a9c mov dword ptr [edi + 0x1f0], 0x3f800000
00503aa6 mov dword ptr [edi + 0x1f4], 0x3f800000
00503ab0 mov dword ptr [edi + 0x1f8], 0x3f800000
00503aba mov ecx, dword ptr [edi + 0x30]
00503abd test ecx, ecx
00503abf je 0x503ad3
00503ac1 mov eax, 4
00503ac6 cmp ecx, eax
00503ac8 cmova ecx, eax
00503acb sub eax, ecx
00503acd mov dword ptr [edi + 0xb10], eax
00503ad3 movss xmm0, dword ptr [0xc02fec]
00503adb movss dword ptr [edi + 0xb00], xmm0
00503ae3 movss xmm0, dword ptr [0xc02ff0]
00503aeb movss dword ptr [edi + 0xb04], xmm0
00503af3 pop edi
00503af4 pop esi
00503af5 mov ecx, dword ptr [esp + 0x184]
00503afc xor ecx, esp
00503afe call 0x9eacd7
00503b03 mov esp, ebp
00503b05 pop ebp
00503b06 ret 
00503b07 mov al, byte ptr [esp + 0x1b]
00503b0b test al, al
00503b0d je 0x503b52
00503b0f mov eax, dword ptr [0xbfd65c]
00503b14 mov eax, dword ptr [eax + 0x1a30dc]
00503b1a sub eax, dword ptr [edi + 0x280]
00503b20 jne 0x503b4e
00503b22 movss xmm0, dword ptr [edi + 0x2c4]
00503b2a mulss xmm0, dword ptr [0xb6a4c4]
00503b32 movss dword ptr [edi + 0x2c4], xmm0
00503b3a pop edi
00503b3b pop esi
00503b3c mov ecx, dword ptr [esp + 0x184]
00503b43 xor ecx, esp
00503b45 call 0x9eacd7
00503b4a mov esp, ebp
00503b4c pop ebp
00503b4d ret 
00503b4e mov al, byte ptr [esp + 0x1b]
00503b52 mov esi, dword ptr [edi + 0xb10]
00503b58 movss xmm0, dword ptr [0xb6a4c4]
00503b60 test esi, esi
00503b62 jns 0x503c15
00503b68 test al, al
00503b6a je 0x503c15
00503b70 xor esi, esi
00503b72 mov dword ptr [edi + 0xb10], 0
00503b7c xor eax, eax
00503b7e mov dword ptr [esp + 0x10], eax
00503b82 mov eax, dword ptr [esi*8 + 0xb42db0]
00503b89 lea ecx, [esp + 0x20]
00503b8d lea eax, [eax + eax*4]
00503b90 shl eax, 3
00503b93 movd xmm0, eax
00503b97 mov eax, dword ptr [esi*8 + 0xb42db4]
00503b9e cvtdq2ps xmm0, xmm0
00503ba1 lea eax, [eax + eax*4]
00503ba4 shl eax, 3
00503ba7 addss xmm0, dword ptr [edi + 0x294]
00503baf movss dword ptr [esp + 0x20], xmm0
00503bb5 movd xmm0, eax
00503bb9 cvtdq2ps xmm0, xmm0
00503bbc addss xmm0, dword ptr [edi + 0x298]
00503bc4 movss dword ptr [esp + 0x24], xmm0
00503bca call 0x502e00
00503bcf test eax, eax
00503bd1 jne 0x503bf5
00503bd3 inc esi
00503bd4 mov dword ptr [edi + 0xb10], esi
00503bda mov dword ptr [esp + 0x10], esi
00503bde cmp esi, 4
00503be1 jl 0x503b82
00503be3 call 0x6c3d90
00503be8 mov edx, eax
00503bea and edx, 3
00503bed mov dword ptr [edi + 0xb10], edx
00503bf3 jmp 0x503bf9
00503bf5 mov edx, dword ptr [esp + 0x10]
00503bf9 movss xmm1, dword ptr [edi + 0x2c4]
00503c01 mov esi, edx
00503c03 movss xmm0, dword ptr [0xb6a4c4]
00503c0b mov al, byte ptr [esp + 0x1b]
00503c0f mulss xmm1, xmm0
00503c13 jmp 0x503c3b
00503c15 movss xmm1, dword ptr [edi + 0x2c4]
00503c1d mov edx, esi
00503c1f test al, al
00503c21 je 0x503c29
00503c23 mulss xmm1, xmm0
00503c27 jmp 0x503c3b
00503c29 mulss xmm1, dword ptr [0xb6a5a4]
00503c31 mov dword ptr [edi + 0x17c], 5
00503c3b movss dword ptr [edi + 0x2c4], xmm1
00503c43 movss xmm3, dword ptr [edi + 0x28c]
00503c4b ucomiss xmm3, dword ptr [0xc02fec]
00503c52 lahf 
00503c53 test ah, 0x44
00503c56 jp 0x503c74
00503c58 movss xmm0, dword ptr [edi + 0x290]
00503c60 ucomiss xmm0, dword ptr [0xc02ff0]
00503c67 lahf 
00503c68 test ah, 0x44
00503c6b jp 0x503c74
00503c6d mov ecx, edx
00503c6f jmp 0x503d02
00503c74 mov ecx, edx
00503c76 mov dword ptr [esp + 0xc], ecx
00503c7a test al, al
00503c7c je 0x503d06
00503c82 cmp dword ptr [edi + 0xaf0], -1
00503c89 mov dword ptr [esp + 0xc], ecx
00503c8d je 0x503d06
00503c8f movd xmm0, dword ptr [esi*8 + 0xb42db4]
00503c98 movss xmm2, dword ptr [edi + 0x298]
00503ca0 subss xmm2, dword ptr [edi + 0x290]
00503ca8 movd xmm1, dword ptr [esi*8 + 0xb42db0]
00503cb1 cvtdq2ps xmm0, xmm0
00503cb4 mov dword ptr [esp + 0xc], ecx
00503cb8 cvtdq2ps xmm1, xmm1
00503cbb mulss xmm2, xmm0
00503cbf movss xmm0, dword ptr [edi + 0x294]
00503cc7 subss xmm0, xmm3
00503ccb mulss xmm1, xmm0
00503ccf addss xmm2, xmm1
00503cd3 comiss xmm2, dword ptr [0xb6aeb8]
00503cda jbe 0x503d06
00503cdc movss xmm0, dword ptr [0xc02fec]
00503ce4 movss dword ptr [edi + 0x28c], xmm0
00503cec movss xmm0, dword ptr [0xc02ff0]
00503cf4 movss dword ptr [edi + 0x290], xmm0
00503cfc mov ecx, dword ptr [edi + 0xb10]
00503d02 mov dword ptr [esp + 0xc], ecx
00503d06 movss xmm0, dword ptr [edi + 0x28c]
00503d0e ucomiss xmm0, dword ptr [0xc02fec]
00503d15 lahf 
00503d16 test ah, 0x44
00503d19 jp 0x5042ca
00503d1f movss xmm0, dword ptr [edi + 0x290]
00503d27 ucomiss xmm0, dword ptr [0xc02ff0]
00503d2e lahf 
00503d2f test ah, 0x44
00503d32 jp 0x5042ca
00503d38 test al, al
00503d3a je 0x5042ce
00503d40 xor eax, eax
00503d42 movss xmm2, dword ptr [edi + 0x294]
00503d4a cmp byte ptr [edi + 0xb15], al
00503d50 lea esi, [ecx + ecx]
00503d53 mov edx, dword ptr [esi*4 + 0xb42db0]
00503d5a setne al
00503d5d movss xmm1, dword ptr [edi + 0x298]
00503d65 mov dword ptr [esp + 0x10], esi
00503d69 lea eax, [eax*2 + 1]
00503d70 add eax, esi
00503d72 mov ecx, dword ptr [eax*4 + 0xb42db0]
00503d79 lea eax, [edx + ecx]
00503d7c imul eax, eax, -0x28
00503d7f movd xmm0, eax
00503d83 mov eax, edx
00503d85 cvtdq2ps xmm0, xmm0
00503d88 sub eax, ecx
00503d8a lea eax, [eax + eax*4]
00503d8d addss xmm0, xmm2
00503d91 shl eax, 3
00503d94 movss dword ptr [esp + 0x20], xmm0
00503d9a movd xmm0, eax
00503d9e lea eax, [ecx + ecx*4]
00503da1 cvtdq2ps xmm0, xmm0
00503da4 shl eax, 3
00503da7 lea ecx, [esp + 0x20]
00503dab addss xmm0, xmm1
00503daf movss dword ptr [esp + 0x24], xmm0
00503db5 movd xmm0, eax
00503db9 lea eax, [edx + edx*4]
00503dbc cvtdq2ps xmm0, xmm0
00503dbf shl eax, 3
00503dc2 subss xmm2, xmm0
00503dc6 movd xmm0, eax
00503dca cvtdq2ps xmm0, xmm0
00503dcd movss dword ptr [esp + 0x30], xmm2
00503dd3 addss xmm0, xmm1
00503dd7 movss dword ptr [esp + 0x34], xmm0
00503ddd call 0x502e00
00503de2 lea ecx, [esp + 0x30]
00503de6 mov dword ptr [esp + 0x38], eax
00503dea call 0x502e00
00503def mov ecx, eax
00503df1 or eax, 0xffffffff
00503df4 mov dword ptr [esp + 0x14], ecx
00503df8 mov dword ptr [esp + 0xc], eax
00503dfc cmp dword ptr [edi + 0xe6c], eax
00503e02 je 0x504043
00503e08 cmp dword ptr [edi + 0xaf0], 0
00503e0f jl 0x504043
00503e15 movss xmm2, dword ptr [0xb6a2cc]
00503e1d lea eax, [esp + 0x20]
00503e21 push eax
00503e22 mov ecx, edi
00503e24 call 0x6af0c0
00503e29 movss xmm0, dword ptr [esp + 0x20]
00503e2f ucomiss xmm0, dword ptr [0xc02fec]
00503e36 lahf 
00503e37 test ah, 0x44
00503e3a jp 0x503e53
00503e3c movss xmm0, dword ptr [esp + 0x24]
00503e42 ucomiss xmm0, dword ptr [0xc02ff0]
00503e49 lahf 
00503e4a test ah, 0x44
00503e4d jnp 0x50408e
00503e53 lea edx, [esp + 0x20]
00503e57 lea ecx, [esp + 0x54]
00503e5b call 0x6593a0
00503e60 mov esi, eax
00503e62 xor eax, eax
00503e64 movss xmm2, dword ptr [esi]
00503e68 movss xmm3, dword ptr [esi + 4]
00503e6d movaps xmm1, xmm2
00503e70 andps xmm1, xmmword ptr [0xb6c980]
00503e77 movaps xmm0, xmm3
00503e7a andps xmm0, xmmword ptr [0xb6c980]
00503e81 comiss xmm1, xmm0
00503e84 xorps xmm0, xmm0
00503e87 jbe 0x503e98
00503e89 comiss xmm0, xmm2
00503e8c seta al
00503e8f lea eax, [eax*2 + 1]
00503e96 jmp 0x503ea3
00503e98 comiss xmm0, xmm3
00503e9b mov ecx, 2
00503ea0 cmova eax, ecx
00503ea3 movss xmm0, dword ptr [0xb6a704]
00503eab mov dword ptr [esp + 0xc], eax
00503eaf call 0x411fe0
00503eb4 movss dword ptr [esp + 0x28], xmm0
00503eba movss xmm0, dword ptr [0xb6a704]
00503ec2 call 0x412010
00503ec7 movss xmm3, dword ptr [esi]
00503ecb movss xmm4, dword ptr [esi + 4]
00503ed0 movaps xmm5, xmm3
00503ed3 mulss xmm5, dword ptr [esp + 0x28]
00503ed9 movaps xmm1, xmm4
00503edc mov eax, dword ptr [esp + 0xc]
00503ee0 sub eax, dword ptr [edi + 0xb10]
00503ee6 mulss xmm1, xmm0
00503eea add eax, 4
00503eed subss xmm5, xmm1
00503ef1 movaps xmm1, xmm3
00503ef4 mulss xmm1, xmm0
00503ef8 movaps xmm0, xmm4
00503efb mulss xmm0, dword ptr [esp + 0x28]
00503f01 movss dword ptr [esp + 0x40], xmm5
00503f07 addss xmm1, xmm0
00503f0b movss dword ptr [esp + 0x28], xmm1
00503f11 and eax, 0x80000001
00503f16 jns 0x503f1d
00503f18 dec eax
00503f19 or eax, 0xfffffffe
00503f1c inc eax
00503f1d cmp eax, 1
00503f20 jne 0x504037
00503f26 movss xmm2, dword ptr [edi + 0x294]
00503f2e lea ecx, [esp + 0x20]
00503f32 movaps xmm0, xmm3
00503f35 movss dword ptr [esp + 0x44], xmm2
00503f3b mulss xmm0, dword ptr [0xb6aa3c]
00503f43 addss xmm0, xmm2
00503f47 movss xmm2, dword ptr [edi + 0x298]
00503f4f movss dword ptr [esp + 0x30], xmm2
00503f55 movss dword ptr [esp + 0x20], xmm0
00503f5b movaps xmm0, xmm4
00503f5e mulss xmm0, dword ptr [0xb6aa3c]
00503f66 addss xmm0, xmm2
00503f6a movss dword ptr [esp + 0x24], xmm0
00503f70 call 0x502e00
00503f75 test eax, eax
00503f77 jne 0x504037
00503f7d movss xmm0, dword ptr [esi]
00503f81 lea ecx, [esp + 0x20]
00503f85 addss xmm0, dword ptr [esp + 0x40]
00503f8b mulss xmm0, dword ptr [0xb6aa3c]
00503f93 addss xmm0, dword ptr [edi + 0x294]
00503f9b movss dword ptr [esp + 0x20], xmm0
00503fa1 movss xmm0, dword ptr [esi + 4]
00503fa6 addss xmm0, dword ptr [esp + 0x28]
00503fac mulss xmm0, dword ptr [0xb6aa3c]
00503fb4 addss xmm0, dword ptr [edi + 0x298]
00503fbc movss dword ptr [esp + 0x24], xmm0
00503fc2 call 0x502e00
00503fc7 test eax, eax
00503fc9 jne 0x504015
00503fcb movss xmm1, dword ptr [esi]
00503fcf lea ecx, [esp + 0x20]
00503fd3 subss xmm1, dword ptr [esp + 0x40]
00503fd9 mulss xmm1, dword ptr [0xb6aa3c]
00503fe1 addss xmm1, dword ptr [esp + 0x44]
00503fe7 movss dword ptr [esp + 0x20], xmm1
00503fed movss xmm1, dword ptr [esi + 4]
00503ff2 subss xmm1, dword ptr [esp + 0x28]
00503ff8 mulss xmm1, dword ptr [0xb6aa3c]
00504000 addss xmm1, dword ptr [esp + 0x30]
00504006 movss dword ptr [esp + 0x24], xmm1
0050400c call 0x502e00
00504011 test eax, eax
00504013 je 0x504037
00504015 mov eax, dword ptr [esp + 0xc]
00504019 mov ecx, dword ptr [esp + 0x14]
0050401d cmp eax, dword ptr [edi + 0xb10]
00504023 je 0x50403f
00504025 mov dword ptr [edi + 0xb10], eax
0050402b lea esi, [eax + eax]
0050402e mov byte ptr [edi + 0xb14], 1
00504035 jmp 0x504043
00504037 mov eax, dword ptr [esp + 0xc]
0050403b mov ecx, dword ptr [esp + 0x14]
0050403f mov esi, dword ptr [esp + 0x10]
00504043 cmp dword ptr [esp + 0x38], 0
00504048 je 0x504098
0050404a test ecx, ecx
0050404c jne 0x504098
0050404e cmp byte ptr [edi + 0xb14], cl
00504054 jne 0x504098
00504056 cmp dword ptr [edi + 0xaf0], ecx
0050405c jl 0x504098
0050405e mov ecx, dword ptr [edi + 0xb10]
00504064 cmp ecx, eax
00504066 je 0x504098
00504068 xor eax, eax
0050406a cmp byte ptr [edi + 0xb15], al
00504070 sete al
00504073 lea eax, [eax*2 + 1]
0050407a add ecx, eax
0050407c mov dword ptr [edi + 0xb10], ecx
00504082 mov byte ptr [edi + 0xb14], 1
00504089 jmp 0x5042d2
0050408e mov eax, dword ptr [esp + 0xc]
00504092 mov ecx, dword ptr [esp + 0x14]
00504096 jmp 0x504043
00504098 mov eax, dword ptr [0xbfd65c]
0050409d movss xmm1, dword ptr [0xb6aa3c]
005040a5 mov ecx, dword ptr [eax + 0x18190]
005040ab mov eax, dword ptr [esi*4 + 0xb42db0]
005040b2 mov dword ptr [esp + 0x10], ecx
005040b6 lea eax, [eax + eax*4]
005040b9 shl eax, 3
005040bc movd xmm0, eax
005040c0 cvtdq2ps xmm0, xmm0
005040c3 mov eax, dword ptr [esi*4 + 0xb42db4]
005040ca lea eax, [eax + eax*4]
005040cd addss xmm0, dword ptr [edi + 0x294]
005040d5 shl eax, 3
005040d8 subss xmm0, xmm1
005040dc divss xmm0, xmm1
005040e0 addss xmm0, dword ptr [0xb6a480]
005040e8 cvttss2si edx, xmm0
005040ec movd xmm0, eax
005040f0 cvtdq2ps xmm0, xmm0
005040f3 addss xmm0, dword ptr [edi + 0x298]
005040fb subss xmm0, dword ptr [0xb6ab20]
00504103 divss xmm0, xmm1
00504107 addss xmm0, dword ptr [0xb6a480]
0050410f cvttss2si eax, xmm0
00504113 test edx, edx
00504115 js 0x5041b9
0050411b mov esi, dword ptr [ecx + 0xc]
0050411e cmp edx, esi
00504120 jge 0x5041b9
00504126 test eax, eax
00504128 js 0x5041b9
0050412e cmp eax, dword ptr [ecx + 0x10]
00504131 jge 0x5041b9
00504137 imul esi, eax
0050413a add esi, edx
0050413c push esi
0050413d call 0x7aeec0
00504142 mov edx, dword ptr [esp + 0x10]
00504146 cmp esi, 0x1bf
0050414c ja 0x5041c6
0050414e cmp dword ptr [edx + esi*4 + 0x76c], 0x3b6
00504159 jne 0x5041c6
0050415b cmp dword ptr [edi + 0xaf0], -2
00504162 jne 0x504283
00504168 mov dword ptr [edi + 0xaf0], 0x3c
00504172 mov eax, dword ptr [edi + 0xb10]
00504178 test eax, eax
0050417a je 0x504186
0050417c cmp eax, 2
0050417f mov eax, 0xb42f48
00504184 jne 0x50418b
00504186 mov eax, 0xb42f18
0050418b push 0
0050418d push eax
0050418e lea ecx, [edi + 0x3c]
00504191 call 0x405a00
00504196 movss xmm0, dword ptr [0xb6a614]
0050419e mov eax, dword ptr [edi + 0xbb4]
005041a4 movss dword ptr [esp + 0x10], xmm0
005041aa cmp eax, 0x12
005041ad jne 0x50421e
005041af movss xmm0, dword ptr [0xb6a6f0]
005041b7 jmp 0x50422b
005041b9 or esi, 0xffffffff
005041bc push esi
005041bd call 0x7aeec0
005041c2 mov edx, dword ptr [esp + 0x10]
005041c6 test eax, eax
005041c8 jne 0x50415b
005041ca mov ecx, dword ptr [edx + 0xc]
005041cd mov eax, esi
005041cf cdq 
005041d0 idiv ecx
005041d2 movss xmm2, dword ptr [0xb6aa3c]
005041da movd xmm1, edx
005041de movd xmm0, eax
005041e2 cvtdq2ps xmm1, xmm1
005041e5 cvtdq2ps xmm0, xmm0
005041e8 mulss xmm1, xmm2
005041ec mulss xmm0, xmm2
005041f0 addss xmm1, xmm2
005041f4 addss xmm0, dword ptr [0xb6ab20]
005041fc movss dword ptr [edi + 0x28c], xmm1
00504204 movss dword ptr [edi + 0x290], xmm0
0050420c mov byte ptr [edi + 0xb14], 0
00504213 mov ecx, dword ptr [edi + 0xb10]
00504219 jmp 0x5042d2
0050421e cmp eax, 0x13
00504221 jne 0x504231
00504223 movss xmm0, dword ptr [0xb6a480]
0050422b movss dword ptr [esp + 0x10], xmm0
00504231 mov esi, dword ptr [0xbfd680]
00504237 lea ecx, [esp + 0x28]
0050423b mov dword ptr [esp + 0x28], 0x48
00504243 call 0x8b1340
00504248 movss xmm0, dword ptr [esp + 0x10]
0050424e sub esp, 8
00504251 mov dword ptr [esp + 4], 0
00504259 movss dword ptr [esp], xmm0
0050425e push 0
00504260 push 2
00504262 push ecx
00504263 mov dword ptr [esp], 0x3f800000
0050426a lea ecx, [esi + 0x29de0]
00504270 push dword ptr [esp + 0x3c]
00504274 call 0x888de0
00504279 mov dword ptr [edi + 0xb84], 0x3dcccccd
00504283 mov ecx, dword ptr [esp + 0xc]
00504287 mov edx, dword ptr [edi + 0xb10]
0050428d test ecx, ecx
0050428f js 0x5042b1
00504291 mov eax, ecx
00504293 sub eax, edx
00504295 add eax, 4
00504298 and eax, 0x80000001
0050429d jns 0x5042a4
0050429f dec eax
005042a0 or eax, 0xfffffffe
005042a3 inc eax
005042a4 cmp eax, 1
005042a7 jne 0x5042b1
005042a9 mov dword ptr [edi + 0xb10], ecx
005042af jmp 0x5042d2
005042b1 xor eax, eax
005042b3 lea ecx, [edx + 1]
005042b6 cmp byte ptr [edi + 0xb15], al
005042bc setne al
005042bf lea ecx, [ecx + eax*2]
005042c2 mov dword ptr [edi + 0xb10], ecx
005042c8 jmp 0x5042d2
005042ca mov dword ptr [esp + 0xc], ecx
005042ce mov ecx, dword ptr [esp + 0xc]
005042d2 cmp ecx, 3
005042d5 jle 0x5042dc
005042d7 lea eax, [ecx - 4]
005042da jmp 0x5042e3
005042dc test ecx, ecx
005042de jns 0x5042e9
005042e0 lea eax, [ecx + 4]
005042e3 mov dword ptr [edi + 0xb10], eax
005042e9 movss xmm1, dword ptr [edi + 0x28c]
005042f1 ucomiss xmm1, dword ptr [0xc02fec]
005042f8 lahf 
005042f9 test ah, 0x44
005042fc jp 0x504317
005042fe movss xmm0, dword ptr [edi + 0x290]
00504306 ucomiss xmm0, dword ptr [0xc02ff0]
0050430d lahf 
0050430e test ah, 0x44
00504311 jnp 0x50458c
00504317 cmp byte ptr [esp + 0x1b], 0
0050431c je 0x50458c
00504322 movss xmm2, dword ptr [edi + 0x294]
0050432a subss xmm2, xmm1
0050432e movss xmm1, dword ptr [edi + 0x298]
00504336 subss xmm1, dword ptr [edi + 0x290]
0050433e movss dword ptr [esp + 0x38], xmm2
00504344 movaps xmm0, xmm1
00504347 movss dword ptr [esp + 0x30], xmm1
0050434d mulss xmm0, xmm1
00504351 movaps xmm1, xmm2
00504354 mulss xmm1, xmm2
00504358 addss xmm0, xmm1
0050435c call 0x4228c0
00504361 cmp dword ptr [edi + 0xaf0], -1
00504368 movaps xmm1, xmm0
0050436b movss xmm7, dword ptr [0xb6c980]
00504373 je 0x5043f2
00504375 movss xmm0, dword ptr [0xb6a974]
0050437d comiss xmm0, xmm1
00504380 ja 0x5043be
00504382 movss xmm2, dword ptr [0xb6a7b0]
0050438a movaps xmm0, xmm1
0050438d subss xmm0, dword ptr [edi + 0xb00]
00504395 andps xmm0, xmm7
00504398 comiss xmm2, xmm0
0050439b jbe 0x5043e0
0050439d movss xmm0, dword ptr [edi + 0xb04]
005043a5 addss xmm0, dword ptr [0xb6a25c]
005043ad comiss xmm0, dword ptr [0xb6a38c]
005043b4 movss dword ptr [edi + 0xb04], xmm0
005043bc jb 0x5043f2
005043be movss xmm0, dword ptr [0xc02fec]
005043c6 movss dword ptr [edi + 0x28c], xmm0
005043ce movss xmm0, dword ptr [0xc02ff0]
005043d6 movss dword ptr [edi + 0x290], xmm0
005043de jmp 0x5043f2
005043e0 movss dword ptr [edi + 0xb00], xmm1
005043e8 mov dword ptr [edi + 0xb04], 0
005043f2 cmp dword ptr [edi + 0x28], 0x28
005043f6 movss xmm0, dword ptr [0xb6a864]
005043fe jne 0x50441f
00504400 mov eax, dword ptr [edi + 0x2c]
00504403 cmp eax, 1
00504406 jne 0x504412
00504408 movss xmm0, dword ptr [0xb6a87c]
00504410 jmp 0x50441f
00504412 cmp eax, 2
00504415 jne 0x50441f
00504417 movss xmm0, dword ptr [0xb6a81c]
0050441f mulss xmm0, dword ptr [edi + 0xb84]
00504427 movss xmm6, dword ptr [edi + 0x2c4]
0050442f ucomiss xmm6, dword ptr [0xb6a18c]
00504436 movss xmm2, dword ptr [esp + 0x38]
0050443c movss xmm5, dword ptr [esp + 0x30]
00504442 movaps xmm3, xmm2
00504445 divss xmm0, xmm1
00504449 xorps xmm3, xmmword ptr [0xb6c9b0]
00504450 movaps xmm4, xmm5
00504453 xorps xmm4, xmmword ptr [0xb6c9b0]
0050445a lahf 
0050445b mulss xmm3, xmm0
0050445f mulss xmm4, xmm0
00504463 test ah, 0x44
00504466 jnp 0x5044a3
00504468 movss xmm1, dword ptr [edi + 0x2f4]
00504470 movaps xmm0, xmm1
00504473 mulss xmm1, xmm4
00504477 mulss xmm0, xmm3
0050447b divss xmm1, xmm6
0050447f divss xmm0, xmm6
00504483 addss xmm1, dword ptr [edi + 0x2bc]
0050448b addss xmm0, dword ptr [edi + 0x2b8]
00504493 movss dword ptr [edi + 0x2bc], xmm1
0050449b movss dword ptr [edi + 0x2b8], xmm0
005044a3 movss xmm3, dword ptr [edi + 0x28c]
005044ab ucomiss xmm3, dword ptr [0xc02fec]
005044b2 lahf 
005044b3 test ah, 0x44
005044b6 jp 0x5044d1
005044b8 movss xmm0, dword ptr [edi + 0x290]
005044c0 ucomiss xmm0, dword ptr [0xc02ff0]
005044c7 lahf 
005044c8 test ah, 0x44
005044cb jnp 0x50458c
005044d1 movss xmm4, dword ptr [edi + 0x2f4]
005044d9 andps xmm2, xmm7
005044dc andps xmm5, xmm7
005044df comiss xmm5, xmm2
005044e2 movss xmm2, dword ptr [0xb6a4c4]
005044ea jbe 0x504539
005044ec ucomiss xmm4, dword ptr [0xb6a614]
005044f3 lahf 
005044f4 test ah, 0x44
005044f7 jnp 0x50450f
005044f9 movaps xmm1, xmm4
005044fc movaps xmm0, xmm4
005044ff addss xmm1, xmm2
00504503 mulss xmm0, xmm2
00504507 subss xmm1, xmm0
0050450b divss xmm2, xmm1
0050450f subss xmm3, dword ptr [edi + 0x294]
00504517 mulss xmm2, dword ptr [edi + 0x2b8]
0050451f mulss xmm3, dword ptr [0xb6a434]
00504527 mulss xmm3, xmm4
0050452b addss xmm3, xmm2
0050452f movss dword ptr [edi + 0x2b8], xmm3
00504537 jmp 0x50458c
00504539 ucomiss xmm4, dword ptr [0xb6a614]
00504540 lahf 
00504541 test ah, 0x44
00504544 jnp 0x50455c
00504546 movaps xmm1, xmm4
00504549 movaps xmm0, xmm4
0050454c addss xmm1, xmm2
00504550 mulss xmm0, xmm2
00504554 subss xmm1, xmm0
00504558 divss xmm2, xmm1
0050455c movss xmm0, dword ptr [edi + 0x290]
00504564 subss xmm0, dword ptr [edi + 0x298]
0050456c mulss xmm2, dword ptr [edi + 0x2bc]
00504574 mulss xmm0, dword ptr [0xb6a434]
0050457c mulss xmm0, xmm4
00504580 addss xmm0, xmm2
00504584 movss dword ptr [edi + 0x2bc], xmm0
0050458c cmp dword ptr [edi + 0x28], 0x28
00504590 movss xmm2, dword ptr [0xb6a8f4]
00504598 jne 0x504b83
0050459e cmp dword ptr [edi + 0x2c], 2
005045a2 jne 0x504b83
005045a8 mov eax, dword ptr [edi + 0xaf0]
005045ae test eax, eax
005045b0 jne 0x50494e
005045b6 cmp dword ptr [edi + 0xe6c], -1
005045bd xorps xmm0, xmm0
005045c0 xorps xmm1, xmm1
005045c3 movss dword ptr [esp + 0x14], xmm0
005045c9 movss dword ptr [esp + 0xc], xmm1
005045cf je 0x5046d4
005045d5 movss xmm2, dword ptr [0xb6a2cc]
005045dd lea eax, [esp + 0x20]
005045e1 push eax
005045e2 mov ecx, edi
005045e4 call 0x6af380
005045e9 movss xmm0, dword ptr [esp + 0x20]
005045ef ucomiss xmm0, dword ptr [0xc02fec]
005045f6 lahf 
005045f7 test ah, 0x44
005045fa jp 0x504613
005045fc movss xmm0, dword ptr [esp + 0x24]
00504602 ucomiss xmm0, dword ptr [0xc02ff0]
00504609 lahf 
0050460a test ah, 0x44
0050460d jnp 0x50478e
00504613 lea edx, [esp + 0x20]
00504617 lea ecx, [esp + 0x54]
0050461b call 0x6593a0
00504620 mov esi, eax
00504622 mov eax, dword ptr [0xbfd65c]
00504627 movss xmm1, dword ptr [esi]
0050462b mulss xmm1, dword ptr [0xb6aa3c]
00504633 mov eax, dword ptr [eax + 0x18190]
00504639 mov ecx, eax
0050463b mov dword ptr [esp + 0x44], eax
0050463f addss xmm1, dword ptr [edi + 0x294]
00504647 movss dword ptr [esp + 0x20], xmm1
0050464d movss dword ptr [esp + 0x38], xmm1
00504653 movss xmm1, dword ptr [esi + 4]
00504658 mulss xmm1, dword ptr [0xb6aa3c]
00504660 addss xmm1, dword ptr [edi + 0x298]
00504668 movss dword ptr [esp + 0x24], xmm1
0050466e push dword ptr [esp + 0x24]
00504672 movss dword ptr [esp + 0x34], xmm1
00504678 push dword ptr [esp + 0x24]
0050467c call 0x7aee40
00504681 test eax, eax
00504683 jne 0x50478e
00504689 movss xmm0, dword ptr [esp + 0x38]
0050468f lea eax, [esp + 0x20]
00504693 mov ecx, dword ptr [esp + 0x44]
00504697 movss dword ptr [esp + 0x20], xmm0
0050469d movss xmm0, dword ptr [esp + 0x30]
005046a3 push eax
005046a4 movss dword ptr [esp + 0x28], xmm0
005046aa call 0x7ce8d0
005046af cmp eax, 0x3b6
005046b4 jge 0x50478e
005046ba movss xmm0, dword ptr [esi]
005046be movss xmm1, dword ptr [esi + 4]
005046c3 movss dword ptr [esp + 0x14], xmm0
005046c9 movss dword ptr [esp + 0xc], xmm1
005046cf jmp 0x50479a
005046d4 mov ecx, dword ptr [esp + 0x1c]
005046d8 test ecx, ecx
005046da je 0x50479a
005046e0 mov eax, dword ptr [ecx + 0x294]
005046e6 movss xmm0, dword ptr [ecx + 0x2b8]
005046ee movss xmm1, dword ptr [ecx + 0x2bc]
005046f6 mov dword ptr [esp + 0x30], eax
005046fa lea eax, [esp + 0x20]
005046fe push eax
005046ff push 0
00504701 mulss xmm0, xmm2
00504705 lea eax, [esp + 0x40]
00504709 push 0
0050470b mulss xmm1, xmm2
0050470f push 0
00504711 addss xmm0, dword ptr [ecx + 0x294]
00504719 push 1
0050471b addss xmm1, dword ptr [ecx + 0x298]
00504723 mov ecx, dword ptr [ecx + 0x298]
00504729 mov dword ptr [esp + 0x48], ecx
0050472d mov ecx, dword ptr [0xbfd65c]
00504733 push eax
00504734 lea eax, [esp + 0x48]
00504738 mov dword ptr [esp + 0x3c], 0
00504740 push eax
00504741 mov ecx, dword ptr [ecx + 0x18190]
00504747 mov dword ptr [esp + 0x3c], 0
0050474f movss dword ptr [esp + 0x54], xmm0
00504755 movss dword ptr [esp + 0x58], xmm1
0050475b call 0x7af4b0
00504760 lea eax, [esp + 0x20]
00504764 push eax
00504765 lea edx, [edi + 0x294]
0050476b lea ecx, [esp + 0x58]
0050476f call 0x502ea0
00504774 add esp, 4
00504777 movss xmm0, dword ptr [eax]
0050477b movss xmm1, dword ptr [eax + 4]
00504780 movss dword ptr [esp + 0x14], xmm0
00504786 movss dword ptr [esp + 0xc], xmm1
0050478c jmp 0x50479a
0050478e movss xmm0, dword ptr [esp + 0x14]
00504794 movss xmm1, dword ptr [esp + 0xc]
0050479a ucomiss xmm0, dword ptr [0xc02fec]
005047a1 lahf 
005047a2 test ah, 0x44
005047a5 jp 0x5047b8
005047a7 ucomiss xmm1, dword ptr [0xc02ff0]
005047ae lahf 
005047af test ah, 0x44
005047b2 jnp 0x504b1c
005047b8 mov esi, dword ptr [edi + 0x90]
005047be test esi, esi
005047c0 je 0x50480c
005047c2 cmp dword ptr [esi + 0x14], 0x10
005047c6 mov eax, esi
005047c8 jb 0x5047cc
005047ca mov eax, dword ptr [esi]
005047cc mov ecx, 0xb40520
005047d1 mov dl, byte ptr [eax]
005047d3 cmp dl, byte ptr [ecx]
005047d5 jne 0x5047f1
005047d7 test dl, dl
005047d9 je 0x5047ed
005047db mov dl, byte ptr [eax + 1]
005047de cmp dl, byte ptr [ecx + 1]
005047e1 jne 0x5047f1
005047e3 add eax, 2
005047e6 add ecx, 2
005047e9 test dl, dl
005047eb jne 0x5047d1
005047ed xor eax, eax
005047ef jmp 0x5047f6
005047f1 sbb eax, eax
005047f3 or eax, 1
005047f6 test eax, eax
005047f8 jne 0x50480c
005047fa cmp byte ptr [esi + 0x34], al
005047fd je 0x50482d
005047ff cmp byte ptr [edi + 0xa0], al
00504805 lea esi, [edi + 0x3c]
00504808 jne 0x50482d
0050480a jmp 0x50480f
0050480c lea esi, [edi + 0x3c]
0050480f push 1
00504811 push 0xb40520
00504816 mov ecx, esi
00504818 call 0x405bb0
0050481d test al, al
0050481f je 0x50482d
00504821 lea ecx, [esi + 0x50]
00504824 call 0x405330
00504829 mov byte ptr [esi + 0x64], 1
0050482d movss xmm2, dword ptr [0xb6aa3c]
00504835 movss xmm0, dword ptr [edi + 0x294]
0050483d subss xmm0, xmm2
00504841 movss xmm3, dword ptr [0xb6ab20]
00504849 mov eax, dword ptr [0xbfd65c]
0050484e divss xmm0, xmm2
00504852 mov edx, dword ptr [eax + 0x18190]
00504858 addss xmm0, dword ptr [0xb6a480]
00504860 cvttss2si esi, xmm0
00504864 movss xmm0, dword ptr [edi + 0x298]
0050486c subss xmm0, xmm3
00504870 divss xmm0, xmm2
00504874 addss xmm0, dword ptr [0xb6a480]
0050487c cvttss2si eax, xmm0
00504880 test esi, esi
00504882 js 0x50489b
00504884 mov ecx, dword ptr [edx + 0xc]
00504887 cmp esi, ecx
00504889 jge 0x50489b
0050488b test eax, eax
0050488d js 0x50489b
0050488f cmp eax, dword ptr [edx + 0x10]
00504892 jge 0x50489b
00504894 imul eax, ecx
00504897 add eax, esi
00504899 jmp 0x5048a1
0050489b mov ecx, dword ptr [edx + 0xc]
0050489e or eax, 0xffffffff
005048a1 cdq 
005048a2 idiv ecx
005048a4 movd xmm0, eax
005048a8 xor eax, eax
005048aa cvtdq2ps xmm0, xmm0
005048ad movd xmm1, edx
005048b1 cvtdq2ps xmm1, xmm1
005048b4 mulss xmm0, xmm2
005048b8 mulss xmm1, xmm2
005048bc addss xmm0, xmm3
005048c0 movss xmm3, dword ptr [esp + 0xc]
005048c6 addss xmm1, xmm2
005048ca movss xmm2, dword ptr [esp + 0x14]
005048d0 movss dword ptr [edi + 0x290], xmm0
005048d8 movaps xmm0, xmm3
005048db andps xmm0, xmmword ptr [0xb6c980]
005048e2 movss dword ptr [edi + 0x28c], xmm1
005048ea movaps xmm1, xmm2
005048ed andps xmm1, xmmword ptr [0xb6c980]
005048f4 mov dword ptr [edi + 0xaf0], 0xffffffff
005048fe movss dword ptr [edi + 0xb08], xmm2
00504906 movss dword ptr [edi + 0xb0c], xmm3
0050490e comiss xmm1, xmm0
00504911 mov dword ptr [edi + 0xb84], 0x3f800000
0050491b xorps xmm0, xmm0
0050491e jbe 0x504938
00504920 comiss xmm0, xmm2
00504923 seta al
00504926 lea eax, [eax*2 + 1]
0050492d mov dword ptr [edi + 0xb10], eax
00504933 jmp 0x504b1c
00504938 comiss xmm0, xmm3
0050493b mov ecx, 2
00504940 cmova eax, ecx
00504943 mov dword ptr [edi + 0xb10], eax
00504949 jmp 0x504b1c
0050494e cmp eax, -1
00504951 jne 0x504ae1
00504957 movss xmm0, dword ptr [edi + 0x2f4]
0050495f mulss xmm0, dword ptr [0xb6a2cc]
00504967 movss xmm1, dword ptr [edi + 0xb84]
0050496f subss xmm1, xmm0
00504973 maxss xmm1, dword ptr [0xb6a2cc]
0050497b movss dword ptr [edi + 0xb84], xmm1
00504983 cmp dword ptr [edi + 0x90], 0
0050498a je 0x504999
0050498c cmp byte ptr [edi + 0xa0], 0
00504993 jne 0x504b1c
00504999 mov esi, dword ptr [edi + 0x90]
0050499f test esi, esi
005049a1 je 0x5049ed
005049a3 cmp dword ptr [esi + 0x14], 0x10
005049a7 mov eax, esi
005049a9 jb 0x5049ad
005049ab mov eax, dword ptr [esi]
005049ad mov ecx, 0xb414b8
005049b2 mov dl, byte ptr [eax]
005049b4 cmp dl, byte ptr [ecx]
005049b6 jne 0x5049d2
005049b8 test dl, dl
005049ba je 0x5049ce
005049bc mov dl, byte ptr [eax + 1]
005049bf cmp dl, byte ptr [ecx + 1]
005049c2 jne 0x5049d2
005049c4 add eax, 2
005049c7 add ecx, 2
005049ca test dl, dl
005049cc jne 0x5049b2
005049ce xor eax, eax
005049d0 jmp 0x5049d7
005049d2 sbb eax, eax
005049d4 or eax, 1
005049d7 test eax, eax
005049d9 jne 0x5049ed
005049db cmp byte ptr [esi + 0x34], al
005049de je 0x504a0e
005049e0 cmp byte ptr [edi + 0xa0], al
005049e6 lea esi, [edi + 0x3c]
005049e9 jne 0x504a0e
005049eb jmp 0x5049f0
005049ed lea esi, [edi + 0x3c]
005049f0 push 1
005049f2 push 0xb414b8
005049f7 mov ecx, esi
005049f9 call 0x405bb0
005049fe test al, al
00504a00 je 0x504a0e
00504a02 lea ecx, [esi + 0x50]
00504a05 call 0x405330
00504a0a mov byte ptr [esi + 0x64], 1
00504a0e movss xmm2, dword ptr [0xb6aa3c]
00504a16 movss xmm0, dword ptr [edi + 0xb08]
00504a1e mulss xmm0, xmm2
00504a22 mov eax, dword ptr [0xbfd65c]
00504a27 movss xmm3, dword ptr [0xb6ab20]
00504a2f addss xmm0, dword ptr [edi + 0x28c]
00504a37 mov edx, dword ptr [eax + 0x18190]
00504a3d subss xmm0, xmm2
00504a41 divss xmm0, xmm2
00504a45 addss xmm0, dword ptr [0xb6a480]
00504a4d cvttss2si esi, xmm0
00504a51 movss xmm0, dword ptr [edi + 0xb0c]
00504a59 mulss xmm0, xmm2
00504a5d addss xmm0, dword ptr [edi + 0x290]
00504a65 subss xmm0, xmm3
00504a69 divss xmm0, xmm2
00504a6d addss xmm0, dword ptr [0xb6a480]
00504a75 cvttss2si eax, xmm0
00504a79 test esi, esi
00504a7b js 0x504a94
00504a7d mov ecx, dword ptr [edx + 0xc]
00504a80 cmp esi, ecx
00504a82 jge 0x504a94
00504a84 test eax, eax
00504a86 js 0x504a94
00504a88 cmp eax, dword ptr [edx + 0x10]
00504a8b jge 0x504a94
00504a8d imul eax, ecx
00504a90 add eax, esi
00504a92 jmp 0x504a9a
00504a94 mov ecx, dword ptr [edx + 0xc]
00504a97 or eax, 0xffffffff
00504a9a cdq 
00504a9b idiv ecx
00504a9d movd xmm1, edx
00504aa1 movd xmm0, eax
00504aa5 cvtdq2ps xmm1, xmm1
00504aa8 cvtdq2ps xmm0, xmm0
00504aab mulss xmm1, xmm2
00504aaf mulss xmm0, xmm2
00504ab3 addss xmm1, xmm2
00504ab7 addss xmm0, xmm3
00504abb movss dword ptr [edi + 0x28c], xmm1
00504ac3 movss dword ptr [edi + 0x290], xmm0
00504acb mov dword ptr [edi + 0xaf0], 0xfffffffe
00504ad5 mov dword ptr [edi + 0xb84], 0x3fe66666
00504adf jmp 0x504b1c
00504ae1 cmp eax, -2
00504ae4 jne 0x504b1c
00504ae6 movss xmm1, dword ptr [0xb6a8cc]
00504aee xorps xmm2, xmm2
00504af1 mov ecx, edi
00504af3 call 0x6847e0
00504af8 test eax, eax
00504afa je 0x504b1c
00504afc push ecx
00504afd mov dword ptr [esp], 0x3f333333
00504b04 push 0
00504b06 push 2
00504b08 push ecx
00504b09 mov dword ptr [esp], 0x3ecccccd
00504b10 mov ecx, edi
00504b12 push 0xb9
00504b17 call 0x6ad720
00504b1c mov edx, dword ptr [edi + 0xaf0]
00504b22 test edx, edx
00504b24 js 0x504b83
00504b26 movss xmm0, dword ptr [edi + 0xb84]
00504b2e movss xmm2, dword ptr [0xb6a614]
00504b36 comiss xmm2, xmm0
00504b39 jbe 0x504b5e
00504b3b movss xmm1, dword ptr [edi + 0x2f4]
00504b43 mulss xmm1, dword ptr [0xb6a274]
00504b4b addss xmm1, xmm0
00504b4f movaps xmm0, xmm2
00504b52 minss xmm0, xmm1
00504b56 movss dword ptr [edi + 0xb84], xmm0
00504b5e test edx, edx
00504b60 jle 0x504b83
00504b62 cvttss2si eax, dword ptr [edi + 0x2fc]
00504b6a cvttss2si ecx, dword ptr [edi + 0x2f8]
00504b72 sub ecx, eax
00504b74 xor eax, eax
00504b76 add ecx, edx
00504b78 test ecx, ecx
00504b7a cmovg eax, ecx
00504b7d mov dword ptr [edi + 0xaf0], eax
00504b83 cmp dword ptr [edi + 0x28], 0x35e
00504b8a jne 0x5050bb
00504b90 mov edx, dword ptr [edi + 0xaf4]
00504b96 cmp edx, 0x1e
00504b99 jl 0x5050a1
00504b9f cmp dword ptr [edi + 0xe6c], -1
00504ba6 je 0x504bc3
00504ba8 movss xmm1, dword ptr [0xb6accc]
00504bb0 mov ecx, edi
00504bb2 push 7
00504bb4 push 0
00504bb6 call 0x6a15a0
00504bbb test al, al
00504bbd je 0x5050bb
00504bc3 mov eax, dword ptr [0xbfd65c]
00504bc8 lea esi, [edi + 0x294]
00504bce mov dword ptr [esp + 0x44], esi
00504bd2 mov dword ptr [esp + 0x1c], eax
00504bd6 call 0x6c3d90
00504bdb mov dword ptr [esp + 0x28], eax
00504bdf lea eax, [esp + 0x28]
00504be3 push eax
00504be4 lea eax, [esp + 0x44]
00504be8 mov dword ptr [esp + 0x44], 0
00504bf0 push eax
00504bf1 push 0
00504bf3 push 0xc02fec
00504bf8 push esi
00504bf9 lea eax, [esp + 0x20]
00504bfd mov dword ptr [esp + 0x20], 0xb
00504c05 push eax
00504c06 lea eax, [esp + 0x28]
00504c0a mov dword ptr [esp + 0x28], 0x3e8
00504c12 push eax
00504c13 call 0x800fb0
00504c18 mov ecx, dword ptr [esp + 0x1c]
00504c1c push 0
00504c1e push dword ptr [esp + 0x14]
00504c22 mov ecx, dword ptr [ecx + 0x1c3198]
00504c28 call 0x6c4b30
00504c2d mov esi, eax
00504c2f mov dword ptr [esp + 0x14], esi
00504c33 test esi, esi
00504c35 je 0x504e53
00504c3b call dword ptr [0xa064c0]
00504c41 mov ecx, dword ptr [esi + 0x320]
00504c47 mov dword ptr [esp + 0x20], eax
00504c4b lea eax, [esi + 0x320]
00504c51 mov dword ptr [esi + 0x34], 0
00504c58 mov dword ptr [esi + 0x38], 0
00504c5f test ecx, ecx
00504c61 je 0x504c7d
00504c63 mov dword ptr [esp + 0x38], eax
00504c67 add ecx, 0x324
00504c6d lea eax, [esp + 0x38]
00504c71 push eax
00504c72 call 0x4bc3c0
00504c77 lea eax, [esi + 0x320]
00504c7d push dword ptr [esp + 0x28]
00504c81 mov dword ptr [eax], 0
00504c87 mov ecx, esi
00504c89 mov eax, dword ptr [edi + 0x294]
00504c8f push dword ptr [esp + 0x44]
00504c93 mov dword ptr [esi + 0x294], eax
00504c99 mov eax, dword ptr [edi + 0x298]
00504c9f push dword ptr [esp + 0x14]
00504ca3 mov dword ptr [esi + 0x298], eax
00504ca9 movss xmm0, dword ptr [0xc02fec]
00504cb1 mov eax, dword ptr [esi]
00504cb3 push dword ptr [esp + 0x1c]
00504cb7 movss dword ptr [esi + 0x2b8], xmm0
00504cbf movss xmm0, dword ptr [0xc02ff0]
00504cc7 movss dword ptr [esi + 0x2bc], xmm0
00504ccf call dword ptr [eax + 4]
00504cd2 mov eax, dword ptr [esp + 0x1c]
00504cd6 push esi
00504cd7 mov edx, dword ptr [eax + 0x18190]
00504cdd mov ecx, dword ptr [edx + 0x1214]
00504ce3 lea eax, [ecx + 1]
00504ce6 mov dword ptr [edx + 0x1214], eax
00504cec mov dword ptr [esi + 0x20], ecx
00504cef lea ecx, [edx + 0x1218]
00504cf5 call 0x413280
00504cfa push esi
00504cfb call 0x6d94d0
00504d00 test al, al
00504d02 je 0x504d0b
00504d04 push ecx
00504d05 push esi
00504d06 call 0x6d9590
00504d0b cmp byte ptr [esi + 0x16a], 0
00504d12 je 0x504e43
00504d18 mov ecx, dword ptr [esp + 0x1c]
00504d1c mov eax, dword ptr [ecx + 0x283c20]
00504d22 cmp eax, dword ptr [ecx + 0x283c24]
00504d28 je 0x504e43
00504d2e mov eax, dword ptr [esi + 0x28]
00504d31 mov dword ptr [esp + 0x28], eax
00504d35 mov eax, dword ptr [esi + 0x2c]
00504d38 mov dword ptr [esp + 0x2c], eax
00504d3c lea eax, [ecx + 0x283c48]
00504d42 lea ecx, [esp + 0x28]
00504d46 mov dword ptr [esp + 0x38], eax
00504d4a push ecx
00504d4b lea ecx, [esp + 0x34]
00504d4f push ecx
00504d50 mov ecx, eax
00504d52 call 0x937c80
00504d57 mov ecx, dword ptr [esp + 0x38]
00504d5b mov eax, dword ptr [ecx]
00504d5d mov dword ptr [esp + 0x38], eax
00504d61 cmp dword ptr [esp + 0x30], eax
00504d65 jne 0x504d91
00504d67 mov eax, dword ptr [esi + 0x28]
00504d6a mov dword ptr [esp + 0x28], eax
00504d6e lea eax, [esp + 0x28]
00504d72 push eax
00504d73 lea eax, [esp + 0x34]
00504d77 mov dword ptr [esp + 0x30], 0xffffffff
00504d7f push eax
00504d80 call 0x937c80
00504d85 mov ecx, dword ptr [esp + 0x38]
00504d89 cmp dword ptr [eax], ecx
00504d8b je 0x504e43
00504d91 mov esi, dword ptr [0xbfd65c]
00504d97 xor edx, edx
00504d99 mov dword ptr [esp + 0x10], edx
00504d9d mov eax, dword ptr [esi + 0x1ba54]
00504da3 sub eax, dword ptr [esi + 0x1ba50]
00504da9 sar eax, 2
00504dac test eax, eax
00504dae je 0x504e3f
00504db4 mov edi, dword ptr [esp + 0x14]
00504db8 nop dword ptr [eax + eax]
00504dc0 mov ecx, dword ptr [esi + 0x1ba54]
00504dc6 mov eax, ecx
00504dc8 sub eax, dword ptr [esi + 0x1ba50]
00504dce test eax, 0xfffffffc
00504dd3 jne 0x504dee
00504dd5 push 0xb3f4d0
00504dda push 3
00504ddc call 0x95e330
00504de1 mov ecx, dword ptr [esi + 0x1ba54]
00504de7 add esp, 8
00504dea mov edx, dword ptr [esp + 0x10]
00504dee mov eax, dword ptr [esi + 0x1ba50]
00504df4 sub ecx, eax
00504df6 sar ecx, 2
00504df9 cmp edx, ecx
00504dfb jae 0x504e00
00504dfd lea eax, [eax + edx*4]
00504e00 mov ecx, dword ptr [eax]
00504e02 push 0xc02fec
00504e07 push dword ptr [esp + 0x48]
00504e0b add ecx, 0x1ec0
00504e11 push edi
00504e12 push 6
00504e14 call 0x935fd0
00504e19 mov esi, dword ptr [0xbfd65c]
00504e1f mov edx, dword ptr [esp + 0x10]
00504e23 inc edx
00504e24 mov dword ptr [esp + 0x10], edx
00504e28 mov eax, dword ptr [esi + 0x1ba54]
00504e2e sub eax, dword ptr [esi + 0x1ba50]
00504e34 sar eax, 2
00504e37 cmp edx, eax
00504e39 jb 0x504dc0
00504e3b mov edi, dword ptr [esp + 0x4c]
00504e3f mov esi, dword ptr [esp + 0x14]
00504e43 call dword ptr [0xa064c0]
00504e49 sub eax, dword ptr [esp + 0x20]
00504e4d add dword ptr [0xbffe0c], eax
00504e53 lea eax, [esi + 0x314]
00504e59 mov dword ptr [esi + 0x2a4], 0
00504e63 mov dword ptr [esi + 0x2a8], 0xc1600000
00504e6d mov ecx, dword ptr [eax]
00504e6f test ecx, ecx
00504e71 je 0x504e8d
00504e73 mov dword ptr [esp + 0x20], eax
00504e77 add ecx, 0x324
00504e7d lea eax, [esp + 0x20]
00504e81 push eax
00504e82 call 0x4bc3c0
00504e87 lea eax, [esi + 0x314]
00504e8d push eax
00504e8e mov ecx, edi
00504e90 mov dword ptr [eax], edi
00504e92 call 0x4bae70
00504e97 mov ecx, edi
00504e99 mov dword ptr [esi + 0x3a0], 1
00504ea3 mov dword ptr [esi + 0x2b0], 0x40a00000
00504ead call 0x695680
00504eb2 lea esi, [edi + 0x294]
00504eb8 movss xmm1, dword ptr [eax + 0x294]
00504ec0 subss xmm1, dword ptr [esi]
00504ec4 movss xmm2, dword ptr [eax + 0x298]
00504ecc subss xmm2, dword ptr [esi + 4]
00504ed1 movaps xmm0, xmm1
00504ed4 movss dword ptr [esp + 0x10], xmm1
00504eda mulss xmm0, xmm1
00504ede movaps xmm1, xmm2
00504ee1 movss dword ptr [esp + 0x1c], xmm2
00504ee7 mulss xmm1, xmm2
00504eeb addss xmm0, xmm1
00504eef call 0x4228c0
00504ef4 comiss xmm0, dword ptr [0xb6a18c]
00504efb jbe 0x504f2c
00504efd movss xmm1, dword ptr [0xb6a614]
00504f05 divss xmm1, xmm0
00504f09 movss xmm2, dword ptr [esp + 0x10]
00504f0f movaps xmm0, xmm1
00504f12 mulss xmm2, xmm0
00504f16 movss xmm0, dword ptr [esp + 0x1c]
00504f1c mulss xmm0, xmm1
00504f20 movss dword ptr [esp + 0x10], xmm2
00504f26 movss dword ptr [esp + 0x1c], xmm0
00504f2c cmp dword ptr [edi + 0xe6c], -1
00504f33 jne 0x504f4f
00504f35 movss xmm0, dword ptr [0xc02fec]
00504f3d movss dword ptr [edi + 0xe70], xmm0
00504f45 movss xmm0, dword ptr [0xc02ff0]
00504f4d jmp 0x504f77
00504f4f movss xmm2, dword ptr [0xb6a2cc]
00504f57 lea eax, [esp + 0x20]
00504f5b push eax
00504f5c mov ecx, edi
00504f5e call 0x6af380
00504f63 movss xmm0, dword ptr [esp + 0x20]
00504f69 movss dword ptr [edi + 0xe70], xmm0
00504f71 movss xmm0, dword ptr [esp + 0x24]
00504f77 movss dword ptr [edi + 0xe74], xmm0
00504f7f movss xmm1, dword ptr [edi + 0xe70]
00504f87 ucomiss xmm1, dword ptr [0xc02fec]
00504f8e lahf 
00504f8f test ah, 0x44
00504f92 jp 0x504fa1
00504f94 ucomiss xmm0, dword ptr [0xc02ff0]
00504f9b lahf 
00504f9c test ah, 0x44
00504f9f jnp 0x504fae
00504fa1 movaps xmm0, xmm1
00504fa4 movss xmm1, dword ptr [edi + 0xe74]
00504fac jmp 0x504fba
00504fae movss xmm0, dword ptr [esp + 0x10]
00504fb4 movss xmm1, dword ptr [esp + 0x1c]
00504fba mulss xmm0, dword ptr [0xb6a974]
00504fc2 lea ecx, [esp + 0xe0]
00504fc9 mulss xmm1, dword ptr [0xb6a974]
00504fd1 movss dword ptr [esp + 0x20], xmm0
00504fd7 movss dword ptr [esp + 0x24], xmm1
00504fdd call 0x430d70
00504fe2 push eax
00504fe3 push 0
00504fe5 lea eax, [esp + 0x28]
00504fe9 mov ecx, edi
00504feb push eax
00504fec push esi
00504fed call 0x6a1a20
00504ff2 movss xmm0, dword ptr [0xb6a614]
00504ffa mov eax, dword ptr [edi + 0xbb4]
00505000 movss dword ptr [esp + 0x10], xmm0
00505006 cmp eax, 0x12
00505009 jne 0x505015
0050500b movss xmm0, dword ptr [0xb6a6f0]
00505013 jmp 0x505022
00505015 cmp eax, 0x13
00505018 jne 0x505028
0050501a movss xmm0, dword ptr [0xb6a480]
00505022 movss dword ptr [esp + 0x10], xmm0
00505028 mov esi, dword ptr [0xbfd680]
0050502e lea ecx, [esp + 0x28]
00505032 mov dword ptr [esp + 0x28], 0xb2
0050503a call 0x8b1340
0050503f movss xmm0, dword ptr [esp + 0x10]
00505045 sub esp, 8
00505048 mov dword ptr [esp + 4], 0
00505050 movss dword ptr [esp], xmm0
00505055 push 0
00505057 push 2
00505059 push ecx
0050505a mov dword ptr [esp], 0x3f800000
00505061 lea ecx, [esi + 0x29de0]
00505067 push dword ptr [esp + 0x3c]
0050506b call 0x888de0
00505070 push 1
00505072 push 0xb400ac
00505077 lea ecx, [edi + 0x3c]
0050507a call 0x405bb0
0050507f test al, al
00505081 je 0x505095
00505083 lea ecx, [edi + 0x8c]
00505089 call 0x405330
0050508e mov byte ptr [edi + 0xa0], 1
00505095 mov dword ptr [edi + 0xaf4], 0
0050509f jmp 0x5050bb
005050a1 cvttss2si ecx, dword ptr [edi + 0x2fc]
005050a9 cvttss2si eax, dword ptr [edi + 0x2f8]
005050b1 sub ecx, eax
005050b3 add ecx, edx
005050b5 mov dword ptr [edi + 0xaf4], ecx
005050bb cmp dword ptr [edi + 0x2c], 1
005050bf mov ecx, 2
005050c4 mov esi, 5
005050c9 cmove esi, ecx
005050cc cmp dword ptr [edi + 0x2c], ecx
005050cf jne 0x5050e5
005050d1 cmp dword ptr [edi + 0xaf0], -2
005050d8 mov esi, 4
005050dd mov eax, 1
005050e2 cmove esi, eax
005050e5 mov eax, dword ptr [edi + 0x28]
005050e8 cmp eax, 0x28
005050eb je 0x5050f8
005050ed cmp eax, 0x35e
005050f2 jne 0x5054c6
005050f8 mov eax, dword ptr [edi + 0x160]
005050fe and eax, 0x4000
00505103 or eax, 0
00505106 jne 0x5054c6
0050510c mov ecx, dword ptr [0xbfd65c]
00505112 call 0x6d0380
00505117 test al, al
00505119 jne 0x5054c6
0050511f mov eax, dword ptr [0xbfd65c]
00505124 mov eax, dword ptr [eax + 0x1a30dc]
0050512a add eax, dword ptr [edi + 0x20]
0050512d cdq 
0050512e idiv esi
00505130 test edx, edx
00505132 jne 0x5054c6
00505138 mov eax, dword ptr [edi + 0x2c]
0050513b cmp eax, 1
0050513e jne 0x5051e6
00505144 call 0x6c3d90
00505149 mov ecx, dword ptr [0xbfd65c]
0050514f push 0
00505151 push eax
00505152 push 0
00505154 push edi
00505155 push 0xc02fec
0050515a lea eax, [edi + 0x294]
00505160 push eax
00505161 push 0x16
00505163 push 0x3e8
00505168 call 0x6d0ca0
0050516d push 0
0050516f push 0xbeaaec
00505174 push 0xbeab18
00505179 push 0
0050517b push eax
0050517c call 0x9ec34c
00505181 movss xmm1, dword ptr [0xbc7a28]
00505189 add esp, 0x14
0050518c movss xmm0, dword ptr [0xbc7a2c]
00505194 mulss xmm1, dword ptr [0xb6a2cc]
0050519c mov dword ptr [eax + 0x3c8], 0x3f400000
005051a6 mulss xmm0, dword ptr [0xb6a2cc]
005051ae mov dword ptr [eax + 0x3ac], 0x14
005051b8 movss dword ptr [eax + 0xd8], xmm1
005051c0 mov dword ptr [eax + 0x3b0], 0x14
005051ca movss dword ptr [eax + 0xdc], xmm0
005051d2 pop edi
005051d3 pop esi
005051d4 mov ecx, dword ptr [esp + 0x184]
005051db xor ecx, esp
005051dd call 0x9eacd7
005051e2 mov esp, ebp
005051e4 pop ebp
005051e5 ret 
005051e6 cmp eax, 2
005051e9 jne 0x505473
005051ef movss xmm1, dword ptr [0xb6a19c]
005051f7 cmp esi, 1
005051fa jne 0x5053e5
00505200 movss xmm0, dword ptr [edi + 0xb08]
00505208 xorps xmm0, xmmword ptr [0xb6c9b0]
0050520f movss dword ptr [esp + 0x38], xmm0
00505215 movss xmm0, dword ptr [edi + 0xb0c]
0050521d xorps xmm0, xmmword ptr [0xb6c9b0]
00505224 movss dword ptr [esp + 0x30], xmm0
0050522a call 0x6c3d90
0050522f movd xmm0, eax
00505233 cvtdq2pd xmm0, xmm0
00505237 shr eax, 0x1f
0050523a addsd xmm0, qword ptr [eax*8 + 0xb6c940]
00505243 cvtpd2ps xmm0, xmm0
00505247 mulss xmm0, xmm1
0050524b mulss xmm0, dword ptr [0xb6a940]
00505253 addss xmm0, dword ptr [0xb6a7b0]
0050525b movss dword ptr [esp + 0x44], xmm0
00505261 call 0x6c3d90
00505266 mov esi, eax
00505268 call 0x6c3d90
0050526d movd xmm0, eax
00505271 cvtdq2pd xmm0, xmm0
00505275 shr eax, 0x1f
00505278 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
00505281 cvtpd2ps xmm0, xmm0
00505285 mulss xmm0, xmm1
00505289 mulss xmm0, dword ptr [0xb6aa3c]
00505291 subss xmm0, dword ptr [0xb6a9c8]
00505299 mulss xmm0, dword ptr [0xb6a230]
005052a1 movss dword ptr [esp + 0x20], xmm0
005052a7 call 0x411fe0
005052ac movss dword ptr [esp + 0x4c], xmm0
005052b2 movss xmm0, dword ptr [esp + 0x20]
005052b8 call 0x412010
005052bd movss xmm6, dword ptr [esp + 0x38]
005052c3 lea eax, [esp + 0x20]
005052c7 movss xmm5, dword ptr [esp + 0x30]
005052cd movaps xmm1, xmm0
005052d0 movss xmm2, dword ptr [esp + 0x4c]
005052d6 mulss xmm1, xmm5
005052da mov ecx, dword ptr [0xbfd65c]
005052e0 mulss xmm2, xmm6
005052e4 push 0
005052e6 push esi
005052e7 push 1
005052e9 subss xmm2, xmm1
005052ed movaps xmm1, xmm6
005052f0 mulss xmm6, dword ptr [0xb6a8cc]
005052f8 push 0
005052fa mulss xmm1, xmm0
005052fe movaps xmm0, xmm5
00505301 push eax
00505302 mulss xmm0, dword ptr [esp + 0x60]
00505308 lea eax, [esp + 0x60]
0050530c push eax
0050530d mulss xmm5, dword ptr [0xb6a8cc]
00505315 push 0x63
00505317 addss xmm6, dword ptr [edi + 0x294]
0050531f mulss xmm2, dword ptr [esp + 0x60]
00505325 addss xmm1, xmm0
00505329 push 0x3e8
0050532e addss xmm5, dword ptr [edi + 0x298]
00505336 movss dword ptr [esp + 0x40], xmm2
0050533c mulss xmm1, dword ptr [esp + 0x64]
00505342 movss dword ptr [esp + 0x6c], xmm6
00505348 movss dword ptr [esp + 0x70], xmm5
0050534e movss dword ptr [esp + 0x44], xmm1
00505354 call 0x6d0ca0
00505359 mov esi, eax
0050535b call 0x6c3d90
00505360 movd xmm0, eax
00505364 cvtdq2pd xmm0, xmm0
00505368 shr eax, 0x1f
0050536b addsd xmm0, qword ptr [eax*8 + 0xb6c940]
00505374 cvtpd2ps xmm1, xmm0
00505378 mulss xmm1, dword ptr [0xb6a19c]
00505380 mulss xmm1, dword ptr [0xb6a6f0]
00505388 addss xmm1, dword ptr [0xb6a614]
00505390 movaps xmm0, xmm1
00505393 mulss xmm1, dword ptr [esi + 0xdc]
0050539b mulss xmm0, dword ptr [esi + 0xd8]
005053a3 movss dword ptr [esi + 0xd8], xmm0
005053ab movss xmm3, dword ptr [0xb6a214]
005053b3 push ecx
005053b4 movss dword ptr [esi + 0xdc], xmm1
005053bc lea ecx, [esp + 0xb8]
005053c3 movaps xmm2, xmm3
005053c6 mov dword ptr [esp], 0x3f800000
005053cd movaps xmm1, xmm3
005053d0 call 0x4325d0
005053d5 push eax
005053d6 lea ecx, [esi + 0x3c]
005053d9 call 0x402370
005053de mov eax, dword ptr [esi]
005053e0 mov ecx, esi
005053e2 call dword ptr [eax + 0xc]
005053e5 call 0x6c3d90
005053ea mov ecx, dword ptr [0xbfd65c]
005053f0 push 0
005053f2 push eax
005053f3 push 0
005053f5 push edi
005053f6 push 0xc02fec
005053fb lea eax, [edi + 0x294]
00505401 push eax
00505402 push 0x1a
00505404 push 0x3e8
00505409 call 0x6d0ca0
0050540e push 0
00505410 push 0xbeaaec
00505415 push 0xbeab18
0050541a push 0
0050541c push eax
0050541d call 0x9ec34c
00505422 movss xmm1, dword ptr [0xbc7a28]
0050542a add esp, 0x14
0050542d movss xmm0, dword ptr [0xbc7a2c]
00505435 mulss xmm1, dword ptr [0xb6a2cc]
0050543d mov dword ptr [eax + 0x3c8], 0x3f400000
00505447 mulss xmm0, dword ptr [0xb6a2cc]
0050544f mov dword ptr [eax + 0x3ac], 0x96
00505459 movss dword ptr [eax + 0xd8], xmm1
00505461 mov dword ptr [eax + 0x3b0], 0x96
0050546b movss dword ptr [eax + 0xdc], xmm0
00505473 call 0x6c3d90
00505478 push ecx
00505479 mov ecx, edi
0050547b movd xmm0, eax
0050547f cvtdq2pd xmm0, xmm0
00505483 shr eax, 0x1f
00505486 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
0050548f cvtpd2ps xmm0, xmm0
00505493 mulss xmm0, dword ptr [0xb6a19c]
0050549b mulss xmm0, dword ptr [0xb6a50c]
005054a3 movss dword ptr [esp], xmm0
005054a8 call 0x68d7b0
005054ad push 1
005054af push 0
005054b1 push 0xff
005054b6 mov edx, dword ptr [eax]
005054b8 lea ecx, [edi + 0x1dc]
005054be push -1
005054c0 push ecx
005054c1 mov ecx, eax
005054c3 call dword ptr [edx + 0x38]
005054c6 mov ecx, dword ptr [esp + 0x18c]
005054cd pop edi
005054ce pop esi
005054cf xor ecx, esp
005054d1 call 0x9eacd7
005054d6 mov esp, ebp
005054d8 pop ebp
005054d9 ret 
