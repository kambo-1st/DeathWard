; Installed Repentance 1.7.9b. Address-bounded linear decode; helper names are unresolved.
; Literal float/string comments describe bytes, not inferred native field meanings.
004a6080 push ebp
004a6081 mov ebp, esp
004a6083 sub esp, 0x14
004a6086 mov eax, dword ptr [ebp + 0xc]
004a6089 push ebx
004a608a push esi
004a608b push edi
004a608c movss xmm0, dword ptr [eax + 4]
004a6091 mov edi, ecx
004a6093 movss xmm1, dword ptr [eax]
004a6097 subss xmm0, dword ptr [edi + 0x298]
004a609f subss xmm1, dword ptr [edi + 0x294]
004a60a7 movaps xmm2, xmm0
004a60aa movss dword ptr [ebp - 4], xmm0
004a60af mulss xmm2, xmm0
004a60b3 movaps xmm0, xmm1
004a60b6 mulss xmm0, xmm1
004a60ba movss dword ptr [ebp + 0xc], xmm1
004a60bf addss xmm2, xmm0
004a60c3 movaps xmm0, xmm2
004a60c6 movss dword ptr [ebp - 0x10], xmm2
004a60cb call 0x4228c0
004a60d0 subss xmm0, dword ptr [0xb6aafc] ; [0xb6aafc] f32=100
004a60d8 xorps xmm1, xmm1
004a60db mov dword ptr [ebp - 8], 0
004a60e2 lea eax, [ebp - 8]
004a60e5 lea ecx, [ebp - 0xc]
004a60e8 divss xmm0, dword ptr [0xb6aba8] ; [0xb6aba8] f32=200
004a60f0 comiss xmm1, xmm0
004a60f3 movss xmm1, dword ptr [0xb6a614] ; [0xb6a614] f32=1
004a60fb movss dword ptr [ebp - 0xc], xmm0
004a6100 cmovbe eax, ecx
004a6103 movss xmm0, dword ptr [eax]
004a6107 comiss xmm0, xmm1
004a610a ja 0x4a6112
004a610c movss xmm0, xmm0
004a6110 jmp 0x4a6116
004a6112 movss xmm0, xmm1
004a6116 mov esi, dword ptr [ebp + 8]
004a6119 cmp dword ptr [esi + 0x2c], 8
004a611d mulss xmm0, dword ptr [0xb6a9bc] ; [0xb6a9bc] f32=18
004a6125 addss xmm0, dword ptr [0xb6a974] ; [0xb6a974] f32=10
004a612d movss dword ptr [ebp - 8], xmm0
004a6132 jne 0x4a6141
004a6134 mulss xmm0, dword ptr [0xb6a53c] ; [0xb6a53c] f32=0.75
004a613c movss dword ptr [ebp - 8], xmm0
004a6141 movss xmm0, dword ptr [ebp - 0x10]
004a6146 call 0x4228c0
004a614b comiss xmm0, dword ptr [0xb6a18c] ; [0xb6a18c] f32=0
004a6152 movss xmm2, dword ptr [ebp - 4]
004a6157 jbe 0x4a6174
004a6159 movss xmm1, dword ptr [0xb6a614] ; [0xb6a614] f32=1
004a6161 divss xmm1, xmm0
004a6165 movss xmm0, dword ptr [ebp + 0xc]
004a616a mulss xmm0, xmm1
004a616e mulss xmm2, xmm1
004a6172 jmp 0x4a6179
004a6174 movss xmm0, dword ptr [ebp + 0xc]
004a6179 mulss xmm0, dword ptr [ebp - 8]
004a617e lea ebx, [esi + 0x320]
004a6184 mov ecx, dword ptr [ebx]
004a6186 mulss xmm2, dword ptr [ebp - 8]
004a618b movss dword ptr [ebp + 0xc], xmm0
004a6190 movss dword ptr [ebp - 4], xmm2
004a6195 test ecx, ecx
004a6197 je 0x4a61ab
004a6199 lea eax, [ebp + 8]
004a619c mov dword ptr [ebp + 8], ebx
004a619f push eax
004a61a0 add ecx, 0x324
004a61a6 call 0x4bc3c0
004a61ab mov dword ptr [ebx], edi
004a61ad test edi, edi
004a61af je 0x4a61b9
004a61b1 push ebx
004a61b2 mov ecx, edi
004a61b4 call 0x4bae70
004a61b9 mov eax, dword ptr [edi + 0x28]
004a61bc lea ebx, [esi + 0x314]
004a61c2 mov ecx, dword ptr [ebx]
004a61c4 mov dword ptr [esi + 0x34], eax
004a61c7 mov eax, dword ptr [edi + 0x2c]
004a61ca mov dword ptr [esi + 0x38], eax
004a61cd test ecx, ecx
004a61cf je 0x4a61e3
004a61d1 lea eax, [ebp + 8]
004a61d4 mov dword ptr [ebp + 8], ebx
004a61d7 push eax
004a61d8 add ecx, 0x324
004a61de call 0x4bc3c0
004a61e3 push ebx
004a61e4 mov ecx, edi
004a61e6 mov dword ptr [ebx], edi
004a61e8 call 0x4bae70
004a61ed movss xmm0, dword ptr [ebp + 0xc]
004a61f2 mov ecx, esi
004a61f4 mov dword ptr [esi + 0x180], 4
004a61fe mov byte ptr [esi + 0x169], 1
004a6205 mov dword ptr [esi + 0x36c], 0xc0800000
004a620f mov dword ptr [esi + 0x2a4], 0
004a6219 mov dword ptr [esi + 0x2a8], 0xc1c00000
004a6223 mov eax, dword ptr [edi + 0x294]
004a6229 mov dword ptr [esi + 0x294], eax
004a622f mov eax, dword ptr [edi + 0x298]
004a6235 and dword ptr [esi + 0x160], 0xffffffdf
004a623c mov dword ptr [esi + 0x298], eax
004a6242 mov eax, dword ptr [esi + 0x164]
004a6248 mov dword ptr [esi + 0x164], eax
004a624e mov eax, dword ptr [esi]
004a6250 movss dword ptr [esi + 0x2b8], xmm0
004a6258 movss xmm0, dword ptr [ebp - 4]
004a625d movss dword ptr [esi + 0x2bc], xmm0
004a6265 call dword ptr [eax + 0xc]
004a6268 pop edi
004a6269 pop esi
004a626a pop ebx
004a626b mov esp, ebp
004a626d pop ebp
004a626e ret 8
004a6271 int3 
004a6272 int3 
004a6273 int3 
004a6274 int3 
004a6275 int3 
004a6276 int3 
004a6277 int3 
004a6278 int3 
004a6279 int3 
004a627a int3 
004a627b int3 
004a627c int3 
004a627d int3 
004a627e int3 
004a627f int3 
