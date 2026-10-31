006348ac and edx, 1
006348af or edx, 0
006348b2 je 0x634b5c
006348b8 push 0
006348ba push 3
006348bc mov ecx, edi
006348be call 0x684790
006348c3 test al, al
006348c5 je 0x6348d0
006348c7 push 0
006348c9 mov ecx, edi
006348cb call 0x681960
006348d0 mov ecx, dword ptr [edi + 0x31c]
006348d6 test ecx, ecx
006348d8 jne 0x634964
006348de mov ecx, dword ptr [edi + 0x320]
006348e4 test ecx, ecx
006348e6 je 0x6348f8
006348e8 push 0
006348ea push 0x100
006348ef call 0x4122f0
006348f4 test al, al
006348f6 jne 0x63492c
006348f8 mov eax, dword ptr [edi + 0x388]
006348fe and eax, 0x80000000
00634903 or eax, 0
00634906 jne 0x63492c
00634908 mov edx, dword ptr [edi + 0x320]
0063490e lea esi, [edi + 0x294]
00634914 movss xmm1, dword ptr [0xb6ac8c]
0063491c mov ecx, esi
0063491e push eax
0063491f push 1
00634921 push eax
00634922 call 0x6d8820
00634927 add esp, 0xc
0063492a jmp 0x63494c
0063492c mov edx, dword ptr [edi + 0x320]
00634932 lea esi, [edi + 0x294]
00634938 movss xmm1, dword ptr [0xb6ac8c]
00634940 mov ecx, esi
00634942 push 0
00634944 call 0x6d90b0
00634949 add esp, 4
0063494c push eax
0063494d mov ecx, edi
0063494f call 0x681960
00634954 mov ecx, dword ptr [edi + 0x31c]
0063495a test ecx, ecx
0063495c je 0x634ab9
00634962 jmp 0x63496a
00634964 lea esi, [edi + 0x294]
0063496a lea eax, [ebp - 0x380]
00634970 push eax
00634971 call 0x412130
00634976 mov ecx, dword ptr [edi + 0x31c]
0063497c lea eax, [ebp - 0x360]
00634982 push eax
00634983 call 0x412170
00634988 push esi
00634989 lea eax, [ebp - 0x358]
0063498f mov dword ptr [ebp - 0x378], 0x3f000000
00634999 push eax
0063499a lea eax, [ebp - 0x378]
006349a0 push eax
006349a1 lea eax, [ebp - 0x450]
006349a7 push eax
006349a8 lea ecx, [ebp - 0x360]
006349ae call 0x962b50
006349b3 push eax
006349b4 lea eax, [ebp - 0x498]
006349ba push eax
006349bb lea ecx, [ebp - 0x380]
006349c1 call 0x962a60
006349c6 mov ecx, eax
006349c8 call 0x962ac0
006349cd lea ecx, [ebp - 0x358]
006349d3 call 0x962a00
006349d8 movss xmm0, dword ptr [0xb6aafc]
006349e0 fstp dword ptr [ebp - 0x378]
006349e6 comiss xmm0, dword ptr [ebp - 0x378]
006349ed jbe 0x634ab9
006349f3 push esi
006349f4 lea eax, [ebp - 0x450]
006349fa push eax
006349fb lea ecx, [ebp - 0x380]
00634a01 call 0x962ac0
00634a06 push eax
00634a07 lea ecx, [ebp - 0x358]
00634a0d call 0x962cd0
00634a12 lea eax, [edi + 0x2f4]
00634a18 mov dword ptr [ebp - 0x378], 0x3fb33333
00634a22 push eax
00634a23 lea eax, [ebp - 0x450]
00634a29 push eax
00634a2a lea esi, [edi + 0x374]
00634a30 push esi
00634a31 lea eax, [ebp - 0x498]
00634a37 push eax
00634a38 lea eax, [ebp - 0x378]
00634a3e push eax
00634a3f lea eax, [ebp - 0x4c0]
00634a45 push eax
00634a46 lea eax, [ebp - 0x4b8]
00634a4c push eax
00634a4d lea ecx, [ebp - 0x358]
00634a53 call 0x962560
00634a58 mov ecx, eax
00634a5a call 0x962b50
00634a5f mov ecx, eax
00634a61 call 0x962b50
00634a66 mov ecx, eax
00634a68 call 0x962b50
00634a6d push eax
00634a6e lea ecx, [edi + 0x2b8]
00634a74 call 0x962a90
00634a79 movss xmm2, dword ptr [esi]
00634a7d movss xmm1, dword ptr [0xb6a5b8]
00634a85 movss xmm0, dword ptr [0xb6a614]
00634a8d call 0x962380
00634a92 movss xmm1, dword ptr [edi + 0x2f4]
00634a9a call 0x65c960
00634a9f lea eax, [ebp - 0x378]
00634aa5 movss dword ptr [ebp - 0x378], xmm0
00634aad push eax
00634aae lea ecx, [edi + 0x2b8]
00634ab4 call 0x962bb0
