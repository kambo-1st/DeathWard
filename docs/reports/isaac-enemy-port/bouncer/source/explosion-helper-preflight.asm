006d6570 push ebp
006d6571 mov ebp, esp
006d6573 push -1
006d6575 push 0x9f5da0
006d657a mov eax, dword ptr fs:[0]
006d6580 push eax
006d6581 sub esp, 0x80
006d6587 mov eax, dword ptr [0xbaa3b4]
006d658c xor eax, ebp
006d658e mov dword ptr [ebp - 0x14], eax
006d6591 push ebx
006d6592 push esi
006d6593 push edi
006d6594 push eax
006d6595 lea eax, [ebp - 0xc]
006d6598 mov dword ptr fs:[0], eax
006d659e mov ebx, ecx
006d65a0 mov ecx, dword ptr [0xbfd65c]
006d65a6 movss xmm0, dword ptr [0xb6a614]
006d65ae mov esi, dword ptr [ebp + 8]
006d65b1 mov edi, dword ptr [ebp + 0x10]
006d65b4 push 1
006d65b6 push 0
006d65b8 lea ecx, [ecx + 0x1ba40]
006d65be mov dword ptr [ebp - 0x60], esi
006d65c1 push 0x86
006d65c6 movss dword ptr [ebp - 0x50], xmm0
006d65cb call 0x91d550
006d65d0 movss xmm0, dword ptr [ebp + 0xc]
006d65d5 test eax, eax
006d65d7 je 0x6d65ec
006d65d9 movss xmm2, dword ptr [0xb6a7b0]
006d65e1 addss xmm0, xmm0
006d65e5 movss dword ptr [ebp - 0x50], xmm2
006d65ea jmp 0x6d65f1
006d65ec movss xmm2, dword ptr [ebp - 0x50]
006d65f1 cmp byte ptr [ebp + 0x14], 0
006d65f5 movss dword ptr [ebp - 0x54], xmm0
006d65fa je 0x6d668f
006d6600 call 0x6c3d90
006d6605 mov ecx, dword ptr [0xbfd65c]
006d660b push eax
006d660c push 0
006d660e push 0
006d6610 push 0xc02fec
006d6615 push esi
006d6616 push 0x22
006d6618 push 0x3e8
006d661d call 0x422e20
006d6622 push 1
006d6624 mov esi, eax
006d6626 mov dword ptr [ebp - 0x20], 0
006d662d push 0
006d662f push 0xff
006d6634 xorps xmm0, xmm0
006d6637 mov dword ptr [ebp - 0x1c], 0
006d663e mov eax, dword ptr [esi]
006d6640 lea ecx, [ebp - 0x40]
006d6643 push -1
006d6645 movups xmmword ptr [ebp - 0x30], xmm0
006d6649 push ecx
006d664a movaps xmm0, xmmword ptr [0xb6c6e0]
006d6651 mov ecx, esi
006d6653 mov dword ptr [ebp - 0x18], 0
006d665a movups xmmword ptr [ebp - 0x40], xmm0
006d665e call dword ptr [eax + 0x38]
006d6661 movss xmm2, dword ptr [ebp - 0x50]
006d6666 movaps xmm1, xmm2
006d6669 movaps xmm0, xmm2
006d666c mulss xmm1, dword ptr [0xbc7a28]
006d6674 mulss xmm0, dword ptr [0xbc7a2c]
006d667c movss dword ptr [esi + 0xd8], xmm1
006d6684 movss dword ptr [esi + 0xdc], xmm0
006d668c mov esi, dword ptr [ebp - 0x60]
006d668f comiss xmm2, dword ptr [0xb6a754]
006d6696 jbe 0x6d671e
006d669c mov ecx, dword ptr [0xbfd680]
006d66a2 push 0x25
006d66a4 lea ecx, [ecx + 0x29de0]
006d66aa call 0x8892c0
006d66af mov ecx, dword ptr [0xbfd680]
006d66b5 sub esp, 8
006d66b8 add ecx, 0x29de0
006d66be mov dword ptr [esp + 4], 0
006d66c6 mov dword ptr [esp], 0x3f800000
006d66cd push 0
006d66cf push 0
006d66d1 push ecx
006d66d2 mov dword ptr [esp], 0x3f800000
006d66d9 push 0x25
006d66db call 0x888de0
006d66e0 mov ecx, dword ptr [0xbfd680]
006d66e6 sub esp, 8
006d66e9 add ecx, 0x29de0
006d66ef mov dword ptr [esp + 4], 0
006d66f7 mov dword ptr [esp], 0x3f000000
006d66fe push 0
006d6700 push 0x14
006d6702 push ecx
006d6703 mov dword ptr [esp], 0x3f99999a
006d670a push 0x25
006d670c call 0x888de0
006d6711 mov ecx, dword ptr [0xbfd65c]
006d6717 push 3
006d6719 call 0x6d5ad0
006d671e mov ecx, dword ptr [ebx + 0x18190]
006d6724 lea eax, [ebp - 0x88]
006d672a movss xmm3, dword ptr [ebp - 0x54]
006d672f add ecx, 0x1218
006d6735 push -1
006d6737 push esi
006d6738 push eax
006d6739 call 0x4157f0
006d673e xor ecx, ecx
006d6740 mov dword ptr [ebp - 4], 0
006d6747 mov dword ptr [ebp - 0x68], ecx
006d674a cmp dword ptr [ebp - 0x7c], ecx
006d674d jbe 0x6d6c0e
006d6753 mov eax, dword ptr [ebp - 0x84]
006d6759 mov esi, dword ptr [eax + ecx*4]
006d675c mov ebx, dword ptr [esi + 0x28]
006d675f cmp ebx, 1
006d6762 jne 0x6d677e
006d6764 test edi, edi
006d6766 je 0x6d678c
006d6768 push 0
006d676a push 0x20000000
006d676f mov ecx, edi
006d6771 call 0x4122f0
006d6776 test al, al
006d6778 jne 0x6d6bfe
006d677e test edi, edi
006d6780 je 0x6d678c
006d6782 cmp dword ptr [edi + 0x28], 1
006d6786 mov byte ptr [ebp - 0x41], 1
006d678a je 0x6d6790
006d678c mov byte ptr [ebp - 0x41], 0
006d6790 push 0
006d6792 mov ecx, esi
006d6794 call 0x684630
006d6799 test al, al
006d679b jne 0x6d67c9
006d679d cmp ebx, 4
006d67a0 je 0x6d67c9
006d67a2 cmp ebx, 5
006d67a5 je 0x6d67c9
006d67a7 cmp ebx, 9
006d67aa jne 0x6d67b6
006d67ac cmp byte ptr [ebp - 0x41], al
006d67af jne 0x6d67c9
006d67b1 jmp 0x6d6bfe
006d67b6 cmp byte ptr [ebp - 0x41], 0
006d67ba jne 0x6d6bfe
006d67c0 cmp ebx, 1
006d67c3 jne 0x6d6bfe
006d67c9 cmp esi, edi
006d67cb je 0x6d6bfe
006d67d1 movss xmm0, dword ptr [esi + 0x2d4]
006d67d9 xorps xmm2, xmm2
006d67dc ucomiss xmm0, xmm2
006d67df lahf 
006d67e0 test ah, 0x44
006d67e3 jnp 0x6d6bfe
006d67e9 mov eax, dword ptr [esi + 0x160]
006d67ef and eax, 0x4000000
006d67f4 or eax, 0
006d67f7 jne 0x6d6bfe
006d67fd mov eax, dword ptr [ebp - 0x60]
006d6800 movss xmm1, dword ptr [esi + 0x298]
006d6808 movss xmm0, dword ptr [ebp - 0x54]
006d680d addss xmm0, dword ptr [esi + 0x2c8]
006d6815 subss xmm1, dword ptr [eax + 4]
006d681a movss xmm2, dword ptr [esi + 0x294]
006d6822 subss xmm2, dword ptr [eax]
006d6826 movss dword ptr [ebp - 0x58], xmm0
006d682b movaps xmm0, xmm1
006d682e movss dword ptr [ebp - 0x4c], xmm1
006d6833 mulss xmm0, xmm1
006d6837 movaps xmm1, xmm2
006d683a movss dword ptr [ebp - 0x48], xmm2
006d683f mulss xmm1, xmm2
006d6843 addss xmm0, xmm1
006d6847 call 0x4228c0
006d684c movaps xmm4, xmm0
006d684f xorps xmm2, xmm2
006d6852 comiss xmm4, xmm2
006d6855 movss dword ptr [ebp - 0x64], xmm4
006d685a jbe 0x6d6bfe
006d6860 cmp ebx, 9
006d6863 jne 0x6d68fa
006d6869 test edi, edi
006d686b je 0x6d6bfe
006d6871 mov eax, dword ptr [edi + 0x28]
006d6874 cmp eax, 1
006d6877 je 0x6d6882
006d6879 cmp eax, 3
006d687c jne 0x6d6bfe
006d6882 comiss xmm4, xmm2
006d6885 movss xmm1, dword ptr [esi + 0x2b8]
006d688d movss xmm0, dword ptr [esi + 0x2bc]
006d6895 jbe 0x6d68d5
006d6897 mulss xmm0, xmm0
006d689b mulss xmm1, xmm1
006d689f addss xmm0, xmm1
006d68a3 call 0x4228c0
006d68a8 divss xmm0, dword ptr [ebp - 0x64]
006d68ad lea eax, [ebp - 0x70]
006d68b0 push eax
006d68b1 push ecx
006d68b2 mov ecx, esi
006d68b4 movaps xmm1, xmm0
006d68b7 mulss xmm0, dword ptr [ebp - 0x4c]
006d68bc mulss xmm1, dword ptr [ebp - 0x48]
006d68c1 movss dword ptr [ebp - 0x6c], xmm0
006d68c6 movss dword ptr [ebp - 0x70], xmm1
006d68cb call 0x62f620
006d68d0 jmp 0x6d6bfe
006d68d5 movss xmm2, dword ptr [ebp - 0x48]
006d68da lea eax, [ebp - 0x70]
006d68dd movss xmm1, dword ptr [ebp - 0x4c]
006d68e2 push eax
006d68e3 push ecx
006d68e4 mov ecx, esi
006d68e6 movss dword ptr [ebp - 0x70], xmm2
006d68eb movss dword ptr [ebp - 0x6c], xmm1
006d68f0 call 0x62f620
006d68f5 jmp 0x6d6bfe
006d68fa movss xmm0, dword ptr [ebp - 0x58]
006d68ff movss xmm2, dword ptr [0xb6a928]
006d6907 subss xmm0, xmm4
006d690b minss xmm2, xmm0
006d690f movss xmm0, dword ptr [esi + 0x2d4]
006d6917 comiss xmm0, dword ptr [0xb6a9c8]
006d691e addss xmm2, xmm2
006d6922 jbe 0x6d692e
006d6924 mulss xmm2, dword ptr [0xb6a480]
006d692c jmp 0x6d6952
006d692e comiss xmm0, dword ptr [0xb6aa0c]
006d6935 jbe 0x6d6941
006d6937 mulss xmm2, dword ptr [0xb6a350]
006d693f jmp 0x6d6952
006d6941 comiss xmm0, dword ptr [0xb6aa60]
006d6948 jbe 0x6d6952
006d694a mulss xmm2, dword ptr [0xb6a220]
006d6952 movss xmm3, dword ptr [ebp - 0x48]
006d6957 mov ecx, esi
006d6959 divss xmm3, xmm4
006d695d push 0
006d695f movss xmm0, dword ptr [esi + 0x2b8]
006d6967 mulss xmm0, dword ptr [0xb6a480]
006d696f mulss xmm3, xmm2
006d6973 movss xmm1, dword ptr [esi + 0x2bc]
006d697b mulss xmm1, dword ptr [0xb6a480]
006d6983 mulss xmm3, dword ptr [ebp - 0x50]
006d6988 addss xmm3, xmm0
006d698c movss xmm0, dword ptr [ebp - 0x4c]
006d6991 divss xmm0, xmm4
006d6995 movss dword ptr [esi + 0x2b8], xmm3
006d699d mulss xmm0, xmm2
006d69a1 mulss xmm0, dword ptr [ebp - 0x50]
006d69a6 addss xmm0, xmm1
006d69aa movss dword ptr [esi + 0x2bc], xmm0
006d69b2 call 0x684630
006d69b7 test al, al
006d69b9 je 0x6d6a29
006d69bb cmp byte ptr [ebp - 0x41], 0
006d69bf je 0x6d6a29
006d69c1 movss xmm0, dword ptr [ebp - 0x50]
006d69c6 comiss xmm0, dword ptr [0xb6a754]
006d69cd jbe 0x6d6a29
006d69cf mov ecx, dword ptr [0xc02fec]
006d69d5 mov eax, dword ptr [0xc02ff0]
006d69da push 0x1e
006d69dc mov dword ptr [ebp - 0x2c], ecx
006d69df mov dword ptr [ebp - 0x24], ecx
006d69e2 lea ecx, [ebp - 0x3c]
006d69e5 push ecx
006d69e6 push 0
006d69e8 mov dword ptr [ebp - 0x28], eax
006d69eb mov dword ptr [ebp - 0x20], eax
006d69ee mov eax, dword ptr [esi]
006d69f0 push 0
006d69f2 push ecx
006d69f3 mov ecx, esi
006d69f5 mov dword ptr [ebp - 0x3c], 0
006d69fc mov dword ptr [ebp - 0x38], 0
006d6a03 mov dword ptr [ebp - 0x34], 0
006d6a0a mov dword ptr [ebp - 0x30], 0
006d6a11 mov dword ptr [ebp - 0x1c], 0
006d6a18 mov dword ptr [ebp - 0x18], 0
006d6a1f mov dword ptr [esp], 0x41200000
006d6a26 call dword ptr [eax + 0x20]
006d6a29 cmp byte ptr [ebp + 0x18], 0
006d6a2d je 0x6d6bfe
006d6a33 push 0
006d6a35 mov ecx, esi
006d6a37 call 0x684630
006d6a3c test al, al
006d6a3e je 0x6d6bfe
006d6a44 movss xmm0, dword ptr [esi + 0x2d4]
006d6a4c comiss xmm0, dword ptr [0xb6a18c]
006d6a53 jbe 0x6d6bfe
006d6a59 mov eax, dword ptr [esi + 0x164]
006d6a5f mov ecx, dword ptr [esi + 0x160]
006d6a65 mov dword ptr [ebp - 0x58], eax
006d6a68 mov eax, ecx
006d6a6a and eax, 0x4000000
006d6a6f or eax, 0
006d6a72 jne 0x6d6bfe
006d6a78 and ecx, 0x20000000
006d6a7e or ecx, eax
006d6a80 jne 0x6d6bfe
006d6a86 mov eax, dword ptr [ebp - 0x60]
006d6a89 movss xmm1, dword ptr [esi + 0x298]
006d6a91 movss xmm2, dword ptr [esi + 0x294]
006d6a99 subss xmm1, dword ptr [eax + 4]
006d6a9e subss xmm2, dword ptr [eax]
006d6aa2 movaps xmm0, xmm1
006d6aa5 movss dword ptr [ebp - 0x48], xmm1
006d6aaa mulss xmm0, xmm1
006d6aae movaps xmm1, xmm2
006d6ab1 mulss xmm1, xmm2
006d6ab5 movss dword ptr [ebp - 0x4c], xmm2
006d6aba addss xmm0, xmm1
006d6abe call 0x4228c0
006d6ac3 movss xmm2, dword ptr [ebp - 0x4c]
006d6ac8 movaps xmm1, xmm0
006d6acb movss xmm3, dword ptr [ebp - 0x48]
006d6ad0 divss xmm2, xmm1
006d6ad4 divss xmm3, xmm1
006d6ad8 movss dword ptr [ebp - 0x4c], xmm2
006d6add movss dword ptr [ebp - 0x48], xmm3
006d6ae2 test edi, edi
006d6ae4 je 0x6d6af0
006d6ae6 movss xmm0, dword ptr [edi + 0x2c8]
006d6aee jmp 0x6d6af8
006d6af0 movss xmm0, dword ptr [0xb6a98c]
006d6af8 addss xmm0, dword ptr [esi + 0x2c8]
006d6b00 movss xmm4, dword ptr [0xb6a974]
006d6b08 subss xmm1, xmm0
006d6b0c movss xmm0, dword ptr [ebp - 0x54]
006d6b11 ucomiss xmm4, xmm0
006d6b14 addss xmm1, dword ptr [esi + 0x2d4]
006d6b1c lahf 
006d6b1d movss dword ptr [ebp - 0x58], xmm1
006d6b22 test ah, 0x44
006d6b25 jp 0x6d6b52
006d6b27 push 0xb5d590
006d6b2c push 3
006d6b2e call 0x95e330
006d6b33 movss xmm1, dword ptr [ebp - 0x58]
006d6b38 add esp, 8
006d6b3b movss xmm2, dword ptr [ebp - 0x4c]
006d6b40 movss xmm3, dword ptr [ebp - 0x48]
006d6b45 movss xmm0, dword ptr [ebp - 0x54]
006d6b4a movss xmm4, dword ptr [0xb6a974]
006d6b52 subss xmm0, xmm4
006d6b56 mov dword ptr [ebp - 0x58], 0
006d6b5d subss xmm1, xmm4
006d6b61 lea eax, [ebp - 0x58]
006d6b64 lea ecx, [ebp - 0x64]
006d6b67 divss xmm1, xmm0
006d6b6b xorps xmm0, xmm0
006d6b6e comiss xmm0, xmm1
006d6b71 movss dword ptr [ebp - 0x64], xmm1
006d6b76 movss xmm1, dword ptr [0xb6a614]
006d6b7e cmovbe eax, ecx
006d6b81 movss xmm0, dword ptr [eax]
006d6b85 comiss xmm0, xmm1
006d6b88 ja 0x6d6b90
006d6b8a movss xmm1, xmm0
006d6b8e jmp 0x6d6b94
006d6b90 movss xmm1, xmm1
006d6b94 push edi
006d6b95 lea ecx, [ebp - 0x3c]
006d6b98 call 0x4229a0
006d6b9d push 1
006d6b9f sub esp, 8
006d6ba2 mulss xmm1, dword ptr [0xb6a9c0]
006d6baa movss xmm0, dword ptr [0xb6a9c8]
006d6bb2 mulss xmm2, dword ptr [0xb6a9b0]
006d6bba mulss xmm3, dword ptr [0xb6a9b0]
006d6bc2 subss xmm0, xmm1
006d6bc6 movss dword ptr [ebp - 0x78], xmm2
006d6bcb movss dword ptr [ebp - 0x74], xmm3
006d6bd0 movss dword ptr [ebp - 0x58], xmm0
006d6bd5 fld dword ptr [ebp - 0x58]
006d6bd8 fstp qword ptr [esp]
006d6bdb call 0x9ec3b2
006d6be0 fstp dword ptr [ebp - 0x58]
006d6be3 fld dword ptr [ebp - 0x58]
006d6be6 add esp, 8
006d6be9 call 0x9ec2c0
006d6bee push eax
006d6bef lea eax, [ebp - 0x78]
006d6bf2 mov ecx, esi
006d6bf4 push eax
006d6bf5 lea eax, [ebp - 0x3c]
006d6bf8 push eax
006d6bf9 call 0x68ee80
006d6bfe mov ecx, dword ptr [ebp - 0x68]
006d6c01 inc ecx
006d6c02 mov dword ptr [ebp - 0x68], ecx
006d6c05 cmp ecx, dword ptr [ebp - 0x7c]
006d6c08 jb 0x6d6753
006d6c0e test edi, edi
006d6c10 je 0x6d6c26
006d6c12 cmp dword ptr [edi + 0x28], 1
006d6c16 jne 0x6d6c26
006d6c18 cmp byte ptr [ebp + 0x14], 0
006d6c1c je 0x6d6c26
006d6c1e push ecx
006d6c1f mov ecx, edi
006d6c21 call 0x76aff0
006d6c26 cmp byte ptr [ebp - 0x88], 0
006d6c2d jne 0x6d6c3d
006d6c2f push dword ptr [ebp - 0x84]
006d6c35 call 0x9eace5
006d6c3a add esp, 4
006d6c3d mov ecx, dword ptr [ebp - 0xc]
006d6c40 mov dword ptr fs:[0], ecx
006d6c47 pop ecx
006d6c48 pop edi
006d6c49 pop esi
006d6c4a pop ebx
006d6c4b mov ecx, dword ptr [ebp - 0x14]
006d6c4e xor ecx, ebp
006d6c50 call 0x9eacd7
006d6c55 mov esp, ebp
006d6c57 pop ebp
006d6c58 ret 0x14
006d6c5b int3 
006d6c5c int3 
006d6c5d int3 
006d6c5e int3 
006d6c5f int3 
006d6c60 inc dword ptr [ecx + 0x1c3188]
006d6c66 cmp dword ptr [ecx + 0x1c3188], 3
006d6c6d jl 0x6d6c7f
006d6c6f mov ecx, dword ptr [0xbfd680]
006d6c75 push 0x4f
006d6c77 lea ecx, [ecx + 0x14]
006d6c7a call 0x884c80
006d6c7f ret 
006d6c80 push ebp
006d6c81 mov ebp, esp
006d6c83 mov eax, dword ptr [ebp + 8]
006d6c86 add dword ptr [ecx + 0x1c318c], eax
006d6c8c pop ebp
006d6c8d ret 4
006d6c90 push ebp
006d6c91 mov ebp, esp
006d6c93 mov eax, dword ptr [ebp + 8]
006d6c96 add dword ptr [ecx + 0x1c3190], eax
006d6c9c pop ebp
006d6c9d ret 4
006d6ca0 push ebp
006d6ca1 mov ebp, esp
006d6ca3 sub esp, 0x10
006d6ca6 mov eax, ecx
006d6ca8 push esi
006d6ca9 xor esi, esi
006d6cab mov dword ptr [ebp - 0x10], eax
006d6cae mov dword ptr [ebp - 0xc], esi
006d6cb1 cmp dword ptr [eax + 0x1815c], esi
006d6cb7 jle 0x6d6d70
006d6cbd push ebx
006d6cbe push edi
006d6cbf lea ebx, [eax + 0x88]
006d6cc5 mov edi, dword ptr [ebx]
006d6cc7 xor ecx, ecx
006d6cc9 mov dword ptr [ebp - 8], ecx
006d6ccc mov eax, 0x4ec4ec4f
006d6cd1 mov ecx, dword ptr [ebx + 4]
006d6cd4 sub ecx, edi
006d6cd6 imul ecx
006d6cd8 sar edx, 5
006d6cdb mov eax, edx
006d6cdd shr eax, 0x1f
006d6ce0 add eax, edx
006d6ce2 je 0x6d6d55
006d6ce4 xor ecx, ecx
006d6ce6 mov dword ptr [ebp - 4], ecx
006d6ce9 nop dword ptr [eax]
006d6cf0 cmp dword ptr [ecx + edi], 5
006d6cf4 mov esi, edi
006d6cf6 jne 0x6d6d29
006d6cf8 cmp dword ptr [ecx + edi + 4], 0x64
006d6cfd jne 0x6d6d29
006d6cff mov edx, dword ptr [ecx + edi + 8]
006d6d03 test edx, edx
006d6d05 je 0x6d6d29
006d6d07 mov ecx, 0x64
006d6d0c call 0x6c32d0
006d6d11 mov ecx, dword ptr [ebp - 4]
006d6d14 test al, al
006d6d16 je 0x6d6d29
006d6d18 mov dword ptr [ecx + edi + 8], 0
006d6d20 mov eax, dword ptr [ebx]
006d6d22 mov byte ptr [ecx + eax + 0x22], 0
006d6d27 mov esi, dword ptr [ebx]
006d6d29 inc dword ptr [ebp - 8]
006d6d2c add ecx, 0x68
006d6d2f mov dword ptr [ebp - 4], ecx
006d6d32 mov eax, 0x4ec4ec4f
006d6d37 mov ecx, dword ptr [ebx + 4]
006d6d3a mov edi, esi
006d6d3c sub ecx, esi
006d6d3e imul ecx
006d6d40 mov ecx, dword ptr [ebp - 4]
006d6d43 sar edx, 5
006d6d46 mov eax, edx
006d6d48 shr eax, 0x1f
006d6d4b add eax, edx
006d6d4d cmp dword ptr [ebp - 8], eax
006d6d50 jb 0x6d6cf0
006d6d52 mov esi, dword ptr [ebp - 0xc]
006d6d55 mov eax, dword ptr [ebp - 0x10]
006d6d58 inc esi
006d6d59 add ebx, 0xb8
006d6d5f mov dword ptr [ebp - 0xc], esi
006d6d62 cmp esi, dword ptr [eax + 0x1815c]
006d6d68 jl 0x6d6cc5
006d6d6e pop edi
006d6d6f pop ebx
006d6d70 pop esi
006d6d71 mov esp, ebp
006d6d73 pop ebp
006d6d74 ret 
006d6d75 int3 
006d6d76 int3 
006d6d77 int3 
006d6d78 int3 
006d6d79 int3 
006d6d7a int3 
006d6d7b int3 
006d6d7c int3 
006d6d7d int3 
006d6d7e int3 
006d6d7f int3 
006d6d80 push ebp
006d6d81 mov ebp, esp
006d6d83 sub esp, 0x48
006d6d86 mov eax, ecx
006d6d88 push ebx
006d6d89 xor ebx, ebx
006d6d8b mov dword ptr [ebp - 0x28], eax
006d6d8e push esi
006d6d8f push edi
006d6d90 mov dword ptr [ebp - 0x20], ebx
006d6d93 cmp dword ptr [eax + 0x1815c], ebx
006d6d99 jle 0x6d7085
006d6d9f add eax, 0x88
006d6da4 mov dword ptr [ebp - 0xc], eax
006d6da7 mov esi, dword ptr [eax]
006d6da9 xor ecx, ecx
006d6dab mov dword ptr [ebp - 0x18], ecx
006d6dae mov ecx, dword ptr [eax + 4]
006d6db1 mov eax, 0x4ec4ec4f
006d6db6 sub ecx, esi
006d6db8 imul ecx
006d6dba sar edx, 5
006d6dbd mov eax, edx
006d6dbf shr eax, 0x1f
006d6dc2 add eax, edx
006d6dc4 je 0x6d7067
006d6dca xor ebx, ebx
006d6dcc mov edi, esi
006d6dce mov dword ptr [ebp - 0x14], ebx
006d6dd1 cmp dword ptr [ebx + edi], 5
006d6dd5 jne 0x6d7035
006d6ddb mov eax, dword ptr [ebx + edi + 4]
006d6ddf cmp eax, 0x64
006d6de2 je 0x6d7035
006d6de8 cmp eax, 0x17c
006d6ded je 0x6d7035
006d6df3 cmp eax, 0x172
006d6df8 je 0x6d7035
006d6dfe cmp eax, 0x154
006d6e03 je 0x6d7035
006d6e09 cmp eax, 0x29
006d6e0c je 0x6d7035
006d6e12 cmp eax, 0x186
006d6e17 je 0x6d7035
006d6e1d mov ecx, dword ptr [0xbfd65c]
006d6e23 lea eax, [ebp - 0x1c]
006d6e26 push eax
006d6e27 lea eax, [ebp - 0x34]
006d6e2a mov dword ptr [ebp - 0x1c], 0x4f
006d6e31 push eax
006d6e32 add ecx, 0x1bb58
006d6e38 call 0x4206b0
006d6e3d cmp dword ptr [esi + ebx + 0x14], 0
006d6e42 je 0x6d6e56
006d6e44 mov eax, dword ptr [ebp - 0xc]
006d6e47 mov dword ptr [esi + ebx + 4], 0x96
006d6e4f mov eax, dword ptr [eax]
006d6e51 jmp 0x6d702d
006d6e56 mov eax, dword ptr [ebp + 8]
006d6e59 movq xmm0, qword ptr [0xa08c44]
006d6e61 mov dword ptr [ebp - 0x1c], eax
006d6e64 mov eax, dword ptr [0xa08c4c]
006d6e69 movq qword ptr [ebp - 0x40], xmm0
006d6e6e mov dword ptr [ebp - 0x24], eax
006d6e71 call 0x6c3d90
006d6e76 xor edx, edx
006d6e78 mov ecx, 6
006d6e7d div ecx
006d6e7f inc edx
006d6e80 lea ebx, [edx + edx*4]
006d6e83 add ebx, ebx
006d6e85 cmp ebx, 0x3c
006d6e88 jne 0x6d6e9b
006d6e8a call 0x6c3d90
006d6e8f lea esi, [ebx - 0x28]
006d6e92 test al, 1
006d6e94 jne 0x6d6ebf
006d6e96 lea ebx, [esi - 0xa]
006d6e99 jmp 0x6d6ebf
006d6e9b cmp ebx, 0x32
006d6e9e jne 0x6d6eba
006d6ea0 call 0x6c3d90
006d6ea5 xor edx, edx
006d6ea7 mov ecx, 3
006d6eac div ecx
006d6eae mov esi, 0x14
006d6eb3 test edx, edx
006d6eb5 cmove ebx, esi
006d6eb8 jmp 0x6d6ebf
006d6eba mov esi, 0x14
006d6ebf call 0x6c3d90
006d6ec4 xor edx, edx
006d6ec6 mov ecx, 0xa
006d6ecb div ecx
006d6ecd test edx, edx
006d6ecf jne 0x6d6ee1
006d6ed1 call 0x6c3d90
006d6ed6 and eax, 1
006d6ed9 add eax, 3
006d6edc lea ebx, [eax + eax*4]
006d6edf add ebx, ebx
006d6ee1 call 0x6c3d90
006d6ee6 xor edx, edx
006d6ee8 mov edi, 0xf
006d6eed div edi
006d6eef mov eax, 0x12c
006d6ef4 test edx, edx
006d6ef6 cmove ebx, eax
006d6ef9 call 0x6c3d90
006d6efe xor edx, edx
