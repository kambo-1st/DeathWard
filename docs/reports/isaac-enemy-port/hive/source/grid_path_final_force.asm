007a46bc movss xmm1, dword ptr [ebp - 0x68]
007a46c1 ucomiss xmm2, dword ptr [0xc02fec]
007a46c8 lahf 
007a46c9 test ah, 0x44
007a46cc jp 0x7a46fa
007a46ce ucomiss xmm1, dword ptr [0xc02ff0]
007a46d5 lahf 
007a46d6 test ah, 0x44
007a46d9 jp 0x7a46fa
007a46db mov eax, dword ptr [ebx]
007a46dd movss xmm0, dword ptr [eax + 0x2c4]
007a46e5 mulss xmm0, dword ptr [0xb6a588]
007a46ed movss dword ptr [eax + 0x2c4], xmm0
007a46f5 jmp 0x7a47f5
007a46fa subss xmm1, dword ptr [ebp - 0x74]
007a46ff subss xmm2, dword ptr [ebp - 0x78]
007a4704 mov esi, dword ptr [ebx]
007a4706 movaps xmm0, xmm1
007a4709 movss dword ptr [ebp - 0x68], xmm1
007a470e mulss xmm0, xmm1
007a4712 movaps xmm1, xmm2
007a4715 mulss xmm1, xmm2
007a4719 movss dword ptr [ebp - 0x54], xmm2
007a471e addss xmm0, xmm1
007a4722 call 0x4228c0
007a4727 movaps xmm2, xmm0
007a472a comiss xmm2, dword ptr [0xb6a614]
007a4731 jbe 0x7a47dd
007a4737 movss xmm0, dword ptr [ebp - 0x50]
007a473c movaps xmm1, xmm2
007a473f mulss xmm1, dword ptr [0xb6a2cc]
007a4747 mulss xmm0, dword ptr [ebp + 0xc]
007a474c movss xmm3, dword ptr [ebp - 0x54]
007a4751 movss xmm4, dword ptr [ebp - 0x68]
007a4756 minss xmm1, dword ptr [0xb6a7b0]
007a475e divss xmm3, xmm2
007a4762 divss xmm4, xmm2
007a4766 mulss xmm1, xmm0
007a476a movss xmm0, dword ptr [esi + 0x2c4]
007a4772 mulss xmm0, dword ptr [0xb6a50c]
007a477a mulss xmm3, xmm1
007a477e movss dword ptr [esi + 0x2c4], xmm0
007a4786 xorps xmm0, xmm0
007a4789 mov ecx, dword ptr [ebx]
007a478b mulss xmm4, xmm1
007a478f movss xmm2, dword ptr [ecx + 0x2c4]
007a4797 ucomiss xmm2, xmm0
007a479a lahf 
007a479b test ah, 0x44
007a479e jnp 0x7a47f5
007a47a0 movss xmm1, dword ptr [ecx + 0x2f4]
007a47a8 movaps xmm0, xmm1
007a47ab mulss xmm1, xmm4
007a47af mulss xmm0, xmm3
007a47b3 divss xmm1, xmm2
007a47b7 divss xmm0, xmm2
007a47bb addss xmm1, dword ptr [ecx + 0x2bc]
007a47c3 addss xmm0, dword ptr [ecx + 0x2b8]
007a47cb movss dword ptr [ecx + 0x2bc], xmm1
007a47d3 movss dword ptr [ecx + 0x2b8], xmm0
007a47db jmp 0x7a47f5
007a47dd movss xmm0, dword ptr [esi + 0x2c4]
007a47e5 mulss xmm0, dword ptr [0xb6a480]
007a47ed movss dword ptr [esi + 0x2c4], xmm0
