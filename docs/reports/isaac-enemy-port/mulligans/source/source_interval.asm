006847e0 push ebp
006847e1 mov ebp, esp
006847e3 and esp, 0xfffffff8
006847e6 sub esp, 0xc
006847e9 push esi
006847ea mov esi, ecx
006847ec movss dword ptr [esp + 8], xmm2
006847f2 movss dword ptr [esp + 0xc], xmm1
006847f8 mov eax, dword ptr [esi + 0x160]
006847fe and eax, 0x4000
00684803 or eax, 0
00684806 jne 0x68484b
00684808 mov ecx, dword ptr [0xbfd65c]
0068480e call 0x6d0380
00684813 test al, al
00684815 jne 0x68484b
00684817 movss xmm1, dword ptr [esp + 8]
0068481d movaps xmm0, xmm1
00684820 addss xmm0, dword ptr [esi + 0x2fc]
00684828 addss xmm1, dword ptr [esi + 0x2f8]
00684830 divss xmm0, dword ptr [esp + 0xc]
00684836 divss xmm1, dword ptr [esp + 0xc]
0068483c cvttss2si eax, xmm0
00684840 cvttss2si ecx, xmm1
00684844 sub eax, ecx
00684846 pop esi
00684847 mov esp, ebp
00684849 pop ebp
0068484a ret 
0068484b xor eax, eax
0068484d pop esi
0068484e mov esp, ebp
00684850 pop ebp
00684851 ret 
