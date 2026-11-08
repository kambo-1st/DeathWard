006d1ec7 movss xmm1, dword ptr [ebx + 0xc]
006d1ecc lea edx, [ebx + 0x1c]
006d1ecf push 0xbc48c0
006d1ed4 lea ecx, [ebp - 0xb8]
006d1eda movss dword ptr [ebp - 0x1c], xmm1
006d1edf call 0x412050
006d1ee4 add esp, 4
006d1ee7 mov ecx, dword ptr [eax]
006d1ee9 or ecx, dword ptr [eax + 4]
006d1eec jne 0x6d1ef6
006d1eee mov ecx, dword ptr [eax + 8]
006d1ef1 or ecx, dword ptr [eax + 0xc]
006d1ef4 je 0x6d1f71
006d1ef6 mov eax, dword ptr [edi + 8]
006d1ef9 xor esi, esi
006d1efb mov ecx, dword ptr [edi + 0xc]
006d1efe sub ecx, eax
006d1f00 mov dword ptr [ebp - 0x24], eax
006d1f03 mov eax, 0x92492493
006d1f08 mov dword ptr [ebp - 0x1c], esi
006d1f0b imul ecx
006d1f0d add edx, ecx
006d1f0f sar edx, 5
006d1f12 mov eax, edx
006d1f14 shr eax, 0x1f
006d1f17 add eax, edx
006d1f19 mov dword ptr [ebp - 0x2c], eax
006d1f1c je 0x6d1f44
006d1f1e xor ecx, ecx
006d1f20 mov edx, dword ptr [ebp - 0x24]
006d1f23 lea ecx, [ecx + 0x38]
006d1f26 mov edi, dword ptr [ebx + 0x18]
006d1f29 mov eax, esi
006d1f2b cmp dword ptr [edx + ecx - 4], edi
006d1f2f mov edi, dword ptr [ebp - 0x1c]
006d1f32 lea esi, [eax + 1]
006d1f35 cmovne esi, eax
006d1f38 inc edi
006d1f39 mov dword ptr [ebp - 0x1c], edi
006d1f3c cmp edi, dword ptr [ebp - 0x2c]
006d1f3f jb 0x6d1f20
006d1f41 mov edi, dword ptr [ebp - 0x28]
006d1f44 mov ecx, esi
006d1f46 mov eax, 1
006d1f4b shl eax, cl
006d1f4d mov esi, dword ptr [ebx + 0x18]
006d1f50 movd xmm0, eax
006d1f54 cvtdq2pd xmm0, xmm0
006d1f58 shr eax, 0x1f
006d1f5b addsd xmm0, qword ptr [eax*8 + 0xb6c940]
006d1f64 cvtpd2ps xmm0, xmm0
006d1f68 divss xmm1, xmm0
006d1f6c movss dword ptr [ebp - 0x1c], xmm1
006d1f71 lea eax, [ebp - 0xc8]
006d1f77 mov ecx, 0xbc4ca0
006d1f7c push eax
006d1f7d call 0x57f3a0
006d1f82 push eax
006d1f83 lea edx, [ebx + 0x1c]
006d1f86 lea ecx, [ebp - 0xd8]
006d1f8c call 0x412050
006d1f91 add esp, 4
006d1f94 lea edx, [ebx + 0x2c]
006d1f97 movups xmm0, xmmword ptr [eax]
006d1f9a push esi
006d1f9b sub esp, 0x14
006d1f9e mov ecx, esp
006d1fa0 push ecx
006d1fa1 movups xmmword ptr [ecx], xmm0
006d1fa4 call 0x656c90
006d1fa9 add esp, 0x1c
006d1fac lea ecx, [ebp - 0x120]
006d1fb2 push esi
006d1fb3 call 0x4229a0
006d1fb8 mov eax, dword ptr [edi]
006d1fba lea ecx, [ebp - 0x120]
006d1fc0 movss xmm0, dword ptr [ebp - 0x1c]
006d1fc5 push 0x1e
006d1fc7 push ecx
006d1fc8 push dword ptr [ebx + 0x30]
006d1fcb push dword ptr [ebx + 0x2c]
006d1fce push ecx
006d1fcf mov ecx, edi
006d1fd1 movss dword ptr [esp], xmm0
006d1fd6 call dword ptr [eax + 0x20]
006d1fd9 mov eax, dword ptr [ebx + 0x1c]
006d1fdc or eax, dword ptr [ebx + 0x20]
006d1fdf jne 0x6d1fed
006d1fe1 mov eax, dword ptr [ebx + 0x24]
006d1fe4 or eax, dword ptr [ebx + 0x28]
006d1fe7 je 0x6d20c4
006d1fed test esi, esi
006d1fef je 0x6d20c4
006d1ff5 mov eax, dword ptr [esi + 0x34]
006d1ff8 cmp eax, 0xa
006d1ffb jl 0x6d2008
006d1ffd cmp eax, 0x3e8
006d2002 jl 0x6d20c4
006d2008 push 0
006d200a mov ecx, edi
006d200c call 0x684630
006d2011 test al, al
006d2013 je 0x6d20c4
006d2019 lea eax, [ebp - 0xe8]
006d201f mov ecx, 0xbc4ca0
006d2024 push eax
006d2025 call 0x57f3a0
006d202a push eax
006d202b lea edx, [ebx + 0x1c]
006d202e lea ecx, [ebp - 0xf8]
006d2034 call 0x412050
006d2039 mov dword ptr [esp], 0x40600000
006d2040 mov ecx, edi
006d2042 push esi
006d2043 sub esp, 0x10
006d2046 movups xmm0, xmmword ptr [eax]
006d2049 mov edx, esp
006d204b movups xmmword ptr [edx], xmm0
006d204e mov edx, dword ptr [ebx + 8]
006d2051 call 0x654de0
006d2056 add esp, 0x18
006d2059 jmp 0x6d20c4
006d205b movss xmm0, dword ptr [ebx + 0xc]
006d2060 comiss xmm0, xmm1
006d2063 jbe 0x6d20c4
006d2065 push esi
006d2066 lea ecx, [ebp - 0x98]
006d206c call 0x4229a0
006d2071 movzx eax, byte ptr [ebp - 0x11]
006d2075 movss xmm1, dword ptr [0xb6a614]
006d207d add eax, eax
006d207f or dword ptr [ebp - 0x78], eax
006d2082 comiss xmm0, dword ptr [0xb6aad8]
006d2089 jb 0x6d2095
006d208b movss xmm0, dword ptr [0xb6a7b0]
006d2093 jmp 0x6d2098
006d2095 movaps xmm0, xmm1
006d2098 mov ecx, dword ptr [ebx + 0x2c]
006d209b mov eax, ecx
006d209d and eax, 0x10000000
006d20a2 or eax, 0
006d20a5 je 0x6d20aa
006d20a7 movaps xmm0, xmm1
006d20aa mov eax, dword ptr [edi]
006d20ac lea edx, [ebp - 0x98]
006d20b2 push 0x1e
006d20b4 push edx
006d20b5 push dword ptr [ebx + 0x30]
006d20b8 push ecx
006d20b9 push ecx
006d20ba mov ecx, edi
006d20bc movss dword ptr [esp], xmm0
006d20c1 call dword ptr [eax + 0x20]
006d20c4 mov edi, dword ptr [ebp - 0x30]
006d20c7 inc edi
006d20c8 mov dword ptr [ebp - 0x30], edi
006d20cb cmp edi, dword ptr [ebp - 0x54]
006d20ce jb 0x6d1833
