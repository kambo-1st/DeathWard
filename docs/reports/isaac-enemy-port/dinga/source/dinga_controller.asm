0050a450 push ebp
0050a451 mov ebp, esp
0050a453 and esp, 0xfffffff8
0050a456 sub esp, 0x10c
0050a45c mov eax, dword ptr [0xbaa3b4]
0050a461 xor eax, esp
0050a463 mov dword ptr [esp + 0x108], eax
0050a46a push ebx
0050a46b push esi
0050a46c mov esi, ecx
0050a46e push edi
0050a46f mov dword ptr [esp + 0x20], esi
0050a473 mov eax, dword ptr [esi + 0xab4]
0050a479 test eax, eax
0050a47b jne 0x50a549
0050a481 mov eax, dword ptr [esi + 0x28]
0050a484 mov dword ptr [esi + 0xab4], 4
0050a48e cmp eax, 0xdf
0050a493 jne 0x50a4e5
0050a495 movaps xmm1, xmmword ptr [0xb6bd30]
0050a49c lea ecx, [esi + 0x1dc]
0050a4a2 lea eax, [esp + 0x3c]
0050a4a6 mov dword ptr [esp + 0x5c], 0x3e828283
0050a4ae mov dword ptr [esp + 0x60], 0x3e24a4a5
0050a4b6 xorps xmm0, xmm0
0050a4b9 mov dword ptr [esp + 0x64], 0x3e0c8c8d
0050a4c1 cmp ecx, eax
0050a4c3 je 0x50ad99
0050a4c9 mov eax, dword ptr [esp + 0x64]
0050a4cd movups xmmword ptr [ecx + 0x10], xmm0
0050a4d1 movq xmm0, qword ptr [esp + 0x5c]
0050a4d7 movq qword ptr [ecx + 0x20], xmm0
0050a4dc movups xmmword ptr [ecx], xmm1
0050a4df mov dword ptr [ecx + 0x28], eax
0050a4e2 mov eax, dword ptr [esi + 0x28]
0050a4e5 cmp eax, 0x39
0050a4e8 jne 0x50ad99
0050a4ee cmp dword ptr [esi + 0x2c], 2
0050a4f2 jne 0x50ad99
0050a4f8 add esi, 0x1dc
0050a4fe cmp esi, 0xbc52ac
0050a504 je 0x50ad99
0050a50a movups xmm0, xmmword ptr [0xbc52ac]
0050a511 movups xmmword ptr [esi], xmm0
0050a514 movups xmm0, xmmword ptr [0xbc52bc]
0050a51b movups xmmword ptr [esi + 0x10], xmm0
0050a51f movq xmm0, qword ptr [0xbc52cc]
0050a527 movq qword ptr [esi + 0x20], xmm0
0050a52c mov eax, dword ptr [0xbc52d4]
0050a531 mov dword ptr [esi + 0x28], eax
0050a534 pop edi
0050a535 pop esi
0050a536 pop ebx
0050a537 mov ecx, dword ptr [esp + 0x108]
0050a53e xor ecx, esp
0050a540 call 0x9eacd7
0050a545 mov esp, ebp
0050a547 pop ebp
0050a548 ret 
0050a549 movss xmm0, dword ptr [esi + 0x2c4]
0050a551 mulss xmm0, dword ptr [0xb6a560]
0050a559 movss dword ptr [esi + 0x2c4], xmm0
0050a561 cmp eax, 4
0050a564 jne 0x50a6bb
0050a56a mov eax, dword ptr [esi + 0x160]
0050a570 and eax, 0x1000800
0050a575 or eax, 0
0050a578 je 0x50a5c8
0050a57a cmp dword ptr [esi + 0xe6c], -1
0050a581 jne 0x50a5c8
0050a583 call 0x695680
0050a588 push 0
0050a58a mov ecx, dword ptr [eax + 0x294]
0050a590 mov eax, dword ptr [eax + 0x298]
0050a596 mov dword ptr [esp + 0x28], eax
0050a59a lea eax, [esp + 0x24]
0050a59e mov dword ptr [esp + 0x24], ecx
0050a5a2 lea ecx, [esi + 0x364]
0050a5a8 push eax
0050a5a9 call 0x7a4830
0050a5ae movss xmm0, dword ptr [esi + 0x2c4]
0050a5b6 mulss xmm0, dword ptr [0xb6a560]
0050a5be movss dword ptr [esi + 0x2c4], xmm0
0050a5c6 jmp 0x50a5d5
0050a5c8 push 0
0050a5ca lea ecx, [esi + 0x364]
0050a5d0 call 0x7a6180
0050a5d5 cmp dword ptr [esi + 0xe6c], -1
0050a5dc je 0x50a616
0050a5de movss xmm1, dword ptr [0xb6accc]
0050a5e6 mov ecx, esi
0050a5e8 push 7
0050a5ea push 0
0050a5ec call 0x6a15a0
0050a5f1 test al, al
0050a5f3 jne 0x50a634
0050a5f5 push 9
0050a5f7 mov ecx, esi
0050a5f9 call 0x6af050
0050a5fe test al, al
0050a600 jne 0x50a634
0050a602 push 0
0050a604 push 0xb42050
0050a609 lea ecx, [esi + 0x3c]
0050a60c call 0x4054f0
0050a611 jmp 0x50aaac
0050a616 call 0x6c3d90
0050a61b xor edx, edx
0050a61d mov ecx, 0x1e
0050a622 div ecx
0050a624 test edx, edx
0050a626 jne 0x50a6a7
0050a628 mov ecx, esi
0050a62a call 0x6ad7a0
0050a62f cmp eax, 8
0050a632 jge 0x50a6a7
0050a634 mov eax, dword ptr [esi + 0x160]
0050a63a and eax, 0x1000a00
0050a63f or eax, 0
0050a642 jne 0x50a6a7
0050a644 cmp dword ptr [esi + 0xe6c], -1
0050a64b mov dword ptr [esi + 0xab4], 8
0050a655 mov dword ptr [esi + 0x360], eax
0050a65b jne 0x50a677
0050a65d movss xmm0, dword ptr [0xc02fec]
0050a665 movss dword ptr [esi + 0xe70], xmm0
0050a66d movss xmm0, dword ptr [0xc02ff0]
0050a675 jmp 0x50a69f
0050a677 movss xmm2, dword ptr [0xb6a2cc]
0050a67f lea eax, [esp + 0x20]
0050a683 push eax
0050a684 mov ecx, esi
0050a686 call 0x6af380
0050a68b movss xmm0, dword ptr [esp + 0x20]
0050a691 movss dword ptr [esi + 0xe70], xmm0
0050a699 movss xmm0, dword ptr [esp + 0x24]
0050a69f movss dword ptr [esi + 0xe74], xmm0
0050a6a7 push 0
0050a6a9 push 0xb42050
0050a6ae lea ecx, [esi + 0x3c]
0050a6b1 call 0x4054f0
0050a6b6 jmp 0x50aaac
0050a6bb push 0
0050a6bd push 0xb40510
0050a6c2 lea ecx, [esi + 0x3c]
0050a6c5 call 0x4054f0
0050a6ca cmp dword ptr [esi + 0x70], 0
0050a6ce lea edi, [esi + 0x6c]
0050a6d1 je 0x50aa9c
0050a6d7 push 0xb400ac
0050a6dc mov ecx, edi
0050a6de call 0x405e90
0050a6e3 test al, al
0050a6e5 je 0x50a704
0050a6e7 push ecx
0050a6e8 mov dword ptr [esp], 0x3f800000
0050a6ef push 0
0050a6f1 push 2
0050a6f3 push ecx
0050a6f4 mov dword ptr [esp], 0x3f4ccccd
0050a6fb mov ecx, esi
0050a6fd push 0x30
0050a6ff call 0x6ad720
0050a704 cmp dword ptr [esi + 0x70], 0
0050a708 je 0x50aa9c
0050a70e push 0xb400ac
0050a713 mov ecx, edi
0050a715 call 0x405e90
0050a71a test al, al
0050a71c je 0x50aa8d
0050a722 mov eax, dword ptr [esi + 0x28]
0050a725 cmp eax, 0x39
0050a728 jne 0x50a7c3
0050a72e lea ecx, [esp + 0x68]
0050a732 call 0x430d70
0050a737 cmp dword ptr [esi + 0x2c], 2
0050a73b lea ecx, [esp + 0x68]
0050a73f push ecx
0050a740 lea eax, [esi + 0x294]
0050a746 mov dword ptr [esp + 0x80], 0x3fb33333
0050a751 lea ecx, [esp + 0x24]
0050a755 jne 0x50a7a3
0050a757 or dword ptr [esp + 0xc4], 0x2000
0050a762 or dword ptr [esp + 0xc8], 0x400
0050a76d push 9
0050a76f push ecx
0050a770 push eax
0050a771 mov ecx, esi
0050a773 mov dword ptr [esp + 0x84], 0xbd8f5c29
0050a77e mov dword ptr [esp + 0x90], 0x3ec90fdb
0050a789 mov dword ptr [esp + 0x30], 0x41000000
0050a791 mov dword ptr [esp + 0x34], 0x41000000
0050a799 call 0x6a1a20
0050a79e jmp 0x50aa8d
0050a7a3 push 8
0050a7a5 push ecx
0050a7a6 push eax
0050a7a7 mov ecx, esi
0050a7a9 mov dword ptr [esp + 0x30], 0x41200000
0050a7b1 mov dword ptr [esp + 0x34], 0
0050a7b9 call 0x6a1a20
0050a7be jmp 0x50aa8d
0050a7c3 cmp eax, 0xdf
0050a7c8 jne 0x50aa8d
0050a7ce mov ecx, esi
0050a7d0 call 0x6ad7a0
0050a7d5 cmp eax, 6
0050a7d8 jge 0x50a906
0050a7de cmp dword ptr [esi + 0xe6c], -1
0050a7e5 je 0x50a7fc
0050a7e7 push 0xc02fec
0050a7ec lea ecx, [esi + 0xe70]
0050a7f2 call 0x962c70
0050a7f7 movzx edx, al
0050a7fa jmp 0x50a810
0050a7fc call 0x6c3d90
0050a801 xor edx, edx
0050a803 mov ecx, 7
0050a808 div ecx
0050a80a neg edx
0050a80c sbb edx, edx
0050a80e neg edx
0050a810 test edx, edx
0050a812 je 0x50a906
0050a818 lea eax, [esp + 0x10]
0050a81c push eax
0050a81d call 0x659290
0050a822 add esp, 4
0050a825 movss xmm2, dword ptr [eax]
0050a829 movss xmm1, dword ptr [eax + 4]
0050a82e mulss xmm2, dword ptr [0xb6aa0c]
0050a836 mulss xmm1, dword ptr [0xb6aa0c]
0050a83e movss dword ptr [esp + 0x18], xmm2
0050a844 movss dword ptr [esp + 0x28], xmm1
0050a84a call 0x6c3d90
0050a84f mov ecx, dword ptr [0xbfd65c]
0050a855 lea edi, [esi + 0x294]
0050a85b push 0
0050a85d push eax
0050a85e movaps xmm0, xmm2
0050a861 mov dword ptr [esp + 0x24], edi
0050a865 addss xmm0, dword ptr [edi]
0050a869 push 0
0050a86b push esi
0050a86c push 0xc02fec
0050a871 lea eax, [esp + 0x24]
0050a875 movss dword ptr [esp + 0x24], xmm0
0050a87b movaps xmm0, xmm1
0050a87e addss xmm0, dword ptr [edi + 4]
0050a883 push eax
0050a884 push 0
0050a886 push 0xd9
0050a88b movss dword ptr [esp + 0x34], xmm0
0050a891 call 0x6d0ca0
0050a896 mov ecx, dword ptr [eax + 0x164]
0050a89c and dword ptr [eax + 0x160], 0xfffffffb
0050a8a3 mov dword ptr [eax + 0x164], ecx
0050a8a9 call 0x6c3d90
0050a8ae movss xmm0, dword ptr [edi]
0050a8b2 subss xmm0, dword ptr [esp + 0x18]
0050a8b8 mov ecx, dword ptr [0xbfd65c]
0050a8be push 0
0050a8c0 push eax
0050a8c1 push 0
0050a8c3 push esi
0050a8c4 movss dword ptr [esp + 0x20], xmm0
0050a8ca lea eax, [esp + 0x20]
0050a8ce movss xmm0, dword ptr [edi + 4]
0050a8d3 subss xmm0, dword ptr [esp + 0x38]
0050a8d9 push 0xc02fec
0050a8de push eax
0050a8df push 0
0050a8e1 push 0xd9
0050a8e6 movss dword ptr [esp + 0x34], xmm0
0050a8ec call 0x6d0ca0
0050a8f1 mov ecx, dword ptr [eax + 0x164]
0050a8f7 and dword ptr [eax + 0x160], 0xfffffffb
0050a8fe mov dword ptr [eax + 0x164], ecx
0050a904 jmp 0x50a950
0050a906 lea ecx, [esp + 0x68]
0050a90a call 0x430d70
0050a90f lea ecx, [esp + 0x68]
0050a913 mov dword ptr [esp + 0x7c], 0x3fb33333
0050a91b push ecx
0050a91c push 8
0050a91e lea ecx, [esp + 0x18]
0050a922 mov dword ptr [esp + 0x104], 3
0050a92d lea eax, [esi + 0x294]
0050a933 mov dword ptr [esp + 0x18], 0x41200000
0050a93b push ecx
0050a93c push eax
0050a93d mov ecx, esi
0050a93f mov dword ptr [esp + 0x24], 0
0050a947 mov dword ptr [esp + 0x2c], eax
0050a94b call 0x6a1a20
0050a950 push 0
0050a952 push 0
0050a954 push -1
0050a956 push -1
0050a958 push 0xd9
0050a95d lea eax, [esp + 0x40]
0050a961 push eax
0050a962 mov eax, dword ptr [0xbfd65c]
0050a967 mov ecx, dword ptr [eax + 0x18190]
0050a96d add ecx, 0x1218
0050a973 call 0x415ed0
0050a978 xor ebx, ebx
0050a97a cmp dword ptr [esp + 0x38], ebx
0050a97e jbe 0x50aa7a
0050a984 mov esi, dword ptr [esp + 0x1c]
0050a988 nop dword ptr [eax + eax]
0050a990 mov eax, dword ptr [esp + 0x30]
0050a994 mov edi, dword ptr [eax + ebx*4]
0050a997 movss xmm1, dword ptr [edi + 0x298]
0050a99f subss xmm1, dword ptr [esi + 4]
0050a9a4 movss xmm2, dword ptr [edi + 0x294]
0050a9ac subss xmm2, dword ptr [esi]
0050a9b0 movaps xmm0, xmm1
0050a9b3 movss dword ptr [esp + 0x18], xmm1
0050a9b9 mulss xmm0, xmm1
0050a9bd movaps xmm1, xmm2
0050a9c0 movss dword ptr [esp + 0x1c], xmm2
0050a9c6 mulss xmm1, xmm2
0050a9ca addss xmm0, xmm1
0050a9ce call 0x4228c0
0050a9d3 movss xmm2, dword ptr [0xb6ab58]
0050a9db movaps xmm3, xmm0
0050a9de xorps xmm1, xmm1
0050a9e1 subss xmm2, xmm3
0050a9e5 comiss xmm3, xmm1
0050a9e8 jbe 0x50aa13
0050a9ea xorps xmm0, xmm0
0050a9ed maxss xmm0, xmm2
0050a9f1 movss xmm2, dword ptr [esp + 0x1c]
0050a9f7 mulss xmm0, dword ptr [0xb6a2cc]
0050a9ff divss xmm0, xmm3
0050aa03 movss xmm3, dword ptr [esp + 0x18]
0050aa09 mulss xmm2, xmm0
0050aa0d mulss xmm3, xmm0
0050aa11 jmp 0x50aa1f
0050aa13 movss xmm2, dword ptr [esp + 0x1c]
0050aa19 movss xmm3, dword ptr [esp + 0x18]
0050aa1f movss xmm4, dword ptr [edi + 0x2c4]
0050aa27 ucomiss xmm4, xmm1
0050aa2a lahf 
0050aa2b test ah, 0x44
0050aa2e jnp 0x50aa6b
0050aa30 movss xmm1, dword ptr [edi + 0x2f4]
0050aa38 movaps xmm0, xmm1
0050aa3b mulss xmm1, xmm3
0050aa3f mulss xmm0, xmm2
0050aa43 divss xmm1, xmm4
0050aa47 divss xmm0, xmm4
0050aa4b addss xmm1, dword ptr [edi + 0x2bc]
0050aa53 addss xmm0, dword ptr [edi + 0x2b8]
0050aa5b movss dword ptr [edi + 0x2bc], xmm1
0050aa63 movss dword ptr [edi + 0x2b8], xmm0
0050aa6b inc ebx
0050aa6c cmp ebx, dword ptr [esp + 0x38]
0050aa70 jb 0x50a990
0050aa76 mov esi, dword ptr [esp + 0x20]
0050aa7a cmp byte ptr [esp + 0x2c], 0
0050aa7f jne 0x50aa8d
0050aa81 push dword ptr [esp + 0x30]
0050aa85 call 0x9eace5
0050aa8a add esp, 4
0050aa8d cmp dword ptr [esi + 0x70], 0
0050aa91 je 0x50aa9c
0050aa93 cmp byte ptr [esi + 0x80], 0
0050aa9a jne 0x50aaa6
0050aa9c mov dword ptr [esi + 0xab4], 4
0050aaa6 inc dword ptr [esi + 0x360]
0050aaac cmp dword ptr [esi + 0x28], 0xdf
0050aab3 movss xmm1, dword ptr [0xb6a19c]
0050aabb jne 0x50ab26
0050aabd call 0x6c3d90
0050aac2 xor edx, edx
0050aac4 mov ecx, 0xa
0050aac9 div ecx
0050aacb test edx, edx
0050aacd jne 0x50ab26
0050aacf call 0x6c3d90
0050aad4 push ecx
0050aad5 mov ecx, esi
0050aad7 movd xmm0, eax
0050aadb cvtdq2pd xmm0, xmm0
0050aadf shr eax, 0x1f
0050aae2 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
0050aaeb cvtpd2ps xmm0, xmm0
0050aaef mulss xmm0, xmm1
0050aaf3 addss xmm0, dword ptr [0xb6a350]
0050aafb movss dword ptr [esp], xmm0
0050ab00 call 0x68d7b0
0050ab05 push 1
0050ab07 push 0
0050ab09 push 0xff
0050ab0e mov edx, dword ptr [eax]
0050ab10 lea ecx, [esi + 0x1dc]
0050ab16 push -1
0050ab18 push ecx
0050ab19 mov ecx, eax
0050ab1b call dword ptr [edx + 0x38]
0050ab1e movss xmm1, dword ptr [0xb6a19c]
0050ab26 cmp byte ptr [esi + 0x16b], 0
0050ab2d je 0x50ad99
0050ab33 cmp word ptr [esi + 0xbc6], 0
0050ab3b jne 0x50ad99
0050ab41 call 0x6c3d90
0050ab46 movd xmm0, eax
0050ab4a cvtdq2pd xmm0, xmm0
0050ab4e shr eax, 0x1f
0050ab51 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
0050ab5a cvtpd2ps xmm0, xmm0
0050ab5e mulss xmm0, xmm1
0050ab62 mulss xmm0, dword ptr [0xb6a874]
0050ab6a addss xmm0, xmm0
0050ab6e movss dword ptr [esp + 0x20], xmm0
0050ab74 call 0x411fe0
0050ab79 mulss xmm0, dword ptr [0xb6a974]
0050ab81 movss dword ptr [esp + 0x18], xmm0
0050ab87 movss xmm0, dword ptr [esp + 0x20]
0050ab8d call 0x412010
0050ab92 mov eax, dword ptr [esi + 0x28]
0050ab95 movaps xmm1, xmm0
0050ab98 mulss xmm1, dword ptr [0xb6a974]
0050aba0 movss dword ptr [esp + 0x1c], xmm1
0050aba6 cmp eax, 0x39
0050aba9 jne 0x50acf3
0050abaf mov eax, dword ptr [esi + 0x2c]
0050abb2 test eax, eax
0050abb4 jne 0x50ac1d
0050abb6 call 0x6c3d90
0050abbb movss xmm0, dword ptr [esp + 0x18]
0050abc1 addss xmm0, dword ptr [esi + 0x294]
0050abc9 mov ecx, dword ptr [0xbfd65c]
0050abcf push 0
0050abd1 push eax
0050abd2 push 0
0050abd4 push esi
0050abd5 movss dword ptr [esp + 0x20], xmm0
0050abdb lea eax, [esp + 0x20]
0050abdf push 0xc02fec
0050abe4 movaps xmm0, xmm1
0050abe7 addss xmm0, dword ptr [esi + 0x298]
0050abef push eax
0050abf0 push 0
0050abf2 push 0x20
0050abf4 movss dword ptr [esp + 0x34], xmm0
0050abfa call 0x6d0ca0
0050abff call 0x6c3d90
0050ac04 push 0
0050ac06 push eax
0050ac07 push 0
0050ac09 push esi
0050ac0a push 0xc02fec
0050ac0f lea eax, [esp + 0x24]
0050ac13 push eax
0050ac14 push 0
0050ac16 push 0x20
0050ac18 jmp 0x50ad66
0050ac1d cmp eax, 2
0050ac20 jne 0x50ac8f
0050ac22 call 0x6c3d90
0050ac27 movss xmm0, dword ptr [esp + 0x18]
0050ac2d addss xmm0, dword ptr [esi + 0x294]
0050ac35 mov ecx, dword ptr [0xbfd65c]
0050ac3b push 0
0050ac3d push eax
0050ac3e push 0
0050ac40 push esi
0050ac41 movss dword ptr [esp + 0x20], xmm0
0050ac47 lea eax, [esp + 0x20]
0050ac4b push 0xc02fec
0050ac50 movaps xmm0, xmm1
0050ac53 addss xmm0, dword ptr [esi + 0x298]
0050ac5b push eax
0050ac5c push 0
0050ac5e push 0x35e
0050ac63 movss dword ptr [esp + 0x34], xmm0
0050ac69 call 0x6d0ca0
0050ac6e call 0x6c3d90
0050ac73 push 0
0050ac75 push eax
0050ac76 push 0
0050ac78 push esi
0050ac79 push 0xc02fec
0050ac7e lea eax, [esp + 0x24]
0050ac82 push eax
0050ac83 push 0
0050ac85 push 0x35e
0050ac8a jmp 0x50ad66
0050ac8f call 0x6c3d90
0050ac94 movss xmm0, dword ptr [esp + 0x18]
0050ac9a addss xmm0, dword ptr [esi + 0x294]
0050aca2 mov ecx, dword ptr [0xbfd65c]
0050aca8 push 0
0050acaa push eax
0050acab push 0
0050acad push esi
0050acae movss dword ptr [esp + 0x20], xmm0
0050acb4 lea eax, [esp + 0x20]
0050acb8 push 0xc02fec
0050acbd movaps xmm0, xmm1
0050acc0 addss xmm0, dword ptr [esi + 0x298]
0050acc8 push eax
0050acc9 push 0
0050accb push 0x28
0050accd movss dword ptr [esp + 0x34], xmm0
0050acd3 call 0x6d0ca0
0050acd8 call 0x6c3d90
0050acdd push 0
0050acdf push eax
0050ace0 push 0
0050ace2 push esi
0050ace3 push 0xc02fec
0050ace8 lea eax, [esp + 0x24]
0050acec push eax
0050aced push 0
0050acef push 0x28
0050acf1 jmp 0x50ad66
0050acf3 cmp eax, 0xdf
0050acf8 jne 0x50ad99
0050acfe call 0x6c3d90
0050ad03 movss xmm0, dword ptr [esp + 0x18]
0050ad09 addss xmm0, dword ptr [esi + 0x294]
0050ad11 mov ecx, dword ptr [0xbfd65c]
0050ad17 push 0
0050ad19 push eax
0050ad1a push 0
0050ad1c push esi
0050ad1d movss dword ptr [esp + 0x20], xmm0
0050ad23 lea eax, [esp + 0x20]
0050ad27 push 0xc02fec
0050ad2c movaps xmm0, xmm1
0050ad2f addss xmm0, dword ptr [esi + 0x298]
0050ad37 push eax
0050ad38 push 0
0050ad3a push 0xdc
0050ad3f movss dword ptr [esp + 0x34], xmm0
0050ad45 call 0x6d0ca0
0050ad4a call 0x6c3d90
0050ad4f push 0
0050ad51 push eax
0050ad52 push 0
0050ad54 push esi
0050ad55 push 0xc02fec
0050ad5a lea eax, [esp + 0x24]
0050ad5e push eax
0050ad5f push 0
0050ad61 push 0xdc
0050ad66 movss xmm0, dword ptr [esi + 0x294]
0050ad6e subss xmm0, dword ptr [esp + 0x38]
0050ad74 mov ecx, dword ptr [0xbfd65c]
0050ad7a movss dword ptr [esp + 0x30], xmm0
0050ad80 movss xmm0, dword ptr [esi + 0x298]
0050ad88 subss xmm0, dword ptr [esp + 0x3c]
0050ad8e movss dword ptr [esp + 0x34], xmm0
0050ad94 call 0x6d0ca0
0050ad99 mov ecx, dword ptr [esp + 0x114]
0050ada0 pop edi
0050ada1 pop esi
0050ada2 pop ebx
0050ada3 xor ecx, esp
0050ada5 call 0x9eacd7
0050adaa mov esp, ebp
0050adac pop ebp
0050adad ret 
