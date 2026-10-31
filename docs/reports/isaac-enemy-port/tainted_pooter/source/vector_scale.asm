00962b50 push ebp
00962b51 mov ebp, esp
00962b53 mov eax, dword ptr [ebp + 0xc]
00962b56 movss xmm1, dword ptr [eax]
00962b5a mov eax, dword ptr [ebp + 8]
00962b5d movaps xmm0, xmm1
00962b60 mulss xmm0, dword ptr [ecx]
00962b64 mulss xmm1, dword ptr [ecx + 4]
00962b69 movss dword ptr [eax], xmm0
00962b6d movss dword ptr [eax + 4], xmm1
00962b72 pop ebp
00962b73 ret 8
00962b76 int3 
00962b77 int3 
00962b78 int3 
00962b79 int3 
00962b7a int3 
00962b7b int3 
00962b7c int3 
00962b7d int3 
00962b7e int3 
00962b7f int3 
