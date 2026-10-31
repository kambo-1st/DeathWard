008d0aa0 push ebp
008d0aa1 mov ebp, esp
008d0aa3 push -1
008d0aa5 push 0x9ff845
008d0aaa mov eax, dword ptr fs:[0]
008d0ab0 push eax
008d0ab1 sub esp, 0x54
008d0ab4 mov eax, dword ptr [0xbaa3b4]
008d0ab9 xor eax, ebp
008d0abb mov dword ptr [ebp - 0x10], eax
008d0abe push esi
008d0abf push edi
008d0ac0 push eax
008d0ac1 lea eax, [ebp - 0xc]
008d0ac4 mov dword ptr fs:[0], eax
008d0aca mov edi, ecx
008d0acc lea esi, [edi + 0x378]
008d0ad2 push 0xbc4bd0
008d0ad7 mov edx, esi
008d0ad9 lea ecx, [ebp - 0x20]
008d0adc call 0x412050
008d0ae1 add esp, 4
008d0ae4 mov ecx, dword ptr [eax]
008d0ae6 or ecx, dword ptr [eax + 4]
008d0ae9 jne 0x8d0af7
008d0aeb mov ecx, dword ptr [eax + 8]
008d0aee or ecx, dword ptr [eax + 0xc]
008d0af1 je 0x8d0d62
008d0af7 mov eax, dword ptr [edi + 0x30]
008d0afa cmp eax, 1
008d0afd je 0x8d0d62
008d0b03 cmp eax, 2
008d0b06 je 0x8d0d62
008d0b0c cmp eax, 3
008d0b0f je 0x8d0d62
008d0b15 cmp dword ptr [edi + 0x3a8], 0
008d0b1c jle 0x8d0d62
008d0b22 lea eax, [ebp - 0x20]
008d0b25 mov ecx, 0xbc4bd0
008d0b2a push eax
008d0b2b call 0x57f3a0
008d0b30 movss xmm1, dword ptr [edi + 0x430]
008d0b38 movss dword ptr [ebp - 0x58], xmm1
008d0b3d mov ecx, dword ptr [eax]
008d0b3f and dword ptr [esi], ecx
008d0b41 mov ecx, dword ptr [eax + 4]
008d0b44 and dword ptr [esi + 4], ecx
008d0b47 mov ecx, dword ptr [eax + 8]
008d0b4a and dword ptr [esi + 8], ecx
008d0b4d mov eax, dword ptr [eax + 0xc]
008d0b50 and dword ptr [esi + 0xc], eax
008d0b53 mov eax, dword ptr [0xbc4bd0]
008d0b58 or dword ptr [edi + 0x398], eax
008d0b5e mov eax, dword ptr [0xbc4bd4]
008d0b63 or dword ptr [edi + 0x39c], eax
008d0b69 mov eax, dword ptr [0xbc4bd8]
008d0b6e or dword ptr [edi + 0x3a0], eax
008d0b74 mov eax, dword ptr [0xbc4bdc]
008d0b79 or dword ptr [edi + 0x3a4], eax
008d0b7f mov eax, dword ptr [edi + 0x2c]
008d0b82 cmp eax, 0xb
008d0b85 je 0x8d0bb9
008d0b87 cmp eax, 0xe
008d0b8a je 0x8d0bb9
008d0b8c cmp eax, 6
008d0b8f je 0x8d0baa
008d0b91 cmp eax, 0xf
008d0b94 je 0x8d0baa
008d0b96 cmp eax, 0xd
008d0b99 jne 0x8d0bc5
008d0b9b mulss xmm1, dword ptr [0xb6a8f4]
008d0ba3 movss dword ptr [ebp - 0x58], xmm1
008d0ba8 jmp 0x8d0bc5
008d0baa mulss xmm1, dword ptr [0xb6a864]
008d0bb2 movss dword ptr [ebp - 0x58], xmm1
008d0bb7 jmp 0x8d0bc5
008d0bb9 movaps xmm0, xmm1
008d0bbc addss xmm0, xmm1
008d0bc0 movss dword ptr [ebp - 0x58], xmm0
008d0bc5 mov ecx, edi
008d0bc7 call 0x8c5940
008d0bcc push dword ptr [edi + 0x344]
008d0bd2 lea ecx, [edi + 0x294]
008d0bd8 test al, al
008d0bda push 0
008d0bdc push dword ptr [edi + 0x320]
008d0be2 mov edx, 0x7e
008d0be7 push 0xc02fec
008d0bec push ecx
008d0bed mov ecx, 0x47
008d0bf2 cmove ecx, edx
008d0bf5 push ecx
008d0bf6 mov ecx, dword ptr [0xbfd65c]
008d0bfc push 0x3e8
008d0c01 call 0x422e20
008d0c06 mov ecx, dword ptr [edi + 0x48c]
008d0c0c lea esi, [edi + 0x48c]
008d0c12 mov dword ptr [ebp - 0x60], eax
008d0c15 cmp ecx, eax
008d0c17 je 0x8d0c46
008d0c19 test ecx, ecx
008d0c1b je 0x8d0c32
008d0c1d lea eax, [ebp - 0x5c]
008d0c20 mov dword ptr [ebp - 0x5c], esi
008d0c23 push eax
008d0c24 add ecx, 0x324
008d0c2a call 0x4bc3c0
008d0c2f mov eax, dword ptr [ebp - 0x60]
008d0c32 mov dword ptr [esi], eax
008d0c34 mov ecx, eax
008d0c36 test eax, eax
008d0c38 je 0x8d0c46
008d0c3a push esi
008d0c3b call 0x4bae70
008d0c40 mov ecx, dword ptr [edi + 0x48c]
008d0c46 lea eax, [ecx + 0x318]
008d0c4c mov ecx, dword ptr [eax]
008d0c4e mov dword ptr [ebp - 0x5c], eax
008d0c51 test ecx, ecx
008d0c53 je 0x8d0c6a
008d0c55 mov dword ptr [ebp - 0x60], eax
008d0c58 add ecx, 0x324
008d0c5e lea eax, [ebp - 0x60]
008d0c61 push eax
008d0c62 call 0x4bc3c0
008d0c67 mov eax, dword ptr [ebp - 0x5c]
008d0c6a push eax
008d0c6b mov ecx, edi
008d0c6d mov dword ptr [eax], edi
008d0c6f call 0x4bae70
008d0c74 mov ecx, dword ptr [esi]
008d0c76 mov eax, dword ptr [edi + 0x2a4]
008d0c7c movss xmm1, dword ptr [ebp - 0x58]
008d0c81 movaps xmm0, xmm1
008d0c84 mov dword ptr [ecx + 0x2a4], eax
008d0c8a mov eax, dword ptr [edi + 0x2a8]
008d0c90 mov dword ptr [ecx + 0x2a8], eax
008d0c96 mov eax, dword ptr [esi]
008d0c98 mulss xmm0, dword ptr [0xbc7a28]
008d0ca0 push 1
008d0ca2 mulss xmm1, dword ptr [0xbc7a2c]
008d0caa push 0
008d0cac movss dword ptr [eax + 0xd8], xmm0
008d0cb4 push 0xff
008d0cb9 movss dword ptr [eax + 0xdc], xmm1
008d0cc1 lea eax, [edi + 0x1b0]
008d0cc7 mov ecx, dword ptr [esi]
008d0cc9 push -1
008d0ccb push eax
008d0ccc mov edx, dword ptr [ecx]
008d0cce call dword ptr [edx + 0x38]
008d0cd1 mov ecx, dword ptr [esi]
008d0cd3 movss xmm0, dword ptr [edi + 0x2e0]
008d0cdb push ecx
008d0cdc movss dword ptr [esp], xmm0
008d0ce1 mov eax, dword ptr [ecx]
008d0ce3 call dword ptr [eax + 0x3c]
008d0ce6 mov eax, dword ptr [esi]
008d0ce8 movups xmm0, xmmword ptr [edi + 0x378]
008d0cef movups xmmword ptr [eax + 0x370], xmm0
008d0cf6 mov eax, dword ptr [edi + 0x314]
008d0cfc test eax, eax
008d0cfe je 0x8d0d0f
008d0d00 cmp dword ptr [eax + 0x28], 7
008d0d04 jne 0x8d0d0f
008d0d06 mov eax, dword ptr [esi]
008d0d08 mov byte ptr [eax + 0x169], 0
008d0d0f mov ecx, dword ptr [esi]
008d0d11 mov eax, dword ptr [ecx]
008d0d13 call dword ptr [eax + 0xc]
008d0d16 mov eax, dword ptr [esi]
008d0d18 lea esi, [edi + 0x314]
008d0d1e mov ecx, dword ptr [esi]
008d0d20 mov dword ptr [ebp - 0x5c], eax
008d0d23 test ecx, ecx
008d0d25 je 0x8d0d3c
008d0d27 lea eax, [ebp - 0x60]
008d0d2a mov dword ptr [ebp - 0x60], esi
008d0d2d push eax
008d0d2e add ecx, 0x324
008d0d34 call 0x4bc3c0
008d0d39 mov eax, dword ptr [ebp - 0x5c]
008d0d3c mov dword ptr [esi], eax
008d0d3e test eax, eax
008d0d40 je 0x8d0d4a
008d0d42 push esi
008d0d43 mov ecx, eax
008d0d45 call 0x4bae70
008d0d4a mov dword ptr [edi + 0x490], 2
008d0d54 mov byte ptr [edi + 0x169], 0
008d0d5b mov byte ptr [edi + 0x434], 1
008d0d62 mov eax, dword ptr [edi + 0x48c]
008d0d68 test eax, eax
008d0d6a je 0x8d0d88
008d0d6c cmp dword ptr [eax + 0x3a0], 0
008d0d73 jne 0x8d0d88
008d0d75 cmp dword ptr [edi + 0x490], 2
008d0d7c jge 0x8d0d88
008d0d7e mov dword ptr [edi + 0x490], 2
008d0d88 mov eax, dword ptr [edi + 0x47c]
008d0d8e mov ecx, edi
008d0d90 test eax, eax
008d0d92 je 0x8d0da0
008d0d94 mov ecx, eax
008d0d96 mov eax, dword ptr [ecx + 0x47c]
008d0d9c test eax, eax
008d0d9e jne 0x8d0d94
008d0da0 lea esi, [ecx + 0x378]
008d0da6 push 0xbc46e0
008d0dab mov edx, esi
008d0dad lea ecx, [ebp - 0x20]
008d0db0 call 0x412050
008d0db5 add esp, 4
008d0db8 mov ecx, dword ptr [eax]
008d0dba or ecx, dword ptr [eax + 4]
008d0dbd jne 0x8d0e81
008d0dc3 mov ecx, dword ptr [eax + 8]
008d0dc6 or ecx, dword ptr [eax + 0xc]
008d0dc9 jne 0x8d0e81
008d0dcf push 0xbc4940
008d0dd4 mov edx, esi
008d0dd6 lea ecx, [ebp - 0x20]
008d0dd9 call 0x412050
008d0dde add esp, 4
008d0de1 mov ecx, dword ptr [eax]
008d0de3 or ecx, dword ptr [eax + 4]
008d0de6 jne 0x8d0df4
008d0de8 mov ecx, dword ptr [eax + 8]
008d0deb or ecx, dword ptr [eax + 0xc]
008d0dee je 0x8d0f68
008d0df4 mov eax, dword ptr [0xbfd65c]
008d0df9 lea ecx, [ebp - 0x3c]
008d0dfc mov eax, dword ptr [eax + 0x1a30dc]
008d0e02 sub eax, dword ptr [edi + 0x280]
008d0e08 cdq 
008d0e09 sub eax, edx
008d0e0b mov edx, eax
008d0e0d sar edx, 1
008d0e0f call 0x402120
008d0e14 and edx, 0x80000007
008d0e1a jns 0x8d0e21
008d0e1c dec edx
008d0e1d or edx, 0xfffffff8
008d0e20 inc edx
008d0e21 cmp edx, 7
008d0e24 ja 0x8d0f16
008d0e2a jmp dword ptr [edx*4 + 0x8d1308]
008d0e31 movaps xmm0, xmmword ptr [0xb6c7c0]
008d0e38 movups xmmword ptr [ebp - 0x2c], xmm0
008d0e3c jmp 0x8d0f16
008d0e41 movaps xmm0, xmmword ptr [0xb6c810]
008d0e48 movups xmmword ptr [ebp - 0x2c], xmm0
008d0e4c jmp 0x8d0f16
008d0e51 movaps xmm0, xmmword ptr [0xb6c800]
008d0e58 movups xmmword ptr [ebp - 0x2c], xmm0
008d0e5c jmp 0x8d0f16
008d0e61 movaps xmm0, xmmword ptr [0xb6c7e0]
008d0e68 movups xmmword ptr [ebp - 0x2c], xmm0
008d0e6c jmp 0x8d0f16
008d0e71 movaps xmm0, xmmword ptr [0xb6c7d0]
008d0e78 movups xmmword ptr [ebp - 0x2c], xmm0
008d0e7c jmp 0x8d0f16
008d0e81 mov eax, dword ptr [0xbfd65c]
008d0e86 push ecx
008d0e87 mov ecx, 0x1e
008d0e8c movss xmm3, dword ptr [0xb6a614]
008d0e94 movss xmm2, dword ptr [0xb6a5a4]
008d0e9c mov eax, dword ptr [eax + 0x1a30dc]
008d0ea2 cdq 
008d0ea3 idiv ecx
008d0ea5 lea ecx, [ebp - 0x20]
008d0ea8 mov dword ptr [esp], 0x3f800000
008d0eaf movd xmm1, edx
008d0eb3 cvtdq2ps xmm1, xmm1
008d0eb6 mulss xmm1, dword ptr [0xb6ac40]
008d0ebe divss xmm1, dword ptr [0xb6aa0c]
008d0ec6 call 0x65c840
008d0ecb movss xmm0, dword ptr [0xb6a8cc]
008d0ed3 add esp, 4
008d0ed6 movss xmm3, dword ptr [ebp - 0x20]
008d0edb movss xmm2, dword ptr [ebp - 0x1c]
008d0ee0 movss xmm1, dword ptr [ebp - 0x18]
008d0ee5 mulss xmm3, xmm0
008d0ee9 mulss xmm2, xmm0
008d0eed mulss xmm1, xmm0
008d0ef1 movaps xmm0, xmmword ptr [0xb6c610]
008d0ef8 movups xmmword ptr [ebp - 0x3c], xmm0
008d0efc movaps xmm0, xmmword ptr [0xb6afe0]
008d0f03 movss dword ptr [ebp - 0x2c], xmm3
008d0f08 movss dword ptr [ebp - 0x28], xmm2
008d0f0d movss dword ptr [ebp - 0x24], xmm1
008d0f12 movups xmmword ptr [ebp - 0x20], xmm0
008d0f16 mov eax, dword ptr [edi]
008d0f18 lea ecx, [ebp - 0x3c]
008d0f1b push 1
008d0f1d push 0
008d0f1f push 0xff
008d0f24 push -1
008d0f26 push ecx
008d0f27 mov ecx, edi
008d0f29 call dword ptr [eax + 0x38]
008d0f2c mov ecx, dword ptr [edi + 0x318]
008d0f32 test ecx, ecx
008d0f34 je 0x8d0f4a
008d0f36 mov eax, dword ptr [ecx]
008d0f38 lea edx, [ebp - 0x3c]
008d0f3b push 1
008d0f3d push 0
008d0f3f push 0xff
008d0f44 push -1
008d0f46 push edx
008d0f47 call dword ptr [eax + 0x38]
008d0f4a mov ecx, dword ptr [edi + 0x48c]
008d0f50 test ecx, ecx
008d0f52 je 0x8d0f68
008d0f54 mov eax, dword ptr [ecx]
008d0f56 lea edx, [ebp - 0x3c]
008d0f59 push 1
008d0f5b push 0
008d0f5d push 0xff
008d0f62 push -1
008d0f64 push edx
008d0f65 call dword ptr [eax + 0x38]
008d0f68 mov eax, dword ptr [edi + 0x490]
008d0f6e test eax, eax
008d0f70 jle 0x8d0f88
008d0f72 dec eax
008d0f73 mov dword ptr [edi + 0x490], eax
008d0f79 test eax, eax
008d0f7b jg 0x8d12eb
008d0f81 mov byte ptr [edi + 0x169], 1
008d0f88 cmp byte ptr [edi + 0x3ac], 0
008d0f8f je 0x8d12bc
008d0f95 mov eax, dword ptr [edi + 0x34]
008d0f98 cmp eax, 0x27
008d0f9b jne 0x8d0fc7
008d0f9d mov eax, dword ptr [edi + 0x314]
008d0fa3 test eax, eax
008d0fa5 je 0x8d12ac
008d0fab cmp dword ptr [eax + 0x34], 0x109
008d0fb2 je 0x8d0ffc
008d0fb4 mov ecx, edi
008d0fb6 call 0x8c86d0
008d0fbb mov byte ptr [edi + 0x3ac], 0
008d0fc2 jmp 0x8d12eb
008d0fc7 cmp eax, 0x44
008d0fca jne 0x8d114d
008d0fd0 mov eax, dword ptr [edi + 0x314]
008d0fd6 test eax, eax
008d0fd8 je 0x8d12ac
008d0fde cmp dword ptr [eax + 0x28], 0x44
008d0fe2 jne 0x8d12ac
008d0fe8 cmp dword ptr [eax + 0x2c], 1
008d0fec jne 0x8d12ac
008d0ff2 cmp dword ptr [eax + 0x30], 1
008d0ff6 jne 0x8d12ac
008d0ffc mov dword ptr [ebp - 0x28], 0
008d1003 push 0x20
008d1005 mov dword ptr [ebp - 0x18], 0
008d100c mov dword ptr [ebp - 0x14], 0xf
008d1013 mov byte ptr [ebp - 0x28], 0
008d1017 call 0x407de0
008d101c movups xmm0, xmmword ptr [0xb59300]
008d1023 mov edx, eax
008d1025 mov dword ptr [ebp - 0x18], 0x1d
008d102c mov dword ptr [ebp - 0x14], 0x1f
008d1033 movups xmmword ptr [edx], xmm0
008d1036 movq xmm0, qword ptr [0xb59310]
008d103e movq qword ptr [edx + 0x10], xmm0
008d1043 mov ecx, dword ptr [0xb59318]
008d1049 mov dword ptr [edx + 0x18], ecx
008d104c mov al, byte ptr [0xb5931c]
008d1051 mov byte ptr [edx + 0x1c], al
008d1054 mov byte ptr [edx + 0x1d], 0
008d1058 mov dword ptr [ebp - 0x28], edx
008d105b push 1
008d105d lea eax, [ebp - 0x28]
008d1060 mov dword ptr [ebp - 4], 0
008d1067 push eax
008d1068 lea ecx, [edi + 0x3c]
008d106b call 0x407160
008d1070 mov dword ptr [ebp - 4], 0xffffffff
008d1077 mov edx, dword ptr [ebp - 0x14]
008d107a cmp edx, 0x10
008d107d jb 0x8d10ad
008d107f mov ecx, dword ptr [ebp - 0x28]
008d1082 inc edx
008d1083 mov eax, ecx
008d1085 cmp edx, 0x1000
008d108b jb 0x8d10a3
008d108d mov ecx, dword ptr [ecx - 4]
008d1090 add edx, 0x23
008d1093 sub eax, ecx
008d1095 add eax, -4
008d1098 cmp eax, 0x1f
008d109b jbe 0x8d10a3
008d109d call dword ptr [0xa065ac]
008d10a3 push edx
008d10a4 push ecx
008d10a5 call 0x9eb08e
008d10aa add esp, 8
008d10ad cmp dword ptr [edi + 0x68], 0x10
008d10b1 lea ecx, [edi + 0x54]
008d10b4 mov dword ptr [ebp - 0x58], ecx
008d10b7 jb 0x8d10be
008d10b9 mov ecx, dword ptr [ecx]
008d10bb mov dword ptr [ebp - 0x58], ecx
008d10be mov esi, dword ptr [edi + 0x70]
008d10c1 test esi, esi
008d10c3 je 0x8d1119
008d10c5 cmp dword ptr [esi + 0x14], 0x10
008d10c9 mov eax, esi
008d10cb jb 0x8d10d0
008d10cd mov eax, dword ptr [esi]
008d10cf nop 
008d10d0 mov dl, byte ptr [eax]
008d10d2 cmp dl, byte ptr [ecx]
008d10d4 jne 0x8d10f0
008d10d6 test dl, dl
008d10d8 je 0x8d10ec
008d10da mov dl, byte ptr [eax + 1]
008d10dd cmp dl, byte ptr [ecx + 1]
008d10e0 jne 0x8d10f0
008d10e2 add eax, 2
008d10e5 add ecx, 2
008d10e8 test dl, dl
008d10ea jne 0x8d10d0
008d10ec xor eax, eax
008d10ee jmp 0x8d10f5
008d10f0 sbb eax, eax
008d10f2 or eax, 1
008d10f5 test eax, eax
008d10f7 jne 0x8d1116
008d10f9 cmp byte ptr [esi + 0x34], al
008d10fc je 0x8d12ac
008d1102 cmp byte ptr [edi + 0x80], al
008d1108 lea esi, [edi + 0x3c]
008d110b jne 0x8d12ac
008d1111 mov ecx, dword ptr [ebp - 0x58]
008d1114 jmp 0x8d111c
008d1116 mov ecx, dword ptr [ebp - 0x58]
008d1119 lea esi, [edi + 0x3c]
008d111c push 1
008d111e push ecx
008d111f mov ecx, esi
008d1121 call 0x405740
008d1126 test al, al
008d1128 je 0x8d12ac
008d112e lea ecx, [esi + 0x30]
008d1131 call 0x405330
008d1136 mov ecx, edi
008d1138 mov byte ptr [esi + 0x44], 1
008d113c call 0x8c86d0
008d1141 mov byte ptr [edi + 0x3ac], 0
008d1148 jmp 0x8d12eb
008d114d cmp eax, 0x3b6
008d1152 jne 0x8d12ac
008d1158 cmp dword ptr [edi + 0x2c], 1
008d115c jne 0x8d12ac
008d1162 mov dword ptr [ebp - 0x54], 0
008d1169 push 0x20
008d116b mov dword ptr [ebp - 0x44], 0
008d1172 mov dword ptr [ebp - 0x40], 0xf
008d1179 mov byte ptr [ebp - 0x54], 0
008d117d call 0x407de0
008d1182 movups xmm0, xmmword ptr [0xb592e0]
008d1189 mov edx, eax
008d118b mov dword ptr [ebp - 0x44], 0x1d
008d1192 mov dword ptr [ebp - 0x40], 0x1f
008d1199 movups xmmword ptr [edx], xmm0
008d119c movq xmm0, qword ptr [0xb592f0]
008d11a4 movq qword ptr [edx + 0x10], xmm0
008d11a9 mov ecx, dword ptr [0xb592f8]
008d11af mov dword ptr [edx + 0x18], ecx
008d11b2 mov al, byte ptr [0xb592fc]
008d11b7 mov byte ptr [edx + 0x1c], al
008d11ba mov byte ptr [edx + 0x1d], 0
008d11be mov dword ptr [ebp - 0x54], edx
008d11c1 push 1
008d11c3 lea eax, [ebp - 0x54]
008d11c6 mov dword ptr [ebp - 4], 1
008d11cd push eax
008d11ce lea ecx, [edi + 0x3c]
008d11d1 call 0x407160
008d11d6 mov dword ptr [ebp - 4], 0xffffffff
008d11dd mov edx, dword ptr [ebp - 0x40]
008d11e0 cmp edx, 0x10
008d11e3 jb 0x8d1213
008d11e5 mov ecx, dword ptr [ebp - 0x54]
008d11e8 inc edx
008d11e9 mov eax, ecx
008d11eb cmp edx, 0x1000
008d11f1 jb 0x8d1209
008d11f3 mov ecx, dword ptr [ecx - 4]
008d11f6 add edx, 0x23
008d11f9 sub eax, ecx
008d11fb add eax, -4
008d11fe cmp eax, 0x1f
008d1201 jbe 0x8d1209
008d1203 call dword ptr [0xa065ac]
008d1209 push edx
008d120a push ecx
008d120b call 0x9eb08e
008d1210 add esp, 8
008d1213 cmp dword ptr [edi + 0x68], 0x10
008d1217 lea ecx, [edi + 0x54]
008d121a mov dword ptr [ebp - 0x44], 0
008d1221 mov dword ptr [ebp - 0x40], 0xf
008d1228 mov byte ptr [ebp - 0x54], 0
008d122c mov dword ptr [ebp - 0x58], ecx
008d122f jb 0x8d1236
008d1231 mov ecx, dword ptr [ecx]
008d1233 mov dword ptr [ebp - 0x58], ecx
008d1236 mov esi, dword ptr [edi + 0x70]
008d1239 test esi, esi
008d123b je 0x8d1288
008d123d cmp dword ptr [esi + 0x14], 0x10
008d1241 mov eax, esi
008d1243 jb 0x8d1247
008d1245 mov eax, dword ptr [esi]
008d1247 mov dl, byte ptr [eax]
008d1249 cmp dl, byte ptr [ecx]
008d124b jne 0x8d1267
008d124d test dl, dl
008d124f je 0x8d1263
008d1251 mov dl, byte ptr [eax + 1]
008d1254 cmp dl, byte ptr [ecx + 1]
008d1257 jne 0x8d1267
008d1259 add eax, 2
008d125c add ecx, 2
008d125f test dl, dl
008d1261 jne 0x8d1247
008d1263 xor eax, eax
008d1265 jmp 0x8d126c
008d1267 sbb eax, eax
008d1269 or eax, 1
008d126c test eax, eax
008d126e jne 0x8d1285
008d1270 cmp byte ptr [esi + 0x34], al
008d1273 je 0x8d12a5
008d1275 cmp byte ptr [edi + 0x80], al
008d127b lea esi, [edi + 0x3c]
008d127e jne 0x8d12a5
008d1280 mov ecx, dword ptr [ebp - 0x58]
008d1283 jmp 0x8d128b
008d1285 mov ecx, dword ptr [ebp - 0x58]
008d1288 lea esi, [edi + 0x3c]
008d128b push 1
008d128d push ecx
008d128e mov ecx, esi
008d1290 call 0x405740
008d1295 test al, al
008d1297 je 0x8d12a5
008d1299 lea ecx, [esi + 0x30]
008d129c call 0x405330
008d12a1 mov byte ptr [esi + 0x44], 1
008d12a5 or dword ptr [edi + 0x14c], 0x20
008d12ac mov ecx, edi
008d12ae call 0x8c86d0
008d12b3 mov byte ptr [edi + 0x3ac], 0
008d12ba jmp 0x8d12eb
008d12bc mov eax, dword ptr [edi + 0x30]
008d12bf cmp eax, 1
008d12c2 je 0x8d12d7
008d12c4 cmp eax, 2
008d12c7 je 0x8d12d7
008d12c9 cmp eax, 3
008d12cc je 0x8d12d7
008d12ce mov ecx, edi
008d12d0 call 0x8cc300
008d12d5 jmp 0x8d12de
008d12d7 mov ecx, edi
008d12d9 call 0x8d4160
008d12de mov ecx, edi
008d12e0 call 0x6860a0
008d12e5 push edi
008d12e6 call 0x7fdd50
008d12eb mov ecx, dword ptr [ebp - 0xc]
008d12ee mov dword ptr fs:[0], ecx
008d12f5 pop ecx
008d12f6 pop edi
008d12f7 pop esi
008d12f8 mov ecx, dword ptr [ebp - 0x10]
008d12fb xor ecx, ebp
008d12fd call 0x9eacd7
008d1302 mov esp, ebp
008d1304 pop ebp
008d1305 ret 
008d1306 nop 
008d1308 xor dword ptr [esi], ecx
008d130a lea eax, [eax]
008d130c jno 0x8d131c
008d130e lea eax, [eax]
008d1310 popal 
008d1311 push cs
008d1312 lea eax, [eax]
008d1314 push ecx
008d1315 push cs
008d1316 lea eax, [eax]
008d1318 inc ecx
008d1319 push cs
008d131a lea eax, [eax]
008d131c push ecx
008d131d push cs
008d131e lea eax, [eax]
008d1320 popal 
008d1321 push cs
008d1322 lea eax, [eax]
008d1324 jno 0x8d1334
008d1326 lea eax, [eax]
008d1328 int3 
008d1329 int3 
008d132a int3 
008d132b int3 
008d132c int3 
008d132d int3 
008d132e int3 
008d132f int3 
