0053d4c0 push ebx
0053d4c1 mov ebx, esp
0053d4c3 sub esp, 8
0053d4c6 and esp, 0xfffffff8
0053d4c9 add esp, 4
0053d4cc push ebp
0053d4cd mov ebp, dword ptr [ebx + 4]
0053d4d0 mov dword ptr [esp + 4], ebp
0053d4d4 mov ebp, esp
0053d4d6 push -1
0053d4d8 push 0x9efaf5
0053d4dd mov eax, dword ptr fs:[0]
0053d4e3 push eax
0053d4e4 push ebx
0053d4e5 sub esp, 0x40
0053d4e8 mov eax, dword ptr [0xbaa3b4]
0053d4ed xor eax, ebp
0053d4ef mov dword ptr [ebp - 0x14], eax
0053d4f2 push esi
0053d4f3 push edi
0053d4f4 push eax
0053d4f5 lea eax, [ebp - 0xc]
0053d4f8 mov dword ptr fs:[0], eax
0053d4fe mov edi, ecx
0053d500 mov ecx, dword ptr [0xbfd65c]
0053d506 push 1
0053d508 add ecx, 0x1ba40
0053d50e push ecx
0053d50f push 0x179
0053d514 call 0x91d340
0053d519 test eax, eax
0053d51b je 0x53d5e0
0053d521 mov eax, dword ptr [edi + 0x160]
0053d527 and eax, 0x20000000
0053d52c or eax, 0
0053d52f jne 0x53d5e0
0053d535 mov byte ptr [ebp - 0x39], 1
0053d539 cmp dword ptr [edi + 0xab4], eax
0053d53f je 0x53d55b
0053d541 mov eax, dword ptr [0xbfd65c]
0053d546 mov eax, dword ptr [eax + 0x1a30dc]
0053d54c sub eax, dword ptr [edi + 0x280]
0053d552 cmp eax, 1
0053d555 jne 0x53d5e4
0053d55b mov eax, dword ptr [0xb43118]
0053d560 mov dword ptr [ebp - 0x2c], eax
0053d563 mov ax, word ptr [0xb4311c]
0053d569 mov dword ptr [ebp - 0x18], 0xf
0053d570 mov dword ptr [ebp - 0x1c], 6
0053d577 mov word ptr [ebp - 0x28], ax
0053d57b mov byte ptr [ebp - 0x26], 0
0053d57f lea eax, [ebp - 0x2c]
0053d582 mov dword ptr [ebp - 4], 0
0053d589 push eax
0053d58a mov ecx, edi
0053d58c call 0x691bc0
0053d591 mov dword ptr [ebp - 4], 0xffffffff
0053d598 mov edx, dword ptr [ebp - 0x18]
0053d59b cmp edx, 0x10
0053d59e jb 0x53d5cc
0053d5a0 mov ecx, dword ptr [ebp - 0x2c]
0053d5a3 inc edx
0053d5a4 mov eax, ecx
0053d5a6 cmp edx, 0x1000
0053d5ac jb 0x53d5c2
0053d5ae mov ecx, dword ptr [ecx - 4]
0053d5b1 add edx, 0x23
0053d5b4 sub eax, ecx
0053d5b6 add eax, -4
0053d5b9 cmp eax, 0x1f
0053d5bc ja 0x53dff5
0053d5c2 push edx
0053d5c3 push ecx
0053d5c4 call 0x9eb08e
0053d5c9 add esp, 8
0053d5cc mov dword ptr [ebp - 0x1c], 0
0053d5d3 mov dword ptr [ebp - 0x18], 0xf
0053d5da mov byte ptr [ebp - 0x2c], 0
0053d5de jmp 0x53d5e4
0053d5e0 mov byte ptr [ebp - 0x39], 0
0053d5e4 mov eax, dword ptr [edi + 0xab4]
0053d5ea test eax, eax
0053d5ec je 0x53e00a
0053d5f2 cmp eax, 3
0053d5f5 je 0x53d7ad
0053d5fb cmp eax, 6
0053d5fe jne 0x53e254
0053d604 mov eax, dword ptr [edi + 0x160]
0053d60a and eax, 0x40000000
0053d60f or eax, 0
0053d612 jne 0x53d62c
0053d614 movss xmm0, dword ptr [edi + 0x2c4]
0053d61c mulss xmm0, dword ptr [0xb6a50c]
0053d624 movss dword ptr [edi + 0x2c4], xmm0
0053d62c cmp dword ptr [edi + 0x70], 0
0053d630 lea esi, [edi + 0x6c]
0053d633 je 0x53d72c
0053d639 push 0xb40338
0053d63e mov ecx, esi
0053d640 call 0x405e90
0053d645 test al, al
0053d647 je 0x53d6d0
0053d64d mov eax, dword ptr [edi + 0x164]
0053d653 or dword ptr [edi + 0x160], 0x40000000
0053d65d mov dword ptr [edi + 0x164], eax
0053d663 mov eax, dword ptr [edi + 0x28c]
0053d669 mov dword ptr [edi + 0x2b8], eax
0053d66f mov eax, dword ptr [edi + 0x290]
0053d675 mov dword ptr [edi + 0x2bc], eax
0053d67b call 0x6c3d90
0053d680 push ecx
0053d681 movd xmm0, eax
0053d685 cvtdq2pd xmm0, xmm0
0053d689 shr eax, 0x1f
0053d68c addsd xmm0, qword ptr [eax*8 + 0xb6c940]
0053d695 cvtpd2ps xmm0, xmm0
0053d699 mulss xmm0, dword ptr [0xb6a19c]
0053d6a1 mulss xmm0, dword ptr [0xb6a350]
0053d6a9 addss xmm0, dword ptr [0xb6a754]
0053d6b1 movss dword ptr [esp], xmm0
0053d6b6 push 0
0053d6b8 push 2
0053d6ba push ecx
0053d6bb mov dword ptr [esp], 0x3ecccccd
0053d6c2 mov ecx, edi
0053d6c4 push 0x102
0053d6c9 call 0x6ad720
0053d6ce jmp 0x53d6fc
0053d6d0 cmp dword ptr [edi + 0x70], 0
0053d6d4 je 0x53d72c
0053d6d6 push 0xb4034c
0053d6db mov ecx, esi
0053d6dd call 0x405e90
0053d6e2 test al, al
0053d6e4 je 0x53d6fc
0053d6e6 mov eax, dword ptr [edi + 0x164]
0053d6ec and dword ptr [edi + 0x160], 0xbfffffff
0053d6f6 mov dword ptr [edi + 0x164], eax
0053d6fc cmp dword ptr [edi + 0x70], 0
0053d700 je 0x53d72c
0053d702 cmp byte ptr [edi + 0x80], 0
0053d709 je 0x53d72c
0053d70b push 0xb4034c
0053d710 mov ecx, esi
0053d712 call 0x405f30
0053d717 test al, al
0053d719 je 0x53e254
0053d71f call 0x6c3d90
0053d724 test al, 3
0053d726 jne 0x53e254
0053d72c mov esi, dword ptr [edi + 0x70]
0053d72f test esi, esi
0053d731 je 0x53d77d
0053d733 cmp dword ptr [esi + 0x14], 0x10
0053d737 mov eax, esi
0053d739 jb 0x53d73d
0053d73b mov eax, dword ptr [esi]
0053d73d mov ecx, 0xb3fd8c
0053d742 mov dl, byte ptr [eax]
0053d744 cmp dl, byte ptr [ecx]
0053d746 jne 0x53d762
0053d748 test dl, dl
0053d74a je 0x53d75e
0053d74c mov dl, byte ptr [eax + 1]
0053d74f cmp dl, byte ptr [ecx + 1]
0053d752 jne 0x53d762
0053d754 add eax, 2
0053d757 add ecx, 2
0053d75a test dl, dl
0053d75c jne 0x53d742
0053d75e xor eax, eax
0053d760 jmp 0x53d767
0053d762 sbb eax, eax
0053d764 or eax, 1
0053d767 test eax, eax
0053d769 jne 0x53d77d
0053d76b cmp byte ptr [esi + 0x34], al
0053d76e je 0x53d79e
0053d770 cmp byte ptr [edi + 0x80], al
0053d776 lea esi, [edi + 0x3c]
0053d779 jne 0x53d79e
0053d77b jmp 0x53d780
0053d77d lea esi, [edi + 0x3c]
0053d780 push 1
0053d782 push 0xb3fd8c
0053d787 mov ecx, esi
0053d789 call 0x405740
0053d78e test al, al
0053d790 je 0x53d79e
0053d792 lea ecx, [esi + 0x30]
0053d795 call 0x405330
0053d79a mov byte ptr [esi + 0x44], 1
0053d79e mov dword ptr [edi + 0xab4], 3
0053d7a8 jmp 0x53e254
0053d7ad movss xmm0, dword ptr [edi + 0x2c4]
0053d7b5 lea eax, [ebp - 0x48]
0053d7b8 mulss xmm0, dword ptr [0xb6a50c]
0053d7c0 push ecx
0053d7c1 mov dword ptr [esp], 0
0053d7c8 mov ecx, edi
0053d7ca push eax
0053d7cb movss dword ptr [edi + 0x2c4], xmm0
0053d7d3 call 0x695a30
0053d7d8 cmp byte ptr [ebp - 0x39], 0
0053d7dc je 0x53d924
0053d7e2 push 0
0053d7e4 push 0
0053d7e6 push -1
0053d7e8 push -1
0053d7ea push dword ptr [edi + 0x28]
0053d7ed lea eax, [ebp - 0x24]
0053d7f0 xorps xmm0, xmm0
0053d7f3 push eax
0053d7f4 mov eax, dword ptr [0xbfd65c]
0053d7f9 movss dword ptr [ebp - 0x34], xmm0
0053d7fe movss dword ptr [ebp - 0x30], xmm0
0053d803 movss dword ptr [ebp - 0x38], xmm0
0053d808 mov ecx, dword ptr [eax + 0x18190]
0053d80e add ecx, 0x1218
0053d814 call 0x415ed0
0053d819 xor esi, esi
0053d81b cmp dword ptr [ebp - 0x18], esi
0053d81e jbe 0x53d8dd
0053d824 mov eax, dword ptr [ebp - 0x20]
0053d827 mov ecx, dword ptr [eax + esi*4]
0053d82a cmp ecx, edi
0053d82c je 0x53d89c
0053d82e mov eax, dword ptr [ecx + 0x160]
0053d834 and eax, 0x20000000
0053d839 or eax, 0
0053d83c jne 0x53d8a3
0053d83e movss xmm1, dword ptr [ecx + 0x294]
0053d846 movss xmm0, dword ptr [ecx + 0x298]
0053d84e subss xmm0, dword ptr [edi + 0x298]
0053d856 subss xmm1, dword ptr [edi + 0x294]
0053d85e mulss xmm0, xmm0
0053d862 mulss xmm1, xmm1
0053d866 addss xmm0, xmm1
0053d86a call 0x4228c0
0053d86f comiss xmm0, dword ptr [ebp - 0x38]
0053d873 jbe 0x53d8a3
0053d875 mov ecx, dword ptr [ebp - 0x20]
0053d878 movss dword ptr [ebp - 0x38], xmm0
0053d87d mov eax, dword ptr [ecx + esi*4]
0053d880 movss xmm1, dword ptr [eax + 0x294]
0053d888 movss dword ptr [ebp - 0x30], xmm1
0053d88d movss xmm1, dword ptr [eax + 0x298]
0053d895 movss dword ptr [ebp - 0x34], xmm1
0053d89a jmp 0x53d8a8
0053d89c movss xmm0, dword ptr [ebp - 0x38]
0053d8a1 jmp 0x53d8ab
0053d8a3 movss xmm0, dword ptr [ebp - 0x38]
0053d8a8 mov eax, dword ptr [ebp - 0x20]
0053d8ab inc esi
0053d8ac cmp esi, dword ptr [ebp - 0x18]
0053d8af jb 0x53d827
0053d8b5 comiss xmm0, dword ptr [0xb6a18c]
0053d8bc jae 0x53d8dd
0053d8be push ecx
0053d8bf mov ecx, dword ptr [0xbfd65c]
0053d8c5 lea eax, [ebp - 0x48]
0053d8c8 mov dword ptr [esp], 0
0053d8cf push eax
0053d8d0 mov ecx, dword ptr [ecx + 0x18190]
0053d8d6 call 0x7d9b50
0053d8db jmp 0x53d8f4
0053d8dd movss xmm0, dword ptr [ebp - 0x30]
0053d8e2 lea eax, [ebp - 0x48]
0053d8e5 movss dword ptr [ebp - 0x48], xmm0
0053d8ea movss xmm0, dword ptr [ebp - 0x34]
0053d8ef movss dword ptr [ebp - 0x44], xmm0
0053d8f4 cmp byte ptr [ebp - 0x24], 0
0053d8f8 movss xmm1, dword ptr [eax]
0053d8fc movss xmm2, dword ptr [eax + 4]
0053d901 movss dword ptr [ebp - 0x38], xmm1
0053d906 movss dword ptr [ebp - 0x30], xmm2
0053d90b jne 0x53d92e
0053d90d push dword ptr [ebp - 0x20]
0053d910 call 0x9eace5
0053d915 movss xmm1, dword ptr [ebp - 0x38]
0053d91a add esp, 4
0053d91d movss xmm2, dword ptr [ebp - 0x30]
0053d922 jmp 0x53d92e
0053d924 movss xmm2, dword ptr [ebp - 0x44]
0053d929 movss xmm1, dword ptr [ebp - 0x48]
0053d92e subss xmm1, dword ptr [edi + 0x294]
0053d936 subss xmm2, dword ptr [edi + 0x298]
0053d93e movaps xmm0, xmm1
0053d941 movss dword ptr [ebp - 0x38], xmm1
0053d946 mulss xmm0, xmm1
0053d94a movaps xmm1, xmm2
0053d94d mulss xmm1, xmm2
0053d951 movss dword ptr [ebp - 0x30], xmm2
0053d956 addss xmm0, xmm1
0053d95a call 0x4228c0
0053d95f movaps xmm1, xmm0
0053d962 comiss xmm1, dword ptr [0xb6a18c]
0053d969 movss dword ptr [ebp - 0x34], xmm1
0053d96e jbe 0x53e254
0053d974 comiss xmm1, dword ptr [0xb6aba8]
0053d97b mov eax, 0x14
0053d980 mov esi, 4
0053d985 cmova esi, eax
0053d988 call 0x6c3d90
0053d98d xor edx, edx
0053d98f div esi
0053d991 test edx, edx
0053d993 je 0x53d9a6
0053d995 movss xmm0, dword ptr [0xb6aafc]
0053d99d comiss xmm0, xmm1
0053d9a0 jbe 0x53da3b
0053d9a6 call 0x6c3d90
0053d9ab and eax, 1
0053d9ae jne 0x53da21
0053d9b0 call 0x6c3d90
0053d9b5 and eax, 1
0053d9b8 jne 0x53d9c4
0053d9ba movss xmm0, dword ptr [0xb6aae4]
0053d9c2 jmp 0x53d9cc
0053d9c4 movss xmm0, dword ptr [0xb6af48]
0053d9cc mulss xmm0, dword ptr [0xb6a230]
0053d9d4 movss dword ptr [ebp - 0x40], xmm0
0053d9d9 call 0x411fe0
0053d9de movss dword ptr [ebp - 0x44], xmm0
0053d9e3 movss xmm0, dword ptr [ebp - 0x40]
0053d9e8 call 0x412010
0053d9ed movss xmm4, dword ptr [ebp - 0x38]
0053d9f2 movss xmm5, dword ptr [ebp - 0x30]
0053d9f7 movaps xmm2, xmm4
0053d9fa mulss xmm2, dword ptr [ebp - 0x44]
0053d9ff movaps xmm1, xmm5
0053da02 mulss xmm5, dword ptr [ebp - 0x44]
0053da07 mulss xmm1, xmm0
0053da0b mulss xmm4, xmm0
0053da0f subss xmm2, xmm1
0053da13 movss xmm1, dword ptr [ebp - 0x34]
0053da18 addss xmm5, xmm4
0053da1c movaps xmm4, xmm2
0053da1f jmp 0x53da45
0053da21 movss xmm4, dword ptr [ebp - 0x38]
0053da26 movss xmm5, dword ptr [ebp - 0x30]
0053da2b xorps xmm4, xmmword ptr [0xb6c9b0]
0053da32 xorps xmm5, xmmword ptr [0xb6c9b0]
0053da39 jmp 0x53da45
0053da3b movss xmm4, dword ptr [ebp - 0x38]
0053da40 movss xmm5, dword ptr [ebp - 0x30]
0053da45 divss xmm4, xmm1
0053da49 mov dword ptr [ebp - 0x20], 0
0053da50 mov dword ptr [ebp - 0x1c], 0
0053da57 mov dword ptr [ebp - 0x18], 0
0053da5e divss xmm5, xmm1
0053da62 movss dword ptr [ebp - 0x38], xmm4
0053da67 movss dword ptr [ebp - 0x30], xmm5
0053da6c mov dword ptr [ebp - 4], 1
0053da73 mov ecx, 5
0053da78 movss xmm2, dword ptr [0xb6aafc]
0053da80 mov eax, 2
0053da85 comiss xmm2, xmm1
0053da88 mov dword ptr [ebp - 0x48], 0
0053da8f cmova eax, ecx
0053da92 lea ecx, [ebp - 0x20]
0053da95 mov dword ptr [ebp - 0x44], eax
0053da98 lea eax, [ebp - 0x48]
0053da9b push eax
0053da9c push 0
0053da9e call 0x48d900
0053daa3 mov edx, dword ptr [ebp - 0x1c]
0053daa6 xor eax, eax
0053daa8 mov ecx, dword ptr [ebp - 0x20]
0053daab mov esi, edx
0053daad sub esi, ecx
0053daaf sar esi, 3
0053dab2 test esi, esi
0053dab4 je 0x53dac1
0053dab6 cmp dword ptr [ecx + eax*8], 1
0053daba je 0x53dae9
0053dabc inc eax
0053dabd cmp eax, esi
0053dabf jb 0x53dab6
0053dac1 mov dword ptr [ebp - 0x48], 1
0053dac8 mov dword ptr [ebp - 0x44], 3
0053dacf cmp edx, dword ptr [ebp - 0x18]
0053dad2 je 0x53dafa
0053dad4 mov dword ptr [edx], 1
0053dada mov dword ptr [edx + 4], 3
0053dae1 add edx, 8
0053dae4 mov dword ptr [ebp - 0x1c], edx
0053dae7 jmp 0x53db0d
0053dae9 add dword ptr [ecx + eax*8 + 4], 3
0053daee jns 0x53db0d
0053daf0 mov dword ptr [ecx + eax*8 + 4], 0
0053daf8 jmp 0x53db0d
0053dafa lea eax, [ebp - 0x48]
0053dafd push eax
0053dafe push edx
0053daff lea ecx, [ebp - 0x20]
0053db02 call 0x48d900
0053db07 mov edx, dword ptr [ebp - 0x1c]
0053db0a mov ecx, dword ptr [ebp - 0x20]
0053db0d movss xmm0, dword ptr [ebp - 0x34]
0053db12 comiss xmm0, dword ptr [0xb6aafc]
0053db19 jbe 0x53db8e
0053db1b comiss xmm0, dword ptr [0xb6aba8]
0053db22 mov esi, 9
0053db27 mov eax, 2
0053db2c cmova eax, esi
0053db2f mov esi, edx
0053db31 sub esi, ecx
0053db33 mov dword ptr [ebp - 0x34], eax
0053db36 sar esi, 3
0053db39 xor eax, eax
0053db3b test esi, esi
0053db3d je 0x53db4b
0053db3f nop 
0053db40 cmp dword ptr [ecx + eax*8], 2
0053db44 je 0x53db6e
0053db46 inc eax
0053db47 cmp eax, esi
0053db49 jb 0x53db40
0053db4b mov eax, dword ptr [ebp - 0x34]
0053db4e mov dword ptr [ebp - 0x48], 2
0053db55 mov dword ptr [ebp - 0x44], eax
0053db58 cmp edx, dword ptr [ebp - 0x18]
0053db5b je 0x53db81
0053db5d mov dword ptr [edx], 2
0053db63 mov dword ptr [edx + 4], eax
0053db66 add edx, 8
0053db69 mov dword ptr [ebp - 0x1c], edx
0053db6c jmp 0x53db8e
0053db6e mov edx, dword ptr [ebp - 0x34]
0053db71 add dword ptr [ecx + eax*8 + 4], edx
0053db75 jns 0x53db8e
0053db77 mov dword ptr [ecx + eax*8 + 4], 0
0053db7f jmp 0x53db8e
0053db81 lea eax, [ebp - 0x48]
0053db84 push eax
0053db85 push edx
0053db86 lea ecx, [ebp - 0x20]
0053db89 call 0x48d900
0053db8e call 0x6c3d90
0053db93 movq xmm0, qword ptr [0xa08c44]
0053db9b lea ecx, [ebp - 0x20]
0053db9e or eax, 1
0053dba1 movq qword ptr [ebp - 0x4c], xmm0
0053dba6 mov dword ptr [ebp - 0x50], eax
0053dba9 sub esp, 0x10
0053dbac mov eax, dword ptr [0xa08c4c]
0053dbb1 mov dword ptr [ebp - 0x44], eax
0053dbb4 mov eax, esp
0053dbb6 movups xmm0, xmmword ptr [ebp - 0x50]
0053dbba movups xmmword ptr [eax], xmm0
0053dbbd call 0x489420
0053dbc2 sub eax, 0
0053dbc5 je 0x53de63
0053dbcb sub eax, 1
0053dbce je 0x53dd22
0053dbd4 sub eax, 1
0053dbd7 jne 0x53dfa4
0053dbdd mov esi, dword ptr [edi + 0x70]
0053dbe0 test esi, esi
0053dbe2 je 0x53dc2e
0053dbe4 cmp dword ptr [esi + 0x14], 0x10
0053dbe8 mov eax, esi
0053dbea jb 0x53dbee
0053dbec mov eax, dword ptr [esi]
0053dbee mov ecx, 0xb43110
0053dbf3 mov dl, byte ptr [eax]
0053dbf5 cmp dl, byte ptr [ecx]
0053dbf7 jne 0x53dc13
0053dbf9 test dl, dl
0053dbfb je 0x53dc0f
0053dbfd mov dl, byte ptr [eax + 1]
0053dc00 cmp dl, byte ptr [ecx + 1]
0053dc03 jne 0x53dc13
0053dc05 add eax, 2
0053dc08 add ecx, 2
0053dc0b test dl, dl
0053dc0d jne 0x53dbf3
0053dc0f xor eax, eax
0053dc11 jmp 0x53dc18
0053dc13 sbb eax, eax
0053dc15 or eax, 1
0053dc18 test eax, eax
0053dc1a jne 0x53dc2e
0053dc1c cmp byte ptr [esi + 0x34], al
0053dc1f je 0x53dc4f
0053dc21 cmp byte ptr [edi + 0x80], al
0053dc27 lea esi, [edi + 0x3c]
0053dc2a jne 0x53dc4f
0053dc2c jmp 0x53dc31
0053dc2e lea esi, [edi + 0x3c]
0053dc31 push 1
0053dc33 push 0xb43110
0053dc38 mov ecx, esi
0053dc3a call 0x405740
0053dc3f test al, al
0053dc41 je 0x53dc4f
0053dc43 lea ecx, [esi + 0x30]
0053dc46 call 0x405330
0053dc4b mov byte ptr [esi + 0x44], 1
0053dc4f call 0x6c3d90
0053dc54 xorps xmm0, xmm0
0053dc57 cvtsi2sd xmm0, eax
0053dc5b shr eax, 0x1f
0053dc5e addsd xmm0, qword ptr [eax*8 + 0xb6c940]
0053dc67 cvtpd2ps xmm0, xmm0
0053dc6b mulss xmm0, dword ptr [0xb6a19c]
0053dc73 mulss xmm0, dword ptr [0xb6a864]
0053dc7b addss xmm0, dword ptr [0xb6a974]
0053dc83 movaps xmm3, xmm0
0053dc86 mulss xmm3, dword ptr [ebp - 0x38]
0053dc8b movss dword ptr [ebp - 0x40], xmm3
0053dc90 movss xmm3, dword ptr [ebp - 0x30]
0053dc95 mulss xmm3, xmm0
0053dc99 movss dword ptr [ebp - 0x30], xmm3
0053dc9e call 0x6c3d90
0053dca3 xorps xmm0, xmm0
0053dca6 cvtsi2sd xmm0, eax
0053dcaa shr eax, 0x1f
0053dcad addsd xmm0, qword ptr [eax*8 + 0xb6c940]
0053dcb6 cvtpd2ps xmm0, xmm0
0053dcba mulss xmm0, dword ptr [0xb6a19c]
0053dcc2 mulss xmm0, dword ptr [0xb6a9c8]
0053dcca subss xmm0, dword ptr [0xb6a974]
0053dcd2 mulss xmm0, dword ptr [0xb6a230]
0053dcda movss dword ptr [ebp - 0x44], xmm0
0053dcdf call 0x411fe0
0053dce4 movss dword ptr [ebp - 0x34], xmm0
0053dce9 movss xmm0, dword ptr [ebp - 0x44]
0053dcee call 0x412010
0053dcf3 movss xmm3, dword ptr [ebp - 0x40]
0053dcf8 movss xmm5, dword ptr [ebp - 0x30]
0053dcfd movaps xmm4, xmm3
0053dd00 mulss xmm4, dword ptr [ebp - 0x34]
0053dd05 movaps xmm1, xmm5
0053dd08 mulss xmm5, dword ptr [ebp - 0x34]
0053dd0d mulss xmm1, xmm0
0053dd11 mulss xmm3, xmm0
0053dd15 subss xmm4, xmm1
0053dd19 addss xmm5, xmm3
0053dd1d jmp 0x53dfae
0053dd22 mov esi, dword ptr [edi + 0x70]
0053dd25 test esi, esi
0053dd27 je 0x53dd73
0053dd29 cmp dword ptr [esi + 0x14], 0x10
0053dd2d mov eax, esi
0053dd2f jb 0x53dd33
0053dd31 mov eax, dword ptr [esi]
0053dd33 mov ecx, 0xb405cc
0053dd38 mov dl, byte ptr [eax]
0053dd3a cmp dl, byte ptr [ecx]
0053dd3c jne 0x53dd58
0053dd3e test dl, dl
0053dd40 je 0x53dd54
0053dd42 mov dl, byte ptr [eax + 1]
0053dd45 cmp dl, byte ptr [ecx + 1]
0053dd48 jne 0x53dd58
0053dd4a add eax, 2
0053dd4d add ecx, 2
0053dd50 test dl, dl
0053dd52 jne 0x53dd38
0053dd54 xor eax, eax
0053dd56 jmp 0x53dd5d
0053dd58 sbb eax, eax
0053dd5a or eax, 1
0053dd5d test eax, eax
0053dd5f jne 0x53dd73
0053dd61 cmp byte ptr [esi + 0x34], al
0053dd64 je 0x53dd94
0053dd66 cmp byte ptr [edi + 0x80], al
0053dd6c lea esi, [edi + 0x3c]
0053dd6f jne 0x53dd94
0053dd71 jmp 0x53dd76
0053dd73 lea esi, [edi + 0x3c]
0053dd76 push 1
0053dd78 push 0xb405cc
0053dd7d mov ecx, esi
0053dd7f call 0x405740
0053dd84 test al, al
0053dd86 je 0x53dd94
0053dd88 lea ecx, [esi + 0x30]
0053dd8b call 0x405330
0053dd90 mov byte ptr [esi + 0x44], 1
0053dd94 call 0x6c3d90
0053dd99 xorps xmm0, xmm0
0053dd9c movss xmm3, dword ptr [ebp - 0x30]
0053dda1 cvtsi2sd xmm0, eax
0053dda5 shr eax, 0x1f
0053dda8 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
0053ddb1 cvtpd2ps xmm0, xmm0
0053ddb5 mulss xmm0, dword ptr [0xb6a19c]
0053ddbd addss xmm0, xmm0
0053ddc1 addss xmm0, dword ptr [0xb6a940]
0053ddc9 movaps xmm2, xmm0
0053ddcc mulss xmm3, xmm0
0053ddd0 mulss xmm2, dword ptr [ebp - 0x38]
0053ddd5 movss dword ptr [ebp - 0x30], xmm3
0053ddda movss dword ptr [ebp - 0x40], xmm2
0053dddf call 0x6c3d90
0053dde4 xorps xmm0, xmm0
0053dde7 cvtsi2sd xmm0, eax
0053ddeb shr eax, 0x1f
0053ddee addsd xmm0, qword ptr [eax*8 + 0xb6c940]
0053ddf7 cvtpd2ps xmm0, xmm0
0053ddfb mulss xmm0, dword ptr [0xb6a19c]
0053de03 mulss xmm0, dword ptr [0xb6aa3c]
0053de0b subss xmm0, dword ptr [0xb6a9c8]
0053de13 mulss xmm0, dword ptr [0xb6a230]
0053de1b movss dword ptr [ebp - 0x44], xmm0
0053de20 call 0x411fe0
0053de25 movss dword ptr [ebp - 0x34], xmm0
0053de2a movss xmm0, dword ptr [ebp - 0x44]
0053de2f call 0x412010
0053de34 movss xmm3, dword ptr [ebp - 0x40]
0053de39 movss xmm5, dword ptr [ebp - 0x30]
0053de3e movaps xmm4, xmm3
0053de41 mulss xmm4, dword ptr [ebp - 0x34]
0053de46 movaps xmm1, xmm5
0053de49 mulss xmm5, dword ptr [ebp - 0x34]
0053de4e mulss xmm1, xmm0
0053de52 mulss xmm3, xmm0
0053de56 subss xmm4, xmm1
0053de5a addss xmm5, xmm3
0053de5e jmp 0x53dfae
0053de63 mov esi, dword ptr [edi + 0x70]
0053de66 test esi, esi
0053de68 je 0x53debb
0053de6a cmp dword ptr [esi + 0x14], 0x10
0053de6e mov eax, esi
0053de70 jb 0x53de74
0053de72 mov eax, dword ptr [esi]
0053de74 mov ecx, 0xb43124
0053de79 nop dword ptr [eax]
0053de80 mov dl, byte ptr [eax]
0053de82 cmp dl, byte ptr [ecx]
0053de84 jne 0x53dea0
0053de86 test dl, dl
0053de88 je 0x53de9c
0053de8a mov dl, byte ptr [eax + 1]
0053de8d cmp dl, byte ptr [ecx + 1]
0053de90 jne 0x53dea0
0053de92 add eax, 2
0053de95 add ecx, 2
0053de98 test dl, dl
0053de9a jne 0x53de80
0053de9c xor eax, eax
0053de9e jmp 0x53dea5
0053dea0 sbb eax, eax
0053dea2 or eax, 1
0053dea5 test eax, eax
0053dea7 jne 0x53debb
0053dea9 cmp byte ptr [esi + 0x34], al
0053deac je 0x53dedc
0053deae cmp byte ptr [edi + 0x80], al
0053deb4 lea esi, [edi + 0x3c]
0053deb7 jne 0x53dedc
0053deb9 jmp 0x53debe
0053debb lea esi, [edi + 0x3c]
0053debe push 1
0053dec0 push 0xb43124
0053dec5 mov ecx, esi
0053dec7 call 0x405740
0053decc test al, al
0053dece je 0x53dedc
0053ded0 lea ecx, [esi + 0x30]
0053ded3 call 0x405330
0053ded8 mov byte ptr [esi + 0x44], 1
0053dedc call 0x6c3d90
0053dee1 xorps xmm0, xmm0
0053dee4 movss xmm3, dword ptr [ebp - 0x30]
0053dee9 cvtsi2sd xmm0, eax
0053deed shr eax, 0x1f
0053def0 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
0053def9 cvtpd2ps xmm0, xmm0
0053defd mulss xmm0, dword ptr [0xb6a19c]
0053df05 addss xmm0, dword ptr [0xb6a8f4]
0053df0d movaps xmm2, xmm0
0053df10 mulss xmm3, xmm0
0053df14 mulss xmm2, dword ptr [ebp - 0x38]
0053df19 movss dword ptr [ebp - 0x30], xmm3
0053df1e movss dword ptr [ebp - 0x40], xmm2
0053df23 call 0x6c3d90
0053df28 xorps xmm0, xmm0
0053df2b cvtsi2sd xmm0, eax
0053df2f shr eax, 0x1f
0053df32 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
0053df3b cvtpd2ps xmm0, xmm0
0053df3f mulss xmm0, dword ptr [0xb6a19c]
0053df47 mulss xmm0, dword ptr [0xb6aae4]
0053df4f subss xmm0, dword ptr [0xb6aa4c]
0053df57 mulss xmm0, dword ptr [0xb6a230]
0053df5f movss dword ptr [ebp - 0x44], xmm0
0053df64 call 0x411fe0
0053df69 movss dword ptr [ebp - 0x34], xmm0
0053df6e movss xmm0, dword ptr [ebp - 0x44]
0053df73 call 0x412010
0053df78 movss xmm3, dword ptr [ebp - 0x40]
0053df7d movss xmm5, dword ptr [ebp - 0x30]
0053df82 movaps xmm4, xmm3
0053df85 mulss xmm4, dword ptr [ebp - 0x34]
0053df8a movaps xmm1, xmm5
0053df8d mulss xmm5, dword ptr [ebp - 0x34]
0053df92 mulss xmm1, xmm0
0053df96 mulss xmm3, xmm0
0053df9a subss xmm4, xmm1
0053df9e addss xmm5, xmm3
0053dfa2 jmp 0x53dfae
0053dfa4 movss xmm4, dword ptr [ebp - 0x38]
0053dfa9 movss xmm5, dword ptr [ebp - 0x30]
0053dfae mov edx, dword ptr [ebp - 0x20]
0053dfb1 movss dword ptr [edi + 0x28c], xmm4
0053dfb9 movss dword ptr [edi + 0x290], xmm5
0053dfc1 mov dword ptr [edi + 0xab4], 6
0053dfcb test edx, edx
0053dfcd je 0x53e254
0053dfd3 mov ecx, dword ptr [ebp - 0x18]
0053dfd6 mov eax, edx
0053dfd8 sub ecx, edx
0053dfda and ecx, 0xfffffff8
0053dfdd cmp ecx, 0x1000
0053dfe3 jb 0x53dffb
0053dfe5 mov edx, dword ptr [edx - 4]
0053dfe8 add ecx, 0x23
0053dfeb sub eax, edx
0053dfed add eax, -4
0053dff0 cmp eax, 0x1f
0053dff3 jbe 0x53dffb
0053dff5 call dword ptr [0xa065ac]
0053dffb push ecx
0053dffc push edx
0053dffd call 0x9eb08e
0053e002 add esp, 8
0053e005 jmp 0x53e254
0053e00a mov esi, dword ptr [edi + 0x70]
0053e00d test esi, esi
0053e00f je 0x53e05b
0053e011 cmp dword ptr [esi + 0x14], 0x10
0053e015 mov eax, esi
0053e017 jb 0x53e01b
0053e019 mov eax, dword ptr [esi]
0053e01b mov ecx, 0xb3fd8c
0053e020 mov dl, byte ptr [eax]
0053e022 cmp dl, byte ptr [ecx]
0053e024 jne 0x53e040
0053e026 test dl, dl
0053e028 je 0x53e03c
0053e02a mov dl, byte ptr [eax + 1]
0053e02d cmp dl, byte ptr [ecx + 1]
0053e030 jne 0x53e040
0053e032 add eax, 2
0053e035 add ecx, 2
0053e038 test dl, dl
0053e03a jne 0x53e020
0053e03c xor eax, eax
0053e03e jmp 0x53e045
0053e040 sbb eax, eax
0053e042 or eax, 1
0053e045 test eax, eax
0053e047 jne 0x53e05b
0053e049 cmp byte ptr [esi + 0x34], al
0053e04c je 0x53e07c
0053e04e cmp byte ptr [edi + 0x80], al
0053e054 lea esi, [edi + 0x3c]
0053e057 jne 0x53e07c
0053e059 jmp 0x53e05e
0053e05b lea esi, [edi + 0x3c]
0053e05e push 1
0053e060 push 0xb3fd8c
0053e065 mov ecx, esi
0053e067 call 0x405740
0053e06c test al, al
0053e06e je 0x53e07c
0053e070 lea ecx, [esi + 0x30]
0053e073 call 0x405330
0053e078 mov byte ptr [esi + 0x44], 1
0053e07c cmp dword ptr [edi + 0x30], 0
0053e080 mov dword ptr [edi + 0xab4], 3
0053e08a mov dword ptr [edi + 0x180], 2
0053e094 jbe 0x53e254
0053e09a movss xmm2, dword ptr [0xb6a19c]
0053e0a2 movss xmm3, dword ptr [0xb6a9c8]
0053e0aa movss xmm4, dword ptr [0xb6aa3c]
0053e0b2 mov dword ptr [ebp - 0x34], 0
0053e0b9 nop dword ptr [eax]
0053e0c0 mov edx, dword ptr [edi + 0x334]
0053e0c6 test edx, edx
0053e0c8 jne 0x53e0fc
0053e0ca push 0xb4d6c4
0053e0cf push 3
0053e0d1 call 0x95e330
0053e0d6 mov edx, dword ptr [edi + 0x334]
0053e0dc add esp, 8
0053e0df movss xmm2, dword ptr [0xb6a19c]
0053e0e7 movss xmm3, dword ptr [0xb6a9c8]
0053e0ef movss xmm4, dword ptr [0xb6aa3c]
0053e0f7 test edx, edx
0053e0f9 jne 0x53e0fc
0053e0fb int3 
0053e0fc mov ecx, dword ptr [edi + 0x338]
0053e102 mov eax, edx
0053e104 shr eax, cl
0053e106 mov ecx, dword ptr [edi + 0x33c]
0053e10c xor eax, edx
0053e10e mov edx, eax
0053e110 shl edx, cl
0053e112 mov ecx, dword ptr [edi + 0x340]
0053e118 xor edx, eax
0053e11a mov esi, edx
0053e11c shr esi, cl
0053e11e xor esi, edx
0053e120 mov dword ptr [edi + 0x334], esi
0053e126 call 0x6c3d90
0053e12b movd xmm0, eax
0053e12f cvtdq2pd xmm0, xmm0
0053e133 shr eax, 0x1f
0053e136 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
0053e13f cvtpd2ps xmm1, xmm0
0053e143 mulss xmm1, xmm2
0053e147 call 0x6c3d90
0053e14c mov ecx, dword ptr [0xbfd65c]
0053e152 push esi
0053e153 mulss xmm1, xmm4
0053e157 push 0
0053e159 movd xmm0, eax
0053e15d cvtdq2pd xmm0, xmm0
0053e161 shr eax, 0x1f
0053e164 push dword ptr [edi + 0x320]
0053e16a addsd xmm0, qword ptr [eax*8 + 0xb6c940]
0053e173 subss xmm1, xmm3
0053e177 push 0xc02fec
0053e17c lea eax, [ebp - 0x48]
0053e17f push eax
0053e180 push dword ptr [edi + 0x2c]
0053e183 addss xmm1, dword ptr [edi + 0x298]
0053e18b cvtpd2ps xmm0, xmm0
0053e18f push dword ptr [edi + 0x28]
0053e192 mulss xmm0, xmm2
0053e196 movss dword ptr [ebp - 0x44], xmm1
0053e19b mulss xmm0, xmm4
0053e19f subss xmm0, xmm3
0053e1a3 addss xmm0, dword ptr [edi + 0x294]
0053e1ab movss dword ptr [ebp - 0x48], xmm0
0053e1b0 call 0x422e20
0053e1b5 mov eax, dword ptr [ebp - 0x34]
0053e1b8 movss xmm2, dword ptr [0xb6a19c]
0053e1c0 inc eax
0053e1c1 movss xmm3, dword ptr [0xb6a9c8]
0053e1c9 movss xmm4, dword ptr [0xb6aa3c]
0053e1d1 mov dword ptr [ebp - 0x34], eax
0053e1d4 cmp eax, dword ptr [edi + 0x30]
0053e1d7 jb 0x53e0c0
0053e1dd call 0x6c3d90
0053e1e2 xorps xmm0, xmm0
0053e1e5 cvtsi2sd xmm0, eax
0053e1e9 shr eax, 0x1f
0053e1ec addsd xmm0, qword ptr [eax*8 + 0xb6c940]
0053e1f5 cvtpd2ps xmm1, xmm0
0053e1f9 mulss xmm1, xmm2
0053e1fd call 0x6c3d90
0053e202 xorps xmm0, xmm0
0053e205 mulss xmm1, xmm4
0053e209 mov dword ptr [edi + 0x30], 0
0053e210 cvtsi2sd xmm0, eax
0053e214 shr eax, 0x1f
0053e217 subss xmm1, xmm3
0053e21b addsd xmm0, qword ptr [eax*8 + 0xb6c940]
0053e224 addss xmm1, dword ptr [edi + 0x298]
0053e22c cvtpd2ps xmm0, xmm0
0053e230 movss dword ptr [edi + 0x298], xmm1
0053e238 mulss xmm0, xmm2
0053e23c mulss xmm0, xmm4
0053e240 subss xmm0, xmm3
0053e244 addss xmm0, dword ptr [edi + 0x294]
0053e24c movss dword ptr [edi + 0x294], xmm0
0053e254 mov ecx, dword ptr [ebp - 0xc]
0053e257 mov dword ptr fs:[0], ecx
0053e25e pop ecx
0053e25f pop edi
0053e260 pop esi
0053e261 mov ecx, dword ptr [ebp - 0x14]
0053e264 xor ecx, ebp
0053e266 call 0x9eacd7
0053e26b mov esp, ebp
0053e26d pop ebp
0053e26e mov esp, ebx
0053e270 pop ebx
0053e271 ret 
