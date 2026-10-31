005346d0 push ebp
005346d1 mov ebp, esp
005346d3 push -1
005346d5 push 0x9ef9e5
005346da mov eax, dword ptr fs:[0]
005346e0 push eax
005346e1 sub esp, 0x7c
005346e4 mov eax, dword ptr [0xbaa3b4]
005346e9 xor eax, ebp
005346eb mov dword ptr [ebp - 0x10], eax
005346ee push ebx
005346ef push esi
005346f0 push edi
005346f1 push eax
005346f2 lea eax, [ebp - 0xc]
005346f5 mov dword ptr fs:[0], eax
005346fb mov edi, ecx
005346fd cmp dword ptr [edi + 0x2c], 1
00534701 jne 0x53470d
00534703 call 0x5351f0
00534708 jmp 0x5351cd
0053470d mov eax, dword ptr [edi + 0xab4]
00534713 test eax, eax
00534715 je 0x534b38
0053471b cmp eax, 4
0053471e je 0x53484f
00534724 cmp eax, 0x10
00534727 jne 0x534b4c
0053472d movss xmm0, dword ptr [edi + 0x2c4]
00534735 mulss xmm0, dword ptr [0xb6a560]
0053473d mov dword ptr [ebp - 0x2c], 0xf
00534744 mov dword ptr [ebp - 0x30], 8
0053474b mov byte ptr [ebp - 0x38], 0
0053474f movss dword ptr [edi + 0x2c4], xmm0
00534757 mov eax, dword ptr [0xb404ec]
0053475c mov ecx, dword ptr [0xb404f0]
00534762 mov dword ptr [ebp - 0x40], eax
00534765 mov dword ptr [ebp - 0x3c], ecx
00534768 mov dword ptr [ebp - 4], 2
0053476f mov eax, dword ptr [0xb40504]
00534774 mov ecx, dword ptr [0xb40508]
0053477a mov dword ptr [ebp - 0x14], 0xf
00534781 mov dword ptr [ebp - 0x18], 8
00534788 mov dword ptr [ebp - 0x28], eax
0053478b mov dword ptr [ebp - 0x24], ecx
0053478e mov byte ptr [ebp - 0x20], 0
00534792 push ecx
00534793 mov byte ptr [ebp - 4], 3
00534797 lea eax, [ebp - 0x40]
0053479a mov dword ptr [esp], 0x3dcccccd
005347a1 mov ecx, edi
005347a3 push eax
005347a4 lea eax, [ebp - 0x28]
005347a7 push eax
005347a8 call 0x6980a0
005347ad mov byte ptr [ebp - 4], 2
005347b1 mov edx, dword ptr [ebp - 0x14]
005347b4 cmp edx, 0x10
005347b7 jb 0x5347e1
005347b9 mov ecx, dword ptr [ebp - 0x28]
005347bc inc edx
005347bd mov eax, ecx
005347bf cmp edx, 0x1000
005347c5 jb 0x5347d7
005347c7 mov ecx, dword ptr [ecx - 4]
005347ca add edx, 0x23
005347cd sub eax, ecx
005347cf add eax, -4
005347d2 cmp eax, 0x1f
005347d5 ja 0x534820
005347d7 push edx
005347d8 push ecx
005347d9 call 0x9eb08e
005347de add esp, 8
005347e1 mov dword ptr [ebp - 4], 0xffffffff
005347e8 mov edx, dword ptr [ebp - 0x2c]
005347eb mov dword ptr [ebp - 0x18], 0
005347f2 mov dword ptr [ebp - 0x14], 0xf
005347f9 mov byte ptr [ebp - 0x28], 0
005347fd cmp edx, 0x10
00534800 jb 0x534830
00534802 mov ecx, dword ptr [ebp - 0x40]
00534805 inc edx
00534806 mov eax, ecx
00534808 cmp edx, 0x1000
0053480e jb 0x534826
00534810 mov ecx, dword ptr [ecx - 4]
00534813 add edx, 0x23
00534816 sub eax, ecx
00534818 add eax, -4
0053481b cmp eax, 0x1f
0053481e jbe 0x534826
00534820 call dword ptr [0xa065ac]
00534826 push edx
00534827 push ecx
00534828 call 0x9eb08e
0053482d add esp, 8
00534830 cmp dword ptr [edi + 0x90], 0
00534837 je 0x534b42
0053483d cmp byte ptr [edi + 0xa0], 0
00534844 jne 0x534b4c
0053484a jmp 0x534b42
0053484f cmp dword ptr [edi + 0xb10], 0
00534856 jg 0x534953
0053485c cmp dword ptr [edi + 0x30], 3
00534860 je 0x534953
00534866 cmp dword ptr [edi + 0xe6c], -1
0053486d jne 0x534953
00534873 push 0
00534875 push ecx
00534876 lea eax, [ebp - 0x60]
00534879 mov dword ptr [esp], 0
00534880 push eax
00534881 call 0x695a30
00534886 push eax
00534887 lea ecx, [edi + 0x364]
0053488d call 0x7a4830
00534892 cmp dword ptr [edi + 0xaa0], 0
00534899 jle 0x5348e1
0053489b mov eax, dword ptr [0xbfd65c]
005348a0 mov eax, dword ptr [eax + 0x1a30dc]
005348a6 sub eax, dword ptr [edi + 0x280]
005348ac cmp eax, 0xa
005348af jle 0x5348e1
005348b1 call 0x6c3d90
005348b6 mov ecx, 0x64
005348bb xor edx, edx
005348bd div ecx
005348bf push ecx
005348c0 mov dword ptr [esp], 0x3f800000
005348c7 push 0
005348c9 lea eax, [edx + 0x2d]
005348cc push eax
005348cd push ecx
005348ce mov dword ptr [esp], 0x3f800000
005348d5 mov ecx, edi
005348d7 push 0x8f
005348dc call 0x6ad720
005348e1 mov edx, dword ptr [edi + 0xb10]
005348e7 test edx, edx
005348e9 jns 0x53490f
005348eb cvttss2si eax, dword ptr [edi + 0x2f8]
005348f3 cvttss2si ecx, dword ptr [edi + 0x2fc]
005348fb sub ecx, eax
005348fd lea eax, [ecx + edx]
00534900 xor edx, edx
00534902 test eax, eax
00534904 cmovs edx, eax
00534907 mov dword ptr [edi + 0xb10], edx
0053490d test edx, edx
0053490f jne 0x534936
00534911 cmp dword ptr [edi + 0xaa0], 0
00534918 jg 0x534936
0053491a call 0x6c3d90
0053491f xor edx, edx
00534921 mov ecx, 0xa
00534926 div ecx
00534928 test edx, edx
0053492a jne 0x534936
0053492c mov dword ptr [edi + 0xb10], 0x5a
00534936 movss xmm0, dword ptr [edi + 0x2c4]
0053493e mulss xmm0, dword ptr [0xb6a560]
00534946 movss dword ptr [edi + 0x2c4], xmm0
0053494e jmp 0x534a01
00534953 mov eax, dword ptr [edi + 0x30]
00534956 movss xmm0, dword ptr [0xb6a480]
0053495e cmp eax, 2
00534961 jne 0x53496d
00534963 movss xmm0, dword ptr [0xb6a50c]
0053496b jmp 0x53497a
0053496d cmp eax, 3
00534970 jne 0x53497a
00534972 movss xmm0, dword ptr [0xb6a5a4]
0053497a push 1
0053497c push 0
0053497e sub esp, 8
00534981 lea eax, [ebp - 0x60]
00534984 movss dword ptr [esp + 4], xmm0
0053498a mov dword ptr [esp], 0
00534991 push eax
00534992 call 0x695a30
00534997 push eax
00534998 lea ecx, [edi + 0x364]
0053499e call 0x7a3650
005349a3 cvttss2si eax, dword ptr [edi + 0x2fc]
005349ab cvttss2si ecx, dword ptr [edi + 0x2f8]
005349b3 movss xmm0, dword ptr [edi + 0x2c4]
005349bb mulss xmm0, dword ptr [0xb6a5a4]
005349c3 sub ecx, eax
005349c5 mov eax, dword ptr [edi + 0xb10]
005349cb add eax, ecx
005349cd xor ecx, ecx
005349cf test eax, eax
005349d1 movss dword ptr [edi + 0x2c4], xmm0
005349d9 cmovg ecx, eax
005349dc mov dword ptr [edi + 0xb10], ecx
005349e2 test ecx, ecx
005349e4 jne 0x534a01
005349e6 call 0x6c3d90
005349eb xor edx, edx
005349ed mov ecx, 0x3c
005349f2 div ecx
005349f4 mov eax, 0xffffffe2
005349f9 sub eax, edx
005349fb mov dword ptr [edi + 0xb10], eax
00534a01 mov eax, dword ptr [0xb404ec]
00534a06 mov ecx, dword ptr [0xb404f0]
00534a0c mov dword ptr [ebp - 0x2c], 0xf
00534a13 mov dword ptr [ebp - 0x30], 8
00534a1a mov dword ptr [ebp - 0x40], eax
00534a1d mov dword ptr [ebp - 0x3c], ecx
00534a20 mov byte ptr [ebp - 0x38], 0
00534a24 mov dword ptr [ebp - 4], 0
00534a2b mov eax, dword ptr [0xb40504]
00534a30 mov ecx, dword ptr [0xb40508]
00534a36 mov dword ptr [ebp - 0x14], 0xf
00534a3d mov dword ptr [ebp - 0x18], 8
00534a44 mov dword ptr [ebp - 0x28], eax
00534a47 mov dword ptr [ebp - 0x24], ecx
00534a4a mov byte ptr [ebp - 0x20], 0
00534a4e push ecx
00534a4f mov byte ptr [ebp - 4], 1
00534a53 lea eax, [ebp - 0x40]
00534a56 mov dword ptr [esp], 0x3dcccccd
00534a5d mov ecx, edi
00534a5f push eax
00534a60 lea eax, [ebp - 0x28]
00534a63 push eax
00534a64 call 0x6980a0
00534a69 mov byte ptr [ebp - 4], 0
00534a6d mov edx, dword ptr [ebp - 0x14]
00534a70 cmp edx, 0x10
00534a73 jb 0x534a9d
00534a75 mov ecx, dword ptr [ebp - 0x28]
00534a78 inc edx
00534a79 mov eax, ecx
00534a7b cmp edx, 0x1000
00534a81 jb 0x534a93
00534a83 mov ecx, dword ptr [ecx - 4]
00534a86 add edx, 0x23
00534a89 sub eax, ecx
00534a8b add eax, -4
00534a8e cmp eax, 0x1f
00534a91 ja 0x534adc
00534a93 push edx
00534a94 push ecx
00534a95 call 0x9eb08e
00534a9a add esp, 8
00534a9d mov dword ptr [ebp - 4], 0xffffffff
00534aa4 mov edx, dword ptr [ebp - 0x2c]
00534aa7 mov dword ptr [ebp - 0x18], 0
00534aae mov dword ptr [ebp - 0x14], 0xf
00534ab5 mov byte ptr [ebp - 0x28], 0
00534ab9 cmp edx, 0x10
00534abc jb 0x534aec
00534abe mov ecx, dword ptr [ebp - 0x40]
00534ac1 inc edx
00534ac2 mov eax, ecx
00534ac4 cmp edx, 0x1000
00534aca jb 0x534ae2
00534acc mov ecx, dword ptr [ecx - 4]
00534acf add edx, 0x23
00534ad2 sub eax, ecx
00534ad4 add eax, -4
00534ad7 cmp eax, 0x1f
00534ada jbe 0x534ae2
00534adc call dword ptr [0xa065ac]
00534ae2 push edx
00534ae3 push ecx
00534ae4 call 0x9eb08e
00534ae9 add esp, 8
00534aec cmp dword ptr [edi + 0x70], 0
00534af0 je 0x534b0c
00534af2 cmp byte ptr [edi + 0x80], 0
00534af9 je 0x534b0c
00534afb push 0
00534afd push 0xb41264
00534b02 lea ecx, [edi + 0x3c]
00534b05 call 0x405a00
00534b0a jmp 0x534b4c
00534b0c push 1
00534b0e push 0xb41264
00534b13 lea ecx, [edi + 0x3c]
00534b16 call 0x405bb0
00534b1b test al, al
00534b1d je 0x534b4c
00534b1f cmp dword ptr [edi + 0x90], 0
00534b26 je 0x534b4c
00534b28 lea ecx, [edi + 0x8c]
00534b2e xorps xmm1, xmm1
00534b31 call 0x403c00
00534b36 jmp 0x534b4c
00534b38 mov dword ptr [edi + 0xb10], 0
00534b42 mov dword ptr [edi + 0xab4], 4
00534b4c push 0
00534b4e push 0xa
00534b50 mov ecx, edi
00534b52 call 0x684790
00534b57 test al, al
00534b59 je 0x534c3d
00534b5f mov eax, dword ptr [edi + 0x30]
00534b62 cmp eax, 3
00534b65 jne 0x534bf7
00534b6b call 0x6c3d90
00534b70 mov ecx, dword ptr [0xbfd65c]
00534b76 push eax
00534b77 push 0
00534b79 push edi
00534b7a push 0xc02fec
00534b7f lea eax, [edi + 0x294]
00534b85 push eax
00534b86 push 0x16
00534b88 push 0x3e8
00534b8d call 0x422e20
00534b92 mov esi, eax
00534b94 call 0x6c3d90
00534b99 mov ecx, esi
00534b9b movd xmm0, eax
00534b9f cvtdq2pd xmm0, xmm0
00534ba3 shr eax, 0x1f
00534ba6 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
00534baf mov eax, dword ptr [esi]
00534bb1 cvtpd2ps xmm0, xmm0
00534bb5 mulss xmm0, dword ptr [0xb6a19c]
00534bbd mulss xmm0, dword ptr [0xb6a3b0]
00534bc5 addss xmm0, dword ptr [0xb6a350]
00534bcd movss dword ptr [esi + 0xd8], xmm0
00534bd5 movss dword ptr [esi + 0xdc], xmm0
00534bdd call dword ptr [eax + 0xc]
00534be0 mov dword ptr [esi + 0x3ac], 0x1e
00534bea mov dword ptr [esi + 0x3b0], 0x1e
00534bf4 mov eax, dword ptr [edi + 0x30]
00534bf7 test eax, eax
00534bf9 je 0x534c3d
00534bfb call 0x6c3d90
00534c00 push ecx
00534c01 mov ecx, edi
00534c03 movd xmm0, eax
00534c07 cvtdq2pd xmm0, xmm0
00534c0b shr eax, 0x1f
00534c0e addsd xmm0, qword ptr [eax*8 + 0xb6c940]
00534c17 cvtpd2ps xmm1, xmm0
00534c1b mulss xmm1, dword ptr [0xb6a19c]
00534c23 mulss xmm1, dword ptr [0xb6a434]
00534c2b addss xmm1, dword ptr [0xb6a434]
00534c33 movss dword ptr [esp], xmm1
00534c38 call 0x68d7b0
00534c3d mov esi, dword ptr [edi + 0xb10]
00534c43 xorps xmm1, xmm1
00534c46 test esi, esi
00534c48 jle 0x534c8b
00534c4a movss xmm0, dword ptr [edi + 0x14]
00534c4f comiss xmm0, xmm1
00534c52 jbe 0x534c8b
00534c54 addss xmm0, xmm0
00534c58 sub esp, 8
00534c5b movss dword ptr [ebp - 0x58], xmm0
00534c60 fld dword ptr [ebp - 0x58]
00534c63 fstp qword ptr [esp]
00534c66 call 0x9ec3ac
00534c6b fstp dword ptr [ebp - 0x58]
00534c6e cvttss2si eax, dword ptr [ebp - 0x58]
00534c73 add esp, 8
00534c76 xorps xmm1, xmm1
00534c79 sub esi, eax
00534c7b mov eax, 1
00534c80 cmp esi, eax
00534c82 cmovg eax, esi
00534c85 mov dword ptr [edi + 0xb10], eax
00534c8b mov eax, dword ptr [edi + 0x30]
00534c8e mov dword ptr [ebp - 0x80], eax
00534c91 cmp eax, 3
00534c94 jae 0x535010
00534c9a movss xmm0, dword ptr [edi + 0x14]
00534c9f comiss xmm0, xmm1
00534ca2 jbe 0x535010
00534ca8 movss xmm2, dword ptr [edi + 0x2d8]
00534cb0 mov ecx, eax
00534cb2 subss xmm2, xmm0
00534cb6 movss dword ptr [ebp - 0x7c], xmm2
00534cbb nop dword ptr [eax + eax]
00534cc0 mov eax, 3
00534cc5 xorps xmm0, xmm0
00534cc8 sub eax, ecx
00534cca mov edx, ecx
00534ccc cvtsi2sd xmm0, eax
00534cd0 shr eax, 0x1f
00534cd3 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
00534cdc mov eax, 4
00534ce1 sub eax, ecx
00534ce3 cvtpd2ps xmm1, xmm0
00534ce7 xorps xmm0, xmm0
00534cea mulss xmm1, dword ptr [edi + 0x2dc]
00534cf2 cvtsi2sd xmm0, eax
00534cf6 shr eax, 0x1f
00534cf9 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
00534d02 cvtpd2ps xmm0, xmm0
00534d06 divss xmm1, xmm0
00534d0a comiss xmm1, xmm2
00534d0d jb 0x534fda
00534d13 lea eax, [ecx + 1]
00534d16 mov ecx, edi
00534d18 mov dword ptr [edi + 0x30], eax
00534d1b call 0x68b970
00534d20 mov ecx, edi
00534d22 call 0x695680
00534d27 movss xmm1, dword ptr [edi + 0x294]
00534d2f lea ebx, [edi + 0x294]
00534d35 movss xmm2, dword ptr [ebx + 4]
00534d3a subss xmm1, dword ptr [eax + 0x294]
00534d42 subss xmm2, dword ptr [eax + 0x298]
00534d4a movaps xmm0, xmm1
00534d4d movss dword ptr [ebp - 0x64], xmm1
00534d52 mulss xmm0, xmm1
00534d56 movaps xmm1, xmm2
00534d59 mulss xmm1, xmm2
00534d5d movss dword ptr [ebp - 0x58], xmm2
00534d62 addss xmm0, xmm1
00534d66 call 0x4228c0
00534d6b movss xmm2, dword ptr [ebp - 0x64]
00534d70 xorps xmm1, xmm1
00534d73 comiss xmm0, xmm1
00534d76 movss xmm3, dword ptr [ebp - 0x58]
00534d7b jbe 0x534d9b
00534d7d movss xmm1, dword ptr [0xb6a614]
00534d85 divss xmm1, xmm0
00534d89 mulss xmm2, xmm1
00534d8d mulss xmm3, xmm1
00534d91 movss dword ptr [ebp - 0x64], xmm2
00534d96 movss dword ptr [ebp - 0x58], xmm3
00534d9b movss xmm0, dword ptr [edi + 0x2f4]
00534da3 movaps xmm1, xmm2
00534da6 mulss xmm1, dword ptr [0xb6a974]
00534dae movaps xmm2, xmm3
00534db1 mulss xmm2, dword ptr [0xb6a974]
00534db9 mulss xmm1, xmm0
00534dbd mulss xmm2, xmm0
00534dc1 addss xmm1, dword ptr [edi + 0x2b8]
00534dc9 addss xmm2, dword ptr [edi + 0x2bc]
00534dd1 movss dword ptr [edi + 0x2b8], xmm1
00534dd9 movss dword ptr [edi + 0x2bc], xmm2
00534de1 call 0x6c3d90
00534de6 movd xmm0, eax
00534dea cvtdq2pd xmm0, xmm0
00534dee shr eax, 0x1f
00534df1 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
00534dfa cvtpd2ps xmm0, xmm0
00534dfe mulss xmm0, dword ptr [0xb6a19c]
00534e06 mulss xmm0, dword ptr [0xb6a8f4]
00534e0e addss xmm0, dword ptr [0xb6a8f4]
00534e16 movss dword ptr [ebp - 0x78], xmm0
00534e1b call 0x6c3d90
00534e20 mov esi, eax
00534e22 call 0x6c3d90
00534e27 movd xmm0, eax
00534e2b cvtdq2pd xmm0, xmm0
00534e2f shr eax, 0x1f
00534e32 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
00534e3b cvtpd2ps xmm0, xmm0
00534e3f mulss xmm0, dword ptr [0xb6a19c]
00534e47 mulss xmm0, dword ptr [0xb6aae4]
00534e4f subss xmm0, dword ptr [0xb6aa4c]
00534e57 mulss xmm0, dword ptr [0xb6a230]
00534e5f movss dword ptr [ebp - 0x70], xmm0
00534e64 call 0x411fe0
00534e69 movss dword ptr [ebp - 0x74], xmm0
00534e6e movss xmm0, dword ptr [ebp - 0x70]
00534e73 call 0x412010
00534e78 movss xmm4, dword ptr [ebp - 0x64]
00534e7d lea eax, [ebp - 0x88]
00534e83 movss xmm5, dword ptr [ebp - 0x58]
00534e88 movaps xmm2, xmm4
00534e8b mulss xmm2, dword ptr [ebp - 0x74]
00534e90 movaps xmm1, xmm5
00534e93 mov ecx, dword ptr [0xbfd65c]
00534e99 movss xmm3, dword ptr [ebp - 0x78]
00534e9e mulss xmm1, xmm0
00534ea2 push esi
00534ea3 push 0
00534ea5 push edi
00534ea6 subss xmm2, xmm1
00534eaa movaps xmm1, xmm4
00534ead mulss xmm4, dword ptr [0xb6a9c8]
00534eb5 push eax
00534eb6 mulss xmm1, xmm0
00534eba movaps xmm0, xmm5
00534ebd lea eax, [ebp - 0x6c]
00534ec0 mulss xmm0, dword ptr [ebp - 0x74]
00534ec5 push eax
00534ec6 mulss xmm5, dword ptr [0xb6a9c8]
00534ece push 1
00534ed0 addss xmm4, dword ptr [ebx]
00534ed4 addss xmm1, xmm0
00534ed8 movaps xmm0, xmm3
00534edb addss xmm5, dword ptr [ebx + 4]
00534ee0 mulss xmm0, xmm2
00534ee4 push 0x136
00534ee9 movss dword ptr [ebp - 0x6c], xmm4
00534eee mulss xmm3, xmm1
00534ef2 movss dword ptr [ebp - 0x88], xmm0
00534efa movss dword ptr [ebp - 0x68], xmm5
00534eff movss dword ptr [ebp - 0x84], xmm3
00534f07 call 0x422e20
00534f0c movss xmm0, dword ptr [eax + 0x2b8]
00534f14 mulss xmm0, dword ptr [0xb6a3b0]
00534f1c mov ecx, dword ptr [eax + 0x164]
00534f22 movss xmm1, dword ptr [eax + 0x2bc]
00534f2a and dword ptr [eax + 0x160], 0xfffffffb
00534f31 mulss xmm1, dword ptr [0xb6a3b0]
00534f39 mov dword ptr [eax + 0x164], ecx
00534f3f movss dword ptr [ebp - 0x60], xmm0
00534f44 movaps xmm0, xmmword ptr [0xb6c610]
00534f4b movups xmmword ptr [ebp - 0x54], xmm0
00534f4f mov dword ptr [ebp - 0x34], 0
00534f56 xorps xmm0, xmm0
00534f59 movss dword ptr [ebp - 0x5c], xmm1
00534f5e movups xmmword ptr [ebp - 0x44], xmm0
00534f62 mov dword ptr [ebp - 0x30], 0
00534f69 mov dword ptr [ebp - 0x2c], 0
00534f70 call 0x6c3d90
00534f75 mov ecx, dword ptr [0xbfd65c]
00534f7b push eax
00534f7c push 2
00534f7e push 0
00534f80 lea eax, [ebp - 0x60]
00534f83 push eax
00534f84 push ebx
00534f85 push 2
00534f87 push 0x3e8
00534f8c call 0x422e20
00534f91 push 1
00534f93 mov esi, eax
00534f95 lea eax, [ebp - 0x54]
00534f98 push 0
00534f9a push 0xff
00534f9f push -1
00534fa1 mov edx, dword ptr [esi]
00534fa3 mov ecx, esi
00534fa5 push eax
00534fa6 call dword ptr [edx + 0x38]
00534fa9 movss xmm2, dword ptr [ebp - 0x7c]
00534fae mov dword ptr [esi + 0xd0], 0
00534fb8 mov dword ptr [esi + 0xd4], 0xc0c00000
00534fc2 mov dword ptr [esi + 0x2b0], 0x3f800000
00534fcc mov ecx, dword ptr [edi + 0x30]
00534fcf mov edx, ecx
00534fd1 cmp ecx, 3
00534fd4 jb 0x534cc0
00534fda cmp edx, dword ptr [ebp - 0x80]
00534fdd jbe 0x535010
00534fdf mov eax, dword ptr [edi + 0x2c]
00534fe2 mov ecx, edi
00534fe4 push -1
00534fe6 push edx
00534fe7 push eax
00534fe8 push dword ptr [edi + 0x28]
00534feb mov dword ptr [edi + 0x2c], 0xffffffff
00534ff2 call 0x697c60
00534ff7 push 0
00534ff9 push 0xb401c8
00534ffe lea ecx, [edi + 0x3c]
00535001 mov dword ptr [edi + 0xab4], 0x10
0053500b call 0x405a00
00535010 cmp byte ptr [edi + 0x16b], 0
00535017 je 0x5351cd
0053501d lea eax, [ebp - 0x60]
00535020 push eax
00535021 call 0x659290
00535026 add esp, 4
00535029 call 0x6c3d90
0053502e movd xmm0, eax
00535032 cvtdq2pd xmm0, xmm0
00535036 shr eax, 0x1f
00535039 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
00535042 cvtpd2ps xmm1, xmm0
00535046 mulss xmm1, dword ptr [0xb6a19c]
0053504e addss xmm1, xmm1
00535052 addss xmm1, dword ptr [0xb6a7b0]
0053505a call 0x6c3d90
0053505f movss xmm3, dword ptr [ebp - 0x60]
00535064 movaps xmm0, xmm1
00535067 movss xmm2, dword ptr [ebp - 0x5c]
0053506c mov ecx, dword ptr [0xbfd65c]
00535072 push eax
00535073 push 0
00535075 mulss xmm0, xmm3
00535079 lea eax, [ebp - 0x60]
0053507c push edi
0053507d mulss xmm3, dword ptr [0xb6a9c8]
00535085 push eax
00535086 mulss xmm1, xmm2
0053508a lea eax, [ebp - 0x6c]
0053508d push eax
0053508e mulss xmm2, dword ptr [0xb6a9c8]
00535096 push 1
00535098 addss xmm3, dword ptr [edi + 0x294]
005350a0 push 0x136
005350a5 addss xmm2, dword ptr [edi + 0x298]
005350ad movss dword ptr [ebp - 0x60], xmm0
005350b2 movss dword ptr [ebp - 0x5c], xmm1
005350b7 movss dword ptr [ebp - 0x6c], xmm3
005350bc movss dword ptr [ebp - 0x68], xmm2
005350c1 call 0x422e20
005350c6 and dword ptr [eax + 0x160], 0xfffffffb
005350cd mov ecx, dword ptr [eax + 0x164]
005350d3 mov dword ptr [eax + 0x164], ecx
005350d9 movss xmm0, dword ptr [edi + 0x2d8]
005350e1 comiss xmm0, dword ptr [0xb6aef8]
005350e8 jbe 0x5351cd
005350ee call 0x6c3d90
005350f3 and eax, 1
005350f6 jne 0x5351cd
005350fc push -1
005350fe push eax
005350ff push eax
00535100 push 0xb
00535102 mov ecx, edi
00535104 call 0x697c60
00535109 push 0x3f
0053510b mov dword ptr [ebp - 0x40], 0
00535112 lea ecx, [ebp - 0x40]
00535115 push 0xb43418
0053511a mov dword ptr [ebp - 0x30], 0
00535121 mov dword ptr [ebp - 0x2c], 0xf
00535128 mov byte ptr [ebp - 0x40], 0
0053512c call 0x407c80
00535131 lea eax, [ebp - 0x40]
00535134 mov dword ptr [ebp - 4], 4
0053513b push eax
0053513c lea eax, [ebp - 0x28]
0053513f mov ecx, edi
00535141 push eax
00535142 call 0x691990
00535147 push eax
00535148 push 0
0053514a lea ecx, [edi + 0x3c]
0053514d mov byte ptr [ebp - 4], 5
00535151 call 0x407340
00535156 lea ecx, [ebp - 0x28]
00535159 call 0x407be0
0053515e mov dword ptr [ebp - 4], 0xffffffff
00535165 mov edx, dword ptr [ebp - 0x2c]
00535168 cmp edx, 0x10
0053516b jb 0x53519b
0053516d mov ecx, dword ptr [ebp - 0x40]
00535170 inc edx
00535171 mov eax, ecx
00535173 cmp edx, 0x1000
00535179 jb 0x535191
0053517b mov ecx, dword ptr [ecx - 4]
0053517e add edx, 0x23
00535181 sub eax, ecx
00535183 add eax, -4
00535186 cmp eax, 0x1f
00535189 jbe 0x535191
0053518b call dword ptr [0xa065ac]
00535191 push edx
00535192 push ecx
00535193 call 0x9eb08e
00535198 add esp, 8
0053519b push ecx
0053519c lea ecx, [edi + 0x3c]
0053519f call 0x4073a0
005351a4 mov byte ptr [edi + 0x16b], 0
005351ab call 0x6c3d90
005351b0 xor edx, edx
005351b2 mov ecx, 0x14
005351b7 div ecx
005351b9 mov eax, dword ptr [edi + 0x2dc]
005351bf add edx, ecx
005351c1 mov dword ptr [edi + 0x2d8], eax
005351c7 mov dword ptr [edi + 0xaf0], edx
005351cd mov ecx, dword ptr [ebp - 0xc]
005351d0 mov dword ptr fs:[0], ecx
005351d7 pop ecx
005351d8 pop edi
005351d9 pop esi
005351da pop ebx
005351db mov ecx, dword ptr [ebp - 0x10]
005351de xor ecx, ebp
005351e0 call 0x9eacd7
005351e5 mov esp, ebp
005351e7 pop ebp
005351e8 ret 
005351e9 int3 
005351ea int3 
005351eb int3 
005351ec int3 
005351ed int3 
005351ee int3 
005351ef int3 
005351f0 push ebx
005351f1 mov ebx, esp
005351f3 sub esp, 8
005351f6 and esp, 0xfffffff0
005351f9 add esp, 4
005351fc push ebp
005351fd mov ebp, dword ptr [ebx + 4]
00535200 mov dword ptr [esp + 4], ebp
00535204 mov ebp, esp
00535206 sub esp, 0x118
0053520c mov eax, dword ptr [0xbaa3b4]
00535211 xor eax, ebp
00535213 mov dword ptr [ebp - 4], eax
00535216 push esi
00535217 push edi
00535218 mov edi, ecx
0053521a mov eax, dword ptr [edi + 0xab4]
00535220 test eax, eax
00535222 je 0x5353c6
00535228 cmp eax, 4
0053522b jne 0x535509
00535231 movss xmm0, dword ptr [edi + 0x2c4]
00535239 lea eax, [ebp - 0xc0]
0053523f mulss xmm0, dword ptr [0xb6a5d8]
00535247 push ecx
00535248 mov dword ptr [esp], 0
0053524f push eax
00535250 movss dword ptr [edi + 0x2c4], xmm0
00535258 call 0x695a30
0053525d movss xmm1, dword ptr [eax]
00535261 subss xmm1, dword ptr [edi + 0x294]
00535269 movss xmm2, dword ptr [eax + 4]
0053526e subss xmm2, dword ptr [edi + 0x298]
00535276 movaps xmm0, xmm1
00535279 movss dword ptr [ebp - 0xb8], xmm1
00535281 mulss xmm0, xmm1
00535285 movaps xmm1, xmm2
00535288 movss dword ptr [ebp - 0xb4], xmm2
00535290 mulss xmm1, xmm2
00535294 addss xmm0, xmm1
00535298 call 0x4228c0
0053529d xorps xmm1, xmm1
005352a0 comiss xmm0, xmm1
005352a3 jbe 0x5352d9
005352a5 movss xmm1, dword ptr [0xb6a614]
005352ad divss xmm1, xmm0
005352b1 movss xmm0, dword ptr [ebp - 0xb8]
005352b9 mulss xmm0, xmm1
005352bd movss dword ptr [ebp - 0xb8], xmm0
005352c5 movss xmm0, dword ptr [ebp - 0xb4]
005352cd mulss xmm0, xmm1
005352d1 movss dword ptr [ebp - 0xb4], xmm0
005352d9 cmp dword ptr [edi + 0xe6c], -1
005352e0 je 0x53530c
005352e2 lea eax, [ebp - 0xc0]
005352e8 xorps xmm2, xmm2
005352eb push eax
005352ec mov ecx, edi
005352ee call 0x6af0c0
005352f3 movss xmm0, dword ptr [eax]
005352f7 movss dword ptr [ebp - 0xb8], xmm0
005352ff movss xmm0, dword ptr [eax + 4]
00535304 movss dword ptr [ebp - 0xb4], xmm0
0053530c call 0x6c3d90
00535311 xorps xmm0, xmm0
00535314 cvtsi2sd xmm0, eax
00535318 shr eax, 0x1f
0053531b addsd xmm0, qword ptr [eax*8 + 0xb6c940]
00535324 cvtpd2ps xmm0, xmm0
00535328 mulss xmm0, dword ptr [0xb6a19c]
00535330 mulss xmm0, dword ptr [0xb6a874]
00535338 addss xmm0, xmm0
0053533c movss dword ptr [ebp - 0xc4], xmm0
00535344 call 0x411fe0
00535349 movss dword ptr [ebp - 0xbc], xmm0
00535351 movss xmm0, dword ptr [ebp - 0xc4]
00535359 call 0x412010
0053535e movss xmm2, dword ptr [edi + 0x2f4]
00535366 movaps xmm3, xmm0
00535369 movss xmm0, dword ptr [ebp - 0xbc]
00535371 addss xmm3, xmm3
00535375 addss xmm0, xmm0
00535379 addss xmm3, dword ptr [ebp - 0xb4]
00535381 addss xmm0, dword ptr [ebp - 0xb8]
00535389 mulss xmm3, dword ptr [0xb6a304]
00535391 mulss xmm0, dword ptr [0xb6a304]
00535399 mulss xmm3, xmm2
0053539d mulss xmm0, xmm2
005353a1 addss xmm3, dword ptr [edi + 0x2bc]
005353a9 addss xmm0, dword ptr [edi + 0x2b8]
005353b1 movss dword ptr [edi + 0x2bc], xmm3
005353b9 movss dword ptr [edi + 0x2b8], xmm0
005353c1 jmp 0x535509
005353c6 mov esi, dword ptr [edi + 0x344]
005353cc movq xmm0, qword ptr [0xa08b0c]
005353d4 mov eax, dword ptr [0xa08b14]
005353d9 movq qword ptr [ebp - 0xcc], xmm0
005353e1 mov dword ptr [ebp - 0xb8], eax
005353e7 test esi, esi
005353e9 jne 0x5353fb
005353eb push 0xb4d6c4
005353f0 push 3
005353f2 call 0x95e330
005353f7 add esp, 8
005353fa int3 
005353fb mov ecx, dword ptr [ebp - 0xcc]
00535401 mov edx, esi
00535403 shr edx, cl
00535405 mov ecx, dword ptr [ebp - 0xc8]
0053540b xor edx, esi
0053540d mov eax, edx
0053540f shl eax, cl
00535411 mov ecx, dword ptr [ebp - 0xb8]
00535417 xor eax, edx
00535419 mov esi, eax
0053541b shr esi, cl
0053541d xor esi, eax
0053541f mov eax, 0xaaaaaaab
00535424 mul esi
00535426 mov eax, esi
00535428 shr edx, 2
0053542b lea ecx, [edx + edx*2]
0053542e add ecx, ecx
00535430 sub eax, ecx
00535432 mov ecx, dword ptr [eax*4 + 0xb42c68]
00535439 mov dword ptr [ebp - 0xb4], ecx
0053543f mov ecx, dword ptr [edi + 0x70]
00535442 test ecx, ecx
00535444 je 0x535493
00535446 cmp dword ptr [ecx + 0x14], 0x10
0053544a mov eax, ecx
0053544c jb 0x535450
0053544e mov eax, dword ptr [ecx]
00535450 mov ecx, dword ptr [ebp - 0xb4]
00535456 mov dl, byte ptr [eax]
00535458 cmp dl, byte ptr [ecx]
0053545a jne 0x535476
0053545c test dl, dl
0053545e je 0x535472
00535460 mov dl, byte ptr [eax + 1]
00535463 cmp dl, byte ptr [ecx + 1]
00535466 jne 0x535476
00535468 add eax, 2
0053546b add ecx, 2
0053546e test dl, dl
00535470 jne 0x535456
00535472 xor eax, eax
00535474 jmp 0x53547b
00535476 sbb eax, eax
00535478 or eax, 1
0053547b lea ecx, [edi + 0x3c]
0053547e test eax, eax
00535480 jne 0x535496
00535482 mov eax, dword ptr [ecx + 0x34]
00535485 cmp byte ptr [eax + 0x34], 0
00535489 je 0x5354b6
0053548b cmp byte ptr [ecx + 0x44], 0
0053548f jne 0x5354b6
00535491 jmp 0x535496
00535493 lea ecx, [edi + 0x3c]
00535496 push 1
00535498 push dword ptr [ebp - 0xb4]
0053549e call 0x405740
005354a3 test al, al
005354a5 je 0x5354b6
005354a7 lea ecx, [edi + 0x6c]
005354aa call 0x405330
005354af mov byte ptr [edi + 0x80], 1
005354b6 mov dword ptr [edi + 0xab4], 4
005354c0 test esi, esi
005354c2 jne 0x5354d4
005354c4 push 0xb4d6c4
005354c9 push 3
005354cb call 0x95e330
005354d0 add esp, 8
005354d3 int3 
005354d4 mov ecx, dword ptr [ebp - 0xcc]
005354da mov eax, esi
005354dc shr eax, cl
005354de mov ecx, dword ptr [ebp - 0xc8]
005354e4 xor eax, esi
005354e6 mov edx, eax
005354e8 mov byte ptr [edi + 0x16c], 1
005354ef shl edx, cl
005354f1 mov ecx, dword ptr [ebp - 0xb8]
005354f7 xor edx, eax
005354f9 mov eax, edx
005354fb shr eax, cl
005354fd xor al, dl
005354ff not al
00535501 and al, 1
00535503 mov byte ptr [edi + 0x13c], al
00535509 push 0
0053550b push 0xa
0053550d mov ecx, edi
0053550f call 0x684790
00535514 test al, al
00535516 je 0x53555a
00535518 call 0x6c3d90
0053551d push ecx
0053551e mov ecx, edi
00535520 movd xmm0, eax
00535524 cvtdq2pd xmm0, xmm0
00535528 shr eax, 0x1f
0053552b addsd xmm0, qword ptr [eax*8 + 0xb6c940]
00535534 cvtpd2ps xmm1, xmm0
00535538 mulss xmm1, dword ptr [0xb6a19c]
00535540 mulss xmm1, dword ptr [0xb6a434]
00535548 addss xmm1, dword ptr [0xb6a434]
00535550 movss dword ptr [esp], xmm1
00535555 call 0x68d7b0
0053555a push 0
0053555c push 6
0053555e mov ecx, edi
00535560 call 0x684790
00535565 movss xmm0, dword ptr [0xb6a3b0]
0053556d movaps xmmword ptr [ebp - 0xe0], xmm0
00535574 test al, al
00535576 je 0x535745
0053557c call 0x6c3d90
00535581 movd xmm0, eax
00535585 cvtdq2pd xmm0, xmm0
00535589 shr eax, 0x1f
0053558c addsd xmm0, qword ptr [eax*8 + 0xb6c940]
00535595 cvtpd2ps xmm0, xmm0
00535599 mulss xmm0, dword ptr [0xb6a19c]
005355a1 movss dword ptr [ebp - 0xb4], xmm0
005355a9 call 0x6c3d90
005355ae mov esi, eax
005355b0 call 0x6c3d90
005355b5 movd xmm0, eax
005355b9 cvtdq2pd xmm0, xmm0
005355bd shr eax, 0x1f
005355c0 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
005355c9 cvtpd2ps xmm0, xmm0
005355cd mulss xmm0, dword ptr [0xb6a19c]
005355d5 mulss xmm0, dword ptr [0xb6a874]
005355dd addss xmm0, xmm0
005355e1 movss dword ptr [ebp - 0xbc], xmm0
005355e9 call 0x411fe0
005355ee mulss xmm0, dword ptr [ebp - 0xb4]
005355f6 movss xmm1, dword ptr [edi + 0x2b8]
005355fe mulss xmm1, dword ptr [ebp - 0xe0]
00535606 mulss xmm0, dword ptr [0xb6a864]
0053560e addss xmm0, xmm1
00535612 movss dword ptr [ebp - 0xc8], xmm0
0053561a movss xmm0, dword ptr [ebp - 0xbc]
00535622 call 0x412010
00535627 mulss xmm0, dword ptr [ebp - 0xb4]
0053562f lea eax, [ebp - 0xc8]
00535635 mov ecx, dword ptr [0xbfd65c]
0053563b movss xmm1, dword ptr [edi + 0x2bc]
00535643 mulss xmm1, dword ptr [ebp - 0xe0]
0053564b push esi
0053564c mulss xmm0, dword ptr [0xb6a864]
00535654 push 0
00535656 push 0
00535658 push eax
00535659 lea eax, [edi + 0x294]
0053565f addss xmm0, xmm1
00535663 push eax
00535664 push 0x6f
00535666 push 0x3e8
0053566b movss dword ptr [ebp - 0xc4], xmm0
00535673 call 0x422e20
00535678 mov esi, eax
0053567a call 0x6c3d90
0053567f movss xmm2, dword ptr [0xb6a4c4]
00535687 movss xmm3, dword ptr [0xb6a480]
0053568f movd xmm0, eax
00535693 cvtdq2pd xmm0, xmm0
00535697 shr eax, 0x1f
0053569a addsd xmm0, qword ptr [eax*8 + 0xb6c940]
005356a3 cvtpd2ps xmm0, xmm0
005356a7 mulss xmm0, dword ptr [0xb6a19c]
005356af mulss xmm0, xmm2
005356b3 addss xmm0, xmm3
005356b7 movss dword ptr [esi + 0x140], xmm0
005356bf call 0x6c3d90
005356c4 movd xmm0, eax
005356c8 cvtdq2pd xmm0, xmm0
005356cc shr eax, 0x1f
005356cf addsd xmm0, qword ptr [eax*8 + 0xb6c940]
005356d8 cvtpd2ps xmm1, xmm0
005356dc mulss xmm1, dword ptr [0xb6a19c]
005356e4 mulss xmm1, xmm2
005356e8 addss xmm1, xmm2
005356ec movss xmm2, dword ptr [edi + 0xb88]
005356f4 movaps xmm0, xmm2
005356f7 mulss xmm2, dword ptr [0xbc7a2c]
005356ff mulss xmm0, dword ptr [0xbc7a28]
00535707 mov dword ptr [esi + 0x2a4], 0
00535711 mulss xmm2, xmm3
00535715 mov dword ptr [esi + 0x2a8], 0xc1b00000
0053571f mulss xmm0, xmm3
00535723 mov dword ptr [esi + 0x2ac], 0xfffffe70
0053572d mulss xmm2, xmm1
00535731 mulss xmm0, xmm1
00535735 movss dword ptr [esi + 0xdc], xmm2
0053573d movss dword ptr [esi + 0xd8], xmm0
00535745 mov eax, dword ptr [edi + 0xe6c]
0053574b cmp eax, -1
0053574e je 0x535764
00535750 push edi
00535751 push eax
00535752 push 9
00535754 call 0x8b10b0
00535759 test al, al
0053575b je 0x535764
0053575d mov eax, dword ptr [edi]
0053575f mov ecx, edi
00535761 call dword ptr [eax + 0x24]
00535764 cmp byte ptr [edi + 0x16b], 0
0053576b je 0x5358cc
00535771 mov ecx, edi
00535773 call 0x695680
00535778 mov esi, eax
0053577a movss xmm1, dword ptr [esi + 0x294]
00535782 movss xmm0, dword ptr [esi + 0x298]
0053578a subss xmm0, dword ptr [edi + 0x298]
00535792 subss xmm1, dword ptr [edi + 0x294]
0053579a mulss xmm0, xmm0
0053579e mulss xmm1, xmm1
005357a2 addss xmm0, xmm1
005357a6 call 0x4228c0
005357ab movss xmm2, dword ptr [esi + 0x2b8]
005357b3 movaps xmm1, xmm0
005357b6 movss xmm3, dword ptr [esi + 0x2bc]
005357be mulss xmm2, dword ptr [0xb6a2cc]
005357c6 mulss xmm3, dword ptr [0xb6a2cc]
005357ce mulss xmm2, xmm1
005357d2 mulss xmm3, xmm1
005357d6 addss xmm2, dword ptr [esi + 0x294]
005357de addss xmm3, dword ptr [esi + 0x298]
005357e6 subss xmm2, dword ptr [edi + 0x294]
005357ee subss xmm3, dword ptr [edi + 0x298]
005357f6 movaps xmm0, xmm2
005357f9 movss dword ptr [ebp - 0xb4], xmm2
00535801 mulss xmm0, xmm2
00535805 movaps xmm1, xmm3
00535808 movss dword ptr [ebp - 0xb8], xmm3
00535810 mulss xmm1, xmm3
00535814 addss xmm0, xmm1
00535818 call 0x4228c0
0053581d movss xmm1, dword ptr [ebp - 0xb4]
00535825 xorps xmm4, xmm4
00535828 comiss xmm0, xmm4
0053582b movss xmm2, dword ptr [ebp - 0xb8]
00535833 jbe 0x53584c
00535835 movss xmm3, dword ptr [0xb6a614]
0053583d divss xmm3, xmm0
00535841 movaps xmm0, xmm3
00535844 mulss xmm2, xmm3
00535848 mulss xmm1, xmm0
0053584c mulss xmm1, dword ptr [0xb6a974]
00535854 lea ecx, [ebp - 0xb0]
0053585a mulss xmm2, dword ptr [0xb6a974]
00535862 movss dword ptr [ebp - 0xc0], xmm1
0053586a movss dword ptr [ebp - 0xbc], xmm2
00535872 call 0x430d70
00535877 movaps xmm0, xmmword ptr [0xb6c610]
0053587e xorps xmm1, xmm1
00535881 mov dword ptr [ebp - 0xe4], 0
0053588b mov ecx, edi
0053588d mov eax, dword ptr [ebp - 0xe4]
00535893 mov dword ptr [ebp - 0x5c], eax
00535896 lea eax, [ebp - 0xb0]
0053589c push eax
0053589d push 0
0053589f movups xmmword ptr [ebp - 0x84], xmm0
005358a6 lea eax, [ebp - 0xc0]
005358ac movaps xmm0, xmmword ptr [ebp - 0xe0]
005358b3 push eax
005358b4 lea eax, [edi + 0x294]
005358ba unpcklps xmm0, xmm4
005358bd push eax
005358be movups xmmword ptr [ebp - 0x74], xmm1
005358c2 movq qword ptr [ebp - 0x64], xmm0
005358c7 call 0x6a1a20
005358cc mov ecx, dword ptr [ebp - 4]
005358cf pop edi
005358d0 xor ecx, ebp
005358d2 pop esi
005358d3 call 0x9eacd7
005358d8 mov esp, ebp
005358da pop ebp
005358db mov esp, ebx
005358dd pop ebx
005358de ret 
005358df int3 
005358e0 push ebp
005358e1 mov ebp, esp
005358e3 sub esp, 0x20
005358e6 movss xmm1, dword ptr [0xb6afc0]
005358ee or ecx, 0xffffffff
005358f1 push ebx
005358f2 mov ebx, dword ptr [0xbfd65c]
005358f8 push esi
005358f9 push edi
005358fa xor edi, edi
005358fc mov dword ptr [ebp - 0x20], ecx
005358ff mov ebx, dword ptr [ebx + 0x18190]
00535905 movss dword ptr [ebp - 0x18], xmm1
0053590a mov dword ptr [ebp - 0x1c], edi
0053590d mov esi, dword ptr [ebx + 0xc]
00535910 mov eax, esi
00535912 imul eax, dword ptr [ebx + 0x10]
00535916 test eax, eax
00535918 jle 0x535c4f
0053591e movss xmm1, dword ptr [0xb6aa3c]
00535926 lea eax, [ebx + 0xe6c]
0053592c lea edx, [ebx + 0x24]
0053592f mov dword ptr [ebp - 0x14], eax
00535932 mov dword ptr [ebp - 0x10], edx
00535935 nop word ptr [eax + eax]
00535940 cmp edi, 0x1bf
00535946 ja 0x535c20
0053594c mov edx, dword ptr [edx]
0053594e test edx, edx
00535950 je 0x535c20
00535956 cmp dword ptr [edx + 4], 7
0053595a jne 0x535c20
00535960 cmp dword ptr [edx + 0xc], 0
00535964 jne 0x535c20
0053596a movzx eax, word ptr [eax]
0053596d test ax, ax
00535970 jne 0x535c20
00535976 mov eax, dword ptr [0xbfd65c]
0053597b mov eax, dword ptr [eax + 0x18190]
00535981 mov ecx, dword ptr [eax + 0xc]
00535984 mov eax, dword ptr [edx + 0x24]
00535987 cdq 
00535988 idiv ecx
0053598a movd xmm0, edx
0053598e cvtdq2ps xmm0, xmm0
00535991 movd xmm2, eax
00535995 mov eax, dword ptr [ebp + 0xc]
00535998 cvtdq2ps xmm2, xmm2
0053599b mulss xmm0, xmm1
0053599f mulss xmm2, xmm1
005359a3 addss xmm0, xmm1
005359a7 addss xmm2, dword ptr [0xb6ab20]
005359af movaps xmm1, xmm0
005359b2 movss dword ptr [ebp - 8], xmm0
005359b7 subss xmm1, dword ptr [eax]
005359bb movaps xmm0, xmm2
005359be movss dword ptr [ebp - 0xc], xmm2
005359c3 subss xmm0, dword ptr [eax + 4]
005359c8 mulss xmm1, xmm1
005359cc mulss xmm0, xmm0
005359d0 addss xmm0, xmm1
005359d4 call 0x4228c0
005359d9 mov eax, dword ptr [ebp + 8]
005359dc movss xmm1, dword ptr [ebp - 8]
005359e1 movss dword ptr [ebp - 4], xmm0
005359e6 movss xmm0, dword ptr [ebp - 0xc]
005359eb subss xmm0, dword ptr [eax + 4]
005359f0 subss xmm1, dword ptr [eax]
005359f4 mulss xmm0, xmm0
005359f8 mulss xmm1, xmm1
005359fc addss xmm0, xmm1
00535a00 call 0x4228c0
00535a05 movss xmm2, dword ptr [0xb6acec]
00535a0d mov eax, dword ptr [ebp + 0x10]
00535a10 movaps xmm1, xmm2
00535a13 subss xmm1, xmm0
00535a17 test eax, eax
00535a19 js 0x535c0a
00535a1f movss xmm0, dword ptr [ebp - 4]
00535a24 movss xmm3, dword ptr [0xb6aa8c]
00535a2c comiss xmm3, xmm0
00535a2f ja 0x535c18
00535a35 mulss xmm0, dword ptr [0xb6a864]
00535a3d subss xmm1, xmm0
00535a41 movss dword ptr [ebp - 4], xmm1
00535a46 movaps xmm0, xmm1
00535a49 cmp eax, edi
00535a4b jne 0x535a56
00535a4d subss xmm0, xmm2
00535a51 movss dword ptr [ebp - 4], xmm0
00535a56 movss xmm2, dword ptr [0xb6aa3c]
00535a5e xorps xmm3, xmm3
00535a61 movss xmm0, dword ptr [ebp - 8]
00535a66 movss xmm1, dword ptr [ebp - 0xc]
00535a6b addss xmm0, xmm2
00535a6f addss xmm1, xmm3
00535a73 subss xmm0, xmm2
00535a77 subss xmm1, dword ptr [0xb6ab20]
00535a7f divss xmm0, xmm2
00535a83 divss xmm1, xmm2
00535a87 addss xmm0, dword ptr [0xb6a480]
00535a8f addss xmm1, dword ptr [0xb6a480]
00535a97 cvttss2si ecx, xmm0
00535a9b cvttss2si edi, xmm1
00535a9f test ecx, ecx
00535aa1 js 0x535ab9
00535aa3 cmp ecx, esi
00535aa5 jge 0x535ab9
00535aa7 test edi, edi
00535aa9 js 0x535ab9
00535aab cmp edi, dword ptr [ebx + 0x10]
00535aae jge 0x535ab9
00535ab0 mov eax, esi
00535ab2 imul eax, edi
00535ab5 add eax, ecx
00535ab7 jmp 0x535abf
00535ab9 mov esi, dword ptr [ebx + 0xc]
00535abc or eax, 0xffffffff
00535abf push eax
00535ac0 mov ecx, ebx
00535ac2 call 0x7aeec0
00535ac7 cmp eax, 1
00535aca jne 0x535bd1
00535ad0 movss xmm1, dword ptr [0xb6aa3c]
00535ad8 movss xmm0, dword ptr [ebp - 8]
00535add subss xmm0, xmm1
00535ae1 subss xmm0, xmm1
00535ae5 divss xmm0, xmm1
00535ae9 addss xmm0, dword ptr [0xb6a480]
00535af1 cvttss2si eax, xmm0
00535af5 test eax, eax
00535af7 js 0x535b0d
00535af9 cmp eax, esi
00535afb jge 0x535b0d
00535afd test edi, edi
00535aff js 0x535b0d
00535b01 cmp edi, dword ptr [ebx + 0x10]
00535b04 jge 0x535b0d
00535b06 imul edi, esi
00535b09 add eax, edi
00535b0b jmp 0x535b10
00535b0d or eax, 0xffffffff
00535b10 push eax
00535b11 mov ecx, ebx
00535b13 call 0x7aeec0
00535b18 cmp eax, 1
00535b1b jne 0x535bd1
00535b21 movss xmm0, dword ptr [ebp - 8]
00535b26 xorps xmm1, xmm1
00535b29 movss xmm2, dword ptr [0xb6aa3c]
00535b31 addss xmm0, xmm1
00535b35 movss xmm1, dword ptr [ebp - 0xc]
00535b3a addss xmm1, xmm2
00535b3e subss xmm0, xmm2
00535b42 subss xmm1, dword ptr [0xb6ab20]
00535b4a divss xmm0, xmm2
00535b4e divss xmm1, xmm2
00535b52 addss xmm0, dword ptr [0xb6a480]
00535b5a addss xmm1, dword ptr [0xb6a480]
00535b62 cvttss2si ecx, xmm0
00535b66 cvttss2si edi, xmm1
00535b6a mov dword ptr [ebp - 0xc], ecx
00535b6d test ecx, ecx
00535b6f js 0x535b87
00535b71 cmp ecx, esi
00535b73 jge 0x535b87
00535b75 test edi, edi
00535b77 js 0x535b87
00535b79 cmp edi, dword ptr [ebx + 0x10]
00535b7c jge 0x535b87
00535b7e mov eax, edi
00535b80 imul eax, esi
00535b83 add eax, ecx
00535b85 jmp 0x535b8a
00535b87 or eax, 0xffffffff
00535b8a push eax
00535b8b mov ecx, ebx
00535b8d call 0x7aeec0
00535b92 cmp eax, 1
00535b95 jne 0x535bd1
00535b97 mov eax, dword ptr [ebp - 0xc]
00535b9a test eax, eax
00535b9c js 0x535bb2
00535b9e cmp eax, esi
00535ba0 jge 0x535bb2
00535ba2 test edi, edi
00535ba4 js 0x535bb2
00535ba6 cmp edi, dword ptr [ebx + 0x10]
00535ba9 jge 0x535bb2
00535bab imul edi, esi
00535bae add eax, edi
00535bb0 jmp 0x535bb5
00535bb2 or eax, 0xffffffff
00535bb5 push eax
00535bb6 mov ecx, ebx
00535bb8 call 0x7aeec0
00535bbd movss xmm2, dword ptr [ebp - 4]
00535bc2 cmp eax, 1
00535bc5 jne 0x535bd6
00535bc7 addss xmm2, dword ptr [0xb6aba8]
00535bcf jmp 0x535bd6
00535bd1 movss xmm2, dword ptr [ebp - 4]
00535bd6 call 0x6c3d90
00535bdb mov edi, dword ptr [ebp - 0x1c]
00535bde movd xmm0, eax
00535be2 cvtdq2pd xmm0, xmm0
00535be6 shr eax, 0x1f
00535be9 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
00535bf2 cvtpd2ps xmm1, xmm0
00535bf6 mulss xmm1, dword ptr [0xb6a19c]
00535bfe mulss xmm1, dword ptr [0xb6ac8c]
00535c06 addss xmm1, xmm2
00535c0a comiss xmm1, dword ptr [ebp - 0x18]
00535c0e jbe 0x535c18
00535c10 movss dword ptr [ebp - 0x18], xmm1
00535c15 mov dword ptr [ebp - 0x20], edi
00535c18 movss xmm1, dword ptr [0xb6aa3c]
00535c20 mov esi, dword ptr [ebx + 0xc]
00535c23 inc edi
00535c24 add dword ptr [ebp - 0x10], 4
00535c28 mov ecx, esi
00535c2a imul ecx, dword ptr [ebx + 0x10]
00535c2e add dword ptr [ebp - 0x14], 2
00535c32 mov edx, dword ptr [ebp - 0x10]
00535c35 mov eax, dword ptr [ebp - 0x14]
00535c38 mov dword ptr [ebp - 0x1c], edi
00535c3b cmp edi, ecx
00535c3d jl 0x535940
00535c43 mov eax, dword ptr [ebp - 0x20]
00535c46 pop edi
00535c47 pop esi
00535c48 pop ebx
00535c49 mov esp, ebp
00535c4b pop ebp
00535c4c ret 0xc
00535c4f pop edi
00535c50 pop esi
00535c51 mov eax, ecx
00535c53 pop ebx
00535c54 mov esp, ebp
00535c56 pop ebp
00535c57 ret 0xc
00535c5a int3 
00535c5b int3 
00535c5c int3 
00535c5d int3 
00535c5e int3 
00535c5f int3 
00535c60 int3 
00535c61 int3 
00535c62 int3 
00535c63 int3 
00535c64 int3 
00535c65 int3 
00535c66 int3 
00535c67 int3 
00535c68 int3 
00535c69 int3 
00535c6a int3 
00535c6b int3 
00535c6c int3 
00535c6d int3 
00535c6e int3 
00535c6f int3 
