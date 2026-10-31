00544ec0 push ebp
00544ec1 mov ebp, esp
00544ec3 mov edx, dword ptr [ecx + 0x314]
00544ec9 sub esp, 0xc
00544ecc push ebx
00544ecd push esi
00544ece push edi
00544ecf test edx, edx
00544ed1 je 0x544f03
00544ed3 mov eax, dword ptr [ebp + 0xc]
00544ed6 test eax, eax
00544ed8 je 0x544ee6
00544eda mov dword ptr [eax], 0
00544ee0 mov edx, dword ptr [ecx + 0x314]
00544ee6 mov eax, dword ptr [ebp + 8]
00544ee9 mov ecx, dword ptr [edx + 0x294]
00544eef mov edx, dword ptr [edx + 0x298]
00544ef5 mov dword ptr [eax], ecx
00544ef7 mov dword ptr [eax + 4], edx
00544efa pop edi
00544efb pop esi
00544efc pop ebx
00544efd mov esp, ebp
00544eff pop ebp
00544f00 ret 8
00544f03 mov edi, dword ptr [0xbfd65c]
00544f09 xor edx, edx
00544f0b movss xmm3, dword ptr [0xc02fec]
00544f13 xorps xmm1, xmm1
00544f16 movss xmm2, dword ptr [0xc02ff0]
00544f1e movss dword ptr [ebp - 4], xmm1
00544f23 mov esi, dword ptr [edi + 0x1ba50]
00544f29 mov eax, esi
00544f2b mov edi, dword ptr [edi + 0x1ba54]
00544f31 cmp eax, edi
00544f33 je 0x544f5e
00544f35 mov ecx, dword ptr [eax]
00544f37 cmp dword ptr [ecx + 0x2c], 0
00544f3b jne 0x544f57
00544f3d cmp dword ptr [ecx + 0x130c], 0x23
00544f44 je 0x544f57
00544f46 addss xmm3, dword ptr [ecx + 0x294]
00544f4e addss xmm2, dword ptr [ecx + 0x298]
00544f56 inc edx
00544f57 add eax, 4
00544f5a cmp eax, edi
00544f5c jne 0x544f35
00544f5e movd xmm0, edx
00544f62 cvtdq2ps xmm0, xmm0
00544f65 mov ebx, dword ptr [ebp + 0xc]
00544f68 divss xmm3, xmm0
00544f6c divss xmm2, xmm0
00544f70 movss dword ptr [ebp - 0xc], xmm3
00544f75 movss dword ptr [ebp - 8], xmm2
00544f7a test ebx, ebx
00544f7c je 0x544fe3
00544f7e cmp edx, 1
00544f81 jle 0x544fdf
00544f83 cmp esi, edi
00544f85 je 0x544fdf
00544f87 mov eax, dword ptr [esi]
00544f89 cmp dword ptr [eax + 0x2c], 0
00544f8d jne 0x544fd8
00544f8f cmp dword ptr [eax + 0x130c], 0x23
00544f96 je 0x544fd8
00544f98 movss xmm1, dword ptr [eax + 0x294]
00544fa0 movss xmm0, dword ptr [eax + 0x298]
00544fa8 subss xmm1, xmm3
00544fac subss xmm0, xmm2
00544fb0 mulss xmm1, xmm1
00544fb4 mulss xmm0, xmm0
00544fb8 addss xmm0, xmm1
00544fbc call 0x4228c0
00544fc1 maxss xmm0, dword ptr [ebp - 4]
00544fc6 movss xmm2, dword ptr [ebp - 8]
00544fcb movss xmm3, dword ptr [ebp - 0xc]
00544fd0 movaps xmm1, xmm0
00544fd3 movss dword ptr [ebp - 4], xmm1
00544fd8 add esi, 4
00544fdb cmp esi, edi
00544fdd jne 0x544f87
00544fdf movss dword ptr [ebx], xmm1
00544fe3 mov eax, dword ptr [ebp + 8]
00544fe6 pop edi
00544fe7 pop esi
00544fe8 pop ebx
00544fe9 movss dword ptr [eax], xmm3
00544fed movss dword ptr [eax + 4], xmm2
00544ff2 mov esp, ebp
00544ff4 pop ebp
