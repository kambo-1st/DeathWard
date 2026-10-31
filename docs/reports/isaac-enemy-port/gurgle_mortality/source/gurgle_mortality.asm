00509002 cmp byte ptr [edi + 0x16b], 0
00509009 je 0x509081
0050900b movss xmm0, dword ptr [edi + 0x2d8]
00509013 comiss xmm0, dword ptr [0xb6aef8]
0050901a jbe 0x509998
00509020 call 0x6c3d90
00509025 xor edx, edx
00509027 mov ecx, 0x64
0050902c div ecx
0050902e cmp edx, 0xf
00509031 jae 0x509998
00509037 cmp dword ptr [edi + 0x2c], 0
0050903b jne 0x509998
00509041 push -1
00509043 push 0
00509045 push 0
00509047 push 0xee
0050904c mov ecx, edi
0050904e call 0x697c60
00509053 mov eax, dword ptr [edi + 0x2dc]
00509059 mov byte ptr [edi + 0x16b], 0
00509060 mov dword ptr [edi + 0x2d8], eax
00509066 call 0x6c3d90
0050906b xor edx, edx
0050906d mov ecx, 0x14
00509072 div ecx
00509074 add edx, ecx
00509076 mov dword ptr [edi + 0xaf0], edx
0050907c jmp 0x509998
00509081 movss xmm0, dword ptr [edi + 0x14]
00509086 xorps xmm2, xmm2
00509089 comiss xmm0, xmm2
0050908c jbe 0x5090ee
0050908e mov eax, dword ptr [edi + 8]
00509091 cmp eax, dword ptr [edi + 0xc]
00509094 je 0x5090ee
00509096 nop word ptr [eax + eax]
005090a0 mov ecx, dword ptr [eax + 0xc]
005090a3 mov edx, dword ptr [eax + 8]
005090a6 mov dword ptr [ebp - 0x12c], ecx
005090ac mov ecx, edx
005090ae and ecx, 6
005090b1 or ecx, 0
005090b4 je 0x5090e0
005090b6 mov ecx, dword ptr [eax + 0x30]
005090b9 shr ecx, 1
005090bb test cl, 1
005090be jne 0x5090e0
005090c0 cmp dword ptr [eax + 0x10], 1
005090c4 je 0x5090e0
005090c6 mov ecx, dword ptr [eax + 0x18]
005090c9 cmp ecx, 1
005090cc je 0x5090e0
005090ce cmp ecx, 3
005090d1 je 0x5090e0
005090d3 and edx, 0x1000
005090d9 or edx, 0
005090dc jne 0x5090e0
005090de mov dword ptr [eax], edx
005090e0 add eax, 0x38
005090e3 cmp eax, dword ptr [edi + 0xc]
005090e6 jne 0x5090a0
005090e8 mov ecx, dword ptr [edi + 0xab4]
