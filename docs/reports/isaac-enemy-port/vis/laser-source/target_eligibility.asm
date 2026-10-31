008c5a90 push ebp
008c5a91 mov ebp, esp
008c5a93 push ecx
008c5a94 push ebx
008c5a95 push esi
008c5a96 push edi
008c5a97 mov edi, dword ptr [ebp + 8]
008c5a9a mov dword ptr [ebp - 4], ecx
008c5a9d mov esi, dword ptr [edi + 0x28]
008c5aa0 cmp esi, 0x11
008c5aa3 je 0x8c5bc0
008c5aa9 mov edx, dword ptr [ecx + 0x314]
008c5aaf test edx, edx
008c5ab1 je 0x8c5acd
008c5ab3 mov eax, dword ptr [edx + 0x28]
008c5ab6 mov dword ptr [ebp + 8], eax
008c5ab9 mov eax, dword ptr [edx + 0x160]
008c5abf and eax, 0x100
008c5ac4 or eax, 0
008c5ac7 je 0x8c5ad4
008c5ac9 mov bh, 1
008c5acb jmp 0x8c5ad6
008c5acd mov dword ptr [ebp + 8], 0
008c5ad4 xor bh, bh
008c5ad6 cmp esi, 3
008c5ad9 jne 0x8c5b03
008c5adb mov eax, dword ptr [edi + 0x2c]
008c5ade cmp eax, 0x3e
008c5ae1 je 0x8c5aff
008c5ae3 cmp eax, 0x43
008c5ae6 je 0x8c5aff
008c5ae8 cmp eax, 0xd3
008c5aed je 0x8c5aff
008c5aef cmp eax, 0xce
008c5af4 jne 0x8c5b03
008c5af6 cmp dword ptr [edi + 0x30], 0x1ab
008c5afd jne 0x8c5b03
008c5aff mov bl, 1
008c5b01 jmp 0x8c5b05
008c5b03 xor bl, bl
008c5b05 cmp edi, edx
008c5b07 je 0x8c5b27
008c5b09 cmp byte ptr [edi + 0x16b], 0
008c5b10 jne 0x8c5b27
008c5b12 cmp dword ptr [edi + 0x180], 0
008c5b19 je 0x8c5b27
008c5b1b xorps xmm0, xmm0
008c5b1e comiss xmm0, dword ptr [edi + 0x2dc]
008c5b25 jb 0x8c5b2f
008c5b27 test bl, bl
008c5b29 je 0x8c5bc0
008c5b2f cmp dword ptr [ebp + 8], esi
008c5b32 jne 0x8c5b3c
008c5b34 test bh, bh
008c5b36 je 0x8c5bc0
008c5b3c mov eax, dword ptr [ecx + 0x47c]
008c5b42 test eax, eax
008c5b44 je 0x8c5b5e
008c5b46 mov ecx, dword ptr [eax + 0x47c]
008c5b4c test ecx, ecx
008c5b4e je 0x8c5b57
008c5b50 call 0x8c5980
008c5b55 jmp 0x8c5b64
008c5b57 add eax, 0x470
008c5b5c jmp 0x8c5b64
008c5b5e lea eax, [ecx + 0x470]
008c5b64 push edi
008c5b65 mov ecx, eax
008c5b67 call 0x422d00
008c5b6c test al, al
008c5b6e jne 0x8c5bc0
008c5b70 mov ecx, dword ptr [ebp - 4]
008c5b73 call 0x8c5a50
008c5b78 test al, al
008c5b7a je 0x8c5bcb
008c5b7c cmp dword ptr [ebp + 8], 3
008c5b80 jne 0x8c5b86
008c5b82 test bh, bh
008c5b84 jne 0x8c5bcb
008c5b86 lea eax, [esi - 0xa]
008c5b89 cmp eax, 0x3dd
008c5b8e ja 0x8c5ba2
008c5b90 push 0
008c5b92 push 0x20000000
008c5b97 mov ecx, edi
008c5b99 call 0x4122f0
008c5b9e test al, al
008c5ba0 je 0x8c5bde
008c5ba2 cmp dword ptr [edi + 0x180], 0
008c5ba9 je 0x8c5bc0
008c5bab cmp esi, 0x21
008c5bae je 0x8c5bde
008c5bb0 cmp esi, 0x124
008c5bb6 je 0x8c5bde
008c5bb8 cmp esi, 0xf5
008c5bbe je 0x8c5bde
008c5bc0 xor al, al
008c5bc2 pop edi
008c5bc3 pop esi
008c5bc4 pop ebx
008c5bc5 mov esp, ebp
008c5bc7 pop ebp
008c5bc8 ret 4
008c5bcb cmp esi, 1
008c5bce je 0x8c5bde
008c5bd0 lea eax, [esi - 0xa]
008c5bd3 cmp eax, 0x3dd
008c5bd8 jbe 0x8c5bde
008c5bda test bl, bl
008c5bdc je 0x8c5bc0
008c5bde pop edi
008c5bdf pop esi
008c5be0 mov al, 1
008c5be2 pop ebx
008c5be3 mov esp, ebp
008c5be5 pop ebp
008c5be6 ret 4
