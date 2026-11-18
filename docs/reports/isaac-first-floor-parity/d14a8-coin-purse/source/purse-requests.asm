0072bb2b cmp byte ptr [ebp + 0x10], 0
0072bb2f je 0x72e057
0072bb35 mov dword ptr [ebp - 0x30], 0
0072bb3c lea eax, [esi + 0x294]
0072bb42 push 0
0072bb44 push 0
0072bb46 push ecx
0072bb47 mov ecx, dword ptr [0xbfd65c]
0072bb4d mov dword ptr [esp], 0x42200000
0072bb54 push eax
0072bb55 lea eax, [ebp - 0x40]
0072bb58 mov ecx, dword ptr [ecx + 0x18190]
0072bb5e push eax
0072bb5f call 0x7cf240
0072bb64 mov edx, dword ptr [edi]
0072bb66 test edx, edx
0072bb68 jne 0x72bb80
0072bb6a push 0xb4d6c4
0072bb6f push 3
0072bb71 call 0x95e330
0072bb76 mov edx, dword ptr [edi]
0072bb78 add esp, 8
0072bb7b test edx, edx
0072bb7d jne 0x72bb80
0072bb7f int3
0072bb80 mov ecx, dword ptr [edi + 4]
0072bb83 mov eax, edx
0072bb85 shr eax, cl
0072bb87 mov ecx, dword ptr [edi + 8]
0072bb8a xor eax, edx
0072bb8c mov edx, eax
0072bb8e shl edx, cl
0072bb90 mov ecx, dword ptr [edi + 0xc]
0072bb93 xor edx, eax
0072bb95 mov eax, edx
0072bb97 shr eax, cl
0072bb99 mov ecx, dword ptr [0xbfd65c]
0072bb9f xor eax, edx
0072bba1 push eax
0072bba2 push 0
0072bba4 push esi
0072bba5 push 0xc02fec
0072bbaa mov dword ptr [edi], eax
0072bbac lea eax, [ebp - 0x40]
0072bbaf push eax
0072bbb0 push 0x46
0072bbb2 push 5
0072bbb4 call 0x422e20
0072bbb9 mov ecx, dword ptr [ebp - 0x30]
0072bbbc mov dword ptr [eax + 0x4a0], ecx
0072bbc2 inc ecx
0072bbc3 mov dword ptr [ebp - 0x30], ecx
0072bbc6 lea eax, [esi + 0x294]
0072bbcc cmp ecx, 4
0072bbcf jl 0x72bb42
0072bbd5 jmp 0x72e057
