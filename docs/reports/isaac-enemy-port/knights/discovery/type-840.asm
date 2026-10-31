00514450 push ebx
00514451 mov ebx, esp
00514453 sub esp, 8
00514456 and esp, 0xfffffff8
00514459 add esp, 4
0051445c push ebp
0051445d mov ebp, dword ptr [ebx + 4]
00514460 mov dword ptr [esp + 4], ebp
00514464 mov ebp, esp
00514466 push -1
00514468 push 0x9ef640
0051446d mov eax, dword ptr fs:[0]
00514473 push eax
00514474 push ebx
00514475 sub esp, 0x320
0051447b mov eax, dword ptr [0xbaa3b4]
00514480 xor eax, ebp
00514482 mov dword ptr [ebp - 0x14], eax
00514485 push esi
00514486 push edi
00514487 push eax
00514488 lea eax, [ebp - 0xc]
0051448b mov dword ptr fs:[0], eax
00514491 mov edi, ecx
00514493 mov dword ptr [ebp - 0x29c], edi
00514499 mov edx, dword ptr [edi + 0xab4]
0051449f test edx, edx
005144a1 jne 0x5145cb
005144a7 mov eax, dword ptr [edi + 0x28]
005144aa mov dword ptr [edi + 0xab4], 3
005144b4 cmp eax, 0x56
005144b7 je 0x5144c8
005144b9 cmp eax, 0x1d
005144bc jne 0x514526
005144be cmp dword ptr [edi + 0x2c], 2
005144c2 jne 0x516dbc
005144c8 movaps xmm0, xmmword ptr [0xb6c070]
005144cf lea eax, [ebp - 0x2d8]
005144d5 add edi, 0x1dc
005144db mov dword ptr [ebp - 0x2b8], 0
005144e5 mov dword ptr [ebp - 0x2b4], 0
005144ef xorps xmm1, xmm1
005144f2 mov dword ptr [ebp - 0x2b0], 0
005144fc cmp edi, eax
005144fe je 0x516dbc
00514504 mov eax, dword ptr [ebp - 0x2b0]
0051450a movups xmmword ptr [edi], xmm0
0051450d movq xmm0, qword ptr [ebp - 0x2b8]
00514515 movq qword ptr [edi + 0x20], xmm0
0051451a movups xmmword ptr [edi + 0x10], xmm1
0051451e mov dword ptr [edi + 0x28], eax
00514521 jmp 0x516dbc
00514526 cmp eax, 0x36
00514529 jne 0x514566
0051452b movaps xmm0, xmmword ptr [0xb6bd30]
00514532 lea eax, [ebp - 0x40]
00514535 movups xmmword ptr [ebp - 0x40], xmm0
00514539 mov dword ptr [ebp - 0x20], 0x3e109091
00514540 lea ecx, [edi + 0x1dc]
00514546 xorps xmm0, xmm0
00514549 mov dword ptr [ebp - 0x1c], 0x3df8f8f9
00514550 push eax
00514551 movups xmmword ptr [ebp - 0x30], xmm0
00514555 mov dword ptr [ebp - 0x18], 0x3de0e0e1
0051455c call 0x4021a0
00514561 jmp 0x516dbc
00514566 cmp eax, 0xf6
0051456b jne 0x51458c
0051456d cmp dword ptr [edi + 0x2c], 1
00514571 jne 0x516dbc
00514577 push 0xbc5178
0051457c lea ecx, [edi + 0x1dc]
00514582 call 0x4021a0
00514587 jmp 0x516dbc
0051458c cmp eax, 0x22
0051458f jne 0x516dbc
00514595 cmp dword ptr [edi + 0x2c], 1
00514599 jne 0x516dbc
0051459f movss xmm3, dword ptr [0xb6a274]
005145a7 lea ecx, [ebp - 0x40]
005145aa movss xmm1, dword ptr [0xb6a234]
005145b2 movaps xmm2, xmm3
005145b5 call 0x427080
005145ba push eax
005145bb lea ecx, [edi + 0x1dc]
005145c1 call 0x4021a0
005145c6 jmp 0x516dbc
005145cb mov ecx, dword ptr [edi + 0x164]
005145d1 xor eax, eax
005145d3 and ecx, 0x8000
005145d9 or eax, ecx
005145db je 0x514649
005145dd cmp dword ptr [edi + 0x250], 1
005145e4 jne 0x514649
005145e6 movss xmm0, dword ptr [edi + 0x28c]
005145ee ucomiss xmm0, dword ptr [0xc02fec]
005145f5 lahf 
005145f6 test ah, 0x44
005145f9 jp 0x514610
005145fb movss xmm0, dword ptr [edi + 0x290]
00514603 ucomiss xmm0, dword ptr [0xc02ff0]
0051460a lahf 
0051460b test ah, 0x44
0051460e jnp 0x514649
00514610 cmp edx, 4
00514613 jne 0x514649
00514615 mov dword ptr [edi + 0xab4], 3
0051461f mov dword ptr [edi + 0x360], 0
00514629 movss xmm0, dword ptr [0xc02fec]
00514631 movss dword ptr [edi + 0x28c], xmm0
00514639 movss xmm0, dword ptr [0xc02ff0]
00514641 movss dword ptr [edi + 0x290], xmm0
00514649 mov esi, dword ptr [edi + 8]
0051464c mov edx, dword ptr [edi + 0xc]
0051464f mov dword ptr [ebp - 0x260], esi
00514655 cmp esi, edx
00514657 je 0x5147dd
0051465d lea ecx, [esi + 0x38]
00514660 mov dword ptr [ebp - 0x244], ecx
00514666 mov eax, dword ptr [ecx - 0x30]
00514669 and eax, 2
0051466c or eax, 0
0051466f je 0x5147c3
00514675 mov eax, dword ptr [edi + 0x28]
00514678 cmp eax, 0x1d
0051467b jne 0x514727
00514681 cmp dword ptr [edi + 0x2c], 0
00514685 jne 0x5147c3
0051468b movss xmm0, dword ptr [edi + 0x2d8]
00514693 mov ecx, edi
00514695 divss xmm0, dword ptr [edi + 0x2dc]
0051469d push -1
0051469f push 0
005146a1 push 0
005146a3 push 0x36
005146a5 movss dword ptr [ebp - 0x23c], xmm0
005146ad call 0x697c60
005146b2 movaps xmm0, xmmword ptr [0xb6bd30]
005146b9 lea ecx, [edi + 0x1dc]
005146bf lea eax, [ebp - 0x304]
005146c5 mov dword ptr [ebp - 0x2e4], 0x3e109091
005146cf mov dword ptr [ebp - 0x2e0], 0x3df8f8f9
005146d9 xorps xmm1, xmm1
005146dc mov dword ptr [ebp - 0x2dc], 0x3de0e0e1
005146e6 cmp ecx, eax
005146e8 je 0x514707
005146ea mov eax, dword ptr [ebp - 0x2dc]
005146f0 movups xmmword ptr [ecx], xmm0
005146f3 movq xmm0, qword ptr [ebp - 0x2e4]
005146fb movq qword ptr [ecx + 0x20], xmm0
00514700 movups xmmword ptr [ecx + 0x10], xmm1
00514704 mov dword ptr [ecx + 0x28], eax
00514707 movss xmm0, dword ptr [ebp - 0x23c]
0051470f mulss xmm0, dword ptr [edi + 0x2dc]
00514717 mov ecx, dword ptr [ebp - 0x244]
0051471d movss dword ptr [edi + 0x2d8], xmm0
00514725 jmp 0x514730
00514727 cmp eax, 0x36
0051472a jne 0x5147c3
00514730 mov eax, dword ptr [edi + 0xc]
00514733 mov dword ptr [ebp - 0x254], eax
00514739 mov dword ptr [ebp - 0x23c], ecx
0051473f cmp ecx, eax
00514741 je 0x5147bb
00514743 lea edx, [ecx - 0xc]
00514746 mov edi, ecx
00514748 mov esi, eax
0051474a nop word ptr [eax + eax]
00514750 mov eax, dword ptr [edi]
00514752 lea edx, [edx + 0x38]
00514755 mov dword ptr [edx - 0x64], eax
00514758 add edi, 0x38
0051475b mov eax, dword ptr [edx - 0x24]
0051475e mov ecx, dword ptr [edx - 0x20]
00514761 mov dword ptr [edx - 0x5c], eax
00514764 mov dword ptr [edx - 0x58], ecx
00514767 mov eax, dword ptr [edx - 0x1c]
0051476a mov dword ptr [edx - 0x54], eax
0051476d mov eax, dword ptr [edx - 0x18]
00514770 mov dword ptr [edx - 0x50], eax
00514773 mov eax, dword ptr [edx - 0x14]
00514776 mov dword ptr [edx - 0x4c], eax
00514779 mov eax, dword ptr [edx - 0x10]
0051477c mov dword ptr [edx - 0x48], eax
0051477f mov eax, dword ptr [edx - 0xc]
00514782 mov dword ptr [edx - 0x44], eax
00514785 mov eax, dword ptr [edx - 8]
00514788 mov dword ptr [edx - 0x40], eax
0051478b mov eax, dword ptr [edx - 4]
0051478e mov dword ptr [edx - 0x3c], eax
00514791 mov eax, dword ptr [edx]
00514793 mov dword ptr [edx - 0x38], eax
00514796 mov eax, dword ptr [edx + 4]
00514799 mov dword ptr [edx - 0x34], eax
0051479c mov eax, dword ptr [edx + 8]
0051479f mov dword ptr [edx - 0x30], eax
005147a2 cmp edi, esi
005147a4 jne 0x514750
005147a6 mov edi, dword ptr [ebp - 0x29c]
005147ac mov esi, dword ptr [ebp - 0x260]
005147b2 mov ecx, dword ptr [ebp - 0x244]
005147b8 mov eax, dword ptr [edi + 0xc]
005147bb lea edx, [eax - 0x38]
005147be mov dword ptr [edi + 0xc], edx
005147c1 jmp 0x5147d5
005147c3 add esi, 0x38
005147c6 add ecx, 0x38
005147c9 mov dword ptr [ebp - 0x260], esi
005147cf mov dword ptr [ebp - 0x244], ecx
005147d5 cmp esi, edx
005147d7 jne 0x514666
005147dd mov eax, dword ptr [edi + 0x28]
005147e0 mov ecx, 0xb3fd8c
005147e5 mov dword ptr [ebp - 0x244], ecx
005147eb mov esi, 0xa081d4
005147f0 mov dword ptr [ebp - 0x260], 0xb405cc
005147fa mov edx, ecx
005147fc cmp eax, 0x56
005147ff jne 0x514817
00514801 mov ecx, 0xb406f0
00514806 mov dword ptr [ebp - 0x260], 0xb40884
00514810 mov esi, 0xb42e90
00514815 jmp 0x514862
00514817 cmp eax, 0x131
0051481c jne 0x514825
0051481e mov esi, 0xb40510
00514823 jmp 0x514868
00514825 cmp eax, 0x1d
00514828 jne 0x514868
0051482a cmp dword ptr [edi + 0x2c], 3
0051482e jne 0x514868
00514830 mov eax, dword ptr [edi + 0xb10]
00514836 mov ecx, 0xb40218
0051483b and eax, 1
0051483e mov dword ptr [ebp - 0x23c], 0xb405cc
00514848 cmove ecx, edx
0051484b test eax, 1
00514850 mov edx, 0xb430f0
00514855 cmove edx, dword ptr [ebp - 0x23c]
0051485c mov dword ptr [ebp - 0x260], edx
00514862 mov dword ptr [ebp - 0x244], ecx
00514868 cmp dword ptr [edi + 0x70], 0
0051486c je 0x514877
0051486e cmp byte ptr [edi + 0x80], 0
00514875 jne 0x5148ad
00514877 mov eax, dword ptr [edi + 0xab4]
0051487d cmp eax, 5
00514880 je 0x5148ad
00514882 sub eax, 3
00514885 je 0x5148a2
00514887 sub eax, 3
0051488a je 0x514899
0051488c sub eax, 1
0051488f jne 0x5148ad
00514891 push eax
00514892 push 0xb430e4
00514897 jmp 0x5148a5
00514899 push 0
0051489b push 0xb405f4
005148a0 jmp 0x5148a5
005148a2 push 0
005148a4 push ecx
005148a5 lea ecx, [edi + 0x3c]
005148a8 call 0x4054f0
005148ad mov eax, dword ptr [edi + 0x28]
005148b0 xorps xmm2, xmm2
005148b3 movss xmm3, dword ptr [0xb6a19c]
005148bb xorps xmm1, xmm1
005148be movss dword ptr [ebp - 0x264], xmm2
005148c6 movss dword ptr [ebp - 0x250], xmm1
005148ce mov dword ptr [ebp - 0x26c], 0
005148d8 cmp eax, 0x1d
005148db jne 0x514911
005148dd mov eax, dword ptr [edi + 0x2c]
005148e0 cmp eax, 1
005148e3 je 0x51491c
005148e5 cmp eax, 2
005148e8 jne 0x5148f9
005148ea mov dword ptr [ebp - 0x26c], 8
005148f4 jmp 0x5149ed
005148f9 cmp eax, 3
005148fc jne 0x5149ed
00514902 mov dword ptr [ebp - 0x26c], 0x1a
0051490c jmp 0x5149ed
00514911 cmp eax, 0xf6
00514916 jne 0x5149a0
0051491c cmp dword ptr [edi + 0xe6c], -1
00514923 je 0x51493c
00514925 movss xmm1, dword ptr [0xb6ab20]
0051492d mov dword ptr [ebp - 0x26c], 0xf
00514937 jmp 0x5149e5
0051493c call 0x6c3d90
00514941 xorps xmm0, xmm0
00514944 cvtsi2sd xmm0, eax
00514948 shr eax, 0x1f
0051494b addsd xmm0, qword ptr [eax*8 + 0xb6c940]
00514954 cvtpd2ps xmm1, xmm0
00514958 mulss xmm1, xmm3
0051495c call 0x6c3d90
00514961 mulss xmm1, dword ptr [0xb6aa60]
00514969 xorps xmm0, xmm0
0051496c mov dword ptr [ebp - 0x26c], 0xf
00514976 cvtsi2sd xmm0, eax
0051497a shr eax, 0x1f
0051497d addss xmm1, xmm2
00514981 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
0051498a cvtpd2ps xmm0, xmm0
0051498e mulss xmm0, xmm3
00514992 mulss xmm0, dword ptr [0xb6aab4]
0051499a addss xmm1, xmm0
0051499e jmp 0x5149e5
005149a0 cmp eax, 0x36
005149a3 jne 0x5149ed
005149a5 cmp dword ptr [edi + 0xe6c], -1
005149ac je 0x5149b8
005149ae movss xmm1, dword ptr [0xb6aa60]
005149b6 jmp 0x5149e5
005149b8 call 0x6c3d90
005149bd movd xmm0, eax
005149c1 cvtdq2pd xmm0, xmm0
005149c5 shr eax, 0x1f
005149c8 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
005149d1 cvtpd2ps xmm1, xmm0
005149d5 mulss xmm1, xmm3
005149d9 mulss xmm1, dword ptr [0xb6aa60]
005149e1 addss xmm1, xmm2
005149e5 movss dword ptr [ebp - 0x250], xmm1
005149ed mov eax, dword ptr [edi + 0x28]
005149f0 movaps xmm0, xmm1
005149f3 mulss xmm0, dword ptr [0xb6a690]
005149fb movss xmm1, dword ptr [0xb6a50c]
00514a03 addss xmm0, dword ptr [0xb6ab34]
00514a0b movss dword ptr [ebp - 0x28c], xmm0
00514a13 cmp eax, 0xf6
00514a18 jne 0x514a20
00514a1a cmp dword ptr [edi + 0x2c], 1
00514a1e jmp 0x514a29
00514a20 cmp eax, 0x1d
00514a23 jne 0x514a37
00514a25 cmp dword ptr [edi + 0x2c], 2
00514a29 jne 0x514a37
00514a2b mulss xmm0, xmm1
00514a2f movss dword ptr [ebp - 0x28c], xmm0
00514a37 cmp dword ptr [edi + 0xe6c], -1
00514a3e movss xmm1, dword ptr [0xb6a2cc]
00514a46 je 0x514b3f
00514a4c lea eax, [ebp - 0x298]
00514a52 movaps xmm2, xmm1
00514a55 push eax
00514a56 mov ecx, edi
00514a58 call 0x6af0c0
00514a5d mov ecx, eax
00514a5f movss xmm0, dword ptr [ecx]
00514a63 ucomiss xmm0, dword ptr [0xc02fec]
00514a6a lahf 
00514a6b test ah, 0x44
00514a6e jp 0x514a8c
00514a70 movss xmm0, dword ptr [ecx + 4]
00514a75 ucomiss xmm0, dword ptr [0xc02ff0]
00514a7c lahf 
00514a7d test ah, 0x44
00514a80 jp 0x514a8c
00514a82 movss xmm0, dword ptr [ebp - 0x264]
00514a8a jmp 0x514ac8
00514a8c movss xmm0, dword ptr [edi + 0xb08]
00514a94 lea eax, [ebp - 0x23c]
00514a9a addss xmm0, dword ptr [0xb6a614]
00514aa2 lea ecx, [ebp - 0x254]
00514aa8 mov dword ptr [ebp - 0x23c], 0x41f00000
00514ab2 comiss xmm0, dword ptr [0xb6aa0c]
00514ab9 movss dword ptr [ebp - 0x254], xmm0
00514ac1 cmovbe eax, ecx
00514ac4 movss xmm0, dword ptr [eax]
00514ac8 movss dword ptr [edi + 0xb08], xmm0
00514ad0 mov eax, dword ptr [edi + 0xab4]
00514ad6 cmp eax, 3
00514ad9 je 0x514afc
00514adb cmp eax, 8
00514ade je 0x514afc
00514ae0 cmp eax, 4
00514ae3 jne 0x514b0d
00514ae5 cmp dword ptr [edi + 0x70], 0
00514ae9 je 0x514b0d
00514aeb push 0xb4034c
00514af0 lea ecx, [edi + 0x6c]
00514af3 call 0x405f30
00514af8 test al, al
00514afa je 0x514b0d
00514afc movss xmm2, dword ptr [ebp - 0x28c]
00514b04 mov ecx, edi
00514b06 push 1
00514b08 call 0x6af8d0
00514b0d mov eax, dword ptr [edi + 0xab4]
00514b13 cmp eax, 3
00514b16 je 0x514b1d
00514b18 cmp eax, 4
00514b1b jne 0x514b3f
00514b1d mov eax, dword ptr [edi + 0xe6c]
00514b23 cmp eax, -1
00514b26 je 0x514b3f
00514b28 push edi
00514b29 push eax
00514b2a push 9
00514b2c call 0x8b10b0
00514b31 test al, al
00514b33 je 0x514b3f
00514b35 mov dword ptr [edi + 0xb0c], 0x3f800000
00514b3f push ecx
00514b40 lea eax, [ebp - 0x2a8]
00514b46 mov dword ptr [esp], 0x42700000
00514b4d push eax
00514b4e mov ecx, edi
00514b50 call 0x695a30
00514b55 movss xmm2, dword ptr [ebp - 0x2a8]
00514b5d lea ecx, [edi + 0x294]
00514b63 movss xmm3, dword ptr [ebp - 0x2a4]
00514b6b subss xmm2, dword ptr [ecx]
00514b6f subss xmm3, dword ptr [ecx + 4]
00514b74 mov eax, dword ptr [edi + 0xab4]
00514b7a mov dword ptr [ebp - 0x27c], ecx
00514b80 movss dword ptr [ebp - 0x268], xmm2
00514b88 movss dword ptr [ebp - 0x248], xmm3
00514b90 cmp eax, 3
00514b93 jne 0x514cca
00514b99 movss xmm0, dword ptr [edi + 0x28c]
00514ba1 ucomiss xmm0, dword ptr [0xc02fec]
00514ba8 lahf 
00514ba9 test ah, 0x44
00514bac jp 0x515175
00514bb2 movss xmm0, dword ptr [edi + 0x290]
00514bba ucomiss xmm0, dword ptr [0xc02ff0]
00514bc1 lahf 
00514bc2 test ah, 0x44
00514bc5 jp 0x515175
00514bcb mov eax, dword ptr [edi + 0x28]
00514bce cmp eax, 0x56
00514bd1 je 0x514bde
00514bd3 cmp eax, 0x131
00514bd8 jne 0x515175
00514bde mov eax, dword ptr [edi + 0x160]
00514be4 and eax, 0x1000a00
00514be9 or eax, 0
00514bec jne 0x515175
00514bf2 mov edx, dword ptr [edi + 0xaf0]
00514bf8 test edx, edx
00514bfa jg 0x514cf6
00514c00 cmp dword ptr [edi + 0xe6c], -1
00514c07 je 0x514c26
00514c09 movss xmm1, dword ptr [0xb6accc]
00514c11 mov ecx, edi
00514c13 push 7
00514c15 push eax
00514c16 call 0x6a15a0
00514c1b movzx eax, al
00514c1e lea ecx, [edi + 0x294]
00514c24 jmp 0x514c48
00514c26 movaps xmm0, xmm3
00514c29 movaps xmm1, xmm2
00514c2c mulss xmm0, xmm3
00514c30 xor eax, eax
00514c32 mulss xmm1, xmm2
00514c36 addss xmm1, xmm0
00514c3a movss xmm0, dword ptr [0xb6ad60]
00514c42 comiss xmm0, xmm1
00514c45 seta al
00514c48 test eax, eax
00514c4a je 0x514cc4
00514c4c cmp dword ptr [edi + 0xe6c], -1
00514c53 jne 0x514c7f
00514c55 push 0
00514c57 push 0
00514c59 push 0
00514c5b push 0x3e7
00514c60 push 3
00514c62 lea eax, [ebp - 0x2a8]
00514c68 push eax
00514c69 push ecx
00514c6a mov ecx, dword ptr [0xbfd65c]
00514c70 mov ecx, dword ptr [ecx + 0x18190]
00514c76 call 0x7af4b0
00514c7b test al, al
00514c7d je 0x514cc4
00514c7f push 1
00514c81 mov ecx, edi
00514c83 call 0x6afe20
00514c88 push 1
00514c8a push esi
00514c8b lea ecx, [edi + 0x3c]
00514c8e mov dword ptr [edi + 0xaf0], 2
00514c98 mov dword ptr [edi + 0xab4], 8
00514ca2 call 0x405740
00514ca7 test al, al
00514ca9 je 0x514cba
00514cab lea ecx, [edi + 0x6c]
00514cae call 0x405330
00514cb3 mov byte ptr [edi + 0x80], 1
00514cba mov dword ptr [edi + 0x360], 0
00514cc4 mov eax, dword ptr [edi + 0xab4]
00514cca cmp eax, 8
00514ccd jne 0x515175
00514cd3 cmp dword ptr [edi + 0xe6c], -1
00514cda jne 0x514d15
00514cdc movss xmm0, dword ptr [0xc02fec]
00514ce4 movss dword ptr [edi + 0xe70], xmm0
00514cec movss xmm0, dword ptr [0xc02ff0]
00514cf4 jmp 0x514d5d
00514cf6 cvttss2si eax, dword ptr [edi + 0x2fc]
00514cfe cvttss2si ecx, dword ptr [edi + 0x2f8]
00514d06 sub ecx, eax
00514d08 add ecx, edx
00514d0a mov dword ptr [edi + 0xaf0], ecx
00514d10 jmp 0x515175
00514d15 movss xmm2, dword ptr [0xb6a2cc]
00514d1d lea eax, [ebp - 0x288]
00514d23 push eax
00514d24 mov ecx, edi
00514d26 call 0x6af380
00514d2b movss xmm1, dword ptr [ebp - 0x288]
00514d33 ucomiss xmm1, dword ptr [0xc02fec]
00514d3a movss xmm0, dword ptr [ebp - 0x284]
00514d42 lahf 
00514d43 test ah, 0x44
00514d46 jp 0x514d55
00514d48 ucomiss xmm0, dword ptr [0xc02ff0]
00514d4f lahf 
00514d50 test ah, 0x44
00514d53 jnp 0x514d65
00514d55 movss dword ptr [edi + 0xe70], xmm1
00514d5d movss dword ptr [edi + 0xe74], xmm0
00514d65 cmp dword ptr [edi + 0x70], 0
00514d69 je 0x515141
00514d6f push 0xb400ac
00514d74 lea ecx, [edi + 0x6c]
00514d77 call 0x405e90
00514d7c test al, al
00514d7e je 0x515132
00514d84 movss xmm0, dword ptr [0xb6a614]
00514d8c mov eax, dword ptr [edi + 0xbb4]
00514d92 movss dword ptr [ebp - 0x254], xmm0
00514d9a cmp eax, 0x12
00514d9d jne 0x514da9
00514d9f movss xmm0, dword ptr [0xb6a6f0]
00514da7 jmp 0x514db6
00514da9 cmp eax, 0x13
00514dac jne 0x514dbe
00514dae movss xmm0, dword ptr [0xb6a480]
00514db6 movss dword ptr [ebp - 0x254], xmm0
00514dbe mov esi, dword ptr [0xbfd680]
00514dc4 lea ecx, [ebp - 0x23c]
00514dca mov dword ptr [ebp - 0x23c], 0xb2
00514dd4 call 0x8b1340
00514dd9 movss xmm0, dword ptr [ebp - 0x254]
00514de1 sub esp, 8
00514de4 mov dword ptr [esp + 4], 0
00514dec movss dword ptr [esp], xmm0
00514df1 push 0
00514df3 push 2
00514df5 push ecx
00514df6 mov dword ptr [esp], 0x3f800000
00514dfd lea ecx, [esi + 0x29de0]
00514e03 push dword ptr [ebp - 0x23c]
00514e09 call 0x888de0
00514e0e cmp dword ptr [edi + 0xe6c], -1
00514e15 je 0x514e5b
00514e17 movss xmm2, dword ptr [edi + 0xe70]
00514e1f ucomiss xmm2, dword ptr [0xc02fec]
00514e26 lahf 
00514e27 test ah, 0x44
00514e2a jp 0x514e41
00514e2c movss xmm0, dword ptr [edi + 0xe74]
00514e34 ucomiss xmm0, dword ptr [0xc02ff0]
00514e3b lahf 
00514e3c test ah, 0x44
00514e3f jnp 0x514e5b
00514e41 movss xmm3, dword ptr [edi + 0xe74]
00514e49 movss dword ptr [ebp - 0x268], xmm2
00514e51 movss dword ptr [ebp - 0x248], xmm3
00514e59 jmp 0x514e6b
00514e5b movss xmm3, dword ptr [ebp - 0x248]
00514e63 movss xmm2, dword ptr [ebp - 0x268]
00514e6b cmp dword ptr [edi + 0x28], 0xf6
00514e72 jne 0x514fdd
00514e78 lea ecx, [ebp - 0xe8]
00514e7e call 0x430d70
00514e83 movaps xmm0, xmmword ptr [0xb6c280]
00514e8a lea esi, [edi + 0x294]
00514e90 mov eax, dword ptr [ebp - 0x8c]
00514e96 xorps xmm1, xmm1
00514e99 or dword ptr [ebp - 0x90], 0x2800
00514ea3 movups xmmword ptr [ebp - 0xbc], xmm0
00514eaa mov dword ptr [ebp - 0x8c], eax
00514eb0 movups xmmword ptr [ebp - 0xac], xmm1
00514eb7 mov dword ptr [ebp - 0x308], 0
00514ec1 movss xmm1, dword ptr [ebp - 0x264]
00514ec9 mov eax, dword ptr [ebp - 0x308]
00514ecf movaps xmm0, xmm1
00514ed2 unpcklps xmm0, xmm1
00514ed5 movaps xmm1, xmm3
00514ed8 movq qword ptr [ebp - 0x9c], xmm0
00514ee0 movss xmm0, dword ptr [esi]
00514ee4 movss dword ptr [ebp - 0x80], xmm0
00514ee9 movss xmm0, dword ptr [esi + 4]
00514eee movss dword ptr [ebp - 0x7c], xmm0
00514ef3 movaps xmm0, xmm2
00514ef6 mulss xmm0, xmm2
00514efa mov dword ptr [ebp - 0x94], eax
00514f00 mulss xmm1, xmm3
00514f04 mov byte ptr [ebp - 0xe8], 0
00514f0b movss dword ptr [ebp - 0x23c], xmm2
00514f13 movss dword ptr [ebp - 0x254], xmm3
00514f1b addss xmm0, xmm1
00514f1f call 0x4228c0
00514f24 comiss xmm0, dword ptr [ebp - 0x264]
00514f2b jbe 0x514f53
00514f2d movss xmm1, dword ptr [0xb6a614]
00514f35 divss xmm1, xmm0
00514f39 movss xmm2, dword ptr [ebp - 0x268]
00514f41 movss xmm3, dword ptr [ebp - 0x248]
00514f49 mulss xmm2, xmm1
00514f4d mulss xmm3, xmm1
00514f51 jmp 0x514f63
00514f53 movss xmm2, dword ptr [ebp - 0x23c]
00514f5b movss xmm3, dword ptr [ebp - 0x254]
00514f63 mulss xmm2, dword ptr [0xb6a928]
00514f6b lea eax, [ebp - 0xe8]
00514f71 mov ecx, edi
00514f73 mulss xmm3, dword ptr [0xb6a928]
00514f7b push eax
00514f7c push 0
00514f7e lea eax, [ebp - 0x288]
00514f84 movss dword ptr [ebp - 0x288], xmm2
00514f8c push eax
00514f8d push esi
00514f8e movss dword ptr [ebp - 0x284], xmm3
00514f96 call 0x6a1a20
00514f9b movss xmm2, dword ptr [ebp - 0x288]
00514fa3 lea eax, [ebp - 0xe8]
00514fa9 movss xmm1, dword ptr [ebp - 0x284]
00514fb1 xorps xmm2, xmmword ptr [0xb6c9b0]
00514fb8 xorps xmm1, xmmword ptr [0xb6c9b0]
00514fbf push eax
00514fc0 movss dword ptr [ebp - 0x298], xmm2
00514fc8 lea eax, [ebp - 0x298]
00514fce movss dword ptr [ebp - 0x294], xmm1
00514fd6 push 0
00514fd8 jmp 0x515129
00514fdd movaps xmm0, xmm2
00514fe0 movss dword ptr [ebp - 0x23c], xmm3
00514fe8 movss dword ptr [ebp - 0x254], xmm0
00514ff0 movaps xmm1, xmm3
00514ff3 mulss xmm0, xmm2
00514ff7 mulss xmm1, xmm3
00514ffb addss xmm0, xmm1
00514fff call 0x4228c0
00515004 comiss xmm0, dword ptr [ebp - 0x264]
0051500b jbe 0x51503b
0051500d movss xmm1, dword ptr [0xb6a614]
00515015 divss xmm1, xmm0
00515019 movss xmm0, dword ptr [ebp - 0x268]
00515021 movss xmm2, dword ptr [ebp - 0x248]
00515029 mulss xmm0, xmm1
0051502d mulss xmm2, xmm1
00515031 movss dword ptr [ebp - 0x254], xmm0
00515039 jmp 0x51504b
0051503b movss xmm2, dword ptr [ebp - 0x23c]
00515043 movss xmm0, dword ptr [ebp - 0x254]
0051504b cmp dword ptr [edi + 0x28], 0x131
00515052 lea esi, [edi + 0x294]
00515058 mulss xmm0, dword ptr [0xb6a928]
00515060 mulss xmm2, dword ptr [0xb6a928]
00515068 movss dword ptr [ebp - 0x288], xmm0
00515070 movss dword ptr [ebp - 0x284], xmm2
00515078 jne 0x515115
0051507e push ecx
0051507f mov dword ptr [esp], 0x3f800000
00515086 push 0
00515088 push 2
0051508a push ecx
0051508b mov dword ptr [esp], 0x3f800000
00515092 mov ecx, edi
00515094 push 0x13e
00515099 call 0x6ad720
0051509e lea ecx, [ebp - 0x238]
005150a4 call 0x430d70
005150a9 movss xmm1, dword ptr [ebp - 0x288]
005150b1 lea eax, [ebp - 0x238]
005150b7 movss xmm0, dword ptr [ebp - 0x284]
005150bf addss xmm1, dword ptr [esi]
005150c3 addss xmm0, dword ptr [esi + 4]
005150c8 push eax
005150c9 push ecx
005150ca mov dword ptr [esp], 0x41200000
005150d1 lea eax, [ebp - 0x298]
005150d7 push eax
005150d8 push 5
005150da mov ecx, edi
005150dc mov dword ptr [ebp - 0x224], 0x3f000000
005150e6 movss dword ptr [ebp - 0x298], xmm1
005150ee movss dword ptr [ebp - 0x294], xmm0
005150f6 call 0x6a3420
005150fb movss xmm1, dword ptr [ebp - 0x264]
00515103 comiss xmm1, dword ptr [ebp - 0x254]
0051510a seta al
0051510d mov byte ptr [edi + 0x13c], al
00515113 jmp 0x515132
00515115 lea ecx, [ebp - 0x238]
0051511b call 0x430d70
00515120 push eax
00515121 push 1
00515123 lea eax, [ebp - 0x288]
00515129 push eax
0051512a push esi
0051512b mov ecx, edi
0051512d call 0x6a1a20
00515132 cmp dword ptr [edi + 0x70], 0
00515136 je 0x515141
00515138 cmp byte ptr [edi + 0x80], 0
0051513f jne 0x515175
00515141 mov dword ptr [edi + 0xab4], 3
0051514b mov dword ptr [edi + 0x360], 0
00515155 movss xmm0, dword ptr [0xc02fec]
0051515d movss dword ptr [edi + 0x28c], xmm0
00515165 movss xmm0, dword ptr [0xc02ff0]
0051516d movss dword ptr [edi + 0x290], xmm0
00515175 mov eax, dword ptr [edi + 0xab4]
0051517b mov esi, 3
00515180 mov dword ptr [ebp - 0x2ac], esi
00515186 cmp eax, 6
00515189 jne 0x515301
0051518f cmp dword ptr [edi + 0x70], 0
00515193 jne 0x51519d
00515195 mov ecx, dword ptr [edi + 0xe6c]
0051519b jmp 0x5151b4
0051519d push 0xb40338
005151a2 lea ecx, [edi + 0x6c]
005151a5 call 0x405f30
005151aa mov ecx, dword ptr [edi + 0xe6c]
005151b0 test al, al
005151b2 jne 0x51520a
005151b4 movss xmm0, dword ptr [edi + 0x2c4]
005151bc mulss xmm0, dword ptr [0xb6a560]
005151c4 mov dword ptr [edi + 0x180], 4
005151ce mov dword ptr [edi + 0x17c], 5
005151d8 movss dword ptr [edi + 0x2c4], xmm0
005151e0 cmp ecx, -1
005151e3 je 0x516375
005151e9 push 1
005151eb push 0
005151ed push ecx
005151ee mov dword ptr [esp], 0x3f000000
005151f5 lea ecx, [edi + 0x364]
005151fb push 0xc02fec
00515200 call 0x7a3650
00515205 jmp 0x516375
0051520a movss xmm4, dword ptr [edi + 0xb00]
00515212 xor eax, eax
00515214 addss xmm4, dword ptr [0xb6a234]
0051521c cmp ecx, -1
0051521f mov dword ptr [edi + 0x180], 0
00515229 cmovne eax, esi
0051522c mov dword ptr [edi + 0x17c], eax
00515232 movss dword ptr [edi + 0xb00], xmm4
0051523a je 0x515281
0051523c mulss xmm4, dword ptr [0xb6a358]
00515244 mov ecx, edi
00515246 movss xmm2, dword ptr [0xb6a680]
0051524e movss xmm3, dword ptr [0xb6aa0c]
00515256 movss xmm1, dword ptr [0xb6a864]
0051525e subss xmm2, xmm4
00515262 call 0x6b00f0
00515267 mov eax, dword ptr [edi + 0x294]
0051526d mov dword ptr [edi + 0x28c], eax
00515273 mov eax, dword ptr [edi + 0x298]
00515279 mov dword ptr [edi + 0x290], eax
0051527f jmp 0x5152cb
00515281 movss xmm2, dword ptr [0xb6a614]
00515289 movaps xmm1, xmm4
0051528c mulss xmm1, dword ptr [edi + 0x28c]
00515294 subss xmm2, xmm4
00515298 mulss xmm4, dword ptr [edi + 0x290]
005152a0 movaps xmm0, xmm2
005152a3 mulss xmm2, dword ptr [edi + 0x298]
005152ab mulss xmm0, dword ptr [edi + 0x294]
005152b3 addss xmm2, xmm4
005152b7 addss xmm1, xmm0
005152bb movss dword ptr [edi + 0x298], xmm2
005152c3 movss dword ptr [edi + 0x294], xmm1
005152cb cmp dword ptr [edi + 0x70], 0
005152cf je 0x5152de
005152d1 cmp byte ptr [edi + 0x80], 0
005152d8 jne 0x516375
005152de mov dword ptr [edi + 0xab4], 7
005152e8 mov dword ptr [edi + 0x360], 0
005152f2 mov dword ptr [edi + 0x2ac], 0
005152fc jmp 0x516375
00515301 cmp eax, 7
00515304 jne 0x515647
0051530a cmp dword ptr [edi + 0x70], 0
0051530e je 0x515359
00515310 lea esi, [edi + 0x6c]
00515313 push 0xb4034c
00515318 mov ecx, esi
0051531a call 0x405f30
0051531f test al, al
00515321 je 0x515354
00515323 movss xmm0, dword ptr [edi + 0x2c4]
0051532b mulss xmm0, dword ptr [0xb6a560]
00515333 mov dword ptr [edi + 0x180], 4
0051533d mov dword ptr [edi + 0x17c], 5
00515347 movss dword ptr [edi + 0x2c4], xmm0
0051534f jmp 0x515421
00515354 mov esi, 3
00515359 movss xmm3, dword ptr [edi + 0xb00]
00515361 xor eax, eax
00515363 addss xmm3, dword ptr [0xb6a234]
0051536b cmp dword ptr [edi + 0xe6c], -1
00515372 mov dword ptr [edi + 0x180], 0
0051537c cmovne eax, esi
0051537f mov dword ptr [edi + 0x17c], eax
00515385 movss dword ptr [edi + 0xb00], xmm3
0051538d je 0x5153d4
0051538f mulss xmm3, dword ptr [0xb6a358]
00515397 mov ecx, edi
00515399 movss xmm2, dword ptr [0xb6a680]
005153a1 movss xmm1, dword ptr [0xb6a864]
005153a9 subss xmm2, xmm3
005153ad movss xmm3, dword ptr [0xb6aa0c]
005153b5 call 0x6b00f0
005153ba mov eax, dword ptr [edi + 0x294]
005153c0 mov dword ptr [edi + 0x28c], eax
005153c6 mov eax, dword ptr [edi + 0x298]
005153cc mov dword ptr [edi + 0x290], eax
005153d2 jmp 0x51541e
005153d4 movss xmm2, dword ptr [0xb6a614]
005153dc movaps xmm0, xmm3
005153df mulss xmm0, dword ptr [edi + 0x28c]
005153e7 subss xmm2, xmm3
005153eb mulss xmm3, dword ptr [edi + 0x290]
005153f3 movaps xmm1, xmm2
005153f6 mulss xmm2, dword ptr [edi + 0x298]
005153fe mulss xmm1, dword ptr [edi + 0x294]
00515406 addss xmm2, xmm3
0051540a addss xmm1, xmm0
0051540e movss dword ptr [edi + 0x298], xmm2
00515416 movss dword ptr [edi + 0x294], xmm1
0051541e lea esi, [edi + 0x6c]
00515421 cmp dword ptr [edi + 0x70], 0
00515425 je 0x51560e
0051542b push 0xb4034c
00515430 mov ecx, esi
00515432 call 0x405e90
00515437 test al, al
00515439 je 0x5155fb
0051543f push ecx
00515440 mov dword ptr [esp], 0x3f800000
00515447 push 0
00515449 push 2
0051544b push ecx
0051544c mov dword ptr [esp], 0x40000000
00515453 mov ecx, edi
00515455 push 0x45
00515457 call 0x6ad720
0051545c push ecx
0051545d mov dword ptr [esp], 0x3f800000
00515464 push 0
00515466 push 2
00515468 push ecx
00515469 mov dword ptr [esp], 0x3f800000
00515470 mov ecx, edi
00515472 push 0xb2
00515477 call 0x6ad720
0051547c cmp dword ptr [edi + 0x28], 0x22
00515480 jne 0x515573
00515486 cmp dword ptr [edi + 0x2c], 1
0051548a jne 0x515573
00515490 call 0x6c3d90
00515495 mov ecx, dword ptr [0xbfd65c]
0051549b lea esi, [edi + 0x294]
005154a1 push eax
005154a2 push 0
005154a4 push edi
005154a5 push 0xc02fec
005154aa push esi
005154ab push 0x1a
005154ad push 0x3e8
005154b2 call 0x422e20
005154b7 movss xmm1, dword ptr [0xbc7a28]
005154bf mov ecx, eax
005154c1 movss xmm0, dword ptr [0xbc7a2c]
005154c9 mulss xmm1, dword ptr [0xb6a7b0]
005154d1 mulss xmm0, dword ptr [0xb6a7b0]
005154d9 mov eax, dword ptr [ecx]
005154db movss dword ptr [ecx + 0xd8], xmm1
005154e3 mov dword ptr [ecx + 0x3ac], 0x12c
005154ed movss dword ptr [ecx + 0xdc], xmm0
005154f5 mov dword ptr [ecx + 0x3b0], 0x12c
005154ff call dword ptr [eax + 0xc]
00515502 push 0xc02fec
00515507 lea eax, [edi + 0x1dc]
0051550d mov edx, esi
0051550f push eax
00515510 push 0xc02fec
00515515 mov ecx, 2
0051551a call 0x6aead0
0051551f add esp, 0xc
00515522 lea ecx, [ebp - 0x190]
00515528 mov dword ptr [eax + 0x2b0], 0xc1200000
00515532 call 0x430d70
00515537 push 0xbc5254
0051553c lea ecx, [ebp - 0x164]
00515542 call 0x4021a0
00515547 lea eax, [ebp - 0x190]
0051554d mov dword ptr [ebp - 0x17c], 0x3f333333
00515557 push eax
00515558 push ecx
00515559 mov dword ptr [esp], 0x41200000
00515560 mov ecx, edi
00515562 push 0xc02fec
00515567 push 6
00515569 call 0x6a3420
0051556e jmp 0x5155fb
00515573 push 0xc02fec
00515578 lea ecx, [ebp - 0x40]
0051557b call 0x402120
00515580 push eax
00515581 lea esi, [edi + 0x294]
00515587 mov ecx, 2
0051558c push 0xc02fec
00515591 mov edx, esi
00515593 call 0x6aead0
00515598 add esp, 0xc
0051559b mov dword ptr [eax + 0x2b0], 0xc1200000
005155a5 mov eax, dword ptr [0xbfd65c]
005155aa mov eax, dword ptr [eax + 0x243624]
005155b0 cmp eax, 1
005155b3 je 0x5155c4
005155b5 cmp eax, 3
005155b8 je 0x5155c4
005155ba movss xmm0, dword ptr [0xb6a95c]
005155c2 jmp 0x5155cc
005155c4 movss xmm0, dword ptr [0xb6a98c]
005155cc lea ecx, [ebp - 0x190]
005155d2 movss dword ptr [ebp - 0x2a0], xmm0
005155da mov dword ptr [ebp - 0x29c], 0
005155e4 call 0x430d70
005155e9 push eax
005155ea push 6
005155ec lea eax, [ebp - 0x2a0]
005155f2 mov ecx, edi
005155f4 push eax
005155f5 push esi
005155f6 call 0x6a1a20
005155fb cmp dword ptr [edi + 0x70], 0
005155ff je 0x51560e
00515601 cmp byte ptr [edi + 0x80], 0
00515608 jne 0x516375
0051560e mov dword ptr [edi + 0xab4], 3
00515618 mov dword ptr [edi + 0x360], 0
00515622 movss xmm0, dword ptr [0xc02fec]
0051562a movss dword ptr [edi + 0x28c], xmm0
00515632 movss xmm0, dword ptr [0xc02ff0]
0051563a movss dword ptr [edi + 0x290], xmm0
00515642 jmp 0x516375
00515647 cmp eax, 3
0051564a jne 0x515c25
00515650 mov ecx, dword ptr [ebp - 0x26c]
00515656 cmp dword ptr [edi + 0x360], ecx
0051565c jl 0x516375
00515662 movss xmm0, dword ptr [edi + 0x28c]
0051566a ucomiss xmm0, dword ptr [0xc02fec]
00515671 lahf 
00515672 test ah, 0x44
00515675 jp 0x516375
0051567b movss xmm0, dword ptr [edi + 0x290]
00515683 ucomiss xmm0, dword ptr [0xc02ff0]
0051568a lahf 
0051568b test ah, 0x44
0051568e jp 0x516375
00515694 cmp dword ptr [edi + 0xe6c], -1
0051569b movss xmm1, dword ptr [ebp - 0x268]
005156a3 movss xmm2, dword ptr [ebp - 0x248]
005156ab movaps xmm3, xmm1
005156ae movaps xmm0, xmm2
005156b1 mulss xmm3, xmm1
005156b5 mulss xmm0, xmm2
005156b9 addss xmm3, xmm0
005156bd movss xmm0, dword ptr [ebp - 0x264]
005156c5 movss dword ptr [ebp - 0x26c], xmm0
005156cd movss dword ptr [ebp - 0x270], xmm0
005156d5 je 0x5157ca
005156db test ecx, ecx
005156dd jne 0x5156f0
005156df movss xmm0, dword ptr [edi + 0xb08]
005156e7 comiss xmm0, dword ptr [0xb6a974]
005156ee ja 0x5156ff
005156f0 mov ecx, edi
005156f2 call 0x6afb10
005156f7 test al, al
005156f9 je 0x5157b5
005156ff lea eax, [ebp - 0x258]
00515705 mov ecx, edi
00515707 push eax
00515708 call 0x6afac0
0051570d movss xmm1, dword ptr [eax + 4]
00515712 subss xmm1, dword ptr [edi + 0x298]
0051571a movss xmm2, dword ptr [eax]
0051571e subss xmm2, dword ptr [edi + 0x294]
00515726 movaps xmm0, xmm1
00515729 movss dword ptr [ebp - 0x254], xmm1
00515731 mulss xmm0, xmm1
00515735 movaps xmm1, xmm2
00515738 movss dword ptr [ebp - 0x23c], xmm2
00515740 mulss xmm1, xmm2
00515744 addss xmm0, xmm1
00515748 call 0x4228c0
0051574d comiss xmm0, dword ptr [0xb6a974]
00515754 jbe 0x5157a0
00515756 movss xmm0, dword ptr [ebp - 0x23c]
0051575e lea eax, [ebp - 0x240]
00515764 movss xmm1, dword ptr [ebp - 0x254]
0051576c addss xmm0, dword ptr [edi + 0x294]
00515774 addss xmm1, dword ptr [edi + 0x298]
0051577c push ecx
0051577d mov dword ptr [esp], 0x41200000
00515784 push eax
00515785 movss dword ptr [ebp - 0x240], xmm0
0051578d lea eax, [ebp - 0x258]
00515793 movss dword ptr [ebp - 0x23c], xmm1
0051579b jmp 0x5158f2
005157a0 movss xmm0, dword ptr [0xc02fec]
005157a8 movss xmm1, dword ptr [0xc02ff0]
005157b0 jmp 0x51590d
005157b5 movss xmm0, dword ptr [ebp - 0x270]
005157bd movss xmm1, dword ptr [ebp - 0x26c]
005157c5 jmp 0x51591d
005157ca movss xmm0, dword ptr [ebp - 0x28c]
005157d2 mulss xmm0, xmm0
005157d6 comiss xmm0, xmm3
005157d9 jbe 0x515882
005157df cmp dword ptr [edi + 0x28], 0x36
005157e3 mulss xmm1, dword ptr [ebp - 0x250]
005157eb mulss xmm2, dword ptr [ebp - 0x250]
005157f3 divss xmm1, dword ptr [0xb6aba8]
005157fb divss xmm2, dword ptr [0xb6aba8]
00515803 movss xmm0, dword ptr [ebp - 0x2a4]
0051580b addss xmm1, dword ptr [ebp - 0x2a8]
00515813 addss xmm0, xmm2
00515817 movss dword ptr [ebp - 0x268], xmm1
0051581f movss dword ptr [ebp - 0x23c], xmm0
00515827 movss dword ptr [ebp - 0x270], xmm1
0051582f movss dword ptr [ebp - 0x26c], xmm0
00515837 jne 0x5158dd
0051583d mov ecx, edi
0051583f call 0x695680
00515844 movss xmm2, dword ptr [ebp - 0x268]
0051584c movss xmm0, dword ptr [eax + 0x2b8]
00515854 mulss xmm0, dword ptr [0xb6a8f4]
0051585c movss xmm1, dword ptr [eax + 0x2bc]
00515864 mulss xmm1, dword ptr [0xb6a8f4]
0051586c addss xmm2, xmm0
00515870 addss xmm1, dword ptr [ebp - 0x23c]
00515878 movss dword ptr [ebp - 0x270], xmm2
00515880 jmp 0x5158d5
00515882 movss xmm0, dword ptr [ebp - 0x250]
0051588a lea eax, [ebp - 0x258]
00515890 addss xmm0, dword ptr [0xb6aaf0]
00515898 push eax
00515899 movss dword ptr [ebp - 0x23c], xmm0
005158a1 call 0x659290
005158a6 movss xmm1, dword ptr [ebp - 0x23c]
005158ae add esp, 4
005158b1 movaps xmm0, xmm1
005158b4 mulss xmm0, dword ptr [eax]
005158b8 mulss xmm1, dword ptr [eax + 4]
005158bd addss xmm0, dword ptr [edi + 0x294]
005158c5 addss xmm1, dword ptr [edi + 0x298]
005158cd movss dword ptr [ebp - 0x270], xmm0
005158d5 movss dword ptr [ebp - 0x26c], xmm1
005158dd push ecx
005158de lea eax, [ebp - 0x270]
005158e4 mov dword ptr [esp], 0x40a00000
005158eb push eax
005158ec lea eax, [ebp - 0x240]
005158f2 mov ecx, dword ptr [0xbfd65c]
005158f8 push eax
005158f9 mov ecx, dword ptr [ecx + 0x18190]
005158ff call 0x427710
00515904 movss xmm1, dword ptr [eax + 4]
00515909 movss xmm0, dword ptr [eax]
0051590d movss dword ptr [ebp - 0x270], xmm0
00515915 movss dword ptr [ebp - 0x26c], xmm1
0051591d ucomiss xmm0, dword ptr [0xc02fec]
00515924 lahf 
00515925 test ah, 0x44
00515928 jp 0x515937
0051592a ucomiss xmm1, dword ptr [0xc02ff0]
00515931 lahf 
00515932 test ah, 0x44
00515935 jnp 0x515956
00515937 push dword ptr [ebp - 0x26c]
0051593d mov ecx, dword ptr [0xbfd65c]
00515943 push dword ptr [ebp - 0x270]
00515949 mov ecx, dword ptr [ecx + 0x18190]
0051594f call 0x7aee40
00515954 mov esi, eax
00515956 cmp dword ptr [edi + 0x28], 0x348
0051595d jne 0x515b17
00515963 cmp dword ptr [edi + 0xe6c], -1
0051596a jne 0x515b20
00515970 mov edx, dword ptr [0xbfd65c]
00515976 lea eax, [ebp - 0x270]
0051597c push eax
0051597d mov ecx, dword ptr [edx + 0x18190]
00515983 call 0x7ce8d0
00515988 mov edi, dword ptr [ebp - 0x27c]
0051598e cmp eax, 0xc8
00515993 mov ecx, 2
00515998 mov dword ptr [ebp - 0x23c], 0
005159a2 cmovge esi, ecx
005159a5 test esi, esi
005159a7 je 0x515b11
005159ad movss xmm0, dword ptr [ebp - 0x250]
005159b5 addss xmm0, dword ptr [0xb6aaf0]
005159bd movss dword ptr [ebp - 0x254], xmm0
005159c5 call 0x6c3d90
005159ca movd xmm0, eax
005159ce cvtdq2pd xmm0, xmm0
005159d2 shr eax, 0x1f
005159d5 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
005159de cvtpd2ps xmm0, xmm0
005159e2 mulss xmm0, dword ptr [0xb6a19c]
005159ea mulss xmm0, dword ptr [0xb6a874]
005159f2 addss xmm0, xmm0
005159f6 movss dword ptr [ebp - 0x27c], xmm0
005159fe call 0x412010
00515a03 movss dword ptr [ebp - 0x244], xmm0
00515a0b movss xmm0, dword ptr [ebp - 0x27c]
00515a13 call 0x411fe0
00515a18 movss xmm1, dword ptr [ebp - 0x254]
00515a20 lea eax, [ebp - 0x290]
00515a26 mov esi, dword ptr [0xbfd65c]
00515a2c sub esp, 0xc
00515a2f movss xmm3, dword ptr [ebp - 0x264]
00515a37 mulss xmm0, xmm1
00515a3b mulss xmm1, dword ptr [ebp - 0x244]
00515a43 mov ecx, dword ptr [esi + 0x18190]
00515a49 addss xmm0, dword ptr [edi]
00515a4d mov dword ptr [esp + 8], 0
00515a55 addss xmm1, dword ptr [edi + 4]
00515a5a mov dword ptr [esp + 4], 0
00515a62 mov dword ptr [esp], 0
00515a69 push eax
00515a6a lea eax, [ebp - 0x24c]
00515a70 movss dword ptr [ebp - 0x290], xmm0
00515a78 push eax
00515a79 movss dword ptr [ebp - 0x28c], xmm1
00515a81 call 0x7cec10
00515a86 movss xmm0, dword ptr [ebp - 0x24c]
00515a8e mov ecx, dword ptr [esi + 0x18190]
00515a94 movss dword ptr [ebp - 0x270], xmm0
00515a9c movss xmm0, dword ptr [ebp - 0x248]
00515aa4 movss dword ptr [ebp - 0x26c], xmm0
00515aac push dword ptr [ebp - 0x26c]
00515ab2 push dword ptr [ebp - 0x270]
00515ab8 call 0x7aee40
00515abd mov esi, eax
00515abf lea eax, [ebp - 0x270]
00515ac5 push eax
00515ac6 mov eax, dword ptr [0xbfd65c]
00515acb mov ecx, dword ptr [eax + 0x18190]
00515ad1 call 0x7ce950
00515ad6 mov ecx, eax
00515ad8 test ecx, ecx
00515ada js 0x515afb
00515adc mov edx, dword ptr [0xbfd65c]
00515ae2 mov eax, dword ptr [edx + 0x18190]
00515ae8 cmp dword ptr [eax + ecx*4 + 0x76c], 0xc8
00515af3 mov eax, 2
00515af8 cmovge esi, eax
00515afb mov eax, dword ptr [ebp - 0x23c]
00515b01 inc eax
00515b02 mov dword ptr [ebp - 0x23c], eax
00515b08 cmp eax, 0xa
00515b0b jb 0x5159a5
00515b11 mov edi, dword ptr [ebp - 0x29c]
00515b17 cmp dword ptr [edi + 0xe6c], -1
00515b1e je 0x515b38
00515b20 movss xmm1, dword ptr [0xb6accc]
00515b28 mov ecx, edi
00515b2a push 7
00515b2c push 0
00515b2e call 0x6a15a0
00515b33 movzx eax, al
00515b36 jmp 0x515b4d
00515b38 call 0x6c3d90
00515b3d xor edx, edx
00515b3f mov ecx, 3
00515b44 div ecx
00515b46 xor eax, eax
00515b48 test edx, edx
00515b4a sete al
00515b4d test eax, eax
00515b4f je 0x515b9d
00515b51 cmp dword ptr [edi + 0x28], 0xf6
00515b58 jne 0x515b9d
00515b5a push 0
00515b5c push 0x1000a00
00515b61 mov ecx, edi
00515b63 call 0x4122f0
00515b68 test al, al
00515b6a jne 0x515b9d
00515b6c push 1
00515b6e mov ecx, edi
00515b70 call 0x6afe20
00515b75 push 1
00515b77 push 0xb40360
00515b7c lea ecx, [edi + 0x3c]
00515b7f mov dword ptr [edi + 0xab4], 8
00515b89 call 0x4054f0
00515b8e mov dword ptr [edi + 0x360], 0
00515b98 jmp 0x516375
00515b9d test esi, esi
00515b9f jne 0x516375
00515ba5 mov eax, dword ptr [0xbfd65c]
00515baa mov esi, dword ptr [eax + 0x18190]
00515bb0 lea eax, [ebp - 0x270]
00515bb6 push eax
00515bb7 mov ecx, esi
00515bb9 call 0x7ce950
00515bbe test eax, eax
00515bc0 js 0x516375
00515bc6 push eax
00515bc7 lea eax, [ebp - 0x280]
00515bcd mov ecx, esi
00515bcf push eax
00515bd0 call 0x7cebc0
00515bd5 push 1
00515bd7 push dword ptr [ebp - 0x260]
00515bdd mov ecx, dword ptr [eax]
00515bdf mov dword ptr [edi + 0x28c], ecx
00515be5 lea ecx, [edi + 0x3c]
00515be8 mov eax, dword ptr [eax + 4]
00515beb mov dword ptr [edi + 0x290], eax
00515bf1 mov dword ptr [edi + 0xab4], 4
00515bfb call 0x4054f0
00515c00 cmp dword ptr [edi + 0x360], 0x270f
00515c0a jl 0x515c16
00515c0c push 4
00515c0e lea ecx, [edi + 0x3c]
00515c11 call 0x405890
00515c16 mov dword ptr [edi + 0x360], 0
00515c20 jmp 0x516375
00515c25 cmp eax, 4
00515c28 jne 0x516375
00515c2e mov eax, dword ptr [edi + 0x70]
00515c31 test eax, eax
00515c33 je 0x515c3a
00515c35 mov al, byte ptr [eax + 0x34]
00515c38 jmp 0x515c3c
00515c3a xor al, al
00515c3c movss xmm1, dword ptr [edi + 0x290]
00515c44 lea esi, [edi + 0x294]
00515c4a subss xmm1, dword ptr [esi + 4]
00515c4f movss xmm2, dword ptr [edi + 0x28c]
00515c57 subss xmm2, dword ptr [esi]
00515c5b mov dword ptr [ebp - 0x248], eax
00515c61 movaps xmm0, xmm1
00515c64 movss dword ptr [ebp - 0x254], xmm1
00515c6c mulss xmm0, xmm1
00515c70 movss dword ptr [ebp - 0x27c], xmm1
00515c78 movaps xmm1, xmm2
00515c7b mulss xmm1, xmm2
00515c7f movss dword ptr [ebp - 0x260], xmm2
00515c87 movss dword ptr [ebp - 0x280], xmm2
00515c8f addss xmm0, xmm1
00515c93 call 0x4228c0
00515c98 cmp byte ptr [ebp - 0x248], 0
00515c9f movss dword ptr [ebp - 0x29c], xmm0
00515ca7 jne 0x51604c
00515cad cmp dword ptr [edi + 0x70], 0
00515cb1 je 0x515ff8
00515cb7 push 0xb4034c
00515cbc lea ecx, [edi + 0x6c]
00515cbf call 0x405e90
00515cc4 test al, al
00515cc6 je 0x515fcb
00515ccc push ecx
00515ccd mov dword ptr [esp], 0x3f800000
00515cd4 push 0
00515cd6 push 2
00515cd8 push ecx
00515cd9 mov dword ptr [esp], 0x3f800000
00515ce0 mov ecx, edi
00515ce2 push 0x45
00515ce4 call 0x6ad720
00515ce9 mov eax, dword ptr [edi + 0x28]
00515cec cmp eax, 0x348
00515cf1 jne 0x515d5d
00515cf3 call 0x6c3d90
00515cf8 mov ecx, dword ptr [0xbfd65c]
00515cfe push eax
00515cff push 0
00515d01 push edi
00515d02 push 0xc02fec
00515d07 push esi
00515d08 push 0x16
00515d0a push 0x3e8
00515d0f call 0x422e20
00515d14 movss xmm2, dword ptr [0xbc7a28]
00515d1c mov ecx, eax
00515d1e movss xmm1, dword ptr [0xbc7a2c]
00515d26 mulss xmm2, dword ptr [0xb6a680]
00515d2e mulss xmm1, dword ptr [0xb6a680]
00515d36 mov eax, dword ptr [ecx]
00515d38 movss dword ptr [ecx + 0xd8], xmm2
00515d40 movss dword ptr [ecx + 0xdc], xmm1
00515d48 call dword ptr [eax + 0xc]
00515d4b push 0xc02fec
00515d50 lea ecx, [ebp - 0x40]
00515d53 call 0x402120
00515d58 jmp 0x515de7
00515d5d cmp eax, 0x22
00515d60 jne 0x515e0b
00515d66 cmp dword ptr [edi + 0x2c], 1
00515d6a jne 0x515fcb
00515d70 call 0x6c3d90
00515d75 mov ecx, dword ptr [0xbfd65c]
00515d7b push eax
00515d7c push 0
00515d7e push edi
00515d7f push 0xc02fec
00515d84 push esi
00515d85 push 0x1a
00515d87 push 0x3e8
00515d8c call 0x422e20
00515d91 movss xmm1, dword ptr [0xbc7a28]
00515d99 mov ecx, eax
00515d9b movss xmm0, dword ptr [0xbc7a2c]
00515da3 mulss xmm1, dword ptr [0xb6a6f0]
00515dab mulss xmm0, dword ptr [0xb6a6f0]
00515db3 mov eax, dword ptr [ecx]
00515db5 movss dword ptr [ecx + 0xd8], xmm1
00515dbd mov dword ptr [ecx + 0x3ac], 0x12c
00515dc7 movss dword ptr [ecx + 0xdc], xmm0
00515dcf mov dword ptr [ecx + 0x3b0], 0x12c
00515dd9 call dword ptr [eax + 0xc]
00515ddc push 0xc02fec
00515de1 lea eax, [edi + 0x1dc]
00515de7 push eax
00515de8 push 0xc02fec
00515ded mov edx, esi
00515def mov ecx, 2
00515df4 call 0x6aead0
00515df9 add esp, 0xc
00515dfc mov dword ptr [eax + 0x2b0], 0xc1200000
00515e06 jmp 0x515e8c
00515e0b cmp eax, 0x1d
00515e0e jne 0x515fcb
00515e14 mov eax, dword ptr [edi + 0x2c]
00515e17 cmp eax, 2
00515e1a jne 0x515eb7
00515e20 call 0x6c3d90
00515e25 mov ecx, dword ptr [0xbfd65c]
00515e2b push eax
00515e2c push 0
00515e2e push edi
00515e2f push 0xc02fec
00515e34 push esi
00515e35 push 0x19
00515e37 push 0x3e8
00515e3c call 0x422e20
00515e41 movss xmm2, dword ptr [0xbc7a28]
00515e49 mov ecx, eax
00515e4b movss xmm1, dword ptr [0xbc7a2c]
00515e53 mulss xmm2, dword ptr [0xb6a560]
00515e5b mulss xmm1, dword ptr [0xb6a560]
00515e63 mov eax, dword ptr [ecx]
00515e65 movss dword ptr [ecx + 0xd8], xmm2
00515e6d mov dword ptr [ecx + 0x3ac], 0x96
00515e77 movss dword ptr [ecx + 0xdc], xmm1
00515e7f mov dword ptr [ecx + 0x3b0], 0x96
00515e89 call dword ptr [eax + 0xc]
00515e8c mov eax, dword ptr [0xbfd65c]
00515e91 push 0x384
00515e96 mov esi, dword ptr [eax + 0x18190]
00515e9c lea eax, [edi + 0x294]
00515ea2 push eax
00515ea3 mov ecx, esi
00515ea5 call 0x7ce950
00515eaa push eax
00515eab mov ecx, esi
00515ead call 0x447f40
00515eb2 jmp 0x515fcb
00515eb7 cmp eax, 3
00515eba jne 0x515fcb
00515ec0 push 0xc02fec
00515ec5 lea ecx, [ebp - 0x40]
00515ec8 call 0x402120
00515ecd push eax
00515ece push 0xc02fec
00515ed3 mov edx, esi
00515ed5 mov ecx, 2
00515eda call 0x6aead0
00515edf add esp, 8
00515ee2 mov ecx, edi
00515ee4 mov dword ptr [eax + 0x2b0], 0xc1200000
00515eee mov dword ptr [esp], 0x3f800000
00515ef5 call 0x68d7b0
00515efa mov eax, dword ptr [0xbfd65c]
00515eff push 0x384
00515f04 mov esi, dword ptr [eax + 0x18190]
00515f0a lea eax, [edi + 0x294]
00515f10 push eax
00515f11 mov ecx, esi
00515f13 call 0x7ce950
00515f18 push eax
00515f19 mov ecx, esi
00515f1b call 0x447f40
00515f20 lea ecx, [ebp - 0x190]
00515f26 call 0x430d70
00515f2b mov eax, dword ptr [edi + 0xb10]
00515f31 mov byte ptr [ebp - 0xf8], 1
00515f38 mov dword ptr [ebp - 0x178], 0
00515f42 mov dword ptr [ebp - 0x184], 0xbd8f5c29
00515f4c cmp eax, 3
00515f4f ja 0x515fcb
00515f51 jmp dword ptr [eax*4 + 0x516ddc]
00515f58 lea eax, [ebp - 0x190]
00515f5e mov dword ptr [ebp - 0x240], 0x41000000
00515f68 push eax
00515f69 mov dword ptr [ebp - 0x23c], 0
00515f73 push 6
00515f75 jmp 0x515fb6
00515f77 mov dword ptr [ebp - 0x23c], 0x40c00000
00515f81 jmp 0x515fa3
00515f83 mov dword ptr [ebp - 0x240], 0x41000000
00515f8d mov dword ptr [ebp - 0x23c], 0x41000000
00515f97 jmp 0x515fad
00515f99 mov dword ptr [ebp - 0x23c], 0x41400000
00515fa3 mov dword ptr [ebp - 0x240], 0x41200000
00515fad lea eax, [ebp - 0x190]
00515fb3 push eax
00515fb4 push 9
00515fb6 lea eax, [ebp - 0x240]
00515fbc mov ecx, edi
00515fbe push eax
00515fbf lea eax, [edi + 0x294]
00515fc5 push eax
00515fc6 call 0x6a1a20
00515fcb cmp dword ptr [edi + 0x70], 0
00515fcf je 0x515ff8
00515fd1 push 0xb40338
00515fd6 lea ecx, [edi + 0x6c]
00515fd9 call 0x405f30
00515fde test al, al
00515fe0 je 0x515ff8
00515fe2 mov dword ptr [edi + 0x17c], 3
00515fec mov dword ptr [edi + 0x180], 2
00515ff6 jmp 0x51604c
00515ff8 movss xmm0, dword ptr [ebp - 0x260]
00516000 mulss xmm0, dword ptr [0xb6a2cc]
00516008 mov dword ptr [edi + 0x17c], 5
00516012 mov dword ptr [edi + 0x180], 4
0051601c movss dword ptr [ebp - 0x260], xmm0
00516024 movss dword ptr [ebp - 0x280], xmm0
0051602c movss xmm0, dword ptr [ebp - 0x254]
00516034 mulss xmm0, dword ptr [0xb6a2cc]
0051603c movss dword ptr [ebp - 0x254], xmm0
00516044 movss dword ptr [ebp - 0x27c], xmm0
0051604c cmp dword ptr [edi + 0x70], 0
00516050 je 0x51605b
00516052 cmp byte ptr [edi + 0x80], 0
00516059 jne 0x516075
0051605b mov esi, dword ptr [ebp - 0x244]
00516061 lea ecx, [edi + 0x3c]
00516064 push 0
00516066 push esi
00516067 call 0x4054f0
0051606c mov byte ptr [ebp - 0x248], 1
00516073 jmp 0x51607b
00516075 mov esi, dword ptr [ebp - 0x244]
0051607b cmp dword ptr [edi + 0x28], 0x348
00516082 jne 0x5160c2
00516084 cmp dword ptr [edi + 0x70], 0
00516088 je 0x5160c2
0051608a push 0xb4034c
0051608f lea ecx, [edi + 0x6c]
00516092 call 0x405f30
00516097 test al, al
00516099 je 0x5160c2
0051609b call 0x6c3d90
005160a0 xor edx, edx
005160a2 mov ecx, 3
005160a7 div ecx
005160a9 mov eax, dword ptr [ebp - 0x248]
005160af mov ecx, 1
005160b4 test edx, edx
005160b6 movzx eax, al
005160b9 cmovne eax, ecx
005160bc mov dword ptr [ebp - 0x248], eax
005160c2 movss xmm0, dword ptr [0xb6a974]
005160ca comiss xmm0, dword ptr [ebp - 0x29c]
005160d1 ja 0x51611c
005160d3 movss xmm1, dword ptr [edi + 0x2bc]
005160db movss xmm0, dword ptr [edi + 0x2b8]
005160e3 mulss xmm0, xmm0
005160e7 mulss xmm1, xmm1
005160eb addss xmm0, xmm1
005160ef call 0x4228c0
005160f4 movss xmm1, dword ptr [0xb6a53c]
005160fc comiss xmm1, xmm0
005160ff ja 0x51610a
00516101 cmp dword ptr [edi + 0x360], 0x1e
00516108 jle 0x516164
0051610a call 0x6c3d90
0051610f xor edx, edx
00516111 mov ecx, 0xa
00516116 div ecx
00516118 test edx, edx
0051611a jne 0x516164
0051611c cmp byte ptr [ebp - 0x248], 0
00516123 je 0x516164
00516125 movss xmm0, dword ptr [0xc02fec]
0051612d lea ecx, [edi + 0x3c]
00516130 movss dword ptr [edi + 0x28c], xmm0
00516138 movss xmm0, dword ptr [0xc02ff0]
00516140 push 0
00516142 movss dword ptr [edi + 0x290], xmm0
0051614a push esi
0051614b mov dword ptr [edi + 0xab4], 3
00516155 mov dword ptr [edi + 0x360], 0
0051615f call 0x4054f0
00516164 cmp dword ptr [edi + 0x28], 0x1d
00516168 jne 0x516263
0051616e cmp dword ptr [edi + 0x2c], 2
00516172 jne 0x5161d6
00516174 push 0xb4034c
00516179 lea ecx, [edi + 0x3c]
0051617c call 0x4060f0
00516181 test al, al
00516183 je 0x5161d6
00516185 call 0x6c3d90
0051618a xor edx, edx
0051618c mov ecx, 3
00516191 div ecx
00516193 test edx, edx
00516195 jne 0x5161d6
00516197 movss xmm0, dword ptr [0xc02fec]
0051619f movss dword ptr [edi + 0x28c], xmm0
005161a7 movss xmm0, dword ptr [0xc02ff0]
005161af movss dword ptr [edi + 0x290], xmm0
005161b7 push edx
005161b8 mov dword ptr [edi + 0xab4], ecx
005161be lea ecx, [edi + 0x3c]
005161c1 push esi
005161c2 mov dword ptr [edi + 0x360], 0x270f
005161cc call 0x4054f0
005161d1 jmp 0x516263
005161d6 cmp dword ptr [edi + 0x28], 0x1d
005161da jne 0x516263
005161e0 cmp dword ptr [edi + 0x2c], 3
005161e4 jne 0x516263
005161e6 push 0xb4034c
005161eb lea ecx, [edi + 0x3c]
005161ee call 0x4060f0
005161f3 test al, al
005161f5 je 0x516263
005161f7 mov eax, dword ptr [edi + 0xb10]
005161fd cmp eax, 3
00516200 jge 0x516259
00516202 inc eax
00516203 mov ecx, 0xb3fd8c
00516208 mov dword ptr [edi + 0xb10], eax
0051620e test al, 1
00516210 movss xmm0, dword ptr [0xc02fec]
00516218 mov eax, 0xb40218
0051621d movss dword ptr [edi + 0x28c], xmm0
00516225 cmove eax, ecx
00516228 movss xmm0, dword ptr [0xc02ff0]
00516230 lea ecx, [edi + 0x3c]
00516233 push 0
00516235 movss dword ptr [edi + 0x290], xmm0
0051623d push eax
0051623e mov dword ptr [edi + 0xab4], 3
00516248 mov dword ptr [edi + 0x360], 0x270f
00516252 call 0x4054f0
00516257 jmp 0x516263
00516259 mov dword ptr [edi + 0xb10], 0
00516263 movss xmm0, dword ptr [0xb6aa0c]
0051626b comiss xmm0, dword ptr [ebp - 0x29c]
00516272 movss xmm3, dword ptr [edi + 0x2c4]
0051627a jbe 0x5162eb
0051627c lea eax, [ebp - 0x2a0]
00516282 push eax
00516283 lea ecx, [ebp - 0x280]
00516289 call 0x962560
0051628e movss xmm2, dword ptr [edi + 0x2c4]
00516296 mov ecx, eax
00516298 movss xmm0, dword ptr [ebp - 0x264]
005162a0 ucomiss xmm2, xmm0
005162a3 lahf 
005162a4 test ah, 0x44
005162a7 jnp 0x51635c
005162ad movss xmm1, dword ptr [edi + 0x2f4]
005162b5 movaps xmm0, xmm1
005162b8 mulss xmm1, dword ptr [ecx + 4]
005162bd mulss xmm0, dword ptr [ecx]
005162c1 divss xmm1, xmm2
005162c5 divss xmm0, xmm2
005162c9 addss xmm1, dword ptr [edi + 0x2bc]
005162d1 addss xmm0, dword ptr [edi + 0x2b8]
005162d9 movss dword ptr [edi + 0x2bc], xmm1
005162e1 movss dword ptr [edi + 0x2b8], xmm0
005162e9 jmp 0x516354
005162eb movss xmm0, dword ptr [ebp - 0x264]
005162f3 movss xmm1, dword ptr [ebp - 0x260]
005162fb movss xmm2, dword ptr [ebp - 0x254]
00516303 mulss xmm1, dword ptr [0xb6a274]
0051630b mulss xmm2, dword ptr [0xb6a274]
00516313 ucomiss xmm3, xmm0
00516316 lahf 
00516317 test ah, 0x44
0051631a jnp 0x51635c
0051631c movss xmm0, dword ptr [edi + 0x2f4]
00516324 mulss xmm1, xmm0
00516328 mulss xmm2, xmm0
0051632c divss xmm1, xmm3
00516330 divss xmm2, xmm3
00516334 addss xmm1, dword ptr [edi + 0x2b8]
0051633c addss xmm2, dword ptr [edi + 0x2bc]
00516344 movss dword ptr [edi + 0x2b8], xmm1
0051634c movss dword ptr [edi + 0x2bc], xmm2
00516354 movss xmm0, dword ptr [ebp - 0x264]
0051635c cmp dword ptr [edi + 0x28], 0x131
00516363 jne 0x516375
00516365 comiss xmm0, dword ptr [edi + 0x2b8]
0051636c seta al
0051636f mov byte ptr [edi + 0x13c], al
00516375 cmp dword ptr [edi + 0x28], 0x22
00516379 jne 0x51648b
0051637f movss xmm0, dword ptr [edi + 0x28c]
00516387 lea esi, [edi + 0x28c]
0051638d ucomiss xmm0, dword ptr [0xc02fec]
00516394 lahf 
00516395 test ah, 0x44
00516398 jp 0x51648b
0051639e movss xmm0, dword ptr [esi + 4]
005163a3 ucomiss xmm0, dword ptr [0xc02ff0]
005163aa lahf 
005163ab test ah, 0x44
005163ae jp 0x51648b
005163b4 cmp dword ptr [edi + 0xe6c], -1
005163bb je 0x5163d3
005163bd movss xmm0, dword ptr [edi + 0xb0c]
005163c5 xor eax, eax
005163c7 comiss xmm0, dword ptr [ebp - 0x264]
005163ce seta al
005163d1 jmp 0x5163e8
005163d3 call 0x6c3d90
005163d8 xor edx, edx
005163da mov ecx, 7
005163df div ecx
005163e1 xor eax, eax
005163e3 test edx, edx
005163e5 sete al
005163e8 test eax, eax
005163ea je 0x51648b
005163f0 mov eax, dword ptr [edi + 0x160]
005163f6 and eax, 0x1000a00
005163fb or eax, 0
005163fe jne 0x51648b
00516404 movss xmm0, dword ptr [ebp - 0x2a8]
0051640c movss dword ptr [esi], xmm0
00516410 movss xmm0, dword ptr [ebp - 0x2a4]
00516418 movss dword ptr [esi + 4], xmm0
0051641d mov dword ptr [edi + 0xb0c], eax
00516423 mov eax, dword ptr [0xbfd65c]
00516428 push dword ptr [esi + 4]
0051642b push dword ptr [esi]
0051642d mov eax, dword ptr [eax + 0x18190]
00516433 mov ecx, eax
00516435 mov dword ptr [ebp - 0x27c], eax
0051643b call 0x7aee40
00516440 test eax, eax
00516442 je 0x51646d
00516444 push 0
00516446 push 0
00516448 push ecx
00516449 mov ecx, dword ptr [ebp - 0x27c]
0051644f lea eax, [ebp - 0x2a8]
00516455 mov dword ptr [esp], 0x42f00000
0051645c push esi
0051645d push eax
0051645e call 0x7cf240
00516463 mov ecx, dword ptr [eax]
00516465 mov dword ptr [esi], ecx
00516467 mov eax, dword ptr [eax + 4]
0051646a mov dword ptr [esi + 4], eax
0051646d mov dword ptr [edi + 0xb00], 0
00516477 mov dword ptr [edi + 0x360], 0
00516481 mov dword ptr [edi + 0xab4], 6
0051648b mov esi, dword ptr [edi + 0xab4]
00516491 cmp esi, 3
00516494 jne 0x5164a0
00516496 mov dword ptr [edi + 0x17c], 5
005164a0 cmp dword ptr [edi + 0x28], 0xf6
005164a7 jne 0x516686
005164ad cmp dword ptr [edi + 0x2c], 1
005164b1 jne 0x516686
005164b7 mov eax, dword ptr [0xbfd65c]
005164bc mov ecx, dword ptr [eax + 0x18190]
005164c2 lea eax, [edi + 0x294]
005164c8 push eax
005164c9 mov dword ptr [ebp - 0x260], ecx
005164cf call 0x7ce950
005164d4 mov ecx, dword ptr [ebp - 0x260]
005164da cmp eax, 0x1bf
005164df ja 0x5164ee
005164e1 cmp dword ptr [ecx + eax*4 + 0x76c], 0x1f4
005164ec jge 0x51651b
005164ee lea eax, [edi + 0x294]
005164f4 push eax
005164f5 call 0x7ce950
005164fa mov ecx, eax
005164fc cmp ecx, 0x1bf
00516502 ja 0x51651b
00516504 mov eax, dword ptr [ebp - 0x260]
0051650a mov dword ptr [eax + ecx*4 + 0x76c], 0x1f4
00516515 mov esi, dword ptr [edi + 0xab4]
0051651b cmp esi, 0x10
0051651e jne 0x516561
00516520 cmp dword ptr [edi + 0x314], 0
00516527 jne 0x516686
0051652d call 0x6c3d90
00516532 mov ecx, dword ptr [0xbfd65c]
00516538 lea esi, [edi + 0x294]
0051653e push eax
0051653f push 0
00516541 push 0
00516543 push 0xc02fec
00516548 push esi
00516549 push 0xf
0051654b push 0x3e8
00516550 call 0x422e20
00516555 mov eax, dword ptr [edi]
00516557 mov ecx, edi
00516559 call dword ptr [eax + 0x28]
0051655c jmp 0x51668c
00516561 cmp byte ptr [edi + 0x16b], 0
00516568 je 0x516612
0051656e cmp dword ptr [edi + 0x314], 0
00516575 je 0x516612
0051657b movss xmm0, dword ptr [edi + 0x2c4]
00516583 mov ecx, edi
00516585 mulss xmm0, dword ptr [0xb6a3b0]
0051658d mov eax, dword ptr [edi + 0x2dc]
00516593 mov byte ptr [edi + 0x16b], 0
0051659a mov dword ptr [edi + 0x2d8], eax
005165a0 mov dword ptr [edi + 0xab4], 0x10
005165aa mov byte ptr [edi + 0x308], 1
005165b1 mov dword ptr [edi + 0x180], 0
005165bb mov dword ptr [edi + 0x17c], 5
005165c5 movss dword ptr [edi + 0x2c4], xmm0
005165cd call 0x685ef0
005165d2 push 0xc02fec
005165d7 lea eax, [edi + 0x1dc]
005165dd mov dword ptr [ebp - 0x298], 0
005165e7 push eax
005165e8 lea eax, [ebp - 0x298]
005165ee mov dword ptr [ebp - 0x294], 0xc0a00000
005165f8 push eax
005165f9 lea edx, [edi + 0x294]
005165ff mov ecx, 3
00516604 call 0x6aead0
00516609 mov esi, dword ptr [edi + 0xab4]
0051660f add esp, 0xc
00516612 cmp esi, 2
00516615 jne 0x516672
00516617 push 0
00516619 push 0xb42990
0051661e lea ecx, [edi + 0x3c]
00516621 call 0x4054f0
00516626 cmp dword ptr [edi + 0x70], 0
0051662a je 0x516635
0051662c cmp byte ptr [edi + 0x80], 0
00516633 jne 0x516686
00516635 mov byte ptr [edi + 0x308], 0
0051663c mov dword ptr [edi + 0xab4], 3
00516646 movss xmm0, dword ptr [0xc02fec]
0051664e movss dword ptr [edi + 0x28c], xmm0
00516656 movss xmm0, dword ptr [0xc02ff0]
0051665e movss dword ptr [edi + 0x290], xmm0
00516666 mov dword ptr [edi + 0x180], 4
00516670 jmp 0x516686
00516672 cmp esi, 0x10
00516675 jne 0x516686
00516677 push 0
00516679 push 0xb43120
0051667e lea ecx, [edi + 0x3c]
00516681 call 0x4054f0
00516686 lea esi, [edi + 0x294]
0051668c cmp dword ptr [edi + 0xab4], 3
00516693 jne 0x5166df
00516695 movss xmm0, dword ptr [edi + 0x28c]
0051669d ucomiss xmm0, dword ptr [0xc02fec]
005166a4 lahf 
005166a5 test ah, 0x44
005166a8 jp 0x5166bf
005166aa movss xmm0, dword ptr [edi + 0x290]
005166b2 ucomiss xmm0, dword ptr [0xc02ff0]
005166b9 lahf 
005166ba test ah, 0x44
005166bd jnp 0x5166df
005166bf movss xmm0, dword ptr [0xc02fec]
005166c7 movss dword ptr [edi + 0x28c], xmm0
005166cf movss xmm0, dword ptr [0xc02ff0]
005166d7 movss dword ptr [edi + 0x290], xmm0
005166df cmp dword ptr [edi + 0x28], 0x1d
005166e3 jne 0x516d8c
005166e9 cmp dword ptr [edi + 0x2c], 2
005166ed jne 0x516d8c
005166f3 cmp dword ptr [edi + 0xab4], 5
005166fa jne 0x516d20
00516700 mov dword ptr [edi + 0x180], 0
0051670a movss xmm1, dword ptr [edi + 0x28c]
00516712 movss xmm0, dword ptr [edi + 0x290]
0051671a subss xmm1, dword ptr [esi]
0051671e subss xmm0, dword ptr [esi + 4]
00516723 movss dword ptr [edi + 0x2b8], xmm1
0051672b movss dword ptr [edi + 0x2bc], xmm0
00516733 cmp dword ptr [edi + 0x70], 0
00516737 je 0x516796
00516739 push 0xb40338
0051673e lea ecx, [edi + 0x6c]
00516741 call 0x405e90
00516746 test al, al
00516748 je 0x516796
0051674a push ecx
0051674b mov dword ptr [esp], 0x3f800000
00516752 push 0
00516754 push 2
00516756 push ecx
00516757 mov dword ptr [esp], 0x3f800000
0051675e mov ecx, edi
00516760 push 0xed
00516765 call 0x6ad720
0051676a push ecx
0051676b mov dword ptr [esp], 0x3f800000
00516772 push 0
00516774 push 2
00516776 push ecx
00516777 mov dword ptr [esp], 0x3f800000
0051677e mov ecx, edi
00516780 push 0xb5
00516785 call 0x6ad720
0051678a mov dword ptr [edi + 0x360], 0
00516794 jmp 0x5167a3
00516796 cmp dword ptr [edi + 0x360], 0
0051679d jl 0x516d0a
005167a3 cvttss2si edx, dword ptr [edi + 0x2fc]
005167ab cvttss2si eax, dword ptr [edi + 0x2f8]
005167b3 sub edx, eax
005167b5 mov dword ptr [ebp - 0x250], edx
005167bb test edx, edx
005167bd jle 0x516d0a
005167c3 mov esi, 6
005167c8 nop dword ptr [eax + eax]
005167d0 mov ecx, dword ptr [edi + 0x360]
005167d6 inc ecx
005167d7 mov dword ptr [edi + 0x360], ecx
005167dd mov eax, ecx
005167df cmp ecx, 0xe
005167e2 jg 0x5167f2
005167e4 cdq 
005167e5 idiv dword ptr [ebp - 0x2ac]
005167eb cmp edx, 2
005167ee je 0x516824
005167f0 jmp 0x5167f9
005167f2 mov ecx, eax
005167f4 cmp eax, 0x1f
005167f7 jg 0x516809
005167f9 mov eax, ecx
005167fb cdq 
005167fc idiv esi
005167fe cmp edx, 1
00516801 je 0x516824
00516803 mov edx, dword ptr [ebp - 0x250]
00516809 cmp ecx, 0x3c
0051680c jg 0x516cf5
00516812 mov eax, ecx
00516814 mov ecx, 0xf
00516819 cdq 
0051681a idiv ecx
0051681c test edx, edx
0051681e jne 0x516cef
00516824 movzx eax, word ptr [edi + 0xbc6]
0051682b test ax, ax
0051682e jle 0x516851
00516830 cwde 
00516831 mov esi, 3
00516836 inc eax
00516837 cmp eax, esi
00516839 cmovl esi, eax
0051683c test esi, esi
0051683e je 0x516851
00516840 call 0x6c3d90
00516845 xor edx, edx
00516847 div esi
00516849 test edx, edx
0051684b jne 0x516cea
00516851 call 0x6c3d90
00516856 movd xmm0, eax
0051685a cvtdq2pd xmm0, xmm0
0051685e shr eax, 0x1f
00516861 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
0051686a cvtpd2ps xmm0, xmm0
0051686e mulss xmm0, dword ptr [0xb6a19c]
00516876 mulss xmm0, dword ptr [0xb6a874]
0051687e addss xmm0, xmm0
00516882 movss dword ptr [ebp - 0x27c], xmm0
0051688a call 0x412010
0051688f movss dword ptr [ebp - 0x29c], xmm0
00516897 movss xmm0, dword ptr [ebp - 0x27c]
0051689f call 0x411fe0
005168a4 movss xmm1, dword ptr [ebp - 0x29c]
005168ac lea ecx, [edi + 0x334]
005168b2 addss xmm0, dword ptr [edi + 0x294]
005168ba addss xmm1, dword ptr [edi + 0x298]
005168c2 movss dword ptr [ebp - 0x298], xmm0
005168ca movss dword ptr [ebp - 0x294], xmm1
005168d2 call 0x7a7e20
005168d7 mov ecx, dword ptr [0xbfd65c]
005168dd push eax
005168de push 0
005168e0 push edi
005168e1 push 0xc02fec
005168e6 lea eax, [ebp - 0x298]
005168ec push eax
005168ed push 0
005168ef push 0x374
005168f4 call 0x422e20
005168f9 mov esi, eax
005168fb mov dword ptr [ebp - 0x25c], 0
00516905 mov dword ptr [ebp - 0x258], 0
0051690f mov dword ptr [ebp - 0x254], 0
00516919 mov ecx, dword ptr [esi + 0x164]
0051691f or dword ptr [esi + 0x160], 0x40000000
00516929 mov dword ptr [esi + 0x164], ecx
0051692f lea eax, [ebp - 0x288]
00516935 mov dword ptr [ebp - 4], 0
0051693c push eax
0051693d push 0
0051693f lea ecx, [ebp - 0x25c]
00516945 mov dword ptr [ebp - 0x288], 0
0051694f mov dword ptr [ebp - 0x284], 3
00516959 call 0x48d900
0051695e mov edx, dword ptr [ebp - 0x258]
00516964 xor eax, eax
00516966 mov ecx, dword ptr [ebp - 0x25c]
0051696c mov dword ptr [ebp - 0x248], edx
00516972 sub dword ptr [ebp - 0x248], ecx
00516978 sar dword ptr [ebp - 0x248], 3
0051697f cmp dword ptr [ebp - 0x248], eax
00516985 jbe 0x516996
00516987 cmp dword ptr [ecx + eax*8], 1
0051698b je 0x5169ca
0051698d inc eax
0051698e cmp eax, dword ptr [ebp - 0x248]
00516994 jb 0x516987
00516996 mov dword ptr [ebp - 0x2a8], 1
005169a0 mov dword ptr [ebp - 0x2a4], 2
005169aa cmp edx, dword ptr [ebp - 0x254]
005169b0 je 0x5169db
005169b2 mov dword ptr [edx], 1
005169b8 mov dword ptr [edx + 4], 2
005169bf add edx, 8
005169c2 mov dword ptr [ebp - 0x258], edx
005169c8 jmp 0x5169fa
005169ca add dword ptr [ecx + eax*8 + 4], 2
005169cf jns 0x5169fa
005169d1 mov dword ptr [ecx + eax*8 + 4], 0
005169d9 jmp 0x5169fa
005169db lea eax, [ebp - 0x2a8]
005169e1 push eax
005169e2 push edx
005169e3 lea ecx, [ebp - 0x25c]
005169e9 call 0x48d900
005169ee mov edx, dword ptr [ebp - 0x258]
005169f4 mov ecx, dword ptr [ebp - 0x25c]
005169fa mov dword ptr [ebp - 0x248], edx
00516a00 xor eax, eax
00516a02 sub dword ptr [ebp - 0x248], ecx
00516a08 sar dword ptr [ebp - 0x248], 3
00516a0f cmp dword ptr [ebp - 0x248], eax
00516a15 jbe 0x516a26
00516a17 cmp dword ptr [ecx + eax*8], 2
00516a1b je 0x516a5a
00516a1d inc eax
00516a1e cmp eax, dword ptr [ebp - 0x248]
00516a24 jb 0x516a17
00516a26 mov dword ptr [ebp - 0x240], 2
00516a30 mov dword ptr [ebp - 0x23c], 1
00516a3a cmp edx, dword ptr [ebp - 0x254]
00516a40 je 0x516a6b
00516a42 mov dword ptr [edx], 2
00516a48 mov dword ptr [edx + 4], 1
00516a4f add edx, 8
00516a52 mov dword ptr [ebp - 0x258], edx
00516a58 jmp 0x516a7e
00516a5a add dword ptr [ecx + eax*8 + 4], 1
00516a5f jns 0x516a7e
00516a61 mov dword ptr [ecx + eax*8 + 4], 0
00516a69 jmp 0x516a7e
00516a6b lea eax, [ebp - 0x240]
00516a71 push eax
00516a72 push edx
00516a73 lea ecx, [ebp - 0x25c]
00516a79 call 0x48d900
00516a7e call 0x6c3d90
00516a83 movd xmm0, eax
00516a87 cvtdq2pd xmm0, xmm0
00516a8b shr eax, 0x1f
00516a8e addsd xmm0, qword ptr [eax*8 + 0xb6c940]
00516a97 cvtpd2ps xmm0, xmm0
00516a9b mulss xmm0, dword ptr [0xb6a19c]
00516aa3 mulss xmm0, dword ptr [0xb6a874]
00516aab addss xmm0, xmm0
00516aaf movss dword ptr [ebp - 0x27c], xmm0
00516ab7 call 0x412010
00516abc movss dword ptr [ebp - 0x28c], xmm0
00516ac4 movss xmm0, dword ptr [ebp - 0x27c]
00516acc call 0x411fe0
00516ad1 movss dword ptr [ebp - 0x244], xmm0
00516ad9 call 0x6c3d90
00516ade movq xmm0, qword ptr [0xa08c44]
00516ae6 lea ecx, [ebp - 0x25c]
00516aec or eax, 1
00516aef movq qword ptr [ebp - 0x274], xmm0
00516af7 mov dword ptr [ebp - 0x278], eax
00516afd sub esp, 0x10
00516b00 mov eax, dword ptr [0xa08c4c]
00516b05 mov dword ptr [ebp - 0x26c], eax
00516b0b mov eax, esp
00516b0d movups xmm0, xmmword ptr [ebp - 0x278]
00516b14 movups xmmword ptr [eax], xmm0
00516b17 call 0x489420
00516b1c sub eax, 0
00516b1f je 0x516c18
00516b25 sub eax, 1
00516b28 je 0x516ba8
00516b2a sub eax, 1
00516b2d jne 0x516c6f
00516b33 push eax
00516b34 push 0xb43110
00516b39 lea ecx, [esi + 0x3c]
00516b3c call 0x4054f0
00516b41 cmp dword ptr [esi + 0x70], 0
00516b45 je 0x516b57
00516b47 movss xmm1, dword ptr [0xb6a910]
00516b4f lea ecx, [esi + 0x6c]
00516b52 call 0x403c00
00516b57 call 0x6c3d90
00516b5c movd xmm0, eax
00516b60 cvtdq2pd xmm0, xmm0
00516b64 shr eax, 0x1f
00516b67 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
00516b70 cvtpd2ps xmm1, xmm0
00516b74 mulss xmm1, dword ptr [0xb6a19c]
00516b7c mulss xmm1, dword ptr [0xb6a864]
00516b84 addss xmm1, dword ptr [0xb6a974]
00516b8c movss xmm2, dword ptr [ebp - 0x244]
00516b94 movaps xmm0, xmm1
00516b97 mulss xmm1, dword ptr [ebp - 0x28c]
00516b9f mulss xmm2, xmm0
00516ba3 jmp 0x516c7f
00516ba8 push 0
00516baa push 0xb405cc
00516baf lea ecx, [esi + 0x3c]
00516bb2 call 0x4054f0
00516bb7 cmp dword ptr [esi + 0x70], 0
00516bbb je 0x516bcd
00516bbd movss xmm1, dword ptr [0xb6a8f4]
00516bc5 lea ecx, [esi + 0x6c]
00516bc8 call 0x403c00
00516bcd call 0x6c3d90
00516bd2 movss xmm2, dword ptr [ebp - 0x244]
00516bda movss xmm1, dword ptr [ebp - 0x28c]
00516be2 movd xmm0, eax
00516be6 cvtdq2pd xmm0, xmm0
00516bea shr eax, 0x1f
00516bed addsd xmm0, qword ptr [eax*8 + 0xb6c940]
00516bf6 cvtpd2ps xmm0, xmm0
00516bfa mulss xmm0, dword ptr [0xb6a19c]
00516c02 addss xmm0, xmm0
00516c06 addss xmm0, dword ptr [0xb6a940]
00516c0e mulss xmm2, xmm0
00516c12 mulss xmm1, xmm0
00516c16 jmp 0x516c7f
00516c18 push 0
00516c1a push 0xb43124
00516c1f lea ecx, [esi + 0x3c]
00516c22 call 0x4054f0
00516c27 cmp dword ptr [esi + 0x70], 0
00516c2b je 0x516c3d
00516c2d movss xmm1, dword ptr [0xb6a8cc]
00516c35 lea ecx, [esi + 0x6c]
00516c38 call 0x403c00
00516c3d call 0x6c3d90
00516c42 movd xmm0, eax
00516c46 cvtdq2pd xmm0, xmm0
00516c4a shr eax, 0x1f
00516c4d addsd xmm0, qword ptr [eax*8 + 0xb6c940]
00516c56 cvtpd2ps xmm1, xmm0
00516c5a mulss xmm1, dword ptr [0xb6a19c]
00516c62 addss xmm1, dword ptr [0xb6a8f4]
00516c6a jmp 0x516b8c
00516c6f movss xmm2, dword ptr [ebp - 0x244]
00516c77 movss xmm1, dword ptr [ebp - 0x28c]
00516c7f mov dword ptr [ebp - 4], 0xffffffff
00516c86 mov ecx, dword ptr [ebp - 0x25c]
00516c8c movss dword ptr [esi + 0x28c], xmm2
00516c94 movss dword ptr [esi + 0x290], xmm1
00516c9c mov dword ptr [esi + 0xab4], 6
00516ca6 movss dword ptr [esi + 0x2b8], xmm2
00516cae movss dword ptr [esi + 0x2bc], xmm1
00516cb6 test ecx, ecx
00516cb8 je 0x516cea
00516cba mov eax, dword ptr [ebp - 0x254]
00516cc0 sub eax, ecx
00516cc2 sar eax, 3
00516cc5 push eax
00516cc6 push ecx
00516cc7 call 0x421f90
00516ccc mov dword ptr [ebp - 0x25c], 0
00516cd6 mov dword ptr [ebp - 0x258], 0
00516ce0 mov dword ptr [ebp - 0x254], 0
00516cea mov esi, 6
00516cef mov edx, dword ptr [ebp - 0x250]
00516cf5 sub edx, 1
00516cf8 mov dword ptr [ebp - 0x250], edx
00516cfe jne 0x5167d0
00516d04 lea esi, [edi + 0x294]
00516d0a cmp dword ptr [edi + 0x70], 0
00516d0e je 0x516d19
00516d10 cmp byte ptr [edi + 0x80], 0
00516d17 jne 0x516d20
00516d19 mov eax, dword ptr [edi]
00516d1b mov ecx, edi
00516d1d call dword ptr [eax + 0x24]
00516d20 cmp byte ptr [edi + 0x16b], 0
00516d27 je 0x516d8c
00516d29 mov eax, dword ptr [edi + 0xab4]
00516d2f cmp eax, 5
00516d32 je 0x516d8c
00516d34 cmp eax, 0x12
00516d37 je 0x516d8c
00516d39 push 0
00516d3b push 0xb43120
00516d40 lea ecx, [edi + 0x3c]
00516d43 call 0x4054f0
00516d48 mov ecx, edi
00516d4a mov dword ptr [edi + 0xab4], 5
00516d54 call 0x685ef0
00516d59 mov dword ptr [edi + 0x360], 0xffffffff
00516d63 mov byte ptr [edi + 0x308], 1
00516d6a mov byte ptr [edi + 0x16b], 0
00516d71 mov dword ptr [edi + 0x2d8], 0x3dcccccd
00516d7b mov eax, dword ptr [esi]
00516d7d mov dword ptr [edi + 0x28c], eax
00516d83 mov eax, dword ptr [esi + 4]
00516d86 mov dword ptr [edi + 0x290], eax
00516d8c cvttss2si ecx, dword ptr [edi + 0x2fc]
00516d94 cvttss2si eax, dword ptr [edi + 0x2f8]
00516d9c movss xmm0, dword ptr [edi + 0x2c4]
00516da4 mulss xmm0, dword ptr [0xb6a50c]
00516dac sub ecx, eax
00516dae add dword ptr [edi + 0x360], ecx
00516db4 movss dword ptr [edi + 0x2c4], xmm0
00516dbc mov ecx, dword ptr [ebp - 0xc]
00516dbf mov dword ptr fs:[0], ecx
00516dc6 pop ecx
00516dc7 pop edi
00516dc8 pop esi
00516dc9 mov ecx, dword ptr [ebp - 0x14]
00516dcc xor ecx, ebp
00516dce call 0x9eacd7
00516dd3 mov esp, ebp
00516dd5 pop ebp
00516dd6 mov esp, ebx
00516dd8 pop ebx
00516dd9 ret 
00516dda nop 
00516ddc pop eax
00516ddd pop edi
00516dde push ecx
00516ddf add byte ptr [edi + 0x5f], dh
00516de2 push ecx
00516de3 add byte ptr [ebx - 0x66ffaea1], al
00516de9 pop edi
00516dea push ecx
00516deb add ah, cl
