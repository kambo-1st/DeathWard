007e73c8 cmp ebx, dword ptr [ebp - 0x60]
007e73cb je 0x7e7513
007e73d1 mov edi, dword ptr [ebp - 0x50]
007e73d4 xorps xmm2, xmm2
007e73d7 mov ecx, dword ptr [ebp - 0x40]
007e73da mov esi, ebx
007e73dc mov ebx, dword ptr [ebp - 0x60]
007e73df xorps xmm3, xmm3
007e73e2 movss dword ptr [ebp - 0x30], xmm2
007e73e7 nop word ptr [eax + eax]
007e73f0 mov eax, dword ptr [esi]
007e73f2 addss xmm3, dword ptr [eax + 0x34]
007e73f7 movss dword ptr [ebp - 0x38], xmm3
007e73fc call 0x6b1490
007e7401 test al, al
007e7403 je 0x7e744b
007e7405 mov ecx, dword ptr [esi]
007e7407 mov ebx, dword ptr [ebp - 0x40]
007e740a mov eax, dword ptr [ecx + 0x38]
007e740d cmp eax, dword ptr [ebx]
007e740f mov ebx, dword ptr [ebp - 0x60]
007e7412 jne 0x7e7448
007e7414 cmp edi, edx
007e7416 je 0x7e7422
007e7418 mov dword ptr [edi], ecx
007e741a add edi, 4
007e741d mov dword ptr [ebp - 0x50], edi
007e7420 jmp 0x7e743c
007e7422 push esi
007e7423 push edi
007e7424 lea ecx, [ebp - 0x54]
007e7427 call 0x426fb0
007e742c mov edx, dword ptr [ebp - 0x4c]
007e742f movss xmm2, dword ptr [ebp - 0x30]
007e7434 movss xmm3, dword ptr [ebp - 0x38]
007e7439 mov edi, dword ptr [ebp - 0x50]
007e743c mov eax, dword ptr [esi]
007e743e addss xmm2, dword ptr [eax + 0x34]
007e7443 movss dword ptr [ebp - 0x30], xmm2
007e7448 mov ecx, dword ptr [ebp - 0x40]
007e744b add esi, 4
007e744e cmp esi, ebx
007e7450 jne 0x7e73f0
007e7452 mov edi, dword ptr [ebp - 0x58]
007e7455 xorps xmm0, xmm0
007e7458 comiss xmm0, xmm3
007e745b mov ebx, dword ptr [ebp - 0x3c]
007e745e mov dword ptr [ebp - 0x2c], edx
007e7461 jb 0x7e754b
007e7467 sub esp, 8
007e746a lea eax, [ebp - 0x28]
007e746d push eax
007e746e call 0x71f370
007e7473 cmp dword ptr [eax + 0x14], 0x10
007e7477 jb 0x7e747b
007e7479 mov eax, dword ptr [eax]
007e747b push dword ptr [ebp - 0x68]
007e747e push eax
007e747f push dword ptr [ebp - 0x6c]
007e7482 push dword ptr [ebp - 0x70]
007e7485 push dword ptr [ebp - 0x74]
007e7488 push dword ptr [ebp - 0x78]
007e748b push dword ptr [ebp - 0x7c]
007e748e push dword ptr [ebp - 0x80]
007e7491 push dword ptr [ebp - 0x44]
007e7494 push dword ptr [ebp - 0x48]
007e7497 push 0xb4e2e8
007e749c push 0
007e749e call 0x95e330
007e74a3 mov edx, dword ptr [ebp - 0x14]
007e74a6 add esp, 0x30
007e74a9 cmp edx, 0x10
007e74ac jb 0x7e74dc
007e74ae mov ecx, dword ptr [ebp - 0x28]
007e74b1 inc edx
007e74b2 mov eax, ecx
007e74b4 cmp edx, 0x1000
007e74ba jb 0x7e74d2
007e74bc mov ecx, dword ptr [ecx - 4]
007e74bf add edx, 0x23
007e74c2 sub eax, ecx
007e74c4 add eax, -4
007e74c7 cmp eax, 0x1f
007e74ca jbe 0x7e74d2
007e74cc call dword ptr [0xa065ac]
007e74d2 push edx
007e74d3 push ecx
007e74d4 call 0x9eb08e
007e74d9 add esp, 8
007e74dc mov edx, dword ptr [ebp - 0x54]
007e74df test edx, edx
007e74e1 je 0x7e7513
007e74e3 mov ecx, dword ptr [ebp - 0x2c]
007e74e6 mov eax, edx
007e74e8 sub ecx, edx
007e74ea and ecx, 0xfffffffc
007e74ed cmp ecx, 0x1000
007e74f3 jb 0x7e7509
007e74f5 mov edx, dword ptr [edx - 4]
007e74f8 add ecx, 0x23
007e74fb sub eax, edx
007e74fd add eax, -4
007e7500 cmp eax, 0x1f
007e7503 ja 0x7e76d4
007e7509 push ecx
007e750a push edx
007e750b call 0x9eb08e
007e7510 add esp, 8
007e7513 test ebx, ebx
007e7515 je 0x7e7544
007e7517 sub edi, ebx
007e7519 mov eax, ebx
007e751b and edi, 0xfffffffc
007e751e cmp edi, 0x1000
007e7524 jb 0x7e753a
007e7526 mov ebx, dword ptr [ebx - 4]
007e7529 add edi, 0x23
007e752c sub eax, ebx
007e752e add eax, -4
007e7531 cmp eax, 0x1f
007e7534 ja 0x7e76d4
007e753a push edi
007e753b push ebx
007e753c call 0x9eb08e
007e7541 add esp, 8
007e7544 xor eax, eax
007e7546 jmp 0x7e774b
007e754b movq xmm0, qword ptr [0xa08af4]
007e7553 mov eax, dword ptr [ebp - 0x48]
007e7556 mov esi, dword ptr [0xa08afc]
007e755c movq qword ptr [ebp - 0x1c], xmm0
007e7561 mov dword ptr [ebp - 0x44], esi
007e7564 test eax, eax
007e7566 jne 0x7e7585
007e7568 push 0xb4d6c4
007e756d push 3
007e756f call 0x95e330
007e7574 add esp, 8
007e7577 int3
007e7578 movss xmm2, dword ptr [ebp - 0x30]
007e757d movss xmm3, dword ptr [ebp - 0x38]
007e7582 mov eax, dword ptr [ebp - 0x48]
007e7585 mov ecx, dword ptr [ebp - 0x1c]
007e7588 mov edx, eax
007e758a shr edx, cl
007e758c mov ecx, dword ptr [ebp - 0x18]
007e758f xor edx, eax
007e7591 mov eax, edx
007e7593 shl eax, cl
007e7595 mov ecx, esi
007e7597 xor eax, edx
007e7599 mov esi, dword ptr [ebp - 0x50]
007e759c mov edx, eax
007e759e shr edx, cl
007e75a0 xor edx, eax
007e75a2 mov eax, edx
007e75a4 mov dword ptr [ebp - 0x3c], edx
007e75a7 shr eax, 0x1f
007e75aa movd xmm0, edx
007e75ae cvtdq2pd xmm0, xmm0
007e75b2 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
007e75bb cvtpd2ps xmm1, xmm0
007e75bf movaps xmm0, xmm2
007e75c2 divss xmm0, xmm3
007e75c6 mulss xmm1, dword ptr [0xb6a198]
007e75ce mulss xmm0, dword ptr [0xb6a970]
007e75d6 movss dword ptr [ebp - 0x58], xmm1
007e75db movss dword ptr [ebp - 0x48], xmm0
007e75e0 cmp dword ptr [ebp - 0x54], esi
007e75e3 je 0x7e76de
007e75e9 test edx, edx
007e75eb jne 0x7e760f
007e75ed push 0xb4d6c4
007e75f2 push 3
007e75f4 call 0x95e330
007e75f9 add esp, 8
007e75fc int3
007e75fd movss xmm1, dword ptr [ebp - 0x58]
007e7602 movss xmm2, dword ptr [ebp - 0x30]
007e7607 movss xmm3, dword ptr [ebp - 0x38]
007e760c mov edx, dword ptr [ebp - 0x3c]
007e760f mov ecx, dword ptr [ebp - 0x1c]
007e7612 shr edx, cl
007e7614 xor edx, dword ptr [ebp - 0x3c]
007e7617 mov ecx, dword ptr [ebp - 0x18]
007e761a mov eax, edx
007e761c shl eax, cl
007e761e mov ecx, dword ptr [ebp - 0x44]
007e7621 xor eax, edx
007e7623 mov edx, eax
007e7625 movss xmm4, dword ptr [ebp - 0x48]
007e762a shr edx, cl
007e762c xor edx, eax
007e762e movd xmm0, edx
007e7632 cvtdq2pd xmm0, xmm0
007e7636 shr edx, 0x1f
007e7639 addsd xmm0, qword ptr [edx*8 + 0xb6c940]
007e7642 cvtpd2ps xmm0, xmm0
007e7646 mulss xmm0, dword ptr [0xb6a198]
007e764e comiss xmm4, xmm0
007e7651 jbe 0x7e76de
007e7657 mov eax, dword ptr [ebp - 0x54]
007e765a mulss xmm1, xmm2
007e765e cmp eax, esi
007e7660 je 0x7e7678
007e7662 xorps xmm0, xmm0
007e7665 mov ecx, dword ptr [eax]
007e7667 addss xmm0, dword ptr [ecx + 0x34]
007e766c comiss xmm0, xmm1
007e766f ja 0x7e76da
007e7671 add eax, 4
007e7674 cmp eax, esi
007e7676 jne 0x7e7665
007e7678 xor esi, esi
007e767a mov edx, dword ptr [ebp - 0x54]
007e767d test edx, edx
007e767f je 0x7e76ad
007e7681 mov ecx, dword ptr [ebp - 0x2c]
007e7684 mov eax, edx
007e7686 sub ecx, edx
007e7688 and ecx, 0xfffffffc
007e768b cmp ecx, 0x1000
007e7691 jb 0x7e76a3
007e7693 mov edx, dword ptr [edx - 4]
007e7696 add ecx, 0x23
007e7699 sub eax, edx
007e769b add eax, -4
007e769e cmp eax, 0x1f
007e76a1 ja 0x7e76d4
007e76a3 push ecx
007e76a4 push edx
007e76a5 call 0x9eb08e
007e76aa add esp, 8
007e76ad test ebx, ebx
007e76af je 0x7e7749
007e76b5 sub edi, ebx
007e76b7 mov eax, ebx
007e76b9 and edi, 0xfffffffc
007e76bc cmp edi, 0x1000
007e76c2 jb 0x7e773f
007e76c4 mov ebx, dword ptr [ebx - 4]
007e76c7 add edi, 0x23
007e76ca sub eax, ebx
007e76cc add eax, -4
007e76cf cmp eax, 0x1f
007e76d2 jbe 0x7e773f
007e76d4 call dword ptr [0xa065ac]
007e76da mov esi, ecx
007e76dc jmp 0x7e770a
007e76de mov ecx, dword ptr [ebp - 0x60]
007e76e1 mov eax, ebx
007e76e3 mulss xmm1, xmm3
007e76e7 cmp eax, ecx
007e76e9 je 0x7e7678
007e76eb xorps xmm0, xmm0
007e76ee nop
007e76f0 mov edx, dword ptr [eax]
007e76f2 addss xmm0, dword ptr [edx + 0x34]
007e76f7 comiss xmm0, xmm1
007e76fa ja 0x7e7708
007e76fc add eax, 4
007e76ff cmp eax, ecx
007e7701 jne 0x7e76f0
007e7703 jmp 0x7e7678
007e7708 mov esi, edx
007e770a test esi, esi
007e770c je 0x7e767a
007e7712 cmp byte ptr [ebp - 0x31], 0
007e7716 je 0x7e767a
007e771c movss xmm1, dword ptr [esi + 0x34]
007e7721 mulss xmm1, dword ptr [0xb6a2cc]
007e7729 movss xmm0, dword ptr [0xb6a1a4]
007e7731 maxss xmm0, xmm1
007e7735 movss dword ptr [esi + 0x34], xmm0
