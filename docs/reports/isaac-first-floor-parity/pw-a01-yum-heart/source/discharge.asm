00771510 push ebx
00771511 mov ebx, esp
00771513 sub esp, 8
00771516 and esp, 0xfffffff8
00771519 add esp, 4
0077151c push ebp
0077151d mov ebp, dword ptr [ebx + 4]
00771520 mov dword ptr [esp + 4], ebp
00771524 mov ebp, esp
00771526 push -1
00771528 push 0x9f8bf7
0077152d mov eax, dword ptr fs:[0]
00771533 push eax
00771534 push ebx
00771535 sub esp, 0x80
0077153b mov eax, dword ptr [0xbaa3b4]
00771540 xor eax, ebp
00771542 mov dword ptr [ebp - 0x14], eax
00771545 push esi
00771546 push edi
00771547 push eax
00771548 lea eax, [ebp - 0xc]
0077154b mov dword ptr fs:[0], eax
00771551 mov edi, ecx
00771553 mov dword ptr [ebp - 0x48], edi
00771556 mov ecx, dword ptr [ebx + 8]
00771559 mov eax, dword ptr [ebx + 0xc]
0077155c mov byte ptr [ebp - 0x74], al
0077155f mov dword ptr [ebp - 0x50], ecx
00771562 lea esi, [ecx*8]
00771569 sub esi, ecx
0077156b shl esi, 2
0077156e mov dword ptr [ebp - 0x60], esi
00771571 cmp dword ptr [esi + edi + 0x14c4], 0
00771579 je 0x771fd7
0077157f mov eax, dword ptr [esi + edi + 0x14cc]
00771586 push ecx
00771587 mov ecx, edi
00771589 mov dword ptr [ebp - 0x5c], eax
0077158c call 0x757e40
00771591 push dword ptr [ebp - 0x50]
00771594 mov ecx, edi
00771596 mov dword ptr [ebp - 0x4c], eax
00771599 call 0x757ea0
0077159e mov ecx, dword ptr [ebp - 0x50]
007715a1 add ecx, 0xbe
007715a7 mov dword ptr [ebp - 0x68], eax
007715aa lea eax, [ecx*8]
007715b1 sub eax, ecx
007715b3 mov ecx, dword ptr [ebp - 0x4c]
007715b6 mov dword ptr [ebp - 0x58], eax
007715b9 mov eax, dword ptr [edi + eax*4]
007715bc cmp eax, ecx
007715be jge 0x771661
007715c4 push dword ptr [esi + edi + 0x14c4]
007715cb sub eax, ecx
007715cd mov ecx, dword ptr [0xbfd680]
007715d3 mov dword ptr [ebp - 0x54], eax
007715d6 lea ecx, [ecx + 0x29e84]
007715dc call 0x6fe5e0
007715e1 mov ecx, eax
007715e3 test ecx, ecx
007715e5 je 0x771661
007715e7 call 0x6ff190
007715ec cmp eax, 2
007715ef je 0x771661
007715f1 call 0x6ff190
007715f6 or ecx, 0xffffffff
007715f9 cmp eax, 1
007715fc mov eax, dword ptr [ebp - 0x54]
007715ff cmove eax, ecx
00771602 cmp dword ptr [edi + 0x130c], 0x12
00771609 mov dword ptr [ebp - 0x54], eax
0077160c jne 0x77164c
0077160e cmp dword ptr [edi + 0x1cc8], 0
00771615 jle 0x77164c
00771617 push 0
00771619 push 0x26b
0077161e mov ecx, edi
00771620 call 0x73af30
00771625 test al, al
00771627 je 0x771640
00771629 mov ecx, dword ptr [edi + 0x1698]
0077162f add ecx, 0x26b0
00771635 push 2
00771637 call 0x7a7d50
0077163c test eax, eax
0077163e je 0x77164c
00771640 push dword ptr [ebp - 0x54]
00771643 mov ecx, edi
00771645 call 0x794420
0077164a jmp 0x771661
0077164c mov ecx, edi
0077164e call 0x794730
00771653 test eax, eax
00771655 jle 0x771661
00771657 push dword ptr [ebp - 0x54]
0077165a mov ecx, edi
0077165c call 0x7946a0
00771661 push 0
00771663 push 0x74
00771665 mov ecx, edi
00771667 call 0x73af30
0077166c test al, al
0077166e mov eax, dword ptr [ebp - 0x5c]
00771671 je 0x771774
00771677 lea ecx, [eax + 1]
0077167a mov dword ptr [ebp - 0x54], ecx
0077167d cmp ecx, dword ptr [ebp - 0x68]
00771680 jge 0x771774
00771686 mov eax, dword ptr [0xbfd680]
0077168b push dword ptr [esi + edi + 0x14c4]
00771692 mov dword ptr [ebp - 0x68], eax
00771695 lea ecx, [eax + 0x29e84]
0077169b call 0x6fe5e0
007716a0 test eax, eax
007716a2 je 0x771714
007716a4 mov eax, dword ptr [eax + 0xac]
007716aa cmp eax, 1
007716ad jne 0x7716cc
007716af mov eax, dword ptr [ebp - 0x4c]
007716b2 cdq
007716b3 sub eax, edx
007716b5 mov edx, dword ptr [ebp - 0x54]
007716b8 sar eax, 1
007716ba mov ecx, edx
007716bc cmp edx, eax
007716be mov dword ptr [ebp - 0x68], eax
007716c1 mov dword ptr [ebp - 0x68], edx
007716c4 cmovl ecx, eax
007716c7 mov dword ptr [ebp - 0x5c], ecx
007716ca jmp 0x771714
007716cc test eax, eax
007716ce jne 0x771714
007716d0 mov edx, dword ptr [ebp - 0x54]
007716d3 lea ecx, [ebp - 0x4c]
007716d6 mov dword ptr [ebp - 0x5c], edx
007716d9 mov dword ptr [ebp - 0x4c], 0xab
007716e0 call 0x8b1340
007716e5 sub esp, 8
007716e8 mov dword ptr [esp + 4], 0
007716f0 mov dword ptr [esp], 0x3f800000
007716f7 push 0
007716f9 push 2
007716fb push ecx
007716fc mov ecx, dword ptr [ebp - 0x68]
007716ff mov dword ptr [esp], 0x3f800000
00771706 add ecx, 0x29de0
0077170c push dword ptr [ebp - 0x4c]
0077170f call 0x888de0
00771714 call 0x6c3d90
00771719 mov ecx, dword ptr [0xbfd65c]
0077171f push 0
00771721 push 0xbeaaec
00771726 push 0xbeab18
0077172b push 0
0077172d push eax
0077172e push 1
00771730 push 0
00771732 push 0xc02fec
00771737 lea eax, [edi + 0x294]
0077173d push eax
0077173e push 0x31
00771740 push 0x3e8
00771745 call 0x422e20
0077174a push eax
0077174b call 0x9ec34c
00771750 add esp, 0x14
00771753 mov dword ptr [eax + 0xd0], 0
0077175d mov dword ptr [eax + 0xd4], 0xc1c00000
00771767 mov dword ptr [eax + 0x2b0], 0x3f800000
00771771 mov eax, dword ptr [ebp - 0x5c]
00771774 mov ecx, dword ptr [ebp - 0x58]
00771777 push dword ptr [ebp - 0x50]
0077177a push eax
0077177b mov ecx, dword ptr [edi + ecx*4]
0077177e mov dword ptr [ebp - 0x5c], ecx
00771781 mov ecx, edi
00771783 call 0x757f20
00771788 mov byte ptr [edi + 0x1746], 0
0077178f mov eax, dword ptr [esi + edi + 0x14c4]
00771796 cmp eax, 0x2bf
0077179b jne 0x771ff7
007717a1 cmp dword ptr [esi + edi + 0x14dc], 0
007717a9 jne 0x771c65
007717af mov eax, dword ptr [0xbfd65c]
007717b4 xor esi, esi
007717b6 mov dword ptr [ebp - 0x58], eax
007717b9 add eax, 0x1badc
007717be nop
007717c0 cmp dword ptr [eax], 0
007717c3 je 0x77195d
007717c9 inc esi
007717ca add eax, 4
007717cd cmp esi, 4
007717d0 jl 0x7717c0
007717d2 mov esi, dword ptr [0xbfd680]
007717d8 lea ecx, [ebp - 0x4c]
007717db mov dword ptr [ebp - 0x4c], 0x35
007717e2 call 0x8b1340
007717e7 sub esp, 8
007717ea mov dword ptr [esp + 4], 0
007717f2 mov dword ptr [esp], 0x3f800000
007717f9 push 0
007717fb push 2
007717fd push ecx
007717fe mov dword ptr [esp], 0x3f800000
00771805 lea ecx, [esi + 0x29de0]
0077180b push dword ptr [ebp - 0x4c]
0077180e call 0x888de0
00771813 call 0x6c3d90
00771818 mov ecx, dword ptr [0xbfd65c]
0077181e lea esi, [edi + 0x294]
00771824 push eax
00771825 push 0
00771827 push 0
00771829 push 0xc02fec
0077182e push esi
0077182f push 0x61
00771831 push 0x3e8
00771836 call 0x422e20
0077183b mov ecx, eax
0077183d mov edx, dword ptr [eax]
0077183f call dword ptr [edx + 0xc]
00771842 call 0x6c3d90
00771847 push 0
00771849 push ecx
0077184a lea ecx, [ebp - 0x40]
0077184d movd xmm0, eax
00771851 cvtdq2pd xmm0, xmm0
00771855 shr eax, 0x1f
00771858 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
00771861 cvtpd2ps xmm1, xmm0
00771865 movss xmm0, dword ptr [edi + 0x2a8]
0077186d mulss xmm1, dword ptr [0xb6a19c]
00771875 movss dword ptr [esp], xmm0
0077187a call 0x402120
0077187f mulss xmm1, dword ptr [0xb6a864]
00771887 push eax
00771888 push ecx
00771889 mov ecx, dword ptr [0xbfd65c]
0077188f addss xmm1, dword ptr [0xb6a7b0]
00771897 movss dword ptr [esp], xmm1
0077189c push 8
0077189e push 0x23
007718a0 push esi
007718a1 call 0x6d57a0
007718a6 call 0x6c3d90
007718ab mov ecx, dword ptr [0xbfd65c]
007718b1 push eax
007718b2 push 2
007718b4 push 0
007718b6 push 0xc02fec
007718bb push esi
007718bc push 2
007718be push 0x3e8
007718c3 call 0x422e20
007718c8 mov ecx, eax
007718ca mov edx, dword ptr [eax]
007718cc call dword ptr [edx + 0xc]
007718cf mov eax, dword ptr [0xbfd680]
007718d4 mov ecx, dword ptr [eax + 0x29e9c]
007718da mov eax, dword ptr [eax + 0x29ea0]
007718e0 sub eax, ecx
007718e2 and eax, 0xfffffffc
007718e5 cmp eax, 0x20c
007718ea jg 0x7718f0
007718ec xor eax, eax
007718ee jmp 0x7718f6
007718f0 mov eax, dword ptr [ecx + 0x20c]
007718f6 mov dword ptr [ebp - 0x70], eax
007718f9 lea ecx, [edi + 0x1450]
007718ff mov eax, dword ptr [eax + 0x78]
00771902 push 1
00771904 mov dword ptr [ebp - 0x68], eax
00771907 lea eax, [ebp - 0x70]
0077190a push 1
0077190c push eax
0077190d mov dword ptr [ebp - 0x6c], 0
00771914 call 0x88b1c0
00771919 mov ecx, edi
0077191b call 0x72ed20
00771920 push 0xb44128
00771925 push 0xb449a0
0077192a push 0x2bf
0077192f mov ecx, edi
00771931 call 0x770300
00771936 cmp byte ptr [ebx + 0xc], 0
0077193a jne 0x771c62
00771940 mov ecx, dword ptr [ebp - 0x60]
00771943 push 1
00771945 push dword ptr [ebp - 0x50]
00771948 push 0
0077194a push dword ptr [ecx + edi + 0x14c4]
00771951 mov ecx, edi
00771953 call 0x756580
00771958 jmp 0x771fd7
0077195d push 0x2580
00771962 call 0x9eacf8
00771967 add esp, 4
0077196a mov dword ptr [ebp - 0x68], eax
0077196d mov ecx, eax
0077196f mov dword ptr [ebp - 4], 0
00771976 call 0x7204d0
0077197b mov dword ptr [ebp - 4], 0xffffffff
00771982 mov ecx, dword ptr [ebp - 0x58]
00771985 mov dword ptr [ecx + esi*4 + 0x1badc], eax
0077198c mov eax, dword ptr [0xbfd65c]
00771991 mov ecx, dword ptr [ebp - 0x60]
00771994 mov eax, dword ptr [eax + esi*4 + 0x1badc]
0077199b mov dword ptr [ebp - 0x54], eax
0077199e lea eax, [esi + 1]
007719a1 mov esi, dword ptr [ebp - 0x54]
007719a4 mov dword ptr [ecx + edi + 0x14dc], eax
007719ab mov ecx, esi
007719ad push dword ptr [edi + 0x344]
007719b3 mov eax, dword ptr [esi]
007719b5 push 0
007719b7 push dword ptr [edi + 0x2c]
007719ba push dword ptr [edi + 0x28]
007719bd call dword ptr [eax + 4]
007719c0 mov eax, dword ptr [edi + 0x294]
007719c6 mov dword ptr [esi + 0x294], eax
007719cc mov eax, dword ptr [edi + 0x298]
007719d2 mov dword ptr [esi + 0x298], eax
007719d8 mov eax, dword ptr [edi + 0x2b8]
007719de mov dword ptr [esi + 0x2b8], eax
007719e4 mov eax, dword ptr [edi + 0x2bc]
007719ea mov dword ptr [esi + 0x2bc], eax
007719f0 mov eax, dword ptr [0xbfd680]
007719f5 mov ecx, dword ptr [eax + 0x29e9c]
007719fb mov eax, dword ptr [eax + 0x29ea0]
00771a01 sub eax, ecx
00771a03 and eax, 0xfffffffc
00771a06 cmp eax, 0x190
00771a0b jg 0x771a11
00771a0d xor eax, eax
00771a0f jmp 0x771a17
00771a11 mov eax, dword ptr [ecx + 0x190]
00771a17 mov dword ptr [ebp - 0x70], eax
00771a1a lea ecx, [esi + 0x1450]
00771a20 mov eax, dword ptr [eax + 0x78]
00771a23 push 1
00771a25 mov dword ptr [ebp - 0x68], eax
00771a28 lea eax, [ebp - 0x70]
00771a2b push 1
00771a2d push eax
00771a2e mov dword ptr [ebp - 0x6c], 0
00771a35 call 0x88b1c0
00771a3a mov dword ptr [esi + 0x1290], 0
00771a44 mov ecx, esi
00771a46 mov dword ptr [esi + 0x1294], 0
00771a50 mov dword ptr [esi + 0x1298], 0
00771a5a mov dword ptr [edi + 0x1cac], 0
00771a64 mov dword ptr [esi + 0x1ca8], 0
00771a6e mov dword ptr [esi + 0x1cc4], 0
00771a78 mov dword ptr [esi + 0x129c], 6
00771a82 mov dword ptr [esi + 0x12a0], 0xffffffff
00771a8c call 0x725600
00771a91 mov eax, dword ptr [edi + 0x1490]
00771a97 mov ecx, edi
00771a99 mov dword ptr [esi + 0x1490], eax
00771a9f mov eax, dword ptr [edi + 0x1494]
00771aa5 mov dword ptr [esi + 0x1494], eax
00771aab mov eax, dword ptr [edi + 0x1498]
00771ab1 mov dword ptr [esi + 0x1498], eax
00771ab7 mov eax, dword ptr [edi + 0x149c]
00771abd mov dword ptr [esi + 0x149c], eax
00771ac3 mov eax, dword ptr [edi + 0x14a0]
00771ac9 push -1
00771acb mov dword ptr [esi + 0x14a0], eax
00771ad1 mov eax, dword ptr [edi + 0x14a4]
00771ad7 push esi
00771ad8 mov dword ptr [esi + 0x14a4], eax
00771ade call 0x7259b0
00771ae3 mov edi, dword ptr [edi + 0x1698]
00771ae9 mov ecx, dword ptr [ebp - 0x48]
00771aec add edi, 0x2bf0
00771af2 mov byte ptr [esi + 0x1d18], 1
00771af9 mov esi, dword ptr [ebp - 0x48]
00771afc mov esi, dword ptr [esi + 0x1d0c]
00771b02 cmp esi, dword ptr [ecx + 0x1d10]
00771b08 je 0x771c55
00771b0e nop
00771b10 cmp byte ptr [esi + 4], 0
00771b14 jne 0x771c46
00771b1a mov edx, dword ptr [esi + 8]
00771b1d mov eax, dword ptr [ecx + 0x15f0]
00771b23 cmp dword ptr [eax + edx*4], 0
00771b27 jle 0x771c46
00771b2d mov ecx, dword ptr [0xbfd680]
00771b33 push edx
00771b34 lea ecx, [ecx + 0x29e84]
00771b3a call 0x6fe5e0
00771b3f cmp dword ptr [eax], 3
00771b42 je 0x771c43
00771b48 push dword ptr [esi + 8]
00771b4b call 0x78fbe0
00771b50 test al, al
00771b52 je 0x771c43
00771b58 cmp dword ptr [esi], 1
00771b5b jl 0x771c43
00771b61 movups xmm0, xmmword ptr [esi]
00771b64 mov eax, dword ptr [esi + 0x18]
00771b67 mov dword ptr [ebp - 0x58], eax
00771b6a movups xmmword ptr [ebp - 0x30], xmm0
00771b6e mov dword ptr [ebp - 0x18], eax
00771b71 xor eax, eax
00771b73 movq xmm0, qword ptr [esi + 0x10]
00771b78 movq qword ptr [ebp - 0x70], xmm0
00771b7d movq qword ptr [ebp - 0x20], xmm0
00771b82 mov dword ptr [ebp - 0x28], eax
00771b85 mov dword ptr [ebp - 0x4c], eax
00771b88 test eax, eax
00771b8a jne 0x771bfa
00771b8c mov edx, dword ptr [edi]
00771b8e test edx, edx
00771b90 jne 0x771ba8
00771b92 push 0xb4d6c4
00771b97 push 3
00771b99 call 0x95e330
00771b9e mov edx, dword ptr [edi]
00771ba0 add esp, 8
00771ba3 test edx, edx
00771ba5 jne 0x771ba8
00771ba7 int3
00771ba8 mov ecx, dword ptr [edi + 4]
00771bab mov eax, edx
00771bad shr eax, cl
00771baf mov ecx, dword ptr [edi + 8]
00771bb2 xor eax, edx
00771bb4 mov edx, eax
00771bb6 shl edx, cl
00771bb8 mov ecx, dword ptr [edi + 0xc]
00771bbb xor edx, eax
00771bbd mov eax, edx
00771bbf shr eax, cl
00771bc1 mov ecx, dword ptr [0xbfd65c]
00771bc7 xor eax, edx
00771bc9 push 0
00771bcb push 6
00771bcd push eax
00771bce mov dword ptr [edi], eax
00771bd0 lea ecx, [ecx + 0x1a5cc]
00771bd6 push dword ptr [esi + 0x18]
00771bd9 call 0x701230
00771bde mov ecx, dword ptr [ebp - 0x4c]
00771be1 inc ecx
00771be2 mov dword ptr [ebp - 0x28], eax
00771be5 mov dword ptr [ebp - 0x4c], ecx
00771be8 cmp ecx, 0xa
00771beb jl 0x771b88
00771bed test eax, eax
00771bef mov ecx, 0x19
00771bf4 cmove eax, ecx
00771bf7 mov dword ptr [ebp - 0x28], eax
00771bfa mov ecx, dword ptr [ebp - 0x54]
00771bfd push 0
00771bff push 0
00771c01 push 0
00771c03 push 0
00771c05 push eax
00771c06 call 0x72b260
00771c0b mov ecx, dword ptr [ebp - 0x54]
00771c0e add ecx, 0x1d0c
00771c14 mov eax, dword ptr [ecx + 4]
00771c17 cmp eax, dword ptr [ecx + 8]
00771c1a je 0x771c39
00771c1c movups xmm0, xmmword ptr [ebp - 0x30]
00771c20 mov edx, dword ptr [ebp - 0x58]
00771c23 movups xmmword ptr [eax], xmm0
00771c26 movq xmm0, qword ptr [ebp - 0x70]
00771c2b movq qword ptr [eax + 0x10], xmm0
00771c30 mov dword ptr [eax + 0x18], edx
00771c33 add dword ptr [ecx + 4], 0x1c
00771c37 jmp 0x771c43
00771c39 lea edx, [ebp - 0x30]
00771c3c push edx
00771c3d push eax
00771c3e call 0x6f0df0
00771c43 mov ecx, dword ptr [ebp - 0x48]
00771c46 add esi, 0x1c
00771c49 cmp esi, dword ptr [ecx + 0x1d10]
00771c4f jne 0x771b10
00771c55 mov eax, dword ptr [ebp - 0x54]
00771c58 mov edi, dword ptr [ebp - 0x48]
00771c5b mov byte ptr [eax + 0x1d18], 0
00771c62 mov esi, dword ptr [ebp - 0x60]
00771c65 mov eax, dword ptr [esi + edi + 0x14dc]
00771c6c mov dword ptr [ebp - 0x68], eax
00771c6f test eax, eax
00771c71 jle 0x771fb3
00771c77 mov esi, dword ptr [0xbfd65c]
00771c7d mov esi, dword ptr [esi + eax*4 + 0x1bad8]
00771c84 mov dword ptr [ebp - 0x48], esi
00771c87 test esi, esi
00771c89 je 0x771fb3
00771c8f lea ecx, [edi + 0x1eb8]
00771c95 mov byte ptr [esi + 0x360], 0
00771c9c mov eax, dword ptr [ecx]
00771c9e mov dword ptr [ebp - 0x4c], eax
00771ca1 test eax, eax
00771ca3 je 0x771cc1
00771ca5 mov dword ptr [ebp - 0x58], ecx
00771ca8 lea ecx, [ebp - 0x58]
00771cab push ecx
00771cac lea ecx, [eax + 0x324]
00771cb2 call 0x4bc3c0
00771cb7 mov dword ptr [edi + 0x1eb8], 0
00771cc1 push 0x6d
00771cc3 lea ecx, [edi + 0x1450]
00771cc9 call 0x88b870
00771cce mov dword ptr [ebp - 0x74], eax
00771cd1 test eax, eax
00771cd3 je 0x771ce6
00771cd5 movq xmm0, qword ptr [eax]
00771cd9 mov ecx, dword ptr [eax + 8]
00771cdc movq qword ptr [ebp - 0x80], xmm0
00771ce1 mov dword ptr [ebp - 0x78], ecx
00771ce4 jmp 0x771d1d
00771ce6 mov eax, dword ptr [0xbfd680]
00771ceb mov ecx, dword ptr [eax + 0x29e9c]
00771cf1 mov eax, dword ptr [eax + 0x29ea0]
00771cf7 sub eax, ecx
00771cf9 and eax, 0xfffffffc
00771cfc cmp eax, 0x1b4
00771d01 jg 0x771d07
00771d03 xor eax, eax
00771d05 jmp 0x771d0d
00771d07 mov eax, dword ptr [ecx + 0x1b4]
00771d0d mov dword ptr [ebp - 0x80], eax
00771d10 mov eax, dword ptr [eax + 0x78]
00771d13 mov dword ptr [ebp - 0x7c], 0
00771d1a mov dword ptr [ebp - 0x78], eax
00771d1d mov ecx, dword ptr [0xbfd65c]
00771d23 lea eax, [ebp - 0x80]
00771d26 movq xmm0, qword ptr [eax]
00771d2a mov eax, dword ptr [eax + 8]
00771d2d push esi
00771d2e push edi
00771d2f lea ecx, [ecx + 0x1ba40]
00771d35 movq qword ptr [ebp - 0x8c], xmm0
00771d3d mov dword ptr [ebp - 0x84], eax
00771d43 call 0x91dea0
00771d48 mov eax, dword ptr [0xbfd65c]
00771d4d mov ecx, dword ptr [ebp - 0x68]
00771d50 mov dword ptr [eax + ecx*4 + 0x1bad8], edi
00771d57 mov eax, dword ptr [edi + 0x130c]
00771d5d cmp dword ptr [esi + 0x130c], eax
00771d63 je 0x771d6f
00771d65 push 1
00771d67 push eax
00771d68 mov ecx, esi
00771d6a call 0x78ff70
00771d6f mov eax, dword ptr [ebp - 0x4c]
00771d72 test eax, eax
00771d74 je 0x771dab
00771d76 mov edx, dword ptr [esi + 0x1eb8]
00771d7c lea ecx, [esi + 0x1eb8]
00771d82 test edx, edx
00771d84 je 0x771da1
00771d86 lea eax, [ebp - 0x58]
00771d89 mov dword ptr [ebp - 0x58], ecx
00771d8c push eax
00771d8d lea ecx, [edx + 0x324]
00771d93 call 0x4bc3c0
00771d98 mov eax, dword ptr [ebp - 0x4c]
00771d9b lea ecx, [esi + 0x1eb8]
00771da1 mov dword ptr [ecx], eax
00771da3 push ecx
00771da4 mov ecx, eax
00771da6 call 0x4bae70
00771dab push -1
00771dad push 0x6d
00771daf lea ecx, [esi + 0x1450]
00771db5 call 0x88b4e0
00771dba cmp dword ptr [ebp - 0x74], 0
00771dbe je 0x771dd6
00771dc0 push 1
00771dc2 push 1
00771dc4 lea eax, [ebp - 0x8c]
00771dca push eax
00771dcb lea ecx, [esi + 0x1450]
00771dd1 call 0x88b1c0
00771dd6 mov esi, dword ptr [edi + 0x1d0c]
00771ddc lea eax, [edi + 0x1d0c]
00771de2 xor cl, cl
00771de4 mov byte ptr [ebp - 0x41], cl
00771de7 cmp esi, dword ptr [eax + 4]
00771dea je 0x771eb6
00771df0 cmp byte ptr [esi + 4], 0
00771df4 jne 0x771e9a
00771dfa mov ecx, dword ptr [0xbfd680]
00771e00 mov eax, dword ptr [esi + 8]
00771e03 push eax
00771e04 lea ecx, [ecx + 0x29e84]
00771e0a call 0x6fe5e0
00771e0f mov dword ptr [ebp - 0x68], eax
00771e12 test eax, eax
00771e14 je 0x771e91
00771e16 cmp dword ptr [eax], 3
00771e19 je 0x771e91
00771e1b mov ecx, dword ptr [eax + 0xb8]
00771e21 and ecx, 0x8000
00771e27 or ecx, 0
00771e2a je 0x771e91
00771e2c mov edx, dword ptr [ebp - 0x48]
00771e2f mov eax, dword ptr [edi + 0x15f0]
00771e35 push esi
00771e36 mov ecx, dword ptr [edx + 0x15f0]
00771e3c mov edx, dword ptr [esi + 8]
00771e3f mov eax, dword ptr [eax + edx*4]
00771e42 mov dword ptr [ecx + edx*4], eax
00771e45 mov ecx, dword ptr [esi + 8]
00771e48 mov eax, dword ptr [edi + 0x15f0]
00771e4e mov dword ptr [eax + ecx*4], 0
00771e55 mov ecx, dword ptr [ebp - 0x48]
00771e58 lea ecx, [ecx + 0x1d0c]
00771e5e call 0x6f06b0
00771e63 push esi
00771e64 lea eax, [ebp - 0x74]
00771e67 push eax
00771e68 lea ecx, [edi + 0x1d0c]
00771e6e call 0x6f0c00
00771e73 mov ecx, dword ptr [ebp - 0x48]
00771e76 mov esi, dword ptr [eax]
00771e78 mov eax, dword ptr [ebp - 0x68]
00771e7b mov eax, dword ptr [eax + 0x54]
00771e7e or dword ptr [ecx + 0x14b8], eax
00771e84 mov cl, 1
00771e86 mov byte ptr [ebp - 0x41], cl
00771e89 lea eax, [edi + 0x1d0c]
00771e8f jmp 0x771e9d
00771e91 mov cl, byte ptr [ebp - 0x41]
00771e94 lea eax, [edi + 0x1d0c]
00771e9a add esi, 0x1c
00771e9d cmp esi, dword ptr [eax + 4]
00771ea0 jne 0x771df0
00771ea6 mov esi, dword ptr [ebp - 0x48]
00771ea9 test cl, cl
00771eab je 0x771eb9
00771ead mov byte ptr [esi + 0x1460], 1
00771eb4 jmp 0x771eb9
00771eb6 mov esi, dword ptr [ebp - 0x48]
00771eb9 call 0x6c3d90
00771ebe push eax
00771ebf push 0
00771ec1 push 0
00771ec3 push 0xc02fec
00771ec8 lea ecx, [edi + 0x294]
00771ece push ecx
00771ecf mov ecx, dword ptr [0xbfd65c]
00771ed5 push 0xf
00771ed7 push 0x3e8
00771edc call 0x422e20
00771ee1 mov ecx, eax
00771ee3 mov edx, dword ptr [eax]
00771ee5 call dword ptr [edx + 0xc]
00771ee8 mov ecx, dword ptr [ebp - 0x60]
00771eeb mov eax, dword ptr [ecx + esi + 0x14c4]
00771ef2 cmp eax, dword ptr [ecx + edi + 0x14c4]
00771ef9 je 0x771f10
00771efb test eax, eax
00771efd je 0x771f10
00771eff push 1
00771f01 push 0
00771f03 push 1
00771f05 push eax
00771f06 mov ecx, esi
00771f08 call 0x756580
00771f0d mov ecx, dword ptr [ebp - 0x60]
00771f10 movups xmm0, xmmword ptr [ecx + edi + 0x14c4]
00771f18 push 0xb44128
00771f1d push 0xb449a0
00771f22 movups xmmword ptr [ecx + esi + 0x14c4], xmm0
00771f2a push 0x2bf
00771f2f movq xmm0, qword ptr [ecx + edi + 0x14d4]
00771f38 movq qword ptr [ecx + esi + 0x14d4], xmm0
00771f41 mov eax, dword ptr [ecx + edi + 0x14dc]
00771f48 mov dword ptr [ecx + esi + 0x14dc], eax
00771f4f mov ecx, esi
00771f51 call 0x770300
00771f56 push -1
00771f58 push esi
00771f59 mov ecx, edi
00771f5b call 0x7259b0
00771f60 push 0
00771f62 push 0x248
00771f67 mov ecx, edi
00771f69 mov byte ptr [esi + 0x360], 1
00771f70 mov dword ptr [esi + 0x364], 1
00771f7a call 0x73af30
00771f7f test al, al
00771f81 jne 0x771f95
00771f83 push 0
00771f85 push 0x248
00771f8a mov ecx, esi
00771f8c call 0x73af30
00771f91 test al, al
00771f93 je 0x771fac
00771f95 push 0
00771f97 push 0
00771f99 lea eax, [edi + 0x294]
00771f9f mov ecx, esi
00771fa1 push eax
00771fa2 push 0x2bf
00771fa7 call 0x5b4730
00771fac mov ecx, esi
00771fae call 0x76d1f0
00771fb3 mov eax, dword ptr [ebp - 0x50]
00771fb6 push dword ptr [ebp - 0x5c]
00771fb9 mov ecx, edi
00771fbb push dword ptr [ebx + 0xc]
00771fbe push eax
00771fbf call 0x770f40
00771fc4 cmp dword ptr [ebp - 0x50], 3
00771fc8 jne 0x771fd7
00771fca push 0
00771fcc push 3
00771fce push 0
00771fd0 mov ecx, edi
00771fd2 call 0x795d50
00771fd7 mov ecx, dword ptr [ebp - 0xc]
00771fda mov dword ptr fs:[0], ecx
00771fe1 pop ecx
00771fe2 pop edi
00771fe3 pop esi
00771fe4 mov ecx, dword ptr [ebp - 0x14]
00771fe7 xor ecx, ebp
00771fe9 call 0x9eacd7
00771fee mov esp, ebp
00771ff0 pop ebp
00771ff1 mov esp, ebx
00771ff3 pop ebx
00771ff4 ret 8
00771ff7 cmp eax, 0x2c7
00771ffc jne 0x771fb3
