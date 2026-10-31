00544dc0 push ebp
00544dc1 mov ebp, esp
00544dc3 and esp, 0xfffffff8
00544dc6 sub esp, 0x14
00544dc9 lea eax, [esp + 8]
00544dcd push esi
00544dce push eax
00544dcf lea eax, [esp + 0x14]
00544dd3 mov esi, ecx
00544dd5 push eax
00544dd6 call 0x544ec0
00544ddb mov eax, dword ptr [0xbfd680]
00544de0 mov eax, dword ptr [eax + 0x4a264]
00544de6 and eax, 0x80000001
00544deb jns 0x544df2
00544ded dec eax
00544dee or eax, 0xfffffffe
00544df1 inc eax
00544df2 cmp dword ptr [esi + 0xab4], 8
00544df9 movss xmm3, dword ptr [0xb6a480]
00544e01 movd xmm1, eax
00544e05 mov eax, dword ptr [0xbfd65c]
00544e0a cvtdq2ps xmm1, xmm1
00544e0d movd xmm0, dword ptr [eax + 0x1a30dc]
00544e15 cvtdq2ps xmm0, xmm0
00544e18 mulss xmm1, xmm3
00544e1c addss xmm1, xmm0
00544e20 movd xmm0, dword ptr [ebp + 0xc]
00544e25 cvtdq2ps xmm0, xmm0
00544e28 addss xmm1, xmm0
00544e2c jne 0x544e38
00544e2e movss xmm2, dword ptr [esi + 0xb0c]
00544e36 jmp 0x544e40
00544e38 movss xmm2, dword ptr [esi + 0xb08]
00544e40 movss xmm0, dword ptr [esi + 0xb04]
00544e48 mulss xmm0, dword ptr [esi + 0xb00]
00544e50 mulss xmm1, xmm3
00544e54 movss dword ptr [esp + 8], xmm0
00544e5a mulss xmm1, dword ptr [0xb6a874]
00544e62 mulss xmm1, dword ptr [0xb6a260]
00544e6a subss xmm2, xmm1
00544e6e movaps xmm0, xmm2
00544e71 movss dword ptr [esp + 0xc], xmm2
00544e77 call 0x411fe0
00544e7c mulss xmm0, dword ptr [esp + 8]
00544e82 mov esi, dword ptr [ebp + 8]
00544e85 addss xmm0, dword ptr [esp + 0x10]
00544e8b movss dword ptr [esi], xmm0
00544e8f movss xmm0, dword ptr [esp + 0xc]
00544e95 call 0x412010
00544e9a mulss xmm0, dword ptr [esp + 8]
00544ea0 mov eax, esi
00544ea2 mulss xmm0, dword ptr [0xb6a580]
00544eaa addss xmm0, dword ptr [esp + 0x14]
00544eb0 movss dword ptr [esi + 4], xmm0
00544eb5 pop esi
00544eb6 mov esp, ebp
00544eb8 pop ebp
