005183a5 comiss xmm5, dword ptr [edi + 0x2b8]
005183ac seta al
005183af mov byte ptr [edi + 0x13c], al
005183b5 movss xmm0, dword ptr [edi + 0x2c4]
005183bd mulss xmm0, dword ptr [0xb6a4c4]
005183c5 movss dword ptr [edi + 0x2c4], xmm0
