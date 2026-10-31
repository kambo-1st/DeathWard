006a3170 mov ecx, dword ptr [ebp - 0x4c]
006a3173 xorps xmm1, xmm1
006a3176 movss xmm0, dword ptr [edi + 4]
006a317b mov ecx, dword ptr [ecx + edx*4]
006a317e addss xmm0, dword ptr [ecx + 0x360]
006a3186 movss dword ptr [ecx + 0x360], xmm0
006a318e movss xmm0, dword ptr [edi + 8]
006a3193 addss xmm0, dword ptr [ecx + 0x364]
006a319b movss dword ptr [ecx + 0x364], xmm0
006a31a3 movss xmm0, dword ptr [ecx + 0x368]
006a31ab addss xmm0, dword ptr [edi + 0xc]
006a31b0 movss dword ptr [ecx + 0x368], xmm0
006a31b8 mov eax, dword ptr [edi + 0x14]
006a31bb mov dword ptr [ecx + 0x370], eax
