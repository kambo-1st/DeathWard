00545510 push ebp
00545511 mov ebp, esp
00545513 and esp, 0xfffffff8
00545516 sub esp, 0x124
0054551c mov eax, dword ptr [0xbaa3b4]
00545521 xor eax, esp
00545523 mov dword ptr [esp + 0x120], eax
0054552a push ebx
0054552b push esi
0054552c push edi
0054552d mov edi, ecx
0054552f mov dword ptr [esp + 0x30], edi
00545533 cvttss2si esi, dword ptr [edi + 0x2fc]
0054553b mov ecx, dword ptr [edi + 0xaf0]
00545541 cvttss2si eax, dword ptr [edi + 0x2f8]
00545549 sub esi, eax
0054554b test ecx, ecx
0054554d jle 0x54555e
0054554f sub ecx, esi
00545551 xor eax, eax
00545553 test ecx, ecx
00545555 cmovg eax, ecx
00545558 mov dword ptr [edi + 0xaf0], eax
0054555e mov eax, dword ptr [edi + 0xab4]
00545564 cmp eax, 0xd
00545567 ja 0x546459
0054556d jmp dword ptr [eax*4 + 0x546480]
00545574 mov eax, dword ptr [edi + 0x160]
0054557a mov ecx, edi
0054557c or dword ptr [edi + 0x164], 0x2000
00545586 mov dword ptr [edi + 0xb00], 0x42f00000
00545590 mov dword ptr [edi + 0xb04], 0x3f800000
0054559a mov dword ptr [edi + 0xaf4], 0x28
005455a4 mov dword ptr [edi + 0x160], eax
005455aa call 0x544b70
005455af mov eax, dword ptr [0xbfd65c]
005455b4 mov ecx, dword ptr [eax + 0x18190]
005455ba cmp byte ptr [ecx], 0
005455bd je 0x5456d5
005455c3 mov eax, dword ptr [eax + 0x1a30dc]
005455c9 sub eax, dword ptr [ecx + 0x11f0]
005455cf jne 0x5456d5
005455d5 push -1
005455d7 push 0x328
005455dc lea eax, [esp + 0x3c]
005455e0 mov ecx, edi
005455e2 push eax
005455e3 call 0x6a6db0
005455e8 xor ebx, ebx
005455ea cmp dword ptr [esp + 0x40], ebx
005455ee jbe 0x5456c2
005455f4 mov edi, dword ptr [esp + 0x38]
005455f8 nop dword ptr [eax + eax]
00545600 mov esi, dword ptr [edi + ebx*4]
00545603 lea eax, [esp + 0x1c]
00545607 push 0
00545609 push eax
0054560a mov ecx, esi
0054560c call 0x544ec0
00545611 push 0xc
00545613 lea eax, [esp + 0x48]
00545617 mov ecx, esi
00545619 push eax
0054561a call 0x544dc0
0054561f movss xmm1, dword ptr [eax]
00545623 subss xmm1, dword ptr [esp + 0x1c]
00545629 movss xmm2, dword ptr [eax + 4]
0054562e subss xmm2, dword ptr [esp + 0x20]
00545634 movaps xmm0, xmm1
00545637 movss dword ptr [esp + 0x10], xmm1
0054563d mulss xmm0, xmm1
00545641 movaps xmm1, xmm2
00545644 movss dword ptr [esp + 0xc], xmm2
0054564a mulss xmm1, xmm2
0054564e addss xmm0, xmm1
00545652 call 0x4228c0
00545657 movss xmm2, dword ptr [esp + 0x10]
0054565d xorps xmm1, xmm1
00545660 comiss xmm0, xmm1
00545663 movss xmm3, dword ptr [esp + 0xc]
00545669 jbe 0x54567f
0054566b movss xmm1, dword ptr [0xb6a614]
00545673 divss xmm1, xmm0
00545677 mulss xmm2, xmm1
0054567b mulss xmm3, xmm1
0054567f movss xmm0, dword ptr [esi + 0xb00]
00545687 inc ebx
00545688 mulss xmm0, dword ptr [0xb6a660]
00545690 mulss xmm2, xmm0
00545694 mulss xmm3, xmm0
00545698 addss xmm2, dword ptr [esp + 0x1c]
0054569e addss xmm3, dword ptr [esp + 0x20]
005456a4 movss dword ptr [esi + 0x294], xmm2
005456ac movss dword ptr [esi + 0x298], xmm3
005456b4 cmp ebx, dword ptr [esp + 0x40]
005456b8 jb 0x545600
005456be mov edi, dword ptr [esp + 0x30]
005456c2 cmp byte ptr [esp + 0x34], 0
005456c7 jne 0x5456d5
005456c9 push dword ptr [esp + 0x38]
005456cd call 0x9eace5
005456d2 add esp, 4
005456d5 mov dword ptr [edi + 0xab4], 3
005456df jmp 0x546459
005456e4 push 0
005456e6 push 0xb405b4
005456eb lea ecx, [edi + 0x3c]
005456ee call 0x4054f0
005456f3 mov ecx, edi
005456f5 call 0x545000
005456fa mov ecx, dword ptr [edi + 0xaf4]
00545700 cmp ecx, 1
00545703 jle 0x545717
00545705 sub ecx, esi
00545707 mov eax, 1
0054570c cmp ecx, eax
0054570e cmovg eax, ecx
00545711 mov dword ptr [edi + 0xaf4], eax
00545717 call 0x6c3d90
0054571c xor edx, edx
0054571e mov ecx, 9
00545723 div ecx
00545725 test edx, edx
00545727 jne 0x546459
0054572d cmp dword ptr [edi + 0x30], 1
00545731 je 0x545827
00545737 cmp dword ptr [edi + 0xaf0], edx
0054573d jg 0x546459
00545743 xorps xmm0, xmm0
00545746 comiss xmm0, dword ptr [edi + 0x2a8]
0054574d ja 0x546459
00545753 push edx
00545754 lea eax, [esp + 0x20]
00545758 mov ecx, edi
0054575a push eax
0054575b call 0x544dc0
00545760 movss xmm1, dword ptr [edi + 0x294]
00545768 lea ecx, [edi + 0x294]
0054576e movss xmm0, dword ptr [ecx + 4]
00545773 subss xmm0, dword ptr [eax + 4]
00545778 subss xmm1, dword ptr [eax]
0054577c mulss xmm0, xmm0
00545780 mulss xmm1, xmm1
00545784 addss xmm0, xmm1
00545788 comiss xmm0, dword ptr [0xb6ac60]
0054578f ja 0x546459
00545795 push ecx
00545796 mov dword ptr [esp], 0
0054579d push ecx
0054579e mov ecx, dword ptr [0xbfd65c]
005457a4 mov ecx, dword ptr [ecx + 0x18190]
005457aa call 0x7cf0a0
005457af test al, al
005457b1 je 0x546459
005457b7 push 0
005457b9 push 0x1000a00
005457be mov ecx, edi
005457c0 call 0x4122f0
005457c5 test al, al
005457c7 jne 0x546459
005457cd push -1
005457cf push 0x328
005457d4 lea eax, [esp + 0x4c]
005457d8 mov ecx, edi
005457da push eax
005457db call 0x6a6db0
005457e0 mov esi, dword ptr [esp + 0x50]
005457e4 xor eax, eax
005457e6 mov edx, dword ptr [esp + 0x48]
005457ea test esi, esi
005457ec je 0x545817
005457ee nop 
005457f0 mov ecx, dword ptr [edx + eax*4]
005457f3 cmp dword ptr [ecx + 0x30], 0
005457f7 jne 0x545812
005457f9 cmp byte ptr [ecx + 0x16b], 0
00545800 jne 0x545812
00545802 mov ecx, dword ptr [ecx + 0xab4]
00545808 cmp ecx, 8
0054580b je 0x545842
0054580d cmp ecx, 9
00545810 je 0x545842
00545812 inc eax
00545813 cmp eax, esi
00545815 jb 0x5457f0
00545817 cmp byte ptr [esp + 0x44], 0
0054581c jne 0x545827
0054581e push edx
0054581f call 0x9eace5
00545824 add esp, 4
00545827 mov eax, dword ptr [edi + 0xb08]
0054582d mov dword ptr [edi + 0xab4], 8
00545837 mov dword ptr [edi + 0xb0c], eax
0054583d jmp 0x546459
00545842 cmp byte ptr [esp + 0x44], 0
00545847 jne 0x546459
0054584d push edx
0054584e call 0x9eace5
00545853 add esp, 4
00545856 jmp 0x546459
0054585b push 0
0054585d push 0xb40510
00545862 lea ecx, [edi + 0x3c]
00545865 call 0x4054f0
0054586a mov ecx, edi
0054586c call 0x545220
00545871 mov ecx, edi
00545873 call 0x545000
00545878 jmp 0x546459
0054587d mov ecx, edi
0054587f call 0x545220
00545884 movss xmm0, dword ptr [edi + 0x28c]
0054588c mov eax, dword ptr [edi + 0x28c]
00545892 mulss xmm0, dword ptr [0xb6a5a4]
0054589a mov dword ptr [edi + 0x2b8], eax
005458a0 mov eax, dword ptr [edi + 0x290]
005458a6 mov dword ptr [edi + 0x2bc], eax
005458ac movss dword ptr [edi + 0x28c], xmm0
005458b4 movss xmm0, dword ptr [edi + 0x290]
005458bc mulss xmm0, dword ptr [0xb6a5a4]
005458c4 movss dword ptr [edi + 0x290], xmm0
005458cc jmp 0x546459
005458d1 mov ecx, edi
005458d3 call 0x545000
005458d8 mov esi, dword ptr [edi + 0x360]
005458de lea ecx, [esp + 0x28]
005458e2 movss xmm1, dword ptr [0xb6a614]
005458ea xorps xmm2, xmm2
005458ed mov dword ptr [esp + 0x14], 0
005458f5 lea eax, [esi + 1]
005458f8 movd xmm0, eax
005458fc cvtdq2ps xmm0, xmm0
005458ff mov dword ptr [edi + 0x360], eax
00545905 lea eax, [esp + 0x14]
00545909 subss xmm0, xmm2
0054590d mulss xmm0, dword ptr [0xb6a280]
00545915 comiss xmm2, xmm0
00545918 movss dword ptr [esp + 0x28], xmm0
0054591e cmovbe eax, ecx
00545921 movss xmm0, dword ptr [eax]
00545925 comiss xmm0, xmm1
00545928 ja 0x545930
0054592a movss xmm0, xmm0
0054592e jmp 0x545934
00545930 movss xmm0, xmm1
00545934 mulss xmm0, dword ptr [0xb6a874]
0054593c addss xmm0, xmm2
00545940 call 0x412010
00545945 mulss xmm0, dword ptr [0xb6a560]
0054594d addss xmm0, dword ptr [0xb6a614]
00545955 movss dword ptr [edi + 0xb04], xmm0
0054595d cmp esi, 2
00545960 je 0x545970
00545962 cmp esi, 5
00545965 je 0x545970
00545967 cmp esi, 8
0054596a jne 0x545a5a
00545970 push ecx
00545971 mov dword ptr [esp], 0x3f800000
00545978 push 0
0054597a push 2
0054597c push ecx
0054597d mov dword ptr [esp], 0x3f800000
00545984 mov ecx, edi
00545986 push 0x99
0054598b call 0x6ad720
00545990 push 0
00545992 lea eax, [esp + 0x38]
00545996 mov ecx, edi
00545998 push eax
00545999 call 0x544ec0
0054599e mov esi, eax
005459a0 mov ecx, edi
005459a2 push 0
005459a4 lea eax, [esp + 0x18]
005459a8 push eax
005459a9 call 0x544dc0
005459ae lea ecx, [esp + 0x1c]
005459b2 movss xmm0, dword ptr [eax]
005459b6 subss xmm0, dword ptr [esi]
005459ba movss dword ptr [esp + 0x1c], xmm0
005459c0 movss xmm0, dword ptr [eax + 4]
005459c5 lea eax, [esp + 0x28]
005459c9 subss xmm0, dword ptr [esi + 4]
005459ce push eax
005459cf movss dword ptr [esp + 0x24], xmm0
005459d5 call 0x962560
005459da lea ecx, [esp + 0x80]
005459e1 movss xmm2, dword ptr [eax + 4]
005459e6 movss xmm0, dword ptr [eax]
005459ea mulss xmm0, dword ptr [0xb6a940]
005459f2 mulss xmm2, dword ptr [0xb6a940]
005459fa movss dword ptr [esp + 0x44], xmm0
00545a00 movss dword ptr [esp + 0x48], xmm2
00545a06 call 0x430d70
00545a0b push 0xbc4140
00545a10 lea ecx, [esp + 0xb0]
00545a17 call 0x4021a0
00545a1c lea eax, [esp + 0x80]
00545a23 mov dword ptr [esp + 0x114], 4
00545a2e push eax
00545a2f push 0
00545a31 lea eax, [esp + 0x4c]
00545a35 mov dword ptr [esp + 0xe0], 0x2000
00545a40 push eax
00545a41 lea eax, [edi + 0x294]
00545a47 mov dword ptr [esp + 0xe8], 0
00545a52 push eax
00545a53 mov ecx, edi
00545a55 call 0x6a1a20
00545a5a cmp dword ptr [edi + 0x70], 0
00545a5e je 0x545a6d
00545a60 cmp byte ptr [edi + 0x80], 0
00545a67 jne 0x546459
00545a6d mov dword ptr [edi + 0xb04], 0x3f800000
00545a77 mov dword ptr [edi + 0xab4], 3
00545a81 jmp 0x546459
00545a86 push 0
00545a88 push 0xb43588
00545a8d lea ecx, [edi + 0x3c]
00545a90 call 0x4054f0
00545a95 mov ecx, edi
00545a97 mov dword ptr [edi + 0x180], 0
00545aa1 call 0x545000
00545aa6 lea ecx, [edi + 0x3c]
00545aa9 call 0x4058f0
00545aae cmp eax, 1
00545ab1 jne 0x545d89
00545ab7 mov esi, dword ptr [0xbfd65c]
00545abd lea ebx, [edi + 0x294]
00545ac3 mov dword ptr [esp + 0x44], ebx
00545ac7 call 0x6c3d90
00545acc mov dword ptr [esp + 0x24], eax
00545ad0 lea eax, [esp + 0x24]
00545ad4 push eax
00545ad5 lea eax, [esp + 0x2c]
00545ad9 mov dword ptr [esp + 0x2c], 0
00545ae1 push eax
00545ae2 push 0
00545ae4 push 0xc02fec
00545ae9 push ebx
00545aea lea eax, [esp + 0x28]
00545aee mov dword ptr [esp + 0x28], 0x85
00545af6 push eax
00545af7 lea eax, [esp + 0x24]
00545afb mov dword ptr [esp + 0x24], 0x3e8
00545b03 push eax
00545b04 call 0x800fb0
00545b09 mov ecx, dword ptr [esi + 0x1c3198]
00545b0f push 0
00545b11 push dword ptr [esp + 0x10]
00545b15 call 0x6c4b30
00545b1a mov ebx, eax
00545b1c mov dword ptr [esp + 0x10], ebx
00545b20 test ebx, ebx
00545b22 je 0x545d27
00545b28 call dword ptr [0xa064c0]
00545b2e mov ecx, dword ptr [ebx + 0x320]
00545b34 mov dword ptr [esp + 0x1c], eax
00545b38 lea eax, [ebx + 0x320]
00545b3e mov dword ptr [ebx + 0x34], 0
00545b45 mov dword ptr [ebx + 0x38], 0
00545b4c test ecx, ecx
00545b4e je 0x545b6a
00545b50 mov dword ptr [esp + 0x34], eax
00545b54 add ecx, 0x324
00545b5a lea eax, [esp + 0x34]
00545b5e push eax
00545b5f call 0x4bc3c0
00545b64 lea eax, [ebx + 0x320]
00545b6a push dword ptr [esp + 0x24]
00545b6e mov dword ptr [eax], 0
00545b74 mov ecx, ebx
00545b76 mov eax, dword ptr [edi + 0x294]
00545b7c push dword ptr [esp + 0x2c]
00545b80 mov dword ptr [ebx + 0x294], eax
00545b86 mov eax, dword ptr [edi + 0x298]
00545b8c push dword ptr [esp + 0x1c]
00545b90 mov dword ptr [ebx + 0x298], eax
00545b96 movss xmm0, dword ptr [0xc02fec]
00545b9e mov eax, dword ptr [ebx]
00545ba0 push dword ptr [esp + 0x18]
00545ba4 movss dword ptr [ebx + 0x2b8], xmm0
00545bac movss xmm0, dword ptr [0xc02ff0]
00545bb4 movss dword ptr [ebx + 0x2bc], xmm0
00545bbc call dword ptr [eax + 4]
00545bbf mov edx, dword ptr [esi + 0x18190]
00545bc5 push ebx
00545bc6 mov ecx, dword ptr [edx + 0x1214]
00545bcc lea eax, [ecx + 1]
00545bcf mov dword ptr [edx + 0x1214], eax
00545bd5 mov dword ptr [ebx + 0x20], ecx
00545bd8 lea ecx, [edx + 0x1218]
00545bde call 0x413280
00545be3 push ebx
00545be4 call 0x6d94d0
00545be9 test al, al
00545beb je 0x545bf4
00545bed push ecx
00545bee push ebx
00545bef call 0x6d9590
00545bf4 cmp byte ptr [ebx + 0x16a], 0
00545bfb je 0x545d17
00545c01 mov eax, dword ptr [esi + 0x283c20]
00545c07 cmp eax, dword ptr [esi + 0x283c24]
00545c0d je 0x545d17
00545c13 mov eax, dword ptr [ebx + 0x28]
00545c16 lea ecx, [esi + 0x283c48]
00545c1c mov dword ptr [esp + 0x14], eax
00545c20 mov eax, dword ptr [ebx + 0x2c]
00545c23 mov dword ptr [esp + 0x18], eax
00545c27 lea eax, [esp + 0x14]
00545c2b push eax
00545c2c lea eax, [esp + 0x38]
00545c30 push eax
00545c31 call 0x937c80
00545c36 mov eax, dword ptr [esi + 0x283c48]
00545c3c cmp dword ptr [esp + 0x34], eax
00545c40 jne 0x545c74
00545c42 mov eax, dword ptr [ebx + 0x28]
00545c45 lea ecx, [esi + 0x283c48]
00545c4b mov dword ptr [esp + 0x14], eax
00545c4f lea eax, [esp + 0x14]
00545c53 push eax
00545c54 lea eax, [esp + 0x38]
00545c58 mov dword ptr [esp + 0x1c], 0xffffffff
00545c60 push eax
00545c61 call 0x937c80
00545c66 mov ecx, dword ptr [esi + 0x283c48]
00545c6c cmp dword ptr [eax], ecx
00545c6e je 0x545d17
00545c74 mov esi, dword ptr [0xbfd65c]
00545c7a xor ebx, ebx
00545c7c mov eax, dword ptr [esi + 0x1ba54]
00545c82 sub eax, dword ptr [esi + 0x1ba50]
00545c88 sar eax, 2
00545c8b test eax, eax
00545c8d je 0x545d13
00545c93 mov edi, dword ptr [esp + 0x10]
00545c97 nop word ptr [eax + eax]
00545ca0 mov ecx, dword ptr [esi + 0x1ba54]
00545ca6 mov eax, ecx
00545ca8 sub eax, dword ptr [esi + 0x1ba50]
00545cae test eax, 0xfffffffc
00545cb3 jne 0x545cca
00545cb5 push 0xb3f4d0
00545cba push 3
00545cbc call 0x95e330
00545cc1 mov ecx, dword ptr [esi + 0x1ba54]
00545cc7 add esp, 8
00545cca mov eax, dword ptr [esi + 0x1ba50]
00545cd0 sub ecx, eax
00545cd2 sar ecx, 2
00545cd5 cmp ebx, ecx
00545cd7 jae 0x545cdc
00545cd9 lea eax, [eax + ebx*4]
00545cdc mov ecx, dword ptr [eax]
00545cde push 0xc02fec
00545ce3 push dword ptr [esp + 0x48]
00545ce7 add ecx, 0x1ec0
00545ced push edi
00545cee push 6
00545cf0 call 0x935fd0
00545cf5 mov esi, dword ptr [0xbfd65c]
00545cfb inc ebx
00545cfc mov eax, dword ptr [esi + 0x1ba54]
00545d02 sub eax, dword ptr [esi + 0x1ba50]
00545d08 sar eax, 2
00545d0b cmp ebx, eax
00545d0d jb 0x545ca0
00545d0f mov edi, dword ptr [esp + 0x30]
00545d13 mov ebx, dword ptr [esp + 0x10]
00545d17 call dword ptr [0xa064c0]
00545d1d sub eax, dword ptr [esp + 0x1c]
00545d21 add dword ptr [0xbffe0c], eax
00545d27 mov eax, dword ptr [ebx]
00545d29 lea ecx, [esp + 0x54]
00545d2d push 1
00545d2f push 0
00545d31 push 0xff
00545d36 xorps xmm0, xmm0
00545d39 mov dword ptr [esp + 0x80], 0x3f800000
00545d44 push -1
00545d46 movups xmmword ptr [esp + 0x74], xmm0
00545d4b push ecx
00545d4c movaps xmm0, xmmword ptr [0xb6bd30]
00545d53 mov ecx, ebx
00545d55 movups xmmword ptr [esp + 0x68], xmm0
00545d5a mov dword ptr [esp + 0x8c], 0x3f40c0c2
00545d65 mov dword ptr [esp + 0x90], 0x3b808081
00545d70 call dword ptr [eax + 0x38]
00545d73 mov eax, dword ptr [edi + 0x288]
00545d79 mov byte ptr [edi + 0x169], 1
00545d80 mov eax, dword ptr [eax + 0x24]
00545d83 mov dword ptr [edi + 0x150], eax
00545d89 cmp dword ptr [edi + 0x70], 0
00545d8d je 0x545d9c
00545d8f cmp byte ptr [edi + 0x80], 0
00545d96 jne 0x546459
00545d9c mov dword ptr [edi + 0xab4], 3
00545da6 mov dword ptr [edi + 0x180], 4
00545db0 jmp 0x546459
00545db5 push 0
00545db7 push 0xb4355c
00545dbc lea ecx, [edi + 0x3c]
00545dbf call 0x4054f0
00545dc4 cmp dword ptr [edi + 0x70], 0
00545dc8 je 0x54609c
00545dce cmp byte ptr [edi + 0x80], 0
00545dd5 je 0x54609c
00545ddb lea ecx, [edi + 0x3c]
00545dde call 0x4058f0
00545de3 cmp eax, 1
00545de6 jne 0x546090
00545dec mov esi, dword ptr [0xbfd65c]
00545df2 lea ebx, [edi + 0x294]
00545df8 mov dword ptr [esp + 0x44], ebx
00545dfc call 0x6c3d90
00545e01 mov dword ptr [esp + 0x14], eax
00545e05 lea eax, [esp + 0x14]
00545e09 push eax
00545e0a lea eax, [esp + 0x2c]
00545e0e mov dword ptr [esp + 0x2c], 0
00545e16 push eax
00545e17 push 0
00545e19 push 0xc02fec
00545e1e push ebx
00545e1f lea eax, [esp + 0x38]
00545e23 mov dword ptr [esp + 0x38], 0x85
00545e2b push eax
00545e2c lea eax, [esp + 0x28]
00545e30 mov dword ptr [esp + 0x28], 0x3e8
00545e38 push eax
00545e39 call 0x800fb0
00545e3e mov ecx, dword ptr [esi + 0x1c3198]
00545e44 push 0
00545e46 push dword ptr [esp + 0x14]
00545e4a call 0x6c4b30
00545e4f mov ebx, eax
00545e51 mov dword ptr [esp + 0xc], ebx
00545e55 test ebx, ebx
00545e57 je 0x546057
00545e5d call dword ptr [0xa064c0]
00545e63 mov ecx, dword ptr [ebx + 0x320]
00545e69 mov dword ptr [esp + 0x34], eax
00545e6d lea eax, [ebx + 0x320]
00545e73 mov dword ptr [ebx + 0x34], 0
00545e7a mov dword ptr [ebx + 0x38], 0
00545e81 test ecx, ecx
00545e83 je 0x545e9f
00545e85 mov dword ptr [esp + 0x1c], eax
00545e89 add ecx, 0x324
00545e8f lea eax, [esp + 0x1c]
00545e93 push eax
00545e94 call 0x4bc3c0
00545e99 lea eax, [ebx + 0x320]
00545e9f push dword ptr [esp + 0x14]
00545ea3 mov dword ptr [eax], 0
00545ea9 mov ecx, ebx
00545eab mov eax, dword ptr [edi + 0x294]
00545eb1 push dword ptr [esp + 0x2c]
00545eb5 mov dword ptr [ebx + 0x294], eax
00545ebb mov eax, dword ptr [edi + 0x298]
00545ec1 push dword ptr [esp + 0x2c]
00545ec5 mov dword ptr [ebx + 0x298], eax
00545ecb movss xmm0, dword ptr [0xc02fec]
00545ed3 mov eax, dword ptr [ebx]
00545ed5 push dword ptr [esp + 0x1c]
00545ed9 movss dword ptr [ebx + 0x2b8], xmm0
00545ee1 movss xmm0, dword ptr [0xc02ff0]
00545ee9 movss dword ptr [ebx + 0x2bc], xmm0
00545ef1 call dword ptr [eax + 4]
00545ef4 mov edx, dword ptr [esi + 0x18190]
00545efa push ebx
00545efb mov ecx, dword ptr [edx + 0x1214]
00545f01 lea eax, [ecx + 1]
00545f04 mov dword ptr [edx + 0x1214], eax
00545f0a mov dword ptr [ebx + 0x20], ecx
00545f0d lea ecx, [edx + 0x1218]
00545f13 call 0x413280
00545f18 push ebx
00545f19 call 0x6d94d0
00545f1e test al, al
00545f20 je 0x545f29
00545f22 push ecx
00545f23 push ebx
00545f24 call 0x6d9590
00545f29 cmp byte ptr [ebx + 0x16a], 0
00545f30 je 0x546047
00545f36 mov eax, dword ptr [esi + 0x283c20]
00545f3c cmp eax, dword ptr [esi + 0x283c24]
00545f42 je 0x546047
00545f48 mov eax, dword ptr [ebx + 0x28]
00545f4b lea ecx, [esi + 0x283c48]
00545f51 mov dword ptr [esp + 0x14], eax
00545f55 mov eax, dword ptr [ebx + 0x2c]
00545f58 mov dword ptr [esp + 0x18], eax
00545f5c lea eax, [esp + 0x14]
00545f60 push eax
00545f61 lea eax, [esp + 0x20]
00545f65 push eax
00545f66 call 0x937c80
00545f6b mov eax, dword ptr [esi + 0x283c48]
00545f71 cmp dword ptr [esp + 0x1c], eax
00545f75 jne 0x545fa9
00545f77 mov eax, dword ptr [ebx + 0x28]
00545f7a lea ecx, [esi + 0x283c48]
00545f80 mov dword ptr [esp + 0x14], eax
00545f84 lea eax, [esp + 0x14]
00545f88 push eax
00545f89 lea eax, [esp + 0x20]
00545f8d mov dword ptr [esp + 0x1c], 0xffffffff
00545f95 push eax
00545f96 call 0x937c80
00545f9b mov ecx, dword ptr [esi + 0x283c48]
00545fa1 cmp dword ptr [eax], ecx
00545fa3 je 0x546047
00545fa9 mov esi, dword ptr [0xbfd65c]
00545faf xor ebx, ebx
00545fb1 mov eax, dword ptr [esi + 0x1ba54]
00545fb7 sub eax, dword ptr [esi + 0x1ba50]
00545fbd sar eax, 2
00545fc0 test eax, eax
00545fc2 je 0x546043
00545fc8 mov edi, dword ptr [esp + 0xc]
00545fcc nop dword ptr [eax]
00545fd0 mov ecx, dword ptr [esi + 0x1ba54]
00545fd6 mov eax, ecx
00545fd8 sub eax, dword ptr [esi + 0x1ba50]
00545fde test eax, 0xfffffffc
00545fe3 jne 0x545ffa
00545fe5 push 0xb3f4d0
00545fea push 3
00545fec call 0x95e330
00545ff1 mov ecx, dword ptr [esi + 0x1ba54]
00545ff7 add esp, 8
00545ffa mov eax, dword ptr [esi + 0x1ba50]
00546000 sub ecx, eax
00546002 sar ecx, 2
00546005 cmp ebx, ecx
00546007 jae 0x54600c
00546009 lea eax, [eax + ebx*4]
0054600c mov ecx, dword ptr [eax]
0054600e push 0xc02fec
00546013 push dword ptr [esp + 0x48]
00546017 add ecx, 0x1ec0
0054601d push edi
0054601e push 6
00546020 call 0x935fd0
00546025 mov esi, dword ptr [0xbfd65c]
0054602b inc ebx
0054602c mov eax, dword ptr [esi + 0x1ba54]
00546032 sub eax, dword ptr [esi + 0x1ba50]
00546038 sar eax, 2
0054603b cmp ebx, eax
0054603d jb 0x545fd0
0054603f mov edi, dword ptr [esp + 0x30]
00546043 mov ebx, dword ptr [esp + 0xc]
00546047 call dword ptr [0xa064c0]
0054604d sub eax, dword ptr [esp + 0x34]
00546051 add dword ptr [0xbffe0c], eax
00546057 mov edx, dword ptr [ebx]
00546059 xorps xmm3, xmm3
0054605c push 1
0054605e push 0
00546060 push 0xff
00546065 push -1
00546067 push 1
00546069 push 0xc0
0054606e push 0xff
00546073 push ecx
00546074 xorps xmm2, xmm2
00546077 mov dword ptr [esp], 0x3f800000
0054607e xorps xmm1, xmm1
00546081 lea ecx, [esp + 0x74]
00546085 call 0x4270d0
0054608a push eax
0054608b mov ecx, ebx
0054608d call dword ptr [edx + 0x38]
00546090 mov ecx, edi
00546092 call 0x545220
00546097 jmp 0x54635a
0054609c mov esi, dword ptr [0xbfd65c]
005460a2 lea ebx, [edi + 0x294]
005460a8 mov dword ptr [esp + 0x44], ebx
005460ac call 0x6c3d90
005460b1 mov dword ptr [esp + 0x14], eax
005460b5 lea eax, [esp + 0x14]
005460b9 push eax
005460ba lea eax, [esp + 0x2c]
005460be mov dword ptr [esp + 0x2c], 0
005460c6 push eax
005460c7 push 0
005460c9 push 0xc02fec
005460ce push ebx
005460cf lea eax, [esp + 0x38]
005460d3 mov dword ptr [esp + 0x38], 0x85
005460db push eax
005460dc lea eax, [esp + 0x28]
005460e0 mov dword ptr [esp + 0x28], 0x3e8
005460e8 push eax
005460e9 call 0x800fb0
005460ee mov ecx, dword ptr [esi + 0x1c3198]
005460f4 push 0
005460f6 push dword ptr [esp + 0x14]
005460fa call 0x6c4b30
005460ff mov ebx, eax
00546101 mov dword ptr [esp + 0xc], ebx
00546105 test ebx, ebx
00546107 je 0x546307
0054610d call dword ptr [0xa064c0]
00546113 mov ecx, dword ptr [ebx + 0x320]
00546119 mov dword ptr [esp + 0x34], eax
0054611d lea eax, [ebx + 0x320]
00546123 mov dword ptr [ebx + 0x34], 0
0054612a mov dword ptr [ebx + 0x38], 0
00546131 test ecx, ecx
00546133 je 0x54614f
00546135 mov dword ptr [esp + 0x1c], eax
00546139 add ecx, 0x324
0054613f lea eax, [esp + 0x1c]
00546143 push eax
00546144 call 0x4bc3c0
00546149 lea eax, [ebx + 0x320]
0054614f push dword ptr [esp + 0x14]
00546153 mov dword ptr [eax], 0
00546159 mov ecx, ebx
0054615b mov eax, dword ptr [edi + 0x294]
00546161 push dword ptr [esp + 0x2c]
00546165 mov dword ptr [ebx + 0x294], eax
0054616b mov eax, dword ptr [edi + 0x298]
00546171 push dword ptr [esp + 0x2c]
00546175 mov dword ptr [ebx + 0x298], eax
0054617b movss xmm0, dword ptr [0xc02fec]
00546183 mov eax, dword ptr [ebx]
00546185 push dword ptr [esp + 0x1c]
00546189 movss dword ptr [ebx + 0x2b8], xmm0
00546191 movss xmm0, dword ptr [0xc02ff0]
00546199 movss dword ptr [ebx + 0x2bc], xmm0
005461a1 call dword ptr [eax + 4]
005461a4 mov edx, dword ptr [esi + 0x18190]
005461aa push ebx
005461ab mov ecx, dword ptr [edx + 0x1214]
005461b1 lea eax, [ecx + 1]
005461b4 mov dword ptr [edx + 0x1214], eax
005461ba mov dword ptr [ebx + 0x20], ecx
005461bd lea ecx, [edx + 0x1218]
005461c3 call 0x413280
005461c8 push ebx
005461c9 call 0x6d94d0
005461ce test al, al
005461d0 je 0x5461d9
005461d2 push ecx
005461d3 push ebx
005461d4 call 0x6d9590
005461d9 cmp byte ptr [ebx + 0x16a], 0
005461e0 je 0x5462f7
005461e6 mov eax, dword ptr [esi + 0x283c20]
005461ec cmp eax, dword ptr [esi + 0x283c24]
005461f2 je 0x5462f7
005461f8 mov eax, dword ptr [ebx + 0x28]
005461fb lea ecx, [esi + 0x283c48]
00546201 mov dword ptr [esp + 0x14], eax
00546205 mov eax, dword ptr [ebx + 0x2c]
00546208 mov dword ptr [esp + 0x18], eax
0054620c lea eax, [esp + 0x14]
00546210 push eax
00546211 lea eax, [esp + 0x20]
00546215 push eax
00546216 call 0x937c80
0054621b mov eax, dword ptr [esi + 0x283c48]
00546221 cmp dword ptr [esp + 0x1c], eax
00546225 jne 0x546259
00546227 mov eax, dword ptr [ebx + 0x28]
0054622a lea ecx, [esi + 0x283c48]
00546230 mov dword ptr [esp + 0x14], eax
00546234 lea eax, [esp + 0x14]
00546238 push eax
00546239 lea eax, [esp + 0x20]
0054623d mov dword ptr [esp + 0x1c], 0xffffffff
00546245 push eax
00546246 call 0x937c80
0054624b mov ecx, dword ptr [esi + 0x283c48]
00546251 cmp dword ptr [eax], ecx
00546253 je 0x5462f7
00546259 mov esi, dword ptr [0xbfd65c]
0054625f xor ebx, ebx
00546261 mov eax, dword ptr [esi + 0x1ba54]
00546267 sub eax, dword ptr [esi + 0x1ba50]
0054626d sar eax, 2
00546270 test eax, eax
00546272 je 0x5462f3
00546278 mov edi, dword ptr [esp + 0xc]
0054627c nop dword ptr [eax]
00546280 mov ecx, dword ptr [esi + 0x1ba54]
00546286 mov eax, ecx
00546288 sub eax, dword ptr [esi + 0x1ba50]
0054628e test eax, 0xfffffffc
00546293 jne 0x5462aa
00546295 push 0xb3f4d0
0054629a push 3
0054629c call 0x95e330
005462a1 mov ecx, dword ptr [esi + 0x1ba54]
005462a7 add esp, 8
005462aa mov eax, dword ptr [esi + 0x1ba50]
005462b0 sub ecx, eax
005462b2 sar ecx, 2
005462b5 cmp ebx, ecx
005462b7 jae 0x5462bc
005462b9 lea eax, [eax + ebx*4]
005462bc mov ecx, dword ptr [eax]
005462be push 0xc02fec
005462c3 push dword ptr [esp + 0x48]
005462c7 add ecx, 0x1ec0
005462cd push edi
005462ce push 6
005462d0 call 0x935fd0
005462d5 mov esi, dword ptr [0xbfd65c]
005462db inc ebx
005462dc mov eax, dword ptr [esi + 0x1ba54]
005462e2 sub eax, dword ptr [esi + 0x1ba50]
005462e8 sar eax, 2
005462eb cmp ebx, eax
005462ed jb 0x546280
005462ef mov edi, dword ptr [esp + 0x30]
005462f3 mov ebx, dword ptr [esp + 0xc]
005462f7 call dword ptr [0xa064c0]
005462fd sub eax, dword ptr [esp + 0x34]
00546301 add dword ptr [0xbffe0c], eax
00546307 mov eax, dword ptr [ebx]
00546309 lea ecx, [esp + 0x54]
0054630d push 1
0054630f push 0
00546311 push 0xff
00546316 xorps xmm0, xmm0
00546319 mov dword ptr [esp + 0x80], 0x3f800000
00546324 push -1
00546326 movups xmmword ptr [esp + 0x74], xmm0
0054632b push ecx
0054632c movaps xmm0, xmmword ptr [0xb6bd30]
00546333 mov ecx, ebx
00546335 movups xmmword ptr [esp + 0x68], xmm0
0054633a mov dword ptr [esp + 0x8c], 0x3f40c0c2
00546345 mov dword ptr [esp + 0x90], 0x3b808081
00546350 call dword ptr [eax + 0x38]
00546353 mov eax, dword ptr [edi]
00546355 mov ecx, edi
00546357 call dword ptr [eax + 0x28]
0054635a movss xmm1, dword ptr [edi + 0x28c]
00546362 movss xmm0, dword ptr [edi + 0x290]
0054636a subss xmm1, dword ptr [edi + 0x294]
00546372 subss xmm0, dword ptr [edi + 0x298]
0054637a movss dword ptr [edi + 0x2b8], xmm1
00546382 movss dword ptr [edi + 0x2bc], xmm0
0054638a jmp 0x546459
0054638f movss xmm0, dword ptr [edi + 0x2c4]
00546397 lea ecx, [edi + 0x3c]
0054639a mulss xmm0, dword ptr [0xb6a480]
005463a2 push 0
005463a4 push 0xb43570
005463a9 movss dword ptr [edi + 0x2c4], xmm0
005463b1 call 0x4054f0
005463b6 cmp dword ptr [edi + 0x70], 0
005463ba je 0x5463c9
005463bc cmp byte ptr [edi + 0x80], 0
005463c3 jne 0x546459
005463c9 cmp dword ptr [edi + 0x180], 0
005463d0 je 0x546459
005463d6 call 0x6c3d90
005463db mov ecx, dword ptr [0xbfd65c]
005463e1 push 0
005463e3 push eax
005463e4 push 0
005463e6 push 0
005463e8 push 0xc02fec
005463ed lea eax, [edi + 0x294]
005463f3 push eax
005463f4 push 0x85
005463f9 push 0x3e8
005463fe call 0x6d0ca0
00546403 push 1
00546405 push 0
00546407 push 0xff
0054640c push -1
0054640e push 1
00546410 push 0xc0
00546415 mov edx, eax
00546417 xorps xmm3, xmm3
0054641a push 0xff
0054641f push ecx
00546420 xorps xmm2, xmm2
00546423 mov dword ptr [esp], 0x3f800000
0054642a mov esi, dword ptr [edx]
0054642c lea ecx, [esp + 0x74]
00546430 xorps xmm1, xmm1
00546433 call 0x4270d0
00546438 push eax
00546439 mov ecx, edx
0054643b call dword ptr [esi + 0x38]
0054643e mov dword ptr [edi + 0x180], 0
00546448 mov byte ptr [edi + 0x169], 0
0054644f mov dword ptr [edi + 0x150], 0
00546459 cmp byte ptr [edi + 0x16b], 0
00546460 je 0x546469
00546462 mov ecx, edi
00546464 call 0x544b70
00546469 mov ecx, dword ptr [esp + 0x12c]
00546470 pop edi
00546471 pop esi
00546472 pop ebx
00546473 xor ecx, esp
00546475 call 0x9eacd7
0054647a mov esp, ebp
0054647c pop ebp
0054647d ret 
