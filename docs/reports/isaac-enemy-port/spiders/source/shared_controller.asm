005175b0 push ebx
005175b1 mov ebx, esp
005175b3 sub esp, 8
005175b6 and esp, 0xfffffff8
005175b9 add esp, 4
005175bc push ebp
005175bd mov ebp, dword ptr [ebx + 4]
005175c0 mov dword ptr [esp + 4], ebp
005175c4 mov ebp, esp
005175c6 push -1
005175c8 push 0x9ef67d
005175cd mov eax, dword ptr fs:[0]
005175d3 push eax
005175d4 push ebx
005175d5 sub esp, 0x50
005175d8 mov eax, dword ptr [0xbaa3b4]
005175dd xor eax, ebp
005175df mov dword ptr [ebp - 0x14], eax
005175e2 push esi
005175e3 push edi
005175e4 push eax
005175e5 lea eax, [ebp - 0xc]
005175e8 mov dword ptr fs:[0], eax
005175ee mov edi, ecx
005175f0 mov ecx, dword ptr [0xbfd65c]
005175f6 push 1
005175f8 add ecx, 0x1ba40
005175fe push ecx
005175ff push 0x179
00517604 call 0x91d340
00517609 test eax, eax
0051760b je 0x5176ec
00517611 mov eax, dword ptr [edi + 0x160]
00517617 and eax, 0x20000000
0051761c or eax, 0
0051761f jne 0x5176ec
00517625 cvttss2si esi, dword ptr [edi + 0x2fc]
0051762d mov cl, 1
0051762f mov byte ptr [ebp - 0x2d], cl
00517632 cvttss2si eax, dword ptr [edi + 0x2f8]
0051763a sub esi, eax
0051763c cmp dword ptr [edi + 0xab4], 0
00517643 je 0x517665
00517645 mov eax, dword ptr [0xbfd65c]
0051764a mov byte ptr [ebp - 0x2e], cl
0051764d mov dword ptr [ebp - 0x44], esi
00517650 mov eax, dword ptr [eax + 0x1a30dc]
00517656 sub eax, dword ptr [edi + 0x280]
0051765c cmp eax, 1
0051765f jne 0x517705
00517665 mov eax, dword ptr [0xb43118]
0051766a mov dword ptr [ebp - 0x2c], eax
0051766d mov ax, word ptr [0xb4311c]
00517673 mov dword ptr [ebp - 0x18], 0xf
0051767a mov dword ptr [ebp - 0x1c], 6
00517681 mov word ptr [ebp - 0x28], ax
00517685 mov byte ptr [ebp - 0x26], 0
00517689 lea eax, [ebp - 0x2c]
0051768c mov dword ptr [ebp - 4], 0
00517693 push eax
00517694 mov ecx, edi
00517696 call 0x691bc0
0051769b mov al, byte ptr [ebp - 0x2d]
0051769e mov dword ptr [ebp - 4], 0xffffffff
005176a5 mov edx, dword ptr [ebp - 0x18]
005176a8 mov byte ptr [ebp - 0x2e], al
005176ab mov dword ptr [ebp - 0x44], esi
005176ae cmp edx, 0x10
005176b1 jb 0x517705
005176b3 mov ecx, dword ptr [ebp - 0x2c]
005176b6 inc edx
005176b7 mov eax, ecx
005176b9 cmp edx, 0x1000
005176bf jb 0x5176d7
005176c1 mov ecx, dword ptr [ecx - 4]
005176c4 add edx, 0x23
005176c7 sub eax, ecx
005176c9 add eax, -4
005176cc cmp eax, 0x1f
005176cf jbe 0x5176d7
005176d1 call dword ptr [0xa065ac]
005176d7 push edx
005176d8 push ecx
005176d9 call 0x9eb08e
005176de mov al, byte ptr [ebp - 0x2d]
005176e1 add esp, 8
005176e4 mov byte ptr [ebp - 0x2e], al
005176e7 mov dword ptr [ebp - 0x44], esi
005176ea jmp 0x517705
005176ec cvttss2si ecx, dword ptr [edi + 0x2fc]
005176f4 mov byte ptr [ebp - 0x2e], 0
005176f8 cvttss2si eax, dword ptr [edi + 0x2f8]
00517700 sub ecx, eax
00517702 mov dword ptr [ebp - 0x44], ecx
00517705 mov ecx, dword ptr [edi + 0xab4]
0051770b test ecx, ecx
0051770d jne 0x517724
0051770f mov dword ptr [edi + 0xab4], 4
00517719 mov dword ptr [edi + 0x360], ecx
0051771f jmp 0x5185b9
00517724 mov eax, dword ptr [edi + 0x160]
0051772a and eax, 0x20000000
0051772f or eax, 0
00517732 je 0x51773d
00517734 cmp dword ptr [edi + 0xe6c], -1
0051773b jne 0x517786
0051773d mov ecx, dword ptr [0xbfd65c]
00517743 lea esi, [edi + 0x294]
00517749 sub esp, 0xc
0051774c lea eax, [ebp - 0x60]
0051774f xorps xmm3, xmm3
00517752 mov ecx, dword ptr [ecx + 0x18190]
00517758 mov dword ptr [esp + 8], 0x41200000
00517760 mov dword ptr [esp + 4], 0
00517768 mov dword ptr [esp], 0x41a00000
0051776f push esi
00517770 push eax
00517771 call 0x7cec10
00517776 mov ecx, dword ptr [eax]
00517778 mov dword ptr [esi], ecx
0051777a mov eax, dword ptr [eax + 4]
0051777d mov dword ptr [esi + 4], eax
00517780 mov ecx, dword ptr [edi + 0xab4]
00517786 xor edx, edx
00517788 mov eax, 4
0051778d cmp ecx, 6
00517790 cmove eax, edx
00517793 mov dword ptr [edi + 0x180], eax
00517799 mov eax, dword ptr [edi + 0x28]
0051779c cmp eax, 0xfa
005177a1 je 0x5177aa
005177a3 cmp eax, 0x365
005177a8 jne 0x5177c9
005177aa mov eax, dword ptr [edi + 0xe6c]
005177b0 cmp eax, -1
005177b3 je 0x5177c9
005177b5 push edi
005177b6 push eax
005177b7 push 9
005177b9 call 0x8b10b0
005177be test al, al
005177c0 je 0x5177c9
005177c2 mov eax, dword ptr [edi]
005177c4 mov ecx, edi
005177c6 call dword ptr [eax + 0x24]
005177c9 mov eax, dword ptr [edi + 0xab4]
005177cf cmp eax, 6
005177d2 jne 0x517b4c
005177d8 mov eax, dword ptr [edi + 0x28]
005177db cmp eax, 0xd7
005177e0 je 0x5178fc
005177e6 cmp eax, 0xfa
005177eb je 0x5178fc
005177f1 cmp eax, 0x365
005177f6 je 0x5178fc
005177fc cmp dword ptr [edi + 0x70], 0
00517800 je 0x517857
00517802 cmp byte ptr [edi + 0x80], 0
00517809 jne 0x517857
0051780b mov eax, dword ptr [edi + 0x70]
0051780e cmp dword ptr [eax + 0x14], 0x10
00517812 jb 0x517816
00517814 mov eax, dword ptr [eax]
00517816 mov ecx, 0xb40338
0051781b nop dword ptr [eax + eax]
00517820 mov dl, byte ptr [eax]
00517822 cmp dl, byte ptr [ecx]
00517824 jne 0x517840
00517826 test dl, dl
00517828 je 0x51783c
0051782a mov dl, byte ptr [eax + 1]
0051782d cmp dl, byte ptr [ecx + 1]
00517830 jne 0x517840
00517832 add eax, 2
00517835 add ecx, 2
00517838 test dl, dl
0051783a jne 0x517820
0051783c xor eax, eax
0051783e jmp 0x517845
00517840 sbb eax, eax
00517842 or eax, 1
00517845 test eax, eax
00517847 jne 0x517857
00517849 push eax
0051784a push 0xb43140
0051784f lea ecx, [edi + 0x3c]
00517852 call 0x4054f0
00517857 mov eax, dword ptr [edi + 0xb00]
0051785d mov dword ptr [edi + 0x2b8], eax
00517863 mov eax, dword ptr [edi + 0xb04]
00517869 mov dword ptr [edi + 0x2bc], eax
0051786f movss xmm2, dword ptr [edi + 0x2f4]
00517877 movaps xmm1, xmm2
0051787a mulss xmm1, dword ptr [0xb6a50c]
00517882 addss xmm1, dword ptr [edi + 0xb0c]
0051788a movaps xmm0, xmm1
0051788d movss dword ptr [edi + 0xb0c], xmm1
00517895 xorps xmm1, xmmword ptr [0xb6c9b0]
0051789c mulss xmm0, xmm2
005178a0 mulss xmm1, xmm2
005178a4 addss xmm0, dword ptr [edi + 0x2a8]
005178ac comiss xmm0, xmm1
005178af movss dword ptr [edi + 0x2a8], xmm0
005178b7 jbe 0x5183cd
005178bd mov dword ptr [edi + 0x2a8], 0
005178c7 movss xmm0, dword ptr [0xc02fec]
005178cf movss dword ptr [edi + 0x28c], xmm0
005178d7 movss xmm0, dword ptr [0xc02ff0]
005178df movss dword ptr [edi + 0x290], xmm0
005178e7 inc dword ptr [edi + 0x360]
005178ed mov dword ptr [edi + 0xab4], 4
005178f7 jmp 0x5183cd
005178fc cmp dword ptr [edi + 0x70], 0
00517900 lea esi, [edi + 0x6c]
00517903 je 0x517a1b
00517909 push 0xb40338
0051790e mov ecx, esi
00517910 call 0x405e90
00517915 test al, al
00517917 je 0x51797d
00517919 movss xmm2, dword ptr [edi + 0x290]
00517921 movss xmm1, dword ptr [edi + 0x28c]
00517929 subss xmm2, dword ptr [edi + 0x298]
00517931 subss xmm1, dword ptr [edi + 0x294]
00517939 mulss xmm2, dword ptr [0xb6a2ac]
00517941 mulss xmm1, dword ptr [0xb6a2ac]
00517949 movss dword ptr [edi + 0x2bc], xmm2
00517951 movss dword ptr [edi + 0xb04], xmm2
00517959 movss dword ptr [edi + 0x2b8], xmm1
00517961 movss dword ptr [edi + 0xb00], xmm1
00517969 mov dword ptr [edi + 0xb0c], 0xc0800000
00517973 mov dword ptr [edi + 0x360], 0
0051797d cmp dword ptr [edi + 0x70], 0
00517981 je 0x517a1b
00517987 push 0xb40338
0051798c mov ecx, esi
0051798e call 0x405f30
00517993 test al, al
00517995 je 0x5179ce
00517997 movss xmm1, dword ptr [edi + 0x2f4]
0051799f movaps xmm0, xmm1
005179a2 mulss xmm0, dword ptr [0xb6a50c]
005179aa addss xmm0, dword ptr [edi + 0xb0c]
005179b2 movss dword ptr [edi + 0xb0c], xmm0
005179ba mulss xmm0, xmm1
005179be addss xmm0, dword ptr [edi + 0x2a8]
005179c6 movss dword ptr [edi + 0x2a8], xmm0
005179ce cmp dword ptr [edi + 0x70], 0
005179d2 je 0x517a1b
005179d4 push 0xb40338
005179d9 mov ecx, esi
005179db call 0x405f30
005179e0 test al, al
005179e2 je 0x517a1b
005179e4 cmp dword ptr [edi + 0x70], 0
005179e8 je 0x5179fa
005179ea push 0xb4034c
005179ef mov ecx, esi
005179f1 call 0x405f30
005179f6 test al, al
005179f8 jne 0x517a1b
005179fa mov eax, dword ptr [edi + 0xb00]
00517a00 xor ecx, ecx
00517a02 mov dword ptr [edi + 0x2b8], eax
00517a08 mov eax, dword ptr [edi + 0xb04]
00517a0e mov dword ptr [edi + 0x2bc], eax
00517a14 mov eax, 3
00517a19 jmp 0x517a25
00517a1b mov eax, 5
00517a20 mov ecx, 4
00517a25 mov dword ptr [edi + 0x180], ecx
00517a2b mov dword ptr [edi + 0x17c], eax
00517a31 cmp dword ptr [edi + 0x70], 0
00517a35 je 0x517a9b
00517a37 push 0xb4034c
00517a3c mov ecx, esi
00517a3e call 0x405f30
00517a43 test al, al
00517a45 je 0x517a9b
00517a47 movss xmm1, dword ptr [edi + 0xb0c]
00517a4f xorps xmm1, xmmword ptr [0xb6c9b0]
00517a56 mulss xmm1, dword ptr [edi + 0x2f4]
00517a5e movss xmm0, dword ptr [edi + 0x2a8]
00517a66 comiss xmm0, xmm1
00517a69 jbe 0x517a9b
00517a6b mov dword ptr [edi + 0x2a8], 0
00517a75 movss xmm0, dword ptr [0xc02fec]
00517a7d movss dword ptr [edi + 0x28c], xmm0
00517a85 movss xmm0, dword ptr [0xc02ff0]
00517a8d movss dword ptr [edi + 0x290], xmm0
00517a95 inc dword ptr [edi + 0x360]
00517a9b movss xmm0, dword ptr [edi + 0x28c]
00517aa3 ucomiss xmm0, dword ptr [0xc02fec]
00517aaa lahf 
00517aab test ah, 0x44
00517aae jp 0x5183cd
00517ab4 movss xmm0, dword ptr [edi + 0x290]
00517abc ucomiss xmm0, dword ptr [0xc02ff0]
00517ac3 lahf 
00517ac4 test ah, 0x44
00517ac7 jp 0x5183cd
00517acd movss xmm0, dword ptr [edi + 0x2c4]
00517ad5 mulss xmm0, dword ptr [0xb6a560]
00517add movss dword ptr [edi + 0x2c4], xmm0
00517ae5 cmp dword ptr [edi + 0x70], 0
00517ae9 je 0x5183cd
00517aef cmp byte ptr [edi + 0x80], 0
00517af6 jne 0x5183cd
00517afc mov eax, dword ptr [edi + 0x70]
00517aff cmp dword ptr [eax + 0x14], 0x10
00517b03 jb 0x517b07
00517b05 mov eax, dword ptr [eax]
00517b07 mov ecx, 0xb40338
00517b0c nop dword ptr [eax]
00517b10 mov dl, byte ptr [eax]
00517b12 cmp dl, byte ptr [ecx]
00517b14 jne 0x517b30
00517b16 test dl, dl
00517b18 je 0x517b2c
00517b1a mov dl, byte ptr [eax + 1]
00517b1d cmp dl, byte ptr [ecx + 1]
00517b20 jne 0x517b30
00517b22 add eax, 2
00517b25 add ecx, 2
00517b28 test dl, dl
00517b2a jne 0x517b10
00517b2c xor eax, eax
00517b2e jmp 0x517b35
00517b30 sbb eax, eax
00517b32 or eax, 1
00517b35 test eax, eax
00517b37 jne 0x5183cd
00517b3d mov dword ptr [edi + 0xab4], 4
00517b47 jmp 0x5183cd
00517b4c cmp byte ptr [edi + 0x16b], 0
00517b53 je 0x517cfd
00517b59 cmp dword ptr [edi + 0x28], 0x5e
00517b5d jne 0x517cfd
00517b63 movss xmm0, dword ptr [edi + 0x2d8]
00517b6b comiss xmm0, dword ptr [0xb6aee4]
00517b72 jbe 0x517cfd
00517b78 push ecx
00517b79 lea eax, [ebp - 0x38]
00517b7c mov dword ptr [esp], 0
00517b83 push eax
00517b84 mov ecx, edi
00517b86 call 0x695a30
00517b8b movss xmm1, dword ptr [ebp - 0x34]
00517b90 subss xmm1, dword ptr [edi + 0x298]
00517b98 movss xmm2, dword ptr [ebp - 0x38]
00517b9d subss xmm2, dword ptr [edi + 0x294]
00517ba5 movaps xmm0, xmm1
00517ba8 movss dword ptr [ebp - 0x44], xmm1
00517bad mulss xmm0, xmm1
00517bb1 movaps xmm1, xmm2
00517bb4 movss dword ptr [ebp - 0x3c], xmm2
00517bb9 mulss xmm1, xmm2
00517bbd addss xmm0, xmm1
00517bc1 call 0x4228c0
00517bc6 movaps xmm3, xmm0
00517bc9 comiss xmm3, dword ptr [0xb6a18c]
00517bd0 jbe 0x517bf5
00517bd2 movss xmm0, dword ptr [ebp - 0x44]
00517bd7 divss xmm0, xmm3
00517bdb movss xmm1, dword ptr [ebp - 0x3c]
00517be0 mulss xmm0, dword ptr [0xb6a974]
00517be8 divss xmm1, xmm3
00517bec xorps xmm0, xmmword ptr [0xb6c9b0]
00517bf3 jmp 0x517c12
00517bf5 lea eax, [ebp - 0x58]
00517bf8 push eax
00517bf9 call 0x659290
00517bfe add esp, 4
00517c01 movss xmm0, dword ptr [eax]
00517c05 mulss xmm0, dword ptr [0xb6a974]
00517c0d movss xmm1, dword ptr [eax + 4]
00517c12 mulss xmm1, dword ptr [0xb6a974]
00517c1a movss dword ptr [ebp - 0x38], xmm0
00517c1f movss dword ptr [ebp - 0x44], xmm0
00517c24 movss dword ptr [ebp - 0x34], xmm1
00517c29 movss dword ptr [ebp - 0x3c], xmm1
00517c2e call 0x6c3d90
00517c33 addss xmm0, dword ptr [edi + 0x294]
00517c3b addss xmm1, dword ptr [edi + 0x298]
00517c43 mov ecx, dword ptr [0xbfd65c]
00517c49 push eax
00517c4a push 0
00517c4c push edi
00517c4d lea eax, [ebp - 0x38]
00517c50 movss dword ptr [ebp - 0x50], xmm0
00517c55 push eax
00517c56 lea eax, [ebp - 0x50]
00517c59 movss dword ptr [ebp - 0x4c], xmm1
00517c5e push eax
00517c5f push 0
00517c61 push 0x55
00517c63 call 0x422e20
00517c68 mov esi, eax
00517c6a call 0x6c3d90
00517c6f movss xmm0, dword ptr [0xc02fec]
00517c77 subss xmm0, dword ptr [ebp - 0x44]
00517c7c mov ecx, dword ptr [0xbfd65c]
00517c82 push eax
00517c83 push 0
00517c85 push edi
00517c86 movss dword ptr [ebp - 0x38], xmm0
00517c8b lea eax, [ebp - 0x38]
00517c8e movss xmm0, dword ptr [0xc02ff0]
00517c96 subss xmm0, dword ptr [ebp - 0x3c]
00517c9b push eax
00517c9c lea eax, [ebp - 0x40]
00517c9f push eax
00517ca0 push 0
00517ca2 movss dword ptr [ebp - 0x34], xmm0
00517ca7 movss xmm0, dword ptr [edi + 0x294]
00517caf subss xmm0, dword ptr [ebp - 0x44]
00517cb4 push 0x55
00517cb6 movss dword ptr [ebp - 0x40], xmm0
00517cbb movss xmm0, dword ptr [edi + 0x298]
00517cc3 subss xmm0, dword ptr [ebp - 0x3c]
00517cc8 movss dword ptr [ebp - 0x3c], xmm0
00517ccd call 0x422e20
00517cd2 mov ecx, dword ptr [esi + 0x164]
00517cd8 and dword ptr [esi + 0x160], 0xfffffffb
00517cdf mov dword ptr [esi + 0x164], ecx
00517ce5 mov ecx, dword ptr [eax + 0x164]
00517ceb and dword ptr [eax + 0x160], 0xfffffffb
00517cf2 mov dword ptr [eax + 0x164], ecx
00517cf8 jmp 0x5183b5
00517cfd cmp eax, 4
00517d00 jne 0x5183b5
00517d06 push ecx
00517d07 lea eax, [ebp - 0x38]
00517d0a mov dword ptr [esp], 0x42700000
00517d11 push eax
00517d12 mov ecx, edi
00517d14 call 0x695a30
00517d19 movss xmm0, dword ptr [ebp - 0x38]
00517d1e lea esi, [edi + 0x294]
00517d24 subss xmm0, dword ptr [esi]
00517d28 mov eax, dword ptr [edi + 0x28]
00517d2b movss dword ptr [ebp - 0x3c], xmm0
00517d30 movss xmm0, dword ptr [ebp - 0x34]
00517d35 subss xmm0, dword ptr [esi + 4]
00517d3a movss dword ptr [ebp - 0x4c], xmm0
00517d3f cmp eax, 0xd7
00517d44 je 0x517d5a
00517d46 cmp eax, 0xfa
00517d4b je 0x517d5a
00517d4d cmp eax, 0x365
00517d52 je 0x517d5a
00517d54 mov byte ptr [ebp - 0x2d], 0
00517d58 jmp 0x517d6f
00517d5a movss xmm2, dword ptr [0xb6ab10]
00517d62 mov ecx, edi
00517d64 push 0
00517d66 mov byte ptr [ebp - 0x2d], 1
00517d6a call 0x6af8d0
00517d6f movss xmm0, dword ptr [edi + 0x28c]
00517d77 ucomiss xmm0, dword ptr [0xc02fec]
00517d7e lahf 
00517d7f test ah, 0x44
00517d82 jp 0x518267
00517d88 movss xmm0, dword ptr [edi + 0x290]
00517d90 ucomiss xmm0, dword ptr [0xc02ff0]
00517d97 lahf 
00517d98 test ah, 0x44
00517d9b jp 0x518267
00517da1 push 0
00517da3 lea ecx, [edi + 0x3c]
00517da6 push 0xb3fd8c
00517dab call 0x4054f0
00517db0 mov ecx, dword ptr [edi + 0x360]
00517db6 mov eax, dword ptr [ebp - 0x44]
00517db9 add eax, ecx
00517dbb mov dword ptr [edi + 0x360], eax
00517dc1 cmp ecx, 0xd
00517dc4 jle 0x5183b5
00517dca cmp dword ptr [edi + 0xe6c], -1
00517dd1 je 0x517ea9
00517dd7 cmp byte ptr [ebp - 0x2d], 0
00517ddb je 0x517e62
00517de1 mov ecx, edi
00517de3 call 0x6afb10
00517de8 test al, al
00517dea je 0x517e62
00517dec lea eax, [ebp - 0x58]
00517def mov ecx, edi
00517df1 push eax
00517df2 call 0x6afac0
00517df7 mov ecx, dword ptr [0xbfd65c]
00517dfd push dword ptr [eax + 4]
00517e00 mov ecx, dword ptr [ecx + 0x18190]
00517e06 push dword ptr [eax]
00517e08 call 0x7aee40
00517e0d test eax, eax
00517e0f jne 0x517e62
00517e11 lea eax, [ebp - 0x58]
00517e14 mov ecx, edi
00517e16 push eax
00517e17 call 0x6afac0
00517e1c push 1
00517e1e push 0xb40338
00517e23 mov ecx, dword ptr [eax]
00517e25 mov dword ptr [edi + 0x28c], ecx
00517e2b lea ecx, [edi + 0x3c]
00517e2e mov eax, dword ptr [eax + 4]
00517e31 mov dword ptr [edi + 0x290], eax
00517e37 mov dword ptr [edi + 0xab4], 6
00517e41 call 0x405740
00517e46 test al, al
00517e48 je 0x5183b5
00517e4e lea ecx, [edi + 0x6c]
00517e51 call 0x405330
00517e56 mov byte ptr [edi + 0x80], 1
00517e5d jmp 0x5183b5
00517e62 movss xmm2, dword ptr [0xb6a2cc]
00517e6a lea eax, [ebp - 0x38]
00517e6d push 0xc02fec
00517e72 push eax
00517e73 mov ecx, edi
00517e75 call 0x6af0c0
00517e7a mov ecx, eax
00517e7c call 0x962ca0
00517e81 test al, al
00517e83 je 0x5183b5
00517e89 mov eax, dword ptr [esi]
00517e8b mov dword ptr [edi + 0x28c], eax
00517e91 mov eax, dword ptr [esi + 4]
00517e94 mov dword ptr [edi + 0x290], eax
00517e9a mov dword ptr [edi + 0x360], 8
00517ea4 jmp 0x5183b5
00517ea9 cmp byte ptr [ebp - 0x2e], 0
00517ead jne 0x517feb
00517eb3 movss xmm1, dword ptr [ebp - 0x4c]
00517eb8 movss xmm0, dword ptr [ebp - 0x3c]
00517ebd mulss xmm0, xmm0
00517ec1 mulss xmm1, xmm1
00517ec5 addss xmm0, xmm1
00517ec9 call 0x4228c0
00517ece movaps xmm2, xmm0
00517ed1 call 0x6c3d90
00517ed6 xorps xmm1, xmm1
00517ed9 cvtsi2sd xmm1, eax
00517edd shr eax, 0x1f
00517ee0 addsd xmm1, qword ptr [eax*8 + 0xb6c940]
00517ee9 cvtpd2ps xmm1, xmm1
00517eed mulss xmm1, dword ptr [0xb6a19c]
00517ef5 mulss xmm1, dword ptr [0xb6aafc]
00517efd addss xmm1, dword ptr [0xb6aafc]
00517f05 comiss xmm1, xmm2
00517f08 ja 0x517f17
00517f0a cmp dword ptr [edi + 0xe88], 0
00517f11 je 0x517feb
00517f17 mov ecx, dword ptr [0xbfd65c]
00517f1d lea eax, [ebp - 0x38]
00517f20 push 0
00517f22 push 0
00517f24 push 0
00517f26 mov ecx, dword ptr [ecx + 0x18190]
00517f2c push 0
00517f2e push 1
00517f30 push eax
00517f31 push esi
00517f32 call 0x7af4b0
00517f37 test al, al
00517f39 jne 0x517f48
00517f3b cmp dword ptr [edi + 0x17c], 3
00517f42 jne 0x517feb
00517f48 mov ecx, edi
00517f4a call 0x695680
00517f4f movss xmm3, dword ptr [edi + 0x2c8]
00517f57 sub esp, 0xc
00517f5a mov ecx, dword ptr [0xbfd65c]
00517f60 movss xmm0, dword ptr [eax + 0x2b8]
00517f68 movss xmm1, dword ptr [eax + 0x2bc]
00517f70 lea eax, [ebp - 0x38]
00517f73 mulss xmm0, dword ptr [0xb6a974]
00517f7b mov ecx, dword ptr [ecx + 0x18190]
00517f81 mulss xmm1, dword ptr [0xb6a974]
00517f89 addss xmm0, dword ptr [ebp - 0x38]
00517f8e movss dword ptr [esp + 8], xmm3
00517f94 addss xmm1, dword ptr [ebp - 0x34]
00517f99 movss dword ptr [esp + 4], xmm3
00517f9f movss dword ptr [esp], xmm3
00517fa4 push eax
00517fa5 lea eax, [ebp - 0x50]
00517fa8 movss dword ptr [ebp - 0x38], xmm0
00517fad push eax
00517fae movss dword ptr [ebp - 0x34], xmm1
00517fb3 call 0x7cec10
00517fb8 movss xmm6, dword ptr [ebp - 0x50]
00517fbd movss xmm7, dword ptr [ebp - 0x4c]
00517fc2 movss dword ptr [ebp - 0x3c], xmm6
00517fc7 movss dword ptr [ebp - 0x38], xmm6
00517fcc movss dword ptr [ebp - 0x44], xmm7
00517fd1 movss dword ptr [ebp - 0x34], xmm7
00517fd6 movss dword ptr [edi + 0x28c], xmm6
00517fde movss dword ptr [edi + 0x290], xmm7
00517fe6 jmp 0x5181c7
00517feb call 0x6c3d90
00517ff0 movd xmm0, eax
00517ff4 cvtdq2pd xmm0, xmm0
00517ff8 shr eax, 0x1f
00517ffb addsd xmm0, qword ptr [eax*8 + 0xb6c940]
00518004 lea eax, [ebp - 0x58]
00518007 push eax
00518008 cvtpd2ps xmm0, xmm0
0051800c mulss xmm0, dword ptr [0xb6a19c]
00518014 mulss xmm0, dword ptr [0xb6aa3c]
0051801c addss xmm0, dword ptr [0xb6aab4]
00518024 movss dword ptr [ebp - 0x4c], xmm0
00518029 call 0x659290
0051802e movss xmm1, dword ptr [ebp - 0x4c]
00518033 movss xmm3, dword ptr [0xb6aa8c]
0051803b movaps xmm0, xmm1
0051803e mov dword ptr [esp], 0x42700000
00518045 sub esp, 8
00518048 mulss xmm0, dword ptr [eax]
0051804c mulss xmm1, dword ptr [eax + 4]
00518051 lea eax, [ebp - 0x38]
00518054 mov dword ptr [esp + 4], 0x42200000
0051805c addss xmm0, dword ptr [esi]
00518060 mov dword ptr [esp], 0x428c0000
00518067 addss xmm1, dword ptr [esi + 4]
0051806c mov esi, dword ptr [0xbfd65c]
00518072 push eax
00518073 lea eax, [ebp - 0x50]
00518076 movss dword ptr [ebp - 0x38], xmm0
0051807b push eax
0051807c mov ecx, dword ptr [esi + 0x18190]
00518082 movss dword ptr [ebp - 0x34], xmm1
00518087 call 0x7cec10
0051808c movss xmm0, dword ptr [eax]
00518090 movss dword ptr [ebp - 0x38], xmm0
00518095 movss dword ptr [ebp - 0x3c], xmm0
0051809a movss xmm0, dword ptr [eax + 4]
0051809f mov eax, dword ptr [esi + 0x18190]
005180a5 mov ecx, eax
005180a7 movss dword ptr [ebp - 0x34], xmm0
005180ac push dword ptr [ebp - 0x34]
005180af movss dword ptr [ebp - 0x44], xmm0
005180b4 push dword ptr [ebp - 0x38]
005180b7 mov dword ptr [ebp - 0x4c], eax
005180ba call 0x7aee40
005180bf test eax, eax
005180c1 jne 0x5181c7
005180c7 mov ecx, dword ptr [ebp - 0x4c]
005180ca lea esi, [edi + 0x294]
005180d0 push eax
005180d1 push eax
005180d2 push eax
005180d3 push eax
005180d4 push eax
005180d5 push esi
005180d6 lea eax, [ebp - 0x38]
005180d9 push eax
005180da call 0x7af4b0
005180df movss xmm7, dword ptr [ebp - 0x34]
005180e4 movss xmm6, dword ptr [ebp - 0x38]
005180e9 movss dword ptr [ebp - 0x44], xmm7
005180ee movss dword ptr [ebp - 0x3c], xmm6
005180f3 test al, al
005180f5 jne 0x5181ad
005180fb call 0x6c3d90
00518100 xor edx, edx
00518102 mov ecx, 0x14
00518107 div ecx
00518109 test edx, edx
0051810b jne 0x5181c7
00518111 movss xmm4, dword ptr [esi]
00518115 lea eax, [ebp - 0x50]
00518118 movss xmm3, dword ptr [0xb6a5a4]
00518120 movaps xmm1, xmm4
00518123 movss xmm2, dword ptr [0xb6a2cc]
0051812b movaps xmm0, xmm6
0051812e movss xmm5, dword ptr [esi + 4]
00518133 mulss xmm0, xmm2
00518137 mov ecx, dword ptr [0xbfd65c]
0051813d mulss xmm1, xmm3
00518141 push edx
00518142 mulss xmm4, xmm2
00518146 mov ecx, dword ptr [ecx + 0x18190]
0051814c addss xmm1, xmm0
00518150 movaps xmm0, xmm5
00518153 mulss xmm0, xmm3
00518157 push edx
00518158 push edx
00518159 mulss xmm5, xmm2
0051815d push edx
0051815e movss dword ptr [ebp - 0x50], xmm1
00518163 movaps xmm1, xmm7
00518166 mulss xmm1, xmm2
0051816a push 1
0051816c push eax
0051816d lea eax, [ebp - 0x58]
00518170 addss xmm1, xmm0
00518174 movaps xmm0, xmm6
00518177 mulss xmm0, xmm3
0051817b push eax
0051817c addss xmm4, xmm0
00518180 movss dword ptr [ebp - 0x4c], xmm1
00518185 movaps xmm0, xmm7
00518188 mulss xmm0, xmm3
0051818c movss dword ptr [ebp - 0x58], xmm4
00518191 addss xmm0, xmm5
00518195 movss dword ptr [ebp - 0x54], xmm0
0051819a call 0x7af4b0
0051819f test al, al
005181a1 je 0x5181c7
005181a3 movss xmm6, dword ptr [ebp - 0x3c]
005181a8 movss xmm7, dword ptr [ebp - 0x44]
005181ad movss dword ptr [edi + 0x28c], xmm6
005181b5 movss dword ptr [edi + 0x290], xmm7
005181bd mov dword ptr [edi + 0x360], 0xf
005181c7 mov eax, dword ptr [edi + 0x28]
005181ca cmp eax, 0xd7
005181cf je 0x5181e3
005181d1 cmp eax, 0xfa
005181d6 je 0x5181e3
005181d8 cmp eax, 0x365
005181dd jne 0x5183b5
005181e3 call 0x6c3d90
005181e8 xor edx, edx
005181ea mov ecx, 3
005181ef div ecx
005181f1 test edx, edx
005181f3 jne 0x5183b5
005181f9 push dword ptr [ebp - 0x34]
005181fc mov ecx, dword ptr [0xbfd65c]
00518202 push dword ptr [ebp - 0x38]
00518205 mov ecx, dword ptr [ecx + 0x18190]
0051820b call 0x7aee40
00518210 test eax, eax
00518212 jne 0x5183b5
00518218 movss xmm0, dword ptr [ebp - 0x3c]
0051821d lea ecx, [edi + 0x3c]
00518220 movss dword ptr [edi + 0x28c], xmm0
00518228 movss xmm0, dword ptr [ebp - 0x44]
0051822d push 1
0051822f push 0xb40338
00518234 movss dword ptr [edi + 0x290], xmm0
0051823c mov dword ptr [edi + 0xab4], 6
00518246 call 0x405740
0051824b test al, al
0051824d je 0x5183b5
00518253 lea ecx, [edi + 0x6c]
00518256 call 0x405330
0051825b mov byte ptr [edi + 0x80], 1
00518262 jmp 0x5183b5
00518267 mov eax, dword ptr [ebp - 0x44]
0051826a sub dword ptr [edi + 0x360], eax
00518270 mov esi, dword ptr [edi + 0x70]
00518273 test esi, esi
00518275 je 0x5182c1
00518277 cmp dword ptr [esi + 0x14], 0x10
0051827b mov eax, esi
0051827d jb 0x518281
0051827f mov eax, dword ptr [esi]
00518281 mov ecx, 0xb41264
00518286 mov dl, byte ptr [eax]
00518288 cmp dl, byte ptr [ecx]
0051828a jne 0x5182a6
0051828c test dl, dl
0051828e je 0x5182a2
00518290 mov dl, byte ptr [eax + 1]
00518293 cmp dl, byte ptr [ecx + 1]
00518296 jne 0x5182a6
00518298 add eax, 2
0051829b add ecx, 2
0051829e test dl, dl
005182a0 jne 0x518286
005182a2 xor eax, eax
005182a4 jmp 0x5182ab
005182a6 sbb eax, eax
005182a8 or eax, 1
005182ab test eax, eax
005182ad jne 0x5182c1
005182af cmp byte ptr [esi + 0x34], al
005182b2 je 0x5182e2
005182b4 cmp byte ptr [edi + 0x80], al
005182ba lea esi, [edi + 0x3c]
005182bd jne 0x5182e2
005182bf jmp 0x5182c4
005182c1 lea esi, [edi + 0x3c]
005182c4 push 1
005182c6 push 0xb41264
005182cb mov ecx, esi
005182cd call 0x405740
005182d2 test al, al
005182d4 je 0x5182e2
005182d6 lea ecx, [esi + 0x30]
005182d9 call 0x405330
005182de mov byte ptr [esi + 0x44], 1
005182e2 cmp dword ptr [edi + 0x28], 0x365
005182e9 movss xmm0, dword ptr [0xb6a910]
005182f1 movss dword ptr [ebp - 0x3c], xmm0
005182f6 jne 0x518305
005182f8 movss xmm0, dword ptr [0xb6a8e8]
00518300 movss dword ptr [ebp - 0x3c], xmm0
00518305 cmp dword ptr [edi + 0xe6c], -1
0051830c je 0x51845f
00518312 mulss xmm0, dword ptr [0xb6a560]
0051831a push 1
0051831c push 0
0051831e push ecx
0051831f movss dword ptr [esp], xmm0
00518324 lea ecx, [edi + 0x364]
0051832a push 0xc02fec
0051832f call 0x7a3650
00518334 mov eax, dword ptr [edi + 0x294]
0051833a mov dword ptr [edi + 0x28c], eax
00518340 mov eax, dword ptr [edi + 0x298]
00518346 mov dword ptr [edi + 0x290], eax
0051834c cmp dword ptr [edi + 0x360], 0
00518353 jl 0x518378
00518355 movss xmm2, dword ptr [0xb6a2cc]
0051835d lea eax, [ebp - 0x50]
00518360 push 0xc02fec
00518365 push eax
00518366 mov ecx, edi
00518368 call 0x6af0c0
0051836d mov ecx, eax
0051836f call 0x962c70
00518374 test al, al
00518376 je 0x5183a2
00518378 movss xmm0, dword ptr [0xc02fec]
00518380 movss dword ptr [edi + 0x28c], xmm0
00518388 movss xmm0, dword ptr [0xc02ff0]
00518390 movss dword ptr [edi + 0x290], xmm0
00518398 mov dword ptr [edi + 0x360], 0
005183a2 xorps xmm5, xmm5
005183a5 comiss xmm5, dword ptr [edi + 0x2b8]
005183ac seta al
005183af mov byte ptr [edi + 0x13c], al
005183b5 movss xmm0, dword ptr [edi + 0x2c4]
005183bd mulss xmm0, dword ptr [0xb6a4c4]
005183c5 movss dword ptr [edi + 0x2c4], xmm0
005183cd cmp byte ptr [edi + 0x16b], 0
005183d4 je 0x5185b9
005183da mov eax, dword ptr [edi + 0x28]
005183dd cmp eax, 0xfa
005183e2 jne 0x51857d
005183e8 movups xmm0, xmmword ptr [0xbfec58]
005183ef mov ecx, dword ptr [0xbfd65c]
005183f5 lea esi, [edi + 0x294]
005183fb push 0
005183fd push 0
005183ff push 4
00518401 sub esp, 0x10
00518404 mov eax, esp
00518406 push edi
00518407 push 1
00518409 sub esp, 8
0051840c movups xmmword ptr [eax], xmm0
0051840f mov dword ptr [esp + 4], 0x42700000
00518417 mov dword ptr [esp], 0x42200000
0051841e push esi
0051841f call 0x6d1750
00518424 movss xmm2, dword ptr [0xb6a614]
0051842c mov ecx, dword ptr [0xbfd65c]
00518432 push esi
00518433 call 0x6d5600
00518438 call 0x6c3d90
0051843d mov ecx, dword ptr [0xbfd65c]
00518443 push eax
00518444 push 0
00518446 push 0
00518448 push 0xc02fec
0051844d push esi
0051844e push 1
00518450 push 0x3e8
00518455 call 0x422e20
0051845a jmp 0x5185b9
0051845f movss xmm1, dword ptr [edi + 0x28c]
00518467 subss xmm1, dword ptr [edi + 0x294]
0051846f movss xmm0, dword ptr [edi + 0x290]
00518477 subss xmm0, dword ptr [edi + 0x298]
0051847f movss dword ptr [ebp - 0x58], xmm1
00518484 mulss xmm1, xmm1
00518488 movss dword ptr [ebp - 0x54], xmm0
0051848d mulss xmm0, xmm0
00518491 addss xmm0, xmm1
00518495 call 0x4228c0
0051849a movss xmm1, dword ptr [0xb6a9a0]
005184a2 comiss xmm1, xmm0
005184a5 ja 0x5184de
005184a7 movss xmm1, dword ptr [edi + 0x2bc]
005184af movss xmm0, dword ptr [edi + 0x2b8]
005184b7 mulss xmm0, xmm0
005184bb mulss xmm1, xmm1
005184bf addss xmm0, xmm1
005184c3 call 0x4228c0
005184c8 movss xmm1, dword ptr [0xb6a864]
005184d0 comiss xmm1, xmm0
005184d3 jbe 0x518508
005184d5 cmp dword ptr [edi + 0x360], 0
005184dc jge 0x518508
005184de movss xmm0, dword ptr [0xc02fec]
005184e6 movss dword ptr [edi + 0x28c], xmm0
005184ee movss xmm0, dword ptr [0xc02ff0]
005184f6 movss dword ptr [edi + 0x290], xmm0
005184fe mov dword ptr [edi + 0x360], 0
00518508 lea eax, [ebp - 0x48]
0051850b push eax
0051850c lea ecx, [ebp - 0x58]
0051850f call 0x962560
00518514 movss xmm3, dword ptr [edi + 0x2c4]
0051851c xorps xmm5, xmm5
0051851f movss xmm2, dword ptr [ebp - 0x3c]
00518524 ucomiss xmm3, xmm5
00518527 movaps xmm4, xmm2
0051852a mulss xmm2, dword ptr [eax + 4]
0051852f mulss xmm4, dword ptr [eax]
00518533 lahf 
00518534 test ah, 0x44
00518537 jnp 0x5183a5
0051853d movss xmm1, dword ptr [edi + 0x2f4]
00518545 movaps xmm0, xmm1
00518548 mulss xmm1, xmm2
0051854c mulss xmm0, xmm4
00518550 divss xmm1, xmm3
00518554 divss xmm0, xmm3
00518558 addss xmm1, dword ptr [edi + 0x2bc]
00518560 addss xmm0, dword ptr [edi + 0x2b8]
00518568 movss dword ptr [edi + 0x2bc], xmm1
00518570 movss dword ptr [edi + 0x2b8], xmm0
00518578 jmp 0x5183a5
0051857d cmp eax, 0x365
00518582 jne 0x5185b9
00518584 push 0
00518586 push 3
00518588 mov edx, 4
0051858d mov ecx, 0x516df0
00518592 call 0x5ed350
00518597 mov ecx, dword ptr [edi + 0x294]
0051859d add esp, 8
005185a0 mov edx, dword ptr [eax]
005185a2 mov dword ptr [eax + 0x294], ecx
005185a8 mov ecx, dword ptr [edi + 0x298]
005185ae mov dword ptr [eax + 0x298], ecx
005185b4 mov ecx, eax
005185b6 call dword ptr [edx + 0xc]
005185b9 mov ecx, dword ptr [ebp - 0xc]
005185bc mov dword ptr fs:[0], ecx
005185c3 pop ecx
005185c4 pop edi
005185c5 pop esi
005185c6 mov ecx, dword ptr [ebp - 0x14]
005185c9 xor ecx, ebp
005185cb call 0x9eacd7
005185d0 mov esp, ebp
005185d2 pop ebp
005185d3 mov esp, ebx
005185d5 pop ebx
005185d6 ret 
