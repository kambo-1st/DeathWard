00962ac0 push ebp
00962ac1 mov ebp, esp
00962ac3 mov edx, dword ptr [ebp + 0xc]
00962ac6 movss xmm0, dword ptr [ecx]
00962aca mov eax, dword ptr [ebp + 8]
00962acd subss xmm0, dword ptr [edx]
00962ad1 movss dword ptr [eax], xmm0
00962ad5 movss xmm0, dword ptr [ecx + 4]
00962ada subss xmm0, dword ptr [edx + 4]
00962adf movss dword ptr [eax + 4], xmm0
00962ae4 pop ebp
00962ae5 ret 8
