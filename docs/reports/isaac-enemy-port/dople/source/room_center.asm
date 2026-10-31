007ce9c0 push ebp
007ce9c1 mov ebp, esp
007ce9c3 mov eax, dword ptr [0xbfd65c]
007ce9c8 mov ecx, dword ptr [eax + 0x18190]
007ce9ce mov eax, dword ptr [ecx + 4]
007ce9d1 test eax, eax
007ce9d3 je 0x7cea48
007ce9d5 mov eax, dword ptr [eax + 0x10]
007ce9d8 test eax, eax
007ce9da je 0x7cea48
007ce9dc mov eax, dword ptr [eax + 0x48]
007ce9df sub eax, 9
007ce9e2 cmp eax, 3
007ce9e5 ja 0x7cea48
007ce9e7 jmp dword ptr [eax*4 + 0x7cea88]
007ce9ee mov eax, 0x84
007ce9f3 cdq 
007ce9f4 idiv dword ptr [ecx + 0xc]
007ce9f7 movss xmm1, dword ptr [0xb6aa3c]
007ce9ff mov ecx, eax
007cea01 mov eax, dword ptr [ebp + 8]
007cea04 movd xmm0, edx
007cea08 cvtdq2ps xmm0, xmm0
007cea0b mulss xmm0, xmm1
007cea0f addss xmm0, xmm1
007cea13 movss dword ptr [eax], xmm0
007cea17 movd xmm0, ecx
007cea1b cvtdq2ps xmm0, xmm0
007cea1e mulss xmm0, xmm1
007cea22 addss xmm0, dword ptr [0xb6ab20]
007cea2a movss dword ptr [eax + 4], xmm0
007cea2f pop ebp
007cea30 ret 4
007cea33 mov eax, 0x77
007cea38 jmp 0x7ce9f3
007cea3a mov eax, 0x148
007cea3f jmp 0x7ce9f3
007cea41 mov eax, 0x13b
007cea46 jmp 0x7ce9f3
007cea48 movss xmm0, dword ptr [ecx + 0x1c]
007cea4d subss xmm0, dword ptr [ecx + 0x14]
007cea52 mov eax, dword ptr [ebp + 8]
007cea55 mulss xmm0, dword ptr [0xb6a480]
007cea5d addss xmm0, dword ptr [ecx + 0x14]
007cea62 movss dword ptr [eax], xmm0
007cea66 movss xmm0, dword ptr [ecx + 0x20]
007cea6b subss xmm0, dword ptr [ecx + 0x18]
007cea70 mulss xmm0, dword ptr [0xb6a480]
007cea78 addss xmm0, dword ptr [ecx + 0x18]
007cea7d movss dword ptr [eax + 4], xmm0
007cea82 pop ebp
007cea83 ret 4
