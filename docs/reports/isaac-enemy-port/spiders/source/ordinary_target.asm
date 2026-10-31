00695bf3 and ecx, 0x1000800
00695bf9 or ecx, 0
00695bfc je 0x695c0c
00695bfe mov eax, dword ptr [esi + 0x28]
00695c01 cmp eax, 0x10
00695c04 jne 0x695c30
00695c06 cmp dword ptr [esi + 0x2c], 2
00695c0a je 0x695c3c
00695c0c mov ecx, esi
00695c0e call 0x695680
00695c13 mov ecx, dword ptr [eax + 0x294]
00695c19 mov edx, dword ptr [eax + 0x298]
00695c1f mov eax, dword ptr [ebp + 8]
00695c22 mov dword ptr [eax + 4], edx
00695c25 mov dword ptr [eax], ecx
00695c27 pop edi
00695c28 pop esi
00695c29 pop ebx
00695c2a mov esp, ebp
00695c2c pop ebp
00695c2d ret 8
