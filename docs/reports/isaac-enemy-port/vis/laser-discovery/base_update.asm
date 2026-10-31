00686060 mov eax, dword ptr [ecx + 0x294]
00686066 mov dword ptr [ecx + 0x2e4], eax
0068606c mov eax, dword ptr [ecx + 0x298]
00686072 mov dword ptr [ecx + 0x2e8], eax
00686078 mov eax, dword ptr [ecx + 0x2b8]
0068607e mov dword ptr [ecx + 0x2ec], eax
00686084 mov eax, dword ptr [ecx + 0x2bc]
0068608a mov dword ptr [ecx + 0x2f0], eax
00686090 ret 
00686091 int3 
00686092 int3 
00686093 int3 
00686094 int3 
00686095 int3 
00686096 int3 
00686097 int3 
00686098 int3 
00686099 int3 
0068609a int3 
0068609b int3 
0068609c int3 
0068609d int3 
0068609e int3 
0068609f int3 
006860a0 push ebp
006860a1 mov ebp, esp
006860a3 and esp, 0xfffffff0
006860a6 sub esp, 0x1d8
006860ac mov eax, dword ptr [0xbaa3b4]
006860b1 xor eax, esp
006860b3 mov dword ptr [esp + 0x1d4], eax
006860ba push esi
006860bb push edi
006860bc mov edi, ecx
006860be mov dword ptr [esp + 0x3c], edi
006860c2 mov edx, dword ptr [edi + 0x160]
006860c8 mov eax, edx
006860ca mov esi, dword ptr [edi + 0x164]
006860d0 and eax, 0x4000
006860d5 or eax, 0
006860d8 mov dword ptr [esp + 0x10], edx
006860dc je 0x6860e7
006860de mov dword ptr [esp + 0x10], edx
006860e2 jmp 0x68618c
006860e7 movss xmm1, dword ptr [edi + 0x2fc]
006860ef mov eax, edx
006860f1 movss xmm2, dword ptr [edi + 0x2f4]
006860f9 and eax, 0x20
006860fc or eax, 0
006860ff movss dword ptr [edi + 0x2f8], xmm1
00686107 movaps xmm0, xmm2
0068610a addss xmm0, xmm1
0068610e movss dword ptr [edi + 0x2fc], xmm0
00686116 jne 0x686120
00686118 cmp dword ptr [edi + 0x348], eax
0068611e jle 0x686129
00686120 cmp byte ptr [edi + 0x16b], 0
00686127 je 0x68618c
00686129 mov ecx, esi
0068612b mov dword ptr [esp + 0x10], edx
0068612f and ecx, 1
00686132 xor eax, eax
00686134 or eax, ecx
00686136 jne 0x68618c
00686138 movss xmm0, dword ptr [edi + 0x140]
00686140 movss dword ptr [esp + 0x1c], xmm0
00686146 mulss xmm0, xmm2
0068614a movss dword ptr [edi + 0x140], xmm0
00686152 cmp byte ptr [edi + 0x145], 0
00686159 je 0x68617e
0068615b lea ecx, [edi + 0x6c]
0068615e call 0x403d60
00686163 lea ecx, [edi + 0x8c]
00686169 call 0x403d60
0068616e mov eax, dword ptr [edi + 0x160]
00686174 mov esi, dword ptr [edi + 0x164]
0068617a mov dword ptr [esp + 0x10], eax
0068617e movss xmm0, dword ptr [esp + 0x1c]
00686184 movss dword ptr [edi + 0x140], xmm0
0068618c mov ecx, esi
0068618e xor eax, eax
00686190 and ecx, 0x8000
00686196 or eax, ecx
00686198 je 0x686406
0068619e mov al, byte ptr [edi + 0x188]
006861a4 mov byte ptr [esp + 0x1b], al
006861a8 test al, al
006861aa jne 0x686243
006861b0 movss xmm1, dword ptr [edi + 0x2b8]
006861b8 movss xmm2, dword ptr [edi + 0x2bc]
006861c0 movaps xmm0, xmm1
006861c3 mulss xmm0, xmm1
006861c7 movss dword ptr [esp + 0x24], xmm1
006861cd movaps xmm1, xmm2
006861d0 mulss xmm1, xmm2
006861d4 movss dword ptr [esp + 0x38], xmm2
006861da addss xmm0, xmm1
006861de call 0x4228c0
006861e3 movss xmm1, dword ptr [edi + 0x264]
006861eb movss xmm2, dword ptr [edi + 0x260]
006861f3 movss dword ptr [esp + 0x1c], xmm0
006861f9 movaps xmm0, xmm1
006861fc mulss xmm0, xmm1
00686200 movaps xmm1, xmm2
00686203 mulss xmm1, xmm2
00686207 addss xmm0, xmm1
0068620b call 0x4228c0
00686210 movss xmm1, dword ptr [esp + 0x1c]
00686216 comiss xmm1, xmm0
00686219 jb 0x686243
0068621b movss xmm1, dword ptr [edi + 0x264]
00686223 movss xmm0, dword ptr [edi + 0x260]
0068622b mulss xmm1, dword ptr [esp + 0x38]
00686231 mulss xmm0, dword ptr [esp + 0x24]
00686237 addss xmm0, xmm1
0068623b xorps xmm1, xmm1
0068623e comiss xmm1, xmm0
00686241 ja 0x68627a
00686243 movss xmm2, dword ptr [edi + 0x260]
0068624b movss xmm1, dword ptr [edi + 0x264]
00686253 movaps xmm0, xmm2
00686256 mulss xmm0, xmm2
0068625a mulss xmm1, xmm1
0068625e movss dword ptr [esp + 0x1c], xmm2
00686264 addss xmm0, xmm1
00686268 call 0x4228c0
0068626d movss xmm1, dword ptr [0xb6a7b0]
00686275 comiss xmm1, xmm0
00686278 jbe 0x68629f
0068627a mov eax, dword ptr [esp + 0x10]
0068627e and esi, 0xfffe7fff
00686284 mov dword ptr [edi + 0x160], eax
0068628a mov dword ptr [edi + 0x164], esi
00686290 mov dword ptr [edi + 0x250], 0
0068629a jmp 0x686406
0068629f movss xmm0, dword ptr [edi + 0x2c0]
006862a7 mov ecx, esi
006862a9 movss xmm2, dword ptr [0xb6a5d8]
006862b1 and ecx, 0x20000
006862b7 mulss xmm0, xmm2
006862bb xor eax, eax
006862bd or eax, ecx
006862bf movss dword ptr [edi + 0x2c4], xmm0
006862c7 movss xmm1, dword ptr [edi + 0x264]
006862cf je 0x6862db
006862d1 mov eax, dword ptr [esp + 0x10]
006862d5 mov cl, byte ptr [esp + 0x1b]
006862d9 jmp 0x68630b
006862db movss xmm0, dword ptr [esp + 0x1c]
006862e1 mulss xmm0, xmm2
006862e5 mulss xmm1, xmm2
006862e9 movss dword ptr [edi + 0x260], xmm0
006862f1 movss dword ptr [edi + 0x264], xmm1
006862f9 mov cl, byte ptr [edi + 0x188]
006862ff mov eax, dword ptr [edi + 0x160]
00686305 mov esi, dword ptr [edi + 0x164]
0068630b mov dword ptr [esp + 0x50], eax
0068630f test cl, cl
00686311 je 0x6863ee
00686317 and esi, 0x10000
0068631d xor eax, eax
0068631f or eax, esi
00686321 je 0x6863dd
00686327 movss xmm0, dword ptr [edi + 0x260]
0068632f mulss xmm0, xmm0
00686333 mulss xmm1, xmm1
00686337 addss xmm0, xmm1
0068633b call 0x4228c0
00686340 lea eax, [esp + 0x50]
00686344 movss dword ptr [esp + 0x1c], xmm0
0068634a push eax
0068634b lea ecx, [edi + 0x2b8]
00686351 call 0x962560
00686356 movss xmm0, dword ptr [esp + 0x1c]
0068635c mov ecx, dword ptr [0xbfd65c]
00686362 movaps xmm1, xmm0
00686365 mulss xmm1, dword ptr [eax]
00686369 mulss xmm0, dword ptr [eax + 4]
0068636e mulss xmm1, dword ptr [0xb6a560]
00686376 mulss xmm0, dword ptr [0xb6a560]
0068637e movss dword ptr [edi + 0x260], xmm1
00686386 movss dword ptr [edi + 0x264], xmm0
0068638e call 0x427780
00686393 mov edx, dword ptr [edi]
00686395 lea ecx, [esp + 0x88]
0068639c dec eax
0068639d push 0x1e
0068639f movd xmm1, eax
006863a3 cvtdq2ps xmm1, xmm1
006863a6 addss xmm1, xmm1
006863aa addss xmm1, dword ptr [0xb6a974]
006863b2 call 0x427290
006863b7 push eax
006863b8 push 0
006863ba push 0
006863bc push ecx
006863bd mov ecx, edi
006863bf movss dword ptr [esp], xmm1
006863c4 call dword ptr [edx + 0x20]
006863c7 mov eax, dword ptr [edi + 0x160]
006863cd and dword ptr [edi + 0x164], 0xfffeffff
006863d7 mov dword ptr [edi + 0x160], eax
006863dd mov eax, dword ptr [edi + 0x250]
006863e3 cdq 
006863e4 sub eax, edx
006863e6 sar eax, 1
006863e8 mov dword ptr [edi + 0x250], eax
006863ee mov eax, dword ptr [edi + 0x260]
006863f4 mov dword ptr [edi + 0x2b8], eax
006863fa mov eax, dword ptr [edi + 0x264]
00686400 mov dword ptr [edi + 0x2bc], eax
00686406 movss xmm2, dword ptr [edi + 0x2f4]
0068640e movss xmm4, dword ptr [0xb6a614]
00686416 movss xmm3, dword ptr [edi + 0x2c4]
0068641e ucomiss xmm2, xmm4
00686421 lahf 
00686422 test ah, 0x44
00686425 jnp 0x68643d
00686427 movaps xmm1, xmm3
0068642a movaps xmm0, xmm3
0068642d addss xmm1, xmm2
00686431 mulss xmm0, xmm2
00686435 subss xmm1, xmm0
00686439 divss xmm3, xmm1
0068643d mov eax, dword ptr [edi + 0x2c0]
00686443 lea edx, [edi + 0x294]
00686449 movaps xmm1, xmm3
0068644c mulss xmm3, dword ptr [edi + 0x2bc]
00686454 mulss xmm1, dword ptr [edi + 0x2b8]
0068645c movss dword ptr [edi + 0x2bc], xmm3
00686464 movss dword ptr [edi + 0x2b8], xmm1
0068646c movss xmm2, dword ptr [edi + 0x2f4]
00686474 movaps xmm0, xmm2
00686477 mov dword ptr [edi + 0x2c4], eax
0068647d mulss xmm0, xmm1
00686481 mulss xmm2, xmm3
00686485 addss xmm0, dword ptr [edx]
00686489 addss xmm2, dword ptr [edx + 4]
0068648e movss dword ptr [edx], xmm0
00686492 movss dword ptr [edx + 4], xmm2
00686497 mov ecx, dword ptr [edi + 0x160]
0068649d mov eax, ecx
0068649f mov esi, dword ptr [edi + 0x164]
006864a5 and eax, 0x4000
006864aa or eax, 0
006864ad jne 0x686d94
006864b3 mov esi, dword ptr [edi + 0x1a4]
006864b9 xor dl, dl
006864bb cmp esi, dword ptr [edi + 0x1a8]
006864c1 je 0x6865d2
006864c7 mov eax, dword ptr [esi + 0x34]
006864ca mov ecx, 1
006864cf dec eax
006864d0 movzx edx, dl
006864d3 mov dword ptr [esi + 0x34], eax
006864d6 cmp byte ptr [esi + 0x38], 0
006864da cmovne edx, ecx
006864dd lea ecx, [esi + 0x3c]
006864e0 test eax, eax
006864e2 jne 0x6864fe
006864e4 mov edx, dword ptr [edi + 0x1a8]
006864ea push esi
006864eb call 0x4a3db0
006864f0 add esp, 4
006864f3 mov dl, 1
006864f5 add dword ptr [edi + 0x1a8], -0x3c
006864fc jmp 0x686500
006864fe mov esi, ecx
00686500 mov ecx, dword ptr [edi + 0x1a8]
00686506 cmp esi, ecx
00686508 jne 0x6864c7
0068650a test dl, dl
0068650c je 0x6865d2
00686512 mov esi, dword ptr [edi + 0x1a4]
00686518 mov eax, 0x88888889
0068651d sub ecx, esi
0068651f imul ecx
00686521 add edx, ecx
00686523 sar edx, 5
00686526 mov eax, edx
00686528 shr eax, 0x1f
0068652b add eax, edx
0068652d je 0x6865cb
00686533 lea ecx, [esi + 4]
00686536 lea edx, [esi + 0x40]
00686539 cmp eax, 1
0068653c ja 0x686544
0068653e lea edx, [edi + 0x1b0]
00686544 cmp byte ptr [esi + 0x38], 0
00686548 movups xmm0, xmmword ptr [ecx]
0068654b mov eax, dword ptr [ecx + 0x28]
0068654e mov dword ptr [esp + 0x154], eax
00686555 movups xmmword ptr [esp + 0x12c], xmm0
0068655d movups xmm0, xmmword ptr [ecx + 0x10]
00686561 movups xmmword ptr [esp + 0x13c], xmm0
00686569 movq xmm0, qword ptr [ecx + 0x20]
0068656e movq qword ptr [esp + 0x14c], xmm0
00686577 je 0x6865b9
00686579 movd xmm1, dword ptr [esi + 0x34]
0068657e lea eax, [esp + 0x158]
00686585 movd xmm0, dword ptr [esi + 0x30]
0068658a cvtdq2ps xmm0, xmm0
0068658d push ecx
0068658e cvtdq2ps xmm1, xmm1
00686591 divss xmm1, xmm0
00686595 movaps xmm0, xmm4
00686598 subss xmm0, xmm1
0068659c movss dword ptr [esp], xmm0
006865a1 push edx
006865a2 push ecx
006865a3 push eax
006865a4 call 0x65b210
006865a9 add esp, 0x10
006865ac lea ecx, [esp + 0x12c]
006865b3 push eax
006865b4 call 0x4021a0
006865b9 lea eax, [esp + 0x12c]
006865c0 push eax
006865c1 lea ecx, [edi + 0x3c]
006865c4 call 0x402370
006865c9 jmp 0x6865d2
006865cb mov eax, dword ptr [edi]
006865cd mov ecx, edi
006865cf call dword ptr [eax + 0x5c]
006865d2 mov esi, dword ptr [edi + 0x160]
006865d8 mov eax, esi
006865da mov ecx, dword ptr [edi + 0x164]
006865e0 and eax, 1
006865e3 or eax, 0
006865e6 mov dword ptr [esp + 0x10], ecx
006865ea jne 0x686735
006865f0 mov eax, dword ptr [edi + 0x28]
006865f3 cmp eax, 0xa
006865f6 jl 0x686735
006865fc cmp eax, 0x3e8
00686601 jge 0x686735
00686607 mov ecx, dword ptr [0xbfd65c]
0068660d push 0x11
0068660f call 0x641630
00686614 test al, al
00686616 jne 0x686635
00686618 mov eax, dword ptr [esp + 0x10]
0068661c mov ecx, dword ptr [0xbfd65c]
00686622 push 0x15
00686624 mov dword ptr [esp + 0x24], esi
00686628 mov dword ptr [esp + 0x18], eax
0068662c call 0x641630
00686631 test al, al
00686633 je 0x68665f
00686635 mov eax, dword ptr [esp + 0x10]
00686639 or esi, 0x100
0068663f mov dword ptr [edi + 0x21c], 2
00686649 mov dword ptr [edi + 0x160], esi
0068664f mov dword ptr [edi + 0x164], eax
00686655 mov dword ptr [esp + 0x20], esi
00686659 mov dword ptr [esp + 0x14], eax
0068665d jmp 0x686663
0068665f mov eax, dword ptr [esp + 0x10]
00686663 mov ecx, dword ptr [0xbfd65c]
00686669 push 0x12
0068666b mov dword ptr [esp + 0x14], eax
0068666f call 0x641630
00686674 test al, al
00686676 je 0x6866a8
00686678 mov esi, dword ptr [esp + 0x20]
0068667c mov eax, dword ptr [esp + 0x14]
00686680 or esi, 0x200
00686686 mov dword ptr [edi + 0x220], 2
00686690 mov dword ptr [esp + 0x10], eax
00686694 mov dword ptr [edi + 0x160], esi
0068669a mov dword ptr [edi + 0x164], eax
006866a0 mov dword ptr [esp + 0x20], esi
006866a4 mov dword ptr [esp + 0x14], eax
006866a8 mov ecx, dword ptr [0xbfd65c]
006866ae push 0x13
006866b0 call 0x641630
006866b5 test al, al
006866b7 jne 0x68670b
006866b9 mov ecx, dword ptr [0xbfd65c]
006866bf push 0x15
006866c1 call 0x641630
006866c6 test al, al
006866c8 jne 0x68670b
006866ca mov ecx, dword ptr [0xbfd65c]
006866d0 push 0x14
006866d2 call 0x641630
006866d7 test al, al
006866d9 je 0x686731
006866db mov eax, dword ptr [esp + 0x10]
006866df mov dword ptr [esp + 0x10], eax
006866e3 mov eax, dword ptr [0xbfd65c]
006866e8 mov ecx, dword ptr [eax + 0x1a30dc]
006866ee mov eax, 0x88888889
006866f3 sub ecx, dword ptr [edi + 0x280]
006866f9 imul ecx
006866fb add edx, ecx
006866fd sar edx, 5
00686700 mov eax, edx
00686702 shr eax, 0x1f
00686705 add eax, edx
00686707 test al, 1
00686709 jne 0x686731
0068670b mov esi, dword ptr [esp + 0x20]
0068670f mov ecx, dword ptr [esp + 0x14]
00686713 or esi, 0x800
00686719 mov dword ptr [edi + 0x228], 2
00686723 mov dword ptr [edi + 0x160], esi
00686729 mov dword ptr [edi + 0x164], ecx
0068672f jmp 0x686735
00686731 mov ecx, dword ptr [esp + 0x10]
00686735 mov eax, dword ptr [edi + 0x208]
0068673b test eax, eax
0068673d jle 0x686746
0068673f dec eax
00686740 mov dword ptr [edi + 0x208], eax
00686746 mov eax, dword ptr [edi + 0x20c]
0068674c test eax, eax
0068674e jle 0x686757
00686750 dec eax
00686751 mov dword ptr [edi + 0x20c], eax
00686757 mov eax, dword ptr [edi + 0x210]
0068675d mov edx, esi
0068675f mov dword ptr [esp + 0x14], ecx
00686763 test eax, eax
00686765 jle 0x686789
00686767 dec eax
00686768 mov dword ptr [esp + 0x14], ecx
0068676c mov dword ptr [edi + 0x210], eax
00686772 test eax, eax
00686774 jg 0x686789
00686776 and edx, 0xffffffdf
00686779 mov esi, ecx
0068677b mov dword ptr [edi + 0x160], edx
00686781 mov dword ptr [edi + 0x164], esi
00686787 jmp 0x68678d
00686789 mov esi, dword ptr [esp + 0x14]
0068678d mov eax, dword ptr [edi + 0x214]
00686793 mov ecx, edx
00686795 mov dword ptr [esp + 0x14], esi
00686799 test eax, eax
0068679b jle 0x6867c7
0068679d dec eax
0068679e mov dword ptr [esp + 0x14], esi
006867a2 mov dword ptr [edi + 0x214], eax
006867a8 test eax, eax
006867aa jg 0x6867c7
006867ac and ecx, 0xffffffbf
006867af mov dword ptr [edi + 0x164], esi
006867b5 mov dword ptr [edi + 0x160], ecx
006867bb mov dword ptr [edi + 0x278], 0x40000000
006867c5 jmp 0x6867cb
006867c7 mov esi, dword ptr [esp + 0x14]
006867cb cmp dword ptr [edi + 0x218], 0
006867d2 mov eax, esi
006867d4 mov edx, ecx
006867d6 mov dword ptr [esp + 0x10], eax
006867da jle 0x68680f
006867dc mov eax, dword ptr [edi + 0x218]
006867e2 dec eax
006867e3 mov dword ptr [esp + 0x10], esi
006867e7 mov dword ptr [edi + 0x218], eax
006867ed test eax, eax
006867ef jg 0x68680b
006867f1 mov eax, esi
006867f3 and edx, 0xffffff7f
006867f9 mov dword ptr [esp + 0x10], eax
006867fd mov dword ptr [edi + 0x160], edx
00686803 mov dword ptr [edi + 0x164], eax
00686809 jmp 0x68680f
0068680b mov eax, dword ptr [esp + 0x10]
0068680f mov dword ptr [esp + 0x14], eax
00686813 mov ecx, edx
00686815 mov eax, dword ptr [edi + 0x21c]
0068681b test eax, eax
0068681d jle 0x68687e
0068681f mov esi, dword ptr [esp + 0x10]
00686823 dec eax
00686824 mov dword ptr [edi + 0x21c], eax
0068682a mov dword ptr [esp + 0x14], esi
0068682e test eax, eax
00686830 jg 0x68687e
00686832 mov eax, dword ptr [edi + 0x31c]
00686838 mov edx, esi
0068683a lea esi, [edi + 0x31c]
00686840 mov dword ptr [edi + 0x164], edx
00686846 and ecx, 0xfffffeff
0068684c mov dword ptr [edi + 0x160], ecx
00686852 test eax, eax
00686854 je 0x686882
00686856 lea ecx, [esp + 0x1c]
0068685a mov dword ptr [esp + 0x1c], esi
0068685e push ecx
0068685f lea ecx, [eax + 0x324]
00686865 call 0x4bc3c0
0068686a mov ecx, dword ptr [edi + 0x160]
00686870 mov edx, dword ptr [edi + 0x164]
00686876 mov dword ptr [esi], 0
0068687c jmp 0x686882
0068687e mov edx, dword ptr [esp + 0x14]
00686882 cmp dword ptr [edi + 0x220], 0
00686889 mov eax, edx
0068688b mov esi, ecx
0068688d mov dword ptr [esp + 0x10], eax
00686891 jle 0x6868c6
00686893 mov eax, dword ptr [edi + 0x220]
00686899 dec eax
0068689a mov dword ptr [esp + 0x10], edx
0068689e mov dword ptr [edi + 0x220], eax
006868a4 test eax, eax
006868a6 jg 0x6868c2
006868a8 mov eax, edx
006868aa and esi, 0xfffffdff
006868b0 mov dword ptr [esp + 0x10], eax
006868b4 mov dword ptr [edi + 0x160], esi
006868ba mov dword ptr [edi + 0x164], eax
006868c0 jmp 0x6868c6
006868c2 mov eax, dword ptr [esp + 0x10]
006868c6 mov edx, eax
006868c8 mov ecx, esi
006868ca mov eax, dword ptr [edi + 0x228]
006868d0 test eax, eax
006868d2 jle 0x6868f5
006868d4 mov edx, dword ptr [esp + 0x10]
006868d8 dec eax
006868d9 mov dword ptr [edi + 0x228], eax
006868df test eax, eax
006868e1 jg 0x6868f5
006868e3 and ecx, 0xfffff7ff
006868e9 mov dword ptr [edi + 0x164], edx
006868ef mov dword ptr [edi + 0x160], ecx
006868f5 movss xmm1, dword ptr [edi + 0x30c]
006868fd movss xmm0, dword ptr [edi + 0x310]
00686905 mov eax, dword ptr [edi + 0x234]
0068690b subss xmm0, xmm1
0068690f mulss xmm0, dword ptr [0xb6a8f4]
00686917 mulss xmm0, dword ptr [0xb6a25c]
0068691f addss xmm0, xmm1
00686923 movss dword ptr [edi + 0x30c], xmm0
0068692b test eax, eax
0068692d jle 0x68694d
0068692f dec eax
00686930 mov dword ptr [edi + 0x234], eax
00686936 test eax, eax
00686938 jg 0x68694d
0068693a mov ecx, edi
0068693c call 0x68d260
00686941 mov ecx, dword ptr [edi + 0x160]
00686947 mov edx, dword ptr [edi + 0x164]
