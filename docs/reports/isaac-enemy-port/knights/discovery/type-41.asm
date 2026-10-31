005014f0 push ebx
005014f1 mov ebx, esp
005014f3 sub esp, 8
005014f6 and esp, 0xfffffff8
005014f9 add esp, 4
005014fc push ebp
005014fd mov ebp, dword ptr [ebx + 4]
00501500 mov dword ptr [esp + 4], ebp
00501504 mov ebp, esp
00501506 push -1
00501508 push 0x9ef39d
0050150d mov eax, dword ptr fs:[0]
00501513 push eax
00501514 push ebx
00501515 sub esp, 0x60
00501518 mov eax, dword ptr [0xbaa3b4]
0050151d xor eax, ebp
0050151f mov dword ptr [ebp - 0x14], eax
00501522 push esi
00501523 push edi
00501524 push eax
00501525 lea eax, [ebp - 0xc]
00501528 mov dword ptr fs:[0], eax
0050152e mov edi, ecx
00501530 mov dword ptr [ebp - 0x64], 0
00501537 cmp dword ptr [edi + 0x28], 0x29
0050153b jne 0x5015d8
00501541 cmp dword ptr [edi + 0x2c], 4
00501545 jne 0x5015d8
0050154b mov eax, dword ptr [edi + 8]
0050154e mov byte ptr [ebp - 0x41], 1
00501552 cmp eax, dword ptr [edi + 0xc]
00501555 je 0x50157d
00501557 cmp dword ptr [eax + 0x10], 0x3e8
0050155e jne 0x501575
00501560 cmp dword ptr [eax + 0x14], 0x93
00501567 jne 0x501575
00501569 cmp dword ptr [eax + 0x18], 1
0050156d je 0x501575
0050156f mov dword ptr [eax], 0
00501575 add eax, 0x38
00501578 cmp eax, dword ptr [edi + 0xc]
0050157b jne 0x501557
0050157d movss xmm3, dword ptr [edi + 0x2a8]
00501585 xorps xmm2, xmm2
00501588 comiss xmm2, xmm3
0050158b ja 0x501596
0050158d comiss xmm2, dword ptr [edi + 0xb08]
00501594 jbe 0x5015dc
00501596 movss xmm0, dword ptr [edi + 0xb08]
0050159e movaps xmm1, xmm0
005015a1 addss xmm0, dword ptr [0xb6a64c]
005015a9 addss xmm1, xmm3
005015ad movss dword ptr [edi + 0xb08], xmm0
005015b5 comiss xmm1, xmm2
005015b8 movss dword ptr [edi + 0x2a8], xmm1
005015c0 jbe 0x5015dc
005015c2 mov dword ptr [edi + 0x2a8], 0
005015cc mov dword ptr [edi + 0xb08], 0
005015d6 jmp 0x5015dc
005015d8 mov byte ptr [ebp - 0x41], 0
005015dc cmp dword ptr [edi + 0xab4], 0
005015e3 mov eax, dword ptr [edi + 0x28]
005015e6 jne 0x501740
005015ec mov dword ptr [edi + 0xab4], 4
005015f6 cmp eax, 0xfe
005015fb jne 0x50160c
005015fd mov dword ptr [edi + 0x17c], 3
00501607 jmp 0x502dc9
0050160c cmp eax, 0x29
0050160f jne 0x502dc9
00501615 cmp dword ptr [edi + 0x2c], 3
00501619 jne 0x502dc9
0050161f push 0
00501621 push 0
00501623 push -1
00501625 push -1
00501627 push 0x348
0050162c lea eax, [ebp - 0x24]
0050162f push eax
00501630 mov eax, dword ptr [0xbfd65c]
00501635 mov ecx, dword ptr [eax + 0x18190]
0050163b add ecx, 0x1218
00501641 call 0x415ed0
00501646 mov dword ptr [ebp - 4], 0
0050164d xor esi, esi
0050164f mov edx, dword ptr [ebp - 0x18]
00501652 xor ecx, ecx
00501654 test edx, edx
00501656 je 0x501711
0050165c movss xmm2, dword ptr [ebp - 0x4c]
00501661 mov eax, dword ptr [ebp - 0x20]
00501664 mov eax, dword ptr [eax + ecx*4]
00501667 cmp dword ptr [eax + 0x314], 0
0050166e jne 0x5016aa
00501670 movss xmm0, dword ptr [eax + 0x294]
00501678 movss xmm1, dword ptr [eax + 0x298]
00501680 subss xmm1, dword ptr [edi + 0x298]
00501688 subss xmm0, dword ptr [edi + 0x294]
00501690 mulss xmm1, xmm1
00501694 mulss xmm0, xmm0
00501698 addss xmm1, xmm0
0050169c test esi, esi
0050169e je 0x5016a5
005016a0 comiss xmm2, xmm1
005016a3 jbe 0x5016aa
005016a5 mov esi, eax
005016a7 movaps xmm2, xmm1
005016aa inc ecx
005016ab cmp ecx, edx
005016ad jb 0x501661
005016af test esi, esi
005016b1 je 0x501711
005016b3 mov ecx, dword ptr [edi + 0x318]
005016b9 lea eax, [edi + 0x318]
005016bf test ecx, ecx
005016c1 je 0x5016db
005016c3 mov dword ptr [ebp - 0x64], eax
005016c6 add ecx, 0x324
005016cc lea eax, [ebp - 0x64]
005016cf push eax
005016d0 call 0x4bc3c0
005016d5 lea eax, [edi + 0x318]
005016db push eax
005016dc mov ecx, esi
005016de mov dword ptr [eax], esi
005016e0 call 0x4bae70
005016e5 mov ecx, dword ptr [esi + 0x314]
005016eb add esi, 0x314
005016f1 test ecx, ecx
005016f3 je 0x501707
005016f5 lea eax, [ebp - 0x64]
005016f8 mov dword ptr [ebp - 0x64], esi
005016fb push eax
005016fc add ecx, 0x324
00501702 call 0x4bc3c0
00501707 push esi
00501708 mov ecx, edi
0050170a mov dword ptr [esi], edi
0050170c call 0x4bae70
00501711 or dword ptr [edi + 0x160], 0x11
00501718 or dword ptr [edi + 0x164], 8
0050171f cmp byte ptr [ebp - 0x24], 0
00501723 mov byte ptr [edi + 0x308], 1
0050172a jne 0x502dc9
00501730 push dword ptr [ebp - 0x20]
00501733 call 0x9eace5
00501738 add esp, 4
0050173b jmp 0x502dc9
00501740 cmp eax, 0x29
00501743 jne 0x5017b1
00501745 cmp dword ptr [edi + 0x2c], 3
00501749 jne 0x5017b1
0050174b or dword ptr [edi + 0x160], 0x11
00501752 or dword ptr [edi + 0x164], 8
00501759 mov byte ptr [edi + 0x308], 1
00501760 movss xmm0, dword ptr [edi + 0x28c]
00501768 ucomiss xmm0, dword ptr [0xc02fec]
0050176f lahf 
00501770 test ah, 0x44
00501773 jp 0x501797
00501775 movss xmm0, dword ptr [edi + 0x290]
0050177d ucomiss xmm0, dword ptr [0xc02ff0]
00501784 lahf 
00501785 test ah, 0x44
00501788 jp 0x501797
0050178a push 1
0050178c lea ecx, [edi + 0x364]
00501792 call 0x7a6180
00501797 mov eax, dword ptr [edi + 0x318]
0050179d test eax, eax
0050179f je 0x5017aa
005017a1 cmp byte ptr [eax + 0x16b], 0
005017a8 je 0x5017b1
005017aa mov eax, dword ptr [edi]
005017ac mov ecx, edi
005017ae call dword ptr [eax + 0x24]
005017b1 movss xmm2, dword ptr [0xb6aa3c]
005017b9 lea esi, [edi + 0x294]
005017bf movss xmm0, dword ptr [esi]
005017c3 subss xmm0, xmm2
005017c7 movss xmm4, dword ptr [0xb6a480]
005017cf movss xmm3, dword ptr [0xb6ab20]
005017d7 mov ecx, dword ptr [0xbfd65c]
005017dd divss xmm0, xmm2
005017e1 mov ecx, dword ptr [ecx + 0x18190]
005017e7 addss xmm0, xmm4
005017eb cvttss2si edx, xmm0
005017ef movss xmm0, dword ptr [esi + 4]
005017f4 subss xmm0, xmm3
005017f8 divss xmm0, xmm2
005017fc addss xmm0, xmm4
00501800 cvttss2si eax, xmm0
00501804 test edx, edx
00501806 js 0x501860
00501808 cmp edx, dword ptr [ecx + 0xc]
0050180b jge 0x501860
0050180d test eax, eax
0050180f js 0x501860
00501811 cmp eax, dword ptr [ecx + 0x10]
00501814 jge 0x501860
00501816 imul eax, dword ptr [ecx + 0xc]
0050181a add eax, edx
0050181c cmp eax, 0x1bf
00501821 ja 0x501860
00501823 add eax, 0x1db
00501828 mov dword ptr [ebp - 0x48], 0x3e8
0050182f lea eax, [ecx + eax*4]
00501832 mov dword ptr [ebp - 0x58], eax
00501835 mov eax, dword ptr [eax]
00501837 mov dword ptr [ebp - 0x5c], eax
0050183a cdq 
0050183b idiv dword ptr [ebp - 0x48]
0050183e cmp edx, 0x384
00501844 jge 0x501860
00501846 mov eax, dword ptr [ebp - 0x5c]
00501849 mov ecx, dword ptr [ebp - 0x58]
0050184c sub eax, edx
0050184e add eax, 0x384
00501853 mov dword ptr [ecx], eax
00501855 mov eax, dword ptr [0xbfd65c]
0050185a mov ecx, dword ptr [eax + 0x18190]
00501860 mov eax, dword ptr [edi + 0x364]
00501866 movss xmm0, dword ptr [eax + 0x294]
0050186e movss xmm1, dword ptr [eax + 0x298]
00501876 subss xmm0, xmm2
0050187a subss xmm1, xmm3
0050187e divss xmm0, xmm2
00501882 divss xmm1, xmm2
00501886 addss xmm0, xmm4
0050188a addss xmm1, xmm4
0050188e cvttss2si eax, xmm0
00501892 cvttss2si edx, xmm1
00501896 mov dword ptr [ebp - 0x58], eax
00501899 test eax, eax
0050189b js 0x5018b9
0050189d mov eax, dword ptr [ecx + 0xc]
005018a0 cmp dword ptr [ebp - 0x58], eax
005018a3 jge 0x5018b9
005018a5 test edx, edx
005018a7 js 0x5018b9
005018a9 cmp edx, dword ptr [ecx + 0x10]
005018ac jge 0x5018b9
005018ae cvttss2si ecx, xmm0
005018b2 imul eax, edx
005018b5 add eax, ecx
005018b7 jmp 0x5018bc
005018b9 or eax, 0xffffffff
005018bc movss xmm3, dword ptr [0xb6a53c]
005018c4 movss xmm0, dword ptr [0xb6a560]
005018cc movaps xmm2, xmm3
005018cf movss xmm4, dword ptr [0xb6a594]
005018d7 mov dword ptr [edi + 0x384], eax
005018dd cvttss2si ecx, dword ptr [edi + 0x2fc]
005018e5 cvttss2si eax, dword ptr [edi + 0x2f8]
005018ed movss dword ptr [ebp - 0x5c], xmm0
005018f2 sub ecx, eax
005018f4 cmp dword ptr [edi + 0x28], 0x29
005018f8 jne 0x501937
005018fa mov eax, dword ptr [edi + 0x2c]
005018fd cmp eax, 1
00501900 jne 0x50190c
00501902 movss xmm2, dword ptr [0xb6a680]
0050190a jmp 0x501937
0050190c cmp eax, 2
0050190f jne 0x50191b
00501911 movss xmm2, dword ptr [0xb6a4c4]
00501919 jmp 0x501937
0050191b cmp eax, 3
0050191e jne 0x50192a
00501920 movaps xmm0, xmm4
00501923 movss dword ptr [ebp - 0x5c], xmm0
00501928 jmp 0x501937
0050192a cmp eax, 4
0050192d jne 0x501937
0050192f movss xmm2, dword ptr [0xb6a4e0]
00501937 mov eax, dword ptr [edi + 0xab4]
0050193d cmp eax, 4
00501940 je 0x5020f1
00501946 cmp eax, 7
00501949 je 0x5020f1
0050194f cmp byte ptr [ebp - 0x41], 0
00501953 je 0x501e04
00501959 cmp byte ptr [edi + 0x188], 0
00501960 je 0x501d5c
00501966 movss xmm1, dword ptr [edi + 0x190]
0050196e movss xmm0, dword ptr [edi + 0x18c]
00501976 mulss xmm0, xmm0
0050197a mulss xmm1, xmm1
0050197e addss xmm0, xmm1
00501982 call 0x4228c0
00501987 comiss xmm0, dword ptr [0xb6a940]
0050198e jbe 0x501d5c
00501994 lea eax, [ebp - 0x1c]
00501997 push eax
00501998 lea ecx, [edi + 0x18c]
0050199e call 0x962560
005019a3 movss xmm1, dword ptr [edi + 0x198]
005019ab movss xmm0, dword ptr [edi + 0x194]
005019b3 mulss xmm1, dword ptr [eax + 4]
005019b8 mulss xmm0, dword ptr [eax]
005019bc addss xmm1, xmm0
005019c0 comiss xmm1, dword ptr [0xb6a5a4]
005019c7 jbe 0x501d5c
005019cd mov ecx, dword ptr [0xbfd65c]
005019d3 push 4
005019d5 call 0x6d5ad0
005019da mov esi, dword ptr [0xbfd680]
005019e0 lea ecx, [ebp - 0x48]
005019e3 mov dword ptr [ebp - 0x48], 0x30
005019ea call 0x8b1340
005019ef sub esp, 8
005019f2 mov dword ptr [esp + 4], 0
005019fa mov dword ptr [esp], 0x3f800000
00501a01 push 0
00501a03 push 2
00501a05 push ecx
00501a06 mov dword ptr [esp], 0x3f19999a
00501a0d lea ecx, [esi + 0x29de0]
00501a13 push dword ptr [ebp - 0x48]
00501a16 call 0x888de0
00501a1b mov esi, dword ptr [0xbfd680]
00501a21 lea ecx, [ebp - 0x48]
00501a24 mov dword ptr [ebp - 0x48], 0x1e3
00501a2b call 0x8b1340
00501a30 sub esp, 8
00501a33 mov dword ptr [esp + 4], 0
00501a3b mov dword ptr [esp], 0x3f800000
00501a42 push 0
00501a44 push 0x2d
00501a46 push ecx
00501a47 mov dword ptr [esp], 0x3f333333
00501a4e lea ecx, [esi + 0x29de0]
00501a54 push dword ptr [ebp - 0x48]
00501a57 call 0x888de0
00501a5c mov eax, dword ptr [0xbfd65c]
00501a61 mov esi, dword ptr [eax + 0x18190]
00501a67 lea eax, [edi + 0x294]
00501a6d push eax
00501a6e mov ecx, esi
00501a70 call 0x7ce950
00501a75 mov esi, dword ptr [esi + 0xc]
00501a78 mov ecx, eax
00501a7a cdq 
00501a7b idiv esi
00501a7d mov eax, ecx
00501a7f movss xmm2, dword ptr [0xb6aa3c]
00501a87 push 0xc02fec
00501a8c lea ecx, [ebp - 0x40]
00501a8f movd xmm0, edx
00501a93 cdq 
00501a94 idiv esi
00501a96 cvtdq2ps xmm0, xmm0
00501a99 mulss xmm0, xmm2
00501a9d addss xmm0, xmm2
00501aa1 movss dword ptr [ebp - 0x50], xmm0
00501aa6 movd xmm0, eax
00501aaa cvtdq2ps xmm0, xmm0
00501aad mulss xmm0, xmm2
00501ab1 addss xmm0, dword ptr [0xb6ab20]
00501ab9 movss dword ptr [ebp - 0x4c], xmm0
00501abe call 0x402120
00501ac3 push eax
00501ac4 push 0xc02fec
00501ac9 lea edx, [edi + 0x294]
00501acf mov ecx, 2
00501ad4 call 0x6aead0
00501ad9 add esp, 0xc
00501adc call 0x6c3d90
00501ae1 mov ecx, dword ptr [0xbfd65c]
00501ae7 push eax
00501ae8 push 0
00501aea push 0
00501aec push 0xc02fec
00501af1 lea eax, [ebp - 0x50]
00501af4 push eax
00501af5 push 0xf
00501af7 push 0x3e8
00501afc call 0x422e20
00501b01 movaps xmm0, xmmword ptr [0xb6c610]
00501b08 mov esi, eax
00501b0a movups xmmword ptr [ebp - 0x40], xmm0
00501b0e mov dword ptr [ebp - 0x20], 0
00501b15 movaps xmm0, xmmword ptr [0xb6be10]
00501b1c movups xmmword ptr [ebp - 0x30], xmm0
00501b20 mov eax, dword ptr [esi]
00501b22 lea ecx, [ebp - 0x40]
00501b25 push 1
00501b27 push 0
00501b29 push 0xff
00501b2e push -1
00501b30 push ecx
00501b31 mov ecx, esi
00501b33 mov dword ptr [ebp - 0x1c], 0
00501b3a mov dword ptr [ebp - 0x18], 0
00501b41 call dword ptr [eax + 0x38]
00501b44 mov eax, dword ptr [esi]
00501b46 mov ecx, esi
00501b48 call dword ptr [eax + 0xc]
00501b4b mov dword ptr [ebp - 0x48], 0xffffffff
00501b52 call 0x6c3d90
00501b57 mov ecx, dword ptr [0xbfd65c]
00501b5d push eax
00501b5e push 0
00501b60 push edi
00501b61 push 0xc02fec
00501b66 lea eax, [ebp - 0x50]
00501b69 push eax
00501b6a push 0x94
00501b6f push 0x3e8
00501b74 call 0x422e20
00501b79 movaps xmm0, xmmword ptr [0xb6c790]
00501b80 lea ecx, [ebp - 0x40]
00501b83 push 1
00501b85 mov esi, eax
00501b87 mov dword ptr [ebp - 0x20], 0
00501b8e push 0
00501b90 push 0xff
00501b95 push -1
00501b97 mov eax, dword ptr [esi]
00501b99 movups xmmword ptr [ebp - 0x40], xmm0
00501b9d mov dword ptr [ebp - 0x68], esi
00501ba0 xorps xmm0, xmm0
00501ba3 mov dword ptr [ebp - 0x1c], 0xbf800000
00501baa push ecx
00501bab mov ecx, esi
00501bad mov dword ptr [ebp - 0x18], 0xbf800000
00501bb4 movups xmmword ptr [ebp - 0x30], xmm0
00501bb8 call dword ptr [eax + 0x38]
00501bbb mov ecx, dword ptr [esi + 0x314]
00501bc1 add esi, 0x314
00501bc7 test ecx, ecx
00501bc9 je 0x501bdd
00501bcb lea eax, [ebp - 0x58]
00501bce mov dword ptr [ebp - 0x58], esi
00501bd1 push eax
00501bd2 add ecx, 0x324
00501bd8 call 0x4bc3c0
00501bdd push esi
00501bde mov ecx, edi
00501be0 mov dword ptr [esi], edi
00501be2 call 0x4bae70
00501be7 movss xmm1, dword ptr [edi + 0x28c]
00501bef movss xmm0, dword ptr [edi + 0x290]
00501bf7 call 0x447a80
00501bfc mov ecx, dword ptr [ebp - 0x48]
00501bff mulss xmm0, dword ptr [0xb6aa84]
00501c07 mov eax, dword ptr [ebp - 0x68]
00501c0a movd xmm1, ecx
00501c0e inc ecx
00501c0f mov dword ptr [ebp - 0x48], ecx
00501c12 addss xmm0, dword ptr [0xb6ab88]
00501c1a cvtdq2ps xmm1, xmm1
00501c1d mulss xmm1, dword ptr [0xb6aae4]
00501c25 addss xmm0, xmm1
00501c29 movss dword ptr [eax + 0x3c4], xmm0
00501c31 cmp ecx, 1
00501c34 jle 0x501b52
00501c3a mov dword ptr [edi + 0xb08], 0xc0a00000
00501c44 lea esi, [edi + 0x294]
00501c4a movss xmm3, dword ptr [edi + 0x198]
00501c52 movss xmm1, dword ptr [edi + 0x194]
00501c5a movaps xmm2, xmm3
00501c5d mulss xmm2, dword ptr [edi + 0x190]
00501c65 movaps xmm0, xmm1
00501c68 mulss xmm0, dword ptr [edi + 0x18c]
00501c70 movss xmm4, dword ptr [edi + 0x2b8]
00501c78 addss xmm2, xmm0
00501c7c movaps xmm0, xmm2
00501c7f mulss xmm2, xmm3
00501c83 mulss xmm0, xmm1
00501c87 mulss xmm2, dword ptr [0xb6a8f4]
00501c8f mulss xmm0, dword ptr [0xb6a8f4]
00501c97 subss xmm4, xmm0
00501c9b movss xmm0, dword ptr [edi + 0x2bc]
00501ca3 subss xmm0, xmm2
00501ca7 movss dword ptr [edi + 0x2b8], xmm4
00501caf movss dword ptr [edi + 0x2bc], xmm0
00501cb7 mov dword ptr [edi + 0xaf4], 0xffffffd3
00501cc1 movss xmm0, dword ptr [0xc02fec]
00501cc9 movss dword ptr [edi + 0x368], xmm0
00501cd1 movss xmm0, dword ptr [0xc02ff0]
00501cd9 movss dword ptr [edi + 0x36c], xmm0
00501ce1 movss xmm0, dword ptr [0xc02fec]
00501ce9 movss dword ptr [edi + 0x370], xmm0
00501cf1 movss xmm0, dword ptr [0xc02ff0]
00501cf9 movss dword ptr [edi + 0x374], xmm0
00501d01 mov dword ptr [edi + 0xab4], 4
00501d0b movss xmm0, dword ptr [0xc02fec]
00501d13 movss dword ptr [edi + 0x28c], xmm0
00501d1b movss xmm0, dword ptr [0xc02ff0]
00501d23 movss dword ptr [edi + 0x290], xmm0
00501d2b cmp byte ptr [edi + 0x188], 0
00501d32 je 0x501d5c
00501d34 movss xmm0, dword ptr [edi + 0x2bc]
00501d3c mulss xmm4, dword ptr [0xb6a214]
00501d44 mulss xmm0, dword ptr [0xb6a214]
00501d4c movss dword ptr [edi + 0x2b8], xmm4
00501d54 movss dword ptr [edi + 0x2bc], xmm0
00501d5c movss xmm1, dword ptr [edi + 0x2bc]
00501d64 movss xmm0, dword ptr [edi + 0x2b8]
00501d6c mulss xmm0, xmm0
00501d70 mulss xmm1, xmm1
00501d74 addss xmm0, xmm1
00501d78 call 0x4228c0
00501d7d subss xmm0, dword ptr [0xb6a940]
00501d85 mulss xmm0, dword ptr [0xb6a2ec]
00501d8d comiss xmm0, dword ptr [0xb6a18c]
00501d94 movss dword ptr [ebp - 0x68], xmm0
00501d99 jbe 0x501e04
00501d9b push 0
00501d9d push 3
00501d9f mov ecx, edi
00501da1 call 0x684790
00501da6 test al, al
00501da8 je 0x501e04
00501daa movaps xmm0, xmmword ptr [0xb6c610]
00501db1 lea ecx, [ebp - 0x40]
00501db4 mov eax, dword ptr [edi]
00501db6 push 1
00501db8 movups xmmword ptr [ebp - 0x40], xmm0
00501dbc push 1
00501dbe movss xmm0, dword ptr [ebp - 0x68]
00501dc3 addss xmm0, dword ptr [0xb6a274]
00501dcb push 1
00501dcd push 3
00501dcf push ecx
00501dd0 mov ecx, edi
00501dd2 mov dword ptr [ebp - 0x30], 0x40400000
00501dd9 mov dword ptr [ebp - 0x2c], 0x3e99999a
00501de0 mov dword ptr [ebp - 0x28], 0
00501de7 movss dword ptr [ebp - 0x24], xmm0
00501dec mov dword ptr [ebp - 0x20], 0
00501df3 mov dword ptr [ebp - 0x1c], 0
00501dfa mov dword ptr [ebp - 0x18], 0
00501e01 call dword ptr [eax + 0x38]
00501e04 cmp dword ptr [edi + 0xab4], 4
00501e0b je 0x50256c
00501e11 cmp byte ptr [edi + 0x188], 0
00501e18 jne 0x50203d
00501e1e push 0
00501e20 push 0x1000a00
00501e25 mov ecx, edi
00501e27 call 0x4122f0
00501e2c test al, al
00501e2e jne 0x50203d
00501e34 cmp dword ptr [edi + 0x28], 0x11b
00501e3b jne 0x501ef6
00501e41 cmp dword ptr [edi + 0xe6c], -1
00501e48 je 0x501e5f
00501e4a push 9
00501e4c mov ecx, edi
00501e4e call 0x6af050
00501e53 xor ecx, ecx
00501e55 test al, al
00501e57 sete cl
00501e5a jmp 0x501eee
00501e5f push ecx
00501e60 lea eax, [ebp - 0x1c]
00501e63 mov dword ptr [esp], 0x42200000
00501e6a push eax
00501e6b lea ecx, [edi + 0x28c]
00501e71 call 0x9628d0
00501e76 movss xmm0, dword ptr [esi]
00501e7a mov ecx, edi
00501e7c movss dword ptr [ebp - 0x48], xmm0
00501e81 movss xmm0, dword ptr [eax]
00501e85 movss dword ptr [ebp - 0x4c], xmm0
00501e8a movss xmm0, dword ptr [esi + 4]
00501e8f movss dword ptr [ebp - 0x68], xmm0
00501e94 movss xmm0, dword ptr [eax + 4]
00501e99 movss dword ptr [ebp - 0x58], xmm0
00501e9e call 0x695680
00501ea3 movss xmm1, dword ptr [ebp - 0x68]
00501ea8 xor ecx, ecx
00501eaa subss xmm1, dword ptr [ebp - 0x58]
00501eaf movss xmm2, dword ptr [eax + 0x298]
00501eb7 movss xmm0, dword ptr [eax + 0x294]
00501ebf subss xmm2, xmm1
00501ec3 movss xmm1, dword ptr [ebp - 0x48]
00501ec8 subss xmm1, dword ptr [ebp - 0x4c]
00501ecd mulss xmm2, dword ptr [edi + 0x2bc]
00501ed5 subss xmm0, xmm1
00501ed9 mulss xmm0, dword ptr [edi + 0x2b8]
00501ee1 addss xmm2, xmm0
00501ee5 xorps xmm0, xmm0
00501ee8 comiss xmm0, xmm2
00501eeb seta cl
00501eee test ecx, ecx
00501ef0 jne 0x50203d
00501ef6 movss xmm0, dword ptr [ebp - 0x5c]
00501efb lea eax, [edi + 0x28c]
00501f01 mulss xmm0, dword ptr [edi + 0x2c4]
00501f09 mov ecx, edi
00501f0b push 0
00501f0d push eax
00501f0e movss dword ptr [edi + 0x2c4], xmm0
00501f16 call 0x422b60
00501f1b cmp byte ptr [ebp - 0x41], 0
00501f1f je 0x501fab
00501f25 movss xmm1, dword ptr [edi + 0x290]
00501f2d movss xmm0, dword ptr [edi + 0x28c]
00501f35 mulss xmm0, xmm0
00501f39 mulss xmm1, xmm1
00501f3d addss xmm0, xmm1
00501f41 call 0x4228c0
00501f46 movss xmm1, dword ptr [0xb6a8cc]
00501f4e comiss xmm1, xmm0
00501f51 jbe 0x501fab
00501f53 lea eax, [ebp - 0x1c]
00501f56 push eax
00501f57 lea ecx, [edi + 0x28c]
00501f5d call 0x962560
00501f62 movss xmm2, dword ptr [edi + 0x2f4]
00501f6a movss xmm3, dword ptr [eax + 4]
00501f6f movss xmm0, dword ptr [eax]
00501f73 mulss xmm0, dword ptr [0xb6a290]
00501f7b mulss xmm3, dword ptr [0xb6a290]
00501f83 mulss xmm0, xmm2
00501f87 mulss xmm3, xmm2
00501f8b addss xmm0, dword ptr [edi + 0x28c]
00501f93 addss xmm3, dword ptr [edi + 0x290]
00501f9b movss dword ptr [edi + 0x28c], xmm0
00501fa3 movss dword ptr [edi + 0x290], xmm3
00501fab mov ecx, dword ptr [0xbfd65c]
00501fb1 lea eax, [ebp - 0x50]
00501fb4 push dword ptr [edi + 0x384]
00501fba push eax
00501fbb mov ecx, dword ptr [ecx + 0x18190]
00501fc1 call 0x7cebc0
00501fc6 movss xmm2, dword ptr [0xb6c980]
00501fce movss xmm1, dword ptr [edi + 0x2b8]
00501fd6 movss xmm0, dword ptr [edi + 0x2bc]
00501fde andps xmm1, xmm2
00501fe1 andps xmm0, xmm2
00501fe4 comiss xmm1, xmm0
00501fe7 jbe 0x502017
00501fe9 movss xmm0, dword ptr [edi + 0x298]
00501ff1 movss xmm1, dword ptr [ebp - 0x4c]
00501ff6 mulss xmm1, dword ptr [0xb6a2cc]
00501ffe mulss xmm0, dword ptr [0xb6a5a4]
00502006 addss xmm1, xmm0
0050200a movss dword ptr [edi + 0x298], xmm1
00502012 jmp 0x502574
00502017 movss xmm0, dword ptr [esi]
0050201b movss xmm1, dword ptr [ebp - 0x50]
00502020 mulss xmm1, dword ptr [0xb6a2cc]
00502028 mulss xmm0, dword ptr [0xb6a5a4]
00502030 addss xmm1, xmm0
00502034 movss dword ptr [esi], xmm1
00502038 jmp 0x502574
0050203d cmp byte ptr [edi + 0x188], 0
00502044 movss xmm0, dword ptr [0xc02fec]
0050204c movss xmm2, dword ptr [0xb6c980]
00502054 movss dword ptr [edi + 0x368], xmm0
0050205c movss xmm0, dword ptr [0xc02ff0]
00502064 movss dword ptr [edi + 0x36c], xmm0
0050206c movss xmm0, dword ptr [0xc02fec]
00502074 movss dword ptr [edi + 0x370], xmm0
0050207c movss xmm0, dword ptr [0xc02ff0]
00502084 movss dword ptr [edi + 0x374], xmm0
0050208c mov dword ptr [edi + 0xab4], 4
00502096 movss xmm0, dword ptr [0xc02fec]
0050209e movss dword ptr [edi + 0x28c], xmm0
005020a6 movss xmm0, dword ptr [0xc02ff0]
005020ae movss dword ptr [edi + 0x290], xmm0
005020b6 je 0x502574
005020bc movss xmm0, dword ptr [edi + 0x2b8]
005020c4 mulss xmm0, dword ptr [0xb6a214]
005020cc movss dword ptr [edi + 0x2b8], xmm0
005020d4 movss xmm0, dword ptr [edi + 0x2bc]
005020dc mulss xmm0, dword ptr [0xb6a214]
005020e4 movss dword ptr [edi + 0x2bc], xmm0
005020ec jmp 0x502574
005020f1 cmp dword ptr [edi + 0x28], 0xfe
005020f8 movss xmm0, dword ptr [0xb6a614]
00502100 movss dword ptr [ebp - 0x48], xmm0
00502105 jne 0x502397
0050210b mov eax, dword ptr [edi + 0x360]
00502111 movaps xmm1, xmm0
00502114 sub eax, ecx
00502116 cmp dword ptr [edi + 0xe6c], -1
0050211d mov dword ptr [edi + 0x360], eax
00502123 je 0x5021b9
00502129 lea eax, [ebp - 0x50]
0050212c xorps xmm2, xmm2
0050212f push eax
00502130 mov ecx, edi
00502132 call 0x6af0c0
00502137 call 0x6c3d90
0050213c xor edx, edx
0050213e movss xmm3, dword ptr [ebp - 0x50]
00502143 mov ecx, 0xf
00502148 movss xmm4, dword ptr [ebp - 0x4c]
0050214d div ecx
0050214f movaps xmm0, xmm4
00502152 movaps xmm1, xmm3
00502155 andps xmm0, xmmword ptr [0xb6c980]
0050215c add edx, 0x1e
0050215f andps xmm1, xmmword ptr [0xb6c980]
00502166 comiss xmm1, xmm0
00502169 mov dword ptr [edi + 0x360], edx
0050216f xorps xmm0, xmm0
00502172 jbe 0x502183
00502174 xor ecx, ecx
00502176 mov eax, 2
0050217b comiss xmm0, xmm3
0050217e cmova eax, ecx
00502181 jmp 0x502192
00502183 xor eax, eax
00502185 comiss xmm0, xmm4
00502188 setbe al
0050218b lea eax, [eax*2 + 1]
00502192 mulss xmm3, xmm3
00502196 mov dword ptr [edi + 0xb10], eax
0050219c mulss xmm4, xmm4
005021a0 addss xmm3, xmm4
005021a4 movaps xmm0, xmm3
005021a7 call 0x4228c0
005021ac movss xmm3, dword ptr [0xb6a53c]
005021b4 movaps xmm1, xmm0
005021b7 jmp 0x5021e6
005021b9 test ecx, ecx
005021bb je 0x5021e6
005021bd test eax, eax
005021bf jg 0x5021e6
005021c1 call 0x6c3d90
005021c6 xor edx, edx
005021c8 mov ecx, 0xf
005021cd div ecx
005021cf add edx, 0x1e
005021d2 mov dword ptr [edi + 0x360], edx
005021d8 call 0x6c3d90
005021dd and eax, 3
005021e0 mov dword ptr [edi + 0xb10], eax
005021e6 mov eax, dword ptr [edi + 0xb10]
005021ec cmp eax, 3
005021ef ja 0x502526
005021f5 jmp dword ptr [eax*4 + 0x502de8]
005021fc movss xmm0, dword ptr [edi + 0x2f4]
00502204 movaps xmm2, xmm1
00502207 mulss xmm2, dword ptr [0xb6a18c]
0050220f mov al, byte ptr [ebp - 0x41]
00502212 mulss xmm1, xmm3
00502216 mulss xmm2, xmm0
0050221a mulss xmm1, xmm0
0050221e addss xmm2, dword ptr [edi + 0x2b8]
00502226 addss xmm1, dword ptr [edi + 0x2bc]
0050222e movss dword ptr [edi + 0x2b8], xmm2
00502236 movss dword ptr [edi + 0x2bc], xmm1
0050223e cmp byte ptr [edi + 0x188], 0
00502245 je 0x502529
0050224b mov dword ptr [edi + 0xb10], 1
00502255 jmp 0x502374
0050225a movss xmm0, dword ptr [edi + 0x2f4]
00502262 movaps xmm2, xmm1
00502265 mulss xmm2, dword ptr [0xb6a18c]
0050226d mov al, byte ptr [ebp - 0x41]
00502270 mulss xmm1, dword ptr [0xb6ae34]
00502278 mulss xmm2, xmm0
0050227c mulss xmm1, xmm0
00502280 addss xmm2, dword ptr [edi + 0x2b8]
00502288 addss xmm1, dword ptr [edi + 0x2bc]
00502290 movss dword ptr [edi + 0x2b8], xmm2
00502298 movss dword ptr [edi + 0x2bc], xmm1
005022a0 cmp byte ptr [edi + 0x188], 0
005022a7 je 0x502529
005022ad mov dword ptr [edi + 0xb10], 3
005022b7 jmp 0x502374
005022bc movss xmm0, dword ptr [edi + 0x2f4]
005022c4 movaps xmm2, xmm1
005022c7 mulss xmm2, dword ptr [0xb6ae34]
005022cf mov al, byte ptr [ebp - 0x41]
005022d2 mulss xmm1, dword ptr [0xb6a18c]
005022da mulss xmm2, xmm0
005022de mulss xmm1, xmm0
005022e2 addss xmm2, dword ptr [edi + 0x2b8]
005022ea addss xmm1, dword ptr [edi + 0x2bc]
005022f2 movss dword ptr [edi + 0x2b8], xmm2
005022fa movss dword ptr [edi + 0x2bc], xmm1
00502302 cmp byte ptr [edi + 0x188], 0
00502309 je 0x502529
0050230f mov dword ptr [edi + 0xb10], 2
00502319 jmp 0x502374
0050231b movss xmm0, dword ptr [edi + 0x2f4]
00502323 movaps xmm2, xmm1
00502326 mulss xmm1, dword ptr [0xb6a18c]
0050232e mov al, byte ptr [ebp - 0x41]
00502331 mulss xmm2, xmm3
00502335 mulss xmm1, xmm0
00502339 mulss xmm2, xmm0
0050233d addss xmm1, dword ptr [edi + 0x2bc]
00502345 addss xmm2, dword ptr [edi + 0x2b8]
0050234d movss dword ptr [edi + 0x2bc], xmm1
00502355 movss dword ptr [edi + 0x2b8], xmm2
0050235d cmp byte ptr [edi + 0x188], 0
00502364 je 0x502529
0050236a mov dword ptr [edi + 0xb10], 0
00502374 movss xmm0, dword ptr [esi]
00502378 subss xmm0, xmm2
0050237c movss dword ptr [esi], xmm0
00502380 movss xmm0, dword ptr [esi + 4]
00502385 subss xmm0, dword ptr [edi + 0x2bc]
0050238d movss dword ptr [esi + 4], xmm0
00502392 jmp 0x502529
00502397 cmp byte ptr [ebp - 0x41], 0
0050239b je 0x5025c1
005023a1 xorps xmm1, xmm1
005023a4 comiss xmm1, dword ptr [edi + 0xb08]
005023ab ja 0x502549
005023b1 comiss xmm1, dword ptr [edi + 0x2a8]
005023b8 ja 0x502549
005023be mov eax, dword ptr [edi + 0xaf4]
005023c4 test eax, eax
005023c6 jns 0x5023e8
005023c8 movss xmm0, dword ptr [edi + 0x2c4]
005023d0 inc eax
005023d1 mulss xmm0, xmm4
005023d5 mov dword ptr [edi + 0xaf4], eax
005023db movss dword ptr [edi + 0x2c4], xmm0
005023e3 jmp 0x502549
005023e8 push 0
005023ea push ecx
005023eb lea ecx, [edi + 0x364]
005023f1 movss dword ptr [esp], xmm2
005023f6 call 0x7a51e0
005023fb mov al, byte ptr [ebp - 0x41]
005023fe test al, al
00502400 je 0x502529
00502406 cmp dword ptr [edi + 0xab4], 7
0050240d jne 0x502461
0050240f movss xmm1, dword ptr [0xb6a9c8]
00502417 xorps xmm2, xmm2
0050241a mov ecx, edi
0050241c call 0x6847e0
00502421 test eax, eax
00502423 je 0x502447
00502425 call 0x6c3d90
0050242a xor edx, edx
0050242c mov ecx, 0xa
00502431 div ecx
00502433 test edx, edx
00502435 jne 0x502447
00502437 mov dword ptr [edi + 0xaf4], edx
0050243d mov dword ptr [edi + 0xab4], 7
00502447 movss xmm0, dword ptr [ebp - 0x5c]
0050244c mulss xmm0, dword ptr [edi + 0x2c4]
00502454 movss dword ptr [edi + 0x2c4], xmm0
0050245c jmp 0x502546
00502461 mov ecx, dword ptr [edi + 0xaf4]
00502467 mov eax, dword ptr [edi + 0x160]
0050246d inc ecx
0050246e and eax, 0x1000a00
00502473 mov dword ptr [edi + 0xaf4], ecx
00502479 or eax, 0
0050247c jne 0x502495
0050247e cmp ecx, 0x5a
00502481 jle 0x50249f
00502483 call 0x6c3d90
00502488 xor edx, edx
0050248a mov ecx, 0x14
0050248f div ecx
00502491 test edx, edx
00502493 jne 0x50249f
00502495 mov dword ptr [edi + 0xab4], 4
0050249f mov ecx, edi
005024a1 call 0x695680
005024a6 push 1
005024a8 push 0
005024aa mov ecx, dword ptr [eax + 0x294]
005024b0 mov eax, dword ptr [eax + 0x298]
005024b6 push ecx
005024b7 mov dword ptr [ebp - 0x4c], eax
005024ba lea eax, [ebp - 0x50]
005024bd mov dword ptr [ebp - 0x50], ecx
005024c0 lea ecx, [edi + 0x364]
005024c6 mov dword ptr [esp], 0x3f28f5c3
005024cd push eax
005024ce call 0x7a3650
005024d3 movss xmm1, dword ptr [edi + 0x2bc]
005024db movss xmm0, dword ptr [edi + 0x2b8]
005024e3 mulss xmm0, xmm0
005024e7 mulss xmm1, xmm1
005024eb addss xmm0, xmm1
005024ef call 0x4228c0
005024f4 lea edx, [edi + 0x2b8]
005024fa movaps xmm5, xmm0
005024fd lea ecx, [ebp - 0x1c]
00502500 call 0x6593a0
00502505 movaps xmm1, xmm5
00502508 mulss xmm1, dword ptr [eax]
0050250c mulss xmm5, dword ptr [eax + 4]
00502511 movss dword ptr [edi + 0x2b8], xmm1
00502519 movss dword ptr [edi + 0x2bc], xmm5
00502521 jmp 0x502447
00502526 mov al, byte ptr [ebp - 0x41]
00502529 movss xmm0, dword ptr [ebp - 0x5c]
0050252e mulss xmm0, dword ptr [edi + 0x2c4]
00502536 movss dword ptr [edi + 0x2c4], xmm0
0050253e test al, al
00502540 je 0x5025e9
00502546 xorps xmm1, xmm1
00502549 cmp dword ptr [edi + 0xaf4], 0
00502550 jl 0x50256c
00502552 movss xmm0, dword ptr [edi + 0x2a8]
0050255a comiss xmm0, xmm1
0050255d jb 0x50256c
0050255f movss xmm0, dword ptr [edi + 0xb08]
00502567 comiss xmm0, xmm1
0050256a jae 0x5025e9
0050256c movss xmm2, dword ptr [0xb6c980]
00502574 cmp dword ptr [edi + 0xab4], 8
0050257b jne 0x502a19
00502581 movss xmm4, dword ptr [edi + 0x28c]
00502589 movss xmm3, dword ptr [edi + 0x290]
00502591 movaps xmm1, xmm4
00502594 movaps xmm0, xmm3
00502597 andps xmm1, xmm2
0050259a andps xmm0, xmm2
0050259d comiss xmm1, xmm0
005025a0 xorps xmm0, xmm0
005025a3 ja 0x502a41
005025a9 comiss xmm0, xmm3
005025ac jbe 0x502a58
005025b2 mov esi, 0xb406e4
005025b7 mov eax, 1
005025bc jmp 0x502a62
005025c1 push 0
005025c3 push ecx
005025c4 lea ecx, [edi + 0x364]
005025ca movss dword ptr [esp], xmm2
005025cf call 0x7a51e0
005025d4 movss xmm0, dword ptr [ebp - 0x5c]
005025d9 mulss xmm0, dword ptr [edi + 0x2c4]
005025e1 movss dword ptr [edi + 0x2c4], xmm0
005025e9 mov eax, dword ptr [edi + 0xe6c]
005025ef cmp eax, -1
005025f2 je 0x5026df
005025f8 push edi
005025f9 push eax
005025fa push 9
005025fc call 0x8b10b0
00502601 test al, al
00502603 je 0x502662
00502605 movss xmm2, dword ptr [0xb6a2cc]
0050260d lea eax, [ebp - 0x50]
00502610 push eax
00502611 mov ecx, edi
00502613 call 0x6af0c0
00502618 movss xmm0, dword ptr [ebp - 0x50]
0050261d ucomiss xmm0, dword ptr [0xc02fec]
00502624 lahf 
00502625 test ah, 0x44
00502628 jp 0x50263c
0050262a movss xmm0, dword ptr [ebp - 0x4c]
0050262f ucomiss xmm0, dword ptr [0xc02ff0]
00502636 lahf 
00502637 test ah, 0x44
0050263a jnp 0x502662
0050263c lea edx, [ebp - 0x50]
0050263f lea ecx, [ebp - 0x1c]
00502642 call 0x6593a0
00502647 mov ecx, dword ptr [eax]
00502649 mov dword ptr [edi + 0x28c], ecx
0050264f mov eax, dword ptr [eax + 4]
00502652 mov dword ptr [edi + 0x290], eax
00502658 mov dword ptr [edi + 0xab4], 8
00502662 cmp dword ptr [edi + 0x2c], 1
00502666 je 0x502671
00502668 cmp dword ptr [edi + 0x28], 0x11b
0050266f jne 0x5026aa
00502671 cmp dword ptr [edi + 0xab4], 8
00502678 jne 0x5026aa
0050267a movss xmm0, dword ptr [edi + 0x28c]
00502682 mulss xmm0, dword ptr [0xb6a710]
0050268a movss dword ptr [edi + 0x28c], xmm0
00502692 movss xmm0, dword ptr [edi + 0x290]
0050269a mulss xmm0, dword ptr [0xb6a710]
005026a2 movss dword ptr [edi + 0x290], xmm0
005026aa movss xmm0, dword ptr [edi + 0x28c]
005026b2 mulss xmm0, dword ptr [0xb6a6b8]
005026ba movss dword ptr [edi + 0x28c], xmm0
005026c2 movss xmm0, dword ptr [edi + 0x290]
005026ca mulss xmm0, dword ptr [0xb6a6b8]
005026d2 movss dword ptr [edi + 0x290], xmm0
005026da jmp 0x50256c
005026df push dword ptr [edi + 0x20]
005026e2 mov ecx, edi
005026e4 push 3
005026e6 call 0x684790
005026eb test al, al
005026ed je 0x50256c
005026f3 mov eax, dword ptr [edi + 0x160]
005026f9 and eax, 0x1000a00
005026fe or eax, 0
00502701 jne 0x50256c
00502707 call 0x6c3d90
0050270c mov ecx, edi
0050270e movd xmm0, eax
00502712 cvtdq2pd xmm0, xmm0
00502716 shr eax, 0x1f
00502719 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
00502722 cvtpd2ps xmm0, xmm0
00502726 mulss xmm0, dword ptr [0xb6a19c]
0050272e mulss xmm0, dword ptr [0xb6a9b0]
00502736 movss dword ptr [ebp - 0x4c], xmm0
0050273b call 0x695680
00502740 mov ecx, edi
00502742 movss xmm0, dword ptr [eax + 0x2b8]
0050274a movss dword ptr [ebp - 0x68], xmm0
0050274f movss xmm0, dword ptr [eax + 0x2bc]
00502757 movss dword ptr [ebp - 0x58], xmm0
0050275c call 0x695680
00502761 movss xmm1, dword ptr [ebp - 0x4c]
00502766 sub esp, 0xc
00502769 mov esi, dword ptr [0xbfd65c]
0050276f movaps xmm0, xmm1
00502772 mulss xmm0, dword ptr [ebp - 0x68]
00502777 mulss xmm1, dword ptr [ebp - 0x58]
0050277c mov ecx, dword ptr [esi + 0x18190]
00502782 addss xmm0, dword ptr [eax + 0x294]
0050278a movss xmm3, dword ptr [0xb6a9c8]
00502792 addss xmm1, dword ptr [eax + 0x298]
0050279a mov dword ptr [esp + 8], 0x41a00000
005027a2 lea eax, [ebp - 0x50]
005027a5 mov dword ptr [esp + 4], 0x41a00000
005027ad mov dword ptr [esp], 0x41a00000
005027b4 push eax
005027b5 lea eax, [ebp - 0x60]
005027b8 movss dword ptr [ebp - 0x50], xmm0
005027bd push eax
005027be movss dword ptr [ebp - 0x4c], xmm1
005027c3 call 0x7cec10
005027c8 mov esi, dword ptr [esi + 0x18190]
005027ce mov eax, dword ptr [edi + 0x384]
005027d4 cdq 
005027d5 movss xmm2, dword ptr [0xb6aa3c]
005027dd idiv dword ptr [esi + 0xc]
005027e0 movss xmm4, dword ptr [0xb6a9c8]
005027e8 movd xmm3, edx
005027ec cvtdq2ps xmm3, xmm3
005027ef movd xmm1, eax
005027f3 cvtdq2ps xmm1, xmm1
005027f6 mulss xmm3, xmm2
005027fa mulss xmm1, xmm2
005027fe addss xmm3, xmm2
00502802 movss xmm2, dword ptr [0xb6c980]
0050280a addss xmm1, dword ptr [0xb6ab20]
00502812 movss dword ptr [ebp - 0x1c], xmm3
00502817 subss xmm3, dword ptr [ebp - 0x60]
0050281c movss dword ptr [ebp - 0x18], xmm1
00502821 subss xmm1, dword ptr [ebp - 0x5c]
00502826 movaps xmm0, xmm3
00502829 movss dword ptr [ebp - 0x58], xmm3
0050282e andps xmm0, xmm2
00502831 comiss xmm4, xmm0
00502834 movss dword ptr [ebp - 0x4c], xmm1
00502839 movss dword ptr [ebp - 0x68], xmm0
0050283e ja 0x50284f
00502840 movaps xmm0, xmm1
00502843 andps xmm0, xmm2
00502846 comiss xmm4, xmm0
00502849 jbe 0x5029c8
0050284f movaps xmm0, xmm1
00502852 mulss xmm0, xmm1
00502856 movaps xmm1, xmm3
00502859 mulss xmm1, xmm3
0050285d addss xmm0, xmm1
00502861 call 0x4228c0
00502866 movss xmm1, dword ptr [0xb6aba8]
0050286e comiss xmm1, xmm0
00502871 jbe 0x5029c0
00502877 push 0
00502879 push 0
0050287b push 0
0050287d push 0
0050287f push 0
00502881 lea eax, [ebp - 0x60]
00502884 mov ecx, esi
00502886 push eax
00502887 lea eax, [ebp - 0x1c]
0050288a push eax
0050288b call 0x7af4b0
00502890 test al, al
00502892 jne 0x5028a1
00502894 cmp dword ptr [edi + 0x28], 0xfe
0050289b jne 0x5029c0
005028a1 movss xmm1, dword ptr [ebp - 0x4c]
005028a6 movss xmm2, dword ptr [ebp - 0x68]
005028ab movaps xmm0, xmm1
005028ae andps xmm0, xmmword ptr [0xb6c980]
005028b5 comiss xmm2, xmm0
005028b8 xorps xmm0, xmm0
005028bb jbe 0x5028f6
005028bd comiss xmm0, dword ptr [ebp - 0x58]
005028c1 mov dword ptr [edi + 0x290], 0
005028cb jbe 0x5028d7
005028cd movss xmm1, dword ptr [0xb6a614]
005028d5 jmp 0x5028e4
005028d7 movss xmm1, dword ptr [0xb6ae44]
005028df movss dword ptr [ebp - 0x48], xmm1
005028e4 movss dword ptr [edi + 0x28c], xmm1
005028ec xorps xmm1, xmm1
005028ef movss dword ptr [ebp - 0x5c], xmm1
005028f4 jmp 0x50292c
005028f6 comiss xmm0, xmm1
005028f9 mov dword ptr [edi + 0x28c], 0
00502903 jbe 0x50290f
00502905 movss xmm1, dword ptr [0xb6a614]
0050290d jmp 0x502917
0050290f movss xmm1, dword ptr [0xb6ae44]
00502917 movss dword ptr [ebp - 0x5c], xmm1
0050291c movss dword ptr [edi + 0x290], xmm1
00502924 xorps xmm1, xmm1
00502927 movss dword ptr [ebp - 0x48], xmm1
0050292c push 0
0050292e push 0x1000800
00502933 mov ecx, edi
00502935 call 0x4122f0
0050293a test al, al
0050293c je 0x502966
0050293e movss xmm2, dword ptr [ebp - 0x48]
00502943 movss xmm1, dword ptr [ebp - 0x5c]
00502948 xorps xmm2, xmmword ptr [0xb6c9b0]
0050294f xorps xmm1, xmmword ptr [0xb6c9b0]
00502956 movss dword ptr [edi + 0x28c], xmm2
0050295e movss dword ptr [edi + 0x290], xmm1
00502966 cmp dword ptr [edi + 0x28], 0x29
0050296a mov dword ptr [edi + 0xab4], 8
00502974 mov dword ptr [edi + 0xaf4], 0
0050297e jne 0x5029c0
00502980 cmp dword ptr [edi + 0x2c], 4
00502984 movss xmm2, dword ptr [0xb6c980]
0050298c jne 0x5029c8
0050298e movss xmm0, dword ptr [edi + 0x28c]
00502996 mulss xmm0, dword ptr [0xb6a50c]
0050299e movss dword ptr [edi + 0x28c], xmm0
005029a6 movss xmm0, dword ptr [edi + 0x290]
005029ae mulss xmm0, dword ptr [0xb6a50c]
005029b6 movss dword ptr [edi + 0x290], xmm0
005029be jmp 0x5029c8
005029c0 movss xmm2, dword ptr [0xb6c980]
005029c8 cmp dword ptr [edi + 0x2c], 1
005029cc je 0x5029db
005029ce cmp dword ptr [edi + 0x28], 0x11b
005029d5 jne 0x502574
005029db cmp dword ptr [edi + 0xab4], 8
005029e2 jne 0x502a19
005029e4 movss xmm0, dword ptr [edi + 0x28c]
005029ec mulss xmm0, dword ptr [0xb6a710]
005029f4 movss dword ptr [edi + 0x28c], xmm0
005029fc movss xmm0, dword ptr [edi + 0x290]
00502a04 mulss xmm0, dword ptr [0xb6a710]
00502a0c movss dword ptr [edi + 0x290], xmm0
00502a14 jmp 0x502574
00502a19 movss xmm4, dword ptr [edi + 0x2b8]
00502a21 movss xmm3, dword ptr [edi + 0x2bc]
00502a29 movaps xmm1, xmm4
00502a2c movaps xmm0, xmm3
00502a2f andps xmm1, xmm2
00502a32 andps xmm0, xmm2
00502a35 comiss xmm1, xmm0
00502a38 xorps xmm0, xmm0
00502a3b jbe 0x5025a9
00502a41 xor ecx, ecx
00502a43 mov eax, 2
00502a48 comiss xmm0, xmm4
00502a4b mov esi, 0xb42f28
00502a50 cmova eax, ecx
00502a53 mov dword ptr [ebp - 0x48], eax
00502a56 jmp 0x502a62
00502a58 mov esi, 0xb406f0
00502a5d mov eax, 3
00502a62 mov edx, eax
00502a64 lea ecx, [ebp - 0x1c]
00502a67 call 0x659400
00502a6c mov ecx, dword ptr [eax]
00502a6e mov dword ptr [edi + 0xe80], ecx
00502a74 mov eax, dword ptr [eax + 4]
00502a77 mov dword ptr [edi + 0xe84], eax
00502a7d mov edx, dword ptr [edi + 0xaf0]
00502a83 test edx, edx
00502a85 jle 0x502aa1
00502a87 cvttss2si ecx, dword ptr [edi + 0x2f8]
00502a8f cvttss2si eax, dword ptr [edi + 0x2fc]
00502a97 sub ecx, eax
00502a99 add ecx, edx
00502a9b mov dword ptr [edi + 0xaf0], ecx
00502aa1 cmp byte ptr [ebp - 0x41], 0
00502aa5 je 0x502b09
00502aa7 lea eax, [ebp - 0x2c]
00502aaa push eax
00502aab lea ecx, [edi + 0x6c]
00502aae call 0x444be0
00502ab3 mov edx, esi
00502ab5 mov dword ptr [ebp - 0x64], 1
00502abc mov ecx, eax
00502abe call 0x4e5d30
00502ac3 test al, al
00502ac5 jne 0x502b03
00502ac7 movss xmm3, dword ptr [edi + 0x2b8]
00502acf movss xmm0, dword ptr [edi + 0x2bc]
00502ad7 movaps xmm1, xmm3
00502ada andps xmm1, xmmword ptr [0xb6c980]
00502ae1 andps xmm0, xmmword ptr [0xb6c980]
00502ae8 comiss xmm1, xmm0
00502aeb jbe 0x502b09
00502aed movzx eax, byte ptr [edi + 0x13c]
00502af4 xor ecx, ecx
00502af6 xorps xmm0, xmm0
00502af9 comiss xmm0, xmm3
00502afc seta cl
00502aff cmp eax, ecx
00502b01 je 0x502b09
00502b03 mov byte ptr [ebp - 0x51], 1
00502b07 jmp 0x502b0d
00502b09 mov byte ptr [ebp - 0x51], 0
00502b0d test byte ptr [ebp - 0x64], 1
00502b11 je 0x502b1b
00502b13 lea ecx, [ebp - 0x2c]
00502b16 call 0x407be0
00502b1b cmp byte ptr [ebp - 0x51], 0
00502b1f je 0x502b2b
00502b21 mov dword ptr [edi + 0xaf0], 0xf
00502b2b cmp byte ptr [ebp - 0x41], 0
00502b2f je 0x502b5b
00502b31 xorps xmm2, xmm2
00502b34 comiss xmm2, dword ptr [edi + 0xb08]
00502b3b ja 0x502be1
00502b41 comiss xmm2, dword ptr [edi + 0x2a8]
00502b48 ja 0x502be1
00502b4e cmp dword ptr [edi + 0xaf4], 0
00502b55 jl 0x502be1
00502b5b movss xmm3, dword ptr [edi + 0x2b8]
00502b63 lea ecx, [edi + 0x3c]
00502b66 movss xmm1, dword ptr [edi + 0x2bc]
00502b6e movaps xmm0, xmm3
00502b71 mulss xmm1, xmm1
00502b75 mulss xmm0, xmm3
00502b79 addss xmm0, xmm1
00502b7d movss xmm1, dword ptr [0xb6a214]
00502b85 comiss xmm1, xmm0
00502b88 jbe 0x502ba4
00502b8a cmp dword ptr [edi + 0x70], 0
00502b8e je 0x502be1
00502b90 lea ecx, [edi + 0x6c]
00502b93 mov byte ptr [edi + 0x80], 0
00502b9a xorps xmm1, xmm1
00502b9d call 0x403c00
00502ba2 jmp 0x502be1
00502ba4 movss xmm0, dword ptr [edi + 0x2bc]
00502bac andps xmm3, xmmword ptr [0xb6c980]
00502bb3 andps xmm0, xmmword ptr [0xb6c980]
00502bba comiss xmm3, xmm0
00502bbd push 0
00502bbf push esi
00502bc0 jbe 0x502bdc
00502bc2 call 0x4054f0
00502bc7 xorps xmm0, xmm0
00502bca comiss xmm0, dword ptr [edi + 0x2b8]
00502bd1 seta al
00502bd4 mov byte ptr [edi + 0x13c], al
00502bda jmp 0x502be1
00502bdc call 0x4054f0
00502be1 cmp dword ptr [edi + 0x28], 0x11b
00502be8 jne 0x502c8b
00502bee push dword ptr [edi + 0x20]
00502bf1 mov ecx, edi
00502bf3 push 7
00502bf5 call 0x684790
00502bfa test al, al
00502bfc je 0x502c8b
00502c02 call 0x6c3d90
00502c07 mov ecx, dword ptr [0xbfd65c]
00502c0d push 0
00502c0f push 0xbeaaec
00502c14 push 0xbeab18
00502c19 push 0
00502c1b push eax
00502c1c push 0
00502c1e push edi
00502c1f push 0xc02fec
00502c24 lea eax, [edi + 0x294]
00502c2a push eax
00502c2b push 0x16
00502c2d push 0x3e8
00502c32 call 0x422e20
00502c37 push eax
00502c38 call 0x9ec34c
00502c3d movss xmm1, dword ptr [0xbc7a28]
00502c45 mov ecx, eax
00502c47 movss xmm0, dword ptr [0xbc7a2c]
00502c4f add esp, 0x14
00502c52 mulss xmm1, dword ptr [0xb6a480]
00502c5a mulss xmm0, dword ptr [0xb6a480]
00502c62 mov eax, dword ptr [ecx]
00502c64 movss dword ptr [ecx + 0xd8], xmm1
00502c6c mov dword ptr [ecx + 0x3ac], 0x14
00502c76 movss dword ptr [ecx + 0xdc], xmm0
00502c7e mov dword ptr [ecx + 0x3b0], 0x14
00502c88 call dword ptr [eax + 0xc]
00502c8b cmp byte ptr [edi + 0x16b], 0
00502c92 je 0x502dc9
00502c98 cmp dword ptr [edi + 0x28], 0x29
00502c9c jne 0x502dc9
00502ca2 cmp dword ptr [edi + 0x2c], 2
00502ca6 jne 0x502dc9
00502cac call 0x6c3d90
00502cb1 mov esi, eax
00502cb3 lea eax, [ebp - 0x6c]
00502cb6 push eax
00502cb7 call 0x659290
00502cbc mov ecx, dword ptr [0xbfd65c]
00502cc2 add esp, 4
00502cc5 movss xmm2, dword ptr [eax + 4]
00502cca movss xmm0, dword ptr [eax]
00502cce lea eax, [ebp - 0x1c]
00502cd1 mulss xmm0, dword ptr [0xb6a974]
00502cd9 push esi
00502cda mulss xmm2, dword ptr [0xb6a974]
00502ce2 push 0
00502ce4 addss xmm0, dword ptr [edi + 0x294]
00502cec push 0
00502cee addss xmm2, dword ptr [edi + 0x298]
00502cf6 push 0xc02fec
00502cfb push eax
00502cfc push 0
00502cfe push 0x348
00502d03 movss dword ptr [ebp - 0x1c], xmm0
00502d08 movss dword ptr [ebp - 0x18], xmm2
00502d0d call 0x422e20
00502d12 cmp byte ptr [edi + 0xbb3], 0
00502d19 mov esi, eax
00502d1b je 0x502d33
00502d1d push dword ptr [edi + 0xbb4]
00502d23 mov ecx, esi
00502d25 push dword ptr [esi + 0x30]
00502d28 push dword ptr [esi + 0x2c]
00502d2b push dword ptr [esi + 0x28]
00502d2e call 0x697c60
00502d33 mov ecx, dword ptr [esi + 0x314]
00502d39 lea eax, [esi + 0x314]
00502d3f test ecx, ecx
00502d41 je 0x502d5b
00502d43 mov dword ptr [ebp - 0x4c], eax
00502d46 add ecx, 0x324
00502d4c lea eax, [ebp - 0x4c]
00502d4f push eax
00502d50 call 0x4bc3c0
00502d55 lea eax, [esi + 0x314]
00502d5b push eax
00502d5c mov ecx, edi
00502d5e mov dword ptr [eax], edi
00502d60 call 0x4bae70
00502d65 mov ecx, dword ptr [edi + 0x318]
00502d6b lea eax, [edi + 0x318]
00502d71 test ecx, ecx
00502d73 je 0x502d8d
00502d75 mov dword ptr [ebp - 0x4c], eax
00502d78 add ecx, 0x324
00502d7e lea eax, [ebp - 0x4c]
00502d81 push eax
00502d82 call 0x4bc3c0
00502d87 lea eax, [edi + 0x318]
00502d8d push eax
00502d8e mov ecx, esi
00502d90 mov dword ptr [eax], esi
00502d92 call 0x4bae70
00502d97 mov eax, dword ptr [esi + 0x164]
00502d9d mov ecx, esi
00502d9f and dword ptr [esi + 0x160], 0xfffffffb
00502da6 mov dword ptr [esi + 0x164], eax
00502dac mov eax, dword ptr [esi]
00502dae call dword ptr [eax + 0xc]
00502db1 push 0
00502db3 push dword ptr [edi + 0x30]
00502db6 mov ecx, edi
00502db8 push 3
00502dba push dword ptr [edi + 0x28]
00502dbd call 0x697c60
00502dc2 mov byte ptr [edi + 0x16b], 0
00502dc9 mov ecx, dword ptr [ebp - 0xc]
00502dcc mov dword ptr fs:[0], ecx
00502dd3 pop ecx
00502dd4 pop edi
00502dd5 pop esi
00502dd6 mov ecx, dword ptr [ebp - 0x14]
00502dd9 xor ecx, ebp
00502ddb call 0x9eacd7
00502de0 mov esp, ebp
00502de2 pop ebp
00502de3 mov esp, ebx
00502de5 pop ebx
00502de6 ret 
00502de7 nop 
00502de8 mov esp, 0x5a005022
00502ded and dl, byte ptr [eax]
00502df0 sbb esp, dword ptr [ebx]
00502df2 push eax
00502df3 add ah, bh
00502df5 and dword ptr [eax], edx
