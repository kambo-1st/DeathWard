006d20d4 push 0x14
006d20d6 mov dword ptr [ebp - 0x3c], 0
006d20dd mov dword ptr [ebp - 0x38], 0
006d20e4 call 0x9eacf8
006d20e9 mov esi, eax
006d20eb mov dword ptr [ebp - 0x24], esi
006d20ee mov dword ptr [esi], esi
006d20f0 mov dword ptr [esi + 4], esi
006d20f3 mov dword ptr [esi + 8], esi
006d20f6 mov word ptr [esi + 0xc], 0x101
006d20fc mov dword ptr [ebp - 0x3c], esi
006d20ff movss xmm0, dword ptr [ebx + 0x10]
006d2104 mov byte ptr [ebp - 4], 0x17
006d2108 mulss xmm0, dword ptr [0xb6a940]
006d2110 push ecx
006d2111 divss xmm0, dword ptr [0xb6aa3c]
006d2119 movss dword ptr [ebp - 0x28], xmm0
006d211e fld dword ptr [ebp - 0x28]
006d2121 fstp qword ptr [esp]
006d2124 call 0x9ec3ac
006d2129 mov ecx, dword ptr [ebx + 8]
006d212c add esp, 8
006d212f movss xmm1, dword ptr [0xb6a914]
006d2137 movss xmm2, dword ptr [0xb6aa3c]
006d213f fstp dword ptr [ebp - 0x28]
006d2142 fld dword ptr [ebp - 0x28]
006d2145 fstp dword ptr [ebp - 0x28]
006d2148 cvttss2si edi, dword ptr [ebp - 0x28]
006d214d mov eax, dword ptr [0xbfd65c]
006d2152 mov eax, dword ptr [eax + 0x18190]
006d2158 mov dword ptr [ebp - 0x28], eax
006d215b mov dword ptr [ebp - 0x30], edi
006d215e movd xmm0, edi
006d2162 cvtdq2ps xmm0, xmm0
006d2165 divss xmm1, xmm0
006d2169 movss xmm0, dword ptr [ecx]
006d216d subss xmm0, xmm2
006d2171 movss dword ptr [ebp - 0x20], xmm1
006d2176 xorps xmm1, xmm1
006d2179 movss dword ptr [ebp - 0x18], xmm1
006d217e divss xmm0, xmm2
006d2182 addss xmm0, dword ptr [0xb6a480]
006d218a cvttss2si edx, xmm0
006d218e movss xmm0, dword ptr [ecx + 4]
006d2193 subss xmm0, dword ptr [0xb6ab20]
006d219b divss xmm0, xmm2
006d219f addss xmm0, dword ptr [0xb6a480]
006d21a7 cvttss2si ecx, xmm0
006d21ab test edx, edx
006d21ad js 0x6d21e7
006d21af mov eax, dword ptr [eax + 0xc]
006d21b2 cmp edx, eax
006d21b4 jge 0x6d21e7
006d21b6 test ecx, ecx
006d21b8 js 0x6d21e7
006d21ba mov esi, dword ptr [ebp - 0x28]
006d21bd cmp ecx, dword ptr [esi + 0x10]
006d21c0 mov esi, dword ptr [ebp - 0x24]
006d21c3 jge 0x6d21e7
006d21c5 imul eax, ecx
006d21c8 add eax, edx
006d21ca mov dword ptr [ebp - 0x28], eax
006d21cd js 0x6d21e7
006d21cf lea eax, [ebp - 0x28]
006d21d2 push eax
006d21d3 lea eax, [ebp - 0x4c]
006d21d6 push eax
006d21d7 lea ecx, [ebp - 0x3c]
006d21da call 0x4d1cd0
006d21df mov esi, dword ptr [ebp - 0x3c]
006d21e2 movss xmm1, dword ptr [ebp - 0x18]
006d21e7 test edi, edi
006d21e9 jle 0x6d231f
006d21ef nop
006d21f0 movaps xmm0, xmm1
006d21f3 call 0x411fe0
006d21f8 movss dword ptr [ebp - 0x28], xmm0
006d21fd movss xmm0, dword ptr [ebp - 0x18]
006d2202 call 0x412010
006d2207 movaps xmm1, xmm0
006d220a xorps xmm3, xmm3
006d220d movss xmm0, dword ptr [ebx + 0x10]
006d2212 xorps xmm2, xmm2
006d2215 comiss xmm0, xmm3
006d2218 movss dword ptr [ebp - 0x1c], xmm1
006d221d jbe 0x6d2301
006d2223 movss xmm3, dword ptr [0xb6aa3c]
006d222b movss xmm4, dword ptr [0xb6a480]
006d2233 mov edi, dword ptr [ebx + 8]
006d2236 nop word ptr [eax + eax]
006d2240 addss xmm2, dword ptr [0xb6a9c8]
006d2248 mov eax, dword ptr [0xbfd65c]
006d224d minss xmm2, xmm0
006d2251 mov esi, dword ptr [eax + 0x18190]
006d2257 movss xmm0, dword ptr [ebp - 0x28]
006d225c mulss xmm0, xmm2
006d2260 mulss xmm1, xmm2
006d2264 addss xmm0, dword ptr [edi]
006d2268 movss dword ptr [ebp - 0x2c], xmm2
006d226d addss xmm1, dword ptr [edi + 4]
006d2272 subss xmm0, xmm3
006d2276 subss xmm1, dword ptr [0xb6ab20]
006d227e divss xmm0, xmm3
006d2282 divss xmm1, xmm3
006d2286 addss xmm0, xmm4
006d228a addss xmm1, xmm4
006d228e cvttss2si ecx, xmm0
006d2292 cvttss2si eax, xmm1
006d2296 test ecx, ecx
006d2298 js 0x6d22ea
006d229a mov edx, dword ptr [esi + 0xc]
006d229d cmp ecx, edx
006d229f jge 0x6d22ea
006d22a1 test eax, eax
006d22a3 js 0x6d22ea
006d22a5 cmp eax, dword ptr [esi + 0x10]
006d22a8 jge 0x6d22ea
006d22aa imul eax, edx
006d22ad add eax, ecx
006d22af js 0x6d22ea
006d22b1 mov esi, dword ptr [esi + eax*4 + 0x24]
006d22b5 test esi, esi
006d22b7 je 0x6d22ea
006d22b9 mov eax, dword ptr [esi + 0x24]
006d22bc lea ecx, [ebp - 0x3c]
006d22bf mov dword ptr [ebp - 0x24], eax
006d22c2 lea eax, [ebp - 0x24]
006d22c5 push eax
006d22c6 lea eax, [ebp - 0x4c]
006d22c9 push eax
006d22ca call 0x4d1cd0
006d22cf cmp dword ptr [esi + 4], 3
006d22d3 je 0x6d22fe
006d22d5 movss xmm2, dword ptr [ebp - 0x2c]
006d22da movss xmm3, dword ptr [0xb6aa3c]
006d22e2 movss xmm4, dword ptr [0xb6a480]
006d22ea movss xmm0, dword ptr [ebx + 0x10]
006d22ef comiss xmm0, xmm2
006d22f2 jbe 0x6d22fe
006d22f4 movss xmm1, dword ptr [ebp - 0x1c]
006d22f9 jmp 0x6d2240
006d22fe mov edi, dword ptr [ebp - 0x30]
006d2301 movss xmm1, dword ptr [ebp - 0x18]
006d2306 sub edi, 1
006d2309 addss xmm1, dword ptr [ebp - 0x20]
006d230e mov dword ptr [ebp - 0x30], edi
006d2311 movss dword ptr [ebp - 0x18], xmm1
006d2316 jne 0x6d21f0
006d231c mov esi, dword ptr [ebp - 0x3c]
006d231f mov edi, dword ptr [esi]
006d2321 mov dword ptr [ebp - 0x2c], edi
006d2324 cmp edi, esi
006d2326 je 0x6d2699
006d232c movss xmm4, dword ptr [0xb6aa3c]
006d2334 movss xmm1, dword ptr [0xb6ab20]
006d233c nop dword ptr [eax]
006d2340 mov ecx, dword ptr [0xbfd65c]
006d2346 mov eax, dword ptr [edi + 0x10]
006d2349 cdq
006d234a push 0
006d234c mov ecx, dword ptr [ecx + 0x18190]
006d2352 push 0
006d2354 push 0
006d2356 push 0
006d2358 mov ecx, dword ptr [ecx + 0xc]
006d235b idiv ecx
006d235d push 2
006d235f movd xmm0, edx
006d2363 cvtdq2ps xmm0, xmm0
006d2366 mulss xmm0, xmm4
006d236a addss xmm0, xmm4
006d236e movss dword ptr [ebp - 0x44], xmm0
006d2373 movd xmm0, eax
006d2377 lea eax, [ebp - 0x44]
006d237a cvtdq2ps xmm0, xmm0
006d237d push eax
006d237e mov eax, dword ptr [ebp - 0x34]
006d2381 push dword ptr [ebx + 8]
006d2384 mov ecx, dword ptr [eax + 0x18190]
006d238a mulss xmm0, xmm4
006d238e addss xmm0, xmm1
006d2392 movss dword ptr [ebp - 0x40], xmm0
006d2397 call 0x7af4b0
006d239c test al, al
006d239e je 0x6d2673
006d23a4 mov eax, dword ptr [ebp - 0x34]
006d23a7 mov esi, dword ptr [edi + 0x10]
006d23aa mov ecx, dword ptr [eax + 0x18190]
006d23b0 mov eax, dword ptr [ecx + 4]
006d23b3 mov eax, dword ptr [eax + 0x10]
006d23b6 test eax, eax
006d23b8 je 0x6d23ce
006d23ba cmp dword ptr [eax + 8], 0x10
006d23be jne 0x6d23ce
006d23c0 cmp dword ptr [eax], 0x23
006d23c3 jne 0x6d23ce
006d23c5 mov dword ptr [ebp - 0x18], 0
006d23cc jmp 0x6d2418
006d23ce test esi, esi
006d23d0 jns 0x6d23db
006d23d2 mov dword ptr [ebp - 0x18], 4
006d23d9 jmp 0x6d2418
006d23db mov eax, dword ptr [ecx + esi*4 + 0x24]
006d23df test eax, eax
006d23e1 jne 0x6d2412
006d23e3 mov edx, dword ptr [ecx + esi*4 + 0x76c]
006d23ea lea eax, [edx - 0xbb8]
006d23f0 cmp eax, 0x3e7
006d23f5 ja 0x6d2400
006d23f7 mov dword ptr [ebp - 0x18], 1
006d23fe jmp 0x6d2418
006d2400 xor eax, eax
006d2402 cmp edx, 0x3e8
006d2408 mov edx, 3
006d240d cmovge eax, edx
006d2410 jmp 0x6d2415
006d2412 mov eax, dword ptr [eax + 0x3c]
006d2415 mov dword ptr [ebp - 0x18], eax
006d2418 cmp esi, 0x1bf
006d241e ja 0x6d2537
006d2424 mov esi, dword ptr [ecx + esi*4 + 0x24]
006d2428 mov dword ptr [ebp - 0x20], esi
006d242b test esi, esi
006d242d je 0x6d2539
006d2433 cmp dword ptr [esi + 4], 0xb
006d2437 jne 0x6d2539
006d243d cmp dword ptr [esi + 0xc], 0
006d2441 jne 0x6d24f0
006d2447 mov eax, dword ptr [0xbfd680]
006d244c mov esi, dword ptr [0xbfd65c]
006d2452 mov dword ptr [ebp - 0x30], esi
006d2455 mov ecx, dword ptr [eax + 0x29e90]
006d245b mov eax, dword ptr [eax + 0x29e94]
006d2461 sub eax, ecx
006d2463 and eax, 0xfffffffc
006d2466 cmp eax, 0x220
006d246b jle 0x6d248d
006d246d mov eax, dword ptr [ecx + 0x220]
006d2473 test eax, eax
006d2475 je 0x6d248d
006d2477 mov eax, dword ptr [eax + 0xb8]
006d247d and eax, 0x80000000
006d2482 or eax, 0
006d2485 je 0x6d248d
006d2487 mov byte ptr [ebp - 0x11], 1
006d248b jmp 0x6d2492
006d248d xor al, al
006d248f mov byte ptr [ebp - 0x11], al
006d2492 mov eax, dword ptr [ebp - 0x30]
006d2495 mov esi, dword ptr [esi + 0x1ba50]
006d249b cmp esi, dword ptr [eax + 0x1ba54]
006d24a1 je 0x6d24ed
006d24a3 mov eax, dword ptr [esi]
006d24a5 mov dword ptr [ebp - 0x1c], eax
006d24a8 cmp dword ptr [eax + 0x2c], 0
006d24ac jne 0x6d24df
006d24ae push 0x88
006d24b3 mov ecx, eax
006d24b5 call 0x78d4c0
006d24ba test eax, eax
006d24bc jg 0x6d250c
006d24be cmp byte ptr [ebp - 0x11], 0
006d24c2 je 0x6d24df
006d24c4 mov eax, dword ptr [ebp - 0x1c]
006d24c7 mov ecx, dword ptr [eax + 0x1d84]
006d24cd test ecx, ecx
006d24cf je 0x6d24df
006d24d1 push 0x88
006d24d6 call 0x78d4c0
006d24db test eax, eax
006d24dd jg 0x6d2501
006d24df mov eax, dword ptr [ebp - 0x30]
006d24e2 add esi, 4
006d24e5 cmp esi, dword ptr [eax + 0x1ba54]
006d24eb jne 0x6d24a3
006d24ed mov esi, dword ptr [ebp - 0x20]
006d24f0 mov eax, dword ptr [esi]
006d24f2 mov ecx, esi
006d24f4 push 4
006d24f6 mov eax, dword ptr [eax + 0x10]
006d24f9 call eax
006d24fb test al, al
006d24fd jne 0x6d256e
006d24ff jmp 0x6d2539
006d2501 mov eax, dword ptr [ebp - 0x1c]
006d2504 mov eax, dword ptr [eax + 0x1d84]
006d250a jmp 0x6d250f
006d250c mov eax, dword ptr [ebp - 0x1c]
006d250f mov esi, dword ptr [ebp - 0x20]
006d2512 test eax, eax
006d2514 je 0x6d24f0
006d2516 push 0
006d2518 mov ecx, esi
006d251a call 0x6e2140
006d251f cmp dword ptr [esi + 0x74], 0
006d2523 je 0x6d256e
006d2525 movss xmm1, dword ptr [0xb6a9c8]
006d252d lea ecx, [esi + 0x70]
006d2530 call 0x403c00
006d2535 jmp 0x6d256e
006d2537 xor esi, esi
006d2539 mov ecx, dword ptr [edi + 0x10]
006d253c cmp ecx, 0x1bf
006d2542 ja 0x6d2673
006d2548 mov eax, dword ptr [ebp - 0x34]
006d254b mov eax, dword ptr [eax + 0x18190]
006d2551 mov ecx, dword ptr [eax + ecx*4 + 0x24]
006d2555 test ecx, ecx
006d2557 je 0x6d2673
006d255d mov eax, dword ptr [ecx]
006d255f push 0
006d2561 mov eax, dword ptr [eax + 0x14]
006d2564 call eax
006d2566 test al, al
006d2568 je 0x6d2673
006d256e cmp dword ptr [ebp - 0x18], 3
006d2572 jne 0x6d2673
006d2578 mov eax, dword ptr [ebx + 8]
006d257b xorps xmm6, xmm6
006d257e movss xmm2, dword ptr [ebp - 0x44]
006d2583 movss xmm3, dword ptr [ebp - 0x40]
006d2588 movaps xmm4, xmm2
006d258b movaps xmm5, xmm3
006d258e subss xmm4, dword ptr [eax]
006d2592 subss xmm5, dword ptr [eax + 4]
006d2597 movaps xmm1, xmm4
006d259a andps xmm1, xmmword ptr [0xb6c980]
006d25a1 movaps xmm0, xmm5
006d25a4 andps xmm0, xmmword ptr [0xb6c980]
006d25ab comiss xmm1, xmm0
006d25ae jbe 0x6d25cc
006d25b0 comiss xmm6, xmm4
006d25b3 xorps xmm1, xmm1
006d25b6 jbe 0x6d25c2
006d25b8 movss xmm0, dword ptr [0xb6ae44]
006d25c0 jmp 0x6d25e6
006d25c2 movss xmm0, dword ptr [0xb6a614]
006d25ca jmp 0x6d25e6
006d25cc comiss xmm6, xmm5
006d25cf xorps xmm0, xmm0
006d25d2 jbe 0x6d25de
006d25d4 movss xmm1, dword ptr [0xb6ae44]
006d25dc jmp 0x6d25e6
006d25de movss xmm1, dword ptr [0xb6a614]
006d25e6 movss xmm4, dword ptr [0xb6aa3c]
006d25ee mulss xmm0, xmm4
006d25f2 mov eax, dword ptr [0xbfd65c]
006d25f7 mulss xmm1, xmm4
006d25fb addss xmm2, xmm0
006d25ff mov edi, dword ptr [eax + 0x18190]
006d2605 addss xmm3, xmm1
006d2609 movss xmm1, dword ptr [0xb6ab20]
006d2611 subss xmm2, xmm4
006d2615 subss xmm3, xmm1
006d2619 divss xmm2, xmm4
006d261d divss xmm3, xmm4
006d2621 addss xmm2, dword ptr [0xb6a480]
006d2629 addss xmm3, dword ptr [0xb6a480]
006d2631 cvttss2si ecx, xmm2
006d2635 cvttss2si eax, xmm3
006d2639 test ecx, ecx
006d263b js 0x6d2683
006d263d mov edx, dword ptr [edi + 0xc]
006d2640 cmp ecx, edx
006d2642 jge 0x6d2683
006d2644 test eax, eax
006d2646 js 0x6d2683
006d2648 cmp eax, dword ptr [edi + 0x10]
006d264b jge 0x6d2683
006d264d imul eax, edx
006d2650 add eax, ecx
006d2652 js 0x6d2683
006d2654 mov ecx, dword ptr [ebp - 0x34]
006d2657 mov ecx, dword ptr [ecx + 0x18190]
006d265d cmp eax, 0x1c0
006d2662 jge 0x6d266a
006d2664 mov eax, dword ptr [ecx + eax*4 + 0x24]
006d2668 jmp 0x6d266c
006d266a xor eax, eax
006d266c push esi
006d266d push eax
006d266e call 0x7d9890
006d2673 movss xmm1, dword ptr [0xb6ab20]
006d267b movss xmm4, dword ptr [0xb6aa3c]
006d2683 lea ecx, [ebp - 0x2c]
006d2686 call 0x40f830
006d268b mov edi, dword ptr [ebp - 0x2c]
006d268e mov esi, dword ptr [ebp - 0x3c]
006d2691 cmp edi, esi
006d2693 jne 0x6d2340
