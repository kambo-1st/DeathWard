00545000 push ebp
00545001 mov ebp, esp
00545003 sub esp, 0x18
00545006 push esi
00545007 mov esi, ecx
00545009 push edi
0054500a cmp dword ptr [esi + 0x30], 0
0054500e jne 0x545217
00545014 push 0
00545016 lea eax, [ebp - 8]
00545019 push eax
0054501a call 0x544dc0
0054501f movss xmm1, dword ptr [esi + 0x294]
00545027 movss xmm0, dword ptr [esi + 0x298]
0054502f subss xmm0, dword ptr [ebp - 4]
00545034 movss dword ptr [ebp - 0xc], xmm1
00545039 subss xmm1, dword ptr [ebp - 8]
0054503e mulss xmm0, xmm0
00545042 mulss xmm1, xmm1
00545046 addss xmm0, xmm1
0054504a call 0x4228c0
0054504f movss xmm1, dword ptr [0xb6a9c8]
00545057 comiss xmm1, xmm0
0054505a jbe 0x54506f
0054505c cmp dword ptr [esi + 0xaf4], 1
00545063 jne 0x54506f
00545065 mov dword ptr [esi + 0xaf4], 0
0054506f mov eax, dword ptr [esi + 0x314]
00545075 movss xmm4, dword ptr [0xc02fec]
0054507d movss xmm5, dword ptr [0xc02ff0]
00545085 test eax, eax
00545087 je 0x5450bb
00545089 movss xmm0, dword ptr [eax + 0x2c4]
00545091 movss xmm1, dword ptr [eax + 0x2b8]
00545099 movss xmm3, dword ptr [eax + 0x2bc]
005450a1 divss xmm1, xmm0
005450a5 divss xmm3, xmm0
005450a9 addss xmm1, xmm1
005450ad addss xmm3, xmm3
005450b1 addss xmm1, xmm4
005450b5 addss xmm3, xmm5
005450b9 jmp 0x545128
005450bb mov ecx, dword ptr [0xbfd65c]
005450c1 xor edi, edi
005450c3 mov eax, dword ptr [ecx + 0x1ba50]
005450c9 mov ecx, dword ptr [ecx + 0x1ba54]
005450cf cmp eax, ecx
005450d1 je 0x545113
005450d3 mov edx, dword ptr [eax]
005450d5 cmp dword ptr [edx + 0x2c], 0
005450d9 jne 0x54510c
005450db movss xmm0, dword ptr [edx + 0x2c4]
005450e3 inc edi
005450e4 movss xmm1, dword ptr [edx + 0x2b8]
005450ec movss xmm2, dword ptr [edx + 0x2bc]
005450f4 divss xmm1, xmm0
005450f8 divss xmm2, xmm0
005450fc addss xmm1, xmm1
00545100 addss xmm2, xmm2
00545104 addss xmm4, xmm1
00545108 addss xmm5, xmm2
0054510c add eax, 4
0054510f cmp eax, ecx
00545111 jne 0x5450d3
00545113 movd xmm0, edi
00545117 movaps xmm1, xmm4
0054511a cvtdq2ps xmm0, xmm0
0054511d movaps xmm3, xmm5
00545120 divss xmm1, xmm0
00545124 divss xmm3, xmm0
00545128 movss xmm0, dword ptr [ebp - 0xc]
0054512d movss xmm2, dword ptr [ebp - 8]
00545132 addss xmm0, xmm1
00545136 movss dword ptr [ebp - 0x14], xmm3
0054513b movss dword ptr [ebp - 0x10], xmm1
00545140 subss xmm2, xmm0
00545144 movaps xmm0, xmm3
00545147 addss xmm0, dword ptr [esi + 0x298]
0054514f movss xmm3, dword ptr [ebp - 4]
00545154 mulss xmm2, dword ptr [0xb6a480]
0054515c subss xmm3, xmm0
00545160 movaps xmm1, xmm2
00545163 movss dword ptr [ebp - 0xc], xmm2
00545168 mulss xmm1, xmm2
0054516c mulss xmm3, dword ptr [0xb6a480]
00545174 movaps xmm0, xmm3
00545177 movss dword ptr [ebp - 4], xmm3
0054517c mulss xmm0, xmm3
00545180 addss xmm0, xmm1
00545184 call 0x4228c0
00545189 movss xmm3, dword ptr [0xb6a974]
00545191 movaps xmm1, xmm0
00545194 comiss xmm1, xmm3
00545197 jbe 0x5451e3
00545199 comiss xmm1, dword ptr [0xb6a18c]
005451a0 movss xmm2, dword ptr [ebp - 4]
005451a5 jbe 0x5451cf
005451a7 movss xmm0, dword ptr [0xb6a614]
005451af divss xmm0, xmm1
005451b3 movss xmm1, dword ptr [ebp - 0xc]
005451b8 mulss xmm2, xmm0
005451bc mulss xmm1, xmm0
005451c0 mulss xmm2, xmm3
005451c4 mulss xmm1, xmm3
005451c8 movss dword ptr [ebp - 4], xmm2
005451cd jmp 0x5451e8
005451cf movss xmm1, dword ptr [ebp - 0xc]
005451d4 mulss xmm2, xmm3
005451d8 mulss xmm1, xmm3
005451dc movss dword ptr [ebp - 4], xmm2
005451e1 jmp 0x5451e8
005451e3 movss xmm1, dword ptr [ebp - 0xc]
005451e8 movss xmm2, dword ptr [ebp - 0x14]
005451ed addss xmm1, dword ptr [ebp - 0x10]
005451f2 addss xmm2, dword ptr [ebp - 4]
005451f7 movss xmm0, dword ptr [esi + 0x2c4]
005451ff divss xmm1, xmm0
00545203 divss xmm2, xmm0
00545207 movss dword ptr [esi + 0x2b8], xmm1
0054520f movss dword ptr [esi + 0x2bc], xmm2
00545217 pop edi
00545218 pop esi
00545219 mov esp, ebp
0054521b pop ebp
0054521c ret 
