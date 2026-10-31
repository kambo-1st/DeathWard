004f8860 push ebx
004f8861 mov ebx, esp
004f8863 sub esp, 8
004f8866 and esp, 0xfffffff8
004f8869 add esp, 4
004f886c push ebp
004f886d mov ebp, dword ptr [ebx + 4]
004f8870 mov dword ptr [esp + 4], ebp
004f8874 mov ebp, esp
004f8876 sub esp, 0x18
004f8879 push esi
004f887a mov esi, ecx
004f887c push edi
004f887d mov eax, dword ptr [esi + 0xab4]
004f8883 test eax, eax
004f8885 jne 0x4f891d
004f888b or dword ptr [esi + 0x160], 1
004f8892 or dword ptr [esi + 0x164], 8
004f8899 mov dword ptr [esi + 0x180], 2
004f88a3 mov dword ptr [esi + 0x17c], eax
004f88a9 mov byte ptr [esi + 0x308], 1
004f88b0 mov dword ptr [esi + 0xab4], 4
004f88ba call 0x6c3d90
004f88bf xor edx, edx
004f88c1 mov dword ptr [esi + 0xb10], 0
004f88cb mov ecx, 0xa
004f88d0 mov dword ptr [esi + 0xaf4], 0
004f88da div ecx
004f88dc mov dword ptr [esi + 0xb14], 0
004f88e6 mov dword ptr [esi + 0x360], edx
004f88ec mov eax, dword ptr [esi + 0x294]
004f88f2 mov dword ptr [esi + 0x28c], eax
004f88f8 mov eax, dword ptr [esi + 0x298]
004f88fe mov dword ptr [esi + 0x290], eax
004f8904 mov eax, dword ptr [esi + 0x164]
004f890a and dword ptr [esi + 0x160], 0xfffffffb
004f8911 mov dword ptr [esi + 0x164], eax
004f8917 mov eax, dword ptr [esi + 0xab4]
004f891d mov ecx, dword ptr [esi + 0x314]
004f8923 lea edi, [esi + 0x314]
004f8929 movss xmm2, dword ptr [0xb6a480]
004f8931 cmp eax, 0x10
004f8934 sete dl
004f8937 mov byte ptr [ebp - 1], dl
004f893a test ecx, ecx
004f893c je 0x4f8aa0
004f8942 movss xmm0, dword ptr [ecx + 0x294]
004f894a movss xmm1, dword ptr [ecx + 0x298]
004f8952 movss dword ptr [esi + 0x28c], xmm0
004f895a movss dword ptr [esi + 0x290], xmm1
004f8962 mov eax, dword ptr [edi]
004f8964 mov dword ptr [esi + 0xaf4], 1
004f896e test eax, eax
004f8970 je 0x4f899f
004f8972 push 0
004f8974 push 0xbeab70
004f8979 push 0xbeab18
004f897e push 0
004f8980 push eax
004f8981 call 0x9ec34c
004f8986 add esp, 0x14
004f8989 test eax, eax
004f898b jne 0x4f899c
004f898d push 0xb40228
004f8992 push 3
004f8994 call 0x95e330
004f8999 add esp, 8
004f899c mov dl, byte ptr [ebp - 1]
004f899f mov ecx, dword ptr [edi]
004f89a1 cmp byte ptr [ecx + 0x16b], 0
004f89a8 je 0x4f89ac
004f89aa mov dl, 1
004f89ac movss xmm0, dword ptr [0xb6a9ec]
004f89b4 movss xmm1, dword ptr [0xb6a264]
004f89bc movss dword ptr [ebp - 8], xmm0
004f89c1 movss xmm0, dword ptr [0xb6a9c8]
004f89c9 movss dword ptr [ebp - 0x10], xmm0
004f89ce movss dword ptr [ebp - 0xc], xmm1
004f89d3 test ecx, ecx
004f89d5 je 0x4f89dd
004f89d7 cmp dword ptr [ecx + 0x28], 0x5a
004f89db jne 0x4f8a04
004f89dd movss xmm0, dword ptr [0xb6a234]
004f89e5 movss dword ptr [ebp - 0xc], xmm0
004f89ea movss xmm0, dword ptr [0xb6aa8c]
004f89f2 movss dword ptr [ebp - 8], xmm0
004f89f7 movss xmm0, dword ptr [0xb6aa60]
004f89ff movss dword ptr [ebp - 0x10], xmm0
004f8a04 test dl, dl
004f8a06 je 0x4f8b90
004f8a0c cmp dword ptr [esi + 0xb10], 0
004f8a13 jle 0x4f8b80
004f8a19 push ecx
004f8a1a mov ecx, dword ptr [0xbfd65c]
004f8a20 lea eax, [esi + 0x28c]
004f8a26 mov dword ptr [esp], 0xc1200000
004f8a2d push eax
004f8a2e mov ecx, dword ptr [ecx + 0x18190]
004f8a34 call 0x7cf0a0
004f8a39 test al, al
004f8a3b je 0x4f8b80
004f8a41 push -1
004f8a43 push 0
004f8a45 push 0
004f8a47 push 0x12
004f8a49 mov ecx, esi
004f8a4b mov dword ptr [esi + 0x17c], 3
004f8a55 call 0x697c60
004f8a5a mov ecx, dword ptr [edi]
004f8a5c test ecx, ecx
004f8a5e je 0x4f8a72
004f8a60 lea eax, [ebp - 0x10]
004f8a63 mov dword ptr [ebp - 0x10], edi
004f8a66 push eax
004f8a67 add ecx, 0x324
004f8a6d call 0x4bc3c0
004f8a72 and dword ptr [esi + 0x160], 0xfffffffe
004f8a79 and dword ptr [esi + 0x164], 0xfffffff7
004f8a80 mov dword ptr [edi], 0
004f8a86 mov byte ptr [esi + 0x308], 0
004f8a8d mov dword ptr [esi + 0x180], 4
004f8a97 pop edi
004f8a98 pop esi
004f8a99 mov esp, ebp
004f8a9b pop ebp
004f8a9c mov esp, ebx
004f8a9e pop ebx
004f8a9f ret 
004f8aa0 cmp dword ptr [esi + 0xaf4], 1
004f8aa7 jne 0x4f8ab0
004f8aa9 mov dl, 1
004f8aab jmp 0x4f89dd
004f8ab0 movss xmm1, dword ptr [0xb6aa3c]
004f8ab8 movss xmm0, dword ptr [esi + 0x28c]
004f8ac0 subss xmm0, xmm1
004f8ac4 mov eax, dword ptr [0xbfd65c]
004f8ac9 mov eax, dword ptr [eax + 0x18190]
004f8acf divss xmm0, xmm1
004f8ad3 mov dword ptr [ebp - 0xc], eax
004f8ad6 addss xmm0, xmm2
004f8ada cvttss2si edi, xmm0
004f8ade mov dword ptr [ebp - 8], edi
004f8ae1 test edi, edi
004f8ae3 lea edi, [esi + 0x314]
004f8ae9 js 0x4f89dd
004f8aef mov eax, dword ptr [eax + 0xc]
004f8af2 cmp dword ptr [ebp - 8], eax
004f8af5 jge 0x4f89dd
004f8afb movss xmm0, dword ptr [esi + 0x290]
004f8b03 subss xmm0, dword ptr [0xb6ab20]
004f8b0b divss xmm0, xmm1
004f8b0f addss xmm0, xmm2
004f8b13 cvttss2si edi, xmm0
004f8b17 mov dword ptr [ebp - 0x10], edi
004f8b1a test edi, edi
004f8b1c lea edi, [esi + 0x314]
004f8b22 js 0x4f89dd
004f8b28 mov edi, dword ptr [ebp - 0xc]
004f8b2b cvttss2si ecx, xmm0
004f8b2f cmp ecx, dword ptr [edi + 0x10]
004f8b32 lea edi, [esi + 0x314]
004f8b38 mov ecx, dword ptr [edi]
004f8b3a jge 0x4f89dd
004f8b40 imul eax, dword ptr [ebp - 0x10]
004f8b44 add eax, dword ptr [ebp - 8]
004f8b47 js 0x4f89ac
004f8b4d cmp eax, 0x1c0
004f8b52 jge 0x4f8b79
004f8b54 mov edi, dword ptr [ebp - 0xc]
004f8b57 mov eax, dword ptr [edi + eax*4 + 0x24]
004f8b5b lea edi, [esi + 0x314]
004f8b61 test eax, eax
004f8b63 je 0x4f8b79
004f8b65 cmp dword ptr [eax + 4], 0xe
004f8b69 jne 0x4f89ac
004f8b6f cmp dword ptr [eax + 0x3c], 0
004f8b73 jne 0x4f89ac
004f8b79 mov dl, 1
004f8b7b jmp 0x4f89dd
004f8b80 mov eax, dword ptr [esi]
004f8b82 mov ecx, esi
004f8b84 call dword ptr [eax + 0x28]
004f8b87 pop edi
004f8b88 pop esi
004f8b89 mov esp, ebp
004f8b8b pop ebp
004f8b8c mov esp, ebx
004f8b8e pop ebx
004f8b8f ret 
004f8b90 test ecx, ecx
004f8b92 je 0x4f8bc1
004f8b94 cmp dword ptr [ecx + 0x70], 0
004f8b98 jne 0x4f8b9e
004f8b9a xor eax, eax
004f8b9c jmp 0x4f8bad
004f8b9e push 0xb40e34
004f8ba3 add ecx, 0x6c
004f8ba6 call 0x405da0
004f8bab mov ecx, dword ptr [edi]
004f8bad test ecx, ecx
004f8baf je 0x4f8bc1
004f8bb1 test eax, eax
004f8bb3 je 0x4f8bbb
004f8bb5 cmp byte ptr [eax + 0xc], 0
004f8bb9 jne 0x4f8bc1
004f8bbb mov byte ptr [ebp - 1], 1
004f8bbf jmp 0x4f8bc5
004f8bc1 mov byte ptr [ebp - 1], 0
004f8bc5 mov eax, dword ptr [esi + 0xab4]
004f8bcb sub eax, 4
004f8bce je 0x4f8ca4
004f8bd4 sub eax, 2
004f8bd7 je 0x4f8c38
004f8bd9 sub eax, 1
004f8bdc jne 0x4f8e1f
004f8be2 push eax
004f8be3 push 0xb42ecc
004f8be8 lea ecx, [esi + 0x3c]
004f8beb call 0x4054f0
004f8bf0 mov eax, dword ptr [esi + 0x28c]
004f8bf6 mov dword ptr [esi + 0x294], eax
004f8bfc mov eax, dword ptr [esi + 0x290]
004f8c02 mov dword ptr [esi + 0x298], eax
004f8c08 cmp dword ptr [esi + 0x70], 0
004f8c0c je 0x4f8c1b
004f8c0e cmp byte ptr [esi + 0x80], 0
004f8c15 jne 0x4f8e1f
004f8c1b mov dword ptr [esi + 0x180], 2
004f8c25 mov dword ptr [esi + 0xab4], 4
004f8c2f pop edi
004f8c30 pop esi
004f8c31 mov esp, ebp
004f8c33 pop ebp
004f8c34 mov esp, ebx
004f8c36 pop ebx
004f8c37 ret 
004f8c38 push 0
004f8c3a push 0xb42ec0
004f8c3f lea ecx, [esi + 0x3c]
004f8c42 call 0x4054f0
004f8c47 mov eax, dword ptr [esi + 0x28c]
004f8c4d mov dword ptr [esi + 0x294], eax
004f8c53 mov eax, dword ptr [esi + 0x290]
004f8c59 mov dword ptr [esi + 0x298], eax
004f8c5f cmp dword ptr [esi + 0x70], 0
004f8c63 je 0x4f8c6e
004f8c65 cmp byte ptr [esi + 0x80], 0
004f8c6c jne 0x4f8c78
004f8c6e mov dword ptr [esi + 0x150], 0
004f8c78 cmp byte ptr [ebp - 1], 0
004f8c7c jne 0x4f8e1f
004f8c82 mov eax, dword ptr [esi + 0x288]
004f8c88 mov dword ptr [esi + 0xab4], 7
004f8c92 mov eax, dword ptr [eax + 0x24]
004f8c95 mov dword ptr [esi + 0x150], eax
004f8c9b pop edi
004f8c9c pop esi
004f8c9d mov esp, ebp
004f8c9f pop ebp
004f8ca0 mov esp, ebx
004f8ca2 pop ebx
004f8ca3 ret 
004f8ca4 push 0
004f8ca6 push 0xb405b4
004f8cab lea ecx, [esi + 0x3c]
004f8cae call 0x4054f0
004f8cb3 cmp byte ptr [ebp - 1], 0
004f8cb7 je 0x4f8cdc
004f8cb9 mov dword ptr [esi + 0x180], 0
004f8cc3 mov dword ptr [esi + 0xab4], 6
004f8ccd mov dword ptr [esi + 0xb10], 0
004f8cd7 jmp 0x4f8e07
004f8cdc mov ecx, dword ptr [esi + 0x360]
004f8ce2 mov eax, dword ptr [0xbfd65c]
004f8ce7 movd xmm1, ecx
004f8ceb movd xmm2, dword ptr [eax + 0x1a30dc]
004f8cf3 cvtdq2ps xmm1, xmm1
004f8cf6 cvtdq2ps xmm2, xmm2
004f8cf9 mulss xmm1, dword ptr [0xb6a874]
004f8d01 mulss xmm2, dword ptr [ebp - 0xc]
004f8d06 divss xmm1, dword ptr [0xb6a974]
004f8d0e mulss xmm2, dword ptr [0xb6a874]
004f8d16 addss xmm2, xmm1
004f8d1a movss dword ptr [ebp - 0xc], xmm2
004f8d1f test cl, 1
004f8d22 jne 0x4f8d30
004f8d24 xorps xmm2, xmmword ptr [0xb6c9b0]
004f8d2b movss dword ptr [ebp - 0xc], xmm2
004f8d30 movaps xmm0, xmm2
004f8d33 call 0x411fe0
004f8d38 movss dword ptr [ebp - 0x14], xmm0
004f8d3d movss xmm0, dword ptr [ebp - 0xc]
004f8d42 call 0x412010
004f8d47 mov edi, dword ptr [edi]
004f8d49 movaps xmm5, xmm0
004f8d4c mov edx, 0x5a
004f8d51 test edi, edi
004f8d53 je 0x4f8d60
004f8d55 cmp dword ptr [edi + 0x28], edx
004f8d58 mov eax, 0x1e
004f8d5d cmove edx, eax
004f8d60 mov ecx, dword ptr [esi + 0xb10]
004f8d66 mov eax, edx
004f8d68 cmp ecx, edx
004f8d6a movd xmm0, edx
004f8d6e cvtdq2ps xmm0, xmm0
004f8d71 cmovl eax, ecx
004f8d74 movd xmm3, eax
004f8d78 lea eax, [ecx + 1]
004f8d7b mov dword ptr [esi + 0xb10], eax
004f8d81 cvtdq2ps xmm3, xmm3
004f8d84 divss xmm3, xmm0
004f8d88 test edi, edi
004f8d8a je 0x4f8d9c
004f8d8c cmp dword ptr [edi + 0x28], 0x66
004f8d90 jne 0x4f8d9c
004f8d92 movss xmm4, dword ptr [0xb6a614]
004f8d9a jmp 0x4f8da4
004f8d9c movss xmm4, dword ptr [0xb6a480]
004f8da4 movss xmm2, dword ptr [ebp - 8]
004f8da9 mulss xmm2, dword ptr [ebp - 0x14]
004f8dae movss xmm0, dword ptr [esi + 0x294]
004f8db6 movss xmm1, dword ptr [esi + 0x298]
004f8dbe mulss xmm2, xmm3
004f8dc2 addss xmm2, dword ptr [esi + 0x28c]
004f8dca subss xmm2, xmm0
004f8dce mulss xmm2, xmm4
004f8dd2 addss xmm2, xmm0
004f8dd6 movss xmm0, dword ptr [ebp - 0x10]
004f8ddb mulss xmm0, xmm5
004f8ddf mulss xmm0, xmm3
004f8de3 addss xmm0, dword ptr [esi + 0x290]
004f8deb movss dword ptr [esi + 0x294], xmm2
004f8df3 subss xmm0, xmm1
004f8df7 mulss xmm0, xmm4
004f8dfb addss xmm0, xmm1
004f8dff movss dword ptr [esi + 0x298], xmm0
004f8e07 movss xmm0, dword ptr [esi + 0x2c4]
004f8e0f mulss xmm0, dword ptr [0xb6a5a4]
004f8e17 movss dword ptr [esi + 0x2c4], xmm0
004f8e1f pop edi
004f8e20 pop esi
004f8e21 mov esp, ebp
004f8e23 pop ebp
004f8e24 mov esp, ebx
004f8e26 pop ebx
004f8e27 ret 
