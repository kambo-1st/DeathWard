007e7c20 push ebp
007e7c21 mov ebp, esp
007e7c23 and esp, 0xffffffc0
007e7c26 movss xmm1, dword ptr [ebp + 8]
007e7c2b sub esp, 0x38
007e7c2e xor dl, dl
007e7c30 xorps xmm0, xmm0
007e7c33 push ebx
007e7c34 push esi
007e7c35 mov esi, ecx
007e7c37 mov bl, byte ptr [esi + 8]
007e7c3a mulss xmm1, dword ptr [esi + 0xc]
007e7c3f test bl, bl
007e7c41 je 0x7e7c6a
007e7c43 mov ecx, dword ptr [esi + 4]
007e7c46 nop word ptr [eax + eax]
007e7c50 movzx eax, dl
007e7c53 lea eax, [eax + eax*2]
007e7c56 addss xmm0, dword ptr [ecx + eax*4 + 8]
007e7c5c lea eax, [ecx + eax*4]
007e7c5f comiss xmm0, xmm1
007e7c62 ja 0x7e7c9b
007e7c64 inc dl
007e7c66 cmp dl, bl
007e7c68 jb 0x7e7c50
007e7c6a mov ecx, dword ptr [esi + 4]
007e7c6d sub esp, 8
007e7c70 movss xmm0, dword ptr [ecx + 8]
007e7c75 movzx eax, word ptr [ecx + 6]
007e7c79 cvtps2pd xmm0, xmm0
007e7c7c movsd qword ptr [esp], xmm0
007e7c81 push eax
007e7c82 movzx eax, word ptr [ecx + 4]
007e7c86 push eax
007e7c87 push dword ptr [ecx]
007e7c89 push 0xb4e438
007e7c8e push 0
007e7c90 call 0x95e330
007e7c95 mov eax, dword ptr [esi + 4]
007e7c98 add esp, 0x1c
007e7c9b pop esi
007e7c9c pop ebx
007e7c9d mov esp, ebp
007e7c9f pop ebp
007e7ca0 ret 4
