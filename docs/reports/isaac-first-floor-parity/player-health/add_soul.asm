00725130 push ebp
00725131 mov ebp, esp
00725133 and esp, 0xfffffff8
00725136 sub esp, 0xc
00725139 push ebx
0072513a mov ebx, dword ptr [ebp + 8]
0072513d push esi
0072513e push edi
0072513f mov esi, ecx
00725141 cmp dword ptr [esi + 0x130c], 0x28
00725148 jne 0x725158
0072514a mov eax, dword ptr [esi + 0x1d80]
00725150 test eax, eax
00725152 je 0x725158
00725154 mov esi, eax
00725156 jmp 0x725141
00725158 cmp byte ptr [esi + 0x148c], 0
0072515f jne 0x725218
00725165 mov eax, dword ptr [0xbfd65c]
0072516a cmp byte ptr [eax + 0x243645], 0
00725171 jne 0x725218
00725177 cmp byte ptr [eax + 0x243647], 0
0072517e jne 0x725218
00725184 test ebx, ebx
00725186 jle 0x7251b4
00725188 push 0x66
0072518a lea ecx, [esi + 0x1450]
00725190 call 0x88b600
00725195 test al, al
00725197 je 0x7251b6
00725199 push -1
0072519b push 0x66
0072519d lea ecx, [esi + 0x1450]
007251a3 call 0x88b4e0
007251a8 lea eax, [ebx - 2]
007251ab xor ebx, ebx
007251ad test eax, eax
007251af cmovg ebx, eax
007251b2 test ebx, ebx
007251b4 je 0x725218
007251b6 lea eax, [esi + 0x14c8]
007251bc xor edi, edi
007251be mov dword ptr [esp + 0xc], eax
007251c2 cmp dword ptr [eax - 4], 0x249
007251c9 jne 0x72520b
007251cb push edi
007251cc mov ecx, esi
007251ce call 0x757e40
007251d3 mov ecx, dword ptr [esp + 0xc]
007251d7 mov edx, dword ptr [ecx]
007251d9 mov dword ptr [esp + 0x10], edx
007251dd lea ecx, [edx + ebx]
007251e0 cmp ecx, eax
007251e2 cmovl eax, ecx
007251e5 xor ecx, ecx
007251e7 test eax, eax
007251e9 cmovg ecx, eax
007251ec mov dword ptr [esp + 0x14], ecx
007251f0 cmp ecx, edx
007251f2 je 0x725207
007251f4 push edi
007251f5 push ecx
007251f6 mov ecx, esi
007251f8 call 0x757f20
007251fd mov eax, dword ptr [esp + 0x10]
00725201 sub eax, dword ptr [esp + 0x14]
00725205 add ebx, eax
00725207 mov eax, dword ptr [esp + 0xc]
0072520b inc edi
0072520c add eax, 0x1c
0072520f mov dword ptr [esp + 0xc], eax
00725213 cmp edi, 4
00725216 jb 0x7251c2
00725218 mov ecx, esi
0072521a call 0x78cdc0
0072521f cmp eax, 2
00725222 je 0x725365
00725228 call 0x78cdc0
0072522d cmp eax, 3
00725230 je 0x725339
00725236 mov eax, dword ptr [esi + 0x130c]
0072523c cmp eax, 0x10
0072523f jne 0x725258
00725241 mov esi, dword ptr [esi + 0x1cb8]
00725247 test esi, esi
00725249 jne 0x725141
0072524f pop edi
00725250 pop esi
00725251 pop ebx
00725252 mov esp, ebp
00725254 pop ebp
00725255 ret 4
00725258 mov ecx, esi
0072525a cmp eax, 0x12
0072525d jne 0x72526e
0072525f push ebx
00725260 call 0x794420
00725265 pop edi
00725266 pop esi
00725267 pop ebx
00725268 mov esp, ebp
0072526a pop ebp
0072526b ret 4
0072526e call 0x78cdc0
00725273 cmp eax, 1
00725276 jne 0x725288
00725278 test ebx, ebx
0072527a jns 0x725288
0072527c mov eax, ebx
0072527e mov ecx, esi
00725280 neg eax
00725282 push eax
00725283 call 0x724d00
00725288 mov edi, dword ptr [esi + 0x129c]
0072528e xor eax, eax
00725290 push 0
00725292 lea ecx, [edi + ebx]
00725295 test ecx, ecx
00725297 cmovg eax, ecx
0072529a mov ecx, esi
0072529c mov dword ptr [esi + 0x129c], eax
007252a2 call 0x78cc70
007252a7 mov edx, dword ptr [esi + 0x1ca8]
007252ad mov ecx, dword ptr [esi + 0x1290]
007252b3 lea ecx, [ecx + edx*2]
007252b6 mov edx, dword ptr [esi + 0x129c]
007252bc mov dword ptr [esp + 0x14], ecx
007252c0 add ecx, edx
007252c2 cmp ecx, eax
007252c4 jle 0x7252d2
007252c6 mov edx, eax
007252c8 sub edx, dword ptr [esp + 0x14]
007252cc mov dword ptr [esi + 0x129c], edx
007252d2 cmp edx, 8
007252d5 jl 0x7252e7
007252d7 mov ecx, dword ptr [0xbfd680]
007252dd push 0x50
007252df lea ecx, [ecx + 0x14]
007252e2 call 0x884c80
007252e7 mov ecx, esi
007252e9 call 0x725600
007252ee mov ecx, esi
007252f0 call 0x78c810
007252f5 mov ecx, esi
007252f7 call 0x78cb90
007252fc test ebx, ebx
007252fe jle 0x725373
00725300 cmp dword ptr [esi + 0x129c], edi
00725306 jl 0x725373
00725308 mov eax, dword ptr [0xbfd65c]
0072530d add eax, 0x3da4c
00725312 xor ecx, ecx
00725314 cmp dword ptr [eax], esi
00725316 je 0x72532c
00725318 inc ecx
00725319 add eax, 0x6b0
0072531e cmp ecx, 8
00725321 jb 0x725314
00725323 pop edi
00725324 pop esi
00725325 pop ebx
00725326 mov esp, ebp
00725328 pop ebp
00725329 ret 4
0072532c mov byte ptr [eax + 0xd], 4
00725330 pop edi
00725331 pop esi
00725332 pop ebx
00725333 mov esp, ebp
00725335 pop ebp
00725336 ret 4
00725339 test ebx, ebx
0072533b jle 0x725373
0072533d push 0
0072533f lea eax, [esi + 0x294]
00725345 mov ecx, esi
00725347 push eax
00725348 lea eax, [ebx*2 + 1]
0072534f add eax, ebx
00725351 cdq 
00725352 sub eax, edx
00725354 sar eax, 1
00725356 push eax
00725357 call 0x725cc0
0072535c pop edi
0072535d pop esi
0072535e pop ebx
0072535f mov esp, ebp
00725361 pop ebp
00725362 ret 4
00725365 test ebx, ebx
00725367 jle 0x725373
00725369 mov dword ptr [esi + 0x129c], 1
00725373 pop edi
00725374 pop esi
00725375 pop ebx
00725376 mov esp, ebp
00725378 pop ebp
00725379 ret 4
0072537c int3 
0072537d int3 
0072537e int3 
0072537f int3 
