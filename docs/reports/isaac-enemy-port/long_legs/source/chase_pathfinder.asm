007a3650 push ebp
007a3651 mov ebp, esp
007a3653 push -1
007a3655 push 0x9f96e8
007a365a mov eax, dword ptr fs:[0]
007a3660 push eax
007a3661 sub esp, 0x80
007a3667 mov eax, dword ptr [0xbaa3b4]
007a366c xor eax, ebp
007a366e mov dword ptr [ebp - 0x10], eax
007a3671 push ebx
007a3672 push esi
007a3673 push edi
007a3674 push eax
007a3675 lea eax, [ebp - 0xc]
007a3678 mov dword ptr fs:[0], eax
007a367e mov ebx, ecx
007a3680 mov dword ptr [ebp - 0x58], ebx
007a3683 mov esi, dword ptr [ebx]
007a3685 mov eax, dword ptr [ebp + 8]
007a3688 mov dword ptr [ebp - 0x3c], eax
007a368b mov eax, dword ptr [esi + 0x28]
007a368e sub eax, 0xa
007a3691 cmp eax, 0x3dd
007a3696 ja 0x7a3754
007a369c cmp dword ptr [esi + 0xe6c], -1
007a36a3 je 0x7a3754
007a36a9 lea eax, [ebp - 0x4c]
007a36ac xorps xmm2, xmm2
007a36af push eax
007a36b0 mov ecx, esi
007a36b2 call 0x6af0c0
007a36b7 movss xmm2, dword ptr [0xb6a614]
007a36bf lea eax, [ebp - 0x4c]
007a36c2 push ecx
007a36c3 push eax
007a36c4 mov ecx, ebx
007a36c6 call 0x7a7610
007a36cb movss xmm1, dword ptr [0xb6aa3c]
007a36d3 movss xmm2, dword ptr [esi + 0x294]
007a36db movss xmm3, dword ptr [esi + 0x298]
007a36e3 subss xmm2, xmm1
007a36e7 subss xmm3, dword ptr [0xb6ab20]
007a36ef mov eax, dword ptr [0xbfd65c]
007a36f4 divss xmm2, xmm1
007a36f8 mov esi, dword ptr [eax + 0x18190]
007a36fe divss xmm3, xmm1
007a3702 addss xmm2, dword ptr [0xb6a480]
007a370a addss xmm3, dword ptr [0xb6a480]
007a3712 cvttss2si edx, xmm2
007a3716 cvttss2si ecx, xmm3
007a371a test edx, edx
007a371c js 0x7a3742
007a371e mov eax, dword ptr [esi + 0xc]
007a3721 cmp edx, eax
007a3723 jge 0x7a3742
007a3725 test ecx, ecx
007a3727 js 0x7a3742
007a3729 cmp ecx, dword ptr [esi + 0x10]
007a372c jge 0x7a3742
007a372e imul eax, ecx
007a3731 mov byte ptr [ebx + 0x72c], 1
007a3738 add eax, edx
007a373a mov dword ptr [ebx + 0x20], eax
007a373d jmp 0x7a47f5
007a3742 or eax, 0xffffffff
007a3745 mov byte ptr [ebx + 0x72c], 1
007a374c mov dword ptr [ebx + 0x20], eax
007a374f jmp 0x7a47f5
007a3754 mov eax, dword ptr [esi + 0x164]
007a375a mov ecx, dword ptr [esi + 0x160]
007a3760 mov dword ptr [ebp - 0x48], eax
007a3763 mov eax, ecx
007a3765 and eax, 0x200
007a376a or eax, 0
007a376d je 0x7a3861
007a3773 and ecx, 0x100
007a3779 or ecx, 0
007a377c jne 0x7a3861
007a3782 push 1
007a3784 mov ecx, ebx
007a3786 call 0x7a6180
007a378b mov esi, dword ptr [ebx]
007a378d movss xmm1, dword ptr [esi + 0x2bc]
007a3795 movss xmm2, dword ptr [esi + 0x2b8]
007a379d movaps xmm0, xmm1
007a37a0 mulss xmm0, xmm1
007a37a4 movss dword ptr [ebp - 0x54], xmm1
007a37a9 movaps xmm1, xmm2
007a37ac mulss xmm1, xmm2
007a37b0 movss dword ptr [ebp - 0x68], xmm2
007a37b5 addss xmm0, xmm1
007a37b9 call 0x4228c0
007a37be movss xmm2, dword ptr [ebp - 0x68]
007a37c3 xorps xmm4, xmm4
007a37c6 comiss xmm0, xmm4
007a37c9 jbe 0x7a37e5
007a37cb movss xmm1, dword ptr [0xb6a614]
007a37d3 divss xmm1, xmm0
007a37d7 movaps xmm0, xmm1
007a37da mulss xmm1, dword ptr [ebp - 0x54]
007a37df mulss xmm2, xmm0
007a37e3 jmp 0x7a37ea
007a37e5 movss xmm1, dword ptr [ebp - 0x54]
007a37ea movss xmm0, dword ptr [0xc02fec]
007a37f2 mulss xmm2, dword ptr [ebp + 0xc]
007a37f7 mulss xmm1, dword ptr [ebp + 0xc]
007a37fc movss dword ptr [esi + 0x2b8], xmm0
007a3804 movss xmm0, dword ptr [0xc02ff0]
007a380c movss dword ptr [esi + 0x2bc], xmm0
007a3814 mov esi, dword ptr [ebx]
007a3816 movss xmm3, dword ptr [esi + 0x2c4]
007a381e ucomiss xmm3, xmm4
007a3821 lahf 
007a3822 test ah, 0x44
007a3825 jnp 0x7a3861
007a3827 movss xmm0, dword ptr [esi + 0x2f4]
007a382f mulss xmm2, xmm0
007a3833 mulss xmm1, xmm0
007a3837 divss xmm2, xmm3
007a383b divss xmm1, xmm3
007a383f addss xmm2, dword ptr [esi + 0x2b8]
007a3847 addss xmm1, dword ptr [esi + 0x2bc]
007a384f movss dword ptr [esi + 0x2b8], xmm2
007a3857 movss dword ptr [esi + 0x2bc], xmm1
007a385f mov esi, dword ptr [ebx]
007a3861 movss xmm0, dword ptr [0xc02fec]
007a3869 movss xmm2, dword ptr [esi + 0x2cc]
007a3871 movss xmm1, dword ptr [esi + 0x2d0]
007a3879 movss dword ptr [ebp - 0x2c], xmm0
007a387e movss dword ptr [ebp - 0x4c], xmm0
007a3883 movss xmm0, dword ptr [0xc02ff0]
007a388b movss dword ptr [ebp - 0x38], xmm0
007a3890 movss dword ptr [ebp - 0x48], xmm0
007a3895 movss xmm0, dword ptr [esi + 0x2c8]
007a389d mulss xmm2, xmm0
007a38a1 mulss xmm1, xmm0
007a38a5 movss xmm0, dword ptr [0xb6aa3c]
007a38ad addss xmm2, xmm2
007a38b1 addss xmm1, xmm1
007a38b5 comiss xmm2, xmm0
007a38b8 movss dword ptr [ebp - 0x50], xmm2
007a38bd movss dword ptr [ebp - 0x74], xmm1
007a38c2 ja 0x7a38cd
007a38c4 comiss xmm1, xmm0
007a38c7 mov byte ptr [ebp - 0x22], 0
007a38cb jbe 0x7a38d1
007a38cd mov byte ptr [ebp - 0x22], 1
007a38d1 cmp dword ptr [esi + 0x28], 3
007a38d5 mov edi, dword ptr [ebp + 0x10]
007a38d8 jne 0x7a38e2
007a38da mov byte ptr [ebp - 0x21], 1
007a38de test edi, edi
007a38e0 jle 0x7a38e6
007a38e2 mov byte ptr [ebp - 0x21], 0
007a38e6 mov ecx, ebx
007a38e8 call 0x7a35d0
007a38ed test al, al
007a38ef jne 0x7a38f8
007a38f1 mov byte ptr [ebp - 0x23], al
007a38f4 test edi, edi
007a38f6 jns 0x7a38fc
007a38f8 mov byte ptr [ebp - 0x23], 1
007a38fc movss xmm1, dword ptr [0xb6aad4]
007a3904 movss xmm0, dword ptr [ebp - 0x50]
007a3909 call 0x447b40
007a390e movss xmm1, dword ptr [0xb6aad4]
007a3916 movss dword ptr [ebp - 0x50], xmm0
007a391b movss xmm0, dword ptr [ebp - 0x74]
007a3920 call 0x447b40
007a3925 movss xmm4, dword ptr [0xb6aa3c]
007a392d movaps xmm2, xmm0
007a3930 movss xmm0, dword ptr [ebp - 0x50]
007a3935 comiss xmm0, xmm4
007a3938 movss xmm1, dword ptr [0xb6a9c4]
007a3940 movss xmm3, dword ptr [ebp - 0x2c]
007a3945 jbe 0x7a3955
007a3947 addss xmm3, xmm1
007a394b movss dword ptr [ebp - 0x2c], xmm3
007a3950 movss dword ptr [ebp - 0x4c], xmm3
007a3955 comiss xmm2, xmm4
007a3958 movss xmm0, dword ptr [ebp - 0x38]
007a395d jbe 0x7a396d
007a395f addss xmm0, xmm1
007a3963 movss dword ptr [ebp - 0x38], xmm0
007a3968 movss dword ptr [ebp - 0x48], xmm0
007a396d mov eax, dword ptr [ebp - 0x3c]
007a3970 movss xmm1, dword ptr [esi + 0x294]
007a3978 movss xmm2, dword ptr [esi + 0x298]
007a3980 movaps xmm5, xmm1
007a3983 movaps xmm6, xmm2
007a3986 movss dword ptr [ebp - 0x70], xmm1
007a398b movss xmm1, dword ptr [eax]
007a398f subss xmm6, xmm0
007a3993 movaps xmm0, xmm1
007a3996 movss dword ptr [ebp - 0x5c], xmm2
007a399b subss xmm0, xmm4
007a399f movss xmm2, dword ptr [0xb6a480]
007a39a7 subss xmm5, xmm3
007a39ab mov edx, dword ptr [0xbfd65c]
007a39b1 movss xmm3, dword ptr [0xb6ab20]
007a39b9 movss dword ptr [ebp - 0x74], xmm6
007a39be divss xmm0, xmm4
007a39c2 mov esi, dword ptr [edx + 0x18190]
007a39c8 mov dword ptr [ebp - 0x28], esi
007a39cb movss dword ptr [ebp - 0x78], xmm5
007a39d0 addss xmm0, xmm2
007a39d4 cvttss2si ecx, xmm0
007a39d8 movss xmm0, dword ptr [eax + 4]
007a39dd subss xmm0, xmm3
007a39e1 divss xmm0, xmm4
007a39e5 addss xmm0, xmm2
007a39e9 cvttss2si eax, xmm0
007a39ed test ecx, ecx
007a39ef js 0x7a3a19
007a39f1 mov edi, dword ptr [esi + 0xc]
007a39f4 cmp ecx, edi
007a39f6 jge 0x7a3a19
007a39f8 test eax, eax
007a39fa js 0x7a3a19
007a39fc cmp eax, dword ptr [esi + 0x10]
007a39ff jge 0x7a3a19
007a3a01 imul edi, eax
007a3a04 add edi, ecx
007a3a06 mov dword ptr [ebp - 0x44], edi
007a3a09 mov eax, edi
007a3a0b cmp edi, 0x1bf
007a3a11 ja 0x7a3a1f
007a3a13 mov ecx, dword ptr [esi + edi*4 + 0x24]
007a3a17 jmp 0x7a3a21
007a3a19 or eax, 0xffffffff
007a3a1c mov dword ptr [ebp - 0x44], eax
007a3a1f xor ecx, ecx
007a3a21 cmp byte ptr [ebx + 0x738], 0
007a3a28 jne 0x7a3a44
007a3a2a test eax, eax
007a3a2c js 0x7a3a7c
007a3a2e cmp eax, 0x1c0
007a3a33 jge 0x7a3a60
007a3a35 cmp dword ptr [esi + eax*4 + 0x76c], 0x3e8
007a3a40 jge 0x7a3a7c
007a3a42 jmp 0x7a3a60
007a3a44 test ecx, ecx
007a3a46 je 0x7a3a7c
007a3a48 call 0x6dc600
007a3a4d test al, al
007a3a4f jne 0x7a3a76
007a3a51 call 0x6dc650
007a3a56 mov edx, dword ptr [0xbfd65c]
007a3a5c test al, al
007a3a5e jne 0x7a3a7c
007a3a60 mov eax, dword ptr [ebp - 0x3c]
007a3a63 movss dword ptr [ebx + 0x730], xmm1
007a3a6b mov eax, dword ptr [eax + 4]
007a3a6e mov dword ptr [ebx + 0x734], eax
007a3a74 jmp 0x7a3af3
007a3a76 mov edx, dword ptr [0xbfd65c]
007a3a7c movss xmm1, dword ptr [ebx + 0x730]
007a3a84 ucomiss xmm1, dword ptr [0xc02fec]
007a3a8b lahf 
007a3a8c test ah, 0x44
007a3a8f jp 0x7a3aa6
007a3a91 movss xmm0, dword ptr [ebx + 0x734]
007a3a99 ucomiss xmm0, dword ptr [0xc02ff0]
007a3aa0 lahf 
007a3aa1 test ah, 0x44
007a3aa4 jnp 0x7a3af3
007a3aa6 movss xmm0, dword ptr [ebx + 0x734]
007a3aae subss xmm1, xmm4
007a3ab2 subss xmm0, xmm3
007a3ab6 divss xmm1, xmm4
007a3aba divss xmm0, xmm4
007a3abe addss xmm1, xmm2
007a3ac2 addss xmm0, xmm2
007a3ac6 cvttss2si ecx, xmm1
007a3aca cvttss2si eax, xmm0
007a3ace test ecx, ecx
007a3ad0 js 0x7a3aec
007a3ad2 mov edi, dword ptr [esi + 0xc]
007a3ad5 cmp ecx, edi
007a3ad7 jge 0x7a3aec
007a3ad9 test eax, eax
007a3adb js 0x7a3aec
007a3add cmp eax, dword ptr [esi + 0x10]
007a3ae0 jge 0x7a3aec
007a3ae2 imul edi, eax
007a3ae5 add edi, ecx
007a3ae7 mov dword ptr [ebp - 0x44], edi
007a3aea jmp 0x7a3af3
007a3aec mov dword ptr [ebp - 0x44], 0xffffffff
007a3af3 movaps xmm0, xmm5
007a3af6 mov eax, dword ptr [edx + 0x18190]
007a3afc subss xmm0, xmm4
007a3b00 divss xmm0, xmm4
007a3b04 addss xmm0, xmm2
007a3b08 cvttss2si edi, xmm0
007a3b0c movaps xmm0, xmm6
007a3b0f subss xmm0, xmm3
007a3b13 divss xmm0, xmm4
007a3b17 addss xmm0, xmm2
007a3b1b cvttss2si edx, xmm0
007a3b1f test edi, edi
007a3b21 js 0x7a3b3c
007a3b23 mov ecx, dword ptr [eax + 0xc]
007a3b26 cmp edi, ecx
007a3b28 jge 0x7a3b3c
007a3b2a test edx, edx
007a3b2c js 0x7a3b3c
007a3b2e cmp edx, dword ptr [eax + 0x10]
007a3b31 jge 0x7a3b3c
007a3b33 mov esi, ecx
007a3b35 imul esi, edx
007a3b38 add esi, edi
007a3b3a jmp 0x7a3b42
007a3b3c mov ecx, dword ptr [eax + 0xc]
007a3b3f or esi, 0xffffffff
007a3b42 mov eax, esi
007a3b44 mov edi, dword ptr [ebx + 0x20]
007a3b47 cdq 
007a3b48 idiv ecx
007a3b4a movd xmm1, edx
007a3b4e movd xmm0, eax
007a3b52 cvtdq2ps xmm1, xmm1
007a3b55 cvtdq2ps xmm0, xmm0
007a3b58 mulss xmm1, xmm4
007a3b5c mulss xmm0, xmm4
007a3b60 addss xmm1, xmm4
007a3b64 addss xmm0, xmm3
007a3b68 movss dword ptr [ebp - 0x6c], xmm1
007a3b6d movss dword ptr [ebp - 0x68], xmm0
007a3b72 cmp esi, edi
007a3b74 je 0x7a3bc8
007a3b76 mov ecx, dword ptr [ebx]
007a3b78 cvttss2si eax, dword ptr [ecx + 0x2fc]
007a3b80 cvttss2si ecx, dword ptr [ecx + 0x2f8]
007a3b88 sub ecx, eax
007a3b8a lea eax, [ecx + ecx*4]
007a3b8d add eax, eax
007a3b8f add dword ptr [ebx + 0x24], eax
007a3b92 jns 0x7a3bc8
007a3b94 movss xmm0, dword ptr [ebp + 0xc]
007a3b99 lea eax, [ebp + 0xc]
007a3b9c comiss xmm0, dword ptr [0xb6a350]
007a3ba3 lea ecx, [ebp - 0x50]
007a3ba6 mov dword ptr [ebp - 0x50], 0x3e4ccccd
007a3bad mov edi, esi
007a3baf mov dword ptr [ebx + 0x20], esi
007a3bb2 movss xmm0, dword ptr [0xb6a9c8]
007a3bba cmovbe eax, ecx
007a3bbd divss xmm0, dword ptr [eax]
007a3bc1 cvttss2si eax, xmm0
007a3bc5 mov dword ptr [ebx + 0x24], eax
007a3bc8 cmp byte ptr [ebp - 0x21], 0
007a3bcc movss xmm0, dword ptr [0xb6a614]
007a3bd4 movss dword ptr [ebp - 0x50], xmm0
007a3bd9 jne 0x7a3d00
007a3bdf mov esi, dword ptr [ebx]
007a3be1 mov ecx, esi
007a3be3 push 1
007a3be5 push 3
007a3be7 call 0x684790
007a3bec test al, al
007a3bee je 0x7a3cc2
007a3bf4 movss xmm1, dword ptr [esi + 0x2bc]
007a3bfc movss xmm2, dword ptr [esi + 0x2b8]
007a3c04 movaps xmm0, xmm1
007a3c07 mulss xmm0, xmm1
007a3c0b movss dword ptr [ebp - 0x60], xmm1
007a3c10 movaps xmm1, xmm2
007a3c13 mulss xmm1, xmm2
007a3c17 movss dword ptr [ebp - 0x30], xmm2
007a3c1c addss xmm0, xmm1
007a3c20 call 0x4228c0
007a3c25 xorps xmm1, xmm1
007a3c28 comiss xmm0, xmm1
007a3c2b jbe 0x7a3c4e
007a3c2d movss xmm1, dword ptr [0xb6a614]
007a3c35 divss xmm1, xmm0
007a3c39 movaps xmm0, xmm1
007a3c3c mulss xmm1, dword ptr [esi + 0x2bc]
007a3c44 mulss xmm0, dword ptr [esi + 0x2b8]
007a3c4c jmp 0x7a3c58
007a3c4e movss xmm0, dword ptr [ebp - 0x30]
007a3c53 movss xmm1, dword ptr [ebp - 0x60]
007a3c58 mulss xmm0, dword ptr [0xb6aa3c]
007a3c60 lea eax, [ebp - 0x34]
007a3c63 mov esi, dword ptr [0xbfd65c]
007a3c69 mulss xmm1, dword ptr [0xb6aa3c]
007a3c71 push eax
007a3c72 addss xmm0, dword ptr [ebp - 0x78]
007a3c77 mov esi, dword ptr [esi + 0x18190]
007a3c7d mov ecx, esi
007a3c7f addss xmm1, dword ptr [ebp - 0x74]
007a3c84 movss dword ptr [ebp - 0x34], xmm0
007a3c89 movss dword ptr [ebp - 0x30], xmm1
007a3c8e call 0x7ce950
007a3c93 cmp eax, 0x1bf
007a3c98 ja 0x7a3ca3
007a3c9a mov eax, dword ptr [esi + eax*4 + 0x76c]
007a3ca1 jmp 0x7a3ca5
007a3ca3 xor eax, eax
007a3ca5 push eax
007a3ca6 mov ecx, ebx
007a3ca8 call 0x7a75b0
007a3cad dec eax
007a3cae cmp eax, 0x3b4
007a3cb3 ja 0x7a3cc2
007a3cb5 movss xmm0, dword ptr [0xb6a50c]
007a3cbd movss dword ptr [ebp - 0x50], xmm0
007a3cc2 mov esi, dword ptr [ebp + 0x10]
007a3cc5 test esi, esi
007a3cc7 js 0x7a3d00
007a3cc9 cmp edi, 0x1bf
007a3ccf ja 0x7a3cdd
007a3cd1 mov eax, dword ptr [ebp - 0x28]
007a3cd4 mov ecx, dword ptr [eax + edi*4 + 0x76c]
007a3cdb jmp 0x7a3cdf
007a3cdd xor ecx, ecx
007a3cdf xor eax, eax
007a3ce1 cmp ecx, 0x3b6
007a3ce7 mov ecx, ebx
007a3ce9 setl al
007a3cec push eax
007a3ced call 0x7a75b0
007a3cf2 test eax, eax
007a3cf4 je 0x7a3d00
007a3cf6 mov ecx, dword ptr [ebp - 0x28]
007a3cf9 push esi
007a3cfa push edi
007a3cfb call 0x4baeb0
007a3d00 mov eax, dword ptr [ebx]
007a3d02 mov ecx, eax
007a3d04 push dword ptr [eax + 0x20]
007a3d07 push 0xa
007a3d09 call 0x684790
007a3d0e test al, al
007a3d10 je 0x7a3dfc
007a3d16 mov eax, dword ptr [0xbfd65c]
007a3d1b movss xmm2, dword ptr [0xb6aa3c]
007a3d23 movss xmm3, dword ptr [0xb6ab20]
007a3d2b mov esi, dword ptr [eax + 0x18190]
007a3d31 mov eax, dword ptr [ebp - 0x3c]
007a3d34 movss xmm0, dword ptr [eax]
007a3d38 subss xmm0, xmm2
007a3d3c divss xmm0, xmm2
007a3d40 addss xmm0, dword ptr [0xb6a480]
007a3d48 cvttss2si edi, xmm0
007a3d4c movss xmm0, dword ptr [eax + 4]
007a3d51 subss xmm0, xmm3
007a3d55 divss xmm0, xmm2
007a3d59 addss xmm0, dword ptr [0xb6a480]
007a3d61 cvttss2si edx, xmm0
007a3d65 test edi, edi
007a3d67 js 0x7a3d82
007a3d69 mov ecx, dword ptr [esi + 0xc]
007a3d6c cmp edi, ecx
007a3d6e jge 0x7a3d82
007a3d70 test edx, edx
007a3d72 js 0x7a3d82
007a3d74 cmp edx, dword ptr [esi + 0x10]
007a3d77 jge 0x7a3d82
007a3d79 mov eax, ecx
007a3d7b imul eax, edx
007a3d7e add eax, edi
007a3d80 jmp 0x7a3d88
007a3d82 mov ecx, dword ptr [esi + 0xc]
007a3d85 or eax, 0xffffffff
007a3d88 cdq 
007a3d89 idiv ecx
007a3d8b xor ecx, ecx
007a3d8d movd xmm1, edx
007a3d91 movd xmm0, eax
007a3d95 cvtdq2ps xmm1, xmm1
007a3d98 cvtdq2ps xmm0, xmm0
007a3d9b mulss xmm1, xmm2
007a3d9f mulss xmm0, xmm2
007a3da3 addss xmm1, xmm2
007a3da7 addss xmm0, xmm3
007a3dab movss dword ptr [ebp - 0x34], xmm1
007a3db0 movss dword ptr [ebp - 0x30], xmm0
007a3db5 cmp byte ptr [ebp - 0x23], cl
007a3db8 jne 0x7a3dbf
007a3dba cmp byte ptr [ebp - 0x21], cl
007a3dbd je 0x7a3dc4
007a3dbf mov ecx, 0x384
007a3dc4 mov eax, dword ptr [ebx]
007a3dc6 cmp dword ptr [eax + 0x17c], 3
007a3dcd jne 0x7a3dd8
007a3dcf mov byte ptr [ebx + 0x72c], 1
007a3dd6 jmp 0x7a3dfc
007a3dd8 movzx eax, byte ptr [ebx + 0x738]
007a3ddf push 0
007a3de1 push 0
007a3de3 push eax
007a3de4 push ecx
007a3de5 push 0
007a3de7 lea eax, [ebp - 0x34]
007a3dea mov ecx, esi
007a3dec push eax
007a3ded lea eax, [ebp - 0x6c]
007a3df0 push eax
007a3df1 call 0x7af4b0
007a3df6 mov byte ptr [ebx + 0x72c], al
007a3dfc mov al, byte ptr [ebp + 0x14]
007a3dff movss xmm3, dword ptr [0xc02fec]
007a3e07 movss xmm4, dword ptr [0xc02ff0]
007a3e0f movss dword ptr [ebp - 0x54], xmm3
007a3e14 movss dword ptr [ebp - 0x68], xmm4
007a3e19 test al, al
007a3e1b je 0x7a3e27
007a3e1d movss xmm2, dword ptr [0xb6acb8]
007a3e25 jmp 0x7a3e2f
007a3e27 movss xmm2, dword ptr [0xb6aab4]
007a3e2f cmp byte ptr [ebp - 0x22], 0
007a3e33 movss dword ptr [ebp - 0x40], xmm2
007a3e38 je 0x7a3e7a
007a3e3a test al, al
007a3e3c jne 0x7a3e7a
007a3e3e mov eax, dword ptr [ebx]
007a3e40 lea ecx, [ebp - 0x60]
007a3e43 movss xmm1, dword ptr [eax + 0x2c8]
007a3e4b movaps xmm0, xmm1
007a3e4e mulss xmm1, dword ptr [eax + 0x2cc]
007a3e56 mulss xmm0, dword ptr [eax + 0x2d0]
007a3e5e lea eax, [ebp - 0x30]
007a3e61 movss dword ptr [ebp - 0x60], xmm1
007a3e66 comiss xmm0, xmm1
007a3e69 movss dword ptr [ebp - 0x30], xmm0
007a3e6e cmovbe eax, ecx
007a3e71 addss xmm2, dword ptr [eax]
007a3e75 movss dword ptr [ebp - 0x40], xmm2
007a3e7a cmp byte ptr [ebx + 0x72c], 0
007a3e81 mov esi, dword ptr [ebp - 0x3c]
007a3e84 je 0x7a3eb4
007a3e86 movss xmm1, dword ptr [esi]
007a3e8a movss xmm0, dword ptr [esi + 4]
007a3e8f subss xmm0, dword ptr [ebp - 0x5c]
007a3e94 subss xmm1, dword ptr [ebp - 0x70]
007a3e99 mulss xmm0, xmm0
007a3e9d mulss xmm1, xmm1
007a3ea1 addss xmm0, xmm1
007a3ea5 call 0x4228c0
007a3eaa movss xmm1, dword ptr [ebp - 0x40]
007a3eaf comiss xmm1, xmm0
007a3eb2 ja 0x7a3ebc
007a3eb4 mov eax, dword ptr [ebx + 0x20]
007a3eb7 cmp eax, dword ptr [ebp - 0x44]
007a3eba jne 0x7a3f08
007a3ebc mov edx, dword ptr [ebx]
007a3ebe movss xmm2, dword ptr [esi]
007a3ec2 movss xmm1, dword ptr [esi + 4]
007a3ec7 subss xmm2, dword ptr [ebp - 0x2c]
007a3ecc cvttss2si eax, dword ptr [edx + 0x2fc]
007a3ed4 cvttss2si ecx, dword ptr [edx + 0x2f8]
007a3edc subss xmm1, dword ptr [ebp - 0x38]
007a3ee1 sub ecx, eax
007a3ee3 lea eax, [ecx + ecx*4]
007a3ee6 add eax, eax
007a3ee8 add dword ptr [ebx + 0x28], eax
007a3eeb cvttss2si eax, dword ptr [edx + 0x2fc]
007a3ef3 cvttss2si ecx, dword ptr [edx + 0x2f8]
007a3efb sub ecx, eax
007a3efd imul eax, ecx, 0x32
007a3f00 add dword ptr [ebx + 0x24], eax
007a3f03 jmp 0x7a46c1
007a3f08 mov edi, dword ptr [ebp - 0x28]
007a3f0b cmp eax, 0x1bf
007a3f10 ja 0x7a3f23
007a3f12 cmp dword ptr [edi + eax*4 + 0x76c], 0x3e8
007a3f1d je 0x7a4559
007a3f23 cmp dword ptr [ebx + 0x28], 0
007a3f27 jg 0x7a4559
007a3f2d call 0x6c3d90
007a3f32 xor edx, edx
007a3f34 mov dword ptr [ebp - 0x8c], 0
007a3f3e mov ecx, 0xa
007a3f43 mov dword ptr [ebp - 0x88], 0
007a3f4d div ecx
007a3f4f mov dword ptr [ebp - 0x84], 0
007a3f59 add edx, ecx
007a3f5b mov dword ptr [ebx + 0x28], edx
007a3f5e cmp byte ptr [ebp - 0x22], 0
007a3f62 mov dword ptr [ebp - 4], 0
007a3f69 jne 0x7a3f80
007a3f6b lea esi, [edi + 0x76c]
007a3f71 mov ecx, 0x1c0
007a3f76 lea edi, [ebx + 0x2c]
007a3f79 rep movsd dword ptr es:[edi], dword ptr [esi]
007a3f7b jmp 0x7a4383
007a3f80 mov dword ptr [ebp - 0x1c], 0
007a3f87 mov dword ptr [ebp - 0x18], 0
007a3f8e mov dword ptr [ebp - 0x14], 0
007a3f95 mov byte ptr [ebp - 4], 1
007a3f99 mov ecx, dword ptr [ebx]
007a3f9b add ecx, 0x170
007a3fa1 mov dword ptr [ebp - 0x5c], ecx
007a3fa4 mov eax, dword ptr [ecx + 4]
007a3fa7 sub eax, dword ptr [ecx]
007a3fa9 lea ecx, [ebp - 0x1c]
007a3fac sar eax, 3
007a3faf inc eax
007a3fb0 push eax
007a3fb1 call 0x7a7c30
007a3fb6 mov edx, dword ptr [ebp - 0x18]
007a3fb9 cmp edx, dword ptr [ebp - 0x14]
007a3fbc je 0x7a3fd9
007a3fbe movss xmm0, dword ptr [ebp - 0x2c]
007a3fc3 movss xmm1, dword ptr [ebp - 0x38]
007a3fc8 movss dword ptr [edx], xmm0
007a3fcc movss dword ptr [edx + 4], xmm1
007a3fd1 add edx, 8
007a3fd4 mov dword ptr [ebp - 0x18], edx
007a3fd7 jmp 0x7a3ff3
007a3fd9 lea eax, [ebp - 0x4c]
007a3fdc push eax
007a3fdd push edx
007a3fde lea ecx, [ebp - 0x1c]
007a3fe1 call 0x422130
007a3fe6 mov edx, dword ptr [ebp - 0x18]
007a3fe9 movss xmm1, dword ptr [ebp - 0x38]
007a3fee movss xmm0, dword ptr [ebp - 0x2c]
007a3ff3 mov eax, dword ptr [ebp - 0x5c]
007a3ff6 xor esi, esi
007a3ff8 mov dword ptr [ebp - 0x40], edx
007a3ffb mov ecx, dword ptr [eax]
007a3ffd mov eax, dword ptr [eax + 4]
007a4000 sub eax, ecx
007a4002 sar eax, 3
007a4005 test eax, eax
007a4007 je 0x7a406f
007a4009 mov edi, dword ptr [ebp - 0x14]
007a400c mov ebx, dword ptr [ebp - 0x5c]
007a400f nop 
007a4010 addss xmm0, dword ptr [ecx + esi*8]
007a4015 addss xmm1, dword ptr [ecx + esi*8 + 4]
007a401b movss dword ptr [ebp - 0x4c], xmm0
007a4020 movss dword ptr [ebp - 0x48], xmm1
007a4025 cmp edx, edi
007a4027 je 0x7a403a
007a4029 movss dword ptr [edx], xmm0
007a402d movss dword ptr [edx + 4], xmm1
007a4032 add edx, 8
007a4035 mov dword ptr [ebp - 0x18], edx
007a4038 jmp 0x7a404d
007a403a lea eax, [ebp - 0x4c]
007a403d push eax
007a403e push edx
007a403f lea ecx, [ebp - 0x1c]
007a4042 call 0x422130
007a4047 mov edi, dword ptr [ebp - 0x14]
007a404a mov edx, dword ptr [ebp - 0x18]
007a404d mov eax, dword ptr [ebx + 4]
007a4050 inc esi
007a4051 mov ecx, dword ptr [ebx]
007a4053 sub eax, ecx
007a4055 movss xmm1, dword ptr [ebp - 0x38]
007a405a movss xmm0, dword ptr [ebp - 0x2c]
007a405f sar eax, 3
007a4062 cmp esi, eax
007a4064 jb 0x7a4010
007a4066 mov ebx, dword ptr [ebp - 0x58]
007a4069 mov edi, dword ptr [ebp - 0x28]
007a406c mov dword ptr [ebp - 0x40], edx
007a406f push 0x700
007a4074 lea eax, [ebx + 0x2c]
007a4077 push 0
007a4079 push eax
007a407a mov dword ptr [ebp - 0x38], eax
007a407d call 0x9ec152
007a4082 mov ecx, dword ptr [edi + 0xc]
007a4085 xor edx, edx
007a4087 mov esi, dword ptr [edi + 0x10]
007a408a mov eax, ecx
007a408c imul eax, esi
007a408f add esp, 0xc
007a4092 mov dword ptr [ebp - 0x30], edx
007a4095 test eax, eax
007a4097 jle 0x7a4237
007a409d mov edi, dword ptr [ebp - 0x40]
007a40a0 sub edi, dword ptr [ebp - 0x1c]
007a40a3 movss xmm4, dword ptr [0xb6aa3c]
007a40ab movss xmm6, dword ptr [0xb6ab20]
007a40b3 sar edi, 3
007a40b6 shr edi, 1
007a40b8 mov dword ptr [ebp - 0x40], edi
007a40bb nop dword ptr [eax + eax]
007a40c0 mov eax, edx
007a40c2 cdq 
007a40c3 idiv ecx
007a40c5 movd xmm2, edx
007a40c9 xor edx, edx
007a40cb movd xmm3, eax
007a40cf mov dword ptr [ebp - 0x60], edx
007a40d2 cvtdq2ps xmm2, xmm2
007a40d5 cvtdq2ps xmm3, xmm3
007a40d8 mulss xmm2, xmm4
007a40dc mulss xmm3, xmm4
007a40e0 addss xmm2, xmm4
007a40e4 addss xmm3, xmm6
007a40e8 test edi, edi
007a40ea je 0x7a421f
007a40f0 movss xmm5, dword ptr [0xb6a480]
007a40f8 nop dword ptr [eax + eax]
007a4100 mov eax, dword ptr [ebp - 0x1c]
007a4103 movaps xmm0, xmm2
007a4106 movaps xmm1, xmm3
007a4109 addss xmm0, dword ptr [eax + edx*8]
007a410e addss xmm1, dword ptr [eax + edx*8 + 4]
007a4114 mov eax, dword ptr [ebp - 0x28]
007a4117 subss xmm0, xmm4
007a411b subss xmm1, xmm6
007a411f divss xmm0, xmm4
007a4123 divss xmm1, xmm4
007a4127 addss xmm0, xmm5
007a412b addss xmm1, xmm5
007a412f cvttss2si edi, xmm0
007a4133 cvttss2si edx, xmm1
007a4137 test edi, edi
007a4139 js 0x7a4165
007a413b mov esi, dword ptr [eax + 0xc]
007a413e cmp edi, esi
007a4140 jge 0x7a4165
007a4142 test edx, edx
007a4144 js 0x7a4165
007a4146 mov ecx, dword ptr [eax + 0x10]
007a4149 mov dword ptr [ebp - 0x70], ecx
007a414c cmp edx, ecx
007a414e jge 0x7a4165
007a4150 mov eax, esi
007a4152 imul eax, edx
007a4155 add eax, edi
007a4157 js 0x7a416b
007a4159 mov ecx, dword ptr [ebp - 0x28]
007a415c mov edi, dword ptr [ecx + eax*4 + 0x76c]
007a4163 jmp 0x7a4170
007a4165 mov esi, dword ptr [eax + 0xc]
007a4168 mov ecx, dword ptr [eax + 0x10]
007a416b xor edi, edi
007a416d mov dword ptr [ebp - 0x70], ecx
007a4170 cmp byte ptr [ebx + 0x738], 0
007a4177 mov eax, esi
007a4179 mov dword ptr [ebp - 0x2c], edi
007a417c mov ecx, esi
007a417e je 0x7a41dd
007a4180 cvttss2si ecx, xmm0
007a4184 test ecx, ecx
007a4186 js 0x7a4202
007a4188 cmp ecx, esi
007a418a jge 0x7a4202
007a418c test edx, edx
007a418e js 0x7a4202
007a4190 cmp edx, dword ptr [ebp - 0x70]
007a4193 jge 0x7a4202
007a4195 imul edx, esi
007a4198 lea eax, [edx + ecx]
007a419b mov ecx, esi
007a419d test eax, eax
007a419f js 0x7a4204
007a41a1 mov ecx, dword ptr [ebp - 0x28]
007a41a4 mov ecx, dword ptr [ecx + eax*4 + 0x24]
007a41a8 test ecx, ecx
007a41aa je 0x7a41d4
007a41ac call 0x6dc600
007a41b1 test al, al
007a41b3 mov edx, edi
007a41b5 mov eax, 1
007a41ba cmovne edx, eax
007a41bd mov dword ptr [ebp - 0x2c], edx
007a41c0 call 0x6dc650
007a41c5 test al, al
007a41c7 mov ecx, 0x320
007a41cc mov eax, dword ptr [ebp - 0x2c]
007a41cf cmovne eax, ecx
007a41d2 jmp 0x7a41d7
007a41d4 mov eax, dword ptr [ebp - 0x2c]
007a41d7 mov ecx, esi
007a41d9 cmp eax, edi
007a41db jle 0x7a41df
007a41dd mov eax, edi
007a41df mov edx, dword ptr [ebp - 0x60]
007a41e2 test edx, edx
007a41e4 je 0x7a41f5
007a41e6 mov esi, dword ptr [ebp - 0x38]
007a41e9 cmp edi, dword ptr [esi]
007a41eb jle 0x7a4209
007a41ed cmp edi, 0x384
007a41f3 jle 0x7a4209
007a41f5 mov ecx, dword ptr [ebp - 0x38]
007a41f8 mov edi, dword ptr [ebp - 0x28]
007a41fb mov dword ptr [ecx], eax
007a41fd mov ecx, dword ptr [edi + 0xc]
007a4200 jmp 0x7a420c
007a4202 mov ecx, eax
007a4204 mov eax, dword ptr [ebp - 0x2c]
007a4207 jmp 0x7a41df
007a4209 mov edi, dword ptr [ebp - 0x28]
007a420c inc edx
007a420d mov dword ptr [ebp - 0x60], edx
007a4210 cmp edx, dword ptr [ebp - 0x40]
007a4213 jb 0x7a4100
007a4219 mov esi, dword ptr [edi + 0x10]
007a421c mov edi, dword ptr [ebp - 0x40]
007a421f mov edx, dword ptr [ebp - 0x30]
007a4222 mov eax, esi
007a4224 add dword ptr [ebp - 0x38], 4
007a4228 inc edx
007a4229 imul eax, ecx
007a422c mov dword ptr [ebp - 0x30], edx
007a422f cmp edx, eax
007a4231 jl 0x7a40c0
007a4237 mov edx, dword ptr [ebp - 0x44]
007a423a mov edi, dword ptr [ebx + edx*4 + 0x2c]
007a423e cmp edi, 0x384
007a4244 jle 0x7a4348
007a424a cmp edx, 0x1bf
007a4250 ja 0x7a4266
007a4252 mov eax, dword ptr [ebp - 0x28]
007a4255 cmp dword ptr [eax + edx*4 + 0x76c], 0x384
007a4260 jg 0x7a4348
007a4266 mov eax, dword ptr [0xbfd65c]
007a426b mov esi, dword ptr [eax + 0x18190]
007a4271 mov ecx, esi
007a4273 mov eax, dword ptr [ebp - 0x3c]
007a4276 push eax
007a4277 call 0x7ce950
007a427c cdq 
007a427d idiv dword ptr [esi + 0xc]
007a4280 movss xmm4, dword ptr [0xb6aa3c]
007a4288 movss xmm6, dword ptr [0xb6ab20]
007a4290 movd xmm3, eax
007a4294 mov eax, dword ptr [ebp - 0x5c]
007a4297 movd xmm2, edx
007a429b cvtdq2ps xmm2, xmm2
007a429e mov ecx, dword ptr [eax + 4]
007a42a1 mov esi, dword ptr [eax]
007a42a3 sub ecx, esi
007a42a5 sar ecx, 3
007a42a8 cvtdq2ps xmm3, xmm3
007a42ab shr ecx, 1
007a42ad mov dword ptr [ebp - 0x30], ecx
007a42b0 mulss xmm2, xmm4
007a42b4 mulss xmm3, xmm4
007a42b8 addss xmm2, xmm4
007a42bc addss xmm3, xmm6
007a42c0 je 0x7a4348
007a42c6 movss xmm5, dword ptr [0xb6a480]
007a42ce nop 
007a42d0 movaps xmm0, xmm2
007a42d3 movaps xmm1, xmm3
007a42d6 subss xmm0, dword ptr [esi]
007a42da subss xmm1, dword ptr [esi + 4]
007a42df subss xmm0, xmm4
007a42e3 subss xmm1, xmm6
007a42e7 divss xmm0, xmm4
007a42eb divss xmm1, xmm4
007a42ef addss xmm0, xmm5
007a42f3 addss xmm1, xmm5
007a42f7 cvttss2si edx, xmm0
007a42fb cvttss2si eax, xmm1
007a42ff test edx, edx
007a4301 js 0x7a4323
007a4303 mov ecx, dword ptr [ebp - 0x28]
007a4306 mov ecx, dword ptr [ecx + 0xc]
007a4309 cmp edx, ecx
007a430b jge 0x7a4323
007a430d test eax, eax
007a430f js 0x7a4323
007a4311 mov ebx, dword ptr [ebp - 0x28]
007a4314 cmp eax, dword ptr [ebx + 0x10]
007a4317 mov ebx, dword ptr [ebp - 0x58]
007a431a jge 0x7a4323
007a431c imul ecx, eax
007a431f add ecx, edx
007a4321 jmp 0x7a4326
007a4323 or ecx, 0xffffffff
007a4326 mov eax, dword ptr [ebx + ecx*4 + 0x2c]
007a432a cmp eax, edi
007a432c cmovge ecx, dword ptr [ebp - 0x44]
007a4330 add esi, 8
007a4333 cmp eax, edi
007a4335 mov edx, ecx
007a4337 mov dword ptr [ebp - 0x44], edx
007a433a cmovge eax, edi
007a433d sub dword ptr [ebp - 0x30], 1
007a4341 mov edi, eax
007a4343 jne 0x7a42d0
007a4345 mov dword ptr [ebp - 0x44], edx
007a4348 mov byte ptr [ebp - 4], 0
007a434c mov ecx, dword ptr [ebp - 0x1c]
007a434f test ecx, ecx
007a4351 je 0x7a4383
007a4353 mov edx, dword ptr [ebp - 0x14]
007a4356 mov eax, ecx
007a4358 sub edx, ecx
007a435a and edx, 0xfffffff8
007a435d cmp edx, 0x1000
007a4363 jb 0x7a4379
007a4365 mov ecx, dword ptr [ecx - 4]
007a4368 add edx, 0x23
007a436b sub eax, ecx
007a436d add eax, -4
007a4370 cmp eax, 0x1f
007a4373 ja 0x7a4547
007a4379 push edx
007a437a push ecx
007a437b call 0x9eb08e
007a4380 add esp, 8
007a4383 mov eax, dword ptr [ebp - 0x44]
007a4386 lea ecx, [ebp - 0x8c]
007a438c mov dword ptr [ebp - 0x4c], eax
007a438f lea eax, [ebp - 0x4c]
007a4392 push eax
007a4393 mov dword ptr [ebp - 0x48], 0
007a439a call 0x7a7bb0
007a439f mov esi, dword ptr [ebp - 0x8c]
007a43a5 mov byte ptr [ebx + 0x72d], 0
007a43ac cmp esi, dword ptr [ebp - 0x88]
007a43b2 je 0x7a451e
007a43b8 nop dword ptr [eax + eax]
007a43c0 cmp byte ptr [ebx + 0x72d], 0
007a43c7 jne 0x7a451e
007a43cd mov ecx, dword ptr [0xbfd65c]
007a43d3 mov eax, dword ptr [esi]
007a43d5 mov edi, dword ptr [esi + 4]
007a43d8 mov dword ptr [ebp - 0x30], eax
007a43db mov ecx, dword ptr [ecx + 0x18190]
007a43e1 mov dword ptr [ebp - 0x60], edi
007a43e4 mov eax, dword ptr [ecx + 0x10]
007a43e7 imul eax, dword ptr [ecx + 0xc]
007a43eb cdq 
007a43ec sub eax, edx
007a43ee sar eax, 1
007a43f0 cmp edi, eax
007a43f2 jge 0x7a451e
007a43f8 lea ecx, [ebp - 0x8c]
007a43fe call 0x7a7aa0
007a4403 mov eax, dword ptr [0xbfd65c]
007a4408 mov ebx, dword ptr [eax + 0x18190]
007a440e mov eax, dword ptr [ebp - 0x30]
007a4411 cdq 
007a4412 mov esi, dword ptr [ebx + 0xc]
007a4415 idiv esi
007a4417 mov ecx, eax
007a4419 lea eax, [edx - 1]
007a441c mov dword ptr [ebp - 0x30], eax
007a441f test eax, eax
007a4421 js 0x7a4440
007a4423 cmp eax, esi
007a4425 jge 0x7a4440
007a4427 test ecx, ecx
007a4429 js 0x7a4440
007a442b cmp ecx, dword ptr [ebx + 0x10]
007a442e jge 0x7a4440
007a4430 mov eax, esi
007a4432 imul eax, ecx
007a4435 add eax, dword ptr [ebp - 0x30]
007a4438 mov dword ptr [ebp - 0x20], eax
007a443b lea eax, [ecx - 1]
007a443e jmp 0x7a444e
007a4440 mov dword ptr [ebp - 0x20], 0xffffffff
007a4447 lea eax, [ecx - 1]
007a444a test edx, edx
007a444c js 0x7a4462
007a444e cmp edx, esi
007a4450 jge 0x7a4462
007a4452 test eax, eax
007a4454 js 0x7a4462
007a4456 cmp eax, dword ptr [ebx + 0x10]
007a4459 jge 0x7a4462
007a445b imul eax, esi
007a445e add eax, edx
007a4460 jmp 0x7a4465
007a4462 or eax, 0xffffffff
007a4465 mov dword ptr [ebp - 0x1c], eax
007a4468 lea eax, [edx + 1]
007a446b mov dword ptr [ebp - 0x30], eax
007a446e test eax, eax
007a4470 js 0x7a4489
007a4472 cmp eax, esi
007a4474 jge 0x7a4489
007a4476 test ecx, ecx
007a4478 js 0x7a4489
007a447a cmp ecx, dword ptr [ebx + 0x10]
007a447d jge 0x7a4489
007a447f mov eax, esi
007a4481 imul eax, ecx
007a4484 add eax, dword ptr [ebp - 0x30]
007a4487 jmp 0x7a448c
007a4489 or eax, 0xffffffff
007a448c mov dword ptr [ebp - 0x18], eax
007a448f lea eax, [ecx + 1]
007a4492 test edx, edx
007a4494 js 0x7a44aa
007a4496 cmp edx, esi
007a4498 jge 0x7a44aa
007a449a test eax, eax
007a449c js 0x7a44aa
007a449e cmp eax, dword ptr [ebx + 0x10]
007a44a1 jge 0x7a44aa
007a44a3 imul eax, esi
007a44a6 add eax, edx
007a44a8 jmp 0x7a44ad
007a44aa or eax, 0xffffffff
007a44ad mov dword ptr [ebp - 0x14], eax
007a44b0 xor esi, esi
007a44b2 mov ecx, dword ptr [ebp + esi*4 - 0x20]
007a44b6 mov ebx, dword ptr [ebp - 0x58]
007a44b9 mov dword ptr [ebp - 0x4c], ecx
007a44bc mov dword ptr [ebp - 0x48], edi
007a44bf test ecx, ecx
007a44c1 js 0x7a4506
007a44c3 mov eax, dword ptr [ebx + ecx*4 + 0x2c]
007a44c7 test eax, eax
007a44c9 js 0x7a4506
007a44cb cmp eax, 0x3b6
007a44d0 jge 0x7a4506
007a44d2 test eax, eax
007a44d4 jle 0x7a44df
007a44d6 cmp byte ptr [ebp - 0x23], 0
007a44da lea eax, [edi + 7]
007a44dd je 0x7a44e2
007a44df lea eax, [edi + 1]
007a44e2 mov dword ptr [ebp - 0x48], eax
007a44e5 neg eax
007a44e7 mov dword ptr [ebx + ecx*4 + 0x2c], eax
007a44eb cmp ecx, dword ptr [ebx + 0x20]
007a44ee jne 0x7a44f7
007a44f0 mov byte ptr [ebx + 0x72d], 1
007a44f7 lea eax, [ebp - 0x4c]
007a44fa push eax
007a44fb lea ecx, [ebp - 0x8c]
007a4501 call 0x7a7bb0
007a4506 inc esi
007a4507 cmp esi, 4
007a450a jb 0x7a44b2
007a450c mov esi, dword ptr [ebp - 0x8c]
007a4512 cmp esi, dword ptr [ebp - 0x88]
007a4518 jne 0x7a43c0
007a451e test esi, esi
007a4520 je 0x7a4570
007a4522 mov ecx, dword ptr [ebp - 0x84]
007a4528 mov eax, esi
007a452a sub ecx, esi
007a452c and ecx, 0xfffffff8
007a452f cmp ecx, 0x1000
007a4535 jb 0x7a454d
007a4537 mov esi, dword ptr [esi - 4]
007a453a add ecx, 0x23
007a453d sub eax, esi
007a453f add eax, -4
007a4542 cmp eax, 0x1f
007a4545 jbe 0x7a454d
007a4547 call dword ptr [0xa065ac]
007a454d push ecx
007a454e push esi
007a454f call 0x9eb08e
007a4554 add esp, 8
007a4557 jmp 0x7a4570
007a4559 mov ecx, dword ptr [ebx]
007a455b cvttss2si eax, dword ptr [ecx + 0x2fc]
007a4563 cvttss2si ecx, dword ptr [ecx + 0x2f8]
007a456b sub ecx, eax
007a456d add dword ptr [ebx + 0x28], ecx
007a4570 cmp byte ptr [ebx + 0x72d], 0
007a4577 je 0x7a46b7
007a457d mov eax, dword ptr [0xbfd65c]
007a4582 mov edi, dword ptr [eax + 0x18190]
007a4588 mov eax, dword ptr [ebx + 0x20]
007a458b mov dword ptr [ebp - 0x3c], eax
007a458e cdq 
007a458f mov esi, dword ptr [edi + 0xc]
007a4592 idiv esi
007a4594 mov dword ptr [ebp - 0x60], esi
007a4597 mov ecx, eax
007a4599 lea ebx, [edx - 1]
007a459c test ebx, ebx
007a459e js 0x7a45ba
007a45a0 cmp ebx, esi
007a45a2 jge 0x7a45ba
007a45a4 test ecx, ecx
007a45a6 js 0x7a45ba
007a45a8 cmp ecx, dword ptr [edi + 0x10]
007a45ab jge 0x7a45ba
007a45ad imul eax, esi
007a45b0 lea esi, [ecx - 1]
007a45b3 add eax, ebx
007a45b5 mov dword ptr [ebp - 0x20], eax
007a45b8 jmp 0x7a45c8
007a45ba mov dword ptr [ebp - 0x20], 0xffffffff
007a45c1 lea esi, [ecx - 1]
007a45c4 test edx, edx
007a45c6 js 0x7a45df
007a45c8 mov eax, dword ptr [edi + 0xc]
007a45cb cmp edx, eax
007a45cd jge 0x7a45e2
007a45cf test esi, esi
007a45d1 js 0x7a45e2
007a45d3 cmp esi, dword ptr [edi + 0x10]
007a45d6 jge 0x7a45e2
007a45d8 imul esi, eax
007a45db add esi, edx
007a45dd jmp 0x7a45e5
007a45df mov eax, dword ptr [edi + 0xc]
007a45e2 or esi, 0xffffffff
007a45e5 lea ebx, [edx + 1]
007a45e8 mov dword ptr [ebp - 0x1c], esi
007a45eb mov dword ptr [ebp - 0x30], ebx
007a45ee test ebx, ebx
007a45f0 mov ebx, dword ptr [ebp - 0x58]
007a45f3 js 0x7a460e
007a45f5 cmp dword ptr [ebp - 0x30], eax
007a45f8 jge 0x7a460e
007a45fa test ecx, ecx
007a45fc js 0x7a460e
007a45fe cmp ecx, dword ptr [edi + 0x10]
007a4601 jge 0x7a460e
007a4603 mov eax, ecx
007a4605 imul eax, dword ptr [edi + 0xc]
007a4609 add eax, dword ptr [ebp - 0x30]
007a460c jmp 0x7a4611
007a460e or eax, 0xffffffff
007a4611 inc ecx
007a4612 mov dword ptr [ebp - 0x18], eax
007a4615 test edx, edx
007a4617 js 0x7a4630
007a4619 mov eax, dword ptr [edi + 0xc]
007a461c cmp edx, eax
007a461e jge 0x7a4630
007a4620 test ecx, ecx
007a4622 js 0x7a4630
007a4624 cmp ecx, dword ptr [edi + 0x10]
007a4627 jge 0x7a4630
007a4629 imul ecx, eax
007a462c add ecx, edx
007a462e jmp 0x7a4633
007a4630 or ecx, 0xffffffff
007a4633 mov dword ptr [ebp - 0x14], ecx
007a4636 xor ecx, ecx
007a4638 mov dword ptr [ebp - 0x30], 0xfffffc18
007a463f nop 
007a4640 cmp dword ptr [edi + 8], 0x10
007a4644 jne 0x7a4661
007a4646 cmp ecx, 1
007a4649 jne 0x7a4661
007a464b cmp esi, 0x1bf
007a4651 ja 0x7a4661
007a4653 mov eax, dword ptr [edi + esi*4 + 0x24]
007a4657 test eax, eax
007a4659 je 0x7a4661
007a465b cmp dword ptr [eax + 4], 0x13
007a465f je 0x7a467e
007a4661 mov eax, dword ptr [ebp + ecx*4 - 0x20]
007a4665 test eax, eax
007a4667 js 0x7a467e
007a4669 mov edx, dword ptr [ebx + eax*4 + 0x2c]
007a466d test edx, edx
007a466f jns 0x7a467e
007a4671 cmp edx, dword ptr [ebp - 0x30]
007a4674 jle 0x7a467e
007a4676 mov dword ptr [ebp - 0x3c], eax
007a4679 mov dword ptr [ebp - 0x30], edx
007a467c jmp 0x7a4681
007a467e mov eax, dword ptr [ebp - 0x3c]
007a4681 inc ecx
007a4682 cmp ecx, 4
007a4685 jb 0x7a4640
007a4687 cdq 
007a4688 idiv dword ptr [ebp - 0x60]
007a468b movss xmm0, dword ptr [0xb6aa3c]
007a4693 movd xmm2, edx
007a4697 movd xmm1, eax
007a469b cvtdq2ps xmm2, xmm2
007a469e cvtdq2ps xmm1, xmm1
007a46a1 mulss xmm2, xmm0
007a46a5 mulss xmm1, xmm0
007a46a9 addss xmm2, xmm0
007a46ad addss xmm1, dword ptr [0xb6ab20]
007a46b5 jmp 0x7a46c1
007a46b7 movss xmm2, dword ptr [ebp - 0x54]
007a46bc movss xmm1, dword ptr [ebp - 0x68]
007a46c1 ucomiss xmm2, dword ptr [0xc02fec]
007a46c8 lahf 
007a46c9 test ah, 0x44
007a46cc jp 0x7a46fa
007a46ce ucomiss xmm1, dword ptr [0xc02ff0]
007a46d5 lahf 
007a46d6 test ah, 0x44
007a46d9 jp 0x7a46fa
007a46db mov eax, dword ptr [ebx]
007a46dd movss xmm0, dword ptr [eax + 0x2c4]
007a46e5 mulss xmm0, dword ptr [0xb6a588]
007a46ed movss dword ptr [eax + 0x2c4], xmm0
007a46f5 jmp 0x7a47f5
007a46fa subss xmm1, dword ptr [ebp - 0x74]
007a46ff subss xmm2, dword ptr [ebp - 0x78]
007a4704 mov esi, dword ptr [ebx]
007a4706 movaps xmm0, xmm1
007a4709 movss dword ptr [ebp - 0x68], xmm1
007a470e mulss xmm0, xmm1
007a4712 movaps xmm1, xmm2
007a4715 mulss xmm1, xmm2
007a4719 movss dword ptr [ebp - 0x54], xmm2
007a471e addss xmm0, xmm1
007a4722 call 0x4228c0
007a4727 movaps xmm2, xmm0
007a472a comiss xmm2, dword ptr [0xb6a614]
007a4731 jbe 0x7a47dd
007a4737 movss xmm0, dword ptr [ebp - 0x50]
007a473c movaps xmm1, xmm2
007a473f mulss xmm1, dword ptr [0xb6a2cc]
007a4747 mulss xmm0, dword ptr [ebp + 0xc]
007a474c movss xmm3, dword ptr [ebp - 0x54]
007a4751 movss xmm4, dword ptr [ebp - 0x68]
007a4756 minss xmm1, dword ptr [0xb6a7b0]
007a475e divss xmm3, xmm2
007a4762 divss xmm4, xmm2
007a4766 mulss xmm1, xmm0
007a476a movss xmm0, dword ptr [esi + 0x2c4]
007a4772 mulss xmm0, dword ptr [0xb6a50c]
007a477a mulss xmm3, xmm1
007a477e movss dword ptr [esi + 0x2c4], xmm0
007a4786 xorps xmm0, xmm0
007a4789 mov ecx, dword ptr [ebx]
007a478b mulss xmm4, xmm1
007a478f movss xmm2, dword ptr [ecx + 0x2c4]
007a4797 ucomiss xmm2, xmm0
007a479a lahf 
007a479b test ah, 0x44
007a479e jnp 0x7a47f5
007a47a0 movss xmm1, dword ptr [ecx + 0x2f4]
007a47a8 movaps xmm0, xmm1
007a47ab mulss xmm1, xmm4
007a47af mulss xmm0, xmm3
007a47b3 divss xmm1, xmm2
007a47b7 divss xmm0, xmm2
007a47bb addss xmm1, dword ptr [ecx + 0x2bc]
007a47c3 addss xmm0, dword ptr [ecx + 0x2b8]
007a47cb movss dword ptr [ecx + 0x2bc], xmm1
007a47d3 movss dword ptr [ecx + 0x2b8], xmm0
007a47db jmp 0x7a47f5
007a47dd movss xmm0, dword ptr [esi + 0x2c4]
007a47e5 mulss xmm0, dword ptr [0xb6a480]
007a47ed movss dword ptr [esi + 0x2c4], xmm0
007a47f5 mov ecx, dword ptr [ebp - 0xc]
007a47f8 mov dword ptr fs:[0], ecx
007a47ff pop ecx
007a4800 pop edi
007a4801 pop esi
007a4802 pop ebx
007a4803 mov ecx, dword ptr [ebp - 0x10]
007a4806 xor ecx, ebp
007a4808 call 0x9eacd7
007a480d mov esp, ebp
007a480f pop ebp
007a4810 ret 0x10
