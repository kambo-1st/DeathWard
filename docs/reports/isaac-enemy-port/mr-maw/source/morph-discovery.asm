00697c60 push ebp
00697c61 mov ebp, esp
00697c63 and esp, 0xfffffff8
00697c66 sub esp, 0x30
00697c69 mov eax, dword ptr [0xbaa3b4]
00697c6e xor eax, esp
00697c70 mov dword ptr [esp + 0x2c], eax
00697c74 mov eax, dword ptr [ebp + 0x14]
00697c77 mov edx, dword ptr [ebp + 0xc]
00697c7a push esi
00697c7b mov esi, ecx
00697c7d mov ecx, dword ptr [ebp + 0x10]
00697c80 push edi
00697c81 mov edi, dword ptr [ebp + 8]
00697c84 cmp edi, dword ptr [esi + 0x28]
00697c87 jne 0x697cb4
00697c89 cmp edx, dword ptr [esi + 0x2c]
00697c8c jne 0x697cb4
00697c8e cmp ecx, dword ptr [esi + 0x30]
00697c91 jne 0x697cb4
00697c93 test eax, eax
00697c95 js 0x697c9f
00697c97 cmp eax, dword ptr [esi + 0xbb4]
00697c9d jne 0x697cb4
00697c9f xor al, al
00697ca1 pop edi
00697ca2 pop esi
00697ca3 mov ecx, dword ptr [esp + 0x2c]
00697ca7 xor ecx, esp
00697ca9 call 0x9eacd7
00697cae mov esp, ebp
00697cb0 pop ebp
00697cb1 ret 0x10
00697cb4 mov dword ptr [esi + 0x28], edi
00697cb7 mov dword ptr [esi + 0x2c], edx
00697cba mov dword ptr [esi + 0x30], ecx
00697cbd test eax, eax
00697cbf js 0x697cce
00697cc1 mov dword ptr [esi + 0xbb4], eax
00697cc7 mov byte ptr [esi + 0xbb3], 1
00697cce push ecx
00697ccf mov ecx, dword ptr [0xbfd680]
00697cd5 push edx
00697cd6 push edi
00697cd7 lea ecx, [ecx + 0x29f88]
00697cdd call 0x66d910
00697ce2 test eax, eax
00697ce4 je 0x697cfd
00697ce6 cmp byte ptr [eax + 0x34], 0
00697cea jne 0x697cfd
00697cec mov dword ptr [esi + 0xbb4], 0xffffffff
00697cf6 mov byte ptr [esi + 0xbb3], 0
00697cfd xor eax, eax
00697cff mov dword ptr [esi + 0xbb8], 0
00697d09 mov word ptr [esi + 0xbc4], ax
00697d10 mov ecx, esi
00697d12 mov eax, dword ptr [esi]
00697d14 mov dword ptr [esi + 0xbbc], 0
00697d1e mov dword ptr [esi + 0xbc0], 0x3f800000
00697d28 mov dword ptr [esi + 0xafc], 0x3f800000
00697d32 mov dword ptr [esi + 0xaf8], 0
00697d3c call dword ptr [eax + 0x5c]
00697d3f movss xmm1, dword ptr [esi + 0x30c]
00697d47 mov ecx, esi
00697d49 movaps xmm0, xmm1
00697d4c mov dword ptr [esi + 0xb88], 0x3f800000
00697d56 mulss xmm0, dword ptr [0xbc7a28]
00697d5e mulss xmm1, dword ptr [0xbc7a2c]
00697d66 movss dword ptr [esi + 0xd8], xmm0
00697d6e movss dword ptr [esi + 0xdc], xmm1
00697d76 mov eax, dword ptr [esi]
00697d78 call dword ptr [eax + 0x60]
00697d7b movss xmm0, dword ptr [esi + 0xe94]
00697d83 lea eax, [esi + 0x2dc]
00697d89 mulss xmm0, dword ptr [eax]
00697d8d lea ecx, [esi + 0x2d8]
00697d93 mov dword ptr [esi + 0xbac], 0
00697d9d movss dword ptr [eax], xmm0
00697da1 comiss xmm0, dword ptr [ecx]
00697da4 cmova eax, ecx
00697da7 mov eax, dword ptr [eax]
00697da9 mov dword ptr [ecx], eax
00697dab mov eax, dword ptr [esi + 0x1a4]
00697db1 cmp eax, dword ptr [esi + 0x1a8]
00697db7 je 0x697dd5
00697db9 mov edx, dword ptr [esi]
00697dbb lea ecx, [esp + 8]
00697dbf push 1
00697dc1 push 0
00697dc3 push 0xfffffc18
00697dc8 push 1
00697dca call 0x402120
00697dcf push eax
00697dd0 mov ecx, esi
00697dd2 call dword ptr [edx + 0x38]
00697dd5 lea ecx, [esi + 0x364]
00697ddb call 0x7a34f0
00697de0 push dword ptr [esi + 0x2c]
00697de3 mov ecx, dword ptr [0xbfd680]
00697de9 push dword ptr [esi + 0x28]
00697dec add ecx, 0x14
00697def call 0x8861d0
00697df4 push esi
00697df5 mov byte ptr [esi + 0xbb0], 1
00697dfc call 0x6d94d0
00697e01 test al, al
00697e03 je 0x697e0c
00697e05 push ecx
00697e06 push esi
00697e07 call 0x6d9590
00697e0c mov ecx, dword ptr [esp + 0x34]
00697e10 mov al, 1
00697e12 pop edi
00697e13 pop esi
00697e14 xor ecx, esp
00697e16 call 0x9eacd7
00697e1b mov esp, ebp
00697e1d pop ebp
00697e1e ret 0x10
00697e21 int3 
00697e22 int3 
00697e23 int3 
00697e24 int3 
00697e25 int3 
00697e26 int3 
00697e27 int3 
00697e28 int3 
00697e29 int3 
00697e2a int3 
00697e2b int3 
00697e2c int3 
00697e2d int3 
00697e2e int3 
00697e2f int3 
00697e30 push ebp
00697e31 mov ebp, esp
00697e33 sub esp, 0xdc
00697e39 mov eax, dword ptr [0xbaa3b4]
00697e3e xor eax, ebp
00697e40 mov dword ptr [ebp - 4], eax
00697e43 push ebx
00697e44 push esi
00697e45 mov esi, ecx
00697e47 push edi
00697e48 cmp byte ptr [esi + 0xbb3], 0
00697e4f je 0x697f24
00697e55 xor edi, edi
00697e57 cmp dword ptr [esi + 0xbc], edi
00697e5d jbe 0x697ebb
00697e5f xor ecx, ecx
00697e61 mov dword ptr [ebp - 0x84], ecx
00697e67 test edi, edi
00697e69 js 0x697e73
00697e6b cmp edi, dword ptr [esi + 0xbc]
00697e71 jl 0x697e96
00697e73 cmp dword ptr [esi + 0x50], 0x10
00697e77 lea eax, [esi + 0x3c]
00697e7a jb 0x697e7f
00697e7c mov eax, dword ptr [esi + 0x3c]
00697e7f push edi
00697e80 push eax
00697e81 push 0xa0830c
00697e86 push 3
00697e88 call 0x95e330
00697e8d mov ecx, dword ptr [ebp - 0x84]
00697e93 add esp, 0x10
00697e96 mov eax, dword ptr [esi + 0xb8]
00697e9c test byte ptr [eax + ecx + 0x88], 0x10
00697ea4 jne 0x697f0e
00697ea6 inc edi
00697ea7 add ecx, 0x9c
00697ead mov dword ptr [ebp - 0x84], ecx
00697eb3 cmp edi, dword ptr [esi + 0xbc]
00697eb9 jb 0x697e67
00697ebb mov eax, dword ptr [esi + 0xbb4]
00697ec1 lea edi, [esi + 0xe4]
00697ec7 mov ecx, eax
00697ec9 shl ecx, 4
00697ecc sub ecx, eax
00697ece lea eax, [ebp - 0xdc]
00697ed4 shl ecx, 2
00697ed7 push eax
00697ed8 lea ecx, [ecx + 0xbc5700]
00697ede call 0x4f3e00
00697ee3 cmp edi, eax
00697ee5 je 0x697fb5
00697eeb movups xmm0, xmmword ptr [eax]
00697eee movups xmmword ptr [edi], xmm0
00697ef1 movups xmm0, xmmword ptr [eax + 0x10]
00697ef5 movups xmmword ptr [edi + 0x10], xmm0
00697ef9 movq xmm0, qword ptr [eax + 0x20]
00697efe movq qword ptr [edi + 0x20], xmm0
00697f03 mov eax, dword ptr [eax + 0x28]
00697f06 mov dword ptr [edi + 0x28], eax
00697f09 jmp 0x697fb5
00697f0e mov eax, dword ptr [esi + 0xbb4]
00697f14 mov ecx, eax
00697f16 shl ecx, 4
00697f19 sub ecx, eax
00697f1b lea eax, [ecx*4 + 0xbc5710]
00697f22 jmp 0x697f8d
00697f24 mov edi, dword ptr [esi + 0xbc8]
00697f2a test edi, edi
00697f2c js 0x697f87
00697f2e mov eax, dword ptr [esi + 0x288]
00697f34 mov ecx, dword ptr [eax + 0x6c]
00697f37 mov ebx, dword ptr [eax + 0x68]
00697f3a sub ecx, ebx
00697f3c mov eax, 0x84210843
00697f41 imul ecx
00697f43 add edx, ecx
00697f45 sar edx, 6
00697f48 mov eax, edx
00697f4a shr eax, 0x1f
00697f4d add eax, edx
00697f4f cmp edi, eax
00697f51 jge 0x697fb5
00697f53 imul eax, edi, 0x7c
00697f56 lea ecx, [ebp - 0x80]
00697f59 add eax, ebx
00697f5b push eax
00697f5c call 0x678450
00697f61 lea eax, [ebp - 0x80]
00697f64 push eax
00697f65 lea ecx, [esi + 0x3c]
00697f68 call 0x402370
00697f6d lea ecx, [ebp - 0x24]
00697f70 call 0x407be0
00697f75 lea ecx, [ebp - 0x3c]
00697f78 call 0x407be0
00697f7d lea ecx, [ebp - 0x54]
00697f80 call 0x407be0
00697f85 jmp 0x697fb5
00697f87 lea eax, [esi + 0x1b0]
00697f8d lea ecx, [esi + 0xe4]
00697f93 cmp ecx, eax
00697f95 je 0x697fb5
00697f97 movups xmm0, xmmword ptr [eax]
00697f9a movups xmmword ptr [ecx], xmm0
00697f9d movups xmm0, xmmword ptr [eax + 0x10]
00697fa1 movups xmmword ptr [ecx + 0x10], xmm0
00697fa5 movq xmm0, qword ptr [eax + 0x20]
00697faa movq qword ptr [ecx + 0x20], xmm0
00697faf mov eax, dword ptr [eax + 0x28]
00697fb2 mov dword ptr [ecx + 0x28], eax
00697fb5 mov eax, dword ptr [esi + 0x160]
00697fbb and eax, 0x20000000
00697fc0 or eax, 0
00697fc3 je 0x698041
00697fc5 cmp dword ptr [esi + 0x28], 0x17
00697fc9 jne 0x697fd7
00697fcb cmp dword ptr [esi + 0x2c], 0
00697fcf jne 0x697fd7
00697fd1 cmp dword ptr [esi + 0x30], 1
00697fd5 je 0x698041
00697fd7 movaps xmm1, xmmword ptr [0xb6c9c0]
00697fde lea ecx, [esi + 0xe4]
00697fe4 lea eax, [ebp - 0xb0]
00697fea mov dword ptr [ebp - 0x90], 0x3dcccccd
00697ff4 mov dword ptr [ebp - 0x8c], 0x3dcccccd
00697ffe mov dword ptr [ebp - 0x88], 0x3dcccccd
00698008 cmp ecx, eax
0069800a je 0x698041
0069800c mov dword ptr [ecx], 0x3f4ccccd
00698012 mov dword ptr [ecx + 4], 0x3f4ccccd
00698019 mov dword ptr [ecx + 8], 0x3f4ccccd
00698020 mov dword ptr [ecx + 0xc], 0x3f800000
00698027 movq xmm0, qword ptr [ebp - 0x90]
0069802f mov eax, dword ptr [ebp - 0x88]
00698035 movq qword ptr [ecx + 0x20], xmm0
0069803a movups xmmword ptr [ecx + 0x10], xmm1
0069803e mov dword ptr [ecx + 0x28], eax
00698041 cmp dword ptr [esi + 0x28], 0x3c3
00698048 jne 0x698082
0069804a add esi, 0xe4
00698050 cmp esi, 0xbc4fc0
00698056 je 0x698082
00698058 movups xmm0, xmmword ptr [0xbc4fc0]
0069805f movups xmmword ptr [esi], xmm0
00698062 movups xmm0, xmmword ptr [0xbc4fd0]
00698069 movups xmmword ptr [esi + 0x10], xmm0
0069806d movq xmm0, qword ptr [0xbc4fe0]
00698075 movq qword ptr [esi + 0x20], xmm0
0069807a mov eax, dword ptr [0xbc4fe8]
0069807f mov dword ptr [esi + 0x28], eax
00698082 mov ecx, dword ptr [ebp - 4]
00698085 pop edi
00698086 pop esi
00698087 xor ecx, ebp
00698089 pop ebx
0069808a call 0x9eacd7
0069808f mov esp, ebp
00698091 pop ebp
00698092 ret 
00698093 int3 
00698094 int3 
00698095 int3 
00698096 int3 
00698097 int3 
00698098 int3 
00698099 int3 
0069809a int3 
0069809b int3 
0069809c int3 
0069809d int3 
0069809e int3 
0069809f int3 
