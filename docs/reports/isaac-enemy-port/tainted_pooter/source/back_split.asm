0063371e mov esi, dword ptr [edi + 0x388]
00633724 mov edx, dword ptr [edi + 0x38c]
0063372a mov ecx, edx
0063372c mov dword ptr [ebp - 0x3cc], esi
00633732 and ecx, 0x400000
00633738 xor eax, eax
0063373a or eax, ecx
0063373c je 0x633859
00633742 lea eax, [ebp - 0x3ec]
00633748 push eax
00633749 lea eax, [ebp - 0x32c]
0063374f push eax
00633750 lea ecx, [edi + 0x2b8]
00633756 call 0x962560
0063375b mov ecx, eax
0063375d call 0x962b20
00633762 or eax, 0xffffffff
00633765 lea esi, [edi + 0x294]
0063376b mov dword ptr [ebp - 0x324], eax
00633771 movd xmm0, eax
00633775 lea ecx, [ebp - 0x340]
0063377b cvtdq2ps xmm0, xmm0
0063377e push ecx
0063377f lea ecx, [ebp - 0x3dc]
00633785 mov dword ptr [ebp - 0x340], 0x41200000
0063378f push ecx
00633790 push ecx
00633791 lea eax, [ebp - 0x370]
00633797 mulss xmm0, dword ptr [0xb6a9e8]
0063379f lea ecx, [ebp - 0x3ec]
006337a5 movss dword ptr [esp], xmm0
006337aa push eax
006337ab call 0x962780
006337b0 mov ecx, eax
006337b2 call 0x962b50
006337b7 call 0x6c3d90
006337bc push eax
006337bd push 0
006337bf push dword ptr [edi + 0x320]
006337c5 lea eax, [ebp - 0x3dc]
006337cb mov ecx, esi
006337cd push eax
006337ce push eax
006337cf lea eax, [ebp - 0x3cc]
006337d5 push eax
006337d6 call 0x962a60
006337db mov ecx, dword ptr [0xbfd65c]
006337e1 push eax
006337e2 push 0
006337e4 push 9
006337e6 call 0x422e20
006337eb push dword ptr [edi + 0x34]
006337ee mov esi, eax
006337f0 mov ecx, esi
006337f2 call 0x4424b0
006337f7 push dword ptr [edi + 0x38]
006337fa mov ecx, esi
006337fc call 0x4a3f60
00633801 push ecx
00633802 mov ecx, esi
00633804 mov dword ptr [esp], 0xbd23d70a
0063380b call 0x436b90
00633810 mov eax, dword ptr [edi + 0x38c]
00633816 mov ecx, esi
00633818 and eax, 0xffbfffff
0063381d push eax
0063381e push dword ptr [edi + 0x388]
00633824 call 0x4395a0
00633829 mov eax, dword ptr [ebp - 0x324]
0063382f lea esi, [edi + 0x294]
00633835 add eax, 2
00633838 mov dword ptr [ebp - 0x324], eax
0063383e cmp eax, 1
00633841 jle 0x633771
00633847 mov eax, dword ptr [edi + 0x388]
0063384d mov edx, dword ptr [edi + 0x38c]
00633853 mov dword ptr [ebp - 0x3cc], eax
