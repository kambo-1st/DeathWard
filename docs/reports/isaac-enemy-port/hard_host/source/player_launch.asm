00794280 push ebp
00794281 mov ebp, esp
00794283 cmp byte ptr [ecx + 0x14b4], 0
0079428a xorps xmm1, xmm1
0079428d jne 0x7942af
0079428f cmp dword ptr [ecx + 0x17c], 5
00794296 jne 0x7942af
00794298 movss xmm0, dword ptr [ecx + 0x2a8]
007942a0 comiss xmm0, xmm1
007942a3 jb 0x7942af
007942a5 mov eax, dword ptr [ebp + 8]
007942a8 cmp dword ptr [eax], 1
007942ab jne 0x7942eb
007942ad jmp 0x7942bb
007942af mov eax, dword ptr [ebp + 8]
007942b2 cmp dword ptr [eax], 1
007942b5 jne 0x79433b
007942bb movss xmm0, dword ptr [ecx + 0x2b8]
007942c3 mulss xmm0, dword ptr [0xb6a3b0]
007942cb movss dword ptr [ecx + 0x2b8], xmm0
007942d3 movss xmm0, dword ptr [ecx + 0x2bc]
007942db mulss xmm0, dword ptr [0xb6a3b0]
007942e3 movss dword ptr [ecx + 0x2bc], xmm0
007942eb movss xmm0, dword ptr [ebp + 0x10]
007942f0 xorps xmm0, xmmword ptr [0xb6c9b0]
007942f7 mov eax, dword ptr [ebp + 0xc]
007942fa movss dword ptr [ecx + 0x1d88], xmm0
00794302 movss xmm0, dword ptr [ecx + 0x2b8]
0079430a mov dword ptr [ecx + 0x2a8], 0
00794314 addss xmm0, dword ptr [eax]
00794318 movss dword ptr [ecx + 0x2b8], xmm0
00794320 movss xmm0, dword ptr [eax + 4]
00794325 mov al, 1
00794327 addss xmm0, dword ptr [ecx + 0x2bc]
0079432f movss dword ptr [ecx + 0x2bc], xmm0
00794337 pop ebp
00794338 ret 0xc
0079433b xor al, al
0079433d pop ebp
