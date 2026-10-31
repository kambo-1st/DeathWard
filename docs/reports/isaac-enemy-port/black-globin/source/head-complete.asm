00500140 push ebp
00500141 mov ebp, esp
00500143 and esp, 0xfffffff8
00500146 sub esp, 0x88
0050014c mov eax, dword ptr [0xbaa3b4]
00500151 xor eax, esp
00500153 mov dword ptr [esp + 0x84], eax
0050015a push esi
0050015b push edi
0050015c mov edi, ecx
0050015e cmp dword ptr [edi + 0xab4], 0
00500165 jne 0x5001e5
00500167 cmp dword ptr [edi + 0x28], 0x12d
0050016e mov dword ptr [edi + 0xab4], 4
00500178 jne 0x500f84
0050017e movaps xmm2, xmmword ptr [0xb6be20]
00500185 lea ecx, [edi + 0x1dc]
0050018b lea eax, [esp + 0x34]
0050018f mov dword ptr [esp + 0x54], 0
00500197 mov dword ptr [esp + 0x58], 0x3e48c8ca
0050019f xorps xmm1, xmm1
005001a2 mov dword ptr [esp + 0x5c], 0
005001aa cmp ecx, eax
005001ac je 0x5001c7
005001ae movq xmm0, qword ptr [esp + 0x54]
005001b4 mov eax, dword ptr [esp + 0x5c]
005001b8 movq qword ptr [ecx + 0x20], xmm0
005001bd movups xmmword ptr [ecx], xmm2
005001c0 mov dword ptr [ecx + 0x28], eax
005001c3 movups xmmword ptr [ecx + 0x10], xmm1
005001c7 mov dword ptr [edi + 0x17c], 3
005001d1 pop edi
005001d2 pop esi
005001d3 mov ecx, dword ptr [esp + 0x84]
005001da xor ecx, esp
005001dc call 0x9eacd7
005001e1 mov esp, ebp
005001e3 pop ebp
005001e4 ret 
005001e5 mov eax, dword ptr [edi + 0x160]
005001eb and eax, 0x4000
005001f0 or eax, 0
005001f3 jne 0x50029e
005001f9 mov ecx, dword ptr [0xbfd65c]
005001ff call 0x6d0380
00500204 test al, al
00500206 jne 0x50029e
0050020c movss xmm0, dword ptr [edi + 0x2fc]
00500214 xorps xmm2, xmm2
00500217 addss xmm0, xmm2
0050021b divss xmm0, dword ptr [0xb6ae7c]
00500223 cvttss2si ecx, xmm0
00500227 movss xmm0, dword ptr [edi + 0x2f8]
0050022f addss xmm0, xmm2
00500233 divss xmm0, dword ptr [0xb6ae7c]
0050023b cvttss2si eax, xmm0
0050023f sub eax, ecx
00500241 je 0x50029e
00500243 call 0x6c3d90
00500248 push ecx
00500249 mov ecx, edi
0050024b movd xmm0, eax
0050024f cvtdq2pd xmm0, xmm0
00500253 shr eax, 0x1f
00500256 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
0050025f cvtpd2ps xmm0, xmm0
00500263 mulss xmm0, dword ptr [0xb6a19c]
0050026b mulss xmm0, dword ptr [0xb6a424]
00500273 addss xmm0, dword ptr [0xb6a350]
0050027b movss dword ptr [esp], xmm0
00500280 call 0x68d7b0
00500285 push 1
00500287 push 0
00500289 push 0xff
0050028e mov edx, dword ptr [eax]
00500290 lea ecx, [edi + 0x1dc]
00500296 push -1
00500298 push ecx
00500299 mov ecx, eax
0050029b call dword ptr [edx + 0x38]
0050029e movss xmm1, dword ptr [0xb6aa3c]
005002a6 movss xmm0, dword ptr [edi + 0x294]
005002ae subss xmm0, xmm1
005002b2 movss xmm2, dword ptr [0xb6a480]
005002ba mov eax, dword ptr [0xbfd65c]
005002bf divss xmm0, xmm1
005002c3 mov ecx, dword ptr [eax + 0x18190]
005002c9 addss xmm0, xmm2
005002cd cvttss2si esi, xmm0
005002d1 test esi, esi
005002d3 js 0x500325
005002d5 mov eax, dword ptr [ecx + 0xc]
005002d8 cmp esi, eax
005002da jge 0x500325
005002dc movss xmm0, dword ptr [edi + 0x298]
005002e4 subss xmm0, dword ptr [0xb6ab20]
005002ec divss xmm0, xmm1
005002f0 addss xmm0, xmm2
005002f4 cvttss2si edx, xmm0
005002f8 test edx, edx
005002fa js 0x500325
005002fc cmp edx, dword ptr [ecx + 0x10]
005002ff jge 0x500325
00500301 imul eax, edx
00500304 add eax, esi
00500306 cmp eax, 0x1bf
0050030b ja 0x500325
0050030d cmp dword ptr [ecx + eax*4 + 0x76c], 0x3b6
00500318 jg 0x500325
0050031a mov dword ptr [ecx + eax*4 + 0x76c], 0x384
00500325 mov esi, dword ptr [edi + 0x70]
00500328 test esi, esi
0050032a je 0x50037b
0050032c cmp dword ptr [esi + 0x14], 0x10
00500330 mov eax, esi
00500332 jb 0x500336
00500334 mov eax, dword ptr [esi]
00500336 mov ecx, 0xb41264
0050033b nop dword ptr [eax + eax]
00500340 mov dl, byte ptr [eax]
00500342 cmp dl, byte ptr [ecx]
00500344 jne 0x500360
00500346 test dl, dl
00500348 je 0x50035c
0050034a mov dl, byte ptr [eax + 1]
0050034d cmp dl, byte ptr [ecx + 1]
00500350 jne 0x500360
00500352 add eax, 2
00500355 add ecx, 2
00500358 test dl, dl
0050035a jne 0x500340
0050035c xor eax, eax
0050035e jmp 0x500365
00500360 sbb eax, eax
00500362 or eax, 1
00500365 test eax, eax
00500367 jne 0x50037b
00500369 cmp byte ptr [esi + 0x34], al
0050036c je 0x50039c
0050036e cmp byte ptr [edi + 0x80], al
00500374 lea esi, [edi + 0x3c]
00500377 jne 0x50039c
00500379 jmp 0x50037e
0050037b lea esi, [edi + 0x3c]
0050037e push 1
00500380 push 0xb41264
00500385 mov ecx, esi
00500387 call 0x405740
0050038c test al, al
0050038e je 0x50039c
00500390 lea ecx, [esi + 0x30]
00500393 call 0x405330
00500398 mov byte ptr [esi + 0x44], 1
0050039c lea ecx, [edi + 0x364]
005003a2 call 0x7a6e20
005003a7 cmp dword ptr [edi + 0xab4], 4
005003ae jne 0x500bfc
005003b4 mov eax, dword ptr [edi + 0x28]
005003b7 cmp eax, 0x117
005003bc jne 0x50040c
005003be push 1
005003c0 push 0x384
005003c5 sub esp, 8
005003c8 lea eax, [esp + 0x3c]
005003cc mov ecx, edi
005003ce mov dword ptr [esp + 4], 0x3f000000
005003d6 mov dword ptr [esp], 0
005003dd push eax
005003de call 0x695a30
005003e3 push eax
005003e4 lea ecx, [edi + 0x364]
005003ea call 0x7a3650
005003ef movss xmm0, dword ptr [edi + 0x2b8]
005003f7 comiss xmm0, dword ptr [0xb6a18c]
005003fe seta al
00500401 mov byte ptr [edi + 0x13c], al
00500407 jmp 0x500dcd
0050040c cmp eax, 0x12d
00500411 jne 0x5008e9
00500417 movss xmm2, dword ptr [edi + 0x2f4]
0050041f ucomiss xmm2, dword ptr [0xb6a614]
00500426 movss xmm1, dword ptr [0xb6a560]
0050042e lahf 
0050042f test ah, 0x44
00500432 jnp 0x500447
00500434 movaps xmm0, xmm2
00500437 mulss xmm2, xmm1
0050043b addss xmm0, xmm1
0050043f subss xmm0, xmm2
00500443 divss xmm1, xmm0
00500447 cvttss2si eax, dword ptr [edi + 0x2fc]
0050044f cvttss2si ecx, dword ptr [edi + 0x2f8]
00500457 movaps xmm0, xmm1
0050045a mulss xmm1, dword ptr [edi + 0x2bc]
00500462 sub ecx, eax
00500464 mulss xmm0, dword ptr [edi + 0x2b8]
0050046c movss dword ptr [edi + 0x2bc], xmm1
00500474 movss dword ptr [edi + 0x2b8], xmm0
0050047c add dword ptr [edi + 0x360], ecx
00500482 js 0x500491
00500484 cmp byte ptr [edi + 0x188], 0
0050048b je 0x500518
00500491 call 0x6c3d90
00500496 xor edx, edx
00500498 mov ecx, 0x5a
0050049d div ecx
0050049f mov dword ptr [edi + 0x360], edx
005004a5 call 0x6c3d90
005004aa and eax, 3
005004ad lea ecx, [esp + 0x2c]
005004b1 mov edx, eax
005004b3 call 0x659400
005004b8 movss xmm0, dword ptr [0xb6a554]
005004c0 mov esi, eax
005004c2 call 0x411fe0
005004c7 movss dword ptr [esp + 0xc], xmm0
005004cd movss xmm0, dword ptr [0xb6a554]
005004d5 call 0x412010
005004da movss xmm1, dword ptr [esi]
005004de movaps xmm2, xmm0
005004e1 movss xmm5, dword ptr [esi + 4]
005004e6 movaps xmm3, xmm1
005004e9 mulss xmm3, dword ptr [esp + 0xc]
005004ef movaps xmm0, xmm5
005004f2 mulss xmm5, dword ptr [esp + 0xc]
005004f8 mulss xmm0, xmm2
005004fc mulss xmm1, xmm2
00500500 subss xmm3, xmm0
00500504 addss xmm5, xmm1
00500508 movss dword ptr [edi + 0x28c], xmm3
00500510 movss dword ptr [edi + 0x290], xmm5
00500518 cmp dword ptr [edi + 0xe6c], -1
0050051f je 0x50065f
00500525 lea eax, [esp + 0x2c]
00500529 xorps xmm2, xmm2
0050052c push eax
0050052d mov ecx, edi
0050052f call 0x6af0c0
00500534 lea ecx, [edi + 0x28c]
0050053a push 0xc02fec
0050053f movss xmm2, dword ptr [eax]
00500543 movss dword ptr [ecx], xmm2
00500547 movss xmm3, dword ptr [eax + 4]
0050054c movss dword ptr [esp + 0x28], xmm2
00500552 movss dword ptr [esp + 0x20], xmm3
00500558 movss dword ptr [ecx + 4], xmm3
0050055d call 0x962ca0
00500562 test al, al
00500564 je 0x50065f
0050056a movaps xmm1, xmm3
0050056d movaps xmm0, xmm2
00500570 mulss xmm1, xmm3
00500574 mulss xmm0, xmm2
00500578 addss xmm0, xmm1
0050057c call 0x4228c0
00500581 movss dword ptr [esp + 0x14], xmm0
00500587 movss xmm0, dword ptr [0xb6ae3c]
0050058f call 0x411fe0
00500594 movss dword ptr [esp + 0xc], xmm0
0050059a movss xmm0, dword ptr [0xb6ae3c]
005005a2 call 0x412010
005005a7 movss xmm3, dword ptr [esp + 0xc]
005005ad lea edx, [esp + 0x1c]
005005b1 movss xmm5, dword ptr [esp + 0x1c]
005005b7 lea ecx, [esp + 0x2c]
005005bb movss xmm4, dword ptr [esp + 0x24]
005005c1 movaps xmm2, xmm0
005005c4 movaps xmm1, xmm3
005005c7 movaps xmm0, xmm5
005005ca mulss xmm1, xmm4
005005ce mulss xmm0, xmm2
005005d2 mulss xmm3, xmm5
005005d6 mulss xmm4, xmm2
005005da subss xmm1, xmm0
005005de addss xmm3, xmm4
005005e2 movss dword ptr [esp + 0x1c], xmm1
005005e8 movss dword ptr [esp + 0x20], xmm3
005005ee call 0x6593a0
005005f3 movss xmm0, dword ptr [0xb6a554]
005005fb mov esi, eax
005005fd call 0x411fe0
00500602 movss dword ptr [esp + 0x1c], xmm0
00500608 movss xmm0, dword ptr [0xb6a554]
00500610 call 0x412010
00500615 movss xmm1, dword ptr [esi]
00500619 movaps xmm2, xmm0
0050061c movss xmm5, dword ptr [esi + 4]
00500621 movaps xmm3, xmm1
00500624 mulss xmm3, dword ptr [esp + 0x1c]
0050062a movaps xmm0, xmm5
0050062d mulss xmm5, dword ptr [esp + 0x1c]
00500633 mulss xmm0, xmm2
00500637 mulss xmm1, xmm2
0050063b subss xmm3, xmm0
0050063f addss xmm5, xmm1
00500643 mulss xmm3, dword ptr [esp + 0x14]
00500649 mulss xmm5, dword ptr [esp + 0x14]
0050064f movss dword ptr [edi + 0x28c], xmm3
00500657 movss dword ptr [edi + 0x290], xmm5
0050065f movss xmm2, dword ptr [edi + 0x290]
00500667 xor edx, edx
00500669 movss xmm0, dword ptr [edi + 0x28c]
00500671 mov ecx, 7
00500676 mulss xmm0, dword ptr [0xb6a480]
0050067e mulss xmm2, dword ptr [0xb6a480]
00500686 movss xmm1, dword ptr [edi + 0x2f4]
0050068e mulss xmm0, xmm1
00500692 mulss xmm2, xmm1
00500696 addss xmm0, dword ptr [edi + 0x2b8]
0050069e movss xmm1, dword ptr [0xb6a928]
005006a6 addss xmm2, dword ptr [edi + 0x2bc]
005006ae movss dword ptr [edi + 0x2b8], xmm0
005006b6 movss dword ptr [edi + 0x2bc], xmm2
005006be mov eax, dword ptr [edi + 0x20]
005006c1 div ecx
005006c3 mov ecx, edi
005006c5 movd xmm0, edx
005006c9 cvtdq2pd xmm0, xmm0
005006cd shr edx, 0x1f
005006d0 addsd xmm0, qword ptr [edx*8 + 0xb6c940]
005006d9 cvtpd2ps xmm2, xmm0
005006dd call 0x6847e0
005006e2 test eax, eax
005006e4 je 0x500dcd
005006ea cmp dword ptr [edi + 0xe6c], -1
005006f1 jne 0x500dcd
005006f7 push 0
005006f9 push 0x1000a00
005006fe mov ecx, edi
00500700 call 0x4122f0
00500705 test al, al
00500707 jne 0x500dcd
0050070d call 0x6c3d90
00500712 mov ecx, edi
00500714 movd xmm0, eax
00500718 cvtdq2pd xmm0, xmm0
0050071c shr eax, 0x1f
0050071f addsd xmm0, qword ptr [eax*8 + 0xb6c940]
00500728 cvtpd2ps xmm0, xmm0
0050072c mulss xmm0, dword ptr [0xb6a19c]
00500734 mulss xmm0, dword ptr [0xb6a9b0]
0050073c movss dword ptr [esp + 0x14], xmm0
00500742 call 0x695680
00500747 mov ecx, edi
00500749 movss xmm0, dword ptr [eax + 0x2b8]
00500751 movss dword ptr [esp + 0x1c], xmm0
00500757 movss xmm0, dword ptr [eax + 0x2bc]
0050075f movss dword ptr [esp + 0xc], xmm0
00500765 call 0x695680
0050076a movss xmm1, dword ptr [esp + 0x14]
00500770 sub esp, 0xc
00500773 mov ecx, dword ptr [0xbfd65c]
00500779 movaps xmm0, xmm1
0050077c mulss xmm0, dword ptr [esp + 0x28]
00500782 mulss xmm1, dword ptr [esp + 0x18]
00500788 mov ecx, dword ptr [ecx + 0x18190]
0050078e addss xmm0, dword ptr [eax + 0x294]
00500796 movss xmm3, dword ptr [0xb6a9c8]
0050079e addss xmm1, dword ptr [eax + 0x298]
005007a6 mov dword ptr [esp + 8], 0x41a00000
005007ae lea eax, [esp + 0x20]
005007b2 mov dword ptr [esp + 4], 0x41a00000
005007ba mov dword ptr [esp], 0x41a00000
005007c1 push eax
005007c2 lea eax, [esp + 0x2c]
005007c6 movss dword ptr [esp + 0x24], xmm0
005007cc push eax
005007cd movss dword ptr [esp + 0x2c], xmm1
005007d3 call 0x7cec10
005007d8 movss xmm0, dword ptr [edi + 0x294]
005007e0 subss xmm0, dword ptr [esp + 0x1c]
005007e6 movss dword ptr [esp + 0x24], xmm0
005007ec movss xmm0, dword ptr [edi + 0x298]
005007f4 subss xmm0, dword ptr [esp + 0x20]
005007fa movss dword ptr [esp + 0xc], xmm0
00500800 movss xmm0, dword ptr [0xb6a554]
00500808 call 0x411fe0
0050080d movss dword ptr [esp + 0x14], xmm0
00500813 movss xmm0, dword ptr [0xb6a554]
0050081b call 0x412010
00500820 movss xmm2, dword ptr [esp + 0x14]
00500826 movaps xmm1, xmm0
00500829 movss xmm4, dword ptr [esp + 0xc]
0050082f movaps xmm5, xmm2
00500832 movss xmm3, dword ptr [esp + 0x24]
00500838 mulss xmm2, xmm3
0050083c mulss xmm0, xmm4
00500840 mulss xmm1, xmm3
00500844 mulss xmm5, xmm4
00500848 subss xmm2, xmm0
0050084c movss xmm0, dword ptr [0xb6a9c8]
00500854 addss xmm5, xmm1
00500858 movss xmm1, dword ptr [0xb6c980]
00500860 andps xmm2, xmm1
00500863 comiss xmm0, xmm2
00500866 ja 0x500874
00500868 andps xmm5, xmm1
0050086b comiss xmm0, xmm5
0050086e jbe 0x500dcd
00500874 movaps xmm0, xmm4
00500877 movaps xmm1, xmm3
0050087a mulss xmm0, xmm4
0050087e mulss xmm1, xmm3
00500882 addss xmm0, xmm1
00500886 call 0x4228c0
0050088b movss xmm1, dword ptr [0xb6aba8]
00500893 movaps xmm2, xmm0
00500896 comiss xmm1, xmm2
00500899 jbe 0x500dcd
0050089f comiss xmm2, dword ptr [0xb6a18c]
005008a6 jbe 0x5008d0
005008a8 movss xmm0, dword ptr [0xb6ae44]
005008b0 divss xmm0, xmm2
005008b4 movaps xmm1, xmm0
005008b7 mulss xmm0, dword ptr [esp + 0xc]
005008bd mulss xmm1, dword ptr [esp + 0x24]
005008c3 movss dword ptr [edi + 0x28c], xmm1
005008cb jmp 0x500be5
005008d0 movss xmm1, dword ptr [esp + 0x24]
005008d6 movss xmm0, dword ptr [esp + 0xc]
005008dc movss dword ptr [edi + 0x28c], xmm1
005008e4 jmp 0x500be5
005008e9 push 0
005008eb push ecx
005008ec lea ecx, [edi + 0x364]
005008f2 mov dword ptr [esp], 0x3f400000
005008f9 call 0x7a51e0
005008fe movss xmm3, dword ptr [edi + 0x2f4]
00500906 movss xmm4, dword ptr [0xb6a614]
0050090e movss xmm2, dword ptr [0xb6a588]
00500916 ucomiss xmm3, xmm4
00500919 lahf 
0050091a test ah, 0x44
0050091d jnp 0x500935
0050091f movaps xmm1, xmm3
00500922 movaps xmm0, xmm3
00500925 addss xmm1, xmm2
00500929 mulss xmm0, xmm2
0050092d subss xmm1, xmm0
00500931 divss xmm2, xmm1
00500935 mulss xmm2, dword ptr [edi + 0x2b8]
0050093d movss xmm1, dword ptr [0xb6a560]
00500945 ucomiss xmm3, xmm4
00500948 movss dword ptr [edi + 0x2b8], xmm2
00500950 lahf 
00500951 test ah, 0x44
00500954 jnp 0x500969
00500956 movaps xmm0, xmm3
00500959 mulss xmm3, xmm1
0050095d addss xmm0, xmm1
00500961 subss xmm0, xmm3
00500965 divss xmm1, xmm0
00500969 mulss xmm1, dword ptr [edi + 0x2bc]
00500971 mov ecx, edi
00500973 push dword ptr [edi + 0x20]
00500976 push 7
00500978 movss dword ptr [edi + 0x2bc], xmm1
00500980 call 0x684790
00500985 test al, al
00500987 je 0x500dcd
0050098d cmp dword ptr [edi + 0xe6c], -1
00500994 jne 0x500dcd
0050099a push 0
0050099c push 0x1000a00
005009a1 mov ecx, edi
005009a3 call 0x4122f0
005009a8 test al, al
005009aa jne 0x500dcd
005009b0 call 0x6c3d90
005009b5 mov ecx, edi
005009b7 movd xmm0, eax
005009bb cvtdq2pd xmm0, xmm0
005009bf shr eax, 0x1f
005009c2 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
005009cb cvtpd2ps xmm0, xmm0
005009cf mulss xmm0, dword ptr [0xb6a19c]
005009d7 mulss xmm0, dword ptr [0xb6a9b0]
005009df movss dword ptr [esp + 0x1c], xmm0
005009e5 call 0x695680
005009ea mov ecx, edi
005009ec movss xmm0, dword ptr [eax + 0x2b8]
005009f4 movss dword ptr [esp + 0x14], xmm0
005009fa movss xmm0, dword ptr [eax + 0x2bc]
00500a02 movss dword ptr [esp + 0xc], xmm0
00500a08 call 0x695680
00500a0d movss xmm0, dword ptr [esp + 0x14]
00500a13 sub esp, 0xc
00500a16 mulss xmm0, dword ptr [esp + 0x28]
00500a1c mov esi, dword ptr [0xbfd65c]
00500a22 movss xmm3, dword ptr [0xb6a9c8]
00500a2a mov dword ptr [esp + 8], 0x41a00000
00500a32 addss xmm0, dword ptr [eax + 0x294]
00500a3a mov ecx, dword ptr [esi + 0x18190]
00500a40 mov dword ptr [esp + 4], 0x41a00000
00500a48 mov dword ptr [esp], 0x41a00000
00500a4f movss dword ptr [esp + 0x20], xmm0
00500a55 movss xmm0, dword ptr [esp + 0x18]
00500a5b mulss xmm0, dword ptr [esp + 0x28]
00500a61 addss xmm0, dword ptr [eax + 0x298]
00500a69 lea eax, [esp + 0x20]
00500a6d push eax
00500a6e lea eax, [esp + 0x34]
00500a72 push eax
00500a73 movss dword ptr [esp + 0x2c], xmm0
00500a79 call 0x7cec10
00500a7e mov esi, dword ptr [esi + 0x18190]
00500a84 mov eax, dword ptr [edi + 0x384]
00500a8a cdq 
00500a8b movss xmm0, dword ptr [0xb6aa3c]
00500a93 idiv dword ptr [esi + 0xc]
00500a96 movss xmm3, dword ptr [0xb6c980]
00500a9e movss xmm4, dword ptr [0xb6a9c8]
00500aa6 movd xmm2, edx
00500aaa cvtdq2ps xmm2, xmm2
00500aad movd xmm1, eax
00500ab1 cvtdq2ps xmm1, xmm1
00500ab4 mulss xmm2, xmm0
00500ab8 mulss xmm1, xmm0
00500abc addss xmm2, xmm0
00500ac0 addss xmm1, dword ptr [0xb6ab20]
00500ac8 movss dword ptr [esp + 0x2c], xmm2
00500ace subss xmm2, dword ptr [esp + 0x24]
00500ad4 movss dword ptr [esp + 0x30], xmm1
00500ada subss xmm1, dword ptr [esp + 0x28]
00500ae0 movaps xmm0, xmm2
00500ae3 movss dword ptr [esp + 0xc], xmm2
00500ae9 andps xmm0, xmm3
00500aec comiss xmm4, xmm0
00500aef movss dword ptr [esp + 0x14], xmm1
00500af5 movss dword ptr [esp + 0x1c], xmm0
00500afb ja 0x500b0c
00500afd movaps xmm0, xmm1
00500b00 andps xmm0, xmm3
00500b03 comiss xmm4, xmm0
00500b06 jbe 0x500dcd
00500b0c movaps xmm0, xmm1
00500b0f mulss xmm0, xmm1
00500b13 movaps xmm1, xmm2
00500b16 mulss xmm1, xmm2
00500b1a addss xmm0, xmm1
00500b1e call 0x4228c0
00500b23 movss xmm1, dword ptr [0xb6aba8]
00500b2b comiss xmm1, xmm0
00500b2e jbe 0x500dcd
00500b34 push 0
00500b36 push 0
00500b38 push 0
00500b3a push 0
00500b3c push 0
00500b3e lea eax, [esp + 0x38]
00500b42 mov ecx, esi
00500b44 push eax
00500b45 lea eax, [esp + 0x44]
00500b49 push eax
00500b4a call 0x7af4b0
00500b4f test al, al
00500b51 je 0x500dcd
00500b57 movss xmm1, dword ptr [esp + 0x14]
00500b5d movss xmm2, dword ptr [esp + 0x1c]
00500b63 movaps xmm0, xmm1
00500b66 andps xmm0, xmmword ptr [0xb6c980]
00500b6d comiss xmm2, xmm0
00500b70 xorps xmm0, xmm0
00500b73 jbe 0x500bc4
00500b75 comiss xmm0, dword ptr [esp + 0xc]
00500b7a mov dword ptr [edi + 0x290], 0
00500b84 jbe 0x500ba5
00500b86 movss xmm0, dword ptr [0xb6a614]
00500b8e movss dword ptr [edi + 0x28c], xmm0
00500b96 mov dword ptr [edi + 0xab4], 8
00500ba0 jmp 0x500dcd
00500ba5 movss xmm0, dword ptr [0xb6ae44]
00500bad movss dword ptr [edi + 0x28c], xmm0
00500bb5 mov dword ptr [edi + 0xab4], 8
00500bbf jmp 0x500dcd
00500bc4 comiss xmm0, xmm1
00500bc7 mov dword ptr [edi + 0x28c], 0
00500bd1 jbe 0x500bdd
00500bd3 movss xmm0, dword ptr [0xb6a614]
00500bdb jmp 0x500be5
00500bdd movss xmm0, dword ptr [0xb6ae44]
00500be5 movss dword ptr [edi + 0x290], xmm0
00500bed mov dword ptr [edi + 0xab4], 8
00500bf7 jmp 0x500dcd
00500bfc cmp byte ptr [edi + 0x188], 0
00500c03 jne 0x500d63
00500c09 mov eax, dword ptr [edi + 0x160]
00500c0f and eax, 0x1000b00
00500c14 or eax, 0
00500c17 jne 0x500d63
00500c1d cmp dword ptr [edi + 0xe88], eax
00500c23 jne 0x500d63
00500c29 cmp dword ptr [edi + 0xe6c], -1
00500c30 jne 0x500d63
00500c36 movss xmm3, dword ptr [edi + 0x2c4]
00500c3e mulss xmm3, dword ptr [0xb6a560]
00500c46 ucomiss xmm3, dword ptr [0xb6a18c]
00500c4d movss dword ptr [edi + 0x2c4], xmm3
00500c55 lahf 
00500c56 test ah, 0x44
00500c59 jnp 0x500ca2
00500c5b movss xmm1, dword ptr [edi + 0x2f4]
00500c63 movss xmm2, dword ptr [edi + 0x290]
00500c6b movaps xmm0, xmm1
00500c6e mulss xmm0, dword ptr [edi + 0x28c]
00500c76 mulss xmm2, xmm1
00500c7a divss xmm0, xmm3
00500c7e divss xmm2, xmm3
00500c82 addss xmm0, dword ptr [edi + 0x2b8]
00500c8a addss xmm2, dword ptr [edi + 0x2bc]
00500c92 movss dword ptr [edi + 0x2b8], xmm0
00500c9a movss dword ptr [edi + 0x2bc], xmm2
00500ca2 cmp dword ptr [edi + 0x28], 0x12d
00500ca9 je 0x500dcd
00500caf mov ecx, dword ptr [0xbfd65c]
00500cb5 mov eax, dword ptr [edi + 0x384]
00500cbb cdq 
00500cbc movss xmm0, dword ptr [0xb6aa3c]
00500cc4 mov ecx, dword ptr [ecx + 0x18190]
00500cca movss xmm2, dword ptr [edi + 0x2b8]
00500cd2 andps xmm2, xmmword ptr [0xb6c980]
00500cd9 mov ecx, dword ptr [ecx + 0xc]
00500cdc idiv ecx
00500cde movd xmm3, edx
00500ce2 cvtdq2ps xmm3, xmm3
00500ce5 movd xmm4, eax
00500ce9 cvtdq2ps xmm4, xmm4
00500cec mulss xmm3, xmm0
00500cf0 mulss xmm4, xmm0
00500cf4 addss xmm3, xmm0
00500cf8 movss xmm0, dword ptr [edi + 0x2bc]
00500d00 andps xmm0, xmmword ptr [0xb6c980]
00500d07 comiss xmm2, xmm0
00500d0a addss xmm4, dword ptr [0xb6ab20]
00500d12 jbe 0x500d3d
00500d14 movss xmm0, dword ptr [edi + 0x298]
00500d1c mulss xmm4, dword ptr [0xb6a2cc]
00500d24 mulss xmm0, dword ptr [0xb6a5a4]
00500d2c addss xmm4, xmm0
00500d30 movss dword ptr [edi + 0x298], xmm4
00500d38 jmp 0x500dcd
00500d3d movss xmm0, dword ptr [edi + 0x294]
00500d45 mulss xmm3, dword ptr [0xb6a2cc]
00500d4d mulss xmm0, dword ptr [0xb6a5a4]
00500d55 addss xmm3, xmm0
00500d59 movss dword ptr [edi + 0x294], xmm3
00500d61 jmp 0x500dcd
00500d63 movss xmm0, dword ptr [0xc02fec]
00500d6b movss dword ptr [edi + 0x368], xmm0
00500d73 movss xmm0, dword ptr [0xc02ff0]
00500d7b movss dword ptr [edi + 0x36c], xmm0
00500d83 movss xmm0, dword ptr [0xc02fec]
00500d8b movss dword ptr [edi + 0x370], xmm0
00500d93 movss xmm0, dword ptr [0xc02ff0]
00500d9b movss dword ptr [edi + 0x374], xmm0
00500da3 mov dword ptr [edi + 0xab4], 4
00500dad movss xmm0, dword ptr [0xc02fec]
00500db5 movss dword ptr [edi + 0x28c], xmm0
00500dbd movss xmm0, dword ptr [0xc02ff0]
00500dc5 movss dword ptr [edi + 0x290], xmm0
00500dcd mov esi, dword ptr [edi + 0x20]
00500dd0 mov ecx, edi
00500dd2 call 0x6ad7a0
00500dd7 xor edx, edx
00500dd9 cmp eax, 5
00500ddc mov eax, esi
00500dde jge 0x500e21
00500de0 mov ecx, 0xc
00500de5 movss xmm1, dword ptr [0xb6a98c]
00500ded div ecx
00500def mov ecx, edi
00500df1 mov esi, edx
00500df3 mov eax, edx
00500df5 shr eax, 0x1f
00500df8 movd xmm0, esi
00500dfc cvtdq2pd xmm0, xmm0
00500e00 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
00500e09 cvtpd2ps xmm2, xmm0
00500e0d call 0x6847e0
00500e12 movss xmm1, dword ptr [0xb6a98c]
00500e1a test eax, eax
00500e1c lea eax, [esi + 6]
00500e1f jmp 0x500e60
00500e21 mov ecx, 0x18
00500e26 movss xmm1, dword ptr [0xb6a9e8]
00500e2e div ecx
00500e30 mov ecx, edi
00500e32 mov esi, edx
00500e34 mov eax, edx
00500e36 shr eax, 0x1f
00500e39 movd xmm0, esi
00500e3d cvtdq2pd xmm0, xmm0
00500e41 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
00500e4a cvtpd2ps xmm2, xmm0
00500e4e call 0x6847e0
00500e53 movss xmm1, dword ptr [0xb6a9e8]
00500e5b test eax, eax
00500e5d lea eax, [esi + 0xc]
00500e60 movd xmm0, eax
00500e64 setg byte ptr [esp + 0x13]
00500e69 cvtdq2pd xmm0, xmm0
00500e6d shr eax, 0x1f
00500e70 mov ecx, edi
00500e72 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
00500e7b cvtpd2ps xmm2, xmm0
00500e7f call 0x6847e0
00500e84 test eax, eax
00500e86 setg al
00500e89 cmp byte ptr [esp + 0x13], 0
00500e8e jne 0x500eb9
00500e90 movss xmm1, dword ptr [edi + 0x2bc]
00500e98 movss xmm0, dword ptr [edi + 0x2b8]
00500ea0 mulss xmm0, xmm0
00500ea4 mulss xmm1, xmm1
00500ea8 addss xmm0, xmm1
00500eac comiss xmm0, dword ptr [0xb6a95c]
00500eb3 jbe 0x500f2e
00500eb5 test al, al
00500eb7 je 0x500f2e
00500eb9 call 0x6c3d90
00500ebe push 0
00500ec0 push eax
00500ec1 push 0
00500ec3 xor ecx, ecx
00500ec5 lea esi, [edi + 0x294]
00500ecb cmp dword ptr [edi + 0x28], 0x12d
00500ed2 push edi
00500ed3 push 0xc02fec
00500ed8 sete cl
00500edb add ecx, 0x16
00500ede push esi
00500edf push ecx
00500ee0 mov ecx, dword ptr [0xbfd65c]
00500ee6 push 0x3e8
00500eeb call 0x6d0ca0
00500ef0 push 0
00500ef2 push 0xbeaaec
00500ef7 push 0xbeab18
00500efc push 0
00500efe push eax
00500eff call 0x9ec34c
00500f04 add esp, 0x14
00500f07 mov ecx, eax
00500f09 mov edx, dword ptr [eax]
00500f0b mov dword ptr [eax + 0xd8], 0x3f9d70a4
00500f15 mov dword ptr [eax + 0xdc], 0x3f9d70a4
00500f1f mov dword ptr [eax + 0x3c4], 0
00500f29 call dword ptr [edx + 0xc]
00500f2c jmp 0x500f34
00500f2e lea esi, [edi + 0x294]
00500f34 cmp byte ptr [edi + 0x16b], 0
00500f3b je 0x500f84
00500f3d cmp dword ptr [edi + 0x28], 0x12d
00500f44 jne 0x500f84
00500f46 push 0
00500f48 push 0
00500f4a push 4
00500f4c push 1
00500f4e push ecx
00500f4f mov dword ptr [esp], 0x3f800000
00500f56 lea ecx, [esp + 0x74]
00500f5a push edi
00500f5b call 0x402120
00500f60 movups xmm0, xmmword ptr [0xbc4c30]
00500f67 push eax
00500f68 sub esp, 0x10
00500f6b mov eax, esp
00500f6d push ecx
00500f6e mov ecx, dword ptr [0xbfd65c]
00500f74 movups xmmword ptr [eax], xmm0
00500f77 mov dword ptr [esp], 0x42200000
00500f7e push esi
00500f7f call 0x6d26e0
00500f84 mov ecx, dword ptr [esp + 0x8c]
00500f8b pop edi
00500f8c pop esi
00500f8d xor ecx, esp
00500f8f call 0x9eacd7
00500f94 mov esp, ebp
00500f96 pop ebp
00500f97 ret 
