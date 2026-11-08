00682280 push ebx
00682281 mov ebx, esp
00682283 sub esp, 8
00682286 and esp, 0xfffffff8
00682289 add esp, 4
0068228c push ebp
0068228d mov ebp, dword ptr [ebx + 4]
00682290 mov dword ptr [esp + 4], ebp
00682294 mov ebp, esp
00682296 sub esp, 0x40
00682299 cmp byte ptr [ebx + 8], 0
0068229d push esi
0068229e push edi
0068229f mov edi, ecx
006822a1 mov dword ptr [ebp - 0x18], edi
006822a4 jne 0x6822ad
006822a6 mov byte ptr [edi + 0x188], 0
006822ad cmp dword ptr [edi + 0x32c], 0
006822b4 jne 0x68363f
006822ba mov eax, dword ptr [edi + 0x17c]
006822c0 mov dword ptr [ebp - 0x10], eax
006822c3 test eax, eax
006822c5 je 0x68363f
006822cb cmp dword ptr [edi + 0x28], 9
006822cf mov esi, dword ptr [0xbfd65c]
006822d5 mov esi, dword ptr [esi + 0x18190]
006822db mov dword ptr [ebp - 0x38], esi
006822de jne 0x6822f4
006822e0 cmp eax, 4
006822e3 jne 0x6822f4
006822e5 cmp dword ptr [esi + 8], 0x10
006822e9 mov ecx, 6
006822ee cmove eax, ecx
006822f1 mov dword ptr [ebp - 0x10], eax
006822f4 sub esp, 0xc
006822f7 lea eax, [edi + 0x294]
006822fd mov dword ptr [ebp - 0x14], eax
00682300 xorps xmm3, xmm3
00682303 mov ecx, esi
00682305 mov dword ptr [esp + 8], 0
0068230d mov dword ptr [esp + 4], 0
00682315 mov dword ptr [esp], 0
0068231c push eax
0068231d lea eax, [ebp - 0x40]
00682320 push eax
00682321 call 0x7cec10
00682326 movss xmm4, dword ptr [0xc02fec]
0068232e movss xmm5, dword ptr [0xc02ff0]
00682336 mov eax, dword ptr [ebp - 0x10]
00682339 movss dword ptr [ebp - 0x30], xmm4
0068233e movss dword ptr [ebp - 0x34], xmm5
00682343 cmp eax, 1
00682346 jne 0x6823f5
0068234c cmp byte ptr [ebx + 8], 0
00682350 movss xmm1, dword ptr [ebp - 0x40]
00682355 jne 0x6823e3
0068235b movss xmm0, dword ptr [edi + 0x294]
00682363 lea ecx, [edi + 0x294]
00682369 ucomiss xmm0, xmm1
0068236c lahf 
0068236d test ah, 0x44
00682370 jnp 0x6823cd
00682372 mov byte ptr [edi + 0x188], 1
00682379 mov eax, dword ptr [edi + 0x2b8]
0068237f mov dword ptr [edi + 0x18c], eax
00682385 mov eax, dword ptr [edi + 0x2bc]
0068238b mov dword ptr [edi + 0x190], eax
00682391 movss xmm0, dword ptr [ecx]
00682395 comiss xmm0, xmm1
00682398 jbe 0x6823a4
0068239a movss xmm0, dword ptr [0xb6ae44]
006823a2 jmp 0x6823ac
006823a4 movss xmm0, dword ptr [0xb6a614]
006823ac movss dword ptr [edi + 0x194], xmm0
006823b4 mov dword ptr [edi + 0x198], 0
006823be movss dword ptr [ecx], xmm1
006823c2 pop edi
006823c3 pop esi
006823c4 mov esp, ebp
006823c6 pop ebp
006823c7 mov esp, ebx
006823c9 pop ebx
006823ca ret 4
006823cd mov byte ptr [edi + 0x188], 0
006823d4 movss dword ptr [ecx], xmm1
006823d8 pop edi
006823d9 pop esi
006823da mov esp, ebp
006823dc pop ebp
006823dd mov esp, ebx
006823df pop ebx
006823e0 ret 4
006823e3 mov ecx, dword ptr [ebp - 0x14]
006823e6 movss dword ptr [ecx], xmm1
006823ea pop edi
006823eb pop esi
006823ec mov esp, ebp
006823ee pop ebp
006823ef mov esp, ebx
006823f1 pop ebx
006823f2 ret 4
006823f5 cmp eax, 2
006823f8 jne 0x68248f
006823fe cmp byte ptr [ebx + 8], 0
00682402 movss xmm1, dword ptr [ebp - 0x3c]
00682407 jne 0x68247c
00682409 movss xmm0, dword ptr [edi + 0x298]
00682411 ucomiss xmm0, xmm1
00682414 lahf 
00682415 test ah, 0x44
00682418 jnp 0x682475
0068241a comiss xmm0, xmm1
0068241d mov byte ptr [edi + 0x188], 1
00682424 mov eax, dword ptr [edi + 0x2b8]
0068242a mov dword ptr [edi + 0x18c], eax
00682430 mov eax, dword ptr [edi + 0x2bc]
00682436 mov dword ptr [edi + 0x190], eax
0068243c jbe 0x682448
0068243e movss xmm0, dword ptr [0xb6ae44]
00682446 jmp 0x682450
00682448 movss xmm0, dword ptr [0xb6a614]
00682450 mov dword ptr [edi + 0x194], 0
0068245a movss dword ptr [edi + 0x198], xmm0
00682462 movss dword ptr [edi + 0x298], xmm1
0068246a pop edi
0068246b pop esi
0068246c mov esp, ebp
0068246e pop ebp
0068246f mov esp, ebx
00682471 pop ebx
00682472 ret 4
00682475 mov byte ptr [edi + 0x188], 0
0068247c movss dword ptr [edi + 0x298], xmm1
00682484 pop edi
00682485 pop esi
00682486 mov esp, ebp
00682488 pop ebp
00682489 mov esp, ebx
0068248b pop ebx
0068248c ret 4
0068248f movss xmm3, dword ptr [0xb6ae44]
00682497 movss xmm6, dword ptr [0xb6a614]
0068249f cmp eax, 3
006824a2 je 0x6824b7
006824a4 cmp eax, 5
006824a7 je 0x6824b7
006824a9 cmp eax, 6
006824ac je 0x6824b7
006824ae cmp eax, 7
006824b1 jne 0x68257f
006824b7 mov dl, byte ptr [ebx + 8]
006824ba lea ecx, [edi + 0x294]
006824c0 movss xmm1, dword ptr [ebp - 0x3c]
006824c5 movss xmm2, dword ptr [ebp - 0x40]
006824ca test dl, dl
006824cc jne 0x682574
006824d2 movss xmm0, dword ptr [ecx]
006824d6 ucomiss xmm0, xmm2
006824d9 lahf 
006824da test ah, 0x44
006824dd jp 0x682508
006824df movss xmm0, dword ptr [edi + 0x298]
006824e7 ucomiss xmm0, xmm1
006824ea lahf 
006824eb test ah, 0x44
006824ee jp 0x682508
006824f0 mov eax, dword ptr [ebp - 0x10]
006824f3 mov byte ptr [edi + 0x188], 0
006824fa movss dword ptr [ecx], xmm2
006824fe movss dword ptr [ecx + 4], xmm1
00682503 jmp 0x682588
00682508 mov byte ptr [edi + 0x188], 1
0068250f mov eax, dword ptr [edi + 0x2b8]
00682515 mov dword ptr [edi + 0x18c], eax
0068251b mov eax, dword ptr [edi + 0x2bc]
00682521 mov dword ptr [edi + 0x190], eax
00682527 movss xmm0, dword ptr [ecx]
0068252b ucomiss xmm0, xmm2
0068252e lahf 
0068252f test ah, 0x44
00682532 jnp 0x68254a
00682534 comiss xmm0, xmm2
00682537 jbe 0x68253e
00682539 movaps xmm0, xmm6
0068253c jmp 0x682541
0068253e movaps xmm0, xmm3
00682541 addss xmm0, xmm4
00682545 movss dword ptr [ebp - 0x30], xmm0
0068254a movss xmm0, dword ptr [edi + 0x298]
00682552 ucomiss xmm0, xmm1
00682555 lahf 
00682556 test ah, 0x44
00682559 jnp 0x682571
0068255b comiss xmm0, xmm1
0068255e jbe 0x682565
00682560 movaps xmm0, xmm6
00682563 jmp 0x682568
00682565 movaps xmm0, xmm3
00682568 addss xmm0, xmm5
0068256c movss dword ptr [ebp - 0x34], xmm0
00682571 mov eax, dword ptr [ebp - 0x10]
00682574 movss dword ptr [ecx], xmm2
00682578 movss dword ptr [ecx + 4], xmm1
0068257d jmp 0x682588
0068257f mov dl, byte ptr [ebx + 8]
00682582 lea ecx, [edi + 0x294]
00682588 cmp eax, 4
0068258b jne 0x6826f6
00682591 test dl, dl
00682593 jne 0x68363f
00682599 mov eax, dword ptr [0xbfd65c]
0068259e mov eax, dword ptr [eax + 0x18190]
006825a4 cmp dword ptr [eax + 0x1d1c], 0x37
006825ab je 0x6825bd
006825ad mov eax, dword ptr [eax + 4]
006825b0 mov byte ptr [ebp - 1], dl
006825b3 mov eax, dword ptr [eax + 0x44]
006825b6 shr eax, 0xf
006825b9 test al, 1
006825bb je 0x6825c1
006825bd mov byte ptr [ebp - 1], 1
006825c1 push dword ptr [ecx + 4]
006825c4 push dword ptr [ecx]
006825c6 mov ecx, esi
006825c8 call 0x7aee40
006825cd mov dword ptr [ebp - 0x28], eax
006825d0 cmp eax, 4
006825d3 je 0x6825e1
006825d5 cmp eax, 5
006825d8 je 0x6825e1
006825da xor cl, cl
006825dc jmp 0x682682
006825e1 sub esp, 0xc
006825e4 mov byte ptr [ebp - 2], 1
006825e8 lea eax, [edi + 0x294]
006825ee xorps xmm3, xmm3
006825f1 mov dword ptr [esp + 8], 0
006825f9 mov dword ptr [esp + 4], 0
00682601 mov dword ptr [esp], 0
00682608 push eax
00682609 lea eax, [ebp - 0x40]
0068260c push eax
0068260d mov eax, dword ptr [0xbfd65c]
00682612 mov ecx, dword ptr [eax + 0x18190]
00682618 call 0x7cec10
0068261d lea eax, [edi + 0x294]
00682623 push eax
00682624 lea ecx, [ebp - 0x40]
00682627 call 0x962ca0
0068262c test al, al
0068262e je 0x68267c
00682630 cmp byte ptr [ebp - 1], 0
00682634 jne 0x68363f
0068263a movss xmm1, dword ptr [ebp - 0x3c]
0068263f lea edx, [edi + 0x294]
00682645 movss xmm0, dword ptr [ebp - 0x40]
0068264a subss xmm1, dword ptr [edx + 4]
0068264f subss xmm0, dword ptr [edx]
00682653 mulss xmm1, dword ptr [edi + 0x2bc]
0068265b mulss xmm0, dword ptr [edi + 0x2b8]
00682663 addss xmm1, xmm0
00682667 comiss xmm1, dword ptr [0xb6a18c]
0068266e jae 0x68363f
00682674 mov eax, dword ptr [ebp - 0x28]
00682677 mov cl, byte ptr [ebp - 2]
0068267a jmp 0x682688
0068267c mov eax, dword ptr [ebp - 0x28]
0068267f mov cl, byte ptr [ebp - 2]
00682682 lea edx, [edi + 0x294]
00682688 cmp eax, 3
0068268b je 0x6826a4
0068268d test cl, cl
0068268f jne 0x6826a4
00682691 cmp dword ptr [edi + 0x28], 2
00682695 jne 0x68363f
0068269b cmp eax, 2
0068269e jne 0x68363f
006826a4 push edx
006826a5 mov ecx, esi
006826a7 call 0x447f80
006826ac test eax, eax
006826ae je 0x68363f
006826b4 lea eax, [edi + 0x294]
006826ba mov ecx, esi
006826bc push eax
006826bd call 0x447f80
006826c2 cmp dword ptr [eax + 4], 7
006826c6 je 0x68363f
006826cc mov byte ptr [edi + 0x188], 1
006826d3 mov eax, dword ptr [edi + 0x2b8]
006826d9 mov dword ptr [edi + 0x18c], eax
006826df mov eax, dword ptr [edi + 0x2bc]
006826e5 mov dword ptr [edi + 0x190], eax
006826eb pop edi
006826ec pop esi
006826ed mov esp, ebp
006826ef pop ebp
006826f0 mov esp, ebx
006826f2 pop ebx
006826f3 ret 4
006826f6 mov eax, dword ptr [edi + 0x170]
006826fc mov edx, dword ptr [edi + 0x174]
00682702 mov dword ptr [ebp - 0x1c], eax
00682705 cmp eax, edx
00682707 je 0x68363f
0068270d movss xmm2, dword ptr [0xc02fec]
00682715 sub edx, eax
00682717 movss xmm1, dword ptr [0xc02ff0]
0068271f movss xmm6, dword ptr [0xb6aa3c]
00682727 movss xmm3, dword ptr [0xb6a480]
0068272f movss xmm4, dword ptr [0xb6ab20]
00682737 sar edx, 3
0068273a cmp dword ptr [ebp - 0x10], 5
0068273e mov dword ptr [ebp - 0x20], edx
00682741 movss dword ptr [ebp - 0xc], xmm2
00682746 movss dword ptr [ebp - 0x40], xmm2
0068274b movss dword ptr [ebp - 8], xmm1
00682750 movss dword ptr [ebp - 0x3c], xmm1
00682755 jne 0x682839
0068275b test edx, edx
0068275d je 0x682d7d
00682763 xor edi, edi
00682765 nop word ptr [eax + eax]
00682770 movss xmm0, dword ptr [eax + edi*8]
00682775 movss xmm1, dword ptr [eax + edi*8 + 4]
0068277b movss dword ptr [ebp - 0x2c], xmm0
00682780 addss xmm0, dword ptr [ecx]
00682784 movss dword ptr [ebp - 0x28], xmm1
00682789 addss xmm1, dword ptr [ecx + 4]
0068278e subss xmm0, xmm6
00682792 subss xmm1, xmm4
00682796 divss xmm0, xmm6
0068279a divss xmm1, xmm6
0068279e addss xmm0, xmm3
006827a2 addss xmm1, xmm3
006827a6 cvttss2si edx, xmm0
006827aa cvttss2si eax, xmm1
006827ae test edx, edx
006827b0 js 0x6827c9
006827b2 mov ecx, dword ptr [esi + 0xc]
006827b5 cmp edx, ecx
006827b7 jge 0x6827c9
006827b9 test eax, eax
006827bb js 0x6827c9
006827bd cmp eax, dword ptr [esi + 0x10]
006827c0 jge 0x6827c9
006827c2 imul eax, ecx
006827c5 add eax, edx
006827c7 jmp 0x6827cc
006827c9 or eax, 0xffffffff
006827cc push eax
006827cd mov ecx, esi
006827cf call 0x7aeec0
006827d4 test eax, eax
006827d6 je 0x682802
006827d8 movss xmm2, dword ptr [ebp - 0x2c]
006827dd movss xmm1, dword ptr [ebp - 0x28]
006827e2 addss xmm2, dword ptr [ebp - 0xc]
006827e7 addss xmm1, dword ptr [ebp - 8]
006827ec movss dword ptr [ebp - 0xc], xmm2
006827f1 movss dword ptr [ebp - 0x40], xmm2
006827f6 movss dword ptr [ebp - 8], xmm1
006827fb movss dword ptr [ebp - 0x3c], xmm1
00682800 jmp 0x68280c
00682802 movss xmm1, dword ptr [ebp - 8]
00682807 movss xmm2, dword ptr [ebp - 0xc]
0068280c movss xmm6, dword ptr [0xb6aa3c]
00682814 inc edi
00682815 movss xmm3, dword ptr [0xb6a480]
0068281d movss xmm4, dword ptr [0xb6ab20]
00682825 mov eax, dword ptr [ebp - 0x1c]
00682828 mov ecx, dword ptr [ebp - 0x14]
0068282b cmp edi, dword ptr [ebp - 0x20]
0068282e jb 0x682770
00682834 jmp 0x682d7a
00682839 cmp dword ptr [ebp - 0x10], 7
0068283d jne 0x682911
00682843 test edx, edx
00682845 je 0x682d7d
0068284b xor edi, edi
0068284d nop dword ptr [eax]
00682850 movss xmm0, dword ptr [eax + edi*8]
00682855 movss xmm1, dword ptr [ecx + 4]
0068285a addss xmm1, dword ptr [eax + edi*8 + 4]
00682860 movss dword ptr [ebp - 0x2c], xmm0
00682865 addss xmm0, dword ptr [ecx]
00682869 subss xmm1, xmm4
0068286d subss xmm0, xmm6
00682871 divss xmm1, xmm6
00682875 divss xmm0, xmm6
00682879 addss xmm1, xmm3
0068287d addss xmm0, xmm3
00682881 cvttss2si eax, xmm1
00682885 cvttss2si edx, xmm0
00682889 test edx, edx
0068288b js 0x6828a4
0068288d mov ecx, dword ptr [esi + 0xc]
00682890 cmp edx, ecx
00682892 jge 0x6828a4
00682894 test eax, eax
00682896 js 0x6828a4
00682898 cmp eax, dword ptr [esi + 0x10]
0068289b jge 0x6828a4
0068289d imul eax, ecx
006828a0 add eax, edx
006828a2 jmp 0x6828a7
006828a4 or eax, 0xffffffff
006828a7 push eax
006828a8 mov ecx, esi
006828aa call 0x7aeec0
006828af movss xmm1, dword ptr [ebp - 8]
006828b4 cmp eax, 1
006828b7 mov eax, dword ptr [ebp - 0x1c]
006828ba je 0x6828e2
006828bc movss xmm2, dword ptr [ebp - 0x2c]
006828c1 addss xmm2, dword ptr [ebp - 0xc]
006828c6 addss xmm1, dword ptr [eax + edi*8 + 4]
006828cc movss dword ptr [ebp - 0xc], xmm2
006828d1 movss dword ptr [ebp - 0x40], xmm2
006828d6 movss dword ptr [ebp - 8], xmm1
006828db movss dword ptr [ebp - 0x3c], xmm1
006828e0 jmp 0x6828e7
006828e2 movss xmm2, dword ptr [ebp - 0xc]
006828e7 movss xmm6, dword ptr [0xb6aa3c]
006828ef inc edi
006828f0 movss xmm3, dword ptr [0xb6a480]
006828f8 movss xmm4, dword ptr [0xb6ab20]
00682900 mov ecx, dword ptr [ebp - 0x14]
00682903 cmp edi, dword ptr [ebp - 0x20]
00682906 jb 0x682850
0068290c jmp 0x682d7a
00682911 cmp dword ptr [ebp - 0x10], 6
00682915 jne 0x682c89
0068291b xor ecx, ecx
0068291d mov dword ptr [ebp - 0x28], ecx
00682920 test edx, edx
00682922 je 0x682d7d
00682928 jmp 0x682938
0068292a nop word ptr [eax + eax]
00682930 movss xmm4, dword ptr [0xb6ab20]
00682938 mov eax, dword ptr [edi + 0x170]
0068293e movss xmm1, dword ptr [edi + 0x298]
00682946 movss xmm0, dword ptr [eax + ecx*8]
0068294b addss xmm1, dword ptr [eax + ecx*8 + 4]
00682951 addss xmm0, dword ptr [edi + 0x294]
00682959 subss xmm1, xmm4
0068295d subss xmm0, xmm6
00682961 divss xmm1, xmm6
00682965 divss xmm0, xmm6
00682969 addss xmm1, xmm3
0068296d addss xmm0, xmm3
00682971 cvttss2si eax, xmm1
00682975 cvttss2si ecx, xmm0
00682979 mov dword ptr [ebp - 0x1c], eax
0068297c mov dword ptr [ebp - 0x24], ecx
0068297f test ecx, ecx
00682981 js 0x6829aa
00682983 mov edx, dword ptr [esi + 0xc]
00682986 cmp ecx, edx
00682988 jge 0x6829aa
0068298a test eax, eax
0068298c js 0x6829aa
0068298e cmp eax, dword ptr [esi + 0x10]
00682991 jge 0x6829aa
00682993 imul eax, edx
00682996 add eax, ecx
00682998 mov ecx, esi
0068299a push eax
0068299b call 0x7aeec0
006829a0 mov edx, eax
006829a2 mov eax, dword ptr [ebp - 0x24]
006829a5 mov dword ptr [ebp - 0x2c], eax
006829a8 jmp 0x6829bf
006829aa push -1
006829ac mov ecx, esi
006829ae call 0x7aeec0
006829b3 mov edx, eax
006829b5 mov eax, dword ptr [ebp - 0x24]
006829b8 mov dword ptr [ebp - 0x2c], eax
006829bb test eax, eax
006829bd js 0x6829e1
006829bf mov ecx, dword ptr [ebp - 0x1c]
006829c2 cmp eax, dword ptr [esi + 0xc]
006829c5 jge 0x6829e4
006829c7 test ecx, ecx
006829c9 js 0x6829e4
006829cb cmp ecx, dword ptr [esi + 0x10]
006829ce jge 0x6829e4
006829d0 mov eax, ecx
006829d2 imul eax, dword ptr [esi + 0xc]
006829d6 add eax, dword ptr [ebp - 0x2c]
006829d9 js 0x6829e4
006829db mov eax, dword ptr [esi + eax*4 + 0x24]
006829df jmp 0x6829e6
006829e1 mov ecx, dword ptr [ebp - 0x1c]
006829e4 xor eax, eax
006829e6 test edx, edx
006829e8 je 0x682a2e
006829ea cmp edx, 1
006829ed je 0x682a2e
006829ef test eax, eax
006829f1 je 0x6829f9
006829f3 cmp dword ptr [eax + 4], 7
006829f7 je 0x682a2e
006829f9 mov esi, dword ptr [ebp - 0x28]
006829fc mov eax, dword ptr [edi + 0x170]
00682a02 movss xmm0, dword ptr [ebp - 0xc]
00682a07 addss xmm0, dword ptr [eax + esi*8]
00682a0c movss dword ptr [ebp - 0xc], xmm0
00682a11 movss dword ptr [ebp - 0x40], xmm0
00682a16 movss xmm0, dword ptr [ebp - 8]
00682a1b addss xmm0, dword ptr [eax + esi*8 + 4]
00682a21 mov esi, dword ptr [ebp - 0x38]
00682a24 movss dword ptr [ebp - 8], xmm0
00682a29 movss dword ptr [ebp - 0x3c], xmm0
00682a2e cmp byte ptr [ebx + 8], 0
00682a32 jne 0x682c18
00682a38 cmp dword ptr [edi + 0x28], 3
00682a3c jne 0x682c18
00682a42 cmp dword ptr [edi + 0x2c], 0x4b
00682a46 jne 0x682c18
00682a4c cmp edx, 3
00682a4f je 0x682a5a
00682a51 cmp edx, 2
00682a54 jne 0x682c18
00682a5a mov eax, dword ptr [0xbfd65c]
00682a5f mov edx, dword ptr [eax + 0x18190]
00682a65 mov eax, dword ptr [ebp - 0x24]
00682a68 test eax, eax
00682a6a js 0x682c18
00682a70 cmp eax, dword ptr [edx + 0xc]
00682a73 jge 0x682c18
00682a79 test ecx, ecx
00682a7b js 0x682c18
00682a81 cmp ecx, dword ptr [edx + 0x10]
00682a84 jge 0x682c18
00682a8a imul ecx, dword ptr [edx + 0xc]
00682a8e add ecx, eax
00682a90 js 0x682c6d
00682a96 cmp ecx, 0x1c0
00682a9c jge 0x682c18
00682aa2 mov ecx, dword ptr [esi + ecx*4 + 0x24]
00682aa6 mov dword ptr [ebp - 0x2c], ecx
00682aa9 test ecx, ecx
00682aab je 0x682c18
00682ab1 movss xmm1, dword ptr [edi + 0x2bc]
00682ab9 movss xmm0, dword ptr [edi + 0x2b8]
00682ac1 mulss xmm0, xmm0
00682ac5 mulss xmm1, xmm1
00682ac9 addss xmm0, xmm1
00682acd comiss xmm0, dword ptr [0xb6a9ec]
00682ad4 jbe 0x682c47
00682ada cmp dword ptr [ecx + 0x3c], 3
00682ade jne 0x682c47
00682ae4 mov eax, dword ptr [ecx]
00682ae6 push 0
00682ae8 mov eax, dword ptr [eax + 0x14]
00682aeb call eax
00682aed test al, al
00682aef je 0x682c47
00682af5 mov ecx, dword ptr [0xbfd65c]
00682afb xorps xmm7, xmm7
00682afe movss xmm6, dword ptr [0xb6aa3c]
00682b06 mov eax, dword ptr [ecx + 0x18190]
00682b0c mov dword ptr [ebp - 0x24], eax
00682b0f mov ecx, dword ptr [eax + 0xc]
00682b12 mov eax, dword ptr [ebp - 0x2c]
00682b15 mov eax, dword ptr [eax + 0x24]
00682b18 cdq 
00682b19 idiv ecx
00682b1b movd xmm4, edx
00682b1f cvtdq2ps xmm4, xmm4
00682b22 movd xmm5, eax
00682b26 cvtdq2ps xmm5, xmm5
00682b29 mulss xmm4, xmm6
00682b2d mulss xmm5, xmm6
00682b31 addss xmm4, xmm6
00682b35 addss xmm5, dword ptr [0xb6ab20]
00682b3d movaps xmm2, xmm4
00682b40 subss xmm2, dword ptr [edi + 0x294]
00682b48 movaps xmm3, xmm5
00682b4b subss xmm3, dword ptr [edi + 0x298]
00682b53 movaps xmm1, xmm2
00682b56 andps xmm1, xmmword ptr [0xb6c980]
00682b5d movaps xmm0, xmm3
00682b60 andps xmm0, xmmword ptr [0xb6c980]
00682b67 comiss xmm1, xmm0
00682b6a jbe 0x682b88
00682b6c comiss xmm7, xmm2
00682b6f xorps xmm0, xmm0
00682b72 jbe 0x682b7e
00682b74 movss xmm1, dword ptr [0xb6ae44]
00682b7c jmp 0x682ba2
00682b7e movss xmm1, dword ptr [0xb6a614]
00682b86 jmp 0x682ba2
00682b88 comiss xmm7, xmm3
00682b8b xorps xmm1, xmm1
00682b8e jbe 0x682b9a
00682b90 movss xmm0, dword ptr [0xb6ae44]
00682b98 jmp 0x682ba2
00682b9a movss xmm0, dword ptr [0xb6a614]
00682ba2 mulss xmm1, xmm6
00682ba6 movss xmm3, dword ptr [0xb6a480]
00682bae mulss xmm0, xmm6
00682bb2 addss xmm1, xmm4
00682bb6 subss xmm1, xmm6
00682bba divss xmm1, xmm6
00682bbe addss xmm1, xmm3
00682bc2 cvttss2si edx, xmm1
00682bc6 test edx, edx
00682bc8 js 0x682c28
00682bca cmp edx, ecx
00682bcc jge 0x682c28
00682bce addss xmm0, xmm5
00682bd2 subss xmm0, dword ptr [0xb6ab20]
00682bda divss xmm0, xmm6
00682bde addss xmm0, xmm3
00682be2 cvttss2si eax, xmm0
00682be6 test eax, eax
00682be8 js 0x682c28
00682bea mov edi, dword ptr [ebp - 0x24]
00682bed cmp eax, dword ptr [edi + 0x10]
00682bf0 mov edi, dword ptr [ebp - 0x18]
00682bf3 jge 0x682c28
00682bf5 imul ecx, eax
00682bf8 add ecx, edx
00682bfa js 0x682c28
00682bfc cmp ecx, 0x1c0
00682c02 jge 0x682c0a
00682c04 mov eax, dword ptr [esi + ecx*4 + 0x24]
00682c08 jmp 0x682c0c
00682c0a xor eax, eax
00682c0c push dword ptr [ebp - 0x2c]
00682c0f mov ecx, dword ptr [ebp - 0x24]
00682c12 push eax
00682c13 call 0x7d9890
00682c18 movss xmm6, dword ptr [0xb6aa3c]
00682c20 movss xmm3, dword ptr [0xb6a480]
00682c28 movss xmm2, dword ptr [ebp - 0xc]
00682c2d movss xmm1, dword ptr [ebp - 8]
00682c32 mov ecx, dword ptr [ebp - 0x28]
00682c35 inc ecx
00682c36 mov dword ptr [ebp - 0x28], ecx
00682c39 cmp ecx, dword ptr [ebp - 0x20]
00682c3c jb 0x682930
00682c42 jmp 0x682d7d
00682c47 movss xmm2, dword ptr [0xc02fec]
00682c4f movss xmm1, dword ptr [0xc02ff0]
00682c57 movss dword ptr [ebp - 0xc], xmm2
00682c5c movss dword ptr [ebp - 0x40], xmm2
00682c61 movss dword ptr [ebp - 8], xmm1
00682c66 movss dword ptr [ebp - 0x3c], xmm1
00682c6b jmp 0x682c77
00682c6d movss xmm1, dword ptr [ebp - 8]
00682c72 movss xmm2, dword ptr [ebp - 0xc]
00682c77 movss xmm3, dword ptr [0xb6a480]
00682c7f movss xmm6, dword ptr [0xb6aa3c]
00682c87 jmp 0x682c32
00682c89 test edx, edx
00682c8b je 0x682d7d
00682c91 xor edi, edi
00682c93 nop dword ptr [eax]
00682c97 nop word ptr [eax + eax]
00682ca0 movss xmm0, dword ptr [eax + edi*8]
00682ca5 movss xmm1, dword ptr [ecx + 4]
00682caa addss xmm1, dword ptr [eax + edi*8 + 4]
00682cb0 movss dword ptr [ebp - 0x38], xmm0
00682cb5 addss xmm0, dword ptr [ecx]
00682cb9 subss xmm1, xmm4
00682cbd subss xmm0, xmm6
00682cc1 divss xmm1, xmm6
00682cc5 divss xmm0, xmm6
00682cc9 addss xmm1, xmm3
00682ccd addss xmm0, xmm3
00682cd1 cvttss2si eax, xmm1
00682cd5 cvttss2si edx, xmm0
00682cd9 test edx, edx
00682cdb js 0x682cf4
00682cdd mov ecx, dword ptr [esi + 0xc]
00682ce0 cmp edx, ecx
00682ce2 jge 0x682cf4
00682ce4 test eax, eax
00682ce6 js 0x682cf4
00682ce8 cmp eax, dword ptr [esi + 0x10]
00682ceb jge 0x682cf4
00682ced imul eax, ecx
00682cf0 add eax, edx
00682cf2 jmp 0x682cf7
00682cf4 or eax, 0xffffffff
00682cf7 push eax
00682cf8 mov ecx, esi
00682cfa call 0x7aeec0
00682cff cmp eax, 4
00682d02 je 0x682d09
00682d04 cmp eax, 5
00682d07 jne 0x682d48
00682d09 mov eax, dword ptr [0xbfd65c]
00682d0e movss xmm1, dword ptr [ebp - 8]
00682d13 mov eax, dword ptr [eax + 0x18190]
00682d19 cmp dword ptr [eax + 8], 0x10
00682d1d mov eax, dword ptr [ebp - 0x1c]
00682d20 je 0x682d50
00682d22 movss xmm2, dword ptr [ebp - 0x38]
00682d27 addss xmm2, dword ptr [ebp - 0xc]
00682d2c addss xmm1, dword ptr [eax + edi*8 + 4]
00682d32 movss dword ptr [ebp - 0xc], xmm2
00682d37 movss dword ptr [ebp - 0x40], xmm2
00682d3c movss dword ptr [ebp - 8], xmm1
00682d41 movss dword ptr [ebp - 0x3c], xmm1
00682d46 jmp 0x682d55
00682d48 movss xmm1, dword ptr [ebp - 8]
00682d4d mov eax, dword ptr [ebp - 0x1c]
00682d50 movss xmm2, dword ptr [ebp - 0xc]
00682d55 movss xmm6, dword ptr [0xb6aa3c]
00682d5d inc edi
00682d5e movss xmm3, dword ptr [0xb6a480]
00682d66 movss xmm4, dword ptr [0xb6ab20]
00682d6e mov ecx, dword ptr [ebp - 0x14]
00682d71 cmp edi, dword ptr [ebp - 0x20]
00682d74 jb 0x682ca0
00682d7a mov edi, dword ptr [ebp - 0x18]
00682d7d ucomiss xmm2, dword ptr [0xc02fec]
00682d84 lahf 
00682d85 test ah, 0x44
00682d88 jp 0x682dc6
00682d8a ucomiss xmm1, dword ptr [0xc02ff0]
00682d91 lahf 
00682d92 test ah, 0x44
00682d95 jp 0x682dc6
00682d97 cmp byte ptr [ebx + 8], 0
00682d9b jne 0x68363f
00682da1 movss xmm0, dword ptr [ebp - 0x30]
00682da6 movss dword ptr [edi + 0x194], xmm0
00682dae movss xmm0, dword ptr [ebp - 0x34]
00682db3 movss dword ptr [edi + 0x198], xmm0
00682dbb pop edi
00682dbc pop esi
00682dbd mov esp, ebp
00682dbf pop ebp
00682dc0 mov esp, ebx
00682dc2 pop ebx
00682dc3 ret 4
00682dc6 mov eax, dword ptr [edi + 0x28]
00682dc9 cmp eax, 2
00682dcc jne 0x682ff6
00682dd2 movss xmm0, dword ptr [0xb6a1c8]
00682dda mulss xmm1, xmm1
00682dde mulss xmm2, xmm2
00682de2 addss xmm1, xmm2
00682de6 comiss xmm0, xmm1
00682de9 jbe 0x682edf
00682def lea eax, [edi + 0x294]
00682df5 mov ecx, esi
00682df7 push eax
00682df8 call 0x7ce950
00682dfd cdq 
00682dfe idiv dword ptr [esi + 0xc]
00682e01 movss xmm1, dword ptr [0xb6aa3c]
00682e09 movss xmm5, dword ptr [edi + 0x294]
00682e11 movss xmm6, dword ptr [edi + 0x2c8]
00682e19 movss xmm4, dword ptr [edi + 0x298]
00682e21 movaps xmm2, xmm6
00682e24 movd xmm0, edx
00682e28 cvtdq2ps xmm0, xmm0
00682e2b movss xmm3, dword ptr [edi + 0x2cc]
00682e33 mulss xmm0, xmm1
00682e37 movss xmm7, dword ptr [0xb6a9c8]
00682e3f mulss xmm2, xmm3
00682e43 addss xmm0, xmm1
00682e47 subss xmm5, xmm0
00682e4b movd xmm0, eax
00682e4f cvtdq2ps xmm0, xmm0
00682e52 mulss xmm0, xmm1
00682e56 addss xmm0, dword ptr [0xb6ab20]
00682e5e subss xmm4, xmm0
00682e62 movaps xmm0, xmm5
00682e65 andps xmm0, xmmword ptr [0xb6c980]
00682e6c addss xmm0, xmm2
00682e70 comiss xmm7, xmm0
00682e73 ja 0x682e93
00682e75 movaps xmm0, xmm6
00682e78 movaps xmm1, xmm4
00682e7b mulss xmm0, dword ptr [edi + 0x2d0]
00682e83 andps xmm1, xmmword ptr [0xb6c980]
00682e8a addss xmm1, xmm0
00682e8e comiss xmm7, xmm1
00682e91 jbe 0x682edf
00682e93 movss xmm1, dword ptr [edi + 0x2d0]
00682e9b movaps xmm0, xmm1
00682e9e mulss xmm3, xmm5
00682ea2 mulss xmm0, xmm4
00682ea6 andps xmm3, xmmword ptr [0xb6c980]
00682ead andps xmm0, xmmword ptr [0xb6c980]
00682eb4 comiss xmm3, xmm0
00682eb7 jbe 0x682fc7
00682ebd comiss xmm5, dword ptr [0xb6a18c]
00682ec4 mov dword ptr [ebp - 0x3c], 0
00682ecb movss dword ptr [ebp - 0x40], xmm2
00682ed0 jbe 0x682edf
00682ed2 mulss xmm2, dword ptr [0xb6ae44]
00682eda movss dword ptr [ebp - 0x40], xmm2
00682edf lea ecx, [ebp - 0x40]
00682ee2 call 0x9624f0
00682ee7 mov al, byte ptr [ebx + 8]
00682eea test al, al
00682eec jne 0x682f08
00682eee movss xmm0, dword ptr [ebp - 0x40]
00682ef3 movss dword ptr [edi + 0x194], xmm0
00682efb movss xmm0, dword ptr [ebp - 0x3c]
00682f00 movss dword ptr [edi + 0x198], xmm0
00682f08 movss xmm2, dword ptr [edi + 0x2bc]
00682f10 movss xmm3, dword ptr [ebp - 0x40]
00682f15 movaps xmm0, xmm2
00682f18 movss xmm4, dword ptr [0xb6c9b0]
00682f20 movss xmm1, dword ptr [edi + 0x2b8]
00682f28 xorps xmm3, xmm4
00682f2b mulss xmm0, dword ptr [ebp - 0x3c]
00682f30 mulss xmm3, xmm1
00682f34 subss xmm3, xmm0
00682f38 xorps xmm0, xmm0
00682f3b comiss xmm0, xmm3
00682f3e movss dword ptr [ebp - 0x28], xmm3
00682f43 jbe 0x68363f
00682f49 test al, al
00682f4b jne 0x6831ef
00682f51 movss dword ptr [edi + 0x190], xmm2
00682f59 movaps xmm2, xmm3
00682f5c mulss xmm2, dword ptr [0xb6a754]
00682f64 mov byte ptr [edi + 0x188], 1
00682f6b movss dword ptr [edi + 0x18c], xmm1
00682f73 mov eax, dword ptr [edi + 0x28]
00682f76 subss xmm2, dword ptr [0xb6a2cc]
00682f7e movss dword ptr [ebp - 0x34], xmm2
00682f83 cmp eax, 0x63
00682f86 jne 0x6830e3
00682f8c movaps xmm2, xmm3
00682f8f xorps xmm2, xmm4
00682f92 mulss xmm2, dword ptr [0xb6a274]
00682f9a push ecx
00682f9b mov dword ptr [esp], 0x3f800000
00682fa2 push 0
00682fa4 minss xmm2, dword ptr [0xb6a670]
00682fac push 2
00682fae push 0x1c
00682fb0 call 0x68d750
00682fb5 movss xmm2, dword ptr [ebp - 0x34]
00682fba mulss xmm2, dword ptr [0xb6a6c8]
00682fc2 jmp 0x6831ba
00682fc7 comiss xmm4, dword ptr [0xb6a18c]
00682fce mov dword ptr [ebp - 0x40], 0
00682fd5 mulss xmm1, xmm6
00682fd9 movss dword ptr [ebp - 0x3c], xmm1
00682fde jbe 0x682edf
00682fe4 mulss xmm1, dword ptr [0xb6ae44]
00682fec movss dword ptr [ebp - 0x3c], xmm1
00682ff1 jmp 0x682edf
00682ff6 cmp eax, 0xa
00682ff9 jl 0x682edf
00682fff cmp eax, 0x3e8
00683004 jge 0x682edf
0068300a cmp dword ptr [ebp - 0x10], 5
0068300e jne 0x682edf
00683014 movss xmm0, dword ptr [0xb6a1c8]
0068301c mulss xmm1, xmm1
00683020 mulss xmm2, xmm2
00683024 addss xmm1, xmm2
00683028 comiss xmm0, xmm1
0068302b jbe 0x682edf
00683031 push ecx
00683032 mov ecx, dword ptr [0xbfd65c]
00683038 lea esi, [edi + 0x294]
0068303e mov dword ptr [esp], 0x42200000
00683045 lea eax, [ebp - 0x40]
00683048 push esi
00683049 push eax
0068304a mov ecx, dword ptr [ecx + 0x18190]
00683050 call 0x7d96d0
00683055 movss xmm4, dword ptr [edi + 0x2c8]
0068305d xorps xmm7, xmm7
00683060 movss xmm2, dword ptr [0xb6a9c8]
00683068 movaps xmm0, xmm4
0068306b mulss xmm0, dword ptr [edi + 0x2cc]
00683073 movaps xmm5, xmm2
00683076 movss xmm1, dword ptr [ebp - 0x40]
0068307b movss xmm3, dword ptr [ebp - 0x3c]
00683080 subss xmm5, xmm0
00683084 movaps xmm6, xmm3
00683087 subss xmm6, dword ptr [esi + 4]
0068308c movaps xmm0, xmm1
0068308f subss xmm0, dword ptr [esi]
00683093 comiss xmm0, xmm7
00683096 jbe 0x68309e
00683098 subss xmm1, xmm5
0068309c jmp 0x6830a2
0068309e addss xmm1, xmm5
006830a2 comiss xmm6, xmm7
006830a5 mulss xmm4, dword ptr [edi + 0x2d0]
006830ad subss xmm2, xmm4
006830b1 jbe 0x6830cb
006830b3 subss xmm3, xmm2
006830b7 movss dword ptr [esi], xmm1
006830bb movss dword ptr [esi + 4], xmm3
006830c0 pop edi
006830c1 pop esi
006830c2 mov esp, ebp
006830c4 pop ebp
006830c5 mov esp, ebx
006830c7 pop ebx
006830c8 ret 4
006830cb addss xmm3, xmm2
006830cf movss dword ptr [esi], xmm1
006830d3 movss dword ptr [esi + 4], xmm3
006830d8 pop edi
006830d9 pop esi
006830da mov esp, ebp
006830dc pop ebp
006830dd mov esp, ebx
006830df pop ebx
006830e0 ret 4
006830e3 cmp eax, 0xd9
006830e8 je 0x6831b2
006830ee cmp eax, 0xdc
006830f3 je 0x6831b2
006830f9 cmp eax, 0x393
006830fe jne 0x68310b
00683100 cmp dword ptr [edi + 0x2c], 1
00683104 je 0x683116
00683106 jmp 0x6831ba
0068310b cmp eax, 0x37d
00683110 jne 0x6831ba
00683116 movss xmm3, dword ptr [edi + 0x2bc]
0068311e movaps xmm2, xmm1
00683121 call 0x6c3d90
00683126 mulss xmm2, xmm2
0068312a push ecx
0068312b mulss xmm3, xmm3
0068312f movd xmm0, eax
00683133 cvtdq2pd xmm0, xmm0
00683137 shr eax, 0x1f
0068313a addss xmm2, xmm3
0068313e addsd xmm0, qword ptr [eax*8 + 0xb6c940]
00683147 cvtpd2ps xmm1, xmm0
0068314b movaps xmm0, xmm2
0068314e mulss xmm1, dword ptr [0xb6a19c]
00683156 mulss xmm1, dword ptr [0xb6a350]
0068315e addss xmm1, dword ptr [0xb6a5a4]
00683166 movss dword ptr [esp], xmm1
0068316b push 0
0068316d push 2
0068316f push ecx
00683170 call 0x4228c0
00683175 mulss xmm0, dword ptr [0xb6a274]
0068317d add esp, 4
00683180 cmp dword ptr [edi + 0x28], 0x37d
00683187 mov ecx, 0x245
0068318c mov eax, 0x1e7
00683191 cmove eax, ecx
00683194 addss xmm0, dword ptr [0xb6a350]
0068319c push eax
0068319d minss xmm0, dword ptr [0xb6a670]
006831a5 movaps xmm2, xmm0
006831a8 call 0x68d750
006831ad movss xmm2, dword ptr [ebp - 0x34]
006831b2 mulss xmm2, dword ptr [0xb6a670]
006831ba movaps xmm0, xmm2
006831bd mulss xmm0, dword ptr [edi + 0x194]
006831c5 addss xmm0, dword ptr [edi + 0x2b8]
006831cd movss dword ptr [edi + 0x2b8], xmm0
006831d5 mulss xmm2, dword ptr [edi + 0x198]
006831dd addss xmm2, dword ptr [edi + 0x2bc]
006831e5 movss dword ptr [edi + 0x2bc], xmm2
006831ed jmp 0x6831ef
006831ef movss xmm1, dword ptr [edi + 0x2b8]
006831f7 mulss xmm2, xmm2
006831fb mulss xmm1, xmm1
006831ff addss xmm2, xmm1
00683203 movaps xmm0, xmm2
00683206 call 0x4228c0
0068320b movaps xmm1, xmm0
0068320e comiss xmm1, dword ptr [0xb6a18c]
00683215 movss dword ptr [ebp - 0x2c], xmm1
0068321a jbe 0x6835f2
00683220 movss xmm1, dword ptr [ebp - 0x40]
00683225 movss xmm0, dword ptr [ebp - 0x3c]
0068322a mulss xmm0, dword ptr [edi + 0x2d0]
00683232 mulss xmm1, dword ptr [edi + 0x2cc]
0068323a mulss xmm0, xmm0
0068323e mulss xmm1, xmm1
00683242 addss xmm0, xmm1
00683246 call 0x4228c0
0068324b mulss xmm0, dword ptr [edi + 0x2c8]
00683253 mov eax, dword ptr [ebp - 0x10]
00683256 movss xmm1, dword ptr [ebp - 0x2c]
0068325b mov edi, dword ptr [ebp - 0x14]
0068325e movss dword ptr [ebp - 0x38], xmm0
00683263 movaps xmm2, xmm0
00683266 movss dword ptr [ebp - 0xc], xmm0
0068326b maxss xmm1, dword ptr [0xb6a7b0]
00683273 subss xmm2, xmm1
00683277 movss dword ptr [ebp - 8], xmm2
0068327c cmp eax, 5
0068327f jne 0x683347
00683285 mov dword ptr [ebp - 0x30], 0xc
0068328c nop dword ptr [eax]
00683290 movss xmm3, dword ptr [0xb6a480]
00683298 movaps xmm1, xmm0
0068329b subss xmm1, xmm2
0068329f mulss xmm1, xmm3
006832a3 addss xmm1, xmm2
006832a7 movss xmm2, dword ptr [0xb6aa3c]
006832af movaps xmm0, xmm1
006832b2 movss dword ptr [ebp - 0x34], xmm1
006832b7 mulss xmm0, dword ptr [ebp - 0x40]
006832bc mulss xmm1, dword ptr [ebp - 0x3c]
006832c1 addss xmm0, dword ptr [edi]
006832c5 addss xmm1, dword ptr [edi + 4]
006832ca subss xmm0, xmm2
006832ce subss xmm1, dword ptr [0xb6ab20]
006832d6 divss xmm0, xmm2
006832da divss xmm1, xmm2
006832de addss xmm0, xmm3
006832e2 addss xmm1, xmm3
006832e6 cvttss2si ecx, xmm0
006832ea cvttss2si eax, xmm1
006832ee test ecx, ecx
006832f0 js 0x683309
006832f2 mov edx, dword ptr [esi + 0xc]
006832f5 cmp ecx, edx
006832f7 jge 0x683309
006832f9 test eax, eax
006832fb js 0x683309
006832fd cmp eax, dword ptr [esi + 0x10]
00683300 jge 0x683309
00683302 imul eax, edx
00683305 add eax, ecx
00683307 jmp 0x68330c
00683309 or eax, 0xffffffff
0068330c push eax
0068330d mov ecx, esi
0068330f call 0x7aeec0
00683314 test eax, eax
00683316 je 0x683329
00683318 movss xmm0, dword ptr [ebp - 0x34]
0068331d movss xmm2, dword ptr [ebp - 8]
00683322 movss dword ptr [ebp - 0xc], xmm0
00683327 jmp 0x683338
00683329 movss xmm2, dword ptr [ebp - 0x34]
0068332e movss xmm0, dword ptr [ebp - 0xc]
00683333 movss dword ptr [ebp - 8], xmm2
00683338 sub dword ptr [ebp - 0x30], 1
0068333c jne 0x683290
00683342 jmp 0x6835b8
00683347 cmp eax, 7
0068334a jne 0x683418
00683350 mov dword ptr [ebp - 0x30], 6
00683357 nop word ptr [eax + eax]
00683360 movss xmm3, dword ptr [0xb6a480]
00683368 movaps xmm1, xmm0
0068336b subss xmm1, xmm2
0068336f mulss xmm1, xmm3
00683373 addss xmm1, xmm2
00683377 movss xmm2, dword ptr [0xb6aa3c]
0068337f movaps xmm0, xmm1
00683382 movss dword ptr [ebp - 0x34], xmm1
00683387 mulss xmm0, dword ptr [ebp - 0x40]
0068338c mulss xmm1, dword ptr [ebp - 0x3c]
00683391 addss xmm0, dword ptr [edi]
00683395 addss xmm1, dword ptr [edi + 4]
0068339a subss xmm0, xmm2
0068339e subss xmm1, dword ptr [0xb6ab20]
006833a6 divss xmm0, xmm2
006833aa divss xmm1, xmm2
006833ae addss xmm0, xmm3
006833b2 addss xmm1, xmm3
006833b6 cvttss2si ecx, xmm0
006833ba cvttss2si eax, xmm1
006833be test ecx, ecx
006833c0 js 0x6833d9
006833c2 mov edx, dword ptr [esi + 0xc]
006833c5 cmp ecx, edx
006833c7 jge 0x6833d9
006833c9 test eax, eax
006833cb js 0x6833d9
006833cd cmp eax, dword ptr [esi + 0x10]
006833d0 jge 0x6833d9
006833d2 imul eax, edx
006833d5 add eax, ecx
006833d7 jmp 0x6833dc
006833d9 or eax, 0xffffffff
006833dc push eax
006833dd mov ecx, esi
006833df call 0x7aeec0
006833e4 cmp eax, 1
006833e7 je 0x6833fa
006833e9 movss xmm0, dword ptr [ebp - 0x34]
006833ee movss xmm2, dword ptr [ebp - 8]
006833f3 movss dword ptr [ebp - 0xc], xmm0
006833f8 jmp 0x683409
006833fa movss xmm2, dword ptr [ebp - 0x34]
006833ff movss xmm0, dword ptr [ebp - 0xc]
00683404 movss dword ptr [ebp - 8], xmm2
00683409 sub dword ptr [ebp - 0x30], 1
0068340d jne 0x683360
00683413 jmp 0x6835b8
00683418 cmp eax, 6
0068341b jne 0x6834ec
00683421 mov dword ptr [ebp - 0x30], eax
00683424 nop dword ptr [eax]
00683428 nop dword ptr [eax + eax]
00683430 movss xmm3, dword ptr [0xb6a480]
00683438 movaps xmm1, xmm0
0068343b subss xmm1, xmm2
0068343f mulss xmm1, xmm3
00683443 addss xmm1, xmm2
00683447 movss xmm2, dword ptr [0xb6aa3c]
0068344f movaps xmm0, xmm1
00683452 movss dword ptr [ebp - 0x34], xmm1
00683457 mulss xmm0, dword ptr [ebp - 0x40]
0068345c mulss xmm1, dword ptr [ebp - 0x3c]
00683461 addss xmm0, dword ptr [edi]
00683465 addss xmm1, dword ptr [edi + 4]
0068346a subss xmm0, xmm2
0068346e subss xmm1, dword ptr [0xb6ab20]
00683476 divss xmm0, xmm2
0068347a divss xmm1, xmm2
0068347e addss xmm0, xmm3
00683482 addss xmm1, xmm3
00683486 cvttss2si ecx, xmm0
0068348a cvttss2si eax, xmm1
0068348e test ecx, ecx
00683490 js 0x6834a9
00683492 mov edx, dword ptr [esi + 0xc]
00683495 cmp ecx, edx
00683497 jge 0x6834a9
00683499 test eax, eax
0068349b js 0x6834a9
0068349d cmp eax, dword ptr [esi + 0x10]
006834a0 jge 0x6834a9
006834a2 imul eax, edx
006834a5 add eax, ecx
006834a7 jmp 0x6834ac
006834a9 or eax, 0xffffffff
006834ac push eax
006834ad mov ecx, esi
006834af call 0x7aeec0
006834b4 test eax, eax
006834b6 je 0x6834ce
006834b8 cmp eax, 1
006834bb je 0x6834ce
006834bd movss xmm0, dword ptr [ebp - 0x34]
006834c2 movss xmm2, dword ptr [ebp - 8]
006834c7 movss dword ptr [ebp - 0xc], xmm0
006834cc jmp 0x6834dd
006834ce movss xmm2, dword ptr [ebp - 0x34]
006834d3 movss xmm0, dword ptr [ebp - 0xc]
006834d8 movss dword ptr [ebp - 8], xmm2
006834dd sub dword ptr [ebp - 0x30], 1
006834e1 jne 0x683430
006834e7 jmp 0x6835b8
006834ec mov dword ptr [ebp - 0x30], 6
006834f3 nop dword ptr [eax]
006834f7 nop word ptr [eax + eax]
00683500 movss xmm3, dword ptr [0xb6a480]
00683508 movaps xmm1, xmm0
0068350b subss xmm1, xmm2
0068350f mulss xmm1, xmm3
00683513 addss xmm1, xmm2
00683517 movss xmm2, dword ptr [0xb6aa3c]
0068351f movaps xmm0, xmm1
00683522 movss dword ptr [ebp - 0x34], xmm1
00683527 mulss xmm0, dword ptr [ebp - 0x40]
0068352c mulss xmm1, dword ptr [ebp - 0x3c]
00683531 addss xmm0, dword ptr [edi]
00683535 addss xmm1, dword ptr [edi + 4]
0068353a subss xmm0, xmm2
0068353e subss xmm1, dword ptr [0xb6ab20]
00683546 divss xmm0, xmm2
0068354a divss xmm1, xmm2
0068354e addss xmm0, xmm3
00683552 addss xmm1, xmm3
00683556 cvttss2si ecx, xmm0
0068355a cvttss2si eax, xmm1
0068355e test ecx, ecx
00683560 js 0x683579
00683562 mov edx, dword ptr [esi + 0xc]
00683565 cmp ecx, edx
00683567 jge 0x683579
00683569 test eax, eax
0068356b js 0x683579
0068356d cmp eax, dword ptr [esi + 0x10]
00683570 jge 0x683579
00683572 imul eax, edx
00683575 add eax, ecx
00683577 jmp 0x68357c
00683579 or eax, 0xffffffff
0068357c push eax
0068357d mov ecx, esi
0068357f call 0x7aeec0
00683584 cmp eax, 4
00683587 je 0x68359f
00683589 cmp eax, 5
0068358c je 0x68359f
0068358e movss xmm2, dword ptr [ebp - 0x34]
00683593 movss xmm0, dword ptr [ebp - 0xc]
00683598 movss dword ptr [ebp - 8], xmm2
0068359d jmp 0x6835ae
0068359f movss xmm0, dword ptr [ebp - 0x34]
006835a4 movss xmm2, dword ptr [ebp - 8]
006835a9 movss dword ptr [ebp - 0xc], xmm0
006835ae sub dword ptr [ebp - 0x30], 1
006835b2 jne 0x683500
006835b8 subss xmm2, dword ptr [ebp - 0x38]
006835bd mov edi, dword ptr [ebp - 0x18]
006835c0 movss xmm1, dword ptr [ebp - 0x2c]
006835c5 movaps xmm0, xmm2
006835c8 mulss xmm2, dword ptr [ebp - 0x3c]
006835cd mulss xmm0, dword ptr [ebp - 0x40]
006835d2 addss xmm2, dword ptr [edi + 0x298]
006835da addss xmm0, dword ptr [edi + 0x294]
006835e2 movss dword ptr [edi + 0x298], xmm2
006835ea movss dword ptr [edi + 0x294], xmm0
006835f2 cmp byte ptr [ebx + 8], 0
006835f6 jne 0x68363f
006835f8 movss xmm0, dword ptr [ebp - 0x28]
006835fd xorps xmm0, xmmword ptr [0xb6c9b0]
00683604 divss xmm0, xmm1
00683608 movss xmm1, dword ptr [0xb6a614]
00683610 mulss xmm0, dword ptr [0xb6a480]
00683618 subss xmm1, xmm0
0068361c movaps xmm0, xmm1
0068361f mulss xmm1, dword ptr [edi + 0x2bc]
00683627 mulss xmm0, dword ptr [edi + 0x2b8]
0068362f movss dword ptr [edi + 0x2bc], xmm1
00683637 movss dword ptr [edi + 0x2b8], xmm0
0068363f pop edi
00683640 pop esi
00683641 mov esp, ebp
00683643 pop ebp
00683644 mov esp, ebx
00683646 pop ebx
00683647 ret 4
