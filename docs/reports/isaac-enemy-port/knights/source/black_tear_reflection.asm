006a3a39 cmp ecx, 2
006a3a3c jne 0x6a3da4
006a3a42 movups xmm0, xmmword ptr [esi + 0x378]
006a3a49 push 0xbc4ce0
006a3a4e mov edx, 0xbc4ca0
006a3a53 lea ecx, [ebp - 0x130]
006a3a59 movups xmmword ptr [ebp - 0x20], xmm0
006a3a5d call 0x427220
006a3a62 push eax
006a3a63 lea edx, [ebp - 0x20]
006a3a66 lea ecx, [ebp - 0x140]
006a3a6c call 0x412050
006a3a71 add esp, 8
006a3a74 mov ecx, dword ptr [eax]
006a3a76 or ecx, dword ptr [eax + 4]
006a3a79 jne 0x6a3da4
006a3a7f mov ecx, dword ptr [eax + 8]
006a3a82 or ecx, dword ptr [eax + 0xc]
006a3a85 jne 0x6a3da4
006a3a8b cmp dword ptr [edi + 0x28], 0x29
006a3a8f jne 0x6a3da4
006a3a95 cmp dword ptr [edi + 0x2c], 4
006a3a99 jne 0x6a3da4
006a3a9f movss xmm0, dword ptr [esi + 0x2b8]
006a3aa7 mov ecx, edi
006a3aa9 movss dword ptr [ebp - 0x100], xmm0
006a3ab1 movss xmm0, dword ptr [esi + 0x2bc]
006a3ab9 movss dword ptr [ebp - 0xfc], xmm0
006a3ac1 push dword ptr [ebp - 0xfc]
006a3ac7 push dword ptr [ebp - 0x100]
006a3acd call 0x6aa830
006a3ad2 test al, al
006a3ad4 jne 0x6a3da4
006a3ada call 0x6c3d90
006a3adf movss xmm2, dword ptr [0xb6a53c]
006a3ae7 push ecx
006a3ae8 movd xmm0, eax
006a3aec cvtdq2pd xmm0, xmm0
006a3af0 shr eax, 0x1f
006a3af3 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
006a3afc cvtpd2ps xmm0, xmm0
006a3b00 mulss xmm0, dword ptr [0xb6a19c]
006a3b08 mulss xmm0, dword ptr [0xb6a2ac]
006a3b10 addss xmm0, dword ptr [0xb6a588]
006a3b18 movss dword ptr [esp], xmm0
006a3b1d push 0
006a3b1f push 2
006a3b21 push 0xab
006a3b26 call 0x68d750
006a3b2b cmp dword ptr [edi + 0xaf0], 0
006a3b32 jg 0x6a3da4
006a3b38 xorps xmm0, xmm0
006a3b3b lea eax, [ebp - 0x28]
006a3b3e movss dword ptr [ebp - 0xf0], xmm0
006a3b46 lea ecx, [edi + 0x6c]
006a3b49 movss xmm0, dword ptr [0xb6a614]
006a3b51 push eax
006a3b52 movss dword ptr [ebp - 0xf8], xmm0
006a3b5a call 0x444be0
006a3b5f mov dword ptr [ebp - 4], 0
006a3b66 lea ecx, [ebp - 0x28]
006a3b69 cmp dword ptr [ebp - 0x14], 0x10
006a3b6d mov edx, dword ptr [ebp - 0x18]
006a3b70 cmovae ecx, dword ptr [ebp - 0x28]
006a3b74 push 2
006a3b76 push 0xb406e4
006a3b7b call 0x408190
006a3b80 add esp, 8
006a3b83 test al, al
006a3b85 je 0x6a3b9c
006a3b87 xorps xmm0, xmm0
006a3b8a movss dword ptr [ebp - 0xf0], xmm0
006a3b92 movss xmm0, dword ptr [0xb6ae44]
006a3b9a jmp 0x6a3be3
006a3b9c cmp dword ptr [ebp - 0x14], 0x10
006a3ba0 lea ecx, [ebp - 0x28]
006a3ba3 mov edx, dword ptr [ebp - 0x18]
006a3ba6 cmovae ecx, dword ptr [ebp - 0x28]
006a3baa push 4
006a3bac push 0xb42f28
006a3bb1 call 0x408190
006a3bb6 add esp, 8
006a3bb9 test al, al
006a3bbb je 0x6a3beb
006a3bbd cmp byte ptr [edi + 0x13c], 0
006a3bc4 je 0x6a3bd0
006a3bc6 movss xmm0, dword ptr [0xb6ae44]
006a3bce jmp 0x6a3bd8
006a3bd0 movss xmm0, dword ptr [0xb6a614]
006a3bd8 movss dword ptr [ebp - 0xf0], xmm0
006a3be0 xorps xmm0, xmm0
006a3be3 movss dword ptr [ebp - 0xf8], xmm0
006a3beb mov eax, dword ptr [esi + 0x2b8]
006a3bf1 mov ecx, dword ptr [esi + 0x2bc]
006a3bf7 mov dword ptr [ebp - 0x100], eax
006a3bfd lea eax, [ebp - 0x108]
006a3c03 mov dword ptr [ebp - 0xfc], ecx
006a3c09 lea ecx, [ebp - 0x100]
006a3c0f push eax
006a3c10 call 0x962560
006a3c15 movss xmm5, dword ptr [ebp - 0xf8]
006a3c1d movss xmm4, dword ptr [ebp - 0xf0]
006a3c25 movaps xmm1, xmm5
006a3c28 movaps xmm0, xmm4
006a3c2b mulss xmm1, dword ptr [eax + 4]
006a3c30 mulss xmm0, dword ptr [eax]
006a3c34 addss xmm1, xmm0
006a3c38 movss xmm0, dword ptr [0xb6a3b0]
006a3c40 andps xmm1, xmmword ptr [0xb6c980]
006a3c47 comiss xmm0, xmm1
006a3c4a jbe 0x6a3c97
006a3c4c movss xmm0, dword ptr [esi + 0x294]
006a3c54 lea eax, [ebp - 0x108]
006a3c5a movss xmm1, dword ptr [esi + 0x298]
006a3c62 lea ecx, [ebp - 0x100]
006a3c68 subss xmm0, dword ptr [edi + 0x294]
006a3c70 subss xmm1, dword ptr [edi + 0x298]
006a3c78 push eax
006a3c79 movss dword ptr [ebp - 0x100], xmm0
006a3c81 movss dword ptr [ebp - 0xfc], xmm1
006a3c89 call 0x962560
006a3c8e movss xmm4, dword ptr [eax]
006a3c92 movss xmm5, dword ptr [eax + 4]
006a3c97 lea ecx, [ebp - 0xe4]
006a3c9d call 0x430d70
006a3ca2 movss xmm2, dword ptr [esi + 0x370]
006a3caa mov ecx, 1
006a3caf movss xmm1, dword ptr [0xb6a274]
006a3cb7 mov eax, 0xb46a30
006a3cbc nop dword ptr [eax]
006a3cc0 movss xmm0, dword ptr [eax]
006a3cc4 addss xmm0, xmm1
006a3cc8 comiss xmm2, xmm0
006a3ccb jbe 0x6a3cd8
006a3ccd add eax, 4
006a3cd0 inc ecx
006a3cd1 cmp eax, 0xb46a60
006a3cd6 jl 0x6a3cc0
006a3cd8 mov eax, 0xd
006a3cdd movss xmm3, dword ptr [esi + 0x2b8]
006a3ce5 cmp ecx, eax
006a3ce7 movss xmm2, dword ptr [esi + 0x2bc]
006a3cef movaps xmm0, xmm5
006a3cf2 cmovl eax, ecx
006a3cf5 mulss xmm0, xmm2
006a3cf9 mov ecx, edi
006a3cfb movd xmm1, eax
006a3cff lea eax, [ebp - 0xe4]
006a3d05 cvtdq2ps xmm1, xmm1
006a3d08 push eax
006a3d09 push 0
006a3d0b lea eax, [ebp - 0x100]
006a3d11 push eax
006a3d12 lea eax, [edi + 0x294]
006a3d18 subss xmm1, dword ptr [0xb6a864]
006a3d20 push eax
006a3d21 divss xmm1, dword ptr [0xb6a864]
006a3d29 movss dword ptr [ebp - 0xd0], xmm1
006a3d31 movaps xmm1, xmm4
006a3d34 mulss xmm1, xmm3
006a3d38 addss xmm1, xmm0
006a3d3c addss xmm1, xmm1
006a3d40 mulss xmm4, xmm1
006a3d44 mulss xmm5, xmm1
006a3d48 subss xmm3, xmm4
006a3d4c subss xmm2, xmm5
006a3d50 movss dword ptr [ebp - 0x100], xmm3
006a3d58 movss dword ptr [ebp - 0xfc], xmm2
006a3d60 call 0x6a1a20
006a3d65 mov dword ptr [ebp - 4], 0xffffffff
006a3d6c mov eax, dword ptr [ebp - 0x14]
006a3d6f cmp eax, 0x10
006a3d72 jb 0x6a3da4
006a3d74 mov ecx, dword ptr [ebp - 0x28]
006a3d77 lea edx, [eax + 1]
006a3d7a mov eax, ecx
006a3d7c cmp edx, 0x1000
006a3d82 jb 0x6a3d9a
006a3d84 mov ecx, dword ptr [ecx - 4]
006a3d87 add edx, 0x23
006a3d8a sub eax, ecx
006a3d8c add eax, -4
006a3d8f cmp eax, 0x1f
006a3d92 jbe 0x6a3d9a
006a3d94 call dword ptr [0xa065ac]
006a3d9a push edx
006a3d9b push ecx
006a3d9c call 0x9eb08e
006a3da1 add esp, 8
