004fb036 lea esi, [edi + 0x294]
004fb03c cmp eax, 0x331
004fb041 jne 0x4fb127
004fb047 cmp dword ptr [edi + 0x2c], 1
004fb04b jne 0x4fb068
004fb04d call 0x6c3d90
004fb052 push eax
004fb053 push 0
004fb055 push edi
004fb056 push 0xc02fec
004fb05b push esi
004fb05c push 0
004fb05e push 0x328
004fb063 jmp 0x4fb157
004fb068 call 0x6c3d90
004fb06d movd xmm0, eax
004fb071 cvtdq2pd xmm0, xmm0
004fb075 shr eax, 0x1f
004fb078 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
004fb081 mov eax, dword ptr [0xbfd65c]
004fb086 mov ecx, dword ptr [eax + 0x18190]
004fb08c cvtpd2ps xmm0, xmm0
004fb090 mulss xmm0, xmm2
004fb094 mulss xmm0, xmm3
004fb098 addss xmm0, xmm0
004fb09c movss dword ptr [ebp - 0x6c], xmm0
004fb0a1 movss xmm0, dword ptr [ecx + 0x7134]
004fb0a9 comiss xmm0, dword ptr [0xb6a18c]
004fb0b0 seta al
004fb0b3 movzx eax, al
004fb0b6 push eax
004fb0b7 push 1
004fb0b9 push ecx
004fb0ba mov dword ptr [esp], 0x42a00000
004fb0c1 lea eax, [ebp - 0x90]
004fb0c7 push esi
004fb0c8 push eax
004fb0c9 call 0x7cf240
004fb0ce movss xmm0, dword ptr [ebp - 0x6c]
004fb0d3 mov esi, eax
004fb0d5 call 0x411fe0
004fb0da mulss xmm0, dword ptr [0xb6a974]
004fb0e2 addss xmm0, dword ptr [esi]
004fb0e6 movss dword ptr [ebp - 0x1c], xmm0
004fb0eb movss xmm0, dword ptr [ebp - 0x6c]
004fb0f0 call 0x412010
004fb0f5 mulss xmm0, dword ptr [0xb6a974]
004fb0fd lea eax, [ebp - 0x1c]
004fb100 lea ecx, [edi + 0x294]
004fb106 mov edx, edi
004fb108 movss xmm2, dword ptr [0xb6aeb8]
004fb110 push 0
004fb112 addss xmm0, dword ptr [esi + 4]
004fb117 push eax
004fb118 movss dword ptr [ebp - 0x18], xmm0
004fb11d call 0x549d70
004fb122 add esp, 8
004fb125 jmp 0x4fb175
