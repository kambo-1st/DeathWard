007599f2 mov eax, dword ptr [edi + 0x1534]
007599f8 test eax, eax
007599fa je 0x759a0f
007599fc cmp dword ptr [edi + ecx*4 + 0x14c4], eax
00759a03 je 0x759a0f
00759a05 mov ecx, edi
00759a07 call 0x786fa0
00759a0c mov ecx, dword ptr [ebp - 0x44]
00759a0f mov byte ptr [edi + 0x1f70], 2
00759a16 mov eax, dword ptr [edi + ecx*4 + 0x14c4]
00759a1d mov dword ptr [edi + 0x1f74], eax
00759a23 mov eax, dword ptr [edi + ecx*4 + 0x14dc]
00759a2a mov dword ptr [edi + 0x1f78], eax
00759a30 xor eax, eax
00759a32 cmp byte ptr [ebp - 0x46], al
00759a35 push 0
00759a37 setne al
00759a3a push ebx
00759a3b add eax, 4
00759a3e push eax
00759a3f push dword ptr [edi + ecx*4 + 0x14c4]
00759a46 lea eax, [ebp - 0x56]
00759a49 mov ecx, edi
00759a4b push eax
00759a4c call 0x5a1360
00759a51 mov ax, word ptr [eax]
00759a54 mov word ptr [ebp - 0x6c], ax
00759a58 push 0
00759a5a push 0x164
00759a5f mov ecx, edi
00759a61 call 0x73af30
00759a66 test al, al
00759a68 je 0x759ab5
00759a6a cmp dword ptr [edi + 0x1534], 0
00759a71 jne 0x759ab5
00759a73 cmp dword ptr [ebp - 0x4c], 0
00759a77 jne 0x759ab5
00759a79 cmp byte ptr [ebp - 0x6b], 0
00759a7d jne 0x759ab5
00759a7f mov eax, dword ptr [ebp - 0x44]
00759a82 mov eax, dword ptr [edi + eax*4 + 0x14c4]
00759a89 test eax, eax
00759a8b je 0x759ab5
00759a8d cmp dword ptr [ebp - 0x50], 0
00759a91 jle 0x759ab5
00759a93 cmp eax, 0x20b
00759a98 je 0x759ab5
00759a9a cmp eax, 0x20f
00759a9f je 0x759ab5
00759aa1 push esi
00759aa2 push -1
00759aa4 push 0x621
00759aa9 push eax
00759aaa lea eax, [ebp - 0x56]
00759aad mov ecx, edi
00759aaf push eax
00759ab0 call 0x5a1360
00759ab5 cmp byte ptr [ebp - 0x6c], 0
00759ab9 je 0x759ac6
00759abb push dword ptr [ebp - 0x6b]
00759abe mov ecx, edi
00759ac0 push ebx
00759ac1 call 0x771510
00759ac6 cmp byte ptr [ebp - 0x6b], 0
00759aca mov esi, dword ptr [ebp - 0x44]
00759acd je 0x759ae2
