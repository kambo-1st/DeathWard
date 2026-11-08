006b48b0 push ebp
006b48b1 mov ebp, esp
006b48b3 push -1
006b48b5 push 0x9f4bfb
006b48ba mov eax, dword ptr fs:[0]
006b48c0 push eax
006b48c1 sub esp, 0x174
006b48c7 mov eax, dword ptr [0xbaa3b4]
006b48cc xor eax, ebp
006b48ce mov dword ptr [ebp - 0x10], eax
006b48d1 push esi
006b48d2 push edi
006b48d3 push eax
006b48d4 lea eax, [ebp - 0xc]
006b48d7 mov dword ptr fs:[0], eax
006b48dd mov esi, edx
006b48df mov dword ptr [ebp - 0x48], esi
006b48e2 mov edx, ecx
006b48e4 mov dword ptr [ebp - 0xa4], edx
006b48ea inc dword ptr [0xc038f8]
006b48f0 cmp dword ptr [esi], 0
006b48f3 movq xmm0, qword ptr [0xa08c44]
006b48fb mov eax, dword ptr [0xa08c4c]
006b4900 mov edi, dword ptr [ebp + 8]
006b4903 mov dword ptr [ebp - 0x6c], edx
006b4906 movq qword ptr [ebp - 0x68], xmm0
006b490b mov dword ptr [ebp - 0x9c], eax
006b4911 mov dword ptr [ebp - 0x60], eax
006b4914 jne 0x6b52b4
006b491a test edx, edx
006b491c jne 0x6b4934
006b491e push 0xb4d6c4
006b4923 push 3
006b4925 call 0x95e330
006b492a add esp, 8
006b492d int3 
006b492e mov edx, dword ptr [ebp - 0xa4]
006b4934 mov ecx, dword ptr [ebp - 0x68]
006b4937 mov eax, edx
006b4939 movq xmm0, qword ptr [0xa08af4]
006b4941 shr eax, cl
006b4943 mov ecx, dword ptr [ebp - 0x64]
006b4946 xor eax, edx
006b4948 mov edx, eax
006b494a movq qword ptr [ebp - 0x17c], xmm0
006b4952 shl edx, cl
006b4954 mov ecx, dword ptr [ebp - 0x9c]
006b495a xor edx, eax
006b495c mov eax, edx
006b495e shr eax, cl
006b4960 xor eax, edx
006b4962 mov dword ptr [ebp - 0x7c], eax
006b4965 mov dword ptr [ebp - 0x6c], eax
006b4968 mov eax, dword ptr [0xa08afc]
006b496d mov dword ptr [ebp - 0x9c], eax
006b4973 mov dword ptr [ebp - 0x174], eax
006b4979 jne 0x6b498b
006b497b push 0xb4d6c4
006b4980 push 3
006b4982 call 0x95e330
006b4987 add esp, 8
006b498a int3 
006b498b mov edx, dword ptr [ebp - 0x7c]
006b498e mov ecx, dword ptr [ebp - 0x17c]
006b4994 shr edx, cl
006b4996 xor edx, dword ptr [ebp - 0x7c]
006b4999 mov ecx, dword ptr [ebp - 0x178]
006b499f mov eax, edx
006b49a1 shl eax, cl
006b49a3 mov ecx, dword ptr [ebp - 0x9c]
006b49a9 xor eax, edx
006b49ab mov edx, eax
006b49ad shr edx, cl
006b49af xor ecx, ecx
006b49b1 xor edx, eax
006b49b3 mov dword ptr [ebp - 0x54], ecx
006b49b6 xor eax, eax
006b49b8 mov dword ptr [ebp - 0x58], eax
006b49bb mov dword ptr [ebp - 0x50], eax
006b49be movd xmm0, edx
006b49c2 cvtdq2pd xmm0, xmm0
006b49c6 shr edx, 0x1f
006b49c9 addsd xmm0, qword ptr [edx*8 + 0xb6c940]
006b49d2 mov edx, dword ptr [edi]
006b49d4 mov dword ptr [ebp - 0x98], edx
006b49da cvtpd2ps xmm0, xmm0
006b49de mulss xmm0, dword ptr [0xb6a198]
006b49e6 movss dword ptr [ebp - 0x9c], xmm0
006b49ee mov dword ptr [ebp - 4], ecx
006b49f1 cmp edx, 3
006b49f4 je 0x6b4a20
006b49f6 lea eax, [ebp - 0x128]
006b49fc mov dword ptr [ebp - 0x128], 0x14
006b4a06 push eax
006b4a07 push ecx
006b4a08 lea ecx, [ebp - 0x58]
006b4a0b mov dword ptr [ebp - 0x124], 0x14
006b4a15 call 0x48d900
006b4a1a mov ecx, dword ptr [ebp - 0x54]
006b4a1d mov eax, dword ptr [ebp - 0x58]
006b4a20 mov dword ptr [ebp - 0x44], ecx
006b4a23 xor edx, edx
006b4a25 sub dword ptr [ebp - 0x44], eax
006b4a28 sar dword ptr [ebp - 0x44], 3
006b4a2c cmp dword ptr [ebp - 0x44], edx
006b4a2f jbe 0x6b4a3d
006b4a31 cmp dword ptr [eax + edx*8], 0xa
006b4a35 je 0x6b4a6b
006b4a37 inc edx
006b4a38 cmp edx, dword ptr [ebp - 0x44]
006b4a3b jb 0x6b4a31
006b4a3d mov dword ptr [ebp - 0x130], 0xa
006b4a47 mov dword ptr [ebp - 0x12c], 0xf
006b4a51 cmp ecx, dword ptr [ebp - 0x50]
006b4a54 je 0x6b4a7c
006b4a56 mov dword ptr [ecx], 0xa
006b4a5c mov dword ptr [ecx + 4], 0xf
006b4a63 add ecx, 8
006b4a66 mov dword ptr [ebp - 0x54], ecx
006b4a69 jmp 0x6b4a92
006b4a6b add dword ptr [eax + edx*8 + 4], 0xf
006b4a70 jns 0x6b4a92
006b4a72 mov dword ptr [eax + edx*8 + 4], 0
006b4a7a jmp 0x6b4a92
006b4a7c lea eax, [ebp - 0x130]
006b4a82 push eax
006b4a83 push ecx
006b4a84 lea ecx, [ebp - 0x58]
006b4a87 call 0x48d900
006b4a8c mov ecx, dword ptr [ebp - 0x54]
006b4a8f mov eax, dword ptr [ebp - 0x58]
006b4a92 mov dword ptr [ebp - 0x44], ecx
006b4a95 xor edx, edx
006b4a97 sub dword ptr [ebp - 0x44], eax
006b4a9a sar dword ptr [ebp - 0x44], 3
006b4a9e cmp dword ptr [ebp - 0x44], edx
006b4aa1 jbe 0x6b4aaf
006b4aa3 cmp dword ptr [eax + edx*8], 0x1e
006b4aa7 je 0x6b4add
006b4aa9 inc edx
006b4aaa cmp edx, dword ptr [ebp - 0x44]
006b4aad jb 0x6b4aa3
006b4aaf mov dword ptr [ebp - 0x138], 0x1e
006b4ab9 mov dword ptr [ebp - 0x134], 0xf
006b4ac3 cmp ecx, dword ptr [ebp - 0x50]
006b4ac6 je 0x6b4aee
006b4ac8 mov dword ptr [ecx], 0x1e
006b4ace mov dword ptr [ecx + 4], 0xf
006b4ad5 add ecx, 8
006b4ad8 mov dword ptr [ebp - 0x54], ecx
006b4adb jmp 0x6b4b04
006b4add add dword ptr [eax + edx*8 + 4], 0xf
006b4ae2 jns 0x6b4b04
006b4ae4 mov dword ptr [eax + edx*8 + 4], 0
006b4aec jmp 0x6b4b04
006b4aee lea eax, [ebp - 0x138]
006b4af4 push eax
006b4af5 push ecx
006b4af6 lea ecx, [ebp - 0x58]
006b4af9 call 0x48d900
006b4afe mov ecx, dword ptr [ebp - 0x54]
006b4b01 mov eax, dword ptr [ebp - 0x58]
006b4b04 mov dword ptr [ebp - 0x44], ecx
006b4b07 xor edx, edx
006b4b09 sub dword ptr [ebp - 0x44], eax
006b4b0c sar dword ptr [ebp - 0x44], 3
006b4b10 cmp dword ptr [ebp - 0x44], edx
006b4b13 jbe 0x6b4b21
006b4b15 cmp dword ptr [eax + edx*8], 0x28
006b4b19 je 0x6b4b4f
006b4b1b inc edx
006b4b1c cmp edx, dword ptr [ebp - 0x44]
006b4b1f jb 0x6b4b15
006b4b21 mov dword ptr [ebp - 0x140], 0x28
006b4b2b mov dword ptr [ebp - 0x13c], 0xf
006b4b35 cmp ecx, dword ptr [ebp - 0x50]
006b4b38 je 0x6b4b60
006b4b3a mov dword ptr [ecx], 0x28
006b4b40 mov dword ptr [ecx + 4], 0xf
006b4b47 add ecx, 8
006b4b4a mov dword ptr [ebp - 0x54], ecx
006b4b4d jmp 0x6b4b76
006b4b4f add dword ptr [eax + edx*8 + 4], 0xf
006b4b54 jns 0x6b4b76
006b4b56 mov dword ptr [eax + edx*8 + 4], 0
006b4b5e jmp 0x6b4b76
006b4b60 lea eax, [ebp - 0x140]
006b4b66 push eax
006b4b67 push ecx
006b4b68 lea ecx, [ebp - 0x58]
006b4b6b call 0x48d900
006b4b70 mov ecx, dword ptr [ebp - 0x54]
006b4b73 mov eax, dword ptr [ebp - 0x58]
006b4b76 mov edx, dword ptr [edi]
006b4b78 cmp edx, 1
006b4b7b je 0x6b4c77
006b4b81 cmp edx, 3
006b4b84 je 0x6b4c77
006b4b8a cmp edx, 4
006b4b8d je 0x6b4c77
006b4b93 mov dword ptr [ebp - 0x44], ecx
006b4b96 xor edx, edx
006b4b98 sub dword ptr [ebp - 0x44], eax
006b4b9b sar dword ptr [ebp - 0x44], 3
006b4b9f cmp dword ptr [ebp - 0x44], edx
006b4ba2 jbe 0x6b4bb0
006b4ba4 cmp dword ptr [eax + edx*8], 0x32
006b4ba8 je 0x6b4bde
006b4baa inc edx
006b4bab cmp edx, dword ptr [ebp - 0x44]
006b4bae jb 0x6b4ba4
006b4bb0 mov dword ptr [ebp - 0x148], 0x32
006b4bba mov dword ptr [ebp - 0x144], 5
006b4bc4 cmp ecx, dword ptr [ebp - 0x50]
006b4bc7 je 0x6b4bef
006b4bc9 mov dword ptr [ecx], 0x32
006b4bcf mov dword ptr [ecx + 4], 5
006b4bd6 add ecx, 8
006b4bd9 mov dword ptr [ebp - 0x54], ecx
006b4bdc jmp 0x6b4c05
006b4bde add dword ptr [eax + edx*8 + 4], 5
006b4be3 jns 0x6b4c05
006b4be5 mov dword ptr [eax + edx*8 + 4], 0
006b4bed jmp 0x6b4c05
006b4bef lea eax, [ebp - 0x148]
006b4bf5 push eax
006b4bf6 push ecx
006b4bf7 lea ecx, [ebp - 0x58]
006b4bfa call 0x48d900
006b4bff mov ecx, dword ptr [ebp - 0x54]
006b4c02 mov eax, dword ptr [ebp - 0x58]
006b4c05 mov dword ptr [ebp - 0x44], ecx
006b4c08 xor edx, edx
006b4c0a sub dword ptr [ebp - 0x44], eax
006b4c0d sar dword ptr [ebp - 0x44], 3
006b4c11 cmp dword ptr [ebp - 0x44], edx
006b4c14 jbe 0x6b4c22
006b4c16 cmp dword ptr [eax + edx*8], 0x3c
006b4c1a je 0x6b4c50
006b4c1c inc edx
006b4c1d cmp edx, dword ptr [ebp - 0x44]
006b4c20 jb 0x6b4c16
006b4c22 mov dword ptr [ebp - 0xb0], 0x3c
006b4c2c mov dword ptr [ebp - 0xac], 5
006b4c36 cmp ecx, dword ptr [ebp - 0x50]
006b4c39 je 0x6b4c61
006b4c3b mov dword ptr [ecx], 0x3c
006b4c41 mov dword ptr [ecx + 4], 5
006b4c48 add ecx, 8
006b4c4b mov dword ptr [ebp - 0x54], ecx
006b4c4e jmp 0x6b4c77
006b4c50 add dword ptr [eax + edx*8 + 4], 5
006b4c55 jns 0x6b4c77
006b4c57 mov dword ptr [eax + edx*8 + 4], 0
006b4c5f jmp 0x6b4c77
006b4c61 lea eax, [ebp - 0xb0]
006b4c67 push eax
006b4c68 push ecx
006b4c69 lea ecx, [ebp - 0x58]
006b4c6c call 0x48d900
006b4c71 mov ecx, dword ptr [ebp - 0x54]
006b4c74 mov eax, dword ptr [ebp - 0x58]
006b4c77 mov dword ptr [ebp - 0x44], ecx
006b4c7a xor edx, edx
006b4c7c sub dword ptr [ebp - 0x44], eax
006b4c7f sar dword ptr [ebp - 0x44], 3
006b4c83 cmp dword ptr [ebp - 0x44], edx
006b4c86 jbe 0x6b4c94
006b4c88 cmp dword ptr [eax + edx*8], 0x46
006b4c8c je 0x6b4cc2
006b4c8e inc edx
006b4c8f cmp edx, dword ptr [ebp - 0x44]
006b4c92 jb 0x6b4c88
006b4c94 mov dword ptr [ebp - 0xb8], 0x46
006b4c9e mov dword ptr [ebp - 0xb4], 4
006b4ca8 cmp ecx, dword ptr [ebp - 0x50]
006b4cab je 0x6b4cd3
006b4cad mov dword ptr [ecx], 0x46
006b4cb3 mov dword ptr [ecx + 4], 4
006b4cba add ecx, 8
006b4cbd mov dword ptr [ebp - 0x54], ecx
006b4cc0 jmp 0x6b4ce9
006b4cc2 add dword ptr [eax + edx*8 + 4], 4
006b4cc7 jns 0x6b4ce9
006b4cc9 mov dword ptr [eax + edx*8 + 4], 0
006b4cd1 jmp 0x6b4ce9
006b4cd3 lea eax, [ebp - 0xb8]
006b4cd9 push eax
006b4cda push ecx
006b4cdb lea ecx, [ebp - 0x58]
006b4cde call 0x48d900
006b4ce3 mov ecx, dword ptr [ebp - 0x54]
006b4ce6 mov eax, dword ptr [ebp - 0x58]
006b4ce9 mov dword ptr [ebp - 0x44], ecx
006b4cec xor edx, edx
006b4cee sub dword ptr [ebp - 0x44], eax
006b4cf1 sar dword ptr [ebp - 0x44], 3
006b4cf5 cmp dword ptr [ebp - 0x44], edx
006b4cf8 jbe 0x6b4d0f
006b4cfa nop word ptr [eax + eax]
006b4d00 cmp dword ptr [eax + edx*8], 0x12c
006b4d07 je 0x6b4d3d
006b4d09 inc edx
006b4d0a cmp edx, dword ptr [ebp - 0x44]
006b4d0d jb 0x6b4d00
006b4d0f mov dword ptr [ebp - 0xc0], 0x12c
006b4d19 mov dword ptr [ebp - 0xbc], 4
006b4d23 cmp ecx, dword ptr [ebp - 0x50]
006b4d26 je 0x6b4d4e
006b4d28 mov dword ptr [ecx], 0x12c
006b4d2e mov dword ptr [ecx + 4], 4
006b4d35 add ecx, 8
006b4d38 mov dword ptr [ebp - 0x54], ecx
006b4d3b jmp 0x6b4d64
006b4d3d add dword ptr [eax + edx*8 + 4], 4
006b4d42 jns 0x6b4d64
006b4d44 mov dword ptr [eax + edx*8 + 4], 0
006b4d4c jmp 0x6b4d64
006b4d4e lea eax, [ebp - 0xc0]
006b4d54 push eax
006b4d55 push ecx
006b4d56 lea ecx, [ebp - 0x58]
006b4d59 call 0x48d900
006b4d5e mov ecx, dword ptr [ebp - 0x54]
006b4d61 mov eax, dword ptr [ebp - 0x58]
006b4d64 mov dword ptr [ebp - 0x44], ecx
006b4d67 xor edx, edx
006b4d69 sub dword ptr [ebp - 0x44], eax
006b4d6c sar dword ptr [ebp - 0x44], 3
006b4d70 cmp dword ptr [ebp - 0x44], edx
006b4d73 jbe 0x6b4d81
006b4d75 cmp dword ptr [eax + edx*8], 0x5a
006b4d79 je 0x6b4daf
006b4d7b inc edx
006b4d7c cmp edx, dword ptr [ebp - 0x44]
006b4d7f jb 0x6b4d75
006b4d81 mov dword ptr [ebp - 0xc8], 0x5a
006b4d8b mov dword ptr [ebp - 0xc4], 2
006b4d95 cmp ecx, dword ptr [ebp - 0x50]
006b4d98 je 0x6b4dc0
006b4d9a mov dword ptr [ecx], 0x5a
006b4da0 mov dword ptr [ecx + 4], 2
006b4da7 add ecx, 8
006b4daa mov dword ptr [ebp - 0x54], ecx
006b4dad jmp 0x6b4dd6
006b4daf add dword ptr [eax + edx*8 + 4], 2
006b4db4 jns 0x6b4dd6
006b4db6 mov dword ptr [eax + edx*8 + 4], 0
006b4dbe jmp 0x6b4dd6
006b4dc0 lea eax, [ebp - 0xc8]
006b4dc6 push eax
006b4dc7 push ecx
006b4dc8 lea ecx, [ebp - 0x58]
006b4dcb call 0x48d900
006b4dd0 mov ecx, dword ptr [ebp - 0x54]
006b4dd3 mov eax, dword ptr [ebp - 0x58]
006b4dd6 cmp dword ptr [edi], 4
006b4dd9 je 0x6b4e54
006b4ddf mov dword ptr [ebp - 0x44], ecx
006b4de2 xor edx, edx
006b4de4 sub dword ptr [ebp - 0x44], eax
006b4de7 sar dword ptr [ebp - 0x44], 3
006b4deb cmp dword ptr [ebp - 0x44], edx
006b4dee jbe 0x6b4dff
006b4df0 cmp dword ptr [eax + edx*8], 0x15e
006b4df7 je 0x6b4e2d
006b4df9 inc edx
006b4dfa cmp edx, dword ptr [ebp - 0x44]
006b4dfd jb 0x6b4df0
006b4dff mov dword ptr [ebp - 0xd0], 0x15e
006b4e09 mov dword ptr [ebp - 0xcc], 1
006b4e13 cmp ecx, dword ptr [ebp - 0x50]
006b4e16 je 0x6b4e3e
006b4e18 mov dword ptr [ecx], 0x15e
006b4e1e mov dword ptr [ecx + 4], 1
006b4e25 add ecx, 8
006b4e28 mov dword ptr [ebp - 0x54], ecx
006b4e2b jmp 0x6b4e54
006b4e2d add dword ptr [eax + edx*8 + 4], 1
006b4e32 jns 0x6b4e54
006b4e34 mov dword ptr [eax + edx*8 + 4], 0
006b4e3c jmp 0x6b4e54
006b4e3e lea eax, [ebp - 0xd0]
006b4e44 push eax
006b4e45 push ecx
006b4e46 lea ecx, [ebp - 0x58]
006b4e49 call 0x48d900
006b4e4e mov ecx, dword ptr [ebp - 0x54]
006b4e51 mov eax, dword ptr [ebp - 0x58]
006b4e54 cmp dword ptr [edi], 0
006b4e57 jne 0x6b4ecb
006b4e59 mov dword ptr [ebp - 0x44], ecx
006b4e5c xor edx, edx
006b4e5e sub dword ptr [ebp - 0x44], eax
006b4e61 sar dword ptr [ebp - 0x44], 3
006b4e65 cmp dword ptr [ebp - 0x44], edx
006b4e68 jbe 0x6b4e7c
006b4e6a nop word ptr [eax + eax]
006b4e70 cmp dword ptr [eax + edx*8], 0x64
006b4e74 je 0x6b4eaa
006b4e76 inc edx
006b4e77 cmp edx, dword ptr [ebp - 0x44]
006b4e7a jb 0x6b4e70
006b4e7c mov dword ptr [ebp - 0x168], 0x64
006b4e86 mov dword ptr [ebp - 0x164], 1
006b4e90 cmp ecx, dword ptr [ebp - 0x50]
006b4e93 je 0x6b4ebb
006b4e95 mov dword ptr [ecx], 0x64
006b4e9b mov dword ptr [ecx + 4], 1
006b4ea2 add ecx, 8
006b4ea5 mov dword ptr [ebp - 0x54], ecx
006b4ea8 jmp 0x6b4ecb
006b4eaa add dword ptr [eax + edx*8 + 4], 1
006b4eaf jns 0x6b4ecb
006b4eb1 mov dword ptr [eax + edx*8 + 4], 0
006b4eb9 jmp 0x6b4ecb
006b4ebb lea eax, [ebp - 0x168]
006b4ec1 push eax
006b4ec2 push ecx
006b4ec3 lea ecx, [ebp - 0x58]
006b4ec6 call 0x48d900
006b4ecb mov eax, dword ptr [ebp - 0x7c]
006b4ece sub esp, 0x10
006b4ed1 movq xmm0, qword ptr [0xa08c44]
006b4ed9 mov ecx, esp
006b4edb mov dword ptr [ecx], eax
006b4edd mov eax, dword ptr [0xa08c4c]
006b4ee2 movq qword ptr [ecx + 4], xmm0
006b4ee7 mov dword ptr [ecx + 0xc], eax
006b4eea lea ecx, [ebp - 0x58]
006b4eed call 0x489420
006b4ef2 mov dword ptr [esi], eax
006b4ef4 mov dword ptr [edi], 0
006b4efa cmp dword ptr [esi], 0xa
006b4efd jne 0x6b51d4
006b4f03 mov ecx, dword ptr [0xbfd65c]
006b4f09 push 1
006b4f0b push 0
006b4f0d push 0x16
006b4f0f lea ecx, [ecx + 0x1ba40]
006b4f15 call 0x91d550
006b4f1a test eax, eax
006b4f1c je 0x6b51d4
006b4f22 movq xmm0, qword ptr [0xa08cd4]
006b4f2a mov eax, dword ptr [0xa08cdc]
006b4f2f mov esi, dword ptr [ebp - 0x7c]
006b4f32 movq qword ptr [ebp - 0x154], xmm0
006b4f3a mov dword ptr [ebp - 0x44], eax
006b4f3d mov dword ptr [ebp - 0x14c], eax
006b4f43 test esi, esi
006b4f45 jne 0x6b4f57
006b4f47 push 0xb4d6c4
006b4f4c push 3
006b4f4e call 0x95e330
006b4f53 add esp, 8
006b4f56 int3 
006b4f57 mov ecx, dword ptr [ebp - 0x154]
006b4f5d mov eax, esi
006b4f5f shr eax, cl
006b4f61 mov ecx, dword ptr [ebp - 0x150]
006b4f67 xor eax, esi
006b4f69 mov edx, eax
006b4f6b shl edx, cl
006b4f6d mov ecx, dword ptr [ebp - 0x44]
006b4f70 xor edx, eax
006b4f72 mov esi, edx
006b4f74 mov eax, 0xcccccccd
006b4f79 shr esi, cl
006b4f7b xor esi, edx
006b4f7d mul esi
006b4f7f mov dword ptr [ebp - 0x158], esi
006b4f85 shr edx, 2
006b4f88 lea eax, [edx + edx*4]
006b4f8b sub esi, eax
006b4f8d je 0x6b51d1
006b4f93 xor eax, eax
006b4f95 xor ecx, ecx
006b4f97 mov dword ptr [ebp - 0x88], eax
006b4f9d mov dword ptr [ebp - 0x84], ecx
006b4fa3 mov dword ptr [ebp - 0x80], eax
006b4fa6 mov byte ptr [ebp - 4], 1
006b4faa cmp dword ptr [edi], 3
006b4fad je 0x6b4fe2
006b4faf lea eax, [ebp - 0x160]
006b4fb5 mov dword ptr [ebp - 0x160], 0x14
006b4fbf push eax
006b4fc0 push ecx
006b4fc1 lea ecx, [ebp - 0x88]
006b4fc7 mov dword ptr [ebp - 0x15c], 0x14
006b4fd1 call 0x48d900
006b4fd6 mov ecx, dword ptr [ebp - 0x84]
006b4fdc mov eax, dword ptr [ebp - 0x88]
006b4fe2 mov esi, ecx
006b4fe4 xor edx, edx
006b4fe6 sub esi, eax
006b4fe8 sar esi, 3
006b4feb test esi, esi
006b4fed je 0x6b4ffb
006b4fef nop 
006b4ff0 cmp dword ptr [eax + edx*8], 0x1e
006b4ff4 je 0x6b502c
006b4ff6 inc edx
006b4ff7 cmp edx, esi
006b4ff9 jb 0x6b4ff0
006b4ffb mov dword ptr [ebp - 0x170], 0x1e
006b5005 mov dword ptr [ebp - 0x16c], 0xf
006b500f cmp ecx, dword ptr [ebp - 0x80]
006b5012 je 0x6b503d
006b5014 mov dword ptr [ecx], 0x1e
006b501a mov dword ptr [ecx + 4], 0xf
006b5021 add ecx, 8
006b5024 mov dword ptr [ebp - 0x84], ecx
006b502a jmp 0x6b505c
006b502c add dword ptr [eax + edx*8 + 4], 0xf
006b5031 jns 0x6b505c
006b5033 mov dword ptr [eax + edx*8 + 4], 0
006b503b jmp 0x6b505c
006b503d lea eax, [ebp - 0x170]
006b5043 push eax
006b5044 push ecx
006b5045 lea ecx, [ebp - 0x88]
006b504b call 0x48d900
006b5050 mov ecx, dword ptr [ebp - 0x84]
006b5056 mov eax, dword ptr [ebp - 0x88]
006b505c mov esi, ecx
006b505e xor edx, edx
006b5060 sub esi, eax
006b5062 sar esi, 3
006b5065 test esi, esi
006b5067 je 0x6b507b
006b5069 nop dword ptr [eax]
006b5070 cmp dword ptr [eax + edx*8], 0x28
006b5074 je 0x6b50ac
006b5076 inc edx
006b5077 cmp edx, esi
006b5079 jb 0x6b5070
006b507b mov dword ptr [ebp - 0xd8], 0x28
006b5085 mov dword ptr [ebp - 0xd4], 0xf
006b508f cmp ecx, dword ptr [ebp - 0x80]
006b5092 je 0x6b50bd
006b5094 mov dword ptr [ecx], 0x28
006b509a mov dword ptr [ecx + 4], 0xf
006b50a1 add ecx, 8
006b50a4 mov dword ptr [ebp - 0x84], ecx
006b50aa jmp 0x6b50dc
006b50ac add dword ptr [eax + edx*8 + 4], 0xf
006b50b1 jns 0x6b50dc
006b50b3 mov dword ptr [eax + edx*8 + 4], 0
006b50bb jmp 0x6b50dc
006b50bd lea eax, [ebp - 0xd8]
006b50c3 push eax
006b50c4 push ecx
006b50c5 lea ecx, [ebp - 0x88]
006b50cb call 0x48d900
006b50d0 mov ecx, dword ptr [ebp - 0x84]
006b50d6 mov eax, dword ptr [ebp - 0x88]
006b50dc mov esi, ecx
006b50de xor edx, edx
006b50e0 sub esi, eax
006b50e2 sar esi, 3
006b50e5 test esi, esi
006b50e7 je 0x6b50fb
006b50e9 nop dword ptr [eax]
006b50f0 cmp dword ptr [eax + edx*8], 0xa
006b50f4 je 0x6b512c
006b50f6 inc edx
006b50f7 cmp edx, esi
006b50f9 jb 0x6b50f0
006b50fb mov dword ptr [ebp - 0xe0], 0xa
006b5105 mov dword ptr [ebp - 0xdc], 0xf
006b510f cmp ecx, dword ptr [ebp - 0x80]
006b5112 je 0x6b513d
006b5114 mov dword ptr [ecx], 0xa
006b511a mov dword ptr [ecx + 4], 0xf
006b5121 add ecx, 8
006b5124 mov dword ptr [ebp - 0x84], ecx
006b512a jmp 0x6b5150
006b512c add dword ptr [eax + edx*8 + 4], 0xf
006b5131 jns 0x6b5150
006b5133 mov dword ptr [eax + edx*8 + 4], 0
006b513b jmp 0x6b5150
006b513d lea eax, [ebp - 0xe0]
006b5143 push eax
006b5144 push ecx
006b5145 lea ecx, [ebp - 0x88]
006b514b call 0x48d900
006b5150 movups xmm0, xmmword ptr [ebp - 0x158]
006b5157 sub esp, 0x10
006b515a lea ecx, [ebp - 0x88]
006b5160 mov eax, esp
006b5162 movups xmmword ptr [eax], xmm0
006b5165 call 0x489420
006b516a mov esi, dword ptr [ebp - 0x48]
006b516d mov byte ptr [ebp - 4], 0
006b5171 mov ecx, dword ptr [ebp - 0x88]
006b5177 mov dword ptr [esi], eax
006b5179 test ecx, ecx
006b517b je 0x6b51d4
006b517d mov eax, dword ptr [ebp - 0x80]
006b5180 sub eax, ecx
006b5182 sar eax, 3
006b5185 lea edx, [eax*8]
006b518c mov eax, ecx
006b518e cmp edx, 0x1000
006b5194 jb 0x6b51aa
006b5196 mov ecx, dword ptr [ecx - 4]
006b5199 add edx, 0x23
006b519c sub eax, ecx
006b519e add eax, -4
006b51a1 cmp eax, 0x1f
006b51a4 ja 0x6b6957
006b51aa push edx
006b51ab push ecx
006b51ac call 0x9eb08e
006b51b1 add esp, 8
006b51b4 mov dword ptr [ebp - 0x88], 0
006b51be mov dword ptr [ebp - 0x84], 0
006b51c8 mov dword ptr [ebp - 0x80], 0
006b51cf jmp 0x6b51d4
006b51d1 mov esi, dword ptr [ebp - 0x48]
006b51d4 cmp dword ptr [ebp - 0x98], 3
006b51db je 0x6b5216
006b51dd cmp dword ptr [esi], 0x14
006b51e0 je 0x6b5216
006b51e2 mov ecx, dword ptr [0xbfd65c]
006b51e8 push 1
006b51ea push 0
006b51ec push 0x54
006b51ee lea ecx, [ecx + 0x1ba40]
006b51f4 call 0x91d550
006b51f9 test eax, eax
006b51fb je 0x6b5216
006b51fd movss xmm0, dword ptr [0xb6a2cc]
006b5205 comiss xmm0, dword ptr [ebp - 0x9c]
006b520c jbe 0x6b5216
006b520e mov dword ptr [esi], 0x14
006b5214 jmp 0x6b525a
006b5216 cmp dword ptr [esi], 0x5a
006b5219 je 0x6b525a
006b521b mov ecx, dword ptr [0xbfd65c]
006b5221 push 1
006b5223 push 0
006b5225 push 0x48
006b5227 lea ecx, [ecx + 0x1ba40]
006b522d call 0x91d550
006b5232 test eax, eax
006b5234 je 0x6b525a
006b5236 movss xmm1, dword ptr [ebp - 0x9c]
006b523e comiss xmm1, dword ptr [0xb6a2cc]
006b5245 jb 0x6b525a
006b5247 movss xmm0, dword ptr [0xb6a350]
006b524f comiss xmm0, xmm1
006b5252 jbe 0x6b525a
006b5254 mov dword ptr [esi], 0x5a
006b525a mov dword ptr [ebp - 4], 0xffffffff
006b5261 mov ecx, dword ptr [ebp - 0x58]
006b5264 test ecx, ecx
006b5266 je 0x6b52b4
006b5268 mov eax, dword ptr [ebp - 0x50]
006b526b sub eax, ecx
006b526d sar eax, 3
006b5270 lea edx, [eax*8]
006b5277 mov eax, ecx
006b5279 cmp edx, 0x1000
006b527f jb 0x6b5295
006b5281 mov ecx, dword ptr [ecx - 4]
006b5284 add edx, 0x23
006b5287 sub eax, ecx
006b5289 add eax, -4
006b528c cmp eax, 0x1f
006b528f ja 0x6b6957
006b5295 push edx
006b5296 push ecx
006b5297 call 0x9eb08e
006b529c add esp, 8
006b529f mov dword ptr [ebp - 0x58], 0
006b52a6 mov dword ptr [ebp - 0x54], 0
006b52ad mov dword ptr [ebp - 0x50], 0
006b52b4 mov ecx, dword ptr [0xbfd65c]
006b52ba push 1
006b52bc add ecx, 0x1ba40
006b52c2 push ecx
006b52c3 push 0xfb
006b52c8 call 0x91d340
006b52cd mov ecx, dword ptr [0xbfd65c]
006b52d3 mov esi, eax
006b52d5 test esi, esi
006b52d7 push 1
006b52d9 setne byte ptr [ebp - 0x49]
006b52dd add ecx, 0x1ba40
006b52e3 push ecx
006b52e4 push 0xfc
006b52e9 call 0x91d340
006b52ee test eax, eax
006b52f0 setne dl
006b52f3 mov byte ptr [ebp - 0x59], dl
006b52f6 test esi, esi
006b52f8 je 0x6b5307
006b52fa test dl, dl
006b52fc je 0x6b5307
006b52fe xor dl, dl
006b5300 xor cl, cl
006b5302 mov byte ptr [ebp - 0x59], dl
006b5305 jmp 0x6b530a
006b5307 mov cl, byte ptr [ebp - 0x49]
006b530a mov esi, dword ptr [ebp - 0x48]
006b530d mov eax, dword ptr [esi]
006b530f cmp eax, 0x46
006b5312 jne 0x6b5320
006b5314 test cl, cl
006b5316 je 0x6b5374
006b5318 mov dword ptr [esi], 0x12c
006b531e jmp 0x6b536e
006b5320 cmp eax, 0x12c
006b5325 jne 0x6b5374
006b5327 test dl, dl
006b5329 je 0x6b5374
006b532b mov ecx, dword ptr [edi]
006b532d mov eax, dword ptr [0xbfd680]
006b5332 test ecx, ecx
006b5334 js 0x6b5368
006b5336 mov edx, dword ptr [eax + 0x29ea8]
006b533c mov eax, dword ptr [eax + 0x29eac]
006b5342 sub eax, edx
006b5344 sar eax, 2
006b5347 cmp ecx, eax
006b5349 jge 0x6b5368
006b534b mov eax, dword ptr [edx + ecx*4]
006b534e test eax, eax
006b5350 je 0x6b5368
006b5352 mov eax, dword ptr [eax + 0x58]
006b5355 test eax, eax
006b5357 je 0x6b5368
006b5359 cmp eax, 5
006b535c je 0x6b5368
006b535e cmp eax, 1
006b5361 je 0x6b5368
006b5363 cmp eax, 3
006b5366 jne 0x6b5374
006b5368 mov dword ptr [esi], 0x46
006b536e mov dword ptr [edi], 0
006b5374 mov ecx, dword ptr [esi]
006b5376 mov eax, ecx
006b5378 mov edx, dword ptr [ebp + 0xc]
006b537b cmp eax, 0x12c
006b5380 ja 0x6b61f3
006b5386 je 0x6b61a2
006b538c sub eax, 0xa
006b538f cmp eax, 0x8c
006b5394 ja 0x6b634c
006b539a movzx eax, byte ptr [eax + 0x6b6abc]
006b53a1 jmp dword ptr [eax*4 + 0x6b6a7c]
006b53a8 cmp dword ptr [edi], 0
006b53ab jne 0x6b577f
006b53b1 push 2
006b53b3 lea ecx, [ebp - 0x6c]
006b53b6 mov dword ptr [edi], 1
006b53bc call 0x7a7d50
006b53c1 test eax, eax
006b53c3 jne 0x6b53cb
006b53c5 mov dword ptr [edi], 2
006b53cb call 0x6cba20
006b53d0 test al, al
006b53d2 mov edx, 0x32
006b53d7 mov ecx, 0x14
006b53dc cmovne ecx, edx
006b53df push ecx
006b53e0 lea ecx, [ebp - 0x6c]
006b53e3 call 0x7a7d50
006b53e8 test eax, eax
006b53ea jne 0x6b53f2
006b53ec mov dword ptr [edi], 5
006b53f2 push 0x32
006b53f4 lea ecx, [ebp - 0x6c]
006b53f7 call 0x7a7d50
006b53fc test eax, eax
006b53fe jne 0x6b5435
006b5400 mov eax, dword ptr [0xbfd680]
006b5405 cmp byte ptr [eax + 0x1e7], 0
006b540c jne 0x6b542f
006b540e cmp dword ptr [eax + 8], 2
006b5412 jne 0x6b5435
006b5414 mov eax, dword ptr [0xbfd65c]
006b5419 test eax, eax
006b541b je 0x6b5435
006b541d cmp dword ptr [eax + 0x1c3204], 0
006b5424 ja 0x6b542f
006b5426 cmp byte ptr [eax + 0x1c31a1], 0
006b542d je 0x6b5435
006b542f mov dword ptr [edi], 0xc
006b5435 push 0x64
006b5437 lea ecx, [ebp - 0x6c]
006b543a call 0x7a7d50
006b543f test eax, eax
006b5441 jne 0x6b5478
006b5443 mov eax, dword ptr [0xbfd680]
006b5448 cmp byte ptr [eax + 0x194], 0
006b544f jne 0x6b5472
006b5451 cmp dword ptr [eax + 8], 2
006b5455 jne 0x6b5478
006b5457 mov eax, dword ptr [0xbfd65c]
006b545c test eax, eax
006b545e je 0x6b5478
006b5460 cmp dword ptr [eax + 0x1c3204], 0
006b5467 ja 0x6b5472
006b5469 cmp byte ptr [eax + 0x1c31a1], 0
006b5470 je 0x6b5478
006b5472 mov dword ptr [edi], 9
006b5478 push 0x64
006b547a lea ecx, [ebp - 0x6c]
006b547d call 0x7a7d50
006b5482 test eax, eax
006b5484 jne 0x6b548c
006b5486 mov dword ptr [edi], 0xa
006b548c push 0x32
006b548e lea ecx, [ebp - 0x6c]
006b5491 call 0x7a7d50
006b5496 test eax, eax
006b5498 je 0x6b5539
006b549e mov ecx, dword ptr [0xbfd65c]
006b54a4 push 1
006b54a6 push 0
006b54a8 push 0x12
006b54aa lea ecx, [ecx + 0x1ba40]
006b54b0 call 0x91d550
006b54b5 test eax, eax
006b54b7 je 0x6b54e3
006b54b9 mov ecx, dword ptr [0xbfd65c]
006b54bf push 0x12
006b54c1 lea ecx, [ecx + 0x1ba40]
006b54c7 call 0x91db10
006b54cc mov ecx, eax
006b54ce mov eax, 0x1e
006b54d3 cdq 
006b54d4 idiv ecx
006b54d6 lea ecx, [ebp - 0x6c]
006b54d9 push eax
006b54da call 0x7a7d50
006b54df test eax, eax
006b54e1 je 0x6b5539
006b54e3 mov ecx, dword ptr [0xbfd65c]
006b54e9 push 1
006b54eb add ecx, 0x1ba40
006b54f1 push ecx
006b54f2 push 0xee
006b54f7 call 0x91d340
006b54fc test eax, eax
006b54fe je 0x6b550e
006b5500 push 0x28
006b5502 lea ecx, [ebp - 0x6c]
006b5505 call 0x7a7d50
006b550a test eax, eax
006b550c je 0x6b5539
006b550e mov ecx, dword ptr [0xbfd65c]
006b5514 push 1
006b5516 add ecx, 0x1ba40
006b551c push ecx
006b551d push 0xef
006b5522 call 0x91d340
006b5527 test eax, eax
006b5529 je 0x6b553f
006b552b push 0x28
006b552d lea ecx, [ebp - 0x6c]
006b5530 call 0x7a7d50
006b5535 test eax, eax
006b5537 jne 0x6b553f
006b5539 mov dword ptr [edi], 4
006b553f push 0xa
006b5541 lea ecx, [ebp - 0x6c]
006b5544 call 0x7a7d50
006b5549 test eax, eax
006b554b je 0x6b55ee
006b5551 mov ecx, dword ptr [0xbfd65c]
006b5557 push 1
006b5559 add ecx, 0x1ba40
006b555f push ecx
006b5560 push 0xad
006b5565 call 0x91d340
006b556a test eax, eax
006b556c je 0x6b557c
006b556e push 3
006b5570 lea ecx, [ebp - 0x6c]
006b5573 call 0x7a7d50
006b5578 test eax, eax
006b557a je 0x6b55ee
006b557c mov ecx, dword ptr [0xbfd65c]
006b5582 push 1
006b5584 push 0
006b5586 push 0x26
006b5588 lea ecx, [ecx + 0x1ba40]
006b558e call 0x91d550
006b5593 test eax, eax
006b5595 je 0x6b55c1
006b5597 mov ecx, dword ptr [0xbfd65c]
006b559d push 0x26
006b559f lea ecx, [ecx + 0x1ba40]
006b55a5 call 0x91db10
006b55aa mov ecx, eax
006b55ac mov eax, 0xa
006b55b1 cdq 
006b55b2 idiv ecx
006b55b4 lea ecx, [ebp - 0x6c]
006b55b7 push eax
006b55b8 call 0x7a7d50
006b55bd test eax, eax
006b55bf je 0x6b55ee
006b55c1 mov ecx, dword ptr [0xbfd65c]
006b55c7 push 5
006b55c9 lea ecx, [ecx + 0x1ba40]
006b55cf call 0x5ef580
006b55d4 test al, al
006b55d6 je 0x6b570c
006b55dc push 0x10
006b55de lea ecx, [ebp - 0x6c]
006b55e1 call 0x7a7d50
006b55e6 test eax, eax
006b55e8 jne 0x6b570c
006b55ee push 4
006b55f0 lea ecx, [ebp - 0x6c]
006b55f3 mov dword ptr [edi], 3
006b55f9 call 0x7a7d50
006b55fe test eax, eax
006b5600 jne 0x6b5634
006b5602 mov eax, dword ptr [0xbfd680]
006b5607 cmp byte ptr [eax + 0x6d], 0
006b560b jne 0x6b562e
006b560d cmp dword ptr [eax + 8], 2
006b5611 jne 0x6b5634
006b5613 mov eax, dword ptr [0xbfd65c]
006b5618 test eax, eax
006b561a je 0x6b5634
006b561c cmp dword ptr [eax + 0x1c3204], 0
006b5623 ja 0x6b562e
006b5625 cmp byte ptr [eax + 0x1c31a1], 0
006b562c je 0x6b5634
006b562e mov dword ptr [edi], 8
006b5634 push 0x14
006b5636 lea ecx, [ebp - 0x6c]
006b5639 call 0x7a7d50
006b563e test eax, eax
006b5640 jne 0x6b5677
006b5642 mov eax, dword ptr [0xbfd680]
006b5647 cmp byte ptr [eax + 0x1d3], 0
006b564e jne 0x6b5671
006b5650 cmp dword ptr [eax + 8], 2
006b5654 jne 0x6b5677
006b5656 mov eax, dword ptr [0xbfd65c]
006b565b test eax, eax
006b565d je 0x6b5677
006b565f cmp dword ptr [eax + 0x1c3204], 0
006b5666 ja 0x6b5671
006b5668 cmp byte ptr [eax + 0x1c31a1], 0
006b566f je 0x6b5677
006b5671 mov dword ptr [edi], 0xb
006b5677 push 0x14
006b5679 lea ecx, [ebp - 0x6c]
006b567c call 0x7a7d50
006b5681 test eax, eax
006b5683 je 0x6b56ca
006b5685 mov ecx, dword ptr [0xbfd65c]
006b568b push 1
006b568d push 0
006b568f push 0x11
006b5691 lea ecx, [ecx + 0x1ba40]
006b5697 call 0x91d550
006b569c test eax, eax
006b569e je 0x6b56d0
006b56a0 mov ecx, dword ptr [0xbfd65c]
006b56a6 push 0x11
006b56a8 add ecx, 0x1ba40
006b56ae call 0x91db10
006b56b3 mov ecx, eax
006b56b5 mov eax, 0xa
006b56ba cdq 
006b56bb idiv ecx
006b56bd lea ecx, [ebp - 0x6c]
006b56c0 push eax
006b56c1 call 0x7a7d50
006b56c6 test eax, eax
006b56c8 jne 0x6b56d0
006b56ca mov dword ptr [edi], 6
006b56d0 push 5
006b56d2 lea ecx, [ebp - 0x6c]
006b56d5 call 0x7a7d50
006b56da test eax, eax
006b56dc jne 0x6b570c
006b56de mov esi, dword ptr [0xbfd65c]
006b56e4 push 0x10
006b56e6 lea ecx, [esi + 0x1ba40]
006b56ec call 0x5ef580
006b56f1 test al, al
006b56f3 jne 0x6b5706
006b56f5 push 0x11
006b56f7 lea ecx, [esi + 0x1ba40]
006b56fd call 0x5ef580
006b5702 test al, al
006b5704 je 0x6b570c
006b5706 mov dword ptr [edi], 0xb
006b570c push 0xa0
006b5711 lea ecx, [ebp - 0x6c]
006b5714 call 0x7a7d50
006b5719 mov ecx, dword ptr [0xbfd65c]
006b571f test eax, eax
006b5721 jne 0x6b5753
006b5723 mov eax, dword ptr [0xbfd680]
006b5728 cmp byte ptr [eax + 0x12c], 0
006b572f jne 0x6b574d
006b5731 cmp dword ptr [eax + 8], 2
006b5735 jne 0x6b5753
006b5737 test ecx, ecx
006b5739 je 0x6b5753
006b573b cmp dword ptr [ecx + 0x1c3204], 0
006b5742 ja 0x6b574d
006b5744 cmp byte ptr [ecx + 0x1c31a1], 0
006b574b je 0x6b5753
006b574d mov dword ptr [edi], 7
006b5753 push 1
006b5755 push 0
006b5757 add ecx, 0x1ba40
006b575d push 0x16
006b575f call 0x91d550
006b5764 test eax, eax
006b5766 je 0x6b577f
006b5768 mov eax, dword ptr [0xbfd65c]
006b576d mov eax, dword ptr [eax + 0x18190]
006b5773 cmp dword ptr [eax + 8], 8
006b5777 je 0x6b577f
006b5779 mov dword ptr [edi], 6
006b577f mov esi, dword ptr [0xbfd65c]
006b5785 mov eax, dword ptr [esi + 0x18190]
006b578b cmp dword ptr [eax + 8], 8
006b578f jne 0x6b593a
006b5795 mov ecx, esi
006b5797 call 0x6cba40
006b579c mov ecx, esi
006b579e mov byte ptr [ebp - 0x49], al
006b57a1 call 0x70e2d0
006b57a6 mov ecx, dword ptr [eax + 0x10]
006b57a9 mov al, byte ptr [ebp - 0x49]
006b57ac mov ecx, dword ptr [ecx + 0xc]
006b57af test al, al
006b57b1 je 0x6b58a1
006b57b7 cmp ecx, 0x19
006b57ba ja 0x6b58f2
006b57c0 movzx eax, byte ptr [ecx + 0x6b6b64]
006b57c7 jmp dword ptr [eax*4 + 0x6b6b4c]
006b57ce mov dword ptr [edi], 6
006b57d4 mov dword ptr [edi], 6
006b57da mov esi, dword ptr [ebp - 0x48]
006b57dd mov ecx, dword ptr [0xbfd65c]
006b57e3 push 1
006b57e5 add ecx, 0x1ba40
006b57eb push ecx
006b57ec push 0xcb
006b57f1 call 0x91d340
006b57f6 test eax, eax
006b57f8 je 0x6b5806
006b57fa test dword ptr [ebp - 0xa4], 0x8000
006b5804 je 0x6b5830
006b5806 cmp dword ptr [esi], 0x28
006b5809 jne 0x6b6361
006b580f mov ecx, dword ptr [0xbfd65c]
006b5815 push 1
006b5817 add ecx, 0x1ba40
006b581d push ecx
006b581e push 0xfa
006b5823 call 0x91d340
006b5828 test eax, eax
006b582a je 0x6b6361
006b5830 mov edx, dword ptr [0xbfd658]
006b5836 mov ecx, dword ptr [ebp - 0x48]
006b5839 test edx, edx
006b583b jne 0x6b636a
006b5841 mov eax, dword ptr [ecx]
006b5843 cmp eax, 0xa
006b5846 jne 0x6b585c
006b5848 mov esi, dword ptr [edi]
006b584a cmp esi, 1
006b584d je 0x6b5854
006b584f cmp esi, 9
006b5852 jne 0x6b585c
006b5854 mov dword ptr [edi], 5
006b585a mov eax, dword ptr [ecx]
006b585c cmp eax, 0x14
006b585f jne 0x6b586e
006b5861 cmp dword ptr [edi], 1
006b5864 jne 0x6b586e
006b5866 mov dword ptr [edi], 4
006b586c mov eax, dword ptr [ecx]
006b586e cmp eax, 0x1e
006b5871 jne 0x6b5884
006b5873 cmp dword ptr [edi], 1
006b5876 jne 0x6b636a
006b587c mov dword ptr [edi], 3
006b5882 mov eax, dword ptr [ecx]
006b5884 cmp eax, 0x28
006b5887 jne 0x6b636a
006b588d cmp dword ptr [edi], 1
006b5890 jne 0x6b636a
006b5896 mov dword ptr [edi], 2
006b589c jmp 0x6b636a
006b58a1 cmp ecx, 0x17
006b58a4 ja 0x6b58f2
006b58a6 movzx eax, byte ptr [ecx + 0x6b6b98]
006b58ad jmp dword ptr [eax*4 + 0x6b6b80]
006b58b4 mov eax, dword ptr [0xbfd680]
006b58b9 cmp byte ptr [eax + 0x1e7], 0
006b58c0 jne 0x6b58e4
006b58c2 cmp dword ptr [eax + 8], 2
006b58c6 jne 0x6b593a
006b58c8 mov esi, dword ptr [0xbfd65c]
006b58ce test esi, esi
006b58d0 je 0x6b593a
006b58d2 cmp dword ptr [esi + 0x1c3204], 0
006b58d9 ja 0x6b58e4
006b58db cmp byte ptr [esi + 0x1c31a1], 0
006b58e2 je 0x6b593a
006b58e4 mov dword ptr [edi], 0xc
006b58ea jmp 0x6b57da
006b58ef mov al, byte ptr [ebp - 0x49]
006b58f2 test ecx, ecx
006b58f4 je 0x6b5962
006b58f6 test al, al
006b58f8 jne 0x6b5904
006b58fa cmp ecx, 1
006b58fd je 0x6b5909
006b58ff cmp ecx, 6
006b5902 jmp 0x6b5934
006b5904 cmp ecx, 0x18
006b5907 jne 0x6b5914
006b5909 mov dword ptr [edi], 4
006b590f jmp 0x6b57da
006b5914 cmp ecx, 0x19
006b5917 jne 0x6b5921
006b5919 mov dword ptr [edi], 2
006b591f jmp 0x6b5943
006b5921 cmp ecx, 4
006b5924 jne 0x6b5931
006b5926 mov dword ptr [edi], 3
006b592c jmp 0x6b57da
006b5931 cmp ecx, 5
006b5934 je 0x6b57d4
006b593a cmp dword ptr [edi], 2
006b593d jne 0x6b57da
006b5943 mov ecx, dword ptr [0xbfd65c]
006b5949 push 1
006b594b push 0
006b594d push 0x57
006b594f lea ecx, [ecx + 0x1ba40]
006b5955 call 0x91d550
006b595a test eax, eax
006b595c je 0x6b57da
006b5962 mov dword ptr [edi], 1
006b5968 jmp 0x6b57da
006b596d cmp dword ptr [edi], 0
006b5970 jne 0x6b5a84
006b5976 push 0x14
006b5978 lea ecx, [ebp - 0x6c]
006b597b mov dword ptr [edi], 1
006b5981 call 0x7a7d50
006b5986 test eax, eax
006b5988 jne 0x6b5992
006b598a mov dword ptr [edi], 2
006b5990 jmp 0x6b5997
006b5992 cmp dword ptr [edi], 2
006b5995 jne 0x6b59da
006b5997 push 0x14
006b5999 lea ecx, [ebp - 0x6c]
006b599c call 0x7a7d50
006b59a1 test eax, eax
006b59a3 jne 0x6b59da
006b59a5 mov eax, dword ptr [0xbfd680]
006b59aa cmp byte ptr [eax + 0x13c], 0
006b59b1 jne 0x6b59d4
006b59b3 cmp dword ptr [eax + 8], 2
006b59b7 jne 0x6b59da
006b59b9 mov eax, dword ptr [0xbfd65c]
006b59be test eax, eax
006b59c0 je 0x6b59da
006b59c2 cmp dword ptr [eax + 0x1c3204], 0
006b59c9 ja 0x6b59d4
006b59cb cmp byte ptr [eax + 0x1c31a1], 0
006b59d2 je 0x6b59da
006b59d4 mov dword ptr [edi], 6
006b59da push 0x64
006b59dc lea ecx, [ebp - 0x6c]
006b59df call 0x7a7d50
006b59e4 test eax, eax
006b59e6 jne 0x6b59f0
006b59e8 mov dword ptr [edi], 3
006b59ee jmp 0x6b5a38
006b59f0 cmp dword ptr [edi], 1
006b59f3 jne 0x6b5a38
006b59f5 push 0x64
006b59f7 lea ecx, [ebp - 0x6c]
006b59fa call 0x7a7d50
006b59ff test eax, eax
006b5a01 jne 0x6b5a38
006b5a03 mov eax, dword ptr [0xbfd680]
006b5a08 cmp byte ptr [eax + 0x13e], 0
006b5a0f jne 0x6b5a32
006b5a11 cmp dword ptr [eax + 8], 2
006b5a15 jne 0x6b5a38
006b5a17 mov eax, dword ptr [0xbfd65c]
006b5a1c test eax, eax
006b5a1e je 0x6b5a38
006b5a20 cmp dword ptr [eax + 0x1c3204], 0
006b5a27 ja 0x6b5a32
006b5a29 cmp byte ptr [eax + 0x1c31a1], 0
006b5a30 je 0x6b5a38
006b5a32 mov dword ptr [edi], 5
006b5a38 push 0xc8
006b5a3d lea ecx, [ebp - 0x6c]
006b5a40 call 0x7a7d50
006b5a45 test eax, eax
006b5a47 jne 0x6b5a84
006b5a49 mov eax, dword ptr [0xbfd680]
006b5a4e cmp byte ptr [eax + 0x2b1], 0
006b5a55 jne 0x6b5a79
006b5a57 cmp dword ptr [eax + 8], 2
006b5a5b jne 0x6b5a84
006b5a5d mov esi, dword ptr [0xbfd65c]
006b5a63 test esi, esi
006b5a65 je 0x6b5a84
006b5a67 cmp dword ptr [esi + 0x1c3204], 0
006b5a6e ja 0x6b5a79
006b5a70 cmp byte ptr [esi + 0x1c31a1], 0
006b5a77 je 0x6b5a84
006b5a79 mov dword ptr [edi], 7
006b5a7f jmp 0x6b57da
006b5a84 cmp dword ptr [edi], 2
006b5a87 jne 0x6b57da
006b5a8d mov eax, dword ptr [0xbfd65c]
006b5a92 mov esi, dword ptr [ebp - 0x48]
006b5a95 cmp dword ptr [eax + 0x1c3210], 7
006b5a9c jne 0x6b57dd
006b5aa2 mov dword ptr [edi], 6
006b5aa8 jmp 0x6b57dd
006b5aad cmp dword ptr [edi], 0
006b5ab0 jne 0x6b57da
006b5ab6 mov dword ptr [ebp - 0x94], 0
006b5ac0 mov dword ptr [ebp - 0x90], 0
006b5aca mov dword ptr [ebp - 0x8c], 0
006b5ad4 lea eax, [ebp - 0xa0]
006b5ada mov dword ptr [ebp - 4], 2
006b5ae1 push eax
006b5ae2 push 0
006b5ae4 lea ecx, [ebp - 0x94]
006b5aea mov dword ptr [ebp - 0xa0], 1
006b5af4 mov dword ptr [ebp - 0x9c], 0x31
006b5afe call 0x48d900
006b5b03 mov ecx, dword ptr [ebp - 0x90]
006b5b09 xor eax, eax
006b5b0b mov esi, dword ptr [ebp - 0x94]
006b5b11 mov edx, ecx
006b5b13 sub edx, esi
006b5b15 sar edx, 3
006b5b18 test edx, edx
006b5b1a je 0x6b5b2b
006b5b1c nop dword ptr [eax]
006b5b20 cmp dword ptr [esi + eax*8], 2
006b5b24 je 0x6b5b5f
006b5b26 inc eax
006b5b27 cmp eax, edx
006b5b29 jb 0x6b5b20
006b5b2b mov dword ptr [ebp - 0xe8], 2
006b5b35 mov dword ptr [ebp - 0xe4], 1
006b5b3f cmp ecx, dword ptr [ebp - 0x8c]
006b5b45 je 0x6b5b70
006b5b47 mov dword ptr [ecx], 2
006b5b4d mov dword ptr [ecx + 4], 1
006b5b54 add ecx, 8
006b5b57 mov dword ptr [ebp - 0x90], ecx
006b5b5d jmp 0x6b5b89
006b5b5f add dword ptr [esi + eax*8 + 4], 1
006b5b64 jns 0x6b5b89
006b5b66 mov dword ptr [esi + eax*8 + 4], 0
006b5b6e jmp 0x6b5b89
006b5b70 lea eax, [ebp - 0xe8]
006b5b76 push eax
006b5b77 push ecx
006b5b78 lea ecx, [ebp - 0x94]
006b5b7e call 0x48d900
006b5b83 mov ecx, dword ptr [ebp - 0x90]
006b5b89 mov eax, dword ptr [0xbfd680]
006b5b8e cmp byte ptr [eax + 0x199], 0
006b5b95 jne 0x6b5bbc
006b5b97 cmp dword ptr [eax + 8], 2
006b5b9b jne 0x6b5bb8
006b5b9d mov eax, dword ptr [0xbfd65c]
006b5ba2 test eax, eax
006b5ba4 je 0x6b5bb8
006b5ba6 cmp dword ptr [eax + 0x1c3204], 0
006b5bad ja 0x6b5bbc
006b5baf cmp byte ptr [eax + 0x1c31a1], 0
006b5bb6 jne 0x6b5bbc
006b5bb8 xor dl, dl
006b5bba jmp 0x6b5bbe
006b5bbc mov dl, 1
006b5bbe test dl, dl
006b5bc0 mov dword ptr [ebp - 0xec], 1
006b5bca mov eax, 1
006b5bcf mov esi, 4
006b5bd4 cmovne eax, esi
006b5bd7 mov dword ptr [ebp - 0xf0], eax
006b5bdd cmp ecx, dword ptr [ebp - 0x8c]
006b5be3 je 0x6b5bf9
006b5be5 mov dword ptr [ecx], eax
006b5be7 mov dword ptr [ecx + 4], 1
006b5bee add ecx, 8
006b5bf1 mov dword ptr [ebp - 0x90], ecx
006b5bf7 jmp 0x6b5c0c
006b5bf9 lea eax, [ebp - 0xf0]
006b5bff push eax
006b5c00 push ecx
006b5c01 lea ecx, [ebp - 0x94]
006b5c07 call 0x48d900
006b5c0c lea ecx, [ebp - 0x6c]
006b5c0f call 0x7a7e20
006b5c14 movq xmm0, qword ptr [0xa08c44]
006b5c1c sub esp, 0x10
006b5c1f mov ecx, esp
006b5c21 mov dword ptr [ecx], eax
006b5c23 mov eax, dword ptr [0xa08c4c]
006b5c28 movq qword ptr [ecx + 4], xmm0
006b5c2d mov dword ptr [ecx + 0xc], eax
006b5c30 lea ecx, [ebp - 0x94]
006b5c36 call 0x489420
006b5c3b mov dword ptr [ebp - 4], 0xffffffff
006b5c42 mov ecx, dword ptr [ebp - 0x94]
006b5c48 mov dword ptr [edi], eax
006b5c4a test ecx, ecx
006b5c4c je 0x6b57da
006b5c52 mov eax, dword ptr [ebp - 0x8c]
006b5c58 sub eax, ecx
006b5c5a sar eax, 3
006b5c5d lea edx, [eax*8]
006b5c64 mov eax, ecx
006b5c66 cmp edx, 0x1000
006b5c6c jb 0x6b5c82
006b5c6e mov ecx, dword ptr [ecx - 4]
006b5c71 add edx, 0x23
006b5c74 sub eax, ecx
006b5c76 add eax, -4
006b5c79 cmp eax, 0x1f
006b5c7c ja 0x6b6957
006b5c82 push edx
006b5c83 push ecx
006b5c84 call 0x9eb08e
006b5c89 add esp, 8
006b5c8c mov dword ptr [ebp - 0x94], 0
006b5c96 mov dword ptr [ebp - 0x90], 0
006b5ca0 mov dword ptr [ebp - 0x8c], 0
006b5caa jmp 0x6b57da
006b5caf cmp dword ptr [edi], 0
006b5cb2 jne 0x6b57da
006b5cb8 push 7
006b5cba lea ecx, [ebp - 0x6c]
006b5cbd mov dword ptr [edi], 1
006b5cc3 call 0x7a7d50
006b5cc8 test eax, eax
006b5cca jne 0x6b5cd2
006b5ccc mov dword ptr [edi], 2
006b5cd2 push 0x64
006b5cd4 lea ecx, [ebp - 0x6c]
006b5cd7 call 0x7a7d50
006b5cdc test eax, eax
006b5cde jne 0x6b5d15
006b5ce0 mov eax, dword ptr [0xbfd680]
006b5ce5 cmp byte ptr [eax + 0x12e], 0
006b5cec jne 0x6b5d0f
006b5cee cmp dword ptr [eax + 8], 2
006b5cf2 jne 0x6b5d15
006b5cf4 mov eax, dword ptr [0xbfd65c]
006b5cf9 test eax, eax
006b5cfb je 0x6b5d15
006b5cfd cmp dword ptr [eax + 0x1c3204], 0
006b5d04 ja 0x6b5d0f
006b5d06 cmp byte ptr [eax + 0x1c31a1], 0
006b5d0d je 0x6b5d15
006b5d0f mov dword ptr [edi], 4
006b5d15 push 0x32
006b5d17 lea ecx, [ebp - 0x6c]
006b5d1a call 0x7a7d50
006b5d1f test eax, eax
006b5d21 jne 0x6b5d2e
006b5d23 cmp dword ptr [edi], 4
006b5d26 sete al
006b5d29 add eax, 5
006b5d2c mov dword ptr [edi], eax
006b5d2e push 0xa
006b5d30 lea ecx, [ebp - 0x6c]
006b5d33 call 0x7a7d50
006b5d38 test eax, eax
006b5d3a jne 0x6b57da
006b5d40 cmp dword ptr [edi], 4
006b5d43 mov eax, 3
006b5d48 mov ecx, 6
006b5d4d cmove eax, ecx
006b5d50 mov dword ptr [edi], eax
006b5d52 jmp 0x6b57dd
006b5d57 cmp dword ptr [edi], 0
006b5d5a jne 0x6b5fbd
006b5d60 push 0x28
006b5d62 lea ecx, [ebp - 0x6c]
006b5d65 call 0x7a7d50
006b5d6a test eax, eax
006b5d6c jne 0x6b5d79
006b5d6e mov dword ptr [esi], 0x36
006b5d74 jmp 0x6b5f19
006b5d79 push 0x14
006b5d7b lea ecx, [ebp - 0x6c]
006b5d7e call 0x7a7d50
006b5d83 test eax, eax
006b5d85 jne 0x6b5d92
006b5d87 mov dword ptr [esi], 0x168
006b5d8d jmp 0x6b5f19
006b5d92 push 0x32
006b5d94 lea ecx, [ebp - 0x6c]
006b5d97 call 0x7a7d50
006b5d9c test eax, eax
006b5d9e jne 0x6b5dab
006b5da0 mov dword ptr [esi], 0x33
006b5da6 jmp 0x6b5f19
006b5dab push 0x50
006b5dad lea ecx, [ebp - 0x6c]
006b5db0 call 0x7a7d50
006b5db5 test eax, eax
006b5db7 jne 0x6b5dc4
006b5db9 mov dword ptr [esi], 0x34
006b5dbf jmp 0x6b5f19
006b5dc4 push 0x64
006b5dc6 lea ecx, [ebp - 0x6c]
006b5dc9 call 0x7a7d50
006b5dce lea ecx, [ebp - 0x6c]
006b5dd1 test eax, eax
006b5dd3 jne 0x6b5e37
006b5dd5 mov dword ptr [esi], 0x45
006b5ddb push 0x64
006b5ddd mov dword ptr [edi], 1
006b5de3 call 0x7a7d50
006b5de8 test eax, eax
006b5dea jne 0x6b57da
006b5df0 mov eax, dword ptr [0xbfd680]
006b5df5 cmp byte ptr [eax + 0x2a8], 0
006b5dfc jne 0x6b5e2c
006b5dfe cmp dword ptr [eax + 8], 2
006b5e02 jne 0x6b57dd
006b5e08 mov esi, dword ptr [0xbfd65c]
006b5e0e test esi, esi
006b5e10 je 0x6b57da
006b5e16 cmp dword ptr [esi + 0x1c3204], 0
006b5e1d ja 0x6b5e2c
006b5e1f cmp byte ptr [esi + 0x1c31a1], 0
006b5e26 je 0x6b57da
006b5e2c mov dword ptr [edi], 2
006b5e32 jmp 0x6b57da
006b5e37 push 0x50
006b5e39 call 0x7a7d50
006b5e3e test eax, eax
006b5e40 jne 0x6b5e91
006b5e42 mov eax, dword ptr [0xbfd680]
006b5e47 cmp byte ptr [eax + 0x2ad], 0
006b5e4e jne 0x6b5e83
006b5e50 cmp dword ptr [eax + 8], 2
006b5e54 jne 0x6b5e91
006b5e56 mov esi, dword ptr [0xbfd65c]
006b5e5c test esi, esi
006b5e5e je 0x6b5e8e
006b5e60 cmp dword ptr [esi + 0x1c3204], 0
006b5e67 ja 0x6b5e80
006b5e69 cmp byte ptr [esi + 0x1c31a1], 0
006b5e70 mov esi, dword ptr [ebp - 0x48]
006b5e73 je 0x6b5e91
006b5e75 mov dword ptr [esi], 0x38
006b5e7b jmp 0x6b5f19
006b5e80 mov esi, dword ptr [ebp - 0x48]
006b5e83 mov dword ptr [esi], 0x38
006b5e89 jmp 0x6b5f19
006b5e8e mov esi, dword ptr [ebp - 0x48]
006b5e91 push 0x28
006b5e93 lea ecx, [ebp - 0x6c]
006b5e96 call 0x7a7d50
006b5e9b test eax, eax
006b5e9d jne 0x6b5f19
006b5e9f mov esi, dword ptr [0xbfd65c]
006b5ea5 mov ecx, dword ptr [esi + 0x18190]
006b5eab call 0x444c30
006b5eb0 cmp eax, 2
006b5eb3 je 0x6b5f16
006b5eb5 mov ecx, dword ptr [esi + 0x18190]
006b5ebb call 0x444c30
006b5ec0 cmp eax, 3
006b5ec3 je 0x6b5f16
006b5ec5 mov ecx, dword ptr [esi + 0x18190]
006b5ecb call 0x444c30
006b5ed0 cmp eax, 7
006b5ed3 je 0x6b5f16
006b5ed5 mov ecx, dword ptr [esi + 0x18190]
006b5edb call 0x444c30
006b5ee0 cmp eax, 5
006b5ee3 je 0x6b5f16
006b5ee5 mov eax, dword ptr [0xbfd680]
006b5eea cmp byte ptr [eax + 0x2af], 0
006b5ef1 jne 0x6b5f0b
006b5ef3 cmp dword ptr [eax + 8], 2
006b5ef7 jne 0x6b5f16
006b5ef9 cmp dword ptr [esi + 0x1c3204], 0
006b5f00 ja 0x6b5f0b
006b5f02 cmp byte ptr [esi + 0x1c31a1], 0
006b5f09 je 0x6b5f16
006b5f0b mov esi, dword ptr [ebp - 0x48]
006b5f0e mov dword ptr [esi], 0x3a
006b5f14 jmp 0x6b5f19
006b5f16 mov esi, dword ptr [ebp - 0x48]
006b5f19 cmp dword ptr [edi], 0
006b5f1c jne 0x6b5fbd
006b5f22 push 0x640
006b5f27 lea ecx, [ebp - 0x6c]
006b5f2a call 0x7a7d50
006b5f2f test eax, eax
006b5f31 jne 0x6b5f39
006b5f33 mov dword ptr [esi], 0x35
006b5f39 cmp dword ptr [edi], 0
006b5f3c jne 0x6b5fbd
006b5f3e mov ecx, dword ptr [0xbfd65c]
006b5f44 push 1
006b5f46 push 0
006b5f48 push 0x3d
006b5f4a lea ecx, [ecx + 0x1ba40]
006b5f50 call 0x91d550
006b5f55 test eax, eax
006b5f57 je 0x6b5fbd
006b5f59 mov dword ptr [esi], 0x168
006b5f5f cmp dword ptr [edi], 0
006b5f62 jne 0x6b57da
006b5f68 mov ecx, dword ptr [0xbfd65c]
006b5f6e push 1
006b5f70 push 0
006b5f72 push 0x9f
006b5f77 lea ecx, [ecx + 0x1ba40]
006b5f7d call 0x91d550
006b5f82 test eax, eax
006b5f84 je 0x6b620f
006b5f8a mov ecx, dword ptr [0xbfd65c]
006b5f90 push 1
006b5f92 push 0
006b5f94 push 0x3d
006b5f96 lea ecx, [ecx + 0x1ba40]
006b5f9c call 0x91d550
006b5fa1 test eax, eax
006b5fa3 jne 0x6b620f
006b5fa9 cmp dword ptr [esi], 0x39
006b5fac je 0x6b620f
006b5fb2 mov dword ptr [esi], 0x3c
006b5fb8 jmp 0x6b6214
006b5fbd cmp dword ptr [esi], 0x34
006b5fc0 jne 0x6b5f5f
006b5fc2 mov ecx, dword ptr [0xbfd65c]
006b5fc8 push 1
006b5fca push 0
006b5fcc push 0x97
006b5fd1 lea ecx, [ecx + 0x1ba40]
006b5fd7 call 0x91d550
006b5fdc test eax, eax
006b5fde je 0x6b5f5f
006b5fe4 mov dword ptr [esi], 0x36
006b5fea jmp 0x6b5f5f
006b5fef cmp dword ptr [edi], 0
006b5ff2 jne 0x6b57da
006b5ff8 lea ecx, [ebp - 0x6c]
006b5ffb call 0x7a7e20
006b6000 mov ecx, dword ptr [0xbfd65c]
006b6006 push eax
006b6007 lea ecx, [ecx + 0x1a5cc]
006b600d call 0x702590
006b6012 mov dword ptr [edi], eax
006b6014 jmp 0x6b57dd
006b6019 cmp dword ptr [edi], 0
006b601c je 0x6b6063
006b601e mov ecx, dword ptr [0xbfd65c]
006b6024 push 1
006b6026 add ecx, 0x1ba40
006b602c push ecx
006b602d push 0x2d1
006b6032 call 0x91d340
006b6037 test eax, eax
006b6039 je 0x6b6057
006b603b cmp dword ptr [0xbfd658], 0
006b6042 jne 0x6b6057
006b6044 mov ecx, dword ptr [edi]
006b6046 call 0x6b1ad0
006b604b test al, al
006b604d jne 0x6b6057
006b604f mov dword ptr [edi], 0
006b6055 jmp 0x6b6060
006b6057 cmp dword ptr [edi], 0
006b605a jne 0x6b57da
006b6060 mov edx, dword ptr [ebp + 0xc]
006b6063 xor dl, 1
006b6066 lea ecx, [ebp - 0x6c]
006b6069 movzx eax, dl
006b606c push eax
006b606d call 0x7a7e20
006b6072 mov ecx, dword ptr [0xbfd65c]
006b6078 push eax
006b6079 mov ecx, dword ptr [ecx + 0x18190]
006b607f call 0x7aab40
006b6084 mov dword ptr [edi], eax
006b6086 jmp 0x6b57dd
006b608b mov dword ptr [edi], 0x226
006b6091 jmp 0x6b57dd
006b6096 cmp dword ptr [edi], 0
006b6099 jne 0x6b57da
006b609f lea ecx, [ebp - 0x6c]
006b60a2 mov dword ptr [edi], 1
006b60a8 call 0x7a7e20
006b60ad lea ecx, [ebp - 0x6c]
006b60b0 mov esi, eax
006b60b2 call 0x7a7e20
006b60b7 mov ecx, dword ptr [0xbfd680]
006b60bd mov edx, eax
006b60bf mov dword ptr [ebp - 0x98], edx
006b60c5 cmp byte ptr [ecx + 0x6d], 0
006b60c9 jne 0x6b60ed
006b60cb cmp dword ptr [ecx + 8], 2
006b60cf jne 0x6b6103
006b60d1 mov ecx, dword ptr [0xbfd65c]
006b60d7 test ecx, ecx
006b60d9 je 0x6b6103
006b60db cmp dword ptr [ecx + 0x1c3204], 0
006b60e2 ja 0x6b60ed
006b60e4 cmp byte ptr [ecx + 0x1c31a1], 0
006b60eb je 0x6b6103
006b60ed mov eax, 0xaaaaaaab
006b60f2 mul esi
006b60f4 shr edx, 1
006b60f6 lea eax, [edx + edx*2]
006b60f9 sub esi, eax
006b60fb jne 0x6b6111
006b60fd mov edx, dword ptr [ebp - 0x98]
006b6103 call 0x6cba20
006b6108 test al, al
006b610a je 0x6b6117
006b610c test dl, 1
006b610f jbe 0x6b6117
006b6111 mov dword ptr [edi], 2
006b6117 push 0x64
006b6119 lea ecx, [ebp - 0x6c]
006b611c call 0x7a7d50
006b6121 test eax, eax
006b6123 jne 0x6b6130
006b6125 mov dword ptr [edi], 3
006b612b jmp 0x6b57da
006b6130 push 0x78
006b6132 lea ecx, [ebp - 0x6c]
006b6135 call 0x7a7d50
006b613a test eax, eax
006b613c jne 0x6b57da
006b6142 mov eax, dword ptr [0xbfd680]
006b6147 cmp byte ptr [eax + 0x2b3], 0
006b614e jne 0x6b5909
006b6154 cmp dword ptr [eax + 8], 2
006b6158 jne 0x6b57da
006b615e mov esi, dword ptr [0xbfd65c]
006b6164 test esi, esi
006b6166 je 0x6b57da
006b616c cmp dword ptr [esi + 0x1c3204], 0
006b6173 ja 0x6b5909
006b6179 cmp byte ptr [esi + 0x1c31a1], 0
006b6180 je 0x6b57da
006b6186 mov dword ptr [edi], 4
006b618c jmp 0x6b57da
006b6191 cmp dword ptr [edi], 0
006b6194 jne 0x6b57da
006b619a lea ecx, [ebp - 0x6c]
006b619d jmp 0x6b5ddb
006b61a2 cmp dword ptr [edi], 0
006b61a5 jne 0x6b57da
006b61ab lea ecx, [ebp - 0x6c]
006b61ae call 0x7a7e20
006b61b3 push 1
006b61b5 push 0xa
006b61b7 push 0xa
006b61b9 mov esi, eax
006b61bb push 0x19
006b61bd push esi
006b61be call 0x701da0
006b61c3 movq xmm0, qword ptr [0xa08c44]
006b61cb mov ecx, dword ptr [0xa08c4c]
006b61d1 push 0
006b61d3 push 1
006b61d5 push 1
006b61d7 push eax
006b61d8 lea eax, [ebp - 0x30]
006b61db mov dword ptr [ebp - 0x30], esi
006b61de push eax
006b61df movq qword ptr [ebp - 0x2c], xmm0
006b61e4 mov dword ptr [ebp - 0x24], ecx
006b61e7 call 0x801c10
006b61ec mov dword ptr [edi], eax
006b61ee jmp 0x6b57da
006b61f3 sub eax, 0x154
006b61f8 cmp eax, 0x32
006b61fb ja 0x6b634c
006b6201 movzx eax, byte ptr [eax + 0x6b6bc4]
006b6208 jmp dword ptr [eax*4 + 0x6b6bb0]
006b620f cmp dword ptr [esi], 0x3c
006b6212 jne 0x6b626b
006b6214 push 0x78
006b6216 lea ecx, [ebp - 0x6c]
006b6219 call 0x7a7d50
006b621e test eax, eax
006b6220 jne 0x6b626b
006b6222 mov eax, dword ptr [0xbfd680]
006b6227 cmp byte ptr [eax + 0x2a5], 0
006b622e jne 0x6b6260
006b6230 cmp dword ptr [eax + 8], 2
006b6234 jne 0x6b626b
006b6236 mov esi, dword ptr [0xbfd65c]
006b623c test esi, esi
006b623e je 0x6b6268
006b6240 cmp dword ptr [esi + 0x1c3204], 0
006b6247 ja 0x6b625d
006b6249 cmp byte ptr [esi + 0x1c31a1], 0
006b6250 mov esi, dword ptr [ebp - 0x48]
006b6253 je 0x6b626b
006b6255 mov dword ptr [esi], 0x39
006b625b jmp 0x6b626b
006b625d mov esi, dword ptr [ebp - 0x48]
006b6260 mov dword ptr [esi], 0x39
006b6266 jmp 0x6b626b
006b6268 mov esi, dword ptr [ebp - 0x48]
006b626b cmp dword ptr [edi], 0
006b626e jne 0x6b57da
006b6274 mov ecx, dword ptr [esi]
006b6276 cmp ecx, 0x39
006b6279 jne 0x6b629b
006b627b push 4
006b627d lea ecx, [ebp - 0x6c]
006b6280 call 0x7a7d50
006b6285 push 4
006b6287 lea ecx, [ebp - 0x6c]
006b628a lea esi, [eax + 1]
006b628d call 0x7a7d50
006b6292 add eax, esi
006b6294 mov dword ptr [edi], eax
006b6296 jmp 0x6b57da
006b629b xor eax, eax
006b629d cmp ecx, 0x35
006b62a0 sete al
006b62a3 inc eax
006b62a4 mov dword ptr [edi], eax
006b62a6 jmp 0x6b57da
006b62ab cmp dword ptr [edi], 0
006b62ae jne 0x6b57da
006b62b4 mov dword ptr [edi], 1
006b62ba jmp 0x6b57dd
006b62bf cmp dword ptr [edi], 0
006b62c2 jne 0x6b57da
006b62c8 mov ecx, dword ptr [0xbfd65c]
006b62ce mov al, dl
006b62d0 xor al, 1
006b62d2 movzx eax, al
006b62d5 push eax
006b62d6 lea ecx, [ecx + 0x1a5cc]
006b62dc call 0x701880
006b62e1 mov dword ptr [edi], eax
006b62e3 test eax, eax
006b62e5 jne 0x6b57da
006b62eb lea ecx, [ebp - 0x6c]
006b62ee mov dword ptr [esi], 0x12c
006b62f4 call 0x7a7e20
006b62f9 push 1
006b62fb push 0xa
006b62fd push 0xa
006b62ff mov esi, eax
006b6301 push 0x19
006b6303 push esi
006b6304 call 0x701da0
006b6309 movq xmm0, qword ptr [0xa08c44]
006b6311 mov ecx, dword ptr [0xa08c4c]
006b6317 push 0
006b6319 push 1
006b631b push 1
006b631d push eax
006b631e lea eax, [ebp - 0x40]
006b6321 mov dword ptr [ebp - 0x40], esi
006b6324 push eax
006b6325 movq qword ptr [ebp - 0x3c], xmm0
006b632a mov dword ptr [ebp - 0x34], ecx
006b632d call 0x801c10
006b6332 cmp byte ptr [ebp - 0x59], 0
006b6336 mov dword ptr [edi], eax
006b6338 je 0x6b57da
006b633e mov esi, dword ptr [ebp - 0x48]
006b6341 mov dword ptr [esi], 0x46
006b6347 jmp 0x6b5ff8
006b634c push ecx
006b634d push 0xb495dc
006b6352 push 0
006b6354 call 0x95e330
006b6359 add esp, 0xc
006b635c jmp 0x6b57dd
006b6361 mov ecx, dword ptr [ebp - 0x48]
006b6364 mov edx, dword ptr [0xbfd658]
006b636a mov esi, dword ptr [0xbfd65c]
006b6370 cmp dword ptr [esi + 0x1c319c], 0x19
006b6377 jne 0x6b63bc
006b6379 cmp dword ptr [ecx], 0xa
006b637c jne 0x6b63bc
006b637e mov eax, dword ptr [edi]
006b6380 cmp eax, 1
006b6383 je 0x6b639e
006b6385 cmp eax, 2
006b6388 je 0x6b639e
006b638a cmp eax, 5
006b638d je 0x6b639e
006b638f cmp eax, 0xa
006b6392 je 0x6b639e
006b6394 cmp eax, 9
006b6397 je 0x6b639e
006b6399 cmp eax, 0xc
006b639c jne 0x6b63bc
006b639e mov dword ptr [ecx], 0x14
006b63a4 cmp dword ptr [edi], 1
006b63a7 jne 0x6b63b1
006b63a9 mov dword ptr [edi], 4
006b63af jmp 0x6b63bc
006b63b1 xor eax, eax
006b63b3 cmp dword ptr [edi], 5
006b63b6 sete al
006b63b9 inc eax
006b63ba mov dword ptr [edi], eax
006b63bc mov eax, dword ptr [esi + 0x1c319c]
006b63c2 cmp eax, 0x29
006b63c5 jne 0x6b64ad
006b63cb test edx, edx
006b63cd jne 0x6b648b
006b63d3 cmp dword ptr [ecx], 0x64
006b63d6 jne 0x6b648b
006b63dc mov ecx, dword ptr [edi]
006b63de call 0x6b1ad0
006b63e3 test al, al
006b63e5 mov eax, dword ptr [ebp - 0x48]
006b63e8 jne 0x6b648e
006b63ee mov dword ptr [eax], 0x15e
006b63f4 lea ecx, [esi + 0x1a5cc]
006b63fa mov al, byte ptr [ebp + 0xc]
006b63fd xor al, 1
006b63ff movzx eax, al
006b6402 push eax
006b6403 call 0x701880
006b6408 mov dword ptr [edi], eax
006b640a test eax, eax
006b640c jne 0x6b6485
006b640e mov eax, dword ptr [ebp - 0x48]
006b6411 lea ecx, [ebp - 0x6c]
006b6414 mov dword ptr [eax], 0x12c
006b641a call 0x7a7e20
006b641f push 1
006b6421 push 0xa
006b6423 push 0xa
006b6425 mov esi, eax
006b6427 push 0x19
006b6429 push esi
006b642a call 0x701da0
006b642f movq xmm0, qword ptr [0xa08c44]
006b6437 mov ecx, dword ptr [0xa08c4c]
006b643d push 0
006b643f push 1
006b6441 push 1
006b6443 push eax
006b6444 lea eax, [ebp - 0x20]
006b6447 mov dword ptr [ebp - 0x20], esi
006b644a push eax
006b644b movq qword ptr [ebp - 0x1c], xmm0
006b6450 mov dword ptr [ebp - 0x14], ecx
006b6453 call 0x801c10
006b6458 cmp byte ptr [ebp - 0x59], 0
006b645c mov dword ptr [edi], eax
006b645e je 0x6b6485
006b6460 mov eax, dword ptr [ebp - 0x48]
006b6463 lea ecx, [ebp - 0x6c]
006b6466 mov dword ptr [eax], 0x46
006b646c call 0x7a7e20
006b6471 mov ecx, dword ptr [0xbfd65c]
006b6477 push eax
006b6478 add ecx, 0x1a5cc
006b647e call 0x702590
006b6483 mov dword ptr [edi], eax
006b6485 mov esi, dword ptr [0xbfd65c]
006b648b mov eax, dword ptr [ebp - 0x48]
006b648e cmp dword ptr [esi + 0x1c319c], 0x2b
006b6495 jne 0x6b64eb
006b6497 mov ecx, dword ptr [eax]
006b6499 cmp ecx, 0x12c
006b649f je 0x6b64d7
006b64a1 cmp ecx, 0x46
006b64a4 je 0x6b64e5
006b64a6 cmp ecx, 0x5a
006b64a9 jne 0x6b64eb
006b64ab jmp 0x6b64e5
006b64ad cmp eax, 0x2b
006b64b0 jne 0x6b648b
006b64b2 test edx, edx
006b64b4 jne 0x6b648b
006b64b6 cmp dword ptr [ecx], 0x64
006b64b9 jne 0x6b648b
006b64bb mov ecx, dword ptr [edi]
006b64bd call 0x6b1ad0
006b64c2 test al, al
006b64c4 mov eax, dword ptr [ebp - 0x48]
006b64c7 jne 0x6b648e
006b64c9 mov dword ptr [eax], 0x12c
006b64cf mov dword ptr [edi], 0
006b64d5 jmp 0x6b648e
006b64d7 test dword ptr [edi], 0x8000
006b64dd jne 0x6b64e5
006b64df mov dword ptr [edi], 0
006b64e5 mov dword ptr [eax], 0x12c
006b64eb mov eax, dword ptr [eax]
006b64ed cmp eax, 0x28
006b64f0 jne 0x6b6534
006b64f2 push ecx
006b64f3 lea ecx, [esi + 0x1ba40]
006b64f9 call 0x91d900
006b64fe test al, al
006b6500 je 0x6b6982
006b6506 mov eax, dword ptr [edi]
006b6508 cmp eax, 3
006b650b je 0x6b6982
006b6511 cmp eax, 5
006b6514 je 0x6b6982
006b651a cmp eax, 6
006b651d je 0x6b6982
006b6523 mov eax, dword ptr [ebp - 0x48]
006b6526 mov dword ptr [eax], 0x2a
006b652c mov dword ptr [edi], 1
006b6532 mov eax, dword ptr [eax]
006b6534 cmp eax, 0x14
006b6537 je 0x6b6542
006b6539 cmp eax, 0x1e
006b653c jne 0x6b6982
006b6542 mov eax, dword ptr [esi + 0x243624]
006b6548 cmp eax, 2
006b654b je 0x6b6982
006b6551 cmp eax, 3
006b6554 je 0x6b6982
006b655a cmp dword ptr [esi], 6
006b655d jle 0x6b6982
006b6563 cmp dword ptr [0xbfd658], 0
006b656a jne 0x6b6982
006b6570 cmp dword ptr [0xc038f8], 2
006b6577 jge 0x6b6982
006b657d push 1
006b657f push 0
006b6581 lea ecx, [esi + 0x1ba40]
006b6587 push 0xa5
006b658c call 0x91d550
006b6591 test eax, eax
006b6593 je 0x6b697c
006b6599 xor eax, eax
006b659b xor ecx, ecx
006b659d mov dword ptr [ebp - 0x78], eax
006b65a0 mov dword ptr [ebp - 0x74], ecx
006b65a3 mov dword ptr [ebp - 0x70], eax
006b65a6 mov esi, dword ptr [ebp - 0x48]
006b65a9 mov dword ptr [ebp - 4], 3
006b65b0 cmp dword ptr [esi], 0x14
006b65b3 jne 0x6b65db
006b65b5 lea eax, [ebp - 0xa8]
006b65bb mov dword ptr [ebp - 0xa8], ecx
006b65c1 push eax
006b65c2 push ecx
006b65c3 lea ecx, [ebp - 0x78]
006b65c6 mov dword ptr [ebp - 0xa4], 8
006b65d0 call 0x48d900
006b65d5 mov ecx, dword ptr [ebp - 0x74]
006b65d8 mov eax, dword ptr [ebp - 0x78]
006b65db mov dword ptr [ebp - 0x44], ecx
006b65de xor edx, edx
006b65e0 sub dword ptr [ebp - 0x44], eax
006b65e3 sar dword ptr [ebp - 0x44], 3
006b65e7 cmp dword ptr [ebp - 0x44], edx
006b65ea jbe 0x6b65fc
006b65ec nop dword ptr [eax]
006b65f0 cmp dword ptr [eax + edx*8], 0x28
006b65f4 je 0x6b662a
006b65f6 inc edx
006b65f7 cmp edx, dword ptr [ebp - 0x44]
006b65fa jb 0x6b65f0
006b65fc mov dword ptr [ebp - 0xf8], 0x28
006b6606 mov dword ptr [ebp - 0xf4], 8
006b6610 cmp ecx, dword ptr [ebp - 0x70]
006b6613 je 0x6b663b
006b6615 mov dword ptr [ecx], 0x28
006b661b mov dword ptr [ecx + 4], 8
006b6622 add ecx, 8
006b6625 mov dword ptr [ebp - 0x74], ecx
006b6628 jmp 0x6b6651
006b662a add dword ptr [eax + edx*8 + 4], 8
006b662f jns 0x6b6651
006b6631 mov dword ptr [eax + edx*8 + 4], 0
006b6639 jmp 0x6b6651
006b663b lea eax, [ebp - 0xf8]
006b6641 push eax
006b6642 push ecx
006b6643 lea ecx, [ebp - 0x78]
006b6646 call 0x48d900
006b664b mov ecx, dword ptr [ebp - 0x74]
006b664e mov eax, dword ptr [ebp - 0x78]
006b6651 mov dword ptr [ebp - 0x44], ecx
006b6654 xor edx, edx
006b6656 sub dword ptr [ebp - 0x44], eax
006b6659 sar dword ptr [ebp - 0x44], 3
006b665d cmp dword ptr [ebp - 0x44], edx
006b6660 jbe 0x6b666e
006b6662 cmp dword ptr [eax + edx*8], 0xa
006b6666 je 0x6b669c
006b6668 inc edx
006b6669 cmp edx, dword ptr [ebp - 0x44]
006b666c jb 0x6b6662
006b666e mov dword ptr [ebp - 0x100], 0xa
006b6678 mov dword ptr [ebp - 0xfc], 8
006b6682 cmp ecx, dword ptr [ebp - 0x70]
006b6685 je 0x6b66ad
006b6687 mov dword ptr [ecx], 0xa
006b668d mov dword ptr [ecx + 4], 8
006b6694 add ecx, 8
006b6697 mov dword ptr [ebp - 0x74], ecx
006b669a jmp 0x6b66c3
006b669c add dword ptr [eax + edx*8 + 4], 8
006b66a1 jns 0x6b66c3
006b66a3 mov dword ptr [eax + edx*8 + 4], 0
006b66ab jmp 0x6b66c3
006b66ad lea eax, [ebp - 0x100]
006b66b3 push eax
006b66b4 push ecx
006b66b5 lea ecx, [ebp - 0x78]
006b66b8 call 0x48d900
006b66bd mov ecx, dword ptr [ebp - 0x74]
006b66c0 mov eax, dword ptr [ebp - 0x78]
006b66c3 mov dword ptr [ebp - 0x44], ecx
006b66c6 xor edx, edx
006b66c8 sub dword ptr [ebp - 0x44], eax
006b66cb sar dword ptr [ebp - 0x44], 3
006b66cf cmp dword ptr [ebp - 0x44], edx
006b66d2 jbe 0x6b66e0
006b66d4 cmp dword ptr [eax + edx*8], 0x46
006b66d8 je 0x6b670e
006b66da inc edx
006b66db cmp edx, dword ptr [ebp - 0x44]
006b66de jb 0x6b66d4
006b66e0 mov dword ptr [ebp - 0x108], 0x46
006b66ea mov dword ptr [ebp - 0x104], 5
006b66f4 cmp ecx, dword ptr [ebp - 0x70]
006b66f7 je 0x6b671f
006b66f9 mov dword ptr [ecx], 0x46
006b66ff mov dword ptr [ecx + 4], 5
006b6706 add ecx, 8
006b6709 mov dword ptr [ebp - 0x74], ecx
006b670c jmp 0x6b6735
006b670e add dword ptr [eax + edx*8 + 4], 5
006b6713 jns 0x6b6735
006b6715 mov dword ptr [eax + edx*8 + 4], 0
006b671d jmp 0x6b6735
006b671f lea eax, [ebp - 0x108]
006b6725 push eax
006b6726 push ecx
006b6727 lea ecx, [ebp - 0x78]
006b672a call 0x48d900
006b672f mov ecx, dword ptr [ebp - 0x74]
006b6732 mov eax, dword ptr [ebp - 0x78]
006b6735 mov dword ptr [ebp - 0x44], ecx
006b6738 xor edx, edx
006b673a sub dword ptr [ebp - 0x44], eax
006b673d sar dword ptr [ebp - 0x44], 3
006b6741 cmp dword ptr [ebp - 0x44], edx
006b6744 jbe 0x6b6755
006b6746 cmp dword ptr [eax + edx*8], 0x12c
006b674d je 0x6b6783
006b674f inc edx
006b6750 cmp edx, dword ptr [ebp - 0x44]
006b6753 jb 0x6b6746
006b6755 mov dword ptr [ebp - 0x110], 0x12c
006b675f mov dword ptr [ebp - 0x10c], 5
006b6769 cmp ecx, dword ptr [ebp - 0x70]
006b676c je 0x6b6794
006b676e mov dword ptr [ecx], 0x12c
006b6774 mov dword ptr [ecx + 4], 5
006b677b add ecx, 8
006b677e mov dword ptr [ebp - 0x74], ecx
006b6781 jmp 0x6b67aa
006b6783 add dword ptr [eax + edx*8 + 4], 5
006b6788 jns 0x6b67aa
006b678a mov dword ptr [eax + edx*8 + 4], 0
006b6792 jmp 0x6b67aa
006b6794 lea eax, [ebp - 0x110]
006b679a push eax
006b679b push ecx
006b679c lea ecx, [ebp - 0x78]
006b679f call 0x48d900
006b67a4 mov ecx, dword ptr [ebp - 0x74]
006b67a7 mov eax, dword ptr [ebp - 0x78]
006b67aa mov dword ptr [ebp - 0x44], ecx
006b67ad xor edx, edx
006b67af sub dword ptr [ebp - 0x44], eax
006b67b2 sar dword ptr [ebp - 0x44], 3
006b67b6 cmp dword ptr [ebp - 0x44], edx
006b67b9 jbe 0x6b67cf
006b67bb nop dword ptr [eax + eax]
006b67c0 cmp dword ptr [eax + edx*8], 0x15e
006b67c7 je 0x6b67fd
006b67c9 inc edx
006b67ca cmp edx, dword ptr [ebp - 0x44]
006b67cd jb 0x6b67c0
006b67cf mov dword ptr [ebp - 0x118], 0x15e
006b67d9 mov dword ptr [ebp - 0x114], 2
006b67e3 cmp ecx, dword ptr [ebp - 0x70]
006b67e6 je 0x6b680e
006b67e8 mov dword ptr [ecx], 0x15e
006b67ee mov dword ptr [ecx + 4], 2
006b67f5 add ecx, 8
006b67f8 mov dword ptr [ebp - 0x74], ecx
006b67fb jmp 0x6b6824
006b67fd add dword ptr [eax + edx*8 + 4], 2
006b6802 jns 0x6b6824
006b6804 mov dword ptr [eax + edx*8 + 4], 0
006b680c jmp 0x6b6824
006b680e lea eax, [ebp - 0x118]
006b6814 push eax
006b6815 push ecx
006b6816 lea ecx, [ebp - 0x78]
006b6819 call 0x48d900
006b681e mov ecx, dword ptr [ebp - 0x74]
006b6821 mov eax, dword ptr [ebp - 0x78]
006b6824 mov dword ptr [ebp - 0x44], ecx
006b6827 xor edx, edx
006b6829 sub dword ptr [ebp - 0x44], eax
006b682c sar dword ptr [ebp - 0x44], 3
006b6830 cmp dword ptr [ebp - 0x44], edx
006b6833 jbe 0x6b6841
006b6835 cmp dword ptr [eax + edx*8], 0x5a
006b6839 je 0x6b686f
006b683b inc edx
006b683c cmp edx, dword ptr [ebp - 0x44]
006b683f jb 0x6b6835
006b6841 mov dword ptr [ebp - 0x120], 0x5a
006b684b mov dword ptr [ebp - 0x11c], 2
006b6855 cmp ecx, dword ptr [ebp - 0x70]
006b6858 je 0x6b6880
006b685a mov dword ptr [ecx], 0x5a
006b6860 mov dword ptr [ecx + 4], 2
006b6867 add ecx, 8
006b686a mov dword ptr [ebp - 0x74], ecx
006b686d jmp 0x6b6890
006b686f add dword ptr [eax + edx*8 + 4], 2
006b6874 jns 0x6b6890
006b6876 mov dword ptr [eax + edx*8 + 4], 0
006b687e jmp 0x6b6890
006b6880 lea eax, [ebp - 0x120]
006b6886 push eax
006b6887 push ecx
006b6888 lea ecx, [ebp - 0x78]
006b688b call 0x48d900
006b6890 lea ecx, [ebp - 0x6c]
006b6893 call 0x7a7e20
006b6898 movq xmm0, qword ptr [0xa08c44]
006b68a0 sub esp, 0x10
006b68a3 mov ecx, esp
006b68a5 mov dword ptr [ecx], eax
006b68a7 mov eax, dword ptr [0xa08c4c]
006b68ac movq qword ptr [ecx + 4], xmm0
006b68b1 mov dword ptr [ecx + 0xc], eax
006b68b4 lea ecx, [ebp - 0x78]
006b68b7 call 0x489420
006b68bc mov dword ptr [esi], eax
006b68be test eax, eax
006b68c0 mov eax, dword ptr [ebp + 0x10]
006b68c3 jne 0x6b690f
006b68c5 test al, al
006b68c7 jne 0x6b692e
006b68c9 dec dword ptr [0xc038f8]
006b68cf mov edx, dword ptr [ebp - 0x78]
006b68d2 mov dword ptr [esi], 0xffffffff
006b68d8 test edx, edx
006b68da je 0x6b6908
006b68dc mov ecx, dword ptr [ebp - 0x70]
006b68df mov eax, edx
006b68e1 sub ecx, edx
006b68e3 and ecx, 0xfffffff8
006b68e6 cmp ecx, 0x1000
006b68ec jb 0x6b68fe
006b68ee mov edx, dword ptr [edx - 4]
006b68f1 add ecx, 0x23
006b68f4 sub eax, edx
006b68f6 add eax, -4
006b68f9 cmp eax, 0x1f
006b68fc ja 0x6b6957
006b68fe push ecx
006b68ff push edx
006b6900 call 0x9eb08e
006b6905 add esp, 8
006b6908 xor al, al
006b690a jmp 0x6b6a61
006b690f push eax
006b6910 push dword ptr [ebp + 0xc]
006b6913 lea ecx, [ebp - 0x6c]
006b6916 mov dword ptr [edi], 0
006b691c push edi
006b691d call 0x7a7e20
006b6922 mov edx, esi
006b6924 mov ecx, eax
006b6926 call 0x6b48b0
006b692b add esp, 0xc
006b692e mov edx, dword ptr [ebp - 0x78]
006b6931 test edx, edx
006b6933 je 0x6b697c
006b6935 mov ecx, dword ptr [ebp - 0x70]
006b6938 mov eax, edx
006b693a sub ecx, edx
006b693c and ecx, 0xfffffff8
006b693f cmp ecx, 0x1000
006b6945 jb 0x6b695d
006b6947 mov edx, dword ptr [edx - 4]
006b694a add ecx, 0x23
006b694d sub eax, edx
006b694f add eax, -4
006b6952 cmp eax, 0x1f
006b6955 jbe 0x6b695d
006b6957 call dword ptr [0xa065ac]
006b695d push ecx
006b695e push edx
006b695f call 0x9eb08e
006b6964 add esp, 8
006b6967 mov dword ptr [ebp - 0x78], 0
006b696e mov dword ptr [ebp - 0x74], 0
006b6975 mov dword ptr [ebp - 0x70], 0
006b697c mov esi, dword ptr [0xbfd65c]
006b6982 cmp byte ptr [ebp + 0x10], 0
006b6986 je 0x6b6a59
006b698c mov eax, dword ptr [esi + 0x1ba54]
006b6992 xor edx, edx
006b6994 sub eax, dword ptr [esi + 0x1ba50]
006b699a sar eax, 2
006b699d mov dword ptr [ebp - 0x44], edx
006b69a0 test eax, eax
006b69a2 je 0x6b6a30
006b69a8 nop dword ptr [eax + eax]
006b69b0 mov ecx, dword ptr [esi + 0x1ba54]
006b69b6 lea eax, [esi + 0x1ba50]
006b69bc mov dword ptr [ebp - 0x7c], eax
006b69bf mov eax, ecx
006b69c1 mov edx, dword ptr [ebp - 0x7c]
006b69c4 sub eax, dword ptr [edx]
006b69c6 mov edx, dword ptr [ebp - 0x44]
006b69c9 test eax, 0xfffffffc
006b69ce jne 0x6b69f0
006b69d0 push 0xb3f4d0
006b69d5 push 3
006b69d7 call 0x95e330
006b69dc mov eax, dword ptr [ebp - 0x7c]
006b69df add esp, 8
006b69e2 mov esi, dword ptr [0xbfd65c]
006b69e8 mov edx, dword ptr [ebp - 0x44]
006b69eb mov ecx, dword ptr [eax + 4]
006b69ee jmp 0x6b69f3
006b69f0 mov eax, dword ptr [ebp - 0x7c]
006b69f3 mov eax, dword ptr [eax]
006b69f5 sub ecx, eax
006b69f7 sar ecx, 2
006b69fa cmp edx, ecx
006b69fc jae 0x6b6a01
006b69fe lea eax, [eax + edx*4]
006b6a01 mov eax, dword ptr [eax]
006b6a03 cmp dword ptr [eax + 0x2c], 0
006b6a07 jne 0x6b6a19
006b6a09 mov eax, dword ptr [eax + 0x130c]
006b6a0f cmp eax, 0xe
006b6a12 je 0x6b6a19
006b6a14 cmp eax, 0x21
006b6a17 jne 0x6b6a59
006b6a19 mov eax, dword ptr [esi + 0x1ba54]
006b6a1f inc edx
006b6a20 sub eax, dword ptr [esi + 0x1ba50]
006b6a26 sar eax, 2
006b6a29 mov dword ptr [ebp - 0x44], edx
006b6a2c cmp edx, eax
006b6a2e jb 0x6b69b0
006b6a30 mov esi, dword ptr [ebp - 0x48]
006b6a33 cmp dword ptr [esi], 0xa
006b6a36 jne 0x6b6a59
006b6a38 lea ecx, [ebp - 0x6c]
006b6a3b call 0x7a7e20
006b6a40 test byte ptr [ebp - 0x6c], 1
006b6a44 mov eax, 0x28
006b6a49 mov ecx, 0x1e
006b6a4e cmove eax, ecx
006b6a51 mov dword ptr [esi], eax
006b6a53 mov dword ptr [edi], 1
006b6a59 dec dword ptr [0xc038f8]
006b6a5f mov al, 1
006b6a61 mov ecx, dword ptr [ebp - 0xc]
006b6a64 mov dword ptr fs:[0], ecx
006b6a6b pop ecx
006b6a6c pop edi
006b6a6d pop esi
006b6a6e mov ecx, dword ptr [ebp - 0x10]
006b6a71 xor ecx, ebp
006b6a73 call 0x9eacd7
006b6a78 mov esp, ebp
006b6a7a pop ebp
006b6a7b ret 
