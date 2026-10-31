; Repentance1.7.9b bounded native evidence. Candidate names are interpretations, not exported symbols.
004bba40 push ebp
004bba41 mov ebp, esp
004bba43 and esp, 0xfffffff8
004bba46 sub esp, 0x44
004bba49 mov eax, dword ptr [0xbaa3b4] ; f32=-0.00294341473
004bba4e xor eax, esp
004bba50 mov dword ptr [esp + 0x40], eax
004bba54 push ebx
004bba55 push esi
004bba56 push edi
004bba57 mov edi, ecx
004bba59 mov eax, dword ptr [edi + 0xab4]
004bba5f mov ebx, dword ptr [edi + 0x2c]
004bba62 test eax, eax
004bba64 jne 0x4bbac5
004bba66 cmp ebx, 0xa
004bba69 mov eax, 4
004bba6e mov ecx, 0x10
004bba73 cmove eax, ecx
004bba76 mov dword ptr [edi + 0xab4], eax
004bba7c jne 0x4bba96
004bba7e mov eax, dword ptr [edi + 0x294]
004bba84 mov dword ptr [edi + 0x28c], eax
004bba8a mov eax, dword ptr [edi + 0x298]
004bba90 mov dword ptr [edi + 0x290], eax
004bba96 mov ecx, dword ptr [edi + 0x160]
004bba9c and ecx, 0xfffffffb
004bba9f mov byte ptr [edi + 0x308], 1
004bbaa6 or ecx, 1
004bbaa9 mov dword ptr [edi + 0x360], 0
004bbab3 or dword ptr [edi + 0x164], 0x10
004bbaba mov dword ptr [edi + 0x160], ecx
004bbac0 jmp 0x4bc01a
004bbac5 cmp eax, 0x10
004bbac8 jne 0x4bbaff
004bbaca movss xmm1, dword ptr [edi + 0x28c]
004bbad2 movss xmm0, dword ptr [edi + 0x290]
004bbada subss xmm1, dword ptr [edi + 0x294]
004bbae2 subss xmm0, dword ptr [edi + 0x298]
004bbaea movss dword ptr [edi + 0x2b8], xmm1
004bbaf2 movss dword ptr [edi + 0x2bc], xmm0
004bbafa jmp 0x4bc01a
004bbaff cmp eax, 4
004bbb02 jne 0x4bc004
004bbb08 cmp ebx, 0xa
004bbb0b jne 0x4bbd5a
004bbb11 movss xmm0, dword ptr [edi + 0xb08]
004bbb19 comiss xmm0, dword ptr [0xb6a560] ; f32=0.800000012
004bbb20 mov dword ptr [edi + 0x2d4], 0x42c80000
004bbb2a mov dword ptr [edi + 0x180], eax
004bbb30 jbe 0x4bbccb
004bbb36 movss xmm1, dword ptr [0xb6a7b0] ; f32=2
004bbb3e xorps xmm2, xmm2
004bbb41 call 0x6847e0
004bbb46 test eax, eax
004bbb48 je 0x4bbccb
004bbb4e call 0x6c3d90
004bbb53 mov esi, eax
004bbb55 lea eax, [esp + 0x14]
004bbb59 push eax
004bbb5a call 0x659290
004bbb5f movss xmm0, dword ptr [edi + 0x2b8]
004bbb67 add esp, 4
004bbb6a mulss xmm0, dword ptr [0xb6a350] ; f32=0.200000003
004bbb72 mov ecx, dword ptr [0xbfd65c]
004bbb78 push 0
004bbb7a addss xmm0, dword ptr [eax]
004bbb7e push esi
004bbb7f push 0
004bbb81 push edi
004bbb82 movss dword ptr [esp + 0x1c], xmm0
004bbb88 movss xmm0, dword ptr [edi + 0x2bc]
004bbb90 mulss xmm0, dword ptr [0xb6a350] ; f32=0.200000003
004bbb98 addss xmm0, dword ptr [eax + 4]
004bbb9d lea eax, [esp + 0x1c]
004bbba1 push eax
004bbba2 lea eax, [edi + 0x294]
004bbba8 push eax
004bbba9 push 0x3b
004bbbab push 0x3e8
004bbbb0 movss dword ptr [esp + 0x30], xmm0
004bbbb6 call 0x6d0ca0
004bbbbb mov esi, eax
004bbbbd call 0x6c3d90
004bbbc2 movd xmm0, eax
004bbbc6 cvtdq2pd xmm0, xmm0
004bbbca shr eax, 0x1f
004bbbcd addsd xmm0, qword ptr [eax*8 + 0xb6c940]
004bbbd6 cvtpd2ps xmm0, xmm0
004bbbda mulss xmm0, dword ptr [0xb6a19c] ; f32=2.32830644e-10
004bbbe2 mulss xmm0, dword ptr [0xb6a974] ; f32=10
004bbbea addss xmm0, dword ptr [0xb6a7b0] ; f32=2
004bbbf2 movss dword ptr [esi + 0x3c4], xmm0
004bbbfa call 0x6c3d90
004bbbff mov ecx, 0xf
004bbc04 movss xmm3, dword ptr [0xb6a468] ; f32=0.449999988
004bbc0c xor edx, edx
004bbc0e movaps xmm2, xmm3
004bbc11 div ecx
004bbc13 push 1
004bbc15 push 0
004bbc17 push 0xff
004bbc1c add edx, ecx
004bbc1e movaps xmm1, xmm3
004bbc21 push -1
004bbc23 push ecx
004bbc24 mov dword ptr [esi + 0x3ac], edx
004bbc2a lea ecx, [esp + 0x34]
004bbc2e mov dword ptr [esi + 0x3b0], edx
004bbc34 mov edx, dword ptr [esi]
004bbc36 mov dword ptr [esp], 0x3f000000
004bbc3d call 0x4325d0
004bbc42 push eax
004bbc43 mov ecx, esi
004bbc45 call dword ptr [edx + 0x38]
004bbc48 call 0x6c3d90
004bbc4d movd xmm0, eax
004bbc51 cvtdq2pd xmm0, xmm0
004bbc55 shr eax, 0x1f
004bbc58 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
004bbc61 mov eax, dword ptr [0xbfd65c]
004bbc66 cvtpd2ps xmm1, xmm0
004bbc6a mulss xmm1, dword ptr [0xb6a19c] ; f32=2.32830644e-10
004bbc72 mulss xmm1, dword ptr [0xb6a3b0] ; f32=0.300000012
004bbc7a addss xmm1, dword ptr [0xb6a3b0] ; f32=0.300000012
004bbc82 movaps xmm0, xmm1
004bbc85 mulss xmm1, dword ptr [0xbc7a2c] ; f32=1
004bbc8d mulss xmm0, dword ptr [0xbc7a28] ; f32=1
004bbc95 movss dword ptr [esi + 0xdc], xmm1
004bbc9d movss dword ptr [esi + 0xd8], xmm0
004bbca5 cmp dword ptr [eax + 0x1b6c0], 0
004bbcac je 0x4bbcc4
004bbcae mov eax, dword ptr [esi + 0x160]
004bbcb4 or dword ptr [esi + 0x164], 0x1000
004bbcbe mov dword ptr [esi + 0x160], eax
004bbcc4 mov eax, dword ptr [esi]
004bbcc6 mov ecx, esi
004bbcc8 call dword ptr [eax + 0xc]
004bbccb lea eax, [esp + 0xc]
004bbccf mov byte ptr [edi + 0x169], 1
004bbcd6 push eax
004bbcd7 lea ecx, [edi + 0xb00]
004bbcdd mov dword ptr [edi + 0x2c4], 0x3f666666
004bbce7 call 0x962560
004bbcec movss xmm2, dword ptr [edi + 0xb08]
004bbcf4 movss xmm0, dword ptr [eax]
004bbcf8 mulss xmm0, dword ptr [0xb6a690] ; f32=1.29999995
004bbd00 movss xmm3, dword ptr [eax + 4]
004bbd05 mulss xmm3, dword ptr [0xb6a690] ; f32=1.29999995
004bbd0d mulss xmm0, xmm2
004bbd11 mulss xmm3, xmm2
004bbd15 addss xmm0, dword ptr [edi + 0x2b8]
004bbd1d addss xmm3, dword ptr [edi + 0x2bc]
004bbd25 movss dword ptr [edi + 0x2b8], xmm0
004bbd2d movss xmm0, dword ptr [edi + 0xb08]
004bbd35 mulss xmm0, dword ptr [0xb6a61c] ; f32=1.01999998
004bbd3d movss dword ptr [edi + 0x2bc], xmm3
004bbd45 addss xmm0, dword ptr [0xb6a214] ; f32=0.00999999978
004bbd4d movss dword ptr [edi + 0xb08], xmm0
004bbd55 jmp 0x4bbe1f
004bbd5a mov eax, dword ptr [edi + 0x318]
004bbd60 test eax, eax
004bbd62 je 0x4bbd7b
004bbd64 mov dword ptr [edi + 0x2d4], 0x461c4000
004bbd6e cmp dword ptr [eax + 0x180], 0
004bbd75 je 0x4bbd85
004bbd77 xor ecx, ecx
004bbd79 jmp 0x4bbd8a
004bbd7b mov dword ptr [edi + 0x2d4], 0x42480000
004bbd85 mov ecx, 4
004bbd8a mov al, 1
004bbd8c mov dword ptr [edi + 0x180], ecx
004bbd92 mov byte ptr [edi + 0x169], al
004bbd98 mov eax, dword ptr [edi + 0x318]
004bbd9e test eax, eax
004bbda0 je 0x4bbe0f
004bbda2 lea eax, [esp + 0xc]
004bbda6 push eax
004bbda7 lea ecx, [edi + 0xb00]
004bbdad call 0x962560
004bbdb2 movss xmm2, dword ptr [edi + 0xb08]
004bbdba movss xmm3, dword ptr [eax + 4]
004bbdbf movss xmm0, dword ptr [eax]
004bbdc3 mulss xmm0, dword ptr [0xb6a690] ; f32=1.29999995
004bbdcb mulss xmm3, dword ptr [0xb6a690] ; f32=1.29999995
004bbdd3 mulss xmm0, xmm2
004bbdd7 mulss xmm3, xmm2
004bbddb addss xmm0, dword ptr [edi + 0x2b8]
004bbde3 addss xmm3, dword ptr [edi + 0x2bc]
004bbdeb movss dword ptr [edi + 0x2b8], xmm0
004bbdf3 movss dword ptr [edi + 0x2bc], xmm3
004bbdfb mov eax, dword ptr [edi + 0x318]
004bbe01 test eax, eax
004bbe03 je 0x4bbe0f
004bbe05 movss xmm0, dword ptr [0xb6a560] ; f32=0.800000012
004bbe0d jmp 0x4bbe17
004bbe0f movss xmm0, dword ptr [0xb6a5a4] ; f32=0.899999976
004bbe17 movss dword ptr [edi + 0x2c4], xmm0
004bbe1f mov dword ptr [edi + 0x17c], 0
004bbe29 cmp dword ptr [edi + 0x318], 0
004bbe30 jne 0x4bbe4f
004bbe32 cmp ebx, 0xa
004bbe35 je 0x4bbe4f
004bbe37 inc dword ptr [edi + 0x360]
004bbe3d cmp dword ptr [edi + 0x360], 2
004bbe44 jle 0x4bbe59
004bbe46 mov ecx, edi
004bbe48 call 0x4bc040
004bbe4d jmp 0x4bbe59
004bbe4f mov dword ptr [edi + 0x360], 0
004bbe59 mov esi, dword ptr [0xbfd65c]
004bbe5f lea eax, [edi + 0x294]
004bbe65 push ecx
004bbe66 mov dword ptr [esp], 0
004bbe6d push eax
004bbe6e mov ebx, dword ptr [esi + 0x18190]
004bbe74 mov ecx, ebx
004bbe76 call 0x7cf0a0
004bbe7b lea edx, [edi + 0x294]
004bbe81 test al, al
004bbe83 jne 0x4bbf3a
004bbe89 movss xmm2, dword ptr [edx]
004bbe8d lea eax, [esp + 0x14]
004bbe91 movss xmm3, dword ptr [ebx + 0x14]
004bbe96 lea ecx, [esp + 0x1c]
004bbe9a movss xmm0, dword ptr [ebx + 0x18]
004bbe9f subss xmm3, xmm2
004bbea3 subss xmm2, dword ptr [ebx + 0x1c]
004bbea8 movss xmm1, dword ptr [edi + 0x298]
004bbeb0 subss xmm0, xmm1
004bbeb4 subss xmm1, dword ptr [ebx + 0x20]
004bbeb9 movss dword ptr [esp + 0x14], xmm3
004bbebf comiss xmm2, xmm3
004bbec2 movss dword ptr [esp + 0x1c], xmm2
004bbec8 movss dword ptr [esp + 0xc], xmm0
004bbece cmovbe ecx, eax
004bbed1 lea eax, [esp + 0xc]
004bbed5 comiss xmm0, dword ptr [ecx]
004bbed8 cmovbe eax, ecx
004bbedb movss xmm0, dword ptr [eax]
004bbedf comiss xmm1, xmm0
004bbee2 ja 0x4bbeea
004bbee4 movss xmm0, xmm0
004bbee8 jmp 0x4bbeee
004bbeea movss xmm0, xmm1
004bbeee mov dword ptr [esp + 0xc], 0
004bbef6 lea eax, [esp + 0xc]
004bbefa lea ecx, [esp + 0x14]
004bbefe xorps xmm1, xmm1
004bbf01 subss xmm0, xmm1
004bbf05 divss xmm0, dword ptr [0xb6aa58] ; f32=48
004bbf0d comiss xmm1, xmm0
004bbf10 movss xmm1, dword ptr [0xb6a614] ; f32=1
004bbf18 movss dword ptr [esp + 0x14], xmm0
004bbf1e cmovbe eax, ecx
004bbf21 movss xmm0, dword ptr [eax]
004bbf25 comiss xmm0, xmm1
004bbf28 ja 0x4bbf30
004bbf2a movss xmm0, xmm0
004bbf2e jmp 0x4bbf34
004bbf30 movss xmm0, xmm1
004bbf34 subss xmm1, xmm0
004bbf38 jmp 0x4bbf42
004bbf3a movss xmm1, dword ptr [0xb6a614] ; f32=1
004bbf42 movss dword ptr [edi + 0xf0], xmm1
004bbf4a mov eax, dword ptr [esi + 0x1a30dc]
004bbf50 sub eax, dword ptr [edi + 0x280]
004bbf56 cmp eax, 0xf
004bbf59 jg 0x4bbf75
004bbf5b cmp dword ptr [esi + 0x1b6c0], 0
004bbf62 je 0x4bc01a
004bbf68 cmp dword ptr [esi + 0x1b6dc], 0x13
004bbf6f jne 0x4bc01a
004bbf75 mov eax, dword ptr [edi + 0x318]
004bbf7b test eax, eax
004bbf7d je 0x4bbf92
004bbf7f cmp dword ptr [eax + 0x28], 0x38a
004bbf86 jne 0x4bbf92
004bbf88 cmp dword ptr [eax + 0x2c], 0
004bbf8c je 0x4bc01a
004bbf92 cmp dword ptr [edi + 0x2c], 0xa
004bbf96 jne 0x4bbfb1
004bbf98 push ecx
004bbf99 mov dword ptr [esp], 0xc3960000
004bbfa0 mov ecx, ebx
004bbfa2 push edx
004bbfa3 call 0x7cf0a0
004bbfa8 xor ecx, ecx
004bbfaa test al, al
004bbfac sete cl
004bbfaf jmp 0x4bbfbe
004bbfb1 push edx
004bbfb2 mov ecx, ebx
004bbfb4 call 0x7ce950
004bbfb9 mov ecx, eax
004bbfbb shr ecx, 0x1f
004bbfbe test ecx, ecx
004bbfc0 je 0x4bc01a
004bbfc2 cmp dword ptr [edi + 0xab4], 0
004bbfc9 jne 0x4bbfd2
004bbfcb mov ecx, edi
004bbfcd call 0x4bba40
004bbfd2 mov ecx, dword ptr [edi + 0x318]
004bbfd8 mov dword ptr [edi + 0xab4], 3
004bbfe2 test ecx, ecx
004bbfe4 je 0x4bbfeb
004bbfe6 mov eax, dword ptr [ecx]
004bbfe8 call dword ptr [eax + 0x28]
004bbfeb mov eax, dword ptr [edi]
004bbfed mov ecx, edi
004bbfef call dword ptr [eax + 0x28]
004bbff2 pop edi
004bbff3 pop esi
004bbff4 pop ebx
004bbff5 mov ecx, dword ptr [esp + 0x40]
004bbff9 xor ecx, esp
004bbffb call 0x9eacd7
004bc000 mov esp, ebp
004bc002 pop ebp
004bc003 ret 
004bc004 cmp eax, 3
004bc007 jne 0x4bc01a
004bc009 mov dword ptr [edi + 0x180], 0
004bc013 mov byte ptr [edi + 0x169], 0
004bc01a cmp byte ptr [edi + 0x16b], 0
004bc021 je 0x4bc02a
004bc023 mov byte ptr [edi + 0x16b], 0
004bc02a mov ecx, dword ptr [esp + 0x4c]
004bc02e pop edi
004bc02f pop esi
004bc030 pop ebx
004bc031 xor ecx, esp
004bc033 call 0x9eacd7
004bc038 mov esp, ebp
004bc03a pop ebp
004bc03b ret 
