006d90b0 push ebp
006d90b1 mov ebp, esp
006d90b3 and esp, 0xfffffff8
006d90b6 sub esp, 0x24
006d90b9 mov eax, dword ptr [0xbfd65c]
006d90be movaps xmm0, xmm1
006d90c1 push ebx
006d90c2 mulss xmm0, xmm0
006d90c6 xor ebx, ebx
006d90c8 mov dword ptr [esp + 8], ecx
006d90cc xor ecx, ecx
006d90ce mov eax, dword ptr [eax + 0x18190]
006d90d4 push esi
006d90d5 push edi
006d90d6 mov dword ptr [esp + 0x18], edx
006d90da mov dword ptr [esp + 0x1c], eax
006d90de movss dword ptr [esp + 0x14], xmm0
006d90e4 mov dword ptr [esp + 0xc], ecx
006d90e8 cmp dword ptr [eax + 0x1264], ecx
006d90ee jbe 0x6d929a
006d90f4 mov eax, dword ptr [eax + 0x125c]
006d90fa mov esi, dword ptr [eax + ebx*4]
006d90fd test edx, edx
006d90ff je 0x6d9117
006d9101 mov eax, dword ptr [edx]
006d9103 mov ecx, edx
006d9105 push esi
006d9106 mov eax, dword ptr [eax + 0x4c]
006d9109 call eax
006d910b mov ecx, dword ptr [esp + 0xc]
006d910f test al, al
006d9111 je 0x6d9285
006d9117 mov eax, dword ptr [0xbfd65c]
006d911c mov eax, dword ptr [eax + 0x1a30dc]
006d9122 sub eax, dword ptr [esi + 0x280]
006d9128 cmp eax, 1
006d912b jle 0x6d9285
006d9131 mov edi, dword ptr [esi + 0x28]
006d9134 lea eax, [edi - 0xa]
006d9137 cmp eax, 0x3dd
006d913c ja 0x6d9285
006d9142 mov eax, dword ptr [esi + 0x180]
006d9148 cmp eax, 1
006d914b je 0x6d9285
006d9151 test eax, eax
006d9153 je 0x6d9285
006d9159 cmp byte ptr [esi + 0x308], 0
006d9160 jne 0x6d9285
006d9166 cmp byte ptr [esi + 0x16b], 0
006d916d jne 0x6d9285
006d9173 push 0
006d9175 push 0x10
006d9177 mov ecx, esi
006d9179 call 0x4122f0
006d917e test al, al
006d9180 je 0x6d9196
006d9182 cmp edi, 0x322
006d9188 je 0x6d9196
006d918a cmp edi, 0x362
006d9190 jne 0x6d9281
006d9196 cmp edi, 0x21
006d9199 je 0x6d9281
006d919f cmp edi, 0x11
006d91a2 je 0x6d9281
006d91a8 cmp edi, 0x124
006d91ae je 0x6d9281
006d91b4 cmp edi, 0x375
006d91ba jne 0x6d91c2
006d91bc cmp dword ptr [esi + 0x2c], 0xa
006d91c0 jmp 0x6d91e0
006d91c2 cmp edi, 0x3c0
006d91c8 je 0x6d9281
006d91ce cmp edi, 0x3c5
006d91d4 je 0x6d9281
006d91da cmp edi, 0xf5
006d91e0 je 0x6d9281
006d91e6 mov ecx, dword ptr [esi + 0x160]
006d91ec mov eax, ecx
006d91ee and eax, 0x20000000
006d91f3 or eax, 0
006d91f6 jne 0x6d9281
006d91fc mov eax, ecx
006d91fe and eax, 0x10
006d9201 or eax, 0
006d9204 jne 0x6d9281
006d9206 cmp dword ptr [ebp + 8], eax
006d9209 je 0x6d922c
006d920b push esi
006d920c push dword ptr [esp + 0x1c]
006d9210 push dword ptr [esp + 0x18]
006d9214 call dword ptr [ebp + 8]
006d9217 mov ecx, dword ptr [esi + 0x160]
006d921d add esp, 0xc
006d9220 fstp dword ptr [esp + 0x20]
006d9224 movss xmm1, dword ptr [esp + 0x20]
006d922a jmp 0x6d9255
006d922c mov edi, dword ptr [esp + 0x10]
006d9230 movss xmm0, dword ptr [esi + 0x294]
006d9238 movss xmm1, dword ptr [esi + 0x298]
006d9240 subss xmm1, dword ptr [edi + 4]
006d9245 subss xmm0, dword ptr [edi]
006d9249 mulss xmm1, xmm1
006d924d mulss xmm0, xmm0
006d9251 addss xmm1, xmm0
006d9255 and ecx, 0x100
006d925b or ecx, 0
006d925e je 0x6d9268
006d9260 addss xmm1, dword ptr [0xb6ad88]
006d9268 movss xmm0, dword ptr [esp + 0x14]
006d926e comiss xmm0, xmm1
006d9271 jbe 0x6d9281
006d9273 mov ecx, esi
006d9275 movss dword ptr [esp + 0x14], xmm1
006d927b mov dword ptr [esp + 0xc], ecx
006d927f jmp 0x6d9285
006d9281 mov ecx, dword ptr [esp + 0xc]
006d9285 mov eax, dword ptr [esp + 0x1c]
006d9289 inc ebx
006d928a mov edx, dword ptr [esp + 0x18]
006d928e cmp ebx, dword ptr [eax + 0x1264]
006d9294 jb 0x6d90f4
006d929a pop edi
006d929b pop esi
006d929c mov eax, ecx
006d929e pop ebx
006d929f mov esp, ebp
006d92a1 pop ebp
006d92a2 ret 
