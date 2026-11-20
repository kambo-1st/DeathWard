00758030 push ebp
00758031 mov ebp, esp
00758033 and esp, 0xfffffff8
00758036 sub esp, 0x1c
00758039 push ebx
0075803a mov ebx, dword ptr [ebp + 0xc]
0075803d push esi
0075803e push edi
0075803f mov edi, ecx
00758041 test ebx, ebx
00758043 jns 0x758077
00758045 xor ebx, ebx
00758047 xor esi, esi
00758049 nop dword ptr [eax]
00758050 push dword ptr [ebp + 0x14]
00758053 mov ecx, edi
00758055 push dword ptr [ebp + 0x10]
00758058 push dword ptr [ebp + 0x18]
0075805b push esi
0075805c push dword ptr [ebp + 8]
0075805f call 0x758030
00758064 inc esi
00758065 add ebx, eax
00758067 cmp esi, 4
0075806a jb 0x758050
0075806c mov eax, ebx
0075806e pop edi
0075806f pop esi
00758070 pop ebx
00758071 mov esp, ebp
00758073 pop ebp
00758074 ret 0x14
00758077 push ebx
00758078 call 0x757c80
0075807d mov dword ptr [esp + 0x24], eax
00758081 xor esi, esi
00758083 lea eax, [ebx*8]
0075808a sub eax, ebx
0075808c mov dword ptr [esp + 0x18], eax
00758090 mov ecx, dword ptr [edi + eax*4 + 0x14c4]
00758097 test ecx, ecx
00758099 je 0x7582c0
0075809f push ecx
007580a0 mov ecx, dword ptr [0xbfd680]
007580a6 lea ecx, [ecx + 0x29e84]
007580ac call 0x6fe5e0
007580b1 mov esi, dword ptr [ebp + 8]
007580b4 mov dword ptr [esp + 0x1c], eax
007580b8 test esi, esi
007580ba jle 0x7580e6
007580bc cmp byte ptr [ebp + 0x18], 0
007580c0 jne 0x7580e6
007580c2 mov eax, dword ptr [eax + 0xac]
007580c8 test eax, eax
007580ca je 0x7580e6
007580cc cmp eax, 1
007580cf je 0x7580dc
007580d1 xor eax, eax
007580d3 pop edi
007580d4 pop esi
007580d5 pop ebx
007580d6 mov esp, ebp
007580d8 pop ebp
007580d9 ret 0x14
007580dc push ebx
007580dd mov ecx, edi
007580df call 0x757e40
007580e4 mov esi, eax
007580e6 push ebx
007580e7 mov ecx, edi
007580e9 call 0x757e40
007580ee mov dword ptr [esp + 0x14], eax
007580f2 test esi, esi
007580f4 jle 0x7583ca
007580fa lea ecx, [ebx + 0xbe]
00758100 lea edx, [ecx*8]
00758107 sub edx, ecx
00758109 xor ecx, ecx
0075810b mov dword ptr [esp + 0x20], edx
0075810f push 0
00758111 push 0x3f
00758113 mov edx, dword ptr [edi + edx*4]
00758116 sub eax, edx
00758118 test eax, eax
0075811a cmovg ecx, eax
0075811d mov eax, esi
0075811f cmp ecx, esi
00758121 cmovl eax, ecx
00758124 mov ecx, dword ptr [esp + 0x28]
00758128 mov dword ptr [esp + 0x18], eax
0075812c add eax, edx
0075812e sub esi, dword ptr [esp + 0x18]
00758132 mov dword ptr [edi + ecx*4], eax
00758135 mov ecx, edi
00758137 call 0x73af30
0075813c test al, al
0075813e jne 0x758149
00758140 cmp byte ptr [ebp + 0x14], al
00758143 je 0x758327
00758149 test esi, esi
0075814b jle 0x758327
00758151 mov edx, dword ptr [esp + 0x18]
00758155 xor ecx, ecx
00758157 mov eax, dword ptr [esp + 0x14]
0075815b sub eax, dword ptr [edi + edx*4 + 0x14cc]
00758162 test eax, eax
00758164 cmovg ecx, eax
00758167 cmp ecx, esi
00758169 cmovl esi, ecx
0075816c test esi, esi
0075816e jle 0x758259
00758174 add dword ptr [edi + edx*4 + 0x14cc], esi
0075817b add dword ptr [esp + 0x10], esi
0075817f cmp byte ptr [ebp + 0x10], 0
00758183 jne 0x7581a3
00758185 mov eax, dword ptr [esp + 0x1c]
00758189 mov edx, dword ptr [esp + 0x14]
0075818d cmp dword ptr [eax + 0xac], 1
00758194 je 0x758465
0075819a cmp edx, 0xc
0075819d jg 0x758465
007581a3 mov ecx, dword ptr [0xbfd65c]
007581a9 push ebx
007581aa push edi
007581ab lea ecx, [ecx + 0x3da4c]
007581b1 call 0x902ab0
007581b6 mov esi, dword ptr [0xbfd680]
007581bc lea ecx, [esp + 0x1c]
007581c0 mov dword ptr [esp + 0x1c], 0xaa
007581c8 call 0x8b1340
007581cd sub esp, 8
007581d0 mov dword ptr [esp + 4], 0
007581d8 mov dword ptr [esp], 0x3f800000
007581df push 0
007581e1 push 2
007581e3 push ecx
007581e4 mov dword ptr [esp], 0x3f800000
007581eb lea ecx, [esi + 0x29de0]
007581f1 push dword ptr [esp + 0x30]
007581f5 call 0x888de0
007581fa call 0x6c3d90
007581ff mov ecx, dword ptr [0xbfd65c]
00758205 push 0
00758207 push eax
00758208 push 1
0075820a push 0
0075820c push 0xc02fec
00758211 lea eax, [edi + 0x294]
00758217 push eax
00758218 push 0x31
0075821a push 0x3e8
0075821f call 0x6d0ca0
00758224 push 0
00758226 push 0xbeaaec
0075822b push 0xbeab18
00758230 push 0
00758232 push eax
00758233 call 0x9ec34c
00758238 add esp, 0x14
0075823b mov dword ptr [eax + 0xd0], 0
00758245 mov dword ptr [eax + 0xd4], 0xc1c00000
0075824f mov dword ptr [eax + 0x2b0], 0x3f800000
00758259 mov esi, dword ptr [esp + 0x10]
0075825d mov edx, dword ptr [esp + 0x14]
00758261 mov eax, dword ptr [esp + 0x18]
00758265 cmp dword ptr [edi + eax*4 + 0x14c4], 0x1da
00758270 jne 0x7582c0
00758272 lea ecx, [ebx + 0xbe]
00758278 lea eax, [ecx*8]
0075827f sub eax, ecx
00758281 cmp dword ptr [edi + eax*4], edx
00758284 jl 0x7582c0
00758286 push 1
00758288 push ebx
00758289 push 0
0075828b push 0x1da
00758290 mov ecx, edi
00758292 call 0x756580
00758297 push 0
00758299 push ebx
0075829a push 0
0075829c push -1
0075829e push 0x160
007582a3 mov ecx, edi
007582a5 call 0x72b260
007582aa push 0xb44128
007582af push 0xb449a0
007582b4 push 0x160
007582b9 mov ecx, edi
007582bb call 0x770300
007582c0 push 0
007582c2 mov ecx, edi
007582c4 call 0x757c80
007582c9 cmp eax, dword ptr [esp + 0x24]
007582cd je 0x7582fa
007582cf push 0x65
007582d1 mov ecx, edi
007582d3 call 0x78d4c0
007582d8 test eax, eax
007582da jg 0x7582e9
007582dc push 0x64
007582de mov ecx, edi
007582e0 call 0x78d4c0
007582e5 test eax, eax
007582e7 jle 0x7582fa
007582e9 or dword ptr [edi + 0x14b8], 0x41f
007582f3 mov ecx, edi
007582f5 call 0x72ed20
007582fa mov eax, dword ptr [0xbfd65c]
007582ff cmp dword ptr [eax + 0x101904], 2
00758306 je 0x75831c
00758308 mov dword ptr [eax + 0x101904], 1
00758312 mov dword ptr [eax + 0x10190c], 2
0075831c pop edi
0075831d mov eax, esi
0075831f pop esi
00758320 pop ebx
00758321 mov esp, ebp
00758323 pop ebp
00758324 ret 0x14
00758327 mov esi, dword ptr [esp + 0x10]
0075832b test esi, esi
0075832d jle 0x75825d
00758333 cmp byte ptr [ebp + 0x10], 0
00758337 jne 0x758357
00758339 mov eax, dword ptr [esp + 0x1c]
0075833d cmp dword ptr [eax + 0xac], 1
00758344 je 0x75825d
0075834a mov edx, dword ptr [esp + 0x14]
0075834e cmp edx, 0xc
00758351 jg 0x758261
00758357 mov ecx, dword ptr [0xbfd65c]
0075835d push ebx
0075835e push edi
0075835f lea ecx, [ecx + 0x3da4c]
00758365 call 0x902ab0
0075836a mov ecx, dword ptr [esp + 0x20]
0075836e mov eax, dword ptr [esp + 0x14]
00758372 mov esi, dword ptr [0xbfd680]
00758378 cmp dword ptr [edi + ecx*4], eax
0075837b lea ecx, [esp + 0x20]
0075837f jge 0x7583c0
00758381 mov dword ptr [esp + 0x20], 0xab
00758389 call 0x8b1340
0075838e sub esp, 8
00758391 mov dword ptr [esp + 4], 0
00758399 mov dword ptr [esp], 0x3f800000
007583a0 push 0
007583a2 push 2
007583a4 push ecx
007583a5 mov dword ptr [esp], 0x3f800000
007583ac lea ecx, [esi + 0x29de0]
007583b2 push dword ptr [esp + 0x34]
007583b6 call 0x888de0
007583bb jmp 0x758259
007583c0 mov dword ptr [esp + 0x20], 0xda
007583c8 jmp 0x758389
