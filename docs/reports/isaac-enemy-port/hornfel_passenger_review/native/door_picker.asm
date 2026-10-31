; Installed-binary disassembly; field interpretations require the source review.
004a8150 push ebp
004a8151 mov ebp, esp
004a8153 push -1
004a8155 push 0x9ee64d
004a815a mov eax, dword ptr fs:[0]
004a8160 push eax
004a8161 sub esp, 0x1c
004a8164 push ebx
004a8165 push esi
004a8166 push edi
004a8167 mov eax, dword ptr [0xbaa3b4]
004a816c xor eax, ebp
004a816e push eax
004a816f lea eax, [ebp - 0xc]
004a8172 mov dword ptr fs:[0], eax
004a8178 mov edx, dword ptr [0xbfd65c]
004a817e xor ebx, ebx
004a8180 xor esi, esi
004a8182 mov dword ptr [ebp - 0x24], ebx
004a8185 xor edi, edi
004a8187 mov dword ptr [ebp - 0x20], esi
004a818a mov dword ptr [ebp - 0x1c], edi
004a818d mov eax, dword ptr [edx + 0x18190]
004a8193 mov dword ptr [ebp - 0x18], eax
004a8196 xor ecx, ecx
004a8198 mov dword ptr [ebp - 4], edi
004a819b mov dword ptr [ebp - 0x10], ecx
004a819e cmp dword ptr [eax + 0x1264], ecx
004a81a4 jbe 0x4a82ec
004a81aa movss xmm2, dword ptr [0xb6aa3c]
004a81b2 mov eax, dword ptr [eax + 0x125c]
004a81b8 mov ecx, dword ptr [eax + ecx*4]
004a81bb mov dword ptr [ebp - 0x14], ecx
004a81be cmp dword ptr [ecx + 0x28], 0x3c7
004a81c5 jne 0x4a82ab
004a81cb cmp dword ptr [ecx + 0x31c], 0
004a81d2 jne 0x4a82ab
004a81d8 mov eax, dword ptr [ecx + 0x314]
004a81de test eax, eax
004a81e0 je 0x4a81ef
004a81e2 cmp dword ptr [eax + 0x31c], 0
004a81e9 jne 0x4a82ab
004a81ef mov ebx, dword ptr [edx + 0x18190]
004a81f5 cmp byte ptr [ebx], 0
004a81f8 je 0x4a820b
004a81fa mov eax, dword ptr [edx + 0x1a30dc]
004a8200 sub eax, dword ptr [ebx + 0x11f0]
004a8206 cmp eax, 0x1e
004a8209 jge 0x4a8282
004a820b mov eax, dword ptr [edx + 0x181ac]
004a8211 test eax, eax
004a8213 js 0x4a8282
004a8215 cmp eax, 8
004a8218 jge 0x4a8249
004a821a mov eax, dword ptr [ebx + eax*4 + 0x744]
004a8221 cdq
004a8222 idiv dword ptr [ebx + 0xc]
004a8225 movd xmm1, edx
004a8229 movd xmm0, eax
004a822d cvtdq2ps xmm1, xmm1
004a8230 cvtdq2ps xmm0, xmm0
004a8233 mulss xmm1, xmm2
004a8237 mulss xmm0, xmm2
004a823b addss xmm1, xmm2
004a823f addss xmm0, dword ptr [0xb6ab20]
004a8247 jmp 0x4a8259
004a8249 movss xmm1, dword ptr [0xc02fec]
004a8251 movss xmm0, dword ptr [0xc02ff0]
004a8259 subss xmm1, dword ptr [ecx + 0x294]
004a8261 subss xmm0, dword ptr [ecx + 0x298]
004a8269 mulss xmm1, xmm1
004a826d mulss xmm0, xmm0
004a8271 addss xmm0, xmm1
004a8275 movss xmm1, dword ptr [0xb6ad0c]
004a827d comiss xmm1, xmm0
004a8280 jae 0x4a82ab
004a8282 cmp esi, edi
004a8284 je 0x4a8290
004a8286 mov dword ptr [esi], ecx
004a8288 add esi, 4
004a828b mov dword ptr [ebp - 0x20], esi
004a828e jmp 0x4a82ab
004a8290 lea eax, [ebp - 0x14]
004a8293 push eax
004a8294 push esi
004a8295 lea ecx, [ebp - 0x24]
004a8298 call 0x426fb0
004a829d mov edi, dword ptr [ebp - 0x1c]
004a82a0 mov esi, dword ptr [ebp - 0x20]
004a82a3 movss xmm2, dword ptr [0xb6aa3c]
004a82ab mov ecx, dword ptr [ebp - 0x10]
004a82ae mov eax, dword ptr [ebp - 0x18]
004a82b1 inc ecx
004a82b2 mov edx, dword ptr [0xbfd65c]
004a82b8 mov dword ptr [ebp - 0x10], ecx
004a82bb cmp ecx, dword ptr [eax + 0x1264]
004a82c1 jb 0x4a81b2
004a82c7 mov ebx, dword ptr [ebp - 0x24]
004a82ca cmp ebx, esi
004a82cc je 0x4a82ec
004a82ce sub esi, ebx
004a82d0 sar esi, 2
004a82d3 test esi, esi
004a82d5 jne 0x4a82de
004a82d7 xor edx, edx
004a82d9 mov esi, dword ptr [ebx + edx*4]
004a82dc jmp 0x4a82ee
004a82de call 0x6c3d90
004a82e3 xor edx, edx
004a82e5 div esi
004a82e7 mov esi, dword ptr [ebx + edx*4]
004a82ea jmp 0x4a82ee
004a82ec xor esi, esi
004a82ee test ebx, ebx
004a82f0 je 0x4a8321
004a82f2 sub edi, ebx
004a82f4 mov eax, ebx
004a82f6 and edi, 0xfffffffc
004a82f9 cmp edi, 0x1000
004a82ff jb 0x4a8317
004a8301 mov ebx, dword ptr [ebx - 4]
004a8304 add edi, 0x23
004a8307 sub eax, ebx
004a8309 add eax, -4
004a830c cmp eax, 0x1f
004a830f jbe 0x4a8317
004a8311 call dword ptr [0xa065ac]
004a8317 push edi
004a8318 push ebx
004a8319 call 0x9eb08e
004a831e add esp, 8
004a8321 mov eax, esi
004a8323 mov ecx, dword ptr [ebp - 0xc]
004a8326 mov dword ptr fs:[0], ecx
004a832d pop ecx
004a832e pop edi
004a832f pop esi
004a8330 pop ebx
004a8331 mov esp, ebp
004a8333 pop ebp
004a8334 ret
