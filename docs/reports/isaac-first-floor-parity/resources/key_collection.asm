006c098e mov eax, dword ptr [esi + 0x30]
006c0991 cmp eax, 1
006c0994 jne 0x6c0a22
006c099a mov eax, dword ptr [0xbfd65c]
006c099f cmp dword ptr [eax + 0x1c319c], 0x20
006c09a6 jne 0x6c0a0f
006c09a8 push 6
006c09aa lea ecx, [esi + 0x334]
006c09b0 call 0x7a7d50
006c09b5 cmp eax, 5
006c09b8 ja 0x6c097b
006c09ba jmp dword ptr [eax*4 + 0x6c2860]
006c09c1 push 1
006c09c3 mov ecx, edi
006c09c5 call 0x725810
006c09ca mov al, 1
006c09cc mov byte ptr [ebp - 0x6d], al
006c09cf jmp 0x6c02a5
006c09d4 push 1
006c09d6 push 1
006c09d8 mov ecx, edi
006c09da call 0x724f00
006c09df mov al, 1
006c09e1 mov byte ptr [ebp - 0x6d], al
006c09e4 jmp 0x6c02a5
006c09e9 push 1
006c09eb mov ecx, edi
006c09ed call 0x725130
006c09f2 mov al, 1
006c09f4 mov byte ptr [ebp - 0x6d], al
006c09f7 jmp 0x6c02a5
006c09fc push 1
006c09fe mov ecx, edi
006c0a00 call 0x725380
006c0a05 mov al, 1
006c0a07 mov byte ptr [ebp - 0x6d], al
006c0a0a jmp 0x6c02a5
006c0a0f push 1
006c0a11 mov ecx, edi
006c0a13 call 0x7258c0
006c0a18 mov al, 1
006c0a1a mov byte ptr [ebp - 0x6d], al
006c0a1d jmp 0x6c02a5
006c0a22 cmp eax, 3
006c0a25 jne 0x6c0ace
006c0a2b mov eax, dword ptr [0xbfd65c]
006c0a30 cmp dword ptr [eax + 0x1c319c], 0x20
006c0a37 jne 0x6c0abb
006c0a3d push 6
006c0a3f lea ecx, [esi + 0x334]
006c0a45 call 0x7a7d50
006c0a4a cmp eax, 5
006c0a4d ja 0x6c097b
006c0a53 jmp dword ptr [eax*4 + 0x6c2878]
006c0a5a push 2
006c0a5c mov ecx, edi
006c0a5e call 0x725810
006c0a63 mov al, 1
006c0a65 mov byte ptr [ebp - 0x6d], al
006c0a68 jmp 0x6c02a5
006c0a6d push 1
006c0a6f push 2
006c0a71 mov ecx, edi
006c0a73 call 0x724f00
006c0a78 mov al, 1
006c0a7a mov byte ptr [ebp - 0x6d], al
006c0a7d jmp 0x6c02a5
006c0a82 push 2
006c0a84 mov ecx, edi
006c0a86 call 0x725130
006c0a8b mov al, 1
006c0a8d mov byte ptr [ebp - 0x6d], al
006c0a90 jmp 0x6c02a5
006c0a95 push 2
006c0a97 mov ecx, edi
006c0a99 call 0x725380
006c0a9e mov al, 1
006c0aa0 mov byte ptr [ebp - 0x6d], al
006c0aa3 jmp 0x6c02a5
006c0aa8 push 2
006c0aaa mov ecx, edi
006c0aac call 0x78be00
006c0ab1 mov al, 1
006c0ab3 mov byte ptr [ebp - 0x6d], al
006c0ab6 jmp 0x6c02a5
006c0abb push 2
006c0abd mov ecx, edi
006c0abf call 0x7258c0
006c0ac4 mov al, 1
006c0ac6 mov byte ptr [ebp - 0x6d], al
006c0ac9 jmp 0x6c02a5
006c0ace cmp eax, 2
006c0ad1 jne 0x6c0b3a
006c0ad3 mov eax, dword ptr [0xbfd65c]
006c0ad8 cmp dword ptr [eax + 0x1c319c], 0x20
006c0adf jne 0x6c0b29
006c0ae1 push 3
006c0ae3 lea ecx, [esi + 0x334]
006c0ae9 call 0x7a7d50
006c0aee sub eax, 0
006c0af1 je 0x6c0c8d
006c0af7 sub eax, 1
006c0afa je 0x6c0b18
006c0afc sub eax, 1
006c0aff jne 0x6c097b
006c0b05 push 1
006c0b07 mov ecx, edi
006c0b09 call 0x78be00
006c0b0e mov al, 1
006c0b10 mov byte ptr [ebp - 0x6d], al
006c0b13 jmp 0x6c02a5
006c0b18 mov ecx, edi
006c0b1a call 0x78b1d0
006c0b1f mov al, 1
006c0b21 mov byte ptr [ebp - 0x6d], al
006c0b24 jmp 0x6c02a5
006c0b29 mov ecx, edi
006c0b2b call 0x725930
006c0b30 mov al, 1
006c0b32 mov byte ptr [ebp - 0x6d], al
006c0b35 jmp 0x6c02a5
006c0b3a cmp eax, 4
006c0b3d jne 0x6c1f4c
006c0b43 push 1
006c0b45 mov ecx, edi
006c0b47 call 0x7258c0
006c0b4c xor esi, esi
006c0b4e nop 
006c0b50 push 0
006c0b52 push 0
006c0b54 push 1
006c0b56 push esi
006c0b57 push 6
006c0b59 mov ecx, edi
006c0b5b call 0x758030
006c0b60 test eax, eax
006c0b62 jne 0x6c097b
006c0b68 inc esi
006c0b69 cmp esi, 4
006c0b6c jb 0x6c0b50
006c0b6e mov al, 1
006c0b70 mov byte ptr [ebp - 0x6d], al
006c0b73 jmp 0x6c02a5
