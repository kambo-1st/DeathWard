004fc330 push ebx
004fc331 mov ebx, esp
004fc333 sub esp, 8
004fc336 and esp, 0xfffffff8
004fc339 add esp, 4
004fc33c push ebp
004fc33d mov ebp, dword ptr [ebx + 4]
004fc340 mov dword ptr [esp + 4], ebp
004fc344 mov ebp, esp
004fc346 push -1
004fc348 push 0x9ef365
004fc34d mov eax, dword ptr fs:[0]
004fc353 push eax
004fc354 push ebx
004fc355 sub esp, 0x88
004fc35b mov eax, dword ptr [0xbaa3b4]
004fc360 xor eax, ebp
004fc362 mov dword ptr [ebp - 0x14], eax
004fc365 push esi
004fc366 push edi
004fc367 push eax
004fc368 lea eax, [ebp - 0xc]
004fc36b mov dword ptr fs:[0], eax
004fc371 mov edi, ecx
004fc373 cmp dword ptr [edi + 0xac4], 1
004fc37a jne 0x4fc3a5
004fc37c mov eax, dword ptr [edi + 0xb10]
004fc382 test eax, eax
004fc384 jle 0x4fd097
004fc38a dec eax
004fc38b mov dword ptr [edi + 0xb10], eax
004fc391 test eax, eax
004fc393 jg 0x4fd097
004fc399 mov byte ptr [edi + 0x308], 0
004fc3a0 jmp 0x4fd097
004fc3a5 cmp dword ptr [edi + 0xab4], 0
004fc3ac jne 0x4fc562
004fc3b2 mov eax, dword ptr [edi + 0x2c]
004fc3b5 cmp eax, 3
004fc3b8 jne 0x4fc418
004fc3ba push ecx
004fc3bb mov ecx, dword ptr [0xbfd65c]
004fc3c1 call 0x706110
004fc3c6 cmp eax, 0x20
004fc3c9 jne 0x4fc3d5
004fc3cb lea ecx, [ebp - 0x40]
004fc3ce call 0x402120
004fc3d3 jmp 0x4fc403
004fc3d5 movups xmm0, xmmword ptr [0xbc5178]
004fc3dc mov eax, dword ptr [0xbc51a0]
004fc3e1 mov dword ptr [ebp - 0x44], eax
004fc3e4 lea eax, [ebp - 0x6c]
004fc3e7 movups xmmword ptr [ebp - 0x6c], xmm0
004fc3eb movups xmm0, xmmword ptr [0xbc5188]
004fc3f2 movups xmmword ptr [ebp - 0x5c], xmm0
004fc3f6 movq xmm0, qword ptr [0xbc5198]
004fc3fe movq qword ptr [ebp - 0x4c], xmm0
004fc403 push eax
004fc404 lea ecx, [edi + 0x1dc]
004fc40a call 0x4021a0
004fc40f or dword ptr [edi + 0xe68], 1
004fc416 jmp 0x4fc444
004fc418 cmp eax, 2
004fc41b jne 0x4fc444
004fc41d movss xmm3, dword ptr [0xb6a274]
004fc425 lea ecx, [ebp - 0x6c]
004fc428 movss xmm1, dword ptr [0xb6a234]
004fc430 movaps xmm2, xmm3
004fc433 call 0x427080
004fc438 push eax
004fc439 lea ecx, [edi + 0x1dc]
004fc43f call 0x4021a0
004fc444 mov eax, dword ptr [edi + 0x2d8]
004fc44a mov dword ptr [edi + 0xb00], eax
004fc450 cmp dword ptr [edi + 0x30], 0xa
004fc454 mov dword ptr [edi + 0xab4], 4
004fc45e jne 0x4fd097
004fc464 mov ecx, dword ptr [edi + 0x160]
004fc46a mov eax, ecx
004fc46c mov edx, dword ptr [edi + 0x164]
004fc472 and eax, 4
004fc475 or eax, 0
004fc478 je 0x4fc544
004fc47e and ecx, 0xfffffffb
004fc481 mov dword ptr [edi + 0x164], edx
004fc487 mov dword ptr [edi + 0x160], ecx
004fc48d call 0x6c3d90
004fc492 mov ecx, dword ptr [0xbfd65c]
004fc498 push 0
004fc49a push 0xbeaaec
004fc49f push 0xbeab18
004fc4a4 push 0
004fc4a6 push eax
004fc4a7 push 0
004fc4a9 push edi
004fc4aa push 0xc02fec
004fc4af lea eax, [edi + 0x294]
004fc4b5 push eax
004fc4b6 push 0xf
004fc4b8 push 0x3e8
004fc4bd call 0x422e20
004fc4c2 push eax
004fc4c3 call 0x9ec34c
004fc4c8 mov ecx, dword ptr [edi + 0x2a4]
004fc4ce mov edx, eax
004fc4d0 add esp, 0x14
004fc4d3 mov dword ptr [ebp - 0x74], edx
004fc4d6 mov dword ptr [edx + 0x2a4], ecx
004fc4dc mov ecx, dword ptr [edi + 0x2a8]
004fc4e2 mov dword ptr [edx + 0x2a8], ecx
004fc4e8 movss xmm0, dword ptr [edi + 0x2a8]
004fc4f0 addss xmm0, dword ptr [0xb6a614]
004fc4f8 movss dword ptr [edx + 0x2b0], xmm0
004fc500 cmp byte ptr [edi + 0xbb3], 0
004fc507 je 0x4fc53d
004fc509 mov esi, dword ptr [edx]
004fc50b lea eax, [ebp - 0x6c]
004fc50e push 1
004fc510 push 0
004fc512 push 0xff
004fc517 push -1
004fc519 push eax
004fc51a mov eax, dword ptr [edi + 0xbb4]
004fc520 mov ecx, eax
004fc522 shl ecx, 4
004fc525 sub ecx, eax
004fc527 lea ecx, [ecx*4 + 0xbc5700]
004fc52e call 0x4f3e00
004fc533 mov ecx, dword ptr [ebp - 0x74]
004fc536 push eax
004fc537 call dword ptr [esi + 0x38]
004fc53a mov edx, dword ptr [ebp - 0x74]
004fc53d mov eax, dword ptr [edx]
004fc53f mov ecx, edx
004fc541 call dword ptr [eax + 0xc]
004fc544 push 0
004fc546 push 0xb42ef4
004fc54b lea ecx, [edi + 0x3c]
004fc54e call 0x4054f0
004fc553 mov dword ptr [edi + 0xab4], 3
004fc55d jmp 0x4fd097
004fc562 cmp dword ptr [edi + 0x28], 0x116
004fc569 xorps xmm0, xmm0
004fc56c movss dword ptr [ebp - 0x84], xmm0
004fc574 jne 0x4fc655
004fc57a movss xmm1, dword ptr [edi + 0x2d8]
004fc582 movss xmm0, dword ptr [edi + 0xb00]
004fc58a subss xmm0, xmm1
004fc58e comiss xmm0, dword ptr [0xb6a8f4]
004fc595 jbe 0x4fc655
004fc59b movss dword ptr [edi + 0xb00], xmm1
004fc5a3 call 0x695680
004fc5a8 movss xmm2, dword ptr [edi + 0x294]
004fc5b0 lea esi, [edi + 0x294]
004fc5b6 movss xmm0, dword ptr [esi + 4]
004fc5bb push 0
004fc5bd movss xmm1, dword ptr [eax + 0x294]
004fc5c5 movss xmm3, dword ptr [eax + 0x298]
004fc5cd subss xmm1, xmm2
004fc5d1 subss xmm3, xmm0
004fc5d5 push 0
004fc5d7 push ecx
004fc5d8 mov ecx, dword ptr [0xbfd65c]
004fc5de lea eax, [ebp - 0x80]
004fc5e1 mulss xmm1, dword ptr [0xb6a53c]
004fc5e9 mov dword ptr [esp], 0
004fc5f0 mulss xmm3, dword ptr [0xb6a53c]
004fc5f8 mov ecx, dword ptr [ecx + 0x18190]
004fc5fe addss xmm2, xmm1
004fc602 push eax
004fc603 addss xmm0, xmm3
004fc607 lea eax, [ebp - 0x8c]
004fc60d push eax
004fc60e movss dword ptr [ebp - 0x80], xmm2
004fc613 movss dword ptr [ebp - 0x7c], xmm0
004fc618 call 0x7cf240
004fc61d push ecx
004fc61e mov dword ptr [esp], 0xc1f00000
004fc625 push 0
004fc627 push dword ptr [eax + 4]
004fc62a push dword ptr [eax]
004fc62c push edi
004fc62d push esi
004fc62e call 0x6994f0
004fc633 add esp, 0x14
004fc636 mov dword ptr [esp], 0x3f800000
004fc63d push 0
004fc63f push 2
004fc641 push ecx
004fc642 mov dword ptr [esp], 0x3e800000
004fc649 mov ecx, edi
004fc64b push 0xb5
004fc650 call 0x6ad720
004fc655 cmp byte ptr [edi + 0x16b], 0
004fc65c je 0x4fc733
004fc662 cmp dword ptr [edi + 0x28], 0x18
004fc666 jne 0x4fc733
004fc66c cmp dword ptr [edi + 0x2c], 2
004fc670 jne 0x4fc733
004fc676 call 0x6c3d90
004fc67b mov ecx, dword ptr [0xbfd65c]
004fc681 push 0
004fc683 push 0xbeaaec
004fc688 push 0xbeab18
004fc68d push 0
004fc68f push eax
004fc690 push 0
004fc692 push edi
004fc693 push 0xc02fec
004fc698 lea eax, [edi + 0x294]
004fc69e push eax
004fc69f push 0x1a
004fc6a1 push 0x3e8
004fc6a6 call 0x422e20
004fc6ab push eax
004fc6ac call 0x9ec34c
004fc6b1 mov esi, eax
004fc6b3 add esp, 0x14
004fc6b6 mov ecx, dword ptr [esi + 0x314]
004fc6bc lea eax, [esi + 0x314]
004fc6c2 test ecx, ecx
004fc6c4 je 0x4fc6de
004fc6c6 mov dword ptr [ebp - 0x74], eax
004fc6c9 add ecx, 0x324
004fc6cf lea eax, [ebp - 0x74]
004fc6d2 push eax
004fc6d3 call 0x4bc3c0
004fc6d8 lea eax, [esi + 0x314]
004fc6de push eax
004fc6df mov ecx, edi
004fc6e1 mov dword ptr [eax], edi
004fc6e3 call 0x4bae70
004fc6e8 movss xmm2, dword ptr [0xbc7a28]
004fc6f0 mov ecx, esi
004fc6f2 movss xmm1, dword ptr [0xbc7a2c]
004fc6fa mulss xmm2, dword ptr [0xb6a7b0]
004fc702 mov eax, dword ptr [esi]
004fc704 mulss xmm1, dword ptr [0xb6a7b0]
004fc70c mov dword ptr [esi + 0x3ac], 0xd2
004fc716 movss dword ptr [esi + 0xd8], xmm2
004fc71e mov dword ptr [esi + 0x3b0], 0xd2
004fc728 movss dword ptr [esi + 0xdc], xmm1
004fc730 call dword ptr [eax + 0xc]
004fc733 cmp dword ptr [edi + 0xab4], 4
004fc73a jne 0x4fca31
004fc740 call 0x6c3d90
004fc745 xor edx, edx
004fc747 mov ecx, 0xa
004fc74c div ecx
004fc74e test edx, edx
004fc750 jne 0x4fc7ad
004fc752 call 0x6c3d90
004fc757 push ecx
004fc758 mov ecx, edi
004fc75a movd xmm0, eax
004fc75e cvtdq2pd xmm0, xmm0
004fc762 shr eax, 0x1f
004fc765 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
004fc76e cvtpd2ps xmm0, xmm0
004fc772 mulss xmm0, dword ptr [0xb6a19c]
004fc77a mulss xmm0, dword ptr [0xb6a480]
004fc782 addss xmm0, dword ptr [0xb6a350]
004fc78a movss dword ptr [esp], xmm0
004fc78f call 0x68d7b0
004fc794 push 1
004fc796 push 0
004fc798 push 0xff
004fc79d mov edx, dword ptr [eax]
004fc79f lea ecx, [edi + 0x1dc]
004fc7a5 push -1
004fc7a7 push ecx
004fc7a8 mov ecx, eax
004fc7aa call dword ptr [edx + 0x38]
004fc7ad mov eax, dword ptr [0xb404ec]
004fc7b2 mov ecx, dword ptr [0xb404f0]
004fc7b8 mov dword ptr [ebp - 0x44], 0xf
004fc7bf mov dword ptr [ebp - 0x48], 8
004fc7c6 mov dword ptr [ebp - 0x58], eax
004fc7c9 mov dword ptr [ebp - 0x54], ecx
004fc7cc mov byte ptr [ebp - 0x50], 0
004fc7d0 mov dword ptr [ebp - 4], 0
004fc7d7 mov eax, dword ptr [0xb40504]
004fc7dc mov ecx, dword ptr [0xb40508]
004fc7e2 mov dword ptr [ebp - 0x18], 0xf
004fc7e9 mov dword ptr [ebp - 0x1c], 8
004fc7f0 mov dword ptr [ebp - 0x2c], eax
004fc7f3 mov dword ptr [ebp - 0x28], ecx
004fc7f6 mov byte ptr [ebp - 0x24], 0
004fc7fa push ecx
004fc7fb mov byte ptr [ebp - 4], 1
004fc7ff lea eax, [ebp - 0x58]
004fc802 mov dword ptr [esp], 0x3dcccccd
004fc809 mov ecx, edi
004fc80b push eax
004fc80c lea eax, [ebp - 0x2c]
004fc80f push eax
004fc810 call 0x6980a0
004fc815 mov byte ptr [ebp - 4], 0
004fc819 mov edx, dword ptr [ebp - 0x18]
004fc81c cmp edx, 0x10
004fc81f jb 0x4fc849
004fc821 mov ecx, dword ptr [ebp - 0x2c]
004fc824 inc edx
004fc825 mov eax, ecx
004fc827 cmp edx, 0x1000
004fc82d jb 0x4fc83f
004fc82f mov ecx, dword ptr [ecx - 4]
004fc832 add edx, 0x23
004fc835 sub eax, ecx
004fc837 add eax, -4
004fc83a cmp eax, 0x1f
004fc83d ja 0x4fc888
004fc83f push edx
004fc840 push ecx
004fc841 call 0x9eb08e
004fc846 add esp, 8
004fc849 mov dword ptr [ebp - 4], 0xffffffff
004fc850 mov edx, dword ptr [ebp - 0x44]
004fc853 mov dword ptr [ebp - 0x1c], 0
004fc85a mov dword ptr [ebp - 0x18], 0xf
004fc861 mov byte ptr [ebp - 0x2c], 0
004fc865 cmp edx, 0x10
004fc868 jb 0x4fc898
004fc86a mov ecx, dword ptr [ebp - 0x58]
004fc86d inc edx
004fc86e mov eax, ecx
004fc870 cmp edx, 0x1000
004fc876 jb 0x4fc88e
004fc878 mov ecx, dword ptr [ecx - 4]
004fc87b add edx, 0x23
004fc87e sub eax, ecx
004fc880 add eax, -4
004fc883 cmp eax, 0x1f
004fc886 jbe 0x4fc88e
004fc888 call dword ptr [0xa065ac]
004fc88e push edx
004fc88f push ecx
004fc890 call 0x9eb08e
004fc895 add esp, 8
004fc898 mov eax, dword ptr [edi + 0x160]
004fc89e and eax, 0x1000800
004fc8a3 or eax, 0
004fc8a6 je 0x4fc8f8
004fc8a8 cmp dword ptr [edi + 0xe6c], -1
004fc8af jne 0x4fc8f8
004fc8b1 mov ecx, edi
004fc8b3 call 0x695680
004fc8b8 push 0
004fc8ba mov ecx, dword ptr [eax + 0x294]
004fc8c0 mov eax, dword ptr [eax + 0x298]
004fc8c6 mov dword ptr [ebp - 0x7c], eax
004fc8c9 lea eax, [ebp - 0x80]
004fc8cc mov dword ptr [ebp - 0x80], ecx
004fc8cf lea ecx, [edi + 0x364]
004fc8d5 push eax
004fc8d6 call 0x7a4830
004fc8db movss xmm0, dword ptr [edi + 0x2c4]
004fc8e3 mulss xmm0, dword ptr [0xb6a560]
004fc8eb movss dword ptr [edi + 0x2c4], xmm0
004fc8f3 jmp 0x4fc99a
004fc8f8 cmp dword ptr [edi + 0x28], 0x116
004fc8ff jne 0x4fc90b
004fc901 movss xmm0, dword ptr [0xb6a4c4]
004fc909 jmp 0x4fc96c
004fc90b mov eax, dword ptr [edi + 0x2c]
004fc90e cmp eax, 1
004fc911 jne 0x4fc91d
004fc913 movss xmm0, dword ptr [0xb6a64c]
004fc91b jmp 0x4fc96c
004fc91d cmp eax, 3
004fc920 jne 0x4fc964
004fc922 cmp dword ptr [edi + 0x30], 0
004fc926 mov eax, dword ptr [edi + 0x344]
004fc92c movq xmm0, qword ptr [0xa08db8]
004fc934 mov dword ptr [ebp - 0x24], eax
004fc937 mov eax, dword ptr [0xa08dc0]
004fc93c movq qword ptr [ebp - 0x20], xmm0
004fc941 mov dword ptr [ebp - 0x18], eax
004fc944 je 0x4fc964
004fc946 lea ecx, [ebp - 0x24]
004fc949 call 0x7a7db0
004fc94e fmul dword ptr [0xb6a38c]
004fc954 fadd dword ptr [0xb6a4dc]
004fc95a fstp dword ptr [ebp - 0x74]
004fc95d movss xmm0, dword ptr [ebp - 0x74]
004fc962 jmp 0x4fc96c
004fc964 movss xmm0, dword ptr [0xb6a53c]
004fc96c push 1
004fc96e push 0
004fc970 sub esp, 8
004fc973 lea eax, [ebp - 0x8c]
004fc979 mov ecx, edi
004fc97b movss dword ptr [esp + 4], xmm0
004fc981 mov dword ptr [esp], 0
004fc988 push eax
004fc989 call 0x695a30
004fc98e push eax
004fc98f lea ecx, [edi + 0x364]
004fc995 call 0x7a3650
004fc99a cmp dword ptr [edi + 0xe6c], -1
004fc9a1 mov ecx, edi
004fc9a3 je 0x4fc9b5
004fc9a5 push 0xa
004fc9a7 call 0x6af080
004fc9ac movzx eax, al
004fc9af test eax, eax
004fc9b1 je 0x4fca01
004fc9b3 jmp 0x4fc9e1
004fc9b5 call 0x695680
004fc9ba push eax
004fc9bb mov ecx, edi
004fc9bd call 0x6aeb40
004fc9c2 test al, al
004fc9c4 je 0x4fca01
004fc9c6 cmp byte ptr [edi + 0xa90], 0
004fc9cd je 0x4fca01
004fc9cf call 0x6c3d90
004fc9d4 xor edx, edx
004fc9d6 mov ecx, 3
004fc9db div ecx
004fc9dd test edx, edx
004fc9df jne 0x4fca01
004fc9e1 push ecx
004fc9e2 mov dword ptr [esp], 0x3f800000
004fc9e9 push 0
004fc9eb push 0x28
004fc9ed push ecx
004fc9ee mov dword ptr [esp], 0x3f800000
004fc9f5 mov ecx, edi
004fc9f7 push 0xa5
004fc9fc call 0x6ad720
004fca01 movss xmm0, dword ptr [edi + 0x2c4]
004fca09 mulss xmm0, dword ptr [0xb6a5f8]
004fca11 movss dword ptr [edi + 0x2c4], xmm0
004fca19 xorps xmm0, xmm0
004fca1c comiss xmm0, dword ptr [edi + 0x2b8]
004fca23 seta al
004fca26 mov byte ptr [edi + 0x13c], al
004fca2c jmp 0x4fcbce
004fca31 mov ecx, edi
004fca33 call 0x695680
004fca38 cmp dword ptr [edi + 0x2c], 1
004fca3c movss xmm1, dword ptr [eax + 0x294]
004fca44 movss xmm2, dword ptr [eax + 0x298]
004fca4c subss xmm1, dword ptr [edi + 0x294]
004fca54 subss xmm2, dword ptr [edi + 0x298]
004fca5c movss dword ptr [ebp - 0x74], xmm1
004fca61 movss dword ptr [ebp - 0x78], xmm2
004fca66 jne 0x4fcb69
004fca6c cmp dword ptr [edi + 0xe6c], -1
004fca73 je 0x4fcaae
004fca75 movss xmm2, dword ptr [0xb6a2cc]
004fca7d lea eax, [ebp - 0x8c]
004fca83 push eax
004fca84 mov ecx, edi
004fca86 call 0x6af0c0
004fca8b movss xmm1, dword ptr [eax]
004fca8f movss xmm2, dword ptr [eax + 4]
004fca94 mulss xmm1, dword ptr [0xb6a974]
004fca9c mulss xmm2, dword ptr [0xb6a974]
004fcaa4 movss dword ptr [ebp - 0x74], xmm1
004fcaa9 movss dword ptr [ebp - 0x78], xmm2
004fcaae movaps xmm0, xmm1
004fcab1 mulss xmm0, xmm1
004fcab5 movaps xmm1, xmm2
004fcab8 mulss xmm1, xmm2
004fcabc addss xmm0, xmm1
004fcac0 call 0x4228c0
004fcac5 movss xmm1, dword ptr [0xb6aba8]
004fcacd comiss xmm1, xmm0
004fcad0 jbe 0x4fcb57
004fcad6 comiss xmm0, dword ptr [0xb6a214]
004fcadd jbe 0x4fcb57
004fcadf movss xmm1, dword ptr [0xb6a480]
004fcae7 divss xmm1, xmm0
004fcaeb movss xmm2, dword ptr [ebp - 0x74]
004fcaf0 xorps xmm0, xmm0
004fcaf3 movss xmm3, dword ptr [ebp - 0x78]
004fcaf8 xorps xmm2, xmmword ptr [0xb6c9b0]
004fcaff xorps xmm3, xmmword ptr [0xb6c9b0]
004fcb06 mulss xmm2, xmm1
004fcb0a mulss xmm3, xmm1
004fcb0e movss xmm1, dword ptr [edi + 0x2c4]
004fcb16 ucomiss xmm1, xmm0
004fcb19 lahf 
004fcb1a test ah, 0x44
004fcb1d jnp 0x4fcb57
004fcb1f movss xmm0, dword ptr [edi + 0x2f4]
004fcb27 mulss xmm2, xmm0
004fcb2b mulss xmm3, xmm0
004fcb2f divss xmm2, xmm1
004fcb33 divss xmm3, xmm1
004fcb37 addss xmm2, dword ptr [edi + 0x2b8]
004fcb3f addss xmm3, dword ptr [edi + 0x2bc]
004fcb47 movss dword ptr [edi + 0x2b8], xmm2
004fcb4f movss dword ptr [edi + 0x2bc], xmm3
004fcb57 movss xmm0, dword ptr [edi + 0x2c4]
004fcb5f mulss xmm0, dword ptr [0xb6a578]
004fcb67 jmp 0x4fcb79
004fcb69 movss xmm0, dword ptr [edi + 0x2c4]
004fcb71 mulss xmm0, dword ptr [0xb6a50c]
004fcb79 movss dword ptr [edi + 0x2c4], xmm0
004fcb81 cmp dword ptr [edi + 0x70], 0
004fcb85 je 0x4fcbc4
004fcb87 push 0xb42990
004fcb8c lea ecx, [edi + 0x6c]
004fcb8f call 0x405e90
004fcb94 test al, al
004fcb96 je 0x4fcbb5
004fcb98 push ecx
004fcb99 mov dword ptr [esp], 0x3f800000
004fcba0 push 0
004fcba2 push 2
004fcba4 push ecx
004fcba5 mov dword ptr [esp], 0x3f800000
004fcbac mov ecx, edi
004fcbae push 0x1d
004fcbb0 call 0x6ad720
004fcbb5 cmp dword ptr [edi + 0x70], 0
004fcbb9 je 0x4fcbc4
004fcbbb cmp byte ptr [edi + 0x80], 0
004fcbc2 jne 0x4fcbce
004fcbc4 mov dword ptr [edi + 0xab4], 4
004fcbce cmp byte ptr [edi + 0x16b], 0
004fcbd5 je 0x4fd097
004fcbdb cmp dword ptr [edi + 0x28], 0x116
004fcbe2 jne 0x4fcc56
004fcbe4 call 0x6c3d90
004fcbe9 mov ecx, dword ptr [0xbfd65c]
004fcbef lea esi, [edi + 0x294]
004fcbf5 push eax
004fcbf6 push 0
004fcbf8 push edi
004fcbf9 push 0xc02fec
004fcbfe push esi
004fcbff push 0
004fcc01 push 0x118
004fcc06 call 0x422e20
004fcc0b call 0x6c3d90
004fcc10 push eax
004fcc11 push 0
004fcc13 push edi
004fcc14 push 0xc02fec
004fcc19 push 0
004fcc1b push 0
004fcc1d push ecx
004fcc1e mov ecx, dword ptr [0xbfd65c]
004fcc24 lea eax, [ebp - 0x8c]
004fcc2a mov dword ptr [esp], 0x42200000
004fcc31 push esi
004fcc32 push eax
004fcc33 mov ecx, dword ptr [ecx + 0x18190]
004fcc39 call 0x7cf240
004fcc3e mov ecx, dword ptr [0xbfd65c]
004fcc44 push eax
004fcc45 push 0
004fcc47 push 0x117
004fcc4c call 0x422e20
004fcc51 jmp 0x4fd097
004fcc56 cmp dword ptr [edi + 0x2c], 3
004fcc5a jne 0x4fd01b
004fcc60 mov eax, dword ptr [edi + 0x344]
004fcc66 mov ecx, edi
004fcc68 movq xmm0, qword ptr [0xa08dc4]
004fcc70 push 0x200000
004fcc75 mov dword ptr [ebp - 0x24], eax
004fcc78 mov eax, dword ptr [0xa08dcc]
004fcc7d push 0
004fcc7f movq qword ptr [ebp - 0x20], xmm0
004fcc84 mov dword ptr [ebp - 0x18], eax
004fcc87 call 0x4122f0
004fcc8c test al, al
004fcc8e jne 0x4fcdbc
004fcc94 mov eax, dword ptr [0xbfd65c]
004fcc99 mov ecx, 0x19
004fcc9e mov esi, 0xf
004fcca3 push 0x64
004fcca5 mov eax, dword ptr [eax + 0x18190]
004fccab cmp dword ptr [eax + 8], 5
004fccaf cmove esi, ecx
004fccb2 lea ecx, [ebp - 0x24]
004fccb5 imul esi, dword ptr [edi + 0x30]
004fccb9 call 0x7a7d50
004fccbe mov ecx, 0x63
004fccc3 cmp esi, ecx
004fccc5 cmovb ecx, esi
004fccc8 cmp eax, ecx
004fccca jbe 0x4fcdbc
004fccd0 movss xmm0, dword ptr [edi + 0x2b8]
004fccd8 movss xmm2, dword ptr [edi + 0x2bc]
004fcce0 movaps xmm1, xmm0
004fcce3 mulss xmm1, xmm0
004fcce7 movaps xmm0, xmm2
004fccea mulss xmm0, xmm2
004fccee addss xmm1, xmm0
004fccf2 movss xmm0, dword ptr [0xb6a214]
004fccfa comiss xmm0, xmm1
004fccfd jbe 0x4fcd10
004fccff lea eax, [ebp - 0x98]
004fcd05 push eax
004fcd06 call 0x659290
004fcd0b add esp, 4
004fcd0e jmp 0x4fcd78
004fcd10 movss xmm0, dword ptr [0xb6a704]
004fcd18 call 0x411fe0
004fcd1d movss dword ptr [ebp - 0x74], xmm0
004fcd22 movss xmm0, dword ptr [0xb6a704]
004fcd2a call 0x412010
004fcd2f movss xmm4, dword ptr [edi + 0x2b8]
004fcd37 lea eax, [ebp - 0x8c]
004fcd3d movss xmm5, dword ptr [edi + 0x2bc]
004fcd45 lea ecx, [ebp - 0x80]
004fcd48 movaps xmm2, xmm4
004fcd4b movaps xmm1, xmm5
004fcd4e mulss xmm2, dword ptr [ebp - 0x74]
004fcd53 push eax
004fcd54 mulss xmm5, dword ptr [ebp - 0x74]
004fcd59 mulss xmm1, xmm0
004fcd5d mulss xmm4, xmm0
004fcd61 subss xmm2, xmm1
004fcd65 addss xmm4, xmm5
004fcd69 movss dword ptr [ebp - 0x80], xmm2
004fcd6e movss dword ptr [ebp - 0x7c], xmm4
004fcd73 call 0x962560
004fcd78 cmp dword ptr [edi + 0xab4], 4
004fcd7f movss xmm1, dword ptr [eax]
004fcd83 movss xmm0, dword ptr [eax + 4]
004fcd88 movss dword ptr [ebp - 0x84], xmm1
004fcd90 movss dword ptr [ebp - 0x78], xmm0
004fcd95 mov byte ptr [edi + 0x16b], 0
004fcd9c mov byte ptr [ebp - 0x6d], 1
004fcda0 je 0x4fcddc
004fcda2 mov dword ptr [ebp - 0x74], 0x28
004fcda9 mov byte ptr [ebp - 0x6d], 1
004fcdad movss dword ptr [ebp - 0x84], xmm1
004fcdb5 movss dword ptr [ebp - 0x78], xmm0
004fcdba jmp 0x4fcdec
004fcdbc cmp dword ptr [edi + 0xab4], 4
004fcdc3 mov byte ptr [ebp - 0x6d], 0
004fcdc7 jne 0x4fd097
004fcdcd xorps xmm0, xmm0
004fcdd0 mov byte ptr [edi + 0x16b], 0
004fcdd7 movss dword ptr [ebp - 0x78], xmm0
004fcddc mov eax, 4
004fcde1 sub eax, dword ptr [edi + 0x30]
004fcde4 lea esi, [eax + eax*4]
004fcde7 add esi, esi
004fcde9 mov dword ptr [ebp - 0x74], esi
004fcdec push 1
004fcdee push 0xb42ef4
004fcdf3 lea ecx, [edi + 0x3c]
004fcdf6 call 0x405740
004fcdfb test al, al
004fcdfd je 0x4fce0e
004fcdff lea ecx, [edi + 0x6c]
004fce02 call 0x405330
004fce07 mov byte ptr [edi + 0x80], 1
004fce0e mov eax, dword ptr [ebp - 0x74]
004fce11 test eax, eax
004fce13 jle 0x4fce2a
004fce15 cmp dword ptr [edi + 0x70], 0
004fce19 je 0x4fce2a
004fce1b movd xmm1, eax
004fce1f lea ecx, [edi + 0x6c]
004fce22 cvtdq2ps xmm1, xmm1
004fce25 call 0x403c00
004fce2a cmp byte ptr [ebp - 0x6d], 0
004fce2e movss xmm0, dword ptr [edi + 0x2dc]
004fce36 mulss xmm0, dword ptr [0xb6a4c4]
004fce3e mov dword ptr [edi + 0xab4], 3
004fce48 movss xmm1, dword ptr [0xb6a614]
004fce50 maxss xmm1, xmm0
004fce54 movss dword ptr [edi + 0x2dc], xmm1
004fce5c movss dword ptr [edi + 0x2d8], xmm1
004fce64 je 0x4fd097
004fce6a inc dword ptr [edi + 0x30]
004fce6d lea ecx, [ebp - 0x24]
004fce70 mov byte ptr [edi + 0x308], 1
004fce77 mov dword ptr [edi + 0xb10], 2
004fce81 call 0x7a7e20
004fce86 movss xmm1, dword ptr [ebp - 0x84]
004fce8e lea ecx, [ebp - 0x24]
004fce91 mulss xmm1, dword ptr [0xb6a8cc]
004fce99 mov dword ptr [edi + 0x344], eax
004fce9f movss xmm2, dword ptr [ebp - 0x78]
004fcea4 mulss xmm2, dword ptr [0xb6a8cc]
004fceac movaps xmm0, xmm1
004fceaf movss dword ptr [ebp - 0x90], xmm1
004fceb7 addss xmm0, dword ptr [edi + 0x294]
004fcebf movss dword ptr [ebp - 0x8c], xmm1
004fcec7 movss dword ptr [ebp - 0x7c], xmm2
004fcecc movss dword ptr [ebp - 0x88], xmm2
004fced4 movss dword ptr [ebp - 0x98], xmm0
004fcedc movaps xmm0, xmm2
004fcedf addss xmm0, dword ptr [edi + 0x298]
004fcee7 movss dword ptr [ebp - 0x94], xmm0
004fceef call 0x7a7e20
004fcef4 mov ecx, dword ptr [0xbfd65c]
004fcefa push eax
004fcefb push 0
004fcefd push edi
004fcefe lea eax, [ebp - 0x8c]
004fcf04 push eax
004fcf05 lea eax, [ebp - 0x98]
004fcf0b push eax
004fcf0c push dword ptr [edi + 0x2c]
004fcf0f push dword ptr [edi + 0x28]
004fcf12 call 0x422e20
004fcf17 movss xmm0, dword ptr [edi + 0x2dc]
004fcf1f mov esi, eax
004fcf21 push 0
004fcf23 push 0xb42ef4
004fcf28 lea ecx, [esi + 0x3c]
004fcf2b movss dword ptr [esi + 0x2d8], xmm0
004fcf33 movss dword ptr [esi + 0x2dc], xmm0
004fcf3b call 0x4054f0
004fcf40 mov eax, dword ptr [ebp - 0x74]
004fcf43 test eax, eax
004fcf45 jle 0x4fcf5c
004fcf47 cmp dword ptr [esi + 0x70], 0
004fcf4b je 0x4fcf5c
004fcf4d movd xmm1, eax
004fcf51 lea ecx, [esi + 0x6c]
004fcf54 cvtdq2ps xmm1, xmm1
004fcf57 call 0x403c00
004fcf5c mov eax, dword ptr [edi + 0x30]
004fcf5f lea ecx, [esi + 0x1dc]
004fcf65 and dword ptr [esi + 0x160], 0xfffffffb
004fcf6c mov dword ptr [esi + 0x30], eax
004fcf6f mov eax, dword ptr [esi + 0x164]
004fcf75 mov dword ptr [esi + 0x164], eax
004fcf7b lea eax, [edi + 0x1dc]
004fcf81 push eax
004fcf82 mov dword ptr [esi + 0xab4], 3
004fcf8c call 0x4021a0
004fcf91 or dword ptr [esi + 0x164], 0x400
004fcf9b mov eax, dword ptr [esi + 0x160]
004fcfa1 or dword ptr [esi + 0xe68], 1
004fcfa8 movss xmm2, dword ptr [ebp - 0x84]
004fcfb0 movss xmm1, dword ptr [ebp - 0x78]
004fcfb5 mulss xmm2, dword ptr [0xb6ae88]
004fcfbd mov byte ptr [esi + 0x308], 1
004fcfc4 mulss xmm1, dword ptr [0xb6ae88]
004fcfcc mov dword ptr [esi + 0xb10], 1
004fcfd6 mov dword ptr [esi + 0x160], eax
004fcfdc movss xmm0, dword ptr [edi + 0x294]
004fcfe4 subss xmm0, dword ptr [ebp - 0x90]
004fcfec movss dword ptr [edi + 0x2b8], xmm2
004fcff4 movss dword ptr [edi + 0x2bc], xmm1
004fcffc movss dword ptr [edi + 0x294], xmm0
004fd004 movss xmm0, dword ptr [edi + 0x298]
004fd00c subss xmm0, dword ptr [ebp - 0x7c]
004fd011 movss dword ptr [edi + 0x298], xmm0
004fd019 jmp 0x4fd097
004fd01b cmp dword ptr [edi + 0xab4], 4
004fd022 jne 0x4fd097
004fd024 push 0
004fd026 push 0xb42ef4
004fd02b lea ecx, [edi + 0x3c]
004fd02e mov byte ptr [edi + 0x16b], 0
004fd035 mov dword ptr [edi + 0x2d8], 0x41200000
004fd03f call 0x4054f0
004fd044 cmp dword ptr [edi + 0x2c], 2
004fd048 mov dword ptr [edi + 0xab4], 3
004fd052 jne 0x4fd097
004fd054 mov ecx, edi
004fd056 call 0x6ad7a0
004fd05b cmp eax, 7
004fd05e jge 0x4fd097
004fd060 call 0x6c3d90
004fd065 mov ecx, dword ptr [0xbfd65c]
004fd06b push eax
004fd06c push 0
004fd06e push edi
004fd06f push 0xc02fec
004fd074 lea eax, [edi + 0x294]
004fd07a push eax
004fd07b push 0
004fd07d push 0x55
004fd07f call 0x422e20
004fd084 mov ecx, dword ptr [eax + 0x164]
004fd08a and dword ptr [eax + 0x160], 0xfffffffb
004fd091 mov dword ptr [eax + 0x164], ecx
004fd097 mov ecx, dword ptr [ebp - 0xc]
004fd09a mov dword ptr fs:[0], ecx
004fd0a1 pop ecx
004fd0a2 pop edi
004fd0a3 pop esi
004fd0a4 mov ecx, dword ptr [ebp - 0x14]
004fd0a7 xor ecx, ebp
004fd0a9 call 0x9eacd7
004fd0ae mov esp, ebp
004fd0b0 pop ebp
004fd0b1 mov esp, ebx
004fd0b3 pop ebx
004fd0b4 ret 
