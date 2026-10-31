00962bb0 push ebp
00962bb1 mov ebp, esp
00962bb3 mov eax, dword ptr [ebp + 8]
00962bb6 movss xmm0, dword ptr [eax]
00962bba mulss xmm0, dword ptr [ecx]
00962bbe movss dword ptr [ecx], xmm0
00962bc2 movss xmm0, dword ptr [ecx + 4]
00962bc7 mulss xmm0, dword ptr [eax]
00962bcb mov eax, ecx
00962bcd movss dword ptr [ecx + 4], xmm0
00962bd2 pop ebp
00962bd3 ret 4
