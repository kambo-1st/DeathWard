00634eb5 mov eax, dword ptr [edi + 0x388]
00634ebb mov ecx, dword ptr [edi + 0x38c]
00634ec1 and eax, 0x1800
00634ec6 or eax, 0
00634ec9 je 0x6351e1
00634ecf and ecx, 0x1000000
00634ed5 xor eax, eax
00634ed7 or eax, ecx
00634ed9 je 0x6350a2
00634edf cmp dword ptr [edi + 0x314], 0
00634ee6 je 0x6350a2
00634eec lea eax, [edi + 0x3b0]
00634ef2 push eax
00634ef3 lea ecx, [edi + 0x2b8]
00634ef9 call 0x962af0
00634efe mov ecx, dword ptr [edi + 0x314]
00634f04 lea eax, [ebp - 0x32c]
00634f0a push eax
00634f0b call 0x412130
00634f10 push eax
00634f11 lea eax, [ebp - 0x3d4]
00634f17 push eax
00634f18 lea ecx, [edi + 0x294]
00634f1e call 0x962ac0
00634f23 movss xmm1, dword ptr [ebp - 0x3d0]
00634f2b lea ecx, [ebp - 0x464]
00634f31 xorps xmm1, xmmword ptr [0xb6c9b0]
00634f38 movss xmm2, dword ptr [ebp - 0x3d4]
00634f40 call 0x9624e0
00634f45 mov eax, dword ptr [edi + 0x388]
00634f4b and eax, 0x1000
00634f50 or eax, 0
00634f53 je 0x634f73
00634f55 lea eax, [ebp - 0x32c]
00634f5b push eax
00634f5c lea ecx, [ebp - 0x464]
00634f62 call 0x962b20
00634f67 push eax
00634f68 lea ecx, [ebp - 0x464]
00634f6e call 0x962cd0
00634f73 movss xmm0, dword ptr [edi + 0x380]
00634f7b lea ecx, [ebp - 0x3d4]
00634f81 comiss xmm0, dword ptr [0xb6a18c]
00634f88 jbe 0x634fda
00634f8a call 0x962a00
00634f8f fdiv dword ptr [edi + 0x380]
00634f95 fld1 
00634f97 movss xmm1, dword ptr [0xb6a614]
00634f9f fsubrp st(1)
00634fa1 movss xmm0, dword ptr [0xb6ae44]
00634fa9 fstp dword ptr [ebp - 0x30c]
00634faf movss xmm2, dword ptr [ebp - 0x30c]
00634fb7 call 0x9623e0
00634fbc mulss xmm0, dword ptr [0xb6a480]
00634fc4 lea eax, [ebp - 0x310]
00634fca lea ecx, [ebp - 0x3d4]
00634fd0 movss dword ptr [ebp - 0x310], xmm0
00634fd8 jmp 0x634fea
00634fda mov dword ptr [ebp - 0x30c], 0x3f000000
00634fe4 lea eax, [ebp - 0x30c]
00634fea push eax
00634feb call 0x962bb0
00634ff0 lea ecx, [edi + 0x2b8]
00634ff6 call 0x962a00
00634ffb lea eax, [ebp - 0x30c]
00635001 push eax
00635002 lea eax, [ebp - 0x32c]
00635008 push eax
00635009 lea eax, [ebp - 0x350]
0063500f push eax
00635010 lea eax, [ebp - 0x464]
00635016 push eax
00635017 lea eax, [ebp - 0x370]
0063501d push eax
0063501e lea ecx, [ebp - 0x3d4]
00635024 fstp dword ptr [ebp - 0x30c]
0063502a call 0x962a60
0063502f mov ecx, eax
00635031 call 0x962560
00635036 mov ecx, eax
00635038 call 0x962b50
0063503d push eax
0063503e lea ecx, [edi + 0x2b8]
00635044 call 0x962cd0
00635049 mov ecx, dword ptr [edi + 0x314]
0063504f lea eax, [ebp - 0x360]
00635055 push eax
00635056 call 0x412170
0063505b push eax
0063505c lea ecx, [edi + 0x2b8]
00635062 call 0x962a90
00635067 mov ecx, dword ptr [edi + 0x314]
0063506d lea eax, [ebp - 0x3a4]
00635073 push eax
00635074 call 0x412170
00635079 push eax
0063507a lea ecx, [edi + 0x3b0]
00635080 call 0x962cd0
00635085 mov ecx, dword ptr [edi + 0x314]
0063508b lea eax, [ebp - 0x4c8]
00635091 push eax
00635092 call 0x412130
00635097 lea ecx, [edi + 0x28c]
0063509d jmp 0x6351db
006350a2 lea eax, [edi + 0x28c]
006350a8 push eax
006350a9 lea eax, [ebp - 0x39c]
006350af push eax
006350b0 lea ecx, [edi + 0x294]
006350b6 call 0x962ac0
006350bb movss xmm1, dword ptr [ebp - 0x398]
006350c3 lea ecx, [ebp - 0x3dc]
006350c9 xorps xmm1, xmmword ptr [0xb6c9b0]
006350d0 movss xmm2, dword ptr [ebp - 0x39c]
006350d8 call 0x9624e0
006350dd mov eax, dword ptr [edi + 0x388]
006350e3 and eax, 0x1000
006350e8 or eax, 0
006350eb je 0x63510b
006350ed lea eax, [ebp - 0x4c8]
006350f3 push eax
006350f4 lea ecx, [ebp - 0x3dc]
006350fa call 0x962b20
006350ff push eax
00635100 lea ecx, [ebp - 0x3dc]
00635106 call 0x962cd0
0063510b movss xmm0, dword ptr [edi + 0x380]
00635113 lea ecx, [ebp - 0x39c]
00635119 comiss xmm0, dword ptr [0xb6a18c]
00635120 jbe 0x635172
00635122 call 0x962a00
00635127 fdiv dword ptr [edi + 0x380]
0063512d fld1 
0063512f movss xmm1, dword ptr [0xb6a614]
00635137 fsubrp st(1)
00635139 movss xmm0, dword ptr [0xb6ae44]
00635141 fstp dword ptr [ebp - 0x30c]
00635147 movss xmm2, dword ptr [ebp - 0x30c]
0063514f call 0x9623e0
00635154 mulss xmm0, dword ptr [0xb6a480]
0063515c lea eax, [ebp - 0x310]
00635162 lea ecx, [ebp - 0x39c]
00635168 movss dword ptr [ebp - 0x310], xmm0
00635170 jmp 0x635182
00635172 mov dword ptr [ebp - 0x30c], 0x3f000000
0063517c lea eax, [ebp - 0x30c]
00635182 push eax
00635183 call 0x962bb0
00635188 lea ecx, [edi + 0x2b8]
0063518e call 0x962a00
00635193 lea eax, [ebp - 0x48c]
00635199 push eax
0063519a lea eax, [ebp - 0x4f0]
006351a0 push eax
006351a1 lea eax, [ebp - 0x4f8]
006351a7 push eax
006351a8 lea eax, [ebp - 0x3dc]
006351ae push eax
006351af lea eax, [ebp - 0x500]
006351b5 push eax
006351b6 lea ecx, [ebp - 0x39c]
006351bc fstp dword ptr [ebp - 0x48c]
006351c2 call 0x962a60
006351c7 mov ecx, eax
006351c9 call 0x962560
006351ce mov ecx, eax
006351d0 call 0x962b50
006351d5 lea ecx, [edi + 0x2b8]
006351db push eax
006351dc call 0x962cd0
