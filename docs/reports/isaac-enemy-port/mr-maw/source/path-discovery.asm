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
