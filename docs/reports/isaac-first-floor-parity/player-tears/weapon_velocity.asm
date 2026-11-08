0095a2a8 lea eax, [ebp - 0x13c]
0095a2ae movss xmm0, dword ptr [ebp - 0x13c]
0095a2b6 mov ecx, esi
0095a2b8 mulss xmm0, dword ptr [0xb6a974]
0095a2c0 push eax
0095a2c1 lea eax, [ebp - 0x20c]
0095a2c7 push eax
0095a2c8 movss dword ptr [ebp - 0xc8], xmm0
0095a2d0 movss xmm0, dword ptr [ebp - 0x138]
0095a2d8 mulss xmm0, dword ptr [0xb6a974]
0095a2e0 movss dword ptr [ebp - 0xb8], xmm0
0095a2e8 call 0x945190
0095a2ed movss xmm0, dword ptr [ebp - 0xc8]
0095a2f5 addss xmm0, dword ptr [eax]
0095a2f9 movss dword ptr [ebp - 0xc8], xmm0
0095a301 movss dword ptr [ebp - 0x14c], xmm0
0095a309 movss xmm0, dword ptr [ebp - 0xb8]
0095a311 addss xmm0, dword ptr [eax + 4]
0095a316 mov eax, dword ptr [ebp - 0xe0]
0095a31c movss dword ptr [ebp - 0xb8], xmm0
0095a324 movss dword ptr [ebp - 0x148], xmm0
