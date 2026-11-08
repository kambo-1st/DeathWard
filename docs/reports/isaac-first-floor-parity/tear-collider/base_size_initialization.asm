00681f87 mov eax, edx
00681f89 mov dword ptr [esi + 0x2c8], 0
00681f93 movss xmm0, dword ptr [0xc02fec]
00681f9b movss dword ptr [esi + 0x2cc], xmm0
00681fa3 movss xmm0, dword ptr [0xc02ff0]
00681fab movss dword ptr [esi + 0x2d0], xmm0
00681fb3 push dword ptr [eax + 0x48]
00681fb6 movss xmm0, dword ptr [eax + 0x38]
00681fbb push dword ptr [eax + 0x40]
00681fbe push dword ptr [eax + 0x3c]
00681fc1 push ecx
00681fc2 mov ecx, esi
00681fc4 movss dword ptr [esp], xmm0
00681fc9 call 0x6843a0
00681fce mov edi, dword ptr [esi + 0x288]
00681fd4 mov eax, dword ptr [edi + 0x4c]
00681fd7 mov dword ptr [esi + 0x2c0], eax
