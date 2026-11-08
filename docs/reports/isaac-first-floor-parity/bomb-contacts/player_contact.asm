007553e0 push ebp
007553e1 mov ebp, esp
007553e3 and esp, 0xfffffff8
007553e6 sub esp, 0xc8
007553ec mov eax, dword ptr [0xbaa3b4]
007553f1 xor eax, esp
007553f3 mov dword ptr [esp + 0xc4], eax
007553fa push esi
007553fb push edi
007553fc push dword ptr [ebp + 0xc]
007553ff mov edi, dword ptr [ebp + 8]
00755402 mov esi, ecx
00755404 push edi
00755405 push esi
00755406 call 0x800bd0
0075540b cmp eax, 1
0075540e je 0x755ebc
00755414 cmp eax, -1
00755417 jne 0x755431
00755419 xor al, al
0075541b pop edi
0075541c pop esi
0075541d mov ecx, dword ptr [esp + 0xc4]
00755424 xor ecx, esp
00755426 call 0x9eacd7
0075542b mov esp, ebp
0075542d pop ebp
0075542e ret 8
00755431 mov eax, dword ptr [edi + 0x28]
00755434 sub eax, 0xa
00755437 cmp eax, 0x3dd
0075543c ja 0x755659
00755442 mov ecx, dword ptr [edi + 0x164]
00755448 xor eax, eax
0075544a and ecx, 0x20000
00755450 or eax, ecx
00755452 je 0x755659
00755458 push 0x8000
0075545d push 0
0075545f mov ecx, edi
00755461 call 0x4122f0
00755466 test al, al
00755468 jne 0x755659
0075546e movss xmm1, dword ptr [esi + 0x2bc]
00755476 movss xmm0, dword ptr [esi + 0x2b8]
0075547e mulss xmm0, xmm0
00755482 mulss xmm1, xmm1
00755486 addss xmm0, xmm1
0075548a comiss xmm0, dword ptr [0xb6a1c8]
00755491 jbe 0x755659
00755497 movss xmm0, dword ptr [edi + 0x294]
0075549f lea ecx, [esp + 0x14]
007554a3 movss xmm1, dword ptr [edi + 0x298]
007554ab subss xmm0, dword ptr [esi + 0x294]
007554b3 subss xmm1, dword ptr [esi + 0x298]
007554bb movss dword ptr [esp + 0x14], xmm0
007554c1 movss dword ptr [esp + 0x18], xmm1
007554c7 call 0x9624f0
007554cc lea eax, [esp + 0x50]
007554d0 push eax
007554d1 lea ecx, [esi + 0x2b8]
007554d7 call 0x962560
007554dc movss xmm0, dword ptr [esp + 0x50]
007554e2 lea eax, [esp + 0x58]
007554e6 addss xmm0, dword ptr [esp + 0x14]
007554ec push eax
007554ed lea ecx, [esp + 0x4c]
007554f1 movss dword ptr [esp + 0x4c], xmm0
007554f7 movss xmm0, dword ptr [esp + 0x58]
007554fd addss xmm0, dword ptr [esp + 0x1c]
00755503 movss dword ptr [esp + 0x50], xmm0
00755509 call 0x962560
0075550e movss xmm0, dword ptr [eax]
00755512 mulss xmm0, dword ptr [0xb6a9bc]
0075551a movss dword ptr [esp + 0x14], xmm0
00755520 movss xmm0, dword ptr [eax + 4]
00755525 mulss xmm0, dword ptr [0xb6a9bc]
0075552d movss dword ptr [esp + 0x18], xmm0
00755533 test esi, esi
00755535 je 0x7555a2
00755537 mov eax, dword ptr [esi + 0x28]
0075553a movss xmm0, dword ptr [esi + 0x294]
00755542 movss xmm1, dword ptr [esi + 0x298]
0075554a mov dword ptr [esp + 0x1c], eax
0075554e mov eax, dword ptr [esi + 0x2c]
00755551 mov dword ptr [esp + 0x20], eax
00755555 mov eax, dword ptr [esi + 0x34]
00755558 mov dword ptr [esp + 0x24], eax
0075555c mov eax, dword ptr [esi + 0x38]
0075555f mov dword ptr [esp + 0x28], eax
00755563 mov eax, dword ptr [esi + 0x160]
00755569 movss dword ptr [esp + 0x2c], xmm0
0075556f and eax, 0x100
00755574 or eax, 0
00755577 movss xmm0, dword ptr [esi + 0x2b8]
0075557f movss dword ptr [esp + 0x30], xmm1
00755585 movss xmm1, dword ptr [esi + 0x2bc]
0075558d movss dword ptr [esp + 0x34], xmm0
00755593 movss dword ptr [esp + 0x38], xmm1
00755599 je 0x7555ea
0075559b mov edx, 1
007555a0 jmp 0x7555f0
007555a2 movss xmm1, dword ptr [0xc02fec]
007555aa movss xmm0, dword ptr [0xc02ff0]
007555b2 mov dword ptr [esp + 0x1c], 0
007555ba mov dword ptr [esp + 0x20], 0
007555c2 mov dword ptr [esp + 0x24], 0
007555ca mov dword ptr [esp + 0x28], 0
007555d2 movss dword ptr [esp + 0x2c], xmm1
007555d8 movss dword ptr [esp + 0x30], xmm0
007555de movss dword ptr [esp + 0x34], xmm1
007555e4 movss dword ptr [esp + 0x38], xmm0
007555ea xor edx, edx
007555ec test esi, esi
007555ee je 0x75560a
007555f0 mov eax, dword ptr [esi + 0x160]
007555f6 and eax, 0x20000000
007555fb or eax, 0
007555fe je 0x75560c
00755600 mov dword ptr [esp + 0xc], 2
00755608 jmp 0x755618
0075560a xor edx, edx
0075560c mov dword ptr [esp + 0xc], 0
00755614 test esi, esi
00755616 je 0x755631
00755618 mov ecx, dword ptr [esi + 0x164]
0075561e xor eax, eax
00755620 and ecx, 0x400000
00755626 or eax, ecx
00755628 je 0x755631
0075562a mov eax, 4
0075562f jmp 0x755633
00755631 xor eax, eax
00755633 or eax, dword ptr [esp + 0xc]
00755637 mov ecx, edi
00755639 or eax, edx
0075563b mov dword ptr [esp + 0x40], esi
0075563f push 1
00755641 mov dword ptr [esp + 0x40], eax
00755645 lea eax, [esp + 0x18]
00755649 push 0xc8
0075564e push eax
0075564f lea eax, [esp + 0x28]
00755653 push eax
00755654 call 0x68ee80
00755659 cmp dword ptr [esi + 0x130c], 0x16
00755660 jne 0x75584f
00755666 push 0
00755668 mov ecx, edi
0075566a call 0x684630
0075566f test al, al
00755671 je 0x75584f
00755677 cmp dword ptr [esi + 0x1df8], 3
0075567e jge 0x75584f
00755684 push 0
00755686 push 0x20000000
0075568b mov ecx, edi
0075568d call 0x4122f0
00755692 test al, al
00755694 jne 0x75584f
0075569a movss xmm0, dword ptr [esi + 0x14c0]
007556a2 push 0
007556a4 call 0x6c3d90
007556a9 addss xmm0, xmm0
007556ad and eax, 1
007556b0 lea eax, [eax*2 - 1]
007556b7 divss xmm0, dword ptr [esi + 0x13b8]
007556bf push eax
007556c0 push ecx
007556c1 lea eax, [esp + 0x6c]
007556c5 mov ecx, esi
007556c7 movss dword ptr [esp], xmm0
007556cc push 0xa
007556ce push eax
007556cf call 0x7836a0
007556d4 call 0x6c3d90
007556d9 mov ecx, dword ptr [esi + 0x294]
007556df mov edx, dword ptr [esi + 0x298]
007556e5 push 0
007556e7 push eax
007556e8 push 4
007556ea push esi
007556eb push 0xc02fec
007556f0 lea eax, [esp + 0x28]
007556f4 mov dword ptr [esp + 0x28], ecx
007556f8 mov ecx, dword ptr [0xbfd65c]
007556fe push eax
007556ff push 1
00755701 push 8
00755703 mov dword ptr [esp + 0x38], edx
00755707 call 0x6d0ca0
0075570c mov ecx, dword ptr [eax + 0x314]
00755712 mov dword ptr [esp + 0xc], eax
00755716 add eax, 0x314
0075571b mov dword ptr [esp + 0x50], eax
0075571f test ecx, ecx
00755721 je 0x75573b
00755723 mov dword ptr [esp + 0x48], eax
00755727 add ecx, 0x324
0075572d lea eax, [esp + 0x48]
00755731 push eax
00755732 call 0x4bc3c0
00755737 mov eax, dword ptr [esp + 0x50]
0075573b push eax
0075573c mov ecx, esi
0075573e mov dword ptr [eax], esi
00755740 call 0x4bae70
00755745 mov ecx, dword ptr [esp + 0xc]
00755749 lea edx, [esp + 0x50]
0075574d mov dword ptr [ecx + 0x28c], 0x40c00000
00755757 mov dword ptr [ecx + 0x290], 0
00755761 lea ecx, [esp + 0x58]
00755765 movss xmm0, dword ptr [edi + 0x294]
0075576d movss xmm1, dword ptr [edi + 0x298]
00755775 subss xmm0, dword ptr [esi + 0x294]
0075577d subss xmm1, dword ptr [esi + 0x298]
00755785 movss dword ptr [esp + 0x50], xmm0
0075578b movss dword ptr [esp + 0x54], xmm1
00755791 call 0x6593a0
00755796 movss xmm1, dword ptr [eax]
0075579a movss xmm0, dword ptr [eax + 4]
0075579f call 0x447a80
007557a4 mov ecx, dword ptr [esp + 0xc]
007557a8 lea edx, [esp + 0x68]
007557ac mulss xmm0, dword ptr [0xb6aa84]
007557b4 push 1
007557b6 push 0
007557b8 push 0xff
007557bd mov dword ptr [ecx + 0x2a4], 0
007557c7 mov dword ptr [ecx + 0x2a8], 0xc1600000
007557d1 mov eax, dword ptr [ecx]
007557d3 push -1
007557d5 push edx
007557d6 movss dword ptr [ecx + 0x388], xmm0
007557de call dword ptr [eax + 0x38]
007557e1 mov ecx, dword ptr [esp + 0xc]
007557e5 mov eax, dword ptr [esi + 0xd8]
007557eb push ecx
007557ec mov dword ptr [ecx + 0xd8], eax
007557f2 mov eax, dword ptr [esi + 0xdc]
007557f8 mov dword ptr [ecx + 0xdc], eax
007557fe movups xmm0, xmmword ptr [esp + 0x9c]
00755806 mov eax, dword ptr [ecx]
00755808 movups xmmword ptr [ecx + 0x360], xmm0
0075580f movss xmm0, dword ptr [esp + 0xac]
00755818 movss dword ptr [esp], xmm0
0075581d call dword ptr [eax + 0x3c]
00755820 mov ecx, dword ptr [esp + 0xc]
00755824 mov eax, dword ptr [ecx + 0x160]
0075582a or dword ptr [ecx + 0x164], 4
00755831 mov dword ptr [ecx + 0x160], eax
00755837 call 0x8c0d00
0075583c mov ecx, dword ptr [esp + 0xc]
00755840 mov eax, dword ptr [ecx]
00755842 call dword ptr [eax + 0xc]
00755845 mov dword ptr [esi + 0x1df8], 9
0075584f lea ecx, [esi + 0x1450]
00755855 push 0x271
0075585a call 0x88b570
0075585f test al, al
00755861 je 0x755b5f
00755867 mov ecx, dword ptr [edi + 0x28]
0075586a lea eax, [ecx - 0xa]
0075586d cmp eax, 0x3dd
00755872 ja 0x755976
00755878 push 0
0075587a push 0x20000000
0075587f mov ecx, edi
00755881 call 0x4122f0
00755886 test al, al
00755888 jne 0x755973
0075588e lea ecx, [esi + 0x1d60]
00755894 push edi
00755895 call 0x422d00
0075589a test al, al
0075589c jne 0x755b5f
007558a2 mov ecx, edi
007558a4 call 0x68d5a0
007558a9 push eax
007558aa lea ecx, [esi + 0x1d60]
007558b0 call 0x422c30
007558b5 mov eax, dword ptr [esi + 0x28]
007558b8 movss xmm0, dword ptr [esi + 0x294]
007558c0 movss xmm1, dword ptr [esi + 0x298]
007558c8 mov ecx, dword ptr [esi + 0x160]
007558ce mov edx, dword ptr [esi + 0x164]
007558d4 mov dword ptr [esp + 0x1c], eax
007558d8 mov eax, dword ptr [esi + 0x2c]
007558db mov dword ptr [esp + 0x20], eax
007558df mov eax, dword ptr [esi + 0x34]
007558e2 mov dword ptr [esp + 0x24], eax
007558e6 mov eax, dword ptr [esi + 0x38]
007558e9 mov dword ptr [esp + 0x28], eax
007558ed mov eax, ecx
007558ef movss dword ptr [esp + 0x2c], xmm0
007558f5 and eax, 0x100
007558fa or eax, 0
007558fd movss xmm0, dword ptr [esi + 0x2b8]
00755905 movss dword ptr [esp + 0x30], xmm1
0075590b movss xmm1, dword ptr [esi + 0x2bc]
00755913 movss dword ptr [esp + 0x34], xmm0
00755919 movss dword ptr [esp + 0x38], xmm1
0075591f mov dword ptr [esp + 0xc], 1
00755927 jne 0x755931
00755929 mov dword ptr [esp + 0xc], 0
00755931 and ecx, 0x20000000
00755937 or ecx, 0
0075593a je 0x755943
0075593c mov ecx, 2
00755941 jmp 0x755945
00755943 xor ecx, ecx
00755945 and edx, 0x400000
0075594b xor eax, eax
0075594d or eax, edx
0075594f je 0x755958
00755951 mov eax, 4
00755956 jmp 0x75595a
00755958 xor eax, eax
0075595a or eax, ecx
0075595c lea ecx, [esp + 0x1c]
00755960 or eax, dword ptr [esp + 0xc]
00755964 push 0x1e
00755966 push ecx
00755967 push 0
00755969 push 0x1000000
0075596e jmp 0x755b48
00755973 mov ecx, dword ptr [edi + 0x28]
00755976 cmp ecx, 6
00755979 jne 0x755a5f
0075597f lea ecx, [esi + 0x1d60]
00755985 push edi
00755986 call 0x422d00
0075598b test al, al
0075598d jne 0x755b5f
00755993 mov ecx, edi
00755995 call 0x68d5a0
0075599a push eax
0075599b lea ecx, [esi + 0x1d60]
007559a1 call 0x422c30
007559a6 mov eax, dword ptr [esi + 0x28]
007559a9 movss xmm0, dword ptr [esi + 0x294]
007559b1 movss xmm1, dword ptr [esi + 0x298]
007559b9 mov ecx, dword ptr [esi + 0x160]
007559bf mov edx, dword ptr [esi + 0x164]
007559c5 mov dword ptr [esp + 0x1c], eax
007559c9 mov eax, dword ptr [esi + 0x2c]
007559cc mov dword ptr [esp + 0x20], eax
007559d0 mov eax, dword ptr [esi + 0x34]
007559d3 mov dword ptr [esp + 0x24], eax
007559d7 mov eax, dword ptr [esi + 0x38]
007559da mov dword ptr [esp + 0x28], eax
007559de mov eax, ecx
007559e0 movss dword ptr [esp + 0x2c], xmm0
007559e6 and eax, 0x100
007559eb or eax, 0
007559ee movss xmm0, dword ptr [esi + 0x2b8]
007559f6 movss dword ptr [esp + 0x30], xmm1
007559fc movss xmm1, dword ptr [esi + 0x2bc]
00755a04 movss dword ptr [esp + 0x34], xmm0
00755a0a movss dword ptr [esp + 0x38], xmm1
00755a10 mov dword ptr [esp + 0xc], 1
00755a18 jne 0x755a22
00755a1a mov dword ptr [esp + 0xc], 0
00755a22 and ecx, 0x20000000
00755a28 or ecx, 0
00755a2b je 0x755a34
00755a2d mov ecx, 2
00755a32 jmp 0x755a36
00755a34 xor ecx, ecx
00755a36 and edx, 0x400000
00755a3c xor eax, eax
00755a3e or eax, edx
00755a40 je 0x755a52
00755a42 mov eax, 4
00755a47 or eax, ecx
00755a49 or eax, dword ptr [esp + 0xc]
00755a4d jmp 0x755b3a
00755a52 xor eax, eax
00755a54 or eax, ecx
00755a56 or eax, dword ptr [esp + 0xc]
00755a5a jmp 0x755b3a
00755a5f cmp ecx, 5
00755a62 jne 0x755b5f
00755a68 lea ecx, [esi + 0x1d60]
00755a6e push edi
00755a6f call 0x422d00
00755a74 test al, al
00755a76 jne 0x755b5f
00755a7c mov ecx, edi
00755a7e call 0x68d5a0
00755a83 push eax
00755a84 lea ecx, [esi + 0x1d60]
00755a8a call 0x422c30
00755a8f mov eax, dword ptr [esi + 0x28]
00755a92 movss xmm0, dword ptr [esi + 0x294]
00755a9a movss xmm1, dword ptr [esi + 0x298]
00755aa2 mov ecx, dword ptr [esi + 0x160]
00755aa8 mov edx, dword ptr [esi + 0x164]
00755aae mov dword ptr [esp + 0x1c], eax
00755ab2 mov eax, dword ptr [esi + 0x2c]
00755ab5 mov dword ptr [esp + 0x20], eax
00755ab9 mov eax, dword ptr [esi + 0x34]
00755abc mov dword ptr [esp + 0x24], eax
00755ac0 mov eax, dword ptr [esi + 0x38]
00755ac3 mov dword ptr [esp + 0x28], eax
00755ac7 mov eax, ecx
00755ac9 movss dword ptr [esp + 0x2c], xmm0
00755acf and eax, 0x100
00755ad4 or eax, 0
00755ad7 movss xmm0, dword ptr [esi + 0x2b8]
00755adf movss dword ptr [esp + 0x30], xmm1
00755ae5 movss xmm1, dword ptr [esi + 0x2bc]
00755aed movss dword ptr [esp + 0x34], xmm0
00755af3 movss dword ptr [esp + 0x38], xmm1
00755af9 mov dword ptr [esp + 0xc], 1
00755b01 jne 0x755b0b
00755b03 mov dword ptr [esp + 0xc], 0
00755b0b and ecx, 0x20000000
00755b11 or ecx, 0
00755b14 je 0x755b1d
00755b16 mov ecx, 2
00755b1b jmp 0x755b1f
00755b1d xor ecx, ecx
00755b1f and edx, 0x400000
00755b25 xor eax, eax
00755b27 or eax, edx
00755b29 je 0x755b32
00755b2b mov eax, 4
00755b30 jmp 0x755b34
00755b32 xor eax, eax
00755b34 or eax, ecx
00755b36 or eax, dword ptr [esp + 0xc]
00755b3a push 0x1e
00755b3c lea ecx, [esp + 0x20]
00755b40 push ecx
00755b41 push 0
00755b43 push 0x1000004
00755b48 mov dword ptr [esp + 0x4c], eax
00755b4c mov eax, dword ptr [edi]
00755b4e push ecx
00755b4f mov ecx, edi
00755b51 mov dword ptr [esp], 0x42a00000
00755b58 mov dword ptr [esp + 0x54], esi
00755b5c call dword ptr [eax + 0x20]
00755b5f cmp dword ptr [esi + 0x130c], 0x28
00755b66 jne 0x755bbe
00755b68 cmp dword ptr [edi + 0x28], 1
00755b6c jne 0x755bbe
00755b6e cmp dword ptr [edi + 0x130c], 0x23
00755b75 jne 0x755bbe
00755b77 push 0x6000000
00755b7c push 0
00755b7e mov ecx, edi
00755b80 call 0x4122f0
00755b85 test al, al
00755b87 jne 0x755ebc
00755b8d mov eax, dword ptr [0xbfd65c]
00755b92 mov ecx, dword ptr [eax + 0x18190]
00755b98 cmp byte ptr [ecx], 0
00755b9b je 0x755ebc
00755ba1 mov eax, dword ptr [eax + 0x1a30dc]
00755ba7 sub eax, dword ptr [ecx + 0x11f0]
00755bad cmp eax, 1
00755bb0 jle 0x755ebc
00755bb6 push edi
00755bb7 mov ecx, esi
00755bb9 call 0x793ad0
00755bbe mov eax, dword ptr [esi + 0x1e2c]
00755bc4 cmp eax, 2
00755bc7 jle 0x755e15
00755bcd mov ecx, dword ptr [edi + 0x28]
00755bd0 lea eax, [ecx - 0xa]
00755bd3 cmp eax, 0x3dd
00755bd8 jbe 0x755ebc
00755bde cmp ecx, 9
00755be1 je 0x755ebc
00755be7 push 0
00755be9 mov ecx, edi
00755beb mov byte ptr [esp + 0x17], 0
00755bf0 call 0x684630
00755bf5 test al, al
00755bf7 je 0x75632a
00755bfd xorps xmm0, xmm0
00755c00 lea ecx, [esi + 0x1450]
00755c06 push 0x251
00755c0b movss dword ptr [esp + 0x10], xmm0
00755c11 call 0x88b570
00755c16 test al, al
00755c18 jne 0x755c3a
00755c1a cmp dword ptr [esi + 0x17a8], 0
00755c21 lea ecx, [esi + 0x1450]
00755c27 push 0x2ca
00755c2c setg byte ptr [esp + 0x17]
00755c31 call 0x88b570
00755c36 test al, al
00755c38 je 0x755c3f
00755c3a mov byte ptr [esp + 0x13], 1
00755c3f push 0x4d
00755c41 lea ecx, [esi + 0x1450]
00755c47 call 0x88b570
00755c4c test al, al
00755c4e jne 0x755c9c
00755c50 push 0x5d
00755c52 lea ecx, [esi + 0x1450]
00755c58 call 0x88b570
00755c5d test al, al
00755c5f jne 0x755c9c
00755c61 push 0x53
00755c63 lea ecx, [esi + 0x1450]
00755c69 call 0x88b570
00755c6e test al, al
00755c70 jne 0x755c9c
00755c72 push 0x12b
00755c77 lea ecx, [esi + 0x1450]
00755c7d call 0x88b570
00755c82 test al, al
00755c84 je 0x755cc1
00755c86 push 0x12b
00755c8b lea ecx, [esi + 0x1450]
00755c91 call 0x88b7c0
00755c96 cmp dword ptr [eax + 8], 0
00755c9a je 0x755cc1
00755c9c movss xmm0, dword ptr [0xb6a9c8]
00755ca4 movss dword ptr [esp + 0xc], xmm0
00755caa movss xmm0, dword ptr [0xb6aa3c]
00755cb2 comiss xmm0, dword ptr [edi + 0x2d8]
00755cb9 jb 0x755cc1
00755cbb movss dword ptr [esp + 0xc], xmm0
00755cc1 push 0
00755cc3 push 0x1e
00755cc5 mov ecx, esi
00755cc7 call 0x73af30
00755ccc test al, al
00755cce je 0x755ce4
00755cd0 movss xmm0, dword ptr [esp + 0xc]
00755cd6 addss xmm0, dword ptr [0xb6a98c]
00755cde movss dword ptr [esp + 0xc], xmm0
00755ce4 push 0
00755ce6 push 0xd
00755ce8 mov ecx, esi
00755cea call 0x73af30
00755cef test al, al
00755cf1 je 0x755d07
00755cf3 movss xmm0, dword ptr [esp + 0xc]
00755cf9 addss xmm0, dword ptr [0xb6a98c]
00755d01 movss dword ptr [esp + 0xc], xmm0
00755d07 push 0
00755d09 push 0x189
00755d0e mov ecx, esi
00755d10 call 0x73af30
00755d15 test al, al
00755d17 je 0x755d2d
00755d19 movss xmm0, dword ptr [esp + 0xc]
00755d1f addss xmm0, dword ptr [0xb6a98c]
00755d27 movss dword ptr [esp + 0xc], xmm0
00755d2d cmp dword ptr [esi + 0x130c], 0x28
00755d34 jne 0x755d40
00755d36 mov ecx, dword ptr [esi + 0x1d80]
00755d3c test ecx, ecx
00755d3e jne 0x755d42
00755d40 mov ecx, esi
00755d42 push 0
00755d44 push 0x114
00755d49 call 0x73af30
00755d4e test al, al
00755d50 je 0x755d6a
00755d52 movss xmm0, dword ptr [esi + 0x14c0]
00755d5a addss xmm0, xmm0
00755d5e addss xmm0, dword ptr [esp + 0xc]
00755d64 movss dword ptr [esp + 0xc], xmm0
00755d6a push 0
00755d6c push 0xca
00755d71 mov ecx, esi
00755d73 call 0x73af30
00755d78 test al, al
00755d7a je 0x755f30
00755d80 mov eax, dword ptr [esi + 0x28]
00755d83 movss xmm0, dword ptr [esi + 0x294]
00755d8b movss xmm1, dword ptr [esi + 0x298]
00755d93 mov ecx, dword ptr [esi + 0x160]
00755d99 mov edx, dword ptr [esi + 0x164]
00755d9f mov dword ptr [esp + 0x1c], eax
00755da3 mov eax, dword ptr [esi + 0x2c]
00755da6 mov dword ptr [esp + 0x20], eax
00755daa mov eax, dword ptr [esi + 0x34]
00755dad mov dword ptr [esp + 0x24], eax
00755db1 mov eax, dword ptr [esi + 0x38]
00755db4 mov dword ptr [esp + 0x28], eax
00755db8 mov eax, ecx
00755dba movss dword ptr [esp + 0x2c], xmm0
00755dc0 and eax, 0x100
00755dc5 or eax, 0
00755dc8 movss xmm0, dword ptr [esi + 0x2b8]
00755dd0 movss dword ptr [esp + 0x30], xmm1
00755dd6 movss xmm1, dword ptr [esi + 0x2bc]
00755dde movss dword ptr [esp + 0x34], xmm0
00755de4 movss dword ptr [esp + 0x38], xmm1
00755dea mov dword ptr [esp + 0x48], 1
00755df2 jne 0x755dfc
00755df4 mov dword ptr [esp + 0x48], 0
00755dfc and ecx, 0x20000000
00755e02 or ecx, 0
00755e05 je 0x755ed4
00755e0b mov ecx, 2
00755e10 jmp 0x755ed6
00755e15 cmp eax, 1
00755e18 jne 0x755be7
00755e1e mov ecx, dword ptr [edi + 0x28]
00755e21 cmp ecx, 9
00755e24 je 0x755ebc
00755e2a lea eax, [ecx - 0xa]
00755e2d cmp eax, 0x3dd
00755e32 jbe 0x755e3d
00755e34 cmp ecx, 4
00755e37 jne 0x755be7
00755e3d push edi
00755e3e mov ecx, esi
00755e40 call 0x793ad0
00755e45 test al, al
00755e47 je 0x755be7
00755e4d mov dword ptr [esi + 0x1534], 0x2c5
00755e57 mov dword ptr [esi + 0x1e30], 0x3c
00755e61 mov dword ptr [esi + 0x1e2c], 2
00755e6b call 0x6c3d90
00755e70 movss xmm2, dword ptr [0xb6a614]
00755e78 push ecx
00755e79 movd xmm0, eax
00755e7d cvtdq2pd xmm0, xmm0
00755e81 shr eax, 0x1f
00755e84 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
00755e8d cvtpd2ps xmm0, xmm0
00755e91 mulss xmm0, dword ptr [0xb6a19c]
00755e99 mulss xmm0, dword ptr [0xb6a350]
00755ea1 addss xmm0, dword ptr [0xb6a5a4]
00755ea9 movss dword ptr [esp], xmm0
00755eae push 0
00755eb0 push 2
00755eb2 push 0xf9
00755eb7 call 0x68d750
00755ebc mov al, 1
00755ebe pop edi
00755ebf pop esi
00755ec0 mov ecx, dword ptr [esp + 0xc4]
00755ec7 xor ecx, esp
00755ec9 call 0x9eacd7
00755ece mov esp, ebp
00755ed0 pop ebp
00755ed1 ret 8
