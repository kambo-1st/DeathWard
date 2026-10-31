00500140 push ebp
00500141 mov ebp, esp
00500143 and esp, 0xfffffff8
00500146 sub esp, 0x88
0050014c mov eax, dword ptr [0xbaa3b4]
00500151 xor eax, esp
00500153 mov dword ptr [esp + 0x84], eax
0050015a push esi
0050015b push edi
0050015c mov edi, ecx
0050015e cmp dword ptr [edi + 0xab4], 0
00500165 jne 0x5001e5
00500167 cmp dword ptr [edi + 0x28], 0x12d
0050016e mov dword ptr [edi + 0xab4], 4
00500178 jne 0x500f84
0050017e movaps xmm2, xmmword ptr [0xb6be20]
00500185 lea ecx, [edi + 0x1dc]
0050018b lea eax, [esp + 0x34]
0050018f mov dword ptr [esp + 0x54], 0
00500197 mov dword ptr [esp + 0x58], 0x3e48c8ca
0050019f xorps xmm1, xmm1
005001a2 mov dword ptr [esp + 0x5c], 0
005001aa cmp ecx, eax
005001ac je 0x5001c7
005001ae movq xmm0, qword ptr [esp + 0x54]
005001b4 mov eax, dword ptr [esp + 0x5c]
005001b8 movq qword ptr [ecx + 0x20], xmm0
005001bd movups xmmword ptr [ecx], xmm2
005001c0 mov dword ptr [ecx + 0x28], eax
005001c3 movups xmmword ptr [ecx + 0x10], xmm1
005001c7 mov dword ptr [edi + 0x17c], 3
005001d1 pop edi
005001d2 pop esi
005001d3 mov ecx, dword ptr [esp + 0x84]
005001da xor ecx, esp
005001dc call 0x9eacd7
005001e1 mov esp, ebp
005001e3 pop ebp
005001e4 ret 
