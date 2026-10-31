--- type822 compare ---
0064dfb9 call 0x412050
0064dfbe add esp, 4
0064dfc1 mov ecx, eax
0064dfc3 call 0x412090
0064dfc8 test al, al
0064dfca jne 0x64dde9
0064dfd0 mov eax, dword ptr [esi + 0x28]
0064dfd3 cmp eax, 0x123
0064dfd8 je 0x64dde9
0064dfde cmp eax, 0x19b
0064dfe3 jne 0x64e10d
0064dfe9 cmp byte ptr [esi + 0x308], 0
0064dff0 jne 0x64dde9
0064dff6 cmp byte ptr [ebp - 0xb1], 0
0064dffd jne 0x64e3a7
0064e003 cmp eax, 0x336
0064e008 jne 0x64e3a7
0064e00e cmp dword ptr [esi + 0xab4], 0x10
0064e015 jne 0x64e3a7
0064e01b mov eax, dword ptr [esi + 0x344]
0064e021 lea ecx, [ebp - 0xec]
0064e027 add eax, dword ptr [edi + 0x344]
0064e02d movq xmm0, qword ptr [0xa08c44]
0064e035 mov dword ptr [ebp - 0xec], eax
0064e03b mov eax, dword ptr [0xa08c4c]
0064e040 push 5
0064e042 movq qword ptr [ebp - 0xe8], xmm0
0064e04a mov dword ptr [ebp - 0xe0], eax
0064e050 call 0x7a7d50
0064e055 test eax, eax
0064e057 jne 0x64e3a7
0064e05d movss xmm0, dword ptr [edi + 0x294]
0064e065 lea eax, [ebp - 0xf4]
0064e06b subss xmm0, dword ptr [esi + 0x294]
0064e073 push eax
0064e074 lea ecx, [ebp - 0xd4]
0064e07a movss dword ptr [ebp - 0xd4], xmm0
0064e082 movss xmm0, dword ptr [edi + 0x298]
--- type822 compare ---
006a4381 jle 0x6a43a5
006a4383 push edi
006a4384 lea ecx, [ebp - 0x38]
006a4387 call 0x4229a0
006a438c mov eax, dword ptr [esi]
006a438e lea ecx, [ebp - 0x38]
006a4391 push 0x1e
006a4393 push ecx
006a4394 push 0
006a4396 push 0
006a4398 push ecx
006a4399 mov ecx, esi
006a439b mov dword ptr [esp], 0x41200000
006a43a2 call dword ptr [eax + 0x20]
006a43a5 mov eax, dword ptr [edi + 0x28]
006a43a8 cmp eax, 0x336
006a43ad jne 0x6a43d0
006a43af cmp dword ptr [edi + 0xab4], 0x10
006a43b6 jne 0x6a43f1
006a43b8 cmp dword ptr [esi + 0x28], 1
006a43bc je 0x6a43c6
006a43be cmp esi, dword ptr [edi + 0x31c]
006a43c4 jne 0x6a43f1
006a43c6 mov eax, dword ptr [edi]
006a43c8 mov ecx, edi
006a43ca call dword ptr [eax + 0x24]
006a43cd mov eax, dword ptr [edi + 0x28]
006a43d0 cmp eax, 0x38a
006a43d5 jne 0x6a445b
006a43db cmp dword ptr [edi + 0x2c], 1
006a43df jne 0x6a43f1
006a43e1 cmp dword ptr [esi + 0x28], 1
006a43e5 jne 0x6a43f8
006a43e7 mov eax, dword ptr [edi]
006a43e9 mov ecx, edi
006a43eb call dword ptr [eax + 0x24]
006a43ee mov eax, dword ptr [edi + 0x28]
006a43f1 cmp eax, 0x38a
