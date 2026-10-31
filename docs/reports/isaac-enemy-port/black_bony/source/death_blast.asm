0052680e cmp eax, 0x115
00526813 jne 0x526887
00526815 movups xmm0, xmmword ptr [0xbfec58]
0052681c mov ecx, dword ptr [0xbfd65c]
00526822 lea esi, [edi + 0x294]
00526828 push 0
0052682a push 0
0052682c push 4
0052682e sub esp, 0x10
00526831 mov eax, esp
00526833 push edi
00526834 push 1
00526836 sub esp, 8
00526839 movups xmmword ptr [eax], xmm0
0052683c mov dword ptr [esp + 4], 0x42700000
00526844 mov dword ptr [esp], 0x42200000
0052684b push esi
0052684c call 0x6d1750
00526851 movss xmm2, dword ptr [0xb6a614]
00526859 mov ecx, dword ptr [0xbfd65c]
0052685f push esi
00526860 call 0x6d5600
00526865 call 0x6c3d90
0052686a mov ecx, dword ptr [0xbfd65c]
00526870 push eax
00526871 push 0
00526873 push 0
00526875 push 0xc02fec
0052687a push esi
0052687b push 1
0052687d push 0x3e8
00526882 call 0x422e20
