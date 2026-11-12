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
