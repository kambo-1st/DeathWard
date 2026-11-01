0054d470 push ebx
0054d471 mov ebx, esp
0054d473 sub esp, 8
0054d476 and esp, 0xfffffff8
0054d479 add esp, 4
0054d47c push ebp
0054d47d mov ebp, dword ptr [ebx + 4]
0054d480 mov dword ptr [esp + 4], ebp
0054d484 mov ebp, esp
0054d486 sub esp, 0xd8
0054d48c mov eax, dword ptr [0xbaa3b4]
0054d491 xor eax, ebp
0054d493 mov dword ptr [ebp - 4], eax
0054d496 push esi
0054d497 mov esi, ecx
0054d499 push edi
0054d49a movss xmm0, dword ptr [esi + 0xb00]
0054d4a2 addss xmm0, dword ptr [0xb6aae4]
0054d4aa mulss xmm0, dword ptr [0xb6a230]
0054d4b2 movss dword ptr [ebp - 0xcc], xmm0
0054d4ba call 0x411fe0
0054d4bf movss dword ptr [ebp - 0xd0], xmm0
0054d4c7 movss xmm0, dword ptr [ebp - 0xcc]
0054d4cf call 0x412010
0054d4d4 mov eax, dword ptr [0xbfd65c]
0054d4d9 movss dword ptr [ebp - 0xcc], xmm0
0054d4e1 mov eax, dword ptr [eax + 0x18190]
0054d4e7 mov edi, dword ptr [eax + 0x1e84]
0054d4ed call 0x690cc0
0054d4f2 mov dword ptr [ebp - 0xd4], eax
0054d4f8 cmp edi, 0x1f
0054d4fb je 0x54d513
0054d4fd cmp edi, 6
0054d500 je 0x54d513
0054d502 cmp eax, 0x1b
0054d505 je 0x54d513
0054d507 mov byte ptr [ebp - 0xb1], 0
0054d50e cmp eax, 0x1c
0054d511 jne 0x54d51a
0054d513 mov byte ptr [ebp - 0xb1], 1
0054d51a movss xmm0, dword ptr [esi + 0x14]
0054d51f comiss xmm0, dword ptr [0xb6a18c]
0054d526 movss xmm4, dword ptr [0xb6a19c]
0054d52e jbe 0x54d6f4
0054d534 mov eax, dword ptr [esi + 8]
0054d537 cmp eax, dword ptr [esi + 0xc]
0054d53a je 0x54d5d6
0054d540 mov eax, dword ptr [esi + 0xc]
0054d543 movss xmm1, dword ptr [esi + 0x294]
0054d54b movss xmm2, dword ptr [esi + 0x298]
0054d553 subss xmm1, dword ptr [eax - 0x18]
0054d558 subss xmm2, dword ptr [eax - 0x14]
0054d55d movaps xmm0, xmm1
0054d560 movss dword ptr [ebp - 0xc0], xmm1
0054d568 mulss xmm0, xmm1
0054d56c movaps xmm1, xmm2
0054d56f mulss xmm1, xmm2
0054d573 movss dword ptr [ebp - 0xc4], xmm2
0054d57b addss xmm0, xmm1
0054d57f call 0x4228c0
0054d584 comiss xmm0, dword ptr [0xb6a18c]
0054d58b movss xmm2, dword ptr [ebp - 0xc0]
0054d593 jbe 0x54d5b6
0054d595 movss xmm1, dword ptr [0xb6a614]
0054d59d divss xmm1, xmm0
0054d5a1 movaps xmm0, xmm1
0054d5a4 mulss xmm2, xmm0
0054d5a8 movss xmm0, dword ptr [ebp - 0xc4]
0054d5b0 mulss xmm0, xmm1
0054d5b4 jmp 0x54d5be
0054d5b6 movss xmm0, dword ptr [ebp - 0xc4]
0054d5be movss xmm4, dword ptr [0xb6a19c]
0054d5c6 movss dword ptr [esi + 0x2b8], xmm2
0054d5ce movss dword ptr [esi + 0x2bc], xmm0
0054d5d6 movss xmm3, dword ptr [esi + 0x2bc]
0054d5de movss xmm2, dword ptr [esi + 0x2b8]
0054d5e6 movaps xmm0, xmm3
0054d5e9 movaps xmm1, xmm2
0054d5ec mulss xmm0, xmm3
0054d5f0 mulss xmm1, xmm2
0054d5f4 movss dword ptr [ebp - 0xc0], xmm3
0054d5fc movss dword ptr [ebp - 0xc4], xmm2
0054d604 addss xmm1, xmm0
0054d608 movss xmm0, dword ptr [0xb6a1ac]
0054d610 comiss xmm0, xmm1
0054d613 jbe 0x54d692
0054d615 call 0x6c3d90
0054d61a movd xmm0, eax
0054d61e cvtdq2pd xmm0, xmm0
0054d622 shr eax, 0x1f
0054d625 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
0054d62e cvtpd2ps xmm0, xmm0
0054d632 mulss xmm0, xmm4
0054d636 mulss xmm0, dword ptr [0xb6a874]
0054d63e addss xmm0, xmm0
0054d642 movss dword ptr [ebp - 0xc4], xmm0
0054d64a call 0x411fe0
0054d64f movss dword ptr [ebp - 0xb8], xmm0
0054d657 movss xmm0, dword ptr [ebp - 0xc4]
0054d65f call 0x412010
0054d664 movaps xmm3, xmm0
0054d667 movss dword ptr [ebp - 0xc0], xmm0
0054d66f movss xmm0, dword ptr [ebp - 0xb8]
0054d677 movss dword ptr [esi + 0x2b8], xmm0
0054d67f movaps xmm2, xmm0
0054d682 movss dword ptr [esi + 0x2bc], xmm3
0054d68a movss dword ptr [ebp - 0xc4], xmm0
0054d692 movaps xmm0, xmm3
0054d695 movaps xmm1, xmm2
0054d698 mulss xmm0, xmm3
0054d69c mulss xmm1, xmm2
0054d6a0 addss xmm0, xmm1
0054d6a4 call 0x4228c0
0054d6a9 movaps xmm1, xmm0
0054d6ac movss xmm0, dword ptr [0xb6a940]
0054d6b4 comiss xmm0, xmm1
0054d6b7 jbe 0x54d6ea
0054d6b9 comiss xmm1, dword ptr [0xb6a18c]
0054d6c0 jbe 0x54d6ea
0054d6c2 divss xmm0, xmm1
0054d6c6 movss xmm1, dword ptr [ebp - 0xc4]
0054d6ce mulss xmm1, xmm0
0054d6d2 mulss xmm0, dword ptr [ebp - 0xc0]
0054d6da movss dword ptr [esi + 0x2b8], xmm1
0054d6e2 movss dword ptr [esi + 0x2bc], xmm0
0054d6ea mov dword ptr [esi + 0x360], 0xf
0054d6f4 mov eax, dword ptr [esi + 0xab4]
0054d6fa test eax, eax
0054d6fc jne 0x54d72b
0054d6fe mov dword ptr [esi + 0x17c], 6
0054d708 mov dword ptr [esi + 0xab4], 0x10
0054d712 mov dword ptr [esi + 0xb00], eax
0054d718 pop edi
0054d719 pop esi
0054d71a mov ecx, dword ptr [ebp - 4]
0054d71d xor ecx, ebp
0054d71f call 0x9eacd7
0054d724 mov esp, ebp
0054d726 pop ebp
0054d727 mov esp, ebx
0054d729 pop ebx
0054d72a ret 
0054d72b cmp eax, 0x10
0054d72e jne 0x54d77d
0054d730 push 0
0054d732 push 0xb436d4
0054d737 lea ecx, [esi + 0x3c]
0054d73a call 0x4054f0
0054d73f cmp dword ptr [esi + 0x70], 0
0054d743 je 0x54d760
0054d745 cmp byte ptr [esi + 0x80], 0
0054d74c je 0x54d760
0054d74e movss xmm0, dword ptr [esi + 0x14]
0054d753 comiss xmm0, dword ptr [0xb6a18c]
0054d75a jbe 0x54de2e
0054d760 mov dword ptr [esi + 0xab4], 3
0054d76a pop edi
0054d76b pop esi
0054d76c mov ecx, dword ptr [ebp - 4]
0054d76f xor ecx, ebp
0054d771 call 0x9eacd7
0054d776 mov esp, ebp
0054d778 pop ebp
0054d779 mov esp, ebx
0054d77b pop ebx
0054d77c ret 
0054d77d cmp eax, 3
0054d780 jne 0x54de2e
0054d786 movss xmm0, dword ptr [esi + 0xb00]
0054d78e movss xmm3, dword ptr [0xb6ab88]
0054d796 movss xmm2, dword ptr [0xb6ac40]
0054d79e subss xmm0, xmm3
0054d7a2 movaps xmm1, xmm0
0054d7a5 andps xmm1, xmmword ptr [0xb6c980]
0054d7ac comiss xmm1, xmm2
0054d7af jbe 0x54d7c9
0054d7b1 movaps xmm1, xmm2
0054d7b4 call 0x447b40
0054d7b9 movss xmm2, dword ptr [0xb6ac40]
0054d7c1 movss xmm3, dword ptr [0xb6ab88]
0054d7c9 comiss xmm0, xmm3
0054d7cc jbe 0x54d7d4
0054d7ce subss xmm0, xmm2
0054d7d2 jmp 0x54d7e5
0054d7d4 movss xmm1, dword ptr [0xb6af74]
0054d7dc comiss xmm1, xmm0
0054d7df jbe 0x54d7e5
0054d7e1 addss xmm0, xmm2
0054d7e5 addss xmm0, xmm3
0054d7e9 sub esp, 8
0054d7ec mulss xmm0, dword ptr [0xb6a98c]
0054d7f4 divss xmm0, xmm2
0054d7f8 movss dword ptr [ebp - 0xb8], xmm0
0054d800 fld dword ptr [ebp - 0xb8]
0054d806 fstp qword ptr [esp]
0054d809 call 0x9ec3b2
0054d80e fstp dword ptr [ebp - 0xb8]
0054d814 fld dword ptr [ebp - 0xb8]
0054d81a xor eax, eax
0054d81c fstp dword ptr [ebp - 0xb8]
0054d822 cvttss2si ecx, dword ptr [ebp - 0xb8]
0054d82a add esp, 8
0054d82d push eax
0054d82e test ecx, ecx
0054d830 cmovs ecx, eax
0054d833 mov eax, 0x2aaaaaab
0054d838 imul ecx
0054d83a sar edx, 1
0054d83c mov eax, edx
0054d83e shr eax, 0x1f
0054d841 add eax, edx
0054d843 lea eax, [eax + eax*2]
0054d846 shl eax, 2
0054d849 sub ecx, eax
0054d84b push dword ptr [ecx*4 + 0xb437b8]
0054d852 lea ecx, [esi + 0x3c]
0054d855 call 0x4054f0
0054d85a movss xmm0, dword ptr [esi + 0x14]
0054d85f xorps xmm1, xmm1
0054d862 comiss xmm0, xmm1
0054d865 jbe 0x54d8af
0054d867 call 0x6c3d90
0054d86c xor edx, edx
0054d86e mov ecx, 3
0054d873 div ecx
0054d875 test edx, edx
0054d877 jne 0x54d8af
0054d879 cmp dword ptr [esi + 0x2c], 1
0054d87d jne 0x54d889
0054d87f movss xmm0, dword ptr [0xb6a588]
0054d887 jmp 0x54d891
0054d889 movss xmm0, dword ptr [0xb6a614]
0054d891 push ecx
0054d892 movss dword ptr [esp], xmm0
0054d897 push 0
0054d899 push 0xa
0054d89b push ecx
0054d89c mov dword ptr [esp], 0x3f800000
0054d8a3 mov ecx, esi
0054d8a5 push 0x92
0054d8aa call 0x6ad720
0054d8af cmp dword ptr [esi + 0x2c], 1
0054d8b3 jne 0x54da5c
0054d8b9 cmp dword ptr [esi + 0x360], 0
0054d8c0 jg 0x54da5c
0054d8c6 push ecx
0054d8c7 lea eax, [ebp - 0xd8]
0054d8cd mov dword ptr [esp], 0
0054d8d4 push eax
0054d8d5 mov ecx, esi
0054d8d7 call 0x695a30
0054d8dc cmp dword ptr [esi + 0xe6c], -1
0054d8e3 movss xmm1, dword ptr [eax]
0054d8e7 movss xmm2, dword ptr [eax + 4]
0054d8ec subss xmm1, dword ptr [esi + 0x294]
0054d8f4 subss xmm2, dword ptr [esi + 0x298]
0054d8fc movss dword ptr [ebp - 0xc4], xmm1
0054d904 movss dword ptr [ebp - 0xc0], xmm2
0054d90c je 0x54d938
0054d90e lea eax, [ebp - 0xd8]
0054d914 xorps xmm2, xmm2
0054d917 push eax
0054d918 mov ecx, esi
0054d91a call 0x6af0c0
0054d91f movss xmm1, dword ptr [eax]
0054d923 movss xmm2, dword ptr [eax + 4]
0054d928 movss dword ptr [ebp - 0xc4], xmm1
0054d930 movss dword ptr [ebp - 0xc0], xmm2
0054d938 movaps xmm0, xmm1
0054d93b mulss xmm0, xmm1
0054d93f movaps xmm1, xmm2
0054d942 mulss xmm1, xmm2
0054d946 addss xmm0, xmm1
0054d94a call 0x4228c0
0054d94f movaps xmm2, xmm0
0054d952 xorps xmm0, xmm0
0054d955 comiss xmm2, xmm0
0054d958 jbe 0x54da13
0054d95e movss xmm1, dword ptr [0xb6a350]
0054d966 divss xmm1, xmm2
0054d96a movss xmm2, dword ptr [esi + 0x2c4]
0054d972 movss xmm3, dword ptr [ebp - 0xc4]
0054d97a movss xmm4, dword ptr [ebp - 0xc0]
0054d982 ucomiss xmm2, xmm0
0054d985 mulss xmm3, xmm1
0054d989 lahf 
0054d98a mulss xmm4, xmm1
0054d98e test ah, 0x44
0054d991 jnp 0x54d9ce
0054d993 movss xmm1, dword ptr [esi + 0x2f4]
0054d99b movaps xmm0, xmm1
0054d99e mulss xmm1, xmm4
0054d9a2 mulss xmm0, xmm3
0054d9a6 divss xmm1, xmm2
0054d9aa divss xmm0, xmm2
0054d9ae addss xmm1, dword ptr [esi + 0x2bc]
0054d9b6 addss xmm0, dword ptr [esi + 0x2b8]
0054d9be movss dword ptr [esi + 0x2bc], xmm1
0054d9c6 movss dword ptr [esi + 0x2b8], xmm0
0054d9ce mulss xmm3, dword ptr [0xb6a434]
0054d9d6 mulss xmm4, dword ptr [0xb6a434]
0054d9de movss xmm1, dword ptr [ebp - 0xd0]
0054d9e6 movss xmm0, dword ptr [ebp - 0xcc]
0054d9ee addss xmm1, xmm3
0054d9f2 addss xmm0, xmm4
0054d9f6 call 0x447a80
0054d9fb mulss xmm0, dword ptr [0xb6aa84]
0054da03 subss xmm0, dword ptr [0xb6aae4]
0054da0b movss dword ptr [esi + 0xb00], xmm0
0054da13 movss xmm1, dword ptr [esi + 0x2bc]
0054da1b movss xmm0, dword ptr [esi + 0x2b8]
0054da23 mulss xmm0, xmm0
0054da27 mulss xmm1, xmm1
0054da2b addss xmm0, xmm1
0054da2f call 0x4228c0
0054da34 comiss xmm0, dword ptr [0xb6a940]
0054da3b jbe 0x54da47
0054da3d mov dword ptr [esi + 0x360], 0xf
0054da47 movss xmm0, dword ptr [esi + 0x2c4]
0054da4f mulss xmm0, dword ptr [0xb6a5a4]
0054da57 jmp 0x54dda2
0054da5c cmp dword ptr [esi + 0xe6c], -1
0054da63 je 0x54db50
0054da69 lea eax, [ebp - 0xc8]
0054da6f xorps xmm2, xmm2
0054da72 push eax
0054da73 mov ecx, esi
0054da75 call 0x6af0c0
0054da7a movss xmm0, dword ptr [ebp - 0xc8]
0054da82 ucomiss xmm0, dword ptr [0xc02fec]
0054da89 movss xmm0, dword ptr [ebp - 0xc4]
0054da91 lahf 
0054da92 test ah, 0x44
0054da95 jp 0x54daa8
0054da97 ucomiss xmm0, dword ptr [0xc02ff0]
0054da9e lahf 
0054da9f test ah, 0x44
0054daa2 jnp 0x54db50
0054daa8 movss xmm1, dword ptr [esi + 0x2bc]
0054dab0 lea edi, [esi + 0x2b8]
0054dab6 movss xmm0, dword ptr [edi]
0054daba mulss xmm0, xmm0
0054dabe mulss xmm1, xmm1
0054dac2 addss xmm0, xmm1
0054dac6 call 0x4228c0
0054dacb divss xmm0, dword ptr [0xb6a5f8]
0054dad3 movss xmm3, dword ptr [ebp - 0xc4]
0054dadb maxss xmm0, dword ptr [0xb6a614]
0054dae3 mulss xmm3, dword ptr [0xb6a350]
0054daeb movss xmm2, dword ptr [esi + 0x2f4]
0054daf3 movss dword ptr [ebp - 0xb8], xmm0
0054dafb movss xmm0, dword ptr [ebp - 0xc8]
0054db03 mulss xmm0, dword ptr [0xb6a350]
0054db0b mulss xmm3, xmm2
0054db0f mulss xmm0, xmm2
0054db13 addss xmm3, dword ptr [edi + 4]
0054db18 addss xmm0, dword ptr [edi]
0054db1c movss dword ptr [edi + 4], xmm3
0054db21 mulss xmm3, xmm3
0054db25 movss dword ptr [edi], xmm0
0054db29 mulss xmm0, xmm0
0054db2d addss xmm0, xmm3
0054db31 call 0x4228c0
0054db36 movss xmm1, dword ptr [ebp - 0xb8]
0054db3e comiss xmm0, xmm1
0054db41 jbe 0x54db50
0054db43 push ecx
0054db44 mov ecx, edi
0054db46 movss dword ptr [esp], xmm1
0054db4b call 0x962860
0054db50 movss xmm1, dword ptr [esi + 0x2b8]
0054db58 movss xmm0, dword ptr [esi + 0x2bc]
0054db60 movaps xmm2, xmm1
0054db63 mulss xmm2, xmm1
0054db67 mulss xmm0, xmm0
0054db6b movss dword ptr [ebp - 0xb8], xmm2
0054db73 addss xmm0, xmm2
0054db77 call 0x4228c0
0054db7c xorps xmm1, xmm1
0054db7f addss xmm0, xmm0
0054db83 comiss xmm1, dword ptr [esi + 0x2b8]
0054db8a jbe 0x54db94
0054db8c mulss xmm0, dword ptr [0xb6ae44]
0054db94 addss xmm0, dword ptr [esi + 0xb00]
0054db9c movss xmm2, dword ptr [0xb6ac40]
0054dba4 movaps xmm1, xmm0
0054dba7 andps xmm1, xmmword ptr [0xb6c980]
0054dbae comiss xmm1, xmm2
0054dbb1 jbe 0x54dbc3
0054dbb3 movaps xmm1, xmm2
0054dbb6 call 0x447b40
0054dbbb movss xmm2, dword ptr [0xb6ac40]
0054dbc3 comiss xmm0, dword ptr [0xb6ab88]
0054dbca jbe 0x54dbd2
0054dbcc subss xmm0, xmm2
0054dbd0 jmp 0x54dbe3
0054dbd2 movss xmm1, dword ptr [0xb6af74]
0054dbda comiss xmm1, xmm0
0054dbdd jbe 0x54dbe3
0054dbdf addss xmm0, xmm2
0054dbe3 movss dword ptr [esi + 0xb00], xmm0
0054dbeb movss xmm0, dword ptr [esi + 0x2bc]
0054dbf3 mulss xmm0, xmm0
0054dbf7 addss xmm0, dword ptr [ebp - 0xb8]
0054dbff call 0x4228c0
0054dc04 movaps xmm1, xmm0
0054dc07 movss xmm0, dword ptr [0xb6a614]
0054dc0f comiss xmm0, xmm1
0054dc12 jbe 0x54dc3a
0054dc14 mov edx, dword ptr [esi + 0x360]
0054dc1a test edx, edx
0054dc1c jle 0x54dc44
0054dc1e cvttss2si eax, dword ptr [esi + 0x2fc]
0054dc26 cvttss2si ecx, dword ptr [esi + 0x2f8]
0054dc2e sub ecx, eax
0054dc30 add ecx, edx
0054dc32 mov dword ptr [esi + 0x360], ecx
0054dc38 jmp 0x54dc44
0054dc3a mov dword ptr [esi + 0x360], 0xf
0054dc44 comiss xmm1, dword ptr [0xb6a214]
0054dc4b jbe 0x54dd8a
0054dc51 mov ecx, 1
0054dc56 cmp dword ptr [esi + 0x2c], ecx
0054dc59 jne 0x54dc65
0054dc5b movss xmm0, dword ptr [0xb6a8f4]
0054dc63 jmp 0x54dc6d
0054dc65 movss xmm0, dword ptr [0xb6a9c8]
0054dc6d divss xmm0, xmm1
0054dc71 cvttss2si eax, xmm0
0054dc75 cmp eax, 1
0054dc78 cmovg ecx, eax
0054dc7b movd xmm0, ecx
0054dc7f mov ecx, dword ptr [esi + 0xb10]
0054dc85 cvtdq2ps xmm0, xmm0
0054dc88 addss xmm0, xmm0
0054dc8c cvttss2si eax, xmm0
0054dc90 cmp ecx, eax
0054dc92 jle 0x54dd87
0054dc98 lea ecx, [ebp - 0xb0]
0054dc9e call 0x430d70
0054dca3 cmp byte ptr [ebp - 0xb1], 0
0054dcaa je 0x54dcbe
0054dcac xor eax, eax
0054dcae cmp dword ptr [ebp - 0xd4], 0x1c
0054dcb5 setne al
0054dcb8 add eax, 3
0054dcbb mov dword ptr [ebp - 0x1c], eax
0054dcbe cmp dword ptr [esi + 0x2c], 1
0054dcc2 mov dword ptr [ebp - 0xa0], 0x3f333333
0054dccc jne 0x54dce2
0054dcce mov dword ptr [ebp - 0xa4], 0xbdcccccd
0054dcd8 mov dword ptr [ebp - 0x9c], 0x3fb33333
0054dce2 movss xmm0, dword ptr [ebp - 0xd0]
0054dcea lea ecx, [ebp - 0xbc]
0054dcf0 movss dword ptr [ebp - 0xbc], xmm0
0054dcf8 movss xmm0, dword ptr [ebp - 0xcc]
0054dd00 movss dword ptr [ebp - 0xb8], xmm0
0054dd08 call 0x9624f0
0054dd0d movss xmm0, dword ptr [ebp - 0xbc]
0054dd15 lea eax, [ebp - 0xb0]
0054dd1b mulss xmm0, dword ptr [0xb6a974]
0054dd23 mov ecx, esi
0054dd25 push eax
0054dd26 push 0
0054dd28 lea eax, [ebp - 0xbc]
0054dd2e movss dword ptr [ebp - 0xbc], xmm0
0054dd36 movss xmm0, dword ptr [ebp - 0xb8]
0054dd3e mulss xmm0, dword ptr [0xb6a974]
0054dd46 push eax
0054dd47 lea eax, [esi + 0x294]
0054dd4d push eax
0054dd4e movss dword ptr [ebp - 0xb8], xmm0
0054dd56 call 0x6a1a20
0054dd5b push ecx
0054dd5c mov dword ptr [esp], 0x3f800000
0054dd63 push 0
0054dd65 push 2
0054dd67 push ecx
0054dd68 mov dword ptr [esp], 0x3f800000
0054dd6f mov ecx, esi
0054dd71 push 0x99
0054dd76 call 0x6ad720
0054dd7b mov dword ptr [esi + 0xb10], 0
0054dd85 xor ecx, ecx
0054dd87 inc ecx
0054dd88 jmp 0x54dd8c
0054dd8a xor ecx, ecx
0054dd8c mov dword ptr [esi + 0xb10], ecx
0054dd92 movss xmm0, dword ptr [esi + 0x2c4]
0054dd9a mulss xmm0, dword ptr [0xb6a5f8]
0054dda2 cmp byte ptr [ebp - 0xb1], 0
0054dda9 movss dword ptr [esi + 0x2c4], xmm0
0054ddb1 jne 0x54de2e
0054ddb3 movss xmm1, dword ptr [esi + 0x2bc]
0054ddbb movss xmm0, dword ptr [esi + 0x2b8]
0054ddc3 mulss xmm0, xmm0
0054ddc7 mulss xmm1, xmm1
0054ddcb addss xmm0, xmm1
0054ddcf call 0x4228c0
0054ddd4 comiss xmm0, dword ptr [0xb6a7b0]
0054dddb jbe 0x54de2e
0054dddd push 0
0054dddf push 7
0054dde1 mov ecx, esi
0054dde3 call 0x684790
0054dde8 test al, al
0054ddea je 0x54de2e
0054ddec call 0x6c3d90
0054ddf1 push ecx
0054ddf2 mov ecx, esi
0054ddf4 movd xmm0, eax
0054ddf8 cvtdq2pd xmm0, xmm0
0054ddfc shr eax, 0x1f
0054ddff addsd xmm0, qword ptr [eax*8 + 0xb6c940]
0054de08 cvtpd2ps xmm0, xmm0
0054de0c mulss xmm0, dword ptr [0xb6a19c]
0054de14 mulss xmm0, dword ptr [0xb6a3b0]
0054de1c addss xmm0, dword ptr [0xb6a2cc]
0054de24 movss dword ptr [esp], xmm0
0054de29 call 0x68d7b0
0054de2e mov ecx, dword ptr [ebp - 4]
0054de31 pop edi
0054de32 xor ecx, ebp
0054de34 pop esi
0054de35 call 0x9eacd7
0054de3a mov esp, ebp
0054de3c pop ebp
0054de3d mov esp, ebx
0054de3f pop ebx
0054de40 ret 
