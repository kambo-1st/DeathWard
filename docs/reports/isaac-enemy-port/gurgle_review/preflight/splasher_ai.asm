004f8e40 push ebx
004f8e41 mov ebx, esp
004f8e43 sub esp, 8
004f8e46 and esp, 0xfffffff8
004f8e49 add esp, 4
004f8e4c push ebp
004f8e4d mov ebp, dword ptr [ebx + 4]
004f8e50 mov dword ptr [esp + 4], ebp
004f8e54 mov ebp, esp
004f8e56 push -1
004f8e58 push 0x9ef255
004f8e5d mov eax, dword ptr fs:[0]
004f8e63 push eax
004f8e64 push ebx
004f8e65 sub esp, 0x148
004f8e6b mov eax, dword ptr [0xbaa3b4]
004f8e70 xor eax, ebp
004f8e72 mov dword ptr [ebp - 0x14], eax
004f8e75 push esi
004f8e76 push edi
004f8e77 push eax
004f8e78 lea eax, [ebp - 0xc]
004f8e7b mov dword ptr fs:[0], eax
004f8e81 mov edi, ecx
004f8e83 cmp dword ptr [edi + 0xab4], 0
004f8e8a jne 0x4f8f3b
004f8e90 cmp dword ptr [edi + 0x28], 0xee
004f8e97 mov dword ptr [edi + 0xab4], 4
004f8ea1 jne 0x4f8ef8
004f8ea3 movaps xmm1, xmmword ptr [0xb6c290]
004f8eaa lea ecx, [edi + 0x1dc]
004f8eb0 lea eax, [ebp - 0x154]
004f8eb6 mov dword ptr [ebp - 0x134], 0xbe48c8ca
004f8ec0 mov dword ptr [ebp - 0x130], 0x3f028283
004f8eca xorps xmm0, xmm0
004f8ecd mov dword ptr [ebp - 0x12c], 0x3e48c8ca
004f8ed7 cmp ecx, eax
004f8ed9 je 0x4f8ef8
004f8edb mov eax, dword ptr [ebp - 0x12c]
004f8ee1 movups xmmword ptr [ecx + 0x10], xmm0
004f8ee5 movq xmm0, qword ptr [ebp - 0x134]
004f8eed movq qword ptr [ecx + 0x20], xmm0
004f8ef2 movups xmmword ptr [ecx], xmm1
004f8ef5 mov dword ptr [ecx + 0x28], eax
004f8ef8 call 0x6c3d90
004f8efd xor edx, edx
004f8eff mov ecx, 0x14
004f8f04 div ecx
004f8f06 add edx, ecx
004f8f08 cmp dword ptr [edi + 0x2c], 0
004f8f0c mov dword ptr [edi + 0xaf0], edx
004f8f12 jne 0x4f8f1a
004f8f14 cmp dword ptr [edi + 0x28], 0xb
004f8f18 je 0x4f8f27
004f8f1a cmp dword ptr [edi + 0x28], 0xee
004f8f21 jne 0x4f9a34
004f8f27 push 0
004f8f29 push 0xb41240
004f8f2e lea ecx, [edi + 0x3c]
004f8f31 call 0x405a00
004f8f36 jmp 0x4f9a34
004f8f3b cmp byte ptr [edi + 0x16b], 0
004f8f42 je 0x4f8f99
004f8f44 cmp dword ptr [edi + 0x28], 0xd2
004f8f4b jne 0x4f8f99
004f8f4d movss xmm0, dword ptr [edi + 0x2d8]
004f8f55 comiss xmm0, dword ptr [0xb6aef8]
004f8f5c jbe 0x4f9a34
004f8f62 call 0x6c3d90
004f8f67 test al, 1
004f8f69 jne 0x4f9a34
004f8f6f push -1
004f8f71 push 0
004f8f73 push 0
004f8f75 push 0xd3
004f8f7a mov ecx, edi
004f8f7c call 0x697c60
004f8f81 mov eax, dword ptr [edi + 0x2dc]
004f8f87 mov byte ptr [edi + 0x16b], 0
004f8f8e mov dword ptr [edi + 0x2d8], eax
004f8f94 jmp 0x4f9a34
004f8f99 cmp dword ptr [edi + 0x28], 0xee
004f8fa0 xorps xmm1, xmm1
004f8fa3 jne 0x4f9008
004f8fa5 movss xmm0, dword ptr [edi + 0x14]
004f8faa comiss xmm0, xmm1
004f8fad jbe 0x4f9008
004f8faf mov eax, dword ptr [edi + 8]
004f8fb2 cmp eax, dword ptr [edi + 0xc]
004f8fb5 je 0x4f9008
004f8fb7 nop word ptr [eax + eax]
004f8fc0 mov ecx, dword ptr [eax + 0xc]
004f8fc3 mov edx, dword ptr [eax + 8]
004f8fc6 mov dword ptr [ebp - 0x11c], ecx
004f8fcc mov ecx, edx
004f8fce and ecx, 4
004f8fd1 or ecx, 0
004f8fd4 je 0x4f9000
004f8fd6 mov ecx, dword ptr [eax + 0x30]
004f8fd9 shr ecx, 1
004f8fdb test cl, 1
004f8fde jne 0x4f9000
004f8fe0 cmp dword ptr [eax + 0x10], 1
004f8fe4 je 0x4f9000
004f8fe6 mov ecx, dword ptr [eax + 0x18]
004f8fe9 cmp ecx, 1
004f8fec je 0x4f9000
004f8fee cmp ecx, 3
004f8ff1 je 0x4f9000
004f8ff3 and edx, 0x1000
004f8ff9 or edx, 0
004f8ffc jne 0x4f9000
004f8ffe mov dword ptr [eax], edx
004f9000 add eax, 0x38
004f9003 cmp eax, dword ptr [edi + 0xc]
004f9006 jne 0x4f8fc0
004f9008 mov eax, dword ptr [0xb404ec]
004f900d mov ecx, dword ptr [0xb404f0]
004f9013 mov dword ptr [ebp - 0x18], 0xf
004f901a mov dword ptr [ebp - 0x1c], 8
004f9021 mov dword ptr [ebp - 0x2c], eax
004f9024 mov dword ptr [ebp - 0x28], ecx
004f9027 mov byte ptr [ebp - 0x24], 0
004f902b mov dword ptr [ebp - 4], 0
004f9032 mov eax, dword ptr [0xb40504]
004f9037 mov ecx, dword ptr [0xb40508]
004f903d mov dword ptr [ebp - 0x44], 0xf
004f9044 mov dword ptr [ebp - 0x48], 8
004f904b mov dword ptr [ebp - 0x58], eax
004f904e mov dword ptr [ebp - 0x54], ecx
004f9051 mov byte ptr [ebp - 0x50], 0
004f9055 push ecx
004f9056 mov byte ptr [ebp - 4], 1
004f905a lea eax, [ebp - 0x2c]
004f905d mov dword ptr [esp], 0x3dcccccd
004f9064 mov ecx, edi
004f9066 push eax
004f9067 lea eax, [ebp - 0x58]
004f906a push eax
004f906b call 0x6980a0
004f9070 mov byte ptr [ebp - 4], 0
004f9074 mov edx, dword ptr [ebp - 0x44]
004f9077 cmp edx, 0x10
004f907a jb 0x4f90a4
004f907c mov ecx, dword ptr [ebp - 0x58]
004f907f inc edx
004f9080 mov eax, ecx
004f9082 cmp edx, 0x1000
004f9088 jb 0x4f909a
004f908a mov ecx, dword ptr [ecx - 4]
004f908d add edx, 0x23
004f9090 sub eax, ecx
004f9092 add eax, -4
004f9095 cmp eax, 0x1f
004f9098 ja 0x4f90e3
004f909a push edx
004f909b push ecx
004f909c call 0x9eb08e
004f90a1 add esp, 8
004f90a4 mov dword ptr [ebp - 4], 0xffffffff
004f90ab mov edx, dword ptr [ebp - 0x18]
004f90ae mov dword ptr [ebp - 0x48], 0
004f90b5 mov dword ptr [ebp - 0x44], 0xf
004f90bc mov byte ptr [ebp - 0x58], 0
004f90c0 cmp edx, 0x10
004f90c3 jb 0x4f90f3
004f90c5 mov ecx, dword ptr [ebp - 0x2c]
004f90c8 inc edx
004f90c9 mov eax, ecx
004f90cb cmp edx, 0x1000
004f90d1 jb 0x4f90e9
004f90d3 mov ecx, dword ptr [ecx - 4]
004f90d6 add edx, 0x23
004f90d9 sub eax, ecx
004f90db add eax, -4
004f90de cmp eax, 0x1f
004f90e1 jbe 0x4f90e9
004f90e3 call dword ptr [0xa065ac]
004f90e9 push edx
004f90ea push ecx
004f90eb call 0x9eb08e
004f90f0 add esp, 8
004f90f3 cmp dword ptr [edi + 0x2c], 0
004f90f7 movss xmm1, dword ptr [0xb6accc]
004f90ff mov eax, dword ptr [edi + 0x28]
004f9102 jne 0x4f9109
004f9104 cmp eax, 0xb
004f9107 je 0x4f9114
004f9109 cmp eax, 0xee
004f910e jne 0x4f9408
004f9114 mov esi, dword ptr [edi + 0x90]
004f911a test esi, esi
004f911c je 0x4f916b
004f911e cmp dword ptr [esi + 0x14], 0x10
004f9122 mov eax, esi
004f9124 jb 0x4f9128
004f9126 mov eax, dword ptr [esi]
004f9128 mov ecx, 0xb41240
004f912d nop dword ptr [eax]
004f9130 mov dl, byte ptr [eax]
004f9132 cmp dl, byte ptr [ecx]
004f9134 jne 0x4f9150
004f9136 test dl, dl
004f9138 je 0x4f914c
004f913a mov dl, byte ptr [eax + 1]
004f913d cmp dl, byte ptr [ecx + 1]
004f9140 jne 0x4f9150
004f9142 add eax, 2
004f9145 add ecx, 2
004f9148 test dl, dl
004f914a jne 0x4f9130
004f914c xor eax, eax
004f914e jmp 0x4f9155
004f9150 sbb eax, eax
004f9152 or eax, 1
004f9155 test eax, eax
004f9157 jne 0x4f916b
004f9159 cmp byte ptr [esi + 0x34], al
004f915c je 0x4f9194
004f915e cmp byte ptr [edi + 0xa0], al
004f9164 lea esi, [edi + 0x3c]
004f9167 jne 0x4f9194
004f9169 jmp 0x4f916e
004f916b lea esi, [edi + 0x3c]
004f916e push 1
004f9170 push 0xb41240
004f9175 mov ecx, esi
004f9177 call 0x405bb0
004f917c test al, al
004f917e je 0x4f918c
004f9180 lea ecx, [esi + 0x50]
004f9183 call 0x405330
004f9188 mov byte ptr [esi + 0x64], 1
004f918c movss xmm1, dword ptr [0xb6accc]
004f9194 mov edx, dword ptr [edi + 0xaf0]
004f919a test edx, edx
004f919c jg 0x4f93e9
004f91a2 mov eax, dword ptr [edi + 0x160]
004f91a8 and eax, 0x1000a00
004f91ad or eax, 0
004f91b0 jne 0x4f93e9
004f91b6 cmp dword ptr [edi + 0xe6c], -1
004f91bd je 0x4f91d1
004f91bf push 7
004f91c1 push eax
004f91c2 mov ecx, edi
004f91c4 call 0x6a15a0
004f91c9 test al, al
004f91cb je 0x4f95dc
004f91d1 cmp dword ptr [edi + 0xe6c], -1
004f91d8 movss xmm0, dword ptr [0xc02fec]
004f91e0 movss xmm1, dword ptr [0xc02ff0]
004f91e8 movss dword ptr [ebp - 0x124], xmm0
004f91f0 movss dword ptr [ebp - 0x11c], xmm1
004f91f8 je 0x4f922b
004f91fa movss xmm2, dword ptr [0xb6a2cc]
004f9202 lea eax, [ebp - 0x120]
004f9208 push eax
004f9209 mov ecx, edi
004f920b call 0x6af380
004f9210 movss xmm0, dword ptr [eax]
004f9214 movss dword ptr [ebp - 0x124], xmm0
004f921c movss xmm0, dword ptr [eax + 4]
004f9221 movss dword ptr [ebp - 0x11c], xmm0
004f9229 jmp 0x4f928f
004f922b movss xmm1, dword ptr [edi + 0x2b8]
004f9233 movss xmm2, dword ptr [edi + 0x2bc]
004f923b movaps xmm0, xmm1
004f923e mulss xmm0, xmm1
004f9242 movaps xmm1, xmm2
004f9245 mulss xmm1, xmm2
004f9249 addss xmm0, xmm1
004f924d call 0x4228c0
004f9252 movaps xmm1, xmm0
004f9255 xorps xmm2, xmm2
004f9258 comiss xmm1, xmm2
004f925b jbe 0x4f9287
004f925d movss xmm0, dword ptr [edi + 0x2b8]
004f9265 divss xmm0, xmm1
004f9269 movss dword ptr [ebp - 0x124], xmm0
004f9271 movss xmm0, dword ptr [edi + 0x2bc]
004f9279 divss xmm0, xmm1
004f927d movss dword ptr [ebp - 0x11c], xmm0
004f9285 jmp 0x4f928f
004f9287 movss xmm0, dword ptr [ebp - 0x11c]
004f928f movss xmm1, dword ptr [ebp - 0x124]
004f9297 ucomiss xmm1, dword ptr [0xc02fec]
004f929e lahf 
004f929f test ah, 0x44
004f92a2 jp 0x4f92b5
004f92a4 ucomiss xmm0, dword ptr [0xc02ff0]
004f92ab lahf 
004f92ac test ah, 0x44
004f92af jnp 0x4f95dc
004f92b5 cmp dword ptr [edi + 0x28], 0xb
004f92b9 jne 0x4f92df
004f92bb cmp dword ptr [edi + 0xe6c], -1
004f92c2 je 0x4f92c8
004f92c4 xor edx, edx
004f92c6 jmp 0x4f92d6
004f92c8 call 0x6c3d90
004f92cd xor edx, edx
004f92cf mov ecx, 0x14
004f92d4 div ecx
004f92d6 lea eax, [edx + 0x28]
004f92d9 mov dword ptr [edi + 0xaf0], eax
004f92df lea ecx, [ebp - 0x118]
004f92e5 call 0x430d70
004f92ea cmp dword ptr [edi + 0x28], 0xee
004f92f1 mov dword ptr [ebp - 0x10c], 0x3e99999a
004f92fb mov dword ptr [ebp - 0x110], 0xc0a00000
004f9305 jne 0x4f934c
004f9307 cmp dword ptr [edi + 0xe6c], -1
004f930e je 0x4f9314
004f9310 xor edx, edx
004f9312 jmp 0x4f9322
004f9314 call 0x6c3d90
004f9319 xor edx, edx
004f931b mov ecx, 0x1e
004f9320 div ecx
004f9322 movaps xmm0, xmmword ptr [0xb6c330]
004f9329 lea eax, [edx + 0x3c]
004f932c or dword ptr [ebp - 0xc0], 2
004f9333 mov dword ptr [edi + 0xaf0], eax
004f9339 mov eax, dword ptr [ebp - 0xbc]
004f933f mov dword ptr [ebp - 0xbc], eax
004f9345 movups xmmword ptr [ebp - 0xdc], xmm0
004f934c call 0x690cc0
004f9351 sub eax, 6
004f9354 je 0x4f936c
004f9356 sub eax, 0x15
004f9359 je 0x4f936c
004f935b sub eax, 1
004f935e jne 0x4f9376
004f9360 mov dword ptr [ebp - 0x84], 3
004f936a jmp 0x4f9376
004f936c mov dword ptr [ebp - 0x84], 4
004f9376 movss xmm1, dword ptr [ebp - 0x124]
004f937e lea eax, [ebp - 0x118]
004f9384 mulss xmm1, dword ptr [0xb6a8f4]
004f938c mov ecx, edi
004f938e push eax
004f938f push 0
004f9391 lea eax, [ebp - 0x128]
004f9397 movss dword ptr [ebp - 0x128], xmm1
004f939f movss xmm1, dword ptr [ebp - 0x11c]
004f93a7 mulss xmm1, dword ptr [0xb6a8f4]
004f93af push eax
004f93b0 lea eax, [edi + 0x294]
004f93b6 push eax
004f93b7 movss dword ptr [ebp - 0x124], xmm1
004f93bf call 0x6a1a20
004f93c4 push ecx
004f93c5 mov dword ptr [esp], 0x3f800000
004f93cc push 0
004f93ce push 2
004f93d0 push ecx
004f93d1 mov dword ptr [esp], 0x3f800000
004f93d8 mov ecx, edi
004f93da push 0xb2
004f93df call 0x6ad720
004f93e4 jmp 0x4f95dc
004f93e9 cvttss2si eax, dword ptr [edi + 0x2fc]
004f93f1 cvttss2si ecx, dword ptr [edi + 0x2f8]
004f93f9 sub ecx, eax
004f93fb add ecx, edx
004f93fd mov dword ptr [edi + 0xaf0], ecx
004f9403 jmp 0x4f95dc
004f9408 cmp eax, 0xd2
004f940d jne 0x4f955d
004f9413 cmp dword ptr [edi + 0xaf0], 0
004f941a jg 0x4f9540
004f9420 mov eax, dword ptr [edi + 0x160]
004f9426 and eax, 0x1000a00
004f942b or eax, 0
004f942e jne 0x4f9540
004f9434 cmp dword ptr [edi + 0xe6c], -1
004f943b je 0x4f945c
004f943d push 7
004f943f push eax
004f9440 mov ecx, edi
004f9442 call 0x6a15a0
004f9447 test al, al
004f9449 jne 0x4f945c
004f944b push 9
004f944d mov ecx, edi
004f944f call 0x6af050
004f9454 test al, al
004f9456 je 0x4f9540
004f945c movss xmm1, dword ptr [edi + 0x2bc]
004f9464 movss xmm0, dword ptr [edi + 0x2b8]
004f946c mulss xmm0, xmm0
004f9470 mulss xmm1, xmm1
004f9474 addss xmm0, xmm1
004f9478 call 0x4228c0
004f947d xorps xmm2, xmm2
004f9480 comiss xmm0, xmm2
004f9483 jbe 0x4f95dc
004f9489 cmp dword ptr [edi + 0xe6c], -1
004f9490 je 0x4f9496
004f9492 xor edx, edx
004f9494 jmp 0x4f94a4
004f9496 call 0x6c3d90
004f949b xor edx, edx
004f949d mov ecx, 0x1e
004f94a2 div ecx
004f94a4 lea eax, [edx + 0x1e]
004f94a7 lea ecx, [ebp - 0x118]
004f94ad mov dword ptr [edi + 0xaf0], eax
004f94b3 call 0x430d70
004f94b8 movss xmm0, dword ptr [ebp - 0x114]
004f94c0 subss xmm0, dword ptr [0xb6a9ac]
004f94c8 mov dword ptr [ebp - 0x110], 0x40a00000
004f94d2 mov dword ptr [ebp - 0xb8], 0
004f94dc mov dword ptr [ebp - 0xb4], 0x40a00000
004f94e6 movss dword ptr [ebp - 0x114], xmm0
004f94ee call 0x6c3d90
004f94f3 mov ecx, 3
004f94f8 xor edx, edx
004f94fa div ecx
004f94fc lea eax, [ebp - 0x118]
004f9502 push eax
004f9503 push ecx
004f9504 mov dword ptr [esp], 0x41200000
004f950b mov ecx, edi
004f950d push 0xc02fec
004f9512 lea eax, [edx + 3]
004f9515 push eax
004f9516 call 0x6a3420
004f951b push ecx
004f951c mov dword ptr [esp], 0x3f800000
004f9523 push 0
004f9525 push 2
004f9527 push ecx
004f9528 mov dword ptr [esp], 0x3f800000
004f952f mov ecx, edi
004f9531 push 0xb2
004f9536 call 0x6ad720
004f953b jmp 0x4f95dc
004f9540 cvttss2si eax, dword ptr [edi + 0x2fc]
004f9548 cvttss2si ecx, dword ptr [edi + 0x2f8]
004f9550 sub ecx, eax
004f9552 add dword ptr [edi + 0xaf0], ecx
004f9558 jmp 0x4f95dc
004f955d cmp eax, 0x118
004f9562 jne 0x4f95dc
004f9564 mov esi, dword ptr [edi + 0x90]
004f956a test esi, esi
004f956c je 0x4f95bb
004f956e cmp dword ptr [esi + 0x14], 0x10
004f9572 mov eax, esi
004f9574 jb 0x4f9578
004f9576 mov eax, dword ptr [esi]
004f9578 mov ecx, 0xb42efc
004f957d nop dword ptr [eax]
004f9580 mov dl, byte ptr [eax]
004f9582 cmp dl, byte ptr [ecx]
004f9584 jne 0x4f95a0
004f9586 test dl, dl
004f9588 je 0x4f959c
004f958a mov dl, byte ptr [eax + 1]
004f958d cmp dl, byte ptr [ecx + 1]
004f9590 jne 0x4f95a0
004f9592 add eax, 2
004f9595 add ecx, 2
004f9598 test dl, dl
004f959a jne 0x4f9580
004f959c xor eax, eax
004f959e jmp 0x4f95a5
004f95a0 sbb eax, eax
004f95a2 or eax, 1
004f95a5 test eax, eax
004f95a7 jne 0x4f95bb
004f95a9 cmp byte ptr [esi + 0x34], al
004f95ac je 0x4f95dc
004f95ae cmp byte ptr [edi + 0xa0], al
004f95b4 lea esi, [edi + 0x3c]
004f95b7 jne 0x4f95dc
004f95b9 jmp 0x4f95be
004f95bb lea esi, [edi + 0x3c]
004f95be push 1
004f95c0 push 0xb42efc
004f95c5 mov ecx, esi
004f95c7 call 0x405bb0
004f95cc test al, al
004f95ce je 0x4f95dc
004f95d0 lea ecx, [esi + 0x50]
004f95d3 call 0x405330
004f95d8 mov byte ptr [esi + 0x64], 1
004f95dc movss xmm0, dword ptr [edi + 0x2c4]
004f95e4 mulss xmm0, dword ptr [0xb6a53c]
004f95ec mov eax, dword ptr [edi + 0x160]
004f95f2 and eax, 0x1000800
004f95f7 or eax, 0
004f95fa movss dword ptr [edi + 0x2c4], xmm0
004f9602 je 0x4f9663
004f9604 cmp dword ptr [edi + 0xe6c], -1
004f960b jne 0x4f9663
004f960d mov ecx, edi
004f960f call 0x695680
004f9614 push 0
004f9616 mov ecx, dword ptr [eax + 0x294]
004f961c mov eax, dword ptr [eax + 0x298]
004f9622 mov dword ptr [ebp - 0x11c], eax
004f9628 lea eax, [ebp - 0x120]
004f962e mov dword ptr [ebp - 0x120], ecx
004f9634 lea ecx, [edi + 0x364]
004f963a push eax
004f963b call 0x7a4830
004f9640 cmp dword ptr [edi + 0xaa0], 0
004f9647 jle 0x4f9670
004f9649 movss xmm0, dword ptr [edi + 0x2c4]
004f9651 mulss xmm0, dword ptr [0xb6a560]
004f9659 movss dword ptr [edi + 0x2c4], xmm0
004f9661 jmp 0x4f9670
004f9663 push 0
004f9665 lea ecx, [edi + 0x364]
004f966b call 0x7a6180
004f9670 movss xmm1, dword ptr [0xb6a974]
004f9678 xorps xmm2, xmm2
004f967b mov ecx, edi
004f967d call 0x6847e0
004f9682 test eax, eax
004f9684 je 0x4f982c
004f968a mov eax, dword ptr [edi + 0x28]
004f968d cmp eax, 0xd3
004f9692 jne 0x4f970e
004f9694 call 0x6c3d90
004f9699 mov ecx, dword ptr [0xbfd65c]
004f969f push eax
004f96a0 push 0
004f96a2 push edi
004f96a3 push 0xc02fec
004f96a8 lea eax, [edi + 0x294]
004f96ae push eax
004f96af push 0x16
004f96b1 push 0x3e8
004f96b6 call 0x422e20
004f96bb mov esi, eax
004f96bd call 0x6c3d90
004f96c2 mov ecx, esi
004f96c4 movd xmm0, eax
004f96c8 cvtdq2pd xmm0, xmm0
004f96cc shr eax, 0x1f
004f96cf addsd xmm0, qword ptr [eax*8 + 0xb6c940]
004f96d8 mov eax, dword ptr [esi]
004f96da cvtpd2ps xmm0, xmm0
004f96de mulss xmm0, dword ptr [0xb6a19c]
004f96e6 mulss xmm0, dword ptr [0xb6a3b0]
004f96ee addss xmm0, dword ptr [0xb6a350]
004f96f6 movss dword ptr [esi + 0xd8], xmm0
004f96fe movss dword ptr [esi + 0xdc], xmm0
004f9706 call dword ptr [eax + 0xc]
004f9709 jmp 0x4f982c
004f970e movss xmm2, dword ptr [0xb6a19c]
004f9716 cmp eax, 0xd2
004f971b jne 0x4f9766
004f971d call 0x6c3d90
004f9722 push ecx
004f9723 mov ecx, edi
004f9725 movd xmm0, eax
004f9729 cvtdq2pd xmm0, xmm0
004f972d shr eax, 0x1f
004f9730 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
004f9739 cvtpd2ps xmm1, xmm0
004f973d mulss xmm1, xmm2
004f9741 mulss xmm1, dword ptr [0xb6a434]
004f9749 addss xmm1, dword ptr [0xb6a434]
004f9751 movss dword ptr [esp], xmm1
004f9756 call 0x68d7b0
004f975b mov eax, dword ptr [edi + 0x28]
004f975e movss xmm2, dword ptr [0xb6a19c]
004f9766 cmp eax, 0xee
004f976b jne 0x4f97ee
004f9771 call 0x6c3d90
004f9776 push ecx
004f9777 mov ecx, edi
004f9779 movd xmm0, eax
004f977d cvtdq2pd xmm0, xmm0
004f9781 shr eax, 0x1f
004f9784 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
004f978d cvtpd2ps xmm0, xmm0
004f9791 mulss xmm0, xmm2
004f9795 mulss xmm0, dword ptr [0xb6a3b0]
004f979d addss xmm0, dword ptr [0xb6a350]
004f97a5 movss dword ptr [esp], xmm0
004f97aa call 0x68d7b0
004f97af push 1
004f97b1 mov ecx, eax
004f97b3 mov dword ptr [ebp - 0x20], 0
004f97ba push 0
004f97bc xorps xmm0, xmm0
004f97bf mov dword ptr [ebp - 0x1c], 0x3f000000
004f97c6 push 0xff
004f97cb mov eax, dword ptr [ecx]
004f97cd lea edx, [ebp - 0x40]
004f97d0 movups xmmword ptr [ebp - 0x30], xmm0
004f97d4 push -1
004f97d6 movaps xmm0, xmmword ptr [0xb6be20]
004f97dd push edx
004f97de movups xmmword ptr [ebp - 0x40], xmm0
004f97e2 mov dword ptr [ebp - 0x18], 0
004f97e9 call dword ptr [eax + 0x38]
004f97ec jmp 0x4f982c
004f97ee call 0x6c3d90
004f97f3 push ecx
004f97f4 mov ecx, edi
004f97f6 movd xmm0, eax
004f97fa cvtdq2pd xmm0, xmm0
004f97fe shr eax, 0x1f
004f9801 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
004f980a cvtpd2ps xmm0, xmm0
004f980e mulss xmm0, xmm2
004f9812 mulss xmm0, dword ptr [0xb6a3b0]
004f981a addss xmm0, dword ptr [0xb6a350]
004f9822 movss dword ptr [esp], xmm0
004f9827 call 0x68d7b0
004f982c mov eax, dword ptr [edi + 0x28]
004f982f cmp eax, 0x118
004f9834 jne 0x4f99c9
004f983a mov edx, dword ptr [edi + 0xaf0]
004f9840 test edx, edx
004f9842 jg 0x4f9a52
004f9848 mov ecx, edi
004f984a call 0x6ad7a0
004f984f cmp eax, 5
004f9852 jge 0x4f99c6
004f9858 cmp dword ptr [edi + 0xe6c], -1
004f985f je 0x4f987c
004f9861 movss xmm1, dword ptr [0xb6accc]
004f9869 mov ecx, edi
004f986b push 7
004f986d push 0
004f986f call 0x6a15a0
004f9874 test al, al
004f9876 je 0x4f99c6
004f987c cmp dword ptr [edi + 0xe6c], -1
004f9883 movss xmm0, dword ptr [0xc02fec]
004f988b movss dword ptr [ebp - 0x120], xmm0
004f9893 movss xmm0, dword ptr [0xc02ff0]
004f989b movss dword ptr [ebp - 0x11c], xmm0
004f98a3 je 0x4f9915
004f98a5 movss xmm2, dword ptr [0xb6a2cc]
004f98ad lea eax, [ebp - 0x128]
004f98b3 push eax
004f98b4 mov ecx, edi
004f98b6 call 0x6af380
004f98bb movss xmm2, dword ptr [ebp - 0x128]
004f98c3 ucomiss xmm2, dword ptr [0xc02fec]
004f98ca movss xmm1, dword ptr [ebp - 0x124]
004f98d2 lahf 
004f98d3 test ah, 0x44
004f98d6 jp 0x4f98e5
004f98d8 ucomiss xmm1, dword ptr [0xc02ff0]
004f98df lahf 
004f98e0 test ah, 0x44
004f98e3 jnp 0x4f9915
004f98e5 mulss xmm2, dword ptr [0xb6aad4]
004f98ed mulss xmm1, dword ptr [0xb6aad4]
004f98f5 addss xmm2, dword ptr [edi + 0x294]
004f98fd addss xmm1, dword ptr [edi + 0x298]
004f9905 movss dword ptr [ebp - 0x120], xmm2
004f990d movss dword ptr [ebp - 0x11c], xmm1
004f9915 push ecx
004f9916 mov dword ptr [esp], 0xc1f00000
004f991d lea esi, [edi + 0x294]
004f9923 push 0
004f9925 push dword ptr [ebp - 0x11c]
004f992b push dword ptr [ebp - 0x120]
004f9931 push edi
004f9932 push esi
004f9933 call 0x6994f0
004f9938 add esp, 0x14
004f993b mov dword ptr [esp], 0x3f800000
004f9942 push 0
004f9944 push 2
004f9946 push ecx
004f9947 mov dword ptr [esp], 0x3f000000
004f994e mov ecx, edi
004f9950 push 0xb5
004f9955 call 0x6ad720
004f995a push 0xc02fec
004f995f lea ecx, [ebp - 0x6c]
004f9962 mov dword ptr [ebp - 0x120], 0
004f996c mov dword ptr [ebp - 0x11c], 0xc1200000
004f9976 call 0x402120
004f997b push eax
004f997c lea eax, [ebp - 0x120]
004f9982 mov edx, esi
004f9984 push eax
004f9985 mov ecx, 1
004f998a call 0x6aead0
004f998f add esp, 0xc
004f9992 mov ecx, eax
004f9994 mov dword ptr [eax + 0x2b0], 0x3f800000
004f999e push edi
004f999f call 0x447de0
004f99a4 cmp dword ptr [edi + 0xe6c], -1
004f99ab je 0x4f99b4
004f99ad mov eax, 0x5a
004f99b2 jmp 0x4f99c0
004f99b4 call 0x6c3d90
004f99b9 and eax, 1
004f99bc inc eax
004f99bd imul eax, eax, 0x5a
004f99c0 mov dword ptr [edi + 0xaf0], eax
004f99c6 mov eax, dword ptr [edi + 0x28]
004f99c9 cmp eax, 0xd2
004f99ce je 0x4f99d7
004f99d0 cmp eax, 0xd3
004f99d5 jne 0x4f9a34
004f99d7 mov eax, dword ptr [edi + 0x20]
004f99da xor edx, edx
004f99dc mov ecx, 0x32
004f99e1 movss xmm1, dword ptr [0xb6aa60]
004f99e9 div ecx
004f99eb mov ecx, edi
004f99ed movd xmm0, edx
004f99f1 cvtdq2pd xmm0, xmm0
004f99f5 shr edx, 0x1f
004f99f8 addsd xmm0, qword ptr [edx*8 + 0xb6c940]
004f9a01 cvtpd2ps xmm2, xmm0
004f9a05 call 0x6847e0
004f9a0a test eax, eax
004f9a0c je 0x4f9a34
004f9a0e call 0x6c3d90
004f9a13 test al, 1
004f9a15 jne 0x4f9a34
004f9a17 push ecx
004f9a18 mov dword ptr [esp], 0x3f800000
004f9a1f push 0
004f9a21 push 2
004f9a23 push ecx
004f9a24 mov dword ptr [esp], 0x3f333333
004f9a2b mov ecx, edi
004f9a2d push 3
004f9a2f call 0x6ad720
004f9a34 mov ecx, dword ptr [ebp - 0xc]
004f9a37 mov dword ptr fs:[0], ecx
004f9a3e pop ecx
004f9a3f pop edi
004f9a40 pop esi
004f9a41 mov ecx, dword ptr [ebp - 0x14]
004f9a44 xor ecx, ebp
004f9a46 call 0x9eacd7
004f9a4b mov esp, ebp
004f9a4d pop ebp
004f9a4e mov esp, ebx
004f9a50 pop ebx
004f9a51 ret 
