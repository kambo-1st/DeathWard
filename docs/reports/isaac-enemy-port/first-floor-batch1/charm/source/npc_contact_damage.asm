006a606f mov eax, dword ptr [esi + 0x28]
006a6072 sub eax, 0xa
006a6075 cmp eax, 0x3dd
006a607a ja 0x6a6200
006a6080 push 0
006a6082 mov ecx, edi
006a6084 call 0x68cf40
006a6089 test al, al
006a608b je 0x6a6200
006a6091 push 0
006a6093 mov ecx, esi
006a6095 call 0x68cf40
006a609a test al, al
006a609c je 0x6a6200
006a60a2 push 0
006a60a4 push 0x100
006a60a9 mov ecx, edi
006a60ab call 0x4122f0
006a60b0 push 0
006a60b2 push 0x100
006a60b7 mov ecx, esi
006a60b9 mov byte ptr [ebp - 0xf1], al
006a60bf call 0x4122f0
006a60c4 cmp byte ptr [ebp - 0xf1], al
006a60ca jne 0x6a60e0
006a60cc cmp dword ptr [edi + 0x31c], esi
006a60d2 je 0x6a60e0
006a60d4 cmp dword ptr [edi + 0xe88], esi
006a60da jne 0x6a6200
006a60e0 movss xmm0, dword ptr [edi + 0x2e0]
006a60e8 xorps xmm1, xmm1
006a60eb comiss xmm0, xmm1
006a60ee jbe 0x6a6200
006a60f4 lea eax, [edi + 0xe50]
006a60fa push esi
006a60fb mov ecx, eax
006a60fd call 0x422d00
006a6102 test al, al
006a6104 jne 0x6a6200
006a610a push esi
006a610b lea ecx, [edi + 0xe50]
006a6111 call 0x422ce0
006a6116 movss xmm0, dword ptr [edi + 0x2dc]
006a611e addss xmm0, dword ptr [0xb6ab10]
006a6126 divss xmm0, dword ptr [0xb6aafc]
006a612e call 0x68f440
006a6133 cmp dword ptr [edi + 0x28], 0x27
006a6137 mulss xmm0, dword ptr [0xb6aa1c]
006a613f movss dword ptr [ebp - 0xf0], xmm0
006a6147 jne 0x6a615f
006a6149 cmp dword ptr [edi + 0x2c], 0x16
006a614d jne 0x6a615f
006a614f movss xmm0, dword ptr [0xb6a98c]
006a6157 movss dword ptr [ebp - 0xf0], xmm0
006a615f push 0
006a6161 push 0x20000000
006a6166 mov ecx, esi
006a6168 call 0x4122f0
006a616d test al, al
006a616f je 0x6a6195
006a6171 movss xmm0, dword ptr [ebp - 0xf0]
006a6179 mulss xmm0, dword ptr [0xb6a38c]
006a6181 movss xmm1, dword ptr [0xb6a8a0]
006a6189 minss xmm1, xmm0
006a618d movss dword ptr [ebp - 0xf0], xmm1
006a6195 push 0x100000
006a619a push 0
006a619c mov ecx, esi
006a619e call 0x4122f0
006a61a3 test al, al
006a61a5 je 0x6a61d8
006a61a7 push 0
006a61a9 push 0x20000100
006a61ae mov ecx, edi
006a61b0 call 0x4122f0
006a61b5 test al, al
006a61b7 jne 0x6a61d8
006a61b9 mov eax, dword ptr [edi]
006a61bb mov ecx, edi
006a61bd mov eax, dword ptr [eax + 0x48]
006a61c0 call eax
006a61c2 movss xmm0, dword ptr [ebp - 0xf0]
006a61ca test al, al
006a61cc jne 0x6a61e0
006a61ce mulss xmm0, dword ptr [0xb6a480]
006a61d6 jmp 0x6a61e0
006a61d8 movss xmm0, dword ptr [ebp - 0xf0]
006a61e0 push edi
006a61e1 lea ecx, [ebp - 0x38]
006a61e4 call 0x4229a0
006a61e9 mov eax, dword ptr [esi]
006a61eb lea ecx, [ebp - 0x38]
006a61ee push 0x1e
006a61f0 push ecx
006a61f1 push 0
006a61f3 push 0
006a61f5 push ecx
006a61f6 mov ecx, esi
006a61f8 movss dword ptr [esp], xmm0
006a61fd call dword ptr [eax + 0x20]
