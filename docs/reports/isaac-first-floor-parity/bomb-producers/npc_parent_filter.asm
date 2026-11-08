0067b342 mov esi, dword ptr [edi + 0x320]
0067b348 mov dword ptr [ebp - 0xac], esi
0067b34e test esi, esi
0067b350 je 0x67b361
0067b352 xor eax, eax
0067b354 cmp dword ptr [esi + 0x28], 1
0067b358 cmovne esi, eax
0067b35b mov dword ptr [ebp - 0xac], esi
