007015e9 imul eax, esi, 0x34
007015ec lea ecx, [ebp - 0xa4]
007015f2 lea esi, [edi + 4]
007015f5 add esi, eax
007015f7 mov dword ptr [ebp - 0x80], esi
007015fa call 0x7a7db0
007015ff fmul dword ptr [esi]
00701601 mov ecx, edi
00701603 push dword ptr [ebp - 0x74]
00701606 push esi
00701607 fstp dword ptr [ebp - 0x78]
0070160a movss xmm1, dword ptr [ebp - 0x78]
0070160f call 0x700c60
