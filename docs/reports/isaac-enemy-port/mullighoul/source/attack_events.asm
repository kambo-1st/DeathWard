00545220 push ebp
00545221 mov ebp, esp
00545223 sub esp, 0xc4
00545229 mov eax, dword ptr [0xbaa3b4]
0054522e xor eax, ebp
00545230 mov dword ptr [ebp - 4], eax
00545233 push ebx
00545234 push esi
00545235 push edi
00545236 mov edi, ecx
00545238 cmp dword ptr [edi + 0x70], 0
0054523c je 0x5454e3
00545242 cmp byte ptr [edi + 0x80], 0
00545249 je 0x5454e3
0054524f push 0xb43580
00545254 lea ecx, [edi + 0x6c]
00545257 call 0x405e90
0054525c test al, al
0054525e je 0x5452ee
00545264 movss xmm0, dword ptr [0xb6a614]
0054526c mov eax, dword ptr [edi + 0xbb4]
00545272 movss dword ptr [ebp - 0xb4], xmm0
0054527a cmp eax, 0x12
0054527d jne 0x545289
0054527f movss xmm0, dword ptr [0xb6a6f0]
00545287 jmp 0x545296
00545289 cmp eax, 0x13
0054528c jne 0x54529e
0054528e movss xmm0, dword ptr [0xb6a480]
00545296 movss dword ptr [ebp - 0xb4], xmm0
0054529e mov esi, dword ptr [0xbfd680]
005452a4 lea ecx, [ebp - 0xb8]
005452aa mov dword ptr [ebp - 0xb8], 0x1d7
005452b4 call 0x8b1340
005452b9 movss xmm0, dword ptr [ebp - 0xb4]
005452c1 sub esp, 8
005452c4 mov dword ptr [esp + 4], 0
005452cc movss dword ptr [esp], xmm0
005452d1 push 0
005452d3 push 2
005452d5 push ecx
005452d6 mov dword ptr [esp], 0x3f800000
005452dd lea ecx, [esi + 0x29de0]
005452e3 push dword ptr [ebp - 0xb8]
005452e9 call 0x888de0
005452ee cmp dword ptr [edi + 0x70], 0
005452f2 je 0x5454ed
005452f8 push 0xb400ac
005452fd lea ecx, [edi + 0x6c]
00545300 call 0x405e90
00545305 test al, al
00545307 je 0x5454ed
0054530d movss xmm0, dword ptr [0xb6a614]
00545315 mov eax, dword ptr [edi + 0xbb4]
0054531b movss dword ptr [ebp - 0xb4], xmm0
00545323 cmp eax, 0x12
00545326 jne 0x545332
00545328 movss xmm0, dword ptr [0xb6a6f0]
00545330 jmp 0x54533f
00545332 cmp eax, 0x13
00545335 jne 0x545347
00545337 movss xmm0, dword ptr [0xb6a480]
0054533f movss dword ptr [ebp - 0xb4], xmm0
00545347 mov esi, dword ptr [0xbfd680]
0054534d lea ecx, [ebp - 0xb8]
00545353 mov dword ptr [ebp - 0xb8], 0x99
0054535d call 0x8b1340
00545362 movss xmm0, dword ptr [ebp - 0xb4]
0054536a sub esp, 8
0054536d mov dword ptr [esp + 4], 0
00545375 movss dword ptr [esp], xmm0
0054537a push 0
0054537c push 2
0054537e push ecx
0054537f mov dword ptr [esp], 0x3f800000
00545386 lea ecx, [esi + 0x29de0]
0054538c push dword ptr [ebp - 0xb8]
00545392 call 0x888de0
00545397 mov ecx, edi
00545399 call 0x695680
0054539e lea ecx, [ebp - 0xb0]
005453a4 mov esi, eax
005453a6 call 0x430d70
005453ab movss xmm1, dword ptr [esi + 0x2b8]
005453b3 lea ebx, [edi + 0x294]
005453b9 addss xmm1, dword ptr [esi + 0x294]
005453c1 movss xmm2, dword ptr [esi + 0x2bc]
005453c9 addss xmm2, dword ptr [esi + 0x298]
005453d1 subss xmm1, dword ptr [ebx]
005453d5 subss xmm2, dword ptr [ebx + 4]
005453da movaps xmm0, xmm1
005453dd movss dword ptr [ebp - 0xb8], xmm1
005453e5 mulss xmm0, xmm1
005453e9 movaps xmm1, xmm2
005453ec movss dword ptr [ebp - 0xb4], xmm2
005453f4 mulss xmm1, xmm2
005453f8 addss xmm0, xmm1
005453fc call 0x4228c0
00545401 movss xmm2, dword ptr [ebp - 0xb8]
00545409 xorps xmm1, xmm1
0054540c comiss xmm0, xmm1
0054540f movss xmm3, dword ptr [ebp - 0xb4]
00545417 jbe 0x545430
00545419 movss xmm1, dword ptr [0xb6a614]
00545421 divss xmm1, xmm0
00545425 movaps xmm0, xmm1
00545428 mulss xmm3, xmm1
0054542c mulss xmm2, xmm0
00545430 cmp dword ptr [edi + 0x314], 0
00545437 movups xmm0, xmmword ptr [0xbc4140]
0054543e mov eax, dword ptr [0xbc4168]
00545443 mulss xmm2, dword ptr [0xb6a974]
0054544b mov dword ptr [ebp - 0x5c], eax
0054544e mulss xmm3, dword ptr [0xb6a974]
00545456 mov dword ptr [ebp - 0x1c], 4
0054545d movups xmmword ptr [ebp - 0x84], xmm0
00545464 mov dword ptr [ebp - 0x58], 0x2000
0054546b movups xmm0, xmmword ptr [0xbc4150]
00545472 mov dword ptr [ebp - 0x54], 0
00545479 movss dword ptr [ebp - 0xc0], xmm2
00545481 movups xmmword ptr [ebp - 0x74], xmm0
00545485 movq xmm0, qword ptr [0xbc4160]
0054548d movss dword ptr [ebp - 0xbc], xmm3
00545495 movq qword ptr [ebp - 0x64], xmm0
0054549a jne 0x5454ba
0054549c cmp dword ptr [edi + 0x30], 0
005454a0 jne 0x5454ba
005454a2 movss xmm0, dword ptr [ebp - 0xa8]
005454aa addss xmm0, dword ptr [0xb6a8cc]
005454b2 movss dword ptr [ebp - 0xa8], xmm0
005454ba lea eax, [ebp - 0xb0]
005454c0 mov ecx, edi
005454c2 push eax
005454c3 push 0
005454c5 lea eax, [ebp - 0xc0]
005454cb push eax
005454cc push ebx
005454cd call 0x6a1a20
005454d2 pop edi
005454d3 pop esi
005454d4 pop ebx
005454d5 mov ecx, dword ptr [ebp - 4]
005454d8 xor ecx, ebp
005454da call 0x9eacd7
005454df mov esp, ebp
005454e1 pop ebp
005454e2 ret 
005454e3 mov dword ptr [edi + 0xab4], 3
005454ed mov ecx, dword ptr [ebp - 4]
005454f0 pop edi
005454f1 pop esi
005454f2 xor ecx, ebp
005454f4 pop ebx
005454f5 call 0x9eacd7
005454fa mov esp, ebp
005454fc pop ebp
005454fd ret 
