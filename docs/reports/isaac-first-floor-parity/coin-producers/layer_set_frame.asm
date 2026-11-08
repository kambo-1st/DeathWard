00403b00 push ebp
00403b01 mov ebp, esp
00403b03 sub esp, 0xc
00403b06 push esi
00403b07 mov esi, ecx
00403b09 push edi
00403b0a sub esp, 8
00403b0d movss xmm0, dword ptr [esi + 0x10]
00403b12 movss dword ptr [ebp - 4], xmm0
00403b17 fld dword ptr [ebp - 4]
00403b1a fstp qword ptr [esp]
00403b1d call 0x9ec3b2
00403b22 mov edi, dword ptr [ebp + 8]
00403b25 add esp, 8
00403b28 fstp dword ptr [ebp - 8]
00403b2b fld dword ptr [ebp - 8]
00403b2e fstp dword ptr [ebp - 8]
00403b31 cvttss2si eax, dword ptr [ebp - 8]
00403b36 cmp edi, eax
00403b38 jge 0x403b52
00403b3a push eax
00403b3b push edi
00403b3c push 0xa08208
00403b41 push 3
00403b43 call 0x95e330
00403b48 movss xmm1, dword ptr [esi + 0x10]
00403b4d add esp, 0x10
00403b50 jmp 0x403b57
00403b52 movss xmm1, dword ptr [ebp - 4]
00403b57 movd xmm0, edi
00403b5b cvtdq2ps xmm0, xmm0
00403b5e mov dword ptr [esi + 0x18], 0
00403b65 comiss xmm0, xmm1
00403b68 movss dword ptr [ebp + 8], xmm0
00403b6d jbe 0x403bae
00403b6f nop 
00403b70 fld dword ptr [esi + 0x10]
00403b73 sub esp, 8
00403b76 fstp qword ptr [esp]
00403b79 call 0x9ec3b2
00403b7e fstp dword ptr [ebp - 8]
00403b81 fld dword ptr [ebp - 8]
00403b84 add esp, 8
00403b87 fstp dword ptr [ebp - 8]
00403b8a movss xmm0, dword ptr [ebp - 8]
00403b8f mov ecx, esi
00403b91 addss xmm0, dword ptr [0xb6a614]
00403b99 movss dword ptr [esi + 0x10], xmm0
00403b9e call 0x403a90
00403ba3 movss xmm0, dword ptr [ebp + 8]
00403ba8 comiss xmm0, dword ptr [esi + 0x10]
00403bac ja 0x403b70
00403bae mov eax, dword ptr [esi + 4]
00403bb1 xor edi, edi
00403bb3 cmp dword ptr [eax + 0x1c], edi
00403bb6 jbe 0x403bd1
00403bb8 push edi
00403bb9 movaps xmm2, xmm0
00403bbc mov ecx, esi
00403bbe call 0x403990
00403bc3 mov eax, dword ptr [esi + 4]
00403bc6 inc edi
00403bc7 movss xmm0, dword ptr [ebp + 8]
00403bcc cmp edi, dword ptr [eax + 0x1c]
00403bcf jb 0x403bb8
00403bd1 xor edi, edi
00403bd3 cmp dword ptr [eax + 0x24], edi
00403bd6 jbe 0x403bee
00403bd8 movss xmm2, dword ptr [ebp + 8]
00403bdd mov ecx, esi
00403bdf push edi
00403be0 call 0x403a10
00403be5 mov eax, dword ptr [esi + 4]
00403be8 inc edi
00403be9 cmp edi, dword ptr [eax + 0x24]
00403bec jb 0x403bd8
00403bee pop edi
00403bef pop esi
00403bf0 mov esp, ebp
00403bf2 pop ebp
