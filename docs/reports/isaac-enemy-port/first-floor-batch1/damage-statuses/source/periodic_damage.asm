00687038 mov ecx, dword ptr [edi + 0x160]
0068703e mov eax, ecx
00687040 mov esi, dword ptr [edi + 0x164]
00687046 and eax, 0x4000
0068704b or eax, 0
0068704e mov dword ptr [esp + 0x14], ecx
00687052 jne 0x687def
00687058 mov eax, dword ptr [edi + 0x28]
0068705b sub eax, 0xa
0068705e cmp eax, 0x3dd
00687063 ja 0x687821
00687069 mov eax, ecx
0068706b mov dword ptr [esp + 0x30], 0x14
00687073 and eax, 0x40
00687076 or eax, 0
00687079 je 0x687137
0068707f mov ecx, dword ptr [edi + 0x238]
00687085 mov eax, ecx
00687087 cdq 
00687088 idiv dword ptr [esp + 0x30]
0068708c lea eax, [ecx + 1]
0068708f mov ecx, dword ptr [edi + 0x160]
00687095 mov dword ptr [edi + 0x238], eax
0068709b mov dword ptr [esp + 0x14], ecx
0068709f cmp edx, 1
006870a2 jne 0x687137
006870a8 mov eax, dword ptr [edi]
006870aa lea ecx, [esp + 0x12c]
006870b1 push edx
006870b2 push 0
006870b4 push 0xff
006870b9 xorps xmm0, xmm0
006870bc mov dword ptr [esp + 0x158], 0
006870c7 push 2
006870c9 movups xmmword ptr [esp + 0x14c], xmm0
006870d1 push ecx
006870d2 movaps xmm0, xmmword ptr [0xb6bfd0]
006870d9 mov ecx, edi
006870db movups xmmword ptr [esp + 0x140], xmm0
006870e3 mov dword ptr [esp + 0x164], 0x3f000000
006870ee mov dword ptr [esp + 0x168], 0
006870f9 call dword ptr [eax + 0x38]
006870fc mov edx, dword ptr [edi]
006870fe lea ecx, [esp + 0xb0]
00687105 push 0x1e
00687107 call 0x427290
0068710c movss xmm0, dword ptr [edi + 0x278]
00687114 push eax
00687115 push 0
00687117 push 0x8000
0068711c push ecx
0068711d mov ecx, edi
0068711f movss dword ptr [esp], xmm0
00687124 call dword ptr [edx + 0x20]
00687127 mov ecx, dword ptr [edi + 0x160]
0068712d mov esi, dword ptr [edi + 0x164]
00687133 mov dword ptr [esp + 0x14], ecx
00687137 mov eax, ecx
00687139 mov dword ptr [esp + 0x40], ecx
0068713d and eax, 0x1000
00687142 or eax, 0
00687145 je 0x687201
0068714b mov ecx, dword ptr [edi + 0x23c]
00687151 mov eax, ecx
00687153 cdq 
00687154 idiv dword ptr [esp + 0x30]
00687158 lea eax, [ecx + 1]
0068715b mov dword ptr [edi + 0x23c], eax
00687161 mov eax, dword ptr [esp + 0x14]
00687165 mov dword ptr [esp + 0x40], eax
00687169 cmp edx, 1
0068716c jne 0x687201
00687172 mov eax, dword ptr [edi]
00687174 lea ecx, [esp + 0x12c]
0068717b push edx
0068717c push 0
0068717e push 0xff
00687183 xorps xmm0, xmm0
00687186 mov dword ptr [esp + 0x158], 0x3f000000
00687191 push 2
00687193 movups xmmword ptr [esp + 0x14c], xmm0
0068719b push ecx
0068719c movaps xmm0, xmmword ptr [0xb6bfc0]
006871a3 mov ecx, edi
006871a5 movups xmmword ptr [esp + 0x140], xmm0
006871ad mov dword ptr [esp + 0x164], 0x3e99999a
006871b8 mov dword ptr [esp + 0x168], 0
006871c3 call dword ptr [eax + 0x38]
006871c6 mov edx, dword ptr [edi]
006871c8 lea ecx, [esp + 0xd8]
006871cf push 0x1e
006871d1 call 0x427290
006871d6 movss xmm0, dword ptr [edi + 0x27c]
006871de push eax
006871df push 0
006871e1 push 0x8000
006871e6 push ecx
006871e7 mov ecx, edi
006871e9 movss dword ptr [esp], xmm0
006871ee call dword ptr [edx + 0x20]
006871f1 mov eax, dword ptr [edi + 0x160]
006871f7 mov esi, dword ptr [edi + 0x164]
006871fd mov dword ptr [esp + 0x40], eax
