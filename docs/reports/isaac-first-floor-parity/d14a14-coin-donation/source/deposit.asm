0063d880 lea ecx, [edi + 0x3c]
0063d883 push 0xb468f8
0063d888 call 0x419b50
0063d88d mov ecx, eax
0063d88f call 0x405e90
0063d894 test al, al
0063d896 je 0x63e3fe
0063d89c mov ecx, dword ptr [0xbfd680]
0063d8a2 mov dword ptr [edi + 0x360], 1
0063d8ac call 0x41c4a0
0063d8b1 push 0x14
0063d8b3 mov ecx, eax
0063d8b5 mov dword ptr [ebp - 0x90], eax
0063d8bb call 0x41e720
0063d8c0 xor edx, edx
0063d8c2 mov ecx, 0x3e8
0063d8c7 div ecx
0063d8c9 mov ecx, dword ptr [ebp - 0x90]
0063d8cf push 1
0063d8d1 push 0x14
0063d8d3 lea esi, [edx + 1]
0063d8d6 call 0x884e40
0063d8db push 0
0063d8dd push 0xb46840
0063d8e2 lea ecx, [edi + 0x3c]
0063d8e5 mov dword ptr [ebp - 0x80], esi
0063d8e8 call 0x405850
0063d8ed mov eax, 0x51eb851f
0063d8f2 mov ecx, 0xa
0063d8f7 imul esi
0063d8f9 sar edx, 5
0063d8fc mov eax, edx
0063d8fe shr eax, 0x1f
0063d901 add eax, edx
0063d903 cdq
0063d904 idiv ecx
0063d906 lea ecx, [edi + 0x3c]
0063d909 push edx
0063d90a push 1
0063d90c call 0x405950
0063d911 mov eax, 0x66666667
0063d916 mov ecx, 0xa
0063d91b imul esi
0063d91d sar edx, 2
0063d920 mov esi, edx
0063d922 shr esi, 0x1f
0063d925 add esi, edx
0063d927 mov eax, esi
0063d929 cdq
0063d92a idiv ecx
0063d92c lea ecx, [edi + 0x3c]
0063d92f push edx
0063d930 push 2
0063d932 call 0x405950
0063d937 mov eax, dword ptr [ebp - 0x80]
0063d93a lea ecx, [esi + esi*4]
0063d93d add ecx, ecx
0063d93f sub eax, ecx
0063d941 lea ecx, [edi + 0x3c]
0063d944 push eax
0063d945 push 3
0063d947 call 0x405950
0063d94c push 0x32
0063d94e mov ecx, ebx
0063d950 call 0x7a7d50
0063d955 mov esi, dword ptr [ebp - 0xa0]
0063d95b test eax, eax
0063d95d jne 0x63d968
0063d95f push 1
0063d961 mov ecx, esi
0063d963 call 0x776b60
0063d968 push 0
0063d96a push 0x55
0063d96c mov ecx, esi
0063d96e call 0x73b950
0063d973 test al, al
0063d975 je 0x63da6b
0063d97b push 3
0063d97d mov ecx, ebx
0063d97f call 0x7a7d50
0063d984 test eax, eax
0063d986 jne 0x63da6b
0063d98c mov ecx, ebx
0063d98e call 0x7a7db0
0063d993 movss xmm0, dword ptr [0xb6a434]
0063d99b fstp dword ptr [ebp - 0x14]
0063d99e movss xmm1, dword ptr [ebp - 0x14]
0063d9a3 comiss xmm0, xmm1
0063d9a6 jbe 0x63d9be
0063d9a8 push 0x55
0063d9aa mov ecx, esi
0063d9ac call 0x78d4c0
0063d9b1 push eax
0063d9b2 mov ecx, esi
0063d9b4 call 0x725740
0063d9b9 jmp 0x63da6b
0063d9be movss xmm0, dword ptr [0xb6a560]
0063d9c6 comiss xmm0, xmm1
0063d9c9 jbe 0x63d9e5
0063d9cb push 0
0063d9cd push 0x55
0063d9cf mov ecx, esi
0063d9d1 call 0x78d4c0
0063d9d6 add eax, eax
0063d9d8 mov ecx, esi
0063d9da push eax
0063d9db call 0x724f00
0063d9e0 jmp 0x63da6b
0063d9e5 movss xmm0, dword ptr [0xb6a5d8]
0063d9ed comiss xmm0, xmm1
0063d9f0 jbe 0x63da05
0063d9f2 push 0x55
0063d9f4 mov ecx, esi
0063d9f6 call 0x78d4c0
0063d9fb push eax
0063d9fc mov ecx, esi
0063d9fe call 0x776b60
0063da03 jmp 0x63da6b
0063da05 mov ecx, ebx
0063da07 call 0x7a7e20
0063da0c movss xmm2, dword ptr [0xb6aa3c]
0063da14 xorps xmm1, xmm1
0063da17 push eax
0063da18 push 0
0063da1a push edi
0063da1b push 0xc02fec
0063da20 push 0
0063da22 push 0
0063da24 push ecx
0063da25 lea ecx, [ebp - 0x38]
0063da28 mov dword ptr [esp], 0
0063da2f call 0x9624e0
0063da34 push eax
0063da35 lea eax, [ebp - 0x18]
0063da38 push eax
0063da39 lea ecx, [edi + 0x294]
0063da3f call 0x962a60
0063da44 mov ecx, dword ptr [0xbfd65c]
0063da4a push eax
0063da4b lea eax, [ebp - 0x7c]
0063da4e push eax
0063da4f call 0x4023f0
0063da54 mov ecx, eax
0063da56 call 0x7cf240
0063da5b mov ecx, dword ptr [0xbfd65c]
0063da61 push eax
0063da62 push 4
0063da64 push 6
0063da66 call 0x422e20
0063da6b mov ecx, dword ptr [0xbfd65c]
0063da71 push 1
0063da73 call 0x6d6c90
0063da78 mov ecx, dword ptr [0xbfd65c]
0063da7e push 1
0063da80 call 0x6d6c80
0063da85 mov esi, dword ptr [ebp - 0x80]
0063da88 cmp esi, 0xa
0063da8b jl 0x63da9d
0063da8d mov ecx, dword ptr [ebp - 0x90]
0063da93 push 0x86
0063da98 call 0x884c80
0063da9d cmp esi, 0x14
0063daa0 jl 0x63dab2
0063daa2 mov ecx, dword ptr [ebp - 0x90]
0063daa8 push 0x97
0063daad call 0x884c80
0063dab2 cmp esi, 0x32
0063dab5 jl 0x63dac7
0063dab7 mov ecx, dword ptr [ebp - 0x90]
0063dabd push 0x87
0063dac2 call 0x884c80
0063dac7 cmp esi, 0x64
0063daca jl 0x63dadc
0063dacc mov ecx, dword ptr [ebp - 0x90]
0063dad2 push 0x98
0063dad7 call 0x884c80
0063dadc cmp esi, 0x96
0063dae2 jl 0x63daf4
0063dae4 mov ecx, dword ptr [ebp - 0x90]
0063daea push 0x88
0063daef call 0x884c80
0063daf4 cmp esi, 0xc8
0063dafa jl 0x63db0c
0063dafc mov ecx, dword ptr [ebp - 0x90]
0063db02 push 0x99
0063db07 call 0x884c80
0063db0c cmp esi, 0x190
0063db12 jl 0x63db24
0063db14 mov ecx, dword ptr [ebp - 0x90]
0063db1a push 0x89
0063db1f call 0x884c80
0063db24 cmp esi, 0x258
0063db2a jl 0x63db3c
0063db2c mov ecx, dword ptr [ebp - 0x90]
0063db32 push 0x9a
0063db37 call 0x884c80
0063db3c cmp esi, 0x384
0063db42 jl 0x63db51
0063db44 mov ecx, dword ptr [ebp - 0x90]
0063db4a push 0x3b
0063db4c call 0x884c80
0063db51 cmp esi, 0x3e7
0063db57 jl 0x63db69
0063db59 mov ecx, dword ptr [ebp - 0x90]
0063db5f push 0x8a
0063db64 call 0x884c80
0063db69 cmp esi, 0x3e8
0063db6f jl 0x63dcd2
0063db75 call 0x6c3d90
0063db7a push eax
0063db7b push 0
0063db7d push 0
0063db7f push 0xc02fec
0063db84 lea ecx, [edi + 0x294]
0063db8a push ecx
0063db8b push 1
0063db8d mov dword ptr [ebp - 0x14], ecx
0063db90 mov ecx, dword ptr [0xbfd65c]
0063db96 push 0x3e8
0063db9b call 0x422e20
0063dba0 push 0
0063dba2 push 0xb408f8
0063dba7 lea ecx, [edi + 0x3c]
0063dbaa call 0x4054f0
0063dbaf mov dword ptr [edi + 0x360], 3
0063dbb9 mov edi, dword ptr [ebp - 0x14]
0063dbbc mov dword ptr [ebp - 0xc8], 0xf
0063dbc6 nop word ptr [eax + eax]
0063dbd0 movss xmm0, dword ptr [0xc02fec]
0063dbd8 xor esi, esi
0063dbda movss dword ptr [ebp - 0x7c], xmm0
0063dbdf movss xmm0, dword ptr [0xc02ff0]
0063dbe7 movss dword ptr [ebp - 0x78], xmm0
0063dbec nop dword ptr [eax]
0063dbf0 lea eax, [ebp - 0x14]
0063dbf3 mov dword ptr [ebp - 0x14], 0x40a00000
0063dbfa push eax
0063dbfb lea eax, [ebp - 0x38]
0063dbfe push eax
0063dbff lea eax, [ebp - 0x9c]
0063dc05 push eax
0063dc06 call 0x659290
0063dc0b add esp, 4
0063dc0e mov ecx, eax
0063dc10 call 0x962b50
0063dc15 push eax
0063dc16 lea ecx, [ebp - 0x7c]
0063dc19 call 0x962cd0
0063dc1e movss xmm0, dword ptr [ebp - 0x78]
0063dc23 lea eax, [ebp - 0x14]
0063dc26 mulss xmm0, dword ptr [0xb6a350]
0063dc2e lea ecx, [ebp - 0x7c]
0063dc31 push 0
0063dc33 push 0
0063dc35 push 0
0063dc37 addss xmm0, dword ptr [0xb6a864]
0063dc3f push 0
0063dc41 push 1
0063dc43 push eax
0063dc44 lea eax, [ebp - 0xac]
0063dc4a mov dword ptr [ebp - 0x14], 0x40e00000
0063dc51 push eax
0063dc52 movss dword ptr [ebp - 0x78], xmm0
0063dc57 call 0x962b50
0063dc5c push eax
0063dc5d lea eax, [ebp - 0xb4]
0063dc63 mov ecx, edi
0063dc65 push eax
0063dc66 call 0x962a60
0063dc6b mov ecx, dword ptr [0xbfd65c]
0063dc71 push eax
0063dc72 push edi
0063dc73 call 0x4023f0
0063dc78 mov ecx, eax
0063dc7a call 0x7af4b0
0063dc7f test al, al
0063dc81 jne 0x63dc8d
0063dc83 inc esi
0063dc84 cmp esi, 0xa
0063dc87 jl 0x63dbf0
0063dc8d mov ecx, ebx
0063dc8f call 0x7a7e20
0063dc94 mov ecx, dword ptr [0xbfd65c]
0063dc9a push eax
0063dc9b push 3
0063dc9d push 0
0063dc9f lea eax, [ebp - 0x7c]
0063dca2 push eax
0063dca3 push edi
0063dca4 push 0x14
0063dca6 push 5
0063dca8 call 0x422e20
0063dcad sub dword ptr [ebp - 0xc8], 1
0063dcb4 jne 0x63dbd0
0063dcba mov ecx, dword ptr [0xbfd65c]
0063dcc0 push 1
0063dcc2 push 0x11
0063dcc4 call 0x4c0540
0063dcc9 mov edi, dword ptr [ebp - 0xb8]
0063dccf mov esi, dword ptr [ebp - 0x80]
0063dcd2 cmp esi, 0x3e7
0063dcd8 jne 0x63dcea
0063dcda xor eax, eax
0063dcdc mov word ptr [edi + 0x376], ax
0063dce3 mov eax, 0x14
0063dce8 jmp 0x63dd20
0063dcea movzx ecx, word ptr [edi + 0x376]
0063dcf1 mov eax, 0xcccccccd
0063dcf6 mul ecx
0063dcf8 mov eax, 0xf
0063dcfd mov dword ptr [ebp - 0x14], 0
0063dd04 shr edx, 3
0063dd07 lea ecx, [ebp - 0x84]
0063dd0d sub eax, edx
0063dd0f lea edx, [ebp - 0x14]
0063dd12 mov dword ptr [ebp - 0x84], eax
0063dd18 call 0x417c80
0063dd1d movzx eax, word ptr [eax]
0063dd20 push ecx
0063dd21 mov word ptr [edi + 0x36a], ax
0063dd28 movss xmm2, dword ptr [0xb6a614]
0063dd30 mov ecx, dword ptr [0xbfd680]
0063dd36 mov dword ptr [esp], 0x3f800000
0063dd3d push 0
0063dd3f push 2
0063dd41 push 0x18
0063dd43 call 0x8b1480
0063dd48 mov ecx, dword ptr [0xbfd65c]
0063dd4e call 0x639090
0063dd53 cmp dword ptr [edi + 0x360], 3
0063dd5a mov esi, eax
0063dd5c je 0x63e3fe
0063dd62 push 0x7d0
0063dd67 mov ecx, ebx
0063dd69 call 0x7a7d50
0063dd6e lea ecx, [esi + esi*2]
0063dd71 cmp eax, ecx
0063dd73 jae 0x63e3fe
0063dd79 push 0
0063dd7b call 0x639170
0063dd80 push eax
0063dd81 lea ecx, [edi + 0x3c]
0063dd84 call 0x4054f0
0063dd89 push 1
0063dd8b push 0x12
0063dd8d mov ecx, dword ptr [0xbfd65c]
0063dd93 call 0x4c0540
0063dd98 mov dword ptr [edi + 0x360], 3
