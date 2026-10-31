0069b140 push ebp
0069b141 mov ebp, esp
0069b143 push -1
0069b145 push 0x9f48bd
0069b14a mov eax, dword ptr fs:[0]
0069b150 push eax
0069b151 sub esp, 0x340
0069b157 mov eax, dword ptr [0xbaa3b4]
0069b15c xor eax, ebp
0069b15e mov dword ptr [ebp - 0x10], eax
0069b161 push esi
0069b162 push edi
0069b163 push eax
0069b164 lea eax, [ebp - 0xc]
0069b167 mov dword ptr fs:[0], eax
0069b16d mov edi, ecx
0069b16f mov dword ptr [ebp - 0x2c0], edi
0069b175 xor ecx, ecx
0069b177 mov dword ptr [ebp - 0x290], ecx
0069b17d mov dword ptr [ebp - 0x274], ecx
0069b183 cmp byte ptr [edi + 0x16a], cl
0069b189 je 0x6a088c
0069b18f mov ecx, edi
0069b191 call 0x690ad0
0069b196 push 0
0069b198 mov ecx, edi
0069b19a movss dword ptr [edi + 0x2f4], xmm0
0069b1a2 call 0x6afeb0
0069b1a7 cmp dword ptr [edi + 0xe6c], -1
0069b1ae jne 0x69b205
0069b1b0 movss xmm0, dword ptr [0xc02fec]
0069b1b8 lea esi, [edi + 0xe78]
0069b1be movss dword ptr [edi + 0xe70], xmm0
0069b1c6 movss xmm0, dword ptr [0xc02ff0]
0069b1ce movss dword ptr [edi + 0xe74], xmm0
0069b1d6 mov ecx, dword ptr [esi]
0069b1d8 test ecx, ecx
0069b1da je 0x69b205
0069b1dc mov eax, dword ptr [ecx]
0069b1de call dword ptr [eax + 0x28]
0069b1e1 mov ecx, dword ptr [esi]
0069b1e3 test ecx, ecx
0069b1e5 je 0x69b1ff
0069b1e7 lea eax, [ebp - 0x270]
0069b1ed mov dword ptr [ebp - 0x270], esi
0069b1f3 push eax
0069b1f4 add ecx, 0x324
0069b1fa call 0x4bc3c0
0069b1ff mov dword ptr [esi], 0
0069b205 mov edx, dword ptr [edi + 0x164]
0069b20b xor eax, eax
0069b20d and edx, 0x20000
0069b213 mov ecx, edi
0069b215 or eax, edx
0069b217 je 0x69b223
0069b219 call 0x6a0950
0069b21e jmp 0x6a088c
0069b223 push 0
0069b225 push 2
0069b227 call 0x684790
0069b22c test al, al
0069b22e je 0x69b27f
0069b230 mov eax, dword ptr [edi + 0x160]
0069b236 and eax, 0x20000000
0069b23b or eax, 0
0069b23e jne 0x69b27f
0069b240 push eax
0069b241 mov ecx, edi
0069b243 call 0x68cf40
0069b248 test al, al
0069b24a je 0x69b27f
0069b24c mov eax, dword ptr [0xbfd65c]
0069b251 push 0x40
0069b253 mov ecx, dword ptr [eax + 0x18190]
0069b259 add ecx, 0x71f4
0069b25f call 0x88b600
0069b264 test al, al
0069b266 je 0x69b27f
0069b268 push 0
0069b26a lea ecx, [ebp - 0x38]
0069b26d call 0x4229a0
0069b272 push -3
0069b274 lea eax, [ebp - 0x38]
0069b277 mov ecx, edi
0069b279 push eax
0069b27a call 0x68ebd0
0069b27f mov ecx, dword ptr [edi + 0xea8]
0069b285 test ecx, ecx
0069b287 je 0x69b2c7
0069b289 cmp dword ptr [ecx + 0x31c], edi
0069b28f jne 0x69b2c7
0069b291 mov eax, dword ptr [edi + 0x294]
0069b297 mov dword ptr [ecx + 0x294], eax
0069b29d mov eax, dword ptr [edi + 0x298]
0069b2a3 mov dword ptr [ecx + 0x298], eax
0069b2a9 mov ecx, dword ptr [edi + 0xea8]
0069b2af mov eax, dword ptr [edi + 0x2b8]
0069b2b5 mov dword ptr [ecx + 0x2b8], eax
0069b2bb mov eax, dword ptr [edi + 0x2bc]
0069b2c1 mov dword ptr [ecx + 0x2bc], eax
0069b2c7 cmp dword ptr [edi + 0x28], 0x17
0069b2cb jne 0x69b2dd
0069b2cd cmp dword ptr [edi + 0x2c], 0
0069b2d1 jne 0x69b2dd
0069b2d3 cmp dword ptr [edi + 0x30], 1
0069b2d7 jne 0x69b2dd
0069b2d9 mov cl, 1
0069b2db jmp 0x69b2df
0069b2dd xor cl, cl
0069b2df mov eax, dword ptr [edi + 0xbb4]
0069b2e5 mov dword ptr [ebp - 0x278], 0
0069b2ef cmp eax, 0x16
0069b2f2 jne 0x69b300
0069b2f4 mov dword ptr [ebp - 0x278], 0xb49018
0069b2fe jmp 0x69b311
