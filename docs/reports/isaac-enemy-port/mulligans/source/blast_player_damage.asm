006d205b movss xmm0, dword ptr [ebx + 0xc]
006d2060 comiss xmm0, xmm1
006d2063 jbe 0x6d20c4
006d2065 push esi
006d2066 lea ecx, [ebp - 0x98]
006d206c call 0x4229a0
006d2071 movzx eax, byte ptr [ebp - 0x11]
006d2075 movss xmm1, dword ptr [0xb6a614]
006d207d add eax, eax
006d207f or dword ptr [ebp - 0x78], eax
006d2082 comiss xmm0, dword ptr [0xb6aad8]
006d2089 jb 0x6d2095
006d208b movss xmm0, dword ptr [0xb6a7b0]
006d2093 jmp 0x6d2098
006d2095 movaps xmm0, xmm1
006d2098 mov ecx, dword ptr [ebx + 0x2c]
006d209b mov eax, ecx
006d209d and eax, 0x10000000
006d20a2 or eax, 0
006d20a5 je 0x6d20aa
006d20a7 movaps xmm0, xmm1
006d20aa mov eax, dword ptr [edi]
006d20ac lea edx, [ebp - 0x98]
006d20b2 push 0x1e
006d20b4 push edx
006d20b5 push dword ptr [ebx + 0x30]
006d20b8 push ecx
006d20b9 push ecx
006d20ba mov ecx, edi
006d20bc movss dword ptr [esp], xmm0
006d20c1 call dword ptr [eax + 0x20]
