004c70e0 push ebx
004c70e1 mov ebx, esp
004c70e3 sub esp, 8
004c70e6 and esp, 0xfffffff8
004c70e9 add esp, 4
004c70ec push ebp
004c70ed mov ebp, dword ptr [ebx + 4]
004c70f0 mov dword ptr [esp + 4], ebp
004c70f4 mov ebp, esp
004c70f6 push -1
004c70f8 push 0x9eeacd
004c70fd mov eax, dword ptr fs:[0]
004c7103 push eax
004c7104 push ebx
004c7105 sub esp, 0x110
004c710b mov eax, dword ptr [0xbaa3b4]
004c7110 xor eax, ebp
004c7112 mov dword ptr [ebp - 0x14], eax
004c7115 push esi
004c7116 push edi
004c7117 push eax
004c7118 lea eax, [ebp - 0xc]
004c711b mov dword ptr fs:[0], eax
004c7121 mov edi, ecx
004c7123 movaps xmm0, xmmword ptr [0xb6bcd0]
004c712a mov eax, dword ptr [edi + 0xab4]
004c7130 mov dword ptr [ebp - 0x1c], 0x3f666666
004c7137 mov dword ptr [ebp - 0x18], 0x3ff33333
004c713e movups xmmword ptr [ebp - 0x2c], xmm0
004c7142 test eax, eax
004c7144 je 0x4c7a75
004c714a cmp eax, 4
004c714d je 0x4c7158
004c714f cmp eax, 8
004c7152 jne 0x4c7b8a
004c7158 mov eax, dword ptr [0xb404ec]
004c715d mov ecx, dword ptr [0xb404f0]
004c7163 mov dword ptr [ebp - 0x30], 0xf
004c716a mov dword ptr [ebp - 0x34], 8
004c7171 mov dword ptr [ebp - 0x44], eax
004c7174 mov dword ptr [ebp - 0x40], ecx
004c7177 mov byte ptr [ebp - 0x3c], 0
004c717b mov dword ptr [ebp - 4], 0
004c7182 mov eax, dword ptr [0xb40504]
004c7187 mov ecx, dword ptr [0xb40508]
004c718d mov dword ptr [ebp - 0x4c], 0xf
004c7194 mov dword ptr [ebp - 0x50], 8
004c719b mov dword ptr [ebp - 0x60], eax
004c719e mov dword ptr [ebp - 0x5c], ecx
004c71a1 mov byte ptr [ebp - 0x58], 0
004c71a5 push ecx
004c71a6 mov byte ptr [ebp - 4], 1
004c71aa lea eax, [ebp - 0x44]
004c71ad mov dword ptr [esp], 0x3dcccccd
004c71b4 mov ecx, edi
004c71b6 push eax
004c71b7 lea eax, [ebp - 0x60]
004c71ba push eax
004c71bb call 0x6980a0
004c71c0 mov byte ptr [ebp - 4], 0
004c71c4 mov edx, dword ptr [ebp - 0x4c]
004c71c7 cmp edx, 0x10
004c71ca jb 0x4c71f4
004c71cc mov ecx, dword ptr [ebp - 0x60]
004c71cf inc edx
004c71d0 mov eax, ecx
004c71d2 cmp edx, 0x1000
004c71d8 jb 0x4c71ea
004c71da mov ecx, dword ptr [ecx - 4]
004c71dd add edx, 0x23
004c71e0 sub eax, ecx
004c71e2 add eax, -4
004c71e5 cmp eax, 0x1f
004c71e8 ja 0x4c7233
004c71ea push edx
004c71eb push ecx
004c71ec call 0x9eb08e
004c71f1 add esp, 8
004c71f4 mov dword ptr [ebp - 4], 0xffffffff
004c71fb mov edx, dword ptr [ebp - 0x30]
004c71fe mov dword ptr [ebp - 0x50], 0
004c7205 mov dword ptr [ebp - 0x4c], 0xf
004c720c mov byte ptr [ebp - 0x60], 0
004c7210 cmp edx, 0x10
004c7213 jb 0x4c7243
004c7215 mov ecx, dword ptr [ebp - 0x44]
004c7218 inc edx
004c7219 mov eax, ecx
004c721b cmp edx, 0x1000
004c7221 jb 0x4c7239
004c7223 mov ecx, dword ptr [ecx - 4]
004c7226 add edx, 0x23
004c7229 sub eax, ecx
004c722b add eax, -4
004c722e cmp eax, 0x1f
004c7231 jbe 0x4c7239
004c7233 call dword ptr [0xa065ac]
004c7239 push edx
004c723a push ecx
004c723b call 0x9eb08e
004c7240 add esp, 8
004c7243 cmp dword ptr [edi + 0x90], 0
004c724a je 0x4c7255
004c724c cmp byte ptr [edi + 0xa0], 0
004c7253 jne 0x4c727f
004c7255 push 1
004c7257 push 0xb41e78
004c725c lea ecx, [edi + 0x3c]
004c725f call 0x405bb0
004c7264 test al, al
004c7266 je 0x4c727f
004c7268 cmp dword ptr [edi + 0x90], 0
004c726f je 0x4c727f
004c7271 lea ecx, [edi + 0x8c]
004c7277 xorps xmm1, xmm1
004c727a call 0x403c00
004c727f cmp dword ptr [edi + 0x70], 0
004c7283 je 0x4c72ae
004c7285 cmp byte ptr [edi + 0x80], 0
004c728c je 0x4c72ae
004c728e cmp dword ptr [edi + 0x90], 0
004c7295 cvttss2si eax, dword ptr [edi + 0x7c]
004c729a je 0x4c72ae
004c729c movd xmm1, eax
004c72a0 lea ecx, [edi + 0x8c]
004c72a6 cvtdq2ps xmm1, xmm1
004c72a9 call 0x403c00
004c72ae cmp dword ptr [edi + 0x28], 0x390
004c72b5 mov dword ptr [edi + 0xb84], 0x3f19999a
004c72bf jne 0x4c7351
004c72c5 movss xmm0, dword ptr [edi + 0x2c4]
004c72cd xorps xmm2, xmm2
004c72d0 mulss xmm0, dword ptr [0xb6a53c]
004c72d8 movss xmm1, dword ptr [edi + 0x2f4]
004c72e0 movss dword ptr [edi + 0x2c4], xmm0
004c72e8 movaps xmm0, xmm1
004c72eb mulss xmm1, dword ptr [0xb6ae44]
004c72f3 mulss xmm0, xmm2
004c72f7 addss xmm1, dword ptr [edi + 0x2bc]
004c72ff addss xmm0, dword ptr [edi + 0x2b8]
004c7307 movss dword ptr [edi + 0x2bc], xmm1
004c730f movss dword ptr [edi + 0x2b8], xmm0
004c7317 call 0x6c3d90
004c731c xor edx, edx
004c731e mov ecx, 0xa
004c7323 div ecx
004c7325 test edx, edx
004c7327 jne 0x4c7b8a
004c732d push ecx
004c732e mov dword ptr [esp], 0x3f800000
004c7335 push edx
004c7336 push 0x28
004c7338 push ecx
004c7339 mov dword ptr [esp], 0x3f800000
004c7340 mov ecx, edi
004c7342 push 0xa5
004c7347 call 0x6ad720
004c734c jmp 0x4c7b8a
004c7351 push ecx
004c7352 lea eax, [ebp - 0x118]
004c7358 mov dword ptr [esp], 0
004c735f push eax
004c7360 mov ecx, edi
004c7362 call 0x695a30
004c7367 mov eax, dword ptr [edi + 0x30]
004c736a cmp eax, 5
004c736d ja 0x4c7385
004c736f movss xmm0, dword ptr [ebp + eax*4 - 0x2c]
004c7375 mulss xmm0, dword ptr [edi + 0xb84]
004c737d movss dword ptr [edi + 0xb84], xmm0
004c7385 movss xmm2, dword ptr [0xb6aa8c]
004c738d cmp eax, 3
004c7390 jne 0x4c7654
004c7396 mov edx, dword ptr [edi + 0xb10]
004c739c test edx, edx
004c739e jle 0x4c73ba
004c73a0 cvttss2si eax, dword ptr [edi + 0x2fc]
004c73a8 cvttss2si ecx, dword ptr [edi + 0x2f8]
004c73b0 sub ecx, eax
004c73b2 add edx, ecx
004c73b4 mov dword ptr [edi + 0xb10], edx
004c73ba lea esi, [edi + 0xb3c]
004c73c0 test edx, edx
004c73c2 jg 0x4c73ec
004c73c4 mov ecx, dword ptr [esi]
004c73c6 test ecx, ecx
004c73c8 je 0x4c73e4
004c73ca lea eax, [ebp - 0x30]
004c73cd mov dword ptr [ebp - 0x30], esi
004c73d0 push eax
004c73d1 add ecx, 0x324
004c73d7 call 0x4bc3c0
004c73dc movss xmm2, dword ptr [0xb6aa8c]
004c73e4 mov dword ptr [esi], 0
004c73ea jmp 0x4c73f5
004c73ec cmp dword ptr [esi], 0
004c73ef jne 0x4c7552
004c73f5 movss xmm1, dword ptr [edi + 0x294]
004c73fd lea eax, [edi + 0x294]
004c7403 movss xmm0, dword ptr [eax + 4]
004c7408 subss xmm0, dword ptr [ebp - 0x114]
004c7410 subss xmm1, dword ptr [ebp - 0x118]
004c7418 mulss xmm0, xmm0
004c741c mulss xmm1, xmm1
004c7420 addss xmm0, xmm1
004c7424 comiss xmm0, dword ptr [0xb6ad28]
004c742b jbe 0x4c7552
004c7431 push 8
004c7433 push eax
004c7434 lea eax, [ebp - 0x24]
004c7437 movaps xmm3, xmm2
004c743a push eax
004c743b mov eax, dword ptr [0xbfd65c]
004c7440 mov ecx, dword ptr [eax + 0x18190]
004c7446 add ecx, 0x1218
004c744c call 0x4157f0
004c7451 xor edx, edx
004c7453 mov dword ptr [ebp - 4], 2
004c745a cmp dword ptr [ebp - 0x18], edx
004c745d jbe 0x4c753a
004c7463 mov eax, dword ptr [ebp - 0x20]
004c7466 mov esi, dword ptr [eax + edx*4]
004c7469 test esi, esi
004c746b je 0x4c74e5
004c746d mov ecx, dword ptr [esi + 0x28]
004c7470 lea eax, [ecx - 0xa]
004c7473 cmp eax, 0x3dd
004c7478 ja 0x4c74e2
004c747a cmp esi, edi
004c747c je 0x4c74e2
004c747e cmp ecx, dword ptr [edi + 0x28]
004c7481 jne 0x4c74e2
004c7483 mov eax, dword ptr [esi + 0x2c]
004c7486 cmp eax, dword ptr [edi + 0x2c]
004c7489 jne 0x4c74e2
004c748b mov eax, dword ptr [esi + 0x30]
004c748e cmp eax, dword ptr [edi + 0x30]
004c7491 je 0x4c74e2
004c7493 mov eax, dword ptr [esi + 0x164]
004c7499 mov ecx, dword ptr [esi + 0x160]
004c749f mov dword ptr [ebp - 0x4c], eax
004c74a2 mov eax, ecx
004c74a4 and eax, 0x20000000
004c74a9 mov byte ptr [ebp - 0x10d], 1
004c74b0 or eax, 0
004c74b3 jne 0x4c74bc
004c74b5 mov byte ptr [ebp - 0x10d], 0
004c74bc mov eax, dword ptr [edi + 0x160]
004c74c2 and eax, 0x20000000
004c74c7 or eax, 0
004c74ca je 0x4c74d0
004c74cc mov al, 1
004c74ce jmp 0x4c74d2
004c74d0 xor al, al
004c74d2 cmp byte ptr [ebp - 0x10d], al
004c74d8 jne 0x4c74e2
004c74da and ecx, 0x10
004c74dd or ecx, 0
004c74e0 je 0x4c74f1
004c74e2 mov eax, dword ptr [ebp - 0x20]
004c74e5 inc edx
004c74e6 cmp edx, dword ptr [ebp - 0x18]
004c74e9 jb 0x4c7466
004c74ef jmp 0x4c753a
004c74f1 mov ecx, dword ptr [edi + 0xb3c]
004c74f7 lea eax, [edi + 0xb3c]
004c74fd test ecx, ecx
004c74ff je 0x4c7519
004c7501 mov dword ptr [ebp - 0x30], eax
004c7504 add ecx, 0x324
004c750a lea eax, [ebp - 0x30]
004c750d push eax
004c750e call 0x4bc3c0
004c7513 lea eax, [edi + 0xb3c]
004c7519 push eax
004c751a mov ecx, esi
004c751c mov dword ptr [eax], esi
004c751e call 0x4bae70
004c7523 call 0x6c3d90
004c7528 xor edx, edx
004c752a mov ecx, 0xf
004c752f div ecx
004c7531 add edx, 0x1e
004c7534 mov dword ptr [edi + 0xb10], edx
004c753a mov dword ptr [ebp - 4], 0xffffffff
004c7541 cmp byte ptr [ebp - 0x24], 0
004c7545 jne 0x4c7552
004c7547 push dword ptr [ebp - 0x20]
004c754a call 0x9eace5
004c754f add esp, 4
004c7552 cvttss2si ecx, dword ptr [edi + 0x2fc]
004c755a cvttss2si eax, dword ptr [edi + 0x2f8]
004c7562 sub ecx, eax
004c7564 add dword ptr [edi + 0xb14], ecx
004c756a cmp dword ptr [edi + 0xb14], 0x3c
004c7571 jle 0x4c75fd
004c7577 call 0x6c3d90
004c757c test al, 7
004c757e jne 0x4c75fd
004c7580 push dword ptr [edi + 0x20]
004c7583 lea eax, [ebp - 0x3c]
004c7586 mov dword ptr [edi + 0xb14], 0
004c7590 push eax
004c7591 mov ecx, edi
004c7593 call 0x6a6f60
004c7598 cmp byte ptr [ebp - 0x3c], 0
004c759c mov esi, dword ptr [eax + 0xc]
004c759f jne 0x4c75ac
004c75a1 push dword ptr [ebp - 0x38]
004c75a4 call 0x9eace5
004c75a9 add esp, 4
004c75ac cmp esi, 6
004c75af jae 0x4c75fd
004c75b1 call 0x6c3d90
004c75b6 mov ecx, dword ptr [0xbfd65c]
004c75bc push eax
004c75bd push 0
004c75bf push edi
004c75c0 push 0xc02fec
004c75c5 lea eax, [edi + 0x294]
004c75cb push eax
004c75cc push 0
004c75ce push 0x355
004c75d3 call 0x422e20
004c75d8 mov esi, eax
004c75da mov ecx, dword ptr [esi + 0x164]
004c75e0 mov edx, dword ptr [esi]
004c75e2 and dword ptr [esi + 0x160], 0xfffffffb
004c75e9 mov dword ptr [esi + 0x164], ecx
004c75ef mov ecx, esi
004c75f1 call dword ptr [edx + 0xc]
004c75f4 mov ecx, dword ptr [edi + 0x20]
004c75f7 mov dword ptr [esi + 0xbcc], ecx
004c75fd call 0x6c3d90
004c7602 xor edx, edx
004c7604 mov ecx, 0x14
004c7609 div ecx
004c760b test edx, edx
004c760d jne 0x4c7654
004c760f movss xmm1, dword ptr [0xb6a8cc]
004c7617 xorps xmm2, xmm2
004c761a mov ecx, edi
004c761c call 0x6847e0
004c7621 test eax, eax
004c7623 je 0x4c7654
004c7625 call 0x6c3d90
004c762a mov ecx, dword ptr [0xbfd65c]
004c7630 push eax
004c7631 push 0
004c7633 push 0
004c7635 push 0xc02fec
004c763a lea eax, [edi + 0x294]
004c7640 push eax
004c7641 push 0x3f
004c7643 push 0x3e8
004c7648 call 0x422e20
004c764d mov ecx, eax
004c764f mov edx, dword ptr [eax]
004c7651 call dword ptr [edx + 0xc]
004c7654 mov eax, dword ptr [edi + 0x160]
004c765a and eax, 0x1000800
004c765f or eax, 0
004c7662 je 0x4c767f
004c7664 mov ecx, edi
004c7666 call 0x695680
004c766b mov ecx, dword ptr [eax + 0x294]
004c7671 mov eax, dword ptr [eax + 0x298]
004c7677 mov dword ptr [ebp - 0x34], ecx
004c767a mov dword ptr [ebp - 0x30], eax
004c767d jmp 0x4c769b
004c767f mov ecx, dword ptr [edi + 0xb3c]
004c7685 test ecx, ecx
004c7687 je 0x4c76c9
004c7689 mov eax, dword ptr [ecx + 0x294]
004c768f mov ecx, dword ptr [ecx + 0x298]
004c7695 mov dword ptr [ebp - 0x34], eax
004c7698 mov dword ptr [ebp - 0x30], ecx
004c769b push 0
004c769d lea eax, [ebp - 0x34]
004c76a0 push eax
004c76a1 lea ecx, [edi + 0x364]
004c76a7 call 0x7a4830
004c76ac movss xmm0, dword ptr [edi + 0x2c4]
004c76b4 mulss xmm0, dword ptr [0xb6a560]
004c76bc movss dword ptr [edi + 0x2c4], xmm0
004c76c4 jmp 0x4c79eb
004c76c9 mov ecx, dword ptr [edi + 0x30]
004c76cc cmp ecx, 5
004c76cf jne 0x4c79ba
004c76d5 movss xmm1, dword ptr [ebp - 0x118]
004c76dd lea esi, [edi + 0x294]
004c76e3 movss xmm0, dword ptr [ebp - 0x114]
004c76eb subss xmm0, dword ptr [esi + 4]
004c76f0 subss xmm1, dword ptr [esi]
004c76f4 mulss xmm0, xmm0
004c76f8 mulss xmm1, xmm1
004c76fc addss xmm0, xmm1
004c7700 call 0x4228c0
004c7705 subss xmm0, dword ptr [0xb6aad4]
004c770d movss xmm1, dword ptr [0xb6a614]
004c7715 lea eax, [ebp - 0x30]
004c7718 xorps xmm2, xmm2
004c771b mov dword ptr [ebp - 0x30], 0
004c7722 lea ecx, [ebp - 0x18]
004c7725 divss xmm0, dword ptr [0xb6aafc]
004c772d comiss xmm2, xmm0
004c7730 movss dword ptr [ebp - 0x18], xmm0
004c7735 cmovbe eax, ecx
004c7738 movss xmm0, dword ptr [eax]
004c773c comiss xmm0, xmm1
004c773f ja 0x4c7747
004c7741 movss xmm0, xmm0
004c7745 jmp 0x4c774b
004c7747 movss xmm0, xmm1
004c774b lea eax, [ebp - 0x118]
004c7751 mov ecx, dword ptr [0xbfd65c]
004c7757 push 0
004c7759 push 0
004c775b push 0
004c775d push 0
004c775f push 0
004c7761 mulss xmm0, dword ptr [0xb6a38c]
004c7769 push eax
004c776a push esi
004c776b addss xmm0, dword ptr [0xb6a53c]
004c7773 mulss xmm0, dword ptr [edi + 0xb84]
004c777b movss dword ptr [edi + 0xb84], xmm0
004c7783 mov ecx, dword ptr [ecx + 0x18190]
004c7789 call 0x7af4b0
004c778e test al, al
004c7790 je 0x4c79b4
004c7796 movss xmm0, dword ptr [esi]
004c779a subss xmm0, dword ptr [ebp - 0x118]
004c77a2 movss dword ptr [ebp - 0x10c], xmm0
004c77aa movss xmm0, dword ptr [esi + 4]
004c77af subss xmm0, dword ptr [ebp - 0x114]
004c77b7 movss dword ptr [ebp - 0x11c], xmm0
004c77bf call 0x6c3d90
004c77c4 movd xmm0, eax
004c77c8 cvtdq2pd xmm0, xmm0
004c77cc shr eax, 0x1f
004c77cf addsd xmm0, qword ptr [eax*8 + 0xb6c940]
004c77d8 cvtpd2ps xmm0, xmm0
004c77dc mulss xmm0, dword ptr [0xb6a19c]
004c77e4 mulss xmm0, dword ptr [0xb6aa3c]
004c77ec subss xmm0, dword ptr [0xb6a9c8]
004c77f4 mulss xmm0, dword ptr [0xb6a230]
004c77fc movss dword ptr [ebp - 0x30], xmm0
004c7801 call 0x411fe0
004c7806 movss dword ptr [ebp - 0x18], xmm0
004c780b movss xmm0, dword ptr [ebp - 0x30]
004c7810 call 0x412010
004c7815 movss xmm4, dword ptr [ebp - 0x18]
004c781a movaps xmm1, xmm0
004c781d movss xmm5, dword ptr [edi + 0x2b8]
004c7825 movaps xmm2, xmm4
004c7828 movss xmm3, dword ptr [edi + 0x2bc]
004c7830 mulss xmm0, xmm5
004c7834 mulss xmm1, xmm3
004c7838 mulss xmm2, xmm5
004c783c mulss xmm4, xmm3
004c7840 subss xmm2, xmm1
004c7844 movss xmm1, dword ptr [ebp - 0x10c]
004c784c mulss xmm1, xmm1
004c7850 addss xmm4, xmm0
004c7854 movss xmm0, dword ptr [ebp - 0x11c]
004c785c mulss xmm0, xmm0
004c7860 movss dword ptr [ebp - 0x50], xmm2
004c7865 addss xmm0, xmm1
004c7869 movss dword ptr [ebp - 0x4c], xmm4
004c786e call 0x4228c0
004c7873 push ecx
004c7874 lea eax, [ebp - 0x1c]
004c7877 movss dword ptr [esp], xmm0
004c787c push eax
004c787d lea ecx, [ebp - 0x50]
004c7880 call 0x9628d0
004c7885 movss xmm0, dword ptr [esi + 4]
004c788a movss xmm2, dword ptr [esi]
004c788e movaps xmm1, xmm0
004c7891 movss dword ptr [ebp - 0x30], xmm0
004c7896 addss xmm1, dword ptr [eax + 4]
004c789b addss xmm2, dword ptr [eax]
004c789f subss xmm1, dword ptr [ebp - 0x114]
004c78a7 subss xmm2, dword ptr [ebp - 0x118]
004c78af movaps xmm0, xmm1
004c78b2 movss dword ptr [ebp - 0x11c], xmm1
004c78ba mulss xmm0, xmm1
004c78be movaps xmm1, xmm2
004c78c1 mulss xmm1, xmm2
004c78c5 movss dword ptr [ebp - 0x10c], xmm2
004c78cd addss xmm0, xmm1
004c78d1 call 0x4228c0
004c78d6 movaps xmm1, xmm0
004c78d9 comiss xmm1, dword ptr [0xb6a18c]
004c78e0 jbe 0x4c7903
004c78e2 movss xmm0, dword ptr [0xb6aa8c]
004c78ea divss xmm0, xmm1
004c78ee movaps xmm1, xmm0
004c78f1 mulss xmm0, dword ptr [ebp - 0x11c]
004c78f9 mulss xmm1, dword ptr [ebp - 0x10c]
004c7901 jmp 0x4c7913
004c7903 movss xmm1, dword ptr [ebp - 0x10c]
004c790b movss xmm0, dword ptr [ebp - 0x11c]
004c7913 addss xmm1, dword ptr [ebp - 0x118]
004c791b addss xmm0, dword ptr [ebp - 0x114]
004c7923 lea eax, [ebp - 0x34]
004c7926 push eax
004c7927 lea ecx, [ebp - 0x50]
004c792a movss dword ptr [ebp - 0x118], xmm1
004c7932 subss xmm1, dword ptr [esi]
004c7936 movss dword ptr [ebp - 0x114], xmm0
004c793e subss xmm0, dword ptr [ebp - 0x30]
004c7943 movss dword ptr [ebp - 0x50], xmm1
004c7948 movss dword ptr [ebp - 0x4c], xmm0
004c794d call 0x962560
004c7952 movss xmm2, dword ptr [edi + 0xb84]
004c795a movss xmm1, dword ptr [edi + 0x2f4]
004c7962 movaps xmm0, xmm2
004c7965 mulss xmm0, dword ptr [eax]
004c7969 movss xmm3, dword ptr [eax + 4]
004c796e mulss xmm3, xmm2
004c7972 mulss xmm0, xmm1
004c7976 mulss xmm3, xmm1
004c797a addss xmm0, dword ptr [edi + 0x2b8]
004c7982 addss xmm3, dword ptr [edi + 0x2bc]
004c798a movss dword ptr [edi + 0x2b8], xmm0
004c7992 movss dword ptr [edi + 0x2bc], xmm3
004c799a movss xmm0, dword ptr [edi + 0x2c4]
004c79a2 mulss xmm0, dword ptr [0xb6a5a4]
004c79aa movss dword ptr [edi + 0x2c4], xmm0
004c79b2 jmp 0x4c79eb
004c79b4 push 1
004c79b6 push -1
004c79b8 jmp 0x4c79cb
004c79ba or edx, 0xffffffff
004c79bd mov eax, 0x384
004c79c2 cmp ecx, 2
004c79c5 push 1
004c79c7 cmove eax, edx
004c79ca push eax
004c79cb movss xmm0, dword ptr [edi + 0xb84]
004c79d3 lea eax, [ebp - 0x118]
004c79d9 push ecx
004c79da movss dword ptr [esp], xmm0
004c79df lea ecx, [edi + 0x364]
004c79e5 push eax
004c79e6 call 0x7a3650
004c79eb mov eax, dword ptr [edi + 0xe6c]
004c79f1 cmp eax, -1
004c79f4 je 0x4c7a16
004c79f6 mov ecx, dword ptr [0xbfd680]
004c79fc push edi
004c79fd push eax
004c79fe push 0xa
004c7a00 call 0x8b1170
004c7a05 xor ecx, ecx
004c7a07 test al, al
004c7a09 setne cl
004c7a0c test ecx, ecx
004c7a0e je 0x4c7b8a
004c7a14 jmp 0x4c7a50
004c7a16 mov ecx, edi
004c7a18 call 0x695680
004c7a1d push eax
004c7a1e mov ecx, edi
004c7a20 call 0x6aeb40
004c7a25 test al, al
004c7a27 je 0x4c7b8a
004c7a2d cmp byte ptr [edi + 0xa90], 0
004c7a34 je 0x4c7b8a
004c7a3a call 0x6c3d90
004c7a3f xor edx, edx
004c7a41 mov ecx, 3
004c7a46 div ecx
004c7a48 test edx, edx
004c7a4a jne 0x4c7b8a
004c7a50 push ecx
004c7a51 mov dword ptr [esp], 0x3f800000
004c7a58 push 0
004c7a5a push 0x28
004c7a5c push ecx
004c7a5d mov dword ptr [esp], 0x3f800000
004c7a64 mov ecx, edi
004c7a66 push 0xa5
004c7a6b call 0x6ad720
004c7a70 jmp 0x4c7b8a
004c7a75 cmp dword ptr [edi + 0x30], 0
004c7a79 jne 0x4c7aeb
004c7a7b cmp dword ptr [edi + 0x28], 0xa
004c7a7f jne 0x4c7aeb
004c7a81 mov esi, dword ptr [edi + 0x344]
004c7a87 movq xmm0, qword ptr [0xa08aac]
004c7a8f mov eax, dword ptr [0xa08ab4]
004c7a94 movq qword ptr [ebp - 0x54], xmm0
004c7a99 mov dword ptr [ebp - 0x30], eax
004c7a9c test esi, esi
004c7a9e jne 0x4c7ab0
004c7aa0 push 0xb4d6c4
004c7aa5 push 3
004c7aa7 call 0x95e330
004c7aac add esp, 8
004c7aaf int3 
004c7ab0 mov ecx, dword ptr [ebp - 0x54]
004c7ab3 mov eax, esi
004c7ab5 shr eax, cl
004c7ab7 mov ecx, dword ptr [ebp - 0x50]
004c7aba xor eax, esi
004c7abc mov edx, eax
004c7abe shl edx, cl
004c7ac0 mov ecx, dword ptr [ebp - 0x30]
004c7ac3 xor edx, eax
004c7ac5 mov esi, edx
004c7ac7 mov eax, 0xcccccccd
004c7acc shr esi, cl
004c7ace mov ecx, edi
004c7ad0 xor esi, edx
004c7ad2 mul esi
004c7ad4 push -1
004c7ad6 shr edx, 2
004c7ad9 lea eax, [edx + edx*4]
004c7adc sub esi, eax
004c7ade inc esi
004c7adf push esi
004c7ae0 push dword ptr [edi + 0x2c]
004c7ae3 push dword ptr [edi + 0x28]
004c7ae6 call 0x697c60
004c7aeb push 1
004c7aed push 0xb41e78
004c7af2 lea ecx, [edi + 0x3c]
004c7af5 call 0x405bb0
004c7afa test al, al
004c7afc je 0x4c7b15
004c7afe cmp dword ptr [edi + 0x90], 0
004c7b05 je 0x4c7b15
004c7b07 lea ecx, [edi + 0x8c]
004c7b0d xorps xmm1, xmm1
004c7b10 call 0x403c00
004c7b15 push 1
004c7b17 push 0xb404ec
004c7b1c lea ecx, [edi + 0x3c]
004c7b1f call 0x405740
004c7b24 test al, al
004c7b26 je 0x4c7b48
004c7b28 mov eax, dword ptr [edi + 0x70]
004c7b2b test eax, eax
004c7b2d je 0x4c7b48
004c7b2f lea ecx, [edi + 0x6c]
004c7b32 xorps xmm1, xmm1
004c7b35 call 0x403c00
004c7b3a mov eax, dword ptr [edi + 0x70]
004c7b3d test eax, eax
004c7b3f je 0x4c7b48
004c7b41 mov byte ptr [edi + 0x80], 0
004c7b48 lea ecx, [edi + 0x1dc]
004c7b4e mov dword ptr [edi + 0xab4], 4
004c7b58 cmp ecx, 0xbc52ac
004c7b5e je 0x4c7b8a
004c7b60 movups xmm0, xmmword ptr [0xbc52ac]
004c7b67 movups xmmword ptr [ecx], xmm0
004c7b6a movups xmm0, xmmword ptr [0xbc52bc]
004c7b71 movups xmmword ptr [ecx + 0x10], xmm0
004c7b75 movq xmm0, qword ptr [0xbc52cc]
004c7b7d movq qword ptr [ecx + 0x20], xmm0
004c7b82 mov eax, dword ptr [0xbc52d4]
004c7b87 mov dword ptr [ecx + 0x28], eax
004c7b8a cmp dword ptr [edi + 0x28], 0x390
004c7b91 jne 0x4c7e9f
004c7b97 cmp byte ptr [edi + 0x16b], 0
004c7b9e je 0x4c7e9f
004c7ba4 mov ecx, dword ptr [edi + 0xadc]
004c7baa mov eax, 0x92492493
004c7baf mov esi, dword ptr [edi + 0xad8]
004c7bb5 sub ecx, esi
004c7bb7 imul ecx
004c7bb9 mov dword ptr [ebp - 0x114], 0
004c7bc3 add edx, ecx
004c7bc5 sar edx, 5
004c7bc8 mov eax, edx
004c7bca shr eax, 0x1f
004c7bcd add eax, edx
004c7bcf je 0x4c7e9f
004c7bd5 xor eax, eax
004c7bd7 xor ecx, ecx
004c7bd9 mov dword ptr [ebp - 0x11c], eax
004c7bdf nop 
004c7be0 cmp dword ptr [eax + esi + 0x10], 0x390
004c7be8 jne 0x4c7e5a
004c7bee cmp dword ptr [eax + esi + 0x14], 0
004c7bf3 jne 0x4c7e5a
004c7bf9 lea ecx, [ebp - 0x108]
004c7bff call 0x430d70
004c7c04 lea eax, [ebp - 0x108]
004c7c0a mov dword ptr [ebp - 0xf8], 0x3ecccccd
004c7c14 push eax
004c7c15 push ecx
004c7c16 mov dword ptr [esp], 0x41200000
004c7c1d mov ecx, edi
004c7c1f push 0xc02fec
004c7c24 push 4
004c7c26 call 0x6a3420
004c7c2b call 0x6c3d90
004c7c30 movd xmm0, eax
004c7c34 cvtdq2pd xmm0, xmm0
004c7c38 shr eax, 0x1f
004c7c3b addsd xmm0, qword ptr [eax*8 + 0xb6c940]
004c7c44 cvtpd2ps xmm0, xmm0
004c7c48 mulss xmm0, dword ptr [0xb6a19c]
004c7c50 movss dword ptr [ebp - 0x30], xmm0
004c7c55 call 0x6c3d90
004c7c5a mov ecx, edi
004c7c5c movd xmm0, eax
004c7c60 cvtdq2pd xmm0, xmm0
004c7c64 shr eax, 0x1f
004c7c67 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
004c7c70 cvtpd2ps xmm0, xmm0
004c7c74 mulss xmm0, dword ptr [0xb6a19c]
004c7c7c mulss xmm0, dword ptr [0xb6a874]
004c7c84 addss xmm0, xmm0
004c7c88 movss dword ptr [ebp - 0x18], xmm0
004c7c8d call 0x695680
004c7c92 movss xmm0, dword ptr [ebp - 0x18]
004c7c97 lea esi, [eax + 0x294]
004c7c9d call 0x411fe0
004c7ca2 mulss xmm0, dword ptr [0xb6aa3c]
004c7caa mulss xmm0, dword ptr [ebp - 0x30]
004c7caf addss xmm0, dword ptr [esi]
004c7cb3 subss xmm0, dword ptr [edi + 0x294]
004c7cbb movss dword ptr [ebp - 0x10c], xmm0
004c7cc3 movss xmm0, dword ptr [ebp - 0x18]
004c7cc8 call 0x412010
004c7ccd mulss xmm0, dword ptr [0xb6aa3c]
004c7cd5 mulss xmm0, dword ptr [ebp - 0x30]
004c7cda addss xmm0, dword ptr [esi + 4]
004c7cdf lea esi, [edi + 0x294]
004c7ce5 mov dword ptr [ebp - 0xf8], 0x3f800000
004c7cef mov dword ptr [ebp - 0xfc], 0xbd75c28f
004c7cf9 mov dword ptr [ebp - 0x74], 0xf
004c7d00 subss xmm0, dword ptr [esi + 4]
004c7d05 movaps xmm2, xmm0
004c7d08 movss dword ptr [ebp - 0x30], xmm0
004c7d0d mulss xmm2, xmm0
004c7d11 movss xmm0, dword ptr [ebp - 0x10c]
004c7d19 mulss xmm0, xmm0
004c7d1d addss xmm2, xmm0
004c7d21 movaps xmm0, xmm2
004c7d24 movss dword ptr [ebp - 0x18], xmm2
004c7d29 call 0x4228c0
004c7d2e comiss xmm0, dword ptr [0xb6a18c]
004c7d35 movaps xmm2, xmm0
004c7d38 mulss xmm2, dword ptr [0xb6a274]
004c7d40 jbe 0x4c7d6e
004c7d42 movss xmm1, dword ptr [0xb6a9ec]
004c7d4a minss xmm1, xmm2
004c7d4e divss xmm1, xmm0
004c7d52 movaps xmm0, xmm1
004c7d55 mulss xmm1, dword ptr [ebp - 0x30]
004c7d5a mulss xmm0, dword ptr [ebp - 0x10c]
004c7d62 movss dword ptr [ebp - 0x4c], xmm1
004c7d67 movss dword ptr [ebp - 0x50], xmm0
004c7d6c jmp 0x4c7d85
004c7d6e movss xmm2, dword ptr [ebp - 0x10c]
004c7d76 movss xmm0, dword ptr [ebp - 0x30]
004c7d7b movss dword ptr [ebp - 0x50], xmm2
004c7d80 movss dword ptr [ebp - 0x4c], xmm0
004c7d85 lea eax, [ebp - 0x108]
004c7d8b mov ecx, edi
004c7d8d push eax
004c7d8e push 0
004c7d90 lea eax, [ebp - 0x50]
004c7d93 push eax
004c7d94 push esi
004c7d95 call 0x6a1a20
004c7d9a mov esi, eax
004c7d9c test esi, esi
004c7d9e je 0x4c7e4e
004c7da4 movss xmm0, dword ptr [ebp - 0x18]
004c7da9 mov dword ptr [esi + 0x368], 0x3fa8f5c3
004c7db3 call 0x4228c0
004c7db8 movss xmm1, dword ptr [esi + 0x2b8]
004c7dc0 movss dword ptr [ebp - 0x10c], xmm0
004c7dc8 movss xmm0, dword ptr [esi + 0x2bc]
004c7dd0 mulss xmm1, xmm1
004c7dd4 mulss xmm0, xmm0
004c7dd8 addss xmm0, xmm1
004c7ddc call 0x4228c0
004c7de1 movss xmm1, dword ptr [ebp - 0x10c]
004c7de9 divss xmm1, xmm0
004c7ded movss xmm0, dword ptr [0xb6a5a4]
004c7df5 movss dword ptr [ebp - 0x10c], xmm1
004c7dfd call 0x4c3f60
004c7e02 subss xmm0, dword ptr [0xb6a614]
004c7e0a movss xmm2, dword ptr [ebp - 0x10c]
004c7e12 movss xmm1, dword ptr [0xb6ae98]
004c7e1a subss xmm1, dword ptr [esi + 0x360]
004c7e22 mulss xmm0, dword ptr [0xb6aeb4]
004c7e2a maxss xmm0, dword ptr [0xb6a214]
004c7e32 subss xmm2, xmm0
004c7e36 mulss xmm2, dword ptr [0xb6a9a4]
004c7e3e subss xmm1, xmm2
004c7e42 divss xmm1, xmm0
004c7e46 movss dword ptr [esi + 0x364], xmm1
004c7e4e mov ecx, dword ptr [ebp - 0x114]
004c7e54 mov eax, dword ptr [ebp - 0x11c]
004c7e5a mov esi, dword ptr [edi + 0xad8]
004c7e60 add eax, 0x38
004c7e63 inc ecx
004c7e64 mov dword ptr [ebp - 0x11c], eax
004c7e6a mov dword ptr [ebp - 0x114], ecx
004c7e70 mov eax, 0x92492493
004c7e75 mov ecx, dword ptr [edi + 0xadc]
004c7e7b sub ecx, esi
004c7e7d imul ecx
004c7e7f add edx, ecx
004c7e81 mov ecx, dword ptr [ebp - 0x114]
004c7e87 sar edx, 5
004c7e8a mov eax, edx
004c7e8c shr eax, 0x1f
004c7e8f add eax, edx
004c7e91 cmp ecx, eax
004c7e93 mov eax, dword ptr [ebp - 0x11c]
004c7e99 jb 0x4c7be0
004c7e9f mov ecx, dword ptr [ebp - 0xc]
004c7ea2 mov dword ptr fs:[0], ecx
004c7ea9 pop ecx
004c7eaa pop edi
004c7eab pop esi
004c7eac mov ecx, dword ptr [ebp - 0x14]
004c7eaf xor ecx, ebp
004c7eb1 call 0x9eacd7
004c7eb6 mov esp, ebp
004c7eb8 pop ebp
004c7eb9 mov esp, ebx
004c7ebb pop ebx
004c7ebc ret 
