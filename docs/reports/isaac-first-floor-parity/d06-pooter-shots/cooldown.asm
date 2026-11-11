004f5d59 mov edx, dword ptr [esi + 0xaf0]
004f5d5f test edx, edx
004f5d61 jle 0x4f5dc5
004f5d63 movss xmm0, dword ptr [esi + 0x2c4]
004f5d6b mulss xmm0, dword ptr [0xb6a560]
004f5d73 cvttss2si eax, dword ptr [esi + 0x2fc]
004f5d7b cvttss2si ecx, dword ptr [esi + 0x2f8]
004f5d83 movss dword ptr [esi + 0x2c4], xmm0
004f5d8b movss xmm0, dword ptr [esi + 0xb00]
004f5d93 sub ecx, eax
004f5d95 mulss xmm0, dword ptr [0xb6a50c]
004f5d9d add ecx, edx
004f5d9f mov dword ptr [esi + 0xaf0], ecx
004f5da5 movss dword ptr [esi + 0xb00], xmm0
004f5dad movss xmm0, dword ptr [esi + 0xb04]
004f5db5 mulss xmm0, dword ptr [0xb6a50c]
004f5dbd movss dword ptr [esi + 0xb04], xmm0
