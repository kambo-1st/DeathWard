00549f50 push ebx
00549f51 mov ebx, esp
00549f53 sub esp, 8
00549f56 and esp, 0xfffffff8
00549f59 add esp, 4
00549f5c push ebp
00549f5d mov ebp, dword ptr [ebx + 4]
00549f60 mov dword ptr [esp + 4], ebp
00549f64 mov ebp, esp
00549f66 movss xmm2, dword ptr [ecx + 0xb00]
00549f6e movss xmm4, dword ptr [0xb6c980]
00549f76 movaps xmm0, xmm2
00549f79 movss xmm3, dword ptr [0xb6ac40]
00549f81 andps xmm0, xmm4
00549f84 comiss xmm0, xmm3
00549f87 jbe 0x549fa7
00549f89 movaps xmm1, xmm3
00549f8c movaps xmm0, xmm2
00549f8f call 0x447b40
00549f94 movss xmm3, dword ptr [0xb6ac40]
00549f9c movaps xmm2, xmm0
00549f9f movss xmm4, dword ptr [0xb6c980]
00549fa7 movss xmm1, dword ptr [0xb6ab88]
00549faf comiss xmm2, xmm1
00549fb2 jbe 0x549fba
00549fb4 subss xmm2, xmm3
00549fb8 jmp 0x549fcb
00549fba movss xmm0, dword ptr [0xb6af74]
00549fc2 comiss xmm0, xmm2
00549fc5 jbe 0x549fcb
00549fc7 addss xmm2, xmm3
00549fcb comiss xmm2, dword ptr [0xb6af68]
00549fd2 movss xmm0, dword ptr [0xb6af24]
00549fda jb 0x549ffc
00549fdc comiss xmm0, xmm2
00549fdf jbe 0x549ffc
00549fe1 addss xmm2, dword ptr [0xb6aae4]
00549fe9 mov eax, dword ptr [ebx + 8]
00549fec movss dword ptr [eax], xmm2
00549ff0 mov eax, 1
00549ff5 pop ebp
00549ff6 mov esp, ebx
00549ff8 pop ebx
00549ff9 ret 4
00549ffc comiss xmm2, xmm0
00549fff movss xmm0, dword ptr [0xb6aa4c]
0054a007 jb 0x54a021
0054a009 comiss xmm0, xmm2
0054a00c jbe 0x54a021
0054a00e mov eax, dword ptr [ebx + 8]
0054a011 movss dword ptr [eax], xmm2
0054a015 mov eax, 2
0054a01a pop ebp
0054a01b mov esp, ebx
0054a01d pop ebx
0054a01e ret 4
0054a021 comiss xmm2, xmm0
0054a024 jb 0x54a04e
0054a026 movss xmm0, dword ptr [0xb6ab3c]
0054a02e comiss xmm0, xmm2
0054a031 jbe 0x54a04e
0054a033 subss xmm2, dword ptr [0xb6aae4]
0054a03b mov eax, dword ptr [ebx + 8]
0054a03e movss dword ptr [eax], xmm2
0054a042 mov eax, 3
0054a047 pop ebp
0054a048 mov esp, ebx
0054a04a pop ebx
0054a04b ret 4
0054a04e subss xmm2, xmm1
0054a052 movaps xmm1, xmm2
0054a055 andps xmm1, xmm4
0054a058 comiss xmm1, xmm3
0054a05b jbe 0x54a073
0054a05d movaps xmm1, xmm3
0054a060 movaps xmm0, xmm2
0054a063 call 0x447b40
0054a068 movss xmm3, dword ptr [0xb6ac40]
0054a070 movaps xmm2, xmm0
0054a073 comiss xmm2, dword ptr [0xb6ab88]
0054a07a jbe 0x54a090
0054a07c mov eax, dword ptr [ebx + 8]
0054a07f subss xmm2, xmm3
0054a083 movss dword ptr [eax], xmm2
0054a087 xor eax, eax
0054a089 pop ebp
0054a08a mov esp, ebx
0054a08c pop ebx
0054a08d ret 4
0054a090 movss xmm0, dword ptr [0xb6af74]
0054a098 comiss xmm0, xmm2
0054a09b jbe 0x54a0a1
0054a09d addss xmm2, xmm3
0054a0a1 mov eax, dword ptr [ebx + 8]
0054a0a4 movss dword ptr [eax], xmm2
0054a0a8 xor eax, eax
0054a0aa pop ebp
0054a0ab mov esp, ebx
0054a0ad pop ebx
0054a0ae ret 4
