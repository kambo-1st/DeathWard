004e7250 push ebx
004e7251 mov ebx, esp
004e7253 sub esp, 8
004e7256 and esp, 0xfffffff8
004e7259 add esp, 4
004e725c push ebp
004e725d mov ebp, dword ptr [ebx + 4]
004e7260 mov dword ptr [esp + 4], ebp
004e7264 mov ebp, esp
004e7266 sub esp, 0x60
004e7269 mov eax, dword ptr [0xbaa3b4]
004e726e xor eax, ebp
004e7270 mov dword ptr [ebp - 4], eax
004e7273 push esi
004e7274 push edi
004e7275 mov edi, ecx
004e7277 mov ecx, dword ptr [0xbfd65c]
004e727d push 1
004e727f add ecx, 0x1ba40
004e7285 push ecx
004e7286 push 0x179
004e728b call 0x91d340
004e7290 cvttss2si ecx, dword ptr [edi + 0x2fc]
004e7298 test eax, eax
004e729a mov byte ptr [ebp - 5], 0
004e729e movss xmm2, dword ptr [0xb6a19c]
004e72a6 setne byte ptr [ebp - 0x15]
004e72aa cvttss2si eax, dword ptr [edi + 0x2f8]
004e72b2 movss xmm4, dword ptr [0xb6a874]
004e72ba movss xmm3, dword ptr [0xb6a480]
004e72c2 sub ecx, eax
004e72c4 mov eax, dword ptr [0xbfd65c]
004e72c9 mov dword ptr [ebp - 0x10], ecx
004e72cc mov esi, dword ptr [eax + 0x18190]
004e72d2 mov eax, dword ptr [edi + 0xab4]
004e72d8 mov dword ptr [ebp - 0x1c], esi
004e72db cmp eax, 0x10
004e72de ja 0x4e74be
004e72e4 movss xmm0, dword ptr [0xb6a614]
004e72ec movzx eax, byte ptr [eax + 0x4e82c4]
004e72f3 movss dword ptr [ebp - 0xc], xmm0
004e72f8 jmp dword ptr [eax*4 + 0x4e82b0]
004e72ff cmp dword ptr [edi + 0x30], 0
004e7303 jne 0x4e731f
004e7305 mov eax, dword ptr [edi + 0x344]
004e730b xor edx, edx
004e730d mov ecx, 3
004e7312 div ecx
004e7314 mov eax, dword ptr [edi]
004e7316 mov ecx, edi
004e7318 inc edx
004e7319 mov dword ptr [edi + 0x30], edx
004e731c call dword ptr [eax + 0x60]
004e731f cmp byte ptr [esi], 0
004e7322 je 0x4e733a
004e7324 mov eax, dword ptr [0xbfd65c]
004e7329 mov eax, dword ptr [eax + 0x1a30dc]
004e732f sub eax, dword ptr [esi + 0x11f0]
004e7335 cmp eax, 1
004e7338 jg 0x4e734d
004e733a mov eax, dword ptr [edi + 0x164]
004e7340 and dword ptr [edi + 0x160], 0xfffffffb
004e7347 mov dword ptr [edi + 0x164], eax
004e734d push 0
004e734f lea esi, [edi + 0x3c]
004e7352 mov dword ptr [edi + 0xab4], 0x10
004e735c push 0xb42a58
004e7361 mov ecx, esi
004e7363 call 0x4054f0
004e7368 cmp dword ptr [edi + 0x28], 0x21
004e736c sete byte ptr [ebp - 5]
004e7370 je 0x4e73c2
004e7372 mov eax, dword ptr [edi + 0x2c]
004e7375 cmp eax, 2
004e7378 je 0x4e73c2
004e737a xorps xmm0, xmm0
004e737d mov dword ptr [ebp - 0x40], 0x3df0f0f2
004e7384 movups xmmword ptr [ebp - 0x50], xmm0
004e7388 lea ecx, [edi + 0x1dc]
004e738e cmp eax, 1
004e7391 movaps xmm0, xmmword ptr [0xb6bd30]
004e7398 lea eax, [ebp - 0x60]
004e739b movups xmmword ptr [ebp - 0x60], xmm0
004e739f push eax
004e73a0 jne 0x4e73b2
004e73a2 mov dword ptr [ebp - 0x3c], 0x3e189899
004e73a9 mov dword ptr [ebp - 0x38], 0x3e70f0f2
004e73b0 jmp 0x4e73cd
004e73b2 mov dword ptr [ebp - 0x3c], 0x3db0b0b1
004e73b9 mov dword ptr [ebp - 0x38], 0x3d909091
004e73c0 jmp 0x4e73cd
004e73c2 push 0xbc514c
004e73c7 lea ecx, [edi + 0x1dc]
004e73cd call 0x4021a0
004e73d2 mov eax, dword ptr [edi + 0x160]
004e73d8 and eax, 4
004e73db mov dword ptr [edi + 0xb00], 0
004e73e5 or eax, 0
004e73e8 je 0x4e79f8
004e73ee call 0x6c3d90
004e73f3 mov ecx, dword ptr [0xbfd65c]
004e73f9 push eax
004e73fa push 0
004e73fc push 0
004e73fe push 0xc02fec
004e7403 lea eax, [edi + 0x294]
004e7409 push eax
004e740a push 0xf
004e740c push 0x3e8
004e7411 call 0x422e20
004e7416 mov eax, dword ptr [edi + 0x164]
004e741c and dword ptr [edi + 0x160], 0xfffffffb
004e7423 mov dword ptr [edi + 0x164], eax
004e7429 jmp 0x4e79f8
004e742e push 0
004e7430 lea esi, [edi + 0x3c]
004e7433 push 0xb42a58
004e7438 mov ecx, esi
004e743a call 0x4054f0
004e743f movss xmm1, dword ptr [edi + 0xb00]
004e7447 movaps xmm0, xmm1
004e744a mov dword ptr [edi + 0x2d4], 0x42c80000
004e7454 mulss xmm0, dword ptr [edi + 0x2f4]
004e745c addss xmm0, dword ptr [edi + 0x2a8]
004e7464 comiss xmm0, dword ptr [0xb6a18c]
004e746b movss dword ptr [edi + 0x2a8], xmm0
004e7473 jbe 0x4e7720
004e7479 push dword ptr [edi + 0x298]
004e747f mov ecx, dword ptr [ebp - 0x1c]
004e7482 push dword ptr [edi + 0x294]
004e7488 mov dword ptr [edi + 0x2a8], 0
004e7492 call 0x7aee40
004e7497 test eax, eax
004e7499 je 0x4e76cb
004e749f mov eax, dword ptr [edi]
004e74a1 mov ecx, edi
004e74a3 call dword ptr [eax + 0x24]
004e74a6 movss xmm3, dword ptr [0xb6a480]
004e74ae movss xmm2, dword ptr [0xb6a19c]
004e74b6 movss xmm4, dword ptr [0xb6a874]
004e74be cmp dword ptr [edi + 0x2c], 2
004e74c2 je 0x4e74ce
004e74c4 cmp dword ptr [edi + 0x28], 0x21
004e74c8 jne 0x4e7637
004e74ce call 0x6c3d90
004e74d3 xor edx, edx
004e74d5 mov ecx, 5
004e74da div ecx
004e74dc test edx, edx
004e74de jne 0x4e7637
004e74e4 call 0x6c3d90
004e74e9 movd xmm0, eax
004e74ed cvtdq2pd xmm0, xmm0
004e74f1 shr eax, 0x1f
004e74f4 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
004e74fd cvtpd2ps xmm0, xmm0
004e7501 mulss xmm0, xmm2
004e7505 movss dword ptr [ebp - 0x28], xmm0
004e750a call 0x6c3d90
004e750f movd xmm0, eax
004e7513 cvtdq2pd xmm0, xmm0
004e7517 shr eax, 0x1f
004e751a addsd xmm0, qword ptr [eax*8 + 0xb6c940]
004e7523 cvtpd2ps xmm0, xmm0
004e7527 mulss xmm0, xmm2
004e752b subss xmm0, xmm3
004e752f mulss xmm0, dword ptr [0xb6a434]
004e7537 movss dword ptr [ebp - 0x14], xmm0
004e753c call 0x6c3d90
004e7541 movd xmm0, eax
004e7545 cvtdq2pd xmm0, xmm0
004e7549 shr eax, 0x1f
004e754c addsd xmm0, qword ptr [eax*8 + 0xb6c940]
004e7555 cvtpd2ps xmm0, xmm0
004e7559 mulss xmm0, xmm2
004e755d movss dword ptr [ebp - 0x10], xmm0
004e7562 call 0x6c3d90
004e7567 movd xmm0, eax
004e756b cvtdq2pd xmm0, xmm0
004e756f shr eax, 0x1f
004e7572 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
004e757b cvtpd2ps xmm0, xmm0
004e757f mulss xmm0, xmm2
004e7583 mulss xmm0, xmm4
004e7587 addss xmm0, xmm0
004e758b movss dword ptr [ebp - 0xc], xmm0
004e7590 call 0x411fe0
004e7595 mulss xmm0, dword ptr [ebp - 0x10]
004e759a mulss xmm0, dword ptr [0xb6a8cc]
004e75a2 addss xmm0, dword ptr [edi + 0x294]
004e75aa movss dword ptr [ebp - 0x24], xmm0
004e75af movss xmm0, dword ptr [ebp - 0xc]
004e75b4 call 0x412010
004e75b9 mulss xmm0, dword ptr [ebp - 0x10]
004e75be mulss xmm0, dword ptr [0xb6a8cc]
004e75c6 addss xmm0, dword ptr [edi + 0x298]
004e75ce movss dword ptr [ebp - 0x20], xmm0
004e75d3 call 0x6c3d90
004e75d8 movss xmm0, dword ptr [edi + 0x2b8]
004e75e0 mulss xmm0, dword ptr [0xb6a350]
004e75e8 mov ecx, dword ptr [0xbfd65c]
004e75ee movss xmm1, dword ptr [ebp - 0x28]
004e75f3 mulss xmm1, dword ptr [0xb6a688]
004e75fb push eax
004e75fc addss xmm0, dword ptr [ebp - 0x14]
004e7601 push 0
004e7603 push 0
004e7605 lea eax, [ebp - 0x34]
004e7608 push eax
004e7609 movss dword ptr [ebp - 0x34], xmm0
004e760e lea eax, [ebp - 0x24]
004e7611 movss xmm0, dword ptr [edi + 0x2bc]
004e7619 mulss xmm0, dword ptr [0xb6a350]
004e7621 push eax
004e7622 push 0x42
004e7624 push 0x3e8
004e7629 subss xmm0, xmm1
004e762d movss dword ptr [ebp - 0x30], xmm0
004e7632 call 0x422e20
004e7637 cmp byte ptr [edi + 0x16b], 0
004e763e je 0x4e8244
004e7644 cmp dword ptr [edi + 0x28], 0x21
004e7648 je 0x4e8244
004e764e movss xmm0, dword ptr [0xb6aa3c]
004e7656 lea esi, [edi + 0x294]
004e765c movss xmm1, dword ptr [esi]
004e7660 movss xmm2, dword ptr [esi + 4]
004e7665 subss xmm1, xmm0
004e7669 subss xmm2, dword ptr [0xb6ab20]
004e7671 divss xmm1, xmm0
004e7675 divss xmm2, xmm0
004e7679 addss xmm1, dword ptr [0xb6a480]
004e7681 addss xmm2, dword ptr [0xb6a480]
004e7689 cvttss2si edx, xmm1
004e768d cvttss2si ecx, xmm2
004e7691 test edx, edx
004e7693 js 0x4e808b
004e7699 mov eax, dword ptr [ebp - 0x1c]
004e769c mov eax, dword ptr [eax + 0xc]
004e769f cmp edx, eax
004e76a1 jge 0x4e808b
004e76a7 test ecx, ecx
004e76a9 js 0x4e808b
004e76af mov esi, dword ptr [ebp - 0x1c]
004e76b2 cmp ecx, dword ptr [esi + 0x10]
004e76b5 lea esi, [edi + 0x294]
004e76bb jge 0x4e808b
004e76c1 imul eax, ecx
004e76c4 add eax, edx
004e76c6 jmp 0x4e808e
004e76cb movss xmm0, dword ptr [edi + 0x2b8]
004e76d3 mulss xmm0, dword ptr [0xb6a560]
004e76db movss dword ptr [edi + 0x2b8], xmm0
004e76e3 movss xmm0, dword ptr [edi + 0x2bc]
004e76eb mulss xmm0, dword ptr [0xb6a560]
004e76f3 movss dword ptr [edi + 0x2bc], xmm0
004e76fb movss xmm1, dword ptr [edi + 0xb00]
004e7703 movaps xmm0, xmm1
004e7706 andps xmm0, xmmword ptr [0xb6c980]
004e770d comiss xmm0, dword ptr [ebp - 0xc]
004e7711 jbe 0x4e771d
004e7713 mulss xmm1, dword ptr [0xb6ae08]
004e771b jmp 0x4e7720
004e771d xorps xmm1, xmm1
004e7720 movss xmm2, dword ptr [edi + 0x2a8]
004e7728 movss xmm0, dword ptr [0xb6af28]
004e7730 comiss xmm0, xmm2
004e7733 jbe 0x4e774b
004e7735 mov dword ptr [edi + 0x17c], 3
004e773f mov dword ptr [edi + 0x180], 0
004e7749 jmp 0x4e7772
004e774b mov dword ptr [edi + 0x180], 4
004e7755 xor eax, eax
004e7757 movss xmm0, dword ptr [0xb6ae88]
004e775f comiss xmm0, xmm2
004e7762 setbe al
004e7765 lea eax, [eax*2 + 3]
004e776c mov dword ptr [edi + 0x17c], eax
004e7772 cmp dword ptr [edi + 0x28], 0x21
004e7776 movss xmm0, dword ptr [edi + 0x2f4]
004e777e mulss xmm0, dword ptr [0xb6a480]
004e7786 addss xmm0, xmm1
004e778a movss dword ptr [edi + 0xb00], xmm0
004e7792 jne 0x4e7956
004e7798 or dword ptr [edi + 0x160], 1
004e779f mov ecx, edi
004e77a1 or dword ptr [edi + 0x164], 0x10
004e77a8 push 0
004e77aa push 0x1e
004e77ac mov byte ptr [edi + 0x308], 1
004e77b3 call 0x684790
004e77b8 test al, al
004e77ba je 0x4e77ec
004e77bc call 0x6c3d90
004e77c1 xor edx, edx
004e77c3 mov ecx, 3
004e77c8 div ecx
004e77ca test edx, edx
004e77cc je 0x4e77ec
004e77ce mov edx, dword ptr [edi]
004e77d0 lea ecx, [ebp - 0x5c]
004e77d3 push 0x1e
004e77d5 call 0x427290
004e77da push eax
004e77db push 0
004e77dd push 0
004e77df push ecx
004e77e0 mov ecx, edi
004e77e2 mov dword ptr [esp], 0x3f800000
004e77e9 call dword ptr [edx + 0x20]
004e77ec movss xmm0, dword ptr [edi + 0x14]
004e77f1 xorps xmm1, xmm1
004e77f4 comiss xmm0, xmm1
004e77f7 jbe 0x4e7930
004e77fd mov eax, dword ptr [edi + 0x18]
004e7800 and eax, 0x1000004
004e7805 or eax, 0
004e7808 je 0x4e7819
004e780a mov dword ptr [edi + 0x2d8], 0x3f800000
004e7814 jmp 0x4e78e1
004e7819 mov esi, dword ptr [edi + 8]
004e781c cmp esi, dword ptr [edi + 0xc]
004e781f je 0x4e78b1
004e7825 movss xmm3, dword ptr [0xb6a974]
004e782d movss xmm2, dword ptr [0xb6a864]
004e7835 jmp 0x4e7843
004e7837 nop word ptr [eax + eax]
004e7840 xorps xmm1, xmm1
004e7843 movss xmm0, dword ptr [esi]
004e7847 comiss xmm3, xmm0
004e784a jb 0x4e7874
004e784c comiss xmm0, xmm1
004e784f jbe 0x4e786a
004e7851 call 0x6c3d90
004e7856 xor edx, edx
004e7858 mov ecx, 3
004e785d div ecx
004e785f test edx, edx
004e7861 je 0x4e7886
004e7863 movss xmm0, dword ptr [ebp - 0xc]
004e7868 jmp 0x4e7893
004e786a movss xmm1, dword ptr [edi + 0x2d8]
004e7872 jmp 0x4e78a7
004e7874 call 0x6c3d90
004e7879 xor edx, edx
004e787b mov ecx, 3
004e7880 div ecx
004e7882 test edx, edx
004e7884 je 0x4e7890
004e7886 movss xmm0, dword ptr [0xb6a7b0]
004e788e jmp 0x4e7893
004e7890 movaps xmm0, xmm2
004e7893 movss xmm1, dword ptr [edi + 0x2d8]
004e789b subss xmm1, xmm0
004e789f movss dword ptr [edi + 0x2d8], xmm1
004e78a7 add esi, 0x38
004e78aa cmp esi, dword ptr [edi + 0xc]
004e78ad jne 0x4e7840
004e78af jmp 0x4e78b9
004e78b1 movss xmm1, dword ptr [edi + 0x2d8]
004e78b9 movss xmm0, dword ptr [ebp - 0xc]
004e78be comiss xmm0, xmm1
004e78c1 jbe 0x4e78d0
004e78c3 mov dword ptr [edi + 0x2d8], 0x3f800000
004e78cd movaps xmm1, xmm0
004e78d0 movss xmm0, dword ptr [0xb6a6f0]
004e78d8 comiss xmm0, xmm1
004e78db mov byte ptr [ebp - 5], 1
004e78df jbe 0x4e792d
004e78e1 mov esi, dword ptr [0xbfd680]
004e78e7 lea ecx, [ebp - 0x10]
004e78ea mov dword ptr [ebp - 0x10], 0x105
004e78f1 call 0x8b1340
004e78f6 sub esp, 8
004e78f9 mov dword ptr [esp + 4], 0
004e7901 mov dword ptr [esp], 0x3f800000
004e7908 push 0
004e790a push 2
004e790c push ecx
004e790d mov dword ptr [esp], 0x3f59999a
004e7914 lea ecx, [esi + 0x29de0]
004e791a push dword ptr [ebp - 0x10]
004e791d call 0x888de0
004e7922 mov eax, dword ptr [edi]
004e7924 mov ecx, edi
004e7926 call dword ptr [eax + 0x24]
004e7929 mov byte ptr [ebp - 5], 1
004e792d lea esi, [edi + 0x3c]
004e7930 mov ecx, edi
004e7932 call 0x6ad7a0
004e7937 test eax, eax
004e7939 jg 0x4e7956
004e793b mov eax, dword ptr [0xbfd65c]
004e7940 mov eax, dword ptr [eax + 0x18190]
004e7946 cmp dword ptr [eax + 0x11ec], 2
004e794d jg 0x4e7956
004e794f mov eax, dword ptr [edi]
004e7951 mov ecx, edi
004e7953 call dword ptr [eax + 0x24]
004e7956 cmp dword ptr [edi + 0x17c], 5
004e795d jne 0x4e79f8
004e7963 movss xmm1, dword ptr [edi + 0xb00]
004e796b andps xmm1, xmmword ptr [0xb6c980]
004e7972 movss xmm0, dword ptr [0xb6a4c4]
004e797a comiss xmm0, xmm1
004e797d jbe 0x4e79f8
004e797f cmp dword ptr [edi + 0x28], 0x21
004e7983 jne 0x4e79a8
004e7985 movss xmm0, dword ptr [edi + 0x2c4]
004e798d mov eax, dword ptr [edi + 0x288]
004e7993 mulss xmm0, dword ptr [0xb6a5a4]
004e799b mov eax, dword ptr [eax + 0x44]
004e799e movss dword ptr [edi + 0x2c4], xmm0
004e79a6 jmp 0x4e79f2
004e79a8 movss xmm1, dword ptr [edi + 0x2bc]
004e79b0 movss xmm0, dword ptr [edi + 0x2b8]
004e79b8 mulss xmm0, xmm0
004e79bc mulss xmm1, xmm1
004e79c0 addss xmm0, xmm1
004e79c4 call 0x4228c0
004e79c9 movss xmm1, dword ptr [0xb6a7b0]
004e79d1 comiss xmm1, xmm0
004e79d4 jbe 0x4e79f8
004e79d6 call 0x6c3d90
004e79db test al, 3
004e79dd jne 0x4e79f8
004e79df mov eax, dword ptr [edi + 0x288]
004e79e5 mov dword ptr [edi + 0xab4], 7
004e79ef mov eax, dword ptr [eax + 0x44]
004e79f2 mov dword ptr [edi + 0x2d4], eax
004e79f8 cmp byte ptr [ebp - 5], 0
004e79fc je 0x4e74a6
004e7a02 movss xmm0, dword ptr [edi + 0x2d8]
004e7a0a lea eax, [ebp - 0x10]
004e7a0d divss xmm0, dword ptr [edi + 0x2dc]
004e7a15 mov dword ptr [ebp - 0x10], 0
004e7a1c lea ecx, [ebp - 0x14]
004e7a1f xorps xmm1, xmm1
004e7a22 comiss xmm1, xmm0
004e7a25 movss xmm1, dword ptr [ebp - 0xc]
004e7a2a movss dword ptr [ebp - 0x14], xmm0
004e7a2f cmovbe eax, ecx
004e7a32 movss xmm0, dword ptr [eax]
004e7a36 comiss xmm0, xmm1
004e7a39 ja 0x4e7a41
004e7a3b movss xmm1, xmm0
004e7a3f jmp 0x4e7a45
004e7a41 movss xmm1, xmm1
004e7a45 cmp dword ptr [esi + 0x80], 1
004e7a4c movss dword ptr [ebp - 0x10], xmm1
004e7a51 jg 0x4e7a74
004e7a53 cmp dword ptr [esi + 0x14], 0x10
004e7a57 mov eax, esi
004e7a59 jb 0x4e7a5d
004e7a5b mov eax, dword ptr [esi]
004e7a5d push 1
004e7a5f push eax
004e7a60 push 0xa0830c
004e7a65 push 3
004e7a67 call 0x95e330
004e7a6c movss xmm1, dword ptr [ebp - 0x10]
004e7a71 add esp, 0x10
004e7a74 mov eax, dword ptr [esi + 0x7c]
004e7a77 movss dword ptr [eax + 0xd0], xmm1
004e7a7f movss dword ptr [eax + 0xd4], xmm1
004e7a87 cmp dword ptr [esi + 0x80], 0
004e7a8e jg 0x4e7ab1
004e7a90 cmp dword ptr [esi + 0x14], 0x10
004e7a94 mov eax, esi
004e7a96 jb 0x4e7a9a
004e7a98 mov eax, dword ptr [esi]
004e7a9a push 0
004e7a9c push eax
004e7a9d push 0xa0830c
004e7aa2 push 3
004e7aa4 call 0x95e330
004e7aa9 movss xmm1, dword ptr [ebp - 0x10]
004e7aae add esp, 0x10
004e7ab1 movss xmm3, dword ptr [0xb6a480]
004e7ab9 movaps xmm0, xmm1
004e7abc mulss xmm1, dword ptr [0xb6a560]
004e7ac4 mov eax, dword ptr [esi + 0x7c]
004e7ac7 mulss xmm0, xmm3
004e7acb addss xmm1, dword ptr [0xb6a350]
004e7ad3 mov dword ptr [eax + 0x54], 0x3f800000
004e7ada addss xmm0, xmm3
004e7ade movss dword ptr [eax + 0x4c], xmm1
004e7ae3 movss dword ptr [eax + 0x50], xmm1
004e7ae8 movss dword ptr [eax + 0x48], xmm0
004e7aed jmp 0x4e74ae
004e7af2 push 0
004e7af4 push 0xb40360
004e7af9 lea ecx, [edi + 0x3c]
004e7afc call 0x4054f0
004e7b01 movss xmm0, dword ptr [edi + 0x2c4]
004e7b09 mulss xmm0, dword ptr [0xb6a4c4]
004e7b11 movss dword ptr [edi + 0x2c4], xmm0
004e7b19 cmp dword ptr [edi + 0x70], 0
004e7b1d je 0x4e7b2c
004e7b1f cmp byte ptr [edi + 0x80], 0
004e7b26 jne 0x4e74a6
004e7b2c mov dword ptr [edi + 0xab4], 3
004e7b36 jmp 0x4e74a6
004e7b3b cmp dword ptr [edi + 0xe6c], -1
004e7b42 movss xmm0, dword ptr [edi + 0x2c4]
004e7b4a mulss xmm0, dword ptr [0xb6a4c4]
004e7b52 movss dword ptr [edi + 0x2c4], xmm0
004e7b5a je 0x4e7b99
004e7b5c lea eax, [ebp - 0x24]
004e7b5f xorps xmm2, xmm2
004e7b62 push eax
004e7b63 mov ecx, edi
004e7b65 call 0x6af0c0
004e7b6a mov ecx, eax
004e7b6c movss xmm0, dword ptr [ecx]
004e7b70 ucomiss xmm0, dword ptr [0xc02fec]
004e7b77 lahf 
004e7b78 test ah, 0x44
004e7b7b jp 0x4e7b99
004e7b7d movss xmm0, dword ptr [ecx + 4]
004e7b82 ucomiss xmm0, dword ptr [0xc02ff0]
004e7b89 lahf 
004e7b8a test ah, 0x44
004e7b8d jp 0x4e7b99
004e7b8f mov dword ptr [edi + 0x360], 0
004e7b99 mov esi, dword ptr [ebp - 0x10]
004e7b9c test esi, esi
004e7b9e jle 0x4e7f1e
004e7ba4 mov eax, dword ptr [edi + 0x360]
004e7baa mov ecx, dword ptr [edi + 0x2c]
004e7bad inc eax
004e7bae mov dword ptr [edi + 0x360], eax
004e7bb4 cmp ecx, 1
004e7bb7 je 0x4e7bbe
004e7bb9 cmp ecx, 2
004e7bbc jne 0x4e7bc5
004e7bbe inc eax
004e7bbf mov dword ptr [edi + 0x360], eax
004e7bc5 cmp eax, 0xc
004e7bc8 je 0x4e7bea
004e7bca cmp eax, 0x18
004e7bcd je 0x4e7bea
004e7bcf cmp eax, 0x24
004e7bd2 je 0x4e7bea
004e7bd4 cmp dword ptr [edi + 0xe6c], -1
004e7bdb jne 0x4e7bea
004e7bdd cmp dword ptr [edi + 0xe88], 0
004e7be4 je 0x4e7ef8
004e7bea push ecx
004e7beb lea eax, [ebp - 0x2c]
004e7bee mov dword ptr [esp], 0x42700000
004e7bf5 push eax
004e7bf6 mov ecx, edi
004e7bf8 call 0x695a30
004e7bfd cmp byte ptr [ebp - 0x15], 0
004e7c01 jne 0x4e7c37
004e7c03 mov eax, dword ptr [edi + 0x2c]
004e7c06 cmp eax, 1
004e7c09 je 0x4e7c22
004e7c0b cmp eax, 2
004e7c0e je 0x4e7c22
004e7c10 call 0x6c3d90
004e7c15 xor edx, edx
004e7c17 mov ecx, 6
004e7c1c div ecx
004e7c1e mov eax, edx
004e7c20 jmp 0x4e7c2a
004e7c22 call 0x6c3d90
004e7c27 and eax, 3
004e7c2a test eax, eax
004e7c2c je 0x4e7c37
004e7c2e mov byte ptr [ebp - 5], 1
004e7c32 mov cl, byte ptr [ebp - 5]
004e7c35 jmp 0x4e7c39
004e7c37 xor cl, cl
004e7c39 mov edx, dword ptr [edi + 0xe6c]
004e7c3f cmp edx, -1
004e7c42 je 0x4e7c92
004e7c44 lea eax, [ebp - 0x24]
004e7c47 mov byte ptr [ebp - 5], 1
004e7c4b push eax
004e7c4c xorps xmm2, xmm2
004e7c4f mov ecx, edi
004e7c51 call 0x6af0c0
004e7c56 mov edx, dword ptr [edi + 0xe6c]
004e7c5c mov cl, byte ptr [ebp - 5]
004e7c5f movss xmm1, dword ptr [eax]
004e7c63 movss xmm0, dword ptr [eax + 4]
004e7c68 mulss xmm1, dword ptr [0xb6aafc]
004e7c70 mulss xmm0, dword ptr [0xb6aafc]
004e7c78 addss xmm1, dword ptr [edi + 0x294]
004e7c80 addss xmm0, dword ptr [edi + 0x298]
004e7c88 movss dword ptr [ebp - 0x2c], xmm1
004e7c8d movss dword ptr [ebp - 0x28], xmm0
004e7c92 mov esi, dword ptr [edi + 0xe88]
004e7c98 test esi, esi
004e7c9a jne 0x4e7d7f
004e7ca0 mov eax, dword ptr [edi + 0x160]
004e7ca6 and eax, 0x100
004e7cab or eax, esi
004e7cad jne 0x4e7d7f
004e7cb3 test cl, cl
004e7cb5 jne 0x4e7d7f
004e7cbb nop dword ptr [eax + eax]
004e7cc0 call 0x6c3d90
004e7cc5 movd xmm0, eax
004e7cc9 cvtdq2pd xmm0, xmm0
004e7ccd shr eax, 0x1f
004e7cd0 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
004e7cd9 cvtpd2ps xmm0, xmm0
004e7cdd mulss xmm0, dword ptr [0xb6a19c]
004e7ce5 mulss xmm0, dword ptr [0xb6a874]
004e7ced addss xmm0, xmm0
004e7cf1 movss dword ptr [ebp - 0xc], xmm0
004e7cf6 call 0x411fe0
004e7cfb movss dword ptr [ebp - 0x14], xmm0
004e7d00 movss xmm0, dword ptr [ebp - 0xc]
004e7d05 call 0x412010
004e7d0a movaps xmm1, xmm0
004e7d0d lea eax, [edi + 0x294]
004e7d13 movss xmm0, dword ptr [ebp - 0x14]
004e7d18 lea ecx, [ebp - 0x34]
004e7d1b push 0
004e7d1d push 0
004e7d1f movss dword ptr [edi + 0x28c], xmm0
004e7d27 mulss xmm0, dword ptr [0xb6a9c8]
004e7d2f push 0
004e7d31 movss dword ptr [edi + 0x290], xmm1
004e7d39 mulss xmm1, dword ptr [0xb6a9c8]
004e7d41 push 0x3e7
004e7d46 addss xmm0, dword ptr [eax]
004e7d4a push 1
004e7d4c addss xmm1, dword ptr [edi + 0x298]
004e7d54 push ecx
004e7d55 mov ecx, dword ptr [ebp - 0x1c]
004e7d58 push eax
004e7d59 movss dword ptr [ebp - 0x34], xmm0
004e7d5e movss dword ptr [ebp - 0x30], xmm1
004e7d63 call 0x7af4b0
004e7d68 test al, al
004e7d6a jne 0x4e7ef5
004e7d70 inc esi
004e7d71 cmp esi, 0xa
004e7d74 jl 0x4e7cc0
004e7d7a jmp 0x4e7ef5
004e7d7f cmp edx, -1
004e7d82 jne 0x4e7de0
004e7d84 test esi, esi
004e7d86 jne 0x4e7de0
004e7d88 mov ecx, dword ptr [ebp - 0x1c]
004e7d8b lea eax, [ebp - 0x2c]
004e7d8e push esi
004e7d8f push esi
004e7d90 push esi
004e7d91 push 0x3e7
004e7d96 push 1
004e7d98 push eax
004e7d99 lea eax, [edi + 0x294]
004e7d9f push eax
004e7da0 call 0x7af4b0
004e7da5 test al, al
004e7da7 jne 0x4e7de0
004e7da9 lea ecx, [edi + 0x364]
004e7daf call 0x7a34f0
004e7db4 push 1
004e7db6 push esi
004e7db7 push ecx
004e7db8 lea eax, [ebp - 0x2c]
004e7dbb mov dword ptr [esp], 0x3f800000
004e7dc2 push eax
004e7dc3 lea ecx, [edi + 0x364]
004e7dc9 call 0x7a3650
004e7dce movss xmm1, dword ptr [edi + 0x2b8]
004e7dd6 movss xmm2, dword ptr [edi + 0x2bc]
004e7dde jmp 0x4e7dfa
004e7de0 movss xmm1, dword ptr [ebp - 0x2c]
004e7de5 movss xmm2, dword ptr [ebp - 0x28]
004e7dea subss xmm1, dword ptr [edi + 0x294]
004e7df2 subss xmm2, dword ptr [edi + 0x298]
004e7dfa movaps xmm0, xmm1
004e7dfd movss dword ptr [ebp - 0xc], xmm1
004e7e02 mulss xmm0, xmm1
004e7e06 movaps xmm1, xmm2
004e7e09 mulss xmm1, xmm2
004e7e0d movss dword ptr [ebp - 0x14], xmm2
004e7e12 addss xmm0, xmm1
004e7e16 call 0x4228c0
004e7e1b comiss xmm0, dword ptr [0xb6a18c]
004e7e22 movss xmm2, dword ptr [ebp - 0xc]
004e7e27 jbe 0x4e7e47
004e7e29 movss xmm1, dword ptr [0xb6a614]
004e7e31 divss xmm1, xmm0
004e7e35 movaps xmm0, xmm1
004e7e38 mulss xmm2, xmm0
004e7e3c movss xmm0, dword ptr [ebp - 0x14]
004e7e41 mulss xmm0, xmm1
004e7e45 jmp 0x4e7e4c
004e7e47 movss xmm0, dword ptr [ebp - 0x14]
004e7e4c movss dword ptr [edi + 0x28c], xmm2
004e7e54 movss dword ptr [edi + 0x290], xmm0
004e7e5c call 0x6c3d90
004e7e61 movd xmm0, eax
004e7e65 cvtdq2pd xmm0, xmm0
004e7e69 shr eax, 0x1f
004e7e6c addsd xmm0, qword ptr [eax*8 + 0xb6c940]
004e7e75 cvtpd2ps xmm0, xmm0
004e7e79 mulss xmm0, dword ptr [0xb6a19c]
004e7e81 subss xmm0, dword ptr [0xb6a480]
004e7e89 mulss xmm0, dword ptr [0xb6aa0c]
004e7e91 mulss xmm0, dword ptr [0xb6a230]
004e7e99 movss dword ptr [ebp - 0xc], xmm0
004e7e9e call 0x411fe0
004e7ea3 movss dword ptr [ebp - 0x14], xmm0
004e7ea8 movss xmm0, dword ptr [ebp - 0xc]
004e7ead call 0x412010
004e7eb2 movss xmm3, dword ptr [edi + 0x28c]
004e7eba movaps xmm1, xmm0
004e7ebd movss xmm2, dword ptr [edi + 0x290]
004e7ec5 movss xmm5, dword ptr [ebp - 0x14]
004e7eca movaps xmm4, xmm5
004e7ecd mulss xmm1, xmm2
004e7ed1 mulss xmm4, xmm3
004e7ed5 mulss xmm5, xmm2
004e7ed9 mulss xmm0, xmm3
004e7edd subss xmm4, xmm1
004e7ee1 addss xmm5, xmm0
004e7ee5 movss dword ptr [edi + 0x28c], xmm4
004e7eed movss dword ptr [edi + 0x290], xmm5
004e7ef5 mov esi, dword ptr [ebp - 0x10]
004e7ef8 call 0x6c3d90
004e7efd test al, 1
004e7eff jne 0x4e7f12
004e7f01 mov eax, dword ptr [edi + 0x360]
004e7f07 test al, 1
004e7f09 je 0x4e7f12
004e7f0b inc eax
004e7f0c mov dword ptr [edi + 0x360], eax
004e7f12 sub esi, 1
004e7f15 mov dword ptr [ebp - 0x10], esi
004e7f18 jne 0x4e7ba4
004e7f1e cmp dword ptr [edi + 0xe6c], -1
004e7f25 je 0x4e7f50
004e7f27 cmp dword ptr [edi + 0x360], 0x28
004e7f2e jle 0x4e7f50
004e7f30 movss xmm0, dword ptr [0xc02fec]
004e7f38 movss dword ptr [edi + 0x28c], xmm0
004e7f40 movss xmm0, dword ptr [0xc02ff0]
004e7f48 movss dword ptr [edi + 0x290], xmm0
004e7f50 movss xmm0, dword ptr [edi + 0x28c]
004e7f58 ucomiss xmm0, dword ptr [0xc02fec]
004e7f5f lahf 
004e7f60 test ah, 0x44
004e7f63 jp 0x4e7f8e
004e7f65 movss xmm0, dword ptr [edi + 0x290]
004e7f6d ucomiss xmm0, dword ptr [0xc02ff0]
004e7f74 lahf 
004e7f75 test ah, 0x44
004e7f78 jp 0x4e7f8e
004e7f7a push 0
004e7f7c push 0xb3fd8c
004e7f81 lea ecx, [edi + 0x3c]
004e7f84 call 0x4054f0
004e7f89 jmp 0x4e8037
004e7f8e push 0
004e7f90 push 0xb41264
004e7f95 lea ecx, [edi + 0x3c]
004e7f98 call 0x4054f0
004e7f9d cmp byte ptr [ebp - 0x15], 0
004e7fa1 movss xmm3, dword ptr [0xb6a864]
004e7fa9 jne 0x4e7fe1
004e7fab mov eax, dword ptr [edi + 0x2c]
004e7fae cmp eax, 1
004e7fb1 jne 0x4e7fbd
004e7fb3 movss xmm3, dword ptr [0xb6a8f8]
004e7fbb jmp 0x4e7fe1
004e7fbd cmp eax, 2
004e7fc0 jne 0x4e7fe1
004e7fc2 cmp dword ptr [edi + 0x34], 0x38b
004e7fc9 jne 0x4e7fd5
004e7fcb movss xmm0, dword ptr [0xb6a70c]
004e7fd3 jmp 0x4e7fdd
004e7fd5 movss xmm0, dword ptr [0xb6a754]
004e7fdd mulss xmm3, xmm0
004e7fe1 movss xmm0, dword ptr [edi + 0x2f4]
004e7fe9 movaps xmm1, xmm3
004e7fec mulss xmm1, dword ptr [edi + 0x28c]
004e7ff4 movss xmm2, dword ptr [edi + 0x290]
004e7ffc mulss xmm2, xmm3
004e8000 mulss xmm1, xmm0
004e8004 mulss xmm2, xmm0
004e8008 xorps xmm0, xmm0
004e800b addss xmm1, dword ptr [edi + 0x2b8]
004e8013 addss xmm2, dword ptr [edi + 0x2bc]
004e801b comiss xmm0, xmm1
004e801e movss dword ptr [edi + 0x2b8], xmm1
004e8026 movss dword ptr [edi + 0x2bc], xmm2
004e802e setae al
004e8031 mov byte ptr [edi + 0x13c], al
004e8037 cmp dword ptr [edi + 0x360], 0x30
004e803e movss xmm2, dword ptr [0xb6a19c]
004e8046 movss xmm3, dword ptr [0xb6a480]
004e804e movss xmm4, dword ptr [0xb6a874]
004e8056 jl 0x4e74be
004e805c mov dword ptr [edi + 0x360], 0
004e8066 movss xmm0, dword ptr [0xc02fec]
004e806e movss dword ptr [edi + 0x28c], xmm0
004e8076 movss xmm0, dword ptr [0xc02ff0]
004e807e movss dword ptr [edi + 0x290], xmm0
004e8086 jmp 0x4e74be
004e808b or eax, 0xffffffff
004e808e mov ecx, dword ptr [ebp - 0x1c]
004e8091 push eax
004e8092 call 0x7aeec0
004e8097 test eax, eax
004e8099 jne 0x4e8203
004e809f mov eax, dword ptr [edi + 0x2c]
004e80a2 cmp eax, 1
004e80a5 jne 0x4e80be
004e80a7 push dword ptr [edi + 0x344]
004e80ad lea eax, [edi + 0x2b8]
004e80b3 push 3
004e80b5 push 0
004e80b7 push eax
004e80b8 push esi
004e80b9 jmp 0x4e8235
004e80be cmp eax, 2
004e80c1 jne 0x4e8173
004e80c7 push dword ptr [edi + 0x344]
004e80cd movss xmm0, dword ptr [edi + 0x2b8]
004e80d5 lea eax, [ebp - 0x24]
004e80d8 push dword ptr [edi + 0x30]
004e80db mulss xmm0, dword ptr [0xb6a480]
004e80e3 mov ecx, dword ptr [0xbfd65c]
004e80e9 push edi
004e80ea push eax
004e80eb movss dword ptr [ebp - 0x24], xmm0
004e80f0 movss xmm0, dword ptr [edi + 0x2bc]
004e80f8 mulss xmm0, dword ptr [0xb6a480]
004e8100 push esi
004e8101 push 0xb
004e8103 push 0x21
004e8105 movss dword ptr [ebp - 0x20], xmm0
004e810a call 0x422e20
004e810f mov esi, eax
004e8111 mov ecx, dword ptr [esi + 0x164]
004e8117 mov edx, dword ptr [esi]
004e8119 and dword ptr [esi + 0x160], 0xfffffffb
004e8120 mov dword ptr [esi + 0x164], ecx
004e8126 mov ecx, esi
004e8128 call dword ptr [edx + 0xc]
004e812b movss xmm1, dword ptr [0xb6ae44]
004e8133 mov dword ptr [esi + 0x2a8], 0xbf800000
004e813d call 0x6c3d90
004e8142 movd xmm0, eax
004e8146 cvtdq2pd xmm0, xmm0
004e814a shr eax, 0x1f
004e814d addsd xmm0, qword ptr [eax*8 + 0xb6c940]
004e8156 cvtpd2ps xmm0, xmm0
004e815a mulss xmm0, dword ptr [0xb6a19c]
004e8162 subss xmm1, xmm0
004e8166 movss dword ptr [esi + 0xb00], xmm1
004e816e jmp 0x4e8244
004e8173 mov ecx, edi
004e8175 call 0x6aac30
004e817a push -1
004e817c push 0
004e817e push 0
004e8180 push 0x55
004e8182 mov ecx, edi
004e8184 call 0x697c60
004e8189 mov eax, dword ptr [edi + 0x2dc]
004e818f lea ecx, [ebp - 0x60]
004e8192 mov dword ptr [edi + 0xab4], 0
004e819c mov dword ptr [edi + 0x2d8], eax
004e81a2 mov byte ptr [edi + 0x16b], 0
004e81a9 call 0x402120
004e81ae push eax
004e81af lea ecx, [edi + 0x1dc]
004e81b5 call 0x4021a0
004e81ba movss xmm0, dword ptr [0xc02fec]
004e81c2 mov ecx, edi
004e81c4 mov eax, dword ptr [edi]
004e81c6 movss dword ptr [edi + 0x2a4], xmm0
004e81ce movss xmm0, dword ptr [0xc02ff0]
004e81d6 movss dword ptr [edi + 0x2a8], xmm0
004e81de movss xmm0, dword ptr [0xc02fec]
004e81e6 movss dword ptr [edi + 0x28c], xmm0
004e81ee movss xmm0, dword ptr [0xc02ff0]
004e81f6 movss dword ptr [edi + 0x290], xmm0
004e81fe call dword ptr [eax + 0xc]
004e8201 jmp 0x4e8244
004e8203 cmp dword ptr [edi + 0x2c], 1
004e8207 jne 0x4e8244
004e8209 push 0
004e820b push 0
004e820d push ecx
004e820e mov ecx, dword ptr [ebp - 0x1c]
004e8211 lea eax, [ebp - 0x24]
004e8214 mov dword ptr [esp], 0
004e821b push esi
004e821c push eax
004e821d call 0x7cf240
004e8222 push dword ptr [edi + 0x344]
004e8228 lea eax, [ebp - 0x24]
004e822b push 3
004e822d push 0
004e822f push 0xc02fec
004e8234 push eax
004e8235 mov ecx, dword ptr [0xbfd65c]
004e823b push 0xa
004e823d push 5
004e823f call 0x422e20
004e8244 mov esi, dword ptr [edi + 8]
004e8247 cmp esi, dword ptr [edi + 0xc]
004e824a je 0x4e829c
004e824c nop dword ptr [eax]
004e8250 mov eax, dword ptr [esi + 8]
004e8253 and eax, 2
004e8256 or eax, 0
004e8259 je 0x4e8294
004e825b movss xmm0, dword ptr [edi + 0x14]
004e8260 mov ecx, edi
004e8262 subss xmm0, dword ptr [esi]
004e8266 push -1
004e8268 push 0
004e826a push 0x332
004e826f movss dword ptr [edi + 0x14], xmm0
004e8274 mov dword ptr [esi], 0
004e827a call 0x412260
004e827f test al, al
004e8281 je 0x4e8294
004e8283 push -1
004e8285 push dword ptr [edi + 0x30]
004e8288 push 2
004e828a push 0x332
004e828f call 0x697c60
004e8294 add esi, 0x38
004e8297 cmp esi, dword ptr [edi + 0xc]
004e829a jne 0x4e8250
004e829c mov ecx, dword ptr [ebp - 4]
004e829f pop edi
004e82a0 xor ecx, ebp
004e82a2 pop esi
004e82a3 call 0x9eacd7
004e82a8 mov esp, ebp
004e82aa pop ebp
004e82ab mov esp, ebx
004e82ad pop ebx
004e82ae ret 
