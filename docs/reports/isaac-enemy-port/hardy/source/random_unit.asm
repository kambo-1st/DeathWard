00659290 push ebp
00659291 mov ebp, esp
00659293 sub esp, 8
00659296 push esi
00659297 call 0x6c3d90
0065929c movd xmm0, eax
006592a0 cvtdq2pd xmm0, xmm0
006592a4 shr eax, 0x1f
006592a7 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
006592b0 cvtpd2ps xmm0, xmm0
006592b4 mulss xmm0, dword ptr [0xb6a19c]
006592bc mulss xmm0, dword ptr [0xb6a874]
006592c4 addss xmm0, xmm0
006592c8 movss dword ptr [ebp - 4], xmm0
006592cd call 0x411fe0
006592d2 mov esi, dword ptr [ebp + 8]
006592d5 movss dword ptr [esi], xmm0
006592d9 movss xmm0, dword ptr [ebp - 4]
006592de call 0x412010
006592e3 movss dword ptr [esi + 4], xmm0
006592e8 mov eax, esi
006592ea pop esi
006592eb mov esp, ebp
006592ed pop ebp
006592ee ret 
