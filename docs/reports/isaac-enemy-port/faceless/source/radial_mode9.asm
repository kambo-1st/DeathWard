006a2e74 mov eax, dword ptr [ebx + 0xc]
006a2e77 movss xmm2, dword ptr [0xb6a914]
006a2e7f mov edi, dword ptr [ebx + 0x14]
006a2e82 movss xmm0, dword ptr [eax + 4]
006a2e87 addss xmm0, dword ptr [0xb6a480]
006a2e8f movss xmm1, dword ptr [edi + 0x18]
006a2e94 cvttss2si ecx, xmm0
006a2e98 mov dword ptr [ebp - 0x20], ecx
006a2e9b movd xmm0, ecx
006a2e9f cvtdq2ps xmm0, xmm0
006a2ea2 divss xmm2, xmm0
006a2ea6 movss xmm0, dword ptr [eax]
006a2eaa movss dword ptr [ebp - 0x2c], xmm2
006a2eaf movss dword ptr [ebp - 0x1c], xmm0
006a2eb4 test ecx, ecx
006a2eb6 jle 0x6a301f
006a2ebc nop dword ptr [eax]
006a2ec0 movaps xmm0, xmm2
006a2ec3 addss xmm1, xmm0
006a2ec7 movaps xmm0, xmm1
006a2eca movss dword ptr [ebp - 0x24], xmm1
006a2ecf call 0x411fe0
006a2ed4 mulss xmm0, dword ptr [ebp - 0x1c]
006a2ed9 movss dword ptr [ebp - 0x18], xmm0
006a2ede movss dword ptr [ebp - 0x38], xmm0
006a2ee3 movss xmm0, dword ptr [ebp - 0x24]
006a2ee8 call 0x412010
006a2eed movaps xmm2, xmm0
006a2ef0 movss xmm0, dword ptr [edi + 0x70]
006a2ef5 ucomiss xmm0, dword ptr [0xc02fec]
006a2efc mulss xmm2, dword ptr [ebp - 0x1c]
006a2f01 lahf 
006a2f02 movss dword ptr [ebp - 0x28], xmm0
006a2f07 movss dword ptr [ebp - 0x34], xmm2
006a2f0c test ah, 0x44
006a2f0f jp 0x6a2f23
006a2f11 movss xmm0, dword ptr [edi + 0x74]
006a2f16 ucomiss xmm0, dword ptr [0xc02ff0]
006a2f1d lahf 
006a2f1e test ah, 0x44
006a2f21 jnp 0x6a2f87
006a2f23 movss xmm0, dword ptr [ebp - 0x18]
006a2f28 movaps xmm1, xmm2
006a2f2b mulss xmm0, xmm0
006a2f2f mulss xmm1, xmm2
006a2f33 addss xmm0, xmm1
006a2f37 call 0x4228c0
006a2f3c comiss xmm0, dword ptr [0xb6a18c]
006a2f43 jbe 0x6a2f69
006a2f45 movss xmm1, dword ptr [0xb6a614]
006a2f4d divss xmm1, xmm0
006a2f51 movaps xmm0, xmm1
006a2f54 mulss xmm0, dword ptr [ebp - 0x18]
006a2f59 movss dword ptr [ebp - 0x18], xmm0
006a2f5e movss xmm0, dword ptr [ebp - 0x34]
006a2f63 mulss xmm0, xmm1
006a2f67 jmp 0x6a2f6e
006a2f69 movss xmm0, dword ptr [ebp - 0x34]
006a2f6e movss xmm1, dword ptr [ebp - 0x28]
006a2f73 mulss xmm0, dword ptr [edi + 0x74]
006a2f78 mulss xmm1, dword ptr [ebp - 0x18]
006a2f7d addss xmm0, xmm1
006a2f81 comiss xmm0, dword ptr [edi + 0x78]
006a2f85 jbe 0x6a3006
006a2f87 call 0x6c3d90
006a2f8c mov ecx, dword ptr [ebx + 8]
006a2f8f push 0
006a2f91 push 0xbeabf4
006a2f96 push 0xbeab18
006a2f9b movss xmm0, dword ptr [ecx]
006a2f9f addss xmm0, dword ptr [edi + 0x60]
006a2fa4 push 0
006a2fa6 push eax
006a2fa7 push 0
006a2fa9 push dword ptr [ebp - 0x14]
006a2fac lea eax, [ebp - 0x38]
006a2faf movss dword ptr [ebp - 0x40], xmm0
006a2fb4 movss xmm0, dword ptr [edi + 0x64]
006a2fb9 addss xmm0, dword ptr [ecx + 4]
006a2fbe mov ecx, dword ptr [0xbfd65c]
006a2fc4 push eax
006a2fc5 lea eax, [ebp - 0x40]
006a2fc8 push eax
006a2fc9 push dword ptr [edi + 0x94]
006a2fcf movss dword ptr [ebp - 0x3c], xmm0
006a2fd4 push 9
006a2fd6 call 0x422e20
006a2fdb push eax
006a2fdc call 0x9ec34c
006a2fe1 add esp, 0x14
006a2fe4 mov dword ptr [ebp - 0x28], eax
006a2fe7 cmp esi, dword ptr [ebp - 0x44]
006a2fea je 0x6a2ff6
006a2fec mov dword ptr [esi], eax
006a2fee add esi, 4
006a2ff1 mov dword ptr [ebp - 0x48], esi
006a2ff4 jmp 0x6a3006
006a2ff6 lea eax, [ebp - 0x28]
006a2ff9 push eax
006a2ffa push esi
006a2ffb lea ecx, [ebp - 0x4c]
006a2ffe call 0x426fb0
006a3003 mov esi, dword ptr [ebp - 0x48]
006a3006 sub dword ptr [ebp - 0x20], 1
006a300a movss xmm1, dword ptr [ebp - 0x24]
006a300f movss xmm2, dword ptr [ebp - 0x2c]
006a3014 jne 0x6a2ec0
006a301a jmp 0x6a301f
