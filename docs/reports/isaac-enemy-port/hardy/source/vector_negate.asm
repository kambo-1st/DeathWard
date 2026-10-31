00962b20 push ebp
00962b21 mov ebp, esp
00962b23 mov eax, dword ptr [ebp + 8]
00962b26 movss xmm0, dword ptr [ecx]
00962b2a xorps xmm0, xmmword ptr [0xb6c9b0]
00962b31 movss dword ptr [eax], xmm0
00962b35 movss xmm0, dword ptr [ecx + 4]
00962b3a xorps xmm0, xmmword ptr [0xb6c9b0]
00962b41 movss dword ptr [eax + 4], xmm0
00962b46 pop ebp
00962b47 ret 4
