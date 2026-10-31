; Installed Repentance 1.7.9b; bounded evidence, names are interpretations.
004a79ff mov eax, dword ptr [edi + 8]
004a7a02 cmp eax, dword ptr [edi + 0xc]
004a7a05 je 0x4a7a76
004a7a07 nop word ptr [eax + eax]
004a7a10 mov ecx, dword ptr [eax + 0xc]
004a7a13 mov edx, dword ptr [eax + 8]
004a7a16 mov dword ptr [ebp - 0x12c], ecx
004a7a1c mov ecx, edx
004a7a1e and ecx, 4
004a7a21 or ecx, 0
004a7a24 je 0x4a7a32
004a7a26 cmp dword ptr [eax + 0x18], 1
004a7a2a je 0x4a7a32
004a7a2c cmp dword ptr [eax + 0x10], 1
004a7a30 jne 0x4a7a5a
004a7a32 and edx, 8
004a7a35 or edx, 0
004a7a38 je 0x4a7a42
004a7a3a mov ecx, dword ptr [eax + 0x10]
004a7a3d cmp ecx, dword ptr [edi + 0x28]
004a7a40 je 0x4a7a5a
004a7a42 cmp dword ptr [eax + 0x10], 0x3e8
004a7a49 jne 0x4a7a6e
004a7a4b cmp dword ptr [eax + 0x14], 0x93
004a7a52 jne 0x4a7a6e
004a7a54 cmp dword ptr [eax + 0x18], 1
004a7a58 je 0x4a7a6e
004a7a5a movss xmm0, dword ptr [edi + 0x14]
004a7a5f subss xmm0, dword ptr [eax]
004a7a63 movss dword ptr [edi + 0x14], xmm0
004a7a68 mov dword ptr [eax], 0
004a7a6e add eax, 0x38
004a7a71 cmp eax, dword ptr [edi + 0xc]
004a7a74 jne 0x4a7a10
004a7a76 comiss xmm1, dword ptr [edi + 0x14]
004a7a7a jbe 0x4a7a83
004a7a7c mov dword ptr [edi + 0x14], 0
004a7a83 movaps xmm2, xmm1
004a7a86 mov ecx, edi
004a7a88 movss xmm1, dword ptr [0xb6a864]
004a7a90 call 0x6847e0
004a7a95 test eax, eax
004a7a97 je 0x4a7ae1
004a7a99 mov al, byte ptr [edi + 0xaf0]
004a7a9f test al, al
004a7aa1 je 0x4a7aab
004a7aa3 dec al
004a7aa5 mov byte ptr [edi + 0xaf0], al
004a7aab mov al, byte ptr [edi + 0xaf1]
004a7ab1 test al, al
004a7ab3 je 0x4a7abd
004a7ab5 dec al
004a7ab7 mov byte ptr [edi + 0xaf1], al
004a7abd mov al, byte ptr [edi + 0xaf2]
004a7ac3 test al, al
004a7ac5 je 0x4a7acf
004a7ac7 dec al
004a7ac9 mov byte ptr [edi + 0xaf2], al
004a7acf mov al, byte ptr [edi + 0xaf3]
004a7ad5 test al, al
004a7ad7 je 0x4a7ae1
004a7ad9 dec al
004a7adb mov byte ptr [edi + 0xaf3], al
004a7ae1 cmp byte ptr [edi + 0x16b], 0
004a7ae8 je 0x4a7f95
004a7aee cmp dword ptr [edi + 0x2c], 1
004a7af2 jne 0x4a7c86
004a7af8 call 0x6c3d90
004a7afd mov ecx, dword ptr [0xbfd65c]
004a7b03 lea esi, [edi + 0x294]
004a7b09 push eax
004a7b0a push 0
004a7b0c push 0
004a7b0e push 0xc02fec
004a7b13 push esi
004a7b14 push 1
004a7b16 push 0x3e8
004a7b1b call 0x422e20
004a7b20 call 0x6c3d90
004a7b25 mov ecx, dword ptr [0xbfd65c]
004a7b2b push eax
004a7b2c push 0
004a7b2e push 0
004a7b30 push 0xc02fec
004a7b35 push esi
004a7b36 push 0x12
004a7b38 push 0x3e8
004a7b3d call 0x422e20
004a7b42 mov ecx, eax
004a7b44 mov edx, dword ptr [eax]
004a7b46 call dword ptr [edx + 0xc]
004a7b49 mov ecx, dword ptr [0xbfd65c]
004a7b4f push 0
004a7b51 push 0
004a7b53 push 0x1004
004a7b58 sub esp, 0x10
004a7b5b mov eax, esp
004a7b5d push 0
004a7b5f push 0
004a7b61 sub esp, 8
004a7b64 mov dword ptr [eax], 0
004a7b6a mov dword ptr [eax + 4], 0
004a7b71 mov dword ptr [eax + 8], 0
004a7b78 mov dword ptr [eax + 0xc], 0
004a7b7f mov dword ptr [esp + 4], 0x42960000
004a7b87 mov dword ptr [esp], 0x42dc0000
004a7b8e push esi
004a7b8f call 0x6d1750
004a7b94 mov esi, 6
004a7b99 nop dword ptr [eax]
004a7ba0 call 0x6c3d90
004a7ba5 movd xmm0, eax
004a7ba9 cvtdq2pd xmm0, xmm0
004a7bad shr eax, 0x1f
004a7bb0 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
004a7bb9 cvtpd2ps xmm0, xmm0
004a7bbd mulss xmm0, dword ptr [0xb6a19c]
004a7bc5 mulss xmm0, dword ptr [0xb6a9ac]
004a7bcd addss xmm0, dword ptr [0xb6a8f4]
004a7bd5 movss dword ptr [ebp - 0xec], xmm0
004a7bdd call 0x6c3d90
004a7be2 movd xmm0, eax
004a7be6 cvtdq2pd xmm0, xmm0
004a7bea shr eax, 0x1f
004a7bed addsd xmm0, qword ptr [eax*8 + 0xb6c940]
004a7bf6 cvtpd2ps xmm0, xmm0
004a7bfa mulss xmm0, dword ptr [0xb6a19c]
004a7c02 mulss xmm0, dword ptr [0xb6a874]
004a7c0a addss xmm0, xmm0
004a7c0e movss dword ptr [ebp - 0xf0], xmm0
004a7c16 call 0x411fe0
004a7c1b mulss xmm0, dword ptr [ebp - 0xec]
004a7c23 movss dword ptr [ebp - 0x100], xmm0
004a7c2b movss xmm0, dword ptr [ebp - 0xf0]
004a7c33 call 0x412010
004a7c38 mulss xmm0, dword ptr [ebp - 0xec]
004a7c40 movss dword ptr [ebp - 0xfc], xmm0
004a7c48 call 0x6c3d90
004a7c4d mov ecx, dword ptr [0xbfd65c]
004a7c53 push eax
004a7c54 push 0
004a7c56 push edi
004a7c57 lea eax, [ebp - 0x100]
004a7c5d push eax
004a7c5e lea eax, [edi + 0x294]
004a7c64 push eax
004a7c65 push 3
004a7c67 push 4
004a7c69 call 0x422e20
004a7c6e mov dword ptr [eax + 0x180], 1
004a7c78 sub esi, 1
004a7c7b jne 0x4a7ba0
