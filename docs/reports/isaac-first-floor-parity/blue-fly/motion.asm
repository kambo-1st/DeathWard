005f7539 movss xmm1, dword ptr [esi + 0x290]
005f7541 subss xmm1, dword ptr [esi + 0x298]
005f7549 movss xmm2, dword ptr [esi + 0x28c]
005f7551 subss xmm2, dword ptr [esi + 0x294]
005f7559 movaps xmm0, xmm1
005f755c movss dword ptr [esp + 0x10], xmm1
005f7562 mulss xmm0, xmm1
005f7566 movaps xmm1, xmm2
005f7569 movss dword ptr [esp + 8], xmm2
005f756f mulss xmm1, xmm2
005f7573 addss xmm0, xmm1
005f7577 call 0x4228c0
005f757c comiss xmm0, dword ptr [0xb6a2cc]
005f7583 jb 0x5f759e
005f7585 movaps xmm1, xmm0
005f7588 mulss xmm1, dword ptr [0xb6a304]
005f7590 minss xmm1, dword ptr [0xb6a7b0]
005f7598 divss xmm1, xmm0
005f759c jmp 0x5f75a1
005f759e xorps xmm1, xmm1
005f75a1 movss xmm0, dword ptr [esp + 8]
005f75a7 mulss xmm0, xmm1
005f75ab addss xmm0, dword ptr [esi + 0x2b8]
005f75b3 movss dword ptr [esi + 0x2b8], xmm0
005f75bb movss xmm0, dword ptr [esp + 0x10]
005f75c1 mulss xmm0, xmm1
005f75c5 addss xmm0, dword ptr [esi + 0x2bc]
005f75cd movss dword ptr [esi + 0x2bc], xmm0
005f75d5 movss xmm0, dword ptr [esi + 0x2c4]
005f75dd mulss xmm0, dword ptr [0xb6a560]
005f75e5 movss dword ptr [esi + 0x2c4], xmm0
