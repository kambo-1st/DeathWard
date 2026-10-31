00501125 cmp dword ptr [edi + 0x70], 0
00501129 je 0x50146b
0050112f push 0xb400ac
00501134 lea ecx, [edi + 0x6c]
00501137 call 0x405e90
0050113c test al, al
0050113e je 0x50145c
00501144 mov ecx, edi
00501146 call 0x695680
0050114b cmp dword ptr [edi + 0xe6c], -1
00501152 lea ebx, [edi + 0x294]
00501158 movss xmm1, dword ptr [eax + 0x294]
00501160 movss xmm2, dword ptr [eax + 0x298]
00501168 subss xmm1, dword ptr [ebx]
0050116c subss xmm2, dword ptr [ebx + 4]
00501171 movss dword ptr [esp + 0x20], xmm1
00501177 movss dword ptr [esp + 0x18], xmm1
0050117d movss dword ptr [esp + 0x10], xmm2
00501183 movss dword ptr [esp + 0x1c], xmm2
00501189 je 0x5011d8
0050118b movss xmm3, dword ptr [edi + 0xe70]
00501193 ucomiss xmm3, dword ptr [0xc02fec]
0050119a lahf 
0050119b test ah, 0x44
0050119e jp 0x5011b5
005011a0 movss xmm0, dword ptr [edi + 0xe74]
005011a8 ucomiss xmm0, dword ptr [0xc02ff0]
005011af lahf 
005011b0 test ah, 0x44
005011b3 jnp 0x5011d8
005011b5 movss xmm2, dword ptr [edi + 0xe74]
005011bd movaps xmm1, xmm3
005011c0 movss dword ptr [esp + 0x20], xmm1
005011c6 movss dword ptr [esp + 0x18], xmm1
005011cc movss dword ptr [esp + 0x10], xmm2
005011d2 movss dword ptr [esp + 0x1c], xmm2
005011d8 mov eax, dword ptr [0xbfd65c]
005011dd mov eax, dword ptr [eax + 0x243624]
005011e3 cmp eax, 1
005011e6 je 0x5011f7
005011e8 cmp eax, 3
005011eb je 0x5011f7
005011ed movss xmm0, dword ptr [0xb6a928]
005011f5 jmp 0x5011ff
005011f7 movss xmm0, dword ptr [0xb6a974]
005011ff movss dword ptr [esp + 0x14], xmm0
00501205 movaps xmm0, xmm1
00501208 mulss xmm0, xmm1
0050120c movaps xmm1, xmm2
0050120f mulss xmm1, xmm2
00501213 addss xmm0, xmm1
00501217 call 0x4228c0
0050121c xorps xmm1, xmm1
0050121f comiss xmm0, xmm1
00501222 jbe 0x50124e
00501224 movss xmm1, dword ptr [esp + 0x14]
0050122a divss xmm1, xmm0
0050122e movss xmm0, dword ptr [esp + 0x20]
00501234 mulss xmm0, xmm1
00501238 movss dword ptr [esp + 0x18], xmm0
0050123e movss xmm0, dword ptr [esp + 0x10]
00501244 mulss xmm0, xmm1
00501248 movss dword ptr [esp + 0x1c], xmm0
