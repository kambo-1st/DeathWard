006848f0 push ecx
006848f1 push esi
006848f2 mov esi, ecx
006848f4 push edi
006848f5 cmp byte ptr [esi + 0x16b], 0
006848fc mov byte ptr [esi + 0x16a], 0
00684903 jne 0x68490c
00684905 mov byte ptr [esi + 0x16b], 1
0068490c push esi
0068490d call 0x802b70
00684912 mov edi, dword ptr [esi + 0x35c]
00684918 test edi, edi
0068491a je 0x684944
0068491c push dword ptr [edi + 4]
0068491f push 0xfff0b9d8
00684924 push dword ptr [edi]
00684926 call dword ptr [0xa06248]
0068492c add esp, 0xc
0068492f push 8
00684931 push edi
00684932 call 0x9eb08e
00684937 add esp, 8
0068493a mov dword ptr [esi + 0x35c], 0
00684944 pop edi
00684945 pop esi
00684946 pop ecx
00684947 ret
