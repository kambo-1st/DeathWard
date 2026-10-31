006375e0 push ebp
006375e1 mov ebp, esp
006375e3 and esp, 0xfffffff8
006375e6 sub esp, 0x94
006375ec mov eax, dword ptr [0xbaa3b4]
006375f1 xor eax, esp
006375f3 mov dword ptr [esp + 0x90], eax
006375fa push ebx
006375fb mov ebx, dword ptr [ebp + 8]
006375fe push esi
006375ff push edi
00637600 push dword ptr [ebp + 0xc]
00637603 mov edi, ecx
00637605 push ebx
00637606 push edi
00637607 mov dword ptr [esp + 0x48], edi
0063760b call 0x7fee20
00637610 cmp eax, 1
00637613 je 0x6385c3
00637619 cmp eax, -1
0063761c jne 0x637637
0063761e xor al, al
00637620 pop edi
00637621 pop esi
00637622 pop ebx
00637623 mov ecx, dword ptr [esp + 0x90]
0063762a xor ecx, esp
0063762c call 0x9eacd7
00637631 mov esp, ebp
00637633 pop ebp
00637634 ret 8
00637637 mov edx, dword ptr [edi + 0x2c]
0063763a cmp edx, 0xe
0063763d mov ecx, dword ptr [ebp + 0xc]
00637640 sete al
00637643 mov byte ptr [esp + 0xe], al
00637647 test cl, cl
00637649 je 0x63785b
0063764f mov esi, dword ptr [ebx + 0x28]
00637652 cmp esi, 0x393
00637658 jne 0x6376f7
0063765e cmp dword ptr [ebx + 0x2c], 1
00637662 jne 0x637701
00637668 mov byte ptr [edi + 0x16b], 1
0063766f movss xmm2, dword ptr [ebx + 0x2c4]
00637677 ucomiss xmm2, dword ptr [0xb6a18c]
0063767e movss xmm1, dword ptr [edi + 0x2b8]
00637686 movss xmm3, dword ptr [edi + 0x2bc]
0063768e mulss xmm1, dword ptr [0xb6a350]
00637696 mulss xmm3, dword ptr [0xb6a350]
0063769e lahf 
0063769f test ah, 0x44
006376a2 jnp 0x6385c5
006376a8 movss xmm0, dword ptr [ebx + 0x2f4]
006376b0 mulss xmm1, xmm0
006376b4 mulss xmm0, xmm3
006376b8 divss xmm1, xmm2
006376bc divss xmm0, xmm2
006376c0 addss xmm1, dword ptr [ebx + 0x2b8]
006376c8 addss xmm0, dword ptr [ebx + 0x2bc]
006376d0 movss dword ptr [ebx + 0x2b8], xmm1
006376d8 movss dword ptr [ebx + 0x2bc], xmm0
006376e0 pop edi
006376e1 pop esi
006376e2 pop ebx
006376e3 mov ecx, dword ptr [esp + 0x90]
006376ea xor ecx, esp
006376ec call 0x9eacd7
006376f1 mov esp, ebp
006376f3 pop ebp
006376f4 ret 8
006376f7 lea eax, [esi - 0xa]
006376fa cmp eax, 0x3dd
006376ff ja 0x63775a
00637701 push 0x20000
00637706 push 0
00637708 mov ecx, ebx
0063770a call 0x4122f0
0063770f test al, al
00637711 je 0x637754
00637713 mov edx, dword ptr [ebx]
00637715 lea ecx, [esp + 0x70]
00637719 push 0x1e
0063771b call 0x427290
00637720 push eax
00637721 push 0
00637723 push 0
00637725 push ecx
00637726 mov ecx, ebx
00637728 mov dword ptr [esp], 0x3f800000
0063772f call dword ptr [edx + 0x20]
00637732 mov al, byte ptr [esp + 0xe]
00637736 mov byte ptr [edi + 0x16b], 1
0063773d pop edi
0063773e pop esi
0063773f pop ebx
00637740 mov ecx, dword ptr [esp + 0x90]
00637747 xor ecx, esp
00637749 call 0x9eacd7
0063774e mov esp, ebp
00637750 pop ebp
00637751 ret 8
00637754 mov ecx, dword ptr [ebp + 0xc]
00637757 mov edx, dword ptr [edi + 0x2c]
0063775a cmp esi, 0xf5
00637760 jne 0x63785b
00637766 mov eax, dword ptr [edi + 0x28]
00637769 movss xmm0, dword ptr [edi + 0x294]
00637771 movss xmm1, dword ptr [edi + 0x298]
00637779 mov ecx, dword ptr [edi + 0x160]
0063777f mov dword ptr [esp + 0x70], eax
00637783 mov eax, dword ptr [edi + 0x34]
00637786 mov dword ptr [esp + 0x78], eax
0063778a mov eax, dword ptr [edi + 0x38]
0063778d mov dword ptr [esp + 0x7c], eax
00637791 mov eax, ecx
00637793 movss dword ptr [esp + 0x80], xmm0
0063779c and eax, 0x100
006377a1 or eax, 0
006377a4 movss xmm0, dword ptr [edi + 0x2b8]
006377ac movss dword ptr [esp + 0x84], xmm1
006377b5 movss xmm1, dword ptr [edi + 0x2bc]
006377bd mov dword ptr [esp + 0x74], edx
006377c1 mov edx, dword ptr [edi + 0x164]
006377c7 movss dword ptr [esp + 0x88], xmm0
006377d0 movss dword ptr [esp + 0x8c], xmm1
006377d9 je 0x6377e2
006377db mov esi, 1
006377e0 jmp 0x6377e4
006377e2 xor esi, esi
006377e4 and ecx, 0x20000000
006377ea or ecx, 0
006377ed je 0x6377f6
006377ef mov ecx, 2
006377f4 jmp 0x6377f8
006377f6 xor ecx, ecx
006377f8 and edx, 0x400000
006377fe xor eax, eax
00637800 or eax, edx
00637802 je 0x63780b
00637804 mov eax, 4
00637809 jmp 0x63780d
0063780b xor eax, eax
0063780d or eax, ecx
0063780f mov dword ptr [esp + 0x94], edi
00637816 push 0x1e
00637818 lea ecx, [esp + 0x74]
0063781c or eax, esi
0063781e push ecx
0063781f push 0
00637821 mov dword ptr [esp + 0x9c], eax
00637828 mov eax, dword ptr [ebx]
0063782a push 0x40
0063782c push ecx
0063782d mov ecx, ebx
0063782f mov dword ptr [esp], 0x3f800000
00637836 call dword ptr [eax + 0x20]
00637839 mov al, byte ptr [esp + 0xe]
0063783d mov byte ptr [edi + 0x16b], 1
00637844 pop edi
00637845 pop esi
00637846 pop ebx
00637847 mov ecx, dword ptr [esp + 0x90]
0063784e xor ecx, esp
00637850 call 0x9eacd7
00637855 mov esp, ebp
00637857 pop ebp
00637858 ret 8
0063785b cmp dword ptr [edi + 0x34], 0x362
00637862 jne 0x63788e
00637864 mov eax, dword ptr [ebx + 0x28]
00637867 cmp eax, 3
0063786a je 0x6385c3
00637870 cmp eax, 1
00637873 jne 0x63788e
00637875 mov eax, dword ptr [ebx + 0x130c]
0063787b cmp eax, 0x13
0063787e je 0x63788e
00637880 cmp eax, 0x25
00637883 je 0x63788e
00637885 cmp eax, 0x27
00637888 jne 0x6385c3
0063788e test cl, cl
00637890 jne 0x637ff5
00637896 cmp dword ptr [ebx + 0x28], 1
0063789a jne 0x638068
006378a0 mov eax, dword ptr [edi + 0x388]
006378a6 and eax, 0x80000000
006378ab or eax, 0
006378ae jne 0x6385c3
006378b4 push eax
006378b5 push 0xbeab9c
006378ba push 0xbeab18
006378bf push eax
006378c0 push ebx
006378c1 call 0x9ec34c
006378c6 movss xmm1, dword ptr [0xb6a480]
006378ce lea ecx, [esp + 0x40]
006378d2 mov ebx, eax
006378d4 mov dword ptr [esp + 0x40], 0x3f000000
006378dc add esp, 0x14
006378df mov dword ptr [esp + 0x60], ebx
006378e3 lea eax, [esp + 0x28]
006378e7 movss xmm0, dword ptr [ebx + 0xdc]
006378ef comiss xmm1, xmm0
006378f2 movss dword ptr [esp + 0x28], xmm0
006378f8 movss xmm0, dword ptr [0xb6a614]
00637900 cmovbe ecx, eax
00637903 movss xmm1, dword ptr [ecx]
00637907 comiss xmm1, xmm0
0063790a ja 0x637912
0063790c movss xmm0, xmm1
00637910 jmp 0x637916
00637912 movss xmm0, xmm0
00637916 mulss xmm0, dword ptr [0xb6af28]
0063791e comiss xmm0, dword ptr [edi + 0x2a8]
00637925 ja 0x6385c3
0063792b mov eax, dword ptr [edi + 0x38c]
00637931 xorps xmm0, xmm0
00637934 mov ecx, dword ptr [edi + 0x388]
0063793a mov dword ptr [esp + 0x44], eax
0063793e mov eax, ecx
00637940 and eax, 0x8000
00637945 mov byte ptr [edi + 0x16b], 1
0063794c or eax, 0
0063794f mov byte ptr [esp + 0xf], 0
00637954 movlpd qword ptr [esp + 0x18], xmm0
0063795a je 0x63796e
0063795c mov dword ptr [esp + 0x10], 2
00637964 mov dword ptr [esp + 0x14], 0
0063796c jmp 0x63797e
0063796e mov eax, dword ptr [esp + 0x1c]
00637972 mov dword ptr [esp + 0x14], eax
00637976 mov eax, dword ptr [esp + 0x18]
0063797a mov dword ptr [esp + 0x10], eax
0063797e and ecx, 2
00637981 or ecx, 0
00637984 jne 0x637ba9
0063798a push ecx
0063798b push 0x5b
0063798d mov ecx, ebx
0063798f call 0x73af30
00637994 test al, al
00637996 jne 0x6379ae
00637998 push 0
0063799a push 0x177
0063799f mov ecx, ebx
006379a1 call 0x73af30
006379a6 test al, al
006379a8 je 0x637a51
006379ae mov eax, dword ptr [0xbfd65c]
006379b3 mov eax, dword ptr [eax + 0x18190]
006379b9 cmp dword ptr [eax + 8], 0x10
006379bd jne 0x637a13
006379bf movss xmm0, dword ptr [edi + 0x294]
006379c7 lea eax, [esp + 0x40]
006379cb subss xmm0, dword ptr [ebx + 0x294]
006379d3 push eax
006379d4 lea ecx, [esp + 0x1c]
006379d8 movss dword ptr [esp + 0x1c], xmm0
006379de movss xmm0, dword ptr [edi + 0x298]
006379e6 subss xmm0, dword ptr [ebx + 0x298]
006379ee movss dword ptr [esp + 0x20], xmm0
006379f4 call 0x962560
006379f9 movss xmm0, dword ptr [0xb6a560]
00637a01 xor ecx, ecx
00637a03 comiss xmm0, dword ptr [eax]
00637a06 seta cl
00637a09 test ecx, ecx
00637a0b jne 0x637ba9
00637a11 jmp 0x637a51
00637a13 movss xmm0, dword ptr [edi + 0x368]
00637a1b comiss xmm0, dword ptr [0xb6a18c]
00637a22 jbe 0x637a51
00637a24 movss xmm0, dword ptr [edi + 0x364]
00637a2c mulss xmm0, dword ptr [edi + 0x2f4]
00637a34 movss xmm1, dword ptr [edi + 0x360]
00637a3c subss xmm1, xmm0
00637a40 movss xmm0, dword ptr [0xb6af28]
00637a48 comiss xmm0, xmm1
00637a4b ja 0x637ba9
00637a51 push 0
00637a53 push 0xf2
00637a58 mov ecx, ebx
00637a5a call 0x73af30
00637a5f test al, al
00637a61 je 0x637ac3
00637a63 call 0x6c3d90
00637a68 test al, 1
00637a6a jne 0x637ac3
00637a6c mov eax, dword ptr [ebx]
00637a6e lea ecx, [esp + 0x70]
00637a72 push 1
00637a74 push 1
00637a76 push 0xff
00637a7b xorps xmm0, xmm0
00637a7e mov dword ptr [esp + 0x9c], 0x3e808081
00637a89 push 0xf
00637a8b movups xmmword ptr [esp + 0x90], xmm0
00637a93 push ecx
00637a94 movaps xmm0, xmmword ptr [0xb6c610]
00637a9b mov ecx, ebx
00637a9d movups xmmword ptr [esp + 0x84], xmm0
00637aa5 mov dword ptr [esp + 0xa8], 0x3e808081
00637ab0 mov dword ptr [esp + 0xac], 0x3f008081
00637abb call dword ptr [eax + 0x38]
00637abe jmp 0x637ba9
00637ac3 mov eax, dword ptr [edi + 0x28]
00637ac6 movss xmm0, dword ptr [edi + 0x294]
00637ace movss xmm1, dword ptr [edi + 0x298]
00637ad6 mov ecx, dword ptr [edi + 0x160]
00637adc mov edx, dword ptr [edi + 0x164]
00637ae2 mov dword ptr [esp + 0x70], eax
00637ae6 mov eax, dword ptr [edi + 0x2c]
00637ae9 mov dword ptr [esp + 0x74], eax
00637aed mov eax, dword ptr [edi + 0x34]
00637af0 mov dword ptr [esp + 0x78], eax
00637af4 mov eax, dword ptr [edi + 0x38]
00637af7 mov dword ptr [esp + 0x7c], eax
00637afb mov eax, ecx
00637afd movss dword ptr [esp + 0x80], xmm0
00637b06 and eax, 0x100
00637b0b or eax, 0
00637b0e movss xmm0, dword ptr [edi + 0x2b8]
00637b16 movss dword ptr [esp + 0x84], xmm1
00637b1f movss xmm1, dword ptr [edi + 0x2bc]
00637b27 movss dword ptr [esp + 0x88], xmm0
00637b30 movss dword ptr [esp + 0x8c], xmm1
00637b39 je 0x637b42
00637b3b mov esi, 1
00637b40 jmp 0x637b44
00637b42 xor esi, esi
00637b44 and ecx, 0x20000000
00637b4a or ecx, 0
00637b4d je 0x637b56
00637b4f mov ecx, 2
00637b54 jmp 0x637b58
00637b56 xor ecx, ecx
00637b58 and edx, 0x400000
00637b5e xor eax, eax
00637b60 or eax, edx
00637b62 je 0x637b6b
00637b64 mov eax, 4
00637b69 jmp 0x637b6d
00637b6b xor eax, eax
00637b6d movss xmm0, dword ptr [edi + 0x2e0]
00637b75 or eax, ecx
00637b77 push 0x1e
00637b79 lea ecx, [esp + 0x74]
00637b7d mov dword ptr [esp + 0x98], edi
00637b84 push ecx
00637b85 push dword ptr [esp + 0x1c]
00637b89 or eax, esi
00637b8b push dword ptr [esp + 0x1c]
00637b8f mov dword ptr [esp + 0xa0], eax
00637b96 mov eax, dword ptr [ebx]
00637b98 push ecx
00637b99 mov ecx, ebx
00637b9b movss dword ptr [esp], xmm0
00637ba0 mov eax, dword ptr [eax + 0x20]
00637ba3 call eax
00637ba5 mov byte ptr [esp + 0xf], al
00637ba9 mov edx, dword ptr [edi + 0x388]
00637baf mov eax, edx
00637bb1 mov esi, dword ptr [edi + 0x38c]
00637bb7 and eax, 0x200
00637bbc or eax, 0
00637bbf mov dword ptr [esp + 0x18], edx
00637bc3 mov ecx, esi
00637bc5 je 0x637f64
00637bcb cmp byte ptr [esp + 0xf], 0
00637bd0 mov dword ptr [esp + 0x18], edx
00637bd4 je 0x637f64
00637bda cmp dword ptr [ebx + 0x12b8], 0
00637be1 mov dword ptr [esp + 0x18], edx
00637be5 jle 0x637f64
00637beb push -1
00637bed mov ecx, ebx
00637bef call 0x725740
00637bf4 call 0x6c3d90
00637bf9 xor edx, edx
00637bfb mov ecx, 3
00637c00 div ecx
00637c02 mov eax, dword ptr [ebx + 0x12b8]
00637c08 inc edx
00637c09 cmp edx, eax
00637c0b cmovl eax, edx
00637c0e mov dword ptr [esp + 0x34], eax
00637c12 test eax, eax
00637c14 jle 0x637f54
00637c1a movss xmm1, dword ptr [0xb6a19c]
00637c22 lea ebx, [edi + 0x294]
00637c28 mov dword ptr [esp + 0x58], ebx
00637c2c mov dword ptr [esp + 0x2c], eax
00637c30 call 0x6c3d90
00637c35 movd xmm0, eax
00637c39 cvtdq2pd xmm0, xmm0
00637c3d shr eax, 0x1f
00637c40 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
00637c49 cvtpd2ps xmm0, xmm0
00637c4d mulss xmm0, xmm1
00637c51 mulss xmm0, dword ptr [0xb6a8f4]
00637c59 addss xmm0, dword ptr [0xb6a7b0]
00637c61 movss dword ptr [esp + 0x10], xmm0
00637c67 call 0x6c3d90
00637c6c mov esi, eax
00637c6e call 0x6c3d90
00637c73 movd xmm0, eax
00637c77 cvtdq2pd xmm0, xmm0
00637c7b shr eax, 0x1f
00637c7e addsd xmm0, qword ptr [eax*8 + 0xb6c940]
00637c87 cvtpd2ps xmm0, xmm0
00637c8b mulss xmm0, xmm1
00637c8f mulss xmm0, dword ptr [0xb6a874]
00637c97 addss xmm0, xmm0
00637c9b movss dword ptr [esp + 0x24], xmm0
00637ca1 call 0x411fe0
00637ca6 mulss xmm0, dword ptr [esp + 0x10]
00637cac movss dword ptr [esp + 0x4c], xmm0
00637cb2 movss dword ptr [esp + 0x18], xmm0
00637cb8 movss xmm0, dword ptr [esp + 0x24]
00637cbe call 0x412010
00637cc3 mov eax, dword ptr [0xbfd65c]
00637cc8 mulss xmm0, dword ptr [esp + 0x10]
00637cce mov dword ptr [esp + 0x30], eax
00637cd2 lea eax, [esp + 0x10]
00637cd6 push eax
00637cd7 lea eax, [esp + 0x3c]
00637cdb mov dword ptr [esp + 0x14], esi
00637cdf push eax
00637ce0 push 0
00637ce2 lea eax, [esp + 0x24]
00637ce6 movss dword ptr [esp + 0x5c], xmm0
00637cec push eax
00637ced push ebx
00637cee lea eax, [esp + 0x38]
00637cf2 movss dword ptr [esp + 0x30], xmm0
00637cf8 push eax
00637cf9 lea eax, [esp + 0x2c]
00637cfd mov dword ptr [esp + 0x50], 1
00637d05 push eax
00637d06 mov dword ptr [esp + 0x40], 0x14
00637d0e mov dword ptr [esp + 0x30], 5
00637d16 call 0x800fb0
00637d1b mov esi, dword ptr [esp + 0x30]
00637d1f push 0
00637d21 push dword ptr [esp + 0x18]
00637d25 mov ecx, dword ptr [esi + 0x1c3198]
00637d2b call 0x6c4b30
00637d30 mov ebx, eax
00637d32 mov dword ptr [esp + 0x54], ebx
00637d36 test ebx, ebx
00637d38 je 0x637f33
00637d3e call dword ptr [0xa064c0]
00637d44 mov ecx, dword ptr [ebx + 0x320]
00637d4a mov dword ptr [esp + 0x5c], eax
00637d4e lea eax, [ebx + 0x320]
00637d54 mov dword ptr [ebx + 0x34], 0
00637d5b mov dword ptr [ebx + 0x38], 0
00637d62 test ecx, ecx
00637d64 je 0x637d80
00637d66 mov dword ptr [esp + 0x30], eax
00637d6a add ecx, 0x324
00637d70 lea eax, [esp + 0x30]
00637d74 push eax
00637d75 call 0x4bc3c0
00637d7a lea eax, [ebx + 0x320]
00637d80 push dword ptr [esp + 0x10]
00637d84 movss xmm0, dword ptr [esp + 0x50]
00637d8a mov ecx, ebx
00637d8c push dword ptr [esp + 0x3c]
00637d90 mov dword ptr [eax], 0
00637d96 mov eax, dword ptr [edi + 0x294]
00637d9c push dword ptr [esp + 0x2c]
00637da0 mov dword ptr [ebx + 0x294], eax
00637da6 mov eax, dword ptr [edi + 0x298]
00637dac push dword ptr [esp + 0x20]
00637db0 mov dword ptr [ebx + 0x298], eax
00637db6 mov eax, dword ptr [ebx]
00637db8 movss dword ptr [ebx + 0x2b8], xmm0
00637dc0 movss xmm0, dword ptr [esp + 0x60]
00637dc6 movss dword ptr [ebx + 0x2bc], xmm0
00637dce call dword ptr [eax + 4]
00637dd1 mov edx, dword ptr [esi + 0x18190]
00637dd7 push ebx
00637dd8 mov ecx, dword ptr [edx + 0x1214]
00637dde lea eax, [ecx + 1]
00637de1 mov dword ptr [edx + 0x1214], eax
00637de7 mov dword ptr [ebx + 0x20], ecx
00637dea lea ecx, [edx + 0x1218]
00637df0 call 0x413280
00637df5 push ebx
00637df6 call 0x6d94d0
00637dfb test al, al
00637dfd je 0x637e06
00637dff push ecx
00637e00 push ebx
00637e01 call 0x6d9590
00637e06 cmp byte ptr [ebx + 0x16a], 0
00637e0d je 0x637f23
00637e13 mov eax, dword ptr [esi + 0x283c20]
00637e19 cmp eax, dword ptr [esi + 0x283c24]
00637e1f je 0x637f23
00637e25 mov eax, dword ptr [ebx + 0x2c]
00637e28 mov ecx, dword ptr [ebx + 0x28]
00637e2b mov dword ptr [esp + 0x68], eax
00637e2f lea eax, [esp + 0x64]
00637e33 push eax
00637e34 lea eax, [esp + 0x2c]
00637e38 mov dword ptr [esp + 0x68], ecx
00637e3c push eax
00637e3d lea ecx, [esi + 0x283c48]
00637e43 call 0x937c80
00637e48 mov eax, dword ptr [esi + 0x283c48]
00637e4e cmp dword ptr [esp + 0x28], eax
00637e52 jne 0x637e8a
00637e54 mov eax, dword ptr [ebx + 0x28]
00637e57 lea ecx, [esi + 0x283c48]
00637e5d mov dword ptr [esp + 0x40], eax
00637e61 lea eax, [esp + 0x40]
00637e65 push eax
00637e66 lea eax, [esp + 0x70]
00637e6a mov dword ptr [esp + 0x48], 0xffffffff
00637e72 push eax
00637e73 call 0x937c80
00637e78 mov eax, dword ptr [eax]
00637e7a mov dword ptr [esp + 0x28], eax
00637e7e cmp eax, dword ptr [esi + 0x283c48]
00637e84 je 0x637f23
00637e8a mov esi, dword ptr [0xbfd65c]
00637e90 xor ebx, ebx
00637e92 mov eax, dword ptr [esi + 0x1ba54]
00637e98 sub eax, dword ptr [esi + 0x1ba50]
00637e9e sar eax, 2
00637ea1 test eax, eax
00637ea3 je 0x637f23
00637ea9 mov edi, dword ptr [esp + 0x54]
00637ead nop dword ptr [eax]
00637eb0 mov ecx, dword ptr [esi + 0x1ba54]
00637eb6 mov eax, ecx
00637eb8 sub eax, dword ptr [esi + 0x1ba50]
00637ebe test eax, 0xfffffffc
00637ec3 jne 0x637eda
00637ec5 push 0xb3f4d0
00637eca push 3
00637ecc call 0x95e330
00637ed1 mov ecx, dword ptr [esi + 0x1ba54]
00637ed7 add esp, 8
00637eda mov eax, dword ptr [esi + 0x1ba50]
00637ee0 sub ecx, eax
00637ee2 sar ecx, 2
00637ee5 cmp ebx, ecx
00637ee7 jae 0x637eec
00637ee9 lea eax, [eax + ebx*4]
00637eec lea ecx, [esp + 0x18]
00637ef0 push ecx
00637ef1 push dword ptr [esp + 0x5c]
00637ef5 mov ecx, dword ptr [eax]
00637ef7 push edi
00637ef8 push 6
00637efa add ecx, 0x1ec0
00637f00 call 0x935fd0
00637f05 mov esi, dword ptr [0xbfd65c]
00637f0b inc ebx
00637f0c mov eax, dword ptr [esi + 0x1ba54]
00637f12 sub eax, dword ptr [esi + 0x1ba50]
00637f18 sar eax, 2
00637f1b cmp ebx, eax
00637f1d jb 0x637eb0
00637f1f mov edi, dword ptr [esp + 0x3c]
00637f23 call dword ptr [0xa064c0]
00637f29 sub eax, dword ptr [esp + 0x5c]
00637f2d add dword ptr [0xbffe0c], eax
00637f33 sub dword ptr [esp + 0x2c], 1
00637f38 lea ebx, [edi + 0x294]
00637f3e movss xmm1, dword ptr [0xb6a19c]
00637f46 jne 0x637c30
00637f4c mov ebx, dword ptr [esp + 0x60]
00637f50 mov eax, dword ptr [esp + 0x34]
00637f54 neg eax
00637f56 mov ecx, ebx
00637f58 push eax
00637f59 call 0x725740
00637f5e mov ecx, dword ptr [edi + 0x38c]
00637f64 and ecx, 0x80000
00637f6a xor eax, eax
00637f6c or eax, ecx
00637f6e je 0x637fc9
00637f70 mov eax, dword ptr [ebx]
00637f72 lea ecx, [esp + 0x70]
00637f76 push 1
00637f78 push 1
00637f7a push -1
00637f7c xorps xmm0, xmm0
00637f7f mov dword ptr [ebx + 0x364], 0x1e
00637f89 push 0x1e
00637f8b movups xmmword ptr [esp + 0x90], xmm0
00637f93 push ecx
00637f94 movaps xmm0, xmmword ptr [0xb6c370]
00637f9b mov ecx, ebx
00637f9d movups xmmword ptr [esp + 0x84], xmm0
00637fa5 mov dword ptr [esp + 0xa4], 0x3ecccccd
00637fb0 mov dword ptr [esp + 0xa8], 0x3ecccccd
00637fbb mov dword ptr [esp + 0xac], 0x3ecccccd
00637fc6 call dword ptr [eax + 0x38]
00637fc9 cmp byte ptr [edi + 0x16b], 0
00637fd0 mov cl, byte ptr [esp + 0xe]
00637fd4 jne 0x6385aa
00637fda mov cl, 1
00637fdc mov al, cl
00637fde pop edi
00637fdf pop esi
00637fe0 pop ebx
00637fe1 mov ecx, dword ptr [esp + 0x90]
00637fe8 xor ecx, esp
00637fea call 0x9eacd7
00637fef mov esp, ebp
00637ff1 pop ebp
00637ff2 ret 8
00637ff5 push 0
00637ff7 mov ecx, ebx
00637ff9 call 0x684630
00637ffe test al, al
00638000 jne 0x63800b
00638002 cmp dword ptr [ebx + 0x28], 0x362
00638009 jne 0x638068
0063800b mov esi, dword ptr [edi + 0x314]
00638011 test esi, esi
00638013 je 0x63822e
00638019 mov ecx, esi
0063801b call 0x68d5a0
00638020 mov ecx, ebx
00638022 mov esi, eax
00638024 call 0x68d5a0
00638029 cmp esi, eax
0063802b mov esi, dword ptr [edi + 0x314]
00638031 jne 0x63822e
00638037 cmp dword ptr [esi + 0x28], 0x390
0063803e jne 0x6385a6
00638044 cmp dword ptr [esi + 0x2c], 0xa
00638048 jne 0x6385a6
0063804e mov eax, dword ptr [0xbfd65c]
00638053 mov eax, dword ptr [eax + 0x1a30dc]
00638059 sub eax, dword ptr [edi + 0x280]
0063805f cmp eax, 5
00638062 jg 0x63822e
00638068 cmp byte ptr [ebp + 0xc], 0
0063806c mov dl, byte ptr [esp + 0xe]
00638070 mov cl, dl
00638072 jne 0x6385aa
00638078 cmp dword ptr [ebx + 0x28], 3
0063807c jne 0x6385aa
00638082 mov eax, dword ptr [ebx + 0x2c]
00638085 cmp eax, 0x3e
00638088 je 0x63809f
0063808a cmp eax, 0x43
0063808d je 0x63809f
0063808f cmp eax, 0xce
00638094 jne 0x6380ea
00638096 cmp dword ptr [ebx + 0x30], 0x2be
0063809d je 0x6380f8
0063809f mov eax, dword ptr [edi + 0x388]
006380a5 and eax, 0x80000000
006380aa or eax, 0
006380ad jne 0x6385c3
006380b3 mov byte ptr [edi + 0x16b], 1
006380ba mov eax, dword ptr [ebx + 0x2c]
006380bd cmp eax, 0x3e
006380c0 je 0x6380c7
006380c2 cmp eax, 0x43
006380c5 jne 0x638113
006380c7 mov ecx, dword ptr [ebx + 0x360]
006380cd push 0
006380cf push 0xf2
006380d4 call 0x73af30
006380d9 test al, al
006380db je 0x638113
006380dd call 0x6c3d90
006380e2 test al, 1
006380e4 jne 0x638113
006380e6 mov dl, 1
006380e8 jmp 0x638115
006380ea cmp eax, 0xed
006380ef je 0x63809f
006380f1 cmp eax, 0xd3
006380f6 je 0x63809f
006380f8 mov cl, dl
006380fa mov al, cl
006380fc pop edi
006380fd pop esi
006380fe pop ebx
006380ff mov ecx, dword ptr [esp + 0x90]
00638106 xor ecx, esp
00638108 call 0x9eacd7
0063810d mov esp, ebp
0063810f pop ebp
00638110 ret 8
00638113 xor dl, dl
00638115 mov eax, dword ptr [edi + 0x388]
0063811b mov ch, byte ptr [esp + 0xe]
0063811f and eax, 2
00638122 or eax, 0
00638125 mov cl, ch
00638127 jne 0x6385aa
0063812d test dl, dl
0063812f jne 0x6385aa
00638135 mov eax, dword ptr [edi + 0x28]
00638138 movss xmm0, dword ptr [edi + 0x294]
00638140 movss xmm1, dword ptr [edi + 0x298]
00638148 mov ecx, dword ptr [edi + 0x160]
0063814e mov edx, dword ptr [edi + 0x164]
00638154 mov dword ptr [esp + 0x70], eax
00638158 mov eax, dword ptr [edi + 0x2c]
0063815b mov dword ptr [esp + 0x74], eax
0063815f mov eax, dword ptr [edi + 0x34]
00638162 mov dword ptr [esp + 0x78], eax
00638166 mov eax, dword ptr [edi + 0x38]
00638169 mov dword ptr [esp + 0x7c], eax
0063816d mov eax, ecx
0063816f movss dword ptr [esp + 0x80], xmm0
00638178 and eax, 0x100
0063817d or eax, 0
00638180 movss xmm0, dword ptr [edi + 0x2b8]
00638188 movss dword ptr [esp + 0x84], xmm1
00638191 movss xmm1, dword ptr [edi + 0x2bc]
00638199 movss dword ptr [esp + 0x88], xmm0
006381a2 movss dword ptr [esp + 0x8c], xmm1
006381ab je 0x6381b4
006381ad mov esi, 1
006381b2 jmp 0x6381b6
006381b4 xor esi, esi
006381b6 and ecx, 0x20000000
006381bc or ecx, 0
006381bf je 0x6381c8
006381c1 mov ecx, 2
006381c6 jmp 0x6381ca
006381c8 xor ecx, ecx
006381ca and edx, 0x400000
006381d0 xor eax, eax
006381d2 or eax, edx
006381d4 je 0x6381dd
006381d6 mov eax, 4
006381db jmp 0x6381df
006381dd xor eax, eax
006381df movss xmm0, dword ptr [edi + 0x2e0]
006381e7 or eax, ecx
006381e9 push 0x1e
006381eb lea ecx, [esp + 0x74]
006381ef mov dword ptr [esp + 0x98], edi
006381f6 push ecx
006381f7 or eax, esi
006381f9 push 0
006381fb mov dword ptr [esp + 0x9c], eax
00638202 mov eax, dword ptr [ebx]
00638204 push 0
00638206 push ecx
00638207 mov ecx, ebx
00638209 movss dword ptr [esp], xmm0
0063820e call dword ptr [eax + 0x20]
00638211 mov cl, byte ptr [esp + 0xe]
00638215 mov al, cl
00638217 pop edi
00638218 pop esi
00638219 pop ebx
0063821a mov ecx, dword ptr [esp + 0x90]
00638221 xor ecx, esp
00638223 call 0x9eacd7
00638228 mov esp, ebp
0063822a pop ebp
0063822b ret 8
0063822e mov eax, dword ptr [edi + 0x38c]
00638234 mov ecx, dword ptr [edi + 0x388]
0063823a mov dword ptr [esp + 0x44], eax
0063823e mov eax, ecx
00638240 and eax, 0x80000000
00638245 or eax, 0
00638248 je 0x638273
0063824a push 0
0063824c push 0x20000000
00638251 mov ecx, ebx
00638253 call 0x4122f0
00638258 test al, al
0063825a jne 0x6385c3
00638260 cmp dword ptr [ebx + 0x28], 0x362
00638267 je 0x6385c3
0063826d mov ecx, dword ptr [edi + 0x388]
00638273 mov eax, ecx
00638275 and eax, 0x80
0063827a or eax, 0
0063827d jne 0x6382a7
0063827f push 0x100000
00638284 push 0x20000000
00638289 mov ecx, ebx
0063828b call 0x4122f0
00638290 test al, al
00638292 jne 0x6382a1
00638294 cmp dword ptr [ebx + 0x28], 0x362
0063829b jne 0x6385c3
006382a1 mov ecx, dword ptr [edi + 0x388]
006382a7 test esi, esi
006382a9 je 0x638311
006382ab mov eax, dword ptr [esi + 0x28]
006382ae cmp eax, 0x390
006382b3 jne 0x6382ea
006382b5 cmp dword ptr [esi + 0x2c], 0xa
006382b9 jne 0x638311
006382bb cmp dword ptr [ebx + 0x28], eax
006382be jne 0x638311
006382c0 cmp dword ptr [ebx + 0x2c], 0xa
006382c4 jne 0x638311
006382c6 mov cl, byte ptr [esp + 0xe]
006382ca mov byte ptr [edi + 0x16b], 1
006382d1 mov al, cl
006382d3 pop edi
006382d4 pop esi
006382d5 pop ebx
006382d6 mov ecx, dword ptr [esp + 0x90]
006382dd xor ecx, esp
006382df call 0x9eacd7
006382e4 mov esp, ebp
006382e6 pop ebp
006382e7 ret 8
006382ea cmp eax, 0x112
006382ef je 0x6382f8
006382f1 cmp eax, 0x113
006382f6 jne 0x638311
006382f8 mov eax, dword ptr [ebx + 0x28]
006382fb cmp eax, 0x112
00638300 je 0x6385a6
00638306 cmp eax, 0x113
0063830b je 0x6385a6
00638311 and ecx, 2
00638314 mov byte ptr [edi + 0x16b], 1
0063831b or ecx, 0
0063831e jne 0x6385a6
00638324 mov eax, dword ptr [edi + 0x160]
0063832a mov ecx, eax
0063832c mov esi, dword ptr [edi + 0x2c]
0063832f and ecx, 0x100
00638335 mov edx, dword ptr [edi + 0x164]
0063833b cmp esi, 8
0063833e jne 0x6383f5
00638344 or ecx, 0
00638347 mov esi, dword ptr [edi + 0x28]
0063834a movss xmm0, dword ptr [edi + 0x294]
00638352 movss xmm1, dword ptr [edi + 0x298]
0063835a mov dword ptr [esp + 0x70], esi
0063835e mov esi, dword ptr [edi + 0x34]
00638361 movss dword ptr [esp + 0x80], xmm0
0063836a movss xmm0, dword ptr [edi + 0x2b8]
00638372 movss dword ptr [esp + 0x84], xmm1
0063837b movss xmm1, dword ptr [edi + 0x2bc]
00638383 mov dword ptr [esp + 0x78], esi
00638387 mov esi, dword ptr [edi + 0x38]
0063838a mov dword ptr [esp + 0x74], 8
00638392 mov dword ptr [esp + 0x7c], esi
00638396 movss dword ptr [esp + 0x88], xmm0
0063839f movss dword ptr [esp + 0x8c], xmm1
006383a8 je 0x6383b1
006383aa mov esi, 1
006383af jmp 0x6383b3
006383b1 xor esi, esi
006383b3 and eax, 0x20000000
006383b8 or eax, 0
006383bb je 0x6383c4
006383bd mov ecx, 2
006383c2 jmp 0x6383c6
006383c4 xor ecx, ecx
006383c6 and edx, 0x400000
006383cc xor eax, eax
006383ce or eax, edx
006383d0 je 0x6383d9
006383d2 mov eax, 4
006383d7 jmp 0x6383db
006383d9 xor eax, eax
006383db push 0x1e
006383dd or eax, ecx
006383df lea ecx, [esp + 0x74]
006383e3 push ecx
006383e4 push 0
006383e6 push 0
006383e8 push ecx
006383e9 mov dword ptr [esp], 0x420c0000
006383f0 jmp 0x6384af
006383f5 or ecx, 0
006383f8 mov edi, dword ptr [edi + 0x28]
006383fb mov dword ptr [esp + 0x70], edi
006383ff mov edi, dword ptr [esp + 0x3c]
00638403 mov dword ptr [esp + 0x74], esi
00638407 movss xmm0, dword ptr [edi + 0x294]
0063840f movss xmm1, dword ptr [edi + 0x298]
00638417 mov esi, dword ptr [edi + 0x34]
0063841a movss dword ptr [esp + 0x80], xmm0
00638423 movss xmm0, dword ptr [edi + 0x2b8]
0063842b movss dword ptr [esp + 0x84], xmm1
00638434 movss xmm1, dword ptr [edi + 0x2bc]
0063843c mov dword ptr [esp + 0x78], esi
00638440 mov esi, dword ptr [edi + 0x38]
00638443 mov dword ptr [esp + 0x7c], esi
00638447 movss dword ptr [esp + 0x88], xmm0
00638450 movss dword ptr [esp + 0x8c], xmm1
00638459 je 0x638462
0063845b mov esi, 1
00638460 jmp 0x638464
00638462 xor esi, esi
00638464 and eax, 0x20000000
00638469 or eax, 0
0063846c je 0x638475
0063846e mov ecx, 2
00638473 jmp 0x638477
00638475 xor ecx, ecx
00638477 and edx, 0x400000
0063847d xor eax, eax
0063847f or eax, edx
00638481 je 0x63848a
00638483 mov eax, 4
00638488 jmp 0x63848c
0063848a xor eax, eax
0063848c movss xmm0, dword ptr [edi + 0x2e0]
00638494 or eax, ecx
00638496 addss xmm0, dword ptr [0xb6a8f4]
0063849e push 0x1e
006384a0 lea ecx, [esp + 0x74]
006384a4 push ecx
006384a5 push 0
006384a7 push 0
006384a9 push ecx
006384aa movss dword ptr [esp], xmm0
006384af or eax, esi
006384b1 mov dword ptr [esp + 0xa8], edi
006384b8 mov dword ptr [esp + 0xa4], eax
006384bf mov ecx, ebx
006384c1 mov eax, dword ptr [ebx]
006384c3 call dword ptr [eax + 0x20]
006384c6 mov ecx, dword ptr [edi + 0x38c]
006384cc xor eax, eax
006384ce and ecx, 0x80000
006384d4 or eax, ecx
006384d6 je 0x6385a6
006384dc mov eax, dword ptr [edi + 0x28]
006384df movss xmm0, dword ptr [edi + 0x294]
006384e7 movss xmm1, dword ptr [edi + 0x298]
006384ef mov ecx, dword ptr [edi + 0x160]
006384f5 mov edx, dword ptr [edi + 0x164]
006384fb mov dword ptr [esp + 0x70], eax
006384ff mov eax, dword ptr [edi + 0x2c]
00638502 mov dword ptr [esp + 0x74], eax
00638506 mov eax, dword ptr [edi + 0x34]
00638509 mov dword ptr [esp + 0x78], eax
0063850d mov eax, dword ptr [edi + 0x38]
00638510 mov dword ptr [esp + 0x7c], eax
00638514 mov eax, ecx
00638516 movss dword ptr [esp + 0x80], xmm0
0063851f and eax, 0x100
00638524 or eax, 0
00638527 movss xmm0, dword ptr [edi + 0x2b8]
0063852f movss dword ptr [esp + 0x84], xmm1
00638538 movss xmm1, dword ptr [edi + 0x2bc]
00638540 movss dword ptr [esp + 0x88], xmm0
00638549 movss dword ptr [esp + 0x8c], xmm1
00638552 je 0x63855b
00638554 mov esi, 1
00638559 jmp 0x63855d
0063855b xor esi, esi
0063855d and ecx, 0x20000000
00638563 or ecx, 0
00638566 je 0x63856f
00638568 mov ecx, 2
0063856d jmp 0x638571
0063856f xor ecx, ecx
00638571 and edx, 0x400000
00638577 xor eax, eax
00638579 or eax, edx
0063857b je 0x638584
0063857d mov eax, 4
00638582 jmp 0x638586
00638584 xor eax, eax
00638586 or eax, ecx
00638588 mov dword ptr [esp + 0x94], edi
0063858f or eax, esi
00638591 mov ecx, ebx
00638593 mov dword ptr [esp + 0x90], eax
0063859a lea eax, [esp + 0x70]
0063859e push 0x5a
006385a0 push eax
006385a1 call 0x685080
006385a6 mov cl, byte ptr [esp + 0xe]
006385aa mov al, cl
006385ac pop edi
006385ad pop esi
006385ae pop ebx
006385af mov ecx, dword ptr [esp + 0x90]
006385b6 xor ecx, esp
006385b8 call 0x9eacd7
006385bd mov esp, ebp
006385bf pop ebp
006385c0 ret 8
006385c3 mov al, 1
006385c5 mov ecx, dword ptr [esp + 0x9c]
006385cc pop edi
006385cd pop esi
006385ce pop ebx
006385cf xor ecx, esp
006385d1 call 0x9eacd7
006385d6 mov esp, ebp
006385d8 pop ebp
006385d9 ret 8
