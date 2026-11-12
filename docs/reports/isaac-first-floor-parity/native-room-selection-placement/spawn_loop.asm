007b1fd1 xor ecx, ecx
007b1fd3 mov eax, dword ptr [ebp - 0x504]
007b1fd9 mov dword ptr [ebp - 0x4f0], 0
007b1fe3 cmp cx, word ptr [eax + 0x44]
007b1fe7 jae 0x7b2120
007b1fed mov esi, dword ptr [ebp - 0x508]
007b1ff3 xor edx, edx
007b1ff5 mov dword ptr [ebp - 0x50c], edx
007b1ffb nop dword ptr [eax + eax]
007b2000 test esi, esi
007b2002 jne 0x7b201a
007b2004 push 0xb4d6c4
007b2009 push 3
007b200b call 0x95e330
007b2010 add esp, 8
007b2013 int3
007b2014 mov edx, dword ptr [ebp - 0x50c]
007b201a mov ecx, dword ptr [ebp - 0x5ac]
007b2020 mov eax, esi
007b2022 shr eax, cl
007b2024 mov ecx, dword ptr [ebp - 0x5a8]
007b202a xor esi, eax
007b202c mov eax, esi
007b202e shl eax, cl
007b2030 mov ecx, dword ptr [ebp - 0x5a4]
007b2036 xor esi, eax
007b2038 mov eax, esi
007b203a shr eax, cl
007b203c xor esi, eax
007b203e mov eax, esi
007b2040 shr eax, 0x1f
007b2043 movd xmm0, esi
007b2047 cvtdq2pd xmm0, xmm0
007b204b addsd xmm0, qword ptr [eax*8 + 0xb6c940]
007b2054 mov eax, dword ptr [ebp - 0x504]
007b205a mov eax, dword ptr [eax + 0x40]
007b205d add edx, eax
007b205f cvtpd2ps xmm0, xmm0
007b2063 movsx ecx, word ptr [edx + 2]
007b2067 movsx eax, word ptr [edx]
007b206a inc ecx
007b206b inc eax
007b206c imul ecx, dword ptr [edi + 0xc]
007b2070 mulss xmm0, dword ptr [0xb6a198]
007b2078 add eax, ecx
007b207a cmp byte ptr [edx + 8], 0
007b207e mov dword ptr [ebp - 0x4f4], eax
007b2084 jbe 0x7b20ec
007b2086 push ecx
007b2087 mov ecx, edx
007b2089 movss dword ptr [esp], xmm0
007b208e call 0x7e7c20
007b2093 mov ecx, dword ptr [edi + 4]
007b2096 sub ecx, -0x80
007b2099 mov dword ptr [ebp - 0x508], eax
007b209f mov eax, dword ptr [ecx]
007b20a1 mov dword ptr [ebp - 0x4f8], eax
007b20a7 lea eax, [ebp - 0x4f4]
007b20ad push eax
007b20ae lea eax, [ebp - 0x734]
007b20b4 push eax
007b20b5 call 0x4206b0
007b20ba mov eax, dword ptr [ebp - 0x72c]
007b20c0 mov ecx, dword ptr [ebp - 0x4f4]
007b20c6 cmp byte ptr [eax + 0xd], 0
007b20ca jne 0x7b20d9
007b20cc cmp ecx, dword ptr [eax + 0x10]
007b20cf jl 0x7b20d9
007b20d1 cmp eax, dword ptr [ebp - 0x4f8]
007b20d7 jne 0x7b20ec
007b20d9 push 0
007b20db push 0
007b20dd push esi
007b20de push dword ptr [ebp - 0x508]
007b20e4 push ecx
007b20e5 mov ecx, edi
007b20e7 call 0x7abe30
007b20ec mov eax, dword ptr [ebp - 0x504]
007b20f2 mov ecx, dword ptr [ebp - 0x4f0]
007b20f8 mov edx, dword ptr [ebp - 0x50c]
007b20fe inc ecx
007b20ff add edx, 0x10
007b2102 mov dword ptr [ebp - 0x4f0], ecx
007b2108 movzx eax, word ptr [eax + 0x44]
007b210c mov dword ptr [ebp - 0x50c], edx
007b2112 cmp ecx, eax
007b2114 jb 0x7b2000
007b211a mov eax, dword ptr [ebp - 0x504]
