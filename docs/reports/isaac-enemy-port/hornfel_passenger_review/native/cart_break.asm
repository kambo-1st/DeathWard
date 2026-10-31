; Installed-binary disassembly; field interpretations require the source review.
004bc040 push ebx
004bc041 mov ebx, esp
004bc043 sub esp, 8
004bc046 and esp, 0xfffffff0
004bc049 add esp, 4
004bc04c push ebp
004bc04d mov ebp, dword ptr [ebx + 4]
004bc050 mov dword ptr [esp + 4], ebp
004bc054 mov ebp, esp
004bc056 sub esp, 0x88
004bc05c mov eax, dword ptr [0xbaa3b4]
004bc061 xor eax, ebp
004bc063 mov dword ptr [ebp - 4], eax
004bc066 push esi
004bc067 push edi
004bc068 mov edi, ecx
004bc06a mov eax, dword ptr [edi]
004bc06c call dword ptr [eax + 0x28]
004bc06f mov esi, dword ptr [0xbfd680]
004bc075 lea ecx, [ebp - 0x34]
004bc078 mov dword ptr [ebp - 0x34], 0x1e1
004bc07f call 0x8b1340
004bc084 sub esp, 8
004bc087 xorps xmm0, xmm0
004bc08a movaps xmmword ptr [ebp - 0x50], xmm0
004bc08e mov dword ptr [esp + 4], 0
004bc096 mov dword ptr [esp], 0x3f800000
004bc09d push 0
004bc09f push 0xa
004bc0a1 push ecx
004bc0a2 mov dword ptr [esp], 0x3f800000
004bc0a9 lea ecx, [esi + 0x29de0]
004bc0af push dword ptr [ebp - 0x34]
004bc0b2 call 0x888de0
004bc0b7 movaps xmm0, xmmword ptr [0xb6c610]
004bc0be mov esi, dword ptr [0xbfd65c]
004bc0c4 movups xmmword ptr [ebp - 0x30], xmm0
004bc0c8 mov dword ptr [ebp - 0x10], 0
004bc0cf xorps xmm0, xmm0
004bc0d2 mov dword ptr [ebp - 0xc], 0
004bc0d9 movups xmmword ptr [ebp - 0x20], xmm0
004bc0dd mov dword ptr [ebp - 8], 0
004bc0e4 mov eax, dword ptr [esi + 0x18190]
004bc0ea cmp dword ptr [eax + 0x1e84], 0x2e
004bc0f1 jne 0x4bc12c
004bc0f3 movaps xmm0, xmmword ptr [ebp - 0x50]
004bc0f7 movaps xmm1, xmmword ptr [0xb6bbf0]
004bc0fe mov dword ptr [ebp - 0x54], 0
004bc105 mov eax, dword ptr [ebp - 0x54]
004bc108 unpcklps xmm0, xmm0
004bc10b mov dword ptr [ebp - 0x30], 0x3f666666
004bc112 mov dword ptr [ebp - 0x2c], 0x3f666666
004bc119 mov dword ptr [ebp - 0x28], 0x3f666666
004bc120 movups xmmword ptr [ebp - 0x20], xmm1
004bc124 mov dword ptr [ebp - 8], eax
004bc127 movq qword ptr [ebp - 0x10], xmm0
004bc12c call 0x6c3d90
004bc131 movd xmm0, eax
004bc135 cvtdq2pd xmm0, xmm0
004bc139 shr eax, 0x1f
004bc13c addsd xmm0, qword ptr [eax*8 + 0xb6c940]
004bc145 cvtpd2ps xmm0, xmm0
004bc149 mulss xmm0, dword ptr [0xb6a19c]
004bc151 call 0x6c3d90
004bc156 mov ecx, 3
004bc15b mulss xmm0, dword ptr [0xb6a8cc]
004bc163 xor edx, edx
004bc165 div ecx
004bc167 addss xmm0, dword ptr [0xb6a864]
004bc16f push 0
004bc171 push ecx
004bc172 mov dword ptr [esp], 0x47c35000
004bc179 lea eax, [ebp - 0x30]
004bc17c push eax
004bc17d push ecx
004bc17e movss dword ptr [esp], xmm0
004bc183 lea eax, [edx + 6]
004bc186 push eax
004bc187 push 0x1b
004bc189 lea eax, [edi + 0x294]
004bc18f mov ecx, esi
004bc191 push eax
004bc192 call 0x6d57a0
004bc197 mov ecx, dword ptr [edi + 0x318]
004bc19d lea esi, [edi + 0x318]
004bc1a3 test ecx, ecx
004bc1a5 je 0x4bc1b9
004bc1a7 lea eax, [ebp - 0x34]
004bc1aa mov dword ptr [ebp - 0x34], esi
004bc1ad push eax
004bc1ae add ecx, 0x324
004bc1b4 call 0x4bc3c0
004bc1b9 mov ecx, dword ptr [ebp - 4]
004bc1bc pop edi
004bc1bd mov dword ptr [esi], 0
004bc1c3 xor ecx, ebp
004bc1c5 pop esi
004bc1c6 call 0x9eacd7
004bc1cb mov esp, ebp
004bc1cd pop ebp
004bc1ce mov esp, ebx
004bc1d0 pop ebx
004bc1d1 ret
