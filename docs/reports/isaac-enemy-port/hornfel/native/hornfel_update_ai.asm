; Installed Repentance 1.7.9b. Address-bounded linear decode; helper names are unresolved.
; Literal float/string comments describe bytes, not inferred native field meanings.
004a6280 push ebx
004a6281 mov ebx, esp
004a6283 sub esp, 8
004a6286 and esp, 0xfffffff8
004a6289 add esp, 4
004a628c push ebp
004a628d mov ebp, dword ptr [ebx + 4]
004a6290 mov dword ptr [esp + 4], ebp
004a6294 mov ebp, esp
004a6296 push -1
004a6298 push 0x9ee60d
004a629d mov eax, dword ptr fs:[0]
004a62a3 push eax
004a62a4 push ebx
004a62a5 sub esp, 0x138
004a62ab mov eax, dword ptr [0xbaa3b4] ; [0xbaa3b4] f32=-0.00294341473
004a62b0 xor eax, ebp
004a62b2 mov dword ptr [ebp - 0x14], eax
004a62b5 push esi
004a62b6 push edi
004a62b7 push eax
004a62b8 lea eax, [ebp - 0xc]
004a62bb mov dword ptr fs:[0], eax
004a62c1 mov edi, ecx
004a62c3 mov dword ptr [ebp - 0xf0], edi
004a62c9 mov eax, dword ptr [0xbfd65c]
004a62ce xorps xmm3, xmm3
004a62d1 mov ecx, dword ptr [edi + 0x32c]
004a62d7 mov dword ptr [ebp - 0x120], ecx
004a62dd mov esi, dword ptr [eax + 0x18190]
004a62e3 mov eax, dword ptr [edi + 0xab4]
004a62e9 mov dword ptr [ebp - 0x11c], esi
004a62ef cmp eax, 0x10
004a62f2 ja 0x4a79e8
004a62f8 jmp dword ptr [eax*4 + 0x4a7fb4]
004a62ff cmp dword ptr [edi + 0x2c], 0
004a6303 jne 0x4a63b8
004a6309 push 0x98
004a630e push 0x3e8
004a6313 lea eax, [ebp - 0x24]
004a6316 mov ecx, edi
004a6318 push eax
004a6319 call 0x6a6db0
004a631e mov dword ptr [ebp - 4], 0
004a6325 cmp dword ptr [ebp - 0x18], 0
004a6329 jne 0x4a635f
004a632b call 0x6c3d90
004a6330 mov ecx, dword ptr [0xbfd65c]
004a6336 push eax
004a6337 push 0
004a6339 push 0
004a633b push 0xc02fec
004a6340 push 0xc02fec
004a6345 push 0x98
004a634a push 0x3e8
004a634f call 0x422e20
004a6354 mov esi, eax
004a6356 mov ecx, esi
004a6358 mov edx, dword ptr [esi]
004a635a call dword ptr [edx + 0xc]
004a635d jmp 0x4a6364
004a635f mov esi, dword ptr [ebp - 0x20]
004a6362 mov esi, dword ptr [esi]
004a6364 mov ecx, dword ptr [edi + 0x314]
004a636a lea eax, [edi + 0x314]
004a6370 test ecx, ecx
004a6372 je 0x4a6392
004a6374 mov dword ptr [ebp - 0xec], eax
004a637a add ecx, 0x324
004a6380 lea eax, [ebp - 0xec]
004a6386 push eax
004a6387 call 0x4bc3c0
004a638c lea eax, [edi + 0x314]
004a6392 mov dword ptr [eax], esi
004a6394 test esi, esi
004a6396 je 0x4a63a0
004a6398 push eax
004a6399 mov ecx, esi
004a639b call 0x4bae70
004a63a0 mov dword ptr [ebp - 4], 0xffffffff
004a63a7 cmp byte ptr [ebp - 0x24], 0
004a63ab jne 0x4a63b8
004a63ad push dword ptr [ebp - 0x20]
004a63b0 call 0x9eace5
004a63b5 add esp, 4
004a63b8 mov eax, dword ptr [edi + 0x164]
004a63be and dword ptr [edi + 0x160], 0xfffffffb
004a63c5 mov dword ptr [edi + 0x164], eax
004a63cb cmp dword ptr [edi + 0xbc], 3
004a63d2 jg 0x4a63f2
004a63d4 cmp dword ptr [edi + 0x50], 0x10
004a63d8 lea eax, [edi + 0x3c]
004a63db jb 0x4a63e0
004a63dd mov eax, dword ptr [edi + 0x3c]
004a63e0 push 3
004a63e2 push eax
004a63e3 push 0xa0830c
004a63e8 push 3
004a63ea call 0x95e330
004a63ef add esp, 0x10
004a63f2 mov eax, dword ptr [edi + 0xb8]
004a63f8 mov byte ptr [eax + 0x248], 0
004a63ff cmp dword ptr [edi + 0xbc], 4
004a6406 jg 0x4a6426
004a6408 cmp dword ptr [edi + 0x50], 0x10
004a640c lea eax, [edi + 0x3c]
004a640f jb 0x4a6414
004a6411 mov eax, dword ptr [edi + 0x3c]
004a6414 push 4
004a6416 push eax
004a6417 push 0xa0830c
004a641c push 3
004a641e call 0x95e330
004a6423 add esp, 0x10
004a6426 mov eax, dword ptr [edi + 0xb8]
004a642c lea esi, [edi + 0xb40]
004a6432 push 2
004a6434 mov ecx, esi
004a6436 mov byte ptr [eax + 0x2e4], 0
004a643d xor eax, eax
004a643f mov dword ptr [edi + 0x360], eax
004a6445 mov dword ptr [edi + 0xaf2], eax
004a644b mov byte ptr [edi + 0xaf6], al
004a6451 mov word ptr [edi + 0xaf0], ax
004a6458 call 0x43da10
004a645d mov edx, dword ptr [esi + 0xc]
004a6460 mov eax, edx
004a6462 mov ecx, dword ptr [esi + 8]
004a6465 and edx, 3
004a6468 shr eax, 2
004a646b dec ecx
004a646c and ecx, eax
004a646e mov eax, dword ptr [esi + 4]
004a6471 mov eax, dword ptr [eax + ecx*4]
004a6474 mov dword ptr [eax + edx*4], 0
004a647b mov eax, dword ptr [esi + 0xc]
004a647e mov ecx, dword ptr [esi + 8]
004a6481 mov dword ptr [ebp - 0xfc], eax
004a6487 dec ecx
004a6488 lea edx, [eax + 1]
004a648b mov eax, edx
004a648d and edx, 3
004a6490 shr eax, 2
004a6493 and ecx, eax
004a6495 mov eax, dword ptr [esi + 4]
004a6498 mov eax, dword ptr [eax + ecx*4]
004a649b mov dword ptr [eax + edx*4], 0
004a64a2 cmp dword ptr [edi + 0x2c], 1
004a64a6 jne 0x4a64d4
004a64a8 mov eax, dword ptr [edi + 0x164]
004a64ae or dword ptr [edi + 0x160], 0x140011
004a64b8 mov dword ptr [edi + 0xab4], 0x10
004a64c2 mov byte ptr [edi + 0x308], 1
004a64c9 mov dword ptr [edi + 0x164], eax
004a64cf jmp 0x4a79e8
004a64d4 mov esi, dword ptr [edi + 0x32c]
004a64da mov dword ptr [ebp - 0x120], esi
004a64e0 test esi, esi
004a64e2 jne 0x4a65ac
004a64e8 push 0xc02fec
004a64ed push 0xc02fec
004a64f2 mov ecx, edi
004a64f4 call 0x68eff0
004a64f9 mov dword ptr [ebp - 0x2c], 0
004a6500 mov esi, eax
004a6502 push 0x30
004a6504 mov dword ptr [ebp - 0x1c], 0
004a650b mov dword ptr [ebp - 0x18], 0xf
004a6512 mov byte ptr [ebp - 0x2c], 0
004a6516 call 0x407de0
004a651b movups xmm0, xmmword ptr [0xb41c38] ; [0xb41c38] f32=2.25918492e-10
004a6522 mov dword ptr [ebp - 0x1c], 0x21
004a6529 mov dword ptr [ebp - 0x18], 0x2f
004a6530 movups xmmword ptr [eax], xmm0
004a6533 movups xmm0, xmmword ptr [0xb41c48] ; [0xb41c48] f32=2.00235275e-19
004a653a movups xmmword ptr [eax + 0x10], xmm0
004a653e mov cl, byte ptr [0xb41c58] ; [0xb41c58] f32=7.00649232e-44
004a6544 mov byte ptr [eax + 0x20], cl
004a6547 mov byte ptr [eax + 0x21], 0
004a654b mov dword ptr [ebp - 0x2c], eax
004a654e push 1
004a6550 lea eax, [ebp - 0x2c]
004a6553 mov dword ptr [ebp - 4], 1
004a655a push eax
004a655b lea ecx, [esi + 0x3c]
004a655e call 0x407160
004a6563 mov dword ptr [ebp - 4], 0xffffffff
004a656a mov edx, dword ptr [ebp - 0x18]
004a656d cmp edx, 0x10
004a6570 jb 0x4a65a0
004a6572 mov ecx, dword ptr [ebp - 0x2c]
004a6575 inc edx
004a6576 mov eax, ecx
004a6578 cmp edx, 0x1000
004a657e jb 0x4a6596
004a6580 mov ecx, dword ptr [ecx - 4]
004a6583 add edx, 0x23
004a6586 sub eax, ecx
004a6588 add eax, -4
004a658b cmp eax, 0x1f
004a658e jbe 0x4a6596
004a6590 call dword ptr [0xa065ac] ; [0xa065ac] f32=1.12523062e-38
004a6596 push edx
004a6597 push ecx
004a6598 call 0x9eb08e
004a659d add esp, 8
004a65a0 mov eax, dword ptr [edi + 0x32c]
004a65a6 mov dword ptr [ebp - 0x120], eax
004a65ac mov ecx, edi
004a65ae call 0x4a5a10
004a65b3 mov word ptr [edi + 0xaf1], 0x1e1e
004a65bc jmp 0x4a79e8
004a65c1 push 0
004a65c3 push 0xb41d5c ; string='DecoyIdle'
004a65c8 lea ecx, [edi + 0x3c]
004a65cb call 0x4054f0
004a65d0 movss xmm0, dword ptr [edi + 0x14]
004a65d5 xorps xmm1, xmm1
004a65d8 comiss xmm0, xmm1
004a65db jbe 0x4a79e8
004a65e1 mov eax, dword ptr [edi + 0x18]
004a65e4 and eax, 4
004a65e7 or eax, 0
004a65ea je 0x4a6602
004a65ec mov dword ptr [edi + 0x2d8], 0x3f800000
004a65f6 mov byte ptr [edi + 0x16b], 1
004a65fd jmp 0x4a79e8
004a6602 mov esi, dword ptr [edi + 8]
004a6605 cmp esi, dword ptr [edi + 0xc]
004a6608 je 0x4a6692
004a660e movss xmm3, dword ptr [0xb6a7b0] ; [0xb6a7b0] f32=2
004a6616 movss xmm4, dword ptr [0xb6a864] ; [0xb6a864] f32=3
004a661e movss xmm5, dword ptr [0xb6a974] ; [0xb6a974] f32=10
004a6626 movss xmm0, dword ptr [esi]
004a662a comiss xmm5, xmm0
004a662d jb 0x4a665a
004a662f comiss xmm0, xmm1
004a6632 jbe 0x4a6650
004a6634 call 0x6c3d90
004a6639 xor edx, edx
004a663b mov ecx, 3
004a6640 div ecx
004a6642 test edx, edx
004a6644 je 0x4a666c
004a6646 movss xmm0, dword ptr [0xb6a614] ; [0xb6a614] f32=1
004a664e jmp 0x4a6674
004a6650 movss xmm2, dword ptr [edi + 0x2d8]
004a6658 jmp 0x4a6688
004a665a call 0x6c3d90
004a665f xor edx, edx
004a6661 mov ecx, 3
004a6666 div ecx
004a6668 test edx, edx
004a666a je 0x4a6671
004a666c movaps xmm0, xmm3
004a666f jmp 0x4a6674
004a6671 movaps xmm0, xmm4
004a6674 movss xmm2, dword ptr [edi + 0x2d8]
004a667c subss xmm2, xmm0
004a6680 movss dword ptr [edi + 0x2d8], xmm2
004a6688 add esi, 0x38
004a668b cmp esi, dword ptr [edi + 0xc]
004a668e jne 0x4a6626
004a6690 jmp 0x4a669a
004a6692 movss xmm2, dword ptr [edi + 0x2d8]
004a669a movss xmm0, dword ptr [0xb6a614] ; [0xb6a614] f32=1
004a66a2 comiss xmm0, xmm2
004a66a5 jbe 0x4a66bd
004a66a7 mov dword ptr [edi + 0x2d8], 0x3f800000
004a66b1 mov byte ptr [edi + 0x16b], 1
004a66b8 jmp 0x4a79e8
004a66bd movss xmm0, dword ptr [0xb6a6f0] ; [0xb6a6f0] f32=1.5
004a66c5 comiss xmm0, xmm2
004a66c8 jbe 0x4a79e8
004a66ce mov byte ptr [edi + 0x16b], 1
004a66d5 jmp 0x4a79e8
004a66da cmp dword ptr [edi + 0x318], 0
004a66e1 mov byte ptr [edi + 0x169], 0
004a66e8 mov dword ptr [edi + 0x180], 0
004a66f2 jne 0x4a79e8
004a66f8 movzx eax, word ptr [edi + 0x360]
004a66ff test ax, ax
004a6702 je 0x4a6711
004a6704 dec eax
004a6705 mov word ptr [edi + 0x360], ax
004a670c jmp 0x4a79e8
004a6711 cmp word ptr [edi + 0x362], 0
004a6719 jg 0x4a79e8
004a671f mov ecx, edi
004a6721 call 0x4a5120
004a6726 jmp 0x4a79e8
004a672b mov eax, dword ptr [edi + 0x70]
004a672e test eax, eax
004a6730 je 0x4a6741
004a6732 cmp byte ptr [edi + 0x80], 0
004a6739 je 0x4a6741
004a673b cmp byte ptr [eax + 0x34], 0
004a673f je 0x4a674e
004a6741 mov ecx, edi
004a6743 call 0x4a4dc0
004a6748 mov ecx, dword ptr [ebp - 0x120]
004a674e mov dword ptr [ecx + 0xb08], 0x3f99999a
004a6758 movzx eax, word ptr [edi + 0xaf4]
004a675f test ax, ax
004a6762 jle 0x4a79e8
004a6768 dec eax
004a6769 mov word ptr [edi + 0xaf4], ax
004a6770 test ax, ax
004a6773 jg 0x4a79e8
004a6779 cmp dword ptr [edi + 0xab4], 0xe
004a6780 jne 0x4a67aa
004a6782 cmp byte ptr [edi + 0xaf7], 0
004a6789 je 0x4a79e8
004a678f push 0
004a6791 push 0xb40898 ; string='Taunt'
004a6796 lea ecx, [edi + 0x3c]
004a6799 call 0x4054f0
004a679e mov byte ptr [edi + 0xaf3], 0x96
004a67a5 jmp 0x4a79e8
004a67aa mov ecx, edi
004a67ac call 0x4a5c40
004a67b1 jmp 0x4a79e8
004a67b6 mov ecx, edi
004a67b8 call 0x4a4dc0
004a67bd mov ecx, dword ptr [ebp - 0x120]
004a67c3 lea edx, [ebp - 0x108]
004a67c9 lea eax, [ebp - 0xec]
004a67cf mov dword ptr [ebp - 0xec], 0x41f00000
004a67d9 movss xmm0, dword ptr [ecx + 0xb08]
004a67e1 addss xmm0, dword ptr [0xb6a2ac] ; [0xb6a2ac] f32=0.0799999982
004a67e9 comiss xmm0, dword ptr [0xb6aa0c] ; [0xb6aa0c] f32=30
004a67f0 movss dword ptr [ebp - 0x108], xmm0
004a67f8 cmovbe eax, edx
004a67fb mov eax, dword ptr [eax]
004a67fd mov dword ptr [ecx + 0xb08], eax
004a6803 mov ecx, edi
004a6805 push dword ptr [edi + 0x20]
004a6808 push 0xf
004a680a call 0x684790
004a680f test al, al
004a6811 je 0x4a79e8
004a6817 push ecx
004a6818 lea eax, [edi + 0x294]
004a681e mov dword ptr [esp], 0x41a00000
004a6825 push eax
004a6826 mov ecx, esi
004a6828 call 0x7cf0a0
004a682d test al, al
004a682f je 0x4a79e8
004a6835 call 0x6c3d90
004a683a movd xmm0, eax
004a683e cvtdq2pd xmm0, xmm0
004a6842 shr eax, 0x1f
004a6845 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
004a684e lea eax, [ebp - 0x110]
004a6854 push eax
004a6855 cvtpd2ps xmm0, xmm0
004a6859 mulss xmm0, dword ptr [0xb6a19c] ; [0xb6a19c] f32=2.32830644e-10
004a6861 movss dword ptr [ebp - 0xec], xmm0
004a6869 call 0x659290
004a686e movss xmm1, dword ptr [ebp - 0xec]
004a6876 add esp, 4
004a6879 movaps xmm0, xmm1
004a687c mulss xmm0, dword ptr [eax]
004a6880 push 0
004a6882 mulss xmm1, dword ptr [eax + 4]
004a6887 lea eax, [ebp - 0x100]
004a688d push 0
004a688f addss xmm0, dword ptr [edi + 0x294]
004a6897 push ecx
004a6898 addss xmm1, dword ptr [edi + 0x298]
004a68a0 mov dword ptr [esp], 0
004a68a7 mov ecx, esi
004a68a9 push eax
004a68aa lea eax, [ebp - 0x138]
004a68b0 movss dword ptr [ebp - 0x100], xmm0
004a68b8 push eax
004a68b9 movss dword ptr [ebp - 0xfc], xmm1
004a68c1 call 0x7cf240
004a68c6 call 0x6c3d90
004a68cb lea ecx, [ebp - 0x138]
004a68d1 push ecx
004a68d2 mov ecx, dword ptr [0xbfd65c]
004a68d8 push eax
004a68d9 push 0
004a68db push 0
004a68dd push 0xc02fec
004a68e2 lea eax, [edi + 0x294]
004a68e8 push eax
004a68e9 push 0
004a68eb push 4
004a68ed call 0x422e20
004a68f2 push eax
004a68f3 mov ecx, edi
004a68f5 call 0x4a6080
004a68fa jmp 0x4a79e8
004a68ff push 0
004a6901 lea esi, [edi + 0x3c]
004a6904 push 0xb41d4c ; string='ChargeFinish'
004a6909 mov ecx, esi
004a690b call 0x4054f0
004a6910 push 0xb400ac ; string='Shoot'
004a6915 mov ecx, esi
004a6917 call 0x4060f0
004a691c test al, al
004a691e je 0x4a6a68
004a6924 lea ecx, [ebp - 0xe8]
004a692a call 0x430d70
004a692f mov eax, dword ptr [ebp - 0x90]
004a6935 lea ecx, [ebp - 0xbc]
004a693b movaps xmm0, xmmword ptr [0xb6c610] ; [0xb6c610] f32=1
004a6942 or dword ptr [ebp - 0x8c], 8
004a6949 mov dword ptr [ebp - 0x90], eax
004a694f lea eax, [ebp - 0x40]
004a6952 movups xmmword ptr [ebp - 0x40], xmm0
004a6956 mov dword ptr [ebp - 0xd4], 0x40000000
004a6960 xorps xmm0, xmm0
004a6963 mov dword ptr [ebp - 0x20], 0x3f800000
004a696a push eax
004a696b movups xmmword ptr [ebp - 0x30], xmm0
004a696f mov dword ptr [ebp - 0x1c], 0x3e99999a
004a6976 mov dword ptr [ebp - 0x18], 0
004a697d call 0x4021a0
004a6982 mov ecx, edi
004a6984 call 0x695680
004a6989 mov esi, eax
004a698b movss xmm1, dword ptr [esi + 0x294]
004a6993 movss xmm0, dword ptr [esi + 0x298]
004a699b subss xmm0, dword ptr [edi + 0x298]
004a69a3 subss xmm1, dword ptr [edi + 0x294]
004a69ab mulss xmm0, xmm0
004a69af mulss xmm1, xmm1
004a69b3 addss xmm0, xmm1
004a69b7 call 0x4228c0
004a69bc movss xmm1, dword ptr [esi + 0x2b8]
004a69c4 lea eax, [ebp - 0xe8]
004a69ca movss xmm2, dword ptr [esi + 0x2bc]
004a69d2 mulss xmm1, dword ptr [0xb6a2cc] ; [0xb6a2cc] f32=0.100000001
004a69da push eax
004a69db mulss xmm2, dword ptr [0xb6a2cc] ; [0xb6a2cc] f32=0.100000001
004a69e3 lea eax, [ebp - 0x100]
004a69e9 push ecx
004a69ea mulss xmm1, xmm0
004a69ee mov ecx, edi
004a69f0 mov dword ptr [esp], 0x41200000
004a69f7 mulss xmm2, xmm0
004a69fb push eax
004a69fc addss xmm1, dword ptr [esi + 0x294]
004a6a04 push 1
004a6a06 addss xmm2, dword ptr [esi + 0x298]
004a6a0e movss dword ptr [ebp - 0x100], xmm1
004a6a16 movss dword ptr [ebp - 0xfc], xmm2
004a6a1e call 0x6a3420
004a6a23 lea esi, [edi + 0x3c]
004a6a26 movss xmm0, dword ptr [eax + 0x368]
004a6a2e subss xmm0, dword ptr [0xb6a4c4] ; [0xb6a4c4] f32=0.600000024
004a6a36 mov dword ptr [eax + 0x370], 0x40000000
004a6a40 movss dword ptr [eax + 0x368], xmm0
004a6a48 movss xmm0, dword ptr [eax + 0x364]
004a6a50 mulss xmm0, dword ptr [0xb6a50c] ; [0xb6a50c] f32=0.699999988
004a6a58 subss xmm0, dword ptr [0xb6a864] ; [0xb6a864] f32=3
004a6a60 movss dword ptr [eax + 0x364], xmm0
004a6a68 push 0xb400ac ; string='Shoot'
004a6a6d mov ecx, esi
004a6a6f call 0x406150
004a6a74 mov ecx, dword ptr [ebp - 0x120]
004a6a7a movss xmm1, dword ptr [ecx + 0xb08]
004a6a82 test al, al
004a6a84 je 0x4a6ac7
004a6a86 addss xmm1, dword ptr [0xb6a2cc] ; [0xb6a2cc] f32=0.100000001
004a6a8e lea eax, [ebp - 0xec]
004a6a94 mov dword ptr [ebp - 0xec], 0x3f99999a
004a6a9e lea edx, [ebp - 0x108]
004a6aa4 comiss xmm1, dword ptr [0xb6a670] ; [0xb6a670] f32=1.20000005
004a6aab movss dword ptr [ebp - 0x108], xmm1
004a6ab3 cmovbe eax, edx
004a6ab6 movss xmm0, dword ptr [eax]
004a6aba movss dword ptr [ecx + 0xb08], xmm0
004a6ac2 jmp 0x4a79e8
004a6ac7 subss xmm1, dword ptr [0xb6a53c] ; [0xb6a53c] f32=0.75
004a6acf movss xmm0, dword ptr [0xb6a560] ; [0xb6a560] f32=0.800000012
004a6ad7 lea eax, [ebp - 0x118]
004a6add lea edx, [ebp - 0x124]
004a6ae3 mov dword ptr [ebp - 0x118], 0x3f4ccccd
004a6aed comiss xmm0, xmm1
004a6af0 movss dword ptr [ebp - 0x124], xmm1
004a6af8 cmovbe eax, edx
004a6afb movss xmm0, dword ptr [eax]
004a6aff movss dword ptr [ecx + 0xb08], xmm0
004a6b07 jmp 0x4a79e8
004a6b0c lea esi, [edi + 0x3c]
004a6b0f push 0xb400b4 ; string='Sound'
004a6b14 mov ecx, esi
004a6b16 call 0x4060f0
004a6b1b test al, al
004a6b1d je 0x4a6b3f
004a6b1f push ecx
004a6b20 mov dword ptr [esp], 0x3f800000
004a6b27 push 0
004a6b29 push 2
004a6b2b push ecx
004a6b2c mov dword ptr [esp], 0x3f800000
004a6b33 mov ecx, edi
004a6b35 push 0xc9
004a6b3a call 0x6ad720 ; PlaySound
004a6b3f push 0xb400ac ; string='Shoot'
004a6b44 mov ecx, esi
004a6b46 call 0x4060f0
004a6b4b test al, al
004a6b4d je 0x4a6d6f
004a6b53 push ecx
004a6b54 mov dword ptr [esp], 0x3f800000
004a6b5b push 0
004a6b5d push 2
004a6b5f push ecx
004a6b60 mov dword ptr [esp], 0x3f800000
004a6b67 mov ecx, edi
004a6b69 push 0x19
004a6b6b call 0x6ad720 ; PlaySound
004a6b70 mov ecx, edi
004a6b72 call 0x695680
004a6b77 mov esi, eax
004a6b79 movss xmm1, dword ptr [esi + 0x294]
004a6b81 movss xmm0, dword ptr [esi + 0x298]
004a6b89 subss xmm0, dword ptr [edi + 0x298]
004a6b91 subss xmm1, dword ptr [edi + 0x294]
004a6b99 mulss xmm0, xmm0
004a6b9d mulss xmm1, xmm1
004a6ba1 addss xmm0, xmm1
004a6ba5 call 0x4228c0
004a6baa movaps xmm3, xmm0
004a6bad call 0x6c3d90
004a6bb2 movss xmm2, dword ptr [esi + 0x2bc]
004a6bba push 0
004a6bbc push 0
004a6bbe movd xmm1, eax
004a6bc2 cvtdq2pd xmm1, xmm1
004a6bc6 shr eax, 0x1f
004a6bc9 push ecx
004a6bca mov ecx, dword ptr [ebp - 0x11c]
004a6bd0 addsd xmm1, qword ptr [eax*8 + 0xb6c940]
004a6bd9 mov dword ptr [esp], 0
004a6be0 lea eax, [ebp - 0x110]
004a6be6 push eax
004a6be7 lea eax, [ebp - 0x100]
004a6bed push eax
004a6bee cvtpd2ps xmm0, xmm1
004a6bf2 movss xmm1, dword ptr [esi + 0x2b8]
004a6bfa mulss xmm0, dword ptr [0xb6a19c] ; [0xb6a19c] f32=2.32830644e-10
004a6c02 mulss xmm0, dword ptr [0xb6a354] ; [0xb6a354] f32=0.200000018
004a6c0a addss xmm0, dword ptr [0xb6a2cc] ; [0xb6a2cc] f32=0.100000001
004a6c12 mulss xmm1, xmm0
004a6c16 mulss xmm2, xmm0
004a6c1a mulss xmm1, xmm3
004a6c1e mulss xmm2, xmm3
004a6c22 addss xmm1, dword ptr [esi + 0x294]
004a6c2a addss xmm2, dword ptr [esi + 0x298]
004a6c32 movss dword ptr [ebp - 0x110], xmm1
004a6c3a movss dword ptr [ebp - 0x10c], xmm2
004a6c42 call 0x7cf240
004a6c47 mov esi, dword ptr [edi + 0xb4c]
004a6c4d mov ecx, esi
004a6c4f mov edx, dword ptr [edi + 0xb48]
004a6c55 and ecx, 3
004a6c58 dec edx
004a6c59 movss xmm0, dword ptr [eax]
004a6c5d movss dword ptr [ebp - 0x110], xmm0
004a6c65 movss xmm0, dword ptr [eax + 4]
004a6c6a mov eax, esi
004a6c6c shr eax, 2
004a6c6f and edx, eax
004a6c71 movss dword ptr [ebp - 0x10c], xmm0
004a6c79 mov eax, dword ptr [edi + 0xb44]
004a6c7f mov eax, dword ptr [eax + edx*4]
004a6c82 cmp dword ptr [eax + ecx*4], 0
004a6c86 mov ecx, dword ptr [edi + 0xb48]
004a6c8c je 0x4a6cbb
004a6c8e dec ecx
004a6c8f mov eax, esi
004a6c91 shr eax, 2
004a6c94 and esi, 3
004a6c97 and ecx, eax
004a6c99 mov eax, dword ptr [edi + 0xb44]
004a6c9f mov eax, dword ptr [eax + ecx*4]
004a6ca2 lea ecx, [ebp - 0x110]
004a6ca8 push ecx
004a6ca9 mov ecx, edi
004a6cab push dword ptr [eax + esi*4]
004a6cae call 0x4a6080
004a6cb3 mov edx, dword ptr [edi + 0xb4c]
004a6cb9 jmp 0x4a6d24
004a6cbb lea edx, [esi + 1]
004a6cbe mov dword ptr [ebp - 0xfc], esi
004a6cc4 mov eax, edx
004a6cc6 dec ecx
004a6cc7 shr eax, 2
004a6cca and edx, 3
004a6ccd and ecx, eax
004a6ccf mov dword ptr [ebp - 0xec], eax
004a6cd5 mov eax, dword ptr [edi + 0xb44]
004a6cdb mov eax, dword ptr [eax + ecx*4]
004a6cde cmp dword ptr [eax + edx*4], 0
004a6ce2 je 0x4a6d66
004a6ce8 mov ecx, dword ptr [edi + 0xb48]
004a6cee mov eax, dword ptr [edi + 0xb44]
004a6cf4 dec ecx
004a6cf5 and ecx, dword ptr [ebp - 0xec]
004a6cfb mov dword ptr [ebp - 0xfc], esi
004a6d01 mov eax, dword ptr [eax + ecx*4]
004a6d04 lea ecx, [ebp - 0x110]
004a6d0a push ecx
004a6d0b mov ecx, edi
004a6d0d push dword ptr [eax + edx*4]
004a6d10 call 0x4a6080
004a6d15 mov eax, dword ptr [edi + 0xb4c]
004a6d1b mov dword ptr [ebp - 0xfc], eax
004a6d21 lea edx, [eax + 1]
004a6d24 mov ecx, dword ptr [edi + 0xb48]
004a6d2a mov eax, edx
004a6d2c shr eax, 2
004a6d2f dec ecx
004a6d30 and ecx, eax
004a6d32 and edx, 3
004a6d35 mov eax, dword ptr [edi + 0xb44]
004a6d3b mov eax, dword ptr [eax + ecx*4]
004a6d3e mov ecx, dword ptr [eax + edx*4]
004a6d41 lea esi, [eax + edx*4]
004a6d44 test ecx, ecx
004a6d46 je 0x4a6d60
004a6d48 lea eax, [ebp - 0xec]
004a6d4e mov dword ptr [ebp - 0xec], esi
004a6d54 push eax
004a6d55 add ecx, 0x324
004a6d5b call 0x4bc3c0
004a6d60 mov dword ptr [esi], 0
004a6d66 inc byte ptr [edi + 0xaf6]
004a6d6c lea esi, [edi + 0x3c]
004a6d6f cmp dword ptr [edi + 0x70], 0
004a6d73 je 0x4a6d82
004a6d75 cmp byte ptr [edi + 0x80], 0
004a6d7c jne 0x4a79e8
004a6d82 mov dword ptr [edi + 0xab4], 3
004a6d8c cmp byte ptr [edi + 0xaf7], 0
004a6d93 je 0x4a79e8
004a6d99 cmp byte ptr [edi + 0xaf3], 0
004a6da0 ja 0x4a79e8
004a6da6 call 0x6c3d90
004a6dab xor edx, edx
004a6dad mov ecx, 0xa
004a6db2 div ecx
004a6db4 test edx, edx
004a6db6 jne 0x4a79e8
004a6dbc movss xmm0, dword ptr [edi + 0x2d8]
004a6dc4 divss xmm0, dword ptr [edi + 0x2dc]
004a6dcc comiss xmm0, dword ptr [0xb6a480] ; [0xb6a480] f32=0.5
004a6dd3 jbe 0x4a79e8
004a6dd9 push edx
004a6dda push 0xb40898 ; string='Taunt'
004a6ddf mov ecx, esi
004a6de1 call 0x4054f0
004a6de6 mov byte ptr [edi + 0xaf3], 0x96
004a6ded jmp 0x4a79e8
004a6df2 push 0xb400ac ; string='Shoot'
004a6df7 lea ecx, [edi + 0x3c]
004a6dfa call 0x4060f0
004a6dff test al, al
004a6e01 je 0x4a79e8
004a6e07 push ecx
004a6e08 mov dword ptr [esp], 0x3f800000
004a6e0f push 0
004a6e11 push 2
004a6e13 push ecx
004a6e14 mov dword ptr [esp], 0x3f800000
004a6e1b mov ecx, edi
004a6e1d push 0x19
004a6e1f call 0x6ad720 ; PlaySound
004a6e24 xor eax, eax
004a6e26 mov dword ptr [ebp - 0x20], 0
004a6e2d xor edx, edx
004a6e2f mov dword ptr [ebp - 0x108], eax
004a6e35 mov dword ptr [ebp - 0x1c], edx
004a6e38 mov dword ptr [ebp - 0x18], eax
004a6e3b mov dword ptr [ebp - 4], 2
004a6e42 mov eax, dword ptr [0xbfd65c]
004a6e47 mov eax, dword ptr [eax + 0x18190]
004a6e4d mov ecx, dword ptr [eax + 0x10]
004a6e50 imul ecx, dword ptr [eax + 0xc]
004a6e54 xor eax, eax
004a6e56 cmp ecx, 0x87
004a6e5c setg al
004a6e5f add eax, 3
004a6e62 mov dword ptr [ebp - 0xec], eax
004a6e68 nop dword ptr [eax + eax]
004a6e70 mov dword ptr [ebp - 0x10c], 0
004a6e7a mov dword ptr [ebp - 0x110], 0
004a6e84 cmp dword ptr [ebp - 0x20], edx
004a6e87 jne 0x4a6ebd
004a6e89 push ecx
004a6e8a lea eax, [ebp - 0x144]
004a6e90 mov dword ptr [esp], 0x42200000
004a6e97 push eax
004a6e98 mov ecx, esi
004a6e9a call 0x7d9b50
004a6e9f movss xmm0, dword ptr [eax]
004a6ea3 movss dword ptr [ebp - 0x110], xmm0
004a6eab movss xmm0, dword ptr [eax + 4]
004a6eb0 movss dword ptr [ebp - 0x10c], xmm0
004a6eb8 jmp 0x4a707a
004a6ebd movss xmm0, dword ptr [0xb6afcc] ; [0xb6afcc] f32=-1.00000002e+30
004a6ec5 mov edi, dword ptr [ebp - 0x1c]
004a6ec8 movss dword ptr [ebp - 0x124], xmm0
004a6ed0 mov dword ptr [ebp - 0x118], 8
004a6eda nop word ptr [eax + eax]
004a6ee0 push ecx
004a6ee1 lea eax, [ebp - 0x100]
004a6ee7 mov dword ptr [esp], 0x42200000
004a6eee push eax
004a6eef mov ecx, esi
004a6ef1 call 0x7d9b50
004a6ef6 mov esi, dword ptr [ebp - 0x20]
004a6ef9 xorps xmm0, xmm0
004a6efc movss dword ptr [ebp - 0x13c], xmm0
004a6f04 nop dword ptr [eax]
004a6f08 nop dword ptr [eax + eax]
004a6f10 movss xmm1, dword ptr [ebp - 0xfc]
004a6f18 subss xmm1, dword ptr [esi + 4]
004a6f1d movss xmm2, dword ptr [ebp - 0x100]
004a6f25 subss xmm2, dword ptr [esi]
004a6f29 movaps xmm0, xmm1
004a6f2c movss dword ptr [ebp - 0xf4], xmm1
004a6f34 mulss xmm0, xmm1
004a6f38 movaps xmm1, xmm2
004a6f3b movss dword ptr [ebp - 0x114], xmm2
004a6f43 mulss xmm1, xmm2
004a6f47 addss xmm0, xmm1
004a6f4b call 0x4228c0
004a6f50 movss xmm1, dword ptr [ebp - 0xf4]
004a6f58 andps xmm1, xmmword ptr [0xb6c980] ; [0xb6c980] f32=nan
004a6f5f movss xmm2, dword ptr [ebp - 0x114]
004a6f67 andps xmm2, xmmword ptr [0xb6c980] ; [0xb6c980] f32=nan
004a6f6e movss dword ptr [ebp - 0xf8], xmm0
004a6f76 movaps xmm0, xmm1
004a6f79 mulss xmm0, xmm1
004a6f7d movss dword ptr [ebp - 0xf4], xmm1
004a6f85 movss dword ptr [ebp - 0x134], xmm1
004a6f8d movaps xmm1, xmm2
004a6f90 mulss xmm1, xmm2
004a6f94 movss dword ptr [ebp - 0x114], xmm2
004a6f9c movss dword ptr [ebp - 0x138], xmm2
004a6fa4 addss xmm0, xmm1
004a6fa8 call 0x4228c0
004a6fad comiss xmm0, dword ptr [0xb6a18c] ; [0xb6a18c] f32=0
004a6fb4 movss xmm2, dword ptr [ebp - 0x114]
004a6fbc jbe 0x4a6fef
004a6fbe movss xmm1, dword ptr [0xb6a614] ; [0xb6a614] f32=1
004a6fc6 divss xmm1, xmm0
004a6fca movaps xmm0, xmm1
004a6fcd mulss xmm2, xmm0
004a6fd1 movss xmm0, dword ptr [ebp - 0xf4]
004a6fd9 mulss xmm0, xmm1
004a6fdd movss dword ptr [ebp - 0x138], xmm2
004a6fe5 movss dword ptr [ebp - 0x134], xmm0
004a6fed jmp 0x4a6ff7
004a6fef movss xmm0, dword ptr [ebp - 0xf4]
004a6ff7 comiss xmm2, xmm0
004a6ffa lea eax, [ebp - 0x134]
004a7000 lea ecx, [ebp - 0x138]
004a7006 cmovbe eax, ecx
004a7009 add esi, 8
004a700c movss xmm0, dword ptr [eax]
004a7010 mulss xmm0, dword ptr [ebp - 0xf8]
004a7018 addss xmm0, dword ptr [ebp - 0x13c]
004a7020 movss dword ptr [ebp - 0x13c], xmm0
004a7028 cmp esi, edi
004a702a jne 0x4a6f10
004a7030 comiss xmm0, dword ptr [ebp - 0x124]
004a7037 jbe 0x4a7061
004a7039 movss dword ptr [ebp - 0x124], xmm0
004a7041 movss xmm0, dword ptr [ebp - 0x100]
004a7049 movss dword ptr [ebp - 0x110], xmm0
004a7051 movss xmm0, dword ptr [ebp - 0xfc]
004a7059 movss dword ptr [ebp - 0x10c], xmm0
004a7061 sub dword ptr [ebp - 0x118], 1
004a7068 mov esi, dword ptr [ebp - 0x11c]
004a706e jne 0x4a6ee0
004a7074 mov edi, dword ptr [ebp - 0xf0]
004a707a push 0
004a707c push 0
004a707e push ecx
004a707f mov dword ptr [esp], 0x42800000
004a7086 lea eax, [ebp - 0x110]
004a708c push eax
004a708d lea eax, [ebp - 0x130]
004a7093 mov ecx, esi
004a7095 push eax
004a7096 call 0x7cf240
004a709b movss xmm0, dword ptr [eax]
004a709f movss dword ptr [ebp - 0xf8], xmm0
004a70a7 movss dword ptr [ebp - 0x110], xmm0
004a70af movss xmm0, dword ptr [eax + 4]
004a70b4 movss dword ptr [ebp - 0x118], xmm0
004a70bc movss dword ptr [ebp - 0x10c], xmm0
004a70c4 call 0x6c3d90
004a70c9 mov ecx, dword ptr [0xbfd65c]
004a70cf push eax
004a70d0 push 0
004a70d2 push 0
004a70d4 push 0xc02fec
004a70d9 lea eax, [edi + 0x294]
004a70df push eax
004a70e0 push 0xf
004a70e2 push 4
004a70e4 call 0x422e20
004a70e9 mov esi, eax
004a70eb mov ecx, edi
004a70ed lea eax, [ebp - 0x110]
004a70f3 push eax
004a70f4 push esi
004a70f5 call 0x4a6080
004a70fa mov edx, dword ptr [ebp - 0x1c]
004a70fd mov ecx, dword ptr [ebp - 0x108]
004a7103 mov dword ptr [esi + 0x180], 1
004a710d cmp edx, ecx
004a710f je 0x4a7132
004a7111 movss xmm0, dword ptr [ebp - 0xf8]
004a7119 movss dword ptr [edx], xmm0
004a711d movss xmm0, dword ptr [ebp - 0x118]
004a7125 movss dword ptr [edx + 4], xmm0
004a712a add edx, 8
004a712d mov dword ptr [ebp - 0x1c], edx
004a7130 jmp 0x4a714e
004a7132 lea eax, [ebp - 0x110]
004a7138 push eax
004a7139 push edx
004a713a lea ecx, [ebp - 0x20]
004a713d call 0x422130
004a7142 mov ecx, dword ptr [ebp - 0x18]
004a7145 mov edx, dword ptr [ebp - 0x1c]
004a7148 mov dword ptr [ebp - 0x108], ecx
004a714e sub dword ptr [ebp - 0xec], 1
004a7155 mov esi, dword ptr [ebp - 0x11c]
004a715b jne 0x4a6e70
004a7161 mov eax, 0x7d
004a7166 mov dword ptr [ebp - 4], 0xffffffff
004a716d mov word ptr [edi + 0x362], ax
004a7174 mov eax, dword ptr [ebp - 0x20]
004a7177 test eax, eax
004a7179 je 0x4a79e8
004a717f sub ecx, eax
004a7181 sar ecx, 3
004a7184 push ecx
004a7185 push eax
004a7186 call 0x421f90
004a718b jmp 0x4a79e8
004a7190 push 0
004a7192 push 0xb41d6c ; string='Detonate'
004a7197 lea ecx, [edi + 0x3c]
004a719a call 0x4054f0
004a719f push 0xb400b4 ; string='Sound'
004a71a4 lea ecx, [edi + 0x3c]
004a71a7 call 0x4060f0
004a71ac test al, al
004a71ae je 0x4a71d0
004a71b0 push ecx
004a71b1 mov dword ptr [esp], 0x3f800000
004a71b8 push 0
004a71ba push 2
004a71bc push ecx
004a71bd mov dword ptr [esp], 0x3f800000
004a71c4 mov ecx, edi
004a71c6 push 0xfc
004a71cb call 0x6ad720 ; PlaySound
004a71d0 push 0xb400ac ; string='Shoot'
004a71d5 lea ecx, [edi + 0x3c]
004a71d8 call 0x4060f0
004a71dd test al, al
004a71df je 0x4a79e8
004a71e5 push ecx
004a71e6 mov dword ptr [esp], 0x3f800000
004a71ed push 0
004a71ef push 2
004a71f1 push ecx
004a71f2 mov dword ptr [esp], 0x3f800000
004a71f9 mov ecx, edi
004a71fb push 0x1d5
004a7200 call 0x6ad720 ; PlaySound
004a7205 jmp 0x4a79e8
004a720a movss xmm0, dword ptr [edi + 0x2c4]
004a7212 mulss xmm0, dword ptr [0xb6a4c4] ; [0xb6a4c4] f32=0.600000024
004a721a movss dword ptr [edi + 0x2c4], xmm0
004a7222 cmp dword ptr [edi + 0x70], 0
004a7226 je 0x4a7235
004a7228 cmp byte ptr [edi + 0x80], 0
004a722f jne 0x4a79e8
004a7235 mov eax, 0x5a
004a723a mov dword ptr [edi + 0xab4], 4
004a7244 mov ecx, edi
004a7246 mov word ptr [edi + 0xaf4], ax
004a724d call 0x695680
004a7252 movss xmm1, dword ptr [edi + 0x294]
004a725a movss xmm0, dword ptr [edi + 0x298]
004a7262 subss xmm1, dword ptr [eax + 0x294]
004a726a subss xmm0, dword ptr [eax + 0x298]
004a7272 call 0x447a80
004a7277 mulss xmm0, dword ptr [0xb6aa84] ; [0xb6aa84] f32=57.2957764
004a727f movss dword ptr [edi + 0xb00], xmm0
004a7287 jmp 0x4a79e8
004a728c movss xmm0, dword ptr [edi + 0x2c4]
004a7294 lea ecx, [edi + 0x3c]
004a7297 movss xmm4, dword ptr [edi + 0x2bc]
004a729f mulss xmm0, dword ptr [0xb6a560] ; [0xb6a560] f32=0.800000012
004a72a7 movaps xmm2, xmm4
004a72aa push 0
004a72ac movss xmm1, dword ptr [edi + 0x2b8]
004a72b4 andps xmm2, xmmword ptr [0xb6c980] ; [0xb6c980] f32=nan
004a72bb andps xmm1, xmmword ptr [0xb6c980] ; [0xb6c980] f32=nan
004a72c2 comiss xmm2, xmm1
004a72c5 movss dword ptr [edi + 0x2c4], xmm0
004a72cd jb 0x4a72e9
004a72cf comiss xmm3, xmm4
004a72d2 mov edx, 0xb41d3c ; string='RunDown'
004a72d7 mov eax, 0xb41d44 ; string='RunUp'
004a72dc cmovbe eax, edx
004a72df push eax
004a72e0 call 0x4054f0
004a72e5 xor al, al
004a72e7 jmp 0x4a7300
004a72e9 push 0xb413f0 ; string='RunHori'
004a72ee call 0x4054f0
004a72f3 xorps xmm0, xmm0
004a72f6 comiss xmm0, dword ptr [edi + 0x2b8]
004a72fd seta al
004a7300 mov byte ptr [edi + 0x13c], al
004a7306 movzx edx, word ptr [edi + 0xaf4]
004a730d test dx, dx
004a7310 jle 0x4a732d
004a7312 cvttss2si eax, dword ptr [edi + 0x2fc]
004a731a cvttss2si ecx, dword ptr [edi + 0x2f8]
004a7322 sub ecx, eax
004a7324 add ecx, edx
004a7326 mov word ptr [edi + 0xaf4], cx
004a732d mov ecx, dword ptr [edi + 0xb3c]
004a7333 test ecx, ecx
004a7335 je 0x4a7344
004a7337 call 0x4a84a0
004a733c mov dword ptr [ebp - 0xf4], eax
004a7342 jmp 0x4a734e
004a7344 mov dword ptr [ebp - 0xf4], 0xffffffff
004a734e lea eax, [edi + 0x294]
004a7354 mov ecx, esi
004a7356 push eax
004a7357 mov dword ptr [ebp - 0x118], eax
004a735d call 0x7ce950
004a7362 cmp eax, dword ptr [ebp - 0xf4]
004a7368 je 0x4a7405
004a736e push ecx
004a736f lea eax, [edi + 0x294]
004a7375 mov dword ptr [esp], 0
004a737c push eax
004a737d mov ecx, esi
004a737f call 0x7cf0a0
004a7384 test al, al
004a7386 je 0x4a7405
004a7388 cmp dword ptr [edi + 0xb3c], 0
004a738f lea eax, [edi + 0xb3c]
004a7395 mov byte ptr [ebp - 0x101], 0
004a739c je 0x4a7412
004a739e push 0
004a73a0 push 0xa
004a73a2 mov ecx, edi
004a73a4 call 0x684790
004a73a9 test al, al
004a73ab je 0x4a740c
004a73ad push 0
004a73af push dword ptr [ebp - 0xf4]
004a73b5 lea eax, [ebp - 0x130]
004a73bb mov ecx, esi
004a73bd push eax
004a73be call 0x7cebc0
004a73c3 push eax
004a73c4 lea ecx, [edi + 0x364]
004a73ca call 0x7a6ea0
004a73cf test al, al
004a73d1 lea eax, [edi + 0xb3c]
004a73d7 jne 0x4a7412
004a73d9 mov ecx, dword ptr [eax]
004a73db test ecx, ecx
004a73dd je 0x4a73fd
004a73df mov dword ptr [ebp - 0xf0], eax
004a73e5 add ecx, 0x324
004a73eb lea eax, [ebp - 0xf0]
004a73f1 push eax
004a73f2 call 0x4bc3c0
004a73f7 lea eax, [edi + 0xb3c]
004a73fd mov dword ptr [eax], 0
004a7403 jmp 0x4a7412
004a7405 mov byte ptr [ebp - 0x101], 1
004a740c lea eax, [edi + 0xb3c]
004a7412 mov ecx, dword ptr [eax]
004a7414 mov dword ptr [ebp - 0x114], ecx
004a741a test ecx, ecx
004a741c jne 0x4a757a
004a7422 cmp word ptr [edi + 0xaf4], cx
004a7429 jg 0x4a766b
004a742f mov eax, dword ptr [0xbfd65c]
004a7434 xor esi, esi
004a7436 movss xmm0, dword ptr [0xb6adc0] ; [0xb6adc0] f32=1.00000002e+30
004a743e movss dword ptr [ebp - 0xec], xmm0
004a7446 mov dword ptr [ebp - 0xf4], ecx
004a744c mov eax, dword ptr [eax + 0x18190]
004a7452 mov dword ptr [ebp - 0xf8], eax
004a7458 mov dword ptr [ebp - 0x108], esi
004a745e cmp dword ptr [eax + 0x1264], ecx
004a7464 jbe 0x4a7553
004a746a nop word ptr [eax + eax]
004a7470 mov eax, dword ptr [eax + 0x125c]
004a7476 mov esi, dword ptr [eax + esi*4]
004a7479 cmp dword ptr [esi + 0x28], 0x3c7
004a7480 jne 0x4a74f4
004a7482 movss xmm0, dword ptr [esi + 0x294]
004a748a lea eax, [edi + 0x294]
004a7490 movss xmm1, dword ptr [esi + 0x298]
004a7498 lea ecx, [edi + 0x364]
004a749e subss xmm1, dword ptr [eax + 4]
004a74a3 subss xmm0, dword ptr [eax]
004a74a7 push 0
004a74a9 push eax
004a74aa mulss xmm1, xmm1
004a74ae mulss xmm0, xmm0
004a74b2 addss xmm1, xmm0
004a74b6 movss dword ptr [ebp - 0xf0], xmm1
004a74be call 0x7a6ea0
004a74c3 test al, al
004a74c5 je 0x4a74ee
004a74c7 movss xmm0, dword ptr [ebp - 0xf0]
004a74cf movss xmm1, dword ptr [ebp - 0xec]
004a74d7 comiss xmm1, xmm0
004a74da jbe 0x4a74ee
004a74dc mov ecx, esi
004a74de movss dword ptr [ebp - 0xec], xmm0
004a74e6 mov dword ptr [ebp - 0xf4], ecx
004a74ec jmp 0x4a74f4
004a74ee mov ecx, dword ptr [ebp - 0xf4]
004a74f4 mov esi, dword ptr [ebp - 0x108]
004a74fa mov eax, dword ptr [ebp - 0xf8]
004a7500 inc esi
004a7501 mov dword ptr [ebp - 0x108], esi
004a7507 cmp esi, dword ptr [eax + 0x1264]
004a750d jb 0x4a7470
004a7513 test ecx, ecx
004a7515 je 0x4a7553
004a7517 mov edx, dword ptr [edi + 0xb3c]
004a751d lea eax, [edi + 0xb3c]
004a7523 test edx, edx
004a7525 je 0x4a754b
004a7527 mov dword ptr [ebp - 0xf0], eax
004a752d lea ecx, [edx + 0x324]
004a7533 lea eax, [ebp - 0xf0]
004a7539 push eax
004a753a call 0x4bc3c0
004a753f mov ecx, dword ptr [ebp - 0xf4]
004a7545 lea eax, [edi + 0xb3c]
004a754b push eax
004a754c mov dword ptr [eax], ecx
004a754e call 0x4bae70
004a7553 mov ecx, dword ptr [edi + 0xb3c]
004a7559 test ecx, ecx
004a755b je 0x4a766b
004a7561 call 0x4a84a0
004a7566 mov ecx, dword ptr [edi + 0xb3c]
004a756c mov esi, dword ptr [ebp - 0x11c]
004a7572 mov dword ptr [ebp - 0x114], ecx
004a7578 jmp 0x4a7580
004a757a mov eax, dword ptr [ebp - 0xf4]
004a7580 test ecx, ecx
004a7582 je 0x4a766b
004a7588 push eax
004a7589 lea eax, [ebp - 0x100]
004a758f mov ecx, esi
004a7591 push eax
004a7592 call 0x7cebc0
004a7597 cmp byte ptr [ebp - 0x101], 0
004a759e je 0x4a763e
004a75a4 mov ecx, dword ptr [ebp - 0x114]
004a75aa lea eax, [ebp - 0x130]
004a75b0 push eax
004a75b1 mov dword ptr [edi + 0x17c], 0
004a75bb call 0x4a8340
004a75c0 movss xmm1, dword ptr [edi + 0x2f4]
004a75c8 mov ecx, dword ptr [ebp - 0x114]
004a75ce push 5
004a75d0 movss xmm3, dword ptr [eax]
004a75d4 movss xmm2, dword ptr [eax + 4]
004a75d9 xorps xmm3, xmmword ptr [0xb6c9b0] ; [0xb6c9b0] f32=-0
004a75e0 xorps xmm2, xmmword ptr [0xb6c9b0] ; [0xb6c9b0] f32=-0
004a75e7 mulss xmm3, xmm1
004a75eb mulss xmm2, xmm1
004a75ef addss xmm3, dword ptr [edi + 0x2b8]
004a75f7 addss xmm2, dword ptr [edi + 0x2bc]
004a75ff movss dword ptr [edi + 0x2b8], xmm3
004a7607 movss dword ptr [edi + 0x2bc], xmm2
004a760f call 0x4a8620
004a7614 lea eax, [edi + 0x294]
004a761a mov ecx, esi
004a761c push eax
004a761d call 0x7ce950
004a7622 test eax, eax
004a7624 jns 0x4a78e3
004a762a push edi
004a762b mov ecx, esi
004a762d call 0x7bb930
004a7632 mov eax, dword ptr [edi]
004a7634 mov ecx, edi
004a7636 call dword ptr [eax + 0x28]
004a7639 jmp 0x4a78e3
004a763e push 1
004a7640 push 0
004a7642 push ecx
004a7643 lea eax, [ebp - 0x100]
004a7649 mov dword ptr [esp], 0x3f8a3d71
004a7650 push eax
004a7651 lea ecx, [edi + 0x364]
004a7657 mov dword ptr [edi + 0x17c], 5
004a7661 call 0x7a3650
004a7666 jmp 0x4a78e3
004a766b mov ecx, edi
004a766d call 0x695680
004a7672 movss xmm5, dword ptr [edi + 0x298]
004a767a xorps xmm1, xmm1
004a767d movss xmm3, dword ptr [0xbe9a2c] ; [0xbe9a2c] f32=1
004a7685 xorps xmm2, xmm2
004a7688 movss xmm6, dword ptr [eax + 0x294]
004a7690 movss xmm7, dword ptr [eax + 0x298]
004a7698 mov eax, dword ptr [ebp - 0x118]
004a769e subss xmm5, xmm7
004a76a2 movss xmm4, dword ptr [eax]
004a76a6 subss xmm4, xmm6
004a76aa mulss xmm3, xmm5
004a76ae movaps xmm0, xmm4
004a76b1 mulss xmm0, dword ptr [0xbe9a28] ; [0xbe9a28] f32=0
004a76b9 addss xmm3, xmm0
004a76bd comiss xmm3, xmm1
004a76c0 jbe 0x4a76c5
004a76c2 movaps xmm2, xmm3
004a76c5 movss xmm1, dword ptr [0xbe9a30] ; [0xbe9a30] f32=0
004a76cd mov ecx, 0xc02fec
004a76d2 movss xmm0, dword ptr [0xbe9a34] ; [0xbe9a34] f32=-1
004a76da mov edx, 0xbe9a28
004a76df mulss xmm1, xmm4
004a76e3 cmova ecx, edx
004a76e6 mulss xmm0, xmm5
004a76ea addss xmm1, xmm0
004a76ee comiss xmm1, xmm2
004a76f1 jbe 0x4a76fb
004a76f3 movaps xmm2, xmm1
004a76f6 mov ecx, 0xbe9a30
004a76fb movss xmm1, dword ptr [0xbe9a38] ; [0xbe9a38] f32=-1
004a7703 movss xmm0, dword ptr [0xbe9a3c] ; [0xbe9a3c] f32=0
004a770b mulss xmm1, xmm4
004a770f mulss xmm0, xmm5
004a7713 addss xmm1, xmm0
004a7717 comiss xmm1, xmm2
004a771a jbe 0x4a7724
004a771c movaps xmm2, xmm1
004a771f mov ecx, 0xbe9a38
004a7724 movss xmm1, dword ptr [0xbe9a40] ; [0xbe9a40] f32=1
004a772c movss xmm0, dword ptr [0xbe9a44] ; [0xbe9a44] f32=0
004a7734 mulss xmm1, xmm4
004a7738 mulss xmm0, xmm5
004a773c addss xmm1, xmm0
004a7740 comiss xmm1, xmm2
004a7743 jbe 0x4a774d
004a7745 movaps xmm2, xmm1
004a7748 mov ecx, 0xbe9a40
004a774d movss xmm1, dword ptr [eax]
004a7751 movaps xmm0, xmm2
004a7754 mulss xmm0, dword ptr [ecx]
004a7758 mulss xmm2, dword ptr [ecx + 4]
004a775d mulss xmm0, dword ptr [0xb6a560] ; [0xb6a560] f32=0.800000012
004a7765 mulss xmm2, dword ptr [0xb6a560] ; [0xb6a560] f32=0.800000012
004a776d addss xmm6, xmm0
004a7771 movss xmm0, dword ptr [edi + 0x298]
004a7779 addss xmm7, xmm2
004a777d subss xmm1, xmm6
004a7781 subss xmm0, xmm7
004a7785 call 0x447a80
004a778a mulss xmm0, dword ptr [0xb6aa84] ; [0xb6aa84] f32=57.2957764
004a7792 movss dword ptr [ebp - 0xf8], xmm0
004a779a movss xmm0, dword ptr [edi + 0xb00]
004a77a2 mulss xmm0, dword ptr [0xb6a230] ; [0xb6a230] f32=0.0174532924
004a77aa movss dword ptr [ebp - 0xf0], xmm0
004a77b2 call 0x412010
004a77b7 movss dword ptr [ebp - 0xec], xmm0
004a77bf movss xmm0, dword ptr [ebp - 0xf0]
004a77c7 call 0x411fe0
004a77cc movss dword ptr [ebp - 0xf0], xmm0
004a77d4 call 0x6c3d90
004a77d9 movss xmm1, dword ptr [ebp - 0xf8]
004a77e1 movd xmm0, eax
004a77e5 cvtdq2pd xmm0, xmm0
004a77e9 shr eax, 0x1f
004a77ec addsd xmm0, qword ptr [eax*8 + 0xb6c940]
004a77f5 cvtpd2ps xmm2, xmm0
004a77f9 movss xmm0, dword ptr [edi + 0xb00]
004a7801 mulss xmm2, dword ptr [0xb6a19c] ; [0xb6a19c] f32=2.32830644e-10
004a7809 mulss xmm2, dword ptr [0xb6a864] ; [0xb6a864] f32=3
004a7811 addss xmm2, dword ptr [0xb6a480] ; [0xb6a480] f32=0.5
004a7819 call 0x65a950
004a781e cmp byte ptr [edi + 0x188], 0
004a7825 movss xmm6, dword ptr [ebp - 0xf0]
004a782d movss xmm7, dword ptr [ebp - 0xec]
004a7835 movaps xmm3, xmm6
004a7838 mulss xmm3, dword ptr [0xb6a670] ; [0xb6a670] f32=1.20000005
004a7840 movaps xmm2, xmm7
004a7843 mulss xmm2, dword ptr [0xb6a670] ; [0xb6a670] f32=1.20000005
004a784b movss xmm1, dword ptr [edi + 0x2f4]
004a7853 mulss xmm3, xmm1
004a7857 mulss xmm2, xmm1
004a785b movss dword ptr [edi + 0xb00], xmm0
004a7863 addss xmm3, dword ptr [edi + 0x2b8]
004a786b addss xmm2, dword ptr [edi + 0x2bc]
004a7873 movss dword ptr [edi + 0x2b8], xmm3
004a787b movss dword ptr [edi + 0x2bc], xmm2
004a7883 je 0x4a78dd
004a7885 movss xmm4, dword ptr [edi + 0x198]
004a788d movss xmm3, dword ptr [edi + 0x194]
004a7895 movaps xmm0, xmm4
004a7898 movaps xmm5, xmm3
004a789b mulss xmm0, xmm7
004a789f mulss xmm5, xmm6
004a78a3 addss xmm3, xmm3
004a78a7 addss xmm4, xmm4
004a78ab addss xmm5, xmm0
004a78af movaps xmm2, xmm5
004a78b2 mulss xmm5, xmm4
004a78b6 mulss xmm2, xmm3
004a78ba subss xmm7, xmm5
004a78be subss xmm6, xmm2
004a78c2 movaps xmm0, xmm7
004a78c5 movaps xmm1, xmm6
004a78c8 call 0x447a80
004a78cd mulss xmm0, dword ptr [0xb6aa84] ; [0xb6aa84] f32=57.2957764
004a78d5 movss dword ptr [edi + 0xb00], xmm0
004a78dd mov esi, dword ptr [ebp - 0x11c]
004a78e3 push ecx
004a78e4 lea eax, [edi + 0x294]
004a78ea mov dword ptr [esp], 0
004a78f1 push eax
004a78f2 mov ecx, esi
004a78f4 call 0x7cf0a0
004a78f9 test al, al
004a78fb jne 0x4a79de
004a7901 movss xmm2, dword ptr [edi + 0x294]
004a7909 lea ecx, [ebp - 0xf8]
004a790f movss xmm3, dword ptr [esi + 0x14]
004a7914 lea eax, [ebp - 0xf0]
004a791a movss xmm0, dword ptr [esi + 0x18]
004a791f subss xmm3, xmm2
004a7923 subss xmm2, dword ptr [esi + 0x1c]
004a7928 movss xmm1, dword ptr [edi + 0x298]
004a7930 subss xmm0, xmm1
004a7934 subss xmm1, dword ptr [esi + 0x20]
004a7939 movss dword ptr [ebp - 0xf8], xmm3
004a7941 comiss xmm2, xmm3
004a7944 movss dword ptr [ebp - 0xf0], xmm2
004a794c movss dword ptr [ebp - 0xec], xmm0
004a7954 cmovbe eax, ecx
004a7957 movss dword ptr [ebp - 0x108], xmm1
004a795f lea ecx, [ebp - 0xec]
004a7965 movss xmm2, dword ptr [0xb6a614] ; [0xb6a614] f32=1
004a796d comiss xmm0, dword ptr [eax]
004a7970 cmovbe ecx, eax
004a7973 lea eax, [ebp - 0x108]
004a7979 comiss xmm1, dword ptr [ecx]
004a797c xorps xmm1, xmm1
004a797f cmovbe eax, ecx
004a7982 lea ecx, [ebp - 0xf0]
004a7988 movss xmm0, dword ptr [eax]
004a798c lea eax, [ebp - 0xf8]
004a7992 subss xmm0, xmm1
004a7996 mov dword ptr [ebp - 0xf0], 0
004a79a0 mov dword ptr [ebp - 0xec], 0x3f800000
004a79aa divss xmm0, dword ptr [0xb6aa58] ; [0xb6aa58] f32=48
004a79b2 comiss xmm1, xmm0
004a79b5 movss dword ptr [ebp - 0xf8], xmm0
004a79bd cmovbe ecx, eax
004a79c0 lea eax, [ebp - 0xec]
004a79c6 movss xmm0, dword ptr [ecx]
004a79ca comiss xmm0, xmm2
004a79cd cmovbe eax, ecx
004a79d0 subss xmm2, dword ptr [eax]
004a79d4 movss dword ptr [edi + 0xf0], xmm2
004a79dc jmp 0x4a79eb
004a79de mov dword ptr [edi + 0xf0], 0x3f800000
004a79e8 xorps xmm1, xmm1
004a79eb movzx eax, word ptr [edi + 0x362]
004a79f2 test ax, ax
004a79f5 jle 0x4a79ff
004a79f7 dec eax
004a79f8 mov word ptr [edi + 0x362], ax
004a79ff mov eax, dword ptr [edi + 8]
004a7a02 cmp eax, dword ptr [edi + 0xc]
004a7a05 je 0x4a7a76
004a7a07 nop word ptr [eax + eax]
004a7a10 mov ecx, dword ptr [eax + 0xc]
004a7a13 mov edx, dword ptr [eax + 8]
004a7a16 mov dword ptr [ebp - 0x12c], ecx
004a7a1c mov ecx, edx
004a7a1e and ecx, 4
004a7a21 or ecx, 0
004a7a24 je 0x4a7a32
004a7a26 cmp dword ptr [eax + 0x18], 1
004a7a2a je 0x4a7a32
004a7a2c cmp dword ptr [eax + 0x10], 1
004a7a30 jne 0x4a7a5a
004a7a32 and edx, 8
004a7a35 or edx, 0
004a7a38 je 0x4a7a42
004a7a3a mov ecx, dword ptr [eax + 0x10]
004a7a3d cmp ecx, dword ptr [edi + 0x28]
004a7a40 je 0x4a7a5a
004a7a42 cmp dword ptr [eax + 0x10], 0x3e8
004a7a49 jne 0x4a7a6e
004a7a4b cmp dword ptr [eax + 0x14], 0x93
004a7a52 jne 0x4a7a6e
004a7a54 cmp dword ptr [eax + 0x18], 1
004a7a58 je 0x4a7a6e
004a7a5a movss xmm0, dword ptr [edi + 0x14]
004a7a5f subss xmm0, dword ptr [eax]
004a7a63 movss dword ptr [edi + 0x14], xmm0
004a7a68 mov dword ptr [eax], 0
004a7a6e add eax, 0x38
004a7a71 cmp eax, dword ptr [edi + 0xc]
004a7a74 jne 0x4a7a10
004a7a76 comiss xmm1, dword ptr [edi + 0x14]
004a7a7a jbe 0x4a7a83
004a7a7c mov dword ptr [edi + 0x14], 0
004a7a83 movaps xmm2, xmm1
004a7a86 mov ecx, edi
004a7a88 movss xmm1, dword ptr [0xb6a864] ; [0xb6a864] f32=3
004a7a90 call 0x6847e0
004a7a95 test eax, eax
004a7a97 je 0x4a7ae1
004a7a99 mov al, byte ptr [edi + 0xaf0]
004a7a9f test al, al
004a7aa1 je 0x4a7aab
004a7aa3 dec al
004a7aa5 mov byte ptr [edi + 0xaf0], al
004a7aab mov al, byte ptr [edi + 0xaf1]
004a7ab1 test al, al
004a7ab3 je 0x4a7abd
004a7ab5 dec al
004a7ab7 mov byte ptr [edi + 0xaf1], al
004a7abd mov al, byte ptr [edi + 0xaf2]
004a7ac3 test al, al
004a7ac5 je 0x4a7acf
004a7ac7 dec al
004a7ac9 mov byte ptr [edi + 0xaf2], al
004a7acf mov al, byte ptr [edi + 0xaf3]
004a7ad5 test al, al
004a7ad7 je 0x4a7ae1
004a7ad9 dec al
004a7adb mov byte ptr [edi + 0xaf3], al
004a7ae1 cmp byte ptr [edi + 0x16b], 0
004a7ae8 je 0x4a7f95
004a7aee cmp dword ptr [edi + 0x2c], 1
004a7af2 jne 0x4a7c86
004a7af8 call 0x6c3d90
004a7afd mov ecx, dword ptr [0xbfd65c]
004a7b03 lea esi, [edi + 0x294]
004a7b09 push eax
004a7b0a push 0
004a7b0c push 0
004a7b0e push 0xc02fec
004a7b13 push esi
004a7b14 push 1
004a7b16 push 0x3e8
004a7b1b call 0x422e20
004a7b20 call 0x6c3d90
004a7b25 mov ecx, dword ptr [0xbfd65c]
004a7b2b push eax
004a7b2c push 0
004a7b2e push 0
004a7b30 push 0xc02fec
004a7b35 push esi
004a7b36 push 0x12
004a7b38 push 0x3e8
004a7b3d call 0x422e20
004a7b42 mov ecx, eax
004a7b44 mov edx, dword ptr [eax]
004a7b46 call dword ptr [edx + 0xc]
004a7b49 mov ecx, dword ptr [0xbfd65c]
004a7b4f push 0
004a7b51 push 0
004a7b53 push 0x1004
004a7b58 sub esp, 0x10
004a7b5b mov eax, esp
004a7b5d push 0
004a7b5f push 0
004a7b61 sub esp, 8
004a7b64 mov dword ptr [eax], 0
004a7b6a mov dword ptr [eax + 4], 0
004a7b71 mov dword ptr [eax + 8], 0
004a7b78 mov dword ptr [eax + 0xc], 0
004a7b7f mov dword ptr [esp + 4], 0x42960000
004a7b87 mov dword ptr [esp], 0x42dc0000
004a7b8e push esi
004a7b8f call 0x6d1750
004a7b94 mov esi, 6
004a7b99 nop dword ptr [eax]
004a7ba0 call 0x6c3d90
004a7ba5 movd xmm0, eax
004a7ba9 cvtdq2pd xmm0, xmm0
004a7bad shr eax, 0x1f
004a7bb0 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
004a7bb9 cvtpd2ps xmm0, xmm0
004a7bbd mulss xmm0, dword ptr [0xb6a19c] ; [0xb6a19c] f32=2.32830644e-10
004a7bc5 mulss xmm0, dword ptr [0xb6a9ac] ; [0xb6a9ac] f32=15
004a7bcd addss xmm0, dword ptr [0xb6a8f4] ; [0xb6a8f4] f32=5
004a7bd5 movss dword ptr [ebp - 0xec], xmm0
004a7bdd call 0x6c3d90
004a7be2 movd xmm0, eax
004a7be6 cvtdq2pd xmm0, xmm0
004a7bea shr eax, 0x1f
004a7bed addsd xmm0, qword ptr [eax*8 + 0xb6c940]
004a7bf6 cvtpd2ps xmm0, xmm0
004a7bfa mulss xmm0, dword ptr [0xb6a19c] ; [0xb6a19c] f32=2.32830644e-10
004a7c02 mulss xmm0, dword ptr [0xb6a874] ; [0xb6a874] f32=3.14159274
004a7c0a addss xmm0, xmm0
004a7c0e movss dword ptr [ebp - 0xf0], xmm0
004a7c16 call 0x411fe0
004a7c1b mulss xmm0, dword ptr [ebp - 0xec]
004a7c23 movss dword ptr [ebp - 0x100], xmm0
004a7c2b movss xmm0, dword ptr [ebp - 0xf0]
004a7c33 call 0x412010
004a7c38 mulss xmm0, dword ptr [ebp - 0xec]
004a7c40 movss dword ptr [ebp - 0xfc], xmm0
004a7c48 call 0x6c3d90
004a7c4d mov ecx, dword ptr [0xbfd65c]
004a7c53 push eax
004a7c54 push 0
004a7c56 push edi
004a7c57 lea eax, [ebp - 0x100]
004a7c5d push eax
004a7c5e lea eax, [edi + 0x294]
004a7c64 push eax
004a7c65 push 3
004a7c67 push 4
004a7c69 call 0x422e20
004a7c6e mov dword ptr [eax + 0x180], 1
004a7c78 sub esi, 1
004a7c7b jne 0x4a7ba0
004a7c81 jmp 0x4a7f95
004a7c86 cmp dword ptr [ebp - 0x120], 0
004a7c8d je 0x4a7f95
004a7c93 cmp byte ptr [edi + 0x169], 0
004a7c9a je 0x4a7f95
004a7ca0 call 0x6c3d90
004a7ca5 mov ecx, dword ptr [0xbfd65c]
004a7cab lea esi, [edi + 0x294]
004a7cb1 push eax
004a7cb2 push 0
004a7cb4 push 0
004a7cb6 push 0xc02fec
004a7cbb push esi
004a7cbc push 1
004a7cbe push 0x3e8
004a7cc3 call 0x422e20
004a7cc8 cmp dword ptr [edi + 0xab4], 8
004a7ccf jne 0x4a7f18
004a7cd5 mov edx, dword ptr [edi + 0xb4c]
004a7cdb mov ecx, edx
004a7cdd mov eax, dword ptr [edi + 0xb48]
004a7ce3 and edx, 3
004a7ce6 dec eax
004a7ce7 shr ecx, 2
004a7cea and ecx, eax
004a7cec mov eax, dword ptr [edi + 0xb44]
004a7cf2 mov eax, dword ptr [eax + ecx*4]
004a7cf5 cmp dword ptr [eax + edx*4], 0
004a7cf9 je 0x4a7df5
004a7cff call 0x6c3d90
004a7d04 movd xmm0, eax
004a7d08 cvtdq2pd xmm0, xmm0
004a7d0c shr eax, 0x1f
004a7d0f addsd xmm0, qword ptr [eax*8 + 0xb6c940]
004a7d18 lea eax, [ebp - 0x130]
004a7d1e push eax
004a7d1f cvtpd2ps xmm0, xmm0
004a7d23 mulss xmm0, dword ptr [0xb6a19c] ; [0xb6a19c] f32=2.32830644e-10
004a7d2b mulss xmm0, dword ptr [0xb6a974] ; [0xb6a974] f32=10
004a7d33 movss dword ptr [ebp - 0xf0], xmm0
004a7d3b call 0x659290
004a7d40 movss xmm1, dword ptr [ebp - 0xf0]
004a7d48 add esp, 4
004a7d4b mov edx, dword ptr [edi + 0xb4c]
004a7d51 movaps xmm0, xmm1
004a7d54 mov ecx, edx
004a7d56 and edx, 3
004a7d59 mulss xmm0, dword ptr [eax]
004a7d5d shr ecx, 2
004a7d60 mulss xmm1, dword ptr [eax + 4]
004a7d65 lea eax, [ebp - 0x100]
004a7d6b push eax
004a7d6c mov eax, dword ptr [edi + 0xb48]
004a7d72 addss xmm0, dword ptr [esi]
004a7d76 addss xmm1, dword ptr [esi + 4]
004a7d7b dec eax
004a7d7c and ecx, eax
004a7d7e mov eax, dword ptr [edi + 0xb44]
004a7d84 movss dword ptr [ebp - 0x100], xmm0
004a7d8c movss dword ptr [ebp - 0xfc], xmm1
004a7d94 mov eax, dword ptr [eax + ecx*4]
004a7d97 mov ecx, edi
004a7d99 push dword ptr [eax + edx*4]
004a7d9c call 0x4a6080
004a7da1 mov edx, dword ptr [edi + 0xb4c]
004a7da7 mov ecx, edx
004a7da9 mov eax, dword ptr [edi + 0xb48]
004a7daf and edx, 3
004a7db2 dec eax
004a7db3 shr ecx, 2
004a7db6 and ecx, eax
004a7db8 mov eax, dword ptr [edi + 0xb44]
004a7dbe mov eax, dword ptr [eax + ecx*4]
004a7dc1 mov ecx, dword ptr [eax + edx*4]
004a7dc4 lea eax, [eax + edx*4]
004a7dc7 mov dword ptr [ebp - 0xf8], eax
004a7dcd test ecx, ecx
004a7dcf je 0x4a7def
004a7dd1 mov dword ptr [ebp - 0xf0], eax
004a7dd7 add ecx, 0x324
004a7ddd lea eax, [ebp - 0xf0]
004a7de3 push eax
004a7de4 call 0x4bc3c0
004a7de9 mov eax, dword ptr [ebp - 0xf8]
004a7def mov dword ptr [eax], 0
004a7df5 mov eax, dword ptr [edi + 0xb4c]
004a7dfb mov ecx, dword ptr [edi + 0xb48]
004a7e01 mov dword ptr [ebp - 0x12c], eax
004a7e07 dec ecx
004a7e08 lea edx, [eax + 1]
004a7e0b mov eax, edx
004a7e0d and edx, 3
004a7e10 shr eax, 2
004a7e13 and ecx, eax
004a7e15 mov eax, dword ptr [edi + 0xb44]
004a7e1b mov eax, dword ptr [eax + ecx*4]
004a7e1e cmp dword ptr [eax + edx*4], 0
004a7e22 je 0x4a7f18
004a7e28 call 0x6c3d90
004a7e2d movd xmm0, eax
004a7e31 cvtdq2pd xmm0, xmm0
004a7e35 shr eax, 0x1f
004a7e38 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
004a7e41 lea eax, [ebp - 0x130]
004a7e47 push eax
004a7e48 cvtpd2ps xmm0, xmm0
004a7e4c mulss xmm0, dword ptr [0xb6a19c] ; [0xb6a19c] f32=2.32830644e-10
004a7e54 mulss xmm0, dword ptr [0xb6a974] ; [0xb6a974] f32=10
004a7e5c movss dword ptr [ebp - 0xf0], xmm0
004a7e64 call 0x659290
004a7e69 movss xmm1, dword ptr [ebp - 0xf0]
004a7e71 add esp, 4
004a7e74 mov ecx, dword ptr [edi + 0xb48]
004a7e7a movaps xmm0, xmm1
004a7e7d dec ecx
004a7e7e mulss xmm0, dword ptr [eax]
004a7e82 mulss xmm1, dword ptr [eax + 4]
004a7e87 mov eax, dword ptr [edi + 0xb4c]
004a7e8d addss xmm0, dword ptr [esi]
004a7e91 addss xmm1, dword ptr [esi + 4]
004a7e96 lea edx, [eax + 1]
004a7e99 lea eax, [ebp - 0x100]
004a7e9f push eax
004a7ea0 mov eax, edx
004a7ea2 movss dword ptr [ebp - 0x100], xmm0
004a7eaa shr eax, 2
004a7ead and edx, 3
004a7eb0 and ecx, eax
004a7eb2 movss dword ptr [ebp - 0xfc], xmm1
004a7eba mov eax, dword ptr [edi + 0xb44]
004a7ec0 mov eax, dword ptr [eax + ecx*4]
004a7ec3 mov ecx, edi
004a7ec5 push dword ptr [eax + edx*4]
004a7ec8 call 0x4a6080
004a7ecd mov eax, dword ptr [edi + 0xb4c]
004a7ed3 lea edx, [eax + 1]
004a7ed6 mov eax, dword ptr [edi + 0xb48]
004a7edc mov ecx, edx
004a7ede dec eax
004a7edf shr ecx, 2
004a7ee2 and edx, 3
004a7ee5 and ecx, eax
004a7ee7 mov eax, dword ptr [edi + 0xb44]
004a7eed mov eax, dword ptr [eax + ecx*4]
004a7ef0 mov ecx, dword ptr [eax + edx*4]
004a7ef3 lea esi, [eax + edx*4]
004a7ef6 test ecx, ecx
004a7ef8 je 0x4a7f12
004a7efa lea eax, [ebp - 0xf0]
004a7f00 mov dword ptr [ebp - 0xf0], esi
004a7f06 push eax
004a7f07 add ecx, 0x324
004a7f0d call 0x4bc3c0
004a7f12 mov dword ptr [esi], 0
004a7f18 mov ecx, dword ptr [ebp - 0x120]
004a7f1e call 0x4bc040
004a7f23 push 0
004a7f25 push 0xb41d68 ; string='Sad'
004a7f2a lea ecx, [edi + 0x3c]
004a7f2d mov dword ptr [edi + 0xab4], 0xd
004a7f37 call 0x4054f0
004a7f3c lea esi, [edi + 0xb3c]
004a7f42 mov dword ptr [edi + 0x17c], 5
004a7f4c mov byte ptr [edi + 0x16b], 0
004a7f53 mov dword ptr [edi + 0x2d8], 0x42c80000
004a7f5d mov ecx, dword ptr [esi]
004a7f5f test ecx, ecx
004a7f61 je 0x4a7f7b
004a7f63 lea eax, [ebp - 0xf0]
004a7f69 mov dword ptr [ebp - 0xf0], esi
004a7f6f push eax
004a7f70 add ecx, 0x324
004a7f76 call 0x4bc3c0
004a7f7b mov dword ptr [esi], 0
004a7f81 mov dword ptr [edi + 0x2e0], 0x3f800000
004a7f8b mov dword ptr [edi + 0xf0], 0x3f800000
004a7f95 mov ecx, dword ptr [ebp - 0xc]
004a7f98 mov dword ptr fs:[0], ecx
004a7f9f pop ecx
004a7fa0 pop edi
004a7fa1 pop esi
004a7fa2 mov ecx, dword ptr [ebp - 0x14]
004a7fa5 xor ecx, ebp
004a7fa7 call 0x9eacd7
004a7fac mov esp, ebp
004a7fae pop ebp
004a7faf mov esp, ebx
004a7fb1 pop ebx
004a7fb2 ret 
