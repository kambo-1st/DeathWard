00403d60 push ebp
00403d61 mov ebp, esp
00403d63 sub esp, 0x10
00403d66 push esi
00403d67 mov esi, ecx
00403d69 push edi
00403d6a mov edi, dword ptr [esi + 4]
00403d6d test edi, edi
00403d6f je 0x403e1b
00403d75 cmp byte ptr [esi + 0x14], 0
00403d79 je 0x403e1b
00403d7f mov eax, dword ptr [esi]
00403d81 sub esp, 8
00403d84 movss xmm0, dword ptr [esi + 0x10]
00403d89 movss dword ptr [ebp - 0xc], xmm0
00403d8e addss xmm0, dword ptr [eax + 0x104]
00403d96 movss dword ptr [ebp - 4], xmm0
00403d9b fld dword ptr [ebp - 4]
00403d9e fstp qword ptr [esp]
00403da1 call 0x9ec3b2
00403da6 mov ecx, dword ptr [edi + 0x30]
00403da9 add esp, 8
00403dac fstp dword ptr [ebp - 8]
00403daf fld dword ptr [ebp - 8]
00403db2 fstp dword ptr [ebp - 8]
00403db5 cvttss2si eax, dword ptr [ebp - 8]
00403dba cmp eax, ecx
00403dbc jl 0x403e09
00403dbe cmp byte ptr [edi + 0x34], 0
00403dc2 je 0x403dd1
00403dc4 mov ecx, esi
00403dc6 call 0x405330
00403dcb pop edi
00403dcc pop esi
00403dcd mov esp, ebp
00403dcf pop ebp
00403dd0 ret 
00403dd1 fld dword ptr [ebp - 0xc]
00403dd4 lea edi, [ecx - 1]
00403dd7 sub esp, 8
00403dda fstp qword ptr [esp]
00403ddd call 0x9ec3b2
00403de2 fstp dword ptr [ebp - 0xc]
00403de5 fld dword ptr [ebp - 0xc]
00403de8 add esp, 8
00403deb fstp dword ptr [ebp - 0xc]
00403dee cvttss2si eax, dword ptr [ebp - 0xc]
00403df3 cmp edi, eax
00403df5 jl 0x403dff
00403df7 push edi
00403df8 mov ecx, esi
00403dfa call 0x403b00
00403dff mov byte ptr [esi + 0x14], 0
00403e03 pop edi
00403e04 pop esi
00403e05 mov esp, ebp
00403e07 pop ebp
00403e08 ret 
00403e09 push eax
00403e0a mov ecx, esi
00403e0c call 0x403b00
00403e11 movss xmm0, dword ptr [ebp - 4]
00403e16 movss dword ptr [esi + 0x10], xmm0
00403e1b pop edi
00403e1c pop esi
00403e1d mov esp, ebp
00403e1f pop ebp
00403e20 ret 
