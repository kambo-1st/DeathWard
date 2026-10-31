004f6ee0 push ebx
004f6ee1 mov ebx, esp
004f6ee3 sub esp, 8
004f6ee6 and esp, 0xfffffff8
004f6ee9 add esp, 4
004f6eec push ebp
004f6eed mov ebp, dword ptr [ebx + 4]
004f6ef0 mov dword ptr [esp + 4], ebp
004f6ef4 mov ebp, esp
004f6ef6 push -1
004f6ef8 push 0x9ef215
004f6efd mov eax, dword ptr fs:[0]
004f6f03 push eax
004f6f04 push ebx
004f6f05 sub esp, 0x1f8
004f6f0b mov eax, dword ptr [0xbaa3b4]
004f6f10 xor eax, ebp
004f6f12 mov dword ptr [ebp - 0x14], eax
004f6f15 push esi
004f6f16 push edi
004f6f17 push eax
004f6f18 lea eax, [ebp - 0xc]
004f6f1b mov dword ptr fs:[0], eax
004f6f21 mov edi, ecx
004f6f23 cmp dword ptr [edi + 0x28], 0xa
004f6f27 jne 0x4f6f39
004f6f29 cmp dword ptr [edi + 0x2c], 3
004f6f2d jne 0x4f6f39
004f6f2f call 0x4c70e0
004f6f34 jmp 0x4f864a
004f6f39 movss xmm0, dword ptr [edi + 0x14]
004f6f3e xorps xmm1, xmm1
004f6f41 comiss xmm0, xmm1
004f6f44 jbe 0x4f6f66
004f6f46 mov eax, dword ptr [edi + 8]
004f6f49 cmp eax, dword ptr [edi + 0xc]
004f6f4c je 0x4f6f66
004f6f4e nop 
004f6f50 mov ecx, dword ptr [eax + 0x18]
004f6f53 cmp ecx, dword ptr [edi + 0x28]
004f6f56 jne 0x4f6f5e
004f6f58 mov dword ptr [eax], 0
004f6f5e add eax, 0x38
004f6f61 cmp eax, dword ptr [edi + 0xc]
004f6f64 jne 0x4f6f50
004f6f66 cmp dword ptr [edi + 0xab4], 0
004f6f6d jne 0x4f7206
004f6f73 mov eax, dword ptr [edi + 0x28]
004f6f76 mov dword ptr [edi + 0xab4], 4
004f6f80 mov dword ptr [edi + 0x360], 0
004f6f8a cmp eax, 0x12e
004f6f8f jne 0x4f6fa8
004f6f91 or dword ptr [edi + 0x160], 1
004f6f98 or dword ptr [edi + 0x164], 8
004f6f9f mov byte ptr [edi + 0x308], 1
004f6fa6 jmp 0x4f6ffc
004f6fa8 cmp eax, 0xd0
004f6fad je 0x4f6ffc
004f6faf cmp eax, 0x101
004f6fb4 je 0x4f6ffc
004f6fb6 cmp eax, 0xa
004f6fb9 jne 0x4f6fd2
004f6fbb cmp dword ptr [edi + 0x2c], 2
004f6fbf jne 0x4f6fd2
004f6fc1 push 0
004f6fc3 push 0xb41e78
004f6fc8 lea ecx, [edi + 0x3c]
004f6fcb call 0x405a00
004f6fd0 jmp 0x4f6ffc
004f6fd2 push 1
004f6fd4 push 0xb41e78
004f6fd9 lea ecx, [edi + 0x3c]
004f6fdc call 0x405bb0
004f6fe1 test al, al
004f6fe3 je 0x4f6ffc
004f6fe5 cmp dword ptr [edi + 0x90], 0
004f6fec je 0x4f6ffc
004f6fee lea ecx, [edi + 0x8c]
004f6ff4 xorps xmm1, xmm1
004f6ff7 call 0x403c00
004f6ffc cmp dword ptr [edi + 0x28], 0xd0
004f7003 jne 0x4f7021
004f7005 cmp dword ptr [edi + 0x2c], 2
004f7009 jne 0x4f7021
004f700b push 0
004f700d push 0xb42e9c
004f7012 lea ecx, [edi + 0x3c]
004f7015 mov byte ptr [edi + 0xac], 1
004f701c call 0x405a00
004f7021 push 1
004f7023 push 0xb404ec
004f7028 lea ecx, [edi + 0x3c]
004f702b call 0x405740
004f7030 test al, al
004f7032 je 0x4f7054
004f7034 mov eax, dword ptr [edi + 0x70]
004f7037 test eax, eax
004f7039 je 0x4f7054
004f703b lea ecx, [edi + 0x6c]
004f703e xorps xmm1, xmm1
004f7041 call 0x403c00
004f7046 mov eax, dword ptr [edi + 0x70]
004f7049 test eax, eax
004f704b je 0x4f7054
004f704d mov byte ptr [edi + 0x80], 0
004f7054 mov eax, dword ptr [edi + 0x28]
004f7057 cmp eax, 0xfc
004f705c jne 0x4f70bc
004f705e movaps xmm1, xmmword ptr [0xb6bd50]
004f7065 lea ecx, [edi + 0x1dc]
004f706b lea eax, [ebp - 0x208]
004f7071 mov dword ptr [ebp - 0x1e8], 0
004f707b mov dword ptr [ebp - 0x1e4], 0
004f7085 xorps xmm0, xmm0
004f7088 mov dword ptr [ebp - 0x1e0], 0
004f7092 cmp ecx, eax
004f7094 je 0x4f7206
004f709a mov eax, dword ptr [ebp - 0x1e0]
004f70a0 movups xmmword ptr [ecx + 0x10], xmm0
004f70a4 movq xmm0, qword ptr [ebp - 0x1e8]
004f70ac movq qword ptr [ecx + 0x20], xmm0
004f70b1 movups xmmword ptr [ecx], xmm1
004f70b4 mov dword ptr [ecx + 0x28], eax
004f70b7 jmp 0x4f7206
004f70bc cmp eax, 0x12e
004f70c1 jne 0x4f7206
004f70c7 lea ecx, [ebp - 0x40]
004f70ca mov dword ptr [edi + 0x180], 2
004f70d4 call 0x402120
004f70d9 lea ecx, [edi + 0x1dc]
004f70df cmp ecx, eax
004f70e1 je 0x4f7101
004f70e3 movups xmm0, xmmword ptr [eax]
004f70e6 movups xmmword ptr [ecx], xmm0
004f70e9 movups xmm0, xmmword ptr [eax + 0x10]
004f70ed movups xmmword ptr [ecx + 0x10], xmm0
004f70f1 movq xmm0, qword ptr [eax + 0x20]
004f70f6 movq qword ptr [ecx + 0x20], xmm0
004f70fb mov eax, dword ptr [eax + 0x28]
004f70fe mov dword ptr [ecx + 0x28], eax
004f7101 mov dword ptr [edi + 0x1ec], 0x3f800000
004f710b mov dword ptr [edi + 0x1f0], 0x3f800000
004f7115 mov dword ptr [edi + 0x1f4], 0x3f800000
004f711f mov dword ptr [edi + 0x1f8], 0x3f800000
004f7129 call 0x6c3d90
004f712e xor edx, edx
004f7130 mov ecx, 0x3c
004f7135 div ecx
004f7137 add edx, 0x5a
004f713a cmp dword ptr [edi + 0x2c], 0xa
004f713e mov dword ptr [edi + 0xb10], edx
004f7144 jne 0x4f7206
004f714a push 0
004f714c push 0xb40d14
004f7151 lea ecx, [edi + 0x3c]
004f7154 call 0x405a00
004f7159 cmp dword ptr [edi + 0x70], 0
004f715d je 0x4f7206
004f7163 push 2
004f7165 lea ecx, [edi + 0x6c]
004f7168 call 0x405d30
004f716d mov edx, eax
004f716f mov dword ptr [ebp - 0x1b4], edx
004f7175 test edx, edx
004f7177 je 0x4f7206
004f717d cmp dword ptr [edi + 0xbc], 1
004f7184 jg 0x4f71aa
004f7186 cmp dword ptr [edi + 0x50], 0x10
004f718a lea eax, [edi + 0x3c]
004f718d jb 0x4f7192
004f718f mov eax, dword ptr [edi + 0x3c]
004f7192 push 1
004f7194 push eax
004f7195 push 0xa0830c
004f719a push 3
004f719c call 0x95e330
004f71a1 mov edx, dword ptr [ebp - 0x1b4]
004f71a7 add esp, 0x10
004f71aa mov ecx, dword ptr [edi + 0xb8]
004f71b0 mov eax, dword ptr [edx]
004f71b2 mov dword ptr [ecx + 0xdc], eax
004f71b8 mov eax, dword ptr [edx + 4]
004f71bb mov dword ptr [ecx + 0xe0], eax
004f71c1 cmp dword ptr [edi + 0xbc], 1
004f71c8 jg 0x4f71ee
004f71ca cmp dword ptr [edi + 0x50], 0x10
004f71ce lea eax, [edi + 0x3c]
004f71d1 jb 0x4f71d6
004f71d3 mov eax, dword ptr [edi + 0x3c]
004f71d6 push 1
004f71d8 push eax
004f71d9 push 0xa0830c
004f71de push 3
004f71e0 call 0x95e330
004f71e5 mov edx, dword ptr [ebp - 0x1b4]
004f71eb add esp, 0x10
004f71ee mov ecx, dword ptr [edi + 0xb8]
004f71f4 mov eax, dword ptr [edx + 0x10]
004f71f7 mov dword ptr [ecx + 0xd0], eax
004f71fd mov eax, dword ptr [edx + 0x14]
004f7200 mov dword ptr [ecx + 0xd4], eax
004f7206 cmp dword ptr [edi + 0x28], 0xd0
004f720d jne 0x4f725e
004f720f cmp dword ptr [edi + 0x2c], 2
004f7213 jne 0x4f725e
004f7215 cmp dword ptr [edi + 0x70], 0
004f7219 je 0x4f725e
004f721b push 0xb42ea4
004f7220 lea ecx, [edi + 0x6c]
004f7223 call 0x405da0
004f7228 mov esi, eax
004f722a test esi, esi
004f722c je 0x4f725e
004f722e cmp byte ptr [esi + 0xc], 0
004f7232 je 0x4f725e
004f7234 push 0xb42e9c
004f7239 lea ecx, [edi + 0x3c]
004f723c call 0x406350
004f7241 mov edx, eax
004f7243 test edx, edx
004f7245 je 0x4f725e
004f7247 mov ecx, dword ptr [esi]
004f7249 mov dword ptr [edx + 0x40], ecx
004f724c mov ecx, dword ptr [esi + 4]
004f724f mov dword ptr [edx + 0x44], ecx
004f7252 mov eax, dword ptr [esi + 0x10]
004f7255 mov dword ptr [edx + 0x34], eax
004f7258 mov eax, dword ptr [esi + 0x14]
004f725b mov dword ptr [edx + 0x38], eax
004f725e mov eax, dword ptr [edi + 0xab4]
004f7264 test eax, eax
004f7266 je 0x4f864a
004f726c cmp byte ptr [edi + 0x16b], 0
004f7273 je 0x4f73cc
004f7279 movss xmm0, dword ptr [edi + 0x2d8]
004f7281 comiss xmm0, dword ptr [0xb6aef8]
004f7288 jbe 0x4f864a
004f728e call 0x6c3d90
004f7293 test al, 1
004f7295 jne 0x4f864a
004f729b mov eax, dword ptr [edi + 0x28]
004f729e cmp eax, 0xa
004f72a1 jne 0x4f72fe
004f72a3 call 0x6c3d90
004f72a8 xor edx, edx
004f72aa mov ecx, 3
004f72af div ecx
004f72b1 test edx, edx
004f72b3 jne 0x4f72c0
004f72b5 cmp dword ptr [edi + 0x2c], 2
004f72b9 je 0x4f72c0
004f72bb lea eax, [ecx - 2]
004f72be jmp 0x4f72c2
004f72c0 xor eax, eax
004f72c2 push -1
004f72c4 push 0
004f72c6 push eax
004f72c7 push 0xb
004f72c9 mov ecx, edi
004f72cb call 0x697c60
004f72d0 mov byte ptr [edi + 0x16b], 0
004f72d7 call 0x6c3d90
004f72dc xor edx, edx
004f72de mov ecx, 0x14
004f72e3 div ecx
004f72e5 mov eax, dword ptr [edi + 0x2dc]
004f72eb add edx, ecx
004f72ed mov dword ptr [edi + 0x2d8], eax
004f72f3 mov dword ptr [edi + 0xaf0], edx
004f72f9 jmp 0x4f864a
004f72fe cmp eax, 0xd0
004f7303 jne 0x4f738d
004f7309 mov eax, dword ptr [edi + 0x2c]
004f730c cmp eax, 1
004f730f jne 0x4f733b
004f7311 push -1
004f7313 push 0
004f7315 push 0
004f7317 push 0xd2
004f731c mov ecx, edi
004f731e call 0x697c60
004f7323 mov eax, dword ptr [edi + 0x2dc]
004f7329 mov byte ptr [edi + 0x16b], 0
004f7330 mov dword ptr [edi + 0x2d8], eax
004f7336 jmp 0x4f864a
004f733b cmp eax, 2
004f733e jne 0x4f864a
004f7344 call 0x6c3d90
004f7349 mov ecx, dword ptr [0xbfd65c]
004f734f push eax
004f7350 push 0
004f7352 push edi
004f7353 push 0xc02fec
004f7358 lea eax, [edi + 0x294]
004f735e push eax
004f735f push 0xa
004f7361 push 0x21
004f7363 call 0x422e20
004f7368 movss xmm0, dword ptr [eax + 0x294]
004f7370 movss xmm1, dword ptr [eax + 0x298]
004f7378 movss dword ptr [eax + 0x28c], xmm0
004f7380 movss dword ptr [eax + 0x290], xmm1
004f7388 jmp 0x4f864a
004f738d cmp eax, 0x101
004f7392 jne 0x4f864a
004f7398 cmp dword ptr [edi + 0x2c], 0
004f739c jne 0x4f864a
004f73a2 push -1
004f73a4 push 0
004f73a6 push 0
004f73a8 push 0xd0
004f73ad mov ecx, edi
004f73af call 0x697c60
004f73b4 mov eax, dword ptr [edi + 0x2dc]
004f73ba mov byte ptr [edi + 0x16b], 0
004f73c1 mov dword ptr [edi + 0x2d8], eax
004f73c7 jmp 0x4f864a
004f73cc mov ecx, dword ptr [edi + 0x28]
004f73cf cmp ecx, 0xd0
004f73d5 je 0x4f761d
004f73db cmp ecx, 0x101
004f73e1 je 0x4f761d
004f73e7 cmp ecx, 0x11c
004f73ed jne 0x4f750b
004f73f3 cmp eax, 8
004f73f6 jne 0x4f750b
004f73fc push 0
004f73fe mov ecx, edi
004f7400 call 0x6afe20
004f7405 push 0xb400ac
004f740a lea ecx, [edi + 0x8c]
004f7410 call 0x405e90
004f7415 test al, al
004f7417 je 0x4f74be
004f741d cmp dword ptr [edi + 0xe6c], -1
004f7424 lea esi, [edi + 0x294]
004f742a je 0x4f7446
004f742c mov eax, dword ptr [edi + 0xe70]
004f7432 mov ecx, dword ptr [edi + 0xe74]
004f7438 mov dword ptr [ebp - 0x1b0], eax
004f743e mov dword ptr [ebp - 0x1ac], ecx
004f7444 jmp 0x4f7476
004f7446 mov ecx, edi
004f7448 call 0x695680
004f744d movss xmm0, dword ptr [eax + 0x294]
004f7455 movss xmm1, dword ptr [eax + 0x298]
004f745d subss xmm0, dword ptr [esi]
004f7461 subss xmm1, dword ptr [esi + 4]
004f7466 movss dword ptr [ebp - 0x1b0], xmm0
004f746e movss dword ptr [ebp - 0x1ac], xmm1
004f7476 lea ecx, [ebp - 0x1b0]
004f747c mov eax, dword ptr [ecx]
004f747e mov ecx, dword ptr [ecx + 4]
004f7481 mov dword ptr [ebp - 0x1ac], ecx
004f7487 lea ecx, [ebp - 0x100]
004f748d mov dword ptr [ebp - 0x1b0], eax
004f7493 call 0x430d70
004f7498 push eax
004f7499 push 0
004f749b push ecx
004f749c lea eax, [ebp - 0x1bc]
004f74a2 mov dword ptr [esp], 0x40e00000
004f74a9 push eax
004f74aa lea ecx, [ebp - 0x1b0]
004f74b0 call 0x9628d0
004f74b5 push eax
004f74b6 push esi
004f74b7 mov ecx, edi
004f74b9 call 0x6a1a20
004f74be cmp dword ptr [edi + 0x90], 0
004f74c5 lea ecx, [edi + 0x3c]
004f74c8 je 0x4f74d3
004f74ca cmp byte ptr [edi + 0xa0], 0
004f74d1 jne 0x4f74f3
004f74d3 push 0
004f74d5 push 0xb41e78
004f74da mov dword ptr [edi + 0xab4], 4
004f74e4 mov dword ptr [edi + 0x360], 0
004f74ee call 0x405cb0
004f74f3 movss xmm0, dword ptr [edi + 0x2c4]
004f74fb mulss xmm0, dword ptr [0xb6a434]
004f7503 movss dword ptr [edi + 0x2c4], xmm0
004f750b cmp dword ptr [edi + 0x28], 0x12e
004f7512 jne 0x4f7526
004f7514 cmp dword ptr [edi + 0xab4], 0x10
004f751b mov eax, 0x12e
004f7520 je 0x4f7e48
004f7526 push 8
004f7528 mov dword ptr [ebp - 0x2c], 0
004f752f lea ecx, [ebp - 0x2c]
004f7532 push 0xb404ec
004f7537 mov dword ptr [ebp - 0x1c], 0
004f753e mov dword ptr [ebp - 0x18], 0xf
004f7545 mov byte ptr [ebp - 0x2c], 0
004f7549 call 0x407c80
004f754e mov dword ptr [ebp - 4], 0
004f7555 lea ecx, [ebp - 0x58]
004f7558 push 8
004f755a mov dword ptr [ebp - 0x58], 0
004f7561 push 0xb40504
004f7566 mov dword ptr [ebp - 0x48], 0
004f756d mov dword ptr [ebp - 0x44], 0xf
004f7574 mov byte ptr [ebp - 0x58], 0
004f7578 call 0x407c80
004f757d push ecx
004f757e mov byte ptr [ebp - 4], 1
004f7582 lea eax, [ebp - 0x2c]
004f7585 mov dword ptr [esp], 0x3dcccccd
004f758c mov ecx, edi
004f758e push eax
004f758f lea eax, [ebp - 0x58]
004f7592 push eax
004f7593 call 0x6980a0
004f7598 mov byte ptr [ebp - 4], 0
004f759c mov edx, dword ptr [ebp - 0x44]
004f759f cmp edx, 0x10
004f75a2 jb 0x4f75cc
004f75a4 mov ecx, dword ptr [ebp - 0x58]
004f75a7 inc edx
004f75a8 mov eax, ecx
004f75aa cmp edx, 0x1000
004f75b0 jb 0x4f75c2
004f75b2 mov ecx, dword ptr [ecx - 4]
004f75b5 add edx, 0x23
004f75b8 sub eax, ecx
004f75ba add eax, -4
004f75bd cmp eax, 0x1f
004f75c0 ja 0x4f7617
004f75c2 push edx
004f75c3 push ecx
004f75c4 call 0x9eb08e
004f75c9 add esp, 8
004f75cc mov dword ptr [ebp - 4], 0xffffffff
004f75d3 mov edx, dword ptr [ebp - 0x18]
004f75d6 mov dword ptr [ebp - 0x48], 0
004f75dd mov dword ptr [ebp - 0x44], 0xf
004f75e4 mov byte ptr [ebp - 0x58], 0
004f75e8 cmp edx, 0x10
004f75eb jb 0x4f7e45
004f75f1 mov ecx, dword ptr [ebp - 0x2c]
004f75f4 inc edx
004f75f5 mov eax, ecx
004f75f7 cmp edx, 0x1000
004f75fd jb 0x4f7e3b
004f7603 mov ecx, dword ptr [ecx - 4]
004f7606 add edx, 0x23
004f7609 sub eax, ecx
004f760b add eax, -4
004f760e cmp eax, 0x1f
004f7611 jbe 0x4f7e3b
004f7617 call dword ptr [0xa065ac]
004f761d cmp eax, 4
004f7620 jne 0x4f77ca
004f7626 mov edx, dword ptr [edi + 0x360]
004f762c cmp edx, 0x64
004f762f jge 0x4f764b
004f7631 cvttss2si ecx, dword ptr [edi + 0x2fc]
004f7639 cvttss2si eax, dword ptr [edi + 0x2f8]
004f7641 sub ecx, eax
004f7643 add ecx, edx
004f7645 mov dword ptr [edi + 0x360], ecx
004f764b mov ecx, edi
004f764d call 0x695680
004f7652 cmp dword ptr [edi + 0xe6c], -1
004f7659 mov esi, eax
004f765b mov ecx, edi
004f765d je 0x4f769d
004f765f push 9
004f7661 call 0x6af050
004f7666 test al, al
004f7668 jne 0x4f76fe
004f766e movss xmm2, dword ptr [0xb6a2cc]
004f7676 lea eax, [ebp - 0x1bc]
004f767c push 0xc02fec
004f7681 push ecx
004f7682 push eax
004f7683 mov ecx, edi
004f7685 call 0x6af380
004f768a add esp, 4
004f768d mov ecx, eax
004f768f call 0x962ca0
004f7694 test al, al
004f7696 jne 0x4f76fe
004f7698 jmp 0x4f750b
004f769d push esi
004f769e call 0x6aeb40
004f76a3 test al, al
004f76a5 je 0x4f750b
004f76ab movss xmm0, dword ptr [esi + 0x294]
004f76b3 movss xmm1, dword ptr [esi + 0x298]
004f76bb subss xmm0, dword ptr [edi + 0x294]
004f76c3 subss xmm1, dword ptr [edi + 0x298]
004f76cb mulss xmm0, xmm0
004f76cf mulss xmm1, xmm1
004f76d3 addss xmm1, xmm0
004f76d7 movss xmm0, dword ptr [0xb6ad60]
004f76df comiss xmm0, xmm1
004f76e2 jbe 0x4f750b
004f76e8 call 0x6c3d90
004f76ed xor edx, edx
004f76ef mov ecx, 0x78
004f76f4 div ecx
004f76f6 test edx, edx
004f76f8 jne 0x4f750b
004f76fe cmp dword ptr [edi + 0x360], 0x64
004f7705 jl 0x4f750b
004f770b push ecx
004f770c mov dword ptr [esp], 0x3f800000
004f7713 push 0
004f7715 push 5
004f7717 push ecx
004f7718 mov dword ptr [esp], 0x3f800000
004f771f mov ecx, edi
004f7721 push 0xa7
004f7726 call 0x6ad720
004f772b movss xmm4, dword ptr [edi + 0x2b8]
004f7733 movss xmm3, dword ptr [edi + 0x2bc]
004f773b movaps xmm2, xmm4
004f773e andps xmm2, xmmword ptr [0xb6c980]
004f7745 movaps xmm0, xmm3
004f7748 andps xmm0, xmmword ptr [0xb6c980]
004f774f comiss xmm2, xmm0
004f7752 mov dword ptr [edi + 0xab4], 8
004f775c mov dword ptr [edi + 0x360], 0
004f7766 jbe 0x4f77ad
004f7768 mulss xmm3, xmm3
004f776c mulss xmm4, xmm4
004f7770 addss xmm3, xmm4
004f7774 comiss xmm3, dword ptr [0xb6a214]
004f777b jbe 0x4f77ad
004f777d push 0
004f777f push 0xb4277c
004f7784 lea ecx, [edi + 0x3c]
004f7787 call 0x4054f0
004f778c xorps xmm0, xmm0
004f778f mov ecx, edi
004f7791 comiss xmm0, dword ptr [edi + 0x2b8]
004f7798 push 1
004f779a seta al
004f779d mov byte ptr [edi + 0x13c], al
004f77a3 call 0x6afe20
004f77a8 jmp 0x4f864a
004f77ad push 0
004f77af push 0xb42818
004f77b4 lea ecx, [edi + 0x3c]
004f77b7 call 0x4054f0
004f77bc push 1
004f77be mov ecx, edi
004f77c0 call 0x6afe20
004f77c5 jmp 0x4f864a
004f77ca cmp eax, 8
004f77cd jne 0x4f750b
004f77d3 push 0
004f77d5 mov ecx, edi
004f77d7 call 0x6afe20
004f77dc cmp dword ptr [edi + 0x28], 0x101
004f77e3 jne 0x4f7c59
004f77e9 cmp dword ptr [edi + 0x2c], 0
004f77ed jne 0x4f7c59
004f77f3 push 0xb42ed8
004f77f8 lea ecx, [edi + 0x3c]
004f77fb call 0x4060f0
004f7800 test al, al
004f7802 je 0x4f785e
004f7804 mov ecx, edi
004f7806 call 0x695680
004f780b lea ecx, [ebp - 0x1b0]
004f7811 movss xmm0, dword ptr [eax + 0x294]
004f7819 movss xmm1, dword ptr [eax + 0x298]
004f7821 lea eax, [ebp - 0x1bc]
004f7827 subss xmm0, dword ptr [edi + 0x294]
004f782f subss xmm1, dword ptr [edi + 0x298]
004f7837 push eax
004f7838 movss dword ptr [ebp - 0x1b0], xmm0
004f7840 movss dword ptr [ebp - 0x1ac], xmm1
004f7848 call 0x962560
004f784d mov ecx, dword ptr [eax]
004f784f mov dword ptr [edi + 0x28c], ecx
004f7855 mov eax, dword ptr [eax + 4]
004f7858 mov dword ptr [edi + 0x290], eax
004f785e push 0xb400ac
004f7863 lea ecx, [edi + 0x3c]
004f7866 call 0x4060f0
004f786b test al, al
004f786d je 0x4f78a9
004f786f cmp dword ptr [edi + 0xe6c], -1
004f7876 je 0x4f78a9
004f7878 lea ecx, [edi + 0xe70]
004f787e push 0xc02fec
004f7883 call 0x962ca0
004f7888 test al, al
004f788a je 0x4f78a9
004f788c lea eax, [ebp - 0x1c4]
004f7892 push eax
004f7893 call 0x962560
004f7898 mov ecx, dword ptr [eax]
004f789a mov dword ptr [edi + 0x28c], ecx
004f78a0 mov eax, dword ptr [eax + 4]
004f78a3 mov dword ptr [edi + 0x290], eax
004f78a9 push 0xb400ac
004f78ae lea ecx, [edi + 0x3c]
004f78b1 call 0x406150
004f78b6 test al, al
004f78b8 je 0x4f7dfb
004f78be push 0xb404bc
004f78c3 lea ecx, [edi + 0x3c]
004f78c6 call 0x406150
004f78cb test al, al
004f78cd jne 0x4f7dfb
004f78d3 mov eax, dword ptr [edi + 0x360]
004f78d9 test eax, eax
004f78db jne 0x4f797b
004f78e1 mov esi, dword ptr [0xbfd680]
004f78e7 lea ecx, [ebp - 0x1b4]
004f78ed mov dword ptr [ebp - 0x1b4], 0xd4
004f78f7 call 0x8b1340
004f78fc sub esp, 8
004f78ff mov dword ptr [esp + 4], 0
004f7907 mov dword ptr [esp], 0x3f800000
004f790e push 0
004f7910 push 2
004f7912 push ecx
004f7913 mov dword ptr [esp], 0x3f333333
004f791a lea ecx, [esi + 0x29de0]
004f7920 push dword ptr [ebp - 0x1b4]
004f7926 call 0x888de0
004f792b mov esi, dword ptr [0xbfd680]
004f7931 lea ecx, [ebp - 0x1b4]
004f7937 mov dword ptr [ebp - 0x1b4], 0x25
004f7941 call 0x8b1340
004f7946 sub esp, 8
004f7949 mov dword ptr [esp + 4], 0
004f7951 mov dword ptr [esp], 0x3f800000
004f7958 push 0
004f795a push 2
004f795c push ecx
004f795d mov dword ptr [esp], 0x3f800000
004f7964 lea ecx, [esi + 0x29de0]
004f796a push dword ptr [ebp - 0x1b4]
004f7970 call 0x888de0
004f7975 mov eax, dword ptr [edi + 0x360]
004f797b movd xmm1, eax
004f797f cvtdq2ps xmm1, xmm1
004f7982 mulss xmm1, dword ptr [0xb6a9ec]
004f798a movaps xmm0, xmm1
004f798d mulss xmm1, dword ptr [edi + 0x290]
004f7995 mulss xmm0, dword ptr [edi + 0x28c]
004f799d addss xmm1, dword ptr [edi + 0x298]
004f79a5 addss xmm0, dword ptr [edi + 0x294]
004f79ad movss dword ptr [ebp - 0x1ac], xmm1
004f79b5 movss dword ptr [ebp - 0x1b0], xmm0
004f79bd call 0x6c3d90
004f79c2 mov ecx, dword ptr [0xbfd65c]
004f79c8 push eax
004f79c9 push 0
004f79cb push edi
004f79cc push 0xc02fec
004f79d1 lea eax, [ebp - 0x1b0]
004f79d7 push eax
004f79d8 push 0x17
004f79da push 0x3e8
004f79df call 0x422e20
004f79e4 movd xmm0, dword ptr [edi + 0x360]
004f79ec mov ecx, eax
004f79ee cvtdq2ps xmm0, xmm0
004f79f1 mov eax, dword ptr [ecx]
004f79f3 mov dword ptr [ecx + 0x3ac], 0xf
004f79fd mov dword ptr [ecx + 0x3b0], 0xf
004f7a07 mulss xmm0, dword ptr [0xb6a290]
004f7a0f addss xmm0, dword ptr [0xb6a5a4]
004f7a17 movss dword ptr [ebp - 0x1b4], xmm0
004f7a1f movss dword ptr [ecx + 0xd8], xmm0
004f7a27 movss dword ptr [ecx + 0xdc], xmm0
004f7a2f call dword ptr [eax + 0xc]
004f7a32 push ecx
004f7a33 mov ecx, dword ptr [0xbfd65c]
004f7a39 lea eax, [ebp - 0x1b0]
004f7a3f mov dword ptr [esp], 0
004f7a46 push eax
004f7a47 mov ecx, dword ptr [ecx + 0x18190]
004f7a4d call 0x7cf0a0
004f7a52 test al, al
004f7a54 je 0x4f7c3c
004f7a5a call 0x6c3d90
004f7a5f lea ecx, [ebp - 0x40]
004f7a62 movd xmm0, eax
004f7a66 cvtdq2pd xmm0, xmm0
004f7a6a shr eax, 0x1f
004f7a6d addsd xmm0, qword ptr [eax*8 + 0xb6c940]
004f7a76 cvtpd2ps xmm1, xmm0
004f7a7a mulss xmm1, dword ptr [0xb6a19c]
004f7a82 movaps xmm0, xmm1
004f7a85 mulss xmm1, dword ptr [edi + 0x290]
004f7a8d mulss xmm0, dword ptr [edi + 0x28c]
004f7a95 addss xmm1, xmm1
004f7a99 addss xmm0, xmm0
004f7a9d movss dword ptr [ebp - 0x1c8], xmm1
004f7aa5 movss dword ptr [ebp - 0x1cc], xmm0
004f7aad call 0x65add0
004f7ab2 movaps xmm0, xmmword ptr [0xb6bd30]
004f7ab9 movups xmmword ptr [ebp - 0x40], xmm0
004f7abd mov dword ptr [ebp - 0x20], 0x3da3d70a
004f7ac4 mov dword ptr [ebp - 0x1c], 0x3f000000
004f7acb mov dword ptr [ebp - 0x18], 0x3c23d70a
004f7ad2 mov dword ptr [ebp - 0x1d4], 0
004f7adc call 0x6c3d90
004f7ae1 movss xmm1, dword ptr [edi + 0x28c]
004f7ae9 lea edx, [ebp - 0x1bc]
004f7aef mulss xmm1, dword ptr [0xb6a8f4]
004f7af7 mov ecx, 2
004f7afc movd xmm0, eax
004f7b00 cvtdq2pd xmm0, xmm0
004f7b04 shr eax, 0x1f
004f7b07 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
004f7b10 lea eax, [ebp - 0x1cc]
004f7b16 push eax
004f7b17 lea eax, [ebp - 0x40]
004f7b1a push eax
004f7b1b cvtpd2ps xmm0, xmm0
004f7b1f lea eax, [ebp - 0x1d4]
004f7b25 push eax
004f7b26 mulss xmm0, dword ptr [0xb6a19c]
004f7b2e mulss xmm0, dword ptr [0xb6aed4]
004f7b36 movss dword ptr [ebp - 0x1d0], xmm0
004f7b3e movss xmm0, dword ptr [ebp - 0x1b0]
004f7b46 subss xmm0, xmm1
004f7b4a movss xmm1, dword ptr [edi + 0x290]
004f7b52 mulss xmm1, dword ptr [0xb6a8f4]
004f7b5a movss dword ptr [ebp - 0x1bc], xmm0
004f7b62 movss xmm0, dword ptr [ebp - 0x1ac]
004f7b6a subss xmm0, xmm1
004f7b6e movss dword ptr [ebp - 0x1b8], xmm0
004f7b76 call 0x6aead0
004f7b7b add esp, 0xc
004f7b7e mov esi, eax
004f7b80 call 0x6c3d90
004f7b85 movd xmm0, eax
004f7b89 cvtdq2pd xmm0, xmm0
004f7b8d shr eax, 0x1f
004f7b90 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
004f7b99 cvtpd2ps xmm0, xmm0
004f7b9d mulss xmm0, dword ptr [0xb6a19c]
004f7ba5 mulss xmm0, dword ptr [0xb6ac40]
004f7bad movss dword ptr [esi + 0xe0], xmm0
004f7bb5 call 0x6c3d90
004f7bba mov ecx, dword ptr [0xbfd65c]
004f7bc0 push eax
004f7bc1 push 0
004f7bc3 push 0
004f7bc5 push 0xc02fec
004f7bca lea eax, [ebp - 0x1b0]
004f7bd0 push eax
004f7bd1 push 7
004f7bd3 push 0x3e8
004f7bd8 call 0x422e20
004f7bdd movss xmm0, dword ptr [ebp - 0x1b4]
004f7be5 lea ecx, [ebp - 0x40]
004f7be8 mov esi, eax
004f7bea movss dword ptr [esi + 0x2cc], xmm0
004f7bf2 movss dword ptr [esi + 0x2d0], xmm0
004f7bfa call 0x65add0
004f7bff movaps xmm0, xmmword ptr [0xb6ba00]
004f7c06 movups xmmword ptr [ebp - 0x40], xmm0
004f7c0a mov dword ptr [ebp - 0x20], 0x3da3d70a
004f7c11 mov eax, dword ptr [esi]
004f7c13 lea ecx, [ebp - 0x40]
004f7c16 push 1
004f7c18 push 0
004f7c1a push 0xff
004f7c1f push -1
004f7c21 push ecx
004f7c22 mov ecx, esi
004f7c24 mov dword ptr [ebp - 0x1c], 0x3f000000
004f7c2b mov dword ptr [ebp - 0x18], 0x3c23d70a
004f7c32 call dword ptr [eax + 0x38]
004f7c35 mov eax, dword ptr [esi]
004f7c37 mov ecx, esi
004f7c39 call dword ptr [eax + 0xc]
004f7c3c cvttss2si ecx, dword ptr [edi + 0x2fc]
004f7c44 cvttss2si eax, dword ptr [edi + 0x2f8]
004f7c4c sub ecx, eax
004f7c4e add dword ptr [edi + 0x360], ecx
004f7c54 jmp 0x4f7dfb
004f7c59 push 0xb400ac
004f7c5e lea ecx, [edi + 0x3c]
004f7c61 call 0x4060f0
004f7c66 test al, al
004f7c68 je 0x4f7dfb
004f7c6e cmp dword ptr [edi + 0x28], 0x101
004f7c75 jne 0x4f7d5e
004f7c7b movss xmm2, dword ptr [0xb6a614]
004f7c83 push ecx
004f7c84 mov dword ptr [esp], 0x3f800000
004f7c8b push 0
004f7c8d push 2
004f7c8f push 0xd5
004f7c94 call 0x8b1480
004f7c99 lea ecx, [ebp - 0x100]
004f7c9f call 0x430d70
004f7ca4 mov eax, dword ptr [ebp - 0xa4]
004f7caa mov ecx, edi
004f7cac or dword ptr [ebp - 0xa8], 3
004f7cb3 mov dword ptr [ebp - 0xa4], eax
004f7cb9 mov dword ptr [ebp - 0xec], 0x3fc00000
004f7cc3 call 0x695680
004f7cc8 cmp dword ptr [edi + 0xe6c], -1
004f7ccf lea esi, [edi + 0x294]
004f7cd5 movss xmm0, dword ptr [eax + 0x294]
004f7cdd movss xmm1, dword ptr [eax + 0x298]
004f7ce5 subss xmm0, dword ptr [esi]
004f7ce9 subss xmm1, dword ptr [esi + 4]
004f7cee movss dword ptr [ebp - 0x1b0], xmm0
004f7cf6 movss dword ptr [ebp - 0x1ac], xmm1
004f7cfe je 0x4f7d2d
004f7d00 lea ecx, [edi + 0xe70]
004f7d06 push 0xc02fec
004f7d0b call 0x962ca0
004f7d10 test al, al
004f7d12 je 0x4f7d2d
004f7d14 movss xmm0, dword ptr [ecx]
004f7d18 movss dword ptr [ebp - 0x1b0], xmm0
004f7d20 movss xmm0, dword ptr [ecx + 4]
004f7d25 movss dword ptr [ebp - 0x1ac], xmm0
004f7d2d lea eax, [ebp - 0x100]
004f7d33 push eax
004f7d34 push 0
004f7d36 push ecx
004f7d37 lea eax, [ebp - 0x1bc]
004f7d3d mov dword ptr [esp], 0x40e00000
004f7d44 push eax
004f7d45 lea ecx, [ebp - 0x1b0]
004f7d4b call 0x9628d0
004f7d50 push eax
004f7d51 push esi
004f7d52 mov ecx, edi
004f7d54 call 0x6a1a20
004f7d59 jmp 0x4f7dfb
004f7d5e push 0
004f7d60 push 1
004f7d62 push edi
004f7d63 push ecx
004f7d64 mov ecx, dword ptr [0xbfd65c]
004f7d6a lea esi, [edi + 0x294]
004f7d70 mov dword ptr [esp], 0x42f00000
004f7d77 push esi
004f7d78 call 0x6d6570
004f7d7d mov eax, dword ptr [edi + 0x2c]
004f7d80 cmp eax, 1
004f7d83 jne 0x4f7db8
004f7d85 lea ecx, [ebp - 0x100]
004f7d8b mov dword ptr [ebp - 0x1bc], 0x41000000
004f7d95 mov dword ptr [ebp - 0x1b8], 0x40c00000
004f7d9f call 0x430d70
004f7da4 push eax
004f7da5 push 9
004f7da7 lea eax, [ebp - 0x1bc]
004f7dad mov ecx, edi
004f7daf push eax
004f7db0 push esi
004f7db1 call 0x6a1a20
004f7db6 jmp 0x4f7dfb
004f7db8 cmp eax, 2
004f7dbb jne 0x4f7dfb
004f7dbd call 0x6c3d90
004f7dc2 mov ecx, dword ptr [0xbfd65c]
004f7dc8 push eax
004f7dc9 push 0
004f7dcb push edi
004f7dcc push 0xc02fec
004f7dd1 push esi
004f7dd2 push 0xa
004f7dd4 push 0x21
004f7dd6 call 0x422e20
004f7ddb movss xmm0, dword ptr [eax + 0x294]
004f7de3 movss xmm1, dword ptr [eax + 0x298]
004f7deb movss dword ptr [eax + 0x28c], xmm0
004f7df3 movss dword ptr [eax + 0x290], xmm1
004f7dfb cmp dword ptr [edi + 0x70], 0
004f7dff je 0x4f7e0a
004f7e01 cmp byte ptr [edi + 0x80], 0
004f7e08 jne 0x4f7e1e
004f7e0a mov dword ptr [edi + 0xab4], 4
004f7e14 mov dword ptr [edi + 0x360], 0
004f7e1e movss xmm0, dword ptr [edi + 0x2c4]
004f7e26 mulss xmm0, dword ptr [0xb6a434]
004f7e2e movss dword ptr [edi + 0x2c4], xmm0
004f7e36 jmp 0x4f864a
004f7e3b push edx
004f7e3c push ecx
004f7e3d call 0x9eb08e
004f7e42 add esp, 8
004f7e45 mov eax, dword ptr [edi + 0x28]
004f7e48 mov dword ptr [edi + 0xb84], 0x3f19999a
004f7e52 cmp eax, 0xd0
004f7e57 je 0x4f7eeb
004f7e5d cmp eax, 0x101
004f7e62 je 0x4f7eeb
004f7e68 cmp eax, 0x12e
004f7e6d jne 0x4f7e88
004f7e6f cmp dword ptr [edi + 0x2c], 0xa
004f7e73 jne 0x4f7f0c
004f7e79 mov dword ptr [edi + 0xb84], 0x3ef5c290
004f7e83 jmp 0x4f7f0c
004f7e88 cmp eax, 0xfc
004f7e8d jne 0x4f7e9b
004f7e8f mov dword ptr [edi + 0xb84], 0x3f666667
004f7e99 jmp 0x4f7f0c
004f7e9b mov edx, dword ptr [edi + 0x2c]
004f7e9e cmp edx, 1
004f7ea1 je 0x4f7edf
004f7ea3 cmp eax, 0x11c
004f7ea8 je 0x4f7edf
004f7eaa lea ecx, [edi + 0x3c]
004f7ead cmp edx, 2
004f7eb0 jne 0x4f7eca
004f7eb2 push 0
004f7eb4 push 0xb41e78
004f7eb9 mov dword ptr [edi + 0xb84], 0x3f0c3c9f
004f7ec3 call 0x405a00
004f7ec8 jmp 0x4f7f0c
004f7eca call 0x405d10
004f7ecf test eax, eax
004f7ed1 jle 0x4f7f0c
004f7ed3 mov dword ptr [edi + 0xb84], 0x3f3851ec
004f7edd jmp 0x4f7f0c
004f7edf mov dword ptr [edi + 0xb84], 0x3efef9db
004f7ee9 jmp 0x4f7f0c
004f7eeb mov dword ptr [edi + 0xb84], 0x3e99999a
004f7ef5 cmp eax, 0xd0
004f7efa jne 0x4f7f0c
004f7efc cmp dword ptr [edi + 0x2c], 2
004f7f00 jne 0x4f7f0c
004f7f02 mov dword ptr [edi + 0xb84], 0x3ea8f5c3
004f7f0c mov eax, dword ptr [edi + 0x160]
004f7f12 and eax, 0x1000800
004f7f17 or eax, 0
004f7f1a je 0x4f7f93
004f7f1c mov ecx, edi
004f7f1e call 0x695680
004f7f23 push 0
004f7f25 lea ecx, [edi + 0x364]
004f7f2b mov edx, dword ptr [eax + 0x294]
004f7f31 mov eax, dword ptr [eax + 0x298]
004f7f37 mov dword ptr [ebp - 0x1b8], eax
004f7f3d lea eax, [ebp - 0x1bc]
004f7f43 push eax
004f7f44 mov dword ptr [ebp - 0x1bc], edx
004f7f4a call 0x7a4830
004f7f4f movss xmm0, dword ptr [edi + 0x2c4]
004f7f57 movss xmm1, dword ptr [0xb6a560]
004f7f5f mov eax, dword ptr [edi + 0x28]
004f7f62 mulss xmm0, xmm1
004f7f66 movss dword ptr [edi + 0x2c4], xmm0
004f7f6e cmp eax, 0xd0
004f7f73 je 0x4f7f7c
004f7f75 cmp eax, 0x101
004f7f7a jne 0x4f7fdc
004f7f7c cmp dword ptr [edi + 0xaa0], 0
004f7f83 jle 0x4f7fdc
004f7f85 mulss xmm0, xmm1
004f7f89 movss dword ptr [edi + 0x2c4], xmm0
004f7f91 jmp 0x4f7fdc
004f7f93 cmp dword ptr [edi + 0x28], 0x12e
004f7f9a mov ecx, 0x64
004f7f9f movss xmm0, dword ptr [edi + 0xb84]
004f7fa7 mov eax, 0x384
004f7fac cmove eax, ecx
004f7faf mov ecx, edi
004f7fb1 push 1
004f7fb3 push eax
004f7fb4 sub esp, 8
004f7fb7 lea eax, [ebp - 0x1bc]
004f7fbd movss dword ptr [esp + 4], xmm0
004f7fc3 mov dword ptr [esp], 0
004f7fca push eax
004f7fcb call 0x695a30
004f7fd0 push eax
004f7fd1 lea ecx, [edi + 0x364]
004f7fd7 call 0x7a3650
004f7fdc cmp dword ptr [edi + 0xe6c], -1
004f7fe3 mov ecx, edi
004f7fe5 je 0x4f7ffb
004f7fe7 push 0xa
004f7fe9 call 0x6af080
004f7fee movzx eax, al
004f7ff1 test eax, eax
004f7ff3 je 0x4f80ed
004f7ff9 jmp 0x4f8033
004f7ffb call 0x695680
004f8000 push eax
004f8001 mov ecx, edi
004f8003 call 0x6aeb40
004f8008 test al, al
004f800a je 0x4f80ed
004f8010 cmp byte ptr [edi + 0xa90], 0
004f8017 je 0x4f80ed
004f801d call 0x6c3d90
004f8022 xor edx, edx
004f8024 mov ecx, 3
004f8029 div ecx
004f802b test edx, edx
004f802d jne 0x4f80ed
004f8033 mov eax, dword ptr [edi + 0x28]
004f8036 cmp eax, 0xd0
004f803b je 0x4f80d0
004f8041 cmp eax, 0x101
004f8046 je 0x4f80d0
004f804c cmp eax, 0x12e
004f8051 jne 0x4f80b5
004f8053 cmp dword ptr [edi + 0xab4], 0x10
004f805a je 0x4f80ed
004f8060 cmp dword ptr [edi + 0x2c], 0xa
004f8064 je 0x4f80ed
004f806a call 0x6c3d90
004f806f push ecx
004f8070 movd xmm0, eax
004f8074 cvtdq2pd xmm0, xmm0
004f8078 shr eax, 0x1f
004f807b addsd xmm0, qword ptr [eax*8 + 0xb6c940]
004f8084 cvtpd2ps xmm0, xmm0
004f8088 mulss xmm0, dword ptr [0xb6a19c]
004f8090 mulss xmm0, dword ptr [0xb6a2cc]
004f8098 addss xmm0, dword ptr [0xb6a5a4]
004f80a0 movss dword ptr [esp], xmm0
004f80a5 push 0
004f80a7 push 0x3c
004f80a9 push ecx
004f80aa mov dword ptr [esp], 0x3f800000
004f80b1 push 0x32
004f80b3 jmp 0x4f80e6
004f80b5 push ecx
004f80b6 mov dword ptr [esp], 0x3f800000
004f80bd push 0
004f80bf push 0x28
004f80c1 push ecx
004f80c2 mov dword ptr [esp], 0x3f800000
004f80c9 push 0xa5
004f80ce jmp 0x4f80e6
004f80d0 push ecx
004f80d1 mov dword ptr [esp], 0x3f800000
004f80d8 push 0
004f80da push 0x3c
004f80dc push ecx
004f80dd mov dword ptr [esp], 0x3f800000
004f80e4 push 0x74
004f80e6 mov ecx, edi
004f80e8 call 0x6ad720
004f80ed cmp dword ptr [edi + 0x2c], 0
004f80f1 jne 0x4f812f
004f80f3 cmp byte ptr [edi + 0xa90], 0
004f80fa je 0x4f812f
004f80fc mov eax, dword ptr [edi + 0x28]
004f80ff cmp eax, 0xd0
004f8104 je 0x4f812f
004f8106 cmp eax, 0x101
004f810b je 0x4f812f
004f810d cmp eax, 0x12e
004f8112 je 0x4f812f
004f8114 lea ecx, [edi + 0x3c]
004f8117 call 0x405d10
004f811c test eax, eax
004f811e jg 0x4f812f
004f8120 push 1
004f8122 push 0xb41e78
004f8127 lea ecx, [edi + 0x3c]
004f812a call 0x405a00
004f812f cmp dword ptr [edi + 0x28], 0x11c
004f8136 jne 0x4f8309
004f813c mov eax, dword ptr [edi + 0x20]
004f813f xor edx, edx
004f8141 mov ecx, 7
004f8146 movss xmm1, dword ptr [0xb6a928]
004f814e div ecx
004f8150 mov ecx, edi
004f8152 movd xmm0, edx
004f8156 cvtdq2pd xmm0, xmm0
004f815a shr edx, 0x1f
004f815d addsd xmm0, qword ptr [edx*8 + 0xb6c940]
004f8166 cvtpd2ps xmm2, xmm0
004f816a call 0x6847e0
004f816f test eax, eax
004f8171 je 0x4f8217
004f8177 call 0x6c3d90
004f817c mov ecx, dword ptr [0xbfd65c]
004f8182 push 0
004f8184 push 0xbeaaec
004f8189 push 0xbeab18
004f818e push 0
004f8190 push eax
004f8191 push 0
004f8193 push edi
004f8194 push 0xc02fec
004f8199 lea eax, [edi + 0x294]
004f819f push eax
004f81a0 push 0x16
004f81a2 push 0x3e8
004f81a7 call 0x422e20
004f81ac push eax
004f81ad call 0x9ec34c
004f81b2 add esp, 0x14
004f81b5 mov esi, eax
004f81b7 call 0x6c3d90
004f81bc mov ecx, esi
004f81be mov dword ptr [esi + 0x3ac], 0x14
004f81c8 mov dword ptr [esi + 0x3b0], 0x14
004f81d2 movd xmm0, eax
004f81d6 cvtdq2pd xmm0, xmm0
004f81da shr eax, 0x1f
004f81dd addsd xmm0, qword ptr [eax*8 + 0xb6c940]
004f81e6 mov eax, dword ptr [esi]
004f81e8 cvtpd2ps xmm0, xmm0
004f81ec mulss xmm0, dword ptr [0xb6a19c]
004f81f4 mulss xmm0, dword ptr [0xb6a3b0]
004f81fc addss xmm0, dword ptr [0xb6a350]
004f8204 movss dword ptr [esi + 0xd8], xmm0
004f820c movss dword ptr [esi + 0xdc], xmm0
004f8214 call dword ptr [eax + 0xc]
004f8217 cmp dword ptr [edi + 0xab4], 4
004f821e jne 0x4f82e5
004f8224 cmp dword ptr [edi + 0xaf0], 0
004f822b jg 0x4f82e5
004f8231 cmp dword ptr [edi + 0xe6c], -1
004f8238 je 0x4f8267
004f823a push 1
004f823c mov ecx, edi
004f823e call 0x6afe20
004f8243 push 0xc02fec
004f8248 lea ecx, [edi + 0xe70]
004f824e call 0x962ca0
004f8253 test al, al
004f8255 je 0x4f82e5
004f825b mov dword ptr [edi + 0xaf0], 0x2d
004f8265 jmp 0x4f82cc
004f8267 cmp byte ptr [edi + 0xa90], 0
004f826e je 0x4f82e5
004f8270 call 0x6c3d90
004f8275 xor edx, edx
004f8277 mov ecx, 0x1e
004f827c div ecx
004f827e test edx, edx
004f8280 jne 0x4f82e5
004f8282 mov ecx, edi
004f8284 call 0x695680
004f8289 movss xmm0, dword ptr [eax + 0x294]
004f8291 movss xmm1, dword ptr [eax + 0x298]
004f8299 subss xmm0, dword ptr [edi + 0x294]
004f82a1 subss xmm1, dword ptr [edi + 0x298]
004f82a9 mulss xmm0, xmm0
004f82ad mulss xmm1, xmm1
004f82b1 addss xmm1, xmm0
004f82b5 movss xmm0, dword ptr [0xb6ad60]
004f82bd comiss xmm0, xmm1
004f82c0 jbe 0x4f82e5
004f82c2 mov dword ptr [edi + 0xaf0], 0x3c
004f82cc push 0
004f82ce push 0xb40510
004f82d3 lea ecx, [edi + 0x3c]
004f82d6 mov dword ptr [edi + 0xab4], 8
004f82e0 call 0x405a00
004f82e5 mov edx, dword ptr [edi + 0xaf0]
004f82eb test edx, edx
004f82ed jle 0x4f8309
004f82ef cvttss2si eax, dword ptr [edi + 0x2fc]
004f82f7 cvttss2si ecx, dword ptr [edi + 0x2f8]
004f82ff sub ecx, eax
004f8301 add ecx, edx
004f8303 mov dword ptr [edi + 0xaf0], ecx
004f8309 cmp dword ptr [edi + 0x28], 0x12e
004f8310 jne 0x4f864a
004f8316 mov ecx, edi
004f8318 call 0x6ad7a0
004f831d test eax, eax
004f831f jg 0x4f83d7
004f8325 mov eax, dword ptr [0xbfd65c]
004f832a mov eax, dword ptr [eax + 0x18190]
004f8330 cmp byte ptr [eax + 0x711d], 0
004f8337 je 0x4f8346
004f8339 cmp dword ptr [eax + 0x11ec], 8
004f8340 jg 0x4f83d7
004f8346 mov eax, dword ptr [edi + 0xab4]
004f834c cmp eax, 0x12
004f834f je 0x4f83dd
004f8355 cmp dword ptr [edi + 0x2c], 0xa
004f8359 mov dword ptr [edi + 0xab4], 0x12
004f8363 mov dword ptr [edi + 0x360], 0
004f836d mov dword ptr [edi + 0x180], 0
004f8377 jne 0x4f864a
004f837d push 0
004f837f lea ecx, [edi + 0x8c]
004f8385 call 0x403740
004f838a push 1
004f838c lea ecx, [edi + 0x3c]
004f838f call 0x4062c0
004f8394 movss xmm0, dword ptr [0xc02fec]
004f839c lea ecx, [edi + 0x3c]
004f839f push 1
004f83a1 movss dword ptr [eax + 0x40], xmm0
004f83a6 movss xmm0, dword ptr [0xc02ff0]
004f83ae movss dword ptr [eax + 0x44], xmm0
004f83b3 call 0x4062c0
004f83b8 movss xmm0, dword ptr [0xbc7a28]
004f83c0 movss dword ptr [eax + 0x34], xmm0
004f83c5 movss xmm0, dword ptr [0xbc7a2c]
004f83cd movss dword ptr [eax + 0x38], xmm0
004f83d2 jmp 0x4f85de
004f83d7 mov eax, dword ptr [edi + 0xab4]
004f83dd cmp eax, 4
004f83e0 jne 0x4f8564
004f83e6 cmp dword ptr [edi + 0x2c], 0xa
004f83ea jne 0x4f8509
004f83f0 cmp dword ptr [edi + 0xb14], 1
004f83f7 mov ecx, 0xb42e5c
004f83fc mov eax, 0xb42e4c
004f8401 cmovne eax, ecx
004f8404 lea ecx, [edi + 0x3c]
004f8407 push 0
004f8409 push eax
004f840a call 0x405a00
004f840f push 0xb400ac
004f8414 lea ecx, [edi + 0x8c]
004f841a call 0x405e90
004f841f test al, al
004f8421 je 0x4f84de
004f8427 push ecx
004f8428 mov dword ptr [esp], 0x3f800000
004f842f push 0
004f8431 push 0
004f8433 push ecx
004f8434 mov dword ptr [esp], 0x3f800000
004f843b mov ecx, edi
004f843d push 0x106
004f8442 call 0x6ad720
004f8447 lea ecx, [ebp - 0x1a8]
004f844d call 0x430d70
004f8452 movss xmm0, dword ptr [edi + 0x2b8]
004f845a lea eax, [ebp - 0x1a8]
004f8460 movss xmm1, dword ptr [edi + 0x2bc]
004f8468 addss xmm0, xmm0
004f846c push eax
004f846d xor eax, eax
004f846f mov dword ptr [ebp - 0x1a4], 0xc1700000
004f8479 cmp dword ptr [edi + 0xb14], 1
004f8480 addss xmm1, xmm1
004f8484 mov ecx, edi
004f8486 mov dword ptr [ebp - 0x19c], 0x3e99999a
004f8490 addss xmm0, dword ptr [edi + 0x294]
004f8498 setne al
004f849b mov dword ptr [ebp - 0x1dc], 0x41200000
004f84a5 add eax, 6
004f84a8 mov dword ptr [ebp - 0x1d8], 0
004f84b2 addss xmm1, dword ptr [edi + 0x298]
004f84ba push eax
004f84bb lea eax, [ebp - 0x1dc]
004f84c1 movss dword ptr [ebp - 0x1c4], xmm0
004f84c9 push eax
004f84ca lea eax, [ebp - 0x1c4]
004f84d0 push eax
004f84d1 movss dword ptr [ebp - 0x1c0], xmm1
004f84d9 call 0x6a1a20
004f84de push 0xa081d4
004f84e3 lea ecx, [edi + 0x3c]
004f84e6 call 0x405b30
004f84eb test al, al
004f84ed je 0x4f85de
004f84f3 mov eax, 1
004f84f8 sub eax, dword ptr [edi + 0xb14]
004f84fe mov dword ptr [edi + 0xb14], eax
004f8504 jmp 0x4f85de
004f8509 mov edx, dword ptr [edi + 0xb10]
004f850f test edx, edx
004f8511 jle 0x4f8535
004f8513 cvttss2si eax, dword ptr [edi + 0x2fc]
004f851b cvttss2si ecx, dword ptr [edi + 0x2f8]
004f8523 sub ecx, eax
004f8525 add edx, ecx
004f8527 mov dword ptr [edi + 0xb10], edx
004f852d test edx, edx
004f852f jg 0x4f85de
004f8535 push 0
004f8537 push 0xb408c8
004f853c lea ecx, [edi + 0x3c]
004f853f mov dword ptr [edi + 0xab4], 0x10
004f8549 call 0x4054f0
004f854e call 0x6c3d90
004f8553 and eax, 3
004f8556 add eax, 2
004f8559 imul eax, eax, 0x15
004f855c mov dword ptr [edi + 0xb10], eax
004f8562 jmp 0x4f85de
004f8564 cmp eax, 0x10
004f8567 jne 0x4f85de
004f8569 movss xmm0, dword ptr [edi + 0x2b8]
004f8571 xorps xmm1, xmm1
004f8574 mulss xmm0, xmm1
004f8578 movss dword ptr [edi + 0x2b8], xmm0
004f8580 movss xmm0, dword ptr [edi + 0x2bc]
004f8588 mulss xmm0, xmm1
004f858c movss dword ptr [edi + 0x2bc], xmm0
004f8594 mov edx, dword ptr [edi + 0xb10]
004f859a test edx, edx
004f859c jle 0x4f85b8
004f859e cvttss2si eax, dword ptr [edi + 0x2fc]
004f85a6 cvttss2si ecx, dword ptr [edi + 0x2f8]
004f85ae sub ecx, eax
004f85b0 add edx, ecx
004f85b2 mov dword ptr [edi + 0xb10], edx
004f85b8 cmp edx, 1
004f85bb jge 0x4f85de
004f85bd mov dword ptr [edi + 0xab4], 4
004f85c7 call 0x6c3d90
004f85cc xor edx, edx
004f85ce mov ecx, 0x3c
004f85d3 div ecx
004f85d5 add edx, 0x5a
004f85d8 mov dword ptr [edi + 0xb10], edx
004f85de cmp dword ptr [edi + 0x2c], 0xa
004f85e2 jne 0x4f864a
004f85e4 cmp dword ptr [edi + 0xab4], 0x12
004f85eb je 0x4f864a
004f85ed add edi, 0x3c
004f85f0 push 2
004f85f2 mov ecx, edi
004f85f4 call 0x406260
004f85f9 mov esi, eax
004f85fb test esi, esi
004f85fd je 0x4f863d
004f85ff cmp byte ptr [esi + 0xc], 0
004f8603 je 0x4f863d
004f8605 push 1
004f8607 mov ecx, edi
004f8609 call 0x4062c0
004f860e push 1
004f8610 mov ecx, edi
004f8612 mov byte ptr [eax + 0x74], 1
004f8616 call 0x4062c0
004f861b mov edx, dword ptr [esi]
004f861d mov ecx, edi
004f861f push 1
004f8621 mov dword ptr [eax + 0x40], edx
004f8624 mov edx, dword ptr [esi + 4]
004f8627 mov dword ptr [eax + 0x44], edx
004f862a call 0x4062c0
004f862f mov ecx, dword ptr [esi + 0x10]
004f8632 mov dword ptr [eax + 0x34], ecx
004f8635 mov ecx, dword ptr [esi + 0x14]
004f8638 mov dword ptr [eax + 0x38], ecx
004f863b jmp 0x4f864a
004f863d push 1
004f863f mov ecx, edi
004f8641 call 0x4062c0
004f8646 mov byte ptr [eax + 0x74], 0
004f864a mov ecx, dword ptr [ebp - 0xc]
004f864d mov dword ptr fs:[0], ecx
004f8654 pop ecx
004f8655 pop edi
004f8656 pop esi
004f8657 mov ecx, dword ptr [ebp - 0x14]
004f865a xor ecx, ebp
004f865c call 0x9eacd7
004f8661 mov esp, ebp
004f8663 pop ebp
004f8664 mov esp, ebx
004f8666 pop ebx
004f8667 ret 
