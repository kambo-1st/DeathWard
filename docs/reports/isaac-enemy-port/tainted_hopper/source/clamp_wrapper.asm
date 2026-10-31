00427710 push ebp
00427711 mov ebp, esp
00427713 movss xmm3, dword ptr [ebp + 0x10]
00427718 sub esp, 0xc
0042771b movss dword ptr [esp + 8], xmm3
00427721 movss dword ptr [esp + 4], xmm3
00427727 movss dword ptr [esp], xmm3
0042772c push dword ptr [ebp + 0xc]
0042772f push dword ptr [ebp + 8]
00427732 call 0x7cec10
00427737 mov eax, dword ptr [ebp + 8]
0042773a pop ebp
0042773b ret 0xc
