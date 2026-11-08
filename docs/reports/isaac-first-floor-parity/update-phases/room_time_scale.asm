007a8ef0 push ebp
007a8ef1 mov ebp, esp
007a8ef3 and esp, 0xfffffff8
007a8ef6 sub esp, 0x1c
007a8ef9 movss xmm0, dword ptr [0xb6a614]
007a8f01 push ebx
007a8f02 push esi
007a8f03 mov esi, dword ptr [ebp + 0xc]
007a8f06 mov dword ptr [esp + 0x14], ecx
007a8f0a movss dword ptr [esp + 0xc], xmm0
007a8f10 push edi
007a8f11 test esi, esi
007a8f13 je 0x7a8f1f
007a8f15 cmp dword ptr [esi + 0x28], 1
007a8f19 je 0x7a9002
007a8f1f mov ecx, dword ptr [0xbfd65c]
007a8f25 push 1
007a8f27 add ecx, 0x1ba40
007a8f2d push ecx
007a8f2e push 0xe8
007a8f33 call 0x91d340
007a8f38 test eax, eax
007a8f3a je 0x7a8f4a
007a8f3c movss xmm0, dword ptr [0xb6a560]
007a8f44 movss dword ptr [esp + 0x10], xmm0
007a8f4a mov ebx, dword ptr [0xbfd65c]
007a8f50 lea eax, [esp + 0x14]
007a8f54 mov edi, dword ptr [ebx + 0x1bb58]
007a8f5a lea ecx, [ebx + 0x1bb58]
007a8f60 push eax
007a8f61 lea eax, [esp + 0x20]
007a8f65 mov dword ptr [esp + 0x18], 0x4d
007a8f6d push eax
007a8f6e call 0x4206b0
007a8f73 mov eax, dword ptr [esp + 0x24]
007a8f77 cmp byte ptr [eax + 0xd], 0
007a8f7b jne 0x7a9002
007a8f81 cmp dword ptr [eax + 0x10], 0x4d
007a8f85 jg 0x7a9002
007a8f87 cmp eax, edi
007a8f89 je 0x7a9002
007a8f8b push 0
007a8f8d mov ecx, ebx
007a8f8f call 0x412750
007a8f94 mov dword ptr [esp + 0x14], 0x3ca3d70a
007a8f9c movss xmm0, dword ptr [eax + 0x2b8]
007a8fa4 movss xmm1, dword ptr [eax + 0x2bc]
007a8fac mulss xmm0, xmm0
007a8fb0 mulss xmm1, xmm1
007a8fb4 addss xmm0, xmm1
007a8fb8 call 0x4228c0
007a8fbd divss xmm0, dword ptr [0xb6a8d0]
007a8fc5 lea eax, [esp + 0x14]
007a8fc9 lea ecx, [esp + 0x10]
007a8fcd movss xmm1, dword ptr [0xb6a234]
007a8fd5 comiss xmm1, xmm0
007a8fd8 movss dword ptr [esp + 0x10], xmm0
007a8fde movss xmm0, dword ptr [0xb6a740]
007a8fe6 cmovbe eax, ecx
007a8fe9 movss xmm1, dword ptr [eax]
007a8fed comiss xmm1, xmm0
007a8ff0 ja 0x7a8ff8
007a8ff2 movss xmm0, xmm1
007a8ff6 jmp 0x7a8ffc
007a8ff8 movss xmm0, xmm0
007a8ffc movss dword ptr [esp + 0x10], xmm0
007a9002 call 0x6d9c60
007a9007 xor ecx, ecx
007a9009 dec eax
007a900a test eax, eax
007a900c push 0x2a5
007a9011 cmovg ecx, eax
007a9014 movd xmm0, ecx
007a9018 mov ecx, dword ptr [esp + 0x1c]
007a901c cvtdq2ps xmm0, xmm0
007a901f add ecx, 0x71f4
007a9025 mulss xmm0, dword ptr [0xb6a2cc]
007a902d addss xmm0, dword ptr [esp + 0x14]
007a9033 movss dword ptr [esp + 0x14], xmm0
007a9039 call 0x88b7c0
007a903e mov edi, eax
007a9040 test edi, edi
007a9042 je 0x7a9127
007a9048 test esi, esi
007a904a je 0x7a90c2
007a904c cmp dword ptr [esi + 0x28], 1
007a9050 jne 0x7a90c2
007a9052 push 0
007a9054 push 0x2a5
007a9059 mov ecx, esi
007a905b call 0x73af30
007a9060 test al, al
007a9062 je 0x7a9127
007a9068 movd xmm1, dword ptr [edi + 8]
007a906d lea eax, [esp + 0x18]
007a9071 cvtdq2ps xmm1, xmm1
007a9074 mov dword ptr [esp + 0x18], 0
007a907c lea ecx, [esp + 0x14]
007a9080 xorps xmm0, xmm0
007a9083 subss xmm1, xmm0
007a9087 divss xmm1, dword ptr [0xb6aae4]
007a908f comiss xmm0, xmm1
007a9092 movss dword ptr [esp + 0x14], xmm1
007a9098 movss xmm1, dword ptr [0xb6a614]
007a90a0 cmovbe eax, ecx
007a90a3 movss xmm0, dword ptr [eax]
007a90a7 comiss xmm0, xmm1
007a90aa ja 0x7a90b2
007a90ac movss xmm0, xmm0
007a90b0 jmp 0x7a90b6
007a90b2 movss xmm0, xmm1
007a90b6 addss xmm0, xmm1
007a90ba mulss xmm0, dword ptr [esp + 0x10]
007a90c0 jmp 0x7a912d
007a90c2 movd xmm1, dword ptr [edi + 8]
007a90c7 lea eax, [esp + 0x18]
007a90cb cvtdq2ps xmm1, xmm1
007a90ce mov dword ptr [esp + 0x18], 0
007a90d6 lea ecx, [esp + 0x14]
007a90da xorps xmm0, xmm0
007a90dd subss xmm1, xmm0
007a90e1 divss xmm1, dword ptr [0xb6aae4]
007a90e9 comiss xmm0, xmm1
007a90ec movss dword ptr [esp + 0x14], xmm1
007a90f2 movss xmm1, dword ptr [0xb6a614]
007a90fa cmovbe eax, ecx
007a90fd movss xmm0, dword ptr [eax]
007a9101 comiss xmm0, xmm1
007a9104 ja 0x7a910c
007a9106 movss xmm0, xmm0
007a910a jmp 0x7a9110
007a910c movss xmm0, xmm1
007a9110 subss xmm1, xmm0
007a9114 mulss xmm1, dword ptr [esp + 0x10]
007a911a maxss xmm1, dword ptr [0xb6a234]
007a9122 movaps xmm0, xmm1
007a9125 jmp 0x7a912d
007a9127 movss xmm0, dword ptr [esp + 0x10]
007a912d mov eax, dword ptr [0xbfd65c]
007a9132 cmp dword ptr [eax + 0x1c319c], 0x16
007a9139 je 0x7a914a
007a913b mov eax, dword ptr [eax + 0x18190]
007a9141 cmp dword ptr [eax + 0x1210], 2
007a9148 jne 0x7a9152
007a914a mulss xmm0, dword ptr [0xb6a6cc]
007a9152 pop edi
007a9153 pop esi
007a9154 pop ebx
007a9155 mov esp, ebp
007a9157 pop ebp
007a9158 ret 8
