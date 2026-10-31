008d6950 mov eax, dword ptr [ecx + 0x160]
008d6956 and eax, 0x200000
008d695b or eax, 0
008d695e jne 0x8d696b
008d6960 cmp byte ptr [ecx + 0x3ac], al
008d6966 jne 0x8d696b
008d6968 mov al, 1
008d696a ret 
008d696b xor al, al
008d696d ret 
008d696e int3 
008d696f int3 
008d6970 push ebp
008d6971 mov ebp, esp
008d6973 push ecx
008d6974 push ebx
008d6975 push esi
008d6976 push edi
008d6977 mov edi, ecx
008d6979 call 0x684950
008d697e lea esi, [edi + 0x448]
008d6984 mov ebx, 2
008d6989 nop dword ptr [eax]
008d6990 cmp byte ptr [edi + 0x16f], 0
008d6997 je 0x8d69ab
008d6999 mov ecx, dword ptr [esi]
008d699b test ecx, ecx
008d699d je 0x8d69ab
008d699f mov eax, dword ptr [ecx]
008d69a1 call dword ptr [eax + 0x28]
008d69a4 mov ecx, dword ptr [esi]
008d69a6 mov eax, dword ptr [ecx]
008d69a8 call dword ptr [eax + 0x40]
008d69ab mov ecx, dword ptr [esi]
008d69ad test ecx, ecx
008d69af je 0x8d69c3
008d69b1 lea eax, [ebp - 4]
008d69b4 mov dword ptr [ebp - 4], esi
008d69b7 push eax
008d69b8 add ecx, 0x324
008d69be call 0x4bc3c0
008d69c3 mov dword ptr [esi], 0
008d69c9 add esi, 4
008d69cc sub ebx, 1
008d69cf jne 0x8d6990
008d69d1 lea esi, [edi + 0x454]
008d69d7 mov ebx, 4
008d69dc nop dword ptr [eax]
008d69e0 cmp byte ptr [edi + 0x16f], 0
008d69e7 je 0x8d69fb
008d69e9 mov ecx, dword ptr [esi]
008d69eb test ecx, ecx
008d69ed je 0x8d69fb
008d69ef mov eax, dword ptr [ecx]
008d69f1 call dword ptr [eax + 0x28]
008d69f4 mov ecx, dword ptr [esi]
008d69f6 mov eax, dword ptr [ecx]
008d69f8 call dword ptr [eax + 0x40]
008d69fb mov ecx, dword ptr [esi]
008d69fd test ecx, ecx
008d69ff je 0x8d6a13
008d6a01 lea eax, [ebp - 4]
008d6a04 mov dword ptr [ebp - 4], esi
008d6a07 push eax
008d6a08 add ecx, 0x324
008d6a0e call 0x4bc3c0
008d6a13 mov dword ptr [esi], 0
008d6a19 add esi, 4
008d6a1c sub ebx, 1
008d6a1f jne 0x8d69e0
008d6a21 cmp byte ptr [edi + 0x16f], bl
008d6a27 je 0x8d6a43
008d6a29 mov ecx, dword ptr [edi + 0x438]
008d6a2f test ecx, ecx
008d6a31 je 0x8d6a43
008d6a33 mov eax, dword ptr [ecx]
008d6a35 call dword ptr [eax + 0x28]
008d6a38 mov ecx, dword ptr [edi + 0x438]
008d6a3e mov eax, dword ptr [ecx]
008d6a40 call dword ptr [eax + 0x40]
008d6a43 mov ecx, dword ptr [edi + 0x438]
008d6a49 lea esi, [edi + 0x438]
008d6a4f test ecx, ecx
008d6a51 je 0x8d6a65
008d6a53 lea eax, [ebp - 4]
008d6a56 mov dword ptr [ebp - 4], esi
008d6a59 push eax
008d6a5a add ecx, 0x324
008d6a60 call 0x4bc3c0
008d6a65 mov dword ptr [esi], 0
008d6a6b cmp byte ptr [edi + 0x16f], 0
008d6a72 je 0x8d6a8e
008d6a74 mov ecx, dword ptr [edi + 0x43c]
008d6a7a test ecx, ecx
008d6a7c je 0x8d6a8e
008d6a7e mov eax, dword ptr [ecx]
008d6a80 call dword ptr [eax + 0x28]
008d6a83 mov ecx, dword ptr [edi + 0x43c]
008d6a89 mov eax, dword ptr [ecx]
008d6a8b call dword ptr [eax + 0x40]
008d6a8e mov ecx, dword ptr [edi + 0x43c]
008d6a94 lea esi, [edi + 0x43c]
008d6a9a test ecx, ecx
008d6a9c je 0x8d6ab0
008d6a9e lea eax, [ebp - 4]
008d6aa1 mov dword ptr [ebp - 4], esi
008d6aa4 push eax
008d6aa5 add ecx, 0x324
008d6aab call 0x4bc3c0
008d6ab0 mov dword ptr [esi], 0
008d6ab6 lea esi, [edi + 0x47c]
008d6abc mov ecx, dword ptr [esi]
008d6abe test ecx, ecx
008d6ac0 je 0x8d6ada
008d6ac2 lea eax, [ebp - 4]
008d6ac5 mov dword ptr [ebp - 4], esi
008d6ac8 push eax
008d6ac9 add ecx, 0x324
008d6acf call 0x4bc3c0
008d6ad4 mov dword ptr [esi], 0
008d6ada lea esi, [edi + 0x480]
008d6ae0 mov ebx, 2
008d6ae5 cmp byte ptr [edi + 0x16f], 0
008d6aec je 0x8d6b00
008d6aee mov ecx, dword ptr [esi]
008d6af0 test ecx, ecx
008d6af2 je 0x8d6b00
008d6af4 mov eax, dword ptr [ecx]
008d6af6 call dword ptr [eax + 0x28]
008d6af9 mov ecx, dword ptr [esi]
008d6afb mov eax, dword ptr [ecx]
008d6afd call dword ptr [eax + 0x40]
008d6b00 mov ecx, dword ptr [esi]
008d6b02 test ecx, ecx
008d6b04 je 0x8d6b1e
008d6b06 lea eax, [ebp - 4]
008d6b09 mov dword ptr [ebp - 4], esi
008d6b0c push eax
008d6b0d add ecx, 0x324
008d6b13 call 0x4bc3c0
008d6b18 mov dword ptr [esi], 0
008d6b1e add esi, 4
008d6b21 sub ebx, 1
008d6b24 jne 0x8d6ae5
008d6b26 cmp byte ptr [edi + 0x16f], bl
008d6b2c je 0x8d6b48
008d6b2e mov ecx, dword ptr [edi + 0x488]
008d6b34 test ecx, ecx
008d6b36 je 0x8d6b48
008d6b38 mov eax, dword ptr [ecx]
008d6b3a call dword ptr [eax + 0x28]
008d6b3d mov ecx, dword ptr [edi + 0x488]
008d6b43 mov eax, dword ptr [ecx]
008d6b45 call dword ptr [eax + 0x40]
008d6b48 mov ecx, dword ptr [edi + 0x488]
008d6b4e lea esi, [edi + 0x488]
008d6b54 test ecx, ecx
008d6b56 je 0x8d6b70
008d6b58 lea eax, [ebp - 4]
008d6b5b mov dword ptr [ebp - 4], esi
008d6b5e push eax
008d6b5f add ecx, 0x324
008d6b65 call 0x4bc3c0
008d6b6a mov dword ptr [esi], 0
008d6b70 mov ecx, dword ptr [edi + 0x48c]
008d6b76 add edi, 0x48c
008d6b7c test ecx, ecx
008d6b7e je 0x8d6b98
008d6b80 lea eax, [ebp - 4]
008d6b83 mov dword ptr [ebp - 4], edi
008d6b86 push eax
008d6b87 add ecx, 0x324
008d6b8d call 0x4bc3c0
008d6b92 mov dword ptr [edi], 0
008d6b98 pop edi
008d6b99 pop esi
008d6b9a pop ebx
008d6b9b mov esp, ebp
008d6b9d pop ebp
008d6b9e ret 
008d6b9f int3 
008d6ba0 push ebx
008d6ba1 push esi
008d6ba2 push edi
008d6ba3 mov ebx, ecx
008d6ba5 call 0x6848f0
008d6baa lea esi, [ebx + 0x448]
008d6bb0 mov edi, 2
008d6bb5 mov ecx, dword ptr [esi]
008d6bb7 test ecx, ecx
008d6bb9 je 0x8d6bc9
008d6bbb cmp byte ptr [ecx + 0x16a], 0
008d6bc2 je 0x8d6bc9
008d6bc4 mov eax, dword ptr [ecx]
008d6bc6 call dword ptr [eax + 0x28]
008d6bc9 add esi, 4
008d6bcc sub edi, 1
008d6bcf jne 0x8d6bb5
008d6bd1 lea esi, [ebx + 0x454]
008d6bd7 mov edi, 4
008d6bdc nop dword ptr [eax]
008d6be0 mov ecx, dword ptr [esi]
008d6be2 test ecx, ecx
008d6be4 je 0x8d6bf4
008d6be6 cmp byte ptr [ecx + 0x16a], 0
008d6bed je 0x8d6bf4
008d6bef mov eax, dword ptr [ecx]
008d6bf1 call dword ptr [eax + 0x28]
008d6bf4 add esi, 4
008d6bf7 sub edi, 1
008d6bfa jne 0x8d6be0
008d6bfc cmp byte ptr [ebx + 0x465], 0
008d6c03 jne 0x8d6c74
008d6c05 mov ecx, dword ptr [ebx + 0x438]
008d6c0b test ecx, ecx
008d6c0d je 0x8d6c1d
008d6c0f cmp byte ptr [ecx + 0x16a], 0
008d6c16 je 0x8d6c1d
008d6c18 mov eax, dword ptr [ecx]
008d6c1a call dword ptr [eax + 0x28]
008d6c1d mov ecx, dword ptr [ebx + 0x43c]
008d6c23 test ecx, ecx
008d6c25 je 0x8d6c35
008d6c27 cmp byte ptr [ecx + 0x16a], 0
008d6c2e je 0x8d6c35
008d6c30 mov eax, dword ptr [ecx]
008d6c32 call dword ptr [eax + 0x28]
008d6c35 lea esi, [ebx + 0x480]
008d6c3b mov edi, 2
008d6c40 mov ecx, dword ptr [esi]
008d6c42 test ecx, ecx
008d6c44 je 0x8d6c54
008d6c46 cmp byte ptr [ecx + 0x16a], 0
008d6c4d je 0x8d6c54
008d6c4f mov eax, dword ptr [ecx]
008d6c51 call dword ptr [eax + 0x28]
008d6c54 add esi, 4
008d6c57 sub edi, 1
008d6c5a jne 0x8d6c40
008d6c5c mov ecx, dword ptr [ebx + 0x488]
008d6c62 test ecx, ecx
008d6c64 je 0x8d6c74
008d6c66 cmp byte ptr [ecx + 0x16a], 0
008d6c6d je 0x8d6c74
008d6c6f mov eax, dword ptr [ecx]
008d6c71 call dword ptr [eax + 0x28]
008d6c74 mov ecx, dword ptr [ebx + 0x318]
008d6c7a pop edi
008d6c7b pop esi
008d6c7c pop ebx
008d6c7d test ecx, ecx
008d6c7f je 0x8d6c8f
008d6c81 cmp byte ptr [ecx + 0x16a], 0
008d6c88 je 0x8d6c8f
008d6c8a mov eax, dword ptr [ecx]
008d6c8c jmp dword ptr [eax + 0x28]
008d6c8f ret 
008d6c90 push ebp
008d6c91 mov ebp, esp
008d6c93 and esp, 0xfffffff8
008d6c96 sub esp, 0x70
008d6c99 push esi
008d6c9a push edi
008d6c9b mov edi, ecx
008d6c9d cmp byte ptr [edi + 0x16e], 0
008d6ca4 je 0x8d6cae
008d6ca6 lea ecx, [edi + 0x3c]
008d6ca9 call 0x406dd0
008d6cae mov eax, dword ptr [0xbfd65c]
008d6cb3 mov eax, dword ptr [eax + 0x1c3164]
008d6cb9 shr eax, 5
008d6cbc test al, 1
008d6cbe je 0x8d791b
008d6cc4 movss xmm0, dword ptr [edi + 0x2c8]
008d6ccc comiss xmm0, dword ptr [0xb6a18c]
008d6cd3 jbe 0x8d791b
008d6cd9 cmp dword ptr [edi + 0x180], 0
008d6ce0 je 0x8d791b
008d6ce6 cmp byte ptr [edi + 0x3ad], 0
008d6ced jl 0x8d791b
008d6cf3 mov eax, dword ptr fs:[0x2c]
008d6cf9 mov ecx, dword ptr [eax]
008d6cfb mov eax, dword ptr [0xc07088]
008d6d00 cmp eax, dword ptr [ecx + 0xc]
008d6d06 jg 0x8d7921
008d6d0c mov esi, dword ptr [edi + 0x180]
008d6d12 test esi, esi
008d6d14 jle 0x8d6d26
008d6d16 cmp esi, 5
008d6d19 jae 0x8d6d26
008d6d1b shl esi, 4
008d6d1e add esi, 0xc070a0
008d6d24 jmp 0x8d6d2b
008d6d26 mov esi, 0xc070a0
008d6d2b cmp byte ptr [edi + 0x3ad], 0
008d6d32 mov dword ptr [esp + 0x24], esi
008d6d36 je 0x8d7556
008d6d3c mov esi, dword ptr [edi + 0x3d4]
008d6d42 mov eax, esi
008d6d44 sub eax, dword ptr [edi + 0x3d0]
008d6d4a sar eax, 3
008d6d4d mov dword ptr [esp + 0x10], 0
008d6d55 sub eax, 1
008d6d58 je 0x8d791b
008d6d5e movss xmm0, dword ptr [0xb6a704]
008d6d66 call 0x411fe0
008d6d6b movss dword ptr [esp + 0x38], xmm0
008d6d71 movss xmm0, dword ptr [0xb6a704]
008d6d79 call 0x412010
008d6d7e movss xmm5, dword ptr [0xb6a480]
008d6d86 xor ecx, ecx
008d6d88 mov edx, dword ptr [edi + 0x3d0]
008d6d8e movss dword ptr [esp + 0x3c], xmm0
008d6d94 mov dword ptr [esp + 0x40], 0x3f800000
008d6d9c mov dword ptr [esp + 0x44], 0x3f800000
008d6da4 movss xmm3, dword ptr [edx + ecx*8]
008d6da9 movss xmm4, dword ptr [edx + ecx*8 + 4]
008d6daf movss xmm0, dword ptr [edx + ecx*8 + 8]
008d6db5 movss xmm1, dword ptr [edx + ecx*8 + 0xc]
008d6dbb mov eax, dword ptr [edi + 0x30]
008d6dbe movss dword ptr [esp + 0x30], xmm3
008d6dc4 movss dword ptr [esp + 0x2c], xmm4
008d6dca movss dword ptr [esp + 0x14], xmm0
