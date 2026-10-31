00525830 push ebx
00525831 mov ebx, esp
00525833 sub esp, 8
00525836 and esp, 0xfffffff8
00525839 add esp, 4
0052583c push ebp
0052583d mov ebp, dword ptr [ebx + 4]
00525840 mov dword ptr [esp + 4], ebp
00525844 mov ebp, esp
00525846 push -1
00525848 push 0x9ef7dd
0052584d mov eax, dword ptr fs:[0]
00525853 push eax
00525854 push ebx
00525855 sub esp, 0x128
0052585b mov eax, dword ptr [0xbaa3b4]
00525860 xor eax, ebp
00525862 mov dword ptr [ebp - 0x14], eax
00525865 push esi
00525866 push edi
00525867 push eax
00525868 lea eax, [ebp - 0xc]
0052586b mov dword ptr fs:[0], eax
00525871 mov edi, ecx
00525873 mov ecx, dword ptr [edi + 0x28]
00525876 cmp ecx, 0xe2
0052587c jne 0x525890
0052587e cmp dword ptr [edi + 0x2c], 2
00525882 jne 0x525890
00525884 mov ecx, edi
00525886 call 0x536d10
0052588b jmp 0x52689f
00525890 mov eax, dword ptr [edi + 0xab4]
00525896 test eax, eax
00525898 jne 0x525977
0052589e mov dword ptr [edi + 0xab4], 4
005258a8 cmp ecx, 0xe2
005258ae jne 0x5258c1
005258b0 push eax
005258b1 push 0xb41e78
005258b6 lea ecx, [edi + 0x3c]
005258b9 call 0x405a00
005258be mov ecx, dword ptr [edi + 0x28]
005258c1 cmp ecx, 0xe3
005258c7 je 0x5258d5
005258c9 cmp ecx, 0x115
005258cf jne 0x52689f
005258d5 or dword ptr [edi + 0x160], 0x10000
005258df mov eax, dword ptr [edi + 0x164]
005258e5 mov dword ptr [edi + 0x164], eax
005258eb cmp ecx, 0x115
005258f1 jne 0x52592c
005258f3 xorps xmm0, xmm0
005258f6 mov dword ptr [ebp - 0x38], 0
005258fd movups xmmword ptr [ebp - 0x48], xmm0
00525901 lea eax, [ebp - 0x58]
00525904 mov dword ptr [ebp - 0x34], 0
0052590b movaps xmm0, xmmword ptr [0xb6c110]
00525912 lea ecx, [edi + 0x1dc]
00525918 push eax
00525919 mov dword ptr [ebp - 0x30], 0
00525920 movups xmmword ptr [ebp - 0x58], xmm0
00525924 call 0x4021a0
00525929 mov ecx, dword ptr [edi + 0x28]
0052592c cmp ecx, 0xe3
00525932 jne 0x52689f
00525938 cmp dword ptr [edi + 0x2c], 1
0052593c jne 0x52689f
00525942 push 1
00525944 push 0xb4332c
00525949 lea ecx, [edi + 0x3c]
0052594c mov byte ptr [edi + 0xac], 1
00525953 call 0x405bb0
00525958 test al, al
0052595a je 0x52689f
00525960 lea ecx, [edi + 0x8c]
00525966 call 0x405330
0052596b mov byte ptr [edi + 0xa0], 1
00525972 jmp 0x52689f
00525977 cmp eax, 4
0052597a jne 0x526211
00525980 cmp ecx, 0xe2
00525986 jne 0x525c20
0052598c push dword ptr [edi + 0x20]
0052598f mov ecx, edi
00525991 push 0x14
00525993 call 0x684790
00525998 test al, al
0052599a je 0x5259ec
0052599c call 0x6c3d90
005259a1 xor edx, edx
005259a3 mov ecx, 3
005259a8 div ecx
005259aa test edx, edx
005259ac jne 0x5259ec
005259ae mov ecx, edi
005259b0 call 0x695680
005259b5 push eax
005259b6 mov ecx, edi
005259b8 call 0x6aeb40
005259bd test al, al
005259bf je 0x5259ec
005259c1 push ecx
005259c2 xor eax, eax
005259c4 mov dword ptr [esp], 0x3f800000
005259cb cmp dword ptr [edi + 0x2c], eax
005259ce push 0
005259d0 sete al
005259d3 push 0x78
005259d5 push ecx
005259d6 mov dword ptr [esp], 0x3f4ccccd
005259dd mov ecx, edi
005259df lea eax, [eax*2 + 0xa5]
005259e6 push eax
005259e7 call 0x6ad720
005259ec push 0
005259ee push 0x1000800
005259f3 mov ecx, edi
005259f5 call 0x4122f0
005259fa test al, al
005259fc je 0x525a5d
005259fe cmp dword ptr [edi + 0xe6c], -1
00525a05 jne 0x525a5d
00525a07 mov ecx, edi
00525a09 call 0x695680
00525a0e push 0
00525a10 mov ecx, dword ptr [eax + 0x294]
00525a16 mov eax, dword ptr [eax + 0x298]
00525a1c mov dword ptr [ebp - 0x108], eax
00525a22 lea eax, [ebp - 0x10c]
00525a28 mov dword ptr [ebp - 0x10c], ecx
00525a2e lea ecx, [edi + 0x364]
00525a34 push eax
00525a35 call 0x7a4830
00525a3a cmp dword ptr [edi + 0xaa0], 0
00525a41 jle 0x525a90
00525a43 movss xmm0, dword ptr [edi + 0x2c4]
00525a4b mulss xmm0, dword ptr [0xb6a560]
00525a53 movss dword ptr [edi + 0x2c4], xmm0
00525a5b jmp 0x525a90
00525a5d push 1
00525a5f push 0x384
00525a64 sub esp, 8
00525a67 lea eax, [ebp - 0x124]
00525a6d mov ecx, edi
00525a6f mov dword ptr [esp + 4], 0x3f000000
00525a77 mov dword ptr [esp], 0
00525a7e push eax
00525a7f call 0x695a30
00525a84 push eax
00525a85 lea ecx, [edi + 0x364]
00525a8b call 0x7a3650
00525a90 mov eax, dword ptr [0xb404ec]
00525a95 mov ecx, dword ptr [0xb404f0]
00525a9b mov dword ptr [ebp - 0x30], 0xf
00525aa2 mov dword ptr [ebp - 0x34], 8
00525aa9 mov dword ptr [ebp - 0x44], eax
00525aac mov dword ptr [ebp - 0x40], ecx
00525aaf mov byte ptr [ebp - 0x3c], 0
00525ab3 mov dword ptr [ebp - 4], 0
00525aba mov eax, dword ptr [0xb40504]
00525abf mov ecx, dword ptr [0xb40508]
00525ac5 mov dword ptr [ebp - 0x18], 0xf
00525acc mov dword ptr [ebp - 0x1c], 8
00525ad3 mov dword ptr [ebp - 0x2c], eax
00525ad6 mov dword ptr [ebp - 0x28], ecx
00525ad9 mov byte ptr [ebp - 0x24], 0
00525add push ecx
00525ade mov byte ptr [ebp - 4], 1
00525ae2 lea eax, [ebp - 0x44]
00525ae5 mov dword ptr [esp], 0x3dcccccd
00525aec mov ecx, edi
00525aee push eax
00525aef lea eax, [ebp - 0x2c]
00525af2 push eax
00525af3 call 0x6980a0
00525af8 mov byte ptr [ebp - 4], 0
00525afc mov edx, dword ptr [ebp - 0x18]
00525aff cmp edx, 0x10
00525b02 jb 0x525b2c
00525b04 mov ecx, dword ptr [ebp - 0x2c]
00525b07 inc edx
00525b08 mov eax, ecx
00525b0a cmp edx, 0x1000
00525b10 jb 0x525b22
00525b12 mov ecx, dword ptr [ecx - 4]
00525b15 add edx, 0x23
00525b18 sub eax, ecx
00525b1a add eax, -4
00525b1d cmp eax, 0x1f
00525b20 ja 0x525b6b
00525b22 push edx
00525b23 push ecx
00525b24 call 0x9eb08e
00525b29 add esp, 8
00525b2c mov dword ptr [ebp - 4], 0xffffffff
00525b33 mov edx, dword ptr [ebp - 0x30]
00525b36 mov dword ptr [ebp - 0x1c], 0
00525b3d mov dword ptr [ebp - 0x18], 0xf
00525b44 mov byte ptr [ebp - 0x2c], 0
00525b48 cmp edx, 0x10
00525b4b jb 0x525b7b
00525b4d mov ecx, dword ptr [ebp - 0x44]
00525b50 inc edx
00525b51 mov eax, ecx
00525b53 cmp edx, 0x1000
00525b59 jb 0x525b71
00525b5b mov ecx, dword ptr [ecx - 4]
00525b5e add edx, 0x23
00525b61 sub eax, ecx
00525b63 add eax, -4
00525b66 cmp eax, 0x1f
00525b69 jbe 0x525b71
00525b6b call dword ptr [0xa065ac]
00525b71 push edx
00525b72 push ecx
00525b73 call 0x9eb08e
00525b78 add esp, 8
00525b7b push dword ptr [edi + 0x20]
00525b7e mov ecx, edi
00525b80 push 7
00525b82 call 0x684790
00525b87 test al, al
00525b89 je 0x5266a2
00525b8f call 0x6c3d90
00525b94 mov ecx, dword ptr [0xbfd65c]
00525b9a push 0
00525b9c push 0xbeaaec
00525ba1 push 0xbeab18
00525ba6 push 0
00525ba8 push eax
00525ba9 push 0
00525bab push edi
00525bac push 0xc02fec
00525bb1 lea eax, [edi + 0x294]
00525bb7 push eax
00525bb8 push 0x16
00525bba push 0x3e8
00525bbf call 0x422e20
00525bc4 push eax
00525bc5 call 0x9ec34c
00525bca movss xmm1, dword ptr [0xbc7a28]
00525bd2 add esp, 0x14
00525bd5 movss xmm0, dword ptr [0xbc7a2c]
00525bdd mulss xmm1, dword ptr [0xb6a2cc]
00525be5 mov dword ptr [eax + 0x3c8], 0x3f000000
00525bef mulss xmm0, dword ptr [0xb6a2cc]
00525bf7 mov dword ptr [eax + 0x3ac], 0x1e
00525c01 movss dword ptr [eax + 0xd8], xmm1
00525c09 mov dword ptr [eax + 0x3b0], 0x1e
00525c13 movss dword ptr [eax + 0xdc], xmm0
00525c1b jmp 0x5266a2
00525c20 cmp ecx, 0xe3
00525c26 je 0x525c34
00525c28 cmp ecx, 0x115
00525c2e jne 0x5266a2
00525c34 push dword ptr [edi + 0x20]
00525c37 mov ecx, edi
00525c39 push 0x1e
00525c3b call 0x684790
00525c40 test al, al
00525c42 je 0x525c72
00525c44 call 0x6c3d90
00525c49 xor edx, edx
00525c4b mov ecx, 3
00525c50 div ecx
00525c52 test edx, edx
00525c54 jne 0x525c72
00525c56 push ecx
00525c57 mov dword ptr [esp], 0x3f800000
00525c5e push edx
00525c5f push 0x78
00525c61 push ecx
00525c62 mov dword ptr [esp], 0x3f4ccccd
00525c69 mov ecx, edi
00525c6b push 0x74
00525c6d call 0x6ad720
00525c72 mov eax, dword ptr [0xbfd65c]
00525c77 lea ecx, [edi + 0x294]
00525c7d push 0x384
00525c82 mov dword ptr [ebp - 0x108], ecx
00525c88 push ecx
00525c89 mov esi, dword ptr [eax + 0x18190]
00525c8f mov ecx, esi
00525c91 call 0x7ce950
00525c96 push eax
00525c97 mov ecx, esi
00525c99 call 0x447f40
00525c9e lea ecx, [edi + 0x364]
00525ca4 call 0x7a6e20
00525ca9 push 0
00525cab push ecx
00525cac lea ecx, [edi + 0x364]
00525cb2 mov dword ptr [esp], 0x3fa00000
00525cb9 call 0x7a51e0
00525cbe movss xmm4, dword ptr [edi + 0x2b8]
00525cc6 xorps xmm2, xmm2
00525cc9 movss xmm1, dword ptr [edi + 0x2bc]
00525cd1 movaps xmm0, xmm4
00525cd4 movss xmm3, dword ptr [0xb6c980]
00525cdc mulss xmm1, xmm1
00525ce0 mulss xmm0, xmm4
00525ce4 addss xmm0, xmm1
00525ce8 movss xmm1, dword ptr [0xb6a614]
00525cf0 comiss xmm1, xmm0
00525cf3 jbe 0x525d09
00525cf5 push 0
00525cf7 push 0xb40800
00525cfc lea ecx, [edi + 0x3c]
00525cff call 0x405850
00525d04 jmp 0x525d95
00525d09 movss xmm5, dword ptr [edi + 0x2bc]
00525d11 movaps xmm1, xmm4
00525d14 movaps xmm0, xmm5
00525d17 andps xmm1, xmm3
00525d1a andps xmm0, xmm3
00525d1d comiss xmm1, xmm0
00525d20 jbe 0x525d7a
00525d22 cmp dword ptr [edi + 0x28], 0xe3
00525d29 jne 0x525d56
00525d2b cmp dword ptr [edi + 0x2c], 1
00525d2f jne 0x525d56
00525d31 comiss xmm2, xmm4
00525d34 mov ecx, 0xb41040
00525d39 mov eax, 0xb4104c
00525d3e push 0
00525d40 cmovbe eax, ecx
00525d43 lea ecx, [edi + 0x3c]
00525d46 push eax
00525d47 call 0x4054f0
00525d4c xor al, al
00525d4e mov byte ptr [edi + 0x13c], al
00525d54 jmp 0x525d95
00525d56 push 0
00525d58 push 0xb40504
00525d5d lea ecx, [edi + 0x3c]
00525d60 call 0x4054f0
00525d65 xorps xmm0, xmm0
00525d68 comiss xmm0, dword ptr [edi + 0x2b8]
00525d6f seta al
00525d72 mov byte ptr [edi + 0x13c], al
00525d78 jmp 0x525d95
00525d7a comiss xmm5, xmm2
00525d7d lea ecx, [edi + 0x3c]
00525d80 push 0
00525d82 jbe 0x525d8b
00525d84 push 0xb40800
00525d89 jmp 0x525d90
00525d8b push 0xb407dc
00525d90 call 0x4054f0
00525d95 cmp dword ptr [edi + 0xe6c], -1
00525d9c mov ecx, edi
00525d9e je 0x525f48
00525da4 push 0
00525da6 push 0x1000a00
00525dab call 0x4122f0
00525db0 test al, al
00525db2 jne 0x5266a2
00525db8 movss xmm1, dword ptr [0xb6accc]
00525dc0 mov ecx, edi
00525dc2 push 7
00525dc4 push 0
00525dc6 call 0x6a15a0
00525dcb test al, al
00525dcd jne 0x525e0a
00525dcf push 9
00525dd1 mov ecx, edi
00525dd3 call 0x6af050
00525dd8 test al, al
00525dda je 0x5266a2
00525de0 lea esi, [edi + 0x294]
00525de6 push esi
00525de7 push ecx
00525de8 lea eax, [ebp - 0x11c]
00525dee mov ecx, edi
00525df0 push eax
00525df1 call 0x6afac0
00525df6 add esp, 4
00525df9 mov ecx, eax
00525dfb call 0x962ca0
00525e00 test al, al
00525e02 je 0x5266a2
00525e08 jmp 0x525e10
00525e0a lea esi, [edi + 0x294]
00525e10 movss xmm2, dword ptr [0xb6ab70]
00525e18 mov ecx, edi
00525e1a push 0
00525e1c call 0x6af8d0
00525e21 push 1
00525e23 mov ecx, edi
00525e25 mov dword ptr [edi + 0xab4], 8
00525e2f mov dword ptr [edi + 0x360], 0
00525e39 call 0x6afe20
00525e3e push esi
00525e3f push ecx
00525e40 lea eax, [ebp - 0x124]
00525e46 mov ecx, edi
00525e48 push eax
00525e49 call 0x6afac0
00525e4e add esp, 4
00525e51 mov ecx, eax
00525e53 call 0x962ca0
00525e58 test al, al
00525e5a je 0x525e8e
00525e5c lea eax, [ebp - 0x114]
00525e62 mov ecx, edi
00525e64 push eax
00525e65 call 0x6afac0
00525e6a movss xmm0, dword ptr [eax]
00525e6e subss xmm0, dword ptr [esi]
00525e72 movss dword ptr [ebp - 0x10c], xmm0
00525e7a movss xmm0, dword ptr [eax + 4]
00525e7f subss xmm0, dword ptr [esi + 4]
00525e84 movss dword ptr [ebp - 0x108], xmm0
00525e8c jmp 0x525ea6
00525e8e mov eax, dword ptr [edi + 0xe70]
00525e94 mov ecx, dword ptr [edi + 0xe74]
00525e9a mov dword ptr [ebp - 0x10c], eax
00525ea0 mov dword ptr [ebp - 0x108], ecx
00525ea6 lea eax, [ebp - 0x10c]
00525eac movss xmm2, dword ptr [eax]
00525eb0 movss xmm4, dword ptr [eax + 4]
00525eb5 movaps xmm1, xmm2
00525eb8 andps xmm1, xmmword ptr [0xb6c980]
00525ebf movaps xmm0, xmm4
00525ec2 andps xmm0, xmmword ptr [0xb6c980]
00525ec9 comiss xmm1, xmm0
00525ecc jbe 0x525f27
00525ece cmp dword ptr [edi + 0x28], 0xe3
00525ed5 jne 0x525ef9
00525ed7 cmp dword ptr [edi + 0x2c], 1
00525edb jne 0x525ef9
00525edd xorps xmm0, xmm0
00525ee0 mov byte ptr [ebp - 0x101], 0
00525ee7 comiss xmm0, xmm2
00525eea mov eax, 0xb429bc
00525eef mov ecx, 0xb427d8
00525ef4 cmovbe eax, ecx
00525ef7 jmp 0x525f0b
00525ef9 xorps xmm0, xmm0
00525efc mov eax, 0xb4277c
00525f01 comiss xmm0, xmm2
00525f04 seta byte ptr [ebp - 0x101]
00525f0b push 0
00525f0d push eax
00525f0e lea ecx, [edi + 0x3c]
00525f11 call 0x4054f0
00525f16 mov al, byte ptr [ebp - 0x101]
00525f1c mov byte ptr [edi + 0x13c], al
00525f22 jmp 0x5266a2
00525f27 comiss xmm4, dword ptr [0xb6a18c]
00525f2e lea ecx, [edi + 0x3c]
00525f31 push 0
00525f33 jbe 0x526202
00525f39 push 0xb427a0
00525f3e call 0x4054f0
00525f43 jmp 0x5266a2
00525f48 push dword ptr [edi + 0x20]
00525f4b push 3
00525f4d call 0x684790
00525f52 test al, al
00525f54 je 0x5266a2
00525f5a cmp dword ptr [edi + 0x34], 0x38a
00525f61 je 0x5266a2
00525f67 push 0
00525f69 push 0x1000a00
00525f6e mov ecx, edi
00525f70 call 0x4122f0
00525f75 test al, al
00525f77 jne 0x5266a2
00525f7d push 0
00525f7f push 0x20000000
00525f84 mov ecx, edi
00525f86 call 0x4122f0
00525f8b test al, al
00525f8d je 0x525fa0
00525f8f mov ecx, edi
00525f91 call 0x695680
00525f96 cmp dword ptr [eax + 0x28], 1
00525f9a je 0x5266a2
00525fa0 call 0x6c3d90
00525fa5 mov ecx, edi
00525fa7 movd xmm0, eax
00525fab cvtdq2pd xmm0, xmm0
00525faf shr eax, 0x1f
00525fb2 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
00525fbb cvtpd2ps xmm0, xmm0
00525fbf mulss xmm0, dword ptr [0xb6a19c]
00525fc7 mulss xmm0, dword ptr [0xb6a9b0]
00525fcf movss dword ptr [ebp - 0x128], xmm0
00525fd7 call 0x695680
00525fdc mov ecx, edi
00525fde movss xmm0, dword ptr [eax + 0x2b8]
00525fe6 movss dword ptr [ebp - 0x110], xmm0
00525fee movss xmm0, dword ptr [eax + 0x2bc]
00525ff6 movss dword ptr [ebp - 0x118], xmm0
00525ffe call 0x695680
00526003 movss xmm0, dword ptr [ebp - 0x110]
0052600b sub esp, 0xc
0052600e mulss xmm0, dword ptr [ebp - 0x128]
00526016 mov esi, dword ptr [0xbfd65c]
0052601c movss xmm3, dword ptr [0xb6a9c8]
00526024 mov dword ptr [esp + 8], 0x41a00000
0052602c addss xmm0, dword ptr [eax + 0x294]
00526034 mov ecx, dword ptr [esi + 0x18190]
0052603a mov dword ptr [esp + 4], 0x41a00000
00526042 mov dword ptr [esp], 0x41a00000
00526049 movss dword ptr [ebp - 0x114], xmm0
00526051 movss xmm0, dword ptr [ebp - 0x118]
00526059 mulss xmm0, dword ptr [ebp - 0x128]
00526061 addss xmm0, dword ptr [eax + 0x298]
00526069 lea eax, [ebp - 0x114]
0052606f push eax
00526070 lea eax, [ebp - 0x11c]
00526076 push eax
00526077 movss dword ptr [ebp - 0x110], xmm0
0052607f call 0x7cec10
00526084 mov esi, dword ptr [esi + 0x18190]
0052608a mov eax, dword ptr [edi + 0x384]
00526090 cdq 
00526091 movss xmm0, dword ptr [0xb6aa3c]
00526099 mov ecx, dword ptr [esi + 0xc]
0052609c idiv ecx
0052609e movss xmm3, dword ptr [0xb6c980]
005260a6 movss xmm5, dword ptr [0xb6a9c8]
005260ae movd xmm4, edx
005260b2 cvtdq2ps xmm4, xmm4
005260b5 movd xmm2, eax
005260b9 mulss xmm4, xmm0
005260bd cvtdq2ps xmm2, xmm2
005260c0 addss xmm4, xmm0
005260c4 mulss xmm2, xmm0
005260c8 addss xmm2, dword ptr [0xb6ab20]
005260d0 movss dword ptr [ebp - 0x114], xmm4
005260d8 subss xmm4, dword ptr [ebp - 0x11c]
005260e0 movss dword ptr [ebp - 0x110], xmm2
005260e8 subss xmm2, dword ptr [ebp - 0x118]
005260f0 movaps xmm0, xmm4
005260f3 andps xmm0, xmm3
005260f6 comiss xmm5, xmm0
005260f9 ja 0x52610a
005260fb movaps xmm1, xmm2
005260fe andps xmm1, xmm3
00526101 comiss xmm5, xmm1
00526104 jbe 0x5266a2
0052610a mulss xmm2, xmm2
0052610e mulss xmm4, xmm4
00526112 addss xmm2, xmm4
00526116 movaps xmm0, xmm2
00526119 call 0x4228c0
0052611e movss xmm1, dword ptr [0xb6aba8]
00526126 comiss xmm1, xmm0
00526129 jbe 0x5266a2
0052612f push 0
00526131 push 0
00526133 push 0
00526135 push 0x3e7
0052613a push 3
0052613c lea eax, [ebp - 0x11c]
00526142 mov ecx, esi
00526144 push eax
00526145 lea eax, [ebp - 0x114]
0052614b push eax
0052614c call 0x7af4b0
00526151 test al, al
00526153 je 0x5266a2
00526159 mov esi, dword ptr [ebp - 0x108]
0052615f movss xmm3, dword ptr [ebp - 0x11c]
00526167 movss xmm4, dword ptr [ebp - 0x118]
0052616f mov dword ptr [edi + 0xab4], 8
00526179 mov dword ptr [edi + 0x360], 0
00526183 subss xmm3, dword ptr [esi]
00526187 subss xmm4, dword ptr [esi + 4]
0052618c movaps xmm1, xmm3
0052618f andps xmm1, xmmword ptr [0xb6c980]
00526196 movaps xmm0, xmm4
00526199 andps xmm0, xmmword ptr [0xb6c980]
005261a0 comiss xmm1, xmm0
005261a3 jbe 0x525f27
005261a9 cmp dword ptr [edi + 0x28], 0xe3
005261b0 jne 0x5261d4
005261b2 cmp dword ptr [edi + 0x2c], 1
005261b6 jne 0x5261d4
005261b8 xorps xmm0, xmm0
005261bb mov byte ptr [ebp - 0x101], 0
005261c2 comiss xmm0, xmm3
005261c5 mov eax, 0xb429bc
005261ca mov ecx, 0xb427d8
005261cf cmovbe eax, ecx
005261d2 jmp 0x5261e6
005261d4 xorps xmm0, xmm0
005261d7 mov eax, 0xb4277c
005261dc comiss xmm0, xmm3
005261df seta byte ptr [ebp - 0x101]
005261e6 push 0
005261e8 push eax
005261e9 lea ecx, [edi + 0x3c]
005261ec call 0x4054f0
005261f1 mov al, byte ptr [ebp - 0x101]
005261f7 mov byte ptr [edi + 0x13c], al
005261fd jmp 0x5266a2
00526202 push 0xb42794
00526207 call 0x4054f0
0052620c jmp 0x5266a2
00526211 cmp eax, 8
00526214 jne 0x5266a2
0052621a movss xmm2, dword ptr [0xb6ab70]
00526222 mov ecx, edi
00526224 push 0
00526226 call 0x6af8d0
0052622b lea eax, [ebp - 0x138]
00526231 mov ecx, edi
00526233 push eax
00526234 lea esi, [edi + 0x294]
0052623a call 0x6afac0
0052623f movss xmm0, dword ptr [eax]
00526243 subss xmm0, dword ptr [esi]
00526247 movss xmm1, dword ptr [eax + 4]
0052624c subss xmm1, dword ptr [esi + 4]
00526251 ucomiss xmm0, dword ptr [0xc02fec]
00526258 movss dword ptr [ebp - 0x10c], xmm0
00526260 movss dword ptr [ebp - 0x108], xmm1
00526268 lahf 
00526269 test ah, 0x44
0052626c jp 0x52627b
0052626e ucomiss xmm1, dword ptr [0xc02ff0]
00526275 lahf 
00526276 test ah, 0x44
00526279 jnp 0x52629e
0052627b lea eax, [ebp - 0x130]
00526281 push eax
00526282 lea ecx, [ebp - 0x10c]
00526288 call 0x962560
0052628d mov ecx, dword ptr [eax]
0052628f mov dword ptr [edi + 0xe70], ecx
00526295 mov eax, dword ptr [eax + 4]
00526298 mov dword ptr [edi + 0xe74], eax
0052629e cmp dword ptr [edi + 0x70], 0
005262a2 je 0x5265d6
005262a8 push 0xb400ac
005262ad lea ecx, [edi + 0x6c]
005262b0 call 0x405e90
005262b5 test al, al
005262b7 je 0x5265c3
005262bd cmp dword ptr [edi + 0xe6c], -1
005262c4 je 0x5262f5
005262c6 push 0xc02fec
005262cb lea ecx, [edi + 0xe70]
005262d1 call 0x962ca0
005262d6 test al, al
005262d8 je 0x5262f5
005262da push ecx
005262db lea eax, [ebp - 0x11c]
005262e1 mov dword ptr [esp], 0x41200000
005262e8 push eax
005262e9 call 0x9628d0
005262ee mov ecx, eax
005262f0 jmp 0x526389
005262f5 mov ecx, edi
005262f7 call 0x695680
005262fc movss xmm1, dword ptr [eax + 0x294]
00526304 subss xmm1, dword ptr [esi]
00526308 movss xmm2, dword ptr [eax + 0x298]
00526310 subss xmm2, dword ptr [esi + 4]
00526315 movaps xmm0, xmm1
00526318 movss dword ptr [ebp - 0x128], xmm1
00526320 mulss xmm0, xmm1
00526324 movaps xmm1, xmm2
00526327 movss dword ptr [ebp - 0x110], xmm2
0052632f mulss xmm1, xmm2
00526333 addss xmm0, xmm1
00526337 call 0x4228c0
0052633c comiss xmm0, dword ptr [0xb6a18c]
00526343 lea ecx, [ebp - 0x10c]
00526349 movss xmm2, dword ptr [ebp - 0x110]
00526351 jbe 0x526371
00526353 movss xmm1, dword ptr [0xb6a974]
0052635b divss xmm1, xmm0
0052635f movss xmm0, dword ptr [ebp - 0x128]
00526367 mulss xmm0, xmm1
0052636b mulss xmm2, xmm1
0052636f jmp 0x526379
00526371 movss xmm0, dword ptr [ebp - 0x128]
00526379 movss dword ptr [ebp - 0x108], xmm2
00526381 movss dword ptr [ebp - 0x10c], xmm0
00526389 mov eax, dword ptr [ecx]
0052638b mov ecx, dword ptr [ecx + 4]
0052638e mov dword ptr [ebp - 0x120], ecx
00526394 lea ecx, [ebp - 0x100]
0052639a mov dword ptr [ebp - 0x124], eax
005263a0 call 0x430d70
005263a5 mov eax, dword ptr [edi + 0x28]
005263a8 mov dword ptr [ebp - 0x6c], 1
005263af cmp eax, 0x115
005263b4 jne 0x5263c9
005263b6 movaps xmm0, xmmword ptr [0xb6c1b0]
005263bd movups xmmword ptr [ebp - 0xd4], xmm0
005263c4 jmp 0x52658b
005263c9 cmp eax, 0xe3
005263ce jne 0x52658b
005263d4 cmp dword ptr [edi + 0x2c], 1
005263d8 jne 0x52658b
005263de mov ecx, edi
005263e0 call 0x695680
005263e5 movss xmm1, dword ptr [eax + 0x294]
005263ed movss xmm0, dword ptr [eax + 0x298]
005263f5 subss xmm0, dword ptr [esi + 4]
005263fa subss xmm1, dword ptr [esi]
005263fe mulss xmm0, xmm0
00526402 mulss xmm1, xmm1
00526406 addss xmm0, xmm1
0052640a call 0x4228c0
0052640f push esi
00526410 push ecx
00526411 lea eax, [ebp - 0x10c]
00526417 mov ecx, edi
00526419 push eax
0052641a movaps xmm1, xmm0
0052641d call 0x6afac0
00526422 add esp, 4
00526425 mov ecx, eax
00526427 call 0x962ca0
0052642c test al, al
0052642e je 0x5264af
00526430 lea eax, [ebp - 0x10c]
00526436 mov ecx, edi
00526438 push eax
00526439 call 0x6afac0
0052643e movss xmm1, dword ptr [eax]
00526442 movss xmm0, dword ptr [eax + 4]
00526447 subss xmm0, dword ptr [esi + 4]
0052644c subss xmm1, dword ptr [esi]
00526450 mulss xmm0, xmm0
00526454 mulss xmm1, xmm1
00526458 addss xmm0, xmm1
0052645c call 0x4228c0
00526461 movss xmm1, dword ptr [0xb6a9c8]
00526469 lea eax, [ebp - 0x118]
0052646f comiss xmm1, xmm0
00526472 lea ecx, [ebp - 0x108]
00526478 mov dword ptr [ebp - 0x108], 0x41a00000
00526482 mov dword ptr [ebp - 0x110], 0x43700000
0052648c movss dword ptr [ebp - 0x118], xmm0
00526494 cmovbe ecx, eax
00526497 lea eax, [ebp - 0x110]
0052649d movss xmm0, dword ptr [ecx]
005264a1 comiss xmm0, dword ptr [0xb6abe4]
005264a8 cmovbe eax, ecx
005264ab movss xmm1, dword ptr [eax]
005264af divss xmm1, dword ptr [0xb6a974]
005264b7 mov dword ptr [ebp - 0xa8], 0
005264c1 mov dword ptr [ebp - 0xa4], 0x2000
005264cb movss xmm0, dword ptr [0xb6a5a4]
005264d3 movss dword ptr [ebp - 0x110], xmm1
005264db call 0x4c3f60
005264e0 subss xmm0, dword ptr [0xb6a614]
005264e8 lea ecx, [ebp - 0x118]
005264ee mov dword ptr [ebp - 0x118], 0x3c23d70a
005264f8 lea eax, [ebp - 0x108]
005264fe mulss xmm0, dword ptr [0xb6aeb4]
00526506 comiss xmm0, dword ptr [0xb6a214]
0052650d movss dword ptr [ebp - 0x108], xmm0
00526515 cmovbe eax, ecx
00526518 movss xmm2, dword ptr [eax]
0052651c call 0x6c3d90
00526521 movss xmm3, dword ptr [ebp - 0x110]
00526529 subss xmm3, xmm2
0052652d mov dword ptr [ebp - 0xf4], 0x3f800000
00526537 movd xmm0, eax
0052653b cvtdq2pd xmm0, xmm0
0052653f shr eax, 0x1f
00526542 mulss xmm3, dword ptr [0xb6a984]
0052654a addsd xmm0, qword ptr [eax*8 + 0xb6c940]
00526553 cvtpd2ps xmm1, xmm0
00526557 movss xmm0, dword ptr [0xb6a9bc]
0052655f mulss xmm1, dword ptr [0xb6a19c]
00526567 subss xmm0, xmm3
0052656b mulss xmm1, dword ptr [0xb6a434]
00526573 divss xmm0, xmm2
00526577 addss xmm1, dword ptr [0xb6a560]
0052657f mulss xmm1, xmm0
00526583 movss dword ptr [ebp - 0xf8], xmm1
0052658b push ecx
0052658c mov dword ptr [esp], 0x3f800000
00526593 push 0
00526595 push 2
00526597 push ecx
00526598 mov dword ptr [esp], 0x3f800000
0052659f mov ecx, edi
005265a1 push 0xf9
005265a6 call 0x6ad720
005265ab lea eax, [ebp - 0x100]
005265b1 mov ecx, edi
005265b3 push eax
005265b4 push 0
005265b6 lea eax, [ebp - 0x124]
005265bc push eax
005265bd push esi
005265be call 0x6a1a20
005265c3 cmp dword ptr [edi + 0x70], 0
005265c7 je 0x5265d6
005265c9 cmp byte ptr [edi + 0x80], 0
005265d0 jne 0x52668a
005265d6 cmp dword ptr [edi + 0x28], 0x115
005265dd jne 0x526680
005265e3 cmp dword ptr [edi + 0x360], 2
005265ea jge 0x526680
005265f0 lea eax, [ebp - 0x44]
005265f3 push eax
005265f4 lea ecx, [edi + 0x6c]
005265f7 call 0x444be0
005265fc mov dword ptr [ebp - 4], 2
00526603 cmp dword ptr [eax + 0x14], 0x10
00526607 jb 0x52660b
00526609 mov eax, dword ptr [eax]
0052660b push 1
0052660d push eax
0052660e lea ecx, [edi + 0x3c]
00526611 call 0x405740
00526616 test al, al
00526618 je 0x526629
0052661a lea ecx, [edi + 0x6c]
0052661d call 0x405330
00526622 mov byte ptr [edi + 0x80], 1
00526629 mov dword ptr [ebp - 4], 0xffffffff
00526630 mov edx, dword ptr [ebp - 0x30]
00526633 cmp edx, 0x10
00526636 jb 0x526666
00526638 mov ecx, dword ptr [ebp - 0x44]
0052663b inc edx
0052663c mov eax, ecx
0052663e cmp edx, 0x1000
00526644 jb 0x52665c
00526646 mov ecx, dword ptr [ecx - 4]
00526649 add edx, 0x23
0052664c sub eax, ecx
0052664e add eax, -4
00526651 cmp eax, 0x1f
00526654 jbe 0x52665c
00526656 call dword ptr [0xa065ac]
0052665c push edx
0052665d push ecx
0052665e call 0x9eb08e
00526663 add esp, 8
00526666 inc dword ptr [edi + 0x360]
0052666c mov dword ptr [ebp - 0x34], 0
00526673 mov dword ptr [ebp - 0x30], 0xf
0052667a mov byte ptr [ebp - 0x44], 0
0052667e jmp 0x52668a
00526680 mov dword ptr [edi + 0xab4], 4
0052668a movss xmm0, dword ptr [edi + 0x2c4]
00526692 mulss xmm0, dword ptr [0xb6a3b0]
0052669a movss dword ptr [edi + 0x2c4], xmm0
005266a2 cmp byte ptr [edi + 0x16b], 0
005266a9 je 0x526887
005266af mov eax, dword ptr [edi + 0x28]
005266b2 cmp eax, 0xe2
005266b7 jne 0x52680e
005266bd cmp dword ptr [edi + 0x2c], 1
005266c1 jne 0x526887
005266c7 call 0x6c3d90
005266cc test al, 1
005266ce jne 0x526717
005266d0 push ecx
005266d1 mov dword ptr [esp], 0x3f800000
005266d8 push 0
005266da push 2
005266dc push ecx
005266dd mov dword ptr [esp], 0x3f800000
005266e4 mov ecx, edi
005266e6 push 0x73
005266e8 call 0x6ad720
005266ed push -1
005266ef push 0
005266f1 push 0
005266f3 push 0xe3
005266f8 mov ecx, edi
005266fa call 0x697c60
005266ff mov eax, dword ptr [edi + 0x2dc]
00526705 mov dword ptr [edi + 0x2d8], eax
0052670b mov byte ptr [edi + 0x16b], 0
00526712 jmp 0x526887
00526717 cmp word ptr [edi + 0xbc6], 0
0052671f jne 0x526887
00526725 lea eax, [ebp - 0x130]
0052672b push eax
0052672c call 0x659290
00526731 add esp, 4
00526734 movss xmm0, dword ptr [eax]
00526738 addss xmm0, xmm0
0052673c movss dword ptr [ebp - 0x108], xmm0
00526744 movss dword ptr [ebp - 0x124], xmm0
0052674c movss xmm0, dword ptr [eax + 4]
00526751 addss xmm0, xmm0
00526755 movss dword ptr [ebp - 0x118], xmm0
0052675d movss dword ptr [ebp - 0x120], xmm0
00526765 call 0x6c3d90
0052676a mov ecx, dword ptr [0xbfd65c]
00526770 lea esi, [edi + 0x294]
00526776 push eax
00526777 push 0
00526779 push edi
0052677a lea eax, [ebp - 0x124]
00526780 push eax
00526781 push esi
00526782 push 0
00526784 push 0x12
00526786 call 0x422e20
0052678b mov ecx, dword ptr [eax + 0x164]
00526791 and dword ptr [eax + 0x160], 0xfffffffb
00526798 mov dword ptr [eax + 0x164], ecx
0052679e call 0x6c3d90
005267a3 test al, 1
005267a5 jne 0x526887
005267ab call 0x6c3d90
005267b0 movss xmm1, dword ptr [ebp - 0x108]
005267b8 xorps xmm1, xmmword ptr [0xb6c9b0]
005267bf mov ecx, dword ptr [0xbfd65c]
005267c5 push eax
005267c6 push 0
005267c8 push edi
005267c9 lea eax, [ebp - 0x124]
005267cf movss dword ptr [ebp - 0x124], xmm1
005267d7 movss xmm1, dword ptr [ebp - 0x118]
005267df xorps xmm1, xmmword ptr [0xb6c9b0]
005267e6 push eax
005267e7 push esi
005267e8 push 0
005267ea push 0x12
005267ec movss dword ptr [ebp - 0x120], xmm1
005267f4 call 0x422e20
005267f9 mov ecx, dword ptr [eax + 0x164]
005267ff and dword ptr [eax + 0x160], 0xfffffffb
00526806 mov dword ptr [eax + 0x164], ecx
0052680c jmp 0x526887
0052680e cmp eax, 0x115
00526813 jne 0x526887
00526815 movups xmm0, xmmword ptr [0xbfec58]
0052681c mov ecx, dword ptr [0xbfd65c]
00526822 lea esi, [edi + 0x294]
00526828 push 0
0052682a push 0
0052682c push 4
0052682e sub esp, 0x10
00526831 mov eax, esp
00526833 push edi
00526834 push 1
00526836 sub esp, 8
00526839 movups xmmword ptr [eax], xmm0
0052683c mov dword ptr [esp + 4], 0x42700000
00526844 mov dword ptr [esp], 0x42200000
0052684b push esi
0052684c call 0x6d1750
00526851 movss xmm2, dword ptr [0xb6a614]
00526859 mov ecx, dword ptr [0xbfd65c]
0052685f push esi
00526860 call 0x6d5600
00526865 call 0x6c3d90
0052686a mov ecx, dword ptr [0xbfd65c]
00526870 push eax
00526871 push 0
00526873 push 0
00526875 push 0xc02fec
0052687a push esi
0052687b push 1
0052687d push 0x3e8
00526882 call 0x422e20
00526887 movss xmm0, dword ptr [edi + 0x2c4]
0052688f mulss xmm0, dword ptr [0xb6a560]
00526897 movss dword ptr [edi + 0x2c4], xmm0
0052689f mov ecx, dword ptr [ebp - 0xc]
005268a2 mov dword ptr fs:[0], ecx
005268a9 pop ecx
005268aa pop edi
005268ab pop esi
005268ac mov ecx, dword ptr [ebp - 0x14]
005268af xor ecx, ebp
005268b1 call 0x9eacd7
005268b6 mov esp, ebp
005268b8 pop ebp
005268b9 mov esp, ebx
005268bb pop ebx
005268bc ret 
