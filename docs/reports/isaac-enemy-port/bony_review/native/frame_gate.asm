00684790 push ebp
00684791 mov ebp, esp
00684793 and esp, 0xfffffff8
00684796 push ecx
00684797 mov eax, dword ptr [ecx + 0x160]
0068479d and eax, 0x4000
006847a2 or eax, 0
006847a5 push esi
006847a6 jne 0x6847d2
006847a8 mov esi, dword ptr [0xbfd65c]
006847ae mov ecx, esi
006847b0 call 0x6d0380
006847b5 test al, al
006847b7 jne 0x6847d2
006847b9 mov eax, dword ptr [esi + 0x1a30dc]
006847bf add eax, dword ptr [ebp + 0xc]
006847c2 cdq 
006847c3 idiv dword ptr [ebp + 8]
006847c6 test edx, edx
006847c8 sete al
006847cb pop esi
006847cc mov esp, ebp
006847ce pop ebp
006847cf ret 8
006847d2 xor al, al
006847d4 pop esi
006847d5 mov esp, ebp
006847d7 pop ebp
006847d8 ret 8
006847db int3 
006847dc int3 
006847dd int3 
006847de int3 
006847df int3 
006847e0 push ebp
006847e1 mov ebp, esp
006847e3 and esp, 0xfffffff8
006847e6 sub esp, 0xc
006847e9 push esi
006847ea mov esi, ecx
006847ec movss dword ptr [esp + 8], xmm2
006847f2 movss dword ptr [esp + 0xc], xmm1
006847f8 mov eax, dword ptr [esi + 0x160]
