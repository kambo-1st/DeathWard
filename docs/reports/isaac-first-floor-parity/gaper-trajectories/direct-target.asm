007a3dfc mov al, byte ptr [ebp + 0x14]
007a3dff movss xmm3, dword ptr [0xc02fec]
007a3e07 movss xmm4, dword ptr [0xc02ff0]
007a3e0f movss dword ptr [ebp - 0x54], xmm3
007a3e14 movss dword ptr [ebp - 0x68], xmm4
007a3e19 test al, al
007a3e1b je 0x7a3e27
007a3e1d movss xmm2, dword ptr [0xb6acb8]
007a3e25 jmp 0x7a3e2f
007a3e27 movss xmm2, dword ptr [0xb6aab4]
007a3e2f cmp byte ptr [ebp - 0x22], 0
007a3e33 movss dword ptr [ebp - 0x40], xmm2
007a3e38 je 0x7a3e7a
007a3e3a test al, al
007a3e3c jne 0x7a3e7a
007a3e3e mov eax, dword ptr [ebx]
007a3e40 lea ecx, [ebp - 0x60]
007a3e43 movss xmm1, dword ptr [eax + 0x2c8]
007a3e4b movaps xmm0, xmm1
007a3e4e mulss xmm1, dword ptr [eax + 0x2cc]
007a3e56 mulss xmm0, dword ptr [eax + 0x2d0]
007a3e5e lea eax, [ebp - 0x30]
007a3e61 movss dword ptr [ebp - 0x60], xmm1
007a3e66 comiss xmm0, xmm1
007a3e69 movss dword ptr [ebp - 0x30], xmm0
007a3e6e cmovbe eax, ecx
007a3e71 addss xmm2, dword ptr [eax]
007a3e75 movss dword ptr [ebp - 0x40], xmm2
007a3e7a cmp byte ptr [ebx + 0x72c], 0
007a3e81 mov esi, dword ptr [ebp - 0x3c]
007a3e84 je 0x7a3eb4
007a3e86 movss xmm1, dword ptr [esi]
007a3e8a movss xmm0, dword ptr [esi + 4]
007a3e8f subss xmm0, dword ptr [ebp - 0x5c]
007a3e94 subss xmm1, dword ptr [ebp - 0x70]
007a3e99 mulss xmm0, xmm0
007a3e9d mulss xmm1, xmm1
007a3ea1 addss xmm0, xmm1
007a3ea5 call 0x4228c0
007a3eaa movss xmm1, dword ptr [ebp - 0x40]
007a3eaf comiss xmm1, xmm0
007a3eb2 ja 0x7a3ebc
007a3eb4 mov eax, dword ptr [ebx + 0x20]
007a3eb7 cmp eax, dword ptr [ebp - 0x44]
007a3eba jne 0x7a3f08
007a3ebc mov edx, dword ptr [ebx]
007a3ebe movss xmm2, dword ptr [esi]
007a3ec2 movss xmm1, dword ptr [esi + 4]
007a3ec7 subss xmm2, dword ptr [ebp - 0x2c]
007a3ecc cvttss2si eax, dword ptr [edx + 0x2fc]
007a3ed4 cvttss2si ecx, dword ptr [edx + 0x2f8]
007a3edc subss xmm1, dword ptr [ebp - 0x38]
007a3ee1 sub ecx, eax
007a3ee3 lea eax, [ecx + ecx*4]
007a3ee6 add eax, eax
007a3ee8 add dword ptr [ebx + 0x28], eax
007a3eeb cvttss2si eax, dword ptr [edx + 0x2fc]
007a3ef3 cvttss2si ecx, dword ptr [edx + 0x2f8]
007a3efb sub ecx, eax
007a3efd imul eax, ecx, 0x32
007a3f00 add dword ptr [ebx + 0x24], eax
007a3f03 jmp 0x7a46c1
