005f6d7a cmp byte ptr [ebp + 0x10], 0
005f6d7e movss xmm4, dword ptr [0xb6ac60]
005f6d86 jne 0x5f6d92
005f6d88 cmp edi, dword ptr [esp + 0x14]
005f6d8c jne 0x5f6d92
005f6d8e addss xmm1, xmm4
005f6d92 cmp byte ptr [esp + 0x2c], 0
005f6d97 movss xmm2, dword ptr [0xb6acc0]
005f6d9f subss xmm2, xmm0
005f6da3 maxss xmm2, xmm3
005f6da7 addss xmm2, xmm1
005f6dab je 0x5f6dc6
005f6dad movaps xmm0, xmm4
005f6db0 subss xmm0, dword ptr [esp + 0x30]
005f6db6 maxss xmm0, xmm3
005f6dba mulss xmm0, dword ptr [0xb6a864]
005f6dc2 addss xmm2, xmm0
005f6dc6 cmp byte ptr [esp + 0x4c], 0
005f6dcb je 0x5f6de0
005f6dcd movaps xmm0, xmm4
005f6dd0 subss xmm0, dword ptr [edi + 0x2d8]
005f6dd8 maxss xmm0, xmm3
005f6ddc addss xmm2, xmm0
