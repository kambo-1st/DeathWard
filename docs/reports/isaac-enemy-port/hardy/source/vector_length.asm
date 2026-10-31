00962a00 push ebp
00962a01 mov ebp, esp
00962a03 sub esp, 8
00962a06 movss xmm1, dword ptr [ecx + 4]
00962a0b movss xmm0, dword ptr [ecx]
00962a0f mulss xmm0, xmm0
00962a13 mulss xmm1, xmm1
00962a17 addss xmm0, xmm1
00962a1b call 0x4228c0
00962a20 movss dword ptr [ebp - 4], xmm0
00962a25 fld dword ptr [ebp - 4]
00962a28 mov esp, ebp
00962a2a pop ebp
00962a2b ret 
