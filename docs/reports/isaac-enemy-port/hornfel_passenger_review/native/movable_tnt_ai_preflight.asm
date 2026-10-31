; Installed-binary disassembly; field interpretations require the source review.
006acb80 push ebp
006acb81 mov ebp, esp
006acb83 and esp, 0xfffffff8
006acb86 sub esp, 0xcc
006acb8c mov eax, dword ptr [0xbaa3b4]
006acb91 xor eax, esp
006acb93 mov dword ptr [esp + 0xc8], eax
006acb9a push ebx
006acb9b push esi
006acb9c push edi
006acb9d mov edi, ecx
006acb9f mov dword ptr [esp + 0x30], edi
006acba3 mov eax, dword ptr [edi + 0xab4]
006acba9 test eax, eax
006acbab jne 0x6acc1c
006acbad mov ecx, dword ptr [edi + 0x160]
006acbb3 movss xmm0, dword ptr [edi + 0x2d8]
006acbbb and ecx, 0xfffffffb
006acbbe mov eax, dword ptr [edi + 0x164]
006acbc4 or ecx, 0x20d0011
006acbca comiss xmm0, dword ptr [0xb6a614]
006acbd1 mov dword ptr [edi + 0x164], eax
006acbd7 mov eax, 0x10
006acbdc mov dword ptr [edi + 0x160], ecx
006acbe2 mov ecx, 3
006acbe7 cmova eax, ecx
006acbea cmp dword ptr [edi + 0x32c], 0
006acbf1 mov dword ptr [edi + 0xab4], eax
006acbf7 jne 0x6ad700
006acbfd mov dword ptr [edi + 0x2ac], 0x64
006acc07 pop edi
006acc08 pop esi
006acc09 pop ebx
006acc0a mov ecx, dword ptr [esp + 0xc8]
006acc11 xor ecx, esp
006acc13 call 0x9eacd7
006acc18 mov esp, ebp
006acc1a pop ebp
006acc1b ret
006acc1c movss xmm0, dword ptr [edi + 0x14]
006acc21 xorps xmm2, xmm2
006acc24 comiss xmm0, xmm2
006acc27 mov ecx, eax
006acc29 mov ebx, 3
006acc2e movss xmm4, dword ptr [0xb6a7b0]
006acc36 movss xmm3, dword ptr [0xb6a614]
006acc3e jbe 0x6acca8
006acc40 movaps xmm1, xmm3
006acc43 call 0x6c3d90
006acc48 xor edx, edx
006acc4a div ebx
006acc4c test edx, edx
006acc4e jne 0x6acc53
006acc50 movaps xmm1, xmm4
006acc53 mov eax, dword ptr [edi + 0x18]
006acc56 and eax, 4
006acc59 or eax, 0
006acc5c je 0x6acc68
006acc5e movss xmm1, dword ptr [0xb6a8cc]
006acc66 jmp 0x6acc6d
006acc68 comiss xmm1, xmm2
006acc6b jbe 0x6acc85
006acc6d movss xmm0, dword ptr [edi + 0x2d8]
006acc75 subss xmm0, xmm1
006acc79 maxss xmm0, xmm3
006acc7d movss dword ptr [edi + 0x2d8], xmm0
006acc85 mov eax, dword ptr [edi + 8]
006acc88 mov dword ptr [edi + 0xc], eax
006acc8b mov dword ptr [edi + 0x14], 0
006acc92 mov dword ptr [edi + 0x18], 0
006acc99 mov dword ptr [edi + 0x1c], 0
006acca0 mov eax, dword ptr [edi + 0xab4]
006acca6 mov ecx, eax
006acca8 cmp byte ptr [edi + 0x16b], 0
006accaf jne 0x6accbe
006accb1 comiss xmm3, dword ptr [edi + 0x2d8]
006accb8 jb 0x6ad62d
006accbe cmp ecx, 0x10
006accc1 je 0x6ad603
006accc7 call 0x6c3d90
006acccc movss xmm0, dword ptr [edi + 0x294]
006accd4 lea ecx, [edi + 0x294]
006accda mov esi, dword ptr [0xbfd65c]
006acce0 mov dword ptr [esp + 0x40], eax
006acce4 lea eax, [esp + 0x40]
006acce8 push eax
006acce9 lea eax, [esp + 0x48]
006acced movss dword ptr [esp + 0x58], xmm0
006accf3 movss xmm0, dword ptr [ecx + 4]
006accf8 push eax
006accf9 push 0
006accfb push 0xc02fec
006acd00 lea eax, [esp + 0x64]
006acd04 mov dword ptr [esp + 0x60], ecx
006acd08 push eax
006acd09 lea eax, [esp + 0x5c]
006acd0d movss dword ptr [esp + 0x6c], xmm0
006acd13 push eax
006acd14 lea eax, [esp + 0x44]
006acd18 mov dword ptr [esp + 0x5c], 0
006acd20 push eax
006acd21 mov dword ptr [esp + 0x64], 1
006acd29 mov dword ptr [esp + 0x48], 0x3e8
006acd31 call 0x800fb0
006acd36 mov ecx, dword ptr [esi + 0x1c3198]
006acd3c push 0
006acd3e push dword ptr [esp + 0x30]
006acd42 call 0x6c4b30
006acd47 mov ebx, eax
006acd49 mov dword ptr [esp + 0x18], ebx
006acd4d test ebx, ebx
006acd4f je 0x6acf54
006acd55 call dword ptr [0xa064c0]
006acd5b mov ecx, dword ptr [ebx + 0x320]
006acd61 mov dword ptr [esp + 0x14], eax
006acd65 lea eax, [ebx + 0x320]
006acd6b mov dword ptr [ebx + 0x34], 0
006acd72 mov dword ptr [ebx + 0x38], 0
006acd79 test ecx, ecx
006acd7b je 0x6acd97
006acd7d mov dword ptr [esp + 0x6c], eax
006acd81 add ecx, 0x324
006acd87 lea eax, [esp + 0x6c]
006acd8b push eax
006acd8c call 0x4bc3c0
006acd91 lea eax, [ebx + 0x320]
006acd97 push dword ptr [esp + 0x40]
006acd9b mov dword ptr [eax], 0
006acda1 mov ecx, ebx
006acda3 movss xmm0, dword ptr [esp + 0x58]
006acda9 push dword ptr [esp + 0x48]
006acdad mov eax, dword ptr [ebx]
006acdaf push dword ptr [esp + 0x50]
006acdb3 movss dword ptr [ebx + 0x294], xmm0
006acdbb movss xmm0, dword ptr [esp + 0x64]
006acdc1 push dword ptr [esp + 0x38]
006acdc5 movss dword ptr [ebx + 0x298], xmm0
006acdcd movss xmm0, dword ptr [0xc02fec]
006acdd5 movss dword ptr [ebx + 0x2b8], xmm0
006acddd movss xmm0, dword ptr [0xc02ff0]
006acde5 movss dword ptr [ebx + 0x2bc], xmm0
006acded call dword ptr [eax + 4]
006acdf0 mov edx, dword ptr [esi + 0x18190]
006acdf6 push ebx
006acdf7 mov ecx, dword ptr [edx + 0x1214]
006acdfd lea eax, [ecx + 1]
006ace00 mov dword ptr [edx + 0x1214], eax
006ace06 mov dword ptr [ebx + 0x20], ecx
006ace09 lea ecx, [edx + 0x1218]
006ace0f call 0x413280
006ace14 push ebx
006ace15 call 0x6d94d0
006ace1a test al, al
006ace1c je 0x6ace25
006ace1e push ecx
006ace1f push ebx
006ace20 call 0x6d9590
006ace25 cmp byte ptr [ebx + 0x16a], 0
006ace2c je 0x6acf44
006ace32 mov eax, dword ptr [esi + 0x283c20]
006ace38 cmp eax, dword ptr [esi + 0x283c24]
006ace3e je 0x6acf44
006ace44 mov eax, dword ptr [ebx + 0x28]
006ace47 lea ecx, [esi + 0x283c48]
006ace4d mov dword ptr [esp + 0x74], eax
006ace51 mov eax, dword ptr [ebx + 0x2c]
006ace54 mov dword ptr [esp + 0x78], eax
006ace58 lea eax, [esp + 0x74]
006ace5c push eax
006ace5d lea eax, [esp + 0x50]
006ace61 push eax
006ace62 call 0x937c80
006ace67 mov eax, dword ptr [esi + 0x283c48]
006ace6d cmp dword ptr [esp + 0x4c], eax
006ace71 jne 0x6aceaf
006ace73 mov eax, dword ptr [ebx + 0x28]
006ace76 lea ecx, [esi + 0x283c48]
006ace7c mov dword ptr [esp + 0x7c], eax
006ace80 lea eax, [esp + 0x7c]
006ace84 push eax
006ace85 lea eax, [esp + 0xa0]
006ace8c mov dword ptr [esp + 0x84], 0xffffffff
006ace97 push eax
006ace98 call 0x937c80
006ace9d mov eax, dword ptr [eax]
006ace9f mov dword ptr [esp + 0x4c], eax
006acea3 cmp eax, dword ptr [esi + 0x283c48]
006acea9 je 0x6acf44
006aceaf mov esi, dword ptr [0xbfd65c]
006aceb5 xor ebx, ebx
006aceb7 mov eax, dword ptr [esi + 0x1ba54]
006acebd sub eax, dword ptr [esi + 0x1ba50]
006acec3 sar eax, 2
006acec6 test eax, eax
006acec8 je 0x6acf44
006aceca mov edi, dword ptr [esp + 0x18]
006acece nop
006aced0 mov ecx, dword ptr [esi + 0x1ba54]
006aced6 mov eax, ecx
006aced8 sub eax, dword ptr [esi + 0x1ba50]
006acede test eax, 0xfffffffc
006acee3 jne 0x6acefa
006acee5 push 0xb3f4d0
006aceea push 3
006aceec call 0x95e330
006acef1 mov ecx, dword ptr [esi + 0x1ba54]
006acef7 add esp, 8
006acefa mov eax, dword ptr [esi + 0x1ba50]
006acf00 sub ecx, eax
006acf02 sar ecx, 2
006acf05 cmp ebx, ecx
006acf07 jae 0x6acf0c
006acf09 lea eax, [eax + ebx*4]
006acf0c push 0xc02fec
006acf11 lea ecx, [esp + 0x58]
006acf15 push ecx
006acf16 mov ecx, dword ptr [eax]
006acf18 push edi
006acf19 push 6
006acf1b add ecx, 0x1ec0
006acf21 call 0x935fd0
006acf26 mov esi, dword ptr [0xbfd65c]
006acf2c inc ebx
006acf2d mov eax, dword ptr [esi + 0x1ba54]
006acf33 sub eax, dword ptr [esi + 0x1ba50]
006acf39 sar eax, 2
006acf3c cmp ebx, eax
006acf3e jb 0x6aced0
006acf40 mov edi, dword ptr [esp + 0x30]
006acf44 call dword ptr [0xa064c0]
006acf4a sub eax, dword ptr [esp + 0x14]
006acf4e add dword ptr [0xbffe0c], eax
006acf54 mov eax, dword ptr [edi + 0x294]
006acf5a lea ebx, [edi + 0x294]
006acf60 mov ecx, dword ptr [ebx + 4]
006acf63 movss xmm2, dword ptr [0xb6a614]
006acf6b mov dword ptr [esp + 0x84], eax
006acf72 lea eax, [esp + 0x84]
006acf79 mov dword ptr [esp + 0x88], ecx
006acf80 mov ecx, dword ptr [0xbfd65c]
006acf86 push eax
006acf87 call 0x6d5600
006acf8c mov eax, dword ptr [ebx]
006acf8e movups xmm0, xmmword ptr [0xbfec58]
006acf95 mov ecx, dword ptr [ebx + 4]
006acf98 push 0
006acf9a push 0
006acf9c push 0x1004
006acfa1 sub esp, 0x10
006acfa4 mov dword ptr [esp + 0xa8], eax
006acfab mov eax, esp
006acfad mov dword ptr [esp + 0xac], ecx
006acfb4 mov ecx, dword ptr [0xbfd65c]
006acfba push 0
006acfbc push 0
006acfbe sub esp, 8
006acfc1 movups xmmword ptr [eax], xmm0
006acfc4 lea eax, [esp + 0xb8]
006acfcb mov dword ptr [esp + 4], 0x42960000
006acfd3 mov dword ptr [esp], 0x42c80000
006acfda push eax
006acfdb call 0x6d1750
006acfe0 call 0x6c3d90
006acfe5 movd xmm0, eax
006acfe9 cvtdq2pd xmm0, xmm0
006acfed shr eax, 0x1f
006acff0 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
006acff9 cvtpd2ps xmm0, xmm0
006acffd mulss xmm0, dword ptr [0xb6a19c]
006ad005 call 0x6c3d90
006ad00a mov ecx, 3
006ad00f xor edx, edx
006ad011 div ecx
006ad013 mov ecx, dword ptr [ebx + 4]
006ad016 mov eax, dword ptr [ebx]
006ad018 push 0
006ad01a push ecx
006ad01b mov dword ptr [esp + 0xa0], ecx
006ad022 lea ecx, [esp + 0xb0]
006ad029 mov dword ptr [esp + 0x9c], eax
006ad030 mov dword ptr [esp], 0x47c35000
006ad037 call 0x402120
006ad03c mulss xmm0, dword ptr [0xb6a8cc]
006ad044 push eax
006ad045 push ecx
006ad046 mov ecx, dword ptr [0xbfd65c]
006ad04c lea eax, [edx + 2]
006ad04f addss xmm0, dword ptr [0xb6a7b0]
006ad057 movss dword ptr [esp], xmm0
006ad05c push eax
006ad05d push 0x1b
006ad05f lea eax, [esp + 0xac]
006ad066 push eax
006ad067 call 0x6d57a0
006ad06c push 0
006ad06e push 1
006ad070 mov edx, ebx
006ad072 lea ecx, [esp + 0xa8]
006ad079 call 0x6c3450
006ad07e mov edx, dword ptr [edi + 0x334]
006ad084 add esp, 8
006ad087 test edx, edx
006ad089 jne 0x6ad0a5
006ad08b push 0xb4d6c4
006ad090 push 3
006ad092 call 0x95e330
006ad097 mov edx, dword ptr [edi + 0x334]
006ad09d add esp, 8
006ad0a0 test edx, edx
006ad0a2 jne 0x6ad0a5
006ad0a4 int3
006ad0a5 mov ecx, dword ptr [edi + 0x338]
006ad0ab mov eax, edx
006ad0ad shr eax, cl
006ad0af mov ecx, dword ptr [edi + 0x33c]
006ad0b5 xor eax, edx
006ad0b7 mov edx, eax
006ad0b9 shl edx, cl
006ad0bb mov ecx, dword ptr [edi + 0x340]
006ad0c1 xor edx, eax
006ad0c3 mov esi, edx
006ad0c5 mov eax, 0x51eb851f
006ad0ca shr esi, cl
006ad0cc xor esi, edx
006ad0ce mul esi
006ad0d0 mov dword ptr [edi + 0x334], esi
006ad0d6 shr edx, 5
006ad0d9 imul eax, edx, 0x64
006ad0dc sub esi, eax
006ad0de jne 0x6ad603
006ad0e4 push 2
006ad0e6 lea ecx, [edi + 0x334]
006ad0ec call 0x7a7d50
006ad0f1 mov esi, dword ptr [0xbfd65c]
006ad0f7 test eax, eax
006ad0f9 jne 0x6ad382
006ad0ff push 0x32
006ad101 lea ecx, [esi + 0x1a5cc]
006ad107 call 0x701d40
006ad10c test al, al
006ad10e je 0x6ad382
006ad114 push 0
006ad116 push 1
006ad118 mov edx, ebx
006ad11a lea ecx, [esp + 0x2c]
006ad11e call 0x6c3450
006ad123 mov esi, dword ptr [0xbfd65c]
006ad129 add esp, 8
006ad12c call 0x6c3d90
006ad131 mov dword ptr [esp + 0x1c], eax
006ad135 lea eax, [esp + 0x1c]
006ad139 push eax
006ad13a lea eax, [esp + 0x24]
006ad13e mov dword ptr [esp + 0x24], 0x32
006ad146 push eax
006ad147 push 0
006ad149 lea eax, [esp + 0x30]
006ad14d mov dword ptr [esp + 0x20], 0x15e
006ad155 push eax
006ad156 push ebx
006ad157 lea eax, [esp + 0x28]
006ad15b mov dword ptr [esp + 0x24], 5
006ad163 push eax
006ad164 lea eax, [esp + 0x28]
006ad168 push eax
006ad169 call 0x800fb0
006ad16e mov ecx, dword ptr [esi + 0x1c3198]
006ad174 push 0
006ad176 push dword ptr [esp + 0x14]
006ad17a call 0x6c4b30
006ad17f mov ebx, eax
006ad181 mov dword ptr [esp + 0x38], ebx
006ad185 test ebx, ebx
006ad187 je 0x6ad603
006ad18d call dword ptr [0xa064c0]
006ad193 mov ecx, dword ptr [ebx + 0x320]
006ad199 mov dword ptr [esp + 0x3c], eax
006ad19d lea eax, [ebx + 0x320]
006ad1a3 mov dword ptr [ebx + 0x34], 0
006ad1aa mov dword ptr [ebx + 0x38], 0
006ad1b1 test ecx, ecx
006ad1b3 je 0x6ad1cf
006ad1b5 mov dword ptr [esp + 0x34], eax
006ad1b9 add ecx, 0x324
006ad1bf lea eax, [esp + 0x34]
006ad1c3 push eax
006ad1c4 call 0x4bc3c0
006ad1c9 lea eax, [ebx + 0x320]
006ad1cf push dword ptr [esp + 0x1c]
006ad1d3 movss xmm0, dword ptr [esp + 0x28]
006ad1d9 mov ecx, ebx
006ad1db push dword ptr [esp + 0x24]
006ad1df mov dword ptr [eax], 0
006ad1e5 mov eax, dword ptr [edi + 0x294]
006ad1eb push dword ptr [esp + 0x1c]
006ad1ef mov dword ptr [ebx + 0x294], eax
006ad1f5 mov eax, dword ptr [edi + 0x298]
006ad1fb push dword ptr [esp + 0x1c]
006ad1ff mov dword ptr [ebx + 0x298], eax
006ad205 mov eax, dword ptr [ebx]
006ad207 movss dword ptr [ebx + 0x2b8], xmm0
006ad20f movss xmm0, dword ptr [esp + 0x38]
006ad215 movss dword ptr [ebx + 0x2bc], xmm0
006ad21d call dword ptr [eax + 4]
006ad220 mov edx, dword ptr [esi + 0x18190]
006ad226 push ebx
006ad227 mov ecx, dword ptr [edx + 0x1214]
006ad22d lea eax, [ecx + 1]
006ad230 mov dword ptr [edx + 0x1214], eax
006ad236 mov dword ptr [ebx + 0x20], ecx
006ad239 lea ecx, [edx + 0x1218]
006ad23f call 0x413280
006ad244 push ebx
006ad245 call 0x6d94d0
006ad24a test al, al
006ad24c je 0x6ad255
006ad24e push ecx
006ad24f push ebx
006ad250 call 0x6d9590
006ad255 cmp byte ptr [ebx + 0x16a], 0
006ad25c je 0x6ad373
006ad262 mov eax, dword ptr [esi + 0x283c20]
006ad268 cmp eax, dword ptr [esi + 0x283c24]
006ad26e je 0x6ad373
006ad274 mov eax, dword ptr [ebx + 0x28]
006ad277 lea ecx, [esi + 0x283c48]
006ad27d mov dword ptr [esp + 0x5c], eax
006ad281 mov eax, dword ptr [ebx + 0x2c]
006ad284 mov dword ptr [esp + 0x60], eax
006ad288 lea eax, [esp + 0x5c]
006ad28c push eax
006ad28d lea eax, [esp + 0x1c]
006ad291 push eax
006ad292 call 0x937c80
006ad297 mov eax, dword ptr [esi + 0x283c48]
006ad29d cmp dword ptr [esp + 0x18], eax
006ad2a1 jne 0x6ad2d9
006ad2a3 mov eax, dword ptr [ebx + 0x28]
006ad2a6 lea ecx, [esi + 0x283c48]
006ad2ac mov dword ptr [esp + 0x64], eax
006ad2b0 lea eax, [esp + 0x64]
006ad2b4 push eax
006ad2b5 lea eax, [esp + 0x74]
006ad2b9 mov dword ptr [esp + 0x6c], 0xffffffff
006ad2c1 push eax
006ad2c2 call 0x937c80
006ad2c7 mov eax, dword ptr [eax]
006ad2c9 mov dword ptr [esp + 0x18], eax
006ad2cd cmp eax, dword ptr [esi + 0x283c48]
006ad2d3 je 0x6ad373
006ad2d9 mov esi, dword ptr [0xbfd65c]
006ad2df xor ebx, ebx
006ad2e1 mov eax, dword ptr [esi + 0x1ba54]
006ad2e7 sub eax, dword ptr [esi + 0x1ba50]
006ad2ed sar eax, 2
006ad2f0 test eax, eax
006ad2f2 je 0x6ad373
006ad2f4 mov edi, dword ptr [esp + 0x38]
006ad2f8 nop dword ptr [eax + eax]
006ad300 mov ecx, dword ptr [esi + 0x1ba54]
006ad306 mov eax, ecx
006ad308 sub eax, dword ptr [esi + 0x1ba50]
006ad30e test eax, 0xfffffffc
006ad313 jne 0x6ad32a
006ad315 push 0xb3f4d0
006ad31a push 3
006ad31c call 0x95e330
006ad321 mov ecx, dword ptr [esi + 0x1ba54]
006ad327 add esp, 8
006ad32a mov eax, dword ptr [esi + 0x1ba50]
006ad330 sub ecx, eax
006ad332 sar ecx, 2
006ad335 cmp ebx, ecx
006ad337 jae 0x6ad33c
006ad339 lea eax, [eax + ebx*4]
006ad33c lea ecx, [esp + 0x24]
006ad340 push ecx
006ad341 push dword ptr [esp + 0x54]
006ad345 mov ecx, dword ptr [eax]
006ad347 push edi
006ad348 push 6
006ad34a add ecx, 0x1ec0
006ad350 call 0x935fd0
006ad355 mov esi, dword ptr [0xbfd65c]
006ad35b inc ebx
006ad35c mov eax, dword ptr [esi + 0x1ba54]
006ad362 sub eax, dword ptr [esi + 0x1ba50]
006ad368 sar eax, 2
006ad36b cmp ebx, eax
006ad36d jb 0x6ad300
006ad36f mov edi, dword ptr [esp + 0x30]
006ad373 call dword ptr [0xa064c0]
006ad379 sub eax, dword ptr [esp + 0x3c]
006ad37d jmp 0x6ad5fd
006ad382 push 0x29
006ad384 lea ecx, [esi + 0x1a5cc]
006ad38a call 0x701d40
006ad38f test al, al
006ad391 je 0x6ad603
006ad397 push 0
006ad399 push 1
006ad39b mov edx, ebx
006ad39d lea ecx, [esp + 0x2c]
006ad3a1 call 0x6c3450
006ad3a6 mov esi, dword ptr [0xbfd65c]
006ad3ac add esp, 8
006ad3af call 0x6c3d90
006ad3b4 mov dword ptr [esp + 0x18], eax
006ad3b8 lea eax, [esp + 0x18]
006ad3bc push eax
006ad3bd lea eax, [esp + 0x18]
006ad3c1 mov dword ptr [esp + 0x18], 0x29
006ad3c9 push eax
006ad3ca push 0
006ad3cc lea eax, [esp + 0x30]
006ad3d0 mov dword ptr [esp + 0x2c], 0x15e
006ad3d8 push eax
006ad3d9 push ebx
006ad3da lea eax, [esp + 0x34]
006ad3de mov dword ptr [esp + 0x24], 5
006ad3e6 push eax
006ad3e7 lea eax, [esp + 0x28]
006ad3eb push eax
006ad3ec call 0x800fb0
006ad3f1 mov ecx, dword ptr [esi + 0x1c3198]
006ad3f7 push 0
006ad3f9 push dword ptr [esp + 0x14]
006ad3fd call 0x6c4b30
006ad402 mov ebx, eax
006ad404 mov dword ptr [esp + 0x38], ebx
006ad408 test ebx, ebx
006ad40a je 0x6ad603
006ad410 call dword ptr [0xa064c0]
006ad416 mov ecx, dword ptr [ebx + 0x320]
006ad41c mov dword ptr [esp + 0x34], eax
006ad420 lea eax, [ebx + 0x320]
006ad426 mov dword ptr [ebx + 0x34], 0
006ad42d mov dword ptr [ebx + 0x38], 0
006ad434 test ecx, ecx
006ad436 je 0x6ad452
006ad438 mov dword ptr [esp + 0x3c], eax
006ad43c add ecx, 0x324
006ad442 lea eax, [esp + 0x3c]
006ad446 push eax
006ad447 call 0x4bc3c0
006ad44c lea eax, [ebx + 0x320]
006ad452 push dword ptr [esp + 0x18]
006ad456 movss xmm0, dword ptr [esp + 0x28]
006ad45c mov ecx, ebx
006ad45e push dword ptr [esp + 0x18]
006ad462 mov dword ptr [eax], 0
006ad468 mov eax, dword ptr [edi + 0x294]
006ad46e push dword ptr [esp + 0x28]
006ad472 mov dword ptr [ebx + 0x294], eax
006ad478 mov eax, dword ptr [edi + 0x298]
006ad47e push dword ptr [esp + 0x1c]
006ad482 mov dword ptr [ebx + 0x298], eax
006ad488 mov eax, dword ptr [ebx]
006ad48a movss dword ptr [ebx + 0x2b8], xmm0
006ad492 movss xmm0, dword ptr [esp + 0x38]
006ad498 movss dword ptr [ebx + 0x2bc], xmm0
006ad4a0 call dword ptr [eax + 4]
006ad4a3 mov edx, dword ptr [esi + 0x18190]
006ad4a9 push ebx
006ad4aa mov ecx, dword ptr [edx + 0x1214]
006ad4b0 lea eax, [ecx + 1]
006ad4b3 mov dword ptr [edx + 0x1214], eax
006ad4b9 mov dword ptr [ebx + 0x20], ecx
006ad4bc lea ecx, [edx + 0x1218]
006ad4c2 call 0x413280
006ad4c7 push ebx
006ad4c8 call 0x6d94d0
006ad4cd test al, al
006ad4cf je 0x6ad4d8
006ad4d1 push ecx
006ad4d2 push ebx
006ad4d3 call 0x6d9590
006ad4d8 cmp byte ptr [ebx + 0x16a], 0
006ad4df je 0x6ad5f3
006ad4e5 mov eax, dword ptr [esi + 0x283c20]
006ad4eb cmp eax, dword ptr [esi + 0x283c24]
006ad4f1 je 0x6ad5f3
006ad4f7 mov eax, dword ptr [ebx + 0x28]
006ad4fa lea ecx, [esi + 0x283c48]
006ad500 mov dword ptr [esp + 0x64], eax
006ad504 mov eax, dword ptr [ebx + 0x2c]
006ad507 mov dword ptr [esp + 0x68], eax
006ad50b lea eax, [esp + 0x64]
006ad50f push eax
006ad510 lea eax, [esp + 0x20]
006ad514 push eax
006ad515 call 0x937c80
006ad51a mov eax, dword ptr [esi + 0x283c48]
006ad520 cmp dword ptr [esp + 0x1c], eax
006ad524 jne 0x6ad55c
006ad526 mov eax, dword ptr [ebx + 0x28]
006ad529 lea ecx, [esi + 0x283c48]
006ad52f mov dword ptr [esp + 0x5c], eax
006ad533 lea eax, [esp + 0x5c]
006ad537 push eax
006ad538 lea eax, [esp + 0x74]
006ad53c mov dword ptr [esp + 0x64], 0xffffffff
006ad544 push eax
006ad545 call 0x937c80
006ad54a mov eax, dword ptr [eax]
006ad54c mov dword ptr [esp + 0x1c], eax
006ad550 cmp eax, dword ptr [esi + 0x283c48]
006ad556 je 0x6ad5f3
006ad55c mov esi, dword ptr [0xbfd65c]
006ad562 xor ebx, ebx
006ad564 mov eax, dword ptr [esi + 0x1ba54]
006ad56a sub eax, dword ptr [esi + 0x1ba50]
006ad570 sar eax, 2
006ad573 test eax, eax
006ad575 je 0x6ad5f3
006ad577 mov edi, dword ptr [esp + 0x38]
006ad57b nop dword ptr [eax + eax]
006ad580 mov ecx, dword ptr [esi + 0x1ba54]
006ad586 mov eax, ecx
006ad588 sub eax, dword ptr [esi + 0x1ba50]
006ad58e test eax, 0xfffffffc
006ad593 jne 0x6ad5aa
006ad595 push 0xb3f4d0
006ad59a push 3
006ad59c call 0x95e330
006ad5a1 mov ecx, dword ptr [esi + 0x1ba54]
006ad5a7 add esp, 8
006ad5aa mov eax, dword ptr [esi + 0x1ba50]
006ad5b0 sub ecx, eax
006ad5b2 sar ecx, 2
006ad5b5 cmp ebx, ecx
006ad5b7 jae 0x6ad5bc
006ad5b9 lea eax, [eax + ebx*4]
006ad5bc lea ecx, [esp + 0x24]
006ad5c0 push ecx
006ad5c1 push dword ptr [esp + 0x54]
006ad5c5 mov ecx, dword ptr [eax]
006ad5c7 push edi
006ad5c8 push 6
006ad5ca add ecx, 0x1ec0
006ad5d0 call 0x935fd0
006ad5d5 mov esi, dword ptr [0xbfd65c]
006ad5db inc ebx
006ad5dc mov eax, dword ptr [esi + 0x1ba54]
006ad5e2 sub eax, dword ptr [esi + 0x1ba50]
006ad5e8 sar eax, 2
006ad5eb cmp ebx, eax
006ad5ed jb 0x6ad580
006ad5ef mov edi, dword ptr [esp + 0x30]
006ad5f3 call dword ptr [0xa064c0]
006ad5f9 sub eax, dword ptr [esp + 0x34]
006ad5fd add dword ptr [0xbffe0c], eax
006ad603 cmp dword ptr [edi + 0x32c], 0
006ad60a je 0x6ad6b4
006ad610 mov eax, dword ptr [edi]
006ad612 mov ecx, edi
006ad614 call dword ptr [eax + 0x28]
006ad617 mov eax, dword ptr [edi + 0xab4]
006ad61d movss xmm3, dword ptr [0xb6a614]
006ad625 movss xmm4, dword ptr [0xb6a7b0]
006ad62d cmp eax, 3
006ad630 jne 0x6ad6ad
006ad632 movss xmm0, dword ptr [edi + 0x2d8]
006ad63a comiss xmm0, dword ptr [0xb6a864]
006ad641 jbe 0x6ad64c
006ad643 push 0
006ad645 push 0xb3fd8c
006ad64a jmp 0x6ad666
006ad64c comiss xmm0, xmm4
006ad64f jbe 0x6ad65a
006ad651 push 0
006ad653 push 0xb49290
006ad658 jmp 0x6ad666
006ad65a comiss xmm0, xmm3
006ad65d jbe 0x6ad66e
006ad65f push 0
006ad661 push 0xb4929c
006ad666 lea ecx, [edi + 0x3c]
006ad669 call 0x4054f0
006ad66e movss xmm0, dword ptr [edi + 0x2c4]
006ad676 mulss xmm0, dword ptr [0xb6a560]
006ad67e mov eax, dword ptr [edi + 0xb10]
006ad684 movss dword ptr [edi + 0x2c4], xmm0
006ad68c cmp eax, -4
006ad68f jle 0x6ad700
006ad691 dec eax
006ad692 mov dword ptr [edi + 0xb10], eax
006ad698 pop edi
006ad699 pop esi
006ad69a pop ebx
006ad69b mov ecx, dword ptr [esp + 0xc8]
006ad6a2 xor ecx, esp
006ad6a4 call 0x9eacd7
006ad6a9 mov esp, ebp
006ad6ab pop ebp
006ad6ac ret
006ad6ad cmp eax, 0x10
006ad6b0 jne 0x6ad700
006ad6b2 jmp 0x6ad6cf
006ad6b4 mov byte ptr [edi + 0x16b], 0
006ad6bb mov dword ptr [edi + 0xab4], 0x10
006ad6c5 mov dword ptr [edi + 0x2d8], 0x3f000000
006ad6cf push 0
006ad6d1 push 0xb492ac
006ad6d6 lea ecx, [edi + 0x3c]
006ad6d9 mov dword ptr [edi + 0x180], 0
006ad6e3 call 0x4054f0
006ad6e8 movss xmm0, dword ptr [edi + 0x2c4]
006ad6f0 mulss xmm0, dword ptr [0xb6a3b0]
006ad6f8 movss dword ptr [edi + 0x2c4], xmm0
006ad700 mov ecx, dword ptr [esp + 0xd4]
006ad707 pop edi
006ad708 pop esi
006ad709 pop ebx
006ad70a xor ecx, esp
006ad70c call 0x9eacd7
006ad711 mov esp, ebp
006ad713 pop ebp
006ad714 ret
