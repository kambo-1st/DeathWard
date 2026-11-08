0078bf20 push ebp
0078bf21 mov ebp, esp
0078bf23 and esp, 0xfffffff8
0078bf26 sub esp, 0xc
0078bf29 push ebx
0078bf2a push esi
0078bf2b push edi
0078bf2c mov edi, ecx
0078bf2e mov esi, dword ptr [edi + 0x1294]
0078bf34 mov ecx, dword ptr [edi + 0x1cc4]
0078bf3a lea eax, [esi + 1]
0078bf3d cdq 
0078bf3e sub eax, edx
0078bf40 sar eax, 1
0078bf42 cmp eax, ecx
0078bf44 cmovl ecx, eax
0078bf47 mov dword ptr [edi + 0x1cc4], ecx
0078bf4d lea eax, [ecx + ecx]
0078bf50 mov ecx, edi
0078bf52 cmp esi, eax
0078bf54 cmovl esi, eax
0078bf57 mov dword ptr [edi + 0x1294], esi
0078bf5d call 0x78fd00
0078bf62 cmp byte ptr [edi + 0x16b], 0
0078bf69 jne 0x78c098
0078bf6f cmp dword ptr [edi + 0x130c], 0x1a
0078bf76 jne 0x78c098
0078bf7c mov eax, dword ptr [edi + 0x1ca8]
0078bf82 add eax, dword ptr [edi + 0x186c]
0078bf88 add eax, dword ptr [edi + 0x129c]
0078bf8e add eax, dword ptr [edi + 0x1298]
0078bf94 add eax, dword ptr [edi + 0x1294]
0078bf9a cmp eax, 1
0078bf9d jne 0x78c098
0078bfa3 mov ebx, dword ptr [0xbfd65c]
0078bfa9 mov esi, dword ptr [ebx + 0x18190]
0078bfaf cmp byte ptr [esi], 0
0078bfb2 je 0x78c09e
0078bfb8 mov eax, dword ptr [ebx + 0x1a30dc]
0078bfbe sub eax, dword ptr [esi + 0x11f0]
0078bfc4 cmp eax, 1
0078bfc7 jle 0x78c09e
0078bfcd lea ecx, [edi + 0x1450]
0078bfd3 push 0x6e
0078bfd5 call 0x88b600
0078bfda test al, al
0078bfdc jne 0x78c09e
0078bfe2 mov esi, dword ptr [esi + 0x1254]
0078bfe8 xor edx, edx
0078bfea test esi, esi
0078bfec je 0x78c039
0078bfee mov ecx, dword ptr [ebx + 0x18190]
0078bff4 mov ecx, dword ptr [ecx + 0x124c]
0078bffa nop word ptr [eax + eax]
