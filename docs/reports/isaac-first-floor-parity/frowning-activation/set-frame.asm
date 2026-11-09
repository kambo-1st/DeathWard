00403c00 push ebp
00403c01 mov ebp, esp
00403c03 sub esp, 8
00403c06 push esi
00403c07 push edi
00403c08 mov edi, ecx
00403c0a movss dword ptr [ebp - 4], xmm1
00403c0f sub esp, 8
00403c12 mov eax, dword ptr [edi + 4]
00403c15 mov dword ptr [esp + 4], 0
00403c1d movd xmm0, dword ptr [eax + 0x30]
00403c22 cvtdq2ps xmm0, xmm0
00403c25 movss dword ptr [esp], xmm0
00403c2a call dword ptr [0xa06550]
00403c30 fstp dword ptr [ebp - 8]
00403c33 movss xmm0, dword ptr [ebp - 8]
00403c38 add esp, 8
00403c3b minss xmm0, dword ptr [ebp - 4]
00403c40 mov ecx, edi
00403c42 mov dword ptr [edi + 0x18], 0
00403c49 movss dword ptr [edi + 0x10], xmm0
00403c4e call 0x403a90
00403c53 mov eax, dword ptr [edi + 4]
00403c56 xor esi, esi
00403c58 cmp dword ptr [eax + 0x1c], esi
00403c5b jbe 0x403c9c
00403c5d nop dword ptr [eax]
00403c60 test eax, eax
00403c62 je 0x403c6d
00403c64 test esi, esi
00403c66 js 0x403c6d
00403c68 cmp esi, dword ptr [eax + 0x1c]
00403c6b jl 0x403c7c
00403c6d push 0xa081d8
00403c72 push 3
00403c74 call 0x95e330
00403c79 add esp, 8
00403c7c mov eax, dword ptr [edi + 8]
00403c7f mov ecx, edi
00403c81 movss xmm2, dword ptr [ebp - 4]
00403c86 push esi
00403c87 mov dword ptr [eax + esi*4], 0
00403c8e call 0x403990
00403c93 mov eax, dword ptr [edi + 4]
00403c96 inc esi
00403c97 cmp esi, dword ptr [eax + 0x1c]
00403c9a jb 0x403c60
00403c9c xor esi, esi
00403c9e cmp dword ptr [eax + 0x24], esi
00403ca1 jbe 0x403cdf
00403ca3 test eax, eax
00403ca5 je 0x403cb0
00403ca7 test esi, esi
00403ca9 js 0x403cb0
00403cab cmp esi, dword ptr [eax + 0x24]
00403cae jl 0x403cbf
00403cb0 push 0xa081d8
00403cb5 push 3
00403cb7 call 0x95e330
00403cbc add esp, 8
00403cbf mov eax, dword ptr [edi + 0xc]
00403cc2 mov ecx, edi
00403cc4 movss xmm2, dword ptr [ebp - 4]
00403cc9 push esi
00403cca mov dword ptr [eax + esi*4], 0
00403cd1 call 0x403a10
00403cd6 mov eax, dword ptr [edi + 4]
00403cd9 inc esi
00403cda cmp esi, dword ptr [eax + 0x24]
00403cdd jb 0x403ca3
00403cdf pop edi
00403ce0 pop esi
00403ce1 mov esp, ebp
00403ce3 pop ebp
00403ce4 ret
