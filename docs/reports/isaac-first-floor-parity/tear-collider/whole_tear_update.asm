00642990 push ebp
00642991 mov ebp, esp
00642993 push -1
00642995 push 0x9f1ecf
0064299a mov eax, dword ptr fs:[0]
006429a0 push eax
006429a1 mov eax, 0x21a0
006429a6 call 0x9ebab0
006429ab mov eax, dword ptr [0xbaa3b4]
006429b0 xor eax, ebp
006429b2 mov dword ptr [ebp - 0x10], eax
006429b5 push esi
006429b6 push edi
006429b7 push eax
006429b8 lea eax, [ebp - 0xc]
006429bb mov dword ptr fs:[0], eax
006429c1 mov edi, ecx
006429c3 mov dword ptr [ebp - 0x6a8], edi
006429c9 cmp byte ptr [edi + 0x3ba], 0
006429d0 je 0x6429de
006429d2 call 0x642660
006429d7 mov byte ptr [edi + 0x3ba], 0
006429de lea eax, [edi + 0x378]
006429e4 push 0xbc4ce0
006429e9 mov edx, eax
006429eb mov dword ptr [ebp - 0x6e4], eax
006429f1 lea ecx, [ebp - 0x15d4]
006429f7 call 0x412050
006429fc add esp, 4
006429ff mov ecx, dword ptr [eax]
00642a01 or ecx, dword ptr [eax + 4]
00642a04 jne 0x642a0e
00642a06 mov ecx, dword ptr [eax + 8]
00642a09 or ecx, dword ptr [eax + 0xc]
00642a0c je 0x642a21
00642a0e test byte ptr [edi + 0x30], 4
00642a12 je 0x642a21
00642a14 cmp dword ptr [edi + 0x314], 0
00642a1b je 0x643bd6
00642a21 mov eax, dword ptr [edi + 0x320]
00642a27 mov ecx, edi
00642a29 test eax, eax
00642a2b je 0x642a4a
00642a2d nop dword ptr [eax]
00642a30 mov edi, eax
00642a32 mov dword ptr [ebp - 0x698], edi
00642a38 mov eax, dword ptr [edi + 0x320]
00642a3e test eax, eax
00642a40 jne 0x642a30
00642a42 mov edi, ecx
00642a44 mov ecx, dword ptr [ebp - 0x698]
00642a4a xor eax, eax
00642a4c lea esi, [edi + 0x294]
00642a52 cmp dword ptr [ecx + 0x28], 1
00642a56 push edi
00642a57 cmovne ecx, eax
00642a5a mov dword ptr [ebp - 0x6d0], esi
00642a60 mov eax, dword ptr [0xbfd65c]
00642a65 mov dword ptr [ebp - 0x698], ecx
00642a6b push esi
00642a6c mov ecx, dword ptr [eax + 0x18190]
00642a72 call 0x7a8ef0
00642a77 mov eax, dword ptr [0xbfd65c]
00642a7c movss xmm1, dword ptr [0xb6a53c]
00642a84 movss dword ptr [edi + 0x2f4], xmm0
00642a8c movss dword ptr [ebp - 0x6bc], xmm1
00642a94 mov eax, dword ptr [eax + 0x18190]
00642a9a cmp dword ptr [eax + 0x7120], 0
00642aa1 jle 0x642aaf
00642aa3 mulss xmm0, xmm1
00642aa7 movss dword ptr [edi + 0x2f4], xmm0
00642aaf mov eax, dword ptr [edi + 0x74c]
00642ab5 test eax, eax
00642ab7 jle 0x642ae0
00642ab9 add eax, -1
00642abc mov dword ptr [edi + 0x74c], eax
00642ac2 jne 0x642ce9
00642ac8 mov eax, dword ptr [edi + 0x758]
00642ace mov dword ptr [edi + 0x2b8], eax
00642ad4 mov eax, dword ptr [edi + 0x75c]
00642ada mov dword ptr [edi + 0x2bc], eax
00642ae0 lea esi, [edi + 0x378]
00642ae6 push 0xbc47e0
00642aeb mov edx, esi
00642aed lea ecx, [ebp - 0x1f54]
00642af3 call 0x412050
00642af8 add esp, 4
00642afb mov ecx, eax
00642afd call 0x412090
00642b02 movss xmm0, dword ptr [0xb6a864]
00642b0a movss dword ptr [ebp - 0x688], xmm0
00642b12 test al, al
00642b14 je 0x642b98
00642b1a mov eax, dword ptr [ebp - 0x698]
00642b20 test eax, eax
00642b22 je 0x642b98
00642b24 push 0x89
00642b29 mov ecx, eax
00642b2b call 0x427860
00642b30 mov ecx, eax
00642b32 call 0x88b570
00642b37 test al, al
00642b39 je 0x642b98
00642b3b lea eax, [ebp - 0x1f64]
00642b41 mov ecx, 0xbc47e0
00642b46 push eax
00642b47 call 0x57f3a0
00642b4c push eax
00642b4d mov ecx, esi
00642b4f call 0x6413c0
00642b54 push 0xbc4ca0
00642b59 mov ecx, esi
00642b5b call 0x4271f0
00642b60 movss xmm0, dword ptr [edi + 0x2e0]
00642b68 mulss xmm0, dword ptr [ebp - 0x688]
00642b70 mov eax, dword ptr [edi]
00642b72 push ecx
00642b73 mov ecx, edi
00642b75 addss xmm0, dword ptr [0xb6a95c]
00642b7d mov eax, dword ptr [eax + 0x3c]
00642b80 movss dword ptr [esp], xmm0
00642b85 call eax
00642b87 mov ecx, edi
00642b89 call 0x436b60
00642b8e mov dword ptr [edi + 0x3c4], 0x40
00642b98 mov ecx, dword ptr [0xbfd65c]
00642b9e call 0x4023f0
00642ba3 mov ecx, eax
00642ba5 call 0x7a8ca0
00642baa movss xmm2, dword ptr [0xb6a4c4]
00642bb2 movss dword ptr [ebp - 0x6c4], xmm2
00642bba test al, al
00642bbc je 0x642c19
00642bbe movss xmm0, dword ptr [edi + 0x360]
00642bc6 comiss xmm0, dword ptr [0xb6ae9c]
00642bcd jb 0x642c19
00642bcf movss xmm1, dword ptr [edi + 0x770]
00642bd7 movss xmm0, dword ptr [edi + 0x2fc]
00642bdf mulss xmm1, xmm2
00642be3 comiss xmm0, xmm1
00642be6 jbe 0x642c19
00642be8 push 0xbc4ce0
00642bed mov edx, esi
00642bef lea ecx, [ebp - 0x1f74]
00642bf5 call 0x412050
00642bfa add esp, 4
00642bfd mov ecx, eax
00642bff call 0x427260
00642c04 test al, al
00642c06 je 0x642c19
00642c08 mov ecx, edi
00642c0a call 0x436b60
00642c0f mov dword ptr [edi + 0x3c4], 0x40
00642c19 mov eax, dword ptr [edi + 0x2c]
00642c1c cmp eax, 0xd
00642c1f je 0x642c26
00642c21 cmp eax, 0x17
00642c24 jne 0x642c57
00642c26 mov ecx, dword ptr [0xbfd65c]
00642c2c push 0x4f
00642c2e call 0x427910
00642c33 mov ecx, eax
00642c35 call 0x4480b0
00642c3a test al, al
00642c3c je 0x642c57
00642c3e lea eax, [ebp - 0x1f84]
00642c44 mov ecx, 0xbc46b0
00642c49 push eax
00642c4a call 0x57f3a0
00642c4f push eax
00642c50 mov ecx, esi
00642c52 call 0x6413c0
00642c57 movss xmm0, dword ptr [0xb6a614]
00642c5f lea ecx, [ebp - 0x1f94]
00642c65 push 0xbc4bd0
00642c6a mov edx, esi
00642c6c movss dword ptr [ebp - 0x684], xmm0
00642c74 movss dword ptr [ebp - 0x6b4], xmm0
00642c7c call 0x412050
00642c81 add esp, 4
00642c84 mov ecx, eax
00642c86 call 0x412090
00642c8b movss xmm0, dword ptr [0xb6a480]
00642c93 movss dword ptr [ebp - 0x68c], xmm0
00642c9b test al, al
00642c9d je 0x642d94
00642ca3 lea eax, [ebp - 0x1fa4]
00642ca9 mov dword ptr [edi + 0x388], 0x5a
00642cb3 push eax
00642cb4 mov ecx, 0xbc4bd0
00642cb9 call 0x57f3a0
00642cbe push eax
00642cbf mov ecx, esi
00642cc1 call 0x6413c0
00642cc6 lea esi, [edi + 0x2b8]
00642ccc push esi
00642ccd lea ecx, [edi + 0x38c]
00642cd3 call 0x962cd0
00642cd8 push 0xc02fec
00642cdd mov ecx, esi
00642cdf call 0x962cd0
00642ce4 jmp 0x642e71
00642ce9 mov eax, dword ptr [edi + 0x314]
00642cef test eax, eax
00642cf1 je 0x642d1c
00642cf3 movss xmm0, dword ptr [eax + 0x294]
00642cfb movss xmm1, dword ptr [eax + 0x298]
00642d03 addss xmm0, dword ptr [edi + 0x750]
00642d0b addss xmm1, dword ptr [edi + 0x754]
00642d13 movss dword ptr [esi], xmm0
00642d17 movss dword ptr [esi + 4], xmm1
00642d1c movss xmm0, dword ptr [0xc02fec]
00642d24 mov eax, 0x88888889
00642d29 movss dword ptr [edi + 0x2b8], xmm0
00642d31 movss xmm0, dword ptr [0xc02ff0]
00642d39 movss dword ptr [edi + 0x2bc], xmm0
00642d41 mov ecx, dword ptr [edi + 0x74c]
00642d47 movss xmm0, dword ptr [edi + 0x360]
00642d4f imul ecx
00642d51 add edx, ecx
00642d53 sar edx, 3
00642d56 mov eax, edx
00642d58 shr eax, 0x1f
00642d5b add eax, edx
00642d5d test al, 1
00642d5f jne 0x642d6b
00642d61 addss xmm0, dword ptr [0xb6a480]
00642d69 jmp 0x642d73
00642d6b subss xmm0, dword ptr [0xb6a480]
00642d73 push ecx
00642d74 mov ecx, edi
00642d76 movss dword ptr [edi + 0x360], xmm0
00642d7e movss dword ptr [esp], xmm0
00642d83 call 0x6500f0
00642d88 mov ecx, edi
00642d8a call 0x6860a0
00642d8f jmp 0x64db64
00642d94 cmp dword ptr [edi + 0x388], 0
00642d9b jle 0x642e71
00642da1 mov ecx, dword ptr [edi + 0x314]
00642da7 test ecx, ecx
00642da9 je 0x642df8
00642dab call 0x412100
00642db0 mov ecx, dword ptr [edi + 0x314]
00642db6 cmp eax, 1
00642db9 je 0x642dd9
00642dbb call 0x412100
00642dc0 cmp eax, 3
00642dc3 jne 0x642df8
00642dc5 mov ecx, dword ptr [edi + 0x314]
00642dcb call 0x427450
00642dd0 mov ecx, eax
00642dd2 call 0x427890
00642dd7 mov ecx, eax
00642dd9 call 0x4866c0
00642dde test eax, eax
00642de0 je 0x642df8
00642de2 mov ecx, eax
00642de4 call 0x422d80
00642de9 cmp eax, -1
00642dec jne 0x642df8
00642dee mov dword ptr [edi + 0x388], 1
00642df8 add dword ptr [edi + 0x388], -1
00642dff mov ecx, dword ptr [edi + 0x388]
00642e05 jne 0x642e2b
00642e07 lea esi, [edi + 0x38c]
00642e0d push esi
00642e0e lea ecx, [edi + 0x2b8]
00642e14 call 0x962a90
00642e19 push 0xc02fec
00642e1e mov ecx, esi
00642e20 call 0x962cd0
00642e25 mov ecx, dword ptr [edi + 0x388]
00642e2b movss xmm0, dword ptr [edi + 0x360]
00642e33 mov eax, 0x88888889
00642e38 imul ecx
00642e3a add edx, ecx
00642e3c sar edx, 3
00642e3f mov eax, edx
00642e41 shr eax, 0x1f
00642e44 add eax, edx
00642e46 test al, 1
00642e48 jne 0x642e54
00642e4a addss xmm0, dword ptr [ebp - 0x68c]
00642e52 jmp 0x642e5c
00642e54 subss xmm0, dword ptr [ebp - 0x68c]
00642e5c push ecx
00642e5d mov ecx, edi
00642e5f movss dword ptr [edi + 0x360], xmm0
00642e67 movss dword ptr [esp], xmm0
00642e6c call 0x6500f0
00642e71 lea esi, [edi + 0x378]
00642e77 push 0xbc4bb0
00642e7c mov edx, esi
00642e7e lea ecx, [ebp - 0x1fb4]
00642e84 call 0x412050
00642e89 add esp, 4
00642e8c mov ecx, eax
00642e8e call 0x412090
00642e93 movss xmm0, dword ptr [0xb6a9ac]
00642e9b movss dword ptr [ebp - 0x6e0], xmm0
00642ea3 movss xmm0, dword ptr [0xb6a434]
00642eab movss dword ptr [ebp - 0x6cc], xmm0
00642eb3 test al, al
00642eb5 je 0x64303e
00642ebb cmp byte ptr [edi + 0x16b], 0
00642ec2 lea ecx, [ebp - 0x1fc4]
00642ec8 push 0xbc4ce0
00642ecd mov edx, esi
00642ecf setne byte ptr [ebp - 0x674]
00642ed6 call 0x412050
00642edb add esp, 4
00642ede mov ecx, eax
00642ee0 call 0x412090
00642ee5 test al, al
00642ee7 je 0x642f0e
00642ee9 push dword ptr [edi + 0x20]
00642eec mov ecx, edi
00642eee push 5
00642ef0 call 0x684790
00642ef5 mov ecx, dword ptr [ebp - 0x674]
00642efb test al, al
00642efd movzx ecx, cl
00642f00 mov eax, 1
00642f05 cmovne ecx, eax
00642f08 mov dword ptr [ebp - 0x674], ecx
00642f0e cmp byte ptr [edi + 0x16b], 0
00642f15 je 0x642f45
00642f17 push 0xbc4ca0
00642f1c mov edx, esi
00642f1e lea ecx, [ebp - 0x1fd4]
00642f24 call 0x412050
00642f29 add esp, 4
00642f2c mov ecx, eax
00642f2e call 0x412090
00642f33 test al, al
00642f35 jne 0x64303e
00642f3b cmp dword ptr [edi + 0x2c], 4
00642f3f je 0x64303e
00642f45 cmp byte ptr [ebp - 0x674], 0
00642f4c je 0x64303e
00642f52 mov ecx, dword ptr [edi + 0x298]
00642f58 mov eax, dword ptr [edi + 0x294]
00642f5e push ecx
00642f5f mov dword ptr [ebp - 0x768], eax
00642f65 lea eax, [ebp - 0x768]
00642f6b mov dword ptr [esp], 0x41700000
00642f72 push eax
00642f73 lea eax, [ebp - 0x121c]
00642f79 mov dword ptr [ebp - 0x764], ecx
00642f7f mov ecx, dword ptr [0xbfd65c]
00642f85 push eax
00642f86 call 0x4023f0
00642f8b mov ecx, eax
00642f8d call 0x427710
00642f92 push eax
00642f93 lea ecx, [ebp - 0x768]
00642f99 call 0x962cd0
00642f9e call 0x6c3d90
00642fa3 mov ecx, dword ptr [0xbfd65c]
00642fa9 push 0
00642fab push 0xbeaaec
00642fb0 push 0xbeab18
00642fb5 push 0
00642fb7 push eax
00642fb8 push 0
00642fba push dword ptr [edi + 0x320]
00642fc0 lea eax, [ebp - 0x768]
00642fc6 push 0xc02fec
00642fcb push eax
00642fcc push 0x35
00642fce push 0x3e8
00642fd3 call 0x422e20
00642fd8 push eax
00642fd9 call 0x9ec34c
00642fde add esp, 0x14
00642fe1 mov ecx, edi
00642fe3 mov esi, eax
00642fe5 call 0x544b60
00642fea lea eax, [ebp - 0x8e8]
00642ff0 mov dword ptr [ebp - 0x8ec], 0x3ecccccd
00642ffa push eax
00642ffb lea eax, [ebp - 0x1224]
00643001 mov ecx, 0xbc7a28
00643006 push eax
00643007 lea eax, [ebp - 0x8ec]
0064300d push eax
0064300e lea eax, [ebp - 0x122c]
00643014 push eax
00643015 fstp dword ptr [ebp - 0x8e8]
0064301b call 0x962b50
00643020 mov ecx, eax
00643022 call 0x962b50
00643027 push eax
00643028 mov ecx, esi
0064302a call 0x427330
0064302f mov eax, dword ptr [esi]
00643031 mov ecx, esi
00643033 mov eax, dword ptr [eax + 0xc]
00643036 call eax
00643038 lea esi, [edi + 0x378]
0064303e push 0xbc4770
00643043 mov edx, esi
00643045 lea ecx, [ebp - 0x1fe4]
0064304b call 0x412050
00643050 add esp, 4
00643053 mov ecx, eax
00643055 call 0x412090
0064305a xorps xmm0, xmm0
0064305d movss dword ptr [ebp - 0x67c], xmm0
00643065 movss xmm0, dword ptr [0xb6a3b0]
0064306d movss dword ptr [ebp - 0x6b8], xmm0
00643075 test al, al
00643077 je 0x6435cb
0064307d cmp dword ptr [edi + 0x3dc], 0
00643084 lea esi, [edi + 0x3dc]
0064308a mov byte ptr [ebp - 0x68e], 0
00643091 mov dword ptr [ebp - 0x674], esi
00643097 jne 0x6433cd
0064309d movss xmm0, dword ptr [0xb6ad84]
006430a5 lea esi, [edi + 0x294]
006430ab mov ecx, dword ptr [0xbfd65c]
006430b1 lea eax, [ebp - 0xa08]
006430b7 push 4
006430b9 push esi
006430ba push eax
006430bb mov dword ptr [ebp - 0x66c], 0
006430c5 movss dword ptr [ebp - 0x680], xmm0
006430cd call 0x4023f0
006430d2 mov ecx, eax
006430d4 call 0x422d70
006430d9 movss xmm3, dword ptr [0xb6ac38]
006430e1 mov ecx, eax
006430e3 call 0x4157f0
006430e8 lea ecx, [ebp - 0xa08]
006430ee mov dword ptr [ebp - 4], 0
006430f5 mov dword ptr [ebp - 0x670], 0
006430ff call 0x4083d0
00643104 test eax, eax
00643106 je 0x6433b5
0064310c xor ecx, ecx
0064310e nop 
00643110 push ecx
00643111 lea ecx, [ebp - 0xa08]
00643117 call 0x4124b0
0064311c cmp dword ptr [eax], edi
0064311e je 0x6431b5
00643124 push dword ptr [ebp - 0x670]
0064312a lea ecx, [ebp - 0xa08]
00643130 call 0x4124b0
00643135 mov ecx, dword ptr [eax]
00643137 call 0x412100
0064313c cmp eax, 2
0064313f jne 0x6431b5
00643141 push dword ptr [ebp - 0x670]
00643147 lea ecx, [ebp - 0xa08]
0064314d call 0x4124b0
00643152 push 0
00643154 push 0xbeae24
00643159 push 0xbeab18
0064315e push 0
00643160 push dword ptr [eax]
00643162 call 0x9ec34c
00643167 add esp, 0x14
0064316a mov dword ptr [ebp - 0x6c0], eax
00643170 lea ecx, [ebp - 0x1234]
00643176 push esi
00643177 push ecx
00643178 mov ecx, eax
0064317a call 0x412130
0064317f mov ecx, eax
00643181 call 0x962750
00643186 movss xmm1, dword ptr [ebp - 0x680]
0064318e fstp dword ptr [ebp - 0x6c8]
00643194 movss xmm0, dword ptr [ebp - 0x6c8]
0064319c comiss xmm1, xmm0
0064319f jbe 0x6431b5
006431a1 mov eax, dword ptr [ebp - 0x6c0]
006431a7 mov dword ptr [ebp - 0x66c], eax
006431ad movss dword ptr [ebp - 0x680], xmm0
006431b5 inc dword ptr [ebp - 0x670]
006431bb lea ecx, [ebp - 0xa08]
006431c1 call 0x4083d0
006431c6 mov ecx, dword ptr [ebp - 0x670]
006431cc cmp ecx, eax
006431ce jb 0x643110
006431d4 mov eax, dword ptr [ebp - 0x66c]
006431da test eax, eax
006431dc je 0x6433b5
006431e2 cmp dword ptr [eax + 0x3dc], edi
006431e8 je 0x6433b5
006431ee cmp dword ptr [ebp - 0x698], 0
006431f5 je 0x6433b5
006431fb lea eax, [edi + 0x2a4]
00643201 mov ecx, esi
00643203 push eax
00643204 lea eax, [ebp - 0x123c]
0064320a push eax
0064320b lea eax, [edi + 0x2b8]
00643211 push eax
00643212 lea eax, [ebp - 0x1244]
00643218 push eax
00643219 call 0x962a60
0064321e mov ecx, eax
00643220 call 0x962a60
00643225 mov ecx, dword ptr [ebp - 0x66c]
0064322b push eax
0064322c lea eax, [ebp - 0xb64]
00643232 push eax
00643233 call 0x4121b0
00643238 mov ecx, dword ptr [ebp - 0x66c]
0064323e push eax
0064323f lea eax, [ebp - 0x124c]
00643245 push eax
00643246 lea eax, [ebp - 0x1254]
0064324c push eax
0064324d call 0x412130
00643252 mov ecx, eax
00643254 call 0x962a60
00643259 mov ecx, eax
0064325b call 0x962ac0
00643260 cmp dword ptr [edi + 0x3d8], 0
00643267 jne 0x643368
0064326d movss xmm2, dword ptr [0xb6aed0]
00643275 lea ecx, [ebp - 0x125c]
0064327b movss xmm1, dword ptr [ebp - 0x67c]
00643283 push 1
00643285 push dword ptr [ebp - 0x698]
0064328b call 0x9624e0
00643290 push eax
00643291 push 3
00643293 lea ecx, [ebp - 0xb64]
00643299 call 0x962830
0064329e push ecx
0064329f fstp dword ptr [esp]
006432a2 push esi
006432a3 push 0xa
006432a5 call 0x8c7550
006432aa mov esi, eax
006432ac add esp, 0x1c
006432af test esi, esi
006432b1 je 0x64337f
006432b7 push 0
006432b9 mov ecx, 2
006432be call 0x659230
006432c3 lea eax, [eax*2 - 1]
006432ca push eax
006432cb push ecx
006432cc mov ecx, dword ptr [ebp - 0x698]
006432d2 lea eax, [ebp - 0x1ec]
006432d8 mov dword ptr [esp], 0x3f800000
006432df push 3
006432e1 push eax
006432e2 call 0x7836a0
006432e7 movss xmm0, dword ptr [ebp - 0x1a4]
006432ef mov eax, dword ptr [esi]
006432f1 mulss xmm0, dword ptr [ebp - 0x6b8]
006432f9 push ecx
006432fa mov ecx, esi
006432fc mov eax, dword ptr [eax + 0x3c]
006432ff movss dword ptr [esp], xmm0
00643304 call eax
00643306 movss xmm1, dword ptr [ebp - 0x1a0]
0064330e mov ecx, esi
00643310 call 0x8d7ff0
00643315 push 4
00643317 mov ecx, esi
00643319 call 0x4272f0
0064331e movups xmm0, xmmword ptr [0xbc4cc0]
00643325 sub esp, 0x10
00643328 mov ecx, esi
0064332a mov eax, esp
0064332c movups xmmword ptr [eax], xmm0
0064332f call 0x427580
00643334 push ecx
00643335 mov ecx, esi
00643337 mov dword ptr [esp], 0
0064333e call 0x439580
00643343 push edi
00643344 mov ecx, esi
00643346 call 0x6818e0
0064334b push 1
0064334d mov ecx, esi
0064334f call 0x4275f0
00643354 mov edx, esi
00643356 lea ecx, [edi + 0x3d8]
0064335c call 0x68cf00
00643361 mov byte ptr [ebp - 0x68e], 1
00643368 mov eax, dword ptr [ebp - 0x66c]
0064336e lea esi, [edi + 0x3dc]
00643374 mov edx, eax
00643376 mov ecx, esi
00643378 call 0x68cf00
0064337d jmp 0x6433bb
0064337f lea eax, [ebp - 0x1ff4]
00643385 mov ecx, 0xbc4770
0064338a push eax
0064338b call 0x57f3a0
00643390 push eax
00643391 lea ecx, [edi + 0x378]
00643397 call 0x6413c0
0064339c xor eax, eax
0064339e lea esi, [edi + 0x3dc]
006433a4 mov edx, eax
006433a6 mov byte ptr [ebp - 0x68e], al
006433ac mov ecx, esi
006433ae call 0x68cf00
006433b3 jmp 0x6433bb
006433b5 lea esi, [edi + 0x3dc]
006433bb lea ecx, [ebp - 0xa08]
006433c1 mov dword ptr [ebp - 4], 0xffffffff
006433c8 call 0x412490
006433cd cmp dword ptr [edi + 0x3d8], 0
006433d4 lea eax, [edi + 0x3d8]
006433da mov dword ptr [ebp - 0x6c8], eax
006433e0 je 0x64341f
006433e2 cmp byte ptr [edi + 0x16b], 0
006433e9 jne 0x643400
006433eb mov ecx, dword ptr [esi]
006433ed test ecx, ecx
006433ef je 0x643400
006433f1 call 0x412350
006433f6 test al, al
006433f8 je 0x64341f
006433fa lea eax, [edi + 0x3d8]
00643400 mov ecx, dword ptr [eax]
00643402 mov eax, dword ptr [ecx]
00643404 mov eax, dword ptr [eax + 0x28]
00643407 call eax
00643409 xor edx, edx
0064340b lea ecx, [edi + 0x3d8]
00643411 call 0x68cf00
00643416 xor edx, edx
00643418 mov ecx, esi
0064341a call 0x68cf00
0064341f cmp byte ptr [edi + 0x16b], 0
00643426 jne 0x64343c
00643428 mov ecx, dword ptr [esi]
0064342a test ecx, ecx
0064342c je 0x643437
0064342e call 0x412350
00643433 test al, al
00643435 jne 0x64343c
00643437 cmp dword ptr [esi], 0
0064343a jne 0x64344d
0064343c mov ecx, dword ptr [edi + 0x3d8]
00643442 test ecx, ecx
00643444 je 0x64344d
00643446 mov eax, dword ptr [ecx]
00643448 mov eax, dword ptr [eax + 0x28]
0064344b call eax
0064344d cmp dword ptr [edi + 0x3d8], 0
00643454 je 0x6435cb
0064345a cmp dword ptr [esi], 0
0064345d je 0x6435cb
00643463 mov esi, dword ptr [ebp - 0x6a8]
00643469 lea eax, [ebp - 0x1264]
0064346f mov ecx, dword ptr [ebp - 0x6d0]
00643475 add edi, 0x2a4
0064347b push edi
0064347c push eax
0064347d add esi, 0x2b8
00643483 lea eax, [ebp - 0x126c]
00643489 push esi
0064348a push eax
0064348b call 0x962a60
00643490 mov ecx, eax
00643492 call 0x962a60
00643497 mov ecx, dword ptr [ebp - 0x674]
0064349d push eax
0064349e lea eax, [ebp - 0xa54]
006434a4 push eax
006434a5 mov ecx, dword ptr [ecx]
006434a7 call 0x4121b0
006434ac push eax
006434ad lea eax, [ebp - 0x1274]
006434b3 push eax
006434b4 lea eax, [ebp - 0x127c]
006434ba push eax
006434bb mov eax, dword ptr [ebp - 0x674]
006434c1 mov ecx, dword ptr [eax]
006434c3 call 0x412130
006434c8 mov ecx, eax
006434ca call 0x962a60
006434cf mov ecx, eax
006434d1 call 0x962ac0
006434d6 lea ecx, [ebp - 0xa54]
006434dc call 0x962a00
006434e1 mov eax, dword ptr [ebp - 0x6c8]
006434e7 push 0
006434e9 push 0xbeabc8
006434ee push 0xbeab18
006434f3 push 0
006434f5 push dword ptr [eax]
006434f7 fstp dword ptr [ebp - 0x680]
006434fd call 0x9ec34c
00643502 add esp, 0x14
00643505 mov dword ptr [ebp - 0x670], eax
0064350b lea ecx, [ebp - 0xa54]
00643511 call 0x962830
00643516 push ecx
00643517 mov ecx, dword ptr [ebp - 0x670]
0064351d fstp dword ptr [esp]
00643520 call 0x8c59a0
00643525 movss xmm0, dword ptr [ebp - 0x680]
0064352d push ecx
0064352e mov ecx, dword ptr [ebp - 0x670]
00643534 movss dword ptr [esp], xmm0
00643539 call 0x4275b0
0064353e mov ecx, dword ptr [ebp - 0x670]
00643544 push 3
00643546 call 0x4275a0
0064354b mov ecx, dword ptr [ebp - 0x670]
00643551 call 0x4121b0
00643556 push eax
00643557 lea eax, [ebp - 0x1284]
0064355d push eax
0064355e push esi
0064355f mov esi, dword ptr [ebp - 0x6d0]
00643565 lea eax, [ebp - 0x129c]
0064356b push eax
0064356c push edi
0064356d lea eax, [ebp - 0x12a4]
00643573 mov ecx, esi
00643575 push eax
00643576 call 0x962a60
0064357b mov ecx, eax
0064357d call 0x962a60
00643582 mov ecx, eax
00643584 call 0x962ac0
00643589 mov edi, dword ptr [ebp - 0x670]
0064358f mov ecx, edi
00643591 push eax
00643592 call 0x427300
00643597 movss xmm0, dword ptr [ebp - 0x680]
0064359f comiss xmm0, dword ptr [0xb6ac38]
006435a6 jbe 0x6435b1
006435a8 mov eax, dword ptr [edi]
006435aa mov ecx, edi
006435ac mov eax, dword ptr [eax + 0x28]
006435af call eax
006435b1 cmp byte ptr [ebp - 0x68e], 0
006435b8 je 0x6435c3
006435ba mov eax, dword ptr [edi]
006435bc mov ecx, edi
006435be mov eax, dword ptr [eax + 0xc]
006435c1 call eax
006435c3 mov edi, dword ptr [ebp - 0x6a8]
006435c9 jmp 0x6435d1
006435cb lea esi, [edi + 0x294]
006435d1 push 0xbc46b0
006435d6 lea edx, [edi + 0x378]
006435dc lea ecx, [ebp - 0x2004]
006435e2 call 0x412050
006435e7 add esp, 4
006435ea mov ecx, eax
006435ec call 0x412090
006435f1 movss xmm0, dword ptr [0xb6aa0c]
006435f9 movss dword ptr [ebp - 0x6c0], xmm0
00643601 test al, al
00643603 je 0x643905
00643609 cmp dword ptr [edi + 0x388], 0
00643610 lea ecx, [edi + 0x38c]
00643616 jg 0x64361e
00643618 lea ecx, [edi + 0x2b8]
0064361e mov eax, dword ptr [ecx]
00643620 mov ecx, dword ptr [ecx + 4]
00643623 mov dword ptr [ebp - 0x928], eax
00643629 mov dword ptr [ebp - 0x924], ecx
0064362f mov eax, dword ptr [edi + 0x3e0]
00643635 test eax, eax
00643637 jne 0x643862
0064363d mov eax, dword ptr [ebp - 0x698]
00643643 mov dword ptr [ebp - 0x680], eax
00643649 test eax, eax
0064364b jne 0x64365f
0064364d mov ecx, dword ptr [0xbfd65c]
00643653 push eax
00643654 call 0x412750
00643659 mov dword ptr [ebp - 0x680], eax
0064365f lea ecx, [edi + 0x2b8]
00643665 push ecx
00643666 mov ecx, esi
00643668 call 0x962af0
0064366d movss xmm2, dword ptr [edi + 0x360]
00643675 lea ecx, [ebp - 0x12ac]
0064367b movss xmm1, dword ptr [ebp - 0x67c]
00643683 push 1
00643685 push dword ptr [ebp - 0x680]
0064368b call 0x9624e0
00643690 push eax
00643691 push 0x3e8
00643696 lea ecx, [edi + 0x2b8]
0064369c call 0x962830
006436a1 push ecx
006436a2 fstp dword ptr [esp]
006436a5 push esi
006436a6 push 3
006436a8 call 0x8c7550
006436ad mov esi, eax
006436af add esp, 0x1c
006436b2 mov dword ptr [ebp - 0x680], esi
006436b8 test esi, esi
006436ba je 0x64382d
006436c0 push edi
006436c1 mov ecx, esi
006436c3 call 0x6818e0
006436c8 push ecx
006436c9 mov ecx, esi
006436cb mov dword ptr [esp], 0x41f00000
006436d2 call 0x4275b0
006436d7 movss xmm0, dword ptr [edi + 0x2e0]
006436df mov eax, dword ptr [esi]
006436e1 mulss xmm0, dword ptr [0xb6a3d4]
006436e9 push ecx
006436ea mov ecx, esi
006436ec mov eax, dword ptr [eax + 0x3c]
006436ef movss dword ptr [esp], xmm0
006436f4 call eax
006436f6 mov esi, dword ptr [esi]
006436f8 mov ecx, edi
006436fa push 1
006436fc push 0
006436fe push 0xff
00643703 push -1
00643705 call 0x4f3de0
0064370a mov ecx, dword ptr [ebp - 0x680]
00643710 push eax
00643711 mov eax, dword ptr [esi + 0x38]
00643714 call eax
00643716 lea eax, [ebp - 0x2014]
0064371c mov edx, 0xbc4c10
00643721 push eax
00643722 push 0xbc4940
00643727 push 0xbc49e0
0064372c push 0xbc46c0
00643731 push 0xbc4bf0
00643736 lea ecx, [ebp - 0x2024]
0064373c call 0x427220
00643741 add esp, 4
00643744 lea ecx, [ebp - 0x2034]
0064374a mov edx, eax
0064374c call 0x427220
00643751 add esp, 4
00643754 lea ecx, [ebp - 0x2044]
0064375a mov edx, eax
0064375c call 0x427220
00643761 add esp, 4
00643764 lea ecx, [ebp - 0x2054]
0064376a mov edx, eax
0064376c call 0x427220
00643771 add esp, 4
00643774 mov ecx, eax
00643776 call 0x57f3a0
0064377b push eax
0064377c lea eax, [ebp - 0x2064]
00643782 mov ecx, edi
00643784 push eax
00643785 call 0x412650
0064378a mov edx, eax
0064378c lea ecx, [ebp - 0x2074]
00643792 call 0x412050
00643797 mov esi, dword ptr [ebp - 0x680]
0064379d sub esp, 0xc
006437a0 mov ecx, esp
006437a2 movups xmm0, xmmword ptr [eax]
006437a5 movups xmmword ptr [ecx], xmm0
006437a8 mov ecx, esi
006437aa call 0x427580
006437af push 1
006437b1 mov ecx, esi
006437b3 call 0x497840
006437b8 push 1
006437ba mov ecx, esi
006437bc call 0x5b74f0
006437c1 push 1
006437c3 mov ecx, esi
006437c5 call 0x5b7500
006437ca lea ecx, [ebp - 0x928]
006437d0 call 0x962830
006437d5 push ecx
006437d6 mov ecx, esi
006437d8 fstp dword ptr [esp]
006437db call 0x8c59a0
006437e0 mov eax, dword ptr [esi]
006437e2 mov eax, dword ptr [eax + 0xc]
006437e5 mov ecx, esi
006437e7 call eax
006437e9 mov edx, esi
006437eb lea ecx, [edi + 0x3e0]
006437f1 call 0x68cf00
006437f6 push 0xbc4ca0
006437fb lea edx, [edi + 0x378]
00643801 mov byte ptr [edi + 0x169], 0
00643808 lea ecx, [ebp - 0x2084]
0064380e call 0x412050
00643813 add esp, 4
00643816 mov ecx, eax
00643818 call 0x427260
0064381d test al, al
0064381f je 0x643883
00643821 mov dword ptr [edi + 0x180], 0
0064382b jmp 0x643883
0064382d lea eax, [ebp - 0x2094]
00643833 mov ecx, 0xbc46b0
00643838 push eax
00643839 call 0x57f3a0
0064383e lea esi, [edi + 0x378]
00643844 push eax
00643845 mov ecx, esi
00643847 call 0x6413c0
0064384c mov byte ptr [edi + 0x169], 1
00643853 mov dword ptr [edi + 0x180], 4
0064385d jmp 0x64393a
00643862 push 0
00643864 push 0xbeabc8
00643869 push 0xbeab18
0064386e push 0
00643870 push eax
00643871 call 0x9ec34c
00643876 mov esi, eax
00643878 add esp, 0x14
0064387b test esi, esi
0064387d je 0x643934
00643883 lea ecx, [ebp - 0x928]
00643889 call 0x962830
0064388e fstp dword ptr [ebp - 0x6c8]
00643894 mov ecx, esi
00643896 call 0x7fab60
0064389b movss xmm2, dword ptr [ebp - 0x68c]
006438a3 movss xmm1, dword ptr [ebp - 0x6c8]
006438ab fstp dword ptr [ebp - 0x6ac]
006438b1 movss xmm0, dword ptr [ebp - 0x6ac]
006438b9 call 0x65a7b0
006438be push ecx
006438bf mov ecx, esi
006438c1 movss dword ptr [esp], xmm0
006438c6 call 0x8c59a0
006438cb cmp byte ptr [edi + 0x16b], 0
006438d2 mov ecx, esi
006438d4 je 0x6438f9
006438d6 call 0x567390
006438db cmp eax, 0xa
006438de jle 0x6438e9
006438e0 push 0xa
006438e2 mov ecx, esi
006438e4 call 0x4275a0
006438e9 lea eax, [edi + 0x2b8]
006438ef mov ecx, esi
006438f1 push eax
006438f2 call 0x422ae0
006438f7 jmp 0x643927
006438f9 push 0x3e8
006438fe call 0x4275a0
00643903 jmp 0x643934
00643905 mov ecx, dword ptr [edi + 0x3e0]
0064390b test ecx, ecx
0064390d je 0x643934
0064390f mov byte ptr [edi + 0x169], 1
00643916 mov dword ptr [edi + 0x180], 4
00643920 mov eax, dword ptr [ecx]
00643922 mov eax, dword ptr [eax + 0x28]
00643925 call eax
00643927 xor edx, edx
00643929 lea ecx, [edi + 0x3e0]
0064392f call 0x68cf00
00643934 lea esi, [edi + 0x378]
0064393a movss xmm0, dword ptr [edi + 0x364]
00643942 lea ecx, [ebp - 0x20a4]
00643948 push 0xbc4ce0
0064394d mov edx, esi
0064394f movss dword ptr [ebp - 0x6b0], xmm0
00643957 call 0x412050
0064395c add esp, 4
0064395f mov ecx, eax
00643961 call 0x412090
00643966 test al, al
00643968 je 0x643a74
0064396e push 0xbc46c0
00643973 mov edx, esi
00643975 lea ecx, [ebp - 0x20b4]
0064397b call 0x412050
00643980 add esp, 4
00643983 mov ecx, eax
00643985 call 0x412090
0064398a test al, al
0064398c je 0x643a74
00643992 mov ecx, edi
00643994 call 0x654610
00643999 movss xmm1, dword ptr [0xb6a874]
006439a1 mov ecx, edi
006439a3 divss xmm1, xmm0
006439a7 movss dword ptr [ebp - 0x674], xmm1
006439af call 0x682200
006439b4 dec eax
006439b5 xorps xmm0, xmm0
006439b8 cvtsi2ss xmm0, eax
006439bc mulss xmm0, dword ptr [ebp - 0x674]
006439c4 call 0x412040
006439c9 mov ecx, edi
006439cb movss dword ptr [ebp - 0x680], xmm0
006439d3 call 0x682200
006439d8 xorps xmm0, xmm0
006439db cvtsi2ss xmm0, eax
006439df mulss xmm0, dword ptr [ebp - 0x674]
006439e7 call 0x412040
006439ec call 0x412000
006439f1 mulss xmm0, dword ptr [edi + 0x360]
006439f9 movss dword ptr [edi + 0x2a8], xmm0
00643a01 movss xmm0, dword ptr [ebp - 0x680]
00643a09 call 0x412000
00643a0e mulss xmm0, dword ptr [edi + 0x360]
00643a16 mov ecx, edi
00643a18 movss xmm1, dword ptr [edi + 0x2a8]
00643a20 subss xmm1, xmm0
00643a24 movss dword ptr [ebp - 0x6b0], xmm1
00643a2c call 0x682200
00643a31 xorps xmm0, xmm0
00643a34 cvtsi2ss xmm0, eax
00643a38 mulss xmm0, dword ptr [ebp - 0x674]
00643a40 call 0x412040
00643a45 mulss xmm0, dword ptr [ebp - 0x680]
00643a4d movss xmm1, dword ptr [ebp - 0x67c]
00643a55 comiss xmm1, xmm0
00643a58 jbe 0x643a74
00643a5a mov dword ptr [edi + 0x3c4], 4
00643a64 mov ecx, edi
00643a66 push 0
00643a68 mov byte ptr [edi + 0x16b], 1
00643a6f call 0x650dd0
00643a74 cmp byte ptr [edi + 0x16b], 0
00643a7b movss xmm0, dword ptr [0xb6aeb8]
00643a83 movss dword ptr [ebp - 0x6c8], xmm0
00643a8b movss xmm0, dword ptr [0xb6aee4]
00643a93 movss dword ptr [ebp - 0x6ac], xmm0
00643a9b movss xmm0, dword ptr [0xb6aef0]
00643aa3 movss dword ptr [ebp - 0x680], xmm0
00643aab je 0x6456e4
00643ab1 mov eax, dword ptr [edi + 0x2c]
00643ab4 cmp eax, 9
00643ab7 je 0x6456e4
00643abd cmp eax, 0x28
00643ac0 jne 0x643be4
00643ac6 lea ecx, [ebp - 0xbac]
00643acc call 0x4e6190
00643ad1 mov ecx, dword ptr [edi + 0x30]
00643ad4 mov eax, ecx
00643ad6 shr eax, 0x10
00643ad9 mov dword ptr [ebp - 0xbac], eax
00643adf movzx eax, cx
00643ae2 mov ecx, edi
00643ae4 push 0
00643ae6 mov dword ptr [ebp - 0xba8], eax
00643aec mov eax, dword ptr [edi + 0x344]
00643af2 push 0x40000
00643af7 mov dword ptr [ebp - 0xb9c], eax
00643afd call 0x4122f0
00643b02 xor ecx, ecx
00643b04 lea esi, [edi + 0x294]
00643b0a test al, al
00643b0c lea edx, [ebp - 0xbac]
00643b12 setne cl
00643b15 mov dword ptr [ebp - 0xb98], ecx
00643b1b mov ecx, esi
00643b1d cvttss2si eax, dword ptr [edi + 0x2d8]
00643b25 mov dword ptr [ebp - 0xba4], eax
00643b2b push dword ptr [edi + 0x3a0]
00643b31 push edi
00643b32 call 0x6dc740
00643b37 mov ecx, dword ptr [edi + 0x320]
00643b3d add esp, 8
00643b40 test ecx, ecx
00643b42 je 0x643bd6
00643b48 call 0x412240
00643b4d test al, al
00643b4f je 0x643bd6
00643b55 mov ecx, dword ptr [edi + 0x320]
00643b5b call 0x4866c0
00643b60 mov dword ptr [ebp - 0x6c0], eax
00643b66 test eax, eax
00643b68 je 0x643bd6
00643b6a push 0
00643b6c push 0x248
00643b71 mov ecx, eax
00643b73 call 0x73af30
00643b78 test al, al
00643b7a je 0x643bd6
00643b7c mov ecx, 3
00643b81 call 0x659230
00643b86 inc eax
00643b87 mov dword ptr [ebp - 0x6c8], eax
00643b8d test eax, eax
00643b8f jle 0x643bd6
00643b91 mov edi, eax
00643b93 mov ecx, dword ptr [ebp - 0x6c0]
00643b99 push 1
00643b9b push 0
00643b9d push esi
00643b9e push 0x25c
00643ba3 call 0x5b4730
00643ba8 mov dword ptr [ebp - 0x6c8], eax
00643bae test eax, eax
00643bb0 je 0x643bcb
00643bb2 push dword ptr [esi + 4]
00643bb5 mov ecx, eax
00643bb7 push dword ptr [esi]
00643bb9 call 0x427390
00643bbe mov ecx, dword ptr [ebp - 0x6c8]
00643bc4 mov eax, dword ptr [ecx]
00643bc6 mov eax, dword ptr [eax + 0xc]
00643bc9 call eax
00643bcb sub edi, 1
00643bce jne 0x643b93
00643bd0 mov edi, dword ptr [ebp - 0x6a8]
00643bd6 mov eax, dword ptr [edi]
00643bd8 mov ecx, edi
00643bda mov eax, dword ptr [eax + 0x28]
00643bdd call eax
00643bdf jmp 0x64db64
00643be4 push 0xbc46c0
00643be9 mov edx, esi
00643beb mov byte ptr [ebp - 0x674], 0
00643bf2 lea ecx, [ebp - 0x20c4]
00643bf8 call 0x412050
00643bfd add esp, 4
00643c00 mov ecx, eax
00643c02 call 0x412090
00643c07 test al, al
00643c09 je 0x643d23
00643c0f cmp dword ptr [edi + 0x3c4], 4
00643c16 jne 0x643d23
00643c1c push 0xbc4ce0
00643c21 mov edx, esi
00643c23 lea ecx, [ebp - 0x20d4]
00643c29 call 0x412050
00643c2e add esp, 4
00643c31 mov ecx, eax
00643c33 call 0x412090
00643c38 movss xmm0, dword ptr [ebp - 0x6c8]
00643c40 movss dword ptr [ebp - 0x678], xmm0
00643c48 test al, al
00643c4a jne 0x643ccf
00643c50 push 0xbc49b0
00643c55 push 0xbc4a00
00643c5a mov edx, 0xbc4ca0
00643c5f lea ecx, [ebp - 0x20e4]
00643c65 call 0x427220
00643c6a add esp, 4
00643c6d lea ecx, [ebp - 0x20f4]
00643c73 mov edx, eax
00643c75 call 0x427220
00643c7a push eax
00643c7b mov edx, esi
00643c7d lea ecx, [ebp - 0x2104]
00643c83 call 0x412050
00643c88 add esp, 8
00643c8b mov ecx, eax
00643c8d call 0x412090
00643c92 test al, al
00643c94 je 0x643ca0
00643c96 movss xmm1, dword ptr [ebp - 0x6ac]
00643c9e jmp 0x643ca8
00643ca0 movss xmm1, dword ptr [ebp - 0x678]
00643ca8 movss xmm0, dword ptr [edi + 0x364]
00643cb0 comiss xmm0, xmm1
00643cb3 jbe 0x643cca
00643cb5 cmp word ptr [edi + 0x3be], 0
00643cbd jne 0x643cca
00643cbf movss dword ptr [edi + 0x364], xmm1
00643cc7 movaps xmm0, xmm1
00643cca comiss xmm1, xmm0
00643ccd jb 0x643d23
00643ccf inc word ptr [edi + 0x3be]
00643cd6 sub esp, 0x10
00643cd9 mov byte ptr [edi + 0x16b], 0
00643ce0 mov eax, esp
00643ce2 movss xmm1, dword ptr [edi + 0x2c8]
00643cea mov edx, edi
00643cec movss xmm2, dword ptr [edi + 0x2e0]
00643cf4 movups xmm0, xmmword ptr [esi]
00643cf7 lea esi, [edi + 0x294]
00643cfd mov byte ptr [ebp - 0x674], 1
00643d04 addss xmm1, dword ptr [0xb6a9c8]
00643d0c mulss xmm2, dword ptr [0xb6a38c]
00643d14 mov ecx, esi
00643d16 movups xmmword ptr [eax], xmm0
00643d19 call 0x656e40
00643d1e add esp, 0x10
00643d21 jmp 0x643d29
00643d23 lea esi, [edi + 0x294]
00643d29 movss xmm1, dword ptr [ebp - 0x684]
00643d31 mov dword ptr [ebp - 0x6d4], 0x3f800000
00643d3b movaps xmm0, xmm1
00643d3e mov ecx, dword ptr [edi + 0x2c]
00643d41 mov dword ptr [ebp - 0x6a4], 0
00643d4b mov dword ptr [ebp - 0x670], 0
00643d55 mov dword ptr [ebp - 0x694], 0
00643d5f movss dword ptr [ebp - 0x69c], xmm0
00643d67 movss dword ptr [ebp - 0x66c], xmm1
00643d6f cmp ecx, 0x32
00643d72 ja 0x6445bd
00643d78 movzx eax, byte ptr [ecx + 0x64dbb8]
00643d7f jmp dword ptr [eax*4 + 0x64db80]
00643d86 movss xmm0, dword ptr [edi + 0x370]
00643d8e movss xmm2, dword ptr [ebp - 0x6cc]
00643d96 comiss xmm2, xmm0
00643d99 jbe 0x643dbc
00643d9b movss xmm0, dword ptr [0xb6a50c]
00643da3 mov dword ptr [ebp - 0x694], 0x102
00643dad mov dword ptr [ebp - 0x6a4], 0x50
00643db7 jmp 0x6445b5
00643dbc movss xmm2, dword ptr [0xb6a560]
00643dc4 comiss xmm2, xmm0
00643dc7 jbe 0x643dea
00643dc9 movss xmm0, dword ptr [0xb6a588]
00643dd1 mov dword ptr [ebp - 0x694], 0x102
00643ddb mov dword ptr [ebp - 0x6a4], 0x4f
00643de5 jmp 0x6445b5
00643dea movss xmm0, dword ptr [edi + 0x360]
00643df2 lea esi, [edi + 0x294]
00643df8 comiss xmm0, dword ptr [0xb6ae98]
00643dff movaps xmm0, xmm1
00643e02 movss dword ptr [ebp - 0x69c], xmm0
00643e0a jbe 0x643e25
00643e0c mov dword ptr [ebp - 0x694], 0x102
00643e16 mov dword ptr [ebp - 0x6a4], 0xd
00643e20 jmp 0x6445c3
00643e25 mov dword ptr [ebp - 0x694], 0x96
00643e2f mov dword ptr [ebp - 0x6a4], 0xc
00643e39 jmp 0x6445c3
00643e3e mov dword ptr [ebp - 0x6a4], 0xb
00643e48 mov dword ptr [ebp - 0x694], 0x96
00643e52 jmp 0x6445b5
00643e57 lea ecx, [edi + 0x3c]
00643e5a call 0x4023b0
00643e5f push eax
00643e60 lea ecx, [ebp - 0x128]
00643e66 call 0x402170
00643e6b cmp dword ptr [edi + 0x2c], 0x1e
00643e6f jne 0x643ebc
00643e71 movss xmm0, dword ptr [ebp - 0x6b8]
00643e79 lea ecx, [ebp - 0x504]
00643e7f movaps xmm3, xmm0
00643e82 movaps xmm2, xmm0
00643e85 movaps xmm1, xmm0
00643e88 call 0x427080
00643e8d sub esp, 0x2c
00643e90 mov esi, eax
00643e92 lea eax, [ebp - 0x128]
00643e98 mov ecx, esp
00643e9a push eax
00643e9b call 0x402170
00643ea0 mov edx, esi
00643ea2 lea ecx, [ebp - 0x2f4]
00643ea8 call 0x402290
00643ead add esp, 0x2c
00643eb0 lea ecx, [ebp - 0x128]
00643eb6 push eax
00643eb7 call 0x4021a0
00643ebc movss xmm0, dword ptr [edi + 0x360]
00643ec4 lea eax, [ebp - 0x128]
00643eca push 1
00643ecc push ecx
00643ecd movss dword ptr [esp], xmm0
00643ed2 push eax
00643ed3 call 0x659200
00643ed8 mulss xmm0, dword ptr [ebp - 0x688]
00643ee0 lea esi, [edi + 0x294]
00643ee6 push ecx
00643ee7 mov ecx, dword ptr [0xbfd65c]
00643eed addss xmm0, dword ptr [0xb6a7b0]
00643ef5 movss dword ptr [esp], xmm0
00643efa push 8
00643efc push 0x23
00643efe push esi
00643eff call 0x6d57a0
00643f04 movss xmm0, dword ptr [ebp - 0x68c]
00643f0c mov dword ptr [ebp - 0x6a4], 0x61
00643f16 mov dword ptr [ebp - 0x694], 0xb5
00643f20 movss dword ptr [ebp - 0x69c], xmm0
00643f28 call 0x659200
00643f2d mulss xmm0, dword ptr [0xb6a350]
00643f35 addss xmm0, dword ptr [ebp - 0x684]
00643f3d movss dword ptr [ebp - 0x66c], xmm0
00643f45 jmp 0x6445c3
00643f4a movss xmm0, dword ptr [edi + 0x360]
00643f52 push 1
00643f54 push ecx
00643f55 lea ecx, [edi + 0x3c]
00643f58 movss dword ptr [esp], xmm0
00643f5d call 0x4023b0
00643f62 push eax
00643f63 call 0x659200
00643f68 mulss xmm0, dword ptr [ebp - 0x688]
00643f70 push ecx
00643f71 mov ecx, dword ptr [0xbfd65c]
00643f77 addss xmm0, dword ptr [0xb6a7b0]
00643f7f movss dword ptr [esp], xmm0
00643f84 push 4
00643f86 push 0x23
00643f88 push esi
00643f89 call 0x6d57a0
00643f8e movss xmm0, dword ptr [ebp - 0x6b8]
00643f96 mov dword ptr [ebp - 0x6a4], 0x61
00643fa0 mov dword ptr [ebp - 0x694], 0x8a
00643faa movss dword ptr [ebp - 0x69c], xmm0
00643fb2 call 0x659200
00643fb7 mulss xmm0, dword ptr [ebp - 0x68c]
00643fbf addss xmm0, dword ptr [ebp - 0x688]
00643fc7 movss dword ptr [ebp - 0x66c], xmm0
00643fcf jmp 0x6445bd
00643fd4 movss xmm0, dword ptr [ebp - 0x6b8]
00643fdc mov dword ptr [ebp - 0x6a4], 0x14
00643fe6 mov dword ptr [ebp - 0x694], 0x31
00643ff0 movss dword ptr [ebp - 0x69c], xmm0
00643ff8 call 0x659200
00643ffd mulss xmm0, dword ptr [0xb6a2cc]
00644005 addss xmm0, dword ptr [0xb6a5d8]
0064400d movss dword ptr [ebp - 0x66c], xmm0
00644015 jmp 0x6445bd
0064401a movss xmm0, dword ptr [edi + 0x360]
00644022 push 1
00644024 push ecx
00644025 lea ecx, [edi + 0x3c]
00644028 movss dword ptr [esp], xmm0
0064402d call 0x4023b0
00644032 push eax
00644033 call 0x659200
00644038 mulss xmm0, dword ptr [ebp - 0x688]
00644040 push ecx
00644041 mov ecx, 2
00644046 addss xmm0, dword ptr [0xb6a7b0]
0064404e movss dword ptr [esp], xmm0
00644053 call 0x659230
00644058 add eax, 2
0064405b push eax
0064405c push 0x55
0064405e mov ecx, dword ptr [0xbfd65c]
00644064 push esi
00644065 call 0x6d57a0
0064406a movss xmm0, dword ptr [ebp - 0x6b8]
00644072 mov dword ptr [ebp - 0x6a4], 0x61
0064407c mov dword ptr [ebp - 0x694], 0x8a
00644086 movss dword ptr [ebp - 0x69c], xmm0
0064408e call 0x659200
00644093 mulss xmm0, dword ptr [ebp - 0x68c]
0064409b addss xmm0, dword ptr [0xb6a7b0]
006440a3 movss dword ptr [ebp - 0x66c], xmm0
006440ab jmp 0x6445bd
006440b0 cmp ecx, 0xd
006440b3 je 0x6440be
006440b5 cmp ecx, 0x17
006440b8 jne 0x64413d
006440be mov ecx, dword ptr [0xbfd65c]
006440c4 push 0x4f
006440c6 call 0x427910
006440cb mov ecx, eax
006440cd call 0x4480b0
006440d2 test al, al
006440d4 je 0x64413d
006440d6 mov ecx, 5
006440db call 0x659230
006440e0 test eax, eax
006440e2 jne 0x644133
006440e4 test byte ptr [edi + 0x3c4], 1
006440eb je 0x644133
006440ed movss xmm0, dword ptr [ebp - 0x684]
006440f5 mov dword ptr [ebp - 0x694], 0x33f
006440ff movss dword ptr [ebp - 0x69c], xmm0
00644107 call 0x659200
0064410c mulss xmm0, dword ptr [ebp - 0x6c4]
00644114 mov dword ptr [ebp - 0x6a4], 0x61
0064411e addss xmm0, dword ptr [0xb6a560]
00644126 movss dword ptr [ebp - 0x66c], xmm0
0064412e jmp 0x6445bd
00644133 movss xmm0, dword ptr [ebp - 0x67c]
0064413b jmp 0x644195
0064413d movss xmm0, dword ptr [edi + 0x360]
00644145 push 1
00644147 push ecx
00644148 lea ecx, [edi + 0x3c]
0064414b movss dword ptr [esp], xmm0
00644150 call 0x4023b0
00644155 push eax
00644156 call 0x659200
0064415b mulss xmm0, dword ptr [ebp - 0x688]
00644163 push ecx
00644164 mov ecx, 2
00644169 addss xmm0, dword ptr [0xb6a7b0]
00644171 movss dword ptr [esp], xmm0
00644176 call 0x659230
0064417b mov ecx, dword ptr [0xbfd65c]
00644181 add eax, 2
00644184 push eax
00644185 push 0x56
00644187 push esi
00644188 call 0x6d57a0
0064418d movss xmm0, dword ptr [ebp - 0x6b8]
00644195 mov dword ptr [ebp - 0x694], 0x8a
0064419f movss dword ptr [ebp - 0x69c], xmm0
006441a7 call 0x659200
006441ac mulss xmm0, dword ptr [ebp - 0x68c]
006441b4 mov dword ptr [ebp - 0x6a4], 0x61
006441be addss xmm0, dword ptr [0xb6a7b0]
006441c6 movss dword ptr [ebp - 0x66c], xmm0
006441ce jmp 0x6445bd
006441d3 movss xmm0, dword ptr [edi + 0x360]
006441db push 1
006441dd push ecx
006441de lea ecx, [edi + 0x3c]
006441e1 movss dword ptr [esp], xmm0
006441e6 call 0x4023b0
006441eb push eax
006441ec call 0x659200
006441f1 mulss xmm0, dword ptr [ebp - 0x688]
006441f9 push ecx
006441fa mov ecx, 2
006441ff addss xmm0, dword ptr [0xb6a7b0]
00644207 movss dword ptr [esp], xmm0
0064420c call 0x659230
00644211 add eax, 4
00644214 push eax
00644215 push 0x62
00644217 jmp 0x64405e
0064421c movss xmm2, dword ptr [edi + 0x370]
00644224 mulss xmm2, dword ptr [0xb6a6c8]
0064422c mov dword ptr [ebp - 0x694], 0x1e7
00644236 movss xmm0, dword ptr [ebp - 0x68c]
0064423e call 0x9623e0
00644243 movss xmm2, dword ptr [ebp - 0x684]
0064424b divss xmm2, dword ptr [edi + 0x370]
00644253 movss xmm1, dword ptr [0xb6a754]
0064425b movss dword ptr [ebp - 0x69c], xmm0
00644263 movss xmm0, dword ptr [0xb6a5d8]
0064426b call 0x9623e0
00644270 push ecx
00644271 mov ecx, dword ptr [0xbfd65c]
00644277 mov dword ptr [esp], 0xc1a00000
0064427e push esi
0064427f movss dword ptr [ebp - 0x66c], xmm0
00644287 mov dword ptr [ebp - 0x6a4], 0x91
00644291 call 0x4023f0
00644296 mov ecx, eax
00644298 call 0x7cf0a0
0064429d test al, al
0064429f je 0x6445bd
006442a5 lea ecx, [ebp - 0xfc]
006442ab call 0x402120
006442b0 push 0xff
006442b5 push 0x7b
006442b7 push 0x7b
006442b9 push 0x8c
006442be lea ecx, [ebp - 0xfc]
006442c4 call 0x65ae50
006442c9 lea ecx, [edi + 0x3c]
006442cc call 0x4023b0
006442d1 push eax
006442d2 lea ecx, [ebp - 0xfc]
006442d8 call 0x65b0f0
006442dd mov dword ptr [ebp - 0x8f8], 0x10
006442e7 mov dword ptr [ebp - 0x8f0], 1
006442f1 call 0x659200
006442f6 mulss xmm0, dword ptr [ebp - 0x68c]
006442fe lea edx, [ebp - 0x8f0]
00644304 lea ecx, [ebp - 0x8f4]
0064430a movss xmm1, dword ptr [edi + 0x370]
00644312 mulss xmm1, dword ptr [0xb6a8cc]
0064431a addss xmm0, dword ptr [ebp - 0x684]
00644322 mulss xmm1, xmm0
00644326 cvttss2si eax, xmm1
0064432a mov dword ptr [ebp - 0x8f4], eax
00644330 call 0x417c80
00644335 lea edx, [ebp - 0x8f8]
0064433b mov ecx, eax
0064433d call 0x417c60
00644342 mov eax, dword ptr [eax]
00644344 mov dword ptr [ebp - 0x6a0], eax
0064434a test eax, eax
0064434c jle 0x6445bd
00644352 lea esi, [edi + 0x2c8]
00644358 lea eax, [edi + 0x2a4]
0064435e mov dword ptr [ebp - 0x668], esi
00644364 mov edi, dword ptr [ebp - 0x6d0]
0064436a mov dword ptr [ebp - 0x678], eax
00644370 call 0x659200
00644375 mulss xmm0, dword ptr [0xb6ac40]
0064437d lea eax, [ebp - 0xa3c]
00644383 push ecx
00644384 movss dword ptr [esp], xmm0
00644389 push eax
0064438a call 0x9627f0
0064438f add esp, 8
00644392 call 0x659200
00644397 mulss xmm0, dword ptr [0xb6a7b0]
0064439f addss xmm0, dword ptr [ebp - 0x684]
006443a7 movss dword ptr [ebp - 0x900], xmm0
006443af call 0x659200
006443b4 push esi
006443b5 lea eax, [ebp - 0x12b4]
006443bb movss dword ptr [ebp - 0x8fc], xmm0
006443c3 push eax
006443c4 lea eax, [ebp - 0x8fc]
006443ca push eax
006443cb lea eax, [ebp - 0x12bc]
006443d1 push eax
006443d2 lea ecx, [ebp - 0xa3c]
006443d8 call 0x962b50
006443dd mov ecx, eax
006443df call 0x962b50
006443e4 push eax
006443e5 lea eax, [ebp - 0xb6c]
006443eb mov ecx, edi
006443ed push eax
006443ee call 0x962a60
006443f3 call 0x6c3d90
006443f8 push eax
006443f9 push 1
006443fb push 0
006443fd lea eax, [ebp - 0x900]
00644403 push eax
00644404 lea eax, [ebp - 0x12c4]
0064440a push eax
0064440b lea ecx, [ebp - 0xa3c]
00644411 call 0x962b50
00644416 mov ecx, dword ptr [0xbfd65c]
0064441c push eax
0064441d lea eax, [ebp - 0xb6c]
00644423 push eax
00644424 push 0x23
00644426 push 0x3e8
0064442b call 0x422e20
00644430 push dword ptr [ebp - 0x678]
00644436 mov esi, eax
00644438 mov ecx, esi
0064443a call 0x412190
0064443f mov eax, dword ptr [esi]
00644441 lea ecx, [ebp - 0xfc]
00644447 push 1
00644449 push 0
0064444b push 0xff
00644450 mov eax, dword ptr [eax + 0x38]
00644453 push -1
00644455 push ecx
00644456 mov ecx, esi
00644458 call eax
0064445a mov eax, dword ptr [esi]
0064445c mov ecx, esi
0064445e mov eax, dword ptr [eax + 0xc]
00644461 call eax
00644463 sub dword ptr [ebp - 0x6a0], 1
0064446a mov esi, dword ptr [ebp - 0x668]
00644470 jne 0x644370
00644476 mov edi, dword ptr [ebp - 0x6a8]
0064447c jmp 0x6445bd
00644481 movss xmm0, dword ptr [edi + 0x360]
00644489 push 1
0064448b push ecx
0064448c lea ecx, [edi + 0x3c]
0064448f movss dword ptr [esp], xmm0
00644494 call 0x4023b0
00644499 push eax
0064449a call 0x659200
0064449f mulss xmm0, dword ptr [ebp - 0x688]
006444a7 push ecx
006444a8 mov ecx, 2
006444ad addss xmm0, dword ptr [0xb6a7b0]
006444b5 movss dword ptr [esp], xmm0
006444ba call 0x659230
006444bf mov ecx, dword ptr [0xbfd65c]
006444c5 add eax, 2
006444c8 push eax
006444c9 push 0x56
006444cb push esi
006444cc call 0x6d57a0
006444d1 mov dword ptr [ebp - 0x694], 0x8a
006444db call 0x659200
006444e0 mulss xmm0, dword ptr [ebp - 0x68c]
006444e8 xor eax, eax
006444ea cmp dword ptr [edi + 0x2c], 0x2c
006444ee mov dword ptr [ebp - 0x6a4], 0xc
006444f8 sete al
006444fb addss xmm0, dword ptr [0xb6a7b0]
00644503 add eax, 0x14
00644506 mov dword ptr [ebp - 0x670], eax
0064450c movss dword ptr [ebp - 0x66c], xmm0
00644514 movss xmm0, dword ptr [ebp - 0x6b8]
0064451c jmp 0x6445b5
00644521 mov dword ptr [ebp - 0x694], 0x31
0064452b call 0x659200
00644530 mulss xmm0, dword ptr [ebp - 0x68c]
00644538 mov dword ptr [ebp - 0x6a4], 0xc
00644542 mov dword ptr [ebp - 0x670], 0x16
0064454c addss xmm0, dword ptr [0xb6a7b0]
00644554 movss dword ptr [ebp - 0x66c], xmm0
0064455c movss xmm0, dword ptr [ebp - 0x6b8]
00644564 jmp 0x6445b5
00644566 mov dword ptr [ebp - 0x694], 0x86
00644570 jmp 0x64452b
00644572 mov dword ptr [ebp - 0x694], 0x1e
0064457c call 0x659200
00644581 mulss xmm0, dword ptr [ebp - 0x68c]
00644589 mov dword ptr [ebp - 0x6a4], 2
00644593 mov dword ptr [ebp - 0x670], 2
0064459d addss xmm0, dword ptr [0xb6a6f0]
006445a5 movss dword ptr [ebp - 0x66c], xmm0
006445ad movss xmm0, dword ptr [ebp - 0x6c4]
006445b5 movss dword ptr [ebp - 0x69c], xmm0
006445bd lea esi, [edi + 0x294]
006445c3 push 0xbc4ca0
006445c8 lea edx, [edi + 0x378]
006445ce lea ecx, [ebp - 0x2114]
006445d4 call 0x412050
006445d9 add esp, 4
006445dc mov ecx, eax
006445de call 0x412090
006445e3 test al, al
006445e5 je 0x644624
006445e7 test byte ptr [edi + 0x30], 2
006445eb jne 0x644624
006445ed push 0xbc4ce0
006445f2 lea edx, [edi + 0x378]
006445f8 lea ecx, [ebp - 0x2124]
006445fe call 0x412050
00644603 add esp, 4
00644606 mov ecx, eax
00644608 call 0x427260
0064460d test al, al
0064460f jne 0x64462e
00644611 cmp word ptr [edi + 0x3be], 1
00644619 jg 0x64462e
0064461b test byte ptr [edi + 0x3c4], 0x20
00644622 jne 0x64462e
00644624 cmp dword ptr [edi + 0x2c], 4
00644628 jne 0x6448f1
0064462e movups xmm0, xmmword ptr [edi + 0x378]
00644635 push ecx
00644636 mov dword ptr [esp], 0x3f800000
0064463d push edi
0064463e sub esp, 0x10
00644641 mov dword ptr [ebp - 0x6a4], 1
0064464b mov eax, esp
0064464d push ecx
0064464e mov ecx, dword ptr [0xbfd65c]
00644654 movups xmmword ptr [eax], xmm0
00644657 mov dword ptr [esp], 0x42700000
0064465e push esi
0064465f call 0x6d2fb0
00644664 cmp byte ptr [ebp - 0x674], 0
0064466b movss xmm0, dword ptr [edi + 0x2e0]
00644673 movss dword ptr [ebp - 0x678], xmm0
0064467b je 0x64468d
0064467d mulss xmm0, dword ptr [ebp - 0x68c]
00644685 movss dword ptr [ebp - 0x678], xmm0
0064468d cmp dword ptr [edi + 0x2c], 4
00644691 mov dword ptr [ebp - 0x6a0], 4
0064469b jne 0x6446a7
0064469d mov dword ptr [ebp - 0x6a0], 0x40000004
006446a7 movss xmm0, dword ptr [edi + 0x2c8]
006446af movss xmm1, dword ptr [0xb6a958]
006446b7 comiss xmm1, xmm0
006446ba jbe 0x6446e8
006446bc mulss xmm0, dword ptr [0xb6aa8c]
006446c4 lea ecx, [ebp - 0x904]
006446ca mov dword ptr [ebp - 0x904], 0x41f00000
006446d4 lea edx, [ebp - 0x908]
006446da divss xmm0, xmm1
006446de movss dword ptr [ebp - 0x908], xmm0
006446e6 jmp 0x64470e
006446e8 addss xmm0, dword ptr [ebp - 0x6c0]
006446f0 mov dword ptr [ebp - 0x914], 0x42700000
006446fa lea ecx, [ebp - 0x910]
00644700 lea edx, [ebp - 0x914]
00644706 movss dword ptr [ebp - 0x910], xmm0
0064470e call 0x417c70
00644713 mov ecx, dword ptr [0xbfd65c]
00644719 push 0
0064471b push 0
0064471d movss xmm1, dword ptr [eax]
00644721 push dword ptr [ebp - 0x6a0]
00644727 movaps xmm0, xmm1
0064472a divss xmm0, dword ptr [0xb6aa8c]
00644732 sub esp, 0x10
00644735 mov eax, esp
00644737 push edi
00644738 push 1
0064473a sub esp, 8
0064473d movss dword ptr [ebp - 0x6d4], xmm0
00644745 movups xmm0, xmmword ptr [edi + 0x378]
0064474c movups xmmword ptr [eax], xmm0
0064474f movss xmm0, dword ptr [ebp - 0x678]
00644757 movss dword ptr [esp + 4], xmm1
0064475d movss dword ptr [esp], xmm0
00644762 push esi
00644763 call 0x6d1750
00644768 push 0xbc4c30
0064476d lea edx, [edi + 0x378]
00644773 lea ecx, [ebp - 0x2134]
00644779 call 0x412050
0064477e add esp, 4
00644781 mov ecx, eax
00644783 call 0x412090
00644788 test al, al
0064478a je 0x6448f1
00644790 call 0x6c3d90
00644795 mov ecx, dword ptr [0xbfd65c]
0064479b push 0
0064479d push 0xbeaaec
006447a2 push 0xbeab18
006447a7 push 0
006447a9 push eax
006447aa push 0
006447ac push 0
006447ae push 0xc02fec
006447b3 push esi
006447b4 push 7
006447b6 push 0x3e8
006447bb call 0x422e20
006447c0 push eax
006447c1 call 0x9ec34c
006447c6 add esp, 0x14
006447c9 mov edi, eax
006447cb call 0x659200
006447d0 addss xmm0, dword ptr [ebp - 0x684]
006447d8 lea ecx, [ebp - 0x12cc]
006447de mulss xmm0, dword ptr [ebp - 0x6d4]
006447e6 movaps xmm2, xmm0
006447e9 movaps xmm1, xmm0
006447ec call 0x9624e0
006447f1 push eax
006447f2 mov ecx, edi
006447f4 call 0x427330
006447f9 movss xmm3, dword ptr [0xb6a234]
00644801 movss xmm2, dword ptr [0xb6a5a4]
00644809 movaps xmm1, xmm3
0064480c mov esi, dword ptr [edi]
0064480e push 1
00644810 push 0
00644812 push 0xff
00644817 push -1
00644819 push 0
0064481b push 0x55
0064481d push 0
0064481f push ecx
00644820 lea ecx, [ebp - 0x4ac]
00644826 mov dword ptr [esp], 0x3f800000
0064482d call 0x4270d0
00644832 push eax
00644833 mov eax, dword ptr [esi + 0x38]
00644836 mov ecx, edi
00644838 call eax
0064483a mov eax, dword ptr [edi]
0064483c mov ecx, edi
0064483e mov eax, dword ptr [eax + 0xc]
00644841 call eax
00644843 call 0x6c3d90
00644848 mov ecx, dword ptr [0xbfd65c]
0064484e push eax
0064484f push 4
00644851 push 0
00644853 push 0xc02fec
00644858 push dword ptr [ebp - 0x6d0]
0064485e push 2
00644860 push 0x3e8
00644865 call 0x422e20
0064486a movss xmm3, dword ptr [0xb6a234]
00644872 mov edi, eax
00644874 movss xmm2, dword ptr [0xb6a5a4]
0064487c movaps xmm1, xmm3
0064487f push 1
00644881 push 0
00644883 mov esi, dword ptr [edi]
00644885 push 0xff
0064488a push -1
0064488c push 0
0064488e push 0x64
00644890 push 0xa
00644892 push ecx
00644893 lea ecx, [ebp - 0x480]
00644899 mov dword ptr [esp], 0x3f800000
006448a0 call 0x4270d0
006448a5 push eax
006448a6 mov eax, dword ptr [esi + 0x38]
006448a9 mov ecx, edi
006448ab call eax
006448ad movss xmm1, dword ptr [ebp - 0x6d4]
006448b5 lea ecx, [ebp - 0x12d4]
006448bb movaps xmm2, xmm1
006448be mulss xmm2, dword ptr [ebp - 0x6cc]
006448c6 call 0x9624e0
006448cb push eax
006448cc mov ecx, edi
006448ce call 0x427330
006448d3 push ecx
006448d4 mov ecx, edi
006448d6 mov dword ptr [esp], 0xc0a00000
006448dd call 0x4273d0
006448e2 mov eax, dword ptr [edi]
006448e4 mov ecx, edi
006448e6 mov eax, dword ptr [eax + 0xc]
006448e9 call eax
006448eb mov edi, dword ptr [ebp - 0x6a8]
006448f1 lea esi, [edi + 0x378]
006448f7 push 0xbc46b0
006448fc mov edx, esi
006448fe lea ecx, [ebp - 0x2144]
00644904 call 0x412050
00644909 add esp, 4
0064490c mov ecx, eax
0064490e call 0x412090
00644913 test al, al
00644915 mov eax, dword ptr [ebp - 0x6a4]
0064491b je 0x64492b
0064491d xor ecx, ecx
0064491f cmp eax, 1
00644922 cmovne eax, ecx
00644925 mov dword ptr [ebp - 0x6a4], eax
0064492b cmp byte ptr [ebp - 0x674], 0
00644932 movss xmm1, dword ptr [ebp - 0x69c]
0064493a je 0x644961
0064493c cmp eax, 1
0064493f je 0x644961
00644941 mulss xmm1, dword ptr [ebp - 0x68c]
00644949 xor ecx, ecx
0064494b cmp eax, 0xb
0064494e mov dword ptr [ebp - 0x6a4], 0xe
00644958 sete cl
0064495b mov dword ptr [ebp - 0x670], ecx
00644961 mov ecx, dword ptr [ebp - 0x694]
00644967 test ecx, ecx
00644969 je 0x644993
0064496b movss xmm0, dword ptr [ebp - 0x66c]
00644973 lea eax, [edi + 0x294]
00644979 push ecx
0064497a movss dword ptr [esp], xmm0
0064497f movaps xmm3, xmm1
00644982 push 0
00644984 push 2
00644986 push eax
00644987 push ecx
00644988 mov ecx, dword ptr [0xbfd680]
0064498e call 0x8b14e0
00644993 push 0xbc4a00
00644998 mov edx, esi
0064499a lea ecx, [ebp - 0x2154]
006449a0 call 0x412050
006449a5 add esp, 4
006449a8 mov ecx, eax
006449aa call 0x412090
006449af test al, al
006449b1 je 0x644dc3
006449b7 lea eax, [ebp - 0x770]
006449bd push eax
006449be call 0x659290
006449c3 add esp, 4
006449c6 lea ecx, [edi + 0x2b8]
006449cc call 0x962a30
006449d1 movss xmm0, dword ptr [0xb6a2cc]
006449d9 fstp dword ptr [ebp - 0x668]
006449df comiss xmm0, dword ptr [ebp - 0x668]
006449e6 jbe 0x6449fa
006449e8 mov dword ptr [ebp - 0x918], 0x41200000
006449f2 lea eax, [ebp - 0x918]
006449f8 jmp 0x644a11
006449fa lea ecx, [edi + 0x2b8]
00644a00 call 0x962a00
00644a05 fstp dword ptr [ebp - 0x91c]
00644a0b lea eax, [ebp - 0x91c]
00644a11 push eax
00644a12 lea ecx, [ebp - 0x770]
00644a18 call 0x962bb0
00644a1d mov dword ptr [ebp - 0x694], 0
00644a27 nop word ptr [eax + eax]
00644a30 lea ecx, [ebp - 0x760]
00644a36 call 0x9624d0
00644a3b cmp dword ptr [ebp - 0x694], 2
00644a42 jae 0x644a4c
00644a44 lea eax, [ebp - 0x770]
00644a4a jmp 0x644a6e
00644a4c movss xmm2, dword ptr [ebp - 0x770]
00644a54 lea ecx, [ebp - 0x12dc]
00644a5a xorps xmm2, xmmword ptr [0xb6c9b0]
00644a61 movss xmm1, dword ptr [ebp - 0x76c]
00644a69 call 0x9624e0
00644a6e push eax
00644a6f lea ecx, [ebp - 0x760]
00644a75 call 0x962cd0
00644a7a test byte ptr [ebp - 0x694], 1
00644a81 je 0x644aa1
00644a83 lea eax, [ebp - 0x12e4]
00644a89 push eax
00644a8a lea ecx, [ebp - 0x760]
00644a90 call 0x962b20
00644a95 push eax
00644a96 lea ecx, [ebp - 0x760]
00644a9c call 0x962cd0
00644aa1 mov ecx, edi
00644aa3 call 0x6414a0
00644aa8 mov esi, dword ptr [edi + 0x2c]
00644aab cmp esi, 0x32
00644aae mov dword ptr [ebp - 0x678], eax
00644ab4 mov eax, 1
00644ab9 cmove esi, eax
00644abc call 0x6c3d90
00644ac1 push 0
00644ac3 push 0xbeae24
00644ac8 push 0xbeab18
00644acd push 0
00644acf push eax
00644ad0 push 0
00644ad2 push dword ptr [edi + 0x320]
00644ad8 lea eax, [ebp - 0x760]
00644ade push eax
00644adf lea eax, [edi + 0x2b8]
00644ae5 push eax
00644ae6 lea eax, [ebp - 0x12ec]
00644aec push eax
00644aed lea ecx, [edi + 0x294]
00644af3 call 0x962ac0
00644af8 mov ecx, dword ptr [0xbfd65c]
00644afe push eax
00644aff push esi
00644b00 push dword ptr [edi + 0x28]
00644b03 call 0x422e20
00644b08 push eax
00644b09 call 0x9ec34c
00644b0e mov esi, eax
00644b10 add esp, 0x14
00644b13 mov eax, dword ptr [ebp - 0x678]
00644b19 mov dword ptr [ebp - 0x66c], esi
00644b1f test eax, eax
00644b21 je 0x644b2c
00644b23 mov ecx, eax
00644b25 call 0x5b76b0
00644b2a jmp 0x644b34
00644b2c movss xmm0, dword ptr [ebp - 0x680]
00644b34 mulss xmm0, dword ptr [ebp - 0x68c]
00644b3c push ecx
00644b3d mov ecx, esi
00644b3f movss dword ptr [esp], xmm0
00644b44 call 0x6500f0
00644b49 push 0xbc46c0
00644b4e lea edx, [edi + 0x378]
00644b54 lea ecx, [ebp - 0x2164]
00644b5a call 0x412050
00644b5f add esp, 4
00644b62 mov ecx, eax
00644b64 call 0x412090
00644b69 test al, al
00644b6b je 0x644b8a
00644b6d mov eax, dword ptr [ebp - 0x678]
00644b73 test eax, eax
00644b75 je 0x644b80
00644b77 mov ecx, eax
00644b79 call 0x5ef490
00644b7e jmp 0x644b92
00644b80 movss xmm0, dword ptr [ebp - 0x67c]
00644b88 jmp 0x644b92
00644b8a movss xmm0, dword ptr [edi + 0x368]
00644b92 push ecx
00644b93 mov ecx, dword ptr [ebp - 0x66c]
00644b99 movss dword ptr [esp], xmm0
00644b9e call 0x436b90
00644ba3 mov ecx, dword ptr [0xbfd65c]
00644ba9 push 0
00644bab call 0x412750
00644bb0 mov ecx, eax
00644bb2 call 0x5ef480
00644bb7 comiss xmm0, dword ptr [ebp - 0x67c]
00644bbe movss dword ptr [ebp - 0x678], xmm0
00644bc6 jbe 0x644bd8
00644bc8 mulss xmm0, dword ptr [ebp - 0x6b8]
00644bd0 movss dword ptr [ebp - 0x678], xmm0
00644bd8 lea eax, [ebp - 0x2174]
00644bde mov ecx, 0xbc48a0
00644be3 push eax
00644be4 call 0x57f3a0
00644be9 push eax
00644bea lea eax, [ebp - 0x13c4]
00644bf0 mov ecx, 0xbc46c0
00644bf5 push eax
00644bf6 call 0x57f3a0
00644bfb push eax
00644bfc lea eax, [ebp - 0x13d4]
00644c02 mov ecx, 0xbc4890
00644c07 push eax
00644c08 call 0x57f3a0
00644c0d push eax
00644c0e lea eax, [ebp - 0x13e4]
00644c14 mov ecx, 0xbc4a30
00644c19 push eax
00644c1a call 0x57f3a0
00644c1f push eax
00644c20 lea eax, [ebp - 0x13f4]
00644c26 mov ecx, 0xbc4ce0
00644c2b push eax
00644c2c call 0x57f3a0
00644c31 push eax
00644c32 lea eax, [ebp - 0x1404]
00644c38 mov ecx, 0xbc49e0
00644c3d push eax
00644c3e call 0x57f3a0
00644c43 push eax
00644c44 lea eax, [ebp - 0x1414]
00644c4a mov ecx, 0xbc4a00
00644c4f push eax
00644c50 call 0x57f3a0
00644c55 push eax
00644c56 lea edx, [edi + 0x378]
00644c5c lea ecx, [ebp - 0x1424]
00644c62 call 0x412050
00644c67 add esp, 4
00644c6a lea ecx, [ebp - 0x1434]
00644c70 mov edx, eax
00644c72 call 0x412050
00644c77 add esp, 4
00644c7a lea ecx, [ebp - 0x1444]
00644c80 mov edx, eax
00644c82 call 0x412050
00644c87 add esp, 4
00644c8a lea ecx, [ebp - 0x1454]
00644c90 mov edx, eax
00644c92 call 0x412050
00644c97 add esp, 4
00644c9a lea ecx, [ebp - 0x1464]
00644ca0 mov edx, eax
00644ca2 call 0x412050
00644ca7 add esp, 4
00644caa lea ecx, [ebp - 0x1474]
00644cb0 mov edx, eax
00644cb2 call 0x412050
00644cb7 add esp, 4
00644cba lea ecx, [ebp - 0xbbc]
00644cc0 mov edx, eax
00644cc2 call 0x412050
00644cc7 add esp, 4
00644cca cmp byte ptr [ebp - 0x674], 0
00644cd1 je 0x644cf0
00644cd3 lea eax, [ebp - 0x1484]
00644cd9 mov ecx, 0xbc4ca0
00644cde push eax
00644cdf call 0x57f3a0
00644ce4 push eax
00644ce5 lea ecx, [ebp - 0xbbc]
00644ceb call 0x6413c0
00644cf0 call 0x659200
00644cf5 mulss xmm0, dword ptr [0xb6a350]
00644cfd mov esi, dword ptr [ebp - 0x66c]
00644d03 push ecx
00644d04 mov ecx, esi
00644d06 subss xmm0, dword ptr [ebp - 0x678]
00644d0e movss dword ptr [esp], xmm0
00644d13 call 0x436b70
00644d18 movss xmm0, dword ptr [edi + 0x2e0]
00644d20 mov eax, dword ptr [esi]
00644d22 mulss xmm0, dword ptr [ebp - 0x68c]
00644d2a push ecx
00644d2b mov ecx, esi
00644d2d mov eax, dword ptr [eax + 0x3c]
00644d30 movss dword ptr [esp], xmm0
00644d35 call eax
00644d37 movups xmm0, xmmword ptr [ebp - 0xbbc]
00644d3e sub esp, 0x10
00644d41 mov ecx, esi
00644d43 mov eax, esp
00644d45 movups xmmword ptr [eax], xmm0
00644d48 call 0x650280
00644d4d movss xmm0, dword ptr [edi + 0x370]
00644d55 mulss xmm0, dword ptr [ebp - 0x6c4]
00644d5d push ecx
00644d5e mov ecx, esi
00644d60 movss dword ptr [esp], xmm0
00644d65 call 0x650250
00644d6a mov esi, dword ptr [esi]
00644d6c lea ecx, [edi + 0x3c]
00644d6f push 1
00644d71 push 0
00644d73 push 0xff
00644d78 push -1
00644d7a call 0x4023b0
00644d7f mov ecx, dword ptr [ebp - 0x66c]
00644d85 push eax
00644d86 mov eax, dword ptr [esi + 0x38]
00644d89 call eax
00644d8b push dword ptr [edi + 0x314]
00644d91 mov esi, dword ptr [ebp - 0x66c]
00644d97 mov ecx, esi
00644d99 call 0x6818e0
00644d9e mov eax, dword ptr [esi]
00644da0 mov ecx, esi
00644da2 mov eax, dword ptr [eax + 0xc]
00644da5 call eax
00644da7 mov eax, dword ptr [ebp - 0x694]
00644dad inc eax
00644dae mov dword ptr [ebp - 0x694], eax
00644db4 cmp eax, 4
00644db7 jl 0x644a30
00644dbd lea esi, [edi + 0x378]
00644dc3 push 0xbc49b0
00644dc8 mov edx, esi
00644dca lea ecx, [ebp - 0x1494]
00644dd0 call 0x412050
00644dd5 add esp, 4
00644dd8 mov ecx, eax
00644dda call 0x412090
00644ddf test al, al
00644de1 je 0x644df0
00644de3 push dword ptr [ebp - 0x674]
00644de9 mov ecx, edi
00644deb call 0x652120
00644df0 push 0xbc4770
00644df5 mov edx, esi
00644df7 lea ecx, [ebp - 0x14a4]
00644dfd call 0x412050
00644e02 add esp, 4
00644e05 mov ecx, eax
00644e07 call 0x412090
00644e0c test al, al
00644e0e je 0x644e33
00644e10 cmp byte ptr [edi + 0x16b], 0
00644e17 jne 0x644e22
00644e19 cmp dword ptr [edi + 0x3dc], 0
00644e20 jne 0x644e33
00644e22 mov ecx, dword ptr [edi + 0x3d8]
00644e28 test ecx, ecx
00644e2a je 0x644e33
00644e2c mov eax, dword ptr [ecx]
00644e2e mov eax, dword ptr [eax + 0x28]
00644e31 call eax
00644e33 cmp dword ptr [ebp - 0x6a4], 0
00644e3a jbe 0x64541d
00644e40 call 0x6c3d90
00644e45 push 0
00644e47 mov ecx, dword ptr [0xbfd65c]
00644e4d push 0xbeaaec
00644e52 push 0xbeab18
00644e57 push 0
00644e59 push eax
00644e5a push dword ptr [ebp - 0x670]
00644e60 lea eax, [edi + 0x294]
00644e66 push 0
00644e68 push 0xc02fec
00644e6d push eax
00644e6e push dword ptr [ebp - 0x6a4]
00644e74 push 0x3e8
00644e79 call 0x422e20
00644e7e push eax
00644e7f call 0x9ec34c
00644e84 add esp, 0x14
00644e87 mov esi, eax
00644e89 lea eax, [edi + 0x2a4]
00644e8f mov dword ptr [ebp - 0x66c], esi
00644e95 mov ecx, esi
00644e97 push eax
00644e98 call 0x412190
00644e9d mov eax, dword ptr [ebp - 0x6a4]
00644ea3 cmp eax, 1
00644ea6 je 0x644fd0
00644eac cmp eax, 0x4f
00644eaf je 0x644fd0
00644eb5 cmp eax, 0x50
00644eb8 je 0x644fd0
00644ebe cmp eax, 0xe
00644ec1 jne 0x644f28
00644ec3 movss xmm0, dword ptr [edi + 0x2c8]
00644ecb lea eax, [ebp - 0x920]
00644ed1 addss xmm0, dword ptr [0xb6a940]
00644ed9 push eax
00644eda lea eax, [ebp - 0x12f4]
00644ee0 mov ecx, 0xbc7a28
00644ee5 push eax
00644ee6 divss xmm0, dword ptr [0xb6aa04]
00644eee movss dword ptr [ebp - 0x920], xmm0
00644ef6 call 0x962b50
00644efb push eax
00644efc mov ecx, esi
00644efe call 0x427330
00644f03 movss xmm2, dword ptr [ebp - 0x67c]
00644f0b lea ecx, [ebp - 0x12fc]
00644f11 movss xmm1, dword ptr [edi + 0x2a4]
00644f19 call 0x9624e0
00644f1e push eax
00644f1f mov ecx, esi
00644f21 call 0x412190
00644f26 jmp 0x644f99
00644f28 cmp eax, 0x14
00644f2b je 0x644f61
00644f2d mov eax, dword ptr [edi + 0x2c]
00644f30 cmp eax, 0xf
00644f33 je 0x644f61
00644f35 cmp eax, 0xe
00644f38 je 0x644f61
00644f3a movss xmm0, dword ptr [edi + 0x370]
00644f42 lea eax, [ebp - 0x974]
00644f48 mulss xmm0, dword ptr [0xb6a560]
00644f50 push eax
00644f51 lea eax, [ebp - 0x1304]
00644f57 movss dword ptr [ebp - 0x974], xmm0
00644f5f jmp 0x644f86
00644f61 movss xmm0, dword ptr [edi + 0x370]
00644f69 lea eax, [ebp - 0x7a8]
00644f6f mulss xmm0, dword ptr [ebp - 0x6cc]
00644f77 push eax
00644f78 lea eax, [ebp - 0x130c]
00644f7e movss dword ptr [ebp - 0x7a8], xmm0
00644f86 push eax
00644f87 mov ecx, 0xbc7a28
00644f8c call 0x962b50
00644f91 push eax
00644f92 mov ecx, esi
00644f94 call 0x427330
00644f99 mov ecx, 4
00644f9e call 0x659230
00644fa3 push ecx
00644fa4 mov ecx, esi
00644fa6 movd xmm0, eax
00644faa cvtdq2pd xmm0, xmm0
00644fae shr eax, 0x1f
00644fb1 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
00644fba cvtpd2ps xmm0, xmm0
00644fbe mulss xmm0, dword ptr [0xb6aae4]
00644fc6 movss dword ptr [esp], xmm0
00644fcb call 0x430ce0
00644fd0 movss xmm0, dword ptr [ebp - 0x6d4]
00644fd8 ucomiss xmm0, dword ptr [ebp - 0x684]
00644fdf lahf 
00644fe0 test ah, 0x44
00644fe3 jnp 0x645009
00644fe5 lea eax, [ebp - 0x6d4]
00644feb mov ecx, esi
00644fed push eax
00644fee lea eax, [ebp - 0x1314]
00644ff4 push eax
00644ff5 call 0x4121c0
00644ffa mov ecx, eax
00644ffc call 0x962b50
00645001 push eax
00645002 mov ecx, esi
00645004 call 0x427330
00645009 mov eax, dword ptr [edi + 0x2c]
0064500c add eax, -3
0064500f cmp eax, 0x2d
00645012 ja 0x6453f6
00645018 movzx eax, byte ptr [eax + 0x64dc24]
0064501f jmp dword ptr [eax*4 + 0x64dbec]
00645026 push 1
00645028 push 0
0064502a push 0xff
0064502f push -1
00645031 lea ecx, [edi + 0x3c]
00645034 call 0x4023b0
00645039 movss xmm0, dword ptr [ebp - 0x6b8]
00645041 sub esp, 0x2c
00645044 movaps xmm3, xmm0
00645047 movaps xmm2, xmm0
0064504a movaps xmm1, xmm0
0064504d mov ecx, esp
0064504f mov esi, eax
00645051 call 0x427080
00645056 lea ecx, [ebp - 0x454]
0064505c mov edx, esi
0064505e call 0x402290
00645063 mov ecx, dword ptr [ebp - 0x66c]
00645069 add esp, 0x2c
0064506c push eax
0064506d mov eax, dword ptr [ecx]
0064506f mov eax, dword ptr [eax + 0x38]
00645072 jmp 0x645415
00645077 push 1
00645079 push 0
0064507b push 0xff
00645080 push -1
00645082 lea ecx, [edi + 0x3c]
00645085 call 0x4023b0
0064508a movss xmm3, dword ptr [0xb6a350]
00645092 sub esp, 0x2c
00645095 movss xmm2, dword ptr [0xb6a50c]
0064509d mov ecx, esp
0064509f movss xmm1, dword ptr [0xb6a6f0]
006450a7 mov esi, eax
006450a9 call 0x427080
006450ae lea ecx, [ebp - 0x428]
006450b4 jmp 0x64505c
006450b6 push 1
006450b8 push 0
006450ba push 0xff
006450bf push -1
006450c1 lea ecx, [edi + 0x3c]
006450c4 call 0x4023b0
006450c9 movss xmm0, dword ptr [0xb6a2cc]
006450d1 sub esp, 0x2c
006450d4 movaps xmm3, xmm0
006450d7 movaps xmm2, xmm0
006450da movaps xmm1, xmm0
006450dd mov ecx, esp
006450df mov esi, eax
006450e1 call 0x427080
006450e6 lea ecx, [ebp - 0x3fc]
006450ec jmp 0x64505c
006450f1 push 1
006450f3 push 0
006450f5 push 0xff
006450fa push -1
006450fc lea ecx, [edi + 0x3c]
006450ff call 0x4023b0
00645104 movss xmm3, dword ptr [ebp - 0x6cc]
0064510c sub esp, 0x2c
0064510f movss xmm2, dword ptr [ebp - 0x684]
00645117 mov ecx, esp
00645119 movss xmm1, dword ptr [ebp - 0x68c]
00645121 mov esi, eax
00645123 call 0x427080
00645128 lea ecx, [ebp - 0x3d0]
0064512e jmp 0x64505c
00645133 push 1
00645135 push 0
00645137 push 0xff
0064513c push -1
0064513e lea ecx, [edi + 0x3c]
00645141 call 0x4023b0
00645146 movss xmm3, dword ptr [0xb6a234]
0064514e sub esp, 0x2c
00645151 movss xmm2, dword ptr [ebp - 0x68c]
00645159 mov ecx, esp
0064515b movaps xmm1, xmm3
0064515e mov esi, eax
00645160 push 0
00645162 push 0x55
00645164 push 0
00645166 push ecx
00645167 mov dword ptr [esp], 0x3f800000
0064516e call 0x4270d0
00645173 lea ecx, [ebp - 0x3a4]
00645179 jmp 0x64505c
0064517e push 1
00645180 push 0
00645182 push 0xff
00645187 push -1
00645189 lea ecx, [edi + 0x3c]
0064518c call 0x4023b0
00645191 movss xmm0, dword ptr [ebp - 0x684]
00645199 sub esp, 0x2c
0064519c mov ecx, esp
0064519e movaps xmm3, xmm0
006451a1 movaps xmm2, xmm0
006451a4 movaps xmm1, xmm0
006451a7 mov esi, eax
006451a9 push 0xff
006451ae push 0x46
006451b0 push 0
006451b2 push ecx
006451b3 mov dword ptr [esp], 0x3f800000
006451ba call 0x4270d0
006451bf lea ecx, [ebp - 0x378]
006451c5 jmp 0x64505c
006451ca push 1
006451cc push 0
006451ce push 0xff
006451d3 push -1
006451d5 lea ecx, [edi + 0x3c]
006451d8 call 0x4023b0
006451dd movss xmm0, dword ptr [ebp - 0x684]
006451e5 sub esp, 0x2c
006451e8 mov ecx, esp
006451ea movaps xmm3, xmm0
006451ed movaps xmm2, xmm0
006451f0 movaps xmm1, xmm0
006451f3 mov esi, eax
006451f5 push 0
006451f7 push 0xe6
006451fc push 0xe6
00645201 push ecx
00645202 mov dword ptr [esp], 0x3f800000
00645209 call 0x4270d0
0064520e lea ecx, [ebp - 0x34c]
00645214 jmp 0x64505c
00645219 push 1
0064521b push 0
0064521d push 0xff
00645222 push -1
00645224 lea ecx, [edi + 0x3c]
00645227 call 0x4023b0
0064522c movss xmm3, dword ptr [ebp - 0x6b8]
00645234 sub esp, 0x2c
00645237 movss xmm2, dword ptr [ebp - 0x684]
0064523f mov ecx, esp
00645241 movss xmm1, dword ptr [0xb6a350]
00645249 mov esi, eax
0064524b push 0
0064524d push 0
0064524f push 0
00645251 push ecx
00645252 mov dword ptr [esp], 0x3f800000
00645259 call 0x4270d0
0064525e lea ecx, [ebp - 0x320]
00645264 jmp 0x64505c
00645269 push 1
0064526b push 0
0064526d push 0xff
00645272 push -1
00645274 lea ecx, [edi + 0x3c]
00645277 call 0x4023b0
0064527c movss xmm0, dword ptr [ebp - 0x68c]
00645284 sub esp, 0x2c
00645287 mov ecx, esp
00645289 movaps xmm3, xmm0
0064528c sub esp, 0x10
0064528f movaps xmm2, xmm0
00645292 movaps xmm1, xmm0
00645295 mov esi, eax
00645297 mov dword ptr [esp + 0xc], 0x3f000000
0064529f mov dword ptr [esp + 8], 0x3f000000
006452a7 mov dword ptr [esp + 4], 0x3f000000
006452af mov dword ptr [esp], 0x3f800000
006452b6 call 0x408270
006452bb lea ecx, [ebp - 0x218]
006452c1 jmp 0x64505c
006452c6 push 1
006452c8 push 0
006452ca push 0xff
006452cf push -1
006452d1 lea ecx, [edi + 0x3c]
006452d4 call 0x4023b0
006452d9 movss xmm0, dword ptr [0xb6a2cc]
006452e1 sub esp, 0x2c
006452e4 movaps xmm3, xmm0
006452e7 movaps xmm2, xmm0
006452ea movaps xmm1, xmm0
006452ed mov ecx, esp
006452ef mov esi, eax
006452f1 call 0x427080
006452f6 lea ecx, [ebp - 0x2c8]
006452fc jmp 0x64505c
00645301 push 1
00645303 push 0
00645305 push 0xff
0064530a push -1
0064530c lea ecx, [edi + 0x3c]
0064530f call 0x4023b0
00645314 movss xmm0, dword ptr [ebp - 0x6b8]
0064531c sub esp, 0x2c
0064531f movaps xmm3, xmm0
00645322 movaps xmm2, xmm0
00645325 movaps xmm1, xmm0
00645328 mov ecx, esp
0064532a mov esi, eax
0064532c call 0x427080
00645331 lea ecx, [ebp - 0x29c]
00645337 jmp 0x64505c
0064533c push 1
0064533e push 0
00645340 push 0xff
00645345 push -1
00645347 lea ecx, [edi + 0x3c]
0064534a call 0x4023b0
0064534f movss xmm0, dword ptr [ebp - 0x684]
00645357 sub esp, 0x2c
0064535a mov ecx, esp
0064535c movaps xmm3, xmm0
0064535f sub esp, 0x20
00645362 movaps xmm2, xmm0
00645365 movaps xmm1, xmm0
00645368 mov esi, eax
0064536a mov dword ptr [esp + 0x1c], 0
00645372 mov dword ptr [esp + 0x18], 0
0064537a mov dword ptr [esp + 0x14], 0
00645382 mov dword ptr [esp + 0x10], 0x3f800000
0064538a mov dword ptr [esp + 0xc], 0x3f47ae14
00645392 mov dword ptr [esp + 8], 0x3f19999a
0064539a mov dword ptr [esp + 4], 0x3f800000
006453a2 mov dword ptr [esp], 0x3f800000
006453a9 call 0x427150
006453ae lea ecx, [ebp - 0x270]
006453b4 jmp 0x64505c
006453b9 push 1
006453bb push 0
006453bd push 0xff
006453c2 push -1
006453c4 lea ecx, [edi + 0x3c]
006453c7 call 0x4023b0
006453cc movss xmm2, dword ptr [ebp - 0x6b8]
006453d4 sub esp, 0x2c
006453d7 movss xmm3, dword ptr [0xb6a50c]
006453df movaps xmm1, xmm2
006453e2 mov ecx, esp
006453e4 mov esi, eax
006453e6 call 0x427080
006453eb lea ecx, [ebp - 0x244]
006453f1 jmp 0x64505c
006453f6 mov esi, dword ptr [esi]
006453f8 lea ecx, [edi + 0x3c]
006453fb push 1
006453fd push 0
006453ff push 0xff
00645404 push -1
00645406 call 0x4023b0
0064540b mov ecx, dword ptr [ebp - 0x66c]
00645411 push eax
00645412 mov eax, dword ptr [esi + 0x38]
00645415 call eax
00645417 lea esi, [edi + 0x378]
0064541d mov eax, dword ptr [edi + 0x2c]
00645420 test eax, eax
00645422 je 0x645455
00645424 cmp eax, 0x18
00645427 je 0x645455
00645429 cmp eax, 0x10
0064542c je 0x645455
0064542e cmp eax, 0x1b
00645431 je 0x645455
00645433 cmp eax, 0x21
00645436 je 0x645455
00645438 cmp eax, 0x22
0064543b je 0x645455
0064543d cmp eax, 0x23
00645440 je 0x645455
00645442 cmp eax, 0x24
00645445 je 0x645455
00645447 cmp eax, 0x25
0064544a je 0x645455
0064544c cmp eax, 0x26
0064544f jne 0x6456b1
00645455 mov ecx, 5
0064545a call 0x659230
0064545f mov dword ptr [ebp - 0x6e8], eax
00645465 cmp dword ptr [edi + 0x2c], 0x1b
00645469 jne 0x64548e
0064546b lea edx, [ebp - 0x6e8]
00645471 mov dword ptr [ebp - 0x7ac], 3
0064547b lea ecx, [ebp - 0x7ac]
00645481 call 0x417c80
00645486 mov eax, dword ptr [eax]
00645488 mov dword ptr [ebp - 0x6e8], eax
0064548e mov ecx, edi
00645490 call 0x6414a0
00645495 cmp dword ptr [ebp - 0x6e8], 0
0064549c mov dword ptr [ebp - 0x678], eax
006454a2 mov dword ptr [ebp - 0x6a0], 0
006454ac jle 0x6456b1
006454b2 call 0x659200
006454b7 mulss xmm0, dword ptr [0xb6a9e8]
006454bf movss dword ptr [ebp - 0x7b0], xmm0
006454c7 call 0x6c3d90
006454cc push 0
006454ce push 0xbeaaec
006454d3 push 0xbeab18
006454d8 push 0
006454da push eax
006454db push 0
006454dd push 0
006454df push 0xc02fec
006454e4 lea eax, [ebp - 0x7b0]
006454ea push eax
006454eb lea eax, [ebp - 0x131c]
006454f1 push eax
006454f2 lea eax, [ebp - 0x1324]
006454f8 push eax
006454f9 call 0x659290
006454fe add esp, 4
00645501 mov ecx, eax
00645503 call 0x962b50
00645508 push eax
00645509 lea eax, [ebp - 0x132c]
0064550f push eax
00645510 lea ecx, [edi + 0x294]
00645516 call 0x962a60
0064551b mov ecx, dword ptr [0xbfd65c]
00645521 push eax
00645522 push 7
00645524 push 0x3e8
00645529 call 0x422e20
0064552e push eax
0064552f call 0x9ec34c
00645534 add esp, 0x14
00645537 mov dword ptr [ebp - 0x674], eax
0064553d lea eax, [ebp - 0x7b4]
00645543 mov dword ptr [ebp - 0x7b4], 0x3e99999a
0064554d mov ecx, 0xbc7a28
00645552 push eax
00645553 lea eax, [ebp - 0x1334]
00645559 push eax
0064555a call 0x962b50
0064555f mov ecx, dword ptr [ebp - 0x674]
00645565 push eax
00645566 call 0x427330
0064556b movss xmm0, dword ptr [ebp - 0x67c]
00645573 lea ecx, [ebp - 0x68]
00645576 movaps xmm3, xmm0
00645579 movaps xmm2, xmm0
0064557c movaps xmm1, xmm0
0064557f call 0x427080
00645584 push ecx
00645585 lea ecx, [ebp - 0x68]
00645588 mov dword ptr [esp], 0x3da3d70a
0064558f call 0x402230
00645594 cmp dword ptr [edi + 0x2c], 0x1b
00645598 jne 0x6455bc
0064559a push 0xff
0064559f push 0xff
006455a4 push 0xff
006455a9 push ecx
006455aa mov dword ptr [esp], 0x3f000000
006455b1 lea ecx, [ebp - 0x664]
006455b7 jmp 0x645650
006455bc mov eax, dword ptr [ebp - 0x678]
006455c2 test eax, eax
006455c4 je 0x64562c
006455c6 push 0
006455c8 push 0x136
006455cd mov ecx, eax
006455cf call 0x73af30
006455d4 test al, al
006455d6 je 0x6455fd
006455d8 call 0x659200
006455dd mulss xmm0, dword ptr [ebp - 0x6b8]
006455e5 push ecx
006455e6 lea ecx, [ebp - 0x68]
006455e9 addss xmm0, dword ptr [0xb6a350]
006455f1 movss dword ptr [esp], xmm0
006455f6 call 0x402230
006455fb jmp 0x64566f
006455fd mov ecx, dword ptr [ebp - 0x678]
00645603 push 0
00645605 push 6
00645607 call 0x73af30
0064560c test al, al
0064560e je 0x64562c
00645610 push 0
00645612 push 0x96
00645617 push 0x96
0064561c push ecx
0064561d mov dword ptr [esp], 0x3f000000
00645624 lea ecx, [ebp - 0x638]
0064562a jmp 0x645650
0064562c mov eax, dword ptr [edi + 0x2c]
0064562f cmp eax, 0x21
00645632 je 0x645639
00645634 cmp eax, 0x22
00645637 jne 0x64566f
00645639 push 0
0064563b push 0
0064563d push 0x96
00645642 push ecx
00645643 mov dword ptr [esp], 0x3dcccccd
0064564a lea ecx, [ebp - 0x60c]
00645650 movss xmm0, dword ptr [ebp - 0x67c]
00645658 movaps xmm3, xmm0
0064565b movaps xmm2, xmm0
0064565e movaps xmm1, xmm0
00645661 call 0x4270d0
00645666 push eax
00645667 lea ecx, [ebp - 0x68]
0064566a call 0x4021a0
0064566f mov ecx, dword ptr [ebp - 0x674]
00645675 lea edx, [ebp - 0x68]
00645678 push 1
0064567a push 0
0064567c push 0xff
00645681 mov eax, dword ptr [ecx]
00645683 push -1
00645685 push edx
00645686 mov eax, dword ptr [eax + 0x38]
00645689 call eax
0064568b mov ecx, dword ptr [ebp - 0x674]
00645691 mov eax, dword ptr [ecx]
00645693 mov eax, dword ptr [eax + 0xc]
00645696 call eax
00645698 mov eax, dword ptr [ebp - 0x6a0]
0064569e inc eax
0064569f mov dword ptr [ebp - 0x6a0], eax
006456a5 cmp eax, dword ptr [ebp - 0x6e8]
006456ab jl 0x6454b2
006456b1 cmp byte ptr [edi + 0x16b], 0
006456b8 je 0x6456e4
006456ba push 0xbc4b80
006456bf mov edx, esi
006456c1 lea ecx, [ebp - 0x14b4]
006456c7 call 0x412050
006456cc add esp, 4
006456cf mov ecx, eax
006456d1 call 0x412090
006456d6 mov eax, dword ptr [edi]
006456d8 mov ecx, edi
006456da mov eax, dword ptr [eax + 0x28]
006456dd call eax
006456df jmp 0x64db64
006456e4 push 0xbc49d0
006456e9 mov edx, esi
006456eb lea ecx, [ebp - 0x14c4]
006456f1 call 0x412050
006456f6 add esp, 4
006456f9 mov ecx, eax
006456fb call 0x412090
00645700 test al, al
00645702 je 0x645892
00645708 mov ecx, edi
0064570a call 0x682200
0064570f cmp eax, 2
00645712 jle 0x645892
00645718 mov eax, dword ptr [ebp - 0x698]
0064571e test eax, eax
00645720 je 0x64572d
00645722 push 0x1e
00645724 mov ecx, eax
00645726 call 0x7866b0
0064572b jmp 0x645735
0064572d movss xmm0, dword ptr [ebp - 0x684]
00645735 mulss xmm0, dword ptr [ebp - 0x68c]
0064573d mov ecx, edi
0064573f addss xmm0, dword ptr [ebp - 0x68c]
00645747 movss dword ptr [ebp - 0x6d8], xmm0
0064574f call 0x682200
00645754 mov ecx, edi
00645756 cmp eax, 4
00645759 jle 0x64583f
0064575f call 0x682200
00645764 sub eax, 5
00645767 mov ecx, 0x16
0064576c cdq 
0064576d idiv ecx
0064576f cmp edx, 0x13
00645772 ja 0x645892
00645778 movzx eax, byte ptr [edx + 0x64dc68]
0064577f jmp dword ptr [eax*4 + 0x64dc54]
00645786 movss xmm1, dword ptr [edi + 0x2bc]
0064578e lea eax, [ebp - 0x6d8]
00645794 xorps xmm1, xmmword ptr [0xb6c9b0]
0064579b lea ecx, [ebp - 0x1344]
006457a1 movss xmm2, dword ptr [edi + 0x2b8]
006457a9 push eax
006457aa lea eax, [ebp - 0x133c]
006457b0 push eax
006457b1 call 0x9624e0
006457b6 mov ecx, eax
006457b8 call 0x962c10
006457bd jmp 0x645880
006457c2 movss xmm1, dword ptr [edi + 0x2bc]
006457ca lea eax, [ebp - 0x6d8]
006457d0 xorps xmm1, xmmword ptr [0xb6c9b0]
006457d7 lea ecx, [ebp - 0x1354]
006457dd movss xmm2, dword ptr [edi + 0x2b8]
006457e5 push eax
006457e6 lea eax, [ebp - 0x134c]
006457ec jmp 0x645873
006457f1 movss xmm2, dword ptr [edi + 0x2b8]
006457f9 lea eax, [ebp - 0x6d8]
006457ff xorps xmm2, xmmword ptr [0xb6c9b0]
00645806 lea ecx, [ebp - 0x1364]
0064580c movss xmm1, dword ptr [edi + 0x2bc]
00645814 push eax
00645815 lea eax, [ebp - 0x135c]
0064581b push eax
0064581c call 0x9624e0
00645821 mov ecx, eax
00645823 call 0x962c10
00645828 jmp 0x645880
0064582a lea eax, [ebp - 0x6d8]
00645830 push eax
00645831 lea eax, [ebp - 0x136c]
00645837 lea ecx, [ebp - 0x1374]
0064583d jmp 0x64585c
0064583f call 0x682200
00645844 cmp eax, 3
00645847 jne 0x645892
00645849 lea eax, [ebp - 0x6d8]
0064584f push eax
00645850 lea eax, [ebp - 0x137c]
00645856 lea ecx, [ebp - 0x1384]
0064585c movss xmm2, dword ptr [edi + 0x2b8]
00645864 movss xmm1, dword ptr [edi + 0x2bc]
0064586c xorps xmm2, xmmword ptr [0xb6c9b0]
00645873 push eax
00645874 call 0x9624e0
00645879 mov ecx, eax
0064587b call 0x962b50
00645880 push eax
00645881 lea ecx, [edi + 0x2b8]
00645887 call 0x962cd0
0064588c lea esi, [edi + 0x378]
00645892 push 0xbc47f0
00645897 mov edx, 0xbc4bf0
0064589c lea ecx, [ebp - 0x14d4]
006458a2 call 0x427220
006458a7 push eax
006458a8 mov edx, esi
006458aa lea ecx, [ebp - 0x14e4]
006458b0 call 0x412050
006458b5 add esp, 8
006458b8 mov ecx, eax
006458ba call 0x412090
006458bf test al, al
006458c1 je 0x645f3a
006458c7 cmp dword ptr [edi + 0x31c], 0
006458ce jne 0x645f3a
006458d4 mov eax, dword ptr [edi + 0x320]
006458da mov dword ptr [ebp - 0x66c], eax
006458e0 test eax, eax
006458e2 jne 0x6458f0
006458e4 mov eax, dword ptr [edi + 0x314]
006458ea mov dword ptr [ebp - 0x66c], eax
006458f0 push 0xbc4ce0
006458f5 mov edx, esi
006458f7 lea ecx, [ebp - 0x14f4]
006458fd call 0x412050
00645902 add esp, 4
00645905 mov ecx, eax
00645907 call 0x412090
0064590c test al, al
0064590e je 0x645a7e
00645914 mov ecx, edi
00645916 call 0x6520e0
0064591b test al, al
0064591d je 0x645f3a
00645923 mov eax, dword ptr [ebp - 0x66c]
00645929 test eax, eax
0064592b je 0x645f3a
00645931 lea ecx, [ebp - 0x138c]
00645937 push ecx
00645938 mov ecx, eax
0064593a call 0x412130
0064593f push eax
00645940 lea eax, [ebp - 0xa7c]
00645946 lea esi, [edi + 0x294]
0064594c push eax
0064594d mov ecx, esi
0064594f call 0x962ac0
00645954 lea ecx, [ebp - 0xa7c]
0064595a call 0x962a00
0064595f fstp dword ptr [ebp - 0x6ec]
00645965 movss xmm0, dword ptr [ebp - 0x6ec]
0064596d ucomiss xmm0, dword ptr [ebp - 0x67c]
00645974 lahf 
00645975 test ah, 0x44
00645978 jp 0x645984
0064597a mov dword ptr [ebp - 0x6ec], 0x3dcccccd
00645984 lea eax, [ebp - 0x6ec]
0064598a push eax
0064598b lea eax, [ebp - 0x930]
00645991 push eax
00645992 lea ecx, [ebp - 0xa7c]
00645998 call 0x962c10
0064599d movss xmm0, dword ptr [0xb6aafc]
006459a5 lea ecx, [ebp - 0x938]
006459ab subss xmm0, dword ptr [ebp - 0x6ec]
006459b3 movss xmm2, dword ptr [ebp - 0x930]
006459bb xorps xmm2, xmmword ptr [0xb6c9b0]
006459c2 movss xmm1, dword ptr [ebp - 0x92c]
006459ca mulss xmm0, dword ptr [0xb6a214]
006459d2 movss dword ptr [ebp - 0x7bc], xmm0
006459da call 0x9624e0
006459df lea eax, [edi + 0x2b8]
006459e5 push eax
006459e6 lea ecx, [ebp - 0x938]
006459ec call 0x962600
006459f1 movss xmm0, dword ptr [ebp - 0x67c]
006459f9 fstp dword ptr [ebp - 0x668]
006459ff comiss xmm0, dword ptr [ebp - 0x668]
00645a06 jbe 0x645a24
00645a08 lea eax, [ebp - 0x7b8]
00645a0e mov dword ptr [ebp - 0x7b8], 0xbf800000
00645a18 push eax
00645a19 lea ecx, [ebp - 0x938]
00645a1f call 0x962bb0
00645a24 push 0
00645a26 lea eax, [ebp - 0x7bc]
00645a2c mov dword ptr [ebp - 0x7c0], 0x3f800000
00645a36 push eax
00645a37 lea eax, [ebp - 0x1394]
00645a3d push eax
00645a3e lea ecx, [ebp - 0x930]
00645a44 call 0x962b50
00645a49 push eax
00645a4a lea eax, [ebp - 0x139c]
00645a50 push eax
00645a51 lea eax, [ebp - 0x7c0]
00645a57 push eax
00645a58 lea eax, [ebp - 0x13a4]
00645a5e push eax
00645a5f lea ecx, [ebp - 0x938]
00645a65 call 0x962b50
00645a6a mov ecx, eax
00645a6c call 0x962a60
00645a71 push eax
00645a72 mov ecx, edi
00645a74 call 0x422b60
00645a79 jmp 0x645f40
00645a7e cmp dword ptr [ebp - 0x66c], 0
00645a85 jne 0x645a9f
00645a87 push 0xc02fec
00645a8c lea ecx, [edi + 0x28c]
00645a92 call 0x962ca0
00645a97 test al, al
00645a99 je 0x645f3a
00645a9f push 0xbc46a0
00645aa4 mov edx, esi
00645aa6 lea ecx, [ebp - 0x1504]
00645aac call 0x412050
00645ab1 add esp, 4
00645ab4 mov ecx, eax
00645ab6 call 0x427260
00645abb test al, al
00645abd je 0x645f3a
00645ac3 push 0xbc47f0
00645ac8 mov edx, esi
00645aca lea ecx, [ebp - 0x1514]
00645ad0 call 0x412050
00645ad5 add esp, 4
00645ad8 mov ecx, eax
00645ada call 0x412090
00645adf test al, al
00645ae1 jne 0x645fbf
00645ae7 cmp dword ptr [edi + 0x388], 1
00645aee jg 0x645fbf
00645af4 test byte ptr [edi + 0x3a0], 1
00645afb jne 0x645b07
00645afd movss xmm0, dword ptr [ebp - 0x684]
00645b05 jmp 0x645b0f
00645b07 movss xmm0, dword ptr [0xb6ae44]
00645b0f lea ecx, [ebp - 0x750]
00645b15 movss dword ptr [ebp - 0x678], xmm0
00645b1d call 0x9624d0
00645b22 lea ecx, [ebp - 0x940]
00645b28 call 0x9624d0
00645b2d lea ecx, [edi + 0x28c]
00645b33 push 0xc02fec
00645b38 call 0x962c70
00645b3d test al, al
00645b3f je 0x645ba3
00645b41 mov ecx, dword ptr [ebp - 0x66c]
00645b47 lea eax, [ebp - 0x13ac]
00645b4d push eax
00645b4e call 0x412150
00645b53 push eax
00645b54 lea eax, [ebp - 0x13b4]
00645b5a push eax
00645b5b lea eax, [edi + 0x2b8]
00645b61 push eax
00645b62 lea eax, [ebp - 0xbd4]
00645b68 push eax
00645b69 lea ecx, [edi + 0x294]
00645b6f call 0x962a60
00645b74 mov ecx, eax
00645b76 call 0x962ac0
00645b7b push eax
00645b7c lea ecx, [ebp - 0x750]
00645b82 call 0x962cd0
00645b87 mov ecx, dword ptr [ebp - 0x66c]
00645b8d lea eax, [ebp - 0xbdc]
00645b93 push eax
00645b94 call 0x412170
00645b99 mov ecx, eax
00645b9b lea eax, [ebp - 0x940]
00645ba1 jmp 0x645be8
00645ba3 lea eax, [edi + 0x28c]
00645ba9 push eax
00645baa lea eax, [ebp - 0xbe4]
00645bb0 push eax
00645bb1 lea eax, [edi + 0x2b8]
00645bb7 push eax
00645bb8 lea eax, [ebp - 0xbec]
00645bbe push eax
00645bbf lea ecx, [edi + 0x294]
00645bc5 call 0x962a60
00645bca mov ecx, eax
00645bcc call 0x962ac0
00645bd1 push eax
00645bd2 lea ecx, [ebp - 0x750]
00645bd8 call 0x962cd0
00645bdd lea eax, [edi + 0x760]
00645be3 mov ecx, 0xc02fec
00645be8 push ecx
00645be9 mov ecx, eax
00645beb call 0x962cd0
00645bf0 push 0xc02fec
00645bf5 lea ecx, [edi + 0x28c]
00645bfb call 0x962c70
00645c00 test al, al
00645c02 je 0x645c49
00645c04 mov ecx, dword ptr [ebp - 0x66c]
00645c0a call 0x412240
00645c0f test al, al
00645c11 je 0x645c49
00645c13 mov ecx, dword ptr [ebp - 0x66c]
00645c19 mov dword ptr [ebp - 0x7c4], 0x42700000
00645c23 call 0x422d90
00645c28 push eax
00645c29 lea edx, [ebp - 0x7c4]
00645c2f lea ecx, [ebp - 0xbf4]
00645c35 call 0x4120b0
00645c3a add esp, 4
00645c3d lea ecx, [ebp - 0x750]
00645c43 push eax
00645c44 call 0x962af0
00645c49 lea ecx, [ebp - 0x750]
00645c4f call 0x962a00
00645c54 fstp dword ptr [ebp - 0x6f0]
00645c5a movss xmm0, dword ptr [ebp - 0x6f0]
00645c62 ucomiss xmm0, dword ptr [ebp - 0x67c]
00645c69 lahf 
00645c6a test ah, 0x44
00645c6d jnp 0x645f3a
00645c73 lea eax, [ebp - 0x6f0]
00645c79 push eax
00645c7a lea eax, [ebp - 0xa24]
00645c80 push eax
00645c81 lea ecx, [ebp - 0x750]
00645c87 call 0x962c10
00645c8c lea eax, [edi + 0x760]
00645c92 push eax
00645c93 lea ecx, [edi + 0x2b8]
00645c99 call 0x962af0
00645c9e movss xmm0, dword ptr [0xb6ab20]
00645ca6 lea ecx, [ebp - 0x1524]
00645cac push 0xbc4920
00645cb1 mov edx, esi
00645cb3 movss dword ptr [ebp - 0x6a0], xmm0
00645cbb mov dword ptr [ebp - 0x6f4], 0x3dcccccd
00645cc5 call 0x412050
00645cca add esp, 4
00645ccd mov ecx, eax
00645ccf call 0x412090
00645cd4 test al, al
00645cd6 je 0x645d8d
00645cdc movss xmm3, dword ptr [0xb6a274]
00645ce4 movss xmm2, dword ptr [0xb6aef4]
00645cec movss xmm1, dword ptr [0xb6ae98]
00645cf4 movss xmm0, dword ptr [edi + 0x360]
00645cfc push ecx
00645cfd mov cl, 1
00645cff mov dword ptr [esp], 0x3fc00000
00645d06 call 0x962420
00645d0b push 0xbc4ca0
00645d10 mov edx, esi
00645d12 movss dword ptr [ebp - 0x708], xmm0
00645d1a lea ecx, [ebp - 0x1534]
00645d20 call 0x412050
00645d25 add esp, 8
00645d28 mov ecx, eax
00645d2a call 0x412090
00645d2f test al, al
00645d31 je 0x645d5c
00645d33 lea edx, [ebp - 0x7c8]
00645d39 mov dword ptr [ebp - 0x7c8], 0x3ecccccd
00645d43 lea ecx, [ebp - 0x708]
00645d49 call 0x417c70
00645d4e movss xmm2, dword ptr [eax]
00645d52 movss dword ptr [ebp - 0x708], xmm2
00645d5a jmp 0x645d64
00645d5c movss xmm2, dword ptr [ebp - 0x708]
00645d64 movss xmm1, dword ptr [0xb6a820]
00645d6c movaps xmm0, xmm2
00645d6f mulss xmm0, dword ptr [0xb6ab20]
00645d77 subss xmm1, xmm2
00645d7b movss dword ptr [ebp - 0x6a0], xmm0
00645d83 mulss xmm1, dword ptr [ebp - 0x6f4]
00645d8b jmp 0x645d9d
00645d8d movss xmm1, dword ptr [ebp - 0x6f4]
00645d95 movss xmm0, dword ptr [0xb6ab20]
00645d9d subss xmm0, dword ptr [ebp - 0x6f0]
00645da5 lea ecx, [ebp - 0xa24]
00645dab mulss xmm0, xmm1
00645daf movss dword ptr [ebp - 0x6f4], xmm0
00645db7 call 0x962830
00645dbc movss xmm0, dword ptr [ebp - 0x678]
00645dc4 mulss xmm0, dword ptr [0xb6aae4]
00645dcc movss xmm2, dword ptr [ebp - 0x6f0]
00645dd4 movss xmm1, dword ptr [ebp - 0x6a0]
00645ddc movss dword ptr [ebp - 0x668], xmm0
00645de4 fadd dword ptr [ebp - 0x668]
00645dea movss xmm0, dword ptr [ebp - 0x67c]
00645df2 fstp dword ptr [ebp - 0x674]
00645df8 call 0x962390
00645dfd movss xmm1, dword ptr [ebp - 0x684]
00645e05 movaps xmm2, xmm0
00645e08 movss xmm0, dword ptr [ebp - 0x67c]
00645e10 call 0x9623e0
00645e15 movss xmm1, dword ptr [0xb6a7b0]
00645e1d call 0x4c3f60
00645e22 lea ecx, [edi + 0x2b8]
00645e28 movss dword ptr [ebp - 0x678], xmm0
00645e30 call 0x962830
00645e35 fsubr dword ptr [ebp - 0x674]
00645e3b fstp dword ptr [ebp - 0x668]
00645e41 movss xmm0, dword ptr [ebp - 0x668]
00645e49 call 0x65a640
00645e4e mulss xmm0, dword ptr [ebp - 0x678]
00645e56 lea ecx, [edi + 0x2b8]
00645e5c movss dword ptr [ebp - 0x668], xmm0
00645e64 call 0x962830
00645e69 fadd dword ptr [ebp - 0x668]
00645e6f push ecx
00645e70 lea eax, [ebp - 0xb5c]
00645e76 fstp dword ptr [ebp - 0x674]
00645e7c movss xmm0, dword ptr [ebp - 0x674]
00645e84 movss dword ptr [esp], xmm0
00645e89 push eax
00645e8a call 0x9627f0
00645e8f add esp, 8
00645e92 lea ecx, [edi + 0x2b8]
00645e98 call 0x962a00
00645e9d lea eax, [ebp - 0x940]
00645ea3 push eax
00645ea4 lea eax, [ebp - 0xbfc]
00645eaa push eax
00645eab lea eax, [ebp - 0x73c]
00645eb1 push eax
00645eb2 lea eax, [ebp - 0xc04]
00645eb8 push eax
00645eb9 lea eax, [ebp - 0xc0c]
00645ebf push eax
00645ec0 lea eax, [ebp - 0x6f4]
00645ec6 push eax
00645ec7 lea eax, [ebp - 0xc14]
00645ecd push eax
00645ece lea ecx, [ebp - 0xa24]
00645ed4 fstp dword ptr [ebp - 0x73c]
00645eda call 0x962b50
00645edf push eax
00645ee0 lea eax, [ebp - 0xc1c]
00645ee6 push eax
00645ee7 lea eax, [ebp - 0x73c]
00645eed push eax
00645eee lea eax, [ebp - 0xc24]
00645ef4 push eax
00645ef5 lea ecx, [ebp - 0xb5c]
00645efb call 0x962b50
00645f00 mov ecx, eax
00645f02 call 0x962a60
00645f07 mov ecx, eax
00645f09 call 0x962560
00645f0e mov ecx, eax
00645f10 call 0x962b50
00645f15 mov ecx, eax
00645f17 call 0x962a60
00645f1c push eax
00645f1d lea ecx, [edi + 0x2b8]
00645f23 call 0x962cd0
00645f28 lea eax, [ebp - 0x940]
00645f2e push eax
00645f2f lea ecx, [edi + 0x760]
00645f35 call 0x962cd0
00645f3a lea esi, [edi + 0x294]
00645f40 push 0xbc48a0
00645f45 lea edx, [edi + 0x378]
00645f4b lea ecx, [ebp - 0x1544]
00645f51 call 0x412050
00645f56 add esp, 4
00645f59 mov ecx, eax
00645f5b call 0x412090
00645f60 test al, al
00645f62 je 0x647da7
00645f68 mov ecx, edi
00645f6a call 0x6414a0
00645f6f mov dword ptr [ebp - 0x694], eax
00645f75 lea eax, [edi + 0x3c]
00645f78 mov ecx, eax
00645f7a mov dword ptr [ebp - 0x674], eax
00645f80 call 0x405930
00645f85 mulss xmm0, dword ptr [0xb6ac40]
00645f8d mov eax, dword ptr [ebp - 0x694]
00645f93 divss xmm0, dword ptr [ebp - 0x6e0]
00645f9b addss xmm0, dword ptr [0xb6aae4]
00645fa3 movss dword ptr [ebp - 0x69c], xmm0
00645fab test eax, eax
00645fad je 0x6463d3
00645fb3 mov ecx, eax
00645fb5 call 0x6415d0
00645fba jmp 0x6463db
00645fbf lea ecx, [ebp - 0x778]
00645fc5 call 0x9624d0
00645fca lea ecx, [ebp - 0xa2c]
00645fd0 call 0x9624d0
00645fd5 lea esi, [edi + 0x28c]
00645fdb push 0xc02fec
00645fe0 mov ecx, esi
00645fe2 call 0x962c70
00645fe7 test al, al
00645fe9 je 0x64603f
00645feb mov esi, dword ptr [ebp - 0x66c]
00645ff1 lea eax, [ebp - 0xc2c]
00645ff7 push eax
00645ff8 mov ecx, esi
00645ffa call 0x412130
00645fff push eax
00646000 lea ecx, [ebp - 0x778]
00646006 call 0x962cd0
0064600b mov ecx, esi
0064600d call 0x427320
00646012 lea eax, [ebp - 0x7cc]
00646018 movss dword ptr [ebp - 0x7cc], xmm0
00646020 push eax
00646021 lea eax, [ebp - 0xc34]
00646027 mov ecx, esi
00646029 push eax
0064602a lea eax, [ebp - 0xc3c]
00646030 push eax
00646031 call 0x412170
00646036 mov ecx, eax
00646038 call 0x962c10
0064603d jmp 0x646050
0064603f push esi
00646040 lea ecx, [ebp - 0x778]
00646046 call 0x962cd0
0064604b mov eax, 0xc02fec
00646050 push eax
00646051 lea ecx, [ebp - 0xa2c]
00646057 call 0x962cd0
0064605c movss xmm0, dword ptr [edi + 0x76c]
00646064 lea esi, [edi + 0x294]
0064606a ucomiss xmm0, dword ptr [ebp - 0x67c]
00646071 lahf 
00646072 test ah, 0x44
00646075 jp 0x6461b7
0064607b lea eax, [ebp - 0x778]
00646081 mov ecx, esi
00646083 push eax
00646084 lea eax, [ebp - 0x948]
0064608a push eax
0064608b call 0x962ac0
00646090 mov eax, dword ptr [edi + 0x2b8]
00646096 mov ecx, dword ptr [edi + 0x2bc]
0064609c mov dword ptr [ebp - 0x720], eax
006460a2 mov dword ptr [ebp - 0x71c], ecx
006460a8 cmp dword ptr [edi + 0x388], 1
006460af jle 0x6460c3
006460b1 lea eax, [edi + 0x38c]
006460b7 push eax
006460b8 lea ecx, [ebp - 0x720]
006460be call 0x962cd0
006460c3 lea eax, [ebp - 0xc44]
006460c9 push eax
006460ca lea ecx, [ebp - 0x720]
006460d0 call 0x962560
006460d5 push eax
006460d6 lea eax, [ebp - 0xc4c]
006460dc push eax
006460dd lea ecx, [ebp - 0x948]
006460e3 call 0x962560
006460e8 mov ecx, eax
006460ea call 0x962600
006460ef fstp dword ptr [ebp - 0x668]
006460f5 movss xmm0, dword ptr [ebp - 0x668]
006460fd comiss xmm0, dword ptr [0xb6a560]
00646104 jb 0x64613c
00646106 test byte ptr [edi + 0x3a0], 1
0064610d mov dword ptr [ebp - 0x678], 0x3f800000
00646117 jne 0x646123
00646119 mov dword ptr [ebp - 0x678], 0xbf800000
00646123 lea ecx, [ebp - 0x720]
00646129 call 0x962a00
0064612e fmul dword ptr [ebp - 0x678]
00646134 lea ecx, [ebp - 0x720]
0064613a jmp 0x6461a6
0064613c lea eax, [ebp - 0x720]
00646142 push eax
00646143 push ecx
00646144 lea eax, [ebp - 0xc54]
0064614a mov dword ptr [esp], 0x42b40000
00646151 push eax
00646152 lea ecx, [ebp - 0x948]
00646158 call 0x962780
0064615d mov ecx, eax
0064615f call 0x962600
00646164 movss xmm0, dword ptr [ebp - 0x67c]
0064616c fstp dword ptr [ebp - 0x668]
00646172 comiss xmm0, dword ptr [ebp - 0x668]
00646179 mov dword ptr [ebp - 0x678], 0xbf800000
00646183 ja 0x64618f
00646185 mov dword ptr [ebp - 0x678], 0x3f800000
0064618f lea ecx, [ebp - 0x720]
00646195 call 0x962a00
0064619a fmul dword ptr [ebp - 0x678]
006461a0 lea ecx, [ebp - 0x948]
006461a6 fstp dword ptr [edi + 0x76c]
006461ac call 0x962830
006461b1 fstp dword ptr [edi + 0x768]
006461b7 mov dword ptr [ebp - 0x70c], 0x42b40000
006461c1 cmp dword ptr [edi + 0x388], 0
006461c8 jle 0x6461d4
006461ca mov dword ptr [ebp - 0x70c], 0x41f00000
006461d4 movss xmm0, dword ptr [edi + 0x768]
006461dc lea eax, [ebp - 0x70c]
006461e2 push eax
006461e3 lea eax, [ebp - 0xc5c]
006461e9 push eax
006461ea push ecx
006461eb lea eax, [ebp - 0xc64]
006461f1 movss dword ptr [esp], xmm0
006461f6 push eax
006461f7 call 0x9627f0
006461fc add esp, 8
006461ff mov ecx, eax
00646201 call 0x962b50
00646206 push eax
00646207 lea eax, [ebp - 0xb7c]
0064620d push eax
0064620e lea ecx, [ebp - 0x778]
00646214 call 0x962a60
00646219 mov dword ptr [ebp - 0x7d0], 0x40a00000
00646223 movss xmm0, dword ptr [edi + 0x76c]
0064622b call 0x412000
00646230 lea edx, [ebp - 0x7d0]
00646236 movss dword ptr [ebp - 0x7d4], xmm0
0064623e lea ecx, [ebp - 0x7d4]
00646244 call 0x417c70
00646249 lea edx, [ebp - 0x7d8]
0064624f lea ecx, [ebp - 0xa34]
00646255 movss xmm0, dword ptr [eax]
00646259 lea eax, [ebp - 0xa2c]
0064625f push eax
00646260 movss dword ptr [ebp - 0x678], xmm0
00646268 mov dword ptr [ebp - 0x7d8], 0x40000000
00646272 call 0x4120b0
00646277 add esp, 4
0064627a mov dword ptr [ebp - 0x7dc], 0x3f000000
00646284 lea eax, [ebp - 0xa34]
0064628a mov ecx, esi
0064628c push eax
0064628d lea eax, [ebp - 0xc6c]
00646293 push eax
00646294 call 0x962a60
00646299 push eax
0064629a lea eax, [ebp - 0xc74]
006462a0 push eax
006462a1 lea ecx, [ebp - 0xb7c]
006462a7 call 0x962ac0
006462ac push eax
006462ad lea edx, [ebp - 0x7dc]
006462b3 lea ecx, [ebp - 0x950]
006462b9 call 0x4120b0
006462be add esp, 4
006462c1 lea ecx, [ebp - 0x950]
006462c7 call 0x962a00
006462cc movss xmm1, dword ptr [ebp - 0x678]
006462d4 fstp dword ptr [ebp - 0x668]
006462da movss xmm0, dword ptr [ebp - 0x668]
006462e2 comiss xmm0, xmm1
006462e5 jbe 0x6462f8
006462e7 push ecx
006462e8 lea ecx, [ebp - 0x950]
006462ee movss dword ptr [esp], xmm1
006462f3 call 0x962860
006462f8 lea eax, [edi + 0x2c4]
006462fe push eax
006462ff lea eax, [ebp - 0xc7c]
00646305 push eax
00646306 lea eax, [ebp - 0x950]
0064630c push eax
0064630d lea eax, [ebp - 0xc84]
00646313 push eax
00646314 lea ecx, [ebp - 0xa34]
0064631a call 0x962a60
0064631f mov ecx, eax
00646321 call 0x962c10
00646326 push eax
00646327 lea ecx, [edi + 0x2b8]
0064632d call 0x962cd0
00646332 movss xmm0, dword ptr [edi + 0x76c]
0064633a lea ecx, [edi + 0x2f4]
00646340 divss xmm0, dword ptr [ebp - 0x70c]
00646348 mulss xmm0, dword ptr [0xb6ab88]
00646350 divss xmm0, dword ptr [0xb6a874]
00646358 mulss xmm0, dword ptr [ecx]
0064635c addss xmm0, dword ptr [edi + 0x768]
00646364 call 0x65a640
00646369 movss dword ptr [edi + 0x768], xmm0
00646371 cmp dword ptr [edi + 0x388], 1
00646378 jle 0x645f40
0064637e movss xmm0, dword ptr [edi + 0x76c]
00646386 call 0x412000
0064638b movss dword ptr [ebp - 0x7e0], xmm0
00646393 lea eax, [ebp - 0xc8c]
00646399 movss xmm0, dword ptr [edi + 0x768]
006463a1 push ecx
006463a2 movss dword ptr [esp], xmm0
006463a7 push eax
006463a8 call 0x9627f0
006463ad push eax
006463ae lea edx, [ebp - 0x7e0]
006463b4 lea ecx, [ebp - 0xc94]
006463ba call 0x4120b0
006463bf add esp, 0xc
006463c2 lea ecx, [edi + 0x38c]
006463c8 push eax
006463c9 call 0x962cd0
006463ce jmp 0x645f40
006463d3 movss xmm0, dword ptr [ebp - 0x67c]
006463db push 0xbc4710
006463e0 lea edx, [edi + 0x378]
006463e6 movss dword ptr [ebp - 0x6a0], xmm0
006463ee lea ecx, [ebp - 0x1554]
006463f4 mov byte ptr [ebp - 0x68d], 0
006463fb call 0x412050
00646400 add esp, 4
00646403 mov ecx, eax
00646405 call 0x412090
0064640a test al, al
0064640c je 0x646663
00646412 lea ecx, [edi + 0x3f4]
00646418 call 0x4076f0
0064641d test eax, eax
0064641f jne 0x6465f2
00646425 cmp byte ptr [edi + 0x16b], al
0064642b jne 0x6465f2
00646431 call 0x6c3d90
00646436 mov ecx, dword ptr [0xbfd65c]
0064643c push 1
0064643e push eax
0064643f push 3
00646441 push dword ptr [ebp - 0x694]
00646447 push 0xc02fec
0064644c push esi
0064644d push 2
0064644f push 7
00646451 call 0x6d0ca0
00646456 mov dword ptr [ebp - 0x66c], eax
0064645c test eax, eax
0064645e je 0x6465d5
00646464 mov ecx, dword ptr [ebp - 0x694]
0064646a test ecx, ecx
0064646c je 0x646499
0064646e mov esi, dword ptr [eax]
00646470 lea eax, [ebp - 0x4d8]
00646476 push 1
00646478 push 0
0064647a push 0xff
0064647f push -1
00646481 push eax
00646482 call 0x6415f0
00646487 mov ecx, dword ptr [ebp - 0x66c]
0064648d push eax
0064648e mov eax, dword ptr [esi + 0x38]
00646491 call eax
00646493 lea esi, [edi + 0x294]
00646499 mov ecx, dword ptr [ebp - 0x66c]
0064649f lea eax, [edi + 0x2a4]
006464a5 push eax
006464a6 call 0x412190
006464ab mov ecx, dword ptr [ebp - 0x66c]
006464b1 push edi
006464b2 call 0x6818e0
006464b7 push ecx
006464b8 mov ecx, dword ptr [ebp - 0x66c]
006464be mov dword ptr [esp], 0x453b8000
006464c5 call 0x4273d0
006464ca lea eax, [ebp - 0x1564]
006464d0 mov edx, 0xbc4bc0
006464d5 push eax
006464d6 push 0xbc48a0
006464db push 0xbc4c60
006464e0 lea ecx, [ebp - 0x1574]
006464e6 call 0x427220
006464eb add esp, 4
006464ee lea ecx, [ebp - 0x1584]
006464f4 mov edx, eax
006464f6 call 0x427220
006464fb add esp, 4
006464fe mov ecx, eax
00646500 call 0x57f3a0
00646505 push eax
00646506 lea edx, [edi + 0x378]
0064650c lea ecx, [ebp - 0x1594]
00646512 call 0x412050
00646517 sub esp, 0xc
0064651a mov ecx, esp
0064651c movups xmm0, xmmword ptr [eax]
0064651f movups xmmword ptr [ecx], xmm0
00646522 mov ecx, dword ptr [ebp - 0x66c]
00646528 call 0x427580
0064652d mov ecx, dword ptr [ebp - 0x66c]
00646533 movss xmm0, dword ptr [edi + 0x2e0]
0064653b mulss xmm0, dword ptr [ebp - 0x68c]
00646543 push ecx
00646544 mov eax, dword ptr [ecx]
00646546 movss dword ptr [esp], xmm0
0064654b mov eax, dword ptr [eax + 0x3c]
0064654e call eax
00646550 mov ecx, dword ptr [ebp - 0x66c]
00646556 push 0x12c
0064655b call 0x4275a0
00646560 movss xmm1, dword ptr [edi + 0x370]
00646568 mulss xmm1, dword ptr [ebp - 0x6bc]
00646570 mov ecx, dword ptr [ebp - 0x66c]
00646576 call 0x8d7ff0
0064657b movss xmm0, dword ptr [edi + 0x370]
00646583 mulss xmm0, dword ptr [0xb6a9ec]
0064658b push ecx
0064658c mov ecx, dword ptr [ebp - 0x66c]
00646592 addss xmm0, dword ptr [0xb6a9a0]
0064659a movss dword ptr [esp], xmm0
0064659f call 0x5ef2f0
006465a4 push dword ptr [ebp - 0x694]
006465aa mov ecx, dword ptr [ebp - 0x66c]
006465b0 call 0x6819a0
006465b5 mov ecx, dword ptr [ebp - 0x66c]
006465bb mov eax, dword ptr [ecx]
006465bd mov eax, dword ptr [eax + 0xc]
006465c0 call eax
006465c2 push dword ptr [ebp - 0x66c]
006465c8 lea ecx, [edi + 0x3f4]
006465ce call 0x4bc380
006465d3 jmp 0x6465f2
006465d5 lea eax, [ebp - 0x15a4]
006465db mov ecx, 0xbc4710
006465e0 push eax
006465e1 call 0x57f3a0
006465e6 push eax
006465e7 lea ecx, [edi + 0x378]
006465ed call 0x6413c0
006465f2 lea ecx, [edi + 0x3f4]
006465f8 call 0x4076f0
006465fd test eax, eax
006465ff je 0x646663
00646601 movss xmm0, dword ptr [edi + 0x370]
00646609 lea ecx, [edi + 0x3f4]
0064660f mulss xmm0, dword ptr [ebp - 0x6bc]
00646617 movss dword ptr [ebp - 0x668], xmm0
0064661f call 0x4076f0
00646624 movss xmm1, dword ptr [ebp - 0x668]
0064662c mov ecx, eax
0064662e call 0x8d7ff0
00646633 movss xmm0, dword ptr [edi + 0x370]
0064663b mulss xmm0, dword ptr [0xb6aa60]
00646643 push ecx
00646644 lea ecx, [edi + 0x3f4]
0064664a addss xmm0, dword ptr [0xb6a910]
00646652 movss dword ptr [esp], xmm0
00646657 call 0x4076f0
0064665c mov ecx, eax
0064665e call 0x5ef2f0
00646663 push 0xbc46d0
00646668 lea edx, [edi + 0x378]
0064666e lea ecx, [ebp - 0x15b4]
00646674 call 0x412050
00646679 add esp, 4
0064667c mov ecx, eax
0064667e call 0x412090
00646683 test al, al
00646685 je 0x646bea
0064668b lea esi, [edi + 0x3ec]
00646691 mov ecx, esi
00646693 mov dword ptr [ebp - 0x668], esi
00646699 call 0x4076f0
0064669e test eax, eax
006466a0 jne 0x646826
006466a6 cmp byte ptr [edi + 0x16b], al
006466ac jne 0x646826
006466b2 mov edx, dword ptr [ebp - 0x6e4]
006466b8 lea ecx, [ebp - 0x15c4]
006466be push 0xbc4850
006466c3 lea esi, [eax + 0xa]
006466c6 call 0x412050
006466cb add esp, 4
006466ce mov ecx, eax
006466d0 call 0x412090
006466d5 test al, al
006466d7 mov ecx, 0xb
006466dc cmovne esi, ecx
006466df call 0x6c3d90
006466e4 mov ecx, dword ptr [0xbfd65c]
006466ea push eax
006466eb push 0
006466ed push dword ptr [ebp - 0x694]
006466f3 push 0xc02fec
006466f8 push dword ptr [ebp - 0x6d0]
006466fe push esi
006466ff push 8
00646701 call 0x422e20
00646706 mov edi, eax
00646708 mov eax, dword ptr [ebp - 0x6a8]
0064670e push eax
0064670f mov ecx, edi
00646711 call 0x6818e0
00646716 mov ecx, dword ptr [ebp - 0x674]
0064671c mov esi, dword ptr [edi]
0064671e push 1
00646720 push 0
00646722 push 0xff
00646727 push -1
00646729 call 0x4023b0
0064672e push eax
0064672f mov eax, dword ptr [esi + 0x38]
00646732 mov ecx, edi
00646734 call eax
00646736 lea eax, [ebp - 0x1bb4]
0064673c mov edx, 0xbc4bc0
00646741 push eax
00646742 push 0xbc4c60
00646747 lea ecx, [ebp - 0x15e4]
0064674d call 0x427220
00646752 add esp, 4
00646755 mov ecx, eax
00646757 call 0x57f3a0
0064675c mov edx, dword ptr [ebp - 0x6e4]
00646762 lea ecx, [ebp - 0x15f4]
00646768 push eax
00646769 call 0x412050
0064676e sub esp, 0xc
00646771 mov ecx, esp
00646773 movups xmm0, xmmword ptr [eax]
00646776 movups xmmword ptr [ecx], xmm0
00646779 mov ecx, edi
0064677b call 0x5b7520
00646780 mov esi, dword ptr [ebp - 0x6a8]
00646786 mov eax, dword ptr [edi]
00646788 push ecx
00646789 mov ecx, edi
0064678b movss xmm0, dword ptr [esi + 0x2e0]
00646793 mulss xmm0, dword ptr [ebp - 0x68c]
0064679b mov eax, dword ptr [eax + 0x3c]
0064679e movss dword ptr [esp], xmm0
006467a3 call eax
006467a5 push ecx
006467a6 mov ecx, edi
006467a8 mov dword ptr [esp], 0
006467af call 0x6414e0
006467b4 movss xmm0, dword ptr [esi + 0x370]
006467bc lea edx, [ebp - 0x7e4]
006467c2 mulss xmm0, dword ptr [ebp - 0x6c4]
006467ca lea ecx, [ebp - 0xc9c]
006467d0 push 0xbc7a28
006467d5 movss dword ptr [ebp - 0x7e4], xmm0
006467dd call 0x4120b0
006467e2 add esp, 4
006467e5 mov ecx, edi
006467e7 push eax
006467e8 call 0x427330
006467ed mov eax, dword ptr [edi]
006467ef mov eax, dword ptr [eax + 0xc]
006467f2 mov ecx, edi
006467f4 call eax
006467f6 mov esi, dword ptr [ebp - 0x668]
006467fc mov ecx, esi
006467fe push edi
006467ff call 0x657470
00646804 movss xmm0, dword ptr [ebp - 0x69c]
0064680c push ecx
0064680d mov ecx, esi
0064680f movss dword ptr [esp], xmm0
00646814 call 0x4076f0
00646819 mov ecx, eax
0064681b call 0x59fda0
00646820 mov edi, dword ptr [ebp - 0x6a8]
00646826 mov ecx, esi
00646828 call 0x4076f0
0064682d test eax, eax
0064682f je 0x6471f2
00646835 mov ecx, esi
00646837 call 0x4076f0
0064683c movss xmm0, dword ptr [edi + 0x2e0]
00646844 mulss xmm0, dword ptr [ebp - 0x68c]
0064684c push ecx
0064684d mov edx, dword ptr [eax]
0064684f mov ecx, eax
00646851 movss dword ptr [esp], xmm0
00646856 mov eax, dword ptr [edx + 0x3c]
00646859 call eax
0064685b movss xmm0, dword ptr [edi + 0x370]
00646863 lea esi, [edi + 0x370]
00646869 mulss xmm0, dword ptr [ebp - 0x6c4]
00646871 lea edx, [ebp - 0x7e8]
00646877 push 0xbc7a28
0064687c lea ecx, [ebp - 0xca4]
00646882 movss dword ptr [ebp - 0x7e8], xmm0
0064688a call 0x4120b0
0064688f add esp, 4
00646892 lea ecx, [edi + 0x3ec]
00646898 push eax
00646899 call 0x4076f0
0064689e mov ecx, eax
006468a0 call 0x427330
006468a5 movss xmm2, dword ptr [0xb6a910]
006468ad lea eax, [ebp - 0xcac]
006468b3 movss xmm1, dword ptr [ebp - 0x67c]
006468bb lea ecx, [ebp - 0xcb4]
006468c1 push esi
006468c2 push eax
006468c3 call 0x9624e0
006468c8 mov ecx, eax
006468ca call 0x962b50
006468cf push eax
006468d0 lea eax, [ebp - 0xcbc]
006468d6 push eax
006468d7 lea ecx, [edi + 0x2a4]
006468dd call 0x962a60
006468e2 lea esi, [edi + 0x3ec]
006468e8 push eax
006468e9 mov ecx, esi
006468eb call 0x4076f0
006468f0 mov ecx, eax
006468f2 call 0x412190
006468f7 movss xmm0, dword ptr [ebp - 0x69c]
006468ff lea eax, [ebp - 0xcc4]
00646905 push ecx
00646906 movss dword ptr [esp], xmm0
0064690b push eax
0064690c call 0x9627f0
00646911 add esp, 8
00646914 mov ecx, esi
00646916 call 0x4076f0
0064691b mov ecx, eax
0064691d call 0x5ef140
00646922 comiss xmm0, dword ptr [0xb6a64c]
00646929 mov ecx, esi
0064692b jbe 0x646968
0064692d push 0
0064692f push 1
00646931 call 0x4076f0
00646936 mov ecx, eax
00646938 call 0x8c1050
0064693d mov ecx, esi
0064693f call 0x4076f0
00646944 movss xmm1, dword ptr [ebp - 0x67c]
0064694c mov ecx, eax
0064694e call 0x6415b0
00646953 push 0
00646955 mov ecx, esi
00646957 call 0x4076f0
0064695c mov ecx, eax
0064695e call 0x6415c0
00646963 jmp 0x646aa9
00646968 call 0x4076f0
0064696d mov ecx, eax
0064696f call 0x641580
00646974 mov ecx, esi
00646976 test al, al
00646978 je 0x6469db
0064697a call 0x4076f0
0064697f mov ecx, eax
00646981 call 0x5ef140
00646986 addss xmm0, dword ptr [0xb6a264]
0064698e mov ecx, esi
00646990 movss dword ptr [ebp - 0x668], xmm0
00646998 call 0x4076f0
0064699d movss xmm1, dword ptr [ebp - 0x668]
006469a5 mov ecx, eax
006469a7 call 0x6415b0
006469ac mov ecx, esi
006469ae call 0x4076f0
006469b3 mov ecx, eax
006469b5 call 0x5ef140
006469ba comiss xmm0, dword ptr [ebp - 0x684]
006469c1 mov ecx, esi
006469c3 setae al
006469c6 movzx eax, al
006469c9 push eax
006469ca call 0x4076f0
006469cf mov ecx, eax
006469d1 call 0x6415c0
006469d6 jmp 0x646aa9
006469db call 0x4076f0
006469e0 mov ecx, eax
006469e2 call 0x641570
006469e7 test al, al
006469e9 jne 0x646aa9
006469ef mov ecx, esi
006469f1 call 0x4076f0
006469f6 mov ecx, eax
006469f8 call 0x4121c0
006469fd movss xmm0, dword ptr [ebp - 0x684]
00646a05 lea edx, [ebp - 0x7ec]
00646a0b lea ecx, [ebp - 0x7f0]
00646a11 movss xmm1, dword ptr [eax]
00646a15 mulss xmm1, dword ptr [ebp - 0x68c]
00646a1d mov dword ptr [ebp - 0x7f0], 0x3f000000
00646a27 addss xmm1, dword ptr [ebp - 0x68c]
00646a2f divss xmm0, xmm1
00646a33 movss dword ptr [ebp - 0x7ec], xmm0
00646a3b call 0x417c70
00646a40 movss xmm0, dword ptr [eax]
00646a44 movss dword ptr [ebp - 0x668], xmm0
00646a4c call 0x659200
00646a51 mulss xmm0, dword ptr [0xb6a350]
00646a59 push ecx
00646a5a movss xmm2, dword ptr [ebp - 0x684]
00646a62 mov ecx, dword ptr [0xbfd680]
00646a68 addss xmm0, dword ptr [0xb6a5a4]
00646a70 mulss xmm0, dword ptr [ebp - 0x668]
00646a78 movss dword ptr [esp], xmm0
00646a7d push 0
00646a7f push 1
00646a81 push 0xfc
00646a86 call 0x8b1480
00646a8b push 1
00646a8d mov ecx, esi
00646a8f call 0x4076f0
00646a94 mov ecx, eax
00646a96 call 0x641590
00646a9b mov ecx, esi
00646a9d call 0x4076f0
00646aa2 mov ecx, eax
00646aa4 call 0x8c0d00
00646aa9 mov ecx, esi
00646aab call 0x4076f0
00646ab0 mov ecx, eax
00646ab2 call 0x5ef380
00646ab7 test al, al
00646ab9 jne 0x646aef
00646abb mov ecx, esi
00646abd call 0x4076f0
00646ac2 mov ecx, eax
00646ac4 call 0x641570
00646ac9 test al, al
00646acb jne 0x646aef
00646acd mov ecx, esi
00646acf call 0x4076f0
00646ad4 mov ecx, eax
00646ad6 call 0x641580
00646adb test al, al
00646add jne 0x646aef
00646adf mov ecx, esi
00646ae1 call 0x4076f0
00646ae6 mov ecx, eax
00646ae8 mov edx, dword ptr [eax]
00646aea mov eax, dword ptr [edx + 0x28]
00646aed call eax
00646aef mov ecx, esi
00646af1 call 0x4076f0
00646af6 mov ecx, eax
00646af8 call 0x412340
00646afd test al, al
00646aff je 0x6471f2
00646b05 push 4
00646b07 push 0xb42298
00646b0c mov ecx, esi
00646b0e call 0x4076f0
00646b13 mov ecx, eax
00646b15 call 0x427440
00646b1a mov ecx, eax
00646b1c call 0x419b40
00646b21 mov ecx, eax
00646b23 call 0x402320
00646b28 push eax
00646b29 call dword ptr [0xa06640]
00646b2f add esp, 0xc
00646b32 test eax, eax
00646b34 jne 0x646bc9
00646b3a push 0xb40190
00646b3f lea eax, [ebp - 0xb84]
00646b45 mov ecx, esi
00646b47 push eax
00646b48 call 0x4076f0
00646b4d mov ecx, eax
00646b4f call 0x68e000
00646b54 lea ecx, [edi + 0x3c]
00646b57 call 0x419b40
00646b5c mov ecx, eax
00646b5e call 0x432ec0
00646b63 movss xmm1, dword ptr [0xb6ac40]
00646b6b lea ecx, [ebp - 0xb84]
00646b71 movd xmm0, eax
00646b75 cvtdq2ps xmm0, xmm0
00646b78 divss xmm1, xmm0
00646b7c movss dword ptr [ebp - 0x678], xmm1
00646b84 call 0x962830
00646b89 fstp dword ptr [ebp - 0x668]
00646b8f movss xmm0, dword ptr [ebp - 0x668]
00646b97 call 0x65a640
00646b9c movss xmm1, dword ptr [ebp - 0x67c]
00646ba4 comiss xmm1, xmm0
00646ba7 jbe 0x646bb1
00646ba9 addss xmm0, dword ptr [0xb6ac40]
00646bb1 divss xmm0, dword ptr [ebp - 0x678]
00646bb9 lea ecx, [edi + 0x3c]
00646bbc movaps xmm1, xmm0
00646bbf call 0x4058b0
00646bc4 jmp 0x6471f2
00646bc9 movss xmm0, dword ptr [ebp - 0x69c]
00646bd1 push ecx
00646bd2 mov ecx, esi
00646bd4 movss dword ptr [esp], xmm0
00646bd9 call 0x4076f0
00646bde mov ecx, eax
00646be0 call 0x59fda0
00646be5 jmp 0x6471f2
00646bea push 0xbc4700
00646bef lea edx, [edi + 0x378]
00646bf5 lea ecx, [ebp - 0x1604]
00646bfb call 0x412050
00646c00 add esp, 4
00646c03 mov ecx, eax
00646c05 call 0x412090
00646c0a test al, al
00646c0c je 0x646e5c
00646c12 lea eax, [edi + 0x3ec]
00646c18 mov ecx, eax
00646c1a mov dword ptr [ebp - 0x668], eax
00646c20 call 0x4076f0
00646c25 test eax, eax
00646c27 jne 0x646d62
00646c2d cmp byte ptr [edi + 0x16b], al
00646c33 jne 0x646d62
00646c39 call 0x6c3d90
00646c3e mov ecx, dword ptr [0xbfd65c]
00646c44 push eax
00646c45 push 0
00646c47 push dword ptr [ebp - 0x694]
00646c4d push 0xc02fec
00646c52 push esi
00646c53 push 0
00646c55 push 8
00646c57 call 0x422e20
00646c5c mov edi, eax
00646c5e mov eax, dword ptr [ebp - 0x6a8]
00646c64 push eax
00646c65 mov ecx, edi
00646c67 call 0x6818e0
00646c6c mov ecx, dword ptr [ebp - 0x674]
00646c72 mov esi, dword ptr [edi]
00646c74 push 1
00646c76 push 0
00646c78 push 0xff
00646c7d push -1
00646c7f call 0x4023b0
00646c84 push eax
00646c85 mov eax, dword ptr [esi + 0x38]
00646c88 mov ecx, edi
00646c8a call eax
00646c8c lea eax, [ebp - 0x1614]
00646c92 mov edx, 0xbc4bc0
00646c97 push eax
00646c98 push 0xbc4c60
00646c9d lea ecx, [ebp - 0x1624]
00646ca3 call 0x427220
00646ca8 add esp, 4
00646cab mov ecx, eax
00646cad call 0x57f3a0
00646cb2 mov edx, dword ptr [ebp - 0x6e4]
00646cb8 lea ecx, [ebp - 0x1634]
00646cbe push eax
00646cbf call 0x412050
00646cc4 sub esp, 0xc
00646cc7 mov ecx, esp
00646cc9 movups xmm0, xmmword ptr [eax]
00646ccc movups xmmword ptr [ecx], xmm0
00646ccf mov ecx, edi
00646cd1 call 0x5b7520
00646cd6 mov esi, dword ptr [ebp - 0x6a8]
00646cdc mov eax, dword ptr [edi]
00646cde push ecx
00646cdf mov ecx, edi
00646ce1 movss xmm0, dword ptr [esi + 0x2e0]
00646ce9 mulss xmm0, dword ptr [ebp - 0x68c]
00646cf1 mov eax, dword ptr [eax + 0x3c]
00646cf4 movss dword ptr [esp], xmm0
00646cf9 call eax
00646cfb push ecx
00646cfc mov ecx, edi
00646cfe mov dword ptr [esp], 0
00646d05 call 0x6414e0
00646d0a movss xmm0, dword ptr [esi + 0x370]
00646d12 lea edx, [ebp - 0x7f4]
00646d18 mulss xmm0, dword ptr [ebp - 0x68c]
00646d20 lea ecx, [ebp - 0xccc]
00646d26 push 0xbc7a28
00646d2b movss dword ptr [ebp - 0x7f4], xmm0
00646d33 call 0x4120b0
00646d38 add esp, 4
00646d3b mov ecx, edi
00646d3d push eax
00646d3e call 0x427330
00646d43 mov eax, dword ptr [edi]
00646d45 mov ecx, edi
00646d47 mov eax, dword ptr [eax + 0xc]
00646d4a call eax
00646d4c mov esi, dword ptr [ebp - 0x668]
00646d52 mov ecx, esi
00646d54 push edi
00646d55 call 0x657470
00646d5a mov edi, dword ptr [ebp - 0x6a8]
00646d60 jmp 0x646d68
00646d62 lea esi, [edi + 0x3ec]
00646d68 mov ecx, esi
00646d6a call 0x4076f0
00646d6f test eax, eax
00646d71 je 0x6471f2
00646d77 mov ecx, esi
00646d79 call 0x4076f0
00646d7e movss xmm0, dword ptr [edi + 0x2e0]
00646d86 mulss xmm0, dword ptr [ebp - 0x68c]
00646d8e push ecx
00646d8f mov edx, dword ptr [eax]
00646d91 mov ecx, eax
00646d93 movss dword ptr [esp], xmm0
00646d98 mov eax, dword ptr [edx + 0x3c]
00646d9b call eax
00646d9d movss xmm0, dword ptr [edi + 0x370]
00646da5 lea esi, [edi + 0x370]
00646dab mulss xmm0, dword ptr [ebp - 0x68c]
00646db3 lea edx, [ebp - 0x7f8]
00646db9 push 0xbc7a28
00646dbe lea ecx, [ebp - 0xcd4]
00646dc4 movss dword ptr [ebp - 0x7f8], xmm0
00646dcc call 0x4120b0
00646dd1 add esp, 4
00646dd4 lea ecx, [edi + 0x3ec]
00646dda push eax
00646ddb call 0x4076f0
00646de0 mov ecx, eax
00646de2 call 0x427330
00646de7 movss xmm2, dword ptr [0xb6a8cc]
00646def lea eax, [ebp - 0xcdc]
00646df5 movss xmm1, dword ptr [ebp - 0x67c]
00646dfd lea ecx, [ebp - 0xce4]
00646e03 push esi
00646e04 push eax
00646e05 call 0x9624e0
00646e0a mov ecx, eax
00646e0c call 0x962b50
00646e11 push eax
00646e12 lea eax, [ebp - 0xcec]
00646e18 push eax
00646e19 lea ecx, [edi + 0x2a4]
00646e1f call 0x962a60
00646e24 push eax
00646e25 lea ecx, [edi + 0x3ec]
00646e2b call 0x4076f0
00646e30 mov ecx, eax
00646e32 call 0x412190
00646e37 movss xmm0, dword ptr [ebp - 0x69c]
00646e3f push ecx
00646e40 lea ecx, [edi + 0x3ec]
00646e46 movss dword ptr [esp], xmm0
00646e4b call 0x4076f0
00646e50 mov ecx, eax
00646e52 call 0x59fda0
00646e57 jmp 0x6471f2
00646e5c push 0xbc4840
00646e61 lea edx, [edi + 0x378]
00646e67 lea ecx, [ebp - 0x1644]
00646e6d call 0x412050
00646e72 add esp, 4
00646e75 mov ecx, eax
00646e77 call 0x412090
00646e7c test al, al
00646e7e je 0x6471f2
00646e84 lea eax, [edi + 0x3ec]
00646e8a mov ecx, eax
00646e8c mov dword ptr [ebp - 0x668], eax
00646e92 call 0x4076f0
00646e97 test eax, eax
00646e99 jne 0x646fcc
00646e9f cmp byte ptr [edi + 0x16b], al
00646ea5 jne 0x646fcc
00646eab call 0x6c3d90
00646eb0 mov ecx, dword ptr [0xbfd65c]
00646eb6 push eax
00646eb7 push 0
00646eb9 push dword ptr [ebp - 0x694]
00646ebf push 0xc02fec
00646ec4 push esi
00646ec5 push 1
00646ec7 push 8
00646ec9 call 0x422e20
00646ece mov edi, eax
00646ed0 mov eax, dword ptr [ebp - 0x6a8]
00646ed6 push eax
00646ed7 mov ecx, edi
00646ed9 call 0x6818e0
00646ede mov ecx, dword ptr [ebp - 0x674]
00646ee4 mov esi, dword ptr [edi]
00646ee6 push 1
00646ee8 push 0
00646eea push 0xff
00646eef push -1
00646ef1 call 0x4023b0
00646ef6 push eax
00646ef7 mov eax, dword ptr [esi + 0x38]
00646efa mov ecx, edi
00646efc call eax
00646efe lea eax, [ebp - 0x1654]
00646f04 mov edx, 0xbc4bc0
00646f09 push eax
00646f0a push 0xbc4c60
00646f0f lea ecx, [ebp - 0x1664]
00646f15 call 0x427220
00646f1a add esp, 4
00646f1d mov ecx, eax
00646f1f call 0x57f3a0
00646f24 mov edx, dword ptr [ebp - 0x6e4]
00646f2a lea ecx, [ebp - 0x1674]
00646f30 push eax
00646f31 call 0x412050
00646f36 sub esp, 0xc
00646f39 mov ecx, esp
00646f3b movups xmm0, xmmword ptr [eax]
00646f3e movups xmmword ptr [ecx], xmm0
00646f41 mov ecx, edi
00646f43 call 0x5b7520
00646f48 mov eax, dword ptr [edi]
00646f4a mov esi, dword ptr [ebp - 0x6a8]
00646f50 push ecx
00646f51 mov ecx, edi
00646f53 mov eax, dword ptr [eax + 0x3c]
00646f56 movss xmm0, dword ptr [esi + 0x2e0]
00646f5e movss dword ptr [esp], xmm0
00646f63 call eax
00646f65 push ecx
00646f66 mov ecx, edi
00646f68 mov dword ptr [esp], 0
00646f6f call 0x6414e0
00646f74 movss xmm0, dword ptr [esi + 0x370]
00646f7c lea edx, [ebp - 0x7fc]
00646f82 mulss xmm0, dword ptr [ebp - 0x6c4]
00646f8a lea ecx, [ebp - 0xcf4]
00646f90 push 0xbc7a28
00646f95 movss dword ptr [ebp - 0x7fc], xmm0
00646f9d call 0x4120b0
00646fa2 add esp, 4
00646fa5 mov ecx, edi
00646fa7 push eax
00646fa8 call 0x427330
00646fad mov eax, dword ptr [edi]
00646faf mov ecx, edi
00646fb1 mov eax, dword ptr [eax + 0xc]
00646fb4 call eax
00646fb6 mov esi, dword ptr [ebp - 0x668]
00646fbc mov ecx, esi
00646fbe push edi
00646fbf call 0x657470
00646fc4 mov edi, dword ptr [ebp - 0x6a8]
00646fca jmp 0x646fd2
00646fcc lea esi, [edi + 0x3ec]
00646fd2 mov ecx, esi
00646fd4 call 0x4076f0
00646fd9 test eax, eax
00646fdb je 0x6471f2
00646fe1 movss xmm2, dword ptr [0xb6a910]
00646fe9 lea eax, [edi + 0x370]
00646fef movss xmm1, dword ptr [ebp - 0x67c]
00646ff7 lea ecx, [ebp - 0xd04]
00646ffd push eax
00646ffe lea eax, [ebp - 0xcfc]
00647004 push eax
00647005 call 0x9624e0
0064700a mov ecx, eax
0064700c call 0x962b50
00647011 push eax
00647012 lea eax, [ebp - 0xd0c]
00647018 push eax
00647019 lea ecx, [edi + 0x2a4]
0064701f call 0x962a60
00647024 push eax
00647025 mov ecx, esi
00647027 call 0x4076f0
0064702c mov ecx, eax
0064702e call 0x412190
00647033 movss xmm0, dword ptr [ebp - 0x69c]
0064703b push ecx
0064703c mov ecx, esi
0064703e movss dword ptr [esp], xmm0
00647043 call 0x4076f0
00647048 mov ecx, eax
0064704a call 0x59fda0
0064704f mov ecx, esi
00647051 call 0x4076f0
00647056 mov ecx, eax
00647058 call 0x641570
0064705d test al, al
0064705f jne 0x6471eb
00647065 movss xmm0, dword ptr [ebp - 0x69c]
0064706d lea eax, [ebp - 0xb14]
00647073 push ecx
00647074 movss dword ptr [esp], xmm0
00647079 push eax
0064707a call 0x9627f0
0064707f mov ecx, dword ptr [edi + 0x31c]
00647085 add esp, 8
00647088 test ecx, ecx
0064708a je 0x6471eb
00647090 lea eax, [ebp - 0xb14]
00647096 push eax
00647097 lea eax, [ebp - 0xd14]
0064709d push eax
0064709e lea esi, [edi + 0x294]
006470a4 push esi
006470a5 lea eax, [ebp - 0xd1c]
006470ab push eax
006470ac lea eax, [ebp - 0xd24]
006470b2 push eax
006470b3 call 0x412130
006470b8 mov ecx, eax
006470ba call 0x962ac0
006470bf mov ecx, eax
006470c1 call 0x962560
006470c6 mov ecx, eax
006470c8 call 0x962600
006470cd fstp dword ptr [ebp - 0x668]
006470d3 movss xmm0, dword ptr [ebp - 0x668]
006470db comiss xmm0, dword ptr [0xb6a2cc]
006470e2 jbe 0x6471eb
006470e8 mov ecx, dword ptr [edi + 0x31c]
006470ee lea eax, [ebp - 0xd2c]
006470f4 push esi
006470f5 push eax
006470f6 call 0x412130
006470fb mov ecx, eax
006470fd call 0x9626f0
00647102 movss xmm0, dword ptr [edi + 0x370]
0064710a mulss xmm0, dword ptr [0xb6aa60]
00647112 fstp dword ptr [ebp - 0x668]
00647118 comiss xmm0, dword ptr [ebp - 0x668]
0064711f jbe 0x6471eb
00647125 lea ecx, [edi + 0x3ec]
0064712b call 0x4076f0
00647130 mov ecx, eax
00647132 call 0x4121c0
00647137 movss xmm0, dword ptr [ebp - 0x684]
0064713f lea edx, [ebp - 0x800]
00647145 lea ecx, [ebp - 0x804]
0064714b movss xmm1, dword ptr [eax]
0064714f mulss xmm1, dword ptr [ebp - 0x68c]
00647157 mov dword ptr [ebp - 0x804], 0x3f000000
00647161 addss xmm1, dword ptr [ebp - 0x68c]
00647169 divss xmm0, xmm1
0064716d movss dword ptr [ebp - 0x800], xmm0
00647175 call 0x417c70
0064717a movss xmm0, dword ptr [eax]
0064717e movss dword ptr [ebp - 0x668], xmm0
00647186 call 0x659200
0064718b mulss xmm0, dword ptr [0xb6a350]
00647193 push ecx
00647194 movss xmm2, dword ptr [ebp - 0x684]
0064719c mov ecx, dword ptr [0xbfd680]
006471a2 addss xmm0, dword ptr [0xb6a5a4]
006471aa mulss xmm0, dword ptr [ebp - 0x668]
006471b2 movss dword ptr [esp], xmm0
006471b7 push 0
006471b9 push 1
006471bb push 0xfc
006471c0 call 0x8b1480
006471c5 push 1
006471c7 lea ecx, [edi + 0x3ec]
006471cd call 0x4076f0
006471d2 mov ecx, eax
006471d4 call 0x641590
006471d9 lea ecx, [edi + 0x3ec]
006471df call 0x4076f0
006471e4 mov ecx, eax
006471e6 call 0x8c0d00
006471eb mov byte ptr [ebp - 0x68d], 1
006471f2 push 0xbc4850
006471f7 lea edx, [edi + 0x378]
006471fd lea ecx, [ebp - 0x1684]
00647203 call 0x412050
00647208 add esp, 4
0064720b mov ecx, eax
0064720d call 0x412090
00647212 test al, al
00647214 je 0x64722b
00647216 mov eax, dword ptr [edi + 0x3f8]
0064721c test eax, eax
0064721e jle 0x6478e7
00647224 dec eax
00647225 mov dword ptr [edi + 0x3f8], eax
0064722b lea esi, [edi + 0x294]
00647231 movss xmm2, dword ptr [edi + 0x2fc]
00647239 divss xmm2, dword ptr [0xb6a974]
00647241 movss xmm1, dword ptr [0xb6a7b0]
00647249 movss xmm0, dword ptr [ebp - 0x67c]
00647251 call 0x9623e0
00647256 movss xmm2, dword ptr [ebp - 0x684]
0064725e movss xmm1, dword ptr [0xb6a7b0]
00647266 subss xmm2, xmm0
0064726a movaps xmm0, xmm2
0064726d call 0x4c3f60
00647272 mulss xmm0, dword ptr [0xb6a2cc]
0064727a lea edx, [ebp - 0x818]
00647280 lea ecx, [ebp - 0x81c]
00647286 addss xmm0, dword ptr [0xb6a5a4]
0064728e movss dword ptr [edi + 0x2c4], xmm0
00647296 movss xmm0, dword ptr [edi + 0x2fc]
0064729e divss xmm0, dword ptr [0xb6aa4c]
006472a6 mov dword ptr [ebp - 0x81c], 0x3f800000
006472b0 movss dword ptr [ebp - 0x818], xmm0
006472b8 call 0x407e80
006472bd push dword ptr [edi + 0x20]
006472c0 mov ecx, edi
006472c2 push 8
006472c4 movss xmm0, dword ptr [eax]
006472c8 movss dword ptr [ebp - 0x694], xmm0
006472d0 call 0x684790
006472d5 test al, al
006472d7 je 0x6472ef
006472d9 cmp dword ptr [edi + 0x3c8], 0
006472e0 jne 0x6472ef
006472e2 push 0
006472e4 lea ecx, [edi + 0x394]
006472ea call 0x4d1fd0
006472ef cmp dword ptr [edi + 0x31c], 0
006472f6 jne 0x647524
006472fc push dword ptr [edi + 0x20]
006472ff mov ecx, edi
00647301 push 4
00647303 call 0x684790
00647308 test al, al
0064730a je 0x647524
00647310 movss xmm0, dword ptr [0xb6adb4]
00647318 lea eax, [edi + 0x2b8]
0064731e push 8
00647320 push eax
00647321 lea edx, [ebp - 0x820]
00647327 mov dword ptr [ebp - 0x6a0], 0
00647331 lea ecx, [ebp - 0xd64]
00647337 movss dword ptr [ebp - 0x678], xmm0
0064733f mov dword ptr [ebp - 0x820], 0x40a00000
00647349 call 0x4120b0
0064734e add esp, 4
00647351 mov ecx, esi
00647353 push eax
00647354 lea eax, [ebp - 0xd6c]
0064735a push eax
0064735b call 0x962a60
00647360 mov ecx, dword ptr [0xbfd65c]
00647366 push eax
00647367 lea eax, [ebp - 0xaec]
0064736d push eax
0064736e call 0x4023f0
00647373 mov ecx, eax
00647375 call 0x422d70
0064737a movss xmm3, dword ptr [0xb6ab30]
00647382 mov ecx, eax
00647384 call 0x4157f0
00647389 lea ecx, [ebp - 0xaec]
0064738f mov dword ptr [ebp - 4], 2
00647396 mov dword ptr [ebp - 0x670], 0
006473a0 call 0x4083d0
006473a5 test eax, eax
006473a7 je 0x647505
006473ad xor ecx, ecx
006473af nop 
006473b0 push ecx
006473b1 lea ecx, [ebp - 0xaec]
006473b7 call 0x4124b0
006473bc push 0
006473be mov eax, dword ptr [eax]
006473c0 mov ecx, eax
006473c2 mov dword ptr [ebp - 0x674], eax
006473c8 call 0x684630
006473cd test al, al
006473cf je 0x6474e6
006473d5 mov ecx, dword ptr [ebp - 0x674]
006473db push 0
006473dd push 0x20000010
006473e2 call 0x4122f0
006473e7 test al, al
006473e9 jne 0x6474e6
006473ef mov ecx, 2
006473f4 call 0x659230
006473f9 test eax, eax
006473fb je 0x6474e6
00647401 cmp dword ptr [edi + 0x17c], 4
00647408 jne 0x647442
0064740a mov ecx, dword ptr [ebp - 0x674]
00647410 lea eax, [ebp - 0xd74]
00647416 push 0
00647418 push 0
0064741a push 0
0064741c push 0
0064741e push 3
00647420 push eax
00647421 call 0x412130
00647426 mov ecx, dword ptr [0xbfd65c]
0064742c push eax
0064742d push esi
0064742e call 0x4023f0
00647433 mov ecx, eax
00647435 call 0x7af4b0
0064743a test al, al
0064743c je 0x6474e6
00647442 mov ecx, dword ptr [ebp - 0x674]
00647448 lea eax, [ebp - 0xd7c]
0064744e push eax
0064744f mov dword ptr [ebp - 0x90c], 0x40a00000
00647459 call 0x412130
0064745e push eax
0064745f lea eax, [edi + 0x2b8]
00647465 push eax
00647466 lea edx, [ebp - 0x90c]
0064746c lea ecx, [ebp - 0xd84]
00647472 call 0x4120b0
00647477 add esp, 4
0064747a mov ecx, esi
0064747c push eax
0064747d lea eax, [ebp - 0xd8c]
00647483 push eax
00647484 call 0x962a60
00647489 mov ecx, eax
0064748b call 0x9626f0
00647490 fstp dword ptr [ebp - 0x66c]
00647496 call 0x659200
0064749b mulss xmm0, dword ptr [0xb6ab30]
006474a3 movss xmm1, dword ptr [ebp - 0x678]
006474ab movss dword ptr [ebp - 0x668], xmm0
006474b3 fld dword ptr [ebp - 0x668]
006474b9 fadd dword ptr [ebp - 0x66c]
006474bf fstp dword ptr [ebp - 0x668]
006474c5 movss xmm0, dword ptr [ebp - 0x668]
006474cd comiss xmm1, xmm0
006474d0 jbe 0x6474e6
006474d2 mov eax, dword ptr [ebp - 0x674]
006474d8 movss dword ptr [ebp - 0x678], xmm0
006474e0 mov dword ptr [ebp - 0x6a0], eax
006474e6 inc dword ptr [ebp - 0x670]
006474ec lea ecx, [ebp - 0xaec]
006474f2 call 0x4083d0
006474f7 mov ecx, dword ptr [ebp - 0x670]
006474fd cmp ecx, eax
006474ff jb 0x6473b0
00647505 push dword ptr [ebp - 0x6a0]
0064750b mov ecx, edi
0064750d call 0x681960
00647512 lea ecx, [ebp - 0xaec]
00647518 mov dword ptr [ebp - 4], 0xffffffff
0064751f call 0x412490
00647524 mov ecx, dword ptr [edi + 0x31c]
0064752a test ecx, ecx
0064752c je 0x648161
00647532 lea eax, [ebp - 0xd94]
00647538 push eax
00647539 call 0x412130
0064753e push eax
0064753f lea eax, [ebp - 0x704]
00647545 mov ecx, esi
00647547 push eax
00647548 call 0x962ac0
0064754d lea eax, [ebp - 0xd9c]
00647553 push eax
00647554 lea ecx, [ebp - 0x704]
0064755a call 0x962560
0064755f push eax
00647560 lea ecx, [edi + 0x2b8]
00647566 call 0x962600
0064756b fstp dword ptr [ebp - 0x668]
00647571 movss xmm0, dword ptr [ebp - 0x668]
00647579 lea ecx, [ebp - 0x704]
0064757f mulss xmm0, dword ptr [0xb6a2cc]
00647587 addss xmm0, dword ptr [0xb6a6b8]
0064758f mulss xmm0, dword ptr [ebp - 0x694]
00647597 movss dword ptr [ebp - 0x834], xmm0
0064759f call 0x962a00
006475a4 fmul dword ptr [0xb6a1c0]
006475aa lea eax, [ebp - 0xda4]
006475b0 push eax
006475b1 lea ecx, [ebp - 0x704]
006475b7 mov dword ptr [ebp - 0x828], 0
006475c1 fsubr dword ptr [0xb6a2ac]
006475c7 fstp dword ptr [ebp - 0x824]
006475cd call 0x962560
006475d2 push eax
006475d3 lea eax, [ebp - 0xdac]
006475d9 push eax
006475da lea ecx, [edi + 0x2b8]
006475e0 call 0x962560
006475e5 mov ecx, eax
006475e7 call 0x962600
006475ec fmul dword ptr [0xb6a274]
006475f2 lea edx, [ebp - 0x824]
006475f8 lea ecx, [ebp - 0x828]
006475fe fsubr dword ptr [0xb6a5b8]
00647604 fstp dword ptr [ebp - 0x668]
0064760a call 0x417c70
0064760f movss xmm0, dword ptr [ebp - 0x668]
00647617 lea edx, [ebp - 0x82c]
0064761d lea ecx, [ebp - 0x830]
00647623 addss xmm0, dword ptr [eax]
00647627 mov dword ptr [ebp - 0x830], 0x3f7ae148
00647631 movss dword ptr [ebp - 0x82c], xmm0
00647639 call 0x407e80
0064763e lea ecx, [ebp - 0x704]
00647644 movss xmm0, dword ptr [eax]
00647648 lea eax, [ebp - 0x834]
0064764e push eax
0064764f lea eax, [ebp - 0xdb4]
00647655 movss dword ptr [ebp - 0x668], xmm0
0064765d push eax
0064765e lea eax, [ebp - 0xdbc]
00647664 push eax
00647665 call 0x962560
0064766a push eax
0064766b lea edx, [edi + 0x2f4]
00647671 lea ecx, [ebp - 0xdc4]
00647677 call 0x4120b0
0064767c add esp, 4
0064767f mov ecx, eax
00647681 call 0x962b50
00647686 push eax
00647687 lea ecx, [edi + 0x2b8]
0064768d call 0x962af0
00647692 movss xmm1, dword ptr [edi + 0x2f4]
0064769a movss xmm0, dword ptr [ebp - 0x668]
006476a2 call 0x65c960
006476a7 lea eax, [ebp - 0x838]
006476ad movss dword ptr [ebp - 0x838], xmm0
006476b5 push eax
006476b6 lea ecx, [edi + 0x2b8]
006476bc call 0x962bb0
006476c1 movss xmm2, dword ptr [0xb6a7b0]
006476c9 movss dword ptr [ebp - 0x674], xmm2
006476d1 lea esi, [edi + 0x378]
006476d7 push 0xbc4cb0
006476dc mov edx, esi
006476de lea ecx, [ebp - 0x1754]
006476e4 call 0x412050
006476e9 add esp, 4
006476ec mov ecx, eax
006476ee call 0x412090
006476f3 test al, al
006476f5 je 0x647707
006476f7 movss xmm2, dword ptr [0xb6a98c]
006476ff movss dword ptr [ebp - 0x674], xmm2
00647707 lea ecx, [edi + 0x2b8]
0064770d call 0x962a00
00647712 movss xmm0, dword ptr [ebp - 0x674]
0064771a lea eax, [ebp - 0xdcc]
00647720 fstp dword ptr [ebp - 0x83c]
00647726 mulss xmm0, dword ptr [edi + 0x2f4]
0064772e lea ecx, [ebp - 0x704]
00647734 push eax
00647735 movss dword ptr [ebp - 0x674], xmm0
0064773d call 0x962b20
00647742 mov ecx, eax
00647744 call 0x962830
00647749 fstp dword ptr [ebp - 0x668]
0064774f lea ecx, [edi + 0x2b8]
00647755 call 0x962830
0064775a movss xmm2, dword ptr [ebp - 0x674]
00647762 movss xmm1, dword ptr [ebp - 0x668]
0064776a fstp dword ptr [ebp - 0x678]
00647770 movss xmm0, dword ptr [ebp - 0x678]
00647778 call 0x65a950
0064777d push ecx
0064777e lea eax, [ebp - 0xdd4]
00647784 movss dword ptr [esp], xmm0
00647789 push eax
0064778a call 0x9627f0
0064778f push eax
00647790 lea edx, [ebp - 0x83c]
00647796 lea ecx, [ebp - 0xddc]
0064779c call 0x4120b0
006477a1 add esp, 0xc
006477a4 lea ecx, [edi + 0x2b8]
006477aa push eax
006477ab call 0x962cd0
006477b0 cmp byte ptr [ebp - 0x68d], 0
006477b7 je 0x648167
006477bd push 0xc02fec
006477c2 lea ecx, [ebp - 0x704]
006477c8 call 0x962ca0
006477cd test al, al
006477cf je 0x648167
006477d5 lea ecx, [edi + 0x3c]
006477d8 call 0x419b40
006477dd mov ecx, eax
006477df call 0x432ec0
006477e4 movss xmm1, dword ptr [0xb6ac40]
006477ec lea ecx, [edi + 0x3c]
006477ef movd xmm0, eax
006477f3 cvtdq2ps xmm0, xmm0
006477f6 divss xmm1, xmm0
006477fa movss dword ptr [ebp - 0x678], xmm1
00647802 call 0x405930
00647807 mulss xmm0, dword ptr [ebp - 0x678]
0064780f lea ecx, [ebp - 0x704]
00647815 movss dword ptr [ebp - 0x668], xmm0
0064781d call 0x962a30
00647822 lea eax, [ebp - 0x840]
00647828 push eax
00647829 fstp dword ptr [ebp - 0x840]
0064782f movss xmm1, dword ptr [edi + 0x2f4]
00647837 lea eax, [ebp - 0xde4]
0064783d mulss xmm1, dword ptr [ebp - 0x6e0]
00647845 lea edx, [ebp - 0x844]
0064784b push eax
0064784c lea eax, [ebp - 0x704]
00647852 push eax
00647853 lea ecx, [ebp - 0xdec]
00647859 movss dword ptr [ebp - 0x844], xmm1
00647861 call 0x4120b0
00647866 add esp, 4
00647869 mov ecx, eax
0064786b call 0x962c10
00647870 movss xmm0, dword ptr [ebp - 0x668]
00647878 push eax
00647879 lea eax, [ebp - 0xb24]
0064787f push eax
00647880 push ecx
00647881 lea eax, [ebp - 0xdf4]
00647887 movss dword ptr [esp], xmm0
0064788c push eax
0064788d call 0x9627f0
00647892 add esp, 8
00647895 mov ecx, eax
00647897 call 0x962a60
0064789c lea ecx, [ebp - 0xb24]
006478a2 call 0x962830
006478a7 fstp dword ptr [ebp - 0x668]
006478ad movss xmm0, dword ptr [ebp - 0x668]
006478b5 call 0x65a640
006478ba movss xmm1, dword ptr [ebp - 0x67c]
006478c2 comiss xmm1, xmm0
006478c5 jbe 0x6478cf
006478c7 addss xmm0, dword ptr [0xb6ac40]
006478cf divss xmm0, dword ptr [ebp - 0x678]
006478d7 lea ecx, [edi + 0x3c]
006478da movaps xmm1, xmm0
006478dd call 0x4058b0
006478e2 jmp 0x648167
006478e7 movss xmm0, dword ptr [ebp - 0x69c]
006478ef lea eax, [ebp - 0xb1c]
006478f5 push ecx
006478f6 movss dword ptr [esp], xmm0
006478fb push eax
006478fc call 0x9627f0
00647901 movss xmm0, dword ptr [0xb6ae44]
00647909 lea esi, [edi + 0x294]
0064790f add esp, 8
00647912 movss dword ptr [ebp - 0x66c], xmm0
0064791a xor ecx, ecx
0064791c lea eax, [ebp - 0xadc]
00647922 mov dword ptr [ebp - 0x678], ecx
00647928 mov ecx, dword ptr [0xbfd65c]
0064792e push 8
00647930 push esi
00647931 push eax
00647932 call 0x4023f0
00647937 mov ecx, eax
00647939 call 0x422d70
0064793e movss xmm3, dword ptr [0xb6ab44]
00647946 mov ecx, eax
00647948 call 0x4157f0
0064794d lea ecx, [ebp - 0xadc]
00647953 mov dword ptr [ebp - 4], 1
0064795a mov dword ptr [ebp - 0x670], 0
00647964 call 0x4083d0
00647969 test eax, eax
0064796b je 0x647d90
00647971 xor ecx, ecx
00647973 push ecx
00647974 lea ecx, [ebp - 0xadc]
0064797a call 0x4124b0
0064797f push 0
00647981 mov eax, dword ptr [eax]
00647983 mov ecx, eax
00647985 mov dword ptr [ebp - 0x674], eax
0064798b call 0x684630
00647990 test al, al
00647992 je 0x647a57
00647998 mov ecx, dword ptr [ebp - 0x674]
0064799e push 0
006479a0 push 0x20000010
006479a5 call 0x4122f0
006479aa test al, al
006479ac jne 0x647a57
006479b2 cmp dword ptr [edi + 0x17c], 4
006479b9 jne 0x6479ef
006479bb mov ecx, dword ptr [ebp - 0x674]
006479c1 lea eax, [ebp - 0xd34]
006479c7 push 0
006479c9 push 0
006479cb push 0
006479cd push 0
006479cf push 3
006479d1 push eax
006479d2 call 0x412130
006479d7 mov ecx, dword ptr [0xbfd65c]
006479dd push eax
006479de push esi
006479df call 0x4023f0
006479e4 mov ecx, eax
006479e6 call 0x7af4b0
006479eb test al, al
006479ed je 0x647a57
006479ef mov ecx, dword ptr [ebp - 0x674]
006479f5 lea eax, [ebp - 0xb1c]
006479fb push eax
006479fc lea eax, [ebp - 0xd3c]
00647a02 push eax
00647a03 push esi
00647a04 lea eax, [ebp - 0xd44]
00647a0a push eax
00647a0b lea eax, [ebp - 0xd4c]
00647a11 push eax
00647a12 call 0x412130
00647a17 mov ecx, eax
00647a19 call 0x962ac0
00647a1e mov ecx, eax
00647a20 call 0x962560
00647a25 mov ecx, eax
00647a27 call 0x962600
00647a2c fstp dword ptr [ebp - 0x668]
00647a32 movss xmm0, dword ptr [ebp - 0x668]
00647a3a comiss xmm0, dword ptr [ebp - 0x66c]
00647a41 jbe 0x647a57
00647a43 mov eax, dword ptr [ebp - 0x674]
00647a49 movss dword ptr [ebp - 0x66c], xmm0
00647a51 mov dword ptr [ebp - 0x678], eax
00647a57 inc dword ptr [ebp - 0x670]
00647a5d lea ecx, [ebp - 0xadc]
00647a63 call 0x4083d0
00647a68 mov ecx, dword ptr [ebp - 0x670]
00647a6e cmp ecx, eax
00647a70 jb 0x647973
00647a76 movss xmm0, dword ptr [ebp - 0x66c]
00647a7e comiss xmm0, dword ptr [0xb6a588]
00647a85 jbe 0x647d90
00647a8b mov ecx, dword ptr [ebp - 0x678]
00647a91 test ecx, ecx
00647a93 je 0x647d90
00647a99 lea eax, [ebp - 0x958]
00647a9f mov dword ptr [edi + 0x3f8], 8
00647aa9 push eax
00647aaa push esi
00647aab lea eax, [ebp - 0xd54]
00647ab1 push eax
00647ab2 lea eax, [ebp - 0xd5c]
00647ab8 push eax
00647ab9 call 0x412130
00647abe mov ecx, eax
00647ac0 call 0x962ac0
00647ac5 mov ecx, eax
00647ac7 call 0x962560
00647acc push 1
00647ace push dword ptr [ebp - 0x694]
00647ad4 lea eax, [edi + 0x2a4]
00647ada push eax
00647adb push 3
00647add lea ecx, [ebp - 0x958]
00647ae3 call 0x962830
00647ae8 push ecx
00647ae9 fstp dword ptr [esp]
00647aec push esi
00647aed push 2
00647aef call 0x8c7550
00647af4 add esp, 0x1c
00647af7 mov dword ptr [ebp - 0x66c], eax
00647afd test eax, eax
00647aff je 0x647d90
00647b05 push 1
00647b07 mov ecx, eax
00647b09 call 0x5b74e0
00647b0e mov ecx, dword ptr [ebp - 0x66c]
00647b14 push 1
00647b16 call 0x4275f0
00647b1b lea eax, [ebp - 0x1694]
00647b21 mov edx, 0xbc4bc0
00647b26 push eax
00647b27 push 0xbc4c60
00647b2c lea ecx, [ebp - 0x16a4]
00647b32 call 0x427220
00647b37 add esp, 4
00647b3a mov ecx, eax
00647b3c call 0x57f3a0
00647b41 push eax
00647b42 lea edx, [edi + 0x378]
00647b48 lea ecx, [ebp - 0x16b4]
00647b4e call 0x412050
00647b53 sub esp, 0xc
00647b56 mov ecx, esp
00647b58 movups xmm0, xmmword ptr [eax]
00647b5b movups xmmword ptr [ecx], xmm0
00647b5e mov ecx, dword ptr [ebp - 0x66c]
00647b64 call 0x427580
00647b69 movss xmm0, dword ptr [0xb6a9c8]
00647b71 lea edx, [ebp - 0x808]
00647b77 subss xmm0, dword ptr [ebp - 0x6a0]
00647b7f lea ecx, [ebp - 0x80c]
00647b85 mov dword ptr [ebp - 0x80c], 1
00647b8f cvttss2si eax, xmm0
00647b93 mov dword ptr [ebp - 0x668], eax
00647b99 mov dword ptr [ebp - 0x808], eax
00647b9f call 0x417c80
00647ba4 mov ecx, dword ptr [eax]
00647ba6 call 0x659230
00647bab test eax, eax
00647bad je 0x647c20
00647baf lea eax, [ebp - 0x16c4]
00647bb5 mov edx, 0xbc4950
00647bba push eax
00647bbb push 0xbc4830
00647bc0 push 0xbc4b50
00647bc5 lea ecx, [ebp - 0x16d4]
00647bcb call 0x427220
00647bd0 add esp, 4
00647bd3 lea ecx, [ebp - 0x16e4]
00647bd9 mov edx, eax
00647bdb call 0x427220
00647be0 add esp, 4
00647be3 mov ecx, eax
00647be5 call 0x57f3a0
00647bea mov ecx, dword ptr [ebp - 0x66c]
00647bf0 push eax
00647bf1 lea eax, [ebp - 0x16f4]
00647bf7 push eax
00647bf8 call 0x412650
00647bfd mov edx, eax
00647bff lea ecx, [ebp - 0x1704]
00647c05 call 0x412050
00647c0a sub esp, 0xc
00647c0d mov ecx, esp
00647c0f movups xmm0, xmmword ptr [eax]
00647c12 movups xmmword ptr [ecx], xmm0
00647c15 mov ecx, dword ptr [ebp - 0x66c]
00647c1b call 0x427580
00647c20 mov eax, dword ptr [ebp - 0x668]
00647c26 lea edx, [ebp - 0x810]
00647c2c lea ecx, [ebp - 0x814]
00647c32 mov dword ptr [ebp - 0x810], eax
00647c38 mov dword ptr [ebp - 0x814], 1
00647c42 call 0x417c80
00647c47 mov ecx, dword ptr [eax]
00647c49 call 0x659230
00647c4e test eax, eax
00647c50 je 0x647cae
00647c52 lea eax, [ebp - 0x1714]
00647c58 mov edx, 0xbc4790
00647c5d push eax
00647c5e push 0xbc4890
00647c63 lea ecx, [ebp - 0x1724]
00647c69 call 0x427220
00647c6e add esp, 4
00647c71 mov ecx, eax
00647c73 call 0x57f3a0
00647c78 mov ecx, dword ptr [ebp - 0x66c]
00647c7e push eax
00647c7f lea eax, [ebp - 0x1734]
00647c85 push eax
00647c86 call 0x412650
00647c8b mov edx, eax
00647c8d lea ecx, [ebp - 0x1744]
00647c93 call 0x412050
00647c98 sub esp, 0xc
00647c9b mov ecx, esp
00647c9d movups xmm0, xmmword ptr [eax]
00647ca0 movups xmmword ptr [ecx], xmm0
00647ca3 mov ecx, dword ptr [ebp - 0x66c]
00647ca9 call 0x427580
00647cae mov ecx, dword ptr [ebp - 0x66c]
00647cb4 movss xmm0, dword ptr [edi + 0x2e0]
00647cbc push ecx
00647cbd movss dword ptr [esp], xmm0
00647cc2 mov eax, dword ptr [ecx]
00647cc4 mov eax, dword ptr [eax + 0x3c]
00647cc7 call eax
00647cc9 movss xmm0, dword ptr [0xb6ae20]
00647cd1 comiss xmm0, dword ptr [ebp - 0x954]
00647cd8 ja 0x647ced
00647cda comiss xmm0, dword ptr [ebp - 0x958]
00647ce1 ja 0x647ced
00647ce3 push ecx
00647ce4 mov dword ptr [esp], 0x453b8000
00647ceb jmp 0x647cf5
00647ced push ecx
00647cee mov dword ptr [esp], 0xc1200000
00647cf5 mov ecx, dword ptr [ebp - 0x66c]
00647cfb call 0x4273d0
00647d00 mov eax, dword ptr [ebp - 0x694]
00647d06 test eax, eax
00647d08 je 0x647d55
00647d0a lea ecx, [ebp - 0x184]
00647d10 push ecx
00647d11 mov ecx, eax
00647d13 call 0x6415f0
00647d18 lea ecx, [edi + 0x3c]
00647d1b call 0x4023b0
00647d20 mov ecx, eax
00647d22 call 0x402220
00647d27 push ecx
00647d28 lea ecx, [ebp - 0x184]
00647d2e fstp dword ptr [esp]
00647d31 call 0x402230
00647d36 mov ecx, dword ptr [ebp - 0x66c]
00647d3c lea edx, [ebp - 0x184]
00647d42 push 1
00647d44 push 0
00647d46 push 0xff
00647d4b mov eax, dword ptr [ecx]
00647d4d push -1
00647d4f push edx
00647d50 mov eax, dword ptr [eax + 0x38]
00647d53 call eax
00647d55 push ecx
00647d56 mov ecx, dword ptr [ebp - 0x66c]
00647d5c mov dword ptr [esp], 0x430c0000
00647d63 call 0x4275b0
00647d68 movss xmm1, dword ptr [edi + 0x370]
00647d70 mulss xmm1, dword ptr [ebp - 0x6bc]
00647d78 mov ecx, dword ptr [ebp - 0x66c]
00647d7e call 0x8d7ff0
00647d83 mov ecx, dword ptr [ebp - 0x66c]
00647d89 mov eax, dword ptr [ecx]
00647d8b mov eax, dword ptr [eax + 0xc]
00647d8e call eax
00647d90 lea ecx, [ebp - 0xadc]
00647d96 mov dword ptr [ebp - 4], 0xffffffff
00647d9d call 0x412490
00647da2 jmp 0x647231
00647da7 push 0xbc4cb0
00647dac lea edx, [edi + 0x378]
00647db2 lea ecx, [ebp - 0x1764]
00647db8 call 0x412050
00647dbd add esp, 4
00647dc0 mov ecx, eax
00647dc2 call 0x412090
00647dc7 test al, al
00647dc9 jne 0x647df3
00647dcb push 0xbc4860
00647dd0 lea edx, [edi + 0x378]
00647dd6 lea ecx, [ebp - 0x1774]
00647ddc call 0x412050
00647de1 add esp, 4
00647de4 mov ecx, eax
00647de6 call 0x412090
00647deb test al, al
00647ded je 0x648161
00647df3 mov eax, dword ptr [edi + 0x31c]
00647df9 test eax, eax
00647dfb je 0x647e16
00647dfd push eax
00647dfe lea ecx, [edi + 0x394]
00647e04 call 0x422d00
00647e09 test al, al
00647e0b je 0x647e16
00647e0d push 0
00647e0f mov ecx, edi
00647e11 call 0x681960
00647e16 cmp dword ptr [edi + 0x31c], 0
00647e1d jne 0x648097
00647e23 push dword ptr [edi + 0x20]
00647e26 mov ecx, edi
00647e28 push 4
00647e2a call 0x684790
00647e2f test al, al
00647e31 je 0x64808a
00647e37 movss xmm0, dword ptr [0xb6adb4]
00647e3f lea eax, [edi + 0x2b8]
00647e45 push 8
00647e47 push eax
00647e48 lea edx, [ebp - 0x848]
00647e4e mov dword ptr [ebp - 0x66c], 0
00647e58 lea ecx, [ebp - 0xdfc]
00647e5e movss dword ptr [ebp - 0x6a0], xmm0
00647e66 mov dword ptr [ebp - 0x848], 0x40a00000
00647e70 call 0x4120b0
00647e75 add esp, 4
00647e78 mov ecx, esi
00647e7a push eax
00647e7b lea eax, [ebp - 0xe04]
00647e81 push eax
00647e82 call 0x962a60
00647e87 mov ecx, dword ptr [0xbfd65c]
00647e8d push eax
00647e8e lea eax, [ebp - 0xafc]
00647e94 push eax
00647e95 call 0x4023f0
00647e9a mov ecx, eax
00647e9c call 0x422d70
00647ea1 movss xmm3, dword ptr [0xb6ab30]
00647ea9 mov ecx, eax
00647eab call 0x4157f0
00647eb0 lea ecx, [ebp - 0xafc]
00647eb6 mov dword ptr [ebp - 4], 3
00647ebd mov dword ptr [ebp - 0x674], 0
00647ec7 call 0x4083d0
00647ecc test eax, eax
00647ece je 0x64806b
00647ed4 xor ecx, ecx
00647ed6 nop word ptr [eax + eax]
00647ee0 push ecx
00647ee1 lea ecx, [ebp - 0xafc]
00647ee7 call 0x4124b0
00647eec push 0
00647eee mov eax, dword ptr [eax]
00647ef0 mov ecx, eax
00647ef2 mov dword ptr [ebp - 0x670], eax
00647ef8 call 0x684630
00647efd test al, al
00647eff je 0x64804c
00647f05 mov ecx, dword ptr [ebp - 0x670]
00647f0b push 0
00647f0d push 0x20000010
00647f12 call 0x4122f0
00647f17 test al, al
00647f19 jne 0x64804c
00647f1f push dword ptr [ebp - 0x670]
00647f25 lea ecx, [edi + 0x394]
00647f2b call 0x422d00
00647f30 test al, al
00647f32 jne 0x64804c
00647f38 mov ecx, 2
00647f3d call 0x659230
00647f42 test eax, eax
00647f44 je 0x64804c
00647f4a cmp dword ptr [edi + 0x17c], 4
00647f51 jne 0x647f8b
00647f53 mov ecx, dword ptr [ebp - 0x670]
00647f59 lea eax, [ebp - 0xe0c]
00647f5f push 0
00647f61 push 0
00647f63 push 0
00647f65 push 0
00647f67 push 3
00647f69 push eax
00647f6a call 0x412130
00647f6f mov ecx, dword ptr [0xbfd65c]
00647f75 push eax
00647f76 push esi
00647f77 call 0x4023f0
00647f7c mov ecx, eax
00647f7e call 0x7af4b0
00647f83 test al, al
00647f85 je 0x64804c
00647f8b mov ecx, dword ptr [ebp - 0x670]
00647f91 lea eax, [ebp - 0xe14]
00647f97 push eax
00647f98 mov dword ptr [ebp - 0x84c], 0x40a00000
00647fa2 call 0x412130
00647fa7 push eax
00647fa8 lea eax, [edi + 0x2b8]
00647fae push eax
00647faf lea edx, [ebp - 0x84c]
00647fb5 lea ecx, [ebp - 0xe1c]
00647fbb call 0x4120b0
00647fc0 add esp, 4
00647fc3 mov ecx, esi
00647fc5 push eax
00647fc6 lea eax, [ebp - 0xe24]
00647fcc push eax
00647fcd call 0x962a60
00647fd2 mov ecx, eax
00647fd4 call 0x9626f0
00647fd9 fstp dword ptr [ebp - 0x678]
00647fdf call 0x659200
00647fe4 mulss xmm0, dword ptr [0xb6ab30]
00647fec lea ecx, [edi + 0x394]
00647ff2 push dword ptr [ebp - 0x670]
00647ff8 movss dword ptr [ebp - 0x668], xmm0
00648000 fld dword ptr [ebp - 0x668]
00648006 fadd dword ptr [ebp - 0x678]
0064800c fstp dword ptr [ebp - 0x678]
00648012 call 0x422d00
00648017 movss xmm0, dword ptr [ebp - 0x678]
0064801f test al, al
00648021 je 0x64802b
00648023 addss xmm0, dword ptr [0xb6accc]
0064802b movss xmm1, dword ptr [ebp - 0x6a0]
00648033 comiss xmm1, xmm0
00648036 jbe 0x64804c
00648038 mov eax, dword ptr [ebp - 0x670]
0064803e movss dword ptr [ebp - 0x6a0], xmm0
00648046 mov dword ptr [ebp - 0x66c], eax
0064804c inc dword ptr [ebp - 0x674]
00648052 lea ecx, [ebp - 0xafc]
00648058 call 0x4083d0
0064805d mov ecx, dword ptr [ebp - 0x674]
00648063 cmp ecx, eax
00648065 jb 0x647ee0
0064806b push dword ptr [ebp - 0x66c]
00648071 mov ecx, edi
00648073 call 0x681960
00648078 lea ecx, [ebp - 0xafc]
0064807e mov dword ptr [ebp - 4], 0xffffffff
00648085 call 0x412490
0064808a cmp dword ptr [edi + 0x31c], 0
00648091 je 0x648161
00648097 push 0xbc4cb0
0064809c lea edx, [edi + 0x378]
006480a2 lea ecx, [ebp - 0x1784]
006480a8 call 0x412050
006480ad add esp, 4
006480b0 mov ecx, eax
006480b2 call 0x412090
006480b7 test al, al
006480b9 je 0x648161
006480bf mov ecx, dword ptr [edi + 0x31c]
006480c5 lea eax, [ebp - 0xe2c]
006480cb push eax
006480cc call 0x412130
006480d1 push eax
006480d2 lea eax, [ebp - 0xb2c]
006480d8 mov ecx, esi
006480da push eax
006480db call 0x962ac0
006480e0 lea eax, [ebp - 0x850]
006480e6 mov dword ptr [ebp - 0x850], 0x40000000
006480f0 push eax
006480f1 lea eax, [ebp - 0xe34]
006480f7 push eax
006480f8 lea eax, [ebp - 0xe3c]
006480fe push eax
006480ff lea ecx, [ebp - 0xb2c]
00648105 call 0x962560
0064810a push eax
0064810b lea edx, [edi + 0x2f4]
00648111 lea ecx, [ebp - 0xe44]
00648117 call 0x4120b0
0064811c add esp, 4
0064811f mov ecx, eax
00648121 call 0x962b50
00648126 push eax
00648127 lea ecx, [edi + 0x2b8]
0064812d call 0x962af0
00648132 movss xmm1, dword ptr [edi + 0x2f4]
0064813a movss xmm0, dword ptr [edi + 0x36c]
00648142 call 0x65c960
00648147 lea eax, [ebp - 0x9f8]
0064814d movss dword ptr [ebp - 0x9f8], xmm0
00648155 push eax
00648156 lea ecx, [edi + 0x2b8]
0064815c call 0x962bb0
00648161 lea esi, [edi + 0x378]
00648167 push 0xbc4c00
0064816c mov edx, esi
0064816e lea ecx, [ebp - 0x1794]
00648174 call 0x412050
00648179 add esp, 4
0064817c mov ecx, eax
0064817e call 0x412090
00648183 test al, al
00648185 je 0x6483ed
0064818b push 0xbc4ce0
00648190 mov edx, esi
00648192 lea ecx, [ebp - 0x17a4]
00648198 call 0x412050
0064819d add esp, 4
006481a0 mov ecx, eax
006481a2 call 0x427260
006481a7 test al, al
006481a9 je 0x6483ed
006481af push 0xbc48a0
006481b4 mov edx, esi
006481b6 lea ecx, [ebp - 0x17b4]
006481bc call 0x412050
006481c1 add esp, 4
006481c4 mov ecx, eax
006481c6 call 0x427260
006481cb test al, al
006481cd je 0x6483ed
006481d3 mov eax, dword ptr [ebp - 0x698]
006481d9 test eax, eax
006481db je 0x6483ed
006481e1 mov ecx, eax
006481e3 call 0x5ef470
006481e8 movss xmm0, dword ptr [0xc02fec]
006481f0 mov ecx, dword ptr [ebp - 0x698]
006481f6 movss dword ptr [ebp - 0x6fc], xmm0
006481fe movss xmm0, dword ptr [0xc02ff0]
00648206 movss dword ptr [ebp - 0x6f8], xmm0
0064820e call 0x74b4d0
00648213 mov ecx, dword ptr [ebp - 0x698]
00648219 test eax, eax
0064821b je 0x6482a3
00648221 lea eax, [ebp - 0x9f4]
00648227 mov dword ptr [ebp - 0x9f4], 0x41200000
00648231 push eax
00648232 lea eax, [ebp - 0xe4c]
00648238 push eax
00648239 lea eax, [edi + 0x294]
0064823f push eax
00648240 lea eax, [ebp - 0xe54]
00648246 push eax
00648247 lea eax, [ebp - 0xe5c]
0064824d push eax
0064824e call 0x74b4d0
00648253 mov ecx, eax
00648255 call 0x412130
0064825a mov ecx, eax
0064825c call 0x962ac0
00648261 mov ecx, eax
00648263 call 0x962c10
00648268 push eax
00648269 lea ecx, [ebp - 0x6fc]
0064826f call 0x962cd0
00648274 lea ecx, [ebp - 0x6fc]
0064827a call 0x962a00
0064827f fstp dword ptr [ebp - 0x668]
00648285 movss xmm0, dword ptr [ebp - 0x668]
0064828d comiss xmm0, dword ptr [ebp - 0x684]
00648294 jbe 0x6482bb
00648296 lea ecx, [ebp - 0x6fc]
0064829c call 0x9624f0
006482a1 jmp 0x6482bb
006482a3 lea eax, [ebp - 0xe64]
006482a9 push eax
006482aa call 0x5b7720
006482af push eax
006482b0 lea ecx, [ebp - 0x6fc]
006482b6 call 0x962cd0
006482bb mov ecx, dword ptr [ebp - 0x698]
006482c1 call 0x427830
006482c6 mulss xmm0, dword ptr [ebp - 0x688]
006482ce mov ecx, dword ptr [ebp - 0x698]
006482d4 push 8
006482d6 movss dword ptr [ebp - 0x6dc], xmm0
006482de call 0x59ff80
006482e3 test al, al
006482e5 je 0x6482f9
006482e7 movss xmm0, dword ptr [ebp - 0x6dc]
006482ef mulss xmm0, dword ptr [ebp - 0x6cc]
006482f7 jmp 0x648329
006482f9 push 0xbc4920
006482fe mov edx, esi
00648300 lea ecx, [ebp - 0x17c4]
00648306 call 0x412050
0064830b add esp, 4
0064830e mov ecx, eax
00648310 call 0x412090
00648315 test al, al
00648317 je 0x648331
00648319 movss xmm0, dword ptr [ebp - 0x6dc]
00648321 mulss xmm0, dword ptr [ebp - 0x68c]
00648329 movss dword ptr [ebp - 0x6dc], xmm0
00648331 movss xmm0, dword ptr [ebp - 0x6fc]
00648339 movss xmm1, dword ptr [ebp - 0x67c]
00648341 ucomiss xmm0, xmm1
00648344 lahf 
00648345 test ah, 0x44
00648348 jp 0x6483b3
0064834a movss xmm0, dword ptr [ebp - 0x6f8]
00648352 ucomiss xmm0, xmm1
00648355 lahf 
00648356 test ah, 0x44
00648359 jp 0x6483b3
0064835b push 0xbc4920
00648360 mov edx, esi
00648362 lea ecx, [ebp - 0x17d4]
00648368 call 0x412050
0064836d add esp, 4
00648370 mov ecx, eax
00648372 call 0x412090
00648377 test al, al
00648379 je 0x648387
0064837b mov dword ptr [edi + 0x2c4], 0x3f800000
00648385 jmp 0x6483ed
00648387 push 0xbc4cb0
0064838c mov edx, esi
0064838e lea ecx, [ebp - 0x17e4]
00648394 call 0x412050
00648399 add esp, 4
0064839c mov ecx, eax
0064839e call 0x412090
006483a3 test al, al
006483a5 je 0x6483e3
006483a7 mov dword ptr [edi + 0x2c4], 0x3f666666
006483b1 jmp 0x6483ed
006483b3 lea ecx, [ebp - 0x6fc]
006483b9 call 0x9624f0
006483be lea eax, [ebp - 0x6dc]
006483c4 push eax
006483c5 lea eax, [ebp - 0xe6c]
006483cb push eax
006483cc lea ecx, [ebp - 0x6fc]
006483d2 call 0x962b50
006483d7 push eax
006483d8 lea ecx, [edi + 0x2b8]
006483de call 0x962a90
006483e3 mov dword ptr [edi + 0x2c4], 0x3f4ccccd
006483ed push 0xbc4bc0
006483f2 mov edx, esi
006483f4 lea ecx, [ebp - 0x17f4]
006483fa call 0x412050
006483ff add esp, 4
00648402 mov ecx, eax
00648404 call 0x412090
00648409 test al, al
0064840b je 0x648504
00648411 push 0xbc4ce0
00648416 mov edx, esi
00648418 lea ecx, [ebp - 0x1804]
0064841e call 0x412050
00648423 add esp, 4
00648426 mov ecx, eax
00648428 call 0x412090
0064842d test al, al
0064842f je 0x6484b4
00648435 mov ecx, edi
00648437 call 0x6520e0
0064843c lea esi, [edi + 0x294]
00648442 test al, al
00648444 je 0x64850a
0064844a mov ecx, dword ptr [edi + 0x314]
00648450 lea eax, [ebp - 0xe74]
00648456 push esi
00648457 push eax
00648458 call 0x412130
0064845d mov ecx, eax
0064845f call 0x9626f0
00648464 movss xmm1, dword ptr [0xb6acb4]
0064846c movss xmm0, dword ptr [ebp - 0x684]
00648474 fstp dword ptr [ebp - 0x668]
0064847a movss xmm2, dword ptr [ebp - 0x668]
00648482 call 0x9623e0
00648487 divss xmm0, dword ptr [0xb6acb4]
0064848f addss xmm0, dword ptr [ebp - 0x684]
00648497 movaps xmm1, xmm0
0064849a movss dword ptr [ebp - 0x6b4], xmm0
006484a2 mulss xmm1, dword ptr [edi + 0x3a4]
006484aa movss dword ptr [edi + 0x2e0], xmm1
006484b2 jmp 0x64850a
006484b4 cmp dword ptr [edi + 0x388], 0
006484bb jg 0x648504
006484bd lea ecx, [edi + 0x73c]
006484c3 call 0x962a00
006484c8 fmul dword ptr [0xb6a21c]
006484ce fstp dword ptr [ebp - 0x668]
006484d4 movss xmm0, dword ptr [ebp - 0x668]
006484dc addss xmm0, dword ptr [edi + 0x2e0]
006484e4 movss dword ptr [edi + 0x2e0], xmm0
006484ec movss xmm0, dword ptr [edi + 0x374]
006484f4 addss xmm0, dword ptr [0xb6a214]
006484fc movss dword ptr [edi + 0x374], xmm0
00648504 lea esi, [edi + 0x294]
0064850a push 0xbc4c60
0064850f lea edx, [edi + 0x378]
00648515 lea ecx, [ebp - 0x1814]
0064851b call 0x412050
00648520 add esp, 4
00648523 mov ecx, eax
00648525 call 0x412090
0064852a test al, al
0064852c je 0x648704
00648532 push 0xbc4ce0
00648537 lea edx, [edi + 0x378]
0064853d lea ecx, [ebp - 0x1824]
00648543 call 0x412050
00648548 add esp, 4
0064854b mov ecx, eax
0064854d call 0x412090
00648552 test al, al
00648554 je 0x6485e2
0064855a mov ecx, edi
0064855c call 0x6520e0
00648561 test al, al
00648563 je 0x648704
00648569 mov ecx, dword ptr [edi + 0x314]
0064856f lea eax, [ebp - 0xe7c]
00648575 push esi
00648576 push eax
00648577 call 0x412130
0064857c mov ecx, eax
0064857e call 0x9626f0
00648583 movss xmm1, dword ptr [0xb6acc4]
0064858b movss xmm0, dword ptr [ebp - 0x67c]
00648593 fstp dword ptr [ebp - 0x668]
00648599 movss xmm2, dword ptr [ebp - 0x668]
006485a1 call 0x9623e0
006485a6 divss xmm0, dword ptr [0xb6acc4]
006485ae movss xmm1, dword ptr [ebp - 0x684]
006485b6 subss xmm1, xmm0
006485ba movaps xmm0, xmm1
006485bd mulss xmm1, dword ptr [edi + 0x3a4]
006485c5 mulss xmm0, dword ptr [ebp - 0x6b4]
006485cd movss dword ptr [edi + 0x2e0], xmm1
006485d5 movss dword ptr [ebp - 0x6b4], xmm0
006485dd jmp 0x648704
006485e2 cmp dword ptr [edi + 0x388], 0
006485e9 jg 0x648704
006485ef movss xmm0, dword ptr [edi + 0x2fc]
006485f7 comiss xmm0, dword ptr [0xb6a8cc]
006485fe jbe 0x648704
00648604 push 0xbc48a0
00648609 lea edx, [edi + 0x378]
0064860f lea ecx, [ebp - 0x1834]
00648615 call 0x412050
0064861a add esp, 4
0064861d mov ecx, eax
0064861f call 0x412090
00648624 movss xmm2, dword ptr [edi + 0x3a4]
0064862c movss xmm0, dword ptr [edi + 0x2e0]
00648634 movaps xmm1, xmm2
00648637 divss xmm1, dword ptr [ebp - 0x688]
0064863f test al, al
00648641 je 0x648682
00648643 comiss xmm1, xmm0
00648646 jb 0x648652
00648648 movss xmm1, dword ptr [0xb6a200]
00648650 jmp 0x64865a
00648652 movss xmm1, dword ptr [0xb6a238]
0064865a mulss xmm1, xmm2
0064865e lea edx, [ebp - 0x9f0]
00648664 mov dword ptr [ebp - 0x9ec], 0x3dcccccd
0064866e lea ecx, [ebp - 0x9ec]
00648674 subss xmm0, xmm1
00648678 movss dword ptr [ebp - 0x9f0], xmm0
00648680 jmp 0x6486bf
00648682 comiss xmm1, xmm0
00648685 jb 0x648691
00648687 movss xmm1, dword ptr [0xb6a248]
0064868f jmp 0x648699
00648691 movss xmm1, dword ptr [0xb6a2ac]
00648699 mulss xmm1, xmm2
0064869d lea edx, [ebp - 0x9e8]
006486a3 mov dword ptr [ebp - 0x9e4], 0x3dcccccd
006486ad lea ecx, [ebp - 0x9e4]
006486b3 subss xmm0, xmm1
006486b7 movss dword ptr [ebp - 0x9e8], xmm0
006486bf call 0x417c70
006486c4 movss xmm0, dword ptr [eax]
006486c8 movss dword ptr [edi + 0x2e0], xmm0
006486d0 divss xmm0, dword ptr [edi + 0x3a4]
006486d8 call 0x4228f0
006486dd movss dword ptr [ebp - 0x6b4], xmm0
006486e5 movss xmm0, dword ptr [0xb6a2cc]
006486ed comiss xmm0, dword ptr [edi + 0x2e0]
006486f4 jb 0x648704
006486f6 mov byte ptr [edi + 0x16b], 1
006486fd or dword ptr [edi + 0x3c4], 0x10
00648704 push 0xbc4cc0
00648709 lea edx, [edi + 0x378]
0064870f lea ecx, [ebp - 0x1844]
00648715 call 0x412050
0064871a add esp, 4
0064871d mov ecx, eax
0064871f call 0x412090
00648724 test al, al
00648726 je 0x6487a9
0064872c mov eax, dword ptr [edi + 0x2c]
0064872f cmp eax, 4
00648732 je 0x64873d
00648734 cmp eax, 9
00648737 je 0x64873d
00648739 xor eax, eax
0064873b jmp 0x648742
0064873d mov eax, 3
00648742 push 0xbc4ce0
00648747 lea edx, [edi + 0x378]
0064874d mov dword ptr [edi + 0x17c], eax
00648753 lea ecx, [ebp - 0x1854]
00648759 call 0x412050
0064875e add esp, 4
00648761 mov ecx, eax
00648763 call 0x427260
00648768 test al, al
0064876a je 0x6487a9
0064876c cmp byte ptr [edi + 0x3bb], 0
00648773 jne 0x648793
00648775 push esi
00648776 mov ecx, edi
00648778 call 0x656f30
0064877d test al, al
0064877f je 0x6487a9
00648781 push 0
00648783 mov ecx, edi
00648785 call 0x650dd0
0064878a mov byte ptr [edi + 0x3bb], 1
00648791 jmp 0x6487a9
00648793 mov ecx, 8
00648798 call 0x659230
0064879d test eax, eax
0064879f jne 0x6487a9
006487a1 push esi
006487a2 mov ecx, edi
006487a4 call 0x656f30
006487a9 push 0xbc4920
006487ae lea edx, [edi + 0x378]
006487b4 lea ecx, [ebp - 0x1864]
006487ba call 0x412050
006487bf add esp, 4
006487c2 mov ecx, eax
006487c4 call 0x412090
006487c9 test al, al
006487cb je 0x64899a
006487d1 cmp dword ptr [edi + 0x314], 0
006487d8 je 0x64899a
006487de push 0xbc47f0
006487e3 push 0xbc4bf0
006487e8 mov edx, 0xbc4ce0
006487ed lea ecx, [ebp - 0x1874]
006487f3 call 0x427220
006487f8 add esp, 4
006487fb lea ecx, [ebp - 0x1884]
00648801 mov edx, eax
00648803 call 0x427220
00648808 push eax
00648809 lea edx, [edi + 0x378]
0064880f lea ecx, [ebp - 0x1894]
00648815 call 0x412050
0064881a add esp, 8
0064881d mov ecx, eax
0064881f call 0x427260
00648824 test al, al
00648826 je 0x64899a
0064882c movss xmm2, dword ptr [0xb6a7b0]
00648834 lea ecx, [ebp - 0xe84]
0064883a movss xmm1, dword ptr [ebp - 0x67c]
00648842 call 0x9624e0
00648847 mov ecx, dword ptr [edi + 0x314]
0064884d push eax
0064884e lea eax, [ebp - 0xe8c]
00648854 push eax
00648855 lea eax, [ebp - 0xe94]
0064885b push eax
0064885c call 0x412130
00648861 mov ecx, eax
00648863 call 0x962a60
00648868 push eax
00648869 lea eax, [ebp - 0xa44]
0064886f mov ecx, esi
00648871 push eax
00648872 call 0x962ac0
00648877 lea ecx, [edi + 0x28c]
0064887d push 0xc02fec
00648882 call 0x962ca0
00648887 test al, al
00648889 je 0x6488d4
0064888b movss xmm2, dword ptr [0xb6a7b0]
00648893 lea ecx, [ebp - 0xe9c]
00648899 movss xmm1, dword ptr [ebp - 0x67c]
006488a1 call 0x9624e0
006488a6 push eax
006488a7 lea eax, [ebp - 0xea4]
006488ad push eax
006488ae lea ecx, [edi + 0x28c]
006488b4 call 0x962ac0
006488b9 push eax
006488ba lea eax, [ebp - 0xeac]
006488c0 mov ecx, esi
006488c2 push eax
006488c3 call 0x962ac0
006488c8 push eax
006488c9 lea ecx, [ebp - 0xa44]
006488cf call 0x962cd0
006488d4 mov ecx, edi
006488d6 call 0x6414a0
006488db movss xmm0, dword ptr [edi + 0x770]
006488e3 lea edx, [ebp - 0x9e0]
006488e9 subss xmm0, dword ptr [0xb6aa8c]
006488f1 lea ecx, [ebp - 0x9dc]
006488f7 mov dword ptr [ebp - 0x668], eax
006488fd mov dword ptr [ebp - 0x9dc], 0x41a00000
00648907 mulss xmm0, dword ptr [ebp - 0x68c]
0064890f movss dword ptr [ebp - 0x9e0], xmm0
00648917 call 0x417c70
0064891c movss xmm1, dword ptr [eax]
00648920 mov eax, dword ptr [ebp - 0x668]
00648926 movss dword ptr [ebp - 0x678], xmm1
0064892e test eax, eax
00648930 je 0x648943
00648932 mov ecx, eax
00648934 call 0x427830
00648939 movss xmm1, dword ptr [ebp - 0x678]
00648941 jmp 0x64894b
00648943 movss xmm0, dword ptr [ebp - 0x684]
0064894b mulss xmm0, dword ptr [0xb6a974]
00648953 addss xmm1, xmm1
00648957 lea eax, [ebp - 0x9d8]
0064895d push eax
0064895e lea eax, [ebp - 0xeb4]
00648964 mulss xmm0, xmm0
00648968 lea ecx, [ebp - 0xa44]
0064896e push eax
0064896f lea eax, [ebp - 0xebc]
00648975 push eax
00648976 divss xmm0, xmm1
0064897a movss dword ptr [ebp - 0x9d8], xmm0
00648982 call 0x962560
00648987 mov ecx, eax
00648989 call 0x962b50
0064898e push eax
0064898f lea ecx, [edi + 0x2b8]
00648995 call 0x962af0
0064899a push 0xbc4930
0064899f lea edx, [edi + 0x378]
006489a5 lea ecx, [ebp - 0x18a4]
006489ab call 0x412050
006489b0 add esp, 4
006489b3 mov ecx, eax
006489b5 call 0x412090
006489ba test al, al
006489bc je 0x648a09
006489be mov eax, dword ptr [ebp - 0x698]
006489c4 test eax, eax
006489c6 je 0x6489fa
006489c8 push 0xa
006489ca mov ecx, eax
006489cc call 0x7866b0
006489d1 lea edx, [ebp - 0x9d4]
006489d7 movss dword ptr [ebp - 0x9d4], xmm0
006489df lea ecx, [ebp - 0x9d0]
006489e5 mov dword ptr [ebp - 0x9d0], 0x3f800000
006489ef call 0x417c70
006489f4 movss xmm1, dword ptr [eax]
006489f8 jmp 0x648a02
006489fa movss xmm1, dword ptr [ebp - 0x684]
00648a02 mov ecx, edi
00648a04 call 0x6421f0
00648a09 push 0xbc4960
00648a0e lea edx, [edi + 0x378]
00648a14 lea ecx, [ebp - 0x18b4]
00648a1a call 0x412050
00648a1f add esp, 4
00648a22 mov ecx, eax
00648a24 call 0x412090
00648a29 test al, al
00648a2b je 0x648a78
00648a2d mov eax, dword ptr [ebp - 0x698]
00648a33 test eax, eax
00648a35 je 0x648a69
00648a37 push 0x1a
00648a39 mov ecx, eax
00648a3b call 0x7866b0
00648a40 lea edx, [ebp - 0x9cc]
00648a46 movss dword ptr [ebp - 0x9cc], xmm0
00648a4e lea ecx, [ebp - 0x9c8]
00648a54 mov dword ptr [ebp - 0x9c8], 0x3f800000
00648a5e call 0x417c70
00648a63 movss xmm1, dword ptr [eax]
00648a67 jmp 0x648a71
00648a69 movss xmm1, dword ptr [ebp - 0x684]
00648a71 mov ecx, edi
00648a73 call 0x642330
00648a78 push 0xbc4a20
00648a7d lea edx, [edi + 0x378]
00648a83 lea ecx, [ebp - 0x18c4]
00648a89 call 0x412050
00648a8e add esp, 4
00648a91 mov ecx, eax
00648a93 call 0x412090
00648a98 test al, al
00648a9a je 0x648ae7
00648a9c mov eax, dword ptr [ebp - 0x698]
00648aa2 test eax, eax
00648aa4 je 0x648ad8
00648aa6 push 0x2e
00648aa8 mov ecx, eax
00648aaa call 0x7866b0
00648aaf lea edx, [ebp - 0x9c4]
00648ab5 movss dword ptr [ebp - 0x9c4], xmm0
00648abd lea ecx, [ebp - 0x9c0]
00648ac3 mov dword ptr [ebp - 0x9c0], 0x3f800000
00648acd call 0x417c70
00648ad2 movss xmm1, dword ptr [eax]
00648ad6 jmp 0x648ae0
00648ad8 movss xmm1, dword ptr [ebp - 0x684]
00648ae0 mov ecx, edi
00648ae2 call 0x6424d0
00648ae7 push 0xbc4b80
00648aec lea edx, [edi + 0x378]
00648af2 lea ecx, [ebp - 0x18d4]
00648af8 call 0x412050
00648afd add esp, 4
00648b00 mov ecx, eax
00648b02 call 0x412090
00648b07 test al, al
00648b09 je 0x648bd1
00648b0f movss xmm2, dword ptr [edi + 0x2fc]
00648b17 subss xmm2, dword ptr [0xb6a974]
00648b1f movss xmm1, dword ptr [ebp - 0x684]
00648b27 movss xmm0, dword ptr [ebp - 0x67c]
00648b2f divss xmm2, dword ptr [0xb6a974]
00648b37 call 0x9623e0
00648b3c mov eax, dword ptr [edi + 0x3c8]
00648b42 movaps xmm1, xmm0
00648b45 mulss xmm1, dword ptr [0xb6a9c8]
00648b4d mulss xmm1, xmm0
00648b51 movss dword ptr [ebp - 0x678], xmm1
00648b59 test eax, eax
00648b5b je 0x648b6d
00648b5d movss xmm0, dword ptr [0xb6a940]
00648b65 movss dword ptr [ebp - 0x678], xmm0
00648b6d mov dword ptr [0xbfedec], eax
00648b72 lea edx, [ebp - 0x9bc]
00648b78 lea eax, [edi + 0x2b8]
00648b7e mov dword ptr [ebp - 0x9bc], 0x40800000
00648b88 push 0x6416b0
00648b8d push eax
00648b8e lea ecx, [ebp - 0xec4]
00648b94 call 0x4120b0
00648b99 add esp, 4
00648b9c mov ecx, esi
00648b9e push eax
00648b9f lea eax, [ebp - 0xecc]
00648ba5 push eax
00648ba6 call 0x962a60
00648bab movss xmm3, dword ptr [0xb6abec]
00648bb3 movss xmm2, dword ptr [ebp - 0x678]
00648bbb mov ecx, dword ptr [0xbfd65c]
00648bc1 push eax
00648bc2 call 0x6d7c90
00648bc7 mov dword ptr [0xbfedec], 0
00648bd1 lea esi, [edi + 0x378]
00648bd7 push 0xbc49f0
00648bdc mov edx, esi
00648bde lea ecx, [ebp - 0x18e4]
00648be4 call 0x412050
00648be9 add esp, 4
00648bec mov ecx, eax
00648bee call 0x412090
00648bf3 test al, al
00648bf5 je 0x648d1d
00648bfb mov eax, dword ptr [ebp - 0x698]
00648c01 test eax, eax
00648c03 je 0x648c37
00648c05 push 0x19
00648c07 mov ecx, eax
00648c09 call 0x7866b0
00648c0e lea edx, [ebp - 0x9b8]
00648c14 movss dword ptr [ebp - 0x9b8], xmm0
00648c1c lea ecx, [ebp - 0x9b4]
00648c22 mov dword ptr [ebp - 0x9b4], 0x3f800000
00648c2c call 0x417c70
00648c31 movss xmm0, dword ptr [eax]
00648c35 jmp 0x648c3f
00648c37 movss xmm0, dword ptr [ebp - 0x684]
00648c3f mulss xmm0, dword ptr [ebp - 0x6b8]
00648c47 lea ecx, [ebp - 0x18f4]
00648c4d push 0xbc4ce0
00648c52 mov edx, esi
00648c54 movss dword ptr [ebp - 0x678], xmm0
00648c5c call 0x412050
00648c61 add esp, 4
00648c64 mov ecx, eax
00648c66 call 0x412090
00648c6b test al, al
00648c6d je 0x648cd4
00648c6f mov ecx, dword ptr [edi + 0x314]
00648c75 test ecx, ecx
00648c77 je 0x648d1d
00648c7d call 0x412100
00648c82 cmp eax, 1
00648c85 jne 0x648d1d
00648c8b mov ecx, edi
00648c8d call 0x682200
00648c92 movd xmm0, eax
00648c96 cvtdq2ps xmm0, xmm0
00648c99 mulss xmm0, dword ptr [0xb6a350]
00648ca1 call 0x412040
00648ca6 addss xmm0, dword ptr [0xb6a350]
00648cae movss xmm2, dword ptr [ebp - 0x6b4]
00648cb6 mulss xmm0, dword ptr [ebp - 0x678]
00648cbe addss xmm0, dword ptr [0xb6a64c]
00648cc6 mulss xmm2, xmm0
00648cca movss dword ptr [ebp - 0x6b4], xmm2
00648cd2 jmp 0x648d25
00648cd4 mov ecx, edi
00648cd6 call 0x682200
00648cdb movd xmm0, eax
00648cdf cvtdq2ps xmm0, xmm0
00648ce2 mulss xmm0, dword ptr [0xb6a50c]
00648cea call 0x412040
00648cef addss xmm0, dword ptr [0xb6a50c]
00648cf7 movss xmm2, dword ptr [ebp - 0x6b4]
00648cff mulss xmm0, dword ptr [ebp - 0x678]
00648d07 addss xmm0, dword ptr [ebp - 0x6c4]
00648d0f mulss xmm2, xmm0
00648d13 movss dword ptr [ebp - 0x6b4], xmm2
00648d1b jmp 0x648d25
00648d1d movss xmm2, dword ptr [ebp - 0x6b4]
00648d25 push 0xbc4950
00648d2a mov edx, esi
00648d2c movss dword ptr [ebp - 0x694], xmm2
00648d34 lea ecx, [ebp - 0x1904]
00648d3a call 0x412050
00648d3f add esp, 4
00648d42 mov ecx, eax
00648d44 call 0x412090
00648d49 test al, al
00648d4b jne 0x648d6d
00648d4d push 0xbc4830
00648d52 mov edx, esi
00648d54 lea ecx, [ebp - 0x1914]
00648d5a call 0x412050
00648d5f add esp, 4
00648d62 mov ecx, eax
00648d64 call 0x412090
00648d69 test al, al
00648d6b je 0x648db3
00648d6d cmp dword ptr [edi + 0x3c8], 0
00648d74 je 0x648db3
00648d76 mov eax, dword ptr [edi + 0x3d4]
00648d7c test eax, eax
00648d7e jle 0x648db3
00648d80 movd xmm0, eax
00648d84 cvtdq2ps xmm0, xmm0
00648d87 movss xmm1, dword ptr [ebp - 0x684]
00648d8f divss xmm0, dword ptr [0xb6aa8c]
00648d97 subss xmm1, xmm0
00648d9b movss xmm0, dword ptr [ebp - 0x6b4]
00648da3 addss xmm1, xmm1
00648da7 addss xmm0, xmm1
00648dab movss dword ptr [ebp - 0x6b4], xmm0
00648db3 lea eax, [edi + 0x3c]
00648db6 push ecx
00648db7 mov ecx, eax
00648db9 mov dword ptr [ebp - 0x69c], eax
00648dbf mov dword ptr [esp], 0
00648dc6 call 0x430cc0
00648dcb lea eax, [edi + 0x510]
00648dd1 mov byte ptr [ebp - 0x68e], 0
00648dd8 mov ecx, eax
00648dda mov dword ptr [ebp - 0x668], eax
00648de0 call 0x5b73d0
00648de5 test al, al
00648de7 je 0x648e04
00648de9 push 0x1000
00648dee lea ecx, [edi + 0x510]
00648df4 call 0x62f0b0
00648df9 mov byte ptr [ebp - 0x68d], 1
00648e00 test al, al
00648e02 jne 0x648e0b
00648e04 mov byte ptr [ebp - 0x68d], 0
00648e0b push 0xbc4a10
00648e10 mov edx, esi
00648e12 lea ecx, [ebp - 0x1924]
00648e18 call 0x412050
00648e1d add esp, 4
00648e20 mov ecx, eax
00648e22 call 0x412090
00648e27 test al, al
00648e29 je 0x648edc
00648e2f mov eax, dword ptr [edi + 0x2c]
00648e32 cmp eax, 4
00648e35 je 0x648edc
00648e3b mov ecx, dword ptr [ebp - 0x698]
00648e41 test ecx, ecx
00648e43 je 0x648e80
00648e45 push 0x1b
00648e47 call 0x7866b0
00648e4c lea edx, [ebp - 0x9b0]
00648e52 movss dword ptr [ebp - 0x9b0], xmm0
00648e5a lea ecx, [ebp - 0x9ac]
00648e60 mov dword ptr [ebp - 0x9ac], 0x3f800000
00648e6a call 0x417c70
00648e6f movss xmm1, dword ptr [ebp - 0x684]
00648e77 movss xmm0, dword ptr [eax]
00648e7b mov eax, dword ptr [edi + 0x2c]
00648e7e jmp 0x648e8b
00648e80 movss xmm1, dword ptr [ebp - 0x684]
00648e88 movaps xmm0, xmm1
00648e8b mulss xmm0, dword ptr [ebp - 0x68c]
00648e93 addss xmm0, xmm1
00648e97 cmp eax, 0x32
00648e9a jne 0x648ebb
00648e9c movaps xmm2, xmm1
00648e9f lea ecx, [ebp - 0xed4]
00648ea5 movaps xmm1, xmm0
00648ea8 call 0x9624e0
00648ead push eax
00648eae lea ecx, [edi + 0x2cc]
00648eb4 call 0x962cd0
00648eb9 jmp 0x648edc
00648ebb movaps xmm2, xmm0
00648ebe lea ecx, [ebp - 0xedc]
00648ec4 call 0x9624e0
00648ec9 push eax
00648eca lea ecx, [edi + 0x2cc]
00648ed0 call 0x962cd0
00648ed5 mov byte ptr [ebp - 0x68e], 1
00648edc mov eax, dword ptr [edi + 0x2c]
00648edf cmp eax, 0xd
00648ee2 je 0x648ee9
00648ee4 cmp eax, 0x17
00648ee7 jne 0x648f04
00648ee9 mov ecx, dword ptr [0xbfd65c]
00648eef push 0x4f
00648ef1 call 0x641630
00648ef6 test al, al
00648ef8 je 0x648f04
00648efa mov dword ptr [edi + 0x2cc], 0x40400000
00648f04 mov eax, dword ptr [edi + 0x2c]
00648f07 cmp eax, 0xe
00648f0a je 0x648f11
00648f0c cmp eax, 0xf
00648f0f jne 0x648f5b
00648f11 push 0xbc4920
00648f16 mov edx, esi
00648f18 lea ecx, [ebp - 0x1934]
00648f1e call 0x412050
00648f23 add esp, 4
00648f26 mov ecx, eax
00648f28 call 0x412090
00648f2d test al, al
00648f2f je 0x648f58
00648f31 movss xmm0, dword ptr [edi + 0x2fc]
00648f39 mulss xmm0, dword ptr [0xb6aa4c]
00648f41 push ecx
00648f42 lea ecx, [edi + 0x3c]
00648f45 movss dword ptr [esp], xmm0
00648f4a call 0x430cc0
00648f4f mov byte ptr [ebp - 0x68e], 0
00648f56 jmp 0x648fb7
00648f58 mov eax, dword ptr [edi + 0x2c]
00648f5b cmp eax, 0xb
00648f5e je 0x648fb0
00648f60 cmp eax, 0xc
00648f63 je 0x648fb0
00648f65 cmp eax, 0xd
00648f68 je 0x648fb0
00648f6a cmp eax, 0xe
00648f6d je 0x648fb0
00648f6f cmp eax, 0xf
00648f72 je 0x648fb0
00648f74 cmp eax, 0x17
00648f77 je 0x648fb0
00648f79 cmp eax, 0x1f
00648f7c je 0x648fb0
00648f7e cmp eax, 0x21
00648f81 je 0x648fb0
00648f83 cmp eax, 0x22
00648f86 je 0x648fb0
00648f88 cmp eax, 0x14
00648f8b je 0x648fb0
00648f8d cmp eax, 0x27
00648f90 je 0x648fb0
00648f92 cmp eax, 0x29
00648f95 je 0x648fb0
00648f97 cmp eax, 0x2b
00648f9a je 0x648fb0
00648f9c cmp eax, 0x2c
00648f9f je 0x648fb0
00648fa1 cmp eax, 0x2d
00648fa4 je 0x648fb0
00648fa6 cmp eax, 0x2f
00648fa9 je 0x648fb0
00648fab cmp eax, 0x31
00648fae jne 0x648fb7
00648fb0 mov byte ptr [ebp - 0x68e], 1
00648fb7 cmp dword ptr [edi + 0x2c], 0x32
00648fbb jne 0x64907e
00648fc1 lea ecx, [edi + 0x2b8]
00648fc7 call 0x962a00
00648fcc movss xmm0, dword ptr [ebp - 0x67c]
00648fd4 fadd st(0), st(0)
00648fd6 comiss xmm0, dword ptr [edi + 0x2b8]
00648fdd fstp dword ptr [ebp - 0x678]
00648fe3 movss xmm0, dword ptr [ebp - 0x678]
00648feb jbe 0x648ff5
00648fed mulss xmm0, dword ptr [0xb6ae44]
00648ff5 lea ecx, [edi + 0x3c]
00648ff8 movss dword ptr [ebp - 0x678], xmm0
00649000 call 0x419b40
00649005 mov ecx, eax
00649007 call 0x432ec0
0064900c movss xmm1, dword ptr [0xb6ac40]
00649014 lea ecx, [edi + 0x3c]
00649017 movd xmm0, eax
0064901b cvtdq2ps xmm0, xmm0
0064901e divss xmm1, xmm0
00649022 movss dword ptr [ebp - 0x6a0], xmm1
0064902a call 0x405930
0064902f movss xmm1, dword ptr [ebp - 0x678]
00649037 mulss xmm0, dword ptr [ebp - 0x6a0]
0064903f mulss xmm1, dword ptr [edi + 0x2f4]
00649047 addss xmm0, xmm1
0064904b call 0x65a640
00649050 movss xmm1, dword ptr [ebp - 0x67c]
00649058 comiss xmm1, xmm0
0064905b jbe 0x649065
0064905d addss xmm0, dword ptr [0xb6ac40]
00649065 divss xmm0, dword ptr [ebp - 0x6a0]
0064906d lea ecx, [edi + 0x3c]
00649070 movaps xmm1, xmm0
00649073 call 0x4058b0
00649078 lea esi, [edi + 0x378]
0064907e cmp byte ptr [ebp - 0x68e], 0
00649085 movss xmm1, dword ptr [0xb6a1c8]
0064908d jne 0x64909c
0064908f cmp byte ptr [ebp - 0x68d], 0
00649096 je 0x64938c
0064909c mov eax, dword ptr [edi + 0x2b8]
006490a2 mov ecx, dword ptr [edi + 0x2bc]
006490a8 mov dword ptr [ebp - 0x780], eax
006490ae mov dword ptr [ebp - 0x77c], ecx
006490b4 cmp dword ptr [edi + 0x388], 0
006490bb jle 0x6490d1
006490bd lea eax, [edi + 0x38c]
006490c3 push eax
006490c4 lea ecx, [ebp - 0x780]
006490ca call 0x962cd0
006490cf jmp 0x649145
006490d1 movss xmm0, dword ptr [edi + 0x368]
006490d9 comiss xmm0, xmm1
006490dc ja 0x64911e
006490de push 0xbc4ce0
006490e3 mov edx, esi
006490e5 lea ecx, [ebp - 0x1944]
006490eb call 0x412050
006490f0 add esp, 4
006490f3 mov ecx, eax
006490f5 call 0x412090
006490fa test al, al
006490fc je 0x649145
006490fe push 0xbc46c0
00649103 mov edx, esi
00649105 lea ecx, [ebp - 0x1954]
0064910b call 0x412050
00649110 add esp, 4
00649113 mov ecx, eax
00649115 call 0x412090
0064911a test al, al
0064911c je 0x649145
0064911e movss xmm2, dword ptr [ebp - 0x6b0]
00649126 lea ecx, [ebp - 0xee4]
0064912c movss xmm1, dword ptr [ebp - 0x67c]
00649134 call 0x9624e0
00649139 push eax
0064913a lea ecx, [ebp - 0x780]
00649140 call 0x962a90
00649145 lea ecx, [ebp - 0x780]
0064914b call 0x962830
00649150 cmp byte ptr [ebp - 0x68e], 0
00649157 fstp dword ptr [ebp - 0x674]
0064915d je 0x649175
0064915f movss xmm0, dword ptr [ebp - 0x674]
00649167 push ecx
00649168 lea ecx, [edi + 0x3c]
0064916b movss dword ptr [esp], xmm0
00649170 call 0x430cc0
00649175 cmp byte ptr [ebp - 0x68d], 0
0064917c je 0x6491c8
0064917e lea ecx, [edi + 0x510]
00649184 xor esi, esi
00649186 call 0x432ed0
0064918b test eax, eax
0064918d je 0x6491c8
0064918f mov edi, dword ptr [ebp - 0x668]
00649195 push esi
00649196 mov ecx, edi
00649198 call 0x4062c0
0064919d test dword ptr [eax + 0x88], 0x1000
006491a7 je 0x6491b6
006491a9 movss xmm0, dword ptr [ebp - 0x674]
006491b1 movss dword ptr [eax + 0x3c], xmm0
006491b6 mov ecx, edi
006491b8 inc esi
006491b9 call 0x432ed0
006491be cmp esi, eax
006491c0 jb 0x649195
006491c2 mov edi, dword ptr [ebp - 0x6a8]
006491c8 cmp dword ptr [edi + 0x2c], 0x17
006491cc jne 0x64938c
006491d2 mov ecx, dword ptr [0xbfd65c]
006491d8 push 0x4f
006491da call 0x427910
006491df mov ecx, eax
006491e1 call 0x4480b0
006491e6 test al, al
006491e8 je 0x64938c
006491ee movss xmm2, dword ptr [ebp - 0x67c]
006491f6 mov ecx, edi
006491f8 movss xmm1, dword ptr [0xb6a7b0]
00649200 call 0x6847e0
00649205 test eax, eax
00649207 je 0x64938c
0064920d cmp byte ptr [edi + 0x169], 0
00649214 je 0x64938c
0064921a mov dword ptr [ebp - 0x9a8], 0x3e0f5c29
00649224 mov dword ptr [ebp - 0x9a4], 0x40a00000
0064922e call 0x6c3d90
00649233 push eax
00649234 push 0
00649236 push 0
00649238 lea eax, [ebp - 0x9a8]
0064923e push eax
0064923f lea eax, [ebp - 0xeec]
00649245 push eax
00649246 lea ecx, [edi + 0x2b8]
0064924c lea esi, [edi + 0x370]
00649252 call 0x962b50
00649257 movss xmm0, dword ptr [ebp - 0x674]
0064925f push eax
00649260 push esi
00649261 lea eax, [ebp - 0xef4]
00649267 push eax
00649268 push ecx
00649269 lea eax, [ebp - 0xefc]
0064926f movss dword ptr [esp], xmm0
00649274 push eax
00649275 call 0x9627f0
0064927a push eax
0064927b lea edx, [ebp - 0x9a4]
00649281 lea ecx, [ebp - 0xf04]
00649287 call 0x4120b0
0064928c add esp, 0xc
0064928f mov ecx, eax
00649291 call 0x962b50
00649296 push eax
00649297 lea eax, [ebp - 0xf0c]
0064929d push eax
0064929e lea ecx, [edi + 0x294]
006492a4 call 0x962ac0
006492a9 mov ecx, dword ptr [0xbfd65c]
006492af push eax
006492b0 push 0x3b
006492b2 push 0x3e8
006492b7 call 0x422e20
006492bc movss xmm0, dword ptr [ebp - 0x684]
006492c4 mov edi, eax
006492c6 push 1
006492c8 push 0
006492ca push 0xff
006492cf mov esi, dword ptr [edi]
006492d1 movaps xmm3, xmm0
006492d4 push -1
006492d6 push ecx
006492d7 movaps xmm2, xmm0
006492da mov dword ptr [esp], 0x3e99999a
006492e1 movaps xmm1, xmm0
006492e4 lea ecx, [ebp - 0x5e0]
006492ea call 0x4325d0
006492ef push eax
006492f0 mov eax, dword ptr [esi + 0x38]
006492f3 mov ecx, edi
006492f5 call eax
006492f7 call 0x659200
006492fc mulss xmm0, dword ptr [0xb6a974]
00649304 push ecx
00649305 mov ecx, edi
00649307 addss xmm0, dword ptr [0xb6a7b0]
0064930f movss dword ptr [esp], xmm0
00649314 call 0x427510
00649319 mov ecx, 0xf
0064931e call 0x659230
00649323 add eax, 0xf
00649326 mov ecx, edi
00649328 push eax
00649329 call 0x4274f0
0064932e mov esi, dword ptr [ebp - 0x6a8]
00649334 lea edx, [ebp - 0x9a0]
0064933a push 0xbc7a28
0064933f lea ecx, [ebp - 0xf14]
00649345 movss xmm0, dword ptr [esi + 0x370]
0064934d mulss xmm0, dword ptr [ebp - 0x6cc]
00649355 movss dword ptr [ebp - 0x9a0], xmm0
0064935d call 0x4120b0
00649362 add esp, 4
00649365 push eax
00649366 mov ecx, edi
00649368 call 0x427330
0064936d push ecx
0064936e mov ecx, edi
00649370 mov dword ptr [esp], 0xc1900000
00649377 call 0x4273d0
0064937c lea eax, [esi + 0x2a4]
00649382 mov ecx, edi
00649384 push eax
00649385 call 0x412190
0064938a mov edi, esi
0064938c mov eax, dword ptr [edi + 0x2c]
0064938f cmp eax, 0x23
00649392 je 0x6493a2
00649394 cmp eax, 0x25
00649397 je 0x6493a2
00649399 cmp eax, 0x26
0064939c jne 0x649663
006493a2 push 0
006493a4 push 2
006493a6 mov ecx, edi
006493a8 call 0x684790
006493ad test al, al
006493af je 0x649663
006493b5 cmp dword ptr [edi + 0x2c], 0x26
006493b9 lea esi, [edi + 0x370]
006493bf jne 0x6494d1
006493c5 mov dword ptr [ebp - 0x99c], 0x40400000
006493cf call 0x659200
006493d4 movss dword ptr [ebp - 0x998], xmm0
006493dc mov dword ptr [ebp - 0x994], 0x3e99999a
006493e6 call 0x6c3d90
006493eb push eax
006493ec push 0
006493ee push 0
006493f0 push esi
006493f1 lea eax, [ebp - 0xf1c]
006493f7 push eax
006493f8 lea eax, [ebp - 0x99c]
006493fe push eax
006493ff lea eax, [ebp - 0xf24]
00649405 push eax
00649406 lea eax, [ebp - 0x998]
0064940c push eax
0064940d lea eax, [ebp - 0xf2c]
00649413 push eax
00649414 lea eax, [ebp - 0xf34]
0064941a push eax
0064941b call 0x659290
00649420 add esp, 4
00649423 mov ecx, eax
00649425 call 0x962b50
0064942a mov ecx, eax
0064942c call 0x962b50
00649431 mov ecx, eax
00649433 call 0x962b50
00649438 push eax
00649439 lea eax, [ebp - 0xf3c]
0064943f push eax
00649440 lea eax, [ebp - 0x994]
00649446 push eax
00649447 lea eax, [ebp - 0xf44]
0064944d push eax
0064944e lea ecx, [edi + 0x2b8]
00649454 call 0x962b50
00649459 mov ecx, eax
0064945b call 0x962a60
00649460 mov ecx, dword ptr [0xbfd65c]
00649466 push eax
00649467 lea eax, [edi + 0x294]
0064946d push eax
0064946e push 0x58
00649470 push 0x3e8
00649475 call 0x422e20
0064947a mov esi, eax
0064947c call 0x659200
00649481 mulss xmm0, dword ptr [ebp - 0x6c4]
00649489 lea eax, [ebp - 0x990]
0064948f push eax
00649490 lea eax, [ebp - 0xf4c]
00649496 mov dword ptr [ebp - 0x970], 0x3f4ccccd
006494a0 push eax
006494a1 addss xmm0, dword ptr [ebp - 0x6c4]
006494a9 lea eax, [ebp - 0x970]
006494af push eax
006494b0 lea eax, [ebp - 0xf54]
006494b6 push eax
006494b7 lea eax, [edi + 0x370]
006494bd movss dword ptr [ebp - 0x990], xmm0
006494c5 push eax
006494c6 lea eax, [ebp - 0xf5c]
006494cc jmp 0x649601
006494d1 mov dword ptr [ebp - 0x98c], 0x40400000
006494db call 0x659200
006494e0 movss dword ptr [ebp - 0x988], xmm0
006494e8 mov dword ptr [ebp - 0x984], 0x3e99999a
006494f2 call 0x6c3d90
006494f7 push eax
006494f8 push 0
006494fa push 0
006494fc push esi
006494fd lea eax, [ebp - 0xf64]
00649503 push eax
00649504 lea eax, [ebp - 0x98c]
0064950a push eax
0064950b lea eax, [ebp - 0xf6c]
00649511 push eax
00649512 lea eax, [ebp - 0x988]
00649518 push eax
00649519 lea eax, [ebp - 0xf74]
0064951f push eax
00649520 lea eax, [ebp - 0xf7c]
00649526 push eax
00649527 call 0x659290
0064952c add esp, 4
0064952f mov ecx, eax
00649531 call 0x962b50
00649536 mov ecx, eax
00649538 call 0x962b50
0064953d mov ecx, eax
0064953f call 0x962b50
00649544 push eax
00649545 lea eax, [ebp - 0xf84]
0064954b push eax
0064954c lea eax, [ebp - 0x984]
00649552 push eax
00649553 lea eax, [ebp - 0xf8c]
00649559 push eax
0064955a lea ecx, [edi + 0x2b8]
00649560 call 0x962b50
00649565 mov ecx, eax
00649567 call 0x962a60
0064956c mov ecx, dword ptr [0xbfd65c]
00649572 push eax
00649573 lea eax, [edi + 0x294]
00649579 push eax
0064957a push 0x6f
0064957c push 0x3e8
00649581 call 0x422e20
00649586 mov esi, eax
00649588 call 0x659200
0064958d mulss xmm0, dword ptr [ebp - 0x6c4]
00649595 push ecx
00649596 mov ecx, esi
00649598 addss xmm0, dword ptr [ebp - 0x68c]
006495a0 movss dword ptr [esp], xmm0
006495a5 call 0x427440
006495aa mov ecx, eax
006495ac call 0x432ee0
006495b1 call 0x659200
006495b6 mulss xmm0, dword ptr [ebp - 0x6c4]
006495be lea eax, [ebp - 0x980]
006495c4 push eax
006495c5 lea eax, [ebp - 0xf94]
006495cb mov dword ptr [ebp - 0x97c], 0x3f000000
006495d5 push eax
006495d6 addss xmm0, dword ptr [ebp - 0x6c4]
006495de lea eax, [ebp - 0x97c]
006495e4 push eax
006495e5 lea eax, [ebp - 0xf9c]
006495eb push eax
006495ec lea eax, [edi + 0x370]
006495f2 movss dword ptr [ebp - 0x980], xmm0
006495fa push eax
006495fb lea eax, [ebp - 0xfa4]
00649601 push eax
00649602 mov ecx, 0xbc7a28
00649607 call 0x962b50
0064960c mov ecx, eax
0064960e call 0x962b50
00649613 mov ecx, eax
00649615 call 0x962b50
0064961a push eax
0064961b mov ecx, esi
0064961d call 0x427440
00649622 mov ecx, eax
00649624 call 0x41b8c0
00649629 lea eax, [edi + 0x2a4]
0064962f mov ecx, esi
00649631 push eax
00649632 call 0x412190
00649637 push 0xfffffe70
0064963c mov ecx, esi
0064963e call 0x432f20
00649643 lea ecx, [edi + 0x3c]
00649646 call 0x4023b0
0064964b push eax
0064964c mov ecx, esi
0064964e call 0x427440
00649653 mov ecx, eax
00649655 call 0x402370
0064965a mov eax, dword ptr [esi]
0064965c mov ecx, esi
0064965e mov eax, dword ptr [eax + 0xc]
00649661 call eax
00649663 lea esi, [edi + 0x378]
00649669 push 0xbc4980
0064966e mov edx, esi
00649670 lea ecx, [ebp - 0x1964]
00649676 call 0x412050
0064967b add esp, 4
0064967e mov ecx, eax
00649680 call 0x412090
00649685 test al, al
00649687 je 0x649826
0064968d movss xmm0, dword ptr [edi + 0x2c8]
00649695 lea esi, [edi + 0x294]
0064969b mulss xmm0, dword ptr [ebp - 0x688]
006496a3 lea eax, [ebp - 0xb0c]
006496a9 mov ecx, dword ptr [0xbfd65c]
006496af push -1
006496b1 push esi
006496b2 addss xmm0, dword ptr [0xb6aafc]
006496ba push eax
006496bb movss dword ptr [ebp - 0x668], xmm0
006496c3 call 0x4023f0
006496c8 mov ecx, eax
006496ca call 0x422d70
006496cf movss xmm3, dword ptr [ebp - 0x668]
006496d7 mov ecx, eax
006496d9 call 0x4157f0
006496de lea ecx, [ebp - 0xb0c]
006496e4 mov dword ptr [ebp - 4], 4
006496eb mov dword ptr [ebp - 0x688], 0
006496f5 call 0x4083d0
006496fa test eax, eax
006496fc je 0x64980e
00649702 xor ecx, ecx
00649704 push ecx
00649705 lea ecx, [ebp - 0xb0c]
0064970b call 0x4124b0
00649710 push 0
00649712 mov eax, dword ptr [eax]
00649714 mov ecx, eax
00649716 mov dword ptr [ebp - 0x674], eax
0064971c call 0x684630
00649721 test al, al
00649723 je 0x6497ef
00649729 mov ecx, dword ptr [ebp - 0x674]
0064972f call 0x4121e0
00649734 addss xmm0, dword ptr [edi + 0x2c8]
0064973c mov ecx, dword ptr [ebp - 0x674]
00649742 movss dword ptr [ebp - 0x670], xmm0
0064974a call 0x4121e0
0064974f movss xmm1, dword ptr [edi + 0x2c8]
00649757 lea eax, [ebp - 0xfac]
0064975d mulss xmm1, dword ptr [0xb6a8cc]
00649765 mov ecx, dword ptr [ebp - 0x674]
0064976b push esi
0064976c push eax
0064976d addss xmm0, xmm1
00649771 movss xmm1, dword ptr [ebp - 0x670]
00649779 mulss xmm1, xmm1
0064977d mulss xmm0, xmm0
00649781 movss dword ptr [ebp - 0x670], xmm1
00649789 movss dword ptr [ebp - 0x6b0], xmm0
00649791 call 0x412130
00649796 mov ecx, eax
00649798 call 0x962750
0064979d movss xmm0, dword ptr [ebp - 0x6b0]
006497a5 fstp dword ptr [ebp - 0x668]
006497ab movss xmm1, dword ptr [ebp - 0x668]
006497b3 comiss xmm0, xmm1
006497b6 jbe 0x6497ef
006497b8 comiss xmm1, dword ptr [ebp - 0x670]
006497bf jbe 0x6497ef
006497c1 push edi
006497c2 lea ecx, [ebp - 0x21ac]
006497c8 call 0x4229a0
006497cd mov ecx, dword ptr [ebp - 0x674]
006497d3 lea edx, [ebp - 0x21ac]
006497d9 push 0x1e
006497db push edx
006497dc push 0
006497de mov eax, dword ptr [ecx]
006497e0 push 0
006497e2 push ecx
006497e3 mov dword ptr [esp], 0x40000000
006497ea mov eax, dword ptr [eax + 0x20]
006497ed call eax
006497ef inc dword ptr [ebp - 0x688]
006497f5 lea ecx, [ebp - 0xb0c]
006497fb call 0x4083d0
00649800 mov ecx, dword ptr [ebp - 0x688]
00649806 cmp ecx, eax
00649808 jb 0x649704
0064980e lea ecx, [ebp - 0xb0c]
00649814 mov dword ptr [ebp - 4], 0xffffffff
0064981b call 0x412490
00649820 lea esi, [edi + 0x378]
00649826 push 0xbc48b0
0064982b mov edx, esi
0064982d lea ecx, [ebp - 0x1974]
00649833 call 0x412050
00649838 add esp, 4
0064983b mov ecx, eax
0064983d call 0x412090
00649842 test al, al
00649844 je 0x6498d2
0064984a push 0xbc4790
0064984f push 0xbc4ce0
00649854 mov edx, 0xbc4890
00649859 lea ecx, [ebp - 0x1984]
0064985f call 0x427220
00649864 add esp, 4
00649867 lea ecx, [ebp - 0x1994]
0064986d mov edx, eax
0064986f call 0x427220
00649874 push eax
00649875 mov edx, esi
00649877 lea ecx, [ebp - 0x19a4]
0064987d call 0x412050
00649882 add esp, 8
00649885 mov ecx, eax
00649887 call 0x427260
0064988c test al, al
0064988e je 0x6498d2
00649890 movss xmm3, dword ptr [ebp - 0x684]
00649898 movss xmm2, dword ptr [0xb6a974]
006498a0 movss xmm1, dword ptr [ebp - 0x67c]
006498a8 movss xmm0, dword ptr [edi + 0x2fc]
006498b0 push ecx
006498b1 mov cl, 1
006498b3 mov dword ptr [esp], 0x3f4ccccd
006498ba call 0x962420
006498bf mulss xmm0, dword ptr [edi + 0x2c4]
006498c7 add esp, 4
006498ca movss dword ptr [edi + 0x2c4], xmm0
006498d2 push 0xbc4730
006498d7 mov edx, esi
006498d9 lea ecx, [ebp - 0x19b4]
006498df call 0x412050
006498e4 add esp, 4
006498e7 mov ecx, eax
006498e9 call 0x412090
006498ee test al, al
006498f0 je 0x6499d7
006498f6 push 0xbc4790
006498fb push 0xbc4ce0
00649900 mov edx, 0xbc4890
00649905 lea ecx, [ebp - 0x19c4]
0064990b call 0x427220
00649910 add esp, 4
00649913 lea ecx, [ebp - 0x19d4]
00649919 mov edx, eax
0064991b call 0x427220
00649920 push eax
00649921 mov edx, esi
00649923 lea ecx, [ebp - 0x19e4]
00649929 call 0x412050
0064992e add esp, 8
00649931 mov ecx, eax
00649933 call 0x427260
00649938 test al, al
0064993a je 0x6499d7
00649940 movss xmm3, dword ptr [0xb6a560]
00649948 movss xmm2, dword ptr [0xb6a974]
00649950 movss xmm1, dword ptr [ebp - 0x67c]
00649958 movss xmm0, dword ptr [edi + 0x2fc]
00649960 push ecx
00649961 mov cl, 1
00649963 mov dword ptr [esp], 0x3f99999a
0064996a call 0x962420
0064996f add esp, 4
00649972 movss dword ptr [ebp - 0x668], xmm0
0064997a lea ecx, [edi + 0x2b8]
00649980 call 0x962a00
00649985 movss xmm0, dword ptr [ebp - 0x668]
0064998d lea edx, [ebp - 0x96c]
00649993 movss dword ptr [ebp - 0x668], xmm0
0064999b lea ecx, [ebp - 0x978]
006499a1 fmul dword ptr [ebp - 0x668]
006499a7 mov dword ptr [ebp - 0x978], 0x41f00000
006499b1 fstp dword ptr [ebp - 0x96c]
006499b7 call 0x407e80
006499bc push ecx
006499bd lea ecx, [edi + 0x2b8]
006499c3 movss xmm0, dword ptr [eax]
006499c7 movss dword ptr [esp], xmm0
006499cc call 0x962860
006499d1 lea esi, [edi + 0x378]
006499d7 push 0xbc4890
006499dc mov edx, esi
006499de lea ecx, [ebp - 0x19f4]
006499e4 call 0x412050
006499e9 add esp, 4
006499ec mov ecx, eax
006499ee call 0x412090
006499f3 test al, al
006499f5 je 0x64a371
006499fb push 0xbc4ce0
00649a00 mov edx, esi
00649a02 lea ecx, [ebp - 0x1a04]
00649a08 call 0x412050
00649a0d add esp, 4
00649a10 mov ecx, eax
00649a12 call 0x427260
00649a17 test al, al
00649a19 je 0x64a371
00649a1f mov ecx, edi
00649a21 call 0x6414a0
00649a26 mov dword ptr [ebp - 0x670], eax
00649a2c test eax, eax
00649a2e je 0x649a72
00649a30 mov ecx, eax
00649a32 call 0x5b76b0
00649a37 mov ecx, dword ptr [ebp - 0x670]
00649a3d movss dword ptr [ebp - 0x680], xmm0
00649a45 call 0x5ef430
00649a4a mov ecx, dword ptr [ebp - 0x670]
00649a50 movss dword ptr [ebp - 0x66c], xmm0
00649a58 call 0x5b7690
00649a5d mov ecx, dword ptr [ebp - 0x670]
00649a63 movss dword ptr [ebp - 0x674], xmm0
00649a6b call 0x427830
00649a70 jmp 0x649a9a
00649a72 movss xmm0, dword ptr [0xb6a8a0]
00649a7a movss dword ptr [ebp - 0x66c], xmm0
00649a82 movss xmm0, dword ptr [0xb6a974]
00649a8a movss dword ptr [ebp - 0x674], xmm0
00649a92 movss xmm0, dword ptr [ebp - 0x684]
00649a9a movss dword ptr [ebp - 0x870], xmm0
00649aa2 movss xmm0, dword ptr [ebp - 0x674]
00649aaa divss xmm0, dword ptr [0xb6a974]
00649ab2 mov dword ptr [ebp - 0x85c], 0x40400000
00649abc movss xmm1, dword ptr [0xb6a7b0]
00649ac4 call 0x4f3dc0
00649ac9 movss dword ptr [ebp - 0x668], xmm0
00649ad1 movss xmm0, dword ptr [ebp - 0x66c]
00649ad9 call 0x4228f0
00649ade movss xmm1, dword ptr [ebp - 0x668]
00649ae6 lea edx, [ebp - 0x854]
00649aec mulss xmm1, xmm0
00649af0 lea ecx, [ebp - 0x858]
00649af6 mov dword ptr [ebp - 0x858], 0x41200000
00649b00 movss dword ptr [ebp - 0x854], xmm1
00649b08 call 0x407e80
00649b0d lea edx, [ebp - 0x85c]
00649b13 mov ecx, eax
00649b15 call 0x417c70
00649b1a push ecx
00649b1b mov ecx, edi
00649b1d movss xmm0, dword ptr [eax]
00649b21 movss dword ptr [ebp - 0x710], xmm0
00649b29 movss xmm0, dword ptr [ebp - 0x680]
00649b31 movss dword ptr [esp], xmm0
00649b36 call 0x6500f0
00649b3b push ecx
00649b3c mov ecx, edi
00649b3e mov dword ptr [esp], 0
00649b45 call 0x436b90
00649b4a push ecx
00649b4b mov ecx, edi
00649b4d mov dword ptr [esp], 0
00649b54 call 0x436b70
00649b59 push 0xbc47f0
00649b5e mov edx, 0xbc4bf0
00649b63 lea ecx, [ebp - 0x1a14]
00649b69 call 0x427220
00649b6e push eax
00649b6f mov edx, esi
00649b71 lea ecx, [ebp - 0x1a24]
00649b77 call 0x412050
00649b7c add esp, 8
00649b7f mov ecx, eax
00649b81 call 0x427260
00649b86 test al, al
00649b88 je 0x649ba2
00649b8a movss xmm0, dword ptr [edi + 0x2c4]
00649b92 mulss xmm0, dword ptr [0xb6a5d8]
00649b9a movss dword ptr [edi + 0x2c4], xmm0
00649ba2 mov ecx, edi
00649ba4 call 0x682200
00649ba9 cmp eax, 0xa
00649bac jle 0x64a371
00649bb2 movss xmm0, dword ptr [edi + 0x370]
00649bba comiss xmm0, dword ptr [ebp - 0x710]
00649bc1 jae 0x649c31
00649bc3 movss xmm0, dword ptr [ebp - 0x674]
00649bcb lea edx, [ebp - 0x860]
00649bd1 mulss xmm0, dword ptr [0xb6a8f4]
00649bd9 lea ecx, [ebp - 0x864]
00649bdf mov dword ptr [ebp - 0x864], 0x96
00649be9 mov dword ptr [ebp - 0x868], 0x50
00649bf3 cvttss2si eax, xmm0
00649bf7 mov dword ptr [ebp - 0x860], eax
00649bfd call 0x417c60
00649c02 mov edx, eax
00649c04 lea ecx, [ebp - 0x868]
00649c0a call 0x417c80
00649c0f mov ecx, edi
00649c11 mov esi, eax
00649c13 call 0x682200
00649c18 cmp eax, dword ptr [esi]
00649c1a jge 0x649c2b
00649c1c mov ecx, edi
00649c1e call 0x641420
00649c23 test al, al
00649c25 je 0x649fd0
00649c2b lea esi, [edi + 0x378]
00649c31 movss xmm2, dword ptr [edi + 0x370]
00649c39 mulss xmm2, dword ptr [0xb6a8f4]
00649c41 movss xmm1, dword ptr [0xb6a940]
00649c49 movss xmm0, dword ptr [ebp - 0x67c]
00649c51 call 0x9623e0
00649c56 cvttss2si eax, xmm0
00649c5a push 0xbc49e0
00649c5f mov edx, esi
00649c61 lea ecx, [ebp - 0x1a34]
00649c67 mov dword ptr [ebp - 0x688], eax
00649c6d call 0x412050
00649c72 add esp, 4
00649c75 mov ecx, eax
00649c77 call 0x412090
00649c7c test al, al
00649c7e je 0x649c87
00649c80 add dword ptr [ebp - 0x688], 4
00649c87 push 0xbc4a00
00649c8c mov edx, esi
00649c8e lea ecx, [ebp - 0x1a44]
00649c94 call 0x412050
00649c99 add esp, 4
00649c9c mov ecx, eax
00649c9e call 0x412090
00649ca3 test al, al
00649ca5 je 0x649cc6
00649ca7 movd xmm0, dword ptr [ebp - 0x688]
00649caf cvtdq2ps xmm0, xmm0
00649cb2 mulss xmm0, dword ptr [0xb6a6f0]
00649cba cvttss2si eax, xmm0
00649cbe mov dword ptr [ebp - 0x688], eax
00649cc4 jmp 0x649ccc
00649cc6 mov eax, dword ptr [ebp - 0x688]
00649ccc cmp eax, 3
00649ccf jl 0x649fa8
00649cd5 call 0x659200
00649cda mulss xmm0, dword ptr [0xb6ac40]
00649ce2 mov dword ptr [ebp - 0x680], 0
00649cec movd xmm1, dword ptr [ebp - 0x688]
00649cf4 cvtdq2ps xmm1, xmm1
00649cf7 movss dword ptr [ebp - 0x6b0], xmm0
00649cff movss xmm0, dword ptr [0xb6ac40]
00649d07 divss xmm0, xmm1
00649d0b movss dword ptr [ebp - 0x668], xmm0
00649d13 jmp 0x649d26
00649d15 nop word ptr [eax + eax]
00649d20 lea esi, [edi + 0x378]
00649d26 lea eax, [ebp - 0x1a54]
00649d2c mov edx, 0xbc49e0
00649d31 push eax
00649d32 push 0xbc48a0
00649d37 push 0xbc4ce0
00649d3c push 0xbc4890
00649d41 push 0xbc4a00
00649d46 lea ecx, [ebp - 0x1a64]
00649d4c call 0x427220
00649d51 add esp, 4
00649d54 lea ecx, [ebp - 0x1a74]
00649d5a mov edx, eax
00649d5c call 0x427220
00649d61 add esp, 4
00649d64 lea ecx, [ebp - 0x1a84]
00649d6a mov edx, eax
00649d6c call 0x427220
00649d71 add esp, 4
00649d74 lea ecx, [ebp - 0x1a94]
00649d7a mov edx, eax
00649d7c call 0x427220
00649d81 add esp, 4
00649d84 mov ecx, eax
00649d86 call 0x57f3a0
00649d8b push eax
00649d8c mov edx, esi
00649d8e lea ecx, [ebp - 0x1294]
00649d94 call 0x412050
00649d99 mov dword ptr [ebp - 0x86c], 0x41200000
00649da3 add esp, 4
00649da6 mov esi, dword ptr [edi + 0x2c]
00649da9 mov eax, 1
00649dae cmp esi, 0x24
00649db1 cmove esi, eax
00649db4 call 0x6c3d90
00649db9 movd xmm0, dword ptr [ebp - 0x680]
00649dc1 push 0
00649dc3 push 0xbeae24
00649dc8 push 0xbeab18
00649dcd push 0
00649dcf push eax
00649dd0 push 0
00649dd2 push dword ptr [edi + 0x320]
00649dd8 cvtdq2ps xmm0, xmm0
00649ddb lea eax, [ebp - 0x86c]
00649de1 push eax
00649de2 lea eax, [ebp - 0xfb4]
00649de8 push eax
00649de9 lea eax, [ebp - 0x870]
00649def mulss xmm0, dword ptr [ebp - 0x668]
00649df7 push eax
00649df8 lea eax, [ebp - 0xfbc]
00649dfe push eax
00649dff addss xmm0, dword ptr [ebp - 0x6b0]
00649e07 push ecx
00649e08 lea eax, [ebp - 0xfc4]
00649e0e movss dword ptr [esp], xmm0
00649e13 push eax
00649e14 call 0x9627f0
00649e19 add esp, 8
00649e1c mov ecx, eax
00649e1e call 0x962b50
00649e23 mov ecx, eax
00649e25 call 0x962b50
00649e2a mov ecx, dword ptr [0xbfd65c]
00649e30 push eax
00649e31 lea eax, [edi + 0x294]
00649e37 push eax
00649e38 push esi
00649e39 push 2
00649e3b call 0x422e20
00649e40 push eax
00649e41 call 0x9ec34c
00649e46 mov esi, eax
00649e48 mov dword ptr [ebp - 0x874], 0xc0c00000
00649e52 lea edx, [ebp - 0x874]
00649e58 mov dword ptr [ebp - 0x670], esi
00649e5e lea ecx, [edi + 0x360]
00649e64 call 0x407e80
00649e69 add esp, 0x10
00649e6c movss xmm0, dword ptr [eax]
00649e70 mov ecx, esi
00649e72 movss dword ptr [esp], xmm0
00649e77 call 0x6500f0
00649e7c movss xmm0, dword ptr [edi + 0x374]
00649e84 mulss xmm0, dword ptr [ebp - 0x68c]
00649e8c push ecx
00649e8d mov ecx, esi
00649e8f movss dword ptr [esp], xmm0
00649e94 call 0x650250
00649e99 movups xmm0, xmmword ptr [ebp - 0x1294]
00649ea0 sub esp, 0x10
00649ea3 mov ecx, esi
00649ea5 mov eax, esp
00649ea7 movups xmmword ptr [eax], xmm0
00649eaa call 0x650280
00649eaf movss xmm0, dword ptr [edi + 0x2e0]
00649eb7 mov eax, dword ptr [esi]
00649eb9 mulss xmm0, dword ptr [ebp - 0x68c]
00649ec1 push ecx
00649ec2 mov ecx, esi
00649ec4 mov eax, dword ptr [eax + 0x3c]
00649ec7 movss dword ptr [esp], xmm0
00649ecc call eax
00649ece mov esi, dword ptr [esi]
00649ed0 mov ecx, edi
00649ed2 push 1
00649ed4 push 0
00649ed6 push 0xff
00649edb push -1
00649edd call 0x4f3de0
00649ee2 mov ecx, dword ptr [ebp - 0x670]
00649ee8 push eax
00649ee9 mov eax, dword ptr [esi + 0x38]
00649eec call eax
00649eee movzx eax, byte ptr [edi + 0x3b8]
00649ef5 mov ecx, dword ptr [ebp - 0x670]
00649efb push eax
00649efc call 0x5ef1c0
00649f01 movzx eax, byte ptr [edi + 0x3b9]
00649f08 mov ecx, dword ptr [ebp - 0x670]
00649f0e push eax
00649f0f call 0x5ef1e0
00649f14 push dword ptr [edi + 0x298]
00649f1a mov ecx, dword ptr [ebp - 0x670]
00649f20 lea esi, [edi + 0x294]
00649f26 push dword ptr [esi]
00649f28 call 0x427390
00649f2d push 0xbc46c0
00649f32 lea edx, [edi + 0x378]
00649f38 lea ecx, [ebp - 0x1aa4]
00649f3e call 0x412050
00649f43 add esp, 4
00649f46 mov ecx, eax
00649f48 call 0x412090
00649f4d test al, al
00649f4f je 0x649f84
00649f51 mov ecx, dword ptr [ebp - 0x670]
00649f57 call 0x447d70
00649f5c fsubr dword ptr [0xb6aed0]
00649f62 push ecx
00649f63 mov ecx, dword ptr [ebp - 0x670]
00649f69 fstp dword ptr [esp]
00649f6c call 0x436b70
00649f71 push ecx
00649f72 mov ecx, dword ptr [ebp - 0x670]
00649f78 mov dword ptr [esp], 0x40400000
00649f7f call 0x436b90
00649f84 mov eax, dword ptr [ebp - 0x680]
00649f8a inc eax
00649f8b mov dword ptr [ebp - 0x680], eax
00649f91 cmp eax, dword ptr [ebp - 0x688]
00649f97 jl 0x649d20
00649f9d mov eax, dword ptr [edi]
00649f9f mov ecx, edi
00649fa1 mov eax, dword ptr [eax + 0x28]
00649fa4 call eax
00649fa6 jmp 0x649fd6
00649fa8 lea eax, [ebp - 0x1ab4]
00649fae mov ecx, 0xbc4890
00649fb3 push eax
00649fb4 call 0x57f3a0
00649fb9 push eax
00649fba mov ecx, esi
00649fbc call 0x6413c0
00649fc1 push ecx
00649fc2 mov ecx, edi
00649fc4 mov dword ptr [esp], 0x3f000000
00649fcb call 0x436b70
00649fd0 lea esi, [edi + 0x294]
00649fd6 cmp byte ptr [edi + 0x16b], 0
00649fdd jne 0x64a36b
00649fe3 movss xmm0, dword ptr [edi + 0x370]
00649feb lea eax, [ebp - 0xa8c]
00649ff1 mulss xmm0, dword ptr [edi + 0x2c8]
00649ff9 mov ecx, dword ptr [0xbfd65c]
00649fff push 4
0064a001 push esi
0064a002 mulss xmm0, dword ptr [0xb6a8cc]
0064a00a push eax
0064a00b movss dword ptr [ebp - 0x668], xmm0
0064a013 call 0x4023f0
0064a018 mov ecx, eax
0064a01a call 0x422d70
0064a01f movss xmm3, dword ptr [ebp - 0x668]
0064a027 mov ecx, eax
0064a029 call 0x4157f0
0064a02e lea ecx, [ebp - 0xa8c]
0064a034 mov dword ptr [ebp - 4], 5
0064a03b mov dword ptr [ebp - 0x680], 0
0064a045 call 0x4083d0
0064a04a test eax, eax
0064a04c je 0x64a359
0064a052 xor ecx, ecx
0064a054 push ecx
0064a055 lea ecx, [ebp - 0xa8c]
0064a05b call 0x4124b0
0064a060 mov ecx, dword ptr [eax]
0064a062 call 0x4274a0
0064a067 mov dword ptr [ebp - 0x670], eax
0064a06d test eax, eax
0064a06f je 0x64a267
0064a075 cmp eax, edi
0064a077 je 0x64a267
0064a07d mov ecx, eax
0064a07f call 0x412350
0064a084 test al, al
0064a086 jne 0x64a267
0064a08c mov ecx, dword ptr [ebp - 0x670]
0064a092 lea eax, [ebp - 0x1ac4]
0064a098 push 0xbc4ce0
0064a09d push eax
0064a09e call 0x412650
0064a0a3 mov edx, eax
0064a0a5 lea ecx, [ebp - 0x1ad4]
0064a0ab call 0x412050
0064a0b0 add esp, 4
0064a0b3 mov ecx, eax
0064a0b5 call 0x412090
0064a0ba test al, al
0064a0bc jne 0x64a267
0064a0c2 mov ecx, dword ptr [ebp - 0x670]
0064a0c8 call 0x4121e0
0064a0cd addss xmm0, dword ptr [edi + 0x2c8]
0064a0d5 lea edx, [ebp - 0x878]
0064a0db mov dword ptr [ebp - 0x87c], 0x40a00000
0064a0e5 lea ecx, [ebp - 0x87c]
0064a0eb movss dword ptr [ebp - 0x878], xmm0
0064a0f3 call 0x417c70
0064a0f8 mov ecx, dword ptr [ebp - 0x670]
0064a0fe push esi
0064a0ff movss xmm0, dword ptr [eax]
0064a103 lea eax, [ebp - 0xfcc]
0064a109 push eax
0064a10a movss dword ptr [ebp - 0x668], xmm0
0064a112 call 0x412130
0064a117 mov ecx, eax
0064a119 call 0x962750
0064a11e movss xmm0, dword ptr [ebp - 0x668]
0064a126 mulss xmm0, xmm0
0064a12a fstp dword ptr [ebp - 0x6b0]
0064a130 comiss xmm0, dword ptr [ebp - 0x6b0]
0064a137 jb 0x64a267
0064a13d mov esi, dword ptr [ebp - 0x670]
0064a143 mov ecx, esi
0064a145 call 0x544b60
0064a14a movss xmm0, dword ptr [edi + 0x370]
0064a152 fstp dword ptr [ebp - 0x668]
0064a158 comiss xmm0, dword ptr [ebp - 0x668]
0064a15f ja 0x64a193
0064a161 push 0xbc4890
0064a166 lea eax, [ebp - 0x1ae4]
0064a16c mov ecx, esi
0064a16e push eax
0064a16f call 0x412650
0064a174 mov edx, eax
0064a176 lea ecx, [ebp - 0x1af4]
0064a17c call 0x412050
0064a181 add esp, 4
0064a184 mov ecx, eax
0064a186 call 0x427260
0064a18b test al, al
0064a18d je 0x64a28b
0064a193 movss xmm0, dword ptr [ebp - 0x674]
0064a19b lea edx, [ebp - 0x880]
0064a1a1 mulss xmm0, dword ptr [edi + 0x374]
0064a1a9 lea ecx, [ebp - 0x884]
0064a1af mov dword ptr [ebp - 0x884], 0x3e4ccccd
0064a1b9 mov dword ptr [ebp - 0x888], 0x3f800000
0064a1c3 divss xmm0, dword ptr [0xb6aa60]
0064a1cb movss dword ptr [ebp - 0x880], xmm0
0064a1d3 call 0x417c70
0064a1d8 mov edx, eax
0064a1da lea ecx, [ebp - 0x888]
0064a1e0 call 0x407e80
0064a1e5 lea edx, [ebp - 0x88c]
0064a1eb lea ecx, [ebp - 0x710]
0064a1f1 movss xmm0, dword ptr [eax]
0064a1f5 addss xmm0, dword ptr [edi + 0x374]
0064a1fd movss dword ptr [ebp - 0x88c], xmm0
0064a205 call 0x407e80
0064a20a push ecx
0064a20b mov ecx, edi
0064a20d movss xmm0, dword ptr [eax]
0064a211 movss dword ptr [esp], xmm0
0064a216 call 0x650250
0064a21b mov ecx, esi
0064a21d call 0x59fd40
0064a222 fstp dword ptr [ebp - 0x890]
0064a228 mov esi, dword ptr [edi]
0064a22a lea ecx, [edi + 0x2e0]
0064a230 lea edx, [ebp - 0x890]
0064a236 call 0x417c70
0064a23b movss xmm0, dword ptr [ebp - 0x66c]
0064a243 push ecx
0064a244 mov ecx, edi
0064a246 addss xmm0, dword ptr [eax]
0064a24a mov eax, dword ptr [esi + 0x3c]
0064a24d movss dword ptr [esp], xmm0
0064a252 call eax
0064a254 mov ecx, dword ptr [ebp - 0x670]
0064a25a mov eax, dword ptr [ecx]
0064a25c mov eax, dword ptr [eax + 0x28]
0064a25f call eax
0064a261 lea esi, [edi + 0x294]
0064a267 inc dword ptr [ebp - 0x680]
0064a26d lea ecx, [ebp - 0xa8c]
0064a273 call 0x4083d0
0064a278 mov ecx, dword ptr [ebp - 0x680]
0064a27e cmp ecx, eax
0064a280 jb 0x64a054
0064a286 jmp 0x64a359
0064a28b movss xmm0, dword ptr [ebp - 0x674]
0064a293 lea edx, [ebp - 0x894]
0064a299 mulss xmm0, dword ptr [esi + 0x374]
0064a2a1 lea ecx, [ebp - 0x898]
0064a2a7 mov dword ptr [ebp - 0x898], 0x3e4ccccd
0064a2b1 mov dword ptr [ebp - 0x89c], 0x3f800000
0064a2bb divss xmm0, dword ptr [0xb6aa60]
0064a2c3 movss dword ptr [ebp - 0x894], xmm0
0064a2cb call 0x417c70
0064a2d0 mov edx, eax
0064a2d2 lea ecx, [ebp - 0x89c]
0064a2d8 call 0x407e80
0064a2dd lea edx, [ebp - 0x8a0]
0064a2e3 lea ecx, [ebp - 0x710]
0064a2e9 movss xmm0, dword ptr [eax]
0064a2ed addss xmm0, dword ptr [esi + 0x374]
0064a2f5 movss dword ptr [ebp - 0x8a0], xmm0
0064a2fd call 0x407e80
0064a302 push ecx
0064a303 mov ecx, esi
0064a305 movss xmm0, dword ptr [eax]
0064a309 movss dword ptr [esp], xmm0
0064a30e call 0x650250
0064a313 mov ecx, esi
0064a315 call 0x59fd40
0064a31a fstp dword ptr [ebp - 0x8a4]
0064a320 mov esi, dword ptr [esi]
0064a322 lea ecx, [edi + 0x2e0]
0064a328 lea edx, [ebp - 0x8a4]
0064a32e call 0x417c70
0064a333 movss xmm0, dword ptr [ebp - 0x66c]
0064a33b push ecx
0064a33c mov ecx, dword ptr [ebp - 0x670]
0064a342 addss xmm0, dword ptr [eax]
0064a346 mov eax, dword ptr [esi + 0x3c]
0064a349 movss dword ptr [esp], xmm0
0064a34e call eax
0064a350 mov eax, dword ptr [edi]
0064a352 mov ecx, edi
0064a354 mov eax, dword ptr [eax + 0x28]
0064a357 call eax
0064a359 lea ecx, [ebp - 0xa8c]
0064a35f mov dword ptr [ebp - 4], 0xffffffff
0064a366 call 0x412490
0064a36b lea esi, [edi + 0x378]
0064a371 push 0xbc4820
0064a376 mov edx, esi
0064a378 lea ecx, [ebp - 0x1b04]
0064a37e call 0x412050
0064a383 add esp, 4
0064a386 mov ecx, eax
0064a388 call 0x412090
0064a38d test al, al
0064a38f je 0x64a4cd
0064a395 lea ecx, [edi + 0x3e4]
0064a39b call 0x4076f0
0064a3a0 test eax, eax
0064a3a2 jne 0x64a433
0064a3a8 movss xmm0, dword ptr [0xb6a940]
0064a3b0 comiss xmm0, dword ptr [edi + 0x2fc]
0064a3b7 jbe 0x64a41a
0064a3b9 mov ecx, dword ptr [edi + 0x314]
0064a3bf test ecx, ecx
0064a3c1 je 0x64a405
0064a3c3 lea eax, [ebp - 0xfd4]
0064a3c9 push eax
0064a3ca call 0x412130
0064a3cf push eax
0064a3d0 lea ecx, [edi + 0x294]
0064a3d6 call 0x9626f0
0064a3db fstp dword ptr [ebp - 0x668]
0064a3e1 movss xmm0, dword ptr [ebp - 0x668]
0064a3e9 comiss xmm0, dword ptr [0xb6a974]
0064a3f0 jbe 0x64a405
0064a3f2 push dword ptr [edi + 0x314]
0064a3f8 lea ecx, [edi + 0x3e4]
0064a3fe call 0x4bc380
0064a403 jmp 0x64a433
0064a405 mov ecx, edi
0064a407 call 0x654660
0064a40c test eax, eax
0064a40e je 0x64a433
0064a410 push eax
0064a411 mov ecx, edi
0064a413 call 0x654cb0
0064a418 jmp 0x64a433
0064a41a lea eax, [ebp - 0x1b14]
0064a420 mov ecx, 0xbc4820
0064a425 push eax
0064a426 call 0x57f3a0
0064a42b push eax
0064a42c mov ecx, esi
0064a42e call 0x6413c0
0064a433 movss xmm0, dword ptr [edi + 0x2fc]
0064a43b comiss xmm0, dword ptr [ebp - 0x6e0]
0064a442 jbe 0x64a4c6
0064a448 lea ecx, [edi + 0x3e4]
0064a44e call 0x4076f0
0064a453 test eax, eax
0064a455 je 0x64a46d
0064a457 lea ecx, [edi + 0x3e4]
0064a45d call 0x4076f0
0064a462 mov ecx, eax
0064a464 call 0x422be0
0064a469 test al, al
0064a46b jne 0x64a4c6
0064a46d push dword ptr [edi + 0x20]
0064a470 mov ecx, edi
0064a472 push 4
0064a474 call 0x684790
0064a479 test al, al
0064a47b je 0x64a4c6
0064a47d mov ecx, edi
0064a47f call 0x654c40
0064a484 cmp eax, 5
0064a487 jge 0x64a4c6
0064a489 mov ecx, 0xa
0064a48e call 0x659230
0064a493 test eax, eax
0064a495 jne 0x64a4c6
0064a497 mov ecx, edi
0064a499 call 0x6547a0
0064a49e mov dword ptr [ebp - 0x668], eax
0064a4a4 test eax, eax
0064a4a6 je 0x64a4c6
0064a4a8 push eax
0064a4a9 lea ecx, [edi + 0x3e4]
0064a4af call 0x4bc380
0064a4b4 mov ecx, dword ptr [ebp - 0x668]
0064a4ba push edi
0064a4bb add ecx, 0x3e8
0064a4c1 call 0x4bc380
0064a4c6 mov ecx, edi
0064a4c8 call 0x654970
0064a4cd push 0xbc46a0
0064a4d2 mov edx, esi
0064a4d4 lea ecx, [ebp - 0x1b24]
0064a4da call 0x412050
0064a4df add esp, 4
0064a4e2 mov ecx, eax
0064a4e4 call 0x412090
0064a4e9 test al, al
0064a4eb je 0x64a6d9
0064a4f1 push 0xbc4ce0
0064a4f6 mov edx, esi
0064a4f8 lea ecx, [ebp - 0x1b34]
0064a4fe call 0x412050
0064a503 add esp, 4
0064a506 mov ecx, eax
0064a508 call 0x427260
0064a50d test al, al
0064a50f je 0x64a6d9
0064a515 mov ecx, dword ptr [edi + 0x314]
0064a51b test ecx, ecx
0064a51d je 0x64a6d9
0064a523 call 0x412100
0064a528 cmp eax, 1
0064a52b jne 0x64a6d9
0064a531 cmp dword ptr [edi + 0x3c8], 0
0064a538 jne 0x64a6d9
0064a53e push 0
0064a540 push 0xbeab9c
0064a545 push 0xbeab18
0064a54a push 0
0064a54c push dword ptr [edi + 0x314]
0064a552 call 0x9ec34c
0064a557 add esp, 0x14
0064a55a mov dword ptr [ebp - 0x6b0], eax
0064a560 mov ecx, eax
0064a562 push 0
0064a564 push 0xbeabc8
0064a569 push 0xbeab18
0064a56e push 0
0064a570 call 0x6415e0
0064a575 push eax
0064a576 call 0x9ec34c
0064a57b add esp, 0x14
0064a57e mov dword ptr [ebp - 0x678], eax
0064a584 test eax, eax
0064a586 je 0x64a6d9
0064a58c mov ecx, dword ptr [ebp - 0x6b0]
0064a592 lea eax, [ebp - 0xfdc]
0064a598 push eax
0064a599 call 0x412130
0064a59e push eax
0064a59f lea eax, [ebp - 0xa4c]
0064a5a5 push eax
0064a5a6 lea ecx, [edi + 0x294]
0064a5ac call 0x962ac0
0064a5b1 push 0xbc4920
0064a5b6 mov edx, esi
0064a5b8 mov dword ptr [ebp - 0x744], 0x3f800000
0064a5c2 lea ecx, [ebp - 0x1b44]
0064a5c8 call 0x412050
0064a5cd add esp, 4
0064a5d0 mov ecx, eax
0064a5d2 call 0x412090
0064a5d7 test al, al
0064a5d9 je 0x64a60e
0064a5db lea eax, [ebp - 0xa4c]
0064a5e1 push eax
0064a5e2 lea ecx, [edi + 0x2b8]
0064a5e8 call 0x962600
0064a5ed movss xmm0, dword ptr [ebp - 0x67c]
0064a5f5 fstp dword ptr [ebp - 0x668]
0064a5fb comiss xmm0, dword ptr [ebp - 0x668]
0064a602 jbe 0x64a60e
0064a604 mov dword ptr [ebp - 0x744], 0xbf800000
0064a60e lea ecx, [edi + 0x2b8]
0064a614 call 0x962a00
0064a619 mov ecx, dword ptr [ebp - 0x678]
0064a61f fstp dword ptr [ebp - 0x668]
0064a625 call 0x7fab60
0064a62a push ecx
0064a62b lea eax, [ebp - 0xa5c]
0064a631 fstp dword ptr [esp]
0064a634 push eax
0064a635 call 0x9627f0
0064a63a movss xmm0, dword ptr [ebp - 0x668]
0064a642 lea eax, [ebp - 0x744]
0064a648 add esp, 8
0064a64b push eax
0064a64c lea eax, [ebp - 0xfe4]
0064a652 push eax
0064a653 push ecx
0064a654 lea eax, [ebp - 0xfec]
0064a65a movss dword ptr [esp], xmm0
0064a65f push eax
0064a660 lea ecx, [ebp - 0xa5c]
0064a666 call 0x9628d0
0064a66b mov ecx, eax
0064a66d call 0x962b50
0064a672 push eax
0064a673 lea ecx, [edi + 0x2b8]
0064a679 call 0x962cd0
0064a67e lea ecx, [ebp - 0xa4c]
0064a684 call 0x962a00
0064a689 lea eax, [ebp - 0x8a8]
0064a68f push eax
0064a690 lea eax, [ebp - 0xff4]
0064a696 push eax
0064a697 lea ecx, [ebp - 0xa5c]
0064a69d fstp dword ptr [ebp - 0x8a8]
0064a6a3 call 0x962b50
0064a6a8 mov ecx, dword ptr [ebp - 0x6b0]
0064a6ae push eax
0064a6af lea eax, [ebp - 0xffc]
0064a6b5 push eax
0064a6b6 lea eax, [ebp - 0x1004]
0064a6bc push eax
0064a6bd call 0x412130
0064a6c2 mov ecx, eax
0064a6c4 call 0x962a60
0064a6c9 lea esi, [edi + 0x294]
0064a6cf push eax
0064a6d0 mov ecx, esi
0064a6d2 call 0x962cd0
0064a6d7 jmp 0x64a6df
0064a6d9 lea esi, [edi + 0x294]
0064a6df push 0
0064a6e1 push 0x80000
0064a6e6 mov ecx, edi
0064a6e8 call 0x4122f0
0064a6ed test al, al
0064a6ef je 0x64a74b
0064a6f1 movss xmm0, dword ptr [edi + 0x2fc]
0064a6f9 movss xmm1, dword ptr [0xb6a8f4]
0064a701 comiss xmm1, xmm0
0064a704 jbe 0x64a73d
0064a706 movss xmm3, dword ptr [0xb6a4a0]
0064a70e movaps xmm2, xmm1
0064a711 movss xmm1, dword ptr [ebp - 0x67c]
0064a719 push ecx
0064a71a mov cl, 1
0064a71c mov dword ptr [esp], 0x3f800000
0064a723 call 0x962420
0064a728 mulss xmm0, dword ptr [edi + 0x2c4]
0064a730 add esp, 4
0064a733 movss dword ptr [edi + 0x2c4], xmm0
0064a73b jmp 0x64a74b
0064a73d push 0
0064a73f push 0x80000
0064a744 mov ecx, edi
0064a746 call 0x4122c0
0064a74b push 0xbc4790
0064a750 lea edx, [edi + 0x378]
0064a756 lea ecx, [ebp - 0x1b54]
0064a75c call 0x412050
0064a761 add esp, 4
0064a764 mov ecx, eax
0064a766 call 0x412090
0064a76b test al, al
0064a76d je 0x64ab3a
0064a773 push 0xbc4ce0
0064a778 lea edx, [edi + 0x378]
0064a77e lea ecx, [ebp - 0x1b64]
0064a784 call 0x412050
0064a789 add esp, 4
0064a78c mov ecx, eax
0064a78e call 0x427260
0064a793 test al, al
0064a795 je 0x64ab3a
0064a79b movss xmm0, dword ptr [edi + 0x2c8]
0064a7a3 lea eax, [ebp - 0xa9c]
0064a7a9 mulss xmm0, dword ptr [0xb6a8cc]
0064a7b1 mov ecx, dword ptr [0xbfd65c]
0064a7b7 push 4
0064a7b9 push esi
0064a7ba push eax
0064a7bb movss dword ptr [ebp - 0x668], xmm0
0064a7c3 call 0x4023f0
0064a7c8 mov ecx, eax
0064a7ca call 0x422d70
0064a7cf movss xmm3, dword ptr [ebp - 0x668]
0064a7d7 mov ecx, eax
0064a7d9 call 0x4157f0
0064a7de lea ecx, [ebp - 0xa9c]
0064a7e4 mov dword ptr [ebp - 4], 6
0064a7eb mov dword ptr [ebp - 0x680], 0
0064a7f5 call 0x4083d0
0064a7fa test eax, eax
0064a7fc je 0x64ab10
0064a802 xor ecx, ecx
0064a804 push ecx
0064a805 lea ecx, [ebp - 0xa9c]
0064a80b call 0x4124b0
0064a810 mov ecx, dword ptr [eax]
0064a812 call 0x4274a0
0064a817 mov dword ptr [ebp - 0x688], eax
0064a81d test eax, eax
0064a81f je 0x64aaf1
0064a825 mov ecx, eax
0064a827 call 0x447d40
0064a82c cmp dword ptr [edi + 0x20], eax
0064a82f jb 0x64aaf1
0064a835 mov ecx, dword ptr [ebp - 0x688]
0064a83b lea eax, [ebp - 0x100c]
0064a841 push eax
0064a842 call 0x412130
0064a847 push eax
0064a848 lea eax, [ebp - 0x788]
0064a84e mov ecx, esi
0064a850 push eax
0064a851 call 0x962ac0
0064a856 mov ecx, dword ptr [ebp - 0x688]
0064a85c call 0x4121e0
0064a861 addss xmm0, dword ptr [edi + 0x2c8]
0064a869 lea ecx, [ebp - 0x788]
0064a86f mulss xmm0, dword ptr [0xb6a5a4]
0064a877 movss dword ptr [ebp - 0x6a0], xmm0
0064a87f call 0x962a30
0064a884 movss xmm1, dword ptr [ebp - 0x6a0]
0064a88c mulss xmm1, xmm1
0064a890 fstp dword ptr [ebp - 0x668]
0064a896 movss xmm0, dword ptr [ebp - 0x668]
0064a89e comiss xmm0, xmm1
0064a8a1 ja 0x64aaf1
0064a8a7 lea ecx, [ebp - 0x788]
0064a8ad call 0x962a30
0064a8b2 fstp dword ptr [ebp - 0x668]
0064a8b8 movss xmm0, dword ptr [ebp - 0x668]
0064a8c0 ucomiss xmm0, dword ptr [ebp - 0x67c]
0064a8c7 lahf 
0064a8c8 test ah, 0x44
0064a8cb jnp 0x64aaf1
0064a8d1 lea eax, [ebp - 0x730]
0064a8d7 push eax
0064a8d8 lea ecx, [ebp - 0x788]
0064a8de call 0x962560
0064a8e3 lea eax, [ebp - 0x730]
0064a8e9 push eax
0064a8ea lea ecx, [edi + 0x2b8]
0064a8f0 call 0x962600
0064a8f5 mov ecx, dword ptr [ebp - 0x688]
0064a8fb lea eax, [ebp - 0x730]
0064a901 push eax
0064a902 lea eax, [ebp - 0x1014]
0064a908 push eax
0064a909 fstp dword ptr [ebp - 0x6b0]
0064a90f call 0x412170
0064a914 mov ecx, eax
0064a916 call 0x962600
0064a91b lea eax, [ebp - 0x734]
0064a921 mov dword ptr [ebp - 0x734], 0x3f8ccccd
0064a92b push eax
0064a92c fstp dword ptr [ebp - 0x678]
0064a932 movss xmm0, dword ptr [ebp - 0x678]
0064a93a lea eax, [ebp - 0x101c]
0064a940 subss xmm0, dword ptr [ebp - 0x6b0]
0064a948 push eax
0064a949 lea eax, [ebp - 0x8ac]
0064a94f push eax
0064a950 lea eax, [ebp - 0x1024]
0064a956 push eax
0064a957 lea ecx, [ebp - 0x730]
0064a95d movss dword ptr [ebp - 0x8ac], xmm0
0064a965 call 0x962b50
0064a96a mov ecx, eax
0064a96c call 0x962b50
0064a971 push eax
0064a972 lea eax, [ebp - 0xb8c]
0064a978 push eax
0064a979 lea ecx, [edi + 0x2b8]
0064a97f call 0x962a60
0064a984 movss xmm0, dword ptr [ebp - 0x6b0]
0064a98c lea eax, [ebp - 0x734]
0064a992 subss xmm0, dword ptr [ebp - 0x678]
0064a99a push eax
0064a99b lea eax, [ebp - 0x102c]
0064a9a1 push eax
0064a9a2 lea eax, [ebp - 0x8b0]
0064a9a8 push eax
0064a9a9 lea eax, [ebp - 0x1034]
0064a9af movss dword ptr [ebp - 0x8b0], xmm0
0064a9b7 push eax
0064a9b8 lea ecx, [ebp - 0x730]
0064a9be call 0x962b50
0064a9c3 mov ecx, eax
0064a9c5 call 0x962b50
0064a9ca mov ecx, dword ptr [ebp - 0x688]
0064a9d0 push eax
0064a9d1 lea eax, [ebp - 0xb34]
0064a9d7 push eax
0064a9d8 lea eax, [ebp - 0x103c]
0064a9de push eax
0064a9df call 0x412170
0064a9e4 mov ecx, eax
0064a9e6 call 0x962a60
0064a9eb lea ecx, [ebp - 0x788]
0064a9f1 call 0x962a00
0064a9f6 fsubr dword ptr [ebp - 0x6a0]
0064a9fc lea eax, [ebp - 0x738]
0064aa02 push eax
0064aa03 lea eax, [ebp - 0x1044]
0064aa09 push eax
0064aa0a fmul dword ptr [0xb6a480]
0064aa10 lea ecx, [ebp - 0x730]
0064aa16 fstp dword ptr [ebp - 0x738]
0064aa1c call 0x962b50
0064aa21 push eax
0064aa22 lea eax, [ebp - 0xb3c]
0064aa28 push eax
0064aa29 lea ecx, [edi + 0x294]
0064aa2f call 0x962a60
0064aa34 lea eax, [ebp - 0x738]
0064aa3a push eax
0064aa3b lea eax, [ebp - 0x104c]
0064aa41 push eax
0064aa42 lea ecx, [ebp - 0x730]
0064aa48 call 0x962b50
0064aa4d mov ecx, dword ptr [ebp - 0x688]
0064aa53 push eax
0064aa54 lea eax, [ebp - 0xb44]
0064aa5a push eax
0064aa5b lea eax, [ebp - 0x1054]
0064aa61 push eax
0064aa62 call 0x412130
0064aa67 mov ecx, eax
0064aa69 call 0x962ac0
0064aa6e lea eax, [ebp - 0xb8c]
0064aa74 push eax
0064aa75 lea ecx, [edi + 0x2b8]
0064aa7b call 0x962cd0
0064aa80 mov ecx, dword ptr [ebp - 0x688]
0064aa86 lea eax, [ebp - 0xb34]
0064aa8c push eax
0064aa8d call 0x422ae0
0064aa92 lea eax, [ebp - 0xb3c]
0064aa98 lea esi, [edi + 0x294]
0064aa9e push eax
0064aa9f mov ecx, esi
0064aaa1 call 0x962cd0
0064aaa6 mov ecx, dword ptr [ebp - 0x688]
0064aaac lea eax, [ebp - 0xb44]
0064aab2 push eax
0064aab3 call 0x427300
0064aab8 mov eax, dword ptr [ebp - 0x688]
0064aabe inc word ptr [edi + 0x3bc]
0064aac5 movss xmm3, dword ptr [ebp - 0x684]
0064aacd push ecx
0064aace mov ecx, dword ptr [0xbfd680]
0064aad4 inc word ptr [eax + 0x3bc]
0064aadb mov dword ptr [esp], 0x3f800000
0064aae2 push 0
0064aae4 push 2
0064aae6 push esi
0064aae7 push 0x1ca
0064aaec call 0x8b14e0
0064aaf1 inc dword ptr [ebp - 0x680]
0064aaf7 lea ecx, [ebp - 0xa9c]
0064aafd call 0x4083d0
0064ab02 mov ecx, dword ptr [ebp - 0x680]
0064ab08 cmp ecx, eax
0064ab0a jb 0x64a804
0064ab10 movss xmm0, dword ptr [edi + 0x2c4]
0064ab18 lea ecx, [ebp - 0xa9c]
0064ab1e mulss xmm0, dword ptr [0xb6a5e8]
0064ab26 mov dword ptr [ebp - 4], 0xffffffff
0064ab2d movss dword ptr [edi + 0x2c4], xmm0
0064ab35 call 0x412490
0064ab3a movss xmm0, dword ptr [edi + 0x360]
0064ab42 comiss xmm0, dword ptr [0xb6ae98]
0064ab49 ja 0x64ab90
0064ab4b push 0xbc46c0
0064ab50 lea edx, [edi + 0x378]
0064ab56 lea ecx, [ebp - 0x1b74]
0064ab5c call 0x412050
0064ab61 add esp, 4
0064ab64 mov ecx, eax
0064ab66 call 0x412090
0064ab6b test al, al
0064ab6d je 0x64acbb
0064ab73 movss xmm0, dword ptr [edi + 0x364]
0064ab7b addss xmm0, dword ptr [edi + 0x360]
0064ab83 comiss xmm0, dword ptr [0xb6ae98]
0064ab8a jbe 0x64acbb
0064ab90 push 0xbc4ce0
0064ab95 lea edx, [edi + 0x378]
0064ab9b lea ecx, [ebp - 0x1b84]
0064aba1 call 0x412050
0064aba6 add esp, 4
0064aba9 mov ecx, eax
0064abab call 0x427260
0064abb0 test al, al
0064abb2 je 0x64acbb
0064abb8 cmp dword ptr [edi + 0x2c], 9
0064abbc jne 0x64ac0a
0064abbe cmp byte ptr [edi + 0x16b], 0
0064abc5 jne 0x64ac0a
0064abc7 push 0xc02fec
0064abcc lea ecx, [edi + 0x2b8]
0064abd2 call 0x962cd0
0064abd7 push ecx
0064abd8 mov dword ptr [edi + 0x17c], 0
0064abe2 lea ecx, [edi + 0x3c]
0064abe5 mov dword ptr [edi + 0x180], 0
0064abef mov dword ptr [esp], 0x43340000
0064abf6 call 0x430cc0
0064abfb push 0
0064abfd push 0xb46b08
0064ac02 lea ecx, [edi + 0x3c]
0064ac05 call 0x4054f0
0064ac0a push 0xbc46c0
0064ac0f lea edx, [edi + 0x378]
0064ac15 lea ecx, [ebp - 0x1b94]
0064ac1b call 0x412050
0064ac20 add esp, 4
0064ac23 mov ecx, eax
0064ac25 call 0x412090
0064ac2a test al, al
0064ac2c je 0x64ac55
0064ac2e movss xmm0, dword ptr [edi + 0x364]
0064ac36 mulss xmm0, dword ptr [0xb6ae58]
0064ac3e push ecx
0064ac3f mov ecx, edi
0064ac41 mov dword ptr [esp], 0xc0a00000
0064ac48 movss dword ptr [edi + 0x364], xmm0
0064ac50 call 0x6500f0
0064ac55 mov byte ptr [edi + 0x16b], 1
0064ac5c mov ecx, edi
0064ac5e or dword ptr [edi + 0x3c4], 4
0064ac65 push 0
0064ac67 call 0x650dd0
0064ac6c mov ecx, dword ptr [edi + 0x314]
0064ac72 test ecx, ecx
0064ac74 je 0x64b2b4
0064ac7a cmp byte ptr [edi + 0x738], 0
0064ac81 je 0x64b2b4
0064ac87 call 0x4866c0
0064ac8c mov esi, eax
0064ac8e test esi, esi
0064ac90 je 0x64b2b4
0064ac96 push 0
0064ac98 push 0x175
0064ac9d mov ecx, esi
0064ac9f call 0x73af30
0064aca4 test al, al
0064aca6 je 0x64acaf
0064aca8 mov ecx, esi
0064acaa call 0x78a720
0064acaf mov ecx, esi
0064acb1 call 0x78d2d0
0064acb6 jmp 0x64b2b4
0064acbb push 0xbc4780
0064acc0 mov edx, 0xbc4c10
0064acc5 lea ecx, [ebp - 0x1ba4]
0064accb call 0x427220
0064acd0 push eax
0064acd1 lea edx, [edi + 0x378]
0064acd7 lea ecx, [ebp - 0x2184]
0064acdd call 0x412050
0064ace2 add esp, 8
0064ace5 mov ecx, eax
0064ace7 call 0x412090
0064acec test al, al
0064acee jne 0x64acf6
0064acf0 cmp dword ptr [edi + 0x2c], 0x2e
0064acf4 jne 0x64ad10
0064acf6 mov ecx, dword ptr [0xbfd65c]
0064acfc call 0x4023f0
0064ad01 mov ecx, eax
0064ad03 call 0x7e2590
0064ad08 test al, al
0064ad0a je 0x64b1ce
0064ad10 push 0xbc4ce0
0064ad15 lea edx, [edi + 0x378]
0064ad1b lea ecx, [ebp - 0x1bc4]
0064ad21 call 0x412050
0064ad26 add esp, 4
0064ad29 mov ecx, eax
0064ad2b call 0x412090
0064ad30 test al, al
0064ad32 je 0x64ad3e
0064ad34 test byte ptr [edi + 0x30], 2
0064ad38 jne 0x64b1ce
0064ad3e push 0xbc4680
0064ad43 lea edx, [edi + 0x378]
0064ad49 lea ecx, [ebp - 0x1bd4]
0064ad4f call 0x412050
0064ad54 add esp, 4
0064ad57 mov ecx, eax
0064ad59 call 0x412090
0064ad5e test al, al
0064ad60 je 0x64af84
0064ad66 mov ecx, dword ptr [0xbfd65c]
0064ad6c push esi
0064ad6d call 0x4023f0
0064ad72 mov ecx, eax
0064ad74 call 0x7ce950
0064ad79 mov esi, eax
0064ad7b mov dword ptr [ebp - 0x678], esi
0064ad81 test esi, esi
0064ad83 js 0x64b2b4
0064ad89 mov ecx, dword ptr [0xbfd65c]
0064ad8f push esi
0064ad90 call 0x4023f0
0064ad95 mov ecx, eax
0064ad97 call 0x4276e0
0064ad9c mov dword ptr [ebp - 0x6b0], eax
0064ada2 test eax, eax
0064ada4 je 0x64b2b4
0064adaa mov ecx, eax
0064adac call 0x6dbe50
0064adb1 test al, al
0064adb3 je 0x64b2b4
0064adb9 lea eax, [ebp - 0x1be4]
0064adbf mov ecx, 0xbc4680
0064adc4 push eax
0064adc5 call 0x57f3a0
0064adca push eax
0064adcb lea ecx, [edi + 0x378]
0064add1 call 0x6413c0
0064add6 mov ecx, dword ptr [ebp - 0x6b0]
0064addc push 2
0064adde call 0x6414d0
0064ade3 mov ecx, dword ptr [ebp - 0x6b0]
0064ade9 call 0x6ea7f0
0064adee lea ecx, [edi + 0x334]
0064adf4 push 6
0064adf6 call 0x7a7d50
0064adfb mov ecx, dword ptr [0xbfd65c]
0064ae01 mov dword ptr [ebp - 0x668], eax
0064ae07 call 0x4023f0
0064ae0c mov ecx, eax
0064ae0e call 0x427750
0064ae13 xor ecx, ecx
0064ae15 cmp esi, eax
0064ae17 sete cl
0064ae1a lea ecx, [ecx*2 + 2]
0064ae21 mov dword ptr [ebp - 0x680], ecx
0064ae27 jne 0x64ae63
0064ae29 push 0x14
0064ae2b lea ecx, [edi + 0x334]
0064ae31 call 0x7a7d50
0064ae36 test eax, eax
0064ae38 jne 0x64ae63
0064ae3a mov ecx, dword ptr [0xbfd680]
0064ae40 push 0x143
0064ae45 call 0x41c4a0
0064ae4a mov ecx, eax
0064ae4c call 0x884da0
0064ae51 mov esi, dword ptr [ebp - 0x680]
0064ae57 test al, al
0064ae59 mov eax, 0x16
0064ae5e cmovne esi, eax
0064ae61 jmp 0x64ae69
0064ae63 mov esi, dword ptr [ebp - 0x680]
0064ae69 mov eax, dword ptr [ebp - 0x668]
0064ae6f mov dword ptr [ebp - 0x674], 0
0064ae79 cmp eax, 4
0064ae7c ja 0x64af38
0064ae82 jmp dword ptr [eax*4 + 0x64dc7c]
0064ae89 lea ecx, [edi + 0x334]
0064ae8f call 0x7a7db0
0064ae94 movss xmm0, dword ptr [ebp - 0x6c4]
0064ae9c mov esi, 0xe
0064aea1 fstp dword ptr [ebp - 0x668]
0064aea7 movss xmm1, dword ptr [ebp - 0x668]
0064aeaf comiss xmm0, xmm1
0064aeb2 ja 0x64af38
0064aeb8 movss xmm0, dword ptr [0xb6a560]
0064aec0 comiss xmm0, xmm1
0064aec3 jbe 0x64aed1
0064aec5 mov dword ptr [ebp - 0x674], 2
0064aecf jmp 0x64af38
0064aed1 movss xmm0, dword ptr [0xb6a5d8]
0064aed9 comiss xmm0, xmm1
0064aedc jbe 0x64aeea
0064aede mov dword ptr [ebp - 0x674], 1
0064aee8 jmp 0x64af38
0064aeea movss xmm0, dword ptr [0xb6a5f8]
0064aef2 comiss xmm0, xmm1
0064aef5 jbe 0x64af03
0064aef7 mov dword ptr [ebp - 0x674], 5
0064af01 jmp 0x64af38
0064af03 movss xmm0, dword ptr [0xb6a604]
0064af0b xor eax, eax
0064af0d comiss xmm0, xmm1
0064af10 seta al
0064af13 add eax, 3
0064af16 mov dword ptr [ebp - 0x674], eax
0064af1c jmp 0x64af38
0064af1e mov esi, 5
0064af23 jmp 0x64af38
0064af25 mov esi, 6
0064af2a jmp 0x64af38
0064af2c mov esi, 3
0064af31 jmp 0x64af38
0064af33 mov esi, 0xc
0064af38 mov ecx, dword ptr [0xbfd65c]
0064af3e push 0
0064af40 push dword ptr [ebp - 0x678]
0064af46 call 0x4023f0
0064af4b mov ecx, eax
0064af4d call 0x447f10
0064af52 push 0
0064af54 lea ecx, [edi + 0x334]
0064af5a call 0x7a7e20
0064af5f mov ecx, dword ptr [0xbfd65c]
0064af65 push eax
0064af66 push dword ptr [ebp - 0x674]
0064af6c push esi
0064af6d push dword ptr [ebp - 0x678]
0064af73 call 0x4023f0
0064af78 mov ecx, eax
0064af7a call 0x7aa9b0
0064af7f jmp 0x64b2b4
0064af84 cmp byte ptr [edi + 0x188], 0
0064af8b je 0x64afc8
0064af8d movss xmm0, dword ptr [edi + 0x360]
0064af95 comiss xmm0, dword ptr [0xb6af34]
0064af9c jbe 0x64afc8
0064af9e push 0xbc4ce0
0064afa3 lea edx, [edi + 0x378]
0064afa9 lea ecx, [ebp - 0x1bf4]
0064afaf call 0x412050
0064afb4 add esp, 4
0064afb7 mov ecx, eax
0064afb9 call 0x427260
0064afbe test al, al
0064afc0 je 0x64afc8
0064afc2 cmp dword ptr [edi + 0x2c], 9
0064afc6 jne 0x64b039
0064afc8 push dword ptr [esi + 4]
0064afcb mov ecx, dword ptr [0xbfd65c]
0064afd1 push dword ptr [esi]
0064afd3 call 0x4023f0
0064afd8 mov ecx, eax
0064afda call 0x7aee40
0064afdf cmp eax, 4
0064afe2 je 0x64b022
0064afe4 push dword ptr [esi + 4]
0064afe7 mov ecx, dword ptr [0xbfd65c]
0064afed push dword ptr [esi]
0064afef call 0x4023f0
0064aff4 mov ecx, eax
0064aff6 call 0x7aee40
0064affb cmp eax, 5
0064affe jne 0x64b2b4
0064b004 mov ecx, dword ptr [0xbfd65c]
0064b00a push esi
0064b00b call 0x4023f0
0064b010 mov ecx, eax
0064b012 call 0x7ce8d0
0064b017 cmp eax, 0xbb8
0064b01c jge 0x64b2b4
0064b022 cmp byte ptr [edi + 0x188], 0
0064b029 je 0x64b2b4
0064b02f cmp dword ptr [edi + 0x2c], 9
0064b033 je 0x64b2be
0064b039 push 0xbc4cc0
0064b03e lea edx, [edi + 0x378]
0064b044 lea ecx, [ebp - 0x1c04]
0064b04a call 0x412050
0064b04f add esp, 4
0064b052 mov ecx, eax
0064b054 call 0x427260
0064b059 test al, al
0064b05b je 0x64b2b4
0064b061 push 0xbc4950
0064b066 lea edx, [edi + 0x378]
0064b06c lea ecx, [ebp - 0x1c14]
0064b072 call 0x412050
0064b077 add esp, 4
0064b07a mov ecx, eax
0064b07c call 0x427260
0064b081 test al, al
0064b083 je 0x64b0cd
0064b085 push 0xbc4b50
0064b08a lea edx, [edi + 0x378]
0064b090 lea ecx, [ebp - 0x1c24]
0064b096 call 0x412050
0064b09b add esp, 4
0064b09e mov ecx, eax
0064b0a0 call 0x427260
0064b0a5 test al, al
0064b0a7 je 0x64b0cd
0064b0a9 push 0xbc4830
0064b0ae lea edx, [edi + 0x378]
0064b0b4 lea ecx, [ebp - 0x1c34]
0064b0ba call 0x412050
0064b0bf add esp, 4
0064b0c2 mov ecx, eax
0064b0c4 call 0x427260
0064b0c9 test al, al
0064b0cb jne 0x64b0da
0064b0cd cmp dword ptr [edi + 0x3c8], 0
0064b0d4 jne 0x64b2b4
0064b0da mov ecx, dword ptr [0xbfd65c]
0064b0e0 mov byte ptr [edi + 0x16b], 1
0064b0e7 or dword ptr [edi + 0x3c4], 1
0064b0ee push dword ptr [esi + 4]
0064b0f1 push dword ptr [esi]
0064b0f3 call 0x4023f0
0064b0f8 mov ecx, eax
0064b0fa call 0x7aee40
0064b0ff cmp eax, 4
0064b102 je 0x64b120
0064b104 push dword ptr [esi + 4]
0064b107 mov ecx, dword ptr [0xbfd65c]
0064b10d push dword ptr [esi]
0064b10f call 0x4023f0
0064b114 mov ecx, eax
0064b116 call 0x7aee40
0064b11b cmp eax, 5
0064b11e jne 0x64b127
0064b120 or dword ptr [edi + 0x3c4], 2
0064b127 push 0
0064b129 mov ecx, edi
0064b12b call 0x650dd0
0064b130 push esi
0064b131 mov ecx, edi
0064b133 call 0x656f30
0064b138 mov ecx, dword ptr [edi + 0x314]
0064b13e test ecx, ecx
0064b140 je 0x64b2b4
0064b146 cmp byte ptr [edi + 0x738], 0
0064b14d je 0x64b2b4
0064b153 call 0x4866c0
0064b158 mov dword ptr [ebp - 0x668], eax
0064b15e test eax, eax
0064b160 je 0x64b2b4
0064b166 mov ecx, dword ptr [0xbfd65c]
0064b16c push esi
0064b16d call 0x4023f0
0064b172 mov ecx, eax
0064b174 call 0x447f80
0064b179 mov esi, eax
0064b17b test esi, esi
0064b17d je 0x64b19f
0064b17f mov ecx, esi
0064b181 call 0x402360
0064b186 cmp eax, 0xe
0064b189 je 0x64b2b4
0064b18f mov ecx, esi
0064b191 call 0x402360
0064b196 cmp eax, 0xc
0064b199 je 0x64b2b4
0064b19f mov esi, dword ptr [ebp - 0x668]
0064b1a5 mov ecx, esi
0064b1a7 call 0x78d2d0
0064b1ac push 0
0064b1ae push 0x175
0064b1b3 mov ecx, esi
0064b1b5 call 0x73af30
0064b1ba test al, al
0064b1bc je 0x64b2b4
0064b1c2 mov ecx, esi
0064b1c4 call 0x78a720
0064b1c9 jmp 0x64b2b4
0064b1ce push 0xbc4cc0
0064b1d3 lea edx, [edi + 0x378]
0064b1d9 lea ecx, [ebp - 0x1c44]
0064b1df call 0x412050
0064b1e4 add esp, 4
0064b1e7 mov ecx, eax
0064b1e9 call 0x412090
0064b1ee test al, al
0064b1f0 mov ecx, 6
0064b1f5 mov eax, 3
0064b1fa cmovne ecx, eax
0064b1fd mov dword ptr [edi + 0x17c], ecx
0064b203 cmp byte ptr [edi + 0x188], 0
0064b20a je 0x64b2b4
0064b210 lea esi, [edi + 0x2b8]
0064b216 push esi
0064b217 lea eax, [ebp - 0x105c]
0064b21d push eax
0064b21e lea ecx, [edi + 0x294]
0064b224 call 0x962ac0
0064b229 push eax
0064b22a mov ecx, edi
0064b22c call 0x656f30
0064b231 mov ecx, esi
0064b233 call 0x9624f0
0064b238 lea ecx, [edi + 0x18c]
0064b23e call 0x962a00
0064b243 lea eax, [ebp - 0x8b4]
0064b249 mov ecx, esi
0064b24b push eax
0064b24c fstp dword ptr [ebp - 0x8b4]
0064b252 call 0x962bb0
0064b257 lea eax, [ebp - 0x1c54]
0064b25d mov ecx, 0xbc46a0
0064b262 push eax
0064b263 call 0x57f3a0
0064b268 push eax
0064b269 lea ecx, [edi + 0x378]
0064b26f call 0x6413c0
0064b274 push 0
0064b276 lea ecx, [edi + 0x394]
0064b27c call 0x4d1fd0
0064b281 mov ecx, dword ptr [0xbfd65c]
0064b287 call 0x4023f0
0064b28c mov ecx, eax
0064b28e call 0x7a8ca0
0064b293 test al, al
0064b295 je 0x64b2b4
0064b297 lea eax, [ebp - 0x1c64]
0064b29d mov ecx, 0xbc4c10
0064b2a2 push eax
0064b2a3 call 0x57f3a0
0064b2a8 push eax
0064b2a9 lea ecx, [edi + 0x378]
0064b2af call 0x6413c0
0064b2b4 cmp dword ptr [edi + 0x2c], 9
0064b2b8 jne 0x64b475
0064b2be cmp byte ptr [edi + 0x16b], 0
0064b2c5 lea esi, [edi + 0x294]
0064b2cb jne 0x64b47b
0064b2d1 mov ecx, dword ptr [0xbfd65c]
0064b2d7 lea eax, [ebp - 0xb74]
0064b2dd sub esp, 0xc
0064b2e0 mov dword ptr [esp + 8], 0xc2200000
0064b2e8 mov dword ptr [esp + 4], 0xc1a00000
0064b2f0 mov dword ptr [esp], 0xbf800000
0064b2f7 push esi
0064b2f8 push eax
0064b2f9 call 0x4023f0
0064b2fe movss xmm3, dword ptr [ebp - 0x6ac]
0064b306 mov ecx, eax
0064b308 call 0x7cec10
0064b30d push esi
0064b30e lea ecx, [ebp - 0xb74]
0064b314 call 0x962ca0
0064b319 test al, al
0064b31b je 0x64b445
0064b321 mov ecx, dword ptr [0xbfd65c]
0064b327 lea eax, [ebp - 0xa64]
0064b32d push eax
0064b32e call 0x4023f0
0064b333 mov ecx, eax
0064b335 call 0x432630
0064b33a mov ecx, dword ptr [0xbfd65c]
0064b340 lea eax, [ebp - 0xa6c]
0064b346 push eax
0064b347 call 0x4023f0
0064b34c mov ecx, eax
0064b34e call 0x432650
0064b353 push 0
0064b355 push 0xb46b08
0064b35a lea ecx, [edi + 0x3c]
0064b35d call 0x4054f0
0064b362 movss xmm1, dword ptr [esi]
0064b366 movss xmm0, dword ptr [ebp - 0xa64]
0064b36e comiss xmm0, xmm1
0064b371 jbe 0x64b392
0064b373 push ecx
0064b374 lea ecx, [edi + 0x3c]
0064b377 mov dword ptr [esp], 0x42b40000
0064b37e call 0x430cc0
0064b383 push 1
0064b385 lea ecx, [edi + 0x3c]
0064b388 call 0x427280
0064b38d jmp 0x64b413
0064b392 comiss xmm1, dword ptr [ebp - 0xa6c]
0064b399 jbe 0x64b3ad
0064b39b push ecx
0064b39c lea ecx, [edi + 0x3c]
0064b39f mov dword ptr [esp], 0x42b40000
0064b3a6 call 0x430cc0
0064b3ab jmp 0x64b413
0064b3ad movss xmm1, dword ptr [edi + 0x298]
0064b3b5 movss xmm0, dword ptr [ebp - 0xa60]
0064b3bd comiss xmm0, xmm1
0064b3c0 jbe 0x64b3e2
0064b3c2 movss xmm0, dword ptr [ebp - 0x67c]
0064b3ca lea ecx, [edi + 0x3c]
0064b3cd comiss xmm0, dword ptr [edi + 0x2b8]
0064b3d4 seta al
0064b3d7 movzx eax, al
0064b3da push eax
0064b3db call 0x427280
0064b3e0 jmp 0x64b413
0064b3e2 comiss xmm1, dword ptr [ebp - 0xa68]
0064b3e9 jbe 0x64b413
0064b3eb movss xmm0, dword ptr [edi + 0x2b8]
0064b3f3 lea ecx, [edi + 0x3c]
0064b3f6 comiss xmm0, dword ptr [ebp - 0x67c]
0064b3fd seta al
0064b400 movzx eax, al
0064b403 push eax
0064b404 call 0x427280
0064b409 push 1
0064b40b lea ecx, [edi + 0x3c]
0064b40e call 0x4f3dd0
0064b413 push 0xc02fec
0064b418 lea ecx, [edi + 0x2b8]
0064b41e call 0x962cd0
0064b423 mov dword ptr [edi + 0x17c], 0
0064b42d mov dword ptr [edi + 0x180], 0
0064b437 mov byte ptr [edi + 0x16b], 1
0064b43e or dword ptr [edi + 0x3c4], 3
0064b445 mov ecx, dword ptr [0xbfd65c]
0064b44b push esi
0064b44c call 0x4023f0
0064b451 mov ecx, eax
0064b453 call 0x7ce950
0064b458 test eax, eax
0064b45a js 0x64b47b
0064b45c mov ecx, dword ptr [0xbfd65c]
0064b462 push 0
0064b464 push 0
0064b466 push eax
0064b467 call 0x4023f0
0064b46c mov ecx, eax
0064b46e call 0x7cf710
0064b473 jmp 0x64b47b
0064b475 lea esi, [edi + 0x294]
0064b47b mov eax, dword ptr [edi + 0x2c]
0064b47e cmp eax, 0x2b
0064b481 je 0x64b48c
0064b483 cmp eax, 0x2c
0064b486 jne 0x64b87c
0064b48c cmp byte ptr [edi + 0x16b], 0
0064b493 jne 0x64b87c
0064b499 mov ecx, dword ptr [edi + 0x320]
0064b49f call 0x4866c0
0064b4a4 mov dword ptr [ebp - 0x680], eax
0064b4aa test eax, eax
0064b4ac je 0x64b87c
0064b4b2 lea eax, [edi + 0x2b8]
0064b4b8 mov ecx, esi
0064b4ba push eax
0064b4bb lea eax, [ebp - 0x790]
0064b4c1 push eax
0064b4c2 call 0x962a60
0064b4c7 push 0xc02fec
0064b4cc lea ecx, [edi + 0x2b8]
0064b4d2 call 0x962ca0
0064b4d7 test al, al
0064b4d9 je 0x64b50e
0064b4db lea eax, [edi + 0x2c8]
0064b4e1 push eax
0064b4e2 lea eax, [ebp - 0x1064]
0064b4e8 push eax
0064b4e9 lea eax, [ebp - 0x106c]
0064b4ef push eax
0064b4f0 lea ecx, [edi + 0x2b8]
0064b4f6 call 0x962560
0064b4fb mov ecx, eax
0064b4fd call 0x962b50
0064b502 push eax
0064b503 lea ecx, [ebp - 0x790]
0064b509 call 0x962a90
0064b50e mov ecx, dword ptr [0xbfd65c]
0064b514 call 0x4023f0
0064b519 lea ecx, [ebp - 0x790]
0064b51f mov dword ptr [ebp - 0x688], eax
0064b525 push ecx
0064b526 mov ecx, eax
0064b528 call 0x7ce950
0064b52d test eax, eax
0064b52f js 0x64b76e
0064b535 mov ecx, dword ptr [ebp - 0x688]
0064b53b push eax
0064b53c call 0x4276e0
0064b541 push dword ptr [ebp - 0x78c]
0064b547 mov ecx, dword ptr [ebp - 0x688]
0064b54d push dword ptr [ebp - 0x790]
0064b553 mov dword ptr [ebp - 0x698], eax
0064b559 call 0x7aee40
0064b55e mov dword ptr [ebp - 0x6ac], eax
0064b564 mov eax, dword ptr [edi + 0x17c]
0064b56a mov dword ptr [ebp - 0x670], eax
0064b570 mov eax, dword ptr [ebp - 0x698]
0064b576 test eax, eax
0064b578 je 0x64b76e
0064b57e mov ecx, eax
0064b580 call 0x402360
0064b585 cmp eax, 0x10
0064b588 jne 0x64b625
0064b58e cmp dword ptr [ebp - 0x6ac], 4
0064b595 jne 0x64b625
0064b59b mov ecx, dword ptr [ebp - 0x698]
0064b5a1 call 0x427640
0064b5a6 test al, al
0064b5a8 je 0x64b5d1
0064b5aa mov ecx, dword ptr [ebp - 0x698]
0064b5b0 call 0x427670
0064b5b5 test al, al
0064b5b7 jne 0x64b5d1
0064b5b9 mov ecx, dword ptr [ebp - 0x698]
0064b5bf push 1
0064b5c1 push dword ptr [ebp - 0x680]
0064b5c7 call 0x6e0bc0
0064b5cc jmp 0x64b65b
0064b5d1 mov ecx, dword ptr [ebp - 0x698]
0064b5d7 push 7
0064b5d9 call 0x5b7550
0064b5de test al, al
0064b5e0 jne 0x64b614
0064b5e2 mov ecx, dword ptr [ebp - 0x698]
0064b5e8 push 8
0064b5ea call 0x5b7550
0064b5ef test al, al
0064b5f1 jne 0x64b614
0064b5f3 mov ecx, dword ptr [ebp - 0x698]
0064b5f9 call 0x4083d0
0064b5fe cmp eax, 2
0064b601 je 0x64b76e
0064b607 mov ecx, dword ptr [ebp - 0x698]
0064b60d call 0x6e1450
0064b612 jmp 0x64b65b
0064b614 mov ecx, dword ptr [ebp - 0x698]
0064b61a push 0
0064b61c mov eax, dword ptr [ecx]
0064b61e mov eax, dword ptr [eax + 0x14]
0064b621 call eax
0064b623 jmp 0x64b65b
0064b625 mov ecx, dword ptr [ebp - 0x698]
0064b62b call 0x402360
0064b630 cmp eax, 0xb
0064b633 jne 0x64b674
0064b635 mov ecx, dword ptr [ebp - 0x698]
0064b63b call 0x4083d0
0064b640 test eax, eax
0064b642 jne 0x64b76e
0064b648 mov ecx, dword ptr [ebp - 0x698]
0064b64e push 1
0064b650 push dword ptr [ebp - 0x680]
0064b656 call 0x6e2080
0064b65b cmp dword ptr [ebp - 0x670], 4
0064b662 jne 0x64b76e
0064b668 mov ecx, edi
0064b66a call 0x436b60
0064b66f jmp 0x64b76e
0064b674 mov eax, dword ptr [ebp - 0x6ac]
0064b67a cmp eax, 3
0064b67d je 0x64b688
0064b67f cmp eax, 2
0064b682 jne 0x64b76e
0064b688 mov ecx, dword ptr [ebp - 0x698]
0064b68e call 0x4866d0
0064b693 cmp eax, 3
0064b696 jne 0x64b76e
0064b69c cmp dword ptr [ebp - 0x670], 4
0064b6a3 je 0x64b6b5
0064b6a5 lea ecx, [eax + 5]
0064b6a8 call 0x659230
0064b6ad test eax, eax
0064b6af jne 0x64b76e
0064b6b5 mov ecx, dword ptr [ebp - 0x698]
0064b6bb push 0
0064b6bd mov eax, dword ptr [ecx]
0064b6bf mov eax, dword ptr [eax + 0x14]
0064b6c2 call eax
0064b6c4 test al, al
0064b6c6 je 0x64b76e
0064b6cc cmp dword ptr [ebp - 0x670], 4
0064b6d3 jne 0x64b6dc
0064b6d5 mov ecx, edi
0064b6d7 call 0x436b60
0064b6dc mov ecx, dword ptr [ebp - 0x698]
0064b6e2 lea eax, [ebp - 0xa74]
0064b6e8 push eax
0064b6e9 call 0x6dae90
0064b6ee push esi
0064b6ef lea eax, [ebp - 0x1074]
0064b6f5 mov dword ptr [ebp - 0x8b8], 0x42200000
0064b6ff push eax
0064b700 lea ecx, [ebp - 0xa74]
0064b706 call 0x962ac0
0064b70b mov edx, eax
0064b70d lea ecx, [ebp - 0x107c]
0064b713 call 0x6593a0
0064b718 push eax
0064b719 lea edx, [ebp - 0x8b8]
0064b71f lea ecx, [ebp - 0x1084]
0064b725 call 0x4120b0
0064b72a add esp, 4
0064b72d lea ecx, [ebp - 0xa74]
0064b733 push eax
0064b734 lea eax, [ebp - 0x108c]
0064b73a push eax
0064b73b call 0x962a60
0064b740 mov ecx, dword ptr [ebp - 0x688]
0064b746 push eax
0064b747 call 0x7ce950
0064b74c test eax, eax
0064b74e js 0x64b76e
0064b750 push dword ptr [ebp - 0x698]
0064b756 mov ecx, dword ptr [ebp - 0x688]
0064b75c push eax
0064b75d call 0x4276e0
0064b762 mov ecx, dword ptr [ebp - 0x688]
0064b768 push eax
0064b769 call 0x7d9890
0064b76e mov ecx, dword ptr [ebp - 0x688]
0064b774 lea eax, [ebp - 0xaac]
0064b77a push 0x10
0064b77c push esi
0064b77d push eax
0064b77e call 0x422d70
0064b783 movss xmm3, dword ptr [0xb6a9e8]
0064b78b mov ecx, eax
0064b78d call 0x4157f0
0064b792 lea ecx, [ebp - 0xaac]
0064b798 mov dword ptr [ebp - 4], 7
0064b79f call 0x4083d0
0064b7a4 test eax, eax
0064b7a6 je 0x64b86a
0064b7ac mov edi, dword ptr [ebp - 0x680]
0064b7b2 xor esi, esi
0064b7b4 push esi
0064b7b5 lea ecx, [ebp - 0xaac]
0064b7bb call 0x4124b0
0064b7c0 mov eax, dword ptr [eax]
0064b7c2 mov dword ptr [ebp - 0x688], eax
0064b7c8 test eax, eax
0064b7ca je 0x64b84a
0064b7d0 mov ecx, eax
0064b7d2 call 0x422c00
0064b7d7 test al, al
0064b7d9 je 0x64b819
0064b7db mov ecx, dword ptr [ebp - 0x688]
0064b7e1 call 0x412110
0064b7e6 cmp eax, 0x3c
0064b7e9 je 0x64b80b
0064b7eb mov ecx, dword ptr [ebp - 0x688]
0064b7f1 call 0x412110
0064b7f6 cmp eax, 0x35
0064b7f9 je 0x64b80b
0064b7fb mov ecx, dword ptr [ebp - 0x688]
0064b801 call 0x412110
0064b806 cmp eax, 0x37
0064b809 jne 0x64b819
0064b80b mov ecx, dword ptr [ebp - 0x688]
0064b811 push edi
0064b812 call 0x6bd410
0064b817 jmp 0x64b84a
0064b819 mov ecx, dword ptr [ebp - 0x688]
0064b81f call 0x427410
0064b824 test al, al
0064b826 je 0x64b84a
0064b828 mov ecx, dword ptr [ebp - 0x688]
0064b82e call 0x412110
0064b833 cmp eax, 7
0064b836 jne 0x64b84a
0064b838 mov edx, dword ptr [ebp - 0x688]
0064b83e mov ecx, edi
0064b840 push 1
0064b842 call 0x68a330
0064b847 add esp, 4
0064b84a lea ecx, [ebp - 0xaac]
0064b850 inc esi
0064b851 call 0x4083d0
0064b856 cmp esi, eax
0064b858 jb 0x64b7b4
0064b85e mov edi, dword ptr [ebp - 0x6a8]
0064b864 lea esi, [edi + 0x294]
0064b86a lea ecx, [ebp - 0xaac]
0064b870 mov dword ptr [ebp - 4], 0xffffffff
0064b877 call 0x412490
0064b87c push 0xbc4ce0
0064b881 lea edx, [edi + 0x378]
0064b887 lea ecx, [ebp - 0x1c74]
0064b88d call 0x412050
0064b892 add esp, 4
0064b895 mov ecx, eax
0064b897 call 0x412090
0064b89c test al, al
0064b89e je 0x64c5dc
0064b8a4 mov eax, dword ptr [edi + 0x30]
0064b8a7 mov ecx, edi
0064b8a9 shr eax, 1
0064b8ab and eax, 0xffffff01
0064b8b0 mov dword ptr [ebp - 0x674], eax
0064b8b6 call 0x6520e0
0064b8bb cmp byte ptr [ebp - 0x674], 0
0064b8c2 mov byte ptr [ebp - 0x68d], al
0064b8c8 je 0x64b8d4
0064b8ca movss xmm0, dword ptr [0xb6a604]
0064b8d2 jmp 0x64b8dc
0064b8d4 movss xmm0, dword ptr [0xb6a50c]
0064b8dc mulss xmm0, dword ptr [edi + 0x2c4]
0064b8e4 mov ecx, edi
0064b8e6 movss dword ptr [edi + 0x2c4], xmm0
0064b8ee call 0x6414a0
0064b8f3 mov dword ptr [ebp - 0x670], eax
0064b8f9 test eax, eax
0064b8fb je 0x64b906
0064b8fd mov ecx, eax
0064b8ff call 0x5b7690
0064b904 jmp 0x64b90e
0064b906 movss xmm0, dword ptr [0xb6a974]
0064b90e push 0xbc4a10
0064b913 lea edx, [edi + 0x378]
0064b919 movss dword ptr [ebp - 0x6ac], xmm0
0064b921 lea ecx, [ebp - 0x1c84]
0064b927 call 0x412050
0064b92c add esp, 4
0064b92f mov ecx, eax
0064b931 call 0x412090
0064b936 test al, al
0064b938 je 0x64b984
0064b93a cmp dword ptr [ebp - 0x670], 0
0064b941 jne 0x64b952
0064b943 push 0
0064b945 push 0xc
0064b947 xor ecx, ecx
0064b949 call 0x73b950
0064b94e test al, al
0064b950 jne 0x64b984
0064b952 movss xmm2, dword ptr [ebp - 0x684]
0064b95a lea ecx, [ebp - 0x1094]
0064b960 movaps xmm1, xmm2
0064b963 call 0x9624e0
0064b968 push eax
0064b969 lea ecx, [edi + 0x2cc]
0064b96f call 0x962cd0
0064b974 push 0xbc4a10
0064b979 lea ecx, [edi + 0x378]
0064b97f call 0x6413f0
0064b984 mov ecx, dword ptr [edi + 0x314]
0064b98a test ecx, ecx
0064b98c je 0x64b9af
0064b98e call 0x427400
0064b993 test al, al
0064b995 je 0x64b9af
0064b997 movss xmm0, dword ptr [ebp - 0x6b4]
0064b99f mulss xmm0, dword ptr [ebp - 0x6bc]
0064b9a7 movss dword ptr [ebp - 0x6b4], xmm0
0064b9af lea ecx, [edi + 0x2b8]
0064b9b5 call 0x962a00
0064b9ba cmp byte ptr [ebp - 0x674], 0
0064b9c1 fstp dword ptr [ebp - 0x680]
0064b9c7 je 0x64ba0b
0064b9c9 movss xmm3, dword ptr [0xb6a5a4]
0064b9d1 movss xmm2, dword ptr [0xb6a9c8]
0064b9d9 movss xmm1, dword ptr [0xb6a974]
0064b9e1 movss xmm0, dword ptr [ebp - 0x680]
0064b9e9 push ecx
0064b9ea mov cl, 1
0064b9ec mov dword ptr [esp], 0x40000000
0064b9f3 call 0x962420
0064b9f8 mulss xmm0, dword ptr [ebp - 0x6b4]
0064ba00 add esp, 4
0064ba03 movss dword ptr [ebp - 0x6b4], xmm0
0064ba0b movss xmm2, dword ptr [ebp - 0x67c]
0064ba13 mov ecx, edi
0064ba15 movss xmm1, dword ptr [ebp - 0x6ac]
0064ba1d call 0x6847e0
0064ba22 mov dword ptr [ebp - 0x6bc], eax
0064ba28 test eax, eax
0064ba2a je 0x64bde0
0064ba30 push 0
0064ba32 lea ecx, [edi + 0x394]
0064ba38 call 0x4d1fd0
0064ba3d push esi
0064ba3e mov ecx, edi
0064ba40 call 0x656f30
0064ba45 cmp dword ptr [ebp - 0x670], 0
0064ba4c je 0x64bde0
0064ba52 push dword ptr [edi + 0x320]
0064ba58 mov ecx, 2
0064ba5d call 0x659230
0064ba62 lea eax, [eax*2 - 1]
0064ba69 push eax
0064ba6a push ecx
0064ba6b mov ecx, dword ptr [ebp - 0x670]
0064ba71 lea eax, [ebp - 0xd0]
0064ba77 mov dword ptr [esp], 0x3f800000
0064ba7e push 8
0064ba80 push eax
0064ba81 call 0x7836a0
0064ba86 mov dword ptr [edi + 0x3d4], 0
0064ba90 mov eax, dword ptr [ebp - 0xd0]
0064ba96 cmp dword ptr [edi + 0x2c], eax
0064ba99 je 0x64bb04
0064ba9f mov dword ptr [edi + 0x2c], eax
0064baa2 mov ecx, dword ptr [ebp - 0xd0]
0064baa8 call 0x641680
0064baad test al, al
0064baaf je 0x64bb04
0064bab1 mov ecx, edi
0064bab3 call 0x681ea0
0064bab8 mov dword ptr [edi + 0x17c], 0
0064bac2 mov eax, dword ptr [edi + 0x288]
0064bac8 test eax, eax
0064baca je 0x64bb04
0064bacc push 1
0064bace add eax, 0x74
0064bad1 lea ecx, [edi + 0x3c]
0064bad4 push eax
0064bad5 call 0x407160
0064bada push 0
0064badc lea ecx, [edi + 0x3c]
0064badf call 0x4921f0
0064bae4 push eax
0064bae5 lea ecx, [edi + 0x3c]
0064bae8 call 0x4054d0
0064baed push ecx
0064baee lea ecx, [edi + 0x3c]
0064baf1 mov dword ptr [esp], 0
0064baf8 call 0x430cc0
0064bafd mov ecx, edi
0064baff call 0x651770
0064bb04 cmp byte ptr [ebp - 0x674], 0
0064bb0b je 0x64bbaa
0064bb11 movss xmm0, dword ptr [ebp - 0x680]
0064bb19 movss xmm1, dword ptr [0xb6a974]
0064bb21 comiss xmm0, xmm1
0064bb24 jbe 0x64bb9a
0064bb2a movss xmm3, dword ptr [ebp - 0x684]
0064bb32 movss xmm2, dword ptr [0xb6a9c8]
0064bb3a push ecx
0064bb3b mov cl, 1
0064bb3d mov dword ptr [esp], 0x40c00000
0064bb44 call 0x962420
0064bb49 mulss xmm0, dword ptr [ebp - 0x88]
0064bb51 mov cl, 1
0064bb53 mov dword ptr [esp], 0x40c00000
0064bb5a movss xmm3, dword ptr [ebp - 0x67c]
0064bb62 movss xmm2, dword ptr [ebp - 0x6e0]
0064bb6a movss xmm1, dword ptr [0xb6a974]
0064bb72 movss dword ptr [ebp - 0x88], xmm0
0064bb7a movss xmm0, dword ptr [ebp - 0x680]
0064bb82 call 0x962420
0064bb87 addss xmm0, dword ptr [ebp - 0x88]
0064bb8f add esp, 4
0064bb92 movss dword ptr [ebp - 0x88], xmm0
0064bb9a push 0xbc4cc0
0064bb9f lea ecx, [ebp - 0x98]
0064bba5 call 0x4271f0
0064bbaa mov eax, dword ptr [edi]
0064bbac lea edx, [ebp - 0xc8]
0064bbb2 movss xmm0, dword ptr [ebp - 0x88]
0064bbba mov ecx, edi
0064bbbc push 1
0064bbbe push 0
0064bbc0 mov eax, dword ptr [eax + 0x38]
0064bbc3 push 0xff
0064bbc8 push -1
0064bbca push edx
0064bbcb movss dword ptr [edi + 0x2e0], xmm0
0064bbd3 call eax
0064bbd5 push 0xbc4ce0
0064bbda lea eax, [ebp - 0x1c94]
0064bbe0 mov ecx, 0xbc4c10
0064bbe5 push eax
0064bbe6 call 0x57f3a0
0064bbeb push eax
0064bbec lea edx, [ebp - 0x98]
0064bbf2 lea ecx, [ebp - 0x1ca4]
0064bbf8 call 0x412050
0064bbfd add esp, 4
0064bc00 lea ecx, [ebp - 0x1cb4]
0064bc06 mov edx, eax
0064bc08 call 0x427220
0064bc0d sub esp, 0xc
0064bc10 mov ecx, esp
0064bc12 movups xmm0, xmmword ptr [eax]
0064bc15 movups xmmword ptr [ecx], xmm0
0064bc18 mov ecx, edi
0064bc1a call 0x650280
0064bc1f cmp byte ptr [ebp - 0x68d], 0
0064bc26 je 0x64bd36
0064bc2c push 0xbc4bc0
0064bc31 lea edx, [edi + 0x378]
0064bc37 lea ecx, [ebp - 0x1cc4]
0064bc3d call 0x412050
0064bc42 add esp, 4
0064bc45 mov ecx, eax
0064bc47 call 0x412090
0064bc4c test al, al
0064bc4e je 0x64bcad
0064bc50 mov ecx, dword ptr [edi + 0x314]
0064bc56 lea eax, [ebp - 0x109c]
0064bc5c push esi
0064bc5d push eax
0064bc5e call 0x412130
0064bc63 mov ecx, eax
0064bc65 call 0x9626f0
0064bc6a movss xmm1, dword ptr [0xb6acb4]
0064bc72 movss xmm0, dword ptr [ebp - 0x684]
0064bc7a fstp dword ptr [ebp - 0x668]
0064bc80 movss xmm2, dword ptr [ebp - 0x668]
0064bc88 call 0x9623e0
0064bc8d divss xmm0, dword ptr [0xb6acb4]
0064bc95 addss xmm0, dword ptr [ebp - 0x684]
0064bc9d mulss xmm0, dword ptr [edi + 0x2e0]
0064bca5 movss dword ptr [edi + 0x2e0], xmm0
0064bcad push 0xbc4c60
0064bcb2 lea edx, [edi + 0x378]
0064bcb8 lea ecx, [ebp - 0x1cd4]
0064bcbe call 0x412050
0064bcc3 add esp, 4
0064bcc6 mov ecx, eax
0064bcc8 call 0x412090
0064bccd test al, al
0064bccf je 0x64bd36
0064bcd5 mov ecx, dword ptr [edi + 0x314]
0064bcdb lea eax, [ebp - 0x10a4]
0064bce1 push esi
0064bce2 push eax
0064bce3 call 0x412130
0064bce8 mov ecx, eax
0064bcea call 0x9626f0
0064bcef movss xmm1, dword ptr [0xb6acb4]
0064bcf7 movss xmm0, dword ptr [ebp - 0x67c]
0064bcff fstp dword ptr [ebp - 0x668]
0064bd05 movss xmm2, dword ptr [ebp - 0x668]
0064bd0d call 0x9623e0
0064bd12 divss xmm0, dword ptr [0xb6acc4]
0064bd1a movss xmm1, dword ptr [ebp - 0x684]
0064bd22 subss xmm1, xmm0
0064bd26 mulss xmm1, dword ptr [edi + 0x2e0]
0064bd2e movss dword ptr [edi + 0x2e0], xmm1
0064bd36 push 0xbc4c00
0064bd3b lea edx, [edi + 0x378]
0064bd41 lea ecx, [ebp - 0x1ce4]
0064bd47 call 0x412050
0064bd4c add esp, 4
0064bd4f mov ecx, eax
0064bd51 call 0x412090
0064bd56 test al, al
0064bd58 je 0x64bde0
0064bd5e mov ecx, dword ptr [ebp - 0x670]
0064bd64 call 0x422d80
0064bd69 cmp eax, -1
0064bd6c je 0x64bde0
0064bd72 cmp dword ptr [ebp - 0x6bc], 0
0064bd79 jle 0x64bde0
0064bd7f nop 
0064bd80 mov ecx, dword ptr [ebp - 0x670]
0064bd86 call 0x427830
0064bd8b mulss xmm0, dword ptr [0xb6a974]
0064bd93 lea eax, [ebp - 0x10ac]
0064bd99 push eax
0064bd9a movss dword ptr [ebp - 0x8bc], xmm0
0064bda2 call 0x659290
0064bda7 push eax
0064bda8 lea edx, [ebp - 0x8bc]
0064bdae lea ecx, [ebp - 0x10b4]
0064bdb4 call 0x4120b0
0064bdb9 mov ecx, dword ptr [ebp - 0x670]
0064bdbf add esp, 4
0064bdc2 mov dword ptr [esp], 0x3f800000
0064bdc9 push edi
0064bdca push 7
0064bdcc push dword ptr [eax + 4]
0064bdcf push dword ptr [eax]
0064bdd1 push esi
0064bdd2 call 0x757690
0064bdd7 sub dword ptr [ebp - 0x6bc], 1
0064bdde jne 0x64bd80
0064bde0 cmp byte ptr [ebp - 0x68d], 0
0064bde7 je 0x64c3eb
0064bded lea ecx, [ebp - 0x7a4]
0064bdf3 call 0x420310
0064bdf8 mov ecx, edi
0064bdfa mov dword ptr [ebp - 4], 8
0064be01 call 0x422c20
0064be06 mov dword ptr [ebp - 0x714], eax
0064be0c test eax, eax
0064be0e je 0x64be37
0064be10 lea eax, [ebp - 0x714]
0064be16 push eax
0064be17 lea ecx, [ebp - 0x7a4]
0064be1d call 0x4a39c0
0064be22 mov ecx, dword ptr [ebp - 0x714]
0064be28 call 0x422c20
0064be2d mov dword ptr [ebp - 0x714], eax
0064be33 test eax, eax
0064be35 jne 0x64be10
0064be37 lea ecx, [ebp - 0x7a4]
0064be3d mov dword ptr [ebp - 0x6bc], 0
0064be47 call 0x4174c0
0064be4c test eax, eax
0064be4e je 0x64c0a1
0064be54 push dword ptr [ebp - 0x6bc]
0064be5a lea ecx, [ebp - 0x7a4]
0064be60 call 0x430970
0064be65 lea ecx, [edi + 0x2b8]
0064be6b push ecx
0064be6c mov eax, dword ptr [eax]
0064be6e mov ecx, eax
0064be70 mov dword ptr [ebp - 0x670], eax
0064be76 call 0x422ae0
0064be7b mov eax, dword ptr [ebp - 0x6bc]
0064be81 lea ecx, [ebp - 0x7a4]
0064be87 movd xmm0, eax
0064be8b cvtdq2pd xmm0, xmm0
0064be8f shr eax, 0x1f
0064be92 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
0064be9b cvtpd2ps xmm0, xmm0
0064be9f mulss xmm0, dword ptr [0xb6ac40]
0064bea7 movss dword ptr [ebp - 0x680], xmm0
0064beaf call 0x4174c0
0064beb4 movss xmm1, dword ptr [ebp - 0x680]
0064bebc mov ecx, edi
0064bebe movd xmm0, eax
0064bec2 cvtdq2pd xmm0, xmm0
0064bec6 shr eax, 0x1f
0064bec9 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
0064bed2 cvtpd2ps xmm0, xmm0
0064bed6 divss xmm1, xmm0
0064beda movss dword ptr [ebp - 0x680], xmm1
0064bee2 call 0x682200
0064bee7 mov ecx, dword ptr [ebp - 0x670]
0064beed movd xmm0, eax
0064bef1 cvtdq2ps xmm0, xmm0
0064bef4 mulss xmm0, dword ptr [0xb6a8f4]
0064befc addss xmm0, dword ptr [ebp - 0x680]
0064bf04 movss dword ptr [ebp - 0x6ac], xmm0
0064bf0c movss xmm0, dword ptr [edi + 0x2c8]
0064bf14 addss xmm0, xmm0
0064bf18 movss dword ptr [ebp - 0x718], xmm0
0064bf20 call 0x682200
0064bf25 cmp eax, 0x32
0064bf28 jge 0x64bf54
0064bf2a mov ecx, dword ptr [ebp - 0x670]
0064bf30 call 0x682200
0064bf35 movd xmm0, eax
0064bf39 cvtdq2ps xmm0, xmm0
0064bf3c divss xmm0, dword ptr [0xb6aa60]
0064bf44 mulss xmm0, dword ptr [ebp - 0x718]
0064bf4c movss dword ptr [ebp - 0x718], xmm0
0064bf54 mov ecx, dword ptr [ebp - 0x670]
0064bf5a lea eax, [ebp - 0x10bc]
0064bf60 push 0
0064bf62 push eax
0064bf63 call 0x412130
0064bf68 movss xmm0, dword ptr [ebp - 0x6ac]
0064bf70 push eax
0064bf71 lea eax, [ebp - 0x10c4]
0064bf77 push eax
0064bf78 lea eax, [ebp - 0x718]
0064bf7e push eax
0064bf7f lea eax, [ebp - 0x10cc]
0064bf85 push eax
0064bf86 push ecx
0064bf87 lea eax, [ebp - 0x10d4]
0064bf8d movss dword ptr [esp], xmm0
0064bf92 push eax
0064bf93 call 0x9627f0
0064bf98 add esp, 8
0064bf9b mov ecx, eax
0064bf9d call 0x962b50
0064bfa2 push eax
0064bfa3 lea eax, [ebp - 0x10dc]
0064bfa9 mov ecx, esi
0064bfab push eax
0064bfac call 0x962a60
0064bfb1 mov ecx, eax
0064bfb3 call 0x962ac0
0064bfb8 mov esi, dword ptr [ebp - 0x670]
0064bfbe mov ecx, esi
0064bfc0 push eax
0064bfc1 call 0x422b60
0064bfc6 mov ecx, edi
0064bfc8 call 0x544b60
0064bfcd fmul dword ptr [0xb6a480]
0064bfd3 push ecx
0064bfd4 mov ecx, esi
0064bfd6 fstp dword ptr [esp]
0064bfd9 call 0x650250
0064bfde mov esi, dword ptr [esi]
0064bfe0 mov ecx, edi
0064bfe2 push 1
0064bfe4 push 0
0064bfe6 push 0xff
0064bfeb push -1
0064bfed call 0x4f3de0
0064bff2 mov ecx, dword ptr [ebp - 0x670]
0064bff8 push eax
0064bff9 mov eax, dword ptr [esi + 0x38]
0064bffc call eax
0064bffe lea eax, [ebp - 0x1cf4]
0064c004 mov ecx, 0xbc4ca0
0064c009 push eax
0064c00a call 0x57f3a0
0064c00f push eax
0064c010 lea edx, [edi + 0x378]
0064c016 lea ecx, [ebp - 0x1d04]
0064c01c call 0x412050
0064c021 mov esi, dword ptr [ebp - 0x670]
0064c027 sub esp, 0xc
0064c02a mov ecx, esp
0064c02c movups xmm0, xmmword ptr [eax]
0064c02f movups xmmword ptr [ecx], xmm0
0064c032 mov ecx, esi
0064c034 call 0x650280
0064c039 push 0
0064c03b mov ecx, esi
0064c03d call 0x43dcc0
0064c042 mov eax, dword ptr [esi]
0064c044 movss xmm1, dword ptr [edi + 0x2e0]
0064c04c push ecx
0064c04d mov ecx, esi
0064c04f movss dword ptr [esp], xmm1
0064c054 mov eax, dword ptr [eax + 0x3c]
0064c057 call eax
0064c059 movss xmm0, dword ptr [ebp - 0x6ac]
0064c061 addss xmm0, dword ptr [0xb6aae4]
0064c069 call 0x65a640
0064c06e push ecx
0064c06f movss dword ptr [esp], xmm0
0064c074 mov ecx, esi
0064c076 call 0x5ef100
0064c07b mov esi, dword ptr [ebp - 0x6bc]
0064c081 lea ecx, [ebp - 0x7a4]
0064c087 inc esi
0064c088 mov dword ptr [ebp - 0x6bc], esi
0064c08e call 0x4174c0
0064c093 cmp esi, eax
0064c095 lea esi, [edi + 0x294]
0064c09b jb 0x64be54
0064c0a1 mov ecx, dword ptr [edi + 0x314]
0064c0a7 test ecx, ecx
0064c0a9 je 0x64c3d4
0064c0af call 0x427400
0064c0b4 lea esi, [edi + 0x294]
0064c0ba test al, al
0064c0bc je 0x64c28b
0064c0c2 mov ecx, dword ptr [0xbfd65c]
0064c0c8 lea eax, [ebp - 0xabc]
0064c0ce push 4
0064c0d0 push esi
0064c0d1 push eax
0064c0d2 call 0x4023f0
0064c0d7 mov ecx, eax
0064c0d9 call 0x422d70
0064c0de movss xmm3, dword ptr [0xb6a9e8]
0064c0e6 mov ecx, eax
0064c0e8 call 0x4157f0
0064c0ed lea ecx, [ebp - 0xabc]
0064c0f3 mov byte ptr [ebp - 4], 9
0064c0f7 mov dword ptr [ebp - 0x680], 0
0064c101 call 0x4083d0
0064c106 test eax, eax
0064c108 je 0x64c27c
0064c10e xor ecx, ecx
0064c110 push ecx
0064c111 lea ecx, [ebp - 0xabc]
0064c117 call 0x4124b0
0064c11c mov ecx, dword ptr [eax]
0064c11e call 0x4274a0
0064c123 mov dword ptr [ebp - 0x6ac], eax
0064c129 test eax, eax
0064c12b je 0x64c25d
0064c131 cmp eax, edi
0064c133 je 0x64c25d
0064c139 push 0xbc4ce0
0064c13e lea edx, [eax + 0x378]
0064c144 lea ecx, [ebp - 0x1d14]
0064c14a call 0x412050
0064c14f add esp, 4
0064c152 mov ecx, eax
0064c154 call 0x412090
0064c159 test al, al
0064c15b je 0x64c25d
0064c161 mov ecx, dword ptr [ebp - 0x6ac]
0064c167 call 0x6520e0
0064c16c test al, al
0064c16e je 0x64c25d
0064c174 mov ecx, dword ptr [ebp - 0x6ac]
0064c17a lea eax, [ebp - 0x10e4]
0064c180 push eax
0064c181 call 0x412130
0064c186 push eax
0064c187 lea eax, [ebp - 0x758]
0064c18d mov ecx, esi
0064c18f push eax
0064c190 call 0x962ac0
0064c195 lea ecx, [ebp - 0x758]
0064c19b call 0x962a00
0064c1a0 movss xmm0, dword ptr [0xb6a9e8]
0064c1a8 fstp dword ptr [ebp - 0x668]
0064c1ae comiss xmm0, dword ptr [ebp - 0x668]
0064c1b5 jbe 0x64c1dc
0064c1b7 lea ecx, [ebp - 0x758]
0064c1bd call 0x962a00
0064c1c2 fld1 
0064c1c4 faddp st(1)
0064c1c6 fdivr dword ptr [0xb6a8cc]
0064c1cc fstp dword ptr [ebp - 0x668]
0064c1d2 movss xmm0, dword ptr [ebp - 0x668]
0064c1da jmp 0x64c1e4
0064c1dc movss xmm0, dword ptr [ebp - 0x67c]
0064c1e4 push 0xc02fec
0064c1e9 lea ecx, [ebp - 0x758]
0064c1ef movss dword ptr [ebp - 0x740], xmm0
0064c1f7 call 0x962c70
0064c1fc test al, al
0064c1fe je 0x64c21b
0064c200 lea eax, [ebp - 0x10ec]
0064c206 push eax
0064c207 call 0x659290
0064c20c add esp, 4
0064c20f lea ecx, [ebp - 0x758]
0064c215 push eax
0064c216 call 0x962cd0
0064c21b movss xmm0, dword ptr [ebp - 0x740]
0064c223 comiss xmm0, dword ptr [ebp - 0x67c]
0064c22a jbe 0x64c25d
0064c22c push 0
0064c22e lea eax, [ebp - 0x740]
0064c234 push eax
0064c235 lea eax, [ebp - 0x10f4]
0064c23b push eax
0064c23c lea eax, [ebp - 0x10fc]
0064c242 push eax
0064c243 lea ecx, [ebp - 0x758]
0064c249 call 0x962560
0064c24e mov ecx, eax
0064c250 call 0x962b50
0064c255 push eax
0064c256 mov ecx, edi
0064c258 call 0x422b60
0064c25d inc dword ptr [ebp - 0x680]
0064c263 lea ecx, [ebp - 0xabc]
0064c269 call 0x4083d0
0064c26e mov ecx, dword ptr [ebp - 0x680]
0064c274 cmp ecx, eax
0064c276 jb 0x64c110
0064c27c lea ecx, [ebp - 0xabc]
0064c282 mov byte ptr [ebp - 4], 8
0064c286 call 0x412490
0064c28b mov ecx, dword ptr [edi + 0x314]
0064c291 lea eax, [ebp - 0x1104]
0064c297 push esi
0064c298 push eax
0064c299 call 0x412130
0064c29e mov ecx, eax
0064c2a0 call 0x962750
0064c2a5 cmp byte ptr [ebp - 0x674], 0
0064c2ac fstp dword ptr [ebp - 0x668]
0064c2b2 je 0x64c36b
0064c2b8 movss xmm0, dword ptr [ebp - 0x668]
0064c2c0 comiss xmm0, dword ptr [0xb6ace4]
0064c2c7 jbe 0x64c33c
0064c2cd push 0
0064c2cf lea eax, [ebp - 0x8c0]
0064c2d5 mov dword ptr [ebp - 0x8c0], 0x3dcccccd
0064c2df mov ecx, dword ptr [edi + 0x314]
0064c2e5 push eax
0064c2e6 lea eax, [ebp - 0x110c]
0064c2ec push eax
0064c2ed lea eax, [ebp - 0x1114]
0064c2f3 push eax
0064c2f4 push esi
0064c2f5 lea eax, [ebp - 0x111c]
0064c2fb push eax
0064c2fc lea eax, [ebp - 0x1124]
0064c302 push eax
0064c303 call 0x412130
0064c308 mov ecx, eax
0064c30a call 0x962ac0
0064c30f mov ecx, eax
0064c311 call 0x962560
0064c316 mov ecx, eax
0064c318 call 0x962b50
0064c31d push eax
0064c31e mov ecx, edi
0064c320 call 0x422b60
0064c325 lea ecx, [ebp - 0x7a4]
0064c32b mov dword ptr [ebp - 4], 0xffffffff
0064c332 call 0x40f700
0064c337 jmp 0x64c5dc
0064c33c movss xmm0, dword ptr [edi + 0x2c4]
0064c344 lea ecx, [ebp - 0x7a4]
0064c34a mulss xmm0, dword ptr [0xb6a5a4]
0064c352 mov dword ptr [ebp - 4], 0xffffffff
0064c359 movss dword ptr [edi + 0x2c4], xmm0
0064c361 call 0x40f700
0064c366 jmp 0x64c5dc
0064c36b mov ecx, dword ptr [edi + 0x314]
0064c371 call 0x412240
0064c376 test al, al
0064c378 je 0x64c3d4
0064c37e push 8
0064c380 push 0
0064c382 push 0xbeab9c
0064c387 push 0xbeab18
0064c38c push 0
0064c38e push dword ptr [edi + 0x314]
0064c394 call 0x9ec34c
0064c399 add esp, 0x14
0064c39c mov ecx, eax
0064c39e call 0x59ff80
0064c3a3 test al, al
0064c3a5 jne 0x64c3d4
0064c3a7 mov ecx, edi
0064c3a9 call 0x422c20
0064c3ae test eax, eax
0064c3b0 je 0x64c3d4
0064c3b2 mov ecx, eax
0064c3b4 mov esi, eax
0064c3b6 call 0x422c20
0064c3bb mov dword ptr [ebp - 0x668], eax
0064c3c1 mov ecx, esi
0064c3c3 mov eax, dword ptr [esi]
0064c3c5 mov eax, dword ptr [eax + 0x28]
0064c3c8 call eax
0064c3ca mov eax, dword ptr [ebp - 0x668]
0064c3d0 test eax, eax
0064c3d2 jne 0x64c3b2
0064c3d4 lea ecx, [ebp - 0x7a4]
0064c3da mov dword ptr [ebp - 4], 0xffffffff
0064c3e1 call 0x40f700
0064c3e6 jmp 0x64c5dc
0064c3eb mov ecx, dword ptr [edi + 0x314]
0064c3f1 test ecx, ecx
0064c3f3 je 0x64c460
0064c3f9 call 0x412100
0064c3fe cmp eax, 2
0064c401 jne 0x64c460
0064c407 mov ecx, dword ptr [edi + 0x314]
0064c40d call 0x412110
0064c412 cmp dword ptr [edi + 0x2c], eax
0064c415 je 0x64c460
0064c417 mov ecx, eax
0064c419 mov dword ptr [edi + 0x2c], eax
0064c41c call 0x641680
0064c421 test al, al
0064c423 je 0x64c460
0064c425 mov ecx, edi
0064c427 call 0x681ea0
0064c42c mov eax, dword ptr [edi + 0x288]
0064c432 lea esi, [edi + 0x3c]
0064c435 test eax, eax
0064c437 je 0x64c463
0064c439 push 1
0064c43b add eax, 0x74
0064c43e mov ecx, esi
0064c440 push eax
0064c441 call 0x407160
0064c446 push 0
0064c448 mov ecx, esi
0064c44a call 0x4921f0
0064c44f push eax
0064c450 mov ecx, esi
0064c452 call 0x4054d0
0064c457 mov ecx, edi
0064c459 call 0x651770
0064c45e jmp 0x64c463
0064c460 lea esi, [edi + 0x3c]
0064c463 mov eax, dword ptr [edi + 0x2c]
0064c466 cmp eax, 5
0064c469 je 0x64c4a8
0064c46b cmp eax, 6
0064c46e je 0x64c4a8
0064c470 cmp eax, 7
0064c473 je 0x64c4a8
0064c475 cmp eax, 0x14
0064c478 je 0x64c4a8
0064c47a cmp eax, 0x21
0064c47d je 0x64c4a8
0064c47f cmp eax, 0x22
0064c482 je 0x64c4a8
0064c484 push 0xbc4a10
0064c489 lea edx, [edi + 0x378]
0064c48f lea ecx, [ebp - 0x1d24]
0064c495 call 0x412050
0064c49a add esp, 4
0064c49d mov ecx, eax
0064c49f call 0x412090
0064c4a4 test al, al
0064c4a6 je 0x64c4bd
0064c4a8 movss xmm0, dword ptr [edi + 0x3a8]
0064c4b0 push ecx
0064c4b1 mov ecx, esi
0064c4b3 movss dword ptr [esp], xmm0
0064c4b8 call 0x430cc0
0064c4bd test byte ptr [edi + 0x30], 1
0064c4c1 je 0x64c5ca
0064c4c7 cmp dword ptr [edi + 0x314], 0
0064c4ce je 0x64c5d3
0064c4d4 mov ecx, edi
0064c4d6 call 0x682200
0064c4db imul ecx, dword ptr [edi + 0x20], 0x32
0064c4df add eax, ecx
0064c4e1 movd xmm0, eax
0064c4e5 cvtdq2pd xmm0, xmm0
0064c4e9 shr eax, 0x1f
0064c4ec addsd xmm0, qword ptr [eax*8 + 0xb6c940]
0064c4f5 cvtpd2ps xmm0, xmm0
0064c4f9 mulss xmm0, dword ptr [0xb6a2ac]
0064c501 call 0x412040
0064c506 mulss xmm0, dword ptr [ebp - 0x68c]
0064c50e lea ecx, [edi + 0x744]
0064c514 addss xmm0, dword ptr [ebp - 0x684]
0064c51c movss dword ptr [ebp - 0x668], xmm0
0064c524 call 0x962a00
0064c529 fmul dword ptr [ebp - 0x668]
0064c52f lea eax, [ebp - 0x112c]
0064c535 push ecx
0064c536 lea ecx, [edi + 0x744]
0064c53c fstp dword ptr [esp]
0064c53f push eax
0064c540 call 0x9628d0
0064c545 mov ecx, dword ptr [edi + 0x314]
0064c54b push eax
0064c54c lea eax, [ebp - 0x1134]
0064c552 push eax
0064c553 lea eax, [ebp - 0x113c]
0064c559 push eax
0064c55a call 0x412130
0064c55f mov ecx, eax
0064c561 call 0x962a60
0064c566 push eax
0064c567 lea ecx, [edi + 0x294]
0064c56d call 0x962cd0
0064c572 mov eax, dword ptr [edi + 0x20]
0064c575 xor edx, edx
0064c577 mov ecx, 0xa
0064c57c div ecx
0064c57e push ecx
0064c57f lea eax, [ebp - 0x1144]
0064c585 lea ecx, [edi + 0x744]
0064c58b movd xmm0, edx
0064c58f cvtdq2pd xmm0, xmm0
0064c593 shr edx, 0x1f
0064c596 addsd xmm0, qword ptr [edx*8 + 0xb6c940]
0064c59f cvtpd2ps xmm0, xmm0
0064c5a3 mulss xmm0, dword ptr [0xb6a2cc]
0064c5ab subss xmm0, dword ptr [0xb6a8cc]
0064c5b3 movss dword ptr [esp], xmm0
0064c5b8 push eax
0064c5b9 call 0x962780
0064c5be push eax
0064c5bf lea ecx, [edi + 0x744]
0064c5c5 call 0x962cd0
0064c5ca cmp dword ptr [edi + 0x314], 0
0064c5d1 jne 0x64c5dc
0064c5d3 mov eax, dword ptr [edi]
0064c5d5 mov ecx, edi
0064c5d7 mov eax, dword ptr [eax + 0x28]
0064c5da call eax
0064c5dc movss xmm0, dword ptr [ebp - 0x6b4]
0064c5e4 lea esi, [edi + 0x370]
0064c5ea mulss xmm0, dword ptr [edi + 0x374]
0064c5f2 lea ecx, [ebp - 0x8c4]
0064c5f8 mov edx, esi
0064c5fa mov dword ptr [ebp - 0x6b0], esi
0064c600 movss dword ptr [esi], xmm0
0064c604 mov dword ptr [ebp - 0x8c4], 0x3c23d70a
0064c60e call 0x417c70
0064c613 mov ecx, edi
0064c615 mov eax, dword ptr [eax]
0064c617 mov dword ptr [esi], eax
0064c619 call 0x651770
0064c61e cmp dword ptr [edi + 0x2c], 0x2e
0064c622 jne 0x64c774
0064c628 mov ecx, dword ptr [edi + 0x320]
0064c62e movss xmm0, dword ptr [edi + 0x3a4]
0064c636 movss dword ptr [ebp - 0x668], xmm0
0064c63e test ecx, ecx
0064c640 je 0x64c69e
0064c646 mulss xmm0, dword ptr [ebp - 0x6c4]
0064c64e lea eax, [edi + 0x294]
0064c654 push ecx
0064c655 movss dword ptr [esp], xmm0
0064c65a push eax
0064c65b lea eax, [ebp - 0x114c]
0064c661 push eax
0064c662 call 0x412130
0064c667 mov ecx, eax
0064c669 call 0x9626f0
0064c66e movss xmm3, dword ptr [ebp - 0x668]
0064c676 mov cl, 1
0064c678 movss xmm2, dword ptr [0xb6ab70]
0064c680 movss xmm1, dword ptr [ebp - 0x67c]
0064c688 fstp dword ptr [ebp - 0x6ac]
0064c68e movss xmm0, dword ptr [ebp - 0x6ac]
0064c696 call 0x962420
0064c69b add esp, 4
0064c69e movss dword ptr [edi + 0x2e0], xmm0
0064c6a6 movss xmm2, dword ptr [edi + 0x2fc]
0064c6ae divss xmm2, dword ptr [ebp - 0x6e0]
0064c6b6 movss xmm1, dword ptr [ebp - 0x684]
0064c6be movss xmm0, dword ptr [ebp - 0x6b8]
0064c6c6 call 0x9623e0
0064c6cb lea eax, [ebp - 0x748]
0064c6d1 movss dword ptr [ebp - 0x748], xmm0
0064c6d9 push eax
0064c6da lea eax, [ebp - 0x1154]
0064c6e0 mov ecx, 0xbc7a28
0064c6e5 push eax
0064c6e6 call 0x962b50
0064c6eb push eax
0064c6ec lea ecx, [edi + 0x3c]
0064c6ef call 0x41b8c0
0064c6f4 movss xmm2, dword ptr [edi + 0x2fc]
0064c6fc divss xmm2, dword ptr [ebp - 0x6c0]
0064c704 movss xmm1, dword ptr [ebp - 0x6c4]
0064c70c movss xmm0, dword ptr [ebp - 0x67c]
0064c714 call 0x9623e0
0064c719 movss xmm1, dword ptr [ebp - 0x684]
0064c721 subss xmm1, xmm0
0064c725 push ecx
0064c726 lea ecx, [edi + 0x3c]
0064c729 movss dword ptr [esp], xmm1
0064c72e call 0x4023b0
0064c733 mov ecx, eax
0064c735 call 0x402230
0064c73a lea edx, [ebp - 0x748]
0064c740 mov dword ptr [ebp - 0x8c8], 0x3f19999a
0064c74a lea ecx, [ebp - 0x8c8]
0064c750 call 0x417c70
0064c755 mov ecx, dword ptr [edi + 0x288]
0064c75b movss xmm0, dword ptr [ecx + 0x38]
0064c760 mulss xmm0, dword ptr [eax]
0064c764 mulss xmm0, dword ptr [0xb6a8f4]
0064c76c movss dword ptr [edi + 0x2c8], xmm0
0064c774 mov ecx, dword ptr [0xbfd65c]
0064c77a push 0x25
0064c77c call 0x641630
0064c781 test al, al
0064c783 je 0x64c823
0064c789 movss xmm0, dword ptr [ebp - 0x67c]
0064c791 lea ecx, [ebp - 0x5b4]
0064c797 mov esi, dword ptr [edi]
0064c799 movaps xmm3, xmm0
0064c79c push 1
0064c79e push 0
0064c7a0 push 0xff
0064c7a5 push -1
0064c7a7 sub esp, 0x10
0064c7aa movaps xmm2, xmm0
0064c7ad movaps xmm1, xmm0
0064c7b0 mov dword ptr [esp + 0xc], 0
0064c7b8 mov dword ptr [esp + 8], 0
0064c7c0 mov dword ptr [esp + 4], 0
0064c7c8 mov dword ptr [esp], 0x3f800000
0064c7cf call 0x408270
0064c7d4 push eax
0064c7d5 mov eax, dword ptr [esi + 0x38]
0064c7d8 mov ecx, edi
0064c7da call eax
0064c7dc movss xmm0, dword ptr [ebp - 0x67c]
0064c7e4 lea ecx, [ebp - 0x588]
0064c7ea sub esp, 0x10
0064c7ed movaps xmm3, xmm0
0064c7f0 movaps xmm2, xmm0
0064c7f3 movaps xmm1, xmm0
0064c7f6 mov dword ptr [esp + 0xc], 0
0064c7fe mov dword ptr [esp + 8], 0
0064c806 mov dword ptr [esp + 4], 0
0064c80e mov dword ptr [esp], 0x3f800000
0064c815 call 0x408270
0064c81a push eax
0064c81b lea ecx, [edi + 0x3c]
0064c81e call 0x402370
0064c823 mov ecx, dword ptr [edi + 0x298]
0064c829 lea esi, [edi + 0x294]
0064c82f mov eax, dword ptr [esi]
0064c831 mov dword ptr [ebp - 0x964], ecx
0064c837 mov ecx, edi
0064c839 mov dword ptr [ebp - 0x968], eax
0064c83f call 0x6860a0
0064c844 cmp dword ptr [edi + 0x31c], 0
0064c84b je 0x64ca77
0064c851 push 0xbc4860
0064c856 lea edx, [edi + 0x378]
0064c85c lea ecx, [ebp - 0x1d34]
0064c862 call 0x412050
0064c867 add esp, 4
0064c86a mov ecx, eax
0064c86c call 0x412090
0064c871 test al, al
0064c873 je 0x64ca77
0064c879 lea ecx, [ebp - 0x728]
0064c87f push ecx
0064c880 lea ecx, [edi + 0x2b8]
0064c886 call 0x962560
0064c88b mov ecx, dword ptr [edi + 0x31c]
0064c891 lea eax, [ebp - 0xb4c]
0064c897 push eax
0064c898 lea eax, [edi + 0x2b8]
0064c89e push eax
0064c89f lea eax, [ebp - 0x115c]
0064c8a5 push eax
0064c8a6 lea eax, [ebp - 0x968]
0064c8ac push eax
0064c8ad lea eax, [ebp - 0x1164]
0064c8b3 push eax
0064c8b4 lea eax, [ebp - 0x116c]
0064c8ba push eax
0064c8bb call 0x412130
0064c8c0 mov ecx, eax
0064c8c2 call 0x962ac0
0064c8c7 mov ecx, eax
0064c8c9 call 0x962ac0
0064c8ce mov ecx, eax
0064c8d0 call 0x962560
0064c8d5 lea eax, [ebp - 0x728]
0064c8db push eax
0064c8dc lea ecx, [ebp - 0xb4c]
0064c8e2 call 0x962600
0064c8e7 mov ecx, dword ptr [edi + 0x31c]
0064c8ed lea eax, [ebp - 0xa1c]
0064c8f3 push eax
0064c8f4 lea eax, [edi + 0x2b8]
0064c8fa push eax
0064c8fb lea eax, [ebp - 0x1174]
0064c901 push eax
0064c902 push esi
0064c903 lea eax, [ebp - 0x117c]
0064c909 push eax
0064c90a lea eax, [ebp - 0x1184]
0064c910 push eax
0064c911 fstp dword ptr [ebp - 0x6c0]
0064c917 call 0x412130
0064c91c mov ecx, eax
0064c91e call 0x962ac0
0064c923 mov ecx, eax
0064c925 call 0x962ac0
0064c92a mov ecx, eax
0064c92c call 0x962560
0064c931 lea eax, [ebp - 0x728]
0064c937 push eax
0064c938 lea ecx, [ebp - 0xa1c]
0064c93e call 0x962600
0064c943 movss xmm3, dword ptr [ebp - 0x67c]
0064c94b movss xmm2, dword ptr [ebp - 0x6c0]
0064c953 movss xmm0, dword ptr [0xb6adec]
0064c95b fstp dword ptr [ebp - 0x668]
0064c961 movss xmm1, dword ptr [ebp - 0x668]
0064c969 comiss xmm3, xmm1
0064c96c jb 0x64ca40
0064c972 comiss xmm2, xmm3
0064c975 ja 0x64c980
0064c977 comiss xmm1, xmm0
0064c97a jb 0x64ca40
0064c980 push ecx
0064c981 lea eax, [ebp - 0x118c]
0064c987 mov dword ptr [esp], 0x42b40000
0064c98e push eax
0064c98f lea ecx, [ebp - 0x728]
0064c995 call 0x962780
0064c99a push eax
0064c99b lea ecx, [ebp - 0x728]
0064c9a1 call 0x962cd0
0064c9a6 lea eax, [ebp - 0xa1c]
0064c9ac push eax
0064c9ad lea ecx, [ebp - 0x728]
0064c9b3 call 0x962600
0064c9b8 movss xmm0, dword ptr [ebp - 0x67c]
0064c9c0 fstp dword ptr [ebp - 0x668]
0064c9c6 comiss xmm0, dword ptr [ebp - 0x668]
0064c9cd jbe 0x64c9eb
0064c9cf lea eax, [ebp - 0x8cc]
0064c9d5 mov dword ptr [ebp - 0x8cc], 0xbf800000
0064c9df push eax
0064c9e0 lea ecx, [ebp - 0x728]
0064c9e6 call 0x962bb0
0064c9eb lea ecx, [edi + 0x2b8]
0064c9f1 call 0x962a00
0064c9f6 lea eax, [ebp - 0x8d0]
0064c9fc push eax
0064c9fd lea eax, [ebp - 0x1194]
0064ca03 push eax
0064ca04 lea ecx, [ebp - 0x728]
0064ca0a fstp dword ptr [ebp - 0x8d0]
0064ca10 call 0x962b50
0064ca15 push eax
0064ca16 lea ecx, [edi + 0x2b8]
0064ca1c call 0x962cd0
0064ca21 lea eax, [ebp - 0x1d44]
0064ca27 mov ecx, 0xbc4860
0064ca2c push eax
0064ca2d call 0x57f3a0
0064ca32 push eax
0064ca33 lea ecx, [edi + 0x378]
0064ca39 call 0x6413c0
0064ca3e jmp 0x64ca77
0064ca40 comiss xmm0, xmm1
0064ca43 jbe 0x64ca77
0064ca45 comiss xmm0, xmm2
0064ca48 jbe 0x64ca77
0064ca4a push 0xbc4cb0
0064ca4f lea edx, [edi + 0x378]
0064ca55 lea ecx, [ebp - 0x1d54]
0064ca5b call 0x412050
0064ca60 add esp, 4
0064ca63 mov ecx, eax
0064ca65 call 0x427260
0064ca6a test al, al
0064ca6c je 0x64ca77
0064ca6e push 0
0064ca70 mov ecx, edi
0064ca72 call 0x681960
0064ca77 push 0xbc4950
0064ca7c lea edx, [edi + 0x378]
0064ca82 lea ecx, [ebp - 0x1d64]
0064ca88 call 0x412050
0064ca8d add esp, 4
0064ca90 mov ecx, eax
0064ca92 call 0x412090
0064ca97 test al, al
0064ca99 jne 0x64cae7
0064ca9b push 0xbc4b50
0064caa0 lea edx, [edi + 0x378]
0064caa6 lea ecx, [ebp - 0x1d74]
0064caac call 0x412050
0064cab1 add esp, 4
0064cab4 mov ecx, eax
0064cab6 call 0x412090
0064cabb test al, al
0064cabd jne 0x64cae7
0064cabf push 0xbc4830
0064cac4 lea edx, [edi + 0x378]
0064caca lea ecx, [ebp - 0x1d84]
0064cad0 call 0x412050
0064cad5 add esp, 4
0064cad8 mov ecx, eax
0064cada call 0x412090
0064cadf test al, al
0064cae1 je 0x64d33b
0064cae7 mov ecx, dword ptr [edi + 0x3c8]
0064caed lea eax, [edi + 0x3c8]
0064caf3 mov dword ptr [ebp - 0x678], eax
0064caf9 test ecx, ecx
0064cafb je 0x64d2df
0064cb01 call 0x412360
0064cb06 test al, al
0064cb08 je 0x64cba1
0064cb0e mov ecx, dword ptr [edi + 0x3c8]
0064cb14 call 0x412230
0064cb19 test eax, eax
0064cb1b je 0x64cba1
0064cb21 mov ecx, dword ptr [edi + 0x3c8]
0064cb27 lea eax, [ebp - 0x119c]
0064cb2d push eax
0064cb2e call 0x412170
0064cb33 push eax
0064cb34 lea ecx, [edi + 0x2b8]
0064cb3a call 0x962cd0
0064cb3f mov ecx, dword ptr [edi + 0x3c8]
0064cb45 lea eax, [edi + 0x3cc]
0064cb4b push eax
0064cb4c lea eax, [ebp - 0x11a4]
0064cb52 push eax
0064cb53 lea eax, [ebp - 0x11ac]
0064cb59 push eax
0064cb5a call 0x412130
0064cb5f mov ecx, eax
0064cb61 call 0x962a60
0064cb66 push eax
0064cb67 mov ecx, esi
0064cb69 call 0x962cd0
0064cb6e mov eax, dword ptr [edi + 0x2c]
0064cb71 cmp eax, 0x1a
0064cb74 je 0x64cb7f
0064cb76 cmp eax, 0x30
0064cb79 jne 0x64cc02
0064cb7f push 0xa081d4
0064cb84 lea ecx, [edi + 0x3c]
0064cb87 call 0x405640
0064cb8c test al, al
0064cb8e je 0x64cc02
0064cb94 lea ecx, [edi + 0x3c]
0064cb97 call 0x4059d0
0064cb9c jmp 0x64cc02
0064cba1 xor edx, edx
0064cba3 lea ecx, [edi + 0x3c8]
0064cba9 call 0x68cf00
0064cbae push 0
0064cbb0 lea ecx, [edi + 0x394]
0064cbb6 call 0x4d1fd0
0064cbbb mov eax, dword ptr [edi + 0x2c]
0064cbbe cmp eax, 0x1a
0064cbc1 je 0x64cbc8
0064cbc3 cmp eax, 0x30
0064cbc6 jne 0x64cc02
0064cbc8 lea eax, [ebp - 0x158]
0064cbce push eax
0064cbcf lea ecx, [edi + 0x3c]
0064cbd2 call 0x419b40
0064cbd7 mov ecx, eax
0064cbd9 call 0x444be0
0064cbde push 0
0064cbe0 push eax
0064cbe1 lea ecx, [edi + 0x3c]
0064cbe4 mov dword ptr [ebp - 4], 0xa
0064cbeb call 0x4054d0
0064cbf0 lea ecx, [ebp - 0x158]
0064cbf6 mov dword ptr [ebp - 4], 0xffffffff
0064cbfd call 0x407330
0064cc02 dec dword ptr [edi + 0x3d4]
0064cc08 cmp dword ptr [edi + 0x3d4], 0
0064cc0f jg 0x64d33b
0064cc15 movss xmm0, dword ptr [ebp - 0x694]
0064cc1d lea edx, [edi + 0x370]
0064cc23 mov byte ptr [edi + 0x16b], 1
0064cc2a lea ecx, [ebp - 0x8d4]
0064cc30 or dword ptr [edi + 0x3c4], 0x40
0064cc37 mulss xmm0, dword ptr [edi + 0x374]
0064cc3f movss dword ptr [edi + 0x370], xmm0
0064cc47 mov dword ptr [ebp - 0x8d4], 0x3c23d70a
0064cc51 call 0x417c70
0064cc56 mov ecx, edi
0064cc58 mov eax, dword ptr [eax]
0064cc5a mov dword ptr [edi + 0x370], eax
0064cc60 call 0x651770
0064cc65 push 0xbc4950
0064cc6a lea edx, [edi + 0x378]
0064cc70 lea ecx, [ebp - 0x1d94]
0064cc76 call 0x412050
0064cc7b add esp, 4
0064cc7e mov ecx, eax
0064cc80 call 0x412090
0064cc85 test al, al
0064cc87 je 0x64cd26
0064cc8d push 0xbc4ca0
0064cc92 lea ecx, [edi + 0x378]
0064cc98 call 0x4271f0
0064cc9d or dword ptr [edi + 0x3c4], 0x20
0064cca4 mov ecx, edi
0064cca6 movss xmm0, dword ptr [edi + 0x2e0]
0064ccae addss xmm0, dword ptr [0xb6aa8c]
0064ccb6 movss dword ptr [edi + 0x2e0], xmm0
0064ccbe call 0x6414a0
0064ccc3 mov dword ptr [ebp - 0x6c0], eax
0064ccc9 test eax, eax
0064cccb je 0x64cd26
0064ccd1 push 0
0064ccd3 sub esp, 0x10
0064ccd6 mov ecx, esp
0064ccd8 push 0
0064ccda push 0
0064ccdc call 0x4271c0
0064cce1 mov ecx, dword ptr [ebp - 0x6c0]
0064cce7 call 0x749da0
0064ccec sub esp, 0x10
0064ccef mov ecx, esp
0064ccf1 push 0
0064ccf3 push 0
0064ccf5 call 0x4271c0
0064ccfa mov ecx, dword ptr [ebp - 0x6c0]
0064cd00 call 0x749db0
0064cd05 comiss xmm0, dword ptr [0xb6a6f0]
0064cd0c jb 0x64cd26
0064cd0e movss xmm0, dword ptr [edi + 0x2e0]
0064cd16 addss xmm0, dword ptr [0xb6aa60]
0064cd1e movss dword ptr [edi + 0x2e0], xmm0
0064cd26 push 0xbc4830
0064cd2b lea edx, [edi + 0x378]
0064cd31 lea ecx, [ebp - 0x1da4]
0064cd37 call 0x412050
0064cd3c add esp, 4
0064cd3f mov ecx, eax
0064cd41 call 0x412090
0064cd46 test al, al
0064cd48 je 0x64d33b
0064cd4e mov ecx, edi
0064cd50 call 0x6414a0
0064cd55 movss xmm0, dword ptr [ebp - 0x684]
0064cd5d lea ecx, [ebp - 0x55c]
0064cd63 sub esp, 0x20
0064cd66 movaps xmm3, xmm0
0064cd69 movaps xmm2, xmm0
0064cd6c movaps xmm1, xmm0
0064cd6f mov esi, eax
0064cd71 mov dword ptr [esp + 0x1c], 0
0064cd79 mov dword ptr [esp + 0x18], 0
0064cd81 mov dword ptr [esp + 0x14], 0
0064cd89 mov dword ptr [esp + 0x10], 0x3f800000
0064cd91 mov dword ptr [esp + 0xc], 0x40000000
0064cd99 mov dword ptr [esp + 8], 0x3f4ccccd
0064cda1 mov dword ptr [esp + 4], 0x3f4ccccd
0064cda9 mov dword ptr [esp], 0x3f800000
0064cdb0 call 0x427150
0064cdb5 push eax
0064cdb6 push 0
0064cdb8 push ecx
0064cdb9 test esi, esi
0064cdbb mov dword ptr [esp], 0x3f800000
0064cdc2 mov eax, edi
0064cdc4 cmovne eax, esi
0064cdc7 lea esi, [edi + 0x294]
0064cdcd push eax
0064cdce push ecx
0064cdcf mov ecx, dword ptr [0xbfd65c]
0064cdd5 mov dword ptr [esp], 0x42aa0000
0064cddc push esi
0064cddd call 0x6d60d0
0064cde2 cmp dword ptr [edi + 0x3c8], 0
0064cde9 je 0x64d33b
0064cdef push 0x800
0064cdf4 push 0
0064cdf6 mov ecx, edi
0064cdf8 call 0x4122f0
0064cdfd test al, al
0064cdff je 0x64ce0d
0064ce01 mov ecx, 2
0064ce06 call 0x659230
0064ce0b jmp 0x64ce1a
0064ce0d mov ecx, 3
0064ce12 call 0x659230
0064ce17 add eax, 2
0064ce1a mov dword ptr [ebp - 0x6bc], eax
0064ce20 call 0x659200
0064ce25 mulss xmm0, dword ptr [0xb6ac40]
0064ce2d lea ecx, [ebp - 0xa14]
0064ce33 movss dword ptr [ebp - 0x668], xmm0
0064ce3b call 0x420310
0064ce40 mov dword ptr [ebp - 4], 0xb
0064ce47 lea ecx, [ebp - 0xa14]
0064ce4d push dword ptr [edi + 0x3c8]
0064ce53 call 0x422ce0
0064ce58 mov ecx, dword ptr [0xbfd65c]
0064ce5e lea eax, [ebp - 0xacc]
0064ce64 push 8
0064ce66 push esi
0064ce67 push eax
0064ce68 call 0x4023f0
0064ce6d mov ecx, eax
0064ce6f call 0x422d70
0064ce74 movss xmm3, dword ptr [0xb6aba8]
0064ce7c mov ecx, eax
0064ce7e call 0x4157f0
0064ce83 mov eax, dword ptr [ebp - 0x6bc]
0064ce89 mov byte ptr [ebp - 4], 0xc
0064ce8d mov dword ptr [ebp - 0x680], 0
0064ce97 test eax, eax
0064ce99 jle 0x64d2bd
0064ce9f nop 
0064cea0 call 0x659200
0064cea5 movd xmm1, dword ptr [ebp - 0x680]
0064cead lea eax, [ebp - 0x960]
0064ceb3 mulss xmm0, dword ptr [0xb6a560]
0064cebb push ecx
0064cebc cvtdq2ps xmm1, xmm1
0064cebf subss xmm1, dword ptr [ebp - 0x6cc]
0064cec7 addss xmm0, xmm1
0064cecb movd xmm1, dword ptr [ebp - 0x6bc]
0064ced3 cvtdq2ps xmm1, xmm1
0064ced6 mulss xmm0, dword ptr [0xb6ac40]
0064cede divss xmm0, xmm1
0064cee2 addss xmm0, dword ptr [ebp - 0x668]
0064ceea movss dword ptr [esp], xmm0
0064ceef push eax
0064cef0 call 0x9627f0
0064cef5 movss xmm0, dword ptr [0xb6adb4]
0064cefd lea ecx, [ebp - 0xacc]
0064cf03 add esp, 8
0064cf06 movss dword ptr [ebp - 0x6c0], xmm0
0064cf0e xor eax, eax
0064cf10 mov dword ptr [ebp - 0x670], eax
0064cf16 mov dword ptr [ebp - 0x6ac], eax
0064cf1c call 0x4083d0
0064cf21 test eax, eax
0064cf23 je 0x64d07a
0064cf29 mov edi, dword ptr [ebp - 0x6ac]
0064cf2f nop 
0064cf30 push edi
0064cf31 lea ecx, [ebp - 0xacc]
0064cf37 call 0x4124b0
0064cf3c push 0
0064cf3e mov esi, dword ptr [eax]
0064cf40 mov ecx, esi
0064cf42 call 0x684630
0064cf47 test al, al
0064cf49 je 0x64cff2
0064cf4f push 0
0064cf51 push 0x20000000
0064cf56 mov ecx, esi
0064cf58 call 0x4122f0
0064cf5d test al, al
0064cf5f jne 0x64cff2
0064cf65 push esi
0064cf66 lea ecx, [ebp - 0xa14]
0064cf6c call 0x422d00
0064cf71 test al, al
0064cf73 jne 0x64cff2
0064cf79 lea eax, [ebp - 0x11b4]
0064cf7f mov dword ptr [ebp - 0x8d8], 0x43480000
0064cf89 push eax
0064cf8a mov ecx, esi
0064cf8c call 0x412130
0064cf91 push eax
0064cf92 lea eax, [ebp - 0x960]
0064cf98 push eax
0064cf99 lea edx, [ebp - 0x8d8]
0064cf9f lea ecx, [ebp - 0x11bc]
0064cfa5 call 0x4120b0
0064cfaa mov ecx, dword ptr [ebp - 0x6d0]
0064cfb0 add esp, 4
0064cfb3 push eax
0064cfb4 lea eax, [ebp - 0x11c4]
0064cfba push eax
0064cfbb call 0x962a60
0064cfc0 mov ecx, eax
0064cfc2 call 0x962750
0064cfc7 movss xmm1, dword ptr [ebp - 0x6c0]
0064cfcf fstp dword ptr [ebp - 0x6ac]
0064cfd5 movss xmm0, dword ptr [ebp - 0x6ac]
0064cfdd comiss xmm1, xmm0
0064cfe0 jbe 0x64cff2
0064cfe2 movss dword ptr [ebp - 0x6c0], xmm0
0064cfea mov dword ptr [ebp - 0x670], esi
0064cff0 jmp 0x64cff8
0064cff2 mov esi, dword ptr [ebp - 0x670]
0064cff8 lea ecx, [ebp - 0xacc]
0064cffe inc edi
0064cfff call 0x4083d0
0064d004 cmp edi, eax
0064d006 jb 0x64cf30
0064d00c mov edi, dword ptr [ebp - 0x6a8]
0064d012 test esi, esi
0064d014 je 0x64d074
0064d01a push esi
0064d01b lea ecx, [ebp - 0xa14]
0064d021 call 0x422ce0
0064d026 movss xmm3, dword ptr [0xb6a2cc]
0064d02e lea eax, [ebp - 0x11cc]
0064d034 push eax
0064d035 lea esi, [edi + 0x294]
0064d03b mov ecx, edi
0064d03d push esi
0064d03e lea eax, [ebp - 0x11d4]
0064d044 push eax
0064d045 mov eax, dword ptr [ebp - 0x670]
0064d04b push eax
0064d04c lea eax, [ebp - 0x11dc]
0064d052 push eax
0064d053 call 0x68e4e0
0064d058 mov ecx, eax
0064d05a call 0x962ac0
0064d05f mov ecx, eax
0064d061 call 0x962560
0064d066 push eax
0064d067 lea ecx, [ebp - 0x960]
0064d06d call 0x962cd0
0064d072 jmp 0x64d07a
0064d074 lea esi, [edi + 0x294]
0064d07a call 0x659200
0064d07f mulss xmm0, dword ptr [0xb6a8cc]
0064d087 addss xmm0, dword ptr [0xb6a940]
0064d08f movss dword ptr [ebp - 0x8dc], xmm0
0064d097 call 0x6c3d90
0064d09c push eax
0064d09d push 0
0064d09f push dword ptr [edi + 0x320]
0064d0a5 lea eax, [ebp - 0x8dc]
0064d0ab push eax
0064d0ac lea eax, [ebp - 0x11e4]
0064d0b2 push eax
0064d0b3 lea ecx, [ebp - 0x960]
0064d0b9 call 0x962b50
0064d0be push eax
0064d0bf lea eax, [edi + 0x2b8]
0064d0c5 mov ecx, esi
0064d0c7 push eax
0064d0c8 lea eax, [ebp - 0x11ec]
0064d0ce push eax
0064d0cf call 0x962ac0
0064d0d4 mov ecx, dword ptr [0xbfd65c]
0064d0da push eax
0064d0db push dword ptr [edi + 0x2c]
0064d0de push dword ptr [edi + 0x28]
0064d0e1 call 0x422e20
0064d0e6 mov edi, eax
0064d0e8 push ecx
0064d0e9 mov ecx, edi
0064d0eb mov dword ptr [esp], 0xc1be0000
0064d0f2 call 0x6500f0
0064d0f7 lea eax, [ebp - 0x1db4]
0064d0fd mov ecx, 0xbc46c0
0064d102 push eax
0064d103 call 0x57f3a0
0064d108 push eax
0064d109 lea eax, [ebp - 0x1dc4]
0064d10f mov ecx, 0xbc4890
0064d114 push eax
0064d115 call 0x57f3a0
0064d11a push eax
0064d11b lea eax, [ebp - 0x1dd4]
0064d121 mov ecx, 0xbc4a30
0064d126 push eax
0064d127 call 0x57f3a0
0064d12c push eax
0064d12d lea eax, [ebp - 0x1de4]
0064d133 mov ecx, 0xbc4ce0
0064d138 push eax
0064d139 call 0x57f3a0
0064d13e push eax
0064d13f lea eax, [ebp - 0x1df4]
0064d145 mov ecx, 0xbc49e0
0064d14a push eax
0064d14b call 0x57f3a0
0064d150 push eax
0064d151 lea eax, [ebp - 0x1e04]
0064d157 mov ecx, 0xbc4a00
0064d15c push eax
0064d15d call 0x57f3a0
0064d162 mov edx, dword ptr [ebp - 0x6e4]
0064d168 lea ecx, [ebp - 0x1e14]
0064d16e push eax
0064d16f call 0x412050
0064d174 add esp, 4
0064d177 lea ecx, [ebp - 0x1e24]
0064d17d mov edx, eax
0064d17f call 0x412050
0064d184 add esp, 4
0064d187 lea ecx, [ebp - 0x1e34]
0064d18d mov edx, eax
0064d18f call 0x412050
0064d194 add esp, 4
0064d197 lea ecx, [ebp - 0x1e44]
0064d19d mov edx, eax
0064d19f call 0x412050
0064d1a4 add esp, 4
0064d1a7 lea ecx, [ebp - 0x1e54]
0064d1ad mov edx, eax
0064d1af call 0x412050
0064d1b4 add esp, 4
0064d1b7 mov edx, eax
0064d1b9 lea ecx, [ebp - 0xbcc]
0064d1bf call 0x412050
0064d1c4 add esp, 4
0064d1c7 lea ecx, [ebp - 0x1e64]
0064d1cd mov edx, 0xbc4be0
0064d1d2 push 0xbc4cb0
0064d1d7 push 0xbc4cc0
0064d1dc call 0x427220
0064d1e1 add esp, 4
0064d1e4 lea ecx, [ebp - 0x1e74]
0064d1ea mov edx, eax
0064d1ec call 0x427220
0064d1f1 add esp, 4
0064d1f4 lea ecx, [ebp - 0xbcc]
0064d1fa push eax
0064d1fb call 0x4271f0
0064d200 movups xmm0, xmmword ptr [ebp - 0xbcc]
0064d207 sub esp, 0x10
0064d20a mov ecx, edi
0064d20c mov eax, esp
0064d20e movups xmmword ptr [eax], xmm0
0064d211 call 0x650280
0064d216 mov eax, dword ptr [ebp - 0x6b0]
0064d21c push ecx
0064d21d mov ecx, edi
0064d21f movss xmm0, dword ptr [eax]
0064d223 mulss xmm0, dword ptr [0xb6a350]
0064d22b movss dword ptr [esp], xmm0
0064d230 call 0x650250
0064d235 mov ecx, dword ptr [ebp - 0x69c]
0064d23b mov esi, dword ptr [edi]
0064d23d push 1
0064d23f push 0
0064d241 push 0xff
0064d246 push -1
0064d248 call 0x4023b0
0064d24d push eax
0064d24e mov eax, dword ptr [esi + 0x38]
0064d251 mov ecx, edi
0064d253 call eax
0064d255 mov eax, dword ptr [ebp - 0x6a8]
0064d25b mov ecx, edi
0064d25d push dword ptr [eax + 0x314]
0064d263 call 0x6818e0
0064d268 mov eax, dword ptr [ebp - 0x678]
0064d26e lea ecx, [edi + 0x394]
0064d274 push dword ptr [eax]
0064d276 call 0x422ce0
0064d27b push 0x800
0064d280 push 0
0064d282 mov ecx, edi
0064d284 call 0x4122a0
0064d289 mov eax, dword ptr [edi]
0064d28b mov ecx, edi
0064d28d mov eax, dword ptr [eax + 0xc]
0064d290 call eax
0064d292 mov eax, dword ptr [ebp - 0x680]
0064d298 mov edi, dword ptr [ebp - 0x6a8]
0064d29e inc eax
0064d29f mov dword ptr [ebp - 0x680], eax
0064d2a5 lea esi, [edi + 0x294]
0064d2ab cmp eax, dword ptr [ebp - 0x6bc]
0064d2b1 jl 0x64cea0
0064d2b7 mov esi, dword ptr [ebp - 0x6d0]
0064d2bd lea ecx, [ebp - 0xacc]
0064d2c3 call 0x412490
0064d2c8 lea ecx, [ebp - 0xa14]
0064d2ce mov dword ptr [ebp - 4], 0xffffffff
0064d2d5 call 0x40eb90
0064d2da jmp 0x64d33b
0064d2df mov eax, dword ptr [edi + 0x2c]
0064d2e2 cmp eax, 0x1a
0064d2e5 je 0x64d2f0
0064d2e7 cmp eax, 0x30
0064d2ea jne 0x64d33b
0064d2f0 push 0xa081d4
0064d2f5 lea ecx, [edi + 0x3c]
0064d2f8 call 0x405640
0064d2fd test al, al
0064d2ff jne 0x64d33b
0064d301 lea eax, [ebp - 0x140]
0064d307 push eax
0064d308 lea ecx, [edi + 0x3c]
0064d30b call 0x419b40
0064d310 mov ecx, eax
0064d312 call 0x444be0
0064d317 push 0
0064d319 push eax
0064d31a lea ecx, [edi + 0x3c]
0064d31d mov dword ptr [ebp - 4], 0xd
0064d324 call 0x4054d0
0064d329 lea ecx, [ebp - 0x140]
0064d32f mov dword ptr [ebp - 4], 0xffffffff
0064d336 call 0x407330
0064d33b push 0xbc4b50
0064d340 lea edx, [edi + 0x378]
0064d346 lea ecx, [ebp - 0x1e84]
0064d34c call 0x412050
0064d351 add esp, 4
0064d354 mov ecx, eax
0064d356 call 0x412090
0064d35b test al, al
0064d35d je 0x64d395
0064d35f push dword ptr [edi + 0x20]
0064d362 mov ecx, edi
0064d364 push 0x1e
0064d366 call 0x684790
0064d36b test al, al
0064d36d je 0x64d395
0064d36f mov ecx, dword ptr [edi + 0x3c8]
0064d375 test ecx, ecx
0064d377 je 0x64d395
0064d379 push 0
0064d37b call 0x684630
0064d380 test al, al
0064d382 je 0x64d395
0064d384 push dword ptr [edi + 0x3c8]
0064d38a lea ecx, [edi + 0x394]
0064d390 call 0x641430
0064d395 push 0xbc4ce0
0064d39a lea edx, [edi + 0x378]
0064d3a0 lea ecx, [ebp - 0x1e94]
0064d3a6 call 0x412050
0064d3ab add esp, 4
0064d3ae mov ecx, eax
0064d3b0 call 0x412090
0064d3b5 test al, al
0064d3b7 je 0x64d41a
0064d3bd mov ecx, edi
0064d3bf call 0x6520e0
0064d3c4 test al, al
0064d3c6 je 0x64d41a
0064d3cc push 0xbc4940
0064d3d1 lea edx, [edi + 0x378]
0064d3d7 lea ecx, [ebp - 0x1ea4]
0064d3dd call 0x412050
0064d3e2 add esp, 4
0064d3e5 mov ecx, eax
0064d3e7 call 0x427260
0064d3ec test al, al
0064d3ee je 0x64d41a
0064d3f0 push ecx
0064d3f1 mov ecx, dword ptr [0xbfd65c]
0064d3f7 lea eax, [ebp - 0x11f4]
0064d3fd mov dword ptr [esp], 0
0064d404 push esi
0064d405 push eax
0064d406 call 0x4023f0
0064d40b mov ecx, eax
0064d40d call 0x427710
0064d412 push eax
0064d413 mov ecx, esi
0064d415 call 0x962cd0
0064d41a lea eax, [ebp - 0x968]
0064d420 mov ecx, esi
0064d422 push eax
0064d423 lea eax, [ebp - 0x11fc]
0064d429 push eax
0064d42a call 0x962ac0
0064d42f push eax
0064d430 lea ecx, [edi + 0x73c]
0064d436 call 0x962cd0
0064d43b cmp dword ptr [edi + 0x388], 0
0064d442 jg 0x64d794
0064d448 push 0xbc4ce0
0064d44d lea edx, [edi + 0x378]
0064d453 lea ecx, [ebp - 0x1eb4]
0064d459 call 0x412050
0064d45e add esp, 4
0064d461 mov ecx, eax
0064d463 call 0x427260
0064d468 test al, al
0064d46a je 0x64d794
0064d470 cmp byte ptr [edi + 0x16b], 0
0064d477 jne 0x64d794
0064d47d cmp dword ptr [edi + 0x3c8], 0
0064d484 jne 0x64d794
0064d48a push 0xbc4820
0064d48f lea edx, [edi + 0x378]
0064d495 lea ecx, [ebp - 0x1ec4]
0064d49b call 0x412050
0064d4a0 add esp, 4
0064d4a3 mov ecx, eax
0064d4a5 call 0x427260
0064d4aa test al, al
0064d4ac je 0x64d794
0064d4b2 push 0xbc4790
0064d4b7 lea edx, [edi + 0x378]
0064d4bd lea ecx, [ebp - 0x1ed4]
0064d4c3 call 0x412050
0064d4c8 add esp, 4
0064d4cb mov ecx, eax
0064d4cd call 0x427260
0064d4d2 test al, al
0064d4d4 jne 0x64d506
0064d4d6 cmp word ptr [edi + 0x3bc], 8
0064d4de jg 0x64d506
0064d4e0 lea ecx, [edi + 0x2b8]
0064d4e6 call 0x962a30
0064d4eb movss xmm0, dword ptr [0xb6a214]
0064d4f3 fstp dword ptr [ebp - 0x668]
0064d4f9 comiss xmm0, dword ptr [ebp - 0x668]
0064d500 jbe 0x64d794
0064d506 push 0xbc48a0
0064d50b lea edx, [edi + 0x378]
0064d511 lea ecx, [ebp - 0x1ee4]
0064d517 call 0x412050
0064d51c add esp, 4
0064d51f mov ecx, eax
0064d521 call 0x412090
0064d526 test al, al
0064d528 je 0x64d5eb
0064d52e movss xmm1, dword ptr [edi + 0x770]
0064d536 mulss xmm1, dword ptr [0xb6a38c]
0064d53e movss xmm0, dword ptr [edi + 0x2fc]
0064d546 comiss xmm0, xmm1
0064d549 jbe 0x64d5d9
0064d54f movss xmm1, dword ptr [edi + 0x368]
0064d557 addss xmm1, dword ptr [0xb6a350]
0064d55f mov dword ptr [ebp - 0x8e4], 0
0064d569 movss dword ptr [ebp - 0x8e0], xmm1
0064d571 movss xmm0, dword ptr [edi + 0x364]
0064d579 movss xmm1, dword ptr [edi + 0x2f4]
0064d581 movss dword ptr [ebp - 0x668], xmm0
0064d589 movss xmm0, dword ptr [0xb6a5a4]
0064d591 call 0x65c960
0064d596 mulss xmm0, dword ptr [ebp - 0x668]
0064d59e lea edx, [ebp - 0x8e0]
0064d5a4 lea ecx, [ebp - 0x8e4]
0064d5aa movss dword ptr [ebp - 0x668], xmm0
0064d5b2 call 0x417c70
0064d5b7 movss xmm3, dword ptr [edi + 0x2f4]
0064d5bf lea ecx, [edi + 0x2f4]
0064d5c5 movaps xmm2, xmm3
0064d5c8 mulss xmm2, dword ptr [eax]
0064d5cc addss xmm2, dword ptr [ebp - 0x668]
0064d5d4 jmp 0x64d62e
0064d5d9 movss xmm2, dword ptr [ebp - 0x67c]
0064d5e1 movss xmm3, dword ptr [edi + 0x2f4]
0064d5e9 jmp 0x64d62e
0064d5eb movss xmm1, dword ptr [edi + 0x2f4]
0064d5f3 movss xmm0, dword ptr [0xb6a5a4]
0064d5fb call 0x65c960
0064d600 movss xmm3, dword ptr [edi + 0x2f4]
0064d608 mulss xmm0, dword ptr [edi + 0x364]
0064d610 movaps xmm1, xmm3
0064d613 mulss xmm1, dword ptr [0xb6a2cc]
0064d61b movaps xmm2, xmm3
0064d61e mulss xmm2, dword ptr [edi + 0x368]
0064d626 addss xmm1, xmm0
0064d62a addss xmm2, xmm1
0064d62e mulss xmm3, xmm2
0064d632 push ecx
0064d633 movss dword ptr [edi + 0x364], xmm2
0064d63b mov ecx, edi
0064d63d addss xmm3, dword ptr [edi + 0x360]
0064d645 movss dword ptr [esp], xmm3
0064d64a call 0x6500f0
0064d64f mov ecx, dword ptr [0xbfd65c]
0064d655 call 0x4023f0
0064d65a mov ecx, eax
0064d65c call 0x7a8ca0
0064d661 test al, al
0064d663 je 0x64d794
0064d669 push 0xbc48a0
0064d66e lea edx, [edi + 0x378]
0064d674 lea ecx, [ebp - 0x1ef4]
0064d67a call 0x412050
0064d67f add esp, 4
0064d682 mov ecx, eax
0064d684 call 0x412090
0064d689 test al, al
0064d68b jne 0x64d6d1
0064d68d movss xmm0, dword ptr [edi + 0x368]
0064d695 comiss xmm0, dword ptr [0xb6a1c8]
0064d69c jb 0x64d6a8
0064d69e addss xmm0, dword ptr [edi + 0x2bc]
0064d6a6 jmp 0x64d6c9
0064d6a8 movss xmm0, dword ptr [edi + 0x360]
0064d6b0 comiss xmm0, dword ptr [ebp - 0x6c8]
0064d6b7 jbe 0x64d6d1
0064d6b9 movss xmm0, dword ptr [edi + 0x2bc]
0064d6c1 addss xmm0, dword ptr [ebp - 0x68c]
0064d6c9 movss dword ptr [edi + 0x2bc], xmm0
0064d6d1 mov ecx, dword ptr [0xbfd65c]
0064d6d7 call 0x4023f0
0064d6dc mov ecx, eax
0064d6de call 0x7e2590
0064d6e3 test al, al
0064d6e5 je 0x64d794
0064d6eb mov ecx, edi
0064d6ed call 0x682200
0064d6f2 cmp eax, 2
0064d6f5 jle 0x64d794
0064d6fb movss xmm0, dword ptr [edi + 0x2bc]
0064d703 comiss xmm0, dword ptr [ebp - 0x67c]
0064d70a jbe 0x64d794
0064d710 mov ecx, dword ptr [0xbfd65c]
0064d716 call 0x4023f0
0064d71b mov ecx, eax
0064d71d call 0x7e25b0
0064d722 movss xmm1, dword ptr [edi + 0x298]
0064d72a comiss xmm1, xmm0
0064d72d jbe 0x64d794
0064d733 push 0xbc4ca0
0064d738 lea edx, [edi + 0x378]
0064d73e lea ecx, [ebp - 0x1f04]
0064d744 call 0x412050
0064d749 add esp, 4
0064d74c mov ecx, eax
0064d74e call 0x412090
0064d753 test al, al
0064d755 je 0x64d760
0064d757 mov byte ptr [edi + 0x16b], 1
0064d75e jmp 0x64d794
0064d760 mov eax, dword ptr [edi]
0064d762 mov ecx, edi
0064d764 mov eax, dword ptr [eax + 0x28]
0064d767 call eax
0064d769 call 0x6c3d90
0064d76e mov ecx, dword ptr [0xbfd65c]
0064d774 push eax
0064d775 push 0x42
0064d777 push 0
0064d779 push 0xc02fec
0064d77e push esi
0064d77f push 0x10
0064d781 push 0x3e8
0064d786 call 0x422e20
0064d78b mov ecx, eax
0064d78d mov edx, dword ptr [eax]
0064d78f mov eax, dword ptr [edx + 0xc]
0064d792 call eax
0064d794 mov ecx, dword ptr [0xbfd65c]
0064d79a call 0x4023f0
0064d79f mov ecx, eax
0064d7a1 call 0x7a8ca0
0064d7a6 test al, al
0064d7a8 je 0x64d7d2
0064d7aa push ecx
0064d7ab mov ecx, dword ptr [0xbfd65c]
0064d7b1 mov dword ptr [esp], 0xc3800000
0064d7b8 push esi
0064d7b9 call 0x4023f0
0064d7be mov ecx, eax
0064d7c0 call 0x7cf0a0
0064d7c5 test al, al
0064d7c7 jne 0x64d7d2
0064d7c9 mov eax, dword ptr [edi]
0064d7cb mov ecx, edi
0064d7cd mov eax, dword ptr [eax + 0x28]
0064d7d0 call eax
0064d7d2 push 0xbc4940
0064d7d7 lea edx, [edi + 0x378]
0064d7dd lea ecx, [ebp - 0x1f14]
0064d7e3 call 0x412050
0064d7e8 add esp, 4
0064d7eb mov ecx, eax
0064d7ed call 0x412090
0064d7f2 test al, al
0064d7f4 je 0x64db01
0064d7fa push 0xbc4ce0
0064d7ff lea edx, [edi + 0x378]
0064d805 lea ecx, [ebp - 0x1f24]
0064d80b call 0x412050
0064d810 add esp, 4
0064d813 mov ecx, eax
0064d815 call 0x427260
0064d81a test al, al
0064d81c jne 0x64d82d
0064d81e mov ecx, edi
0064d820 call 0x6520e0
0064d825 test al, al
0064d827 je 0x64db01
0064d82d push ecx
0064d82e mov ecx, dword ptr [0xbfd65c]
0064d834 lea eax, [ebp - 0x798]
0064d83a mov dword ptr [esp], 0xc2c80000
0064d841 push esi
0064d842 push eax
0064d843 call 0x4023f0
0064d848 mov ecx, eax
0064d84a call 0x62f0d0
0064d84f push esi
0064d850 lea eax, [ebp - 0xb54]
0064d856 push eax
0064d857 lea ecx, [ebp - 0x798]
0064d85d call 0x962ac0
0064d862 lea eax, [ebp - 0x798]
0064d868 mov ecx, esi
0064d86a push eax
0064d86b call 0x962ca0
0064d870 test al, al
0064d872 je 0x64d8be
0064d878 push 0xbc46a0
0064d87d lea edx, [edi + 0x378]
0064d883 lea ecx, [ebp - 0x1f34]
0064d889 call 0x412050
0064d88e add esp, 4
0064d891 mov ecx, eax
0064d893 call 0x412090
0064d898 test al, al
0064d89a je 0x64d8be
0064d89c mov ecx, dword ptr [edi + 0x314]
0064d8a2 test ecx, ecx
0064d8a4 je 0x64d8be
0064d8a6 lea eax, [ebp - 0x1204]
0064d8ac push eax
0064d8ad call 0x412130
0064d8b2 push eax
0064d8b3 lea ecx, [ebp - 0x798]
0064d8b9 call 0x962cd0
0064d8be lea eax, [ebp - 0x798]
0064d8c4 mov ecx, esi
0064d8c6 push eax
0064d8c7 call 0x962cd0
0064d8cc push 0xbc4ce0
0064d8d1 lea edx, [edi + 0x378]
0064d8d7 lea ecx, [ebp - 0x1f44]
0064d8dd call 0x412050
0064d8e2 add esp, 4
0064d8e5 mov ecx, eax
0064d8e7 call 0x412090
0064d8ec test al, al
0064d8ee je 0x64d948
0064d8f4 mov ecx, edi
0064d8f6 call 0x6520e0
0064d8fb test al, al
0064d8fd je 0x64d948
0064d903 mov esi, dword ptr [edi + 0x318]
0064d909 test esi, esi
0064d90b je 0x64d948
0064d90d nop dword ptr [eax]
0064d910 lea eax, [ebp - 0xb54]
0064d916 mov ecx, esi
0064d918 push eax
0064d919 lea eax, [ebp - 0x120c]
0064d91f push eax
0064d920 lea eax, [ebp - 0x1214]
0064d926 push eax
0064d927 call 0x412130
0064d92c mov ecx, eax
0064d92e call 0x962a60
0064d933 push eax
0064d934 mov ecx, esi
0064d936 call 0x427300
0064d93b mov ecx, esi
0064d93d call 0x422c20
0064d942 mov esi, eax
0064d944 test esi, esi
0064d946 jne 0x64d910
0064d948 push dword ptr [edi + 0x20]
0064d94b mov ecx, edi
0064d94d push 2
0064d94f call 0x684790
0064d954 test al, al
0064d956 je 0x64db01
0064d95c mov ecx, edi
0064d95e call 0x682200
0064d963 cdq 
0064d964 lea ecx, [ebp - 0x3c]
0064d967 sub eax, edx
0064d969 mov esi, eax
0064d96b sar esi, 1
0064d96d call 0x402120
0064d972 mov eax, 0x38e38e39
0064d977 imul esi
0064d979 sar edx, 1
0064d97b mov eax, edx
0064d97d shr eax, 0x1f
0064d980 add eax, edx
0064d982 lea eax, [eax + eax*8]
0064d985 sub esi, eax
0064d987 cmp esi, 8
0064d98a ja 0x64dae9
0064d990 jmp dword ptr [esi*4 + 0x64dc90]
0064d997 sub esp, 0x10
0064d99a mov dword ptr [esp + 0xc], 0x3f800000
0064d9a2 mov dword ptr [esp + 8], 0x3f800000
0064d9aa mov dword ptr [esp + 4], 0x3ea8f5c3
0064d9b2 jmp 0x64dada
0064d9b7 sub esp, 0x10
0064d9ba mov dword ptr [esp + 0xc], 0x3f800000
0064d9c2 mov dword ptr [esp + 8], 0x3f800000
0064d9ca mov dword ptr [esp + 4], 0x3f28f5c3
0064d9d2 jmp 0x64dada
0064d9d7 sub esp, 0x10
0064d9da mov dword ptr [esp + 0xc], 0x3f800000
0064d9e2 mov dword ptr [esp + 8], 0x3f800000
0064d9ea mov dword ptr [esp + 4], 0x3f800000
0064d9f2 jmp 0x64dada
0064d9f7 sub esp, 0x10
0064d9fa mov dword ptr [esp + 0xc], 0x3f800000
0064da02 mov dword ptr [esp + 8], 0x3f28f5c3
0064da0a mov dword ptr [esp + 4], 0x3f28f5c3
0064da12 mov dword ptr [esp], 0x3f28f5c3
0064da19 jmp 0x64dae1
0064da1e sub esp, 0x10
0064da21 mov dword ptr [esp + 0xc], 0x3f800000
0064da29 mov dword ptr [esp + 8], 0x3ea8f5c3
0064da31 mov dword ptr [esp + 4], 0x3ea8f5c3
0064da39 mov dword ptr [esp], 0x3ea8f5c3
0064da40 jmp 0x64dae1
0064da45 sub esp, 0x10
0064da48 lea ecx, [ebp - 0x3c]
0064da4b mov dword ptr [esp + 0xc], 0x3f800000
0064da53 mov dword ptr [esp + 8], 0
0064da5b mov dword ptr [esp + 4], 0
0064da63 mov dword ptr [esp], 0
0064da6a call 0x65ae20
0064da6f jmp 0x64dae9
0064da74 sub esp, 0x10
0064da77 mov dword ptr [esp + 0xc], 0x3f800000
0064da7f mov dword ptr [esp + 8], 0x3ea8f5c3
0064da87 mov dword ptr [esp + 4], 0
0064da8f mov dword ptr [esp], 0x3ea8f5c3
0064da96 jmp 0x64dae1
0064da9b sub esp, 0x10
0064da9e mov dword ptr [esp + 0xc], 0x3f800000
0064daa6 mov dword ptr [esp + 8], 0x3f28f5c3
0064daae mov dword ptr [esp + 4], 0
0064dab6 mov dword ptr [esp], 0x3f28f5c3
0064dabd jmp 0x64dae1
0064dabf sub esp, 0x10
0064dac2 mov dword ptr [esp + 0xc], 0x3f800000
0064daca mov dword ptr [esp + 8], 0x3f800000
0064dad2 mov dword ptr [esp + 4], 0
0064dada mov dword ptr [esp], 0x3f800000
0064dae1 lea ecx, [ebp - 0x3c]
0064dae4 call 0x65aeb0
0064dae9 mov eax, dword ptr [edi]
0064daeb lea ecx, [ebp - 0x3c]
0064daee push 1
0064daf0 push 0
0064daf2 push 0xff
0064daf7 mov eax, dword ptr [eax + 0x38]
0064dafa push -1
0064dafc push ecx
0064dafd mov ecx, edi
0064daff call eax
0064db01 mov ecx, dword ptr [0xbfd65c]
0064db07 call 0x4023f0
0064db0c mov ecx, eax
0064db0e call 0x448070
0064db13 test al, al
0064db15 je 0x64db58
0064db17 movss xmm2, dword ptr [ebp - 0x684]
0064db1f movss xmm3, dword ptr [0xb6a690]
0064db27 movaps xmm1, xmm2
0064db2a mov esi, dword ptr [edi]
0064db2c push 1
0064db2e push 0
0064db30 push 0xff
0064db35 push 2
0064db37 push 0x28
0064db39 push 0x28
0064db3b push 0x28
0064db3d push ecx
0064db3e lea ecx, [ebp - 0x530]
0064db44 mov dword ptr [esp], 0x3f800000
0064db4b call 0x4270d0
0064db50 push eax
0064db51 mov eax, dword ptr [esi + 0x38]
0064db54 mov ecx, edi
0064db56 call eax
0064db58 mov ecx, dword ptr [0xbfd674]
0064db5e push edi
0064db5f call 0x7ff160
0064db64 mov ecx, dword ptr [ebp - 0xc]
0064db67 mov dword ptr fs:[0], ecx
0064db6e pop ecx
0064db6f pop edi
0064db70 pop esi
0064db71 mov ecx, dword ptr [ebp - 0x10]
0064db74 xor ecx, ebp
0064db76 call 0x9eacd7
0064db7b mov esp, ebp
0064db7d pop ebp
0064db7e ret 
