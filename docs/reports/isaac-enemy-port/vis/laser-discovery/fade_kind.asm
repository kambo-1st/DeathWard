008c5940 mov eax, dword ptr [ecx + 0x2c]
008c5943 dec eax
008c5944 cmp eax, 0xe
008c5947 ja 0x8c595a
008c5949 movzx eax, byte ptr [eax + 0x8c5968]
008c5950 jmp dword ptr [eax*4 + 0x8c5960]
008c5957 mov al, 1
008c5959 ret 
008c595a xor al, al
008c595c ret 
008c595d nop dword ptr [eax]
008c5960 push edi
008c5961 pop ecx
008c5962 mov word ptr [eax], es
008c5964 pop edx
008c5965 pop ecx
008c5966 mov word ptr [eax], es
008c5968 add byte ptr [ecx], al
008c596a add byte ptr [ecx], al
008c596c add dword ptr [eax], eax
008c596e add dword ptr [ecx], eax
008c5970 add byte ptr [ecx], al
008c5972 add byte ptr [eax], al
008c5974 add byte ptr [eax], al
008c5976 add ah, cl
008c5978 int3 
008c5979 int3 
008c597a int3 
008c597b int3 
008c597c int3 
008c597d int3 
008c597e int3 
008c597f int3 
008c5980 mov eax, dword ptr [ecx + 0x47c]
008c5986 test eax, eax
008c5988 je 0x8c5991
008c598a mov ecx, eax
008c598c jmp 0x8c5980
008c5991 lea eax, [ecx + 0x470]
008c5997 ret 
008c5998 int3 
008c5999 int3 
008c599a int3 
008c599b int3 
008c599c int3 
008c599d int3 
008c599e int3 
008c599f int3 
008c59a0 push ebp
008c59a1 mov ebp, esp
008c59a3 movss xmm0, dword ptr [ebp + 8]
008c59a8 mov eax, dword ptr [ecx + 0x36c]
008c59ae movss dword ptr [ecx + 0x368], xmm0
008c59b6 movss dword ptr [ecx + 0x36c], xmm0
008c59be subss xmm0, dword ptr [0xb6aae4]
008c59c6 mov dword ptr [ecx + 0x370], eax
008c59cc movss dword ptr [ecx + 0xe0], xmm0
008c59d4 pop ebp
008c59d5 ret 4
008c59d8 int3 
008c59d9 int3 
008c59da int3 
008c59db int3 
008c59dc int3 
008c59dd int3 
008c59de int3 
008c59df int3 
