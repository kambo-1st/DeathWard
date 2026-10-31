007a7610 push ebp
007a7611 mov ebp, esp
007a7613 and esp, 0xfffffff8
007a7616 sub esp, 0x50
007a7619 push esi
007a761a mov esi, dword ptr [ebp + 8]
007a761d push edi
007a761e mov edi, ecx
007a7620 movss dword ptr [esp + 0x18], xmm2
007a7626 movss xmm2, dword ptr [esi]
007a762a movss xmm1, dword ptr [esi + 4]
007a762f mov eax, dword ptr [edi]
007a7631 movss dword ptr [esp + 0x1c], xmm2
007a7637 movss dword ptr [esp + 0xc], xmm1
007a763d mov ecx, dword ptr [eax + 0x17c]
007a7643 mov eax, dword ptr [eax + 0x160]
007a7649 and eax, 0x8000
007a764e mov dword ptr [esp + 0x24], ecx
007a7652 or eax, 0
007a7655 je 0x7a7665
007a7657 cmp ecx, 5
007a765a jne 0x7a7665
007a765c xorps xmm1, xmm1
007a765f movss dword ptr [esp + 0xc], xmm1
007a7665 movaps xmm0, xmm1
007a7668 mulss xmm0, xmm1
007a766c movaps xmm1, xmm2
007a766f mulss xmm1, xmm2
007a7673 addss xmm0, xmm1
007a7677 call 0x4228c0
007a767c movss xmm1, dword ptr [0xb6a614]
007a7684 xorps xmm3, xmm3
007a7687 comiss xmm0, xmm1
007a768a jbe 0x7a76af
007a768c comiss xmm0, xmm3
007a768f jbe 0x7a76af
007a7691 divss xmm1, xmm0
007a7695 movss xmm0, dword ptr [esi]
007a7699 mulss xmm0, xmm1
007a769d movss dword ptr [esp + 0x1c], xmm0
007a76a3 movss xmm0, dword ptr [esp + 0xc]
007a76a9 mulss xmm0, xmm1
007a76ad jmp 0x7a76b5
007a76af movss xmm0, dword ptr [esp + 0xc]
007a76b5 movss xmm4, dword ptr [esp + 0x18]
007a76bb mulss xmm4, dword ptr [0xb6a38c]
007a76c3 addss xmm4, dword ptr [0xb6a53c]
007a76cb movaps xmm5, xmm4
007a76ce mulss xmm4, xmm0
007a76d2 mulss xmm5, dword ptr [esp + 0x1c]
007a76d8 movaps xmm0, xmm4
007a76db movss dword ptr [edi + 0x10], xmm4
007a76e0 andps xmm0, xmmword ptr [0xb6c980]
007a76e7 movaps xmm2, xmm5
007a76ea movss dword ptr [edi + 0xc], xmm5
007a76ef andps xmm2, xmmword ptr [0xb6c980]
007a76f6 comiss xmm2, xmm0
007a76f9 mov dword ptr [edi + 0x14], 0xffffffff
007a7700 movss dword ptr [esp + 0x1c], xmm5
007a7706 movss dword ptr [esp + 0x14], xmm4
007a770c jbe 0x7a771d
007a770e xor eax, eax
007a7710 mov ecx, 2
007a7715 comiss xmm3, xmm5
007a7718 cmovbe eax, ecx
007a771b jmp 0x7a7739
007a771d comiss xmm3, xmm4
007a7720 jbe 0x7a772b
007a7722 mov dword ptr [edi + 0x14], 1
007a7729 jmp 0x7a773c
007a772b mov eax, dword ptr [edi + 0x14]
007a772e mov ecx, 3
007a7733 comiss xmm4, xmm3
007a7736 cmova eax, ecx
007a7739 mov dword ptr [edi + 0x14], eax
007a773c mov ecx, dword ptr [edi]
007a773e mov dword ptr [esp + 0x54], ecx
007a7742 mov eax, dword ptr [ecx + 0x160]
007a7748 and eax, 0x8000000
007a774d or eax, 0
007a7750 je 0x7a7760
007a7752 mov dword ptr [edi + 0x28], 0x3c
007a7759 mov eax, 0x3c
007a775e jmp 0x7a7772
007a7760 add dword ptr [edi + 0x28], -1
007a7764 mov eax, dword ptr [edi + 0x28]
007a7767 jns 0x7a7772
007a7769 mov dword ptr [edi + 0x28], 0
007a7770 xor eax, eax
007a7772 movd xmm4, eax
007a7776 cvtdq2ps xmm4, xmm4
007a7779 mov eax, dword ptr [ecx + 0x164]
007a777f mov esi, dword ptr [ecx + 0x160]
007a7785 mov dword ptr [esp + 0x4c], eax
007a7789 mov eax, esi
007a778b and eax, 0x80
007a7790 or eax, 0
007a7793 subss xmm4, xmm3
007a7797 divss xmm4, dword ptr [0xb6aa8c]
007a779f movss dword ptr [esp + 0x10], xmm4
007a77a5 je 0x7a77b0
007a77a7 xorps xmm4, xmm4
007a77aa movss dword ptr [esp + 0x10], xmm4
007a77b0 movss xmm2, dword ptr [ecx + 0x2b8]
007a77b8 movaps xmm0, xmm4
007a77bb mulss xmm0, dword ptr [0xb6a50c]
007a77c3 movss xmm1, dword ptr [ecx + 0x2bc]
007a77cb mulss xmm2, dword ptr [0xb6a480]
007a77d3 subss xmm0, dword ptr [0xb6a350]
007a77db mulss xmm1, dword ptr [0xb6a480]
007a77e3 movss dword ptr [esp + 0xc], xmm2
007a77e9 movss dword ptr [esp + 0x2c], xmm0
007a77ef movaps xmm0, xmm4
007a77f2 mulss xmm0, dword ptr [0xb6a338]
007a77fa movss dword ptr [esp + 8], xmm1
007a7800 addss xmm0, dword ptr [0xb6a544]
007a7808 call 0x4228c0
007a780d movss xmm6, dword ptr [esp + 0x1c]
007a7813 and esi, 0x8000
007a7819 movss xmm5, dword ptr [esp + 0x14]
007a781f xorps xmm4, xmm4
007a7822 movss xmm2, dword ptr [esp + 8]
007a7828 movss xmm3, dword ptr [esp + 0xc]
007a782e mov edi, dword ptr [esp + 0x24]
007a7832 movss dword ptr [esp + 0x48], xmm0
007a7838 movss xmm0, dword ptr [esp + 0x18]
007a783e mulss xmm0, dword ptr [0xb6a8dc]
007a7846 mov dword ptr [esp + 0x20], 2
007a784e movss dword ptr [esp + 0x38], xmm0
007a7854 movaps xmm0, xmm6
007a7857 mulss xmm0, dword ptr [0xb6a480]
007a785f movss dword ptr [esp + 0x30], xmm0
007a7865 movaps xmm0, xmm5
007a7868 mulss xmm0, dword ptr [0xb6a480]
007a7870 movss dword ptr [esp + 0x34], xmm0
007a7876 ucomiss xmm6, xmm4
007a7879 lahf 
007a787a test ah, 0x44
007a787d jp 0x7a788c
007a787f ucomiss xmm5, xmm4
007a7882 lahf 
007a7883 test ah, 0x44
007a7886 jnp 0x7a7917
007a788c mov eax, esi
007a788e or eax, 0
007a7891 je 0x7a7898
007a7893 cmp edi, 5
007a7896 je 0x7a7917
007a7898 movaps xmm1, xmm2
007a789b movaps xmm0, xmm3
007a789e mulss xmm0, xmm6
007a78a2 mulss xmm1, xmm5
007a78a6 addss xmm1, xmm0
007a78aa movaps xmm0, xmm1
007a78ad mulss xmm1, xmm5
007a78b1 mulss xmm0, xmm6
007a78b5 movss dword ptr [esp + 0x28], xmm1
007a78bb movss dword ptr [esp + 0x24], xmm0
007a78c1 movss xmm0, dword ptr [esp + 0x10]
007a78c7 mulss xmm0, dword ptr [0xb6a34c]
007a78cf addss xmm0, dword ptr [0xb6a560]
007a78d7 call 0x4228c0
007a78dc movss xmm3, dword ptr [esp + 0xc]
007a78e2 xorps xmm4, xmm4
007a78e5 movss xmm2, dword ptr [esp + 8]
007a78eb subss xmm3, dword ptr [esp + 0x24]
007a78f1 subss xmm2, dword ptr [esp + 0x28]
007a78f7 movss xmm5, dword ptr [esp + 0x14]
007a78fd movss xmm6, dword ptr [esp + 0x1c]
007a7903 mulss xmm3, xmm0
007a7907 mulss xmm2, xmm0
007a790b addss xmm3, dword ptr [esp + 0x24]
007a7911 addss xmm2, dword ptr [esp + 0x28]
007a7917 movaps xmm1, xmm2
007a791a movss dword ptr [esp + 0x24], xmm3
007a7920 mulss xmm1, xmm5
007a7924 movaps xmm0, xmm3
007a7927 mulss xmm0, xmm6
007a792b movss dword ptr [esp + 0x28], xmm2
007a7931 addss xmm1, xmm0
007a7935 movss xmm0, dword ptr [esp + 0x2c]
007a793b mulss xmm0, xmm1
007a793f maxss xmm0, xmm4
007a7943 divss xmm0, dword ptr [esp + 0x18]
007a7949 addss xmm0, dword ptr [0xb6a864]
007a7951 mulss xmm0, dword ptr [0xb6a434]
007a7959 movaps xmm1, xmm0
007a795c mulss xmm1, dword ptr [0xb6a38c]
007a7964 subss xmm1, xmm0
007a7968 mulss xmm1, dword ptr [esp + 0x10]
007a796e addss xmm1, xmm0
007a7972 movaps xmm0, xmm1
007a7975 mulss xmm1, dword ptr [esp + 0x34]
007a797b mulss xmm0, dword ptr [esp + 0x30]
007a7981 addss xmm2, xmm1
007a7985 addss xmm3, xmm0
007a7989 movss xmm0, dword ptr [esp + 0x10]
007a798f comiss xmm0, xmm4
007a7992 movaps xmm7, xmm2
007a7995 movss dword ptr [esp + 8], xmm2
007a799b movaps xmm6, xmm3
007a799e movss dword ptr [esp + 0xc], xmm3
007a79a4 movss dword ptr [esp + 0x40], xmm6
007a79aa movss dword ptr [esp + 0x44], xmm7
007a79b0 jbe 0x7a7a36
007a79b6 movaps xmm1, xmm7
007a79b9 movaps xmm0, xmm6
007a79bc mulss xmm1, xmm7
007a79c0 mulss xmm0, xmm6
007a79c4 addss xmm0, xmm1
007a79c8 movss xmm1, dword ptr [esp + 0x38]
007a79ce mulss xmm1, xmm1
007a79d2 comiss xmm0, xmm1
007a79d5 jbe 0x7a7a36
007a79d7 call 0x4228c0
007a79dc xorps xmm4, xmm4
007a79df movss dword ptr [esp + 0x3c], xmm0
007a79e5 comiss xmm0, xmm4
007a79e8 jbe 0x7a7a24
007a79ea movss xmm1, dword ptr [esp + 0x24]
007a79f0 movss xmm0, dword ptr [esp + 0x28]
007a79f6 mulss xmm0, xmm0
007a79fa mulss xmm1, xmm1
