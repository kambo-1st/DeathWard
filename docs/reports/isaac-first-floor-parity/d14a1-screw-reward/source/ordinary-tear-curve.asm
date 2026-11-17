0073006a mulss xmm1, dword ptr [0xb6a690]
00730072 lea edx, [ebp - 0x488]
00730078 lea ecx, [ebp - 0x48c]
0073007e mov dword ptr [ebp - 0x48c], 0
00730088 addss xmm1, xmm0
0073008c movss dword ptr [ebp - 0x488], xmm1
00730094 call 0x417c70
00730099 movss xmm0, dword ptr [eax]
0073009d call 0x4228f0
007300a2 lea edx, [ebp - 0x490]
007300a8 movss dword ptr [ebp - 0x42c], xmm0
007300b0 lea ecx, [ebp - 0x448]
007300b6 mov dword ptr [ebp - 0x490], 0
007300c0 call 0x407e80
007300c5 movss xmm0, dword ptr [ebp - 0x42c]
007300cd lea edx, [ebp - 0x494]
007300d3 mulss xmm0, dword ptr [0xb6a910]
007300db lea ecx, [ebp - 0x498]
007300e1 movss xmm1, dword ptr [0xb6a9b0]
007300e9 subss xmm1, xmm0
007300ed movss xmm0, dword ptr [eax]
007300f1 mulss xmm0, dword ptr [0xb6a910]
007300f9 mov dword ptr [ebp - 0x498], 0x40a00000
00730103 subss xmm1, xmm0
00730107 movss dword ptr [ebp - 0x494], xmm1
0073010f call 0x417c70
00730114 movss xmm1, dword ptr [0xb6aa0c]
0073011c mov esi, dword ptr [ebp - 0x428]
00730122 mov ecx, esi
00730124 push 0
00730126 movss xmm0, dword ptr [eax]
0073012a movss dword ptr [ebp - 0x448], xmm0
00730132 addss xmm0, dword ptr [0xb6a614]
0073013a push 0x258
0073013f divss xmm1, xmm0
