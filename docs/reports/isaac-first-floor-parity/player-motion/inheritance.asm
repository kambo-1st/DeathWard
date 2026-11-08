0076ff80 push ebp
0076ff81 mov ebp, esp
0076ff83 and esp, 0xfffffff8
0076ff86 sub esp, 0x18
0076ff89 cmp byte ptr [ebp + 0x10], 0
0076ff8d push esi
0076ff8e push edi
0076ff8f mov esi, ecx
0076ff91 jne 0x77002a
0076ff97 push 0
0076ff99 push 0x18a
0076ff9e call 0x73af30
0076ffa3 test al, al
0076ffa5 je 0x76ffb0
0076ffa7 cmp dword ptr [esi + 0x1354], 0
0076ffae jne 0x770006
0076ffb0 movss xmm0, dword ptr [esi + 0x1580]
0076ffb8 ucomiss xmm0, dword ptr [0xc02fec]
0076ffbf lahf 
0076ffc0 test ah, 0x44
0076ffc3 jp 0x76ffde
0076ffc5 movss xmm0, dword ptr [esi + 0x1584]
0076ffcd movss xmm3, dword ptr [0xc02ff0]
0076ffd5 ucomiss xmm0, xmm3
0076ffd8 lahf 
0076ffd9 test ah, 0x44
0076ffdc jnp 0x770032
0076ffde push 0x145
0076ffe3 lea ecx, [esi + 0x1450]
0076ffe9 call 0x88b570
0076ffee test al, al
0076fff0 jne 0x770006
0076fff2 push 0x2d9
0076fff7 lea ecx, [esi + 0x1450]
0076fffd call 0x88b570
00770002 test al, al
00770004 je 0x77002a
00770006 mov eax, dword ptr [ebp + 8]
00770009 movss xmm0, dword ptr [0xc02fec]
00770011 movss dword ptr [eax], xmm0
00770015 movss xmm0, dword ptr [0xc02ff0]
0077001d movss dword ptr [eax + 4], xmm0
00770022 pop edi
00770023 pop esi
00770024 mov esp, ebp
00770026 pop ebp
00770027 ret 0xc
0077002a movss xmm3, dword ptr [0xc02ff0]
00770032 movss xmm1, dword ptr [esi + 0x1594]
0077003a movss xmm2, dword ptr [esi + 0x1598]
00770042 mov esi, dword ptr [ebp + 0xc]
00770045 mulss xmm1, dword ptr [0xb6a4c4]
0077004d mulss xmm2, dword ptr [0xb6a4c4]
00770055 movss xmm0, dword ptr [esi]
00770059 addss xmm1, xmm1
0077005d ucomiss xmm0, dword ptr [0xc02fec]
00770064 addss xmm2, xmm2
00770068 movss dword ptr [esp + 0xc], xmm1
0077006e lahf 
0077006f movss dword ptr [esp + 0x10], xmm2
00770075 test ah, 0x44
00770078 jp 0x77008c
0077007a movss xmm0, dword ptr [esi + 4]
0077007f ucomiss xmm0, xmm3
00770082 lahf 
00770083 test ah, 0x44
00770086 jnp 0x7701c0
0077008c movss xmm1, dword ptr [esi]
00770090 movss xmm2, dword ptr [esi + 4]
00770095 movaps xmm0, xmm1
00770098 mulss xmm0, xmm1
0077009c movss dword ptr [esp + 0x14], xmm1
007700a2 movaps xmm1, xmm2
007700a5 mulss xmm1, xmm2
007700a9 movss dword ptr [esp + 0x18], xmm2
007700af addss xmm0, xmm1
007700b3 call 0x4228c0
007700b8 comiss xmm0, dword ptr [0xb6a18c]
007700bf jbe 0x7700e6
007700c1 movss xmm1, dword ptr [0xb6a614]
007700c9 divss xmm1, xmm0
007700cd movss xmm0, dword ptr [esi]
007700d1 mulss xmm0, xmm1
007700d5 movss dword ptr [esp + 0x14], xmm0
007700db movss xmm0, dword ptr [esi + 4]
007700e0 mulss xmm0, xmm1
007700e4 jmp 0x7700ec
007700e6 movss xmm0, dword ptr [esp + 0x18]
007700ec movss xmm1, dword ptr [esp + 0x10]
007700f2 movss xmm2, dword ptr [esi + 4]
007700f7 mulss xmm1, xmm0
007700fb movss xmm0, dword ptr [esp + 0xc]
00770101 mulss xmm0, dword ptr [esp + 0x14]
00770107 movss dword ptr [esp + 0x14], xmm2
0077010d addss xmm1, xmm0
00770111 movss dword ptr [esp + 0x1c], xmm1
00770117 movss xmm1, dword ptr [esi]
0077011b movaps xmm0, xmm1
0077011e movss dword ptr [esp + 0x18], xmm1
00770124 mulss xmm0, xmm1
00770128 movaps xmm1, xmm2
0077012b mulss xmm1, xmm2
0077012f addss xmm0, xmm1
00770133 call 0x4228c0
00770138 movaps xmm1, xmm0
0077013b xorps xmm4, xmm4
0077013e comiss xmm1, xmm4
00770141 jbe 0x770162
00770143 movss xmm0, dword ptr [0xb6a614]
0077014b divss xmm0, xmm1
0077014f movss xmm2, dword ptr [esi]
00770153 movss xmm3, dword ptr [esi + 4]
00770158 mulss xmm2, xmm0
0077015c mulss xmm3, xmm0
00770160 jmp 0x77016e
00770162 movss xmm2, dword ptr [esp + 0x18]
00770168 movss xmm3, dword ptr [esp + 0x14]
0077016e mulss xmm2, dword ptr [esp + 0x1c]
00770174 mulss xmm3, dword ptr [esp + 0x1c]
0077017a movaps xmm0, xmm2
0077017d mulss xmm0, dword ptr [esi]
00770181 movaps xmm1, xmm3
00770184 mulss xmm1, dword ptr [esi + 4]
00770189 addss xmm1, xmm0
0077018d comiss xmm4, xmm1
00770190 movss xmm1, dword ptr [esp + 0xc]
00770196 jbe 0x7701ba
00770198 mov eax, dword ptr [ebp + 8]
0077019b subss xmm1, xmm2
0077019f movss xmm2, dword ptr [esp + 0x10]
007701a5 subss xmm2, xmm3
007701a9 movss dword ptr [eax], xmm1
007701ad movss dword ptr [eax + 4], xmm2
007701b2 pop edi
007701b3 pop esi
007701b4 mov esp, ebp
007701b6 pop ebp
007701b7 ret 0xc
007701ba movss xmm2, dword ptr [esp + 0x10]
007701c0 mov eax, dword ptr [ebp + 8]
007701c3 pop edi
007701c4 pop esi
007701c5 movss dword ptr [eax], xmm1
007701c9 movss dword ptr [eax + 4], xmm2
007701ce mov esp, ebp
007701d0 pop ebp
007701d1 ret 0xc
