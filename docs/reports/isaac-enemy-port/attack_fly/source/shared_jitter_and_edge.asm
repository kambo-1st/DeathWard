004f6d0e mov edi, dword ptr [0xbfd65c]
004f6d14 mov ecx, dword ptr [edi + 0x1a30dc]
004f6d1a mov eax, ecx
004f6d1c and eax, 0x80000003
004f6d21 jns 0x4f6d28
004f6d23 dec eax
004f6d24 or eax, 0xfffffffc
004f6d27 inc eax
004f6d28 cmp eax, 1
004f6d2b jne 0x4f6d89
004f6d2d lea eax, [esp + 0xc]
004f6d31 push eax
004f6d32 call 0x659290
004f6d37 add esp, 4
004f6d3a movss xmm2, dword ptr [eax + 4]
004f6d3f movss xmm0, dword ptr [eax]
004f6d43 mulss xmm0, dword ptr [0xb6a4c4]
004f6d4b mulss xmm2, dword ptr [0xb6a4c4]
004f6d53 addss xmm0, dword ptr [esi + 0xb00]
004f6d5b addss xmm2, dword ptr [esi + 0xb04]
004f6d63 mulss xmm0, dword ptr [0xb6a434]
004f6d6b mulss xmm2, dword ptr [0xb6a434]
004f6d73 movss dword ptr [esi + 0xb00], xmm0
004f6d7b movss dword ptr [esi + 0xb04], xmm2
004f6d83 mov ecx, dword ptr [edi + 0x1a30dc]
004f6d89 mov eax, ecx
004f6d8b mov ecx, 3
004f6d90 cdq 
004f6d91 idiv ecx
004f6d93 cmp edx, 2
004f6d96 jne 0x4f6e78
004f6d9c cmp dword ptr [esi + 0x34], 0x43
004f6da0 je 0x4f6e2e
004f6da6 movss xmm2, dword ptr [esi + 0x298]
004f6dae movss xmm0, dword ptr [0xb6abd0]
004f6db6 comiss xmm0, xmm2
004f6db9 movss xmm1, dword ptr [0xb6a278]
004f6dc1 jbe 0x4f6dd1
004f6dc3 movss xmm0, dword ptr [esi + 0xb04]
004f6dcb addss xmm0, xmm1
004f6dcf jmp 0x4f6de6
004f6dd1 comiss xmm2, dword ptr [0xb6ac6c]
004f6dd8 jbe 0x4f6dee
004f6dda movss xmm0, dword ptr [esi + 0xb04]
004f6de2 subss xmm0, xmm1
004f6de6 movss dword ptr [esi + 0xb04], xmm0
004f6dee movss xmm2, dword ptr [esi + 0x294]
004f6df6 comiss xmm2, dword ptr [0xb6ac94]
004f6dfd jbe 0x4f6e0d
004f6dff movss xmm0, dword ptr [esi + 0xb00]
004f6e07 subss xmm0, xmm1
004f6e0b jmp 0x4f6e26
004f6e0d movss xmm0, dword ptr [0xb6aad4]
004f6e15 comiss xmm0, xmm2
004f6e18 jbe 0x4f6e2e
004f6e1a movss xmm0, dword ptr [esi + 0xb00]
004f6e22 addss xmm0, xmm1
004f6e26 movss dword ptr [esi + 0xb00], xmm0
004f6e2e movss xmm0, dword ptr [esi + 0xb00]
004f6e36 lea eax, [esp + 0x18]
004f6e3a addss xmm0, xmm0
004f6e3e mov ecx, esi
004f6e40 push 0
004f6e42 push eax
004f6e43 movss dword ptr [esp + 0x20], xmm0
004f6e49 movss xmm0, dword ptr [esi + 0xb04]
004f6e51 addss xmm0, xmm0
004f6e55 movss dword ptr [esp + 0x24], xmm0
004f6e5b call 0x422b60
004f6e60 movss xmm0, dword ptr [esi + 0x2c4]
004f6e68 mulss xmm0, dword ptr [0xb6a4c4]
004f6e70 movss dword ptr [esi + 0x2c4], xmm0
004f6e78 cmp dword ptr [esi + 0x28], 0xf9
004f6e7f jne 0x4f6ebc
004f6e81 cmp byte ptr [esi + 0x16b], 0
004f6e88 je 0x4f6ebc
004f6e8a lea ecx, [esp + 0x90]
004f6e91 mov dword ptr [esp + 0x18], 0x41000000
004f6e99 mov dword ptr [esp + 0x1c], 0x40c00000
004f6ea1 call 0x430d70
004f6ea6 push eax
004f6ea7 push 9
004f6ea9 lea eax, [esp + 0x20]
004f6ead mov ecx, esi
004f6eaf push eax
004f6eb0 lea eax, [esi + 0x294]
004f6eb6 push eax
004f6eb7 call 0x6a1a20
004f6ebc mov ecx, dword ptr [esp + 0x1e4]
004f6ec3 pop edi
004f6ec4 pop esi
004f6ec5 xor ecx, esp
004f6ec7 call 0x9eacd7
004f6ecc mov esp, ebp
004f6ece pop ebp
004f6ecf ret 
004f6ed0 int3 
004f6ed1 int3 
004f6ed2 int3 
004f6ed3 int3 
004f6ed4 int3 
004f6ed5 int3 
004f6ed6 int3 
004f6ed7 int3 
004f6ed8 int3 
004f6ed9 int3 
004f6eda int3 
004f6edb int3 
004f6edc int3 
004f6edd int3 
004f6ede int3 
004f6edf int3 
