00503080 push ebp
00503081 mov ebp, esp
00503083 and esp, 0xfffffff8
00503086 sub esp, 0x18
00503089 push esi
0050308a mov esi, dword ptr [ebp + 0x10]
0050308d push edi
0050308e mov dword ptr [esp + 0xc], 0
00503096 mov dword ptr [esp + 8], 0
0050309e mov eax, dword ptr [esi + 0x294]
005030a4 movss xmm1, dword ptr [esi + 0x2b8]
005030ac movss xmm2, dword ptr [esi + 0x2bc]
005030b4 mulss xmm1, dword ptr [0xb6a8f4]
005030bc mov ecx, dword ptr [esi + 0x298]
005030c2 mulss xmm2, dword ptr [0xb6a8f4]
005030ca mov dword ptr [esp + 0x18], eax
005030ce lea eax, [esp + 8]
005030d2 addss xmm1, dword ptr [esi + 0x294]
005030da push eax
005030db addss xmm2, dword ptr [esi + 0x298]
005030e3 push 0
005030e5 push 0
005030e7 push 0
005030e9 mov dword ptr [esp + 0x2c], ecx
005030ed lea eax, [esp + 0x20]
005030f1 mov ecx, dword ptr [0xbfd65c]
005030f7 push 1
005030f9 push eax
005030fa lea eax, [esp + 0x30]
005030fe movss dword ptr [esp + 0x28], xmm1
00503104 mov ecx, dword ptr [ecx + 0x18190]
0050310a push eax
0050310b movss dword ptr [esp + 0x30], xmm2
00503111 call 0x7af4b0
00503116 mov edi, dword ptr [ebp + 8]
00503119 lea eax, [esp + 8]
0050311d push eax
0050311e mov edx, edi
00503120 lea ecx, [esp + 0x1c]
00503124 call 0x502ea0
00503129 mov ecx, eax
0050312b add esp, 4
0050312e movss xmm0, dword ptr [ecx]
00503132 ucomiss xmm0, dword ptr [0xc02fec]
00503139 lahf 
0050313a test ah, 0x44
0050313d jp 0x50315b
0050313f movss xmm0, dword ptr [ecx + 4]
00503144 ucomiss xmm0, dword ptr [0xc02ff0]
0050314b lahf 
0050314c test ah, 0x44
0050314f jp 0x50315b
00503151 movss xmm2, dword ptr [0xb6a7b0]
00503159 jmp 0x503163
0050315b movss xmm2, dword ptr [0xb6a214]
00503163 movss xmm1, dword ptr [edi]
00503167 movss xmm0, dword ptr [edi + 4]
0050316c subss xmm0, dword ptr [esi + 0x298]
00503174 subss xmm1, dword ptr [esi + 0x294]
0050317c pop edi
0050317d pop esi
0050317e mulss xmm0, xmm0
00503182 mulss xmm1, xmm1
00503186 addss xmm0, xmm1
0050318a mulss xmm0, xmm2
0050318e movss dword ptr [esp], xmm0
00503193 fld dword ptr [esp]
00503196 mov esp, ebp
00503198 pop ebp
00503199 ret 
