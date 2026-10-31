00635d8d mov eax, dword ptr [edi + 0x388]
00635d93 and eax, 0x8000000
00635d98 or eax, 0
00635d9b je 0x635e4f
00635da1 movss xmm1, dword ptr [edi + 0x2f4]
00635da9 movss xmm0, dword ptr [edi + 0x37c]
00635db1 call 0x65c960
00635db6 lea eax, [ebp - 0x478]
00635dbc movss dword ptr [ebp - 0x478], xmm0
00635dc4 push eax
00635dc5 mov ecx, esi
00635dc7 call 0x962bb0
00635dcc mov eax, dword ptr [edi + 0x34]
00635dcf cmp eax, 0x197
00635dd4 jne 0x635e0c
00635dd6 mov ecx, esi
00635dd8 call 0x962a00
00635ddd movss xmm1, dword ptr [0xb6a95c]
00635de5 fstp dword ptr [ebp - 0x30c]
00635deb movss xmm0, dword ptr [ebp - 0x30c]
00635df3 comiss xmm0, xmm1
00635df6 jbe 0x635e4f
00635df8 divss xmm1, xmm0
00635dfc lea eax, [ebp - 0x3bc]
00635e02 movss dword ptr [ebp - 0x3bc], xmm1
00635e0a jmp 0x635e47
00635e0c cmp eax, 0x378
00635e11 jne 0x635e4f
00635e13 mov ecx, esi
00635e15 call 0x962a00
00635e1a movss xmm1, dword ptr [0xb6a974]
00635e22 fstp dword ptr [ebp - 0x3bc]
00635e28 movss xmm0, dword ptr [ebp - 0x3bc]
00635e30 comiss xmm0, xmm1
00635e33 jbe 0x635e4f
00635e35 divss xmm1, xmm0
00635e39 lea eax, [ebp - 0x474]
00635e3f movss dword ptr [ebp - 0x474], xmm1
00635e47 push eax
00635e48 mov ecx, esi
00635e4a call 0x962bb0
