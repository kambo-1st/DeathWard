00500fa0 push ebp
00500fa1 mov ebp, esp
00500fa3 and esp, 0xfffffff8
00500fa6 sub esp, 0x11c
00500fac mov eax, dword ptr [0xbaa3b4]
00500fb1 xor eax, esp
00500fb3 mov dword ptr [esp + 0x118], eax
00500fba push ebx
00500fbb push esi
00500fbc push edi
00500fbd mov edi, ecx
00500fbf movss xmm0, dword ptr [edi + 0x2c4]
00500fc7 mulss xmm0, dword ptr [0xb6a50c]
00500fcf mov edx, dword ptr [edi + 0xaf0]
00500fd5 movss dword ptr [edi + 0x2c4], xmm0
00500fdd test edx, edx
00500fdf jle 0x50106c
00500fe5 cvttss2si eax, dword ptr [edi + 0x2fc]
00500fed cvttss2si ecx, dword ptr [edi + 0x2f8]
00500ff5 sub ecx, eax
00500ff7 add ecx, edx
00500ff9 cmp dword ptr [edi + 0xe6c], -1
00501000 mov dword ptr [edi + 0xaf0], ecx
00501006 jne 0x501022
00501008 movss xmm0, dword ptr [0xc02fec]
00501010 movss dword ptr [edi + 0xe70], xmm0
00501018 movss xmm0, dword ptr [0xc02ff0]
00501020 jmp 0x501064
00501022 movss xmm2, dword ptr [0xb6a2cc]
0050102a lea eax, [esp + 0x18]
0050102e push eax
0050102f mov ecx, edi
00501031 call 0x6af380
00501036 movss xmm1, dword ptr [esp + 0x18]
0050103c ucomiss xmm1, dword ptr [0xc02fec]
00501043 movss xmm0, dword ptr [esp + 0x1c]
00501049 lahf 
0050104a test ah, 0x44
0050104d jp 0x50105c
0050104f ucomiss xmm0, dword ptr [0xc02ff0]
00501056 lahf 
00501057 test ah, 0x44
0050105a jnp 0x50106c
0050105c movss dword ptr [edi + 0xe70], xmm1
00501064 movss dword ptr [edi + 0xe74], xmm0
0050106c cmp dword ptr [edi + 0xaf0], 0
00501073 jg 0x501125
00501079 movss xmm1, dword ptr [0xb6aba8]
00501081 mov ecx, edi
00501083 push 7
00501085 push 0
00501087 call 0x6a15a0
0050108c test al, al
0050108e je 0x501125
00501094 mov eax, dword ptr [0xbfd65c]
00501099 mov eax, dword ptr [eax + 0x243624]
0050109f cmp eax, 1
005010a2 je 0x5010ad
005010a4 cmp eax, 3
005010a7 je 0x5010ad
005010a9 xor eax, eax
005010ab jmp 0x5010b2
005010ad mov eax, 1
005010b2 xor ecx, ecx
005010b4 cmp ecx, eax
005010b6 push ecx
005010b7 sbb eax, eax
005010b9 lea ecx, [edi + 0x3c]
005010bc and eax, 0xfffffff2
005010bf add eax, 0x1c
005010c2 push 0xb40510
005010c7 mov dword ptr [edi + 0xaf0], eax
005010cd call 0x4054f0
005010d2 cmp dword ptr [edi + 0xe6c], -1
005010d9 jne 0x5010f5
005010db movss xmm0, dword ptr [0xc02fec]
005010e3 movss dword ptr [edi + 0xe70], xmm0
005010eb movss xmm0, dword ptr [0xc02ff0]
005010f3 jmp 0x50111d
005010f5 movss xmm2, dword ptr [0xb6a2cc]
005010fd lea eax, [esp + 0x18]
00501101 push eax
00501102 mov ecx, edi
00501104 call 0x6af380
00501109 movss xmm0, dword ptr [esp + 0x18]
0050110f movss dword ptr [edi + 0xe70], xmm0
00501117 movss xmm0, dword ptr [esp + 0x1c]
0050111d movss dword ptr [edi + 0xe74], xmm0
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
0050124e lea ecx, [esp + 0xf8]
00501255 call 0x402120
0050125a mov esi, eax
0050125c call 0x6c3d90
00501261 mov ecx, dword ptr [0xbfd65c]
00501267 push eax
00501268 push 5
0050126a push 0
0050126c push 0xc02fec
00501271 push ebx
00501272 push 2
00501274 push 0x3e8
00501279 call 0x422e20
0050127e push 1
00501280 mov ebx, eax
00501282 push 0
00501284 push 0xff
00501289 push -1
0050128b mov edx, dword ptr [ebx]
0050128d mov ecx, ebx
0050128f push esi
00501290 call dword ptr [edx + 0x38]
00501293 movss xmm0, dword ptr [0xb6a614]
0050129b lea esi, [ebx + 0x314]
005012a1 mov dword ptr [ebx + 0xd0], 0
005012ab mov dword ptr [ebx + 0xd4], 0xc1200000
005012b5 mov ecx, dword ptr [esi]
005012b7 movss dword ptr [esp + 0x14], xmm0
005012bd mov dword ptr [ebx + 0x2b0], 0x3f800000
005012c7 test ecx, ecx
005012c9 je 0x5012df
005012cb lea eax, [esp + 0x10]
005012cf mov dword ptr [esp + 0x10], esi
005012d3 push eax
005012d4 add ecx, 0x324
005012da call 0x4bc3c0
005012df push esi
005012e0 mov ecx, edi
005012e2 mov dword ptr [esi], edi
005012e4 call 0x4bae70
005012e9 movss xmm0, dword ptr [ebx + 0x298]
005012f1 lea esi, [edi + 0x294]
005012f7 movss xmm1, dword ptr [ebx + 0x294]
005012ff lea ecx, [esp + 0x24]
00501303 subss xmm0, dword ptr [esi + 4]
00501308 subss xmm1, dword ptr [esi]
0050130c push 1
0050130e push 0
00501310 push 0xff
00501315 movss dword ptr [ebx + 0x3bc], xmm0
0050131d movaps xmm0, xmmword ptr [0xb6b9f0]
00501324 movss dword ptr [ebx + 0x3b8], xmm1
0050132c mov eax, dword ptr [ebx]
0050132e push -1
00501330 movups xmmword ptr [esp + 0x34], xmm0
00501335 mov byte ptr [ebx + 0x3b4], 1
0050133c xorps xmm0, xmm0
0050133f mov byte ptr [ebx + 0x13c], 1
00501346 push ecx
00501347 mov ecx, ebx
00501349 mov dword ptr [esp + 0x58], 0x3f19999a
00501351 movups xmmword ptr [esp + 0x48], xmm0
00501356 mov dword ptr [esp + 0x5c], 0x3dcccccd
0050135e mov dword ptr [esp + 0x60], 0x3dcccccd
00501366 call dword ptr [eax + 0x38]
00501369 lea ecx, [esp + 0x50]
0050136d call 0x430d70
00501372 cmp dword ptr [edi + 0x28], 0xf8
00501379 jne 0x5013d8
0050137b mov eax, dword ptr [esp + 0xac]
00501382 lea ecx, [esp + 0x24]
00501386 movaps xmm0, xmmword ptr [0xb6bb40]
0050138d or dword ptr [esp + 0xa8], 1
00501395 push 1
00501397 push 0
00501399 push 0xff
0050139e mov dword ptr [esp + 0xb8], eax
005013a5 mov eax, dword ptr [ebx]
005013a7 push -1
005013a9 movups xmmword ptr [esp + 0x34], xmm0
005013ae push ecx
005013af movaps xmm0, xmmword ptr [0xb6c550]
005013b6 mov ecx, ebx
005013b8 movups xmmword ptr [esp + 0x48], xmm0
005013bd mov dword ptr [esp + 0x58], 0x3e851eb8
005013c5 mov dword ptr [esp + 0x5c], 0x3d4ccccd
005013cd mov dword ptr [esp + 0x60], 0x3ecccccd
005013d5 call dword ptr [eax + 0x38]
005013d8 lea eax, [esp + 0x50]
005013dc mov ecx, edi
005013de push eax
005013df push 0
005013e1 lea eax, [esp + 0x20]
005013e5 push eax
005013e6 push esi
005013e7 call 0x6a1a20
005013ec mov eax, dword ptr [edi + 0xbb4]
005013f2 cmp eax, 0x12
005013f5 jne 0x501401
005013f7 movss xmm0, dword ptr [0xb6a6f0]
005013ff jmp 0x50140e
00501401 cmp eax, 0x13
00501404 jne 0x501414
00501406 movss xmm0, dword ptr [0xb6a480]
0050140e movss dword ptr [esp + 0x14], xmm0
00501414 mov esi, dword ptr [0xbfd680]
0050141a lea ecx, [esp + 0x10]
0050141e mov dword ptr [esp + 0x10], 0x92
00501426 call 0x8b1340
0050142b movss xmm0, dword ptr [esp + 0x14]
00501431 sub esp, 8
00501434 mov dword ptr [esp + 4], 0
0050143c movss dword ptr [esp], xmm0
00501441 push 0
00501443 push 2
00501445 push ecx
00501446 mov dword ptr [esp], 0x3f800000
0050144d lea ecx, [esi + 0x29de0]
00501453 push dword ptr [esp + 0x24]
00501457 call 0x888de0
0050145c cmp dword ptr [edi + 0x70], 0
00501460 je 0x50146b
00501462 cmp byte ptr [edi + 0x80], 0
00501469 jne 0x5014d9
0050146b mov esi, dword ptr [edi + 0x70]
0050146e test esi, esi
00501470 je 0x5014b7
00501472 cmp dword ptr [esi + 0x14], 0x10
00501476 mov eax, esi
00501478 jb 0x50147c
0050147a mov eax, dword ptr [esi]
0050147c mov ecx, 0xb41e80
00501481 mov dl, byte ptr [eax]
00501483 cmp dl, byte ptr [ecx]
00501485 jne 0x5014a1
00501487 test dl, dl
00501489 je 0x50149d
0050148b mov dl, byte ptr [eax + 1]
0050148e cmp dl, byte ptr [ecx + 1]
00501491 jne 0x5014a1
00501493 add eax, 2
00501496 add ecx, 2
00501499 test dl, dl
0050149b jne 0x501481
0050149d xor eax, eax
0050149f jmp 0x5014a6
005014a1 sbb eax, eax
005014a3 or eax, 1
005014a6 test eax, eax
005014a8 jne 0x5014b7
005014aa cmp byte ptr [esi + 0x34], al
005014ad je 0x5014d9
005014af cmp byte ptr [edi + 0x80], al
005014b5 jne 0x5014d9
005014b7 push 1
005014b9 push 0xb41e80
005014be lea ecx, [edi + 0x3c]
005014c1 call 0x405740
005014c6 test al, al
005014c8 je 0x5014d9
005014ca lea ecx, [edi + 0x6c]
005014cd call 0x405330
005014d2 mov byte ptr [edi + 0x80], 1
005014d9 mov ecx, dword ptr [esp + 0x124]
005014e0 pop edi
005014e1 pop esi
005014e2 pop ebx
005014e3 xor ecx, esp
005014e5 call 0x9eacd7
005014ea mov esp, ebp
005014ec pop ebp
005014ed ret 
