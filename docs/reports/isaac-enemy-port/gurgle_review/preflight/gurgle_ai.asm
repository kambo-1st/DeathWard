00508ef0 push ebx
00508ef1 mov ebx, esp
00508ef3 sub esp, 8
00508ef6 and esp, 0xfffffff8
00508ef9 add esp, 4
00508efc push ebp
00508efd mov ebp, dword ptr [ebx + 4]
00508f00 mov dword ptr [esp + 4], ebp
00508f04 mov ebp, esp
00508f06 push -1
00508f08 push 0x9ef4d5
00508f0d mov eax, dword ptr fs:[0]
00508f13 push eax
00508f14 push ebx
00508f15 sub esp, 0x178
00508f1b mov eax, dword ptr [0xbaa3b4]
00508f20 xor eax, ebp
00508f22 mov dword ptr [ebp - 0x14], eax
00508f25 push esi
00508f26 push edi
00508f27 push eax
00508f28 lea eax, [ebp - 0xc]
00508f2b mov dword ptr fs:[0], eax
00508f31 mov edi, ecx
00508f33 mov ecx, dword ptr [edi + 0xab4]
00508f39 test ecx, ecx
00508f3b jne 0x509002
00508f41 movaps xmm1, xmmword ptr [0xb6c290]
00508f48 lea ecx, [edi + 0x1dc]
00508f4e lea eax, [ebp - 0x15c]
00508f54 mov dword ptr [edi + 0xab4], 4
00508f5e mov dword ptr [ebp - 0x13c], 0xbe48c8ca
00508f68 xorps xmm0, xmm0
00508f6b mov dword ptr [ebp - 0x138], 0x3f028283
00508f75 mov dword ptr [ebp - 0x134], 0x3e48c8ca
00508f7f cmp ecx, eax
00508f81 je 0x508fa0
00508f83 mov eax, dword ptr [ebp - 0x134]
00508f89 movups xmmword ptr [ecx + 0x10], xmm0
00508f8d movq xmm0, qword ptr [ebp - 0x13c]
00508f95 movq qword ptr [ecx + 0x20], xmm0
00508f9a movups xmmword ptr [ecx], xmm1
00508f9d mov dword ptr [ecx + 0x28], eax
00508fa0 cmp dword ptr [edi + 0x2c], 1
00508fa4 jne 0x509998
00508faa movaps xmm0, xmmword ptr [0xb6c880]
00508fb1 lea eax, [ebp - 0x188]
00508fb7 mov dword ptr [ebp - 0x168], 0x3f800000
00508fc1 xorps xmm1, xmm1
00508fc4 mov dword ptr [ebp - 0x164], 0x3f038384
00508fce mov dword ptr [ebp - 0x160], 0x3b808081
00508fd8 cmp ecx, eax
00508fda je 0x509998
00508fe0 mov eax, dword ptr [ebp - 0x160]
00508fe6 movups xmmword ptr [ecx], xmm0
00508fe9 movq xmm0, qword ptr [ebp - 0x168]
00508ff1 movq qword ptr [ecx + 0x20], xmm0
00508ff6 movups xmmword ptr [ecx + 0x10], xmm1
00508ffa mov dword ptr [ecx + 0x28], eax
00508ffd jmp 0x509998
00509002 cmp byte ptr [edi + 0x16b], 0
00509009 je 0x509081
0050900b movss xmm0, dword ptr [edi + 0x2d8]
00509013 comiss xmm0, dword ptr [0xb6aef8]
0050901a jbe 0x509998
00509020 call 0x6c3d90
00509025 xor edx, edx
00509027 mov ecx, 0x64
0050902c div ecx
0050902e cmp edx, 0xf
00509031 jae 0x509998
00509037 cmp dword ptr [edi + 0x2c], 0
0050903b jne 0x509998
00509041 push -1
00509043 push 0
00509045 push 0
00509047 push 0xee
0050904c mov ecx, edi
0050904e call 0x697c60
00509053 mov eax, dword ptr [edi + 0x2dc]
00509059 mov byte ptr [edi + 0x16b], 0
00509060 mov dword ptr [edi + 0x2d8], eax
00509066 call 0x6c3d90
0050906b xor edx, edx
0050906d mov ecx, 0x14
00509072 div ecx
00509074 add edx, ecx
00509076 mov dword ptr [edi + 0xaf0], edx
0050907c jmp 0x509998
00509081 movss xmm0, dword ptr [edi + 0x14]
00509086 xorps xmm2, xmm2
00509089 comiss xmm0, xmm2
0050908c jbe 0x5090ee
0050908e mov eax, dword ptr [edi + 8]
00509091 cmp eax, dword ptr [edi + 0xc]
00509094 je 0x5090ee
00509096 nop word ptr [eax + eax]
005090a0 mov ecx, dword ptr [eax + 0xc]
005090a3 mov edx, dword ptr [eax + 8]
005090a6 mov dword ptr [ebp - 0x12c], ecx
005090ac mov ecx, edx
005090ae and ecx, 6
005090b1 or ecx, 0
005090b4 je 0x5090e0
005090b6 mov ecx, dword ptr [eax + 0x30]
005090b9 shr ecx, 1
005090bb test cl, 1
005090be jne 0x5090e0
005090c0 cmp dword ptr [eax + 0x10], 1
005090c4 je 0x5090e0
005090c6 mov ecx, dword ptr [eax + 0x18]
005090c9 cmp ecx, 1
005090cc je 0x5090e0
005090ce cmp ecx, 3
005090d1 je 0x5090e0
005090d3 and edx, 0x1000
005090d9 or edx, 0
005090dc jne 0x5090e0
005090de mov dword ptr [eax], edx
005090e0 add eax, 0x38
005090e3 cmp eax, dword ptr [edi + 0xc]
005090e6 jne 0x5090a0
005090e8 mov ecx, dword ptr [edi + 0xab4]
005090ee cmp ecx, 4
005090f1 jne 0x509581
005090f7 call 0x6c3d90
005090fc xor edx, edx
005090fe mov ecx, 0xa
00509103 div ecx
00509105 test edx, edx
00509107 jne 0x509228
0050910d call 0x6c3d90
00509112 movd xmm0, eax
00509116 cvtdq2pd xmm0, xmm0
0050911a shr eax, 0x1f
0050911d addsd xmm0, qword ptr [eax*8 + 0xb6c940]
00509126 cvtpd2ps xmm0, xmm0
0050912a mulss xmm0, dword ptr [0xb6a19c]
00509132 mulss xmm0, dword ptr [0xb6a480]
0050913a addss xmm0, dword ptr [0xb6a350]
00509142 movss dword ptr [ebp - 0x124], xmm0
0050914a call 0x6c3d90
0050914f movss xmm1, dword ptr [edi + 0x294]
00509157 movss xmm0, dword ptr [edi + 0x298]
0050915f addss xmm1, xmm2
00509163 addss xmm0, dword ptr [0xb6a614]
0050916b mov ecx, dword ptr [0xbfd65c]
00509171 push 0
00509173 push 0xbeaaec
00509178 push 0xbeab18
0050917d push 0
0050917f push eax
00509180 push 0
00509182 push edi
00509183 push 0xc02fec
00509188 lea eax, [ebp - 0x120]
0050918e movss dword ptr [ebp - 0x120], xmm1
00509196 push eax
00509197 push 7
00509199 push 0x3e8
0050919e movss dword ptr [ebp - 0x11c], xmm0
005091a6 call 0x422e20
005091ab push eax
005091ac call 0x9ec34c
005091b1 movss xmm0, dword ptr [ebp - 0x124]
005091b9 add esp, 0x14
005091bc mov esi, eax
005091be push 1
005091c0 push 0
005091c2 movss dword ptr [esi + 0xd8], xmm0
005091ca movss dword ptr [esi + 0xdc], xmm0
005091d2 cmp dword ptr [edi + 0x2c], 0
005091d6 push 0xff
005091db push -1
005091dd jne 0x509213
005091df mov eax, dword ptr [esi]
005091e1 lea ecx, [ebp - 0x40]
005091e4 xorps xmm0, xmm0
005091e7 mov dword ptr [ebp - 0x20], 0
005091ee movups xmmword ptr [ebp - 0x30], xmm0
005091f2 push ecx
005091f3 movaps xmm0, xmmword ptr [0xb6be20]
005091fa mov ecx, esi
005091fc movups xmmword ptr [ebp - 0x40], xmm0
00509200 mov dword ptr [ebp - 0x1c], 0x3f000000
00509207 mov dword ptr [ebp - 0x18], 0
0050920e call dword ptr [eax + 0x38]
00509211 jmp 0x509221
00509213 mov edx, dword ptr [esi]
00509215 lea eax, [edi + 0x1dc]
0050921b push eax
0050921c mov ecx, esi
0050921e call dword ptr [edx + 0x38]
00509221 mov eax, dword ptr [esi]
00509223 mov ecx, esi
00509225 call dword ptr [eax + 0xc]
00509228 mov ecx, dword ptr [0xb40504]
0050922e mov eax, dword ptr [0xb40508]
00509233 mov dword ptr [ebp - 0x18], 0xf
0050923a mov dword ptr [ebp - 0x1c], 8
00509241 mov dword ptr [ebp - 0x2c], ecx
00509244 mov dword ptr [ebp - 0x28], eax
00509247 mov byte ptr [ebp - 0x24], 0
0050924b mov dword ptr [ebp - 4], 0
00509252 mov dword ptr [ebp - 0x44], 0xf
00509259 mov dword ptr [ebp - 0x48], 8
00509260 mov dword ptr [ebp - 0x58], ecx
00509263 mov dword ptr [ebp - 0x54], eax
00509266 mov byte ptr [ebp - 0x50], 0
0050926a push ecx
0050926b mov byte ptr [ebp - 4], 1
0050926f lea eax, [ebp - 0x2c]
00509272 mov dword ptr [esp], 0x3dcccccd
00509279 mov ecx, edi
0050927b push eax
0050927c lea eax, [ebp - 0x58]
0050927f push eax
00509280 call 0x6980a0
00509285 mov byte ptr [ebp - 4], 0
00509289 mov edx, dword ptr [ebp - 0x44]
0050928c cmp edx, 0x10
0050928f jb 0x5092b9
00509291 mov ecx, dword ptr [ebp - 0x58]
00509294 inc edx
00509295 mov eax, ecx
00509297 cmp edx, 0x1000
0050929d jb 0x5092af
0050929f mov ecx, dword ptr [ecx - 4]
005092a2 add edx, 0x23
005092a5 sub eax, ecx
005092a7 add eax, -4
005092aa cmp eax, 0x1f
005092ad ja 0x5092f8
005092af push edx
005092b0 push ecx
005092b1 call 0x9eb08e
005092b6 add esp, 8
005092b9 mov dword ptr [ebp - 4], 0xffffffff
005092c0 mov edx, dword ptr [ebp - 0x18]
005092c3 mov dword ptr [ebp - 0x48], 0
005092ca mov dword ptr [ebp - 0x44], 0xf
005092d1 mov byte ptr [ebp - 0x58], 0
005092d5 cmp edx, 0x10
005092d8 jb 0x509308
005092da mov ecx, dword ptr [ebp - 0x2c]
005092dd inc edx
005092de mov eax, ecx
005092e0 cmp edx, 0x1000
005092e6 jb 0x5092fe
005092e8 mov ecx, dword ptr [ecx - 4]
005092eb add edx, 0x23
005092ee sub eax, ecx
005092f0 add eax, -4
005092f3 cmp eax, 0x1f
005092f6 jbe 0x5092fe
005092f8 call dword ptr [0xa065ac]
005092fe push edx
005092ff push ecx
00509300 call 0x9eb08e
00509305 add esp, 8
00509308 mov eax, dword ptr [edi + 0x160]
0050930e and eax, 0x1000800
00509313 or eax, 0
00509316 je 0x50936e
00509318 cmp dword ptr [edi + 0xe6c], -1
0050931f jne 0x50936e
00509321 mov ecx, edi
00509323 call 0x695680
00509328 push 0
0050932a mov ecx, dword ptr [eax + 0x294]
00509330 mov eax, dword ptr [eax + 0x298]
00509336 mov dword ptr [ebp - 0x11c], eax
0050933c lea eax, [ebp - 0x120]
00509342 mov dword ptr [ebp - 0x120], ecx
00509348 lea ecx, [edi + 0x364]
0050934e push eax
0050934f call 0x7a4830
00509354 movss xmm0, dword ptr [edi + 0x2c4]
0050935c mulss xmm0, dword ptr [0xb6a560]
00509364 movss dword ptr [edi + 0x2c4], xmm0
0050936c jmp 0x50939e
0050936e push 1
00509370 push 0
00509372 sub esp, 8
00509375 lea eax, [ebp - 0x120]
0050937b mov ecx, edi
0050937d mov dword ptr [esp + 4], 0x3f19999a
00509385 mov dword ptr [esp], 0
0050938c push eax
0050938d call 0x695a30
00509392 push eax
00509393 lea ecx, [edi + 0x364]
00509399 call 0x7a3650
0050939e mov eax, dword ptr [edi + 0xe6c]
005093a4 mov esi, 3
005093a9 cmp eax, -1
005093ac je 0x5093ca
005093ae mov ecx, dword ptr [0xbfd680]
005093b4 push edi
005093b5 push eax
005093b6 push 0xa
005093b8 call 0x8b1170
005093bd xor ecx, ecx
005093bf test al, al
005093c1 setne cl
005093c4 test ecx, ecx
005093c6 je 0x509445
005093c8 jmp 0x5093f3
005093ca mov ecx, edi
005093cc call 0x695680
005093d1 push eax
005093d2 mov ecx, edi
005093d4 call 0x6aeb40
005093d9 test al, al
005093db je 0x509445
005093dd cmp byte ptr [edi + 0xa90], 0
005093e4 je 0x509445
005093e6 call 0x6c3d90
005093eb xor edx, edx
005093ed div esi
005093ef test edx, edx
005093f1 jne 0x509445
005093f3 mov eax, dword ptr [edi + 0x2c]
005093f6 test eax, eax
005093f8 jne 0x509414
005093fa push ecx
005093fb mov dword ptr [esp], 0x3f800000
00509402 push eax
00509403 push 0x28
00509405 push ecx
00509406 mov dword ptr [esp], 0x3f800000
0050940d push 0xa5
00509412 jmp 0x50943e
00509414 cmp eax, 1
00509417 jne 0x509445
00509419 call 0x6c3d90
0050941e xor edx, edx
00509420 div esi
00509422 test edx, edx
00509424 jne 0x509445
00509426 push ecx
00509427 mov dword ptr [esp], 0x3f800000
0050942e push edx
0050942f push 0x78
00509431 push ecx
00509432 mov dword ptr [esp], 0x3f800000
00509439 push 0xa7
0050943e mov ecx, edi
00509440 call 0x6ad720
00509445 xorps xmm0, xmm0
00509448 comiss xmm0, dword ptr [edi + 0x2b8]
0050944f seta al
00509452 cmp dword ptr [edi + 0xe6c], -1
00509459 mov byte ptr [edi + 0x13c], al
0050945f je 0x509479
00509461 movss xmm1, dword ptr [0xb6accc]
00509469 mov ecx, edi
0050946b push 7
0050946d push 0
0050946f call 0x6a15a0
00509474 movzx edx, al
00509477 jmp 0x50948c
00509479 call 0x6c3d90
0050947e xor edx, edx
00509480 mov ecx, 0x3c
00509485 div ecx
00509487 neg edx
00509489 sbb edx, edx
0050948b inc edx
0050948c test edx, edx
0050948e je 0x509998
00509494 cmp dword ptr [edi + 0x34], 0x38a
0050949b je 0x509998
005094a1 mov eax, dword ptr [edi + 0x160]
005094a7 and eax, 0x1000a00
005094ac or eax, 0
005094af jne 0x509998
005094b5 push 1
005094b7 mov ecx, edi
005094b9 call 0x6afe20
005094be mov ecx, edi
005094c0 call 0x695680
005094c5 cmp dword ptr [edi + 0xe6c], -1
005094cc movss xmm2, dword ptr [edi + 0x294]
005094d4 movss xmm0, dword ptr [edi + 0x298]
005094dc subss xmm2, dword ptr [eax + 0x294]
005094e4 subss xmm0, dword ptr [eax + 0x298]
005094ec movss dword ptr [ebp - 0x124], xmm2
005094f4 je 0x50950e
005094f6 movss xmm2, dword ptr [edi + 0xe70]
005094fe movss xmm0, dword ptr [edi + 0xe74]
00509506 movss dword ptr [ebp - 0x124], xmm2
0050950e movaps xmm1, xmm2
00509511 mulss xmm0, xmm0
00509515 mulss xmm1, xmm2
00509519 addss xmm1, xmm0
0050951d movss xmm0, dword ptr [0xb6ad48]
00509525 comiss xmm0, xmm1
00509528 jbe 0x509998
0050952e push 1
00509530 push 0xb40510
00509535 lea ecx, [edi + 0x3c]
00509538 mov dword ptr [edi + 0x360], 0
00509542 mov dword ptr [edi + 0xab4], 8
0050954c call 0x405740
00509551 test al, al
00509553 je 0x509564
00509555 lea ecx, [edi + 0x6c]
00509558 call 0x405330
0050955d mov byte ptr [edi + 0x80], 1
00509564 movss xmm0, dword ptr [ebp - 0x124]
0050956c comiss xmm0, dword ptr [0xb6a18c]
00509573 seta al
00509576 mov byte ptr [edi + 0x13c], al
0050957c jmp 0x509998
00509581 cmp dword ptr [edi + 0xe6c], -1
00509588 jne 0x5095a4
0050958a movss xmm0, dword ptr [0xc02fec]
00509592 movss dword ptr [edi + 0xe70], xmm0
0050959a movss xmm0, dword ptr [0xc02ff0]
005095a2 jmp 0x5095ec
005095a4 movss xmm2, dword ptr [0xb6a2cc]
005095ac lea eax, [ebp - 0x120]
005095b2 push eax
005095b3 mov ecx, edi
005095b5 call 0x6af380
005095ba movss xmm1, dword ptr [ebp - 0x120]
005095c2 ucomiss xmm1, dword ptr [0xc02fec]
005095c9 movss xmm0, dword ptr [ebp - 0x11c]
005095d1 lahf 
005095d2 test ah, 0x44
005095d5 jp 0x5095e4
005095d7 ucomiss xmm0, dword ptr [0xc02ff0]
005095de lahf 
005095df test ah, 0x44
005095e2 jnp 0x5095f4
005095e4 movss dword ptr [edi + 0xe70], xmm1
005095ec movss dword ptr [edi + 0xe74], xmm0
005095f4 cmp dword ptr [edi + 0x70], 0
005095f8 je 0x5098f0
005095fe push 0xb400ac
00509603 lea ecx, [edi + 0x6c]
00509606 call 0x405e90
0050960b test al, al
0050960d je 0x5098f0
00509613 mov ecx, edi
00509615 call 0x695680
0050961a cmp dword ptr [edi + 0xe6c], -1
00509621 movss xmm0, dword ptr [eax + 0x294]
00509629 movss dword ptr [ebp - 0x128], xmm0
00509631 movss xmm0, dword ptr [eax + 0x298]
00509639 movss dword ptr [ebp - 0x124], xmm0
00509641 je 0x5096a5
00509643 movss xmm2, dword ptr [edi + 0xe70]
0050964b ucomiss xmm2, dword ptr [0xc02fec]
00509652 lahf 
00509653 test ah, 0x44
00509656 jp 0x50966d
00509658 movss xmm0, dword ptr [edi + 0xe74]
00509660 ucomiss xmm0, dword ptr [0xc02ff0]
00509667 lahf 
00509668 test ah, 0x44
0050966b jnp 0x5096a5
0050966d movss xmm1, dword ptr [edi + 0xe74]
00509675 mulss xmm2, dword ptr [0xb6ab58]
0050967d mulss xmm1, dword ptr [0xb6ab58]
00509685 addss xmm2, dword ptr [edi + 0x294]
0050968d addss xmm1, dword ptr [edi + 0x298]
00509695 movss dword ptr [ebp - 0x128], xmm2
0050969d movss dword ptr [ebp - 0x124], xmm1
005096a5 push ecx
005096a6 mov dword ptr [esp], 0x3f800000
005096ad push 0
005096af push 2
005096b1 push ecx
005096b2 mov dword ptr [esp], 0x3f333333
005096b9 mov ecx, edi
005096bb push 0xd5
005096c0 call 0x6ad720
005096c5 lea ecx, [ebp - 0x118]
005096cb call 0x430d70
005096d0 push eax
005096d1 push ecx
005096d2 mov dword ptr [esp], 0x41200000
005096d9 lea eax, [ebp - 0x128]
005096df push eax
005096e0 push 1
005096e2 mov ecx, edi
005096e4 call 0x6a3420
005096e9 mov ecx, dword ptr [edi + 0x2c]
005096ec mov esi, eax
005096ee mov edx, dword ptr [esi + 0x388]
005096f4 mov eax, dword ptr [esi + 0x38c]
005096fa mov dword ptr [esi + 0x370], 0x3fcccccd
00509704 cmp ecx, 1
00509707 jne 0x5097bc
0050970d movaps xmm0, xmmword ptr [0xb6c610]
00509714 or eax, 8
00509717 push ecx
00509718 push 0
0050971a push 0xff
0050971f mov dword ptr [esi + 0x38c], eax
00509725 lea ecx, [ebp - 0x40]
00509728 mov eax, dword ptr [esi]
0050972a push -1
0050972c movups xmmword ptr [ebp - 0x40], xmm0
00509730 mov dword ptr [esi + 0x388], edx
00509736 xorps xmm0, xmm0
00509739 mov dword ptr [ebp - 0x20], 0x3f800000
00509740 push ecx
00509741 mov ecx, esi
00509743 mov dword ptr [ebp - 0x1c], 0x3e99999a
0050974a movups xmmword ptr [ebp - 0x30], xmm0
0050974e mov dword ptr [ebp - 0x18], 0
00509755 call dword ptr [eax + 0x38]
00509758 cmp byte ptr [edi + 0x13c], 0
0050975f je 0x50976b
00509761 movss xmm0, dword ptr [0xb6aeac]
00509769 jmp 0x509773
0050976b movss xmm0, dword ptr [0xb6a940]
00509773 movss dword ptr [ebp - 0x120], xmm0
0050977b lea eax, [esi + 0xe4]
00509781 movss xmm0, dword ptr [edi + 0x294]
00509789 lea edx, [ebp - 0x128]
0050978f addss xmm0, dword ptr [0xb6a18c]
00509797 movss dword ptr [ebp - 0x128], xmm0
0050979f movss xmm0, dword ptr [edi + 0x298]
005097a7 addss xmm0, dword ptr [0xb6a7b0]
005097af movss dword ptr [ebp - 0x124], xmm0
005097b7 jmp 0x50985e
005097bc movss xmm0, dword ptr [0xb6a614]
005097c4 lea ecx, [ebp - 0x6c]
005097c7 or edx, 2
005097ca mov dword ptr [esi + 0x38c], eax
005097d0 movaps xmm3, xmm0
005097d3 mov dword ptr [esi + 0x388], edx
005097d9 movaps xmm2, xmm0
005097dc movaps xmm1, xmm0
005097df call 0x427080
005097e4 mov eax, dword ptr [esi]
005097e6 movaps xmm0, xmmword ptr [0xb6c330]
005097ed push 1
005097ef push 0
005097f1 push 0xff
005097f6 push -1
005097f8 push ecx
005097f9 mov ecx, esi
005097fb movups xmmword ptr [ebp - 0x5c], xmm0
005097ff call dword ptr [eax + 0x38]
00509802 cmp byte ptr [edi + 0x13c], 0
00509809 je 0x509815
0050980b movss xmm0, dword ptr [0xb6aeac]
00509813 jmp 0x50981d
00509815 movss xmm0, dword ptr [0xb6a940]
0050981d movss dword ptr [ebp - 0x120], xmm0
00509825 lea eax, [ebp - 0x6c]
00509828 movss xmm0, dword ptr [edi + 0x294]
00509830 lea edx, [ebp - 0x130]
00509836 addss xmm0, dword ptr [0xb6a18c]
0050983e movss dword ptr [ebp - 0x130], xmm0
00509846 movss xmm0, dword ptr [edi + 0x298]
0050984e addss xmm0, dword ptr [0xb6a7b0]
00509856 movss dword ptr [ebp - 0x12c], xmm0
0050985e push 0xc02fec
00509863 push eax
00509864 lea eax, [ebp - 0x120]
0050986a mov dword ptr [ebp - 0x11c], 0xc1700000
00509874 push eax
00509875 mov ecx, 2
0050987a call 0x6aead0
0050987f movss xmm1, dword ptr [esi + 0x2b8]
00509887 add esp, 0xc
0050988a movss xmm0, dword ptr [esi + 0x368]
00509892 subss xmm0, dword ptr [0xb6a4c4]
0050989a mulss xmm1, dword ptr [0xb6a4a0]
005098a2 movss xmm2, dword ptr [esi + 0x2bc]
005098aa mulss xmm2, dword ptr [0xb6a4a0]
005098b2 movss dword ptr [esi + 0x368], xmm0
005098ba movss xmm0, dword ptr [esi + 0x364]
005098c2 movss dword ptr [esi + 0x2b8], xmm1
005098ca movss xmm1, dword ptr [0xb6a50c]
005098d2 mulss xmm0, xmm1
005098d6 movss dword ptr [esi + 0x2bc], xmm2
005098de subss xmm0, dword ptr [0xb6a864]
005098e6 movss dword ptr [esi + 0x364], xmm0
005098ee jmp 0x5098f8
005098f0 movss xmm1, dword ptr [0xb6a50c]
005098f8 movss xmm0, dword ptr [edi + 0x2c4]
00509900 mulss xmm0, xmm1
00509904 movss dword ptr [edi + 0x2c4], xmm0
0050990c cmp dword ptr [edi + 0x70], 0
00509910 je 0x50991b
00509912 cmp byte ptr [edi + 0x80], 0
00509919 jne 0x509998
0050991b mov dword ptr [edi + 0xab4], 4
00509925 mov esi, dword ptr [edi + 0x70]
00509928 test esi, esi
0050992a je 0x509976
0050992c cmp dword ptr [esi + 0x14], 0x10
00509930 mov eax, esi
00509932 jb 0x509936
00509934 mov eax, dword ptr [esi]
00509936 mov ecx, 0xb3fd8c
0050993b nop dword ptr [eax + eax]
00509940 mov dl, byte ptr [eax]
00509942 cmp dl, byte ptr [ecx]
00509944 jne 0x509960
00509946 test dl, dl
00509948 je 0x50995c
0050994a mov dl, byte ptr [eax + 1]
0050994d cmp dl, byte ptr [ecx + 1]
00509950 jne 0x509960
00509952 add eax, 2
00509955 add ecx, 2
00509958 test dl, dl
0050995a jne 0x509940
0050995c xor eax, eax
0050995e jmp 0x509965
00509960 sbb eax, eax
00509962 or eax, 1
00509965 test eax, eax
00509967 jne 0x509976
00509969 cmp byte ptr [esi + 0x34], al
0050996c je 0x509998
0050996e cmp byte ptr [edi + 0x80], al
00509974 jne 0x509998
00509976 push 1
00509978 push 0xb3fd8c
0050997d lea ecx, [edi + 0x3c]
00509980 call 0x405740
00509985 test al, al
00509987 je 0x509998
00509989 lea ecx, [edi + 0x6c]
0050998c call 0x405330
00509991 mov byte ptr [edi + 0x80], 1
00509998 mov ecx, dword ptr [ebp - 0xc]
0050999b mov dword ptr fs:[0], ecx
005099a2 pop ecx
005099a3 pop edi
005099a4 pop esi
005099a5 mov ecx, dword ptr [ebp - 0x14]
005099a8 xor ecx, ebp
005099aa call 0x9eacd7
005099af mov esp, ebp
005099b1 pop ebp
005099b2 mov esp, ebx
005099b4 pop ebx
005099b5 ret 
