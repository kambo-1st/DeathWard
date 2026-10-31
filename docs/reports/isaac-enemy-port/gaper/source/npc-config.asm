00692960 push ebp
00692961 mov ebp, esp
00692963 push -1
00692965 push 0x9f4600
0069296a mov eax, dword ptr fs:[0]
00692970 push eax
00692971 sub esp, 0xb0
00692977 mov eax, dword ptr [0xbaa3b4]
0069297c xor eax, ebp
0069297e mov dword ptr [ebp - 0x10], eax
00692981 push ebx
00692982 push esi
00692983 push edi
00692984 push eax
00692985 lea eax, [ebp - 0xc]
00692988 mov dword ptr fs:[0], eax
0069298e mov esi, ecx
00692990 mov eax, dword ptr [esi + 0x344]
00692996 movq xmm0, qword ptr [0xa08aac]
0069299e mov dword ptr [ebp - 0xbc], eax
006929a4 mov eax, dword ptr [0xa08ab4]
006929a9 movq qword ptr [ebp - 0xb8], xmm0
006929b1 mov dword ptr [ebp - 0xb0], eax
006929b7 mov byte ptr [esi + 0xb8d], 0
006929be call 0x681ea0
006929c3 cmp dword ptr [esi + 0x288], 0
006929ca je 0x692f42
006929d0 push 1
006929d2 mov ecx, esi
006929d4 call 0x692080
006929d9 movss xmm0, dword ptr [0xbc7a28]
006929e1 lea eax, [esi + 0x54]
006929e4 movss dword ptr [esi + 0xd8], xmm0
006929ec movss xmm0, dword ptr [0xbc7a2c]
006929f4 movss dword ptr [esi + 0xdc], xmm0
006929fc cmp dword ptr [esi + 0x68], 0x10
00692a00 jb 0x692a05
00692a02 mov eax, dword ptr [esi + 0x54]
00692a05 push 1
00692a07 push eax
00692a08 lea ecx, [esi + 0x3c]
00692a0b call 0x405740
00692a10 test al, al
00692a12 je 0x692a34
00692a14 mov eax, dword ptr [esi + 0x70]
00692a17 test eax, eax
00692a19 je 0x692a34
00692a1b lea ecx, [esi + 0x6c]
00692a1e xorps xmm1, xmm1
00692a21 call 0x403c00
00692a26 mov eax, dword ptr [esi + 0x70]
00692a29 test eax, eax
00692a2b je 0x692a34
00692a2d mov byte ptr [esi + 0x80], 0
00692a34 mov ecx, dword ptr [esi + 0x288]
00692a3a movss xmm0, dword ptr [0xb6a274]
00692a42 push 1
00692a44 movss dword ptr [ebp - 0x90], xmm0
00692a4c mov al, byte ptr [ecx + 0x58]
00692a4f mov byte ptr [esi + 0xb8c], al
00692a55 mov al, byte ptr [ecx + 0x2c]
00692a58 mov byte ptr [esi + 0xb8d], al
00692a5e mov eax, dword ptr [ecx + 0xe0]
00692a64 mov dword ptr [esi + 0xb90], eax
00692a6a mov eax, dword ptr [ecx + 0xe4]
00692a70 mov ecx, dword ptr [0xbfd65c]
00692a76 add ecx, 0x1ba40
00692a7c mov dword ptr [esi + 0xb94], eax
00692a82 push ecx
00692a83 push 0xd0
00692a88 call 0x91d340
00692a8d test eax, eax
00692a8f je 0x692aa1
00692a91 movss xmm0, dword ptr [0xb6a350]
00692a99 movss dword ptr [ebp - 0x90], xmm0
00692aa1 mov ecx, dword ptr [0xbfd65c]
00692aa7 cmp dword ptr [ecx], 0xc
00692aaa jne 0x692abc
00692aac movss xmm0, dword ptr [0xb6a53c]
00692ab4 movss dword ptr [ebp - 0x90], xmm0
00692abc push 1
00692abe push 0
00692ac0 add ecx, 0x1ba40
00692ac6 push 5
00692ac8 call 0x91d550
00692acd test eax, eax
00692acf je 0x692b01
00692ad1 mov ecx, dword ptr [0xbfd65c]
00692ad7 push 5
00692ad9 lea ecx, [ecx + 0x1ba40]
00692adf call 0x91db10
00692ae4 movd xmm0, eax
00692ae8 cvtdq2ps xmm0, xmm0
00692aeb addss xmm0, xmm0
00692aef mulss xmm0, dword ptr [ebp - 0x90]
00692af7 movss dword ptr [ebp - 0x90], xmm0
00692aff jmp 0x692b09
00692b01 movss xmm0, dword ptr [ebp - 0x90]
00692b09 mov edi, dword ptr [0xbfd65c]
00692b0f mov ebx, dword ptr [edi + 0x18190]
00692b15 mov al, byte ptr [ebx]
00692b17 mov byte ptr [ebp - 0x91], al
00692b1d test al, al
00692b1f je 0x692b31
00692b21 mulss xmm0, dword ptr [0xb6a350]
00692b29 movss dword ptr [ebp - 0x90], xmm0
00692b31 mov eax, dword ptr [edi + 0x1bb58]
00692b37 lea ecx, [edi + 0x1bb58]
00692b3d mov dword ptr [ebp - 0x98], eax
00692b43 lea eax, [ebp - 0x9c]
00692b49 push eax
00692b4a lea eax, [ebp - 0xa8]
00692b50 mov dword ptr [ebp - 0x9c], 0xd
00692b5a push eax
00692b5b call 0x4206b0
00692b60 mov eax, dword ptr [ebp - 0xa0]
00692b66 cmp byte ptr [eax + 0xd], 0
00692b6a jne 0x692b8a
00692b6c cmp dword ptr [eax + 0x10], 0xd
00692b70 jg 0x692b8a
00692b72 cmp eax, dword ptr [ebp - 0x98]
00692b78 je 0x692b8a
00692b7a movss xmm0, dword ptr [0xb6a614]
00692b82 movss dword ptr [ebp - 0x90], xmm0
00692b8a cmp byte ptr [esi + 0xb8d], 0
00692b91 mov eax, dword ptr [esi + 0x288]
00692b97 je 0x692e7e
00692b9d mov ecx, dword ptr [eax + 0x6c]
00692ba0 sub ecx, dword ptr [eax + 0x68]
00692ba3 mov eax, 0x84210843
00692ba8 imul ecx
00692baa mov eax, dword ptr [esi + 0x320]
00692bb0 add edx, ecx
00692bb2 sar edx, 6
00692bb5 mov ebx, edx
00692bb7 shr ebx, 0x1f
00692bba add ebx, edx
00692bbc test eax, eax
00692bbe je 0x692bd0
00692bc0 cmp dword ptr [eax + 0x28], 0x19b
00692bc7 jne 0x692bd0
00692bc9 xor ebx, ebx
00692bcb jmp 0x692d60
00692bd0 test ebx, ebx
00692bd2 jle 0x692d60
00692bd8 cmp dword ptr [esi + 0x30], 0
00692bdc jne 0x692d60
00692be2 mov eax, dword ptr [0xbfd680]
00692be7 cmp byte ptr [eax + 0x4f], 0
00692beb jne 0x692c0d
00692bed cmp dword ptr [eax + 8], 2
00692bf1 jne 0x692d60
00692bf7 cmp dword ptr [edi + 0x1c3204], 0
00692bfe ja 0x692c0d
00692c00 cmp byte ptr [edi + 0x1c31a1], 0
00692c07 je 0x692d60
00692c0d cmp byte ptr [eax + 0x6d], 0
00692c11 movss xmm0, dword ptr [0xb6a2cc]
00692c19 movss dword ptr [ebp - 0x90], xmm0
00692c21 jne 0x692c3b
00692c23 cmp dword ptr [eax + 8], 2
00692c27 jne 0x692c4b
00692c29 cmp dword ptr [edi + 0x1c3204], 0
00692c30 ja 0x692c3b
00692c32 cmp byte ptr [edi + 0x1c31a1], 0
00692c39 je 0x692c4b
00692c3b movss xmm0, dword ptr [0xb6a3b0]
00692c43 movss dword ptr [ebp - 0x90], xmm0
00692c4b cmp dword ptr [edi + 0x243624], 3
00692c52 jne 0x692c64
00692c54 movss xmm0, dword ptr [0xb6a4c4]
00692c5c movss dword ptr [ebp - 0x90], xmm0
00692c64 push 1
00692c66 push 0
00692c68 lea ecx, [edi + 0x1ba40]
00692c6e push 5
00692c70 call 0x91d550
00692c75 test eax, eax
00692c77 je 0x692ca7
00692c79 mov ecx, dword ptr [0xbfd65c]
00692c7f push 5
00692c81 lea ecx, [ecx + 0x1ba40]
00692c87 call 0x91db10
00692c8c movd xmm0, eax
00692c90 cvtdq2ps xmm0, xmm0
00692c93 addss xmm0, xmm0
00692c97 mulss xmm0, dword ptr [ebp - 0x90]
00692c9f movss dword ptr [ebp - 0x90], xmm0
00692ca7 mov eax, dword ptr [0xbfd65c]
00692cac cmp dword ptr [eax + 0x1c319c], 0x22
00692cb3 je 0x692cbe
00692cb5 cmp dword ptr [eax + 0x1c33f8], 1
00692cbc jl 0x692cce
00692cbe movss xmm0, dword ptr [0xb6a614]
00692cc6 movss dword ptr [ebp - 0x90], xmm0
00692cce mov eax, dword ptr [eax + 0x18190]
00692cd4 mov eax, dword ptr [eax + 4]
00692cd7 test eax, eax
00692cd9 je 0x692cde
00692cdb mov eax, dword ptr [eax + 0x5c]
00692cde movq xmm0, qword ptr [0xa08adc]
00692ce6 lea ecx, [ebp - 0xac]
00692cec mov dword ptr [ebp - 0xac], eax
00692cf2 mov eax, dword ptr [0xa08ae4]
00692cf7 movq qword ptr [ebp - 0xa8], xmm0
00692cff mov dword ptr [ebp - 0xa0], eax
00692d05 call 0x7a7db0
00692d0a movss xmm1, dword ptr [ebp - 0x90]
00692d12 fstp dword ptr [ebp - 0x98]
00692d18 comiss xmm1, dword ptr [ebp - 0x98]
00692d1f jbe 0x692d31
00692d21 push ebx
00692d22 lea ecx, [ebp - 0xac]
00692d28 call 0x7a7d50
00692d2d inc eax
00692d2e mov dword ptr [esi + 0x30], eax
00692d31 mov eax, dword ptr [esi + 0x288]
00692d37 cmp dword ptr [eax], 0x2d
00692d3a jne 0x692d5a
00692d3c cmp dword ptr [esi + 0x30], 2
00692d40 jne 0x692d5a
00692d42 mov edi, dword ptr [0xbfd65c]
00692d48 cmp dword ptr [edi + 0x1c319c], 0x1e
00692d4f jne 0x692d60
00692d51 mov dword ptr [esi + 0x30], 0
00692d58 jmp 0x692d60
00692d5a mov edi, dword ptr [0xbfd65c]
00692d60 mov eax, dword ptr [edi + 4]
00692d63 cmp eax, 4
00692d66 je 0x692d6d
00692d68 cmp eax, 5
00692d6b jne 0x692d8f
00692d6d mov eax, dword ptr [esi + 0x288]
00692d73 mov eax, dword ptr [eax]
00692d75 cmp eax, 0x2d
00692d78 jne 0x692d83
00692d7a mov dword ptr [esi + 0x30], 3
00692d81 jmp 0x692d8f
00692d83 cmp eax, 0x4e
00692d86 jne 0x692d8f
00692d88 mov dword ptr [esi + 0x30], 1
00692d8f mov ecx, dword ptr [esi + 0x30]
00692d92 test ecx, ecx
00692d94 je 0x692f1c
00692d9a cmp ecx, ebx
00692d9c ja 0x692f1c
00692da2 mov eax, dword ptr [esi + 0x288]
00692da8 imul ecx, ecx, 0x7c
00692dab mov eax, dword ptr [eax + 0x68]
00692dae add ecx, -0x7c
00692db1 add eax, ecx
00692db3 lea ecx, [ebp - 0x8c]
00692db9 push eax
00692dba call 0x678450
00692dbf mov dword ptr [ebp - 4], 0
00692dc6 mov eax, dword ptr [esi + 0x30]
00692dc9 sub eax, 1
00692dcc mov dword ptr [esi + 0xbc8], eax
00692dd2 js 0x692e22
00692dd4 cmp eax, ebx
00692dd6 jge 0x692e22
00692dd8 movss xmm2, dword ptr [ebp - 0x18]
00692ddd movaps xmm0, xmm2
00692de0 movaps xmm1, xmm2
00692de3 mulss xmm0, dword ptr [esi + 0xdc]
00692deb mulss xmm1, dword ptr [esi + 0xd8]
00692df3 movss dword ptr [esi + 0xdc], xmm0
00692dfb movss xmm0, dword ptr [ebp - 0x14]
00692e00 mulss xmm0, dword ptr [esi + 0x2dc]
00692e08 movss dword ptr [esi + 0xd8], xmm1
00692e10 movss dword ptr [esi + 0xb88], xmm2
00692e18 movss dword ptr [esi + 0x2dc], xmm0
00692e20 jmp 0x692e3c
00692e22 push eax
00692e23 push 0xb4906c
00692e28 push 0
00692e2a call 0x95e330
00692e2f add esp, 0xc
00692e32 mov dword ptr [esi + 0xbc8], 0xffffffff
00692e3c mov eax, dword ptr [esi]
00692e3e mov ecx, esi
00692e40 call dword ptr [eax + 0x5c]
00692e43 push 1
00692e45 mov ecx, esi
00692e47 call 0x692080
00692e4c push 0
00692e4e lea eax, [esi + 0x54]
00692e51 push eax
00692e52 lea ecx, [esi + 0x3c]
00692e55 call 0x405800
00692e5a lea ecx, [ebp - 0x30]
00692e5d mov dword ptr [ebp - 4], 0xffffffff
00692e64 call 0x407be0
00692e69 lea ecx, [ebp - 0x48]
00692e6c call 0x407be0
00692e71 lea ecx, [ebp - 0x60]
00692e74 call 0x407be0
00692e79 jmp 0x692f1c
00692e7e cmp byte ptr [eax + 0x34], 0
00692e82 je 0x692f1c
00692e88 cmp byte ptr [esi + 0xbb3], 0
00692e8f jne 0x692f25
00692e95 cmp byte ptr [ebp - 0x91], 0
00692e9c jne 0x692f1c
00692e9e push 4
00692ea0 mov ecx, ebx
00692ea2 call 0x68f510
00692ea7 test al, al
00692ea9 jne 0x692f1c
00692eab cmp dword ptr [ebx + 8], 5
00692eaf jne 0x692eba
00692eb1 cmp dword ptr [esi + 0x28], 0x379
00692eb8 je 0x692f1c
00692eba lea ecx, [ebp - 0xbc]
00692ec0 call 0x7a7db0
00692ec5 movss xmm1, dword ptr [ebp - 0x90]
00692ecd fstp dword ptr [ebp - 0x98]
00692ed3 comiss xmm1, dword ptr [ebp - 0x98]
00692eda ja 0x692f15
00692edc mov eax, dword ptr [0xbfd65c]
00692ee1 cmp dword ptr [eax + 0x1c319c], 0x22
00692ee8 je 0x692f15
00692eea cmp dword ptr [eax + 0x1c33f8], 1
00692ef1 jl 0x692f1c
00692ef3 lea ecx, [ebp - 0xbc]
00692ef9 call 0x7a7db0
00692efe movss xmm0, dword ptr [0xb6a38c]
00692f06 fstp dword ptr [ebp - 0x98]
00692f0c comiss xmm0, dword ptr [ebp - 0x98]
00692f13 jbe 0x692f1c
00692f15 mov byte ptr [esi + 0xbb3], 1
00692f1c cmp byte ptr [esi + 0xbb3], 0
00692f23 je 0x692f57
00692f25 push 1
00692f27 push dword ptr [esi + 0xbb4]
00692f2d lea ecx, [ebp - 0xbc]
00692f33 call 0x7a7e20
00692f38 push eax
00692f39 mov ecx, esi
00692f3b call 0x6a6570
00692f40 jmp 0x692f57
00692f42 push dword ptr [esi + 0x2c]
00692f45 push dword ptr [esi + 0x28]
00692f48 push 0xb48fd8
00692f4d push 0
00692f4f call 0x95e330
00692f54 add esp, 0x10
00692f57 mov ecx, dword ptr [ebp - 0xc]
00692f5a mov dword ptr fs:[0], ecx
00692f61 pop ecx
00692f62 pop edi
00692f63 pop esi
00692f64 pop ebx
00692f65 mov ecx, dword ptr [ebp - 0x10]
00692f68 xor ecx, ebp
00692f6a call 0x9eacd7
00692f6f mov esp, ebp
00692f71 pop ebp
00692f72 ret 
