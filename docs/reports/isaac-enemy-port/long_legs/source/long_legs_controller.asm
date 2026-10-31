0051edf0 push ebx
0051edf1 mov ebx, esp
0051edf3 sub esp, 8
0051edf6 and esp, 0xfffffff8
0051edf9 add esp, 4
0051edfc push ebp
0051edfd mov ebp, dword ptr [ebx + 4]
0051ee00 mov dword ptr [esp + 4], ebp
0051ee04 mov ebp, esp
0051ee06 push -1
0051ee08 push 0x9ed735
0051ee0d mov eax, dword ptr fs:[0]
0051ee13 push eax
0051ee14 push ebx
0051ee15 sub esp, 0x100
0051ee1b mov eax, dword ptr [0xbaa3b4]
0051ee20 xor eax, ebp
0051ee22 mov dword ptr [ebp - 0x14], eax
0051ee25 push esi
0051ee26 push edi
0051ee27 push eax
0051ee28 lea eax, [ebp - 0xc]
0051ee2b mov dword ptr fs:[0], eax
0051ee31 mov edi, ecx
0051ee33 mov ecx, dword ptr [0xbfd65c]
0051ee39 push 1
0051ee3b add ecx, 0x1ba40
0051ee41 push ecx
0051ee42 push 0x179
0051ee47 call 0x91d340
0051ee4c test eax, eax
0051ee4e je 0x51ee64
0051ee50 mov eax, dword ptr [edi + 0x160]
0051ee56 and eax, 0x20000000
0051ee5b or eax, 0
0051ee5e jne 0x51ee64
0051ee60 mov dl, 1
0051ee62 jmp 0x51ee66
0051ee64 xor dl, dl
0051ee66 mov eax, dword ptr [edi + 0xab4]
0051ee6c mov byte ptr [ebp - 0xf9], dl
0051ee72 test eax, eax
0051ee74 jne 0x51ee85
0051ee76 mov dword ptr [edi + 0xab4], 4
0051ee80 jmp 0x51f4e6
0051ee85 cmp eax, 4
0051ee88 jne 0x51f253
0051ee8e cmp dword ptr [edi + 0x28], 0xce
0051ee95 mov eax, dword ptr [edi + 0x164]
0051ee9b mov ecx, dword ptr [edi + 0x160]
0051eea1 mov dword ptr [edi + 0x140], 0x3f800000
0051eeab mov dword ptr [ebp - 0x104], eax
0051eeb1 jne 0x51efd7
0051eeb7 and ecx, 0x200
0051eebd or ecx, 0
0051eec0 jne 0x51f120
0051eec6 test dl, dl
0051eec8 jne 0x51f120
0051eece cmp dword ptr [edi + 0xe6c], -1
0051eed5 mov ecx, edi
0051eed7 je 0x51ef19
0051eed9 call 0x695680
0051eede push 1
0051eee0 push 0x384
0051eee5 push ecx
0051eee6 mov edx, dword ptr [eax + 0x294]
0051eeec lea ecx, [edi + 0x364]
0051eef2 mov eax, dword ptr [eax + 0x298]
0051eef8 mov dword ptr [ebp - 0xf4], eax
0051eefe lea eax, [ebp - 0xf8]
0051ef04 mov dword ptr [esp], 0x3f266666
0051ef0b push eax
0051ef0c mov dword ptr [ebp - 0xf8], edx
0051ef12 call 0x7a3650
0051ef17 jmp 0x51ef4a
0051ef19 call 0x695680
0051ef1e push 0
0051ef20 mov ecx, dword ptr [eax + 0x294]
0051ef26 mov eax, dword ptr [eax + 0x298]
0051ef2c mov dword ptr [ebp - 0xf4], eax
0051ef32 lea eax, [ebp - 0xf8]
0051ef38 mov dword ptr [ebp - 0xf8], ecx
0051ef3e lea ecx, [edi + 0x364]
0051ef44 push eax
0051ef45 call 0x7a4830
0051ef4a cmp dword ptr [edi + 0x2c], 1
0051ef4e mov eax, 0xc8
0051ef53 mov esi, 0x64
0051ef58 mov ecx, edi
0051ef5a cmove esi, eax
0051ef5d call 0x6ad7a0
0051ef62 cmp eax, 6
0051ef65 jge 0x51f178
0051ef6b cmp dword ptr [edi + 0xe6c], -1
0051ef72 je 0x51ef9d
0051ef74 push 9
0051ef76 mov ecx, edi
0051ef78 call 0x6af050
0051ef7d test al, al
0051ef7f jne 0x51efc2
0051ef81 movss xmm1, dword ptr [0xb6accc]
0051ef89 mov ecx, edi
0051ef8b push 7
0051ef8d push 0
0051ef8f call 0x6a15a0
0051ef94 test al, al
0051ef96 jne 0x51efc2
0051ef98 jmp 0x51f178
0051ef9d cmp dword ptr [edi + 0xaa0], 0
0051efa4 jg 0x51efb3
0051efa6 mov ecx, esi
0051efa8 shr ecx, 1
0051efaa call 0x659230
0051efaf test eax, eax
0051efb1 je 0x51efc2
0051efb3 mov ecx, esi
0051efb5 call 0x659230
0051efba test eax, eax
0051efbc jne 0x51f178
0051efc2 push 0
0051efc4 push 0x1000800
0051efc9 mov ecx, edi
0051efcb call 0x4122f0
0051efd0 test al, al
0051efd2 jmp 0x51f112
0051efd7 and ecx, 0x1000800
0051efdd or ecx, 0
0051efe0 mov ecx, edi
0051efe2 je 0x51f06a
0051efe8 cmp dword ptr [edi + 0xe6c], -1
0051efef je 0x51f034
0051eff1 call 0x695680
0051eff6 push 1
0051eff8 push 0x384
0051effd push ecx
0051effe mov edx, dword ptr [eax + 0x294]
0051f004 lea ecx, [edi + 0x364]
0051f00a mov eax, dword ptr [eax + 0x298]
0051f010 mov dword ptr [ebp - 0xf4], eax
0051f016 lea eax, [ebp - 0xf8]
0051f01c mov dword ptr [esp], 0x3f266666
0051f023 push eax
0051f024 mov dword ptr [ebp - 0xf8], edx
0051f02a call 0x7a3650
0051f02f jmp 0x51f178
0051f034 call 0x695680
0051f039 push 0
0051f03b mov ecx, dword ptr [eax + 0x294]
0051f041 mov eax, dword ptr [eax + 0x298]
0051f047 mov dword ptr [ebp - 0xf4], eax
0051f04d lea eax, [ebp - 0xf8]
0051f053 mov dword ptr [ebp - 0xf8], ecx
0051f059 lea ecx, [edi + 0x364]
0051f05f push eax
0051f060 call 0x7a4830
0051f065 jmp 0x51f178
0051f06a push 0
0051f06c push 0x200
0051f071 call 0x4122f0
0051f076 test al, al
0051f078 jne 0x51f120
0051f07e cmp byte ptr [ebp - 0xf9], al
0051f084 jne 0x51f120
0051f08a mov ecx, edi
0051f08c call 0x695680
0051f091 push 1
0051f093 push 0x384
0051f098 mov ecx, dword ptr [eax + 0x294]
0051f09e mov eax, dword ptr [eax + 0x298]
0051f0a4 push ecx
0051f0a5 mov dword ptr [ebp - 0xf4], eax
0051f0ab lea eax, [ebp - 0xf8]
0051f0b1 mov dword ptr [ebp - 0xf8], ecx
0051f0b7 lea ecx, [edi + 0x364]
0051f0bd mov dword ptr [esp], 0x3f266666
0051f0c4 push eax
0051f0c5 call 0x7a3650
0051f0ca cmp dword ptr [edi + 0xe6c], -1
0051f0d1 je 0x51f0f9
0051f0d3 push 9
0051f0d5 mov ecx, edi
0051f0d7 call 0x6af050
0051f0dc test al, al
0051f0de jne 0x51f114
0051f0e0 movss xmm1, dword ptr [0xb6accc]
0051f0e8 mov ecx, edi
0051f0ea push 7
0051f0ec push 0
0051f0ee call 0x6a15a0
0051f0f3 test al, al
0051f0f5 jne 0x51f114
0051f0f7 jmp 0x51f178
0051f0f9 cmp byte ptr [edi + 0xa90], 0
0051f100 je 0x51f178
0051f102 call 0x6c3d90
0051f107 xor edx, edx
0051f109 mov ecx, 0x32
0051f10e div ecx
0051f110 test edx, edx
0051f112 jne 0x51f178
0051f114 mov dword ptr [edi + 0xab4], 8
0051f11e jmp 0x51f178
0051f120 cmp dword ptr [edi + 0xe6c], -1
0051f127 je 0x51f16b
0051f129 mov ecx, edi
0051f12b call 0x695680
0051f130 push 1
0051f132 push 0x384
0051f137 push ecx
0051f138 mov edx, dword ptr [eax + 0x294]
0051f13e lea ecx, [edi + 0x364]
0051f144 mov eax, dword ptr [eax + 0x298]
0051f14a mov dword ptr [ebp - 0xf4], eax
0051f150 lea eax, [ebp - 0xf8]
0051f156 mov dword ptr [esp], 0x3f266666
0051f15d push eax
0051f15e mov dword ptr [ebp - 0xf8], edx
0051f164 call 0x7a3650
0051f169 jmp 0x51f178
0051f16b push 0
0051f16d lea ecx, [edi + 0x364]
0051f173 call 0x7a6180
0051f178 mov dword ptr [ebp - 0x30], 0xf
0051f17f mov dword ptr [ebp - 0x34], 4
0051f186 mov dword ptr [ebp - 0x44], 0x6b6c6157
0051f18d mov byte ptr [ebp - 0x40], 0
0051f191 mov dword ptr [ebp - 4], 0
0051f198 mov dword ptr [ebp - 0x18], 0xf
0051f19f mov dword ptr [ebp - 0x1c], 4
0051f1a6 mov dword ptr [ebp - 0x2c], 0x6b6c6157
0051f1ad mov byte ptr [ebp - 0x28], 0
0051f1b1 push ecx
0051f1b2 mov byte ptr [ebp - 4], 1
0051f1b6 lea eax, [ebp - 0x44]
0051f1b9 mov dword ptr [esp], 0x3dcccccd
0051f1c0 mov ecx, edi
0051f1c2 push eax
0051f1c3 lea eax, [ebp - 0x2c]
0051f1c6 push eax
0051f1c7 call 0x6980a0
0051f1cc mov edx, dword ptr [ebp - 0x18]
0051f1cf cmp edx, 0x10
0051f1d2 jb 0x51f1fc
0051f1d4 mov ecx, dword ptr [ebp - 0x2c]
0051f1d7 inc edx
0051f1d8 mov eax, ecx
0051f1da cmp edx, 0x1000
0051f1e0 jb 0x51f1f2
0051f1e2 mov ecx, dword ptr [ecx - 4]
0051f1e5 add edx, 0x23
0051f1e8 sub eax, ecx
0051f1ea add eax, -4
0051f1ed cmp eax, 0x1f
0051f1f0 ja 0x51f234
0051f1f2 push edx
0051f1f3 push ecx
0051f1f4 call 0x9eb08e
0051f1f9 add esp, 8
0051f1fc mov edx, dword ptr [ebp - 0x30]
0051f1ff mov dword ptr [ebp - 0x1c], 0
0051f206 mov dword ptr [ebp - 0x18], 0xf
0051f20d mov byte ptr [ebp - 0x2c], 0
0051f211 cmp edx, 0x10
0051f214 jb 0x51f244
0051f216 mov ecx, dword ptr [ebp - 0x44]
0051f219 inc edx
0051f21a mov eax, ecx
0051f21c cmp edx, 0x1000
0051f222 jb 0x51f23a
0051f224 mov ecx, dword ptr [ecx - 4]
0051f227 add edx, 0x23
0051f22a sub eax, ecx
0051f22c add eax, -4
0051f22f cmp eax, 0x1f
0051f232 jbe 0x51f23a
0051f234 call dword ptr [0xa065ac]
0051f23a push edx
0051f23b push ecx
0051f23c call 0x9eb08e
0051f241 add esp, 8
0051f244 mov dword ptr [edi + 0x2c4], 0x3f4ccccd
0051f24e jmp 0x51f4e6
0051f253 cmp eax, 8
0051f256 jne 0x51f4e6
0051f25c cmp dword ptr [edi + 0x28], 0xce
0051f263 lea ecx, [edi + 0x3c]
0051f266 push 0
0051f268 jne 0x51f3c6
0051f26e push 0xb432bc
0051f273 call 0x4054f0
0051f278 cmp dword ptr [edi + 0xe6c], -1
0051f27f je 0x51f28b
0051f281 mov dword ptr [edi + 0x140], 0x3fc00000
0051f28b cmp dword ptr [edi + 0x70], 0
0051f28f je 0x51f4c4
0051f295 push 0xb432a8
0051f29a lea ecx, [edi + 0x6c]
0051f29d call 0x405e90
0051f2a2 test al, al
0051f2a4 je 0x51f4b5
0051f2aa push ecx
0051f2ab mov dword ptr [esp], 0x3f800000
0051f2b2 push 0
0051f2b4 push 2
0051f2b6 push ecx
0051f2b7 mov dword ptr [esp], 0x3f800000
0051f2be mov ecx, edi
0051f2c0 push 0x9f
0051f2c5 call 0x6ad720
0051f2ca mov eax, dword ptr [edi + 0x2c]
0051f2cd test eax, eax
0051f2cf jne 0x51f373
0051f2d5 lea eax, [ebp - 0xf8]
0051f2db push eax
0051f2dc call 0x659290
0051f2e1 add esp, 4
0051f2e4 call 0x6c3d90
0051f2e9 mov ecx, dword ptr [0xbfd65c]
0051f2ef lea esi, [edi + 0x294]
0051f2f5 push eax
0051f2f6 push 0
0051f2f8 push edi
0051f2f9 lea eax, [ebp - 0xf8]
0051f2ff push eax
0051f300 push esi
0051f301 push 0
0051f303 push 0x55
0051f305 call 0x422e20
0051f30a call 0x6c3d90
0051f30f xor edx, edx
0051f311 mov ecx, 0x14
0051f316 div ecx
0051f318 test edx, edx
0051f31a jne 0x51f4b5
0051f320 call 0x6c3d90
0051f325 movss xmm0, dword ptr [ebp - 0xf8]
0051f32d xorps xmm0, xmmword ptr [0xb6c9b0]
0051f334 mov ecx, dword ptr [0xbfd65c]
0051f33a push eax
0051f33b push 0
0051f33d push edi
0051f33e lea eax, [ebp - 0x110]
0051f344 movss dword ptr [ebp - 0x110], xmm0
0051f34c movss xmm0, dword ptr [ebp - 0xf4]
0051f354 xorps xmm0, xmmword ptr [0xb6c9b0]
0051f35b push eax
0051f35c push esi
0051f35d push 0
0051f35f push 0x55
0051f361 movss dword ptr [ebp - 0x10c], xmm0
0051f369 call 0x422e20
0051f36e jmp 0x51f4b5
0051f373 cmp eax, 1
0051f376 jne 0x51f4b5
0051f37c call 0x6c3d90
0051f381 mov ecx, dword ptr [0xbfd65c]
0051f387 lea esi, [edi + 0x294]
0051f38d push eax
0051f38e push 0
0051f390 push edi
0051f391 push 0xc02fec
0051f396 push esi
0051f397 push 2
0051f399 push 0x1e
0051f39b call 0x422e20
0051f3a0 call 0x6c3d90
0051f3a5 mov ecx, dword ptr [0xbfd65c]
0051f3ab push eax
0051f3ac push 0
0051f3ae push edi
0051f3af push 0xc02fec
0051f3b4 push esi
0051f3b5 push 0x19
0051f3b7 push 0x3e8
0051f3bc call 0x422e20
0051f3c1 jmp 0x51f4b5
0051f3c6 push 0xb40510
0051f3cb call 0x4054f0
0051f3d0 cmp dword ptr [edi + 0xe6c], -1
0051f3d7 je 0x51f3e3
0051f3d9 mov dword ptr [edi + 0x140], 0x3fc00000
0051f3e3 cmp dword ptr [edi + 0x70], 0
0051f3e7 je 0x51f4c4
0051f3ed push 0xb400ac
0051f3f2 lea ecx, [edi + 0x6c]
0051f3f5 call 0x405e90
0051f3fa test al, al
0051f3fc je 0x51f4b5
0051f402 push ecx
0051f403 mov dword ptr [esp], 0x3f800000
0051f40a push 0
0051f40c push 2
0051f40e push ecx
0051f40f mov dword ptr [esp], 0x3f800000
0051f416 mov ecx, edi
0051f418 push 0xb2
0051f41d call 0x6ad720
0051f422 lea ecx, [ebp - 0xf0]
0051f428 call 0x430d70
0051f42d mov esi, dword ptr [edi + 0x2c]
0051f430 neg esi
0051f432 mov dword ptr [ebp - 0xe4], 0x3f000000
0051f43c mov dword ptr [ebp - 0xe8], 0xc1200000
0051f446 sbb esi, esi
0051f448 mov dword ptr [ebp - 0xec], 0x41200000
0051f452 add esi, 8
0051f455 call 0x6c3d90
0051f45a mov ecx, edi
0051f45c mov dword ptr [ebp - 0x104], 0
0051f466 movd xmm0, eax
0051f46a cvtdq2pd xmm0, xmm0
0051f46e shr eax, 0x1f
0051f471 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
0051f47a lea eax, [ebp - 0xf0]
0051f480 push eax
0051f481 push esi
0051f482 lea eax, [ebp - 0x108]
0051f488 cvtpd2ps xmm0, xmm0
0051f48c push eax
0051f48d lea eax, [edi + 0x294]
0051f493 push eax
0051f494 mulss xmm0, dword ptr [0xb6a19c]
0051f49c addss xmm0, xmm0
0051f4a0 addss xmm0, dword ptr [0xb6a940]
0051f4a8 movss dword ptr [ebp - 0x108], xmm0
0051f4b0 call 0x6a1a20
0051f4b5 cmp dword ptr [edi + 0x70], 0
0051f4b9 je 0x51f4c4
0051f4bb cmp byte ptr [edi + 0x80], 0
0051f4c2 jne 0x51f4ce
0051f4c4 mov dword ptr [edi + 0xab4], 4
0051f4ce movss xmm0, dword ptr [edi + 0x2c4]
0051f4d6 mulss xmm0, dword ptr [0xb6a480]
0051f4de movss dword ptr [edi + 0x2c4], xmm0
0051f4e6 mov ecx, dword ptr [ebp - 0xc]
0051f4e9 mov dword ptr fs:[0], ecx
0051f4f0 pop ecx
0051f4f1 pop edi
0051f4f2 pop esi
0051f4f3 mov ecx, dword ptr [ebp - 0x14]
0051f4f6 xor ecx, ebp
0051f4f8 call 0x9eacd7
0051f4fd mov esp, ebp
0051f4ff pop ebp
0051f500 mov esp, ebx
0051f502 pop ebx
0051f503 ret 
