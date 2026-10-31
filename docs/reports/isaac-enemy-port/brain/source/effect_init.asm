005b79c0 push ebp
005b79c1 mov ebp, esp
005b79c3 push -1
005b79c5 push 0x9f0e3c
005b79ca mov eax, dword ptr fs:[0]
005b79d0 push eax
005b79d1 sub esp, 0x158
005b79d7 mov eax, dword ptr [0xbaa3b4]
005b79dc xor eax, ebp
005b79de mov dword ptr [ebp - 0x10], eax
005b79e1 push esi
005b79e2 push edi
005b79e3 push eax
005b79e4 lea eax, [ebp - 0xc]
005b79e7 mov dword ptr fs:[0], eax
005b79ed mov esi, ecx
005b79ef mov dword ptr [ebp - 0xa8], esi
005b79f5 lea eax, [esi + 0x3d8]
005b79fb push 0
005b79fd mov ecx, eax
005b79ff mov dword ptr [ebp - 0xbc], eax
005b7a05 call 0x5eeac0
005b7a0a push dword ptr [ebp + 0x14]
005b7a0d mov eax, dword ptr [ebp + 0xc]
005b7a10 mov ecx, esi
005b7a12 push dword ptr [ebp + 0x10]
005b7a15 push eax
005b7a16 push dword ptr [ebp + 8]
005b7a19 call 0x6819e0
005b7a1e lea ecx, [esi + 0x3cc]
005b7a24 lea eax, [ebp - 0x144]
005b7a2a cmp eax, ecx
005b7a2c je 0x5b7a78
005b7a2e mov eax, dword ptr [ecx]
005b7a30 mov edx, dword ptr [ecx + 8]
005b7a33 mov dword ptr [ecx], 0
005b7a39 mov dword ptr [ecx + 4], 0
005b7a40 mov dword ptr [ecx + 8], 0
005b7a47 test eax, eax
005b7a49 je 0x5b7a78
005b7a4b sub edx, eax
005b7a4d and edx, 0xfffffffc
005b7a50 cmp edx, 0x1000
005b7a56 jb 0x5b7a6e
005b7a58 mov ecx, dword ptr [eax - 4]
005b7a5b add edx, 0x23
005b7a5e sub eax, ecx
005b7a60 add eax, -4
005b7a63 cmp eax, 0x1f
005b7a66 ja 0x5ba561
005b7a6c mov eax, ecx
005b7a6e push edx
005b7a6f push eax
005b7a70 call 0x9eb08e
005b7a75 add esp, 8
005b7a78 mov eax, dword ptr [esi + 0x288]
005b7a7e mov dword ptr [esi + 0x2dc], 0
005b7a88 test eax, eax
005b7a8a je 0x5b7b27
005b7a90 push 0
005b7a92 add eax, 0x74
005b7a95 lea ecx, [esi + 0x3c]
005b7a98 push eax
005b7a99 call 0x407160
005b7a9e cmp dword ptr [esi + 0x68], 0x10
005b7aa2 lea ecx, [esi + 0x54]
005b7aa5 mov dword ptr [ebp - 0xb0], ecx
005b7aab jb 0x5b7ab5
005b7aad mov ecx, dword ptr [ecx]
005b7aaf mov dword ptr [ebp - 0xb0], ecx
005b7ab5 cmp dword ptr [esi + 0x70], 0
005b7ab9 je 0x5b7b09
005b7abb mov edx, dword ptr [esi + 0x70]
005b7abe mov eax, edx
005b7ac0 cmp dword ptr [edx + 0x14], 0x10
005b7ac4 jb 0x5b7ac8
005b7ac6 mov eax, dword ptr [edx]
005b7ac8 mov dl, byte ptr [eax]
005b7aca cmp dl, byte ptr [ecx]
005b7acc jne 0x5b7ae8
005b7ace test dl, dl
005b7ad0 je 0x5b7ae4
005b7ad2 mov dl, byte ptr [eax + 1]
005b7ad5 cmp dl, byte ptr [ecx + 1]
005b7ad8 jne 0x5b7ae8
005b7ada add eax, 2
005b7add add ecx, 2
005b7ae0 test dl, dl
005b7ae2 jne 0x5b7ac8
005b7ae4 xor eax, eax
005b7ae6 jmp 0x5b7aed
005b7ae8 sbb eax, eax
005b7aea or eax, 1
005b7aed test eax, eax
005b7aef jne 0x5b7b03
005b7af1 mov eax, dword ptr [esi + 0x70]
005b7af4 cmp byte ptr [eax + 0x34], 0
005b7af8 je 0x5b7b27
005b7afa cmp byte ptr [esi + 0x80], 0
005b7b01 jne 0x5b7b27
005b7b03 mov ecx, dword ptr [ebp - 0xb0]
005b7b09 push 1
005b7b0b push ecx
005b7b0c lea ecx, [esi + 0x3c]
005b7b0f call 0x405740
005b7b14 test al, al
005b7b16 je 0x5b7b27
005b7b18 lea ecx, [esi + 0x6c]
005b7b1b call 0x405330
005b7b20 mov byte ptr [esi + 0x80], 1
005b7b27 mov edx, dword ptr [0xbfd65c]
005b7b2d mov dword ptr [esi + 0x3a0], 0
005b7b37 mov dword ptr [esi + 0x3ac], 0xffffffff
005b7b41 mov dword ptr [esi + 0x3b0], 1
005b7b4b movss xmm0, dword ptr [0xc02fec]
005b7b53 movss dword ptr [esi + 0x3b8], xmm0
005b7b5b movss xmm0, dword ptr [0xc02ff0]
005b7b63 movss dword ptr [esi + 0x3bc], xmm0
005b7b6b xorps xmm0, xmm0
005b7b6e movlpd qword ptr [ebp - 0x20], xmm0
005b7b73 movlpd qword ptr [ebp - 0x18], xmm0
005b7b78 movups xmm0, xmmword ptr [ebp - 0x20]
005b7b7c mov dword ptr [esi + 0x3c4], 0
005b7b86 mov byte ptr [esi + 0x3b4], 0
005b7b8d mov dword ptr [esi + 0x3c8], 0x3f800000
005b7b97 mov dword ptr [esi + 0x3a4], 0
005b7ba1 mov dword ptr [esi + 0x3a8], 0
005b7bab mov dword ptr [esi + 0x3c0], 0
005b7bb5 movups xmmword ptr [esi + 0x370], xmm0
005b7bbc mov eax, dword ptr [edx + 0x18190]
005b7bc2 cmp dword ptr [eax + 8], 0x10
005b7bc6 jne 0x5b7bf6
005b7bc8 mov eax, dword ptr [esi + 0x2c]
005b7bcb add eax, -7
005b7bce cmp eax, 0xbc
005b7bd3 ja 0x5b7bf6
005b7bd5 movzx eax, byte ptr [eax + 0x5bbffc]
005b7bdc jmp dword ptr [eax*4 + 0x5bbff4]
005b7be3 mov byte ptr [esi + 0x169], 0
005b7bea mov eax, dword ptr [esi]
005b7bec mov ecx, esi
005b7bee call dword ptr [eax + 0x28]
005b7bf1 jmp 0x5bbf75
005b7bf6 mov ecx, dword ptr [esi + 0x2c]
005b7bf9 cmp ecx, 0x16
005b7bfc je 0x5b7dd2
005b7c02 cmp ecx, 0x17
005b7c05 je 0x5b7dd2
005b7c0b cmp ecx, 0x18
005b7c0e je 0x5b7dd2
005b7c14 cmp ecx, 0x19
005b7c17 je 0x5b7dd2
005b7c1d cmp ecx, 0x1a
005b7c20 je 0x5b7dd2
005b7c26 cmp ecx, 0x20
005b7c29 je 0x5b7dd2
005b7c2f cmp ecx, 0x4e
005b7c32 je 0x5b7dd2
005b7c38 cmp ecx, 0x25
005b7c3b je 0x5b7dd2
005b7c41 cmp ecx, 0x2c
005b7c44 je 0x5b7dd2
005b7c4a cmp ecx, 0x2d
005b7c4d je 0x5b7dd2
005b7c53 cmp ecx, 0x2e
005b7c56 je 0x5b7dd2
005b7c5c cmp ecx, 0x36
005b7c5f je 0x5b7dd2
005b7c65 cmp ecx, 0x35
005b7c68 je 0x5b7dd2
005b7c6e cmp ecx, 0x38
005b7c71 je 0x5b7dd2
005b7c77 cmp ecx, 0x5a
005b7c7a je 0x5b7dd2
005b7c80 cmp ecx, 0x5c
005b7c83 je 0x5b7dd2
005b7c89 cmp ecx, 0x5d
005b7c8c je 0x5b7dd2
005b7c92 cmp ecx, 0x5e
005b7c95 je 0x5b7dd2
005b7c9b cmp ecx, 0xc3
005b7ca1 je 0x5b7dd2
005b7ca7 cmp ecx, 0xa9
005b7cad je 0x5b7dd2
005b7cb3 cmp ecx, 7
005b7cb6 je 0x5b7d09
005b7cb8 cmp ecx, 0x12
005b7cbb je 0x5b7da3
005b7cc1 cmp ecx, 0x59
005b7cc4 je 0x5b7cd1
005b7cc6 cmp ecx, 0x64
005b7cc9 jne 0x5b7ef6
005b7ccf jmp 0x5b7d12
005b7cd1 mov eax, dword ptr [esi + 0x70]
005b7cd4 test eax, eax
005b7cd6 je 0x5b7cdd
005b7cd8 mov ecx, dword ptr [eax + 0x30]
005b7cdb jmp 0x5b7cdf
005b7cdd xor ecx, ecx
005b7cdf call 0x659230
005b7ce4 cmp dword ptr [esi + 0x70], 0
005b7ce8 je 0x5b7cf9
005b7cea movd xmm1, eax
005b7cee lea ecx, [esi + 0x6c]
005b7cf1 cvtdq2ps xmm1, xmm1
005b7cf4 call 0x403c00
005b7cf9 xorps xmm0, xmm0
005b7cfc movups xmmword ptr [ebp - 0x3c], xmm0
005b7d00 movaps xmm0, xmmword ptr [0xb6b960]
005b7d07 jmp 0x5b7d7e
005b7d09 cmp ecx, 0x64
005b7d0c jne 0x5b7da3
005b7d12 push 0
005b7d14 push 0xb44568
005b7d19 lea ecx, [esi + 0x3c]
005b7d1c call 0x4054f0
005b7d21 cmp dword ptr [esi + 0xbc], 0
005b7d28 jg 0x5b7d48
005b7d2a cmp dword ptr [esi + 0x50], 0x10
005b7d2e lea eax, [esi + 0x3c]
005b7d31 jb 0x5b7d36
005b7d33 mov eax, dword ptr [esi + 0x3c]
005b7d36 push 0
005b7d38 push eax
005b7d39 push 0xa0830c
005b7d3e push 3
005b7d40 call 0x95e330
005b7d45 add esp, 0x10
005b7d48 mov eax, dword ptr [esi + 0xb8]
005b7d4e xorps xmm0, xmm0
005b7d51 movups xmmword ptr [ebp - 0x3c], xmm0
005b7d55 movaps xmm0, xmmword ptr [0xb6bb80]
005b7d5c mov dword ptr [eax + 0x78], 4
005b7d63 mov dword ptr [eax + 0x7c], 7
005b7d6a mov dword ptr [eax + 0x80], 4
005b7d74 mov dword ptr [eax + 0x84], 7
005b7d7e lea eax, [ebp - 0x4c]
005b7d81 mov dword ptr [ebp - 0x2c], 0
005b7d88 push eax
005b7d89 lea ecx, [esi + 0x3c]
005b7d8c mov dword ptr [ebp - 0x28], 0
005b7d93 movups xmmword ptr [ebp - 0x4c], xmm0
005b7d97 mov dword ptr [ebp - 0x24], 0
005b7d9e call 0x402370
005b7da3 mov eax, dword ptr [esi + 0x2c]
005b7da6 cmp eax, 7
005b7da9 je 0x5b7dc3
005b7dab cmp eax, 0x12
005b7dae je 0x5b7dc3
005b7db0 mov eax, dword ptr [esi + 0x164]
005b7db6 or dword ptr [esi + 0x160], 8
005b7dbd mov dword ptr [esi + 0x164], eax
005b7dc3 mov dword ptr [esi + 0x2b4], 0
005b7dcd jmp 0x5b7ef6
005b7dd2 mov dword ptr [esi + 0x2b4], 0
005b7ddc mov dword ptr [esi + 0x2ac], 0x7d0
005b7de6 cmp ecx, 0x20
005b7de9 je 0x5b7e01
005b7deb cmp ecx, 0x25
005b7dee je 0x5b7e01
005b7df0 cmp ecx, 0x4e
005b7df3 je 0x5b7e01
005b7df5 cmp ecx, 0x5a
005b7df8 je 0x5b7e01
005b7dfa mov eax, 0x7d
005b7dff jmp 0x5b7e10
005b7e01 mov dword ptr [esi + 0x3b0], 0x122
005b7e0b mov eax, 0x122
005b7e10 mov dword ptr [esi + 0x3ac], eax
005b7e16 mov byte ptr [esi + 0x16e], 1
005b7e1d mov eax, dword ptr [edx + 0x18190]
005b7e23 cmp ecx, 0x16
005b7e26 jne 0x5b7e86
005b7e28 cmp dword ptr [eax + 0x1e84], 0xa
005b7e2f jne 0x5b7e86
005b7e31 movaps xmm1, xmmword ptr [0xb6c290]
005b7e38 lea ecx, [esi + 0xe4]
005b7e3e lea eax, [ebp - 0xfc]
005b7e44 mov dword ptr [ebp - 0xdc], 0
005b7e4e mov dword ptr [ebp - 0xd8], 0
005b7e58 xorps xmm0, xmm0
005b7e5b mov dword ptr [ebp - 0xd4], 0
005b7e65 cmp ecx, eax
005b7e67 je 0x5b7e86
005b7e69 mov eax, dword ptr [ebp - 0xd4]
005b7e6f movups xmmword ptr [ecx + 0x10], xmm0
005b7e73 movq xmm0, qword ptr [ebp - 0xdc]
005b7e7b movq qword ptr [ecx + 0x20], xmm0
005b7e80 movups xmmword ptr [ecx], xmm1
005b7e83 mov dword ptr [ecx + 0x28], eax
005b7e86 mov eax, dword ptr [esi + 0x2c]
005b7e89 cmp eax, 0xa9
005b7e8e jne 0x5b7e9a
005b7e90 or dword ptr [esi + 0x14c], 0x20
005b7e97 mov eax, dword ptr [esi + 0x2c]
005b7e9a cmp eax, 0xc3
005b7e9f jne 0x5b7ef6
005b7ea1 movaps xmm1, xmmword ptr [0xb6bd30]
005b7ea8 lea ecx, [esi + 0xe4]
005b7eae lea eax, [ebp - 0x128]
005b7eb4 mov dword ptr [ebp - 0x108], 0x3f19999a
005b7ebe mov dword ptr [ebp - 0x104], 0x3ecccccd
005b7ec8 xorps xmm0, xmm0
005b7ecb mov dword ptr [ebp - 0x100], 0
005b7ed5 cmp ecx, eax
005b7ed7 je 0x5b7ef6
005b7ed9 mov eax, dword ptr [ebp - 0x100]
005b7edf movups xmmword ptr [ecx + 0x10], xmm0
005b7ee3 movq xmm0, qword ptr [ebp - 0x108]
005b7eeb movq qword ptr [ecx + 0x20], xmm0
005b7ef0 movups xmmword ptr [ecx], xmm1
005b7ef3 mov dword ptr [ecx + 0x28], eax
005b7ef6 mov ecx, dword ptr [esi + 0x2c]
005b7ef9 cmp ecx, 0xe
005b7efc jne 0x5b7f18
005b7efe mov dword ptr [esi + 0x2b4], 0
005b7f08 call 0x6c3d90
005b7f0d mov ecx, dword ptr [esi + 0x2c]
005b7f10 and al, 1
005b7f12 mov byte ptr [esi + 0x13c], al
005b7f18 xor edx, edx
005b7f1a mov edi, 3
005b7f1f cmp ecx, 5
005b7f22 mov eax, edi
005b7f24 cmovne eax, edx
005b7f27 mov dword ptr [esi + 0x17c], eax
005b7f2d movss xmm2, dword ptr [0xb6a19c]
005b7f35 movss xmm3, dword ptr [0xb6a480]
005b7f3d mov dword ptr [esi + 0x180], edx
005b7f43 cmp ecx, 0xc
005b7f46 je 0x5ba1c8
005b7f4c cmp ecx, 0xd
005b7f4f je 0x5ba1c8
005b7f55 cmp ecx, 0x4f
005b7f58 je 0x5ba1c8
005b7f5e cmp ecx, 0x50
005b7f61 je 0x5ba1c8
005b7f67 cmp ecx, 0x61
005b7f6a jne 0x5b7fb6
005b7f6c call 0x6c3d90
005b7f71 and eax, edi
005b7f73 mov byte ptr [esi + 0x16e], 1
005b7f7a movd xmm0, eax
005b7f7e cvtdq2pd xmm0, xmm0
005b7f82 shr eax, 0x1f
005b7f85 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
005b7f8e cvtpd2ps xmm0, xmm0
005b7f92 mulss xmm0, dword ptr [0xb6aae4]
005b7f9a movss dword ptr [esi + 0x3c4], xmm0
005b7fa2 call 0x6c3d90
005b7fa7 xor al, 0xff
005b7fa9 and al, 1
005b7fab mov byte ptr [esi + 0x13c], al
005b7fb1 jmp 0x5ba1ff
005b7fb6 cmp ecx, 1
005b7fb9 jne 0x5b7fcf
005b7fbb call 0x6c3d90
005b7fc0 xor al, 0xff
005b7fc2 and al, 1
005b7fc4 mov byte ptr [esi + 0x13c], al
005b7fca jmp 0x5ba1ff
005b7fcf cmp ecx, 4
005b7fd2 je 0x5ba0de
005b7fd8 cmp ecx, 0x1b
005b7fdb je 0x5ba0de
005b7fe1 cmp ecx, 0x23
005b7fe4 je 0x5ba0de
005b7fea cmp ecx, 0x55
005b7fed je 0x5ba0de
005b7ff3 cmp ecx, 0x56
005b7ff6 je 0x5ba0de
005b7ffc cmp ecx, 0x5f
005b7fff je 0x5ba0de
005b8005 cmp ecx, 0x62
005b8008 je 0x5ba0de
005b800e cmp ecx, 0xa3
005b8014 je 0x5ba0de
005b801a cmp ecx, 0x3a
005b801d jne 0x5b80d3
005b8023 mov dword ptr [esi + 0x368], 0x3fa66666
005b802d mov dword ptr [esi + 0x360], 0xc1b80000
005b8037 call 0x6c3d90
005b803c movd xmm0, eax
005b8040 cvtdq2pd xmm0, xmm0
005b8044 shr eax, 0x1f
005b8047 cmp dword ptr [esi + 0xbc], 0
005b804e addsd xmm0, qword ptr [eax*8 + 0xb6c940]
005b8057 cvtpd2ps xmm0, xmm0
005b805b mulss xmm0, xmm2
005b805f movss dword ptr [ebp - 0xac], xmm0
005b8067 jg 0x5b808f
005b8069 cmp dword ptr [esi + 0x50], 0x10
005b806d lea eax, [esi + 0x3c]
005b8070 jb 0x5b8075
005b8072 mov eax, dword ptr [esi + 0x3c]
005b8075 push 0
005b8077 push eax
005b8078 push 0xa0830c
005b807d push 3
005b807f call 0x95e330
005b8084 movss xmm0, dword ptr [ebp - 0xac]
005b808c add esp, 0x10
005b808f mov eax, dword ptr [esi + 0xb8]
005b8095 mulss xmm0, dword ptr [0xb6ac40]
005b809d movss dword ptr [eax + 0x3c], xmm0
005b80a2 call 0x6c3d90
005b80a7 xor edx, edx
005b80a9 mov ecx, 5
005b80ae div ecx
005b80b0 push 0
005b80b2 lea ecx, [esi + 0x3c]
005b80b5 push dword ptr [edx*4 + 0xb45a98]
005b80bc call 0x4054f0
005b80c1 call 0x6c3d90
005b80c6 movd xmm0, eax
005b80ca cvtdq2pd xmm0, xmm0
005b80ce jmp 0x5b8c10
005b80d3 cmp ecx, 0x22
005b80d6 jne 0x5b8226
005b80dc cmp dword ptr [esi + 0x30], 1
005b80e0 jne 0x5b81b2
005b80e6 push 0x20
005b80e8 call 0x407de0
005b80ed movups xmm0, xmmword ptr [0xb450a0]
005b80f4 mov edx, eax
005b80f6 mov dword ptr [ebp - 0x28], 0x1f
005b80fd mov edi, 0x1f
005b8102 mov dword ptr [ebp - 0x38], edx
005b8105 mov dword ptr [ebp - 0x24], edi
005b8108 movups xmmword ptr [edx], xmm0
005b810b movq xmm0, qword ptr [0xb450b0]
005b8113 movq qword ptr [edx + 0x10], xmm0
005b8118 mov ecx, dword ptr [0xb450b8]
005b811e mov dword ptr [edx + 0x18], ecx
005b8121 mov ax, word ptr [0xb450bc]
005b8127 mov word ptr [edx + 0x1c], ax
005b812b mov al, byte ptr [0xb450be]
005b8130 mov byte ptr [edx + 0x1e], al
005b8133 mov byte ptr [edx + 0x1f], 0
005b8137 mov dword ptr [ebp - 4], 0
005b813e cmp dword ptr [esi + 0xbc], 0
005b8145 jle 0x5b8174
005b8147 mov eax, dword ptr [esi + 0xb8]
005b814d lea esi, [ebp - 0x38]
005b8150 lea ecx, [eax + 8]
005b8153 cmp ecx, esi
005b8155 mov esi, dword ptr [ebp - 0xa8]
005b815b je 0x5b8170
005b815d push edi
005b815e push edx
005b815f call 0x407c80
005b8164 mov eax, dword ptr [esi + 0xb8]
005b816a mov edi, dword ptr [ebp - 0x24]
005b816d mov edx, dword ptr [ebp - 0x38]
005b8170 mov byte ptr [eax + 0x30], 0
005b8174 mov dword ptr [ebp - 4], 0xffffffff
005b817b cmp edi, 0x10
005b817e jb 0x5b81a9
005b8180 inc edi
005b8181 mov eax, edx
005b8183 cmp edi, 0x1000
005b8189 jb 0x5b819f
005b818b mov edx, dword ptr [edx - 4]
005b818e add edi, 0x23
005b8191 sub eax, edx
005b8193 add eax, -4
005b8196 cmp eax, 0x1f
005b8199 ja 0x5ba561
005b819f push edi
005b81a0 push edx
005b81a1 call 0x9eb08e
005b81a6 add esp, 8
005b81a9 push ecx
005b81aa lea ecx, [esi + 0x3c]
005b81ad call 0x4073a0
005b81b2 call 0x6c3d90
005b81b7 xor al, 0xff
005b81b9 and al, 1
005b81bb cmp dword ptr [esi + 0x30], 0xa
005b81bf mov byte ptr [esi + 0x13c], al
005b81c5 jae 0x5b8217
005b81c7 mov esi, dword ptr [0xbfd680]
005b81cd lea ecx, [ebp - 0xac]
005b81d3 mov dword ptr [ebp - 0xac], 0x25
005b81dd call 0x8b1340
005b81e2 sub esp, 8
005b81e5 mov dword ptr [esp + 4], 0
005b81ed mov dword ptr [esp], 0x3f800000
005b81f4 push 0
005b81f6 push 0x14
005b81f8 push ecx
005b81f9 mov dword ptr [esp], 0x3f800000
005b8200 lea ecx, [esi + 0x29de0]
005b8206 push dword ptr [ebp - 0xac]
005b820c call 0x888de0
005b8211 mov esi, dword ptr [ebp - 0xa8]
005b8217 mov dword ptr [esi + 0x2ac], 0x3e8
005b8221 jmp 0x5ba1ff
005b8226 cmp ecx, 8
005b8229 jne 0x5b823a
005b822b mov dword ptr [esi + 0x2b0], 0xc2200000
005b8235 jmp 0x5ba1ff
005b823a cmp ecx, 0xa
005b823d je 0x5ba0a8
005b8243 cmp ecx, 0x34
005b8246 je 0x5ba0a8
005b824c cmp ecx, 0x33
005b824f je 0x5ba0a8
005b8255 cmp ecx, 0x1f
005b8258 jne 0x5b826e
005b825a push 0
005b825c push 0xb45098
005b8261 lea ecx, [esi + 0x3c]
005b8264 call 0x405850
005b8269 jmp 0x5ba1ff
005b826e cmp ecx, 0x37
005b8271 jne 0x5b829b
005b8273 push 0
005b8275 push 0xb4508c
005b827a lea ecx, [esi + 0x3c]
005b827d call 0x4054f0
005b8282 mov dword ptr [esi + 0x3a0], 1
005b828c mov dword ptr [esi + 0x2e0], 0x3f800000
005b8296 jmp 0x5ba1ff
005b829b mov eax, dword ptr [ebp + 0xc]
005b829e cmp eax, 0x15
005b82a1 je 0x5ba00b
005b82a7 cmp eax, 0x21
005b82aa je 0x5b9fd8
005b82b0 cmp eax, 0x44
005b82b3 je 0x5ba015
005b82b9 cmp eax, 2
005b82bc jne 0x5b82e8
005b82be mov eax, dword ptr [esi + 0x30]
005b82c1 test eax, eax
005b82c3 je 0x5ba1f8
005b82c9 cmp eax, 5
005b82cc ja 0x5ba1f8
005b82d2 push 0
005b82d4 push dword ptr [eax*4 + 0xb459a0]
005b82db lea ecx, [esi + 0x3c]
005b82de call 0x4054f0
005b82e3 jmp 0x5ba1f8
005b82e8 cmp eax, 0xf
005b82eb jne 0x5b8319
005b82ed mov eax, dword ptr [esi + 0x30]
005b82f0 test eax, eax
005b82f2 je 0x5b830a
005b82f4 cmp eax, 3
005b82f7 ja 0x5b830a
005b82f9 push 0
005b82fb push dword ptr [eax*4 + 0xb459dc]
005b8302 lea ecx, [esi + 0x3c]
005b8305 call 0x4054f0
005b830a mov dword ptr [esi + 0x2ac], 0x1f40
005b8314 jmp 0x5ba1ff
005b8319 cmp eax, 0x10
005b831c jne 0x5b83f5
005b8322 mov eax, dword ptr [esi + 0x30]
005b8325 cmp eax, 1
005b8328 je 0x5b83ca
005b832e cmp eax, 3
005b8331 je 0x5b83ca
005b8337 cmp eax, 2
005b833a je 0x5b83ac
005b833c cmp eax, 4
005b833f je 0x5b83ac
005b8341 cmp eax, 5
005b8344 je 0x5b83ac
005b8346 cmp eax, 0x42
005b8349 jne 0x5b839a
005b834b mov eax, dword ptr [esi + 0x344]
005b8351 lea ecx, [ebp - 0x20]
005b8354 movq xmm0, qword ptr [0xa08ad0]
005b835c push 0
005b835e mov dword ptr [ebp - 0x20], eax
005b8361 mov eax, dword ptr [0xa08ad8]
005b8366 push 3
005b8368 movq qword ptr [ebp - 0x1c], xmm0
005b836d mov dword ptr [ebp - 0x14], eax
005b8370 call 0x7a7d50
005b8375 mov eax, dword ptr [eax*4 + 0xb45934]
005b837c push eax
005b837d lea ecx, [esi + 0x3c]
005b8380 call 0x4054f0
005b8385 mov al, byte ptr [esi + 0x344]
005b838b not al
005b838d and al, 1
005b838f mov byte ptr [esi + 0x13c], al
005b8395 jmp 0x5ba1ff
005b839a cmp eax, 0x43
005b839d jne 0x5ba1ff
005b83a3 push 0
005b83a5 push 0xb450fc
005b83aa jmp 0x5b837d
005b83ac push 0
005b83ae push 0xb4030c
005b83b3 lea ecx, [esi + 0x3c]
005b83b6 mov dword ptr [esi + 0x2ac], 0x1f40
005b83c0 call 0x4054f0
005b83c5 jmp 0x5ba1ff
005b83ca mov eax, dword ptr [0xbfd65c]
005b83cf mov eax, dword ptr [eax + 0x18190]
005b83d5 cmp dword ptr [eax + 8], 0x10
005b83d9 je 0x5b83e1
005b83db mov dword ptr [esi + 0x2b4], edx
005b83e1 push 0
005b83e3 push 0xb4030c
005b83e8 lea ecx, [esi + 0x3c]
005b83eb call 0x4054f0
005b83f0 jmp 0x5ba1ff
005b83f5 cmp eax, 0x39
005b83f8 jne 0x5b8439
005b83fa cmp dword ptr [esi + 0x30], edx
005b83fd mov ecx, 0xb450f4
005b8402 mov eax, 0xb42494
005b8407 cmovne eax, ecx
005b840a lea ecx, [esi + 0x3c]
005b840d push 0
005b840f push eax
005b8410 call 0x4054f0
005b8415 mov eax, dword ptr [0xbfd65c]
005b841a mov eax, dword ptr [eax + 0x18190]
005b8420 cmp dword ptr [eax + 8], 0x10
005b8424 je 0x5ba1ff
005b842a mov dword ptr [esi + 0x2b4], 0
005b8434 jmp 0x5ba1ff
005b8439 cmp eax, 0x3b
005b843c jne 0x5b8520
005b8442 push 0xb450ec
005b8447 lea ecx, [esi + 0x3c]
005b844a call 0x4070e0
005b844f mov dword ptr [ebp - 0xac], eax
005b8455 test eax, eax
005b8457 je 0x5ba1ff
005b845d mov ecx, dword ptr [eax + 0x30]
005b8460 call 0x659230
005b8465 push eax
005b8466 push dword ptr [ebp - 0xac]
005b846c lea ecx, [esi + 0x3c]
005b846f call 0x405800
005b8474 call 0x6c3d90
005b8479 xor al, 0xff
005b847b and al, 1
005b847d mov byte ptr [esi + 0x13c], al
005b8483 call 0x6c3d90
005b8488 movd xmm0, eax
005b848c cvtdq2pd xmm0, xmm0
005b8490 shr eax, 0x1f
005b8493 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
005b849c cvtpd2ps xmm0, xmm0
005b84a0 mulss xmm0, dword ptr [0xb6a19c]
005b84a8 mulss xmm0, dword ptr [0xb6ac40]
005b84b0 subss xmm0, dword ptr [0xb6ab88]
005b84b8 movss dword ptr [esi + 0xe0], xmm0
005b84c0 mov dword ptr [esi + 0xd8], 0x3f000000
005b84ca mov dword ptr [esi + 0xdc], 0x3f000000
005b84d4 cmp dword ptr [esi + 0x30], 1
005b84d8 mov dword ptr [esi + 0x2ac], 0x1f40
005b84e2 jne 0x5ba1ff
005b84e8 xorps xmm0, xmm0
005b84eb mov dword ptr [ebp - 0x2c], 0xbf000000
005b84f2 movups xmmword ptr [ebp - 0x3c], xmm0
005b84f6 lea eax, [ebp - 0x4c]
005b84f9 mov dword ptr [ebp - 0x28], 0xbf000000
005b8500 movaps xmm0, xmmword ptr [0xb6c610]
005b8507 lea ecx, [esi + 0x3c]
005b850a push eax
005b850b movups xmmword ptr [ebp - 0x4c], xmm0
005b850f mov dword ptr [ebp - 0x24], 0xbf000000
005b8516 call 0x402370
005b851b jmp 0x5ba1ff
005b8520 cmp ecx, 0x3c
005b8523 jne 0x5b8553
005b8525 push 0
005b8527 push 0xb42e30
005b852c lea ecx, [esi + 0x3c]
005b852f mov dword ptr [esi + 0x17c], edi
005b8535 call 0x4054f0
005b853a mov dword ptr [esi + 0x2a4], 0
005b8544 mov dword ptr [esi + 0x2a8], 0xc1a00000
005b854e jmp 0x5ba1ff
005b8553 cmp ecx, 0x3d
005b8556 jne 0x5b8581
005b8558 mov byte ptr [esi + 0x169], dl
005b855e mov dword ptr [esi + 0x3ac], 0x14
005b8568 mov dword ptr [esi + 0x3a4], 0x41a00000
005b8572 mov dword ptr [esi + 0x3a8], 0x42be0000
005b857c jmp 0x5ba1ff
005b8581 cmp ecx, 0x43
005b8584 jne 0x5b85af
005b8586 mov byte ptr [esi + 0x169], dl
005b858c mov dword ptr [esi + 0x3ac], 0x32
005b8596 mov dword ptr [esi + 0x3a4], 0x42340000
005b85a0 mov dword ptr [esi + 0x3a8], 0x43a00000
005b85aa jmp 0x5ba1ff
005b85af cmp ecx, 0x3e
005b85b2 jne 0x5b8882
005b85b8 call 0x6c3d90
005b85bd xor al, 0xff
005b85bf and al, 1
005b85c1 mov byte ptr [esi + 0x13c], al
005b85c7 mov eax, dword ptr [0xbfd65c]
005b85cc mov ecx, dword ptr [eax + 0x18190]
005b85d2 mov eax, dword ptr [ecx + 0x1e84]
005b85d8 add eax, -4
005b85db cmp eax, 0x2a
005b85de ja 0x5ba1ff
005b85e4 movzx eax, byte ptr [eax + 0x5bc0e8]
005b85eb jmp dword ptr [eax*4 + 0x5bc0bc]
005b85f2 push 0x30
005b85f4 call 0x407de0
005b85f9 movups xmm0, xmmword ptr [0xb450c0]
005b8600 mov edx, eax
005b8602 mov dword ptr [ebp - 0x28], 0x2b
005b8609 mov ecx, 0x2f
005b860e mov dword ptr [ebp - 0x38], edx
005b8611 mov dword ptr [ebp - 0x24], ecx
005b8614 movups xmmword ptr [edx], xmm0
005b8617 movups xmm0, xmmword ptr [0xb450d0]
005b861e movups xmmword ptr [edx + 0x10], xmm0
005b8622 movq xmm0, qword ptr [0xb450e0]
005b862a movq qword ptr [edx + 0x20], xmm0
005b862f mov ax, word ptr [0xb450e8]
005b8635 mov word ptr [edx + 0x28], ax
005b8639 mov al, byte ptr [0xb450ea]
005b863e mov byte ptr [edx + 0x2a], al
005b8641 mov byte ptr [edx + 0x2b], 0
005b8645 mov dword ptr [ebp - 4], 1
005b864c cmp dword ptr [esi + 0xbc], 0
005b8653 jle 0x5b8685
005b8655 mov eax, dword ptr [esi + 0xb8]
005b865b lea esi, [ebp - 0x38]
005b865e lea edi, [eax + 8]
005b8661 cmp edi, esi
005b8663 mov esi, dword ptr [ebp - 0xa8]
005b8669 je 0x5b8681
005b866b push 0x2b
005b866d push edx
005b866e mov ecx, edi
005b8670 call 0x407c80
005b8675 mov eax, dword ptr [esi + 0xb8]
005b867b mov ecx, dword ptr [ebp - 0x24]
005b867e mov edx, dword ptr [ebp - 0x38]
005b8681 mov byte ptr [eax + 0x30], 0
005b8685 mov dword ptr [ebp - 4], 0xffffffff
005b868c cmp ecx, 0x10
005b868f jb 0x5ba1ff
005b8695 inc ecx
005b8696 mov eax, edx
005b8698 cmp ecx, 0x1000
005b869e jb 0x5b86b4
005b86a0 mov edx, dword ptr [edx - 4]
005b86a3 add ecx, 0x23
005b86a6 sub eax, edx
005b86a8 add eax, -4
005b86ab cmp eax, 0x1f
005b86ae ja 0x5ba561
005b86b4 push ecx
005b86b5 push edx
005b86b6 call 0x9eb08e
005b86bb add esp, 8
005b86be jmp 0x5ba1ff
005b86c3 push 0x30
005b86c5 call 0x407de0
005b86ca movups xmm0, xmmword ptr [0xb45194]
005b86d1 mov ecx, eax
005b86d3 mov dword ptr [ebp - 0x28], 0x2c
005b86da mov dword ptr [ebp - 0x24], 0x2f
005b86e1 mov dword ptr [ebp - 0x38], ecx
005b86e4 movups xmmword ptr [ecx], xmm0
005b86e7 movups xmm0, xmmword ptr [0xb451a4]
005b86ee movups xmmword ptr [ecx + 0x10], xmm0
005b86f2 movq xmm0, qword ptr [0xb451b4]
005b86fa movq qword ptr [ecx + 0x20], xmm0
005b86ff mov eax, dword ptr [0xb451bc]
005b8704 mov dword ptr [ecx + 0x28], eax
005b8707 mov byte ptr [ecx + 0x2c], 0
005b870b lea eax, [ebp - 0x38]
005b870e mov dword ptr [ebp - 4], 2
005b8715 push eax
005b8716 push 0
005b8718 lea ecx, [esi + 0x3c]
005b871b call 0x407340
005b8720 mov dword ptr [ebp - 4], 0xffffffff
005b8727 mov edx, dword ptr [ebp - 0x24]
005b872a cmp edx, 0x10
005b872d jb 0x5ba1ff
005b8733 mov ecx, dword ptr [ebp - 0x38]
005b8736 inc edx
005b8737 mov eax, ecx
005b8739 cmp edx, 0x1000
005b873f jb 0x5b8755
005b8741 mov ecx, dword ptr [ecx - 4]
005b8744 add edx, 0x23
005b8747 sub eax, ecx
005b8749 add eax, -4
005b874c cmp eax, 0x1f
005b874f ja 0x5ba561
005b8755 push edx
005b8756 push ecx
005b8757 call 0x9eb08e
005b875c add esp, 8
005b875f jmp 0x5ba1ff
005b8764 push 0xb45168
005b8769 lea ecx, [ebp - 0x38]
005b876c call 0x407990
005b8771 mov dword ptr [ebp - 4], 3
005b8778 jmp 0x5b8840
005b877d push 0xb45138
005b8782 lea ecx, [ebp - 0x38]
005b8785 call 0x407990
005b878a mov dword ptr [ebp - 4], 4
005b8791 jmp 0x5b8840
005b8796 call 0x7df1a0
005b879b lea ecx, [ebp - 0x38]
005b879e test al, al
005b87a0 je 0x5b87b8
005b87a2 push 0xb45108
005b87a7 call 0x407990
005b87ac mov dword ptr [ebp - 4], 5
005b87b3 jmp 0x5b96b0
005b87b8 push 0xb45254
005b87bd call 0x407990
005b87c2 mov dword ptr [ebp - 4], 6
005b87c9 jmp 0x5b96b0
005b87ce push 0xb45108
005b87d3 lea ecx, [ebp - 0x38]
005b87d6 call 0x407990
005b87db mov dword ptr [ebp - 4], 7
005b87e2 jmp 0x5b96b0
005b87e7 push 0xb45224
005b87ec lea ecx, [ebp - 0x38]
005b87ef call 0x407990
005b87f4 mov dword ptr [ebp - 4], 8
005b87fb jmp 0x5b96b0
005b8800 push 0xb451f4
005b8805 lea ecx, [ebp - 0x38]
005b8808 call 0x407990
005b880d mov dword ptr [ebp - 4], 9
005b8814 jmp 0x5b8840
005b8816 push 0xb451c4
005b881b lea ecx, [ebp - 0x38]
005b881e call 0x407990
005b8823 mov dword ptr [ebp - 4], 0xa
005b882a jmp 0x5b8840
005b882c push 0xb45168
005b8831 lea ecx, [ebp - 0x38]
005b8834 call 0x407990
005b8839 mov dword ptr [ebp - 4], 0xb
005b8840 lea eax, [ebp - 0x38]
005b8843 push eax
005b8844 lea edi, [esi + 0x3c]
005b8847 push 0
005b8849 mov ecx, edi
005b884b call 0x407340
005b8850 lea ecx, [ebp - 0x38]
005b8853 mov dword ptr [ebp - 4], 0xffffffff
005b885a call 0x407be0
005b885f push 0
005b8861 push 3
005b8863 lea ecx, [esi + 0x334]
005b8869 call 0x7a7d50
005b886e mov ecx, edi
005b8870 mov eax, dword ptr [eax*4 + 0xb45928]
005b8877 push eax
005b8878 call 0x4054f0
005b887d jmp 0x5ba1ff
005b8882 cmp ecx, 0x29
005b8885 jne 0x5b8997
005b888b mov eax, dword ptr [0xbfd65c]
005b8890 mov eax, dword ptr [eax]
005b8892 cmp eax, 7
005b8895 jl 0x5b88ad
005b8897 push 0xb452bc
005b889c lea ecx, [ebp - 0x38]
005b889f call 0x407990
005b88a4 mov dword ptr [ebp - 4], 0xc
005b88ab jmp 0x5b88d6
005b88ad cmp eax, 5
005b88b0 je 0x5b88b7
005b88b2 cmp eax, 6
005b88b5 jne 0x5b88f3
005b88b7 mov eax, dword ptr [0xbfd65c]
005b88bc cmp dword ptr [eax + 4], 2
005b88c0 jne 0x5b88f3
005b88c2 push 0xb45298
005b88c7 lea ecx, [ebp - 0x38]
005b88ca call 0x407990
005b88cf mov dword ptr [ebp - 4], 0xd
005b88d6 lea eax, [ebp - 0x38]
005b88d9 push eax
005b88da push 0
005b88dc lea ecx, [esi + 0x3c]
005b88df call 0x407340
005b88e4 lea ecx, [ebp - 0x38]
005b88e7 mov dword ptr [ebp - 4], 0xffffffff
005b88ee call 0x407be0
005b88f3 call 0x6c3d90
005b88f8 xor edx, edx
005b88fa lea ecx, [esi + 0x3c]
005b88fd div edi
005b88ff push 0
005b8901 mov dword ptr [esi + 0x3a0], edx
005b8907 test edx, edx
005b8909 jne 0x5b896f
005b890b push 0xb4528c
005b8910 call 0x4054f0
005b8915 call 0x6c3d90
005b891a movd xmm0, eax
005b891e cvtdq2pd xmm0, xmm0
005b8922 shr eax, 0x1f
005b8925 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
005b892e cvtpd2ps xmm1, xmm0
005b8932 mulss xmm1, dword ptr [0xb6a19c]
005b893a mulss xmm1, dword ptr [0xb6a480]
005b8942 addss xmm1, dword ptr [0xb6a480]
005b894a movaps xmm0, xmm1
005b894d mulss xmm1, dword ptr [0xbc7a2c]
005b8955 mulss xmm0, dword ptr [0xbc7a28]
005b895d movss dword ptr [esi + 0xdc], xmm1
005b8965 movss dword ptr [esi + 0xd8], xmm0
005b896d jmp 0x5b8979
005b896f push 0xb45280
005b8974 call 0x4054f0
005b8979 mov dword ptr [esi + 0x360], 0xc1200000
005b8983 call 0x6c3d90
005b8988 xor al, 0xff
005b898a and al, 1
005b898c mov byte ptr [esi + 0x13c], al
005b8992 jmp 0x5ba1ff
005b8997 cmp ecx, 0x41
005b899a jne 0x5b8b5c
005b89a0 push ecx
005b89a1 mov ecx, dword ptr [0xbfd65c]
005b89a7 call 0x706110
005b89ac add eax, -0xa
005b89af cmp eax, 0x18
005b89b2 ja 0x5b8a81
005b89b8 movzx eax, byte ptr [eax + 0x5bc124]
005b89bf jmp dword ptr [eax*4 + 0x5bc114]
005b89c6 push 0
005b89c8 lea edi, [esi + 0x3c]
005b89cb push 0xb45304
005b89d0 mov ecx, edi
005b89d2 call 0x4054f0
005b89d7 movss xmm3, dword ptr [0xb6a480]
005b89df movss xmm1, dword ptr [0xb6a614]
005b89e7 movaps xmm2, xmm3
005b89ea jmp 0x5b8aaa
005b89ef push 0
005b89f1 lea edi, [esi + 0x3c]
005b89f4 push 0xb45084
005b89f9 mov ecx, edi
005b89fb call 0x4054f0
005b8a00 movss xmm2, dword ptr [0xb6a560]
005b8a08 xorps xmm3, xmm3
005b8a0b movss xmm1, dword ptr [0xb6a614]
005b8a13 push ecx
005b8a14 lea ecx, [ebp - 0x4c]
005b8a17 mov dword ptr [esp], 0x3f800000
005b8a1e call 0x4325d0
005b8a23 push eax
005b8a24 mov ecx, edi
005b8a26 call 0x402370
005b8a2b movss xmm2, dword ptr [0xb6a614]
005b8a33 movss xmm3, dword ptr [0xb6a480]
005b8a3b movaps xmm1, xmm2
005b8a3e jmp 0x5b8aaa
005b8a40 push 0
005b8a42 lea edi, [esi + 0x3c]
005b8a45 push 0xb45084
005b8a4a mov ecx, edi
005b8a4c call 0x4054f0
005b8a51 movss xmm2, dword ptr [0xb6a234]
005b8a59 xorps xmm3, xmm3
005b8a5c movss xmm1, dword ptr [0xb6a614]
005b8a64 push ecx
005b8a65 lea ecx, [ebp - 0x4c]
005b8a68 mov dword ptr [esp], 0x3f800000
005b8a6f call 0x4325d0
005b8a74 push eax
005b8a75 mov ecx, edi
005b8a77 call 0x402370
005b8a7c jmp 0x5b89d7
005b8a81 push 0
005b8a83 lea edi, [esi + 0x3c]
005b8a86 push 0xb452fc
005b8a8b mov ecx, edi
005b8a8d call 0x4054f0
005b8a92 movss xmm3, dword ptr [0xb6a614]
005b8a9a movss xmm2, dword ptr [0xb6a4c4]
005b8aa2 movss xmm1, dword ptr [0xb6a434]
005b8aaa lea ecx, [ebp - 0x4c]
005b8aad call 0x427080
005b8ab2 push eax
005b8ab3 lea ecx, [esi + 0x1dc]
005b8ab9 call 0x4021a0
005b8abe call 0x6c3d90
005b8ac3 movd xmm0, eax
005b8ac7 cvtdq2pd xmm0, xmm0
005b8acb shr eax, 0x1f
005b8ace addsd xmm0, qword ptr [eax*8 + 0xb6c940]
005b8ad7 cvtpd2ps xmm0, xmm0
005b8adb mulss xmm0, dword ptr [0xb6a19c]
005b8ae3 mulss xmm0, dword ptr [0xb6af28]
005b8aeb movss dword ptr [esi + 0x2a8], xmm0
005b8af3 call 0x6c3d90
005b8af8 push 2
005b8afa lea ecx, [ebp - 0x20]
005b8afd movd xmm0, eax
005b8b01 cvtdq2pd xmm0, xmm0
005b8b05 shr eax, 0x1f
005b8b08 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
005b8b11 cvtpd2ps xmm1, xmm0
005b8b15 mulss xmm1, dword ptr [0xb6a19c]
005b8b1d mulss xmm1, dword ptr [0xb6a480]
005b8b25 addss xmm1, dword ptr [0xb6a480]
005b8b2d movaps xmm0, xmm1
005b8b30 mulss xmm1, dword ptr [0xbc7a2c]
005b8b38 mulss xmm0, dword ptr [0xbc7a28]
005b8b40 movss dword ptr [esi + 0xdc], xmm1
005b8b48 movss dword ptr [esi + 0xd8], xmm0
005b8b50 call 0x95ed30
005b8b55 mov ecx, edi
005b8b57 jmp 0x5b9893
005b8b5c cmp ecx, 0x3f
005b8b5f jne 0x5b8c49
005b8b65 mov eax, dword ptr [0xbfd65c]
005b8b6a mov eax, dword ptr [eax + 0x18190]
005b8b70 cmp dword ptr [eax + 8], 0x10
005b8b74 je 0x5b7bea
005b8b7a mov eax, dword ptr [esi + 0x30]
005b8b7d test eax, eax
005b8b7f jne 0x5b8b89
005b8b81 push eax
005b8b82 push 0xb452f0
005b8b87 jmp 0x5b8ba3
005b8b89 cmp eax, 1
005b8b8c jne 0x5b8b97
005b8b8e push 0
005b8b90 push 0xb452e4
005b8b95 jmp 0x5b8ba3
005b8b97 cmp eax, 2
005b8b9a jne 0x5b8bb3
005b8b9c push 0
005b8b9e push 0xb45344
005b8ba3 lea ecx, [esi + 0x3c]
005b8ba6 call 0x4054f0
005b8bab movss xmm2, dword ptr [0xb6a19c]
005b8bb3 call 0x6c3d90
005b8bb8 xorps xmm0, xmm0
005b8bbb cvtsi2sd xmm0, eax
005b8bbf shr eax, 0x1f
005b8bc2 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
005b8bcb cvtpd2ps xmm0, xmm0
005b8bcf mulss xmm0, xmm2
005b8bd3 mulss xmm0, dword ptr [0xb6ac40]
005b8bdb call 0x65a640
005b8be0 movss dword ptr [esi + 0x3c4], xmm0
005b8be8 movss dword ptr [esi + 0xe0], xmm0
005b8bf0 mov dword ptr [esi + 0x2b4], 1
005b8bfa mov dword ptr [esi + 0x368], 0x3fa66666
005b8c04 call 0x6c3d90
005b8c09 xorps xmm0, xmm0
005b8c0c cvtsi2sd xmm0, eax
005b8c10 shr eax, 0x1f
005b8c13 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
005b8c1c cvtpd2ps xmm1, xmm0
005b8c20 movss xmm0, dword ptr [0xb6a8f4]
005b8c28 mulss xmm1, dword ptr [0xb6a19c]
005b8c30 mulss xmm1, dword ptr [0xb6aa0c]
005b8c38 subss xmm0, xmm1
005b8c3c movss dword ptr [esi + 0x364], xmm0
005b8c44 jmp 0x5ba1ff
005b8c49 cmp ecx, 0x40
005b8c4c jne 0x5b8cd5
005b8c52 push 0
005b8c54 push 0xb40504
005b8c59 lea ecx, [esi + 0x3c]
005b8c5c call 0x4054f0
005b8c61 call 0x6c3d90
005b8c66 movd xmm0, eax
005b8c6a cvtdq2pd xmm0, xmm0
005b8c6e shr eax, 0x1f
005b8c71 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
005b8c7a cvtpd2ps xmm0, xmm0
005b8c7e mulss xmm0, dword ptr [0xb6a19c]
005b8c86 mulss xmm0, dword ptr [0xb6ac40]
005b8c8e call 0x65a640
005b8c93 mov eax, dword ptr [ebp - 0xa8]
005b8c99 lea ecx, [esi + 0x3c]
005b8c9c push 0
005b8c9e movss dword ptr [ebp - 0xac], xmm0
005b8ca6 movss dword ptr [eax + 0x3c4], xmm0
005b8cae call 0x4062c0
005b8cb3 mov esi, dword ptr [ebp - 0xa8]
005b8cb9 movss xmm0, dword ptr [ebp - 0xac]
005b8cc1 movss dword ptr [eax + 0x3c], xmm0
005b8cc6 mov dword ptr [esi + 0x360], 0
005b8cd0 jmp 0x5ba1f8
005b8cd5 cmp ecx, 0x45
005b8cd8 jne 0x5b8dbd
005b8cde push 0
005b8ce0 push 0xb3fd8c
005b8ce5 lea ecx, [esi + 0x3c]
005b8ce8 call 0x4054f0
005b8ced mov ecx, dword ptr [ebp - 0xa8]
005b8cf3 lea ecx, [ecx + 0x6c]
005b8cf6 call 0x432ec0
005b8cfb mov ecx, eax
005b8cfd call 0x659230
005b8d02 push eax
005b8d03 lea ecx, [esi + 0x3c]
005b8d06 call 0x405890
005b8d0b call 0x6c3d90
005b8d10 movd xmm0, eax
005b8d14 cvtdq2pd xmm0, xmm0
005b8d18 shr eax, 0x1f
005b8d1b addsd xmm0, qword ptr [eax*8 + 0xb6c940]
005b8d24 cvtpd2ps xmm0, xmm0
005b8d28 mulss xmm0, dword ptr [0xb6a19c]
005b8d30 mulss xmm0, dword ptr [0xb6ac40]
005b8d38 call 0x65a640
005b8d3d mov esi, dword ptr [ebp - 0xa8]
005b8d43 movss dword ptr [esi + 0x3c4], xmm0
005b8d4b movss dword ptr [esi + 0xe0], xmm0
005b8d53 call 0x6c3d90
005b8d58 movd xmm0, eax
005b8d5c cvtdq2pd xmm0, xmm0
005b8d60 shr eax, 0x1f
005b8d63 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
005b8d6c cvtpd2ps xmm0, xmm0
005b8d70 mulss xmm0, dword ptr [0xb6a19c]
005b8d78 mulss xmm0, dword ptr [0xb6af0c]
005b8d80 subss xmm0, dword ptr [0xb6a8f4]
005b8d88 movss dword ptr [esi + 0x2a8], xmm0
005b8d90 movss dword ptr [esi + 0x360], xmm0
005b8d98 movss xmm0, dword ptr [0xc02fec]
005b8da0 movss dword ptr [esi + 0x28c], xmm0
005b8da8 movss xmm0, dword ptr [0xc02ff0]
005b8db0 movss dword ptr [esi + 0x290], xmm0
005b8db8 jmp 0x5ba1f8
005b8dbd cmp ecx, 0x46
005b8dc0 jne 0x5b8e33
005b8dc2 call 0x6c3d90
005b8dc7 xor edx, edx
005b8dc9 lea ecx, [esi + 0x3c]
005b8dcc div edi
005b8dce push edx
005b8dcf push 0xb45338
005b8dd4 call 0x405850
005b8dd9 mov dword ptr [esi + 0x368], 0x3fa66666
005b8de3 call 0x6c3d90
005b8de8 mov dword ptr [esi + 0x150], 0x3d23d70a
005b8df2 movd xmm0, eax
005b8df6 cvtdq2pd xmm0, xmm0
005b8dfa shr eax, 0x1f
005b8dfd addsd xmm0, qword ptr [eax*8 + 0xb6c940]
005b8e06 cvtpd2ps xmm1, xmm0
005b8e0a movss xmm0, dword ptr [0xb6a614]
005b8e12 mulss xmm1, dword ptr [0xb6a19c]
005b8e1a mulss xmm1, dword ptr [0xb6a9ac]
005b8e22 subss xmm0, xmm1
005b8e26 movss dword ptr [esi + 0x364], xmm0
005b8e2e jmp 0x5ba1ff
005b8e33 cmp ecx, 0x47
005b8e36 je 0x5b9f91
005b8e3c cmp ecx, 0x6e
005b8e3f je 0x5b9f91
005b8e45 cmp ecx, 0x7e
005b8e48 jne 0x5b8f77
005b8e4e call 0x6c3d90
005b8e53 and eax, 3
005b8e56 movd xmm0, eax
005b8e5a cvtdq2pd xmm0, xmm0
005b8e5e shr eax, 0x1f
005b8e61 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
005b8e6a cvtpd2ps xmm0, xmm0
005b8e6e mulss xmm0, dword ptr [0xb6aae4]
005b8e76 movss dword ptr [esi + 0xe0], xmm0
005b8e7e call 0x6c3d90
005b8e83 xor al, 0xff
005b8e85 lea ecx, [esi + 0x3c]
005b8e88 and al, 1
005b8e8a push 1
005b8e8c mov byte ptr [esi + 0x13c], al
005b8e92 call 0x4062c0
005b8e97 mov byte ptr [eax + 0x74], 0
005b8e9b cmp dword ptr [esi + 0x30], 1
005b8e9f jne 0x5b8f0c
005b8ea1 mov dword ptr [esi + 0x3ac], 0x3c
005b8eab mov dword ptr [esi + 0x3b0], 0x3c
005b8eb5 call 0x6c3d90
005b8eba movss xmm3, dword ptr [0xb6a614]
005b8ec2 push ecx
005b8ec3 movd xmm0, eax
005b8ec7 cvtdq2pd xmm0, xmm0
005b8ecb shr eax, 0x1f
005b8ece addsd xmm0, qword ptr [eax*8 + 0xb6c940]
005b8ed7 cvtpd2ps xmm0, xmm0
005b8edb mulss xmm0, dword ptr [0xb6a19c]
005b8ee3 mulss xmm0, dword ptr [0xb6a350]
005b8eeb addss xmm0, dword ptr [0xb6a5a4]
005b8ef3 movss dword ptr [esp], xmm0
005b8ef8 push 0
005b8efa push 2
005b8efc push ecx
005b8efd push 0x22d
005b8f02 call 0x8b14e0
005b8f07 jmp 0x5ba1ff
005b8f0c mov dword ptr [esi + 0x3ac], 0x5a
005b8f16 mov dword ptr [esi + 0x3b0], 0x5a
005b8f20 call 0x6c3d90
005b8f25 movss xmm3, dword ptr [0xb6a4c4]
005b8f2d push ecx
005b8f2e movd xmm0, eax
005b8f32 cvtdq2pd xmm0, xmm0
005b8f36 shr eax, 0x1f
005b8f39 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
005b8f42 cvtpd2ps xmm0, xmm0
005b8f46 mulss xmm0, dword ptr [0xb6a19c]
005b8f4e mulss xmm0, dword ptr [0xb6a3b0]
005b8f56 addss xmm0, dword ptr [0xb6a840]
005b8f5e movss dword ptr [esp], xmm0
005b8f63 push 0
005b8f65 push 2
005b8f67 push ecx
005b8f68 push 0x110
005b8f6d call 0x8b14e0
005b8f72 jmp 0x5ba1ff
005b8f77 cmp ecx, 0x7f
005b8f7a je 0x5b9db6
005b8f80 cmp ecx, 0x48
005b8f83 jne 0x5b8fba
005b8f85 mov byte ptr [esi + 0x169], dl
005b8f8b mov dword ptr [esi + 0x3ac], 0xf0
005b8f95 movss xmm0, dword ptr [0xc02fec]
005b8f9d movss dword ptr [esi + 0x28c], xmm0
005b8fa5 movss xmm0, dword ptr [0xc02ff0]
005b8fad movss dword ptr [esi + 0x290], xmm0
005b8fb5 jmp 0x5ba1ff
005b8fba cmp ecx, 0x49
005b8fbd jne 0x5b8fd4
005b8fbf mov byte ptr [esi + 0x169], dl
005b8fc5 mov dword ptr [esi + 0x3ac], 8
005b8fcf jmp 0x5ba1ff
005b8fd4 cmp ecx, 0x4a
005b8fd7 jne 0x5b901d
005b8fd9 mov eax, dword ptr [0xbfd65c]
005b8fde mov dword ptr [esi + 0x2b4], edx
005b8fe4 mov dword ptr [esi + 0x17c], edi
005b8fea mov dword ptr [esi + 0x180], 1
005b8ff4 mov eax, dword ptr [eax + 0x18190]
005b8ffa cmp dword ptr [eax + 8], 0x13
005b8ffe jne 0x5ba1ff
005b9004 push 0xb45308
005b9009 lea ecx, [ebp - 0x38]
005b900c call 0x407990
005b9011 mov dword ptr [ebp - 4], 0xe
005b9018 jmp 0x5b96b0
005b901d cmp ecx, 0x4b
005b9020 jne 0x5b9054
005b9022 push 0
005b9024 push 0xb453c0
005b9029 lea ecx, [esi + 0x3c]
005b902c mov dword ptr [esi + 0x3ac], 0x32
005b9036 mov dword ptr [esi + 0x368], 0x3fa66666
005b9040 mov dword ptr [esi + 0x364], 0x3f000000
005b904a call 0x4054f0
005b904f jmp 0x5ba1ff
005b9054 cmp ecx, 0x4c
005b9057 jne 0x5b9095
005b9059 cmp dword ptr [esi + 0x30], 5
005b905d lea eax, [esi + 0x30]
005b9060 lea ecx, [ebp - 0xac]
005b9066 mov dword ptr [ebp - 0xac], 5
005b9070 cmovb ecx, eax
005b9073 push 0
005b9075 mov eax, dword ptr [ecx]
005b9077 lea ecx, [esi + 0x3c]
005b907a push dword ptr [eax*4 + 0xb4598c]
005b9081 call 0x4054f0
005b9086 mov dword ptr [esi + 0x2b4], 0
005b9090 jmp 0x5ba1ff
005b9095 cmp ecx, 0x24
005b9098 jne 0x5b90d1
005b909a mov eax, dword ptr [0xbfd65c]
005b909f mov ecx, dword ptr [eax + 0x18190]
005b90a5 imul eax, dword ptr [ecx + 0x1e84], 0x13c
005b90af add ecx, 0x1f90
005b90b5 add eax, ecx
005b90b7 lea ecx, [esi + 0x3c]
005b90ba push eax
005b90bb push 0
005b90bd call 0x407340
005b90c2 mov dword ptr [esi + 0x2b4], 1
005b90cc jmp 0x5ba1ff
005b90d1 cmp ecx, 0x1d
005b90d4 jne 0x5b9105
005b90d6 movss xmm0, dword ptr [0xc02fec]
005b90de movss dword ptr [esi + 0x28c], xmm0
005b90e6 movss xmm0, dword ptr [0xc02ff0]
005b90ee movss dword ptr [esi + 0x290], xmm0
005b90f6 mov dword ptr [esi + 0x2e0], 0x43960000
005b9100 jmp 0x5ba1ff
005b9105 cmp ecx, 0x13
005b9108 jne 0x5b9119
005b910a mov dword ptr [esi + 0x2e0], 0x41a00000
005b9114 jmp 0x5ba1ff
005b9119 cmp ecx, 0x51
005b911c jne 0x5b9147
005b911e mov dword ptr [esi + 0x364], edx
005b9124 mov dword ptr [esi + 0x360], 0xc2700000
005b912e mov dword ptr [esi + 0x2a8], 0xc2700000
005b9138 mov dword ptr [esi + 0x17c], 6
005b9142 jmp 0x5ba1ff
005b9147 cmp ecx, 0x52
005b914a jne 0x5b932b
005b9150 cmp dword ptr [esi + 0x30], 1
005b9154 jne 0x5b9191
005b9156 push 0xb453a0
005b915b lea ecx, [ebp - 0x38]
005b915e call 0x407990
005b9163 lea eax, [ebp - 0x38]
005b9166 mov dword ptr [ebp - 4], 0xf
005b916d lea edi, [esi + 0x3c]
005b9170 push eax
005b9171 push 0
005b9173 mov ecx, edi
005b9175 mov dword ptr [ebp - 0xac], edi
005b917b call 0x407340
005b9180 lea ecx, [ebp - 0x38]
005b9183 mov dword ptr [ebp - 4], 0xffffffff
005b918a call 0x407be0
005b918f jmp 0x5b919a
005b9191 lea edi, [esi + 0x3c]
005b9194 mov dword ptr [ebp - 0xac], edi
005b919a push 0
005b919c push 0xb41d90
005b91a1 mov ecx, edi
005b91a3 mov dword ptr [esi + 0x2b4], 0
005b91ad mov dword ptr [esi + 0x3a0], 0
005b91b7 call 0x4054f0
005b91bc mov eax, dword ptr [esi + 0x30]
005b91bf mov edi, dword ptr [0xbfd65c]
005b91c5 dec eax
005b91c6 and eax, 1
005b91c9 mov ecx, edi
005b91cb push -1
005b91cd lea eax, [eax + eax*2]
005b91d0 push dword ptr [edi + eax*4 + 0x18208]
005b91d7 mov dword ptr [ebp - 0xb0], eax
005b91dd call 0x70e0f0
005b91e2 mov ecx, dword ptr [0xbfd65c]
005b91e8 mov esi, eax
005b91ea call 0x70e2d0
005b91ef cmp esi, eax
005b91f1 mov eax, dword ptr [ebp - 0xb0]
005b91f7 sete cl
005b91fa cmp dword ptr [edi + eax*4 + 0x18208], 0
005b9202 jge 0x5b9208
005b9204 test cl, cl
005b9206 je 0x5b920a
005b9208 mov cl, 1
005b920a test cl, cl
005b920c mov edx, 0xb41d90
005b9211 mov ecx, dword ptr [ebp - 0xac]
005b9217 mov eax, 0xb41d88
005b921c push 0
005b921e cmove eax, edx
005b9221 push eax
005b9222 call 0x4054f0
005b9227 mov esi, dword ptr [ebp - 0xa8]
005b922d mov ecx, dword ptr [0xbfd65c]
005b9233 mov eax, dword ptr [esi + 0x30]
005b9236 add eax, 0x202c
005b923b lea eax, [eax + eax*2]
005b923e cmp byte ptr [ecx + eax*4], 0
005b9242 je 0x5ba1ff
005b9248 push 1
005b924a push 0
005b924c lea eax, [esi + 0x294]
005b9252 push eax
005b9253 push 0x18c
005b9258 push 0
005b925a call 0x412750
005b925f mov ecx, eax
005b9261 call 0x5b4730
005b9266 mov edi, eax
005b9268 test edi, edi
005b926a je 0x5ba1ff
005b9270 push esi
005b9271 mov ecx, edi
005b9273 call 0x6818e0
005b9278 cmp dword ptr [esi + 0x30], 0
005b927c je 0x5b92e2
005b927e push 0
005b9280 push 0
005b9282 push 0
005b9284 push 0xff
005b9289 push 0x3c
005b928b push 0xfa
005b9290 push 0x190
005b9295 lea ecx, [ebp - 0x4c]
005b9298 call 0x447b90
005b929d push eax
005b929e push 0
005b92a0 lea ecx, [edi + 0x3c]
005b92a3 call 0x4062c0
005b92a8 lea ecx, [eax + 0x48]
005b92ab call 0x4021a0
005b92b0 push 0
005b92b2 push 0
005b92b4 push 0
005b92b6 push 0xff
005b92bb push 0xa
005b92bd push 0xc8
005b92c2 push 0x12c
005b92c7 lea ecx, [ebp - 0x4c]
005b92ca call 0x447b90
005b92cf push eax
005b92d0 push 1
005b92d2 lea ecx, [edi + 0x3c]
005b92d5 call 0x4062c0
005b92da lea ecx, [eax + 0x48]
005b92dd call 0x4021a0
005b92e2 push 9
005b92e4 mov ecx, edi
005b92e6 call 0x61b090
005b92eb mov eax, dword ptr [0xbfd65c]
005b92f0 mov ecx, dword ptr [eax + 0x18190]
005b92f6 cmp byte ptr [ecx], 0
005b92f9 je 0x5b930c
005b92fb mov eax, dword ptr [eax + 0x1a30dc]
005b9301 sub eax, dword ptr [ecx + 0x11f0]
005b9307 cmp eax, 2
005b930a jge 0x5b931f
005b930c mov eax, dword ptr [edi + 0x164]
005b9312 and dword ptr [edi + 0x160], 0xfffffffb
005b9319 mov dword ptr [edi + 0x164], eax
005b931f mov eax, dword ptr [edi]
005b9321 mov ecx, edi
005b9323 call dword ptr [eax + 0xc]
005b9326 jmp 0x5ba1ff
005b932b cmp ecx, 0x57
005b932e jne 0x5b93ad
005b9330 push 2
005b9332 lea ecx, [ebp - 0x20]
005b9335 call 0x95ed30
005b933a push 0
005b933c lea ecx, [esi + 0x3c]
005b933f call 0x4062c0
005b9344 mov ecx, dword ptr [ebp - 0x20]
005b9347 mov dword ptr [eax + 0x78], ecx
005b934a mov ecx, dword ptr [ebp - 0x1c]
005b934d mov dword ptr [eax + 0x7c], ecx
005b9350 mov ecx, dword ptr [ebp - 0x18]
005b9353 mov dword ptr [eax + 0x80], ecx
005b9359 mov ecx, dword ptr [ebp - 0x14]
005b935c mov dword ptr [eax + 0x84], ecx
005b9362 lea ecx, [esi + 0x334]
005b9368 call 0x7a7db0
005b936d fld dword ptr [0xb6a480]
005b9373 fmul st(1), st(0)
005b9375 faddp st(1)
005b9377 fstp dword ptr [ebp - 0xac]
005b937d movss xmm1, dword ptr [ebp - 0xac]
005b9385 movaps xmm0, xmm1
005b9388 mulss xmm1, dword ptr [0xbc7a2c]
005b9390 mulss xmm0, dword ptr [0xbc7a28]
005b9398 movss dword ptr [esi + 0xdc], xmm1
005b93a0 movss dword ptr [esi + 0xd8], xmm0
005b93a8 jmp 0x5ba1ff
005b93ad cmp ecx, 0x58
005b93b0 jne 0x5b941b
005b93b2 cmp dword ptr [esi + 0x30], 1
005b93b6 jne 0x5b93ed
005b93b8 push 0xb45378
005b93bd lea ecx, [ebp - 0x38]
005b93c0 call 0x407990
005b93c5 lea eax, [ebp - 0x38]
005b93c8 mov dword ptr [ebp - 4], 0x10
005b93cf push eax
005b93d0 lea edi, [esi + 0x3c]
005b93d3 push 0
005b93d5 mov ecx, edi
005b93d7 call 0x407340
005b93dc lea ecx, [ebp - 0x38]
005b93df mov dword ptr [ebp - 4], 0xffffffff
005b93e6 call 0x407be0
005b93eb jmp 0x5b93f0
005b93ed lea edi, [esi + 0x3c]
005b93f0 call 0x6c3d90
005b93f5 push eax
005b93f6 mov ecx, edi
005b93f8 call 0x405420
005b93fd call 0x6c3d90
005b9402 xor al, 0xff
005b9404 mov dword ptr [esi + 0x2ac], 0xfffffc18
005b940e and al, 1
005b9410 mov byte ptr [esi + 0x13c], al
005b9416 jmp 0x5ba1ff
005b941b cmp ecx, 0x5b
005b941e jne 0x5b944f
005b9420 push 0
005b9422 push 0xb40884
005b9427 lea ecx, [esi + 0x3c]
005b942a call 0x4054f0
005b942f movss xmm2, dword ptr [0xb6a614]
005b9437 push ecx
005b9438 mov dword ptr [esp], 0x3f800000
005b943f push 0
005b9441 push 2
005b9443 push 2
005b9445 call 0x8b1480
005b944a jmp 0x5ba1ff
005b944f cmp ecx, 0x63
005b9452 jne 0x5b9685
005b9458 cmp dword ptr [esi + 0x30], edx
005b945b jne 0x5b9591
005b9461 mov eax, dword ptr [0xbfd65c]
005b9466 lea ecx, [esi + 0x3c]
005b9469 mov eax, dword ptr [eax + 0x18190]
005b946f add eax, 0x1cf0
005b9474 push eax
005b9475 call 0x402370
005b947a call 0x6c3d90
005b947f movss xmm3, dword ptr [0xb6a19c]
005b9487 movd xmm0, eax
005b948b cvtdq2pd xmm0, xmm0
005b948f shr eax, 0x1f
005b9492 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
005b949b cvtpd2ps xmm0, xmm0
005b949f mulss xmm0, xmm3
005b94a3 mulss xmm0, dword ptr [0xb6a304]
005b94ab addss xmm0, dword ptr [0xb6a274]
005b94b3 movss dword ptr [esi + 0xf0], xmm0
005b94bb call 0x6c3d90
005b94c0 xor al, 0xff
005b94c2 and al, 1
005b94c4 mov byte ptr [esi + 0x13c], al
005b94ca call 0x6c3d90
005b94cf movss xmm4, dword ptr [0xb6a480]
005b94d7 movd xmm0, eax
005b94db cvtdq2pd xmm0, xmm0
005b94df shr eax, 0x1f
005b94e2 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
005b94eb cvtpd2ps xmm1, xmm0
005b94ef mulss xmm1, xmm3
005b94f3 mulss xmm1, dword ptr [0xb6a350]
005b94fb addss xmm1, xmm4
005b94ff movaps xmm0, xmm1
005b9502 mulss xmm1, dword ptr [0xbc7a2c]
005b950a mulss xmm0, dword ptr [0xbc7a28]
005b9512 movss dword ptr [esi + 0xdc], xmm1
005b951a movss dword ptr [esi + 0xd8], xmm0
005b9522 call 0x6c3d90
005b9527 movd xmm0, eax
005b952b cvtdq2pd xmm0, xmm0
005b952f shr eax, 0x1f
005b9532 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
005b953b cvtpd2ps xmm1, xmm0
005b953f mulss xmm1, xmm3
005b9543 call 0x6c3d90
005b9548 addss xmm1, xmm1
005b954c push ecx
005b954d movd xmm0, eax
005b9551 cvtdq2pd xmm0, xmm0
005b9555 shr eax, 0x1f
005b9558 addss xmm1, dword ptr [0xb6a614]
005b9560 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
005b9569 movss dword ptr [esp], xmm1
005b956e cvtpd2ps xmm2, xmm0
005b9572 push 0
005b9574 push 2
005b9576 push 0x18e
005b957b mulss xmm2, xmm3
005b957f mulss xmm2, xmm4
005b9583 addss xmm2, xmm4
005b9587 call 0x8b1480
005b958c jmp 0x5ba1ff
005b9591 mov dword ptr [esi + 0x368], 0x3f000000
005b959b call 0x6c3d90
005b95a0 mov dword ptr [esi + 0x360], 0xc1200000
005b95aa movd xmm0, eax
005b95ae cvtdq2pd xmm0, xmm0
005b95b2 shr eax, 0x1f
005b95b5 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
005b95be cvtpd2ps xmm1, xmm0
005b95c2 movss xmm0, dword ptr [0xb6ae44]
005b95ca mulss xmm1, xmm2
005b95ce addss xmm1, xmm1
005b95d2 subss xmm0, xmm1
005b95d6 movss dword ptr [esi + 0x364], xmm0
005b95de call 0x6c3d90
005b95e3 lea ecx, [esi + 0x3c]
005b95e6 movd xmm0, eax
005b95ea cvtdq2pd xmm0, xmm0
005b95ee shr eax, 0x1f
005b95f1 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
005b95fa mov eax, dword ptr [0xbfd65c]
005b95ff cvtpd2ps xmm1, xmm0
005b9603 mulss xmm1, xmm2
005b9607 mulss xmm1, xmm3
005b960b addss xmm1, xmm3
005b960f movaps xmm0, xmm1
005b9612 mulss xmm1, dword ptr [0xbc7a2c]
005b961a mulss xmm0, dword ptr [0xbc7a28]
005b9622 movss dword ptr [esi + 0xdc], xmm1
005b962a movss dword ptr [esi + 0xd8], xmm0
005b9632 mov eax, dword ptr [eax + 0x18190]
005b9638 add eax, 0x1cf0
005b963d push eax
005b963e call 0x402370
005b9643 call 0x6c3d90
005b9648 movd xmm0, eax
005b964c cvtdq2pd xmm0, xmm0
005b9650 shr eax, 0x1f
005b9653 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
005b965c cvtpd2ps xmm0, xmm0
005b9660 mulss xmm0, dword ptr [0xb6a19c]
005b9668 mulss xmm0, dword ptr [0xb6a3b0]
005b9670 addss xmm0, dword ptr [0xb6a2cc]
005b9678 movss dword ptr [esi + 0xf0], xmm0
005b9680 jmp 0x5ba1ff
005b9685 cmp ecx, 0x53
005b9688 jne 0x5b96d2
005b968a mov eax, dword ptr [0xbfd65c]
005b968f cmp dword ptr [eax + 0x1c319c], 0x1e
005b9696 jne 0x5ba1ff
005b969c push 0xb45350
005b96a1 lea ecx, [ebp - 0x38]
005b96a4 call 0x407990
005b96a9 mov dword ptr [ebp - 4], 0x11
005b96b0 lea eax, [ebp - 0x38]
005b96b3 push eax
005b96b4 push 0
005b96b6 lea ecx, [esi + 0x3c]
005b96b9 call 0x407340
005b96be lea ecx, [ebp - 0x38]
005b96c1 mov dword ptr [ebp - 4], 0xffffffff
005b96c8 call 0x407be0
005b96cd jmp 0x5ba1ff
005b96d2 cmp ecx, 0x35
005b96d5 jne 0x5b96e6
005b96d7 mov dword ptr [esi + 0x3ac], 0x19
005b96e1 jmp 0x5ba1ff
005b96e6 cmp ecx, 0x68
005b96e9 jne 0x5b98c4
005b96ef mov eax, dword ptr [esi + 0x30]
005b96f2 test eax, eax
005b96f4 jne 0x5b9701
005b96f6 mov byte ptr [esi + 0x169], dl
005b96fc jmp 0x5b983e
005b9701 cmp eax, 1
005b9704 jne 0x5b980a
005b970a push 0
005b970c push 0xb45400
005b9711 lea ecx, [esi + 0x3c]
005b9714 call 0x4054f0
005b9719 call 0x6c3d90
005b971e movss xmm1, dword ptr [0xb6a19c]
005b9726 movd xmm0, eax
005b972a cvtdq2pd xmm0, xmm0
005b972e shr eax, 0x1f
005b9731 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
005b973a cvtpd2ps xmm0, xmm0
005b973e mulss xmm0, xmm1
005b9742 mulss xmm0, dword ptr [0xb6a8cc]
005b974a addss xmm0, dword ptr [0xb6a98c]
005b9752 xorps xmm0, xmmword ptr [0xb6c9b0]
005b9759 movss dword ptr [esi + 0x360], xmm0
005b9761 call 0x6c3d90
005b9766 movd xmm0, eax
005b976a cvtdq2pd xmm0, xmm0
005b976e shr eax, 0x1f
005b9771 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
005b977a cvtpd2ps xmm2, xmm0
005b977e mulss xmm2, xmm1
005b9782 call 0x6c3d90
005b9787 movd xmm0, eax
005b978b cvtdq2pd xmm0, xmm0
005b978f shr eax, 0x1f
005b9792 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
005b979b cvtpd2ps xmm5, xmm0
005b979f mulss xmm5, xmm1
005b97a3 call 0x6c3d90
005b97a8 movss xmm4, dword ptr [0xb6a614]
005b97b0 lea ecx, [ebp - 0x4c]
005b97b3 mov edx, dword ptr [esi]
005b97b5 push 1
005b97b7 movd xmm0, eax
005b97bb cvtdq2pd xmm0, xmm0
005b97bf shr eax, 0x1f
005b97c2 push 0
005b97c4 push 0xff
005b97c9 push -1
005b97cb addsd xmm0, qword ptr [eax*8 + 0xb6c940]
005b97d4 cvtpd2ps xmm3, xmm0
005b97d8 movaps xmm0, xmm5
005b97db mulss xmm3, xmm1
005b97df addss xmm0, xmm2
005b97e3 addss xmm0, xmm3
005b97e7 divss xmm4, xmm0
005b97eb movaps xmm1, xmm4
005b97ee mulss xmm3, xmm4
005b97f2 mulss xmm1, xmm2
005b97f6 movaps xmm2, xmm4
005b97f9 mulss xmm2, xmm5
005b97fd call 0x427080
005b9802 push eax
005b9803 mov ecx, esi
005b9805 call dword ptr [edx + 0x38]
005b9808 jmp 0x5b9836
005b980a cmp eax, 2
005b980d jne 0x5b9818
005b980f push 0
005b9811 push 0xb42eec
005b9816 jmp 0x5b982e
005b9818 cmp eax, 3
005b981b jb 0x5b983e
005b981d call 0x6c3d90
005b9822 and eax, 3
005b9825 push 0
005b9827 push dword ptr [eax*4 + 0xb45a54]
005b982e lea ecx, [esi + 0x3c]
005b9831 call 0x4054f0
005b9836 movss xmm2, dword ptr [0xb6a19c]
005b983e cmp dword ptr [esi + 0x30], 1
005b9842 je 0x5b987d
005b9844 call 0x6c3d90
005b9849 movd xmm0, eax
005b984d cvtdq2pd xmm0, xmm0
005b9851 shr eax, 0x1f
005b9854 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
005b985d cvtpd2ps xmm0, xmm0
005b9861 mulss xmm0, xmm2
005b9865 mulss xmm0, dword ptr [0xb6ac40]
005b986d subss xmm0, dword ptr [0xb6ab88]
005b9875 movss dword ptr [esi + 0xe0], xmm0
005b987d push 2
005b987f lea ecx, [ebp - 0xd0]
005b9885 call 0x95ed30
005b988a mov ecx, dword ptr [ebp - 0xa8]
005b9890 lea ecx, [ecx + 0x3c]
005b9893 push 0
005b9895 mov esi, eax
005b9897 call 0x4062c0
005b989c mov ecx, dword ptr [esi]
005b989e mov dword ptr [eax + 0x78], ecx
005b98a1 mov ecx, dword ptr [esi + 4]
005b98a4 mov dword ptr [eax + 0x7c], ecx
005b98a7 mov ecx, dword ptr [esi + 8]
005b98aa mov dword ptr [eax + 0x80], ecx
005b98b0 mov ecx, dword ptr [esi + 0xc]
005b98b3 mov esi, dword ptr [ebp - 0xa8]
005b98b9 mov dword ptr [eax + 0x84], ecx
005b98bf jmp 0x5ba1ff
005b98c4 cmp ecx, 0x69
005b98c7 jne 0x5b98e7
005b98c9 push 0
005b98cb push 0xb453f4
005b98d0 lea ecx, [esi + 0x3c]
005b98d3 call 0x4054f0
005b98d8 mov dword ptr [esi + 0x2ac], 0x3e8
005b98e2 jmp 0x5ba1ff
005b98e7 cmp ecx, 0x6a
005b98ea jne 0x5b9914
005b98ec push 0
005b98ee push 0xb40360
005b98f3 lea ecx, [esi + 0x3c]
005b98f6 call 0x4054f0
005b98fb mov dword ptr [esi + 0x2ac], 0x3e8
005b9905 mov dword ptr [esi + 0x2a8], 0xc1a00000
005b990f jmp 0x5ba1ff
005b9914 cmp ecx, 0x27
005b9917 jne 0x5b9a5b
005b991d or dword ptr [esi + 0x160], 0x200000
005b9927 cmp dword ptr [esi + 0x30], 1
005b992b mov eax, dword ptr [esi + 0x164]
005b9931 mov dword ptr [esi + 0x164], eax
005b9937 jne 0x5ba1ff
005b993d cmp dword ptr [esi + 0x34], edx
005b9940 jne 0x5b9a50
005b9946 lea edi, [esi + 0x3c]
005b9949 push 0
005b994b mov ecx, edi
005b994d call 0x4062c0
005b9952 push 0
005b9954 mov ecx, edi
005b9956 mov dword ptr [eax + 0x20], 1
005b995d call 0x4062c0
005b9962 push 2
005b9964 mov ecx, edi
005b9966 mov dword ptr [eax + 0x24], 1
005b996d call 0x4062c0
005b9972 push 2
005b9974 mov ecx, edi
005b9976 mov dword ptr [eax + 0x20], 1
005b997d call 0x4062c0
005b9982 push 2
005b9984 lea ecx, [ebp - 0xd0]
005b998a mov dword ptr [eax + 0x24], 1
005b9991 call 0x95ed30
005b9996 push 0
005b9998 mov ecx, edi
005b999a mov esi, eax
005b999c call 0x4062c0
005b99a1 mov ecx, dword ptr [esi]
005b99a3 push 2
005b99a5 mov dword ptr [eax + 0x78], ecx
005b99a8 mov ecx, dword ptr [esi + 4]
005b99ab mov dword ptr [eax + 0x7c], ecx
005b99ae mov ecx, dword ptr [esi + 8]
005b99b1 mov dword ptr [eax + 0x80], ecx
005b99b7 mov ecx, dword ptr [esi + 0xc]
005b99ba mov dword ptr [eax + 0x84], ecx
005b99c0 lea ecx, [ebp - 0xd0]
005b99c6 call 0x95ed30
005b99cb push 2
005b99cd mov ecx, edi
005b99cf mov esi, eax
005b99d1 call 0x4062c0
005b99d6 mov edx, dword ptr [esi]
005b99d8 mov ecx, edi
005b99da push 2
005b99dc mov dword ptr [eax + 0x78], edx
005b99df mov edx, dword ptr [esi + 4]
005b99e2 mov dword ptr [eax + 0x7c], edx
005b99e5 mov edx, dword ptr [esi + 8]
005b99e8 mov dword ptr [eax + 0x80], edx
005b99ee mov edx, dword ptr [esi + 0xc]
005b99f1 mov dword ptr [eax + 0x84], edx
005b99f7 call 0x4062c0
005b99fc mov edi, dword ptr [ebp - 0xa8]
005b9a02 mov ecx, dword ptr [0xbfd65c]
005b9a08 mov byte ptr [eax + 0x74], 0
005b9a0c push dword ptr [edi + 0x344]
005b9a12 lea eax, [edi + 0x294]
005b9a18 push dword ptr [edi + 0x30]
005b9a1b push edi
005b9a1c push 0xc02fec
005b9a21 push eax
005b9a22 push dword ptr [edi + 0x2c]
005b9a25 push dword ptr [edi + 0x28]
005b9a28 call 0x422e20
005b9a2d mov esi, eax
005b9a2f mov ecx, edi
005b9a31 push esi
005b9a32 call 0x681920
005b9a37 push edi
005b9a38 mov ecx, esi
005b9a3a call 0x6818e0
005b9a3f mov esi, edi
005b9a41 mov dword ptr [esi + 0x2b0], 0x41200000
005b9a4b jmp 0x5ba1ff
005b9a50 mov dword ptr [esi + 0x2b4], edx
005b9a56 jmp 0x5ba1ff
005b9a5b cmp ecx, 0x7b
005b9a5e jne 0x5b9b52
005b9a64 mov eax, dword ptr [esi + 0x30]
005b9a67 cmp eax, 3
005b9a6a jne 0x5b9aa7
005b9a6c push 0
005b9a6e lea ecx, [esi + 0x3c]
005b9a71 call 0x4062c0
005b9a76 mov dword ptr [eax + 0x78], 0
005b9a7d mov dword ptr [eax + 0x7c], 2
005b9a84 mov dword ptr [eax + 0x80], 0
005b9a8e mov dword ptr [eax + 0x84], 2
005b9a98 mov dword ptr [esi + 0x2ac], 0xfffffc18
005b9aa2 jmp 0x5ba1ff
005b9aa7 cmp eax, 4
005b9aaa jne 0x5b9ae5
005b9aac or dword ptr [esi + 0x14c], 0x20
005b9ab3 lea ecx, [ebp - 0x154]
005b9ab9 push 2
005b9abb call 0x95ed30
005b9ac0 push 0
005b9ac2 lea ecx, [esi + 0x3c]
005b9ac5 mov edi, eax
005b9ac7 call 0x4062c0
005b9acc mov ecx, dword ptr [edi]
005b9ace mov dword ptr [eax + 0x78], ecx
005b9ad1 mov ecx, dword ptr [edi + 4]
005b9ad4 mov dword ptr [eax + 0x7c], ecx
005b9ad7 mov ecx, dword ptr [edi + 8]
005b9ada mov dword ptr [eax + 0x80], ecx
005b9ae0 mov ecx, dword ptr [edi + 0xc]
005b9ae3 jmp 0x5b9b37
005b9ae5 cmp eax, 7
005b9ae8 jne 0x5b9afc
005b9aea or dword ptr [esi + 0x14c], 0x100
005b9af4 lea ecx, [ebp - 0x164]
005b9afa jmp 0x5b9ab9
005b9afc cmp eax, 9
005b9aff jne 0x5b9b43
005b9b01 push 2
005b9b03 lea ecx, [ebp - 0x138]
005b9b09 call 0x95ed30
005b9b0e mov ecx, dword ptr [ebp - 0xa8]
005b9b14 mov esi, eax
005b9b16 push 1
005b9b18 lea ecx, [ecx + 0x3c]
005b9b1b call 0x4062c0
005b9b20 mov ecx, dword ptr [esi]
005b9b22 mov dword ptr [eax + 0x78], ecx
005b9b25 mov ecx, dword ptr [esi + 4]
005b9b28 mov dword ptr [eax + 0x7c], ecx
005b9b2b mov ecx, dword ptr [esi + 8]
005b9b2e mov dword ptr [eax + 0x80], ecx
005b9b34 mov ecx, dword ptr [esi + 0xc]
005b9b37 mov esi, dword ptr [ebp - 0xa8]
005b9b3d mov dword ptr [eax + 0x84], ecx
005b9b43 mov dword ptr [esi + 0x2ac], 0xfffffc18
005b9b4d jmp 0x5ba1ff
005b9b52 cmp ecx, 0x6b
005b9b55 jne 0x5b9b8d
005b9b57 lea ecx, [esi + 0x3c]
005b9b5a cmp dword ptr [esi + 0x30], edx
005b9b5d jne 0x5b9b7b
005b9b5f mov eax, 0xb40518
005b9b64 mov dword ptr [esi + 0x2a8], 0xc2000000
005b9b6e push 0
005b9b70 push eax
005b9b71 call 0x4054f0
005b9b76 jmp 0x5ba1ff
005b9b7b mov eax, 0xb3fd8c
005b9b80 push 0
005b9b82 push eax
005b9b83 call 0x4054f0
005b9b88 jmp 0x5ba1ff
005b9b8d cmp ecx, 0x6c
005b9b90 jne 0x5b9bd5
005b9b92 push 0x124
005b9b97 call 0x9eacf8
005b9b9c add esp, 4
005b9b9f mov dword ptr [ebp - 0xac], eax
005b9ba5 mov ecx, eax
005b9ba7 mov dword ptr [ebp - 4], 0x12
005b9bae call 0x5b7790
005b9bb3 push eax
005b9bb4 lea ecx, [esi + 0x3d8]
005b9bba mov dword ptr [ebp - 4], 0xffffffff
005b9bc1 call 0x5eeac0
005b9bc6 mov dword ptr [esi + 0x3a0], 0
005b9bd0 jmp 0x5ba1ff
005b9bd5 cmp ecx, 0x6d
005b9bd8 je 0x5b9f7d
005b9bde cmp ecx, 0x6f
005b9be1 jne 0x5b9bf7
005b9be3 push 0
005b9be5 push 0xb4030c
005b9bea lea ecx, [esi + 0x3c]
005b9bed call 0x4054f0
005b9bf2 jmp 0x5ba1ff
005b9bf7 cmp ecx, 0x70
005b9bfa jne 0x5b9c58
005b9bfc push 2
005b9bfe lea ecx, [ebp - 0x138]
005b9c04 call 0x95ed30
005b9c09 mov edi, dword ptr [ebp - 0xa8]
005b9c0f mov esi, eax
005b9c11 push 0
005b9c13 lea ecx, [edi + 0x3c]
005b9c16 call 0x4062c0
005b9c1b mov edx, dword ptr [esi]
005b9c1d lea ecx, [edi + 0x3c]
005b9c20 push 0
005b9c22 push 0xb40360
005b9c27 mov dword ptr [eax + 0x78], edx
005b9c2a mov edx, dword ptr [esi + 4]
005b9c2d mov dword ptr [eax + 0x7c], edx
005b9c30 mov edx, dword ptr [esi + 8]
005b9c33 mov dword ptr [eax + 0x80], edx
005b9c39 mov edx, dword ptr [esi + 0xc]
005b9c3c mov dword ptr [eax + 0x84], edx
005b9c42 call 0x4054f0
005b9c47 mov esi, edi
005b9c49 mov dword ptr [esi + 0x3a0], 0xffffffff
005b9c53 jmp 0x5ba1ff
005b9c58 cmp ecx, 0x71
005b9c5b je 0x5b9f7d
005b9c61 cmp ecx, 0x73
005b9c64 jne 0x5b9c8e
005b9c66 push 0
005b9c68 push 0xb3fd8c
005b9c6d lea ecx, [esi + 0x3c]
005b9c70 call 0x4054f0
005b9c75 mov dword ptr [esi + 0x2ac], 0x2710
005b9c7f mov dword ptr [esi + 0x3a0], 0
005b9c89 jmp 0x5b9dbc
005b9c8e cmp ecx, 0x74
005b9c91 jne 0x5b9d31
005b9c97 push 0
005b9c99 push 0xb3fd8c
005b9c9e lea ecx, [esi + 0x3c]
005b9ca1 call 0x4054f0
005b9ca6 mov eax, dword ptr [esi + 0x164]
005b9cac or dword ptr [esi + 0x160], 0x200000
005b9cb6 mov dword ptr [esi + 0x164], eax
005b9cbc mov eax, dword ptr [0xbfd65c]
005b9cc1 mov dword ptr [esi + 0x2b4], 0
005b9ccb mov dword ptr [esi + 0x3a0], 0
005b9cd5 mov dword ptr [esi + 0x3c0], 0
005b9cdf mov eax, dword ptr [eax + 0x18190]
005b9ce5 cmp dword ptr [eax + 0x1e84], 0x10
005b9cec jne 0x5ba1ff
005b9cf2 push 0xb453d0
005b9cf7 lea ecx, [ebp - 0x38]
005b9cfa call 0x407990
005b9cff lea eax, [ebp - 0x38]
005b9d02 mov dword ptr [ebp - 4], 0x13
005b9d09 push eax
005b9d0a push 0
005b9d0c lea ecx, [esi + 0x3c]
005b9d0f call 0x407340
005b9d14 lea ecx, [ebp - 0x38]
005b9d17 mov dword ptr [ebp - 4], 0xffffffff
005b9d1e call 0x407be0
005b9d23 push ecx
005b9d24 lea ecx, [esi + 0x3c]
005b9d27 call 0x4073a0
005b9d2c jmp 0x5ba1ff
005b9d31 cmp ecx, 0x75
005b9d34 jne 0x5b9d80
005b9d36 mov eax, dword ptr fs:[0x2c]
005b9d3c mov ecx, dword ptr [eax]
005b9d3e mov eax, dword ptr [0xc04a94]
005b9d43 cmp eax, dword ptr [ecx + 0xc]
005b9d49 jg 0x5bbf92
005b9d4f push 0xc04984
005b9d54 lea ecx, [esi + 0x3c]
005b9d57 call 0x402370
005b9d5c push 0
005b9d5e push 0xb453c4
005b9d63 lea ecx, [esi + 0x3c]
005b9d66 call 0x4054f0
005b9d6b mov esi, dword ptr [ebp - 0xa8]
005b9d71 mov dword ptr [esi + 0x3a0], 0
005b9d7b jmp 0x5ba1ff
005b9d80 cmp ecx, 0x77
005b9d83 jne 0x5b9d9b
005b9d85 mov dword ptr [esi + 0x374], 1
005b9d8f mov dword ptr [esi + 0x378], 1
005b9d99 jmp 0x5b9db0
005b9d9b cmp ecx, 0x78
005b9d9e jne 0x5b9dd7
005b9da0 mov dword ptr [esi + 0x374], edx
005b9da6 mov dword ptr [esi + 0x3a0], 0xffffffff
005b9db0 mov dword ptr [esi + 0x370], edx
005b9db6 mov byte ptr [esi + 0x169], dl
005b9dbc mov eax, dword ptr [esi + 0x164]
005b9dc2 or dword ptr [esi + 0x160], 0x200000
005b9dcc mov dword ptr [esi + 0x164], eax
005b9dd2 jmp 0x5ba1ff
005b9dd7 cmp ecx, 0x31
005b9dda jne 0x5b9dfe
005b9ddc mov eax, dword ptr [esi + 0x30]
005b9ddf cmp eax, 6
005b9de2 jae 0x5ba1ff
005b9de8 push 0
005b9dea push dword ptr [eax*4 + 0xb45940]
005b9df1 lea ecx, [esi + 0x3c]
005b9df4 call 0x4054f0
005b9df9 jmp 0x5ba1ff
005b9dfe cmp ecx, 0x79
005b9e01 jne 0x5b9e33
005b9e03 mov eax, dword ptr [esi + 0x164]
005b9e09 lea ecx, [esi + 0x3c]
005b9e0c or dword ptr [esi + 0x160], 0x200000
005b9e16 push 0
005b9e18 mov dword ptr [esi + 0x164], eax
005b9e1e mov dword ptr [esi + 0x3c8], edx
005b9e24 push 0xb45494
005b9e29 call 0x405850
005b9e2e jmp 0x5ba1ff
005b9e33 cmp ecx, 0x7c
005b9e36 jne 0x5b9e66
005b9e38 call 0x6c3d90
005b9e3d xor edx, edx
005b9e3f lea ecx, [esi + 0x3c]
005b9e42 div edi
005b9e44 push 0
005b9e46 push dword ptr [edx*4 + 0xb45a80]
005b9e4d call 0x4054f0
005b9e52 call 0x6c3d90
005b9e57 xor al, 0xff
005b9e59 and al, 1
005b9e5b mov byte ptr [esi + 0x13c], al
005b9e61 jmp 0x5ba1ff
005b9e66 cmp ecx, 0x7d
005b9e69 jne 0x5ba1ff
005b9e6f push 0
005b9e71 push 0xb40490
005b9e76 lea ecx, [esi + 0x3c]
005b9e79 call 0x4054f0
005b9e7e mov edi, dword ptr [ebp - 0xa8]
005b9e84 lea ecx, [esi + 0x3c]
005b9e87 push 0xb40368
005b9e8c mov dword ptr [edi + 0x3a0], 0
005b9e96 mov dword ptr [edi + 0x2b0], 0xc0a00000
005b9ea0 call 0x406350
005b9ea5 mov dword ptr [ebp - 0xb0], eax
005b9eab test eax, eax
005b9ead je 0x5b9fd1
005b9eb3 call 0x6c3d90
005b9eb8 mov ecx, dword ptr [0xbfd65c]
005b9ebe add edi, 0x294
005b9ec4 push eax
005b9ec5 mov eax, dword ptr [ebp - 0xa8]
005b9ecb push 0
005b9ecd push eax
005b9ece push 0xc02fec
005b9ed3 push edi
005b9ed4 push 0x7a
005b9ed6 push 0x3e8
005b9edb call 0x422e20
005b9ee0 push dword ptr [ebp - 0xa8]
005b9ee6 mov esi, eax
005b9ee8 mov ecx, esi
005b9eea call 0x6818e0
005b9eef mov ecx, dword ptr [ebp - 0xb0]
005b9ef5 call 0x444bd0
005b9efa mov dword ptr [esi + 0x3a0], eax
005b9f00 push esi
005b9f01 mov esi, dword ptr [ebp - 0xa8]
005b9f07 mov ecx, esi
005b9f09 call 0x681920
005b9f0e mov eax, dword ptr [ebp - 0xb0]
005b9f14 mov ecx, dword ptr [0xbfd65c]
005b9f1a push edi
005b9f1b mov byte ptr [eax + 0x74], 0
005b9f1f lea eax, [ebp - 0x20]
005b9f22 movss xmm3, dword ptr [esi + 0x2c8]
005b9f2a mov ecx, dword ptr [ecx + 0x18190]
005b9f30 push eax
005b9f31 call 0x7de530
005b9f36 movss xmm0, dword ptr [0xb6a7b0]
005b9f3e movss xmm3, dword ptr [ebp - 0x18]
005b9f43 movss xmm2, dword ptr [ebp - 0x1c]
005b9f48 movss xmm1, dword ptr [ebp - 0x20]
005b9f4d push ecx
005b9f4e mulss xmm3, xmm0
005b9f52 lea ecx, [ebp - 0x78]
005b9f55 mov dword ptr [esp], 0x3f800000
005b9f5c mulss xmm2, xmm0
005b9f60 mulss xmm1, xmm0
005b9f64 call 0x4325d0
005b9f69 mov ecx, dword ptr [ebp - 0xb0]
005b9f6f push eax
005b9f70 add ecx, 0x48
005b9f73 call 0x4021a0
005b9f78 jmp 0x5ba1ff
005b9f7d push 0
005b9f7f push 0xb40360
005b9f84 lea ecx, [esi + 0x3c]
005b9f87 call 0x4054f0
005b9f8c jmp 0x5ba1ff
005b9f91 push 1
005b9f93 lea ecx, [esi + 0x3c]
005b9f96 call 0x4062c0
005b9f9b push 1
005b9f9d lea ecx, [esi + 0x3c]
005b9fa0 mov dword ptr [eax + 0x20], 1
005b9fa7 call 0x4062c0
005b9fac mov dword ptr [eax + 0x24], 1
005b9fb3 cmp dword ptr [esi + 0x2c], 0x6e
005b9fb7 jne 0x5ba1ff
005b9fbd push 0
005b9fbf push 0xb4532c
005b9fc4 lea ecx, [esi + 0x3c]
005b9fc7 call 0x4054f0
005b9fcc jmp 0x5ba1ff
005b9fd1 mov esi, edi
005b9fd3 jmp 0x5ba1ff
005b9fd8 mov ecx, dword ptr [0xbfd65c]
005b9fde push -1
005b9fe0 mov edx, dword ptr [ecx + 4]
005b9fe3 mov ecx, dword ptr [ecx]
005b9fe5 call 0x7e79c0
005b9fea add esp, 4
005b9fed cmp eax, 0xf
005b9ff0 jne 0x5ba015
005b9ff2 push 0
005b9ff4 push 0xb45084
005b9ff9 lea ecx, [esi + 0x3c]
005b9ffc call 0x4054f0
005ba001 movss xmm2, dword ptr [0xb6a19c]
005ba009 jmp 0x5ba015
005ba00b mov dword ptr [esi + 0x2b4], 1
005ba015 cmp dword ptr [esi + 0x2c], 0x44
005ba019 jne 0x5ba08f
005ba01b mov dword ptr [esi + 0x2b4], 0
005ba025 mov dword ptr [esi + 0x2ac], 0x1388
005ba02f call 0x6c3d90
005ba034 xorps xmm0, xmm0
005ba037 cvtsi2sd xmm0, eax
005ba03b shr eax, 0x1f
005ba03e addsd xmm0, qword ptr [eax*8 + 0xb6c940]
005ba047 cvtpd2ps xmm1, xmm0
005ba04b mulss xmm1, xmm2
005ba04f call 0x6c3d90
005ba054 xorps xmm0, xmm0
005ba057 mulss xmm1, dword ptr [0xb6ad38]
005ba05f cvtsi2sd xmm0, eax
005ba063 shr eax, 0x1f
005ba066 movss dword ptr [esi + 0x290], xmm1
005ba06e addsd xmm0, qword ptr [eax*8 + 0xb6c940]
005ba077 cvtpd2ps xmm0, xmm0
005ba07b mulss xmm0, xmm2
005ba07f mulss xmm0, dword ptr [0xb6aa3c]
005ba087 movss dword ptr [esi + 0x28c], xmm0
005ba08f mov dword ptr [esi + 0x2d4], 0x3f800000
005ba099 mov dword ptr [esi + 0x180], 4
005ba0a3 jmp 0x5ba1f8
005ba0a8 mov dword ptr [esi + 0x17c], 6
005ba0b2 cmp ecx, 0xa
005ba0b5 je 0x5ba1ff
005ba0bb mov dword ptr [esi + 0x3c8], 0x3f800000
005ba0c5 mov dword ptr [esi + 0x3ac], 0x12c
005ba0cf mov dword ptr [esi + 0x3b0], 0x12c
005ba0d9 jmp 0x5ba1ff
005ba0de mov dword ptr [esi + 0x368], 0x3fa66666
005ba0e8 call 0x6c3d90
005ba0ed mov dword ptr [esi + 0x360], 0xc1b80000
005ba0f7 mov dword ptr [esi + 0x2a8], 0xc1b80000
005ba101 movd xmm0, eax
005ba105 cvtdq2pd xmm0, xmm0
005ba109 shr eax, 0x1f
005ba10c addsd xmm0, qword ptr [eax*8 + 0xb6c940]
005ba115 mov eax, dword ptr [esi + 0x2c]
005ba118 cvtpd2ps xmm1, xmm0
005ba11c movss xmm0, dword ptr [0xb6ae98]
005ba124 mulss xmm1, xmm2
005ba128 mulss xmm1, dword ptr [0xb6a974]
005ba130 subss xmm0, xmm1
005ba134 movss dword ptr [esi + 0x364], xmm0
005ba13c cmp eax, 0x1b
005ba13f je 0x5ba1ad
005ba141 cmp eax, 0xa3
005ba146 je 0x5ba1ad
005ba148 cmp eax, 0x23
005ba14b je 0x5ba165
005ba14d cmp eax, 0x55
005ba150 je 0x5ba165
005ba152 cmp eax, 0x56
005ba155 je 0x5ba165
005ba157 cmp eax, 0x5f
005ba15a je 0x5ba165
005ba15c cmp eax, 0x62
005ba15f jne 0x5ba1ff
005ba165 call 0x6c3d90
005ba16a mov edi, eax
005ba16c and edi, 3
005ba16f call 0x6c3d90
005ba174 xor edx, edx
005ba176 mov ecx, 3
005ba17b div ecx
005ba17d lea ecx, [esi + 0x3c]
005ba180 push 0
005ba182 test edx, edx
005ba184 je 0x5ba194
005ba186 push dword ptr [edi*4 + 0xb45958]
005ba18d call 0x4054f0
005ba192 jmp 0x5ba1ff
005ba194 cmp dword ptr [esi + 0x2c], 0x55
005ba198 mov eax, dword ptr [edi*4 + 0xb45958]
005ba19f push eax
005ba1a0 jne 0x5b9e29
005ba1a6 call 0x4054f0
005ba1ab jmp 0x5ba1ff
005ba1ad call 0x6c3d90
005ba1b2 and eax, 3
005ba1b5 lea ecx, [esi + 0x3c]
005ba1b8 push 0
005ba1ba push dword ptr [eax*4 + 0xb458c8]
005ba1c1 call 0x405850
005ba1c6 jmp 0x5ba1ff
005ba1c8 call 0x6c3d90
005ba1cd and eax, 3
005ba1d0 movd xmm0, eax
005ba1d4 cvtdq2pd xmm0, xmm0
005ba1d8 shr eax, 0x1f
005ba1db addsd xmm0, qword ptr [eax*8 + 0xb6c940]
005ba1e4 cvtpd2ps xmm0, xmm0
005ba1e8 mulss xmm0, dword ptr [0xb6aae4]
005ba1f0 movss dword ptr [esi + 0x3c4], xmm0
005ba1f8 mov byte ptr [esi + 0x16e], 1
005ba1ff cmp dword ptr [esi + 0x2c], 0x67
005ba203 jne 0x5ba2be
005ba209 mov ecx, dword ptr [0xc034dc]
005ba20f mov eax, 0xcccccccd
005ba214 mul ecx
005ba216 shr edx, 2
005ba219 lea eax, [edx + edx*4]
005ba21c mov edx, ecx
005ba21e sub edx, eax
005ba220 inc ecx
005ba221 cmp dword ptr [esi + 0xbc], 0
005ba228 lea eax, [esi + 0x3c]
005ba22b mov edi, eax
005ba22d mov dword ptr [ebp - 0xb0], edx
005ba233 mov dword ptr [0xc034dc], ecx
005ba239 mov dword ptr [ebp - 0xac], eax
005ba23f mov dword ptr [ebp - 0xb4], edi
005ba245 jg 0x5ba272
005ba247 cmp dword ptr [eax + 0x14], 0x10
005ba24b mov ecx, eax
005ba24d jb 0x5ba251
005ba24f mov ecx, dword ptr [eax]
005ba251 push 0
005ba253 push ecx
005ba254 push 0xa0830c
005ba259 push 3
005ba25b call 0x95e330
005ba260 mov eax, dword ptr [ebp - 0xac]
005ba266 lea edi, [esi + 0x3c]
005ba269 add esp, 0x10
005ba26c mov dword ptr [ebp - 0xb4], edi
005ba272 mov esi, dword ptr [eax + 0x7c]
005ba275 lea ecx, [ebp - 0x30]
005ba278 push 2
005ba27a call 0x95ed30
005ba27f push 0
005ba281 mov ecx, dword ptr [eax]
005ba283 mov dword ptr [esi + 0x78], ecx
005ba286 mov edx, dword ptr [eax + 4]
005ba289 mov ecx, dword ptr [ebp - 0xac]
005ba28f mov dword ptr [esi + 0x7c], edx
005ba292 mov edx, dword ptr [eax + 8]
005ba295 mov dword ptr [esi + 0x80], edx
005ba29b mov eax, dword ptr [eax + 0xc]
005ba29e mov dword ptr [esi + 0x84], eax
005ba2a4 mov eax, dword ptr [ebp - 0xb0]
005ba2aa push dword ptr [eax*4 + 0xb45978]
005ba2b1 call 0x4054f0
005ba2b6 mov esi, dword ptr [ebp - 0xa8]
005ba2bc jmp 0x5ba2c7
005ba2be lea edi, [esi + 0x3c]
005ba2c1 mov dword ptr [ebp - 0xb4], edi
005ba2c7 mov eax, dword ptr [esi + 0x2c]
005ba2ca add eax, -0x15
005ba2cd cmp eax, 0xb4
005ba2d2 ja 0x5ba855
005ba2d8 movzx eax, byte ptr [eax + 0x5bc20c]
005ba2df jmp dword ptr [eax*4 + 0x5bc140]
005ba2e6 mov eax, dword ptr [0xbfd65c]
005ba2eb lea ecx, [esi + 0x3c]
005ba2ee mov dword ptr [esi + 0x2ac], 0xffffff9c
005ba2f8 mov eax, dword ptr [eax + 0x18190]
005ba2fe add eax, 0x1cf0
005ba303 push eax
005ba304 call 0x402370
005ba309 movss xmm0, dword ptr [esi + 0xf0]
005ba311 mulss xmm0, dword ptr [0xb6a560]
005ba319 movss dword ptr [esi + 0xf0], xmm0
005ba321 jmp 0x5ba855
005ba326 mov eax, dword ptr [esi + 0x30]
005ba329 cmp eax, 1
005ba32c je 0x5ba333
005ba32e cmp eax, 2
005ba331 jne 0x5ba383
005ba333 or dword ptr [esi + 0x14c], 0x20
005ba33a jmp 0x5ba855
005ba33f call 0x6c3d90
005ba344 and eax, 3
005ba347 mov ecx, edi
005ba349 push 0
005ba34b push dword ptr [eax*4 + 0xb459d0]
005ba352 call 0x4054f0
005ba357 mov ecx, dword ptr [0xbfd65c]
005ba35d mov ecx, dword ptr [ecx + 0x18190]
005ba363 call 0x7cf750
005ba368 test eax, eax
005ba36a jne 0x5ba383
005ba36c lea ecx, [esi + 0x6c]
005ba36f call 0x432ec0
005ba374 mov ecx, eax
005ba376 call 0x659230
005ba37b push eax
005ba37c mov ecx, edi
005ba37e call 0x405890
005ba383 mov eax, dword ptr [0xbfd65c]
005ba388 mov ecx, edi
005ba38a mov eax, dword ptr [eax + 0x18190]
005ba390 add eax, 0x1cf0
005ba395 push eax
005ba396 call 0x402370
005ba39b jmp 0x5ba855
005ba3a0 push ecx
005ba3a1 mov ecx, dword ptr [0xbfd65c]
005ba3a7 call 0x706110
005ba3ac cmp eax, 0x1c
005ba3af jne 0x5ba855
005ba3b5 push 0xb4545c
005ba3ba lea ecx, [ebp - 0x38]
005ba3bd call 0x407990
005ba3c2 lea eax, [ebp - 0x38]
005ba3c5 mov dword ptr [ebp - 4], 0x14
005ba3cc push eax
005ba3cd push 0
005ba3cf mov ecx, edi
005ba3d1 call 0x407340
005ba3d6 lea ecx, [ebp - 0x38]
005ba3d9 mov dword ptr [ebp - 4], 0xffffffff
005ba3e0 call 0x407be0
005ba3e5 push ecx
005ba3e6 mov ecx, edi
005ba3e8 call 0x4073a0
005ba3ed jmp 0x5ba855
005ba3f2 lea eax, [esi + 0x3c]
005ba3f5 push 0
005ba3f7 push 0xb41d80
005ba3fc mov ecx, eax
005ba3fe mov dword ptr [ebp - 0xbc], eax
005ba404 call 0x4054f0
005ba409 mov eax, dword ptr [esi + 0x30]
005ba40c test eax, eax
005ba40e jne 0x5ba41c
005ba410 mov dword ptr [esi + 0x2b4], 1
005ba41a jmp 0x5ba43a
005ba41c cmp eax, 1
005ba41f jne 0x5ba43a
005ba421 mov eax, dword ptr [0xbfd65c]
005ba426 lea ecx, [esi + 0x3c]
005ba429 mov eax, dword ptr [eax + 0x18190]
005ba42f add eax, 0x1cf0
005ba434 push eax
005ba435 call 0x402370
005ba43a push ecx
005ba43b mov ecx, dword ptr [0xbfd65c]
005ba441 call 0x706110
005ba446 cmp eax, 0x1c
005ba449 jne 0x5ba855
005ba44f cmp dword ptr [esi + 0xbc], 0
005ba456 mov dword ptr [ebp - 0xac], 0
005ba460 jbe 0x5ba550
005ba466 mov dword ptr [ebp - 0xb0], 0
005ba470 push 0x32
005ba472 mov dword ptr [ebp - 0x38], 0
005ba479 lea ecx, [ebp - 0x38]
005ba47c push 0xb45428
005ba481 mov dword ptr [ebp - 0x28], 0
005ba488 mov dword ptr [ebp - 0x24], 0xf
005ba48f mov byte ptr [ebp - 0x38], 0
005ba493 call 0x407c80
005ba498 mov dword ptr [ebp - 4], 0x15
005ba49f mov eax, dword ptr [ebp - 0xac]
005ba4a5 test eax, eax
005ba4a7 js 0x5ba4f6
005ba4a9 cmp eax, dword ptr [esi + 0xbc]
005ba4af jge 0x5ba4f6
005ba4b1 mov eax, dword ptr [ebp - 0xb0]
005ba4b7 lea edi, [ebp - 0x38]
005ba4ba mov ecx, dword ptr [esi + 0xb8]
005ba4c0 lea edx, [eax + 8]
005ba4c3 add edx, ecx
005ba4c5 cmp edx, edi
005ba4c7 mov edi, dword ptr [ebp - 0xb4]
005ba4cd je 0x5ba4f1
005ba4cf cmp dword ptr [ebp - 0x24], 0x10
005ba4d3 lea eax, [ebp - 0x38]
005ba4d6 push dword ptr [ebp - 0x28]
005ba4d9 cmovae eax, dword ptr [ebp - 0x38]
005ba4dd mov ecx, edx
005ba4df push eax
005ba4e0 call 0x407c80
005ba4e5 mov ecx, dword ptr [esi + 0xb8]
005ba4eb mov eax, dword ptr [ebp - 0xb0]
005ba4f1 mov byte ptr [eax + ecx + 0x30], 0
005ba4f6 mov dword ptr [ebp - 4], 0xffffffff
005ba4fd mov edx, dword ptr [ebp - 0x24]
005ba500 cmp edx, 0x10
005ba503 jb 0x5ba52d
005ba505 mov ecx, dword ptr [ebp - 0x38]
005ba508 inc edx
005ba509 mov eax, ecx
005ba50b cmp edx, 0x1000
005ba511 jb 0x5ba523
005ba513 mov ecx, dword ptr [ecx - 4]
005ba516 add edx, 0x23
005ba519 sub eax, ecx
005ba51b add eax, -4
005ba51e cmp eax, 0x1f
005ba521 ja 0x5ba561
005ba523 push edx
005ba524 push ecx
005ba525 call 0x9eb08e
005ba52a add esp, 8
005ba52d mov eax, dword ptr [ebp - 0xac]
005ba533 add dword ptr [ebp - 0xb0], 0x9c
005ba53d inc eax
005ba53e mov dword ptr [ebp - 0xac], eax
005ba544 cmp eax, dword ptr [esi + 0xbc]
005ba54a jb 0x5ba470
005ba550 push ecx
005ba551 mov ecx, dword ptr [ebp - 0xbc]
005ba557 call 0x4073a0
005ba55c jmp 0x5ba855
005ba561 call dword ptr [0xa065ac]
005ba567 push 2
005ba569 lea ecx, [ebp - 0x20]
005ba56c mov dword ptr [esi + 0x2ac], 0x80000000
005ba576 call 0x95ed30
005ba57b push 0
005ba57d lea ecx, [esi + 0x3c]
005ba580 call 0x4062c0
005ba585 mov ecx, dword ptr [ebp - 0x20]
005ba588 mov dword ptr [eax + 0x78], ecx
005ba58b mov ecx, dword ptr [ebp - 0x1c]
005ba58e mov dword ptr [eax + 0x7c], ecx
005ba591 mov ecx, dword ptr [ebp - 0x18]
005ba594 mov dword ptr [eax + 0x80], ecx
005ba59a mov ecx, dword ptr [ebp - 0x14]
005ba59d mov dword ptr [eax + 0x84], ecx
005ba5a3 jmp 0x5ba855
005ba5a8 cmp dword ptr [esi + 0x30], 1
005ba5ac jne 0x5ba622
005ba5ae push 4
005ba5b0 lea ecx, [esi + 0x334]
005ba5b6 mov dword ptr [esi + 0x2b4], 0
005ba5c0 call 0x7a7d50
005ba5c5 inc eax
005ba5c6 push eax
005ba5c7 push 0xb40c58
005ba5cc lea eax, [ebp - 0x20]
005ba5cf push 0x10
005ba5d1 push eax
005ba5d2 call 0x418980
005ba5d7 add esp, 0x10
005ba5da lea eax, [ebp - 0x20]
005ba5dd mov ecx, edi
005ba5df push 0
005ba5e1 push eax
005ba5e2 call 0x4054f0
005ba5e7 mov eax, dword ptr [0xbfd65c]
005ba5ec mov ecx, edi
005ba5ee mov eax, dword ptr [eax + 0x18190]
005ba5f4 add eax, 0x1cf0
005ba5f9 push eax
005ba5fa call 0x402370
005ba5ff mov dword ptr [esi + 0x104], 0x3e99999a
005ba609 mov dword ptr [esi + 0x108], 0x3e99999a
005ba613 mov dword ptr [esi + 0x10c], 0x3e99999a
005ba61d jmp 0x5ba855
005ba622 mov dword ptr [esi + 0x2b0], 0xc1600000
005ba62c jmp 0x5ba383
005ba631 mov eax, dword ptr [0xbfd65c]
005ba636 mov eax, dword ptr [eax + 0x18190]
005ba63c cmp dword ptr [eax + 0x1e84], 0x2d
005ba643 jne 0x5ba855
005ba649 movss xmm2, dword ptr [0xb6a4c4]
005ba651 lea ecx, [ebp - 0x78]
005ba654 movss xmm3, dword ptr [0xb6a480]
005ba65c movaps xmm1, xmm2
005ba65f call 0x427080
005ba664 push eax
005ba665 mov ecx, edi
005ba667 call 0x402370
005ba66c jmp 0x5ba855
005ba671 mov eax, dword ptr [esi + 0x294]
005ba677 mov dword ptr [esi + 0x28c], eax
005ba67d mov eax, dword ptr [esi + 0x298]
005ba683 mov dword ptr [esi + 0x290], eax
005ba689 call 0x6c3d90
005ba68e movd xmm0, eax
005ba692 cvtdq2pd xmm0, xmm0
005ba696 shr eax, 0x1f
005ba699 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
005ba6a2 cvtpd2ps xmm0, xmm0
005ba6a6 mulss xmm0, dword ptr [0xb6a19c]
005ba6ae mulss xmm0, dword ptr [0xb6ac40]
005ba6b6 call 0x65a640
005ba6bb push 0
005ba6bd push 0xb3fd8c
005ba6c2 mov ecx, edi
005ba6c4 movss dword ptr [esi + 0x3c4], xmm0
005ba6cc call 0x4054f0
005ba6d1 lea ecx, [esi + 0x334]
005ba6d7 call 0x7a7db0
005ba6dc fmul dword ptr [0xb6a350]
005ba6e2 lea ecx, [esi + 0x334]
005ba6e8 fld1 
005ba6ea push 2
005ba6ec faddp st(1)
005ba6ee fstp dword ptr [ebp - 0xbc]
005ba6f4 movss xmm1, dword ptr [ebp - 0xbc]
005ba6fc movaps xmm0, xmm1
005ba6ff mulss xmm1, dword ptr [0xbc7a2c]
005ba707 mulss xmm0, dword ptr [0xbc7a28]
005ba70f movss dword ptr [esi + 0xdc], xmm1
005ba717 movss dword ptr [esi + 0xd8], xmm0
005ba71f call 0x7a7d50
005ba724 test eax, eax
005ba726 lea ecx, [esi + 0x334]
005ba72c setne al
005ba72f mov byte ptr [esi + 0x13c], al
005ba735 call 0x7a7db0
005ba73a fmul dword ptr [0xb6a3b0]
005ba740 fld1 
005ba742 mov eax, dword ptr [0xbfd65c]
005ba747 faddp st(1)
005ba749 fstp dword ptr [esi + 0x140]
005ba74f mov eax, dword ptr [eax + 0x18190]
005ba755 mov eax, dword ptr [eax + 0x1e84]
005ba75b add eax, -0x21
005ba75e cmp eax, 9
005ba761 ja 0x5ba7a1
005ba763 movzx eax, byte ptr [eax + 0x5bc2cc]
005ba76a jmp dword ptr [eax*4 + 0x5bc2c4]
005ba771 movss xmm3, dword ptr [0xb6a614]
005ba779 movss xmm2, dword ptr [0xb6a5a4]
005ba781 movss xmm1, dword ptr [0xb6a5e8]
005ba789 push ecx
005ba78a lea ecx, [ebp - 0x78]
005ba78d mov dword ptr [esp], 0x3f800000
005ba794 call 0x4325d0
005ba799 push eax
005ba79a mov ecx, edi
005ba79c call 0x402370
005ba7a1 lea ecx, [esi + 0x334]
005ba7a7 call 0x7a7db0
005ba7ac fld dword ptr [0xb6a3b0]
005ba7b2 fmul st(1), st(0)
005ba7b4 mov byte ptr [esi + 0x16e], 1
005ba7bb faddp st(1)
005ba7bd fstp dword ptr [esi + 0xf0]
005ba7c3 jmp 0x5ba855
005ba7c8 push 0
005ba7ca push 0xb3fd8c
005ba7cf lea ecx, [esi + 0x3c]
005ba7d2 call 0x4054f0
005ba7d7 call 0x6c3d90
005ba7dc movd xmm0, eax
005ba7e0 cvtdq2pd xmm0, xmm0
005ba7e4 shr eax, 0x1f
005ba7e7 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
005ba7f0 cvtpd2ps xmm0, xmm0
005ba7f4 mulss xmm0, dword ptr [0xb6a19c]
005ba7fc mulss xmm0, dword ptr [0xb6ac40]
005ba804 call 0x65a640
005ba809 mov edi, dword ptr [ebp - 0xa8]
005ba80f lea ecx, [esi + 0x3c]
005ba812 push 0
005ba814 movss dword ptr [edi + 0x3c4], xmm0
005ba81c addss xmm0, dword ptr [0xb6ab88]
005ba824 movss dword ptr [ebp - 0xbc], xmm0
005ba82c call 0x4062c0
005ba831 movss xmm0, dword ptr [ebp - 0xbc]
005ba839 movss dword ptr [eax + 0x3c], xmm0
005ba83e mov dword ptr [edi + 0x360], 0
005ba848 mov byte ptr [edi + 0x16e], 1
005ba84f mov edi, dword ptr [ebp - 0xb4]
005ba855 push ecx
005ba856 mov ecx, edi
005ba858 call 0x4073a0
005ba85d mov ecx, dword ptr [ebp - 0xa8]
005ba863 mov eax, dword ptr [ecx + 0x2c]
005ba866 cmp eax, 0xbe
005ba86b je 0x5ba874
005ba86d cmp eax, 0xc6
005ba872 jne 0x5ba8de
005ba874 cmp dword ptr [edi + 0x80], 1
005ba87b jg 0x5ba899
005ba87d cmp dword ptr [edi + 0x14], 0x10
005ba881 mov eax, edi
005ba883 jb 0x5ba887
005ba885 mov eax, dword ptr [edi]
005ba887 push 1
005ba889 push eax
005ba88a push 0xa0830c
005ba88f push 3
005ba891 call 0x95e330
005ba896 add esp, 0x10
005ba899 mov eax, dword ptr [edi + 0x7c]
005ba89c mov dword ptr [eax + 0xbc], 1
005ba8a6 cmp dword ptr [edi + 0x80], 1
005ba8ad jg 0x5ba8cb
005ba8af cmp dword ptr [edi + 0x14], 0x10
005ba8b3 mov eax, edi
005ba8b5 jb 0x5ba8b9
005ba8b7 mov eax, dword ptr [edi]
005ba8b9 push 1
005ba8bb push eax
005ba8bc push 0xa0830c
005ba8c1 push 3
005ba8c3 call 0x95e330
005ba8c8 add esp, 0x10
005ba8cb mov eax, dword ptr [edi + 0x7c]
005ba8ce mov ecx, dword ptr [ebp - 0xa8]
005ba8d4 mov dword ptr [eax + 0xc0], 1
005ba8de cmp dword ptr [ecx + 0x2c], 0x3b
005ba8e2 jne 0x5ba948
005ba8e4 cmp dword ptr [edi + 0x80], 0
005ba8eb jg 0x5ba909
005ba8ed cmp dword ptr [edi + 0x14], 0x10
005ba8f1 mov eax, edi
005ba8f3 jb 0x5ba8f7
005ba8f5 mov eax, dword ptr [edi]
005ba8f7 push 0
005ba8f9 push eax
005ba8fa push 0xa0830c
005ba8ff push 3
005ba901 call 0x95e330
005ba906 add esp, 0x10
005ba909 mov eax, dword ptr [edi + 0x7c]
005ba90c mov dword ptr [eax + 0x20], 1
005ba913 cmp dword ptr [edi + 0x80], 0
005ba91a jg 0x5ba938
005ba91c cmp dword ptr [edi + 0x14], 0x10
005ba920 mov eax, edi
005ba922 jb 0x5ba926
005ba924 mov eax, dword ptr [edi]
005ba926 push 0
005ba928 push eax
005ba929 push 0xa0830c
005ba92e push 3
005ba930 call 0x95e330
005ba935 add esp, 0x10
005ba938 mov eax, dword ptr [edi + 0x7c]
005ba93b mov ecx, dword ptr [ebp - 0xa8]
005ba941 mov dword ptr [eax + 0x24], 1
005ba948 mov eax, dword ptr [ecx + 0x2c]
005ba94b cmp eax, 0x1e
005ba94e je 0x5ba95b
005ba950 cmp eax, 0x99
005ba955 jne 0x5bbbab
005ba95b mov dword ptr [ecx + 0x374], 0
005ba965 mov dword ptr [ecx + 0x378], 0
005ba96f cmp dword ptr [edi + 0x80], 1
005ba976 jg 0x5ba994
005ba978 cmp dword ptr [edi + 0x14], 0x10
005ba97c mov eax, edi
005ba97e jb 0x5ba982
005ba980 mov eax, dword ptr [edi]
005ba982 push 1
005ba984 push eax
005ba985 push 0xa0830c
005ba98a push 3
005ba98c call 0x95e330
005ba991 add esp, 0x10
005ba994 mov eax, dword ptr [edi + 0x7c]
005ba997 mov dword ptr [eax + 0xc4], 0
005ba9a1 cmp dword ptr [edi + 0x80], 1
005ba9a8 jg 0x5ba9c6
005ba9aa cmp dword ptr [edi + 0x14], 0x10
005ba9ae mov eax, edi
005ba9b0 jb 0x5ba9b4
005ba9b2 mov eax, dword ptr [edi]
005ba9b4 push 1
005ba9b6 push eax
005ba9b7 push 0xa0830c
005ba9bc push 3
005ba9be call 0x95e330
005ba9c3 add esp, 0x10
005ba9c6 mov eax, dword ptr [edi + 0x7c]
005ba9c9 xorps xmm2, xmm2
005ba9cc mov dword ptr [eax + 0xc8], 1
005ba9d6 mov eax, dword ptr [ebp - 0xa8]
005ba9dc cmp dword ptr [eax + 0x2c], 0x99
005ba9e3 jne 0x5bbb87
005ba9e9 movss xmm3, dword ptr [0xb6a4c8]
005ba9f1 lea ecx, [ebp - 0x78]
005ba9f4 movss xmm1, dword ptr [0xb6a4b8]
005ba9fc jmp 0x5bbb95
005baa01 cmp dword ptr [esi + 0x30], 1
005baa05 lea eax, [ebp - 0x4c]
005baa08 mov dword ptr [ebp - 0x28], 0x3e4ccccd
005baa0f mov ecx, edi
005baa11 mov dword ptr [ebp - 0x24], 0
005baa18 push eax
005baa19 jne 0x5baa3b
005baa1b movaps xmm0, xmmword ptr [0xb6c2b0]
005baa22 movups xmmword ptr [ebp - 0x4c], xmm0
005baa26 mov dword ptr [ebp - 0x2c], 0x3e4ccccd
005baa2d xorps xmm0, xmm0
005baa30 movups xmmword ptr [ebp - 0x3c], xmm0
005baa34 call 0x402370
005baa39 jmp 0x5baab0
005baa3b movaps xmm0, xmmword ptr [0xb6c2f0]
005baa42 movups xmmword ptr [ebp - 0x4c], xmm0
005baa46 mov dword ptr [ebp - 0x2c], 0
005baa4d xorps xmm0, xmm0
005baa50 movups xmmword ptr [ebp - 0x3c], xmm0
005baa54 call 0x402370
005baa59 mov ecx, dword ptr [0xbfd65c]
005baa5f mov ecx, dword ptr [ecx + 0x18190]
005baa65 call 0x7e2590
005baa6a test al, al
005baa6c je 0x5baab0
005baa6e movaps xmm0, xmmword ptr [0xb6c310]
005baa75 lea eax, [ebp - 0x4c]
005baa78 movups xmmword ptr [ebp - 0x4c], xmm0
005baa7c mov dword ptr [ebp - 0x2c], 0
005baa83 mov ecx, edi
005baa85 xorps xmm0, xmm0
005baa88 mov dword ptr [ebp - 0x28], 0x3e99999a
005baa8f push eax
005baa90 movups xmmword ptr [ebp - 0x3c], xmm0
005baa94 mov dword ptr [ebp - 0x24], 0
005baa9b call 0x402370
005baaa0 push 0
005baaa2 mov ecx, edi
005baaa4 call 0x4062c0
005baaa9 mov dword ptr [eax + 0x54], 0x3f000000
005baab0 mov dword ptr [esi + 0xf0], 0
005baaba add esi, 0x334
005baac0 mov ecx, esi
005baac2 call 0x7a7db0
005baac7 fmul dword ptr [0xb6a434]
005baacd mov ecx, esi
005baacf mov edi, dword ptr [ebp - 0xa8]
005baad5 push 2
005baad7 fadd dword ptr [0xb6a614]
005baadd fstp dword ptr [ebp - 0xbc]
005baae3 movss xmm1, dword ptr [ebp - 0xbc]
005baaeb movaps xmm0, xmm1
005baaee mulss xmm1, dword ptr [0xbc7a2c]
005baaf6 mulss xmm0, dword ptr [0xbc7a28]
005baafe mov dword ptr [edi + 0xd0], 0
005bab08 movss dword ptr [edi + 0xdc], xmm1
005bab10 mov dword ptr [edi + 0xd4], 0xc1a00000
005bab1a movss dword ptr [edi + 0xd8], xmm0
005bab22 call 0x7a7d50
005bab27 mov ecx, dword ptr [ebp - 0xb4]
005bab2d test eax, eax
005bab2f push 0
005bab31 setne al
005bab34 push 0xb3fd8c
005bab39 mov byte ptr [edi + 0x13c], al
005bab3f call 0x4054f0
005bab44 lea ecx, [edi + 0x6c]
005bab47 call 0x432ec0
005bab4c push eax
005bab4d mov ecx, esi
005bab4f call 0x7a7d50
005bab54 mov edi, dword ptr [ebp - 0xb4]
005bab5a mov ecx, edi
005bab5c push eax
005bab5d call 0x405890
005bab62 jmp 0x5ba855
005bab67 mov byte ptr [esi + 0x169], 0
005bab6e mov dword ptr [esi + 0x3ac], 0x78
005bab78 movss xmm0, dword ptr [0xc02fec]
005bab80 movss dword ptr [esi + 0x28c], xmm0
005bab88 movss xmm0, dword ptr [0xc02ff0]
005bab90 movss dword ptr [esi + 0x290], xmm0
005bab98 jmp 0x5ba855
005bab9d cmp dword ptr [esi + 0x30], 0
005baba1 push 0
005baba3 jne 0x5bac02
005baba5 push 4
005baba7 lea ecx, [esi + 0x334]
005babad call 0x7a7d50
005babb2 mov ecx, edi
005babb4 mov eax, dword ptr [eax*4 + 0xb459b8]
005babbb push eax
005babbc call 0x4054f0
005babc1 mov ecx, dword ptr [0xbfd65c]
005babc7 lea eax, [esi + 0x294]
005babcd push eax
005babce mov dword ptr [esi + 0x17c], 3
005babd8 call 0x6d5e30
005babdd test eax, eax
005babdf je 0x5ba855
005babe5 movss xmm0, dword ptr [eax + 0x294]
005babed comiss xmm0, dword ptr [esi + 0x294]
005babf4 seta al
005babf7 mov byte ptr [esi + 0x13c], al
005babfd jmp 0x5ba855
005bac02 push 0xb40124
005bac07 mov ecx, edi
005bac09 call 0x4054f0
005bac0e mov eax, dword ptr [esi + 0x30]
005bac11 mov dword ptr [esi + 0x2b0], 0x42c80000
005bac1b cmp eax, 2
005bac1e jne 0x5bac34
005bac20 movaps xmm0, xmmword ptr [0xb6c700]
005bac27 movups xmmword ptr [ebp - 0x4c], xmm0
005bac2b movaps xmm0, xmmword ptr [0xb6c610]
005bac32 jmp 0x5bac4f
005bac34 cmp eax, 3
005bac37 jne 0x5ba855
005bac3d movaps xmm0, xmmword ptr [0xb6c610]
005bac44 movups xmmword ptr [ebp - 0x4c], xmm0
005bac48 movaps xmm0, xmmword ptr [0xb6c5b0]
005bac4f lea eax, [ebp - 0x4c]
005bac52 mov dword ptr [ebp - 0x2c], 0
005bac59 push eax
005bac5a mov ecx, edi
005bac5c mov dword ptr [ebp - 0x28], 0
005bac63 movups xmmword ptr [ebp - 0x3c], xmm0
005bac67 mov dword ptr [ebp - 0x24], 0
005bac6e call 0x402370
005bac73 jmp 0x5ba855
005bac78 push 2
005bac7a lea ecx, [esi + 0x334]
005bac80 mov byte ptr [esi + 0x16e], 1
005bac87 call 0x7a7d50
005bac8c test eax, eax
005bac8e setne al
005bac91 mov byte ptr [esi + 0x13c], al
005bac97 jmp 0x5ba855
005bac9c push 2
005bac9e lea ecx, [esi + 0x334]
005baca4 mov byte ptr [esi + 0x16e], 1
005bacab call 0x7a7d50
005bacb0 test eax, eax
005bacb2 mov dword ptr [esi + 0x3b0], 0x1e
005bacbc push 0
005bacbe setne al
005bacc1 mov dword ptr [esi + 0x3ac], 0x1e
005baccb push 0xb40360
005bacd0 mov ecx, edi
005bacd2 mov byte ptr [esi + 0x13c], al
005bacd8 call 0x4054f0
005bacdd cmp dword ptr [esi + 0x30], 0
005bace1 jne 0x5ba855
005bace7 mov ecx, dword ptr [0xbfd65c]
005baced lea eax, [esi + 0x294]
005bacf3 movss xmm3, dword ptr [esi + 0x2c8]
005bacfb push eax
005bacfc lea eax, [ebp - 0x20]
005bacff mov ecx, dword ptr [ecx + 0x18190]
005bad05 push eax
005bad06 call 0x7de530
005bad0b movss xmm0, dword ptr [0xb6a7b0]
005bad13 movss xmm3, dword ptr [ebp - 0x18]
005bad18 movss xmm2, dword ptr [ebp - 0x1c]
005bad1d movss xmm1, dword ptr [ebp - 0x20]
005bad22 push ecx
005bad23 mulss xmm3, xmm0
005bad27 lea ecx, [ebp - 0x78]
005bad2a mov dword ptr [esp], 0x3f800000
005bad31 mulss xmm2, xmm0
005bad35 mulss xmm1, xmm0
005bad39 call 0x4325d0
005bad3e push eax
005bad3f mov ecx, edi
005bad41 call 0x402370
005bad46 jmp 0x5ba855
005bad4b call 0x6c3d90
005bad50 movss xmm1, dword ptr [0xb6a19c]
005bad58 movd xmm0, eax
005bad5c cvtdq2pd xmm0, xmm0
005bad60 shr eax, 0x1f
005bad63 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
005bad6c mov eax, dword ptr [esi + 0x30]
005bad6f cvtpd2ps xmm0, xmm0
005bad73 mulss xmm0, xmm1
005bad77 mulss xmm0, dword ptr [0xb6aa0c]
005bad7f addss xmm0, dword ptr [0xb6a8f4]
005bad87 movss dword ptr [esi + 0x3c4], xmm0
005bad8f cmp eax, 0xb
005bad92 jne 0x5badde
005bad94 call 0x6c3d90
005bad99 mov dword ptr [esi + 0x3a8], 0x42c80000
005bada3 mov dword ptr [esi + 0x3c8], 0x3f800000
005badad movd xmm0, eax
005badb1 cvtdq2pd xmm0, xmm0
005badb5 shr eax, 0x1f
005badb8 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
005badc1 cvtpd2ps xmm0, xmm0
005badc5 mulss xmm0, xmm1
005badc9 mulss xmm0, dword ptr [0xb6ac40]
005badd1 movss dword ptr [esi + 0xe0], xmm0
005badd9 jmp 0x5ba855
005badde cmp eax, 0xa
005bade1 jne 0x5bae2c
005bade3 push 0xb4540c
005bade8 lea ecx, [ebp - 0x38]
005badeb mov dword ptr [esi + 0x3a8], 0x42c80000
005badf5 call 0x407990
005badfa lea eax, [ebp - 0x38]
005badfd mov dword ptr [ebp - 4], 0x16
005bae04 push eax
005bae05 push 0
005bae07 mov ecx, edi
005bae09 call 0x407340
005bae0e lea ecx, [ebp - 0x38]
005bae11 mov dword ptr [ebp - 4], 0xffffffff
005bae18 call 0x407be0
005bae1d mov dword ptr [esi + 0x3c8], 0x3f800000
005bae27 jmp 0x5ba855
005bae2c test eax, eax
005bae2e je 0x5baec4
005bae34 call 0x6c3d90
005bae39 mov dword ptr [esi + 0x3a8], 0x41a00000
005bae43 movd xmm0, eax
005bae47 cvtdq2pd xmm0, xmm0
005bae4b shr eax, 0x1f
005bae4e cmp dword ptr [esi + 0x34], 0x3b7
005bae55 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
005bae5e cvtpd2ps xmm0, xmm0
005bae62 mulss xmm0, xmm1
005bae66 mulss xmm0, dword ptr [0xb6ac40]
005bae6e movss dword ptr [esi + 0xe0], xmm0
005bae76 jne 0x5baefd
005bae7c call 0x6c3d90
005bae81 mov dword ptr [esi + 0x3c8], 0x3f800000
005bae8b movd xmm0, eax
005bae8f cvtdq2pd xmm0, xmm0
005bae93 shr eax, 0x1f
005bae96 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
005bae9f cvtpd2ps xmm0, xmm0
005baea3 mulss xmm0, xmm1
005baea7 mulss xmm0, dword ptr [0xb6aad4]
005baeaf addss xmm0, dword ptr [0xb6ab44]
005baeb7 movss dword ptr [esi + 0xe0], xmm0
005baebf jmp 0x5ba855
005baec4 call 0x6c3d90
005baec9 movd xmm0, eax
005baecd cvtdq2pd xmm0, xmm0
005baed1 shr eax, 0x1f
005baed4 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
005baedd cvtpd2ps xmm0, xmm0
005baee1 mulss xmm0, xmm1
005baee5 mulss xmm0, dword ptr [0xb6a434]
005baeed addss xmm0, dword ptr [0xb6a670]
005baef5 movss dword ptr [esi + 0x3a8], xmm0
005baefd mov dword ptr [esi + 0x3c8], 0x3f800000
005baf07 jmp 0x5ba855
005baf0c mov byte ptr [esi + 0x169], 0
005baf13 mov eax, dword ptr [esi + 0x164]
005baf19 or dword ptr [esi + 0x160], 0x200000
005baf23 mov dword ptr [esi + 0x164], eax
005baf29 jmp 0x5ba855
005baf2e mov dword ptr [esi + 0x2b4], 0
005baf38 mov dword ptr [esi + 0x2ac], 0x7d0
005baf42 mov byte ptr [esi + 0x16e], 1
005baf49 mov dword ptr [esi + 0x3c8], 0x3d072b02
005baf53 jmp 0x5ba855
005baf58 mov eax, dword ptr [esi + 0x30]
005baf5b test eax, eax
005baf5d jne 0x5baf73
005baf5f movaps xmm0, xmmword ptr [0xb6c610]
005baf66 movups xmmword ptr [ebp - 0x4c], xmm0
005baf6a movaps xmm0, xmmword ptr [0xb6c320]
005baf71 jmp 0x5bafa3
005baf73 cmp eax, 1
005baf76 jne 0x5baf8c
005baf78 movaps xmm0, xmmword ptr [0xb6c610]
005baf7f movups xmmword ptr [ebp - 0x4c], xmm0
005baf83 movaps xmm0, xmmword ptr [0xb6c1e0]
005baf8a jmp 0x5bafa3
005baf8c cmp eax, 2
005baf8f jne 0x5bafc7
005baf91 movaps xmm0, xmmword ptr [0xb6c610]
005baf98 movups xmmword ptr [ebp - 0x4c], xmm0
005baf9c movaps xmm0, xmmword ptr [0xb6c750]
005bafa3 lea eax, [ebp - 0x4c]
005bafa6 mov dword ptr [ebp - 0x2c], 0
005bafad push eax
005bafae mov ecx, edi
005bafb0 mov dword ptr [ebp - 0x28], 0
005bafb7 movups xmmword ptr [ebp - 0x3c], xmm0
005bafbb mov dword ptr [ebp - 0x24], 0
005bafc2 call 0x402370
005bafc7 push 0
005bafc9 push 0xb41d88
005bafce mov ecx, edi
005bafd0 mov dword ptr [esi + 0x2b4], 0
005bafda mov dword ptr [esi + 0x3a0], 0
005bafe4 call 0x4054f0
005bafe9 lea ecx, [esi + 0x6c]
005bafec call 0x432ec0
005baff1 push eax
005baff2 lea ecx, [esi + 0x334]
005baff8 call 0x7a7d50
005baffd push eax
005baffe mov ecx, edi
005bb000 call 0x405890
005bb005 jmp 0x5ba855
005bb00a push 0x18
005bb00c mov dword ptr [esi + 0x2ac], 0x80000000
005bb016 call 0x9eacf8
005bb01b add esp, 4
005bb01e mov dword ptr [ebp - 0xbc], eax
005bb024 mov ecx, eax
005bb026 mov dword ptr [ebp - 4], 0x17
005bb02d call 0x5bc2e0
005bb032 push eax
005bb033 lea ecx, [esi + 0x3d8]
005bb039 mov dword ptr [ebp - 4], 0xffffffff
005bb040 call 0x5eeac0
005bb045 push 2
005bb047 lea ecx, [ebp - 0x20]
005bb04a mov dword ptr [esi + 0x3a4], 0x3dcccccd
005bb054 call 0x95ed30
005bb059 push 0
005bb05b lea ecx, [esi + 0x3c]
005bb05e call 0x4062c0
005bb063 mov ecx, dword ptr [ebp - 0x20]
005bb066 mov dword ptr [eax + 0x78], ecx
005bb069 mov ecx, dword ptr [ebp - 0x1c]
005bb06c mov dword ptr [eax + 0x7c], ecx
005bb06f mov ecx, dword ptr [ebp - 0x18]
005bb072 mov dword ptr [eax + 0x80], ecx
005bb078 mov ecx, dword ptr [ebp - 0x14]
005bb07b mov dword ptr [eax + 0x84], ecx
005bb081 jmp 0x5ba855
005bb086 xorps xmm0, xmm0
005bb089 mov dword ptr [esi + 0x3ac], 1
005bb093 movlpd qword ptr [ebp - 0x20], xmm0
005bb098 movlpd qword ptr [ebp - 0x18], xmm0
005bb09d movups xmm0, xmmword ptr [ebp - 0x20]
005bb0a1 mov dword ptr [esi + 0x3b0], 1
005bb0ab mov dword ptr [esi + 0x3a8], 0x43020000
005bb0b5 mov dword ptr [esi + 0x3a4], 0x43020000
005bb0bf mov dword ptr [esi + 0x380], 0x40600000
005bb0c9 mov dword ptr [esi + 0x384], 0x3f800000
005bb0d3 movups xmmword ptr [esi + 0x370], xmm0
005bb0da mov byte ptr [esi + 0x169], 0
005bb0e1 jmp 0x5ba855
005bb0e6 mov dword ptr [esi + 0x2b4], 0
005bb0f0 mov dword ptr [esi + 0x2ac], 0x7d0
005bb0fa push 0
005bb0fc push 0xb40360
005bb101 mov ecx, edi
005bb103 call 0x4054f0
005bb108 jmp 0x5ba855
005bb10d push 0
005bb10f push 0xb402c0
005bb114 mov ecx, edi
005bb116 mov dword ptr [esi + 0x2b4], 0
005bb120 call 0x405a00
005bb125 mov edi, dword ptr [ebp - 0xa8]
005bb12b add esi, 0x334
005bb131 lea ecx, [edi + 0x8c]
005bb137 call 0x432ec0
005bb13c push eax
005bb13d mov ecx, esi
005bb13f call 0x7a7d50
005bb144 mov ecx, dword ptr [ebp - 0xb4]
005bb14a push eax
005bb14b call 0x405cf0
005bb150 mov ecx, dword ptr [ebp - 0xb4]
005bb156 push 0
005bb158 push 0xb3fd8c
005bb15d call 0x405850
005bb162 lea ecx, [edi + 0x6c]
005bb165 call 0x432ec0
005bb16a push eax
005bb16b mov ecx, esi
005bb16d call 0x7a7d50
005bb172 mov ecx, dword ptr [ebp - 0xb4]
005bb178 push eax
005bb179 call 0x405890
005bb17e push 2
005bb180 mov ecx, esi
005bb182 call 0x7a7d50
005bb187 test eax, eax
005bb189 setne al
005bb18c or dword ptr [edi + 0x160], 0x200000
005bb196 mov byte ptr [edi + 0x13c], al
005bb19c mov eax, dword ptr [edi + 0x164]
005bb1a2 mov dword ptr [edi + 0x164], eax
005bb1a8 jmp 0x5ba84f
005bb1ad mov eax, dword ptr [esi + 0x30]
005bb1b0 lea ecx, [esi + 0x3c]
005bb1b3 push 0
005bb1b5 cmp eax, 2
005bb1b8 jne 0x5bb238
005bb1ba push 0xb454d8
005bb1bf call 0x4054f0
005bb1c4 movss xmm2, dword ptr [0xbc7a28]
005bb1cc movss xmm1, dword ptr [0xbc7a2c]
005bb1d4 mulss xmm2, dword ptr [0xb6a864]
005bb1dc mulss xmm1, dword ptr [0xb6a864]
005bb1e4 movss dword ptr [esi + 0xd8], xmm2
005bb1ec movss dword ptr [esi + 0xdc], xmm1
005bb1f4 call 0x6c3d90
005bb1f9 mov dword ptr [esi + 0xf0], 0
005bb203 movd xmm0, eax
005bb207 cvtdq2pd xmm0, xmm0
005bb20b shr eax, 0x1f
005bb20e addsd xmm0, qword ptr [eax*8 + 0xb6c940]
005bb217 cvtpd2ps xmm0, xmm0
005bb21b mulss xmm0, dword ptr [0xb6a19c]
005bb223 mulss xmm0, dword ptr [0xb6ac40]
005bb22b movss dword ptr [esi + 0xe0], xmm0
005bb233 jmp 0x5ba855
005bb238 cmp eax, 1
005bb23b jne 0x5bb2f0
005bb241 push 0xb43ad0
005bb246 call 0x4054f0
005bb24b call 0x6c3d90
005bb250 movss xmm2, dword ptr [0xb6a19c]
005bb258 xorps xmm0, xmm0
005bb25b cvtsi2sd xmm0, eax
005bb25f shr eax, 0x1f
005bb262 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
005bb26b cvtpd2ps xmm1, xmm0
005bb26f mulss xmm1, xmm2
005bb273 call 0x6c3d90
005bb278 mulss xmm1, dword ptr [0xb6a480]
005bb280 xorps xmm0, xmm0
005bb283 cvtsi2sd xmm0, eax
005bb287 shr eax, 0x1f
005bb28a addss xmm1, dword ptr [0xb6a480]
005bb292 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
005bb29b movss dword ptr [esi + 0xdc], xmm1
005bb2a3 cvtpd2ps xmm0, xmm0
005bb2a7 mulss xmm0, xmm2
005bb2ab addss xmm0, dword ptr [0xb6a614]
005bb2b3 movss dword ptr [esi + 0xd8], xmm0
005bb2bb call 0x6c3d90
005bb2c0 xorps xmm0, xmm0
005bb2c3 cvtsi2sd xmm0, eax
005bb2c7 shr eax, 0x1f
005bb2ca addsd xmm0, qword ptr [eax*8 + 0xb6c940]
005bb2d3 cvtpd2ps xmm0, xmm0
005bb2d7 mulss xmm0, xmm2
005bb2db mulss xmm0, dword ptr [0xb6ac40]
005bb2e3 movss dword ptr [esi + 0xe0], xmm0
005bb2eb jmp 0x5ba855
005bb2f0 mov eax, dword ptr [esi + 0x164]
005bb2f6 or dword ptr [esi + 0x160], 0x200000
005bb300 mov dword ptr [esi + 0x164], eax
005bb306 or dword ptr [ecx + 0x110], 0x20
005bb30d push 0xb454cc
005bb312 call 0x4054f0
005bb317 mov dword ptr [esi + 0x3ac], 0x2d
005bb321 jmp 0x5ba855
005bb326 mov eax, dword ptr [esi + 0x30]
005bb329 lea ecx, [esi + 0x3c]
005bb32c mov dword ptr [ebp - 0xbc], ecx
005bb332 cmp eax, 2
005bb335 jne 0x5bb3bb
005bb33b push 0
005bb33d push 0xb454d8
005bb342 call 0x4054f0
005bb347 movss xmm2, dword ptr [0xbc7a28]
005bb34f movss xmm1, dword ptr [0xbc7a2c]
005bb357 mulss xmm2, dword ptr [0xb6a50c]
005bb35f mulss xmm1, dword ptr [0xb6a50c]
005bb367 movss dword ptr [esi + 0xd8], xmm2
005bb36f movss dword ptr [esi + 0xdc], xmm1
005bb377 call 0x6c3d90
005bb37c mov dword ptr [esi + 0xf0], 0x3f800000
005bb386 movd xmm0, eax
005bb38a cvtdq2pd xmm0, xmm0
005bb38e shr eax, 0x1f
005bb391 addsd xmm0, qword ptr [eax*8 + 0xb6c940]
005bb39a cvtpd2ps xmm0, xmm0
005bb39e mulss xmm0, dword ptr [0xb6a19c]
005bb3a6 mulss xmm0, dword ptr [0xb6ac40]
005bb3ae movss dword ptr [esi + 0xe0], xmm0
005bb3b6 jmp 0x5ba855
005bb3bb cmp eax, 1
005bb3be jne 0x5bb44a
005bb3c4 push 0
005bb3c6 push 0xb454c4
005bb3cb call 0x405850
005bb3d0 mov esi, dword ptr [ebp - 0xbc]
005bb3d6 mov ecx, esi
005bb3d8 push 1
005bb3da call 0x4062c0
005bb3df push 2
005bb3e1 lea ecx, [ebp - 0x20]
005bb3e4 mov byte ptr [eax + 0x74], 0
005bb3e8 call 0x95ed30
005bb3ed push 0
005bb3ef mov ecx, esi
005bb3f1 call 0x4062c0
005bb3f6 mov edx, dword ptr [ebp - 0x1c]
005bb3f9 mov ecx, dword ptr [ebp - 0x20]
005bb3fc push 2
005bb3fe mov dword ptr [eax + 0x7c], edx
005bb401 mov edx, dword ptr [ebp - 0x18]
005bb404 mov dword ptr [eax + 0x78], ecx
005bb407 lea ecx, [ebp - 0x20]
005bb40a mov dword ptr [eax + 0x80], edx
005bb410 mov edx, dword ptr [ebp - 0x14]
005bb413 mov dword ptr [eax + 0x84], edx
005bb419 call 0x95ed30
005bb41e push 1
005bb420 mov ecx, esi
005bb422 call 0x4062c0
005bb427 mov ecx, dword ptr [ebp - 0x20]
005bb42a mov dword ptr [eax + 0x78], ecx
005bb42d mov ecx, dword ptr [ebp - 0x1c]
005bb430 mov dword ptr [eax + 0x7c], ecx
005bb433 mov ecx, dword ptr [ebp - 0x18]
005bb436 mov dword ptr [eax + 0x80], ecx
005bb43c mov ecx, dword ptr [ebp - 0x14]
005bb43f mov dword ptr [eax + 0x84], ecx
005bb445 jmp 0x5ba855
005bb44a mov eax, dword ptr [esi + 0x164]
005bb450 or dword ptr [esi + 0x160], 0x200000
005bb45a mov dword ptr [esi + 0x164], eax
005bb460 or dword ptr [ecx + 0x110], 0x20
005bb467 lea ecx, [ebp - 0x20]
005bb46a push 2
005bb46c call 0x95ed30
005bb471 push 2
005bb473 lea ecx, [esi + 0x3c]
005bb476 call 0x4062c0
005bb47b mov ecx, dword ptr [ebp - 0x20]
005bb47e push 0
005bb480 push 0xb41d80
005bb485 mov dword ptr [eax + 0x78], ecx
005bb488 mov ecx, dword ptr [ebp - 0x1c]
005bb48b mov dword ptr [eax + 0x7c], ecx
005bb48e mov ecx, dword ptr [ebp - 0x18]
005bb491 mov dword ptr [eax + 0x80], ecx
005bb497 mov ecx, dword ptr [ebp - 0x14]
005bb49a mov dword ptr [eax + 0x84], ecx
005bb4a0 lea ecx, [esi + 0x3c]
005bb4a3 call 0x4054f0
005bb4a8 mov dword ptr [esi + 0x3a4], 0
005bb4b2 jmp 0x5ba855
005bb4b7 mov eax, dword ptr [esi + 0x164]
005bb4bd mov ecx, edi
005bb4bf or dword ptr [esi + 0x160], 0x200000
005bb4c9 push 0
005bb4cb push 0xb3fd8c
005bb4d0 mov dword ptr [esi + 0x164], eax
005bb4d6 call 0x4054f0
005bb4db jmp 0x5ba855
005bb4e0 mov eax, dword ptr [esi + 0x164]
005bb4e6 mov ecx, edi
005bb4e8 or dword ptr [esi + 0x160], 0x200000
005bb4f2 push 0
005bb4f4 push 0xb3fd8c
005bb4f9 mov dword ptr [esi + 0x164], eax
005bb4ff call 0x4054f0
005bb504 mov eax, dword ptr [0xbfd65c]
005bb509 mov dword ptr [esi + 0x2b0], 0xc2c80000
005bb513 mov eax, dword ptr [eax + 0x18190]
005bb519 mov ecx, eax
005bb51b mov dword ptr [ebp - 0xbc], eax
005bb521 call 0x7cf750
005bb526 cmp eax, 1
005bb529 jle 0x5ba855
005bb52f mov ecx, dword ptr [ebp - 0xbc]
005bb535 xor al, al
005bb537 push 0
005bb539 push 0
005bb53b push -1
005bb53d push 0xae
005bb542 mov byte ptr [ebp - 0xb5], al
005bb548 add ecx, 0x1218
005bb54e push 0x3e8
005bb553 lea eax, [ebp - 0x20]
005bb556 push eax
005bb557 call 0x415ed0
005bb55c mov dword ptr [ebp - 4], 0x18
005bb563 xor ecx, ecx
005bb565 mov eax, dword ptr [ebp - 0x14]
005bb568 mov dword ptr [ebp - 0xac], ecx
005bb56e test eax, eax
005bb570 je 0x5bb613
005bb576 mov edx, dword ptr [ebp - 0x1c]
005bb579 nop dword ptr [eax]
005bb580 mov ecx, dword ptr [edx + ecx*4]
005bb583 cmp dword ptr [ecx + 0x3a0], 0
005bb58a je 0x5bb5f5
005bb58c mov eax, dword ptr [ecx + 0x294]
005bb592 mov ecx, dword ptr [ecx + 0x298]
005bb598 mov dword ptr [ebp - 0xc0], eax
005bb59e mov eax, dword ptr [0xbfd65c]
005bb5a3 mov dword ptr [ebp - 0xbc], ecx
005bb5a9 mov edi, dword ptr [eax + 0x18190]
005bb5af lea eax, [esi + 0x294]
005bb5b5 push eax
005bb5b6 mov ecx, edi
005bb5b8 call 0x7ce950
005bb5bd mov esi, eax
005bb5bf mov ecx, edi
005bb5c1 lea eax, [ebp - 0xc0]
005bb5c7 push eax
005bb5c8 call 0x7ce950
005bb5cd mov edx, dword ptr [ebp - 0x1c]
005bb5d0 cmp eax, esi
005bb5d2 jne 0x5bb5ec
005bb5d4 mov eax, dword ptr [ebp - 0xac]
005bb5da mov ecx, dword ptr [edx + eax*4]
005bb5dd mov eax, dword ptr [ecx]
005bb5df call dword ptr [eax + 0x28]
005bb5e2 mov edx, dword ptr [ebp - 0x1c]
005bb5e5 mov byte ptr [ebp - 0xb5], 1
005bb5ec mov eax, dword ptr [ebp - 0x14]
005bb5ef mov esi, dword ptr [ebp - 0xa8]
005bb5f5 mov ecx, dword ptr [ebp - 0xac]
005bb5fb inc ecx
005bb5fc mov dword ptr [ebp - 0xac], ecx
005bb602 cmp ecx, eax
005bb604 jb 0x5bb580
005bb60a cmp byte ptr [ebp - 0xb5], 0
005bb611 jne 0x5bb654
005bb613 push 0x12
005bb615 push dword ptr [esi + 0x344]
005bb61b lea ecx, [ebp - 0x30]
005bb61e call 0x7a7cd0
005bb623 mov ecx, eax
005bb625 call 0x7a7e20
005bb62a mov ecx, dword ptr [0xbfd65c]
005bb630 push eax
005bb631 push 0
005bb633 push 0
005bb635 push 0xc02fec
005bb63a lea eax, [esi + 0x294]
005bb640 push eax
005bb641 push 7
005bb643 push 0x3e8
005bb648 call 0x422e20
005bb64d mov ecx, eax
005bb64f mov edx, dword ptr [eax]
005bb651 call dword ptr [edx + 0xc]
005bb654 mov dword ptr [ebp - 4], 0xffffffff
005bb65b cmp byte ptr [ebp - 0x20], 0
005bb65f jne 0x5ba84f
005bb665 push dword ptr [ebp - 0x1c]
005bb668 call 0x9eace5
005bb66d add esp, 4
005bb670 jmp 0x5ba84f
005bb675 or dword ptr [esi + 0x160], 0x200000
005bb67f or dword ptr [esi + 0x164], 0x20
005bb686 mov dword ptr [esi + 0x3ac], 0xffffffff
005bb690 mov dword ptr [esi + 0x3c8], 0
005bb69a jmp 0x5ba855
005bb69f push 2
005bb6a1 lea ecx, [ebp - 0x20]
005bb6a4 call 0x95ed30
005bb6a9 push 0
005bb6ab lea ecx, [esi + 0x3c]
005bb6ae call 0x4062c0
005bb6b3 mov ecx, dword ptr [ebp - 0x20]
005bb6b6 mov dword ptr [eax + 0x78], ecx
005bb6b9 mov ecx, dword ptr [ebp - 0x1c]
005bb6bc mov dword ptr [eax + 0x7c], ecx
005bb6bf mov ecx, dword ptr [ebp - 0x18]
005bb6c2 mov dword ptr [eax + 0x80], ecx
005bb6c8 mov ecx, dword ptr [ebp - 0x14]
005bb6cb mov dword ptr [eax + 0x84], ecx
005bb6d1 lea ecx, [esi + 0x334]
005bb6d7 call 0x7a7db0
005bb6dc fmul dword ptr [0xb6a3b0]
005bb6e2 lea ecx, [esi + 0x334]
005bb6e8 mov edi, dword ptr [ebp - 0xa8]
005bb6ee fadd dword ptr [0xb6a5a4]
005bb6f4 fstp dword ptr [ebp - 0xbc]
005bb6fa movss xmm1, dword ptr [ebp - 0xbc]
005bb702 movaps xmm0, xmm1
005bb705 mulss xmm1, dword ptr [0xbc7a2c]
005bb70d mulss xmm0, dword ptr [0xbc7a28]
005bb715 movss dword ptr [edi + 0xdc], xmm1
005bb71d movss dword ptr [edi + 0xd8], xmm0
005bb725 call 0x7a7db0
005bb72a fmul dword ptr [0xb6a2ac]
005bb730 fadd dword ptr [0xb6a278]
005bb736 fstp dword ptr [edi + 0x3c8]
005bb73c jmp 0x5ba84f
005bb741 push 2
005bb743 lea ecx, [ebp - 0x20]
005bb746 call 0x95ed30
005bb74b push 0
005bb74d lea ecx, [esi + 0x3c]
005bb750 call 0x4062c0
005bb755 mov ecx, dword ptr [ebp - 0x20]
005bb758 mov dword ptr [eax + 0x78], ecx
005bb75b mov ecx, dword ptr [ebp - 0x1c]
005bb75e mov dword ptr [eax + 0x7c], ecx
005bb761 mov ecx, dword ptr [ebp - 0x18]
005bb764 mov dword ptr [eax + 0x80], ecx
005bb76a mov ecx, dword ptr [ebp - 0x14]
005bb76d mov dword ptr [eax + 0x84], ecx
005bb773 cmp dword ptr [esi + 0x30], 1
005bb777 jne 0x5bb788
005bb779 mov dword ptr [esi + 0x2b4], 0
005bb783 jmp 0x5ba855
005bb788 mov dword ptr [esi + 0x2b0], 0x40800000
005bb792 jmp 0x5ba855
005bb797 push 2
005bb799 lea ecx, [ebp - 0x20]
005bb79c mov dword ptr [esi + 0x2b0], 0x42a00000
005bb7a6 mov dword ptr [esi + 0xf0], 0x3f19999a
005bb7b0 call 0x95ed30
005bb7b5 push 0
005bb7b7 lea ecx, [esi + 0x3c]
005bb7ba call 0x4062c0
005bb7bf mov ecx, dword ptr [ebp - 0x20]
005bb7c2 mov dword ptr [eax + 0x78], ecx
005bb7c5 mov ecx, dword ptr [ebp - 0x1c]
005bb7c8 mov dword ptr [eax + 0x7c], ecx
005bb7cb mov ecx, dword ptr [ebp - 0x18]
005bb7ce mov dword ptr [eax + 0x80], ecx
005bb7d4 mov ecx, dword ptr [ebp - 0x14]
005bb7d7 mov dword ptr [eax + 0x84], ecx
005bb7dd jmp 0x5ba855
005bb7e2 mov dword ptr [esi + 0x2b0], 0xc2c80000
005bb7ec jmp 0x5ba855
005bb7f1 push 2
005bb7f3 lea ecx, [ebp - 0x20]
005bb7f6 mov dword ptr [esi + 0x2ac], 0x3e8
005bb800 call 0x95ed30
005bb805 push 0
005bb807 lea ecx, [esi + 0x3c]
005bb80a call 0x4062c0
005bb80f mov ecx, dword ptr [ebp - 0x20]
005bb812 mov dword ptr [eax + 0x78], ecx
005bb815 mov ecx, dword ptr [ebp - 0x1c]
005bb818 mov dword ptr [eax + 0x7c], ecx
005bb81b mov ecx, dword ptr [ebp - 0x18]
005bb81e mov dword ptr [eax + 0x80], ecx
005bb824 mov ecx, dword ptr [ebp - 0x14]
005bb827 mov dword ptr [eax + 0x84], ecx
005bb82d jmp 0x5ba855
005bb832 push 2
005bb834 lea ecx, [ebp - 0x30]
005bb837 call 0x95ed30
005bb83c mov edi, dword ptr [ebp - 0xa8]
005bb842 mov esi, eax
005bb844 push 1
005bb846 lea ecx, [edi + 0x3c]
005bb849 call 0x4062c0
005bb84e mov ecx, dword ptr [esi]
005bb850 push 0
005bb852 push 0xb3fd8c
005bb857 mov dword ptr [eax + 0x78], ecx
005bb85a lea ecx, [edi + 0x3c]
005bb85d mov edx, dword ptr [esi + 4]
005bb860 mov dword ptr [eax + 0x7c], edx
005bb863 mov edx, dword ptr [esi + 8]
005bb866 mov dword ptr [eax + 0x80], edx
005bb86c mov edx, dword ptr [esi + 0xc]
005bb86f mov dword ptr [eax + 0x84], edx
005bb875 mov eax, edi
005bb877 mov dword ptr [eax + 0x2b0], 0xc1200000
005bb881 call 0x4054f0
005bb886 jmp 0x5ba84f
005bb88b cmp dword ptr [esi + 0x30], 1
005bb88f jne 0x5bb8c1
005bb891 push 0xb4549c
005bb896 lea ecx, [ebp - 0x38]
005bb899 call 0x407990
005bb89e lea eax, [ebp - 0x38]
005bb8a1 mov dword ptr [ebp - 4], 0x19
005bb8a8 push eax
005bb8a9 push 0
005bb8ab mov ecx, edi
005bb8ad call 0x407340
005bb8b2 lea ecx, [ebp - 0x38]
005bb8b5 mov dword ptr [ebp - 4], 0xffffffff
005bb8bc call 0x407be0
005bb8c1 push 0
005bb8c3 push 0xb40360
005bb8c8 mov ecx, edi
005bb8ca call 0x4054f0
005bb8cf jmp 0x5ba855
005bb8d4 mov byte ptr [esi + 0x169], 0
005bb8db mov dword ptr [esi + 0x3a0], 0
005bb8e5 jmp 0x5ba855
005bb8ea cmp dword ptr [esi + 0x30], 0
005bb8ee jne 0x5bb0fa
005bb8f4 push 8
005bb8f6 push dword ptr [esi + 0x344]
005bb8fc lea ecx, [ebp - 0x20]
005bb8ff call 0x7a7cd0
005bb904 push 4
005bb906 lea ecx, [ebp - 0x20]
005bb909 call 0x7a7d50
005bb90e push 2
005bb910 lea ecx, [ebp - 0x20]
005bb913 mov esi, eax
005bb915 call 0x7a7d50
005bb91a mov edi, dword ptr [ebp - 0xa8]
005bb920 test eax, eax
005bb922 movd xmm0, esi
005bb926 cvtdq2ps xmm0, xmm0
005bb929 setne cl
005bb92c mov byte ptr [edi + 0x13c], cl
005bb932 lea ecx, [edi + 0x3c]
005bb935 push 0
005bb937 mulss xmm0, dword ptr [0xb6aa98]
005bb93f movss dword ptr [ebp - 0xac], xmm0
005bb947 call 0x4062c0
005bb94c movss xmm0, dword ptr [ebp - 0xac]
005bb954 lea ecx, [edi + 0x3c]
005bb957 push 1
005bb959 movss dword ptr [eax + 0x90], xmm0
005bb961 call 0x4062c0
005bb966 movss xmm0, dword ptr [ebp - 0xac]
005bb96e lea ecx, [edi + 0x3c]
005bb971 push 1
005bb973 movss dword ptr [eax + 0x90], xmm0
005bb97b call 0x4062c0
005bb980 push 0
005bb982 push 0xb40360
005bb987 lea ecx, [edi + 0x3c]
005bb98a mov dword ptr [eax + 0x78], 0
005bb991 mov dword ptr [eax + 0x7c], 2
005bb998 mov dword ptr [eax + 0x80], 0
005bb9a2 mov dword ptr [eax + 0x84], 2
005bb9ac call 0x4054f0
005bb9b1 mov dword ptr [edi + 0x2b4], 0
005bb9bb jmp 0x5ba84f
005bb9c0 push 2
005bb9c2 lea ecx, [ebp - 0x20]
005bb9c5 call 0x95ed30
005bb9ca add esi, 0x3c
005bb9cd push 0
005bb9cf mov ecx, esi
005bb9d1 call 0x4062c0
005bb9d6 mov ecx, dword ptr [ebp - 0x20]
005bb9d9 push 2
005bb9db mov dword ptr [eax + 0x78], ecx
005bb9de mov ecx, dword ptr [ebp - 0x1c]
005bb9e1 mov dword ptr [eax + 0x7c], ecx
005bb9e4 mov ecx, dword ptr [ebp - 0x18]
005bb9e7 mov dword ptr [eax + 0x80], ecx
005bb9ed mov ecx, dword ptr [ebp - 0x14]
005bb9f0 mov dword ptr [eax + 0x84], ecx
005bb9f6 lea ecx, [ebp - 0x20]
005bb9f9 call 0x95ed30
005bb9fe push 1
005bba00 mov ecx, esi
005bba02 call 0x4062c0
005bba07 mov ecx, dword ptr [ebp - 0x20]
005bba0a mov edx, dword ptr [ebp - 0x18]
005bba0d push 1
005bba0f mov dword ptr [eax + 0x78], ecx
005bba12 mov ecx, dword ptr [ebp - 0x1c]
005bba15 mov dword ptr [eax + 0x7c], ecx
005bba18 mov ecx, esi
005bba1a mov dword ptr [eax + 0x80], edx
005bba20 mov edx, dword ptr [ebp - 0x14]
005bba23 mov dword ptr [eax + 0x84], edx
005bba29 call 0x4062c0
005bba2e push 0
005bba30 mov ecx, esi
005bba32 mov byte ptr [eax + 0x74], 0
005bba36 call 0x4062c0
005bba3b mov byte ptr [eax + 0x74], 0
005bba3f mov eax, dword ptr [ebp - 0xa8]
005bba45 mov dword ptr [eax + 0x2a4], 0
005bba4f mov dword ptr [eax + 0x2a8], 0xc1a00000
005bba59 jmp 0x5ba855
005bba5e push 0x458
005bba63 call 0x9eacf8
005bba68 mov esi, eax
005bba6a add esp, 4
005bba6d mov dword ptr [ebp - 0xac], esi
005bba73 push 0x403130
005bba78 push 0x4024b0
005bba7d push 4
005bba7f push 0x114
005bba84 lea eax, [esi + 4]
005bba87 mov dword ptr [ebp - 4], 0x1b
005bba8e push eax
005bba8f mov dword ptr [esi], 0xb45a94
005bba95 call 0x9eb0c8
005bba9a mov dword ptr [ebp - 4], 0xffffffff
005bbaa1 mov ecx, dword ptr [ebp - 0xbc]
005bbaa7 push esi
005bbaa8 call 0x5eeac0
005bbaad mov eax, dword ptr [0xbfd65c]
005bbab2 mov eax, dword ptr [eax + 0x18190]
005bbab8 cmp dword ptr [eax + 8], 0x10
005bbabc mov eax, dword ptr [ebp - 0xa8]
005bbac2 jne 0x5bbad3
005bbac4 mov dword ptr [eax + 0x2ac], 0x2710
005bbace jmp 0x5ba855
005bbad3 mov dword ptr [eax + 0x2b0], 0x41200000
005bbadd jmp 0x5ba855
005bbae2 push 0
005bbae4 lea ecx, [esi + 0x3c]
005bbae7 mov dword ptr [esi + 0x3a0], 0
005bbaf1 push 0xb3fd8c
005bbaf6 call 0x4054f0
005bbafb cmp dword ptr [esi + 0x30], 0
005bbaff lea ecx, [esi + 0x3c]
005bbb02 jne 0x5bbb1b
005bbb04 push 1
005bbb06 mov byte ptr [esi + 0x169], 0
005bbb0d call 0x4062c0
005bbb12 mov byte ptr [eax + 0x74], 0
005bbb16 jmp 0x5ba855
005bbb1b push 0
005bbb1d call 0x4062c0
005bbb22 mov byte ptr [eax + 0x74], 0
005bbb26 jmp 0x5ba855
005bbb2b push 0
005bbb2d push 0xb454fc
005bbb32 mov ecx, edi
005bbb34 mov dword ptr [esi + 0x3a0], 0
005bbb3e call 0x4054f0
005bbb43 mov dword ptr [esi + 0x2b4], 0
005bbb4d jmp 0x5ba855
005bbb52 push 0
005bbb54 push 0xb454f4
005bbb59 mov ecx, edi
005bbb5b call 0x4054f0
005bbb60 jmp 0x5ba855
005bbb65 push 0
005bbb67 push 0xb42298
005bbb6c mov ecx, edi
005bbb6e call 0x4054f0
005bbb73 jmp 0x5ba855
005bbb78 mov dword ptr [esi + 0x2b0], 0x41200000
005bbb82 jmp 0x5ba855
005bbb87 movss xmm1, dword ptr [0xb6a4c8]
005bbb8f lea ecx, [ebp - 0x4c]
005bbb92 xorps xmm3, xmm3
005bbb95 call 0x427080
005bbb9a push eax
005bbb9b mov ecx, edi
005bbb9d call 0x402370
005bbba2 mov ecx, dword ptr [ebp - 0xa8]
005bbba8 mov eax, dword ptr [ecx + 0x2c]
005bbbab cmp eax, 0xa0
005bbbb0 jne 0x5bbc55
005bbbb6 cmp dword ptr [edi + 0x80], 0
005bbbbd jg 0x5bbbdb
005bbbbf cmp dword ptr [edi + 0x14], 0x10
005bbbc3 mov eax, edi
005bbbc5 jb 0x5bbbc9
005bbbc7 mov eax, dword ptr [edi]
005bbbc9 push 0
005bbbcb push eax
005bbbcc push 0xa0830c
005bbbd1 push 3
005bbbd3 call 0x95e330
005bbbd8 add esp, 0x10
005bbbdb mov eax, dword ptr [edi + 0x7c]
005bbbde mov dword ptr [eax + 0x28], 1
005bbbe5 cmp dword ptr [edi + 0x80], 0
005bbbec jg 0x5bbc0a
005bbbee cmp dword ptr [edi + 0x14], 0x10
005bbbf2 mov eax, edi
005bbbf4 jb 0x5bbbf8
005bbbf6 mov eax, dword ptr [edi]
005bbbf8 push 0
005bbbfa push eax
005bbbfb push 0xa0830c
005bbc00 push 3
005bbc02 call 0x95e330
005bbc07 add esp, 0x10
005bbc0a mov eax, dword ptr [edi + 0x7c]
005bbc0d mov dword ptr [eax + 0x2c], 0
005bbc14 cmp dword ptr [edi + 0x80], 0
005bbc1b jg 0x5bbc39
005bbc1d cmp dword ptr [edi + 0x14], 0x10
005bbc21 mov eax, edi
005bbc23 jb 0x5bbc27
005bbc25 mov eax, dword ptr [edi]
005bbc27 push 0
005bbc29 push eax
005bbc2a push 0xa0830c
005bbc2f push 3
005bbc31 call 0x95e330
005bbc36 add esp, 0x10
005bbc39 mov eax, dword ptr [edi + 0x7c]
005bbc3c mov byte ptr [eax + 0x74], 0
005bbc40 mov eax, dword ptr [ebp - 0xa8]
005bbc46 mov dword ptr [eax + 0x2b0], 0x40800000
005bbc50 jmp 0x5bbf6f
005bbc55 cmp eax, 0xaf
005bbc5a jne 0x5bbede
005bbc60 mov eax, dword ptr [ecx + 0x164]
005bbc66 or dword ptr [ecx + 0x160], 0x200000
005bbc70 push 0
005bbc72 mov dword ptr [ecx + 0x164], eax
005bbc78 mov ecx, edi
005bbc7a push 0xb3fd8c
005bbc7f call 0x4054f0
005bbc84 push 2
005bbc86 lea ecx, [ebp - 0x20]
005bbc89 call 0x95ed30
005bbc8e cmp dword ptr [edi + 0x80], 0
005bbc95 jg 0x5bbcb3
005bbc97 cmp dword ptr [edi + 0x14], 0x10
005bbc9b mov eax, edi
005bbc9d jb 0x5bbca1
005bbc9f mov eax, dword ptr [edi]
005bbca1 push 0
005bbca3 push eax
005bbca4 push 0xa0830c
005bbca9 push 3
005bbcab call 0x95e330
005bbcb0 add esp, 0x10
005bbcb3 mov ecx, dword ptr [edi + 0x7c]
005bbcb6 mov eax, dword ptr [ebp - 0x20]
005bbcb9 mov dword ptr [ecx + 0x78], eax
005bbcbc mov eax, dword ptr [ebp - 0x1c]
005bbcbf mov dword ptr [ecx + 0x7c], eax
005bbcc2 mov eax, dword ptr [ebp - 0x18]
005bbcc5 mov dword ptr [ecx + 0x80], eax
005bbccb mov eax, dword ptr [ebp - 0x14]
005bbcce mov dword ptr [ecx + 0x84], eax
005bbcd4 cmp dword ptr [edi + 0x80], 0
005bbcdb jg 0x5bbcf9
005bbcdd cmp dword ptr [edi + 0x14], 0x10
005bbce1 mov eax, edi
005bbce3 jb 0x5bbce7
005bbce5 mov eax, dword ptr [edi]
005bbce7 push 0
005bbce9 push eax
005bbcea push 0xa0830c
005bbcef push 3
005bbcf1 call 0x95e330
005bbcf6 add esp, 0x10
005bbcf9 mov eax, dword ptr [edi + 0x7c]
005bbcfc mov byte ptr [eax + 0x74], 0
005bbd00 cmp dword ptr [edi + 0x80], 0
005bbd07 jg 0x5bbd25
005bbd09 cmp dword ptr [edi + 0x14], 0x10
005bbd0d mov eax, edi
005bbd0f jb 0x5bbd13
005bbd11 mov eax, dword ptr [edi]
005bbd13 push 0
005bbd15 push eax
005bbd16 push 0xa0830c
005bbd1b push 3
005bbd1d call 0x95e330
005bbd22 add esp, 0x10
005bbd25 mov eax, dword ptr [edi + 0x7c]
005bbd28 mov dword ptr [eax + 0x28], 1
005bbd2f cmp dword ptr [edi + 0x80], 0
005bbd36 jg 0x5bbd54
005bbd38 cmp dword ptr [edi + 0x14], 0x10
005bbd3c mov eax, edi
005bbd3e jb 0x5bbd42
005bbd40 mov eax, dword ptr [edi]
005bbd42 push 0
005bbd44 push eax
005bbd45 push 0xa0830c
005bbd4a push 3
005bbd4c call 0x95e330
005bbd51 add esp, 0x10
005bbd54 mov eax, dword ptr [edi + 0x7c]
005bbd57 lea ecx, [ebp - 0x20]
005bbd5a push 2
005bbd5c mov dword ptr [eax + 0x2c], 0
005bbd63 call 0x95ed30
005bbd68 cmp dword ptr [edi + 0x80], 1
005bbd6f jg 0x5bbd8d
005bbd71 cmp dword ptr [edi + 0x14], 0x10
005bbd75 mov eax, edi
005bbd77 jb 0x5bbd7b
005bbd79 mov eax, dword ptr [edi]
005bbd7b push 1
005bbd7d push eax
005bbd7e push 0xa0830c
005bbd83 push 3
005bbd85 call 0x95e330
005bbd8a add esp, 0x10
005bbd8d mov ecx, dword ptr [edi + 0x7c]
005bbd90 mov eax, dword ptr [ebp - 0x20]
005bbd93 mov dword ptr [ecx + 0x114], eax
005bbd99 mov eax, dword ptr [ebp - 0x1c]
005bbd9c mov dword ptr [ecx + 0x118], eax
005bbda2 mov eax, dword ptr [ebp - 0x18]
005bbda5 mov dword ptr [ecx + 0x11c], eax
005bbdab mov eax, dword ptr [ebp - 0x14]
005bbdae mov dword ptr [ecx + 0x120], eax
005bbdb4 cmp dword ptr [edi + 0x80], 1
005bbdbb jg 0x5bbdd9
005bbdbd cmp dword ptr [edi + 0x14], 0x10
005bbdc1 mov eax, edi
005bbdc3 jb 0x5bbdc7
005bbdc5 mov eax, dword ptr [edi]
005bbdc7 push 1
005bbdc9 push eax
005bbdca push 0xa0830c
005bbdcf push 3
005bbdd1 call 0x95e330
005bbdd6 add esp, 0x10
005bbdd9 mov eax, dword ptr [edi + 0x7c]
005bbddc mov byte ptr [eax + 0x110], 0
005bbde3 cmp dword ptr [edi + 0x80], 1
005bbdea jg 0x5bbe08
005bbdec cmp dword ptr [edi + 0x14], 0x10
005bbdf0 mov eax, edi
005bbdf2 jb 0x5bbdf6
005bbdf4 mov eax, dword ptr [edi]
005bbdf6 push 1
005bbdf8 push eax
005bbdf9 push 0xa0830c
005bbdfe push 3
005bbe00 call 0x95e330
005bbe05 add esp, 0x10
005bbe08 mov eax, dword ptr [edi + 0x7c]
005bbe0b mov dword ptr [eax + 0xc4], 1
005bbe15 cmp dword ptr [edi + 0x80], 1
005bbe1c jg 0x5bbe3a
005bbe1e cmp dword ptr [edi + 0x14], 0x10
005bbe22 mov eax, edi
005bbe24 jb 0x5bbe28
005bbe26 mov eax, dword ptr [edi]
005bbe28 push 1
005bbe2a push eax
005bbe2b push 0xa0830c
005bbe30 push 3
005bbe32 call 0x95e330
005bbe37 add esp, 0x10
005bbe3a mov eax, dword ptr [edi + 0x7c]
005bbe3d lea ecx, [ebp - 0x20]
005bbe40 push 2
005bbe42 mov dword ptr [eax + 0xc8], 0
005bbe4c call 0x95ed30
005bbe51 cmp dword ptr [edi + 0x80], 2
005bbe58 jg 0x5bbe76
005bbe5a cmp dword ptr [edi + 0x14], 0x10
005bbe5e mov eax, edi
005bbe60 jb 0x5bbe64
005bbe62 mov eax, dword ptr [edi]
005bbe64 push 2
005bbe66 push eax
005bbe67 push 0xa0830c
005bbe6c push 3
005bbe6e call 0x95e330
005bbe73 add esp, 0x10
005bbe76 mov ecx, dword ptr [edi + 0x7c]
005bbe79 xorps xmm2, xmm2
005bbe7c mov eax, dword ptr [ebp - 0x20]
005bbe7f add ecx, 0x1b0
005bbe85 movss xmm3, dword ptr [0xb6a614]
005bbe8d movss xmm1, dword ptr [0xb6a480]
005bbe95 push 1
005bbe97 mov dword ptr [ecx], eax
005bbe99 mov eax, dword ptr [ebp - 0x1c]
005bbe9c mov dword ptr [ecx + 4], eax
005bbe9f mov eax, dword ptr [ebp - 0x18]
005bbea2 mov dword ptr [ecx + 8], eax
005bbea5 mov eax, dword ptr [ebp - 0x14]
005bbea8 push 0
005bbeaa mov dword ptr [ecx + 0xc], eax
005bbead mov eax, dword ptr [ebp - 0xa8]
005bbeb3 push 0xff
005bbeb8 push -1
005bbeba push ecx
005bbebb mov edx, dword ptr [eax]
005bbebd lea ecx, [ebp - 0xa4]
005bbec3 mov dword ptr [esp], 0x3f800000
005bbeca call 0x4325d0
005bbecf mov ecx, dword ptr [ebp - 0xa8]
005bbed5 push eax
005bbed6 call dword ptr [edx + 0x38]
005bbed9 jmp 0x5bbf69
005bbede cmp eax, 0xc1
005bbee3 jne 0x5bbf07
005bbee5 push 1
005bbee7 mov ecx, edi
005bbee9 call 0x4062c0
005bbeee push 1
005bbef0 mov ecx, edi
005bbef2 mov dword ptr [eax + 0x28], 1
005bbef9 call 0x4062c0
005bbefe mov dword ptr [eax + 0x2c], 0
005bbf05 jmp 0x5bbf69
005bbf07 cmp eax, 0xc4
005bbf0c jne 0x5bbf69
005bbf0e mov dword ptr [ecx + 0x2b4], 0
005bbf18 lea ecx, [ebp - 0x20]
005bbf1b push 2
005bbf1d call 0x95ed30
005bbf22 push 0
005bbf24 mov ecx, edi
005bbf26 call 0x4062c0
005bbf2b mov ecx, dword ptr [ebp - 0x20]
005bbf2e push 0
005bbf30 mov dword ptr [eax + 0x78], ecx
005bbf33 mov ecx, dword ptr [ebp - 0x1c]
005bbf36 mov dword ptr [eax + 0x7c], ecx
005bbf39 mov ecx, dword ptr [ebp - 0x18]
005bbf3c mov dword ptr [eax + 0x80], ecx
005bbf42 mov ecx, dword ptr [ebp - 0x14]
005bbf45 mov dword ptr [eax + 0x84], ecx
005bbf4b mov ecx, edi
005bbf4d call 0x4062c0
005bbf52 push 0
005bbf54 mov ecx, edi
005bbf56 mov dword ptr [eax + 0x20], 1
005bbf5d call 0x4062c0
005bbf62 mov dword ptr [eax + 0x24], 1
005bbf69 mov eax, dword ptr [ebp - 0xa8]
005bbf6f push eax
005bbf70 call 0x7fd990
005bbf75 mov ecx, dword ptr [ebp - 0xc]
005bbf78 mov dword ptr fs:[0], ecx
005bbf7f pop ecx
005bbf80 pop edi
005bbf81 pop esi
005bbf82 mov ecx, dword ptr [ebp - 0x10]
005bbf85 xor ecx, ebp
005bbf87 call 0x9eacd7
005bbf8c mov esp, ebp
005bbf8e pop ebp
005bbf8f ret 0x10
005bbf92 push 0xc04a94
