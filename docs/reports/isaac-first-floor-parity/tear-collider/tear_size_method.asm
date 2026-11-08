00651770 push ebp
00651771 mov ebp, esp
00651773 and esp, 0xfffffff8
00651776 sub esp, 0x4c
00651779 mov eax, dword ptr [0xbaa3b4]
0065177e xor eax, esp
00651780 mov dword ptr [esp + 0x48], eax
00651784 movss xmm1, dword ptr [0xb6a614]
0065178c push ebx
0065178d push esi
0065178e push edi
0065178f mov edi, ecx
00651791 movss dword ptr [esp + 0x10], xmm1
00651797 mov ecx, dword ptr [edi + 0x2c]
0065179a imul ebx, ecx, 0x64
0065179d mov dword ptr [esp + 0x14], ebx
006517a1 cmp ecx, 0x32
006517a4 ja 0x651cb0
006517aa movzx eax, byte ptr [ecx + 0x6520a4]
006517b1 jmp dword ptr [eax*4 + 0x652080]
006517b8 movss xmm2, dword ptr [edi + 0x370]
006517c0 mov esi, 1
006517c5 movss xmm1, dword ptr [0xb6a274]
006517cd mov eax, 0xb46a30
006517d2 movss xmm0, dword ptr [eax]
006517d6 addss xmm0, xmm1
006517da comiss xmm2, xmm0
006517dd jbe 0x6517e8
006517df inc esi
006517e0 add eax, 4
006517e3 cmp esi, 0xd
006517e6 jb 0x6517d2
006517e8 add ebx, esi
006517ea cmp dword ptr [edi + 0x3ac], ebx
006517f0 je 0x6518d1
006517f6 cmp ecx, 1
006517f9 je 0x6518a4
006517ff cmp ecx, 0xc
00651802 je 0x6518a4
00651808 cmp ecx, 0xf
0065180b je 0x6518a4
00651811 cmp ecx, 0x11
00651814 je 0x6518a4
0065181a cmp ecx, 0x22
0065181d je 0x6518a4
00651823 cmp ecx, 0x19
00651826 je 0x6518a4
00651828 cmp ecx, 2
0065182b je 0x65188c
0065182d cmp ecx, 0x1e
00651830 je 0x65188c
00651832 cmp ecx, 0x14
00651835 jne 0x65184f
00651837 mov eax, esi
00651839 mov ecx, 1
0065183e cdq 
0065183f sub eax, edx
00651841 mov edx, 0xb4427c
00651846 sar eax, 1
00651848 cmp eax, ecx
0065184a cmovg ecx, eax
0065184d jmp 0x6518ab
0065184f cmp ecx, 0x16
00651852 je 0x651874
00651854 cmp ecx, 0x1a
00651857 je 0x651874
00651859 cmp ecx, 0x1b
0065185c je 0x651874
0065185e cmp ecx, 0x1c
00651861 je 0x651874
00651863 cmp ecx, 0x1d
00651866 je 0x651874
00651868 cmp ecx, 0x30
0065186b je 0x651874
0065186d mov edx, 0xb4670c
00651872 jmp 0x6518a9
00651874 mov eax, esi
00651876 mov ecx, 1
0065187b cdq 
0065187c sub eax, edx
0065187e mov edx, 0xb46c4c
00651883 sar eax, 1
00651885 cmp eax, ecx
00651887 cmovg ecx, eax
0065188a jmp 0x6518ab
0065188c mov eax, esi
0065188e mov ecx, 1
00651893 cdq 
00651894 sub eax, edx
00651896 mov edx, 0xb46c58
0065189b sar eax, 1
0065189d cmp eax, ecx
0065189f cmovg ecx, eax
006518a2 jmp 0x6518ab
006518a4 mov edx, 0xb46bc8
006518a9 mov ecx, esi
006518ab push ecx
006518ac push edx
006518ad lea eax, [esp + 0x3c]
006518b1 push 0x20
006518b3 push eax
006518b4 call 0x418980
006518b9 add esp, 0x10
006518bc lea eax, [esp + 0x34]
006518c0 lea ecx, [edi + 0x3c]
006518c3 push 0
006518c5 push eax
006518c6 call 0x4054f0
006518cb mov dword ptr [edi + 0x3ac], ebx
006518d1 cmp esi, 0xd
006518d4 jge 0x65195a
006518da mov ecx, dword ptr [0xbc4bc0]
006518e0 mov eax, dword ptr [0xbc4bc4]
006518e5 or ecx, dword ptr [0xbc4ce0]
006518eb or eax, dword ptr [0xbc4ce4]
006518f1 mov edx, dword ptr [0xbc4bc8]
006518f7 mov ebx, dword ptr [0xbc4bcc]
006518fd and ecx, dword ptr [edi + 0x378]
00651903 and eax, dword ptr [edi + 0x37c]
00651909 or edx, dword ptr [0xbc4ce8]
0065190f or ebx, dword ptr [0xbc4cec]
00651915 or ecx, eax
00651917 jne 0x65193e
00651919 mov eax, dword ptr [edi + 0x384]
0065191f and edx, dword ptr [edi + 0x380]
00651925 and eax, ebx
00651927 or edx, eax
00651929 jne 0x65193e
0065192b movss xmm0, dword ptr [0xb6a614]
00651933 movss dword ptr [esp + 0x10], xmm0
00651939 jmp 0x651cd5
0065193e movss xmm0, dword ptr [edi + 0x370]
00651946 divss xmm0, dword ptr [esi*4 + 0xb46a2c]
0065194f movss dword ptr [esp + 0x10], xmm0
00651955 jmp 0x651cd5
0065195a movss xmm0, dword ptr [edi + 0x370]
00651962 divss xmm0, dword ptr [0xb6a84c]
0065196a movss dword ptr [esp + 0x10], xmm0
00651970 jmp 0x651cd5
00651975 cmp dword ptr [edi + 0x3ac], ebx
0065197b je 0x651992
0065197d push 0
0065197f push 0xb42404
00651984 lea ecx, [edi + 0x3c]
00651987 call 0x4054f0
0065198c mov dword ptr [edi + 0x3ac], ebx
00651992 cmp dword ptr [edi + 0x388], 0
00651999 movss xmm1, dword ptr [edi + 0x370]
006519a1 divss xmm1, dword ptr [0xb6a84c]
006519a9 movss xmm0, dword ptr [edi + 0x364]
006519b1 addss xmm0, dword ptr [edi + 0x2bc]
006519b9 movss dword ptr [esp + 0x10], xmm1
006519bf movss xmm1, dword ptr [edi + 0x2b8]
006519c7 addss xmm1, dword ptr [0xb6a18c]
006519cf jle 0x6519e1
006519d1 movss xmm1, dword ptr [edi + 0x38c]
006519d9 movss xmm0, dword ptr [edi + 0x390]
006519e1 call 0x447a80
006519e6 mulss xmm0, dword ptr [0xb6aa84]
006519ee movss dword ptr [edi + 0xe0], xmm0
006519f6 movss xmm0, dword ptr [esp + 0x10]
006519fc jmp 0x651cd5
00651a01 movss xmm1, dword ptr [edi + 0x370]
00651a09 xor eax, eax
00651a0b movss dword ptr [esp + 0x10], xmm1
00651a11 movss xmm0, dword ptr [eax*4 + 0xb46af0]
00651a1a comiss xmm0, xmm1
00651a1d jae 0x651a25
00651a1f inc eax
00651a20 cmp eax, 5
00651a23 jl 0x651a11
00651a25 inc eax
00651a26 push eax
00651a27 lea eax, [esp + 0x38]
00651a2b push 0xb4427c
00651a30 push eax
00651a31 call 0x4e6170
00651a36 add esp, 0xc
00651a39 lea ecx, [edi + 0x3c]
00651a3c cmp dword ptr [edi + 0x70], 0
00651a40 je 0x651a59
00651a42 cmp byte ptr [edi + 0x80], 0
00651a49 je 0x651a59
00651a4b push 0
00651a4d lea eax, [esp + 0x38]
00651a51 push eax
00651a52 call 0x405740
00651a57 jmp 0x651a96
00651a59 push 0
00651a5b lea eax, [esp + 0x38]
00651a5f push eax
00651a60 call 0x4054f0
00651a65 mov eax, dword ptr [edi + 0x70]
00651a68 test eax, eax
00651a6a je 0x651a81
00651a6c mov esi, dword ptr [eax + 0x30]
00651a6f test esi, esi
00651a71 je 0x651a81
00651a73 call 0x6c3d90
00651a78 xor edx, edx
00651a7a div esi
00651a7c mov eax, dword ptr [edi + 0x70]
00651a7f jmp 0x651a83
00651a81 xor edx, edx
00651a83 test eax, eax
00651a85 je 0x651a96
00651a87 movd xmm1, edx
00651a8b lea ecx, [edi + 0x6c]
00651a8e cvtdq2ps xmm1, xmm1
00651a91 call 0x403c00
00651a96 cmp dword ptr [edi + 0x2c], 8
00651a9a jne 0x6519f6
00651aa0 movss xmm0, dword ptr [edi + 0x370]
00651aa8 addss xmm0, xmm0
00651aac movss dword ptr [edi + 0x370], xmm0
00651ab4 movss xmm0, dword ptr [esp + 0x10]
00651aba jmp 0x651cd5
00651abf cmp byte ptr [edi + 0x16b], 0
00651ac6 jne 0x651ccd
00651acc cmp dword ptr [edi + 0x3ac], ebx
00651ad2 je 0x651ae9
00651ad4 push 0
00651ad6 push 0xb42e30
00651adb lea ecx, [edi + 0x3c]
00651ade call 0x4054f0
00651ae3 mov dword ptr [edi + 0x3ac], ebx
00651ae9 xorps xmm0, xmm0
00651aec comiss xmm0, dword ptr [edi + 0x2b8]
00651af3 seta al
00651af6 mov byte ptr [edi + 0x13c], al
00651afc jmp 0x651ccd
00651b01 push 0
00651b03 push 0xb43ac4
00651b08 lea ecx, [edi + 0x3c]
00651b0b call 0x4054f0
00651b10 cmp byte ptr [0xbc7a4f], 0
00651b17 mov ebx, 6
00651b1c mov eax, 1
00651b21 cmovne ebx, eax
00651b24 cmp dword ptr [edi + 0xbc], 0
00651b2b jg 0x651b4b
00651b2d cmp dword ptr [edi + 0x50], 0x10
00651b31 lea eax, [edi + 0x3c]
00651b34 jb 0x651b39
00651b36 mov eax, dword ptr [edi + 0x3c]
00651b39 push 0
00651b3b push eax
00651b3c push 0xa0830c
00651b41 push 3
00651b43 call 0x95e330
00651b48 add esp, 0x10
00651b4b mov eax, dword ptr [edi + 0xb8]
00651b51 mov dword ptr [eax + 0x78], ebx
00651b54 mov dword ptr [eax + 0x7c], 1
00651b5b mov dword ptr [eax + 0x80], 1
00651b65 mov dword ptr [eax + 0x84], 1
00651b6f jmp 0x651ccd
00651b74 push 0
00651b76 push 0xb3fd8c
00651b7b lea ecx, [edi + 0x3c]
00651b7e call 0x4054f0
00651b83 movss xmm0, dword ptr [edi + 0x370]
00651b8b movss dword ptr [esp + 0x10], xmm0
00651b91 jmp 0x651cd5
00651b96 movss xmm1, dword ptr [edi + 0x370]
00651b9e xor ebx, ebx
00651ba0 addss xmm1, dword ptr [0xb6a38c]
00651ba8 movss dword ptr [edi + 0x370], xmm1
00651bb0 movss xmm0, dword ptr [ebx*4 + 0xb46a70]
00651bb9 comiss xmm0, xmm1
00651bbc jae 0x651bc4
00651bbe inc ebx
00651bbf cmp ebx, 4
00651bc2 jl 0x651bb0
00651bc4 mov eax, dword ptr [esp + 0x14]
00651bc8 add eax, ebx
00651bca cmp dword ptr [edi + 0x3ac], eax
00651bd0 je 0x651c82
00651bd6 mov dword ptr [edi + 0x3ac], eax
00651bdc lea eax, [ebx + 1]
00651bdf push eax
00651be0 lea eax, [esp + 0x38]
00651be4 push 0xb4427c
00651be9 push eax
00651bea call 0x4e6170
00651bef mov eax, 0x51eb851f
00651bf4 lea ecx, [edi + 0x3c]
00651bf7 imul dword ptr [edi + 0x3ac]
00651bfd mov eax, 0x51eb851f
00651c02 add esp, 0xc
00651c05 sar edx, 5
00651c08 mov esi, edx
00651c0a shr esi, 0x1f
00651c0d add esi, edx
00651c0f imul dword ptr [esp + 0x14]
00651c13 sar edx, 5
00651c16 mov eax, edx
00651c18 shr eax, 0x1f
00651c1b add eax, edx
00651c1d cmp esi, eax
00651c1f jne 0x651c3d
00651c21 call 0x4058f0
00651c26 mov esi, eax
00651c28 lea ecx, [edi + 0x3c]
00651c2b push 0
00651c2d lea eax, [esp + 0x38]
00651c31 push eax
00651c32 call 0x4054f0
00651c37 test esi, esi
00651c39 js 0x651c49
00651c3b jmp 0x651c5e
00651c3d push 0
00651c3f lea eax, [esp + 0x38]
00651c43 push eax
00651c44 call 0x4054f0
00651c49 mov eax, dword ptr [edi + 0x70]
00651c4c test eax, eax
00651c4e je 0x651c55
00651c50 mov ecx, dword ptr [eax + 0x30]
00651c53 jmp 0x651c57
00651c55 xor ecx, ecx
00651c57 call 0x659230
00651c5c mov esi, eax
00651c5e mov ecx, dword ptr [edi + 0x70]
00651c61 test ecx, ecx
00651c63 je 0x651c82
00651c65 movd xmm1, esi
00651c69 lea ecx, [edi + 0x6c]
00651c6c cvtdq2ps xmm1, xmm1
00651c6f call 0x403c00
00651c74 mov ecx, dword ptr [edi + 0x70]
00651c77 test ecx, ecx
00651c79 je 0x651c82
00651c7b mov byte ptr [edi + 0x80], 0
00651c82 movss xmm0, dword ptr [edi + 0x370]
00651c8a cmp ebx, 5
00651c8d jae 0x651ca0
00651c8f divss xmm0, dword ptr [ebx*4 + 0xb46a70]
00651c98 movss dword ptr [esp + 0x10], xmm0
00651c9e jmp 0x651cd5
00651ca0 divss xmm0, dword ptr [0xb6a804]
00651ca8 movss dword ptr [esp + 0x10], xmm0
00651cae jmp 0x651cd5
00651cb0 cmp dword ptr [edi + 0x3ac], ebx
00651cb6 je 0x651ccd
00651cb8 push 0
00651cba push 0xb3fd8c
00651cbf lea ecx, [edi + 0x3c]
00651cc2 call 0x4054f0
00651cc7 mov dword ptr [edi + 0x3ac], ebx
00651ccd movss xmm0, dword ptr [0xb6a614]
00651cd5 movss xmm3, dword ptr [edi + 0x2cc]
00651cdd movss xmm4, dword ptr [edi + 0x2d0]
00651ce5 mov eax, dword ptr [edi + 0x2c]
00651ce8 movss dword ptr [esp + 0x18], xmm3
00651cee movss dword ptr [esp + 0x14], xmm4
00651cf4 cmp eax, 0x33
00651cf7 jb 0x651db3
00651cfd xor esi, esi
00651cff cmp dword ptr [edi + 0xbc], esi
00651d05 jbe 0x651ebe
00651d0b xor ecx, ecx
00651d0d mov dword ptr [esp + 0x10], ecx
00651d11 movss xmm0, dword ptr [edi + 0x370]
00651d19 movaps xmm1, xmm0
00651d1c mulss xmm0, dword ptr [0xbc7a2c]
00651d24 mulss xmm1, dword ptr [0xbc7a28]
00651d2c mulss xmm0, xmm4
00651d30 mulss xmm1, xmm3
00651d34 movss dword ptr [esp + 0x20], xmm0
00651d3a movss dword ptr [esp + 0x1c], xmm1
00651d40 test esi, esi
00651d42 js 0x651d4c
00651d44 cmp esi, dword ptr [edi + 0xbc]
00651d4a jl 0x651d85
00651d4c cmp dword ptr [edi + 0x50], 0x10
00651d50 lea eax, [edi + 0x3c]
00651d53 jb 0x651d58
00651d55 mov eax, dword ptr [edi + 0x3c]
00651d58 push esi
00651d59 push eax
00651d5a push 0xa0830c
00651d5f push 3
00651d61 call 0x95e330
00651d66 movss xmm0, dword ptr [esp + 0x30]
00651d6c add esp, 0x10
00651d6f movss xmm1, dword ptr [esp + 0x1c]
00651d75 movss xmm3, dword ptr [esp + 0x18]
00651d7b movss xmm4, dword ptr [esp + 0x14]
00651d81 mov ecx, dword ptr [esp + 0x10]
00651d85 mov eax, dword ptr [edi + 0xb8]
00651d8b inc esi
00651d8c movss dword ptr [eax + ecx + 0x34], xmm1
00651d92 movss dword ptr [eax + ecx + 0x38], xmm0
00651d98 add ecx, 0x9c
00651d9e mov dword ptr [esp + 0x10], ecx
00651da2 cmp esi, dword ptr [edi + 0xbc]
00651da8 jb 0x651d11
00651dae jmp 0x651ebe
00651db3 cmp eax, 0xd
00651db6 je 0x651dbd
00651db8 cmp eax, 0x17
00651dbb jne 0x651e04
00651dbd mov ecx, dword ptr [0xbfd65c]
00651dc3 lea eax, [esp + 0x1c]
00651dc7 add ecx, 0x1bb58
00651dcd mov dword ptr [esp + 0x1c], 0x4f
00651dd5 push eax
00651dd6 lea eax, [esp + 0x2c]
00651dda push eax
00651ddb mov esi, dword ptr [ecx]
00651ddd call 0x4206b0
00651de2 mov eax, dword ptr [esp + 0x30]
00651de6 cmp byte ptr [eax + 0xd], 0
00651dea jne 0x651e04
00651dec cmp dword ptr [eax + 0x10], 0x4f
00651df0 jg 0x651e04
00651df2 cmp eax, esi
00651df4 je 0x651e04
00651df6 divss xmm3, dword ptr [0xb6a864]
00651dfe movss dword ptr [esp + 0x18], xmm3
00651e04 xor esi, esi
00651e06 cmp dword ptr [edi + 0xbc], esi
00651e0c jbe 0x651ebe
00651e12 xor ecx, ecx
00651e14 mov dword ptr [esp + 0x20], ecx
00651e18 nop dword ptr [eax + eax]
00651e20 movaps xmm1, xmm0
00651e23 movaps xmm2, xmm0
00651e26 mulss xmm1, dword ptr [0xbc7a28]
00651e2e mulss xmm2, dword ptr [0xbc7a2c]
00651e36 mulss xmm1, xmm3
00651e3a mulss xmm2, xmm4
00651e3e movss dword ptr [esp + 0x1c], xmm1
00651e44 movss dword ptr [esp + 0x24], xmm2
00651e4a test esi, esi
00651e4c js 0x651e56
00651e4e cmp esi, dword ptr [edi + 0xbc]
00651e54 jl 0x651e95
00651e56 cmp dword ptr [edi + 0x50], 0x10
00651e5a lea eax, [edi + 0x3c]
00651e5d jb 0x651e62
00651e5f mov eax, dword ptr [edi + 0x3c]
00651e62 push esi
00651e63 push eax
00651e64 push 0xa0830c
00651e69 push 3
00651e6b call 0x95e330
00651e70 movss xmm0, dword ptr [esp + 0x20]
00651e76 add esp, 0x10
00651e79 movss xmm1, dword ptr [esp + 0x1c]
00651e7f movss xmm2, dword ptr [esp + 0x24]
00651e85 movss xmm3, dword ptr [esp + 0x18]
00651e8b movss xmm4, dword ptr [esp + 0x14]
00651e91 mov ecx, dword ptr [esp + 0x20]
00651e95 mov eax, dword ptr [edi + 0xb8]
00651e9b inc esi
00651e9c movss dword ptr [eax + ecx + 0x34], xmm1
00651ea2 movss dword ptr [eax + ecx + 0x38], xmm2
00651ea8 add ecx, 0x9c
00651eae mov dword ptr [esp + 0x20], ecx
00651eb2 cmp esi, dword ptr [edi + 0xbc]
00651eb8 jb 0x651e20
00651ebe mov ecx, dword ptr [edi + 0x378]
00651ec4 mov eax, dword ptr [edi + 0x37c]
00651eca mov edx, dword ptr [edi + 0x380]
00651ed0 mov esi, dword ptr [edi + 0x384]
00651ed6 and ecx, dword ptr [0xbc4980]
00651edc and eax, dword ptr [0xbc4984]
00651ee2 and edx, dword ptr [0xbc4988]
00651ee8 and esi, dword ptr [0xbc498c]
00651eee or ecx, eax
00651ef0 movss xmm0, dword ptr [0xb6a468]
00651ef8 jne 0x651efe
00651efa or edx, esi
00651efc je 0x651f4c
00651efe movss xmm1, dword ptr [edi + 0x370]
00651f06 mulss xmm1, xmm0
00651f0a movaps xmm0, xmm1
00651f0d mulss xmm1, xmm4
00651f11 mulss xmm0, xmm3
00651f15 movss dword ptr [edi + 0x49c], xmm1
00651f1d movss dword ptr [edi + 0x498], xmm0
00651f25 cmp byte ptr [edi + 0x505], 0
00651f2c je 0x651f44
00651f2e lea ecx, [edi + 0x42c]
00651f34 call 0x403d60
00651f39 lea ecx, [edi + 0x44c]
00651f3f call 0x403d60
00651f44 movss xmm0, dword ptr [0xb6a468]
00651f4c cmp byte ptr [edi + 0x619], 0
00651f53 movss xmm2, dword ptr [esp + 0x18]
00651f59 movss xmm3, dword ptr [esp + 0x14]
00651f5f je 0x651faa
00651f61 movss xmm1, dword ptr [edi + 0x370]
00651f69 lea ecx, [edi + 0x540]
00651f6f mulss xmm1, xmm0
00651f73 movaps xmm0, xmm1
00651f76 mulss xmm1, xmm3
00651f7a mulss xmm0, xmm2
00651f7e movss dword ptr [edi + 0x5b0], xmm1
00651f86 movss dword ptr [edi + 0x5ac], xmm0
00651f8e call 0x403d60
00651f93 lea ecx, [edi + 0x560]
00651f99 call 0x403d60
00651f9e movss xmm2, dword ptr [esp + 0x18]
00651fa4 movss xmm3, dword ptr [esp + 0x14]
00651faa movss xmm0, dword ptr [edi + 0x3b4]
00651fb2 ucomiss xmm0, dword ptr [0xb6a18c]
00651fb9 lahf 
00651fba test ah, 0x44
00651fbd jnp 0x652009
00651fbf movss xmm1, dword ptr [edi + 0x370]
00651fc7 mulss xmm1, dword ptr [0xb6a468]
00651fcf movaps xmm0, xmm1
00651fd2 mulss xmm1, xmm3
00651fd6 mulss xmm0, xmm2
00651fda movss dword ptr [edi + 0x6c4], xmm1
00651fe2 movss dword ptr [edi + 0x6c0], xmm0
00651fea cmp byte ptr [edi + 0x72d], 0
00651ff1 je 0x652009
00651ff3 lea ecx, [edi + 0x654]
00651ff9 call 0x403d60
00651ffe lea ecx, [edi + 0x674]
00652004 call 0x403d60
00652009 mov eax, dword ptr [edi + 0x288]
0065200f push dword ptr [eax + 0x48]
00652012 movss xmm0, dword ptr [eax + 0x38]
00652017 push dword ptr [edi + 0x2d0]
0065201d mulss xmm0, dword ptr [edi + 0x370]
00652025 push dword ptr [edi + 0x2cc]
0065202b push ecx
0065202c mov ecx, edi
0065202e movss dword ptr [esp], xmm0
00652033 call 0x6843a0
00652038 mov eax, dword ptr [edi + 0x288]
0065203e movss xmm1, dword ptr [esp + 0x18]
00652044 addss xmm1, dword ptr [esp + 0x14]
0065204a mov ecx, dword ptr [esp + 0x54]
0065204e movss xmm0, dword ptr [eax + 0x24]
00652053 mulss xmm0, dword ptr [edi + 0x370]
0065205b mulss xmm0, xmm1
0065205f mulss xmm0, dword ptr [0xb6a480]
00652067 movss dword ptr [edi + 0x150], xmm0
0065206f pop edi
00652070 pop esi
00652071 pop ebx
00652072 xor ecx, esp
00652074 call 0x9eacd7
00652079 mov esp, ebp
0065207b pop ebp
0065207c ret 
