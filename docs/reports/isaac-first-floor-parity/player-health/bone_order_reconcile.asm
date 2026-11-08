0078cb90 push ebx
0078cb91 push esi
0078cb92 push edi
0078cb93 push 0
0078cb95 mov edi, ecx
0078cb97 call 0x78cc70
0078cb9c mov ecx, dword ptr [edi + 0x1290]
0078cba2 mov esi, dword ptr [edi + 0x1ca8]
0078cba8 inc ecx
0078cba9 cdq 
0078cbaa sub eax, edx
0078cbac mov edx, dword ptr [edi + 0x129c]
0078cbb2 add ecx, edx
0078cbb4 sar eax, 1
0078cbb6 sar ecx, 1
0078cbb8 sub eax, ecx
0078cbba cmp eax, esi
0078cbbc cmovl esi, eax
0078cbbf mov dword ptr [edi + 0x1ca8], esi
0078cbc5 test esi, esi
0078cbc7 jg 0x78cbe1
0078cbc9 mov dword ptr [edi + 0x1ca8], 0
0078cbd3 mov dword ptr [edi + 0x1cac], 0
0078cbdd pop edi
0078cbde pop esi
0078cbdf pop ebx
0078cbe0 ret 
0078cbe1 lea eax, [edx + 1]
0078cbe4 mov ecx, 0x20
0078cbe9 cdq 
0078cbea sub eax, edx
0078cbec or edx, 0xffffffff
0078cbef mov ebx, eax
0078cbf1 sar ebx, 1
0078cbf3 add ebx, esi
0078cbf5 sub ecx, ebx
0078cbf7 shr edx, cl
0078cbf9 and dword ptr [edi + 0x1cac], edx
0078cbff xor edx, edx
0078cc01 mov eax, dword ptr [edi + 0x1cac]
0078cc07 test ebx, ebx
0078cc09 jle 0x78cc29
0078cc0b mov ecx, 1
0078cc10 test ecx, eax
0078cc12 je 0x78cc1c
0078cc14 sub esi, 1
0078cc17 jns 0x78cc1c
0078cc19 btr eax, edx
0078cc1c inc edx
0078cc1d rol ecx, 1
0078cc1f cmp edx, ebx
0078cc21 jl 0x78cc10
0078cc23 mov dword ptr [edi + 0x1cac], eax
0078cc29 lea edx, [ebx - 1]
0078cc2c test edx, edx
0078cc2e js 0x78cc5f
0078cc30 mov eax, 1
0078cc35 mov ecx, edx
0078cc37 rol eax, cl
0078cc39 nop dword ptr [eax]
0078cc40 test esi, esi
0078cc42 jle 0x78cc5f
0078cc44 mov ecx, dword ptr [edi + 0x1cac]
0078cc4a test eax, ecx
0078cc4c jne 0x78cc58
0078cc4e bts ecx, edx
0078cc51 dec esi
0078cc52 mov dword ptr [edi + 0x1cac], ecx
0078cc58 ror eax, 1
0078cc5a sub edx, 1
0078cc5d jns 0x78cc40
0078cc5f pop edi
0078cc60 pop esi
0078cc61 pop ebx
0078cc62 ret 
0078cc63 int3 
0078cc64 int3 
0078cc65 int3 
0078cc66 int3 
0078cc67 int3 
0078cc68 int3 
0078cc69 int3 
0078cc6a int3 
0078cc6b int3 
0078cc6c int3 
0078cc6d int3 
0078cc6e int3 
0078cc6f int3 
