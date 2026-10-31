00548fc0 push ebx
00548fc1 mov ebx, esp
00548fc3 sub esp, 8
00548fc6 and esp, 0xfffffff8
00548fc9 add esp, 4
00548fcc push ebp
00548fcd mov ebp, dword ptr [ebx + 4]
00548fd0 mov dword ptr [esp + 4], ebp
00548fd4 mov ebp, esp
00548fd6 sub esp, 0x20
00548fd9 mov eax, dword ptr [0xbfd65c]
00548fde push esi
00548fdf push edi
00548fe0 mov edi, ecx
00548fe2 mov eax, dword ptr [eax + 0x18190]
00548fe8 movss xmm0, dword ptr [eax + 0x7134]
00548ff0 comiss xmm0, dword ptr [0xb6a18c]
00548ff7 seta cl
00548ffa cmp dword ptr [edi + 0xab4], 6
00549001 mov byte ptr [ebp - 1], cl
00549004 je 0x549012
00549006 movzx eax, cl
00549009 add eax, 5
0054900c mov dword ptr [edi + 0x17c], eax
00549012 mov eax, dword ptr [0xbfd680]
00549017 cmp byte ptr [eax + 0x29e7b], 0
0054901e je 0x549124
00549024 test cl, cl
00549026 je 0x549124
0054902c movss xmm0, dword ptr [edi + 0x2a8]
00549034 comiss xmm0, dword ptr [0xb6ae7c]
0054903b jbe 0x549124
00549041 push ecx
00549042 mov ecx, dword ptr [0xbfd65c]
00549048 lea esi, [edi + 0x3c]
0054904b call 0x706110
00549050 cmp eax, 0x1c
00549053 jne 0x549097
00549055 cmp dword ptr [esi + 0x80], 0
0054905c jg 0x54907a
0054905e cmp dword ptr [esi + 0x14], 0x10
00549062 mov eax, esi
00549064 jb 0x549068
00549066 mov eax, dword ptr [esi]
00549068 push 0
0054906a push eax
0054906b push 0xa0830c
00549070 push 3
00549072 call 0x95e330
00549077 add esp, 0x10
0054907a mov eax, dword ptr [esi + 0x7c]
0054907d mov dword ptr [eax + 0x48], 0x3fb33333
00549084 mov dword ptr [eax + 0x4c], 0x3fb33333
0054908b mov dword ptr [eax + 0x50], 0x3fb33333
00549092 jmp 0x549164
00549097 cmp dword ptr [esi + 0x80], 0
0054909e jg 0x5490bc
005490a0 cmp dword ptr [esi + 0x14], 0x10
005490a4 mov eax, esi
005490a6 jb 0x5490aa
005490a8 mov eax, dword ptr [esi]
005490aa push 0
005490ac push eax
005490ad push 0xa0830c
005490b2 push 3
005490b4 call 0x95e330
005490b9 add esp, 0x10
005490bc mov eax, dword ptr [esi + 0x7c]
005490bf mov dword ptr [eax + 0x48], 0x40a00000
005490c6 mov dword ptr [eax + 0x4c], 0x40a00000
005490cd mov dword ptr [eax + 0x50], 0x40a00000
005490d4 mov dword ptr [eax + 0x54], 0x3f800000
005490db cmp dword ptr [edi + 0xbc], 0
005490e2 jg 0x549100
005490e4 cmp dword ptr [edi + 0x50], 0x10
005490e8 mov eax, esi
005490ea jb 0x5490ee
005490ec mov eax, dword ptr [esi]
005490ee push 0
005490f0 push eax
005490f1 push 0xa0830c
005490f6 push 3
005490f8 call 0x95e330
005490fd add esp, 0x10
00549100 mov eax, dword ptr [edi + 0xb8]
00549106 mov dword ptr [eax + 0x58], 0x3f800000
0054910d mov dword ptr [eax + 0x5c], 0x3f800000
00549114 mov dword ptr [eax + 0x60], 0x3f800000
0054911b mov dword ptr [eax + 0x64], 0x3f19999a
00549122 jmp 0x54916b
00549124 cmp dword ptr [edi + 0xbc], 0
0054912b lea esi, [edi + 0x3c]
0054912e jg 0x54914c
00549130 cmp dword ptr [esi + 0x14], 0x10
00549134 mov eax, esi
00549136 jb 0x54913a
00549138 mov eax, dword ptr [esi]
0054913a push 0
0054913c push eax
0054913d push 0xa0830c
00549142 push 3
00549144 call 0x95e330
00549149 add esp, 0x10
0054914c mov eax, dword ptr [esi + 0x7c]
0054914f mov dword ptr [eax + 0x48], 0x3f800000
00549156 mov dword ptr [eax + 0x4c], 0x3f800000
0054915d mov dword ptr [eax + 0x50], 0x3f800000
00549164 mov dword ptr [eax + 0x54], 0x3f800000
0054916b mov eax, dword ptr [edi + 0xab4]
00549171 cmp eax, 7
00549174 ja 0x549d38
0054917a jmp dword ptr [eax*4 + 0x549d44]
00549181 mov dword ptr [edi + 0x17c], 6
0054918b mov ecx, esi
0054918d mov dword ptr [edi + 0xab4], 3
00549197 push 0
00549199 mov dword ptr [edi + 0xb00], 0
005491a3 push 0xb435bc
005491a8 mov dword ptr [edi + 0xb04], 0
005491b2 call 0x4054f0
005491b7 pop edi
005491b8 pop esi
005491b9 mov esp, ebp
005491bb pop ebp
005491bc mov esp, ebx
005491be pop ebx
005491bf ret 
005491c0 mov dword ptr [edi + 0x17c], 3
005491ca mov dword ptr [edi + 0x180], 0
005491d4 movss xmm3, dword ptr [edi + 0xb08]
005491dc movss dword ptr [edi + 0x2b8], xmm3
005491e4 mov eax, dword ptr [edi + 0xb0c]
005491ea mov dword ptr [edi + 0x2bc], eax
005491f0 movss xmm2, dword ptr [edi + 0x2f4]
005491f8 movaps xmm1, xmm2
005491fb movaps xmm0, xmm2
005491fe mulss xmm1, dword ptr [0xb6a50c]
00549206 addss xmm1, dword ptr [edi + 0xb00]
0054920e mulss xmm0, xmm1
00549212 movss dword ptr [edi + 0xb00], xmm1
0054921a xorps xmm1, xmmword ptr [0xb6c9b0]
00549221 addss xmm0, dword ptr [edi + 0x2a8]
00549229 mulss xmm1, xmm2
0054922d comiss xmm0, xmm1
00549230 movss dword ptr [edi + 0x2a8], xmm0
00549238 jbe 0x5492b5
0054923a mov dword ptr [edi + 0x2a8], 0
00549244 mov dword ptr [edi + 0xb00], 0
0054924e movss xmm0, dword ptr [0xc02fec]
00549256 movss dword ptr [edi + 0xb08], xmm0
0054925e movss xmm0, dword ptr [0xc02ff0]
00549266 movss dword ptr [edi + 0xb0c], xmm0
0054926e movss xmm0, dword ptr [0xc02fec]
00549276 movss dword ptr [edi + 0x28c], xmm0
0054927e movss xmm0, dword ptr [0xc02ff0]
00549286 movss dword ptr [edi + 0x290], xmm0
0054928e mov dword ptr [edi + 0x17c], 6
00549298 mov dword ptr [edi + 0x180], 4
005492a2 mov dword ptr [edi + 0xab4], 3
005492ac pop edi
005492ad pop esi
005492ae mov esp, ebp
005492b0 pop ebp
005492b1 mov esp, ebx
005492b3 pop ebx
005492b4 ret 
005492b5 xorps xmm0, xmm0
005492b8 mov ecx, 0xb43598
005492bd comiss xmm0, xmm3
005492c0 mov eax, 0xb435bc
005492c5 push 0
005492c7 cmova eax, ecx
005492ca mov ecx, esi
005492cc push eax
005492cd call 0x4054f0
005492d2 pop edi
005492d3 pop esi
005492d4 mov esp, ebp
005492d6 pop ebp
005492d7 mov esp, ebx
005492d9 pop ebx
005492da ret 
005492db cmp byte ptr [ebp - 1], 0
005492df mov eax, dword ptr [edi + 0xe6c]
005492e5 je 0x549ac7
005492eb cmp eax, -1
005492ee je 0x54931c
005492f0 mov ecx, dword ptr [edi + 0x314]
005492f6 lea eax, [edi + 0x314]
005492fc test ecx, ecx
005492fe je 0x54931c
00549300 mov dword ptr [ebp - 0x14], eax
00549303 add ecx, 0x324
00549309 lea eax, [ebp - 0x14]
0054930c push eax
0054930d call 0x4bc3c0
00549312 mov dword ptr [edi + 0x314], 0
0054931c movss xmm0, dword ptr [edi + 0xb04]
00549324 xorps xmm1, xmm1
00549327 movss xmm2, dword ptr [0xb6a19c]
0054932f ucomiss xmm0, xmm1
00549332 lahf 
00549333 test ah, 0x44
00549336 jp 0x549424
0054933c cmp dword ptr [edi + 0x314], 0
00549343 je 0x549424
00549349 call 0x6c3d90
0054934e movd xmm0, eax
00549352 cvtdq2pd xmm0, xmm0
00549356 shr eax, 0x1f
00549359 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
00549362 mov eax, dword ptr [edi + 0x314]
00549368 cvtpd2ps xmm1, xmm0
0054936c movss xmm0, dword ptr [eax + 0x2c8]
00549374 addss xmm0, dword ptr [0xb6a9c8]
0054937c mulss xmm1, xmm2
00549380 mulss xmm1, dword ptr [0xb6aa3c]
00549388 addss xmm0, xmm1
0054938c movss dword ptr [edi + 0xb04], xmm0
00549394 movss xmm1, dword ptr [edi + 0x294]
0054939c movss xmm0, dword ptr [edi + 0x298]
005493a4 subss xmm1, dword ptr [eax + 0x294]
005493ac subss xmm0, dword ptr [eax + 0x298]
005493b4 call 0x447a80
005493b9 mulss xmm0, dword ptr [0xb6aa84]
005493c1 movss dword ptr [edi + 0xb08], xmm0
005493c9 call 0x6c3d90
005493ce test al, 1
005493d0 je 0x5493dc
005493d2 movss xmm1, dword ptr [0xb6ae44]
005493da jmp 0x5493e4
005493dc movss xmm1, dword ptr [0xb6a614]
005493e4 call 0x6c3d90
005493e9 movss xmm2, dword ptr [0xb6a19c]
005493f1 movd xmm0, eax
005493f5 cvtdq2pd xmm0, xmm0
005493f9 shr eax, 0x1f
005493fc addsd xmm0, qword ptr [eax*8 + 0xb6c940]
00549405 cvtpd2ps xmm0, xmm0
00549409 mulss xmm0, xmm2
0054940d addss xmm0, dword ptr [0xb6a8cc]
00549415 mulss xmm0, xmm1
00549419 xorps xmm1, xmm1
0054941c movss dword ptr [edi + 0xb0c], xmm0
00549424 movss xmm0, dword ptr [edi + 0x14]
00549429 comiss xmm0, xmm1
0054942c jbe 0x549486
0054942e call 0x6c3d90
00549433 test al, 1
00549435 jne 0x549486
00549437 call 0x6c3d90
0054943c push ecx
0054943d movd xmm0, eax
00549441 cvtdq2pd xmm0, xmm0
00549445 shr eax, 0x1f
00549448 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
00549451 cvtpd2ps xmm0, xmm0
00549455 mulss xmm0, xmm2
00549459 mulss xmm0, dword ptr [0xb6a350]
00549461 addss xmm0, dword ptr [0xb6a690]
00549469 movss dword ptr [esp], xmm0
0054946e push 0
00549470 push 0xa
00549472 push ecx
00549473 mov dword ptr [esp], 0x3f4ccccd
0054947a mov ecx, edi
0054947c push 0xdd
00549481 call 0x6ad720
00549486 mov eax, dword ptr [edi + 0x314]
0054948c mov dword ptr [ebp - 0xc], eax
0054948f test eax, eax
00549491 je 0x54971f
00549497 movss xmm0, dword ptr [edi + 0xb0c]
0054949f addss xmm0, dword ptr [edi + 0xb08]
005494a7 call 0x65a640
005494ac mov eax, dword ptr [ebp - 0xc]
005494af movss dword ptr [edi + 0xb08], xmm0
005494b7 movss xmm1, dword ptr [edi + 0x294]
005494bf movss dword ptr [ebp - 0x14], xmm0
005494c4 movss xmm0, dword ptr [edi + 0x298]
005494cc subss xmm0, dword ptr [eax + 0x298]
005494d4 subss xmm1, dword ptr [eax + 0x294]
005494dc mulss xmm0, xmm0
005494e0 mulss xmm1, xmm1
005494e4 addss xmm0, xmm1
005494e8 call 0x4228c0
005494ed movss xmm1, dword ptr [edi + 0xb04]
005494f5 addss xmm1, dword ptr [0xb6aa0c]
005494fd comiss xmm0, xmm1
00549500 jbe 0x549514
00549502 mov eax, dword ptr [ebp - 0xc]
00549505 mov dword ptr [edi + 0xb00], 0x3f000000
0054950f jmp 0x549726
00549514 movss xmm0, dword ptr [ebp - 0x14]
00549519 mulss xmm0, dword ptr [0xb6a230]
00549521 movss dword ptr [ebp - 0x14], xmm0
00549526 call 0x411fe0
0054952b mulss xmm0, dword ptr [edi + 0xb04]
00549533 mov eax, dword ptr [ebp - 0xc]
00549536 addss xmm0, dword ptr [eax + 0x294]
0054953e subss xmm0, dword ptr [edi + 0x294]
00549546 movss dword ptr [ebp - 8], xmm0
0054954b movss xmm0, dword ptr [ebp - 0x14]
00549550 call 0x412010
00549555 mov eax, dword ptr [ebp - 0xc]
00549558 movaps xmm1, xmm0
0054955b mulss xmm1, dword ptr [edi + 0xb04]
00549563 addss xmm1, dword ptr [eax + 0x298]
0054956b subss xmm1, dword ptr [edi + 0x298]
00549573 movaps xmm0, xmm1
00549576 movss dword ptr [ebp - 0x14], xmm1
0054957b mulss xmm0, xmm1
0054957f movss xmm1, dword ptr [ebp - 8]
00549584 mulss xmm1, xmm1
00549588 addss xmm0, xmm1
0054958c call 0x4228c0
00549591 movss xmm3, dword ptr [ebp - 8]
00549596 movaps xmm1, xmm0
00549599 movss xmm0, dword ptr [0xb6a9c8]
005495a1 xorps xmm2, xmm2
005495a4 comiss xmm1, xmm0
005495a7 movss xmm4, dword ptr [ebp - 0x14]
005495ac jbe 0x5495bf
005495ae comiss xmm1, xmm2
005495b1 jbe 0x5495bf
005495b3 divss xmm0, xmm1
005495b7 mulss xmm3, xmm0
005495bb mulss xmm4, xmm0
005495bf movss xmm5, dword ptr [edi + 0x2f4]
005495c7 movss xmm6, dword ptr [0xb6a614]
005495cf movss xmm1, dword ptr [0xb6a3fc]
005495d7 ucomiss xmm5, xmm6
005495da lahf 
005495db test ah, 0x44
005495de jnp 0x5495f3
005495e0 movaps xmm0, xmm5
005495e3 mulss xmm5, xmm1
005495e7 addss xmm0, xmm1
005495eb subss xmm0, xmm5
005495ef divss xmm1, xmm0
005495f3 mov ecx, dword ptr [ebp - 0xc]
005495f6 lea eax, [edi + 0x2b8]
005495fc subss xmm6, xmm1
00549600 addss xmm3, dword ptr [ecx + 0x2b8]
00549608 addss xmm4, dword ptr [ecx + 0x2bc]
00549610 subss xmm3, dword ptr [eax]
00549614 subss xmm4, dword ptr [eax + 4]
00549619 mulss xmm3, xmm6
0054961d mulss xmm4, xmm6
00549621 addss xmm3, dword ptr [eax]
00549625 addss xmm4, dword ptr [eax + 4]
0054962a movss dword ptr [eax], xmm3
0054962e movss dword ptr [eax + 4], xmm4
00549633 movss xmm0, dword ptr [edi + 0x2c4]
0054963b mulss xmm0, dword ptr [0xb6a588]
00549643 movss dword ptr [edi + 0x2c4], xmm0
0054964b movss xmm0, dword ptr [edi + 0xb0c]
00549653 comiss xmm0, xmm2
00549656 jbe 0x549662
00549658 movss xmm0, dword ptr [0xb6aae4]
00549660 jmp 0x54966a
00549662 movss xmm0, dword ptr [0xb6af48]
0054966a addss xmm0, dword ptr [edi + 0xb08]
00549672 mulss xmm0, dword ptr [0xb6a230]
0054967a movss dword ptr [ebp - 0x14], xmm0
0054967f call 0x411fe0
00549684 movss dword ptr [ebp - 0xc], xmm0
00549689 movss xmm0, dword ptr [ebp - 0x14]
0054968e call 0x412010
00549693 movaps xmm4, xmm0
00549696 movss xmm0, dword ptr [ebp - 0xc]
0054969b movaps xmm1, xmm4
0054969e movaps xmm3, xmm0
005496a1 andps xmm1, xmmword ptr [0xb6c980]
005496a8 andps xmm3, xmmword ptr [0xb6c980]
005496af comiss xmm3, xmm1
005496b2 xorps xmm1, xmm1
005496b5 jbe 0x5496eb
005496b7 comiss xmm0, xmm1
005496ba jbe 0x5496cf
005496bc push 0
005496be push 0xb435bc
005496c3 mov ecx, esi
005496c5 call 0x4054f0
005496ca jmp 0x5499bc
005496cf comiss xmm1, xmm0
005496d2 jbe 0x5499bf
005496d8 push 0
005496da push 0xb43598
005496df mov ecx, esi
005496e1 call 0x4054f0
005496e6 jmp 0x5499bc
005496eb comiss xmm4, xmm1
005496ee jbe 0x549703
005496f0 push 0
005496f2 push 0xb435a4
005496f7 mov ecx, esi
005496f9 call 0x4054f0
005496fe jmp 0x5499bc
00549703 comiss xmm1, xmm4
00549706 jbe 0x5499bf
0054970c push 0
0054970e push 0xb435d8
00549713 mov ecx, esi
00549715 call 0x4054f0
0054971a jmp 0x5499bc
0054971f mov ecx, edi
00549721 call 0x695680
00549726 movss xmm0, dword ptr [eax + 0x294]
0054972e lea ecx, [ebp - 0x18]
00549731 movss xmm1, dword ptr [eax + 0x298]
00549739 lea eax, [ebp - 0x10]
0054973c subss xmm0, dword ptr [edi + 0x294]
00549744 subss xmm1, dword ptr [edi + 0x298]
0054974c push eax
0054974d movss dword ptr [ebp - 0x18], xmm0
00549752 movss dword ptr [ebp - 0x14], xmm1
00549757 call 0x962560
0054975c push 0
0054975e push 0x200
00549763 mov ecx, edi
00549765 call 0x4122f0
0054976a test al, al
0054976c je 0x5497eb
0054976e mov eax, dword ptr [0xbfd65c]
00549773 lea ecx, [ebp - 0x20]
00549776 movq xmm0, qword ptr [0xa08ac4]
0054977e movq qword ptr [ebp - 0x1c], xmm0
00549783 mov eax, dword ptr [eax + 0x1a30dc]
00549789 sub eax, dword ptr [edi + 0x280]
0054978f imul eax, eax, 0x3ff
00549795 cdq 
00549796 and edx, 3
00549799 add eax, edx
0054979b sar eax, 2
0054979e add eax, dword ptr [edi + 0x344]
005497a4 mov dword ptr [ebp - 0x20], eax
005497a7 mov eax, dword ptr [0xa08acc]
005497ac mov dword ptr [ebp - 0x14], eax
005497af call 0x7a7e20
005497b4 lea ecx, [ebp - 0x20]
005497b7 call 0x7a7db0
005497bc fmul dword ptr [0xb6ac40]
005497c2 fmul dword ptr [0xb6a230]
005497c8 fstp dword ptr [ebp - 0x14]
005497cb movss xmm0, dword ptr [ebp - 0x14]
005497d0 call 0x411fe0
005497d5 movss dword ptr [ebp - 0xc], xmm0
005497da movss xmm0, dword ptr [ebp - 0x14]
005497df call 0x412010
005497e4 movss dword ptr [ebp - 8], xmm0
005497e9 jmp 0x5497ff
005497eb movss xmm0, dword ptr [ebp - 0xc]
005497f0 movss dword ptr [ebp - 8], xmm0
005497f5 movss xmm0, dword ptr [ebp - 0x10]
005497fa movss dword ptr [ebp - 0xc], xmm0
005497ff push 0
00549801 push 0x1000800
00549806 mov ecx, edi
00549808 call 0x4122f0
0054980d movss xmm4, dword ptr [ebp - 0xc]
00549812 movss xmm3, dword ptr [ebp - 8]
00549817 test al, al
00549819 je 0x549835
0054981b mulss xmm4, dword ptr [0xb6ae44]
00549823 mulss xmm3, dword ptr [0xb6ae44]
0054982b movss dword ptr [ebp - 0xc], xmm4
00549830 movss dword ptr [ebp - 8], xmm3
00549835 cmp dword ptr [edi + 0xe6c], -1
0054983c je 0x54985f
0054983e lea eax, [ebp - 0x18]
00549841 xorps xmm2, xmm2
00549844 push eax
00549845 mov ecx, edi
00549847 call 0x6af0c0
0054984c movss xmm4, dword ptr [eax]
00549850 movss xmm3, dword ptr [eax + 4]
00549855 movss dword ptr [ebp - 0xc], xmm4
0054985a movss dword ptr [ebp - 8], xmm3
0054985f cmp dword ptr [edi + 0x30], 1
00549863 movss xmm0, dword ptr [0xb6a53c]
0054986b jne 0x54987f
0054986d mulss xmm4, xmm0
00549871 mulss xmm3, xmm0
00549875 movss dword ptr [ebp - 0xc], xmm4
0054987a movss dword ptr [ebp - 8], xmm3
0054987f movss xmm2, dword ptr [edi + 0x2f4]
00549887 movss xmm1, dword ptr [0xb6a3f8]
0054988f movaps xmm0, xmm2
00549892 mulss xmm0, dword ptr [0xb6a228]
0054989a addss xmm0, dword ptr [edi + 0xb00]
005498a2 minss xmm1, xmm0
005498a6 movss dword ptr [edi + 0xb00], xmm1
005498ae movaps xmm0, xmm1
005498b1 mulss xmm0, xmm4
005498b5 mulss xmm1, xmm3
005498b9 mulss xmm0, xmm2
005498bd mulss xmm1, xmm2
005498c1 addss xmm0, dword ptr [edi + 0x2b8]
005498c9 addss xmm1, dword ptr [edi + 0x2bc]
005498d1 movss dword ptr [edi + 0x2b8], xmm0
005498d9 movss dword ptr [edi + 0x2bc], xmm1
005498e1 movss xmm0, dword ptr [edi + 0x2c4]
005498e9 mulss xmm0, dword ptr [0xb6a5e8]
005498f1 movss dword ptr [edi + 0x2c4], xmm0
005498f9 ucomiss xmm4, dword ptr [0xc02fec]
00549900 lahf 
00549901 test ah, 0x44
00549904 jp 0x549913
00549906 ucomiss xmm3, dword ptr [0xc02ff0]
0054990d lahf 
0054990e test ah, 0x44
00549911 jnp 0x549976
00549913 movaps xmm2, xmm4
00549916 movaps xmm0, xmm3
00549919 andps xmm2, xmmword ptr [0xb6c980]
00549920 xorps xmm1, xmm1
00549923 andps xmm0, xmmword ptr [0xb6c980]
0054992a comiss xmm2, xmm0
0054992d jbe 0x54994b
0054992f comiss xmm4, xmm1
00549932 jbe 0x54993d
00549934 push 0
00549936 push 0xb435bc
0054993b jmp 0x549965
0054993d comiss xmm1, xmm4
00549940 jbe 0x549979
00549942 push 0
00549944 push 0xb43598
00549949 jmp 0x549965
0054994b comiss xmm3, xmm1
0054994e jbe 0x549959
00549950 push 0
00549952 push 0xb435a4
00549957 jmp 0x549965
00549959 comiss xmm1, xmm3
0054995c jbe 0x549979
0054995e push 0
00549960 push 0xb435d8
00549965 mov ecx, esi
00549967 call 0x4054f0
0054996c movss xmm4, dword ptr [ebp - 0xc]
00549971 movss xmm3, dword ptr [ebp - 8]
00549976 xorps xmm1, xmm1
00549979 cmp dword ptr [edi + 0xe6c], -1
00549980 je 0x5499bf
00549982 mulss xmm3, xmm3
00549986 mulss xmm4, xmm4
0054998a addss xmm3, xmm4
0054998e movaps xmm0, xmm3
00549991 call 0x4228c0
00549996 cmp dword ptr [edi + 0x30], 1
0054999a jne 0x5499a4
0054999c divss xmm0, dword ptr [0xb6a53c]
005499a4 mulss xmm0, dword ptr [0xb6a480]
005499ac addss xmm0, dword ptr [0xb6a480]
005499b4 movss dword ptr [edi + 0x140], xmm0
005499bc xorps xmm1, xmm1
005499bf movss xmm2, dword ptr [edi + 0x2b8]
005499c7 lea esi, [edi + 0x2b8]
005499cd comiss xmm1, xmm2
005499d0 mov eax, dword ptr [0xbfd65c]
005499d5 mov eax, dword ptr [eax + 0x18190]
005499db movss xmm4, dword ptr [edi + 0x2c4]
005499e3 movaps xmm5, xmm2
005499e6 movss xmm6, dword ptr [0xb6ae28]
005499ee movss xmm3, dword ptr [0xb6a974]
005499f6 mulss xmm5, xmm4
005499fa mulss xmm4, dword ptr [esi + 4]
005499ff addss xmm5, dword ptr [edi + 0x294]
00549a07 addss xmm4, dword ptr [edi + 0x298]
00549a0f jbe 0x549a1f
00549a11 movss xmm0, dword ptr [eax + 0x14]
00549a16 addss xmm0, xmm3
00549a1a comiss xmm0, xmm5
00549a1d ja 0x549a32
00549a1f comiss xmm2, xmm1
00549a22 jbe 0x549a3a
00549a24 movss xmm0, dword ptr [eax + 0x1c]
00549a29 subss xmm0, xmm3
00549a2d comiss xmm5, xmm0
00549a30 jbe 0x549a3a
00549a32 mulss xmm2, xmm6
00549a36 movss dword ptr [esi], xmm2
00549a3a movss xmm2, dword ptr [edi + 0x2bc]
00549a42 comiss xmm1, xmm2
00549a45 jbe 0x549a59
00549a47 movss xmm0, dword ptr [eax + 0x18]
00549a4c addss xmm0, dword ptr [0xb6a9c8]
00549a54 comiss xmm0, xmm4
00549a57 ja 0x549a70
00549a59 comiss xmm2, xmm1
00549a5c jbe 0x549a7c
00549a5e movss xmm0, dword ptr [eax + 0x20]
00549a63 subss xmm0, dword ptr [0xb6a8cc]
00549a6b comiss xmm4, xmm0
00549a6e jbe 0x549a7c
00549a70 mulss xmm2, xmm6
00549a74 movss dword ptr [edi + 0x2bc], xmm2
00549a7c divss xmm3, dword ptr [edi + 0x2c4]
00549a84 movss xmm1, dword ptr [esi + 4]
00549a89 movss xmm0, dword ptr [esi]
00549a8d mulss xmm0, xmm0
00549a91 mulss xmm1, xmm1
00549a95 movss dword ptr [ebp - 0x14], xmm3
00549a9a addss xmm0, xmm1
00549a9e call 0x4228c0
00549aa3 movss xmm1, dword ptr [ebp - 0x14]
00549aa8 comiss xmm0, xmm1
00549aab jbe 0x549d38
00549ab1 push ecx
00549ab2 mov ecx, esi
00549ab4 movss dword ptr [esp], xmm1
00549ab9 call 0x962860
00549abe pop edi
00549abf pop esi
00549ac0 mov esp, ebp
00549ac2 pop ebp
00549ac3 mov esp, ebx
00549ac5 pop ebx
00549ac6 ret 
00549ac7 movss xmm0, dword ptr [edi + 0x2c4]
00549acf mulss xmm0, dword ptr [0xb6a50c]
00549ad7 movss dword ptr [edi + 0x2c4], xmm0
00549adf cmp eax, -1
00549ae2 je 0x549b08
00549ae4 movss xmm2, dword ptr [0xb6a2cc]
00549aec lea eax, [ebp - 0x18]
00549aef push 0xc02fec
00549af4 push eax
00549af5 mov ecx, edi
00549af7 call 0x6af0c0
00549afc mov ecx, eax
00549afe call 0x962ca0
00549b03 movzx eax, al
00549b06 jmp 0x549b12
00549b08 call 0x6c3d90
00549b0d not eax
00549b0f and eax, 1
00549b12 test eax, eax
00549b14 je 0x549d38
00549b1a push ecx
00549b1b lea eax, [ebp - 0x10]
00549b1e mov dword ptr [esp], 0
00549b25 push eax
00549b26 mov ecx, edi
00549b28 call 0x695a30
00549b2d movss xmm0, dword ptr [eax]
00549b31 subss xmm0, dword ptr [edi + 0x294]
00549b39 movss xmm1, dword ptr [eax + 4]
00549b3e subss xmm1, dword ptr [edi + 0x298]
00549b46 ucomiss xmm0, dword ptr [0xc02fec]
00549b4d movss dword ptr [ebp - 0x18], xmm0
00549b52 movss dword ptr [ebp - 0x14], xmm1
00549b57 lahf 
00549b58 test ah, 0x44
00549b5b jp 0x549b81
00549b5d ucomiss xmm1, dword ptr [0xc02ff0]
00549b64 lahf 
00549b65 test ah, 0x44
00549b68 jp 0x549b81
00549b6a lea eax, [ebp - 0x18]
00549b6d push eax
00549b6e call 0x659290
00549b73 add esp, 4
00549b76 movss xmm5, dword ptr [eax]
00549b7a movss xmm4, dword ptr [eax + 4]
00549b7f jmp 0x549b93
00549b81 lea ecx, [ebp - 0x18]
00549b84 call 0x9624f0
00549b89 movss xmm4, dword ptr [ebp - 0x14]
00549b8e movss xmm5, dword ptr [ebp - 0x18]
00549b93 cmp dword ptr [edi + 0xe6c], -1
00549b9a je 0x549bb8
00549b9c movss xmm2, dword ptr [0xb6a2cc]
00549ba4 lea eax, [ebp - 0x18]
00549ba7 push eax
00549ba8 mov ecx, edi
00549baa call 0x6af0c0
00549baf movss xmm5, dword ptr [eax]
00549bb3 movss xmm4, dword ptr [eax + 4]
00549bb8 ucomiss xmm5, dword ptr [0xc02fec]
00549bbf lahf 
00549bc0 test ah, 0x44
00549bc3 jp 0x549bd6
00549bc5 ucomiss xmm4, dword ptr [0xc02ff0]
00549bcc lahf 
00549bcd test ah, 0x44
00549bd0 jnp 0x549d38
00549bd6 cmp dword ptr [edi + 0xe6c], -1
00549bdd je 0x549be9
00549bdf movss xmm0, dword ptr [0xb6a8cc]
00549be7 jmp 0x549c1a
00549be9 call 0x6c3d90
00549bee movd xmm0, eax
00549bf2 cvtdq2pd xmm0, xmm0
00549bf6 shr eax, 0x1f
00549bf9 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
00549c02 cvtpd2ps xmm0, xmm0
00549c06 mulss xmm0, dword ptr [0xb6a19c]
00549c0e addss xmm0, xmm0
00549c12 addss xmm0, dword ptr [0xb6a7b0]
00549c1a movss xmm2, dword ptr [edi + 0x2c4]
00549c22 xorps xmm3, xmm3
00549c25 ucomiss xmm2, xmm3
00549c28 movaps xmm6, xmm5
00549c2b movaps xmm7, xmm4
00549c2e mulss xmm6, xmm0
00549c32 lahf 
00549c33 mulss xmm7, xmm0
00549c37 test ah, 0x44
00549c3a jnp 0x549c77
00549c3c movss xmm1, dword ptr [edi + 0x2f4]
00549c44 movaps xmm0, xmm1
00549c47 mulss xmm1, xmm7
00549c4b mulss xmm0, xmm6
00549c4f divss xmm1, xmm2
00549c53 divss xmm0, xmm2
00549c57 addss xmm1, dword ptr [edi + 0x2bc]
00549c5f addss xmm0, dword ptr [edi + 0x2b8]
00549c67 movss dword ptr [edi + 0x2bc], xmm1
00549c6f movss dword ptr [edi + 0x2b8], xmm0
00549c77 movaps xmm2, xmm5
00549c7a movaps xmm0, xmm4
00549c7d andps xmm2, xmmword ptr [0xb6c980]
00549c84 andps xmm0, xmmword ptr [0xb6c980]
00549c8b comiss xmm2, xmm0
00549c8e jbe 0x549cac
00549c90 comiss xmm5, xmm3
00549c93 jbe 0x549c9e
00549c95 push 1
00549c97 push 0xb435e0
00549c9c jmp 0x549cc6
00549c9e comiss xmm3, xmm5
00549ca1 jbe 0x549cdd
00549ca3 push 1
00549ca5 push 0xb435c8
00549caa jmp 0x549cc6
00549cac comiss xmm4, xmm3
00549caf jbe 0x549cba
00549cb1 push 1
00549cb3 push 0xb435d0
00549cb8 jmp 0x549cc6
00549cba comiss xmm3, xmm4
00549cbd jbe 0x549cdd
00549cbf push 1
00549cc1 push 0xb43608
00549cc6 mov ecx, esi
00549cc8 call 0x405740
00549ccd test al, al
00549ccf je 0x549cdd
00549cd1 lea ecx, [esi + 0x30]
00549cd4 call 0x405330
00549cd9 mov byte ptr [esi + 0x44], 1
00549cdd mov dword ptr [edi + 0xab4], 7
00549ce7 pop edi
00549ce8 pop esi
00549ce9 mov esp, ebp
00549ceb pop ebp
00549cec mov esp, ebx
00549cee pop ebx
00549cef ret 
00549cf0 cmp dword ptr [edi + 0x70], 0
00549cf4 je 0x549d2e
00549cf6 push 0xb4034c
00549cfb lea ecx, [edi + 0x6c]
00549cfe call 0x405f30
00549d03 test al, al
00549d05 je 0x549d1f
00549d07 movss xmm0, dword ptr [edi + 0x2c4]
00549d0f mulss xmm0, dword ptr [0xb6a50c]
00549d17 movss dword ptr [edi + 0x2c4], xmm0
00549d1f cmp dword ptr [edi + 0x70], 0
00549d23 je 0x549d2e
00549d25 cmp byte ptr [edi + 0x80], 0
00549d2c jne 0x549d38
00549d2e mov dword ptr [edi + 0xab4], 3
00549d38 pop edi
00549d39 pop esi
00549d3a mov esp, ebp
00549d3c pop ebp
00549d3d mov esp, ebx
00549d3f pop ebx
00549d40 ret 
