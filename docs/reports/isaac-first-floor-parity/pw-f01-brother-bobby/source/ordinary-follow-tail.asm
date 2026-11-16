005f4d7c movss xmm0, dword ptr [edi + 0x294]
005f4d84 mov ecx, dword ptr [esi + 0x360]
005f4d8a movss dword ptr [ebp - 0x1c], xmm0
005f4d8f movss xmm0, dword ptr [edi + 0x298]
005f4d97 movss dword ptr [ebp - 0x18], xmm0
005f4d9c movss xmm0, dword ptr [0xb6a9c8]
005f4da4 push 0x59
005f4da6 movss dword ptr [ebp - 0x24], xmm0
005f4dab call 0x78d4c0
005f4db0 test eax, eax
005f4db2 jle 0x5f4dc1
005f4db4 movss xmm0, dword ptr [0xb6a8f4]
005f4dbc movss dword ptr [ebp - 0x24], xmm0
005f4dc1 movss xmm1, dword ptr [esi + 0x298]
005f4dc9 subss xmm1, dword ptr [ebp - 0x18]
005f4dce movss xmm2, dword ptr [esi + 0x294]
005f4dd6 subss xmm2, dword ptr [ebp - 0x1c]
005f4ddb movaps xmm0, xmm1
005f4dde movss dword ptr [ebp - 0x38], xmm1
005f4de3 mulss xmm0, xmm1
005f4de7 movaps xmm1, xmm2
005f4dea movss dword ptr [ebp - 0x28], xmm2
005f4def mulss xmm1, xmm2
005f4df3 addss xmm0, xmm1
005f4df7 call 0x4228c0
005f4dfc movss xmm4, dword ptr [ebp - 0x24]
005f4e01 movaps xmm5, xmm0
005f4e04 comiss xmm5, dword ptr [0xb6a18c]
005f4e0b jbe 0x5f4e23
005f4e0d movaps xmm3, xmm4
005f4e10 divss xmm3, xmm5
005f4e14 movaps xmm0, xmm3
005f4e17 mulss xmm3, dword ptr [ebp - 0x38]
005f4e1c mulss xmm0, dword ptr [ebp - 0x28]
005f4e21 jmp 0x5f4e2d
005f4e23 movss xmm0, dword ptr [ebp - 0x28]
005f4e28 movss xmm3, dword ptr [ebp - 0x38]
005f4e2d comiss xmm5, xmm4
005f4e30 movss xmm1, dword ptr [ebp - 0x1c]
005f4e35 movss xmm2, dword ptr [ebp - 0x18]
005f4e3a addss xmm1, xmm0
005f4e3e addss xmm2, xmm3
005f4e42 jbe 0x5f4e7f
005f4e44 movaps xmm0, xmm5
005f4e47 subss xmm0, xmm4
005f4e4b subss xmm1, dword ptr [esi + 0x294]
005f4e53 subss xmm2, dword ptr [esi + 0x298]
005f4e5b divss xmm0, xmm5
005f4e5f mulss xmm0, dword ptr [0xb6a350]
005f4e67 mulss xmm1, xmm0
005f4e6b mulss xmm2, xmm0
005f4e6f movss dword ptr [esi + 0x2b8], xmm1
005f4e77 movss dword ptr [esi + 0x2bc], xmm2
005f4e7f movss xmm0, dword ptr [esi + 0x2c4]
005f4e87 mulss xmm0, dword ptr [0xb6a560]
005f4e8f movss dword ptr [esi + 0x2c4], xmm0
005f4e97 mov ecx, dword ptr [ebp - 0xc]
005f4e9a mov dword ptr fs:[0], ecx
005f4ea1 pop ecx
005f4ea2 pop edi
005f4ea3 pop esi
005f4ea4 mov esp, ebp
005f4ea6 pop ebp
005f4ea7 mov esp, ebx
005f4ea9 pop ebx
005f4eaa ret
