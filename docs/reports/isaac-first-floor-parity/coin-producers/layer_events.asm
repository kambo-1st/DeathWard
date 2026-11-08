00403a90 push ebx
00403a91 push esi
00403a92 mov esi, ecx
00403a94 push edi
00403a95 mov edi, dword ptr [esi + 4]
00403a98 mov ebx, edi
00403a9a test edi, edi
00403a9c jne 0x403ab2
00403a9e push 0xa081ec
00403aa3 push 3
00403aa5 call 0x95e330
00403aaa mov edi, dword ptr [esi + 4]
00403aad add esp, 8
00403ab0 mov ebx, edi
00403ab2 xor edx, edx
00403ab4 cmp dword ptr [ebx + 0x2c], edx
00403ab7 jbe 0x403af9
00403ab9 movss xmm1, dword ptr [esi + 0x10]
00403abe nop 
00403ac0 mov eax, dword ptr [ebx + 0x28]
00403ac3 movd xmm0, dword ptr [eax + edx*8 + 4]
00403ac9 cvtdq2ps xmm0, xmm0
00403acc ucomiss xmm0, xmm1
00403acf lahf 
00403ad0 test ah, 0x44
00403ad3 jp 0x403af3
00403ad5 mov eax, dword ptr [ebx + 0x28]
00403ad8 mov ecx, dword ptr [esi + 0x18]
00403adb mov eax, dword ptr [eax + edx*8]
00403ade bts ecx, eax
00403ae1 mov dword ptr [esi + 0x18], ecx
00403ae4 mov eax, dword ptr [ebx + 0x28]
00403ae7 mov ecx, dword ptr [esi + 0x1c]
00403aea mov eax, dword ptr [eax + edx*8]
00403aed bts ecx, eax
00403af0 mov dword ptr [esi + 0x1c], ecx
00403af3 inc edx
00403af4 cmp edx, dword ptr [edi + 0x2c]
00403af7 jb 0x403ac0
00403af9 pop edi
00403afa pop esi
00403afb pop ebx
00403afc ret 
