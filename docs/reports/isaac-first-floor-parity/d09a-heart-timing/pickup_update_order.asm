006bb274 mov ecx, edi
006bb276 call 0x6860a0
006bb27b mov ecx, dword ptr [edi + 0x2c]
006bb27e call 0x6c3350
006bb283 movss xmm2, dword ptr [0xb6a560]
006bb28b test al, al
006bb28d je 0x6bb2c7
006bb28f mov ecx, dword ptr [edi + 0x164]
006bb295 xor eax, eax
006bb297 and ecx, 0x4000000
006bb29d or eax, ecx
006bb29f jne 0x6bb34b
006bb2a5 movss xmm0, dword ptr [edi + 0x2b8]
006bb2ad mulss xmm0, xmm2
006bb2b1 movss dword ptr [edi + 0x2b8], xmm0
006bb2b9 movss xmm0, dword ptr [edi + 0x2bc]
006bb2c1 mulss xmm0, xmm2
006bb2c5 jmp 0x6bb343
006bb2c7 cmp ecx, 0x154
006bb2cd je 0x6bb2d7
006bb2cf cmp ecx, 0x172
006bb2d5 jne 0x6bb34b
006bb2d7 movss xmm0, dword ptr [edi + 0x2b8]
006bb2df mulss xmm0, dword ptr [0xb6a4c4]
006bb2e7 movss dword ptr [edi + 0x2b8], xmm0
006bb2ef movss xmm0, dword ptr [edi + 0x2bc]
006bb2f7 mulss xmm0, dword ptr [0xb6a4c4]
006bb2ff movss dword ptr [edi + 0x2bc], xmm0
006bb307 movss xmm1, dword ptr [edi + 0x28c]
006bb30f subss xmm1, dword ptr [edi + 0x294]
006bb317 movss xmm0, dword ptr [edi + 0x290]
006bb31f subss xmm0, dword ptr [edi + 0x298]
006bb327 mov dword ptr [edi + 0x2cc], 0x40000000
006bb331 mov dword ptr [edi + 0x2d0], 0x3f800000
006bb33b movss dword ptr [edi + 0x2b8], xmm1
006bb343 movss dword ptr [edi + 0x2bc], xmm0
006bb34b cmp dword ptr [edi + 0x2c], 0x64
006bb34f jne 0x6bb460
006bb355 movss xmm0, dword ptr [edi + 0x2c4]
006bb35d mov esi, dword ptr [edi + 0x50c]
006bb363 mulss xmm0, xmm2
006bb367 mov dword ptr [edi + 0x2d4], 0x41000000
006bb371 movss dword ptr [edi + 0x2c4], xmm0
006bb379 test esi, esi
006bb37b je 0x6bb48a
006bb381 cmp esi, 4
006bb384 mov eax, 1
006bb389 sbb ecx, ecx
006bb38b and ecx, 0x18
006bb38e add ecx, 6
006bb391 cmp esi, 8
006bb394 cmovae ecx, eax
006bb397 cmp dword ptr [edi + 0x30], 0
006bb39b jne 0x6bb3ac
006bb39d mov dword ptr [edi + 0x50c], 0
006bb3a7 jmp 0x6bb48a
006bb3ac mov eax, dword ptr [0xbfd65c]
006bb3b1 mov eax, dword ptr [eax + 0x1a30dc]
006bb3b7 sub eax, dword ptr [edi + 0x280]
006bb3bd test eax, eax
006bb3bf jle 0x6bb48a
006bb3c5 push 0
006bb3c7 push ecx
006bb3c8 mov ecx, edi
006bb3ca call 0x684790
006bb3cf test al, al
006bb3d1 je 0x6bb48a
006bb3d7 lea eax, [esi*4 - 4]
006bb3de push eax
006bb3df lea eax, [edi + 0x4f0]
006bb3e5 push eax
006bb3e6 lea eax, [ebp - 0x30]
006bb3e9 push eax
006bb3ea call 0x9ec14c
006bb3ef mov eax, dword ptr [edi + 0x30]
006bb3f2 lea ecx, [edi + 0x3c]
006bb3f5 add esp, 0xc
006bb3f8 mov dword ptr [ebp + esi*4 - 0x34], eax
006bb3fc call 0x4058f0
006bb401 push 1
006bb403 push 1
006bb405 push 1
006bb407 push dword ptr [edi + 0x4ec]
006bb40d mov ecx, edi
006bb40f mov dword ptr [ebp - 0x9c], eax
006bb415 push 0x64
006bb417 push dword ptr [edi + 0x28]
006bb41a call 0x6b97f0
006bb41f cmp dword ptr [edi + 0x70], 0
006bb423 je 0x6bb438
006bb425 movd xmm1, dword ptr [ebp - 0x9c]
006bb42d lea ecx, [edi + 0x6c]
006bb430 cvtdq2ps xmm1, xmm1
006bb433 call 0x403c00
006bb438 movups xmm0, xmmword ptr [ebp - 0x30]
006bb43c mov dword ptr [edi + 0x50c], esi
006bb442 mov dword ptr [edi + 0x490], 0
006bb44c movups xmmword ptr [edi + 0x4ec], xmm0
006bb453 movups xmm0, xmmword ptr [ebp - 0x20]
006bb457 movups xmmword ptr [edi + 0x4fc], xmm0
006bb45e jmp 0x6bb48a
006bb460 mov ecx, dword ptr [edi + 0x164]
006bb466 xor eax, eax
006bb468 and ecx, 0x4000000
006bb46e or eax, ecx
006bb470 jne 0x6bb48a
006bb472 movss xmm0, dword ptr [edi + 0x2c4]
006bb47a mulss xmm0, dword ptr [0xb6a5f4]
006bb482 movss dword ptr [edi + 0x2c4], xmm0
