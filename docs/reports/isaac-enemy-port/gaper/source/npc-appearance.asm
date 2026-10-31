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
