004fa1e0 push ebx
004fa1e1 mov ebx, esp
004fa1e3 sub esp, 8
004fa1e6 and esp, 0xfffffff8
004fa1e9 add esp, 4
004fa1ec push ebp
004fa1ed mov ebp, dword ptr [ebx + 4]
004fa1f0 mov dword ptr [esp + 4], ebp
004fa1f4 mov ebp, esp
004fa1f6 push -1
004fa1f8 push 0x9ef2e5
004fa1fd mov eax, dword ptr fs:[0]
004fa203 push eax
004fa204 push ebx
004fa205 sub esp, 0x80
004fa20b mov eax, dword ptr [0xbaa3b4]
004fa210 xor eax, ebp
004fa212 mov dword ptr [ebp - 0x14], eax
004fa215 push esi
004fa216 push edi
004fa217 push eax
004fa218 lea eax, [ebp - 0xc]
004fa21b mov dword ptr fs:[0], eax
004fa221 mov edi, ecx
004fa223 mov dword ptr [ebp - 0x64], edi
004fa226 mov eax, dword ptr [edi + 0xab4]
004fa22c test eax, eax
004fa22e jne 0x4fa27a
004fa230 cmp dword ptr [edi + 0x28], 0x331
004fa237 jne 0x4fa261
004fa239 push eax
004fa23a push 0xb41e88
004fa23f lea ecx, [edi + 0x3c]
004fa242 call 0x405a00
004fa247 cmp dword ptr [edi + 0x2c], 1
004fa24b jne 0x4fa261
004fa24d mov dword ptr [edi + 0x2a8], 0xc0c00000
004fa257 mov dword ptr [edi + 0x17c], 6
004fa261 mov dword ptr [edi + 0xab4], 4
004fa26b mov dword ptr [edi + 0xb00], 0
004fa275 jmp 0x4fb1a7
004fa27a cmp eax, 4
004fa27d jne 0x4fa4f5
004fa283 cmp dword ptr [edi + 0xe6c], -1
004fa28a jne 0x4fa2ac
004fa28c call 0x695680
004fa291 push eax
004fa292 mov ecx, edi
004fa294 call 0x6aeb40
004fa299 test al, al
004fa29b jne 0x4fa2ac
004fa29d push 1
004fa29f lea ecx, [edi + 0x364]
004fa2a5 call 0x7a6180
004fa2aa jmp 0x4fa323
004fa2ac push 0
004fa2ae push ecx
004fa2af lea eax, [ebp - 0x1c]
004fa2b2 mov dword ptr [esp], 0
004fa2b9 push eax
004fa2ba mov ecx, edi
004fa2bc call 0x695a30
004fa2c1 push eax
004fa2c2 lea ecx, [edi + 0x364]
004fa2c8 call 0x7a4830
004fa2cd cmp dword ptr [edi + 0xe6c], -1
004fa2d4 je 0x4fa2e4
004fa2d6 push 0xa
004fa2d8 mov ecx, edi
004fa2da call 0x6af080
004fa2df movzx eax, al
004fa2e2 jmp 0x4fa2ef
004fa2e4 xor eax, eax
004fa2e6 cmp dword ptr [edi + 0xaa0], eax
004fa2ec setg al
004fa2ef test eax, eax
004fa2f1 je 0x4fa323
004fa2f3 call 0x6c3d90
004fa2f8 mov ecx, 0x64
004fa2fd xor edx, edx
004fa2ff div ecx
004fa301 push ecx
004fa302 mov dword ptr [esp], 0x3f800000
004fa309 push 0
004fa30b lea eax, [edx + 0x2d]
004fa30e push eax
004fa30f push ecx
004fa310 mov dword ptr [esp], 0x3f800000
004fa317 mov ecx, edi
004fa319 push 0x8f
004fa31e call 0x6ad720
004fa323 cmp dword ptr [edi + 0x28], 0x331
004fa32a jne 0x4fa37f
004fa32c cmp dword ptr [edi + 0x2c], 1
004fa330 jne 0x4fa37f
004fa332 push 0
004fa334 push 0xb404ec
004fa339 lea ecx, [edi + 0x3c]
004fa33c call 0x4054f0
004fa341 movss xmm3, dword ptr [edi + 0x2b8]
004fa349 movss xmm0, dword ptr [edi + 0x2bc]
004fa351 movaps xmm2, xmm3
004fa354 andps xmm2, xmmword ptr [0xb6c980]
004fa35b andps xmm0, xmmword ptr [0xb6c980]
004fa362 comiss xmm2, xmm0
004fa365 jbe 0x4fa46a
004fa36b xorps xmm0, xmm0
004fa36e comiss xmm0, xmm3
004fa371 seta al
004fa374 mov byte ptr [edi + 0x13c], al
004fa37a jmp 0x4fa46a
004fa37f mov eax, dword ptr [0xb404ec]
004fa384 mov ecx, dword ptr [0xb404f0]
004fa38a mov dword ptr [ebp - 0x30], 0xf
004fa391 mov dword ptr [ebp - 0x34], 8
004fa398 mov dword ptr [ebp - 0x44], eax
004fa39b mov dword ptr [ebp - 0x40], ecx
004fa39e mov byte ptr [ebp - 0x3c], 0
004fa3a2 mov dword ptr [ebp - 4], 0
004fa3a9 mov eax, dword ptr [0xb40504]
004fa3ae mov ecx, dword ptr [0xb40508]
004fa3b4 mov dword ptr [ebp - 0x18], 0xf
004fa3bb mov dword ptr [ebp - 0x1c], 8
004fa3c2 mov dword ptr [ebp - 0x2c], eax
004fa3c5 mov dword ptr [ebp - 0x28], ecx
004fa3c8 mov byte ptr [ebp - 0x24], 0
004fa3cc push ecx
004fa3cd mov byte ptr [ebp - 4], 1
004fa3d1 lea eax, [ebp - 0x44]
004fa3d4 mov dword ptr [esp], 0x3dcccccd
004fa3db mov ecx, edi
004fa3dd push eax
004fa3de lea eax, [ebp - 0x2c]
004fa3e1 push eax
004fa3e2 call 0x6980a0
004fa3e7 mov byte ptr [ebp - 4], 0
004fa3eb mov edx, dword ptr [ebp - 0x18]
004fa3ee cmp edx, 0x10
004fa3f1 jb 0x4fa41b
004fa3f3 mov ecx, dword ptr [ebp - 0x2c]
004fa3f6 inc edx
004fa3f7 mov eax, ecx
004fa3f9 cmp edx, 0x1000
004fa3ff jb 0x4fa411
004fa401 mov ecx, dword ptr [ecx - 4]
004fa404 add edx, 0x23
004fa407 sub eax, ecx
004fa409 add eax, -4
004fa40c cmp eax, 0x1f
004fa40f ja 0x4fa45a
004fa411 push edx
004fa412 push ecx
004fa413 call 0x9eb08e
004fa418 add esp, 8
004fa41b mov dword ptr [ebp - 4], 0xffffffff
004fa422 mov edx, dword ptr [ebp - 0x30]
004fa425 mov dword ptr [ebp - 0x1c], 0
004fa42c mov dword ptr [ebp - 0x18], 0xf
004fa433 mov byte ptr [ebp - 0x2c], 0
004fa437 cmp edx, 0x10
004fa43a jb 0x4fa46a
004fa43c mov ecx, dword ptr [ebp - 0x44]
004fa43f inc edx
004fa440 mov eax, ecx
004fa442 cmp edx, 0x1000
004fa448 jb 0x4fa460
004fa44a mov ecx, dword ptr [ecx - 4]
004fa44d add edx, 0x23
004fa450 sub eax, ecx
004fa452 add eax, -4
004fa455 cmp eax, 0x1f
004fa458 jbe 0x4fa460
004fa45a call dword ptr [0xa065ac]
004fa460 push edx
004fa461 push ecx
004fa462 call 0x9eb08e
004fa467 add esp, 8
004fa46a cmp dword ptr [edi + 0x70], 0
004fa46e je 0x4fa48a
004fa470 cmp byte ptr [edi + 0x80], 0
004fa477 je 0x4fa48a
004fa479 push 0
004fa47b push 0xb41228
004fa480 lea ecx, [edi + 0x3c]
004fa483 call 0x405a00
004fa488 jmp 0x4fa4b4
004fa48a push 1
004fa48c push 0xb41228
004fa491 lea ecx, [edi + 0x3c]
004fa494 call 0x405bb0
004fa499 test al, al
004fa49b je 0x4fa4b4
004fa49d cmp dword ptr [edi + 0x90], 0
004fa4a4 je 0x4fa4b4
004fa4a6 lea ecx, [edi + 0x8c]
004fa4ac xorps xmm1, xmm1
004fa4af call 0x403c00
004fa4b4 cmp dword ptr [edi + 0x28], 0x16
004fa4b8 movss xmm0, dword ptr [edi + 0x2c4]
004fa4c0 mulss xmm0, dword ptr [0xb6a560]
004fa4c8 movss dword ptr [edi + 0x2c4], xmm0
004fa4d0 jne 0x4fa94c
004fa4d6 cmp dword ptr [edi + 0x2c], 1
004fa4da jne 0x4fa94c
004fa4e0 mulss xmm0, dword ptr [0xb6a5d8]
004fa4e8 movss dword ptr [edi + 0x2c4], xmm0
004fa4f0 jmp 0x4fa94c
004fa4f5 cmp dword ptr [edi + 0x28], 0x16
004fa4f9 jne 0x4fa612
004fa4ff cmp dword ptr [edi + 0x2c], 2
004fa503 je 0x4fa50f
004fa505 cmp dword ptr [edi + 0x2c], 3
004fa509 jne 0x4fa612
004fa50f movss xmm0, dword ptr [edi + 0x2c4]
004fa517 mulss xmm0, dword ptr [0xb6a560]
004fa51f mov dword ptr [ebp - 0x30], 0xf
004fa526 mov dword ptr [ebp - 0x34], 8
004fa52d mov byte ptr [ebp - 0x3c], 0
004fa531 movss dword ptr [edi + 0x2c4], xmm0
004fa539 mov eax, dword ptr [0xb404ec]
004fa53e mov ecx, dword ptr [0xb404f0]
004fa544 mov dword ptr [ebp - 0x44], eax
004fa547 mov dword ptr [ebp - 0x40], ecx
004fa54a mov dword ptr [ebp - 4], 2
004fa551 mov eax, dword ptr [0xb40504]
004fa556 mov ecx, dword ptr [0xb40508]
004fa55c mov dword ptr [ebp - 0x18], 0xf
004fa563 mov dword ptr [ebp - 0x1c], 8
004fa56a mov dword ptr [ebp - 0x2c], eax
004fa56d mov dword ptr [ebp - 0x28], ecx
004fa570 mov byte ptr [ebp - 0x24], 0
004fa574 push ecx
004fa575 mov byte ptr [ebp - 4], 3
004fa579 lea eax, [ebp - 0x44]
004fa57c mov dword ptr [esp], 0x3dcccccd
004fa583 mov ecx, edi
004fa585 push eax
004fa586 lea eax, [ebp - 0x2c]
004fa589 push eax
004fa58a call 0x6980a0
004fa58f mov byte ptr [ebp - 4], 2
004fa593 mov edx, dword ptr [ebp - 0x18]
004fa596 cmp edx, 0x10
004fa599 jb 0x4fa5c3
004fa59b mov ecx, dword ptr [ebp - 0x2c]
004fa59e inc edx
004fa59f mov eax, ecx
004fa5a1 cmp edx, 0x1000
004fa5a7 jb 0x4fa5b9
004fa5a9 mov ecx, dword ptr [ecx - 4]
004fa5ac add edx, 0x23
004fa5af sub eax, ecx
004fa5b1 add eax, -4
004fa5b4 cmp eax, 0x1f
004fa5b7 ja 0x4fa602
004fa5b9 push edx
004fa5ba push ecx
004fa5bb call 0x9eb08e
004fa5c0 add esp, 8
004fa5c3 mov dword ptr [ebp - 4], 0xffffffff
004fa5ca mov edx, dword ptr [ebp - 0x30]
004fa5cd mov dword ptr [ebp - 0x1c], 0
004fa5d4 mov dword ptr [ebp - 0x18], 0xf
004fa5db mov byte ptr [ebp - 0x2c], 0
004fa5df cmp edx, 0x10
004fa5e2 jb 0x4fa612
004fa5e4 mov ecx, dword ptr [ebp - 0x44]
004fa5e7 inc edx
004fa5e8 mov eax, ecx
004fa5ea cmp edx, 0x1000
004fa5f0 jb 0x4fa608
004fa5f2 mov ecx, dword ptr [ecx - 4]
004fa5f5 add edx, 0x23
004fa5f8 sub eax, ecx
004fa5fa add eax, -4
004fa5fd cmp eax, 0x1f
004fa600 jbe 0x4fa608
004fa602 call dword ptr [0xa065ac]
004fa608 push edx
004fa609 push ecx
004fa60a call 0x9eb08e
004fa60f add esp, 8
004fa612 push 0xb400ac
004fa617 lea ecx, [edi + 0x8c]
004fa61d call 0x405e90
004fa622 test al, al
004fa624 je 0x4fa930
004fa62a push ecx
004fa62b mov dword ptr [esp], 0x3f800000
004fa632 xor eax, eax
004fa634 cmp dword ptr [edi + 0x28], 0xcd
004fa63b push 0
004fa63d push 2
004fa63f push ecx
004fa640 sete al
004fa643 mov dword ptr [esp], 0x3f800000
004fa64a add eax, 0x9e
004fa64f mov ecx, edi
004fa651 push eax
004fa652 call 0x6ad720
004fa657 mov eax, dword ptr [edi + 0x28]
004fa65a cmp eax, 0x16
004fa65d jne 0x4fa868
004fa663 mov eax, dword ptr [edi + 0x2c]
004fa666 cmp eax, 1
004fa669 jne 0x4fa6b4
004fa66b call 0x6c3d90
004fa670 mov ecx, dword ptr [0xbfd65c]
004fa676 push eax
004fa677 push 0
004fa679 push edi
004fa67a push 0xc02fec
004fa67f lea eax, [edi + 0x294]
004fa685 push eax
004fa686 push 1
004fa688 push 0x17
004fa68a call 0x422e20
004fa68f movss xmm0, dword ptr [eax + 0x2dc]
004fa697 mulss xmm0, dword ptr [0xb6a480]
004fa69f movss dword ptr [eax + 0x2dc], xmm0
004fa6a7 movss dword ptr [eax + 0x2d8], xmm0
004fa6af jmp 0x4fa91d
004fa6b4 cmp eax, 2
004fa6b7 jne 0x4fa787
004fa6bd cmp byte ptr [edi + 0x13c], 0
004fa6c4 je 0x4fa6d0
004fa6c6 movss xmm0, dword ptr [0xb6aeac]
004fa6ce jmp 0x4fa6d8
004fa6d0 movss xmm0, dword ptr [0xb6a940]
004fa6d8 movss dword ptr [ebp - 0x78], xmm0
004fa6dd mov dword ptr [ebp - 0x74], 0
004fa6e4 call 0x6c3d90
004fa6e9 addss xmm0, dword ptr [edi + 0x294]
004fa6f1 mov ecx, dword ptr [0xbfd65c]
004fa6f7 push eax
004fa6f8 push 1
004fa6fa push edi
004fa6fb movss dword ptr [ebp - 0x70], xmm0
004fa700 lea eax, [ebp - 0x78]
004fa703 movss xmm0, dword ptr [edi + 0x298]
004fa70b addss xmm0, dword ptr [0xb6a18c]
004fa713 push eax
004fa714 lea eax, [ebp - 0x70]
004fa717 push eax
004fa718 push 1
004fa71a push 0x26
004fa71c movss dword ptr [ebp - 0x6c], xmm0
004fa721 call 0x422e20
004fa726 mov ecx, dword ptr [eax + 0x164]
004fa72c and dword ptr [eax + 0x160], 0xfffffffb
004fa733 mov dword ptr [eax + 0x164], ecx
004fa739 lea eax, [ebp - 0x78]
004fa73c movss xmm1, dword ptr [edi + 0xb88]
004fa744 lea ecx, [ebp - 0x58]
004fa747 movaps xmm0, xmm1
004fa74a mulss xmm1, dword ptr [0xb6aee4]
004fa752 push eax
004fa753 mulss xmm0, dword ptr [0xb6a18c]
004fa75b movss dword ptr [ebp - 0x6c], xmm1
004fa760 movss dword ptr [ebp - 0x70], xmm0
004fa765 call 0x402120
004fa76a push eax
004fa76b lea eax, [ebp - 0x70]
004fa76e mov ecx, 2
004fa773 push eax
004fa774 lea edx, [edi + 0x294]
004fa77a call 0x6aead0
004fa77f add esp, 0xc
004fa782 jmp 0x4fa930
004fa787 cmp eax, 3
004fa78a jne 0x4fa8cb
004fa790 xor esi, esi
004fa792 mov dword ptr [ebp - 0x60], 6
004fa799 nop dword ptr [eax]
004fa7a0 call 0x6c3d90
004fa7a5 mov ecx, dword ptr [0xbfd65c]
004fa7ab push eax
004fa7ac push 1
004fa7ae push edi
004fa7af push 0xc02fec
004fa7b4 lea eax, [edi + 0x294]
004fa7ba push eax
004fa7bb push 0
004fa7bd push 0xde
004fa7c2 call 0x422e20
004fa7c7 mov ecx, dword ptr [eax + 0x314]
004fa7cd test esi, esi
004fa7cf mov dword ptr [ebp - 0x5c], eax
004fa7d2 cmove esi, eax
004fa7d5 add eax, 0x314
004fa7da mov dword ptr [ebp - 0x6c], eax
004fa7dd test ecx, ecx
004fa7df je 0x4fa7f6
004fa7e1 mov dword ptr [ebp - 0x74], eax
004fa7e4 add ecx, 0x324
004fa7ea lea eax, [ebp - 0x74]
004fa7ed push eax
004fa7ee call 0x4bc3c0
004fa7f3 mov eax, dword ptr [ebp - 0x6c]
004fa7f6 mov dword ptr [eax], esi
004fa7f8 test esi, esi
004fa7fa je 0x4fa804
004fa7fc push eax
004fa7fd mov ecx, esi
004fa7ff call 0x4bae70
004fa804 mov ecx, dword ptr [ebp - 0x5c]
004fa807 mov eax, dword ptr [ecx + 0x164]
004fa80d and dword ptr [ecx + 0x160], 0xfffffffb
004fa814 mov dword ptr [ecx + 0x164], eax
004fa81a call 0x6c3d90
004fa81f xor edx, edx
004fa821 mov ecx, 0x64
004fa826 div ecx
004fa828 mov eax, dword ptr [ebp - 0x5c]
004fa82b add edx, 0xc8
004fa831 movd xmm0, edx
004fa835 cvtdq2pd xmm0, xmm0
004fa839 shr edx, 0x1f
004fa83c sub dword ptr [ebp - 0x60], 1
004fa840 addsd xmm0, qword ptr [edx*8 + 0xb6c940]
004fa849 cvtpd2ps xmm0, xmm0
004fa84d addss xmm0, dword ptr [eax + 0x2d8]
004fa855 movss dword ptr [eax + 0x2d8], xmm0
004fa85d jne 0x4fa7a0
004fa863 jmp 0x4fa930
004fa868 cmp eax, 0x331
004fa86d jne 0x4fa8cb
004fa86f cmp dword ptr [edi + 0x2c], 1
004fa873 lea esi, [edi + 0x294]
004fa879 jne 0x4fa893
004fa87b call 0x6c3d90
004fa880 push eax
004fa881 push 0
004fa883 push edi
004fa884 push 0xc02fec
004fa889 push esi
004fa88a push 0
004fa88c push 0x328
004fa891 jmp 0x4fa8a9
004fa893 call 0x6c3d90
004fa898 push eax
004fa899 push 0
004fa89b push edi
004fa89c push 0xc02fec
004fa8a1 push esi
004fa8a2 push 0
004fa8a4 push 0x32a
004fa8a9 mov ecx, dword ptr [0xbfd65c]
004fa8af call 0x422e20
004fa8b4 mov ecx, eax
004fa8b6 mov eax, dword ptr [ecx + 0x164]
004fa8bc and dword ptr [ecx + 0x160], 0xfffffffb
004fa8c3 mov dword ptr [ecx + 0x164], eax
004fa8c9 jmp 0x4fa930
004fa8cb call 0x6c3d90
004fa8d0 cmp dword ptr [edi + 0x28], 0x16
004fa8d4 mov ecx, 0x12
004fa8d9 push 0
004fa8db push 0xbeab70
004fa8e0 push 0xbeab18
004fa8e5 push 0
004fa8e7 push eax
004fa8e8 push 0
004fa8ea push edi
004fa8eb push 0xc02fec
004fa8f0 lea eax, [edi + 0x294]
004fa8f6 push eax
004fa8f7 mov eax, 0x55
004fa8fc cmove eax, ecx
004fa8ff mov ecx, dword ptr [0xbfd65c]
004fa905 push 0
004fa907 push eax
004fa908 call 0x422e20
004fa90d push eax
004fa90e call 0x9ec34c
004fa913 add esp, 0x14
004fa916 mov byte ptr [eax + 0x16c], 1
004fa91d mov ecx, dword ptr [eax + 0x164]
004fa923 mov dword ptr [eax + 0x164], ecx
004fa929 and dword ptr [eax + 0x160], 0xfffffffb
004fa930 cmp dword ptr [edi + 0x90], 0
004fa937 je 0x4fa942
004fa939 cmp byte ptr [edi + 0xa0], 0
004fa940 jne 0x4fa94c
004fa942 mov dword ptr [edi + 0xab4], 4
004fa94c mov ecx, edi
004fa94e call 0x6ad7a0
004fa953 cmp dword ptr [edi + 0x28], 0x16
004fa957 mov esi, eax
004fa959 mov dword ptr [ebp - 0x74], 5
004fa960 jne 0x4fa9d5
004fa962 cmp dword ptr [edi + 0x2c], 3
004fa966 jne 0x4fa9d5
004fa968 push 0
004fa96a push 1
004fa96c push -1
004fa96e push -1
004fa970 push 0xde
004fa975 lea eax, [ebp - 0x24]
004fa978 push eax
004fa979 mov eax, dword ptr [0xbfd65c]
004fa97e mov ecx, dword ptr [eax + 0x18190]
004fa984 add ecx, 0x1218
004fa98a call 0x415ed0
004fa98f xor ecx, ecx
004fa991 cmp dword ptr [ebp - 0x18], ecx
004fa994 jbe 0x4fa9c4
004fa996 mov edi, dword ptr [ebp - 0x20]
004fa999 nop dword ptr [eax]
004fa9a0 mov eax, dword ptr [edi + ecx*4]
004fa9a3 cmp dword ptr [eax + 0x314], eax
004fa9a9 je 0x4fa9bb
004fa9ab mov eax, dword ptr [eax + 0x344]
004fa9b1 xor edx, edx
004fa9b3 div dword ptr [ebp - 0x74]
004fa9b6 test edx, edx
004fa9b8 jne 0x4fa9bb
004fa9ba dec esi
004fa9bb inc ecx
004fa9bc cmp ecx, dword ptr [ebp - 0x18]
004fa9bf jb 0x4fa9a0
004fa9c1 mov edi, dword ptr [ebp - 0x64]
004fa9c4 cmp byte ptr [ebp - 0x24], 0
004fa9c8 jne 0x4fa9d5
004fa9ca push dword ptr [ebp - 0x20]
004fa9cd call 0x9eace5
004fa9d2 add esp, 4
004fa9d5 movss xmm0, dword ptr [edi + 0xb00]
004fa9dd xorps xmm1, xmm1
004fa9e0 subss xmm0, dword ptr [edi + 0x2f4]
004fa9e8 comiss xmm1, xmm0
004fa9eb jb 0x4faa3b
004fa9ed call 0x6c3d90
004fa9f2 xor edx, edx
004fa9f4 mov ecx, 5
004fa9f9 div ecx
004fa9fb add edx, 4
004fa9fe cmp esi, edx
004faa00 jl 0x4faa3b
004faa02 call 0x6c3d90
004faa07 xor edx, edx
004faa09 mov ecx, 0x32
004faa0e div ecx
004faa10 add edx, 0x14
004faa13 movd xmm0, edx
004faa17 cvtdq2pd xmm0, xmm0
004faa1b shr edx, 0x1f
004faa1e addsd xmm0, qword ptr [edx*8 + 0xb6c940]
004faa27 cvtpd2ps xmm0, xmm0
004faa2b addss xmm0, dword ptr [edi + 0xb00]
004faa33 movss dword ptr [edi + 0xb00], xmm0
004faa3b cmp dword ptr [edi + 0xaa0], 0
004faa42 jg 0x4faa51
004faa44 cmp dword ptr [edi + 0xe6c], -1
004faa4b je 0x4faccb
004faa51 movss xmm0, dword ptr [edi + 0xb00]
004faa59 comiss xmm1, xmm0
004faa5c jb 0x4facbb
004faa62 mov ecx, edi
004faa64 call 0x695680
004faa69 lea esi, [edi + 0x294]
004faa6f movss xmm2, dword ptr [eax + 0x294]
004faa77 subss xmm2, dword ptr [esi]
004faa7b movss xmm0, dword ptr [eax + 0x298]
004faa83 subss xmm0, dword ptr [esi + 4]
004faa88 movaps xmm1, xmm2
004faa8b movss dword ptr [ebp - 0x5c], xmm2
004faa90 mulss xmm1, xmm2
004faa94 mulss xmm0, xmm0
004faa98 addss xmm0, xmm1
004faa9c call 0x4228c0
004faaa1 cmp dword ptr [edi + 0xe6c], -1
004faaa8 movaps xmm1, xmm0
004faaab je 0x4faafc
004faaad movss xmm2, dword ptr [0xb6a2cc]
004faab5 lea eax, [ebp - 0x1c]
004faab8 push eax
004faab9 mov ecx, edi
004faabb call 0x6af380
004faac0 mov ecx, eax
004faac2 movss xmm0, dword ptr [ecx]
004faac6 ucomiss xmm0, dword ptr [0xc02fec]
004faacd lahf 
004faace test ah, 0x44
004faad1 jp 0x4faaef
004faad3 movss xmm0, dword ptr [ecx + 4]
004faad8 ucomiss xmm0, dword ptr [0xc02ff0]
004faadf lahf 
004faae0 test ah, 0x44
004faae3 jp 0x4faaef
004faae5 mov ecx, dword ptr [edi + 0xe6c]
004faaeb xor eax, eax
004faaed jmp 0x4fab0f
004faaef mov ecx, dword ptr [edi + 0xe6c]
004faaf5 mov eax, 1
004faafa jmp 0x4fab0f
004faafc movss xmm0, dword ptr [0xb6ac14]
004fab04 xor eax, eax
004fab06 comiss xmm0, xmm1
004fab09 seta al
004fab0c or ecx, 0xffffffff
004fab0f test eax, eax
004fab11 je 0x4facaf
004fab17 mov eax, dword ptr [edi + 0x160]
004fab1d and eax, 0x1000a00
004fab22 or eax, 0
004fab25 jne 0x4facaf
004fab2b cmp ecx, -1
004fab2e jne 0x4fab7c
004fab30 mov ecx, edi
004fab32 call 0x695680
004fab37 push 0
004fab39 push 0
004fab3b push 0
004fab3d mov ecx, dword ptr [eax + 0x294]
004fab43 mov eax, dword ptr [eax + 0x298]
004fab49 push 0
004fab4b mov dword ptr [ebp - 0x68], ecx
004fab4e mov ecx, dword ptr [0xbfd65c]
004fab54 push 2
004fab56 mov dword ptr [ebp - 0x64], eax
004fab59 lea eax, [ebp - 0x68]
004fab5c push esi
004fab5d mov ecx, dword ptr [ecx + 0x18190]
004fab63 push eax
004fab64 call 0x7af4b0
004fab69 test al, al
004fab6b jne 0x4fab7c
004fab6d mov dword ptr [edi + 0xb00], 0x40e00000
004fab77 jmp 0x4faccb
004fab7c movss xmm1, dword ptr [0xb6aac4]
004fab84 mov dword ptr [edi + 0xb00], 0x42960000
004fab8e cmp dword ptr [edi + 0x28], 0xcd
004fab95 jne 0x4fabe1
004fab97 cmp dword ptr [edi + 0xe6c], -1
004fab9e je 0x4faba4
004faba0 xor edx, edx
004faba2 jmp 0x4fabba
004faba4 call 0x6c3d90
004faba9 movss xmm1, dword ptr [edi + 0xb00]
004fabb1 xor edx, edx
004fabb3 mov ecx, 0x14
004fabb8 div ecx
004fabba lea eax, [edx + 0x37]
004fabbd movd xmm0, eax
004fabc1 cvtdq2pd xmm0, xmm0
004fabc5 shr eax, 0x1f
004fabc8 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
004fabd1 cvtpd2ps xmm0, xmm0
004fabd5 addss xmm0, xmm1
004fabd9 movss dword ptr [edi + 0xb00], xmm0
004fabe1 cmp dword ptr [edi + 0x28], 0x16
004fabe5 jne 0x4fabf7
004fabe7 cmp dword ptr [edi + 0x2c], 3
004fabeb jne 0x4fabf7
004fabed mov dword ptr [edi + 0xb00], 0x43520000
004fabf7 cmp dword ptr [edi + 0xe6c], -1
004fabfe jne 0x4fac1a
004fac00 movss xmm0, dword ptr [0xc02fec]
004fac08 movss dword ptr [edi + 0xe70], xmm0
004fac10 movss xmm0, dword ptr [0xc02ff0]
004fac18 jmp 0x4fac3f
004fac1a movss xmm2, dword ptr [0xb6a2cc]
004fac22 lea eax, [ebp - 0x68]
004fac25 push eax
004fac26 mov ecx, edi
004fac28 call 0x6af380
004fac2d movss xmm0, dword ptr [ebp - 0x68]
004fac32 movss dword ptr [edi + 0xe70], xmm0
004fac3a movss xmm0, dword ptr [ebp - 0x64]
004fac3f movss dword ptr [edi + 0xe74], xmm0
004fac47 movss xmm1, dword ptr [edi + 0xe70]
004fac4f ucomiss xmm1, dword ptr [0xc02fec]
004fac56 lahf 
004fac57 test ah, 0x44
004fac5a jp 0x4fac69
004fac5c ucomiss xmm0, dword ptr [0xc02ff0]
004fac63 lahf 
004fac64 test ah, 0x44
004fac67 jnp 0x4fac6e
004fac69 movss dword ptr [ebp - 0x5c], xmm1
004fac6e push 1
004fac70 push 0xb41234
004fac75 lea ecx, [edi + 0x3c]
004fac78 call 0x405bb0
004fac7d test al, al
004fac7f je 0x4fac93
004fac81 lea ecx, [edi + 0x8c]
004fac87 call 0x405330
004fac8c mov byte ptr [edi + 0xa0], 1
004fac93 xorps xmm0, xmm0
004fac96 mov dword ptr [edi + 0xab4], 8
004faca0 comiss xmm0, dword ptr [ebp - 0x5c]
004faca4 seta al
004faca7 mov byte ptr [edi + 0x13c], al
004facad jmp 0x4faccb
004facaf mov dword ptr [edi + 0xb00], 0x40400000
004facb9 jmp 0x4faccb
004facbb subss xmm0, dword ptr [edi + 0x2f4]
004facc3 movss dword ptr [edi + 0xb00], xmm0
004faccb cmp byte ptr [edi + 0x16b], 0
004facd2 je 0x4fb194
004facd8 movss xmm0, dword ptr [edi + 0x2d8]
004face0 comiss xmm0, dword ptr [0xb6aee4]
004face7 jbe 0x4fb194
004faced mov ecx, edi
004facef call 0x6ad7a0
004facf4 movss xmm0, dword ptr [0xb6a8cc]
004facfc sub esp, 8
004facff movd xmm1, eax
004fad03 cvtdq2ps xmm1, xmm1
004fad06 mulss xmm1, dword ptr [0xb6a350]
004fad0e addss xmm1, dword ptr [0xb6a614]
004fad16 divss xmm0, xmm1
004fad1a movss dword ptr [ebp - 0x64], xmm0
004fad1f fld dword ptr [ebp - 0x64]
004fad22 fstp qword ptr [esp]
004fad25 call 0x9ec3ac
004fad2a mov eax, dword ptr [edi + 0x28]
004fad2d add esp, 8
004fad30 fstp dword ptr [ebp - 0x64]
004fad33 fld dword ptr [ebp - 0x64]
004fad36 fstp dword ptr [ebp - 0x64]
004fad39 cvttss2si esi, dword ptr [ebp - 0x64]
004fad3e cmp eax, 0x16
004fad41 jne 0x4fad6a
004fad43 mov eax, dword ptr [edi + 0x2c]
004fad46 cmp eax, 1
004fad49 je 0x4fad5a
004fad4b cmp eax, 2
004fad4e je 0x4fad5a
004fad50 cmp eax, 3
004fad53 jne 0x4fad8c
004fad55 lea esi, [eax - 2]
004fad58 jmp 0x4fad8c
004fad5a call 0x6c3d90
004fad5f and eax, 1
004fad62 inc eax
004fad63 cmp eax, esi
004fad65 cmovl esi, eax
004fad68 jmp 0x4fad8c
004fad6a cmp eax, 0xcd
004fad6f jne 0x4fad78
004fad71 mov esi, 1
004fad76 jmp 0x4fad8c
004fad78 cmp eax, 0x331
004fad7d jne 0x4fad8c
004fad7f lea eax, [esi - 1]
004fad82 mov esi, 1
004fad87 cmp eax, esi
004fad89 cmovg esi, eax
004fad8c movsx eax, word ptr [edi + 0xbc6]
004fad93 xor ecx, ecx
004fad95 sub esi, eax
004fad97 test esi, esi
004fad99 cmovg ecx, esi
004fad9c mov dword ptr [ebp - 0x74], ecx
004fad9f test ecx, ecx
004fada1 jle 0x4fb194
004fada7 movss xmm2, dword ptr [0xb6a19c]
004fadaf mov esi, 0xe
004fadb4 movss xmm3, dword ptr [0xb6a874]
004fadbc nop dword ptr [eax]
004fadc0 mov eax, dword ptr [edi + 0x28]
004fadc3 mov dword ptr [ebp - 0x5c], 0
004fadca cmp eax, 0x16
004fadcd jne 0x4fb036
004fadd3 cmp dword ptr [edi + 0x2c], 3
004fadd7 jne 0x4faee0
004faddd mov dword ptr [ebp - 0x60], 0
004fade4 call 0x6c3d90
004fade9 movd xmm0, eax
004faded cvtdq2pd xmm0, xmm0
004fadf1 shr eax, 0x1f
004fadf4 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
004fadfd cvtpd2ps xmm0, xmm0
004fae01 mulss xmm0, xmm2
004fae05 mulss xmm0, dword ptr [0xb6a974]
004fae0d addss xmm0, dword ptr [0xb6a8f4]
004fae15 movss dword ptr [ebp - 0x5c], xmm0
004fae1a call 0x6c3d90
004fae1f mov esi, eax
004fae21 call 0x6c3d90
004fae26 movd xmm0, eax
004fae2a cvtdq2pd xmm0, xmm0
004fae2e shr eax, 0x1f
004fae31 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
004fae3a cvtpd2ps xmm0, xmm0
004fae3e mulss xmm0, xmm2
004fae42 mulss xmm0, xmm3
004fae46 addss xmm0, xmm0
004fae4a movss dword ptr [ebp - 0x64], xmm0
004fae4f call 0x411fe0
004fae54 mulss xmm0, dword ptr [ebp - 0x5c]
004fae59 addss xmm0, dword ptr [edi + 0x294]
004fae61 movss dword ptr [ebp - 0x80], xmm0
004fae66 movss xmm0, dword ptr [ebp - 0x64]
004fae6b call 0x412010
004fae70 mulss xmm0, dword ptr [ebp - 0x5c]
004fae75 lea eax, [ebp - 0x80]
004fae78 mov ecx, dword ptr [0xbfd65c]
004fae7e push esi
004fae7f mov esi, dword ptr [ebp - 0x60]
004fae82 addss xmm0, dword ptr [edi + 0x298]
004fae8a push 0
004fae8c push edi
004fae8d push 0xc02fec
004fae92 push eax
004fae93 push dword ptr [esi + 0xb42be4]
004fae99 movss dword ptr [ebp - 0x7c], xmm0
004fae9e push dword ptr [esi + 0xb42be0]
004faea4 call 0x422e20
004faea9 movss xmm2, dword ptr [0xb6a19c]
004faeb1 add esi, 8
004faeb4 movss xmm3, dword ptr [0xb6a874]
004faebc mov dword ptr [ebp - 0x60], esi
004faebf and dword ptr [eax + 0x160], 0xfffffffb
004faec6 mov ecx, dword ptr [eax + 0x164]
004faecc mov dword ptr [eax + 0x164], ecx
004faed2 cmp esi, 0x68
004faed5 jb 0x4fade4
004faedb jmp 0x4fb175
004faee0 call 0x6c3d90
004faee5 xor edx, edx
004faee7 mov ecx, 0xb
004faeec div ecx
004faeee lea eax, [ecx + 2]
004faef1 cmp edx, 7
004faef4 jbe 0x4faeff
004faef6 mov dword ptr [ebp - 0x60], 0x12
004faefd jmp 0x4faf05
004faeff cmove eax, esi
004faf02 mov dword ptr [ebp - 0x60], eax
004faf05 mov eax, dword ptr [edi + 0x2c]
004faf08 cmp eax, 1
004faf0b jne 0x4faf19
004faf0d mov dword ptr [ebp - 0x60], 0x17
004faf14 mov dword ptr [ebp - 0x5c], eax
004faf17 jmp 0x4faf2c
004faf19 cmp eax, 2
004faf1c jne 0x4faf2c
004faf1e mov dword ptr [ebp - 0x60], 0x4d
004faf25 mov dword ptr [ebp - 0x5c], 0
004faf2c call 0x6c3d90
004faf31 movd xmm0, eax
004faf35 cvtdq2pd xmm0, xmm0
004faf39 shr eax, 0x1f
004faf3c addsd xmm0, qword ptr [eax*8 + 0xb6c940]
004faf45 cvtpd2ps xmm1, xmm0
004faf49 mulss xmm1, xmm2
004faf4d mulss xmm1, xmm3
004faf51 addss xmm1, xmm1
004faf55 movss dword ptr [ebp - 0x64], xmm1
004faf5a call 0x6c3d90
004faf5f movd xmm0, eax
004faf63 cvtdq2pd xmm0, xmm0
004faf67 shr eax, 0x1f
004faf6a addsd xmm0, qword ptr [eax*8 + 0xb6c940]
004faf73 cvtpd2ps xmm0, xmm0
004faf77 mulss xmm0, xmm2
004faf7b mulss xmm0, dword ptr [0xb6a910]
004faf83 maxss xmm0, dword ptr [0xb6a7b0]
004faf8b movss dword ptr [ebp - 0x6c], xmm0
004faf90 call 0x6c3d90
004faf95 movaps xmm0, xmm1
004faf98 mov esi, eax
004faf9a call 0x411fe0
004faf9f mulss xmm0, dword ptr [ebp - 0x6c]
004fafa4 addss xmm0, dword ptr [edi + 0x294]
004fafac movss dword ptr [ebp - 0x88], xmm0
004fafb4 movss xmm0, dword ptr [ebp - 0x64]
004fafb9 call 0x412010
004fafbe mulss xmm0, dword ptr [ebp - 0x6c]
004fafc3 lea eax, [ebp - 0x88]
004fafc9 mov ecx, dword ptr [0xbfd65c]
004fafcf push esi
004fafd0 push 0
004fafd2 addss xmm0, dword ptr [edi + 0x298]
004fafda push edi
004fafdb push 0xc02fec
004fafe0 push eax
004fafe1 push dword ptr [ebp - 0x5c]
004fafe4 movss dword ptr [ebp - 0x84], xmm0
004fafec push dword ptr [ebp - 0x60]
004fafef call 0x422e20
004faff4 mov ecx, dword ptr [eax + 0x164]
004faffa and dword ptr [eax + 0x160], 0xfffffffb
004fb001 mov dword ptr [eax + 0x164], ecx
004fb007 cmp dword ptr [edi + 0x2c], 1
004fb00b jne 0x4fb175
004fb011 movss xmm0, dword ptr [eax + 0x2dc]
004fb019 mulss xmm0, dword ptr [0xb6a480]
004fb021 movss dword ptr [eax + 0x2dc], xmm0
004fb029 movss dword ptr [eax + 0x2d8], xmm0
004fb031 jmp 0x4fb175
004fb036 lea esi, [edi + 0x294]
004fb03c cmp eax, 0x331
004fb041 jne 0x4fb127
004fb047 cmp dword ptr [edi + 0x2c], 1
004fb04b jne 0x4fb068
004fb04d call 0x6c3d90
004fb052 push eax
004fb053 push 0
004fb055 push edi
004fb056 push 0xc02fec
004fb05b push esi
004fb05c push 0
004fb05e push 0x328
004fb063 jmp 0x4fb157
004fb068 call 0x6c3d90
004fb06d movd xmm0, eax
004fb071 cvtdq2pd xmm0, xmm0
004fb075 shr eax, 0x1f
004fb078 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
004fb081 mov eax, dword ptr [0xbfd65c]
004fb086 mov ecx, dword ptr [eax + 0x18190]
004fb08c cvtpd2ps xmm0, xmm0
004fb090 mulss xmm0, xmm2
004fb094 mulss xmm0, xmm3
004fb098 addss xmm0, xmm0
004fb09c movss dword ptr [ebp - 0x6c], xmm0
004fb0a1 movss xmm0, dword ptr [ecx + 0x7134]
004fb0a9 comiss xmm0, dword ptr [0xb6a18c]
004fb0b0 seta al
004fb0b3 movzx eax, al
004fb0b6 push eax
004fb0b7 push 1
004fb0b9 push ecx
004fb0ba mov dword ptr [esp], 0x42a00000
004fb0c1 lea eax, [ebp - 0x90]
004fb0c7 push esi
004fb0c8 push eax
004fb0c9 call 0x7cf240
004fb0ce movss xmm0, dword ptr [ebp - 0x6c]
004fb0d3 mov esi, eax
004fb0d5 call 0x411fe0
004fb0da mulss xmm0, dword ptr [0xb6a974]
004fb0e2 addss xmm0, dword ptr [esi]
004fb0e6 movss dword ptr [ebp - 0x1c], xmm0
004fb0eb movss xmm0, dword ptr [ebp - 0x6c]
004fb0f0 call 0x412010
004fb0f5 mulss xmm0, dword ptr [0xb6a974]
004fb0fd lea eax, [ebp - 0x1c]
004fb100 lea ecx, [edi + 0x294]
004fb106 mov edx, edi
004fb108 movss xmm2, dword ptr [0xb6aeb8]
004fb110 push 0
004fb112 addss xmm0, dword ptr [esi + 4]
004fb117 push eax
004fb118 movss dword ptr [ebp - 0x18], xmm0
004fb11d call 0x549d70
004fb122 add esp, 8
004fb125 jmp 0x4fb175
004fb127 call 0x6c3d90
004fb12c mov esi, eax
004fb12e and esi, 1
004fb131 call 0x6c3d90
004fb136 push eax
004fb137 push 0
004fb139 push edi
004fb13a push 0xc02fec
004fb13f lea eax, [edi + 0x294]
004fb145 test esi, esi
004fb147 push eax
004fb148 mov eax, 0x5e
004fb14d mov ecx, 0x1d
004fb152 push esi
004fb153 cmovne eax, ecx
004fb156 push eax
004fb157 mov ecx, dword ptr [0xbfd65c]
004fb15d call 0x422e20
004fb162 mov ecx, dword ptr [eax + 0x164]
004fb168 mov dword ptr [eax + 0x164], ecx
004fb16e and dword ptr [eax + 0x160], 0xfffffffb
004fb175 sub dword ptr [ebp - 0x74], 1
004fb179 mov esi, 0xe
004fb17e movss xmm2, dword ptr [0xb6a19c]
004fb186 movss xmm3, dword ptr [0xb6a874]
004fb18e jne 0x4fadc0
004fb194 cmp dword ptr [edi + 0xe6c], -1
004fb19b je 0x4fb1a7
004fb19d mov dword ptr [edi + 0x2c4], 0x3f800000
004fb1a7 mov ecx, dword ptr [ebp - 0xc]
004fb1aa mov dword ptr fs:[0], ecx
004fb1b1 pop ecx
004fb1b2 pop edi
004fb1b3 pop esi
004fb1b4 mov ecx, dword ptr [ebp - 0x14]
004fb1b7 xor ecx, ebp
004fb1b9 call 0x9eacd7
004fb1be mov esp, ebp
004fb1c0 pop ebp
004fb1c1 mov esp, ebx
004fb1c3 pop ebx
004fb1c4 ret 
