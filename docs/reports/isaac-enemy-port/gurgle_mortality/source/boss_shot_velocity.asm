006a35e8 movss xmm0, dword ptr [esp + 0xc]
006a35ee mulss xmm0, xmm0
006a35f2 addss xmm0, xmm1
006a35f6 call 0x4228c0
006a35fb comiss xmm0, dword ptr [0xb6a18c]
006a3602 jbe 0x6a3621
006a3604 movss xmm1, dword ptr [0xb6a614]
006a360c divss xmm1, xmm0
006a3610 movaps xmm0, xmm1
006a3613 mulss xmm1, dword ptr [esp + 0x10]
006a3619 mulss xmm0, dword ptr [esp + 0xc]
006a361f jmp 0x6a362d
006a3621 movss xmm0, dword ptr [esp + 0xc]
006a3627 movss xmm1, dword ptr [esp + 0x10]
006a362d mulss xmm0, dword ptr [0xb6a928]
006a3635 mulss xmm1, dword ptr [0xb6a928]
006a363d addss xmm0, dword ptr [esp + 0x20]
006a3643 addss xmm1, dword ptr [esp + 0x1c]
006a3649 movss dword ptr [esp + 0x28], xmm0
006a364f movss dword ptr [esp + 0x2c], xmm1
