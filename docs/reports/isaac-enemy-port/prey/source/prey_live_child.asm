004fa868 cmp eax, 0x331
004fa86d jne 0x4fa8cb
004fa86f cmp dword ptr [edi + 0x2c], 1
004fa873 lea esi, [edi + 0x294]
004fa879 jne 0x4fa893
004fa87b call 0x6c3d90
004fa880 push eax
004fa881 push 0
004fa883 push edi
004fa884 push 0xc02fec
004fa889 push esi
004fa88a push 0
004fa88c push 0x328
004fa891 jmp 0x4fa8a9
004fa893 call 0x6c3d90
004fa898 push eax
004fa899 push 0
004fa89b push edi
004fa89c push 0xc02fec
004fa8a1 push esi
004fa8a2 push 0
004fa8a4 push 0x32a
004fa8a9 mov ecx, dword ptr [0xbfd65c]
004fa8af call 0x422e20
004fa8b4 mov ecx, eax
004fa8b6 mov eax, dword ptr [ecx + 0x164]
004fa8bc and dword ptr [ecx + 0x160], 0xfffffffb
004fa8c3 mov dword ptr [ecx + 0x164], eax
004fa8c9 jmp 0x4fa930
