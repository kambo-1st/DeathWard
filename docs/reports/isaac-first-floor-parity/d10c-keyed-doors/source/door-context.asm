006e0bc0 push ebp
006e0bc1 mov ebp, esp
006e0bc3 and esp, 0xfffffff8
006e0bc6 sub esp, 0x68
006e0bc9 push esi
006e0bca push edi
006e0bcb mov edi, ecx
006e0bcd test byte ptr [edi + 0x288], 0x10
006e0bd4 jne 0x6e13a4
006e0bda mov esi, dword ptr [ebp + 8]
006e0bdd cmp byte ptr [esi + 0x1f88], 0
006e0be4 jne 0x6e13a4
006e0bea cmp byte ptr [ebp + 0xc], 0
006e0bee jne 0x6e10fe
006e0bf4 cmp dword ptr [edi + 8], 1
006e0bf8 jne 0x6e10fe
006e0bfe cmp dword ptr [edi + 0x15c], 0x1b
006e0c05 jne 0x6e10fe
006e0c0b call 0x6dd9b0
006e0c10 cmp eax, 3
006e0c13 jne 0x6e10fe
006e0c19 test byte ptr [edi + 0x288], 0x40
006e0c20 je 0x6e0dac
006e0c26 lea eax, [esp + 0x10]
006e0c2a mov dword ptr [esp + 0xc], 0
006e0c32 push eax
006e0c33 lea edx, [esp + 0x10]
006e0c37 mov dword ptr [esp + 0x14], 0
006e0c3f mov ecx, esi
006e0c41 call 0x6e0ac0
006e0c46 mov edx, eax
006e0c48 add esp, 4
006e0c4b test edx, edx
006e0c4d je 0x6e13a4
006e0c53 mov eax, dword ptr [esp + 0xc]
006e0c57 mov ecx, dword ptr [esp + 0x10]
006e0c5b test eax, eax
006e0c5d je 0x6e0c6f
006e0c5f push 1
006e0c61 push 0
006e0c63 push 0
006e0c65 push eax
006e0c66 mov ecx, edx
006e0c68 call 0x756580
006e0c6d jmp 0x6e0c7b
006e0c6f test ecx, ecx
006e0c71 je 0x6e0c7b
006e0c73 push ecx
006e0c74 mov ecx, edx
006e0c76 call 0x73bf30
006e0c7b mov esi, dword ptr [0xbfd680]
006e0c81 lea ecx, [esp + 0x14]
006e0c85 mov dword ptr [esp + 0x14], 8
006e0c8d call 0x8b1340
006e0c92 sub esp, 8
006e0c95 mov dword ptr [esp + 4], 0
006e0c9d mov dword ptr [esp], 0x3f800000
006e0ca4 push 0
006e0ca6 push 2
006e0ca8 push ecx
006e0ca9 mov dword ptr [esp], 0x3f800000
006e0cb0 lea ecx, [esi + 0x29de0]
006e0cb6 push dword ptr [esp + 0x28]
006e0cba call 0x888de0
006e0cbf mov ecx, dword ptr [0xbfd680]
006e0cc5 sub esp, 8
006e0cc8 push 0x44
006e0cca lea ecx, [ecx + 0x29a78]
006e0cd0 call 0x7a27b0
006e0cd5 mov ecx, edi
006e0cd7 mov dword ptr [edi + 0xc], 2
006e0cde call 0x6df520
006e0ce3 mov dword ptr [edi + 8], 8
006e0cea add edi, 0x40
006e0ced cmp dword ptr [edi + 0x80], 1
006e0cf4 jg 0x6e0d12
006e0cf6 cmp dword ptr [edi + 0x14], 0x10
006e0cfa mov eax, edi
006e0cfc jb 0x6e0d00
006e0cfe mov eax, dword ptr [edi]
006e0d00 push 1
006e0d02 push eax
006e0d03 push 0xa0830c
006e0d08 push 3
006e0d0a call 0x95e330
006e0d0f add esp, 0x10
006e0d12 mov eax, dword ptr [edi + 0x7c]
006e0d15 mov esi, dword ptr [esp + 0xc]
006e0d19 mov byte ptr [eax + 0x110], 0
006e0d20 cmp esi, 0x147
006e0d26 je 0x6e0d34
006e0d28 cmp dword ptr [esp + 0x10], 0x45
006e0d2d mov byte ptr [esp + 0xb], 0
006e0d32 jne 0x6e0d39
006e0d34 mov byte ptr [esp + 0xb], 1
006e0d39 cmp dword ptr [edi + 0x80], 2
006e0d40 jg 0x6e0d5e
006e0d42 cmp dword ptr [edi + 0x14], 0x10
006e0d46 mov eax, edi
006e0d48 jb 0x6e0d4c
006e0d4a mov eax, dword ptr [edi]
006e0d4c push 2
006e0d4e push eax
006e0d4f push 0xa0830c
006e0d54 push 3
006e0d56 call 0x95e330
006e0d5b add esp, 0x10
006e0d5e mov eax, dword ptr [edi + 0x7c]
006e0d61 mov cl, byte ptr [esp + 0xb]
006e0d65 mov byte ptr [eax + 0x1ac], cl
006e0d6b cmp dword ptr [edi + 0x80], 4
006e0d72 jg 0x6e0d90
006e0d74 cmp dword ptr [edi + 0x14], 0x10
006e0d78 mov eax, edi
006e0d7a jb 0x6e0d7e
006e0d7c mov eax, dword ptr [edi]
006e0d7e push 4
006e0d80 push eax
006e0d81 push 0xa0830c
006e0d86 push 3
006e0d88 call 0x95e330
006e0d8d add esp, 0x10
006e0d90 mov eax, dword ptr [edi + 0x7c]
006e0d93 cmp esi, 0x148
006e0d99 sete cl
006e0d9c mov byte ptr [eax + 0x2e4], cl
006e0da2 mov al, 1
006e0da4 pop edi
006e0da5 pop esi
006e0da6 mov esp, ebp
006e0da8 pop ebp
006e0da9 ret 8
006e0dac push 0xb4a758
006e0db1 lea ecx, [edi + 0x40]
006e0db4 call 0x405640
006e0db9 test al, al
006e0dbb jne 0x6e13a4
006e0dc1 mov ecx, esi
006e0dc3 call 0x78cdc0
006e0dc8 cmp eax, 2
006e0dcb je 0x6e10a8
006e0dd1 call 0x79c960
006e0dd6 test al, al
006e0dd8 jne 0x6e10a8
006e0dde mov ecx, dword ptr [0xbfd65c]
006e0de4 push 0x49
006e0de6 lea ecx, [ecx + 0x1bb04]
006e0dec call 0x4480b0
006e0df1 test al, al
006e0df3 jne 0x6e10a8
006e0df9 lea ecx, [esp + 0x44]
006e0dfd call 0x427290
006e0e02 mov eax, dword ptr [esi]
006e0e04 push 0x1e
006e0e06 push ecx
006e0e07 push 0
006e0e09 mov eax, dword ptr [eax + 0x20]
006e0e0c push 0x12002080
006e0e11 push ecx
006e0e12 mov ecx, esi
006e0e14 mov dword ptr [esp + 0x58], 0
006e0e1c mov dword ptr [esp + 0x5c], 0x2713
006e0e24 mov dword ptr [esi + 0x1308], 0
006e0e2e mov dword ptr [esp], 0x40000000
006e0e35 call eax
006e0e37 test al, al
006e0e39 je 0x6e13a4
006e0e3f mov edx, dword ptr [edi + 0x160]
006e0e45 lea ecx, [esp + 0x3c]
006e0e49 call 0x659400
006e0e4e movss xmm1, dword ptr [eax]
006e0e52 xorps xmm1, xmmword ptr [0xb6c9b0]
006e0e59 movss dword ptr [esp + 0x18], xmm1
006e0e5f movss xmm1, dword ptr [eax + 4]
006e0e64 xorps xmm1, xmmword ptr [0xb6c9b0]
006e0e6b movss dword ptr [esp + 0x1c], xmm1
006e0e71 call 0x6c3d90
006e0e76 mov esi, eax
006e0e78 mov ecx, edi
006e0e7a lea eax, [esp + 0x3c]
006e0e7e push eax
006e0e7f call 0x6dae90
006e0e84 mov ecx, dword ptr [0xbfd65c]
006e0e8a push 0
006e0e8c push esi
006e0e8d push 3
006e0e8f push 0
006e0e91 push 0xc02fec
006e0e96 push eax
006e0e97 push 2
006e0e99 push 0x3e8
006e0e9e call 0x6d0ca0
006e0ea3 call 0x6c3d90
006e0ea8 and eax, 1
006e0eab lea esi, [eax + 2]
006e0eae mov dword ptr [esp + 0x24], esi
006e0eb2 call 0x6c3d90
006e0eb7 xor edx, edx
006e0eb9 mov ecx, 0xa
006e0ebe div ecx
006e0ec0 lea eax, [esi + 6]
006e0ec3 xor esi, esi
006e0ec5 add eax, edx
006e0ec7 mov dword ptr [esp + 0x14], esi
006e0ecb mov dword ptr [esp + 0x28], eax
006e0ecf test eax, eax
006e0ed1 jle 0x6e10af
006e0ed7 movss xmm1, dword ptr [0xb6a19c]
006e0edf movss xmm2, dword ptr [0xb6a9ac]
006e0ee7 call 0x6c3d90
006e0eec xorps xmm0, xmm0
006e0eef cvtsi2sd xmm0, eax
006e0ef3 shr eax, 0x1f
006e0ef6 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
006e0eff cvtpd2ps xmm0, xmm0
006e0f03 mulss xmm0, xmm1
006e0f07 mulss xmm0, xmm2
006e0f0b addss xmm0, dword ptr [0xb6a8f4]
006e0f13 movss dword ptr [esp + 0x20], xmm0
006e0f19 call 0x6c3d90
006e0f1e xorps xmm0, xmm0
006e0f21 cvtsi2sd xmm0, eax
006e0f25 shr eax, 0x1f
006e0f28 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
006e0f31 cvtpd2ps xmm0, xmm0
006e0f35 mulss xmm0, xmm1
006e0f39 mulss xmm0, dword ptr [0xb6aa0c]
006e0f41 subss xmm0, xmm2
006e0f45 mulss xmm0, dword ptr [0xb6a230]
006e0f4d movss dword ptr [esp + 0x10], xmm0
006e0f53 call 0x411fe0
006e0f58 movss dword ptr [esp + 0xc], xmm0
006e0f5e movss xmm0, dword ptr [esp + 0x10]
006e0f64 call 0x412010
006e0f69 mov ecx, dword ptr [0xbfd65c]
006e0f6f movaps xmm2, xmm0
006e0f72 movss xmm0, dword ptr [esp + 0xc]
006e0f78 movaps xmm1, xmm2
006e0f7b mulss xmm1, dword ptr [esp + 0x1c]
006e0f81 movaps xmm3, xmm0
006e0f84 mov eax, dword ptr [edi + 0x24]
006e0f87 mulss xmm0, dword ptr [esp + 0x1c]
006e0f8d cdq
006e0f8e mulss xmm3, dword ptr [esp + 0x18]
006e0f94 mulss xmm2, dword ptr [esp + 0x18]
006e0f9a subss xmm3, xmm1
006e0f9e movss xmm1, dword ptr [0xb6aa3c]
006e0fa6 addss xmm2, xmm0
006e0faa xorps xmm0, xmm0
006e0fad mulss xmm3, dword ptr [esp + 0x20]
006e0fb3 mulss xmm2, dword ptr [esp + 0x20]
006e0fb9 movss dword ptr [esp + 0x3c], xmm3
006e0fbf movss dword ptr [esp + 0x40], xmm2
006e0fc5 mov ecx, dword ptr [ecx + 0x18190]
006e0fcb mov ecx, dword ptr [ecx + 0xc]
006e0fce idiv ecx
006e0fd0 cvtsi2ss xmm0, edx
006e0fd4 mulss xmm0, xmm1
006e0fd8 addss xmm0, xmm1
006e0fdc addss xmm0, xmm3
006e0fe0 movss dword ptr [esp + 0x2c], xmm0
006e0fe6 xorps xmm0, xmm0
006e0fe9 cvtsi2ss xmm0, eax
006e0fed mulss xmm0, xmm1
006e0ff1 addss xmm0, dword ptr [0xb6ab20]
006e0ff9 addss xmm0, xmm2
006e0ffd movss dword ptr [esp + 0x30], xmm0
006e1003 call 0x6c3d90
006e1008 mov ecx, dword ptr [0xbfd65c]
006e100e push 0
006e1010 push eax
006e1011 cmp esi, dword ptr [esp + 0x2c]
006e1015 jae 0x6e1056
006e1017 mulss xmm3, dword ptr [0xb6a350]
006e101f lea eax, [esp + 0x3c]
006e1023 push 0
006e1025 mulss xmm2, dword ptr [0xb6a350]
006e102d push 0
006e102f push eax
006e1030 lea eax, [esp + 0x40]
006e1034 movss dword ptr [esp + 0x48], xmm3
006e103a push eax
006e103b push 5
006e103d push 0x3e8
006e1042 movss dword ptr [esp + 0x58], xmm2
006e1048 call 0x6d0ca0
006e104d mov ecx, eax
006e104f mov edx, dword ptr [eax]
006e1051 call dword ptr [edx + 0xc]
006e1054 jmp 0x6e1087
006e1056 push 0x63
006e1058 push 0
006e105a lea eax, [esp + 0x4c]
006e105e push eax
006e105f lea eax, [esp + 0x40]
006e1063 push eax
006e1064 push 5
006e1066 push 0x3e8
006e106b call 0x6d0ca0
006e1070 mov esi, eax
006e1072 mov ecx, esi
006e1074 mov edx, dword ptr [esi]
006e1076 call dword ptr [edx + 0xc]
006e1079 mov dword ptr [esi + 0x364], 0xc1000000
006e1083 mov esi, dword ptr [esp + 0x14]
006e1087 movss xmm1, dword ptr [0xb6a19c]
006e108f inc esi
006e1090 movss xmm2, dword ptr [0xb6a9ac]
006e1098 mov dword ptr [esp + 0x14], esi
006e109c cmp esi, dword ptr [esp + 0x28]
006e10a0 jl 0x6e0ee7
006e10a6 jmp 0x6e10af
006e10a8 mov dword ptr [edi + 0x18], 0
006e10af xor eax, eax
006e10b1 mov ecx, edi
006e10b3 cmp dword ptr [edi + 0x18], eax
006e10b6 setne al
006e10b9 add eax, 2
006e10bc mov dword ptr [edi + 0xc], eax
006e10bf call 0x6df520
006e10c4 mov eax, dword ptr [edi + 0x18]
006e10c7 test eax, eax
006e10c9 jg 0x6e10d4
006e10cb mov dword ptr [edi + 8], 8
006e10d2 jmp 0x6e10d8
006e10d4 dec eax
006e10d5 mov dword ptr [edi + 0x18], eax
006e10d8 movss xmm2, dword ptr [0xb6a614]
006e10e0 sub esp, 8
006e10e3 mov dword ptr [esp + 4], 0x3f800000
006e10eb push 2
006e10ed push 0x48
006e10ef call 0x6dc6e0
006e10f4 mov al, 1
006e10f6 pop edi
006e10f7 pop esi
006e10f8 mov esp, ebp
006e10fa pop ebp
006e10fb ret 8
006e10fe mov eax, dword ptr [edi + 8]
006e1101 mov byte ptr [esp + 0xb], 0
006e1106 cmp eax, 1
006e1109 je 0x6e1110
006e110b cmp eax, 2
006e110e jne 0x6e112e
006e1110 push 0x96
006e1115 mov ecx, esi
006e1117 call 0x78d4c0
006e111c test eax, eax
006e111e jle 0x6e112e
006e1120 mov al, 1
006e1122 mov byte ptr [ebp + 0xc], al
006e1125 mov byte ptr [esp + 0xb], al
006e1129 jmp 0x6e11fe
006e112e mov al, byte ptr [ebp + 0xc]
006e1131 test al, al
006e1133 jne 0x6e11fe
006e1139 mov ecx, dword ptr [edi + 0xc]
006e113c cmp ecx, 2
006e113f je 0x6e13a4
006e1145 mov edx, dword ptr [edi + 8]
006e1148 cmp edx, 1
006e114b je 0x6e1156
006e114d cmp edx, 2
006e1150 jne 0x6e13a4
006e1156 cmp byte ptr [edi + 0x278], 0
006e115d je 0x6e1199
006e115f cmp ecx, 3
006e1162 jne 0x6e1199
006e1164 lea eax, [edi + 0x164]
006e116a push 0xb4a808
006e116f mov ecx, eax
006e1171 call 0x405640
006e1176 test al, al
006e1178 jne 0x6e13a4
006e117e push 0xb4a81c
006e1183 lea ecx, [edi + 0x164]
006e1189 call 0x405640
006e118e test al, al
006e1190 jne 0x6e13a4
006e1196 mov al, byte ptr [ebp + 0xc]
006e1199 test byte ptr [edi + 0x288], 1
006e11a0 je 0x6e11ad
006e11a2 cmp dword ptr [esi + 0x12b8], 0
006e11a9 jg 0x6e11fe
006e11ab jmp 0x6e11c3
006e11ad cmp dword ptr [edi + 0x15c], 2
006e11b4 jne 0x6e11c3
006e11b6 push 0x53
006e11b8 mov ecx, esi
006e11ba call 0x78d4c0
006e11bf test eax, eax
006e11c1 jg 0x6e11fb
006e11c3 cmp dword ptr [edi + 0x15c], 5
006e11ca jne 0x6e11df
006e11cc cmp dword ptr [edi + 0x27c], 0
006e11d3 jl 0x6e11df
006e11d5 mov eax, dword ptr [0xbfd65c]
006e11da cmp dword ptr [eax], 9
006e11dd je 0x6e11fb
006e11df test byte ptr [edi + 0x288], 1
006e11e6 jne 0x6e13a4
006e11ec mov ecx, esi
006e11ee call 0x726070
006e11f3 test al, al
006e11f5 je 0x6e13a4
006e11fb mov al, byte ptr [ebp + 0xc]
006e11fe test byte ptr [edi + 0x288], 1
006e1205 je 0x6e1219
006e1207 test al, al
006e1209 jne 0x6e121d
006e120b push -1
006e120d mov ecx, esi
006e120f call 0x725740
006e1214 mov al, byte ptr [ebp + 0xc]
006e1217 jmp 0x6e1224
006e1219 test al, al
006e121b je 0x6e1224
006e121d mov byte ptr [edi + 0x27a], 1
006e1224 cmp dword ptr [edi + 8], 2
006e1228 jne 0x6e124c
006e122a cmp dword ptr [edi + 0xc], 3
006e122e je 0x6e124c
006e1230 test al, al
006e1232 jne 0x6e124c
006e1234 mov ecx, edi
006e1236 mov dword ptr [edi + 0xc], 3
006e123d call 0x6df520
006e1242 mov al, 1
006e1244 pop edi
006e1245 pop esi
006e1246 mov esp, ebp
006e1248 pop ebp
006e1249 ret 8
006e124c mov ecx, edi
006e124e mov dword ptr [edi + 0xc], 2
006e1255 call 0x6df520
006e125a cmp dword ptr [edi + 0x15c], 5
006e1261 mov dword ptr [edi + 8], 8
006e1268 jne 0x6e129b
006e126a cmp dword ptr [edi + 0x27c], 0
006e1271 jl 0x6e129b
006e1273 mov eax, dword ptr [0xbfd65c]
006e1278 cmp dword ptr [eax], 9
006e127b jne 0x6e129b
006e127d movss xmm2, dword ptr [0xb6a614]
006e1285 sub esp, 8
006e1288 mov dword ptr [esp + 4], 0x3e99999a
006e1290 push 2
006e1292 push 0xe
006e1294 call 0x6dc6e0
006e1299 jmp 0x6e12f0
006e129b test byte ptr [edi + 0x288], 1
006e12a2 lea ecx, [esp + 0x14]
006e12a6 mov esi, dword ptr [0xbfd680]
006e12ac mov dword ptr [esp + 0x14], 0x2d
006e12b4 jne 0x6e12be
006e12b6 mov dword ptr [esp + 0x14], 0x9c
006e12be call 0x8b1340
006e12c3 sub esp, 8
006e12c6 mov dword ptr [esp + 4], 0
006e12ce mov dword ptr [esp], 0x3f800000
006e12d5 push 0
006e12d7 push 2
006e12d9 push ecx
006e12da mov dword ptr [esp], 0x3f800000
006e12e1 lea ecx, [esi + 0x29de0]
006e12e7 push dword ptr [esp + 0x28]
006e12eb call 0x888de0
006e12f0 cmp byte ptr [esp + 0xb], 0
006e12f5 je 0x6e139a
006e12fb push 0xb4a7c8
006e1300 lea ecx, [edi + 0x40]
006e1303 call 0x405640
006e1308 test al, al
006e130a je 0x6e131b
006e130c push 0
006e130e push 0xb4a2a8
006e1313 lea ecx, [edi + 0x40]
006e1316 call 0x4054f0
006e131b push 0xb4a2a8
006e1320 lea ecx, [edi + 0x40]
006e1323 call 0x405640
006e1328 test al, al
006e132a je 0x6e137a
006e132c push 0xb4a5ec
006e1331 lea ecx, [edi + 0x40]
006e1334 call 0x406350
006e1339 test eax, eax
006e133b je 0x6e137a
006e133d movaps xmm0, xmmword ptr [0xb6c610]
006e1344 lea ecx, [esp + 0x44]
006e1348 movups xmmword ptr [esp + 0x44], xmm0
006e134d push ecx
006e134e movaps xmm0, xmmword ptr [0xb6c5a0]
006e1355 lea ecx, [eax + 0x48]
006e1358 movups xmmword ptr [esp + 0x58], xmm0
006e135d mov dword ptr [esp + 0x68], 0
006e1365 mov dword ptr [esp + 0x6c], 0
006e136d mov dword ptr [esp + 0x70], 0
006e1375 call 0x4021a0
006e137a mov ecx, dword ptr [0xbfd65c]
006e1380 push -1
006e1382 push dword ptr [edi + 0x27c]
006e1388 call 0x70e0f0
006e138d cmp dword ptr [eax + 0x10], 0
006e1391 je 0x6e139a
006e1393 or dword ptr [eax + 0x44], 0x40000
006e139a mov al, 1
006e139c pop edi
006e139d pop esi
006e139e mov esp, ebp
006e13a0 pop ebp
006e13a1 ret 8
006e13a4 pop edi
006e13a5 xor al, al
006e13a7 pop esi
006e13a8 mov esp, ebp
006e13aa pop ebp
