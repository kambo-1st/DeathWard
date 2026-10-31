00501369 lea ecx, [esp + 0x50]
0050136d call 0x430d70
00501372 cmp dword ptr [edi + 0x28], 0xf8
00501379 jne 0x5013d8
0050137b mov eax, dword ptr [esp + 0xac]
00501382 lea ecx, [esp + 0x24]
00501386 movaps xmm0, xmmword ptr [0xb6bb40]
0050138d or dword ptr [esp + 0xa8], 1
00501395 push 1
00501397 push 0
00501399 push 0xff
0050139e mov dword ptr [esp + 0xb8], eax
005013a5 mov eax, dword ptr [ebx]
005013a7 push -1
005013a9 movups xmmword ptr [esp + 0x34], xmm0
005013ae push ecx
005013af movaps xmm0, xmmword ptr [0xb6c550]
005013b6 mov ecx, ebx
005013b8 movups xmmword ptr [esp + 0x48], xmm0
005013bd mov dword ptr [esp + 0x58], 0x3e851eb8
005013c5 mov dword ptr [esp + 0x5c], 0x3d4ccccd
005013cd mov dword ptr [esp + 0x60], 0x3ecccccd
005013d5 call dword ptr [eax + 0x38]
005013d8 lea eax, [esp + 0x50]
005013dc mov ecx, edi
005013de push eax
005013df push 0
005013e1 lea eax, [esp + 0x20]
005013e5 push eax
005013e6 push esi
005013e7 call 0x6a1a20
