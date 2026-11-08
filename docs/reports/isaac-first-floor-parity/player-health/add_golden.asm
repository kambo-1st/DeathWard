0078be00 push ebp
0078be01 mov ebp, esp
0078be03 and esp, 0xfffffff8
0078be06 push esi
0078be07 mov esi, ecx
0078be09 push edi
0078be0a cmp dword ptr [esi + 0x130c], 0x28
0078be11 jne 0x78be28
0078be13 mov eax, dword ptr [esi + 0x1d80]
0078be19 test eax, eax
0078be1b je 0x78be28
0078be1d mov esi, eax
0078be1f cmp dword ptr [esi + 0x130c], 0x28
0078be26 je 0x78be13
0078be28 mov ecx, dword ptr [esi + 0x1290]
0078be2e mov eax, dword ptr [esi + 0x1294]
0078be34 cmp ecx, eax
0078be36 mov edi, dword ptr [esi + 0x186c]
0078be3c cmovl eax, ecx
0078be3f inc eax
0078be40 cdq 
0078be41 sub eax, edx
0078be43 mov ecx, eax
0078be45 mov eax, dword ptr [esi + 0x129c]
0078be4b inc eax
0078be4c sar ecx, 1
0078be4e cdq 
0078be4f sub eax, edx
0078be51 mov edx, dword ptr [ebp + 8]
0078be54 sar eax, 1
0078be56 add edx, edi
0078be58 add ecx, eax
0078be5a add ecx, dword ptr [esi + 0x1ca8]
0078be60 cmp ecx, edx
0078be62 cmovl edx, ecx
0078be65 xor eax, eax
0078be67 test edx, edx
0078be69 mov ecx, esi
0078be6b cmovg eax, edx
0078be6e mov dword ptr [esi + 0x186c], eax
0078be74 call 0x78c810
0078be79 cmp dword ptr [esi + 0x186c], edi
0078be7f jle 0x78beab
0078be81 mov eax, dword ptr [0xbfd65c]
0078be86 add eax, 0x3da4c
0078be8b xor ecx, ecx
0078be8d nop dword ptr [eax]
0078be90 cmp dword ptr [eax], esi
0078be92 je 0x78bea7
0078be94 inc ecx
0078be95 add eax, 0x6b0
0078be9a cmp ecx, 8
0078be9d jb 0x78be90
0078be9f pop edi
0078bea0 pop esi
0078bea1 mov esp, ebp
0078bea3 pop ebp
0078bea4 ret 4
0078bea7 mov byte ptr [eax + 0xe], 4
0078beab pop edi
0078beac pop esi
0078bead mov esp, ebp
0078beaf pop ebp
0078beb0 ret 4
0078beb3 int3 
0078beb4 int3 
0078beb5 int3 
0078beb6 int3 
0078beb7 int3 
0078beb8 int3 
0078beb9 int3 
0078beba int3 
0078bebb int3 
0078bebc int3 
0078bebd int3 
0078bebe int3 
0078bebf int3 
0078bec0 cmp dword ptr [ecx + 0x130c], 0x28
0078bec7 jne 0x78bee5
0078bec9 nop dword ptr [eax]
0078bed0 mov eax, dword ptr [ecx + 0x1d80]
0078bed6 test eax, eax
0078bed8 je 0x78bee5
0078beda mov ecx, eax
0078bedc cmp dword ptr [ecx + 0x130c], 0x28
0078bee3 je 0x78bed0
0078bee5 mov edx, dword ptr [ecx + 0x1290]
0078beeb mov eax, dword ptr [ecx + 0x1294]
0078bef1 cmp edx, eax
0078bef3 push esi
0078bef4 cmovl eax, edx
0078bef7 inc eax
0078bef8 cdq 
0078bef9 sub eax, edx
0078befb mov esi, eax
0078befd mov eax, dword ptr [ecx + 0x129c]
0078bf03 inc eax
0078bf04 sar esi, 1
0078bf06 cdq 
0078bf07 sub eax, edx
0078bf09 sar eax, 1
0078bf0b add esi, eax
0078bf0d add esi, dword ptr [ecx + 0x1ca8]
0078bf13 cmp dword ptr [ecx + 0x186c], esi
0078bf19 pop esi
0078bf1a setl al
0078bf1d ret 
0078bf1e int3 
0078bf1f int3 
