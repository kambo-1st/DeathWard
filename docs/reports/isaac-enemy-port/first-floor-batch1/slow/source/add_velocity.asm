00422b60 push ebp
00422b61 mov ebp, esp
00422b63 movss xmm3, dword ptr [ecx + 0x2c4]
00422b6b ucomiss xmm3, dword ptr [0xb6a18c]
00422b72 lahf 
00422b73 test ah, 0x44
00422b76 jnp 0x422bcb
00422b78 cmp byte ptr [ebp + 0xc], 0
00422b7c je 0x422b88
00422b7e movss xmm2, dword ptr [0xb6a614]
00422b86 jmp 0x422b90
00422b88 movss xmm2, dword ptr [ecx + 0x2f4]
00422b90 mov eax, dword ptr [ebp + 8]
00422b93 movaps xmm0, xmm2
00422b96 movss xmm1, dword ptr [eax + 4]
00422b9b mulss xmm0, dword ptr [eax]
00422b9f mulss xmm1, xmm2
00422ba3 divss xmm0, xmm3
00422ba7 divss xmm1, xmm3
00422bab addss xmm0, dword ptr [ecx + 0x2b8]
00422bb3 addss xmm1, dword ptr [ecx + 0x2bc]
00422bbb movss dword ptr [ecx + 0x2b8], xmm0
00422bc3 movss dword ptr [ecx + 0x2bc], xmm1
00422bcb pop ebp
00422bcc ret 8
