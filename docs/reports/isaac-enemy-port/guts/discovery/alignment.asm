00502ea0 push ebp
00502ea1 mov ebp, esp
00502ea3 sub esp, 0x14
00502ea6 mov eax, dword ptr [0xbfd65c]
00502eab push ebx
00502eac push esi
00502ead push edi
00502eae mov ebx, dword ptr [eax + 0x18190]
00502eb4 mov edi, edx
00502eb6 push ecx
00502eb7 mov dword ptr [ebp - 0x14], ecx
00502eba mov ecx, ebx
00502ebc mov dword ptr [esp], 0
00502ec3 push edi
00502ec4 call 0x7cf0a0
00502ec9 test al, al
00502ecb je 0x502f60
00502ed1 mov esi, dword ptr [ebp + 8]
00502ed4 push ecx
00502ed5 mov dword ptr [esp], 0
00502edc mov ecx, ebx
00502ede push esi
00502edf call 0x7cf0a0
00502ee4 test al, al
00502ee6 je 0x502f60
00502ee8 movss xmm3, dword ptr [0xb6aa3c]
00502ef0 movss xmm0, dword ptr [edi]
00502ef4 subss xmm0, xmm3
00502ef8 movss xmm2, dword ptr [0xb6a480]
00502f00 divss xmm0, xmm3
00502f04 addss xmm0, xmm2
00502f08 cvttss2si eax, xmm0
00502f0c movss xmm0, dword ptr [edi + 4]
00502f11 subss xmm0, dword ptr [0xb6ab20]
00502f19 mov dword ptr [ebp - 4], eax
00502f1c divss xmm0, xmm3
00502f20 addss xmm0, xmm2
00502f24 cvttss2si edi, xmm0
00502f28 movss xmm0, dword ptr [esi]
00502f2c subss xmm0, xmm3
00502f30 divss xmm0, xmm3
00502f34 addss xmm0, xmm2
00502f38 cvttss2si ecx, xmm0
00502f3c movss xmm0, dword ptr [esi + 4]
00502f41 mov dword ptr [ebp - 8], ecx
00502f44 subss xmm0, dword ptr [0xb6ab20]
00502f4c divss xmm0, xmm3
00502f50 addss xmm0, xmm2
00502f54 cvttss2si esi, xmm0
00502f58 cmp eax, ecx
00502f5a je 0x502f7c
00502f5c cmp edi, esi
00502f5e je 0x502f80
00502f60 mov edx, dword ptr [ebp - 0x14]
00502f63 mov eax, dword ptr [0xc02fec]
00502f68 mov ecx, dword ptr [0xc02ff0]
00502f6e mov dword ptr [edx], eax
00502f70 mov eax, edx
00502f72 mov dword ptr [edx + 4], ecx
00502f75 pop edi
00502f76 pop esi
00502f77 pop ebx
00502f78 mov esp, ebp
00502f7a pop ebp
00502f7b ret 
00502f7c cmp edi, esi
00502f7e je 0x502f60
00502f80 mov eax, esi
00502f82 sub eax, edi
00502f84 cdq 
00502f85 mov ecx, eax
00502f87 mov eax, dword ptr [ebp - 8]
00502f8a sub eax, dword ptr [ebp - 4]
00502f8d xor ecx, edx
00502f8f sub ecx, edx
00502f91 cdq 
00502f92 xor eax, edx
00502f94 sub eax, edx
00502f96 cmp eax, ecx
00502f98 cmovl eax, ecx
00502f9b mov ecx, dword ptr [ebp - 8]
00502f9e dec eax
00502f9f mov dword ptr [ebp - 0x10], eax
00502fa2 mov eax, dword ptr [ebp - 4]
00502fa5 cmp ecx, eax
00502fa7 jle 0x502fb0
00502fa9 mov edx, 1
00502fae jmp 0x502fb8
00502fb0 xor edx, edx
00502fb2 cmp ecx, eax
00502fb4 setge dl
00502fb7 dec edx
00502fb8 mov dword ptr [ebp - 4], edx
00502fbb cmp esi, edi
00502fbd jle 0x502fc6
00502fbf mov ecx, 1
00502fc4 jmp 0x502fce
00502fc6 xor ecx, ecx
00502fc8 cmp esi, edi
00502fca setge cl
00502fcd dec ecx
00502fce add edi, ecx
00502fd0 mov dword ptr [ebp - 0xc], ecx
00502fd3 cmp dword ptr [ebp - 0x10], 0
00502fd7 lea esi, [edx + eax]
00502fda mov dword ptr [ebp - 8], 0
00502fe1 jle 0x503053
00502fe3 test esi, esi
00502fe5 js 0x502ffe
00502fe7 mov eax, dword ptr [ebx + 0xc]
00502fea cmp esi, eax
00502fec jge 0x502ffe
00502fee test edi, edi
00502ff0 js 0x502ffe
00502ff2 cmp edi, dword ptr [ebx + 0x10]
00502ff5 jge 0x502ffe
00502ff7 imul eax, edi
00502ffa add eax, esi
00502ffc jmp 0x503001
00502ffe or eax, 0xffffffff
00503001 push eax
00503002 mov ecx, ebx
00503004 call 0x7aeec0
00503009 test eax, eax
0050300b jne 0x502f60
00503011 test esi, esi
00503013 js 0x50303d
00503015 mov eax, dword ptr [ebx + 0xc]
00503018 cmp esi, eax
0050301a jge 0x50303d
0050301c test edi, edi
0050301e js 0x50303d
00503020 cmp edi, dword ptr [ebx + 0x10]
00503023 jge 0x50303d
00503025 imul eax, edi
00503028 add eax, esi
0050302a js 0x50303d
0050302c cmp dword ptr [ebx + eax*4 + 0x76c], 0x28a
00503037 jg 0x502f60
0050303d mov eax, dword ptr [ebp - 8]
00503040 mov edx, dword ptr [ebp - 4]
00503043 inc eax
00503044 mov ecx, dword ptr [ebp - 0xc]
00503047 add esi, edx
00503049 add edi, ecx
0050304b mov dword ptr [ebp - 8], eax
0050304e cmp eax, dword ptr [ebp - 0x10]
00503051 jl 0x502fe3
00503053 mov eax, dword ptr [ebp - 0x14]
00503056 movd xmm0, edx
0050305a cvtdq2ps xmm0, xmm0
0050305d pop edi
0050305e pop esi
0050305f pop ebx
00503060 movss dword ptr [eax], xmm0
00503064 movd xmm0, ecx
00503068 cvtdq2ps xmm0, xmm0
0050306b movss dword ptr [eax + 4], xmm0
00503070 mov esp, ebp
00503072 pop ebp
00503073 ret 
