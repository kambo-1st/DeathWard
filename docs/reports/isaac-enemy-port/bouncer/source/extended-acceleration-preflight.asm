00635e4f mov ecx, dword ptr [edi + 0x388]
00635e55 mov eax, ecx
00635e57 mov edx, dword ptr [edi + 0x38c]
00635e5d and eax, 0x10000000
00635e62 or eax, 0
00635e65 je 0x635ea6
00635e67 movss xmm0, dword ptr [0xb6a614]
00635e6f divss xmm0, dword ptr [edi + 0x37c]
00635e77 movss xmm1, dword ptr [edi + 0x2f4]
00635e7f call 0x65c960
00635e84 lea eax, [ebp - 0x470]
00635e8a movss dword ptr [ebp - 0x470], xmm0
00635e92 push eax
00635e93 mov ecx, esi
00635e95 call 0x962bb0
00635e9a mov ecx, dword ptr [edi + 0x388]
00635ea0 mov edx, dword ptr [edi + 0x38c]
00635ea6 mov dword ptr [ebp - 0x35c], edx
00635eac xor eax, eax
00635eae and edx, 0x20
00635eb1 or eax, edx
00635eb3 je 0x635f3a
00635eb9 movss xmm0, dword ptr [edi + 0x2fc]
00635ec1 lea edx, [ebp - 0x30c]
00635ec7 divss xmm0, dword ptr [0xb6a9c8]
00635ecf lea ecx, [ebp - 0x310]
00635ed5 mov dword ptr [ebp - 0x310], 0x3f800000
00635edf movss dword ptr [ebp - 0x30c], xmm0
00635ee7 call 0x407e80
00635eec movss xmm1, dword ptr [edi + 0x37c]
00635ef4 movss xmm0, dword ptr [0xb6a614]
00635efc movss xmm2, dword ptr [eax]
00635f00 call 0x962380
00635f05 movss xmm1, dword ptr [edi + 0x2f4]
00635f0d call 0x65c960
00635f12 lea eax, [ebp - 0x46c]
00635f18 movss dword ptr [ebp - 0x46c], xmm0
