0095c790 push ebp
0095c791 mov ebp, esp
0095c793 cmp byte ptr [ebp + 8], 0
0095c797 jne 0x95c7f2
0095c799 movss xmm0, dword ptr [ecx + 0xc]
0095c79e movss xmm3, dword ptr [0xb6ae44]
0095c7a6 comiss xmm0, xmm3
0095c7a9 movss xmm1, dword ptr [0xb6a614]
0095c7b1 jbe 0x95c7d0
0095c7b3 mov eax, dword ptr [ecx + 4]
0095c7b6 test eax, eax
0095c7b8 je 0x95c7c4
0095c7ba movss xmm2, dword ptr [eax + 0x2f4]
0095c7c2 jmp 0x95c7c7
0095c7c4 movaps xmm2, xmm1
0095c7c7 subss xmm0, xmm2
0095c7cb movss dword ptr [ecx + 0xc], xmm0
0095c7d0 movss xmm0, dword ptr [ecx + 0x48]
0095c7d5 comiss xmm0, xmm3
0095c7d8 jbe 0x95c7f2
0095c7da mov eax, dword ptr [ecx + 4]
0095c7dd test eax, eax
0095c7df je 0x95c7e9
0095c7e1 movss xmm1, dword ptr [eax + 0x2f4]
0095c7e9 subss xmm0, xmm1
0095c7ed movss dword ptr [ecx + 0x48], xmm0
0095c7f2 pop ebp
0095c7f3 ret 4
0095c7f6 int3 
