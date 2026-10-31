004fa8cb call 0x6c3d90
004fa8d0 cmp dword ptr [edi + 0x28], 0x16
004fa8d4 mov ecx, 0x12
004fa8d9 push 0
004fa8db push 0xbeab70
004fa8e0 push 0xbeab18
004fa8e5 push 0
004fa8e7 push eax
004fa8e8 push 0
004fa8ea push edi
004fa8eb push 0xc02fec
004fa8f0 lea eax, [edi + 0x294]
004fa8f6 push eax
004fa8f7 mov eax, 0x55
004fa8fc cmove eax, ecx
004fa8ff mov ecx, dword ptr [0xbfd65c]
004fa905 push 0
004fa907 push eax
004fa908 call 0x422e20
004fa90d push eax
004fa90e call 0x9ec34c
004fa913 add esp, 0x14
004fa916 mov byte ptr [eax + 0x16c], 1
004fa91d mov ecx, dword ptr [eax + 0x164]
004fa923 mov dword ptr [eax + 0x164], ecx
004fa929 and dword ptr [eax + 0x160], 0xfffffffb
