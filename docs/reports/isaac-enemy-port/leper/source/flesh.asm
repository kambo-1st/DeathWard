005351f0 push ebx
005351f1 mov ebx, esp
005351f3 sub esp, 8
005351f6 and esp, 0xfffffff0
005351f9 add esp, 4
005351fc push ebp
005351fd mov ebp, dword ptr [ebx + 4]
00535200 mov dword ptr [esp + 4], ebp
00535204 mov ebp, esp
00535206 sub esp, 0x118
0053520c mov eax, dword ptr [0xbaa3b4]
00535211 xor eax, ebp
00535213 mov dword ptr [ebp - 4], eax
00535216 push esi
00535217 push edi
00535218 mov edi, ecx
0053521a mov eax, dword ptr [edi + 0xab4]
00535220 test eax, eax
00535222 je 0x5353c6
00535228 cmp eax, 4
0053522b jne 0x535509
00535231 movss xmm0, dword ptr [edi + 0x2c4]
00535239 lea eax, [ebp - 0xc0]
0053523f mulss xmm0, dword ptr [0xb6a5d8]
00535247 push ecx
00535248 mov dword ptr [esp], 0
0053524f push eax
00535250 movss dword ptr [edi + 0x2c4], xmm0
00535258 call 0x695a30
0053525d movss xmm1, dword ptr [eax]
00535261 subss xmm1, dword ptr [edi + 0x294]
00535269 movss xmm2, dword ptr [eax + 4]
0053526e subss xmm2, dword ptr [edi + 0x298]
00535276 movaps xmm0, xmm1
00535279 movss dword ptr [ebp - 0xb8], xmm1
00535281 mulss xmm0, xmm1
00535285 movaps xmm1, xmm2
00535288 movss dword ptr [ebp - 0xb4], xmm2
00535290 mulss xmm1, xmm2
00535294 addss xmm0, xmm1
00535298 call 0x4228c0
0053529d xorps xmm1, xmm1
005352a0 comiss xmm0, xmm1
005352a3 jbe 0x5352d9
005352a5 movss xmm1, dword ptr [0xb6a614]
005352ad divss xmm1, xmm0
005352b1 movss xmm0, dword ptr [ebp - 0xb8]
005352b9 mulss xmm0, xmm1
005352bd movss dword ptr [ebp - 0xb8], xmm0
005352c5 movss xmm0, dword ptr [ebp - 0xb4]
005352cd mulss xmm0, xmm1
005352d1 movss dword ptr [ebp - 0xb4], xmm0
005352d9 cmp dword ptr [edi + 0xe6c], -1
005352e0 je 0x53530c
005352e2 lea eax, [ebp - 0xc0]
005352e8 xorps xmm2, xmm2
005352eb push eax
005352ec mov ecx, edi
005352ee call 0x6af0c0
005352f3 movss xmm0, dword ptr [eax]
005352f7 movss dword ptr [ebp - 0xb8], xmm0
005352ff movss xmm0, dword ptr [eax + 4]
00535304 movss dword ptr [ebp - 0xb4], xmm0
0053530c call 0x6c3d90
00535311 xorps xmm0, xmm0
00535314 cvtsi2sd xmm0, eax
00535318 shr eax, 0x1f
0053531b addsd xmm0, qword ptr [eax*8 + 0xb6c940]
00535324 cvtpd2ps xmm0, xmm0
00535328 mulss xmm0, dword ptr [0xb6a19c]
00535330 mulss xmm0, dword ptr [0xb6a874]
00535338 addss xmm0, xmm0
0053533c movss dword ptr [ebp - 0xc4], xmm0
00535344 call 0x411fe0
00535349 movss dword ptr [ebp - 0xbc], xmm0
00535351 movss xmm0, dword ptr [ebp - 0xc4]
00535359 call 0x412010
0053535e movss xmm2, dword ptr [edi + 0x2f4]
00535366 movaps xmm3, xmm0
00535369 movss xmm0, dword ptr [ebp - 0xbc]
00535371 addss xmm3, xmm3
00535375 addss xmm0, xmm0
00535379 addss xmm3, dword ptr [ebp - 0xb4]
00535381 addss xmm0, dword ptr [ebp - 0xb8]
00535389 mulss xmm3, dword ptr [0xb6a304]
00535391 mulss xmm0, dword ptr [0xb6a304]
00535399 mulss xmm3, xmm2
0053539d mulss xmm0, xmm2
005353a1 addss xmm3, dword ptr [edi + 0x2bc]
005353a9 addss xmm0, dword ptr [edi + 0x2b8]
005353b1 movss dword ptr [edi + 0x2bc], xmm3
005353b9 movss dword ptr [edi + 0x2b8], xmm0
005353c1 jmp 0x535509
005353c6 mov esi, dword ptr [edi + 0x344]
005353cc movq xmm0, qword ptr [0xa08b0c]
005353d4 mov eax, dword ptr [0xa08b14]
005353d9 movq qword ptr [ebp - 0xcc], xmm0
005353e1 mov dword ptr [ebp - 0xb8], eax
005353e7 test esi, esi
005353e9 jne 0x5353fb
005353eb push 0xb4d6c4
005353f0 push 3
005353f2 call 0x95e330
005353f7 add esp, 8
005353fa int3 
005353fb mov ecx, dword ptr [ebp - 0xcc]
00535401 mov edx, esi
00535403 shr edx, cl
00535405 mov ecx, dword ptr [ebp - 0xc8]
0053540b xor edx, esi
0053540d mov eax, edx
0053540f shl eax, cl
00535411 mov ecx, dword ptr [ebp - 0xb8]
00535417 xor eax, edx
00535419 mov esi, eax
0053541b shr esi, cl
0053541d xor esi, eax
0053541f mov eax, 0xaaaaaaab
00535424 mul esi
00535426 mov eax, esi
00535428 shr edx, 2
0053542b lea ecx, [edx + edx*2]
0053542e add ecx, ecx
00535430 sub eax, ecx
00535432 mov ecx, dword ptr [eax*4 + 0xb42c68]
00535439 mov dword ptr [ebp - 0xb4], ecx
0053543f mov ecx, dword ptr [edi + 0x70]
00535442 test ecx, ecx
00535444 je 0x535493
00535446 cmp dword ptr [ecx + 0x14], 0x10
0053544a mov eax, ecx
0053544c jb 0x535450
0053544e mov eax, dword ptr [ecx]
00535450 mov ecx, dword ptr [ebp - 0xb4]
00535456 mov dl, byte ptr [eax]
00535458 cmp dl, byte ptr [ecx]
0053545a jne 0x535476
0053545c test dl, dl
0053545e je 0x535472
00535460 mov dl, byte ptr [eax + 1]
00535463 cmp dl, byte ptr [ecx + 1]
00535466 jne 0x535476
00535468 add eax, 2
0053546b add ecx, 2
0053546e test dl, dl
00535470 jne 0x535456
00535472 xor eax, eax
00535474 jmp 0x53547b
00535476 sbb eax, eax
00535478 or eax, 1
0053547b lea ecx, [edi + 0x3c]
0053547e test eax, eax
00535480 jne 0x535496
00535482 mov eax, dword ptr [ecx + 0x34]
00535485 cmp byte ptr [eax + 0x34], 0
00535489 je 0x5354b6
0053548b cmp byte ptr [ecx + 0x44], 0
0053548f jne 0x5354b6
00535491 jmp 0x535496
00535493 lea ecx, [edi + 0x3c]
00535496 push 1
00535498 push dword ptr [ebp - 0xb4]
0053549e call 0x405740
005354a3 test al, al
005354a5 je 0x5354b6
005354a7 lea ecx, [edi + 0x6c]
005354aa call 0x405330
005354af mov byte ptr [edi + 0x80], 1
005354b6 mov dword ptr [edi + 0xab4], 4
005354c0 test esi, esi
005354c2 jne 0x5354d4
005354c4 push 0xb4d6c4
005354c9 push 3
005354cb call 0x95e330
005354d0 add esp, 8
005354d3 int3 
005354d4 mov ecx, dword ptr [ebp - 0xcc]
005354da mov eax, esi
005354dc shr eax, cl
005354de mov ecx, dword ptr [ebp - 0xc8]
005354e4 xor eax, esi
005354e6 mov edx, eax
005354e8 mov byte ptr [edi + 0x16c], 1
005354ef shl edx, cl
005354f1 mov ecx, dword ptr [ebp - 0xb8]
005354f7 xor edx, eax
005354f9 mov eax, edx
005354fb shr eax, cl
005354fd xor al, dl
005354ff not al
00535501 and al, 1
00535503 mov byte ptr [edi + 0x13c], al
00535509 push 0
0053550b push 0xa
0053550d mov ecx, edi
0053550f call 0x684790
00535514 test al, al
00535516 je 0x53555a
00535518 call 0x6c3d90
0053551d push ecx
0053551e mov ecx, edi
00535520 movd xmm0, eax
00535524 cvtdq2pd xmm0, xmm0
00535528 shr eax, 0x1f
0053552b addsd xmm0, qword ptr [eax*8 + 0xb6c940]
00535534 cvtpd2ps xmm1, xmm0
00535538 mulss xmm1, dword ptr [0xb6a19c]
00535540 mulss xmm1, dword ptr [0xb6a434]
00535548 addss xmm1, dword ptr [0xb6a434]
00535550 movss dword ptr [esp], xmm1
00535555 call 0x68d7b0
0053555a push 0
0053555c push 6
0053555e mov ecx, edi
00535560 call 0x684790
00535565 movss xmm0, dword ptr [0xb6a3b0]
0053556d movaps xmmword ptr [ebp - 0xe0], xmm0
00535574 test al, al
00535576 je 0x535745
0053557c call 0x6c3d90
00535581 movd xmm0, eax
00535585 cvtdq2pd xmm0, xmm0
00535589 shr eax, 0x1f
0053558c addsd xmm0, qword ptr [eax*8 + 0xb6c940]
00535595 cvtpd2ps xmm0, xmm0
00535599 mulss xmm0, dword ptr [0xb6a19c]
005355a1 movss dword ptr [ebp - 0xb4], xmm0
005355a9 call 0x6c3d90
005355ae mov esi, eax
005355b0 call 0x6c3d90
005355b5 movd xmm0, eax
005355b9 cvtdq2pd xmm0, xmm0
005355bd shr eax, 0x1f
005355c0 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
005355c9 cvtpd2ps xmm0, xmm0
005355cd mulss xmm0, dword ptr [0xb6a19c]
005355d5 mulss xmm0, dword ptr [0xb6a874]
005355dd addss xmm0, xmm0
005355e1 movss dword ptr [ebp - 0xbc], xmm0
005355e9 call 0x411fe0
005355ee mulss xmm0, dword ptr [ebp - 0xb4]
005355f6 movss xmm1, dword ptr [edi + 0x2b8]
005355fe mulss xmm1, dword ptr [ebp - 0xe0]
00535606 mulss xmm0, dword ptr [0xb6a864]
0053560e addss xmm0, xmm1
00535612 movss dword ptr [ebp - 0xc8], xmm0
0053561a movss xmm0, dword ptr [ebp - 0xbc]
00535622 call 0x412010
00535627 mulss xmm0, dword ptr [ebp - 0xb4]
0053562f lea eax, [ebp - 0xc8]
00535635 mov ecx, dword ptr [0xbfd65c]
0053563b movss xmm1, dword ptr [edi + 0x2bc]
00535643 mulss xmm1, dword ptr [ebp - 0xe0]
0053564b push esi
0053564c mulss xmm0, dword ptr [0xb6a864]
00535654 push 0
00535656 push 0
00535658 push eax
00535659 lea eax, [edi + 0x294]
0053565f addss xmm0, xmm1
00535663 push eax
00535664 push 0x6f
00535666 push 0x3e8
0053566b movss dword ptr [ebp - 0xc4], xmm0
00535673 call 0x422e20
00535678 mov esi, eax
0053567a call 0x6c3d90
0053567f movss xmm2, dword ptr [0xb6a4c4]
00535687 movss xmm3, dword ptr [0xb6a480]
0053568f movd xmm0, eax
00535693 cvtdq2pd xmm0, xmm0
00535697 shr eax, 0x1f
0053569a addsd xmm0, qword ptr [eax*8 + 0xb6c940]
005356a3 cvtpd2ps xmm0, xmm0
005356a7 mulss xmm0, dword ptr [0xb6a19c]
005356af mulss xmm0, xmm2
005356b3 addss xmm0, xmm3
005356b7 movss dword ptr [esi + 0x140], xmm0
005356bf call 0x6c3d90
005356c4 movd xmm0, eax
005356c8 cvtdq2pd xmm0, xmm0
005356cc shr eax, 0x1f
005356cf addsd xmm0, qword ptr [eax*8 + 0xb6c940]
005356d8 cvtpd2ps xmm1, xmm0
005356dc mulss xmm1, dword ptr [0xb6a19c]
005356e4 mulss xmm1, xmm2
005356e8 addss xmm1, xmm2
005356ec movss xmm2, dword ptr [edi + 0xb88]
005356f4 movaps xmm0, xmm2
005356f7 mulss xmm2, dword ptr [0xbc7a2c]
005356ff mulss xmm0, dword ptr [0xbc7a28]
00535707 mov dword ptr [esi + 0x2a4], 0
00535711 mulss xmm2, xmm3
00535715 mov dword ptr [esi + 0x2a8], 0xc1b00000
0053571f mulss xmm0, xmm3
00535723 mov dword ptr [esi + 0x2ac], 0xfffffe70
0053572d mulss xmm2, xmm1
00535731 mulss xmm0, xmm1
00535735 movss dword ptr [esi + 0xdc], xmm2
0053573d movss dword ptr [esi + 0xd8], xmm0
00535745 mov eax, dword ptr [edi + 0xe6c]
0053574b cmp eax, -1
0053574e je 0x535764
00535750 push edi
00535751 push eax
00535752 push 9
00535754 call 0x8b10b0
00535759 test al, al
0053575b je 0x535764
0053575d mov eax, dword ptr [edi]
0053575f mov ecx, edi
00535761 call dword ptr [eax + 0x24]
00535764 cmp byte ptr [edi + 0x16b], 0
0053576b je 0x5358cc
00535771 mov ecx, edi
00535773 call 0x695680
00535778 mov esi, eax
0053577a movss xmm1, dword ptr [esi + 0x294]
00535782 movss xmm0, dword ptr [esi + 0x298]
0053578a subss xmm0, dword ptr [edi + 0x298]
00535792 subss xmm1, dword ptr [edi + 0x294]
0053579a mulss xmm0, xmm0
0053579e mulss xmm1, xmm1
005357a2 addss xmm0, xmm1
005357a6 call 0x4228c0
005357ab movss xmm2, dword ptr [esi + 0x2b8]
005357b3 movaps xmm1, xmm0
005357b6 movss xmm3, dword ptr [esi + 0x2bc]
005357be mulss xmm2, dword ptr [0xb6a2cc]
005357c6 mulss xmm3, dword ptr [0xb6a2cc]
005357ce mulss xmm2, xmm1
005357d2 mulss xmm3, xmm1
005357d6 addss xmm2, dword ptr [esi + 0x294]
005357de addss xmm3, dword ptr [esi + 0x298]
005357e6 subss xmm2, dword ptr [edi + 0x294]
005357ee subss xmm3, dword ptr [edi + 0x298]
005357f6 movaps xmm0, xmm2
005357f9 movss dword ptr [ebp - 0xb4], xmm2
00535801 mulss xmm0, xmm2
00535805 movaps xmm1, xmm3
00535808 movss dword ptr [ebp - 0xb8], xmm3
00535810 mulss xmm1, xmm3
00535814 addss xmm0, xmm1
00535818 call 0x4228c0
0053581d movss xmm1, dword ptr [ebp - 0xb4]
00535825 xorps xmm4, xmm4
00535828 comiss xmm0, xmm4
0053582b movss xmm2, dword ptr [ebp - 0xb8]
00535833 jbe 0x53584c
00535835 movss xmm3, dword ptr [0xb6a614]
0053583d divss xmm3, xmm0
00535841 movaps xmm0, xmm3
00535844 mulss xmm2, xmm3
00535848 mulss xmm1, xmm0
0053584c mulss xmm1, dword ptr [0xb6a974]
00535854 lea ecx, [ebp - 0xb0]
0053585a mulss xmm2, dword ptr [0xb6a974]
00535862 movss dword ptr [ebp - 0xc0], xmm1
0053586a movss dword ptr [ebp - 0xbc], xmm2
00535872 call 0x430d70
00535877 movaps xmm0, xmmword ptr [0xb6c610]
0053587e xorps xmm1, xmm1
00535881 mov dword ptr [ebp - 0xe4], 0
0053588b mov ecx, edi
0053588d mov eax, dword ptr [ebp - 0xe4]
00535893 mov dword ptr [ebp - 0x5c], eax
00535896 lea eax, [ebp - 0xb0]
0053589c push eax
0053589d push 0
0053589f movups xmmword ptr [ebp - 0x84], xmm0
005358a6 lea eax, [ebp - 0xc0]
005358ac movaps xmm0, xmmword ptr [ebp - 0xe0]
005358b3 push eax
005358b4 lea eax, [edi + 0x294]
005358ba unpcklps xmm0, xmm4
005358bd push eax
005358be movups xmmword ptr [ebp - 0x74], xmm1
005358c2 movq qword ptr [ebp - 0x64], xmm0
005358c7 call 0x6a1a20
005358cc mov ecx, dword ptr [ebp - 4]
005358cf pop edi
005358d0 xor ecx, ebp
005358d2 pop esi
005358d3 call 0x9eacd7
005358d8 mov esp, ebp
005358da pop ebp
005358db mov esp, ebx
005358dd pop ebx
005358de ret 
