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
