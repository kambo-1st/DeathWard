007250a0 push ebp
007250a1 mov ebp, esp
007250a3 push esi
007250a4 mov esi, ecx
007250a6 call 0x78cdc0
007250ab cmp eax, 3
007250ae je 0x725120
007250b0 call 0x78cdc0
007250b5 cmp eax, 2
007250b8 je 0x725120
007250ba mov eax, dword ptr [ebp + 8]
007250bd xor ecx, ecx
007250bf add eax, dword ptr [esi + 0x1298]
007250c5 test eax, eax
007250c7 cmovg ecx, eax
007250ca mov dword ptr [esi + 0x1298], ecx
007250d0 cmp ecx, 1
007250d3 jle 0x725120
007250d5 mov ecx, esi
007250d7 call 0x725050
007250dc mov eax, dword ptr [esi + 0x1298]
007250e2 mov ecx, esi
007250e4 cdq 
007250e5 sub eax, edx
007250e7 push 0
007250e9 and eax, 0xfffffffe
007250ec push eax
007250ed call 0x724d50
007250f2 mov eax, dword ptr [esi + 0x1298]
007250f8 mov ecx, esi
007250fa cdq 
007250fb sub eax, edx
007250fd push 0
007250ff and eax, 0xfffffffe
00725102 push eax
00725103 call 0x724f00
00725108 mov eax, dword ptr [esi + 0x1298]
0072510e and eax, 0x80000001
00725113 jns 0x72511a
00725115 dec eax
00725116 or eax, 0xfffffffe
00725119 inc eax
0072511a mov dword ptr [esi + 0x1298], eax
00725120 pop esi
00725121 pop ebp
00725122 ret 4
00725125 int3 
00725126 int3 
00725127 int3 
00725128 int3 
00725129 int3 
0072512a int3 
0072512b int3 
0072512c int3 
0072512d int3 
0072512e int3 
0072512f int3 
