00884e40 push ebp
00884e41 mov ebp, esp
00884e43 sub esp, 0xd4
00884e49 mov eax, dword ptr [0xbaa3b4]
00884e4e xor eax, ebp
00884e50 mov dword ptr [ebp - 4], eax
00884e53 mov eax, dword ptr [ebp + 0xc]
00884e56 push ebx
00884e57 mov ebx, dword ptr [ebp + 8]
00884e5a push esi
00884e5b mov esi, ecx
00884e5d push edi
00884e5e cmp byte ptr [esi + 1], 0
00884e62 jne 0x8855b8
00884e68 mov edi, dword ptr [esi + ebx*4 + 0x2b8]
00884e6f mov edx, eax
00884e71 neg edx
00884e73 lea ecx, [edi + eax]
00884e76 xor eax, eax
00884e78 cmp edx, edi
00884e7a cmovle eax, ecx
00884e7d mov dword ptr [esi + ebx*4 + 0x2b8], eax
00884e84 mov byte ptr [esi], 1
