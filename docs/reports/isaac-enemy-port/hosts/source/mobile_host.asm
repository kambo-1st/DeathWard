0051f510 push ebp
0051f511 mov ebp, esp
0051f513 push -1
0051f515 push 0x9ef795
0051f51a mov eax, dword ptr fs:[0]
0051f520 push eax
0051f521 sub esp, 0x104
0051f527 mov eax, dword ptr [0xbaa3b4]
0051f52c xor eax, ebp
0051f52e mov dword ptr [ebp - 0x10], eax
0051f531 push ebx
0051f532 push esi
0051f533 push edi
0051f534 push eax
0051f535 lea eax, [ebp - 0xc]
0051f538 mov dword ptr fs:[0], eax
0051f53e mov esi, ecx
0051f540 cmp dword ptr [esi + 0x28], 0xcc
0051f547 jne 0x51f553
0051f549 cmp dword ptr [esi + 0x30], 0x63
0051f54d je 0x51f553
0051f54f mov bl, 1
0051f551 jmp 0x51f555
0051f553 xor bl, bl
0051f555 cmp dword ptr [esi + 0xab4], 0
0051f55c jne 0x51f586
0051f55e mov dword ptr [esi + 0xab4], 4
0051f568 mov dword ptr [esi + 0x360], 0
0051f572 test bl, bl
0051f574 je 0x520011
0051f57a mov byte ptr [esi + 0x308], 1
0051f581 jmp 0x520011
0051f586 cmp dword ptr [esi + 0x90], 0
0051f58d mov byte ptr [esi + 0x308], 0
0051f594 jne 0x51f5a5
0051f596 push 0
0051f598 push 0xb3fd8c
0051f59d lea ecx, [esi + 0x3c]
0051f5a0 call 0x405a00
0051f5a5 mov eax, dword ptr [0xb404ec]
0051f5aa mov ecx, dword ptr [0xb404f0]
0051f5b0 mov dword ptr [ebp - 0x2c], 0xf
0051f5b7 mov dword ptr [ebp - 0x30], 8
0051f5be mov dword ptr [ebp - 0x40], eax
0051f5c1 mov dword ptr [ebp - 0x3c], ecx
0051f5c4 mov byte ptr [ebp - 0x38], 0
0051f5c8 mov dword ptr [ebp - 4], 0
0051f5cf mov eax, dword ptr [0xb40504]
0051f5d4 mov ecx, dword ptr [0xb40508]
0051f5da mov dword ptr [ebp - 0x14], 0xf
0051f5e1 mov dword ptr [ebp - 0x18], 8
0051f5e8 mov dword ptr [ebp - 0x28], eax
0051f5eb mov dword ptr [ebp - 0x24], ecx
0051f5ee mov byte ptr [ebp - 0x20], 0
0051f5f2 push ecx
0051f5f3 mov byte ptr [ebp - 4], 1
0051f5f7 lea eax, [ebp - 0x40]
0051f5fa mov dword ptr [esp], 0x3dcccccd
0051f601 mov ecx, esi
0051f603 push eax
0051f604 lea eax, [ebp - 0x28]
0051f607 push eax
0051f608 call 0x6980a0
0051f60d mov byte ptr [ebp - 4], 0
0051f611 mov edx, dword ptr [ebp - 0x14]
0051f614 cmp edx, 0x10
0051f617 jb 0x51f641
0051f619 mov ecx, dword ptr [ebp - 0x28]
0051f61c inc edx
0051f61d mov eax, ecx
0051f61f cmp edx, 0x1000
0051f625 jb 0x51f637
0051f627 mov ecx, dword ptr [ecx - 4]
0051f62a add edx, 0x23
0051f62d sub eax, ecx
0051f62f add eax, -4
0051f632 cmp eax, 0x1f
0051f635 ja 0x51f680
0051f637 push edx
0051f638 push ecx
0051f639 call 0x9eb08e
0051f63e add esp, 8
0051f641 mov dword ptr [ebp - 4], 0xffffffff
0051f648 mov edx, dword ptr [ebp - 0x2c]
0051f64b mov dword ptr [ebp - 0x18], 0
0051f652 mov dword ptr [ebp - 0x14], 0xf
0051f659 mov byte ptr [ebp - 0x28], 0
0051f65d cmp edx, 0x10
0051f660 jb 0x51f690
0051f662 mov ecx, dword ptr [ebp - 0x40]
0051f665 inc edx
0051f666 mov eax, ecx
0051f668 cmp edx, 0x1000
0051f66e jb 0x51f686
0051f670 mov ecx, dword ptr [ecx - 4]
0051f673 add edx, 0x23
0051f676 sub eax, ecx
0051f678 add eax, -4
0051f67b cmp eax, 0x1f
0051f67e jbe 0x51f686
0051f680 call dword ptr [0xa065ac]
0051f686 push edx
0051f687 push ecx
0051f688 call 0x9eb08e
0051f68d add esp, 8
0051f690 xorps xmm3, xmm3
0051f693 test bl, bl
0051f695 je 0x51f7d0
0051f69b movss xmm0, dword ptr [esi + 0x14]
0051f6a0 comiss xmm0, xmm3
0051f6a3 jbe 0x51f7d0
0051f6a9 mov eax, dword ptr [esi + 0xab4]
0051f6af xorps xmm0, xmm0
0051f6b2 movss dword ptr [ebp - 0x104], xmm0
0051f6ba cmp eax, 4
0051f6bd je 0x51f6f4
0051f6bf cmp eax, 8
0051f6c2 jne 0x51f73d
0051f6c4 push 0xb432ac
0051f6c9 lea ecx, [esi + 0x8c]
0051f6cf call 0x405f30
0051f6d4 test al, al
0051f6d6 jne 0x51f6ec
0051f6d8 push 0xb432d8
0051f6dd lea ecx, [esi + 0x8c]
0051f6e3 call 0x405f30
0051f6e8 test al, al
0051f6ea jne 0x51f73d
0051f6ec movss xmm0, dword ptr [ebp - 0x104]
0051f6f4 mov eax, dword ptr [esi + 8]
0051f6f7 cmp eax, dword ptr [esi + 0xc]
0051f6fa je 0x51f73d
0051f6fc nop dword ptr [eax]
0051f700 mov ecx, dword ptr [eax + 0xc]
0051f703 mov edx, dword ptr [eax + 8]
0051f706 mov dword ptr [ebp - 0x10c], ecx
0051f70c mov ecx, edx
0051f70e and ecx, 0x8000
0051f714 or ecx, 0
0051f717 jne 0x51f72d
0051f719 and edx, 0x400000
0051f71f or edx, ecx
0051f721 jne 0x51f727
0051f723 addss xmm0, dword ptr [eax]
0051f727 mov dword ptr [eax], 0
0051f72d add eax, 0x38
0051f730 cmp eax, dword ptr [esi + 0xc]
0051f733 jne 0x51f700
0051f735 movss dword ptr [ebp - 0x104], xmm0
0051f73d cmp dword ptr [esi + 0xab4], 4
0051f744 xorps xmm3, xmm3
0051f747 jne 0x51f7d0
0051f74d movss xmm2, dword ptr [ebp - 0x104]
0051f755 comiss xmm2, xmm3
0051f758 jbe 0x51f7d0
0051f75a movss xmm1, dword ptr [esi + 0x14]
0051f75f mov ecx, dword ptr [esi + 0x360]
0051f765 movaps xmm0, xmm1
0051f768 addss xmm0, dword ptr [0xb6a480]
0051f770 mulss xmm1, dword ptr [0xb6a274]
0051f778 cvttss2si eax, xmm0
0051f77c movss xmm0, dword ptr [esi + 0xb08]
0051f784 cdq 
0051f785 subss xmm0, xmm1
0051f789 sub eax, edx
0051f78b sar eax, 1
0051f78d add ecx, eax
0051f78f mov eax, 0xa
0051f794 cmp ecx, eax
0051f796 maxss xmm0, xmm3
0051f79a cmovl eax, ecx
0051f79d comiss xmm2, dword ptr [0xb6a9c8]
0051f7a4 mov dword ptr [esi + 0x360], eax
0051f7aa movss dword ptr [esi + 0xb08], xmm0
0051f7b2 jbe 0x51f7d0
0051f7b4 push 0
0051f7b6 push 0xb42f20
0051f7bb lea ecx, [esi + 0x3c]
0051f7be call 0x405a00
0051f7c3 mov dword ptr [esi + 0xb08], 0
0051f7cd xorps xmm3, xmm3
0051f7d0 cmp dword ptr [esi + 0xe6c], -1
0051f7d7 movss xmm0, dword ptr [0xb6a614]
0051f7df je 0x51f8fe
0051f7e5 mov eax, dword ptr [esi + 0x160]
0051f7eb and eax, 0x10
0051f7ee or eax, 0
0051f7f1 je 0x51f8a7
0051f7f7 cmp dword ptr [esi + 0x90], 0
0051f7fe je 0x51f849
0051f800 cmp byte ptr [esi + 0xa0], 0
0051f807 je 0x51f849
0051f809 mov eax, dword ptr [esi + 0x90]
0051f80f cmp dword ptr [eax + 0x14], 0x10
0051f813 jb 0x51f817
0051f815 mov eax, dword ptr [eax]
0051f817 mov ecx, 0xb42f20
0051f81c nop dword ptr [eax]
0051f820 mov dl, byte ptr [eax]
0051f822 cmp dl, byte ptr [ecx]
0051f824 jne 0x51f840
0051f826 test dl, dl
0051f828 je 0x51f83c
0051f82a mov dl, byte ptr [eax + 1]
0051f82d cmp dl, byte ptr [ecx + 1]
0051f830 jne 0x51f840
0051f832 add eax, 2
0051f835 add ecx, 2
0051f838 test dl, dl
0051f83a jne 0x51f820
0051f83c xor eax, eax
0051f83e jmp 0x51f845
0051f840 sbb eax, eax
0051f842 or eax, 1
0051f845 test eax, eax
0051f847 je 0x51f8a7
0051f849 test bl, bl
0051f84b je 0x51f8a7
0051f84d push 0
0051f84f push 0x1000a00
0051f854 mov ecx, esi
0051f856 movss dword ptr [ebp - 0x104], xmm0
0051f85e call 0x4122f0
0051f863 test al, al
0051f865 je 0x51f871
0051f867 movss xmm1, dword ptr [0xb6a7b0]
0051f86f jmp 0x51f879
0051f871 movss xmm1, dword ptr [ebp - 0x104]
0051f879 mulss xmm1, dword ptr [esi + 0x2f4]
0051f881 movss xmm0, dword ptr [0xb6a614]
0051f889 divss xmm1, dword ptr [0xb6aae4]
0051f891 addss xmm1, dword ptr [esi + 0xb0c]
0051f899 minss xmm1, xmm0
0051f89d movss dword ptr [esi + 0xb0c], xmm1
0051f8a5 jmp 0x51f8ec
0051f8a7 movss xmm0, dword ptr [esi + 0x2f4]
0051f8af movss xmm1, dword ptr [esi + 0xb0c]
0051f8b7 addss xmm0, xmm0
0051f8bb divss xmm0, dword ptr [0xb6aae4]
0051f8c3 subss xmm1, xmm0
0051f8c7 maxss xmm1, xmm3
0051f8cb movss dword ptr [esi + 0xb0c], xmm1
0051f8d3 movss xmm0, dword ptr [0xb6a614]
0051f8db test bl, bl
0051f8dd jne 0x51f8ec
0051f8df mov dword ptr [esi + 0xb0c], 0
0051f8e9 movaps xmm1, xmm3
0051f8ec movaps xmm3, xmm1
0051f8ef xorps xmm2, xmm2
0051f8f2 push 1
0051f8f4 movaps xmm1, xmm0
0051f8f7 mov ecx, esi
0051f8f9 call 0x6afbd0
0051f8fe mov eax, dword ptr [esi + 0xab4]
0051f904 cmp eax, 4
0051f907 jne 0x51fb59
0051f90d mov eax, dword ptr [esi + 0x164]
0051f913 mov dword ptr [ebp - 0x10c], eax
0051f919 test bl, bl
0051f91b je 0x51f92a
0051f91d or dword ptr [esi + 0x160], 0x10
0051f924 mov dword ptr [esi + 0x164], eax
0051f92a mov ecx, dword ptr [esi + 0x160]
0051f930 and ecx, 0x1000800
0051f936 or ecx, 0
0051f939 je 0x51f99a
0051f93b cmp dword ptr [esi + 0xe6c], -1
0051f942 jne 0x51f99a
0051f944 mov ecx, esi
0051f946 call 0x695680
0051f94b push 0
0051f94d mov ecx, dword ptr [eax + 0x294]
0051f953 mov eax, dword ptr [eax + 0x298]
0051f959 mov dword ptr [ebp - 0x104], eax
0051f95f lea eax, [ebp - 0x108]
0051f965 mov dword ptr [ebp - 0x108], ecx
0051f96b lea ecx, [esi + 0x364]
0051f971 push eax
0051f972 call 0x7a4830
0051f977 cmp dword ptr [esi + 0xaa0], 0
0051f97e jle 0x51f9da
0051f980 movss xmm0, dword ptr [esi + 0x2c4]
0051f988 mulss xmm0, dword ptr [0xb6a560]
0051f990 movss dword ptr [esi + 0x2c4], xmm0
0051f998 jmp 0x51f9da
0051f99a mov ecx, esi
0051f99c call 0x695680
0051f9a1 push 1
0051f9a3 push 0x12c
0051f9a8 mov ecx, dword ptr [eax + 0x294]
0051f9ae mov eax, dword ptr [eax + 0x298]
0051f9b4 push ecx
0051f9b5 mov dword ptr [ebp - 0x104], eax
0051f9bb lea eax, [ebp - 0x108]
0051f9c1 mov dword ptr [ebp - 0x108], ecx
0051f9c7 lea ecx, [esi + 0x364]
0051f9cd mov dword ptr [esp], 0x3f000000
0051f9d4 push eax
0051f9d5 call 0x7a3650
0051f9da cmp dword ptr [esi + 0x360], 0
0051f9e1 jg 0x51f9f2
0051f9e3 push 0
0051f9e5 push 0xb3fd8c
0051f9ea lea ecx, [esi + 0x3c]
0051f9ed call 0x405a00
0051f9f2 cmp dword ptr [esi + 0xe6c], -1
0051f9f9 je 0x51fa4c
0051f9fb movss xmm0, dword ptr [esi + 0xb0c]
0051fa03 comiss xmm0, dword ptr [0xb6a614]
0051fa0a jae 0x51fa27
0051fa0c movss xmm1, dword ptr [0xb6accc]
0051fa14 mov ecx, esi
0051fa16 push 7
0051fa18 push 0
0051fa1a call 0x6a15a0
0051fa1f test al, al
0051fa21 je 0x51fb14
0051fa27 movss xmm0, dword ptr [0xc02fec]
0051fa2f movss dword ptr [esi + 0xe70], xmm0
0051fa37 movss xmm0, dword ptr [0xc02ff0]
0051fa3f movss dword ptr [esi + 0xe74], xmm0
0051fa47 jmp 0x51faf6
0051fa4c cmp dword ptr [esi + 0x360], 0
0051fa53 jg 0x51fb14
0051fa59 mov eax, dword ptr [esi + 0x160]
0051fa5f and eax, 0x200
0051fa64 or eax, 0
0051fa67 jne 0x51fa7a
0051fa69 push eax
0051fa6a push 0x1000800
0051fa6f mov ecx, esi
0051fa71 call 0x4122f0
0051fa76 test al, al
0051fa78 je 0x51fa9c
0051fa7a call 0x6c3d90
0051fa7f xor edx, edx
0051fa81 mov ecx, 0x32
0051fa86 div ecx
0051fa88 test edx, edx
0051fa8a jne 0x51fa9c
0051fa8c mov dword ptr [esi + 0xab4], 9
0051fa96 mov dword ptr [esi + 0x360], edx
0051fa9c cmp dword ptr [esi + 0x360], 0
0051faa3 jg 0x51fb14
0051faa5 call 0x6c3d90
0051faaa xor edx, edx
0051faac mov ecx, 3
0051fab1 div ecx
0051fab3 test edx, edx
0051fab5 jne 0x51fb14
0051fab7 mov edx, dword ptr [esi + 0xaf0]
0051fabd test edx, edx
0051fabf jle 0x51fadf
0051fac1 cvttss2si eax, dword ptr [esi + 0x2fc]
0051fac9 cvttss2si ecx, dword ptr [esi + 0x2f8]
0051fad1 sub ecx, eax
0051fad3 add edx, ecx
0051fad5 mov dword ptr [esi + 0xaf0], edx
0051fadb test edx, edx
0051fadd jg 0x51fb14
0051fadf movss xmm1, dword ptr [0xb6abe4]
0051fae7 mov ecx, esi
0051fae9 push 7
0051faeb push 0
0051faed call 0x6a15a0
0051faf2 test al, al
0051faf4 je 0x51fb14
0051faf6 mov dword ptr [esi + 0xaf0], 0x46
0051fb00 mov dword ptr [esi + 0x360], 0
0051fb0a mov dword ptr [esi + 0xab4], 8
0051fb14 cmp dword ptr [esi + 0xab4], 8
0051fb1b je 0x51fb44
0051fb1d movss xmm1, dword ptr [0xb6a928]
0051fb25 xorps xmm2, xmm2
0051fb28 mov ecx, esi
0051fb2a call 0x6847e0
0051fb2f test eax, eax
0051fb31 je 0x51fb44
0051fb33 mov eax, dword ptr [esi + 0x360]
0051fb39 test eax, eax
0051fb3b jle 0x51fb44
0051fb3d dec eax
0051fb3e mov dword ptr [esi + 0x360], eax
0051fb44 movss xmm0, dword ptr [esi + 0x2c4]
0051fb4c mulss xmm0, dword ptr [0xb6a560]
0051fb54 jmp 0x520009
0051fb59 cmp eax, 9
0051fb5c jne 0x51fc26
0051fb62 push 0xb432d8
0051fb67 lea ecx, [esi + 0x8c]
0051fb6d call 0x405e90
0051fb72 test al, al
0051fb74 je 0x51fb96
0051fb76 push ecx
0051fb77 mov dword ptr [esp], 0x3f800000
0051fb7e push 0
0051fb80 push 2
0051fb82 push ecx
0051fb83 mov dword ptr [esp], 0x3f800000
0051fb8a mov ecx, esi
0051fb8c push 0xa6
0051fb91 call 0x6ad720
0051fb96 inc dword ptr [esi + 0x360]
0051fb9c test bl, bl
0051fb9e je 0x51fbb3
0051fba0 mov eax, dword ptr [esi + 0x164]
0051fba6 and dword ptr [esi + 0x160], 0xffffffef
0051fbad mov dword ptr [esi + 0x164], eax
0051fbb3 push 0
0051fbb5 push 0xb400ac
0051fbba lea ecx, [esi + 0x3c]
0051fbbd call 0x405a00
0051fbc2 mov ecx, esi
0051fbc4 call 0x695680
0051fbc9 xorps xmm1, xmm1
0051fbcc movss xmm0, dword ptr [eax + 0x294]
0051fbd4 subss xmm0, dword ptr [esi + 0x294]
0051fbdc comiss xmm1, xmm0
0051fbdf seta al
0051fbe2 mov byte ptr [esi + 0x13c], al
0051fbe8 cmp dword ptr [esi + 0x90], 0
0051fbef je 0x51fbfe
0051fbf1 cmp byte ptr [esi + 0xa0], 0
0051fbf8 jne 0x51fff9
0051fbfe push 0
0051fc00 push 0xb3fd8c
0051fc05 lea ecx, [esi + 0x3c]
0051fc08 mov dword ptr [esi + 0xab4], 4
0051fc12 mov dword ptr [esi + 0x360], 0
0051fc1c call 0x405a00
0051fc21 jmp 0x51fff9
0051fc26 cmp eax, 8
0051fc29 jne 0x520011
0051fc2f push 0xb432d8
0051fc34 lea ecx, [esi + 0x8c]
0051fc3a call 0x405e90
0051fc3f test al, al
0051fc41 je 0x51fc63
0051fc43 push ecx
0051fc44 mov dword ptr [esp], 0x3f800000
0051fc4b push 0
0051fc4d push 2
0051fc4f push ecx
0051fc50 mov dword ptr [esp], 0x3f800000
0051fc57 mov ecx, esi
0051fc59 push 0xa6
0051fc5e call 0x6ad720
0051fc63 cmp dword ptr [esi + 0xe6c], -1
0051fc6a je 0x51fcf8
0051fc70 push 0xb400ac
0051fc75 lea ecx, [esi + 0x8c]
0051fc7b call 0x405f30
0051fc80 test al, al
0051fc82 jne 0x51fcf8
0051fc84 push 0
0051fc86 push 0x1000a00
0051fc8b mov ecx, esi
0051fc8d call 0x4122f0
0051fc92 test al, al
0051fc94 je 0x51fcb0
0051fc96 movss xmm0, dword ptr [0xc02fec]
0051fc9e movss dword ptr [esi + 0xe70], xmm0
0051fca6 movss xmm0, dword ptr [0xc02ff0]
0051fcae jmp 0x51fcf0
0051fcb0 movss xmm2, dword ptr [0xb6ae44]
0051fcb8 mov ecx, esi
0051fcba push 0
0051fcbc call 0x6af8d0
0051fcc1 lea eax, [ebp - 0x110]
0051fcc7 mov ecx, esi
0051fcc9 push eax
0051fcca call 0x6afac0
0051fccf movss xmm1, dword ptr [eax]
0051fcd3 subss xmm1, dword ptr [esi + 0x294]
0051fcdb movss xmm0, dword ptr [eax + 4]
0051fce0 subss xmm0, dword ptr [esi + 0x298]
0051fce8 movss dword ptr [esi + 0xe70], xmm1
0051fcf0 movss dword ptr [esi + 0xe74], xmm0
0051fcf8 inc dword ptr [esi + 0x360]
0051fcfe test bl, bl
0051fd00 je 0x51fd15
0051fd02 mov eax, dword ptr [esi + 0x164]
0051fd08 and dword ptr [esi + 0x160], 0xffffffef
0051fd0f mov dword ptr [esi + 0x164], eax
0051fd15 push 0
0051fd17 lea ebx, [esi + 0x3c]
0051fd1a push 0xb400ac
0051fd1f mov ecx, ebx
0051fd21 call 0x405a00
0051fd26 cmp dword ptr [esi + 0xe6c], -1
0051fd2d je 0x51fd3b
0051fd2f xorps xmm0, xmm0
0051fd32 comiss xmm0, dword ptr [esi + 0xe70]
0051fd39 jmp 0x51fd58
0051fd3b mov ecx, esi
0051fd3d call 0x695680
0051fd42 xorps xmm1, xmm1
0051fd45 movss xmm0, dword ptr [eax + 0x294]
0051fd4d subss xmm0, dword ptr [esi + 0x294]
0051fd55 comiss xmm1, xmm0
0051fd58 seta al
0051fd5b mov byte ptr [esi + 0x13c], al
0051fd61 mov edx, dword ptr [esi + 0xaf0]
0051fd67 test edx, edx
0051fd69 jle 0x51fd85
0051fd6b cvttss2si eax, dword ptr [esi + 0x2fc]
0051fd73 cvttss2si ecx, dword ptr [esi + 0x2f8]
0051fd7b sub ecx, eax
0051fd7d add ecx, edx
0051fd7f mov dword ptr [esi + 0xaf0], ecx
0051fd85 push 0xb400ac
0051fd8a lea ecx, [esi + 0x8c]
0051fd90 call 0x405e90
0051fd95 test al, al
0051fd97 je 0x51fecb
0051fd9d mov ecx, esi
0051fd9f call 0x695680
0051fda4 cmp dword ptr [esi + 0xe6c], -1
0051fdab lea ebx, [esi + 0x294]
0051fdb1 movss xmm0, dword ptr [eax + 0x294]
0051fdb9 movss xmm1, dword ptr [eax + 0x298]
0051fdc1 subss xmm0, dword ptr [ebx]
0051fdc5 subss xmm1, dword ptr [ebx + 4]
0051fdca movss dword ptr [ebp - 0x108], xmm0
0051fdd2 movss dword ptr [ebp - 0x104], xmm1
0051fdda je 0x51fdfc
0051fddc movss xmm0, dword ptr [esi + 0xe70]
0051fde4 movss xmm1, dword ptr [esi + 0xe74]
0051fdec movss dword ptr [ebp - 0x108], xmm0
0051fdf4 movss dword ptr [ebp - 0x104], xmm1
0051fdfc ucomiss xmm0, dword ptr [0xc02fec]
0051fe03 lahf 
0051fe04 test ah, 0x44
0051fe07 jp 0x51fe1a
0051fe09 ucomiss xmm1, dword ptr [0xc02ff0]
0051fe10 lahf 
0051fe11 test ah, 0x44
0051fe14 jnp 0x51fec8
0051fe1a push ecx
0051fe1b mov dword ptr [esp], 0x3f800000
0051fe22 push 0
0051fe24 push 2
0051fe26 push ecx
0051fe27 mov dword ptr [esp], 0x3f800000
0051fe2e mov ecx, esi
0051fe30 push 0xb2
0051fe35 call 0x6ad720
0051fe3a movss xmm1, dword ptr [ebp - 0x108]
0051fe42 movss xmm0, dword ptr [ebp - 0x104]
0051fe4a mulss xmm0, xmm0
0051fe4e mulss xmm1, xmm1
0051fe52 addss xmm0, xmm1
0051fe56 call 0x4228c0
0051fe5b comiss xmm0, dword ptr [0xb6a18c]
0051fe62 jbe 0x51fe98
0051fe64 movss xmm1, dword ptr [0xb6a928]
0051fe6c divss xmm1, xmm0
0051fe70 movss xmm0, dword ptr [ebp - 0x108]
0051fe78 mulss xmm0, xmm1
0051fe7c movss dword ptr [ebp - 0x108], xmm0
0051fe84 movss xmm0, dword ptr [ebp - 0x104]
0051fe8c mulss xmm0, xmm1
0051fe90 movss dword ptr [ebp - 0x104], xmm0
0051fe98 lea ecx, [ebp - 0x100]
0051fe9e call 0x430d70
0051fea3 cmp dword ptr [esi + 0x28], 0xcc
0051feaa mov ecx, 2
0051feaf push eax
0051feb0 mov eax, 5
0051feb5 cmove eax, ecx
0051feb8 mov ecx, esi
0051feba push eax
0051febb lea eax, [ebp - 0x108]
0051fec1 push eax
0051fec2 push ebx
0051fec3 call 0x6a1a20
0051fec8 lea ebx, [esi + 0x3c]
0051fecb push 0xb4030c
0051fed0 lea ecx, [esi + 0x8c]
0051fed6 call 0x405e90
0051fedb test al, al
0051fedd je 0x51ffbb
0051fee3 cmp dword ptr [esi + 0xe6c], -1
0051feea je 0x51ff04
0051feec push 0xc02fec
0051fef1 lea ecx, [esi + 0xe70]
0051fef7 call 0x962ca0
0051fefc test al, al
0051fefe je 0x51ffbb
0051ff04 push 0xb432e8
0051ff09 lea ecx, [esi + 0x8c]
0051ff0f call 0x405da0
0051ff14 movss xmm1, dword ptr [0xc02fec]
0051ff1c movss xmm2, dword ptr [0xc02ff0]
0051ff24 test eax, eax
0051ff26 je 0x51ff31
0051ff28 movss xmm1, dword ptr [eax]
0051ff2c movss xmm2, dword ptr [eax + 4]
0051ff31 divss xmm1, dword ptr [0xb6a4dc]
0051ff39 push 0xc02fec
0051ff3e lea ecx, [ebp - 0x54]
0051ff41 mov dword ptr [ebp - 0x108], 0
0051ff4b mov dword ptr [ebp - 0x104], 0xc0c00000
0051ff55 divss xmm2, dword ptr [0xb6a4dc]
0051ff5d addss xmm1, dword ptr [esi + 0x294]
0051ff65 addss xmm2, dword ptr [esi + 0x298]
0051ff6d movss dword ptr [ebp - 0x110], xmm1
0051ff75 movss dword ptr [ebp - 0x10c], xmm2
0051ff7d call 0x402120
0051ff82 push eax
0051ff83 lea eax, [ebp - 0x108]
0051ff89 mov ecx, 1
0051ff8e push eax
0051ff8f lea edx, [ebp - 0x110]
0051ff95 call 0x6aead0
0051ff9a add esp, 0xc
0051ff9d mov dword ptr [eax + 0xd8], 0x3f400000
0051ffa7 mov dword ptr [eax + 0xdc], 0x3f400000
0051ffb1 mov dword ptr [eax + 0x2b0], 0x42c80000
0051ffbb cmp dword ptr [esi + 0x90], 0
0051ffc2 je 0x51ffcd
0051ffc4 cmp byte ptr [esi + 0xa0], 0
0051ffcb jne 0x51fff9
0051ffcd push 0
0051ffcf push 0xb3fd8c
0051ffd4 mov ecx, ebx
0051ffd6 mov dword ptr [esi + 0xab4], 4
0051ffe0 mov dword ptr [esi + 0x360], 0
0051ffea call 0x405a00
0051ffef mov dword ptr [esi + 0xb0c], 0
0051fff9 movss xmm0, dword ptr [esi + 0x2c4]
00520001 mulss xmm0, dword ptr [0xb6a480]
00520009 movss dword ptr [esi + 0x2c4], xmm0
00520011 mov ecx, dword ptr [ebp - 0xc]
00520014 mov dword ptr fs:[0], ecx
0052001b pop ecx
0052001c pop edi
0052001d pop esi
0052001e pop ebx
0052001f mov ecx, dword ptr [ebp - 0x10]
00520022 xor ecx, ebp
00520024 call 0x9eacd7
00520029 mov esp, ebp
0052002b pop ebp
0052002c ret 
