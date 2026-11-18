00739bd1 lea esi, [edi + 0x15fc]
00739bd7 push 0x12
00739bd9 mov ecx, esi
00739bdb call 0x430970
00739be0 push 0x11
00739be2 mov ecx, esi
00739be4 mov edi, dword ptr [eax]
00739be6 call 0x430970
00739beb sub edi, dword ptr [eax]
00739bed movd xmm0, edi
00739bf1 mov edi, dword ptr [ebp - 0x428]
00739bf7 cvtdq2ps xmm0, xmm0
00739bfa cmp byte ptr [edi + 0x1f1c], 0
00739c01 movss dword ptr [ebp - 0x42c], xmm0
