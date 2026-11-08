00653380 push ebp
00653381 mov ebp, esp
00653383 and esp, 0xfffffff8
00653386 sub esp, 0x30
00653389 push esi
0065338a push edi
0065338b mov edi, ecx
0065338d mov dword ptr [esp + 0x24], edi
00653391 cmp dword ptr [edi + 0x74c], 0
00653398 jle 0x6533de
0065339a mov eax, dword ptr [edi + 0x314]
006533a0 test eax, eax
006533a2 je 0x653df3
006533a8 movss xmm0, dword ptr [eax + 0x294]
006533b0 movss xmm1, dword ptr [eax + 0x298]
006533b8 addss xmm0, dword ptr [edi + 0x750]
006533c0 addss xmm1, dword ptr [edi + 0x754]
006533c8 movss dword ptr [edi + 0x294], xmm0
006533d0 movss dword ptr [edi + 0x298], xmm1
006533d8 pop edi
006533d9 pop esi
006533da mov esp, ebp
006533dc pop ebp
006533dd ret 
006533de mov edx, dword ptr [edi + 0x380]
006533e4 mov eax, edx
006533e6 and eax, dword ptr [0xbc46a8]
006533ec mov esi, dword ptr [edi + 0x378]
006533f2 mov ecx, esi
006533f4 and ecx, dword ptr [0xbc46a0]
006533fa mov dword ptr [esp + 0xc], eax
006533fe mov eax, dword ptr [edi + 0x384]
00653404 and eax, dword ptr [0xbc46ac]
0065340a mov dword ptr [esp + 0x10], eax
0065340e mov eax, dword ptr [edi + 0x37c]
00653414 and eax, dword ptr [0xbc46a4]
0065341a or ecx, eax
0065341c jne 0x65342c
0065341e mov eax, dword ptr [esp + 0xc]
00653422 or eax, dword ptr [esp + 0x10]
00653426 je 0x65364c
0065342c mov ecx, dword ptr [edi + 0x37c]
00653432 mov eax, dword ptr [edi + 0x384]
00653438 and esi, dword ptr [0xbc4ce0]
0065343e and ecx, dword ptr [0xbc4ce4]
00653444 and edx, dword ptr [0xbc4ce8]
0065344a and eax, dword ptr [0xbc4cec]
00653450 or esi, ecx
00653452 jne 0x65364c
00653458 or edx, eax
0065345a jne 0x65364c
00653460 mov eax, dword ptr [edi + 0x314]
00653466 test eax, eax
00653468 je 0x65364c
0065346e cmp dword ptr [eax + 0x28], 1
00653472 jne 0x65364c
00653478 cmp dword ptr [edi + 0x3c8], edx
0065347e jne 0x65364c
00653484 push edx
00653485 push 0xbeab9c
0065348a push 0xbeab18
0065348f push edx
00653490 push eax
00653491 call 0x9ec34c
00653496 add esp, 0x14
00653499 mov esi, eax
0065349b push 0
0065349d push 0xbeabc8
006534a2 push 0xbeab18
006534a7 push 0
006534a9 push dword ptr [esi + 0x1378]
006534af call 0x9ec34c
006534b4 mov edx, eax
006534b6 add esp, 0x14
006534b9 test edx, edx
006534bb je 0x65364c
006534c1 mov ecx, dword ptr [edi + 0x378]
006534c7 and ecx, dword ptr [0xbc4920]
006534cd mov eax, dword ptr [edi + 0x37c]
006534d3 and eax, dword ptr [0xbc4924]
006534d9 movss xmm0, dword ptr [edi + 0x294]
006534e1 movss xmm1, dword ptr [edi + 0x298]
006534e9 subss xmm0, dword ptr [esi + 0x294]
006534f1 subss xmm1, dword ptr [esi + 0x298]
006534f9 movss xmm2, dword ptr [0xb6a614]
00653501 mov dword ptr [esp + 0x28], ecx
00653505 mov ecx, dword ptr [edi + 0x380]
0065350b and ecx, dword ptr [0xbc4928]
00653511 mov dword ptr [esp + 0x2c], eax
00653515 mov eax, dword ptr [edi + 0x384]
0065351b and eax, dword ptr [0xbc492c]
00653521 mov dword ptr [esp + 0x30], ecx
00653525 lea ecx, [esp + 0x28]
00653529 movss dword ptr [esp + 0x18], xmm0
0065352f movss dword ptr [esp + 0x1c], xmm1
00653535 movss dword ptr [esp + 0xc], xmm2
0065353b mov dword ptr [esp + 0x34], eax
0065353f call 0x412090
00653544 test al, al
00653546 je 0x653572
00653548 mulss xmm0, dword ptr [edi + 0x2b8]
00653550 mulss xmm1, dword ptr [edi + 0x2bc]
00653558 addss xmm1, xmm0
0065355c xorps xmm0, xmm0
0065355f comiss xmm0, xmm1
00653562 jbe 0x653572
00653564 movss xmm2, dword ptr [0xb6ae44]
0065356c movss dword ptr [esp + 0xc], xmm2
00653572 movss xmm0, dword ptr [edx + 0x36c]
0065357a mulss xmm0, dword ptr [0xb6a230]
00653582 movss dword ptr [esp + 0x10], xmm0
00653588 call 0x411fe0
0065358d movss dword ptr [esp + 0x28], xmm0
00653593 movss xmm0, dword ptr [esp + 0x10]
00653599 call 0x412010
0065359e movss xmm1, dword ptr [edi + 0x2bc]
006535a6 movss dword ptr [esp + 0x2c], xmm0
006535ac movss xmm0, dword ptr [edi + 0x2b8]
006535b4 mulss xmm0, xmm0
006535b8 mulss xmm1, xmm1
006535bc addss xmm0, xmm1
006535c0 call 0x4228c0
006535c5 push ecx
006535c6 lea eax, [esp + 0x14]
006535ca movss dword ptr [esp], xmm0
006535cf push eax
006535d0 lea ecx, [esp + 0x30]
006535d4 call 0x9628d0
006535d9 movss xmm0, dword ptr [esp + 0xc]
006535df movaps xmm1, xmm0
006535e2 mulss xmm0, dword ptr [eax + 4]
006535e7 mulss xmm1, dword ptr [eax]
006535eb movss dword ptr [edi + 0x2bc], xmm0
006535f3 movss xmm0, dword ptr [esp + 0x18]
006535f9 movss dword ptr [edi + 0x2b8], xmm1
00653601 movss xmm1, dword ptr [esp + 0x1c]
00653607 mulss xmm0, xmm0
0065360b mulss xmm1, xmm1
0065360f addss xmm0, xmm1
00653613 call 0x4228c0
00653618 movss xmm2, dword ptr [esp + 0x28]
0065361e movss xmm1, dword ptr [esp + 0x2c]
00653624 mulss xmm2, xmm0
00653628 mulss xmm1, xmm0
0065362c addss xmm2, dword ptr [esi + 0x294]
00653634 addss xmm1, dword ptr [esi + 0x298]
0065363c movss dword ptr [edi + 0x294], xmm2
00653644 movss dword ptr [edi + 0x298], xmm1
0065364c mov edx, dword ptr [edi + 0x380]
00653652 mov eax, edx
00653654 and eax, dword ptr [0xbc4778]
0065365a mov esi, dword ptr [edi + 0x384]
00653660 mov ecx, dword ptr [edi + 0x378]
00653666 and ecx, dword ptr [0xbc4770]
0065366c mov dword ptr [esp + 0x1c], eax
00653670 mov eax, esi
00653672 and eax, dword ptr [0xbc477c]
00653678 mov dword ptr [esp + 0x18], eax
0065367c mov eax, dword ptr [edi + 0x37c]
00653682 and eax, dword ptr [0xbc4774]
00653688 or ecx, eax
0065368a mov dword ptr [esp + 0xc], esi
0065368e jne 0x65369e
00653690 mov eax, dword ptr [esp + 0x1c]
00653694 or eax, dword ptr [esp + 0x18]
00653698 je 0x6537fd
0065369e mov eax, dword ptr [edi + 0x3d8]
006536a4 test eax, eax
006536a6 je 0x653801
006536ac cmp dword ptr [edi + 0x3dc], 0
006536b3 mov dword ptr [esp + 0xc], esi
006536b7 je 0x653801
006536bd push 0
006536bf push 0xbeabc8
006536c4 push 0xbeab18
006536c9 push 0
006536cb push eax
006536cc call 0x9ec34c
006536d1 mov ecx, dword ptr [edi + 0x3dc]
006536d7 add esp, 0x14
006536da movss xmm0, dword ptr [edi + 0x2b8]
006536e2 mov esi, eax
006536e4 addss xmm0, dword ptr [edi + 0x294]
006536ec movss xmm1, dword ptr [ecx + 0x294]
006536f4 addss xmm1, dword ptr [ecx + 0x2a4]
006536fc movss xmm2, dword ptr [ecx + 0x298]
00653704 addss xmm0, dword ptr [edi + 0x2a4]
0065370c addss xmm2, dword ptr [ecx + 0x2a8]
00653714 subss xmm1, xmm0
00653718 movss xmm0, dword ptr [edi + 0x2bc]
00653720 addss xmm0, dword ptr [edi + 0x298]
00653728 movss dword ptr [esp + 0x1c], xmm1
0065372e addss xmm0, dword ptr [edi + 0x2a8]
00653736 subss xmm2, xmm0
0065373a movaps xmm0, xmm2
0065373d movss dword ptr [esp + 0x18], xmm2
00653743 call 0x447a80
00653748 mulss xmm0, dword ptr [0xb6aa84]
00653750 mov eax, dword ptr [esi + 0x36c]
00653756 movss xmm1, dword ptr [esp + 0x1c]
0065375c mulss xmm1, xmm1
00653760 mov dword ptr [esi + 0x370], eax
00653766 movss dword ptr [esi + 0x368], xmm0
0065376e movss dword ptr [esi + 0x36c], xmm0
00653776 subss xmm0, dword ptr [0xb6aae4]
0065377e movss dword ptr [esi + 0xe0], xmm0
00653786 movss xmm0, dword ptr [esp + 0x18]
0065378c mulss xmm0, xmm0
00653790 addss xmm0, xmm1
00653794 call 0x4228c0
00653799 movss dword ptr [esi + 0x420], xmm0
006537a1 movss xmm1, dword ptr [edi + 0x2a4]
006537a9 movss xmm0, dword ptr [edi + 0x2a8]
006537b1 addss xmm1, dword ptr [edi + 0x294]
006537b9 addss xmm0, dword ptr [edi + 0x298]
006537c1 addss xmm1, dword ptr [edi + 0x2b8]
006537c9 addss xmm0, dword ptr [edi + 0x2bc]
006537d1 subss xmm1, dword ptr [esi + 0x2a4]
006537d9 subss xmm0, dword ptr [esi + 0x2a8]
006537e1 movss dword ptr [esi + 0x294], xmm1
006537e9 movss dword ptr [esi + 0x298], xmm0
006537f1 mov edx, dword ptr [edi + 0x380]
006537f7 mov esi, dword ptr [edi + 0x384]
006537fd mov dword ptr [esp + 0xc], esi
00653801 mov ecx, dword ptr [edi + 0x378]
00653807 mov eax, edx
00653809 and eax, dword ptr [0xbc4ce8]
0065380f and ecx, dword ptr [0xbc4ce0]
00653815 and esi, dword ptr [0xbc4cec]
0065381b movss xmm4, dword ptr [0xb6a480]
00653823 mov dword ptr [esp + 0x1c], eax
00653827 mov eax, dword ptr [edi + 0x37c]
0065382d and eax, dword ptr [0xbc4ce4]
00653833 or ecx, eax
00653835 jne 0x653a3b
0065383b mov eax, dword ptr [esp + 0x1c]
0065383f or eax, esi
00653841 jne 0x653a3b
00653847 mov eax, dword ptr [edi + 0x320]
0065384d mov esi, edi
0065384f test eax, eax
00653851 je 0x65385f
00653853 mov esi, eax
00653855 mov eax, dword ptr [esi + 0x320]
0065385b test eax, eax
0065385d jne 0x653853
0065385f mov ecx, dword ptr [edi + 0x378]
00653865 xor eax, eax
00653867 cmp dword ptr [esi + 0x28], 1
0065386b mov edi, dword ptr [edi + 0x37c]
00653871 cmovne esi, eax
00653874 mov eax, dword ptr [esp + 0xc]
00653878 and edi, dword ptr [0xbc4934]
0065387e and ecx, dword ptr [0xbc4930]
00653884 and edx, dword ptr [0xbc4938]
0065388a and eax, dword ptr [0xbc493c]
00653890 or ecx, edi
00653892 mov edi, dword ptr [esp + 0x24]
00653896 jne 0x65389c
00653898 or edx, eax
0065389a je 0x6538c5
0065389c test esi, esi
0065389e je 0x6538b3
006538a0 push 0xa
006538a2 mov ecx, esi
006538a4 call 0x7866b0
006538a9 maxss xmm0, dword ptr [0xb6a614]
006538b1 jmp 0x6538bb
006538b3 movss xmm0, dword ptr [0xb6a614]
006538bb movaps xmm1, xmm0
006538be mov ecx, edi
006538c0 call 0x6421f0
006538c5 mov eax, dword ptr [edi + 0x384]
006538cb and eax, dword ptr [0xbc496c]
006538d1 mov ecx, dword ptr [0xbc4960]
006538d7 mov edx, dword ptr [edi + 0x380]
006538dd and ecx, dword ptr [edi + 0x378]
006538e3 and edx, dword ptr [0xbc4968]
006538e9 mov dword ptr [esp + 0x24], eax
006538ed mov eax, dword ptr [0xbc4964]
006538f2 and eax, dword ptr [edi + 0x37c]
006538f8 or ecx, eax
006538fa jne 0x653902
006538fc or edx, dword ptr [esp + 0x24]
00653900 je 0x653939
00653902 test esi, esi
00653904 je 0x65392a
00653906 push 0xb
00653908 mov ecx, esi
0065390a call 0x78d4c0
0065390f mov ecx, 1
00653914 cmp eax, ecx
00653916 cmovg ecx, eax
00653919 movd xmm1, ecx
0065391d cvtdq2ps xmm1, xmm1
00653920 maxss xmm1, dword ptr [0xb6a614]
00653928 jmp 0x653932
0065392a movss xmm1, dword ptr [0xb6a614]
00653932 mov ecx, edi
00653934 call 0x642330
00653939 mov eax, dword ptr [edi + 0x384]
0065393f and eax, dword ptr [0xbc4a2c]
00653945 mov ecx, dword ptr [edi + 0x378]
0065394b mov edx, dword ptr [edi + 0x380]
00653951 and ecx, dword ptr [0xbc4a20]
00653957 and edx, dword ptr [0xbc4a28]
0065395d mov dword ptr [esp + 0x24], eax
00653961 mov eax, dword ptr [edi + 0x37c]
00653967 and eax, dword ptr [0xbc4a24]
0065396d or ecx, eax
0065396f jne 0x653977
00653971 or edx, dword ptr [esp + 0x24]
00653975 je 0x6539af
00653977 test esi, esi
00653979 je 0x6539a0
0065397b push 0x60
0065397d mov ecx, esi
0065397f call 0x78d4c0
00653984 cmp eax, 1
00653987 mov ecx, 1
0065398c cmovg ecx, eax
0065398f movd xmm1, ecx
00653993 cvtdq2ps xmm1, xmm1
00653996 maxss xmm1, dword ptr [0xb6a614]
0065399e jmp 0x6539a8
006539a0 movss xmm1, dword ptr [0xb6a614]
006539a8 mov ecx, edi
006539aa call 0x6424d0
006539af mov ecx, edi
006539b1 call 0x688240
006539b6 mov esi, dword ptr [0xbfd65c]
006539bc cmp dword ptr [edi + 0x388], 0
006539c3 jg 0x653df3
006539c9 mov eax, dword ptr [edi + 0x384]
006539cf and eax, dword ptr [0xbc4cec]
006539d5 mov ecx, dword ptr [edi + 0x378]
006539db mov edx, dword ptr [edi + 0x380]
006539e1 and ecx, dword ptr [0xbc4ce0]
006539e7 and edx, dword ptr [0xbc4ce8]
006539ed mov dword ptr [esp + 0x24], eax
006539f1 mov eax, dword ptr [edi + 0x37c]
006539f7 and eax, dword ptr [0xbc4ce4]
006539fd or ecx, eax
006539ff jne 0x653df3
00653a05 or edx, dword ptr [esp + 0x24]
00653a09 jne 0x653df3
00653a0f cmp byte ptr [edi + 0x16b], dl
00653a15 jne 0x653df3
00653a1b mov eax, dword ptr [esi + 0x18190]
00653a21 cmp dword ptr [eax + 8], 0x10
00653a25 jne 0x653dc4
00653a2b mov dword ptr [edi + 0x2a8], 0xc1900000
00653a35 pop edi
00653a36 pop esi
00653a37 mov esp, ebp
00653a39 pop ebp
00653a3a ret 
00653a3b test byte ptr [edi + 0x30], 2
00653a3f je 0x653a6c
00653a41 mov ecx, dword ptr [edi + 0x160]
00653a47 mov eax, ecx
00653a49 mov edx, dword ptr [edi + 0x164]
00653a4f and eax, 2
00653a52 or eax, 0
00653a55 je 0x653a6c
00653a57 and ecx, 0xfffffffd
00653a5a mov dword ptr [edi + 0x164], edx
00653a60 mov dword ptr [edi + 0x160], ecx
00653a66 pop edi
00653a67 pop esi
00653a68 mov esp, ebp
00653a6a pop ebp
00653a6b ret 
00653a6c mov eax, dword ptr [edi + 0x294]
00653a72 lea esi, [edi + 0x294]
00653a78 mov dword ptr [edi + 0x29c], eax
00653a7e mov eax, dword ptr [esi + 4]
00653a81 mov dword ptr [edi + 0x2a0], eax
00653a87 movss xmm3, dword ptr [edi + 0x2c4]
00653a8f movss xmm2, dword ptr [edi + 0x2bc]
00653a97 movaps xmm0, xmm3
00653a9a mulss xmm0, dword ptr [edi + 0x2b8]
00653aa2 test byte ptr [edi + 0x30], 2
00653aa6 movss xmm1, dword ptr [edi + 0x2f4]
00653aae mulss xmm3, xmm2
00653ab2 mulss xmm0, xmm1
00653ab6 mulss xmm3, xmm1
00653aba mulss xmm0, xmm4
00653abe mulss xmm3, xmm4
00653ac2 addss xmm0, dword ptr [esi]
00653ac6 addss xmm3, dword ptr [esi + 4]
00653acb movss dword ptr [esi], xmm0
00653acf movss dword ptr [esi + 4], xmm3
00653ad4 mov byte ptr [edi + 0x16d], 1
00653adb mov edx, dword ptr [edi + 0x314]
00653ae1 mov dword ptr [esp + 0xc], edx
00653ae5 test edx, edx
00653ae7 je 0x653af3
00653ae9 cmp dword ptr [edx + 0x28], 2
00653aed je 0x653b9a
00653af3 mov eax, dword ptr [edi + 0x380]
00653af9 and eax, dword ptr [0xbc4948]
00653aff mov ecx, dword ptr [edi + 0x378]
00653b05 and ecx, dword ptr [0xbc4940]
00653b0b mov dword ptr [esp + 0x24], eax
00653b0f mov eax, dword ptr [edi + 0x384]
00653b15 and eax, dword ptr [0xbc494c]
00653b1b mov dword ptr [esp + 0x1c], eax
00653b1f mov eax, dword ptr [edi + 0x37c]
00653b25 and eax, dword ptr [0xbc4944]
00653b2b or ecx, eax
00653b2d jne 0x653b84
00653b2f mov eax, dword ptr [esp + 0x24]
00653b33 or eax, dword ptr [esp + 0x1c]
00653b37 jne 0x653b84
00653b39 mov ecx, dword ptr [0xbfd65c]
00653b3f sub esp, 0xc
00653b42 xorps xmm3, xmm3
00653b45 mov ecx, dword ptr [ecx + 0x18190]
00653b4b mov dword ptr [esp + 8], eax
00653b4f mov dword ptr [esp + 4], eax
00653b53 mov dword ptr [esp], eax
00653b56 lea eax, [esp + 0x34]
00653b5a push esi
00653b5b push eax
00653b5c call 0x7cec10
00653b61 movss xmm0, dword ptr [esp + 0x28]
00653b67 movss xmm4, dword ptr [0xb6a480]
00653b6f movss dword ptr [esi], xmm0
00653b73 movss xmm0, dword ptr [esp + 0x2c]
00653b79 movss dword ptr [esi + 4], xmm0
00653b7e mov edx, dword ptr [edi + 0x314]
00653b84 mov dword ptr [esp + 0xc], edx
00653b88 test edx, edx
00653b8a je 0x653d2f
00653b90 cmp dword ptr [edx + 0x28], 2
00653b94 jne 0x653d2f
00653b9a test byte ptr [edi + 0x30], 1
00653b9e je 0x653d2f
00653ba4 mov eax, dword ptr [edi + 0x20]
00653ba7 xor edx, edx
00653ba9 mov ecx, 0xa
00653bae div ecx
00653bb0 movd xmm0, edx
00653bb4 cvtdq2pd xmm0, xmm0
00653bb8 shr edx, 0x1f
00653bbb addsd xmm0, qword ptr [edx*8 + 0xb6c940]
00653bc4 cvtpd2ps xmm0, xmm0
00653bc8 mulss xmm0, dword ptr [0xb6a2cc]
00653bd0 mulss xmm0, xmm4
00653bd4 addss xmm0, dword ptr [0xb6a7b0]
00653bdc mulss xmm0, dword ptr [0xb6a230]
00653be4 movss dword ptr [esp + 0x24], xmm0
00653bea call 0x411fe0
00653bef movss dword ptr [esp + 0x1c], xmm0
00653bf5 movss xmm0, dword ptr [esp + 0x24]
00653bfb call 0x412010
00653c00 movss xmm2, dword ptr [edi + 0x744]
00653c08 movss xmm5, dword ptr [edi + 0x748]
00653c10 movaps xmm4, xmm2
00653c13 movss xmm3, dword ptr [esp + 0x1c]
00653c19 movaps xmm1, xmm5
00653c1c mov eax, dword ptr [0xbfd65c]
00653c21 mulss xmm1, xmm0
00653c25 mulss xmm4, xmm3
00653c29 mulss xmm2, xmm0
00653c2d subss xmm4, xmm1
00653c31 mulss xmm5, xmm3
00653c35 addss xmm5, xmm2
00653c39 movss dword ptr [esp + 0x1c], xmm4
00653c3f mov eax, dword ptr [eax + 0x1a30dc]
00653c45 sub eax, dword ptr [edi + 0x280]
00653c4b movss dword ptr [esp + 0x28], xmm4
00653c51 movss dword ptr [esp + 0x24], xmm5
00653c57 movss dword ptr [esp + 0x2c], xmm5
00653c5d movd xmm0, eax
00653c61 imul eax, dword ptr [edi + 0x20], 0x32
00653c65 cvtdq2ps xmm0, xmm0
00653c68 addss xmm0, dword ptr [0xb6a480]
00653c70 movd xmm1, eax
00653c74 cvtdq2pd xmm1, xmm1
00653c78 shr eax, 0x1f
00653c7b addsd xmm1, qword ptr [eax*8 + 0xb6c940]
00653c84 cvtpd2ps xmm1, xmm1
00653c88 addss xmm0, xmm1
00653c8c mulss xmm0, dword ptr [0xb6a2ac]
00653c94 call 0x412010
00653c99 mov eax, dword ptr [esp + 0xc]
00653c9d movss dword ptr [esp + 0x18], xmm0
00653ca3 movss xmm0, dword ptr [esp + 0x24]
00653ca9 mulss xmm0, xmm0
00653cad movss xmm1, dword ptr [eax + 0x294]
00653cb5 movss dword ptr [esp + 0x10], xmm1
00653cbb movss xmm1, dword ptr [eax + 0x298]
00653cc3 movss dword ptr [esp + 0xc], xmm1
00653cc9 movss xmm1, dword ptr [esp + 0x1c]
00653ccf mulss xmm1, xmm1
00653cd3 addss xmm0, xmm1
00653cd7 call 0x4228c0
00653cdc movss xmm1, dword ptr [esp + 0x18]
00653ce2 lea eax, [esp + 0x1c]
00653ce6 mulss xmm1, dword ptr [0xb6a480]
00653cee push ecx
00653cef lea ecx, [esp + 0x2c]
00653cf3 addss xmm1, dword ptr [0xb6a614]
00653cfb mulss xmm0, xmm1
00653cff movss dword ptr [esp], xmm0
00653d04 push eax
00653d05 call 0x9628d0
00653d0a movss xmm0, dword ptr [esp + 0x10]
00653d10 movss xmm1, dword ptr [esp + 0xc]
00653d16 addss xmm0, dword ptr [eax]
00653d1a addss xmm1, dword ptr [eax + 4]
00653d1f movss dword ptr [edi + 0x294], xmm0
00653d27 movss dword ptr [edi + 0x298], xmm1
00653d2f mov ecx, dword ptr [edi + 0x378]
00653d35 mov eax, dword ptr [edi + 0x37c]
00653d3b mov edx, dword ptr [edi + 0x380]
00653d41 mov esi, dword ptr [edi + 0x384]
00653d47 and ecx, dword ptr [0xbc46c0]
00653d4d and eax, dword ptr [0xbc46c4]
00653d53 and edx, dword ptr [0xbc46c8]
00653d59 and esi, dword ptr [0xbc46cc]
00653d5f or ecx, eax
00653d61 jne 0x653d6b
00653d63 or edx, esi
00653d65 je 0x6539b6
00653d6b mov ecx, edi
00653d6d call 0x654610
00653d72 movss xmm2, dword ptr [0xb6a874]
00653d7a mov esi, dword ptr [0xbfd65c]
00653d80 divss xmm2, xmm0
00653d84 mov eax, dword ptr [esi + 0x1a30dc]
00653d8a sub eax, dword ptr [edi + 0x280]
00653d90 movd xmm1, eax
00653d94 cvtdq2ps xmm0, xmm1
00653d97 addss xmm0, dword ptr [0xb6a480]
00653d9f mulss xmm0, xmm2
00653da3 call 0x412010
00653da8 andps xmm0, xmmword ptr [0xb6c980]
00653daf mulss xmm0, dword ptr [edi + 0x360]
00653db7 movss dword ptr [edi + 0x2a8], xmm0
00653dbf jmp 0x6539bc
00653dc4 movss xmm1, dword ptr [edi + 0x364]
00653dcc mov ecx, edi
00653dce mulss xmm1, dword ptr [edi + 0x2f4]
00653dd6 mulss xmm1, dword ptr [0xb6a480]
00653dde addss xmm1, dword ptr [edi + 0x360]
00653de6 call 0x650150
00653deb movss dword ptr [edi + 0x2a8], xmm0
00653df3 pop edi
00653df4 pop esi
00653df5 mov esp, ebp
00653df7 pop ebp
00653df8 ret 
