00726070 push ebp
00726071 mov ebp, esp
00726073 sub esp, 8
00726076 push esi
00726077 push edi
00726078 mov edi, ecx
0072607a cmp byte ptr [edi + 0x12b0], 0
00726081 jne 0x726171
00726087 mov eax, dword ptr [edi + 0x12ac]
0072608d test eax, eax
0072608f jle 0x726179
00726095 dec eax
00726096 mov dword ptr [edi + 0x12ac], eax
0072609c mov eax, dword ptr [0xbfd65c]
007260a1 cmp dword ptr [eax + 0x101904], 2
007260a8 je 0x7260be
007260aa mov dword ptr [eax + 0x101904], 1
007260b4 mov dword ptr [eax + 0x10190c], 2
007260be push 2
007260c0 call 0x725af0
007260c5 push 0x57
007260c7 mov ecx, edi
007260c9 call 0x78d4c0
007260ce test eax, eax
007260d0 jle 0x726171
007260d6 push 0
007260d8 push 1
007260da mov ecx, edi
007260dc call 0x724f00
007260e1 cmp dword ptr [edi + 0x130c], 0x16
007260e8 mov ecx, 0x266
007260ed mov esi, dword ptr [0xbfd680]
007260f3 mov eax, 0x9d
007260f8 cmove eax, ecx
007260fb lea ecx, [ebp - 4]
007260fe mov dword ptr [ebp - 4], eax
00726101 call 0x8b1340
00726106 sub esp, 8
00726109 mov dword ptr [esp + 4], 0
00726111 mov dword ptr [esp], 0x3f800000
00726118 push 0
0072611a push 2
0072611c push ecx
0072611d mov dword ptr [esp], 0x3f800000
00726124 lea ecx, [esi + 0x29de0]
0072612a push dword ptr [ebp - 4]
0072612d call 0x888de0
00726132 call 0x6c3d90
00726137 mov ecx, dword ptr [0xbfd65c]
0072613d push 0
0072613f push 0xbeaaec
00726144 push 0xbeab18
00726149 push 0
0072614b push eax
0072614c push 0
0072614e push 0
00726150 push 0xc02fec
00726155 lea eax, [edi + 0x294]
0072615b push eax
0072615c push 0x31
0072615e push 0x3e8
00726163 call 0x422e20
00726168 push eax
00726169 call 0x9ec34c
0072616e add esp, 0x14
00726171 mov al, 1
00726173 pop edi
00726174 pop esi
00726175 mov esp, ebp
00726177 pop ebp
00726178 ret
00726179 pop edi
0072617a xor al, al
0072617c pop esi
0072617d mov esp, ebp
0072617f pop ebp
00726180 ret
