00725cc0 push ebp
00725cc1 mov ebp, esp
00725cc3 and esp, 0xfffffff8
00725cc6 sub esp, 0xc
00725cc9 push ebx
00725cca push esi
00725ccb push edi
00725ccc mov ebx, ecx
00725cce push 0x5e
00725cd0 mov dword ptr [esp + 0x14], ebx
00725cd4 call 0x78d4c0
00725cd9 mov edx, dword ptr [ebp + 8]
00725cdc test eax, eax
00725cde lea edi, [edx + edx]
00725ce1 cmovle edi, edx
00725ce4 xor esi, esi
00725ce6 add dword ptr [ebx + 0x12bc], edi
00725cec mov eax, dword ptr [ebx + 0x12bc]
00725cf2 mov dword ptr [esp + 0xc], edi
00725cf6 test edi, edi
00725cf8 jle 0x725d91
00725cfe mov ebx, dword ptr [ebp + 0x10]
00725d01 call 0x6c3d90
00725d06 mov ecx, dword ptr [0xbfd65c]
00725d0c push 0
00725d0e push eax
00725d0f push 0
00725d11 push dword ptr [esp + 0x1c]
00725d15 push 0xc02fec
00725d1a push dword ptr [ebp + 0xc]
00725d1d push 0x2b
00725d1f push 3
00725d21 call 0x6d0ca0
00725d26 mov esi, eax
00725d28 test ebx, ebx
00725d2a je 0x725d67
00725d2c cmp byte ptr [ebx + 0x16b], 0
00725d33 jne 0x725d67
00725d35 mov ecx, dword ptr [esi + 0x31c]
00725d3b lea edi, [esi + 0x31c]
00725d41 test ecx, ecx
00725d43 je 0x725d59
00725d45 lea eax, [esp + 0x14]
00725d49 mov dword ptr [esp + 0x14], edi
00725d4d push eax
00725d4e add ecx, 0x324
00725d54 call 0x4bc3c0
00725d59 push edi
00725d5a mov ecx, ebx
00725d5c mov dword ptr [edi], ebx
00725d5e call 0x4bae70
00725d63 mov edi, dword ptr [esp + 0xc]
00725d67 and dword ptr [esi + 0x160], 0xfffffffb
00725d6e sub edi, 1
00725d71 mov eax, dword ptr [esi + 0x164]
00725d77 mov dword ptr [esi + 0x164], eax
00725d7d mov dword ptr [esp + 0xc], edi
00725d81 jne 0x725d01
00725d87 mov eax, dword ptr [esp + 0x10]
00725d8b mov eax, dword ptr [eax + 0x12bc]
00725d91 cmp eax, 0x14
00725d94 jl 0x725da9
00725d96 mov ecx, dword ptr [0xbfd680]
