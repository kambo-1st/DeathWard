007327d2 push 0
007327d4 push 0xff
007327d9 call 0x73b3b0
007327de mov ecx, dword ptr [ebp - 0x428]
007327e4 add esi, eax
007327e6 push 0
007327e8 push 0x8f
007327ed call 0x73b3b0
007327f2 add eax, esi
007327f4 movd xmm0, eax
007327f8 cvtdq2ps xmm0, xmm0
007327fb mulss xmm0, dword ptr [0xb6a350]
00732803 mov ecx, dword ptr [ebp - 0x428]
00732809 push 0
0073280b push 0xa5
00732810 movss dword ptr [ebp - 0x450], xmm0
