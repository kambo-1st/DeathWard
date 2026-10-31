005054e0 push ebp
005054e1 mov ebp, esp
005054e3 and esp, 0xfffffff8
005054e6 sub esp, 0x154
005054ec mov eax, dword ptr [0xbaa3b4]
005054f1 xor eax, esp
005054f3 mov dword ptr [esp + 0x150], eax
005054fa push ebx
005054fb mov ebx, ecx
005054fd push esi
005054fe push edi
005054ff cmp dword ptr [ebx + 0xab4], 0
00505506 jne 0x505686
0050550c mov eax, dword ptr [0xbfd65c]
00505511 mov eax, dword ptr [eax + 0x243624]
00505517 cmp eax, 1
0050551a je 0x50552b
0050551c cmp eax, 3
0050551f je 0x50552b
00505521 movss xmm2, dword ptr [0xb6a928]
00505529 jmp 0x505577
0050552b movss xmm1, dword ptr [ebx + 0x2dc]
00505533 mulss xmm1, dword ptr [0xb6a560]
0050553b call 0x6c3d90
00505540 xorps xmm0, xmm0
00505543 cvtsi2sd xmm0, eax
00505547 shr eax, 0x1f
0050554a addsd xmm0, qword ptr [eax*8 + 0xb6c940]
00505553 cvtpd2ps xmm2, xmm0
00505557 movss xmm0, dword ptr [0xb6a928]
0050555f mulss xmm2, dword ptr [0xb6a19c]
00505567 maxss xmm1, xmm0
0050556b subss xmm1, xmm0
0050556f mulss xmm2, xmm1
00505573 addss xmm2, xmm0
00505577 movss dword ptr [ebx + 0x2d8], xmm2
0050557f mov dword ptr [ebx + 0xb00], 0
00505589 mov eax, dword ptr [ebx + 0x294]
0050558f mov dword ptr [ebx + 0x28c], eax
00505595 mov eax, dword ptr [ebx + 0x298]
0050559b mov dword ptr [ebx + 0x290], eax
005055a1 mov eax, dword ptr [ebx + 0x2c]
005055a4 mov dword ptr [ebx + 0xab4], 3
005055ae cmp eax, 1
005055b1 jne 0x505615
005055b3 movaps xmm1, xmmword ptr [0xb6c0b0]
005055ba lea eax, [esp + 0x2c]
005055be add ebx, 0x1dc
005055c4 mov dword ptr [esp + 0x4c], 0
005055cc mov dword ptr [esp + 0x50], 0x3f000000
005055d4 xorps xmm0, xmm0
005055d7 mov dword ptr [esp + 0x54], 0
005055df cmp ebx, eax
005055e1 je 0x506118
005055e7 mov eax, dword ptr [esp + 0x54]
005055eb movups xmmword ptr [ebx + 0x10], xmm0
005055ef movq xmm0, qword ptr [esp + 0x4c]
005055f5 movq qword ptr [ebx + 0x20], xmm0
005055fa movups xmmword ptr [ebx], xmm1
005055fd mov dword ptr [ebx + 0x28], eax
00505600 pop edi
00505601 pop esi
00505602 pop ebx
00505603 mov ecx, dword ptr [esp + 0x150]
0050560a xor ecx, esp
0050560c call 0x9eacd7
00505611 mov esp, ebp
00505613 pop ebp
00505614 ret 
00505615 cmp eax, 2
00505618 jne 0x506118
0050561e movaps xmm2, xmmword ptr [0xb6bd30]
00505625 lea eax, [esp + 0x58]
00505629 add ebx, 0x1dc
0050562f mov dword ptr [esp + 0x78], 0x3f800000
00505637 mov dword ptr [esp + 0x7c], 0x3f800000
0050563f xorps xmm1, xmm1
00505642 mov dword ptr [esp + 0x80], 0x3f800000
0050564d cmp ebx, eax
0050564f je 0x506118
00505655 movq xmm0, qword ptr [esp + 0x78]
0050565b mov eax, dword ptr [esp + 0x80]
00505662 movq qword ptr [ebx + 0x20], xmm0
00505667 movups xmmword ptr [ebx], xmm2
0050566a mov dword ptr [ebx + 0x28], eax
0050566d movups xmmword ptr [ebx + 0x10], xmm1
00505671 pop edi
00505672 pop esi
00505673 pop ebx
00505674 mov ecx, dword ptr [esp + 0x150]
0050567b xor ecx, esp
0050567d call 0x9eacd7
00505682 mov esp, ebp
00505684 pop ebp
00505685 ret 
00505686 movss xmm0, dword ptr [ebx + 0x2c4]
0050568e xorps xmm1, xmm1
00505691 mulss xmm0, dword ptr [0xb6a560]
00505699 movss dword ptr [ebx + 0x2c4], xmm0
005056a1 movss xmm0, dword ptr [ebx + 0x14]
005056a6 comiss xmm0, xmm1
005056a9 jbe 0x505711
005056ab mov eax, dword ptr [ebx + 8]
005056ae xorps xmm0, xmm0
005056b1 cmp eax, dword ptr [ebx + 0xc]
005056b4 je 0x505711
005056b6 mov ecx, dword ptr [eax + 0xc]
005056b9 mov edx, dword ptr [eax + 8]
005056bc mov dword ptr [esp + 0x14], ecx
005056c0 mov ecx, edx
005056c2 and ecx, 4
005056c5 or ecx, 0
005056c8 je 0x5056f6
005056ca mov ecx, dword ptr [eax + 0x30]
005056cd shr ecx, 1
005056cf test cl, 1
005056d2 jne 0x5056f6
005056d4 cmp dword ptr [eax + 0x10], 1
005056d8 je 0x5056f6
005056da mov ecx, dword ptr [eax + 0x18]
005056dd cmp ecx, 1
005056e0 je 0x5056f6
005056e2 cmp ecx, 3
005056e5 je 0x5056f6
005056e7 and edx, 0x1000
005056ed or edx, 0
005056f0 jne 0x5056f6
005056f2 mov dword ptr [eax], edx
005056f4 jmp 0x5056fa
005056f6 addss xmm0, dword ptr [eax]
005056fa add eax, 0x38
005056fd cmp eax, dword ptr [ebx + 0xc]
00505700 jne 0x5056b6
00505702 comiss xmm0, xmm1
00505705 jbe 0x505711
00505707 mov dword ptr [ebx + 0xb00], 0
00505711 mov ecx, ebx
00505713 call 0x695680
00505718 movss xmm1, dword ptr [eax + 0x294]
00505720 movss xmm0, dword ptr [eax + 0x298]
00505728 subss xmm0, dword ptr [ebx + 0x298]
00505730 subss xmm1, dword ptr [ebx + 0x294]
00505738 mulss xmm0, xmm0
0050573c mulss xmm1, xmm1
00505740 addss xmm0, xmm1
00505744 call 0x4228c0
00505749 movss xmm1, dword ptr [ebx + 0x2d8]
00505751 lea edx, [ebx + 0x2dc]
00505757 movss xmm6, dword ptr [edx]
0050575b movaps xmm2, xmm0
0050575e comiss xmm1, xmm6
00505761 movss dword ptr [esp + 0x1c], xmm2
00505767 jb 0x505f95
0050576d mov ecx, dword ptr [ebx + 0xab4]
00505773 cmp ecx, 3
00505776 jne 0x505884
0050577c mov eax, dword ptr [ebx + 0x160]
00505782 and eax, 0x1000a00
00505787 or eax, 0
0050578a jne 0x505884
00505790 cmp dword ptr [ebx + 0xe6c], -1
00505797 je 0x5057b1
00505799 movss xmm1, dword ptr [0xb6accc]
005057a1 mov ecx, ebx
005057a3 push 7
005057a5 push eax
005057a6 call 0x6a15a0
005057ab mov byte ptr [esp + 0xf], al
005057af jmp 0x5057e5
005057b1 call 0x6c3d90
005057b6 xor edx, edx
005057b8 mov ecx, 0x32
005057bd div ecx
005057bf test edx, edx
005057c1 jne 0x5057e0
005057c3 movss xmm0, dword ptr [0xb6abd0]
005057cb comiss xmm0, xmm2
005057ce ja 0x5057d9
005057d0 call 0x6c3d90
005057d5 test al, 3
005057d7 jne 0x5057e0
005057d9 mov byte ptr [esp + 0xf], 1
005057de jmp 0x5057e5
005057e0 mov byte ptr [esp + 0xf], 0
005057e5 mov eax, dword ptr [ebx + 0xe6c]
005057eb cmp eax, -1
005057ee je 0x5057fd
005057f0 push ebx
005057f1 push eax
005057f2 push 0xa
005057f4 call 0x8b10b0
005057f9 test al, al
005057fb jne 0x505821
005057fd cmp byte ptr [esp + 0xf], 0
00505802 je 0x505840
00505804 cmp dword ptr [ebx + 0x2c], 2
00505808 jne 0x50582d
0050580a mov ecx, ebx
0050580c call 0x6ad7a0
00505811 cmp eax, 8
00505814 jge 0x505821
00505816 mov ecx, eax
00505818 call 0x659230
0050581d test eax, eax
0050581f je 0x50582d
00505821 mov dword ptr [ebx + 0xab4], 9
0050582b jmp 0x505840
0050582d push 1
0050582f mov ecx, ebx
00505831 mov dword ptr [ebx + 0xab4], 8
0050583b call 0x6afe20
00505840 push 1
00505842 push 0xb41e70
00505847 lea ecx, [ebx + 0x3c]
0050584a call 0x405740
0050584f test al, al
00505851 je 0x5060e8
00505857 mov eax, dword ptr [ebx + 0x70]
0050585a test eax, eax
0050585c je 0x5060e8
00505862 lea ecx, [ebx + 0x6c]
00505865 xorps xmm1, xmm1
00505868 call 0x403c00
0050586d mov eax, dword ptr [ebx + 0x70]
00505870 test eax, eax
00505872 je 0x5060e8
00505878 mov byte ptr [ebx + 0x80], 0
0050587f jmp 0x5060e8
00505884 mov edi, dword ptr [ebx + 0x70]
00505887 cmp ecx, 8
0050588a jne 0x505f25
00505890 test edi, edi
00505892 je 0x5058d9
00505894 cmp dword ptr [edi + 0x14], 0x10
00505898 mov eax, edi
0050589a jb 0x50589e
0050589c mov eax, dword ptr [edi]
0050589e mov ecx, 0xb400ac
005058a3 mov dl, byte ptr [eax]
005058a5 cmp dl, byte ptr [ecx]
005058a7 jne 0x5058c3
005058a9 test dl, dl
005058ab je 0x5058bf
005058ad mov dl, byte ptr [eax + 1]
005058b0 cmp dl, byte ptr [ecx + 1]
005058b3 jne 0x5058c3
005058b5 add eax, 2
005058b8 add ecx, 2
005058bb test dl, dl
005058bd jne 0x5058a3
005058bf xor eax, eax
005058c1 jmp 0x5058c8
005058c3 sbb eax, eax
005058c5 or eax, 1
005058c8 test eax, eax
005058ca jne 0x5058d9
005058cc cmp byte ptr [edi + 0x34], al
005058cf je 0x5058fb
005058d1 cmp byte ptr [ebx + 0x80], al
005058d7 jne 0x5058fb
005058d9 push 1
005058db push 0xb400ac
005058e0 lea ecx, [ebx + 0x3c]
005058e3 call 0x405740
005058e8 test al, al
005058ea je 0x5058fb
005058ec lea ecx, [ebx + 0x6c]
005058ef call 0x405330
005058f4 mov byte ptr [ebx + 0x80], 1
005058fb cmp dword ptr [ebx + 0xe6c], -1
00505902 jne 0x50591e
00505904 movss xmm0, dword ptr [0xc02fec]
0050590c movss dword ptr [ebx + 0xe70], xmm0
00505914 movss xmm0, dword ptr [0xc02ff0]
0050591c jmp 0x505960
0050591e movss xmm2, dword ptr [0xb6a2cc]
00505926 lea eax, [esp + 0x10]
0050592a push eax
0050592b mov ecx, ebx
0050592d call 0x6af380
00505932 movss xmm1, dword ptr [esp + 0x10]
00505938 ucomiss xmm1, dword ptr [0xc02fec]
0050593f movss xmm0, dword ptr [esp + 0x14]
00505945 lahf 
00505946 test ah, 0x44
00505949 jp 0x505958
0050594b ucomiss xmm0, dword ptr [0xc02ff0]
00505952 lahf 
00505953 test ah, 0x44
00505956 jnp 0x505968
00505958 movss dword ptr [ebx + 0xe70], xmm1
00505960 movss dword ptr [ebx + 0xe74], xmm0
00505968 cmp dword ptr [ebx + 0x70], 0
0050596c je 0x5060de
00505972 push 0xb400ac
00505977 lea ecx, [ebx + 0x6c]
0050597a call 0x405e90
0050597f test al, al
00505981 je 0x505f09
00505987 call 0x6c3d90
0050598c movd xmm0, eax
00505990 cvtdq2pd xmm0, xmm0
00505994 shr eax, 0x1f
00505997 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
005059a0 cvtpd2ps xmm1, xmm0
005059a4 movss xmm0, dword ptr [0xb6abec]
005059ac mulss xmm1, dword ptr [0xb6a19c]
005059b4 mulss xmm1, dword ptr [0xb6a9c8]
005059bc subss xmm0, xmm1
005059c0 comiss xmm0, dword ptr [esp + 0x1c]
005059c5 jbe 0x5059d2
005059c7 cmp dword ptr [ebx + 0x34], 0x24
005059cb mov byte ptr [esp + 0xf], 1
005059d0 jne 0x5059d7
005059d2 mov byte ptr [esp + 0xf], 0
005059d7 mov eax, dword ptr [ebx + 0x2c]
005059da push ecx
005059db mov dword ptr [esp], 0x3f800000
005059e2 push 0
005059e4 push 2
005059e6 push ecx
005059e7 mov ecx, ebx
005059e9 test eax, eax
005059eb jne 0x505aed
005059f1 mov dword ptr [esp], 0x3f800000
005059f8 push 0xb2
005059fd call 0x6ad720
00505a02 cmp byte ptr [esp + 0xf], 0
00505a07 je 0x505a36
00505a09 mov ecx, ebx
00505a0b call 0x695680
00505a10 movss xmm3, dword ptr [0xc02ff0]
00505a18 movss xmm4, dword ptr [0xc02fec]
00505a20 mov ecx, dword ptr [eax + 0x294]
00505a26 mov eax, dword ptr [eax + 0x298]
00505a2c mov dword ptr [esp + 0x10], ecx
00505a30 mov dword ptr [esp + 0x14], eax
00505a34 jmp 0x505a52
00505a36 movss xmm4, dword ptr [0xc02fec]
00505a3e movss xmm3, dword ptr [0xc02ff0]
00505a46 movss dword ptr [esp + 0x10], xmm4
00505a4c movss dword ptr [esp + 0x14], xmm3
00505a52 movss xmm0, dword ptr [ebx + 0xe70]
00505a5a lea eax, [esp + 0x10]
00505a5e movss xmm1, dword ptr [eax]
00505a62 movss xmm2, dword ptr [eax + 4]
00505a67 ucomiss xmm0, xmm4
00505a6a movss dword ptr [esp + 0x1c], xmm1
00505a70 movss dword ptr [esp + 0x20], xmm2
00505a76 lahf 
00505a77 test ah, 0x44
00505a7a jp 0x505a8d
00505a7c movss xmm0, dword ptr [ebx + 0xe74]
00505a84 ucomiss xmm0, xmm3
00505a87 lahf 
00505a88 test ah, 0x44
00505a8b jnp 0x505ab9
00505a8d mulss xmm1, dword ptr [0xb6aafc]
00505a95 mulss xmm2, dword ptr [0xb6aafc]
00505a9d addss xmm1, dword ptr [ebx + 0x294]
00505aa5 addss xmm2, dword ptr [ebx + 0x298]
00505aad movss dword ptr [esp + 0x1c], xmm1
00505ab3 movss dword ptr [esp + 0x20], xmm2
00505ab9 call 0x6c3d90
00505abe mov esi, eax
00505ac0 lea ecx, [esp + 0xb0]
00505ac7 and esi, 1
00505aca call 0x430d70
00505acf push eax
00505ad0 push ecx
00505ad1 mov dword ptr [esp], 0x41200000
00505ad8 lea eax, [esp + 0x24]
00505adc push eax
00505add lea eax, [esi + 3]
00505ae0 mov ecx, ebx
00505ae2 push eax
00505ae3 call 0x6a3420
00505ae8 jmp 0x505f09
00505aed cmp eax, 1
00505af0 jne 0x505cf2
00505af6 mov dword ptr [esp], 0x3f333333
00505afd push 0xd5
00505b02 call 0x6ad720
00505b07 cmp byte ptr [esp + 0xf], 0
00505b0c mov dword ptr [ebx + 0xaf0], 0xffffffce
00505b16 je 0x505b45
00505b18 mov ecx, ebx
00505b1a call 0x695680
00505b1f movss xmm3, dword ptr [0xc02ff0]
00505b27 movss xmm4, dword ptr [0xc02fec]
00505b2f mov ecx, dword ptr [eax + 0x294]
00505b35 mov eax, dword ptr [eax + 0x298]
00505b3b mov dword ptr [esp + 0x10], ecx
00505b3f mov dword ptr [esp + 0x14], eax
00505b43 jmp 0x505b61
00505b45 movss xmm4, dword ptr [0xc02fec]
00505b4d movss xmm3, dword ptr [0xc02ff0]
00505b55 movss dword ptr [esp + 0x10], xmm4
00505b5b movss dword ptr [esp + 0x14], xmm3
00505b61 movss xmm0, dword ptr [ebx + 0xe70]
00505b69 lea eax, [esp + 0x10]
00505b6d movss xmm1, dword ptr [eax]
00505b71 movss xmm2, dword ptr [eax + 4]
00505b76 ucomiss xmm0, xmm4
00505b79 movss dword ptr [esp + 0x1c], xmm1
00505b7f movss dword ptr [esp + 0x20], xmm2
00505b85 lahf 
00505b86 test ah, 0x44
00505b89 jp 0x505b9c
00505b8b movss xmm0, dword ptr [ebx + 0xe74]
00505b93 ucomiss xmm0, xmm3
00505b96 lahf 
00505b97 test ah, 0x44
00505b9a jnp 0x505bc8
00505b9c mulss xmm1, dword ptr [0xb6aafc]
00505ba4 mulss xmm2, dword ptr [0xb6aafc]
00505bac addss xmm1, dword ptr [ebx + 0x294]
00505bb4 addss xmm2, dword ptr [ebx + 0x298]
00505bbc movss dword ptr [esp + 0x1c], xmm1
00505bc2 movss dword ptr [esp + 0x20], xmm2
00505bc8 lea ecx, [esp + 0xb0]
00505bcf call 0x430d70
00505bd4 push eax
00505bd5 push ecx
00505bd6 mov dword ptr [esp], 0x41200000
00505bdd lea eax, [esp + 0x24]
00505be1 push eax
00505be2 push 1
00505be4 mov ecx, ebx
00505be6 call 0x6a3420
00505beb mov esi, eax
00505bed or dword ptr [esi + 0x388], 2
00505bf4 cmp byte ptr [esp + 0xf], 0
00505bf9 movss xmm1, dword ptr [esi + 0x2b8]
00505c01 movss xmm2, dword ptr [esi + 0x2bc]
00505c09 mov ecx, dword ptr [esi + 0x38c]
00505c0f mulss xmm1, dword ptr [0xb6a4a0]
00505c17 mov dword ptr [esi + 0x38c], ecx
00505c1d mulss xmm2, dword ptr [0xb6a4a0]
00505c25 mov dword ptr [esi + 0x370], 0x3fcccccd
00505c2f je 0x505c66
00505c31 call 0x6c3d90
00505c36 movd xmm0, eax
00505c3a cvtdq2pd xmm0, xmm0
00505c3e shr eax, 0x1f
00505c41 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
00505c4a cvtpd2ps xmm0, xmm0
00505c4e mulss xmm0, dword ptr [0xb6a19c]
00505c56 addss xmm0, dword ptr [0xb6a4c4]
00505c5e mulss xmm1, xmm0
00505c62 mulss xmm2, xmm0
00505c66 movss xmm0, dword ptr [esi + 0x368]
00505c6e lea ecx, [esp + 0x84]
00505c75 subss xmm0, dword ptr [0xb6a3b0]
00505c7d movss dword ptr [esi + 0x2b8], xmm1
00505c85 movss dword ptr [esi + 0x2bc], xmm2
00505c8d movss dword ptr [esi + 0x368], xmm0
00505c95 movss xmm0, dword ptr [esi + 0x364]
00505c9d mulss xmm0, dword ptr [0xb6a50c]
00505ca5 subss xmm0, dword ptr [0xb6a994]
00505cad movss dword ptr [esi + 0x364], xmm0
00505cb5 movss xmm0, dword ptr [0xb6a614]
00505cbd movaps xmm3, xmm0
00505cc0 movaps xmm2, xmm0
00505cc3 movaps xmm1, xmm0
00505cc6 call 0x427080
00505ccb movaps xmm0, xmmword ptr [0xb6c330]
00505cd2 push 1
00505cd4 push 0
00505cd6 push 0xff
00505cdb movups xmmword ptr [esp + 0xa0], xmm0
00505ce3 mov eax, dword ptr [esi]
00505ce5 push -1
00505ce7 push ecx
00505ce8 mov ecx, esi
00505cea call dword ptr [eax + 0x38]
00505ced jmp 0x505f09
00505cf2 mov dword ptr [esp], 0x3f800000
00505cf9 push 0xb5
00505cfe call 0x6ad720
00505d03 movss xmm2, dword ptr [ebx + 0xe70]
00505d0b ucomiss xmm2, dword ptr [0xc02fec]
00505d12 lahf 
00505d13 test ah, 0x44
00505d16 jp 0x505d93
00505d18 movss xmm0, dword ptr [ebx + 0xe74]
00505d20 ucomiss xmm0, dword ptr [0xc02ff0]
00505d27 lahf 
00505d28 test ah, 0x44
00505d2b jp 0x505d93
00505d2d cmp byte ptr [esp + 0xf], 0
00505d32 lea esi, [ebx + 0x294]
00505d38 je 0x505d84
00505d3a mov ecx, ebx
00505d3c call 0x695680
00505d41 push 0
00505d43 push 0
00505d45 push ecx
00505d46 movss xmm1, dword ptr [eax + 0x294]
00505d4e movss xmm2, dword ptr [eax + 0x298]
00505d56 addss xmm1, dword ptr [esi]
00505d5a addss xmm2, dword ptr [esi + 4]
00505d5f mov dword ptr [esp], 0x428c0000
00505d66 mulss xmm1, dword ptr [0xb6a480]
00505d6e mulss xmm2, dword ptr [0xb6a480]
00505d76 movss dword ptr [esp + 0x1c], xmm1
00505d7c movss dword ptr [esp + 0x20], xmm2
00505d82 jmp 0x505dd3
00505d84 push 0
00505d86 push 0
00505d88 push ecx
00505d89 mov dword ptr [esp], 0x42c80000
00505d90 push esi
00505d91 jmp 0x505dd8
00505d93 movss xmm0, dword ptr [ebx + 0xe74]
00505d9b mulss xmm2, dword ptr [0xb6aad4]
00505da3 push 0
00505da5 mulss xmm0, dword ptr [0xb6aad4]
00505dad push 0
00505daf addss xmm2, dword ptr [ebx + 0x294]
00505db7 push ecx
00505db8 addss xmm0, dword ptr [ebx + 0x298]
00505dc0 mov dword ptr [esp], 0
00505dc7 movss dword ptr [esp + 0x1c], xmm2
00505dcd movss dword ptr [esp + 0x20], xmm0
00505dd3 lea eax, [esp + 0x1c]
00505dd7 push eax
00505dd8 mov ecx, dword ptr [0xbfd65c]
00505dde lea eax, [esp + 0x34]
00505de2 push eax
00505de3 mov ecx, dword ptr [ecx + 0x18190]
00505de9 call 0x7cf240
00505dee movss xmm0, dword ptr [eax]
00505df2 movss dword ptr [esp + 0x1c], xmm0
00505df8 movss xmm0, dword ptr [eax + 4]
00505dfd movss dword ptr [esp + 0x20], xmm0
00505e03 call 0x6c3d90
00505e08 mov ecx, dword ptr [0xbfd65c]
00505e0e push 0
00505e10 push eax
00505e11 push 0
00505e13 push ebx
00505e14 push 0xc02fec
00505e19 lea eax, [esp + 0x30]
00505e1d push eax
00505e1e push 0
00505e20 push 0x55
00505e22 call 0x6d0ca0
00505e27 push 0
00505e29 push 0xbeab70
00505e2e push 0xbeab18
00505e33 push 0
00505e35 push eax
00505e36 call 0x9ec34c
00505e3b mov ecx, dword ptr [0xbfd65c]
00505e41 add esp, 0x14
00505e44 mov edi, eax
00505e46 lea eax, [esp + 0x1c]
00505e4a mov esi, dword ptr [ecx + 0x18190]
00505e50 mov ecx, esi
00505e52 push 0x384
00505e57 push eax
00505e58 call 0x7ce950
00505e5d push eax
00505e5e mov ecx, esi
00505e60 call 0x447f40
00505e65 movss xmm4, dword ptr [edi + 0x294]
00505e6d movss xmm0, dword ptr [edi + 0x2a8]
00505e75 subss xmm0, dword ptr [0xb6a974]
00505e7d movss dword ptr [edi + 0x28c], xmm4
00505e85 movss xmm3, dword ptr [edi + 0x298]
00505e8d movss dword ptr [edi + 0x290], xmm3
00505e95 movss xmm2, dword ptr [ebx + 0x294]
00505e9d movss dword ptr [edi + 0x294], xmm2
00505ea5 subss xmm4, xmm2
00505ea9 movss xmm1, dword ptr [ebx + 0x298]
00505eb1 subss xmm3, xmm1
00505eb5 movss dword ptr [edi + 0x298], xmm1
00505ebd movss dword ptr [edi + 0x2a8], xmm0
00505ec5 mov dword ptr [edi + 0xab4], 6
00505ecf mulss xmm4, dword ptr [0xb6a264]
00505ed7 mov dword ptr [edi + 0xb0c], 0xc1000000
00505ee1 mulss xmm3, dword ptr [0xb6a264]
00505ee9 movss dword ptr [edi + 0x2b8], xmm4
00505ef1 movss dword ptr [edi + 0xb00], xmm4
00505ef9 movss dword ptr [edi + 0x2bc], xmm3
00505f01 movss dword ptr [edi + 0xb04], xmm3
00505f09 cmp dword ptr [ebx + 0x70], 0
00505f0d je 0x5060de
00505f13 cmp byte ptr [ebx + 0x80], 0
00505f1a jne 0x5060e8
00505f20 jmp 0x5060de
00505f25 test edi, edi
00505f27 je 0x505f6e
00505f29 cmp dword ptr [edi + 0x14], 0x10
00505f2d mov eax, edi
00505f2f jb 0x505f33
00505f31 mov eax, dword ptr [edi]
00505f33 mov ecx, 0xb41e80
00505f38 mov dl, byte ptr [eax]
00505f3a cmp dl, byte ptr [ecx]
00505f3c jne 0x505f58
00505f3e test dl, dl
00505f40 je 0x505f54
00505f42 mov dl, byte ptr [eax + 1]
00505f45 cmp dl, byte ptr [ecx + 1]
00505f48 jne 0x505f58
00505f4a add eax, 2
00505f4d add ecx, 2
00505f50 test dl, dl
00505f52 jne 0x505f38
00505f54 xor eax, eax
00505f56 jmp 0x505f5d
00505f58 sbb eax, eax
00505f5a or eax, 1
00505f5d test eax, eax
00505f5f jne 0x505f6e
00505f61 cmp byte ptr [edi + 0x34], al
00505f64 je 0x505f09
00505f66 cmp byte ptr [ebx + 0x80], al
00505f6c jne 0x505f09
00505f6e push 1
00505f70 push 0xb41e80
00505f75 lea ecx, [ebx + 0x3c]
00505f78 call 0x405740
00505f7d test al, al
00505f7f je 0x505f09
00505f81 lea ecx, [ebx + 0x6c]
00505f84 call 0x405330
00505f89 mov byte ptr [ebx + 0x80], 1
00505f90 jmp 0x505f09
00505f95 movss xmm2, dword ptr [ebx + 0xb00]
00505f9d lea eax, [ebx + 0x2d8]
00505fa3 movss xmm3, dword ptr [ebx + 0x2f4]
00505fab movaps xmm0, xmm2
00505fae mulss xmm0, dword ptr [0xb6a670]
00505fb6 mulss xmm0, xmm3
00505fba addss xmm0, xmm1
00505fbe comiss xmm0, xmm6
00505fc1 movss dword ptr [ebx + 0x2d8], xmm0
00505fc9 cmova eax, edx
00505fcc cmp dword ptr [ebx + 0x34], 0x24
00505fd0 movss xmm4, dword ptr [eax]
00505fd4 movss dword ptr [ebx + 0x2d8], xmm4
00505fdc jne 0x505fe8
00505fde movss xmm1, dword ptr [0xb6a214]
00505fe6 jmp 0x505ff0
00505fe8 movss xmm1, dword ptr [0xb6a234]
00505ff0 movaps xmm0, xmm3
00505ff3 mulss xmm0, xmm1
00505ff7 addss xmm0, xmm2
00505ffb movss dword ptr [ebx + 0xb00], xmm0
00506003 cmp dword ptr [ebx + 0x2c], 2
00506007 movss xmm5, dword ptr [0xb6a614]
0050600f jne 0x506048
00506011 movss xmm2, dword ptr [0xb6a560]
00506019 ucomiss xmm3, xmm5
0050601c lahf 
0050601d test ah, 0x44
00506020 jnp 0x506038
00506022 movaps xmm1, xmm3
00506025 movaps xmm0, xmm3
00506028 addss xmm1, xmm2
0050602c mulss xmm0, xmm2
00506030 subss xmm1, xmm0
00506034 divss xmm2, xmm1
00506038 mulss xmm2, dword ptr [ebx + 0xb00]
00506040 movss dword ptr [ebx + 0xb00], xmm2
00506048 movss xmm1, dword ptr [0xb6a560]
00506050 ucomiss xmm3, xmm5
00506053 lahf 
00506054 test ah, 0x44
00506057 jnp 0x50606c
00506059 movaps xmm0, xmm3
0050605c mulss xmm3, xmm1
00506060 addss xmm0, xmm1
00506064 subss xmm0, xmm3
00506068 divss xmm1, xmm0
0050606c divss xmm4, xmm6
00506070 mulss xmm1, dword ptr [ebx + 0xb00]
00506078 maxss xmm4, dword ptr [0xb6a18c]
00506080 movss dword ptr [ebx + 0xb00], xmm1
00506088 mulss xmm4, dword ptr [0xb6a994]
00506090 movaps xmm0, xmm4
00506093 call 0x9eb8a0
00506098 push 1
0050609a mov edi, 0xd
0050609f lea ecx, [ebx + 0x3c]
005060a2 push 0xb41e70
005060a7 sub edi, eax
005060a9 call 0x405740
005060ae test al, al
005060b0 je 0x5060de
005060b2 mov eax, dword ptr [ebx + 0x70]
005060b5 test eax, eax
005060b7 je 0x5060de
005060b9 xor eax, eax
005060bb lea ecx, [ebx + 0x6c]
005060be cmp eax, edi
005060c0 sbb eax, eax
005060c2 and eax, edi
005060c4 movd xmm1, eax
005060c8 cvtdq2ps xmm1, xmm1
005060cb call 0x403c00
005060d0 mov eax, dword ptr [ebx + 0x70]
005060d3 test eax, eax
005060d5 je 0x5060de
005060d7 mov byte ptr [ebx + 0x80], 0
005060de mov dword ptr [ebx + 0xab4], 3
005060e8 movss xmm1, dword ptr [ebx + 0x28c]
005060f0 movss xmm0, dword ptr [ebx + 0x290]
005060f8 subss xmm1, dword ptr [ebx + 0x294]
00506100 subss xmm0, dword ptr [ebx + 0x298]
00506108 movss dword ptr [ebx + 0x2b8], xmm1
00506110 movss dword ptr [ebx + 0x2bc], xmm0
00506118 mov ecx, dword ptr [esp + 0x15c]
0050611f pop edi
00506120 pop esi
00506121 pop ebx
00506122 xor ecx, esp
00506124 call 0x9eacd7
00506129 mov esp, ebp
0050612b pop ebp
0050612c ret 
