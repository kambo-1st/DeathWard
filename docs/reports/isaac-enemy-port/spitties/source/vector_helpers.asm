009624e0 movss dword ptr [ecx], xmm1
009624e4 mov eax, ecx
009624e6 movss dword ptr [ecx + 4], xmm2
009624eb ret 
009624ec int3 
009624ed int3 
009624ee int3 
009624ef int3 
009624f0 push ebp
009624f1 mov ebp, esp
009624f3 sub esp, 8
009624f6 push esi
009624f7 mov esi, ecx
009624f9 movss xmm1, dword ptr [esi]
009624fd movss xmm2, dword ptr [esi + 4]
00962502 movaps xmm0, xmm1
00962505 mulss xmm0, xmm1
00962509 movss dword ptr [ebp - 4], xmm1
0096250e movaps xmm1, xmm2
00962511 mulss xmm1, xmm2
00962515 movss dword ptr [ebp - 8], xmm2
0096251a addss xmm0, xmm1
0096251e call 0x4228c0
00962523 comiss xmm0, dword ptr [0xb6a18c]
0096252a jbe 0x962553
0096252c movss xmm1, dword ptr [0xb6a614]
00962534 divss xmm1, xmm0
00962538 movss xmm0, dword ptr [ebp - 4]
0096253d mulss xmm0, xmm1
00962541 movss dword ptr [esi], xmm0
00962545 movss xmm0, dword ptr [ebp - 8]
0096254a mulss xmm0, xmm1
0096254e movss dword ptr [esi + 4], xmm0
00962553 pop esi
00962554 mov esp, ebp
00962556 pop ebp
00962557 ret 
00962558 int3 
00962559 int3 
0096255a int3 
0096255b int3 
0096255c int3 
0096255d int3 
0096255e int3 
0096255f int3 
00962560 push ebp
00962561 mov ebp, esp
00962563 push ecx
00962564 mov eax, dword ptr [ecx]
00962566 mov ecx, dword ptr [ecx + 4]
00962569 push esi
0096256a mov esi, dword ptr [ebp + 8]
0096256d mov dword ptr [esi], eax
0096256f movss xmm1, dword ptr [esi]
00962573 movaps xmm0, xmm1
00962576 mov dword ptr [esi + 4], ecx
00962579 movss xmm2, dword ptr [esi + 4]
0096257e mulss xmm0, xmm1
00962582 movss dword ptr [ebp + 8], xmm1
00962587 movaps xmm1, xmm2
0096258a mulss xmm1, xmm2
0096258e movss dword ptr [ebp - 4], xmm2
00962593 addss xmm0, xmm1
00962597 call 0x4228c0
0096259c comiss xmm0, dword ptr [0xb6a18c]
009625a3 mov eax, esi
009625a5 jbe 0x9625ce
009625a7 movss xmm1, dword ptr [0xb6a614]
009625af divss xmm1, xmm0
009625b3 movss xmm0, dword ptr [ebp + 8]
009625b8 mulss xmm0, xmm1
009625bc movss dword ptr [esi], xmm0
009625c0 movss xmm0, dword ptr [ebp - 4]
009625c5 mulss xmm0, xmm1
009625c9 movss dword ptr [esi + 4], xmm0
009625ce pop esi
009625cf mov esp, ebp
009625d1 pop ebp
009625d2 ret 4
009625d5 int3 
009625d6 int3 
009625d7 int3 
009625d8 int3 
009625d9 int3 
009625da int3 
009625db int3 
009625dc int3 
009625dd int3 
009625de int3 
009625df int3 
009625e0 movss xmm0, dword ptr [ecx + 4]
009625e5 movss xmm1, dword ptr [ecx]
009625e9 mulss xmm0, dword ptr [edx + 4]
009625ee mulss xmm1, dword ptr [edx]
009625f2 addss xmm0, xmm1
009625f6 ret 
009625f7 int3 
009625f8 int3 
009625f9 int3 
009625fa int3 
009625fb int3 
009625fc int3 
009625fd int3 
009625fe int3 
009625ff int3 
00962600 push ebp
00962601 mov ebp, esp
00962603 mov eax, dword ptr [ebp + 8]
00962606 fld dword ptr [eax + 4]
00962609 fmul dword ptr [ecx + 4]
0096260c fld dword ptr [eax]
0096260e fmul dword ptr [ecx]
00962610 faddp st(1)
00962612 pop ebp
00962613 ret 4
00962616 int3 
00962617 int3 
00962618 int3 
00962619 int3 
0096261a int3 
0096261b int3 
0096261c int3 
0096261d int3 
0096261e int3 
0096261f int3 
00962620 push ebp
00962621 mov ebp, esp
00962623 mov eax, dword ptr [ebp + 8]
00962626 fld dword ptr [eax + 4]
00962629 fmul dword ptr [ecx]
0096262b fld dword ptr [ecx + 4]
0096262e fmul dword ptr [eax]
00962630 fsubp st(1)
00962632 pop ebp
00962633 ret 4
00962636 int3 
00962637 int3 
00962638 int3 
00962639 int3 
0096263a int3 
0096263b int3 
0096263c int3 
0096263d int3 
0096263e int3 
0096263f int3 
00962640 push ebp
00962641 mov ebp, esp
00962643 mov eax, dword ptr [ebp + 8]
00962646 movss xmm0, dword ptr [eax]
0096264a subss xmm0, dword ptr [edx]
0096264e mulss xmm0, xmm3
00962652 addss xmm0, dword ptr [edx]
00962656 movss dword ptr [ecx], xmm0
0096265a movss xmm0, dword ptr [eax + 4]
0096265f mov eax, ecx
00962661 subss xmm0, dword ptr [edx + 4]
00962666 mulss xmm0, xmm3
0096266a addss xmm0, dword ptr [edx + 4]
0096266f movss dword ptr [ecx + 4], xmm0
00962674 pop ebp
00962675 ret 
00962676 int3 
00962677 int3 
00962678 int3 
00962679 int3 
0096267a int3 
0096267b int3 
0096267c int3 
0096267d int3 
0096267e int3 
0096267f int3 
00962680 push ebp
00962681 mov ebp, esp
00962683 mov eax, dword ptr [ebp + 8]
00962686 movss xmm4, dword ptr [eax + 4]
0096268b movss xmm0, dword ptr [eax]
0096268f subss xmm0, dword ptr [ecx]
00962693 subss xmm4, dword ptr [ecx + 4]
00962698 mulss xmm0, dword ptr [ebp + 0xc]
0096269d mulss xmm4, dword ptr [ebp + 0xc]
009626a2 addss xmm0, dword ptr [ecx]
009626a6 addss xmm4, dword ptr [ecx + 4]
009626ab movss dword ptr [ecx], xmm0
009626af movss dword ptr [ecx + 4], xmm4
009626b4 pop ebp
009626b5 ret 8
009626b8 int3 
009626b9 int3 
009626ba int3 
009626bb int3 
009626bc int3 
009626bd int3 
009626be int3 
009626bf int3 
009626c0 push ecx
009626c1 movss xmm1, dword ptr [ecx]
009626c5 movss xmm0, dword ptr [ecx + 4]
009626ca subss xmm0, dword ptr [edx + 4]
009626cf subss xmm1, dword ptr [edx]
009626d3 mulss xmm0, xmm0
009626d7 mulss xmm1, xmm1
009626db addss xmm0, xmm1
009626df call 0x4228c0
009626e4 pop ecx
009626e5 ret 
009626e6 int3 
009626e7 int3 
009626e8 int3 
009626e9 int3 
009626ea int3 
009626eb int3 
009626ec int3 
009626ed int3 
009626ee int3 
009626ef int3 
009626f0 push ebp
009626f1 mov ebp, esp
009626f3 push ecx
009626f4 mov eax, dword ptr [ebp + 8]
009626f7 movss xmm1, dword ptr [ecx]
009626fb movss xmm0, dword ptr [ecx + 4]
00962700 subss xmm0, dword ptr [eax + 4]
00962705 subss xmm1, dword ptr [eax]
00962709 mulss xmm0, xmm0
0096270d mulss xmm1, xmm1
00962711 addss xmm0, xmm1
00962715 call 0x4228c0
0096271a movss dword ptr [ebp + 8], xmm0
0096271f fld dword ptr [ebp + 8]
00962722 pop ecx
00962723 pop ebp
00962724 ret 4
00962727 int3 
00962728 int3 
00962729 int3 
0096272a int3 
0096272b int3 
0096272c int3 
0096272d int3 
0096272e int3 
0096272f int3 
00962730 movss xmm1, dword ptr [ecx]
00962734 movss xmm0, dword ptr [ecx + 4]
00962739 subss xmm0, dword ptr [edx + 4]
0096273e subss xmm1, dword ptr [edx]
00962742 mulss xmm0, xmm0
00962746 mulss xmm1, xmm1
0096274a addss xmm0, xmm1
0096274e ret 
0096274f int3 
00962750 push ebp
00962751 mov ebp, esp
00962753 mov eax, dword ptr [ebp + 8]
00962756 movss xmm1, dword ptr [ecx]
0096275a movss xmm0, dword ptr [ecx + 4]
0096275f subss xmm0, dword ptr [eax + 4]
00962764 subss xmm1, dword ptr [eax]
00962768 mulss xmm0, xmm0
0096276c mulss xmm1, xmm1
00962770 addss xmm0, xmm1
00962774 movss dword ptr [ebp + 8], xmm0
00962779 fld dword ptr [ebp + 8]
0096277c pop ebp
0096277d ret 4
00962780 push ebp
00962781 mov ebp, esp
00962783 push ecx
00962784 movss xmm0, dword ptr [ebp + 0xc]
00962789 mulss xmm0, dword ptr [0xb6a230]
00962791 push esi
00962792 mov esi, ecx
00962794 movss dword ptr [ebp + 0xc], xmm0
00962799 call 0x411fe0
0096279e movss dword ptr [ebp - 4], xmm0
009627a3 movss xmm0, dword ptr [ebp + 0xc]
009627a8 call 0x412010
009627ad movss xmm4, dword ptr [esi]
009627b1 movss xmm3, dword ptr [esi + 4]
009627b6 movaps xmm2, xmm4
009627b9 mulss xmm2, dword ptr [ebp - 4]
009627be movaps xmm1, xmm3
009627c1 mov eax, dword ptr [ebp + 8]
009627c4 mulss xmm3, dword ptr [ebp - 4]
009627c9 pop esi
009627ca mulss xmm1, xmm0
009627ce mulss xmm4, xmm0
009627d2 subss xmm2, xmm1
009627d6 addss xmm3, xmm4
009627da movss dword ptr [eax], xmm2
009627de movss dword ptr [eax + 4], xmm3
009627e3 mov esp, ebp
009627e5 pop ebp
009627e6 ret 8
009627e9 int3 
009627ea int3 
009627eb int3 
009627ec int3 
009627ed int3 
009627ee int3 
009627ef int3 
009627f0 push ebp
009627f1 mov ebp, esp
009627f3 push ecx
009627f4 movss xmm0, dword ptr [ebp + 0xc]
009627f9 mulss xmm0, dword ptr [0xb6a230]
00962801 push esi
00962802 movss dword ptr [ebp + 0xc], xmm0
00962807 call 0x411fe0
0096280c mov esi, dword ptr [ebp + 8]
0096280f movss dword ptr [esi], xmm0
00962813 movss xmm0, dword ptr [ebp + 0xc]
00962818 call 0x412010
0096281d movss dword ptr [esi + 4], xmm0
00962822 mov eax, esi
00962824 pop esi
00962825 pop ecx
00962826 pop ebp
00962827 ret 
00962828 int3 
00962829 int3 
0096282a int3 
0096282b int3 
0096282c int3 
0096282d int3 
0096282e int3 
0096282f int3 
00962830 push ebp
00962831 mov ebp, esp
00962833 sub esp, 8
00962836 movss xmm1, dword ptr [ecx]
0096283a movss xmm0, dword ptr [ecx + 4]
0096283f call 0x447a80
00962844 mulss xmm0, dword ptr [0xb6aa84]
0096284c movss dword ptr [ebp - 4], xmm0
00962851 fld dword ptr [ebp - 4]
00962854 mov esp, ebp
00962856 pop ebp
00962857 ret 
00962858 int3 
00962859 int3 
0096285a int3 
0096285b int3 
0096285c int3 
0096285d int3 
0096285e int3 
0096285f int3 
00962860 push ebp
00962861 mov ebp, esp
00962863 sub esp, 8
00962866 push esi
00962867 mov esi, ecx
00962869 movss xmm1, dword ptr [esi]
0096286d movss xmm2, dword ptr [esi + 4]
00962872 movaps xmm0, xmm1
00962875 mulss xmm0, xmm1
00962879 movss dword ptr [ebp - 4], xmm1
0096287e movaps xmm1, xmm2
00962881 mulss xmm1, xmm2
00962885 movss dword ptr [ebp - 8], xmm2
0096288a addss xmm0, xmm1
0096288e call 0x4228c0
00962893 comiss xmm0, dword ptr [0xb6a18c]
0096289a jbe 0x9628c0
0096289c movss xmm1, dword ptr [ebp + 8]
009628a1 divss xmm1, xmm0
009628a5 movss xmm0, dword ptr [ebp - 4]
009628aa mulss xmm0, xmm1
009628ae movss dword ptr [esi], xmm0
009628b2 movss xmm0, dword ptr [ebp - 8]
009628b7 mulss xmm0, xmm1
009628bb movss dword ptr [esi + 4], xmm0
009628c0 pop esi
009628c1 mov esp, ebp
009628c3 pop ebp
009628c4 ret 4
009628c7 int3 
009628c8 int3 
009628c9 int3 
009628ca int3 
009628cb int3 
009628cc int3 
009628cd int3 
009628ce int3 
009628cf int3 
009628d0 push ebp
009628d1 mov ebp, esp
009628d3 push esi
009628d4 mov esi, ecx
009628d6 movss xmm1, dword ptr [esi + 4]
009628db movss xmm0, dword ptr [esi]
009628df mulss xmm0, xmm0
009628e3 mulss xmm1, xmm1
009628e7 addss xmm0, xmm1
009628eb call 0x4228c0
009628f0 comiss xmm0, dword ptr [0xb6a18c]
009628f7 mov eax, dword ptr [ebp + 8]
009628fa jbe 0x962924
009628fc movss xmm1, dword ptr [ebp + 0xc]
00962901 divss xmm1, xmm0
00962905 movss xmm0, dword ptr [esi]
00962909 mulss xmm0, xmm1
0096290d movss dword ptr [eax], xmm0
00962911 movss xmm0, dword ptr [esi + 4]
00962916 mulss xmm0, xmm1
0096291a pop esi
0096291b movss dword ptr [eax + 4], xmm0
00962920 pop ebp
00962921 ret 8
00962924 mov ecx, dword ptr [esi]
00962926 mov edx, dword ptr [esi + 4]
00962929 mov dword ptr [eax], ecx
0096292b mov dword ptr [eax + 4], edx
0096292e pop esi
0096292f pop ebp
00962930 ret 8
00962933 int3 
00962934 int3 
00962935 int3 
00962936 int3 
00962937 int3 
00962938 int3 
00962939 int3 
0096293a int3 
0096293b int3 
0096293c int3 
0096293d int3 
0096293e int3 
0096293f int3 
00962940 push ebp
00962941 mov ebp, esp
00962943 movss xmm0, dword ptr [ebp + 0x10]
00962948 lea eax, [ebp + 0x10]
0096294b comiss xmm0, dword ptr [ecx]
0096294e movss xmm0, dword ptr [ebp + 8]
00962953 cmova eax, ecx
00962956 movss xmm1, dword ptr [eax]
0096295a comiss xmm1, xmm0
0096295d ja 0x962965
0096295f movss xmm0, xmm0
00962963 jmp 0x962969
00962965 movss xmm0, xmm1
00962969 lea edx, [ecx + 4]
0096296c lea eax, [ebp + 0xc]
0096296f movss dword ptr [ecx], xmm0
00962973 lea ecx, [ebp + 0x14]
00962976 movss xmm0, dword ptr [ebp + 0x14]
0096297b comiss xmm0, dword ptr [edx]
0096297e cmova ecx, edx
00962981 movss xmm0, dword ptr [ecx]
00962985 comiss xmm0, dword ptr [ebp + 0xc]
00962989 cmova eax, ecx
0096298c mov eax, dword ptr [eax]
0096298e mov dword ptr [edx], eax
00962990 pop ebp
00962991 ret 0x10
00962994 int3 
00962995 int3 
00962996 int3 
00962997 int3 
00962998 int3 
00962999 int3 
0096299a int3 
0096299b int3 
0096299c int3 
0096299d int3 
0096299e int3 
0096299f int3 
009629a0 push ebp
009629a1 mov ebp, esp
009629a3 movss xmm0, dword ptr [ebp + 0x18]
009629a8 lea eax, [ecx + 4]
009629ab comiss xmm0, dword ptr [eax]
009629ae lea edx, [ebp + 0x18]
009629b1 movss xmm0, dword ptr [ebp + 0x14]
009629b6 cmova edx, eax
009629b9 lea eax, [ebp + 0x14]
009629bc comiss xmm0, dword ptr [ecx]
009629bf movss xmm0, dword ptr [ebp + 0xc]
009629c4 cmova eax, ecx
009629c7 movss xmm1, dword ptr [eax]
009629cb comiss xmm1, xmm0
009629ce ja 0x9629d6
009629d0 movss xmm0, xmm0
009629d4 jmp 0x9629da
009629d6 movss xmm0, xmm1
009629da mov eax, dword ptr [ebp + 8]
009629dd lea ecx, [ebp + 0x10]
009629e0 movss dword ptr [eax], xmm0
009629e4 movss xmm0, dword ptr [edx]
009629e8 comiss xmm0, dword ptr [ebp + 0x10]
009629ec cmova ecx, edx
009629ef mov ecx, dword ptr [ecx]
009629f1 mov dword ptr [eax + 4], ecx
009629f4 pop ebp
009629f5 ret 0x14
009629f8 int3 
009629f9 int3 
009629fa int3 
009629fb int3 
009629fc int3 
009629fd int3 
009629fe int3 
009629ff int3 
00962a00 push ebp
00962a01 mov ebp, esp
00962a03 sub esp, 8
00962a06 movss xmm1, dword ptr [ecx + 4]
00962a0b movss xmm0, dword ptr [ecx]
00962a0f mulss xmm0, xmm0
00962a13 mulss xmm1, xmm1
00962a17 addss xmm0, xmm1
00962a1b call 0x4228c0
00962a20 movss dword ptr [ebp - 4], xmm0
00962a25 fld dword ptr [ebp - 4]
00962a28 mov esp, ebp
00962a2a pop ebp
00962a2b ret 
00962a2c int3 
00962a2d int3 
00962a2e int3 
00962a2f int3 
00962a30 push ebp
00962a31 mov ebp, esp
00962a33 push ecx
00962a34 movss xmm1, dword ptr [ecx + 4]
00962a39 movss xmm0, dword ptr [ecx]
00962a3d mulss xmm0, xmm0
00962a41 mulss xmm1, xmm1
00962a45 addss xmm0, xmm1
00962a49 movss dword ptr [ebp - 4], xmm0
00962a4e fld dword ptr [ebp - 4]
00962a51 mov esp, ebp
00962a53 pop ebp
00962a54 ret 
00962a55 int3 
00962a56 int3 
00962a57 int3 
00962a58 int3 
00962a59 int3 
00962a5a int3 
00962a5b int3 
00962a5c int3 
00962a5d int3 
00962a5e int3 
00962a5f int3 
00962a60 push ebp
00962a61 mov ebp, esp
00962a63 mov edx, dword ptr [ebp + 0xc]
00962a66 mov eax, dword ptr [ebp + 8]
00962a69 movss xmm0, dword ptr [edx]
00962a6d addss xmm0, dword ptr [ecx]
00962a71 movss dword ptr [eax], xmm0
00962a75 movss xmm0, dword ptr [edx + 4]
00962a7a addss xmm0, dword ptr [ecx + 4]
00962a7f movss dword ptr [eax + 4], xmm0
00962a84 pop ebp
00962a85 ret 8
00962a88 int3 
00962a89 int3 
00962a8a int3 
00962a8b int3 
00962a8c int3 
00962a8d int3 
00962a8e int3 
00962a8f int3 
00962a90 push ebp
00962a91 mov ebp, esp
00962a93 mov eax, dword ptr [ebp + 8]
00962a96 movss xmm0, dword ptr [eax]
00962a9a addss xmm0, dword ptr [ecx]
00962a9e movss dword ptr [ecx], xmm0
00962aa2 movss xmm0, dword ptr [eax + 4]
00962aa7 mov eax, ecx
00962aa9 addss xmm0, dword ptr [ecx + 4]
00962aae movss dword ptr [ecx + 4], xmm0
00962ab3 pop ebp
00962ab4 ret 4
00962ab7 int3 
00962ab8 int3 
00962ab9 int3 
00962aba int3 
00962abb int3 
00962abc int3 
00962abd int3 
00962abe int3 
00962abf int3 
00962ac0 push ebp
00962ac1 mov ebp, esp
00962ac3 mov edx, dword ptr [ebp + 0xc]
00962ac6 movss xmm0, dword ptr [ecx]
00962aca mov eax, dword ptr [ebp + 8]
00962acd subss xmm0, dword ptr [edx]
00962ad1 movss dword ptr [eax], xmm0
00962ad5 movss xmm0, dword ptr [ecx + 4]
00962ada subss xmm0, dword ptr [edx + 4]
00962adf movss dword ptr [eax + 4], xmm0
00962ae4 pop ebp
00962ae5 ret 8
00962ae8 int3 
00962ae9 int3 
00962aea int3 
00962aeb int3 
00962aec int3 
00962aed int3 
00962aee int3 
00962aef int3 
00962af0 push ebp
00962af1 mov ebp, esp
00962af3 mov eax, dword ptr [ebp + 8]
00962af6 movss xmm0, dword ptr [ecx]
00962afa subss xmm0, dword ptr [eax]
00962afe movss dword ptr [ecx], xmm0
00962b02 movss xmm0, dword ptr [ecx + 4]
00962b07 subss xmm0, dword ptr [eax + 4]
00962b0c mov eax, ecx
00962b0e movss dword ptr [ecx + 4], xmm0
00962b13 pop ebp
00962b14 ret 4
00962b17 int3 
00962b18 int3 
00962b19 int3 
00962b1a int3 
00962b1b int3 
00962b1c int3 
00962b1d int3 
00962b1e int3 
00962b1f int3 
00962b20 push ebp
00962b21 mov ebp, esp
00962b23 mov eax, dword ptr [ebp + 8]
00962b26 movss xmm0, dword ptr [ecx]
00962b2a xorps xmm0, xmmword ptr [0xb6c9b0]
00962b31 movss dword ptr [eax], xmm0
00962b35 movss xmm0, dword ptr [ecx + 4]
00962b3a xorps xmm0, xmmword ptr [0xb6c9b0]
00962b41 movss dword ptr [eax + 4], xmm0
00962b46 pop ebp
00962b47 ret 4
00962b4a int3 
00962b4b int3 
00962b4c int3 
00962b4d int3 
00962b4e int3 
00962b4f int3 
00962b50 push ebp
00962b51 mov ebp, esp
00962b53 mov eax, dword ptr [ebp + 0xc]
00962b56 movss xmm1, dword ptr [eax]
00962b5a mov eax, dword ptr [ebp + 8]
00962b5d movaps xmm0, xmm1
00962b60 mulss xmm0, dword ptr [ecx]
00962b64 mulss xmm1, dword ptr [ecx + 4]
00962b69 movss dword ptr [eax], xmm0
00962b6d movss dword ptr [eax + 4], xmm1
00962b72 pop ebp
00962b73 ret 8
00962b76 int3 
00962b77 int3 
00962b78 int3 
00962b79 int3 
00962b7a int3 
00962b7b int3 
00962b7c int3 
00962b7d int3 
00962b7e int3 
00962b7f int3 
00962b80 push ebp
00962b81 mov ebp, esp
00962b83 mov edx, dword ptr [ebp + 0xc]
00962b86 mov eax, dword ptr [ebp + 8]
00962b89 movss xmm0, dword ptr [edx]
00962b8d mulss xmm0, dword ptr [ecx]
00962b91 movss dword ptr [eax], xmm0
00962b95 movss xmm0, dword ptr [edx + 4]
00962b9a mulss xmm0, dword ptr [ecx + 4]
00962b9f movss dword ptr [eax + 4], xmm0
00962ba4 pop ebp
00962ba5 ret 8
00962ba8 int3 
00962ba9 int3 
00962baa int3 
00962bab int3 
00962bac int3 
00962bad int3 
00962bae int3 
00962baf int3 
00962bb0 push ebp
00962bb1 mov ebp, esp
00962bb3 mov eax, dword ptr [ebp + 8]
00962bb6 movss xmm0, dword ptr [eax]
00962bba mulss xmm0, dword ptr [ecx]
00962bbe movss dword ptr [ecx], xmm0
00962bc2 movss xmm0, dword ptr [ecx + 4]
00962bc7 mulss xmm0, dword ptr [eax]
00962bcb mov eax, ecx
00962bcd movss dword ptr [ecx + 4], xmm0
00962bd2 pop ebp
00962bd3 ret 4
00962bd6 int3 
00962bd7 int3 
00962bd8 int3 
00962bd9 int3 
00962bda int3 
00962bdb int3 
00962bdc int3 
00962bdd int3 
00962bde int3 
00962bdf int3 
00962be0 push ebp
00962be1 mov ebp, esp
00962be3 mov eax, dword ptr [ebp + 8]
00962be6 movss xmm0, dword ptr [eax]
00962bea mulss xmm0, dword ptr [ecx]
00962bee movss dword ptr [ecx], xmm0
00962bf2 movss xmm0, dword ptr [eax + 4]
00962bf7 mov eax, ecx
00962bf9 mulss xmm0, dword ptr [ecx + 4]
00962bfe movss dword ptr [ecx + 4], xmm0
00962c03 pop ebp
00962c04 ret 4
00962c07 int3 
00962c08 int3 
00962c09 int3 
00962c0a int3 
00962c0b int3 
00962c0c int3 
00962c0d int3 
00962c0e int3 
00962c0f int3 
00962c10 push ebp
00962c11 mov ebp, esp
00962c13 mov eax, dword ptr [ebp + 0xc]
00962c16 movss xmm0, dword ptr [ecx]
00962c1a movss xmm1, dword ptr [eax]
00962c1e mov eax, dword ptr [ebp + 8]
00962c21 divss xmm0, xmm1
00962c25 movss dword ptr [eax], xmm0
00962c29 movss xmm0, dword ptr [ecx + 4]
00962c2e divss xmm0, xmm1
00962c32 movss dword ptr [eax + 4], xmm0
00962c37 pop ebp
00962c38 ret 8
00962c3b int3 
00962c3c int3 
00962c3d int3 
00962c3e int3 
00962c3f int3 
00962c40 push ebp
00962c41 mov ebp, esp
00962c43 mov eax, dword ptr [ebp + 8]
00962c46 movss xmm0, dword ptr [ecx]
00962c4a divss xmm0, dword ptr [eax]
00962c4e movss dword ptr [ecx], xmm0
00962c52 movss xmm0, dword ptr [ecx + 4]
00962c57 divss xmm0, dword ptr [eax]
00962c5b mov eax, ecx
00962c5d movss dword ptr [ecx + 4], xmm0
00962c62 pop ebp
00962c63 ret 4
00962c66 int3 
00962c67 int3 
00962c68 int3 
00962c69 int3 
00962c6a int3 
00962c6b int3 
00962c6c int3 
00962c6d int3 
00962c6e int3 
00962c6f int3 
00962c70 push ebp
00962c71 mov ebp, esp
00962c73 mov edx, dword ptr [ebp + 8]
00962c76 movss xmm0, dword ptr [ecx]
00962c7a ucomiss xmm0, dword ptr [edx]
00962c7d lahf 
00962c7e test ah, 0x44
00962c81 jp 0x962c98
00962c83 movss xmm0, dword ptr [ecx + 4]
00962c88 ucomiss xmm0, dword ptr [edx + 4]
00962c8c lahf 
00962c8d test ah, 0x44
00962c90 jp 0x962c98
00962c92 mov al, 1
00962c94 pop ebp
00962c95 ret 4
00962c98 xor al, al
00962c9a pop ebp
00962c9b ret 4
00962c9e int3 
00962c9f int3 
00962ca0 push ebp
00962ca1 mov ebp, esp
00962ca3 mov edx, dword ptr [ebp + 8]
00962ca6 movss xmm0, dword ptr [ecx]
00962caa ucomiss xmm0, dword ptr [edx]
00962cad lahf 
00962cae test ah, 0x44
00962cb1 jp 0x962cc8
00962cb3 movss xmm0, dword ptr [ecx + 4]
00962cb8 ucomiss xmm0, dword ptr [edx + 4]
00962cbc lahf 
00962cbd test ah, 0x44
00962cc0 jp 0x962cc8
00962cc2 xor al, al
00962cc4 pop ebp
00962cc5 ret 4
00962cc8 mov al, 1
00962cca pop ebp
00962ccb ret 4
00962cce int3 
00962ccf int3 
00962cd0 push ebp
00962cd1 mov ebp, esp
00962cd3 mov edx, dword ptr [ebp + 8]
00962cd6 mov eax, dword ptr [edx]
00962cd8 mov dword ptr [ecx], eax
00962cda mov eax, dword ptr [edx + 4]
00962cdd mov dword ptr [ecx + 4], eax
00962ce0 mov eax, ecx
00962ce2 pop ebp
00962ce3 ret 4
00962ce6 int3 
00962ce7 int3 
00962ce8 int3 
00962ce9 int3 
00962cea int3 
00962ceb int3 
00962cec int3 
00962ced int3 
00962cee int3 
00962cef int3 
