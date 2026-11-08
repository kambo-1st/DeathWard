0068a2c0 push ebp
0068a2c1 mov ebp, esp
0068a2c3 and esp, 0xfffffff8
0068a2c6 movss xmm0, dword ptr [ecx + 0x2cc]
0068a2ce movss xmm2, dword ptr [0xbc7a28]
0068a2d6 ucomiss xmm0, xmm2
0068a2d9 lahf 
0068a2da test ah, 0x44
0068a2dd jp 0x68a323
0068a2df movss xmm0, dword ptr [ecx + 0x2d0]
0068a2e7 movss xmm1, dword ptr [0xbc7a2c]
0068a2ef ucomiss xmm0, xmm1
0068a2f2 lahf 
0068a2f3 test ah, 0x44
0068a2f6 jp 0x68a323
0068a2f8 movss xmm0, dword ptr [edx + 0x2cc]
0068a300 ucomiss xmm0, xmm2
0068a303 lahf 
0068a304 test ah, 0x44
0068a307 jp 0x68a323
0068a309 movss xmm0, dword ptr [edx + 0x2d0]
0068a311 ucomiss xmm0, xmm1
0068a314 lahf 
0068a315 test ah, 0x44
0068a318 jp 0x68a323
0068a31a call 0x689cf0
0068a31f mov esp, ebp
0068a321 pop ebp
0068a322 ret 
0068a323 call 0x689980
0068a328 mov esp, ebp
0068a32a pop ebp
0068a32b ret 
