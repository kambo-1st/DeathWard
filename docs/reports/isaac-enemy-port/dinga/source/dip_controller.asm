00521e10 push ebp
00521e11 mov ebp, esp
00521e13 sub esp, 0x124
00521e19 mov eax, dword ptr [0xbaa3b4]
00521e1e xor eax, ebp
00521e20 mov dword ptr [ebp - 4], eax
00521e23 push ebx
00521e24 push esi
00521e25 push edi
00521e26 mov edi, ecx
00521e28 cmp byte ptr [edi + 0x16b], 0
00521e2f jne 0x521f30
00521e35 mov ecx, dword ptr [0xbfd65c]
00521e3b push 1
00521e3d add ecx, 0x1ba40
00521e43 push ecx
00521e44 push 0x240
00521e49 call 0x91d340
00521e4e test eax, eax
00521e50 jne 0x521e73
00521e52 mov ecx, dword ptr [0xbfd65c]
00521e58 push 1
00521e5a push eax
00521e5b push 0xa3
00521e60 lea ecx, [ecx + 0x1ba40]
00521e66 call 0x91d550
00521e6b test eax, eax
00521e6d je 0x521f30
00521e73 mov ecx, dword ptr [0xbfd65c]
00521e79 push 0
00521e7b push dword ptr [edi + 0x344]
00521e81 push 0x240
00521e86 lea ecx, [ecx + 0x1ba40]
00521e8c call 0x91d400
00521e91 mov esi, eax
00521e93 test esi, esi
00521e95 jne 0x521eba
00521e97 mov ecx, dword ptr [0xbfd65c]
00521e9d push eax
00521e9e push dword ptr [edi + 0x344]
00521ea4 push 0xa3
00521ea9 lea ecx, [ecx + 0x1ba40]
00521eaf call 0x91d680
00521eb4 mov esi, eax
00521eb6 test esi, esi
00521eb8 je 0x521f30
00521eba mov eax, dword ptr [edi]
00521ebc mov ecx, edi
00521ebe mov dword ptr [edi + 0x180], 0
00521ec8 call dword ptr [eax + 0x28]
00521ecb xor ecx, ecx
00521ecd cmp dword ptr [edi + 0x28], 0xd9
00521ed4 jne 0x521f10
00521ed6 mov eax, dword ptr [edi + 0x2c]
00521ed9 cmp eax, 1
00521edc je 0x521f0b
00521ede cmp eax, 3
00521ee1 je 0x521f0b
00521ee3 cmp eax, 2
00521ee6 jne 0x521f10
00521ee8 lea ecx, [eax + 0x12]
00521eeb push esi
00521eec lea edx, [edi + 0x294]
00521ef2 call 0x6182c0
00521ef7 add esp, 4
00521efa pop edi
00521efb pop esi
00521efc pop ebx
00521efd mov ecx, dword ptr [ebp - 4]
00521f00 xor ecx, ebp
00521f02 call 0x9eacd7
00521f07 mov esp, ebp
00521f09 pop ebp
00521f0a ret 
00521f0b mov ecx, 2
00521f10 push esi
00521f11 lea edx, [edi + 0x294]
00521f17 call 0x6182c0
00521f1c add esp, 4
00521f1f pop edi
00521f20 pop esi
00521f21 pop ebx
00521f22 mov ecx, dword ptr [ebp - 4]
00521f25 xor ecx, ebp
00521f27 call 0x9eacd7
00521f2c mov esp, ebp
00521f2e pop ebp
00521f2f ret 
00521f30 mov ecx, dword ptr [edi + 0xab4]
00521f36 test ecx, ecx
00521f38 jne 0x52200b
00521f3e movaps xmm1, xmmword ptr [0xb6bd30]
00521f45 lea ecx, [edi + 0x1dc]
00521f4b lea eax, [ebp - 0xf4]
00521f51 mov dword ptr [edi + 0xab4], 3
00521f5b mov dword ptr [ebp - 0xd4], 0x3e828283
00521f65 xorps xmm0, xmm0
00521f68 mov dword ptr [ebp - 0xd0], 0x3e24a4a5
00521f72 mov dword ptr [ebp - 0xcc], 0x3e0c8c8d
00521f7c cmp ecx, eax
00521f7e je 0x521f9d
00521f80 mov eax, dword ptr [ebp - 0xcc]
00521f86 movups xmmword ptr [ecx + 0x10], xmm0
00521f8a movq xmm0, qword ptr [ebp - 0xd4]
00521f92 movq qword ptr [ecx + 0x20], xmm0
00521f97 movups xmmword ptr [ecx], xmm1
00521f9a mov dword ptr [ecx + 0x28], eax
00521f9d cmp dword ptr [edi + 0x2c], 2
00521fa1 jne 0x52282b
00521fa7 movaps xmm1, xmmword ptr [0xb6bd30]
00521fae lea eax, [ebp - 0x120]
00521fb4 mov dword ptr [ebp - 0x100], 0x3f19999a
00521fbe xorps xmm0, xmm0
00521fc1 mov dword ptr [ebp - 0xfc], 0x3ecccccd
00521fcb mov dword ptr [ebp - 0xf8], 0
00521fd5 cmp ecx, eax
00521fd7 je 0x52282b
00521fdd mov eax, dword ptr [ebp - 0xf8]
00521fe3 movups xmmword ptr [ecx + 0x10], xmm0
00521fe7 movq xmm0, qword ptr [ebp - 0x100]
00521fef movq qword ptr [ecx + 0x20], xmm0
00521ff4 movups xmmword ptr [ecx], xmm1
00521ff7 mov dword ptr [ecx + 0x28], eax
00521ffa pop edi
00521ffb pop esi
00521ffc pop ebx
00521ffd mov ecx, dword ptr [ebp - 4]
00522000 xor ecx, ebp
00522002 call 0x9eacd7
00522007 mov esp, ebp
00522009 pop ebp
0052200a ret 
0052200b mov eax, dword ptr [edi + 0x28]
0052200e cmp eax, 0x366
00522013 je 0x522022
00522015 cmp eax, 0xd9
0052201a jne 0x522043
0052201c cmp dword ptr [edi + 0x2c], 3
00522020 jne 0x522043
00522022 mov eax, dword ptr [0xbfd65c]
00522027 mov eax, dword ptr [eax + 0x18190]
0052202d movss xmm0, dword ptr [eax + 0x7134]
00522035 mov eax, 6
0052203a comiss xmm0, dword ptr [0xb6a18c]
00522041 ja 0x522048
00522043 mov eax, 5
00522048 mov dword ptr [edi + 0x17c], eax
0052204e mov ebx, 0xa
00522053 cmp ecx, 3
00522056 je 0x522132
0052205c cmp ecx, 0x10
0052205f je 0x522132
00522065 cmp ecx, 4
00522068 jne 0x52260f
0052206e push 0
00522070 push 0xb404a0
00522075 lea ecx, [edi + 0x3c]
00522078 call 0x4054f0
0052207d cmp dword ptr [edi + 0x28], 0x366
00522084 movss xmm0, dword ptr [edi + 0x2c4]
0052208c mulss xmm0, dword ptr [0xb6a5d8]
00522094 movss dword ptr [edi + 0x2c4], xmm0
0052209c jne 0x5220f6
0052209e lea ecx, [edi + 0x3c]
005220a1 call 0x4058f0
005220a6 cmp eax, ebx
005220a8 jne 0x5220d4
005220aa call 0x6c3d90
005220af xor edx, edx
005220b1 mov ecx, 3
005220b6 div ecx
005220b8 test edx, edx
005220ba je 0x5220c5
005220bc cmp dword ptr [edi + 0xe6c], -1
005220c3 je 0x5220d4
005220c5 mov dword ptr [edi + 0xab4], 0x10
005220cf jmp 0x52260f
005220d4 cmp dword ptr [edi + 0x70], 0
005220d8 je 0x5220e7
005220da cmp byte ptr [edi + 0x80], 0
005220e1 jne 0x52260f
005220e7 mov dword ptr [edi + 0xab4], 3
005220f1 jmp 0x52260f
005220f6 movss xmm1, dword ptr [edi + 0x2bc]
005220fe movss xmm0, dword ptr [edi + 0x2b8]
00522106 mulss xmm1, xmm1
0052210a mulss xmm0, xmm0
0052210e addss xmm0, xmm1
00522112 movss xmm1, dword ptr [0xb6a614]
0052211a comiss xmm1, xmm0
0052211d jbe 0x52260f
00522123 mov dword ptr [edi + 0xab4], 3
0052212d jmp 0x52260f
00522132 push 0
00522134 push 0xb3fd8c
00522139 lea ecx, [edi + 0x3c]
0052213c call 0x4054f0
00522141 cmp dword ptr [edi + 0xab4], 0x10
00522148 je 0x5221af
0052214a cmp dword ptr [edi + 0xe6c], -1
00522151 je 0x522199
00522153 movss xmm2, dword ptr [0xb6a2cc]
0052215b lea eax, [ebp - 0xc8]
00522161 push eax
00522162 mov ecx, edi
00522164 call 0x6af0c0
00522169 mov ecx, eax
0052216b movss xmm0, dword ptr [ecx]
0052216f ucomiss xmm0, dword ptr [0xc02fec]
00522176 lahf 
00522177 test ah, 0x44
0052217a jp 0x522192
0052217c movss xmm0, dword ptr [ecx + 4]
00522181 ucomiss xmm0, dword ptr [0xc02ff0]
00522188 lahf 
00522189 test ah, 0x44
0052218c jp 0x522192
0052218e xor edx, edx
00522190 jmp 0x5221a7
00522192 mov edx, 1
00522197 jmp 0x5221a7
00522199 call 0x6c3d90
0052219e xor edx, edx
005221a0 div ebx
005221a2 neg edx
005221a4 sbb edx, edx
005221a6 inc edx
005221a7 test edx, edx
005221a9 je 0x5225e4
005221af mov eax, dword ptr [edi + 0x160]
005221b5 and eax, 0x1000800
005221ba mov dword ptr [edi + 0xab4], 4
005221c4 or eax, 0
005221c7 je 0x5223c4
005221cd cmp dword ptr [edi + 0xe6c], -1
005221d4 jne 0x5223c4
005221da cmp dword ptr [edi + 0x28], 0x366
005221e1 jne 0x5222c6
005221e7 call 0x6c3d90
005221ec mov ecx, edi
005221ee movd xmm0, eax
005221f2 cvtdq2pd xmm0, xmm0
005221f6 shr eax, 0x1f
005221f9 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
00522202 cvtpd2ps xmm0, xmm0
00522206 mulss xmm0, dword ptr [0xb6a19c]
0052220e mulss xmm0, dword ptr [0xb6a864]
00522216 addss xmm0, dword ptr [0xb6a8f4]
0052221e movss dword ptr [ebp - 0xb4], xmm0
00522226 call 0x695680
0052222b movss xmm0, dword ptr [edi + 0x294]
00522233 lea ecx, [ebp - 0xc0]
00522239 subss xmm0, dword ptr [eax + 0x294]
00522241 movss dword ptr [ebp - 0xc0], xmm0
00522249 movss xmm0, dword ptr [edi + 0x298]
00522251 subss xmm0, dword ptr [eax + 0x298]
00522259 lea eax, [ebp - 0xc8]
0052225f push eax
00522260 movss dword ptr [ebp - 0xbc], xmm0
00522268 call 0x962560
0052226d movss xmm3, dword ptr [edi + 0x2c4]
00522275 ucomiss xmm3, dword ptr [0xb6a18c]
0052227c movss xmm2, dword ptr [ebp - 0xb4]
00522284 movaps xmm4, xmm2
00522287 mulss xmm2, dword ptr [eax + 4]
0052228c mulss xmm4, dword ptr [eax]
00522290 lahf 
00522291 test ah, 0x44
00522294 jnp 0x5225e4
0052229a movss xmm1, dword ptr [edi + 0x2f4]
005222a2 movaps xmm0, xmm1
005222a5 mulss xmm1, xmm2
005222a9 mulss xmm0, xmm4
005222ad divss xmm0, xmm3
005222b1 addss xmm0, dword ptr [edi + 0x2b8]
005222b9 movss dword ptr [edi + 0x2b8], xmm0
005222c1 jmp 0x5225d0
005222c6 call 0x6c3d90
005222cb mov ecx, edi
005222cd movd xmm0, eax
005222d1 cvtdq2pd xmm0, xmm0
005222d5 shr eax, 0x1f
005222d8 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
005222e1 cvtpd2ps xmm1, xmm0
005222e5 mulss xmm1, dword ptr [0xb6a19c]
005222ed mulss xmm1, dword ptr [0xb6a8f4]
005222f5 addss xmm1, dword ptr [0xb6a8f4]
005222fd movss dword ptr [ebp - 0xb4], xmm1
00522305 call 0x695680
0052230a movss xmm0, dword ptr [edi + 0x294]
00522312 lea ecx, [ebp - 0xc0]
00522318 subss xmm0, dword ptr [eax + 0x294]
00522320 movss dword ptr [ebp - 0xc0], xmm0
00522328 movss xmm0, dword ptr [edi + 0x298]
00522330 subss xmm0, dword ptr [eax + 0x298]
00522338 lea eax, [ebp - 0xc8]
0052233e push eax
0052233f movss dword ptr [ebp - 0xbc], xmm0
00522347 call 0x962560
0052234c movss xmm2, dword ptr [ebp - 0xb4]
00522354 movaps xmm3, xmm2
00522357 mulss xmm3, dword ptr [eax]
0052235b mulss xmm2, dword ptr [eax + 4]
00522360 mov eax, dword ptr [edi + 0x2c]
00522363 cmp eax, 1
00522366 je 0x52236d
00522368 cmp eax, 2
0052236b jne 0x52237b
0052236d movaps xmm0, xmm3
00522370 addss xmm3, xmm0
00522374 movaps xmm0, xmm2
00522377 addss xmm2, xmm0
0052237b movss xmm4, dword ptr [edi + 0x2c4]
00522383 ucomiss xmm4, dword ptr [0xb6a18c]
0052238a lahf 
0052238b test ah, 0x44
0052238e jnp 0x5225e4
00522394 movss xmm1, dword ptr [edi + 0x2f4]
0052239c movaps xmm0, xmm1
0052239f mulss xmm1, xmm2
005223a3 mulss xmm0, xmm3
005223a7 divss xmm1, xmm4
005223ab divss xmm0, xmm4
005223af addss xmm0, dword ptr [edi + 0x2b8]
005223b7 movss dword ptr [edi + 0x2b8], xmm0
005223bf jmp 0x5225d4
005223c4 cmp dword ptr [edi + 0x28], 0x366
005223cb jne 0x5224ff
005223d1 call 0x6c3d90
005223d6 xor edx, edx
005223d8 mov ecx, 3
005223dd div ecx
005223df test edx, edx
005223e1 jne 0x52242e
005223e3 mov ecx, edi
005223e5 call 0x695680
005223ea lea ecx, [ebp - 0xb8]
005223f0 movss xmm0, dword ptr [eax + 0x294]
005223f8 movss xmm1, dword ptr [eax + 0x298]
00522400 lea eax, [ebp - 0xc8]
00522406 subss xmm0, dword ptr [edi + 0x294]
0052240e subss xmm1, dword ptr [edi + 0x298]
00522416 push eax
00522417 movss dword ptr [ebp - 0xb8], xmm0
0052241f movss dword ptr [ebp - 0xb4], xmm1
00522427 call 0x962560
0052242c jmp 0x52243d
0052242e lea eax, [ebp - 0xc0]
00522434 push eax
00522435 call 0x659290
0052243a add esp, 4
0052243d cmp dword ptr [edi + 0xe6c], -1
00522444 movss xmm1, dword ptr [eax]
00522448 movss xmm4, dword ptr [eax + 4]
0052244d je 0x522469
0052244f lea eax, [ebp - 0xc8]
00522455 xorps xmm2, xmm2
00522458 push eax
00522459 mov ecx, edi
0052245b call 0x6af0c0
00522460 movss xmm1, dword ptr [eax]
00522464 movss xmm4, dword ptr [eax + 4]
00522469 call 0x6c3d90
0052246e movd xmm0, eax
00522472 shr eax, 0x1f
00522475 cvtdq2pd xmm0, xmm0
00522479 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
00522482 mov eax, dword ptr [0xbfd65c]
00522487 mov eax, dword ptr [eax + 0x18190]
0052248d cvtpd2ps xmm2, xmm0
00522491 mulss xmm2, dword ptr [0xb6a19c]
00522499 mulss xmm2, dword ptr [0xb6a864]
005224a1 addss xmm2, dword ptr [0xb6a8f4]
005224a9 movaps xmm3, xmm2
005224ac mulss xmm2, xmm4
005224b0 movss xmm4, dword ptr [eax + 0x7344]
005224b8 ucomiss xmm4, dword ptr [0xc02fec]
005224bf mulss xmm3, xmm1
005224c3 movss xmm1, dword ptr [eax + 0x7348]
005224cb lahf 
005224cc test ah, 0x44
005224cf jp 0x5224e2
005224d1 ucomiss xmm1, dword ptr [0xc02ff0]
005224d8 lahf 
005224d9 test ah, 0x44
005224dc jnp 0x52237b
005224e2 mulss xmm4, dword ptr [0xb6a940]
005224ea mulss xmm1, dword ptr [0xb6a940]
005224f2 subss xmm3, xmm4
005224f6 subss xmm2, xmm1
005224fa jmp 0x52237b
005224ff lea eax, [ebp - 0xb8]
00522505 push eax
00522506 call 0x659290
0052250b add esp, 4
0052250e cmp dword ptr [edi + 0xe6c], -1
00522515 je 0x522533
00522517 lea eax, [ebp - 0xc8]
0052251d xorps xmm2, xmm2
00522520 push eax
00522521 mov ecx, edi
00522523 call 0x6af0c0
00522528 movss xmm3, dword ptr [eax]
0052252c movss xmm4, dword ptr [eax + 4]
00522531 jmp 0x522543
00522533 movss xmm4, dword ptr [ebp - 0xb4]
0052253b movss xmm3, dword ptr [ebp - 0xb8]
00522543 call 0x6c3d90
00522548 movd xmm0, eax
0052254c cvtdq2pd xmm0, xmm0
00522550 shr eax, 0x1f
00522553 cmp dword ptr [edi + 0x2c], 1
00522557 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
00522560 cvtpd2ps xmm1, xmm0
00522564 mulss xmm1, dword ptr [0xb6a19c]
0052256c mulss xmm1, dword ptr [0xb6a8f4]
00522574 addss xmm1, dword ptr [0xb6a8f4]
0052257c movaps xmm2, xmm1
0052257f mulss xmm1, xmm4
00522583 mulss xmm2, xmm3
00522587 jne 0x522597
00522589 movaps xmm0, xmm2
0052258c addss xmm2, xmm0
00522590 movaps xmm0, xmm1
00522593 addss xmm1, xmm0
00522597 movss xmm3, dword ptr [edi + 0x2c4]
0052259f ucomiss xmm3, dword ptr [0xb6a18c]
005225a6 lahf 
005225a7 test ah, 0x44
005225aa jnp 0x5225e4
005225ac movss xmm0, dword ptr [edi + 0x2f4]
005225b4 mulss xmm2, xmm0
005225b8 mulss xmm1, xmm0
005225bc divss xmm2, xmm3
005225c0 addss xmm2, dword ptr [edi + 0x2b8]
005225c8 movss dword ptr [edi + 0x2b8], xmm2
005225d0 divss xmm1, xmm3
005225d4 addss xmm1, dword ptr [edi + 0x2bc]
005225dc movss dword ptr [edi + 0x2bc], xmm1
005225e4 cmp dword ptr [edi + 0x28], 0x366
005225eb movss xmm0, dword ptr [edi + 0x2c4]
005225f3 jne 0x5225ff
005225f5 mulss xmm0, dword ptr [0xb6a5a4]
005225fd jmp 0x522607
005225ff mulss xmm0, dword ptr [0xb6a560]
00522607 movss dword ptr [edi + 0x2c4], xmm0
0052260f xorps xmm0, xmm0
00522612 comiss xmm0, dword ptr [edi + 0x2b8]
00522619 seta al
0052261c mov byte ptr [edi + 0x13c], al
00522622 call 0x6c3d90
00522627 xor edx, edx
00522629 div ebx
0052262b test edx, edx
0052262d jne 0x52268a
0052262f call 0x6c3d90
00522634 push ecx
00522635 mov ecx, edi
00522637 movd xmm0, eax
0052263b cvtdq2pd xmm0, xmm0
0052263f shr eax, 0x1f
00522642 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
0052264b cvtpd2ps xmm0, xmm0
0052264f mulss xmm0, dword ptr [0xb6a19c]
00522657 mulss xmm0, dword ptr [0xb6a480]
0052265f addss xmm0, dword ptr [0xb6a350]
00522667 movss dword ptr [esp], xmm0
0052266c call 0x68d7b0
00522671 push 1
00522673 push 0
00522675 push 0xff
0052267a mov edx, dword ptr [eax]
0052267c lea ecx, [edi + 0x1dc]
00522682 push -1
00522684 push ecx
00522685 mov ecx, eax
00522687 call dword ptr [edx + 0x38]
0052268a movss xmm0, dword ptr [edi + 0x14]
0052268f comiss xmm0, dword ptr [0xb6a18c]
00522696 jbe 0x5226be
00522698 call 0x6c3d90
0052269d test al, 1
0052269f jne 0x5226be
005226a1 push ecx
005226a2 mov dword ptr [esp], 0x3f800000
005226a9 push 0
005226ab push 0xf
005226ad push ecx
005226ae mov dword ptr [esp], 0x3f4ccccd
005226b5 mov ecx, edi
005226b7 push 0x3c
005226b9 call 0x6ad720
005226be cmp dword ptr [edi + 0x28], 0xd9
005226c5 jne 0x5226ec
005226c7 cmp dword ptr [edi + 0x2c], 3
005226cb jne 0x5226ec
005226cd mov eax, dword ptr [edi + 0xe6c]
005226d3 cmp eax, -1
005226d6 je 0x5226ec
005226d8 push edi
005226d9 push eax
005226da push 9
005226dc call 0x8b10b0
005226e1 test al, al
005226e3 je 0x5226ec
005226e5 mov eax, dword ptr [edi]
005226e7 mov ecx, edi
005226e9 call dword ptr [eax + 0x24]
005226ec cmp byte ptr [edi + 0x16b], 0
005226f3 je 0x52282b
005226f9 cmp dword ptr [edi + 0x28], 0xd9
00522700 jne 0x52282b
00522706 cmp dword ptr [edi + 0x2c], 3
0052270a jne 0x52282b
00522710 mov ecx, edi
00522712 call 0x695680
00522717 mov esi, eax
00522719 lea ebx, [edi + 0x294]
0052271f movss xmm1, dword ptr [esi + 0x294]
00522727 movss xmm0, dword ptr [esi + 0x298]
0052272f subss xmm0, dword ptr [ebx + 4]
00522734 subss xmm1, dword ptr [ebx]
00522738 mulss xmm0, xmm0
0052273c mulss xmm1, xmm1
00522740 addss xmm0, xmm1
00522744 call 0x4228c0
00522749 movss xmm1, dword ptr [esi + 0x2b8]
00522751 mulss xmm1, dword ptr [0xb6a2cc]
00522759 movss xmm2, dword ptr [esi + 0x2bc]
00522761 mulss xmm2, dword ptr [0xb6a2cc]
00522769 mulss xmm1, xmm0
0052276d mulss xmm2, xmm0
00522771 addss xmm1, dword ptr [esi + 0x294]
00522779 addss xmm2, dword ptr [esi + 0x298]
00522781 subss xmm1, dword ptr [ebx]
00522785 subss xmm2, dword ptr [ebx + 4]
0052278a movaps xmm0, xmm1
0052278d movss dword ptr [ebp - 0xbc], xmm1
00522795 mulss xmm0, xmm1
00522799 movaps xmm1, xmm2
0052279c movss dword ptr [ebp - 0xb4], xmm2
005227a4 mulss xmm1, xmm2
005227a8 addss xmm0, xmm1
005227ac call 0x4228c0
005227b1 comiss xmm0, dword ptr [0xb6a18c]
005227b8 movss xmm1, dword ptr [ebp - 0xbc]
005227c0 movss xmm2, dword ptr [ebp - 0xb4]
005227c8 jbe 0x5227e1
005227ca movss xmm3, dword ptr [0xb6a614]
005227d2 divss xmm3, xmm0
005227d6 movaps xmm0, xmm3
005227d9 mulss xmm2, xmm3
005227dd mulss xmm1, xmm0
005227e1 mulss xmm1, dword ptr [0xb6a974]
005227e9 lea ecx, [ebp - 0xb0]
005227ef mulss xmm2, dword ptr [0xb6a974]
005227f7 movss dword ptr [ebp - 0xc8], xmm1
005227ff movss dword ptr [ebp - 0xc4], xmm2
00522807 call 0x430d70
0052280c lea eax, [ebp - 0xb0]
00522812 mov dword ptr [ebp - 0x1c], 5
00522819 push eax
0052281a push 0
0052281c lea eax, [ebp - 0xc8]
00522822 mov ecx, edi
00522824 push eax
00522825 push ebx
00522826 call 0x6a1a20
0052282b mov ecx, dword ptr [ebp - 4]
0052282e pop edi
0052282f pop esi
00522830 xor ecx, ebp
00522832 pop ebx
00522833 call 0x9eacd7
00522838 mov esp, ebp
0052283a pop ebp
0052283b ret 
